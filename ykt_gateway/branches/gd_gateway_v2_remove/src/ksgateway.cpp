
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
#include "task_scheduler.h"
#include "proactor_def.h"
#include "version.h"
//////////////////////////////////////////////////////////////////////////
//

#define KSG_VERSION_MAGIC	"sungard kingstar gateway gd version"

//<! ȫ�� DRTP �����
DRTPPoolType theDrtpPool;
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
	KSGOSUtil::GetBaseDir(_basedir);
	_basedir = KSGOSUtil::GetPathName(_basedir);
}
KSGConfig::~KSGConfig()
{
	//
}

int KSGConfig::loadConfig(const std::string& file_name)
{
	ACE_Configuration_Heap config;
	if(config.open() == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	ACE_Ini_ImpExp config_importer(config);

	if(config_importer.import_config(file_name.c_str()) == -1)
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

	_listenerIds = "";
	if(config.get_string_value(section,KSG_LISTENER_IDS,v) != -1)
	{
		_listenerIds = v.c_str();
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
	return 0;
}
//////////////////////////////////////////////////////////////////////////
// KSGGateway

KSGateway::KSGateway():_devManager(NULL),_status(stStop),_logBackend(NULL)
{
	// 
	//ACE_DEBUG((LM_DEBUG,"CREATE KSGATEWAY OBJECT!!!"));
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
	//_devgrpSchd.TerminateAll();
	//_devgrpSchd.ClearAll();

	free_vendor_config();
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

void KSGateway::report_status()
{
	int task_count;
	task_count = this->GetTaskManager()->GetTaskCount();
	ACE_DEBUG((LM_NOTICE,"ϵͳ�е�ǰ������[%d]",task_count));
	
}
int KSGateway::run()
{
	long sleep_time = 0;
	int ret = loadLocalConfig();
	if(ret)
		return ret;
	ret = setupLogSystem();
	if(ret)
		return ret;
	ACE_DEBUG((LM_INFO,"��ʼ����ǰ�û�..."));
	ACE_DEBUG((LM_NOTICE,"ǰ�û��汾[%s]",KSG_FULL_VERSION));
	ACE_DEBUG((LM_NOTICE,"������ : %s",KSG_BUILD_INFO));
	ACE_DEBUG((LM_NOTICE,"libraries ACE : %s , boost : %s , libcurl : %s"
		,KSG_ACE_VERSION,KSG_BOOST_VERSION,KSG_CURL_VERSION));
	ACE_DEBUG((LM_NOTICE,KSG_COPYRIGHT_STRING));
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
	ret = downloadRuntimeParams(&_configuration);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"�������в���ʧ�ܣ�������[%d]",ret));
		return ret;
	}
	
	ret = load_vendor_config();
	if(ret)
	{
		return ret;
	}
	// ���� loop �豸
	/*
	ret = loadLoopDevice();
	if(ret)
	{
		return ret;
	}
	*/

	ret = setupAllDevices();
	if(ret)
	{
		return ret;
	}
	//ACE_DEBUG((LM_INFO,"ǰ�û�δ�����豸!"));
	loadTaskExecutor();

	_status = stRunning;

	ret = setup_all_proactor_acceptor();

	// 2007-04-19
	// Ϊ��ֹ�����߳��ڽ��������߳�֮�������������������ֻ��һ�������
	// ����£�������ɵļ���������Ӧ�����������̡߳��������ִ���취��
	// ������õģ�Ӧ�������ź�������������ɼ��߳����ڵ����߳�����.
	ret = start_scheduler_algorithm();
	if(ret)
		return ret;

	ret = startTimeScheduler();
	if(ret)
		return ret;
	
	
	ACE_DEBUG((LM_INFO,"����ǰ�û��ɹ�..."));
	// ������ѭ��
	
	int i = 0;
	while(_status == stRunning)
	{
		KSGThreadUtil::Sleep(5000);
		report_status();

		/*
		sleep_time += 5000;
		if(sleep_time > 1000 * 60 * 15)
		{
			
			KSGConfig config;
			config = _configuration;
			if(downloadRuntimeParams(&config) == 0)
			{
				ACE_DEBUG((LM_DEBUG,"����ǰ�û�����,gwid[%d]",config._gwId));
				ACE_GUARD(ACE_Thread_Mutex,mon,_global_mutex);
				_configuration = config;
			}
			sleep_time = 0;
		}
		*/
		KSGThreadUtil::yield();
	}
	ACE_DEBUG((LM_INFO,"����ֹͣǰ�û�..."));
	stop_all_proactor_acceptor();
	SchedulerGroup::Instance().TerminateAll();
	// ʹ��ѭ���ȴ���ʽ,���Ƴ�ʱ
	/*
	while(_status == stRunning)
	{
		ACE_Time_Value tv(5);
		tv += ACE_OS::gettimeofday();
		ACE_DEBUG((LM_DEBUG,"�ȴ���ʱ,׼������"));
	}
	*/
	_status = stStop;
	//_devgrpSchd.TerminateAll();
	stop_scheduler_algorithm();
	ACE_DEBUG((LM_INFO,"���������н���"));
	exit();
	return 0;
}
int KSGateway::setupDrtpPool()
{
	CDRTPHelper::InitDrtp();
	theDrtpPool.Init();
	return 0;
}
int KSGateway::exit()
{
	_status = stStop;
	vendor_map_type::iterator i;
	for(i = _vender_config.begin();i != _vender_config.end();++i)
	{
		KSGVendorConfig *config = i->second;
		delete config;
	}
	_vender_config.clear();
	// TODO : �ͷŴ����ĵ�����Դ
	task_schd_list_type::iterator ti;
	for(ti = _task_schd.begin();ti != _task_schd.end(); ++ti)
	{
		KSG_Task_Scheduler *schd = static_cast<KSG_Task_Scheduler*>(*ti);
		KSG_Task_Scheduler_Implementation *impl = schd->implementation();
		if(impl)
			delete impl;
		delete schd;
	}
	_task_schd.clear();
	// �ͷ���־��Դ
	closeLogSystem();
	return 0;
}
int KSGateway::loadLocalConfig()
{
	std::string config_path = KSGOSUtil::JoinPath(_configuration._basedir,KSG_CONFIG_FILENAME);
	return _configuration.loadConfig(config_path);
}

