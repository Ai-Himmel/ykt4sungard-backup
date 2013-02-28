; 一卡通安装程序脚本

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Configuration

  ;General
  
  ; the followings are used for debugging
  ; end debugging
  
  !define MUI_PRODUCT "e卡通管理中心"
  !define SHORT_NAME "e卡通管理中心"
  !define PRO_VER_NUM "cpu_v3.0"
  
  ; 定义
  !define MUI_VERSION "${PRO_VER_NUM}"
  !define VER_BUILD "${PRO_VER_NUM}"

  Name "${MUI_PRODUCT} ${MUI_VERSION}"
  
  !define COMPANY_SITE "http://www.ekingstar.com/china"
  !define COMPANY_MAIL "info@sungard.com"
  !define COMPANY_PHONE "021-38954588"
  !define COMPANY_NAME "SunGard"
  
  !define DELPHI_BIN_PATH "C:\Program Files\Borland\Delphi\Bin"
  !define DELPHI_PATH "C:\Program Files\Borland\Delphi"
  !define SYSTEM32_PATH "c:\winnt\system32"
  !define EXE_FILE "KSClient50d.exe"
  
  !define PRO_ROOT_KEY "Software\KINGSTAR SOFTWARE\YKT"
  !define PRO_UNIT_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\YKT"
  
  !define /date NOW "%Y%m%d"
  OutFile "exec/ykt_trunk_${VER_BUILD}_${NOW}.exe"
  XPStyle on

  ;Folder selection page
  InstallDir "$PROGRAMFILES\SUNGARD\YKT"
  
  ;Get install folder from registry if available
  InstallDirRegKey HKCU "${PRO_ROOT_KEY}\AppPath" ""
  ; 标志信息
  BrandingText "${COMPANY_NAME}"
  LicenseForceSelection checkbox

;--------------------------------
;Interface Settings
 
!define MUI_ICON "install.ico"
!define MUI_UNICON "uninstall.ico"
;!define MUI_HEADERIMAGE "..\img\header.bmp"
!define MUI_LICENSEPAGE_BGCOLOR /grey
!define MUI_ABORTWARNING

;--------------------------------
;Language Selection Dialog Settings

  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "${PRO_ROOT_KEY}\Lang" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"
  
  ;!define MUI_PAGE_CUSTOMFUNCTION_show Pageshow

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_WELCOME
; !insertmacro MUI_PAGE_LICENSE "${NSISDIR}\Contrib\Modern UI\License.txt"
  ;!insertmacro MUI_PAGE_LICENSE "..\doc\License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES

;--------------------------------
;Languages

  ;!insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "SimpChinese"

;--------------------------------
;Reserve Files
  
  ;These files should be inserted before other files in the data block
  ;Keep these lines before any File command
  ;Only for BZIP2 (solid) compression
  !insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Installer Functions

Function .onInit

  ;!insertmacro MUI_LANGDLL_DISPLAY
  ReadRegStr $0 HKLM "${PRO_ROOT_KEY}" "AppPath"
  StrCmp $0 "" 0 +2
  	Goto donnot_inst
  MessageBox MB_ICONQUESTION|MB_YESNO "已经安装了该程序，是否覆盖？" IDNO user_abort
  StrCpy $INSTDIR $0
  
donnot_inst:

	Return

user_abort:
	MessageBox MB_OK "感谢您的使用！"
	Abort "感谢您的使用！"
	
FunctionEnd

;--------------------------------
;Installer Sections

!ifndef NO_RUNTIME
Section "运行环境（必须）" RunTimeEnvironment
  SetDetailsPrint textonly
  DetailPrint "安装运行环境..."
  SetDetailsPrint listonly
  
  SectionIn 1 2 3 4 RO
	SetOutPath "$INSTDIR\bin"
	SetOverwrite on
	File ..\bin\*.dll
	File ..\bin\*.bpl
	
	SetOutPath $SYSDIR
	SetOverwrite ifdiff

SectionEnd
!endif ;NO_RUNTIM

