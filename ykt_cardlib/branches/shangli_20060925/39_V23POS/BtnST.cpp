// BtnST.cpp : implementation file
#include "stdafx.h"
#include "BtnST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CButtonST

CButtonST::CButtonST()
{
	m_MouseOnButton = FALSE;

	m_hIconIn = NULL;
	m_hIconOut = NULL;
	m_cxIcon = 0;
	m_cyIcon = 0;
	m_hCursor = NULL;
  
	// 缺省风格为平面按钮
	m_bIsFlat = TRUE; 
  
	m_bDrawBorder = TRUE; 
  
	//图标水平排列
	m_nAlign = ST_ALIGN_HORIZ; 
  
	// 显示文本按钮
	m_bShowText = TRUE; 
  
	// 平面按钮不绘制焦点矩形
	m_bDrawFlatFocus = FALSE;

	// 按钮不为标准（缺省）按钮
	m_bIsDefault = FALSE;

	SetDefaultInactiveBgColor();
	SetDefaultInactiveFgColor();
	SetDefaultActiveBgColor();
	SetDefaultActiveFgColor();

	// 不创建工具提示
	m_ToolTip.m_hWnd = NULL;

	// 不为透明按钮
	m_bDrawTransparent = FALSE;
	m_pbmpOldBk = NULL;
} // End of CButtonST


CButtonST::~CButtonST()
{
	// 恢复原来的位图
	if (m_dcBk.m_hDC != NULL && m_pbmpOldBk != NULL)
	{
		m_dcBk.SelectObject(m_pbmpOldBk);
	}

} // End of ~CButtonST


BEGIN_MESSAGE_MAP(CButtonST, CButton)
    //{{AFX_MSG_MAP(CButtonST)
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CButtonST::SetIcon(int nIconInId, int nIconOutId)
{
	HINSTANCE hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconInId),
													RT_GROUP_ICON);
	// 设置光标位于按钮上时的图标
	m_hIconIn = (HICON)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nIconInId), IMAGE_ICON, 0, 0, 0);
  
	// 设置光标位于按钮外时的图标
	m_hIconOut = (nIconOutId == NULL) ? m_hIconIn : (HICON)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nIconOutId), IMAGE_ICON, 0, 0, 0);
  
	ICONINFO ii;

	// 获取图标大小
	ZeroMemory(&ii, sizeof(ICONINFO));
	::GetIconInfo(m_hIconIn, &ii);

	m_cxIcon = (BYTE)(ii.xHotspot * 2);
	m_cyIcon = (BYTE)(ii.yHotspot * 2);

	RedrawWindow();
} // End of SetIcon


BOOL CButtonST::SetBtnCursor(int nCursorId)
{
	HINSTANCE hInstResource;
	// Destroy any previous cursor
	if (m_hCursor != NULL) ::DestroyCursor(m_hCursor);
	m_hCursor = NULL;

	// If we want a cursor
	if (nCursorId != -1)
	{
		hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nCursorId),
											RT_GROUP_CURSOR);
		// Load icon resource
		m_hCursor = (HCURSOR)::LoadImage(hInstResource/*AfxGetApp()->m_hInstance*/, MAKEINTRESOURCE(nCursorId), IMAGE_CURSOR, 0, 0, 0);
		// If something wrong then return FALSE
		if (m_hCursor == NULL) return FALSE;
	}

	return TRUE;
} // End of SetBtnCursor


void CButtonST::SetFlat(BOOL bState)
{
  m_bIsFlat = bState;
  Invalidate();
} // End of SetFlat


BOOL CButtonST::GetFlat()
{
  return m_bIsFlat;
} // End of GetFlat


void CButtonST::SetAlign(int nAlign)
{
  switch (nAlign)
  {    
    case ST_ALIGN_HORIZ:
         m_nAlign = ST_ALIGN_HORIZ;
         break;
    case ST_ALIGN_VERT:
         m_nAlign = ST_ALIGN_VERT;
         break;
  }
  Invalidate();
} // End of SetAlign


