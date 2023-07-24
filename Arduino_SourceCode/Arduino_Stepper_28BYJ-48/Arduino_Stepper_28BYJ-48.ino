/*

  Filename: UCD_motor_control.ino
  Created by Daniel Horke and Ana Caballo
  Contact: d.horke@science.ru.nl
  https://www.ultrafast-dynamics.com

  Based on the work by Luis José Salazar-Serrano and sources cited therein
  https://github.com/totesalaz/MKM

  This code is available under the GNU General Public License v3.0
  https://www.gnu.org/licenses/gpl-3.0.en.html#license-text

  Description: 
  Program that allows to control TEN stepper motors (28BYJ-48) connected to an 
  Arduino Mega sensor shield. The motors are connected to the following pins:
   
  motor1 -> 8, 9, 10, 11
  motor2 -> 4, 5, 6, 7
  motor3 -> 22, 23, 24, 25
  motor4 -> 26, 27, 28, 29
  motor5 -> 30, 31, 32, 33
  motor6 -> 34, 35, 36, 37
  motor7 -> 38, 39, 40, 41
  motor8 -> 42, 43, 44, 45 
  motor9 -> 46, 47, 48, 49
  motor10-> 50, 51, 52, 53
 
  The following commands are used to control the connected motors:
  
  | Command       | Description                                                     |
  | STPM:N:ABS:X  | move stetper motor N to absolute position X (in steps)          |
  | STPM:N:REL:X  | move stepper motor N, relative to current position              |
  | STPM:N:RST    | reset stepper motor N counter to to 0                           |
  | STPM:N:VEL:X  | set stepper motor N velocity to X, where X [1 fast | 10 slow]   |
  | STPM:N:STAT   | retrieve motor N current status (position, velocity, state)     |
  |               | velocity -> [1 fast | 10 slow]                                  |
  |               | state -> [0 stop | 1 moving]  
  | STATUS        | retrieve status of all 10 motors
  | STOP          | emergency stop. Press reset button to restart                   |

  
*/

#include <EEPROM.h>

const byte interruptPin = 21; // attach "panic button" to external interrupt pin

String commandString = ""; // a string to hold incoming data
boolean stringComplete = false; // whether the string is complete

// function that determines sign +/- of argument
int sign(int x) { 
  return (x>0) - (x<0); 
}

typedef struct {
  
  int cnt;
  int vel;
  boolean state;

} motorStatus;

class StepperMotor
{  
  int motorPin1;  //blue cable stepper motor 28BYJ-48
  int motorPin2;  //pink cable stepper motor 28BYJ-48
  int motorPin3;  //yellow cable stepper motor 28BYJ-48
  int motorPin4;  //orange cable stepper motor 28BYJ-48
  int memoryPos;  //EEPROM memory position
  
  int newPosition;
 
  unsigned int currentSpeed; 
  unsigned long previousMillis;
  
  motorStatus array;
 
  int motorSequence[8];
  
  //Constructor
  public: 
  StepperMotor(int bluePin, int pinkPin, int yellowPin, int orangePin, int memorySlot)
  {
    motorPin1 = bluePin;
    pinMode(motorPin1,OUTPUT);
    motorPin2 = pinkPin;
    pinMode(motorPin2,OUTPUT);
    motorPin3 = yellowPin;
    pinMode(motorPin3,OUTPUT);
    motorPin4 = orangePin;
    pinMode(motorPin4,OUTPUT);
    memoryPos = memorySlot;
       
//    array.cnt = 0;
    EEPROM.get(memoryPos*sizeof(int), array.cnt); 

    array.vel = 1;
    array.state = false;
//    newPosition = 0;
    EEPROM.get(memoryPos*sizeof(int), newPosition);   
    previousMillis = 0;

    motorSequence[0] = B1000;
    motorSequence[1] = B1100;
    motorSequence[2] = B0100;
    motorSequence[3] = B0110;
    motorSequence[4] = B0010;
    motorSequence[5] = B0011;
    motorSequence[6] = B0001;
    motorSequence[7] = B1001;    
}
  
