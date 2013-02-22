/* --------------------------------------------
 * 程序名称: F250006.sqc
 * 创建日期: 2008-06-28
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 转账模拟程序
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



int F250006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int money,tradefee = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SDATE0,F_STIME0,F_SORDER2,F_SCUSTTYPES,F_SSERIAL1,F_SSERIAL0,F_LVOL2,F_SCUST_NO,0);

	writelog(LOG_DEBUG,"txdate[%s],txtime[%s],termid[%s],input1[%s],input2[%s],balance[%s],cardid[%s],tradecount[%d],\
	trade[%s],flag[%d],serialno[%d],oper[%s]",in_pack->sdate0,in_pack->stime0,in_pack->sorder2,in_pack->scust_auth,
	in_pack->sstation0,in_pack->sserial1,in_pack->sserial0,in_pack->lvol1,in_pack->sorder0,in_pack->lvol0,in_pack->lvol2,in_pack->scust_no);
	
	// 卡余额
	money = atoi(in_pack->sserial1);
	tradefee = D2I(atof(in_pack->sorder0)*100.0);
	
	if(money < tradefee)
	{
		*pRetCode = E_INPUT_AMT;
		goto l_ret;
	}
	
	des2src(out_pack->sdate0,in_pack->sdate0);
	des2src(out_pack->stime0,in_pack->stime0);
	des2src(out_pack->sorder2,in_pack->sorder2);
	des2src(out_pack->sserial0,in_pack->sserial0);
	sprintf(out_pack->sserial1,"%d",money-tradefee);
	sprintf(out_pack->scusttypes,"转账成功");
	out_pack->lvol2 = 1000;
	des2src(out_pack->scust_no,"system");
	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
l_ret:
	return -1;
}


