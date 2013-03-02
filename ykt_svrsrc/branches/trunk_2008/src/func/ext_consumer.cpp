/* --------------------------------------------
 * 程序名称: Ext_consumer.cpp
 * 创建日期: 2007-08-16
 * 程序作者: hlq
 * 版本信息: 1.0.0.0
 * 程序功能: 第三方转账通用模块
 * --------------------------------------------*/


#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "account.h"
#include "fdsqc.h"
#include "tcp.h"
#include "rsa.h"
#include "ext_consumer.h"
#include "svrlink.h"
#include "bupub.h"
#include "callbu.h"

 
#define NETCHARGE_CODE 1001 //记录网络收费转账失败标记
 
 
#define PRE_CHEDK_ENTER_ACCOUNT_MOBILE_TRANS		240200		//手机充值
#define PRE_ENTER_ACCOUNT_WATER_TRANS	240201	//水控转账
#define TERMINAL_TRADE						240202
#define PRE_LOGIN_ELECT_TRANS				240203	 //爱力德电控转账
#define CHECK_ROOMNAME_ELECT_TRANS		240204      //常州电控转账
#define TURN_OVER	240405		//海事大学考试报名
#define HGC_RJ_NETWORK	240208	// 哈工程锐捷网络转账
#define NET_FEE_TRANS	240209	//网费转帐


#define TIMEOUT_REDO_FORBIT 	0			//和第三方交互超时，不允许重发
#define TIMEOUT_REDO_ALLOW 	1

extern CSvrLink g_SvrLink;
int SetHeadCol(ST_CPACK *in_cpack, ...)
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

static int packege_search_data(ST_PACK *in_pack,char *send_data){
	int ret;
	ext_elect_search_req_t* elect_search_req_t;
	elect_search_req_t=(ext_elect_search_req_t*)send_data;
	
	unsigned char buf[68]="";
	unsigned char soutmd5[16]="";
	char outmd5[32]="";
	
	T_t_pif_card	tCard;	
	memset(&tCard,0,sizeof(tCard));
	

	memcpy(elect_search_req_t->prix,"1",1);	
	memcpy(elect_search_req_t->length,"0103",4);	
	memcpy(elect_search_req_t->type,"0006",4);
	memset(elect_search_req_t->bitery,'0',sizeof(elect_search_req_t->bitery));	
	sprintf(elect_search_req_t->room,"%-20s",in_pack->saddr);
	ret=DB_t_pif_card_read_by_card_id(in_pack->lvol0, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}
	sprintf(elect_search_req_t->cutid,"%-22d",tCard.cosumer_id);//客户号
	memcpy(elect_search_req_t->relate,"1",1);//对应关系
	memcpy(elect_search_req_t->clientid,"0001",4);
	memset(outmd5,'0',32);

	memcpy(buf,elect_search_req_t->type,67);	
	writelog(LOG_ERR,"buf data=[%s]",buf);
	CalcMD5(buf,67,soutmd5);
	dec2hex(soutmd5,16,outmd5);
	writelog(LOG_ERR,"outmd5 data=[%s]",outmd5);
	sprintf(elect_search_req_t->signcheck,"%s",outmd5);	
	
	return 0;
}
	
static int packege_send_data(ST_PACK *in_pack,int flag,char *send_data){
	int ret =0;
	//char cellphone[31]="";	//充值手机号
	double money=0;			//充值金额
	char sysdate[11]="";
	char systime[9]="";
	char sysdatetime[20]="";
	char serialno[20]="";
	char sMoney[20]="";
	T_t_pif_card	tCard;
//	ext_phone_trans_t phone_trans_struct;
	ext_phone_trans_t* phone_trans_struct;
	phone_trans_struct=(ext_phone_trans_t*)send_data;
	
	memset(&tCard,0,sizeof(tCard));
	memset(phone_trans_struct,0,sizeof(ext_phone_trans_t));
	
	phone_trans_struct->prix[0]=0x31;
	memcpy(phone_trans_struct->length,"0067",4);
	if(1==flag)
	{
		memcpy(phone_trans_struct->type,"0100",4);
	}
	else if(2==flag)
	{
		memcpy(phone_trans_struct->type,"0200",4);		
	}
	//memcpy(phone_trans_struct->bitery,"0000000000000000",16);
	memset(phone_trans_struct->bitery,'0',sizeof(phone_trans_struct->bitery));
	ret=DB_t_pif_card_read_by_card_id(in_pack->lvol0, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}
	sprintf(phone_trans_struct->cutid,"%-22d",tCard.cosumer_id);	
	money = in_pack->damt1;
	int i_money=D2I(D4U5(money*100,0));
	sprintf(sMoney,"%07d",i_money);
	memcpy(phone_trans_struct->money,sMoney,sizeof(phone_trans_struct->money));
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}
	strcpy(sysdatetime,sysdate+4);
	strcat(sysdatetime,systime);
	memcpy(phone_trans_struct->datetime,sysdatetime,10);
	memcpy(phone_trans_struct->tracenum,sysdate,8);
	sprintf(serialno,"%06d",in_pack->lvol6%1000000);
	memcpy(phone_trans_struct->tracenum+8,serialno,6);
	memcpy(phone_trans_struct->phone,in_pack->sphone,strlen(in_pack->sphone));
	memcpy(phone_trans_struct->retnum,"00",2);
	memset(phone_trans_struct->plugdata,0x20,sizeof(phone_trans_struct->plugdata));

	/*
	memcpy(send_data,phone_trans_struct->prix,1);
	memcpy(send_data+1,phone_trans_struct->length,4);
	memcpy(send_data+5,phone_trans_struct->type,4);
	memcpy(send_data+9,phone_trans_struct->bitery,16);
	memcpy(send_data+25,phone_trans_struct->cutid,22);
	memcpy(send_data+47,phone_trans_struct->money,7);
	memcpy(send_data+54,phone_trans_struct->datetime,10);
	memcpy(send_data+64,phone_trans_struct->tracenum,14);
	memcpy(send_data+78,phone_trans_struct->phone,11);
	memcpy(send_data+89,phone_trans_struct->retnum,2);
	memcpy(send_data+91,phone_trans_struct->plugdata,36);
	*/
	writelog(LOG_ERR,"package send data=[%s]",send_data);
	return 0;
	
}


static int packege_elec_request(ST_PACK *in_pack,int flag,char *send_data){
	int ret;
	ext_elect_req_t* elect_req_t;
	elect_req_t=(ext_elect_req_t*)send_data;
	double money=0;			//充值金额
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
	
	memcpy(elect_req_t->length,"0141",4);	
	
	if(flag==1){
		memcpy(elect_req_t->type,"0001",4);
		
	}else if(flag==2){
		memcpy(elect_req_t->type,"0002",4);
	}

	memset(elect_req_t->bitery,'0',sizeof(elect_req_t->bitery));
	sprintf(elect_req_t->room,"%-20s",in_pack->saddr);
	ret=DB_t_pif_card_read_by_card_id(in_pack->lvol0, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}
	sprintf(elect_req_t->cutid,"%-22d",tCard.cosumer_id);	
	money = in_pack->damt1;
	int i_money=D2I(D4U5(money*100,0));
	sprintf(elect_req_t->money,"%07d",i_money);
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
	}
	strcpy(sysdatetime,sysdate+4);
	strcat(sysdatetime,systime);
	memcpy(elect_req_t->datetime,sysdatetime,10);
	memcpy(elect_req_t->tracenum,sysdate,8);
	sprintf(serialno,"%010d",in_pack->lvol6);
	memcpy(elect_req_t->tracenum+8,serialno,10);
	memcpy(elect_req_t->retnum,"0000",4);
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


/*

	爱立德电控房间余额查询
	2008-01-09
*/
#define elec_search_len 103
#define elec_len 141
#define TIMEOUT 180


