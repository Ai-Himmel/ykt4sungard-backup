/* --------------------------------------------
 * ��������: F847125.sqc
 * ��������: 2004-12-16
 * ��������: �Ž�
 * �汾��Ϣ: 1.0.0.0
 * ������:  ������ʱ��(�Ǽ��� )
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

static int process(InAcc *IA,T_t_tif_tradeserial *p) {
    int ret = 0;

    //���ݿ��ź�Ǯ���ŵõ��������˺�(�跽)

    IA->iMainDevId=p->maindeviceid;			//����վ��ʶ
    IA->iDevId=p->deviceid;					//�豸ID
    IA->iSerialNo=p->serial_no;				//��ˮ��
    IA->iTradeNo=p->serial_type;				//������
    strcpy(IA->sTxDate,p->operate_date);		//��������
    strcpy(IA->sTxTime,p->operate_time);		//����ʱ��
    strcpy(IA->sTxCollectDate,p->collect_date);	//�ɼ�����
    strcpy(IA->sTxCollectTime,p->collect_time);	//�ɼ�ʱ��
    strcpy(IA->sTxAccDate,p->enteract_date);	//��������
    strcpy(IA->sTxAccTime,p->enteract_time);	//����ʱ��

//	strcpy(IA->sActno[0],p->out_account_id);		//�˺�

//	IA->dAmt[0]=p->trade_fee;				//��ֵ���(����������)
//	IA->dAmt[1]=p->managefee;					//��ֵ���(����)
//	IA->dAmt[2]=p->depositfee;				//Ԥ�����
//	IA->dAmt[3]=p->in_fee;					//������/�����
//	IA->dAmt[4]=p->cost_fee;					//���ɱ���

    p->in_balance=0;							//�뿨ֵ
    IA->iUseCardFlag=USE_CARD_TYPE_ONLINE;	//��������
    IA->iTxCnt=p->trade_count;				//���״���
    IA->dInCardBala=p->in_balance;			//�뿨ֵ
    IA->dOutCardBala=-1;						//����ֵ
    //�޸Ľ跽�ʹ����ʻ����ǻ�Ʒ�¼��
    ret=AccountProcess(IA);
    if(ret) {
        writelog(LOG_ERR,"AccountProcess ret[%d]",ret);
        return ret;
    }
    p->out_balance=IA->dOutCardBala;		//����ֵ
    return 0;
}

int F847125(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int	hi_custtype = 0;										//�ͻ�����
    int i=0;
    int ret = 0;
    int iSeqNo=0;
    char h_showcardid[11] = "";								//��ʾ����
    char h_password[7] = "";									//������
    double h_temp_Card_id = 0;								//����
    char seed_key[17] = "";									//������Կ
    char card_endtime[8 + 1] = "";							//������Ч��������
    char logicdate[11]="";
    char sysdate[11]="";
    char systime[9]="";
    char sMsg[256]="";
    char temp[256] ="";
    double dSerial_no = 0;
    char sMaxCardBalance[20]="";
    double dMaxCardBalance=0;
    T_t_card tCard;
    T_t_aif_account  tAccount;
    T_t_tif_tradeserial  tradeserial;
    T_t_customer  tCustomer;
    T_t_feetype tFeetype;
    T_t_custtypefee tCuttype;
    InAcc	IA;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_LVOL1,F_LVOL5,
           F_SCUST_NO,	F_SCUST_NO2,F_SCUST_AUTH,F_SCUST_AUTH2,
           F_SDATE0,F_SNAME,F_SNAME2,
           F_SOPEN_EMP,F_SSTATUS0,
           F_DAMT2,F_DAMT3,F_DAMT4,F_DAMT5,F_LSERIAL1,F_VSMESS,0);

    memset(&IA,0,sizeof(IA));
    memset(&tCard, 0, sizeof(tCard));
    memset(&tAccount,0,sizeof(tAccount));
    memset(&tradeserial,0,sizeof(tradeserial));
    memset(&tCustomer,0,sizeof(tCustomer));

#ifdef DEBUG
    writelog(LOG_DEBUG,"rPack->damt0[%lf]",rPack->damt0);
    writelog(LOG_DEBUG,"rPack->scust_auth2[%s]",rPack->scust_auth2);
#endif

    tradeserial.trade_fee=rPack->damt0;					//������
    hi_custtype = rPack->lvol3;									//�ͻ����
    trim(rPack->scust_no);
    des2src(h_showcardid,rPack->scust_no);					//��ʾ����
    des2src(tCard.cardphyid, rPack->sbank_acc);				//������
    des2src(card_endtime,rPack->sdate0);
    getsysdate(sysdate);
    getsystime(systime);
    ret=GetLogicDate(logicdate);								//ҵ������
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    ret=IsInvalidDateTime(card_endtime,"YYYYMMDD");
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    if(strlen(h_showcardid)>10) {
        *pRetCode=E_INPUT_SHOWID;
        goto L_RETU;
    }
    ret=IsExistShowCardNo(h_showcardid);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    ret=IsExistCardByPhyCardNo(tCard.cardphyid);			//������
    if(ret) {
        writelog(LOG_ERR,"cardphyid[%s]",tCard.cardphyid);
        *pRetCode = ret;
        goto L_RETU;
    }
    //������Ƿ񳬹������
    ret=GetParameter(GLOBE_MAXCARDBALANCE,sMaxCardBalance);
    if(ret) {
        *pRetCode=ret;
        goto L_RETU;
    }
    dMaxCardBalance=atof(sMaxCardBalance);

    if(amtcmp(tradeserial.trade_fee,dMaxCardBalance)>0) {
        writelog(LOG_ERR,"tradeserial.trade_fee[%lf]",tradeserial.trade_fee);
        *pRetCode=E_AMT_EXCEED_MAX;
        goto L_RETU;
    }
//�����ӿͻ�
    ret = GetParameter(GLOBE_FLAG_TEMPCARD_CUTTYPE,temp);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    hi_custtype = atoi(temp);
    memset(&tCuttype,0,sizeof tCuttype);
    if(hi_custtype <= 0) {
        *pRetCode = E_GLOBAL_PARAM_ERROR;
        strcpy(szMsg,"����ȷ������ʱ��Ա�ͻ����");
        goto L_RETU;
    }
    ret = DB_t_custtypefee_read_by_custtype(hi_custtype,&tCuttype);
    if(ret) {
        if(DB_NOTFOUND == ret) {
            *pRetCode = E_DB_CUTTYPEFEE_N;
            strcpy(szMsg,"����ȷ������ʱ��Ա�շ����");
        } else
            *pRetCode = E_DB_CUTTYPEFEE_R;
        goto L_RETU;
    }

    ret = GetParameter(GLOBE_FLAG_TEMPCARD_FEETYPE,temp);
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    tCustomer.feetype = atoi(temp);
    if(tCustomer.feetype <= 1) {
        *pRetCode = E_GLOBAL_PARAM_ERROR;
        strcpy(szMsg,"����ȷ������ʱ��Ա�շ����");
        goto L_RETU;
    }
    memset(&tFeetype,0,sizeof tFeetype);
    ret = DB_t_feetype_read_by_feetype(tCustomer.feetype,&tFeetype);
    if(ret) {
        if(DB_NOTFOUND == ret) {
            *pRetCode = E_DB_FEETYPE_N;
            strcpy(szMsg,"����ȷ������ʱ��Ա�շ����");
        } else
            *pRetCode = E_DB_FEETYPE_R;
        goto L_RETU;
    }
    ret=getNewUniqNo(KEYTYPE_CUSTOMER, &iSeqNo);
    if(ret) {
        *pRetCode=ret;
        writelog(LOG_ERR,"getNewUniqNo err[%d]",ret);
        goto L_RETU;
    }
    tCustomer.custid=iSeqNo;
    tCustomer.custtype=hi_custtype;					//�ͻ�����
    //tCustomer.feetype=tCustomer.custtype;
    tCustomer.cut_state=CUSTSTAT_REGIST;
    des2src(tCustomer.is_havecard,TYPE_YES);
//	tCustomer.area=rPack->lvol10;						//����
    /*
    	ret=GetTempPersonId(tCustomer.stuempno);	//Ա����
    	if(ret)
    	{
    		*pRetCode=ret;
    		goto L_RETU;
    	}
    */
