// yuchuandemo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "yuchuandemo.h"
#include "AllPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DEF_DLLFUNC(OpenCommAuto);
DEF_DLLFUNC(CloseComm);
DEF_DLLFUNC(JS_GET_RECORD);
DEF_DLLFUNC(JS_SET_Black_Version);
DEF_DLLFUNC(JS_SET_Black);
DEF_DLLFUNC(JS_GetNodeTime);
DEF_DLLFUNC(JS_SET_ONE_Black);
DEF_DLLFUNC(JS_GET_Black_Version);
DEF_DLLFUNC(JS_GET_APPOINTED_RECORD);
DEF_DLLFUNC(JS_SetNodeTime);
DEF_DLLFUNC(JS_GET_SYSTEM_INFO);
DEF_DLLFUNC(JS_SET_SYSTEM_INFO);
DEF_DLLFUNC(JS_SET_Address);
DEF_DLLFUNC(JS_UID_SET_Address);
DEF_DLLFUNC(JS_ShakeHand);
HANDLE g_comhandle;

// CyuchuandemoApp

BEGIN_MESSAGE_MAP(CyuchuandemoApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CyuchuandemoApp 构造

CyuchuandemoApp::CyuchuandemoApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CyuchuandemoApp 对象

CyuchuandemoApp theApp;


// CyuchuandemoApp 初始化

BOOL CyuchuandemoApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	//CWinApp::InitInstance();

	//AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	if(LoadAllDLL()!=0)
	{
		AfxMessageBox(_T("加载宇川DLL失败"));
		return FALSE;
	}
	//CyuchuandemoDlg dlg;
	CAllPropertySheet dlg(_T("SunGard一卡通-宇川Demo"));
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用“确定”来关闭
		//对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	// 而不是启动应用程序的消息泵。
	return FALSE;
}

int CyuchuandemoApp::LoadAllDLL()
{
	// 加载 DLL 动态库
	HMODULE h = NULL;
	if((h = LoadLibrary("YC_ISP.dll"))==NULL)
	{
		return -1;
	}
	LOAD_DLLFUNC(h,OpenCommAuto);
	LOAD_DLLFUNC(h,CloseComm);
	LOAD_DLLFUNC(h,JS_GET_RECORD);
	LOAD_DLLFUNC(h,JS_SET_Black_Version);
	LOAD_DLLFUNC(h,JS_SET_Black);
	LOAD_DLLFUNC(h,JS_GetNodeTime);
	LOAD_DLLFUNC(h,JS_SET_ONE_Black);
	LOAD_DLLFUNC(h,JS_GET_Black_Version);
	LOAD_DLLFUNC(h,JS_GET_APPOINTED_RECORD);
	LOAD_DLLFUNC(h,JS_SetNodeTime);
	LOAD_DLLFUNC(h,JS_GET_SYSTEM_INFO);
	LOAD_DLLFUNC(h,JS_SET_SYSTEM_INFO);
	LOAD_DLLFUNC(h,JS_SET_Address);
	LOAD_DLLFUNC(h,JS_UID_SET_Address);
	LOAD_DLLFUNC(h,JS_ShakeHand);

	return 0;
}
