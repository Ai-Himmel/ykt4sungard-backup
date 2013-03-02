/* --------------------------------------------
 * ��������: F847121.c
 * ��������: 2005-05-26
 * ��������: �Ž�
 * �汾��Ϣ:
 * ������:���¿���Ϣ
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"

int F847121(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double dSerialno=0;
	int cardno=0;
	char cardphyid[16+1]="";

	T_t_card tCard;
	T_t_tif_tradeserial tTradeserial;

	memset(&tCard,0,sizeof(tCard));
	memset(&tTradeserial,0,sizeof(tTradeserial));

	cardno=rPack->lvol0;
	des2src(cardphyid,rPack->sbank_acc);

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	/*
	if(rPack->lvol2!=IS_NO)
	{
		if(strlen(rPack->scust_limit)==0)
		{
			*pRetCode=E_OPER_NOT_EXIST;
			goto L_RETU;
		}
		if(strlen(rPack->scust_limit2)==0)
		{
			*pRetCode=E_INPUT_AUTH_OPER_NULL;
			goto L_RETU;
		}
		if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
		{
			writelog(LOG_ERR,"oper[%s]auth_oper[%s]",rPack->scust_limit,rPack->scust_limit2);
			*pRetCode=E_OPER_AND_AUTH_OPER_EQ;
			goto L_RETU;
		}
		ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
		if(ret)
		{
			if(E_OPER_NOT_EXIST==ret)
				*pRetCode=E_AUTH_OPER_NOT_EXIST;
			else if(E_PASSWORD_WRONG==ret)
				*pRetCode=E_AUTH_OPER_PWD;
			else
				*pRetCode=ret;
			goto L_RETU;
		}
	}
	*/
	trim(rPack->scust_no);
	ret=IsInvalidDateTime(rPack->sdate0, "YYYYMMDD");
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	if(cardno==0)
	{
		ret=get_cardno_by_physical_no(&cardno,cardphyid);
		if(ret)
		{
			*pRetCode= E_CARDNO_NOT_EXIST;
			writelog(LOG_ERR,"get_cardno_by_physical_no error,ret=[%d] cardphyid=[%s]",ret,cardphyid);
			goto L_RETU;
		}
	}

	ret=DB_t_card_read_lock_by_cur_and_cardno(cardno, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.cardattr[CARDSTAT_TYPE_REG])
	{
		DB_t_card_free_lock_by_cur();
		*pRetCode=E_CARD_CLOSE;
		goto L_RETU;
	}
//		if('3'==tCard.cardattr[CARDSTAT_TYPE_REG])
//		{
//			DB_t_card_free_lock_by_cur();
//			*pRetCode=E_CARD_CHANGE;
//			goto L_RETU;
//		}
	trim(rPack->scust_no);
//		if(strlen(rPack->scust_no)!=0)
//		{
//			if(strcmp(tCard.showid,rPack->scust_no)!=0)
//			{
//				ret=IsExistShowCardNo(rPack->scust_no);
//				if(ret)
//				{
//					DB_t_card_free_lock_by_cur();
//					writelog(LOG_ERR,"showcardno[%s]",rPack->scust_no);
//					*pRetCode=ret;
//					goto L_RETU;
//				}
//			}
//		}
	trim(rPack->sbank_acc);
	if(strcmp(tCard.cardphyid,rPack->sbank_acc)!=0)
	{
		DB_t_card_free_lock_by_cur();
		writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,rPack->sbank_acc);
		*pRetCode= E_CARD_PHYNO_DIFFER;
		goto L_RETU;
	}
	if(strlen(rPack->scust_no)==10)
		des2src(tCard.showid,rPack->scust_no);
	if(strlen(rPack->sdate0)==8)
		des2src(tCard.endtime,rPack->sdate0);
	ret=DB_t_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"cardno[%d]",cardno);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_card_free_lock_by_cur();
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//�����ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no = D2I(dSerialno);											//��ˮ��
	tTradeserial.other_seri_no = 0;												//�ϴ�����ˮ��
	tTradeserial.serial_type = 847121;												//���״��룻��ע������+��ֵ ��һ�������룬��847101�� ����������ֵ������һ�������룬���µķ��������ļ������Ӷ����ַ�����ֵ�뷢������ֵ�Ŀ�������Ϣ��
	tTradeserial.serial_state = SERISTAT_DEBT;										//��ˮ״̬
	des2src(tTradeserial.operate_date,sysdate);									//��������
	des2src(tTradeserial.operate_time,systime);									//����ʱ��
	des2src(tTradeserial.collect_date,sysdate);										//�ɼ�����
	des2src(tTradeserial.collect_time,systime);										//�ɼ�ʱ��
	des2src(tTradeserial.enteract_date,logicdate);									//��������
	des2src(tTradeserial.enteract_time,systime);									//����ʱ��
	des2src(tTradeserial.opercode , rPack->scust_limit);
	tTradeserial.maindeviceid = rPack->lvol6;										//�ϴ�����վ��ʶ
	tTradeserial.deviceid = rPack->lvol7;											//�ɼ��豸��ʶ
	tTradeserial.cardno = tCard.cardno;											//����
	des2src(tTradeserial.showid,tCard.showid);										//��ʾ����
	tTradeserial.purseno = PURSE_NO_ONE;										//Ǯ����
	tTradeserial.custid = tCard.custid;									//�ͻ���ʶ
//	tTradeserial.reviseserial_no=dSerialno;											//ԭд��ʧ����ˮ��
	des2src(tTradeserial.reserve_1,rPack->scust_limit2);							//��Ȩ����Ա��
	des2src(tTradeserial.reserve_2,rPack->semp_pwd);								//��Ȩ����Ա����
	if(rPack->lvol2!=IS_NO)
	{
		// ���д�����
		tTradeserial.in_balance = rPack->damt0;
		tTradeserial.out_balance = rPack->damt1;
		tTradeserial.trade_fee = rPack->damt1 - rPack->damt0;
		tTradeserial.trade_count = rPack->lvol1+1;
	}
	//	���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tTradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
