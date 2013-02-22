// lisencemanagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "lisencemanager.h"
#include "lisencemanagerDlg.h"
#include "CIniFile.h"
#include ".\lisencemanagerdlg.h"
#include "CardFieldDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] =
{
    ID_SEPARATOR,                   // status line indicator
    ID_INDICATOR_CAPS,              //CAP lock indicator.
    ID_INDICATOR_NUM,               //NUM lock indicator.
    ID_INDICATOR_SCRL,              //SCRL lock indicator.
};

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


// ClisencemanagerDlg 对话框



ClisencemanagerDlg::ClisencemanagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(ClisencemanagerDlg::IDD, pParent),m_private_keyfile(_T("")),
	m_public_keyfile(_T("")),m_lisence_file(_T("")),m_select_item_idx(-1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ClisencemanagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_PARAMS, m_list);
}

BEGIN_MESSAGE_MAP(ClisencemanagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_SELPRIVKEY, OnBnClickedBtnSelprivkey)
	ON_BN_CLICKED(ID_BTN_SELPUBKEY, OnBnClickedBtnSelpubkey)
	ON_BN_CLICKED(ID_BTN_LISENCE, OnBnClickedBtnLisence)
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_BTN_LOADPRIVKEY, OnBnClickedBtnLoadprivkey)
	ON_BN_CLICKED(ID_BTN_LOADPUBKEY, OnBnClickedBtnLoadpubkey)
	ON_BN_CLICKED(ID_BTN_LOADLISENCE, OnBnClickedBtnLoadlisence)
	ON_BN_CLICKED(ID_BTN_GENKEY, OnBnClickedBtnGenkey)
	ON_BN_CLICKED(ID_BTN_SAVELICENSE, OnBnClickedBtnSavelicense)
	ON_NOTIFY(NM_RCLICK, IDC_LST_PARAMS, OnNMRclickLstParams)
	ON_COMMAND(ID_MENU_ADD, OnMenuAdd)
	ON_COMMAND(ID_MENU_DEL, OnMenuDel)
	ON_NOTIFY(NM_CLICK, IDC_LST_PARAMS, OnNMClickLstParams)
	ON_NOTIFY(NM_DBLCLK, IDC_LST_PARAMS, OnNMDblclkLstParams)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_PARAMS, OnLvnItemchangedLstParams)
	ON_BN_CLICKED(ID_BTN_ERRMSG, OnBnClickedBtnErrmsg)
END_MESSAGE_MAP()


// ClisencemanagerDlg 消息处理程序

