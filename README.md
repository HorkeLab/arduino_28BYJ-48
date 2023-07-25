# Description
This repository contains all files necessary to control 28BYJ-48 type stepper motors using an arduino MEGA with sensor shield. It is based on the previous work by Luis José Salazar-Serrano and sources cited therein -  https://github.com/totesalaz/MKM

The steppers can be controller using simple terminal commands, as detailed in the documentation. We also provide a LabView UI (including compiled executable) to control two motors, for example to control the tip/tilt of a kinematic mirror mount.

We use this motor control for out motorized optical components:
-motorized kinematic mirror mount (KM100) - https://github.com/HorkeLab/motorized_kinematic_mount

# Folder structure

The folder **Arduino_SourceCode** contains the program that should be uploaded to the Arduino board, while **LabView_Projects** corresponds to graphical interfaces written in LabView to interact with the motors. 