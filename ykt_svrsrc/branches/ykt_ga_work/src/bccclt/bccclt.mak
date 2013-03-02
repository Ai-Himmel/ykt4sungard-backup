# Microsoft Developer Studio Generated NMAKE File, Based on bccclt.dsp
!IF "$(CFG)" == ""
CFG=bccclt - Win32 Debug
!MESSAGE No configuration specified. Defaulting to bccclt - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "bccclt - Win32 Release" && "$(CFG)" != "bccclt - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bccclt.mak" CFG="bccclt - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "bccclt - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "bccclt - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "bccclt - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\bccclt.dll"


CLEAN :
	-@erase "$(INTDIR)\bccclt.obj"
	-@erase "$(INTDIR)\DRTPRouter.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\mypub.obj"
	-@erase "$(INTDIR)\PackHandle.obj"
	-@erase "$(INTDIR)\tcp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XPack.obj"
	-@erase "$(INTDIR)\XPData.obj"
	-@erase "$(OUTDIR)\bccclt.dll"
	-@erase "$(OUTDIR)\bccclt.exp"
	-@erase "$(OUTDIR)\bccclt.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BCCCLT_EXPORTS" /D "PACKC_EXPORTS" /D "BUPUB_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bccclt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib drtplib.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\bccclt.pdb" /machine:I386 /out:"$(OUTDIR)\bccclt.dll" /implib:"$(OUTDIR)\bccclt.lib" /libpath:"../lib" 
LINK32_OBJS= \
	"$(INTDIR)\bccclt.obj" \
	"$(INTDIR)\DRTPRouter.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\mypub.obj" \
	"$(INTDIR)\PackHandle.obj" \
	"$(INTDIR)\tcp.obj" \
	"$(INTDIR)\XPack.obj" \
	"$(INTDIR)\XPData.obj"

"$(OUTDIR)\bccclt.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "bccclt - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\bccclt.dll"


CLEAN :
	-@erase "$(INTDIR)\bccclt.obj"
	-@erase "$(INTDIR)\DRTPRouter.obj"
	-@erase "$(INTDIR)\mutex.obj"
	-@erase "$(INTDIR)\mypub.obj"
	-@erase "$(INTDIR)\PackHandle.obj"
	-@erase "$(INTDIR)\tcp.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XPack.obj"
	-@erase "$(INTDIR)\XPData.obj"
	-@erase "$(OUTDIR)\bccclt.dll"
	-@erase "$(OUTDIR)\bccclt.exp"
	-@erase "$(OUTDIR)\bccclt.ilk"
	-@erase "$(OUTDIR)\bccclt.lib"
	-@erase "$(OUTDIR)\bccclt.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "BCCCLT_EXPORTS" /D "PACKC_EXPORTS" /D "BUPUB_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\bccclt.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib drtplib.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\bccclt.pdb" /debug /machine:I386 /out:"$(OUTDIR)\bccclt.dll" /implib:"$(OUTDIR)\bccclt.lib" /pdbtype:sept /libpath:"../lib" 
LINK32_OBJS= \
	"$(INTDIR)\bccclt.obj" \
	"$(INTDIR)\DRTPRouter.obj" \
	"$(INTDIR)\mutex.obj" \
	"$(INTDIR)\mypub.obj" \
	"$(INTDIR)\PackHandle.obj" \
	"$(INTDIR)\tcp.obj" \
	"$(INTDIR)\XPack.obj" \
	"$(INTDIR)\XPData.obj"

"$(OUTDIR)\bccclt.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("bccclt.dep")
!INCLUDE "bccclt.dep"
!ELSE 
!MESSAGE Warning: cannot find "bccclt.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "bccclt - Win32 Release" || "$(CFG)" == "bccclt - Win32 Debug"
SOURCE=.\bccclt.cpp

"$(INTDIR)\bccclt.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\DRTPRouter.cpp

"$(INTDIR)\DRTPRouter.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mutex.cpp

"$(INTDIR)\mutex.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\mypub.cpp

"$(INTDIR)\mypub.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\PackHandle.cpp

"$(INTDIR)\PackHandle.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\tcp.cpp

"$(INTDIR)\tcp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\XPack.cpp

"$(INTDIR)\XPack.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\XPData.cpp

"$(INTDIR)\XPData.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

