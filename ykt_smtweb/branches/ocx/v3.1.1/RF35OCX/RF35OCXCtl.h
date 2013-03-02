#if !defined(AFX_RF35OCXCTL_H__55D3FC3D_925D_4AAD_9342_3588DA068114__INCLUDED_)
#define AFX_RF35OCXCTL_H__55D3FC3D_925D_4AAD_9342_3588DA068114__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RF35OCXCtl.h : Declaration of the CRF35OCXCtrl ActiveX Control class.

#include "HttpConnector.h"
#include <map>

typedef std::map<CString,CString> RequestRet_Map;
typedef std::multimap<CString,CString> ParamName_Map;

/////////////////////////////////////////////////////////////////////////////
// CRF35OCXCtrl : See RF35OCXCtl.cpp for implementation.
class CRF35OCXCtrl : public COleControl
{
	DECLARE_DYNCREATE(CRF35OCXCtrl)

// Constructor
public:
	CRF35OCXCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRF35OCXCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CRF35OCXCtrl();

	DECLARE_OLECREATE_EX(CRF35OCXCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CRF35OCXCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CRF35OCXCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CRF35OCXCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CRF35OCXCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CRF35OCXCtrl)
	long m_nCardNo;
	afx_msg void OnCardNoChanged();
	short m_nPortNo;
	afx_msg void OnPortNoChanged();
	afx_msg short DoScan();
	afx_msg short UndoLoss(LPCTSTR CardPhyId,LPCTSTR blkver);
	afx_msg short ChangePassWord(LPCTSTR CardPhyId, LPCTSTR newpwd);
	afx_msg short SendRequest(LPCTSTR URL);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()


// Event maps
	//{{AFX_EVENT(CRF35OCXCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {	
		dispidCheckLockStatus = 66L,		dispidInitWaterCtlPocket = 65L,		dispidCleanReturnMap = 64L,		dispidSetReturnMap = 63L,		dispidCheckTransProve = 62L,		dispidReUnlockWriteCard = 61L,		dispidUnlockWriteCard = 60L,		dispidGetCardLockInfo = 59L,		dispidReadCardLockInfo = 58L,		dispidPsamCardPosition = 57,		dispidDoOpenCom = 56L,		dispidReWriteWaterCtlTrans = 55L,		dispidWriteWaterCtlPacket = 54L,		dispidWaterCtlTransWriteCard = 53L,		dispidGetWaterCtlPacketInfo = 52L,		dispidReadWaterCtlPacket = 51L,		dispidCardPhyID = 50,		dispidCheckOldCard = 49L,		dispidGetChangeCardinfo = 48L,		dispidReCardChangeNewCard = 47L,		dispidCardChangeNewCard = 46L,		dispidCheckNewCard = 45L,		dispidReCardChangeClearOldCard = 44L,		dispidCardChangeClearOldCard = 43L,		dispidGetCardStateInfo = 42L,		dispidReadShowCardno = 41L,		dispidBankTransWriteCard = 40L,		dispidReportWriteCardFailure = 39L,		dispidReWriteWaterTrans = 38L,		dispidWaterTransWriteCard = 37L,		dispidGetSmallPacketInfo = 36L,		dispidReadSmallPacket = 35L,		dispidGetVersion = 34L,	dispidUpdateCard = 33L,		
	dispidSetCardProperty = 32L,		
	dispidBeginUpdateCard = 31L,
	dispidgetDeadlineDate = 30L,		
	dispidUpdateDeadlineDate = 29L,
	dispidCardTransWriteCard = 28L,		
	dispidgetMoneyFromOldCard = 27L,		
	dispidgetOldCardInfo = 26L,		
	dispidReadOldCardInfo = 25L,		
	dispidReverseNetTrans = 24L,		
	dispidReNetTransWriteCard = 23L,		
	dispidRewriteSidy = 22L,		
	dispidReadCardSidyNo = 21L,		
	dispidResetConsumerLimit = 20L,		
	dispidReadCardConsumerLimit = 19L,		
	dispidgetComsumerLimit = 18L,		
	dispidNetTransWriteCard = 17L,		
	dispidUpdateCardInfo = 16L,		
	dispidCommonTransWriteCard = 15L,			
	dispidGetMainKey = 13L,		
	dispidReportCardWriteFailue = 12L,		
	dispidRewriteCardInfo = 11L,		
	dispidGetPacketInfo = 10L,		
	dispidReadCardPocket = 9L,		
	dispidGetRequestRetInfo = 8L,	
	dispidCardNo = 1L,
	dispidPortNo = 2L,
	dispidDoScan = 3L,
	dispidUndoLoss = 4L,
	dispidChangePassWord = 5L,
	dispidSendRequest = 6L,
	dispidMySendRequest = 7L,
	//}}AFX_DISP_ID
	};
protected:
	//! 处理 HTTP 请求
	/*!
	 * \param T socket 连接类类型
	 * \param url 请求的 URL
	 * \return 成功返回 TRUE
	 */
	template<class T>
	int DoHttpRequest(const cutil::cURL& url)
	{
		cutil::CHttpConnector<T> connector(url.GetServer().c_str(),url.GetPort());
		int retries = 3;
		int ret;
		while(--retries >= 0)
		{
			// 发送请求，并重试3次
			try
			{
				ret = connector.PostRequest(url);
				if(!ret)
				{
					// 返回 HTTP 处理结果不正确
					if(connector.GetReturnCode() != 200)
					{
						return -2;
					}
					return TRUE;
				}

			}
			catch(...)
			{
				return -1;
			}
		}
		return -1;
	}
	int DoSendRequest(const CString& url);
	int ParseURL(const CString& url);
	CString m_requestServer;
	int m_serverPort;
	static CString ms_tokenKey;
	int m_icdev;
	char m_workkey[16];
	bool m_comopen;
	unsigned long m_currCardID;
	int OpenCOM();
	void Beep(int mSec);
	int ReadCardSNR(unsigned long * snr);
	int CalCardKeyA(unsigned long snr,unsigned char * key);	
	SHORT MySendRequest(LPCTSTR url, LPCTSTR params);
	BSTR GetRequestRetInfo(LPCTSTR param);
private:
	void ResetInfo(void);
	void FreeXsqQkIntfDLL(void);
	void ResetOldCardInfo(void);
	int LoadXsqQkIntfDLL();
	int do_write_card_and_request(LPCTSTR url, LPCTSTR cardno,LPCTSTR txcnt, LPCTSTR outcardamount,LPCTSTR amount,LPCTSTR sdate3,LPCTSTR stime3,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc,LPCTSTR params);
	int do_request_and_write_card(LPCTSTR url, LPCTSTR cardphyid,LPCTSTR outcardamount,LPCTSTR dptCardCnt, LPCTSTR params);
	int get_return_field(const CString &param_name,CString &param_value);
	void ResetconsumeLimitInfo(void);
	short UndoLock(LPCTSTR CardPhyId,LPCTSTR CARDSTAT);
	CString rtnCstring(int ret);
	ParamName_Map m_param_name_map;
	ParamName_Map m_cardprop_map;
public:
		// 写卡
	short WriteCard(LPCTSTR outcardamount,LPCTSTR cardphyid,LPCTSTR txcnt,LPCTSTR amount,LPCTSTR sdate,LPCTSTR stime,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc);
	short WriteWaterPacket(LPCTSTR outcardamount,LPCTSTR cardphyid,LPCTSTR txcnt);
protected:
	LONG ReadCardPocket(SHORT pocket,LPCTSTR CardPhyId);
	LONG GetPacketInfo(LPCTSTR param);
	short WriteSidy(LPCTSTR outcardamount,LPCTSTR amount,LPCTSTR sdate,LPCTSTR stime,LPCTSTR cardphyid,LPCTSTR sidyno,LPCTSTR ssd_cardcnt,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc);
public:
	void RetsetPacketInfo(void);
	void RetsetLockInfo(void);
	void RetsetSmallPacketInfo(void);
	void RetsetShowCardNoRef(void);
	void RetsetChangeCardInfo(void);
	int CloseCOM(void);
