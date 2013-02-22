; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CNewCardThread
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ReadCardInfo.h"

ClassCount=4
Class1=CReadCardInfoApp
Class2=CReadCardInfoDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_READCARDINFO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=CNewCardThread
Resource4=IDR_POPUP_MENU

[CLS:CReadCardInfoApp]
Type=0
HeaderFile=ReadCardInfo.h
ImplementationFile=ReadCardInfo.cpp
Filter=N

[CLS:CReadCardInfoDlg]
Type=0
HeaderFile=ReadCardInfoDlg.h
ImplementationFile=ReadCardInfoDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CReadCardInfoDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ReadCardInfoDlg.h
ImplementationFile=ReadCardInfoDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_READCARDINFO_DIALOG]
Type=1
Class=CReadCardInfoDlg
ControlCount=13
Control1=ID_BTN_CONNECT,button,1342242817
Control2=ID_BTN_CONCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COM_PORT,combobox,1344340226
Control7=IDC_COM_BAUDRATE,combobox,1344340226
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,button,1342177287
Control10=ID_BTN_TEST,button,1342242817
Control11=ID_CANCEL,button,1342242817
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATUS,static,1342308352

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_MENUITEM_SHOW
Command2=ID_MENUITEM_CANCEL
CommandCount=2

[CLS:CNewCardThread]
Type=0
HeaderFile=NewCardThread.h
ImplementationFile=NewCardThread.cpp
BaseClass=CWinThread
Filter=N

