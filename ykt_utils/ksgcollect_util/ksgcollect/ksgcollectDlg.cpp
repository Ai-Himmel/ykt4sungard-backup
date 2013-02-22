// ksgcollectDlg.cpp : 实现文件
//
#include "stdafx.h"
#include "windows.h"
#include "ksgcollect.h"
#include "ksgcollectDlg.h"
#include ".\ksgcollectdlg.h"
#include "mfcutil.h"
#include "yktclt.h"
#include "parsedef.h"
#include "utils.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DRTP_NODE drtpNode;
char ChangeData[512];
char errTradeFile[MAX_PATH] = "";

IMPLEMENT_DYNAMIC(CParseDataThread, CWinThread) 

BEGIN_MESSAGE_MAP(CParseDataThread, CWinThread) 
	//{{AFX_MSG_MAP(CGDIThread) 
	// NOTE - the ClassWizard will add and remove mapping macros here. 
	//}}AFX_MSG_MAP 
END_MESSAGE_MAP() 


CParseDataThread::CParseDataThread(CDataFileFinder *finder):
CWinThread(),finder_(finder),m_isterminate(TRUE)
{
	m_bAutoDelete = TRUE;
}

CParseDataThread::~CParseDataThread()
{
	Reset();
}

int CParseDataThread::ParseDataFile(const CString& data_file)
{
	int parser_idx = 0;
	int ret = 0;
	int iCount;
	my_string_t hdStr;
	TRADE_SERIAL trade_serial;
	char fileName[MAX_PATH];
	
	if(data_file.GetLength() <= 0)
		return -1;

	_tcscpy( fileName,data_file);
	FILE *fpParseFile = fopen(fileName,"rb");
	if(!fpParseFile)
		return -1;

	//记录入库失败流水
	FILE *fp = fopen(errTradeFile,"w+");  //记录失败的流水
	char *pHead = "流水号	卡号	时间	日期	设备号	入卡值	出卡值	交易额	交易次数	管理费	标志\n";
	fputs(pHead,fp);

	hdStr = alloc_mystring();

	int start = 0;
	do 
	{
		if(read_file_line(&hdStr,fpParseFile) != 0)  //文件结束或错误
		{
			ret = -1;
			goto L_RET;
		}
		start = trim_line(&hdStr);
	} while(hdStr.length == 0);
	
	for(parser_idx = 0;parser_idx < g_parser_count;++parser_idx)
	{		
		if(g_parser_ops[parser_idx].parse_head(hdStr.data + start) == 0)
			break;
	}
	if(parser_idx >= g_parser_count)   //不支持的文件格式
	{
		ret = -1;
		goto L_RET;
	}
	
	do  
	{
		//memset(hdStr.data,0,hdStr.length);
		hdStr.length = 0;
		ret = read_file_line(&hdStr,fpParseFile);
		//if (read_file_line(&hdStr,fpParseFile) != 0) //文件结束
		if(ret!=0)
		{
			ret = 0;
			goto L_RET;
		}
		if (hdStr.length == 0)	  //文件结束
			goto L_RET;			
		start = trim_line(&hdStr);
		memset(&trade_serial,0,sizeof trade_serial);
		if(g_parser_ops[parser_idx].parse_line(hdStr.data+start,trade_serial))
		{
			iCount = 3;
		}
		else
		{


			KS_YKT_Clt yktClt(drtpNode.drtp_ip_,drtpNode.drtp_port_,drtpNode.svr_main_func_);
			
			//送往后台处理
			yktClt.SetIntFieldByName("lvol4",trade_serial.serial_no);
			yktClt.SetIntFieldByName("lvol5",trade_serial.card_no);
			yktClt.SetStringFieldByName("spost_code",trade_serial.tx_date);
			yktClt.SetStringFieldByName("spost_code2",trade_serial.tx_time);
			yktClt.SetStringFieldByName("sdate1",trade_serial.device_id);
			yktClt.SetStringFieldByName("sphone3",trade_serial.device_id);
			yktClt.SetIntFieldByName("lvol9",trade_serial.in_balance);
			yktClt.SetIntFieldByName("lvol10",trade_serial.out_balance);
			yktClt.SetIntFieldByName("lvol8",trade_serial.trade_fee);
			yktClt.SetIntFieldByName("lvol7",trade_serial.trade_count);
			yktClt.SetIntFieldByName("lvol1",trade_serial.manage_fee);
			yktClt.SetIntFieldByName("lvol12",trade_serial.tx_mark);
			yktClt.SetStringFieldByName("sbank_code2","xxxx");  ///CRC校验
			yktClt.SetIntFieldByName("lcert_code",1);

			if(trade_serial.serial_type == 0)
				trade_serial.serial_type = 950031;
			iCount = 0;
			do   //失败重试3次
			{
				if(yktClt.SendRequest(trade_serial.serial_type,5000))
					break;
				//int ret_code = yktClt.GetReturnCode();
				//int err_code = yktClt.GetErrCode();
				iCount++;
			} while(iCount < 3);
		}
		if (iCount >= 3)  //此条记录失败，写入文件
		{
			char buf[512];
			sprintf(buf,"%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",trade_serial.serial_no,trade_serial.card_no,
				trade_serial.tx_date,trade_serial.tx_time,trade_serial.device_id,trade_serial.in_balance,
				trade_serial.out_balance,trade_serial.trade_fee,trade_serial.trade_count,trade_serial.manage_fee,trade_serial.tx_mark);
			fputs(buf,fp);
		}
		//yktClt.ResetHandler();
		
	} while(!IsTerminate());

	if(IsTerminate())  //中断
		ret = 1; 
	
L_RET:	fclose(fp);
	fclose(fpParseFile);
	free_mystring(&hdStr);
	return ret;
}

