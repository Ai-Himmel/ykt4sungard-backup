// RF35OCXCtl.cpp : Implementation of the CRF35OCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "RF35OCX.h"
#include "RF35OCXCtl.h"
#include "RF35OCXPpg.h"
#include "comm.h"
#include ".\rf35ocxctl.h"
#include "curl\curl.h"
#include "tinyxml.h"
#include "kscard_imp.h"
#include "logfile.h"
#include "UtilTime.h"
#include <map>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define OPEN_READER(x) \
	KSCardReader _reader(x); \
	if(_reader.Open()) return -1

CString CRF35OCXCtrl::ms_tokenKey("&token=r34ks2005fd");

#define OCX_VERSION "1.2.0"

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
	DISP_FUNCTION(CRF35OCXCtrl, "UndoLoss", UndoLoss, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CRF35OCXCtrl, "ChangePassWord", ChangePassWord, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CRF35OCXCtrl, "SendRequest", SendRequest, VT_I2, VTS_BSTR)	
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CRF35OCXCtrl, "MySendRequest", dispidMySendRequest, MySendRequest, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetRequestRetInfo", dispidGetRequestRetInfo, GetRequestRetInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardPocket", dispidReadCardPocket, ReadCardPocket, VT_I4, VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetPacketInfo", dispidGetPacketInfo, GetPacketInfo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "RewriteCardInfo", dispidRewriteCardInfo, RewriteCardInfo, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReportCardWriteFailue", dispidReportCardWriteFailue, ReportCardWriteFailue, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetMainKey", dispidGetMainKey, GetMainKey, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CommonTransWriteCard", dispidCommonTransWriteCard, CommonTransWriteCard, VT_I2,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UpdateCardInfo", dispidUpdateCardInfo, UpdateCardInfo, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getComsumerLimit", dispidgetComsumerLimit, getComsumerLimit, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardConsumerLimit", dispidReadCardConsumerLimit, ReadCardConsumerLimit, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ResetConsumerLimit", dispidResetConsumerLimit, ResetConsumerLimit, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardSidyNo", dispidReadCardSidyNo, ReadCardSidyNo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "RewriteSidy", dispidRewriteSidy, RewriteSidy, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReNetTransWriteCard", dispidReNetTransWriteCard, ReNetTransWriteCard, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReverseNetTrans", dispidReverseNetTrans, ReverseNetTrans, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadOldCardInfo", dispidReadOldCardInfo, ReadOldCardInfo, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getOldCardInfo", dispidgetOldCardInfo, getOldCardInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getMoneyFromOldCard", dispidgetMoneyFromOldCard, getMoneyFromOldCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CardTransWriteCard", dispidCardTransWriteCard, CardTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "BeginUpdateCard", dispidBeginUpdateCard, BeginUpdateCard, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "SetCardProperty", dispidSetCardProperty, SetCardProperty, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UpdateCard", dispidUpdateCard, UpdateCard, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UpdateDeadlineDate", dispidUpdateDeadlineDate, UpdateDeadlineDate, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getDeadlineDate", dispidgetDeadlineDate, getDeadlineDate, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetVersion", dispidGetVersion, GetVersion, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadSmallPacket", dispidReadSmallPacket, ReadSmallPacket, VT_I2, VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetSmallPacketInfo", dispidGetSmallPacketInfo, GetSmallPacketInfo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "WaterTransWriteCard", dispidWaterTransWriteCard, WaterTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReWriteWaterTrans", dispidReWriteWaterTrans, ReWriteWaterTrans, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReportWriteCardFailure", dispidReportWriteCardFailure, ReportWriteCardFailure, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "BankTransWriteCard", dispidBankTransWriteCard, BankTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadShowCardno", dispidReadShowCardno, ReadShowCardno, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetCardStateInfo", dispidGetCardStateInfo, GetCardStateInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CardChangeClearOldCard", dispidCardChangeClearOldCard, CardChangeClearOldCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReCardChangeClearOldCard", dispidReCardChangeClearOldCard, ReCardChangeClearOldCard, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CheckNewCard", dispidCheckNewCard, CheckNewCard, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CardChangeNewCard", dispidCardChangeNewCard, CardChangeNewCard, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReCardChangeNewCard", dispidReCardChangeNewCard, ReCardChangeNewCard, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetChangeCardinfo", dispidGetChangeCardinfo, GetChangeCardinfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CheckOldCard", dispidCheckOldCard, CheckOldCard, VT_I2, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CRF35OCXCtrl, "CardPhyID", dispidCardPhyID, m_CardPhyID, OnCardPhyIDChanged, VT_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadWaterCtlPacket", dispidReadWaterCtlPacket, ReadWaterCtlPacket, VT_I2, VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetWaterCtlPacketInfo", dispidGetWaterCtlPacketInfo, GetWaterCtlPacketInfo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "WaterCtlTransWriteCard", dispidWaterCtlTransWriteCard, WaterCtlTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "WriteWaterCtlPacket", dispidWriteWaterCtlPacket, WriteWaterCtlPacket, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_I2 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReWriteWaterCtlTrans", dispidReWriteWaterCtlTrans, ReWriteWaterCtlTrans, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "DoOpenCom", dispidDoOpenCom, DoOpenCom, VT_I2, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CRF35OCXCtrl, "PsamCardPosition", dispidPsamCardPosition, m_PsamCardPosition, OnPsamCardPositionChanged, VT_I2)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardLockInfo", dispidReadCardLockInfo, ReadCardLockInfo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetCardLockInfo", dispidGetCardLockInfo, GetCardLockInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UnlockWriteCard", dispidUnlockWriteCard, UnlockWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReUnlockWriteCard", dispidReUnlockWriteCard, ReUnlockWriteCard, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CheckTransProve", dispidCheckTransProve, CheckTransProve, VT_I2, VTS_BSTR VTS_I2 VTS_I2)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "SetReturnMap", dispidSetReturnMap, SetReturnMap, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CleanReturnMap", dispidCleanReturnMap, CleanReturnMap, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "InitWaterCtlPocket", dispidInitWaterCtlPocket, InitWaterCtlPocket, VT_I2,VTS_BSTR VTS_I2 VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CheckLockStatus", dispidCheckLockStatus, CheckLockStatus, VT_I2, VTS_BSTR)
END_DISPATCH_MAP()
//	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetRequestRetInfo",dispidGetRequestRetInfo, GetRequestRetInfo,VT_BSTR, VTS_BSTR)
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
	m_nPortNo = 2;
	m_nCardNo = 0;

	m_param_name_map.insert(ParamName_Map::value_type(_T("errcode"),_T("ErrorCode")));
	m_param_name_map.insert(ParamName_Map::value_type(_T("errmsg"),_T("ErrorMessage")));
	m_param_name_map.insert(ParamName_Map::value_type(_T("serialno"),_T("SerialNo")));
	
	m_param_name_map.insert(ParamName_Map::value_type(_T("outcardamount"),_T("OutCardAmount")));
	m_param_name_map.insert(ParamName_Map::value_type(_T("cardphyid"),_T("CardId")));

	m_param_name_map.insert(ParamName_Map::value_type(_T("amount"),_T("MobileAmount")));
	m_param_name_map.insert(ParamName_Map::value_type(_T("amount"),_T("SidyAmount")));
	
}


///////////////////////////////////////////////////////////////////////////////
//串口管理模块
KSCardReader::KSCardReader():is_open_(0)
{

}
KSCardReader::~KSCardReader()
{
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	if(_file_open){
		g_LogFile.WriteLogEx(0, "ocx被析构 is_open=[%d]",is_open_);
		g_LogFile.ToFlush();
	}
	if(is_open_)
		ks_closeport();
	is_open_=0;
}
CString CRF35OCXCtrl::rtnCstring(int ret)
{
	CString tmp = "";
	tmp.Format("%d",ret);
	return tmp.AllocSysString();
}
int KSCardReader::Open(int cpupara4sam, int port)
{ 
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	if(is_open_)
		return 0;

	ks_licence("","123456");
	if(_file_open){
		g_LogFile.WriteLogEx(0, "ocx版本号日期=[%s],串口port=[%d]","20110127.1625",port);
		g_LogFile.ToFlush();
	}
	if((port<0)||(port>100)){
		port=0;
	}

	
	int ret = ks_openport(port,115200);//usb 读卡
	if(_file_open){
		g_LogFile.WriteLogEx(0, "psam卡座=[%d]",cpupara4sam);
		g_LogFile.ToFlush();
	}
	if((cpupara4sam>0)&&(cpupara4sam<5)){
		ks_setcpupara4sam(cpupara4sam);//1、大卡槽 2、小卡槽
	}
	if(ret!=0){
		char sMsg[256]="";
		ks_geterrmsg(sMsg);
		if(strlen(sMsg)<1)
		{
			CString tmp = "";
			tmp.Format("%d",ret);
			AfxMessageBox("打开串口失败，返回码="+tmp);
		}else{
			AfxMessageBox(sMsg);
		}
		return -1;
	}

	is_open_ = 1;
	m_port = port;
	ks_beep();
	return 0;
}

static KSCardReader g_ksCardRead;


/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl::~CRF35OCXCtrl - Destructor

CRF35OCXCtrl::~CRF35OCXCtrl()
{
	// TODO: Cleanup your control's instance data here.
/*	if(m_icdev > 0)
	{
		rf_exit(m_icdev);
		
		m_icdev = 0;
	}*/
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

//deprated
int CRF35OCXCtrl::OpenCOM()
{
	return -1;
}

//deprated
int CRF35OCXCtrl::CloseCOM(void)
{
	return -1;
}

short CRF35OCXCtrl::DoScan() 
{
	int ret = 0;
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
		if (ret==0)
	{

		char sCardPhyID[17];
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		m_CardPhyID.Format("%s",sCardPhyID);

		SetWindowText(sCardPhyID);
		return 0;
		
	}else{
		return -1;
	}
}

void CRF35OCXCtrl::OnPortNoChanged() 
{
	SetModifiedFlag();
}


short CRF35OCXCtrl::UndoLoss(LPCTSTR CardPhyId,LPCTSTR blkver) 
{
	unsigned long snr = 0;
	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		
		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDSTATUS);
		ret=ks_readcard();
		if(ret==0){
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_CARDSTATUS,sdata);
			if(ret==0){
				if(atol(sdata)==6){
					AfxMessageBox(_T("卡片被锁,不能解挂,请去解锁!"));
					return -1;
				}
			}else{
				AfxMessageBox(_T("卡状态读取失败,返回码="+rtnCstring(ret)));
				return -6;
			}

		}else{
			AfxMessageBox(_T("卡状态读取失败,返回码="+rtnCstring(ret)));
			return -4;
		}


		const char * cardstatus = "0";
		ks_clearallfieldallmode();
		ks_setfieldwritemode(CF_CARDSTATUS);
		ks_setfieldval(CF_CARDSTATUS,cardstatus);
		ks_setfieldwritemode(CF_CARDVERNO);
		ks_setfieldval(CF_CARDVERNO,blkver);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet==0 )
		{
			ks_beep();
			ks_clearallfieldwritemode();
			return 0;

		}else{
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				AfxMessageBox(sMsg);
			}
			return -5;
		}
		
		
	}else{
		return -1;
	}
}

short CRF35OCXCtrl::ChangePassWord(LPCTSTR CardPhyId,LPCTSTR newpwd)
{
	unsigned long snr = 0;
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
	
		ks_clearallfieldallmode();
		ks_setfieldwritemode(CF_CARDPWD);
		ks_setfieldval(CF_CARDPWD,newpwd);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet==0 )
		{
			ks_beep();
			ks_clearallfieldwritemode();
			return 0;

		}else{
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				AfxMessageBox(sMsg);
			}
			return -5;
		}
	}else{
		return -1;
	}
	
}

int CRF35OCXCtrl::DoSendRequest(const CString& url)
{
	cutil::cURL theUrl;
	int ret = theUrl.ParseURL((LPCTSTR)url);
	if(ret!=0){
		return -1;
	}
	if(theUrl.IsSSL())
	{
		return DoHttpRequest<cutil::SSLTCPSocket>(theUrl);
	}else{
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
	return MySendRequest((LPCTSTR)u,NULL);
}

void CRF35OCXCtrl::Beep(int mSec)
{
	//ControlBuzzer();
	//rf_beep(m_icdev,mSec);
}

int CRF35OCXCtrl::ReadCardSNR(unsigned long * snr)
{
	return 0;
}

int CRF35OCXCtrl::CalCardKeyA(unsigned long snr,unsigned char * key)
{
	int i;
	unsigned char decKey[17] = "";
	unsigned char ucSerialNo[5],ucRawData[256],ucDesData[256],ucKeyA[6],ucWorkKey[8];
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
	Cal_Key(ucDesData,ucKeyA);
	
	memcpy(key,ucKeyA,6);
	return 0;
}

// ChttprequestCtrl message handlers
struct MemoryStruct {
	char *memory;
	size_t size;
};

/*
struct RequestRetInfo 
{
	CString errcode; //错误码
	CString errmsg; //错误消息
	CString serialno;//流水号
	CString amount;//补助领取金额
	CString outcardamount;//最后出卡值
	CString paramKey;//系统密钥
	CString cardno;//卡号

};



//static RequestRetInfo g_request_ret;
*/

static RequestRet_Map g_request_return;

void *myrealloc(void *ptr, size_t size)
{
	/* There might be a realloc() out there that doesn't like reallocing
	NULL pointers, so we take care of it here */
	if(ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = (char *)myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

typedef struct 
{
	int cardbal;
	int dpt_card_cnt;
	int pay_card_cnt;
}MONEY_PACK_INFO;

static MONEY_PACK_INFO g_packet_info;

typedef struct 
{
	CString m_svrip;
	int m_svrport;
	int m_mainfunc;
}SERVER_BCC_INFO;

static SERVER_BCC_INFO g_server_bcc_info;
//原凯路水控钱包结构体
static sr_water_pack_t g_water_packet_info;
//最新的水控钱包结构体
static ks_water_pack_t g_waterctl_packet_info;

typedef struct
{
	CString termid;
	CString transdate;
	CString transtime;
	CString lockcardcnt;
}LOCK_INFO;

static LOCK_INFO g_lock_info; 

int CRF35OCXCtrl::get_return_field(const CString &param_name,CString &param_value)
{
	RequestRet_Map::iterator i = g_request_return.find(param_name);
	if(i == g_request_return.end())
		return -1;
	param_value = i->second;
	return 0;
}

//补助领取专用
SHORT CRF35OCXCtrl::MySendRequest(LPCTSTR url, LPCTSTR params)
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString dptCardCnt ="";
	CString payCardCnt = "";
	bala.Format("%d",g_packet_info.cardbal);
	dptCardCnt.Format("%d",g_packet_info.dpt_card_cnt);
	payCardCnt.Format("%d",g_packet_info.pay_card_cnt);
	t_params += "&cardBala="+bala+"&dptCardCnt="+dptCardCnt+"&payCardCnt="+payCardCnt;
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		
		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}
	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();
		
		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code))
		{
			return -2;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				CString outcardamount,amount,sdate3,stime3,cardphyid,sidyno,txcnt,ipServer,drtpPort,svrFunc;
				if(get_return_field("OutCardAmount",outcardamount))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("SidyAmount",amount))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("sdate3",sdate3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("stime3",stime3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("cardphyid",cardphyid))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("txCnt",txcnt))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("sidyno",sidyno))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("ipServer",ipServer))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("drtpPort",drtpPort))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("svrFunc",svrFunc))
				{
					// 没有卡号字段
					return -2;
				}


				int ret= WriteSidy(outcardamount,amount,sdate3,stime3,cardphyid,sidyno,txcnt,ipServer,drtpPort,svrFunc);

				if (ret==0)
				{
					//写卡成功
					return 0;
				}else{				
					return -1;
				}
			}else{
				//领取补助失败
				return 1;
			}
		}
	}
	return 2;
}


