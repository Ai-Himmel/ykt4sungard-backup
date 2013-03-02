#ifndef _GDCTPUB_H_
#define _GDCTPUB_H_

#include "ksglobal.h"
DECLARE_NAMESPACE_BEGIN(GDCT)

typedef struct {
	int datalen; // ���ĳ���
	int seqno;
	char msgtype[5]; // ҵ������
	char msgcode[7]; // ��Ϣ��
	char respcode[5]; // ��Ӧ��
	int bodylen; // ���峤��
	char body[512]; // ���ݰ���
}gdct_msg_t;


void PackCTRequest(gdct_msg_t* mymsg,char *buffer,int &buflen);
void UnPackCTRequest(gdct_msg_t* mymsg,char *buffer,int buflen);
int GetBufferAsInteger(const char *buf,int len,int &value);
int GetBufferAsString(const char *buf,int len,char *value);
int GetRespDataAsString(gdct_msg_t* mymsg,int begin,int len,char *value);
int GetRespDataAsInteger(gdct_msg_t* mymsg,int begin,int len,int &value);

DECLARE_NAMESPACE_END(GDCT);

#endif // _GDCTPUB_H_
