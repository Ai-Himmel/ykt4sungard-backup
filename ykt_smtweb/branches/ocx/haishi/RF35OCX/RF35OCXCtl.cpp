// RF35OCXCtl.cpp : Implementation of the CRF35OCXCtrl ActiveX Control class.

#include "stdafx.h"
#include "RF35OCX.h"
#include "RF35OCXCtl.h"
#include "RF35OCXPpg.h"
//#include "mwrf32.h"
#include "comm.h"
#include ".\rf35ocxctl.h"
#include "curl\curl.h"
#include "tinyxml.h"
#include "CardDLL.h"

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
	DISP_FUNCTION_ID(CRF35OCXCtrl, "MySendRequest", dispidMySendRequest, MySendRequest, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetRequestRetInfo", dispidGetRequestRetInfo, GetRequestRetInfo, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReadCardPocket", dispidReadCardPocket, ReadCardPocket, VT_I4, VTS_I2 VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetPacketInfo", dispidGetPacketInfo, GetPacketInfo, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "RewriteCardInfo", dispidRewriteCardInfo, RewriteCardInfo, VT_I2, VTS_NONE)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ReportCardWriteFailue", dispidReportCardWriteFailue, ReportCardWriteFailue, VT_I2, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "GetMainKey", dispidGetMainKey, GetMainKey, VT_I2, VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "MobileTransWriteCard", dispidMobileTransWriteCard, MobileTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "ElectTransWriteCard", dispidElectTransWriteCard, ElectTransWriteCard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "CheckTurnOver", dispidCheckTurnOver, CheckTurnOver, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "turnOverWritecard", dispidturnOverWritecard, turnOverWritecard, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CRF35OCXCtrl, "turnoverChecked", dispidturnoverChecked, turnoverChecked, VT_I2, VTS_BSTR VTS_BSTR VTS_BSTR)
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

	// TODO: Initialize your control's instance data here.
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
	ret = OpenCOM();
	if (ret==0)
	{
		//unsigned char snr[5] = "";
		unsigned long snr = 0;
		ret = ReadCardSNR(&snr);
		if(ret==0)
		{
			m_nCardNo = ntohl(snr);
			char cardno[16];
			ltoa(m_nCardNo, cardno, 10);
			SetWindowText(cardno);
			CloseCOM();
			return 0;
		}else{
			CloseCOM();
			return -2;
		}
		
	}else{
		return -1;
	}
	
}

void CRF35OCXCtrl::OnPortNoChanged() 
{
	SetModifiedFlag();
}


short CRF35OCXCtrl::UndoLoss(LPCTSTR mkey,long cardno,LPCTSTR blkver) 
{
	unsigned long snr = 0;
	int ret = OpenCOM();
	if (ret==0)
	{
		if(ReadCardSNR(&snr))
		{
			CloseCOM();
			return -2;
		}
		if(cardno != (long)ntohl(snr))
		{
			AfxMessageBox(_T("卡号不正确"));
			CloseCOM();
			return -3;
		}
		ret = Load_WorkKey((char *) mkey);
		if (ret)
		{
			AfxMessageBox(_T("装载密码失败"));
			CloseCOM();
			return -4;
		}
		ret = SMT_SetNormalFlagByBlkVerion((char *)blkver);
		if(ret)
		{
			AfxMessageBox(_T("更改黑名单标志出错"));
			CloseCOM();
			return -5;
		}else{
			CloseCOM();
			return 0;
		}
		
	}else{
		return -1;
	}
}

short CRF35OCXCtrl::ChangePassWord(LPCTSTR mkey,LPCTSTR newpwd,long cardno) 
{
	unsigned long snr = 0;
	int ret = OpenCOM();
	if (ret==0)
	{
		if(ReadCardSNR(&snr))
		{
			CloseCOM();
			return -2;
		}

		if(cardno != (long)ntohl(snr))
		{
			AfxMessageBox(_T("卡号不正确"));
			CloseCOM();
			return -3;
		}

		ret = Load_WorkKey((char *) mkey);
		if (ret)
		{
			AfxMessageBox(_T("装载密码失败"));
			CloseCOM();
			return -4;
		}

		unsigned char passwd[6]="";
		memcpy(passwd,newpwd,6);	
		ret=WriteCardPwd(passwd);
		if(ret)
		{
			AfxMessageBox(_T("更改密码失败"));
			CloseCOM();
			return -5;
		}else{
			Beep(10);
			CloseCOM();
			return 0;
		}
		
	}else{
		return -1;
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



static RequestRetInfo g_request_ret;


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

SHORT CRF35OCXCtrl::MySendRequest(LPCTSTR url, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	bala.Format("%d",g_packet_info.bala);
	txCnt.Format("%d",g_packet_info.total_cnt);
	t_params += "&cardBala="+bala+"&txCnt="+txCnt+"&paramKey="+g_request_ret.paramKey;
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

		node = node->FirstChild();//errcode节点
		textnode = node->FirstChild();//根节点
		CString code = textnode->Value();
		if (code=="0000")
		{
			g_request_ret.errcode = code;
			//完成工作－－>显示信息 出卡值
			node1 = node->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.errmsg = textnode->Value();//错误消息
			node1 = node1->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.amount = textnode->Value();//补助金额
			node1 = node1->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.outcardamount = textnode->Value();//出卡值
			node1 = node1->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.serialno = textnode->Value();//处理流水号

			node1 = node1->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.paramKey = textnode->Value();//密钥

			node1 = node1->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.cardno = textnode->Value();//补助卡号

			if (WriteCard(g_request_ret.outcardamount,g_request_ret.cardno,g_request_ret.paramKey)==0)
			{
				//写卡成功
				return 0;
			}else{				
				return -1;
			}

		}else{
			//领取补助失败
			g_request_ret.errcode = code;
			node1 = node->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.errmsg = textnode->Value();//错误消息
			return 1;
		}
	}
	
	return 2;
}


BSTR CRF35OCXCtrl::GetRequestRetInfo(LPCTSTR param)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString code(param);
	CString strResult;
	if (code=="errcode")
	{
		strResult = g_request_ret.errcode;
	}
	else if (code=="errmsg")
	{
		strResult = g_request_ret.errmsg;
	}
	else if (code=="serialno")
	{
		strResult = g_request_ret.serialno;
	}
	else if (code=="amount")
	{		
		strResult = g_request_ret.amount;
	}
	else if (code=="outcardamount")
	{
		strResult = g_request_ret.outcardamount;
	}
	else if (code=="cardno")
	{
		strResult = g_request_ret.cardno;
	}
	else if (code=="paramKey")
	{
		strResult = g_request_ret.paramKey;
	}

	return strResult.AllocSysString();
}
void CRF35OCXCtrl::ResetInfo(void)
{
	//全局初始化 /清空
	g_request_ret.amount ="";
	g_request_ret.errcode="";
	g_request_ret.errmsg="";
	g_request_ret.outcardamount="";
	g_request_ret.serialno="";
	g_request_ret.cardno="";
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
short CRF35OCXCtrl::WriteCard(LPCTSTR outcardamount, LPCTSTR cardno,LPCTSTR mainkey)
{
	unsigned long snr = 0;
	int ret = OpenCOM();
	if (ret==0)
	{
		if(ReadCardSNR(&snr))
		{
			//读卡失败
			CloseCOM();
			return -2;
		}
		if(atol(cardno) != (long)ntohl(snr))
		{
			AfxMessageBox(_T("卡号不正确"));
			CloseCOM();
			return -3;
		}
	
	//int Load_WorkKey(char *ascWorkKey)
		if (Load_WorkKey((char*)mainkey)==0)
		{
			//密钥设置成功
			//int SMT_PacketSetMoney(int nPacketNo,int nMoney);
				//动态库加载成功
				int out_card_amount = atoi(outcardamount);
				if (SMT_PacketSetMoney(1,out_card_amount)==0)
				{
					//写卡成功
					CloseMF();
					return 0;
				}else{
					CloseMF();
					return 2;					
				}

			}else{
			//密钥设置失败
			CloseMF();
			return 1;
			}
	}else{
		CloseMF();
		return 3;
	}
}

LONG CRF35OCXCtrl::ReadCardPocket(SHORT pocket,LPCTSTR cardno,LPCTSTR mainkey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	//int Load_WorkKey(char *ascWorkKey)
	//int ConnectMF(int com,int baud)
	unsigned long snr = 0;

	if (ConnectMF(m_nPortNo,19200)==0)
	{
		if(ReadCardSNR(&snr))
		{
			//读卡失败
			CloseCOM();
			return 1;
		}
		CString card_no(cardno);
		if((atol(cardno) != (long)ntohl(snr))&&(card_no!="0"))
		{
			AfxMessageBox(_T("卡号不正确"));
			CloseCOM();
			return 2;
		}
		//重置
		RetsetPacketInfo();
		if (Load_WorkKey((LPTSTR)(LPCTSTR)g_request_ret.paramKey)==0)
		{
			if (SMT_GetPacketInfo(pocket,&g_packet_info)==0)
			{
				CloseMF();
				return 0;
			}else{
				CloseMF();
				return -1;
			}
			
		}else{
			CloseMF();
			return -2;
		}
		
	}else{
		return -3;
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

	int ret = WriteCard(g_request_ret.outcardamount,g_request_ret.cardno,g_request_ret.paramKey);
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
			g_request_ret.paramKey=strResult;
		}
	}

	return 0;
}

SHORT CRF35OCXCtrl::MobileTransWriteCard(LPCTSTR url, LPCTSTR cardno,LPCTSTR outcardamount, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;
	CString t_temp="";
	t_params.AppendFormat("&cardId=%s",cardno);
	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */


	if (WriteCard(outcardamount,cardno,g_request_ret.paramKey)==0)
	{
		curl = curl_easy_init();

		if (curl)
		{
			curl_easy_setopt(curl,CURLOPT_URL,url);
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 180); 
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
			if(todoElement==NULL){
				return -1;
			}
			node = todoElement->FirstChild();//head节点
			if (node==NULL)
			{
				return -1;
			}
			node = node->FirstChild();//errcode节点
			if (node==NULL)
			{
				return -1;
			}
			textnode = node->FirstChild();//根节点
			if (textnode==NULL)
			{
				return -1;
			}
			CString code = textnode->Value();
			if (code=="0000")
			{
				g_request_ret.errcode = code;
				//完成工作－－>显示信息 出卡值
				node1 = node->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.errmsg = textnode->Value();//错误消息
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.amount = textnode->Value();//充值金额
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.outcardamount = textnode->Value();//出卡值
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.serialno = textnode->Value();//处理流水号
				node1 = node1->NextSibling()->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.cardno = textnode->Value();//卡号
				return 0;

			}else{
				//手机充值失败
				g_request_ret.errcode = code;
				node1 = node->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.errmsg = textnode->Value();//错误消息
				return 1;
			}
		}else{
			return -3;
		}
	}else{				
		return -2;
	}

}

SHORT CRF35OCXCtrl::ElectTransWriteCard(LPCTSTR url, LPCTSTR cardno, LPCTSTR outcardamount, LPCTSTR params)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here
	CString strResult;
	CString t_params(params);
	CString bala ="";
	CString txCnt = "";
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;
	CString t_temp="";
	t_params.AppendFormat("&cardId=%s",cardno);
	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */


	if (WriteCard(outcardamount,cardno,g_request_ret.paramKey)==0)
	{
		curl = curl_easy_init();

		if (curl)
		{
			curl_easy_setopt(curl,CURLOPT_URL,url);
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 180); 
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
			if(todoElement==NULL){
				return -1;
			}
			node = todoElement->FirstChild();//head节点
			if (node==NULL)
			{
				return -1;
			}
			node = node->FirstChild();//errcode节点
			if (node==NULL)
			{
				return -1;
			}
			textnode = node->FirstChild();//根节点
			if (textnode==NULL)
			{
				return -1;
			}
			CString code = textnode->Value();
			if (code=="0000")
			{
				g_request_ret.errcode = code;
				//完成工作－－>显示信息 出卡值
				node1 = node->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.errmsg = textnode->Value();//错误消息
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.amount = textnode->Value();//充值金额
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.outcardamount = textnode->Value();//出卡值
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.serialno = textnode->Value();//处理流水号
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.cardno = textnode->Value();//卡号
				return 0;

			}else{
				//电控转账失败
				g_request_ret.errcode = code;
				node1 = node->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.errmsg = textnode->Value();//错误消息
				return 1;
			}
		}else{
			return -3;
		}
	}else{				
		return -2;
	}
}