  void Update()
  {
            
    unsigned long currentMillis = millis();
    if((currentMillis-previousMillis >= abs(array.vel)) && (newPosition != array.cnt)){
              
      previousMillis = currentMillis;
      array.cnt += sign(newPosition-array.cnt);     
//      EEPROM.put(motorPin1*sizeof(int), array.cnt);  // don't use it! 
      
      digitalWrite(motorPin1,bitRead(motorSequence[((array.cnt % 8) + 8) % 8],0));
      digitalWrite(motorPin2,bitRead(motorSequence[((array.cnt % 8) + 8) % 8],1));
      digitalWrite(motorPin3,bitRead(motorSequence[((array.cnt % 8) + 8) % 8],2));
      digitalWrite(motorPin4,bitRead(motorSequence[((array.cnt % 8) + 8) % 8],3));                 

      if(newPosition == array.cnt){        
        EEPROM.put(memoryPos*sizeof(int), array.cnt);  
        array.state = false;
        digitalWrite(motorPin1,0);
        digitalWrite(motorPin2,0);
        digitalWrite(motorPin3,0);
        digitalWrite(motorPin4,0);                 
      }else{
        array.state = true; // motor is moving
      }

    }
  }

  void relMove(int steps)
  { 
    newPosition = array.cnt + steps;
  }

  void absMove(int steps)
  { 
    newPosition = steps;
  }

  void velMove(int velocity)
  { 
    array.vel = velocity;
  }

  void Status(){
//    EEPROM.get(memoryPos*sizeof(int), array.cnt);
    Serial.println(String(array.cnt)+":"+String(array.vel)+":"+String(array.state));    
  }
  
  void resetCnt()
  { 
    array.cnt = 0;
    newPosition = 0;
    EEPROM.put(memoryPos*sizeof(int), array.cnt);  
  }
  
  void emerStop()
  { 
    EEPROM.put(memoryPos*sizeof(int), array.cnt);  
  }

};

StepperMotor motor1(8,9,10,11,0);
StepperMotor motor2(4,5,6,7,1);  
StepperMotor motor3(22,23,24,25,2);
StepperMotor motor4(26,27,28,29,3);
StepperMotor motor5(30,31,32,33,4);
StepperMotor motor6(34,35,36,37,5);
StepperMotor motor7(38,39,40,41,6);
StepperMotor motor8(42,43,44,45,7);
StepperMotor motor9(46,47,48,49,8);
StepperMotor motor10(50,51,52,53,9);

void setup()
{
  Serial.begin(9600);
  /* // uncomment to initialize EEPROM memory to 0
  EEPROM.put(0*sizeof(int), 0);
  EEPROM.put(1*sizeof(int), 0);  
  EEPROM.put(2*sizeof(int), 0);  
  EEPROM.put(3*sizeof(int), 0);  
  // */  
  attachInterrupt(digitalPinToInterrupt(interruptPin), emergency, CHANGE);
}

void loop()
{

  motor1.Update();
  motor2.Update();
  motor3.Update();
  motor4.Update();
  motor5.Update();
  motor6.Update();
  motor7.Update();
  motor8.Update();
  motor9.Update();
  motor10.Update();
    
}


/*
SerialEvent occurs whenever a new data comes in the
hardware serial RX. This routine is run between each
time loop() runs, so using delay inside loop can delay
response. Multiple bytes of data may be available.

Function taken from:
https://www.arduino.cc/en/Tutorial/SerialEvent
*/