; all version could install apps.
Section "应用程序" SecClient
	SetDetailsPrint textonly
  	DetailPrint "安装应用程序..."
  	SetDetailsPrint listonly
  
	SetOutPath "$INSTDIR\bin"
	SetOverwrite on
	File ..\bin\KSClient50d.exe
	File ..\bin\SysFileMan50c.exe
	SetOverwrite on
	File ..\bin\*.ini
	File ..\bin\*.jpg
	File ..\bin\cpack.dat
	File ..\bin\pub.key
	File ..\bin\*.db3
	File ..\bin\license.lcs
	File ..\bin\Microsoft.VC90.CRT.manifest
	
	SetOutPath "$INSTDIR\bin\PATCHLOG"
		SetOverwrite on
  	File ..\bin\PATCHLOG\test.txt

	SetOutPath "$INSTDIR\bin\logs"
		SetOverwrite on
  	File ..\bin\logs\*.txt

	SetOutPath "$INSTDIR\configs"
	SetOverwrite off
  	File ..\configs\*.in
	SetOverwrite on
  	File ..\configs\*.ini
  	
	SetOutPath "$INSTDIR\configs"
	SetOverwrite on
  	File ..\configs\menus_CPU_std.mn
  	File ..\configs\mTitle.jpg
  	
	SetOutPath "$INSTDIR\skins"
	SetOverwrite on
  	File ..\skins\*.skn
	
  	SetOutPath "$INSTDIR\report"
  	SetOverwrite on
  	File "..\report\*.rmf"
	
  	SetOutPath "$INSTDIR\report\Account"
  	SetOverwrite on
	File "..\report\Account\*.rmf"
	
  	SetOutPath "$INSTDIR\report\RtnTicket"
  	SetOverwrite on
	File "..\report\RtnTicket\*.rmf"
  	
  	SetOutPath "$INSTDIR\importtemplet"
  	SetOverwrite on
  	File "..\importtemplet\*.xls"
  	
  	SetOutPath "$INSTDIR\user"
  	SetOverwrite on
  	File "..\user\*.ini"
  	
SectionEnd

Section -SecConf

  SetOutPath $INSTDIR

  WriteRegStr HKLM "${PRO_ROOT_KEY}" "AppPath" $INSTDIR
  WriteRegStr HKLM "${PRO_ROOT_KEY}" "VersionBuild" "${MUI_VERSION}"

  WriteRegExpandStr HKLM "${PRO_UNIT_KEY}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegExpandStr HKLM "${PRO_UNIT_KEY}" InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "${PRO_UNIT_KEY}" "DisplayName" "${MUI_PRODUCT}"
  WriteRegStr HKLM "${PRO_UNIT_KEY}" "DisplayIcon" "$INSTDIR\bin\${EXE_FILE},0"
  WriteRegStr HKLM "${PRO_UNIT_KEY}" "DisplayVersion" "${MUI_VERSION}"
  WriteRegStr HKLM "${PRO_UNIT_KEY}" "URLInfoAbout" "${COMPANY_SITE}"
  WriteRegDWORD HKLM "${PRO_UNIT_KEY}" "NoModify" "1"
  WriteRegDWORD HKLM "${PRO_UNIT_KEY}" "NoRepair" "1"
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  
  ;Set shortcut
  SetDetailsPrint textonly
  DetailPrint "创建快捷方式..."
  SetDetailsPrint listonly

	SetOutPath "$SMPROGRAMS\${MUI_PRODUCT}"
	SetOutPath "$INSTDIR\bin"
	
	CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${SHORT_NAME}.lnk" "$INSTDIR\bin\${EXE_FILE}" "" "$INSTDIR\bin\${EXE_FILE}"
	
	;SetOutPath "$DESKTOP"
	CreateShortCut "$DESKTOP\${SHORT_NAME}.lnk" "$INSTDIR\bin\${EXE_FILE}" "" "$INSTDIR\bin\${EXE_FILE}"
	
	SetDetailsPrint textonly
  ;ExecWait "$INSTDIR\bin\vehicle_conf.exe"
  
SectionEnd


;--------------------------------
;Descriptions

  ;USE A LANGSTRING IF YOU WANT A DESCRIPTION TO BE LANGUAGE SPECIFIC

  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  	!insertmacro MUI_DESCRIPTION_TEXT ${RunTimeEnvironment} "运行环境，必须安装"
  	!insertmacro MUI_DESCRIPTION_TEXT ${SecClient} "${SHORT_NAME}主程序"
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section Uninstall

  ;ADD YOUR OWN STUFF HERE!

  Delete "$INSTDIR\Uninstall.exe"
  Delete "$INSTDIR\update.exe"
  Delete "$INSTDIR\update.ini"
  Delete "$DESKTOP\${SHORT_NAME}.lnk"

  RMDir /r "$INSTDIR\bin"
  RMDir /r "$INSTDIR\configs"
  ;RMDir /r "$INSTDIR\help"
  ;RMDir /r "$INSTDIR\report"
  RMDir /r "$INSTDIR\importtemplet"
  RMDir /r "$INSTDIR\user"
  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\${MUI_PRODUCT}"

  DeleteRegKey HKLM "${PRO_UNIT_KEY}"
  DeleteRegKey HKLM "${PRO_ROOT_KEY}" 
  DeleteRegKey /ifempty HKLM "Software\KINGSTAR"
  
SectionEnd

Section
	WriteINIStr "..\configs\SetPara.ini" "debug" "ifdebug" "0"
	WriteINIStr "..\configs\SetPara.ini" "menu" "menu" "menus_CPU_std.mn"
	WriteINIStr "..\configs\SetPara.ini" "bj" "bjopen" "0"
	WriteINIStr "..\bin\kscard.ini" "INTERFACE" "LICENSE" ""
SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd
