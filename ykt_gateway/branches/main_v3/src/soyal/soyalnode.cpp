/**
* V1.2 �޸����豸�ڵ� toplogic ��ʼ������
*/
#include "soyal/soyal_pub.h"
#include "soyal/soyalnode.h"
#include "ksgateway.h"
#include "netutil.h"
#include "xutils/xstring.h"
#include "task_scheduler.h"
#include "impl/schdimpl.h"
#include "osutil.h"
#include "execimpl.h"
#include <ace/Test_and_Set.h>
#include <ace/Null_Mutex.h>
#include <ace/SOCK_Connector.h>
#include <ace/OS.h>
#include "pubfunc.h"
#include <curl/curl.h>

#define KSG_SOYAL_DEV	"soyal"

static int delmaxtime = 0;
static int downmaxtime = 0;

using namespace SOYALDEV;

typedef struct {
	int soyal_event_code;
	char ecodedef[64];
}SOYAL_Event_Code_Def_t;

static const SOYAL_Event_Code_Def_t g_event_defs[]={
	{0,"��Ƭ�����"},
	{1,"λַ�������"},	
	{2,"������"},					
	{3,"�Ƿ���"},					
	{4,"ʱ�δ���"},					
	{5,"�������"},					
	{6,"��Ƭ�ѹ���"},
	{8,"�������"},
	{9,"�������"},		
	{10,"�������"},
	{11,"ˢ������"},	
	{14,"�������뾯��"},
	{15,"�����˳�����"},
	//{16,"�����Ű�ť"},
	{17,"��������"},
	{20,"�����ص�Դ"},
	{24,"��������Դ"},
	{28,"���������"},
	{19,"DI״̬�ı�"},
	{30,"Υ����������"},
	{31,"��������"},
	{32,"��������"},
	{52,"ˢ����δ��"},
	{53,"�������༭״̬"},
	{SOYAL_EVENT_CODE_END,"δ����"}
};

bool SOYAL_event_code_bsave(const SOYAL_Event_Code_Def_t *defs,int event_code)
{
	int i = 0;
	while(defs[i].soyal_event_code != SOYAL_EVENT_CODE_END)
	{
		if(event_code == defs[i].soyal_event_code)
			return true;
		i++;
	}
	return false;
}


#ifdef KSG_SOYAL_SUPPORT


// ע��soyal�����͹���
KSG_REG_FACTORY_INTERFACE(KSG_SOYAL_DEV,KSGSOYALDevInterfaceFactory);

// ע��soyal�豸����
KSG_REG_DEVICE_OBJECT(KSG_SOYAL_DEV,KSG_SY_716E,SOYALDevice);
KSG_REG_DEVICE_OBJECT(KSG_SOYAL_DEV,KSG_SY_721H,SOYALReader);

#endif // KSG_SOYAL_SUPPORT

bool SOYALReader::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
	return false;
}

int SOYALReader::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	return 1;
}

int SOYALReader::close_handler(KSGDeviceNode* node,ACE_HANDLE handler)
{
	return 1;
}

bool SOYALDevice::Accept(BaseVisitor& guest,KSGDeviceNode* visitor)
{
//	if(typeid(guest) == typeid(KSGTaskCollHeartBeat::CollHeartBeatVisitor))
//	return true;

	if(typeid(guest) == typeid(KSGTaskCollectSerial::CollectSerialVisitor))
		return true;

	if(typeid(guest) == typeid(KSGTaskDoorBatchDlCard::BatchDownloadCardVisitor))
		return true;
	
	return false;
}

