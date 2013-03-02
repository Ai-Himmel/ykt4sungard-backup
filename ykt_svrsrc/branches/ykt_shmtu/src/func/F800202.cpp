/* --------------------------------------------
 * ��������: F847128.c
 * ��������: 2009-6-17
 * ��������: 
 * �汾��Ϣ: 1.0.0.0
 * ������: ���Ա������ɷ�
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
#include "fdsqc.h"


/*
���׿���		lvol0
��������		sdate0
��������		stime0
�̻��˻�		sstation1
�뿨ֵ			damt0
���׽��		damt1
���״���		lvol1	
�豸��			lvol3
*/

int F800202(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	//int i=0;
	int ret =0;
	int card_id= 0;
	char logicdate[11]="";										//ҵ������
	char systime[9]="";
	char pre_time[9]="";
	InAcc	IA;
	char  ia_buf[1024]="";
	double dUniqno = 0;
	char sMsg[256]="";
	
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_DAMT0,F_DAMT1,F_DAMT2,F_VSMESS,0);

	T_t_tif_tradeserial tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));
	IA.pVoidPointer=ia_buf;
	ResetNormalCPack(&aPack,0,1);
	
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		writelog(LOG_ERR,"GetLogicDate error,errcode=[%d]",ret);
		return ret;
	}
	getsystime(systime);

	T_t_pif_card tCard;
	memset(&tCard,0,sizeof(tCard));

	card_id=rPack->lvol0;
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			ret=E_CARDNO_NOT_EXIST;
		else
			ret=E_DB_CARD_R;
		return ret;
	}

	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret= E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			ret = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			ret=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			ret=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			ret=E_CARDNO_WFAIL;
		return ret;
	}

	T_t_aif_account account;
	memset(&account,0,sizeof(account));
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id,0,&account);
	if(ret)
	{
		writelog(LOG_ERR,"read t_aif_account err[%d]cardid[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
		{
			return E_ACTNO_NOT_EXIST;
		}
		else
			return E_DB_ACCOUNT_R;
	}
	
	T_t_cif_customer tCustomer;
	memset(&tCustomer,0,sizeof tCustomer);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			ret= E_CUSTOMER_NOT_EXIST;
		else
			ret= E_DB_CUSTOMER_R;
		return ret;
	}

	T_t_pif_spefee tSpeFee;
	memset(&tSpeFee,0,sizeof tSpeFee);
	//�õ��շ����
	if(0==tCustomer.fee_type)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				return E_DB_SPEFEE_R;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
		//���¿ͻ�����շ�����ֶ�
		ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				ret= E_CUSTOMER_NOT_EXIST;
			else
				ret= E_DB_CUSTOMER_U;
			return ret;
		}
	}
	DB_t_cif_customer_free_lock_cur();
	
	//	׼�����ݲ��뽻����ˮ��
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"getNewUniqNo error,errcode=[%d]",ret);
		return ret;
	}						
	tradeserial.serial_no = D2I(dUniqno);			//��ˮ��
	
	tradeserial.serial_type = 847233;
	des2src(tradeserial.operate_date,rPack->sdate0);
	GetPreTime(rPack->stime0, 1, pre_time);
	des2src(tradeserial.operate_time,pre_time);
	des2src(tradeserial.collect_date,tradeserial.operate_date);								//�ɼ�����
	des2src(tradeserial.collect_time,tradeserial.operate_time);								//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);							//��������
	des2src(tradeserial.enteract_time,systime);							//����ʱ��
	tradeserial.purse_id = PURSE_NO_ONE;					//Ǯ����
	tradeserial.serial_state = SERISTAT_DEBT;								//��ˮ״̬
	tradeserial.maindevice_id = 0;						//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol3;										//�ɼ��豸��ʶ
	tradeserial.card_id = card_id;										//���׿���
	tradeserial.customer_id=tCard.cosumer_id;								//�ͻ���
	des2src(tradeserial.oper_code,"web");
	tradeserial.trade_count=rPack->lvol1;			//���״���
	tradeserial.in_balance=rPack->damt0;			//�뿨ֵ
	tradeserial.trade_fee=rPack->damt1;				//���׽��
	tradeserial.out_balance=tradeserial.in_balance -tradeserial.trade_fee ;			//����ֵ
	strcpy(tradeserial.reserve_2,"���Ա������ɷ�");

	des2src(IA.sArrInActno[0],account.account_id);			//�跽�˺�(����)
	des2src(IA.sArrInActno[1],rPack->sstation1);				//�����˺�
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	IA.iMainDevId=tradeserial.maindevice_id;				//����վ��ʶ
	IA.iDevId=tradeserial.device_id;						//�豸ID
	IA.iSerialNo=tradeserial.serial_no;					//��ˮ��
	IA.iTradeNo=tradeserial.serial_type;					//������
	strcpy(IA.sTxDate,tradeserial.operate_date);			//��������
	strcpy(IA.sTxTime,tradeserial.operate_time);			//����ʱ��
	strcpy(IA.sTxCollectDate,tradeserial.collect_date);		//�ɼ�����
	strcpy(IA.sTxCollectTime,tradeserial.collect_time);		//�ɼ�ʱ��
	strcpy(IA.sTxAccDate,tradeserial.enteract_date);		//��������
	strcpy(IA.sTxAccTime,tradeserial.enteract_time);		//����ʱ��
	strcpy(IA.sMdeOper,tradeserial.oper_code);			//����Ա

	IA.iUseCardFlag=USE_CARD_TYPE_OFFLINE;		//��������
	IA.iTxCnt=tradeserial.trade_count;					//���״���
	IA.dInCardBala=tradeserial.in_balance;				//�뿨ֵ
	IA.dOutCardBala=-1;							//����ֵ

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(&IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}

	out_pack->damt0=tradeserial.out_balance;	//����ֵ
	out_pack->damt1=tradeserial.trade_fee;		//���׽��	
	out_pack->damt2=tradeserial.in_balance;		//���׽��	
	out_pack->lvol0 = tradeserial.serial_no;		//��ˮ��	
	sprintf(sMsg,"����:%d,���׽��:%.2f,����ǰ�����:%.2lfԪ, ����ǰ���:%.2lfԪ",card_id,tradeserial.trade_fee,tradeserial.in_balance,tradeserial.out_balance);
	strcat(out_pack->vsmess,sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}

	
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}

