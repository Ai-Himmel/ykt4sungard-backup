/* ----------------------------------------------------------
 * 程序名称：bank_ccb_nm.cpp
 * 创建日期：2009-08-10
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：内蒙财经建行转账接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ccb_nm.h"
#include "tcp.h"

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

//按照通用接口规范进行封装各自银行的接口
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;

	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
//	TRANS_REQ trans_req;
//	TRANS_ANS trans_ans;
//	memset(&trans_req,0x20,sizeof trans_req);			// 先填充上空格
//	memset(&trans_ans,0x20,sizeof trans_ans);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);
	char buf[256] = " ";
	char tmp[8] = "";
	
	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1;								// 等待银行超时时间

	memset(buf,0x20,sizeof buf);			// 填充空格
	sprintf(buf,"%04d",REQ_PACK_LEN);		// 包体长度
	strcpy(buf+4,TRANS_CODE);				// 交易码
	STRLENCPY(buf+8, rPack->sdate0,8);				// 交易日期
	STRLENCPY(buf+16, rPack->sholder_ac_no,14);		// 一卡通交易参考号
	STRLENCPY(buf+30, rPack->sphone,32);				// 学工号
	STRLENCPY(buf+62, rPack->scust_limit,32);			// 姓名
	STRLENCPY(buf+94,rPack->scust_auth2,18);			// 身份证号
	STRLENCPY(buf+112,rPack->scust_limit2,32);		// 银行卡号
	sprintf(buf+144,"%-17.2f",rPack->damt0);			// 交易金额
	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}

	buf[REQ_PACK_LEN+4]=0;
	writelog(LOG_INFO,"trans send[%s]",buf);
	
	ret = tcpsocket.Send(buf,REQ_PACK_LEN+4);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	ret = tcpsocket.Recv(buf, ANS_PACK_LEN+4, timeout);		
	tcpsocket.Close();
	
	buf[ANS_PACK_LEN+4]=0;
	writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",buf,ret);

	if (ret!=ANS_PACK_LEN+4)
	{
		out_pack->lvol1 = -1;							//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"接收银行数据错误");
		goto r_ret;  
	}

	memcpy(tmp,buf,4);
	if(atoi(tmp) != ANS_PACK_LEN)
	{
		out_pack->lvol1 = -1;							//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"接收银行数据错误");
		goto r_ret;  // 接收时候出错，或超时
	}
	memcpy(tmp,buf+20,6);								
	if(strncmp(tmp,"000000",6)!=0)    // 银行端处理错误
	{
		memcpy(szMsg,buf+26,34);
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->sdate1,buf+12,8);						// 银行流水号
		memcpy(out_pack->scert_no,buf+26,34);					// 银行返回信息
	}
	writelog(LOG_INFO,"bankretinfo[%s],lvol1[%d]",out_pack->scert_no,out_pack->lvol1);
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;

	char host[16]="";		//对方机器的ip
	short port = 0;			
	int timeout = 0;
	
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	CTcpSocket tcpsocket ;
//	REVERSE_REQ reverse_req;
//	REVERSE_ANS reverse_ans;
//	memset(&reverse_req,0x20,sizeof reverse_req);			// 先填充上空格
//	memset(&reverse_ans,0x20,sizeof reverse_ans);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SCERT_NO,0);

	des2src(host,rPack->scust_auth);					// 银行ip
	port=rPack->lvol0;									// 银行端口
	timeout = rPack->lvol1;								// 等待银行超时时间
	char buf[256] = " ";
	char tmp[8] = "";

	memset(buf,0x20,sizeof buf);							// 填充空格
	sprintf(buf,"%04d",REV_REQ_PACK_LEN);					// 包体长度
	strcpy(buf+4,REV_TRANS_CODE);							// 交易码
	STRLENCPY(buf+8,rPack->sdate0,8);						// 交易日期
	STRLENCPY(buf+16,rPack->sholder_ac_no,14);			// 一卡通交易参考号
	STRLENCPY(buf+30,rPack->sphone,32);					// 学工号
	STRLENCPY(buf+62,rPack->scust_limit2,32);				// 银行卡号
	sprintf(buf+94,"%-17.2f",rPack->damt0);					// 交易金额
	
	writelog(LOG_INFO,"Connect to bank ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_TRANS_CONNECT;
	}
	buf[REV_REQ_PACK_LEN +4]=0;
	writelog(LOG_INFO,"reverse send[%s]",buf);
	
	ret = tcpsocket.Send(buf,REV_REQ_PACK_LEN +4);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,error code is [%d] ",ret);
		return E_TRANS_REQUEST;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		return E_TRANS_REQUEST;
	}

	ret = tcpsocket.Recv(buf, REV_ANS_PACK_LEN+4, timeout);		
	tcpsocket.Close();
	
	buf[REV_ANS_PACK_LEN+4] = 0;
	writelog(LOG_INFO,"reverse recv[%s]",buf);
	
	if (ret!=REV_ANS_PACK_LEN+4)
	{
		out_pack->lvol1 = -1;							//超时 或 接收数据错误 ，后台应向银行发冲正
		strcpy(szMsg,"接收银行数据错误");
		goto r_ret;  
	}

	memcpy(tmp,buf,4);
	if(atoi(tmp) != REV_ANS_PACK_LEN)
	{
		out_pack->lvol1 = -1;							//接收数据错误，后台应向银行发冲正
		strcpy(szMsg,"接收银行数据错误");
		goto r_ret;  // 接收时候出错，或超时
	}
	memcpy(tmp,buf+4,6);
	if(strncmp(tmp,"000000",6)!=0)
	{
		memcpy(szMsg,buf+10,34);
		return E_TRANS_BANK_RECVERR;
	}
	else
	{
		out_pack->lvol1 = 1;
		memcpy(out_pack->scert_no,buf+10,34);
	}
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

