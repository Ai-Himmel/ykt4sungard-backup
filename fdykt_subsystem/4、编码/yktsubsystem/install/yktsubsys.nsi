; һ��ͨ��װ����ű�
; Author ���� 
; Date : 2005-4-28
; $Id: yktsubsys.nsi 22 2005-08-29 09:23:04Z cheng.tang $

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"

;--------------------------------
;Configuration

  ;General
  
  ; the followings are used for debugging
  ; end debugging
  
  !define MUI_PRODUCT "������ѧУ԰һ��ͨ����ϵͳ"
  !define SHORT_NAME "һ��ͨ��ϵͳ"
  !define PRO_VER_NUM "v1.00"
  
  ; ����
  !define MUI_VERSION "${PRO_VER_NUM}"
  !define VER_BUILD "${PRO_VER_NUM}"

  Name "${MUI_PRODUCT} ${MUI_VERSION}"
  
  !define COMPANY_SITE "http://www.kingstargroup.com"
  !define COMPANY_MAIL "info@kingstargroup.com"
  !define COMPANY_PHONE "021-38954588"
  !define COMPANY_NAME "�Ϻ��������˴��������޹�˾"
  
  !define DELPHI_BIN_PATH "C:\Program Files\Borland\Delphi\Bin"
  !define DELPHI_PATH "C:\Program Files\Borland\Delphi"
  !define SYSTEM32_PATH "c:\windows\system32"
  !define EXE_FILE "yktsubsystem.exe"
  
  !define PRO_ROOT_KEY "Software\KINGSTAR SOFTWARE\YKT"
  !define PRO_UNIT_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\YKT"
  
  OutFile "һ��ͨ��ϵͳ.exe"
  XPStyle on

  ;Folder selection page
  InstallDir "$PROGRAMFILES\KINGSTAR\yktsubsys"
  
  ;Get install folder from registry if available
  InstallDirRegKey HKCU "${PRO_ROOT_KEY}\AppPath" ""
  ; ��־��Ϣ
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
;  MessageBox MB_ICONQUESTION|MB_YESNO "�Ѿ���װ�˸ó����Ƿ񸲸ǣ�" IDNO user_abort
;  StrCpy $INSTDIR $0
;  
;donnot_inst:
;
;	Return
;
;user_abort:
;	MessageBox MB_OK "��л����ʹ�ã�"
;	Abort "��л����ʹ�ã�"
;	
FunctionEnd

;--------------------------------
;Installer Sections

; all version could install apps.
Section "Ӧ�ó���" SecClient
	SectionIn RO
	SetDetailsPrint textonly
  	DetailPrint "��װӦ�ó���..."
  	SetDetailsPrint listonly
  
	SetOutPath "$INSTDIR"
	SetOverwrite on
	File ..\Release\*.exe
	; ��װ VC7 Runtime libraries
	File ..\runtime\*71.dll
	SetOverwrite off
	File ..\yktsys.ini
	SetOutPath "$INSTDIR\plugin"
	SetOutPath "$INSTDIR\logs"
  
SectionEnd

Section "���Գ���" SectTest
	SetDetailsPrint textonly
	DetailPrint "��װ���Գ���..."
	SetDetailsPrint listonly
	
	SetOutPath "$INSTDIR\test"
	SetOverwrite on
	File ..\test\*.py
	SetOverwrite off
	File ..\test\*.xml
	
SectionEnd

Section -SecConf

  SetOutPath $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  
  ;Set shortcut
  SetDetailsPrint textonly
  DetailPrint "������ݷ�ʽ..."
  SetDetailsPrint listonly

	;SetOutPath "$SMPROGRAMS\${MUI_PRODUCT}"
	SetOutPath "$INSTDIR"
	
	CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${SHORT_NAME}.lnk" "$INSTDIR\${EXE_FILE}" "" "$INSTDIR\${EXE_FILE}"
	CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\ж��.lnk" "$INSTDIR\unintall.exe" "" "$INSTDIR\unintall.exe"
	
	;SetOutPath "$DESKTOP"
	CreateShortCut "$DESKTOP\${SHORT_NAME}.lnk" "$INSTDIR\${EXE_FILE}" "" "$INSTDIR\${EXE_FILE}"
	
	SetDetailsPrint textonly
  ;ExecWait "$INSTDIR\bin\vehicle_conf.exe"
  
SectionEnd


;--------------------------------
;Descriptions

  ;USE A LANGSTRING IF YOU WANT A DESCRIPTION TO BE LANGUAGE SPECIFIC

  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  	!insertmacro MUI_DESCRIPTION_TEXT ${SecClient} "${SHORT_NAME}������"
  	!insertmacro MUI_DESCRIPTION_TEXT ${SectTest} "���Խű�"
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