int elec_room_deposit_search(ST_PACK *in_pack,ST_PACK *out_pack){
	int ret = 0;	
	char host[16]="";		//对方机器的ip
	char portchar[10]="";
	short port=0;				//对方机器的port
	char senddata[elec_search_len+1]="";	//加密后的传送数据
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
		return ret;
	}
	ret=GetParameter(2302, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2303, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2304, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ret = packege_search_data(in_pack,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}
	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 250004;
	des2src(sPack.pack.ssectypes,senddata);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250004 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250004 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	
	memcpy(out_pack->sstation0,aPack.pack.sstation0,17);
	memcpy(out_pack->sstation1,aPack.pack.sstation1,17);
	memcpy(out_pack->sbank_acc,aPack.pack.sbank_acc,17);
	writelog(LOG_ERR,"electrity depelemoney =[%17s]",out_pack->sstation0);
	writelog(LOG_ERR,"electrity depelect =[%17s]",out_pack->sstation1);
	writelog(LOG_ERR,"electrity depmoney =[%17s]",out_pack->sbank_acc);

	return 0;

}


static int elect_room_check(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *trans_ctl)
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
	trans_ctl->check_user_pwd = 0;
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	ret=GetParameter(2301, host);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2302, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2303, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2304, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ret = packege_elec_request(in_pack,1,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}
	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 250002;
	des2src(sPack.pack.ssectypes,senddata);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250002 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250002 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	
	memcpy(out_pack->saddr,aPack.pack.saddr,20);
	writelog(LOG_ERR,"saddr=[%s]",out_pack->saddr);

	return 0;
/*
	memset(&ElectTrans,0,sizeof(ElectTrans));
	memcpy(&ElectTrans, aPack.pack.ssectypes,141);

	if(strncmp(ElectTrans.retnum,"0001",4)==0){
		//房间存在
		writelog(LOG_INFO,"query success ret[%s] ",ElectTrans.retnum);
		return 0;
	}else if(strncmp(ElectTrans.retnum,"0400",4)){
		writelog(LOG_ERR,"query falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_DATA;		
	}else if(strncmp(ElectTrans.retnum,"0401",4)){
	writelog(LOG_ERR,"query falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_DB_CONN;
	}else if(strncmp(ElectTrans.retnum,"0402",4)){
		//一卡通帐号与房间不对应
		writelog(LOG_INFO,"query success but ret[%s] ",ElectTrans.retnum);
		sprintf(out_pack->saddr,ElectTrans.room,sizeof(ElectTrans.room));
		return 0;
	}else if(strncmp(ElectTrans.retnum,"0403",4)){
	writelog(LOG_ERR,"query falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_ROOM;
	}else if(strncmp(ElectTrans.retnum,"0404",4)){
	writelog(LOG_ERR,"query falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_WORKSTAT;		
	}else if(strncmp(ElectTrans.retnum,"0406",4)){
	writelog(LOG_ERR,"query falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_DATA_LOSS;		
	}else if(strncmp(ElectTrans.retnum,"0407",4)){
	writelog(LOG_ERR,"query falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_UNKNOW;		
	}
	*/
	
}


static int elect_room_check_get_name(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *trans_ctl)
{
	int ret = 0;	

	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	trans_ctl->check_user_pwd = 0;
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包


	ret=GetParameter(2501, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2502, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 847356;
	sPack.pack.lvol0=in_pack->lvol10;//房间号
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 847356 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 847356 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	
	memcpy(out_pack->sbankname,aPack.pack.sbankname,81);//房间名称
	out_pack->damt2=aPack.pack.damt0;//电价
	writelog(LOG_ERR,"sbankname=[%s]",out_pack->sbankname);

	return 0;

	
}



static int elect_request(ST_PACK *in_pack,char ext_msg[256]){
	int ret = 0;	
	char host[16]="";		//对方机器的ip
	char portchar[10]="";
	short port=0;				//对方机器的port
	char senddata[elec_len+1]="";	//加密后的传送数据
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	ret=GetParameter(2301, host);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2302, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2303, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2304, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);
	
	ret = packege_elec_request(in_pack,2,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}


	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_LVOL1,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 250002;
	des2src(sPack.pack.ssectypes,senddata);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	sPack.pack.lvol1=1;
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250002 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250002 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}

	return 0;
	/*
	memset(&ElectTrans,0,sizeof(ElectTrans));
	memcpy(&ElectTrans, aPack.pack.ssectypes,141);

	if(strncmp(ElectTrans.retnum,"0001",4)==0){
		//成功
		writelog(LOG_INFO,"trans success ret[%s] ",ElectTrans.retnum);
		return 0;
	}else if(strncmp(ElectTrans.retnum,"0400",4)){
		writelog(LOG_ERR,"trans falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_DATA;		
	}else if(strncmp(ElectTrans.retnum,"0401",4)){
	writelog(LOG_ERR,"trans falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_DB_CONN;
	}else if(strncmp(ElectTrans.retnum,"0403",4)){
	writelog(LOG_ERR,"trans falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_ROOM;
	}else if(strncmp(ElectTrans.retnum,"0404",4)){
	writelog(LOG_ERR,"trans falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_WORKSTAT;		
	}else if(strncmp(ElectTrans.retnum,"0406",4)){
	writelog(LOG_ERR,"trans falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_DATA_LOSS;		
	}else if(strncmp(ElectTrans.retnum,"0407",4)){
	writelog(LOG_ERR,"trans falied ret[%s] ",ElectTrans.retnum);
		return E_ELEC_UNKNOW;		
	}
	
	return -1;

	*/
}

static int elect_request_changzhou(ST_PACK *in_pack,char ext_msg[256]){
	int ret = 0;	

	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包
	int card_id;

	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;
	T_t_pif_card	tCard;

	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));

	card_id=in_pack->lvol0;

	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	

	ret=GetParameter(2501, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2502, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_LVOL1,F_SORDER0,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 847357;
	sPack.pack.lvol0=in_pack->lvol10;//房间号
	sPack.pack.lvol1=D2I(in_pack->damt1*100);//转账金额(分)
	memcpy(sPack.pack.sorder0,tCustomer.cut_name,11);
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 847357 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 847357 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}

	return 0;
}


#define package_len 327


//从第三方确认手机号码的正确性
static int 	check_cellphone(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *trans_ctl)
{
	int ret = 0;	
	char host[16]="";		//对方机器的ip
	char portchar[10]="";
	short port=0;				//对方机器的port
	char rcvdata[package_len+1]="";		//接收对方的传送数据
	char senddata[package_len+1]="";	//加密后的传送数据
	char tempdate[package_len+1-200]="";
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	
	memset(tempdate,0,sizeof tempdate);
	trans_ctl->check_user_pwd = 0;
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	
	ret=GetParameter(2104, host);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2105, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2106, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2107, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);

	ret = packege_send_data(in_pack,1,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}

	memcpy(tempdate,senddata,package_len-200);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 250001;
	des2src(sPack.pack.ssectypes,tempdate);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	
	des2src(rcvdata,aPack.pack.ssectypes);
/*
	
	writelog(LOG_ERR,"bengin to connect the telecom's server for cellphone check\n,host=[%s],port=[%d],senddata=[%s]",host,port,senddata);
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to boss system error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_MOBILE_TRANS_CONNECT;
	}
	ret = tcpsocket.Send(senddata,326);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to boss system error,error code is [%d] ",ret);
		return E_MOBILE_TRANS_REQUEST;
	}else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to boss system error，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
	      	return	E_MOBILE_TRANS_REQUEST;
	}
	
	ret = tcpsocket.Recv(rcvdata, 326, 180000);
	if (ret!=326)
	{
		writelog(LOG_ERR,"Receive from boss system error,error code is [%d] ",ret);
		return	E_MOBILE_TRANS_TIME_OUT;  // 接收时候出错，或超时
	}
	tcpsocket.Close();
*/
	if(('0'==rcvdata[89])&&('0'==rcvdata[90]))
	{
		//号码正确
		return 0;
	}
	else if(('0'==rcvdata[89])&&('1'==rcvdata[90]))
	{
		//mac校验出错
		return E_MOBILE_CHECK_MAC;

	}else if(('0'==rcvdata[89])&&('2'==rcvdata[90]))
	{
		//失败
		return E_MOBILE_CHECK_FAIL;
	}else
	{
		//未知异常
		return E_MOBILE_CHECK_UNKNOW;
	}
	
}

