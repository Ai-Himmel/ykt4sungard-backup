// TestCardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "cpucard.h"
#include "MainFrm.h"
#include "InputPwd.h"
#include "TestCardDlg.h"
#include "kscard.h"
#include "MyCListCtrl.h"
#include <vector>
#include ".\testcarddlg.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
vector<ST_CARDTABLEINDEX>  g_VsCardInfo;
vector<ST_READCARDINFO>      g_VsReadCardInfo;
vector<ST_WRITECARDINFO>     g_VsWriteCardInfo;

/////////////////////////////////////////////////////////////////////////////
// CTestCardDlg dialog
IMPLEMENT_DYNCREATE(CTestCardDlg, CDialog)
ST_CARDTABLEINDEX   sCardTable;

void YCT_InitIndexTable()
{
	
	g_VsCardInfo.clear();
	memset(&sCardTable,0,sizeof sCardTable);
#if 1
	sCardTable.nIndexNo=CF_CARDNO ;strcpy(sCardTable.sIndexName,"���׿���");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SHOWCARDNO ;strcpy(sCardTable.sIndexName,"��ʾ����");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_FEETYPE ;strcpy(sCardTable.sIndexName,"��Ȩ�����");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SUBSIDYNO ;strcpy(sCardTable.sIndexName,"���������κ�");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDVERNO ;strcpy(sCardTable.sIndexName,"�������汾");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDSTATUS ;strcpy(sCardTable.sIndexName,"��״̬��־");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
#else
	sCardTable.nIndexNo=CF_CARDSTATUS ;strcpy(sCardTable.sIndexName,"��״̬��־");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);

#endif
#if 1
	sCardTable.nIndexNo=CF_STARTDATE ;strcpy(sCardTable.sIndexName,"��������");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_EXPIREDATE;strcpy(sCardTable.sIndexName,"��Ч����");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_PUBLISHID;strcpy(sCardTable.sIndexName,"���з���ʶ");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDSTRUCTVER;strcpy(sCardTable.sIndexName,"���ṹ�汾");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDTYPE;strcpy(sCardTable.sIndexName,"�����");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CUSTID;strcpy(sCardTable.sIndexName,"�ͻ���");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CUSTTYPE;strcpy(sCardTable.sIndexName,"�ͻ����");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_STUEMPNO;strcpy(sCardTable.sIndexName,"ѧ����");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_NAME;strcpy(sCardTable.sIndexName,"����");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SEX;strcpy(sCardTable.sIndexName,"�Ա�");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_DEPTCODE;strcpy(sCardTable.sIndexName,"���Ŵ���");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_IDTYPE;strcpy(sCardTable.sIndexName,"֤������");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_IDNO;strcpy(sCardTable.sIndexName,"֤������");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	//	sCardTable.nIndexNo=00;strcpy(sCardTable.sIndexName,"�����ļ�");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_BANKCARDNO;strcpy(sCardTable.sIndexName,"���п���");	g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_SINGLEMAXAMT;strcpy(sCardTable.sIndexName,"���������ѽ������");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_DAYMAXAMT;strcpy(sCardTable.sIndexName,"�����ۼ����ѽ������");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	//sCardTable.nIndexNo=34;strcpy(sCardTable.sIndexName,"�������ۼƶ�");		g_VsCardInfo.push_back(sCardTable);memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDCNT;strcpy(sCardTable.sIndexName,"������״���");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_LOCKCARDCNT;strcpy(sCardTable.sIndexName,"�������״���");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_TERMID;strcpy(sCardTable.sIndexName,"��������ն˺�");	g_VsCardInfo.push_back(sCardTable); memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_TRANSTYPE;strcpy(sCardTable.sIndexName,"�����������");	g_VsCardInfo.push_back(sCardTable); memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_TRANSDATE;strcpy(sCardTable.sIndexName,"�����������");g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_TRANSTIME;strcpy(sCardTable.sIndexName,"�������ʱ��");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_DPSCNT;strcpy(sCardTable.sIndexName,"����ֵ����");		g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_PAYCNT;strcpy(sCardTable.sIndexName,"�����Ѵ���");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDBAL;strcpy(sCardTable.sIndexName,"�����");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_CARDPWD;strcpy(sCardTable.sIndexName,"������");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_DAYSUMAMT;strcpy(sCardTable.sIndexName,"���ۼ����ѽ��");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
