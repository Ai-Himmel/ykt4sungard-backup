#include "std.h"
#include "InitCardFrameImpl.h"
#include "kscard_imp.h"

#define WIN_TITLE wxT("SunGard InitCardUtil ")
#define UTIL_VERSION wxT("V1.0 " __DATE__)
//DECLARE_EVENT_TYPE(wxFINISH_ONECARD,-1)

//DEFINE_EVENT_TYPE(wxFINISH_ONECARD)

InitCardFrameImpl::InitCardFrameImpl( wxWindow* parent )
:InitCardFrame( parent ),m_PCDConnected(false),m_isAuth(false),m_workThr(NULL)
{
	wxString title = WIN_TITLE;
	title += UTIL_VERSION;
	this->SetTitle(title);
	m_baudBox->SetSelection(m_baudBox->GetCount()-1);
	this->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(InitCardFrameImpl::m_OnInitOneCard),NULL,this);
	this->Center();
	if(InitKsCardLib())
	{
		this->Close(true);
	}
}
void InitCardFrameImpl::m_OnInitOneCard( wxCommandEvent& event )
{
	LogMsg(wxT("完成一张卡"));
}
int InitCardFrameImpl::InitKsCardLib()
{
	if(ks_init())
	{
		wxMessageBox("初始化读卡库错误");
		return -1;
	}
	return 0;
}
void InitCardFrameImpl::m_connPCDBtnOnButtonClick( wxCommandEvent& event )
{
	if(m_PCDConnected)
	{
		ks_closeport();
		m_isAuth = false;
		LogMsg(wxT("断开设备连接"));
	}
	else
	{
		int ret;
		int port,baud;
		wxString value = m_portNoBox->GetValue();
		if(wxT("USB") == value)
		{
			port = 100;
			baud = 0;
		}
		else
		{
			if(value.StartsWith(wxT("COM")))
			{
				long l = 0;
				value.SubString(3,value.Length()).ToLong(&l);
				port = l;
				value = m_baudBox->GetValue();
				value.ToLong(&l);
				baud = l;
			}
			else
			{
				wxMessageBox(wxT("端口号参数错误"));
				return;
			}
		}
		ret = ks_openport(port,baud);
		if(ret)
		{
			wxMessageBox(wxT("连接设备失败"));
			LogMsg(wxT("连接设备失败"));
			return;
		}
		ks_beep();
		LogMsg(wxT("连接设备成功"));
	}
	m_PCDConnected = !m_PCDConnected;
}