int CParseDataThread::Run()
{
	int has_file = 1;
	int ret;
	CString filePath;
	has_file = finder_->FetchDataFile(filePath);
	if (has_file == -1)
	{
		memset(ChangeData,0,sizeof(ChangeData));
		sprintf(ChangeData,"找不到指定文件");
		SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,0,(LPARAM)ChangeData);
		SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,1,1);   //不用打开入库失败文件
		goto L_RET;
	}
	//has_file = 1;  //测试用
	while(!has_file && !IsTerminate())
	{
		memset(ChangeData,0,sizeof(ChangeData));
		sprintf(ChangeData,"正解析文件[%s],请等待...",filePath);
		SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,0,(LPARAM)ChangeData);
		
		ret = ParseDataFile(filePath);
		if(ret==0)
		{
			memset(ChangeData,0,sizeof(ChangeData));
			sprintf(ChangeData,"文件[%s]解析完毕",filePath);
			SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,0,(LPARAM)ChangeData);
		}
		else if(ret ==1) //中断
		{
			memset(ChangeData,0,sizeof(ChangeData));
			sprintf(ChangeData,"文件[%s]被中断",filePath);
			SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,0,(LPARAM)ChangeData);
		}
		else
		{
			memset(ChangeData,0,sizeof(ChangeData));
			sprintf(ChangeData,"文件[%s]打开错误或格式不支持",filePath);
			SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,0,(LPARAM)ChangeData);
		}
		has_file = finder_->FetchDataFile(filePath);
	}

	SendMessage(m_pMainWnd->m_hWnd,WM_MYMESSAGE,1,0);
L_RET:	return CWinThread::Run();
	//ExitInstance();
}

BOOL CParseDataThread::InitInstance()
{
	return TRUE;
}

int CParseDataThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

void CParseDataThread::Reset()
{
	if(m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
		m_isterminate = TRUE;
	}
}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CksgcollectDlg 对话框



CksgcollectDlg::CksgcollectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CksgcollectDlg::IDD, pParent),parseDateThread_(&dateFileFinder_),pIniFile_(NULL)
{
	int len = GetModuleFileName(NULL, module_path, sizeof(module_path) - 1);
	char *pos = strrchr(module_path, '\\');
	len = pos - module_path;
	module_path[len] = '\0';
	
	sprintf(errTradeFile,"%s\\入库失败流水.txt",module_path);
	//sprintf(errTradeFile,"入库失败流水.txt");
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CksgcollectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CksgcollectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_SELFILE, OnBnClickedBtnSelfile)
	ON_BN_CLICKED(ID_RD_COLFILE, OnBnClickedRdColfile)
	ON_BN_CLICKED(ID_RD_COLDIR, OnBnClickedRdColdir)
	ON_BN_CLICKED(ID_BTN_SELDIR, OnBnClickedBtnSeldir)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_PARSE, OnBnClickedParse)
	ON_MESSAGE(WM_MYMESSAGE,OnMyMessage)
