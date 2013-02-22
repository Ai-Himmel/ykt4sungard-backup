// RF35OCXCtl.cpp : Implementation of the CRF35OCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "RF35OCX.h"
#include "RF35OCXCtl.h"
#include "RF35OCXPpg.h"
//#include "mwrf32.h"
#include "dcrf32.h"
#include "comm.h"
#include ".\rf35ocxctl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString CRF35OCXCtrl::ms_tokenKey("&token=r34ks2005fd");

IMPLEMENT_DYNCREATE(CRF35OCXCtrl, COleControl)


	/////////////////////////////////////////////////////////////////////////////
	// Message map

BEGIN_MESSAGE_MAP(CRF35OCXCtrl, COleControl)
	//{{AFX_MSG_MAP(CRF35OCXCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


	/////////////////////////////////////////////////////////////////////////////
	// Dispatch map

BEGIN_DISPATCH_MAP(CRF35OCXCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CRF35OCXCtrl)
	DISP_PROPERTY_NOTIFY(CRF35OCXCtrl, "CardNo", m_nCardNo, OnCardNoChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CRF35OCXCtrl, "PortNo", m_nPortNo, OnPortNoChanged, VT_I2)
	DISP_FUNCTION(CRF35OCXCtrl, "DoScan", DoScan, VT_I2, VTS_NONE)
	DISP_FUNCTION(CRF35OCXCtrl, "UndoLoss", UndoLoss, VT_I2, VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CRF35OCXCtrl, "ChangePassWord", ChangePassWord, VT_I2, VTS_BSTR VTS_BSTR VTS_I4)
	DISP_FUNCTION(CRF35OCXCtrl, "SendRequest", SendRequest, VT_I2, VTS_BSTR)
	//}}AFX_DISPATCH_MAP
	// DISP_FUNCTION_ID(CRF35OCXCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	// DISP_FUNCTION_ID(CRF35OCXCtrl, "SendRequest", dispidSendRequest, SendRequest, VT_I2)
END_DISPATCH_MAP()


	/////////////////////////////////////////////////////////////////////////////
	// Event map

BEGIN_EVENT_MAP(CRF35OCXCtrl, COleControl)
	//{{AFX_EVENT_MAP(CRF35OCXCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


	/////////////////////////////////////////////////////////////////////////////
	// Property pages

	// TODO: Add more property pages as needed.  Remember to increase the count!
	BEGIN_PROPPAGEIDS(CRF35OCXCtrl, 1)
	PROPPAGEID(CRF35OCXPropPage::guid)
END_PROPPAGEIDS(CRF35OCXCtrl)


	/////////////////////////////////////////////////////////////////////////////
	// Initialize class factory and guid

	IMPLEMENT_OLECREATE_EX(CRF35OCXCtrl, "RF35OCX.RF35OCXCtrl.1",
						   0x335aeb92, 0x0d39, 0x4999, 0xa2, 0xb5, 0x53, 0x6a, 0x2c, 0x71, 0x89, 0x01)


	/////////////////////////////////////////////////////////////////////////////
	// Type library ID and version

IMPLEMENT_OLETYPELIB(CRF35OCXCtrl, _tlid, _wVerMajor, _wVerMinor)


	/////////////////////////////////////////////////////////////////////////////
	// Interface IDs

	const IID BASED_CODE IID_DRF35OCX =
{ 0x5f5cacb6, 0xafb2, 0x49be, { 0x9e, 0xd4, 0xd1, 0xe3, 0x4b, 0xd4, 0xe8, 0xd1 } };
const IID BASED_CODE IID_DRF35OCXEvents =
{ 0xc49584bd, 0x7055, 0x48b1, { 0xaf, 0x83, 0x74, 0x4d, 0x3d, 0x2e, 0xbe, 0xda } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwRF35OCXOleMisc =
OLEMISC_ACTIVATEWHENVISIBLE |
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CRF35OCXCtrl, IDS_RF35OCX, _dwRF35OCXOleMisc)


	/////////////////////////////////////////////////////////////////////////////
	// CRF35OCXCtrl::CRF35OCXCtrlFactory::UpdateRegistry -
	// Adds or removes system registry entries for CRF35OCXCtrl

BOOL CRF35OCXCtrl::CRF35OCXCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_RF35OCX,
			IDB_RF35OCX,
			afxRegApartmentThreading,
			_dwRF35OCXOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::CRF35OCXCtrl - Constructor