//获得第三方充值业务对应的商户id
static int get_third_part_account(ST_PACK *in_pack,int trade_code,InAcc *IA){
	int ret=0;
	int cnt=0;
	char szActno[17]="";				//帐户
	int shpid=0;						//商户ID
	T_t_cif_shop		shop;			//商户信息表
	T_t_aif_account	account;		//帐户表
	T_t_cif_customer	tCustomer;		//客户表
	T_t_pif_spefee 	tSpeFee;
	T_t_pif_card		tCard;
	T_t_tradecode_shop tradeshop;
	memset(&tCard,0,sizeof(tCard));
	memset(&shop,0,sizeof(shop));
	memset(&account,0,sizeof(account));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	//根据交易代码取得
	memset(&tradeshop,0,sizeof(tradeshop));
	
	ret =DB_t_tradecode_shop_open_select_by_c0_and_trade_code(trade_code);
	if(ret){
		writelog(LOG_ERR,"DB_t_tradecode_shop_open_select_by_c0_and_trade_code error,errcode=[%d]",ret);
		return 	ret;
	}
	while(1){
		memset(&tradeshop,0,sizeof(tradeshop));
		ret =DB_t_tradecode_shop_fetch_select_by_c0(&tradeshop);
		if(ret){
			DB_t_tradecode_shop_close_select_by_c0();
			if(cnt==0)
			{
				writelog(LOG_ERR,"DB_t_tradecode_shop_fetch_select_by_c0 error errorcode=[%d]",ret);
				return E_SHP_ID_NOT_EXIST;
			}
			break;
		}
		cnt++;
		shpid = tradeshop.shop_id;
	}
	
	
	//根据商户ID查询得到商户信息
	ret=DB_t_cif_shop_read_by_shop_id(shpid, &shop);
	if(ret)
	{
		writelog(LOG_ERR,"read tablet_cif_shop  shpid[%d]",shpid);
		if(DB_NOTFOUND==ret)
		{
			return E_SHP_ID_NOT_EXIST;
		}
		else
			return E_DB_CARD_R;
	}
	//根据客户号和商户主账号类型查询账号表，得到账号
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(shop.cut_id,ACCTYPE_SHOPMAIN,&account);
	if(ret)
	{
		writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,shop.cut_id);
		if(DB_NOTFOUND==ret)
			return  E_SHOP_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	strcpy(szActno,account.account_id);
	memset(&account,0,sizeof(account));
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(in_pack->lvol0,0,&account);
	if(ret)
	{
		writelog(LOG_ERR,"read t_aif_account err[%d]cardid[%d]",ret,in_pack->lvol0);
		if(DB_NOTFOUND==ret)
		{
			return E_ACTNO_NOT_EXIST;
		}
		else
			return E_DB_ACCOUNT_R;
	}

	des2src(IA->sArrInActno[0],account.account_id);					//借方账号
	des2src(IA->sArrInActno[1],szActno);							//贷方账号


	return 0;
	
}

//发送正式充值请求
static int trans_request(ST_PACK *in_pack,char ext_msg[256]){
	int ret = 0;
	char host[16]="";		//对方机器的ip
	char portchar[10]="";
	short port=0;				//对方机器的port
	char rcvdata[package_len+1]="";		//接收对方的传送数据
	char senddata[package_len+1]="";	//加密后的传送数据
	char tempdate[package_len+1-200]="";
	char c_drtbranch[10]="";
	char c_bccbasefuncno[10]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
//	char temp[512] = "";
//	int i,j;

	memset(tempdate,0,sizeof tempdate);
	CTcpSocket tcpsocket ;

	ST_PACK ArrayPack;			// 设置返回包
	ST_CPACK aPack;				// 设置应答包
	ST_CPACK sPack;			 	// 设置发送包

	ret=GetParameter(2104, host);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return E_DB_TRADESERIALERROR_R;
	}
	ret=GetParameter(2105, portchar);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return E_DB_TRADESERIALERROR_R;
	}
	ret=GetParameter(2106, c_drtbranch);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2107, c_bccbasefuncno);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	
	port = atoi(portchar);
	DRTP_BRANCH = atoi(c_drtbranch);
	BCC_BASEFUNCNO = atoi(c_bccbasefuncno);
	
	ret = packege_send_data(in_pack,2,senddata);
	if(ret){
		writelog(LOG_ERR,"packege send data error,error code is [%d]",ret);
		return ret;
	}

	memcpy(tempdate,senddata,package_len-200);

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	ResetNormalCPack(&sPack, 0, 1);
	SetHeadCol(&sPack, F_SSECTYPES,F_LVOL0,F_LVOL1,F_SCUST_AUTH,0);       // 设置发送windows BU的头部视图信息
	sPack.head.RequestType = 250001;
	des2src(sPack.pack.ssectypes,tempdate);
	des2src(sPack.pack.scust_auth,host);
	sPack.pack.lvol0=port;
	sPack.pack.lvol1=1;
	
	ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, TIMEOUT, &sPack, &aPack, &ArrayPack);
	if (ret < 0||aPack.head.retCode!=0)
	{
		if(ret<0)
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return ret;
		}
		else
		{
			writelog(LOG_ERR,"Call 250001 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			return aPack.head.retCode;
		}
	}
	
	des2src(rcvdata,aPack.pack.ssectypes);

	/*
	ret = tcpsocket.ConnectTcp(host, port);
	if(!ret)
	{
		writelog(LOG_ERR,"Connect to boss system error,error code is [%d],ip_addr[%s],port[%d] ",ret,host,port);
		return E_MOBILE_TRANS_CONNECT;
	}
	ret = tcpsocket.Send(senddata,326);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to boss system error,error code is [%d] ",ret);
		return E_MOBILE_TRANS_REQUEST;
	}else if(0==ret){
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to boss system error，CTcpSocket.Send should not return this error,error code is[%d]!\n",ret);
	      	return	E_MOBILE_TRANS_REQUEST;
	}
	tcpsocket.Recv(rcvdata, 326, 1000);

	tcpsocket.Close();
	*/
	return 0;
}


/**************************************************
	终端消费模块
*******************************************************/
static int pre_check_term_trade(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *trans_ctl)
{
	T_t_pif_device tDevice;
	char curr_date[9];
	char curr_time[7];
	int shop_id;
	int ret;
	if(in_pack->lvol4 <= 0)
		return E_INPUT_DATA_INVAILD;

	trans_ctl->check_user_pwd = 0;
	
	memset(&tDevice,0,sizeof tDevice);

	getsysdate(curr_date);
	getsystime(curr_time);
	if( strcmp(in_pack->sdate0,curr_date) != 0)
	{
		return E_INPUT_DATE;
	}
	ret = get_shpId_by_devId_date_time(&shop_id,tDevice.device_id,in_pack->sdate0
		,curr_time,0);
	if(ret)
	{
		return ret;
	}
	// 保存商户号
	in_pack->lvol12 = shop_id;
	ret = DB_t_pif_device_read_lock_by_cur_and_device_id(in_pack->lvol4,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DEVICE_N;
		else
			return E_DB_DEVICE_R;
	}
	ret = 0;
	if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		ret = E_DEVICE_NOT_EXIST;
	}
	else if(tDevice.lasttraserno!= in_pack->lvol5)
	{
		writelog(LOG_ERR,"中断流水号不符,devid[%d]input serial[%d]"
			,in_pack->lvol4,in_pack->lvol5);
		ret = E_SERIALNO_NOT_EXIST;
	}
	 DB_t_pif_device_free_lock_cur();
	 return ret;
}