int KSGateway::enroll()
{
	DRTPPoolType::SmartObject obj;
	ACE_DEBUG((LM_INFO,"��������ǩ��"));
	std::list<std::string> local_ips;
	KSGNetUtil::GetLocalIP(local_ips);
	std::list<std::string>::iterator iter;
	bool ret = std::find(local_ips.begin(),local_ips.end(),_configuration._localIP) != local_ips.end();
	if(!ret)
	{
		ACE_DEBUG((LM_ERROR,"���õ�IP��ַ[%s]���Ǳ�����IP��ַ"
			,_configuration._localIP.c_str()));
		return -1;
	}
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
	obj->AddField(F_SCERT_NO,KSG_VERSION_MAGIC);
	if(obj->Connect())
	{
		ACE_DEBUG((LM_ERROR,"DRTP����ʧ�ܣ���������"));
		return -1;
	}
	if(!obj->SendRequest(3000))
	{
		if(obj->GetReturnCode())
		{
			ACE_DEBUG((LM_ERROR,"����ǩ��ʧ��,������Ϣ[%s]",obj->GetReturnMsg().c_str()));
		}
		else
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
	}
	else
	ACE_DEBUG((LM_ERROR,"����ǩ��ʧ��,������Ϣ[%s]",obj->GetErrMsg().c_str()));
	return -1;
}
int KSGateway::downloadRuntimeParams(KSGConfig *config)
{
	DRTPPoolType::SmartObject obj;
	ACE_DEBUG((LM_INFO,"�����������в���"));
	obj = KsgGetDrtpPool()->Alloc();
	obj->SetRequestHeader(KSG_DRTP_DW_PARAMS,1);
	obj->AddField(F_LVOL0,config->_gwId); // ǰ�û�ID
	obj->AddField(F_SCUST_LIMIT,config->_dynaKey.c_str()); // ��̬��Կ
	if(obj->Connect())
	{
		return -1;
	}
	if(obj->SendRequest(10000))
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
		config->_heartbeat = data->lvol0;
		config->_heartbeatIntval = data->lvol1;
		config->_heartbeatFuncNo = data->lvol2;
		//_configuration._drtpQueueNo = data->lvol3;
		config->_taskRecvFuncNo = data->lvol3;
		config->_taskResponseFuncNo = data->lvol9;
		if(config->_taskRecvFuncNo <= 0
			|| config->_taskResponseFuncNo <= 0)
			return -1;
		config->_execTimeout = data->lvol4;
		// FIXME : unicode
		config->_startDBTime = data->sname;
		config->_serialIntval = data->lvol5;
		config->_drtpGetDevFuncNo = data->lvol6;
		config->_taskQueueMaxWaiting = data->lvol7;
		config->_taskRecvIntval = data->lvol8;
		// TODO : ����ȡ����ļ�¼����
		config->_get_task_count = 1;
		// Ϊ������Կ
#if 1
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
		config->_cardKey = enkey;
#else
		config->_cardKey = data->sname2;
#endif

		// FIXME: �����˻���豸ʹ�õĹ�����Կ
		ACE_OS::memset(config->_workKey,0,sizeof(config->_workKey));
		size_t keylen = ACE_OS::strlen(data->sphone);
		if(keylen == 0)
		{
			ACE_OS::strcpy(data->sphone,"ffffffffffffffff");
			keylen = ACE_OS::strlen(data->sphone);
		}
		xutil::StringUtil::Str2Hex(data->sphone,config->_workKey,(keylen+1)/2);
		return 0;
	}
	ACE_DEBUG((LM_ERROR,"δ���ص�����[%s]",obj->GetReturnMsg().c_str()));
	return -1;
}
const KSGConfig * KSGateway::GetConfig()
{
	/*
	static KSGConfig temp_config;
L_TEST_AGAIN:
	{
		ACE_Guard  guard(_global_mutex);
		if(guard.locked() == 0)
			goto L_TEST_AGAIN;
	}
	*/
	return &_configuration;
	//return &temp_config;
}
int KSGateway::load_vendor_config()
{
	// ���� LOOP �豸����
	KSGVendorConfig *config = new KSGVendorConfig;
	config->_vendor = KSG_LOOP_DEV;
	config->_devMode = 0;
	_vender_config.insert(_vender_config.end(),vendor_map_type::value_type(config->_vendor,config));
	DRTPPoolType::SmartObject obj;
	obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(KSG_DRTP_VENDOR_CONFIG,1);
		obj->AddField(F_LCERT_CODE,_configuration._gwId); // ǰ�û�ID
		obj->AddField(F_SCUST_LIMIT2,_configuration._dynaKey.c_str()); // ��̬��Կ
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
			ACE_DEBUG((LM_ERROR,"����Ӳ���������ò���ʧ��[%s]",obj->GetReturnMsg().c_str()));
			return -1;
		}
		while(obj->HasMoreRecord())
		{
			ST_PACK *data = obj->GetNextRecord();
			KSGVendorConfig *config = new KSGVendorConfig;
			config->_vendor = data->sname;
			config->_devMode = data->lvol0;
			_vender_config.insert(vendor_map_type::value_type(config->_vendor,config));
		}
		return 0;
	}
	return -1;
}