BSTR CRF35OCXCtrl::GetRequestRetInfo(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString code(param);
	CString strResult=_T("");
	if(get_return_field(code,strResult))
	{
		// 没有对应的参数，查找其它参数
		ParamName_Map::iterator itup,itlow;
		itup = m_param_name_map.upper_bound(code);
		itlow = m_param_name_map.lower_bound(code);
		for(;itlow != m_param_name_map.end() && itlow != itup; ++itlow)
		{
			if(get_return_field(itlow->second,strResult) == 0)
				break;
		}
	}
	return strResult.AllocSysString();
}
void CRF35OCXCtrl::ResetInfo(void)
{
	//全局初始化 /清空
	CString paramKey = _T("");
	get_return_field(_T("paramKey"),paramKey);
	g_request_return.clear();
	g_request_return.insert(RequestRet_Map::value_type(_T("paramKey"),paramKey));
}


// 写卡
short CRF35OCXCtrl::WriteCard(LPCTSTR outcardamount, LPCTSTR cardphyid,LPCTSTR txcnt,LPCTSTR amount,LPCTSTR sdate,LPCTSTR stime,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc)
{
	char sCardNo[20]="";
	ST_TRANSPACK payment;
	unsigned long snr=0;
	//char sCardPhyID[9];
	memset(&payment,0,sizeof payment);
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		CLogFile g_LogFile;
		bool _file_open = false;
		if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
				_file_open = true;
		}

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )                                                                                                       
		{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,错误信息=[%s],cardphyid=[%s]","寻卡失败",cardphyid);
					g_LogFile.ToFlush();
				}
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));			
			return -3;
		}
		const char * ip_server = ipServer;
		int svrport = atoi(drtpPort);
		int svrfunc = atoi(svrFunc);
		ks_comminit(ip_server,svrport,svrfunc);

		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDNO);
		ks_setfieldreadmode(CF_DPSCNT);
		ks_setfieldreadmode(CF_PAYCNT);
		ks_setfieldreadmode(CF_CARDBAL);

		nRet = ks_readcard();
		if(nRet!=0)
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "写卡信息发生错误,错误信息=[%s],cardphyid=[%s]","卡信息读取失败",cardphyid);
				g_LogFile.ToFlush();
			}
			AfxMessageBox(_T("卡信息读取失败"));
			return -4;
		}
		strcpy(payment.sCardPhyID,sCardPhyID);
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
		payment.nAftBalance = atoi(outcardamount);

		strcpy(payment.sTransDate,sdate);
		strcpy(payment.sTransTime,stime);
		payment.nFundType = 1;
		payment.nTransAmt = atoi(amount)*100; //1 元
		char termno[13]={0};
		ks_readpsamtermno(termno,0);
		strcpy(payment.sTermno,termno);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_setcardbal(&payment);
		if(nRet!=0)
		{		
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]","写卡错误，返回码="+nRet,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox(sMsg);
			}

			if(payment.cGetProveFlag==1){
				//中途拔卡
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,中途拔卡,cardphyid=[%s]",cardphyid);
					g_LogFile.ToFlush();
				}
				return -99;
			}		
				
			return -10;
		}else{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "写卡信息结果写卡成功,cardphyid=[%s]",cardphyid);
				g_LogFile.ToFlush();
			}
			ks_beep();
			return 0;
		}

	}else{
		return -1;
	}
}

LONG CRF35OCXCtrl::ReadCardPocket(SHORT pocket,LPCTSTR CardPhyId)
{
	int ret = 0;
	int sidyno = 0;
	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		char sCardPhyID[17];
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return 1;
		}


		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return 2;
		}


		RetsetPacketInfo();

		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDBAL);
		ks_setfieldreadmode(CF_DPSCNT);
		ks_setfieldreadmode(CF_PAYCNT);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret=ks_readcard();
		if(ret==0)
		{
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_CARDBAL,sdata);
			if(ret==0){
				g_packet_info.cardbal = atol(sdata);
			}else{
				return -1;
			}

			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_DPSCNT,sdata);
			if(ret==0){
				g_packet_info.dpt_card_cnt = atol(sdata);
			}else{
				return -2;
			}

			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_PAYCNT,sdata);
			if(ret==0){
				g_packet_info.pay_card_cnt = atol(sdata);
			}else{
				return -3;
			}
			
			return 0;

		}else{
			return -4;
		}

	}else{
		return -5;
	}
}

LONG CRF35OCXCtrl::GetPacketInfo(LPCTSTR param)
{
	LONG ret = 0;
	
	CString code(param);
	if (code=="cardbal")
	{
		ret = g_packet_info.cardbal;
	}
	if (code=="dpt_card_cnt")
	{
		ret = g_packet_info.dpt_card_cnt;
	}
	if (code=="pay_card_cnt")
	{
		ret = g_packet_info.pay_card_cnt;
	}
	if (code=="ssd_card_cnt")
	{		
		ret = 0;
	}

	return ret;
}

void CRF35OCXCtrl::RetsetPacketInfo(void)
{
	memset(&g_packet_info,0,sizeof g_packet_info);
}


void CRF35OCXCtrl::RetsetLockInfo(void)
{
	//memset(&g_lock_info,0,sizeof g_lock_info);
	g_lock_info.termid="";
	g_lock_info.transdate="";
	g_lock_info.transtime="";
	g_lock_info.lockcardcnt="";
}

SHORT CRF35OCXCtrl::RewriteCardInfo(void)
{
	int ret;
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
		_file_open = true;
	}

	CString outcardamount,amount,cardphyid,txcnt,sdate3,stime3,ipServer,drtpPort,svrFunc;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("amount",amount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("cardphyid",cardphyid))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("sdate3",sdate3))
	{
		// 没有金额字段
		return -2;
	}

	if(get_return_field("stime3",stime3))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("ipServer",ipServer))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("drtpPort",drtpPort))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("svrFunc",svrFunc))
	{
		// 没有卡号字段
		return -2;
	}
	if(_file_open){
		g_LogFile.WriteLogEx(0, "写卡失败，补写卡片余额cardphyid=[%s],amount=[%s]",cardphyid,amount);
		g_LogFile.ToFlush();
	}
	ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);
	return ret;
}

SHORT CRF35OCXCtrl::ReportCardWriteFailue(LPCTSTR url, LPCTSTR serialno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return -1;
}

SHORT CRF35OCXCtrl::GetMainKey(LPCTSTR url)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	CString strResult;

	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */
	CString t_param("key=kingstar");
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,t_param);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,3);

		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		int retries = 3;
		while(--retries){
			res = curl_easy_perform(curl);
			if(CURLE_OK==res){
				break;
			}
		}
		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}
		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}
		if(strResult!=""){
			g_request_return.insert(RequestRet_Map::value_type("paramKey",strResult));			
		}
	}

	return 0;
}
int CRF35OCXCtrl::do_write_card_and_request(LPCTSTR url, LPCTSTR cardno,LPCTSTR txcnt, LPCTSTR outcardamount,LPCTSTR amount,LPCTSTR sdate3,LPCTSTR stime3,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc,LPCTSTR params)
{
	CString strResult;
	CString t_params(params);
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */
	int ret = WriteCard(outcardamount,cardno,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);
	if (ret ==0)
	{
		curl = curl_easy_init();

		if (curl)
		{
			curl_easy_setopt(curl,CURLOPT_URL,url);
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60); 
			/* send all data to this function  */
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

			/* we pass our 'chunk' struct to the callback function */
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

			res = curl_easy_perform(curl);

			if(CURLE_OK!=res){
				//网络不通
				return 2;			
			}

			curl_easy_cleanup(curl);

			// TODO: Add your dispatch handler code here
			strResult.Format("%s",chunk.memory);
			if (chunk.memory)
			{
				free(chunk.memory);
			}	

		}

		//全局初始化 /清空
		ResetInfo();
		if(strResult!=""){
			TiXmlDocument doc;
			doc.Parse(strResult);
			TiXmlNode* node = 0;
			TiXmlNode* textnode = 0;
			TiXmlNode* node1 = 0;
			TiXmlElement* todoElement = 0;
			TiXmlElement* itemElement = 0;

			todoElement = doc.RootElement();
			node = todoElement->FirstChild();//head节点

			// 第一个节点
			node = node->FirstChild();

			CString node_name;
			CString code;
			while(node!=NULL)
			{
				node_name = node->Value(); // 节点名
				textnode = node->FirstChild();
				if(textnode!=NULL) // 节点值
					code = textnode->Value();
				else
					code = _T("");
				g_request_return.insert(RequestRet_Map::value_type(node_name,code));
				node = node->NextSibling();
			}
			if(get_return_field("ErrorCode",code))
			{
				return -1;
			}
			else
			{
				// 表示成功
				if("0000" == code)
				{
					return 0;
				}
				else
				{
					return 1;
				}
			}
		}else{
			return -3;
		}
	}else if (ret ==-10){
		return -10;
	}else if(ret ==-99){
		return -99;
	}else{
		return -100;
	}
}
//通用的写卡请求  使用于第三方转账 包括电控、上机上网等功能
SHORT CRF35OCXCtrl::CommonTransWriteCard(LPCTSTR url, LPCTSTR cardphyid,LPCTSTR txcnt,LPCTSTR outcardamount,LPCTSTR amount,LPCTSTR sdate3,LPCTSTR stime3,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc,LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ResetInfo();
	g_request_return.insert(RequestRet_Map::value_type("url",url));
	g_request_return.insert(RequestRet_Map::value_type("cardphyid",cardphyid));
	g_request_return.insert(RequestRet_Map::value_type("txCnt",txcnt));
	g_request_return.insert(RequestRet_Map::value_type("OutCardAmount",outcardamount));
	g_request_return.insert(RequestRet_Map::value_type("amount",amount));
	g_request_return.insert(RequestRet_Map::value_type("sdate3",sdate3));
	g_request_return.insert(RequestRet_Map::value_type("stime3",stime3));
	g_request_return.insert(RequestRet_Map::value_type("ipServer",ipServer));
	g_request_return.insert(RequestRet_Map::value_type("drtpPort",drtpPort));
	g_request_return.insert(RequestRet_Map::value_type("svrFunc",svrFunc));
	g_request_return.insert(RequestRet_Map::value_type("params",params));
	return do_write_card_and_request(url,cardphyid,txcnt,outcardamount,amount,sdate3,stime3,ipServer,drtpPort,svrFunc,params);
}

static void str2bcd(LPCTSTR str,unsigned char *bcd,int len)
{
	int i;
	char temp[3] = "";
	for (i = 0;i < len; ++i)
	{
		memcpy(temp,str+i*2,2);
		bcd[i] = atoi(temp);
	}
}
SHORT CRF35OCXCtrl::UpdateCardInfo(LPCTSTR CardPhyId, LPCTSTR feetype, LPCTSTR enddate)
{
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}

		ks_clearallfieldallmode();
		ks_setfieldwritemode(CF_FEETYPE);		
		ks_setfieldval(CF_FEETYPE,feetype);
		ks_setfieldwritemode(CF_EXPIREDATE);
		ks_setfieldval(CF_EXPIREDATE,enddate);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet==0 )
		{
			ks_beep();
			ks_clearallfieldwritemode();
			return 0;

		}else{
			return -5;
		}		
	}else{
		return -1;
	}
}

SHORT CRF35OCXCtrl::BeginUpdateCard(LPCTSTR cardphyid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString val;
	m_cardprop_map.clear();
	val = cardphyid;
	m_cardprop_map.insert(ParamName_Map::value_type(_T("cardphyid"),val));
	return 0;
}

SHORT CRF35OCXCtrl::SetCardProperty(LPCTSTR prop_name, LPCTSTR prop_value)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString val,val_name;

	val_name = prop_name;
	val = prop_value;
	//AfxMessageBox(val);
	m_cardprop_map.insert(ParamName_Map::value_type(val_name,val));

	return 0;
}

SHORT CRF35OCXCtrl::UpdateCard()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString val_name;
	CString val;
	CString cardphyid;
	ParamName_Map::iterator i;
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if(ret){
		return ret;
	}
	
	i = m_cardprop_map.find(_T("cardphyid"));
	if(i == m_cardprop_map.end())
	{
		return -1;
	}

	cardphyid = i->second;

	char sCardPhyID[17];
	if( ks_card(sCardPhyID)!=0 )
	{
		AfxMessageBox("寻卡失败");
		return 1;
	}
	CString nCardPhyid="";

	nCardPhyid.Format("%s",sCardPhyID);

	if(nCardPhyid!=cardphyid){
		AfxMessageBox(_T("卡号不正确"));
		return 2;
	}
	
	ks_clearallfieldallmode();
	for(i = m_cardprop_map.begin();i!=m_cardprop_map.end();++i)
	{
		val_name = i->first;
		val = i->second;
		if(val_name.Compare(_T("feetype"))==0)
		{
			ks_setfieldwritemode(CF_FEETYPE);
			ks_setfieldval(CF_FEETYPE,val);
		}
		else if(val_name.Compare(_T("expiredate"))==0)
		{
			ks_setfieldwritemode(CF_EXPIREDATE);
			ks_setfieldval(CF_EXPIREDATE,val);
		}
		else if(val_name.Compare(_T("deptno"))==0)
		{
			ks_setfieldwritemode(CF_DEPTCODE);
			ks_setfieldval(CF_DEPTCODE,val);
		}
		else if(val_name.Compare(_T("stuempno"))==0)
		{
			ks_setfieldwritemode(CF_STUEMPNO);
			ks_setfieldval(CF_STUEMPNO,val);
		}
		else
		{
			continue;
		}
	}
	CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
	ret=ks_writecard(sCardPhyID);
	if( ret==0 )
	{
		ks_beep();
		ks_clearallfieldwritemode();
		return 0;

	}else{
		char sMsg[256]="";
		ks_geterrmsg(sMsg);
		if(strlen(sMsg)<1)
		{
			AfxMessageBox("写卡错误，返回码="+rtnCstring(ret));
		}else{
			AfxMessageBox(sMsg);
		}
		return -5;
	}		
}