#endif
	sCardTable.nIndexNo=CF_LOCKTERMID;strcpy(sCardTable.sIndexName,"�����ն˺�");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_LOCKTRANSDATE;strcpy(sCardTable.sIndexName,"������������");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	sCardTable.nIndexNo=CF_LOCKTRANSTIME;strcpy(sCardTable.sIndexName,"��������ʱ��");			g_VsCardInfo.push_back(sCardTable);	memset(&sCardTable,0,sizeof sCardTable);
	// 	sCardTable.nIndexNo=41;strcpy(sCardTable.sIndexName,"�ۿ���");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	// 	sCardTable.nIndexNo=42;strcpy(sCardTable.sIndexName,"��ֵ���");	g_VsCardInfo.push_back(sCardTable);		memset(&sCardTable,0,sizeof sCardTable);
	// 	sCardTable.nIndexNo=43;strcpy(sCardTable.sIndexName,"�������");	g_VsCardInfo.push_back(sCardTable);
	return ;
}

CTestCardDlg::CTestCardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCardDlg::IDD, pParent)
	, m_nPort(0)
{
	//{{AFX_DATA_INIT(CTestCardDlg)
	m_sFieldVal = _T("");
	//}}AFX_DATA_INIT
}


void CTestCardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCardDlg)
	DDX_Control(pDX, IDC_EDIT_FIELDVAL, m_edtFieldVal);
	DDX_Control(pDX, IDC_CMB_FIELD, m_cbxField);
	DDX_Control(pDX, IDC_LIST_CMD, m_listCmd);
	DDX_Text(pDX, IDC_EDIT_FIELDVAL, m_sFieldVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestCardDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCardDlg)
	ON_BN_CLICKED(IDC_READBASEINFO, OnReadbaseinfo)
	ON_BN_CLICKED(IDC_BTN_SETREAD, OnBtnSetread)
	ON_BN_CLICKED(IDC_BTN_SETWRITE, OnBtnSetwrite)
	ON_BN_CLICKED(IDC_BTN_READ, OnBtnRead)
	ON_BN_CLICKED(IDC_BTN_WRITE, OnBtnWrite)
	ON_BN_CLICKED(IDC_BTN_CLEARALL, OnBtnClearall)
	ON_BN_CLICKED(IDC_BTN_REQUESTCARD, OnBtnRequestcard)
	ON_BN_CLICKED(IDC_BTN_GETKEY, OnBtnGetkey)
	ON_BN_CLICKED(IDC_BTN_ADDMONEY, OnBtnAddmoney)
	ON_BN_CLICKED(IDC_BTN_PAYMENT, OnBtnPayment)
	ON_BN_CLICKED(IDC_BTN_SETBALANCE, OnBtnSetbalance)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_READBALANCE, OnBnClickedBtnReadbalance)
	ON_BN_CLICKED(IDC_BTN_VERIFYPWD, OnBnClickedBtnVerifypwd)
	ON_BN_CLICKED(IDC_BTN_RESETPWD, OnBnClickedBtnResetpwd)
	ON_BN_CLICKED(IDC_BTN_CARDDTL, OnBnClickedBtnCarddtl)
	ON_BN_CLICKED(IDC_BTN_REVERSE, OnBnClickedBtnReverse)
	ON_BN_CLICKED(IDC_BTN_OPENPORT, OnBnClickedBtnOpenport)
//	ON_BN_CLICKED(IDC_BTN_REQUESTCARD2, OnBnClickedBtnRequestcard2)
ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
ON_BN_CLICKED(IDC_BTN_TEST, OnBnClickedBtnTest)
ON_BN_CLICKED(ID_BTN_INITPOSTPAID, OnBnClickedBtnInitpostpaid)
ON_BN_CLICKED(IDC_BTN_HALT, OnBnClickedBtnHalt)
ON_BN_CLICKED(IDC_BTN_SETM1KEY, OnBnClickedBtnSetm1key)
ON_BN_CLICKED(ID_BTN_CHECKWRITECARD, OnBnClickedBtnCheckwritecard)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCardDlg message handlers