int CButtonST::GetAlign()
{
  return m_nAlign;
} // End of GetAlign


void CButtonST::DrawBorder(BOOL bEnable)
{
  m_bDrawBorder = bEnable;
} // End of DrawBorder


const char* CButtonST::GetVersionC()
{
  return "2.5";
} // End of GetVersionC


const short CButtonST::GetVersionI()
{
  return 25; // Divide by 10 to get actual version
} // End of GetVersionI


void CButtonST::SetShowText(BOOL bShow)
{
  m_bShowText = bShow;
  Invalidate();
} // End of SetShowText


BOOL CButtonST::GetShowText()
{
  return m_bShowText;
} // End of GetShowText


void CButtonST::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd* pWnd;  // Finestra attiva
	CWnd* pParent; // Finestra che contiene il bottone

	CButton::OnMouseMove(nFlags, point);

	// If the mouse enter the button with the left button pressed
	// then do nothing
	if (nFlags & MK_LBUTTON && m_MouseOnButton == FALSE) return;

	// If our button is not flat then do nothing
	if (m_bIsFlat == FALSE) return;

	pWnd = GetActiveWindow();
	pParent = GetOwner();

	if ((GetCapture() != this) && 
		(
#ifndef ST_LIKEIE
		pWnd != NULL && 
#endif
		pParent != NULL)) 
	{
		m_MouseOnButton = TRUE;
		//SetFocus();	
		SetCapture();
		Invalidate();
	}
	else
	{
		/*
		CRect rc;
		GetClientRect(&rc);
		if (!rc.PtInRect(point))
		{
		*/

		POINT p2 = point;
		ClientToScreen(&p2);
		CWnd* wndUnderMouse = WindowFromPoint(p2);
		if (wndUnderMouse != this)
		{
			// Redraw only if mouse goes out
			if (m_MouseOnButton == TRUE)
			{
				m_MouseOnButton = FALSE;
				Invalidate();
			}
			// If user is NOT pressing left button then release capture!
			if (!(nFlags & MK_LBUTTON)) ReleaseCapture();
		}
	}
} // End of OnMouseMove


void CButtonST::OnKillFocus(CWnd * pNewWnd)
{
  CButton::OnKillFocus(pNewWnd);

  // 若按钮不为平面按钮，则返回
  if (m_bIsFlat == FALSE) return;

  if (m_MouseOnButton == TRUE)
  {
    m_MouseOnButton = FALSE;
    Invalidate();
  }
} // End of OnKillFocus


void CButtonST::OnCaptureChanged(CWnd *pWnd) 
{
	if (m_MouseOnButton == TRUE)
	{
		ReleaseCapture();
		Invalidate();
	}

	// 调用基类消息处理函数
	CButton::OnCaptureChanged(pWnd);
} // End of OnCaptureChanged


void CButtonST::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
#ifdef ST_USE_MEMDC
  CDC  *pdrawDC = CDC::FromHandle(lpDIS->hDC);
  CMemDC memDC(pdrawDC);
  CDC  *pDC = &memDC;
#else	
  CDC* pDC = CDC::FromHandle(lpDIS->hDC);
