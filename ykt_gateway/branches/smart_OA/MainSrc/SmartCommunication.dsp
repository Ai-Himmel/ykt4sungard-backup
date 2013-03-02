# Microsoft Developer Studio Project File - Name="SmartCommunication" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SmartCommunication - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SmartCommunication.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SmartCommunication.mak" CFG="SmartCommunication - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SmartCommunication - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SmartCommunication - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SmartCommunication - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /Zi /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"../bin/Smart_054140AO.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "SmartCommunication - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"../bin/Smart_054140AO.exe" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "SmartCommunication - Win32 Release"
# Name "SmartCommunication - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Data.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\readfile.cpp
# End Source File
# Begin Source File

SOURCE=.\Smart.cpp
# End Source File
# Begin Source File

SOURCE=.\Smart_userdes.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartBlackListMemoryOper.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartCom.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartCommunication.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartCommunication.rc
# End Source File
# Begin Source File

SOURCE=.\SmartCommunicationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartLog.cpp
# End Source File
# Begin Source File

SOURCE=.\SmartSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SystemInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=.\TThread.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Data.h
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# Begin Source File

SOURCE=.\public.h
# End Source File
# Begin Source File

SOURCE=.\readfile.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Smart.h
# End Source File
# Begin Source File

SOURCE=.\SmartBlackListMemoryOper.h
# End Source File
# Begin Source File

SOURCE=.\SmartCom.h
# End Source File
# Begin Source File

SOURCE=.\SmartCommunication.h
# End Source File
# Begin Source File

SOURCE=.\SmartCommunicationDlg.h
# End Source File
# Begin Source File

SOURCE=.\SmartLog.h
# End Source File
# Begin Source File

SOURCE=.\SmartSocket.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SystemInfo.h
# End Source File
# Begin Source File

SOURCE=.\SystemTray.h
# End Source File
# Begin Source File

SOURCE=.\TDatabase.h
# End Source File
# Begin Source File

SOURCE=.\TThread.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\log.bmp
# End Source File
# Begin Source File

SOURCE=.\res\log.ico
# End Source File
# Begin Source File

SOURCE=.\res\LOGO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\sb.ico
# End Source File
# Begin Source File

SOURCE=.\res\SmartCommunication.ico
# End Source File
# Begin Source File

SOURCE=.\res\SmartCommunication.rc2
# End Source File
# End Group
# Begin Group "Export_Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\export\include\bccclt.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