void CTestCardDlg::OnReadbaseinfo() 
{
	int nRet=0;
	char sValue[128],sdata[128];
	
	memset(sdata,0,sizeof sdata);
	memset(sValue,0,sizeof sValue);
	if( (nRet=ks_readcard())!=0 )
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);		
		m_listCmd.InsertItem(m_nRow,sValue);
		sprintf(sValue,"����ʧ��,%X",nRet);
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		return ;
	}
	else
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);
		m_listCmd.InsertItem(m_nRow,sValue);
		strcpy(sValue,"�����ɹ�");
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		ks_beep();		
	}	
	for( int i=0; i<g_VsReadCardInfo.size();i++ )
	{
		memset(sdata,0,sizeof sdata);
		memset(sValue,0,sizeof sValue);
		if( (nRet=ks_getfieldval(g_VsReadCardInfo[i].nIndex,sdata))!=0 )
		{
			memset(sValue,0,sizeof sValue);
			sprintf(sValue,"%04ld",m_nRow+1);		
			m_listCmd.InsertItem(m_nRow,sValue);
			sprintf(sValue,"��ȡ��ȡ����Ϣʧ��,%X",nRet);
			m_listCmd.SetItemText(m_nRow++,1,sValue);
			return ;			
		}
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);		
		m_listCmd.InsertItem(m_nRow,sValue);
		sprintf(sValue,"%s=%s",g_VsReadCardInfo[i].sValues,sdata);
		m_listCmd.SetItemText(m_nRow++,1,sValue);
	}	
}

BOOL CTestCardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_nRow=0;
	m_listCmd.MyInit();
	m_listCmd.InsertColumn(0,"����",LVCFMT_LEFT,50);
	m_listCmd.InsertColumn(1,"����",LVCFMT_LEFT,500);
	m_listCmd.InsertColumn(2,"ע��",LVCFMT_LEFT,200);
	YCT_InitIndexTable();
	for( int i=0; i<g_VsCardInfo.size(); i++ )
	{
//		if( memcmp(g_VsCardInfo[i].sIndexName,"����",strlen("����"))) 
//		{
	//		char sMsg[256];
	//		memset(sMsg,0,sizeof sMsg);
	//		sprintf(sMsg,"%s                           %03ld",g_VsCardInfo[i].sIndexName,g_VsCardInfo[i].nIndexNo);
			m_cbxField.AddString(g_VsCardInfo[i].sIndexName);
//		}
	}
	m_cbxField.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTestCardDlg::OnBtnSetread() 
{
	int nField=0;
	char sdata[128];
	CString cs;
	ST_READCARDINFO      VsReadCardInfo;
	
	memset(&VsReadCardInfo,0x00,sizeof VsReadCardInfo);
	memset(sdata,0,sizeof sdata);	
	m_cbxField.GetWindowText(cs);

	for( int i=0; i<g_VsCardInfo.size(); i++ )
	{
		CString ss=g_VsCardInfo[i].sIndexName;
		if(cs== ss ) 
		{
			nField=g_VsCardInfo[i].nIndexNo;
			break;
		}
	}
	if(nField<1)
		return;
//	nField=atol(cs.GetBuffer(0)+cs.GetLength()-3);
	ks_setfieldreadmode(nField);
	ks_beep();
}

