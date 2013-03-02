/* --------------------------------------------
 * ��������: 2008 8 21
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: ����Ǯ������ӿ�:��¼, ��ѯ,����,֧��,����,�ⶳ
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
#include "busqc.h"
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
	strcpy(IA->sMdeOper,p->oper_code);			//����Ա
	strcpy(IA->sChkOper,p->reserve_1);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//�޿�����
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
//	p->out_balance=IA->dOutCardBala;			//����ֵ
	return 0;
}

//��¼
static int login(ST_PACK *rPack,ST_PACK *out_pack)
{
	int ret = 0;
	char  key[17] = "";
	char opcode[11]="";
	char accpwd_crypt[33]="";
	char dyna_key[33]="";
	
	T_t_pif_operator tOper;
	memset(&tOper,0,sizeof(tOper));
	
	des2src(opcode,rPack->scust_no);		//����Ա��
	ret = DB_t_pif_operator_read_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_R;
	}

	Strncpy_t(key, opcode,sizeof(key));
	EncodePwd(key, rPack->scust_limit,accpwd_crypt, 0);
	
	if(strcmp(tOper.pwd,accpwd_crypt)!=0)
		return E_FAN_OPER_INVALID;
	//������̬��Կ
	GetDynaKey(dyna_key);
	des2src(tOper.comments,dyna_key);			
	ret = DB_t_pif_operator_update_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_U;
	}
	des2src(out_pack->scust_limit2,dyna_key);		//���û����ض�̬��Կ
	return 0;
}


//��ѯ���
static int checkbala(ST_PACK *rPack,ST_PACK *out_pack)
{
	int ret = 0;
	int cust_id = 0;
	char accno[33]="";
	char opcode[11]="";
	T_t_aif_account tAccount;
	T_t_cif_customer tCustomer;
	T_t_pif_operator tOper;
	
	memset(&tOper,0,sizeof(tOper));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCustomer,0,sizeof(tCustomer));
	
	
	des2src(opcode,rPack->scust_no);
	ret = DB_t_pif_operator_read_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_R;
	}

	if(strcmp(tOper.comments,rPack->scust_limit2) != 0)		//��֤��̬��Կ
		return E_EACC_DYNA_KEY;

	if(rPack->lvol1 == 0) 
	{
		des2src(accno,rPack->sbank_acc); //�˺�
		if(!strlen(accno))
			return E_INPUTNULL_ACCNO;
		
		ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		if(tAccount.act_type != ACCTYPE_PEREACC)
			return E_ACC_NOTEACC;
	}
	else
	{
		cust_id = rPack->lvol2;
		if(cust_id < 1)
			return E_INPUTNULL_CUSTID;
		ret = DB_t_cif_customer_read_by_cut_id(cust_id, &tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_CUSTOMER_N;
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.cut_state != CUSTSTAT_REGIST)
			return E_CUSTOMER_LOGOUT;
		
		if(tCustomer.eaccflag[0] == '0')
			return E_EACCNO_LOGOUT;
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(cust_id, ACCTYPE_PEREACC, &tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}		
	}

	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
		return E_EACCNO_LOGOUT;

	des2src(out_pack->sname,tAccount.cut_name);
	des2src(out_pack->sbank_acc,tAccount.account_id);
	out_pack->damt0=D4U5(tAccount.cur_bala,2);
	out_pack->damt1=D4U5(tAccount.cur_freebala,2);
	out_pack->damt2=D4U5(tAccount.cur_frozebala,2);
	return 0;
}

//�����˻�
static int frozen(ST_PACK *rPack,ST_PACK *out_pack)
{
	int ret = 0;
	int cust_id = 0;
	char accno[33]="";
	char opcode[11]="";
	T_t_aif_account tAccount;
	T_t_cif_customer tCustomer;
	T_t_pif_operator tOper;
	
	memset(&tOper,0,sizeof(tOper));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCustomer,0,sizeof(tCustomer));
	
	des2src(opcode,rPack->scust_no);
	ret = DB_t_pif_operator_read_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_R;
	}

	if(strcmp(tOper.comments,rPack->scust_limit2) != 0)
		return E_EACC_DYNA_KEY;

	char seed[32]="";
	char accpwd_plain[10]="";
	ret = GetParameter(2006, seed);
	if(ret)
		return ret;
	if(rPack->lvol1 == 0) 
	{
		des2src(accno,rPack->sbank_acc); //�˺�
		if(!strlen(accno))
			return E_INPUTNULL_ACCNO;
		
		ret=DB_t_aif_account_read_lock_by_cur_and_account_id(accno,&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		
		if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
		{
			DB_t_aif_account_free_lock_cur();
			return E_EACCNO_LOGOUT;
		}

		if(tAccount.act_type != ACCTYPE_PEREACC)
		{
			DB_t_aif_account_free_lock_cur();
			return E_ACC_NOTEACC;
		}
		
		ret = decrypt_elec_card_pwd(0,seed,tAccount.password,accpwd_plain);
		if(ret)
		{
			DB_t_aif_account_free_lock_cur();
			return E_PWD_DECRYPT;
		}
		if(strcmp(accpwd_plain,rPack->scust_limit)!=0)
		{
			DB_t_aif_account_free_lock_cur();
			return E_EACCPWD;
		}

		if(amtcmp(tAccount.cur_freebala, rPack->damt4) < 0)
		{
			DB_t_aif_account_free_lock_cur();
			return E_EACC_BALANCE_SHORTAGE;
		}
		tAccount.cur_freebala -= rPack->damt4;
		tAccount.cur_frozebala += rPack->damt4;
		ret = DB_t_aif_account_update_lock_by_cur(&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_U;
		}
		DB_t_aif_account_free_lock_cur();
	}
	else
	{
		cust_id = rPack->lvol2;
		ret = DB_t_cif_customer_read_by_cut_id(cust_id, &tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_CUSTOMER_N;
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.cut_state != CUSTSTAT_REGIST)
			return E_CUSTOMER_LOGOUT;
		
		if(tCustomer.eaccflag[0] == '0')
			return E_EACCNO_LOGOUT;
		ret = DB_t_aif_account_read_lock_by_c5_and_customer_id_and_act_type(cust_id, ACCTYPE_PEREACC, &tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}		
		if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
		{
			DB_t_aif_account_free_lock_c5();
			return E_EACCNO_LOGOUT;
		}
	
		ret = decrypt_elec_card_pwd(0,seed,tAccount.password,accpwd_plain);
		if(ret)
		{
			DB_t_aif_account_free_lock_c5();
			return E_PWD_DECRYPT;
		}
		if(strcmp(accpwd_plain,rPack->scust_limit)!=0)
		{
			DB_t_aif_account_free_lock_c5();
			return E_EACCPWD;
		}

		if(amtcmp(tAccount.cur_freebala, rPack->damt4) < 0)
		{
			DB_t_aif_account_free_lock_c5();
			return E_EACC_BALANCE_SHORTAGE;
		}
		
		tAccount.cur_freebala -= rPack->damt4;
		tAccount.cur_frozebala += rPack->damt4;
		ret = DB_t_aif_account_update_lock_by_c5(&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_U;
		}
		DB_t_aif_account_free_lock_c5();
	}

	
	//������ˮ
	char sysdate[9]="";
	char logicdate[9]="";
	char systime[7]="";
	T_t_tif_tradeserial  tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	double dSerialNo = 0;
	
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
	tradeserial.trade_fee = rPack->damt4;		//������
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_EACC_FROZEN;
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, rPack->semp);
	tradeserial.customer_id = tAccount.customer_id;
//	tradeserial.in_balance=tAccount.cur_freebala+rPack->damt4;
//	tradeserial.out_balance=tAccount.cur_freebala;
//	tradeserial.trade_count=tAccount.consume_count;		//���״���������
	tradeserial.sys_id = 0;		
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	//��������˻�������ˮ����
	T_t_tif_eacctradeserial tEacctradeserial;
	memset(&tEacctradeserial,0,sizeof(tEacctradeserial));
	tEacctradeserial.serial_no = D2I(dSerialNo);
	des2src(tEacctradeserial.ordercode,rPack->sholder_ac_no);
	des2src(tEacctradeserial.logic_date, logicdate);
	des2src(tEacctradeserial.opcode,rPack->scust_no);
	des2src(tEacctradeserial.operate_date,sysdate);
	des2src(tEacctradeserial.operate_time, systime);
	des2src(tEacctradeserial.opcode,rPack->scust_no);
	des2src(tEacctradeserial.payacc,tAccount.account_id);
	tEacctradeserial.frozenmoney = rPack->damt4;
	tEacctradeserial.frozencode[0] = '1';					//����ǰ�ȶ����˻�
	ret = DB_t_tif_eacctradeserial_add(&tEacctradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}	
	des2src(out_pack->sholder_ac_no,rPack->sholder_ac_no);
	out_pack->damt4 = rPack->damt4;
	out_pack->damt3 = tAccount.cur_frozebala;
	return 0;
}

//֧������
static int payment(ST_PACK *rPack,ST_PACK *out_pack)
{
	int ret = 0;
	int cust_id = 0;
	char accno[33]="";
	char opcode[11]="";
	char seed[32]="";
	char accpwd_plain[10]="";
	T_t_aif_account tAccount;		//���
	T_t_cif_customer tCustomer;
	T_t_pif_operator tOper;

	T_t_aif_account tAccount2;		//�տ
	T_t_cif_customer tCustomer2;
	
	memset(&tOper,0,sizeof(tOper));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tAccount2,0,sizeof(tAccount2));
	memset(&tCustomer2,0,sizeof(tCustomer2));
	
	ret = GetParameter(2006, seed);
	if(ret)
		return ret;
	
	des2src(opcode,rPack->scust_no);
	ret = DB_t_pif_operator_read_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_R;
	}

	//��֤��̬��Կ
	if(strcmp(tOper.comments,rPack->scust_limit2) != 0)
		return E_EACC_DYNA_KEY;
	//���
	if(rPack->lvol1 == 0) 		//�������Ϊ�ʺ�
	{
		des2src(accno,rPack->sbank_acc); //�˺�
		if(!strlen(accno))
			return E_INPUTNULL_ACCNO;
		
		ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		if(tAccount.act_type != ACCTYPE_PEREACC)
			return E_ACC_NOTEACC;
	}
	else
	{
		cust_id = rPack->lvol2;
		ret = DB_t_cif_customer_read_by_cut_id(cust_id, &tCustomer);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_CUSTOMER_N;
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer.cut_state != CUSTSTAT_REGIST)
			return E_CUSTOMER_LOGOUT;
		
		if(tCustomer.eaccflag[0] == '0')
			return E_EACCNO_LOGOUT;
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(cust_id, ACCTYPE_PEREACC, &tAccount);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}		
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
		return E_EACCNO_LOGOUT;

	ret = decrypt_elec_card_pwd(0,seed,tAccount.password,accpwd_plain);
	if(ret)
		return E_PWD_DECRYPT;
	if(strcmp(accpwd_plain,rPack->scust_limit)!=0)
		return E_EACCPWD;

	//�տ
	if(rPack->lvol0 == 0)		//�տ�ʺ�����Ϊ�ʺ�
	{
		des2src(accno,rPack->sbank_acc2); //�˺�
		if(!strlen(accno))
			return E_INPUTNULL_ACCNO;
		
		ret=DB_t_aif_account_read_by_account_id(accno,&tAccount2);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		if(tAccount2.act_type != ACCTYPE_SHOPMAIN)
			return E_ACC_NOTSHOP;
	}
	else
	{
		cust_id = rPack->lvol5;
		ret = DB_t_cif_customer_read_by_cut_id(cust_id, &tCustomer2);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_CUSTOMER_N;
			else
				return E_DB_CUSTOMER_R;
		}
		if(tCustomer2.cut_state != CUSTSTAT_REGIST)
			return E_CUSTOMER_LOGOUT;
		
		if(tCustomer2.eaccflag[0] == '0')
			return E_EACCNO_LOGOUT;
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(cust_id, ACCTYPE_SHOPMAIN, &tAccount2);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}		
	}
	if(tAccount2.current_state!=ACCOUNTSTAT_REGIST)
		return E_EACCNO_LOGOUT;
	
	char sysdate[9]="";
	char logicdate[9]="";
	char systime[7]="";
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
		return ret;

	T_t_tif_eacctradeserial tEaccts;
	memset(&tEaccts,0,sizeof(tEaccts));
	//��ȡ�����ʺŽ�����ˮ��
	ret = DB_t_tif_eacctradeserial_read_by_logic_date_and_ordercode_and_opcode(logicdate, rPack->sholder_ac_no, 
		rPack->scust_no, &tEaccts);
	if(ret)
	{
		if(DB_NOTFOUND !=ret)		
			return E_DB_TRADESERIAL_R;
		else		//���足��,ֱ��֧������
		{
			if(amtcmp(tAccount.cur_freebala, rPack->damt4) <0)
				return E_EACC_BALANCE_SHORTAGE;			
		}			
	}
	else
	{
		if(tEaccts.frozencode[0] != '1')
			return E_EACC_ORDERCODE;
		if(amtcmp(tEaccts.frozenmoney, rPack->damt4) <0)			//����Ľ��С�ڽ��׽��
			return E_EACC_BALANCE_SHORTAGE;	

		//��ǰ�ʻ��Ŀ����������,����������
		tAccount.cur_freebala += tEaccts.frozenmoney;
		tAccount.cur_frozebala -= tEaccts.frozenmoney;
		ret = DB_t_aif_account_update_by_account_id(tAccount.account_id, &tAccount);
		if(ret)
		{
			if(DB_NOTFOUND ==ret )
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_U;
		}
	}

	double prefreebala = tAccount.cur_freebala;
	//����ˮ,����
	double dSerialNo = 0;
	InAcc	IA;
	T_t_tif_tradeserial  tradeserial;
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	tradeserial.trade_fee = rPack->damt4;		//���׽��
	tradeserial.serial_type = TXCODE_EACC_PAYMENT;
//	tradeserial.in_balance=tAccount.cur_freebala;
//	tradeserial.trade_count=tAccount.consume_count+1;		//���״���
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, rPack->semp);
	tradeserial.customer_id = tAccount.customer_id;
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	
	des2src(IA.sArrInActno[1],tAccount2.account_id);						//�̻��ʻ�
	des2src(IA.sArrInActno[5],tAccount.account_id);						//����Ǯ���ʻ�
	IA.iCardNo=tAccount.card_id;

	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}

	ret=DB_t_aif_account_read_by_account_id(tAccount.account_id,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;
	}
	sprintf(out_pack->vsmess,"ת��ǰ�������:%.2lfԪ,��ǰ�������:%.2lfԪ",prefreebala,tAccount.cur_freebala);
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
	//��¼/���µ����ʻ�������ˮ

	tEaccts.serial_no = D2I(dSerialNo);
	des2src(tEaccts.ordercode,rPack->sholder_ac_no);
	des2src(tEaccts.logic_date, logicdate);
	des2src(tEaccts.opcode,rPack->scust_no);
	des2src(tEaccts.operate_date,sysdate);
	des2src(tEaccts.operate_time,systime);
	tEaccts.frozenmoney =0;
	tEaccts.paymoney = rPack->damt4;
	des2src(tEaccts.payacc,rPack->sbank_acc);
	des2src(tEaccts.payname,tAccount.cut_name);
	des2src(tEaccts.rcvacc,rPack->sbank_acc2);
	des2src(tEaccts.rcvname,tAccount2.cut_name);
	tEaccts.tradestatus[0] = '1';
	tEaccts.frozencode[0] ='0';
	tEaccts.backoff_flag[0] ='0';
	ret = DB_t_tif_eacctradeserial_update_by_logic_date_and_ordercode_and_opcode(logicdate, rPack->sholder_ac_no, 
		rPack->scust_no, &tEaccts);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			ret = DB_t_tif_eacctradeserial_add(&tEaccts);
			if (ret)
			{
				writelog(LOG_ERR,"ret[%d]",ret);
				if(DB_REPEAT==ret)
					return E_DB_TRADESERIAL_E;
				else
					return E_DB_TRADESERIAL_I;
			}
		}
		else
			return E_DB_TRADESERIAL_U;
	}

	des2src(out_pack->sholder_ac_no,rPack->sholder_ac_no);		//������
	out_pack->damt1 =tAccount.cur_freebala;				//��ǰ�������
	out_pack->damt4 = rPack->damt4;			//���׽��
	return 0;
}
//����
static int backoff(ST_PACK *rPack,ST_PACK *out_pack)
{	
	int ret = 0;
	char opcode[11]="";
	char sysdate[9]="";
	char logicdate[9]="";
	char systime[7]="";
	
	T_t_aif_account tAccount;		//���
	T_t_aif_account tAccount2;		//�տ
	T_t_tif_eacctradeserial tEaccts;
	T_t_pif_operator tOper;

	memset(&tAccount,0,sizeof(tAccount));
	memset(&tAccount2,0,sizeof(tAccount2));
	memset(&tEaccts,0,sizeof(tEaccts));
	memset(&tOper,0,sizeof(tOper));

	des2src(opcode,rPack->scust_no);
	ret = DB_t_pif_operator_read_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_R;
	}

	//��֤��̬��Կ
	if(strcmp(tOper.comments,rPack->scust_limit2) != 0)
		return E_EACC_DYNA_KEY;			

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
		return ret;

	ret = DB_t_tif_eacctradeserial_read_by_logic_date_and_ordercode_and_opcode(logicdate,rPack->sholder_ac_no,
			opcode,&tEaccts);
	if(ret)
	{
		if(DB_NOTFOUND ==ret)		
			return E_DB_TRADESERIAL_N;
		else		//���足��,ֱ��֧������
			return E_DB_TRADESERIAL_R;
	}

	if(tEaccts.tradestatus[0] != '1' || tEaccts.backoff_flag[0] == '1')
		return E_ACC_BACKOFF;
	
	ret=DB_t_aif_account_read_by_account_id(tEaccts.payacc,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	ret=DB_t_aif_account_read_by_account_id(tEaccts.rcvacc,&tAccount2);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	double prefreebala = tAccount.cur_freebala;
	//����ˮ,����
	double dSerialNo = 0;
	InAcc	IA;
	T_t_tif_tradeserial  tradeserial;
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	tradeserial.trade_fee = tEaccts.paymoney;		//����
	tradeserial.serial_type = TXCODE_EACC_BACKOFF;
//	tradeserial.in_balance=tAccount.cur_freebala;
//	tradeserial.trade_count=tAccount.consume_count+1;		//���״���
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, rPack->semp);
	tradeserial.customer_id = tAccount.customer_id;
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	
	des2src(IA.sArrInActno[1],tAccount2.account_id);						//�̻��ʻ�
	des2src(IA.sArrInActno[5],tAccount.account_id);						//����Ǯ���ʻ�
	IA.iCardNo=tAccount.card_id;

	IA.dArrInAmt[0]=tradeserial.trade_fee;
//	IA.iTxFlag = 1;
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}

	ret=DB_t_aif_account_read_by_account_id(tAccount.account_id,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;
	}
	sprintf(out_pack->vsmess,"����ǰ�������:%.2lfԪ,��ǰ�������:%.2lfԪ",prefreebala,tAccount.cur_freebala);
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
	//��¼/���µ����ʻ�������ˮ

	tEaccts.backoff_flag[0] ='1';			//��Ϊ������ʶ
	ret = DB_t_tif_eacctradeserial_update_by_logic_date_and_ordercode_and_opcode(logicdate, rPack->sholder_ac_no, 
		rPack->scust_no, &tEaccts);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_TRADESERIAL_N;
		else 
			return E_DB_TRADESERIAL_U;
	}

	des2src(out_pack->sholder_ac_no,rPack->sholder_ac_no);		//������
	out_pack->damt4 = tEaccts.paymoney;			//�������
	out_pack->damt1 = tAccount.cur_freebala;		//��ǰ�������
	return 0;
}

//�ⶳ�˻�
static int frozenoff(ST_PACK *rPack,ST_PACK *out_pack)
{
	int ret = 0;
	char opcode[11]="";
	char sysdate[9]="";
	char logicdate[9]="";
	char systime[7]="";
	T_t_aif_account tAccount;
	T_t_pif_operator tOper;
	T_t_tif_eacctradeserial tEaccts;

	memset(&tOper,0,sizeof(tOper));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tEaccts,0,sizeof(tEaccts));
	
	des2src(opcode,rPack->scust_no);
	ret = DB_t_pif_operator_read_by_oper_code(opcode, &tOper);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_OPERATOR_N;
		else
			return E_DB_OPERATOR_R;
	}

	if(strcmp(tOper.comments,rPack->scust_limit2) != 0)
		return E_EACC_DYNA_KEY;

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
		return ret;
	
	ret = DB_t_tif_eacctradeserial_read_by_logic_date_and_ordercode_and_opcode(logicdate,rPack->sholder_ac_no,
			opcode,&tEaccts);
	if(ret)
	{
		if(DB_NOTFOUND ==ret)		
			return E_DB_TRADESERIAL_N;
		else		
			return E_DB_TRADESERIAL_R;
	}

	if(tEaccts.frozencode[0] != '1')
		return E_ACC_FROZENOFF;

	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(tEaccts.payacc,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_R;
	}
	
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		DB_t_aif_account_free_lock_cur();
		return E_EACCNO_LOGOUT;
	}

	if(tAccount.act_type != ACCTYPE_PEREACC)
	{
		DB_t_aif_account_free_lock_cur();
		return E_ACC_NOTEACC;
	}
	
	tAccount.cur_freebala += tEaccts.frozenmoney;
	tAccount.cur_frozebala -= tEaccts.frozenmoney;
	ret = DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else
			return E_DB_ACCOUNT_U;
	}
	DB_t_aif_account_free_lock_cur();
	
	//������ˮ
	T_t_tif_tradeserial  tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	double dSerialNo = 0;
	
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
	tradeserial.trade_fee = tEaccts.frozenmoney;		//������
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_EACC_FROZENOFF;
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, rPack->semp);
	tradeserial.customer_id = tAccount.customer_id;
//	tradeserial.in_balance=tAccount.cur_freebala+rPack->damt4;
//	tradeserial.out_balance=tAccount.cur_freebala;
//	tradeserial.trade_count=tAccount.consume_count;		//���״���������
	tradeserial.sys_id = 0;		
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	//���µ����˻�������ˮ����
	tEaccts.frozencode[0] = '2';					//����Ľ���Ѿ��ⶳ
	ret = DB_t_tif_eacctradeserial_update_by_logic_date_and_ordercode_and_opcode(logicdate,rPack->sholder_ac_no,
			opcode,&tEaccts);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_NOTFOUND==ret)
			return E_DB_TRADESERIAL_N;
		else
			return E_DB_TRADESERIAL_U;
	}	
	des2src(out_pack->sholder_ac_no,rPack->sholder_ac_no);
	out_pack->damt4 = tEaccts.frozenmoney;
	out_pack->damt1 = tAccount.cur_freebala;
	out_pack->damt3 = tAccount.cur_frozebala;
	return 0;
}

int F846339(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);

	int transcode = rPack->lvol3;		//������
	switch(transcode)
	{
		case 10:						//ǩ��
			ret = login(rPack,out_pack);
			break;
		case 11:
			ret = checkbala(rPack,out_pack);
			break;
		case 12:
			ret = frozen(rPack,out_pack);
			break;
		case 13:
			ret = payment(rPack,out_pack);
			break;
		case 14:
			ret = backoff(rPack,out_pack);
			break;
		case 15:
			ret = frozenoff(rPack,out_pack);
			break;
		default :
			ret =-1;
	}

	if(ret)
		return ret;
	
	SetCol(handle,0);
 	SetCol(handle,F_LVOL4,F_DAMT0,F_DAMT1,F_DAMT2,F_DAMT3,F_DAMT4,F_SNAME,F_SBANK_ACC,F_SHOLDER_AC_NO,F_SCUST_LIMIT2,F_VSMESS,0);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


