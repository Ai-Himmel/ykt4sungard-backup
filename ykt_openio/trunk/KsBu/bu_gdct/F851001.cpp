/* --------------------------------------------
* 程序名称: F851001.cpp
* 创建日期: 2009-12-16
* 程序作者: 汤成
* 版本信息: 1.0.0.0
* 程序功能: 空中充值帐户查询(包含第三方对接)
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
#include "bufunc.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include <string>

#include "logfile.h"
#include "ksbu.h"
#include "gdctpub.h"
extern CSvrLink *g_pSvrLink;

#ifdef __cplusplus
extern "C" {
#endif

int F851001(TRUSERID *handle, int iRequest, ST_PACK *in_pack, int *pRetCode, char *szMsg)
{
	int ret = 0;
	int t;
	TRUSERID answer_handle;
	char request_data[512];
	char drtphandle[121] = "";
	int req_len,offset;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	gdct_msg_t mymsg;

	memcpy(&answer_handle,handle,sizeof answer_handle);

	ResetNormalCPack(&aPack, 0, 1);

	SetCol(handle,0);
	SetCol(handle,F_LSAFE_LEVEL,F_VSMESS, F_SCUST_LIMIT, F_SBANK_CODE,F_SBANK_ACC,
		F_SCUSTTYPES,F_LVOL1,F_SSTATION0, 0);
	strcpy(drtphandle,in_pack->vsvarstr1);

	memset(&mymsg,0,sizeof mymsg);
	strcpy(mymsg.msgtype,"DCCZ");
	strcpy(mymsg.msgcode,"000006");
	if(strlen(in_pack->sphone3)>4)
		mymsg.seqno = atoi(in_pack->sphone3+4);
	
	// 交易码
	offset = 0;
	memcpy(mymsg.body,g_gdct_pswd,32);
	offset += 32;
	// 交易方式
	memcpy(mymsg.body+offset,in_pack->sbank_code2,6);  // 支付方式
	offset += 6;
	// 手机号
	memset(mymsg.body+offset,' ',13); 
	t = strlen(in_pack->sbank_acc2);
	if(t > 13)
	{
		*pRetCode = 1000;
		return -1;
	}
	// 交易参考号
	memset(mymsg.body+offset,' ',20);
	memcpy(mymsg.body+offset+6,in_pack->sphone3,14);
	offset += 20;
	// 代理商手机号
	memcpy(mymsg.body+offset,g_gdct_phone_num,13);
	offset += 13;

	mymsg.bodylen = offset;

	PackCTRequest(&mymsg,request_data,req_len);
	
	ret = CTSendAndRecv(request_data,req_len,&mymsg,g_timeout);

	if(ret)
	{
		*pRetCode = 1002;
		return -1;
	}
	else
	{
		strcpy(mymsg.respcode,"0000");
		if(strncmp(mymsg.respcode,"0000",4)!=0)
		{
			*pRetCode = atoi(mymsg.respcode);
			TranslateErrMsg(mymsg.respcode,szMsg);
			return -1;
		}
		else
		{
			GetRespDataAsInteger(&mymsg,0,16,t);
			out_pack->lvol12 = t;
		}
	}
	
	ResetNormalCPack(&aPack,0,1);
	SetHeadCol(&aPack,F_LVOL0,F_DAMT0,F_LVOL5,F_DAMT2,F_DAMT1,F_SNAME2,F_SDATE1,F_SDATE3,
		F_LWITHDRAW_FLAG,F_LSERIAL1,F_LVOL12,0);
	
	out_pack->lvol0 = in_pack->lvol5;//trans.termseqno;
	out_pack->damt0 = in_pack->lvol7 / 100.0;
	out_pack->lvol5 = in_pack->lvol7;
	//out_pack->damt2 = trans.cardbefbal;
	out_pack->damt1 = in_pack->lvol1/100.0;//trans.inputamt;
	strcpy(out_pack->sname2,in_pack->sphone3); //dtl_.refno);
	strcpy(out_pack->sdate1,in_pack->sdate0);//dtl_.accdate);
	strcpy(out_pack->sdate3,in_pack->sdate0);//trans.sysdate);
	out_pack->lwithdraw_flag = in_pack->lwithdraw_flag;//=trans.termid;
	out_pack->lserial1=in_pack->lvol5;//trans.termseqno;
	//g_pSvrLink->SetAnswerMode(AM_CONFIRM);
	//SetTransHandle(&answer_handle,drtphandle);
	//AnswerDataEx(&answer_handle,&aPack,NULL,0,szMsg);
	g_pSvrLink->SetCol(handle,aPack.head.ParmBits);
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
}

#ifdef __cplusplus
}
#endif