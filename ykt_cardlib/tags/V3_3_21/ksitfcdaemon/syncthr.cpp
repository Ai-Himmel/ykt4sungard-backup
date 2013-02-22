///////////////////////////////////////////////////////////////////////////////
//
#include "std.h"
#include "syncthr.h"
#include "kscardmsg.h"
#include "yktclt.h"
#include "dbhandler.h"
#include "svrrequest.h"


KsSyncThr* KsSyncThr::instance_ = NULL;
const int KsSyncThr::CHK_HEARTBEAT_INTVAL = 5 * 1000 * 60;
const int KsSyncThr::UPLOAD_SERAIL_INTVAL = 10000; //1 * 1000 * 60;
const int KsSyncThr::SYNC_BLACKCARD_INTVAL = 10 * 1000 * 60;
const int KsSyncThr::ONLINE_INTERVAL = 1000 * 60;

KsSyncThr* KsSyncThr::instance()
{
	if(NULL == instance_)
	{
		instance_ = new KsSyncThr();
	}
	return instance_;
}
void KsSyncThr::FreeAll()
{
	if(NULL != instance_)
	{
		instance_->stop_thr();
		delete instance_;
		instance_ = NULL;
	}
}
/////////////////////////////////////
KsSyncThr::KsSyncThr():wxThread(wxTHREAD_JOINABLE),global_cfg_(NULL),
	upload_serial_interval_(0),sync_blackcard_interval_(0),svronline_(0)
{
	if(Create() != wxTHREAD_NO_ERROR)
	{
		wxLogError(wxT("创建同步线程失败"));
	}
}

KsSyncThr::~KsSyncThr()
{
	stop_thr();
}

