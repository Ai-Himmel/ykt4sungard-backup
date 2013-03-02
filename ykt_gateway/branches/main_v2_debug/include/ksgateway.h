#ifndef _KSGATEWAY_H_
#define _KSGATEWAY_H_
/*! @file
*	ģ����:	һ��ͨͨ��ǰ�û�
*	�ļ���: ksgateway.h
*	�ļ�ʵ�ֹ���:	
*	����:	����
*	�汾:	V0.1
*	��ע:	
*/
#ifdef _MSC_VER
#pragma once
#endif
#include "ksglobal.h"
#include "taskdef.h"
#include "taskqueue.h"
#include "device.h"
#include "smartpool.h"
#include "DRTPHelper.h"
#include "scheduler.h"
#include <boost/pool/object_pool.hpp>
#include <ace/Log_Msg_Backend.h>
#include <ace/Thread_Manager.h>
#include <map>

//////////////////////////////////////////////////////////////////////////
// 
//typedef KSGTaskManager<KSGDeviceNode::Task> TaskManager;
typedef KSGTaskManager TaskManager;

//! �豸��������
class KSGVendorConfig
{
public:
	int _vendor_id;
	std::string _vendor;
	//<! �豸����ģʽ
	int _devMode;

};

struct KSG_Schd_Alg_Config_t
{
	std::string _algorithm_name;
	size_t _thr_count;
};

#define MAX_IP_ADDR_LEN 16
typedef struct {
	//<! DRTP �ڵ�� IP 
	char drtp_svr_ip[MAX_IP_ADDR_LEN+1];
	//<! DRTP �ڵ�Ķ˿�
	int drtp_svr_port;
	//<! DRTP �ڵ�ı��
	int drtp_branch_no;
	//<! bcc �����ܺ�
	int bcc_main_funcno;
	//<! bcc ˽�й��ܺ�
	int bcc_private_funcno;
	//<! bcc ��������ʱ����
	int bcc_intval;
	//<! ������ bcc �� server id
	int bcc_svrid;
	//<! bcc ��������״̬, 1 ����, 0 ֹͣ
	int bcc_running;
	//<! bcc �������е��߳���
	int bcc_svr_thr_cnt;
}KSG_BCC_Config_t;


//! ǰ�û�ȫ�����ò���
class KSGConfig
{
public:
	//<! ǰ�û����汾��
	int _majorVer;
	//<! ǰ�û��ΰ汾��
	int _minorVer;
	//<! ǰ�û���ID��
	int _gwId;
	//<! ������Ŀ¼
	std::string _basedir;
	//<! DRTP ������IP
	std::string _drtpSvrIP;
	//<! DRTP �������˿ں�
	int _drtpSvrPort;
	//<! DRTP �����ܺ�
	int _drtpMainFunc;
	//<! DRTP �ڵ��
	int _drtpNo;
	//<! DRTP �������������
	int _drtpPoolMaxCnt;
	//<! ǰ�û�ʹ�õ�IP
	std::string _localIP;
	//<! ����IP��Ӧ�� MAC
	std::string _localMac;
	//<! ��̬��Կ
	std::string _dynaKey;
	//<! ָ�������ܺ�
	int _taskRecvFuncNo;
	int _taskResponseFuncNo;
	//<! �����豸�����Ĺ��ܺ�
	int _drtpGetDevFuncNo;
	//<! ����ʱ����
	int _heartbeat;
	//<! ������ֵ
	int _heartbeatIntval;
	//<! ����Ӧ��DRTP���ܺ�
	int _heartbeatFuncNo;
	//<! ǰ�û�DRTP���к�
	int _drtpQueueNo;
	//<! ǰ�û�ָ��ִ�г�ʱʱ��
	int _execTimeout;
	//<! �Ӻ�̨ȡ�������
	int _get_task_count;
	/*
	//<! �豸����
	std::string _devType;
	*/
	//<! ǩ��ʱӦ�÷��������ݿ�ʱ��
	std::string _startDBTime;
	//<! �ɼ���ˮʱ����
	int _serialIntval;
	//<! ָ��������ȴ�ָ����
	int _taskQueueMaxWaiting;
	//<! ��ȡָ��ʱ����
	int _taskRecvIntval;
	//<! ������ָ���̺߳�
	std::string _runTaskIds;
	//<! ���������������
	std::string _listenerIds;
	//<! ��������Կ
	BYTE _workKey[32];
	//<! �豸����Կ
	std::string _cardKey;
	///////////////////////////////////////////////////////////
	//<! ��־����
	std::string _logLevel;
	//<! ��־���
	std::string _logOutput;
	//<! ��־�ļ�·��
	std::string _logFilePath;
	//<! ��־�ļ���С
	unsigned long _log_max_file_size;
	//<! ��־�ļ�����
	int _log_max_backup;
	//<! �Ƿ����� bcc ����
	int _start_bcc;
	//<! �Ƿ���ؿ�״̬(�ڰ�����)
	int _loadCardState;
	//<! �����豸ʧ�������ȴ�ʱ�� ms
	long _conn_interval;
	//<! reactor �����߳�����
	int _reactor_thr_count;
public:
	//! default constructor
	KSGConfig();
	//! destructor
	~KSGConfig();
	//! ���ر��������ļ�
	/*!
	 \param filename ���������ļ�
	 \return ����0 ��ʾ���سɹ���ʧ�ܷ��� -1
	 */
	int loadConfig(const std::string& filename);
};

