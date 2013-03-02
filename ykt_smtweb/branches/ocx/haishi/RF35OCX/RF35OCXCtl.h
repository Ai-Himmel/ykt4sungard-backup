#if !defined(AFX_RF35OCXCTL_H__55D3FC3D_925D_4AAD_9342_3588DA068114__INCLUDED_)
#define AFX_RF35OCXCTL_H__55D3FC3D_925D_4AAD_9342_3588DA068114__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// RF35OCXCtl.h : Declaration of the CRF35OCXCtrl ActiveX Control class.

#include "HttpConnector.h"

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
	afx_msg short UndoLoss(LPCTSTR mkey,long cardno,LPCTSTR blkver);
	afx_msg short ChangePassWord(LPCTSTR mkey, LPCTSTR newpwd,long cardno);
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
		dispidturnoverChecked = 18L,		dispidturnOverWritecard = 17L,		dispidCheckTurnOver = 16L,		dispidElectTransWriteCard = 15L,		dispidMobileTransWriteCard = 14L,		dispidGetMainKey = 13L,		dispidReportCardWriteFailue = 12L,		dispidRewriteCardInfo = 11L,		dispidGetPacketInfo = 10L,		dispidReadCardPocket = 9L,		dispidGetRequestRetInfo = 8L,	dispidCardNo = 1L,
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
public:
	// ocx写卡失败 回传给后台
	short ReportWriteCardError(LPCTSTR url, LPCTSTR serialno,LPCTSTR cardno);
	// 写卡
	short WriteCard(LPCTSTR outcardamount, LPCTSTR cardno,LPCTSTR mainkey);
protected:
	LONG ReadCardPocket(SHORT pocket,LPCTSTR cardno,LPCTSTR mainkey);
	LONG GetPacketInfo(LPCTSTR param);
public:
	void RetsetPacketInfo(void);
	int CloseCOM(void);
protected:
	SHORT RewriteCardInfo(void);
	SHORT ReportCardWriteFailue(LPCTSTR url, LPCTSTR serialno);
	SHORT GetMainKey(LPCTSTR url);
	SHORT MobileTransWriteCard(LPCTSTR url, LPCTSTR cardno, LPCTSTR outcardamount, LPCTSTR params);
	SHORT ElectTransWriteCard(LPCTSTR url, LPCTSTR cardno, LPCTSTR outcardamount, LPCTSTR params);
	SHORT CheckTurnOver(LPCTSTR url,LPCTSTR cardid, LPCTSTR cardamount);
	SHORT turnOverWritecard(LPCTSTR outcardamount, LPCTSTR cardno, LPCTSTR mainkey);
	SHORT turnoverChecked(LPCTSTR url, LPCTSTR cardid, LPCTSTR serialno);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RF35OCXCTL_H__55D3FC3D_925D_4AAD_9342_3588DA068114__INCLUDED)
