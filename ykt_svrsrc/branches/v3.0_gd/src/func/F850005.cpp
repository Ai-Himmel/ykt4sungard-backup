/* ----------------------------------------------------------
 * 创建日期：2009-08-18
 * 程序作者：闻剑
 * 版本信息：3.0.0.0
 * 程序功能：支付
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "errdef.h"
#include "pubdb.h"
#include "busqc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "acctrans.h"
#include "tcp.h"
#include "payment.h"
//查询第三方账户状态
static int QryAcc(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
   	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,F_DAMT0,F_DAMT1,F_DAMT2,F_SDATE1,F_LWITHDRAW_FLAG,
		   F_SBANKNAME,F_SADDR,F_SNAME2,F_SPHONE3,F_VSMESS,0);

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.cardno=rPack->lvol0;
	
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));

	T_t_account tAccount;
	memset(&tAccount,0,sizeof(tAccount));
	
	ret=pAccTrans->CheckAcc(&tCard,&tAccount);
	if(ret)
	{
		writelog(LOG_INFO,"检查状态失败");
		return ret;
	}
	if(strlen(rPack->stx_pwd))
	{
		ret=check_card_pwd_by_card(trans.cardno,rPack->stx_pwd);
		if(ret)
			return ret;
	}	
	int paycode=rPack->lcert_code;
	CPaymentBase *payment;
	payment = CPaymentBase::find_payment(paycode);
	if(NULL == payment)
	{
		return E_TRANS_FUNC_NONSUPPORT;
	}
	ret = payment->init(handle,&aPack,rPack);
	if(ret)
	{
		writelog(LOG_ERR,"trade[%d],ret[%d]",paycode,ret);		
		return	ret;
	}
	if(payment->payment_.onlinepay>0)
	{
		ret = payment->qry_acc(handle,rPack,outPack);
		if(ret)
		{
			writelog(LOG_ERR,"查询收款方账户信息错误trade[%d],ret[%d]",paycode,ret);
			return ret;
		}
	}
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}
static int TestTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,F_SDATE0,F_SPHONE3,F_SADDR,F_LSAFE_LEVEL2,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	trans.transcode=TC_CARDPAYMENT;
	des2src(trans.opercode,rPack->semp);
	trans.termid=rPack->lwithdraw_flag;
	ret=pAccTrans->InitTrans();
	if(ret)
		return ret;	
	
	int paycode=rPack->lcert_code;

	trans.cardno=rPack->lvol0;
	if(trans.cardno<1)
	{
		return E_INPUTNULL_CARDNO;
	}
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.purseno=PURSE_NO_ONE;
	trans.paycnt=rPack->lvol6+1;
	des2src(trans.cardphyid,rPack->sstation1);

	trans.inputamt= D4U5(rPack->lvol1/100.0);	
	trans.unusedamt = trans.inputamt;
	trans.cardbefbal=rPack->lvol7/100.0;
	trans.cardaftbal=trans.cardbefbal - trans.inputamt;
	if(amtcmp(trans.inputamt,0)<=0)
	{
		ERRTIP("交易金额不能为0");
		return E_COMMON_ERR;
	}
	if(amtcmp(trans.inputamt,trans.cardbefbal)>0)
	{
		return ERRINFO(E_CARD_BALANCE_SHORTAGE,trans.cardbefbal);
	}	
	T_t_card  tCard;
	memset(&tCard,0,sizeof(tCard));

	T_t_account tAccount;
	memset(&tAccount,0,sizeof(tAccount));
	
	ret=pAccTrans->CheckAcc(&tCard,&tAccount);
	if(ret)
	{
		writelog(LOG_INFO,"检查状态失败");
		return ret;
	}
	if(tCard.custid<1)
	{
		return E_NOTEXIST_CUSTOMER;
	}
	if(strlen(rPack->stx_pwd))
	{
		ret=check_card_pwd_by_card(trans.cardno,rPack->stx_pwd);
		if(ret)
			return ret;
	}	
	ret=GetCustBaseInfoByCustID(trans.custid,trans.custname,trans.stuempno,trans.remark);
	if(ret)
		return ret;
	CPaymentBase *payment;
	payment = CPaymentBase::find_payment(paycode);
	if(NULL == payment)
	{
		return E_TRANS_FUNC_NONSUPPORT;
	}
	ret = payment->init(handle,&aPack,rPack);
	if(ret)
	{
		writelog(LOG_ERR,"trade[%d],ret[%d]",paycode,ret);		
		return	ret;
	}
	int waterflag=0;
	double waterbefbal=0;
	double wateraftbal=0;
	int paytype=paycode/1000;
	if(paytype==1)//水控
	{
		waterflag=1;
	}
	if(2==paytype)
	{
		//如果是网络收费则核对支付码及支付名称是否相同
		trim(rPack->snote);
		if(strcmp(payment->payment_.summary,rPack->snote)!=0)
		{
			ERRTIP("网络收费支付名称配置错误");
			return E_COMMON_ERR;
		}
	}
	if(payment->payment_.onlinepay>0&&payment->payment_.paychkflag>0)
	{
		ret=payment->qry_acc(handle,rPack,outPack);
		if(ret)
			return ret;
	}
	if(waterflag)
	{
		if(strlen(trans.opercode)<1)
		{
			switch(rPack->lvol1)
			{
				case 500:
				case 1000:
				case 1500:
				case 2000:
					break;
				default:
				  ERRTIP("交易金额只能为5、10、15、20元");
				  return E_COMMON_ERR;
			}
		}
		waterbefbal = rPack->lsafe_level/100.0;
		wateraftbal = D4U5(waterbefbal+trans.inputamt);
		double CardMaxBal=0;
		ret=GetPurseMaxBal(PURSE_NO_TWO,CardMaxBal);
		if(ret)
			return ret;
		if(amtcmp(wateraftbal,CardMaxBal)>0)
			return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
		if(1061==paycode)
		{
			int price1=0;
			int price2=0;
			int price3=0;
			ret=GetWaterPrice(price1,price2,price3);
			if(ret)
			{
				writelog(LOG_ERR,"读水价失败ret=%d",ret);
				return ret;
			}
			outPack->lvol10=price1;
			outPack->lvol11=price2;
			outPack->lvol12=price3;
		}
	}
	// 保持第三方账号
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	transdtl.exttype = paycode;
	if(waterflag)
	{
		sprintf(transdtl.extdata,"%.2lf",wateraftbal);	
	}
	else
	{
		des2src(transdtl.extdata,rPack->sbank_acc);
	}
	ret = pAccTrans->GenTransdtl(&transdtl,DTLSTATUS_INIT);
	if(ret)
	{
		writelog(LOG_ERR,"GenTransdtl ret=%d",ret);
		return ret;
	}
	ret=db_commit();
	if(ret)
	{
		return ret;
	}	
	trans.cardaftbal=trans.cardbefbal;
	ret=pAccTrans->doTrans();
	if(ret)
	{
		writelog(LOG_ERR,"doTrans err=%d",ret);
		return ret;
	}
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		writelog(LOG_ERR,"doTransEnd err=%d",ret);
		return ret;
	}
	if(amtcmp(trans.cardaftbal,transdtl.cardaftbal)!=0)
	{
		ERRTIP("卡余额计算有误");
		return E_COMMON_ERR;
	}
	ret=db_rollback();
	if(ret)
	{
		writelog(LOG_ERR,"db_rollback err");
		return ret;
	}
	// 输出参数
	outPack->lvol0=tCard.cardno;
	outPack->lvol1=D4U5(trans.inputamt*100,0);
	outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
	outPack->lsafe_level2=D4U5(wateraftbal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,trans.refno);	
    des2src(outPack->saddr,trans.cardpwd);	//mac
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

static int NormalTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL8,F_LVOL10,F_LVOL11,F_LVOL12,F_SDATE0,F_SPHONE3,F_SADDR,F_LSAFE_LEVEL2,
		F_SDATE3,F_STIME3,F_SEMP,F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,0);

	des2src(trans.refno,rPack->sphone3);		//交易参考号
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
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_R;
	}
	if(strncmp(tRefno.mac,rPack->saddr,8)!=0)
	{
		ERRTIP("交易参考号MAC校验错误");
		return E_COMMON_ERR;
	}
	if(RS_FAIL==tRefno.status)
	{
		ERRTIP("交易已失败");
		return E_COMMON_ERR;
	}
	T_t_transdtl transdtl;	
	memset(&transdtl,0,sizeof(transdtl));
	ret=DB_t_transdtl_read_by_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_TRANSDTL;
		else
			return E_DB_TRANSDTL_R;
	}
	if(RS_SUCC==tRefno.status)
	{
		outPack->lvol0=transdtl.cardno;
		outPack->lvol1=D4U5(transdtl.amount*100,0);
		outPack->lvol8=D4U5(transdtl.cardaftbal*100,0);
		double wateraftbal= atof(transdtl.extdata);
		outPack->lsafe_level2=D4U5(wateraftbal*100,0);
		des2src(outPack->sdate3,transdtl.transdate);
		des2src(outPack->stime3,transdtl.transtime);
		des2src(outPack->semp,transdtl.opercode);
		outPack->lwithdraw_flag=transdtl.termid;
		outPack->lserial1=transdtl.termseqno;
		des2src(outPack->sphone3,transdtl.refno);	
		PutRow(handle,outPack,pRetCode,szMsg);
		return 0;
	}

	if(transdtl.status[0]!=DTLSTATUS_INIT)
	{
		ERRTIP("交易流水表状态错误");
		return E_COMMON_ERR;
	}
	des2src(trans.opercode,transdtl.opercode);
	trans.termid=transdtl.termid;
	trans.termseqno=transdtl.termseqno;
	trans.cardflag=1;
	trans.usecardflag=1;	
	trans.transcode=transdtl.transcode;
	trans.cardno=transdtl.cardno;	
	trans.purseno=transdtl.purseno;
	trans.paycnt=transdtl.cardcnt;
	trans.cardbefbal=transdtl.cardbefbal;
	trans.cardaftbal=transdtl.cardbefbal;
	trans.inputamt= transdtl.amount;	
	trans.unusedamt = trans.inputamt;

	CPaymentBase *payment;
	payment = CPaymentBase::find_payment(transdtl.exttype);
	if(NULL == payment)
	{
		return E_TRANS_FUNC_NONSUPPORT;
	}
	rPack->lcert_code = transdtl.exttype;
	ret = payment->init(handle,&aPack,rPack);
	if(ret)
	{
		writelog(LOG_ERR,"trade[%d],ret[%d]",transdtl.exttype,ret);		
		return	ret;
	}
	pAccTrans->SetSummary(payment->payment_.summary);
	
	T_t_card tCard;

	memset(&tCard,0,sizeof(tCard));

	ret=DB_t_card_read_by_cardno(trans.cardno,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
		else
			return E_DB_CARD_R;
	}
	strcpy(trans.cardaccno,tCard.accno);
	trans.feetype=tCard.feetype;
	trans.custid=tCard.custid;
	
	ret=pAccTrans->doTrans();
	if(ret)
		return ret;
	ret=pAccTrans->doTransEnd();
	if(ret)
		return ret;
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_update_by_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_U;
	}
	tRefno.status=RS_SUCC;
	strcpy(tRefno.lastsaved,trans.sysdatetime);
	ret=DB_t_refno_update_by_refno(tRefno.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_U;
	}
	outPack->lvol0=tCard.cardno;
	outPack->lvol1=D4U5(trans.inputamt*100,0);
	outPack->lvol8=D4U5(trans.cardaftbal*100,0);	
	double wateraftbal= atof(transdtl.extdata);
	outPack->lsafe_level2=D4U5(wateraftbal*100,0);
	des2src(outPack->sdate3,trans.accdate);
	des2src(outPack->stime3,trans.acctime);
	des2src(outPack->semp,trans.opercode);
	outPack->lwithdraw_flag=trans.termid;
	outPack->lserial1=trans.termseqno;
	des2src(outPack->sphone3,trans.refno);
	sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
	des2src(outPack->vsmess,trans.remark);
	PutRow(handle,outPack,pRetCode,szMsg);
	
//	AnswerData(handle,*pRetCode,szMsg);
	//进行第三方支付
	if(payment->payment_.onlinepay)
	{
		ret=db_commit();
		if(ret)
		{
			writelog(LOG_ERR,"数据库事务提交失败 ret=%d",ret);
			return E_DB_COMMIT;
		}
		ret=payment->transfer(handle,rPack,outPack);
		if(ret)
		{
			writelog(LOG_ERR,"与第三方系统交易失败 ret=%d",ret);
		}
	}
	return 0;
}
//写卡异常处理
static int WriteCardExcept(ST_PACK *rPack)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	des2src(trans.refno,rPack->sphone3);		//交易参考号
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
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_R;
	}
	if(strncmp(tRefno.mac,rPack->saddr,8)!=0)
	{
		ERRTIP("交易参考号MAC校验错误");
		return E_COMMON_ERR;
	}
	T_t_transdtl transdtl;

	memset(&transdtl,0,sizeof(transdtl));

	ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(tRefno.accdate,tRefno.termid,tRefno.termseqno,&transdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_U;
	}
	if(transdtl.status[0]!=DTLSTATUS_SUCCESS)
		transdtl.status[0]=DTLSTATUS_FAIL;
	transdtl.errcode = 2;
	strcpy(transdtl.remark,"中途拔卡,写卡失败");
	ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
		return E_DB_TRANSDTL_U;
	}
	return 0;
}

static int ConfirmTrans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
    CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
    T_t_transdtl dtl;
    int ret;
    ST_CPACK aPack;
    ST_PACK *out_pack=&(aPack.pack);

    memset(&dtl,0,sizeof dtl);
    T_t_refno tRefno;
	memset(&tRefno,0,sizeof(tRefno));
	ret=DB_t_refno_read_by_refno(rPack->sphone3,&tRefno);
    writelog(LOG_DEBUG,"confirm refno[%s]",rPack->sphone3);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_REFNO_R;
	}
	if(RS_SUCC==tRefno.status)
	{
		TIPINFO("交易已确认");
		return 0;
	}
    tRefno.status=RS_SUCC;
	strcpy(tRefno.lastsaved,trans.sysdatetime);
	ret=DB_t_refno_update_by_refno(tRefno.refno,&tRefno);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_U;
	}
    
    ret = DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(
        tRefno.accdate,tRefno.termid,tRefno.termseqno,&dtl);
    if(ret)
    {
        if(DB_NOTFOUND == ret)
            return E_DB_TRANSDTL_N;
        return E_DB_TRANSDTL_R;
    }
    dtl.errcode = rPack->lvol0;
    des2src(dtl.remark,rPack->vsmess);
    des2src(dtl.voucherno,rPack->sphone2);
    writelog(LOG_ERR,"begin DB_t_transdtl_update_lock_by_c0");
    ret = DB_t_transdtl_update_lock_by_c0(&dtl);
    if(ret)
    {
        writelog(LOG_ERR,"更新流水表失败,ret[%d]",ret);
        return E_DB_TRANSDTL_U;
    }
    writelog(LOG_ERR,"end DB_t_transdtl_update_lock_by_c0");
    
    
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL5,F_DAMT0,F_DAMT1,F_DAMT2,F_SNAME2,F_SDATE1,0);
    out_pack->lvol0 = dtl.termseqno;
    out_pack->damt0 = dtl.cardaftbal;
    out_pack->damt1 = dtl.amount;
    out_pack->damt2 = dtl.cardbefbal;
    out_pack->lvol5 = D2I(dtl.cardaftbal * 100.0);
    des2src(out_pack->sname2,dtl.refno);
    des2src(out_pack->sdate1,dtl.accdate);
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
}

int F850005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	//支付交易
	switch(rPack->lbank_acc_type)
	{
			//试入账
		case 1:
			ret=TestTrans(handle,rPack,pRetCode,szMsg);
			break;
			//正式入账
		case 2:
			ret=NormalTrans(handle,rPack,pRetCode,szMsg);
			break;
		case 3://写卡失败
			ret=WriteCardExcept(rPack);
			break;
        case 255:// 前置机转账成功确认
            ret = ConfirmTrans(handle,rPack,pRetCode,szMsg);
            break;
		default:
			//查询账户
			ret=QryAcc(handle,rPack,pRetCode,szMsg);
			break;
	}
	return ret;
}

