/* --------------------------------------------
 * ��������: F940031.sqc
 * ��������: 2010-11-29
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������:  �ռ�����������ˮ����
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

static int check(T_t_tif_rcvdtl *p)
{
	int ret=0;
	if(strlen(p->crc)==0)
	{
		return E_999_CRC;						    	//�ϴ���ˮCRCУ�����
	}
	ret=IsInvalidDateTime(p->tx_date,"YYYYMMDD");
	if(ret)
	{
		return E_999_DATE;							   //�ϴ���ˮ������������
	}
	ret=IsInvalidDateTime(p->tx_time,"HHMMSS");
	if(ret)
	{
		return E_999_TIME;							   //�ϴ���ˮ����ʱ������
	}
	if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			       //�ѷ�������Ϊ���ױ��
	}
	if(p->in_bala- p->out_bala!=p->amount)
	{
		return E_999_CARD_BALANCE;				    	//�ϴ���ˮ���뿨�������
	}
	if(0X99==p->tx_mark)
	{
		if(p->amount<0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
		if(p->amount-p->manage_fee<0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
	}
	else
	{
		//��������,������Ϊ����
		if(p->amount>0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
		if(p->amount-p->manage_fee>0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
	}
	return 0;
}

/*
static int checktRcvdtl(T_t_extposdtl *p)
{
	int ret=0;
	ret=IsInvalidDateTime(p->transdate,"YYYYMMDD");
	if(ret)
	{
	writelog(LOG_ERR,"IsInvalidDateTime[%s]",p->transdate);
		return E_999_DATE;						    	//�ϴ���ˮ������������
	}
	ret=IsInvalidDateTime(p->transtime,"HHMMSS");
	if(ret)
	{ 
	writelog(LOG_ERR,"IsInvalidDateTime[%s]",p->transtime);
		return E_999_TIME;						    	//�ϴ���ˮ����ʱ������
	}
	/*if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			//�ѷ�������Ϊ���ױ��
	}
	*/
	
	/*
	if(0X99==p->tx_mark)
	{
		if(p->amount<=0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
		if(p->amount-p->manage_fee<0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
	}
	else
	{
		//��������,������Ϊ����
		if(p->amount>=0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
		if(p->amount-p->manage_fee>0)
		{
			return E_999_AMT;							//�ϴ���ˮ���׷����������
		}
	}
	
	return 0;
}
*/