void CTestCardDlg::OnBtnSetwrite() 
{
//	if( !YCT_Auth() ) return ;
	
	UpdateData();
	int nMode=0,nField=0;
	char sdata[128];
	CString cs;
	ST_WRITECARDINFO      VsWriteCardInfo;
	memset(&VsWriteCardInfo,0x00,sizeof VsWriteCardInfo);
	memset(sdata,0,sizeof sdata);	
	m_cbxField.GetWindowText(cs);
	
//	nField=atol(cs.GetBuffer(0)+cs.GetLength()-3);
	for( int i=0; i<g_VsCardInfo.size(); i++ )
	{
		CString ss=g_VsCardInfo[i].sIndexName;
		if(cs== ss ) 
		{
			nField=g_VsCardInfo[i].nIndexNo;
			
			break;
		}
	}
	if(nField<1)
		return ;
	cs="";
	//	m_edtFieldVal.GetWindowText(cs);
	if(m_sFieldVal=="" ) 
	{
		MessageBox("������Ҫд������","��ʾ",MB_OK);
		m_edtFieldVal.SetFocus();
		return ;
	}
	VsWriteCardInfo.nIndex=nField;
	strcpy((char*)VsWriteCardInfo.sValues,m_sFieldVal);
	strcpy(sdata,m_sFieldVal.GetBuffer(0));
	ks_setfieldwritemode(nField);
	ks_setfieldval(nField,(const char*)m_sFieldVal);
	ks_beep();
}

void CTestCardDlg::OnBtnRead() 
{
	int nRet=0;
	char sValue[1024],sdata[1024];
	
	memset(sdata,0,sizeof sdata);
	memset(sValue,0,sizeof sValue);
	if( (nRet=ks_readcard())!=0 )
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);		
		m_listCmd.InsertItem(m_nRow,sValue);
		sprintf(sValue,"����ʧ��,%s",ks_geterrmsg(NULL));
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		return ;
	}
	CString cs;
	int nField=0;
	m_cbxField.GetWindowText(cs);
	for( int i=0; i<g_VsCardInfo.size(); i++ )
	{
		CString ss=g_VsCardInfo[i].sIndexName;
		if(cs== ss ) 
		{
			nField=g_VsCardInfo[i].nIndexNo;
			break;
		}
	}
	if(nField<1)
		return;

	if( (nRet=ks_getfieldval(nField,sdata))!=0 )
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);		
		m_listCmd.InsertItem(m_nRow,sValue);
		sprintf(sValue,ks_geterrmsg(NULL));
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		return ;			
	}
	else
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);
		m_listCmd.InsertItem(m_nRow,sValue);
		strcpy(sValue,"�����ɹ�");
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		ks_beep();		
	}	
	m_listCmd.InsertItem(m_nRow,sValue);
	sprintf(sValue,"%s",sdata);
	m_listCmd.SetItemText(m_nRow++,1,sValue);
}

void CTestCardDlg::OnBtnWrite() 
{
//	if( !YCT_Auth() ) return ;
	
	int nRet=0;
	char sValue[1024];
	char sCardPhyID[17]={0};
	if(ks_reset(10)!=0)
	{
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	/*
	if( ks_card(sCardPhyID)!=0 )
	{
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	*/

	memset(sValue,0,sizeof sValue);
	if( (nRet=ks_writecard(sCardPhyID))!=0 )
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);		
		m_listCmd.InsertItem(m_nRow,sValue);
		sprintf(sValue,"д��ʧ��,%s",ks_geterrmsg(NULL));
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		return ;
	}
	else
	{
		memset(sValue,0,sizeof sValue);
		sprintf(sValue,"%04ld",m_nRow+1);
		m_listCmd.InsertItem(m_nRow,sValue);
		strcpy(sValue,"д���ɹ�");
		m_listCmd.SetItemText(m_nRow++,1,sValue);
		ks_beep();
		ks_clearallfieldwritemode();
		g_VsWriteCardInfo.clear();
	}	
}

void CTestCardDlg::OnBtnClearall() 
{
	// TODO: Add your control notification handler code here
	ks_clearallfieldallmode();
}

