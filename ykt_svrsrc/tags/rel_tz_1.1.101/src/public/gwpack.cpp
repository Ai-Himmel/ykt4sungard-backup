#include "gwpack.h"
#include "tcp.h"
#include "errdef.h"
#include "pubfunc.h"
#include <stdlib.h>
#include <stdio.h>

int SendToServer(gw_server_info_t* svr,int funcno,const char* data)
{
	int ret = E_POWER_INTERNAL_ERR;
	int sendbytes = 0;
	if(!svr->sock->ConnectTcp(svr->server_ip,svr->server_port,5))
	{
		return E_POWER_CONN_SVR;
	}
	KSG_GW_PACK_t * pack = NULL;
	int datalen = strlen(data);
	int packlen = sizeof(KSG_GW_PACK_t) - sizeof(char[1]) + datalen;
	if((pack = (KSG_GW_PACK_t*)malloc(packlen)) == NULL)
	{
		ret = E_POWER_INTERNAL_ERR;
	}
	else
	{
		memset(pack,0,packlen);
		pack->func_no = htonl(funcno);
		pack->length = htonl(datalen);
		pack->enc_type = 0;
		pack->pack_index = htonl(1);
		pack->next_pack = 0;
		memcpy(pack->data,data,datalen);
		CalcMD5((unsigned char*)pack->data,datalen,(unsigned char*)pack->CRC);
		sendbytes = svr->sock->Send((char*)pack,packlen);
		if(-1 == sendbytes)
		{
			ret = E_POWER_CONN_SVR;
		}
		else if(-2 == sendbytes || sendbytes != packlen)
		{
			ret = E_POWER_TRANS_ERR;
		}
		else
		{
			//成功
			ret = 0;
		}
	}
	if(pack)
		free(pack);
	// 如果处理失败,关闭连接
	if(ret)
		svr->sock->Close();
	return ret;
}

int RecvFromServer(gw_server_info_t* svr,KSG_GW_PACK_t** resp)
{
	int ret;
	int recvbytes;
	int packlen;
	unsigned char md5[16];
	if(svr->sock->IsFree())
		return E_POWER_CONN_SVR;
	KSG_GW_PACK_t * pack = NULL;
	if((pack = (KSG_GW_PACK_t*)malloc(sizeof(KSG_GW_PACK_t))) == NULL)
	{
		ret = E_POWER_INTERNAL_ERR;
	}
	else if((recvbytes = svr->sock->Recv((char*)pack,sizeof(int),1000)) == sizeof(int))
	{
		pack->length = ntohl(pack->length);
		packlen = sizeof(KSG_GW_PACK_t) - sizeof(char[1]) + pack->length;
		if((pack = (KSG_GW_PACK_t*)realloc(pack,packlen)) == NULL)
		{
			ret = E_POWER_INTERNAL_ERR;
		}
		else if((svr->sock->Recv(((char*)pack)+sizeof(int),packlen-sizeof(int),1000) 
			== (packlen-sizeof(int))))
		{
			if(pack->length > 0)
			{
				CalcMD5((unsigned char*)pack->data,pack->length,md5);
				if(memcmp(md5,pack->CRC,sizeof md5))
				{
					writelog(LOG_ERR,"数据检查错误");
					ret = E_POWER_RECV_ERR;
				}
				else
				{
					pack->func_no = ntohl(pack->func_no);
					pack->pack_index = ntohl(pack->pack_index);
					pack->next_pack = ntohl(pack->next_pack);
					pack->retcode = ntohl(pack->retcode);
					ret = 0;
				}
			}
			else
			{
				pack->func_no = ntohl(pack->func_no);
				pack->pack_index = ntohl(pack->pack_index);
				pack->next_pack = ntohl(pack->next_pack);
				pack->retcode = ntohl(pack->retcode);
				ret = 0;
			}
		}
		else
		{
			ret = E_POWER_CONN_SVR;
		}
	}
	else
	{
		ret = E_POWER_TRANS_ERR;
	}
	*resp = pack;
	svr->sock->Close();
	return ret;
}

