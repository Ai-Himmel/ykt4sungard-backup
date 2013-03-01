// testgwdllDlg.cpp : implementation file
//

#include "stdafx.h"
#include "testgwdll.h"
#include "testgwdllDlg.h"
#include "gwdef.h"
#include ".\testgwdlldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestgwdllDlg dialog

CTestgwdllDlg::CTestgwdllDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestgwdllDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestgwdllDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestgwdllDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestgwdllDlg)
	DDX_Control(pDX, IDC_LST_RESULT, m_result_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestgwdllDlg, CDialog)
	//{{AFX_MSG_MAP(CTestgwdllDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_BTN_READINFO, OnBtnReadinfo)
	//}}AFX_MSG_MAP
//	ON_WM_ACTIVATE()
ON_BN_CLICKED(IDC_BTN_LOSS_OF_STH, OnBnClickedBtnLossOfSth)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestgwdllDlg message handlers

BOOL CTestgwdllDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestgwdllDlg::OnPaint() 
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
HCURSOR CTestgwdllDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestgwdllDlg::OnLogin() 
{
	
	if(KLogin() != 0)
	{
		ShowErrorMsg();
	}
	else
	{
		AfxMessageBox("签到成功");
	}
}

void CTestgwdllDlg::ShowErrorMsg()
{
	char msg[512 + 1] = "";
	KGetErrorMsg(msg);
	CString tmp;
	tmp.Format("[%d]%s",KGetErrorNo(),msg);
	AfxMessageBox(tmp);
}

void CTestgwdllDlg::OnBtnReadinfo() 
{
	CString phyid,showid,stuempno;
	CWnd * pItem;
	if((pItem = GetDlgItem(IDC_EDT_PHYID)) == NULL)
	{
		AfxMessageBox("程序异常!");
		return;
	}
	pItem->GetWindowText(phyid);

	if((pItem = GetDlgItem(IDC_EDT_SHOWID)) == NULL)
	{
		AfxMessageBox("程序异常!");
		return;
	}
	pItem->GetWindowText(showid);

	if((pItem = GetDlgItem(IDC_EDT_STUEMP_NO)) == NULL)
	{
		AfxMessageBox("程序异常!");
		return;
	}
	pItem->GetWindowText(stuempno);

	CardInfo_t card;
	memset(&card,0,sizeof card);
	if(KGetCardInfo((LPCTSTR)phyid,(LPCTSTR)showid
		,(LPCTSTR)stuempno,&card))
	{
		ShowErrorMsg();
	}
	else
	{
		while(m_result_list.GetCount() > 0)
		{
			m_result_list.DeleteString(0);
		}
		CString line;
		line.Format("卡号: %d\n",card.cardid);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("物理卡号: %s",card.phyid);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("显示卡号: %s",card.cardno);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("姓名: %s",card.name);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("性别: %d",card.sex);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("学工号: %s",card.stuemp_no);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("部门号: %s",card.deptno);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("部门名称: %s",card.deptname);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("类别: %d",card.cut_type);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("类别名称: %s",card.cut_name);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("卡类型: %d",card.card_type_id);
		m_result_list.AddString((LPCTSTR)line);
		line.Format("卡类型名称;%s",card.card_type_name);
		m_result_list.AddString((LPCTSTR)line);
		
	}

}

//void CTestgwdllDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
//{
//	CDialog::OnActivate(nState, pWndOther, bMinimized);
//
//	// TODO: Add your message handler code here
//}


void CTestgwdllDlg::OnBnClickedBtnLossOfSth()
{
	// TODO: Add your control notification handler code here
	char stuempno[21] = "00000024";
	char password[] = "180456";
	int flag = 1;
	int ret = KGetLossOfSthByStuempNo(stuempno, password, flag);
	if (ret)
	{
		::AfxMessageBox("挂失失败!");
		return;
	}
	return ;
}
