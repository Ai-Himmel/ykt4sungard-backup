/* --------------------------------------------
 * �޸�����: 2009-11-17
 * �޸���  : �����
 * ������: ���շ���� (��ǰ������ѵ)
 * --------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "mypub.h"
#include "pubfunc.h"
#include "account.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "svrlink.h"

int F847140(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	    int hi_cardid = 0;             //���׿���
	    int hi_day = 0;					// ��ǰ������
	    int hi_card_cnt = 0;
	    double hi_card_bala = 0;			// �����
	    double service_fee = 0;		//ÿ��ķ���ѽ��
	    char   fee_buf[20]="";
	double dUniqNo = 0;                              //�����ˮ��
	char sysdate[11] = "";
    	char systime[7] = "";
	char logicdate[11] = "";
	
    	T_t_pif_card tCard;
	T_t_aif_account tAccount;
	T_t_tif_tradeserial tSerial;
	T_t_cif_customer tCustomer;
	InAcc IAE;
	T_t_cif_cut_svrfee tCutsvrfee;

	memset(&tSerial, 0, sizeof(tSerial));
	memset(&tCard, 0, sizeof(tCard));
	memset(&tAccount,0,sizeof(tAccount));
	memset(&tCustomer, 0, sizeof(tCustomer));
	memset(&IAE, 0, sizeof(IAE));
	memset(&tCutsvrfee,0,sizeof tCutsvrfee);


    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack, 0, sizeof(aPack));
	    
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL1,F_VSMESS,F_LSERIAL1,0);

	hi_card_bala = rPack->lvol3/100.0;		
	hi_card_cnt = rPack->lvol2;
//	hi_day = rPack->lvol0;
    	hi_cardid = rPack->lvol1;
	service_fee = rPack->damt0;			//atof(fee_buf)*hi_day;		// ǰֱ̨��������

	if(amtcmp(service_fee, 0)<=0)
		return E_INPUT_ERROR;
    if (hi_cardid <= 0)
       return E_INPUT_CARDNO;
    
    ret = DB_t_pif_card_read_by_card_id(hi_cardid,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		   return E_DB_CARD_N;		
		return E_DB_CARD_R;
	}
	
    if (strncmp(tCard.state_id, TYPE_YES, 1) != 0)
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        return E_CARDNO_LOGOUT;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_FREEZE])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
       	return E_CARDNO_FREEZE;
    }

	 if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_WFAIL])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
       	return E_CARDNO_WFAIL;
    }

	ret = DB_t_aif_account_read_by_card_id_and_purse_id(hi_cardid,PURSE_NO_ONE, &tAccount);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_ACCOUNT_N;
		return E_DB_ACCOUNT_R;
	}

	/*
	if (ret = GetParameter(GLOBAL_SERVICE_FEE, fee_buf))
	{
		writelog(LOG_ERR,"get_parameter error,error code=[%d]",ret);
		return ret;
	}
	*/
	
	if(amtcmp(service_fee, tAccount.cur_freebala)>0)
	   		return E_SVR_FEE_SHORT;
	
	if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_LOST])			// ��ʧ��
    {
    	hi_card_cnt = tAccount.consume_count;
		hi_card_bala = tAccount.cur_freebala;
		IAE.iUseCardFlag = USE_CARD_TYPE_NULL;            
	}
	else
	{
		if( hi_card_cnt <0)
	   		return E_INPUT_CARD_TXCNT;
		if(amtcmp(tAccount.cur_freebala,hi_card_bala)>0			// ��ȿ���
   			&& amtcmp(service_fee, hi_card_bala)>0)
   			return E_SVR_FEE_SHORT;
		 IAE.iUseCardFlag = USE_CARD_TYPE_ONLINE;            //��������
	}

	ret = DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id,&tCustomer);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            ret = E_DB_CUSTOMER_N;
        }
        else
        {
            ret = E_DB_CUSTOMER_R;
        }
        return ret;
    }

    ret = getNewUniqNo(KEYTYPE_TRADESERIAL, &dUniqNo);              // ��������ˮ��
    if (ret)
    {
        writelog(LOG_ERR,"get_new_uniq_no[%d]",ret);
        return ret;
    }

    getsysdate(sysdate);
    getsystime(systime);
    GetLogicDate(logicdate);
    tSerial.serial_no = D2I(dUniqNo);
    tSerial.other_seri_no = 0;
    tSerial.serial_state = SERISTAT_DEBT;                           //��ˮ״̬
    tSerial.serial_type = TXCODE_RECLAIM_SVR_FEE;              		//��������
    des2src(tSerial.operate_date,sysdate);                           //��������
    des2src(tSerial.operate_time,systime);                           //����ʱ��
    des2src(tSerial.collect_date,sysdate);                           //�ɼ�����
    des2src(tSerial.collect_time,systime);                           //�ɼ�ʱ��
    des2src(tSerial.enteract_date,logicdate);                        //��������
    des2src(tSerial.enteract_time,systime);                          //����ʱ��

  	tSerial.maindevice_id = rPack->lvol6;                            
    tSerial.device_id = rPack->lvol7;                               //�ɼ��豸��ʶ 
    tSerial.card_id = hi_cardid;                                 	//���׿���
    des2src(tSerial.showid,tCard.showid);                            	//��ʾ����
    tSerial.purse_id = PURSE_NO_ONE;                                //Ǯ����
    tSerial.customer_id = tCard.cosumer_id;                         	//�ͻ���
    des2src(tSerial.oper_code, rPack->semp);                      //����Ա����
    tSerial.sys_id = 0;
    tSerial.trade_fee = service_fee;                             		//תǮ���
    tSerial.in_balance = hi_card_bala;                                	//Ǯ���뿨ֵ
	tSerial.trade_count=hi_card_cnt+1;									//���״���
	tSerial.out_balance = tSerial.in_balance - service_fee ;            //����ֵ  
	
  //des2src(IAE.sArrInActno[1],account.account_id);                  	//�̻��ʻ�
  	des2src(IAE.sArrInActno[0],tAccount.account_id);					//�跽�ʺ�(����)

    IAE.dArrInAmt[0] = tSerial.trade_fee;                            //���׽��
    IAE.iCardNo = tSerial.card_id;                                     	//���׿���
    IAE.iFeeType = tCustomer.fee_type;                               //�ͻ��շ�����
	IAE.iMainDevId = tSerial.maindevice_id;                  				//����վ��ʾ
    IAE.iDevId = tSerial.device_id;                     //�豸ID��
    IAE.iSerialNo = tSerial.serial_no;                  //��ˮ��
    IAE.iTradeNo = tSerial.serial_type;                 //���״��� 
    strcpy(IAE.sTxDate, tSerial.operate_date);               //��������
    strcpy(IAE.sTxTime, tSerial.operate_time);               //����ʱ��
    strcpy(IAE.sTxCollectDate, tSerial.collect_date);        //�ɼ�����
    strcpy(IAE.sTxCollectTime, tSerial.collect_time);        //�ɼ�ʱ��
    strcpy(IAE.sTxAccDate, tSerial.enteract_date);           //��������
    strcpy(IAE.sTxAccTime, tSerial.enteract_time);           //����ʱ��

    IAE.iTxCnt = tSerial.trade_count;                        //���״���
    IAE.dInCardBala = tSerial.in_balance;                    //�뿨ֵ
    IAE.dOutCardBala = -1;                              //����ֵ
    des2src(IAE.sMdeOper, tSerial.oper_code);                 //����Ա��

    // �޸Ľ跽�ʹ������ʻ����, �ǻ�Ʒ�¼����
    ret = AccountProcess(&IAE);
    if (ret)
    {
        writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
        return ret;
    }
    
 	sprintf(out_pack->vsmess,"���շ������ˮ��:%d ����:%d,���ս��:%.2lf,����ֵ:%.2lf ",IAE.iSerialNo,IAE.iCardNo,tSerial.trade_fee,tSerial.out_balance);

	writelog(LOG_DEBUG,out_pack->vsmess);

	//���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tSerial);
	if (ret)
	{
	    writelog(LOG_ERR,"ret[%d]",ret);  
		if (DB_REPEAT == ret)
	 		return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}

	ret = DB_t_cif_cut_svrfee_read_by_cut_id(tCard.cosumer_id,&tCutsvrfee);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{			
			tCutsvrfee.cut_id = tCard.cosumer_id;
			tCutsvrfee.svrfee_draw = service_fee;				// ���շ����
			des2src(tCutsvrfee.close_date,sysdate);
			ret = DB_t_cif_cut_svrfee_add(&tCutsvrfee);
			if(ret)
				return E_DB_CUT_SVRFEE_I;
		}
		else
			return E_DB_CUT_SVRFEE_R;
	}
	else
	{
		tCutsvrfee.svrfee_draw += service_fee;				// ���շ����
		des2src(tCutsvrfee.close_date,sysdate);
		ret = DB_t_cif_cut_svrfee_update_by_cut_id(tCard.cosumer_id,&tCutsvrfee);
		if(ret)
			return E_DB_CUT_SVRFEE_U;
	}

	out_pack->lvol1= D2I(tSerial.out_balance*100);
	out_pack->lserial1 = tSerial.serial_no;

	PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
	return -1;	
}