SHORT CRF35OCXCtrl::ReNetTransWriteCard(void)
{

	CString url,outcardamount,amount,cardphyid,txcnt,sdate3,stime3,ipServer,drtpPort,svrFunc,params;
	if(get_return_field("url",url))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("amount",amount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("cardphyid",cardphyid))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -2;
	}

	if(get_return_field("sdate3",sdate3))
	{
		// 没有金额字段
		return -2;
	}

	if(get_return_field("stime3",stime3))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("ipServer",ipServer))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("drtpPort",drtpPort))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("svrFunc",svrFunc))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("params",params))
	{
		// 没有卡号字段
		return -2;
	}

	return do_write_card_and_request(url,cardphyid,txcnt,outcardamount,amount,sdate3,stime3,ipServer,drtpPort,svrFunc,params);
}


SHORT CRF35OCXCtrl::ReverseNetTrans(LPCTSTR url)
{

	CString params;

	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	if(get_return_field("params",params))
	{
		// 没有卡号字段
		return -1;
	}
	if(_file_open){
		g_LogFile.WriteLogEx(0, "发送冲正交易=[%s]",params);
		g_LogFile.ToFlush();
	}
	CString strResult;
	CString t_params(params);

	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */




	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			node_name = node->Value(); // 节点名
			textnode = node->FirstChild();
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code))
		{
			return -1;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	else return -3;
}

typedef struct
{
	unsigned int single_max_amt;
	unsigned int day_max_amt;
}CONSUME_LIMIT;

static CONSUME_LIMIT g_consume_limit;

LONG CRF35OCXCtrl::getComsumerLimit(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LONG ret = 0;
	CString code(param);
	if (code=="single_max_amt")
	{
		ret = g_consume_limit.single_max_amt;
	}
	if (code=="day_max_amt")
	{
		ret = g_consume_limit.day_max_amt;
	}
	return ret;
}


void CRF35OCXCtrl::ResetconsumeLimitInfo(void)
{
	//全局初始化 /清空
	g_consume_limit.single_max_amt=0;
	g_consume_limit.day_max_amt=0;
}


SHORT CRF35OCXCtrl::ReadCardConsumerLimit(LPCTSTR CardPhyId)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here



	int ret = 0;
	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		char sCardPhyID[17];
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return 1;
		}


		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return 2;
		}

		ResetconsumeLimitInfo();

		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_SINGLEMAXAMT);
		ks_setfieldreadmode(CF_DAYMAXAMT);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret=ks_readcard();
		if(ret==0)
		{
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_SINGLEMAXAMT,sdata);
			if(ret==0){
				g_consume_limit.single_max_amt = atol(sdata);
			}else{
				return -1;
			}

			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_DAYMAXAMT,sdata);
			if(ret==0){
				g_consume_limit.day_max_amt = atol(sdata);
			}else{
				return -2;
			}
			return 0;

		}else{
			return -4;
		}

	}else{
		return -5;
	}
}

SHORT CRF35OCXCtrl::ResetConsumerLimit(LPCTSTR CardPhyId, LPCTSTR singleMaxAmt, LPCTSTR dayMaxAmt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());


	unsigned long snr = 0;
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}

		ks_clearallfieldallmode();
		ks_setfieldwritemode(CF_SINGLEMAXAMT);
		ks_setfieldval(CF_SINGLEMAXAMT,singleMaxAmt);
		ks_setfieldwritemode(CF_DAYMAXAMT);
		ks_setfieldval(CF_DAYMAXAMT,dayMaxAmt);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet==0 )
		{
			ks_beep();
			ks_clearallfieldwritemode();
			return 0;

		}else{
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				AfxMessageBox(sMsg);
			}
			return -5;
		}		
	}else{
		return -1;
	}

}

LONG CRF35OCXCtrl::ReadCardSidyNo(LPCTSTR CardPhyId)
{
	int ret = 0;
	int sidyno = 0;
	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		char sCardPhyID[17];
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -1;
		}


		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -2;
		}


		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_SUBSIDYNO);
		memset(sdata,0,sizeof sdata);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret=ks_readcard();
		if(ret==0)
		{
			ret=ks_getfieldval(CF_SUBSIDYNO,sdata);
			if(ret==0){
				sidyno = atol(sdata);
				return sidyno;

			}else{
				return -3;
			}

		}else{
			return -4;
		}

	}else{
		return -5;
	}
}

SHORT CRF35OCXCtrl::RewriteSidy(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}

	CString outcardamount,amount,sdate3,stime3,cardphyid,sidyno,txcnt,ipServer,drtpPort,svrFunc;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -1;
	}
	
	if(get_return_field("SidyAmount",amount))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("sdate3",sdate3))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("stime3",stime3))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("cardphyid",cardphyid))
	{
		// 没有卡号字段
		return -1;
	}
	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -1;
	}
	if(get_return_field("sidyno",sidyno))
	{
		// 没有卡号字段
		return -1;
	}
	if(get_return_field("ipServer",ipServer))
	{
		// 没有卡号字段
		return -1;
	}
	if(get_return_field("drtpPort",drtpPort))
	{
		// 没有卡号字段
		return -1;
	}
	if(get_return_field("svrFunc",svrFunc))
	{
		// 没有卡号字段
		return -1;
	}
	if(_file_open){
		g_LogFile.WriteLogEx(0, "补助信息重写卡余额cardphyid=[%s],amount=[%s]",cardphyid,amount);
		g_LogFile.ToFlush();
	}

	// TODO: Add your dispatch handler code here
	int ret = WriteSidy(outcardamount,amount,sdate3,stime3,cardphyid,sidyno,txcnt,ipServer,drtpPort,svrFunc);
	return ret;
}

short CRF35OCXCtrl::WriteSidy(LPCTSTR outcardamount,LPCTSTR amount,LPCTSTR sdate,LPCTSTR stime,LPCTSTR cardphyid,LPCTSTR sidyno,LPCTSTR ssd_cardcnt,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc){

	char sCardNo[20]="";
	ST_TRANSPACK payment;
	unsigned long snr=0;
	memset(&payment,0,sizeof payment);

	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
		_file_open = true;
	}

	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "领取补助发生错误,错误信息=[%s],cardphyid=[%s]","寻卡失败",cardphyid);
				g_LogFile.ToFlush();
			}

			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			if(_file_open){
				g_LogFile.WriteLogEx(0, "领取补助发生错误,错误信息=[%s],cardphyid=[%s]","卡号不正确",cardphyid);
				g_LogFile.ToFlush();
			}
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
		const char * ip_server = ipServer;
		int svrport = atoi(drtpPort);
		int svrfunc = atoi(svrFunc);
		ks_comminit(ip_server,svrport,svrfunc);
		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDNO);
		ks_setfieldreadmode(CF_DPSCNT);
		ks_setfieldreadmode(CF_PAYCNT);
		ks_setfieldreadmode(CF_CARDBAL);
		nRet = ks_readcard();
		if(nRet!=0)
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "领取补助发生错误,错误信息=[%s],cardphyid=[%s]","读卡信息失败",cardphyid);
				g_LogFile.ToFlush();
			}
			return -4;
		}
		strcpy(payment.sCardPhyID,sCardPhyID);
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
		payment.nAftBalance = atoi(outcardamount);

		strcpy(payment.sTransDate,sdate);
		strcpy(payment.sTransTime,stime);
		payment.nFundType = 1;
		payment.nTransAmt = atoi(amount); //1 分
		char termno[13]={0};
		ks_readpsamtermno(termno,0);
		strcpy(payment.sTermno,termno);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_setcardbal(&payment);
		if(nRet!=0)
		{		
			
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				AfxMessageBox(sMsg);
			}
			if(_file_open){
				g_LogFile.WriteLogEx(0, "领取补助写卡错误，返回码ret=[%d],物理id=[%s],补助金额=[%s],出卡值=[%s],错误信息=[%s]",nRet,cardphyid,amount,outcardamount,sMsg);
				g_LogFile.ToFlush();
			}
			return -1;
		}else{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "补助领取成功,cardphyid=[%s]",cardphyid);
				g_LogFile.ToFlush();
			}
			ks_beep();
			return 0;
		}

	}else{
	if(_file_open){
		g_LogFile.WriteLogEx(0, "打开串口失败 ret=[%d]",ret);
		g_LogFile.ToFlush();
	}
		return -1;
	}
}

typedef struct  
{
	int old_card_no;
	int old_card_balance;
	char old_card_name[200];
}OLD_CARD_INFO;

static 	OLD_CARD_INFO g_old_card_info;

void CRF35OCXCtrl::ResetOldCardInfo(void)
{
	memset(&g_old_card_info,0,sizeof g_old_card_info);
}



typedef int (__stdcall* LPXsqQkIntf_Init)(int IcDev, int ReInitCardReader,int CardReaderBeep,int CardReaderKeySetIndex);
typedef int (__stdcall* LPXsqQkIntf_ReadCard)(int *CardNo, int *CardBalance,char *Pwd,char *Name);
typedef int (__stdcall* LPXsqQkIntf_GetMoneyFromCard)(int CardNo, int Money,char *Pwd,char *Name);
typedef int (__stdcall* LPXsqQkIntf_Exit)();


LPXsqQkIntf_Init XsqQkIntf_Init = NULL;
LPXsqQkIntf_ReadCard XsqQkIntf_ReadCard = NULL;
LPXsqQkIntf_GetMoneyFromCard XsqQkIntf_GetMoneyFromCard = NULL;
LPXsqQkIntf_Exit XsqQkIntf_Exit = NULL;


HINSTANCE hXsqQkIntfDLL = NULL;



SHORT CRF35OCXCtrl::ReadOldCardInfo(LPCTSTR oldcardpwd)
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int ret;
	
	ret = LoadXsqQkIntfDLL();

	if (ret != 0)
	{
		if (-1001 == ret) { ::AfxMessageBox("加载XsqQkIntf.dll失败"); }
		else if (-1002 == ret) { ::AfxMessageBox("加载XsqQkIntf.dll函数出错"); }
		else { ::AfxMessageBox("未知错误"); }

		return -1;
	}

	ret = XsqQkIntf_Init(0,1,1,1);
	if (ret!=0)
	{
		::AfxMessageBox("初始化读卡器失败");
		return -2;
	}

	char cardpwd[20];
	strncpy(cardpwd,oldcardpwd,19);
	cardpwd[19]=0;


	ResetOldCardInfo();
	ret = XsqQkIntf_ReadCard(&g_old_card_info.old_card_no,&g_old_card_info.old_card_balance,cardpwd,g_old_card_info.old_card_name);

	
	if (ret!=0)
	{
		if (ret==1){
			::AfxMessageBox("初始化读卡器失败");
		}else if (ret==2){
			::AfxMessageBox("读卡器操作失败");
		}else if (ret==3){
			::AfxMessageBox("卡片未被正确放置");
		}else if(ret==4){
			::AfxMessageBox("卡片错误");
		}else if(ret==5){
			::AfxMessageBox("读卡失败");
		}else if(ret==6){
			::AfxMessageBox("未注册卡片或密码错误");
		}else if(ret==7){
			::AfxMessageBox("卡片未挂失或挂失不足48小时");
		}else if(ret==8){
			::AfxMessageBox("数据库操作失败");
		}else if(ret==9){
			::AfxMessageBox("卡片未注册");
		}else if(ret==11){
			::AfxMessageBox("错误的配置文件");
		}else if(ret==12){
			::AfxMessageBox("密码错误");
		}else if(ret==15){
			::AfxMessageBox("老卡帐户异常,需要到卡中心预处理");
		}
		FreeXsqQkIntfDLL();
		return ret;
	}
	FreeXsqQkIntfDLL();
    return 0;
}

BSTR CRF35OCXCtrl::getOldCardInfo(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	LONG ret = 0;
	CString retStr=_T("");
	CString code(param);
	if (code=="old_card_no")
	{
		retStr.Format("%d",g_old_card_info.old_card_no);
		//ret = g_old_card_info.old_card_no;
	}else if (code=="old_card_balance")
	{
		retStr.Format("%d",g_old_card_info.old_card_balance);
		//ret = g_old_card_info.old_card_balance;
	}else if (code=="old_card_name")
	{
		retStr.Format("%s",g_old_card_info.old_card_name);
		//ret = g_old_card_info.old_card_name;
	}
	return retStr.AllocSysString();
}




SHORT CRF35OCXCtrl::getMoneyFromOldCard(LPCTSTR CardNo, LPCTSTR Money, LPCTSTR cardPwd,LPCTSTR newCardName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int ret;

	ret = LoadXsqQkIntfDLL();

	if (ret != 0)
	{
		if (-1001 == ret) { ::AfxMessageBox("加载XsqQkIntf.dll失败"); }
		else if (-1002 == ret) { ::AfxMessageBox("加载XsqQkIntf.dll函数出错"); }
		else { ::AfxMessageBox("未知错误"); }

		return -1;
	}

	ret = XsqQkIntf_Init(0,true,true,1);
	if (ret!=0)
	{
		::AfxMessageBox("初始化读卡器失败");
		return -2;
	}

	ret = XsqQkIntf_GetMoneyFromCard(atoi(CardNo),atoi(Money),(LPTSTR)(LPCTSTR)cardPwd,(LPTSTR)(LPCTSTR)newCardName);

	if (ret==0)
	{
		FreeXsqQkIntfDLL();
		return 0;
	}else{		
		if (ret==1){
			::AfxMessageBox("初始化读卡器失败");
		}else if (ret==2){
			::AfxMessageBox("读卡器操作失败");
		}else if (ret==3){
			::AfxMessageBox("卡片未被正确放置");
		}else if(ret==4){
			::AfxMessageBox("卡片错误");
		}else if(ret==5){
			::AfxMessageBox("读卡失败");
		}else if(ret==6){
			::AfxMessageBox("未注册卡片或密码错误");
		}else if(ret==7){
			::AfxMessageBox("卡片未挂失或挂失不足48小时");
		}else if(ret==8){
			::AfxMessageBox("数据库操作失败");
		}else if(ret==9){
			::AfxMessageBox("卡片未注册");
		}else if(ret==11){
			::AfxMessageBox("错误的配置文件");
		}else if(ret==12){
			::AfxMessageBox("密码错误");
		}else if(ret==13){
			::AfxMessageBox("错误金额");
		}else if(ret==14){
			::AfxMessageBox("新老卡对应的姓名不符");
		}else if(ret==15){
			::AfxMessageBox("老卡帐户异常,需要到卡中心预处理");
		}

		FreeXsqQkIntfDLL();
		return ret;
	}

}



void CRF35OCXCtrl::FreeXsqQkIntfDLL(void)
{
	if(hXsqQkIntfDLL)
	{	
		//XsqQkIntf_Exit();
		FreeLibrary(hXsqQkIntfDLL);
		hXsqQkIntfDLL = NULL;
	}
}

