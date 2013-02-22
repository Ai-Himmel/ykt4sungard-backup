// KSInputDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ksnl.h"
#include "KSInputDialog.h"
#include ".\ksinputdialog.h"
#include "EditEx.h"


// CKSInputDialog dialog

IMPLEMENT_DYNAMIC(CKSInputDialog, CDialog)
CKSInputDialog::CKSInputDialog(CWnd* pParent /*=NULL*/,CKSConfig* config)
	: CDialog(CKSInputDialog::IDD, pParent)
	, m_inputValue(_T(""))
	, m_password(false)
	, m_defaultValue(_T(""))
	, m_timeout(10)
	, m_elapse(0)
	, m_prompt(_T(""))
	, m_fontName(_T("楷体"))
	, m_fontSize(48)
	, m_showEdit(true)
	, m_config(config)
	, m_fontColor(RGB(255,0,0))
{

}

CKSInputDialog::~CKSInputDialog()
{

}

void CKSInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INPUT_EDT, m_edtInput);
}


BEGIN_MESSAGE_MAP(CKSInputDialog, CDialog)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_EN_CHANGE(IDC_INPUT_EDT, OnEnChangeInputEdt)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CKSInputDialog message handlers

BOOL CKSInputDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	//////////////////////////////////////////////////////////////////////////
	// initialize input edit
	if(m_password)
	{
		m_edtInput.SetPasswordChar('*');
	}
	//////////////////////////////////////////////////////////////////////////
	// set edit
	if(m_showEdit)
	{
		m_edtInput.SetWindowText(m_defaultValue);
		m_edtInput.SetFocus();
		m_edtInput.SetTextFont(m_fontSize,m_fontName);
		switch(m_sizeLimitFlag)
		{
		case 0:
			m_edtInput.LimitText(2);
			break;
		case 1:
			m_edtInput.LimitText(6);
			break;
		case 2:
			m_edtInput.LimitText(11);
			break;
		case 3:
			m_edtInput.LimitText(3);
			break;
		default:
			m_edtInput.LimitText(6);
		    break;
		}
	}
	else
	{
		m_edtInput.ShowWindow(SW_HIDE);
	}
	
	// set timeout handle
	m_elapse = m_timeout;
	if(m_timeout != -1)
		SetTimer(1,1000,NULL);

	// set window position
	SetDialogPosition();

	//////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
// 输入
int CKSInputDialog::InputQuery(const CString & prompt, const CString & defaultValue, CString & value)
{
	m_defaultValue = defaultValue;
	m_password = false;
	m_prompt = prompt;
/*	flag = 0;*/
	int ret = DoModal();
	if(ret == IDOK)
	{
		GetInputValue(value);
	}
	return ret;
}

void CKSInputDialog::GetInputValue(CString & value)
{
	value = m_inputValue;
}

void CKSInputDialog::OnOK()
{
	if(m_edtInput.IsWindowVisible())
	{
		m_edtInput.GetWindowText(m_inputValue);
		if(m_inputValue.GetLength() == 0)
		{
			return;
		}
		if ('0' == m_inputValue.GetAt(0))
		{
			return;
		}
	}
	CDialog::OnOK();
}

void CKSInputDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC memDC;
	CBitmap bkBit,*oldBkBit;
	CRect client;
	RECT clientRect,edtRect;
	dc.GetClipBox(client);
	if(memDC.CreateCompatibleDC(&dc))
	{
		memDC.SetBkMode(TRANSPARENT);
		if(bkBit.CreateCompatibleBitmap(&dc,client.Width(),client.Height()))
		{
			oldBkBit = memDC.SelectObject(&bkBit);
			/*
			CBrush brh;
			brh.CreateSolidBrush( RGB(0,0,255) );
			brh.UnrealizeObject();
			memDC.FillRect( client , &brh );
			*/
			if(m_config)
			{
				CRect parentRect;
				CWnd * parentWnd = GetParent();
				ASSERT(parentWnd != NULL);
				parentWnd->GetWindowRect(parentRect);
				GetWindowRect(&clientRect);
				m_config->m_bkImg.m_Dest.x = -(clientRect.left);
				m_config->m_bkImg.m_Dest.y = -(clientRect.top);
				m_config->m_bkImg.m_DestSize.cx = parentRect.Width();
				m_config->m_bkImg.m_DestSize.cy = parentRect.Height();
				m_config->m_bkImg.m_Src.x = 0;
				m_config->m_bkImg.m_Src.y = 0;
				m_config->m_bkImg.m_SrcSize.cx = m_config->m_bkImg.GetWidth();
				m_config->m_bkImg.m_SrcSize.cy = m_config->m_bkImg.GetHeight();
				m_config->m_bkImg.Display(&memDC);
				/*
				dc.StretchBlt(0,0,client.Width(),client.Height(),&memDC
				,0,0,m_config->m_bkImg.GetWidth(),m_config->m_bkImg.GetHeight(),SRCCOPY);
				*/
			}
			//////////////////////////////////////////////////////////////////////////
			// 设置字体
			LOGFONT lf;
			memset(&lf,0,sizeof lf);
			lf.lfCharSet = GB2312_CHARSET;
			strcpy(lf.lfFaceName,m_fontName.GetBuffer(1));
			lf.lfHeight = m_fontSize;
			lf.lfWeight = FW_BOLD;			

			CFont font;
			CFont *pOldFont;						// 新添加的老字体资源
			font.CreateFontIndirect(&lf);
			// memDC.SelectObject(font);			// 隐掉
			pOldFont = memDC.SelectObject(&font);	// 新添加获得老字体资源		
			//////////////////////////////////////////////////////////////////////////
			// 取得字体属性
			TEXTMETRIC tm;
			memset(&tm,0,sizeof tm);
			memDC.GetTextMetrics(&tm);
			CSize fs = memDC.GetTextExtent(m_prompt);
			int textWidth = fs.cx;//tm.tmAveCharWidth * (m_prompt.GetLength() + 1);
			//////////////////////////////////////////////////////////////////////////
			// 设置字体颜色
			memDC.SetTextColor(m_fontColor);
			//////////////////////////////////////////////////////////////////////////
			GetWindowRect(&clientRect);
			ScreenToClient(&clientRect);
			m_edtInput.GetWindowRect(&edtRect);
			ScreenToClient(&edtRect);
			int x,y;
			RECT textRect;
			if(clientRect.right > textWidth)
			{
				x = (clientRect.right - textWidth) / 2;
				textRect.left = x;
				textRect.right = textRect.left + textWidth;
			}
			else
			{
				x = 20;
				textRect.left = x;
				textRect.right = clientRect.right - 20;
			}
			
			//y = (edtRect.top - tm.tmHeight - 2);
			y = 5;
			memDC.MoveTo(x,y);
			textRect.top = y;
			
			textRect.bottom = y + GetTextLineHeight(fs.cy,textRect.right-textRect.left
				,fs.cx);
			memDC.DrawText(m_prompt,&textRect,DT_WORDBREAK|DT_CENTER);
			//////////////////////////////////////////////////////////////////////////
			
			dc.BitBlt(0,0,client.Width(),client.Height(),&memDC,0,0,SRCCOPY);
			memDC.SelectObject(pOldFont);				// 新添加的把老字体资源选回去
			font.DeleteObject();
			//brh.DeleteObject();
			memDC.SelectObject(oldBkBit);
			memDC.DeleteDC();
		}
	}
}

int CKSInputDialog::InputPassword(const CString& prompt, const CString& defaultValue, CString& value)
{
	m_password = true;
	m_defaultValue = defaultValue;
	m_prompt = prompt;
	flag = 1;
	int ret = DoModal();
	if(ret == IDOK)
	{
		GetInputValue(value);
	}
	return ret;
}

void CKSInputDialog::SetTimeOut(int timeout)
{
	m_timeout = timeout;
}

void CKSInputDialog::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	if(--m_elapse > 0)
	{
		return;
	}
	EndDialog(IDABORT);
}

void CKSInputDialog::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKSInputDialog::OnEnChangeInputEdt()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	m_elapse = m_timeout;
}

