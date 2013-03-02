/* ----------------------------------------------------------
 * 程序名称：bank_boc_yntv.cpp
 * 创建日期：2011-01-12
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：云南电大中国银行接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "shem.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_boc_yntv.h"
#include "tcp.h"
#include "d3des.h"


#define BANK_LOGIN	(shm[1]==1)			// 是否签到
#define MSG_LEN 170						// 银行数据包定长

ERRDEF g_errdef[]= {
{"00","交易成功"},
{"01","卡已挂失"},
{"02","帐户状态不正常"},
{"03","余额不足"},
{"04","其他错误"},
{"05","无此帐户"},
{"06","身份效验错误"},
{"07","系统错误"},
{"08","已签约（签约时用）"},
{"09","未签约（交易和解约时用）"},
{"10","已用其它银行卡签约"},
{"99","帐户其他错误"}
};

char * GetErrMsg(char *errcode)
{
	for (int i=0;i<sizeof g_errdef;i++)
	{
		if(memcmp(errcode,g_errdef[i].errcode,2) ==0)
			return g_errdef[i].errmsg;
	}
	return "银行未知错误";
}

int GenSendMsg(MEGBODY msgbody,unsigned char *msg,bool bdynamic)
{
	int index=0;
	int offset=2;											// 2 位交易码略过
	char sysdate[9]="";
	char systime[7]="";
	unsigned char k[17] = "";
	unsigned char clear[17] = "";
	getsysdate(sysdate);
	getsystime(systime);

	memcpy(msgbody.TradeDate,sysdate,8);
	memcpy(msgbody.TradeTime,systime,6);
	strncpy(msgbody.CustNo,SCHOOLCODE,strlen(SCHOOLCODE));		// 院校代码

	writelog(LOG_INFO,"send pre-encrypt [%s]",(char*)&msgbody);

	if(bdynamic)						// 动态密钥
	{
		memcpy((char*)k,shm+10,8);
	}
	else
		memcpy((char*)k, sysdate,8);
	for(;index<sizeof (msgbody)-offset;index+=8)
	{
		memcpy((char*)clear,(char*)(&msgbody)+index+offset,8);
		deskey(k, 0);
		Ddes(clear, msg+index+offset);							
	}
	memcpy(msg,msgbody.TradeCode,2);							// 交易码
	return 0;
}

int GetRecvMsg(MEGBODY &msgbody,unsigned char *msg,bool bdynamic)
{
	int index=0;
	int offset=2;											// 2 位交易码略过
	char sysdate[9]="";
	unsigned char k[17] = "";
	unsigned char secret[17] = "";
	getsysdate(sysdate);

	if(bdynamic)						// 动态密钥
	{
		memcpy((char*)k,shm+10,8);
	}
	else
		memcpy((char*)k, sysdate,8);
	
	for(;index<MSG_LEN-offset;index+=8)
	{
		memcpy((char*)secret,(char*)msg+index+offset,8);
		deskey(k, 1);
		Ddes(secret, (unsigned char*)(&msgbody)+index+offset);								
	}
	memcpy(msgbody.TradeCode,msg,2);
	return 0;	
}
int Bank_Bind_Process(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg,char *tradecode)
{
	int ret=0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"签到失败ret[%d]",ret);
			return ret;
		}
	}
	
	char tmp[20]="";
	unsigned char msg[256]="";
	MEGBODY msgbody;
	memset(&msgbody,' ',sizeof msgbody);

	memcpy(msgbody.TradeCode,tradecode,2);

	memset(tmp,0,sizeof tmp);
	ret = sprintf(tmp,"%d",rPack->lvol2);			// 客户号
	memcpy(msgbody.CustAccountNo,tmp,ret);
	strncpy(msgbody.BankCardNo, rPack->scard0,strlen(rPack->scard0));		// 银行卡号
	strncpy(msgbody.IdentityCode, rPack->semail2,strlen(rPack->semail2));	// 身份证号
	strncpy(msgbody.Name,rPack->sall_name,strlen(rPack->sall_name));			// 姓名

	// 生成发送报文
	GenSendMsg(msgbody, msg, true);
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LSAFE_LEVEL,F_VSVARSTR0,F_SCARD0,0);
	
	out_pack->lsafe_level=E_COMMON_ERR;
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间(毫秒)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,MSG_LEN);
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
	memset(tmp,0,sizeof tmp);
	ret = tcpsocket.Recv((char*)msg, MSG_LEN, timeout);					// 收报文内容
	if (ret != MSG_LEN)
	{
		des2src(out_pack->vsvarstr0,"接收银行数据包体错误");
		goto r_ret;  
	}
	GetRecvMsg(msgbody, msg, true);
	writelog(LOG_INFO,"bind_process recv[%s]",(char*)&msgbody);
	
	memcpy(tmp,msgbody.RetCode,2);
	out_pack->lsafe_level=atoi(tmp);
	des2src(out_pack->vsvarstr0,GetErrMsg(tmp));
	memcpy(out_pack->scard0,msgbody.BankCardNo,20);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_Bind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,BIND_BANK);
}

int Bank_UnBind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,UN_BIND_BANK);
}

int Bank_Querybind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
	return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,QUERY_BIND);
}

//按照通用接口规范进行封装各自银行的接口
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"签到失败ret[%d]",ret);
			return ret;
		}
	}

	char tmp[20]="";
	unsigned char msg[256]="";
	MEGBODY msgbody;
	memset(&msgbody,' ',sizeof msgbody);

	memcpy(msgbody.TradeCode,TRANS_CODE,2);			// 圈存充值

	memset(tmp,0,sizeof tmp);
	ret = sprintf(tmp,"%d",rPack->lvol2);											// 客户号
	memcpy(msgbody.CustAccountNo,tmp,ret);
	strncpy(msgbody.BankCardNo, rPack->scust_limit2,strlen(rPack->scust_limit2));		// 银行卡号
	strncpy(msgbody.IdentityCode, rPack->scust_auth2,strlen(rPack->scust_auth2));		// 身份证号
	strncpy(msgbody.Name,rPack->scust_limit,strlen(rPack->scust_limit));				// 姓名
	strncpy(msgbody.CustSn,rPack->sholder_ac_no+6,8);								// 校园端流水号

	memset(tmp,0,sizeof tmp);
	sprintf(tmp,"%09d",D2I(rPack->damt0*100));			// 转账金额,分为单位
	memcpy(msgbody.TransMoney,tmp,9);

	// 生成发送报文
	GenSendMsg(msgbody, msg,true);

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SPHONE,0);
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间(毫秒)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,MSG_LEN);
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
	memset(tmp,0,sizeof tmp);
	ret = tcpsocket.Recv((char*)msg, MSG_LEN, timeout);					// 收报文内容
	if (ret != MSG_LEN)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据包体错误");
		goto r_ret;  
	}
	
	GetRecvMsg(msgbody, msg, true);	

	writelog(LOG_INFO,"trans  recv[%s]",(char*)&msgbody);
	
	if(memcmp(msgbody.TradeCode,TRANS_CODE,2) !=0)							// 前2位应该是 01
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"充值接收银行数据交易码错误");
		goto r_ret;  
	}
	
	if(memcmp(msgbody.RetCode,"00",2)!=0)						// 银行返回失败
	{
		des2src(szMsg,GetErrMsg(msgbody.RetCode));
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sphone,msgbody.BankSn,8);				// 银行流水号
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
	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"签到失败ret[%d]",ret);
			return ret;
		}
	}

	char tmp[20]="";
	unsigned char msg[256]="";
	MEGBODY msgbody;
	memset(&msgbody,' ',sizeof msgbody);

	memcpy(msgbody.TradeCode,REV_TRANS_CODE,2);			// 圈存冲正

	memset(tmp,0,sizeof tmp);
	ret = sprintf(tmp,"%d",rPack->lvol2);											// 客户号
	memcpy(msgbody.CustAccountNo,tmp,ret);
	strncpy(msgbody.BankCardNo, rPack->scust_limit2,strlen(rPack->scust_limit2));		// 银行卡号
	strncpy(msgbody.IdentityCode, rPack->scust_auth2,strlen(rPack->scust_auth2));		// 身份证号
	strncpy(msgbody.Name,rPack->scust_limit,strlen(rPack->scust_limit));				// 姓名
	
	strncpy(msgbody.CustSn,rPack->sholder_ac_no+6,8);								// 校园端流水号
	
	memset(tmp,0,sizeof tmp);
	sprintf(tmp,"%09d",D2I(rPack->damt0*100));			// 转账金额,分为单位
	memcpy(msgbody.TransMoney,tmp,9);

	// 生成发送报文
	GenSendMsg(msgbody, msg, true);
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,F_SPHONE,0);

	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;								// 等待银行超时时间

	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,MSG_LEN);
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
	
	ret = tcpsocket.Recv((char*)msg, MSG_LEN, timeout);					// 收报文内容
	if (ret != MSG_LEN)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据包体错误");
		goto r_ret;  
	}

	GetRecvMsg(msgbody, msg, true);	
	writelog(LOG_INFO,"transRev recv[%s]",(char*)&msgbody);
	if(memcmp(msgbody.TradeCode,REV_TRANS_CODE,2) !=0)							// 前2位应该是 11
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"冲正接收银行数据交易码错误");
		goto r_ret;  
	}

	if(memcmp(msgbody.RetCode,"00",2)!=0)						// 银行返回失败
	{
		des2src(szMsg,GetErrMsg(msgbody.RetCode));
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sphone,msgbody.BankSn,8);				// 银行流水号
	}
	writelog(LOG_INFO,"trans:bank transno[%s],lvol1[%d]",out_pack->sphone,out_pack->lvol1);		

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

	if(!BANK_LOGIN)
	{
		ret = Bank_SignIn(handle,rPack,pRetCode,szMsg);
		if(ret)
		{
			writelog(LOG_ERR,"签到失败ret[%d]",ret);
			return ret;
		}
	}

	char tmp[20]="";
	unsigned char msg[256]="";
	MEGBODY msgbody;
	memset(&msgbody,' ',sizeof msgbody);

	memcpy(msgbody.TradeCode,QUERY_BALA,2);									// 银行卡余额查询

	memset(tmp,0,sizeof tmp);
	ret = sprintf(tmp,"%d",rPack->lvol2);											// 客户号
	memcpy(msgbody.CustAccountNo,tmp,ret);
	strncpy(msgbody.BankCardNo, rPack->scust_limit2,strlen(rPack->scust_limit2));		// 银行卡号
	strncpy(msgbody.IdentityCode, rPack->scust_auth2,strlen(rPack->scust_auth2));		// 身份证号
	strncpy(msgbody.Name,rPack->scust_limit,strlen(rPack->scust_limit));				// 姓名

	// 生成发送报文
	GenSendMsg(msgbody, msg,true);
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SALL_NAME,F_DAMT0,F_DAMT1,0);
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}

	ret = tcpsocket.Send((char*)msg,MSG_LEN);
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
	ret = tcpsocket.Recv((char*)msg, MSG_LEN, timeout);					// 收报文内容
	if (ret != MSG_LEN)
	{
		out_pack->lvol1 = -1;								//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据包体错误");
		goto r_ret;  
	}

	GetRecvMsg(msgbody, msg,true);	
	writelog(LOG_INFO,"querybala recv[%s]",(char*)&msgbody);
	
	if(memcmp(msgbody.TradeCode,QUERY_BALA,2) !=0)							// 前2位应该是 05
	{
		out_pack->lvol1 = -1;								//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"查询余额接收银行数据交易码错误");
		goto r_ret;  
	}

	if(memcmp(msgbody.RetCode,"00",2)!=0)						// 银行返回失败
	{
		des2src(szMsg,GetErrMsg(msgbody.RetCode));
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sall_name,msgbody.Name,30);			// 客户名称
		trim(out_pack->sall_name);
		memset(tmp,0,sizeof tmp);
		memcpy(tmp,msgbody.Balance,9);
		out_pack->damt0 = D4U5(atof(tmp)/100, 2);
		out_pack->damt1= out_pack->damt0;	
	}
	writelog(LOG_INFO,"querybala:cutname[%s],actbala[%f],actavlbala[%f]",out_pack->sall_name,out_pack->damt0,out_pack->damt1);

r_ret:
	tcpsocket.Close();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_SignIn(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char host[16]="";		//对方机器的ip
	char tmp[4]="";
	short port = 0;			
	int timeout = 0;
	unsigned char msg[256]="";
	MEGBODY msgbody;
	memset(&msgbody,' ',sizeof msgbody);

	memcpy(msgbody.TradeCode,BANK_SIGN_IN,2);

	// 生成发送报文
	GenSendMsg(msgbody, msg,false);
	
	CTcpSocket tcpsocket ;

	des2src(host,rPack->scust_auth);						// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1*1000;							// 等待银行超时时间(毫秒)

	writelog(LOG_INFO,"bank info:  ip_addr[%s],port[%d],timeout[%d] ",host,port,timeout);

	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		strcpy(szMsg,"连接银行错误");
		return E_TRANS_CONNECT;
	}
	
	ret = tcpsocket.Send((char*)msg,MSG_LEN);
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
	ret = tcpsocket.Recv((char*)msg, MSG_LEN, timeout);					// 收报文内容
	if (ret != MSG_LEN)
	{
		writelog(LOG_ERR,"签到接收银行数据包体错误");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}

	GetRecvMsg(msgbody, msg,false);	
	writelog(LOG_INFO,"signIn recv[%s]",(char*)&msgbody);
	
	if(memcmp(msgbody.TradeCode,BANK_SIGN_IN,2) !=0)							// 前2位应该是 31
	{
		writelog(LOG_ERR,"签到接收银行数据交易码错误");
		tcpsocket.Close();
		return E_TRANS_BANK_RECVERR;  
	}
	memset(tmp,0,sizeof tmp);
	memcpy(tmp,msgbody.RetCode,2);
	ret = atoi(tmp);
	if(ret==0)					// 签到成功
	{
		shm[1]=1;
		shm[3]=0;
		memcpy(shm+10,msgbody.BankPWD,8);

		char buffer[20]="";
		int k=0;
		for(int i=0;i<8;i++)
		{
			k=msgbody.BankPWD[i];
			sprintf(&buffer[2*i],"%02X",k);
		}
		buffer[16]=0;
		writelog(LOG_INFO,"Bank dynamic key=[%s]",buffer);
	}
	
	return ret;
}


