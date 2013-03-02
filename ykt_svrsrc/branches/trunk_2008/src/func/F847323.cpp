/*
 * 模块名 第三方查询类交易
 * 文件名 F847323.cpp
 * 文件实现功能
 * 作者 
 * 版本
 * 日期 2008-09-10
 * 备注
 * $Id$
 */

#define _IN_SQC_
 #include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "fdsqc.h"
#include "ext_consumer.h"
#include "bupub.h"
#include "svrlink.h"
#include "callbu.h"
#include "account.h"
#include "fdsqc.h"
#include "tcp.h"
#include "rsa.h"

extern CSvrLink g_SvrLink;
typedef struct {
	int tx_code;
	int (* do_func)(ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg);
}query_func_def_t;
#define elec_search_len 103
#define elec_len 104
#define TIMEOUT 180

static void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02x",k);
	}
}


static int SetHeadCol(ST_CPACK *in_cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, in_cpack);
	while ((arg = va_arg(ap, int)) >= 0)
	{
		SetParmBit(&(in_cpack->head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}



static int packege_elec_request847323(ST_PACK *in_pack,int flag,char *send_data){
	int ret;
	ext_elect_req_t847323* elect_req_t;
	elect_req_t=(ext_elect_req_t847323*)send_data;
	//double money=0;			//充值金额
	char serialno[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char sysdatetime[20]="";
	unsigned char buf[106]="";
	unsigned char soutmd5[16]="";
	char outmd5[32]="";
	T_t_pif_card	tCard;
	memset(&tCard,0,sizeof(tCard));
	if(flag==1){//房间查询不加密
		memcpy(elect_req_t->prix,"0",1);
	}else{
		memcpy(elect_req_t->prix,"1",1);
	}
	
	memcpy(elect_req_t->length,"0103",4);	
	
	
	memcpy(elect_req_t->type,"0006",4);
	

	memset(elect_req_t->bitery,'0',sizeof(elect_req_t->bitery));
	sprintf(elect_req_t->room,"%-20s",in_pack->saddr);
	//ret=DB_t_pif_card_read_by_card_id(in_pack->lvol0, &tCard);
    //	if(ret)
	//{
	//	if(DB_NOTFOUND==ret)
	//		ret=E_CARDNO_NOT_EXIST;
	//	else
	//		ret=E_DB_CARD_R;
	//	return ret;
	//}
	sprintf(elect_req_t->cutid,"%-22d",in_pack->lvol0);	
//	money = in_pack->damt1;
//	int i_money=D2I(D4U5(money*100,0));
//	sprintf(elect_req_t->money,"%07d",i_money);
	memcpy(elect_req_t->checkflag,"0",1);
	
	memcpy(elect_req_t->clientid,"0001",4);
	memset(outmd5,'0',32);
	if(flag==1){
		sprintf(elect_req_t->signcheck,"%s",outmd5);
	}else if(flag==2){
		memcpy(buf,elect_req_t->type,105);	
		writelog(LOG_ERR,"buf data=[%s]",buf);
		CalcMD5(buf,105,soutmd5);
		dec2hex(soutmd5,16,outmd5);
		writelog(LOG_ERR,"outmd5 data=[%s]",outmd5);
		sprintf(elect_req_t->signcheck,"%s",outmd5);
	}
	
	
	
	return 0;
	
}


static int do_query_240203(ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;	
	char host[16]="";		//对方机器的ip
	char portchar[10]="";
	short port=0;				//对方机器的port
	char senddata[elec_len+1]="";	//加密后的传送数据
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	ret=GetParameter(2301, host);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		strcpy(szMsg,"not 2301");
		return ret;
	}
	ret=GetParameter(2302, portchar);
	if(ret){
		strcpy(szMsg,"not 2302");
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2303, c_drtbranch);
	if(ret){
		strcpy(szMsg,"not 2303");
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2304, c_bccbasefuncno);
	if(ret){
		strcpy(szMsg,"not 2304");
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ret = packege_elec_request847323(in_pack,1,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}
	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 250003;
	des2src(sPack.pack.ssectypes,senddata);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;	
		ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250003 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250003 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	
	memcpy(out_pack->saddr,aPack.pack.saddr,20);
	writelog(LOG_ERR,"saddr=[%s]",out_pack->saddr);
	 out_pack->damt0=aPack.pack.damt0;
	return 0;

}


static query_func_def_t g_query_func[] = {
	{240203,do_query_240203},
	{-1,NULL}
};

int F847323(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret,i;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
   	SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT1,F_DAMT2,F_SBANKNAME,F_SADDR,F_VSMESS,0);
	i = 0;
	while(g_query_func[i].tx_code != -1)
	{
		if(g_query_func[i].tx_code == in_pack->lcert_code)
		{
			// 
			ret = g_query_func[i].do_func(in_pack,out_pack,pRetCode,szMsg);
			if(ret)
			{
				writelog(LOG_ERR,"处理请求[%d]失败errcode[%d]",in_pack->lcert_code,*pRetCode);
				return ret;
			}
			PutRow(handle,out_pack,pRetCode,szMsg);
			return 0;
		}
		i++;
	}
	*pRetCode = E_INPUT_DATA_INVAILD;
	return -1;
}