// class KSGDeviceManager;
class KSGSchedulerObserver;

class KSG_DRTP_Creator
{
public:
	KSG_DRTP_Creator();
	int get_max();
	CDRTPHelper *create_new();
	void delete_one(CDRTPHelper *p);
};

//! ǰ�û�������
class KSGateway
{
public:
	typedef KSGDeviceNode DeviceNodeType;
	typedef KSGDevice DeviceType;
	typedef enum KSG_Gateway_Status { stRunning, stRestarting, stStop,stStopPedding };
private:
	//<! ״̬
	KSG_Gateway_Status _status;
	//<! ȫ�����ò���
	KSGConfig _configuration;
	//<! bcc �����������
	KSG_BCC_Config_t _bcc_config;
	//<! ����Ӳ���豸���ò���
	typedef std::map<std::string,KSGVendorConfig*> vendor_map_type;
	vendor_map_type _vender_config;
	//<! �豸�ڵ������
	KSGDeviceManager *_devManager;

	KSG_DRTP_Creator _drtp_creator;
	/*!
	 * ǰ�û���Ӧ�÷�����ǩ����Ӧ�÷������Ὣǰ�û��� ID �붯̬��Կ����
	 * \return ǩ���ɹ����� 0 ,ʧ�ܷ��ش�����
	 */
	int enroll();
	/*!
	 * ǰ�û���Ӧ�÷�����ǩ��
	 * \return ǩ�˳ɹ����� 0 ,ʧ�ܷ��ش�����
	 */
	int exit();
	/*!
	 * ����ǰ�û����������в���
	 * \return ���سɹ����� 0 ,ʧ�ܷ��ش�����
	 */
	int downloadRuntimeParams(KSGConfig *config);
	/*!
	 * ��ȡ���ص�ǰ�û�����,�����ļ�������Ŀ¼�µ� yktgw.cfg
	 * \return �ɹ����� 0 , -1 ��ʾʧ��
	 */
	int loadLocalConfig();
	/*!
	 * ���������豸��Ϣ�������Ǵ�Ӧ�÷��������أ�Ҳ���Բ���Ҫ��Ӧ�÷���������
	 * \return ���سɹ����� 0 ,ʧ�ܷ��ش����� 
	 */
	int setupAllDevices();
	int device_factory_init(const std::string &vendor);
	int load_executor();
	/*!
	 *  �������еĶ�ʱ����
	 */
	int startTimeScheduler();
	//! ������־ϵͳ
	/*!
	 \brief �÷��������һ�������ã��Գ�ʼ����־
	 \return ���سɹ����� 0 , ʧ�ܷ��� -1
	 */
	int setupLogSystem();
	//! �ر���־ϵͳ
	int closeLogSystem();
	//! ���� DRTP �����, ����ش�С�� _drtpPoolMaxCnt �������� \sa KSGConfig
	/*!
	 \return �ɹ����� 0,ʧ�ܷ��� -1;
	 */
	int setupDrtpPool();
	//! ���� Loop �豸
	/*
	 \return ���سɹ�����0, ʧ�ܷ��� -1
	 */
	int loadLoopDevice();
	//! ����ָ��ִ����
	int loadTaskExecutor();
	//! ���س�������
	/*!
	 \brief ����Ӳ����������, ֻ�м��ع���Ӳ���������͵��豸�ӿڲſ���ʹ��!!!
			LOOP �豸Ĭ�ϱ�����
	 \return 0 ��ʾ�ɹ� -1 ��ʧ��
	 */
	int load_vendor_config();
	int free_vendor_config();

	void report_status();

	int start_scheduler_algorithm();
	int init_scheduler_algorithm(const std::string &alg_name);
	int stop_scheduler_algorithm();
	int get_scheduler_alg_thr_count(const std::string &alg_name);
	typedef std::list<void*> task_schd_list_type;
	task_schd_list_type _task_schd;
	ACE_Thread_Manager _task_schd_thr_manager;

	int setup_all_acceptor();

	int stop_all_acceptor();
	int loadCardState();
	/*
	 \brief ���� bcc server
	 \return 0 ��ʾ�����ɹ� , -1 ��ʾ����ʧ��
	 */
	int start_bcc_svr();
	/*
	 \brief ֹͣ bcc server
	 \return 0 ��ʾֹͣ�ɹ�, -1 ��ʾֹͣʧ��
	 */
	int stop_bcc_svr();
	
	int update_max_blk_version();

