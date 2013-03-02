; 一卡通安装程序脚本
; Author 汤成 
; Date : 2005-4-28
; $Id$

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Configuration

  ;General
  
  ; the followings are used for debugging
  ; end debugging
  
  !define MUI_PRODUCT "校园一卡通密钥生成程序"
  !define SHORT_NAME "密钥生成"
  !define PRO_VER_NUM "v1.00"
  
  ; 定义
  !define MUI_VERSION "${PRO_VER_NUM}"
  !define VER_BUILD "${PRO_VER_NUM}"

  Name "${MUI_PRODUCT} ${MUI_VERSION}"
  
  !define COMPANY_SITE "http://www.kingstargroup.com"
  !define COMPANY_MAIL "info@kingstargroup.com"
  !define COMPANY_PHONE "021-38954588"
  !define COMPANY_NAME "SunGard金仕达计算机有限公司"
  
  !define DELPHI_BIN_PATH "C:\Program Files\Borland\Delphi\Bin"
  !define DELPHI_PATH "C:\Program Files\Borland\Delphi"
  !define SYSTEM32_PATH "c:\windows\system32"
  !define EXE_FILE "SuperSecure.exe"
  
  !define PRO_ROOT_KEY "Software\KINGSTAR SOFTWARE\YKT"
  !define PRO_UNIT_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\YKT"
  
  OutFile "一卡通密钥生成程序.exe"
  XPStyle on

  ;Folder selection page
  InstallDir "$PROGRAMFILES\KINGSTAR\genkey"
  
  ;Get install folder from registry if available
  InstallDirRegKey HKCU "${PRO_ROOT_KEY}\AppPath" ""
  ; 标志信息
  BrandingText "${COMPANY_NAME}"
  LicenseForceSelection checkbox

;--------------------------------
;Interface Settings
 
;!define MUI_ICON "install.ico"
;!define MUI_UNICON "uninstall.ico"
;!define MUI_HEADERIMAGE "..\img\header.bmp"
!define MUI_LICENSEPAGE_BGCOLOR /grey
!define MUI_ABORTWARNING

;--------------------------------
;Language Selection Dialog Settings

  ;Remember the installer language
  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "${PRO_ROOT_KEY}\Lang" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

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
;  ReadRegStr $0 HKLM "${PRO_ROOT_KEY}" "AppPath"
;  StrCmp $0 "" 0 +2
;  	Goto donnot_inst
;  MessageBox MB_ICONQUESTION|MB_YESNO "已经安装了该程序，是否覆盖？" IDNO user_abort
;  StrCpy $INSTDIR $0
;  
;donnot_inst:
;
;	Return
;
;user_abort:
;	MessageBox MB_OK "感谢您的使用！"
;	Abort "感谢您的使用！"
;	
FunctionEnd

;--------------------------------
;Installer Sections

; all version could install apps.
Section "应用程序" SecClient
	SectionIn RO
	SetDetailsPrint textonly
  	DetailPrint "安装应用程序..."
  	SetDetailsPrint listonly
  
	SetOutPath "$INSTDIR"
	SetOverwrite on
	File ..\*.exe
	File ..\*.dll
;	File ..\*.bpl
	File ..\ExceptInfo.log
	SetOverwrite off
	File ..\SuperPassword.pwd
	File ..\config.ini
; File "${SYSTEM32_PATH}\msvcp60.dll"
  
SectionEnd


Section -SecConf

  SetOutPath $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  
  ;Set shortcut
  SetDetailsPrint textonly
  DetailPrint "创建快捷方式..."
  SetDetailsPrint listonly

	;SetOutPath "$SMPROGRAMS\${MUI_PRODUCT}"
	SetOutPath "$INSTDIR"
	
	CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${SHORT_NAME}.lnk" "$INSTDIR\${EXE_FILE}" "" "$INSTDIR\${EXE_FILE}"
	CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\卸载.lnk" "$INSTDIR\unintall.exe" "" "$INSTDIR\unintall.exe"
	
	;SetOutPath "$DESKTOP"
	CreateShortCut "$DESKTOP\${SHORT_NAME}.lnk" "$INSTDIR\${EXE_FILE}" "" "$INSTDIR\${EXE_FILE}"
	
	SetDetailsPrint textonly
  ;ExecWait "$INSTDIR\bin\vehicle_conf.exe"
  
SectionEnd


;--------------------------------
;Descriptions

  ;USE A LANGSTRING IF YOU WANT A DESCRIPTION TO BE LANGUAGE SPECIFIC

  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  	!insertmacro MUI_DESCRIPTION_TEXT ${SecClient} "${SHORT_NAME}主程序"
  !insertmacro MUI_FUNCTION_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section Uninstall

  ;ADD YOUR OWN STUFF HERE!

  Delete "$INSTDIR\Uninstall.exe"
  Delete "$DESKTOP\${SHORT_NAME}.lnk"
  RMDir /r "$INSTDIR"
  RMDir /r "$SMPROGRAMS\${MUI_PRODUCT}"

;  DeleteRegKey HKLM "${PRO_UNIT_KEY}"
;  DeleteRegKey HKLM "${PRO_ROOT_KEY}" 
;  DeleteRegKey /ifempty HKLM "Software\KINGSTAR"
  
SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd
