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
#include "account.h"
#include "fdsqc.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//����վ��ʶ
	IA->iDevId=p->device_id;						//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	IA->iTradeNo=p->serial_type;					//������
	strcpy(IA->sTxDate,p->operate_date);			//��������
	strcpy(IA->sTxTime,p->operate_time);			//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);		//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);		//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);		//��������
	strcpy(IA->sTxAccTime,p->enteract_time);		//����ʱ��
	strcpy(IA->sMdeOper,p->oper_code);			//����Ա
	strcpy(IA->sChkOper,p->reserve_1);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
	IA->iTxCnt=p->trade_count;					//���״���
	IA->dInCardBala=p->in_balance;				//�뿨ֵ
	IA->dOutCardBala=p->out_balance;							//����ֵ
	IA->iTxFlag=ACC_TYPE_RUSH;
	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
//		p->out_balance=IA->dOutCardBala;			//����ֵ
	return 0;
}

int F849004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	int	type=0;
	InAcc	IA;
	double dSerialNo = 0;
	char sdevice_id[31]="";
	T_t_tif_tradeserial  tTradeserial;
	T_t_tif_tradeserial  OldtTradeserial;
	T_t_pif_card		tCard;
	T_t_deposit_oper   tDepositOper;
	T_t_deposit_shoppos tDepositShoppos;
	T_t_deposit_shop tDepositShop;
	T_t_cif_customer   tCustomer;
	T_t_aif_account	tAccount;		//�ʻ���

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tDepositOper,0,sizeof(tDepositOper));
	memset(&tCard,0,sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tTradeserial,0,sizeof(tTradeserial));
	memset(&OldtTradeserial,0,sizeof(OldtTradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&IA,0,sizeof(IA));

	snprintf(sysdate,9,"20%s",rPack->spost_code);
//	getsysdate(sysdate);

	ret=DB_t_deposit_oper_read_lock_by_c1_and_last_device_id_and_last_pos_serial_no( rPack->sdate1,rPack->lvol3,&tDepositOper);
	if(ret)
	{
		writelog(LOG_ERR,"ret[%d]last_device_id[%s]last_pos_serial_no[%d]",ret,rPack->sdate1,rPack->lvol3);		
		if(DB_NOTFOUND==ret)
			return 0;
		else
		{
			*pRetCode=E_DB_DEPOSIT_OPER_R;
			goto L_RETU;
		}
	}
	ret=DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(tDepositOper.last_host_serial_no,&OldtTradeserial);
	if(ret)
	{
		DB_t_deposit_oper_free_lock_by_c1();
		writelog(LOG_ERR,"ret[%d]last_host_serial_no[%d]",ret,tDepositOper.last_host_serial_no);		
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_TRADESERIAL_N;
		else
			*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;
	}
	if(SERISTAT_RUSH==OldtTradeserial.serial_state)
	{
		DB_t_tif_tradeserial_free_lock_cur();
		DB_t_deposit_oper_free_lock_by_c1();
		return 0;
	}
	OldtTradeserial.serial_state=SERISTAT_RUSH;
	ret=DB_t_tif_tradeserial_update_lock_by_cur(&OldtTradeserial);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_TRADESERIAL_N;
		else
			*pRetCode=E_DB_TRADESERIAL_U;
			goto L_RETU;
	}
	DB_t_tif_tradeserial_free_lock_cur();
	tDepositOper.total_cnt--;
	tDepositOper.total_amt-=(int)(OldtTradeserial.trade_fee*100);
	tDepositOper.lastday_total_amt-=(int)(OldtTradeserial.trade_fee*100);
	tDepositOper.lastday_total_cnt--;
	getdatetime(tDepositOper.last_saved);	
	ret=DB_t_deposit_oper_update_lock_by_c1(&tDepositOper);
	if(ret)
	{
		*pRetCode=E_DB_DEPOSIT_OPER_U;
		goto L_RETU;
	}
	DB_t_deposit_oper_free_lock_by_c1();
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	memcpy(&tTradeserial,&OldtTradeserial,sizeof(tTradeserial));
	if(OldtTradeserial.serial_type==TXCODE_ONLINE_SHOPDEPOSIT)
	{
		sprintf(sdevice_id,"%d",OldtTradeserial.device_id);
	
		ret=DB_t_deposit_shoppos_read_by_device_id(sdevice_id, &tDepositShoppos);
		if(ret)
		{
			writelog(LOG_ERR,"sdevice_id[%s]devphy999_id[%s]",sdevice_id,OldtTradeserial.devphy999_id);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_DB_DEPOSIT_SHOPPOS_N;
			else
				*pRetCode=E_DB_DEPOSIT_SHOPPOS_R;
			goto L_RETU;
		}
		ret=DB_t_deposit_shop_read_by_shop_id(tDepositShoppos.shop_id, &tDepositShop);
		if(ret)
		{
			writelog(LOG_ERR,"deposit_shop_id[%d]",tDepositShoppos.shop_id);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_DB_DEPOSIT_SHOP_N;
			else
				*pRetCode=E_DB_DEPOSIT_SHOP_R;
			goto L_RETU;
		}
		des2src(IA.sArrInActno[4],tDepositShop.account_id);						//�ʻ�
	}
	ret=DB_t_pif_card_read_by_card_id(OldtTradeserial.card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",OldtTradeserial.card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(OldtTradeserial.card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,OldtTradeserial.card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_ACTNO_NOT_EXIST;
		else
			*pRetCode=E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	ret=DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	//�õ��շ����
	if(0==tCustomer.fee_type)
	{
		tCustomer.fee_type=tCustomer.cut_type;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no = D2I(dSerialNo);								//��ˮ��
	tTradeserial.reviseserial_no= OldtTradeserial.serial_no;					//������ˮ��
	tTradeserial.trade_fee=-OldtTradeserial.trade_fee;
	tTradeserial.serial_state = SERISTAT_DEBT;							//��ˮ״̬
	des2src(tTradeserial.operate_date,sysdate);							//��������
	des2src(tTradeserial.operate_time,systime);							//����ʱ��
	des2src(tTradeserial.collect_date,sysdate);							//�ɼ�����
	des2src(tTradeserial.collect_time,systime);							//�ɼ�ʱ��
	des2src(tTradeserial.enteract_date,logicdate);						//��������
	des2src(tTradeserial.enteract_time,systime);							//����ʱ��
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	tTradeserial.in_balance=OldtTradeserial.out_balance;
	tTradeserial.out_balance=OldtTradeserial.in_balance;
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tTradeserial.trade_fee;
	IA.dInCardBala=tTradeserial.in_balance;
	IA.dOutCardBala=tTradeserial.out_balance;

	ret=process(&IA,&tTradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"��ˮ��%d ����%d ��ֵ����ǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",IA.iSerialNo,IA.iCardNo,tTradeserial.in_balance,tTradeserial.out_balance);
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
	if(amtcmp(tTradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
      	ResetNormalCPack(&aPack,0,1);
      	SetCol(handle,0);
      	SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);

      	out_pack->lvol5 = tTradeserial.card_id;
      	out_pack->lvol10 = (int)D4U5(tTradeserial.out_balance*100,0);
      	out_pack->lcert_code = tTradeserial.serial_no;
      	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
