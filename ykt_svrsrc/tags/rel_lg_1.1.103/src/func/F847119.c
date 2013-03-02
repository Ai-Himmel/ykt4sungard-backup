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
 * --------------------------------------------
 * �޸�����: 2005-12-26
 * �޸���Ա: �Ž�
 * �޸�����: ����Ȧ��д��������Ϣ
 ����ȷ�Ĵ���
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����: 2006-03-26
 * �޸���Ա: ������
 * �޸�����: ����Ȧ�����д���ɹ�
 ���󷵻ص��������ֹ
 �ಹǮ
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------
 * �޸�����: 2006-12-27
 * �޸���Ա: ����
 * �޸�����: ���ˮ�ش�Ǯ����д��ӵ�д��ʧ�ܱ�
 �����޸�ҵ����
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
#define     PURESE_COUNT 4

static int insert_chcard_blacklist(int i_serial_type)
{
	if(
		847104 == i_serial_type ||
		847116 == i_serial_type ||
		847126 == i_serial_type
	  )
	{
		return 0; 
	}
	else
	{
		return 1;
	}
}

static int do_process(T_t_pif_card *tCard, T_t_tif_writefailed *tWriteFailed, ST_PACK *rPack, T_t_tif_tradeserial *tradeserial)
{
	int ret = 0;
	int free_lock_flag = 1;                     //0�ر�, 1��ʾ��
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char operate_date[11]="";
	//	char sSerialno[20]="";
	char physical_no[41]="";
	char old_physical_no[41]="";
	char deal_flag[1 + 1] = "";
	int 	iSerialno=0;
	int 	card_id=0;
	int 	serial_type=0;
	int   flag=0;
	double dSerialno=0;
	double  dAmt=0; 
	int cnt_purse_no = 0;
	int card_use_cnt=0;
	int seri_use_cnt=0;
	double seri_in_bala=0;
	double seri_out_bala=0;
	double seri_in_bala_next=0;
	double seri_out_bala_next=0;
	int amt_flag=0;
	char tx_date[11]="";

	T_t_tif_tradeserial_his tradeserialhis;
	T_t_tif_tradeserial old_tradeserial;

	memset(&old_tradeserial,0,sizeof(old_tradeserial));
	memset(&tradeserialhis,0,sizeof(tradeserialhis));

	des2src(physical_no,rPack->sbank_acc);
	card_id=rPack->lvol0;
	card_use_cnt=rPack->lvol8;
	cnt_purse_no = rPack->lvol4;

	getsysdate(sysdate);
	getsystime(systime);
	deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
	ret=GetLogicDate(logicdate);								//ҵ������
	if(ret)
	{
		free_lock_flag = 0;
		goto L_RETU_INNER;
	}
	//�жϿ�״̬�Ƿ�Ϊд��δ�ɹ�״̬
	ret=DB_t_pif_card_read_by_card_id(card_id, tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			ret = E_CARDNO_NOT_EXIST;
		else
			ret = E_DB_CARD_R;
		free_lock_flag = 0;
		goto L_RETU_INNER;
	}

	if(STATE_FALSE==tCard->state_id[CARDSTAT_TYPE_WFAIL])
	{
		ret = E_CARDSTATE_NOTWRITEFAIL;
		free_lock_flag = 0;
		goto L_RETU_INNER;
	}
	ret = DB_t_tif_writefailed_read_lock_by_c1_and_card_id_and_purese_no_and_deal_flag(tCard->card_id,cnt_purse_no,&deal_flag[0],tWriteFailed);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
			//            ret = E_DB_WRITEFAILED_N;
			ret = E_WRITEFAILED_DEAL_FLAG_N;         // û�в鵽, �����Ѿ�д����
		else
			ret = E_DB_WRITEFAILED_R;
		goto L_RETU_INNER;
	}

	//  writelog(LOG_ERR,"XXX");
	iSerialno = tWriteFailed->serial_no;
	des2src(operate_date,tWriteFailed->tx_date);

	writelog(LOG_DEBUG,"Serialno[%d]",iSerialno);
	writelog(LOG_DEBUG,"operate_date[%s]",operate_date);
	writelog(LOG_DEBUG,"logictime[%s]",logicdate);
	if(strncmp(logicdate,operate_date,8)==0)
	{
		ret=DB_t_tif_tradeserial_read_by_serial_no(iSerialno,&old_tradeserial);
		if(ret)
		{
			writelog(LOG_ERR,"Serialno[%d]",iSerialno);
			if(DB_NOTFOUND==ret)
				ret = E_SERIALNO_NOT_EXIST;
			else
				ret = E_DB_TRADESERIAL_R;
			goto L_RETU_INNER;
		}
		if(card_id!=old_tradeserial.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,old_tradeserial.card_id);
			ret = E_CARDNO_SERIAL_NE;
			goto L_RETU_INNER;
		}
		serial_type=old_tradeserial.serial_type;
		flag=TYPE_CUR;
	}
	else
	{
		// TODO: ��Ҫ�����ݿ��Ͻ�������
		ret=DB_t_tif_tradeserial_his_read_by_operate_date_and_serial_no(operate_date,iSerialno,&tradeserialhis);
		if(ret)
		{
			writelog(LOG_ERR,"operate_date[%s]Serialno[%d]",operate_date,iSerialno);
			if(DB_NOTFOUND==ret)
				ret = E_SERIALNO_NOT_EXIST;
			else
				ret = E_DB_TRADESERIAL_R;
			goto L_RETU_INNER;
		}
		if(card_id!=tradeserialhis.card_id)
		{
			writelog(LOG_ERR,"input card_id [%d],tradeserial card_id[%d]",card_id,tradeserialhis.card_id);
			ret = E_CARDNO_SERIAL_NE;
			goto L_RETU_INNER;
		}
		serial_type=tradeserialhis.serial_type;
		flag=TYPE_HIS;
	}
	if(TYPE_CUR==flag)
	{
		seri_in_bala=old_tradeserial.in_balance;
		seri_out_bala=old_tradeserial.out_balance;
		strncpy(tx_date,old_tradeserial.operate_date,sizeof(tx_date));
		dAmt=D4U5(old_tradeserial.out_balance-old_tradeserial.in_balance,2); 		//������=����ֵ-�뿨ֵ
		seri_use_cnt=old_tradeserial.trade_count;
	}
	else
	{
		seri_in_bala=tradeserialhis.in_balance;
		seri_out_bala=tradeserialhis.out_balance;
		strncpy(tx_date,tradeserialhis.operate_date,sizeof(tx_date));
		dAmt=D4U5(tradeserialhis.out_balance-tradeserialhis.in_balance,2); 		//������=����ֵ-�뿨ֵ
		seri_use_cnt=tradeserialhis.trade_count;
	}
	des2src(old_physical_no,tCard->physical_no);
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
				goto L_RETU_INNER;
			}
			//�޸Ŀ���־����Ϊ����״̬
			ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, tCard);
			if(ret)
			{
				writelog(LOG_ERR,"card_id[%d]",card_id);
				if(DB_NOTFOUND==ret)
					ret = E_CARDNO_NOT_EXIST;
				else
					ret = E_DB_CARD_R;
				goto L_RETU_INNER;
			}
			des2src(tCard->physical_no,physical_no);			//����������
			ret=DB_t_pif_card_update_lock_by_cur(tCard);
			if(ret)
			{
				writelog(LOG_ERR,"card_id[%d]",card_id);
				if(DB_NOTFOUND==ret)
					ret = E_CARDNO_NOT_EXIST;
				else
					ret = E_DB_CARD_U;
				goto L_RETU_INNER;
			}
			DB_t_pif_card_free_lock_by_cur();
			// �궨����ж�, 0��ʾ�ɹ�, 1��ʾ����Ҫ����
			if (0 == insert_chcard_blacklist(serial_type))
			{
				ret = InsertToBlkList(tCard->card_id,CHCARD_BLACKLIST);
				if (ret)
				{
					goto L_RETU_INNER;
				}	
			}
			// add by ���� 2005-8-10
			// ������������д���¼
			/*
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
			goto L_RETU_INNER;
			}
			break;
			default:
			break;
			}
			*/
		}
		tradeserial->in_balance=0;													//�뿨ֵ
		des2src(tWriteFailed->comments, "��д���ɹ�");
		break;
		//��дˮ��СǮ��, ��СǮ���ۿ�ʧ�ܶ���
		//ˮ��СǮ����д���ൽ847119�У���������д
	case 847300:
		des2src(tWriteFailed->comments, "СǮ����д���ɹ�");
		tradeserial->in_balance = rPack->damt1;
		writelog(LOG_ERR,"СǮ���뿨ֵ[%f]",tradeserial->in_balance);
		break;
		//��дˮ�ش�Ǯ��, ���Ǯ���ۿ�ʧ�ܶ���
		//ˮ���ƴ�Ǯ����д���ൽ847119��, ��������д
	case 847301:
		des2src(tWriteFailed->comments, "��Ǯ����д���ɹ�");
		tradeserial->in_balance = rPack->damt1;
		break;
		//����ת��-Added by hhd at 20051225
		//���ǵ��п���Ȧ��д���ɹ���������ʾʧ��
		//�����ظ�д��
	case 240001:
		//�жϿ��н��״����Ƿ���ڷ����������ˮ�Ľ��״���
		writelog(LOG_ERR,"card_use_cnt=[%d],seri_use_cnt=[%d]",card_use_cnt,seri_use_cnt);
		if((card_use_cnt+1)==seri_use_cnt)
		{
			//�ж��ϴ��뿨ֵ�Ƿ���ڷ����������ˮ���뿨ֵ
			if(amtcmp(rPack->damt1,seri_in_bala)==0)	   //�뿨ֵ�����뿨ֵ����û��д��
				tradeserial->in_balance=rPack->damt1;
			else if(amtcmp(rPack->damt1,seri_out_bala)==0)  //�뿨ֵ���ڳ���ֵ�����Ѿ�д��
			{
				tradeserial->in_balance=rPack->damt1;
				amt_flag=1;
			}
			else
			{
				writelog(LOG_ERR,"In_balance abnormity,in_bala=[%f]",rPack->damt1);
				ret = E_ENTER_ACCOUNT;
				goto L_RETU_INNER;
			}
		}
		else if((card_use_cnt+1)>seri_use_cnt)
		{
			//��д�����ɹ�ʱ��һ�㲻����¿��Ľ��״�����
			//������һ�εĽ��״������ǵ���ʧ����ˮ�Ĵ�����
			//����ȥ��һ����ˮ��ʱ�����ȡ��������+1
			ret=Get_card_next_serial(tCard->card_id,tx_date,seri_use_cnt,&seri_in_bala_next,&seri_out_bala_next);
			if(ret)
			{
				if(DB_NOTFOUND==ret)
				{
					ret=Get_card_next_serial(tCard->card_id,tx_date,seri_use_cnt+1,&seri_in_bala_next,&seri_out_bala_next);
					if(ret)
					{
						writelog(LOG_ERR,"Get_card_next_serial(=) error,errcode=[%d]",ret);
						writelog(LOG_ERR,"û���ҵ���һ����ˮ");
						goto L_RETU_INNER;
					}
				}
				else
				{
					writelog(LOG_ERR,"Get_card_next_serial(+1) error,errcode=[%d]",ret);
					goto L_RETU_INNER;
				}
			}
			writelog(LOG_INFO,"seri_in_bala_next=[%f],seri_in_bala=[%f],seri_out_bala=[%f]",seri_in_bala_next,seri_in_bala,seri_out_bala);

			if(amtcmp(seri_in_bala_next/100,seri_in_bala)==0)
				tradeserial->in_balance=rPack->damt1;
			else if(amtcmp(seri_in_bala_next/100,seri_out_bala)==0)
			{
				tradeserial->in_balance=rPack->damt1;
				amt_flag=1;
			}
			else
			{
				tradeserial->in_balance=rPack->damt1;
				writelog(LOG_ERR,"In_balance abnormity,in_bala=[%f]",rPack->damt1);
				ret = E_ENTER_ACCOUNT;
				goto L_RETU_INNER;
			}
		}
		else
		{
			writelog(LOG_ERR,"In_total_cnt abnormity,in_total_cnt=[%d]",card_use_cnt);
			ret = E_ENTER_ACCOUNT;
			goto L_RETU_INNER;
		}
	default:
		if(strcmp(old_physical_no,physical_no)!=0)
		{
			writelog(LOG_ERR,"db physical_no[%s],input physical_no[%s]",old_physical_no,physical_no);
			ret = E_CARD_PHYNO_DIFFER;
			goto L_RETU_INNER;
		}
		tradeserial->in_balance=rPack->damt1;										//�뿨ֵ
		break;
	}
	if(TYPE_CUR==flag)
		dAmt=D4U5(old_tradeserial.out_balance-old_tradeserial.in_balance,2); 		//������=����ֵ-�뿨ֵ
	else
		dAmt=D4U5(tradeserialhis.out_balance-tradeserialhis.in_balance,2); 		//������=����ֵ-�뿨ֵ
	//˵������Ҫд��,��������Ϊ0
	if(amt_flag==1)
	{
		tradeserial->trade_fee=0;											//��д��ֵ
	}
	else
	{
		tradeserial->trade_fee=dAmt;											//��д��ֵ
	}
	tradeserial->out_balance=tradeserial->in_balance+dAmt;					//����ֵ
	writelog(LOG_ERR,"СǮ������ֵ[%f]",tradeserial->out_balance);
	writelog(LOG_ERR,"СǮ�����׽��[%f]",dAmt);

	if(tradeserial->out_balance<0||tradeserial->out_balance>999)
	{
		writelog(LOG_ERR,"tradeserial.out_balance[%lf]",tradeserial->out_balance);
		ret = E_TX_SERIAL;
		goto L_RETU_INNER;
	}
	writelog(LOG_DEBUG,"д��ʧ������%s,��д��ˮ��%d,������%d,����%d,��д���%.2lf,�뿨ֵ%lf,����ֵ%lf",operate_date,iSerialno,serial_type,card_id,dAmt,tradeserial->in_balance,tradeserial->out_balance);

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialno);  				//�����ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		goto L_RETU_INNER;
	}

	tradeserial->serial_no = D2I(dSerialno);											//��ˮ��
	tradeserial->other_seri_no = 0;												//�ϴ�����ˮ��
	tradeserial->serial_type = TXCODE_REWRITE_CARD;								//���״��룻��ע������+��ֵ ��һ�������룬��847101�� ����������ֵ������һ�������룬���µķ��������ļ������Ӷ����ַ�����ֵ�뷢������ֵ�Ŀ�������Ϣ��
	tradeserial->serial_state = SERISTAT_DEBT;										//��ˮ״̬
	des2src(tradeserial->operate_date,sysdate);											//��������
	des2src(tradeserial->operate_time,systime);											//����ʱ��
	des2src(tradeserial->collect_date,sysdate);												//�ɼ�����
	des2src(tradeserial->collect_time,systime);												//�ɼ�ʱ��
	des2src(tradeserial->enteract_date,logicdate);											//��������
	des2src(tradeserial->enteract_time,systime);											//����ʱ��
	des2src(tradeserial->oper_code , rPack->scust_limit);
	tradeserial->maindevice_id = rPack->lvol6;											//�ϴ�����վ��ʶ
	tradeserial->device_id = rPack->lvol7;												//�ɼ��豸��ʶ
	tradeserial->card_id = tCard->card_id;											//����
	des2src(tradeserial->showid,tCard->showid);										//��ʾ����
	tradeserial->purse_id = cnt_purse_no;										//Ǯ����,���ݾ��巢����Ҫ��д��Ǯ���ž���
	tradeserial->customer_id = tCard->cosumer_id;									//�ͻ���ʶ
	tradeserial->reviseserial_no = iSerialno;											//ԭд��ʧ����ˮ��
	tradeserial->trade_count = card_use_cnt + 1;                                    //���״���Ϊ�����״���+1           
	//	���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		goto L_RETU_INNER;
	}
	/******************************************************************/
	//����д��ʧ�ܱ�
	tWriteFailed->deal_serial_no = tradeserial->serial_no;
	//	writelog(LOG_ERR,"��ˮ��[%d]",tWriteFailed->deal_serial_no);
	tWriteFailed->deal_bala = tradeserial->trade_fee;
	des2src(tWriteFailed->deal_date,sysdate);
	des2src(tWriteFailed->deal_time,systime);
	//	tWriteFailed->deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_N;
	ret = DB_t_tif_writefailed_update_lock_by_c1(tWriteFailed);
	if (ret)
	{
		if (DB_NOTFOUND == ret)
		{
			ret = E_DB_WRITEFAILED_N;
		}
		else
		{
			ret = E_DB_WRITEFAILED_U;    
		}
		goto L_RETU_INNER;
	}
	DB_t_tif_writefailed_free_lock_by_c1();
	/******************************************************************/
	return 0;