void serialEvent() {

while (Serial.available()) {
// get the new byte:
char inChar = (char)Serial.read();

// add it to the inputString:
if (inChar != '\n')
commandString += inChar;
//Serial.println(commandString);

// if the incoming character is a newline, set a flag
// so the main loop can do something about it:
if (inChar == '\n'){
  commandString.toUpperCase();
//  Serial.println(commandString);
  stringComplete = true;
}
}

if(stringComplete){
//  Serial.println(commandString.substring(0,11));
//  Serial.println(String(commandString.substring(11).toInt()+10));

  // motor1
  if(commandString.substring(0,11) == "STPM:1:REL:"){  
    motor1.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:1:ABS:"){   
    motor1.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:1:VEL:"){  
    motor1.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:1:RST"){  
    motor1.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:1:STAT"){
    motor1.Status();
  }

  // motor2
  if(commandString.substring(0,11) == "STPM:2:REL:"){  
    motor2.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:2:ABS:"){   
    motor2.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:2:VEL:"){  
    motor2.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:2:RST"){  
    motor2.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:2:STAT"){
    motor2.Status();
  }

  // motor3
  if(commandString.substring(0,11) == "STPM:3:REL:"){  
    motor3.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:3:ABS:"){   
    motor3.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:3:VEL:"){  
    motor3.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:3:RST"){  
    motor3.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:3:STAT"){
    motor3.Status();
  } // end motor 3*/
  
  // motor4
  if(commandString.substring(0,11) == "STPM:4:REL:"){  
    motor4.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:4:ABS:"){   
    motor4.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:4:VEL:"){  
    motor4.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:4:RST"){  
    motor4.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:4:STAT"){
    motor4.Status();
  } // end motor 4*/
  
  // motor5
  if(commandString.substring(0,11) == "STPM:5:REL:"){  
    motor5.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:5:ABS:"){   
    motor5.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:5:VEL:"){  
    motor5.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:5:RST"){  
    motor5.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:5:STAT"){
    motor5.Status();
  } // end motor 5*/

  // motor6
  if(commandString.substring(0,11) == "STPM:6:REL:"){  
    motor6.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:6:ABS:"){   
    motor6.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:6:VEL:"){  
    motor6.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:6:RST"){  
    motor6.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:6:STAT"){
    motor6.Status();
  } // end motor 6*/

  // motor7
  if(commandString.substring(0,11) == "STPM:7:REL:"){  
    motor7.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:7:ABS:"){   
    motor7.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:7:VEL:"){  
    motor7.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:7:RST"){  
    motor7.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:7:STAT"){
    motor7.Status();
  } // end motor 7*/

  // motor8
  if(commandString.substring(0,11) == "STPM:8:REL:"){  
    motor8.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:8:ABS:"){   
    motor8.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:8:VEL:"){  
    motor8.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:8:RST"){  
    motor8.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:8:STAT"){
    motor8.Status();
  } // end motor 8*/

  // motor9
  if(commandString.substring(0,11) == "STPM:9:REL:"){  
    motor9.relMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:9:ABS:"){   
    motor9.absMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,11) == "STPM:9:VEL:"){  
    motor9.velMove(commandString.substring(11).toInt());
  }

  if(commandString.substring(0,10) == "STPM:9:RST"){  
    motor9.resetCnt();
  }

  if(commandString.substring(0,11) == "STPM:9:STAT"){
    motor9.Status();
  } // end motor 9*/

  // motor10
  if(commandString.substring(0,12) == "STPM:10:REL:"){  
    motor10.relMove(commandString.substring(12).toInt());
  }

  if(commandString.substring(0,12) == "STPM:10:ABS:"){   
    motor10.absMove(commandString.substring(12).toInt());
  }

  if(commandString.substring(0,12) == "STPM:10:VEL:"){  
    motor10.velMove(commandString.substring(12).toInt());
  }

  if(commandString.substring(0,11) == "STPM:10:RST"){  
    motor10.resetCnt();
  }

  if(commandString.substring(0,12) == "STPM:10:STAT"){
    motor10.Status();
  } // end motor 10*/

  if(commandString.substring(0,6) == "STATUS"){
    Serial.println("STATUS REPORT");
    Serial.println("Motor 1:"), motor1.Status();
    Serial.println("Motor 2:"), motor2.Status();
    Serial.println("Motor 3:"), motor3.Status();
    Serial.println("Motor 4:"), motor4.Status();
    Serial.println("Motor 5:"), motor5.Status();
    Serial.println("Motor 6:"), motor6.Status();
    Serial.println("Motor 7:"), motor7.Status();
    Serial.println("Motor 8:"), motor8.Status();
    Serial.println("Motor 9:"), motor9.Status();
    Serial.println("Motor 10:"), motor10.Status();    
  }

  if(commandString.substring(0,4) == "STOP"){
    emergency();
  }
  
  stringComplete = false;
  commandString = "";
}

}//END serialEvent

void emergency(){

  motor1.emerStop();
  motor2.emerStop();
  motor3.emerStop();
  motor4.emerStop();
  motor5.emerStop();
  motor6.emerStop();
  motor7.emerStop();
  motor8.emerStop();
  motor9.emerStop();
  motor10.emerStop();
  
  Serial.println("All motors stopped. Press reset button to restart.");    
  while(1){
  }
}