END_MESSAGE_MAP()


// CksgcollectDlg 消息处理程序

BOOL CksgcollectDlg::OnInitDialog()
{
	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// TODO: 在此添加额外的初始化代码
	
	SetDlgItemText(IDC_FILTER,"*.txt");
	//
	((CButton*)GetDlgItem(ID_RD_COLFILE))->SetCheck(TRUE);
	enable_group(1);
	// 初始化 bccclt
	KS_YKT_Clt::Initialize();

	char cpack_path[MAX_PATH];
	sprintf(cpack_path,"%s\\cpack.dat",module_path);
	KS_YKT_Clt::set_xpack_path(cpack_path);


	char iniFilePath[MAX_PATH];
	sprintf(iniFilePath,"%s\\config.ini",module_path);
	pIniFile_ = new CCIniFile(iniFilePath);
	
	drtpNode.drtp_ip_ = pIniFile_->ReadString("DRTP","DRTP_IP","").c_str();
	drtpNode.drtp_port_ = pIniFile_->ReadInteger("DRTP","DRTP_PORT",0);
	drtpNode.svr_main_func_ = pIniFile_->ReadInteger("DRTP","BCC_NO",0);
	
	pIniFile_->ReadSectionValues("DLLMAP",dllMap);
	if (initDLL())
	{
		AfxMessageBox("加载动态库失败，请检查配置文件[DLLMAP]项");
		delete pIniFile_;
		return FALSE;
	}
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CksgcollectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CksgcollectDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CksgcollectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CksgcollectDlg::OnBnClickedBtnSelfile()
{
	static char szFilter[] = "Text Files (*.txt)|*.txt|Data Files (*.dat)|*.dat|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);

	if(dlg.DoModal() == IDOK)
	{
		SetDlgItemText(ID_EDT_DATAFILE,dlg.GetPathName());
		UpdateData(TRUE);
	}
}

void CksgcollectDlg::enable_group(int idx)
{
	GetDlgItem(ID_EDT_DATAFILE)->EnableWindow((1==idx));
	GetDlgItem(ID_BTN_SELFILE)->EnableWindow((1==idx));
	GetDlgItem(ID_EDT_DATADIR)->EnableWindow((2==idx));
	GetDlgItem(ID_BTN_SELDIR)->EnableWindow((2==idx));
	GetDlgItem(IDC_FILTER)->EnableWindow((2==idx));
}

void CksgcollectDlg::OnBnClickedRdColfile()
{
	enable_group(1);
}

void CksgcollectDlg::OnBnClickedRdColdir()
{
	enable_group(2);
}

void CksgcollectDlg::OnBnClickedBtnSeldir()
{
	CDirDialog dlg;
	if(dlg.DoModal(this) == IDOK)
	{
		CString str = dlg.m_strPath;
		SetDlgItemText(ID_EDT_DATADIR,str);
	}
}

//////////////////////////////////////////////////////////////////////////
// CCriticalSectioinGuard
CCriticalSectioinGuard::CCriticalSectioinGuard(CRITICAL_SECTION &sect)
:critial_sect_(sect),locked_(0)
{
	if(TryEnterCriticalSection(&critial_sect_))
	{
		locked_ = 1;
	}
}
CCriticalSectioinGuard::~CCriticalSectioinGuard()
{
	if(locked_)
	{
		LeaveCriticalSection(&critial_sect_);
	}
}

int CCriticalSectioinGuard::is_locked() const
{
	return locked_;
}

// CDataFileFinder
CDataFileFinder::CDataFileFinder():file_handle_(INVALID_HANDLE_VALUE),find_flag_(0),bFile_(0)
{
	memset(&file_data_,0,sizeof file_data_);
	memset(&fetch_sect_,0,sizeof fetch_sect_);
	InitializeCriticalSection(&fetch_sect_);	
}

CDataFileFinder::~CDataFileFinder()
{
	DeleteCriticalSection(&fetch_sect_);
	clear_find_data();
}

int CDataFileFinder::FetchDataFile(CString &file_path)
{
	CCriticalSectioinGuard guard(fetch_sect_);
	if(!guard.is_locked())
		return -1;
	return find_next_file(file_path);
}

void CDataFileFinder::clear_find_data()
{
	file_path_ = "";
	find_flag_ = 0;
	bFile_ = 0;
	if(file_handle_ != INVALID_HANDLE_VALUE)
	{
		FindClose(file_handle_);
		file_handle_ = INVALID_HANDLE_VALUE;
		memset(&file_data_,0,sizeof file_data_);
		//file_path_ = "";
		//find_flag_ = 0;
		//bFile_ = 0;
	}
}

int CDataFileFinder::BeginFindFile(BOOL bFile,const CString &path,const CString &file_suffix)
{
	clear_find_data();
	file_path_ = path;
	file_suffix_ = file_suffix;
	bFile_ = bFile;
	if(!bFile_)
		file_path_ += "\\";
	return 0;
}

int CDataFileFinder::find_next_file(CString &file_path)
{
	if(!find_flag_)
	{
		find_flag_ = 1;
		if (bFile_)	//查找的是文件，直接返回
		{
			file_path = file_path_;
			return 0;
		}
		file_handle_ = FindFirstFileEx((LPCTSTR)(file_path_ + file_suffix_),FindExInfoStandard,
			&file_data_,FindExSearchNameMatch,NULL,0);
		if(file_handle_ == INVALID_HANDLE_VALUE)
			return -1;

		if (file_data_.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			//return find_next_file(file_path);
			return 1;   //不支持多级目录
		}
		
		file_path = file_data_.cFileName;
	
		if(!bFile_)
			file_path = file_path_ + file_path;
		
		return 0;
	}
	if (find_flag_ && bFile_)  //查找的是文件，只返回一次
		return 1;
	if(!FindNextFile(file_handle_, &file_data_))
	{
		if(GetLastError() == ERROR_NO_MORE_FILES)
			return 1;
		else
			return -1;
	}
	file_path = file_data_.cFileName;
	if(!bFile_)
		file_path = file_path_ + file_path;
	return 0;
}

void CksgcollectDlg::OnDestroy()
{
	
	//parseDateThread_.Reset();

	if (pIniFile_)
		delete pIniFile_;

	KS_YKT_Clt::Uninitialize();
	// TODO: Add your message handler code here
	CDialog::OnDestroy();
	//_CrtDumpMemoryLeaks(); 
}

static BOOL is_running = FALSE;
void CksgcollectDlg::OnBnClickedParse()
{
	// TODO: Add your control notification handler code here
	CString file_path;
	CString file_suffix;
	
	BOOL bFile = ((CButton *)GetDlgItem(ID_RD_COLFILE))->GetCheck();
	if (bFile)
		GetDlgItemText(ID_EDT_DATAFILE,file_path);
	else
	{
		GetDlgItemText(ID_EDT_DATADIR,file_path);
		GetDlgItemText(IDC_FILTER,file_suffix);
	}

	if(!is_running)
	{
		dateFileFinder_.BeginFindFile(bFile,file_path,file_suffix);

		if(!parseDateThread_.CreateThread(CREATE_SUSPENDED))
			AfxMessageBox("创建线程失败");
		else
		{
			CListBox *pList = (CListBox*)this->GetDlgItem(IDC_DISP);
			pList->ResetContent();

			parseDateThread_.m_isterminate = FALSE;
			parseDateThread_.ResumeThread();
			SetDlgItemText(IDC_PARSE,"停止解析");
			//SetDlgItemText(IDC_DISP,"");
			is_running = TRUE;
		}
	}
	else
	{
		parseDateThread_.Reset();
		SetDlgItemText(IDC_PARSE,"开始解析");
		is_running = FALSE;
		//SetDlgItemText(IDC_DISP,"");
	}	
}

long CksgcollectDlg::OnMyMessage(WPARAM w,LPARAM l)
{
	if (w == 0)
	{
		//char *pstr = (char*)l;
		//SetDlgItemText(IDC_DISP,pstr);
		CListBox *pList = (CListBox*)this->GetDlgItem(IDC_DISP);
		pList->AddString((char*)l);
	}
	if (w == 1)
	{
		if(l != 1)
			ShellExecute(NULL,"open",errTradeFile,NULL,NULL,SW_SHOW);
		parseDateThread_.Reset();
		SetDlgItemText(IDC_PARSE,"开始解析");
		is_running = FALSE;
	}

	return 0;
}

