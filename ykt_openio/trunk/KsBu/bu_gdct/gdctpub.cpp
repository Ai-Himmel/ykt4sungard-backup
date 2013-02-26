#include "gdctpub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "svrlink.h"
#include "bdefine.h"
#include "logfile.h"
#include "pubfunc.h"
#include "mypub.h"
#include "bufunc.h"
#include "tcpsock.h"

char g_gdct_pswd[33];
char g_gdct_phone_num[14];
int g_mainsvr_func;
int g_mainsvr_drtpno;
int g_timeout;
char g_xunyuan_svrip[30];
int g_xunyuan_svrport;

struct {
	const char *errcode;
	const char * errmsg;
}g_gcct_errmsg[]=
{
	{"0000","���׳ɹ�"},
	{"1001","��¼ʧ�ܣ���ҵ��Ϣ������ҵ�����������ȣ�"},
	{"1002","��¼ʧ�ܣ�Э��汾���󣨲�֧�ֵ�Э�飩"},
	{"1003","��¼ʧ�ܣ��ظ���¼��������������ͬʱʹ�ã�"},
	{"1004","��¼ʧ�ܣ�δ��ȨIP��¼"},
	{"2001","ע��ʧ��"},
	{"3001","����ʧ�ܣ�ϵͳ��æ"},
	{"3002","�������벻��ȷ"},
	{"3003","δע��"},
	{"3004","��δ��ͨҵ��"},
	{"3005","ҵ���ѱ���ͣ"},
	{"3006","��ע��"},
	{"3007","�ύ�����ݸ�ʽ�����ݲ���ȷ"},
	{"3008","�ʻ�����"},
	{"3009","���׽��С����С���"},
	{"3010","���׽����������"},
	{"3011","�޽��׷������ɹ�"},
	{"3012","�����������ķ�������"},
	{"3013","Ӷ���㣬����ʧ��"},
	{"3014","�ظ���ֵ"},
	{"3015","��ֵ������ȷ"},
	{"3016","û�ж�Ӧ�����к��루��ҵ������룩"},
	{"3017","��ʱ��η�����ͣ"},
	{"3018","���Ϸ����û�����"},
	{"3019","δ������������ֻ�"},
	{"3020","�û��ֻ�����״̬����ȷ"},
	{"3021","ȡ����ֵ�����Ϊ��"},
	{"3022","�û����뱣���ڲ���ȡ����ֵ"},
	{"3023","�ظ�����"},
};
void PackCTRequest(gdct_msg_t* mymsg,char *buffer,int &buflen)
{
	int offset;
	sprintf(buffer,"%04d",mymsg->bodylen +24);
	offset = 4;
#ifdef WIN32
	_snprintf(buffer+offset,10,"%010d",mymsg->seqno);
#else
	snprintf(buffer+offset,10,"%010d",mymsg->seqno);
#endif
	offset += 10;
	memcpy(buffer+offset,mymsg->msgtype,4);
	offset += 4;
	memcpy(buffer+offset,mymsg->msgcode,6);
	offset += 6;
	memcpy(buffer+offset,mymsg->body,mymsg->bodylen);
	buflen = offset + mymsg->bodylen;
}

static int GetBufferAsInteger(const char *buf,int len,int &value)
{
	int i;
	char maxbuf[512] = "";
	if(len > 511)
		return -1;
	i = 0;
	while(i<len && buf[i]=='0') i++; 
	if(i == len)
	{
		value = 0;
		return 0;
	}
	memcpy(maxbuf,buf+i,len-i);
	value = atol(maxbuf);
	return 0;
}
static int GetBufferAsString(const char *buf,int len,char *value)
{
	int i,j;
	if(len > 511)
		return -1;
	for(i=0,j=0;i<len;++i)
	{
		if(buf[i]==' ')
			continue;
		if(buf[i]=='\0')
			break;
		value[j++] = buf[i];
	}
	value[j] = '\0';
	return 0;
}
int CTSendAndRecv(const char *buffer,int buflen,gdct_msg_t *mymsg,long timeout)
{
	TCPSockStream tcp;
	char resp_data[512]="";
	int ret,offset;
	if(tcp.connect(g_xunyuan_svrip,g_xunyuan_svrport,timeout)!=0)
	{
		// connect error
		g_LogFile.WriteLogEx(1001,"���ӵ�ѶԴʧ��,svr ip[%s:%d]",g_xunyuan_svrip,g_xunyuan_svrport);
		return -2;
	}
	if(tcp.send_n((const unsigned char*)buffer,buflen,timeout)<0)
	{
		g_LogFile.WriteLogEx(1001,"��������ѶԴʧ��");
		return -1;
	}
	ret = tcp.recv_n((unsigned char*)resp_data,4,timeout);
	if(ret<=0)
	{
		// ���մ���
		g_LogFile.WriteLogEx(1001,"����ѶԴӦ��ʧ��,ret[%d]LastErr[%d]",ret,tcp.get_last_error());
		return -1;
	}
	mymsg->datalen = atoi(resp_data);
	if(mymsg->datalen < 24 || mymsg->datalen > 512)
	{
		g_LogFile.WriteLogEx(1001,"����ѶԴӦ���ͷ����,�յ�����[%d]����",mymsg->datalen);
		return -3;
	}
	offset = 4;
	ret = tcp.recv_n((unsigned char*)resp_data+offset,mymsg->datalen-4,timeout);
	if(ret<=0)
	{
		g_LogFile.WriteLogEx(1001,"����ѶԴ�������ret[%d]",ret);
		return -1;
	}
	GetBufferAsInteger(resp_data+offset,10,mymsg->seqno);
	offset += 10;
	GetBufferAsString(resp_data+offset,4,mymsg->msgtype);
	offset += 4;
	GetBufferAsString(resp_data+offset,6,mymsg->msgcode);
	offset += 6;
	if(mymsg->datalen>24)
	{
		GetBufferAsString(resp_data+offset,4,mymsg->respcode);
		offset += 4;
		if(mymsg->datalen<28)
			return -1;
	}
	// ��Ϣ��
	memcpy(mymsg->body,resp_data+offset,mymsg->datalen-offset);
	mymsg->bodylen = mymsg->datalen-offset;
	return 0;
}

void TranslateErrMsg(const char *retcode,char *errmsg)
{
	int i;
	for(i = 0;i < sizeof(g_gcct_errmsg)/sizeof(g_gcct_errmsg[0]);++i)
	{
		if(strncmp(g_gcct_errmsg[i].errcode,retcode,4)==0)
		{
			strcpy(errmsg,g_gcct_errmsg[i].errmsg);
			return;
		}
	}
	strcpy(errmsg,"δ֪����");
}

int GetRespDataAsString(gdct_msg_t* mymsg,int begin,int len,char *value)
{
	return GetBufferAsString(mymsg->body+begin,len,value);
}
int GetRespDataAsInteger(gdct_msg_t* mymsg,int begin,int len,int &value)
{
	return GetBufferAsInteger(mymsg->body+begin,len,value);
}