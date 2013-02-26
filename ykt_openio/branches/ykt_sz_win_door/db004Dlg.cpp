// db004Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "db004.h"
#include "db004Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDb004Dlg dialog

CDb004Dlg::CDb004Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDb004Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDb004Dlg)
// 	m_strId = _T("");
// 	m_strName = _T("");
// 	m_nScore = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDb004Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDb004Dlg)

// 	DDX_Text(pDX, IDC_EDIT_ID, m_strId);
// 	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
// 	DDX_Text(pDX, IDC_EDIT_SCORE, m_nScore);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDb004Dlg, CDialog)
	//{{AFX_MSG_MAP(CDb004Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
//	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
//	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
//	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STDUENT, OnDblclkListStduent)
	//}}AFX_MSG_MAP


//	ON_BN_CLICKED(IDC_BUTTON3, &CDb004Dlg::OnBnClickedButton3)
//	ON_BN_CLICKED(IDC_BUTTON4, &CDb004Dlg::OnBnClickedButton4)
//	ON_BN_CLICKED(IDC_BUTTON5, &CDb004Dlg::OnBnClickedButton5)
	ON_WM_TIMER()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDb004Dlg message handlers


void CDb004Dlg:: Opencmd(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* sqltext)
{
	m_pCommand.CreateInstance(__uuidof(Command));
	m_pCommand->ActiveConnection=m_cnn;
	m_pCommand->CommandType=adCmdStoredProc;
	//m_pCommand->CommandText=_bstr_t("sp_wg_NewConsumer");		
	m_pCommand->CommandText=_bstr_t(sqltext);

}

void CDb004Dlg:: Appendcmd(_CommandPtr& m_pCommand,char prm_name[],DataTypeEnum prm_type,\
						   ParameterDirectionEnum prm_direction,char prm_value[])
{
	_ParameterPtr mp_var1;
	if(prm_type==adInteger)
	{
		mp_var1=m_pCommand->CreateParameter(_bstr_t(prm_name),prm_type,prm_direction,4,_variant_t(prm_value));	
	}
	else if(prm_type==adVarChar)
	{
		mp_var1=m_pCommand->CreateParameter(_bstr_t(prm_name),prm_type,prm_direction,strlen(prm_value)+1,_variant_t(_bstr_t(prm_value)));	
	}
	m_pCommand->Parameters->Append(mp_var1);
}



void CDb004Dlg:: Appendret(_CommandPtr& m_pCommand,_ParameterPtr& mp_var)
{
	mp_var=m_pCommand->CreateParameter(_bstr_t("total"),adInteger,adParamReturnValue,4,_variant_t("0"));
	m_pCommand->Parameters->Append(mp_var);
}


void CDb004Dlg:: Opencmd_ret(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* sqltext,_ParameterPtr& ret_var)
{
	//Opencmd(m_pCommand,m_cnn,"sp_wg_NewConsumer");
	Opencmd(m_pCommand,m_cnn,sqltext);
	Appendret(m_pCommand,ret_var);
}


int CDb004Dlg:: Executecmd(_CommandPtr& m_pCommand,_ParameterPtr& ret_var)
{
	m_pCommand->Execute(NULL,NULL,adCmdStoredProc);
	return ret_var->Value;
}

//int CDb004Dlg:: wg_NewConsumer(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,int CARDPHYID,char* ConsumerName,char* GroupName)
int CDb004Dlg:: sp_wg_NewConsumer(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID,char* ConsumerName,char* GroupName)
{
	_ParameterPtr ret_var;
	Opencmd_ret(m_pCommand,m_cnn,"sp_wg_NewConsumer",ret_var);
	Appendcmd(m_pCommand,"CARDPHYID",adInteger,adParamInput,CARDPHYID);
	Appendcmd(m_pCommand,"ConsumerName",adVarChar,adParamInput,ConsumerName);
	if(GroupName!=NULL)
	{
		Appendcmd(m_pCommand,"GroupName",adVarChar,adParamInput,GroupName);
	}
	//int xx;
	//xx=Executecmd(m_pCommand,ret_var);	
	return Executecmd(m_pCommand,ret_var);
}

