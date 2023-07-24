<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="21008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="FindVISA_UI.vi" Type="VI" URL="../FindVISA_UI.vi"/>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build">
			<Item Name="Find VISA application" Type="EXE">
				<Property Name="App_copyErrors" Type="Bool">true</Property>
				<Property Name="App_INI_aliasGUID" Type="Str">{7216BA7B-6E28-4B34-A78B-1F84322B363D}</Property>
				<Property Name="App_INI_GUID" Type="Str">{3EC1C637-20BB-4C14-8C3A-0EE19D78BA48}</Property>
				<Property Name="App_serverConfig.httpPort" Type="Int">8002</Property>
				<Property Name="App_serverType" Type="Int">0</Property>
				<Property Name="Bld_autoIncrement" Type="Bool">true</Property>
				<Property Name="Bld_buildCacheID" Type="Str">{62332D08-E63A-4597-B7B0-84BEA6E2F795}</Property>
				<Property Name="Bld_buildSpecName" Type="Str">Find VISA application</Property>
				<Property Name="Bld_excludeInlineSubVIs" Type="Bool">true</Property>
				<Property Name="Bld_excludeLibraryItems" Type="Bool">true</Property>
				<Property Name="Bld_excludePolymorphicVIs" Type="Bool">true</Property>
				<Property Name="Bld_localDestDir" Type="Path">../Builds</Property>
				<Property Name="Bld_localDestDirType" Type="Str">relativeToProject</Property>
				<Property Name="Bld_modifyLibraryFile" Type="Bool">true</Property>
				<Property Name="Bld_previewCacheID" Type="Str">{5D594B5A-307A-4BC7-8994-425F6D897BF4}</Property>
				<Property Name="Bld_version.build" Type="Int">2</Property>
				<Property Name="Bld_version.major" Type="Int">1</Property>
				<Property Name="Destination[0].destName" Type="Str">FindVISA.exe</Property>
				<Property Name="Destination[0].path" Type="Path">../Builds/NI_AB_PROJECTNAME.exe</Property>
				<Property Name="Destination[0].path.type" Type="Str">relativeToProject</Property>
				<Property Name="Destination[0].preserveHierarchy" Type="Bool">true</Property>
				<Property Name="Destination[0].type" Type="Str">App</Property>
				<Property Name="Destination[1].destName" Type="Str">Support Directory</Property>
				<Property Name="Destination[1].path" Type="Path">../Builds/data</Property>
				<Property Name="Destination[1].path.type" Type="Str">relativeToProject</Property>
				<Property Name="DestinationCount" Type="Int">2</Property>
				<Property Name="Source[0].itemID" Type="Str">{7269C949-5B44-4AB5-A748-BF6E76D95470}</Property>
				<Property Name="Source[0].type" Type="Str">Container</Property>
				<Property Name="Source[1].destinationIndex" Type="Int">0</Property>
				<Property Name="Source[1].itemID" Type="Ref">/My Computer/FindVISA_UI.vi</Property>
				<Property Name="Source[1].sourceInclusion" Type="Str">TopLevel</Property>
				<Property Name="Source[1].type" Type="Str">VI</Property>
				<Property Name="SourceCount" Type="Int">2</Property>
				<Property Name="TgtF_companyName" Type="Str">Radboud Universiteit</Property>
				<Property Name="TgtF_fileDescription" Type="Str">Find VISA application</Property>
				<Property Name="TgtF_internalName" Type="Str">Find VISA application</Property>
				<Property Name="TgtF_legalCopyright" Type="Str">Copyright © 2023 Radboud Universiteit</Property>
				<Property Name="TgtF_productName" Type="Str">Find VISA application</Property>
				<Property Name="TgtF_targetfileGUID" Type="Str">{5EEA6AAA-D919-49A2-B3B1-C9ABFE3EC046}</Property>
				<Property Name="TgtF_targetfileName" Type="Str">FindVISA.exe</Property>
				<Property Name="TgtF_versionIndependent" Type="Bool">true</Property>
			</Item>
		</Item>
	</Item>
</Project>
