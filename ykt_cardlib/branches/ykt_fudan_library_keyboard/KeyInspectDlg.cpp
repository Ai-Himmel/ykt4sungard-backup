// KeyInspectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KeyInspect.h"
#include "KeyInspectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#include "label.h"
#include "hyperlink.h"
HWND hWnd;
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CHyperLink	m_labelWWW;
	CLabel	m_labelNetAdd;
	CHyperLink	m_email;
	CLabel	m_labelPhone;
	CLabel	m_labelName;
	CLabel	m_labelAddFax;
	CLabel	m_labelAdd2;
	CLabel	m_labelAdd1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDC_STATIC_WWW, m_labelWWW);
	DDX_Control(pDX, IDC_STATIC_NETADD, m_labelNetAdd);
	DDX_Control(pDX, IDC_STATIC_EMAIL, m_email);
	DDX_Control(pDX, IDC_STATIC_COMPANYPHONE, m_labelPhone);
	DDX_Control(pDX, IDC_STATIC_COMPANYNAME, m_labelName);
	DDX_Control(pDX, IDC_STATIC_COMPANYFAX, m_labelAddFax);
	DDX_Control(pDX, IDC_STATIC_COMPANYADDRESS2, m_labelAdd2);
	DDX_Control(pDX, IDC_STATIC_COMPANYADDRESS1, m_labelAdd1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyInspectDlg dialog

CKeyInspectDlg::CKeyInspectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyInspectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKeyInspectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyInspectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKeyInspectDlg)
	DDX_Control(pDX, IDC_CHECK1, m_btnCheck);
	DDX_Control(pDX, IDC_STATIC_NAME, m_Name);
	DDX_Control(pDX, IDC_STATIC_COMPANY_WWW, m_www);
	DDX_Control(pDX, IDC_STATIC_PAR, m_labelPar);
	DDX_Control(pDX, IDC_STATIC_PORTNO, m_labelPortNo);
	DDX_Control(pDX, IDC_STATIC_BUADRATE, m_labelBuadRate);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btnPause);
	DDX_Control(pDX, IDC_BUTTON_HIDE, m_btnHide);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_COMBO_PORTNO, m_comboPortNo);
	DDX_Control(pDX, IDC_COMBO_BUADRATE, m_comboBuadRate);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKeyInspectDlg, CDialog)
	//{{AFX_MSG_MAP(CKeyInspectDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, OnButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_COMMAND(IDI_EXIT, OnExit)
	ON_COMMAND(IDI_SHOW, OnShow)
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_WM_CHAR()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECV_MESSAGE,OnComPortRead)
	ON_MESSAGE(WM_TRAY_NOTIFY,OnTrayNotify)
	ON_MESSAGE(WM_MSG_RXRCV,OnRxRcv)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKeyInspectDlg message handlers

BOOL CKeyInspectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		//VERIFY(pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND));
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	HICON hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_TrayIconDriver.Create(this,WM_TRAY_NOTIFY,"点右键",hIcon,IDR_POPUP_MENU);

	m_comboPortNo.SetCurSel(0);
	m_comboBuadRate.SetCurSel(0);
	m_btnStart.SetIcon(IDI_ICON_START);
	m_btnStart.SetActiveFgColor(RGB(0,0,255),TRUE);
	m_btnStart.SetInactiveFgColor(RGB(0,0,255),TRUE);
	m_btnPause.SetIcon(IDI_ICON_STOP);
	m_btnPause.SetActiveFgColor(RGB(0,0,255),TRUE);
	m_btnPause.SetInactiveFgColor(RGB(0,0,255),TRUE);
	m_btnHide.SetIcon(IDI_ICON_HIDE);
	m_btnHide.SetActiveFgColor(RGB(0,0,255),TRUE);
	m_btnHide.SetInactiveFgColor(RGB(0,0,255),TRUE);
	m_btnExit.SetIcon(IDI_ICON_EXIT);
	m_btnExit.SetActiveFgColor(RGB(0,0,255),TRUE);
	m_btnExit.SetInactiveFgColor(RGB(0,0,255),TRUE);
	m_labelPortNo.SetTextColor(RGB(0,0,255));
	m_labelBuadRate.SetTextColor(RGB(0,0,255));
