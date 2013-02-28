/* --------------------------------------------
 * 创建日期: 2009-08-08
 * 程序作者:
 * 版本信息: 3.0.0.0
 * 程序功能: 交易撤销(请求交易参考号)
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"
#include "transfunc.h"

//iint OnlineTransRev(char *oldaccdate,int oldtermid,int oldtermseqno);
// int AccTransRev(char *oldaccdate,int oldtermid,int oldtermseqno);

int F850001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	TRANS& trans=ats.trans;
	des2src(trans.refno,rPack->sphone3);

	if(strlen(trans.refno)!=14)
	{
		 ERRTIP("交易参考号错误");
		 return E_COMMON_ERR;
	}
	T_t_refno tRefno;

	memset(&tRefno,0,sizeof(tRefno));

	ret=DB_t_refno_read_by_refno(trans.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_REFNO_R;
	}
	if(strncmp(tRefno.mac,rPack->saddr,8)!=0)
	{
		ERRTIP("交易参考号MAC校验错误");
		return E_COMMON_ERR;
	}
	if(RS_SUCC!=tRefno.status)
	{
		TIPINFO("交易已冲正");
		return 0;
	}
	ats.trans.transcode=TC_TRANSREV;
	ats.trans.termid=tRefno.termid;
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	des2src(ats.trans.chkopercode,rPack->semp_no);
	char authrightflag=rPack->sstatus2[0];
	if('1'==authrightflag)
	{
		ret=chk_oper_pwd(ats.trans.chkopercode,rPack->scust_limit);
		if(ret)
			return ret;
		ret=AccTransRev(tRefno.accdate,tRefno.termid,tRefno.termseqno);
		if(ret)
		{
			writelog(LOG_ERR,"acctransrev err ret=%d",ret);
			return ret;
		}			
	}
	else
	{
		ret=OnlineTransRev(tRefno.accdate,tRefno.termid,tRefno.termseqno);
		if(ret)
		{
			writelog(LOG_ERR,"acctransrev err ret=%d",ret);
			return ret;
		}
	}
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,F_LVOL0,F_SPHONE3,F_SADDR,F_LWITHDRAW_FLAG,F_SDATE3,F_STIME3,F_SEMP,F_LSERIAL1,F_VSMESS,0);	
	outPack->lvol0=ats.trans.cardno;
	des2src(outPack->sdate3,ats.trans.accdate);
	des2src(outPack->stime3,ats.trans.acctime);
	des2src(outPack->semp,ats.trans.opercode);
	outPack->lserial1=ats.trans.termseqno;
	strcpy(outPack->sphone3,tRefno.refno);
	strcpy(outPack->saddr,tRefno.mac);
	strcpy(outPack->vsmess,ats.remark.c_str());
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