int CRF35OCXCtrl::LoadXsqQkIntfDLL(void)
{

	if (hXsqQkIntfDLL)
	{
		return 0;
	}
	hXsqQkIntfDLL = LoadLibrary("XsqQkIntf.dll");
	if (!hXsqQkIntfDLL)
	{
		return -101;
	}

	XsqQkIntf_Init = (LPXsqQkIntf_Init)GetProcAddress(hXsqQkIntfDLL, "XsqQkIntf_Init");
	XsqQkIntf_ReadCard = (LPXsqQkIntf_ReadCard)GetProcAddress(hXsqQkIntfDLL, "XsqQkIntf_ReadCard");
	XsqQkIntf_GetMoneyFromCard = (LPXsqQkIntf_GetMoneyFromCard)GetProcAddress(hXsqQkIntfDLL, "XsqQkIntf_GetMoneyFromCard");
	XsqQkIntf_Exit = (LPXsqQkIntf_Exit)GetProcAddress(hXsqQkIntfDLL, "XsqQkIntf_GetMoneyFromCard");

	if (!XsqQkIntf_Init || !XsqQkIntf_ReadCard || !XsqQkIntf_GetMoneyFromCard || !XsqQkIntf_Exit)
	{
		FreeLibrary(hXsqQkIntfDLL);
		hXsqQkIntfDLL = NULL;
		return -102;
	}
	return 0;
}
//银行转账用
int CRF35OCXCtrl::do_request_and_write_card(LPCTSTR url, LPCTSTR cardphyid,LPCTSTR outcardamount,LPCTSTR dptCardCnt, LPCTSTR params)
{
	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	CLogFile g_LogFile;
	char time_msg[20] = "";
	CUtilTime util_time;
	util_time.GetLocalTime(time_msg);
	bool _file_open = false;
	bala.Format("%d",g_packet_info.cardbal);
	t_params += "&cardBala="+bala+"&dptCardCnt="+dptCardCnt;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
		_file_open = true;
	}

	if(_file_open){
		g_LogFile.WriteLogEx(0, "[%s],param=[%s],cardphyid=[%s]",time_msg,t_params,cardphyid);
		g_LogFile.ToFlush();
	}
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */
	
	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			if(_file_open){
				g_LogFile.WriteLogEx(0, "%s","网络异常，请求发送失败！");
				g_LogFile.ToFlush();
			}
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	if(_file_open){
		g_LogFile.WriteLogEx(0, "返回结果=[%s]",strResult);
		g_LogFile.ToFlush();
	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code)){
			if(_file_open){
				g_LogFile.WriteLogEx(0, "[%s]","结果中ErrorCode未取到,发生未预知的错误");
				g_LogFile.ToFlush();
			}
			return -2;
		}else{
			// 表示成功
			if("0000" == code){
				CString outcardamount,amount,sdate3,stime3,cardphyid,txcnt,ipServer,drtpPort,svrFunc;
				if(get_return_field("OutCardAmount",outcardamount))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("amount",amount))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("sdate3",sdate3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("stime3",stime3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("cardphyid",cardphyid))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("dptCardCnt",txcnt))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("ipServer",ipServer))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("drtpPort",drtpPort))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("svrFunc",svrFunc))
				{
					// 没有卡号字段
					return -2;
				}
				int ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);

				if (ret==0)
				{
					//写卡成功
					if(_file_open){
						g_LogFile.WriteLogEx(0, "操作结果=[%s]","写卡成功ret=0");
						g_LogFile.ToFlush();
					}
					return 0;
				}else{				
					if(_file_open){
						g_LogFile.WriteLogEx(0, "操作结果,写卡失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					return -1;
				}
			}else{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "后台返回错误码ErrorCode=[%s]",code);
					g_LogFile.ToFlush();
				}
				return 1;
			}
		}
	}
	if(_file_open){
		g_LogFile.WriteLogEx(0, "[%s]","返回信息为空ret=2");
		g_LogFile.ToFlush();
	}
	return 2;

}


SHORT CRF35OCXCtrl::CardTransWriteCard(LPCTSTR outcardamount, LPCTSTR cardphyid, LPCTSTR txcnt,LPCTSTR amount,LPCTSTR sdate3,LPCTSTR stime3,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc)
{
	return  WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);;

}


SHORT CRF35OCXCtrl::UpdateDeadlineDate(LPCTSTR url, LPCTSTR CardPhyId, LPCTSTR enddate, LPCTSTR param)
{

	unsigned long snr = 0;
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
	int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}

		ks_clearallfieldallmode();
		ks_setfieldwritemode(CF_EXPIREDATE);
		ks_setfieldval(CF_EXPIREDATE,enddate);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet!=0 )
		{
			return -5;
		}else{
			ks_beep();
			ks_clearallfieldwritemode();
			//更新成功

			CString strResult;
			CString t_params(param);
			CString t_cardphyid(CardPhyId);
			CString t_enddate(enddate);
			if(t_params==""){
				t_params = "cardphyid="+t_cardphyid+"&enddate="+t_enddate;
			}else{
				t_params += "&cardphyid="+t_cardphyid+"&enddate="+t_enddate;
			}


			CURL *curl;
			CURLcode res;
			struct MemoryStruct chunk;
			int retries = 3;

			chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
			chunk.size = 0;    /* no data at this point */

			curl = curl_easy_init();

			if (curl)
			{
				curl_easy_setopt(curl,CURLOPT_URL,url);
				curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

				curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

				curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
				/* send all data to this function  */
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

				/* we pass our 'chunk' struct to the callback function */
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

				res = curl_easy_perform(curl);

				if(CURLE_OK!=res){
					//网络不通
					return 2;			
				}

				curl_easy_cleanup(curl);

				// TODO: Add your dispatch handler code here
				strResult.Format("%s",chunk.memory);
				if (chunk.memory)
				{
					free(chunk.memory);
				}	

			}

			//全局初始化 /清空
			ResetInfo();
			if(strResult!=""){
				TiXmlDocument doc;
				doc.Parse(strResult);
				TiXmlNode* node = 0;
				TiXmlNode* textnode = 0;
				TiXmlNode* node1 = 0;
				TiXmlElement* todoElement = 0;
				TiXmlElement* itemElement = 0;

				todoElement = doc.RootElement();
				node = todoElement->FirstChild();//head节点

				// 第一个节点
				node = node->FirstChild();

				CString node_name;
				CString code;
				while(node!=NULL)
				{
					textnode = node->FirstChild();
					node_name = node->Value(); // 节点名
					if(textnode!=NULL) // 节点值
						code = textnode->Value();
					else
						code = _T("");
					g_request_return.insert(RequestRet_Map::value_type(node_name,code));
					node = node->NextSibling();
				}
				if(get_return_field("ErrorCode",code))
				{
					return -2;
				}
				else
				{
					// 表示成功
					if("0000" == code)
					{
						return 0;
					}
					else{
						//失败
						return 1;
					}
				}
			}
			return 2;
		}
	}else{
		return -1;
	}
}

BSTR CRF35OCXCtrl::getDeadlineDate(LPCTSTR url,LPCTSTR CardPhyId,LPCTSTR params)
{


	CString strResult;
	CString retResult("");
	CString t_params(params);
	CString t_cardphyid(CardPhyId);
	if (t_params=="")
	{
		t_params = "cardphyid="+t_cardphyid;
	}else{
		t_params += "&cardphyid="+t_cardphyid;
	}

	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return retResult.AllocSysString();			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		return  strResult.AllocSysString();
	}
	return retResult.AllocSysString();
}
BSTR CRF35OCXCtrl::GetVersion(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;

	strResult.Format("%s [%s %s]",OCX_VERSION,__DATE__,__TIME__);
	// TODO: Add your dispatch handler code here

	return strResult.AllocSysString();
}
/*******************************************/
//999水控钱包
/******************************************/
typedef struct  
{
	int nBalance;
	int nCnt;
}SMALL_PACKET;

static SMALL_PACKET g_small_packet;

void CRF35OCXCtrl::RetsetSmallPacketInfo(void)
{

	memset(&g_small_packet,0,sizeof g_small_packet);
}

SHORT CRF35OCXCtrl::ReadSmallPacket(SHORT nPacketNo,LPCTSTR cardno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return 0;
}

LONG CRF35OCXCtrl::GetSmallPacketInfo(LPCTSTR param)
{
	LONG ret = 0;
	CString code(param);
	if (code=="nBalance")
	{
		ret = g_small_packet.nBalance;
	}
	if (code=="nCnt")
	{
		ret = g_small_packet.nCnt;
	}
	return ret;
}
//kl 水控还用
SHORT CRF35OCXCtrl::WaterTransWriteCard(LPCTSTR url, LPCTSTR cardphyid, LPCTSTR param)
{
	CString strResult;
	CString t_params(param);
	CString bala ="";
	CString txCnt = "";
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code))
		{
			return -2;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				CString outcardamount,outcardamount1,amount,cardphyid,txcnt,txcnt1,sdate3,stime3,ipServer,drtpPort,svrFunc;
				if(get_return_field("OutCardAmount",outcardamount))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("OutCardAmount1",outcardamount1))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("amount",amount))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("cardphyid",cardphyid))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("txCnt",txcnt))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("txCnt1",txcnt1))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("sdate3",sdate3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("stime3",stime3))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("ipServer",ipServer))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("drtpPort",drtpPort))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("svrFunc",svrFunc))
				{
					// 没有卡号字段
					return -2;
				}
				int ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);
				if (ret==0)
				{
					//写卡成功
					ret = WriteWaterPacket(outcardamount1,cardphyid,txcnt1);
					if (ret==0)
					{
						return 0;
					}else{
						return -3;
					}

				}else{				
					return -1;
				}
			}else{
				//失败
				return 1;
			}
		}
	}
	return 2;
}
//kl 水控用
SHORT CRF35OCXCtrl::ReWriteWaterTrans(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString outcardamount,outcardamount1,amount,cardphyid,txcnt,txcnt1,sdate3,stime3,ipServer,drtpPort,svrFunc;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("OutCardAmount1",outcardamount1))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("amount",amount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("cardphyid",cardphyid))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt1",txcnt1))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("sdate3",sdate3))
	{
		// 没有金额字段
		return -2;
	}

	if(get_return_field("stime3",stime3))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("ipServer",ipServer))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("drtpPort",drtpPort))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("svrFunc",svrFunc))
	{
		// 没有卡号字段
		return -2;
	}
	int ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);
	if (ret==0)
	{
		//写卡成功
		ret = WriteWaterPacket(outcardamount1,cardphyid,txcnt1);
		if (ret==0)
		{
			return 0;
		}else{
			return -3;
		}

	}else{				
		return -1;
	}
}
//各大功能都需要  报告写卡失败，3.0后台未必实现
SHORT CRF35OCXCtrl::ReportWriteCardFailure(LPCTSTR url, LPCTSTR params)
{
	CString strResult;

	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();
	CString t_params(params);

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,10);

		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}
		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}
	
	ResetInfo();
	//全局初始化 /清空
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
	}

	return 0;
}

// 水控钱包写卡
short CRF35OCXCtrl::WriteWaterPacket(LPCTSTR outcardamount,LPCTSTR cardphyid,LPCTSTR txcnt)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char phyid[17];
	int ret = 0;
	//KSCardReader ksCardRead(m_nPortNo);
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		ret = ks_card(phyid);
		if(ret){
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",phyid);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){			
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
		int water_bala = atoi(outcardamount);
		int water_cnt = atoi(txcnt);
			g_waterctl_packet_info.money = water_bala;
			g_waterctl_packet_info.addcount = water_cnt+1;
	   CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret = ks_water_writemoney(1,&g_waterctl_packet_info);
		if(ret)
		{
			AfxMessageBox("水控钱包读取失败");
			return ret;
		}else{
			return 0;
		}		

	}else{
		return -1;
	}
}
//银行卡转账
SHORT CRF35OCXCtrl::BankTransWriteCard(LPCTSTR url, LPCTSTR cardphyid, LPCTSTR outcardamount, LPCTSTR dptCardCnt, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return do_request_and_write_card(url,cardphyid,outcardamount,dptCardCnt,params);
}


/**
	南大新生换卡功能相关
**/

typedef struct
{
	CString showcardno;
}SHOW_CARD_NO_REF;

typedef struct
{
	CString o_cardphyid;
	CString n_cardphyid;
	CString n_showcardno;
	CString o_dpt_card_cnt;
	CString o_pay_card_cnt;
	CString o_cardBala;
	CString retcode;

}CHANGE_CARD_INFO;


static SHOW_CARD_NO_REF g_show_card_no_ref;
static CHANGE_CARD_INFO g_change_card_info;

void CRF35OCXCtrl::RetsetShowCardNoRef(void)
{
	g_show_card_no_ref.showcardno="";
}
void CRF35OCXCtrl::RetsetChangeCardInfo(void)
{
	g_change_card_info.n_cardphyid="";
	g_change_card_info.n_showcardno="";
	g_change_card_info.o_cardBala="";
	g_change_card_info.o_cardphyid="";
	g_change_card_info.o_pay_card_cnt="";
	g_change_card_info.o_dpt_card_cnt="";
	g_change_card_info.retcode="0";
}


SHORT CRF35OCXCtrl::ReadShowCardno(void)
{
AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char sdata[128];
	char phyid[17];
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		ret = ks_card(phyid);
		if(ret){
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);

		RetsetShowCardNoRef();

		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_SHOWCARDNO);
		ret=ks_readcard();
		if(ret==0)
		{					
			CString tmp ="";
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_SHOWCARDNO,sdata);
			if(ret==0){
				tmp="";
				tmp.Format("%s",sdata);
				g_show_card_no_ref.showcardno=tmp;
			}else{
				return -2;
			}			
			return 0;

		}else{
			return -3;
		}


	}else{
		return -1;
	}
}

BSTR CRF35OCXCtrl::GetCardStateInfo(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString strResult;
	if(param="showcardno"){
		strResult = g_show_card_no_ref.showcardno;
	}else{
		strResult = "";
	}
	return strResult.AllocSysString();
}