//	m_labelPar.SetTextColor(RGB(0,0,255));
	m_Name.SetTextColor(RGB(0,0,255));
	m_Name.SetFontBold(TRUE);
	m_btnPause.EnableWindow(FALSE);
	m_nSize = 0;
	m_btnCheck.SetCheck(0);
	hWnd = m_hWnd;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CKeyInspectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CKeyInspectDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CKeyInspectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKeyInspectDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CKeyInspectDlg::OnOK() 
{
	//CDialog::OnOK();
}

void CKeyInspectDlg::OnButtonExit() 
{
	if((::AfxMessageBox("警告：退出监控系统 ?",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
	  &&(::AfxMessageBox("退出监控系统 ?",MB_YESNO|MB_ICONQUESTION)==IDYES))
	{
		CDialog::OnCancel();
	}		
	
}

//开启
void CKeyInspectDlg::OnButtonStart() 
{
	
	CString cs;
	int ret;
	m_comboPortNo.GetWindowText(cs);
	if(cs.IsEmpty())
	{
		::AfxMessageBox("请选择串口!!!",MB_OK);
		return;
	}
	m_nPortNo = m_comboPortNo.GetCurSel()+1;
	ret = sio_open(m_nPortNo);
	if(ret != SIO_OK)
	{
		AfxMessageBox("串口打开错误，请检查!");
		return ;
	}
	m_comboBuadRate.GetWindowText(cs);
	if(cs.IsEmpty())
	{
		::AfxMessageBox("请选择通讯波特率!!!",MB_OK);
		return;
	}
	m_nBuadRate = m_comboBuadRate.GetCurSel();
	int i;	
	i = m_nBuadRate;
	if(i == 0)
		m_nBuadRate = B19200;		
	else if(i == 1)
		m_nBuadRate = B9600;
	else if(i == 2)
		m_nBuadRate = B4800;
	else
		m_nBuadRate = B19200;

	ret = sio_ioctl(m_nPortNo, m_nBuadRate , P_NONE | BIT_8 | STOP_1);
	
	ret = sio_SetReadTimeouts(m_nPortNo , MAXDWORD, 0);
	ret = sio_SetWriteTimeouts(m_nPortNo , MAXDWORD);
	ret = sio_flush(m_nPortNo, 2 );
	ret = sio_cnt_irq(m_nPortNo, CntIrq, 1);
		
	m_dwReadLength = 0;
	m_btnStart.EnableWindow(FALSE);
	m_btnPause.EnableWindow(TRUE);
	m_bFlag = m_btnCheck.GetCheck();
	//SetTimer(1,1000,NULL);
	OnButtonHide();
	memset(m_pucReadBuf,0x00,256);
}

//暂停
void CKeyInspectDlg::OnButtonPause() 
{
	int ret;
	ret = sio_close(m_nPortNo);
	if(ret != SIO_OK)
	{
		::AfxMessageBox("串口关闭错误!!!",MB_OK);
		return;
	}
	m_btnStart.EnableWindow(TRUE);
	m_btnPause.EnableWindow(FALSE);
}
//隐藏
void CKeyInspectDlg::OnButtonHide() 
{
	ShowWindow(SW_HIDE);
    m_TrayIconDriver.SetTooltipText(IsWindowVisible()?IDS_TRAY_ICON_SHOW:IDS_TRAY_ICON_HIDE);
    m_TrayIconDriver.SetIcon(IDR_MAINFRAME);
	
	
}

LRESULT CKeyInspectDlg::OnComPortRead(WPARAM wParam,LPARAM lParam)
{
	int  i,length;
	length = (int)wParam;
	for(i=0;i<length;i++)
	{
		keybd_event(m_pComThread->m_pucSmtBuf[i],0,0,0); 
		keybd_event(m_pComThread->m_pucSmtBuf[i],0,KEYEVENTF_KEYUP,0);

	}

	//debug
	/*CString cs;
	cs.Format("%.2X",i);
	MessageBox(cs,NULL,MB_OK);*/
	return 0l;
}
LRESULT CKeyInspectDlg::OnTrayNotify(WPARAM wParam,LPARAM lParam)
{
	return m_TrayIconDriver.OnTrayNotify(wParam,lParam);
}

void CKeyInspectDlg::OnExit() 
{
	OnButtonExit();
	
}

void CKeyInspectDlg::OnShow() 
{
	UpdateData(FALSE);
	ShowWindow(IsWindowVisible()?SW_HIDE:SW_SHOWNORMAL);
    m_TrayIconDriver.SetTooltipText(IsWindowVisible()?IDS_TRAY_ICON_SHOW:IDS_TRAY_ICON_HIDE);
    m_TrayIconDriver.SetIcon(IDR_MAINFRAME);
}

void CKeyInspectDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("aaa",NULL,MB_OK);
	OnButtonExit();
	//CDialog::OnClose();
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_labelName.SetTextColor(RGB(0,0,255));	
	m_labelName.SetFontBold(TRUE);
	m_labelAdd1.SetTextColor(RGB(0,0,255));	
	m_labelAdd1.SetFontBold(TRUE);
	m_labelAdd2.SetTextColor(RGB(0,0,255));	
	m_labelAdd2.SetFontBold(TRUE);
	m_labelPhone.SetTextColor(RGB(0,0,255));	
	m_labelPhone.SetFontBold(TRUE);
	m_labelAddFax.SetTextColor(RGB(0,0,255));	
	m_labelAddFax.SetFontBold(TRUE);
	m_labelNetAdd.SetTextColor(RGB(0,0,255));	
	m_labelNetAdd.SetFontBold(TRUE);
	m_email.SetURL(_T("mailto:GDZHJK@public.guangzhou.gd.cn?subject=我的建议:"));
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CKeyInspectDlg::OnSize(UINT nType, int cx, int cy) 
{
	//CDialog::OnSize(nType, cx, cy);
	//MessageBox("aa",NULL,MB_OK);
	if(m_nSize == 0)
	{
		OnButtonHide();
		m_nSize = 1;
		return;
	}
	if(m_nSize == 1)
	{
		//OnButtonHide();
		m_nSize = 0;
		return;
	}

	// TODO: Add your message handler code here
	
}


void CKeyInspectDlg::CntIrq(int port)
{
	::PostMessage(hWnd,WM_MSG_RXRCV,port,0);
}

LRESULT CKeyInspectDlg::OnRxRcv(WPARAM wParam,LPARAM lParam)
{
	DWORD      dwLength,i,j;
	char       ucReadBuf[512] = "",
		       bbb;
	int        port;
	port = (int)wParam;
	
	BYTE  b;
	
	//memset(m_pucReadBuf,0x00,256);
	dwLength = sio_read(port,ucReadBuf,512);
	CString cs,cs1;
	if(m_dwReadLength == 0)
	{
		if(((BYTE)ucReadBuf[0]) == 0xA3 )
		{
			for(i=0;i<dwLength;i++)
			{
				b = (BYTE)ucReadBuf[i];
				m_pucReadBuf[i+m_dwReadLength] = b;
			}
			m_dwReadLength = dwLength;	
			if(m_dwReadLength >= 33)
			{
				SimulateKeyPress();
				m_dwReadLength = 0; 
				memset(m_pucReadBuf,0x00,256);
				return 0l;
			}
			else
				return 0l;
		}
		if(((BYTE)ucReadBuf[0]) == 0xA2 )
		{
			for(i=0;i<dwLength;i++)
			{
				b = (BYTE)ucReadBuf[i];
				m_pucReadBuf[i+m_dwReadLength] = b;
			}
			m_dwReadLength = dwLength;	
			if(m_dwReadLength == 5)
			{
				SimulateKeyPress();
				m_dwReadLength = 0; 
				memset(m_pucReadBuf,0x00,256);
				return 0l;
			}
			else
				return 0l;
		}
		return 0l;
	}
	else
	{
		if(m_pucReadBuf[0] == 0xa3 )
		{
			for(i=0;i<dwLength;i++)
			{
				b = (BYTE)ucReadBuf[i];
				m_pucReadBuf[i+m_dwReadLength] = b;
			}
			m_dwReadLength += dwLength;	
			if(m_dwReadLength >= 11)
			{
				SimulateKeyPress();
				m_dwReadLength = 0; 
				memset(m_pucReadBuf,0x00,256);
				return 0l;
			}
			else
				return 0l;
		}
		if(m_pucReadBuf[0] == 0xa2 )
		{
			for(i=0;i<dwLength;i++)
			{
				b = (BYTE)ucReadBuf[i];
				m_pucReadBuf[i+m_dwReadLength] = b;
			}
			m_dwReadLength += dwLength;	
			if(m_dwReadLength == 5)
			{
				SimulateKeyPress();
				m_dwReadLength = 0; 
				memset(m_pucReadBuf,0x00,256);
				return 0l;
			}
			else
				return 0l;
		}
		return 0l;

	}
	return 0l;
}

void CKeyInspectDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	char sendbuf[256];
	m_dwReadLength = 0;
	sendbuf[0] = 0xc0;
	sendbuf[1] = 0xff;
	sendbuf[2] = 0x6d;//0x6c;
	sendbuf[3] = 0x00;  // 
	sendbuf[4] = 0xad;//0x9e;
	sendbuf[5] = 0x03;//0x32;
	sendbuf[6] = 0xc1;
	sio_write(m_nPortNo,sendbuf,7);
}

void CKeyInspectDlg::SimulateKeyPress()
{
	int i,nMoney;
	char bbb,
		 ucReadBuf[256] = "";
	float fMoney;
	bool flag = false;
	CString cs,cs1;
	short state = 0;
//	UINT scan_code = 0;
	short virtual_key = 0;
//	LPARAM lpar = 0x0001;
//	DWORD curID = 0,
//		  wID = 0; 
	/*模拟键盘快捷键组合使用*/
	/*Ctrl + Shift + 1*/
	keybd_event(VK_CONTROL, 0, 0, 0);
	keybd_event(VK_LSHIFT, 0, 0, 0);
	keybd_event(0x31, 0, 0, 0);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(0x31, 0, KEYEVENTF_KEYUP, 0);

	/*
	HWND hWnd = ::GetForegroundWindow();
	if (hWnd != NULL)
	{
		curID = ::GetCurrentThreadId();
		wID = ::GetWindowThreadProcessId(hWnd,NULL);
		::AttachThreadInput(wID, curID, TRUE);
		hWnd = ::GetFocus();
		::AttachThreadInput(wID, curID, FALSE);
	*/	
		if(m_pucReadBuf[0] == 0xA3)
		{
			for(i = 0; i < 32; i++)
			{
				ucReadBuf[i] = m_pucReadBuf[1+i];
//				if(ucReadBuf[i] != 0xff || ucReadBuf[i] != 0x00) //空格不打
				if(ucReadBuf[i] != 0xff && ucReadBuf[i] != 0x00)
					flag = true;
				if(flag == true)
				{
					//				if (ucReadBuf[i] >= '0' ucReadBuf[i] )
					bbb = ucReadBuf[i] - 0x30;//(ucReadBuf[i]>>4)&0x0f;
					bbb = bbb + 0x30;
					virtual_key = VkKeyScan(bbb);
					
					state = GetKeyState(VK_CAPITAL);
					if (state & 0x0F)
					{
						keybd_event(VK_CAPITAL, 0, 0, 0);
						keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
						keybd_event((BYTE)virtual_key, 0, 0, 0);
						keybd_event((BYTE)virtual_key, 0, KEYEVENTF_KEYUP, 0);
						keybd_event(VK_CAPITAL, 0, 0, 0);
						keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
					}
					else
					{
						keybd_event((BYTE)virtual_key, 0, 0, 0); 
						keybd_event((BYTE)virtual_key, 0, KEYEVENTF_KEYUP, 0);	
					}
//					scan_code = MapVirtualKey(virtual_key, 0);
//					lpar |= (scan_code << 16);
//					keybd_event(bbb,0,0,0); 
//					keybd_event(bbb,0,KEYEVENTF_KEYUP,0);
//					::PostMessage(hWnd, WM_CHAR, (WPARAM)bbb, NULL);
					//bbb = ucReadBuf[i]&0x0f;
					//bbb = bbb+0x30;
					//keybd_event(bbb,0,0,0); 
					//keybd_event(bbb,0,KEYEVENTF_KEYUP,0);
				}
				flag = false;
			}
			//if(m_bFlag == true)
			if(m_btnCheck.GetCheck() == 1)
			{
				bbb = 0x0d;
//				::PostMessage(hWnd, WM_KEYDOWN, (WPARAM)bbb, NULL);
//				::PostMessage(hWnd, WM_KEYUP, NULL, NULL);
//				::PostMessage(hWnd, WM_CHAR, (WPARAM)bbb, NULL);
				
				keybd_event(bbb,0,0,0); 
				keybd_event(bbb,0,KEYEVENTF_KEYUP,0);
				return ;
			}	
		}
//	}
	//if(m_pucReadBuf[0] == 0xC2)
	if(m_pucReadBuf[0] == 0xA2)
	{
		nMoney = m_pucReadBuf[4]*256*256*256+
			     m_pucReadBuf[3]*256*256+
				 m_pucReadBuf[2]*256+
				 m_pucReadBuf[1];
		fMoney = nMoney/100.0;
		
		cs.Format("%.2f",fMoney);
		/*char pChar='1';		
		SHORT ks = VkKeyScan(pChar);
		BYTE key = ks & 0xFF;
		cs.Format("%.2X",key);*/
		//MessageBox(cs,NULL,MB_OK);
		//return;
	//	keybd_event(key,0,0,0);
	//	keybd_event(key,0,KEYEVENTF_KEYUP,0);
		for(i=0;i<cs.GetLength();i++)
		{
			//VkKeyScan(('.');
			if(cs.GetAt(i) == '.')
			{
				keybd_event(0xbe,0,0,0);
				keybd_event(0xbe,0,KEYEVENTF_KEYUP,0);
			}
			else
			{
				keybd_event(cs.GetAt(i),0,0,0);
				keybd_event(cs.GetAt(i),0,KEYEVENTF_KEYUP,0);
			}
		}	
		

		
		
		//if(m_bFlag == true)
		if(m_btnCheck.GetCheck() == 1)
		{
			bbb = 0x0d;
			keybd_event(bbb,0,0,0); 
			keybd_event(bbb,0,KEYEVENTF_KEYUP,0);
		
		}
	}


}




void CKeyInspectDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnButton1();
	CDialog::OnTimer(nIDEvent);
}