int CDb004Dlg:: sp_wg_DeleteConsumer(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID)
{
	_ParameterPtr ret_var;
	Opencmd_ret(m_pCommand,m_cnn,"sp_wg_DeleteConsumer",ret_var);
	Appendcmd(m_pCommand,"CARDPHYID",adInteger,adParamInput,CARDPHYID);
	return Executecmd(m_pCommand,ret_var);
}

int CDb004Dlg:: sp_wg_EditConsumerNameAndGroupName(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID,char* ConsumerName,char* GroupName)
{
	_ParameterPtr ret_var;
	Opencmd_ret(m_pCommand,m_cnn,"sp_wg_EditConsumerNameAndGroupName",ret_var);
	Appendcmd(m_pCommand,"CARDPHYID",adInteger,adParamInput,CARDPHYID);
	Appendcmd(m_pCommand,"ConsumerName",adVarChar,adParamInput,ConsumerName);
	if(GroupName!=NULL)
	{
		Appendcmd(m_pCommand,"GroupName",adVarChar,adParamInput,GroupName);
	}
	return Executecmd(m_pCommand,ret_var);
}


int CDb004Dlg:: sp_wg_RegisterLostCard(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID,char* NewCARDPHYID)
{
	_ParameterPtr ret_var;
	Opencmd_ret(m_pCommand,m_cnn,"sp_wg_RegisterLostCard",ret_var);
	Appendcmd(m_pCommand,"CARDPHYID",adInteger,adParamInput,CARDPHYID);
	Appendcmd(m_pCommand,"NewCARDPHYID",adInteger,adParamInput,NewCARDPHYID);
	return Executecmd(m_pCommand,ret_var);
}

int CDb004Dlg:: sp_wg_RegisterLostCardWithoutNewCard(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID)
{
	_ParameterPtr ret_var;
	Opencmd_ret(m_pCommand,m_cnn,"sp_wg_RegisterLostCardWithoutNewCard",ret_var);
	Appendcmd(m_pCommand,"CARDPHYID",adInteger,adParamInput,CARDPHYID);
	//Appendcmd(m_pCommand,"NewCARDPHYID",adInteger,adParamInput,NewCARDPHYID);
	return Executecmd(m_pCommand,ret_var);
}

int CDb004Dlg:: sp_wg_ReleaseLostCard(_CommandPtr& m_pCommand,_ConnectionPtr& m_cnn,char* CARDPHYID)
{
	_ParameterPtr ret_var;
	Opencmd_ret(m_pCommand,m_cnn,"sp_wg_ReleaseLostCard",ret_var);
	Appendcmd(m_pCommand,"CARDPHYID",adInteger,adParamInput,CARDPHYID);
	return Executecmd(m_pCommand,ret_var);
}



BOOL CDb004Dlg:: ConnectDb(_ConnectionPtr& m_cnn,char* udl)
{
	_bstr_t strcnn(_T(udl));
	try
	{
		m_cnn.CreateInstance(__uuidof(Connection));
		m_cnn->Open(strcnn,  _T(""), _T(""), adModeUnknown);
		
	//	_CommandPtr m_pCommand;
	//		int x,y;
	//	x=sp_wg_NewConsumer(m_pCommand,m_cnn,"91234","��С��",NULL);
	//	x=sp_wg_NewConsumer(m_pCommand,m_cnn,"91235","����","������");
	//	x=sp_wg_DeleteConsumer(m_pCommand,m_cnn,"91234");
// 		x=sp_wg_EditConsumerNameAndGroupName(m_pCommand,m_cnn,"91234","��С��2","������");
// 		x=sp_wg_EditConsumerNameAndGroupName(m_pCommand,m_cnn,"91234","��С��2",NULL);
//		x=sp_wg_RegisterLostCard(m_pCommand,m_cnn,"91234","91235");
//		x=sp_wg_RegisterLostCardWithoutNewCard(m_pCommand,m_cnn,"91234");
//		x=sp_wg_ReleaseLostCard(m_pCommand,m_cnn,"91234");
//		y=x;
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("�������ݿ�ʧ��!"), MB_OK|MB_ICONSTOP);
		return FALSE;
	}
	return TRUE;
}