#endif

  CPen *pOldPen;
  BOOL bIsPressed  = (lpDIS->itemState & ODS_SELECTED);
  BOOL bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
  BOOL bIsDisabled = (lpDIS->itemState & ODS_DISABLED);

  CRect itemRect = lpDIS->rcItem;

  if (m_bIsFlat == FALSE)
  {
    if (bIsFocused || (GetDefault() == TRUE))
    {
      CBrush br(RGB(0,0,0));  
      pDC->FrameRect(&itemRect, &br);
      itemRect.DeflateRect(1, 1);
    }
  }

  // 用背景颜色绘制按钮
  COLORREF bgColor;
  if ((m_MouseOnButton == TRUE) || (bIsPressed))
    bgColor = GetActiveBgColor();
  else
    bgColor = GetInactiveBgColor();

	CBrush br(bgColor);
	// 是否透明？
	if (m_bDrawTransparent == TRUE)
	{
		PaintBk(pDC);
	}
	else
	{
		pDC->FillRect(&itemRect, &br);
	}

  //绘制处于“按下”状态的按钮
  if (bIsPressed)
  {
    if (m_bIsFlat == TRUE)
    {
      if (m_bDrawBorder == TRUE)
      {
	    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // Bianco
        CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Grigio scuro

        // 暗灰线
        pOldPen = pDC->SelectObject(&penBtnShadow);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.left, itemRect.top);
        pDC->LineTo(itemRect.right, itemRect.top);
        // 白线
        pDC->SelectObject(penBtnHiLight);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.top-1);
        //
        pDC->SelectObject(pOldPen);
      }
    }
    else    
    {
      CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
      pDC->FrameRect(&itemRect, &brBtnShadow);
    }
  }
  else // 不绘制处于“按下”状态的按钮
  {
    CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
    CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
    CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
    CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

    if (m_bIsFlat == TRUE)
    {
      if (m_MouseOnButton == TRUE && m_bDrawBorder == TRUE)
      {
        // 白线
        pOldPen = pDC->SelectObject(&penBtnHiLight);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.left, itemRect.top);
        pDC->LineTo(itemRect.right, itemRect.top);
        // 暗灰线
        pDC->SelectObject(penBtnShadow);
        pDC->MoveTo(itemRect.left, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
        pDC->LineTo(itemRect.right-1, itemRect.top-1);
        //
        pDC->SelectObject(pOldPen);
      }
    }
    else
    {
      // 白线
      pOldPen = pDC->SelectObject(&penBtnHiLight);
      pDC->MoveTo(itemRect.left, itemRect.bottom-1);
      pDC->LineTo(itemRect.left, itemRect.top);
      pDC->LineTo(itemRect.right, itemRect.top);
      // 亮灰线
      pDC->SelectObject(pen3DLight);
      pDC->MoveTo(itemRect.left+1, itemRect.bottom-1);
      pDC->LineTo(itemRect.left+1, itemRect.top+1);
      pDC->LineTo(itemRect.right, itemRect.top+1);
      // 黑线
      pDC->SelectObject(pen3DDKShadow);
      pDC->MoveTo(itemRect.left, itemRect.bottom-1);
      pDC->LineTo(itemRect.right-1, itemRect.bottom-1);
      pDC->LineTo(itemRect.right-1, itemRect.top-1);
      // 暗灰线
      pDC->SelectObject(penBtnShadow);
      pDC->MoveTo(itemRect.left+1, itemRect.bottom-2);
      pDC->LineTo(itemRect.right-2, itemRect.bottom-2);
      pDC->LineTo(itemRect.right-2, itemRect.top);
      //
      pDC->SelectObject(pOldPen);
    }
  }

  // 按钮标题
  CString sTitle;
  GetWindowText(sTitle);

  // 若不显示按钮标题
  if (m_bShowText == FALSE) sTitle.Empty();

  CRect captionRect = lpDIS->rcItem;

  // 绘制图标
  if (m_hIconIn != NULL)
  {
    DrawTheIcon(pDC, &sTitle, &lpDIS->rcItem, &captionRect, bIsPressed, bIsDisabled);
  }

  // 写按钮标题
  if (sTitle.IsEmpty() == FALSE)
  {
    if (bIsPressed)
      captionRect.OffsetRect(1, 1);
    
    // ONLY FOR DEBUG 
    //CBrush brBtnShadow(RGB(255, 0, 0));
    //pDC->FrameRect(&captionRect, &brBtnShadow);

#ifdef ST_USE_MEMDC
	// 获取对话框字体
    CFont *pCurrentFont = GetFont(); 
    CFont *pOldFont = pDC->SelectObject(pCurrentFont);
#endif
    if ((m_MouseOnButton == TRUE) || (bIsPressed)) 
	{
      pDC->SetTextColor(GetActiveFgColor());
      pDC->SetBkColor(GetActiveBgColor());
    } 
	else 
	{
      pDC->SetTextColor(GetInactiveFgColor());
      pDC->SetBkColor(GetInactiveBgColor());
    }
    // 文本居中显示
    CRect centerRect = captionRect;
    pDC->DrawText(sTitle, -1, captionRect, DT_SINGLELINE|DT_CALCRECT);
    captionRect.OffsetRect((centerRect.Width() - captionRect.Width())/2, (centerRect.Height() - captionRect.Height())/2);
	/* 
    captionRect.OffsetRect(0, (centerRect.Height() - captionRect.Height())/2);
    captionRect.OffsetRect((centerRect.Width() - captionRect.Width())-4, (centerRect.Height() - captionRect.Height())/2);
	*/

	pDC->SetBkMode(TRANSPARENT);
    pDC->DrawState(captionRect.TopLeft(), captionRect.Size(), (LPCTSTR)sTitle, (bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
                   TRUE, 0, (CBrush*)NULL);
#ifdef ST_USE_MEMDC
    pDC->SelectObject(pOldFont);
#endif
  }

  if (m_bIsFlat == FALSE || (m_bIsFlat == TRUE && m_bDrawFlatFocus == TRUE))
  {
    // 绘制焦点矩形
    if (bIsFocused)
    {
      CRect focusRect = itemRect;
      focusRect.DeflateRect(3, 3);
      pDC->DrawFocusRect(&focusRect);
    }
  }
} // End of DrawItem