static int pre_check_fee(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *trans_ctl)
{
	int ret;
	double check_fee;
	char stuemp_no[21]="";

	trans_ctl->check_user_pwd = 0;

	
	ret = get_stuemp_no_by_card_no(in_pack->lvol0,stuemp_no);
	if (ret)
	{
		return ret;
	}
	writelog(LOG_ERR,"stuemp_no got =[%s]!",stuemp_no);

	
	ret = updateBMStudentPayStatus(stuemp_no);
	if (ret)
	{
		return ret;
	}
	
	ret = getTurnOverFeebyStuempNO(stuemp_no,&check_fee);
	if (ret)
	{
		return ret;
	}

	if(amtcmp(check_fee,0)<=0){
		return E_TURN_OVER_N;
	}
	writelog(LOG_ERR,"check_fee got =[%f]!",check_fee);
	in_pack->damt1 = check_fee;


	ret = db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_DB_COMMIT;
	}

	return 0;
	
}

static int write_turn_over_fee(ST_PACK *in_pack,char ext_msg[256])
{
	
	int ret;
	char stuemp_no[21]="";


	
	ret = get_stuemp_no_by_card_no(in_pack->lvol0,stuemp_no);
	if (ret)
	{
		return ret;
	}

	writelog(LOG_ERR,"17 stuemp_no got =[%s]!",stuemp_no);

	ret = updateBminfoByStuempNo(stuemp_no);
	if (ret)
	{
		return ret;
	}

	return 0;
	
}


static int search_account_from_term_id(ST_PACK *in_pack,int trade_code,InAcc *IA)
{
	T_t_pif_device tDevice;
	T_t_aif_account tAccount;
	T_t_cif_shop tShop;
	int shop_id;
	char curr_time[7] = "";
	int ret;
	if(in_pack->lvol4 <= 0)
		return E_INPUT_DATA_INVAILD;

	memset(&tDevice,0,sizeof tDevice);
	
	ret = DB_t_pif_device_read_by_device_id(in_pack->lvol4,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DEVICE_N;
		else
			return E_DB_DEVICE_R;
	}
	getsystime(curr_time);
	ret = get_shpId_by_devId_date_time(&shop_id,tDevice.device_id,in_pack->sdate0
		,curr_time,0);
	if(ret)
	{
		return ret;
	}
	// 保存商户号
	memset(&tShop,0,sizeof tShop);
	ret = DB_t_cif_shop_read_by_shop_id(shop_id,&tShop);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SHOP_N;
		return E_DB_SHOP_R;
	}
	memset(&tAccount,0,sizeof tAccount);
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(tShop.cut_id,ACCTYPE_SHOPMAIN,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"read_by_customer_id_and_act_type ret[%d]cutid[%d]",ret,tShop.cut_id);
		if(DB_NOTFOUND==ret)
			return  E_SHOP_ACTNO_NOT_EXIST;
		else
			return E_DB_ACCOUNT_R;
	}
	des2src(IA->sArrInActno[1],tAccount.account_id);
	return 0;
	
}

static int do_term_trade(ST_PACK *in_pack,char ext_msg[256])
{
	T_t_pif_device tDevice;
	int ret;
	if(in_pack->lvol4 <= 0)
		return E_INPUT_DATA_INVAILD;
		
	ret = DB_t_pif_device_read_lock_by_cur_and_device_id(in_pack->lvol4,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_DEVICE_N;
		else
			return E_DB_DEVICE_R;
	}
	
	ret = 0;
	if(tDevice.state_id == DEVISTAT_LOGOUT)
	{
		ret = E_DEVICE_NOT_EXIST;
	}
	else if(tDevice.lasttraserno != in_pack->lvol5)
	{
		writelog(LOG_ERR,"中断流水号不符,devid[%d]input serial[%d]"
			,in_pack->lvol4,in_pack->lvol5);
		ret = E_SERIALNO_NOT_EXIST;
	}
	else if(!ret)
	{
		tDevice.lasttraserno = in_pack->lvol5+1;
		ret = DB_t_pif_device_update_lock_by_cur(&tDevice);
		if(ret)
		{
			writelog(LOG_DEBUG,"更新中断流水号失败devid[%d]",in_pack->lvol4);
			return E_DB_DEVICE_N;
		}
	}
	 DB_t_pif_device_free_lock_cur();
	 return 0;
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
//系统模拟入账
 int tend_to_enter_account(ST_PACK *in_pack,InAcc *IA,int trade_code,T_t_tif_tradeserial *tradeserial){
	int ret = 0;
	int i=0;
	int	card_id = 0;
	
	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;

	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));

	card_id=tradeserial->card_id;
	
	//根据卡号和钱包号得到消费者账号(借方)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			ret=E_ACTNO_NOT_EXIST;
		else
			ret=E_DB_ACCOUNT_R;
		return ret;
	}
	
	ret=DB_t_cif_customer_read_by_cut_id(tAccount.customer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tAccount.customer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	

	IA->iCardNo=tradeserial->card_id;
	IA->iFeeType=tCustomer.fee_type;
	IA->dArrInAmt[0]=tradeserial->trade_fee;
	IA->iMainDevId=tradeserial->maindevice_id;				//工作站标识
	IA->iDevId=tradeserial->device_id;						//设备ID
	IA->iSerialNo=tradeserial->serial_no;					//流水号
	IA->iTradeNo=tradeserial->serial_type;					//交易码
	strcpy(IA->sTxDate,tradeserial->operate_date);			//交易日期
	strcpy(IA->sTxTime,tradeserial->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,tradeserial->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,tradeserial->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,tradeserial->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,tradeserial->enteract_time);		//记账时间
	strcpy(IA->sMdeOper,tradeserial->oper_code);			//操作员
	strcpy(IA->sChkOper,tradeserial->reserve_1);			//复核操作员

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
	IA->iTxCnt=tradeserial->trade_count;					//交易次数
	IA->dInCardBala=tradeserial->in_balance;				//入卡值
	IA->dOutCardBala=-1;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	tradeserial->out_balance=IA->dOutCardBala;			//出卡值
	if(amtcmp(tradeserial->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}

	for(i=1;i<=IA->iOutTxTypeCnt;i++)
	{
		switch(IA->iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial->deposit_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial->boardfee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tradeserial->in_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tradeserial->cost_fee=IA->dArrOutAmt[i];
				break;
			default:
				break;
		}
		
	}

	ret = db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_roll_back error,errcode=[%d]",ret);
		return E_DB_ROLLBACK;
	}
	return 0;
}

 int record_serial(ST_PACK *in_pack,T_t_tif_tradeserial *tradeserial,ST_PACK *out_pack){
	int ret =0;
	int card_id= 0;
	double dUniqno = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	Operator[33+1] = "";
	int	maindevice_id = 0;
	int	device_id = 0;

	T_t_pif_card tCard;
	card_id=in_pack->lvol0;

	memset(&tCard,0,sizeof(tCard));
	
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
		return ret;
	}
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}

	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}						
	tradeserial->serial_no = D2I(dUniqno);			//流水号
	
	des2src(Operator,in_pack->scust_no);					//操作员号								//采集设备标识

	strncpy(tradeserial->operate_date,sysdate,sizeof(sysdate)-1);				//发生日期
	strncpy(tradeserial->operate_time,systime,sizeof(systime)-1);
	des2src(tradeserial->collect_date,tradeserial->operate_date);								//采集日期
	des2src(tradeserial->collect_time,tradeserial->operate_time);								//采集时间
	des2src(tradeserial->enteract_date,logicdate);							//处理日期
	des2src(tradeserial->enteract_time,tradeserial->operate_time);							//处理时间
	tradeserial->serial_no = D2I(dUniqno);									//流水号
	tradeserial->purse_id = PURSE_NO_ONE;					//钱包号
	tradeserial->serial_state = SERISTAT_NODEBT;								//流水状态
	tradeserial->maindevice_id = maindevice_id;						//上传工作站标识
	tradeserial->device_id = device_id;										//采集设备标识
	tradeserial->card_id = card_id;										//交易卡号
	tradeserial->customer_id=tCard.cosumer_id;								//客户号
	des2src(tradeserial->oper_code,Operator);
	tradeserial->trade_count=in_pack->lvol1+1;		//交易次数
	tradeserial->in_balance=in_pack->damt0;			//入卡值

	//除了海事的考试报名，别的交易金额不能小于0
	if(amtcmp(in_pack->damt1, 0) <= 0)
	{
		//if(tradeserial->serial_type != 847233)
			return E_INPUT_AMT_NULL;
	}
	tradeserial->trade_fee=in_pack->damt1;				//交易金额

	if(tradeserial->serial_type==TXCODE_NET_CHARGE_EXT )	// 锐捷网费
		des2src(tradeserial->reserve_2,in_pack->sall_name);
	else
		des2src(tradeserial->reserve_2,in_pack->vsmess);

	ret = DB_t_tif_tradeserial_add(tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit error,errcode=[%d]",ret);
		return E_DB_COMMIT;
	}
	return 0;
	

}	