BOOL CDb004Dlg::FileExist(CString fileName)
{
	CFileFind fFind;
	return fFind.FindFile(fileName);
}

CDb004Dlg:: ~CDb004Dlg()
{
//	file.Close();
}

BOOL CDb004Dlg::Openfile(CFile& file)
{
	CString str;
	CString fileName;
	CFileException fileException;
	CTime time=CTime::GetCurrentTime();
	str.Format( "%4d%02d%02d",time.GetYear(), time.GetMonth(), time.GetDay());
	fileName="log\\"+str+".txt";
	if(FileExist(fileName))
	{
		if (!file.Open((LPSTR)(LPCTSTR)fileName, CFile::modeWrite, &fileException))
		{
			//��ʾ�쳣��Ϣ
			CString errorInfo;
			errorInfo.Format("���ܴ��ļ�%s, ����%u\n", fileName, fileException.m_cause);
			MessageBox(errorInfo, "����", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	}
	else
	{
		if (!file.Open((LPSTR)(LPCTSTR)fileName, CFile::modeCreate | CFile::modeWrite, &fileException))
		{
			//��ʾ�쳣��Ϣ
			CString errorInfo;
			errorInfo.Format("���ܴ����ļ�%s, ����%u\n", fileName, fileException.m_cause);
			MessageBox(errorInfo, "����", MB_OK | MB_ICONERROR);
			return FALSE;
		}
	
	}
	
	
// 	{
// 		//��ʾ�쳣��Ϣ
// 		CString errorInfo;
// 		errorInfo.Format("���ܴ��ļ�%s, ����%u\n", fileName, fileException.m_cause);
// 		MessageBox(errorInfo, "����", MB_OK | MB_ICONERROR);
// 		return FALSE;
// 	}
	file.SeekToEnd();
	return TRUE;
}


// __int64 CDb004Dlg::Str2Int64(char* str)
// {
// 	__int64 tmp;
// 	if(strstr(str,"0x") || strstr(str,"0X"))
// 	{
// 		str += 2;
// 		__int64 tmp = 0;
// 		int len = strlen(str);
// 		for(int i = 0;i < len ;i++)
// 		{
// 			int nDecNum;
// 			switch(str[i])
// 			{
// 			case 'a':
// 			case 'A':
// 				nDecNum = 10;
// 				break;
// 			case 'b':
// 			case 'B':
// 				nDecNum = 11;
// 				break;
// 			case 'c':
// 			case 'C':
// 				nDecNum = 12;
// 				break;
// 			case 'd':
// 			case 'D':
// 				nDecNum = 13;
// 				break;
// 			case 'e':
// 			case 'E':
// 				nDecNum = 14;
// 				break;
// 			case 'f':
// 			case 'F':
// 				nDecNum = 15;
// 				break;
// 			case '0':
// 			case '1':
// 			case '2':
// 			case '3':
// 			case '4':
// 			case '5':
// 			case '6':
// 			case '7':
// 			case '8':
// 			case '9':
// 				nDecNum = str[i] - '0';
// 				break;
// 			default:
// 				return 0;
// 
// 			}
// 			tmp += nDecNum*pow(16,len-i -1);
// 		}
// 		return tmp;
// 	}
// 	else
// 	{
// 		return _atoi64(str);
// 	}
// }



CString CDb004Dlg::EMh2d(char *strh)
{
	//int h,a,b,c,d;
	__int64  h,a,b,c,d;
	CString y;
	//sscanf(strh,"%x",&h);
	//sscanf("FF","%Lx",&h);
	//h = strtol(strh,NULL, 16);
//h = strtol("0xFF",NULL, 16);
	//h=4294967295;
	//h=Str2Int64("FFFFFFFF");
	//h=StrToInt64("1234");
	sscanf(strh,"%I64x",&h);
	//sscanf("FFFFFFFF","%I64x",&h);
	a=h%65536;
	b=h/65536%256;
	c=b*100000;
	d=a+c;
	//d=99999999;
	y.Format("%d",d);
	return y;
}


BOOL CDb004Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
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
	oraflag=FALSE;
	sqlflag=FALSE;
	fileflag=FALSE;
	if(ConnectDb(m_oraConnection,"FILE NAME=udl/ora.udl")==FALSE){	CDialog::OnClose();}	
	oraflag=TRUE;
	if(ConnectDb(m_sqlConnection,"FILE NAME=udl/sql.udl")==FALSE) {	CDialog::OnClose();}
	sqlflag=TRUE;
	if(Openfile(file)==FALSE) {	CDialog::OnClose();}
	fileflag=TRUE;
//	CString y;
	//y=EMh2d("2664A76E");
//	y=EMh2d("FFFFFFF8");
// 	// file.SeekToEnd();
// // 	WriteLogint(11117);
// // 	WriteLogint(22227);
// // 	WriteLogint(33337);
// // 	WriteLogstr("abcde");
// 	CString c;
// 	c="xxxxxx";
// 	WriteLogcstr(c);
// 	CString t;
// 	t=GetTime();
//	WriteLogcstr(GetTime());
	SetTimer(10,5000,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

CString CDb004Dlg::GetTime()
{
	CTime time = CTime::GetCurrentTime();
	CString str;
	str.Format( "[%4d-%02d-%02d %02d:%02d:%02d] ", 
		time.GetYear(), time.GetMonth(), time.GetDay(),
		time.GetHour(), time.GetMinute(), time.GetSecond());
	return str;
}


void CDb004Dlg::WriteLogcstr(CString str)
{
	file.Write((void*)(LPSTR)(LPCTSTR)(str),str.GetLength());
}



void CDb004Dlg::WriteLogstr(char* s)
{
	file.Write((void*)(s),strlen(s));
}


void CDb004Dlg::WriteLogint(int i)
{
	CString   str; 
	str.Format( "%d ",i); 
	file.Write((void*)(LPSTR)(LPCTSTR)(str),str.GetLength());
}


void CDb004Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDb004Dlg::OnPaint() 
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
HCURSOR CDb004Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//void CDb004Dlg::OnButtonAdd() 
//{
//	// TODO: Add your control notification handler code here
//	m_bAdd = TRUE;
//	EnableInput(TRUE);
//}

//void CDb004Dlg::OnButtonSave() 
//{
//	// TODO: Add your control notification handler code here
//	UpdateData(TRUE);
//	if(m_strId.IsEmpty())
//	{
//		AfxMessageBox(_T("ѧ��ѧ�Ų���Ϊ��."));
//		return;
//	}
//	if(m_strName.IsEmpty())
//	{
//		AfxMessageBox(_T("ѧ����������Ϊ��."));
//		return;
//	}
//	CString strSql;
//	strSql.Format(_T("Insert into StudentInfo values('%s','%s',%d)"), m_strId, m_strName, m_nScore);
//	try
//	{
//		m_pConnection->Execute(_bstr_t(strSql), 0, adCmdText);
//	}
//	catch(_com_error e)
//	{
//		AfxMessageBox(_T("���Ӽ�¼ʧ��!"));
//	}
//	AfxMessageBox(_T("���Ӽ�¼�ɹ�!"));
//	FreshList();
//
//	m_bAdd = FALSE;
//	EnableInput(FALSE);
//}

//void CDb004Dlg::OnButtonCancel() 
//{
//	// TODO: Add your control notification handler code here
//	m_bAdd = FALSE;
//	EnableInput(FALSE);
//}

void CDb004Dlg::EnableInput(BOOL bEnable)
{
	CEdit *pEdit;
	CButton *pButton;

	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_ID);
	pEdit->SetReadOnly(!bEnable);
	
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	pEdit->SetReadOnly(!bEnable);
	
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_SCORE);
	pEdit->SetReadOnly(!bEnable);
	
	pButton =(CButton*)GetDlgItem(IDC_BUTTON_ADD);
	pButton->EnableWindow(!bEnable);

	pButton =(CButton*)GetDlgItem(IDC_BUTTON_SAVE);
	pButton->EnableWindow(bEnable);

	pButton =(CButton*)GetDlgItem(IDC_BUTTON_CANCEL);
	pButton->EnableWindow(bEnable);
}








bool CDb004Dlg::SearchSqlGroup(char* DEPTNAME)
{
	try
	{
		_RecordsetPtr rssql;
		CString strsql;
		bool flag;
		rssql.CreateInstance(__uuidof(Recordset));
		strsql.Format(_T("select * from t_b_Group where f_GroupName LIKE \'%%%s%%\'"),DEPTNAME);
		rssql->Open(_bstr_t(strsql), (IDispatch*)m_sqlConnection,\
			adOpenDynamic,adLockOptimistic,adCmdText);

		if(!rssql->adoEOF)
		{
			flag=true;
		}
		else
		{
			flag=false;
		}
		rssql->Close();
		return flag;
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("���Ų�����!"));
		return false;
	}
}


