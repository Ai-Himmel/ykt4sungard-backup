#ifndef _GDCTSVR_H_
#define _GDCTSVR_H_

class KSG_GDCT_Config
{
public:
	// 讯源相关配置
	char ct_server_ip_[30];
	int ct_server_port_;
	int ct_trans_timeout_;
	// 队列相关配置
	// 请求队列最大数
	int bu_queue_max_;
	// 请求队列最长等待时间
	int bu_queue_time_max_;
	// 
};

class KSG_GDCT_Server
{
private:
	int do_read_config_file();
	int do_connect_xunyuan();
public:
	KSG_GDCT_Server();
	~KSG_GDCT_Server();
	int start_server();
	int shutdown_server();
	int is_running();
};

extern KSG_GDCT_Server g_server;
#define CT_SERVER g_server;

#endif // _GDCTSVR_H_