CRF35OCXCtrl::CRF35OCXCtrl():m_comopen(false)
{
	InitializeIIDs(&IID_DRF35OCX, &IID_DRF35OCXEvents);
	m_nPortNo = 0;
	m_nCardNo = 0;

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::~CRF35OCXCtrl - Destructor

CRF35OCXCtrl::~CRF35OCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
	if(m_icdev > 0)
	{
		dc_exit(m_icdev);
		
		m_icdev = 0;
	}
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::OnDraw - Drawing function

void CRF35OCXCtrl::OnDraw(
	CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	DoSuperclassPaint(pdc, rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::DoPropExchange - Persistence support

void CRF35OCXCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::OnResetState - Reset control to default state

void CRF35OCXCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::AboutBox - Display an "About" box to the user


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CRF35OCXCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= WS_DISABLED|WS_BORDER|WS_VISIBLE;
	cs.lpszClass = _T("EDIT");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::IsSubclassedControl - This is a subclassed control

BOOL CRF35OCXCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::OnOcmCommand - Handle command messages

LRESULT CRF35OCXCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl message handlers

void CRF35OCXCtrl::OnCardNoChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

int CRF35OCXCtrl::OpenCOM()
{
	if(!m_comopen)
	{	
		int ret = dc_init(100, 57600L);
		//int ret = dc_init(m_nPortNo,57600L);
		//int ret = rf_init(0,57600L);
		if(ret < 0)
		{
			AfxMessageBox(_T("初始化读卡器失败!"));
			return -1;
		}
		m_icdev = ret;
		m_comopen = true;
	}
	return 0;
}
short CRF35OCXCtrl::DoScan() 
{
	// TODO: Add your dispatch handler code here

	int ret = 0;
	int icdev = 0;
	unsigned long snr = 0;
	unsigned char size=0;
	if(ReadCardSNR(&snr))
	{
		return -1;
	}
	Beep(10);
	m_nCardNo = ntohl(snr);

	char cardno[16];
	ltoa(m_nCardNo, cardno, 10);
	SetWindowText(cardno);
	return TRUE;
}

void CRF35OCXCtrl::OnPortNoChanged() 
{
	SetModifiedFlag();
}


short CRF35OCXCtrl::UndoLoss(LPCTSTR mkey,long cardno,LPCTSTR blkver) 
{
	int ret = 0;
	unsigned long snr = 0;
	unsigned char data[16]="";
	unsigned char bcdblk[6] = "";
	unsigned char ucKeyA[6];
	
	if(ReadCardSNR(&snr))
	{
		return -1;
	}
	
	if(cardno != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -1;
	}
	memcpy(m_workkey,mkey,16);
	if(CalCardKeyA(snr,ucKeyA))
	{
		AfxMessageBox(_T("计算密钥失败"));
		return -1;
	}
	ret=dc_load_key(m_icdev,0,3,ucKeyA);
	if(ret != 0)
	{
		AfxMessageBox(_T("装载密码失败"));
		return -3;
	}

	ret=dc_authentication(m_icdev,0,3);	
	if(ret != 0)
	{
		AfxMessageBox(_T("验证密码失败"));
		return -4;
	}
	ret=dc_read(m_icdev,14,data);
	if(ret != 0)
	{
		AfxMessageBox(_T("读卡信息失败"));
		return -5;
	}
	// 版本
	if(_tcslen(blkver) != 12)
	{
		AfxMessageBox(_T("名单版本号不正确"));
		return -6;
	}
	USES_CONVERSION;
	unsigned char * blk = (unsigned char*)T2A(blkver);
	dec2bcd(blk,bcdblk,6);
	data[0]=0xff;
	memcpy(data+1,bcdblk,6);
	ret=dc_write(m_icdev,14,data);
	if(ret)
	{
		AfxMessageBox(_T("更改黑名单标志出错"));
		return -6;
	}
	Beep(10);
	return TRUE;
}

short CRF35OCXCtrl::ChangePassWord(LPCTSTR mkey,LPCTSTR newpwd,long cardno) 
{
	int ret = 0;
	unsigned long snr = 0;
	unsigned char data[16]="";
	char passwd[6]="";
	unsigned char ucKeyA[6];
	// AfxMessageBox(mkey);
	
	if(ReadCardSNR(&snr))
	{
		return -1;
	}
	
	if(cardno != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -1;
	}
	
	memcpy(m_workkey,mkey,16);
	if(CalCardKeyA(snr,ucKeyA))
	{
		AfxMessageBox(_T("计算密钥失败"));
		return -1;
	}

	ret=dc_load_key(m_icdev,0,1,ucKeyA);
	if(ret != 0)
	{
		AfxMessageBox(_T("装载密码失败"));
		return -3;
	}

	ret=dc_authentication(m_icdev,0,1);	
	if(ret != 0)
	{
		AfxMessageBox(_T("验证密码失败"));
		return -4;
	}
	ret=dc_read(m_icdev,5,data);
	if(ret != 0)
	{
		AfxMessageBox(_T("读卡信息失败"));
		return -5;
	}
	memcpy(passwd,newpwd,6);

	dec2bcd((unsigned char*)passwd,data,3);

	ret=dc_write(m_icdev,5,data);
	if(ret)
	{
		AfxMessageBox(_T("更改密码失败"));
		return -6;
	}
	Beep(10);
	return TRUE;
}

int CRF35OCXCtrl::DoSendRequest(const CString& url)
{
	cutil::cURL theUrl;
	int ret = theUrl.ParseURL((LPCTSTR)url);
	if(ret!=0)
	{
		return -1;
	}
	if(theUrl.IsSSL())
	{
		return DoHttpRequest<cutil::SSLTCPSocket>(theUrl);
	}
	else
	{
		return DoHttpRequest<cutil::TCPSocket>(theUrl);
	}
}

short CRF35OCXCtrl::SendRequest(LPCTSTR URL) 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString u(URL);
	if(u.GetLength() < 1)
	{
		return -1;
	}
	// u += (LPCTSTR)ms_tokenKey;
	return DoSendRequest((LPCTSTR)u);
}

void CRF35OCXCtrl::Beep(int mSec)
{
	dc_beep(m_icdev,mSec);
}

int CRF35OCXCtrl::ReadCardSNR(unsigned long * snr)
{
	int ret = 0;
	unsigned __int16 cardmode = 0;
	unsigned char size = 0;
	unsigned long cardid = 0;
	if(OpenCOM()< 0)
	{
		return -1;
	}
	// 重新放卡
//	dc_reset(m_icdev,10);				// 隐藏
	ret = dc_request(m_icdev,1,&cardmode);
	if(ret != 0)
	{
		AfxMessageBox(_T("读卡序列号失败,请移走卡后重试一次!"));
		return -2;
	}
	ret= dc_anticoll(m_icdev,0,&cardid);
	if(ret)
	{
		AfxMessageBox(_T("读卡器感应区没有卡"));
		return ret;
	}
	ret = dc_select(m_icdev,cardid,&size);
	if(ret)
	{
		AfxMessageBox(_T("选卡失败!"));
		return ret;
	}
	if(snr)
		*snr = cardid;
	return 0;
}

int CRF35OCXCtrl::CalCardKeyA(unsigned long snr,unsigned char * key)
{
	int i, 
		nCnt,
		nTemp = 0;
	unsigned char decKey[17] = "";
	unsigned char ucRawData[256],ucDesData[256],ucKeyA[6],ucWorkKey[8];
	unsigned char ucOffsetData[17] = "";
	//计算扇区密钥
	//memcpy(key,mkey,16);
	hex2dec((char*)m_workkey,decKey,8);

	en_key(decKey,ucWorkKey);

	unsigned char ucBuf[4];
	char ucTmp[9];

	memcpy(ucBuf,&snr,4);
	for(i=0;i<4;i++)
		sprintf(&ucTmp[2*i],"%02X",ucBuf[i]);
	hex2dec(ucTmp,ucRawData,4);

	for(i=0;i<4;i++)
	{
		ucRawData[i+4] = ~ucRawData[i];
	}
	des_code(ucWorkKey,ucRawData,ucDesData,'0');
//	Cal_Key(ucDesData,ucKeyA);
	//////////////////////////////////////////////////////////////////////////
	// 添加偏移算法
	memcpy(ucOffsetData, ucDesData, 8);
	memcpy(ucOffsetData + 8, ucDesData, 8);
	for (nCnt = 0; nCnt < 8; nCnt++)
	{
		nTemp += ucDesData[nCnt] * nCnt;
	}
	nTemp = nTemp % 10;
	memcpy(key, ucOffsetData + nTemp, 6);
	//////////////////////////////////////////////////////////////////////////
		
//	memcpy(key,ucKeyA,6);
	return 0;
}