int SOYALDevice::make_handler(KSGDeviceNode* node,ACE_HANDLE* handler)
{
	if(!node)
		return -1;
	std::string ip = node->GetDevAddr().GetConnect();
	int port = node->GetDevAddr().GetPort();
	ACE_INET_Addr addr(port,ip.c_str());
	ACE_SOCK_Connector conn;
	ACE_SOCK_Stream stream;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	int err_code;
	ACE_DEBUG((LM_TRACE,"��ʼ����soyal��������[%s][%s]",node->get_name().c_str(),ip.c_str()));
	if(conn.connect(stream,addr,&tv))
	{
		err_code = ACE_OS::last_error();
		// TODO: �������ӵĴ�����
		if(EWOULDBLOCK == err_code)
		{
			ACE_DEBUG((LM_ERROR,"���ӿ�����ʧ��"));
		}
		else if(EHOSTUNREACH == err_code || ENETUNREACH == err_code)
		{
			ACE_DEBUG((LM_ERROR,"�޷������豸����"));
			node->SetState(KSGDeviceNode::dsError);
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"��������δ֪����![%d][%s]ip[%s]"
				,err_code,ACE_OS::strerror(err_code),ip.c_str()));
		}
		// add by cash �ͷ� SOCKET 
		// 2007-01-29
		stream.close();
		return -1;
	}
	// ���� handler Ϊ BLOCK ��
	// stream.disable(ACE_NONBLOCK);
	// ���� linger ����
	struct linger lg;
	ACE_OS::memset(&lg,0,sizeof lg);
	lg.l_onoff = 1;
	// 3s 
	lg.l_linger = 3;
	stream.set_option(SOL_SOCKET,SO_LINGER,&lg,sizeof lg);
	node->SetState(KSGDeviceNode::dsOnline);
	*handler = stream.get_handle();
	return 0;
}

int SOYALDevice::close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ()
{
	if(node->GetConnType() != KSGDeviceURL::dctTCP)
		return 1;
	try
	{
		ACE_OS::closesocket(handler);
		return 0;
	}
	catch(...)
	{
		// catch all
		ACE_DEBUG((LM_ERROR,"�ر������Ž� Handler ʧ��"));
		return -1;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////
int SOYALDeviceLoader::Finish(KSGDeviceManager* manager)
{
	KSGDeviceManager::DeviceList * devs = manager->GetDevices();
	//std::for_each(devs->begin(),devs->end(),
	//	boost::bind(&HDDeviceLoader::SetupDeviceNoticeTask,this,_1));
	// ����ָ����еķ���
	try
	{
		manager->Traseval(boost::bind(&SOYALDeviceLoader::SetupDeviceGroup,this,_1));
	}
	catch(KSGException&)
	{
		return -1;
	}
	return 0;
}

int SOYALDeviceLoader::LoadDevice(KSGDeviceManager* manager)
{
	ACE_DEBUG((LM_INFO,"��ʼ����SOYAL�豸..."));
	try
	{
		// modified by ����  2006-12-31
		// �޸� : ���豸�ڵ� toplogic �ĳ�ʼ��������������������
		// �����豸������ṹ��ϵ
		/*
		std::for_each(devs->begin(),devs->end(),
		boost::bind(&HDDeviceLoader::SetupDevice,this,manager,_1));
		*/
	}
	catch(...)
	{
	}
	return 0;
}

void SOYALDeviceLoader::SetupDeviceGroup(KSGDeviceNode* node)
{
	if(node->get_vendor() != KSG_SOYAL_DEV)
		return;
	node->connect_module(KSGDeviceNode::cm_short_conn);
	// ����Ҫ���� loop device ,
	if(node->GetDeviceType() == KSG_SY_716E)
	{
		KSG_Task_Queue *queue = Task_Queue_Pool::instance()->add_initial_queue(KSG_SCHEDULER_STATUS);
		if(queue)
		{
			// ���������豸
			if(queue->load_all_device(node))
			{
				ACE_DEBUG((LM_INFO,"�����豸ʧ�ܣ�"));
				throw KSGException();
			}
		}
		else
		{
			ACE_DEBUG((LM_WARNING,"�豸�޷������������,dev[%d]",node->GetDevId()));
		}
	}
}
//////////////////////////////////////////////////////////////////////
// SOYALDevInterfaceLoader
int SOYALDevInterfaceLoader::LoadInterface(KSGDeviceManager *manager)
{
	try
	{
		ACE_DEBUG((LM_INFO,"����SOYAL�豸�ӿ�........."));
		// Ϊ�豸�������ӽӿ�
		KSG_ADD_DEVICE_INTERFACE(KSG_SOYAL_DEV,KSG_SY_716E,ID_SOYAL_DL_Card);		
		KSG_ADD_DEVICE_INTERFACE(KSG_SOYAL_DEV,KSG_SY_716E,ID_SOYAL_CollectData);	
		KSG_ADD_DEVICE_INTERFACE(KSG_SOYAL_DEV,KSG_SY_716E,ID_SOYAL_DL_Week);
		KSG_ADD_DEVICE_INTERFACE(KSG_SOYAL_DEV,KSG_SY_721H,ID_SOYAL_Ctrl_Door);
		KSG_ADD_DEVICE_INTERFACE(KSG_SOYAL_DEV,KSG_SY_716E,ID_SOYAL_DL_Timer);
		KSG_ADD_DEVICE_INTERFACE(KSG_SOYAL_DEV,KSG_SY_716E,ID_SOYAL_UL_Timer);
		return 0;
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"����SOYAL�豸�ӿ�ʧ��.........."));
		return -1;
	}
}

