/* --------------------------------------------
 * ��������: F847132.c
 * ��������: 2005-12-7
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �·�����
 * --------------------------------------------
 * �޸�����: 2008-3-22
 * �޸���Ա: ����
 * �޸�����: �޸��·��������ܣ������ֱ�Ӽ�������˻�
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"

static int do_running_account(T_t_tif_subsidy *tSubsidy,InAcc *IA)
{
	int ret;
	int subsidy_no;
	T_t_tif_subsidy card_subsidy;
	T_t_aif_account tAccount;

	// �������е���Ĳ���
	ret = DB_t_tif_subsidy_open_select_for_update_by_c4_and_batch_no_and_subsidy_no(tSubsidy->batch_no,0);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSIDY_N;
		return E_DB_SUBSIDY_R;
	}
	while(1)
	{
		memset(&card_subsidy,0,sizeof card_subsidy);
		ret = DB_t_tif_subsidy_fetch_select_by_c4(&card_subsidy);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
				break;
			return E_DB_SUBSIDY_R;
		}
		ret = DB_t_aif_account_read_by_card_id_and_purse_id(card_subsidy.card_no,PURSE_NO_ONE,&tAccount);
		if(ret)
		{
			DB_t_tif_subsidy_close_select_by_c4();
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_N;
			return E_DB_ACCOUNT_R;
		}
		// ����
		des2src(IA->sArrInActno[0],tAccount.account_id);
		if(amtcmp(card_subsidy.amount,0.0) < 0)
		{
			IA->dArrInAmt[0] = -card_subsidy.amount;
		}
		else
		{
			IA->dArrInAmt[0] = card_subsidy.amount;
		}
		//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
		ret=AccountProcess(IA);
		if(ret)
		{
			DB_t_tif_subsidy_close_select_by_c4();
			writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
			return ret;
		}
		// ������ֻ��������ˣ�����ǲ�����Ϣ״̬
		ret = DB_t_tif_subsidy_update_lock_by_c4(&card_subsidy);
		if(ret)
		{
			return E_DB_SUBSIDY_U;
		}
	}
	return 0;	
}

static int process(InAcc *IA,T_t_tif_tradeserial *p,T_t_tif_subsidy *tSubsidy)
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
	//if(p->trade_fee<0)	p->trade_fee=0-p->trade_fee;

	return do_running_account(tSubsidy,IA);
}


int F847132(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int i=0;
	int iTotalCnt=0;
	double dTotalAmt=0.0;
	double dSerialNo = 0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	char sMsg[256]="";
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_tif_subsidy  	tSubsidy;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_tif_meslist tMesList;
	T_t_pif_device t_device;
	T_t_pif_syskey tSyskey;

	memset(&t_device,0,sizeof t_device);
	memset(&tMesList,0,sizeof tMesList);
	memset(&tSavdtl,0,sizeof(tSavdtl));
	memset(&tSubsidy,0,sizeof(tSubsidy));
	memset(&tSyskey,0,sizeof tSyskey);
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&IA,0,sizeof(IA));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSMESS,0);
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);					//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit)<1)
	{
		*pRetCode=E_INPUT_BATCH_NO;
		goto L_RETU;
	}
	if(strlen(rPack->scust_no)<1)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	//�����������
	if(amtcmp(rPack->damt0,0)==0)
	{
		*pRetCode=E_INPUT_AMT;
		goto L_RETU;
	}
	des2src(tSubsidy.summary,rPack->semail);		//����ժҪ
	if(strlen(rPack->semail)<1)
	{
		*pRetCode=E_INPUT_SUMMARY;
		goto L_RETU;
	}
	
	des2src(tSubsidy.batch_no,rPack->scust_limit);
	tSubsidy.bill_type=rPack->lvol2;					//Ʊ������
	des2src(tSubsidy.bill_no,rPack->scust_auth2);	//Ʊ�ݺ���
	tSubsidy.amount=rPack->damt0;				//�������
	des2src(tSubsidy.subsidytype,rPack->smain_flag);//������־(0��ֵ1��ֵ)
	des2src(tSubsidy.subsidytype,"1");			//������־(0��ֵ1��ֵ)
	des2src(tSubsidy.broker_id,rPack->sname);		//���������֤��
	des2src(tSubsidy.broker_name,rPack->semail2);	//����������

	IA.dArrInAmt[0]=tradeserial.trade_fee;
	switch(tSubsidy.bill_type)
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
			*pRetCode=E_INPUT_DEPOSIT_TYPE;
			goto L_RETU;
	}

	/*
	ret=get_batch_no_by_subsidy_no(tSubsidy.subsidy_no,tSubsidy.batch_no);
	if(ret)
	{
		*pRetCode = E_DB_SUBSIDYTMP_R;
		goto L_RETU;
	}
	*/
	// �·�����ʱ���������κ�
	/*
	ret=judge_with_max_subsidy_no_within_new(tSubsidy.subsidy_no);
	if(ret)
	{
		*pRetCode = E_SUBSIDY_DOWN_ERROR;
		goto L_RETU;
	}
	*/
	ret=stat_subsidy_amount_by_batch_no(tSubsidy.batch_no, &iTotalCnt,&dTotalAmt);
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	
	if(iTotalCnt!=rPack->lvol3)
	{
		strcpy(szMsg,"���������뵼������ݲ���");
		*pRetCode=E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	if(amtcmp(dTotalAmt,rPack->damt0)!=0)
	{
		strcpy(szMsg,"�����ܽ���뵼��Ĳ������ݲ���");
		*pRetCode=E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"download subsidy batch_no : %s",tSubsidy.batch_no);
	des2src(tSubsidy.tx_date,sysdate);
	des2src(tSubsidy.tx_time,systime);

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  					//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(dSerialNo);											//��ˮ��
	tradeserial.other_seri_no = 0;															//�ϴ�����ˮ��
	if(amtcmp(dTotalAmt,0.0)>0)
		tradeserial.serial_type = TXCODE_SET_SUBSIDY;
	else tradeserial.serial_type = TXCODE_DESUBSIDY_DOWN;
	
	tradeserial.serial_state = SERISTAT_DEBT;				//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);			//��������
	des2src(tradeserial.operate_time,systime);			//����ʱ��
	des2src(tradeserial.collect_date,sysdate);				//�ɼ�����
	des2src(tradeserial.collect_time,systime);				//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);			//��������
	des2src(tradeserial.enteract_time,systime);			//����ʱ��
	tradeserial.maindevice_id = rPack->lvol6;				//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol7;					//�ɼ��豸��ʶ
	des2src(tradeserial.oper_code , rPack->scust_no);		//����Ա����
	tradeserial.sys_id = 0;								//�ⲿϵͳ��ʶ
	// ���÷������
	tradeserial.trade_fee = dTotalAmt;
	switch(tSubsidy.bill_type)
	{
		case TYPE_CASH:		//�ֽ�
			break;
 		case TYPE_BILL:		//֧Ʊ
		case TYPE_FUNDBOOK:	//���ѱ�
 			tSavdtl.amount=rPack->damt0;				//������
 			if(amtcmp(tSavdtl.amount,0)==0)
				break;
			des2src(tSavdtl.bill_no,tSubsidy.bill_no);		//Ʊ�ݺ���
			if(strlen(tSavdtl.bill_no)<1)
			{
				*pRetCode=E_INPUT_BILLNO;
				goto L_RETU;
			}
			tSavdtl.card_no=0;							//����
			des2src(tSavdtl.oper_no,rPack->scust_limit);	//����Ա
			tSavdtl.seqno=tradeserial.serial_no;			//��ˮ��
			des2src(tSavdtl.tx_date,sysdate);			//��������
			des2src(tSavdtl.tx_time,systime);			//����ʱ��
			tSavdtl.cnt=1;								//Ʊ������
			tSavdtl.bill_type=tSubsidy.bill_type;			//Ʊ������
			tSavdtl.tx_code=tradeserial.serial_type;		//������
			ret=DB_t_tif_savdtl_add(&tSavdtl);
			if(ret)
			{
				if(DB_REPEAT==ret)
					*pRetCode = E_DB_SAVDTL_E;
				else
					*pRetCode = E_DB_SAVDTL_I;
				goto L_RETU;
			}
			break;
		default:
			*pRetCode=E_INPUT_DEPOSIT_TYPE;
			goto L_RETU;
	}
	IA.iFeeType=1;				//Ĭ��ֵ
	//֧�ָ����ۿ�
	if(tradeserial.trade_fee<0)
		tradeserial.trade_fee=-tradeserial.trade_fee;
	IA.dArrInAmt[0]=tradeserial.trade_fee;

	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	IA.iArrInFeeSwitch[6]=rPack->lvol6;
	IA.iArrInFeeSwitch[7]=rPack->lvol7;
	IA.iArrInFeeSwitch[8]=rPack->lvol8;
	IA.iArrInFeeSwitch[9]=rPack->lvol9;
	IA.iArrInFeeSwitch[10]=rPack->lvol10;

	// �����˻���Ϣ
	ret=process(&IA,&tradeserial,&tSubsidy);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"��ˮ��:%d ",IA.iSerialNo);
	// writelog(LOG_DEBUG,"out tx type count %d",IA.iOutTxTypeCnt);
	/*
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	*/
	sprintf(sMsg,",��%d��",iTotalCnt);
	strcat(out_pack->vsmess,sMsg);
	// strcat(out_pack->vsmess,sMsg);
	// writelog(LOG_DEBUG,out_pack->vsmess);
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
	
	// �㲥���ز�����������
	memset(&tMesList,0,sizeof tMesList);
	tMesList.funid=930077;
	tMesList.level = MESLIST_PRIORITY_REALTIME;
	tMesList.msgtype = MESLIST_TYPE_NORMAL;
	tMesList.max_send_cnt = 5;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=E_DB_MESLIST_I;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		return ret;
	}

