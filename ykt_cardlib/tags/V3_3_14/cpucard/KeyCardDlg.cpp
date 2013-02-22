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
		AfxMessageBox("密钥1长度不足8位");
		GetDlgItem(IDC_EDIT_KEY1)->SetFocus();
		return;
	}
	// TODO: Add your control notification handler code here
	if(m_sKey2.GetLength()<8)
	{
		AfxMessageBox("密钥2长度不足8位");
		GetDlgItem(IDC_EDIT_KEY2)->SetFocus();
		return;
	}
	// TODO: Add your control notification handler code here
	if(m_sKey3.GetLength()<8)
	{
		AfxMessageBox("密钥3长度不足8位");
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
		//右8字节取反
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
		((CMainFrame*)AfxGetMainWnd())->ShowLog("请先创建主密钥");
		return;
	}
	UpdateData();
	int ret=0;
	if(m_sPwd.GetLength()!=6)
	{
		AfxMessageBox("保护密码长度不足6位");
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
		((CMainFrame*)AfxGetMainWnd())->ShowLog("发行密钥卡失败");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("密钥卡发行成功,请妥善保管本卡");
}

void CKeyCardDlg::OnRecyclecard() 
{
	if(ks_recyclekeycard()==0)
	{
		//AfxMessageBox("Recycle Key Card OK");
		ks_beep();
		((CMainFrame*)AfxGetMainWnd())->ShowLog("回收卡成功");
	}	
	else
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("回收卡失败");
	}
}

void CKeyCardDlg::OnBnClickedBtnClonecard()
{
	if(ks_checkloadclonekeys()!=1)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("请放已发行的密钥卡");
		char sKeyCardPin[7]={0};
		CInputPwd dlg("请输入已发行的密钥卡的6位保护密码");
		if(dlg.DoModal()!=IDOK)
		{
			return;
		}
		strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
		int ret=ks_loadkeys4clone(sKeyCardPin);
		if(ret)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
			((CMainFrame*)AfxGetMainWnd())->ShowLog("装载密钥卡失败");
			return ;
		}
		if(ks_checkloadclonekeys()!=1)
		{
			((CMainFrame*)AfxGetMainWnd())->ShowLog("装载克隆密钥失败");
			return ;
		}
		ks_beep();	
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("装载克隆密钥成功");
	char sKeyCardPin[7]={0};
	CInputPwd dlg("请输入要克隆的新密钥卡的6位保护密码");
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	int ret=ks_clonekeycard(sKeyCardPin);
	if(ret)
	{
		AfxMessageBox(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("克隆失败");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("克隆成功,请记住保护密码");
}

void CKeyCardDlg::OnBnClickedBtnSavekeys()
{
	((CMainFrame*)AfxGetMainWnd())->ShowLog("请放密钥卡");
	char sKeyCardPin[7]={0};
	CInputPwd dlg("请输入已发行密钥卡的6位保护密码");
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	int ret=ks_loadcardkeys(sKeyCardPin);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("装载密钥失败");
		return ;
	}
	if(ks_checkloadkeys()!=1)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("装载密钥失败");
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("装载密钥成功");
	if(ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc)!=0)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		AfxMessageBox(ks_geterrmsg(NULL));
		return;
	}
	if(ks_savekeys()!=0)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("密钥保存失败");
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("密钥保存成功");
}