SHORT CRF35OCXCtrl::CardChangeClearOldCard(LPCTSTR cardphyid,LPCTSTR newcardphyid, LPCTSTR showcardno, LPCTSTR dpt_card_cnt,LPCTSTR pay_card_cnt, LPCTSTR cardBala,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc)
{

	//保存必要的信息
	RetsetChangeCardInfo();
	CString o_cardphyid(cardphyid);
	CString n_cardphyid(newcardphyid);
	CString n_showcardno(showcardno);
	CString o_dpt_card_cnt(dpt_card_cnt);
	CString o_pay_card_cnt(pay_card_cnt);
	CString o_cardBala(cardBala);
	g_change_card_info.o_cardphyid=o_cardphyid;
	g_change_card_info.n_cardphyid=n_cardphyid;
	g_change_card_info.n_showcardno=n_showcardno;
	g_change_card_info.o_dpt_card_cnt=o_dpt_card_cnt;
	g_change_card_info.o_pay_card_cnt=o_pay_card_cnt;
	g_change_card_info.o_cardBala=o_cardBala;	
	
	CString paramKey="";
	get_return_field("paramKey",paramKey);

	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		CLogFile g_LogFile;
		bool _file_open = false;
		if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
				_file_open = true;
		}

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )                                                                                                       
		{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[%s],cardphyid=[%s]","寻卡失败",cardphyid);
					g_LogFile.ToFlush();
				}
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[%s],cardphyid=[%s],ncardphyid=[%s]","卡号不正确",cardphyid,nCardPhyid);
					g_LogFile.ToFlush();
				}
			AfxMessageBox(_T("卡号不正确"));			
			return -3;
		}
		const char * ip_server = ipServer;
		int svrport = atoi(drtpPort);
		int svrfunc = atoi(svrFunc);
		ks_comminit(ip_server,svrport,svrfunc);
		ST_TRANSPACK payment;
		memset(&payment,0,sizeof payment);
		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDNO);
		ks_setfieldreadmode(CF_DPSCNT);
		ks_setfieldreadmode(CF_PAYCNT);
		ks_setfieldreadmode(CF_CARDBAL);
		ks_setmifare1key((LPCTSTR)paramKey);
		char sCardNo[20]="";
		nRet = ks_readcard();
		if(nRet!=0)
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "写卡信息发生错误,错误信息=[%s],cardphyid=[%s]","卡信息读取失败",cardphyid);
				g_LogFile.ToFlush();
			}
			AfxMessageBox(_T("卡信息读取失败"));
			return -4;
		}
		strcpy(payment.sCardPhyID,sCardPhyID);
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
		payment.nAftBalance = 0;

		strcpy(payment.sTransDate,"19700101");
		strcpy(payment.sTransTime,"000000");
		payment.nFundType = 1;
		payment.nTransAmt = payment.nBefBalance; //1 元
		char termno[13]={0};
		ks_readpsamtermno(termno,0);
		strcpy(payment.sTermno,termno);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_setcardbal(&payment);
		if(nRet!=0)
		{		
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]","写卡错误，返回码="+nRet,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox(sMsg);
			}

			if(payment.cGetProveFlag==1){
				//中途拔卡
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,中途拔卡,cardphyid=[%s]",cardphyid);
					g_LogFile.ToFlush();
				}
				return -99;
			}		
				
			return -10;
		}else{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "写卡信息结果写卡成功,cardphyid=[%s]",cardphyid);
				g_LogFile.ToFlush();
			}
		}

		//const char * cardno = "0";
		const char * cardstatus = "1";
		ks_clearallfieldallmode();
		//ks_setfieldwritemode(CF_CARDNO);
		//ks_setfieldval(CF_CARDNO,cardno);
		ks_setfieldwritemode(CF_CARDSTATUS);
		ks_setfieldval(CF_CARDSTATUS,cardstatus);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet==0 )
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "清除临时卡信息成功,cardphyid=[%s]",cardphyid);
				g_LogFile.ToFlush();
			}
			CString pursetype1="0";
			CString pursetype2="0";
			CString pursetype3="0";
			if(!get_return_field("pursetype1",pursetype1)&&pursetype1!="0")
			{
				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,"");
				g_waterctl_packet_info.addcount = 0;
				g_waterctl_packet_info.price1 = 100;
				g_waterctl_packet_info.price2 = 100;
				g_waterctl_packet_info.price3 = 100;
				strcpy(g_waterctl_packet_info.expireddate,"");

				ret = ks_water_writemoney(atoi(pursetype1),&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"清除小钱包失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包-1-清除失败");
					return ret;
				}
			}

			if(!get_return_field("pursetype2",pursetype2)&&pursetype2!="0")
			{
				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,"");
				g_waterctl_packet_info.addcount = 0;
				g_waterctl_packet_info.price1 = 100;
				g_waterctl_packet_info.price2 = 100;
				g_waterctl_packet_info.price3 = 100;
				strcpy(g_waterctl_packet_info.expireddate,"");

				ret = ks_water_writemoney(atoi(pursetype2),&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"清除小钱包失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包-2-清除失败");
					return ret;
				}
			}

			if(!get_return_field("pursetype3",pursetype3)&&pursetype3!="0")
			{
				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,"");
				g_waterctl_packet_info.addcount = 0;
				g_waterctl_packet_info.price1 = 100;
				g_waterctl_packet_info.price2 = 100;
				g_waterctl_packet_info.price3 = 100;
				strcpy(g_waterctl_packet_info.expireddate,"");

				ret = ks_water_writemoney(atoi(pursetype3),&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"清除小钱包失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包-3-清除失败");
					return ret;
				}
			}

	
			ks_beep();
			ks_clearallfieldwritemode();
			return 0;

		}else{
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[写卡错误,返回码=[%d],cardphyid=[%s]",nRet,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox(sMsg);
			}
			
			return -5;
		}

	}else{
		return -1;
	}

}

SHORT CRF35OCXCtrl::ReCardChangeClearOldCard(void)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString paramKey="";
	get_return_field("paramKey",paramKey);
	CString cardphyid=g_change_card_info.o_cardphyid;

	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		CLogFile g_LogFile;
		bool _file_open = false;
		if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
				_file_open = true;
		}

		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )                                                                                                       
		{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[%s],cardphyid=[%s]","寻卡失败",cardphyid);
					g_LogFile.ToFlush();
				}
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[%s],cardphyid=[%s],ncardphyid=[%s]","卡号不正确",cardphyid,nCardPhyid);
					g_LogFile.ToFlush();
				}
			AfxMessageBox(_T("卡号不正确"));			
			return -3;
		}

		ST_TRANSPACK payment;
		memset(&payment,0,sizeof payment);
		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDNO);
		ks_setfieldreadmode(CF_DPSCNT);
		ks_setfieldreadmode(CF_PAYCNT);
		ks_setfieldreadmode(CF_CARDBAL);
		ks_setmifare1key((LPCTSTR)paramKey);
		char sCardNo[20]="";
		nRet = ks_readcard();
		if(nRet!=0)
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "写卡信息发生错误,错误信息=[%s],cardphyid=[%s]","卡信息读取失败",cardphyid);
				g_LogFile.ToFlush();
			}
			AfxMessageBox(_T("卡信息读取失败"));
			return -4;
		}
		strcpy(payment.sCardPhyID,sCardPhyID);
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
		payment.nAftBalance = 0;

		strcpy(payment.sTransDate,"19700101");
		strcpy(payment.sTransTime,"000000");
		payment.nFundType = 1;
		payment.nTransAmt = payment.nBefBalance; //1 元
		char termno[13]={0};
		ks_readpsamtermno(termno,0);
		strcpy(payment.sTermno,termno);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_setcardbal(&payment);
		if(nRet!=0)
		{		
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]","写卡错误，返回码="+nRet,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox(sMsg);
			}

			if(payment.cGetProveFlag==1){
				//中途拔卡
				if(_file_open){
					g_LogFile.WriteLogEx(0, "写卡信息发生错误,中途拔卡,cardphyid=[%s]",cardphyid);
					g_LogFile.ToFlush();
				}
				return -99;
			}		
				
			return -10;
		}else{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "写卡信息结果写卡成功,cardphyid=[%s]",cardphyid);
				g_LogFile.ToFlush();
			}
		}

		//const char * cardno = "0";
		const char * cardstatus = "1";
		ks_clearallfieldallmode();
		//ks_setfieldwritemode(CF_CARDNO);
		//ks_setfieldval(CF_CARDNO,cardno);
		ks_setfieldwritemode(CF_CARDSTATUS);
		ks_setfieldval(CF_CARDSTATUS,cardstatus);
		ks_setmifare1key((LPCTSTR)paramKey);
		nRet=ks_writecard(sCardPhyID);
		if( nRet==0 )
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "清除临时卡信息成功,cardphyid=[%s]",cardphyid);
				g_LogFile.ToFlush();
			}
			CString pursetype1="0";
			CString pursetype2="0";
			CString pursetype3="0";
			if(!get_return_field("pursetype1",pursetype1)&&pursetype1!="0")
			{
				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,"");
				g_waterctl_packet_info.addcount = 0;
				g_waterctl_packet_info.price1 = 100;
				g_waterctl_packet_info.price2 = 100;
				g_waterctl_packet_info.price3 = 100;
				strcpy(g_waterctl_packet_info.expireddate,"");

				ret = ks_water_writemoney(atoi(pursetype1),&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"清除小钱包失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包-1-清除失败");
					return ret;
				}
			}

			if(!get_return_field("pursetype2",pursetype2)&&pursetype2!="0")
			{
				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,"");
				g_waterctl_packet_info.addcount = 0;
				g_waterctl_packet_info.price1 = 100;
				g_waterctl_packet_info.price2 = 100;
				g_waterctl_packet_info.price3 = 100;
				strcpy(g_waterctl_packet_info.expireddate,"");

				ret = ks_water_writemoney(atoi(pursetype2),&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"清除小钱包失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包-2-清除失败");
					return ret;
				}
			}

			if(!get_return_field("pursetype3",pursetype3)&&pursetype3!="0")
			{
				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,"");
				g_waterctl_packet_info.addcount = 0;
				g_waterctl_packet_info.price1 = 100;
				g_waterctl_packet_info.price2 = 100;
				g_waterctl_packet_info.price3 = 100;
				strcpy(g_waterctl_packet_info.expireddate,"");

				ret = ks_water_writemoney(atoi(pursetype3),&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"清除小钱包失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包-3-清除失败");
					return ret;
				}
			}

	
			ks_beep();
			ks_clearallfieldwritemode();
			return 0;

		}else{
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[写卡错误,返回码=[%d],cardphyid=[%s]",nRet,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
			}else{
				if(_file_open){
					g_LogFile.WriteLogEx(0, "清除临时卡信息发生错误,错误信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
					g_LogFile.ToFlush();
				}
				AfxMessageBox(sMsg);
			}
			
			return -5;
		}

	}else{
		return -1;
	}
}

SHORT CRF35OCXCtrl::CheckNewCard(void)
{

	CString paramKey="";
	get_return_field("paramKey",paramKey);
	CString newcardphyid=g_change_card_info.n_cardphyid;

	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )                                                                                                       
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",newcardphyid);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));			
			return -3;
		}else{
			return 0;
		}	
	}else{
		return 3;
	}
}