SHORT CRF35OCXCtrl::CheckTurnOver(LPCTSTR url,LPCTSTR cardid, LPCTSTR cardamount)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Add your dispatch handler code here

	int ret;
	ret = DoScan();
	if (ret)
	{
		return ret;
	}

	CString strResult;
	CString t_params("");
	CString bala ="";
	CString txCnt = "";
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;

	char cardno[16];
	ltoa(m_nCardNo, cardno, 10);
	CString t_temp="";
	t_temp.Format("%s",cardno);
	t_params.AppendFormat("cardId=%s",t_temp);
	t_params.AppendFormat("&cardBala=%d",g_packet_info.bala);
	t_params.AppendFormat("&txCnt=%d",g_packet_info.total_cnt);

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

		curl = curl_easy_init();

		if (curl)
		{
			curl_easy_setopt(curl,CURLOPT_URL,url);
			curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

			curl_easy_setopt(curl, CURLOPT_TIMEOUT, 180); 
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
			if(todoElement==NULL){
				return -1;
			}
			node = todoElement->FirstChild();//head节点
			if (node==NULL)
			{
				return -1;
			}
			node = node->FirstChild();//errcode节点
			if (node==NULL)
			{
				return -1;
			}
			textnode = node->FirstChild();//根节点
			if (textnode==NULL)
			{
				return -1;
			}
			CString code = textnode->Value();
			if (code=="0000")
			{
				g_request_ret.errcode = code;
				//完成工作－－>显示信息 出卡值
				node1 = node->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.errmsg = textnode->Value();//错误消息
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.amount = textnode->Value();//扣款金额
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.outcardamount = textnode->Value();//出卡值
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.serialno = textnode->Value();//处理流水号
				node1 = node1->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.cardno = textnode->Value();//卡号
				return 0;

			}else{
				//模拟缴费流水失败
				g_request_ret.errcode = code;
				node1 = node->NextSibling();
				textnode = node1->FirstChild();
				g_request_ret.errmsg = textnode->Value();//错误消息
				return 1;
			}
		}else{
			return -3;
		}
	
}

SHORT CRF35OCXCtrl::turnOverWritecard(LPCTSTR outcardamount, LPCTSTR cardno, LPCTSTR mainkey)
{
	// TODO: Add your dispatch handler code here
	//开始写卡
	return WriteCard(g_request_ret.outcardamount,g_request_ret.cardno,g_request_ret.paramKey);


}

SHORT CRF35OCXCtrl::turnoverChecked(LPCTSTR url, LPCTSTR cardid, LPCTSTR serialno)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	CString t_params("");
	CString bala ="";
	CString txCnt = "";
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;
	int retries = 3;
	CString t_temp="";
	t_params.AppendFormat("cardId=%s",g_request_ret.cardno);
	t_params.AppendFormat("&serialno=%s",g_request_ret.serialno);

	chunk.memory=NULL; /* we expect realloc(NULL, size) to work */
	chunk.size = 0;    /* no data at this point */

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,url);
		curl_easy_setopt(curl,CURLOPT_POSTFIELDS,t_params);

		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);

		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 180); 
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
	//
	if(strResult!=""){
		TiXmlDocument doc;
		doc.Parse(strResult);
		TiXmlNode* node = 0;
		TiXmlNode* textnode = 0;
		TiXmlNode* node1 = 0;
		TiXmlElement* todoElement = 0;
		TiXmlElement* itemElement = 0;			
		todoElement = doc.RootElement();
		if(todoElement==NULL){
			return -1;
		}
		node = todoElement->FirstChild();//head节点
		if (node==NULL)
		{
			return -1;
		}
		node = node->FirstChild();//errcode节点
		if (node==NULL)
		{
			return -1;
		}
		textnode = node->FirstChild();//根节点
		if (textnode==NULL)
		{
			return -1;
		}
		CString code = textnode->Value();
		if (code=="0000")
		{
	//		ResetInfo();
			return 0;

		}else{
			//模拟缴费流水失败
			g_request_ret.errcode = code;
			node1 = node->NextSibling();
			textnode = node1->FirstChild();
			g_request_ret.errmsg = textnode->Value();//错误消息
			return 1;
		}
	}else{
		return -3;
	}

}