BOOL ClisencemanagerDlg::OnInitDialog()
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

	if (!m_wndStatusBar.Create(this) ||
                !m_wndStatusBar.SetIndicators(indicators,
                    sizeof(indicators)/sizeof(UINT)))
    {
        TRACE0("Failed to create status barn");
        return -1;         // fail to create
    }

	m_listMenu.LoadMenu(IDR_MENU_LIST);
	ASSERT(m_listMenu);


    UINT nID=ID_INDICATOR_CAPS;        //控制状态栏里面的分栏
    m_wndStatusBar.SetPaneInfo(0,nID,SBPS_NORMAL|SBPS_NOBORDERS,36);               //返回值存nID中
    m_wndStatusBar.SetPaneText(0,_T("就绪"));

    m_wndStatusBar.SetPaneInfo(1,nID,SBPS_NORMAL,36);
    m_wndStatusBar.SetPaneText(1,_T("大写"));

    m_wndStatusBar.SetPaneInfo(2,nID,SBPS_POPOUT,36);
    m_wndStatusBar.SetPaneText(2,_T("数字"));

	m_wndStatusBar.SetPaneInfo(3,nID,SBPS_STRETCH ,50);
    m_wndStatusBar.SetPaneText(3,_T(""));

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_NORMAL);
	
	SetDlgItemText(IDC_VERSION,_T(""));
	loadconfig();

	initial_list();


	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void ClisencemanagerDlg::showloginfo(const CString &info)
{
	m_wndStatusBar.SetPaneText(3,(LPCTSTR)info);
}
void ClisencemanagerDlg::initial_list()
{
	m_list.InsertColumn(0,_T("参数类型"),LVCFMT_LEFT,60);
	m_list.InsertColumn(1,_T("参数名"),LVCFMT_LEFT,150);
	m_list.InsertColumn(2,_T("参数说明"),LVCFMT_LEFT,200);
	m_list.InsertColumn(3,_T("参数值"),LVCFMT_LEFT,300);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	m_listEdit.CreateEx(this,&m_list);
	m_listComboBox.CreateEx(this,&m_list);

	m_listComboBox.AddString(_T("公有"));
	m_listComboBox.AddString(_T("私有"));
	m_listComboBox.Insert(0);
	m_listEdit.Insert(1);
	m_listEdit.Insert(2);
	m_listEdit.Insert(3);
}
void ClisencemanagerDlg::loadpathconfig(int uID,std::map<std::string,std::string> &values)
{
	std::map<std::string,std::string>::const_iterator iter;
	TCHAR buffer[1024]="";
	DWORD len;
	for(iter = values.begin();iter != values.end();++iter)
	{
		std::string pathstr = iter->second;
		len = sizeof(buffer)/sizeof(TCHAR) - 1;
		memset(buffer,0,sizeof buffer);
		ConvertMBS2WCS(pathstr.c_str(),pathstr.size(),buffer,len);
		
		((CComboBox*)GetDlgItem(uID))->AddString(buffer);
	}
}
void ClisencemanagerDlg::loadconfig()
{
	CString path = ((ClisencemanagerApp*)AfxGetApp())->m_apppath;
	path += _T("\\lsccfg.ini");
	char global_path[2048+1] = "";
	DWORD len = sizeof(global_path)-1;
	ConvertWCS2MBS((LPCTSTR)path,path.GetLength(),global_path,len);
	CCIniFile ini(global_path);

	std::map<std::string,std::string> values;
	ini.ReadSectionValues("PRIVKEYS",values);
	loadpathconfig(ID_CMB_PRIVKEY,values);

	values.clear();
	ini.ReadSectionValues("PUBKEYS",values);
	loadpathconfig(ID_CMB_PUBKEY,values);

	values.clear();
	ini.ReadSectionValues("LISENCES",values);
	loadpathconfig(ID_CMB_LISENCE,values);

}
void ClisencemanagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void ClisencemanagerDlg::OnPaint() 
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
HCURSOR ClisencemanagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ClisencemanagerDlg::OnBnClickedBtnSelprivkey()
{
	CString filepath;
	filepath = selectFile(ID_CMB_PRIVKEY);
	if(filepath.IsEmpty())
		return;
	// 加载 private key
	m_private_keyfile = filepath;
}
CString ClisencemanagerDlg::selectFile(int uID,LPCTSTR filter)
{
	CString f;
	if(filter)
		f = filter;
	else
		f = _T("Key Files(*.key)|*.key|All Files(*.*)|*.*||");
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,f);
	if(dlg.DoModal()==IDCANCEL)
		return _T("");
	CString path = dlg.GetPathName();
	CComboBox * cmb = (CComboBox*)GetDlgItem(uID);
	if(cmb->FindString(0,path) != CB_ERR)
	{
		cmb->SelectString(0,path);
	}
	else
	{
		cmb->AddString(path);
		cmb->SelectString(0,path);
	}
	return path;
}
void ClisencemanagerDlg::OnBnClickedBtnSelpubkey()
{
	CString filepath;
	filepath = selectFile(ID_CMB_PUBKEY);
	if(filepath.IsEmpty())
		return;
	// 加载 private key
	m_public_keyfile = filepath;
}

