// KSNLDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ksnl.h"
#include "KSNLDlg.h"
#include "ksutil.h"
#include "nl8900def.h"
#include "ksnldlg.h"
#include "KSInputDialog.h"
#include "DRTPHelper.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKSNLDlg dialog

#define KS_TIMER_TIPMSG	  1   // 提示信息时钟
#define KS_TIMER_BK		  2	  // 等待时钟
#define TIME_PIECE	100

using namespace std;

static struct KEY_NAME_MAP{
	UINT keycode;
	const char *keyname;
}s_globalKeyMap[] = {
	{VK_F1,"F1"},
	{VK_F2,"F2"},
	{VK_F3,"F3"},
	{VK_F4,"F4"},
	{VK_F5,"F5"},
	{VK_F6,"F6"},
	{VK_F7,"F7"},
	{VK_F8,"F8"},
	{VK_F9,"F9"},
	{VK_F10,"F10"},
	{VK_F11,"F11"},
	{VK_F12,"F12"},
	{-1,NULL},
};

static CString FindKeyName(UINT keycode)
{
	int i = 0;
	while(s_globalKeyMap[i].keycode != -1)
	{
		if(s_globalKeyMap[i].keycode == keycode)
			return CString(s_globalKeyMap[i].keyname);
		i++;
	}
	return "";
}
static UINT FindKeyCode(const char* keyname)
{
	int i = 0;
	while(s_globalKeyMap[i].keycode != -1)
	{
		if(!strcmp(s_globalKeyMap[i].keyname,keyname))
			return s_globalKeyMap[i].keycode;
		i++;
	}
	return -1;
}
CKSNLDlg::CKSNLDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKSNLDlg::IDD, pParent)
	, m_currentWorkflow(NULL)
	, m_bShowDlg(FALSE)
	, m_dlg_msg_overlapped(false)
{
	//{{AFX_DATA_INIT(CKSNLDlg)
	//}}AFX_DATA_INIT
}


void CKSNLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKSNLDlg)
	DDX_Control(pDX, IDC_INFOLIST, m_InfoListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CKSNLDlg, CDialog)
	//{{AFX_MSG_MAP(CKSNLDlg)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKSNLDlg message handlers

BOOL CKSNLDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CKsnlApp * app = (CKsnlApp*)AfxGetApp();
	// 加载配置，加载工作流
	m_config.LoadConfig(app->m_appPath);
	// 保证只有16个字节
	m_config.m_workKey = CString(app->m_param.workkey,16);
	m_config.m_ICCardkey = CString(app->m_param.bankkey,16);
	// 初始化 DRTP
	//CDRTPHelper::InitDrtp();
	
	MaxWindow();
	// ((CKsnlApp*)AfxGetApp())->ShowParentForm(false);

	SetTimer(KS_TIMER_BK,1000,NULL);
	m_idletime = m_config.m_idleTime;
	Reset();
	m_drawer.m_fontName = m_config.m_fontName;
	m_drawer.m_fontSize = m_config.m_fontSize;
	
	m_dlg_msg_overlapped = true;
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE

}

// 最大化窗口
void CKSNLDlg::MaxWindow(void)
{
	WINDOWPLACEMENT wndPlcmt;
	memset(&wndPlcmt,0,sizeof wndPlcmt);
	wndPlcmt.length = sizeof wndPlcmt;
	wndPlcmt.flags = WPF_RESTORETOMAXIMIZED;
	wndPlcmt.showCmd = SW_SHOWMAXIMIZED;
	SetWindowPlacement(&wndPlcmt);
}

void CKSNLDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CDC memDC;
	CBitmap bkBit,*oldBkBit;
	CRect client;
	dc.GetClipBox(client);
	if(memDC.CreateCompatibleDC(&dc))
	{
		if(bkBit.CreateCompatibleBitmap(&dc,client.Width(),client.Height()))
		{
			oldBkBit = memDC.SelectObject(&bkBit);
			//////////////////////////////////////////////////////////////////////////
			// 设置字体
			LOGFONT lf;
			memset(&lf,0,sizeof lf);
			lf.lfCharSet = GB2312_CHARSET;
			strcpy(lf.lfFaceName,m_config.m_fontName);
			lf.lfHeight = m_config.m_fontSize;
			lf.lfWeight = FW_BOLD;			
//			lf.lfWeight = FW_MEDIUM;
			CFont font;
			CFont *pOldFont;							// 新添加老字体资源指针
			font.CreateFontIndirect(&lf);
			// memDC.SelectObject(font);				// 隐掉
			pOldFont = memDC.SelectObject(&font);		// 添加新字体资源
			//////////////////////////////////////////////////////////////////////////
			// 设置字体颜色
			memDC.SetTextColor(m_config.m_fontColor);
			//////////////////////////////////////////////////////////////////////////
			CRect clientRect;
			GetWindowRect(clientRect);
			memDC.SetBkMode(TRANSPARENT);
			m_config.m_bkImg.m_Dest.x = 0;
			m_config.m_bkImg.m_Dest.y = 0;
			m_config.m_bkImg.m_DestSize.cx = clientRect.Width();
			m_config.m_bkImg.m_DestSize.cy = clientRect.Height();
			m_config.m_bkImg.m_Src.x = 0;
			m_config.m_bkImg.m_Src.y = 0;
			m_config.m_bkImg.m_SrcSize.cx = m_config.m_bkImg.GetWidth();
			m_config.m_bkImg.m_SrcSize.cy = m_config.m_bkImg.GetHeight();
			m_config.m_bkImg.Display(&memDC);
			if(!GetCurrentWorkflow())
			{
				DrawFuncBtn(&memDC);          
			}
			//////////////////////////////////////////////////////////////////////////
			// show tip messages
			m_drawer.DisplayMessages(&memDC,clientRect);
			//////////////////////////////////////////////////////////////////////////
			//
			dc.BitBlt(0,0,client.Width(),client.Height(),&memDC
				,0,0,SRCCOPY);
			memDC.SelectObject(pOldFont);				// 获取老字体资源 
			
			font.DeleteObject();
			memDC.SelectObject(oldBkBit);
			memDC.DeleteDC();
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

void CKSNLDlg::OnFormKeyDown(UINT nChar, UINT nFlags)
{
	m_idletime = m_config.m_idleTime;
	CKSWorkflow * work = GetCurrentWorkflow();
	int ret;
	if(work)
	{
		if(!work->IsTerminate())
		{
			if(work->IsStopKey())
			{
				return;
			}
			ret = work->OnFormKeyDown(nChar,nFlags);
			return;
		}
	}
	//Key down
	switch(nChar)
	{
		case VK_RETURN:
			//OnOK();
			return;
		case VK_ESCAPE:
			if(m_drawer.IsMsgShowing())
			{
				Reset();
				Invalidate(FALSE);
				return;
			}
			OnCancel();
			return;
		default:
			break;
	}
	
	m_currentWorkflow = NULL;
	CString keyname = FindKeyName(nChar);
	if(!keyname.IsEmpty())
	{
		vector<CKSWorkflow*>  workflows;
		workflows = m_config.m_workflows.GetAllWorkflows();
		vector<CKSWorkflow*>::iterator iter;
		for (iter = workflows.begin();iter != workflows.end();++iter)
		{
			//
			CKSWorkflow * work = *iter;
			if(keyname == work->m_key)
			{
				m_errcode = 0;
				m_currentWorkflow = work;
				KillTimer(KS_TIMER_TIPMSG);
				// 处理业务
				m_errcode = work->Work();
				//TRACE1("finish work[%d]\n",m_errcode);
				if(RET_WF_TIMEOUT == m_errcode)
				{
					Reset();
					Invalidate(FALSE);			
				}
				else if(RET_WF_EXIT_APP == m_errcode)
				{
					// 退出
					EndDialog(IDOK);
					return;
				}
				else
				{
					SetTimeOut(3);
				}
				if(m_errcode == ERR_NOT_LOGIN)
				{
					EndDialog(IDCANCEL);
				}
				return;
			}
		}
	}
	//CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKSNLDlg::Reset()
{
	KillTimer(KS_TIMER_TIPMSG);
	m_currentWorkflow = NULL;
	m_drawer.Reset();
}
// 显示信息
int CKSNLDlg::ShowTipMessage(const char* msg,int timeout /*= 10*/)
{
	m_drawer.ShowTipMessage(msg);
	return DisplayMessage(timeout);
}


// 绘制功能按键
void CKSNLDlg::DrawFuncBtn(CDC* pDC)
{
	vector<CKSWorkflow*>  workflows;
	workflows = m_config.m_workflows.GetAllWorkflows();
	vector<CKSWorkflow*>::iterator iter;
	for (iter = workflows.begin();iter != workflows.end();++iter)
	{
		DrawFuncBtn(pDC,*iter);
	}
}

// 绘制功能按钮
void CKSNLDlg::DrawFuncBtn(CDC* pDC, CKSWorkflow* workflow)
{
	// load 
	CRect client;
	CFG_DIB * dib;
	GetWindowRect(client);
	int midPos = client.Width() / 2;
	if(workflow->m_posX < midPos)
	{
		dib = &(m_config.m_leftBtnImg);
		dib->m_DestSize.cx = m_config.m_leftBtnPicWidth;
		dib->m_DestSize.cy = m_config.m_leftBtnPicHeight;
		dib->m_SrcSize.cx = dib->GetWidth();
		dib->m_SrcSize.cy = dib->GetHeight();
	}
	else
	{
		dib = &(m_config.m_rightBtnImg);
		dib->m_DestSize.cx = m_config.m_rightBtnPicWidth;
		dib->m_DestSize.cy = m_config.m_rightBtnPicHeight;
		dib->m_SrcSize.cx = dib->GetWidth();;
		dib->m_SrcSize.cy = dib->GetHeight();
	}
	dib->m_Dest.x = workflow->m_posX;
	dib->m_Dest.y = workflow->m_posY;
	
	dib->m_Src.x = 0;
	dib->m_Src.y = 0;
	dib->Display(pDC);
	// 计算位置
	CSize size = pDC->GetTextExtent(workflow->m_funcText);
	int x = workflow->m_posX + (dib->m_SrcSize.cx - size.cx) / 2;
	int y = workflow->m_posY + (dib->m_SrcSize.cy - size.cy) / 2;

	pDC->MoveTo(x,y);
	RECT textRect;
	textRect.left = x;
	textRect.top = y;
	textRect.right = x + size.cx;
	textRect.bottom = y + size.cy;
	pDC->DrawText(workflow->m_funcText,&textRect,DT_SINGLELINE);
	
}

// 获取当前的 工作流
CKSWorkflow* CKSNLDlg::GetCurrentWorkflow(void)
{
	return m_currentWorkflow;
}

BOOL CKSNLDlg::PreTranslateMessage(MSG* pMsg)
{
	if (m_dlg_msg_overlapped)
	{
		m_dlg_msg_overlapped = false;
		return TRUE;
	}
	
	if(pMsg->message >= WM_KEYFIRST && pMsg->message <= WM_KEYLAST)
	{
		if(pMsg->hwnd == this->GetSafeHwnd() 
			||::IsChild(GetSafeHwnd(),pMsg->hwnd))
		{
			//TRACE("mwnd[%d]twnd[%d]msg[%d]key[%d]\n",pMsg->hwnd,GetSafeHwnd()
			//	,pMsg->message,pMsg->wParam);
			if(pMsg->message == WM_KEYUP || pMsg->message == WM_SYSKEYUP)
			{
				OnFormKeyDown(pMsg->wParam,1);
				return TRUE;
			}
			else if(pMsg->message == WM_KEYDOWN)
			{
				if(VK_ESCAPE == pMsg->wParam 
					|| VK_RETURN == pMsg->wParam)
					return TRUE;
			}	
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

int CKSNLDlg::InputQuery(const CString & prompt, const CString & defaultValue,
			   CString & value,int timeout)
{
	m_drawer.Reset();
	Invalidate(FALSE);
	m_bShowDlg = TRUE;
	CKSInputDialog dlg(this,&m_config);
	dlg.m_fontColor = m_config.m_fontColor;
	dlg.m_fontSize = m_config.m_fontSize;
	dlg.m_fontName = m_config.m_fontName;
	dlg.SetTimeOut(timeout);
	//////////////////////////////////////////////////////////////////////////
	dlg.SetLimtText(m_sizeFlag);
	//////////////////////////////////////////////////////////////////////////
	int ret = dlg.InputQuery(prompt,defaultValue,value);
	m_bShowDlg = FALSE;
	Invalidate(FALSE);
	return (ret == IDOK) ? 0 : -1;
}
int CKSNLDlg::InputPassword(const CString & prompt, CString & value,int timeout)
{
	m_drawer.Reset();
	Invalidate(FALSE);
	m_bShowDlg = TRUE;
	CKSInputDialog dlg(this,&m_config);
	dlg.m_fontColor = m_config.m_fontColor;
	dlg.m_fontSize = m_config.m_fontSize;
	dlg.m_fontName = m_config.m_fontName;
	dlg.SetTimeOut(timeout);
	//////////////////////////////////////////////////////////////////////////
	dlg.SetLimtText(m_sizeFlag);
	//////////////////////////////////////////////////////////////////////////
	int ret = dlg.InputPassword(prompt,"",value);
	m_bShowDlg = FALSE;
	Invalidate(FALSE);
	return (ret == IDOK) ? 0 : -1;
}
int CKSNLDlg::Confirm(int timeout)
{
	/*
	CKSInputDialog dlg(this,&m_config);
	dlg.m_fontColor = m_config.m_fontColor;
	dlg.m_fontSize = m_config.m_fontSize;
	dlg.m_fontName = m_config.m_fontName;
	dlg.SetTimeOut(timeout);
	m_bShowDlg = TRUE;
	int ret = dlg.WaitConfirm("");
	m_bShowDlg = FALSE;
	Invalidate(FALSE);
	return (ret == IDOK) ? 0 : -1;
	*/
	return DisplayMessage(timeout);
}
int CKSNLDlg::Confirm(const CString& prompt,int timeout)
{
	return ShowTipMessage(prompt);
}

void CKSNLDlg::OnClose()
{
	
	CDialog::OnClose();
}

void CKSNLDlg::OnTimer(UINT nIDEvent)
{
	if(m_bShowDlg)
		return;
	CDialog::OnTimer(nIDEvent);
	switch(nIDEvent)
	{
	case KS_TIMER_TIPMSG:
		{
			if(m_timeout-->0)
			{
				return;
			}
			KillTimer(KS_TIMER_TIPMSG);
			Reset();
			Invalidate(FALSE);
			break;
		}
	case KS_TIMER_BK:
		if(GetCurrentWorkflow()==NULL)
		{
			if(--m_idletime<0)
			{
				m_errcode = 0;
				EndDialog(IDABORT);
				return;
			}
		}
		break;
	default:
		break;
	}
}

BOOL CKSNLDlg::DestroyWindow()
{
	((CKsnlApp*)AfxGetApp())->ShowParentForm(true);
	// 等待1s
	Sleep(1000);
	KillTimer(KS_TIMER_BK);
	return CDialog::DestroyWindow();
}

int CKSNLDlg::DisplayMessage(int timeout)
{
	// Reset();
	long timeslice = timeout * 1000;
	int ret = 0;
	// m_timeout = 0;
	MSG msg;
	KillTimer(KS_TIMER_TIPMSG);
	/*
	if(timeout != -1)
	{
		m_timeout = timeout;
		SetTimer(KS_TIMER_TIPMSG,1000,NULL);
	}
	*/
	m_drawer.DisplayMessage();
	Invalidate(FALSE);
	UpdateWindow();
	while(timeslice>0)
	{
		if (::PeekMessage(&msg,GetSafeHwnd(),0,0,PM_REMOVE))
		{
			// 如果设置的不响应按键，不处理
			if(m_currentWorkflow!=NULL && m_currentWorkflow->IsStopKey())
				goto L_CNT;
			if(msg.message == WM_KEYUP)
			{
				switch(msg.wParam)
				{
				case VK_ESCAPE:
					ret = IDCANCEL;
					//AfxMessageBox("cancel");
					goto L_RETU;
				case VK_RETURN:
					//AfxMessageBox("return");
					// TRACE0("press return key\n");
					ret = IDOK;
					goto L_RETU;
				default:
					break;
				}
			}
		}
L_CNT:
		Sleep(TIME_PIECE);
		timeslice -= TIME_PIECE;
	}
L_RETU:
	// m_drawer.Reset();
	return ret;
}

void CKSNLDlg::SetTimeOut(int timeout)
{
	m_timeout = timeout;
	KillTimer(KS_TIMER_TIPMSG);
	SetTimer(KS_TIMER_TIPMSG,1000,NULL);

}

int CKSNLDlg::ShowListInfo(int timeout)
{
	CRect clientRect;
	GetWindowRect(clientRect);
	int height = clientRect.Height();
	clientRect.top = height / 4;
	clientRect.bottom = clientRect.top + height / 2;
	// ScreenToClient(clientRect);
	m_InfoListCtrl.MoveWindow(clientRect,TRUE);
	m_InfoListCtrl.ShowWindow(SW_SHOWNORMAL);
	Invalidate(FALSE);
	ClearMessageLine();
	AddMessageLine("                    按[退出]返回",6,+4);
	int ret = DisplayMessage(timeout);
	m_InfoListCtrl.ShowWindow(SW_HIDE);
	Reset();
	Invalidate(FALSE);
	return ret;
}

void CKSNLDlg::ClearAllColumns()
{
	m_InfoListCtrl.DeleteAllItems();
	if(m_InfoListCtrl.GetHeaderCtrl() == NULL) return;
	int i = m_InfoListCtrl.GetHeaderCtrl()->GetItemCount() - 1;
	while(i >= 0)
	{
		m_InfoListCtrl.DeleteColumn(i);
		i--;
	}
}

void CKSNLDlg::AddListColumns(const CString & colName,int width /*= -1*/)
{
	int colInd = 0;
	if(m_InfoListCtrl.GetHeaderCtrl() != NULL)
		colInd = m_InfoListCtrl.GetHeaderCtrl()->GetItemCount();
	if(-1 == width)
		width = 100;
	m_InfoListCtrl.InsertColumn(colInd,colName,LVCFMT_LEFT,width);
}

int CKSNLDlg::AddToListInfo(LPCTSTR pText,...)
{
	int lineno = m_InfoListCtrl.GetItemCount();
	if(m_InfoListCtrl.GetHeaderCtrl() == NULL) return -1;
	m_InfoListCtrl.InsertItem(lineno,pText);
	LPCTSTR pArg;
	int iCols = 1;
	va_list rowCols;
	va_start(rowCols,pText);
	while(iCols < m_InfoListCtrl.GetHeaderCtrl()->GetItemCount())
	{
		pArg = va_arg(rowCols,LPCTSTR);
		if(pArg != NULL)
		{
			m_InfoListCtrl.SetItem(lineno,iCols,LVIF_TEXT,pArg,0,0,0,0);
		}
		else
		{
			m_InfoListCtrl.SetItem(lineno,iCols,LVIF_TEXT,_T(""),0,0,0,0);
		}
		iCols++;
	}
	va_end(rowCols);
	return lineno;
}

void CKSNLDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CKSNLDlg::SetLimtText(int sizeFlag)
{
	m_sizeFlag = sizeFlag;		
}
