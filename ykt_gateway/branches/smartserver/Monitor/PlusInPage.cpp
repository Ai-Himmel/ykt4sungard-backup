// PlusInPage.cpp : implementation file
//

#include "stdafx.h"
#include "Monitor.h"
#include "PlusInPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlusInPage dialog


CPlusInPage::CPlusInPage(CWnd* pParent /*=NULL*/)
	: CDialog(CPlusInPage::IDD, pParent)
{
	m_nItem = -1 ;
	m_strName = "" ;
}


void CPlusInPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPlusInPage)
	DDX_Control(pDX, IDC_EDIT_PLUSMACTYPE, m_editMacType);
	DDX_Control(pDX, IDC_EDIT_PLUSOTHER, m_editOther);
	DDX_Control(pDX, IDC_EDIT_PLUSTASK, m_editTask);
	DDX_Control(pDX, IDC_EDIT_PLUSPATH, m_editPath);
	DDX_Control(pDX, IDC_LIST1, m_list);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPlusInPage, CDialog)
	//{{AFX_MSG_MAP(CPlusInPage)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_BN_CLICKED(IDC_BTN_PLUSSET, OnBtnPlusset)
	ON_BN_CLICKED(IDC_BTN_PLUSDEL, OnBtnPlusdel)
	ON_BN_CLICKED(IDC_BTN_PLUSNEW, OnBtnPlusnew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlusInPage message handlers

BOOL CPlusInPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_ImageList.Create(32, 32, ILC_COLOR16|ILC_MASK, 0, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
	m_list.SetImageList(&m_ImageList, LVSIL_NORMAL);

	m_list.InsertColumn(0, "文件名", LVCFMT_LEFT, 200, -1);
	m_list.InsertColumn(1, "描述", LVCFMT_LEFT, 100, -1);

	UINT nCount = GetPrivateProfileInt("MODULE", "COUNT", 0, strServerINI);

	TCHAR  szItem[64];
	TCHAR  szValue[256];
	DWORD  dwSize = sizeof(szValue);

	for(UINT i=0; i< nCount; i++)
	{
		wsprintf(szItem, "MODULE%d", i+1);
		GetPrivateProfileString("MODULE", szItem, "", szValue, dwSize, strServerINI);
		m_list.InsertItem(i, szValue, 0);
	}

	return TRUE;
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPlusInPage::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if( pNMListView->iItem >= 0 )
	{
//		GetDlgItem(IDC_BTN_PLUSDEL)->EnableWindow(TRUE);
//		GetDlgItem(IDC_BTN_PLUSSET)->EnableWindow(TRUE);

		m_nItem = pNMListView->iItem ;
		m_strName = m_list.GetItemText(pNMListView->iItem, 0);
		m_editPath.SetWindowText(m_strName);

		m_editMacType.SetWindowText("");
		m_editTask.SetWindowText("");
		m_editOther.SetWindowText("");

		DWORD dwSize = GetFileVersionInfoSize(m_strName.GetBuffer(0), NULL);
		TCHAR szBuffer[4096];
				
		if( GetFileVersionInfo(m_strName.GetBuffer(0), NULL, dwSize, szBuffer) )
		{
			LPTSTR pszString = NULL ;
			UINT nLength = 0 ;

			if( VerQueryValue(szBuffer, 
						TEXT("\\StringFileInfo\\080404b0\\Comments"), 
						(LPVOID*)&pszString, 
						&nLength) )
			{
				if( nLength > 0 )
				{
					m_editOther.SetWindowText(pszString);
					LocalFree(pszString);
				}
			}
		}

		HINSTANCE hHandle = LoadLibrary(m_strName.GetBuffer(0));
		if( hHandle != NULL )
		{
			typedef long (__stdcall *lpfnDLLSupportInfo)(TSSmartSupport *pSupport);
			lpfnDLLSupportInfo  DLLSupportInfo = NULL ;
			DLLSupportInfo = (lpfnDLLSupportInfo)GetProcAddress(hHandle, "DLLSupportInfo");
			if( DLLSupportInfo != NULL )
			{
				TSSmartSupport   Info;
				CString strValue, strText = "" ;

				ZeroMemory(&Info, sizeof(Info));

				DLLSupportInfo(&Info);
				if( Info.nMacCount == 0 )
				{
					m_editMacType.SetWindowText("全部机型");
				}
				else
				{
					for(int i=0; i< Info.nMacCount; i++)
					{
						strValue.Format("%s,", Info.MacType[i]);
						strText += strValue ;
					}
					m_editMacType.SetWindowText(strText);
				}

				strText = "" ;
				for(int i=0; i< Info.nTaskCount; i++)
				{
					strValue.Format("%s,", Info.TaskCode[i]);
					strText += strValue ;
				}

				m_editTask.SetWindowText(strText);
			}
			FreeLibrary(hHandle);
		}
	}
	else
	{
		GetDlgItem(IDC_BTN_PLUSDEL)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_PLUSSET)->EnableWindow(FALSE);
		m_strName = "" ;
		m_nItem = -1;
	}

	*pResult = 0;
}

void CPlusInPage::OnBtnPlusset() 
{
	if( m_strName == "" )
		return ;

	HINSTANCE hHandle = LoadLibrary(m_strName.GetBuffer(0));
	if( hHandle == NULL )
	{
		AfxMessageBox("不能装入业务动态库!");
		return ;
	}

	typedef long (__stdcall *lpfnDLLSetup)() ;
	lpfnDLLSetup  DLLSetup = NULL ;
	DLLSetup = (lpfnDLLSetup)GetProcAddress(hHandle, "DLLSetup");
	if( DLLSetup == NULL )
	{
		AfxMessageBox("业务动态库不支持设置功能!");
		FreeLibrary(hHandle);
		return ;
	}

	DLLSetup();
	FreeLibrary(hHandle);

	return ;
}

void CPlusInPage::OnBtnPlusdel() 
{
	if( m_nItem < 0 )
		return ;

	if( AfxMessageBox("您确认删除此业务插件?",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2) != IDYES )
		return ;

	m_list.DeleteItem(m_nItem);
	m_nItem = -1 ;
}

void CPlusInPage::OnBtnPlusnew() 
{
	static char BASED_CODE szFilter[] = "Task DLL Files (*.dll)|*.dll|All Files (*.*)|*.*||"; 

	CFileDialog  dlg(TRUE, _T("*.DLL"), _T("TASK.DLL"), 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if( dlg.DoModal() == IDOK )
	{
		m_list.InsertItem(m_list.GetItemCount(), dlg.GetFileName(), 0);
	}
}

bool CPlusInPage::SaveToDisk()
{
	UpdateData(TRUE);

	if( m_list.GetItemCount() <= 0 )
	{
		AfxMessageBox("应至少有一个业务插件!");
		return false;
	}

	CString strValue;

	strValue.Format("%d", m_list.GetItemCount());
    WritePrivateProfileString("MODULE", "COUNT", strValue, strSmartTemp);

	for(int i=0; i< m_list.GetItemCount(); i++)
	{
		CString strFileName = m_list.GetItemText(i, 0);

		strValue.Format("MODULE%d", i+1);
	    WritePrivateProfileString("MODULE", strValue.GetBuffer(0), strFileName, strSmartTemp);
	}

	return true;
}

BOOL CPlusInPage::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_ESCAPE )
		{
			return TRUE;
		}
		else if( pMsg->wParam == VK_RETURN )
		{
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}
