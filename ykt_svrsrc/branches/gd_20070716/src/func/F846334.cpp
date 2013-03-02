/* --------------------------------------------
 * ��������: 2008 8 21
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: �����ʻ�ȡ��
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
	//���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
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

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//��������
//	IA->iTxCnt=p->trade_count;					//���״���
//	IA->dInCardBala=p->in_balance;				//�뿨ֵ
//	IA->dOutCardBala=-1;							//����ֵ
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

int F846334(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";

	InAcc IA;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_cif_customer tCustomer;
	
	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tCustomer,0,sizeof(tCustomer));
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	
	des2src(accno,rPack->sbank_acc);		//�˻�
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	
	if(amtcmp(rPack->damt0,0)<=0)		//ȡ����
		return E_INPUT_AMT;

	//ȡ�ʻ���Ϣ
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"accno[%s]",accno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		return E_EACCNO_LOGOUT;
	}	
	double accbefbal=tAccount.cur_bala;
	char seedkey[33]="";
	char inpwd_crypt[65]="";
	char inpwd_plain[65]="";
	char dbpwd_plain[65]="";
	des2src(inpwd_crypt,rPack->snote2);
	if(!strlen(inpwd_crypt))
		return E_INPUTNULL_PWD;
	ret=GetParameter(2006,seedkey);
	if(ret)
		return ret;
	ret=decrypt_elec_card_pwd(0,seedkey,inpwd_crypt,inpwd_plain);
	if(ret)
		return E_EACCPWD;
	ret=decrypt_elec_card_pwd(0,seedkey,tAccount.password,dbpwd_plain);
	if(ret)
		return E_PWD_DECRYPT;
	writelog(LOG_ERR,"input pwd[%s],db pwd[%s]",inpwd_plain,dbpwd_plain);
	if(strcmp(inpwd_plain,dbpwd_plain)!=0)
		return E_EACCPWD;
	if(tAccount.stoppayflag[0]=='1')
		return E_EACC_STOPPAY;	
	if(amtcmp(tAccount.cur_freebala,rPack->damt0)<0)
	{
		writelog(LOG_ERR,"eAcc balance[%lf] amount[%lf]",tAccount.cur_freebala,rPack->damt0);
		return E_BALANCE_SHORTAGE;
	}	
	//���ͻ�
	ret=DB_t_cif_customer_read_by_cut_id(tAccount.customer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tAccount.customer_id);
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state != CUSTSTAT_REGIST)
	{
		return E_CUSTOMER_LOGOUT;
	}
	tradeserial.trade_fee = rPack->damt0;					//ȡ����

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
		return ret;
	
	IA.iArrInFeeSwitch[1]=1;

	double dSerialNo = 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  	//�����ˮ��
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}

	tradeserial.serial_no = D2I(dSerialNo);						//��ˮ��
	tradeserial.other_seri_no = 0;							//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_EACC_CASH_DEPOSIT;		//���״���
	tradeserial.serial_state = SERISTAT_DEBT;					//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);				//��������
	des2src(tradeserial.operate_time,systime);				//����ʱ��
	des2src(tradeserial.collect_date,sysdate);					//�ɼ�����
	des2src(tradeserial.collect_time,systime);					//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);				//��������
	des2src(tradeserial.enteract_time,systime);				//����ʱ��
	tradeserial.card_id = tAccount.card_id;						//����
	tradeserial.customer_id = tAccount.customer_id;					//�ͻ���ʶ
	//tradeserial.in_balance=tAccount.cur_freebala;					//�뿨ֵ
	//tradeserial.trade_count=tAccount.consume_count+1;				//���״���
	des2src(tradeserial.oper_code , rPack->semp);		//����Ա����
	tradeserial.sys_id = 0;									//�ⲿϵͳ��ʶ

	IA.iCardNo=tAccount.card_id;
//	IA.iFeeType=tCustomer.fee_type;
	strcpy(IA.sArrInActno[5],tAccount.account_id);		//�˺�
	IA.dArrInAmt[0]=tradeserial.trade_fee;					
/*
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;
*/
	//	����������ģ��
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"accno[%s]",accno);
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	sprintf(outPack->vsmess,"ȡ��ǰ�ʻ����%.2lfԪ,ȡ����%.2lf,��ǰ�ʻ����:%.2lfԪ",accbefbal,tradeserial.trade_fee,tAccount.cur_bala);
	writelog(LOG_DEBUG,outPack->vsmess);
	//	���뿨������ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_VSMESS,0);	
	outPack->lserial1=tradeserial.serial_no;								//��ˮ��
	outPack->damt2 = tAccount.cur_bala;
	PutRow(handle,outPack,pRetCode,szMsg);

	return 0;
}

