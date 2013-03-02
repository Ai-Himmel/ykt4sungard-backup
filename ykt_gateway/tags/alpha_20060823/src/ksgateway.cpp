#include "stdafx.h"
#include "ksglobal.h"
#include "ksgateway.h"
#include <ostream>
#include <sstream>
#include <functional>
#include <algorithm>
#include <boost/function.hpp>
#include <xutils/functor.h>
#include <CIniFile.h>
#include <ace/Trace.h>
#include <ace/Configuration.h>
#include <ace/Configuration_Import_Export.h>
#include "smartpool.h"
#include "netutil.h"
#include "osutil.h"
#include "scheduler.h"
#include "impl/schdimpl.h"
#include "device.h"
#include "deviceinterface.h"
#include "xutils/xstring.h"
#include "ace/Reactor.h"
#include "logcallback.h"
#include "des.h"
//////////////////////////////////////////////////////////////////////////
//

//<! ȫ�� DRTP �����
ResourcePool<CDRTPHelper> theDrtpPool;
//<! ȫ��ǰ�û�����
KSGateway* theGlobalGateWay = NULL;

int KsgStartServer(KSGateway* gateway)
{
	theGlobalGateWay = gateway;
	return theGlobalGateWay->run();
}
//////////////////////////////////////////////////////////////////////////
// KSGConfig
KSGConfig::KSGConfig()
{
	//
	KSGOSUtil::GetBaseDir(_basedir);
	_basedir = KSGOSUtil::GetPathName(_basedir);
}
KSGConfig::~KSGConfig()
{
	//
}