static int record_small_serial(ST_PACK *in_pack,T_t_tif_tradeserial *tradeserial,ST_PACK *out_pack){
	int ret =0;
	double dUniqno = 0;
	 T_t_tif_tradeserial  tPacketSerial;

	//保存充值流水
	memset(&tPacketSerial, 0, sizeof tPacketSerial);
	memcpy(&tPacketSerial, tradeserial, sizeof tPacketSerial);
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		return ret;
	}
	tPacketSerial.serial_no = D2I(dUniqno);
	tPacketSerial.serial_state = SERISTAT_NONEEDDEBT;
	tPacketSerial.serial_type = TXCODE_SAVING_SMALL_PACKET;
	tPacketSerial.purse_id = 33;//33扇区钱包
	tPacketSerial.in_balance = in_pack->damt2;
	tPacketSerial.trade_fee = in_pack->damt1;
	tPacketSerial.out_balance = tPacketSerial.in_balance + tPacketSerial.trade_fee;

	ret = DB_t_tif_tradeserial_add(&tPacketSerial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}

	out_pack->damt2=tPacketSerial.out_balance;
	out_pack->lvol1= D2I(dUniqno);			//流水号

	return 0;
	

}	






//系统正式入账
 int enter_account(ST_PACK *in_pack,InAcc *IA,ST_PACK *out_pack,T_t_tif_tradeserial *tradeserial){
	int ret = 0;
	int i=0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char sMsg[256]="";
	
	T_t_cif_customer 	tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_aif_account	tAccount;
	T_t_pif_card	tCard;


	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCard,0,sizeof(tCard));
//	memset(&tradeserial,0,sizeof tradeserial);

	card_id=in_pack->lvol0;
	
	ret=get_datetime_from_db(sysdate,systime);
	if(ret)
	{
		writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
		getsysdate(sysdate);
		getsystime(systime);
		return ret;
	}
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}

	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}


	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}

	
	//根据卡号和钱包号得到消费者账号(借方)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			ret=E_ACTNO_NOT_EXIST;
		else
			ret=E_DB_ACCOUNT_R;
		return ret;
	}
	
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}
	//得到收费类别
	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				return E_DB_SPEFEE_R;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//更新客户表的收费类别字段
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				ret= E_CUSTOMER_NOT_EXIST;
			else
				ret= E_DB_CUSTOMER_U;
			return ret;
		}
	}
	DB_t_cif_customer_free_lock_cur();

//已经入账了
	if(tradeserial->serial_state == SERISTAT_DEBT)
		goto L_RET;

	IA->iCardNo=tCard.card_id;
	IA->iFeeType=tCustomer.fee_type;
	IA->dArrInAmt[0]=tradeserial->trade_fee;
	IA->iMainDevId=tradeserial->maindevice_id;				//工作站标识
	IA->iDevId=tradeserial->device_id;						//设备ID
	IA->iSerialNo=tradeserial->serial_no;					//流水号
	IA->iTradeNo=tradeserial->serial_type;					//交易码
	strcpy(IA->sTxDate,tradeserial->operate_date);			//交易日期
	strcpy(IA->sTxTime,tradeserial->operate_time);			//交易时间
	strcpy(IA->sTxCollectDate,tradeserial->collect_date);		//采集日期
	strcpy(IA->sTxCollectTime,tradeserial->collect_time);		//采集时间
	strcpy(IA->sTxAccDate,tradeserial->enteract_date);		//记账日期
	strcpy(IA->sTxAccTime,tradeserial->enteract_time);		//记账时间
	strcpy(IA->sMdeOper,tradeserial->oper_code);			//操作员
	strcpy(IA->sChkOper,tradeserial->reserve_1);			//复核操作员

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//联机交易
	IA->iTxCnt=tradeserial->trade_count;					//交易次数
	IA->dInCardBala=tradeserial->in_balance;				//入卡值
	IA->dOutCardBala=-1;							//出卡值

	//修改借方和贷方帐户余额，记会计分录帐
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	tradeserial->out_balance=IA->dOutCardBala;			//出卡值
	if(amtcmp(tradeserial->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}

	for(i=1;i<=IA->iOutTxTypeCnt;i++)
	{
		switch(IA->iArrOutTxType[i])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tradeserial->deposit_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_BANK_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_CASH:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_BILL:
			case TXTYPE_SUBSIDY_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tradeserial->boardfee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tradeserial->in_fee=IA->dArrOutAmt[i];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tradeserial->cost_fee=IA->dArrOutAmt[i];
				break;
			default:
				break;
		}
		if(amtcmp(IA->dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lf元 ",IA->sArrOutTxName[i],IA->dArrOutAmt[i]);
		}
	}
	tradeserial->serial_state=SERISTAT_DEBT;
	/*
	ret = DB_t_tif_tradeserial_update_lock_by_cur(&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"db update t_tif_tradeserial error,errcode=[%d]",ret);
		return E_DB_TRADESERIAL_U;
	}
	*/
	
L_RET:
	out_pack->damt0=tradeserial->out_balance;	//出卡值
	out_pack->damt1=tradeserial->trade_fee;		//交易金额	
	out_pack->lvol0 = tradeserial->serial_no;		//流水号	
	sprintf(sMsg,"交易前卡余额:%.2lf元 卡当前余额:%.2lf元",tradeserial->in_balance,tradeserial->out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);
	
	return 0;
}


static int deal_water_ctl_out_pack(ST_PACK *in_pack,ST_PACK *out_pack){
	int ret = 0;	
	/*
	char price1[16]="";	
	char price2[16]="";
	char price3[16]="";
	double d_price1 = 0;
	double d_price2 = 0;
	double d_price3 = 0;
	*/
	T_t_tif_tradeserial  tPacketSerial;
	memset(&tPacketSerial, 0, sizeof tPacketSerial);
	/*
	ret=GetParameter(2201, price1);	
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2202, price2);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	ret=GetParameter(2203, price3);
	if(ret){
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	d_price1 = atof(price1);
	d_price2 = atof(price2);
	d_price3 = atof(price3);

	out_pack->damt10 = D4U5(d_price1/600,4);
	out_pack->damt11 = D4U5(d_price2/600,4);
	out_pack->damt12 = D4U5(d_price3/600,4);
	*/
 	ret = DB_t_tif_tradeserial_read_by_serial_no(in_pack->lvol7, &tPacketSerial);  //消费流水号
	if (ret)
	{
	    writelog(LOG_DEBUG,"输入号不存在消费流水号[%d]",in_pack->lvol7);
	    if (DB_NOTFOUND == ret)
	    {
	        ret = E_DB_TRADESERIAL_N;
	    }
	    else
	    {
	        ret = E_DB_TRADESERIAL_R;
	    }
	    return ret;
	}
	out_pack->damt2=tPacketSerial.out_balance;
	out_pack->lvol1=tPacketSerial.serial_no;
	return 0;
	
}

