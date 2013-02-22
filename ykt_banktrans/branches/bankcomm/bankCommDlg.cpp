// bankCommDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "bankComm.h"
#include "bankCommDlg.h"
#include ".\bankcommdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CbankCommDlg 对话框



CbankCommDlg::CbankCommDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CbankCommDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_ComPortVec.clear();
	int len = GetModuleFileName(NULL, module_path, sizeof(module_path) - 1);
	char *pos = strrchr(module_path, '\\');
	len = pos - module_path + 1;
	module_path[len] = '\0';
}

void CbankCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CbankCommDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_COMPROPERTY, OnBnClickedComproperty)
	ON_BN_CLICKED(IDC_ADDCOM, OnBnClickedAddcom)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SHOWLOG, OnBnClickedShowlog)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CbankCommDlg 消息处理程序

BOOL CbankCommDlg::OnInitDialog()
{
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

	//初始化配置文件
	char config_path[MAX_PATH]="";
	sprintf(config_path,"%sconfig\\ComPort.ini",module_path);
	IniFile = new CCIniFile(config_path);

	IniFile->ReadSectionValues("PosMap",deviceIDMap);
	std::map<std::string,std::string> values;
	std::map<std::string,std::string>::iterator mapIter;
	IniFile->ReadSectionValues("ComOpen",values);

	int nPort = 1;
	CListBox*pList =(CListBox*)this->GetDlgItem(IDC_LIST1);

	int baudRate = IniFile->ReadInteger("ComProperty","BaudRate",0);
	int byteSize = IniFile->ReadInteger("ComProperty","ByteSize",0);	
LsComm::CComPort::StopBits stopBits =(LsComm::CComPort::StopBits)IniFile->ReadInteger("ComProperty","StopBits",0);
	LsComm::CComPort::Parity parity = (LsComm::CComPort::Parity)IniFile->ReadInteger("ComProperty","Parity",0);
	
	CString sMsg;
	LsComm::CComPort *pComPort = NULL;
	for (mapIter = values.begin();mapIter != values.end();mapIter++)
	{
		nPort = (atoi)(mapIter->second.c_str());
		if(nPort <= 0)
			continue;
		
		pComPort = new LsComm::CComPort();
		ASSERT(pComPort);
		if (pComPort == NULL)
		{
			AfxMessageBox("内存不足!!!");
			///释放已分配的内存？

			return false;
		}

		pComPort->SetModulePath(module_path);

		if(!pComPort->Open(nPort,baudRate))
		//if(!pComPort->Open(nPort,baudRate,parity,byteSize,stopBits,LsComm::CComPort::NoFlowControl))
		{					
			delete pComPort;
			sMsg.Format("提示:不能打开串口:com%d!",nPort);			
			//AfxMessageBox(sMsg,MB_ICONINFORMATION | MB_OK);
		} 
		else
		{
			sMsg.Format("串口:com%d正在侦听...",nPort);
			pComPort->SetReceiveFunc((FOnReceiveData)OnReceiveData,this);
			pComPort->SetPrintFunc((FOnReceiveData)OnPrintData,this);
			pComPort->m_dataParse.SetDeviceIDMap(&deviceIDMap);
			m_ComPortVec.push_back(pComPort);
		}		
		pList->AddString(sMsg);		
	}

	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CbankCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CbankCommDlg::OnPaint() 
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
HCURSOR CbankCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CbankCommDlg::OnBnClickedComproperty()
{
	// TODO: Add your control notification handler code here
	CComPropertyDlg dlg;

	DCB dcb;
	if(m_ComPortVec.size() <= 0)
		return;

	m_ComPortVec[0]->GetSerialPort()->GetState(dcb);
	dlg.SetDCB(&dcb);

	if(dlg.DoModal() == IDOK)
	{
		std::vector<LsComm::CComPort *>::iterator iterVec;
		//配置串口属性
		for (iterVec = m_ComPortVec.begin();iterVec != m_ComPortVec.end();iterVec++)
		{
			(*iterVec)->GetSerialPort()->SetState(dcb);
		}

		//记录到配置文件中
		char value[8] = "";
		sprintf(value,"%d",dcb.BaudRate);
		IniFile->WriteString("ComProperty","BaudRate",value);
		memset(value,0,8);
		sprintf(value,"%d",dcb.ByteSize);
		IniFile->WriteString("ComProperty","ByteSize",value);
		memset(value,0,8);
		sprintf(value,"%d",dcb.StopBits);
		IniFile->WriteString("ComProperty","StopBits",value);
		memset(value,0,8);
		sprintf(value,"%d",dcb.Parity);
		IniFile->WriteString("ComProperty","Parity",value);
	}

}

void CbankCommDlg::OnBnClickedAddcom()
{
	// TODO: Add your control notification handler code here
	CAddComPortDlg addComPortDlg;
	if (addComPortDlg.DoModal() == IDOK)
	{
		CString sMsg;
		CListBox*pList =(CListBox*)this->GetDlgItem(IDC_LIST1);
		BOOL bAdd = addComPortDlg.bAdd;
		int comPort = addComPortDlg.addComPort;
		if(comPort <= 0)
			return;

		std::vector<LsComm::CComPort *>::iterator iterVec;
		LsComm::CComPort *pComPort = NULL;
		for (iterVec = m_ComPortVec.begin();iterVec != m_ComPortVec.end();iterVec++)
		{
			if((*iterVec)->GetCurPortNum() == comPort)
				break;
		}
		if (iterVec == m_ComPortVec.end())  //串口未打开
		{			
			if(!bAdd)    ///删除串口
			{
				sMsg.Format("串口:com%d未打开!",comPort);
				pList->AddString(sMsg);
				return;
			}			
			
			int baudRate = IniFile->ReadInteger("ComProperty","BaudRate",0);
			int byteSize = IniFile->ReadInteger("ComProperty","ByteSize",0);
			LsComm::CComPort::StopBits stopBits =(LsComm::CComPort::StopBits)IniFile->ReadInteger("ComProperty","StopBits",0);
			LsComm::CComPort::Parity parity = (LsComm::CComPort::Parity)IniFile->ReadInteger("ComProperty","Parity",0);
			
			pComPort = new LsComm::CComPort();
			ASSERT(pComPort);
			if (pComPort == NULL)
				return;

			pComPort->SetModulePath(module_path);
			if(!pComPort->Open(comPort,baudRate))
			//if(!pComPort->Open(comPort,baudRate,parity,byteSize,stopBits))   //打开串口失败
			{			
				delete pComPort;
				sMsg.Format("提示:不能打开串口:com%d!",comPort);
				pList->AddString(sMsg);
			} 
			else   //记录日志
			{
				char indent[8],value[4];
				memset(indent,0,8);
				memset(value,0,4);
				sprintf(indent,"COM%d",comPort);
				sprintf(value,"%d",comPort);
				sMsg.Format("串口:com%d正在侦听...",comPort);
				pList->AddString(sMsg);
				IniFile->WriteString("ComOpen",indent,value);
				pComPort->SetReceiveFunc((FOnReceiveData)OnReceiveData,this);
				pComPort->SetPrintFunc((FOnReceiveData)OnPrintData,this);
				pComPort->m_dataParse.SetDeviceIDMap(&deviceIDMap);
				m_ComPortVec.push_back(pComPort);
			}
		}
		else    //串口已打开
		{			
			if (bAdd)  ///增加串口
			{				
				sMsg.Format("串口:com%d已经打开!",comPort);
				pList->AddString(sMsg);
				return;
			}
			char indent[8],value[4];
			memset(indent,0,8);
			memset(value,0,4);
			sprintf(indent,"COM%d",comPort);
			sprintf(value,"%d",0);
			sMsg.Format("已删除串口:com%d",comPort);
			pList->AddString(sMsg);
			IniFile->WriteString("ComOpen",indent,value);

			m_ComPortVec.erase(iterVec);
			(*iterVec)->Close();
			delete *iterVec;			
		}
	}
}

void CbankCommDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	std::vector<LsComm::CComPort *>::iterator iterVec;
	for (iterVec = m_ComPortVec.begin();iterVec != m_ComPortVec.end();iterVec++)
	{
		(*iterVec)->Close();
		delete *iterVec;
	}
	m_ComPortVec.clear();
	delete IniFile;
	
	::Shell_NotifyIcon(NIM_DELETE,&m_tnid); 
	CDialog::OnClose();
}

