/* --------------------------------------------
 * ��������: F49003.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:POS ������ֵ
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
	IA->dOutCardBala=-1;							//����ֵ

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//����ֵ
	return 0;
}

int F849003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	int	type=0;
	InAcc	IA;
	double dSerialNo = 0;
	int card_id=0;
	int amt=0;
	int oper_card_id=0;
	char sMaxCardBalance[20]="";
	char sdevice_id[31]="";
	double dMaxCardBalance=0;
	T_t_pif_oper_authcard tOper_auth_card;
	T_t_tif_tradeserial  tradeserial;
	T_t_pif_card		tCard;
	T_t_deposit_oper   tDepositOper;
	T_t_deposit_operpos tDepositOperpos;
	T_t_deposit_shoppos tDepositShoppos;
	T_t_deposit_shop tDepositShop;
	T_t_cif_customer   tCustomer;
	T_t_aif_account	tAccount;		//�ʻ���

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tOper_auth_card,0,sizeof(tOper_auth_card));
	memset(&tDepositOper,0,sizeof(tDepositOper));
	memset(&tDepositOperpos,0,sizeof(tDepositOperpos));
	memset(&tDepositShoppos,0,sizeof(tDepositShoppos));
	memset(&tDepositShop,0,sizeof(tDepositShop));
	memset(&tCard,0,sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&IA,0,sizeof(IA));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	tradeserial.maindevice_id   = rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	card_id=rPack->lvol5;
	tradeserial.card_id=card_id;
	tradeserial.other_seri_no=rPack->lvol4;					//�ϴ�����ˮ��
	amt=rPack->lvol8;									//��ֵ���
	tradeserial.in_balance=rPack->lvol9/100.0;				//�뿨���
	tradeserial.trade_fee   = amt/100.0;				
	tradeserial.trade_count = rPack->lvol7;					//�뿨���
	oper_card_id=rPack->lvol3;			//����Ա��
	des2src(tradeserial.devphy999_id, rPack->sdate1);		//�����豸ID
	// ��ȡ����Ա��
	if(oper_card_id > 0)
	{
		ret = DB_t_pif_oper_authcard_read_by_card_id(oper_card_id,&tOper_auth_card);
		if(ret)
		{
			writelog(LOG_ERR,"get operator code from auth card error, auth_card_id[%d]",oper_card_id);
			if(DB_NOTFOUND == ret)
				*pRetCode=E_DB_OPER_AUTHCARD_N;
			else
				*pRetCode= E_DB_OPERATOR_R;
			goto L_RETU;
		}
		if(2==tOper_auth_card.status)
		{
			*pRetCode=E_OPERLOGON_UNREG;
			goto L_RETU;
		}
		des2src(tradeserial.oper_code,tOper_auth_card.oper_code);
	}
	ret=GetDevIdByDevPhyId(&(tradeserial.device_id),tradeserial.devphy999_id);
	if (ret)
	{
		writelog(LOG_ERR,"GetDevIdByDevPhyId err[%d] devphy999_id[%s]",ret,tradeserial.devphy999_id);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(sdevice_id,"%d",tradeserial.device_id);
	ret=DB_t_deposit_oper_read_lock_by_cur_and_oper_code(tradeserial.oper_code,&tDepositOper);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_DEPOSIT_OPER_R;
		else
			*pRetCode=E_DB_DEPOSIT_OPER_N;
		goto L_RETU;
	}
	if(tDepositOper.status[0]!='1')
	{
		DB_t_deposit_oper_free_lock_by_cur();
		*pRetCode=E_DEPOSIT_OPER_STOP;
		goto L_RETU;
	}
	//�ж��Ƿ����ظ�����
	if(tDepositOper.last_pos_serial_no==rPack->lvol4)
	{
		DB_t_deposit_oper_free_lock_by_cur();
		ret=DB_t_tif_tradeserial_read_by_serial_no(tDepositOper.last_host_serial_no,&tradeserial);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode=E_DB_TRADESERIAL_N;
			else
				*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;

		}
	
	      	ResetNormalCPack(&aPack,0,1);
	      	SetCol(handle,0);
	      	SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);

	      	out_pack->lvol5 = tradeserial.card_id;
	      	out_pack->lvol10 = (int)D4U5(tradeserial.out_balance*100,0);
	      	out_pack->lcert_code = tradeserial.serial_no;
	      	PutRow(handle,out_pack,pRetCode,szMsg);
		return 0;
	}
	if(strncmp(tDepositOper.lastday,sysdate,8)!=0)
	{
		des2src(tDepositOper.lastday,sysdate);
		tDepositOper.lastday_total_cnt=0;
		tDepositOper.lastday_total_amt=0;
	}
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(dSerialNo);								//��ˮ��	
	tDepositOper.total_cnt++;
	tDepositOper.total_amt+=amt;
	tDepositOper.lastday_total_cnt++;
	tDepositOper.lastday_total_amt+=amt;
	tDepositOper.last_pos_serial_no=tradeserial.other_seri_no;
	tDepositOper.last_host_serial_no=tradeserial.serial_no;
	tDepositOper.last_card_id=card_id;
	des2src(tDepositOper.last_device_id,rPack->sdate1);
	getdatetime(tDepositOper.last_saved);
	if(tDepositOper.max_amt>0)
	{
		if(tDepositOper.lastday_total_amt>tDepositOper.max_amt)
		{
			*pRetCode=E_OPER_OVER_MAX_DEPOSIT_AMT;
			goto L_RETU;
		}
	}
	ret=DB_t_deposit_oper_update_lock_by_cur(&tDepositOper);
	if(ret)
	{
		*pRetCode=E_DB_DEPOSIT_OPER_U;
		goto L_RETU;
	}
	DB_t_deposit_oper_free_lock_by_cur();
	ret=DB_t_deposit_shoppos_read_by_device_id(sdevice_id, &tDepositShoppos);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			tradeserial.serial_type = TXCODE_DEPOSIT_LOG;
		}
		else
		{
			*pRetCode=E_DB_DEPOSIT_SHOPPOS_R;
			goto L_RETU;
		}
	}
	else
	{
		tradeserial.serial_type = TXCODE_ONLINE_SHOPDEPOSIT;
		ret=DB_t_deposit_shop_read_by_shop_id(tDepositShoppos.shop_id, &tDepositShop);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				*pRetCode=E_DB_DEPOSIT_SHOP_N;
			else
				*pRetCode=E_DB_DEPOSIT_SHOP_R;
			goto L_RETU;
		}
		if(tDepositShop.status[0]=='2')
		{
			*pRetCode=E_SHOP_CLOSE;
			goto L_RETU;
		}
		des2src(IA.sArrInActno[4],tDepositShop.account_id);						//�ʻ�
	}
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			*pRetCode = E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			*pRetCode=E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			*pRetCode=E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			*pRetCode=E_CARDNO_WFAIL;
		goto L_RETU;
	}
	//�жϿ��Ƿ񳬹�������Ч����
	if(strncmp(tCard.end_time,sysdate,8)<=0)
	{
		*pRetCode = E_CARD_EXPIRE;
		goto L_RETU;
	}
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
	ret=DB_t_aif_account_read_by_card_id_and_purse_id(card_id, PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_card_id_and_purse_id ret[%d]card_id[%d]",ret,card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_ACTNO_NOT_EXIST;
		else
			*pRetCode=E_DB_ACCOUNT_R;
		goto L_RETU;
	}
	ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	dMaxCardBalance=atof(sMaxCardBalance);

	if(amtcmp(tradeserial.in_balance+tradeserial.trade_fee,dMaxCardBalance)>0)
	{
		*pRetCode= E_AMT_EXCEED_MAX;
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
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	tradeserial.serial_state = SERISTAT_DEBT;								//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);							//��������
	des2src(tradeserial.operate_time,systime);							//����ʱ��
	des2src(tradeserial.collect_date,sysdate);								//�ɼ�����
	des2src(tradeserial.collect_time,systime);								//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);							//��������
	des2src(tradeserial.enteract_time,systime);							//����ʱ��
	tradeserial.purse_id = PURSE_NO_ONE;								//Ǯ����
	tradeserial.customer_id = tCustomer.cut_id;
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
	IA.iCardNo=tCard.card_id;
	IA.iFeeType=tCustomer.fee_type;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	writelog(LOG_INFO,"��ˮ��%d ����%d ��ֵǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",IA.iSerialNo,IA.iCardNo,tradeserial.in_balance,tradeserial.out_balance);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	if(amtcmp(tradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
      	ResetNormalCPack(&aPack,0,1);
      	SetCol(handle,0);
      	SetCol(handle,F_LVOL5,F_LVOL10,F_LCERT_CODE,0);

      	out_pack->lvol5 = tradeserial.card_id;
      	out_pack->lvol10 = (int)D4U5(tradeserial.out_balance*100,0);
      	out_pack->lcert_code = tradeserial.serial_no;
      	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
