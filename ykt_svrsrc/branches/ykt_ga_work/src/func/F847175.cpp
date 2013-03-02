/* --------------------------------------------
 * ��������: F847175.sqc
 * ��������: 2008-09-03
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ��ѯ,��Ѻ��,����,��Ѻ��
 * --------------------------------------------
 * �޸�����: 
 * �޸���Ա: 
 * �޸�����: 
 * �汾��Ϣ: 
 * ��ע��Ϣ: 
 * --------------------------------------------*/

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
#include "account.h"

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
	if(strlen(p->oper_code))
		strcpy(IA->sMdeOper,p->oper_code);			//����Ա
	else
		strcpy(IA->sMdeOper,"system");
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

static int check_deposit(ST_PACK *rPack,ST_PACK *out_pack)		//��ѯѺ��
{
	int ret = 0;
	T_t_pif_card tCard;
	T_t_cif_customer tCustomer;
	T_t_tif_libdeposit tLibdeposit;

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tLibdeposit,0,sizeof(tLibdeposit));

	int card_id = rPack->lvol0;		//����
	writelog(LOG_DEBUG,"����[%d]*******************",card_id);
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CARDNO_NOT_EXIST;
		else
			return E_DB_CARD_R;
	}
	if(strncmp(tCard.state_id,CARDSTAT_REG,4)!=0)
	{
		if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
			return E_CARDNO_LOGOUT;
		else if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
			return E_CARD_CHANGE;
		else if(tCard.state_id[CARDSTAT_TYPE_LOST]==STATE_TRUE)
			return E_CARDNO_LOST;
		else if(tCard.state_id[CARDSTAT_TYPE_FREEZE]==STATE_TRUE)
			return E_CARDNO_FREEZE;
		else if(tCard.state_id[CARDSTAT_TYPE_WFAIL]==STATE_TRUE)
			return E_CARDNO_WFAIL;
	}
	
		
	if(tCard.type_id == CT_NORMAL)			//��ʽ��,��ֹ����,�����ж�
		ret = -1;
	
	ret = DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		if(ret ==DB_NOTFOUND)
			return E_DB_CUSTOMER_N;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state != CUSTSTAT_REGIST)		//�ͻ��Ѿ�ע��
		return E_CUSTOMER_LOGOUT;
	
	writelog(LOG_DEBUG,"�ͻ���[%d]*******************",tCustomer.cut_id);
	if(tCustomer.cut_type != 20 && tCustomer.cut_type != 26)				///////////////�޸�Ϊ��ѵѧԱ
		ret = -1;
	else
	{
		ret = DB_t_tif_libdeposit_read_by_customer_id(tCustomer.cut_id, &tLibdeposit);
		if(ret)
		{
			if(ret == DB_NOTFOUND)			//δ�ҵ�,�轻Ѻ��
				ret = 1;			
			else
				return E_DB_LIBDEPOSIT_R;
		}
		else
		{
			if(tLibdeposit.fee_flag[0] !='1')	// δ��Ѻ��
				ret = 1;
			else 
				ret = 0;		
		}
	}

	writelog(LOG_DEBUG,"ret [%d]*******************",ret);
	if(ret == -1)		//����ѵѧԱ
		out_pack->lvol0 = -1;
	
	else if(ret == 0)		//��ѵѧԱ,�ѽ���Ѻ��
		out_pack->lvol0  = 0;
	
	else if(ret == 1)				//��ѵѧԱ,�轻Ѻ��
		out_pack->lvol0 = 1;

	return 0;
}

