/*

nsDialogs_createIPaddress.nsh
Header file for creating IP address input controls

Usage:
  ${NSD_CreateIPaddress} x y width height text
  ( text is ignored but included keep parity with the other ${NSD_Create*} commands

version info:
	1.1 - Major bugfix: the installer font could get corrupted when using this
          control.  This is a known issue with the SysIPAddress32 control.  The
          fix is simple but can't be applied completely within the nsDialogs
          framework.  Some manual replacement of the NSD_Create command is
          thus performed.

	1.0 - Initial version
*/

!ifndef NSDIALOGS_createIPaddress_INCLUDED
	!define NSDIALOGS_createIPaddress_INCLUDED
	!verbose push
	!verbose 3

	!ifndef ICC_INTERNET_CLASSES
		!define ICC_INTERNET_CLASSES 0x00000800
	!endif

	!include LogicLib.nsh
	!include WinMessages.nsh

	!define __NSD_IPaddress_CLASS SysIPAddress32
	!define __NSD_IPaddress_STYLE ${DEFAULT_STYLES}|${WS_TABSTOP}
	!define __NSD_IPaddress_EXSTYLE 0

	!insertmacro __NSD_DefineControl IPaddress
	!define NSD_CreateIPAddressControl "${NSD_CreateIPAddress}"
	!undef NSD_CreateIPAddress
	!macro NSD_CreateIPAddress x y w h label
		Push $0			; $0
		Push $1			; $1 $0
		${NSD_CreateIPAddressControl} ${x} ${y} ${w} ${h} "${label}"
						; hwnd $1 $0
		Pop $0			; $1 $0
  		CreateFont $R1 "$(^Font)" "$(^FontSize)"
  		SendMessage $0 ${WM_SETFONT} $R1 1
		Pop $1			; $0
		Exch $0			; hwnd
	!macroend
	!define NSD_CreateIPAddress `!insertmacro NSD_CreateIPAddress`

	!macro NSD_InitIPaddress
	    Push $0                 ; $0
	    Push $1                 ; $1 $0
		System::Alloc 400       ; memalloc $1 $0
		Pop $1                  ; $1 $0
		System::Call "*$1(i 8, i ${ICC_INTERNET_CLASSES})"
		System::Call 'comctl32::InitCommonControlsEx(i r1) i .r0'
		System::Free $1
		Pop $1                  ; $0
		Exch $0                 ; 1|0 (true|false)
	!macroend
	!define NSD_InitIPaddress '!insertmacro "NSD_InitIPaddress"'

	!verbose pop
!endif