L_RETU_INNER:
	if (free_lock_flag)
		DB_t_tif_writefailed_free_lock_by_c1();
	return ret;
}

int F847119(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char h_password[7] = "";							//������
	char seed_key[17] = "";							//������Կ
	T_t_pif_card tCard;
	T_t_tif_tradeserial tradeserial;
	T_t_tif_writefailed tWriteFailed;
	T_t_cif_customer tCustomer;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	memset(&tCard,0,sizeof(tCard));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tWriteFailed, 0, sizeof tWriteFailed);
	memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));		//��������Կ

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,F_LVOL6,
		   F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
		   F_SDATE0,F_SNAME,F_SNAME2,
		   F_SOPEN_EMP,F_SSTATUS0,
		   F_DAMT2,F_LSERIAL1,F_VSMESS,0);
	/************************************************************************/
	ret = do_process(&tCard, &tWriteFailed, rPack, &tradeserial);
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	ret=DB_t_cif_customer_read_lock_by_cur_and_cut_id(tCard.cosumer_id, &tCustomer);
	if(ret)
	{
		writelog(LOG_ERR,"cut_id[%d]",tCard.cosumer_id);
		if(DB_NOTFOUND==ret)
			*pRetCode = E_CUSTOMER_NOT_EXIST;
		else
			*pRetCode = E_DB_CUSTOMER_R;
		goto L_RETU;
	}
	EncodePwd(seed_key,h_password,tCard.password,1);			//������
	DB_t_cif_customer_free_lock_cur();
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