int SOYALTaskExecutorLoader::LoadExecutor()
{
	// ע��ָ��ִ�д���ӿ�
	return 0;
}
//////////////////////////////////////////////////////////////////////
//

int ID_SOYAL_DL_Card::success_download(int list_id,int device_id)
{
	DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
	if(!drtp)
		return TASK_ERR_EXECUTE;
	if(drtp->Connect())
	{
		// ����ʧ��
		return 1;
	}
	drtp->SetRequestHeader(KSG_DOWNLOAD_CARDLIST);
	drtp->AddField(F_LVOL0,device_id);	
	drtp->AddField(F_LVOL2,list_id); // for update
	drtp->AddField(F_LVOL3,1);
	drtp->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);			// ��ϵͳ��
	
	if(drtp->SendRequest(2000))
	{
		if(drtp->GetReturnCode())
			ACE_DEBUG((LM_ERROR,"������Ա����ʧ��[%d]",drtp->GetReturnCode()));
		return TASK_ERR_EXECUTE;
	}

	return TASK_SUCCESS;
}
int ID_SOYAL_DL_Card::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret,i,j,t,interval;
	char tmp[20]="";
	char temp[3]="";
	BYTE bitctl=0;
	char pre_phyno[12]="";
	char exp_date[9]="";
	int list_id,cardaddr,retries,ipasswd;
	//std::string phyno;
	std::list<DownCard_info> card_list;
	unsigned long pre_time,now;	
	

	ACE_HANDLE handler = task->_handle;
	// ����
	int nodeid = node->GetTermId();
	int devid = node->GetDevId();
	int cardtype = node->card_type();

	DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
	if(!drtp)
		return TASK_ERR_EXECUTE;
	if(drtp->Connect())
	{
		// ����ʧ��
		return 1;
	}
	drtp->SetRequestHeader(KSG_DOWNLOAD_CARDLIST);
	drtp->AddField(F_LVOL0,devid);
	ACE_DEBUG((LM_INFO,"soyal AR-716E device_id[%d]",devid));
	drtp->AddField(F_LVOL1,10);
	drtp->AddField(F_LVOL3,1);
	if(drtp->SendRequest(5000))
	{
		if(drtp->GetReturnCode())
			ACE_DEBUG((LM_ERROR,"��ѯ��Ա����ʧ��[%d]",drtp->GetReturnCode()));
		return TASK_ERR_EXECUTE;
	}
	
	DownCard_info info;
	memset(&info,0,sizeof info);
	memset(pre_phyno,0,sizeof pre_phyno);

	while(drtp->HasMoreRecord() )
	{
		ST_PACK *data = drtp->GetNextRecord();

		list_id = data->lvol0;
		memcpy(pre_phyno,data->sdate0,8);				// ������
		memcpy(exp_date,data->sdate1,8);				// ����ʱ��
		int doorcount = data->lvol10;					// ����
		cardaddr = data->lvol11;						// ��ַ(0--14999)
		ipasswd = atoi(data->stx_pwd);					// �������루���4λ��
		ACE_DEBUG((LM_INFO,"AR-716E���ؿ�����list_id[%d],doorcount[%d],phyno[%s]",list_id,doorcount,pre_phyno));
		
		if(strcmp(info.phyno,pre_phyno)!=0)
		{
			card_list.push_back(info);
			ACE_OS::strcpy(info.phyno,pre_phyno);
			
			// ��ʼ��
			info.cardaddr = -1;
			info.ipasswd = 0;
			info.delflag = false;
			memset(info.timezone,0,sizeof info.timezone);
			memset(info.mapping,0,sizeof info.mapping);
		}
        memset(tmp,0,sizeof tmp);
		memcpy(tmp,exp_date+2,2);
		info.expdate[0] = atoi(tmp);			// ��
		memcpy(tmp,exp_date+4,2);
		info.expdate[1] = atoi(tmp);			// ��
		memcpy(tmp,exp_date+6,2);
		info.expdate[2] = atoi(tmp);			// ��
		info.cardaddr = cardaddr;				// ��ַ
		info.ipasswd = ipasswd;					// ��������
		if(doorcount==0)						// ûһ���ſɽ���ɾ��
			info.delflag = true;
		else		// ���֧��16���ţ����Ŵ�1��ʼ���
		{
#ifdef KSG_SOYAL_4_BYTE
			for(i=0;i<16;i++)
			{
				bitctl = 0;
				memcpy(tmp,data->vsvarstr0+(i+1)*8,8);				// ��i����
				for (j=0;j<4;j++)
				{
					memcpy(temp,tmp+2*j,2);
					t = (int)strtoul(temp,NULL,16);
					if(t)
					{
						info.timezone[4*i+j] = t;
						bitctl = 1<<(i%8);
					}
				}
				info.mapping[i/8] |= bitctl;
			}
#else
			memcpy(tmp,data->vsvarstr0+1*2,2);				// ��1����
			int t = (int)strtoul(tmp,NULL,16);
			if(t != 0xFF)
			{
				info.timezone[0] = t+1;						// ʱ��Σ���1��ʼ
				info.mapping[0] = 1;
			}
			else
				info.mapping[0] = 0;

			for(i=2;i<=8;i++)								// 2--8 ��
			{
				memcpy(tmp,data->vsvarstr0+i*2,2);
				t = (int)strtoul(tmp,NULL,16);
				if(t != 0xFF)
				{
					info.timezone[i-1] = t+1;				
					info.mapping[0] |= 1 << (i-1);
				}
			}	

			memcpy(tmp,data->vsvarstr0+9*2,2);				// ��9����
			t = (int)strtoul(tmp,NULL,16);
			if(t != 0xFF)
			{
				info.timezone[8] = t+1;
				info.mapping[1] = 1;
			}
			else
				info.mapping[1] = 0;

			for(i=10;i<=16;i++)								// 10--16 ��
			{
				memcpy(tmp,data->vsvarstr0+i*2,2);
				t = (int)strtoul(tmp,NULL,16);
				if(t != 0xFF)
				{
					info.timezone[i-1] = t+1;				// ʱ���
					info.mapping[1] |= 1 << (i-9);
				}
			}
#endif
		}
	}
	if(ACE_OS::strlen(info.phyno)>0)
		card_list.push_back(info);
	
	
	//ACE_DEBUG((LM_INFO,"card_list size[%d]",card_list.size()));
	// ���ص��豸��
	memset(pre_phyno,0,sizeof pre_phyno);
	std::list<DownCard_info>::const_iterator iter = card_list.begin();
	for(;iter != card_list.end();++iter)
	{
		memset(&info,0,sizeof info);
		info = *iter;
		if(strlen(info.phyno) == 0)
			continue;
		retries = 3;
		if(info.delflag)			// ɾ��
		{
			//pre_time = ACE_OS::gettimeofday().msec();
			//time(&pre_time);
			pre_time = GetTickCount();
			while(retries-->0)
			{
				ret = ClearCardData(handler,nodeid,info.cardaddr);				// ɾ��������
				if(ret)
					continue;
				else
					break;
			}
			//time(&now);
			now = GetTickCount();
			//now = ACE_OS::gettimeofday().msec();
			interval = now- pre_time;
			ACE_DEBUG((LM_INFO,"ɾ��������ʱ[%d]milliseconds ",interval));
			if(interval >delmaxtime)
			{
				delmaxtime = now-pre_time;
				ACE_DEBUG((LM_INFO,"ɾ�����������ʱ[%d]milliseconds ",delmaxtime));
			}
			if(ret)
			{
				ACE_DEBUG((LM_ERROR,"ClearCardData errcode[%d],devid[%d],nodeid[%d],phycard[%s]",ret,devid,nodeid,info.phyno));
				return -1;
			}
		}
		else
		{
			//time(&pre_time);
			//pre_time = ACE_OS::gettimeofday().msec();
			pre_time = GetTickCount();
			retries = 3;
			while(retries-->0)
			{
				ret = SetCardData(handler,nodeid,info,cardtype);				// ���ؿ�����
				if(ret)
					continue;
				else
					break;
			}
			if(ret)													// ��������ʧ��
			{
				ACE_DEBUG((LM_ERROR,"SetCardData errcode[%d],devid[%d],nodeid[%d],phycard[%s]",ret,devid,nodeid,info.phyno));
				return -1;
			}

			retries = 3;
			while(retries-->0)
			{
				ret = SetGroupSet(handler,nodeid,info);				// ����ʱ���
				if(ret)
					continue;
				else
					break;
			}
			//time(&now);
			//now = ACE_OS::gettimeofday().msec();
			now = GetTickCount();
			interval = now- pre_time;
			ACE_DEBUG((LM_INFO,"����������ʱ[%d]milliseconds ",interval));
			if(interval >downmaxtime)
			{
				downmaxtime = now-pre_time;
				ACE_DEBUG((LM_INFO,"�������������ʱ[%d]milliseconds ",downmaxtime));
			}
			if(ret)
			{
				ACE_DEBUG((LM_ERROR,"SetGroupSet errcode[%d],devid[%d],nodeid[%d],phycard[%s]",ret,devid,nodeid,info.phyno));
				return -1;
			}
		}
		
		if(success_download(list_id,devid))
		{
			ACE_DEBUG((LM_ERROR,"���������ɹ���Ӧ��ϵͳʧ�ܣ�dev[%d],����[%s]",devid,info.phyno));
			return TASK_ERR_EXECUTE;
		}
		ACE_DEBUG((LM_INFO,"�´������ɹ� AR-716E[%d]����[%s]",devid,info.phyno));

	}

	if(card_list.size() == 0)
	{
		ACE_DEBUG((LM_INFO,"AR-716E[%d]������������",devid));
	}
	return TASK_SUCCESS;
}