int KsSyncThr::start_thr()
{
	static int first_start = 1;
	if(this->IsRunning())
	{
		wxLogMessage(wxT("同步线程已经启动"));
		return 0;
	}
	checkSvrHeartBeatTime_.Start();
	uploadSerialTime_.Start();
	syncBlackCardTime_.Start();
	if(first_start)
	{
		if(this->Run() != wxTHREAD_NO_ERROR)
		{
			wxLogError(wxT("启动同步线程失败"));
			return -1;
		}
		first_start = 0;
	}
	else
	{
		if(this->Resume() != wxTHREAD_NO_ERROR)
		{
			wxLogError(wxT("启动同步线程失败"));
			return -1;
		}
	}
	return 0;
}
int KsSyncThr::stop_thr()
{
	if(this->IsRunning())
	{
		if(this->Pause() != wxTHREAD_NO_ERROR)
		{
			wxLogError(wxT("暂停同步线程失败"));
			return -1;
		}
	}
	return 0;
}
void* KsSyncThr::Entry()
{
	{
		wxCriticalSectionLocker locker(global_cfg_->m_critsect);
		wxLogMessage(wxT("同步线程已启动"));
		checkSvrHeartBeatTime_.Start();
		uploadSerialTime_.Start();
		syncBlackCardTime_.Start();
		upload_serial_interval_ = KsSyncThr::UPLOAD_SERAIL_INTVAL;
		sync_blackcard_interval_ = KsSyncThr::SYNC_BLACKCARD_INTVAL;
	}
	// 启动时检查一卡通系统状态
	ChkHeartBeat();
	for(;;)
	{
		if(TestDestroy())
			break;
		DoMainLoop();
		wxThread::Sleep(1000);
	}
	return NULL;
}
void KsSyncThr::OnExit()
{
	wxLogMessage(wxT("同步线程已退出"));
}
void KsSyncThr::UpdateSvrStatus(int online)
{
	wxCriticalSectionLocker locker(m_Chkcritsect);
	if(online)
	{
		svrofflineTime_.Start();
	}
	svronline_ = online;
}
int KsSyncThr::IsOnline()
{
	wxCriticalSectionLocker locker(m_Chkcritsect);
	if(svronline_)
	{
		long tick = svrofflineTime_.Time();
		// offline
		if(tick >= KsSyncThr::ONLINE_INTERVAL)
			return -1;

		return 0;
	}
	return -1;
}
void KsSyncThr::DoMainLoop()
{
	if(checkSvrHeartBeatTime_.Time() >= KsSyncThr::CHK_HEARTBEAT_INTVAL)
	{
		checkSvrHeartBeatTime_.Start();
		ChkHeartBeat();
	}
	if(uploadSerialTime_.Time() >= upload_serial_interval_)
	{
		uploadSerialTime_.Start();
		UploadSerial();
	}
	if(syncBlackCardTime_.Time() >= sync_blackcard_interval_)
	{
		syncBlackCardTime_.Start();
		SyncBlackCard();
	}
}
void KsSyncThr::SyncBlackCard()
{
	int ret = KsYktSvrUtil::SyncBlackCard();
	sync_blackcard_interval_ = KsSyncThr::SYNC_BLACKCARD_INTVAL;
	if(ret ==0)
	{
		UpdateSvrStatus(1);
		sync_blackcard_interval_ = 0;
		return;
	}
	else if(ret == -1)
	{
		// error
		UpdateSvrStatus(1);
		return;
	}
	else if(ret == -2)
	{
		
		// 网络故障
		UpdateSvrStatus(0);
		return;
	}
	else if(ret == 1)
	{
		// 无黑名单
		UpdateSvrStatus(1);
		return ;
	}
}
void KsSyncThr::UploadSerial()
{
	int ret = KsYktSvrUtil::UploadSerial();
	
	if(ret ==0)
	{
		UpdateSvrStatus(1);
		upload_serial_interval_ = 0;
		return;
	}
	else if(ret == -1)
	{
		// error
		upload_serial_interval_ = KsSyncThr::UPLOAD_SERAIL_INTVAL;
		UpdateSvrStatus(1);
		return;
	}
	else if(ret == -2)
	{
		
		// 网络故障
		upload_serial_interval_ += KsSyncThr::UPLOAD_SERAIL_INTVAL;
		if(KsSyncThr::UPLOAD_SERAIL_INTVAL*10 < upload_serial_interval_)
			upload_serial_interval_ = KsSyncThr::UPLOAD_SERAIL_INTVAL;
		UpdateSvrStatus(0);
		return;
	}
	else if(ret == 1)
	{
		// 无黑名单
		upload_serial_interval_ += KsSyncThr::UPLOAD_SERAIL_INTVAL;
		if(KsSyncThr::UPLOAD_SERAIL_INTVAL*10 < upload_serial_interval_)
			upload_serial_interval_ = KsSyncThr::UPLOAD_SERAIL_INTVAL;
		return ;
	}
}
void KsSyncThr::ChkHeartBeat()
{
	if(IsOnline()==0)
		return;
	int ret = KsYktSvrUtil::ChkHeartBeat();
	if(ret ==0)
	{
		UpdateSvrStatus(1);
		return;
	}
	else if(ret == -1)
	{
		// error
		UpdateSvrStatus(0);
		return;
	}
	else if(ret == -2)
	{
		
		// 网络故障
		UpdateSvrStatus(0);
		return;
	}
	else
	{
		return ;
	}
}

void KsSyncThr::SetConfig(KsCardDaemonCfg* cfg)
{
	global_cfg_ = cfg;
}
int KsSyncThr::InitYKTSvr(const char *apppath)
{
	return KsYktSvrUtil::InitYKTSvr(apppath,global_cfg_);
}

///////////////////////////////////////////////////////////////////////////////
// class KsYktSvrUtil
KsCardDaemonCfg* KsYktSvrUtil::global_cfg_ = NULL;
int KsYktSvrUtil::isYKTSvrOK_ = 0;