SHORT CRF35OCXCtrl::CardChangeNewCard(LPCTSTR url)
{
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	CString strResult;
	CString t_params("");
	CString cardphyid=g_change_card_info.o_cardphyid;
	CString cardBala=g_change_card_info.o_cardBala;
	CString pay_card_cnt=g_change_card_info.o_pay_card_cnt;
	CString dpt_card_cnt=g_change_card_info.o_dpt_card_cnt;
	CString showcardno=g_change_card_info.n_showcardno;
	CString n_cardphyid=g_change_card_info.n_cardphyid;

	CString pursetype1="0";
	CString pursetype2="0";
	CString pursetype3="0";
	if(get_return_field("pursetype1",pursetype1))
	{
		pursetype1="0";
	}
	if(get_return_field("pursetype2",pursetype2))
	{
		pursetype2="0";
	}
	if(get_return_field("pursetype3",pursetype3))
	{
		pursetype3="0";
	}
	CString water_str1="";
	CString water_str2="";
	CString water_str3="";
	if(pursetype1!="0"){
		CString water_money1="0";
		CString water_price11="100";
		CString water_price21="100";
		CString water_price31="100";
		if(get_return_field("water_money1",water_money1))
		{
			water_money1="0";
		}
		if(get_return_field("water_price11",water_price11))
		{
			water_price11="100";
		}
		if(get_return_field("water_price21",water_price21))
		{
			water_price21="100";
		}
		if(get_return_field("water_price31",water_price31))
		{
			water_price31="100";
		}
		water_str1="&pursetype1="+pursetype1+"&water_money1="+water_money1+"&water_price11="+water_price11+"&water_price21="+water_price21+"&water_price31="+water_price31;
		
	}
	if(pursetype2!="0"){
		CString water_money2="0";
		CString water_price12="100";
		CString water_price22="100";
		CString water_price32="100";
		if(get_return_field("water_money2",water_money2))
		{
			water_money2="0";
		}
		if(get_return_field("water_price12",water_price12))
		{
			water_price12="100";
		}
		if(get_return_field("water_price22",water_price22))
		{
			water_price22="100";
		}
		if(get_return_field("water_price32",water_price32))
		{
			water_price32="100";
		}
		water_str2="&pursetype2="+pursetype2+"&water_money2="+water_money2+"&water_price12="+water_price12+"&water_price22="+water_price22+"&water_price32="+water_price32;

	}
	if(pursetype3!="0"){
		CString water_money3="0";
		CString water_price13="100";
		CString water_price23="100";
		CString water_price33="100";
		if(get_return_field("water_money3",water_money3))
		{
			water_money3="0";
		}
		if(get_return_field("water_price13",water_price13))
		{
			water_price13="100";
		}
		if(get_return_field("water_price23",water_price23))
		{
			water_price23="100";
		}
		if(get_return_field("water_price33",water_price33))
		{
			water_price33="100";
		}
		water_str3="&pursetype3="+pursetype3+"&water_money3="+water_money3+"&water_price13="+water_price13+"&water_price23="+water_price23+"&water_price33="+water_price33;

	}	

	CString paramKey;
	get_return_field("paramKey",paramKey);
	t_params += "&cardphyid="+cardphyid+"&pay_card_cnt="+pay_card_cnt+"&cardBala="+cardBala+"&dpt_card_cnt="+dpt_card_cnt+"&showcardno="+showcardno+"&newcardphyid="+n_cardphyid;
	if(water_str1!=""){
		t_params += water_str1;
	}
	if(water_str2!=""){
		t_params += water_str2;
	}
	if(water_str3!=""){
		t_params += water_str3;
	}
	if(_file_open){
		g_LogFile.WriteLogEx(0, "新生换卡，水控钱包信息=[%s],cardphyid=[%s]",t_params,cardphyid);
		g_LogFile.ToFlush();
	}

	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; 
	chunk.size = 0;    

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60); 

		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code))
		{
			return -2;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				g_change_card_info.retcode="1";
				CString lserial1,lwithdraw_flag,sdate3,lvol0,sorder0,lvol1,lsafe_level2,lvol5,sall_name,spager,scert_no,semail2,smarket_code,sdate0,lvol8,lvol6,lvol4,stx_pwd,lvol11,lvol12,sholder_ac_no,smarket_code2,lsafe_level,stime3;
				if(get_return_field("lserial1",lserial1))
				{
					return -2;
				}

				if(get_return_field("lwithdraw_flag",lwithdraw_flag))
				{
					return -2;
				}
				if(get_return_field("sdate3",sdate3))
				{
					return -2;
				}
				if(get_return_field("lvol0",lvol0))
				{
					return -2;
				}
				if(get_return_field("sorder0",sorder0))
				{
					return -2;
				}
				if(get_return_field("lvol1",lvol1))
				{
					return -2;
				}
				if(get_return_field("lsafe_level2",lsafe_level2))
				{
					return -2;
				}
				if(get_return_field("lvol5",lvol5))
				{
					return -2;
				}
				if(get_return_field("sall_name",sall_name))
				{
					return -2;
				}
				if(get_return_field("spager",spager))
				{
					return -2;
				}
				if(get_return_field("scert_no",scert_no))
				{
					return -2;
				}
				if(get_return_field("semail2",semail2))
				{
					return -2;
				}
				if(get_return_field("smarket_code",smarket_code))
				{
					return -2;
				}
				if(get_return_field("sdate0",sdate0))
				{
					return -2;
				}
				if(get_return_field("lvol8",lvol8))
				{
					return -2;
				}
				if(get_return_field("lvol6",lvol6))
				{
					return -2;
				}
				if(get_return_field("lvol4",lvol4))
				{
					return -2;
				}
				if(get_return_field("stx_pwd",stx_pwd))
				{
					return -2;
				}
				if(get_return_field("lvol11",lvol11))
				{
					return -2;
				}
				if(get_return_field("lvol12",lvol12))
				{
					return -2;
				}
				if(get_return_field("sholder_ac_no",sholder_ac_no))
				{
					return -2;
				}
				if(get_return_field("smarket_code2",smarket_code2))
				{
					return -2;
				}
				if(get_return_field("lsafe_level",lsafe_level))
				{
					return -2;
				}
				if(get_return_field("stime3",stime3))
				{
					return -2;
				}

				get_return_field("paramKey",paramKey);

				int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
				if (ret==0)
				{
					

					int nRet;
					char sCardPhyID[17]={0};
					if( ks_card(sCardPhyID)!=0 )                                                                                                       
					{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡，写新卡发生错误,错误信息=[%s],cardphyid=[%s]","寻卡失败",cardphyid);
								g_LogFile.ToFlush();
							}
						AfxMessageBox("寻卡失败");
						return -2;
					}

					CString nCardPhyid="";
					CString oCardPhyid="";

					nCardPhyid.Format("%s",sCardPhyID);
					oCardPhyid.Format("%s",n_cardphyid);

					if(nCardPhyid!=oCardPhyid){
						if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡，写新卡发生错误,错误信息=[%s],cardphyid=[%s],ncardphyid=[%s]","卡号不正确",cardphyid,nCardPhyid);
								g_LogFile.ToFlush();
							}
						AfxMessageBox(_T("卡号不正确"));			
						return -3;
					}
					
					ks_clearallfieldallmode();
					ks_setfieldwritemode(CF_CARDNO);
					ks_setfieldval(CF_CARDNO,lvol0);				

					ks_setfieldwritemode(CF_SHOWCARDNO);					
					ks_setfieldval(CF_SHOWCARDNO,sorder0);

					ks_setfieldwritemode(CF_EXPIREDATE);
					ks_setfieldval(CF_EXPIREDATE,sdate0);

					ks_setfieldwritemode(CF_FEETYPE);
					ks_setfieldval(CF_FEETYPE,lvol5);

					ks_setfieldwritemode(CF_CUSTTYPE);
					ks_setfieldval(CF_CUSTTYPE,lsafe_level2);

					ks_setfieldwritemode(CF_NAME);
					ks_setfieldval(CF_NAME,sall_name);

					ks_setfieldwritemode(CF_IDNO);
					ks_setfieldval(CF_IDNO,semail2);

					ks_setfieldwritemode(CF_DEPTCODE);
					ks_setfieldval(CF_DEPTCODE,scert_no);

					ks_setfieldwritemode(CF_SEX);
					ks_setfieldval(CF_SEX,smarket_code);

					ks_setfieldwritemode(CF_STUEMPNO);
					ks_setfieldval(CF_STUEMPNO,spager);

					ks_setfieldwritemode(CF_CARDSTATUS);
					ks_setfieldval(CF_CARDBAL,"0");

					ks_setfieldwritemode(CF_CARDPWD);
					ks_setfieldval(CF_CARDPWD,stx_pwd);

					ks_setfieldwritemode(CF_IDTYPE);
					ks_setfieldval(CF_IDTYPE,smarket_code2);

					ks_setfieldwritemode(CF_PUBLISHID);
					ks_setfieldval(CF_PUBLISHID,sholder_ac_no);

					ks_setfieldwritemode(CF_CARDTYPE);
					ks_setfieldval(CF_CARDTYPE,lsafe_level);

					ks_setfieldwritemode(CF_CUSTID);
					ks_setfieldval(CF_CUSTID,lvol1);

					ks_setfieldwritemode(CF_SINGLEMAXAMT);
					ks_setfieldval(CF_SINGLEMAXAMT,lvol11);

					ks_setfieldwritemode(CF_DAYMAXAMT);
					ks_setfieldval(CF_DAYMAXAMT,lvol12);

					ks_setfieldwritemode(CF_SUBSIDYNO);
					ks_setfieldval(CF_SUBSIDYNO,lvol4);

					CString paramKey;
					get_return_field("paramKey",paramKey);
					ks_setmifare1key((LPCTSTR)paramKey);
					nRet=ks_writecard(sCardPhyID);
					if( nRet==0 )
					{
						g_change_card_info.retcode="2";
						if(_file_open){
							g_LogFile.WriteLogEx(0, "新生换卡基本信息写卡成功,cardphyid=[%s]",cardphyid);
							g_LogFile.ToFlush();
						}
						ST_TRANSPACK payment;
						memset(&payment,0,sizeof payment);
						strcpy(payment.sCardPhyID,n_cardphyid);
						payment.nCardNo = atoi(lvol0);
						payment.nDpsCardCnt = atoi(dpt_card_cnt);
						payment.nPayCardCnt = atoi(pay_card_cnt);
						payment.nBefBalance = 0;
						payment.nAftBalance = atoi(lvol8);

						strcpy(payment.sTransDate,sdate3);
						strcpy(payment.sTransTime,stime3);
						payment.nFundType = 1;
						payment.nTransAmt = atoi(lvol8); 
						char termno[13]={0};
						ks_readpsamtermno(termno,0);
						strcpy(payment.sTermno,termno);
						CString paramKey;
						get_return_field("paramKey",paramKey);
						ks_setmifare1key((LPCTSTR)paramKey);
						nRet=ks_setcardbal(&payment);
						if(nRet!=0)
						{		
							char sMsg[256]="";
							ks_geterrmsg(sMsg);
							if(strlen(sMsg)<1)
							{
								if(_file_open){
									g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]","写卡错误，返回码="+nRet,cardphyid);
									g_LogFile.ToFlush();
								}
								AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
							}else{
								if(_file_open){
									g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
									g_LogFile.ToFlush();
								}
								AfxMessageBox(sMsg);
							}

							if(payment.cGetProveFlag==1){
								//中途拔卡
								if(_file_open){
									g_LogFile.WriteLogEx(0, "写卡信息发生错误,中途拔卡,cardphyid=[%s]",cardphyid);
									g_LogFile.ToFlush();
								}
								return -99;
							}		
								
							return -10;
						}else{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "写卡信息结果写卡余额成功,cardphyid=[%s]",cardphyid);
								g_LogFile.ToFlush();
							}
						}
						g_change_card_info.retcode="3";
						CString validatedate="";
						if(get_return_field("validatedate",validatedate))
						{
							validatedate="";
						}
						
						if(pursetype1!="0"){
							CString money="0";
							CString price1="100";
							CString price2="100";
							CString price3="100";
							if(get_return_field("water_money1",money))
							{
								money="0";
							}
							if(get_return_field("water_price11",price1))
							{
								price1="100";
							}
							if(get_return_field("water_price21",price2))
							{
								price2="100";
							}
							if(get_return_field("water_price31",price3))
							{
								price3="100";
							}

							int water_bala = atoi(money);
							g_waterctl_packet_info.cardno=1;
							g_waterctl_packet_info.custno=1;
							g_waterctl_packet_info.money = water_bala;
							g_waterctl_packet_info.totalmoney = water_bala;
							strcpy(g_waterctl_packet_info.addtime,sdate3+stime3);
							g_waterctl_packet_info.addcount = 1;
							g_waterctl_packet_info.price1 = atoi(price1);
							g_waterctl_packet_info.price2 = atoi(price2);
							g_waterctl_packet_info.price3 = atoi(price3);
							strcpy(g_waterctl_packet_info.expireddate,validatedate);
							ret = ks_water_publishcard(atoi(pursetype1),&g_waterctl_packet_info);
							if(ret)
							{
								if(_file_open){
									g_LogFile.WriteLogEx(0,"小钱包1writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
									g_LogFile.ToFlush();
								}
								AfxMessageBox("水控钱包写卡失败");
								return ret;
							}else{
								if(_file_open){
									g_LogFile.WriteLogEx(0, "小钱包1writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
									g_LogFile.ToFlush();
								}
								if(pursetype2!="0"){
										if(get_return_field("water_money2",money))
										{
											money="0";
										}
										if(get_return_field("water_price12",price1))
										{
											price1="100";
										}
										if(get_return_field("water_price22",price2))
										{
											price2="100";
										}
										if(get_return_field("water_price32",price3))
										{
											price3="100";
										}
										g_waterctl_packet_info.money = water_bala;
										g_waterctl_packet_info.totalmoney = water_bala;
										g_waterctl_packet_info.price1 = atoi(price1);
										g_waterctl_packet_info.price2 = atoi(price2);
										g_waterctl_packet_info.price3 = atoi(price3);
										ret = ks_water_publishcard(atoi(pursetype2),&g_waterctl_packet_info);
										if(ret)
										{
											if(_file_open){
												g_LogFile.WriteLogEx(0,"小钱包2writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
												g_LogFile.ToFlush();
											}
											AfxMessageBox("水控钱包写卡失败");
											return ret;
										}else{
											if(_file_open){
												g_LogFile.WriteLogEx(0, "小钱包2writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
												g_LogFile.ToFlush();
											}
											if(pursetype3!="0"){
													if(get_return_field("water_money3",money))
													{
														money="0";
													}
													if(get_return_field("water_price13",price1))
													{
														price1="100";
													}
													if(get_return_field("water_price23",price2))
													{
														price2="100";
													}
													if(get_return_field("water_price33",price3))
													{
														price3="100";
													}
													g_waterctl_packet_info.money = water_bala;
													g_waterctl_packet_info.totalmoney = water_bala;
													g_waterctl_packet_info.price1 = atoi(price1);
													g_waterctl_packet_info.price2 = atoi(price2);
													g_waterctl_packet_info.price3 = atoi(price3);
													ret = ks_water_publishcard(atoi(pursetype3),&g_waterctl_packet_info);
													if(ret)
													{
														if(_file_open){
															g_LogFile.WriteLogEx(0,"小钱包3writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
															g_LogFile.ToFlush();
														}
														AfxMessageBox("水控钱包写卡失败");
														return ret;
													}else{
														if(_file_open){
															g_LogFile.WriteLogEx(0, "小钱包3writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
															g_LogFile.ToFlush();
														}
													}		
											}
									}
								}
							}
						}


						g_change_card_info.retcode="4";
						ks_beep();
						ks_clearallfieldwritemode();
						return 0;

					}else{
						char sMsg[256]="";
						ks_geterrmsg(sMsg);
						if(strlen(sMsg)<1)
						{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡发生错误,错误信息=[写卡错误,返回码=[%d],cardphyid=[%s]",nRet,cardphyid);
								g_LogFile.ToFlush();
							}
							AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
						}else{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡发生错误,错误信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
								g_LogFile.ToFlush();
							}
							AfxMessageBox(sMsg);
						}
						
						return -5;
					}

				}else{
					return -1;
				}
		}else
			{
				return -2;
			}
		}
	}else{
		return -3;
	}
}
SHORT CRF35OCXCtrl::ReCardChangeNewCard(LPCTSTR url)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString cardphyid=g_change_card_info.o_cardphyid;
	CString cardBala=g_change_card_info.o_cardBala;
	CString pay_card_cnt=g_change_card_info.o_pay_card_cnt;
	CString dpt_card_cnt=g_change_card_info.o_dpt_card_cnt;
	CString showcardno=g_change_card_info.n_showcardno;
	CString n_cardphyid=g_change_card_info.n_cardphyid;
	CString paramKey;
	get_return_field("paramKey",paramKey);

	if (g_change_card_info.retcode=="0")
	{
		//后台没有返回
		return CardChangeNewCard(url);

	}else{
		CString code;
		//后台返回，发卡失败
		if(get_return_field("ErrorCode",code))
		{
			return -2;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				CString lserial1,lwithdraw_flag,sdate3,lvol0,sorder0,lvol1,lsafe_level2,lvol5,sall_name,spager,scert_no,semail2,smarket_code,sdate0,lvol8,lvol6,lvol4,stx_pwd,lvol11,lvol12,sholder_ac_no,smarket_code2,lsafe_level,stime3;
				if(get_return_field("lserial1",lserial1))
				{
					return -2;
				}

				if(get_return_field("lwithdraw_flag",lwithdraw_flag))
				{
					return -2;
				}
				if(get_return_field("sdate3",sdate3))
				{
					return -2;
				}
				if(get_return_field("lvol0",lvol0))
				{
					return -2;
				}
				if(get_return_field("sorder0",sorder0))
				{
					return -2;
				}
				if(get_return_field("lvol1",lvol1))
				{
					return -2;
				}
				if(get_return_field("lsafe_level2",lsafe_level2))
				{
					return -2;
				}
				if(get_return_field("lvol5",lvol5))
				{
					return -2;
				}
				if(get_return_field("sall_name",sall_name))
				{
					return -2;
				}
				if(get_return_field("spager",spager))
				{
					return -2;
				}
				if(get_return_field("scert_no",scert_no))
				{
					return -2;
				}
				if(get_return_field("semail2",semail2))
				{
					return -2;
				}
				if(get_return_field("smarket_code",smarket_code))
				{
					return -2;
				}
				if(get_return_field("sdate0",sdate0))
				{
					return -2;
				}
				if(get_return_field("lvol8",lvol8))
				{
					return -2;
				}
				if(get_return_field("lvol6",lvol6))
				{
					return -2;
				}
				if(get_return_field("lvol4",lvol4))
				{
					return -2;
				}
				if(get_return_field("stx_pwd",stx_pwd))
				{
					return -2;
				}
				if(get_return_field("lvol11",lvol11))
				{
					return -2;
				}
				if(get_return_field("lvol12",lvol12))
				{
					return -2;
				}
				if(get_return_field("sholder_ac_no",sholder_ac_no))
				{
					return -2;
				}
				if(get_return_field("smarket_code2",smarket_code2))
				{
					return -2;
				}
				if(get_return_field("lsafe_level",lsafe_level))
				{
					return -2;
				}
				if(get_return_field("stime3",stime3))
				{
					return -2;
				}

				get_return_field("paramKey",paramKey);

				int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
				if (ret==0)
				{
					CLogFile g_LogFile;
					bool _file_open = false;
					if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
							_file_open = true;
					}

					int nRet;
					char sCardPhyID[17]={0};
					if( ks_card(sCardPhyID)!=0 )                                                                                                       
					{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡，写新卡发生错误,错误信息=[%s],cardphyid=[%s]","寻卡失败",cardphyid);
								g_LogFile.ToFlush();
							}
						AfxMessageBox("寻卡失败");
						return -2;
					}

					CString nCardPhyid="";
					CString oCardPhyid="";

					nCardPhyid.Format("%s",sCardPhyID);
					oCardPhyid.Format("%s",n_cardphyid);

					if(nCardPhyid!=oCardPhyid){
						if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡，写新卡发生错误,错误信息=[%s],cardphyid=[%s],ncardphyid=[%s]","卡号不正确",cardphyid,nCardPhyid);
								g_LogFile.ToFlush();
							}
						AfxMessageBox(_T("卡号不正确"));			
						return -3;
					}
					
					ks_clearallfieldallmode();
					ks_setfieldwritemode(CF_CARDNO);
					ks_setfieldval(CF_CARDNO,lvol0);				

					ks_setfieldwritemode(CF_SHOWCARDNO);					
					ks_setfieldval(CF_SHOWCARDNO,sorder0);

					ks_setfieldwritemode(CF_EXPIREDATE);
					ks_setfieldval(CF_EXPIREDATE,sdate0);

					ks_setfieldwritemode(CF_FEETYPE);
					ks_setfieldval(CF_FEETYPE,lvol5);

					ks_setfieldwritemode(CF_CUSTTYPE);
					ks_setfieldval(CF_CUSTTYPE,lsafe_level2);

					ks_setfieldwritemode(CF_NAME);
					ks_setfieldval(CF_NAME,sall_name);

					ks_setfieldwritemode(CF_IDNO);
					ks_setfieldval(CF_IDNO,semail2);

					ks_setfieldwritemode(CF_DEPTCODE);
					ks_setfieldval(CF_DEPTCODE,scert_no);

					ks_setfieldwritemode(CF_SEX);
					ks_setfieldval(CF_SEX,smarket_code);

					ks_setfieldwritemode(CF_STUEMPNO);
					ks_setfieldval(CF_STUEMPNO,spager);

					ks_setfieldwritemode(CF_CARDSTATUS);
					ks_setfieldval(CF_CARDBAL,"0");

					ks_setfieldwritemode(CF_CARDPWD);
					ks_setfieldval(CF_CARDPWD,stx_pwd);

					ks_setfieldwritemode(CF_IDTYPE);
					ks_setfieldval(CF_IDTYPE,smarket_code2);

					ks_setfieldwritemode(CF_PUBLISHID);
					ks_setfieldval(CF_PUBLISHID,sholder_ac_no);

					ks_setfieldwritemode(CF_CARDTYPE);
					ks_setfieldval(CF_CARDTYPE,lsafe_level);

					ks_setfieldwritemode(CF_CUSTID);
					ks_setfieldval(CF_CUSTID,lvol1);

					ks_setfieldwritemode(CF_SINGLEMAXAMT);
					ks_setfieldval(CF_SINGLEMAXAMT,lvol11);

					ks_setfieldwritemode(CF_DAYMAXAMT);
					ks_setfieldval(CF_DAYMAXAMT,lvol12);

					ks_setfieldwritemode(CF_SUBSIDYNO);
					ks_setfieldval(CF_SUBSIDYNO,lvol4);

					CString paramKey;
					get_return_field("paramKey",paramKey);
					ks_setmifare1key((LPCTSTR)paramKey);
					nRet=ks_writecard(sCardPhyID);
					if( nRet==0 )
					{

						if(_file_open){
							g_LogFile.WriteLogEx(0, "新生换卡基本信息写卡成功,cardphyid=[%s]",cardphyid);
							g_LogFile.ToFlush();
						}
						ST_TRANSPACK payment;
						memset(&payment,0,sizeof payment);
						strcpy(payment.sCardPhyID,n_cardphyid);
						payment.nCardNo = atoi(lvol0);
						payment.nDpsCardCnt = atoi(dpt_card_cnt);
						payment.nPayCardCnt = atoi(pay_card_cnt);
						payment.nBefBalance = 0;
						payment.nAftBalance = atoi(lvol8);

						strcpy(payment.sTransDate,sdate3);
						strcpy(payment.sTransTime,stime3);
						payment.nFundType = 1;
						payment.nTransAmt = atoi(lvol8); 
						char termno[13]={0};
						ks_readpsamtermno(termno,0);
						strcpy(payment.sTermno,termno);
						CString paramKey;
						get_return_field("paramKey",paramKey);
						ks_setmifare1key((LPCTSTR)paramKey);
						nRet=ks_setcardbal(&payment);
						if(nRet!=0)
						{		
							char sMsg[256]="";
							ks_geterrmsg(sMsg);
							if(strlen(sMsg)<1)
							{
								if(_file_open){
									g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]","写卡错误，返回码="+nRet,cardphyid);
									g_LogFile.ToFlush();
								}
								AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
							}else{
								if(_file_open){
									g_LogFile.WriteLogEx(0, "写卡信息发生错误,返回信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
									g_LogFile.ToFlush();
								}
								AfxMessageBox(sMsg);
							}

							if(payment.cGetProveFlag==1){
								//中途拔卡
								if(_file_open){
									g_LogFile.WriteLogEx(0, "写卡信息发生错误,中途拔卡,cardphyid=[%s]",cardphyid);
									g_LogFile.ToFlush();
								}
								return -99;
							}		
								
							return -10;
						}else{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "写卡信息结果写卡余额成功,cardphyid=[%s]",cardphyid);
								g_LogFile.ToFlush();
							}
						}
						
						CString pursetype1="0";
						CString pursetype2="0";
						CString pursetype3="0";
						if(get_return_field("pursetype1",pursetype1))
						{
							pursetype1="0";
						}
						if(get_return_field("pursetype2",pursetype2))
						{
							pursetype2="0";
						}
						if(get_return_field("pursetype3",pursetype3))
						{
							pursetype3="0";
						}
						CString validatedate="";
						if(get_return_field("validatedate",validatedate))
						{
							validatedate="";
						}
						if(pursetype1!="0"){
							CString money="0";
							CString price1="100";
							CString price2="100";
							CString price3="100";
							if(get_return_field("water_money1",money))
							{
								money="0";
							}
							if(get_return_field("water_price11",price1))
							{
								price1="100";
							}
							if(get_return_field("water_price21",price2))
							{
								price2="100";
							}
							if(get_return_field("water_price31",price3))
							{
								price3="100";
							}

							int water_bala = atoi(money);
							g_waterctl_packet_info.cardno=1;
							g_waterctl_packet_info.custno=1;
							g_waterctl_packet_info.money = water_bala;
							g_waterctl_packet_info.totalmoney = water_bala;
							strcpy(g_waterctl_packet_info.addtime,sdate3+stime3);
							g_waterctl_packet_info.addcount = 1;
							g_waterctl_packet_info.price1 = atoi(price1);
							g_waterctl_packet_info.price2 = atoi(price2);
							g_waterctl_packet_info.price3 = atoi(price3);
							strcpy(g_waterctl_packet_info.expireddate,validatedate);
							ret = ks_water_publishcard(atoi(pursetype1),&g_waterctl_packet_info);
							if(ret)
							{
								if(_file_open){
									g_LogFile.WriteLogEx(0,"小钱包1writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
									g_LogFile.ToFlush();
								}
								AfxMessageBox("水控钱包写卡失败");
								return ret;
							}else{
								if(_file_open){
									g_LogFile.WriteLogEx(0, "小钱包1writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
									g_LogFile.ToFlush();
								}
								if(pursetype2!="0"){
										if(get_return_field("water_money2",money))
										{
											money="0";
										}
										if(get_return_field("water_price12",price1))
										{
											price1="100";
										}
										if(get_return_field("water_price22",price2))
										{
											price2="100";
										}
										if(get_return_field("water_price32",price3))
										{
											price3="100";
										}
										g_waterctl_packet_info.money = water_bala;
										g_waterctl_packet_info.totalmoney = water_bala;
										g_waterctl_packet_info.price1 = atoi(price1);
										g_waterctl_packet_info.price2 = atoi(price2);
										g_waterctl_packet_info.price3 = atoi(price3);
										ret = ks_water_publishcard(atoi(pursetype2),&g_waterctl_packet_info);
										if(ret)
										{
											if(_file_open){
												g_LogFile.WriteLogEx(0,"小钱包2writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
												g_LogFile.ToFlush();
											}
											AfxMessageBox("水控钱包写卡失败");
											return ret;
										}else{
											if(_file_open){
												g_LogFile.WriteLogEx(0, "小钱包2writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
												g_LogFile.ToFlush();
											}
											if(pursetype3!="0"){
													if(get_return_field("water_money3",money))
													{
														money="0";
													}
													if(get_return_field("water_price13",price1))
													{
														price1="100";
													}
													if(get_return_field("water_price23",price2))
													{
														price2="100";
													}
													if(get_return_field("water_price33",price3))
													{
														price3="100";
													}
													g_waterctl_packet_info.money = water_bala;
													g_waterctl_packet_info.totalmoney = water_bala;
													g_waterctl_packet_info.price1 = atoi(price1);
													g_waterctl_packet_info.price2 = atoi(price2);
													g_waterctl_packet_info.price3 = atoi(price3);
													ret = ks_water_publishcard(atoi(pursetype3),&g_waterctl_packet_info);
													if(ret)
													{
														if(_file_open){
															g_LogFile.WriteLogEx(0,"小钱包3writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
															g_LogFile.ToFlush();
														}
														AfxMessageBox("水控钱包写卡失败");
														return ret;
													}else{
														if(_file_open){
															g_LogFile.WriteLogEx(0, "小钱包3writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,water_bala,water_bala);
															g_LogFile.ToFlush();
														}
													}		
											}
									}
								}
							}
						}


				
						ks_beep();
						ks_clearallfieldwritemode();
						return 0;

					}else{
						char sMsg[256]="";
						ks_geterrmsg(sMsg);
						if(strlen(sMsg)<1)
						{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡发生错误,错误信息=[写卡错误,返回码=[%d],cardphyid=[%s]",nRet,cardphyid);
								g_LogFile.ToFlush();
							}
							AfxMessageBox("写卡错误，返回码="+rtnCstring(nRet));
						}else{
							if(_file_open){
								g_LogFile.WriteLogEx(0, "新生换卡发生错误,错误信息=[%s],cardphyid=[%s]",sMsg,cardphyid);
								g_LogFile.ToFlush();
							}
							AfxMessageBox(sMsg);
						}
						
						return -5;
					}

				}else{
					return -1;
				}
		}else
			{
				return -2;
			}
		}
	}
}

