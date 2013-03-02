/* --------------------------------------------
 * ��������: F240021.cpp
 * ��������: 2009-08-07
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת��
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "transcode.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include "bupub.h"
#include "svrlink.h"

int F240021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->trans.transcode=TC_BANKTRANS;
	TRANS& trans=pAccTrans->trans;
	trans.termid=rPack->lcert_code;

	T_t_account	tAccount;		//�ʻ���
	T_t_transdtl  transdtl;		//��������ˮ��
	T_t_card	card;
	T_t_refno refno;

	memset(&tAccount,0,sizeof(tAccount));
	memset(&transdtl,0,sizeof(transdtl));
	memset(&card,0,sizeof(card));
	memset(&refno,0,sizeof(refno));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,F_SNAME,F_SNAME2,F_LVOL0,F_LVOL5,F_LCERT_CODE,0);

	//�ж��Ƿ������ս���״̬
	/*
 	ret=GetSysParaVal(GLOBE_FLAG_BALANCE,buffer);
	if(ret)
	{
		writelog(LOG_ERR,"GetSysParaVal error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	else if(strncmp(buffer,"0",1)!=0)
	{
		writelog(LOG_ERR,"System is balance now!");
		return E_TRANS_BANK_SERVICE_NOEXIT;
	}
	*/

	des2src(refno.refno,rPack->sname2);
	ret = DB_t_refno_read_by_refno(refno.refno,&refno);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_REFNO_N;
		else
			return E_DB_REFNO_R;
	}
	if(strncmp(refno.mac,rPack->stx_pwd,8)!=0)
	{
		ERRTIP("���ײο���MACУ�����");
		return E_MAC_FAIL;
	}

	//ret = DB_t_transdtl_read_by_refno(refno.refno, &transdtl);
	ret = DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(refno.accdate,refno.termid,refno.termseqno,&transdtl);
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		if(DB_NOTFOUND == ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_R;
	}
	
	if(transdtl.status[0] != DTLSTATUS_INIT)
	{
		DB_t_transdtl_free_lock_by_c0();
		if(transdtl.status[0] == DTLSTATUS_SUCCESS)					// �Ѿ��ɹ���
		{
			out_pack->damt0=transdtl.cardaftbal;
			out_pack->damt1=transdtl.amount;
			out_pack->damt2=transdtl.managefee;	
			out_pack->lvol2=D2I(transdtl.cardaftbal*100);
			out_pack->lvol1= 1;
			return 0;
		}
		else
		{
			ERRTIP("��ˮ����ʧ��");
			return E_COMMON_ERR;
		}
	}

	// ��ѯ������ˮ
	if(rPack->sstatus0[0] == 'R')
	{
		DB_t_transdtl_free_lock_by_c0();
		des2src(out_pack->sname2,transdtl.refno);
		des2src(out_pack->sname,transdtl.extdata);
		out_pack->lvol0 = transdtl.cardno;
		out_pack->lvol5 = D2I(transdtl.amount*100);
		out_pack->lcert_code = transdtl.termid;
		PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}

	// ����ת�˳�ʱ(״̬4)
	if(rPack->sstation0[0] == 'U')
	{
		DB_t_transdtl_free_lock_by_c0();
		refno.status = RS_YKTREVSUCC;			// ״̬Ϊ4
		ret = DB_t_refno_update_by_refno(refno.refno,&refno);
		if(ret)
			return E_DB_REFNO_U;
		return 0;
	}
	trans.cardno=transdtl.cardno;
	ret=DB_t_card_read_by_cardno(trans.cardno,&card);
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}
	
	trans.inputamt = transdtl.amount;
	trans.unusedamt=trans.inputamt;
	trans.termseqno= transdtl.termseqno;
	//��ʼ�����ˮ����
	//��ˮ��
	//ģʽ�޸�Ϊ���������ʲ�����ˮ�ţ���¼��ˮ�ṹ����ʽ����ֻ�޸ĸ�
	//��ˮ�ĳ���ֵ�Լ���ˮ״̬
	
	ret=pAccTrans->InitTrans();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		goto L_REV;
	}
	//�ж�ת�ʽ���Ƿ񳬳�Ǯ������޶�
	ret=DB_t_account_read_by_accno(card.accno,&tAccount);
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		*pRetCode = E_DB_ACCOUNT_R;
		goto L_REV;
	}
	writelog(LOG_INFO,"name[%s]",tAccount.accname);
//	if(amtcmp(tAccount.availbal+trans.inputamt,tAccount.cardmaxbal)>0)
//	{
//		DB_t_transdtl_free_lock_by_c0();
//		return E_TRANS_TRANSMONEY_OUTRANGE;
//	}
	des2src(trans.cardaccno,tAccount.accno);			//�����ʻ�,�ֿ����˻�
	trans.cardflag=1;
	trans.usecardflag=1;
	trans.feetype=card.feetype;
	trans.cardtype=card.cardtype;
	trans.cardbefbal=transdtl.cardbefbal;
	trans.dpscnt=transdtl.cardcnt;
	trans.cardaftbal=trans.cardbefbal;
	
	ret=pAccTrans->doFeeTrans();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		goto L_REV;
	}
	writelog(LOG_INFO,"donfeetrans done");
	ret=pAccTrans->doMainTrans();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		goto L_REV;
	}
	writelog(LOG_INFO,"doMainTrans done");
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		goto L_REV;
	}
	//���������ˮ����
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.status[0]=DTLSTATUS_SUCCESS;	

	//ret=DB_t_transdtl_update_by_refno(refno.refno,&transdtl);
	ret = DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		*pRetCode = E_DB_TRANSDTL_U;
		writelog(LOG_ERR,"DB_t_transdtl_update_lock_by_c0 error,error code=[%d]",ret);
		goto L_REV;
	}

	refno.status = RS_SUCC;
	ret = DB_t_refno_update_by_refno(refno.refno,&refno);
	if(ret)
	{
		*pRetCode = E_DB_REFNO_U;
		goto L_REV;
	}
	out_pack->damt0=transdtl.cardaftbal;
	out_pack->damt1=transdtl.amount;
	out_pack->damt2=transdtl.managefee;	
	out_pack->lvol2=D2I(transdtl.cardaftbal*100);
	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;

L_REV:

	refno.status = RS_YKTREVSUCC;
	ret = DB_t_refno_update_by_refno(refno.refno,&refno);
	if(ret)
		return E_DB_REFNO_U;
	
	return -1;
		
}

