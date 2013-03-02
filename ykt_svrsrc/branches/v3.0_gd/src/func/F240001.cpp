/* --------------------------------------------
 * ��������: F240001.sqc
 * ��������: 2007-07-21
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: Ȧ��ת����ʽ����
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


int F240001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->trans.transcode=TC_BANKTRANS;
	TRANS& trans=pAccTrans->trans;
	trans.termid=atoi(rPack->sorder2);
	int i=0;
	char sMsg[255]="";
	char sDebugMsg[255]="";

	T_t_account	tAccount;		//�ʻ���
	T_t_transdtl  transdtl;		//��������ˮ��
	T_t_card		card;

	memset(&tAccount,0,sizeof(tAccount));
	memset(&transdtl,0,sizeof(transdtl));
	memset(&card,0,sizeof(card));


	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);


	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_DAMT2,F_LVOL1,F_LVOL2,F_SDATE0,0);

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
	trans.cardno=atoi(rPack->sserial0);
	ret=DB_t_card_read_by_cardno(trans.cardno,&card);
	if(ret)
	{
		writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}
	if(card.status[0]!=STATUS_NORMAL)
	{
		return ERRINFO(E_CARD_LOGOUT,trans.cardno);
	}	
	if('1'==card.frozeflag[0])
	{
		return ERRINFO(E_CARD_FREEZE,trans.cardno);
	}
	if('1'==card.lossflag[0])
	{
		return ERRINFO(E_CARD_LOST,trans.cardno);
	}	
	if('1'==card.badflag[0])
	{
		return ERRINFO(E_CARD_BADRECORD,trans.cardno);
	}	
	if('1'==card.lockflag[0])
	{
		return ERRINFO(E_CARDNO_LOCKED,trans.cardno);
	}	
	trans.inputamt = rPack->lvol5/100.0;
	trans.unusedamt=trans.inputamt;
	//��ʼ�����ˮ����
	//��ˮ��
	//ģʽ�޸�Ϊ���������ʲ�����ˮ�ţ���¼��ˮ�ṹ����ʽ����ֻ�޸ĸ�
	//��ˮ�ĳ���ֵ�Լ���ˮ״̬
	pAccTrans->trans.termseqno=rPack->lvol7;
	ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(pAccTrans->trans.accdate,trans.termid,pAccTrans->trans.termseqno, &transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_tif_transdtl_read_lock_by_cur_and_serial_no error,error code=[%d],serial_no=[%d]",ret,rPack->lvol7);
		if(DB_NOTFOUND==ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_R;
	}
	ret=pAccTrans->InitTrans();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		return ret;
	}
	//�ж�ת�ʽ���Ƿ񳬳�Ǯ������޶�
	ret=DB_t_account_read_by_accno(card.accno,&tAccount);
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		writelog(LOG_ERR,"DB_t_account_read_by_accno ret[%d]cardaccno[%s]",ret,card.accno);
		if(DB_NOTFOUND==ret)
		{
			return ERRINFO(E_NOTEXIST_CARDACCNO,card.accno);
		}
		else
		{
			return E_DB_ACCOUNT_R;
		}
	}
//	if(amtcmp(tAccount.availbal+trans.inputamt,tAccount.cardmaxbal)>0)
//	{
//		DB_t_transdtl_free_lock_by_c0();
//		return E_TRANS_TRANSMONEY_OUTRANGE;
//	}
	des2src(trans.cardaccno,tAccount.accno);			//�����ʻ�,�ֿ����˻�
	des2src(trans.draccno,rPack->sstation0);				//�跽�ʺţ���ǰ�û��ϴ�
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
		return ret;
	}
	ret=pAccTrans->doMainTrans();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		return ret;
	}
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		DB_t_transdtl_free_lock_by_c0();
		return ret;
	}
	//���������ˮ����
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_transdtl_update_lock_by_c0 error,error code=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	writelog(LOG_INFO,"ת�˽��%.2lf ת��ǰ�����%.2lf ת�ʺ����%.2lf ",transdtl.amount,trans.cardbefbal,trans.cardaftbal);

	out_pack->damt0=transdtl.cardaftbal;
	out_pack->damt1=transdtl.amount;
	out_pack->damt2=transdtl.managefee;	
	out_pack->lvol2=D4U5(transdtl.cardaftbal*100,0);
	out_pack->lvol1=transdtl.termseqno;
	des2src(out_pack->sdate0,pAccTrans->trans.accdate);

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

