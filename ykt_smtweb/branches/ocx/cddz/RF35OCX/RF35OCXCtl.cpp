// RF35OCXCtl.cpp : Implementation of the CRF35OCXCtrl ActiveX Control class.

#include "stdafx.h"
#include <afxmt.h>
#include "RF35OCX.h"
#include "RF35OCXCtl.h"
#include "RF35OCXPpg.h"
//#include "mwrf32.h"
#include "comm.h"
#include ".\rf35ocxctl.h"
#include "curl\curl.h"
#include "tinyxml.h"
#include "CardDLL.h"
#include <map>
#include   <time.h>
#include "serialport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString CRF35OCXCtrl::ms_tokenKey("&token=r34ks2005fd");

#define OCX_VERSION "1.2.1"

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
	DISP_FUNCTION_ID(CRF35OCXCtrl, "MySendRequest", dispidMySendRequest, MySendRequest, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetRequestRetInfo", dispidGetRequestRetInfo, GetRequestRetInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardPocket", dispidReadCardPocket, ReadCardPocket, VT_I4, VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetPacketInfo", dispidGetPacketInfo, GetPacketInfo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "RewriteCardInfo", dispidRewriteCardInfo, RewriteCardInfo, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReportCardWriteFailue", dispidReportCardWriteFailue, ReportCardWriteFailue, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetMainKey", dispidGetMainKey, GetMainKey, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "MobileTransWriteCard", dispidMobileTransWriteCard, MobileTransWriteCard, VT_I2,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ElectTransWriteCard", dispidElectTransWriteCard, ElectTransWriteCard, VT_I2,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UpdateCardInfo", dispidUpdateCardInfo, UpdateCardInfo, VT_I2, VTS_I4 VTS_I4 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "NetTransWriteCard", dispidNetTransWriteCard, NetTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getComsumerLimit", dispidgetComsumerLimit, getComsumerLimit, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardConsumerLimit", dispidReadCardConsumerLimit, ReadCardConsumerLimit, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ResetConsumerLimit", dispidResetConsumerLimit, ResetConsumerLimit, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardSidyNo", dispidReadCardSidyNo, ReadCardSidyNo, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "RewriteSidy", dispidRewriteSidy, RewriteSidy, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReNetTransWriteCard", dispidReNetTransWriteCard, ReNetTransWriteCard, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReverseNetTrans", dispidReverseNetTrans, ReverseNetTrans, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadOldCardInfo", dispidReadOldCardInfo, ReadOldCardInfo, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getOldCardInfo", dispidgetOldCardInfo, getOldCardInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getMoneyFromOldCard", dispidgetMoneyFromOldCard, getMoneyFromOldCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CardTransWriteCard", dispidCardTransWriteCard, CardTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "BeginUpdateCard", dispidBeginUpdateCard, BeginUpdateCard, VT_I2, VTS_I4)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "SetCardProperty", dispidSetCardProperty, SetCardProperty, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UpdateCard", dispidUpdateCard, UpdateCard, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "UpdateDeadlineDate", dispidUpdateDeadlineDate, UpdateDeadlineDate, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "getDeadlineDate", dispidgetDeadlineDate, getDeadlineDate, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetVersion", dispidGetVersion, GetVersion, VT_BSTR, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "BeginRequest", dispidBeginRequest, BeginRequest, VT_EMPTY, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadBankCard", dispidReadBankCard, ReadBankCard, VT_BSTR, VTS_I4)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CheckPwdGetUserName", dispidCheckPwdGetUserName, CheckPwdGetUserName, VT_I2, VTS_BSTR VTS_BSTR )
	DISP_PROPERTY_EX_ID(CRF35OCXCtrl, "CustName", dispidCustName, GetCustName, SetCustName, VT_BSTR)
	DISP_PROPERTY_EX_ID(CRF35OCXCtrl, "StuempNo", dispidStuempNo, GetStuempNo, SetStuempNo, VT_BSTR)
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



#define OPEN_READER(x) \
	KSCardReader _reader(x); \
	if(_reader.Open()) return -1



//////////////////////////////////////////////////////////////////////////
static void str2bcd(LPCTSTR str,unsigned char *bcd,int len)
{
	int i;
	char temp[3] = "";
	for (i = 0;i < len; ++i)
	{
		memcpy(temp,str+i*2,2);
		bcd[i] = (temp[0] - '0') << 4;
		bcd[i] += (temp[1] - '0');
	}
}


static void date2bcd(char *str,unsigned char *bcd,int len)//test
{
		char sYear[3]="";
		char sMon[3]="";
		char sDay[3]="";
		char date[7]="";
		memset(sYear,0,sizeof(sYear));
		memset(sMon,0,sizeof(sMon));
		memset(sDay,0,sizeof(sDay));
		memset(bcd,0,sizeof(bcd));
        strcpy (date,str);
		memcpy(sYear,date+0,2);
		memcpy(sMon,date+2,2);
		memcpy(sDay,date+4,2);
		bcd[0]=atoi(sYear);
		bcd[1]=atoi(sMon);
		bcd[2]=atoi(sDay);

}

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
	m_param_name_map.insert(ParamName_Map::value_type(_T("cardno"),_T("CardId")));

	m_param_name_map.insert(ParamName_Map::value_type(_T("amount"),_T("MobileAmount")));
	m_param_name_map.insert(ParamName_Map::value_type(_T("amount"),_T("SidyAmount")));

	m_logFile.open("c:\\quancunlog.txt",std::ios_base::app | std::ios_base::out);

}


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