static int handin_deposit(ST_PACK *rPack,ST_PACK *out_pack)		//�Ͻ�Ѻ��
{
	int ret = 0,depflag = 0;
	int card_id = 0;
	double deposit_fee = 0;
	char deposit_para[20] = "";
	char logicdate[9] = "";
	char sysdate[9] ="";
	char systime[7] = "";
	double dSerialNo = 0;
	InAcc	IA;
	
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_libdeposit tLibdeposit;
	T_t_aif_account tAccount;
	memset(&tLibdeposit,0,sizeof(tLibdeposit));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ret = check_deposit(rPack,out_pack);
	if(ret)
		return ret;
	
	writelog(LOG_DEBUG,"ret [%d]*******************",ret);

	depflag = out_pack->lvol0;
//	if(depflag != 1)			//����Ҫ��Ѻ��,ֱ�ӷ���
//		return 1;
	if(depflag == -1)
		return -1;			//����Ҫ��Ѻ��
	if(depflag == 0)
		return 1;			//�Ѿ�����Ѻ��

	ret = GetParameter(GLOBAL_LIB_DEPOSIT, deposit_para);
	if(ret)
		return ret;
	deposit_fee = atof(deposit_para);
	writelog(LOG_DEBUG,"deposit_fee [%f]*******************",deposit_fee);

//	rPack->damt1 = rPack->lvol8/100;		//��ת��ΪԪ
	if(amtcmp(rPack->damt1,deposit_fee) < 0)		//��Ƭ�Ͻ��С��Ѻ����
		return E_AMT_LACK;
	
	card_id = rPack->lvol0;		//����
	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}
	if(tAccount.act_type != ACCOUNTSTAT_REGIST)
		return E_ACTNO_LOGOUT;
	if(amtcmp(tAccount.cur_freebala,deposit_fee) < 0)
		return E_BALANCE_SHORTAGE;
	
	writelog(LOG_DEBUG,"name [%s]*******************",tAccount.cut_name);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
		return ret;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	
	tradeserial.trade_fee = deposit_fee;		//���׽��
	tradeserial.serial_type = TXCODE_LIBDEPOSIT_HANDIN;
	tradeserial.in_balance=rPack->damt1;		//��Ƭ�Ͻ��
	tradeserial.trade_count=rPack->lvol10+1;		//���״���
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, "system");
	tradeserial.customer_id = tAccount.customer_id;
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	tradeserial.card_id = card_id;
	
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�̻��ʻ�
	IA.iCardNo=tAccount.card_id;
	writelog(LOG_DEBUG,"acc_id [%s]*******************",IA.sArrInActno[0]);
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}

	sprintf(out_pack->vsmess,"��Ѻ��ǰ�������:%.2lfԪ,��ǰ�������:%.2lfԪ",tradeserial.in_balance,tradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	if(amtcmp(tradeserial.out_balance,0)<0)
		return E_ENTER_ACCOUNT;
	
	tLibdeposit.customer_id = tAccount.customer_id;
	tLibdeposit.deposit_fee = deposit_fee;
	tLibdeposit.fee_flag[0] = '1';
	des2src(tLibdeposit.cut_name,tAccount.cut_name);
	des2src(tLibdeposit.oper_date,logicdate);
	des2src(tLibdeposit.oper_time,systime);	
	ret = DB_t_tif_libdeposit_add(&tLibdeposit);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
			ret = DB_t_tif_libdeposit_update_by_customer_id(tAccount.customer_id,&tLibdeposit);
			if(ret)
				return E_DB_LIBDEPOSIT_U;
		}
		else
			return E_DB_LIBDEPOSIT_I;
	}
	out_pack->damt1 = deposit_fee;		//���׽��
	out_pack->damt2 = tradeserial.out_balance;		//����ֵ
	out_pack->lvol4 = D2I(deposit_fee*100);
	out_pack->lvol5 = D2I(tradeserial.out_balance*100);
	out_pack->lserial0 = tradeserial.serial_no;	//��ˮ��
	return 0;
}

