// TestDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\KsCardInterFace\KsCardInterFace.h"
#include "KsCardInterFaceDemo.h"
#include "KsCardInterFaceDemoDlg.h"
#include<sstream>
#include ".\kscardinterfacedemodlg.h"
using namespace std;
#pragma comment(lib,"KsCardInterFace.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
static bool s_comopen=false;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKsCardInterFaceDemoDlg dialog

CKsCardInterFaceDemoDlg::CKsCardInterFaceDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKsCardInterFaceDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKsCardInterFaceDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKsCardInterFaceDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKsCardInterFaceDemoDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edit_Balance);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKsCardInterFaceDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CKsCardInterFaceDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BTN_COM, OnOpenCom)
//	ON_BN_CLICKED(ID_READ_BALANCE, OnReadBalance)
	ON_BN_CLICKED(ID_DEL_MONEY, OnDelMoney)
	ON_BN_CLICKED(ID_READ_CARDINFO, OnReadCardinfo)
	ON_BN_CLICKED(ID_MEND_MONEY, OnMendMoney)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(ID_LOGON_YKT, OnBnClickedLogonYkt)
//	ON_BN_CLICKED(ID_READ_YKTINFO, OnBnClickedReadYktinfo)
	ON_WM_CLOSE()
//	ON_BN_CLICKED(IDC_CheckDeposit, OnBnClickedCheckdeposit)
ON_BN_CLICKED(ID_LOGIN, OnBnClickedLogin)
ON_BN_CLICKED(IDC_BTN_READKEY, OnBnClickedBtnReadkey)
ON_BN_CLICKED(ID_LOGIN2, OnBnClickedLogin2)
ON_BN_CLICKED(ID_BTN_RECHANGE, OnBnClickedBtnRechange)
ON_CBN_SELCHANGE(IDC_COM_PORT, OnCbnSelchangeComPort)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKsCardInterFaceDemoDlg message handlers

BOOL CKsCardInterFaceDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	int ret=KS_Init();
	if(ret)
	{
		::AfxMessageBox("动态库初始化失败");
		return FALSE;		
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKsCardInterFaceDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKsCardInterFaceDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKsCardInterFaceDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKsCardInterFaceDemoDlg::OnOpenCom() 
{
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		KS_ClosePort();
		s_comopen = false;
		GetDlgItem(ID_BTN_COM)->SetWindowText("打开端口");
	}
	else
	{
		// baud设置参看文档
		if(KS_OpenPort(0,0))
		{
			AfxMessageBox("打开端口失败");
			return;
		}
		GetDlgItem(ID_BTN_COM)->SetWindowText("关闭端口");
		s_comopen = true;
	}
}

