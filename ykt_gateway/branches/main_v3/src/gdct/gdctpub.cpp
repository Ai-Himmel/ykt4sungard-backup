#include "gdct/gdctpub.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "netutil.h"

DECLARE_NAMESPACE_BEGIN(GDCT)
struct {
	const char *errcode;
	const char * errmsg;
}g_gcct_errmsg[]=
{
	{"0000","交易成功"},
	{"1001","登录失败，企业信息错误（企业代码或者密码等）"},
	{"1002","登录失败，协议版本错误（不支持的协议）"},
	{"1003","登录失败，重复登录（不允许多个连接同时使用）"},
	{"1004","登录失败，未授权IP登录"},
	{"2001","注销失败"},
	{"3001","交易失败，系统繁忙"},
	{"3002","服务密码不正确"},
	{"3003","未注册"},
	{"3004","尚未开通业务"},
	{"3005","业务已被暂停"},
	{"3006","已注销"},
	{"3007","提交的数据格式和内容不正确"},
	{"3008","帐户余额不足"},
	{"3009","交易金额小于最小金额"},
	{"3010","交易金额大于最大金额"},
	{"3011","无交易返销不成功"},
	{"3012","超过允许最大的返销次数"},
	{"3013","佣金不足，返销失败"},
	{"3014","重复充值"},
	{"3015","充值面额不在正确"},
	{"3016","没有对应的主叫号码（企业虚拟号码）"},
	{"3017","此时间段服务暂停"},
	{"3018","不合法的用户号码"},
	{"3019","未开户或者异地手机"},
	{"3020","用户手机号码状态不正确"},
	{"3021","取消充值后余额为负"},
	{"3022","用户进入保留期不能取消充值"},
	{"3023","重复冲正"},
};
void PackCTRequest(gdct_msg_t* mymsg,char *buffer,int &buflen)
{
	int offset;
	sprintf(buffer,"%04d",mymsg->bodylen +24);
	offset = 4;
	_snprintf(buffer+offset,10,"%010d",mymsg->seqno);
	offset += 10;
	memcpy(buffer+offset,mymsg->msgtype,4);
	offset += 4;
	memcpy(buffer+offset,mymsg->msgcode,6);
	offset += 6;
	if(mymsg->bodylen > 0)
	{
		memcpy(buffer+offset,mymsg->body,mymsg->bodylen);
	}
	buflen = offset + mymsg->bodylen;
}
void UnPackCTRequest(gdct_msg_t* mymsg,char *buffer,int buflen)
{
	int offset;
	if(buflen < 24)
	{
		strcpy(mymsg->respcode,"9999");
	}
	offset = 0;
	GetBufferAsInteger(buffer,4,mymsg->datalen);
	offset += 4;
	GetBufferAsInteger(buffer+offset,10,mymsg->seqno);
	offset += 10;
	GetBufferAsString(buffer+offset,4,mymsg->msgtype);
	offset += 4;
	GetBufferAsString(buffer+offset,6,mymsg->msgcode);
	offset += 6;
	// 判断长度
	if(offset + 4 < buflen)
	{
		GetBufferAsString(buffer+offset,4,mymsg->respcode);
		offset += 4;
		if(offset < buflen)
		{
			mymsg->bodylen = buflen - offset;
			memcpy(mymsg->body,buffer+offset,mymsg->bodylen);
		}
	}
}

int GetBufferAsInteger(const char *buf,int len,int &value)
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
	value = atoi(maxbuf);
	return 0;
}
int GetBufferAsString(const char *buf,int len,char *value)
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
/*
int CTSendAndRecv(const char *buffer,int buflen,gdct_msg_t *mymsg,long timeout)
{
	TCPSockStream tcp;
	char resp_data[512]="";
	int ret,offset;
	if(!tcp.connect(g_xunyuan_svrip,g_xunyuan_svrport,timeout))
	{
		// connect error
		g_LogFile.WriteLogEx(1001,"连接到讯源失败,svr ip[%s:%d]",g_xunyuan_svrip,g_xunyuan_svrport);
		return -2;
	}
	if(tcp.send_n((const unsigned char*)buffer,buflen,timeout)<0)
	{
		g_LogFile.WriteLogEx(1001,"发送请求到讯源失败");
		return -1;
	}
	ret = tcp.recv_n((unsigned char*)resp_data,4,timeout);
	if(ret<=0)
	{
		// 接收错误
		g_LogFile.WriteLogEx(1001,"接收讯源应答失败,ret[%d]LastErr[%d]",ret,tcp.get_last_error());
		return -1;
	}
	mymsg->datalen = atoi(resp_data);
	if(mymsg->datalen < 64 || mymsg->datalen > 512)
	{
		g_LogFile.WriteLogEx(1001,"接收讯源应答包头错误,收到长度[%d]错误",mymsg->datalen);
		return -3;
	}
	offset = 4;
	ret = tcp.recv_n((unsigned char*)resp_data+offset,mymsg->datalen-4,timeout);
	if(ret<=0)
	{
		g_LogFile.WriteLogEx(1001,"接收讯源包体错误，ret[%d]",ret);
		return -1;
	}
	GetBufferAsInteger(resp_data+offset,10,mymsg->seqno);
	offset += 10;
	GetBufferAsString(resp_data+offset,4,mymsg->msgtype);
	offset += 4;
	GetBufferAsString(resp_data+offset,6,mymsg->msgcode);
	offset += 6;
	GetBufferAsString(resp_data+offset,4,mymsg->respcode);
	offset += 4;
	// 消息体
	memcpy(mymsg->body,resp_data+offset,mymsg->datalen-offset);
	return 0;
}
*/

int GetRespDataAsString(gdct_msg_t* mymsg,int begin,int len,char *value)
{
	return GetBufferAsString(mymsg->body+begin,len,value);
}
int GetRespDataAsInteger(gdct_msg_t* mymsg,int begin,int len,int &value)
{
	return GetBufferAsInteger(mymsg->body+begin,len,value);
}

DECLARE_NAMESPACE_END(GDCT);