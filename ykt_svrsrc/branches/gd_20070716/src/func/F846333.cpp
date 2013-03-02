/* --------------------------------------------
 * ��������: 2008 8 21
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: �����ʻ���ֵ
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

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//��������
	IA->iTxCnt=0;					//���״���
	IA->dInCardBala=0;				//�뿨ֵ
	IA->dOutCardBala=0;							//����ֵ

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

int F846333(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char sysdate[9]="";
	char logicdate[9]="";
	char systime[7]="";
	char accno[21]="";

	int	type=0;
	InAcc	IA;
	char sMaxEAccBalance[20]="";
	double dMaxEAccBalance = 0;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_cif_customer tCustomer;

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);

	memset(&IA,0,sizeof(IA));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tCustomer,0,sizeof(tCustomer));
	
	des2src(accno,rPack->sbank_acc); //�˺�
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	
	if(amtcmp(rPack->damt0,0)<=0)   //��ֵ���
		return E_INPUT_AMT;
		
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	//����˻�
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		return E_EACCNO_LOGOUT;
	}
	
	double accbefbal=tAccount.cur_bala;
	
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
	
	tradeserial.trade_fee = rPack->damt0;					//��ֵ���
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
		return ret;
//
	ret=GetParameter(GLOBE_MAXEACCBALANCE,sMaxEAccBalance);
	if(ret)
		return ret;
	dMaxEAccBalance=atof(sMaxEAccBalance);

	if(amtcmp(tAccount.cur_bala+tradeserial.trade_fee,dMaxEAccBalance)>0)
		return E_AMT_EXCEED_MAX;
	
	type=rPack->lvol9;										//��������
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(type)
	{
		case TYPE_CASH:	//�ֽ�
			IA.iArrInFeeSwitch[1]=1;
			break;
		case TYPE_BILL:	//֧Ʊ
			IA.iArrInFeeSwitch[2]=1;
			break;
		case TYPE_FUNDBOOK:	//���ѱ�
			IA.iArrInFeeSwitch[3]=1;
			break;
		default:
			return E_INPUT_DEPOSIT_TYPE;
	}

	double dSerialNo = 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR," getNewUniqNo ERRCODE = [%d]",ret);
		return ret;
	}
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_EACC_SAVING_CASH;
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, rPack->semp);
	tradeserial.customer_id = tCustomer.cut_id;
//	tradeserial.in_balance=tAccount.cur_freebala;
//tradeserial.trade_count=tAccount.consume_count+1;		//���״���
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	switch(type)
	{
		case TYPE_CASH:		//�ֽ�
			break;
 		case TYPE_BILL:		//֧Ʊ
		case TYPE_FUNDBOOK:	//���ѱ�
		case TYPE_OTHER:	//����
 			tSavdtl.amount=rPack->damt0;				//������
				break;
			des2src(tSavdtl.bill_no,rPack->sphone);		//Ʊ�ݺ���
			if(strlen(tSavdtl.bill_no)<1)
				return E_INPUT_BILLNO;
			
			tSavdtl.card_no=tAccount.card_id;	//����
			des2src(tSavdtl.oper_no,rPack->semp);	//����Ա
			tSavdtl.seqno=tradeserial.serial_no;			//��ˮ��
			des2src(tSavdtl.tx_date,sysdate);			//��������
			des2src(tSavdtl.tx_time,systime);			//����ʱ��
			tSavdtl.cnt=1;								//Ʊ������
			tSavdtl.bill_type=type;						//Ʊ������
			tSavdtl.tx_code=tradeserial.serial_type;		//������
			ret=DB_t_tif_savdtl_add(&tSavdtl);
			if(ret)
			{
				if(DB_REPEAT==ret)
					return E_DB_SAVDTL_E;
				else
					return E_DB_SAVDTL_I;
			}
			break;
		default:
			return E_TXCODE_NOT_EXIST;
	}
	
	des2src(IA.sArrInActno[5],tAccount.account_id);						//�ʻ�
//	writelog(LOG_ERR,"account_id[%s]",IA.sArrInActno[5]);
//	IA.iCardNo=tAccount.card_id;
//	IA.iFeeType=tCustomer.fee_type;
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
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_R;
	}
	
	sprintf(outPack->vsmess,"��ֵǰ�ʻ����%.2lfԪ,��ֵ���%.2lf,��ǰ�ʻ����:%.2lfԪ",accbefbal,tradeserial.trade_fee,tAccount.cur_bala);
	writelog(LOG_DEBUG,outPack->vsmess);
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	SetCol(handle,F_DAMT2,F_LSERIAL1,F_VSMESS,0);		

	outPack->damt2=tAccount.cur_bala;		//����ֵ
	outPack->lserial1=tradeserial.serial_no;			//��ˮ��
	PutRow(handle,outPack,pRetCode,szMsg);

	return 0;

}