int KSGConfig::loadConfig(const std::string& filename)
{
	ACE_Configuration_Heap config;
	if(config.open() == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	ACE_Ini_ImpExp config_importer(config);

	if(config_importer.import_config(filename.c_str()) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}

	ACE_Configuration_Section_Key section;
	if(config.open_section(config.root_section(),ACE_TEXT(KSG_COMMON_SECT)
		,0,section) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	
	ACE_TString v;

	if(config.get_string_value(section,ACE_TEXT(KSG_MAJOR_VER),v) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	_majorVer = ACE_OS::atoi(v.c_str());
	if(config.get_string_value(section,KSG_MINOR_VER,v) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	_minorVer = ACE_OS::atoi(v.c_str());

	if(config.open_section(config.root_section(),ACE_TEXT(KSG_SERVER_SECT)
		,0,section) == -1 )
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);

	
	if(config.get_string_value(section,KSG_SVR_IP,v) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	_drtpSvrIP = v.c_str();
	if(config.get_string_value(section,KSG_SVR_PORT,v) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	_drtpSvrPort = ACE_OS::atoi(v.c_str());
	if(config.get_string_value(section,KSG_SVR_BRANCE_NO,v) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	_drtpNo = ACE_OS::atoi(v.c_str());
	if(config.get_string_value(section,KSG_SVR_MAINFUNC,v) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	_drtpMainFunc = ACE_OS::atoi(v.c_str());
	if(config.get_string_value(section,KSG_SVR_POOL_CONN,v) == -1)
		_drtpPoolMaxCnt = 5;
	else
		_drtpPoolMaxCnt = ACE_OS::atoi(v.c_str());
	if(_drtpPoolMaxCnt < 0)
		_drtpPoolMaxCnt = 5;
	if(_drtpPoolMaxCnt > 30)
		_drtpPoolMaxCnt = 30;

	if(config.open_section(config.root_section(),ACE_TEXT(KSG_GATEWAY_SECT)
		,0,section) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);

	if(config.get_string_value(section,KSG_GW_IP,v) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	_localIP = v.c_str();

	if(config.open_section(config.root_section(),ACE_TEXT(KSG_SCHEDULER_SECT)
		,0,section) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);

	_runTaskIds = "";
	if(config.get_string_value(section,KSG_SCHD_IDS,v) != -1)
	{
		_runTaskIds = v.c_str();
	}

	if(config.open_section(config.root_section(),ACE_TEXT(KSG_LOG_SECT)
		,0,section) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡ��־����ʧ��")),-1);
	if(config.get_string_value(section,KSG_LOG_LEVEL,v)!=-1)
	{
		_logLevel = v.c_str();
	}
	if(config.get_string_value(section,KSG_LOG_APPENDER,v)!=-1)
	{
		_logOutput = v.c_str();
	}
	if(config.get_string_value(section,KSG_LOG_FILE,v)!=-1)
	{
		_logFilePath = v.c_str();
	}
	
	if(config.get_string_value(section,KSG_LOG_FILEMAX,v) != -1)
	{
		_log_max_file_size = ACE_OS::atoi(v.c_str());
		if(_log_max_file_size == 0)
			_log_max_file_size = 1024;
		_log_max_file_size *= 1024;
		if(_log_max_file_size <= 0)
			_log_max_file_size = 1024 * 1024;
	}
	if(config.get_string_value(section,KSG_LOG_MAX_COUNT,v) !=-1)
	{
		_log_max_backup = ACE_OS::atoi(v.c_str());
		if(_log_max_backup == 0)
			_log_max_backup = 1;
	}
	_devType = "";
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// KSGGateway

KSGateway::KSGateway():_devManager(NULL),_status(stStop),_logBackend(NULL)
{
	// 
	_devManager = new KSGDeviceManager(this);
	_taskManager = new TaskManager;
	_schdObserver = new KSGSchedulerObserver(this);
}
KSGateway::~KSGateway()
{
	// ֹͣ���е�����
	SchedulerGroup::Instance().TerminateAll();
	// ɾ�����е��������
	SchedulerGroup::Instance().ClearAll();
	// ֹͣ���е��豸ָ�����
	_devgrpSchd.TerminateAll();
	_devgrpSchd.ClearAll();
	// �ͷ�һЩȫ����Դ
	if(_taskManager)
	{
		delete _taskManager;
	}
	if(_schdObserver)
	{
		delete _schdObserver;
	}
	//
	if(_devManager)
	{
		delete _devManager;
	}
}
CDRTPHelper * KSGateway::CreateDrtpHelper()
{
	return new CDRTPHelper(_configuration._drtpSvrIP.c_str()
		,_configuration._drtpSvrPort
		,_configuration._drtpMainFunc,_configuration._drtpNo);
}
int KSGateway::run()
{
	int ret = loadLocalConfig();
	if(ret)
		return ret;
	ret = setupLogSystem();
	if(ret)
		return ret;
	ACE_DEBUG((LM_INFO,"��ʼ����ǰ�û�..."));
	ACE_DEBUG((LM_INFO,"Ӧ�÷�����[%s:%d]func[%d]",_configuration._drtpSvrIP.c_str()
		,_configuration._drtpSvrPort,_configuration._drtpMainFunc));

	ret = setupDrtpPool();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"��ʼ��DRTP����ʧ��,������[%d]",ret));
		return ret;
	}
	
	ret = enroll();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"ǰ�û�ǩ��ʧ��,������[%d]",ret));
		return ret;
	}
	ret = downloadRuntimeParams();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"�������в���ʧ�ܣ�������[%d]",ret));
		return ret;
	}
	
	// ���� loop �豸
	ret = loadLoopDevice();
	if(ret)
	{
		return ret;
	}
	if("" != _configuration._devType)
	{
		// ֻ�е����豸ʱ,����Ҫ�������ó�ʼ��
		ret = loadDeviceType();
		if(ret)
		{
			return ret;
		}
		
		ret = setupAllDevices();
		if(ret)
		{
			return ret;
		}
	}
	else
	{
		ACE_DEBUG((LM_INFO,"ǰ�û�δ�����豸!"));
	}
	loadTaskExecutor();

	ret = startTimeScheduler();
	if(ret)
		return ret;
	
	ACE_DEBUG((LM_INFO,"����ǰ�û��ɹ�..."));
	// ������ѭ��
	_status = stRunning;
	int i = 0;
	while(_status == stRunning)
	{
		KSGThreadUtil::Sleep(5000);
		KSGThreadUtil::yield();
	}
	ACE_DEBUG((LM_INFO,"����ֹͣǰ�û�..."));
	SchedulerGroup::Instance().TerminateAll();
	_devgrpSchd.TerminateAll();
	ACE_DEBUG((LM_INFO,"���������н���"));
	exit();
	return 0;
}
int KSGateway::setupDrtpPool()
{
	CDRTPHelper::InitDrtp();

	boost::function0<DRTPPoolType::PointerType> func =
		boost::bind(&KSGateway::CreateDrtpHelper,this);
	theDrtpPool.Init(_configuration._drtpPoolMaxCnt,func);

	return 0;
}
int KSGateway::exit()
{
	_status = stStop;
	closeLogSystem();
	return 0;
}
int KSGateway::loadLocalConfig()
{
	return _configuration.loadConfig(KSGOSUtil::JoinPath(
		_configuration._basedir,"ksgateway.ini"));
}
int KSGateway::enroll()
{
	DRTPPoolType::SmartObject obj;
	ACE_DEBUG((LM_INFO,"��������ǩ��"));
	if(KSGNetUtil::GetMacByIP(_configuration._localIP,_configuration._localMac))
	{
		ACE_DEBUG((LM_ERROR,"��ȡIP[%s]��Ӧ��MAC��ַʧ��",
			_configuration._localIP.c_str()));
		return -2;
	}
	obj = KsgGetDrtpPool()->Alloc();
	obj->SetRequestHeader(KSG_DRTP_ENROLL,1);
	obj->AddField(F_SCUST_LIMIT,_configuration._localIP.c_str());	// IP
	obj->AddField(F_SCUST_LIMIT2,_configuration._localMac.c_str()); // MAC
	if(obj->Connect())
	{
		ACE_DEBUG((LM_ERROR,"DRTP����ʧ�ܣ���������"));
		return -1;
	}
	if(!obj->SendRequest(3000))
	{
		if(obj->HasMoreRecord())
		{
			// ǩ���ɹ� ����ȡǰ�û����붯̬��Կ
			ST_PACK * data = obj->GetNextRecord();
			_configuration._gwId = data->lvol0;
			_configuration._dynaKey = data->scust_limit;
		}
		return 0;
	}
	ACE_DEBUG((LM_ERROR,"����ǩ��ʧ��,������Ϣ[%s]",obj->GetErrMsg().c_str()));
	return -1;
}
int KSGateway::downloadRuntimeParams()
{
	DRTPPoolType::SmartObject obj;
	ACE_DEBUG((LM_INFO,"�����������в���"));
	obj = KsgGetDrtpPool()->Alloc();
	obj->SetRequestHeader(KSG_DRTP_DW_PARAMS,1);
	obj->AddField(F_LVOL0,_configuration._gwId); // ǰ�û�ID
	obj->AddField(F_SCUST_LIMIT,_configuration._dynaKey.c_str()); // ��̬��Կ
	if(obj->Connect())
	{
		return -1;
	}
	if(obj->SendRequest(3000))
	{
		return -1;
	}
	else if(obj->GetReturnCode())
	{
		ACE_DEBUG((LM_ERROR,"����ǰ�û����в���ʧ��[%s]",obj->GetReturnMsg().c_str()));
		return -1;
	}
	if(obj->HasMoreRecord())
	{
		ST_PACK * data = obj->GetNextRecord();
		// �������е����в���
		_configuration._heartbeat = data->lvol0;
		_configuration._heartbeatIntval = data->lvol1;
		_configuration._heartbeatFuncNo = data->lvol2;
		//_configuration._drtpQueueNo = data->lvol3;
		_configuration._taskRecvFuncNo = data->lvol3;
		_configuration._taskResponseFuncNo = data->lvol9;
		if(_configuration._taskRecvFuncNo <= 0
			|| _configuration._taskResponseFuncNo <= 0)
			return -1;
		_configuration._execTimeout = data->lvol4;
		_configuration._devType = data->sdate0;
		// FIXME : unicode
		_configuration._devMode = atoi(data->sstatus1);
		_configuration._startDBTime = data->sname;
		_configuration._serialIntval = data->lvol5;
		_configuration._drtpGetDevFuncNo = data->lvol6;
		_configuration._taskQueueMaxWaiting = data->lvol7;
		_configuration._taskRecvIntval = data->lvol8;

		// Ϊ������Կ
		char enkey[17] = "";
		unsigned char hexkey[17] = "";
		unsigned char hexenkey[17] = "";
		xutil::StringUtil::Str2Hex(data->sname2,hexkey,8);
		if(decrypt_work_key(hexkey,hexenkey) != 0)
		{
			ACE_DEBUG((LM_ERROR,"��ѹ������Կʧ��"));
			return -1;
		}
		xutil::StringUtil::Hex2Str(hexenkey,8,enkey);
		_configuration._cardKey = enkey;
		// FIXME: �����˻���豸ʹ�õĹ�����Կ
		_configuration._workKey = "ffffffffffffffff";
		return 0;
	}
	ACE_DEBUG((LM_ERROR,"δ���ص�����[%s]",obj->GetReturnMsg().c_str()));
	return -1;
}
int KSGateway::setupAllDevices()
{
	DRTPPoolType::SmartObject obj;
	int ret;
	
	ACE_DEBUG((LM_INFO,"�����豸����"));
	KSGDeviceLoader * loader = NULL; 
	KSGDeviceInterfaceLoader * iloader = NULL;
	obj = KsgGetDrtpPool()->Alloc();
	obj->SetRequestHeader(_configuration._drtpGetDevFuncNo,1);
	obj->AddField(F_LCERT_CODE,_configuration._gwId); // ID
	obj->AddField(F_SCUST_LIMIT2,_configuration._dynaKey.c_str()); // dynamic
	if(obj->Connect())
	{
		return -1;
	}
	if(obj->SendRequest(3000))
	{
		ACE_DEBUG((LM_ERROR,"�����豸����ʧ��"));
		return -1;
	}
	else if(obj->GetReturnCode())
	{
		ACE_DEBUG((LM_ERROR,"�����豸����ʧ��[%s]",obj->GetReturnMsg().c_str()));
		return -1;
	}
	int devcnt = 0;
	if(obj->HasMoreRecord())
	{
		while(obj->HasMoreRecord())
		{
			ST_PACK * data = obj->GetNextRecord();
			// ��ȡ�豸�Ĳ���
			NormalDeviceType dt = data->semp;
			std::string devphyid = data->sname;
			std::string ipaddr = data->sname2;
			char addr[256];
			int devport = data->lvol2;
			try
			{
				ACE_DEBUG((LM_DEBUG,"�豸[%d]����[%s]����ID[%s]����[%d]"
					,data->lvol0,dt.c_str(),devphyid.c_str(),devport));
				DeviceNodeType * device = _devManager->NewDevice(data->lvol0,data->lvol1,devphyid,dt);
				// FIXME: ��Ϊ���е��豸����TCP/IPͨѶ��ʽ��
				// �豸��ַ��Ϣ
				ACE_OS::sprintf(addr,"dev:TCP:%s//%d@%s:%d",_configuration._devType.c_str()
					,devport,ipaddr.c_str(),data->lvol4);
				device->SetAddrUrl(addr);
				// �豸����
				device->SetTermId(data->lvol3);
				devcnt++;
			}
			catch (DeviceIdAlreadyExists&)
			{
				ACE_DEBUG((LM_ERROR,"�豸ID��Ϊ[%d]���豸�Ѿ�����!!!",data->lvol0));
				return -1;
			}
			catch(DevTypeNotExists&)
			{
				ACE_DEBUG((LM_ERROR,"�豸���Ͳ�����!�豸��[%d]����[%s]"
					,data->lvol0,dt.c_str()));
				continue;
			}
			catch(DeviceAddrUrlException&)
			{
				ACE_DEBUG((LM_ERROR,"�豸�ĵ�ַ��Ϣ����!�豸[%d]addr[%s]"
					,data->lvol0,data->vsvarstr0));
				continue;
			}
		}
		ACE_DEBUG((LM_INFO,"������[%d]���豸",devcnt));
		// ���豸���ո�ID�Ž�������
		_devManager->Sort();
		// �����豸�ӿڳ�ʼ���豸�ṹ
		KSG_GET_DEVICE_LOADER(_configuration._devType,loader);
		// ���ò�ͬ�豸���̵�ʵ������ʼ���豸�ṹ
		if(loader)
		{
			ret = loader->LoadDevice(_devManager);
			if(ret)
				return ret;
		}
		// �����豸�ӿڶ���
		KSG_GET_DEVINT_LOADER(_configuration._devType,iloader);
		if(iloader)
		{
			// ���ò�ͬ���̵Ľӿ�����ʼ���豸�ӿ�
			ret = iloader->LoadInterface(_devManager);
			if(ret)
				return ret;
		}

		// ������ĳ�ʼ������
		ret = loader->Finish(_devManager);
		if(ret)
		{
			ACE_DEBUG((LM_DEBUG,"����豸��ʼ��ʧ��"));
			return ret;
		}
		loader = NULL; 
		// ��� Loop �豸�ĳ�ʼ������
		KSG_GET_DEVICE_LOADER(KSG_LOOP_DEV,loader);
		if(!loader)
			return -1;
		ret = loader->Finish(_devManager);
		if(ret)
		{
			ACE_DEBUG((LM_ERROR,"δ����豸��ʼ��"));
			return -1;
		}
		
		return 0;
	}
	ACE_DEBUG((LM_ERROR,"���豸����...[%s]",obj->GetReturnMsg().c_str()));
	return 0;
}

int KSGateway::loadTaskExecutor()
{
	TaskExecutorLoader* tload = NULL;
	try
	{
		_KSG_GET_FACTORY_INTERFACE_OBJECT(_configuration._devType
			,TaskExecutorLoader,tload);
		if(tload)
			return tload->LoadExecutor();
		return -1;
	}
	catch(...)
	{
		// 
		ACE_DEBUG((LM_ERROR,"����ָ��ִ����ʧ��"));
		return -1;
	}
}

int KSGateway::loadLoopDevice()
{
	KSGDeviceLoader * loader = NULL; 
	ACE_DEBUG((LM_INFO,"��ʼ��loop�豸"));
	KSG_GET_DEVICE_LOADER(KSG_LOOP_DEV,loader);
	if(!loader)
		return -1;
	if(loader->LoadDevice(_devManager) != 0)
	{
		ACE_DEBUG((LM_ERROR,"����loop�豸ʧ��!"));
		return -1;
	}
	KSGDeviceInterfaceLoader * iloader = NULL;
	KSG_GET_DEVINT_LOADER(KSG_LOOP_DEV,iloader);
	if(!iloader)
		return -1;
	if(iloader->LoadInterface(_devManager))
	{
		ACE_DEBUG((LM_ERROR,"����loop�豸�ӿ�ʧ��"));
		return -1;
	}
	return 0;
}
int KSGateway::loadDeviceType()
{
	// ���ǰ�û��Ƿ�֧������豸����
	AbstractDeviceInterfaceFactory * factory = NULL;
	try
	{
		KSG_GET_FACTORY_INTERFACE(_configuration._devType,factory);
		if(NULL == factory)
		{
			ACE_DEBUG((LM_ERROR,"�豸�������Ͳ�����[%s]",_configuration._devType.c_str()));
			return -1;
		}
		return 0;
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"�豸�������Ͳ�����[%s]",_configuration._devType.c_str()));
		return -1;
	}
}

