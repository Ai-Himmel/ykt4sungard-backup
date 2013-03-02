#ifndef _GDCT_H_
#define _GDCT_H_

#include "ksglobal.h"
#include "scheduler.h"
#include "taskcode.h"
#include <boost/shared_ptr.hpp>
#include <ace/Thread_Mutex.h>
#include "bit_endian.h"
#include "reactor_def.h"
#include <ace/Task.h>
#include <ace/SOCK_Stream.h>
#include "gdct/gdctpub.h"

DECLARE_NAMESPACE_BEGIN(GDCT)

class GDCT_Service_Request : public KSG_Reactor_Request
{
private:
public:
	GDCT_Service_Request()
	{}
	~GDCT_Service_Request()
	{}

	int process_request(void *arg,long timeout /* = 5000 */);
private:
	int do_request(KSG_WORK_SVR_HANDLER *handle);
};

//! 接收业务
class GDCT_Service_Handler : public KSG_Service_Handler
{
private:
	//int do_request(ACE_Message_Block *mblk,int data_len);
protected:
	virtual int recv_data(ACE_Message_Block *&blk);
	//int recv_from_client(ACE_Message_Block *buf,size_t *recv_len);
public:
	GDCT_Service_Handler(ACE_Reactor *r);
	virtual ~GDCT_Service_Handler()
	{}
	virtual int process_request(long timeout /* = 5000 */);
	//virtual int handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);
};

class GDCT_Service_Acceptor : public KSG_Service_Acceptor
{
protected:
	virtual KSG_Service_Handler *new_handle();
	virtual int free_handle(KSG_Service_Handler *handle);
public:
	DECLARE_FACTORY_CREATOR(GDCT_Service_Acceptor)
	GDCT_Service_Acceptor(ACE_Reactor *r):KSG_Service_Acceptor(r)
	{}
	GDCT_Service_Acceptor()
	{}
	virtual int start_listen();
	virtual int stop_listen();
};

struct GDCT_Data 
{
public:
	ACE_HANDLE handle_;
	ACE_Message_Block *msg_;
};
class GDCT_Transfer : public ACE_Task<ACE_MT_SYNCH>
{
private:
	typedef std::map<std::string,GDCT_Data> MESSAGE_MAP_TYPE;
	MESSAGE_MAP_TYPE input_queue_;
	MESSAGE_MAP_TYPE output_queue_;
private:
	char gdct_msgtype_[5];
	char gdct_company_code_[9];
	char gdct_company_pswd_[33];
	// 连接讯源服务器是否成功
	int is_connected_;
	int svr_port_;
	std::string svr_ip_;
	ACE_Time_Value default_timeout_;
	// 最后一次成功通讯时间
	ACE_Time_Value last_success_time_;
	//! 讯源服务器连接
	ACE_SOCK_Stream connector_;
	//!
	ACE_Thread_Mutex msg_mutex_;
	//! 连接讯源服务器
	int do_connect_svr();
	//! 签到
	int do_login_svr();
	//! 签退
	int do_logout_svr();
	//! 发送心跳
	int do_send_heartbeat();
	//! 断开讯源服务连接
	int do_disconnect();
	//! 处理业务逻辑
	int do_main_service();
	//! 发送/接收
	int do_send_and_recv(gdct_msg_t *sendmsg,gdct_msg_t *mymsg);
	//! 下载参数
	int do_setup();
	//!	
	int peek_msg(GDCT_Data *the_data);
	//!
	int do_send_one_data(GDCT_Data *the_data);
	int do_recv_one_data();
	int wait_for_input();
	int get_output_queue_count();
	int get_input_queue_count();
public:
	GDCT_Transfer();
	~GDCT_Transfer();
	int svc();
	int push_queue(GDCT_Data *the_data);

	//! 
	int do_get_svr_param(const char *param,char *value);
};

DECLARE_NAMESPACE_END(GDCT);

#endif //_GDCT_H_