int KSGateway::free_vendor_config()
{
	vendor_map_type::iterator iter = _vender_config.begin();
	for(; iter != _vender_config.end(); ++iter)
	{
		KSGVendorConfig * c = iter->second;
		if(c)
			delete c;
	}
	_vender_config.clear();
	return 0;
}

int KSGateway::setupAllDevices()
{
	DRTPPoolType::SmartObject obj;
	int ret;
	
	ret = device_factory_init(KSG_LOOP_DEV);
	if(ret)
	{
		return -1;
	}
	ACE_DEBUG((LM_INFO,"�����豸����"));
	obj = KsgGetDrtpPool()->Alloc();
	obj->SetRequestHeader(_configuration._drtpGetDevFuncNo,1);
	obj->AddField(F_LCERT_CODE,_configuration._gwId); // ID
	obj->AddField(F_SCUST_LIMIT2,_configuration._dynaKey.c_str()); // dynamic key
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
	if(obj->HasMoreRecord())
	{
		while(obj->HasMoreRecord())
		{
			ST_PACK * data = obj->GetNextRecord();
			// ��ȡ�豸�Ĳ���
			NormalDeviceType dt = data->semp;
			std::string devphyid = data->sname;
			std::string ipaddr = data->sname2;
			std::string devname = data->scust_limit; // �豸����
			std::string vendor = data->sdate0;
			// ���ӷ�ʽ, Ĭ��Ϊ TCP 
			KSGDeviceURL::DevConnType conn_type = static_cast<KSGDeviceURL::DevConnType>(data->lvol5); 			
			char addr[512];
			int devport = data->lvol2;
			try
			{
				ACE_DEBUG((LM_DEBUG,"�豸[%d][%s]����[%s]����ID[%s]����[%d]"
					,data->lvol0,devname.c_str(),dt.c_str(),devphyid.c_str(),devport));
				// �豸���̱�ʶ
				DeviceNodeType * device = _devManager->NewDevice(data->lvol0,data->lvol1,vendor,devphyid,dt);
				// �豸��ַ��Ϣ
				if(conn_type == KSGDeviceURL::dctCOM)
					ACE_OS::sprintf(addr,"dev:COM:%s//%d@%s:%d",vendor.c_str()
									,devport,ipaddr.c_str(),data->lvol4);
				else if(conn_type == KSGDeviceURL::dctTCP)
					ACE_OS::sprintf(addr,"dev:TCP:%s//%d@%s:%d",vendor.c_str()
									,devport,ipaddr.c_str(),data->lvol4);
				else if(conn_type == KSGDeviceURL::dctModem)
					ACE_OS::sprintf(addr,"dev:MDM:%s//%d@%s:%d",vendor.c_str()
					,devport,ipaddr.c_str(),data->lvol4);
				else if(conn_type == KSGDeviceURL::dctSubLevel)
					ACE_OS::sprintf(addr,"dev:SUB:%s//%d@",vendor.c_str()
					,devport);
				else
					throw DeviceAddrUrlException();
				device->SetAddrUrl(addr);
				device->set_name(devname);
				device->set_vendor(vendor);
				// �豸����
				device->SetTermId(data->lvol3);
				device->set_port_count(data->lvol6);
			}
			catch (DeviceIdAlreadyExists&)
			{
				ACE_DEBUG((LM_ERROR,"�豸[%d][%s]���Ѿ�����!!!",data->lvol0,devname.c_str()));
				return -1;
			}
			catch(DevTypeNotExists&)
			{
				ACE_DEBUG((LM_ERROR,"�豸���Ͳ�����!�豸[%d][%s]����[%s]"
					,data->lvol0,devname.c_str(),dt.c_str()));
				continue;
			}
			catch(DeviceAddrUrlException&)
			{
				ACE_DEBUG((LM_ERROR,"�豸�ĵ�ַ��Ϣ����!�豸[%d]addr[%s]"
					,data->lvol0,data->vsvarstr0));
				continue;
			}
		}
		ACE_DEBUG((LM_INFO,"������[%d]���豸",_devManager->GetDeviceCount()));
		// ���豸���ո�ID�Ž�������, 
		// ���������ṹ 2006-12-30
		/*
		if(_devManager->Sort())
		{
			return -1;
		}*/
		_devManager->Sort();
	 	
		// ���ճ������ý����е��豸���ͽ��г�ʼ��
		vendor_map_type::const_iterator iter;
		for(iter = _vender_config.begin();iter != _vender_config.end();++iter)
		{
			if(iter->first == KSG_LOOP_DEV)
				continue;
			// �����֧�ֵ��豸���̽ӿ�,ֻ��ʾ������Ϣ
			ret = device_factory_init(iter->first);
			if(ret)
			{
				ACE_DEBUG((LM_ERROR,"��ʼ���豸����Ӳ���ӿڴ���[%s]",(iter->first).c_str()));
				//return -1;
				if(ret!=-3)
					return -1;
			}
		}
		return 0;
	}
	ACE_DEBUG((LM_ERROR,"���豸����...[%s]",obj->GetReturnMsg().c_str()));
	return 0;
}

