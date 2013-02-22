#if !defined(AFX_TRYICONDRIVER_H__2DA137BA_93C5_49DC_9B82_3E7C5B9DCFC3__INCLUDED_)
#define AFX_TRYICONDRIVER_H__2DA137BA_93C5_49DC_9B82_3E7C5B9DCFC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TryIconDriver.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTryIconDriver window

class CTryIconDriver  
{
protected:
    BOOL    m_bEnabled;       //操作系统是否支持Tray Icon
    BOOL    m_bHidden;        //图标是否已经已经隐藏
    NOTIFYICONDATA  m_tnd;    //对应任务条状态区图标的NOTIFYICONDATA结构

public:
	CWnd* GetNotificationWnd();
	virtual LRESULT OnTrayNotify(WPARAM uID,LPARAM lEvent);
	BOOL SetNotificationWnd(CWnd *pNotifyWnd);
	void HideIcon();
	HICON GetIcon() const;
	void MoveToRight();
	void RemoveIcon();
	void ShowIcon();
	
	BOOL SetIcon(UINT nIDResource);
	BOOL SetIcon(LPCTSTR lpIconName);
	BOOL SetIcon(HICON hIcon);
	CString GetTooltipText() const;
	BOOL SetTooltipText(UINT nID);
	BOOL SetTooltipText(LPCTSTR pszTooltipText);
	BOOL Visible();
	BOOL Enabled();
	BOOL Create(CWnd *pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT nID);
	CTryIconDriver(CWnd *pWnd, UINT nCallbackMessage, LPCTSTR szTip, HICON icon, UINT nID);
	
    CTryIconDriver();
	virtual ~CTryIconDriver();

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYICONDRIVER_H__2DA137BA_93C5_49DC_9B82_3E7C5B9DCFC3__INCLUDED_)