void CKSInputDialog::SetDialogPosition(void)
{
	CPaintDC dc(this); // device context for painting
	// 设置字体
	LOGFONT lf;
	memset(&lf,0,sizeof lf);
	lf.lfCharSet = GB2312_CHARSET;
	strcpy(lf.lfFaceName,m_fontName.GetBuffer(1));
	lf.lfHeight = m_fontSize;
	lf.lfWeight = FW_BOLD;		

	CFont font;
	CFont *pOldFont;								// 添加老的字体对象
	font.CreateFontIndirect(&lf);
	// dc.SelectObject(font);						// 隐掉
	pOldFont = dc.SelectObject(&font);				// 选入新的字体资源
	//////////////////////////////////////////////////////////////////////////
	// 取得字体属性
	//TEXTMETRIC tm;
	//memset(&tm,0,sizeof tm);
	//dc.GetTextMetrics(&tm);
	CSize fs = dc.GetTextExtent(m_prompt);
	int textWidth = fs.cx;//tm.tmAveCharWidth * m_prompt.GetLength();
	
	//////////////////////////////////////////////////////////////////////////
	// 计算窗体宽度
	RECT edtRect;
	m_edtInput.GetWindowRect(&edtRect);
	int edtWidth = edtRect.right - edtRect.left;
	int cx = (textWidth < edtWidth ) ? edtWidth : textWidth;
	cx += 40;
	CWnd * desktop = CWnd::GetDesktopWindow();
	if(::IsWindow(desktop->GetSafeHwnd()))
	{
		// 
		CRect desktopRect;
		desktop->GetWindowRect(desktopRect);
		RECT clientRect;
		this->GetWindowRect(&clientRect);
		if(desktopRect.Width() <= cx)
		{
			cx = desktopRect.Width() - 80;
		}
		int x = (desktopRect.right - cx) / 2;
		int y = (desktopRect.bottom - clientRect.bottom) / 2;
		int cy = (desktopRect.bottom - clientRect.top);
		this->SetWindowPos(&CWnd::wndTopMost,x,y,cx,cy,SWP_NOREDRAW);
		RECT edtRect;
		m_edtInput.GetWindowRect(&edtRect);
		ScreenToClient(&edtRect);
		x = (cx - textWidth) / 2;
		y = GetTextLineHeight(fs.cy,cx,fs.cx) + 5;
		m_edtInput.MoveWindow(x,y+20,textWidth
			,edtRect.bottom-edtRect.top + 10,TRUE);
	}
	dc.SelectObject(pOldFont);					// 收回老的字体资源
	font.DeleteObject();						// 字体资源本身要回收
}

HBRUSH CKSInputDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	switch(nCtlColor)
	{
	case CTLCOLOR_EDIT:
		pDC->SetTextColor(m_fontColor);
		break;
	}
	return hbr;
}

int CKSInputDialog::WaitConfirm(const CString& prompt)
{
	m_password = true;
	m_prompt = prompt;
	m_showEdit = false;

	int ret = DoModal();
	return ret;
}

int CKSInputDialog::GetTextLineHeight(int heightPerLine,int maxWidth,int totalWidth)
{
	int linecnt;
	if( totalWidth % maxWidth == 0)
	{
		linecnt = totalWidth / maxWidth;
	}
	else
	{
		linecnt = totalWidth / maxWidth + 1;
	}
	return linecnt * heightPerLine;
}

BOOL CKSInputDialog::PreTranslateMessage(MSG* pMsg)
{
	MSG msg;
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
#if 1
		if(pMsg->hwnd == this->GetSafeHwnd() 
			||::IsChild(GetSafeHwnd(),pMsg->hwnd))//&& GetCurrentWorkflow() == NULL)
#endif
		{
			//TRACE1("dialog %d\n",::GetDlgCtrlID(pMsg->hwnd));
			//TRACE("input mwnd[%d]twnd[%d]msg[%d]key[%d]\n",pMsg->hwnd,GetSafeHwnd()
			//	,pMsg->message,pMsg->wParam);
			if(pMsg->message == WM_KEYUP)
			{		
				switch(pMsg->wParam)
				{
				case VK_RETURN:
					if(m_inputValue.GetLength() == 0 || ('0' == m_inputValue.GetAt(0) && 0 == m_sizeLimitFlag))
					{
						break;
					}
					EndDialog(IDOK);
					break;
				case VK_ESCAPE:
					::PeekMessage(&msg,pMsg->hwnd,WM_KEYFIRST,WM_KEYLAST,PM_REMOVE);
					EndDialog(IDCANCEL);
					break;
				default:
					return CDialog::PreTranslateMessage(pMsg);
				}
				return TRUE;
			}
			else if(WM_KEYDOWN == pMsg->message)
			{
				if(VK_ESCAPE == pMsg->wParam)
					return TRUE;
			}
			else if (pMsg->message == WM_CHAR)
			{
				if (VK_DELETE == pMsg->wParam)    // 0x2e, 小键盘del
				{
					pMsg->wParam = NULL;
					return TRUE;
				}
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CKSInputDialog::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
// 	if (nChar == 0xbe)
// 	{
// 		OnKeyDown(NULL, nRepCnt, nFlags);	
// 	}
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CKSInputDialog::SetLimtText(int sizeFlag)
{
	m_sizeLimitFlag = sizeFlag;
}
