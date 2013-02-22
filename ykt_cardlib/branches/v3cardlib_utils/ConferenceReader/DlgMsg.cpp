// DlgMsg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "DlgMsg.h"
#include ".\dlgmsg.h"


// CDlgMsg 对话框

IMPLEMENT_DYNAMIC(CDlgMsg, CDialog)
CDlgMsg::CDlgMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMsg::IDD, pParent)
{
}

CDlgMsg::~CDlgMsg()
{
}

void CDlgMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMsg, CDialog)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDlgMsg 消息处理程序

void CDlgMsg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	OnDestroy();
	CDialog::OnClose();
	delete this;
}

void CDlgMsg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
}

void CDlgMsg::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialog::PostNcDestroy();
}
