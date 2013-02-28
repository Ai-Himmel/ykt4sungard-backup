#ifndef _KS_FILESVR_H_
#define _KS_FILESVR_H_

#include <map>
#include <string>
#include "nbccsvr.h"
#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#include <Windows.h>
#define FILE_SEP "\\"
#else
#include <unistd.h>
#define FILE_SEP "/"
#endif

class KSFileServer
{
private:
	char drtp_ip_[64];
	int drtp_port_;
	int main_func_;
	int load_config_;
	int server_start_;
	int debug_;
	int klg_open_;
	int service_id_;
	char xpack_path_[1024];
	char err_msg_[1024];
	int err_code_;
	BSHANDLE bcc_handle_;
	inline void write_msg(char *fmt,...);
	int open_log(const char *klgpath);
	inline void write_xpack(void *pBuf, int nBufLen,const char *pszPackHint);
	int new_bcc_handle();
	void free_bcc_handle();
	void sleep_thread(long sleeptime);
	static const int BCC_TR0 = 100;
	int process_request(BSHANDLE handle);
public:
	KSFileServer();
	~KSFileServer();
	int load_config(const char *cfg);
	int handle_request();
	int start_svr();
	int stop_svr();
	int check_svr();
};

class KSConfiguration
{
private:
	typedef std::map<std::string,std::string> VALUE_MAP_TYPE;
	VALUE_MAP_TYPE cfgs_;
	KSConfiguration();
	static KSConfiguration *instance_;
public:
	static KSConfiguration* getInstance();
	~KSConfiguration();
	int GetIntPara(const char *param,int *value) const;		
	int GetStringPara(const char *param,char *value) const;
	int GetDoublePara(const char *param,double *value) const;
	void PusIntPara(const char *param,int value);
	void PutStringPara(const char *param,const char *value);
};

class BCCHandle
{
private:
	int current_row_;
	int record_count_;
public:
	BSHANDLE bcc_handle_;
	BCCHandle(BSHANDLE bcc_handle_);
	BCCHandle();
	BCCHandle(const BCCHandle &rhs);
	BCCHandle& operator=(const BCCHandle &rhs);
public:
	void Reset();
	int PutRow(int retCode);
	int DataDone(int retCode);
	int SetStringFieldByName(const char *fieldname,const char *val);
	int SetIntFieldByName(const char *fieldname,long value);
	int SetDoubleFieldByName(const char *fieldname,double value);
	int GetIntFieldByName(const char *fieldname,int *value);
	int GetDoubleFieldByName(const char *fieldname,double *value);
	int GetStringFieldByName(const char *fieldname,char *value);
	int HasMoreRecord();
	int GetNextRecord();
	int GetRecordCount();
};

/////////////////////////////////////////////////////////////
int ExecuteCommand(const char *cmd,const char *cmdarg,std::string &output);

#endif // _KS_FILESVR_H_