void ClisencemanagerDlg::OnBnClickedBtnLisence()
{
	CString filepath;
	filepath = selectFile(ID_CMB_LISENCE,_T("License Files(*.lcs)|*.lcs|All Files(*.*)|*.*||"));
	if(filepath.IsEmpty())
		return;
	m_lisence_file = filepath;
}

static void do_saveconfig(CCIniFile &ini,const char *section,const std::map<std::string,std::string> &values)
{
	char indent[1024];
	char value[2048];
	DWORD len;
	std::map<std::string,std::string>::const_iterator iter;
	for(iter = values.begin();iter != values.end();++iter)
	{
		std::string s1 = iter->first;
		std::string s2 = iter->second;
		len = sizeof(indent)-1;
		memset(indent,0,sizeof indent);
		ConvertMBS2WCS(s1.c_str(),s1.size(),indent,len);
		indent[len] = 0;
		len = sizeof(value)-1;
		memset(value,0,sizeof value);
		ConvertMBS2WCS(s2.c_str(),s2.size(),value,len);
		value[len] = 0;
		ini.WriteString(section,indent,value);
	}
}

void ClisencemanagerDlg::saveconfig()
{

	CString path = ((ClisencemanagerApp*)AfxGetApp())->m_apppath;
	path += _T("\\lsccfg.ini");
	char global_path[2048+1] = "";
	DWORD len = sizeof(global_path)-1;
	ConvertWCS2MBS((LPCTSTR)path,path.GetLength(),global_path,len);
	CCIniFile ini(global_path);

	std::map<std::string,std::string> values;

	values.clear();
	savepathconfig(ID_CMB_PRIVKEY,values);
	do_saveconfig(ini,"PRIVKEYS",values);

	values.clear();
	savepathconfig(ID_CMB_PUBKEY,values);
	do_saveconfig(ini,"PUBKEYS",values);

	values.clear();
	savepathconfig(ID_CMB_LISENCE,values);
	do_saveconfig(ini,"LISENCES",values);
}

void ClisencemanagerDlg::savepathconfig(int uID,std::map<std::string,std::string> &values)
{
	CString item;
	CComboBox *cmb;
	char path_name[2048+1];
	char key_name[32];
	int i,n;
	DWORD len;
	cmb = (CComboBox*)this->GetDlgItem(uID);
	for(i = 0;i < cmb->GetCount();++i)
	{
		n = cmb->GetLBTextLen(i);
		cmb->GetLBText(i,item.GetBuffer(n));
		item.ReleaseBuffer();
		len = sizeof(path_name)-1;
		memset(path_name,0,sizeof path_name);
		ConvertWCS2MBS((LPCTSTR)item,item.GetLength(),path_name,len);
		sprintf(key_name,"key%d",i+1);
		values.insert(std::map<std::string,std::string>::value_type(key_name,path_name));
	}
}
void ClisencemanagerDlg::OnDestroy()
{
	CDialog::OnDestroy();
	saveconfig();
}

void ClisencemanagerDlg::OnBnClickedBtnLoadprivkey()
{
	if(m_private_keyfile.IsEmpty())
	{
		this->GetDlgItemText(ID_CMB_PRIVKEY,m_private_keyfile);
		if(m_private_keyfile.IsEmpty())
			return;
	}
	else
	{
		this->GetDlgItemText(ID_CMB_PRIVKEY,m_private_keyfile);
	}
	CString msg;
	char keypath[2048+1];
	DWORD len;
	int ret;
	memset(keypath,0,sizeof(keypath));
	len = sizeof(keypath)-1;
	ConvertWCS2MBS((LPCTSTR)m_private_keyfile,m_private_keyfile.GetLength(),keypath,len);
	if((ret=m_license.load_private_key_file(keypath))==LCS_OK)
	{
		showloginfo(_T("加载私钥文件成功"));
	}
	else
	{
		msg.Format(_T("加载私钥文件错误,ret[%d]"),ret);
		showloginfo(msg);
		AfxMessageBox(msg);
	}
}