int CRF35OCXCtrl::OpenCOM()
{
	int ret = ConnectMF(m_nPortNo,19200L);
	if(ret != 0)
	{
		AfxMessageBox(_T("初始化读卡器失败!"));
		return -1;
	}
	return 0;
}


int CRF35OCXCtrl::CloseCOM(void)
{
	CloseMF();
	return 0;
}

short CRF35OCXCtrl::DoScan() 
{
	// TODO: Add your dispatch handler code here

	int ret = 0;
	OPEN_READER(m_nPortNo);
	//unsigned char snr[5] = "";
	unsigned long snr = 0;
	ret = ReadCardSNR(&snr);
	if(ret==0)
	{
		m_nCardNo = ntohl(snr);
		char cardno[16];
		ltoa(m_nCardNo, cardno, 10);
		SetWindowText(cardno);
		return 0;
	}else{
		return -2;
	}
}

void CRF35OCXCtrl::OnPortNoChanged() 
{
	SetModifiedFlag();
}


short CRF35OCXCtrl::UndoLoss(LPCTSTR mkey,long cardno,LPCTSTR blkver) 
{
	int ret;
	unsigned long snr = 0;
	OPEN_READER(m_nPortNo);

	if(ReadCardSNR(&snr))
	{
		return -2;
	}
	if(cardno != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -3;
	}
	ret = Load_WorkKey((char *) mkey);
	if (ret)
	{
		AfxMessageBox(_T("装载密码失败"));
		return -4;
	}
	ret = SMT_SetNormalFlagByBlkVerion((char *)blkver);
	if(ret)
	{
		AfxMessageBox(_T("更改黑名单标志出错"));
		return -5;
	}else{
		return 0;
	}
}

short CRF35OCXCtrl::ChangePassWord(LPCTSTR mkey,LPCTSTR newpwd,long cardno) 
{
	unsigned long snr = 0;
	int ret;
	OPEN_READER(m_nPortNo);

	if(ReadCardSNR(&snr))
	{
		return -2;
	}
	if(cardno != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -3;
	}
	ret = Load_WorkKey((char *) mkey);
	if (ret)
	{
		AfxMessageBox(_T("装载密码失败"));
		return -4;
	}

	unsigned char passwd[6]="";
	memcpy(passwd,newpwd,6);	
	ret=WriteCardPwd(passwd);
	if(ret)
	{
		AfxMessageBox(_T("更改密码失败"));
		return -5;
	}else{
		Beep(10);
		return 0;
	}
	
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
	return MySendRequest((LPCTSTR)u,NULL);
}

void CRF35OCXCtrl::Beep(int mSec)
{
	ControlBuzzer();
	//rf_beep(m_icdev,mSec);
}

