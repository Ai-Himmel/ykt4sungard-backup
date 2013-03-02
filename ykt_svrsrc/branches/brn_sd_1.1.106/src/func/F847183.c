/* --------------------------------------------
 * ��������: F847183.sqc
 * ��������: 2005-04-11
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  ���׳���
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

int F847183(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	char    	tx_date[8+1]="";              	//��������
//		char    	tx_time[6+1]="";      		//����ʱ��
	int		card_no=0;                    	//����
	char    	device_id[8+1]="";            	//�ն˻�ID
	int		serial_no=0;                  	//�ն˻���ˮ��
	int 		flag=0;
	double 	dUniqno=0;
	T_t_tif_tradeserial		tOldTradeserial;	//������ˮ��
	T_t_tif_tradeserial		tTradeserial;	//������ˮ��
	T_t_tif_tradeserial_his	tTradeserialhis;	//��ʷ��ˮ��
	T_t_pif_card tCard;
	char sysdate[11]="";
	char systime[9]="";
	char sYear[5]="";
	char sMonDay[5]="";
       ST_CPACK aPack;
       ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	memset(&tTradeserial,0,sizeof(tTradeserial));
	memset(&tOldTradeserial,0,sizeof(tOldTradeserial));
	memset(&tTradeserialhis,0,sizeof(tTradeserialhis));
	memset(&tCard,0,sizeof tCard);
	getsysdate(sysdate);
	getsystime(systime);
	des2src(tTradeserial.enteract_time,systime);

	des2src(tx_date,rPack->sbank_pwd);
//		des2src(tx_time,rPack->sbank_code);
	card_no=rPack->lvol0;
	des2src(device_id,rPack->sbank_pwd2);
	serial_no=rPack->lvol1;
	trim(rPack->scust_limit);
	trim(rPack->scust_limit2);
	trim(rPack->semp_pwd);
	des2src(sYear,tx_date);
	des2src(sMonDay,tx_date+4);

	if(strlen(rPack->scust_limit)==0)
	{
		*pRetCode=E_OPER_NOT_EXIST;
		goto L_RETU;
	}
	if(strlen(rPack->scust_limit2)==0)
	{
		*pRetCode=E_INPUT_AUTH_OPER_NULL;
		goto L_RETU;
	}
	if(strcmp(rPack->scust_limit,rPack->scust_limit2)==0)
	{
		writelog(LOG_ERR,"oper[%s]auth_oper[%s]",rPack->scust_limit,rPack->scust_limit2);
		*pRetCode=E_OPER_AND_AUTH_OPER_EQ;
		goto L_RETU;
	}
	ret=chk_oper_pwd(rPack->scust_limit2,rPack->semp_pwd);
	if(ret)
	{
		if(E_OPER_NOT_EXIST==ret)
			*pRetCode=E_AUTH_OPER_NOT_EXIST;
		else if(E_PASSWORD_WRONG==ret)
			*pRetCode=E_AUTH_OPER_PWD;
		else
			*pRetCode=ret;
		goto L_RETU;
	}
	ret = DB_t_pif_card_read_by_card_id(card_no,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_CARDNO_NOT_EXIST;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}
	if(tCard.state_id[CARDSTAT_TYPE_REG] == '2')
	{
		writelog(LOG_ERR,"�������׿�����ע��cardid[%d]",tCard.card_id);
		*pRetCode = E_ACTNO_LOGOUT;
		goto L_RETU;
	}
	//��ѯ��ǰ��ˮ��
	ret=DB_t_tif_tradeserial_read_lock_by_c4_and_operate_date_and_serial_no_and_card_id(tx_date,serial_no,card_no,&tOldTradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"tx_date[%s]serial_no[%d]ret[%d]",tx_date,serial_no,ret);
		if(DB_NOTFOUND!=ret)
		{
			*pRetCode=E_DB_TRADESERIAL_R;
			goto L_RETU;
		}
	}
	else
	{
		flag=1;
		memcpy(&tTradeserial,&tOldTradeserial,sizeof(tTradeserial));
		tTradeserial.other_seri_no=tOldTradeserial.serial_no;					//�ϴ�����ˮ��
		tOldTradeserial.serial_state=SERISTAT_RUSH;				//����
		des2src(tOldTradeserial.oper_code,rPack->scust_limit);
		ret=DB_t_tif_tradeserial_update_lock_by_c4(&tOldTradeserial);
		if(ret)
		{
		        *pRetCode=E_DB_TRADESERIAL_U;
		        writelog(LOG_ERR,"DB_t_tif_tradeserial_update_lock_by_c4[%d]",ret);
		        goto L_RETU;
		}
		DB_t_tif_tradeserial_free_lock_c4();
	}
	if(!flag)
	{
		//��ѯ��ʷ��ˮ��
//		ret=DB_t_tif_tradeserial_his_read_lock_by_c0_and_trans_year_and_trans_mon_day_and_serial_no_and_card_id(sYear,sMonDay,serial_no,card_no,&tTradeserialhis);
		ret = DB_t_tif_tradeserial_his_read_lock_by_c0_and_operate_date_and_serial_no_and_card_id(tx_date, serial_no, card_no, &tTradeserialhis);
		if(ret)
		{
			writelog(LOG_ERR,"tx_date[%s]serial_no[%d]card_no[%d]ret[%d]",tx_date,serial_no,card_no,ret);
			if(DB_NOTFOUND==ret)
			{
				*pRetCode=E_SERIALNO_NOT_EXIST;
				goto L_RETU;
			}
			else
			{
				*pRetCode=E_DB_TRADESERIAL_R;
				goto L_RETU;
			}
		}
		tTradeserial.other_seri_no=tTradeserialhis.serial_no;						//�ϴ�����ˮ��
		tTradeserial.serial_state = tTradeserialhis.serial_state;						//��ˮ״̬
		tTradeserial.tmark=tTradeserialhis.tmark;								//999���ױ��
		tTradeserial.maindevice_id = tTradeserialhis.maindevice_id;							//�ϴ�����վ��ʶ(ǰ�û�ע���)
		tTradeserial.sys_id= tTradeserialhis.sys_id;
		tTradeserial.comu_ver=tTradeserialhis.comu_ver;							//ͨ�Ű汾��
		// add by ���� 2007-10-31
		tTradeserial.device_id=tTradeserialhis.device_id;
		des2src(tTradeserial.devphy999_id,tTradeserialhis.devphy999_id);				//�����豸ID
		des2src(tTradeserial.dev_auth,tTradeserialhis.dev_auth);					//�ն��豸��Ȩ��
		des2src(tTradeserial.crc,tTradeserialhis.crc);								//CRCУ��
		tTradeserial.card_id = tTradeserialhis.card_id;								//���׿���
		tTradeserial.purse_id = tTradeserialhis.purse_id;							//����Ǯ����
		tTradeserial.in_balance =tTradeserialhis.in_balance;						//�뿨���
		tTradeserial.out_balance = tTradeserialhis.out_balance;					//�������
		tTradeserial.trade_fee = tTradeserialhis.trade_fee;						//�������ѽ��
		tTradeserial.trade_count = tTradeserialhis.trade_count;							//��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
		tTradeserial.serial_type = tTradeserialhis.serial_type;							//���״���
		tTradeserial.boardfee = tTradeserialhis.boardfee	;						//����
		des2src(tTradeserial.operate_date,tTradeserialhis.operate_date);					//��������(��ʽ�����������)
		des2src(tTradeserial.operate_time,tTradeserialhis.operate_time);					//����ʱ��(��ʽ�������ʱ��)
		tTradeserial.condition_id = tTradeserialhis.condition_id;							// �շѿ�Ŀ
		tTradeserialhis.serial_state=SERISTAT_RUSH;				//����
		des2src(tTradeserialhis.oper_code,rPack->scust_limit);
		ret=DB_t_tif_tradeserial_his_update_lock_by_c0(&tTradeserialhis);
		if(ret)
		{
		        *pRetCode=E_DB_TRADESERIAL_U;
		        writelog(LOG_ERR,"DB_t_tif_tradeserial_update_lock_by_c4[%d]",ret);
		        goto L_RETU;
		}
		DB_t_tif_tradeserial_his_free_lock_by_c0();
	}
	if(tTradeserial.card_id!=card_no)
	{
		writelog(LOG_ERR,"��ˮ�п��Ų���cardid[%d]serial[%d]",card_no,tTradeserial.card_id);
		*pRetCode=E_SERIALNO_NOT_EXIST;
		goto L_RETU;
	}
	if(tTradeserial.serial_state==SERISTAT_RUSH)
	{
		*pRetCode=E_TX_SERIAL_CZ;
		goto L_RETU;
	}
	if(tTradeserial.serial_state!=SERISTAT_DEBT)
	{
		*pRetCode=E_TX_SERIAL_CANNOT_CZ;
		goto L_RETU;
	}
	if(amtcmp(tTradeserial.trade_fee,0)==0)
	{
		*pRetCode=E_TX_SERIAL_CANNOT_CZ;
		goto L_RETU;
	}
	
	des2src(tTradeserial.operate_date,sysdate);
	des2src(tTradeserial.operate_time,systime);
	des2src(tTradeserial.collect_date,sysdate);
	des2src(tTradeserial.collect_time,systime);
	
	ret=GetLogicDate(tTradeserial.enteract_date);						//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"GetLogicDate  err ret[%d]",ret);
		goto L_RETU;
	}
	des2src(tTradeserial.enteract_time,systime);
	tTradeserial.in_balance =rPack->damt1;
 	tTradeserial.trade_fee = -1 * tTradeserial.trade_fee;					//�������ѽ��
 	tTradeserial.boardfee = -1 * tTradeserial.boardfee;					//�������ѹ����
       tTradeserial.out_balance=tTradeserial.in_balance-tTradeserial.trade_fee;
       if(rPack->lvol10 > 0)
		tTradeserial.trade_count=rPack->lvol10+1;
	tTradeserial.maindevice_id=rPack->lvol6;
	des2src(tTradeserial.oper_code,rPack->scust_limit);
	tTradeserial.reviseserial_no=tTradeserial.other_seri_no;

	//ȡ��ˮ��,���ʴ���
	ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqno);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
		goto L_RETU;
	}
	tTradeserial.serial_no=D2I(dUniqno);
	//######################################################
	//���˴���
	switch(tTradeserial.serial_type)
	{
		case 930031:
			// ���׳���
			if(amtcmp(tTradeserial.trade_fee,0)==0)
				break;
			tTradeserial.serial_type=TXCODE_TX_REVEAL;
			ret=process930031(&tTradeserial);
			if(ret)
			{	//ҵ����ʧ�ܴ���
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		case 930034:
			// ��ֵ����
			if(amtcmp(tTradeserial.trade_fee,0)==0)
				break;
			tTradeserial.serial_type=TXCODE_TX_REVEAL;
			ret=process930034(&tTradeserial);
			if(ret)
			{	//ҵ����ʧ�ܴ���
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		case 930036:
			// ���ѳ���
			if(amtcmp(tTradeserial.trade_fee,0)==0)
				break;
			tTradeserial.serial_type=TXCODE_TX_REVEAL;
			ret=process930036(&tTradeserial);
			if(ret)
			{	//ҵ����ʧ�ܴ���
				*pRetCode=ret;
				goto L_RETU;
			}
			break;
		default:
			*pRetCode=E_TXCODE_NOT_EXIST;	//���������
			goto L_RETU;
	}
	//######################################################
	//��ӽ�����ˮ
        tTradeserial.serial_state=SERISTAT_DEBT;
        ret = DB_t_tif_tradeserial_add(&tTradeserial);
        if (ret)
        {
                writelog(LOG_ERR,"DB_t_tif_tradeserial_add ret[%d]",ret);
                if(DB_REPEAT==ret)
                        *pRetCode= E_DB_TRADESERIAL_E;
                else
                        *pRetCode= E_DB_TRADESERIAL_I;
                goto L_RETU;
        }
	if(amtcmp(tTradeserial.out_balance,0)<0)
	{
		*pRetCode=E_ENTER_ACCOUNT;
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_VSMESS,0);
	out_pack->lserial1=tTradeserial.serial_no;
	out_pack->damt2=tTradeserial.out_balance;
	out_pack->damt3=-tTradeserial.trade_fee;
	sprintf(out_pack->vsmess,"��ˮ��:%d �������:%.2lfԪ ����ǰ�����:%.2lfԪ ����ǰ���:%.2lfԪ",tTradeserial.serial_no,-tTradeserial.trade_fee,tTradeserial.in_balance,tTradeserial.out_balance);
	writelog(LOG_DEBUG,out_pack->vsmess);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}
