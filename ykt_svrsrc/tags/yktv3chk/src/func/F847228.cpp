/* --------------------------------------------
 * ��������: F847228
 * ��������: 2007-01-19
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ����Ա��Ȩ������
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "busqc.h"
#include "acctrans.h"

int F847228(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	char sysdate[9] = "";
	char systime[7] = "";
	int auth_cardno = 0;
	T_t_authcard tAuthCard;
	T_t_operator tOper;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	double uni_no = 0.0;

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	TRANS& trans=pAccTrans->trans;
	ret=pAccTrans->checkCfgUpdate();
	if(ret)
		return ret;
	pAccTrans->clear();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_AUTHCARDUPD;
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;

	memset(&tAuthCard,0,sizeof tAuthCard);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&aPack,0,1);

	auth_cardno = rPack->lvol0;
	if(auth_cardno <= 0)
	{
		*pRetCode = E_INPUT_CARDNO;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit) == 0)
	{
		*pRetCode = E_INPUT_OPER_NULL;
		goto L_RETU;
	}

	if(IsInvalidDateTime(rPack->sdate0,"YYYYMMDD"))
	{
		*pRetCode = E_INPUT_DATE;
		goto L_RETU;
	}
	
	ret = DB_t_authcard_read_by_cardno(auth_cardno,&tAuthCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_AUTHCARD_NOT_EXISTS;
		else
			*pRetCode = E_DB_OPER_AUTHCARD_R;
		goto L_RETU;
	}

	if(tAuthCard.status[0] == STATUS_LOGOUT)
	{
		writelog(LOG_ERR,"auth card has been cancel ,card id[%d]",tAuthCard.cardno);
		*pRetCode = E_AUTHCARD_HAS_CANCEL;
		goto L_RETU;
	}
	if(tAuthCard.cardstatus[CARDSTAT_TYPE_LOST]== '1')
	{
		writelog(LOG_ERR,"auth card is loss , card id [%d]",tAuthCard.cardno);
		*pRetCode = E_AUTHCARD_IS_LOSS;
		goto L_RETU;
	}

	memset(&tOper,0,sizeof tOper);
	ret = DB_t_operator_read_by_opercode(tAuthCard.opercode,&tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			writelog(LOG_ERR,"operator does not exists, oper [%s]",tAuthCard.opercode);
			*pRetCode = E_DB_OPERATOR_N;
		}
		else
			*pRetCode = E_DB_OPERATOR_R;
		goto L_RETU;
	}
	if(tOper.status[0]==STATUS_LOGOUT)
	{
		writelog(LOG_ERR,"operator [%s] has been logout ",tAuthCard.opercode);
		*pRetCode = E_OPERLOGON_UNREG;
		goto L_RETU;
	}
	des2src(tAuthCard.expiredate,rPack->sdate0);
	tAuthCard.privilege = rPack->lvol1;

	ret = DB_t_authcard_update_by_cardno(tAuthCard.cardno,&tAuthCard);
	if(ret)
	{
		writelog(LOG_ERR,"update operator auth card information error, card id[%d]",tAuthCard.cardno);
		*pRetCode = E_DB_OPER_AUTHCARD_U;
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SDATE0,F_SCUST_LIMIT,0);
	out_pack->lvol0 = tAuthCard.cardno;
	des2src(out_pack->sdate0,tAuthCard.expiredate);
	out_pack->lvol1 = tAuthCard.privilege;
	des2src(out_pack->scust_limit,tAuthCard.opercode);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;		
}
