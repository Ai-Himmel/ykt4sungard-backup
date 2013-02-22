# Microsoft Developer Studio Project File - Name="SmartServer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SmartServer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SmartServer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmartServer.mak" CFG="SmartServer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmartServer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SmartServer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SmartServer - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MTd /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"..\Release\SmartServer.exe"

!ELSEIF  "$(CFG)" == "SmartServer - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\Include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\Bin\SmartServer.exe" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "SmartServer - Win32 Release"
# Name "SmartServer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\SmartServer.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartServer.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TCmdBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\TDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\TExportFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\TServer.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartChannels.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartModule.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartMonitor.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartOutThread.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartPacket.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartProtocol.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartRegister.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartServer.cpp
# End Source File
# Begin Source File

SOURCE=.\TSmartTask.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Include\Common.h
# End Source File
# Begin Source File

SOURCE=.\SmartServer.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TCmdBuffer.h
# End Source File
# Begin Source File

SOURCE=.\TDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TExportFunc.h
# End Source File
# Begin Source File

SOURCE=.\TServer.h
# End Source File
# Begin Source File

SOURCE=.\TSmartChannels.h
# End Source File
# Begin Source File

SOURCE=.\TSmartDoc.h
# End Source File
# Begin Source File

SOURCE=.\TSmartModule.h
# End Source File
# Begin Source File

SOURCE=.\TSmartMonitor.h
# End Source File
# Begin Source File

SOURCE=.\TSmartOutThread.h
# End Source File
# Begin Source File

SOURCE=.\TSmartPacket.h
# End Source File
# Begin Source File

SOURCE=.\TSmartProtocol.h
# End Source File
# Begin Source File

SOURCE=.\TSmartRegister.h
# End Source File
# Begin Source File

SOURCE=.\TSmartServer.h
# End Source File
# Begin Source File

SOURCE=.\TSmartTask.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\mainfram.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
