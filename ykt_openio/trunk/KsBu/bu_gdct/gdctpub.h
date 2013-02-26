#ifndef _GDCTPUB_H_
#define _GDCTPUB_H_


#include "slist.h"
#include "cpack.h"
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
#include "mypub.h"
#include "bufunc.h"
#include "bupub.h"
#include "ksbu.h"
typedef struct {
	int datalen; // ���ĳ���
	int seqno;
	char msgtype[5]; // ҵ������
	char msgcode[7]; // ��Ϣ��
	char respcode[5]; // ��Ӧ��
	int bodylen; // ���峤��
	char body[512]; // ���ݰ���
}gdct_msg_t;

extern char g_gdct_pswd[33];
extern char g_gdct_phone_num[14];
extern int g_mainsvr_func;
extern int g_mainsvr_drtpno;
extern int g_timeout;
extern char g_xunyuan_svrip[30];
extern int g_xunyuan_svrport;

void PackCTRequest(gdct_msg_t* mymsg,char *buffer,int &buflen);
int CTSendAndRecv(const char *buffer,int buflen,gdct_msg_t *mymsg,long timeout);
void TranslateErrMsg(const char *retcode,char *errmsg);
int GetRespDataAsString(gdct_msg_t* mymsg,int begin,int len,char *value);
int GetRespDataAsInteger(gdct_msg_t* mymsg,int begin,int len,int &value);

#endif // _GDCTPUB_H_
