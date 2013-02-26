/* --------------------------------------------
 * 程序名称: F250002.sqc
 * 创建日期: 2007-08-16
 * 程序作者: 何林青
 * 版本信息: 1.0.0.0
 * 程序功能: 电控转账
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "tcp.h"
#include "logfile.h"

#pragma pack(1)

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char money[7];
	char datetime[10];
    char tracenum[18];
	char retnum[4];
	char clientid[4];
	char signcheck[32];
}ext_elect_req_t;

#pragma pack()

#define E_ELEC_DB_CONN	109176 //数据库连接错误
#define E_ELEC_CARD	109177 //一卡通账号与房间不对应
#define E_ELEC_ROOM	109178 // 不存在的房间
#define E_ELEC_WORKSTAT 109179 //不存在工作站
#define E_ELEC_DATA	109180 //数据校验错误
#define E_ELEC_DATA_LOSS 109181 //数据丢失
#define E_ELEC_UNKNOW	109182 //未知错误
#define E_TRANS_REQUEST 109183 //请求发送失败
#define E_TRANS_CONNECT 109184 //请求连接失败
#define E_TRANS_NOT_CONNECT 109185 //请求网络故障
#define E_TRANS_TIME_OUT 109186 //请求超时无应答


#ifdef __cplusplus
extern "C" {
#endif

extern CLogFile g_LogFile;

int F250002(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	char host[21]="";		//对方机器的ip
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	CTcpSocket tcpsocket ;
	ext_elect_req_t  ElectTrans;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SADDR,F_SSECTYPES,0);

	strcpy(host,rPack->scust_auth);
	port=rPack->lvol0;
	memset(&ElectTrans,0,sizeof(ElectTrans));
    memcpy(&ElectTrans, rPack->ssectypes,142);

	g_LogFile.WriteLogEx(1001,"Connect to electricity system ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		g_LogFile.WriteLogEx(1001,"Connect to electricity system error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		*pRetCode=E_TRANS_CONNECT;
		goto l_ret;
	}
	//printf("send:[%s]\n",(char*)&ElectTrans);
	ret = tcpsocket.Send((char*)&ElectTrans,sizeof(ElectTrans));
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		g_LogFile.WriteLogEx(1001,"Send to electricity system error,error code is [%d] ",ret);
		*pRetCode=E_TRANS_REQUEST;
		goto l_ret;
	}
	else if(0==ret){
		// 不应该出现这种情况
	    g_LogFile.WriteLogEx(1001,"Send to electricity system error，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		*pRetCode=E_TRANS_REQUEST;
	    goto l_ret;
	}
	memset(&ElectTrans,0,sizeof(ElectTrans));
	if(rPack->lvol1==1)
	{//正式请求
		ret = tcpsocket.Recv((char*)&ElectTrans, sizeof(ElectTrans), 15000);		
		tcpsocket.Close();
		if (ret!=142)
		{
			g_LogFile.WriteLogEx(1001,"Receive from electricity system error,error code is [%d] ",ret);
			*pRetCode=E_TRANS_TIME_OUT;
			goto l_ret;  // 接收时候出错，或超时
		}
		//printf("trans recv:[%s]\n",(char*)&ElectTrans);
		if(strncmp(ElectTrans.retnum,"0001",4)==0
			|| strncmp(ElectTrans.retnum,"0410",4) == 0){
			//成功, 如果流水号已经存在，那么也认为转账成功
			g_LogFile.WriteLogEx(1001,"转账成功 ret[%4s] ",ElectTrans.retnum);
		}else if(strncmp(ElectTrans.retnum,"0400",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0401",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DB_CONN;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0402",4)==0){
			//一卡通帐号与房间不对应
			g_LogFile.WriteLogEx(1001,"trans success but ret[%4s] ",ElectTrans.retnum);
			sprintf(out_pack->saddr,ElectTrans.room,20);
		}else if(strncmp(ElectTrans.retnum,"0403",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_ROOM;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0404",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_WORKSTAT;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0406",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA_LOSS;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0407",4)==0){
			g_LogFile.WriteLogEx(1001,"trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
		else
		{
			g_LogFile.WriteLogEx(1001,"unknown error ,trans falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode = E_ELEC_UNKNOW;
			goto l_ret;
		}
	}else{
		ret=tcpsocket.Recv((char*)&ElectTrans, sizeof(ElectTrans), 15000);
		tcpsocket.Close();
		if (ret!=142)
		{
			g_LogFile.WriteLogEx(1001,"Receive from electricity system error,error code is [%d] ",ret);
			*pRetCode=E_TRANS_TIME_OUT;
			goto l_ret;  // 接收时候出错，或超时
		}
		//printf("query recv:[%s]\n",(char*)&ElectTrans);	
		if(strncmp(ElectTrans.retnum,"0001",4)==0){
			//成功
			g_LogFile.WriteLogEx(1001,"查询成功 ret[%4s] ",ElectTrans.retnum);
		}else if(strncmp(ElectTrans.retnum,"0400",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0401",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DB_CONN;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0402",4)==0){
			//一卡通帐号与房间不对应
			g_LogFile.WriteLogEx(1001,"query success but ret[%4s] ",ElectTrans.retnum);
			sprintf(out_pack->saddr,ElectTrans.room,20);
		}else if(strncmp(ElectTrans.retnum,"0403",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_ROOM;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0404",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_WORKSTAT;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0406",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_DATA_LOSS;
			goto l_ret;
		}else if(strncmp(ElectTrans.retnum,"0407",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
		else
		{
			g_LogFile.WriteLogEx(1001,"unknown error, query falied ret[%4s] ",ElectTrans.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
l_ret:
	return -1;
}

#ifdef __cplusplus
}
#endif