int KSGateway::device_factory_init(const std::string &vendor)
{
	int ret = 0;
	KSGDeviceLoader *loader = NULL; 
	KSGDeviceInterfaceLoader *iloader = NULL;
	// �����豸�ӿڳ�ʼ���豸�ṹ
	try
	{
		ACE_DEBUG((LM_INFO,"��ʼ��Ӳ������[%s]",vendor.c_str()));
		KSG_GET_DEVICE_LOADER(vendor,loader);
		// ���ò�ͬ�豸���̵�ʵ������ʼ���豸�ṹ
		if(loader)
		{
			ret = loader->LoadDevice(_devManager);
			if(ret)
				return ret;
		}

		// �����豸�ӿڶ���
		KSG_GET_DEVINT_LOADER(vendor,iloader);
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
		TaskExecutorLoader* tload = NULL;
		_KSG_GET_FACTORY_INTERFACE_OBJECT(vendor,TaskExecutorLoader,tload);
		if(tload)
			ret = tload->LoadExecutor();
		if(ret)
		{
			ACE_DEBUG((LM_ERROR,"����ִ��ִ�нӿ�ʧ��"));
		}
		ACE_DEBUG((LM_INFO,"��ʼ������[%s]�ӿڳɹ�",vendor.c_str()));
	}
	catch (KSGException&)
	{
		ACE_DEBUG((LM_NOTICE,"�豸�������Ͳ�֧��[%s]",vendor.c_str()));
		return -3;
	}
	return 0;
}

