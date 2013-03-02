/* --------------------------------------------
 * 程序名称: F250004.sqc
 * 创建日期: 2008-01-08
 * 程序作者: 何林青
 * 版本信息: 1.0.0.0
 * 程序功能: 电控查询
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

#pragma pack(1)

typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char relate[1];
	char clientid[4];
	char signcheck[32];
}ext_elect_search_req_t;


typedef struct{
	char prix[1];
	char length[4];
	char type[4];
	char bitery[16];
	char room[20];
	char cutid[22];
	char relate[1];
	char depmoney[16];
	char depelemoney[16];
	char depelect[16];
	char depwatermoney[16];
	char depwater[16];
	char retnum[4];
	char clientid[4];
	char signcheck[32];
}ext_elect_search_res_t;

#pragma pack()

int F250004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	char host[16]="";		//对方机器的ip
	short port=0;			
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	CTcpSocket tcpsocket ;
	ext_elect_search_req_t SearchRequest;
	ext_elect_search_res_t  SearchResponse;

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SBANK_ACC,F_SSTATION0,F_SSTATION1,F_SADDR,F_SSECTYPES,0);

	des2src(host,rPack->scust_auth);
	port=rPack->lvol0;
	memset(&SearchRequest,0,sizeof(SearchRequest));
	memcpy(&SearchRequest, rPack->ssectypes,104);


	writelog(LOG_INFO,"Connect to electricity system ip_addr[%s],port[%d] ",host,port);	
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to electricity system error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		*pRetCode=E_TRANS_CONNECT;
		goto l_ret;
	}
	printf("send:[%s]\n",(char*)&SearchRequest);
	ret = tcpsocket.Send((char*)&SearchRequest,sizeof(SearchRequest));
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to electricity system error,error code is [%d] ",ret);
		*pRetCode=E_TRANS_REQUEST;
		goto l_ret;
	}
	else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to electricity system error，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
		*pRetCode=E_TRANS_REQUEST;
	      	goto l_ret;
	}
	memset(&SearchResponse,0,sizeof(SearchResponse));

	ret = tcpsocket.Recv((char*)&SearchResponse, sizeof(SearchResponse), 15000);		
	tcpsocket.Close();
	if (ret!=188)
	{
		writelog(LOG_ERR,"Receive from electricity system error,error code is [%d] ",ret);
		*pRetCode=E_TRANS_TIME_OUT;
		goto l_ret;  // 接收时候出错，或超时
	}
	printf("trans recv:[%s]\n",(char*)&SearchResponse);
	if(strncmp(SearchResponse.retnum,"0001",4)==0){
		//成功
		writelog(LOG_INFO,"trans success ret[%4s] ",SearchResponse.retnum);
		sprintf(out_pack->sstation0,SearchResponse.depelemoney,16);
		sprintf(out_pack->sstation1,SearchResponse.depelect,16);
		sprintf(out_pack.sbank_acc,SearchResponse.depmoney,16);
		
	}else if(strncmp(SearchResponse.retnum,"0400",4)==0){
		writelog(LOG_ERR,"trans falied ret[%4s] ",SearchResponse.retnum);
		*pRetCode=E_ELEC_DATA;
		goto l_ret;
	}else if(strncmp(SearchResponse.retnum,"0401",4)==0){
		writelog(LOG_ERR,"trans falied ret[%4s] ",SearchResponse.retnum);
		*pRetCode=E_ELEC_DB_CONN;
		goto l_ret;
	}else if(strncmp(SearchResponse.retnum,"0402",4)==0){
		//一卡通帐号与房间不对应
		writelog(LOG_INFO,"trans success but ret[%4s] ",SearchResponse.retnum);
		sprintf(out_pack->saddr,SearchResponse.room,20);
	}else if(strncmp(SearchResponse.retnum,"0403",4)==0){
		writelog(LOG_ERR,"trans falied ret[%4s] ",SearchResponse.retnum);
		*pRetCode=E_ELEC_ROOM;
		goto l_ret;
	}else if(strncmp(SearchResponse.retnum,"0404",4)==0){
		writelog(LOG_ERR,"trans falied ret[%4s] ",SearchResponse.retnum);
		*pRetCode=E_ELEC_WORKSTAT;
		goto l_ret;
	}else if(strncmp(SearchResponse.retnum,"0406",4)==0){
		writelog(LOG_ERR,"trans falied ret[%4s] ",SearchResponse.retnum);
		*pRetCode=E_ELEC_DATA_LOSS;
		goto l_ret;
	}else if(strncmp(SearchResponse.retnum,"0407",4)==0){
		writelog(LOG_ERR,"trans falied ret[%4s] ",SearchResponse.retnum);
		*pRetCode=E_ELEC_UNKNOW;
		goto l_ret;	
	}

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
l_ret:
	return -1;
}


