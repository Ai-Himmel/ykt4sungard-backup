/* --------------------------------------------
 * ��������: 2008 8 21
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: �����ʻ���������
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
int CheckIdno(char *idtype,char *idno,int custid)
{
	//�˶�֤��
	T_t_cif_customer customer;
	memset(&customer,0,sizeof(customer));
	int ret=DB_t_cif_customer_read_by_cut_id(custid,&customer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_CUSTOMER_NO_EXIST;
		else
			return E_DB_CUSTOMER_R;
	}
	if(strlen(customer.man_id))
	{
		if(strlen(customer.man_idtype))
		{
			if(customer.man_idtype[0]!=idtype[0])
				return E_DIFF_IDTYPE;
		}
		if(strcmp(customer.man_id,idno)!=0)
		{
			return E_DIFF_IDNO;
		}
	}
	return 0;
}

int F846338(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[9]="";
	char sysdate[9]="";
	char systime[7]="";
	char accno[21]="";
	char idtype[2];
	char idno[61]="";

	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
    
	des2src(idtype,rPack->smarket_code2);
	des2src(idno,rPack->semail2);

	des2src(accno,rPack->sbank_acc);
	if(!strlen(accno))
		return E_INPUTNULL_ACCNO;

//	char key[17]="";
//	char newpwd_plain[33]="";
	char newpwd_crypt[65]="";
//	strcpy(key,STATIC_SEED_KEY);
	des2src(newpwd_crypt,rPack->snote2);
    if(!strlen(newpwd_crypt))
       return E_INPUTNULL_PWD;
//	EncodePwd(key,newpwd_plain,newpwd_crypt,0);
	//ȡ�ʻ���Ϣ
	T_t_aif_account tAccount;	
	memset(&tAccount,0,sizeof(tAccount));
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
	ret=CheckIdno(idtype,idno,tAccount.customer_id);
	if(ret)
	{
		DB_t_aif_account_free_lock_cur();
		return ret;
	}
	des2src(tAccount.password,newpwd_crypt);
	ret=DB_t_aif_account_update_lock_by_cur(&tAccount);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_ACCOUNT_N;
		else 
			return E_DB_ACCOUNT_U;
	}

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
		return ret;
	
	double dUniqno= 0;
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		return ret;
	}
	
	T_t_tif_tradeserial  tradeserial;
	memset(&tradeserial,0,sizeof(tradeserial));
	
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	tradeserial.serial_type = TXCODE_EACC_INITPW;								//��������
	tradeserial.serial_no = D2I(dUniqno);										//��ˮ��
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//��ˮ״̬
	tradeserial.card_id = tAccount.card_id;											//���׿���
	tradeserial.customer_id=tAccount.customer_id;									//�ͻ���
	des2src(tradeserial.oper_code,rPack->semp);						//����Ա

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			return  E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	
	SetCol(handle,F_LSERIAL1,F_VSMESS,0);	
	outPack->lserial1=tradeserial.serial_no;

	sprintf(outPack->vsmess,"%s���������óɹ�",tAccount.cut_name);
	PutRow(handle,outPack,pRetCode,szMsg);
	return 0;
}