void CButtonST::DrawTheIcon(CDC* pDC, CString* title, RECT* rcItem, CRect* captionRect, BOOL IsPressed, BOOL IsDisabled)
{
  CRect iconRect = rcItem;

  switch (m_nAlign)
  {
    case ST_ALIGN_HORIZ:
         if (title->IsEmpty())
         {
           // 图标水平居中
           iconRect.left += ((iconRect.Width() - m_cxIcon)/2);
         }
         else
         {
           iconRect.left += 3;  
           captionRect->left += m_cxIcon + 3;
         }
         // 图标垂直居中
         iconRect.top += ((iconRect.Height() - m_cyIcon)/2);
         break;
    case ST_ALIGN_VERT:
         // 图标水平居中
         iconRect.left += ((iconRect.Width() - m_cxIcon)/2);
         if (title->IsEmpty())
         {
           // 图标垂直居中
           iconRect.top += ((iconRect.Height() - m_cyIcon)/2);           
         }
         else
         {
           captionRect->top += m_cyIcon;
         }
         break;
  }
    
  // 按钮按下时按下图标
  if (IsPressed) iconRect.OffsetRect(1, 1);

  pDC->DrawState(iconRect.TopLeft(), 
	               iconRect.Size(), 
				         (m_MouseOnButton == TRUE || IsPressed) ? m_hIconIn : m_hIconOut, 
				         (IsDisabled ? DSS_DISABLED : DSS_NORMAL), 
                 (CBrush*)NULL);
} // End of DrawTheIcon


void CButtonST::PreSubclassWindow() 
{
	UINT nBS;

	nBS = GetButtonStyle();

	// 检查是否为缺省（标准）按钮
	if (nBS & BS_DEFPUSHBUTTON) m_bIsDefault = TRUE;

	// 增加 BS_OWNERDRAW 风格
	SetButtonStyle(nBS | BS_OWNERDRAW);

	CButton::PreSubclassWindow();
} // End of PreSubclassWindow


BOOL CButtonST::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_ToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage


LRESULT CButtonST::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == WM_LBUTTONDBLCLK)
	{
		message = WM_LBUTTONDOWN;
	}
	return CButton::DefWindowProc(message, wParam, lParam);
} // End of DefWindowProc


