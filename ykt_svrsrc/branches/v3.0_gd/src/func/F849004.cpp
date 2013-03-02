/* --------------------------------------------
 * ��������: F49004.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:POS ������ֵ����
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
static int doReverse(char* oldaccdate,int oldtermid,int oldtermseqno)
{
	//���Ҳ���Ա��ˮ
	int ret=0;
	T_t_card tCard;
	
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	T_t_transdtl transdtl;
	memset(&transdtl,0,sizeof(transdtl));
	ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&transdtl);
	if(ret)
	{
	    if(DB_NOTFOUND==ret)
	        return E_DB_TRANSDTL_N;
	    else
	        return E_DB_TRANSDTL_R;
	}	
	if(trans.cardno!=transdtl.cardno)
	{
		DB_t_transdtl_free_lock_by_c0();
		return E_CARDNO_DIFFER;
	}
	if(transdtl.transcode!=TC_POSDEPOSIT&&
		transdtl.transcode!=TC_POSDEPOSITREV&&
		transdtl.transcode!=TC_SHOPPOSDEPOSIT&&
		transdtl.transcode!=TC_SHOPPOSDEPOSITREV&&
		transdtl.transcode!=TC_CARDDEPOSIT&&
		transdtl.transcode!=TC_CARDDEPOSITREV)
	{
		DB_t_transdtl_free_lock_by_c0();
		return E_TRANSCODE_NOT_SAVING;
	}
	if(transdtl.revflag[0]=='1')
	{
		DB_t_transdtl_free_lock_by_c0();
		//pAccTrans->remark="�ý����ѳ���";
		//strcpy(cardphyid,tCard.cardphyid);
		return 0;
	}
	transdtl.revflag[0]='1';
	ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
	    return E_DB_TRANSDTL_U;
	}	
//	ret=UpdateCardBitmap(transdtl.cardno,transdtl.cardcnt,CARDBITMAPTYPE_INCREV,0);
//	if(ret)
//		return ret;
	T_t_transdtl transdtlrev;
	memset(&transdtlrev,0,sizeof(transdtlrev));

	des2src(transdtlrev.transdate,trans.transdate);
	des2src(transdtlrev.transtime,trans.transtime);
	des2src(transdtlrev.accdate,pAccTrans->trans.accdate);
	strcpy(transdtlrev.acctime,trans.acctime);
	des2src(transdtlrev.devphyid,transdtl.devphyid);
	transdtlrev.devseqno=transdtl.devseqno+1;
	transdtlrev.termid=trans.termid;
	transdtlrev.termseqno=trans.termseqno;
	transdtlrev.transcode=trans.transcode;
	transdtlrev.paytype=0;
	transdtlrev.sysid=transdtl.sysid;
	transdtlrev.cardno=transdtl.cardno;
	transdtlrev.purseno=transdtl.purseno;
	transdtlrev.transflag =transdtl.transflag;
	transdtlrev.cardcnt=transdtl.cardcnt;
	transdtlrev.cardbefbal=transdtl.cardbefbal;
	transdtlrev.cardaftbal=transdtl.cardbefbal;
	transdtlrev.amount = -transdtl.amount;
	transdtlrev.managefee= -transdtl.managefee;
	transdtlrev.custid=transdtl.custid;
	des2src(transdtlrev.custname,transdtl.custname);
	transdtlrev.showcardno=transdtl.showcardno;
	des2src(transdtlrev.stuempno,transdtl.stuempno);
	des2src(transdtlrev.opercode,trans.opercode);
	transdtlrev.status[0]=DTLSTATUS_SUCCESS;
	transdtlrev.errcode=0;
	ret=DB_t_transdtl_add(&transdtlrev);
	if(ret)
	{
	  if(DB_REPEAT==ret)
	    return E_DB_TRANSDTL_E;
	  else
	    return E_DB_TRANSDTL_I;
	}		
	ret=pAccTrans->doTodayReverseTrans(oldaccdate,oldtermid,oldtermseqno);	
	if(ret)
		return ret;
	trans.cardaftbal=transdtlrev.cardaftbal;
	trans.transamt=transdtlrev.amount;
	return 0;
}
int F849004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->CheckCfgUpdate();
	if(ret)
		return ret;
	trans.cardno=rPack->lvol5;
	int lastdevseqno=rPack->lvol3;
	char devphyid[31]="";
	des2src(devphyid,rPack->sphone3);
	ret=GetDevIdByDevPhyId(&(trans.termid),devphyid);
	if(ret)
	{
		return ret;
	}

	T_t_transdtl transdtl;

	memset(&transdtl,0,sizeof(transdtl));
	ret=DB_t_transdtl_read_by_accdate_and_termid_and_devseqno(trans.accdate,trans.termid,lastdevseqno,&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"transdate[%s]devphyid[%s]devseqno[%d]",trans.accdate,devphyid,lastdevseqno);
		if(DB_NOTFOUND==ret)
			return 0;
		else
			return E_DB_TRANSDTL_R;
	}
	if(transdtl.revflag[0]=='1')
	{
		return 0;
	}
 	ret=pAccTrans->GetTermSeqno();
	if(ret)
		return ret;
	
	if(transdtl.transcode==TC_POSDEPOSIT)
		pAccTrans->trans.transcode=TC_POSDEPOSITREV;
	else if(transdtl.transcode==TC_SHOPPOSDEPOSIT)
		pAccTrans->trans.transcode=TC_SHOPPOSDEPOSITREV;
	else
		return E_TRANSCODE_NOT_SAVING;
	ret=doReverse(transdtl.accdate,transdtl.termid,transdtl.termseqno);
	if(ret)
		return ret;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);
	
	outPack->lvol5 = transdtl.cardno;
	outPack->lvol10 = (int)D4U5(transdtl.cardaftbal*100,0);
	outPack->lcert_code = transdtl.termseqno;
	
//	outPack->lvol0=pAccTrans->trans.cardno;
//	outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
//	des2src(outPack->sdate3,pAccTrans->sysPara.sSettleDate);
//	des2src(outPack->semp,pAccTrans->trans.opercode);
//	outPack->lserial1=pAccTrans->trans.termseqno;
	sprintf(outPack->vsmess,"�������%.2lf �����%.2lf",trans.transamt,trans.cardaftbal);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
} 