int KSGateway::startTimeScheduler()
{
	// �������ж�ʱ���� ���߳� 
	KSGSchedulerGrpFactory::SchedulerIdList loadid;
	std::list<std::string> idstr;
	std::back_insert_iterator<std::list<std::string> > iter(idstr);
	// �������ж�ȡ��Ҫ�����������
	xutil::StringUtil::SpliteString(_configuration._runTaskIds,",",iter);
	for(std::list<std::string>::iterator i = idstr.begin();i != idstr.end();++i)
	{
		loadid.push_back(ACE_OS::atoi((*i).c_str()));
	}
	// ������Ҫ����������
	SchedulerGroup::Instance().AddScheduler(loadid);
	// ����һ���۲���
	SchedulerGroup::Instance().AddObserver(_schdObserver);
	// �������������߳�
	SchedulerGroup::Instance().StartAll();
	ACE_DEBUG((LM_INFO,"���������̳߳ɹ�"));
	return 0;
}
int KSGateway::stop()
{
	_status = stStopPedding;
	return 0;
}

void KSGateway::restart()
{
	// TODO : �豸����״̬,�Ժ�ϵͳ����
}
int KSGateway::setupLogSystem()
{
	// ����ACE_Log_Msg �Ĺ�����
	std::string logfile = _configuration._logFilePath;
	/*
	if(logfile.length() > 0)
	{
		char filepath[1024] = "";
		ACE_OS::realpath(logfile.c_str(),filepath);
		if(logfile != filepath)
		{
			logfile = KSGOSUtil::JoinPath(_configuration._basedir,logfile);
		}
	}
	*/
	ACE_NEW_RETURN(_logBackend,KSGLogBackend(_configuration._logLevel
		,_configuration._logOutput,logfile),-1);
	// TODO: ���Ӵ������ļ��ж�ȡLOG�����ò���
	ACE_LOG_MSG->clr_flags(ACE_Log_Msg::STDERR);
	ACE_LOG_MSG->set_flags (ACE_Log_Msg::CUSTOM|ACE_Log_Msg::VERBOSE_LITE);
	((KSGLogBackend*)_logBackend)->set_file_max_count(_configuration._log_max_backup);
	((KSGLogBackend*)_logBackend)->set_file_size(_configuration._log_max_file_size);
	ACE_Log_Msg::msg_backend(_logBackend);
	return 0;
}

int KSGateway::closeLogSystem()
{
	// �ر���־
	ACE_LOG_MSG->msg_backend(NULL);
	if(_logBackend)
		delete _logBackend;
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// KSGSchedulerObserver
void KSGSchedulerObserver::Update(ObserverableType& obj)
{
	ThreadModelType lock(_mutex);
	KSGScheduler* schd = reinterpret_cast<KSGScheduler*>(&obj);
	// TODO : ����ͨ�� scheduler manager ���µ����߳�״̬�Ĺ���
	if(schd)
		ACE_DEBUG((LM_DEBUG,"�����߳���������,scheduler id [%d]",schd->GetSchdId()));
}