int CRF35OCXCtrl::ReadCardSNR(unsigned long * snr)
{

	int ret = 0;	
	unsigned char cardid[5]="";
	unsigned long temp = 0;
	ret = ReadSerial(cardid);
	if (ret)
	{
		AfxMessageBox(_T("读卡失败!"));
		return ret;
	}	
	memcpy(&temp, cardid, sizeof(cardid) - 1);
	*snr = temp;
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

static MONEY_PACK_INFO g_packet_info;

int CRF35OCXCtrl::get_return_field(const CString &param_name,CString &param_value)
{
	RequestRet_Map::iterator i = g_request_return.find(param_name);
	if(i == g_request_return.end())
		return -1;
	param_value = i->second;
	return 0;
}

SHORT CRF35OCXCtrl::MySendRequest(LPCTSTR url, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	CString paramKey;
	get_return_field("paramKey",paramKey);
	bala.Format("%d",g_packet_info.bala);
	txCnt.Format("%d",g_packet_info.total_cnt);
	t_params += "&cardBala="+bala+"&txCnt="+txCnt+"&paramKey="+paramKey;
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
			return -1;
		}
		else
		{
			// 表示成功
			if("0000" == code)
			{
				CString outcardamount,cardno,sidyno,txcnt,paramKey;
				if(get_return_field("OutCardAmount",outcardamount))
				{
					// 没有金额字段
					return -1;
				}
				
				if(get_return_field("CardId",cardno))
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

				get_return_field("paramKey",paramKey);

				if (WriteSidy(outcardamount,cardno,sidyno,paramKey)==0)
				{
					//写卡成功
					return 0;
				}else{				
					return -1;
				}
			}
			else{
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

// ocx写卡失败 回传给后台
short CRF35OCXCtrl::ReportWriteCardError(LPCTSTR url, LPCTSTR serialno,LPCTSTR cardno)
{
	CString strResult;

	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();
	CString t_serialno(serialno);
	CString t_cardno(cardno);
	CString t_param ="cardno="+t_cardno+"&serialno="+t_serialno;

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS,t_param);

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
	return 0;
}

// 写卡
short CRF35OCXCtrl::WriteCard(LPCTSTR outcardamount, LPCTSTR cardno,LPCTSTR txcnt,LPCTSTR mainkey)
{
	unsigned long snr = 0;
	int ret;
	char str[1024]="";
	char date[128]="";
	char time[128]="";
	_strtime(time);   
	_strdate(date);
	strcat(str,date);
	strcat(str,"  ");
	strcat(str,time);
	m_logFile<<"打开串口"<<" "<<str<<std::endl;
	OPEN_READER(m_nPortNo);	
	m_logFile<<"写卡,card["<<cardno<<"]out_bala["<<outcardamount<<"]txcnt["<<txcnt<<"]"<<" "<<str<<std::endl;
	if(ReadCardSNR(&snr))
	{
		//读卡失败
		m_logFile<<"写卡失败,card["<<cardno<<"]"<<" "<<str<<std::endl;
		return -2;
	}
/*
	if(atol(cardno) != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		CloseCOM();
		return -3;
	}

	*/

//int Load_WorkKey(char *ascWorkKey)
	if (Load_WorkKey((char*)mainkey)==0)
	{
		//动态库加载成功
		long card_id = atol(cardno);
		unsigned long l = (unsigned long)card_id;
		int tx_cnt = atoi(txcnt)+1;
		int out_card_amount = atoi(outcardamount);
		ret = SMT_SetCardMoney(l,out_card_amount,tx_cnt);
		if(ret==0)
		{
			//写卡成功
			m_logFile<<"写卡成功,card["<<cardno<<"]"<<" "<<str<<std::endl;
			return 0;
		}else{			
			m_logFile<<"写卡失败,card["<<cardno<<"]ret["<<ret<<"]"<<" "<<str<<std::endl;
			if(ret==-10){
				return -10;
			}else{
				return 2;
			}
		}
	}else{
		//密钥设置失败
		m_logFile<<"写卡失败,card["<<cardno<<"]ret["<<ret<<"]"<<" "<<str<<std::endl;
		return 1;
	}

}

LONG CRF35OCXCtrl::ReadCardPocket(SHORT pocket,LPCTSTR cardno,LPCTSTR mainkey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	//int Load_WorkKey(char *ascWorkKey)
	//int ConnectMF(int com,int baud)
	CString paramKey;
	get_return_field("paramKey",paramKey);
	unsigned long snr = 0;

	OPEN_READER(m_nPortNo);
	if(ReadCardSNR(&snr))
	{
		//读卡失败
		return 1;
	}
	if(atol(cardno) != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return 2;
	}

	//重置
	RetsetPacketInfo();
	if (Load_WorkKey((LPTSTR)(LPCTSTR)paramKey)==0)
	{
		if (SMT_GetPacketInfo(pocket,&g_packet_info)==0)
		{
			return 0;
		}else{
			return -1;
		}
		
	}else{
		return -2;
	}
		
}

LONG CRF35OCXCtrl::GetPacketInfo(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	LONG ret = 0;
	CString code(param);
	if (code=="bala")
	{
		ret = g_packet_info.bala;
	}
	if (code=="daybala")
	{
		ret = g_packet_info.daybala;
	}
	if (code=="total_cnt")
	{
		ret = g_packet_info.total_cnt;
	}
	if (code=="day_cnt")
	{		
		ret = g_packet_info.day_cnt;
	}
	if (code=="time_cnt")
	{
		ret = g_packet_info.time_cnt;
	}
	if (code=="date")
	{		
		ret = g_packet_info.date;
	}
	if (code=="time")
	{
		ret = g_packet_info.time;
	}

	return ret;
}

void CRF35OCXCtrl::RetsetPacketInfo(void)
{
	/*
	g_packet_info.bala = 0;
	g_packet_info.daybala = 0;
	g_packet_info.total_cnt = 0;
	g_packet_info.day_cnt = 0;
	g_packet_info.time_cnt = 0;
	g_packet_info.date = 0;
	g_packet_info.time = 0;
	*/
	memset(&g_packet_info,0,sizeof g_packet_info);
}



SHORT CRF35OCXCtrl::RewriteCardInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	int ret;
	CString outcardamount,cardno,txcnt,paramKey;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("CardId",cardno))
	{
		// 没有卡号字段
		return -1;
	}

    if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -1;
	}

	get_return_field("paramKey",paramKey);
	ret = WriteCard(outcardamount,cardno,txcnt,paramKey);
	return ret;
}

SHORT CRF35OCXCtrl::ReportCardWriteFailue(LPCTSTR url, LPCTSTR serialno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	int ret = 0;
	ret = ReportWriteCardError(url,serialno,"0");
	return ret;
}

