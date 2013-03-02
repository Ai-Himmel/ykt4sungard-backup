#ifndef _KSG_HDREACTOR_H_
#define _KSG_HDREACTOR_H_

#include "reactor_def.h"
#include "hddev/hdsvr.h"

DECLARE_NAMESPACE_BEGIN(HDDEV)

class HD_Service_Request : public KSG_Reactor_Request
{
public:
	HD_Service_Request()
	{}
	~HD_Service_Request()
	{}

	int process_request(void *arg,long timeout /* = 5000 */);
private:
	HDResponseHandler *_request_handler;
	int do_request(KSG_WORK_SVR_HANDLER *handle);
};
extern HD_Service_Request g_global_hd_request;
//! 汇多接收业务
class HD_Service_Handler : public KSG_Service_Handler
{
private:
	HDResponseHandler *_request_handler;
	int do_request(ACE_Message_Block *mblk,int data_len);
protected:
	virtual int recv_data(ACE_Message_Block *&blk);
	int recv_from_client(ACE_Message_Block *buf,size_t *recv_len);
public:
	HD_Service_Handler(ACE_Reactor *r):KSG_Service_Handler(r)
	{ this->request_ = &g_global_hd_request; }
	virtual ~HD_Service_Handler()
	{}
	virtual int process_request(long timeout /* = 5000 */);
	virtual int handle_input(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);
};

class HD_Service_Acceptor : public KSG_Service_Acceptor
{
protected:
	virtual KSG_Service_Handler *new_handle();
	virtual int free_handle(KSG_Service_Handler *handle);
public:
	DECLARE_FACTORY_CREATOR(HD_Service_Acceptor)
	HD_Service_Acceptor(ACE_Reactor *r):KSG_Service_Acceptor(r)
	{}
	HD_Service_Acceptor()
	{}
	virtual int start_listen();
	virtual int stop_listen();
};


DECLARE_NAMESPACE_END(HDDEV);

#endif // _KSG_HDREACTOR_H_
