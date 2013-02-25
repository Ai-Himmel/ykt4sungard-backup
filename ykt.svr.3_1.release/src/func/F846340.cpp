/* --------------------------------------------
 * ��������: 2011-10-18
 * ��������:
 * �汾��Ϣ: 1.0.0.0
 * ������: �����ʻ��������ۿ�
 * --------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "transcode.h"
#include "acctrans.h"

int F846340(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;

    CAccTrans *pAccTrans=CAccTrans::getInstance();
    TRANS& trans=pAccTrans->trans;
    trans.transcode=TC_EACC2SHOP;
    trans.transtype = TRANSTYPE_EACCPAYMENT; // ֧������
    //trans.termid=TERMID_WEB;
    trans.termid=rPack->lcert_code; // ʹ��֧�����ص�ע��ID

    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;

    trans.inputamt=D4U5(rPack->damt0,2);
    trans.unusedamt = trans.inputamt;
    trans.transamt=trans.inputamt;

    if(amtcmp(trans.inputamt,0)==0)
        return E_INPUT_AMT_NULL;

    if(amtcmp(trans.inputamt,0)<0)
        return E_INPUT_AMT;

    //��ѯ����Ǯ���ʻ�
    T_t_netacc tNetAccount;
    memset(&tNetAccount,0,sizeof(tNetAccount));
    ret=DB_t_netacc_read_by_accno(rPack->scust_no,&tNetAccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_EACCNO,rPack->scust_no);
        else
            return E_DB_ACCOUNT_R;
    }

    //������Ǯ������
    if(rPack->lvol1 == 0) { // �������˻����� ����˻����
        if(strcmp(rPack->snote2,tNetAccount.paypwd)!=0)
            return E_EACCPWD;
    }

    if(tNetAccount.status[0]!=STATUS_NORMAL) // �˻�״̬
        return ERRINFO(E_EACCNO_LOGOUT,tNetAccount.accno);

    if(tNetAccount.stoppayflag[0]=='1') // ֹ����־
        return ERRINFO(E_EACC_STOPPAY,tNetAccount.accno);

    if(rPack->lvol1 == 0) { // �������˻����� ����˻����
        if(amtcmp(trans.inputamt,tNetAccount.balance)>0)
            return ERRINFO(E_EACC_BALANCE_SHORTAGE,trans.inputamt-tNetAccount.balance);
    }
    /*
    double CardMaxBal=0;
    ret=GetPurseMaxBal(PURSE_NO_ONE,CardMaxBal);
    if(ret)
    	return ret;
    if(amtcmp(trans.inputamt+trans.cardbefbal,CardMaxBal)>0)
    	return ERRINFO(E_AMT_EXCEED_MAX,CardMaxBal);
    */
    des2src(trans.draccno,tNetAccount.accno);

    trans.custid=tNetAccount.custid;
    des2src(trans.custname,tNetAccount.accname);

    // ֧��ת��
    T_t_shop shop;

    memset(&shop,0,sizeof(shop));
    ret=DB_t_shop_read_by_shopid(rPack->lvol0,&shop);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_NOTEXIST_SHOPID;
        else
            return E_DB_SHOP_R;
    }
    if(shop.status[0]!=STATUS_NORMAL)
        return E_SHOP_LOGOUT;

    if(shop.shoptype!=SHOPTYPE_ESHOP)
        return ERRIF_SHOP_TYPE;

    des2src(trans.craccno,shop.accno);

    // �������ײο���
    T_t_refno tRefno;

    memset(&tRefno,0,sizeof(tRefno));
    get_random(tRefno.mac);
    ret= GetNewRefno(tRefno.refno);
    if(ret)
        return ret;

    des2src(tRefno.lastsaved,trans.sysdatetime);
    des2src(tRefno.accdate,trans.accdate);
    tRefno.termid = trans.termid;
    tRefno.termseqno = trans.termseqno;
    tRefno.status = RS_SUCC;

    ret=DB_t_refno_add(&tRefno);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_REFNO_E;
        else
            return E_DB_REFNO_I;
    }

    des2src(trans.refno, tRefno.refno);

    ret=pAccTrans->doTrans();
    if(ret)
        return ret;

    // ��ӵ����˻�֧����Ϣ
    T_t_epay_record t_epay_record;
    memset(&t_epay_record,0,sizeof(t_epay_record));

    des2src(t_epay_record.refno, tRefno.refno);
    t_epay_record.shopid = shop.shopid;
    des2src(t_epay_record.oid, rPack->sbankname);
    des2src(t_epay_record.accno,tNetAccount.accno);
    des2src(t_epay_record.accname,tNetAccount.accname);
    t_epay_record.amount = trans.inputamt;
    des2src(t_epay_record.currency,rPack->sstock_code);

    des2src(t_epay_record.epay_date,trans.accdate);
    des2src(t_epay_record.epay_time,trans.acctime);
    t_epay_record.status = 1; // ���׳ɹ�
    t_epay_record.transcode = trans.transcode;
    des2src(t_epay_record.remark,rPack->snote);

    ret=DB_t_epay_record_add(&t_epay_record);
    if(ret)
        return ret;

    // ��ӽ�����ˮ
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));

    des2src(transdtl.refno,tRefno.refno); // ���ײο���
    des2src(transdtl.transdate,trans.accdate);
    des2src(transdtl.transtime,trans.acctime);
    strcpy(transdtl.accdate,trans.accdate);
    strcpy(transdtl.acctime,trans.acctime);
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
    transdtl.transcode=trans.transcode;
    transdtl.transflag=TF_PAY;
    transdtl.managefee=trans.totalfeeamt;
    des2src(transdtl.custname,tNetAccount.accname);
    transdtl.amount = trans.inputamt;
    des2src(transdtl.opercode,trans.opercode);
    transdtl.cardbefbal = trans.draccbefbal;
    transdtl.cardaftbal = trans.draccaftbal;
    des2src(transdtl.coldate,trans.accdate);
    des2src(transdtl.coltime,trans.acctime);
    transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.revflag[0]='0';
    transdtl.custid=tNetAccount.custid;
    GetStuempnoByCustid(transdtl.custid,transdtl.stuempno);
    ret=DB_t_transdtl_add(&transdtl);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    SetCol(handle,0);
    SetCol(handle,F_LVOL0,F_SCUST_NO, F_SDATE0,F_STIME0,
           F_DAMT0,F_SPHONE3,F_SADDR,F_VSMESS,0);
    outPack->lvol0=shop.shopid;
    des2src(outPack->scust_no,tNetAccount.accno);
    des2src(outPack->sdate0,trans.accdate);
    des2src(outPack->stime0,trans.acctime);

    des2src(outPack->sphone3,tRefno.refno); // һ��ͨ��ˮ��,����ʹ��
    des2src(outPack->saddr,tRefno.mac); // MAC ����ʹ��

    outPack->damt0=trans.draccaftbal; // ���
    char temp[128]="";
    sprintf(temp,"%s ֧���ɹ�,����Ǯ�����:%.2f",
            tNetAccount.accname, trans.draccaftbal);

    pAccTrans->remark+=temp;
    strcpy(outPack->vsmess,pAccTrans->remark.c_str());
    des2src(trans.remark,outPack->vsmess);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}