static int GetThirdPartySysId(int *sub_system_id, int trade_code, int device_id)
{
	int system_id = 0;
	char func_list[255] = "";
	int ret = 0;
	T_t_pif_device tDevice;
	T_t_pif_subsystem subsystem;
	memset(&tDevice, 0, sizeof(tDevice));
	memset(&subsystem, 0, sizeof(subsystem));
	
	sprintf(func_list, "%d", TXCODE_NET_CHARGE_EXT);
	
	if (0 == device_id)
	{
		// 设备ID号不存在, 就用交易代码查询第三方子系统
		ret = DB_t_pif_subsystem_read_by_system_type_and_func_list(SUBSYSTYPE_THIRDPARY, func_list, &subsystem);
		if (ret)
		{
			writelog(LOG_ERR,"subsystem_id=[%d]", subsystem.system_id);
			if (DB_NOTFOUND == ret)
			{
				ret = E_DB_SUBSYSPARAMS_N;
			}
			else
			{
				ret = E_DB_SUBSYSPARAMS_R;
			}
			goto L_RETU;
		}

		*sub_system_id = subsystem.system_id;
	}
	else
	{
		// 设备ID号存在, 就用设备ID号查询上级子系统
		if (0 != device_login_yes_or_no(device_id))
		{
			writelog(LOG_ERR,"Device don't login");
			return E_TRANS_TERM_NOLOGIN;	
		}

		ret = DB_t_pif_device_read_by_device_id(device_id, &tDevice);
		if (ret)
		{
			writelog(LOG_ERR,"device [%d] not found!", tDevice.device_id);
			if (DB_NOTFOUND == ret)  
			{ 
				ret = E_DB_DEVICE_N;
			}
		    else 
			{ 
				ret = E_DB_DEVICE_R;
			}
			goto L_RETU;
		}

		*sub_system_id = tDevice.subsystem_id;
	}

	writelog(LOG_ERR,"func_list=[%s]--sub_system_id=[%d]", func_list, *sub_system_id);
	return 0;
	
L_RETU:
	return ret;
}

// check account, transfer, check database and so on ......
static int DoNetCharge(int sub_system_id, ST_PACK *in_pack, ST_PACK *out_pack)
{
	int drtp_node = 0;
	int bcc_main_func = 0;
	int request_func_no = 0;
	int drtp_port = 0;
	char des_ip[20]="";
	
	int ret = 0;
	char err_msg[128] = "";
	CBccExtPack bcc_ext_pack;
	T_t_pif_third_part_system third_part_system;
	memset(&third_part_system, 0, sizeof(third_part_system));
	
	int des_func_type = 0;
	des_func_type = in_pack->lvol7;						// destination function type, 1--check user id, 2--transfer
	
	// get third ksmbcc + ksbu system parameters
	ret = DB_t_pif_third_part_system_read_by_sub_system_id_and_des_func_type(sub_system_id, des_func_type, &third_part_system);
	if (ret)
	{
		if (ret == DB_NOTFOUND)
		{
			ret = E_DB_SUBSYSPARAMS_N;
		}
		else
			ret = E_DB_SUBSYSPARAMS_R;
		goto L_RETU;
	}

	drtp_node = third_part_system.des_drtp_node;
	bcc_main_func = third_part_system.des_bcc_func;
	request_func_no = third_part_system.des_func;
	drtp_port = third_part_system.des_port;
	des2src(des_ip, third_part_system.des_ip);
	writelog(LOG_ERR,"DRTP_NO=[%d]--BCC_FUNC=[%d]--REQUEST_FUNC=[%d]--DES_FUNC_TYPE=[%d]--DES_IP=[%s]",drtp_node,bcc_main_func,request_func_no,des_func_type,des_ip);
	BCC_EXT_PACK ext_pack;
	ext_pack.drtp_node = drtp_node;
	ext_pack.bcc_main_func = bcc_main_func;
	ext_pack.request_func_no = request_func_no;
	memcpy(&ext_pack.sPack.pack, in_pack, sizeof(ext_pack.sPack.pack));
	bcc_ext_pack.SetExtPack(&ext_pack);
	bcc_ext_pack.SetHeadCol(0, F_DAMT1, F_SALL_NAME, 0);			// send user id and transfer money
    bcc_ext_pack.SetTimeOut(10);
	bcc_ext_pack.ExtCallBu();
	bcc_ext_pack.GetLastErr(&ret, err_msg);
	bcc_ext_pack.GetOutPack(out_pack);
	if (ret) 
	{
		writelog(LOG_ERR,"Call RetCode=[%d]", ret);
//		if (-2 == ret) 				// out of time, may be third part system already transfer in its account
//		{
//			out_pack->lvol11 = NETCHARGE_CODE;
//			return 0;
//		}

		goto  L_RETU;
	}

	return 0;
L_RETU:
	return ret;
}
static int pre_check_user_id(ST_PACK *in_pack, ST_PACK *out_pack, transfer_control_t *trans_ctl)
{
	int ret = 0;
	int card_id=0;
	int device_id = 0;
	int sub_system_id = 0;
	double in_balance = 0.0;
	double trade_fee = 0.0;
	double dUniqNo = 0.0;
	int trade_count = 0;
	char sMsg[128] = "";
	char net_charge_user_id[30] = "";
	int des_func_type = 0;
	char para_trade_money[20] = "";

	device_id = in_pack->lvol4;							// device id 
	trade_fee = in_pack->damt1;							// trade fee
	in_balance = in_pack->damt0;						// input balance
	trade_count = in_pack->lvol1;						// trade count
	des_func_type = in_pack->lvol7;						// destination function type, 1--check user id, 2--transfer
	card_id = in_pack->lvol0;							// trade card id

	// check transfer balance
	if (amtcmp(trade_fee - in_balance, 0) > 0)
	{
		writelog(LOG_ERR,"tradeserial.trade_fee=[%lf]in_balance=[%lf]", trade_fee, in_balance);
		return E_BALANCE_SHORTAGE;
	}

	ret=GetParameter(NET_CHARGE_TRADE_MONEY, para_trade_money);	
	if (ret)
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}

	writelog(LOG_ERR,"para_trade_money=[%lf]", atof(para_trade_money));
	if (amtcmp((int)trade_fee % (int)atof(para_trade_money), 0) != 0)
	{
		writelog(LOG_ERR,"tradeserial.trade_fee=[%lf]in_balance=[%lf]", trade_fee, in_balance);
		return E_NETCHARGE_INPUTMONEY;
	}

	des2src(net_charge_user_id, in_pack->sall_name);
	if (0 == strlen(net_charge_user_id)) 
	{ 
		return  E_NETCHARGE_USER_ID_NULL; 
	}

	ret = GetThirdPartySysId(&sub_system_id, TXCODE_NET_CHARGE_EXT, device_id);
	if (ret)	
	{
		return ret;
	}

	// send third party trade
	ret = DoNetCharge(sub_system_id, in_pack, out_pack);
	if (ret)
	{
		return ret;
	}
	
	in_pack->lvol11 = out_pack->lvol11;					// get timeout flag
	return 0;
}

static int transfer_balance(ST_PACK *in_pack, char ext_msg[256])
{
	int ret = 0;
	int sub_system_id = 0;
	int device_id = 0;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack, 0, 1);
	
	device_id = in_pack->lvol4;	
	
	ret = GetThirdPartySysId(&sub_system_id, TXCODE_NET_CHARGE_EXT, device_id);
	if (ret)
	{
		return ret;
	}
	
	// send third party trade
	ret = DoNetCharge(sub_system_id, in_pack, out_pack);
	if (ret)
	{
		return ret;
	}
	
	return 0;
}

