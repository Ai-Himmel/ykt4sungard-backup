# Microsoft Developer Studio Project File - Name="testksnl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=testksnl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "testksnl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "testksnl.mak" CFG="testksnl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "testksnl - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "testksnl - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "testksnl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /Fp".\Debug/testksnl.pch" /Fo".\Debug/" /Fd".\Debug/" /GZ /c /GX 
# ADD CPP /nologo /MDd /ZI /W3 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /Fp".\Debug/testksnl.pch" /Fo".\Debug/" /Fd".\Debug/" /GZ /c /GX 
# ADD BASE MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug\testksnl.tlb" /win32 
# ADD MTL /nologo /D"_DEBUG" /mktyplib203 /tlb".\Debug\testksnl.tlb" /win32 
# ADD BASE RSC /l 2052 /d "_DEBUG" 
# ADD RSC /l 2052 /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\bin\testksnl.exe" /incremental:no /debug /pdb:".\Debug\testksnl.pdb" /pdbtype:sept /subsystem:windows /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\bin\testksnl.exe" /incremental:no /debug /pdb:".\Debug\testksnl.pdb" /pdbtype:sept /subsystem:windows /machine:ix86 

!ELSEIF  "$(CFG)" == "testksnl - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /GF /Gy /Yu"stdafx.h" /Fp".\Release/testksnl.pch" /Fo".\Release/" /Fd".\Release/" /c /GX 
# ADD CPP /nologo /MD /W3 /O2 /Ob1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /GF /Gy /Yu"stdafx.h" /Fp".\Release/testksnl.pch" /Fo".\Release/" /Fd".\Release/" /c /GX 
# ADD BASE MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release\testksnl.tlb" /win32 
# ADD MTL /nologo /D"NDEBUG" /mktyplib203 /tlb".\Release\testksnl.tlb" /win32 
# ADD BASE RSC /l 2052 /d "NDEBUG" 
# ADD RSC /l 2052 /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo 
# ADD BSC32 /nologo 
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\bin\testksnl.exe" /incremental:no /pdb:".\Release\testksnl.pdb" /pdbtype:sept /subsystem:windows /machine:ix86 
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /out:"..\bin\testksnl.exe" /incremental:no /pdb:".\Release\testksnl.pdb" /pdbtype:sept /subsystem:windows /machine:ix86 

!ENDIF

# Begin Target

# Name "testksnl - Win32 Debug"
# Name "testksnl - Win32 Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=StdAfx.cpp

!IF  "$(CFG)" == "testksnl - Win32 Debug"

# ADD CPP /nologo /Od /Yc"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "testksnl - Win32 Release"

# ADD CPP /nologo /O2 /Yc"stdafx.h" /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=testksnl.cpp

!IF  "$(CFG)" == "testksnl - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "testksnl - Win32 Release"

# ADD CPP /nologo /O2 /Yu"stdafx.h" /GX 
!ENDIF

# End Source File
# Begin Source File

SOURCE=testksnl.rc
# End Source File
# Begin Source File

SOURCE=testksnlDlg.cpp

!IF  "$(CFG)" == "testksnl - Win32 Debug"

# ADD CPP /nologo /Od /Yu"stdafx.h" /GZ /GX 
!ELSEIF  "$(CFG)" == "testksnl - Win32 Release"

# ADD CPP /nologo /O2 /Yu"stdafx.h" /GX 
!ENDIF

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=StdAfx.h
# End Source File
# Begin Source File

SOURCE=testksnl.h
# End Source File
# Begin Source File

SOURCE=testksnlDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=res\testksnl.ico
# End Source File
# Begin Source File

SOURCE=res\testksnl.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\KSInputDialog.htm
# End Source File
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project

