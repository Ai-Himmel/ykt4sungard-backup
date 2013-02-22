// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "MyDlg.h"
#include "MainFrm.h"
#include "InputPwd.h"
#include "kscard_imp.h"
#include "des.h"
#include <vector>
#include ".\mydlg.h"
#include "global_func.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;
/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

IMPLEMENT_DYNCREATE(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	m_iSamNo =0;
	m_sCmdStr = _T("");
	m_sTermID = _T("");
	//}}AFX_DATA_INIT
	bGetKey=false;
}


void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_CMB_SAM, m_cbxSamNo);
	DDX_CBIndex(pDX, IDC_CMB_SAM, m_iSamNo);
	DDX_Text(pDX, IDC_EDIT_CMDSTR, m_sCmdStr);
	DDX_Text(pDX, IDC_EDIT_TERMID, m_sTermID);
	DDV_MaxChars(pDX, m_sTermID, 12);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_BN_CLICKED(IDC_BTN_READKEYCARD, OnBtnReadkeycard)
	ON_BN_CLICKED(IDC_PUBLISHPSAMCARD, OnPublishpsamcard)
	ON_BN_CLICKED(IDC_BTN_RECYCLEPSAMCARD, OnBtnRecyclepsamcard)
	ON_BN_CLICKED(IDC_BTN_PSAMRESET, OnBtnPsamreset)
	ON_BN_CLICKED(IDC_BTN_RUNAPDU, OnBtnRunapdu)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_READPSAMCARD, OnBnClickedBtnReadpsamcard)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CMyDlg::OnBtnReadkeycard() 
{
	// TODO: Add your control notification handler code here
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
	//if(ks_checkloadkeys())
	//{
	//	pMainFrame->ShowLog("密钥已装载");
	//	return ;
	//}
	char sKeyCardPin[7]={0};
	CInputPwd dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	int ret=ks_loadcardkeys(sKeyCardPin);
	if(ret)
	{
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	ks_beep();
/*	
	CString cs;
	int nRet=0;
	char sMsg[128];
	unsigned long _Snr;
	byte rlen=0,rBuff[256];
	unsigned char sSendData[256];
	unsigned char nSendDatalen=0;
	unsigned char sRespData[256];
	unsigned char nRespDatalen=0;
	char sCardPhyID[9];
	_Snr=0;
	memset(rBuff,0,sizeof rBuff);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	rlen=0;
	nRet=ks_card(sCardPhyID);
	if(nRet)
	{
		CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
		pMainFrame->ShowLog("读密钥卡失败,请放密钥卡");
		//		AfxMessageBox("读密钥卡失败,请放密钥卡");
		return ;
	}
	memset(&CardMainKey,0,sizeof(CardMainKey));
	Sleep(100);
	for( int i=1; i<10; i++ )
	{	
		memset(sMsg,0,sizeof sMsg);
		nRet=ks_getkey(i,sKeyCardPin,sMsg);
		if( nRet!=0 )
		{
			ks_geterrmsg(sMsg);
			pMainFrame->ShowLog(sMsg);
			//sprintf(sMsg,"KNG_Get_Key=%ld",nRet);
			//	MessageBox(sMsg,"error",MB_OK);			
			return;
		}
		if( i==1 ) memcpy(CardMainKey.DPK1,sMsg,16);
		if( i==2 ) memcpy(CardMainKey.DPK2,sMsg,16);
		if( i==3 ) memcpy(CardMainKey.DLK,sMsg,16);
		if( i==4 ) memcpy(CardMainKey.DTAC1,sMsg,16);
		if( i==5 ) memcpy(CardMainKey.DTAC2,sMsg,16);
		if( i==6 ) memcpy(CardMainKey.DUK,sMsg,16);
		if( i==7 ) memcpy(CardMainKey.DRPK,sMsg,16);
		if( i==8 ) memcpy(CardMainKey.DAMK,sMsg,16);
		if( i==9 ) memcpy(CardMainKey.DACK,sMsg,16);
		//APP_BcdToAsc((byte*)sMsg,16,(byte*)sMsg);	
	}
	bGetKey=true;
	ks_beep();
	pMainFrame->ShowLog("取密钥成功");
	*/
}
void CMyDlg::OnPublishpsamcard() 
{
	if(!ks_checkloadkeys())
	{
		AfxMessageBox("请先读密钥卡装入密钥");
		return ;
	}
	UpdateData();
	if(m_sTermID.GetLength()<1||m_sTermID=="0")
	{
		GetDlgItem(IDC_EDIT_TERMID)->SetFocus();
		AfxMessageBox("请设置终端编号");
		return ;
	}
	for(;m_sTermID.GetLength()<12;)
	{
		m_sTermID="0"+m_sTermID;
	}
	ST_PSAMCARD PSAMCard;
	memset(&PSAMCard,0,sizeof(PSAMCard));
	
	PSAMCard.nCardType=2;
	PSAMCard.nCardVer=1;
	strcpy(PSAMCard.sPublishID,"20");
	strcpy(PSAMCard.sUserID,"10");
	strcpy(PSAMCard.sCardNo,"1234567");
	strcpy(PSAMCard.sTermID,(LPCTSTR)m_sTermID);
	strcpy(PSAMCard.sStartDate,"20090101");
	strcpy(PSAMCard.sExpireDate,"20991231");

	int ret=ks_publishpsamcard(&PSAMCard);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		((CMainFrame*)AfxGetMainWnd())->ShowLog("发行SAM失败");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("发行SAM成功");

}

void CMyDlg::OnBtnRecyclepsamcard() 
{
	
	int ret=ks_recyclepsamcard();
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("回收PSAM卡成功");	

}

void CMyDlg::OnBtnPsamreset() 
{
	// TODO: Add your control notification handler code here

	int ret=0;
	UpdateData();
	BYTE rlen;
	BYTE rbuf[256];
	int SAMID=m_iSamNo+1;
	if(m_cbxSamNo.GetCurSel()==3)
		SAMID=0;
	ks_reset(2);
	ret=ks_setcpupara4sam(SAMID);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		return ;
	}

	ret=ks_cpureset4sam(&rlen,rbuf);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		return;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("SAM卡片复位OK");
}

BOOL CMyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cbxSamNo.SetCurSel(3);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDlg::OnBtnRunapdu() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	char *pstr=(char*)m_sCmdStr.GetBuffer(0);
	BYTE slen,rlen,apducmd[256],rbuf[256];
	char hex[256];
	int cmdlen;
	memset(apducmd,0,sizeof(apducmd));
	memset(rbuf,0,sizeof(rbuf));
	memset(hex,0,sizeof(hex));
	hex2dec(pstr,m_sCmdStr.GetLength(),apducmd,cmdlen);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(">"+m_sCmdStr);
	slen=cmdlen;
	int ret=ks_cpuapdu4sam(apducmd,slen,rbuf,rlen);
	if(ret)
	{
		char szMsg[256];
		sprintf(szMsg,"%s retcode=%x",pstr,ret);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(szMsg);
		return;
	}
	dec2hex(rbuf,rlen,hex);
	((CMainFrame*)AfxGetMainWnd())->ShowLog(CString("<")+hex);
	return;
}

void CMyDlg::OnBnClickedBtnReadpsamcard()
{
	// TODO: 在此添加控件通知处理程序代码
	ST_PSAMCARD PsamCard;
	
	memset(&PsamCard,0,sizeof(PsamCard));
	int nRet=0;
	nRet=ks_readpsamcard(&PsamCard);
	if(nRet)
	{
		AfxMessageBox("读PSAM卡失败");
		return;
	}
	ks_beep();
}

void CMyDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