int KSGateway::loadTaskExecutor()
{
	TaskExecutorLoader* tload = NULL;
	try
	{
		vendor_map_type::const_iterator iter;
		for(iter = _vender_config.begin();iter != _vender_config.end();++iter)
		{
			KSGVendorConfig *c = iter->second;
			_KSG_GET_FACTORY_INTERFACE_OBJECT(c->_vendor,TaskExecutorLoader,tload);
			if(!tload || tload->LoadExecutor())
			{
				ACE_DEBUG((LM_ERROR,"����ָ��ִ����ʧ��[%s]",c->_vendor.c_str()));
				return -1;
			}
			else
				ACE_DEBUG((LM_INFO,"����ָ��ִ�����ӿ�[%s] �ɹ�",c->_vendor.c_str()));
		}
		return 0;
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
		,_configuration._logOutput,logfile,_configuration._log_max_file_size
		,_configuration._log_max_backup),-1);
	// TODO: ���Ӵ������ļ��ж�ȡLOG�����ò���
	ACE_LOG_MSG->clr_flags(ACE_Log_Msg::STDERR);
	ACE_LOG_MSG->set_flags (ACE_Log_Msg::CUSTOM|ACE_Log_Msg::VERBOSE_LITE);
	((KSGLogBackend*)_logBackend)->set_file_max_count(_configuration._log_max_backup);
	((KSGLogBackend*)_logBackend)->set_file_size(_configuration._log_max_file_size);
	ACE_Log_Msg::msg_backend(_logBackend);
	return 0;
}

