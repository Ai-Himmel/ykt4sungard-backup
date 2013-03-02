#ifndef _GDCTPUB_H_
#define _GDCTPUB_H_

#include "ksglobal.h"
DECLARE_NAMESPACE_BEGIN(GDCT)

typedef struct {
	int datalen; // 报文长度
	int seqno;
	char msgtype[5]; // 业务类型
	char msgcode[7]; // 消息码
	char respcode[5]; // 响应码
	int bodylen; // 包体长度
	char body[512]; // 数据包体
}gdct_msg_t;


void PackCTRequest(gdct_msg_t* mymsg,char *buffer,int &buflen);
void UnPackCTRequest(gdct_msg_t* mymsg,char *buffer,int buflen);
int GetBufferAsInteger(const char *buf,int len,int &value);
int GetBufferAsString(const char *buf,int len,char *value);
int GetRespDataAsString(gdct_msg_t* mymsg,int begin,int len,char *value);
int GetRespDataAsInteger(gdct_msg_t* mymsg,int begin,int len,int &value);

DECLARE_NAMESPACE_END(GDCT);

#endif // _GDCTPUB_H_