void CKsCardInterFaceDemoDlg::OnDelMoney() 
{
	int nRet;
	if (!s_comopen)
	{
		AfxMessageBox("串口未有打开");
		return;
	}
	CString sTransAmt;
	GetDlgItem(IDC_EDIT8)->GetWindowText(sTransAmt);
	if(sTransAmt=="")
	{
		AfxMessageBox("请输入扣款金额(单位:分)");
		GetDlgItem(IDC_EDIT8)->SetFocus();
		return;
	}
	char szCardPhyID[17]={0};
	nRet=KS_RequestCard(szCardPhyID);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	KS_Reset();
	KS_SetReadFieldName("CARDNO");		//交易卡号
	KS_SetReadFieldName("CARDBAL");		//卡余额
	KS_SetReadFieldName("PAYCNT");		//消费次数

	nRet=KS_ReadCard();
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	char fieldval[61]={0};
	KS_GetFieldVal("CARDNO",fieldval);		//交易卡号
	int cardno=atol(fieldval);
	KS_GetFieldVal("CARDBAL",fieldval);		//卡余额
	int cardbefbal=atol(fieldval);
	KS_GetFieldVal("PAYCNT",fieldval);		//消费次数
	int paycnt=atol(fieldval);
	char refno[20]={0};
	char mac[9]={0};
	nRet=KS_PayPrepare(szCardPhyID,cardno,cardbefbal,paycnt,atoi(sTransAmt),refno,mac);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	char GetProveFlag=0;
REPEAT:
	nRet=KS_CardBalanceDec(&GetProveFlag);
	if(nRet)
	{
		if(0 == GetProveFlag)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return;
		}
		////////////////////
		//中途拔卡处理
		AfxMessageBox("写卡失败,请重放卡");
		int FindCardFlag=0;
		int WaitStartTime=GetTickCount();
		//等待用户刷卡，超时时间10秒
		while(GetTickCount()-WaitStartTime<10*1000)
		{
			char sNewCardPhyID[17]={0};
			nRet=KS_RequestCard(sNewCardPhyID);
			if(nRet)
			{
				Sleep(50);
				continue;
			}
			if(strcmp(szCardPhyID,sNewCardPhyID)!=0)
			{
				AfxMessageBox("卡号错误,请刷原卡");
				continue;
			}
			FindCardFlag=1;
			break;
		}
		if(0==FindCardFlag)
		{
			//等待刷卡超时,写卡失败处理
			KS_UnProveProcess();
			AfxMessageBox("写卡失败,交易取消");
			return;
		}
		else
		{
			char cReWriteCardFlag=0;
			KS_GetProve(&cReWriteCardFlag);
			if(cReWriteCardFlag)
			{
				goto REPEAT;
			}
		}
	}
	nRet=KS_PayProcess();
	if(nRet)
	{
		AfxMessageBox("保存消费流水失败");	
		return;
	}
	KS_Beep();//读卡器轰鸣,提示成功
	char sCardAftBal[20];
	sprintf(sCardAftBal,"%d",cardbefbal-atoi(sTransAmt));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sCardAftBal);
	GetDlgItem(IDC_EDIT3)->SetWindowText(refno);
	GetDlgItem(IDC_EDIT7)->SetWindowText(mac);
}

void CKsCardInterFaceDemoDlg::OnReadCardinfo() 
{
	int ret = 0;
	// TODO: Add your control notification handler code here
	if (s_comopen)
	{
		char szCardPhyID[30]={0};
		ret=KS_RequestCard(szCardPhyID);
		if(ret)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return;
		}
		KS_Reset();
		KS_SetReadFieldName("EXPIREDATE");	//过期日期
		KS_SetReadFieldName("CARDNO");		//交易卡号
		KS_SetReadFieldName("SHOWCARDNO");	//显示卡号
		KS_SetReadFieldName("CARDTYPE");	//卡类别
		KS_SetReadFieldName("CUSTID");		//客户号
		KS_SetReadFieldName("CUSTTYPE");	//客户类别
		KS_SetReadFieldName("STUEMPNO");	//学号
		KS_SetReadFieldName("NAME");		//姓名
		KS_SetReadFieldName("SEX");			//性别
		KS_SetReadFieldName("DEPTCODE");	//部门代码
		KS_SetReadFieldName("IDNO");		//证件号码
		KS_SetReadFieldName("IDTYPE");		//证件类型
		KS_SetReadFieldName("CARDSTATUS");	//卡状态
		KS_SetReadFieldName("EXPIREDATE");	//过期日期
		KS_SetReadFieldName("FEETYPE");		//收费类别
		KS_SetReadFieldName("SUBSIDYNO");	//补助批次号
		KS_SetReadFieldName("CARDBAL");		//卡余额
		KS_SetReadFieldName("DPSCNT");		//充值次数
		KS_SetReadFieldName("PAYCNT");		//消费次数

		ret=KS_ReadCard();
		if(ret)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return ;
		}
		KS_Beep();
		stringstream ssInfo;
		char fieldval[61]={0};
		KS_GetFieldVal("CARDNO",fieldval);		//交易卡号
		int cardno = atoi(fieldval);
		ssInfo<<"交易卡号 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("SHOWCARDNO",fieldval);	//显示卡号
		ssInfo<<"显示卡号 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CARDTYPE",fieldval);	//卡类别
		ssInfo<<"卡类别 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CUSTID",fieldval);		//客户号
		ssInfo<<"客户号 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CUSTTYPE",fieldval);	//客户类别
		ssInfo<<"客户类别 "<<fieldval<<endl;
	
		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("STUEMPNO",fieldval);	//学工号
		ssInfo<<"学工号 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("NAME",fieldval);		//姓名
		ssInfo<<"姓名 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("SEX",fieldval);			//性别
		ssInfo<<"性别 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("DEPTCODE",fieldval);	//部门代码
		ssInfo<<"部门代码 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("IDNO",fieldval);		//证件号码
		ssInfo<<"证件号码 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("IDTYPE",fieldval);		//证件类型
		ssInfo<<"证件类型 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CARDSTATUS",fieldval);	//卡状态
		ssInfo<<"卡状态 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("EXPIREDATE",fieldval);	//过期日期
		ssInfo<<"过期日期 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("FEETYPE",fieldval);		//收费类别
		ssInfo<<"收费类别 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("SUBSIDYNO",fieldval);	//补助批次号
		ssInfo<<"补助批次号 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("CARDBAL",fieldval);		//卡余额
		ssInfo<<"卡余额 "<<fieldval<<endl;
		GetDlgItem(IDC_EDIT1)->SetWindowText(fieldval);

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("DPSCNT",fieldval);		//充值次数
		ssInfo<<"充值次数 "<<fieldval<<endl;

		memset(fieldval,0,sizeof fieldval);
		KS_GetFieldVal("PAYCNT",fieldval);		//消费次数
		ssInfo<<"消费次数 "<<fieldval<<endl;

		MessageBox(ssInfo.str().c_str());
		char statuscode=0;
		char szStatusInfo[256];
		ret=KS_GetCardStatus(cardno,&statuscode,szStatusInfo);
		if(ret)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return ;
		}
		if(statuscode!=0)
		{
			AfxMessageBox(szStatusInfo);
			return ;
		}
	}
	else
	{
		AfxMessageBox("串口未有打开");
	}
	return ;
}

void CKsCardInterFaceDemoDlg::OnMendMoney() 
{
	// TODO: Add your control notification handler code here
	int ret;
	int nRet;
	if (!s_comopen)
	{
		AfxMessageBox("串口未有打开");
		return;
	}
	CString sRefno;
	GetDlgItem(IDC_EDIT3)->GetWindowText(sRefno);
	if(sRefno=="")
	{
		AfxMessageBox("请输入要冲正流水的交易参考号");
		GetDlgItem(IDC_EDIT3)->SetFocus();
		return;
	}
	CString sMac;
	GetDlgItem(IDC_EDIT7)->GetWindowText(sMac);
	if(sRefno=="")
	{
		AfxMessageBox("请输入要冲正流水的MAC校验码");
		GetDlgItem(IDC_EDIT7)->SetFocus();
		return;
	}
	CString sTransAmt;
	GetDlgItem(IDC_EDIT8)->GetWindowText(sTransAmt);
	if(sTransAmt=="")
	{
		AfxMessageBox("请输入扣款金额(单位:分)");
		GetDlgItem(IDC_EDIT8)->SetFocus();
		return;
	}
	char szCardPhyID[17]={0};
	ret=KS_RequestCard(szCardPhyID);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	KS_Reset();
	KS_SetReadFieldName("CARDNO");		//交易卡号
	KS_SetReadFieldName("CARDBAL");		//卡余额
	KS_SetReadFieldName("DPSCNT");		//充值次数
	//KS_SetReadFieldName("PAYCNT");		//消费次数

	ret=KS_ReadCard();
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	//	KS_Beep();
	//	stringstream ssInfo;
	char fieldval[61]={0};
	KS_GetFieldVal("CARDNO",fieldval);		//交易卡号
	int cardno=atol(fieldval);
	KS_GetFieldVal("CARDBAL",fieldval);		//卡余额
	int cardbefbal=atol(fieldval);
	KS_GetFieldVal("DPSCNT",fieldval);		//充值次数
	int dpscnt=atol(fieldval);
	ret=KS_PayCancelProcess((LPSTR)(LPCTSTR)sRefno,(LPSTR)(LPCTSTR)sMac,szCardPhyID,cardno,cardbefbal,dpscnt);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	char GetProveFlag=0;
REPEAT:
	nRet=KS_CardBalanceInc(&GetProveFlag);
	if(nRet)
	{
		if(0 == GetProveFlag)
		{
			AfxMessageBox(KS_GetErrMsg(NULL));
			return;
		}
		////////////////////
		//中途拔卡处理
		AfxMessageBox("写卡失败,请重放卡");
		int FindCardFlag=0;
		int WaitStartTime=GetTickCount();
		//等待用户刷卡，超时时间30秒
		while(GetTickCount()-WaitStartTime<30)
		{
			char sNewCardPhyID[17]={0};
			nRet=KS_RequestCard(sNewCardPhyID);
			if(nRet)
			{
				Sleep(50);
				continue;
			}
			if(strcmp(szCardPhyID,sNewCardPhyID)!=0)
			{
				AfxMessageBox("卡号错误,请刷原卡");
				continue;
			}
			FindCardFlag=1;
			break;
		}
		if(0==FindCardFlag)
		{
			//等待刷卡超时,写卡失败处理
			KS_UnProveProcess();
			AfxMessageBox("写卡失败,交易取消");
			return;
		}
		else
		{
			char cReWriteCardFlag=0;
			KS_GetProve(&cReWriteCardFlag);
			if(cReWriteCardFlag)
			{
				goto REPEAT;
			}
		}
	}
	char sBefBal[20]={0};
	char sAftBal[20]={0};
	sprintf(sBefBal,"%d",cardbefbal);
	sprintf(sAftBal,"%d",cardbefbal+atoi(sTransAmt));
	GetDlgItem(IDC_EDIT4)->SetWindowText(sBefBal);
	GetDlgItem(IDC_EDIT5)->SetWindowText(sAftBal);
	KS_Beep();
}

void CKsCardInterFaceDemoDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (s_comopen) 
	{ 
		KS_ClosePort(); 
	}
	CDialog::OnClose();
}

void CKsCardInterFaceDemoDlg::OnBnClickedLogin()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	int nShopID=0;
	char szMsg[256];
	char sShopName[61]={0};
	ret=KS_SignIn(&nShopID,sShopName);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	KS_Beep();

	sprintf(szMsg,"%d",nShopID);
	GetDlgItem(IDC_EDIT6)->SetWindowText(szMsg);
	GetDlgItem(IDC_EDIT2)->SetWindowText(sShopName);
	sprintf(szMsg,"读卡器签到成功，商户号%d商户名:%s",nShopID,sShopName);
	AfxMessageBox(szMsg);
}

void CKsCardInterFaceDemoDlg::OnBnClickedBtnReadkey()
{
	int ret;
	ret = KS_LoadCardKeys("123456");
	if(ret)
	{
		AfxMessageBox("请放授权卡");
		return;
	}
	KS_Beep();
}

void CKsCardInterFaceDemoDlg::OnBnClickedLogin2()
{
	// TODO: 在此添加控件通知处理程序代码
	int ret=0;
	int nShopID=0;
	char sShopName[61]={0};

	CString sUser;
	GetDlgItem(IDC_EDIT_USER)->GetWindowText(sUser);
	if(sUser=="")
	{
		AfxMessageBox("请输入要操作员号");
		GetDlgItem(IDC_EDIT_USER)->SetFocus();
		return;
	}
	CString sUserPasswd;
	GetDlgItem(IDC_EDIT_PASSWD)->GetWindowText(sUserPasswd);
	if(sUser=="")
	{
		AfxMessageBox("请输入操作员密码");
		GetDlgItem(IDC_EDIT_PASSWD)->SetFocus();
		return;
	}
	ret=KS_UserSignIn((LPCTSTR)sUser,(LPCTSTR)sUserPasswd);
	if(ret)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	KS_Beep();
	AfxMessageBox("充值机签到成功");
}

void CKsCardInterFaceDemoDlg::OnBnClickedBtnRechange()
{
	int nRet;
	if (!s_comopen)
	{
		AfxMessageBox("串口未有打开");
		return;
	}
	CString sTransAmt;
	GetDlgItem(IDC_EDIT8)->GetWindowText(sTransAmt);
	if(sTransAmt=="")
	{
		AfxMessageBox("请输入充值金额(单位:分)");
		GetDlgItem(IDC_EDIT8)->SetFocus();
		return;
	}
	char szCardPhyID[17]={0};
	nRet=KS_RequestCard(szCardPhyID);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	KS_Reset();
	KS_SetReadFieldName("CARDNO");		//交易卡号
	KS_SetReadFieldName("CARDBAL");		//卡余额
	KS_SetReadFieldName("DPSCNT");		//充值次数

	nRet=KS_ReadCard();
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return ;
	}
	char fieldval[61]={0};
	KS_GetFieldVal("CARDNO",fieldval);		//交易卡号
	int cardno=atol(fieldval);
	KS_GetFieldVal("CARDBAL",fieldval);		//卡余额
	int cardbefbal=atol(fieldval);
	KS_GetFieldVal("DPSCNT",fieldval);		//消费次数
	int dpscnt=atol(fieldval);
	char refno[20]={0};
	char mac[9]={0};
	nRet=KS_RechangePrepare(szCardPhyID,cardno,cardbefbal,dpscnt,0,refno,mac);
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));
		return;
	}
	////////////////////////////////
	
	//自助机收取现金

	////////////////////////////////
	nRet=KS_RechangeProcess(atoi(sTransAmt));
	if(nRet)
	{
		AfxMessageBox(KS_GetErrMsg(NULL));	
		return;
	}
	///写卡
	char GetProveFlag=0;
REPEAT:
	nRet=KS_CardBalanceInc(&GetProveFlag);
	if(nRet)
	{
		////////////////////
		//写卡失败处理
		AfxMessageBox("写卡失败,请重放卡");
		int FindCardFlag=0;
		int WaitStartTime=GetTickCount();
		//等待用户刷卡，超时时间30秒
		while(GetTickCount()-WaitStartTime<10*1000)
		{
			char sNewCardPhyID[17]={0};
			nRet=KS_RequestCard(sNewCardPhyID);
			if(nRet)
			{
				Sleep(50);
				continue;
			}
			if(strcmp(szCardPhyID,sNewCardPhyID)!=0)
			{
				AfxMessageBox("卡号错误,请刷原卡");
				continue;
			}
			FindCardFlag=1;
			break;
		}
		if(0==FindCardFlag)
		{
			//等待刷卡超时,写卡失败处理
			KS_UnProveProcess();
			AfxMessageBox("写卡失败,交易取消");
			return;
		}
		else
		{
			if(1 == GetProveFlag)
			{
				//中途拔卡处理
				char cReWriteCardFlag=0;
				KS_GetProve(&cReWriteCardFlag);
				if(cReWriteCardFlag)
				{
					goto REPEAT;
				}
			}
			else
			{
				goto REPEAT;
			}
		}
	}
	KS_Beep();//读卡器轰鸣,提示成功
	char sCardAftBal[20];
	sprintf(sCardAftBal,"%d",cardbefbal+atoi(sTransAmt));
	GetDlgItem(IDC_EDIT1)->SetWindowText(sCardAftBal);
	GetDlgItem(IDC_EDIT3)->SetWindowText(refno);
	GetDlgItem(IDC_EDIT7)->SetWindowText(mac);
}
void CKsCardInterFaceDemoDlg::OnCbnSelchangeComPort()
{
	// TODO: 在此添加控件通知处理程序代码
}