void CDb004Dlg::AddSqlGroup(char* f_GroupName)  // �����
{
	CString strsql;
	strsql.Format(_T("Insert into t_b_Group(f_GroupName) values('%s')"),f_GroupName);
	try
	{
		m_sqlConnection->Execute(_bstr_t(strsql), 0, adCmdText);
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("�����ʧ��!"));
	}
}


void CDb004Dlg::GetCollect(_RecordsetPtr& m_oraRecordset,CString& CARDNO,CString& CUSTNAME,CString& DEPTNAME,CString& NEW_CARDUPDTIME) 
{
	CString CARDPHYID;
	CARDPHYID=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("CARDPHYID"));
	CARDNO=EMh2d((LPSTR)(LPCTSTR)CARDPHYID);
	CUSTNAME=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("CUSTNAME"));
	_variant_t var=m_oraRecordset->GetCollect("DEPTNAME");
	if (var.vt!=VT_NULL)
		DEPTNAME=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("DEPTNAME"));
	else
		DEPTNAME="NULL";
	NEW_CARDUPDTIME=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("CARDUPDTIME"));
}

void CDb004Dlg::AddUser()  // ��Ա���
{
	try
	{
		_RecordsetPtr m_oraRecordset;
		m_oraRecordset.CreateInstance(__uuidof(Recordset));
		CString CARDNO,CUSTNAME,DEPTNAME;
		_CommandPtr m_pCommand;
		CString strora;
		CString OLD_CARDUPDTIME,NEW_CARDUPDTIME;
		::GetPrivateProfileString("V_CUSTCARDINFO", "ADD_CARDUPDTIME", NULL ,OLD_CARDUPDTIME.GetBuffer(40), 40, "udl\\ora.ini");
//strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =1 AND ltrim(rtrim(CARDPHYID))<> ' ' and ltrim(rtrim(CUSTNAME))<> ' ' and ltrim(rtrim(DEPTNAME))<> ' ' and ltrim(rtrim(CARDUPDTIME)) <> ' ' order by CARDUPDTIME"),OLD_CARDUPDTIME);		
//strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =1 order by CARDUPDTIME"),OLD_CARDUPDTIME);				
//	strora.Format(_T("select CARDPHYID,CUSTNAME,DEPTNAME,CARDUPDTIME from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =1 order by CARDUPDTIME"),OLD_CARDUPDTIME);				
	strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =1 order by CARDUPDTIME"),OLD_CARDUPDTIME);
		//strora.Format(_T("select * from V_CUSTCARDINFO"));		
		NEW_CARDUPDTIME=OLD_CARDUPDTIME;
		m_oraRecordset->Open(_bstr_t(strora), (IDispatch*)m_oraConnection,\
			adOpenDynamic,adLockOptimistic,adCmdText);
		BOOL z;
		z=m_oraRecordset->adoEOF;
		while(!m_oraRecordset->adoEOF)
		{	
			GetCollect(m_oraRecordset,CARDNO,CUSTNAME,DEPTNAME,NEW_CARDUPDTIME); 
			if(!SearchSqlGroup((LPSTR)(LPCTSTR)DEPTNAME))
			{
				AddSqlGroup((LPSTR)(LPCTSTR)DEPTNAME);
			}
			int ret;
			ret=sp_wg_NewConsumer(m_pCommand,m_sqlConnection,(LPSTR)(LPCTSTR)CARDNO,(LPSTR)(LPCTSTR)CUSTNAME,(LPSTR)(LPCTSTR)DEPTNAME);
			CString cstr;
			cstr.Format("[��Ա���]sp_wg_NewConsumer %s,'%s','%s'          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,(LPSTR)(LPCTSTR)CUSTNAME,(LPCTSTR)DEPTNAME,ret);
			WriteLogcstr(GetTime()+cstr);
			m_oraRecordset->MoveNext();
		}
		m_oraRecordset->Close();
		::WritePrivateProfileString("V_CUSTCARDINFO", "ADD_CARDUPDTIME", NEW_CARDUPDTIME, "udl\\ora.ini");
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("��Ա���ʧ��!"));
	}
}



