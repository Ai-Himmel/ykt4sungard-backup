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

static int SaveDoorJSBSerial(T_t_door_txdtl* tTxdtl)
{
	int ret = 0;


	g_dbchkerr=0;
	ret = DB_t_door_txdtl_add(tTxdtl);
	g_dbchkerr=1;
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",
			tTxdtl->serial_no,tTxdtl->card_no,tTxdtl->device_id,tTxdtl->tx_date,tTxdtl->tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_DOOR_TXDTL_I;
	}
	return ret;
}

static int UpdateConferSerial(T_t_door_txdtl* tTxdtl)
{
	int ret = 0;
	int confid = 0;
	T_t_pif_card tCard;
	char sign[1] = "";
	memset(&tCard,0,sizeof(tCard));
	if(tTxdtl->tx_mark != (E_999_0x99 - E_999_BASE))
	{
		writelog(LOG_DEBUG,"����ȷ��ˢ��������[%d]��־[%d]"
			,tTxdtl->card_no,tTxdtl->tx_mark);
		return 0;
	}
	ret = DB_t_pif_card_read_by_card_id(tTxdtl->card_no,&tCard);
	if(ret)
		return ret;
	ret = GetConferenceIDByDev(tTxdtl,&confid,sign);
	if(ret)
	{
		// ���û�в��һ���
		/*
		if(E_DB_CONFDEV_N == ret)
			return 0;
		return ret;
		*/
		writelog(LOG_ERR,"�޷��ҵ�����,�豸[%d][%s : %s]"
			,tTxdtl->device_id,tTxdtl->tx_date,tTxdtl->tx_time);
		return 0;
	}
	ret = SaveConferenceSerial(tTxdtl,confid,tCard.cosumer_id,sign[0]);
	if(ret)
	{
		writelog(LOG_DEBUG,"������[%d]����[%d],�ͻ���[%d]�����[%d]",
			ret,tTxdtl->card_no,tCard.cosumer_id,confid);
		// û�ж�Ӧ�ļ�¼��ɾ����
		if(E_DB_CONFATTLST_N == ret)
			return 0;
	}
	return ret;
}

//���Ӳ��뿼����ˮ���¼����
//added by hhd at 2006-06-27
static int InsertKQSerial(T_t_door_txdtl* tTxdtl)
{
	int ret = 0;
	int confid = 0;
	T_t_pif_card tCard;
	memset(&tCard,0,sizeof(tCard));
	/*
	ret = DB_t_pif_card_read_by_card_id(tTxdtl->card_no,&tCard);
	if(ret)
	{
		writelog(LOG_DEBUG,"DB_t_pif_card_read_by_card_id error,errcode=[%d]",ret);
		return ret;
	}
	*/
	ret = SaveKQSerial(tTxdtl);
	if(ret)
	{
		writelog(LOG_DEBUG,"SaveKQSerial error,errcode=[%d]",ret);
		return ret;
	}
	return 0;
}

int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	T_t_door_txdtl tTxdtl;
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

	tTxdtl.serial_no= rPack->lvol3;						//�ϴ�����ˮ��
	tTxdtl.sys_id  = rPack->lcert_code;					//�ϴ�����վ��ʶ(ǰ�û�ע���)
	tTxdtl.mode_code=rPack->lvol6;					//ģʽ����
	tTxdtl.card_no= rPack->lvol7;						//���׿���
	tTxdtl.use_type= rPack->lvol8;						//��������
	tTxdtl.inductor_no= rPack->lvol9;					//��Ӧͷ���
	tTxdtl.work_mark=rPack->lvol10;					//���°��־
	tTxdtl.tx_mark=rPack->lvol11;						//999���ױ�־
	des2src(tTxdtl.device_id, rPack->sdate0);			//�����豸ID
 	des2src(tTxdtl.tx_date,rPack->sdate1);				//��������(��ʽ�����������)
	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRCУ��
	des2src(tTxdtl.tx_time,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	getsysdate(tTxdtl.col_date);
	getsystime(tTxdtl.col_time);
	ret=check(&tTxdtl);
	if(ret)
	{
//		tTxdtl.status[0]='5';								//��Ч����
//		tTxdtl.err_code=ret;
		writelog(LOG_DEBUG,"��Ч��ˮ[%s][%d]",tTxdtl.device_id,tTxdtl.serial_no);
		return ret;
	}
	else
		tTxdtl.status[0]='1';
	ret = GetDevUsageByDevId(tTxdtl.device_id,&dev_usage);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	switch(dev_usage)
	{
		case DU_JSB_CONFRENCE:
			ret = SaveDoorJSBSerial(&tTxdtl);
			if(ret)
			{
				writelog(LOG_ERR,"�����ʱ����ˮʧ��,errcode[%d]",ret);
				break;
			}
			ret = UpdateConferSerial(&tTxdtl);
			break;
		case DU_JSB_ATTENDANCE:
			ret = InsertKQSerial(&tTxdtl);
			if(ret)
			{
				writelog(LOG_ERR,"���뿼����ˮ��ʧ��,errcode[%d]",ret);
				break;
			}
		default:
			ret = SaveDoorJSBSerial(&tTxdtl);
			break;
	}
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