void CTestCardDlg::OnBtnRequestcard() 
{
	char sSerialNo[30],sValue[40];
	unsigned long _Snr=0;
	char sCardPhyID[17];
	memset(sValue,   0,sizeof sValue);
	memset(sSerialNo,0,sizeof sSerialNo);
	for(int i=0;i<1000;i++)
	{
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox(ks_geterrmsg(NULL));
			return ;
		}
		sprintf(sValue,"%04ld",m_nRow+1);	
		m_listCmd.InsertItem(m_nRow,sValue);	
		memset(sValue,   0,sizeof sValue);
		//sprintf(sSerialNo,"%.8X",_Snr);
		sprintf(sValue,"No.%d:������%s",i,sCardPhyID);	
		//m_listCmd.SetItemText(m_nRow++,1,sValue);	
		m_listCmd.SetItemText(m_nRow,1,sValue);	
		Sleep(500);
		break;
	}
}

void CTestCardDlg::OnBtnGetkey() 
{
	CMainFrame* pMainFrame=(CMainFrame*)AfxGetMainWnd();	
	char sKeyCardPin[7]={0};
	CInputPwd dlg;
	if(dlg.DoModal()!=IDOK)
	{
		return;
	}
	strcpy(sKeyCardPin,dlg.m_sKeyCardPwd);
	
	CString cs;
	int nRet=0;
	char sMsg[128];
	unsigned long _Snr;
	byte rlen=0,rBuff[256];
	unsigned char sSendData[256];
	unsigned char nSendDatalen=0;
	unsigned char sRespData[256];
	unsigned char nRespDatalen=0;
	char sCardPhyID[17];

	_Snr=0;
	memset(rBuff,0,sizeof rBuff);
	memset(sSendData,0,sizeof sSendData);
	memset(sRespData,0,sizeof sRespData);
	rlen=0;
	nRet=ks_card(sCardPhyID);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("����Կ��ʧ��,�����Կ��");
		return ;
	}
	memset(&CardMainKey,0,sizeof(CardMainKey));
	Sleep(100);
	nRet=ks_loadcardkeys(sKeyCardPin);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("װ����Կʧ��");
		return ;
	}
	ks_beep();
	((CMainFrame*)AfxGetMainWnd())->ShowLog("����Կ�ɹ�");

}

void CTestCardDlg::OnBtnAddmoney() 
{
	int nRet=0;
	char sCardNo[20]="";
	ST_TRANSPACK deposit;
	unsigned long snr;
	//char sCardPhyID[9];
	memset(&deposit,0,sizeof deposit);

	if( ks_card(deposit.sCardPhyID)!=0 )
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("δ������");
		return ;
	}
	// TODO: Add your control notification handler code here
	ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc);
	ks_clearallfieldallmode();
	//ks_setfieldreadmode(CF_CARDNO);
	ks_setfieldreadmode(CF_DPSCNT);
	ks_setfieldreadmode(CF_CARDBAL);
	
	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	//memset(sCardNo,0,sizeof sCardNo);
	//ks_getfieldval(CF_CARDNO,sCardNo);
	//deposit.nCardNo = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_DPSCNT,sCardNo);
	deposit.nDpsCardCnt = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDBAL,sCardNo);
	deposit.nBefBalance = atoi(sCardNo);


	//deposit.sTermno = 1234;
	deposit.nFundType = 1;
	deposit.nTransAmt = this->GetDlgItemInt(ID_PAYMONEY); // 50 Ԫ
	strcpy(deposit.sOperCode,"1001");

	nRet = ks_deposit(&deposit,0);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��ֵ�ɹ�");
	ks_beep();
}

void CTestCardDlg::OnBtnPayment() 
{
	// TODO: Add your control notification handler code here
	int nRet=0;
	char sCardNo[20]="";
	ST_TRANSPACK payment;
	unsigned long snr;
	//char sCardPhyID[9];
	memset(&payment,0,sizeof payment);
	if( ks_card(payment.sCardPhyID)!=0 )
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("δ������");
		return ;
	}
	// TODO: Add your control notification handler code here
	ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc);
	ks_clearallfieldallmode();
	ks_setfieldreadmode(CF_CARDNO);
	ks_setfieldreadmode(CF_PAYCNT);
	ks_setfieldreadmode(CF_CARDBAL);

	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDNO,sCardNo);
	payment.nCardNo = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_PAYCNT,sCardNo);
	payment.nPayCardCnt = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDBAL,sCardNo);
	payment.nBefBalance = atoi(sCardNo);


	//deposit.sTermno = 1234;
	payment.nFundType = 0;
	payment.nTransAmt = this->GetDlgItemInt(ID_PAYMONEY); //1 Ԫ
	
	strcpy(payment.sOperCode,"1000");
	payment.nPayCode=3000;
	nRet = ks_payment(&payment,0);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("�ۿ�ɹ�");	
	unsigned char sMac[5]={0};
	unsigned char sTac[5]={0};
	nRet=ks_gettransprove(2,payment.nPayCardCnt+1);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	ks_beep();
}

