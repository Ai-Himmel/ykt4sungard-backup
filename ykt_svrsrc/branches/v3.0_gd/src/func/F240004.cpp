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
#include "acctrans.h"
#include "busqc.h"


int F240004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;

	T_t_refno     tRefno;
	T_t_transdtl  transdtl; //卡操作流水表，用做冲正用

	memset(&transdtl,0,sizeof transdtl);
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	SetCol(handle,0);
   	SetCol(handle,F_SHOLDER_AC_NO,F_SCLOSE_EMP,F_SORDER0,F_SORDER1,F_SSERIAL1,F_LVOL0,F_LVOL1,F_SDATE0,F_STIME0,F_SDATE1,F_STIME1,F_SCUST_NO,F_SCHANGE_EMP,F_SSERIAL0,F_LVOL2,F_SCUST_AUTH,F_SSTATUS1,F_SEMP_PWD,F_SEMP_PWD2,F_SSTATION0,F_SSTATION1,F_SORDER2,0);

	ret =  DB_t_refno_open_select_by_c1_and_status(RS_YKTREVSUCC);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_REFNO_N;
		return E_DB_REFNO_R;
	}
	while(1)
	{
		memset(&tRefno,0,sizeof tRefno);
		ret = DB_t_refno_fetch_select_by_c1(&tRefno);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return 0;
			else
				return E_DB_REFNO_R;
		}
		break;
	}
	ret=DB_t_transdtl_read_by_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(ret==DB_NOTFOUND)
			return E_DB_TRANSDTL_N;
		else 
			return E_DB_TRANSDTL_R;
	}	
	sprintf(out_pack->sorder0,"%-9d", int(transdtl.amount));     // 转账时 限制了金额不能有小数
	Strncpy_t(out_pack->sdate0,transdtl.transdate,sizeof(out_pack->sdate0));
	Strncpy_t(out_pack->stime0,transdtl.transtime,sizeof(out_pack->stime0));
	sprintf(out_pack->sserial0,"%-10d",transdtl.cardno);
	Strncpy_t(out_pack->scust_auth,transdtl.extdata,sizeof(out_pack->scust_auth));
	out_pack->lvol0=atoi(transdtl.refno+8);
	//out_pack->lvol1=atoi(transdtl.refno+8);
	out_pack->lvol2=transdtl.termid;

	des2src(out_pack->sholder_ac_no,transdtl.refno);	// 交易参考号
	des2src(out_pack->sdate1,tRefno.mac);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


