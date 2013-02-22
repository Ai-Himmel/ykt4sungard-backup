/*
 * IRS Skin Library
 * Designed by Kilo(110i@110i.net)
 * (C)CopyRight, 2003-2004, IRS, All Right Reserved
 * iRacer.Studio - HttP://wWw.110i.nEt
 */
#include "stdafx.h"
//#include "library.h"


HHOOK	globalWndHookEx;

/*
 * Button Procduce Routine
 */
#define STATUS_BUTTON_NORMAL	0x00000000
#define STATUS_BUTTON_HOVER		0x00000001
#define STATUS_BUTTON_DOWN		0x00000002

class CButtonExt
{
public:
	CButtonExt() {}
	~CButtonExt() {}

	static UINT		m_nStatus;
	static WNDPROC	m_cWndProc;

	static LRESULT DefWindowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		CWnd	*pWnd = NULL;
		CPoint	point;
		pWnd = CWnd::FromHandle( hWnd );

		switch( message )
		{
		case WM_PAINT:
			return OnPaint( pWnd );
			break;

		case WM_LBUTTONDOWN:
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			return OnLButtonDown( pWnd, 0, point );
			break;

		case WM_LBUTTONUP:
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			return OnLButtonUp( pWnd, 0, point );
			break;

		case WM_LBUTTONDBLCLK:
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			return OnLButtonDblClk( pWnd, 0, point );
			break;

		case WM_MOUSEMOVE:
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			return OnMouseMove( pWnd, 0, point );
			break;

		default:
			break;
		}

		return CallWindowProc( m_cWndProc, hWnd, message, wParam, lParam );
	}

	static LRESULT OnLButtonDown( CWnd *pWnd, UINT nFlags, CPoint point ) {
		m_nStatus = STATUS_BUTTON_DOWN;
		pWnd->Invalidate();
		pWnd->UpdateWindow();

		return TRUE;
	}

	static LRESULT OnLButtonUp( CWnd *pWnd, UINT nFlags, CPoint point ) {
		if( m_nStatus != STATUS_BUTTON_NORMAL ) {
			m_nStatus = STATUS_BUTTON_NORMAL;
			pWnd->Invalidate();
			pWnd->UpdateWindow();
			SendMessage( pWnd->GetParent()->m_hWnd, WM_COMMAND, pWnd->GetDlgCtrlID(), (LPARAM) (pWnd->m_hWnd) );
		}

		return TRUE;
	}

	static LRESULT OnLButtonDblClk( CWnd *pWnd, UINT nFlags, CPoint point ) {
		return TRUE;
	}

	static LRESULT OnMouseMove( CWnd *pWnd, UINT nFlags, CPoint point ) {
		HRGN hRgn = CreateRectRgn( 0, 0, 0, 0 );
		pWnd->GetWindowRgn( hRgn );

		BOOL bIn = PtInRegion( hRgn, point.x, point.y );
		if( bIn ) {
			if( m_nStatus == STATUS_BUTTON_DOWN ) return TRUE;
			if( m_nStatus != STATUS_BUTTON_HOVER ) {
				m_nStatus = STATUS_BUTTON_HOVER;
				pWnd->Invalidate();
				pWnd->UpdateWindow();
				pWnd->SetCapture();
			}
		} else {
			if ( m_nStatus == STATUS_BUTTON_HOVER ) {
				m_nStatus = STATUS_BUTTON_NORMAL;
				pWnd->Invalidate();
				pWnd->UpdateWindow();
				ReleaseCapture();
			}
		}
		DeleteObject( hRgn );

		return TRUE;
	}

	static LRESULT OnPaint( CWnd *pWnd ) {
		CPaintDC	dc(pWnd);
		CString		cs;
		RECT		rc;
		CFont		Font;
		CFont		*pOldFont;
		CBrush		Brush;
		CBrush		*pOldBrush;
		CPen		Pen;
		CPen		*pOldPen;
		POINT		pt;
		pt.x = 2;
		pt.y = 2;

		dc.SetBkMode( TRANSPARENT );
		Font.CreateFont( 12, 0, 0, 0, FW_HEAVY, 0, 0, 0, ANSI_CHARSET, \
				OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, \
				VARIABLE_PITCH | FF_SWISS, "MS Sans Serif" );
		pOldFont = dc.SelectObject( &Font );

		if( m_nStatus == STATUS_BUTTON_DOWN ) {
			Brush.CreateSolidBrush( RGB( 90, 90, 255 ) );
			Pen.CreatePen( PS_SOLID, 1, RGB( 100, 100, 100 ) );
			dc.SetTextColor( RGB( 255, 151, 255 ) );
		} else if( m_nStatus == STATUS_BUTTON_HOVER ) {
			Brush.CreateSolidBrush( RGB( 120, 190, 255 ) );
			Pen.CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
			dc.SetTextColor( RGB( 255, 128, 128 ) );
		} else if( m_nStatus == STATUS_BUTTON_NORMAL ) {
			Brush.CreateSolidBrush( RGB( 255, 180, 120 ) );
			Pen.CreatePen( PS_SOLID, 1, RGB( 120, 120, 120 ) );
			dc.SetTextColor( RGB( 255, 255, 255 ) );
		}
		pOldBrush = dc.SelectObject( &Brush );
		pOldPen = dc.SelectObject( &Pen );
		pWnd->GetClientRect( &rc );
		dc.RoundRect( &rc, pt );

		HRGN hRgn = CreateRectRgn( rc.left, rc.top, rc.right, rc.bottom );
		pWnd->SetWindowRgn( hRgn, TRUE );
		DeleteObject( hRgn );

		pWnd->GetWindowText( cs );
		dc.DrawText( cs, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE );

		dc.SelectObject( pOldFont );
		dc.SelectObject( pOldBrush );
		dc.SelectObject( pOldPen );

		return TRUE;
	}

	static LRESULT OnEraseBkgnd( CWnd *pWnd, CDC *pDC ) {
		return TRUE;
	}
};

