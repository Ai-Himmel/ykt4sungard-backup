/* --------------------------------------------
 * ��������: F847301.c
 * ��������: 2006-12-12
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ˮ�ش�Ǯ��תСǮ��
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

static int process(InAcc * IA, T_t_tif_tradeserial * p)
{
    int ret = 0;
    //���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
    IA->iMainDevId = p->maindevice_id;                  //����վ��ʾ
    IA->iDevId = p->device_id;                          //�豸ID��
    IA->iSerialNo = p->serial_no;                       //��ˮ��
    IA->iTradeNo = p->serial_type;                      //���״��� 
    strcpy(IA->sTxDate, p->operate_date);               //��������
    strcpy(IA->sTxTime, p->operate_time);               //����ʱ��
    strcpy(IA->sTxCollectDate, p->collect_date);        //�ɼ�����
    strcpy(IA->sTxCollectTime, p->collect_time);        //�ɼ�ʱ��
    strcpy(IA->sTxAccDate, p->enteract_date);           //��������
    strcpy(IA->sTxAccTime, p->enteract_time);           //����ʱ��

    IA->iTxCnt = p->trade_count;                        //���״���
    IA->iUseCardFlag = USE_CARD_TYPE_ONLINE;            //��������
    IA->dInCardBala = p->in_balance;                    //�뿨ֵ
    IA->dOutCardBala = -1;                              //����ֵ

    // �޸Ľ跽�ʹ������ʻ����, �ǻ�Ʒ�¼����
    ret = AccountProcess(IA);
    if (ret)
    {
        writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
        return ret;
    }
    p->out_balance = IA->dOutCardBala;                  //����ֵ          
    return 0;
}

int F847301(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
    T_t_tif_tradeserial tSerial, tPacketSerial;
    T_t_aif_account tAccount;
    T_t_pif_card tCard;
    T_t_cif_customer tCustomer;
    T_t_tif_writefailed tWriteFailed;
    InAcc IA;

    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

    int ret = 0;
    int TxTypeCount = 0;
    int hi_cardid = 0;             //���׿���
    char buf[100 + 1] = "";
    char sysdate[11] = "";
    char systime[7] = "";
    char logicdate[11] = "";
    char sMsg[128] = "";
//    char temp_account_id[16 + 1] = "2081";             //������ʱ�ʻ�
    double dUniqNo = 0;                              //�����ˮ��
    double in_balance = 0;
    double small_packet_balance = 0;                    //СǮ���е����
    double max_balance = 0;                           //СǮ���������  
    double transfer_price = 0;                          //ת����

    memset(&tAccount, 0, sizeof tAccount);
    memset(&tCard, 0, sizeof tCard);
    memset(&tCustomer, 0, sizeof tCustomer);
    memset(&IA, 0, sizeof IA);
    memset(&tPacketSerial, 0, sizeof tPacketSerial);
    memset(&tWriteFailed, 0, sizeof tWriteFailed);

    memset(&aPack,0,sizeof aPack);
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL1,F_DAMT0,F_DAMT2,F_VSMESS,F_LVOL9,F_LVOL5,0);

    hi_cardid = rPack->lvol0;
    if (hi_cardid <= 0)
    {
        *pRetCode = E_INPUT_CARDNO;
        goto L_RETU;
    }

    //�ж�СǮ���е����
    small_packet_balance = rPack->damt3;

    //��ȡСǮ���������
    ret = GetParameter(GLB_PACKET_LIMITS,buf);
    if (ret)
    {
        *pRetCode = ret;
        goto L_RETU;
    }
    max_balance = atof(buf);
    if (amtcmp(max_balance,0) <= 0)
    {
        *pRetCode = E_GLOBAL_PARAM_ERROR;
        goto L_RETU;
    }

    //�жϳ�ֵ��СǮ���Ľ��
    transfer_price = rPack->damt4;               //Ǯ��ת����

    writelog(LOG_DEBUG,"tranfser_price=[%d]",transfer_price);
    writelog(LOG_DEBUG,"small_packet_balance=[%d]",small_packet_balance);
    if (amtcmp(transfer_price, 0) <= 0 || amtcmp(small_packet_balance, 0) < 0)
    {
        *pRetCode = E_INPUT_DATA_INVAILD;
        goto L_RETU;
    }

    if (amtcmp(small_packet_balance + transfer_price,max_balance) > 0)
    {
        sprintf(sMsg, "Ǯ�����������%f��", max_balance);
        *pRetCode = E_PACKET_LIMIT_EXCEED;
        goto L_RETU;
    }

    in_balance = rPack->damt1;
    if (amtcmp(in_balance,0.0) < 0)
    {
        *pRetCode = E_BALANCE_SHORTAGE;
        goto L_RETU;
    }
    
    ret = DB_t_pif_card_read_by_card_id(hi_cardid,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
		{
		    *pRetCode = E_DB_CARD_N;
		}
		else
		{
		    *pRetCode = E_DB_CARD_R;
	    }
	    goto L_RETU;
	}
	
    //�жϿ������Ƿ���ȷ
    /*
    if (CheckUserPswd(rPack->semp_pwd,tCard.password))
    {
        writelog(LOG_ERR,"Card password error");
        *pRetCode = E_TRANS_SCHCARD_PWDERR;
        goto L_RETU;
    }
    */
    
    if (strncmp(tCard.state_id, TYPE_YES, 1) != 0)
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        *pRetCode = E_TRANS_SCHACC_DESTORY;
        goto L_RETU;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_LOST])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        *pRetCode = E_TRANS_SCHCARD_LOSTING;
        goto L_RETU;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_FREEZE])
    {
        writelog(LOG_ERR,"card_state=[%s]",tCard.state_id);
        *pRetCode = E_TRANS_SCHCARD_FREEZE;
        goto L_RETU;
    }

    if (STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_WFAIL])
    {
        *pRetCode = E_CARDNO_WFAIL;
        goto L_RETU;
    }

    ret = DB_t_cif_customer_read_by_cut_id(tCard.cosumer_id,&tCustomer);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_CUSTOMER_N;
        }
        else
        {
            *pRetCode = E_DB_CUSTOMER_R;
        }
        goto L_RETU;
    }

    //��ȡ�����ʻ�
    ret = DB_t_aif_account_read_by_card_id_and_purse_id(tCard.card_id,PURSE_NO_ONE,&tAccount);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_ACCOUNT_N;
        }
        else
        {
            *pRetCode = E_DB_ACCOUNT_R;
        }
        goto L_RETU;
    }
    //������ʱ�ʻ���������, ����Ҫ��ѯ
    ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqNo);              // ��������ˮ��
    if (ret)
    {
        writelog(LOG_ERR,"ret[%d]",ret);
        *pRetCode = ret;
		goto L_RETU;
    }

    getsysdate(sysdate);
    getsystime(systime);
    GetLogicDate(logicdate);
    memset(&tSerial, 0, sizeof tSerial);
    tSerial.serial_no = D2I(dUniqNo);
    tSerial.other_seri_no = 0;
    tSerial.serial_state = SERISTAT_DEBT;                           //��ˮ״̬
    tSerial.serial_type = TXCODE_CONSUME;                           //��������
    des2src(tSerial.operate_date,sysdate);                           //��������
    des2src(tSerial.operate_time,systime);                           //����ʱ��
    des2src(tSerial.collect_date,sysdate);                           //�ɼ�����
    des2src(tSerial.collect_time,systime);                           //�ɼ�ʱ��
    des2src(tSerial.enteract_date,logicdate);                        //��������
    des2src(tSerial.enteract_time,systime);                          //����ʱ��

//    tSerial.maindevice_id = rPack->lvol3;                            //�ϴ�����վ��ʶ
    tSerial.device_id = 0;                                          //�ɼ��豸��ʶ 
    tSerial.card_id = hi_cardid;                                    //���׿���
    des2src(tSerial.showid,tCard.showid);                           //��ʾ����
    tSerial.purse_id = PURSE_NO_ONE;                                //Ǯ����
    tSerial.customer_id = tCard.cosumer_id;                         //�ͻ���
    des2src(tSerial.oper_code, rPack->scust_no);                      //����Ա����
    tSerial.sys_id = 0;
    tSerial.trade_count = rPack->lvol4 + 1;                          //�����״���
    tSerial.trade_fee = transfer_price;                             //תǮ���
    tSerial.in_balance = in_balance;                                //�뿨ֵ
    writelog(LOG_DEBUG,"ˮ��ת���뿨ֵ[%.2lf]",in_balance);
    des2src(IA.sArrInActno[0],tAccount.account_id);                 //�����ʻ�
//  des2src(IA.sArrInActno[1],temp_account_id);                  //������ʱ�ʻ�
    IA.dArrInAmt[0] = tSerial.trade_fee;                            //���׽��
    IA.iCardNo = tCard.card_id;                                     //���׿���
    IA.iFeeType = tCustomer.fee_type;                               //�ͻ��շ�����

    //����������ģ��
    ret = process(&IA,&tSerial);
    if (ret)
    {
        writelog(LOG_ERR,"process ret[%d]",ret);
        *pRetCode = ret;
        goto L_RETU;
    }
    sprintf(out_pack->vsmess,"��ˮ��:%d ����:%d ",IA.iSerialNo,IA.iCardNo);
	for(TxTypeCount = 1; TxTypeCount <= IA.iOutTxTypeCnt; TxTypeCount++)
	{
		switch(IA.iArrOutTxType[TxTypeCount])
		{
			case TXTYPE_TOLL_DEPOSIT:
			case TXTYPE_TOLL_DEPOSIT_BILL:
			case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
			case TXTYPE_DEDUCT_DEPOSIT:
			case TXTYPE_RETURN_DEPOSIT:
				tSerial.deposit_fee = IA.dArrOutAmt[TxTypeCount];
				break;
			case TXTYPE_PRE_TOLL_BOARD:
			case TXTYPE_PRE_TOLL_BOARD_BILL:
			case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
			case TXTYPE_TOLL_BOARD:
			case TXTYPE_DEDUCT_BOARD:
			case TXTYPE_RETURN_BOARD:
			case TXTYPE_RETURN_BOARD_BILL:
			case TXTYPE_RETURN_BOARD_FUNDBOOK:
				tSerial.boardfee = IA.dArrOutAmt[TxTypeCount];
				break;
			case TXTYPE_TOLL_CHARGE:
			case TXTYPE_TOLL_CHARGE_BILL:
			case TXTYPE_TOLL_CHARGE_FUNDBOOK:
				tSerial.in_fee = IA.dArrOutAmt[TxTypeCount];
				break;
			case TXTYPE_TOLL_CARDCOST:
			case TXTYPE_TOLL_CARDCOST_BILL:
			case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
				tSerial.cost_fee = IA.dArrOutAmt[TxTypeCount];
				break;
			default:
				break;
		}
		if (amtcmp(IA.dArrOutAmt[TxTypeCount], 0) != 0)
		{
		    sprintf(sMsg,"%s:%.2lfԪ ", IA.sArrOutTxName[TxTypeCount], IA.dArrOutAmt[TxTypeCount]);
			strcat(out_pack->vsmess, sMsg);
		}
	}
	sprintf(sMsg, "����ǰ���:%.2lfԪ", tSerial.out_balance);
	strcat(out_pack->vsmess, sMsg);
	writelog(LOG_DEBUG,out_pack->vsmess);

	//���뽻����ˮ��
	ret = DB_t_tif_tradeserial_add(&tSerial);
	if (ret)
	{
	    writelog(LOG_ERR,"ret[%d]",ret);
		if (DB_REPEAT == ret)
		{
		    *pRetCode = E_DB_TRADESERIAL_E;
		}
		else
		{
		    *pRetCode = E_DB_TRADESERIAL_I;
		}
		goto L_RETU;
	}
	//�����ֵ��ˮ
	memcpy(&tPacketSerial, &tSerial, sizeof tPacketSerial);
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqNo);  						//��������ˮ��
	if(ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	tPacketSerial.serial_no = D2I(dUniqNo);
	tPacketSerial.serial_state = SERISTAT_NONEEDDEBT;
	tPacketSerial.serial_type = TXCODE_SAVING_SMALL_PACKET;
	tPacketSerial.purse_id = PURSE_NO_TWO;
	tPacketSerial.trade_count = rPack->lvol5 + 1;
    des2src(tPacketSerial.oper_code, rPack->scust_no);
	tPacketSerial.in_balance = small_packet_balance;
	tPacketSerial.trade_fee = transfer_price;
	tPacketSerial.out_balance = small_packet_balance + tPacketSerial.trade_fee;
	
	ret = DB_t_tif_tradeserial_add(&tPacketSerial);
	if(ret)
	{
		if(DB_REPEAT == ret)
		{
	        *pRetCode = E_DB_TRADESERIAL_E;	
		}
		else
		{
		    *pRetCode = E_DB_TRADESERIAL_I;
		}
		goto L_RETU;
	}
	out_pack->lvol0 = tSerial.serial_no;
	out_pack->lvol1 = tPacketSerial.serial_no;
	out_pack->damt2 = tPacketSerial.out_balance;
	out_pack->damt0 = tSerial.out_balance;
	out_pack->lvol9 = tSerial.trade_count;
	out_pack->lvol5 = tPacketSerial.trade_count;
	writelog(LOG_DEBUG,"ˮ��Ǯ�����[%.2lf], ����ֵ[%.2lf]",out_pack->damt2,out_pack->damt0);
	
	PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
	return -1;	
}

