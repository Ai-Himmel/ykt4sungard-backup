/* --------------------------------------------
 * 创建日期: 2008-06-04
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通回收卡
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
#include "acctrans.h"
#include "transfunc.h"

static int doCard(TRANS& trans,T_t_card& tCard) {

    int ret=0;

    ret=DB_t_card_read_lock_by_cur_and_cardno(trans.cardno,&tCard);
    if(ret) {
        writelog(LOG_ERR,"cardno[%d]",trans.cardno);
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDNO,trans.cardno);
        else
            return E_DB_CARD_R;
    }
    if(tCard.status[0]!=STATUS_NORMAL) {
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_CARD_LOGOUT,trans.cardno);
    }
    if('1'==tCard.frozeflag[0]) {
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_CARD_FREEZE,trans.cardno);
    }
    if('1'==tCard.lossflag[0]) {
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_CARD_LOST,trans.cardno);
    }
    if('1'==tCard.badflag[0]) {
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_CARD_BADRECORD,trans.cardno);
    }
    //比较卡物理ID是否相同
    if(strcmp(tCard.cardphyid,trans.cardphyid)!=0) {
        writelog(LOG_ERR,"db cardphyid[%s],input cardphyid[%s]",tCard.cardphyid,trans.cardphyid);
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_CARD_PHYNO_DIFFER,trans.cardphyid,tCard.cardphyid);
    }
    //回收卡
    T_t_cardtype tCardType;

    memset(&tCardType,0,sizeof(tCardType));

    ret=DB_t_cardtype_read_by_cardtype(tCard.cardtype,&tCardType);
    if(tCardType.recycleable[0]!='1') {
        DB_t_card_free_lock_by_cur();
        return	ERRINFO(E_CARDTYPE_CANNOT_REUSE,tCardType.cardtype);
    }
    if(tCardType.fixdaycnt<1) {
        DB_t_card_free_lock_by_cur();
        return ERRINFO(E_NOSET_CARDTYPE_VALIDDAYS,tCardType.cardtype);
    }
    ret=calcEndDate(trans.transdate,tCardType.fixdaycnt,tCard.expiredate);
    if(ret) {
        DB_t_card_free_lock_by_cur();
        return ret;
    }
    char cardpwd[33]="";
    char key[17]="";
    get_init_passwd_by_man_id("",cardpwd);
    strcpy(key,STATIC_SEED_KEY);
    EncodePwd(key,cardpwd,tCard.cardpwd, 0);
//	memset(tCard.cardstatus,'0',sizeof(tCard.cardstatus));
    des2src(tCard.lastsaved,trans.sysdatetime);

    ret=DB_t_card_update_lock_by_cur(&tCard);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_CARD_N;
        else
            return E_DB_CARD_U;
    }
    //用来输出卡密码
    strcpy(tCard.cardpwd,cardpwd);
    /*
    //添加卡片回收明细记录
    T_t_carddtl tCarddtl;

    memset(&tCarddtl,0,sizeof(tCarddtl));
    /////////////////////////////////rPack2TableStuct////////////////////////
    des2src(tCarddtl.accdate,pAccTrans->sysPara.sSettleDate);
    tCarddtl.termid=trans.termid;
    tCarddtl.termseqno=trans.termseqno;
    tCarddtl.cardtype=tCard.cardtype;
    des2src(tCarddtl.showcardno,tCard.showcardno);
    des2src(tCarddtl.cardphyid,tCard.cardphyid);
    tCarddtl.cardusetype=CARDUSETYPE_RETURNCARD;
    des2src(tCarddtl.opercode,trans.opercode);
    ret=DB_t_carddtl_add(&tCarddtl);
    if(ret)
    {
    	if(DB_REPEAT==ret)
    		return E_DB_CARDDTL_E;
    	else
    		return E_DB_CARDDTL_I;
    }
    */
    return 0;
}
static int doAccount(TRANS& trans,char *cardaccno) {
    int ret=0;
    T_t_account tCardAccount;

    memset(&tCardAccount,0,sizeof(tCardAccount));

    ret=DB_t_account_read_lock_by_c0_and_accno(cardaccno,&tCardAccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDACCNO,cardaccno);
        else
            return E_DB_ACCOUNT_R;
    }
    if(tCardAccount.status[0]!=STATUS_NORMAL) {
        DB_t_account_free_lock_by_c0();
        return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
    }
    if(amtcmp(tCardAccount.balance,0)!=0) {
        DB_t_account_free_lock_by_c0();
        return ERRINFO(E_CARDACC_BALANCE_NOZERO,tCardAccount.balance);
    }
    tCardAccount.availbal=0;
    tCardAccount.frozebal=0;
    ret=DB_t_account_update_lock_by_c0(&tCardAccount);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDACCNO,cardaccno);
        else
            return E_DB_ACCOUNT_U;
    }
    return 0;
}

