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

static int doTrans(int tradecode,T_t_transdtl  *transdtl,char *errmsg)
{
	int ret = 0;
	int request_type = 2401;
	int drtp_branch  = 0;
	int base_funcno = 0;
	int bcc_timeout = 0;
	char bankcode[3] = "";
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = request_type;
	
	SetHeadCol(&sPack,F_LCERT_CODE,F_SCUST_AUTH,F_LVOL0,F_LVOL1,F_SDATE0,
		F_SHOLDER_AC_NO,F_SPHONE,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SCUST_AUTH2,F_DAMT0,0);      

	T_t_bankcard bankcard;
	memset(&bankcard,0,sizeof bankcard);
	ret = DB_t_bankcard_read_by_custid_and_bankcardno(transdtl->custid,transdtl->extdata, &bankcard);
	if(ret)
	{
		return E_DB_BANKCARD_R;
	}
	des2src(bankcode,bankcard.bankcode);

	T_t_cfgbank cfgbank;
	memset(&cfgbank,0,sizeof cfgbank);
	ret = DB_t_cfgbank_read_by_bankcode(bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}

	T_t_customer customer;
	memset(&customer,0,sizeof customer);
	ret = DB_t_customer_read_by_custid(transdtl->custid, &customer);
	if(ret)
	{
		return E_DB_CUSTOMER_R;
	}
	
	drtp_branch = cfgbank.bccdrtpno;								// drtp ���
	base_funcno = cfgbank.bccfuncno;							// ǰ�������ܺ�
	bcc_timeout = cfgbank.bcctimeout;								// ǰ�ó�ʱʱ��

	sPack.pack.lcert_code = tradecode;								// ������
	des2src(sPack.pack.scust_auth,cfgbank.bankip);					// ����ip
	sPack.pack.lvol0 = cfgbank.bankport;							// ���ж˿�
	sPack.pack.lvol1 = cfgbank.banktimeout*1000;					// ���г�ʱʱ��

	des2src(sPack.pack.sdate0,transdtl->transdate);					// ��������
	des2src(sPack.pack.sholder_ac_no,transdtl->refno);				// һ��ͨ���ײο���
	des2src(sPack.pack.sphone,transdtl->stuempno);					// ѧ����
	des2src(sPack.pack.scust_limit,customer.custname);				// ����
	des2src(sPack.pack.scust_auth2,customer.idno);					// ���֤��
	des2src(sPack.pack.scust_limit2,transdtl->extdata);				// ���п���
	sPack.pack.damt0 = transdtl->amount;							// ���׽��
	if(bcc_timeout<5)
	   bcc_timeout=5;
	
	ret = ExtCall(0, drtp_branch, base_funcno, 0, bcc_timeout, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		writelog(LOG_ERR,"extcall 2401 ret[%d],retcode[%d] timeout[%d] ",ret,aPack.head.retCode,bcc_timeout);
		if (ret < 0)				// ͨѶ����Ҫ������
		{
			strcpy(errmsg,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
			return E_BCC_NETWORK;
		}
		else						// �յ�ǰ�÷��صĴ���
		{
			trim(aPack.pack.vsmess);
			strcpy(errmsg,aPack.pack.vsmess);
			return E_COMMON_ERR;
		}
	}
	if(aPack.pack.lvol1 != 1)		// ǰ�ý������
	{	
		strcpy(errmsg,"�����������ݴ���");
		return E_BCC_NETWORK;
	}
	return 0;
}


int F240021(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int ret1 = 0;
	int reverse_flag = 0;
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
	trans.cardno=rPack->lvol0;
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
		return E_COMMON_ERR;
	}

	ret = DB_t_transdtl_read_by_refno(refno.refno, &transdtl);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_TRANSDTL_N;
		else
			return E_DB_TRANSDTL_R;
	}
	if(transdtl.status[0] != DTLSTATUS_INIT)
	{
		if(transdtl.status[0] == DTLSTATUS_SUCCESS)					// �Ѿ��ɹ���
		{
			out_pack->damt0=transdtl.cardaftbal;
			out_pack->damt1=transdtl.amount;
			out_pack->damt2=transdtl.managefee;	
			out_pack->lvol2=D2I(transdtl.cardaftbal*100);
			return 0;
		}
		else
		{
			ERRTIP("��ˮ����ʧ��");
			return E_COMMON_ERR;
		}
	}
	
	ret = doTrans(TRADE_TRANS,&transdtl,szMsg);
	if(ret)
	{
		if(ret != E_BCC_NETWORK)
		{
			transdtl.errcode = ret;
			transdtl.status[0] = DTLSTATUS_FAIL;
			des2src(transdtl.remark,szMsg);
			if(DB_t_transdtl_update_by_refno(refno.refno,&transdtl))
				return E_DB_TRANSDTL_U;
			else
			{			
				db_commit();
				return ret;
			}
		}
		else							// ͨѶ���⣬Ҫ����
		{
			reverse_flag = 1;
			goto L_RET;
		}
	}

	trans.inputamt = transdtl.amount;
	trans.unusedamt=trans.inputamt;
	//��ʼ�����ˮ����
	//��ˮ��
	//ģʽ�޸�Ϊ���������ʲ�����ˮ�ţ���¼��ˮ�ṹ����ʽ����ֻ�޸ĸ�
	//��ˮ�ĳ���ֵ�Լ���ˮ״̬

	writelog(LOG_INFO,"trans sucess");
	ret=pAccTrans->InitTrans();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//�ж�ת�ʽ���Ƿ񳬳�Ǯ������޶�
	ret=DB_t_account_read_by_accno(card.accno,&tAccount);
	if(ret)
	{
		reverse_flag = 1;
		ret = E_DB_ACCOUNT_R;
		goto L_RET;
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
		reverse_flag = 1;
		goto L_RET;
	}
	//writelog(LOG_INFO,"donfeetrans done");
	ret=pAccTrans->doMainTrans();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//writelog(LOG_INFO,"doMainTrans done");
	ret=pAccTrans->doTransEnd();
	if(ret)
	{
		reverse_flag = 1;
		goto L_RET;
	}
	//���������ˮ����
	transdtl.cardaftbal=trans.cardaftbal;
	transdtl.status[0]=DTLSTATUS_SUCCESS;
	

	ret=DB_t_transdtl_update_by_refno(refno.refno,&transdtl);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_transdtl_update_by_refno error,error code=[%d]",ret);
		reverse_flag = 1;
	}
	
L_RET:	
	if(reverse_flag)
	{
		transdtl.status[0] = DTLSTATUS_FAIL;
		ret1 = doTrans(TRADE_REVERSE, &transdtl, szMsg);
		if(ret1)												// ����Ҳʧ���ˣ����˽����ƽ
		{
			transdtl.errcode = ret1;
			des2src(transdtl.remark,szMsg);
			strcat(transdtl.remark," ����ʧ��");
			if(DB_t_transdtl_update_by_refno(refno.refno,&transdtl))
				return E_DB_TRANSDTL_U;
			else
			{			
				db_commit();
				return ret1;
			}
		}
		///////////////�����ɹ��ˣ���ʾ�ղ�Ҫ������ԭ��
		transdtl.errcode = ret;
		if(DB_t_transdtl_update_by_refno(refno.refno,&transdtl))
			return E_DB_TRANSDTL_U;
		else
		{			
			db_commit();
			return ret;
		}
	}	
	
	out_pack->damt0=transdtl.cardaftbal;
	out_pack->damt1=transdtl.amount;
	out_pack->damt2=transdtl.managefee;	
	out_pack->lvol2=D2I(transdtl.cardaftbal*100);
	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