BSTR CRF35OCXCtrl::GetChangeCardinfo(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult="";
	CString t_param(param);

	if (t_param=="showcardno")
	{
		strResult = g_change_card_info.n_showcardno;
	}else if (t_param=="cardphyid")
	{
		strResult = g_change_card_info.n_cardphyid;
	}else if (t_param=="oldcardphyid")
	{
		strResult = g_change_card_info.o_cardphyid;
	}else if (t_param=="cardbala")
	{
		strResult = g_change_card_info.o_cardBala;
	}else if (t_param=="dpt_card_cnt")
	{
		strResult = g_change_card_info.o_dpt_card_cnt;
	}else if (t_param=="pay_card_cnt")
	{
		strResult = g_change_card_info.o_pay_card_cnt;
	}else
	{
		strResult="";
	}

	return strResult.AllocSysString();
}

SHORT CRF35OCXCtrl::CheckOldCard(void)
{
	CString paramKey="";
	get_return_field("paramKey",paramKey);
	CString cardphyid=g_change_card_info.o_cardphyid;

	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )                                                                                                       
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));			
			return -3;
		}else{
			return 0;
		}	
	}else{
		return 3;
	}
}

void CRF35OCXCtrl::OnCardPhyIDChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}
//读水控钱包信息
SHORT CRF35OCXCtrl::ReadWaterCtlPacket(SHORT watertype, LPCTSTR cardphyid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	char phyid[17];

	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		ret = ks_card(phyid);
		if(ret){
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",phyid);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
		memset(&g_waterctl_packet_info,0,sizeof g_waterctl_packet_info);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret = ks_water_readmoney(watertype,&g_waterctl_packet_info);
		if(ret)
		{
			//AfxMessageBox("水控钱包读取失败");
			return ret;
		}else{
			return 0;
		}


	}else{
		return -1;
	}
}

LONG CRF35OCXCtrl::GetWaterCtlPacketInfo(LPCTSTR param)
{
	LONG ret = 0;

	CString code(param);
	if (code=="money")
	{
		ret = g_waterctl_packet_info.money;
	}
	if (code=="addcount")
	{
		ret = g_waterctl_packet_info.addcount;
	}
	if (code=="price1")
	{
		ret = g_waterctl_packet_info.price1;
	}
	if (code=="price2")
	{
		ret = g_waterctl_packet_info.price2;
	}
	if (code=="price3")
	{
		ret = g_waterctl_packet_info.price3;
	}

	return ret;
}


//yjz 和 999 水控用
SHORT CRF35OCXCtrl::WaterCtlTransWriteCard(LPCTSTR url, LPCTSTR cardphyid, SHORT watertype, LPCTSTR params)
{
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code))
		{
			return -2;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				CString outcardamount,outcardamount1,amount,cardphyid,txcnt,txcnt1,sdate3,stime3,ipServer,drtpPort,svrFunc,price1,price2,price3,validatedate;
				if(get_return_field("OutCardAmount",outcardamount))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("OutCardAmount1",outcardamount1))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("amount",amount))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("cardphyid",cardphyid))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("txCnt",txcnt))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("txCnt1",txcnt1))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("sdate3",sdate3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("stime3",stime3))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("ipServer",ipServer))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("drtpPort",drtpPort))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("svrFunc",svrFunc))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("price1",price1))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("price2",price2))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("price3",price3))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("validatedate",validatedate))
				{
					// 没有卡号字段
					return -2;
				}

				//把钱包号放入map中，以备补写的时候用
				CString s_watertype ="";
				s_watertype.Format("%d",watertype);
				g_request_return.insert(RequestRet_Map::value_type("watertype",s_watertype));
				int ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);
				if (ret==0)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0, "水控转账大钱包扣卡成功ret=[%d],cardphyid=[%s],出卡值=[%s]",ret,cardphyid,outcardamount);
						g_LogFile.ToFlush();
					}
					//写卡成功
					ret = WriteWaterCtlPacket(outcardamount1,cardphyid,txcnt1,watertype,amount,sdate3+stime3,price1,price2,price3,validatedate);
					if (ret==0)
					{
						if(_file_open){
							g_LogFile.WriteLogEx(0, "水控转账小钱包加卡成功ret=[%d],cardphyid=[%s],出卡值=[%s]",ret,cardphyid,outcardamount1);
							g_LogFile.ToFlush();
						}
						return 0;
					}else{
						if(_file_open){
							g_LogFile.WriteLogEx(0, "水控转账小钱包加卡失败ret=[%d]",ret);
							g_LogFile.ToFlush();
						}
						return -3;
					}

				}else{		
					if(_file_open){
						g_LogFile.WriteLogEx(0, "水控转账大钱包扣卡失败ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					return -1;
				}
			}else{
				//失败
				return 1;
			}
		}
	}
	return 2;
}

