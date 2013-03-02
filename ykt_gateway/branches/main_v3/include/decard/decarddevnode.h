#ifndef _DECARDDEVNODE_H_
#define _DECARDDEVNODE_H_


#include "ksglobal.h"
#include "scheduler.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "deviceinterface.h"
#include <boost/shared_ptr.hpp>
#include <ace/Thread_Mutex.h>
#include "bit_endian.h"
#include "reactor_def.h"

#ifdef HAS_DECARD_SUPPORT

DECLARE_NAMESPACE_BEGIN(DECARD)

//! 德卡设备初始化类
class DC_DeviceLoader : public KSGDeviceLoader
{
private:
	void SetupDeviceGroup(KSGDeviceNode* node);
public:
	int LoadDevice(KSGDeviceManager* manager);
	int Finish(KSGDeviceManager* manager);
};

//! 德卡设备接口初始化类
class DC_DevInterfaceLoader : public KSGDeviceInterfaceLoader
{
public:
	virtual int LoadInterface(KSGDeviceManager *manager);
};
//! 德卡业务层初始化类
class DC_TaskExecutorLoader : public TaskExecutorLoader
{
public:
	virtual int LoadExecutor();
};

//<! 定义 德卡 设备工厂
typedef KSGDeviceInterfaceFactory
<
TYPELIST_4(DevAbstractObject,DC_DeviceLoader,DC_DevInterfaceLoader,DC_TaskExecutorLoader)
>::Result KSG_DC_DevInterfaceFactory;

//!
class DC_BusPos_Device : public KSGDevice
{
	DECLARE_FACTORY_CREATOR(DC_BusPos_Device)
protected:
	virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
	virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
public:
	DC_BusPos_Device():KSGDevice(KSG_BUSPOS_DEV)
	{}
	virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
};


//////////////////////////////////////////////////////////////////////////
// 服务器段定义

class DC_Service_Request : public KSG_Reactor_Request
{
private:
	int do_save_record(unsigned char *recbuf);
	int do_upload_serial(unsigned char *inbuf,int inlen,unsigned char *outbuf,int &outlen);
	int do_download_blkcard(unsigned char *inbuf,int inlen,unsigned char *outbuf,int &outlen);
public:
	DC_Service_Request()
	{}
	~DC_Service_Request()
	{}

	int process_request(void *arg,long timeout /* = 5000 */);
private:
	int do_request(KSG_WORK_SVR_HANDLER *handle);
};

//! 德卡接收业务
class DC_Service_Handler : public KSG_Service_Handler
{
private:
	//int do_request(ACE_Message_Block *mblk,int data_len);
protected:
	virtual int recv_data(ACE_Message_Block *&blk);
	//int recv_from_client(ACE_Message_Block *buf,size_t *recv_len);
public:
	DC_Service_Handler(ACE_Reactor *r);
	virtual ~DC_Service_Handler()
	{}
	virtual int process_request(long timeout /* = 5000 */);
	//virtual int handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);
};

class DC_Service_Acceptor : public KSG_Service_Acceptor
{
protected:
	virtual KSG_Service_Handler *new_handle();
	virtual int free_handle(KSG_Service_Handler *handle);
public:
	DECLARE_FACTORY_CREATOR(DC_Service_Acceptor)
	DC_Service_Acceptor(ACE_Reactor *r):KSG_Service_Acceptor(r)
	{}
	DC_Service_Acceptor()
	{}
	virtual int start_listen();
	virtual int stop_listen();
	static int blk_per_dl_;
};
DECLARE_NAMESPACE_END(DECARD);

#endif // HAS_DECARD_SUPPORT

#endif // _DECARDDEVNODE_H_