int ID_SOYAL_CollectData::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret = 0;
	int event_code = 0;
	bool bsave = false;
	char txmark[5]="";
	KSGDeviceNode *task_node = task->GetDeviceNode();
	ACE_ASSERT(task_node != NULL);

	ACE_HANDLE handler = task->_handle;
	// ����
	int nodeid = node->GetTermId();
	int devid = node->GetDevId();
	int cardtype = node->card_type();
	
	CtrlMsg ctrlmsg;
	for(int i=0;i<20;i++)		
	{
		ret = ReadCtrlMsg(handler,nodeid,ctrlmsg,cardtype);
		if(ret)
		{
			if(ret==-2)		// ��ˮ�ɼ�����
				return 0;

			ACE_DEBUG((LM_ERROR,"ReadCtrlMsg errcode[%d],devid[%d],nodeid[%d]",ret,devid,nodeid));
			return ret;
		}
		bsave = SOYAL_event_code_bsave(g_event_defs,ctrlmsg.txmark);
		if(bsave)
		{
			DRTPPoolType::SmartObject drtp = KsgGetDrtpPool()->Alloc();
			if(!drtp)
				return TASK_ERR_EXECUTE;
			if(drtp->Connect())
			{
				// ����ʧ��
				return 1;
			}
			drtp->SetRequestHeader(930203);
			drtp->AddField(F_LVOL2,devid);				// ������id��
			drtp->AddField(F_LVOL1,ctrlmsg.termid);						// ��ͷ��
			drtp->AddField(F_SDATE1,ctrlmsg.phyno);						// ������
			drtp->AddField(F_SDATE0,ctrlmsg.date);	
			drtp->AddField(F_STIME0,ctrlmsg.time);
			//sprintf(txmark,"%d",ctrlmsg.txmark);						// ˢ���¼�
			//event_code = SOYAL_event_code_2_ks_event(g_rac_event_defs,ctrlmsg.txmark);
			drtp->AddField(F_SEMP_NO,ctrlmsg.txmark);
			drtp->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);	//sys_id
			if(drtp->SendRequest(5000))
			{
				if(drtp->GetReturnCode())
					ACE_DEBUG((LM_ERROR,"�ϴ�ˢ����Ϣʧ��,�豸[%d]������[%d]"
					,devid,drtp->GetReturnCode()));
				return TASK_ERR_EXECUTE;
			}
		}
		
		ret = DeleteCtrlMsg(handler,nodeid);
		if(ret)
		{
			ACE_DEBUG((LM_ERROR,"DeleteCtrlMsg errcode[%d],devid[%d],nodeid[%d]",ret,devid,nodeid));
			return ret;
		}
		
		ACE_DEBUG((LM_DEBUG,"���������Ž���ˮ�ɹ�,devid[%d],nodeid[%d]",devid,nodeid));
	}
	return TASK_SUCCESS;
}

