/* --------------------------------------------
 * ��������: F240024.cpp
 * ��������: 2010-08-04
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���п�����ѯ
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

static int DoQueryBala(int tradecode,ST_PACK *rPack,ST_PACK *out_pack,char *szMsg)
{
	int ret = 0;
	int request_type = 2401;
	int drtp_branch  = 0;
	int base_funcno = 0;
	int bcc_timeout = 0;
	
	int  termid=rPack->lcert_code;
	int cardno=rPack->lvol0;
	int custid = rPack->lvol1;

	char sdatetime[15]="";
		
	T_t_card	tCard;
	T_t_bankcard bankcard;
	T_t_cfgbank cfgbank;
	T_t_customer tCust;
	
	memset(&cfgbank,0,sizeof cfgbank);
	memset(&bankcard,0,sizeof bankcard);
	memset(&tCard,0,sizeof(tCard));
	memset(&tCust,0,sizeof tCust);

	char bankcode[3] = "";
	ST_PACK ArrayPack;			// ���÷��ذ�
	ST_CPACK aPack;				// ����Ӧ���
	ST_CPACK sPack;			 	// ���÷��Ͱ�

	ResetNormalCPack(&aPack, 0, 1);
	memset(&ArrayPack, 0, sizeof(ArrayPack));
	
	ResetNormalCPack(&sPack, 0, 1);
	sPack.head.RequestType = request_type;
	
	SetHeadCol(&sPack,F_LCERT_CODE,F_SCUST_AUTH,F_LVOL0,F_LVOL1,F_LVOL6,F_SDATE0,F_STIME0,
		F_SHOLDER_AC_NO,F_SPHONE,F_SCUST_LIMIT,F_SCUST_LIMIT2,F_SCUST_AUTH2,0);      

	if(custid<1)
	{
		if(cardno>0)
		{
			ret=DB_t_card_read_by_cardno(cardno,&tCard);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
					return E_NOTEXIST_CARDNO;
				else
					return E_DB_CARD_R;
			}
			if(tCard.status[0]!=STATUS_NORMAL)
			{
				return ERRINFO(E_CARD_LOGOUT,cardno);
			}	
			if('1'==tCard.frozeflag[0])
			{
				return ERRINFO(E_CARD_FREEZE,cardno);
			}
			if('1'==tCard.lossflag[0])
			{
				return ERRINFO(E_CARD_LOST,cardno);
			}	
			if('1'==tCard.badflag[0])
			{
				return ERRINFO(E_CARD_BADRECORD,cardno);
			}	
			if('1'==tCard.lockflag[0])
			{
				return ERRINFO(E_CARDNO_LOCKED,cardno);
			}	
			custid=tCard.custid;
		}
		else
		{
			return E_NOTEXIST_CARDNO;			
		}
	}

	if(custid>0)
	{
		ret = DB_t_customer_read_by_custid(custid, &tCust);
		if(ret)
		{
			return E_DB_CUSTOMER_R;
		}
		ret = DB_t_bankcard_read_by_custid(custid, &bankcard);
		if(ret)
		{
			return E_DB_BANKCARD_R;
		}
		des2src(bankcode,bankcard.bankcode);
	}	
	
	ret = DB_t_cfgbank_read_by_bankcode(bankcode,&cfgbank);
	if(ret)
	{
		return E_DB_CFGBANK_R;
	}	
	CAccTrans& ats=CAccTrans::GetInst();
	if(strncmp(ats.trans.acctime,cfgbank.bankstarttime,6) < 0
		|| strncmp(ats.trans.acctime,cfgbank.bankendtime,6) > 0)
	{
		return E_OUT_BANKTIME;
	}
	drtp_branch = cfgbank.bccdrtpno;								// drtp ���
	base_funcno = cfgbank.bccfuncno;								// ǰ�������ܺ�
	bcc_timeout = cfgbank.bcctimeout;								// ǰ�ó�ʱʱ��

	sPack.pack.lcert_code = tradecode;							// ������
	des2src(sPack.pack.scust_auth,cfgbank.bankip);					// ����ip
	sPack.pack.lvol0 = cfgbank.bankport;							// ���ж˿�
	sPack.pack.lvol1 = cfgbank.banktimeout*1000;					// ���г�ʱʱ��

	getsysdatetime(sdatetime);
	memcpy(sPack.pack.sdate0,sdatetime,8);						// ��������
	memcpy(sPack.pack.stime0,sdatetime+8,6);						// ����ʱ��
//	des2src(sPack.pack.sholder_ac_no,transdtl->refno);				// һ��ͨ���ײο���
	des2src(sPack.pack.sphone,tCust.stuempno);					// ѧ����
	des2src(sPack.pack.scust_limit,tCust.custname);					// ����
	des2src(sPack.pack.scust_auth2,tCust.idno);						// ���֤��
	des2src(sPack.pack.scust_limit2,bankcard.bankcardno);			// ���п���
	sPack.pack.lvol6 = termid;									// �ն˺�
	if(bcc_timeout<5)
	   bcc_timeout=5;
	
	ret = ExtCall(0, drtp_branch, base_funcno, 0, bcc_timeout, &sPack, &aPack, &ArrayPack);
	if (ret < 0 || aPack.head.retCode != 0)
	{
		writelog(LOG_ERR,"extcall 2401 ret[%d],retcode[%d] timeout[%d] ",ret,aPack.head.retCode,bcc_timeout);
		if (ret < 0)				// ͨѶ����
		{
			strcpy(szMsg,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
			return E_BCC_NETWORK;
		}
		else						// �յ�ǰ�÷��صĴ���
		{
			strcpy(szMsg,aPack.pack.vsmess);
			return E_COMMON_ERR;
		}
	}
	if(aPack.pack.lvol1 != 1)		// ǰ�ý������
	{	
		strcpy(szMsg,"�����������ݴ���");
		return E_BCC_NETWORK;
	}

	des2src(out_pack->sall_name,aPack.pack.sall_name);				//�ͻ���
	out_pack->damt0 = aPack.pack.damt0;							// �˻����
	out_pack->damt1 = aPack.pack.damt1;							// �������
	return 0;
}


int F240024(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_DAMT0,F_DAMT1,F_SALL_NAME,0);

	ret = DoQueryBala(BANK_QUERYBALA,rPack,out_pack,szMsg);
	if(ret)
		return ret;
			
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

