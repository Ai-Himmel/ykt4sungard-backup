#ifndef _KSG_BCC_SERVER_H_
#define _KSG_BCC_SERVER_H_

#include <list>
#include <ace/Thread_Mutex.h>
#include "bccsvr.h"

class KSG_BCC_Svr_Handler 
{
private:
	typedef std::list<KSG_BCC_Svr_Handler*> HANDLER_LIST_TYPE;
	static HANDLER_LIST_TYPE s_handlers_;
	static ACE_Thread_Mutex s_handler_mutex_;
	static const int s_max_free_handlers_ = 50;
	static const int s_max_pack_path_len_ = 1024;
	static char s_xpack_data_[s_max_pack_path_len_]; 
	//////////////////////////////////////////////////////////////////////////
	// member 
	XDHANDLE handler_;
	int resp_row_num_;
	int req_row_num_;
	int req_rows_;
public:
	//////////////////////////////////////////////////////////////////////////
	// 公共函数
	static int init(const char *xpack_path);
	static int uninit();

	static KSG_BCC_Svr_Handler *create_new_handler();
	static int free_handler(KSG_BCC_Svr_Handler *handler);
	//////////////////////////////////////////////////////////////////////////
	// 成员函数
	KSG_BCC_Svr_Handler();
	~KSG_BCC_Svr_Handler();
	XDHANDLE get_handler();
	int put_one_row();
	int finish(int ret);

	inline int get_resp_row_count() const
	{
		return resp_row_num_;
	}
	int SetStringField(const char *field,const char *value,int val_len = 0);
	int SetIntField(const char *field,long value);
	int SetDoubleField(const char *field,double value);

	//////////////////////////////////////////////////////////////////////////
	// 
	int get_req_row_count();
	int GetIntField(const char *field,long *value);
	int GetDoubleField(const char *field,double *value);
	int GetStringField(const char *field,char *value,int max_size);
	int get_next_req();
	int has_more_req_rows();

	int get_req_msg_id();
	int get_request_type();

};
#endif // _KSG_BCC_SERVER_H_
