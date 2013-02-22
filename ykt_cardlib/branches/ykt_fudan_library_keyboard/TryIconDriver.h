// TryIconDriver.h: interface for the CTryIconDriver class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRYICONDRIVER_H__47F229B4_FAF0_432C_BF16_84F0FDB017C7__INCLUDED_)
#define AFX_TRYICONDRIVER_H__47F229B4_FAF0_432C_BF16_84F0FDB017C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTryIconDriver  
{
protected:
    BOOL    m_bEnabled;       //����ϵͳ�Ƿ�֧��Tray Icon
    BOOL    m_bHidden;        //ͼ���Ƿ��Ѿ��Ѿ�����
    NOTIFYICONDATA  m_tnd;    //��Ӧ������״̬��ͼ���NOTIFYICONDATA�ṹ

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


#endif // !defined(AFX_TRYICONDRIVER_H__47F229B4_FAF0_432C_BF16_84F0FDB017C7__INCLUDED_)
