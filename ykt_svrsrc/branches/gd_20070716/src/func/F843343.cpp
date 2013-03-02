/* --------------------------------------------
 * ��������: F843343.sqc
 * ��������: 2007-8-8
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: �����̻���
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



int F843343(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int	hi_cutid = 0;											//�ͻ�ID
	int	hi_cuttype = 0;										//�ͻ�����
	int i=0;
	int ret = 0;
	int len = 0;
	char h_showcardid[11] = "";						//��ʾ����
	char h_password[7] = "";							//������
	double h_temp_Card_id = 0;						//����
	char seed_key[17] = "";							//������Կ
	char card_endtime[8 + 1] = "";						//������Ч��������
	char logicdate[11]="";								//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	char sTempFeeType[256]="";
	char sMsg[256]="";
	char sMaxCardBalance[20]="";
	double dMaxCardBalance=0;
	int 	type=0;										//��ֵ����
	int card_type=0;
	T_t_cif_customer tCustomer;
	T_t_pif_card tCard;

	T_t_aif_account  tAccount;
	T_t_tif_tradeserial  tradeserial;
	T_t_tif_savdtl		tSavdtl;
	T_t_pif_spefee 	tSpeFee;
	double dUniqNo = 0;
	InAcc	IA;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&IA,0,sizeof(IA));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSavdtl,0,sizeof(tSavdtl));

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCERT_NO,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,
   			       F_SORDER0,F_SORDER1,F_SORDER2,
   			       F_SHOLDER_AC_NO,F_SSTAT_TYPE,F_SSTAT_TYPE2,
   			       F_SNATION_CODE,F_SBRANCH_CODE0,F_LVOL10,F_LVOL11,
				0);
	hi_cutid = rPack->lvol0;									//�ͻ�ID
	hi_cuttype = rPack->lvol3;									//�ͻ����
	card_type=CT_MERCH;										//������
	des2src(h_showcardid,rPack->scust_no);						//��ʾ����
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//���ͻ���Ϣ���ж��Ƿ���Է��п�
	des2src(tCard.physical_no, rPack->sbank_acc);				//������
	trim(h_showcardid);
	if(strlen(h_showcardid))
	{
		ret=IsExistShowCardNo(h_showcardid);
		if(ret)
		{
			//*pRetCode = ret;
			//goto L_RETU;
		}
	}
	ret=IsExistCardByPhyCardNo(tCard.physical_no);
	if(ret)
	{
		writelog(LOG_ERR,"IsExistCardByPhyCardNo err,errcod=[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=IsExistCardByCustomId(hi_cutid);
	if (ret)
	{
		writelog(LOG_ERR,"IsExistCardByCustomId err,errcod=[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	//�õ��շ����
	memset(&tCustomer,0,sizeof tCustomer);
	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(hi_cutid, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",hi_cutid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}

	if(tCustomer.fee_type<1)
	{
		ret=DB_t_pif_spefee_read_by_dept_code_and_cut_type(tCustomer.classdept_no, tCustomer.cut_type,&tSpeFee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				tCustomer.fee_type=tCustomer.cut_type;
			}
			else
			{
				DB_t_cif_customer_free_lock_cur();
				*pRetCode=E_DB_SPEFEE_R;
				goto L_RETU;
			}
		}
		else
		{
			tCustomer.fee_type=tSpeFee.fee_type;
		}
	}
	tCustomer.use_flag[0]='1';
	//���¿ͻ�����շ�����ֶ�
	ret=DB_t_cif_customer_update_lock_by_cur(&tCustomer);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_U;
		goto L_RETU;
	}
	DB_t_cif_customer_free_lock_cur();
	ret = GetParameter(GLOBE_FLAG_TEMPCARD_FEETYPE,sTempFeeType);
	if(ret)
	{
		writelog(LOG_ERR,"GetParameter err,errcod=[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}

	//tradeserial.trade_fee =D4U5(rPack->damt0,2);

	//������Ƿ񳬹������
	//	׼�����ݲ��뿨��Ϣ��
	memcpy(seed_key,STATIC_SEED_KEY,16);			//��������Կ


	if(strlen(rPack->sdate0)==0)
	{
		*pRetCode=E_TB_CUSTOMER_NO_ENDTIME;
		goto L_RETU;
	}
	else
	{
		ret=IsInvalidDateTime(rPack->sdate0,"YYYYMMDD");
		if(ret)
		{
			*pRetCode = E_INPUT_DATE;
			goto L_RETU;
		}
		if(strncmp(rPack->sdate0,sysdate,8)<=0)
		{
			*pRetCode=E_INPUT_DATE;
			goto L_RETU;
		}
		des2src(card_endtime,rPack->sdate0);
	}
	//	Ĭ������, ��ʼȡ���֤�ĺ�6λ, û�����֤����666666.
	if(strcmp(tCustomer.man_idtype,"1")==0)
	{
		get_init_passwd_by_man_id(tCustomer.man_id,h_password);
	}
	else
		strcpy(h_password,DEFAULT_CUST_PWD);
	ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//��ȡ��󿨺�
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	tCard.type_id=card_type;
	tradeserial.serial_type = TXCODE_MERCH_OPEN;

	tCard.card_id = D2I(h_temp_Card_id);										//����
	des2src(tCard.showid,h_showcardid);											//��ʾ����
	des2src(tCard.is_main,TYPE_YES);  											//�Ƿ�Ϊ����
	des2src(tCard.state_id,CARDSTAT_REG);										//��״̬
	EncodePwd(seed_key,h_password,tCard.password,0);							//������
	tCard.cosumer_id = hi_cutid;													//�ͻ���ʶ
	tCard.account_count = ACCOUNT_COUNT_ONE;									//����Ӧ�ʻ�����
	des2src(tCard.begin_time,sysdate);											//ע��ʱ��
	des2src(tCard.end_time, card_endtime);										//����ʱ��

	tCard.phytype = PHYTYPE_NO_ONE;											//�豸�����ͺ�;Ĭ��Ϊ1
	//	���뿨��Ϣ
	ret = DB_t_pif_card_add(&tCard);
	if (ret)
	{
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_CARD_E;
		else
			*pRetCode = E_DB_CARD_I;
		goto L_RETU;
	}
	//	�����˻���Ϣ����д����
	ret=DB_t_aif_account_read_by_customer_id_and_act_type(hi_cutid,ACCTYPE_SHOPMAIN,&tAccount);
	if (ret)
	{
		writelog(LOG_ERR,"DB_t_aif_account_read_by_customer_id_and_act_type err,errcod=[%d]",ret);
		*pRetCode = E_DB_ACCOUNT_R;
		goto L_RETU;
	}

	tAccount.card_id=tCard.card_id;
	tAccount.card_type=tCard.type_id;
	
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
	/*
	// add by ����2005-09-05
	// ��¼������ʽ����Ϣ
	/////////////////////////////////////////////////////////////////////////
	ret = InsertToCutUpdList(tCard.card_id, CUTUPD_ADD,tCard.physical_no);
	if( ret )
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	/////////////////////////////////////////////////////////////////////////
	*/
	tradeserial.serial_no = D2I(dUniqNo);											//��ˮ��
	tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
	tradeserial.serial_state = SERISTAT_NODEBT;												//��ˮ״̬
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
	tradeserial.customer_id = hi_cutid;													//�ͻ���ʶ

	des2src(tradeserial.oper_code , rPack->scust_limit);			//����Ա����
	tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
	tradeserial.trade_count=1;														//��ǰ�����״���
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
	T_t_cif_shop  t_cif_shop;
	memset(&t_cif_shop,0,sizeof t_cif_shop);
	ret=DB_t_cif_shop_read_by_cut_id(hi_cutid,&t_cif_shop);
	if(ret)
	{
		*pRetCode = E_DB_SHOP_R;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}
	//	���ؿ���\����\��ʾ����\�ͻ�����\ͼ��֤��\��Ч��������
	out_pack->lvol10=CT_MERCH;									//������
	out_pack->lvol11=t_cif_shop.shop_id;							//�̻���
	out_pack->lvol0 = (int)h_temp_Card_id;                      			//���׿���
	out_pack->lvol1 = tCustomer.cut_type;						//�ͻ����
	out_pack->lvol5 = tCustomer.fee_type;						//�շ����
	des2src(out_pack->scust_no,h_showcardid);					//��ʾ����
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//���ź�
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//ѧ��
	des2src(out_pack->scert_no,tCustomer.man_id);				//���֤��
	des2src(out_pack->sname,tCustomer.cut_name);				//�ͻ�����
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//ͼ��֤��
	des2src(out_pack->sstatus0,tCustomer.sex);					//�Ա�
	des2src(out_pack->sopen_emp,h_password);					//������
	des2src(out_pack->sdate0,card_endtime);					//��Ч��������
	strcpy(out_pack->sorder0,CARD_STRUCT_VERSION);			//�ƿ��汾��
	strcpy(out_pack->sorder1,CARD_REGISTER_PUBLISH_CODE);	//����ע���ʶ��
	strcpy(out_pack->sorder2,CARD_REGISTER_SERVICE_CODE);	//����ע���ʶ��
	sprintf(out_pack->sholder_ac_no,"%d",tCustomer.cut_id);		//�ͻ���
	des2src(out_pack->sstat_type,tCustomer.man_idtype);			//֤������
	des2src(out_pack->snation_code,tCustomer.country);			//����
	sprintf(out_pack->sstat_type2,"%d",tCustomer.nation);			//����
	des2src(out_pack->sbranch_code0,tCustomer.school_code);		//ԺУ����
//	out_pack->damt2=tradeserial.out_balance;				//����ֵ
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

