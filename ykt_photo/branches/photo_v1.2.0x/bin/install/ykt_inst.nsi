; 一卡通升级程序脚本

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Configuration

  ;General
  
  ; the followings are used for debugging
  ; end debugging
  
  !define MUI_PRODUCT "校园一卡通管理中心"
  !define SHORT_NAME "拍照制卡系统"
  !define PRO_VER_NUM "v1.2"
  
  ; 定义
  !define MUI_VERSION "${PRO_VER_NUM}"
  !define VER_BUILD "${PRO_VER_NUM}"

  Name "${SHORT_NAME} ${MUI_VERSION}"
  
  !define COMPANY_SITE "http://www.sungard.com"
  !define COMPANY_MAIL "info@kingstargroup.com"
  !define COMPANY_PHONE "021-38954588"
  !define COMPANY_NAME "SunGard"
  
  !define DELPHI_BIN_PATH "C:\Program Files\Borland\Delphi\Bin"
  !define DELPHI_PATH "C:\Program Files\Borland\Delphi"
  !define SYSTEM32_PATH "c:\winnt\system32"
  !define EXE_FILE "Photo.exe"
  
  !define PRO_ROOT_KEY "Software\SUNGARD SOFTWARE\Photo"
  !define PRO_UNIT_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\Photo"
  
  !define /date NOW "%Y%m%d"
  OutFile "exec/photo_${VER_BUILD}_${NOW}.exe"
  XPStyle on

  ;Folder selection page
  InstallDir "$PROGRAMFILES\SUNGARD\PHOTO"
  
  ;Get install folder from registry if available
  InstallDirRegKey HKCU "${PRO_ROOT_KEY}\AppPath" ""
  ; 标志信息
  BrandingText "${COMPANY_NAME}"
  LicenseForceSelection checkbox

;--------------------------------
;Interface Settings
 
!define MUI_ICON "install.ico"
!define MUI_UNICON "uninstall.ico"
!define MUI_LICENSEPAGE_BGCOLOR /grey
!define MUI_ABORTWARNING

;--------------------------------
;Language Selection Dialog Settings

  !define MUI_LANGDLL_REGISTRY_ROOT "HKCU" 
  !define MUI_LANGDLL_REGISTRY_KEY "${PRO_ROOT_KEY}\Lang" 
  !define MUI_LANGDLL_REGISTRY_VALUENAME "Installer Language"

;--------------------------------
  ;Remember the installer language
  !insertmacro MUI_PAGE_WELCOME
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
  
  !insertmacro MUI_RESERVEFILE_LANGDLL

;--------------------------------
;Installer Functions

Function .onInit

  ReadRegStr $0 HKLM "${PRO_ROOT_KEY}" "AppPath"
  StrCmp $0 "" 0 +2
  	Goto donnot_inst
  MessageBox MB_ICONQUESTION|MB_YESNO "已经安装校园一卡通拍照管理系统，是否覆盖？" IDNO user_abort
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
Section "校园一卡通拍照管理系统" RunTimeEnvironment
  SetDetailsPrint textonly
  DetailPrint "校园一卡通拍照管理系统"
  SetDetailsPrint listonly
  
  SectionIn 1 2 3 4 RO
	SetOutPath "$INSTDIR\photo"
	SetOverwrite on
	;File ..\bin\*.bpl
	File ..\*.dll
	File ..\*.exe
	File ..\*.ini
	File ..\*.txt
	
	SetOutPath "$INSTDIR\photo\printset"
	SetOverwrite on
	
	File ..\printset\*.ini
	File ..\printset\*.txt
	File ..\printset\*.jpg
	
	SetOutPath $SYSDIR
	SetOverwrite ifdiff

SectionEnd
!endif ;NO_RUNTIM

; all version could install apps.
;Section "应用程序" SecClient
	;SetDetailsPrint textonly
  	;DetailPrint "安装应用程序..."
  	;SetDetailsPrint listonly
  
	;SetOutPath "$INSTDIR\configs"
	;SetOverwrite off
  	;File .\configs\*.mn
  	;File .\configs\*.mnt
  	
  	;SetOutPath "$INSTDIR\report"
  	;SetOverwrite on
  	;File "report\*.frf"
  	
;SectionEnd


Section -SecConf

  SetOutPath $INSTDIR

  WriteRegStr HKLM "${PRO_ROOT_KEY}" "AppPath" $INSTDIR
  WriteRegStr HKLM "${PRO_ROOT_KEY}" "VersionBuild" "${MUI_VERSION}"

  WriteRegExpandStr HKLM "${PRO_UNIT_KEY}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegExpandStr HKLM "${PRO_UNIT_KEY}" InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "${PRO_UNIT_KEY}" "DisplayName" "${MUI_PRODUCT}"
  WriteRegStr HKLM "${PRO_UNIT_KEY}" "DisplayIcon" "$INSTDIR\photo\${EXE_FILE},0"
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
	SetOutPath "$INSTDIR\photo"
	
	CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${SHORT_NAME}.lnk" "$INSTDIR\photo\${EXE_FILE}" "" "$INSTDIR\photo\${EXE_FILE}"
	;CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${SHORT_NAME}.lnk" "$INSTDIR\CustInfoQuery\${EXE_FILE}" "" "$INSTDIR\CustInfoQuery\${EXE_FILE}"
	
	;SetOutPath "$DESKTOP"
	CreateShortCut "$DESKTOP\${SHORT_NAME}.lnk" "$INSTDIR\photo\${EXE_FILE}" "" "$INSTDIR\photo\${EXE_FILE}"
	;CreateShortCut "$DESKTOP\${SHORT_NAME}.lnk" "$INSTDIR\CustInfoQuery\${EXE_FILE}" "" "$INSTDIR\CustInfoQuery\${EXE_FILE}"
	
	SetDetailsPrint textonly
  ;ExecWait "$INSTDIR\photo\vehicle_conf.exe"
  
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
  ;Delete "$INSTDIR\update.exe"
  ;Delete "$INSTDIR\update.ini"
  Delete "$DESKTOP\${SHORT_NAME}.lnk"

  RMDir /r "$INSTDIR\photo"
  ;RMDir /r "$INSTDIR\configs"
  ;RMDir /r "$INSTDIR\help"
  ;RMDir /r "$INSTDIR\report"
  ;RMDir /r "$INSTDIR\user"
  RMDir /r "$SMPROGRAMS\${MUI_PRODUCT}"

  DeleteRegKey HKLM "${PRO_UNIT_KEY}"
  DeleteRegKey HKLM "${PRO_ROOT_KEY}" 
  DeleteRegKey /ifempty HKLM "Software\KINGSTAR"
  
SectionEnd

;--------------------------------
;Uninstaller Functions

Function un.onInit

  !insertmacro MUI_UNGETLANGUAGE
  
FunctionEnd