int KsYktSvrUtil::IsYKTSvrOK()
{
	if(KsYktSvrUtil::isYKTSvrOK_)
		return 0;
	wxSocketClient sock;
	wxIPV4address addr;
	addr.Hostname(global_cfg_->svrip_.c_str());
	addr.Service(global_cfg_->svrport_);
	sock.Connect(addr,false);
	if(sock.WaitOnConnect(1,0))
	{
		if(sock.IsConnected())
		{
			KsYktSvrUtil::isYKTSvrOK_ = 1;
			return 0;
		}
	}
	return -1;
}
int KsYktSvrUtil::InitYKTSvr(const char *path,KsCardDaemonCfg* cfg)
{
	assert(path != NULL);
	assert(cfg != NULL);
	wxString xpack = path;
	xpack += "/cpack.dat";
	KS_YKT_Clt::set_xpack_path(xpack.c_str());
	global_cfg_ = cfg;
	if(!KS_YKT_Clt::Initialize(global_cfg_->svrip_.c_str(),
		global_cfg_->svrport_,global_cfg_->svrmainfunc_))
	{
		wxLogError(wxT("初始化一卡通服务失败"));
		return -1;
	}
	global_cfg_ = cfg;
	return 0;
}
int KsYktSvrUtil::SyncBlackCard()
{
	if(IsYKTSvrOK())
		return -2;
	InfoDB &infodb = KsCardProcessor::instance()->GetInfoDB();
	std::string cardverno;
	if(infodb.GetMaxCardVer(cardverno))
	{
		wxLogError(wxT("读取本地黑名单版本失败"));
		return -1;
	}
	KS_YKT_Clt ykt;
	ykt.SetStringFieldByName("sname",(char*)cardverno.c_str());
	ykt.SetIntFieldByName("lvol5",KsYktSvrUtil::global_cfg_->termid_);
	ykt.SetIntFieldByName("lvol1",50);
	if(ykt.SendRequest(950007,10000))
	{
		int retcode = ykt.GetReturnCode();
		if(retcode == 0)
		{
			// update black card
			int row = 0;
			while(ykt.HasMoreRecord())
			{
				CardVerInfo cardver;
				char temp[64] = {0};
				ykt.GetNextPackage();
				ykt.GetIntFieldByName("lvol2",&(cardver.cardno_));
				int flag;
				ykt.GetIntFieldByName("lvol3",&flag);
				if(flag == 0)
					cardver.flag_ = CARDSTATUS_LOST;
				else
					cardver.flag_ = CARDSTATUS_NORMAL;
				ykt.GetStringFieldByName("sname",temp,14);
				cardver.cardverno_ = temp;
				retcode = infodb.AddNewCard(cardver);
				if(retcode)
				{
					wxLogError(wxT("同步黑名单保存失败"));
					return -1;
				}
				++row;
			}
			if(row > 0)
			{
				wxString info = wxString::Format(wxT("同步系统黑名单,[%d]条"),row);
				wxLogMessage(info);
				return 0;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			wxString err = wxString::Format("同步系统黑名单失败 %d:",retcode);
			err += ykt.GetReturnMsg(NULL);
			wxLogError(err);
			return -1;
		}
	}
	KsYktSvrUtil::isYKTSvrOK_  = 0;
	return -2;
}
int KsYktSvrUtil::UploadSerial()
{
	if(IsYKTSvrOK())
		return -2;
	TransDB &transdb = KsCardProcessor::instance()->GetTransDB();
	const int max_per_trans = 10;
	int reccnt;
	if(transdb.CheckTransDtl())
		return -1;
	for(reccnt = 0;reccnt < max_per_trans; ++reccnt)
	{
		KS_YKT_Clt ykt;
		KsCardMsg trans;
		trans.Reset();
		int ret;

		ret = transdb.GetTransDtl(trans);
		if(ret==0)
		{
			std::string sValue;
			int iValue;
			

			trans.GetStrPara("data.devphyid",sValue);
			ykt.SetStringFieldByName("sphone3",(char*)sValue.c_str());

			trans.GetIntPara("data.termseqno",&iValue);
			ykt.SetIntFieldByName("lvol4",iValue);

			trans.GetIntPara("data.cardno",&iValue);
			ykt.SetIntFieldByName("lvol5",iValue);

			trans.GetIntPara("data.befbala",&iValue);
			ykt.SetIntFieldByName("lvol9",iValue);
			int cardbefbal = iValue;
	
			int amount = 0;
			trans.GetIntPara("data.amount",&amount);
			int cardaftbal = cardbefbal - amount;
	
			ykt.SetIntFieldByName("lvol8",amount);
			ykt.SetIntFieldByName("lvol10",cardaftbal);

			trans.GetStrPara("data.termdate",sValue);
			ykt.SetStringFieldByName("spost_code",(char*)sValue.substr(2).c_str());

			trans.GetStrPara("data.termtime",sValue);
			ykt.SetStringFieldByName("spost_code2",(char*)sValue.c_str());

			iValue = 0;
			trans.GetIntPara("data.paycnt",&iValue);
			ykt.SetIntFieldByName("lvol7",iValue+1); // 上传交易后的次数

			iValue = 0;
			trans.GetIntPara("data.shopid",&iValue);
			ykt.SetIntFieldByName("lvol3",iValue);

			iValue = 0;
			trans.GetIntPara("data.managefee",&iValue);
			ykt.SetIntFieldByName("lvol1",iValue);

			trans.GetStrPara("data.samno",sValue);
			ykt.SetStringFieldByName("sstation0",(char*)sValue.c_str());

			iValue = 0;
			trans.GetIntPara("data.status",&iValue);
			int transcode;
			trans.GetIntPara("data.transcode",&transcode);

			if(transcode == TC_CANCELPURCHASE)
			{
				if(iValue == DTLST_SUCCESS)
					iValue = DTLST_CANCEL;
			}
			ykt.SetIntFieldByName("lvol12",iValue);

			ykt.SetIntFieldByName("lvol11",1);
			ykt.SetIntFieldByName("lserial1",2);

			if(ykt.SendRequest(950156,10000))
			{
				int retcode = ykt.GetReturnCode();
				if(retcode == 0)
				{
					ret = transdb.ConfirmTransDtl(trans);
					if(ret==0)
					{
						// OK 
						continue;
					}
					else if(ret == 1)
					{
						// not found ,continue
						continue;
					}
					else
					{
						// error
						wxLogError(wxT("确认流水上传失败"));
						return -1;
					}
				}
				else
				{
					wxString err = wxString::Format("上传流水失败 %d:",retcode);
					err += ykt.GetReturnMsg(NULL);
					wxLogError(err);
					return -1;
				}
			}
			else
			{
				KsYktSvrUtil::isYKTSvrOK_  = 0;
				return -2;
			}
		}
		else if(ret == 1)
		{
			// 无流水
			if(reccnt > 0)
			{
				wxString info = wxString::Format(wxT("上传流水完成，[%d]条 "),reccnt);
				wxLogMessage(info);
				return 1;
			}
			return 1;
		}
		else
		{
			wxString info = wxT("上传流水失败 ");
			info += transdb.GetErrInfo();
			wxLogError(info);
			return -1;
		}
	}
	return 0;
}
int KsYktSvrUtil::ChkHeartBeat()
{
	if(IsYKTSvrOK())
		return -2;
	KS_YKT_Clt ykt;
	if(ykt.SendRequest(950009,1000))
	{
		int retcode = ykt.GetReturnCode();
		if(retcode)
			return -1;
		return 0;
	}
	return -2;
}
int KsYktSvrUtil::LoginDevice(KsCardMsg &msg)
{
	if(IsYKTSvrOK())
		return -2;
	int termid,shopid;
	std::string devphyid,cardverno,samno;
	char shopname[100]={0};

	if(!msg.GetIntPara("data.termid",&termid))
		return -1;

	//if(!msg.GetStrPara("data.cardverno",cardverno))
	//	return -1;
	
	if(!msg.GetStrPara("data.samno",samno))
		return -1;
	KS_YKT_Clt ykt;
	ykt.SetIntFieldByName("lwithdraw_flag",termid);
	ykt.SetStringFieldByName("sserial0",(char*)samno.c_str());

	if(ykt.SendRequest(850003,1000))
	{
		int retcode = ykt.GetReturnCode();
		if(retcode ==0)
		{
			if(ykt.GetNextPackage())
			{
				ykt.GetIntFieldByName("lvol3",&shopid);
				ykt.GetStringFieldByName("sall_name",shopname,sizeof(shopname)-1);
				msg.SetIntPara("data.shopid",shopid);
				msg.SetStrPara("data.shopname",shopname);
				msg.SetStrPara("data.devphyid",samno);
				return 0;
			}
			wxLogError(wxT("签到无返回"));
		}
		else
		{
			wxString info = wxString::Format("签到失败: %d ",retcode);
			info += ykt.GetReturnMsg(NULL);
			wxLogError(info);
		}
	}
	else
	{
		wxString info = wxString::Format("发送签到请求失败: ");
		info += ykt.GetReturnMsg(NULL);
		wxLogError(info);
		KsYktSvrUtil::isYKTSvrOK_  = 0;
		return -2;
	}
	return -1;
}