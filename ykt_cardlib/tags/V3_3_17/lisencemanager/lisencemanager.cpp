// lisencemanager.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "lisencemanager.h"
#include "lisencemanagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClisencemanagerApp

BEGIN_MESSAGE_MAP(ClisencemanagerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// ClisencemanagerApp 构造

ClisencemanagerApp::ClisencemanagerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 ClisencemanagerApp 对象

ClisencemanagerApp theApp;


// ClisencemanagerApp 初始化

BOOL ClisencemanagerApp::InitInstance()
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
	TCHAR app_path[1025];
	TCHAR *p;
	GetModuleFileName(NULL,app_path,sizeof(app_path)/sizeof(TCHAR)-1);
	p = _tcsrchr(app_path,'\\');
	if(p != NULL)
	{
		*p = 0;
	}
	m_apppath = app_path;
	ClisencemanagerDlg dlg;
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


void ConvertWCS2MBS(LPCTSTR input,DWORD inlen,char *output,DWORD &outlen)
{
#ifdef _UNICODE
	size_t t = 0;
	wcstombs_s(&t,output,outlen,input,outlen);
	outlen = t;
#else
	memcpy(output,input,inlen);
	outlen = inlen;
#endif
}
void ConvertMBS2WCS(const char *input,DWORD inlen,LPSTR output,DWORD &outlen)
{
#ifdef _UNICODE
	size_t t = 0;
	mbstowcs_s(&t,output,outlen,input,outlen);
	outlen = t;
#else
	memcpy(output,input,inlen);
	outlen = inlen;
#endif
}