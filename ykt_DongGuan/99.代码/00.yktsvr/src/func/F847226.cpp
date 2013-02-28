/* --------------------------------------------
 * 程序名称: F847226
 * 创建日期: 2007-01-19
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 操作员授权卡发行
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
#include "busqc.h"
#include "acctrans.h"

int F847226(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans& ats=CAccTrans::GetInst();
	des2src(ats.trans.opercode,rPack->semp);
	ats.trans.transcode=TC_AUTHCARDOPEN;
	ret=ats.InitTrans();
	if(ret)
		return ret;			
	TRANS& trans=ats.trans;
	
	char opercode[11] = "";
	char work_key[51] = "";

	T_t_operator tOper;
	T_t_authcard tAuthCard;
		
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tOper,0,sizeof tOper);
	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SDATE2,F_SBANK_ACC,0);

	des2src(opercode,rPack->sname2);
	des2src(trans.cardphyid,rPack->sname);
	des2src(trans.showcardno,rPack->sorder0);
	if(strlen(opercode) == 0)
	{
		return E_NOTEXIST_OPER;
	}
	if(strlen(rPack->scust_limit) == 0)
	{
		return E_INPUT_OPER_NULL;
	}
	ret = IsInvalidDateTime(rPack->sdate2,"YYYYMMDD");
	if(ret)
	{
		return ret;
	}
	ret = DB_t_operator_read_by_opercode(opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_NOTEXIST_OPER;
		else
			return E_DB_OPERATOR_R;
	}
	if(tOper.status[0]=='0')
	{
		DB_t_operator_free_lock_by_c0();
		return E_OPER_LOCK;
	}	
	if(tOper.status[0]==STATUS_DELETE)
	{
		DB_t_operator_free_lock_by_c0();
		return E_OPERLOGON_UNREG;
	}
	//todo:判断如果该操作员持有该卡已经发行过,那么系统允许重复发行,但是不计流水
	//todo:用于解决操作员发行卡失败后,必须回收卡才能继续处理的问题
	ret=DB_t_authcard_read_by_opercode_and_status(opercode,"1",&tAuthCard);
	if(ret!=DB_NOTFOUND)
	{
		if(0==ret)
		{
			if(strcmp(trans.cardphyid,tAuthCard.cardphyid)==0)
			{
				out_pack->lvol0 = tAuthCard.cardno;
				out_pack->lvol1 = tAuthCard.privilege;
				des2src(out_pack->sdate2,tAuthCard.expiredate);
				des2src(out_pack->scust_limit,tAuthCard.opercode);
				des2src(out_pack->sbank_acc,work_key);
				des2src(out_pack->scust_limit2,tOper.opername);
				PutRow(handle,out_pack,pRetCode,szMsg);
				return 0;
			}
			else
				return E_AUTHCARD_EXIST;
		}
		else
			return E_DB_AUTHCARD_R;
	}
//		//记录存在
//		if(tAuthCard.cardstatus[CARDSTAT_TYPE_LOST]=='1')
//		{
//			//修改原来卡为注销状态
//			tAuthCard.status[0]==STATUS_DELETE;
//			des2src(tAuthCard.closedate,ats.trans.transdate);
//			ret=DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
//			if(ret)
//			{
//					return E_DB_AUTHCARD_U;
//			}
//		}
		//return E_OPER_ALREADY_HAS_AUTHCARD;
//	}
	ret=GetSysParaVal(GLOBE_999_DEVAUTHKEY,work_key);
	if( ret)
	{
		return ret;
	}

	ret = getNewUniqNo(KEYTYPE_CARDNO,&(trans.cardno));
	if(ret)
	{
		return ret;
	}

	tAuthCard.cardno = trans.cardno;

	des2src(tAuthCard.opendate,ats.trans.transdate);
	des2src(tAuthCard.opercode,opercode);
	des2src(tAuthCard.cardphyid,trans.cardphyid);
	des2src(tAuthCard.showcardno,trans.showcardno);
	des2src(tAuthCard.expiredate,rPack->sdate2);
	tAuthCard.privilege = rPack->lvol0;
	tAuthCard.status[0]=STATUS_NORMAL;
	tAuthCard.lossflag[0]='0';
	// TODO : 检查物理卡号是否已经存在
	ret = DB_t_authcard_add(&tAuthCard);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_AUTHCARD_E;
		else
			return E_DB_AUTHCARD_I;
	}
	out_pack->lvol0 = tAuthCard.cardno;
	out_pack->lvol1 = tAuthCard.privilege;
	des2src(out_pack->sdate2,tAuthCard.expiredate);
	des2src(out_pack->scust_limit,tAuthCard.opercode);
	des2src(out_pack->sbank_acc,work_key);
	des2src(out_pack->scust_limit2,tOper.opername);
	PutRow(handle,out_pack,pRetCode,szMsg);
	ret = DB_t_operator_read_lock_by_c0_and_opercode(opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_NOTEXIST_OPER;
		else
			return E_DB_OPERATOR_R;
	}
	tOper.cardno=tAuthCard.cardno;
	ret=DB_t_operator_update_lock_by_c0(&tOper);
	if(ret)
	{
		return E_DB_OPERATOR_U;
	}
	/*
	int cardtype=0;
	ret=UseShowCardNo(trans.opercode,tAuthCard.showcardno,cardtype);
	if(ret)
	{
		return ret;
	}
	if(cardtype!=CARDTYPE_AUTH)
	{	
		return E_CARDTYPE_NOT_AUTHCARD;
	}
	T_t_carddtl carddtl;
	memset(&carddtl,0,sizeof(carddtl));
	
	des2src(carddtl.accdate,ats.sysPara.sSettleDate);
	des2src(carddtl.acctime,trans.acctime);
	carddtl.termid=trans.termid;
	carddtl.termseqno=trans.termseqno;
	des2src(carddtl.opercode,trans.opercode);
	carddtl.cardtype=CARDTYPE_AUTH;
	carddtl.usetype=CARDUSETYPE_USE;
	carddtl.inoutflag=INOUTFLAG_OUT;
	carddtl.transcnt=1;
	strcpy(carddtl.summary,"发行授权卡");	
	des2src(carddtl.cardphyid,tAuthCard.cardphyid);
	des2src(carddtl.showcardno,tAuthCard.showcardno);
	ret=DB_t_carddtl_add(&carddtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return E_DB_CARDDTL_E;
		else
			return E_DB_CARDDTL_I;
	}
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	transdtl.revflag[0]='0';
	transdtl.errcode=0;
	transdtl.custid=trans.custid;
	strcpy(transdtl.custname,trans.custname);
	strcpy(transdtl.transdate,trans.transdate);
	strcpy(transdtl.transtime,trans.transtime);
	strcpy(transdtl.accdate,ats.sysPara.sSettleDate);
	strcpy(transdtl.acctime,trans.acctime);
	transdtl.termid=trans.termid;
	transdtl.termseqno=trans.termseqno;
	transdtl.transcode=trans.transcode;
	des2src(transdtl.opercode,trans.opercode);
	transdtl.cardno=trans.cardno;
	des2src(transdtl.custname,tOper.opername);
	ret=DB_t_transdtl_add(&transdtl);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	*/
	return 0;
}