	static ACE_THR_FUNC_RETURN bcc_svr_loop_proc(void *arg);
	//<! ����ָ����еĹ�������
	typedef KSGTaskQueueManager TaskQueueManager;
	//<! ����ָ�����
	TaskManager* _taskManager;
	TaskQueueManager _taskQueue;
	//KSGDeviceGroupScheduler _devgrpSchd;
	//<! ��������㷨
	typedef std::list<KSG_Schd_Alg_Config_t*> schd_alg_list_type;
	//schd_alg_list_type _schd_alg_list;
	//<! �����̹߳۲���
	KSGSchedulerObserver* _schdObserver;
	//<! 
	ACE_Log_Msg_Backend* _logBackend;
	//<! ��ǰϵͳ���ĺ������汾
	char _max_blk_version[13];
public:
	/*!
	 * ����ǰ�û����񣬸ú�����������
	 * �������ʧ�ܷ���һ�������룬��������ɹ�������һ������ѭ��
	 * \return ���� 0 ��ʾ�����˳������򷵻��˳�����
	 */
	int run();
	/*!
	 * ���øú�����ֹͣ��������ϵͳ������ֹͣ�������������̣߳�Ȼ�󷵻�
	 * ���ֹͣ����ʧ�ܷ��ش����룬���ú������ᳬʱ������һֱ�ȴ�������ֹͣ��
	 * ���øú�����ǰ�û�������Ӧ�÷�����ǩ�ˡ�
	 * ֹͣǰ�û��Ὣ������ָ������е�ָ��ɾ����
	 * \return 0 ��ʾֹͣʧ�ܣ����򷵻ش�����
	 */
	int stop();
	void restart();

	inline KSG_Gateway_Status status() const
	{
		return _status;
	}
	/*!
	 * default constructor
	 */
	KSGateway();
	/*!
	 * destructor
	 */
	~KSGateway();
	//! ���� DRTPHelper ����,ͨ����������������DRTP����
	/*!
	 \return DRTPHelper ��ָ�룬ʧ�ܷ��� NULL
	 */
	CDRTPHelper * CreateDrtpHelper();
	//! ��ȡǰ�û�������
	const KSGConfig* GetConfig() const
	{
		return &_configuration;
	}
	//! ��ȡǰ�û����������
	inline TaskManager* GetTaskManager()
	{
		return _taskManager;
	}
	inline TaskQueueManager* GetTaskQueue()
	{
		return &_taskQueue;
	}
	//! ��ȡǰ�û��豸�ڵ������
	inline KSGDeviceManager* GetDeviceManager()
	{
		return _devManager;
	}
	/*
	inline KSGDeviceGroupScheduler* GetDeviceGroupScheduler()
	{
		//return &_devgrpSchd;
	}
	*/
	inline KSG_BCC_Config_t* get_bcc_config()
	{
		return &_bcc_config;
	}
	inline KSGVendorConfig* get_vendor_config(const std::string &config) const
	{
		vendor_map_type::const_iterator iter = _vender_config.find(config);
		if(iter == _vender_config.end())
			return NULL;
		return iter->second;
	}
	void sleep_and_test(unsigned long msec);
	const char *get_max_blk_version() const
	{
		return _max_blk_version;
	}

	inline bool is_running() const
	{
		return (_status == stRunning);
	}
};
//! �����̹߳۲���
class KSGSchedulerObserver : public KSGMTObserver
{
private:
	KSGateway * _gateway;
public:
	//! constructor
	/*
	 \param gateway ǰ�û�����ָ��
	 */
	KSGSchedulerObserver(KSGateway* gateway):_gateway(gateway)
	{
		assert(gateway != NULL);
	}
	//! �����߳�֪ͨ�ӿں���
	virtual void Update(KSGScheduler& obj);
};


//<! DRTP ���������
typedef KSG_SmartPool<CDRTPHelper,
KSG_Resource_Pool_Allocator<CDRTPHelper,KSGMultiThreadmModel<10000>,KSG_DRTP_Creator> > DRTPPoolType;
//<! ȫ�� DRTP �����
extern DRTPPoolType theDrtpPool;
//<! ��ȡȫ�ֵ� DrtpPool ��
inline DRTPPoolType* KsgGetDrtpPool()
{
	return &theDrtpPool;
}
int KsgStartServer(KSGateway* gateway);

#define KSG_SLEEP(n) do {KsgGetGateway()->sleep_and_test(n);} while(0)


//���ؿ�״̬(�ڰ�����)
class HD_LoadCardState
{
private:
	static ST_PACK g_out_pack;
	static int g_card_idx_range[];
	int get_card_count_per_pack();
	int get_pack_index(int card_idx);
	int copy_bitmap_buf(const char *buffer,int buf_len);
	int _pack_index;
	int _offset;
	unsigned char *_pbuf;
	char _version[13]; //�������汾��
	static const int MAX_CARD_COUNT = 1500000;
	unsigned char char_to_hex(char c);
public:
	HD_LoadCardState():_pack_index(0),_pbuf(NULL),_offset(0)
	{}
	~HD_LoadCardState();
	int is_valid_card(int cardno);
	int update_card_state(int cardno,int state);
	int apply_bitmap_buf(char *version);
	int put_one_pack(ST_PACK * data);
};

extern HD_LoadCardState hd_loadCardState;

#endif // _KSGATEWAY_H_

