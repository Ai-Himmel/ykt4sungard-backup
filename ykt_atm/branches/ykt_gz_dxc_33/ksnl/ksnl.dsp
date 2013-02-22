# Microsoft Developer Studio Project File - Name="ksnl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=ksnl - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ksnl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ksnl.mak" CFG="ksnl - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ksnl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ksnl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "ksnl - Win32 Remote Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ksnl - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\Release"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /GF /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GF /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86 /out:"..\bin\ksnl.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /machine:IX86 /out:"..\bin\ksnl.dll" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ksnl - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\Debug"
# PROP Intermediate_Dir ".\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /Zd /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:IX86 /out:"..\bin\ksnl.dll" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /debug /machine:IX86 /out:"..\bin\ksnl.dll" /pdbtype:sept /libpath:"Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ksnl - Win32 Remote Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(ConfigurationName)"
# PROP BASE Intermediate_Dir "$(ConfigurationName)"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "E:\debug"
# PROP Intermediate_Dir "E:\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_MBCS" /FR /Fp".\Debug/ksnl.pch" /Yu"stdafx.h" /Fo".\Debug/" /Fd".\Debug/" /GZ /c
# ADD CPP /nologo /MDd /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_USRDLL" /D "_AFXDLL" /D "_MBCS" /FR"" /Fp".\Debug/ksnl.pch" /Yu"stdafx.h" /Fo".\Debug/" /Fd".\Debug/" /GZ " " /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:".\Debug\ksnl.pdb" /debug /machine:IX86 /out:"..\bin\ksnl.dll" /implib:".\Debug/ksnl.lib" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib drtplib.lib /nologo /subsystem:windows /dll /incremental:no /pdb:".\Debug\ksnl.pdb" /debug /machine:IX86 /out:"\\10.49.188.248\8900\dll\ksnl.dll" /implib:".\Debug/ksnl.lib" /pdbtype:sept /libpath:"Lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ksnl - Win32 Release"
# Name "ksnl - Win32 Debug"
# Name "ksnl - Win32 Remote Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CIniFile.cpp
DEP_CPP_CINIF=\
	".\CIniFile.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\DRTPHelper.cpp
DEP_CPP_DRTPH=\
	".\CPack.h"\
	".\drtperr.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\mytypes.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\EditEx.cpp
DEP_CPP_EDITE=\
	".\EditEx.h"\
	".\ksnl.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\FG_DIB.cpp
DEP_CPP_FG_DI=\
	".\FG_DIB.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\KSCardManager.cpp
DEP_CPP_KSCAR=\
	".\CPack.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\FG_DIB.h"\
	".\KSCardManager.h"\
	".\kscomdef.h"\
	".\KSConfig.h"\
	".\KSWorkflow.h"\
	".\mytypes.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\KSConfig.cpp
DEP_CPP_KSCON=\
	".\CIniFile.h"\
	".\CPack.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\FG_DIB.h"\
	".\KSCardManager.h"\
	".\kscomdef.h"\
	".\KSConfig.h"\
	".\ksnl.h"\
	".\KSWorkflow.h"\
	".\mytypes.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\KSInputDialog.cpp
DEP_CPP_KSINP=\
	".\CPack.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\EditEx.h"\
	".\FG_DIB.h"\
	".\KSCardManager.h"\
	".\kscomdef.h"\
	".\KSConfig.h"\
	".\KSInputDialog.h"\
	".\ksnl.h"\
	".\KSWorkflow.h"\
	".\mytypes.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=.\KSMsgDrawer.cpp
DEP_CPP_KSMSG=\
	".\KSMsgDrawer.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=ksnl.cpp
DEP_CPP_KSNL_=\
	".\CPack.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\FG_DIB.h"\
	".\KSCardManager.h"\
	".\kscomdef.h"\
	".\KSConfig.h"\
	".\KSMsgDrawer.h"\
	".\ksnl.h"\
	".\KSNLDlg.h"\
	".\KSWorkflow.h"\
	".\mytypes.h"\
	".\nl8900def.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ksnl - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "ksnl - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "ksnl - Win32 Remote Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=ksnl.def
