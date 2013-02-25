// SysSettingPage.cpp : implementation file
/** 
 * 模块名						外接子系统
 * 文件名						SysSettingPage.cpp
 * 文件实现功能					系统配置页类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: SysSettingPage.cpp 22 2005-08-29 09:23:04Z cheng.tang $
 */

#include "stdafx.h"
#include "yktsubsystem.h"
#include "SysSettingPage.h"
#include "FileDialogEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SysSettingPage

IMPLEMENT_DYNAMIC(CSysSettingPage, CBasePropPage)

CSysSettingPage::CSysSettingPage(CYktsubsystemDoc * pDoc)
:CBasePropPage(pDoc,CSysSettingPage::IDD)
{
}

CSysSettingPage::CSysSettingPage()
	:CBasePropPage(CSysSettingPage::IDD)
{
	//{{AFX_DATA_INIT(CSysSettingPage)
	m_plugin_name = _T("");
	//}}AFX_DATA_INIT
}

CSysSettingPage::~CSysSettingPage()
{
}

void CSysSettingPage::DoDataExchange(CDataExchange* pDX)
{
	CBasePropPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysSettingPage)
	DDX_Text(pDX, IDC_PLUGIN_NAME, m_plugin_name);
	//}}AFX_DATA_MAP
	
}

BEGIN_MESSAGE_MAP(CSysSettingPage, CBasePropPage)
	//{{AFX_MSG_MAP(CSysSettingPage)
	ON_BN_CLICKED(IDC_BTN_SEL_PLUGIN, OnBtnSelPlugin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SysSettingPage message handlers

void CSysSettingPage::OnBtnSelPlugin() 
{
	char * filter = "Dll Files(*.dll)|*.dll";
	//CFileDialog fd(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
	//	,filter);

	CFileDialogEx fd(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT
		,filter);
	if( fd.DoModal() == IDOK )
	{
		m_plugin_name = fd.GetFileName();
		CString path = fd.GetPathName();
		UpdateData(FALSE);
		if(!m_pDoc->StopListening())
		{
			AfxMessageBox("不能停止服务,加载插件失败!");
			return;
		}
		CPluginManage * manage = m_pDoc->GetPluginModule();
		manage->UnRegistePluginModule();
		if(manage->LoadPluginFromFile(path,TRUE) == 0)
		{
			AfxMessageBox("加载成功!");
		}
	}
}

void CSysSettingPage::OnOK()
{
	m_pDoc->UpdateAllViews(NULL);
}