protected:
	SHORT RewriteCardInfo(void);
	SHORT ReportCardWriteFailue(LPCTSTR url, LPCTSTR serialno);
	SHORT GetMainKey(LPCTSTR url);
	SHORT CommonTransWriteCard(LPCTSTR url, LPCTSTR cardphyid,LPCTSTR txcnt, LPCTSTR outcardamount,LPCTSTR amount,LPCTSTR sdate3,LPCTSTR stime3,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc,LPCTSTR params);
	SHORT UpdateCardInfo(LPCTSTR CardPhyId, LPCTSTR feetype, LPCTSTR enddate);
	SHORT BeginUpdateCard(LPCTSTR cardphyid);
	SHORT SetCardProperty(LPCTSTR prop_name, LPCTSTR prop_value);
	SHORT UpdateCard(void);
	LONG getComsumerLimit(LPCTSTR param);
	SHORT ReadCardConsumerLimit(LPCTSTR cardno);
	SHORT ResetConsumerLimit(LPCTSTR CardPhyId, LPCTSTR singleMaxAmt, LPCTSTR dayMaxAmt);
	LONG ReadCardSidyNo(LPCTSTR CardPhyId);
	SHORT RewriteSidy(void);
	SHORT ReNetTransWriteCard(void);
	SHORT ReverseNetTrans(LPCTSTR url);
	SHORT ReadOldCardInfo(LPCTSTR oldcardpwd);
	BSTR getOldCardInfo(LPCTSTR param);
	SHORT getMoneyFromOldCard(LPCTSTR CardNo, LPCTSTR Money, LPCTSTR cardPwd,LPCTSTR newCardName);
	SHORT CardTransWriteCard(LPCTSTR outcardamount, LPCTSTR cardphyid, LPCTSTR txcnt,LPCTSTR amount,LPCTSTR sdate3,LPCTSTR stime3,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc);
	SHORT UpdateDeadlineDate(LPCTSTR url, LPCTSTR cardno, LPCTSTR enddate, LPCTSTR param);
	BSTR getDeadlineDate(LPCTSTR url,LPCTSTR cardno, LPCTSTR params);
	BSTR GetVersion(void);
	SHORT ReadSmallPacket(SHORT nPacketNo,LPCTSTR cardno);
	LONG GetSmallPacketInfo(LPCTSTR param);
	SHORT WaterTransWriteCard(LPCTSTR url, LPCTSTR cardphyid, LPCTSTR param);
	SHORT ReWriteWaterTrans(void);
	SHORT ReportWriteCardFailure(LPCTSTR url, LPCTSTR params);
	SHORT BankTransWriteCard(LPCTSTR url, LPCTSTR cardphyid, LPCTSTR outcardamount, LPCTSTR dptCardCnt, LPCTSTR params);
	SHORT ReadShowCardno(void);
	BSTR GetCardStateInfo(LPCTSTR param);
	SHORT CardChangeClearOldCard(LPCTSTR cardphyid, LPCTSTR newcardphyid,LPCTSTR showcardno, LPCTSTR dpt_card_cnt,LPCTSTR pay_card_cnt, LPCTSTR cardBala,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc);
	SHORT ReCardChangeClearOldCard(void);
	SHORT CheckNewCard(void);
	SHORT CardChangeNewCard(LPCTSTR url);
	SHORT ReCardChangeNewCard(LPCTSTR url);
	BSTR GetChangeCardinfo(LPCTSTR param);
	SHORT CheckOldCard(void);
	void OnCardPhyIDChanged(void);
	CString m_CardPhyID;
	SHORT ReadWaterCtlPacket(SHORT watertype, LPCTSTR cardphyid);
	LONG GetWaterCtlPacketInfo(LPCTSTR param);
	SHORT WaterCtlTransWriteCard(LPCTSTR url, LPCTSTR cardphyid, SHORT watertype, LPCTSTR params);
	SHORT WriteWaterCtlPacket(LPCTSTR outcardamount, LPCTSTR cardphyid, LPCTSTR txcnt, SHORT watertype, LPCTSTR amount, LPCTSTR sdatetime, LPCTSTR price1, LPCTSTR price2, LPCTSTR price3, LPCTSTR validatedate);
	SHORT ReWriteWaterCtlTrans(void);
	SHORT DoOpenCom(void);
	void OnPsamCardPositionChanged(void);
	SHORT m_PsamCardPosition;
	LONG ReadCardLockInfo(LPCTSTR CardPhyId);
	BSTR GetCardLockInfo(LPCTSTR param);
	SHORT UnlockWriteCard(LPCTSTR outcardamount,LPCTSTR cardphyid,LPCTSTR txcnt,LPCTSTR amount,LPCTSTR sdate,LPCTSTR stime,LPCTSTR ipServer,LPCTSTR drtpPort,LPCTSTR svrFunc, LPCTSTR CARDSTAT);
	SHORT ReUnlockWriteCard(void);
	SHORT CheckTransProve(LPCTSTR cardphyid,SHORT transflag, SHORT cardcnt);
	void SetReturnMap(LPCTSTR key, LPCTSTR value);
	void CleanReturnMap(void);
	SHORT InitWaterCtlPocket(LPCTSTR url, SHORT pocket, LPCTSTR cardphyid);
	SHORT CheckLockStatus(LPCTSTR cardphyid);
};
class KSCardReader 
{
private:
	int m_port;
	int is_open_;
public:
	KSCardReader();
	~KSCardReader();
	int Open(int cpupara4sam,int port);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RF35OCXCTL_H__55D3FC3D_925D_4AAD_9342_3588DA068114__INCLUDED)
