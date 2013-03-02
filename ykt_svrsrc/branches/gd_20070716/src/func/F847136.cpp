/* --------------------------------------------
 * ��������: F847136.sqc
 * ��������: 2007-8-8
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: ���� �̻���
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_
 #include <string.h>
 #include <stdio.h>
 #include "pubfunc.h"
 #include "pubdb.h"
 #include "pubdef.h"
 #include "errdef.h"
 #include "dbfunc.h"
 #include "fdsqc.h"
 #include "dbfunc_foo.h"

int F847136(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret = 0;
	char logicdate[11]="";								//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	
	int card_id=0;
	char cardphyid[12]="";
	
	T_t_pif_card tCard;
	T_t_aif_account  tAccount;
	T_t_tif_tradeserial  tradeserial;
	T_t_cif_customer   tCustomer;
	double dUniqNo = 0;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&IA,0,sizeof(IA));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,F_LSERIAL1,0);
	card_id = rPack->lvol2;									//�ͻ����
	des2src(cardphyid,rPack->scust_auth);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	if(card_id<1)
	{
		*pRetCode=E_CARDNO_NOT_EXIST;
		goto L_RETU;
	}
	//���ͻ���Ϣ���ж��Ƿ���Է��п�
	//ע����
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode=E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if('0'==tCard.state_id[CARDSTAT_TYPE_LOST])
	{
		//����������Ƿ�һ��
		trim(cardphyid);
		trim(tCard.physical_no);
		if(strcmp(tCard.physical_no,cardphyid)!=0)
		{
			DB_t_pif_card_free_lock_by_cur();
			writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",tCard.physical_no,cardphyid);
			*pRetCode= E_CARD_PHYNO_DIFFER;
			goto L_RETU;
		}
	}
	des2src(tCard.state_id,CARDSTAT_LOGOUT);		//ע��
	des2src(tCard.end_time,sysdate);			//ע������
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",tCard.card_id);
		*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	//	�����˻���Ϣ����д����
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(tCard.cosumer_id,ACCTYPE_SHOPMAIN,&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_customer_id_and_act_type err,errcod=[%d]",ret);
		*pRetCode = E_DB_ACCOUNT_R;
		goto L_RETU;
	}

	tAccount.card_id=0;
	tAccount.card_type=0;
	
	ret=DB_t_aif_account_update_by_account_id(tAccount.account_id,&tAccount);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_update_by_account_id err,errcod=[%d]",ret);
		*pRetCode = E_DB_ACCOUNT_U;
		goto L_RETU;
	}

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqNo);  						//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = D2I(dUniqNo);											//��ˮ��
	tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��

	tradeserial.maindevice_id = rPack->lvol6;												//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol7;													//�ɼ��豸��ʶ
	tradeserial.card_id = tCard.card_id;													//����
	des2src(tradeserial.showid,tCard.showid);												//��ʾ����
	tradeserial.purse_id = PURSE_NO_ONE;												//Ǯ����
	tradeserial.customer_id = tCard.cosumer_id;													//�ͻ���ʶ

	des2src(tradeserial.oper_code , rPack->scust_limit);			//����Ա����
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	tradeserial.trade_count=0;														//��ǰ�����״���
	// ���뽻����ˮ��
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
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��
	sprintf(out_pack->vsmess,"�̻���%d����%d���ճɹ�",rPack->lvol0,card_id);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