void CDb004Dlg::FreshList()
{
	
//	AddUser();
	//AddUser();
	//bool x;
	//x=SearchSqlGroup("����");
	//x=SearchSqlGroup("����");
//	AddSqlGroup("����3");
//	ShowOraList();
//	ShowSqlList();
}










void CDb004Dlg::DelUser()  // ��Աɾ��
{
	try
	{
		_RecordsetPtr m_oraRecordset;
		m_oraRecordset.CreateInstance(__uuidof(Recordset));
		CString CARDPHYID,CUSTNAME,DEPTNAME;
		_CommandPtr m_pCommand;
		CString strora;
		CString OLD_CARDUPDTIME,NEW_CARDUPDTIME;
		CString CARDNO;
		::GetPrivateProfileString("V_CUSTCARDINFO", "DEL_CARDUPDTIME", NULL ,OLD_CARDUPDTIME.GetBuffer(40), 40, "udl\\ora.ini");
		NEW_CARDUPDTIME=OLD_CARDUPDTIME;
		//strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS <>1 order by CARDUPDTIME"),OLD_CARDUPDTIME);
		//strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =2 order by CARDUPDTIME"),OLD_CARDUPDTIME);
//strora.Format(_T("select * from V_CUSTCARDINFO D where CARDSTATUS =2 and CARDUPDTIME>'%s' and CARDUPDTIME>(select max(A.CARDUPDTIME) from V_CUSTCARDINFO A where D.cardphyid=A.cardphyid) order by CARDUPDTIME"),OLD_CARDUPDTIME);		
strora.Format(_T("select * from V_CUSTCARDINFO D where CARDSTATUS =2 and CARDUPDTIME>'%s' and CARDUPDTIME>(select max(A.CARDUPDTIME) from V_CUSTCARDINFO A where D.cardphyid=A.cardphyid and A.Cardstatus=1) order by CARDUPDTIME"),OLD_CARDUPDTIME);				
		m_oraRecordset->Open(_bstr_t(strora), (IDispatch*)m_oraConnection,\
			adOpenDynamic,adLockOptimistic,adCmdText);
		while(!m_oraRecordset->adoEOF)
		{	
			GetCollect(m_oraRecordset,CARDNO,CUSTNAME,DEPTNAME,NEW_CARDUPDTIME); 
			int ret;
			ret=sp_wg_DeleteConsumer(m_pCommand,m_sqlConnection,(LPSTR)(LPCTSTR)CARDNO);
			CString cstr;
			//cstr.Format("[��Աɾ��]sp_wg_DeleteConsumer %s          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,ret);
			cstr.Format("[��Աɾ��]sp_wg_DeleteConsumer %s,'%s','%s'          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,(LPSTR)(LPCTSTR)CUSTNAME,(LPCTSTR)DEPTNAME,ret);
			WriteLogcstr(GetTime()+cstr);
			
			
			
			
	
			
			
			
			
			m_oraRecordset->MoveNext();
		}
		m_oraRecordset->Close();
		::WritePrivateProfileString("V_CUSTCARDINFO", "DEL_CARDUPDTIME", NEW_CARDUPDTIME, "udl\\ora.ini");
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("��Աɾ��ʧ��!"));
	}
}




