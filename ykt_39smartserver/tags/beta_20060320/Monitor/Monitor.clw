; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CGeneralPage
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Monitor.h"
LastPage=0

ClassCount=9
Class1=CMonitorApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=8
Resource1=IDD_DIALOG_CONFIG_INTERFACE
Resource2=IDR_MAINFRAME
Resource3=IDD_DIALOG_CONFIG_PLUSIN
Class2=CChildView
Class5=CConfigDlg
Resource4=IDD_DIALOG_MONITOR
Class6=CMonitorDlg
Resource5=IDR_MENU_TRAY
Resource6=IDD_DIALOG_CONFIG
Class7=CInterfacePage
Class8=CPlusInPage
Resource7=IDD_ABOUTBOX
Class9=CGeneralPage
Resource8=IDD_DIALOG_CONFIG_OPTION

[CLS:CMonitorApp]
Type=0
HeaderFile=Monitor.h
ImplementationFile=Monitor.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Monitor.cpp
ImplementationFile=Monitor.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_APP_EXIT
Command2=ID_EDIT_UNDO
Command3=ID_EDIT_CUT
Command4=ID_EDIT_COPY
Command5=ID_EDIT_PASTE
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
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

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
Command4=ID_FILE_PRINT
Command5=ID_APP_ABOUT
CommandCount=5

[MNU:IDR_MENU_TRAY]
Type=1
Class=?
Command1=IDM_TRAY_START
Command2=IDM_TRAY_STOP
Command3=IDM_TRAY_SERVERLOG
Command4=IDM_TRAY_INTERFACELOG
Command5=IDM_TRAY_SET
Command6=IDM_TRAY_ABOUT
Command7=IDM_TRAY_EXIT
CommandCount=7

[DLG:IDD_DIALOG_CONFIG]
Type=1
Class=CConfigDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_TAB_SMART,SysTabControl32,1342177280
Control4=IDC_STATIC,static,1342177294

[CLS:CConfigDlg]
Type=0
HeaderFile=ConfigDlg.h
ImplementationFile=ConfigDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CConfigDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_MONITOR]
Type=1
Class=CMonitorDlg
ControlCount=8
Control1=IDOK,button,1342242816
Control2=IDC_STATIC,button,1342177287
Control3=IDC_EDIT1,edit,1342244996
Control4=IDC_START,button,1342242816
Control5=IDC_STOP,button,1476460544
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC_STATUS,static,1342312960

[CLS:CMonitorDlg]
Type=0
HeaderFile=MonitorDlg.h
ImplementationFile=MonitorDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_STATUS

[DLG:IDD_DIALOG_CONFIG_PLUSIN]
Type=1
Class=CPlusInPage
ControlCount=15
Control1=IDC_LIST1,SysListView32,1350631424
Control2=IDC_BTN_PLUSNEW,button,1476460544
Control3=IDC_BTN_PLUSDEL,button,1476460544
Control4=IDC_BTN_PLUSSET,button,1476460544
Control5=IDC_EDIT_PLUSPATH,edit,1342244992
Control6=IDC_EDIT_PLUSTASK,edit,1342244992
Control7=IDC_EDIT_PLUSMACTYPE,edit,1342244992
Control8=IDC_EDIT_PLUSOTHER,edit,1344342148
Control9=IDC_STATIC,static,1342177283
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342181383
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_CONFIG_INTERFACE]
Type=1
Class=CInterfacePage
ControlCount=36
Control1=IDC_EDIT_TASK,edit,1350633600
Control2=IDC_BUTTON_TASK,button,1342242816
Control3=IDC_EDIT_IP,edit,1350631552
Control4=IDC_EDIT_PORT,edit,1350639744
Control5=IDC_EDIT_SERVER,edit,1350639744
Control6=IDC_EDIT_CHILDFUNC,edit,1350639744
Control7=IDC_EDIT_ENDCODE,edit,1350639744
Control8=IDC_EDIT_TICK,edit,1350639744
Control9=IDC_EDIT_NUMBER,edit,1350639744
Control10=IDC_EDIT_MONITORIP,edit,1484849280
Control11=IDC_EDIT_MONITORPORT,edit,1484857472
Control12=IDC_EDIT_MONITORNO,edit,1484857472
Control13=IDC_EDIT_MONITORCID,edit,1484857472
Control14=IDC_EDIT_MONITOREND,edit,1484857472
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342181383
Control18=IDC_STATIC,static,1342177283
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342181383
Control27=IDC_STATIC,static,1342177283
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342181383
Control31=IDC_STATIC,static,1342177283
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352

[CLS:CInterfacePage]
Type=0
HeaderFile=InterfacePage.h
ImplementationFile=InterfacePage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CInterfacePage

[CLS:CPlusInPage]
Type=0
HeaderFile=PlusInPage.h
ImplementationFile=PlusInPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPlusInPage

[DLG:IDD_DIALOG_CONFIG_OPTION]
Type=1
Class=CGeneralPage
ControlCount=16
Control1=IDC_CHECK_BOOT,button,1342242819
Control2=IDC_BUTTON1,button,1342242816
Control3=IDC_BUTTON2,button,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342181383
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342177283
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342181383
Control11=IDC_STATIC,static,1342177283
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342181383
Control14=IDC_STATIC,static,1342308352
Control15=IDC_COMBO_REG,combobox,1344339971
Control16=IDC_STATIC,static,1342177283

[CLS:CGeneralPage]
Type=0
HeaderFile=GeneralPage.h
ImplementationFile=GeneralPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO_REG

