// VCKBASEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "KeyCardDlg.h"
#include "kscard.h"
#include "InputPwd.h"
#include "MainFrm.h"
#include "keycarddlg.h"
#include ".\keycarddlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKeyCardDlg dialog

IMPLEMENT_DYNCREATE(CKeyCardDlg, CDialog)

CKeyCardDlg::CKeyCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyCardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyCardDlg)
	m_sKey1 = _T("");
	m_sKey2 = _T("");
	m_sKey3 = _T("");
	m_sPwd = _T("");
	m_sMasterKey = _T("");
	bMaster=false;
	//}}AFX_DATA_INIT
}

void CKeyCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyCardDlg)
	DDX_Text(pDX, IDC_EDIT_KEY1, m_sKey1);
	DDV_MaxChars(pDX, m_sKey1, 8);
	DDX_Text(pDX, IDC_EDIT_KEY2, m_sKey2);
	DDV_MaxChars(pDX, m_sKey2, 8);
	DDX_Text(pDX, IDC_EDIT_KEY3, m_sKey3);
	DDV_MaxChars(pDX, m_sKey3, 8);
	DDX_Text(pDX, IDC_EDIT_PWD, m_sPwd);
	DDV_MaxChars(pDX, m_sPwd, 6);
	DDX_Text(pDX, IDC_EDIT_PRIMAYKEY, m_sMasterKey);
	DDV_MaxChars(pDX, m_sMasterKey, 32);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKeyCardDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyCardDlg)
	ON_BN_CLICKED(IDC_BTN_GENPRIMAYKEY, OnBtnGenprimaykey)
	ON_BN_CLICKED(IDC_PUBLISHKEYCARD, OnPublishkeycard)
	ON_BN_CLICKED(IDC_RECYCLECARD, OnRecyclecard)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_CLONECARD, OnBnClickedBtnClonecard)
	ON_BN_CLICKED(IDC_BTN_SAVEKEYS, OnBnClickedBtnSavekeys)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyCardDlg message handlers
BOOL CKeyCardDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		pMsg->wParam=VK_TAB;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CKeyCardDlg::OnBtnGenprimaykey() 
{
	UpdateData();
	bMaster=false;
	if(m_sKey1.GetLength()<8)
	{
		AfxMessageBox("��Կ1���Ȳ���8λ");
		GetDlgItem(IDC_EDIT_KEY1)->SetFocus();
		return;
	}
	// TODO: Add your control notification handler code here
	if(m_sKey2.GetLength()<8)
	{
		AfxMessageBox("��Կ2���Ȳ���8λ");
		GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
		return;
	}
	// TODO: Add your control notification handler code here
	if(m_sKey3.GetLength()<8)
	{
		AfxMessageBox("��Կ3���Ȳ���8λ");
		GetDlgItem(IDC_EDIT_KEY3)->SetFocus();
		return;
	}
	//ks_genkey(m_sKey1,m_sKey2,m_sKey3);
	memset(m_uMasterKeyBuf,0,sizeof(m_uMasterKeyBuf));
	m_sMasterKey="";
	int i=0;
	for(i=0;i<8;i++)
	{
		m_uMasterKeyBuf[i]=m_sKey1.GetAt(i);
		m_uMasterKeyBuf[i]^=m_sKey2.GetAt(i);
		m_uMasterKeyBuf[i]^=m_sKey3.GetAt(i);
		//��8�ֽ�ȡ��
		m_uMasterKeyBuf[i+8]=~m_uMasterKeyBuf[i];
	}
	for(i=0;i<16;i++)
	{
		char shex[3];
		sprintf(shex,"%02X",m_uMasterKeyBuf[i]);
		m_sMasterKey=m_sMasterKey+shex;
	}		
	bMaster=true;
	UpdateData(false);
}

void CKeyCardDlg::OnPublishkeycard() 
{
	// TODO: Add your control notification handler code here
	if(!bMaster)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���ȴ�������Կ");
		return;
	}
	UpdateData();
	int ret=0;
	if(m_sPwd.GetLength()!=6)
	{
		AfxMessageBox("�������볤�Ȳ���6λ");
		GetDlgItem(IDC_EDIT_PWD)->SetFocus();
		return;
	}
	ret=ks_publishkeycard(m_uMasterKeyBuf,m_sPwd.GetBuffer(6));
	if(ret)
	{
		char sMsg[256]="";
		ks_geterrmsg(sMsg);
		if(strlen(sMsg)<1)
		{
			sprintf(sMsg,"ks_publishkeycard ret=%d",ret);
		}
		((CMainFrame*)AfxGetMainWnd())->ShowLog(sMsg);
		((CMainFrame*)AfxGetMainWnd())->ShowLog("������Կ��ʧ��");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��Կ�����гɹ�,�����Ʊ��ܱ���");
}

void CKeyCardDlg::OnRecyclecard() 
{
	if(ks_recyclekeycard()==0)
	{
		//AfxMessageBox("Recycle Key Card OK");
		ks_beep();
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���տ��ɹ�");
	}	
	else
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���տ�ʧ��");
	}
}

void CKeyCardDlg::OnBnClickedBtnClonecard()
{
	if(ks_checkloadclonekeys()!=1)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("����ѷ��е���Կ��");
		char sKeyCardPin[7]={0};
		CInputPwd dlg("�������ѷ��е���Կ����6λ��������");
		if(dlg.DoModal()!=IDOK)
		{
			return;
		}
		strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
		int ret=ks_loadkeys4clone(sKeyCardPin);
		if(ret)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
			((CMainFrame*)AfxGetMainWnd())->ShowLog("װ����Կ��ʧ��");
			return ;
		}
		if(ks_checkloadclonekeys()!=1)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowLog("װ�ؿ�¡��Կʧ��");
			return ;
		}
		ks_beep();	
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("װ�ؿ�¡��Կ�ɹ�");
	char sKeyCardPin[7]={0};
	CInputPwd dlg("������Ҫ��¡������Կ����6λ��������");
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	int ret=ks_clonekeycard(sKeyCardPin);
	if(ret)
	{
		AfxMessageBox(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("��¡ʧ��");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��¡�ɹ�,���ס��������");
}

void CKeyCardDlg::OnBnClickedBtnSavekeys()
{
	((CMainFrame*)AfxGetMainWnd())->ShowLog("�����Կ��");
	char sKeyCardPin[7]={0};
	CInputPwd dlg("�������ѷ�����Կ����6λ��������");
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	int ret=ks_loadcardkeys(sKeyCardPin);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("װ����Կʧ��");
		return ;
	}
	if(ks_checkloadkeys()!=1)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("װ����Կʧ��");
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("װ����Կ�ɹ�");
	if(ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc)!=0)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		AfxMessageBox(ks_geterrmsg(NULL));
		return;
	}
	if(ks_savekeys()!=0)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("��Կ����ʧ��");
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��Կ����ɹ�");
}
