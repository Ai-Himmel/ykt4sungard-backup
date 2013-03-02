#ifndef _HUNDURE_DEF_H_
#define _HUNDURE_DEF_H_

#include "hundure/hundure_config.h"
#include "scheduler.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "deviceinterface.h"
#include <boost/shared_ptr.hpp>
#include <ace/Thread_Mutex.h>
#include "bit_endian.h"

#ifdef WIN32
typedef HANDLE HNDR_HANDLE;
#else
typedef int HNDR_HANDLE;
#endif

/////////////////////////////////////////////////////////////////
// 汉军错误码
#define E_HNDR_SUCCESS 0
#define E_HNDR_PARAM_ERR 1001
#define E_HNDR_FAILED 1002
#define E_HNDR_TIMEOUT 1003
#define E_HNDR_INVALID_HANDLE 1004
/////////////////////////////////////////////////////////////////
#if defined(HAS_RAC2000G_SUPPORT) || defined(HAS_RAC2000P_SUPPORT)
#include "hundure/RAC2000.h"
#endif 

#ifdef HAS_GCU_SUPPORT

#endif 

#ifdef HAS_NCU_SUPPORT

#endif 

#define HUNDURE_RAC2000P  "9001"
#define HUNDURE_RAC2000G  "9002"
#define HUNDURE_GCU3	  "9003"
#define HUNDURE_NCU3	  "9004"
#define HUNDURE_DOOR	  "9000"
#define HUNDURE_BF430	  "9005"
#define HUNDURE_RAC_BAND_RATE 19200
#define HUNDURE_EVENT_FUNC_NO 930203
#define HUNDURE_HOLIDAY_FUNC_NO 930122


DECLARE_NAMESPACE_BEGIN(HUNDURE)

typedef struct {
	int err_code;
	const char *err_msg;
}HNDR_Err_Define_t;

typedef struct {
	int hndr_event_code;
	int ks_event_code;
}HNDR_Event_Code_Def_t;

#define HNDR_EVENT_CODE_END 0xFFFFFFFF
#define HNDR_KS_EVENT_UNKNOWN -9999

//<!功能函数
int HNDR_convert_cardphy_hex2dec(const std::string &hex_str
								 ,std::string &dec_str);
int HNDR_convert_cardphy_dec2hex(const std::string &dec_str
								 ,std::string &hex_str);
int HNDR_convert_cardphy_hex2zip(const std::string &hex_str
								 ,char zip_str[5]);
int HNDR_convert_cardphy_zip2hex(const char zip_str[5]
								 ,std::string &hex_str);
int HNDR_convert_event_datetime(const char *event_date
								,char *date_str,int maxlen=16);
int HNDR_event_code_2_ks_event(const HNDR_Event_Code_Def_t *defs,int event_code);

//<! 定义 门设备
class HNDR_Door_Device : public KSGDevice
{
	DECLARE_FACTORY_CREATOR(HNDR_Door_Device)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
public:
	HNDR_Door_Device():KSGDevice(HUNDURE_DOOR)
	{}
	virtual bool Accept(BaseVisitor& guest);
};
//<! 汉军设备基类
class HNDR_Device_Base : public KSGDevice
{
public:
	enum {psSuccess,psFailed};
private:
	struct Poll_Status_t
	{
		int _last_record;
		time_t _last_status;
		int _empty_times;
		time_t _last_timetick;
		ACE_Thread_Mutex _mutex;
		Poll_Status_t():_last_record(0),_last_status(psSuccess)
			,_empty_times(0),_last_timetick(0)
		{}
	};
	typedef boost::shared_ptr<Poll_Status_t> Poll_Status_Ptr_t;
	typedef std::map<KSGDeviceNode*,Poll_Status_Ptr_t> Dev_Poll_Status_map_t;
	Dev_Poll_Status_map_t _dev_poll_status;
	ACE_Thread_Mutex _mutex;
protected:
	Poll_Status_Ptr_t find_status_ptr(KSGDeviceNode* node);
public:
	HNDR_Device_Base(NormalDeviceType devtype):KSGDevice(devtype)
	{}
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
	virtual void update_poll_status(KSGDeviceNode* node,int success,int record_cnt);
	virtual int get_last_poll_record(KSGDeviceNode* node);
};

class HNDR_BF430 : public HNDR_Device_Base
{
	DECLARE_FACTORY_CREATOR(HNDR_BF430)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
public:
	HNDR_BF430():HNDR_Device_Base(HUNDURE_BF430)
	{}
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};
//! 汉军设备初始化类
class HNDR_DeviceLoader : public KSGDeviceLoader
{
private:
	void SetupDeviceGroup(KSGDeviceNode* node);
public:
	int LoadDevice(KSGDeviceManager* manager);
	int Finish(KSGDeviceManager* manager);
};

//! 汉军设备接口初始化类
class HNDR_DevInterfaceLoader : public KSGDeviceInterfaceLoader
{
public:
	virtual int LoadInterface(KSGDeviceManager *manager);
};
//! 汉军业务层初始化类
class HNDR_TaskExecutorLoader : public TaskExecutorLoader
{
public:
	virtual int LoadExecutor();
};

//<! 定义 汉军 设备工厂
typedef KSGDeviceInterfaceFactory
<
TYPELIST_4(DevAbstractObject,HNDR_DeviceLoader,HNDR_DevInterfaceLoader,HNDR_TaskExecutorLoader)
>::Result KSG_HNDR_DevInterfaceFactory;

DECLARE_NAMESPACE_END(HUNDURE);

#endif // _HUNDURE_DEF_H_