static int do_enteract(T_t_tif_tradeserial *reverse_serial,T_t_tif_tradeserial *tradeserial,InAcc *IA)
{
	int ret;
	double new_serial;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&new_serial);
	if(ret)
	{
		writelog(LOG_ERR,"���ɽ�����ˮ�Ŵ���");

		return ret;
	}
	tradeserial->serial_no = D2I(new_serial);
	tradeserial->serial_state = SERISTAT_DEBT;
	tradeserial->in_balance = reverse_serial->out_balance;
	tradeserial->out_balance = reverse_serial->in_balance;
	tradeserial->trade_fee = -reverse_serial->trade_fee;
	getsysdate(tradeserial->operate_date);
	getsystime(tradeserial->operate_time);
	des2src(tradeserial->enteract_time,tradeserial->operate_time);

	// ���׽��
	IA->dArrInAmt[0] = tradeserial->trade_fee;
	// ������־
	IA->iTxFlag = ACC_TYPE_RUSH;
	writelog(LOG_DEBUG,"�������׽�� [%f]*******************",IA->dArrInAmt[0]);
	ret = process(IA,tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process account ret[%d]",ret);
		return ret;
	}
	
	if(amtcmp(tradeserial->out_balance,0)<0)
		return E_ENTER_ACCOUNT;
	
	ret = DB_t_tif_tradeserial_add(tradeserial);
	if(ret)
	{
		if(DB_REPEAT == ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}

	// ��¼ˮ��ˮ��
	reverse_serial->reviseserial_no = tradeserial->serial_no;
	
	return 0;
}

static int backoff(ST_PACK *rPack,ST_PACK *out_pack)				//д��ʧ�ܳ���
{
	int ret = 0;
	InAcc	IA;
	int serial_no = rPack->lserial0;		//��ˮ��
	int card_id = rPack->lvol0;		//����
	
	T_t_tif_tradeserial  tradeserial,reverse_serial;
	T_t_tif_libdeposit tLibdeposit;
	T_t_aif_account tAccount;
	memset(&tLibdeposit,0,sizeof(tLibdeposit));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&reverse_serial,0,sizeof(reverse_serial));

	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}

	des2src(IA.sArrInActno[0],tAccount.account_id);						
	IA.iCardNo=tAccount.card_id;
	writelog(LOG_DEBUG,"acc_id [%s]*******************",IA.sArrInActno[0]);

	ret = DB_t_tif_tradeserial_read_lock_by_cur_and_serial_no(serial_no, &reverse_serial);
	if(ret)
	{
		writelog(LOG_ERR,"read serial error,serialno[%d]",serial_no);
		// �޶�Ӧ��ˮ,�ͷ��س����ɹ�
		if(DB_NOTFOUND == ret)
			return 0;
		return E_DB_TRADESERIAL_R;
	}

	if(reverse_serial.serial_state != SERISTAT_DEBT)
	{
		writelog(LOG_ERR,"������ˮ�ѱ�����,�����ٴγ���,serial[%d]logicdate[%s]",
				 reverse_serial.serial_no,reverse_serial.enteract_date);
		ret = 0;
	}
	else
	{
		memcpy(&tradeserial,&reverse_serial,sizeof(tradeserial));
		ret = do_enteract(&reverse_serial,&tradeserial,&IA);
		if(!ret)
		{
			// ��ˮ״̬��־�� �ѳ���
			reverse_serial.serial_state = SERISTAT_RUSH;
			ret = DB_t_tif_tradeserial_update_lock_by_cur(&reverse_serial);
			if(ret)
			{
				writelog(LOG_ERR,"���±�������ˮʧ��,ret[%d]",ret);
				ret = E_DB_TRADESERIAL_U;
			}
		}		
	}
	DB_t_tif_tradeserial_free_lock_cur();
	if(ret)
		return ret;
	
	ret = DB_t_tif_libdeposit_read_by_customer_id(tAccount.customer_id, &tLibdeposit);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_LIBDEPOSIT_N;
		return E_DB_LIBDEPOSIT_R;
	}
	if(tLibdeposit.fee_flag[0] == '0')
		tLibdeposit.fee_flag[0] = '1';
	else
		tLibdeposit.fee_flag[0] = '0';
	ret = DB_t_tif_libdeposit_update_by_customer_id(tAccount.customer_id, &tLibdeposit);
	if(ret)
		return E_DB_LIBDEPOSIT_U;
	out_pack->damt2 = tradeserial.out_balance;		//����ֵ
	out_pack->lserial0 = tradeserial.serial_no;	//��ˮ��
	return 0;
}

