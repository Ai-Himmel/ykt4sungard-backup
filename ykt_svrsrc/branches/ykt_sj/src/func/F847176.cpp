/* --------------------------------------------
 * ��������: F847176.c
 * ��������: 2010-04-08
 * ��������: xlh
 * �汾��Ϣ: 1.0.0.0
 * ������: ������ˮ�ֹ���-�ֹ���
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "account.h"
#include "fdsqc.h"

static int getacc(char *divphi,T_t_aif_account *acc)
{  
   // T_t_aif_account accrt=&acc;
    int ret=0;
	T_t_pif_device device;
	memset(&device,0,sizeof(device));
	T_t_cif_shop_pos shoppos;
	memset(&shoppos,0,sizeof(shoppos));
	T_t_cif_shop shop;
	memset(&shop,0,sizeof(shop));
	T_t_aif_account accrt;
	memset(&accrt,0,sizeof(accrt));
	ret=DB_t_pif_device_read_by_devphy999_id(divphi,&device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_by_devphy999_id err [%s]",divphi);
		return ret;
	}
	writelog(LOG_ERR,"shipid ret[%d]",device.device_id);
    ret=DB_t_cif_shop_pos_read_by_device_id(device.device_id,&shoppos);
	if (ret)
	{
		writelog(LOG_ERR," DB_t_cif_shop_pos_read_by_device_id err [%d]",device.device_id);
		return ret;
	 }
	ret=DB_t_cif_shop_read_by_shop_id(shoppos.shop_id,&shop);
	if (ret)
	{
		writelog(LOG_ERR," DB_t_cif_shop_read_by_shop_id err [%d]",shoppos.shop_id);
		return ret;
	 }
	ret = DB_t_aif_account_read_by_customer_id_and_act_type(
		shop.cut_id,ACCTYPE_SHOPMAIN,&accrt);
	if (ret)
	{
		writelog(LOG_ERR," DB_t_aif_account_read_by_customer_id_and_act_type err [%d]",shop.cut_id);
		return ret;
	 }
     strcpy(acc->account_id,accrt.account_id);
	 return 0;
}

static int process(InAcc *IA,T_t_tif_tradeserial *p)
{
	int ret=0;

	IA->iMainDevId=p->maindevice_id;				//����վ��ʶ
	IA->iDevId=p->device_id;						//�豸ID
	IA->iSerialNo=p->serial_no;					//��ˮ��
	IA->iTradeNo=p->serial_type;					//������
	strcpy(IA->sTxDate,p->operate_date);			//��������
	strcpy(IA->sTxTime,p->operate_time);			//����ʱ��
	strcpy(IA->sTxCollectDate,p->collect_date);		//�ɼ�����
	strcpy(IA->sTxCollectTime,p->collect_time);		//�ɼ�ʱ��
	strcpy(IA->sTxAccDate,p->enteract_date);		//��������
	strcpy(IA->sTxAccTime,p->enteract_time);		//����ʱ��
	strcpy(IA->sChkOper,p->oper_code);			//���˲���Ա

	IA->iUseCardFlag=USE_CARD_TYPE_NULL;		//�޿�����
	IA->iTxCnt=0;								//���״���
	IA->dInCardBala=0;							//�뿨ֵ
	IA->dOutCardBala=0;							//����ֵ

	//�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
	ret=AccountProcess(IA);
	if(ret)
	{
		writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
		return ret;
	}
	p->out_balance=IA->dOutCardBala;			//����ֵ
	if(amtcmp(p->out_balance,0)<0)
	{
		return E_ENTER_ACCOUNT;
	}
	return 0;
}

int F847176(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int i=0;
	int ret =0;
	char logicdate[11]="";										//ҵ������
	char sysdate[11]="";
	char systime[9]="";
	InAcc	IA;
	char  ia_buf[1024]="";
	char sbank_acc[41]="";
	char sbank_acc2[41]="";
	double dUniqno = 0;
	char sMsg[256]="";
	char    tx_date[8+1]="";              	//��������
	char    tx_time[6+1]="";      		//����ʱ��
	int		card_no=0;                    	//����
	char    deviceph_id[8+1]="";            	//�ն˻�ID
	int		serial_no=0;
	T_t_tif_tradeserial tradeserial;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
    T_t_tif_rcvdtl		tRcvdtl;
	memset(&tRcvdtl,0,sizeof(tRcvdtl));
	memset(&tradeserial,0,sizeof(tradeserial));
	T_t_aif_account account;
	memset(&account,0,sizeof(account));
	memset(&IA,0,sizeof(IA));
	T_t_pif_device device;
	memset(&device,0,sizeof(device));
	IA.pVoidPointer=ia_buf;
	ResetNormalCPack(&aPack,0,1);

/*	if(amtcmp(rPack->damt0,0)==0)
	{
		*pRetCode=E_INPUT_AMT_NULL;
		goto L_RETU;
	}
	*/
	if(strlen(rPack->semp)==0)
	{
		*pRetCode=E_INPUT_OPER_NULL;
		goto L_RETU;
	}
	des2src(tx_time,rPack->sbank_pwd);
	des2src(tx_date,rPack->sdate0);
	card_no=rPack->lvol0;
	des2src(deviceph_id,rPack->sbank_pwd2);
	serial_no=rPack->lvol1;
	writelog(LOG_ERR,"tx_date[%s],tx_time[%s],card_no[%d],device_id[%s],serial_no[%d]",tx_date,tx_time,card_no,deviceph_id,serial_no);
	ret=DB_t_tif_rcvdtl_read_lock_by_c0_and_tx_date_and_tx_time_and_card_no_and_device_id_and_serial_no(tx_date,tx_time,card_no,deviceph_id,serial_no,&tRcvdtl);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
		{
			writelog(LOG_ERR,"tx_date[%s],tx_time[%s],card_no[%d],device_id[%s],serial_no[%d]",tx_date,tx_time,card_no,deviceph_id,serial_no);
			*pRetCode=E_SERIALNO_NOT_EXIST;
		}
		else
		{
			*pRetCode=E_DB_RCVDTL_R;
			writelog(LOG_ERR,"read_lock t_tif_rcvdtl err ret[%d]",ret);
		}
		goto L_RETU;
	}
	if(tRcvdtl.status[0]!='9')
	{
		*pRetCode=E_TX_CANNOT_DEAL;
		DB_t_tif_rcvdtl_free_lock_c0();
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);							//ҵ������
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	tradeserial.trade_fee = tRcvdtl.amount;						//�������
	ret=DB_t_pif_device_read_by_devphy999_id(deviceph_id,&device);
	if(ret)
	{
		writelog(LOG_ERR,"DB_t_pif_device_read_by_devphy999_id err [%s]",deviceph_id);
		return ret;
	}
	ret=getacc("00000000",&account);
	if (ret)
	  {
		writelog(LOG_ERR," ����ʺ�ʧ�� err [%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	  }
	strcpy(sbank_acc,account.account_id);
	//memset(account,0,sizeof(account));
	ret=getacc(deviceph_id,&account);
	if (ret)
		{
		writelog(LOG_ERR," ����ʺ�ʧ�� err [%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	  }
	strcpy(sbank_acc2,account.account_id);
	writelog(LOG_ERR," sbank_acc[%s],sbank_acc2 [%s]",sbank_acc,sbank_acc2);
	tradeserial.device_id=device.device_id;
	des2src(tradeserial.out_account_id,sbank_acc);//����
	des2src(tradeserial.in_account_id,sbank_acc2);//����
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  		//��������ˮ��
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR," ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(dUniqno);							//��ˮ��
	tradeserial.other_seri_no = 0;								//�ϴ�����ˮ��
	tradeserial.serial_type  = TXCODE_CARD_DBCR;				//������
	tradeserial.serial_state = SERISTAT_DEBT;						//��ˮ״̬
	des2src(tradeserial.operate_date,sysdate);					//��������
	des2src(tradeserial.operate_time,systime);					//����ʱ��
	des2src(tradeserial.collect_date,sysdate);						//�ɼ�����
	des2src(tradeserial.collect_time,systime);						//�ɼ�ʱ��
	des2src(tradeserial.enteract_date,logicdate);					//��������
	des2src(tradeserial.enteract_time,systime);					//����ʱ��
	tradeserial.maindevice_id = rPack->lvol6;						//�ϴ�����վ��ʶ
	tradeserial.in_balance=rPack->damt0;						//�뿨ֵ
	tradeserial.trade_count=0;									//���״���
	des2src(tradeserial.oper_code,rPack->semp);			//����Ա����
	tradeserial.sys_id = 0;										//�ⲿϵͳ��ʶ
	des2src(tradeserial.reserve_1,"������ˮ����");
	IA.iCardNo=0;
	IA.iFeeType=1;
	IA.dArrInAmt[0]=tradeserial.trade_fee;
	des2src(IA.sArrInActno[0],tradeserial.out_account_id);				//�跽�ʺ�
	des2src(IA.sArrInActno[1],tradeserial.in_account_id);				//�����ʺ�
	IA.iArrInFeeSwitch[0]=rPack->lvol0;
	IA.iArrInFeeSwitch[1]=rPack->lvol1;
	IA.iArrInFeeSwitch[2]=rPack->lvol2;
	IA.iArrInFeeSwitch[3]=rPack->lvol3;
	IA.iArrInFeeSwitch[4]=rPack->lvol4;
	IA.iArrInFeeSwitch[5]=rPack->lvol5;
	writelog(LOG_ERR," ��ʼ���� err [%d]",ret);
	ret=process(&IA,&tradeserial);
	if(ret)
	{
		writelog(LOG_ERR,"process ret[%d]",ret);
		*pRetCode=ret;
		goto L_RETU;
	}
	sprintf(out_pack->vsmess,"��ˮ��:%d ",IA.iSerialNo);
	for(i=1;i<=IA.iOutTxTypeCnt;i++)
	{
		if(amtcmp(IA.dArrOutAmt[i],0)!=0)
		{
			sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
			strcat(out_pack->vsmess,sMsg);
		}
	}
	strcat(out_pack->vsmess,(char*)IA.pVoidPointer);
	writelog(LOG_DEBUG,out_pack->vsmess);
	SetCol(handle,0);
	SetCol(handle,F_LSERIAL1,F_DAMT2,F_DAMT3,F_DAMT4,F_VSMESS,0);
	out_pack->lserial1=tradeserial.serial_no;			//��ˮ��
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	des2src(tRcvdtl.oper_no,rPack->semp);
	des2src(tRcvdtl.deal_date,sysdate);
	des2src(tRcvdtl.deal_time,systime);
    tRcvdtl.status[0]='3';          				//1-δ����2-ʧ��3-�ɹ�
	ret=DB_t_tif_rcvdtl_update_lock_by_c0(&tRcvdtl);
	if(ret)
	{
	        *pRetCode=E_DB_RCVDTL_U;
	        writelog(LOG_ERR,"DB_t_tif_rcvdtl_update_lock_by_c1[%d]",ret);
	        goto L_RETU;
	}
	DB_t_tif_rcvdtl_free_lock_c0();
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

