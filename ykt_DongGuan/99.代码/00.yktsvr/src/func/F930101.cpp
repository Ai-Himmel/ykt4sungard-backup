/* --------------------------------------------
 * ��������: F930101.sqc
 * ��������: 2005-08-22
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������: �ռ��Ž���ˮ
 * --------------------------------------------
 * �޸�����: 2009-11-30
 * �޸���Ա:	xlh
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

static int checkdoordtl(T_t_doordtl *p)
{
	int ret=0;
	if(strlen(p->devphyid)==0)
	{
		return E_DEVPHYID_NULL;							
	}
	ret=IsInvalidDateTime(p->transdate,"YYYYMMDD");
	if(ret)
	{
		return E_999_DATE;							//�ϴ���ˮ������������
	}
	ret=IsInvalidDateTime(p->transtime,"HHMMSS");
	if(ret)
	{
		return E_999_TIME;							//�ϴ���ˮ����ʱ������
	}
	
	return 0;
}
static int checkattenddtl(T_t_attserial *p)
{
	int ret=0;
	if(p->device_id<1)
	{
		return E_DEVPHYID_NULL;							
	}
	ret=IsInvalidDateTime(p->att_date,"YYYYMMDD");
	if(ret)
	{
		return E_999_DATE;							//�ϴ���ˮ������������
	}
	ret=IsInvalidDateTime(p->att_time,"HHMMSS");
	if(ret)
	{
		return E_999_TIME;							//�ϴ���ˮ����ʱ������
	}
	return 0;
}
static int SaveDoorJSBSerial(T_t_attserial* attserial)
{
	int ret = 0;

	g_dbchkerr=0;
	ret = DB_t_attserial_add(attserial);
	g_dbchkerr=1;
	if (ret)
	{
		writelog(LOG_DEBUG,"serial_no[%d]phycardid[%s]cardno[%d]deviceid[%s]transdate[%s]transtime[%s]",
			attserial->serial_id,attserial->phy_id,attserial->card_id,attserial->device_id,attserial->att_date,attserial->att_time);
		if(DB_REPEAT==ret)
			return 0;
		else
			return E_DB_ATTSERIAL_I;
	}
	return ret;
}
int F930101(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret= 0;
	int dev_usage = 0;
	int device_id=0;
	int devusage=0;
	T_t_doordtl doordtl;
	T_t_attserial attserial; 
	T_t_card tCard;
	T_t_customer customer;
	if(!strlen(rPack->sdate0))
	{
		return E_DEVPHYID_NULL;
	}
    memset(&doordtl,0,sizeof(doordtl));
	memset(&attserial,0,sizeof(attserial));
	memset(&tCard,0,sizeof(tCard));
	memset(&customer,0,sizeof(customer));
   	ret=GetDevIdByDevPhyId(&device_id,rPack->sdate0);
	if(ret)
	{
		writelog(LOG_ERR,"�豸�����[%s]ret[%d]",rPack->sdate0,ret);
	}
	if(device_id)
	{
		ret=GetDevusageByDeviceID(device_id,&devusage);
		if(ret)
		{
			return ret;
		}
	}
	SQLCODE=0;
	if(rPack->lvol7)
	{
		ret = DB_t_card_read_by_cardno(rPack->lvol7,&tCard);
		if(ret)
		{
			if(DB_NOTFOUND != ret)
				return E_DB_CARD_R;
		}
	}
	SQLCODE=0;
	if(tCard.custid>0)
	{
		ret = DB_t_customer_read_by_custid(tCard.custid,&customer);
		if(ret)
		{
			if(DB_NOTFOUND != ret)
				return E_DB_CUSTOMER_R;
		}
	}
	if (devusage==1004)
	{
		if(strlen(rPack->sdate1)==6)
			sprintf(attserial.att_date,"20%s",rPack->sdate1);
		else
			des2src(attserial.att_date,rPack->sdate1);				//��������(��ʽ�����������)
	   	des2src(attserial.att_time,rPack->spost_code2);           //����ʱ��(��ʽ�������ʱ��)
	   	attserial.device_id=device_id;                                   //�豸��                    
	   	attserial.serial_id= rPack->lvol3;                        //�ϴ�����ˮ��                  
	   	attserial.card_id= rPack->lvol7;	                         //���׿��� 
	   	des2src(attserial.show_cardno,tCard.showcardno);	         //��ʾ����
	   	des2src(attserial.phy_id,tCard.cardphyid);	             //��ʾ����
	   	attserial.cust_id=tCard.custid;	                         //��ʾ����
	   	attserial.tx_mark=rPack->lvol11;						     //999���ױ�־                                
	   	des2src(attserial.status,"0");
//	   	ret=checkattenddtl(&attserial);
//	   	if (ret)
//	    {
//	    	return ret;
//	   	}
	  	ret=SaveDoorJSBSerial(&attserial); 
	  	if(ret)
		{
			  if(DB_REPEAT==ret)
				  return 0;
			  else
				 return E_DB_ATTSERIAL_I;
		}
	 }
	else 
	 {
		if(strlen(rPack->sdate1)==6)
			sprintf(doordtl.transdate,"20%s",rPack->sdate1);
		else
			des2src(doordtl.transdate,rPack->sdate1);				//��������(��ʽ�����������)
		des2src(doordtl.transtime,rPack->spost_code2);        //����ʱ��(��ʽ�������ʱ��)
		doordtl.deviceid=device_id;                           //�豸��                     
		des2src(doordtl.devphyid,rPack->sdate0);               // �豸�����
		doordtl.devseqno= rPack->lvol3;                       //�ϴ�����ˮ��
		getsysdate(doordtl.coldate);                          //�ɼ�����
		getsystime(doordtl.coltime);                          //�ɼ�ʱ�� 						  
		doordtl.cardno= rPack->lvol7;	                        //���׿��� 
		des2src(doordtl.cardphyid,tCard.cardphyid);	        //������
		des2src(doordtl.showcardno,tCard.showcardno);	        //��ʾ����
		des2src(doordtl.stuempno,customer.stuempno);	        //ѧ����
		des2src(doordtl.custname,customer.custname);          //����
		doordtl.custid = tCard.custid;                        //�ͻ���
		doordtl.transmark=rPack->lvol11;						//999���ױ�־
		doordtl.sysid  = rPack->lcert_code;	                //�ϴ�����վ��ʶ(ǰ�û�ע���)  
//		ret=checkdoordtl(&doordtl);
//		if (ret)
//		{
//			return ret;
//		}
		ret=DB_t_doordtl_add(&doordtl);
		if(ret)
		{
			 if(DB_REPEAT==ret)
				return 0;
		 	else
				return E_DB_DOORDTL_I;
		}
   }
	return 0;
}