int F846310(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
//	ret=pAccTrans->checkCfgUpdate();
//	if(ret)
//		return ret;
    des2src(pAccTrans->trans.opercode,rPack->semp);
    pAccTrans->trans.transcode=TC_CARDRETURN;
    ret=pAccTrans->InitTrans();
    if(ret)
        return ret;
    TRANS& trans=pAccTrans->trans;

    char anonymflag[2]="";

    int returnForgiftFlag=0;

    ST_CPACK aPack;
    ST_PACK *outPack = &(aPack.pack);
    ResetNormalCPack(&aPack,0,1);

    SetCol(handle,0);

    //检查客户
    trans.cardflag=1;
    trans.usecardflag=1;
    trans.cardno=rPack->lvol0;
    pAccTrans->SetCardCntAndCardBal(rPack->lvol5,rPack->lvol6,rPack->lvol7);
    trans.transflag=TF_PAY;
    trans.aftpaycnt++;
    des2src(trans.cardphyid,rPack->sstation0);

    T_t_card tCard;

    memset(&tCard,0,sizeof(tCard));
    ret=doCard(trans,tCard);
    if(ret) {
        return ret;
    }
    ret=UpdateCardBitmap(trans.cardno,trans.aftpaycnt,CARDBITMAPTYPE_SYS_ONLINE);
    if(ret)
        return ret;
    T_t_account tCardAccount;
    memset(&tCardAccount,0,sizeof(tCardAccount));
    ret=DB_t_account_read_by_accno(tCard.accno,&tCardAccount);
    if(ret) {
        writelog(LOG_ERR,"cardno[%d]",tCard.cardno);
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CARDACCNO,tCard.accno);
        else
            return E_DB_ACCOUNT_R;
    }
    if(tCardAccount.status[0]!=STATUS_NORMAL) {
        return ERRINFO(E_CARDACC_LOGOUT,tCardAccount.accno);
    }
    if(amtcmp(tCardAccount.balance,0)<0) {
        ERRTIP("账户余额小于0不能直接回收");
        return E_COMMON_ERR;
    } else if(amtcmp(tCardAccount.balance,0)==0) {
        trans.cardaftbal=0;
    } else {
        strcpy(trans.cardaccno,tCardAccount.accno);
        trans.feetype=tCard.feetype;
        trans.inputamt=tCardAccount.balance;
        trans.unusedamt = trans.inputamt;
        ret=pAccTrans->doTrans();
        if(ret)
            return ret;
        ret=pAccTrans->doTransEnd();
        if(ret)
            return ret;
        //修改帐户
        ret=doAccount(trans,tCardAccount.accno);
        if(ret)
            return ret;
    }
    T_t_customer tCustomer;

    memset(&tCustomer,0,sizeof(tCustomer));

    if(tCard.custid>0) {
        ret=DB_t_customer_read_by_custid(tCard.custid,&tCustomer);
        if(ret) {
            if(DB_NOTFOUND==ret)
                return E_NOTEXIST_CUSTOMER;
            else
                return E_DB_CUSTOMER_R;
        }
        strcpy(trans.stuempno,tCustomer.stuempno);
    }
    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));

    strcpy(transdtl.transdate,trans.transdate);
    strcpy(transdtl.transtime,trans.transtime);
    strcpy(transdtl.accdate,trans.accdate);
    strcpy(transdtl.acctime,trans.acctime);
    transdtl.termid=trans.termid;
    transdtl.termseqno=trans.termseqno;
//	des2src(transdtl.collectdate,rPack->sdate1);
//	des2src(transdtl.collecttime,rPack->stime1);
    transdtl.transcode=trans.transcode;
//	transdtl.paytype=rPack->lvol9;
//	des2src(transdtl.voucherno,rPack->scust_auth2);
    transdtl.cardno=trans.cardno;
    transdtl.purseno=PURSE_NO_ONE;
    transdtl.transflag=TF_PAY;
    transdtl.cardcnt=trans.paycnt;
    transdtl.cardbefbal=trans.cardbefbal;
    transdtl.cardaftbal=trans.cardaftbal;
    transdtl.amount=trans.totaltransamt;
    transdtl.managefee=trans.totalfeeamt;