static int do_netcharge_acc(ST_PACK *in_pack,char ext_msg[256])	//(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int ret=0;
	int ret_net_charge = 0;
	int card_id=0;
	int cnt = 0;
	int subsystem_id = 0;
	InAcc IA;
	char datetime[20]="";

	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	int time_out = 0;

	T_t_pif_device tDevice;
	T_t_pif_card card;
	T_t_cif_customer tCustomer;
	T_t_tradecode_shop tradeshop;
	T_t_subsysparams t_subsysparams;

    // 此处需要通过后台获得一个机房收费的商户ID号, 以便于进行发生交易

	memset(&tDevice, 0, sizeof(tDevice));
	memset(&card, 0, sizeof(card));
	memset(&tCustomer, 0, sizeof(tCustomer));
	memset(&IA, 0, sizeof(IA));
	memset(&t_subsysparams,0,sizeof(t_subsysparams));
    
    ST_PACK ArrayPack;
    memset(&ArrayPack, 0, sizeof(ArrayPack));

	ret =DB_t_tradecode_shop_open_select_by_c0_and_trade_code(TXCODE_NETFEE_TRANS);
	if(ret){
		writelog(LOG_ERR,"DB_t_tradecode_shop_open_select_by_c0_and_trade_code error,errcode=[%d]",ret);
		return 	ret;
	}
	while(1){
		memset(&tradeshop,0,sizeof(tradeshop));
		ret =DB_t_tradecode_shop_fetch_select_by_c0(&tradeshop);
		if(ret){
			DB_t_tradecode_shop_close_select_by_c0();
			if(cnt==0)
			{
				writelog(LOG_ERR,"DB_t_tradecode_shop_fetch_select_by_c0 error errorcode=[%d]",ret);
				return E_SHP_ID_NOT_EXIST;
			}
			break;
		}
		cnt++;
		subsystem_id = tradeshop.subsystem_id;
	}

	ret = DB_t_subsysparams_read_by_sysid(subsystem_id, &t_subsysparams);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_SUBSYSPARAMS_R;
	}

	DRTP_BRANCH = t_subsysparams.bcc_drtp_no;
	BCC_BASEFUNCNO = t_subsysparams.bcc_main_func;
	time_out = t_subsysparams.bcc_interval;
	
   
	
	memset(&card, 0, sizeof(card));

	card_id = in_pack->lvol0;
	
	ret = DB_t_pif_card_read_by_card_id(card_id, &card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		return E_TRANS_SCHACC_NOEXIT;
	}

    ret = DB_t_cif_customer_read_by_cut_id(card.cosumer_id, &tCustomer);
    if(ret)
    {
        if(DB_NOTFOUND == ret)
            return E_DB_CUSTOMER_N;
        else
            return E_DB_CUSTOMER_R;
    }

	 ST_CPACK sPack;
    ResetNormalCPack(&sPack, 0, 1);
    sPack.head.RequestType = 847308;
    SetHeadCol(&sPack, F_LVOL6,F_SCUST_AUTH, F_SCUST_AUTH2,F_SROOM_NO,F_DAMT0,F_DAMT1,F_SSERIAL1, F_SORDER2, F_SCUSTTYPES, 0);       // 设置发送windows BU的头部视图信息
    memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));
    
	ST_CPACK aPack ;
	ResetNormalCPack(&aPack, 0, 1);
	SetHeadCol(&aPack, F_LVOL11,F_DAMT0,F_DAMT1,F_SSERIAL1, 0); 

    // 和windows平台上的BCC进行通讯
    writelog(LOG_DEBUG,"ExtCall: DRTP_BRANCH[%d],BCC_BASEFUNCNO[%d],time_out[%d]",DRTP_BRANCH,BCC_BASEFUNCNO,time_out);
	sPack.pack.damt0 = in_pack->damt1;  //转帐金额	// 保留，为了和老系统兼容
	strcpy(sPack.pack.scust_auth,tCustomer.stuemp_no);  //学号
	strcpy(sPack.pack.sroom_no,"009");
	strcpy(sPack.pack.sserial1,in_pack->sserial1);		//密码
	getdatetime(datetime);
	strcpy(sPack.pack.scust_auth2,datetime);
	Strncpy(sPack.pack.sorder2,in_pack->sname,sizeof(sPack.pack.sorder2));  //设备物理ID
    ret_net_charge = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, time_out, &sPack, &aPack, &ArrayPack);

	if(ret_net_charge<0)
		return ret_net_charge; 	//通讯超时
		
	ret = aPack.pack.lvol11;	
  
        if (ret)
        {
	        if (-1 ==ret)
	        {
	            return E_NETCHARGE_DATABASE_CONNECT;
	        }  
	        else if (-2 == ret)
	        {
	            writelog(LOG_ERR,"ret=[%d]",E_NETCHARGE_NO_ACCOUNT);
	            return E_NETCHARGE_NO_ACCOUNT;
	        }  
	        else if (-3 == ret)
	        {
	            return E_NETCHARGE_NODATE;
	        }
	        else if (-5 == ret)
	        {
	            return E_NETCHARGE_OUT_OF_MAXBALANCE;
	        }
	        else if (-6 == ret)
	        {
	            return E_NETCHARGE_ACCOUNT_ISEXIST;
	        }    
	        else if (-8 == ret)
	        {
	            return E_NETCHARGE_ACCOUNT_NOTOPEN;
	        }    
	        else if (-11 == ret)
	        {
	            return E_NETCHARGE_DEPOSIT_SHORTAGE;
	        }    
	        else if (-15 == ret)
	        {
	            return E_NETCHARGE_MULTI_ACCOUNT;
	        }    
	        else if (-1004 == ret)
	        {
	            return E_NETCHARGE_STOP_SERVICE;
	        }    
	        else if (-1005 == ret)
	        {
	            return E_NETCHARGE_STOP_SERVICE;
	        }    
		else if(-16 == ret)
			return E_INPUT_AMT;
		else if(-17 == ret)
			return -17;
		else if(-18 == ret)
			return E_NETCHARGE_ACC_PSWORD;
	        else
	               return E_TRANS_UNKNOW_ERROR; 
        	}
    
    return 0;
}