int KSGateway::start_scheduler_algorithm()
{
	std::string config_path = KSGOSUtil::JoinPath(_configuration._basedir,KSG_CONFIG_FILENAME);
	ACE_Configuration_Heap config;
	if(config.open() == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	ACE_Ini_ImpExp config_importer(config);

	if(config_importer.import_config(config_path.c_str()) == -1)
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

	if(config.open_section(config.root_section(),ACE_TEXT(KSG_SCHEDULER_SECT)
		,0,section) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);

	if(config.get_string_value(section,KSG_SCHD_ALG,v) == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	std::string algs = v.c_str();
	std::list<std::string> idstr;
	std::back_insert_iterator<std::list<std::string> > iter(idstr);
	// �������ж�ȡ��Ҫ�����������
	xutil::StringUtil::SpliteString(algs,",",iter);
	int count = 0;
	for(std::list<std::string>::iterator i = idstr.begin();i != idstr.end();++i,++count)
	{
		if(init_scheduler_algorithm(*i))
			return -1;
	}
	ACE_DEBUG((LM_DEBUG,"����[%d]�������㷨",count));
	return 0;
}

int KSGateway::get_scheduler_alg_thr_count(const std::string &alg_name)
{
	int count = 0;
	std::string config_path = KSGOSUtil::JoinPath(_configuration._basedir,KSG_CONFIG_FILENAME);
	ACE_Configuration_Heap config;
	if(config.open() == -1)
	{
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	}
	ACE_Ini_ImpExp config_importer(config);

	if(config_importer.import_config(config_path.c_str()) == -1)
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

	if(config.open_section(config.root_section(),ACE_TEXT(KSG_SCHEDULER_SECT)
		,0,section) == -1)
		ACE_ERROR_RETURN((LM_ERROR,ACE_TEXT("��ȡǰ�û�����ʧ��")),-1);
	
	std::string key_name = alg_name;
	key_name += "_thr_count";
	if(config.get_string_value(section,key_name.c_str(),v) == -1)
	{
		count = 5;
	}
	else
	{
		count = ACE_OS::atoi(v.c_str());
		count = (count <= 0) ? 5 : count;
	}
	
	return count;
}

ACE_THR_FUNC_RETURN task_scheduler_thr_func(void * args)
{
	KSG_Task_Scheduler *schd = static_cast<KSG_Task_Scheduler*>(args);
	if(schd)
	{
		schd->release_semaphore();
		while(theGlobalGateWay->status() == KSGateway::stRunning)
		{
			schd->process_task(3000);
			ACE_DEBUG((LM_DEBUG,"��������������..."));
		}
		ACE_DEBUG((LM_DEBUG,"���������������̣�"));
		//schd->end_process_loop();
	}
	return (ACE_THR_FUNC_RETURN)0;
}

int KSGateway::init_scheduler_algorithm(const std::string &alg)
{
	static int thr_total_cnt = 0;
	int thr_cnt;
	thr_cnt = get_scheduler_alg_thr_count(alg);
	if(thr_cnt < 0)
	{
		ACE_ERROR_RETURN((LM_ERROR,"��ȡ�����㷨����ʧ�ܣ�"),-1);
	}
	thr_total_cnt += thr_cnt;
	if(thr_total_cnt > 1024)
	{
		ACE_ERROR_RETURN((LM_ERROR,"���������㷨�߳��������ޣ�"),-1);
	}
	KSG_Task_Scheduler_Implementation *impl = NULL;
	try
	{
		impl = Task_Schd_Impl_Object::instance()->Create(alg);
	}
	catch (...)
	{
		ACE_ERROR_RETURN((LM_ERROR,"�޷���ʼ�������㷨[%s]",alg.c_str()),-1);
	}
	
	
	if(!impl)
	{
		ACE_DEBUG((LM_ERROR,"�����㷨δ�ҵ�[%d]",alg.c_str()));
		return -1;
	}
	KSG_Task_Scheduler * schd = new KSG_Task_Scheduler(impl);
	if(!schd)
	{
		ACE_DEBUG((LM_ERROR,"�������ȶ���ʧ��"));
		return -1;
	}
	if(schd->open(alg))
		return 0;

	_task_schd.push_back(schd);
	// ���������߳�
	int ret = _task_schd_thr_manager.spawn_n(thr_cnt,task_scheduler_thr_func,schd);
	if(ret > 0)
	{
		for (int i = 0;i < thr_cnt;++i)
			schd->wait_semaphore();
		return 0;
	}
	return -1;
}

static void do_stop_algorithm(void * arg)
{
	KSG_Task_Scheduler * schd = static_cast<KSG_Task_Scheduler*>(arg);
	if(schd)
	{
		schd->end_process_loop();
	}
}
int KSGateway::stop_scheduler_algorithm()
{
	// ֹͣ���е� scheduler
	std::for_each(_task_schd.begin(),_task_schd.end(),do_stop_algorithm);
	// �ȴ�ֹͣ�����߳�
	ACE_Time_Value tv(10);
	tv += ACE_OS::gettimeofday();
	return _task_schd_thr_manager.wait();
}

int KSGateway::closeLogSystem()
{
	// �ر���־
	ACE_LOG_MSG->msg_backend(NULL);
	if(_logBackend)
		delete _logBackend;
	return 0;
}

int KSGateway::setup_all_proactor_acceptor()
{
	long cpus = ACE_OS::num_processors_online();
	if(cpus <= 0)
		cpus = 1;

	long num_of_threads = cpus * 2 + 2;

	// �������ж�ʱ���� ���߳� 
	std::list<std::string> idstr;
	std::back_insert_iterator<std::list<std::string> > iter(idstr);
	// �������ж�ȡ��Ҫ�����������
	xutil::StringUtil::SpliteString(_configuration._listenerIds,",",iter);

	if(idstr.size() <= 0)
	{
		ACE_DEBUG((LM_INFO,"δע���κ��������� ..."));
		return 0;
	}
	ACE_DEBUG((LM_INFO,"ACE Proactor ���� [%d] ���߳�",num_of_threads));
	Proactor_Task::instance()->start_task(num_of_threads);
	ACE_DEBUG((LM_DEBUG,"ACE LISTENER [%d] ......",idstr.size()));
	for(std::list<std::string>::const_iterator i = idstr.begin();i != idstr.end();++i)
	{
		int listener_id = ACE_OS::atoi(i->c_str());
		// ע����������
		if(Proactor_Task::instance()->start_listener(listener_id))
				ACE_DEBUG((LM_ERROR,"������������[%d]ʧ��",listener_id));
			else
				ACE_DEBUG((LM_INFO,"������������[%d]�ɹ�",listener_id));

	}
	return 0;
}

int KSGateway::stop_all_proactor_acceptor()
{
	Proactor_Task::instance()->stop_task();
	return 0;
}
void KSGateway::sleep_and_test(unsigned long msec)
{
	long eslipse = 0;
	do 
	{
		KSGThreadUtil::Sleep(300);
		eslipse+=300;
	} while(eslipse >= msec && _status == stRunning);
}
//////////////////////////////////////////////////////////////////////////
// KSG_DRTP_Creator
KSG_DRTP_Creator::KSG_DRTP_Creator()
{
	//empty
}
int KSG_DRTP_Creator::get_max()
{
	return theGlobalGateWay->GetConfig()->_drtpPoolMaxCnt;
}
CDRTPHelper* KSG_DRTP_Creator::create_new()
{
	const KSGConfig *config = theGlobalGateWay->GetConfig();
	return new CDRTPHelper(config->_drtpSvrIP.c_str()
		,config->_drtpSvrPort,config->_drtpMainFunc,config->_drtpNo);
}
void KSG_DRTP_Creator::delete_one(CDRTPHelper *p)
{
	delete p;
}

//////////////////////////////////////////////////////////////////////////
// KSGSchedulerObserver
void KSGSchedulerObserver::Update(ObserverableType& obj)
{
	//ThreadModelType lock(_mutex);
	KSGScheduler* schd = reinterpret_cast<KSGScheduler*>(&obj);
	// TODO : ����ͨ�� scheduler manager ���µ����߳�״̬�Ĺ���
	if(schd)
		ACE_DEBUG((LM_DEBUG,"�����߳���������,scheduler id [%d]",schd->GetSchdId()));
}



