; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTestCardDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "cpucard.h"
LastPage=0

ClassCount=15
Class1=CChildView
Class2=CCoolTabCtrl
Class3=CcpucardApp
Class4=CAboutDlg
Class5=CKeyCardDlg
Class6=CMainFrame
Class7=CMyDlg
Class8=CCoolBar
Class9=CSizingControlBar
Class10=CSCBMiniDockFrameWnd
Class11=CXTabCtrl

ResourceCount=8
Resource1=IDD_DIALOGBAR
Resource2=IDD_DIALOGBAR3
Resource3=IDD_DIALOGBAR2
Resource4=IDR_MAINFRAME
Class12=CUserCardDlg
Resource5=IDD_INPUTPWD
Class13=CInputPwd
Resource6=IDD_DIALOGBAR4
Class14=CTestCardDlg
Resource7=IDD_ABOUTBOX
Class15=CSupCardDlg
Resource8=IDD_DIALOGBAR5

[CLS:CChildView]
Type=0
BaseClass=CWnd
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp

[CLS:CCoolTabCtrl]
Type=0
BaseClass=CWnd
HeaderFile=CoolTabCtrl.h
ImplementationFile=CoolTabCtrl.cpp

[CLS:CcpucardApp]
Type=0
BaseClass=CWinApp
HeaderFile=cpucard.h
ImplementationFile=cpucard.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=cpucard.cpp
ImplementationFile=cpucard.cpp
LastObject=CAboutDlg

[CLS:CKeyCardDlg]
Type=0
BaseClass=CDialog
HeaderFile=keycarddlg.h
ImplementationFile=KeyCardDlg.cpp
LastObject=CKeyCardDlg

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CMyDlg]
Type=0
BaseClass=CDialog
HeaderFile=MyDlg.h
ImplementationFile=MyDlg.cpp
LastObject=CMyDlg
Filter=D
VirtualFilter=dWC

[CLS:CCoolBar]
Type=0
BaseClass=baseCCoolBar
HeaderFile=scbarg.h
ImplementationFile=scbarg.cpp

[CLS:CSizingControlBar]
Type=0
BaseClass=baseCSizingControlBar
HeaderFile=sizecbar.h
ImplementationFile=sizecbar.cpp

[CLS:CSCBMiniDockFrameWnd]
Type=0
BaseClass=baseCSCBMiniDockFrameWnd
HeaderFile=sizecbar.h
ImplementationFile=sizecbar.cpp

[CLS:CXTabCtrl]
Type=0
BaseClass=CTabCtrl
HeaderFile=XTabCtrl.h
ImplementationFile=XTabCtrl.cpp

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOGBAR]
Type=1
Class=CKeyCardDlg
ControlCount=20
Control1=IDC_EDIT_KEY1,edit,1350631552
Control2=IDC_EDIT_KEY2,edit,1350631552
Control3=IDC_EDIT_KEY3,edit,1350631552
Control4=IDC_EDIT_PWD,edit,1350631552
Control5=IDC_BTN_GENPRIMAYKEY,button,1342242816
Control6=IDC_PUBLISHKEYCARD,button,1342242816
Control7=IDC_RECYCLECARD,button,1342242816
Control8=IDC_STATIC,static,1342177294
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CHECK1,button,1342242819
Control11=IDC_CHECK2,button,1342242819
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_EDIT_PRIMAYKEY,edit,1350633600
Control18=IDC_STATIC,button,1342177287
Control19=IDC_RADIO1,button,1342177289
Control20=IDC_RADIO2,button,1342177289

[DLG:IDD_DIALOGBAR2]
Type=1
Class=CMyDlg
ControlCount=10
Control1=IDC_EDIT_TERMID,edit,1350639744
Control2=IDC_CMB_SAM,combobox,1344340226
Control3=IDC_EDIT_CMDSTR,edit,1350631552
Control4=IDC_BTN_READKEYCARD,button,1342242816
Control5=IDC_PUBLISHPSAMCARD,button,1342242816
Control6=IDC_BTN_RECYCLEPSAMCARD,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_BTN_PSAMRESET,button,1342242816
Control9=IDC_BTN_RUNAPDU,button,1342242816
Control10=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDM_OPENPORT
Command2=IDM_CLOSEPORT
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_APP_ABOUT
CommandCount=10

[DLG:IDD_DIALOGBAR3]
Type=1
Class=CUserCardDlg
ControlCount=8
Control1=IDC_EDIT_TERMID,edit,1350639744
Control2=IDC_SPIN1,msctls_updown32,1342177280
Control3=IDC_PUBLISHCARD,button,1342242816
Control4=IDC_BTN_RECYCLECARD,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT2,edit,1350631552
Control8=IDC_CHECK1,button,1342242819

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_SHOWLEFTBAR
Command2=ID_SHOWBOTTOMBAR
CommandCount=2

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[CLS:CUserCardDlg]
Type=0
HeaderFile=UserCardDlg.h
ImplementationFile=UserCardDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CUserCardDlg
VirtualFilter=dWC

[DLG:IDD_INPUTPWD]
Type=1
Class=CInputPwd
ControlCount=4
Control1=IDC_EDIT_PIN,edit,1350631584
Control2=IDOK,button,1342373889
Control3=IDCANCEL,button,1342242816
Control4=65535,static,1342177283

[CLS:CInputPwd]
Type=0
HeaderFile=InputPwd.h
ImplementationFile=InputPwd.cpp
BaseClass=CDialog
Filter=D
LastObject=CInputPwd
VirtualFilter=dWC

[DLG:IDD_DIALOGBAR4]
Type=1
Class=CTestCardDlg
ControlCount=16
Control1=IDC_BTN_READBALANCE,button,1342242816
Control2=IDC_BTN_ADDMONEY,button,1342242816
Control3=IDC_BTN_PAYMENT,button,1342242816
Control4=IDC_LIST_CMD,SysListView32,1350631427
Control5=IDC_CMB_FIELD,combobox,1344340226
Control6=IDC_STATIC,static,1342308352
Control7=IDC_BTN_SETREAD,button,1342242816
Control8=IDC_BTN_SETWRITE,button,1342242816
Control9=IDC_BTN_READ,button,1342242816
Control10=IDC_BTN_WRITE,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_FIELDVAL,edit,1350631552
Control13=IDC_BTN_CLEARALL,button,1342242816
Control14=IDC_BTN_REQUESTCARD,button,1342242816
Control15=IDC_BTN_GETKEY,button,1342242816
Control16=IDC_BTN_SETBALANCE,button,1342242816

[CLS:CTestCardDlg]
Type=0
HeaderFile=TestCardDlg.h
ImplementationFile=TestCardDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CTestCardDlg
VirtualFilter=dWC

[DLG:IDD_DIALOGBAR5]
Type=1
Class=CSupCardDlg
ControlCount=6
Control1=IDC_CMB_SAM,combobox,1344340226
Control2=IDC_BTN_READKEYCARD,button,1342242816
Control3=IDC_PUBLISHSUPERCARD,button,1342242816
Control4=IDC_BTN_RECYCLESUPERCARD,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_BTN_PSAMRESET,button,1342242816

[CLS:CSupCardDlg]
Type=0
HeaderFile=SupCardDlg.h
ImplementationFile=SupCardDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSupCardDlg

