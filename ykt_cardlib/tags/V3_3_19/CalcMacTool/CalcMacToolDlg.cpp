// CalcMacToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CalcMacTool.h"
#include "CalcMacToolDlg.h"
//#include "d3des.h"
#include "des.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

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
// CMyCalcMacToolDlg dialog

CMyCalcMacToolDlg::CMyCalcMacToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyCalcMacToolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyCalcMacToolDlg)
	m_sCryptKey = _T("");
	m_sInitResp = _T("");
	m_sMidKey = _T("");
	m_sMidKeyData = _T("");
	m_sMac = _T("");
	m_sMacData = _T("");
	m_sTermID = _T("");
	m_sSysDate = _T("");
	m_sTransAmt = _T("");
	m_sInitCmd = _T("");
	m_sCreditCmd = _T("");
	m_sDebitCmd = _T("");
	m_sTermsno = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyCalcMacToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyCalcMacToolDlg)
	DDX_Control(pDX, IDC_CMB_TRANSTYPE, m_cbxTransType);
	DDX_Text(pDX, IDC_CRYPT_KEY, m_sCryptKey);
	DDV_MaxChars(pDX, m_sCryptKey, 32);
	DDX_Text(pDX, IDC_INITRESP, m_sInitResp);
	DDX_Text(pDX, IDC_MIDKEY, m_sMidKey);
	DDX_Text(pDX, IDC_MIDKEYDATA, m_sMidKeyData);
	DDX_Text(pDX, IDC_MAC, m_sMac);
	DDV_MaxChars(pDX, m_sMac, 8);
	DDX_Text(pDX, IDC_MACDATA, m_sMacData);
	DDV_MaxChars(pDX, m_sMacData, 48);
	DDX_Text(pDX, IDC_TERMID, m_sTermID);
	DDV_MaxChars(pDX, m_sTermID, 12);
	DDX_Text(pDX, IDC_SYSDATE, m_sSysDate);
	DDV_MaxChars(pDX, m_sSysDate, 14);
	DDX_Text(pDX, IDC_TRANSAMT, m_sTransAmt);
	DDV_MaxChars(pDX, m_sTransAmt, 8);
	DDX_Text(pDX, IDC_INITCMD, m_sInitCmd);
	DDV_MaxChars(pDX, m_sInitCmd, 34);
	DDX_Text(pDX, IDC_CREDITCMD, m_sCreditCmd);
	DDX_Text(pDX, IDC_DEBITCMD, m_sDebitCmd);
	DDX_Text(pDX, IDC_TERMSNO, m_sTermsno);
	DDV_MaxChars(pDX, m_sTermsno, 8);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyCalcMacToolDlg, CDialog)
	//{{AFX_MSG_MAP(CMyCalcMacToolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_GENMIDKEY, OnGenmidkey)
	ON_BN_CLICKED(IDC_GENMAC, OnGenmac)
	ON_BN_CLICKED(IDC_GENINITCMD, OnGeninitcmd)
	ON_BN_CLICKED(IDC_GENCMD, OnGencmd)
	ON_CBN_SELENDOK(IDC_CMB_TRANSTYPE, OnSelendokCmbTranstype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyCalcMacToolDlg message handlers

BOOL CMyCalcMacToolDlg::OnInitDialog()
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
//	m_sPlain="1122334455667788";
	m_sTermsno="00000001";
	m_sCryptKey="66666666666666666666666666666666";
	m_sTermID="112233445566";
	m_sSysDate="20090212121212";
	m_sTransAmt="00000005";
	m_cbxTransType.SetCurSel(0);
	UpdateData(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyCalcMacToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyCalcMacToolDlg::OnPaint() 
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
HCURSOR CMyCalcMacToolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyCalcMacToolDlg::OnClose() 
{
	// TODO: Add your control notification handler code here
	CDialog::EndDialog(0);
}
/*
void CMyCalcMacToolDlg::OnBtnEncode() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    des_context ctx;
    des3_context ctx3;

	if(m_sPlain.GetLength()<1)
	{
		AfxMessageBox("明文不能空");
		GetDlgItem(IDC_PLAIN)->SetFocus();
		return;
	}
	unsigned char szKey[100];
	int lDst=0;
	unsigned char szCryptKey[100];
	unsigned char szPlain[100];
	unsigned char szHex[100];
	unsigned char *pCipher=NULL;
	unsigned char szCipher[100];
	memset(szCryptKey,0,sizeof(szCryptKey));
	memset(szPlain,0,sizeof(szPlain));
	memset(szCipher,0,sizeof(szCipher));

	char hexplain[100];
	char hexkey[100];
	int i=0;
	char temp[3];
	//对key处理
	int len=m_sCryptKey.GetLength()/2;
	if(len%8!=0)
	{
		AfxMessageBox("密钥的长度不是8的倍数");
		return; 
	}
	memset(hexkey,0,sizeof(hexkey));
	strcpy(hexkey,m_sCryptKey.GetBuffer(0));
	m_sCryptKey.ReleaseBuffer();
	memset(szKey,0,sizeof(szKey));
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexkey[2*i],2);
		sscanf(temp,"%02X",&szKey[i]);
	}
	//对明文处理
	memset(hexplain,0,sizeof(hexplain));
	if(m_sPlain.GetLength()%8!=0)
	{
		AfxMessageBox("明文的长度不是8的倍数");
		return; 
	}
	strcpy(hexplain,m_sPlain.GetBuffer(0));
	m_sPlain.ReleaseBuffer();
	for(i=0;i<8;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexplain[2*i],2);
		sscanf(temp,"%02X",&szPlain[i]);
	}
	if(8==len)
	{
		des_set_key( &ctx, szKey);

		des_encrypt( &ctx, szPlain, szCipher );
	}
	else if(16==len)
	{
		des3_set_2keys( &ctx3, szKey,szKey+8 );
		des3_encrypt( &ctx3, szPlain, szCipher);
	}
	//对密文处理
	memset(szHex,0,sizeof(szHex));
	for( i=0;i<8;i++)
	{
		sprintf((char*)szHex,"%s%02X",szHex,szCipher[i]);
	}
	m_sCipher=CString(szHex);
	UpdateData(false);
}
*/
/*
void CMyCalcMacToolDlg::OnDecode() 
{

    des_context ctx;
    des3_context ctx3;
	unsigned char szKey[100];
	int lDst=0;
	int i=0;
	unsigned char szHex[100];
	unsigned char szCryptKey[100];
	unsigned char szPlain[100];
	unsigned char *pCipher=NULL;
	unsigned char szCipher[100];
	char hexCipher[100];
	char temp[3];
	char hexkey[100]="";
	UpdateData();
	int len=m_sCryptKey.GetLength()/2;
	if(len%8!=0)
	{
		AfxMessageBox("密钥的长度不是8的倍数");
		return; 
	}
	memset(szCryptKey,0,sizeof(szCryptKey));
	strcpy(hexkey,m_sCryptKey.GetBuffer(0));
	m_sCryptKey.ReleaseBuffer();
	//对key处理
	memset(szKey,0,sizeof(szKey));
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexkey[2*i],2);
		sscanf(temp,"%02X",&szKey[i]);
	}
	memset(hexCipher,0,sizeof(hexCipher));
	strcpy(hexCipher,m_sCipher.GetBuffer(0));
	m_sCipher.ReleaseBuffer();
	//对密文处理
	for(i=0;i<8;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexCipher[2*i],2);
		sscanf(temp,"%02X",&szCipher[i]);
	}
	memset(szPlain,0,sizeof(szPlain));
	if(8==len)
	{
		des_set_key( &ctx, szKey);
		
		des_decrypt( &ctx,szCipher,szPlain);
	}
	else if(16==len)
	{
		des3_set_2keys( &ctx3, szKey,szKey+8 );
		des3_decrypt( &ctx3, szCipher,szPlain);
	}
	//对明文处理
	memset(szHex,0,sizeof(szHex));
	for( i=0;i<8;i++)
	{
		sprintf((char*)szHex,"%s%02X",szHex,szPlain[i]);
	}
	m_sPlain2=CString(szHex);
	UpdateData(false);

}
*/
BOOL CMyCalcMacToolDlg::PreTranslateMessage(MSG* pMsg) 
{
    if(pMsg->message == WM_KEYDOWN) 
     { 
		 if(pMsg->wParam == VK_RETURN) 
		 { 
			 UINT nID = GetFocus()->GetDlgCtrlID(); 
			 switch( nID) 
			 { 
			 case IDOK: 
			 break; 
			 default: 
			 NextDlgCtrl(); 
			 return TRUE; 
			 } 
		 } 
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CMyCalcMacToolDlg::OnGenmidkey() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
    des_context ctx;
    des3_context ctx3;	

	if(m_sInitResp.GetLength()<1)
	{
		AfxMessageBox("响应数据不能空");
		GetDlgItem(IDC_INITRESP)->SetFocus();
		return;
	}
	if(m_sInitResp.GetLength()<32)
	{
		AfxMessageBox("响应数据长度不足32位");
		GetDlgItem(IDC_INITRESP)->SetFocus();
	}
	if(m_cbxTransType.GetCurSel()==0)
	{
		CString sTransAmt=m_sInitResp.Left(8);
		CString  sTransCnt=m_sInitResp.Mid(8,4);
		CString sRoundNum=m_sInitResp.Mid(16,8);
		m_sMidKeyData=sRoundNum+sTransCnt+"8000";
	}
	else
	{
		CString sTransAmt=m_sInitResp.Left(8);
		CString  sTransCnt=m_sInitResp.Mid(8,4);
		CString sRoundNum=m_sInitResp.Mid(22,8);
		for(;m_sTermsno.GetLength()<8;)
			m_sTermsno="0"+m_sTermsno;
		m_sMidKeyData=sRoundNum+sTransCnt+m_sTermsno.Right(4);
	}
	unsigned char szKey[100];
	int lDst=0;
	unsigned char szCryptKey[100];
	unsigned char szPlain[100];
	unsigned char szHex[100];
	unsigned char *pCipher=NULL;
	unsigned char szCipher[100];
	memset(szCryptKey,0,sizeof(szCryptKey));
	memset(szPlain,0,sizeof(szPlain));
	memset(szCipher,0,sizeof(szCipher));
	
	char hexplain[100];
	char hexkey[100];
	int i=0;
	char temp[3];
	//对key处理
	int len=m_sCryptKey.GetLength()/2;
	if(len%8!=0)
	{
		AfxMessageBox("密钥的长度不是8的倍数");
		return; 
	}
	memset(hexkey,0,sizeof(hexkey));
	strcpy(hexkey,m_sCryptKey.GetBuffer(0));
	m_sCryptKey.ReleaseBuffer();
	memset(szKey,0,sizeof(szKey));
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexkey[2*i],2);
		sscanf(temp,"%02X",&szKey[i]);
	}
	//对明文处理
	memset(hexplain,0,sizeof(hexplain));
	if(m_sMidKeyData.GetLength()%8!=0)
	{
		AfxMessageBox("计算MAc的数据长度不是8的倍数");
		return; 
	}
	strcpy(hexplain,m_sMidKeyData.GetBuffer(0));
	m_sMidKeyData.ReleaseBuffer();
	for(i=0;i<8;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexplain[2*i],2);
		sscanf(temp,"%02X",&szPlain[i]);
	}
	if(8==len)
	{
		des_set_key( &ctx, szKey);	
		des_encrypt( &ctx, szPlain, szCipher );
	}
	else if(16==len)
	{
		des3_set_2keys( &ctx3, szKey,szKey+8 );
		des3_encrypt( &ctx3, szPlain, szCipher);
	}
	//对密文处理
	memset(szHex,0,sizeof(szHex));
	for( i=0;i<8;i++)
	{
		sprintf((char*)szHex,"%s%02X",szHex,szCipher[i]);
	}
	m_sMidKey=CString(szHex);
	UpdateData(false);	
}
/*
void CMyCalcMacToolDlg::OnGenmac() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData();
    des_context ctx;
    des3_context ctx3;	
	//交易金额＋交易类型02=ep电子钱包＋终端机编号2075525820392＋交易日期20031229＋交易时间
	//＋初始值“0000000000000000”＋过程密钥＝mac2
	m_sMidKey="01020304050607081112131415161718";
	m_sMacData="182713000000000000DF0458778792A164C8721AF4056B508180000000000000"; 

	CString sRadomData="C0300764594D6D8D";
	UpdateData(false);
	unsigned char szKey[100];
	int lDst=0;
	unsigned char szCryptKey[100];
	unsigned char szPlain[100];
	unsigned char szHex[100];
	unsigned char *pCipher=NULL;
	unsigned char szCipher[100],szCipher2[100];
	unsigned char szInitData[17]={0};
	memset(szCryptKey,0,sizeof(szCryptKey));
	memset(szPlain,0,sizeof(szPlain));
	memset(szCipher,0,sizeof(szCipher));
	
	char hexplain[100];
	char hexkey[100];
	int i=0;
	char temp[3];
	//对key处理
	int len=m_sMidKey.GetLength()/2;
	if(len%8!=0)
	{
		AfxMessageBox("过程密钥的长度不是8的倍数");
		return; 
	}
	memset(hexkey,0,sizeof(hexkey));
	strcpy(hexkey,m_sMidKey.GetBuffer(0));
	m_sMidKey.ReleaseBuffer();
	memset(szKey,0,sizeof(szKey));
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexkey[2*i],2);
		sscanf(temp,"%02X",&szKey[i]);
	}
	a1 a2 a3

	a1^'0000000000000'
	des 
	ret^a2
	des 
	ret^a3
	des



	//对明文处理
	memset(hexplain,0,sizeof(hexplain));
	if(m_sMacData.GetLength()%8!=0)
	{
		AfxMessageBox("明文的长度不是8的倍数");
		return; 
	}
	strcpy(hexplain,m_sMacData.GetBuffer(0));
	m_sMacData.ReleaseBuffer();
	len=m_sMacData.GetLength()/2;
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexplain[2*i],2);
		sscanf(temp,"%02X",&szPlain[i]);
	}
	//先加密
	des3_set_2keys( &ctx3, szKey,szKey+8 );
	des3_encrypt( &ctx3, szPlain, szCipher2);
	des3_encrypt( &ctx3, szPlain+8, szCipher2+8);
	des3_encrypt( &ctx3, szPlain+16, szCipher2+16);
	des3_encrypt( &ctx3, szPlain+24, szCipher2+24);
	
	memcpy(szPlain,szCipher2,32);
	
	BYTE uMacData[100];
	memset(&uMacData,0,sizeof(uMacData));
	memcpy(uMacData,"\x84\xD4\x00\x11\x24",5);
	memcpy(uMacData+5,szCipher2,32);
	uMacData[37]=0x80;
	memset(hexplain,0,sizeof(hexplain));
	strcpy(hexplain,sRadomData.GetBuffer(0));
	len=sRadomData.GetLength()/2;
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexplain[2*i],2);
		sscanf(temp,"%02X",&szInitData[i]);
	}
	//第一步 异或 szInitData是随机数szPlain是要算mac的32字节数据
	for(i=0;i<8;i++)
	{
		szPlain[i]=szInitData[i]^uMacData[i];
	}
	//3des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlain, szCipher);
	//第二步 异或
	for(i=0;i<8;i++)
	{
		szPlain[i]=szCipher[i]^uMacData[8+i];  //D2
	}
	//3des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlain, szCipher);
	//第三步 异或
	for(i=0;i<8;i++)
	{
		szPlain[i]=szCipher[i]^uMacData[16+i];
	}
	//3des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlain, szCipher);
	//第四步 异或
	for(i=0;i<8;i++)
	{
		szPlain[i]=szCipher[i]^uMacData[24+i];
	}
	//3des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlain, szCipher);
	//第四步 异或
	for(i=0;i<8;i++)
	{
		szPlain[i]=szCipher[i]^uMacData[32+i];
	}
	//3des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlain, szCipher);

	des_set_key( &ctx, szKey+8);	
	des_decrypt(&ctx,szCipher,szPlain);
	des_set_key(&ctx, szKey);	
	des_encrypt( &ctx, szPlain, szCipher);	
		//对密文处理
	memset(szHex,0,sizeof(szHex));
	for( i=0;i<4;i++)
	{
		sprintf((char*)szHex,"%s%02X",szHex,szCipher[i]);
	}
	//36 9A 09 B9 
	m_sMac=CString(szHex);
	UpdateData(false);	
}
*/
void CMyCalcMacToolDlg::OnGenmac() 
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	UpdateData();
    des_context ctx;
	//交易金额＋交易类型02=ep电子钱包＋终端机编号2075525820392＋交易日期20031229＋交易时间
	//＋初始值“0000000000000000”＋过程密钥＝mac2
	if(m_sInitResp.GetLength()<32)
	{
		AfxMessageBox("响应数据长度不足");
		GetDlgItem(IDC_INITRESP)->SetFocus();
		return;
	}
	if(m_sInitCmd.GetLength()<32)
	{
		AfxMessageBox("初始数据长度不足");
		GetDlgItem(IDC_INITRESP)->SetFocus();
		return;
	}
	CString sTransAmt=m_sInitCmd.Mid(12,8);
	if(m_cbxTransType.GetCurSel()==0)
	{
		m_sMacData=sTransAmt+"02"+m_sTermID+m_sSysDate;
	}
	else
	{
		m_sMacData=sTransAmt+"06"+m_sTermID+m_sSysDate;
	}
	m_sMacData+="800000000000";
	if(m_sMacData.GetLength()!=48)
	{
		AfxMessageBox("数据长度不足48位");
		GetDlgItem(IDC_MACDATA)->SetFocus();
		return;
	}
	UpdateData(false);
	unsigned char szKey[100];
	int lDst=0;
	unsigned char szCryptKey[100];
	unsigned char szPlain[100];
	unsigned char szHex[100];
	unsigned char *pCipher=NULL;
	unsigned char szCipher[100];
	unsigned char szInitData[9]={0};
	memset(szCryptKey,0,sizeof(szCryptKey));
	memset(szPlain,0,sizeof(szPlain));
	memset(szCipher,0,sizeof(szCipher));
	
	char hexplain[100];
	char hexkey[100];
	int i=0;
	char temp[3];
	//对key处理
	int len=m_sMidKey.GetLength()/2;
	if(len%8!=0)
	{
		AfxMessageBox("过程密钥的长度不是8的倍数");
		return; 
	}
	memset(hexkey,0,sizeof(hexkey));
	strcpy(hexkey,m_sMidKey.GetBuffer(0));
	m_sMidKey.ReleaseBuffer();
	memset(szKey,0,sizeof(szKey));
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexkey[2*i],2);
		sscanf(temp,"%02X",&szKey[i]);
	}
	//对明文处理
	memset(hexplain,0,sizeof(hexplain));
	if(m_sMacData.GetLength()%8!=0)
	{
		AfxMessageBox("明文的长度不是8的倍数");
		return; 
	}
	strcpy(hexplain,m_sMacData.GetBuffer(0));
	m_sMacData.ReleaseBuffer();
	len=m_sMacData.GetLength()/2;
	for(i=0;i<len;i++)
	{
		memset(temp,0,sizeof(temp));
		memcpy((char*)temp,&hexplain[2*i],2);
		sscanf(temp,"%02X",&szPlain[i]);
	}
	//第一步 异或
	unsigned char szPlainXor[9]={0};
	for(i=0;i<8;i++)
	{
		szPlainXor[i]=szInitData[i]^szPlain[i];
	}
	//des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlainXor, szCipher);
	//第二步 异或
	unsigned char szPlainXor2[9]={0};
	for(i=0;i<8;i++)
	{
		szPlainXor2[i]=szCipher[i]^szPlain[8+i];  //D2
	}
	//des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlainXor2, szCipher);
	//第三步 异或
	unsigned char szPlainXor3[9]={0};
	for(i=0;i<8;i++)
	{
		szPlainXor3[i]=szCipher[i]^szPlain[16+i];
	}
	//des加密
	des_set_key( &ctx, szKey);	
	des_encrypt( &ctx, szPlainXor3, szCipher);

	//对密文处理
	memset(szHex,0,sizeof(szHex));
	for( i=0;i<4;i++)
	{
		sprintf((char*)szHex,"%s%02X",szHex,szCipher[i]);
	}
	m_sMac=CString(szHex);
	UpdateData(false);	
}
void CMyCalcMacToolDlg::OnGeninitcmd() 
{
	// TODO: Add your control notification handler code here
	//805000020B010000271011223344556610
	UpdateData();

	for(;m_sTransAmt.GetLength()<8;)
	{
		m_sTransAmt="0"+m_sTransAmt;
	}
	if(m_cbxTransType.GetCurSel()==0)
		m_sInitCmd="805000020B01"+m_sTransAmt+m_sTermID+"10";
	else
		m_sInitCmd="805001020B01"+m_sTransAmt+m_sTermID+"0F";
	UpdateData(false);
}

void CMyCalcMacToolDlg::OnGencmd() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_sMac.GetLength()!=8)
	{
		AfxMessageBox("MAC长度不正确");
		return; 
	}
	if(m_cbxTransType.GetCurSel()==0)
	{
		m_sCreditCmd="805200000B"+m_sSysDate+m_sMac;
		m_sDebitCmd="";
	}
	else
	{
		m_sDebitCmd ="805401000F"+m_sTermsno+m_sSysDate+m_sMac;
		m_sCreditCmd="";
	}
	UpdateData(false);
}
void CMyCalcMacToolDlg::OnSelendokCmbTranstype() 
{
	// TODO: Add your control notification handler code here
	if(m_cbxTransType.GetCurSel()!=0)
		m_sCryptKey="77777777777777777777777777777777";
	else
		m_sCryptKey="66666666666666666666666666666666";
	UpdateData(false);		
}
