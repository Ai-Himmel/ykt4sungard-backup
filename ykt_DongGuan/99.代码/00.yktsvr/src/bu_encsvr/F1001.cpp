/* --------------------------------------------
 * 创建日期: 2010-12-10
 * 程序作者: tc
 * 版本信息: 3.0.0.0
 * 程序功能: 充值计算MAC请求
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

extern CSvrLink *g_pSvrLink;
extern ST_CPACK *g_RequestPack;
using namespace std;



////////////////////////////////////////////////////////////////////////////////
int F1001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	char remoteip[128]={0};
	int remoteport;
	char senddata[512],temp[256];
	int ret,offset,recvlen;
	CTcpSocket sock;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	// 拷贝原包数据
	memcpy(aPack.head.ParmBits,g_RequestPack->head.ParmBits,sizeof(aPack.head.ParmBits));
	memcpy(out_pack,rPack,sizeof(ST_PACK));

	
	SetParmBit(&(aPack.head),F_SCUST_AUTH);
	SetParmBit(&(aPack.head),F_SCUST_AUTH2);
	SetParmBit(&(aPack.head),F_LVOL1);
	// TODO : 请求加密机

	/*
	
	offset = 4;
	offset += sprintf(senddata+offset,"100105"); // 请求码
	offset += snprintf(senddata+offset,9,"%s",rPack->sdate0); // 日期
 	offset += snprintf(senddata+offset,7,"%s",rPack->stime0); // 时间
 	offset += snprintf(senddata+offset,13,"%s",rPack->sholder_ac_no); // PSAM卡终端号
 	offset += snprintf(senddata+offset,37,"00000000%s%s%08d",rPack->sdate0,rPack->sholder_ac_no,rPack->lserial0); // 流水号
 	offset += snprintf(senddata+offset,20,"0000000000000001230");//卡号?
 	int applen = strlen(rPack->scust_auth);
	char appno[17]={0};
	if(applen > 16)
	{
		strncpy(appno,rPack->scust_auth+applen-16,16);
	}
	else
	{
		strcpy(appno,rPack->scust_auth);
	}
 	offset += snprintf(senddata+offset,21,"0000%s",appno);//应用序列号
 	offset += sprintf(senddata+offset,"%08d",rPack->lvol2); //交易前余额
 	offset += sprintf(senddata+offset,"%08d",rPack->lvol0); //交易金额
 	offset += snprintf(senddata+offset,9,"%s",rPack->scust_auth2); //随机数
 	offset += sprintf(senddata+offset,"%04X",rPack->lvol1); //交易次数
 	offset += sprintf(senddata+offset,"02");//交易类型
 	offset += snprintf(senddata+offset,9,"%s",rPack->sholder_ac_no2);//MAC1

	
	BKConfiguration::instance()->get_string_para("encsvr.remoteip",remoteip);
	BKConfiguration::instance()->get_int_para("encsvr.remoteport",&remoteport);
	//strcpy(remoteip,"192.168.0.103");
	//remoteport=18220;
	writelog(LOG_ERR,"try connect server[%s][%d]",remoteip,remoteport);
 	if(!sock.ConnectTcp(remoteip,remoteport))
 	{
 		// TODO: 必须
 		strcpy(szMsg,"连接加密平台失败");
 		return -1;
 	}

	sprintf(temp,"%04d",offset-4);
	memcpy(senddata,temp,4);

	writelog(LOG_ERR,"send data calc mac len[%d]",offset);
	if(sock.Send(senddata,offset)!=offset)
	{
		strcpy(szMsg,"连接加密平台失败");
 		return -1;
	}

 	ret=sock.Recv(temp,4,3000);
 	if(ret<0)
 	{
 		strcpy(szMsg,"接收加密平台数据超时");
 		return -1;
 	}
 	temp[4]=0;
 	recvlen = atoi(temp);
 	writelog(LOG_ERR,"recv len[%d]",recvlen);
 	ret = sock.Recv(senddata,recvlen,3000);
 	if(ret<0)
 	{
 		strcpy(szMsg,"接收加密平台数据超时");
 		return -1; 
 	}
 	senddata[recvlen]=0;
 	//writelog(LOG_ERR,"recv[%s]",senddata);
 	if(strncmp(senddata,"100105",6)!=0)
 	{
 		strcpy(szMsg,"接收加密平台数据错误");
 		return -1;
 	}
 	if(strncmp(senddata+6,"000000000",9)!=0)
 	{
 		memcpy(temp,senddata+6,9+60);
 		temp[69]=0;
 		sprintf(szMsg,"接收加密平台数据错误[%s]",temp);
 		return -1;
 	}
 	
 	offset=6+9+60;
 	offset+=36;
 	strncpy(out_pack->sdate0,senddata+offset,8); // 主机日期
 	offset+=8;
 	strncpy(out_pack->stime0,senddata+offset,6); // 主机时间
 	offset+=6;
 	strncpy(out_pack->scust_auth2,senddata+offset,8); // MAC2
 	writelog(LOG_ERR,"calc mac success!");
 	*/
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
 	writelog(LOG_ERR,"calc mac success!");
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
	
}
