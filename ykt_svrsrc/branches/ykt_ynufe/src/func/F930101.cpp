/* --------------------------------------------
 * ��������: F930101.sqc
 * ��������: 2005-08-22
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �ռ��Ž���ˮ
 * --------------------------------------------
 * �޸�����: 2006-06-27
 * �޸���Ա:	������
 * �޸�����:	���ӿ�����ˮ�ռ�����
 * �汾��Ϣ:	1.0.0.1
 * ��ע��Ϣ:
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
#include "dbfunc_foo.h"

static int check(T_t_door_txdtl *p)
{
	int ret=0;
	if(strlen(p->crc)==0)
	{
		return E_999_CRC;							//�ϴ���ˮCRCУ�����
	}
	ret=IsInvalidDateTime(p->tx_date,"YYYYMMDD");
	if(ret)
	{
		return E_999_DATE;							//�ϴ���ˮ������������
	}
	ret=IsInvalidDateTime(p->tx_time,"HHMMSS");
	if(ret)
	{
		return E_999_TIME;							//�ϴ���ˮ����ʱ������
	}
	/*
	if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			//�ѷ�������Ϊ���ױ��
	}
	*/
	return 0;
}

static int SaveDoorJSBSerial(T_t_attend_txdtl* tTxdtl)
{
	int ret = 0;

	g_dbchkerr=0;
	ret = DB_t_attend_txdtl_add(tTxdtl);
	g_dbchkerr=1;
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]phycardid[%s]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",
			tTxdtl->serial_no,tTxdtl->phycard_no,tTxdtl->card_no,tTxdtl->device_id,tTxdtl->tx_date,tTxdtl->tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_DOOR_TXDTL_I;
	}
	return ret;
}
int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	//T_t_attend_txdtl tTxdtl;
	T_t_door_txdtl tTxdtl;
	T_t_pif_device tDevice;
	T_t_pif_card tCard;
	if(strlen(rPack->sdate0) != 8)
	{
		*pRetCode = E_DEVPHYID_NULL;
		goto L_RETU;
	}

	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&tTxdtl,0,sizeof(tTxdtl));
	memset(&tDevice,0,sizeof tDevice);

	/*

	tTxdtl.serial_no= rPack->lvol3;						//�ϴ�����ˮ��
	tTxdtl.sys_id  = rPack->lcert_code;					//�ϴ�����վ��ʶ(ǰ�û�ע���)
//		tTxdtl.mode_code=rPack->lvol6;					//ģʽ����
	tTxdtl.card_no= rPack->lvol7;						//���׿���
//		tTxdtl.use_type= rPack->lvol8;						//��������
//		tTxdtl.inductor_no= rPack->lvol9;					//��Ӧͷ���
//		tTxdtl.work_mark=rPack->lvol10;					//���°��־
	tTxdtl.tx_mark=rPack->lvol11;						//999���ױ�־
	des2src(tTxdtl.device_id, rPack->sdate0);			//�����豸ID
	des2src(tTxdtl.tx_date,rPack->sdate1);				//��������(��ʽ�����������)
	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRCУ��
	des2src(tTxdtl.tx_time,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	getsysdate(tTxdtl.col_date);
	getsystime(tTxdtl.col_time);
//		ret=check(&tTxdtl);
//		if(ret)
//		{
//			tTxdtl.status[0]='5';							//��Ч����
//			//tTxdtl.err_code=ret;
//			writelog(LOG_DEBUG,"��Ч��ˮdevice_id[%d]serial_no[%d]",tTxdtl.device_id,tTxdtl.serial_no);
//			return ret;
//		}
//		else
//			tTxdtl.status[0]='1';
	ret = SaveDoorJSBSerial(&tTxdtl);
	*/
	tTxdtl.serial_no= rPack->lvol3;						//�ϴ�����ˮ��
	tTxdtl.sys_id  = rPack->lcert_code;					//�ϴ�����վ��ʶ(ǰ�û�ע���)
//		tTxdtl.mode_code=rPack->lvol6;					//ģʽ����
	tTxdtl.card_no= rPack->lvol7;						//���׿���
	memset(&tCard,0,sizeof tCard);
	ret = DB_t_pif_card_read_by_card_id(tTxdtl.card_no,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			// ���Ų�����
		}
		else
		{
			*pRetCode = E_DB_CARD_R;
			goto L_RETU;
		}
	}
//		tTxdtl.use_type= rPack->lvol8;						//��������
//		tTxdtl.inductor_no= rPack->lvol9;					//��Ӧͷ���
//		tTxdtl.work_mark=rPack->lvol10;					//���°��־
	tTxdtl.cust_id = tCard.cosumer_id; //�ͻ���
	tTxdtl.tx_mark=rPack->lvol11;						//999���ױ�־
	//des2src(tTxdtl.device_id, rPack->sdate0);			//�����豸ID
	ret = get_devinfo_by_phyid(rPack->sdate0,&tDevice);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
			// �豸������
			writelog(LOG_ERR,"�ɼ���ʱ����ˮ,�豸�����ڻ���ע��[%s]"
			,rPack->sdate0);
			return 0;
		}
		else
		{
			*pRetCode = ret;
			goto L_RETU;
		}
	}
	tTxdtl.device_id = tDevice.device_id;
	des2src(tTxdtl.tx_date,rPack->sdate1);				//��������(��ʽ�����������)
	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRCУ��
	des2src(tTxdtl.tx_time,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	getsysdate(tTxdtl.col_date);
	getsystime(tTxdtl.col_time);
	ret = SaveKQSerial(&tTxdtl);
	if(ret)
	{
		writelog(LOG_ERR,"���뿼����ˮ��ʧ��,errcode[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