int F940031(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	int ret=0;
	int in_balance = 0;
	int out_balance = 0;
	int man_fee = 0;
	int trade_fee = 0;
	T_t_tif_rcvdtl tRcvdtl;
	T_t_door_txdtl txdtl;
	T_t_pif_card card;
	T_t_pif_device device;
	//T_t_extposdtl extposdtl;
	writelog(LOG_ERR,"240031[%d]",ret);
	if (rPack->lvol6==0)
	{
	           memset(&device,0,sizeof(device));
		    memset(&card,0,sizeof(card));
		    memset(&txdtl,0,sizeof(txdtl));
		    memset(&tRcvdtl,0,sizeof(tRcvdtl));
	           tRcvdtl.serial_no= rPack->lvol4;							//�ϴ�����ˮ��
	           tRcvdtl.tx_mark=rPack->lvol12;							//999���ױ��
	            tRcvdtl.sys_id  = rPack->lcert_code;						//�ϴ�����վ��ʶ(ǰ�û�ע���)
	           des2src(tRcvdtl.device_id, rPack->sdate1);				//�����豸ID
	           des2src(tRcvdtl.inpower_no,rPack->stx_pwd);				//�ն��豸��Ȩ��
	           tRcvdtl.comu_ver=rPack->lbank_acc_type;					//ͨ�Ű汾��
	           int ver = tRcvdtl.comu_ver / 10;
	           if( 0x81 == tRcvdtl.comu_ver || 0x81 == ver )
	           {		     	
		       tRcvdtl.fee_code = rPack->lbank_acc_type2;			// ������ԭ�򱣴浽�շѿ�Ŀ��
             	}
	           else
	            {
	          	tRcvdtl.fee_code = 0;
	            }
	            des2src(tRcvdtl.crc,rPack->sbank_code2);				//CRCУ��

               	in_balance = rPack->lvol9;								//�뿨���
	             out_balance = rPack->lvol10;							//�������
	            man_fee = rPack->lvol1;								    //Ϊ����
	           trade_fee = rPack->lvol8;								//�������ѽ��
	            tRcvdtl.in_bala = in_balance;
	            tRcvdtl.out_bala = out_balance;
	            tRcvdtl.amount = trade_fee;
	            tRcvdtl.manage_fee = man_fee;
	            tRcvdtl.card_no= rPack->lvol5;							//���׿���
               	tRcvdtl.purse_no = rPack->lvol6;						//����Ǯ����						
	            tRcvdtl.total_cnt= rPack->lvol7;							//��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
               	tRcvdtl.tx_code = 930031;								//���״���
            		snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//��������(��ʽ�����������)
               	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//����ʱ��(��ʽ�������ʱ��)
	            getsystimestamp(tRcvdtl.col_timestamp);
	              ret=check(&tRcvdtl);
	 
                	if(ret)
	              {
	                  	tRcvdtl.err_code=ret;
	            	if(tRcvdtl.tx_mark==2)
		          	tRcvdtl.status[0]='6';								//��;�ο�����
 	             else
 	            	{
		            tRcvdtl.status[0]='5';								//��Ч����
		           	strncpy(tRcvdtl.deal_date,tRcvdtl.col_timestamp,8);
		          	strncpy(tRcvdtl.deal_time,tRcvdtl.col_timestamp+8,6);
		             }
	              }
	            else
		        tRcvdtl.status[0]='1';
			writelog(LOG_ERR,"DB_t_pif_device_read_by_devphy999_id[%d]",ret);
			ret=DB_t_pif_device_read_by_devphy999_id(tRcvdtl.device_id,&device);
			if(ret)
			{
				if(DB_NOTFOUND == ret)
					return  E_DB_DEVICE_N;
				else
					return E_DB_DEVICE_R;
				
			}
	              txdtl.device_id=device.device_id;
			des2src(txdtl.tx_date, tRcvdtl.tx_date);
			des2src(txdtl.tx_time, tRcvdtl.tx_time);
			writelog(LOG_ERR,"DB_t_pif_card_read_by_card_id[%d]",ret);
			ret=DB_t_pif_card_read_by_card_id(tRcvdtl.card_no,&card);
			if(ret)
			{
				writelog(LOG_ERR,"DB_t_pif_card_read_by_card_id error,card_id=[%d],errcode=[%d]",tRcvdtl.card_no,ret);
				if(DB_NOTFOUND==ret)
					return E_CARDNO_NOT_EXIST;
				else
					return E_DB_CARD_R;
			}
			des2src(txdtl.phycard_no, card.physical_no);
			writelog(LOG_ERR,"txdtl.phycard_no[%d]",txdtl.phycard_no);
			txdtl.serial_no=tRcvdtl.serial_no;
			txdtl.cust_id=card.cosumer_id;
			txdtl.card_no=tRcvdtl.card_no;
			txdtl.tx_mark=tRcvdtl.tx_mark;
			des2src(txdtl.crc, tRcvdtl.crc);
			txdtl.sys_id=tRcvdtl.sys_id;
			des2src(txdtl.col_date,tRcvdtl.deal_date);
			des2src(txdtl.col_time,tRcvdtl.deal_time);
			writelog(LOG_ERR,"1[%d]",ret);
		      ret = DB_t_door_txdtl_add(&txdtl);
			  writelog(LOG_ERR,"2[%d]",ret);
	             g_dbchkerr=0;
	            ret = DB_t_tif_rcvdtl_add(&tRcvdtl);
	            g_dbchkerr=1;
	            if (ret)
	           {
		          writelog(LOG_DEBUG,"old serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",tRcvdtl.serial_no,tRcvdtl.card_no,tRcvdtl.device_id,tRcvdtl.tx_date,tRcvdtl.tx_time);
		           if(DB_REPEAT==ret)
		          	return 0;
	              	else
		           	*pRetCode = E_DB_TRADESERIAL_I;
		          goto L_RETU;
	             }
	  }
	else
	{
	          /*
	                memset(&extposdtl,0,sizeof(extposdtl));
	               extposdtl.devseqno= rPack->lvol4;							//�ϴ�����ˮ��
	               extposdtl.transmark=rPack->lvol12;							//999���ױ��
	               extposdtl.sysid= rPack->lcert_code;					    	//�ϴ�����վ��ʶ(ǰ�û�ע���)
                 	des2src(extposdtl.devphyid, rPack->sdate1);				    //�����豸ID
                  	extposdtl.cardbefbal= rPack->lvol9/100.0;								//�뿨���
                 	extposdtl.cardaftbal= rPack->lvol10/100.0;							//�������
                  	extposdtl.amount= rPack->lvol8/100.0;								//�������ѽ��
	                extposdtl.cardno= rPack->lvol5;						    	//���׿���
                    	extposdtl.purseno= rPack->lvol6;					    	//����Ǯ����						
                   	extposdtl.cardcnt= rPack->lvol7;					        //��ǰ�����ʻ����Ѵ���(�ۼ�ʹ�ô���)
                 	extposdtl.transcode= 847306;								//���״���
                	snprintf(extposdtl.transdate,9,"20%s",rPack->spost_code);		//��������(��ʽ�����������)
					
					

					des2src(extposdtl.transtime,rPack->spost_code2);			 //����ʱ��(��ʽ�������ʱ��)
	              getsysdate(extposdtl.coldate);                               //�ɼ�����
	              getsystime(extposdtl.coltime);                                //�ɼ�ʱ��
	               extposdtl.shopid=0;
	              ret=checktRcvdtl(&extposdtl);
				   if((rPack->lvol9-rPack->lvol10!=rPack->lvol8)||(rPack->lvol8==0))
	              {
		           ret=E_999_CARD_BALANCE;					   //�ϴ���ˮ���뿨�������
	              }
	               if(ret)
	              {
	                des2src(extposdtl.status,"4");
	              	extposdtl.errcode=ret;
	                }
	               else
	            	extposdtl.status[0]='1';
	               g_dbchkerr=0;
	               ret = DB_t_extposdtl_add(&extposdtl);
	              g_dbchkerr=1;
	            if (ret)
	           {
		           writelog(LOG_DEBUG,"serial_no[%d]card_no[%d]device_id[%s]tx_date[%s]tx_time[%s]",extposdtl.termseqno,extposdtl.cardno,extposdtl.devphyid,extposdtl.transdate,extposdtl.transtime);
		             if(DB_REPEAT==ret)
		            	return 0;
		            else
		    	*pRetCode = E_DB_EXTPOSDTL_I;
		             goto L_RETU;
	             }
	             */
	}

	return 0;
L_RETU:
	return -1;
}

