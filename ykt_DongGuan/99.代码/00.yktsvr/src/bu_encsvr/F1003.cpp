/* --------------------------------------------
 * 创建日期: 2011-4-5
 * 程序作者: tc
 * 版本信息: 3.0.0.0
 * 程序功能: 充值计算MAC请求2
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "bupub.h"
#include <string>
#include <sstream>
#include <syslog.h>
#include "ksbu.h"
#include "svrlink.h"
#include "encsvrfunc.h"
#include "pubfunc.h"
//#include "bufunc.h"

extern CSvrLink *g_pSvrLink;
extern ST_CPACK *g_RequestPack;
using namespace std;


static int SetHeadCol(ST_CPACK *cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, cpack);
	while ((arg = va_arg(ap, int)) >= 0)
	{
		SetParmBit(&(cpack->head), arg);
	}
	va_end(ap);
    return(g_pSvrLink->SetCol(0, cpack->head.ParmBits));
}

static int doSend2Server(ST_PACK *rPack,ST_PACK *out_pack,char *szMsg)
{
	ST_CPACK request_pack,answer_pack;
	ResetNormalCPack(&request_pack,0,1);

	/*
	SetHeadCol(&request_pack,0);
	SetHeadCol(&request_pack,F_SCUST_AUTH,F_SHOLDER_AC_NO,F_LSERIAL0,F_SDATE0,F_STIME0,
		F_LVOL0,F_LVOL1,F_LVOL2,F_SCUST_AUTH2,F_SHOLDER_AC_NO2,F_SEMP,F_SSTATUS0,
		F_SNAME,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_LVOL9,0);
	*/
	
	memcpy(request_pack.head.ParmBits,g_RequestPack->head.ParmBits,sizeof(request_pack.head.ParmBits));

	
	SetParmBit(&(request_pack.head),F_SCUST_AUTH);
	SetParmBit(&(request_pack.head),F_SCUST_AUTH2);
	SetParmBit(&(request_pack.head),F_LVOL1);
	SetParmBit(&(request_pack.head),F_SPHONE);
	SetParmBit(&(request_pack.head),F_SDATE1);
	SetParmBit(&(request_pack.head),F_STIME1);
	SetParmBit(&(request_pack.head),F_SNAME);
	
	ST_PACK *pack = &(request_pack.pack);
	memcpy(pack,rPack,sizeof(ST_PACK));
	strcpy(pack->sname,out_pack->scust_auth2); // mac2
	strcpy(pack->sdate1,out_pack->sdate0); // host date
	strcpy(pack->stime1,out_pack->stime0); // host time
	strcpy(pack->sstatus0,"R");
	request_pack.head.RequestType = 846801;

	int ret;
	memset(&answer_pack,0,sizeof answer_pack);

	int mainsvr,mainfunc;
	BKConfiguration::instance()->get_int_para("encsvr.mainfunc",&mainfunc);
	BKConfiguration::instance()->get_int_para("encsvr.drtpno",&mainsvr);
	writelog(LOG_ERR,"Extcall svr [%d:%d]",mainfunc,mainsvr);
	ret = ExtCall(0,mainsvr,mainfunc,0,5,&request_pack,&answer_pack,NULL);
	if(ret<0)
	{
		writelog(LOG_ERR,"ExtCall server error,ret=[%d]",ret);
		if(ret == -2)
			strcpy(szMsg,"保存交易流水请求超时");
		else
			strcpy(szMsg,"保存交易流水请求错误!");
		return -1;
	}
	if(answer_pack.head.retCode != 0)
	{
		writelog(LOG_ERR,"record dpsdtl error,retcode=[%d]",answer_pack.head.retCode);
		sprintf(szMsg,"保存交易流水失败,retcode=[%d]",answer_pack.head.retCode);
		return -3;
	}
	strcpy(out_pack->sphone,answer_pack.pack.sphone);
	strcpy(out_pack->sdate3,answer_pack.pack.sdate3);
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
int F1003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	char remoteip[128]={0};
	int remoteport;
	int ret;
	
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	// 拷贝原包数据
	memcpy(aPack.head.ParmBits,g_RequestPack->head.ParmBits,sizeof(aPack.head.ParmBits));
	memcpy(out_pack,rPack,sizeof(ST_PACK));

	
	SetParmBit(&(aPack.head),F_SCUST_AUTH);
	SetParmBit(&(aPack.head),F_SCUST_AUTH2);
	SetParmBit(&(aPack.head),F_LVOL1);
	SetParmBit(&(aPack.head),F_SPHONE);
	SetParmBit(&(aPack.head),F_SDATE3);
	SetParmBit(&(aPack.head),F_SNAME);
	
	BKConfiguration::instance()->get_string_para("encsvr.remoteip",remoteip);
	BKConfiguration::instance()->get_int_para("encsvr.remoteport",&remoteport);
	YangjiangDebitComm comm(remoteip,remoteport);

	ret = comm.SendRequest(rPack,szMsg);
	if(ret)
	{
		writelog(LOG_ERR,"comm.SendRequest error");
		return -1;
	}
 	strncpy(out_pack->sdate0,comm.host_date(),8); // 主机日期
 	strncpy(out_pack->stime0,comm.host_time(),6); // 主机时间
 	strncpy(out_pack->scust_auth2,comm.mac2(),8); // MAC2
 	writelog(LOG_ERR,"calc mac success![%s]",comm.mac2());
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);

	// 发送请求给一卡通后台

	ret = doSend2Server(rPack,out_pack,szMsg);
	if(ret)
	{
		return -1;
	}
	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
}