void OnReceiveData(LPVOID pSender,void* pBuf,DWORD InBufferCount)
{
	CString c;
	byte a[256]="\0";
	char b[4]="\0";
	memcpy(a,pBuf,InBufferCount);
	for(int i=0;i<(int)InBufferCount;i++)
	{
		::sprintf(b,"%2.2X",a[i]);
		c+=b;
		c+=" ";
	}

	CbankCommDlg* pDlg = (CbankCommDlg*) pSender;
	CListBox*pList =(CListBox*)pDlg->GetDlgItem(IDC_LIST2);

	if(pList->GetCount() > 20)
		pList->ResetContent();

	c="接收(Recv):"+c;
	pList->AddString(c);
}

void OnPrintData(LPVOID pSender,void* pBuf,DWORD InBufferCount)
{
	CString c;
	byte a[256]="\0";
	char b[4]="\0";
	memcpy(a,pBuf,InBufferCount);
	for(int i=0;i<(int)InBufferCount;i++)
	{
		::sprintf(b,"%2.2X",a[i]);
		c+=b;
		c+=" ";
	}
	CbankCommDlg* pDlg = (CbankCommDlg*) pSender;
	CListBox*pList =(CListBox*)pDlg->GetDlgItem(IDC_LIST2);
	c="发送(Send):"+c;
	pList->AddString(c);
}
void CbankCommDlg::OnBnClickedShowlog()
{
	// TODO: Add your control notification handler code here

	if(m_ComPortVec.size() <= 0)
		return;

	char logName[MAX_PATH];
	char currTime[15];
	char currDate[9];
	m_ComPortVec[0]->m_dataParse.m_logWriter.get_current_time(currTime);
	memcpy(currDate,currTime,sizeof(currDate));
	currDate[8] = 0;
	sprintf(logName,"%slogs\\%s\\com.log",module_path,currDate);
	ShellExecute(NULL,"open",logName,NULL,NULL,SW_SHOW);
	//system("NOTEPAD.exe D:\\programTest\\bankComm\\Debug\\logs\\20080514\\com.log"); //NOTEPAD
}

int CbankCommDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_tnid.cbSize=sizeof(NOTIFYICONDATA); 
	m_tnid.hWnd=this->m_hWnd; 
	m_tnid.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP; 
	m_tnid.uCallbackMessage=MYWM_NOTIFYICON; 
	CString szToolTip; 
	szToolTip=_T("圈存接口"); 
	_tcscpy(m_tnid.szTip, szToolTip); 
	m_tnid.uID=IDR_MAINFRAME; 
	m_tnid.hIcon = m_hIcon;
	::Shell_NotifyIcon(NIM_ADD,&m_tnid); 
	return 0;
}

LRESULT CbankCommDlg::WindowProc(UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message){
		case MYWM_NOTIFYICON:
			if(lParam == WM_LBUTTONDBLCLK || lParam == WM_RBUTTONDOWN)
			{
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
			}
		case WM_SYSCOMMAND:
			if(wParam == SC_MINIMIZE)
			{
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);
				return 0;
			}
			break;
	}
	return CDialog::WindowProc(message,wParam,lParam);
}