void CDb004Dlg::RegisterLostCard()  // 	У԰����ʧ
{
	try
	{
		_RecordsetPtr m_oraRecordset;
		m_oraRecordset.CreateInstance(__uuidof(Recordset));

		CString CARDPHYID,CUSTNAME,DEPTNAME;
		CString CARDNO;
		_CommandPtr m_pCommand;
		CString strora;
		CString OLD_CARDUPDTIME,NEW_CARDUPDTIME;
		
		::GetPrivateProfileString("V_CUSTCARDINFO", "RegL_CARDUPDTIME", NULL ,OLD_CARDUPDTIME.GetBuffer(40), 40, "udl\\ora.ini");
		NEW_CARDUPDTIME=OLD_CARDUPDTIME;
		
		strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =3 order by CARDUPDTIME"),OLD_CARDUPDTIME);
		m_oraRecordset->Open(_bstr_t(strora), (IDispatch*)m_oraConnection,\
			adOpenDynamic,adLockOptimistic,adCmdText);
		
		while(!m_oraRecordset->adoEOF)
		{	
			GetCollect(m_oraRecordset,CARDNO,CUSTNAME,DEPTNAME,NEW_CARDUPDTIME); 
			int ret;
			ret=sp_wg_RegisterLostCardWithoutNewCard(m_pCommand,m_sqlConnection,(LPSTR)(LPCTSTR)CARDNO);
			CString cstr;
			//cstr.Format("[У԰����ʧ]sp_wg_RegisterLostCardWithoutNewCard %s          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,ret);
			cstr.Format("[У԰����ʧ]sp_wg_RegisterLostCardWithoutNewCard %s,'%s','%s'          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,(LPSTR)(LPCTSTR)CUSTNAME,(LPCTSTR)DEPTNAME,ret);
			WriteLogcstr(GetTime()+cstr);
			
			
			m_oraRecordset->MoveNext();
		}
		m_oraRecordset->Close();
		::WritePrivateProfileString("V_CUSTCARDINFO", "RegL_CARDUPDTIME", NEW_CARDUPDTIME, "udl\\ora.ini");
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("У԰����ʧ��!"));
	}
}