int CRF35OCXCtrl::do_get_mainkey(LPCTSTR url,void *param)
{
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
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,100);

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
			if (chunk.memory)
			{
				free(chunk.memory);
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
		if(strResult!=""){
			g_request_return.insert(RequestRet_Map::value_type("paramKey",strResult));
		}
	}

	return 0;
}

SHORT CRF35OCXCtrl::GetMainKey(LPCTSTR url)
{
	int ret;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ret = do_get_mainkey(url,NULL);
	if(ret)
		return (SHORT)ret;
	else
		return 0;
}
int CRF35OCXCtrl::do_write_card_and_request(LPCTSTR url, LPCTSTR cardno,LPCTSTR outcardamount,LPCTSTR txcnt, LPCTSTR params)
{
	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	CString paramKey;
	get_return_field(_T("paramKey"),paramKey);
	bala.Format("%d",g_packet_info.bala);
	txCnt.Format("%d",g_packet_info.total_cnt);
	t_params += "&cardBala="+bala+"&txCnt="+txCnt+"&paramKey="+paramKey;
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */
	int ret = WriteCard(outcardamount,cardno,txcnt,paramKey);
	if (ret ==0)
	{
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
	}else if (ret ==-10)
	{
		return -10;
	}
	else return -100;
}
SHORT CRF35OCXCtrl::MobileTransWriteCard(LPCTSTR url, LPCTSTR cardno,LPCTSTR outcardamount,LPCTSTR txcnt, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return do_write_card_and_request(url,cardno,outcardamount,txcnt,params);
}

SHORT CRF35OCXCtrl::ElectTransWriteCard(LPCTSTR url, LPCTSTR cardno, LPCTSTR outcardamount,LPCTSTR txcnt, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return do_write_card_and_request(url,cardno,outcardamount,txcnt,params);
}


SHORT CRF35OCXCtrl::UpdateCardInfo(LONG cardno, LONG feetype, LPCTSTR enddate, LPCTSTR mkey)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());

	unsigned long snr = 0;
	int ret;
	OPEN_READER(m_nPortNo);
	
	if(ReadCardSNR(&snr))
	{
		return -2;
	}
	if(cardno != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -3;
	}
	ret = Load_WorkKey((char *) mkey);
	if (ret)
	{
		AfxMessageBox(_T("装载密码失败"));
		return -4;
	}

	unsigned char ucCardTypeRight[1];
	unsigned char deadline[3];
	char date[7]="";
	strcpy(date,enddate);
	date2bcd(date,deadline,3);	
	ucCardTypeRight[0] = (unsigned char)feetype;
	ret = SMT_ChangeCardRightType(ucCardTypeRight);
	if(ret)
	{
		AfxMessageBox(_T("更新卡权限类别失败"));
		ret = -5;
	}
	else if((ret = SMT_ChangeDeadLineDate(deadline)) != 0)
	{
		AfxMessageBox(_T("更新有效期失败"));
		ret = -6;
	}
	else
	{
		ret = 0;
	}
	return ret;
}