//	des2src(tCustomer.stuempno,h_showcardid);
    snprintf(tCustomer.custname,20,"��%.10s",h_showcardid);			//�ͻ� ����
    des2src(tCustomer.opendate,sysdate);							//ע������
    ret=DB_t_customer_add(&tCustomer);
    if(ret) {
        *pRetCode = E_DB_CUSTOMER_I;
        writelog(LOG_ERR,"DB_t_customer_add ret[%d]",ret);
        goto L_RETU;
    }
    //	׼�����ݲ��뿨��Ϣ��
    memcpy(seed_key,STATIC_SEED_KEY,sizeof(seed_key));						//��������Կ

    //	Ĭ������, ��ʼȡ���֤�ĺ�6λ, û�����֤����Ĭ������
    strcpy(h_password,DEFAULT_CUST_PWD);
    ret = getNewUniqNo(KEYTYPE_CARD_ID,&h_temp_Card_id);						//��ȡ��󿨺�
    if(ret) {
        *pRetCode = ret;
        writelog(LOG_ERR,"ret[%d]",ret);
        goto L_RETU;
    }
    tCard.cardno = D2I(h_temp_Card_id);											//����
    des2src(tCard.showid,h_showcardid);											//��ʾ����
    des2src(tCard.is_main,TYPE_YES);  											//�Ƿ�Ϊ����
    des2src(tCard.cardattr,CARDSTAT_REG);										//��״̬
    tCard.type_id = CT_TEMP_NONAME;											//�����
    EncodePwd(seed_key,h_password,tCard.password,0);							//������
    tCard.custid = tCustomer.custid;											//�ͻ���ʶ
    tCard.account_count = ACCOUNT_COUNT_ONE;									//����Ӧ�ʻ�����
    des2src(tCard.begintime,logicdate);											//ע��ʱ��
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
    //	׼�����ݲ����ʻ���Ϣ��
    ret = getNewActno(tAccount.account_id);  	    //�������ʺ�
    if (ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    des2src(tAccount.open_date,logicdate);		   								//����ʱ��
    des2src(tAccount.open_time,systime);
    tAccount.current_state = ACCOUNTSTAT_REGIST;      							//��ǰ״̬
    tAccount.act_type = ACCTYPE_PERMAIN;				        					//�ʺ����
    tAccount.custid = tCustomer.custid;				        					//�ͻ���
    des2src(tAccount.custname,tCustomer.custname);								//�ͻ�����
    tAccount.custtype = hi_custtype;												//�ͻ����
    des2src(tAccount.stuempno,tCustomer.stuempno); 							//�ͻ�ѧ�Ż�Ա����
    tAccount.cardno =tCard.cardno; 											//��������
    tAccount.purseno = PURSE_NO_ONE;										//������Ǯ����
    tAccount.card_type = tCard.type_id;											//�����
    des2src(tAccount.subno,SUBJECT_INDIVIDUALSAVING);						//������Ŀ
    des2src(tAccount.isautotra,TYPE_NO); 										//�Ƿ��Զ�ת��
    //	�����ʻ���Ϣ��
    ret = DB_t_aif_account_add(&tAccount);
    if (ret) {
        if(DB_REPEAT==ret)
            *pRetCode = E_DB_ACCOUNT_E;
        else
            *pRetCode = E_DB_ACCOUNT_I;
        goto L_RETU;
    }
    //׼�����ݲ��뽻����ˮ��
    ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  						//��������ˮ��
    if(ret) {
        *pRetCode = ret;
        goto L_RETU;
    }
    tradeserial.serial_no = D2I(dSerial_no);											//��ˮ��
    tradeserial.other_seri_no = 0;														//�ϴ�����ˮ��
    tradeserial.serial_type = TXCODE_CARD_OPEN_FOR_TEMP;								//���״���
    tradeserial.serial_state = SERISTAT_DEBT;												//��ˮ״̬
    des2src(tradeserial.operate_date,sysdate);											//��������
    des2src(tradeserial.operate_time,systime);											//����ʱ��
    des2src(tradeserial.collect_date,sysdate);												//�ɼ�����
    des2src(tradeserial.collect_time,systime);												//�ɼ�ʱ��
    des2src(tradeserial.enteract_date,logicdate);											//��������
    des2src(tradeserial.enteract_time,systime);											//����ʱ��
    tradeserial.maindeviceid = rPack->lvol6;												//�ϴ�����վ��ʶ
    tradeserial.deviceid = rPack->lvol7;													//�ɼ��豸��ʶ
    tradeserial.cardno = tCard.cardno;													//����
    des2src(tradeserial.showid,tCard.showid);												//��ʾ����
    tradeserial.purseno = PURSE_NO_ONE;												//Ǯ����
    tradeserial.custid = tCustomer.custid;											//�ͻ���ʶ
    des2src(tradeserial.opercode,rPack->scust_limit);									//����Ա����
    tradeserial.sys_id = 0;																//�ⲿϵͳ��ʶ
    tradeserial.trade_count=1;														//��ǰ�����״���

    des2src(IA.sArrInActno[0],tAccount.account_id);						//�ʻ�
    IA.iCardNo=tCard.cardno;
    IA.iFeeType=tCustomer.feetype;
    IA.dArrInAmt[0]=tradeserial.trade_fee;

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

    //	����������ģ��
    ret=process(&IA,&tradeserial);
    if(ret) {
        *pRetCode=ret;
        writelog(LOG_ERR,"process ret[%d]",ret);
        goto L_RETU;
    }
    sprintf(out_pack->vsmess,"��ˮ��:%d ����:%d ",IA.iSerialNo,IA.iCardNo);
    for(i=1; i<=IA.iOutTxTypeCnt; i++) {
        switch(IA.iArrOutTxType[i]) {
        case TXTYPE_TOLL_DEPOSIT:
        case TXTYPE_TOLL_DEPOSIT_BILL:
        case TXTYPE_TOLL_DEPOSIT_FUNDBOOK:
        case TXTYPE_DEDUCT_DEPOSIT:
        case TXTYPE_RETURN_DEPOSIT:
            tradeserial.depositfee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_PRE_TOLL_BOARD:
        case TXTYPE_PRE_TOLL_BOARD_BILL:
        case TXTYPE_PRE_TOLL_BOARD_FUNDBOOK:
        case TXTYPE_TOLL_BOARD:
        case TXTYPE_DEDUCT_BOARD:
        case TXTYPE_RETURN_BOARD:
        case TXTYPE_RETURN_BOARD_BILL:
        case TXTYPE_RETURN_BOARD_FUNDBOOK:
            tradeserial.managefee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_TOLL_CHARGE:
        case TXTYPE_TOLL_CHARGE_BILL:
        case TXTYPE_TOLL_CHARGE_FUNDBOOK:
            tradeserial.in_fee=IA.dArrOutAmt[i];
            break;
        case TXTYPE_TOLL_CARDCOST:
        case TXTYPE_TOLL_CARDCOST_BILL:
        case TXTYPE_TOLL_CARDCOST_FUNDBOOK:
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
    //	���뽻����ˮ��
    ret = DB_t_tif_tradeserial_add(&tradeserial);
    if (ret) {
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
    //	���ؿ���\����\��ʾ����\�ͻ�����\ͼ��֤��\��Ч��������
    out_pack->lvol0 = (int)h_temp_Card_id;						//���׿���
    out_pack->lvol1 = tCustomer.custtype;						//�ͻ����
    out_pack->lvol5 = tCustomer.feetype;						//�շ����
    des2src(out_pack->scust_no,h_showcardid);					//��ʾ����
    des2src(out_pack->scust_no2,tCustomer.deptcode);			//���ź�
//	des2src(out_pack->scust_auth,tCustomer.stuempno);			//ѧ��
    des2src(out_pack->scust_auth2,tCustomer.man_id);			//���֤��
    des2src(out_pack->sname,tCustomer.custname);				//�ͻ�����
    des2src(out_pack->sname2,tCustomer.lib_cardid);				//ͼ��֤��
    des2src(out_pack->sstatus0,tCustomer.sex);					//�Ա�
    des2src(out_pack->sopen_emp,h_password);					//������
    des2src(out_pack->sdate0,card_endtime);					//��Ч��������

    out_pack->damt2=tradeserial.out_balance;					//����ֵ
    out_pack->damt3=tradeserial.managefee;						//����
    out_pack->damt4=tradeserial.cost_fee;						//�� �ɱ� ��
    out_pack->damt5=tradeserial.in_fee;							//������
    out_pack->lserial1=tradeserial.serial_no;						//��ˮ��

    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
    return -1;
}
