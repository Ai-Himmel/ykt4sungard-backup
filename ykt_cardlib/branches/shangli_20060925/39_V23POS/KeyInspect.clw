; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CKeyInspectDlg
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "KeyInspect.h"

ClassCount=4
Class1=CKeyInspectApp
Class2=CKeyInspectDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=ComThread
Resource3=IDD_KEYINSPECT_DIALOG
Resource4=IDR_POPUP_MENU

[CLS:CKeyInspectApp]
Type=0
HeaderFile=KeyInspect.h
ImplementationFile=KeyInspect.cpp
Filter=N
LastObject=CKeyInspectApp

[CLS:CKeyInspectDlg]
Type=0
HeaderFile=KeyInspectDlg.h
ImplementationFile=KeyInspectDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_STATIC_BUADRATE

[CLS:CAboutDlg]
Type=0
HeaderFile=KeyInspectDlg.h
ImplementationFile=KeyInspectDlg.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=10
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC_COMPANYNAME,static,1342308480
Control3=IDOK,button,1342373889
Control4=IDC_STATIC_COMPANYADDRESS1,static,1342308352
Control5=IDC_STATIC_COMPANYADDRESS2,static,1342308352
Control6=IDC_STATIC_COMPANYPHONE,static,1342308352
Control7=IDC_STATIC_COMPANYFAX,static,1342308352
Control8=IDC_STATIC_EMAIL,static,1342308352
Control9=IDC_STATIC_NETADD,static,1342308352
Control10=IDC_STATIC_WWW,static,1342308352

[DLG:IDD_KEYINSPECT_DIALOG]
Type=1
Class=CKeyInspectDlg
ControlCount=16
Control1=IDOK,button,1073807361
Control2=IDCANCEL,button,1073807360
Control3=IDC_BUTTON_START,button,1342242816
Control4=IDC_STATIC_PAR,button,1342177287
Control5=IDC_STATIC_PORTNO,static,1342308865
Control6=IDC_COMBO_PORTNO,combobox,1344339970
Control7=IDC_STATIC_BUADRATE,static,1073873409
Control8=IDC_COMBO_BUADRATE,combobox,1075904514
Control9=IDC_BUTTON_PAUSE,button,1342242816
Control10=IDC_BUTTON_HIDE,button,1342242816
Control11=IDC_BUTTON_EXIT,button,1342242816
Control12=IDC_STATIC_NAME,static,1342308352
Control13=IDC_STATIC_COMPANY_WWW,static,1342308352
Control14=IDC_EDIT1,edit,1084293316
Control15=IDC_BUTTON1,button,1073807360
Control16=IDC_CHECK1,button,1342242819

[CLS:ComThread]
Type=0
HeaderFile=omThread.h
ImplementationFile=omThread.cpp
BaseClass=CWinThread
Filter=N
VirtualFilter=TC
LastObject=ComThread

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=IDI_SHOW
Command2=IDI_EXIT
CommandCount=2

