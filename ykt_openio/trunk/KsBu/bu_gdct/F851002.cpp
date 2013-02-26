/* --------------------------------------------
* 程序名称: F851002.cpp
* 创建日期: 2009-12-16
* 程序作者: 汤成
* 版本信息: 1.0.0.0
* 程序功能: 空中充值帐户支付(包含第三方对接)
* --------------------------------------------
* 修改日期:
* 修改人员:
* 修改描述:
* 版本信息:
* 备注信息:
* --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include "bufunc.h"
#include "gdctpub.h"
#include "logfile.h"

extern CSvrLink *g_pSvrLink;

#ifdef __cplusplus
extern "C" {
#endif

int F851002(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	TRUSERID answer_handle;
	char request_data[512];
	char drtphandle[129];
	int req_len,offset,t;
	ST_CPACK aPack;
	ST_CPACK sPack;
	ST_PACK *out_pack = &(aPack.pack);
	gdct_msg_t mymsg;

	memcpy(&answer_handle,handle,sizeof answer_handle);
	memset(&mymsg,0,sizeof mymsg);
	strcpy(mymsg.msgtype,"DCCZ");
	strcpy(mymsg.msgcode,"000005");
	if(strlen(in_pack->sphone3)>4)
		mymsg.seqno = atoi(in_pack->sphone3+4);

	offset = 0;
	memcpy(mymsg.body,g_gdct_pswd,32); // 密码
	offset += 32;
	memcpy(mymsg.body+offset,in_pack->sbank_code2,6);  // 支付方式
	offset += 6;
	sprintf(mymsg.body+offset,"%010d",in_pack->lvol1); // 支付金额
	offset += 10;
	// 手机号
	memset(mymsg.body+offset,' ',13); 
	t = strlen(in_pack->sbank_acc2);
	if(t > 13)
	{
		*pRetCode = 1000;
		return -1;
	}
	memcpy(mymsg.body+offset+13-t,in_pack->sbank_acc2,t);
	offset += 13;
	// 交易参考号
	memset(mymsg.body+offset,' ',20);
	memcpy(mymsg.body+offset+6,in_pack->sphone3,14);
	offset += 20;
	// 代理商手机号
	memcpy(mymsg.body+offset,g_gdct_phone_num,13);
	offset += 13;
	mymsg.bodylen = offset;
	// drtphandle
	strcpy(drtphandle,in_pack->vsvarstr1);
	g_LogFile.WriteLogEx(1000,"[%s][%d]",in_pack->sbank_code2,in_pack->lvol1);




	PackCTRequest(&mymsg,request_data,req_len);
	// 发请求包
	ret = CTSendAndRecv(request_data,req_len,&mymsg,g_timeout);
	
	// 给后台确认
	ResetNormalCPack(&sPack,0,1);
	sPack.head.RequestType = 850005;
	SetHeadCol(&sPack,F_LVOL0,F_LBANK_ACC_TYPE,F_SPHONE2,F_SPHONE3,F_SHOLDER_AC_NO,
		F_LVOL1,F_LVOL2,F_VSMESS,F_SBANK_ACC,0);
	sPack.pack.lbank_acc_type = 255;
	strcpy(sPack.pack.sphone3,in_pack->sphone3);
	if(ret!=0)
	{
		sPack.pack.lvol0 = ret;
		strcpy(sPack.pack.vsmess,"通讯错误");
	}
	else
	{
		// DEBUG
		strcpy(mymsg.respcode,"0000");
		sPack.pack.lvol0 = atoi(mymsg.respcode);
		TranslateErrMsg(mymsg.respcode,sPack.pack.vsmess);
		if(strncmp(mymsg.respcode,"0000",4)==0)
		{
			// 交易成功
			offset = 0;
			GetRespDataAsString(&mymsg,22,10,sPack.pack.sphone2); // 讯源流水号
			offset += 32;
			GetRespDataAsString(&mymsg,offset,14,sPack.pack.sholder_ac_no); // 讯源交易时间
			offset += 14;
			GetRespDataAsString(&mymsg,offset,16,sPack.pack.sbank_acc); // 代理商户账户余额
			offset += 16;
			GetRespDataAsInteger(&mymsg,offset,16,t); // 充值账户余额
			sPack.pack.lvol2 = t;
			offset += 16;
			g_LogFile.WriteLogEx(1000,"支付成功,refno[%s]recvno[%s],bala[%s]",sPack.pack.sphone3
				,sPack.pack.sphone2,sPack.pack.sbank_acc);
		}
	}
	// 发送确认请求, aPack 中的数据返回给客户端
	memset(&aPack,0,sizeof aPack);
	ret = ExtCall(0,g_mainsvr_drtpno,g_mainsvr_func,0,2,&sPack,&aPack,NULL);
	if(ret >= 0)
	{
		if(aPack.head.retCode==0)
			g_LogFile.WriteLogEx(1000,"发送确认成功,refno[%s]",in_pack->sphone3);
		else
		{
			g_LogFile.WriteLogEx(1000,"发送确认失败,refno[%s],ret[%d]",in_pack->sphone3,aPack.head.retCode);
			return -1;
		}
	}
	else
	{
		g_LogFile.WriteLogEx(1000,"发送确认失败,refno[%s],ret[%d],err[%d]"
			,in_pack->sphone3,ret,aPack.head.retCode);
		// 确认失败
		return -1;

	}
	// 给客户端应答
	ResetNormalCPack(&sPack,0,1);
	//memcpy(sPack.head.ParmBits,aPack.head.ParmBits,sizeof sPack.head.ParmBits);
	memcpy(&(sPack.pack),&(aPack.pack),sizeof sPack.pack);
	//g_pSvrLink->SetAnswerMode(AM_CONFIRM);
	//SetTransHandle(&answer_handle,drtphandle);
	//AnswerDataEx(&answer_handle,&sPack,NULL,0,szMsg);
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle,&(sPack.pack),pRetCode,szMsg);
	return 0;
}

#ifdef __cplusplus
}
#endif