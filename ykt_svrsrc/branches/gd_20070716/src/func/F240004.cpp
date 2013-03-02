/* --------------------------------------------
 * 程序名称: F240004.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 冲正查询
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


int F240004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_tif_tradeserial  tradeserial; //卡操作流水表，用做冲正用
	memset(&tradeserial,0,sizeof tradeserial);
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	SetCol(handle,0);
   	SetCol(handle,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,
		   F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,
		   F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	ret = DB_t_tif_tradeserial_next_flush(&tradeserial);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
		{
			*pRetCode=E_DB_TRADESERIAL_N;
			goto L_RETU;
		}
		else 
		{
			*pRetCode=E_DB_TRADESERIAL_R;
			writelog(LOG_ERR,"读取冲正记录失败,errcode=[%d]",ret);
			goto L_RETU;
		}
	}

	sprintf(out_pack->sorder0,"%-9d", int(tradeserial.trade_fee));
	Strncpy_t(out_pack->sdate0,tradeserial.operate_date,sizeof(out_pack->sdate0));
	Strncpy_t(out_pack->stime0,tradeserial.operate_time,sizeof(out_pack->stime0));
	sprintf(out_pack->sserial0,"%-10d",tradeserial.card_id);
	Strncpy_t(out_pack->scust_auth,tradeserial.b_act_id,sizeof(out_pack->scust_auth));
	out_pack->lvol0=tradeserial.reviseserial_no;
	out_pack->lvol1=tradeserial.serial_no;
	out_pack->lvol2=tradeserial.device_id;

	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
L_RETU:
	return ret;

}