SHORT CRF35OCXCtrl::BeginUpdateCard(ULONG cardno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString val;
	m_cardprop_map.clear();

	val.Format("%lu",cardno);
	//AfxMessageBox(val);
	m_cardprop_map.insert(ParamName_Map::value_type(_T("phyno"),val));
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

SHORT CRF35OCXCtrl::UpdateCard(LPCTSTR mkey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString val_name;
	CString val;
	CString phyno;
	LONG cardno;
	char str[1024]="";
	char date[128]="";
	char time[128]="";
	_strtime(time);   
	_strdate(date);
	strcat(str,date);
	strcat(str,"  ");
	strcat(str,time);
	int int_val;
	unsigned char char_val[20];
	ParamName_Map::iterator i;
	unsigned long snr = 0;
	int ret;
	OPEN_READER(m_nPortNo);
	
	i = m_cardprop_map.find(_T("phyno"));
	if(i == m_cardprop_map.end())
	{
		ret = -1;
		goto L_FAILD;
	}

	phyno = i->second;
	cardno = atoi((LPCTSTR)phyno);
	//AfxMessageBox(phyno);
	
	if(ReadCardSNR(&snr))
	{
		AfxMessageBox(_T("读卡失败"));
		ret =  -2;
		goto L_FAILD;
	}
	if(cardno != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		ret = -3;
		goto L_FAILD;
	}
	ret = Load_WorkKey((char *) mkey);
	if (ret)
	{
		AfxMessageBox(_T("装载密码失败"));
		ret = -4;
		goto L_FAILD;
	}

	for(i = m_cardprop_map.begin();i!=m_cardprop_map.end();++i)
	{
		val_name = i->first;
		val = i->second;
		if(val_name.Compare(_T("cardno"))==0)
		{
			// continue
		}
		else if(val_name.Compare(_T("feetype"))==0)
		{
			// 
			int_val = atoi((LPCTSTR)val);
			char_val[0] = (unsigned char)int_val;
			ret = SMT_ChangeCardRightType(char_val);
			if(ret)
			{
				AfxMessageBox(_T("更新卡权限类别失败"));
				ret = -5;
				goto L_FAILD;
			}
		}
		else if(val_name.Compare(_T("expiredate"))==0)
		{
			unsigned char deadline[3];
			char date[7]="";
			strcpy(date,val);
			date2bcd(date,deadline,3);
			if((ret = SMT_ChangeDeadLineDate(deadline)) != 0)
			{
				AfxMessageBox(_T("更新有效期失败"));
				ret = -6;
				goto L_FAILD;
			}
		}
		else if(val_name.Compare(_T("deptno"))==0)
		{
			ret = SMT_ChangeDepartmentNo((unsigned char*)(LPCTSTR)val);
			if(ret)
			{
				AfxMessageBox(_T("更新院系代码失败"));
				ret = -7;
				goto L_FAILD;
			}
		}
		else if(val_name.Compare(_T("stuempno"))==0)
		{
			//val.TrimLeft(" ");
			//val.TrimLeft("]");
			//val="*"+val;
			//val=val+"*"
			m_logFile<<"更新学工号,stuempno["<<val<<"]ret["<<ret<<"]"<<" "<<str<<std::endl;
			if(SMT_ChangeCardNo((unsigned char*)(LPCTSTR)val))
			{
				AfxMessageBox(_T("更新学工号失败"));
				ret = -8;
				goto L_FAILD;
			}
		}
		else
		{
			continue;
		}
	}
	return 0;
L_FAILD:
	return ret;
}

SHORT CRF35OCXCtrl::NetTransWriteCard(LPCTSTR url, LPCTSTR cardno, LPCTSTR outcardamount, LPCTSTR txcnt, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	ResetInfo();
	g_request_return.insert(RequestRet_Map::value_type("url",url));
	g_request_return.insert(RequestRet_Map::value_type("CardId",cardno));
	g_request_return.insert(RequestRet_Map::value_type("OutCardAmount",outcardamount));
	g_request_return.insert(RequestRet_Map::value_type("txCnt",txcnt));
	g_request_return.insert(RequestRet_Map::value_type("params",params));

	return do_write_card_and_request(url,cardno,outcardamount,txcnt,params);
}

SHORT CRF35OCXCtrl::ReNetTransWriteCard(void)
{
	// TODO: Add your dispatch handler code here
	CString url,cardno,outcardamount,txcnt,params;
	if(get_return_field("url",url))
	{
		// 没有金额字段
		return -1;
	}
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("CardId",cardno))
	{
		// 没有卡号字段
		return -1;
	}

	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -1;
	}

	if(get_return_field("params",params))
	{
		// 没有卡号字段
		return -1;
	}

	return do_write_card_and_request(url,cardno,outcardamount,txcnt,params);
}


SHORT CRF35OCXCtrl::ReverseNetTrans(LPCTSTR url)
{

	CString cardno,outcardamount,txcnt,params;

	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("CardId",cardno))
	{
		// 没有卡号字段
		return -1;
	}

	if(get_return_field("txCnt",txcnt))
	{
		// 没有卡号字段
		return -1;
	}

	if(get_return_field("params",params))
	{
		// 没有卡号字段
		return -1;
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


static CONSUME_LIMIT g_consume_limit;

LONG CRF35OCXCtrl::getComsumerLimit(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	LONG ret = 0;
	CString code(param);
	if (code=="max_per_count")
	{
		ret = g_consume_limit.max_per_count;
	}
	if (code=="max_per_day")
	{
		ret = g_consume_limit.max_per_day;
	}
	return ret;
}


void CRF35OCXCtrl::ResetconsumeLimitInfo(void)
{
	//全局初始化 /清空
	g_consume_limit.max_per_count =0;
	g_consume_limit.max_per_day=0;
}


SHORT CRF35OCXCtrl::ReadCardConsumerLimit(LPCTSTR cardno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	ResetconsumeLimitInfo();

	CString paramKey;
	get_return_field("paramKey",paramKey);
	unsigned int max_per_count = 0;
	unsigned int max_per_day = 0;
	unsigned long snr = 0;

	if (ConnectMF(m_nPortNo,19200)==0)
	{
		if(ReadCardSNR(&snr))
		{
			//读卡失败
			CloseMF();
			return -1;
		}
		if(atol(cardno) != (long)ntohl(snr))
		{
			AfxMessageBox(_T("卡号不正确"));
			CloseMF();
			return -2;
		}

		//重置
		if (Load_WorkKey((LPTSTR)(LPCTSTR)paramKey)==0)
		{	
			int limitret = ReadConsumeLimit(&max_per_count,&max_per_day);

			if (limitret==0)
			{
				g_consume_limit.max_per_count=max_per_count;
				g_consume_limit.max_per_day=max_per_day;

				CloseMF();
				return 0;
			}else{
				CloseMF();
				return limitret;
			}
			//	return 0;

		}else{
			CloseMF();
			return -4;
		}

	}else{
		return -5;
	}
}

SHORT CRF35OCXCtrl::ResetConsumerLimit(LPCTSTR cardid, LPCTSTR maxpercount, LPCTSTR maxperday)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString paramKey;
	get_return_field("paramKey",paramKey);

	unsigned long snr = 0;
	int ret;
	OPEN_READER(m_nPortNo);

	if(ReadCardSNR(&snr))
	{
		//读卡失败
		return -2;
	}
	if(atol(cardid) != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -3;
	}

	//int Load_WorkKey(char *ascWorkKey)
	if (Load_WorkKey((LPTSTR)(LPCTSTR)paramKey)==0)
	{
		//密钥设置成功
		//int SMT_PacketSetMoney(int nPacketNo,int nMoney);
		//动态库加载成功
		int max_per_count = atoi(maxpercount);
		int max_per_day = atoi(maxperday);			

		if (SetConsumeLimit(max_per_count,max_per_day)==0)
		{
			//写卡成功
			return 0;
		}else{
			return 2;				
		}

		//		return 0;
	}else{
		//密钥设置失败
		return 1;
	}
}