void CTestCardDlg::OnBtnSetbalance() 
{
	// TODO: Add your control notification handler code here
	int nRet=0;
	char sCardNo[20]="";
	ST_TRANSPACK payment;
	unsigned long snr;
	//char sCardPhyID[9];
	memset(&payment,0,sizeof payment);

	if( ks_card(payment.sCardPhyID)!=0 )
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("δ������");
		return ;
	}
	// TODO: Add your control notification handler code here
	ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc);
	ks_clearallfieldallmode();
	ks_setfieldreadmode(CF_CARDNO);
	ks_setfieldreadmode(CF_DPSCNT);
	ks_setfieldreadmode(CF_PAYCNT);
	ks_setfieldreadmode(CF_CARDBAL);

	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDNO,sCardNo);
	payment.nCardNo = atoi(sCardNo);
	
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_DPSCNT,sCardNo);
	payment.nDpsCardCnt = atoi(sCardNo);
	
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_PAYCNT,sCardNo);
	payment.nPayCardCnt = atoi(sCardNo);

	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDBAL,sCardNo);
	payment.nBefBalance = atoi(sCardNo);
	payment.nAftBalance = 20000;
	strcpy(payment.sTransDate,"20090515");
	strcpy(payment.sTransTime,"122531");
	//payment.nFundType = 1;
	payment.nTransAmt = 100; //1 Ԫ
	strcpy(payment.sOperCode,"1000");
	nRet=ks_setcardbal(&payment);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	ks_beep();
}

void CTestCardDlg::OnBnClickedBtnReadbalance()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTestCardDlg::OnBnClickedBtnVerifypwd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ks_beeperr();
	/*
	int nRet;
	char sCardPhyID[17]={0};
	if( ks_card(sCardPhyID)!=0 )
	{
		AfxMessageBox("Ѱ��ʧ��");
		return ;
	}
	int iIsPass=0;
	nRet=ks_verifypasswd(sCardPhyID,"123123",iIsPass);
	if(nRet)
	{
		return ;
	}
	if(iIsPass)
	{
		AfxMessageBox("����У��ͨ��");
		ks_beep();
	}
	*/
}

void CTestCardDlg::OnBnClickedBtnResetpwd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRet;
	char sCardPhyID[17]={0};
	if( ks_card(sCardPhyID)!=0 )
	{
		AfxMessageBox("Ѱ��ʧ��");
		return ;
	}
	ks_clearallfieldallmode();
	nRet=ks_resetpasswd(sCardPhyID,"123123");
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("��������ɹ�");
	ks_beep();
}

void CTestCardDlg::OnBnClickedBtnCarddtl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRet;
	char sCardPhyID[17]={0};
	if( ks_card(sCardPhyID)!=0 )
	{
		AfxMessageBox("Ѱ��ʧ��");
		return ;
	}
	ST_PAYDTL  paydtl;
	static int recordno=1;
	int ret=ks_readpaydtl(recordno,&paydtl);
	if(ret)
	{
		AfxMessageBox("readpaydtl");
		return ;
	}
}