////////////////////////����
	ret=DB_t_pif_device_open_select_by_c5_and_devtype_and_phytype("5301",1001);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_open_select_by_c5_and_devtype_and_phytype error,ret=[%d]",ret);
		*pRetCode = E_DB_DEVICE_R;
		goto L_RETU;
	}

	while(1)
	{
		// ��ʼ����������
		ret=DB_t_pif_device_fetch_select_by_c5(&t_device);
		if (ret)    
		{
			DB_t_pif_device_close_select_by_c5();
			db_chk_err(__FILE__,__LINE__,&sqlca);
			if(DB_NOTFOUND==ret)
			{
				break;
			}
			else
			{
				*pRetCode=E_DB_DEVICE_R;
				writelog(LOG_ERR,"DB_t_pif_device_fetch_select_by_c5 err [%d]",ret);
				goto L_RETU;
			}
		}
		
		if(t_device.state_id >= DEVISTAT_LOGOUT)   //�豸�Ѿ�ע��
			continue;
		tMesList.devid = t_device.device_id;
		tMesList.device_id= t_device.subsystem_id;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=E_DB_MESLIST_I;
			DB_t_pif_device_close_select_by_c5();
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			return ret;
		}
	}

	
	// ��ס���κ�
	ret = DB_t_pif_syskey_read_lock_by_cur_and_key_code(KEYTYPE_TIF_SUBSIDY_NO,&tSyskey);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_SYSKEY_N;
		else
			*pRetCode = E_DB_SYSKEY_R;
		goto L_RETU;
	}
	ret = calc_import_max_subsidy_no(tSubsidy.batch_no,tSubsidy.oper_code,&tSubsidy.subsidy_no);
	if(ret)
	{
		DB_t_tif_subsidy_close_select_by_c4();
		return ret;
	}
	writelog(LOG_DEBUG,"download subsidy no[%d]",tSubsidy.subsidy_no);
	ret=update_subsidy_info_by_batch_no(&tSubsidy);
	if(ret)
	{
		*pRetCode = ret;
		DB_t_pif_syskey_free_lock_cur();
		writelog(LOG_ERR,"ret[%d]",ret);
		goto L_RETU;
	}
	// �ͷ����κ�
	DB_t_pif_syskey_free_lock_cur();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