LONG CRF35OCXCtrl::ReadCardSidyNo(LPCTSTR cardno, LPCTSTR mainkey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// TODO: Add your dispatch handler code here
	CString paramKey;
	get_return_field("paramKey",paramKey);
	int sidyno = 0;
	unsigned long snr = 0;

	OPEN_READER(m_nPortNo);
	if(ReadCardSNR(&snr))
	{
		//读卡失败
		return -1;
	}
	if(atol(cardno) != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -2;
	}

	//重置
	if (Load_WorkKey((LPTSTR)(LPCTSTR)paramKey)==0)
	{
		if (SMT_ReadSubsidy(&sidyno)==0)
		{
			return sidyno;
		}else{
			return -3;
		}

	}else{
		return -4;
	}

}

SHORT CRF35OCXCtrl::RewriteSidy(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString outcardamount,cardno,sidyno,paramKey;
	if(get_return_field("OutCardAmount",outcardamount))
	{
		// 没有金额字段
		return -1;
	}

	if(get_return_field("CardId",cardno))
	{
		// 没有卡号字段
		return -1;
	}

	if(get_return_field("sidyno",sidyno))
	{
		// 没有卡号字段
		return -1;
	}

	get_return_field("paramKey",paramKey);

	// TODO: Add your dispatch handler code here
	int ret = WriteSidy(outcardamount,cardno,sidyno,paramKey);
	return ret;
}

short CRF35OCXCtrl::WriteSidy(LPCTSTR outcardamount,LPCTSTR cardno,LPCTSTR sidyno,LPCTSTR mainkey){
	unsigned long snr = 0;
	int ret;
	OPEN_READER(m_nPortNo);

	if(ReadCardSNR(&snr))
	{
		//读卡失败
		return -2;
	}
	if(atol(cardno) != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -3;
	}

	//int Load_WorkKey(char *ascWorkKey)
	if (Load_WorkKey((char*)mainkey)==0)
	{
		//密钥设置成功
		//int SMT_PacketSetMoney(int nPacketNo,int nMoney);
		//动态库加载成功
		int out_card_amount = atoi(outcardamount);
		int batch_no = atoi(sidyno);
		if (SMT_WriteSubsidy(out_card_amount,batch_no)==0)
		{
			//写卡成功
			return 0;
		}else{
			return 2;				
		}

	}else{
		//密钥设置失败
		return 1;
	}

}


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

int CRF35OCXCtrl::do_request_and_write_card(LPCTSTR url, LPCTSTR cardno,LPCTSTR outcardamount,LPCTSTR txcnt, LPCTSTR params)
{
CString strResult;
CString t_params(params);
CString bala ="";
CString txCnt = "";
CString paramKey;
get_return_field("paramKey",paramKey);
bala.Format("%d",g_packet_info.bala);
txCnt.Format("%d",g_packet_info.total_cnt);
t_params += "&cardBala="+bala+"&txCnt="+txCnt+"&paramKey="+paramKey;
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
			CString outcardamount,cardno,txcnt,paramKey;
			if(get_return_field("OutCardAmount",outcardamount))
			{
				// 没有金额字段
				return -2;
			}

			if(get_return_field("CardId",cardno))
			{
				// 没有卡号字段
				return -2;
			}
			if(get_return_field("txCnt",txcnt))
			{
				// 没有卡号字段
				return -2;
			}

			get_return_field("paramKey",paramKey);
			if (WriteCard(outcardamount,cardno,txcnt,paramKey)==0)
			{
				//写卡成功
				return 0;
			}else{				
				return -1;
			}
		}
		else{
			//领取补助失败
			return 1;
		}
	}
}
return 2;

}