SHORT CRF35OCXCtrl::WriteWaterCtlPacket(LPCTSTR outcardamount, LPCTSTR cardphyid, LPCTSTR txcnt, SHORT watertype, LPCTSTR amount, LPCTSTR sdatetime, LPCTSTR price1, LPCTSTR price2, LPCTSTR price3, LPCTSTR validatedate)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	char phyid[17];
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{

		ret = ks_card(phyid);
		if(ret){
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",phyid);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){			
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);

		int water_bala = atoi(outcardamount);
		int water_cnt = atoi(txcnt);
		int water_amount =  atoi(amount)*100;//分
		if(water_bala!=g_waterctl_packet_info.money){
			g_waterctl_packet_info.cardno=1;
			g_waterctl_packet_info.custno=1;
			g_waterctl_packet_info.lockflag=0xFF;
			g_waterctl_packet_info.money = water_bala;
			g_waterctl_packet_info.totalmoney = g_waterctl_packet_info.totalmoney+water_amount;
			strcpy(g_waterctl_packet_info.addtime,sdatetime);
			g_waterctl_packet_info.addcount = g_waterctl_packet_info.addcount+1;
			g_waterctl_packet_info.price1 = atoi(price1);
			g_waterctl_packet_info.price2 = atoi(price2);
			g_waterctl_packet_info.price3 = atoi(price3);
			strcpy(g_waterctl_packet_info.expireddate,validatedate);
		}
		ret = ks_water_writemoney(watertype,&g_waterctl_packet_info);
		if(ret)
		{
			if(_file_open){
				g_LogFile.WriteLogEx(0,"小钱包writemoeny失败,ret=[%d],余额=[%d],加款金额=[%d]",ret,g_waterctl_packet_info.money,water_amount);
				g_LogFile.ToFlush();
			}
			AfxMessageBox("水控钱包写卡失败");
			return ret;
		}else{
			if(_file_open){
				g_LogFile.WriteLogEx(0, "小钱包writemoeny成功,ret=[%d],余额=[%d],加款金额=[%d]",ret,g_waterctl_packet_info.money,water_amount);
				g_LogFile.ToFlush();
			}
			return 0;
		}		

	}else{
		return -1;
	}
}

SHORT CRF35OCXCtrl::ReWriteWaterCtlTrans(void)
{
	CString outcardamount,outcardamount1,amount,cardphyid,txcnt,txcnt1,sdate3,stime3,ipServer,drtpPort,svrFunc,price1,price2,price3,validatedate,watertype;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("OutCardAmount1",outcardamount1))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("amount",amount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("cardphyid",cardphyid))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt1",txcnt1))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("sdate3",sdate3))
	{
		// 没有金额字段
		return -2;
	}

	if(get_return_field("stime3",stime3))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("ipServer",ipServer))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("drtpPort",drtpPort))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("svrFunc",svrFunc))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("watertype",watertype))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("price1",price1))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("price2",price2))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("price3",price3))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("validatedate",validatedate))
	{
		// 没有卡号字段
		return -2;
	}

	int ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc);
	if (ret==0)
	{
		//写卡成功

		ret = WriteWaterCtlPacket(outcardamount1,cardphyid,txcnt1,atoi(watertype),amount,sdate3+stime3,price1,price2,price3,validatedate);
		if (ret==0)
		{
			return 0;
		}else{
			return -3;
		}

	}else{				
		return -1;
	}
}

SHORT CRF35OCXCtrl::DoOpenCom()
{
	return g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
}

void CRF35OCXCtrl::OnPsamCardPositionChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	SetModifiedFlag();
}

LONG CRF35OCXCtrl::ReadCardLockInfo(LPCTSTR CardPhyId)
{
	int ret = 0;
	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		char sCardPhyID[17];
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return 1;
		}


		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return 2;
		}

		RetsetLockInfo();

		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDSTATUS);
		ks_setfieldreadmode(CF_LOCKTERMID);
		ks_setfieldreadmode(CF_LOCKTRANSDATE);
		ks_setfieldreadmode(CF_LOCKTRANSTIME);
		ks_setfieldreadmode(CF_LOCKCARDCNT);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret=ks_readcard();
		if(ret==0)
		{
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_CARDSTATUS,sdata);
			if(ret==0){
				if(atol(sdata)!=6){
					AfxMessageBox(_T("卡片未被锁,不需要解锁!"));
					return -100;
				}
			}else{
				return -8;
			}			
			CString tmp ="";
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_LOCKTERMID,sdata);
			if(ret==0){
				tmp="";
				tmp.Format("%s",sdata);
				g_lock_info.termid=tmp;
			}else{
				return -1;
			}

			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_LOCKTRANSDATE,sdata);
			if(ret==0){
				tmp="";
				tmp.Format("%s",sdata);
				g_lock_info.transdate=tmp;
			}else{
				return -2;
			}

			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_LOCKTRANSTIME,sdata);
			if(ret==0){
				tmp="";
				tmp.Format("%s",sdata);
				g_lock_info.transtime=tmp;
			}else{
				return -3;
			}

			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_LOCKCARDCNT,sdata);
			if(ret==0){
				tmp="";
				tmp.Format("%s",sdata);
				g_lock_info.lockcardcnt=tmp;
			}else{
				return -4;
			}
			
			return 0;

		}else{
			return -6;
		}

	}else{
		return -5;
	}
}

BSTR CRF35OCXCtrl::GetCardLockInfo(LPCTSTR param)
{
	CString strResult=_T("");
	CString code(param);
	if (code=="termid"){
		strResult = g_lock_info.termid;
	}else if (code=="transdate"){
		strResult = g_lock_info.transdate;
	}else if (code=="transtime"){
		strResult = g_lock_info.transtime;
	}else if (code=="lockcardcnt"){
		strResult = g_lock_info.lockcardcnt;
	}
	return strResult.AllocSysString();
}


SHORT CRF35OCXCtrl::UnlockWriteCard(LPCTSTR outcardamount, LPCTSTR cardphyid,LPCTSTR txcnt,LPCTSTR amount,LPCTSTR sdate,LPCTSTR stime,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc,LPCTSTR CARDSTAT)
{
	int ret = 0;
	ResetInfo();
	g_request_return.insert(RequestRet_Map::value_type("cardphyid",cardphyid));
	g_request_return.insert(RequestRet_Map::value_type("txCnt",txcnt));
	g_request_return.insert(RequestRet_Map::value_type("OutCardAmount",outcardamount));
	g_request_return.insert(RequestRet_Map::value_type("amount",amount));
	g_request_return.insert(RequestRet_Map::value_type("sdate3",sdate));
	g_request_return.insert(RequestRet_Map::value_type("stime3",stime));
	g_request_return.insert(RequestRet_Map::value_type("ipServer",ipServer));
	g_request_return.insert(RequestRet_Map::value_type("drtpPort",drtpPort));
	g_request_return.insert(RequestRet_Map::value_type("svrFunc",svrFunc));
	g_request_return.insert(RequestRet_Map::value_type("CARDSTAT",CARDSTAT));
	if(atoi(amount)*100==0){
		ret = UndoLock(cardphyid,CARDSTAT);
		return ret;
	}else{
		ret = WriteCard(outcardamount,cardphyid,txcnt,amount,sdate,stime,ipServer,drtpPort,svrFunc);
		if(ret==0){
			ret = UndoLock(cardphyid,CARDSTAT);
			return ret;
		}else{
			return -10;
		}
	}	
	return 0;
}

short CRF35OCXCtrl::UndoLock(LPCTSTR CardPhyId,LPCTSTR CARDSTAT) 
{
	unsigned long snr = 0;
//	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		
//		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -12;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",CardPhyId);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -13;
		}

		ks_clearallfieldallmode();
		ks_setfieldwritemode(CF_CARDSTATUS);
		ks_setfieldval(CF_CARDSTATUS,CARDSTAT);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret=ks_writecard(sCardPhyID);
		if( ret==0 )
		{
			ks_beep();
			return 0;

		}else{
			char sMsg[256]="";
			ks_geterrmsg(sMsg);
			if(strlen(sMsg)<1)
			{
				AfxMessageBox("写卡错误，返回码="+rtnCstring(ret));
			}else{
				AfxMessageBox(sMsg);
			}
			return -20;
		}		
	}else{
		return -11;
	}
}

SHORT CRF35OCXCtrl::ReUnlockWriteCard(void)
{
	CString outcardamount,amount,cardphyid,txcnt,sdate3,stime3,ipServer,drtpPort,svrFunc,CARDSTAT;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("amount",amount))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("cardphyid",cardphyid))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("sdate3",sdate3))
	{
		// 没有金额字段
		return -2;
	}

	if(get_return_field("stime3",stime3))
	{
		// 没有金额字段
		return -2;
	}
	if(get_return_field("ipServer",ipServer))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("drtpPort",drtpPort))
	{
		// 没有卡号字段
		return -2;
	}
	if(get_return_field("svrFunc",svrFunc))
	{
		// 没有卡号字段
		return -2;
	}
		if(get_return_field("CARDSTAT",CARDSTAT))
	{
		// 没有卡号字段
		return -2;
	}

	return UnlockWriteCard(outcardamount,cardphyid,txcnt,amount,sdate3,stime3,ipServer,drtpPort,svrFunc,CARDSTAT);
}

SHORT CRF35OCXCtrl::CheckTransProve( LPCTSTR cardphyid,SHORT transflag, SHORT cardcnt)
{
	int ret = 0;
	ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		char sCardPhyID[17];
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}


		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}

		ret = ks_gettransprove(transflag,cardcnt+1);
		if(ret==0){
			return 0;
		}else{
			return 1;
		}

	}else{
		return -1;
	}
}

void CRF35OCXCtrl::SetReturnMap(LPCTSTR key, LPCTSTR value)
{
	g_request_return.insert(RequestRet_Map::value_type(key,value));
}

void CRF35OCXCtrl::CleanReturnMap(void)
{
	ResetInfo();
}

SHORT CRF35OCXCtrl::InitWaterCtlPocket(LPCTSTR url,SHORT pocket, LPCTSTR cardphyid)
{
CLogFile g_LogFile;
	bool _file_open = false;
	if(g_LogFile.Open("C:\\WINDOWS\\system32\\OCXLogs")){
			_file_open = true;
	}
	CString strResult;
	CString t_params(cardphyid);
	t_params="cardphyid="+t_params;
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10); 
		/* send all data to this function  */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

		/* we pass our 'chunk' struct to the callback function */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

		res = curl_easy_perform(curl);

		if(CURLE_OK!=res){
			//网络不通
			return 2;			
		}

		curl_easy_cleanup(curl);

		// TODO: Add your dispatch handler code here
		strResult.Format("%s",chunk.memory);
		if (chunk.memory)
		{
			free(chunk.memory);
		}	

	}

	//全局初始化 /清空
	ResetInfo();
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;

		todoElement = doc.RootElement();
		node = todoElement->FirstChild();//head节点

		// 第一个节点
		node = node->FirstChild();

		CString node_name;
		CString code;
		while(node!=NULL)
		{
			textnode = node->FirstChild();
			node_name = node->Value(); // 节点名
			if(textnode!=NULL) // 节点值
				code = textnode->Value();
			else
				code = _T("");
			g_request_return.insert(RequestRet_Map::value_type(node_name,code));
			node = node->NextSibling();
		}
		if(get_return_field("ErrorCode",code))
		{
			return -2;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				CString sdate3,stime3,price1,price2,price3,validatedate;

				if(get_return_field("sdate3",sdate3))
				{
					// 没有金额字段
					return -2;
				}

				if(get_return_field("stime3",stime3))
				{
					// 没有金额字段
					return -2;
				}
				if(get_return_field("price1",price1))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("price2",price2))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("price3",price3))
				{
					// 没有卡号字段
					return -2;
				}
				if(get_return_field("validatedate",validatedate))
				{
					// 没有卡号字段
					return -2;
				}

				g_waterctl_packet_info.cardno=1;
				g_waterctl_packet_info.custno=1;
				g_waterctl_packet_info.lockflag=0xFF;
				g_waterctl_packet_info.money = 0;
				g_waterctl_packet_info.totalmoney = 0;
				strcpy(g_waterctl_packet_info.addtime,sdate3+stime3);
				g_waterctl_packet_info.addcount = 1;
				g_waterctl_packet_info.price1 = atoi(price1);
				g_waterctl_packet_info.price2 = atoi(price2);
				g_waterctl_packet_info.price3 = atoi(price3);
				strcpy(g_waterctl_packet_info.expireddate,validatedate);
				CString paramKey;
				get_return_field("paramKey",paramKey);
				ks_setmifare1key((LPCTSTR)paramKey);
				int ret = ks_water_publishcard(pocket,&g_waterctl_packet_info);
				if(ret)
				{
					if(_file_open){
						g_LogFile.WriteLogEx(0,"小钱包初始化失败,ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					AfxMessageBox("水控钱包初始化失败,返回码="+rtnCstring(ret));
					return -1;
				}else{
					if(_file_open){
						g_LogFile.WriteLogEx(0, "小钱包初始化成功,ret=[%d]",ret);
						g_LogFile.ToFlush();
					}
					ks_beep();
					return 0;
				}


			}else{
				//失败
				return 1;
			}
		}
	}else{
		return -4;
	}
}

SHORT CRF35OCXCtrl::CheckLockStatus(LPCTSTR cardphyid)
{
unsigned long snr = 0;
	char sdata[128];
	//KSCardReader ksCardRead(m_nPortNo);
	int ret = g_ksCardRead.Open(m_PsamCardPosition,m_nPortNo);
	if (ret==0)
	{
		
		int nRet;
		char sCardPhyID[17]={0};
		if( ks_card(sCardPhyID)!=0 )
		{
			AfxMessageBox("寻卡失败");
			return -2;
		}

		CString nCardPhyid="";
		CString oCardPhyid="";

		nCardPhyid.Format("%s",sCardPhyID);
		oCardPhyid.Format("%s",cardphyid);

		if(nCardPhyid!=oCardPhyid){
			AfxMessageBox(_T("卡号不正确"));
			return -3;
		}
		ks_clearallfieldallmode();
		ks_setfieldreadmode(CF_CARDSTATUS);
		CString paramKey;
		get_return_field("paramKey",paramKey);
		ks_setmifare1key((LPCTSTR)paramKey);
		ret=ks_readcard();
		if(ret==0){
			memset(sdata,0,sizeof sdata);
			ret=ks_getfieldval(CF_CARDSTATUS,sdata);
			if(ret==0){
				if(atol(sdata)==6){
					return -1;
				}else{
					return 0;
				}
			}else{
				AfxMessageBox(_T("卡状态读取失败,返回码="+rtnCstring(ret)));
				return -6;
			}

		}else{
			AfxMessageBox(_T("卡状态读取失败,返回码="+rtnCstring(ret)));
			return -4;
		}
		
		
	}else{
		return -8;
	}
}