TimeSec ID_SOYAL_DL_Week::GetTimeSect(std::string time_str)
{
	char time_hh[3]="",time_mm[3]="";
	TimeSec timesec;
	memset(&timesec,0,sizeof timesec);
    if(time_str.length()==8)
	{
    	time_str.copy(time_hh,2);
    	time_str.copy(time_mm,2,2);
    	timesec.begin_time = atoi(time_hh)*60 + atoi(time_mm);		// ��ʼʱ�䣨���ӣ�		
    	time_str.copy(time_hh,2,4);
    	time_str.copy(time_mm,2,6);
    	timesec.end_time = atoi(time_hh)*60 + atoi(time_mm);		// ����ʱ�䣨���ӣ�
    }
	return timesec;
}
int ID_SOYAL_DL_Week::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret = 0;
	int seqno = 0,link = 0,time_level=0;
	TimeGroup timegroup;
	std::string time_sect;

	memset(&timegroup,0,sizeof timegroup);
	ACE_HANDLE handler = task->_handle;
	int nodeid = node->GetTermId();						// ����
	int devid = node->GetDevId();

	try
	{
		seqno = task->GetParams().GetParamIntVal(XML_KEY_SEQNO);				// ʱ��α�ţ���1��ʼ
		link = task->GetParams().GetParamIntVal("LINK");						// ������һ��ʱ��
		time_level = task->GetParams().GetParamIntVal(XML_KEY_WORKMODE);		// level,1:����ʱ�Σ�2���ǹ���ʱ��
		
		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY1);
		timegroup.mon_timesec = GetTimeSect(time_sect);							// ��һ

		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY2);
		timegroup.tues_timesec = GetTimeSect(time_sect);						// �ܶ�
		
		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY3);
		timegroup.wed_timesec = GetTimeSect(time_sect);							// ����

		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY4);
		timegroup.thur_timesec = GetTimeSect(time_sect);						// ����

		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY5);
		timegroup.fri_timesec = GetTimeSect(time_sect);							// ����

		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY6);
		timegroup.sat_timesec = GetTimeSect(time_sect);							// ����

		time_sect = task->GetParams().GetParam(XML_KEY_WEEK_DAY7);
		timegroup.sun_timesec = GetTimeSect(time_sect);							// ����		
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}

	ret = SetTimeZone(handler,nodeid,seqno,link,time_level,timegroup);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"SetTimeZone errcode[%d],devid[%d],nodeid[%d]",ret,devid,nodeid));
		return ret;
	}

	ACE_DEBUG((LM_DEBUG,"SetTimeZone sucess,devide[%d],nodeid[%d],seqno[%d],link[%d]",devid,nodeid,seqno,link));
	return TASK_SUCCESS;
}