////	transdtl.frontno=0;
    //des2src(transdtl.devphyid,rPack->sname);
    //transdtl.devseqno=rPack->lserial0;
    //des2src(transdtl.bankcode,rPack->sbank_code);
    //des2src(transdtl.bankcardno,rPack->scard0);
    //des2src(transdtl.mobile,rPack->sphone2);
    des2src(transdtl.opercode,trans.opercode);
    transdtl.status[0]=DTLSTATUS_SUCCESS;
    transdtl.revflag[0]='0';
    transdtl.errcode=0;
    transdtl.custid=tCardAccount.custid;
    des2src(transdtl.showcardno,tCard.showcardno);
    GetCustBaseInfoByCustID(transdtl.custid,transdtl.custname,transdtl.stuempno,NULL);
    ret=DB_t_transdtl_add(&transdtl);
    if(ret) {
        if(DB_REPEAT==ret)
            return E_DB_TRANSDTL_E;
        else
            return E_DB_TRANSDTL_I;
    }
    SetCol(handle,F_LVOL1,F_LSAFE_LEVEL2,F_LVOL5,F_LVOL6,
           F_SALL_NAME,F_SPAGER,F_SCERT_NO,F_SHOLDER_AC_NO,F_LSAFE_LEVEL,F_SMARKET_CODE2,
           F_SEMAIL2,F_SMARKET_CODE,F_SDATE0,F_SNOTE,
           F_SSTAT_TYPE,F_SSTAT_TYPE2,F_SNATION_CODE,F_SBRANCH_CODE0,
           F_LVOL0,F_STX_PWD,F_LVOL8,F_LVOL11,F_LVOL12,
           F_SORDER0,F_SORDER1,F_SORDER2,F_SDATE3,F_STIME3,F_SEMP,
           F_LWITHDRAW_FLAG,F_LSERIAL1,F_VSMESS,F_SNAME2,0);
    outPack->lvol1=tCustomer.custid;
    outPack->lsafe_level2=tCustomer.custtype;
    outPack->lvol5=tCard.feetype;
    des2src(outPack->sall_name,tCustomer.custname);
    des2src(outPack->spager,tCustomer.stuempno);
    des2src(outPack->scert_no,tCustomer.deptcode);
    des2src(outPack->semail2,tCustomer.idno);
    des2src(outPack->smarket_code,tCustomer.sex);
    des2src(outPack->smarket_code2,tCustomer.idtype);
    outPack->lsafe_level=tCard.cardtype;
    des2src(outPack->sdate0,tCard.expiredate);
    outPack->lvol0=tCard.cardno;
    outPack->lvol6=trans.paycnt;
    des2src(outPack->stx_pwd,tCard.cardpwd);
    des2src(outPack->sorder0,tCard.showcardno);
    des2src(outPack->sname2,tCard.cardverno);
    //	des2src(outPack->sorder0,tCard.showcardno);
    strcpy(outPack->snote,CARD_STRUCT_VERSION);			  //制卡版本号
    strcpy(outPack->sorder1,CARD_REGISTER_PUBLISH_CODE);	  //发卡注册标识号
    strcpy(outPack->sorder2,CARD_REGISTER_SERVICE_CODE);	  //服务注册标识号
    outPack->lvol8=D4U5(pAccTrans->trans.cardaftbal*100,0);
    outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
    outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
    sprintf(outPack->sholder_ac_no,"%d",tCustomer.custid);  //客户号
    des2src(outPack->sstat_type,tCustomer.idtype);		  //证件类型
    des2src(outPack->snation_code,tCustomer.country); 	  //国籍
    des2src(outPack->sstat_type2,tCustomer.nation); //民族
    des2src(outPack->sbranch_code0,tCustomer.areacode);	  //院校代码
    des2src(outPack->sdate3,pAccTrans->trans.accdate);
    des2src(outPack->stime3,pAccTrans->trans.acctime);
    des2src(outPack->semp,trans.opercode);
    outPack->lwithdraw_flag=trans.termid;
    outPack->lserial1=trans.termseqno;
    sprintf(trans.remark,"%s卡余额%.2lf元",pAccTrans->remark.c_str(),pAccTrans->trans.cardaftbal);
    des2src(outPack->vsmess,trans.remark);
    PutRow(handle,outPack,pRetCode,szMsg);
    return 0;
}