void CTestCardDlg::OnBnClickedBtnReverse()
{
	// TODO: Add your control notification handler code here
	int nRet=0;
	char sCardNo[20]="";
	ST_TRANSPACK payment;
	unsigned long snr;
	memset(&payment,0,sizeof payment);
	if( ks_card(payment.sCardPhyID)!=0 )
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("δ������");
		return ;
	}
	// TODO: Add your control notification handler code here
	ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc);
	ks_clearallfieldallmode();
	ks_setfieldreadmode(CF_CARDNO);
	ks_setfieldreadmode(CF_DPSCNT);
	ks_setfieldreadmode(CF_CARDBAL);

	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDNO,sCardNo);
	payment.nCardNo = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_DPSCNT,sCardNo);
	payment.nPayCardCnt = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDBAL,sCardNo);
	payment.nBefBalance = atoi(sCardNo);

	//deposit.sTermno = 1234;
	payment.nFundType = 0;
	payment.nTransAmt = 100; //1 Ԫ
	strcpy(payment.sOperCode,"1000");
	payment.nPayCode=3000;
	nRet = ks_pay_reverse(&payment,1);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("�����ɹ�");	
	ks_beep();
}
void CTestCardDlg::OnBnClickedBtnOpenport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	int ret=0;
	ret=ks_openport(m_nPort+1,9600);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	ks_beep();
}

//void CTestCardDlg::OnBnClickedBtnRequestcard2()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}

void CTestCardDlg::OnBnClickedButton1()
{
	char phyno[17];
	int ret;

	ret = ks_card(phyno);
	if(ret)
	{
		AfxMessageBox("��ſ�Ƭ");
		return ;
	}
	ret = ks_external_auth(phyno);
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
		return ;
	}
	((CMainFrame*)AfxGetMainWnd())->ShowLog("�ⲿ��֤�ɹ�");	
	ks_beep();
}

void CTestCardDlg::OnBnClickedBtnTest()
{
	char phyno[17]={0};
	int ret;

	ret = ks_card(phyno);
	if(ret)
	{
		AfxMessageBox("��ſ�Ƭ");
		return ;
	}
	ret=ks_verifypin("000000");
	if(ret)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
	}
	//ks_beep();
}

void CTestCardDlg::OnBnClickedBtnInitpostpaid()
{
	int nRet;
	char phyno[20] = {0};
	char sCardNo[100] = {0};
	ST_TRANSPACK payment;

	nRet = ks_card(phyno);
	if(nRet)
	{
		AfxMessageBox("��ſ�Ƭ");
		return ;
	}
	memset(&payment,0,sizeof payment);
	strcpy(payment.sCardPhyID,phyno);

	ks_comminit(g_config.m_svrip,g_config.m_svrport,g_config.m_mainfunc);
	ks_clearallfieldallmode();
	ks_setfieldreadmode(CF_CARDNO);
	ks_setfieldreadmode(CF_PAYCNT);
	ks_setfieldreadmode(CF_CARDBAL);

	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		return;
	}
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDNO,sCardNo);
	payment.nCardNo = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_PAYCNT,sCardNo);
	payment.nPayCardCnt = atoi(sCardNo);
	memset(sCardNo,0,sizeof sCardNo);
	ks_getfieldval(CF_CARDBAL,sCardNo);
	payment.nBefBalance = atoi(sCardNo);


	//deposit.sTermno = 1234;
	payment.nFundType = 0;
	payment.nTransAmt = 100; //1 Ԫ
	//strcpy(payment.sOperCode,"1000");
	payment.nTermID = 21;
	payment.nPayCode=3000;
	
	
	nRet=ks_init_postpaid(&payment,1);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));	
		AfxMessageBox(ks_geterrmsg(NULL));
		return;
	}
	ks_beep();
}

void CTestCardDlg::OnBnClickedBtnGetprove4dps()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CTestCardDlg::OnBnClickedBtnHalt()
{
	int nRet = ks_halt();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("���߿�ʧ��");	
		return;
	}
	ks_beep();
}

void CTestCardDlg::OnBnClickedBtnSetm1key()
{
	int nRet;
	CString key;
	this->GetDlgItemText(ID_EDT_M1KEY,key);
	if(key.GetLength() != 16)
	{
		AfxMessageBox("��Կ���Ȳ���ȷ");
		return;
	}
	nRet = ks_setmifare1key((LPCTSTR)key);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog("����M1����Կʧ��");	
		return;
	}
	ks_beep();
}