void ClisencemanagerDlg::OnBnClickedBtnLoadpubkey()
{
	if(m_public_keyfile.IsEmpty())
	{
		this->GetDlgItemText(ID_CMB_PUBKEY,m_public_keyfile);
		if(m_public_keyfile.IsEmpty())
			return;
	}
	else
	{
		this->GetDlgItemText(ID_CMB_PUBKEY,m_public_keyfile);
	}
	CString msg;
	char keypath[2048+1];
	DWORD len;
	int ret;
	memset(keypath,0,sizeof(keypath));
	len = sizeof(keypath)-1;
	ConvertWCS2MBS((LPCTSTR)m_public_keyfile,m_public_keyfile.GetLength(),keypath,len);
	if((ret=m_license.load_public_key_file(keypath))==LCS_OK)
	{
		showloginfo(_T("加载公钥文件成功"));
	}
	else
	{
		msg.Format(_T("加载公钥文件错误,ret[%d]"),ret);
		showloginfo(msg);
		AfxMessageBox(msg);
	}
}

void ClisencemanagerDlg::load_param_2_list()
{
	CString pname,psummary,pvalue;
	std::list<ks_cllcns_param_t> params;
	ks_cllcns_param_t p;
	std::list<ks_cllcns_param_t>::const_iterator iter;
	int i;
	DWORD len;
	LPSTR b;
	m_license.get_all_parameters(params);
	m_list.DeleteAllItems();
	for(iter=params.begin(),i=0;iter != params.end();++iter)
	{
		p = *iter;
		
		len = ks_cardlib_license::LCNS_PARAM_MAX_LEN+1;
		b = pname.GetBuffer(len);
		memset(b,0,len);
		ConvertMBS2WCS(p.param_name.c_str(),p.param_name.length(),b,len);
		pname.ReleaseBuffer();

		len = ks_cardlib_license::LCNS_PARAM_MAX_LEN+1;
		b = psummary.GetBuffer(len);
		memset(b,0,len);
		ConvertMBS2WCS(p.param_summary.c_str(),p.param_summary.length(),b,len);
		psummary.ReleaseBuffer();
		
		len = ks_cardlib_license::LCNS_PARAM_MAX_LEN+1;
		b = pvalue.GetBuffer(len);
		memset(b,0,len);
		ConvertMBS2WCS(p.param_value.c_str(),p.param_value.length(),b,len);
		pvalue.ReleaseBuffer();

		if(p.param_name == ks_cardlib_license::LCNS_CUST_ID)
		{
			SetDlgItemText(IDC_CUST_ID,pvalue);
		}
		else if(p.param_name == ks_cardlib_license::LCNS_EXPIRED_DATE)
		{
			SetDlgItemText(IDC_EDT_EXPIRED,pvalue);
		}
		else if(p.param_name == ks_cardlib_license::LCNS_VERSION)
		{
			SetDlgItemText(IDC_VERSION,pvalue);
		}
		else
		{
			m_list.InsertItem(i,_T("公有"));
			m_list.SetItemText(i,1,pname);
			m_list.SetItemText(i,2,psummary);
			m_list.SetItemText(i,3,pvalue);
			i++;
		}
	}

}
void ClisencemanagerDlg::OnBnClickedBtnLoadlisence()
{
	if(m_lisence_file.IsEmpty())
	{
		this->GetDlgItemText(ID_CMB_LISENCE,m_lisence_file);
		if(m_lisence_file.IsEmpty())
			return;
	}
	else
	{
		this->GetDlgItemText(ID_CMB_LISENCE,m_lisence_file);
	}

	CString msg;
	char keypath[2048+1];
	DWORD len;
	int ret;
	memset(keypath,0,sizeof(keypath));
	len = sizeof(keypath)-1;
	ConvertWCS2MBS((LPCTSTR)m_lisence_file,m_lisence_file.GetLength(),keypath,len);
	if((ret=m_license.load_license_file(keypath))==LCS_OK)
	{
		showloginfo(_T("加载授权文件成功"));
		load_param_2_list();
	}
	else
	{
		msg.Format(_T("加载授权文件错误,ret[%d]"),ret);
		showloginfo(msg);
		AfxMessageBox(msg);
	}
}