static int do_netcharge_check(ST_PACK *in_pack,ST_PACK *out_pack,transfer_control_t *trans_ctl)	//(ST_PACK *in_pack,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	int cnt=0;
	int ret=0;
	int ret_net_charge = 0;
	int card_id=0;
	int subsystem_id = 0;
	InAcc IA;
	char datetime[20]="";
	int DRTP_BRANCH =0;
	int BCC_BASEFUNCNO =0;
	int time_out = 0;

	T_t_aif_account tAccount;
	T_t_pif_card card;
	T_t_cif_customer tCustomer;
	T_t_tradecode_shop tradeshop;
	T_t_subsysparams t_subsysparams;

	memset(&tAccount, 0, sizeof(tAccount));
	memset(&card, 0, sizeof(card));
	memset(&tCustomer, 0, sizeof(tCustomer));
	memset(&IA, 0, sizeof(IA));
	memset(&t_subsysparams,0,sizeof(t_subsysparams));

	ret =DB_t_tradecode_shop_open_select_by_c0_and_trade_code(TXCODE_NETFEE_TRANS);
	if(ret){
		writelog(LOG_ERR,"DB_t_tradecode_shop_open_select_by_c0_and_trade_code error,errcode=[%d]",ret);
		return 	ret;
	}
	while(1){
		memset(&tradeshop,0,sizeof(tradeshop));
		ret =DB_t_tradecode_shop_fetch_select_by_c0(&tradeshop);
		if(ret){
			DB_t_tradecode_shop_close_select_by_c0();
			if(cnt==0)
			{
				writelog(LOG_ERR,"DB_t_tradecode_shop_fetch_select_by_c0 error errorcode=[%d]",ret);
				return E_SHP_ID_NOT_EXIST;
			}
			break;
		}
		cnt++;
		subsystem_id = tradeshop.subsystem_id;
	}

	ret = DB_t_subsysparams_read_by_sysid(subsystem_id, &t_subsysparams);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_SUBSYSPARAMS_R;
	}

	DRTP_BRANCH = t_subsysparams.bcc_drtp_no;
	BCC_BASEFUNCNO = t_subsysparams.bcc_main_func;
	time_out = t_subsysparams.bcc_interval;
	
	
    trans_ctl->check_user_pwd = 0;
    ST_PACK ArrayPack;
    memset(&ArrayPack, 0, sizeof(ArrayPack));
    
    
	
	memset(&card, 0, sizeof(card));

	card_id = in_pack->lvol0;
	
	ret = DB_t_pif_card_read_by_card_id(card_id, &card);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_card_read_lock_by_cur_and_card_id error,errcode=[%d]",ret);
		return E_TRANS_SCHACC_NOEXIT;
	}

	if (strncmp(card.state_id, TYPE_YES, 1) != 0)
	{
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHACC_DESTORY;
	}

	if (STATE_TRUE == card.state_id[CARDSTAT_TYPE_LOST])
	{
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_LOSTING;
	}

	if (STATE_TRUE == card.state_id[CARDSTAT_TYPE_FREEZE])
	{
		writelog(LOG_ERR,"card_state=[%s]",card.state_id);
		return E_TRANS_SCHCARD_FREEZE;
	}

    if (STATE_TRUE == card.state_id[CARDSTAT_TYPE_WFAIL])
    {
        writelog(LOG_ERR,"card_state=[%s]",card.state_id);
        return E_TRANS_SCHCARD_WFAIL;
    }

	ret = DB_t_cif_customer_read_by_cut_id(card.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCustomer.cut_id);		
		return E_CUSTOMER_NOT_EXIST;		
	}
	
	if(amtcmp(in_pack->damt1, 0) <= 0)
	{
		return E_INPUT_AMT;
	}
	
	if(amtcmp(in_pack->damt0, 0) < 0)
	{
		return E_INPUT_CARD_BALA;
	}

    if (amtcmp(in_pack->damt0, in_pack->damt1) < 0)
    {
        writelog(LOG_ERR, "tCard balance[%lf] trade amount[%lf]", in_pack->damt0, in_pack->damt1);
	return E_BALANCE_SHORTAGE;
    }

//    SetCol(handle,0);
 //  	SetCol(handle,F_LVOL0,F_DAMT0,F_DAMT1,F_SSERIAL1,0);
	ST_CPACK sPack;
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = 847307;
	SetHeadCol(&sPack, F_LVOL6,F_SCUST_AUTH,F_SCUST_AUTH2,F_SROOM_NO,F_DAMT1,F_SSERIAL1, 0);       // 设置发送windows BU的头部视图信息
	strcpy(in_pack->scust_auth,tCustomer.stuemp_no);
	
	strcpy(in_pack->sroom_no,"008");
	getdatetime(datetime);
	strcpy(in_pack->scust_auth2,datetime);
	memcpy(&(sPack.pack), in_pack, sizeof(sPack.pack));

	writelog(LOG_DEBUG,"学号[%s],密码[%s],请求码[%s],金额[%f],交易时间[%s]",in_pack->scust_auth,in_pack->sserial1,
		in_pack->sroom_no,in_pack->damt1,in_pack->scust_auth2);
	ST_CPACK aPack ;
	ResetNormalCPack(&aPack, 0, 1);
	SetHeadCol(&aPack, F_LVOL11, 0);
    // 测试连接方数据库是否成功，并且下一条不入账流水
    writelog(LOG_DEBUG,"ExtCall: DRTP_BRANCH[%d],BCC_BASEFUNCNO[%d],time_out[%d]",DRTP_BRANCH,BCC_BASEFUNCNO,time_out);
    ret_net_charge = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, time_out, &sPack, &aPack, &ArrayPack);

	writelog(LOG_ERR,"ExtCall retCode[%d],ret[%d]",aPack.head.retCode,ret_net_charge);
    if (ret_net_charge < 0)
    {
       return ret_net_charge;  //通讯超时
    }
	
	out_pack->lvol11 = aPack.pack.lvol11;
	
    	writelog(LOG_ERR,"out_pack->lvol11=[%d]",out_pack->lvol11);

    if (1 == out_pack->lvol11)
	  return 0;
    else if (-1003 == out_pack->lvol11)
            return E_NETCHARGE_NO_ACCOUNT;
    	else if(-16 == out_pack->lvol11)
		return E_INPUT_AMT;
	else if(-17 == out_pack->lvol11)
		return -17;
	else if(-18 == out_pack->lvol11)
		return E_NETCHARGE_ACC_PSWORD;
    else 
        return E_NETCHARGE_DATABASE_CONNECT;
  
    return 0;
}

static const ext_consumer_request_t  g_transfer_process[] = {
	// 广州大学城手机充值
	{PRE_CHEDK_ENTER_ACCOUNT_MOBILE_TRANS, TXCODE_MOBILE_TRANS,TIMEOUT_REDO_FORBIT ,check_cellphone,get_third_part_account,trans_request,NULL,NULL},
	// 广州大学城水控转账
	{PRE_ENTER_ACCOUNT_WATER_TRANS,TXCODE_CONSUME, NULL,TIMEOUT_REDO_FORBIT ,get_third_part_account,NULL,deal_water_ctl_out_pack,record_small_serial},
	// 广州大学城读卡器终端联机消费
	{TERMINAL_TRADE,TXCODE_COSUME_LOG,TIMEOUT_REDO_FORBIT ,pre_check_term_trade,search_account_from_term_id,do_term_trade,NULL,NULL},
	// 爱立德电控
	{PRE_LOGIN_ELECT_TRANS,TXCODE_ELECT_TRANS,TIMEOUT_REDO_FORBIT ,elect_room_check,get_third_part_account,elect_request,NULL,NULL},
	// 常工电控
	{CHECK_ROOMNAME_ELECT_TRANS,TXCODE_ELECT_TRANS,TIMEOUT_REDO_FORBIT ,elect_room_check_get_name,get_third_part_account,elect_request_changzhou,NULL,NULL},
	// 海事大学考试报名
	{TURN_OVER,TXCODE_TURNOVER,TIMEOUT_REDO_FORBIT ,pre_check_fee,get_third_part_account,write_turn_over_fee,NULL,NULL},
	// 海洋锐捷网费
	{HGC_RJ_NETWORK, TXCODE_NET_CHARGE_EXT, TIMEOUT_REDO_FORBIT ,pre_check_user_id, get_third_part_account, transfer_balance, NULL, NULL},
	// 城市热点充值
	{NET_FEE_TRANS,TXCODE_NETFEE_TRANS,TIMEOUT_REDO_FORBIT ,do_netcharge_check,get_third_part_account,do_netcharge_acc,NULL,NULL},
	{-1,-1,0,NULL,NULL,NULL,NULL,NULL}
};


int ext_consumer_find_trade(int request_type,ext_consumer_request_t *transfer)
{
	int i = 0;
	//writelog(LOG_DEBUG,"请求功能号[%d]",request_type);
	while(g_transfer_process[i].request_type != -1)
	{
		//writelog(LOG_DEBUG,"功能号[%d]",g_transfer_process[i].request_type);
		if(g_transfer_process[i].request_type == request_type)
		{
			*transfer = g_transfer_process[i];
			return 0;
		}
		i++;
	}
	return E_TRANS_FUNC_NONSUPPORT;
}

