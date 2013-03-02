/* ----------------------------------------------------------
 * 程序名称：bank_ccb_hljit.cpp
 * 创建日期：2011-07-30
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：黑工程建行接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_hljit.h"
#include "tcp.h"

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

//按照通用接口规范进行封装各自银行的接口
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen=0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	char msg[512]="";
	char tmp[24] = "";

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SPHONE,0);
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间(毫秒)
	
	memset(msg,0x20,sizeof msg);						// 填充空格
	memcpy(msg+2,TRANS_CODE,2);						//校方交易码
	memcpy(msg+90, rPack->sdate0,8);					// 交易日期
	memcpy(msg+98, rPack->stime0,6);					// 交易时间
	STRLENCPY(msg+104,rPack->sphone,10);				//校园卡卡号(使用学工号)
	STRLENCPY(msg+129,rPack->scust_limit,16);			//真实姓名
	STRLENCPY(msg+145, rPack->scust_limit2,20);			// 银行卡号
	
	sprintf(tmp,"%d",D2I(rPack->damt0*100));				
	STRLENCPY(msg+165, tmp,15);						// 转帐金额

	STRLENCPY(msg+195, rPack->sholder_ac_no+8,6);		// 校方流水号
	STRLENCPY(msg+224, SCHOOLCODE_HLJIT,16);			// 学校代码

	msg[HLJIT_MSG_LEN]=0;
	writelog(LOG_INFO,"trans send[%s]",msg);

	writelog(LOG_INFO,"Connect to bank ,ip_addr[%s],port[%d] ",host,port);
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send(msg,HLJIT_MSG_LEN);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"发送数据错误");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	writelog(LOG_DEBUG,"Send ret [%d] ",ret);
	
	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(msg, HLJIT_MSG_LEN, timeout);					// 收报文内容
	msg[HLJIT_MSG_LEN]=0;
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",msg,ret);

	if (ret != HLJIT_MSG_LEN)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据包体错误");
		goto r_ret;  
	}

	if(memcmp(msg+2,TRANS_CODE,2) !=0)						// 前2位应该是 01
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据交易码错误");
		goto r_ret;  
	}
					
	if(memcmp(msg+4,HLJIT_TRADE_SUCC,6)!=0)
	{
		tcpsocket.Close();
		memcpy(szMsg,msg+10,80);						// 银行返还的错误信息
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(tmp,msg+203,21);						// 银行流水号
		trim(tmp);
		STRLENCPY(out_pack->sphone,tmp,21);				
	}
	writelog(LOG_INFO,"trans:bank transno[%s],lvol1[%d]",out_pack->sphone,out_pack->lvol1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// 冲正
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int msglen = 0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	char msg[512]="";
	char tmp[24] = "";
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);						// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间

	memset(msg,0x20,sizeof msg);						// 填充空格
	memcpy(msg+2,REV_TRANS_CODE,2);					//校方交易码
	memcpy(msg+90, rPack->sdate0,8);					// 交易日期
	memcpy(msg+98, rPack->stime0,6);					// 交易时间
	STRLENCPY(msg+104,rPack->sphone,10);				//校园卡卡号(使用学工号)
	STRLENCPY(msg+129,rPack->scust_limit,16);			//真实姓名
	STRLENCPY(msg+145, rPack->scust_limit2,20);			// 银行卡号
	
	sprintf(tmp,"%d",D2I(rPack->damt0*100));				
	STRLENCPY(msg+165, tmp,15);						// 转帐金额

	STRLENCPY(msg+195, rPack->sholder_ac_no+8,6);		// 校方流水号
	STRLENCPY(msg+224, SCHOOLCODE_HLJIT,16);			// 学校代码

	msg[HLJIT_MSG_LEN]=0;
	writelog(LOG_INFO,"reverse send[%s]",msg);
	
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send(msg,HLJIT_MSG_LEN);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"发送数据错误");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(msg, HLJIT_MSG_LEN, timeout);					// 收报文内容
	msg[HLJIT_MSG_LEN]=0;
	writelog(LOG_INFO,"transRev recv[%s],recvlen[%d]",msg,ret);

	if (ret != HLJIT_MSG_LEN)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据包体错误");
		goto r_ret;  
	}

	if(strncmp(msg+2,REV_TRANS_CODE,2) !=0)							// 前2位应该是 02
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据交易码错误");
		goto r_ret;  
	}
					
	if(memcmp(msg+4,HLJIT_TRADE_SUCC,6)!=0)
	{
		tcpsocket.Close();
		memcpy(szMsg,msg+10,80);									// 银行返还的错误信息
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(tmp,msg+203,21);						// 银行流水号
		trim(tmp);
		STRLENCPY(out_pack->sphone,tmp,21);				
	}
	writelog(LOG_INFO,"transrev:bank transno[%s],lvol1[%d]",out_pack->sphone,out_pack->lvol1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

// 查询银行卡余额
int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	char msg[512]="";
	char tmp[16]="";

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SALL_NAME,F_DAMT0,F_DAMT1,0);
	
	des2src(host,rPack->scust_auth);						// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间

	memset(msg,0x20,sizeof msg);						// 填充空格
	memcpy(msg+2,QUERY_BALA,2);						//校方交易码
	memcpy(msg+90, rPack->sdate0,8);					// 交易日期
	memcpy(msg+98, rPack->stime0,6);					// 交易时间
	STRLENCPY(msg+145, rPack->scust_limit2,20);			// 银行卡号
	STRLENCPY(msg+224, SCHOOLCODE_HLJIT,16);			// 学校代码

	msg[HLJIT_MSG_LEN]=0;
	writelog(LOG_INFO,"querybala send[%s]",msg);

	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send(msg,HLJIT_MSG_LEN);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
	      	tcpsocket.Close();
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		strcpy(szMsg,"发送数据错误");
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
		tcpsocket.Close();
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	memset(msg,0,sizeof msg);
	ret = tcpsocket.Recv(msg, HLJIT_MSG_LEN, timeout);					// 收报文内容
	msg[HLJIT_MSG_LEN]=0;
	writelog(LOG_INFO,"querybala recv[%s],recvlen[%d]",msg,ret);

	if (ret != HLJIT_MSG_LEN)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据包体错误");
		goto r_ret;  
	}

	if(memcmp(msg+2,QUERY_BALA,2) !=0)							// 前2位应该是 05
	{
		out_pack->lvol1 = -1;									//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据交易码错误");
		goto r_ret;  
	}
				
	if(memcmp(msg+4,HLJIT_TRADE_SUCC,6)!=0)
	{
		tcpsocket.Close();
		memcpy(szMsg,msg+10,80);									// 银行返还的错误信息
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(tmp,msg+180,15);
		trim(tmp);
		out_pack->damt0 = D4U5(atof(tmp)/100.0, 2);
		out_pack->damt1=	out_pack->damt0;	
		
	}
	writelog(LOG_INFO,"querybala:cutname[%s],actbala[%f],actavlbala[%f]",out_pack->sall_name,out_pack->damt0,out_pack->damt1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


int Bank_Bind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return 0;
}

int Bank_UnBind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return 0;
}

int Bank_Querybind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return 0;
}