void ClisencemanagerDlg::OnBnClickedBtnGenkey()
{
	int ret;
	CString dlg_title;
	CString priv_key,pub_key;
	char priv_path[2048+1],pub_path[2048+1];
	DWORD len;

	if(AfxMessageBox(_T("你是否要生成key文件？"),MB_OKCANCEL|MB_DEFBUTTON2)==IDCANCEL)
	{
		return ;
	}
	CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Key Files(*.key)|*.key|All Files(*.*)|*.*||"));
	dlg_title = _T("保存私钥文件");
	dlg.GetOFN().lpstrTitle = (LPCTSTR)dlg_title;
	if(dlg.DoModal()==IDCANCEL)
		return;
	priv_key = dlg.GetPathName();

	dlg_title = _T("保存公钥文件");
	dlg.GetOFN().lpstrTitle = (LPCTSTR)dlg_title;
	if(dlg.DoModal()==IDCANCEL)
		return;
	pub_key = dlg.GetPathName();

	memset(priv_path,0,sizeof(priv_path));
	len = sizeof(priv_path)-1;
	ConvertWCS2MBS((LPCTSTR)priv_key,priv_key.GetLength(),priv_path,len);

	memset(pub_path,0,sizeof pub_path);
	len = sizeof(pub_path)-1;
	ConvertWCS2MBS((LPCTSTR)pub_key,pub_key.GetLength(),pub_path,len);

	// save key
	ret = m_license.generate_key_file(priv_path,pub_path);
	if(ret == LCS_OK)
	{
		showloginfo(_T("生成key文件成功，请检查"));
		AfxMessageBox(_T("生成key文件成功，请检查"));
	}
	else
	{
		CString msg;
		msg.Format(_T("生成key文件失败，ret=%d"),ret);
		showloginfo(msg);
		AfxMessageBox((LPCTSTR)msg);
	}
	

}

void ClisencemanagerDlg::getitemtext(int uID,char *text)
{
	CString t;
	DWORD len;
	this->GetDlgItemText(uID,t);
	len = 256;
	ConvertWCS2MBS((LPCTSTR)t,t.GetLength(),text,len);
	text[len] = 0;
}

void ClisencemanagerDlg::save_list_param()
{
	int cnt,i;
	DWORD len;
	char param_name[1024+1];
	char param_summary[1024+1];
	char param_value[2048+1];
	CString t;
	cnt = m_list.GetItemCount();
	for(i = 0;i< cnt;++i)
	{
		t = m_list.GetItemText(i,1);
		t = t.Trim();
		if(t.IsEmpty())
		{
			AfxMessageBox(_T("参数名不能为空!"));
			return;
		}
		memset(param_name,0,sizeof param_name);
		len = sizeof(param_name)-1;
		ConvertWCS2MBS((LPCTSTR)t,t.GetLength(),param_name,len);

		t = m_list.GetItemText(i,2);
		memset(param_summary,0,sizeof param_summary);
		len = sizeof(param_summary)-1;
		ConvertWCS2MBS((LPCTSTR)t,t.GetLength(),param_summary,len);

		t = m_list.GetItemText(i,3);
		memset(param_value,0,sizeof param_value);
		len = sizeof(param_value)-1;
		ConvertWCS2MBS((LPCTSTR)t,t.GetLength(),param_value,len);
	
		if(m_license.update_public_param(param_name,param_summary,param_value))
		{
			CString msg;
			msg.Format(_T("保存参数[%s]错误"),(LPCTSTR)m_list.GetItemText(i,1));
			AfxMessageBox(msg);
		}

	}
}

