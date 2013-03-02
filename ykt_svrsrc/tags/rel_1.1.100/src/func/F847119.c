/* --------------------------------------------
 * ��������: F847119.sqc
 * ��������: Sep 29 2004
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ��д����Ϣ
 * --------------------------------------------
 * �޸�����: 2004-11-29
 * �޸���Ա: �Ž�
 * �޸�����: �޸�����ҵ���߼�
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/
#define _IN_SQC_
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
#define 	TYPE_CUR	1
#define 	TYPE_HIS	2

int F847119(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char operate_date[11]="";
	char sSerialno[20]="";
	char physical_no[41]="";
	char old_physical_no[41]="";
	int 	iSerialno=0;
	int 	card_id=0;
	int 	serial_type=0;
	int   flag=0;
	double dSerialno=0;
	double  dAmt=0;
	char h_password[7] = "";							//������
	char seed_key[17] = "";							//������Կ
	T_t_pif_card tCard;
	T_t_cif_customer  tCustomer;
	T_t_pif_spefee 	tSpeFee;
	T_t_tif_tradeserial tradeserial;
	T_t_tif_tradeserial old_tradeserial;
	T_t_tif_tradeserial_his tradeserialhis;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tCustomer,0,sizeof(tCustomer));
	memset(&tSpeFee,0,sizeof(tSpeFee));
	memset(&old_tradeserial,0,sizeof(old_tradeserial));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tradeserialhis,0,sizeof(tradeserialhis));
	memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));		//��������Կ

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
				F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
				F_SDATE0,F_SNAME,F_SNAME2,
				F_SOPEN_EMP,F_SSTATUS0,
				F_DAMT2,F_LSERIAL1,F_VSMESS,0);
	des2src(physical_no,rPack->sbank_acc);
	card_id=rPack->lvol0;

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	ret=DB_t_pif_card_read_by_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_WFAIL])
	{
		*pRetCode=E_CARDSTATE_NOTWRITEFAIL;
		goto L_RETU;
	}
	ret=GetXmlValue(sSerialno, sizeof(sSerialno), XML_KEY_SERIALNO, tCard.comments);
	if(ret)
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode=ret;
		goto L_RETU;
	}
	//�޸��˺ű��еĿ�״̬
	//������ˮ�ŵõ������ĳ���ֵ
	ret=GetXmlValue(operate_date, sizeof(operate_date), XML_KEY_OPERATEDATE, tCard.comments);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	iSerialno=atoi(sSerialno);
	if(strncmp(sysdate,operate_date,8)==0)
	{
		ret=DB_t_tif_tradeserial_read_by_serial_no(iSerialno,&old_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"Serialno[%d]",iSerialno);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_SERIALNO_NOT_EXIST;
			else
				*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
		if(card_id!=old_tradeserial.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,old_tradeserial.card_id);
			*pRetCode=E_CARDNO_SERIAL_NE;
			goto L_RETU;
		}
		serial_type=old_tradeserial.serial_type;
		flag=TYPE_CUR;
	}
	else
	{
		ret=DB_t_tif_tradeserial_his_read_by_enteract_date_and_serial_no(operate_date,iSerialno,&tradeserialhis);
		if(ret)
		{
			writelog(LOG_ERR,"operate_date[%s]Serialno[%d]",operate_date,iSerialno);
			if(DB_NOTFOUND==ret)
				*pRetCode=E_SERIALNO_NOT_EXIST;
			else
				*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
		if(card_id!=tradeserialhis.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,tradeserialhis.card_id);
			*pRetCode=E_CARDNO_SERIAL_NE;
			goto L_RETU;
		}
		serial_type=tradeserialhis.serial_type;
		flag=TYPE_HIS;
	}
	des2src(old_physical_no,tCard.physical_no);
	trim(physical_no);
	trim(old_physical_no);
	switch(serial_type)
	{
		//������ʽ��
		case  847101:
		//������ʽ��
		case  847104:
		//���й�����ʱ��
		case 847116:
		//���зǼ�����ʱ��
		case 847124:
		case 847125:
		case 847126:
			if(strcmp(old_physical_no,physical_no)!=0)
			{
				ret=IsExistCardByPhyCardNo(physical_no);
				if(ret)
				{
					*pRetCode = ret;
					goto L_RETU;
				}
				//�޸Ŀ���־����Ϊ����״̬
				ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
				if(ret)
				{
					writelog(LOG_ERR,"card_id[%d]",card_id);
					if(DB_NOTFOUND==ret)
						*pRetCode= E_CARDNO_NOT_EXIST;
					else
						*pRetCode= E_DB_CARD_R;
					goto L_RETU;
				}
				des2src(tCard.physical_no,physical_no);			//������
				ret=DB_t_pif_card_update_lock_by_cur(&tCard);
				if(ret)
				{
					writelog(LOG_ERR,"card_id[%d]",card_id);
					if(DB_NOTFOUND==ret)
						*pRetCode= E_CARDNO_NOT_EXIST;
					else
						*pRetCode= E_DB_CARD_U;
					goto L_RETU;
				}
				DB_t_pif_card_free_lock_by_cur();
				// add by ���� 2005-8-10
				// ������������д���¼
				switch(serial_type)
				{
				//������ʽ��
				case  847104:
				//���й�����ʱ��
				case 847116:
				// ������ʱ��
				//case 847124:
				// VIP ��
				case 847126:
					ret = InsertToBlkList(tCard.card_id,CHCARD_BLACKLIST);
					if(ret)
					{
						*pRetCode = ret;
						goto L_RETU;
					}
					break;
				default:
					break;
				}
			}
			tradeserial.in_balance=0;													//�뿨ֵ
			break;
		default:
			if(strcmp(old_physical_no,physical_no)!=0)
			{
				writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",old_physical_no,physical_no);
				*pRetCode= E_CARD_PHYNO_DIFFER;
				goto L_RETU;
			}
			tradeserial.in_balance=rPack->damt1;										//�뿨ֵ
			break;
	}
	if(TYPE_CUR==flag)
		dAmt=D4U5(old_tradeserial.out_balance-old_tradeserial.in_balance,2); 		//������=����ֵ-�뿨ֵ
	else
		dAmt=D4U5(tradeserialhis.out_balance-tradeserialhis.in_balance,2); 		//������=����ֵ-�뿨ֵ
	tradeserial.trade_fee=dAmt;											//��д��ֵ
	tradeserial.out_balance=tradeserial.in_balance+dAmt;					//����ֵ
	if(tradeserial.out_balance<0||tradeserial.out_balance>999)
	{
		writelog(LOG_ERR,"tradeserial.out_balance[%lf]",tradeserial.out_balance);
		*pRetCode= E_TX_SERIAL;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"д��ʧ������%s,��д��ˮ��%d,������%d,����%d,��д���%.2lf,�뿨ֵ%lf,����ֵ%lf",operate_date,iSerialno,serial_type,card_id,dAmt,tradeserial.in_balance,tradeserial.out_balance);

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode= E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	EncodePwd(seed_key,h_password,tCard.password,0);			//������
	//�õ��շ����
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
	}
	DB_t_cif_customer_free_lock_cur();

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//�����ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU;
	}

	tradeserial.serial_no = (int)dSerialno;											//��ˮ��
	tradeserial.other_seri_no = 0;												//�ϴ�����ˮ��
	tradeserial.serial_type = TXCODE_REWRITE_CARD;								//���״��룻��ע������+��ֵ ��һ�������룬��847101�� ����������ֵ������һ�������룬���µķ��������ļ������Ӷ����ַ�����ֵ�뷢������ֵ�Ŀ�������Ϣ��
	tradeserial.serial_state = SERISTAT_DEBT;										//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);											//��������
	des2src(tradeserial.operate_time,systime);											//����ʱ��
	des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);											//��������
	des2src(tradeserial.enteract_time,systime);											//����ʱ��
	des2src(tradeserial.oper_code , rPack->scust_limit);
	tradeserial.maindevice_id = rPack->lvol6;											//�ϴ�����վ��ʶ
	tradeserial.device_id = rPack->lvol7;												//�ɼ��豸��ʶ
	tradeserial.card_id = tCard.card_id;											//����
	des2src(tradeserial.showid,tCard.showid);										//��ʾ����
	tradeserial.purse_id = PURSE_NO_ONE;										//Ǯ����
	tradeserial.customer_id = tCard.cosumer_id;									//�ͻ���ʶ
	tradeserial.reviseserial_no=dSerialno;											//ԭд��ʧ����ˮ��
	//	���뽻����ˮ��
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
	sprintf(out_pack->vsmess,"��ˮ��:%d ��д���:%.2lfԪ ��дǰ�����:%.2lfԪ  ����ǰ���:%.2lfԪ",tradeserial.serial_no,tradeserial.trade_fee,tradeserial.in_balance,tradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);

	out_pack->lvol0 = tCard.card_id;								//���׿���
	out_pack->lvol1 = tCustomer.cut_type;						//�ͻ����
	out_pack->lvol5 = tCustomer.fee_type;						//�շ����
	des2src(out_pack->scust_no,tCard.showid);					//��ʾ����
	des2src(out_pack->scust_no2,tCustomer.classdept_no);			//���ź�
	des2src(out_pack->scust_auth,tCustomer.stuemp_no);			//ѧ��
	des2src(out_pack->scust_auth2,tCustomer.man_id);			//���֤��
	des2src(out_pack->sname,tCustomer.cut_name);				//�ͻ�����
	des2src(out_pack->sname2,tCustomer.lib_cardid);				//ͼ��֤��
	des2src(out_pack->sstatus0,tCustomer.sex);					//�Ա�
	des2src(out_pack->sopen_emp,h_password);					//������
	des2src(out_pack->sdate0,tCard.end_time);					//��Ч��������

	out_pack->damt2=tradeserial.out_balance;					//����ֵ=�뿨ֵ+������
	out_pack->lserial1=tradeserial.serial_no;						//��ˮ��

	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
