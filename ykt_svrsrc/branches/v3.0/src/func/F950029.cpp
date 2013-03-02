/* --------------------------------------------
 * ��������: F930029.cpp
 * ��������: 2007-10-15
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ռ�ϴ�»�������ˮ
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

static int check(T_t_posdtl *p)
{
	int ret=0;
//	if(strlen(p->crc)==0)
//	{
//		return E_999_CRC;							//�ϴ���ˮCRCУ�����
//	}
	if(strcmp(p->transdate,"20000000") != 0)
	{
		ret=IsInvalidDateTime(p->transdate,"YYYYMMDD");
		if(ret)
		{
			return E_999_DATE;						//�ϴ���ˮ������������
		}
	}
	else
		getsysdate(p->transdate);
	if(strcmp(p->transtime,"000000") != 0)
	{
		ret=IsInvalidDateTime(p->transtime,"HHMMSS");
		if(ret)
		{
			return E_999_TIME;							//�ϴ���ˮ����ʱ������
		}
	}
	else
		getsystime(p->transtime);
	// &&(p->transmark!=0xF0)
	
	if((p->transmark!=0XFA))
	{
		return 	p->transmark+E_999_0X00;			//�ѷ�������Ϊ���ױ��
	}
	if(p->cardbefbal - p->amount != p->cardaftbal)
	{
		return E_999_CARD_BALANCE;					//�ϴ���ˮ���뿨�������
	}
	return 0;
}

int F950029(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	T_t_posdtl posdtl;

	/*
	ret=chk_dyn_key(rPack->lcert_code,rPack->scust_limit2);
	if(ret)
	{
		writelog(LOG_ERR,"subsys_id[%d]dyn_key[%s]",rPack->lcert_code,rPack->scust_limit2);
		*pRetCode =  ret;
		goto L_RETU;
	}
	*/
	memset(&posdtl,0,sizeof(posdtl));

	posdtl.devseqno= rPack->lvol4;							//�ϴ�����ˮ��
	posdtl.transmark=rPack->lvol12;							//999���ױ��
	posdtl.sysid  = rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	des2src(posdtl.devphyid, rPack->sdate1);				//�����豸ID
//	des2src(posdtl.inpower_no,rPack->stx_pwd);				//�ն��豸��Ȩ��
//	posdtl.comu_ver=rPack->lbank_acc_type;					//ͨ�Ű汾��
//	int ver = posdtl.comu_ver / 10;
//	if( 0x81 == posdtl.comu_ver || 0x81 == ver )
//	{
//	posdtl.run_reason = rPack->lbank_acc_type2;				//����ԭ��
//		posdtl.fee_code = rPack->lbank_acc_type2;				// ������ԭ�򱣴浽�շѿ�Ŀ��
//	}
//	else
//	{
//		posdtl.fee_code = 0;
//	}
//	des2src(posdtl.crc,rPack->sbank_code2);				//CRCУ��

	//posdtl.man_fee = rPack->lvol11;						//
	posdtl.cardno= rPack->lvol5;							//���׿���
	//posdtl.purseno = rPack->lvol6;						//����Ǯ����
	posdtl.purseno = 0;
	posdtl.cardbefbal= rPack->lvol9;							//�뿨���
	posdtl.cardaftbal = rPack->lvol10;						//�������
	posdtl.amount = rPack->lvol8;							//�������ѽ��
	if(posdtl.amount>0)
		posdtl.amount = -posdtl.amount;
	posdtl.cardcnt= rPack->lvol7;							//��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
	posdtl.transcode = 930031;								//���״���
 	snprintf(posdtl.transdate,9,"20%s",rPack->spost_code);		//��������(��ʽ�����������)
	des2src(posdtl.transtime,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	getsysdate(posdtl.coldate);
	getsystime(posdtl.coltime);	
	ret=check(&posdtl);
	if(ret)
	{
		posdtl.errcode=ret;
		if(posdtl.transmark==240 || posdtl.transmark==2)
		{
			posdtl.status[0]='6';							//��;�ο�����
			// ���Ϊ��;�ο�
			posdtl.transmark = 2;
		}
		else
		{
			posdtl.status[0]='5';								//��Ч����
			strcpy(posdtl.accdate,posdtl.coldate);
			strcpy(posdtl.acctime,posdtl.coltime);
		}
	}
	else
		posdtl.status[0]='1';
	g_dbchkerr=0;
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		g_dbchkerr=1;
		writelog(LOG_DEBUG,"serial_no[%d]cardno[%d]deviceid[%s]transdate[%s]transtime[%s]",posdtl.devseqno,posdtl.cardno,posdtl.devphyid,posdtl.transdate,posdtl.transtime);
		if(DB_REPEAT==ret)
			return 0;
		else
			*pRetCode = E_DB_POSDTL_I;
		goto L_RETU;
	}
	g_dbchkerr=1;
	return 0;
L_RETU:
	return -1;
}

