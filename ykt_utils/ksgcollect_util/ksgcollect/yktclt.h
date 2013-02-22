#ifndef _YKTCLT_H_
#define _YKTCLT_H_

#include "bccclt.h"

class KS_YKT_Clt 
{
private:
	XDHANDLE handler_;
	int resp_row_;
	int req_row_;
	int record_count_;
	int time_out_;
	int err_code_;
	int return_code_;
	int drtp_idx_;
	char err_msg_[512];
	int main_func_;

	void Reset();
	bool SendNextRequest();
	struct drtp_ip_def_t{
		int drtp_no_;
		int drtp_port_;
		char drtp_ip_[20];
	};
	static char s_global_xpack_path[1024];
	static const int MAX_DRTP_COUNT = 20;
	static drtp_ip_def_t s_drtps[MAX_DRTP_COUNT];
	static int s_drtp_count;
	static int s_has_init;
	static int find_drtp_by_ip(const char *ip);

	/////////////////////////////
	int init_drtp(const char *ip,int port,int main_func);
public:
	static bool Initialize();
	static bool Uninitialize();
	static void set_xpack_path(const char *path);
	KS_YKT_Clt(const char *ip,int port,int main_func);
	KS_YKT_Clt(const char *xpack_data,const char *ip,int port,int main_func);
	~KS_YKT_Clt();
	KS_YKT_Clt(const KS_YKT_Clt &rhs);
	KS_YKT_Clt& operator=(const KS_YKT_Clt &rhs);
	void ResetHandler();
	bool SetIntFieldByName(char * FieldName,int Value);
	bool SetDoubleFieldByName(char * FieldName,double Value);
	bool SetStringFieldByName(char * FieldName,char * Value);
	
	bool GetIntFieldByName(char * FieldName,int * Value);
 	bool GetDoubleFieldByName(char * FieldName,double * Value);
  	bool GetStringFieldByName(char * FieldName,char * Value,int ValueBufferSize);

	bool SendRequest(int request,int timeout=1000);
	bool HasMoreRecord();
	bool GetNextPackage();
	int GetReturnCode() const
	{
		return return_code_;
	}
	void GetReturnMsg(char *msg) const;
	int GetErrCode() const
	{
		return err_code_;
	}
};

#ifndef GET_PACK_STR
#define GET_PACK_STR(c,p,v) do {\
	c.GetStringFieldByName(p,v,sizeof(v)-1); }while(0)
#endif

#endif // _YKTCLT_H_
