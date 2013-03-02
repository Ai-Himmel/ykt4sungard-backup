/* --------------------------------------------
 * ��������: 2008 8 21
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: �����ʻ�����
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

static int doAccount(char *cardaccno)
{
	int ret=0;
	T_t_aif_account tAccount;

	memset(&tAccount,0,sizeof(tAccount));

	ret=DB_t_aif_account_read_lock_by_cur_and_account_id(cardaccno,&tAccount);
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
	if(amtcmp(tAccount.cur_freebala,0)!=0)
	{
		writelog(LOG_ERR,"balance[%d]",tAccount.cur_freebala);
		DB_t_aif_account_free_lock_cur();
		return E_EACC_BALANCE_NOZERO;
	}
	tAccount.current_state=ACCOUNTSTAT_LOGOUT;
	getsysdate(tAccount.close_date);
	getsystime(tAccount.close_time);
	ret=DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_U;

	}
	return 0;
}
static int doCustomer(int custid,T_t_cif_customer& tCustomer)
{
	int ret=0;
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(custid,&tCustomer);
	if(ret)
	{		
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(tCustomer.cut_state!=CUSTSTAT_REGIST)
		return E_CUSTOMER_LOGOUT;
	tCustomer.eaccflag[0]='0';
	ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NOT_EXIST;
		else
			return E_DB_CUSTOMER_U;
	}
	return 0;
}
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


int F846332(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";
	double dUniqno = 0;
	
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
		
	SetCol(handle,0);

	InAcc	IA;
	memset(&IA,0,sizeof(IA));
	des2src(accno,rPack->sbank_acc);	//�����ʻ�
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;
	//ȥ�ʻ���Ϣ
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
	ret=DB_t_aif_account_read_by_account_id(accno,&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_NOTEXIST_EACCNO;
		else 
			return E_DB_ACCOUNT_R;
	}
	if(tAccount.current_state!=ACCOUNTSTAT_REGIST)
	{
		return E_EACCNO_LOGOUT;
	}	
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
		return	E_EACCPWD;
	ret=decrypt_elec_card_pwd(0,seedkey,tAccount.password,dbpwd_plain);
	if(ret)
		return E_PWD_DECRYPT;
	if(strcmp(inpwd_plain,dbpwd_plain)!=0)
		return E_EACCPWD;
	//���ͻ�
	T_t_cif_customer tCustomer;
	memset(&tCustomer,0,sizeof(tCustomer));
	ret=doCustomer(tAccount.customer_id,tCustomer);
	if(ret)
		return ret;
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);		//ҵ������
	if(ret)
		return ret;
	
	//������ˮ
	T_t_tif_tradeserial  tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  						//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		return ret;
	}
	tradeserial.serial_no = D2I(dUniqno);											//��ˮ��
	tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_EACC_CLOSE;											//���״��룻
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code, rPack->semp);										//����Ա����
	tradeserial.customer_id=tAccount.customer_id;											//�ͻ���

	tradeserial.trade_fee=tAccount.cur_bala;
	//	���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return	E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	} 	
	des2src(IA.sArrInActno[5],tAccount.account_id);							//�ʻ�
	IA.iCardNo=0;
	IA.iFeeType=0;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		return ret;
	}
	//ע���ʻ�
	ret=doAccount(accno);
	if(ret)
		return ret;
	SetCol(handle,F_LSERIAL1,F_VSMESS,0);	
	
	outPack->lserial1=tradeserial.serial_no;
	sprintf(outPack->vsmess,"�˻�[%s]�����ɹ�,���ʻ����%.2lf",tAccount.account_id,tAccount.cur_bala);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