static int handback_deposit(ST_PACK *rPack,ST_PACK *out_pack)		//�˻�Ѻ��
{
	int ret = 0,depflag = 0;
	int card_id = 0;
	double deposit_fee = 0;
	char logicdate[9] = "";
	char sysdate[9] ="";
	char systime[7] = "";
	double dSerialNo = 0;
	InAcc	IA;
	
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_libdeposit tLibdeposit;
	T_t_aif_account tAccount;
	memset(&tLibdeposit,0,sizeof(tLibdeposit));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ret = check_deposit(rPack,out_pack);
	if(ret)
		return ret;
	
	depflag = out_pack->lvol0;
//	if(depflag != 0)			//����Ҫ��Ѻ��,ֱ�ӷ���
//		return 1;
	if(depflag == -1)
		return -1;			//����Ҫ��Ѻ��
	if(depflag == 1)
		return 1;			//δ����Ѻ��
	
	card_id = rPack->lvol0;		//����
	ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_id,PURSE_NO_ONE,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}
	if(tAccount.act_type != ACCOUNTSTAT_REGIST)
		return E_ACTNO_LOGOUT;
	if(amtcmp(tAccount.cur_freebala,deposit_fee) < 0)
		return E_BALANCE_SHORTAGE;

	ret = DB_t_tif_libdeposit_read_by_customer_id(tAccount.customer_id, &tLibdeposit);
	if(ret)
		return E_DB_LIBDEPOSIT_R;
	deposit_fee = tLibdeposit.deposit_fee;
	
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
		return ret;
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
//	rPack->damt1 = rPack->lvol8/100;	
	tradeserial.trade_fee = deposit_fee;		//���׽��
	tradeserial.serial_type = TXCODE_LIBDEPOSIT_HANDOFF;
	tradeserial.in_balance=rPack->damt1;		//��Ƭ�Ͻ��
	tradeserial.trade_count=rPack->lvol10+1;		//���״���
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, "system");
	tradeserial.customer_id = tAccount.customer_id;
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	tradeserial.card_id = card_id;
	
	des2src(IA.sArrInActno[0],tAccount.account_id);						//�̻��ʻ�
	IA.iCardNo=tAccount.card_id;

	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}

	sprintf(out_pack->vsmess,"��Ѻ��ǰ�������:%.2lfԪ,��ǰ�������:%.2lfԪ",tradeserial.in_balance,tradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	if(amtcmp(tradeserial.out_balance,0)<0)
		return E_ENTER_ACCOUNT;
	
	
	tLibdeposit.fee_flag[0] = '0';	
	ret = DB_t_tif_libdeposit_update_by_customer_id(tAccount.customer_id,&tLibdeposit);
	if(ret)
		return E_DB_LIBDEPOSIT_U;
		
	out_pack->damt1 = deposit_fee;		//���׽��
	out_pack->damt2 = tradeserial.out_balance;		//����ֵ
	out_pack->lvol4 = D2I(deposit_fee*100);
	out_pack->lvol5 = D2I(tradeserial.out_balance*100);
	out_pack->lserial0 = tradeserial.serial_no;	//��ˮ��
	return 0;
}

int F847175(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	int transcode = rPack->lvol3;		//������
	rPack->damt1=D4U5(rPack->lvol8/100.0, 2);		// �뿨ֵ��ǰ�˴����
	switch(transcode)
	{
		case 10:						
			ret = check_deposit(rPack,out_pack);
			break;
		case 11:
			ret = handin_deposit(rPack,out_pack);
			break;
		case 12:
			ret = backoff(rPack,out_pack);
			break;
		case 13:
			ret = handback_deposit(rPack,out_pack);
			break;
		default :
			ret =-1;
	}

	if(ret)
		return ret;
	
	SetCol(handle,0);
 	SetCol(handle,F_LVOL0,F_LVOL4,F_LVOL5,F_DAMT1,F_DAMT2,F_LSERIAL0,F_VSMESS,0);
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
}
