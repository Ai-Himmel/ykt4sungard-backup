/* --------------------------------------------
 * ��������: F47104.c
 * ��������: 2005-08-08
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  ���쿨
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
#include "dbfunc_foo.h"

static int process(InAcc *IA,T_t_tif_tradeserial *p) {
    int ret = 0;

    //���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)
    IA->iMainDevId=p->maindeviceid;			//����վ��ʶ
    IA->iDevId=p->deviceid;					//�豸ID
    IA->iSerialNo=p->serial_no;					//��ˮ��
    IA->iTradeNo=p->serial_type;				//������
    strcpy(IA->sTxDate,p->operate_date);		//��������
    strcpy(IA->sTxTime,p->operate_time);		//����ʱ��
    strcpy(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
    strcpy(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
    strcpy(IA->sTxAccDate,p->enteract_date);	//��������
    strcpy(IA->sTxAccTime,p->enteract_time);	//����ʱ��
    p->in_balance=0;							//�뿨ֵ
    IA->dOutCardBala=-1;						//����ֵ
    IA->iTxCnt=1;							//���״���
    //�޸Ľ跽�ʹ����ʻ����,�ǻ�Ʒ�¼��
    ret=AccountProcess(IA);
    if(ret) {
        writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
        return ret;
    }
    p->out_balance=IA->dOutCardBala;		//����ֵ
    return 0;
}
static int do_change_subsidy(T_t_aif_account *account,int old_cardno) {
    T_t_tif_subsidy tSubsidy;
    int ret;
    int count;
    T_t_tif_meslist tMesList;
    char status[2] = "";

    status[0] = SUBSIDY_STAT_NORMAL;
    ret = DB_t_tif_subsidy_open_select_for_update_by_c3_and_cardno_and_status(
              old_cardno,status);
    if(ret) {
        if(DB_NOTFOUND == ret)
            return 0;
        writelog(LOG_ERR,"open subsidy cardno[%d],ret[%d]",old_cardno,ret);
        return E_DB_SUBSIDY_R;
    }
    count = 0;
    while(1) {
        memset(&tSubsidy,0,sizeof tSubsidy);
        ret = DB_t_tif_subsidy_fetch_select_by_c3(&tSubsidy);
        if(ret) {
            if(DB_NOTFOUND == ret)
                break;
            writelog(LOG_ERR,"read subsidy cardno[%d],ret[%d]",old_cardno,ret);
        }
        // �µĽ��׿���
        tSubsidy.cardno=account->cardno;
        ret = DB_t_tif_subsidy_update_lock_by_c3(&tSubsidy);
        if(ret) {
            writelog(LOG_ERR,"update subsidy cust_id[%d],subsidy_no[%d],ret[%d]",
                     tSubsidy.cust_no,tSubsidy.subsidy_no,ret);
            return E_DB_SUBSIDY_U;
        }
        count++;
    }
    if( count > 0 ) {
        //�㲥���ز�����Ϣ����

        memset(&tMesList,0,sizeof tMesList);
        tMesList.funid = 930077;
        tMesList.max_send_cnt = 10;
        tMesList.level = MESLIST_PRIORITY_REALTIME;
        tMesList.msgtype = MESLIST_TYPE_NORMAL;
        ret=AddMsgLst(&tMesList);
        if(ret) {
            writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
            return ret;
        }

    }
    return 0;
}
int F847104(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {

    int ret =0;
    int len = 0;
    int i=0;
    int hi_custid=0;
    char h_showcardid[11] = "";						//��ʾ����
    char h_password[7] = "";							//������
    double h_temp_Card_id = 0;						//����
    double dSerialNo=0;
    char seed_key[17] = "";							//������Կ
    char card_endtime[8 + 1] = "";						//������Ч��������
    char logicdate[11]="";								//ҵ������
    char sysdate[11]="";
    char systime[9]="";
    char sEndDate[9]="";
    char sMsg[256]="";
    char sMaxCardBalance[20]="";
    char lost_date[11]="";
    double dMaxCardBalance=0;
    int lost_cardno=0;
    T_t_card		tCard;
    T_t_card		tOldCard;
    T_t_customer 	tCustomer;
    T_t_spefee 	tSpeFee;
    //	T_t_cardlossinfo tCardLossInfo;
    T_t_tif_tradeserial  tradeserial;
    T_t_aif_account tAccount;
    InAcc  IA;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
           F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
           F_SDATE0,F_SNAME,F_SNAME2,
           F_SOPEN_EMP,F_SSTATUS0,
           F_DAMT2,F_LSERIAL1,F_VSMESS,0);

    memset(&tCard,0,sizeof(tCard));
    memset(&tOldCard,0,sizeof(tOldCard));
    memset(&tCustomer,0,sizeof(tCustomer));
    memset(&tSpeFee,0,sizeof(tSpeFee));
    //	memset(&tCardLossInfo,0,sizeof(tCardLossInfo));
    memset(&tAccount,0,sizeof(tAccount));
    memset(&tradeserial,0,sizeof(tradeserial));
    memset(&IA,0,sizeof(IA));

    getsysdate(sysdate);
    getsystime(systime);
    ret=GetLogicDate(logicdate);										//ҵ������
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    //���ͻ���Ϣ���ж��Ƿ���Է��п�
    hi_custid=rPack->lvol0;									//�ͻ���
    des2src(tCard.cardphyid, rPack->sbank_acc);				//������
    trim(h_showcardid);
    ret=IsExistFreezeCardByCustomId(hi_custid);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    ret=IsExistNoLostCardByCustomId(hi_custid);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    if(strlen(h_showcardid)) {
        ret=IsExistShowCardNo(h_showcardid);
        if(ret) {
            *pRetCode = ret;
            goto L_RETU;
        }
    }
    ret=IsExistCardByPhyCardNo(tCard.cardphyid);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    ret=GetLostCardIdByCustomId_TypeId(hi_custid,CT_NORMAL,&lost_cardno);
    if(ret) {
        writelog(LOG_ERR,"customer[%d]tCard type_id[%d]",hi_custid,CT_NORMAL);
        *pRetCode = ret;
        goto L_RETU;
    }

    /*
      ret=DB_t_cardlossinfo_read_by_cardno_and_state_id(lost_cardno, STATE_VALID, &tCardLossInfo);
      if(ret)
      {
      writelog(LOG_ERR,"lost_cardno[%d]",lost_cardno);
      if(DB_NOTFOUND==ret)
      *pRetCode =  E_CARDNO_NOT_EXIST;
      else
      *pRetCode =  E_DB_CARD_R;
      goto L_RETU;
      }
    */
    ret=get_latest_lost_date_by_cardno(lost_cardno,lost_date);
    if(ret) {
        writelog(LOG_ERR,"lost_cardno[%d]",lost_cardno);
        *pRetCode =ret;
        goto L_RETU;
    }
    //�ȼ��ͻ��Ĺ�ʧ����ʽ���Ƿ��˲�������
    ret=GetLostCardValiddate(lost_date,sEndDate);
    if(ret) {
        *pRetCode =ret;
        goto L_RETU;
    }

    if(strncmp(sEndDate,sysdate,8)>0) {
        writelog(LOG_ERR,"lost_normal_cardno[%d]lost_date[%s]end_date[%s]",lost_cardno,lost_date,sEndDate);
        *pRetCode =  E_NORMALCARD_NOT_REACH_ENDDATE;
        goto L_RETU;
    }
    /*
    //���¿���ʧ���ڱ��иÿ�״̬Ϊ��Ч
    ret=UpdateCardLossInfoState(lost_cardno,STATE_VALID,STATE_INVALID);
    if(ret)
    {
    *pRetCode = ret;
    goto L_RETU;
    }
    */
    //ע��ԭ��
    ret=DB_t_card_read_lock_by_cur_and_cardno(lost_cardno,&tOldCard);
    if(ret) {
        writelog(LOG_ERR,"lost_cardno[%d]",lost_cardno);
        if(DB_NOTFOUND==ret)
            *pRetCode = E_CARDNO_NOT_EXIST;
        else
            *pRetCode =  E_DB_CARD_R;
        goto L_RETU;
    }
    des2src(tOldCard.state_id,CARDSTAT_LOGOUT);		//ע��
    des2src(tOldCard.endtime,sysdate);				//ע������
    ret=DB_t_card_update_lock_by_cur(&tOldCard);
    if(ret) {
        writelog(LOG_ERR,"lost_cardno[%d]",lost_cardno);
        if(DB_NOTFOUND==ret)
            *pRetCode =   E_CARDNO_NOT_EXIST;
        else
            *pRetCode =  E_DB_CARD_R;
        goto L_RETU;
    }
    DB_t_card_free_lock_by_cur();

    ret = InsertToCutUpdList(tOldCard.cardno,CUTUPD_CH_OLDCARD,tOldCard.cardphyid);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }

    ret=DB_t_customer_read_lock_by_cur_and_custid(hi_custid, &tCustomer);
    if(ret) {
        writelog(LOG_ERR,"custid[%d]",hi_custid);
        if(DB_NOTFOUND==ret)
            *pRetCode= E_CUSTOMER_NOT_EXIST;
        else
            *pRetCode= E_DB_CUSTOMER_R;
        goto L_RETU;
    }
    //�õ��շ����
    if(tCustomer.feetype<1) {
        ret=DB_t_spefee_read_by_deptcode_and_custtype(tCustomer.deptcode, tCustomer.custtype,&tSpeFee);
        if(ret) {
            if(DB_NOTFOUND==ret) {
                tCustomer.feetype=tCustomer.custtype;
            } else {
                DB_t_customer_free_lock_cur();
                *pRetCode=E_DB_SPEFEE_R;
                goto L_RETU;
            }
        } else {
            tCustomer.feetype=tSpeFee.feetype;
        }
        //���¿ͻ�����շ�����ֶ�
        ret=DB_t_customer_update_lock_by_cur(&tCustomer);
        if(ret) {
            if(DB_NOTFOUND==ret)
                *pRetCode= E_CUSTOMER_NOT_EXIST;
            else
                *pRetCode= E_DB_CUSTOMER_U;
            goto L_RETU;
        }
    }
    DB_t_customer_free_lock_cur();

    tradeserial.trade_fee =D4U5(rPack->damt0,2);
    //	׼�����ݲ��뿨��Ϣ��
    memcpy(seed_key,STATIC_SEED_KEY,16);			//��������Կ
    if(strlen(tCustomer.can_time)==8) {
        ret=IsInvalidDateTime(tCustomer.can_time,"YYYYMMDD");
        if(ret) {
            *pRetCode=E_TB_CUSTOMER_ENDTIME;
            goto L_RETU;
        }
        if(strncmp(tCustomer.can_time,sysdate,8)<=0) {
            *pRetCode=E_TB_CUSTOMER_ENDTIME;
            goto L_RETU;
        }
        des2src(card_endtime,tCustomer.can_time);
    } else if(strlen(rPack->sdate0)==0) {
        *pRetCode=E_TB_CUSTOMER_NO_ENDTIME;
        goto L_RETU;
    } else {
        ret=IsInvalidDateTime(rPack->sdate0,"YYYYMMDD");
        if(ret) {
            *pRetCode = E_INPUT_DATE;
            goto L_RETU;
        }
        if(strncmp(rPack->sdate0,sysdate,8)<=0) {
            *pRetCode=E_INPUT_DATE;
            goto L_RETU;
        }
        des2src(card_endtime,rPack->sdate0);
    }

    tradeserial.trade_fee = rPack->damt0;								//���
    tradeserial.other_seri_no = 0;										//�ϴ�����ˮ��
    tradeserial.serial_state = SERISTAT_DEBT;								//��ˮ״̬
    des2src(tradeserial.operate_date,sysdate);							//��������
    des2src(tradeserial.operate_time,systime);							//����ʱ��
    des2src(tradeserial.collect_date,sysdate);								//�ɼ�����
    des2src(tradeserial.collect_time,systime);								//�ɼ�ʱ��
    des2src(tradeserial.enteract_date,logicdate);							//��������
    des2src(tradeserial.enteract_time,systime);							//����ʱ��
    tradeserial.maindeviceid = rPack->lvol6;								//�ϴ�����վ��ʶ
    tradeserial.deviceid = rPack->lvol7;									//�ɼ��豸��ʶ
    tradeserial.purseno = PURSE_NO_ONE;								//Ǯ����
    tradeserial.custid = tCustomer.custid;							//�ͻ���ʶ
    tradeserial.sys_id = 0;												//�ⲿϵͳ��ʶ
    des2src(tradeserial.opercode, rPack->scust_limit);					//����Ա��

    len=strlen(tCustomer.man_id) ;
    if (len >= 6) {
        strncpy(h_password,&(tCustomer.man_id[len-6]),6);
        if(h_password[5]>'9'||h_password[5]<'0')
            h_password[5]='0';
    } else {
        strcpy(h_password,DEFAULT_CUST_PWD);
    }
    ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//��ȡ��󿨺�
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    tCard.cardno = D2I(h_temp_Card_id);											//����
    des2src(tCard.showid,h_showcardid);										//��ʾ����
    des2src(tCard.is_main,TYPE_YES);  											//�Ƿ�Ϊ����
    des2src(tCard.cardattr,CARDSTAT_REG);										//��״̬
    tCard.type_id = CT_NORMAL;													//�����
    EncodePwd(seed_key,h_password,tCard.password,0);							//������
    tCard.custid = hi_custid;													//�ͻ���ʶ
    tCard.account_count = ACCOUNT_COUNT_ONE;									//����Ӧ�ʻ�����
    des2src(tCard.begintime,sysdate);											//ע��ʱ��
    des2src(tCard.endtime, card_endtime);										//����ʱ��

    tCard.phytype = PHYTYPE_NO_ONE;											//�豸�����ͺ�;Ĭ��Ϊ1
    //	���뿨��Ϣ
    ret = DB_t_card_add(&tCard);
    if (ret) {
        if(DB_REPEAT==ret)
            *pRetCode = E_DB_CARD_E;
        else
            *pRetCode = E_DB_CARD_I;
        goto L_RETU;
    }
    ret = InsertToCutUpdList(tCard.cardno,CUTUPD_CH_NEWCARD,tCard.cardphyid);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }

    //�޸��ʻ����ж�Ӧ�Ŀ���,����,״̬
    ret=DB_t_aif_account_read_lock_by_c0_and_cardno_and_purseno(lost_cardno,PURSE_NO_ONE,&tAccount);
    if (ret) {
        writelog(LOG_ERR,"normalcard_account_id[%s]",lost_cardno);
        if(DB_NOTFOUND==ret)
            *pRetCode =  E_ACTNO_NOT_EXIST;
        else
            *pRetCode =  E_DB_ACCOUNT_R;
    }
    if(tAccount.current_state!=1) {
        *pRetCode=E_ACTNO_LOGOUT;
        goto L_RETU;
    }
    tAccount.cardno=tCard.cardno;
    tAccount.card_balance=tAccount.cur_freebala;			//���¿����������һ��
    tAccount.consume_count=0;
    ret=DB_t_aif_account_update_lock_by_c0(&tAccount);
    if (ret) {
        writelog(LOG_ERR,"DB_t_aif_account_update_lock_by_cur4 ret[%d]account_id[%s]",
                 ret,tAccount.account_id);
        if(DB_NOTFOUND==ret)
            *pRetCode =   E_ACTNO_EXIST;
        else
            *pRetCode =  E_DB_ACCOUNT_U;
    }
    DB_t_aif_account_free_lock_c0();
    // ����δ��ȡ������Ϣ��
    ret = do_change_subsidy(&tAccount,lost_cardno);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    // ����δ��ȡ������¼�еĽ��׿���
    ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerialNo);  						//��������ˮ��
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    tradeserial.serial_no=D2I(dSerialNo);
    tradeserial.serial_type=TXCODE_CHANGE_CARD;
    tradeserial.cardno=tCard.cardno;				//�¿���
    des2src(tradeserial.showid,tCard.showid);			//��ʾ����

    strcpy(IA.sArrInActno[0],tAccount.account_id);		//�˺�
    IA.dArrInAmt[0]=tradeserial.trade_fee;			//���׽��
    IA.iUseCardFlag=USE_CARD_TYPE_ONLINE;		//��������
    IA.dInCardBala=tAccount.cur_freebala;			//�뿨ֵ
    IA.iTxCnt=1;
    IA.iCardNo=tCard.cardno;
    IA.iFeeType=tCustomer.feetype;
    IA.iArrInFeeSwitch[0]=rPack->lvol0;
    IA.iArrInFeeSwitch[1]=rPack->lvol1;
    IA.iArrInFeeSwitch[2]=rPack->lvol2;
    IA.iArrInFeeSwitch[3]=rPack->lvol3;
    IA.iArrInFeeSwitch[4]=rPack->lvol4;
    IA.iArrInFeeSwitch[5]=rPack->lvol5;
    IA.iArrInFeeSwitch[6]=rPack->lvol6;
    IA.iArrInFeeSwitch[7]=rPack->lvol7;
    IA.iArrInFeeSwitch[8]=rPack->lvol8;
    IA.iArrInFeeSwitch[9]=rPack->lvol9;
    IA.iArrInFeeSwitch[10]=rPack->lvol10;
    ret=process(&IA,&tradeserial);
    if(ret) {
        writelog(LOG_ERR,"process ret[%d]",ret);
        *pRetCode=ret;
        goto L_RETU;
    }
    sprintf(out_pack->vsmess,"��ˮ��:%d ����:%d ",IA.iSerialNo,IA.iCardNo);
    for(i=1; i<=IA.iOutTxTypeCnt; i++) {
        switch(IA.iArrOutTxType[i]) {
        case TXTYPE_TOLL_DEPOSIT:
        case TXTYPE_DEDUCT_DEPOSIT:
        case TXTYPE_RETURN_DEPOSIT:
            tradeserial.depositfee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_PRE_TOLL_BOARD:
        case TXTYPE_TOLL_BOARD:
        case TXTYPE_DEDUCT_BOARD:
        case TXTYPE_RETURN_BOARD:
            tradeserial.managefee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_TOLL_CHARGE:
            tradeserial.in_fee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_TOLL_CARDCOST:
            tradeserial.cost_fee=IA.dArrOutAmt[i];
            break;
        default:
            break;
        }
        if(amtcmp(IA.dArrOutAmt[i],0)!=0) {
            sprintf(sMsg,"%s:%.2lfԪ ",IA.sArrOutTxName[i],IA.dArrOutAmt[i]);
            strcat(out_pack->vsmess,sMsg);
        }
    }
    sprintf(sMsg,"����ǰ���:%.2lfԪ",tradeserial.out_balance);
    strcat(out_pack->vsmess,sMsg);
    writelog(LOG_DEBUG,out_pack->vsmess);
    ret = DB_t_tif_tradeserial_add(&tradeserial);
    if (ret) {
        writelog(LOG_ERR,"ret[%d]",ret);
        if(DB_REPEAT==ret)
            *pRetCode = E_DB_TRADESERIAL_E;
        else
            *pRetCode = E_DB_TRADESERIAL_I;
        goto L_RETU;
    }
    if(amtcmp(tradeserial.out_balance,0)<0) {
        *pRetCode=E_ENTER_ACCOUNT;
        goto L_RETU;
    }
    //������Ƿ񳬹������
    ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    dMaxCardBalance=atof(sMaxCardBalance);
    if(amtcmp(tradeserial.out_balance,dMaxCardBalance)>0) {
        writelog(LOG_ERR,"tradeserial.out_balance[%lf]",tradeserial.out_balance);
        *pRetCode=E_AMT_EXCEED_MAX;
        goto L_RETU;
    }

    //���ؿ���\����\��ʾ����\�ͻ�����\ͼ��֤��\��Ч��������
    out_pack->lvol0 = (int)h_temp_Card_id;						//���׿���
    out_pack->lvol1 = tCustomer.custtype;						//�ͻ����
    out_pack->lvol5 = tCustomer.feetype;						//�շ����
    des2src(out_pack->scust_no,h_showcardid);					//��ʾ����
    des2src(out_pack->scust_no2,tCustomer.deptcode);			//���ź�
    des2src(out_pack->scust_auth,tCustomer.stuempno);			//ѧ��
    des2src(out_pack->scust_auth2,tCustomer.man_id);			//���֤��
    des2src(out_pack->sname,tCustomer.custname);				//�ͻ�����
    des2src(out_pack->sname2,tCustomer.lib_cardid);				//ͼ��֤��
    des2src(out_pack->sstatus0,tCustomer.sex);					//�Ա�
    des2src(out_pack->sopen_emp,h_password);					//������
    des2src(out_pack->sdate0,card_endtime);					//��Ч��������

    out_pack->damt2=tradeserial.out_balance;					//����ֵ
    out_pack->lserial1=tradeserial.serial_no;						//��ˮ��
    // add by ���� 2005-8-8
    // ������������д���¼
    /*
    ret = InsertToBlkList((int)h_temp_Card_id,CHCARD_BLACKLIST);
    if(ret)
    {
    	*pRetCode = ret;
    	goto L_RETU;
    }
    */
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
    return -1;
}