void ClisencemanagerDlg::OnBnClickedBtnSavelicense()
{
	char pvalue[512];
	char path[2048+1];
	int ret;
	DWORD len;
	if(m_lisence_file.IsEmpty())
	{
		CFileDialog dlg(FALSE,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			_T("All Files(*.*)|*.*||"));
		CString dlg_title = _T("保存授权文件");
		dlg.GetOFN().lpstrTitle = (LPCTSTR)dlg_title;
		if(dlg.DoModal()==IDCANCEL)
			return;
		m_lisence_file = dlg.GetPathName();
	}
	else
	{
		if(AfxMessageBox(_T("你是否确定保存授权文件？"),MB_OKCANCEL|MB_DEFBUTTON2)==IDCANCEL)
			return;
	}
	m_license.delete_all_param();
	memset(pvalue,0,sizeof pvalue);
	getitemtext(IDC_EDT_EXPIRED,pvalue);
	m_license.update_public_param(ks_cardlib_license::LCNS_EXPIRED_DATE,"",pvalue);

	memset(pvalue,0,sizeof pvalue);
	getitemtext(IDC_CUST_ID,pvalue);
	m_license.update_public_param(ks_cardlib_license::LCNS_CUST_ID,"",pvalue);

	memset(path,0,sizeof path);
	len = sizeof(path)-1;
	ConvertWCS2MBS((LPCTSTR)m_lisence_file,m_lisence_file.GetLength(),path,len);

	save_list_param();

	ret = m_license.save_license_file(path);
	if(ret)
	{
		CString msg;
		msg.Format(_T("保存授权文件失败,ret=%d"),ret);
		AfxMessageBox(msg);
		showloginfo(msg);
	}
	else
	{
		showloginfo(_T("保存授权文件成功"));
	}
	return;
}

void ClisencemanagerDlg::OnNMRclickLstParams(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	//if(pNMListView->iItem == -1)
	{
		DWORD  pos = GetMessagePos();
		CPoint pt(LOWORD(pos),HIWORD(pos));
		CMenu *popup = m_listMenu.GetSubMenu(0);
		ASSERT(popup != NULL);
		
		m_select_item_idx = -1;
		LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
		CPoint point(pia->ptAction);
		m_select_item_idx = m_list.HitTest(point);

		if(m_select_item_idx < 0 || m_select_item_idx >= m_list.GetItemCount())
		{
			popup->EnableMenuItem(1,FALSE);
		}
		else
		{
			popup->EnableMenuItem(1,TRUE);
		}
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
	}
	*pResult = 0;
}

void ClisencemanagerDlg::OnMenuAdd()
{
	int cnt = m_list.GetItemCount();
	m_list.InsertItem(cnt,_T("公有"));
	m_list.SetItemText(cnt,1,_T("kscardlib."));
	m_list.SetItemText(cnt,2,_T(""));
	m_list.SetItemText(cnt,3,_T(""));

}

void ClisencemanagerDlg::OnMenuDel()
{
	if(m_select_item_idx >= 0 && m_select_item_idx < m_list.GetItemCount())
	{
		// 
		CString pname;
		char tname[ks_cardlib_license::LCNS_PARAM_MAX_LEN+1];
		int len;
		DWORD t;
		len = ks_cardlib_license::LCNS_PARAM_MAX_LEN+1;
		m_list.GetItemText(m_select_item_idx,1,pname.GetBuffer(len),len);
		memset(tname,0,sizeof tname);
		ConvertWCS2MBS((LPCTSTR)pname,pname.GetLength(),tname,t);
		m_license.delete_param(tname);
		m_list.DeleteItem(m_select_item_idx);
		m_select_item_idx = -1;
	}
}

