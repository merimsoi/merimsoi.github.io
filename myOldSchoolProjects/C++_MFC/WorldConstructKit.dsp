# Microsoft Developer Studio Project File - Name="WorldConstructKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WorldConstructKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WorldConstructKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WorldConstructKit.mak" CFG="WorldConstructKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WorldConstructKit - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WorldConstructKit - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/WORLDCONSTRUCTKIT", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WorldConstructKit - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /map

!ELSEIF  "$(CFG)" == "WorldConstructKit - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /w /W0 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /O<none>
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WorldConstructKit - Win32 Release"
# Name "WorldConstructKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnimationInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\CameraDefinitionView.cpp
# End Source File
# Begin Source File

SOURCE=.\CharacterContextView.cpp
# End Source File
# Begin Source File

SOURCE=.\CharacterInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\engineClasses.cpp
# End Source File
# Begin Source File

SOURCE=.\forms.cpp
# End Source File
# Begin Source File

SOURCE=.\HotSpotInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemDefinitionView.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyboardTriggerView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicSampleView.cpp
# End Source File
# Begin Source File

SOURCE=.\MusicScriptView.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\NewNodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SceneDefinitionView.cpp
# End Source File
# Begin Source File

SOURCE=.\SFXInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\SkyDefinitionView.cpp
# End Source File
# Begin Source File

SOURCE=.\StagingInfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StdString.cpp
# End Source File
# Begin Source File

SOURCE=.\TemplateFormView.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDisplayView.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldConstructKit.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldConstructKit.rc
# End Source File
# Begin Source File

SOURCE=.\WorldConstructKitDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldDefinitionView.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnimationInfoView.h
# End Source File
# Begin Source File

SOURCE=.\basic.h
# End Source File
# Begin Source File

SOURCE=.\CameraDefinitionView.h
# End Source File
# Begin Source File

SOURCE=.\CharacterContextView.h
# End Source File
# Begin Source File

SOURCE=.\CharacterInfoView.h
# End Source File
# Begin Source File

SOURCE=.\engineClasses.h
# End Source File
# Begin Source File

SOURCE=.\engineClassesBasic.h
# End Source File
# Begin Source File

SOURCE=.\forms.h
# End Source File
# Begin Source File

SOURCE=.\HotSpotInfoView.h
# End Source File
# Begin Source File

SOURCE=.\ImageInfoView.h
# End Source File
# Begin Source File

SOURCE=.\ItemDefinitionView.h
# End Source File
# Begin Source File

SOURCE=.\KeyboardTriggerView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MusicSampleView.h
# End Source File
# Begin Source File

SOURCE=.\MusicScriptView.h
# End Source File
# Begin Source File

SOURCE=.\MyTreeView.h
# End Source File
# Begin Source File

SOURCE=.\NewNodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SceneDefinitionView.h
# End Source File
# Begin Source File

SOURCE=.\SFXInfoView.h
# End Source File
# Begin Source File

SOURCE=.\SkyDefinitionView.h
# End Source File
# Begin Source File

SOURCE=.\StagingInfoView.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\stdList.h
# End Source File
# Begin Source File

SOURCE=.\StdString.h
# End Source File
# Begin Source File

SOURCE=.\TemplateFormView.h
# End Source File
# Begin Source File

SOURCE=.\TextDisplayView.h
# End Source File
# Begin Source File

SOURCE=.\WorldConstructKit.h
# End Source File
# Begin Source File

SOURCE=.\WorldConstructKitDoc.h
# End Source File
# Begin Source File

SOURCE=.\WorldDefinitionView.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeImageList.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WorldConstructKit.ico
# End Source File
# Begin Source File

SOURCE=.\res\WorldConstructKit.rc2
# End Source File
# Begin Source File

SOURCE=.\res\WorldConstructKitDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