typedef struct
{
	int fieldID;
	const char *fieldval;
	const char *fieldName;
}USERINFO;
#define DEFINFO(id,val) {id,val,#id}

void CTestCardDlg::OnBnClickedBtnCheckwritecard()
{
	int nRet,i;
	char szCardPhyId[24]={0};
	CString errMsg;
	char val[256] = {0},temp[1024] = {0};
	nRet = ks_card(szCardPhyId);
	if(nRet)
	{
		AfxMessageBox("����ÿ�Ƭ");
		return;
	}
	USERINFO checkinfo[] =
	{
		DEFINFO(CF_CARDNO,"1234"),
		DEFINFO(CF_SHOWCARDNO,"100005"),
		DEFINFO(CF_FEETYPE,"12"),
		DEFINFO(CF_SUBSIDYNO,"5"),
		DEFINFO(CF_CARDVERNO,"100920000015"),
		DEFINFO(CF_CARDSTATUS,"1"),
		DEFINFO(CF_STARTDATE,"20100101"),
		DEFINFO(CF_EXPIREDATE,"20110101"),
		DEFINFO(CF_CARDTYPE,"1"),
		DEFINFO(CF_APPTYPE,"2"),
		DEFINFO(CF_SCHOOLCODE,"010"),
		DEFINFO(CF_CUSTID,"4321"),
		DEFINFO(CF_CUSTTYPE,"13"),
		DEFINFO(CF_STUEMPNO,"201009200000001234"),
		DEFINFO(CF_NAME,"����̫��"),
		DEFINFO(CF_SEX,"1"),
		DEFINFO(CF_DEPTCODE,"010001"),
		DEFINFO(CF_IDNO,"111111111111111111"),
		DEFINFO(CF_IDTYPE,"5"),
		DEFINFO(CF_BANKCARDNO,"6353210394855"),
		DEFINFO(CF_LOCKCARDCNT,"6"),
		DEFINFO(CF_DAYMAXAMT,"5000"),
		DEFINFO(CF_SINGLEMAXAMT,"1000"),
		DEFINFO(CF_CARDPWD,"888888"),
	};
	/*
	for(i = 0;i < sizeof(checkinfo)/sizeof(checkinfo[0]); ++i)
	{
		ks_setfieldreadmode(checkinfo[i].fieldID);
	}
	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		AfxMessageBox("����ʧ��");
		return;
	}
	*/
	for(i = 0;i < sizeof(checkinfo)/sizeof(checkinfo[0]); ++i)
	{
		ks_setfieldwritemode(checkinfo[i].fieldID);
		ks_setfieldval(checkinfo[i].fieldID,checkinfo[i].fieldval);
	}
	nRet = ks_writecard(szCardPhyId);
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		AfxMessageBox("д��ʧ��");
		return;
	}
	for(i = 0;i < sizeof(checkinfo)/sizeof(checkinfo[0]); ++i)
	{
		ks_setfieldreadmode(checkinfo[i].fieldID);
	}
	
	nRet = ks_readcard();
	if(nRet)
	{
		((CMainFrame*)AfxGetMainWnd())->ShowLog(ks_geterrmsg(NULL));
		AfxMessageBox("����ʧ��");
		return;
	}

	for(i = 0;i < sizeof(checkinfo)/sizeof(checkinfo[0]); ++i)
	{
		memset(val,0,sizeof val);
		nRet = ks_getfieldval(checkinfo[i].fieldID,val);
		if(nRet)
		{
			sprintf(temp,"����[%s][%d]��֧��\n",checkinfo[i].fieldName,checkinfo[i].fieldID);
			errMsg += temp;
		}
		else
		{
			if(strcmp(val,checkinfo[i].fieldval))
			{
				sprintf(temp,"����[%s][%d],����[%s]ʵ��[%s]\n",checkinfo[i].fieldName,checkinfo[i].fieldID
					,checkinfo[i].fieldval,val);
				errMsg += temp;
			}
		}
	}
	if(errMsg.GetLength() > 0)
	{
		AfxMessageBox(errMsg);
		return;
	}
	ks_beep();
}
