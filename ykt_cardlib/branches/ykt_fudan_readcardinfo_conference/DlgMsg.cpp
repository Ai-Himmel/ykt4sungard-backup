// DlgMsg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "DlgMsg.h"
#include ".\dlgmsg.h"


// CDlgMsg �Ի���

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


// CDlgMsg ��Ϣ�������

void CDlgMsg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	OnDestroy();
	CDialog::OnClose();
	delete this;
}

void CDlgMsg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}

void CDlgMsg::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
	CDialog::PostNcDestroy();
}
