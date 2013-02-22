#ifndef _YKTCLT_H_
#define _YKTCLT_H_

#include "bccclt.h"

class KS_YKT_Clt 
{
private:
	XDHANDLE handler_;
	int resp_row_;
	int resp_read_row_;
	int req_row_;
	int record_count_;
	int time_out_;
	int err_code_;
	int return_code_;
	char err_msg_[512];
	static int drtp_no_;
	static int main_func_;

	void Reset();
	bool SendNextRequest();
public:
	static char s_global_xpack_path[1024];
	static bool Initialize(const char *ip,int port,int main_func);
	static bool Initialize2(int drtpno,int main_func);
	static bool Uninitialize();
	static bool IsInitialized() { return (KS_YKT_Clt::drtp_no_ >= 0); }
	static void SetDebug(int b);
	static void set_xpack_path(const char *path);
	KS_YKT_Clt();
	KS_YKT_Clt(const char *xpack_data);
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
	char* GetReturnMsg(char *msg) const;
	
};

#ifndef GET_PACK_STR
#define GET_PACK_STR(c,p,v) do {\
	c.GetStringFieldByName(p,v,sizeof(v)-1); }while(0)
#endif

#endif // _YKTCLT_H_