//void CDb004Dlg::OnBnClickedButton3()
//{
//	RegisterLostCard();
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CDb004Dlg::ReleaseLostCard()  // У԰�������ʧ
{
	try
	{
		_RecordsetPtr m_oraRecordset;
		m_oraRecordset.CreateInstance(__uuidof(Recordset));
		CString CARDPHYID,CUSTNAME,DEPTNAME;
		_CommandPtr m_pCommand;
		CString strora;
		CString OLD_CARDUPDTIME,NEW_CARDUPDTIME;
		CString CARDNO;
		::GetPrivateProfileString("V_CUSTCARDINFO", "RelL_CARDUPDTIME", NULL ,OLD_CARDUPDTIME.GetBuffer(40), 40, "udl\\ora.ini");
		NEW_CARDUPDTIME=OLD_CARDUPDTIME;
		strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =1 order by CARDUPDTIME"),OLD_CARDUPDTIME);
		m_oraRecordset->Open(_bstr_t(strora), (IDispatch*)m_oraConnection,\
			adOpenDynamic,adLockOptimistic,adCmdText);	
		while(!m_oraRecordset->adoEOF)
		{	

			GetCollect(m_oraRecordset,CARDNO,CUSTNAME,DEPTNAME,NEW_CARDUPDTIME); 
			int ret;
			ret=sp_wg_ReleaseLostCard(m_pCommand,m_sqlConnection,(LPSTR)(LPCTSTR)CARDNO);
			CString cstr;
			//cstr.Format("[У԰�������ʧ]sp_wg_ReleaseLostCard %s          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,ret);
			cstr.Format("[У԰�������ʧ]sp_wg_ReleaseLostCard %s,'%s','%s'          ������=%d\r\n",(LPSTR)(LPCTSTR)CARDNO,(LPSTR)(LPCTSTR)CUSTNAME,(LPCTSTR)DEPTNAME,ret);
			WriteLogcstr(GetTime()+cstr);
			
			m_oraRecordset->MoveNext();
		}
		m_oraRecordset->Close();
		::WritePrivateProfileString("V_CUSTCARDINFO", "RelL_CARDUPDTIME", NEW_CARDUPDTIME, "udl\\ora.ini");
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("У԰�������ʧʧ��!"));
	}
}


