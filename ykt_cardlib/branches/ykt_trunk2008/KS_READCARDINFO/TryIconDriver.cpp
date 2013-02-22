// TryIconDriver.cpp : implementation file
//

#include "stdafx.h"
#include "ReadCardInfo.h"
#include "TryIconDriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTryIconDriver

CTryIconDriver::CTryIconDriver()
{
	ZeroMemory((LPVOID)&m_tnd, sizeof(m_tnd));
	m_bEnabled = FALSE;
	m_bHidden = FALSE;
}

CTryIconDriver::~CTryIconDriver()
{
	RemoveIcon();
}

BOOL CTryIconDriver::Create(CWnd *pWnd, UINT uCallbackMessage, LPCTSTR szTip, HICON icon, UINT nID)
{
    VERIFY(m_bEnabled = (GetVersion() & 0xff) >= 4);
    if(!m_bEnabled) return FALSE;

    VERIFY(m_bEnabled = (pWnd && ::IsWindow(pWnd->GetSafeHwnd())));
    if(!m_bEnabled) return FALSE;

    ASSERT(uCallbackMessage >= WM_USER);

    ASSERT(_tcslen(szTip) <= 64);

    m_tnd.cbSize = sizeof(NOTIFYICONDATA);
    m_tnd.hWnd = pWnd->GetSafeHwnd();
    m_tnd.uID = nID;
    m_tnd.hIcon = icon;
    m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
    m_tnd.uCallbackMessage = uCallbackMessage;
    strcpy(m_tnd.szTip, szTip);

    VERIFY(m_bEnabled = Shell_NotifyIcon(NIM_ADD,&m_tnd));
    return m_bEnabled;
}

BOOL CTryIconDriver::Enabled()
{
    return m_bEnabled;

}

BOOL CTryIconDriver::Visible()
{
    return !m_bHidden;
}

BOOL CTryIconDriver::SetTooltipText(LPCTSTR pszTooltipText)
{
    if(!m_bEnabled) 
	{
		return FALSE;
	}
    m_tnd.uFlags = NIF_TIP;
    _tcscpy(m_tnd.szTip, pszTooltipText);
    return Shell_NotifyIcon(NIM_MODIFY, &m_tnd);
}

BOOL CTryIconDriver::SetTooltipText(UINT nID)
{
    CString strText;
    VERIFY(strText.LoadString(nID));
    return SetTooltipText(strText);
}

CString CTryIconDriver::GetTooltipText() const
{
    CString strText;
    if(m_bEnabled)
        strText=m_tnd.szTip;
    return strText;
}

BOOL CTryIconDriver::SetIcon(HICON hIcon)
{
    if( !m_bEnabled) return FALSE;
    m_tnd.uFlags = NIF_ICON;
    m_tnd.hIcon = hIcon;
    return Shell_NotifyIcon(NIM_MODIFY,&m_tnd);
}

BOOL CTryIconDriver::SetIcon(LPCTSTR lpIconName)
{
    HICON hIcon = AfxGetApp()->LoadIcon(lpIconName);
    return SetIcon(hIcon);
}

BOOL CTryIconDriver::SetIcon(UINT nIDResource)
{
	HICON hIcon = AfxGetApp()->LoadIcon(nIDResource);
	return SetIcon(hIcon);
}

void CTryIconDriver::ShowIcon()
{
    if(m_bEnabled && m_bHidden)
    {
        m_tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
        Shell_NotifyIcon(NIM_ADD,&m_tnd);
        m_bHidden = FALSE;
    }
}

void CTryIconDriver::RemoveIcon()
{
    if(!m_bEnabled) return;
    m_tnd.uFlags = 0;
    Shell_NotifyIcon(NIM_DELETE,&m_tnd);
    m_bEnabled = FALSE;

}

void CTryIconDriver::MoveToRight()
{
    HideIcon();
    ShowIcon();
}

HICON CTryIconDriver::GetIcon() const
{
    HICON hIcon = NULL;
    if(m_bEnabled)
        hIcon = m_tnd.hIcon;
    return hIcon;

}

void CTryIconDriver::HideIcon()
{
    if( m_bEnabled && !m_bHidden)
    {
        m_tnd.uFlags = NIF_ICON;
        Shell_NotifyIcon(NIM_DELETE,&m_tnd);
        m_bHidden = TRUE;
    }

}

BOOL CTryIconDriver::SetNotificationWnd(CWnd *pNotifyWnd)
{
    if(!m_bEnabled) return FALSE;
    ASSERT(pNotifyWnd && ::IsWindow(pNotifyWnd->GetSafeHwnd()));
    m_tnd.hWnd =  pNotifyWnd->GetSafeHwnd();
    m_tnd.uFlags = 0;
    return Shell_NotifyIcon(NIM_MODIFY,&m_tnd);

}


// 这个位置要搞清楚(菜单到状态栏)
LRESULT CTryIconDriver::OnTrayNotify(WPARAM wParam, LPARAM lParam)
{
    if(wParam != m_tnd.uID)
        return 0L;
    CMenu menu, *pSubMenu;
    if(LOWORD(lParam) == WM_RBUTTONUP)
    {
        if(!menu.LoadMenu(m_tnd.uID))   return 0;
        if(!(pSubMenu = menu.GetSubMenu(0))) return 0;
        ::SetMenuDefaultItem(pSubMenu->m_hMenu,0,TRUE);
        pSubMenu->ModifyMenu(0,MF_BYPOSITION|MF_STRING,
            (UINT)pSubMenu->GetMenuItemID(0),(IsWindowVisible(m_tnd.hWnd)?"隐藏窗口":"显示窗口"));
        CPoint pos;
        GetCursorPos(&pos);
        ::SetForegroundWindow(m_tnd.hWnd);
	    ::TrackPopupMenu(pSubMenu->m_hMenu,0,pos.x,pos.y,0,m_tnd.hWnd,NULL);
        menu.DestroyMenu();
    }
    else if(LOWORD(lParam) == WM_LBUTTONDBLCLK)
    {
        if(GetNotificationWnd()->IsWindowVisible()) return 1;
        if(!menu.LoadMenu(m_tnd.uID))   return 0;
        if(!(pSubMenu = menu.GetSubMenu(0)))    return 0;
        GetNotificationWnd()->SetForegroundWindow();
        GetNotificationWnd()->SendMessage(WM_COMMAND,pSubMenu->GetMenuItemID(0),0);
        menu.DestroyMenu();
    }
    return 1;
}

CWnd* CTryIconDriver::GetNotificationWnd()
{
    return CWnd::FromHandle(m_tnd.hWnd); 

}
/////////////////////////////////////////////////////////////////////////////
// CTryIconDriver message handlers
