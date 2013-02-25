; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CYktsubsystemDoc
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "yktsubsystem.h"
LastPage=0

ClassCount=10
Class1=CBasePropPage
Class2=CFileDialogEx
Class3=CListenSocket
Class4=CMainFrame
Class5=CSysSettingPage
Class6=CYktsubsystemApp
Class7=CAboutDlg
Class8=CYktsubsystemDoc
Class9=CYktsubsystemView

ResourceCount=4
Resource1=IDR_POPUP
Resource2=IDR_MAINFRAME
Class10=CRequestSocket
Resource3=IDD_ABOUTBOX
Resource4=IDD_SETTING_PAGE

[CLS:CBasePropPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=BasePropPage.h
ImplementationFile=BasePropPage.cpp

[CLS:CFileDialogEx]
Type=0
BaseClass=CFileDialog
HeaderFile=FileDialogEx.h
ImplementationFile=FileDialogEx.cpp

[CLS:CListenSocket]
Type=0
BaseClass=CAsyncSocket
HeaderFile=ListenSocket.h
ImplementationFile=ListenSocket.cpp
Filter=N
VirtualFilter=q
LastObject=CListenSocket

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
LastObject=CMainFrame
Filter=T
VirtualFilter=fWC

[CLS:CSysSettingPage]
Type=0
BaseClass=CBasePropPage
HeaderFile=SysSettingPage.h
ImplementationFile=SysSettingPage.cpp

[CLS:CYktsubsystemApp]
Type=0
BaseClass=CWinApp
HeaderFile=yktsubsystem.h
ImplementationFile=yktsubsystem.cpp
LastObject=CYktsubsystemApp
Filter=N
VirtualFilter=AC

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=yktsubsystem.cpp
ImplementationFile=yktsubsystem.cpp
LastObject=CAboutDlg

[CLS:CYktsubsystemDoc]
Type=0
BaseClass=CDocument
HeaderFile=yktsubsystemDoc.h
ImplementationFile=yktsubsystemDoc.cpp
LastObject=ID_SERVER_CFG

[CLS:CYktsubsystemView]
Type=0
BaseClass=CListView
HeaderFile=yktsubsystemView.h
ImplementationFile=yktsubsystemView.cpp
LastObject=CYktsubsystemView

[DLG:IDD_DUMY_DLG]
Type=1
Class=CBasePropPage

[DLG:IDD_SETTING_PAGE]
Type=1
Class=CSysSettingPage
ControlCount=3
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PLUGIN_NAME,static,1350701056
Control3=IDC_BTN_SEL_PLUGIN,button,1342242816

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_MI_START_SVR
Command2=ID_MI_STOP_SVR
Command3=ID_APP_ABOUT
CommandCount=3

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_MI_START_SVR
Command2=ID_MI_STOP_SVR
Command3=ID_SVR_RESTART
Command4=ID_SERVER_CFG
Command5=ID_MI_CLOSE
Command6=ID_APP_ABOUT
CommandCount=6

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[CLS:CRequestSocket]
Type=0
HeaderFile=RequestSocket.h
ImplementationFile=RequestSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CRequestSocket
VirtualFilter=q

[MNU:IDR_POPUP]
Type=1
Class=?
Command1=ID_MI_START_SVR
Command2=ID_MI_STOP_SVR
Command3=ID_MI_SHOW
Command4=ID_MI_CLOSE
CommandCount=4

