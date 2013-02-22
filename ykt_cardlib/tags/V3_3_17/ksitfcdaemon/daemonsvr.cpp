//////////////////////////////////////////////////////
////
#include "std.h"
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <sstream>
#include <iomanip>
#include "daemonsvr.h"
#include "svrrequest.h"

//#include "kscarddaemon.h"

///////////////////////////////////////////////////////////////////////////////
KsCardDaemonSvr* KsCardDaemonSvr::instance_ = NULL;
KsCardDaemonSvr* KsCardDaemonSvr::instance()
{
	if(NULL == instance_)
	{
		instance_ = new KsCardDaemonSvr;
	}
	return instance_;
}
void KsCardDaemonSvr::FreeSvr()
{
	if(NULL != instance_)
	{
		delete instance_;
		instance_ = NULL;
	}
}
KsCardDaemonSvr::KsCardDaemonSvr():wxThread(wxTHREAD_JOINABLE),
	svrport_(0),server_(NULL),cltsock_(NULL),global_cfg_(NULL)
{
	if(Create() != wxTHREAD_NO_ERROR)
	{
		wxLogError(wxT("创建服务线程失败"));
	}
}
KsCardDaemonSvr::~KsCardDaemonSvr()
{
	freeCltSocket();
}
int KsCardDaemonSvr::StartServer(int port)
{
	if(NULL != server_)
	{
		wxLogMessage(wxT("服务已启动"));
		return 0;
	}
	wxIPV4address addr;
	addr.Service(port);
	addr.LocalHost();
	server_ = new wxSocketServer(addr,wxSOCKET_REUSEADDR);
	if(!server_->IsOk())
	{
		wxLogError(wxT("启动服务失败"));
		StopServer();
		return -1;
	}
	server_->SetTimeout(30); // 30 seconds
	return 0;
}
int KsCardDaemonSvr::StopServer()
{
	if(NULL == server_)
	{
		wxLogMessage(wxT("服务未启动"));
		return 0;
	}
	if(cltsock_)
	{
		cltsock_->Close();
		delete cltsock_;
		cltsock_ = NULL;
	}
	server_->Destroy();
	delete server_;
	server_ = NULL;
	wxLogMessage(wxT("关闭服务"));
	return 0;
}
void KsCardDaemonSvr::freeCltSocket()
{
	if(NULL == cltsock_)
		return;
	cltsock_->Close();
	delete cltsock_;
	cltsock_ = NULL;
}
int KsCardDaemonSvr::process_loop(long timeout)
{
	int ret;
	bool rc;
	size_t recvlen=0;
	size_t msglen = 0;
	if(NULL == server_)
		return -1;
	if(cltsock_ == NULL)
	{
		rc = server_->WaitForAccept(0,100);
		if(rc)
		{
			wxSocketBase *clt = server_->Accept();
			cltsock_ = clt;
			msgrecv_.Reset();
			requestMsg_.Reset();
			msgrecv_.SetClient(cltsock_);
			wxLogMessage(wxT("接收新客户端连接"));
		}
	}
	if(NULL == cltsock_)
	{
		return -1;
	}
	rc = cltsock_->WaitForRead(0,timeout);
	if(rc)
	{
		ret = msgrecv_.RecvData(requestMsg_);
		if(ret<0)
		{
			requestMsg_.Reset();
			if(ret == -2)
			{
				freeCltSocket();
				return -1;
			}
			return -1;
		}
		else if(ret == 0)
		{
			ret = do_process_msg();
			requestMsg_.Reset();
			return ret;
		}
		else
		{
			// 继续接收后续消息
			return 1;
		}
	}
	else
	{
		return -1;
	}
}
int KsCardDaemonSvr::send_response(KsCardMsg &resp)
{
	std::stringstream content;
	std::string buf = resp.ToMsg();
	content<<std::setfill('0')<< std::setw(5)<<buf.length()<<buf;
	buf = content.str();
	//if(cltsock_->WaitForWrite(0,300))
	{
		cltsock_->Write(buf.c_str(),buf.length());
		return 0;
	}
	return -1;
}
int KsCardDaemonSvr::do_process_msg()
{	
	KsCardMsg resp;
	std::string msgtype;
	msgtype = requestMsg_.MsgType();
	wxString info = wxString::Format(wxT("msg[%s] received"),msgtype.c_str());
	wxLogMessage(info);
	int ret;
	ret = KsCardProcessor::instance()->ProcessRequest(requestMsg_,resp);
	if(ret == 0)
	{
		// process success, and not return
	}
	else if(ret == 1)
	{
		// send response to client
		if(send_response(resp))
		{
			return -1;
		}
	}
	else
	{
		// process error
		info = wxString::Format(wxT("msg[%s] process error,ret=%d"),msgtype.c_str(),ret);
		wxLogError(info);
		return -1;
	}
	return 0;
	
}
void* KsCardDaemonSvr::Entry()
{
	{
		wxCriticalSectionLocker locker(global_cfg_->m_critsect);
		wxLogMessage(wxT("服务线程已启动"));
	}
	for(;;)
	{
		if ( TestDestroy() )
            break;
		if(this->process_loop(100)<0)
			wxThread::Sleep(500);
	}
	return NULL;
}
void KsCardDaemonSvr::OnExit()
{
	wxLogMessage(wxT("服务线程已停止"));
}

int KsCardDaemonSvr::run_as_thr()
{
	static int first_start = 1;
	if(first_start)
	{
		if(this->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError(wxT("启动线程失败"));
			return -1;
		}
		first_start = 0;
	}
	else
	{
		if(this->Resume() != wxTHREAD_NO_ERROR)
		{
			wxLogError(wxT("启动线程失败"));
			return -1;
		}
	}
	return 0;
}
int KsCardDaemonSvr::stop_thr()
{
	this->Pause();
	return 0;
}
void KsCardDaemonSvr::SetConfig(KsCardDaemonCfg* cfg)
{
	global_cfg_ = cfg;
}