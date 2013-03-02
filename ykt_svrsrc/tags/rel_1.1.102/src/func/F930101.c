/* --------------------------------------------
 * ��������: F930101.sqc
 * ��������: 2005-08-22
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �ռ��Ž���ˮ
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
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

int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_door_txdtl tTxdtl;
	

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
		*pRetCode=ret;
		goto L_RETU;
	}
	else
		tTxdtl.status[0]='1';
	g_dbchkerr=0;
	
	ret = DB_t_door_txdtl_add(&tTxdtl);
	if (ret)
	{
		g_dbchkerr=1;
		writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",tTxdtl.serial_no,tTxdtl.card_no,tTxdtl.device_id,tTxdtl.tx_date,tTxdtl.tx_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			*pRetCode = E_DB_DOOR_TXDTL_I;
		goto L_RETU;
	}
	g_dbchkerr=1;
	return 0;
L_RETU:
	return -1;
}