int ID_SOYAL_Ctrl_Door::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret=0,flag;
	try
	{
		flag = task->GetParams().GetParamIntVal(XML_KEY_FTFLAG);
	}
	catch (...)
	{
		return TASK_ERR_PARAM;
	}

	ACE_HANDLE handler = task->_handle;
	int reader = node->GetTermId();								// ��ͷ

	KSGDeviceNode *task_parent = node->GetParent();
	ACE_ASSERT(task_parent != NULL);
	int nodeid = task_parent->GetTermId();						// ����������
	int devid = task_parent->GetDevId();

	ret = CtrlReader(handler,nodeid,reader,flag);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"CtrlReader errcode[%d],ctrldevid[%d],ctrlid[%d],reader[%d]",ret,devid,nodeid,reader));
		return ret;
	}

	ACE_DEBUG((LM_DEBUG,"����Զ�̿��Ƴɹ�,ctrldevid[%d],ctrlid[%d],reader[%d]",devid,nodeid,reader));
	return TASK_SUCCESS;
}

void ID_SOYAL_DL_Timer::GetDatetime(std::string date_str,Datetime_str &datetime)
{
	char tmp[3]="";
	time_t t;
	struct tm tm_t,*ptm=NULL;
	memset(&tm_t,0,sizeof tm_t);

	date_str.copy(tmp,2);
	datetime.year = atoi(tmp);

	date_str.copy(tmp,2,2);
	datetime.mon = atoi(tmp);

	date_str.copy(tmp,2,4);
	datetime.day = atoi(tmp);

	date_str.copy(tmp,2,6);
	datetime.hr = atoi(tmp);

	date_str.copy(tmp,2,8);
	datetime.min = atoi(tmp);

	date_str.copy(tmp,2,10);
	datetime.sec = atoi(tmp);

	tm_t.tm_year = 100 + datetime.year;
	tm_t.tm_mon = datetime.mon -1;
	tm_t.tm_mday = datetime.day;
	tm_t.tm_hour=datetime.hr;
	tm_t.tm_min=datetime.min;
	tm_t.tm_sec=datetime.sec;

	t = ACE_OS::mktime(&tm_t);
	ptm = ACE_OS::localtime(&t);
	datetime.week = (ptm->tm_wday+1)%7;
}