UINT	CButtonExt::m_nStatus = STATUS_BUTTON_NORMAL;
WNDPROC	CButtonExt::m_cWndProc = NULL;

/*
 * Windows Hook Procduce Routine
 * nCode	- hook code
 * wParam	- current-process flag
 * lParam	- message data
 */
LRESULT CALLBACK IRCallWndProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	PCWPSTRUCT	pcs = (PCWPSTRUCT) lParam;
	HWND		hWnd = pcs->hwnd;

	if( hWnd ) {
		char		sClassName[201] = "\0";

		GetClassName( hWnd, sClassName, 200 );
		if( strcmp( sClassName, "Button" ) == 0) 
		{
			CWnd	*pWnd = CWnd::FromHandle( hWnd );
			DWORD	dwStyle = pWnd->GetStyle();
			if(
				dwStyle == 0x50010000 || 
				dwStyle == 0x50010001 || 
				dwStyle == 0x50030001 || 
				dwStyle == 0x50018000 ||
				dwStyle == 0x50014000 ||
				dwStyle == 0x5001C000
				)
			{
				WNDPROC	WndProc;
				WndProc = (WNDPROC) GetWindowLong( hWnd, GWL_WNDPROC );
				if( CButtonExt::m_cWndProc != NULL && \
					WndProc != CButtonExt::m_cWndProc )
				{
					return CallNextHookEx( globalWndHookEx, nCode, wParam, lParam );
				}
				if( WndProc != (WNDPROC) CButtonExt::DefWindowProc ) 
				{
					WndProc = (WNDPROC) SetWindowLong( hWnd, GWL_WNDPROC, (LONG) CButtonExt::DefWindowProc );
					CButtonExt::m_cWndProc = WndProc;
				}
			}
		}
	}

	return CallNextHookEx( globalWndHookEx, nCode, wParam, lParam );
}

BOOL IRStartup( HINSTANCE hModule, DWORD dwThreadID )
{
	globalWndHookEx = SetWindowsHookEx(
		WH_CALLWNDPROC, (HOOKPROC) IRCallWndProc, hModule, dwThreadID );

	return TRUE;
}

BOOL IRComplete( void )
{
	UnhookWindowsHookEx( globalWndHookEx );

	return TRUE;
}
