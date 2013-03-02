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
#include "acctrans.h"
#include "busqc.h"
#include "dbfunc_foo.h"

//static int check(T_t_doordtl *p)
//{
//	int ret=0;
//	if(strlen(p->crc)==0)
//	{
//		return E_999_CRC;							//�ϴ���ˮCRCУ�����
//	}
//	ret=IsInvalidDateTime(p->transdate,"YYYYMMDD");
//	if(ret)
//	{
//		return E_999_DATE;							//�ϴ���ˮ������������
//	}
//	ret=IsInvalidDateTime(p->transtime,"HHMMSS");
//	if(ret)
//	{
//		return E_999_TIME;							//�ϴ���ˮ����ʱ������
//	}
//	/*
//	if((p->transmark!=0X99)&&(p->transmark!=0xFE)	)
//	{
//		return 	p->transmark+E_999_0X00;			//�ѷ�������Ϊ���ױ��
//	}
//	*/
//	return 0;
//}

//static int SaveDoorJSBSerial(T_t_attenddtl* attenddtl)
//{
//	int ret = 0;
//
//	g_dbchkerr=0;
//	ret = DB_t_attenddtl_add(attenddtl);
//	g_dbchkerr=1;
//	if (ret)
//	{
//		writelog(LOG_DEBUG,"serial_no[%d]phycardid[%s]cardno[%d]deviceid[%s]transdate[%s]transtime[%s]",
//			attenddtl->devseqno,attenddtl->cardphyid,attenddtl->cardno,attenddtl->deviceid,attenddtl->transdate,attenddtl->transtime);
//		if(DB_REPEAT==ret)
//			return 0;
//		else
//			return E_DB_DOOR_TXDTL_I;
//	}
//	return ret;
//}
int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	T_t_doordtl tTxdtl;
	T_t_card tCard;
	if(!strlen(rPack->sdate0))
	{
		return E_DEVPHYID_NULL;
	}
	memset(&tTxdtl,0,sizeof(tTxdtl));

	tTxdtl.devseqno= rPack->lvol3;						//�ϴ�����ˮ��
	tTxdtl.sysid  = rPack->lcert_code;					//�ϴ�����վ��ʶ(ǰ�û�ע���)
//		tTxdtl.mode_code=rPack->lvol6;					//ģʽ����
	tTxdtl.cardno= rPack->lvol7;						//���׿���
	memset(&tCard,0,sizeof tCard);
	ret = DB_t_card_read_by_cardno(tTxdtl.cardno,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND != ret)
			return E_DB_CARD_R;
	}
	tTxdtl.custid = tCard.custid; //�ͻ���
	tTxdtl.transmark=rPack->lvol11;						//999���ױ�־
	ret=GetDevIdByDevPhyId(&tTxdtl.deviceid,rPack->sdate0);
	if(ret)
	{
			writelog(LOG_ERR,"�ɼ���ʱ����ˮ,�豸�����ڻ���ע��[%s]",rPack->sdate0);
//			return ret;
	}
	des2src(tTxdtl.transdate,rPack->sdate1);				//��������(��ʽ�����������)
//	des2src(tTxdtl.crc,rPack->sbank_code2);				//CRCУ��
	des2src(tTxdtl.transtime,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	getsysdate(tTxdtl.coldate);
	getsystime(tTxdtl.coltime);
	ret=DB_t_doordtl_add(&tTxdtl);
	if(ret)
	{
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_DOORDTL_I;
	}
	return 0;
}