int ID_SOYAL_DL_Timer::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret=0;
	Datetime_str datetime;

	ACE_HANDLE handler = task->_handle;
	int nodeid = node->GetTermId();		
	int devid = node->GetDevId();

	
	std::string sys_clock;
	try
	{
		sys_clock = task->GetParams().GetParam(XML_KEY_CLOCK);
	}
	catch (...)
	{
		TASK_ERR_PARAM;
	}
	
	/*
	time_t now = ACE_OS::gettimeofday().sec();
	struct tm* tv = ACE_OS::localtime(&now);

	datetime.sec = tv->tm_sec;
	datetime.min = tv->tm_min;
	datetime.hr = tv->tm_hour;
	datetime.week = (tv->tm_wday+1)%7;
	datetime.day = tv->tm_mday;
	datetime.mon = tv->tm_mon+1;
	datetime.year = (tv->tm_year + 1900)%2000;
	*/

	GetDatetime(sys_clock,datetime);
	ret = SetCtrlTime(handler,nodeid,datetime);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"SetCtrlTime errcode[%d],devid[%d],ctrlid[%d]",ret,devid,nodeid));
		return ret;
	}

	ACE_DEBUG((LM_DEBUG,"SetCtrlTime sucess,devid[%d],ctrlid[%d]",devid,nodeid));
	
	return TASK_SUCCESS;
}

int ID_SOYAL_UL_Timer::ExecuteTask(KSGDeviceNode* node,Task* task)
{
	int ret=0;
	char date_time_buf[15] = "";
	Datetime_str datetime;

	KSGTaskResponse &resp = task->GetResponse();
	ACE_HANDLE handler = task->_handle;
	int nodeid = node->GetTermId();		
	int devid = node->GetDevId();

	ret = GetCtrlTime(handler,nodeid,datetime);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"GetCtrlTime errcode[%d],devid[%d],ctrlid[%d]",ret,devid,nodeid));
		return ret;
	}

	sprintf(date_time_buf,"20%02d%02d%02d%02d%02d%02d",datetime.year,datetime.mon,datetime.day,
		datetime.hr,datetime.min,datetime.sec);
	resp.AddField(XML_KEY_CLOCK,date_time_buf+2);

	ACE_DEBUG((LM_DEBUG,"GetCtrlTime sucess,devid[%d],ctrlid[%d],datetime[%s]",devid,nodeid,date_time_buf));
	return TASK_SUCCESS;
}