//void CDb004Dlg::OnBnClickedButton4()
//{
//	
//	ReleaseLostCard();
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CDb004Dlg::BbCard()  // У԰������
{
	try
	{
		_RecordsetPtr m_oraRecordset;
		m_oraRecordset.CreateInstance(__uuidof(Recordset));
		CString strora;
		CString OLD_CARDUPDTIME,NEW_CARDUPDTIME;
		::GetPrivateProfileString("V_CUSTCARDINFO", "RelL_CARDUPDTIME", NULL ,OLD_CARDUPDTIME.GetBuffer(40), 40, "udl\\ora.ini");
		NEW_CARDUPDTIME=OLD_CARDUPDTIME;
		
		//strora.Format(_T("select * from V_CUSTCARDINFO where CARDUPDTIME>'%s' and CARDSTATUS =2 order by CARDUPDTIME"),OLD_CARDUPDTIME);
// 		strora.Format(_T("select * from ykt_cur.t_card,v_custcardinfo where v_custcardinfo.CARDSTATUS<>1 \
// 						 and ykt_cur.t_card.status=1 and ykt_cur.t_card.CARDPHYID=v_custcardinfo.CARDPHYID \
// 						 and v_custcardinfo.CARDUPDTIME>'%s' order by v_custcardinfo.cardupdtime"),OLD_CARDUPDTIME);
	

		strora.Format(_T("select t.CARDPHYID,t.status,v.CARDPHYID,v.cardstatus from t_card t,v_custcardinfo v where t.CARDPHYID=v.CARDPHYID"));
		m_oraRecordset->Open(_bstr_t(strora), (IDispatch*)m_oraConnection,\
		 			adOpenDynamic,adLockOptimistic,adCmdText);
		
// 		m_oraRecordset->Open(_T("select * from V_CUSTCARDINFO where CARDSTATUS=2"), (IDispatch*)m_oraConnection,\
// 			adOpenDynamic,adLockOptimistic,adCmdText);
		CString CARDPHYID,CUSTNAME,DEPTNAME;
		_CommandPtr m_pCommand;
		while(!m_oraRecordset->adoEOF)
		{	
			CARDPHYID=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("CARDPHYID"));
			CUSTNAME=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("CUSTNAME"));
			DEPTNAME=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("DEPTNAME"));
			NEW_CARDUPDTIME=(LPCTSTR)_bstr_t(m_oraRecordset->GetCollect("CARDUPDTIME"));
			//sp_wg_ReleaseLostCard(m_pCommand,m_sqlConnection,(LPSTR)(LPCTSTR)CARDPHYID);
			//sp_wg_RegisterLostCard 91234,91235
			//sp_wg_RegisterLostCard((m_pCommand,m_sqlConnection,(LPSTR)(LPCTSTR)CARDPHYID);
			
			m_oraRecordset->MoveNext();
		}
		m_oraRecordset->Close();
	}
	catch(_com_error e)
	{
		AfxMessageBox(_T("У԰�������ʧ!"));
	}
}

//void CDb004Dlg::OnBnClickedButton5()
//{
//		BbCard();
//		
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}

void CDb004Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(10);
	AddUser();	
   	DelUser();
   	RegisterLostCard();
   	ReleaseLostCard();
	CDialog::OnTimer(nIDEvent);
// 	int i;
// 	CString str;
// 	for(i=1;i<5;i++)
// 	{
// 		str.Format(_T("%d"),i);
// 		AfxMessageBox(str);
// 	}
	SetTimer(10,5000,NULL);
}

void CDb004Dlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

// 	m_pConnection->Close();
// 	m_pConnection.Release();a
// 	CoUninitialize();
	if(oraflag==TRUE)
	{
		m_oraConnection->Close();
		m_oraConnection.Release();
		CoUninitialize();
	}
	if(sqlflag==TRUE)
	{
		m_sqlConnection->Close();
		m_sqlConnection.Release();
		CoUninitialize();
	}
	if(fileflag==TRUE)
	{	
		file.Close();
	}
	CDialog::OnClose();
}