void CKeyInspectDlg::OnCheck1() 
{
	
	m_bFlag = m_btnCheck.GetCheck();
	
}

void CKeyInspectDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString cs;
	cs.Format("%d",nChar);
	MessageBox(cs,NULL,MB_OK);

	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CKeyInspectDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString cs;
	cs.Format("%d",nChar);
	MessageBox(cs,NULL,MB_OK);
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CAboutDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString cs;
	cs.Format("%d",nChar);
	MessageBox(cs,NULL,MB_OK);
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CKeyInspectDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	CString cs;
	cs.Format("%d",nChar);
	MessageBox(cs,NULL,MB_OK);
	//CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CKeyInspectDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYUP)
	{
		CString str_code = "";
		
//		UINT key_code = MapVirtualKey(pMsg->wParam,0);
//		UINT key_code = MapVirtualKey(0x2E,1);
//		str_code.Format("%d : %d", pMsg->lParam, key_code);
//		MessageBox(str_code,NULL,MB_OK);
//		keybd_event(67,0,0,0); 
//		keybd_event(67,0,KEYEVENTF_KEYUP,0);
	}
	return CDialog::PreTranslateMessage(pMsg);
}

int CKeyInspectDlg::KeyDownLowCaseChar(int &low_case_char)
{
	if (low_case_char >= 97 &&low_case_char <= 122)
		low_case_char -= 32;
	return 0;
}

int CKeyInspectDlg::KeyDownUpCaseChar(int &up_case_char)
{
	if (up_case_char >= 65 && up_case_char <= 90)
	{
			keybd_event(VK_SHIFT,0,0,0); 
			keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
	}
	return 0;
}