void ClisencemanagerDlg::OnNMClickLstParams(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pia = (LPNMITEMACTIVATE)pNMHDR;
	CString jsonPath;
	if(pia->iItem>=0)
	{
		CString v = m_list.GetItemText(pia->iItem,1);
		CString p = m_list.GetItemText(pia->iItem,3);
		if(v == "kscardlib.cardreadright"
			|| v == "kscardlib.cardwriteright")
		{
			CCardFieldDlg dlg;
			jsonPath = ((ClisencemanagerApp*)AfxGetApp())->m_apppath;
			jsonPath += "\\lcsmanager\\cardright.json";
			if(dlg.DoSelectDlg(jsonPath,p)==IDOK)
			{
				m_list.SetItemText(pia->iItem,3,p);
			}
		}
		else if(v == "kscardlib.mfinit.sect"
			|| v == "kscardlib.mfrecycle.sect")
		{
			CCardFieldDlg dlg;
			jsonPath = ((ClisencemanagerApp*)AfxGetApp())->m_apppath;
			jsonPath += "\\lcsmanager\\mfsection.json";
			if(dlg.DoSelectDlg(jsonPath,p)==IDOK)
			{
				m_list.SetItemText(pia->iItem,3,p);
			}
		}
		else
		{
			CListCtrlEditBase::OnOpen(&m_list, pNMHDR);
		}
	}
	*pResult = 0;
}

void ClisencemanagerDlg::OnNMDblclkLstParams(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nItem, nSubItem;
    if (CListCtrlEditBase::HitTestEx(&m_list, pNMHDR, nItem, nSubItem) &&
	    nSubItem == 0)
	{
	   m_listComboBox.ShowEdit(nItem, nSubItem);
	}
	*pResult = 0;
}

void ClisencemanagerDlg::OnLvnItemchangedLstParams(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	char tname[ks_cardlib_license::LCNS_PARAM_MAX_LEN+1];
	char tsummary[ks_cardlib_license::LCNS_PARAM_MAX_LEN+1];
	char tvalue[ks_cardlib_license::LCNS_PARAM_MAX_LEN+1];

	int n = pNMLV->iItem;
	int len;
	DWORD t;
	/*
	if(n >= 0 && n < m_list.GetItemCount())
	{
		// 处理
		CString pname,psummary,pvalue;
		len = ks_cardlib_license::LCNS_PARAM_MAX_LEN;
		m_list.GetItemText(n,1,pname.GetBuffer(len),len);
		pname.ReleaseBuffer();
		pname = pname.Trim();
		m_list.GetItemText(n,2,psummary.GetBuffer(len),len);
		psummary.ReleaseBuffer();
		m_list.GetItemText(n,3,pvalue.GetBuffer(len),len);
		pvalue.ReleaseBuffer();

		memset(tname,0,sizeof tname);
		memset(tsummary,0,sizeof tsummary);
		memset(tvalue,0,sizeof tvalue);

		ConvertWCS2MBS((LPCTSTR)pname,pname.GetLength(),tname,t);
		ConvertWCS2MBS((LPCTSTR)psummary,psummary.GetLength(),tsummary,t);
		ConvertWCS2MBS((LPCTSTR)pvalue,pvalue.GetLength(),tvalue,t);

		if(pname.IsEmpty())
		{
			AfxMessageBox(_T("参数名不能为空"));
			return;
		}
		m_license.update_public_param(tname,tsummary,tvalue);

	}
	*/
	*pResult = 0;
}

void ClisencemanagerDlg::OnBnClickedBtnErrmsg()
{
	CString msg = _T("1 文件格式错误\n"
					"2 解密错误\n"
					"3 加密错误\n"
					"4 校验文件错误\n"
					"5 写文件错误\n"
					"6 读文件错误\n"
					"7 内存操作出错\n"
					"8 未授权\n"
					"9 未指定文件名\n"
					"10 参数未设置\n"
					"11 不支持的操作或者参数\n"
					"12 参数格式错误\n");

	AfxMessageBox(msg);
}