SHORT CRF35OCXCtrl::CardTransWriteCard(LPCTSTR outcardamount, LPCTSTR cardno, LPCTSTR txcnt)
{
	CString paramKey;
	m_logFile<<"CardTransWriteCard "<<" "<<paramKey<<std::endl;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	
	m_logFile<<"begin paramKey "<<" "<<paramKey<<std::endl;
	get_return_field("paramKey",paramKey);
	m_logFile<<"end paramKey "<<" "<<paramKey<<std::endl;
	// TODO: Add your dispatch handler code here
	return WriteCard(outcardamount,cardno,txcnt,paramKey);

}


SHORT CRF35OCXCtrl::UpdateDeadlineDate(LPCTSTR url, LPCTSTR cardno, LPCTSTR enddate, LPCTSTR param)
{

	unsigned long snr = 0;
	int ret;
	OPEN_READER(m_nPortNo);
	if(ReadCardSNR(&snr))
	{
		return -2;
	}
	if(atol(cardno) != (long)ntohl(snr))
	{
		AfxMessageBox(_T("卡号不正确"));
		return -3;
	}
	CString paramKey;
	get_return_field("paramKey",paramKey);
	ret = Load_WorkKey((LPTSTR)(LPCTSTR) paramKey);
	if (ret)
	{
		AfxMessageBox(_T("装载密码失败"));
		return -4;
	}
	unsigned char ucShowCardNo[5];
	int nDealCardNo[1];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	ret = SMT_ReadCardStateInfo(ucShowCardNo,
		nDealCardNo,
		ucDeadLineDate,
		ucCardRightType);




	//unsigned char ucCardTypeRight[1];
	unsigned char deadline[3];
	char date[7]="";
	strcpy(date,enddate);
	date2bcd(date,deadline,3);
	if (memcmp(ucDeadLineDate,deadline,sizeof(ucDeadLineDate))==0)
	{
		return 0;
	}

	if((ret = SMT_ChangeDeadLineDate(deadline)) != 0)
	{
		return -6;
	}
	else
	{
		//更新成功

		CString strResult;
		CString t_params(param);
		CString t_cardno(cardno);
		CString t_enddate(enddate);
		if(t_params==""){
			t_params = "cardno="+t_cardno+"&enddate="+t_enddate;
		}else{
			t_params += "&cardno="+t_cardno+"&enddate="+t_enddate;
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
}

BSTR CRF35OCXCtrl::getDeadlineDate(LPCTSTR url,LPCTSTR cardno,LPCTSTR params)
{


	CString strResult;
	CString retResult("");
	CString t_params(params);
	CString t_cardno(cardno);
	if (t_params=="")
	{
		t_params = "cardno="+t_cardno;
	}else{
		t_params += "&cardno="+t_cardno;
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

void CRF35OCXCtrl::BeginRequest(LPCTSTR request_name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
}

CString CRF35OCXCtrl::do_parsebankno(char *buffer,int len)
{
	char bankno[30] = "";
	char *p;
	int i,j;
	char begin_str[]="+99";
	char begin_str2[]=";";
	int padlen;
	i = 0;
//先查分号  再查99
	p = strstr(buffer,begin_str2);
	if(!p)
	{
	p = strstr(buffer,begin_str);
	if(!p)
		return "";
	padlen = strlen(begin_str);
	}
	else
	{
	padlen = strlen(begin_str2);
	}
	i = p - buffer;
	for(j=0;j<len-i;++j)
	{
		if(p[padlen+j] == '=') break;
		bankno[j] = p[padlen+j];
	}
	CString r = bankno;
	return r;
}
#if 1
CString CRF35OCXCtrl::readbankno(CSerialPort *serialport,int portno)
{
	char buffer[256];
	CEvent event(FALSE,TRUE);
	OVERLAPPED overlapped;
	DWORD dwBytesTransfered = 0;
	memset(&overlapped,0,sizeof overlapped);
	overlapped.hEvent = event;
	serialport->ClearReadBuffer();
	serialport->ClearWriteBuffer();
	try
	{
		if(serialport->Read(buffer,100,overlapped,&dwBytesTransfered)==FALSE)
		{
			if(GetLastError()==ERROR_IO_PENDING)
			{
				dwBytesTransfered = 0;
				serialport->GetOverlappedResult(overlapped,dwBytesTransfered,TRUE);
			}
		}
	}
	catch (CSerialException* e)
	{
		if(e->m_dwError == ERROR_IO_PENDING)
		{
			e->Delete();
			dwBytesTransfered = 0;
			serialport->GetOverlappedResult(overlapped,dwBytesTransfered,TRUE);
		}
		else
		{
			DWORD dwError = e->m_dwError;
			e->Delete();
			return "";
		}
	}
	serialport->SetMask(EV_TXEMPTY);
	if(dwBytesTransfered > 0)
	{
		buffer[dwBytesTransfered] = 0;
		//AfxMessageBox(buffer);
		return do_parsebankno(buffer,dwBytesTransfered);
	}
	return "";
}
#else
CString CRF35OCXCtrl::readbankno(int portno)
{
	CString strResult;
	KS_SerialPort serial(portno,9600);
	//char bankno[50]
	char bankno2[256];
	char strbank[256];
	int i,j,endc,len;

	strResult.Empty();
	memset(strbank,0,sizeof strbank);
	memset(bankno2,0,sizeof bankno2);

	if(serial.open())
	{
		AfxMessageBox(_T("打开串口失败"));
		return strResult;
	}


	i = 0;
	do 
	{
		if((len=serial.read((unsigned char*)bankno2+i,30,15))<=0)
		{
			//serial.Purge(PURGE_TXABORT|PURGE_RXABORT|PURGE_TXCLEAR|PURGE_RXCLEAR);
			break;
		}
		i+=len;
	} while (i < 30);

	if(i == 0)
		return strResult;
	Sleep(200);
	

	sprintf(strbank,"[%d]%s",i,bankno2);
	//AfxMessageBox(strbank);
	memset(strbank,0,sizeof strbank);

	for(i = 0;i < 30;++i)
	{
		if(bankno2[i] == 0x25 && bankno2[i+1] == 0x42) // 信用卡
		{
			i = i+2;
			endc='^';
			break;
		}
		else if(bankno2[i] == 0x3b)
		{
			i = i+1;
			endc = '=';
			break;
		}
	}
	// 有问题
	if(i >= 10)
		return strResult;
	for(j=0;i < 30 ;++i,++j)
	{
		if(bankno2[i] == endc)
			break;
		strbank[j] = bankno2[i];

	}

	strResult.Format("%s",strbank);

	return strResult;
}
#endif 
BSTR CRF35OCXCtrl::ReadBankCard(LONG portno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
#if 1
	CSerialPort serialport;
	serialport.Open(portno,9600,CSerialPort::NoParity, 8, CSerialPort::OneStopBit, CSerialPort::XonXoffFlowControl, TRUE);
	COMMTIMEOUTS tm;
	memset(&tm,0,sizeof tm);
	tm.ReadIntervalTimeout = MAXDWORD;
	serialport.GetTimeouts(tm);
	tm.ReadTotalTimeoutConstant = 15000;
	tm.ReadTotalTimeoutMultiplier = 0;
	serialport.SetTimeouts(tm);
	strResult = readbankno(&serialport,portno);
#else
	int i;
	for(i= 0;i < 10;++i)
	{
		strResult = readbankno(portno);
		if(strResult.IsEmpty())
		{
			Sleep(1000);
		}
		else
			break;
	}
#endif 
	return strResult.AllocSysString();
}


//////////////////////////////////////////////////////////////////////////
// 
KSCardReader::KSCardReader(int port):m_port(port),is_open_(0)
{
	
}
KSCardReader::~KSCardReader()
{
	if(is_open_)
		CloseMF();
}
int KSCardReader::Open()
{
	if(is_open_)
		return 0;
	if(ConnectMF(m_port,19200))
		return -1;
	is_open_ = 1;
	return 0;
}
SHORT CRF35OCXCtrl::CheckPwdGetUserName(LPCTSTR url, LPCTSTR pwd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int ret;
	CString get_key_url;
	unsigned char bcd_pwd[3],input_bcd_pwd[3];
	unsigned char ucName[9]="";
	unsigned char ucDutyNo[5]="";
	unsigned char ucCertificateNo[21]="";
	unsigned char ucDepartmentNo[11]="";
	unsigned char ucIdentifyNo[5]="";
	unsigned char ucSexNo[2]="";
	unsigned char ucCardNo[21]="";
	OPEN_READER(m_nPortNo);

	// 检查卡密码
	get_key_url = url;
	get_key_url += "getSysPara.do";
	ret = do_get_mainkey((LPCTSTR)get_key_url,NULL);
	if(ret)
		return ret;

	CString paramKey;
	get_return_field("paramKey",paramKey);
	if(paramKey.GetLength()!=16)
		return -4;
	ret = Load_WorkKey((LPTSTR)(LPCTSTR) paramKey);
	if (ret)
	{
		return -4;
	}
	ret = SMT_ReadPersonalPassword(bcd_pwd);
	if(ret)
	{
		return -6;
	};
	str2bcd((LPCTSTR)pwd,input_bcd_pwd,3);
	if(memcmp(bcd_pwd,input_bcd_pwd,3)!=0)
	{
		// 密码不符
		return 8;
	}
	ret = SMT_ReadPersonalInfo(ucName,ucDutyNo,ucCertificateNo,ucDepartmentNo,
		ucIdentifyNo,ucSexNo,ucCardNo);
	if(ret)
		return -6;
	m_CustName = ucName;
	m_StuempNo = ucCardNo;
	return 0;
}

BSTR CRF35OCXCtrl::GetCustName(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	strResult = m_CustName;

	return strResult.AllocSysString();
}

void CRF35OCXCtrl::SetCustName(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}

BSTR CRF35OCXCtrl::GetStuempNo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	strResult = m_StuempNo;

	return strResult.AllocSysString();
}

void CRF35OCXCtrl::SetStuempNo(LPCTSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your property handler code here

	SetModifiedFlag();
}