void InitCardFrameImpl::m_connPCDBtnOnUpdateUI( wxUpdateUIEvent& event )
{
	if(m_PCDConnected)
	{
		m_connPCDBtn->SetLabel(wxT("断开连接"));
	}
	else
	{
		m_connPCDBtn->SetLabel(wxT("连接设备"));
	}
	m_connPCDBtn->Enable(!IsWork());
}
void InitCardFrameImpl::m_startBtnOnButtonClick( wxCommandEvent& event )
{
	if(IsWork())
	{
		StopWork();
	}
	else
	{
		if(StartWork())
		{
			//
			LogMsg(wxT("启动服务成功"));
		}
		else
		{
			wxMessageBox(wxT("启动服务失败"));
			LogMsg(wxT("启动服务失败"));
		}
	}
}
void InitCardFrameImpl::m_startBtnOnUpdateUI( wxUpdateUIEvent& event )
{
	if(m_PCDConnected && m_isAuth)
	{
		m_startBtn->Enable(true);
		// check running
		if(IsWork())
		{
			m_startBtn->SetLabel(wxT("停止"));
		}
		else
		{
			m_startBtn->SetLabel(wxT("开始"));
		}
	}
	else
	{
		m_startBtn->Enable(false);
	}
}
wxString InitCardFrameImpl::getCardLibError(wxString &errmsg)
{
	wxString msg = ks_geterrmsg(NULL);
	if(msg.Length()>0)
	{
		errmsg = msg;
	}
	else
	{
		errmsg = wxString("未知错误");
		msg = errmsg;
	}
	return msg;
}
void InitCardFrameImpl::m_authBtnOnButtonClick( wxCommandEvent& event )
{
	int ret;
	wxString pwd = wxGetPasswordFromUser(wxT("输入密钥卡密码，无密码直接确认"));
	ret = ks_loadcardkeys(pwd.mb_str());
	if(ret)
	{
		wxString errmsg;
		getCardLibError(errmsg);
		errmsg = "授权失败 ：" + errmsg;
		wxMessageBox(errmsg);
		m_isAuth = false;
		return;
	}
	ks_beep();
	LogMsg(wxT("授权成功"));
	m_isAuth = true;
}
void InitCardFrameImpl::m_authBtnOnUpdateUI( wxUpdateUIEvent& event )
{
	m_authBtn->Enable(m_PCDConnected && !IsWork());
}
bool InitCardFrameImpl::StartWork()
{
	m_workThr = new InitCardThread();
	if(m_workThr->StartWork())
		return true;
	return false;
}
void InitCardFrameImpl::StopWork()
{
	if(m_workThr->IsRunning())
	{
		m_workThr->Delete();
		//delete m_workThr;
		m_workThr = NULL;
	}
}
bool InitCardFrameImpl::IsWork()
{
	if(NULL == m_workThr)
		return false;
	return m_workThr->IsRunning();
}
void InitCardFrameImpl::LogMsg(const wxString &msg)
{
	m_logText->AppendText(msg + wxT("\n"));	
}
void InitCardFrameImpl::m_closeBtnOnButtonClick( wxCommandEvent& event )
{
	Close();
}
void InitCardFrameImpl::m_closeBtnOnUpdateUI( wxUpdateUIEvent& event )
{
	long style = this->GetWindowStyle();
	m_closeBtn->Enable(!IsWork() && !m_PCDConnected);
	/*
	if(!IsWork() && !m_PCDConnected)
	{
		style |= wxCLOSE_BOX;		
	}
	else
	{
		style &=  ~wxCLOSE_BOX;
	}
	this->SetWindowStyleFlag(style);
	this->Refresh();
	*/
}
///////////////////////////////////////////////////////////////////////////////
IMPLEMENT_APP(InitCardApp)
InitCardApp::InitCardApp():wxApp(),m_frame(NULL)
{
}
InitCardApp::~InitCardApp()
{
}
bool InitCardApp::OnInit()
{
	m_frame = new InitCardFrameImpl(NULL);
	m_frame->Show();
	return true;
}
int InitCardApp::OnExit()
{
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
InitCardThread::InitCardThread():wxThread()
{
	
}
InitCardThread::~InitCardThread()
{
}
void InitCardThread::SendFinishEvent(const wxString &cardPhyID)
{
	wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED,wxID_MAINFRAME);
	evt.SetEventObject(&wxGetApp());
	
	wxGetApp().ProcessEvent(evt);
}
int InitCardThread::doProcess()
{
	int ret;
	char cardPhyID[32]={0};
	static wxString prePhyID;
	ret = ks_card(cardPhyID);
	if(ret)
	{
		return -1;
	}
	if(prePhyID.Cmp(cardPhyID)==0)
	{
		return -1;
	}
	ret = ks_recycleusercard();
	if(ret)
	{
		ks_beeperr();
		return 1;
	}
    prePhyID = cardPhyID;
	SendFinishEvent(cardPhyID);
	ks_halt();
	ks_beep();
	return 0;
}
void* InitCardThread::Entry()
{
	for(;;)
	{
		if ( TestDestroy() )
            break;
		if(this->doProcess()<0)
			wxThread::Sleep(500);
	}
	return NULL;
}
bool InitCardThread::StartWork()
{
	if(Create() != wxTHREAD_NO_ERROR)
	{
		return false;
	}
	if(Run() != wxTHREAD_NO_ERROR)
	{
		return false;
	}
	return true;
}