void CButtonST::SetDefaultInactiveBgColor(BOOL bRepaint)
{
	m_crInactiveBg = ::GetSysColor(COLOR_BTNFACE); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultInactiveBgColor


void CButtonST::SetInactiveBgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crInactiveBg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetInactiveBgColor


const COLORREF CButtonST::GetInactiveBgColor()
{
	return m_crInactiveBg;
} // End of GetInactiveBgColor


void CButtonST::SetDefaultInactiveFgColor(BOOL bRepaint)
{
	m_crInactiveFg = ::GetSysColor(COLOR_BTNTEXT); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultInactiveFgColor


void CButtonST::SetInactiveFgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crInactiveFg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetInactiveFgColor


const COLORREF CButtonST::GetInactiveFgColor()
{
	return m_crInactiveFg;
} // End of GetInactiveFgColor


void CButtonST::SetDefaultActiveBgColor(BOOL bRepaint)
{
	m_crActiveBg = ::GetSysColor(COLOR_BTNFACE); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultActiveBgColor


void CButtonST::SetActiveBgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crActiveBg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetActiveBgColor


const COLORREF CButtonST::GetActiveBgColor()
{
	return m_crActiveBg;
} // End of GetActiveBgColor


void CButtonST::SetDefaultActiveFgColor(BOOL bRepaint)
{
	m_crActiveFg = ::GetSysColor(COLOR_BTNTEXT); 
	if (bRepaint == TRUE) Invalidate();
} // End of SetDefaultActiveFgColor


void CButtonST::SetActiveFgColor(COLORREF crNew, BOOL bRepaint)
{
	m_crActiveFg = crNew; 
	if (bRepaint == TRUE) Invalidate();
} // End of SetActiveFgColor


const COLORREF CButtonST::GetActiveFgColor()
{
	return m_crActiveFg;
} // End of GetActiveFgColor


void CButtonST::SetFlatFocus(BOOL bDrawFlatFocus, BOOL bRepaint)
{
	m_bDrawFlatFocus = bDrawFlatFocus;
	
	// 重画按钮
	if (bRepaint == TRUE) Invalidate();
} // End of SetFlatFocus


BOOL CButtonST::GetFlatFocus()
{
	return m_bDrawFlatFocus;
} // End of GetFlatFocus


BOOL CButtonST::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// 使用指定光标
	if (m_hCursor != NULL)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CButton::OnSetCursor(pWnd, nHitTest, message);
} // End of OnSetCursor


void CButtonST::SetTooltipText(CString* spText, BOOL bActivate)
{
	// 不接受空指针
	if (spText == NULL) return;

	// 初始化ToolTip
	InitToolTip();

	// 若没有定义工具提示，则增加
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip.AddTool(this, (LPCTSTR)*spText, rectBtn, 1);
	}

	// 设置工具提示的文本
	m_ToolTip.UpdateTipText((LPCTSTR)*spText, this, 1);
	m_ToolTip.Activate(bActivate);
} // End of SetTooltipText


void CButtonST::SetTooltipText(int nId, BOOL bActivate)
{
	CString sText;

	// 导入字符串资源
	sText.LoadString(nId);
	// 若字符串资源不为空
	if (sText.IsEmpty() == FALSE) SetTooltipText(&sText, bActivate);
} // End of SetTooltipText


void CButtonST::ActivateTooltip(BOOL bActivate)
{
	// 若没有工具提示，则返回
	if (m_ToolTip.GetToolCount() == 0) return;

	// 激活工具提示
	m_ToolTip.Activate(bActivate);
} // End of EnableTooltip


BOOL CButtonST::GetDefault()
{
	return m_bIsDefault;
} // End of GetDefault


void CButtonST::DrawTransparent()
{
	m_bDrawTransparent = TRUE;
} // End of DrawTransparent


void CButtonST::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// 创建工具提示控件
		m_ToolTip.Create(this);

		m_ToolTip.Activate(FALSE);
	}
} // End of InitToolTip


void CButtonST::PaintBk(CDC * pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
} // End of PaintBk


#undef ST_USE_MEMDC
#undef ST_LIKEIE