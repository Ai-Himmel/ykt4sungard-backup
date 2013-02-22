// ksinterface_demo.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "ksinterface_demo.h"
#include "ksinterface_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(Load_Dll);
DEF_DLLFUNC(Load_WorkKey);
DEF_DLLFUNC(ReadSerial);
DEF_DLLFUNC(ReadBalance);


DEF_DLLFUNC(QueryBalance);
DEF_DLLFUNC(CashIncrease);


// Cksinterface_demoApp

BEGIN_MESSAGE_MAP(Cksinterface_demoApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cksinterface_demoApp 构造

Cksinterface_demoApp::Cksinterface_demoApp():m_interface_(NULL)
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 Cksinterface_demoApp 对象

Cksinterface_demoApp theApp;


// Cksinterface_demoApp 初始化

BOOL Cksinterface_demoApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControls()。否则，将无法创建窗口。
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	if(load_dll()!=0)
	{
		return FALSE;
	}
	Cksinterface_demoDlg dlg;
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

int Cksinterface_demoApp::load_dll()
{
	if(m_interface_ != NULL)
		return 0;
	m_interface_ = LoadLibrary("ksinterface.dll");
	if(m_interface_ == NULL)
	{
		AfxMessageBox(_T("加载ksinterface.dll失败"));
		return -1;
	}
	LOAD_DLLFUNC(m_interface_,ConnectMF);
	LOAD_DLLFUNC(m_interface_,CloseMF);
	LOAD_DLLFUNC(m_interface_,Load_Dll);
	LOAD_DLLFUNC(m_interface_,Load_WorkKey);
	LOAD_DLLFUNC(m_interface_,ReadSerial);
	LOAD_DLLFUNC(m_interface_,ReadBalance);
	LOAD_DLLFUNC(m_interface_,QueryBalance);
	LOAD_DLLFUNC(m_interface_,CashIncrease);
	if(Load_Dll())
	{
		return -1;
	}
	return 0;
}