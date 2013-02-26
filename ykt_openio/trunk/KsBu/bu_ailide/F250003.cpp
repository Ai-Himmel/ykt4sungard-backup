/* --------------------------------------------
 * 程序名称: F250003.sqc
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

#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))
#pragma pack(1)

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	//char money[7];//xiao
	//char datetime[10];
   //char tracenum[18];
	//char retnum[4];
	char checkflag[1];
	char clientid[4];
	char signcheck[32];
}ext_elect_req_t;

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char checkflag[1];
	char money[16];//xiao
	char elc_money[16];
	char elc_bal_money[16];
	char wat_money[16];
	char wat_bla_money[16];
	char retnum[4];
	char clientid[4];
	char signcheck[32];
}ext_elect_rec_t;


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

int F250003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char cur_bala[17]="";
	char host[21]="";		//对方机器的ip
	short port=0;			
	int index = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	CTcpSocket tcpsocket ;
	ext_elect_req_t  ElectTrans;
	ext_elect_rec_t  ElectTransRec;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SADDR,F_SSECTYPES,F_DAMT0,0);				// 设置要返回字段的位图
 

	strcpy(host,rPack->scust_auth);
	port=rPack->lvol0;
	memset(&ElectTrans,0,sizeof(ElectTrans));
	memcpy(&ElectTrans, rPack->ssectypes,104);					// 应该是104 不是103

	//g_LogFile.WriteLogEx(1001,"Connect to electricity system ip_addr[%s],port[%d] ",host,port);	
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
	   	memset(&ElectTransRec,0,sizeof(ElectTransRec));
		ret=tcpsocket.Recv((char*)&ElectTransRec, sizeof(ElectTransRec), 15000);	
		tcpsocket.Close();
		//g_LogFile.WriteLogEx(1001,"Receive room[%s],money[%s] ",ElectTransRec.room,ElectTransRec.money);
		
		if (ret!=188)
		{
			g_LogFile.WriteLogEx(1001,"Receive from electricity system error,error code is [%d] ",ret);
			*pRetCode=E_TRANS_TIME_OUT;
			goto l_ret;  // 接收时候出错，或超时
		}
		//printf("query recv:[%s]\n",(char*)&ElectTrans);	
		
		if(strncmp(ElectTransRec.retnum,"0001",4)==0){
			//成功
			g_LogFile.WriteLogEx(1001,"查询成功 ");
		}else if(strncmp(ElectTransRec.retnum,"0400",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret1[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_DATA;
			goto l_ret;
		}else if(strncmp(ElectTransRec.retnum,"0401",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret2[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_DB_CONN;
			goto l_ret;
		}else if(strncmp(ElectTransRec.retnum,"0402",4)==0){
			//一卡通帐号与房间不对应
			g_LogFile.WriteLogEx(1001,"query success but ret3[%4s] ",ElectTransRec.retnum);
			sprintf(out_pack->saddr,ElectTransRec.room,20);
		}else if(strncmp(ElectTransRec.retnum,"0403",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret4[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_ROOM;
			goto l_ret;
		}else if(strncmp(ElectTransRec.retnum,"0404",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret5[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_WORKSTAT;
			goto l_ret;
		}else if(strncmp(ElectTransRec.retnum,"0406",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret6[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_DATA_LOSS;
			goto l_ret;
		}else if(strncmp(ElectTransRec.retnum,"0407",4)==0){
			g_LogFile.WriteLogEx(1001,"query falied ret7[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
		else
		{   
			g_LogFile.WriteLogEx(1001,"unknown error, query falied ret8[%4s] ",ElectTransRec.retnum);
			*pRetCode=E_ELEC_UNKNOW;
			goto l_ret;	
		}
		
		STRLENCPY(cur_bala,ElectTransRec.money,16);
		for(;index<16;index++)
		{
			if(cur_bala[index] != '0')
				break;
		}
		g_LogFile.WriteLogEx(1001,"cur_bala[%s] ",cur_bala+index);
		out_pack->damt0=atof(cur_bala+index)/100.0;
		STRLENCPY(out_pack->saddr,ElectTransRec.room,20);
		g_LogFile.WriteLogEx(1001,"room[%s],money[%f] ",out_pack->saddr,out_pack->damt0);
		PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
l_ret:
	return -1;
}

#ifdef __cplusplus
}
#endif