# End Source File
# Begin Source File

SOURCE=ksnl.rc
# End Source File
# Begin Source File

SOURCE=.\KSNLDlg.cpp
DEP_CPP_KSNLD=\
	".\CPack.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\EditEx.h"\
	".\FG_DIB.h"\
	".\KSCardManager.h"\
	".\kscomdef.h"\
	".\KSConfig.h"\
	".\KSInputDialog.h"\
	".\KSMsgDrawer.h"\
	".\ksnl.h"\
	".\KSNLDlg.h"\
	".\ksutil.h"\
	".\KSWorkflow.h"\
	".\mytypes.h"\
	".\nl8900def.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=ksutil.cpp
DEP_CPP_KSUTI=\
	".\ksutil.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ksnl - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "ksnl - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "ksnl - Win32 Remote Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\KSWorkflow.cpp
DEP_CPP_KSWOR=\
	".\CPack.h"\
	".\DRTPHelper.h"\
	".\drtplib.h"\
	".\EditEx.h"\
	".\FG_DIB.h"\
	".\KSCardManager.h"\
	".\kscomdef.h"\
	".\KSConfig.h"\
	".\KSInputDialog.h"\
	".\KSMsgDrawer.h"\
	".\ksnl.h"\
	".\KSNLDlg.h"\
	".\KSWorkflow.h"\
	".\mytypes.h"\
	".\StdAfx.h"\
	
# End Source File
# Begin Source File

SOURCE=nl8900def.cpp
DEP_CPP_NL890=\
	".\nl8900def.h"\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ksnl - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yu"stdafx.h"

!ELSEIF  "$(CFG)" == "ksnl - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "ksnl - Win32 Remote Debug"

# ADD CPP /nologo /GX /Od /FR /Yu"stdafx.h" /GZ

!ENDIF 

# End Source File
# Begin Source File

SOURCE=StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ksnl - Win32 Release"

# ADD CPP /nologo /GX /O2 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "ksnl - Win32 Debug"

# ADD CPP /nologo /GX /Od /FR /Yc"stdafx.h" /GZ

!ELSEIF  "$(CFG)" == "ksnl - Win32 Remote Debug"

# ADD CPP /nologo /GX /Od /FR /Yc"stdafx.h" /GZ

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CIniFile.h
# End Source File
# Begin Source File

SOURCE=.\CPack.h
# End Source File
# Begin Source File

SOURCE=.\drtperr.h
# End Source File
# Begin Source File

SOURCE=.\DRTPHelper.h
# End Source File
# Begin Source File

SOURCE=.\EditEx.h
# End Source File
# Begin Source File

SOURCE=.\FG_DIB.h
# End Source File
# Begin Source File

SOURCE=.\KSCardManager.h
# End Source File
# Begin Source File

SOURCE=.\kscomdef.h
# End Source File
# Begin Source File

SOURCE=.\KSConfig.h
# End Source File
# Begin Source File

SOURCE=.\KSInputDialog.h
# End Source File
# Begin Source File

SOURCE=.\KSMsgDrawer.h
# End Source File
# Begin Source File

SOURCE=ksnl.h
# End Source File
# Begin Source File

SOURCE=KSNLDlg.h
# End Source File
# Begin Source File

SOURCE=ksutil.h
# End Source File
# Begin Source File

SOURCE=.\KSWorkflow.h
# End Source File
# Begin Source File

SOURCE=.\mytypes.h
# End Source File
# Begin Source File

SOURCE=nl8900def.h
# End Source File
# Begin Source File

SOURCE=Resource.h
# End Source File
# Begin Source File

SOURCE=StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=res\ksnl.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=ReadMe.txt
# End Source File
# End Target
# End Project
