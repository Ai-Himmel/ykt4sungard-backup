/* --------------------------------------------
 * ��������: F930031.sqc
 * ��������: 9 17 2004
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ռ�������ˮ����
 * --------------------------------------------
 * �޸�����:2004-10-12
 * �޸���Ա:	�Ž�
 * �޸�����:���Ӽ��˽��״���
 * �汾��Ϣ:1.0.0.1
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
#include "interfacefunc.h"
#include "busqc.h"
/*
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
		return E_999_DATE;							//�ϴ���ˮ������������
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
	if((p->transmark!=0X99)&&(p->transmark!=0xFE)&&	(p->transmark!=0X02))
	{
		return 	p->transmark+E_999_0X00;			//�ѷ�������Ϊ���ױ��
	}
	if(amtcmp(p->cardbefbal- p->cardaftbal,p->amount)!=0)
	{
			return E_999_CARD_BALANCE;					//�ϴ���ˮ���뿨�������
	}
	if(0X99==p->transmark||0x02==p->transmark)
	{
		if(amtcmp(p->amount,0)<0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
	}
	else
	{
		//��������,������Ϊ����
		if(amtcmp(p->amount,0)>=0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
	}
	return 0;
}
*/
int F930031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	CAccTrans *pAccTrans=CAccTrans::getInstance();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
//	writelog(LOG_INFO,"cpack:[%s]",pAccTrans->cpackdata);
//	writelog(LOG_INFO,"%s:930031 Start",getdbtimestamp(NULL));
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

	getsysdate(posdtl.coldate);
	getsystime(posdtl.coltime);
	posdtl.devseqno= rPack->lvol4;							//�ϴ�����ˮ��
	posdtl.transmark=rPack->lvol12;							//999���ױ��
	posdtl.sysid  = rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	des2src(posdtl.devphyid, rPack->sdate1);				//�����豸ID
	ret=GetDeviceidByDevphyid(posdtl.devphyid,&(posdtl.termid));
	if(ret)
		return ret;
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
	posdtl.cardbefbal= rPack->lvol9/100.0;							//�뿨���
	posdtl.cardaftbal = rPack->lvol10/100.0;						//�������
	posdtl.amount = rPack->lvol8/100.0;							//�������ѽ��
	posdtl.cardcnt= rPack->lvol7;							//��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
	posdtl.transcode = 930031;								//���״���
 	snprintf(posdtl.transdate,9,"20%s",rPack->spost_code);		//��������(��ʽ�����������)
	des2src(posdtl.transtime,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	if(strcmp(posdtl.transdate,"20000000") != 0)
	{
		ret=IsInvalidDateTime(posdtl.transdate,"YYYYMMDD");
		if(ret)
		{
			return E_999_DATE;							//�ϴ���ˮ������������
		}
		ret=IsInvalidDateTime(posdtl.transtime,"HHMMSS");
		if(ret)
		{
			return E_999_TIME;							//�ϴ���ˮ����ʱ������
		}
	}
	else
	{
		des2src(posdtl.transdate,posdtl.coldate);
		des2src(posdtl.transtime,posdtl.coltime);
	}
	posdtl.status[0]='1';
	*pRetCode=0;

	g_dbchkerr=0;
	ret = DB_t_posdtl_add(&posdtl);
	if (ret)
	{
		g_dbchkerr=1;
		if(DB_REPEAT==ret)
		{	
			writelog(LOG_ERR,"serial_no[%d]cardno[%d]devphyid[%s]transdate[%s]transtime[%s]ret[%d]",posdtl.devseqno,posdtl.cardno,posdtl.devphyid,posdtl.transdate,posdtl.transtime,ret);
			return 0;
		}
		else
			return E_DB_POSDTL_I;
	}
	g_dbchkerr=1;
//	writelog(LOG_INFO,"%s:930031 OK",getdbtimestamp(NULL));
	return 0;
}
