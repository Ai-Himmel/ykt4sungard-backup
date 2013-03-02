/* --------------------------------------------
 * 程序名称: F940031.sqc
 * 创建日期: 2010-11-29
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  收集车载消费流水入账
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
		return E_999_CRC;						    	//上传流水CRC校验错误
	}
	ret=IsInvalidDateTime(p->tx_date,"YYYYMMDD");
	if(ret)
	{
		return E_999_DATE;							   //上传流水交易日期有误
	}
	ret=IsInvalidDateTime(p->tx_time,"HHMMSS");
	if(ret)
	{
		return E_999_TIME;							   //上传流水交易时间有误
	}
	if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			       //把返回码置为交易标记
	}
	if(p->in_bala- p->out_bala!=p->amount)
	{
		return E_999_CARD_BALANCE;				    	//上传流水出入卡余额有误
	}
	if(0X99==p->tx_mark)
	{
		if(p->amount<0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
		if(p->amount-p->manage_fee<0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	else
	{
		//冲正交易,发生额为负数
		if(p->amount>0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
		if(p->amount-p->manage_fee>0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
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
		return E_999_DATE;						    	//上传流水交易日期有误
	}
	ret=IsInvalidDateTime(p->transtime,"HHMMSS");
	if(ret)
	{ 
	writelog(LOG_ERR,"IsInvalidDateTime[%s]",p->transtime);
		return E_999_TIME;						    	//上传流水交易时间有误
	}
	/*if((p->tx_mark!=0X99)&&(p->tx_mark!=0xFE)	)
	{
		return 	p->tx_mark+E_999_0X00;			//把返回码置为交易标记
	}
	*/
	
	/*
	if(0X99==p->tx_mark)
	{
		if(p->amount<=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
		if(p->amount-p->manage_fee<0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
	}
	else
	{
		//冲正交易,发生额为负数
		if(p->amount>=0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
		}
		if(p->amount-p->manage_fee>0)
		{
			return E_999_AMT;							//上传流水交易发生金额有误
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
	           tRcvdtl.serial_no= rPack->lvol4;							//上传端流水号
	           tRcvdtl.tx_mark=rPack->lvol12;							//999交易标记
	            tRcvdtl.sys_id  = rPack->lcert_code;						//上传工作站标识(前置机注册号)
	           des2src(tRcvdtl.device_id, rPack->sdate1);				//物理设备ID
	           des2src(tRcvdtl.inpower_no,rPack->stx_pwd);				//终端设备授权号
	           tRcvdtl.comu_ver=rPack->lbank_acc_type;					//通信版本号
	           int ver = tRcvdtl.comu_ver / 10;
	           if( 0x81 == tRcvdtl.comu_ver || 0x81 == ver )
	           {		     	
		       tRcvdtl.fee_code = rPack->lbank_acc_type2;			// 将启动原因保存到收费科目中
             	}
	           else
	            {
	          	tRcvdtl.fee_code = 0;
	            }
	            des2src(tRcvdtl.crc,rPack->sbank_code2);				//CRC校验

               	in_balance = rPack->lvol9;								//入卡金额
	             out_balance = rPack->lvol10;							//出卡金额
	            man_fee = rPack->lvol1;								    //为负数
	           trade_fee = rPack->lvol8;								//本次消费金额
	            tRcvdtl.in_bala = in_balance;
	            tRcvdtl.out_bala = out_balance;
	            tRcvdtl.amount = trade_fee;
	            tRcvdtl.manage_fee = man_fee;
	            tRcvdtl.card_no= rPack->lvol5;							//交易卡号
               	tRcvdtl.purse_no = rPack->lvol6;						//消费钱包号						
	            tRcvdtl.total_cnt= rPack->lvol7;							//当前卡中帐户消费次数(累计使用次数)
               	tRcvdtl.tx_code = 930031;								//交易代码
            		snprintf(tRcvdtl.tx_date,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
               	des2src(tRcvdtl.tx_time,rPack->spost_code2);			//发生时间(格式化输入的时间)
	            getsystimestamp(tRcvdtl.col_timestamp);
	              ret=check(&tRcvdtl);
	 
                	if(ret)
	              {
	                  	tRcvdtl.err_code=ret;
	            	if(tRcvdtl.tx_mark==2)
		          	tRcvdtl.status[0]='6';								//中途拔卡交易
 	             else
 	            	{
		            tRcvdtl.status[0]='5';								//无效交易
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
	               extposdtl.devseqno= rPack->lvol4;							//上传端流水号
	               extposdtl.transmark=rPack->lvol12;							//999交易标记
	               extposdtl.sysid= rPack->lcert_code;					    	//上传工作站标识(前置机注册号)
                 	des2src(extposdtl.devphyid, rPack->sdate1);				    //物理设备ID
                  	extposdtl.cardbefbal= rPack->lvol9/100.0;								//入卡金额
                 	extposdtl.cardaftbal= rPack->lvol10/100.0;							//出卡金额
                  	extposdtl.amount= rPack->lvol8/100.0;								//本次消费金额
	                extposdtl.cardno= rPack->lvol5;						    	//交易卡号
                    	extposdtl.purseno= rPack->lvol6;					    	//消费钱包号						
                   	extposdtl.cardcnt= rPack->lvol7;					        //当前卡中帐户消费次数(累计使用次数)
                 	extposdtl.transcode= 847306;								//交易代码
                	snprintf(extposdtl.transdate,9,"20%s",rPack->spost_code);		//发生日期(格式化输入的日期)
					
					

					des2src(extposdtl.transtime,rPack->spost_code2);			 //发生时间(格式化输入的时间)
	              getsysdate(extposdtl.coldate);                               //采集日期
	              getsystime(extposdtl.coltime);                                //采集时间
	               extposdtl.shopid=0;
	              ret=checktRcvdtl(&extposdtl);
				   if((rPack->lvol9-rPack->lvol10!=rPack->lvol8)||(rPack->lvol8==0))
	              {
		           ret=E_999_CARD_BALANCE;					   //上传流水出入卡余额有误
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

