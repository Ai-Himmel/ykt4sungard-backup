#include "payment.h"
//#include "svrlink.h"
#include "ext_consumer.h"
#include "dbfunc_foo.h"
#include "interfacefunc.h"
#include "busqc.h"
#include "bufunc.h"

extern CSvrLink *g_pSvrLink;  // 与业务调度中心的连接

//extern CSvrLink g_SvrLink;  // 与业务调度中心的连接

static int register_payment(CPaymentBase *p)
{
    CPaymentBase::PAYMENT_LIST::iterator i;
    for (i = CPaymentBase::s_payments_.begin(); i != CPaymentBase::s_payments_.end(); ++i)
    {
        // 已经存在提示
        CPaymentBase *b = *i;
        if (b->paycode() == p->paycode())
        {
            writelog(LOG_ERR, "转账交易已经存在，不能重复定义,payment[%d]", p->paycode());
            return -1;
        }
    }
    CPaymentBase::s_payments_.push_back(p);
    return 0;
}
/*
static int SetHeadCol(ST_CPACK *in_cpack, ...)
{
    va_list ap;
    int arg;
    va_start(ap, in_cpack);
    while ((arg = va_arg(ap, int)) >= 0)
    {
        SetParmBit(&(in_cpack->head), arg);
    }
    va_end(ap);
    return(g_SvrLink.SetCol(0, in_cpack->head.ParmBits));
}
*/
// CPaymentBase
CPaymentBase::PAYMENT_LIST CPaymentBase::s_payments_;
//REGISTER_PAYMENT(CPaymentBase)
CPaymentBase* CPaymentBase::find_payment(int paycode)
{
    PAYMENT_LIST::iterator i;
    CPaymentBase *normal_pay = NULL;
    for (i = CPaymentBase::s_payments_.begin(); i != CPaymentBase::s_payments_.end(); ++i)
    {
        CPaymentBase *PayTrans = *i;
        if (PayTrans->paycode() == paycode)
            return PayTrans;
        if (PayTrans->paycode() == PAYMENT_NORMAL)
            normal_pay = PayTrans;
    }
    // 用通用支付交易
    return normal_pay;
}
int CPaymentBase::init(TRUSERID *handle, ST_CPACK *aPack, ST_PACK *in_pack)
{
    int ret;
    memset(&payment_, 0, sizeof payment_);
    //paycode_=in_pack->lcert_code;
    ret = DB_t_cfgpayment_read_by_paycode(paycode_, &payment_);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            writelog(LOG_ERR, "系统中未配置支付交易,交易码[%d]", this->paycode());
            return ERRINFO(E_NOTEXIST_PAYCODE, this->paycode());
        }
        return E_DB_CFGPAYMENT_R;
    }
    if (payment_.enabled != 1)
    {
        writelog(LOG_ERR, "支付交易[%d][%s]暂停使用", payment_.paycode, payment_.summary);
        ERRTIP("%s暂停使用", payment_.summary);
        return E_COMMON_ERR;
    }
    memset(&shop_, 0, sizeof shop_);
    ret = DB_t_shop_read_by_shopid(payment_.shopid, &shop_);
    if (ret)
    {
        writelog(LOG_ERR, "读取支付交易[%d]对应商户[%d]信息失败", payment_.paycode, payment_.shopid);
        return E_DB_SHOP_R;
    }
    if (shop_.status[0] != STATUS_NORMAL)
        return ERRINFO(E_SHOP_LOGOUT, shop_.shopid);
    if (shop_.shoptype != SHOPTYPE_COSUMESHOP)
    {
        return E_SHOP_NOT_COSUMESHOP;
    }
    ret = DB_t_paypara_read_by_paycode_and_paraname(paycode_, "pushflag", &paypara_);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            writelog(LOG_ERR, "支付码%d推送参数未配置", this->paycode());
            //return E_DB_PAYPARA_N;
        }
        else
            return E_DB_PAYPARA_R;
    }
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    des2src(pAccTrans->trans.shopaccno, shop_.accno);
    return 0;
}
int CPaymentBase::fini(int result, ST_PACK *in_pack)
{
    int ret;
    if (result == 0)
    {
        dtl_.status[0] = DTLSTATUS_SUCCESS;
        ret = DB_t_transdtl_update_lock_by_c0(&dtl_);
        if (ret)
        {
            return E_DB_TRANSDTL_U;
        }
    }
    else
    {
        sprintf(dtl_.remark, "交易失败 %d", result);
        dtl_.status[0] = DTLSTATUS_SUCCESS;
        ret = DB_t_transdtl_update_lock_by_c0(&dtl_);
        if (ret)
        {
            return E_DB_TRANSDTL_U;
        }
        ret = db_commit();
        if (ret)
        {
            writelog(LOG_ERR, "提交事务失败，accdate[%s],termid[%d],termseqno[%d]",
                     dtl_.accdate, dtl_.termid, dtl_.termseqno);
            return ret;
        }
    }
    return 0;
}

int CPaymentBase::tend_acc(ST_PACK *rPack, ST_PACK *out_pack)
{
    int ret = 0;
    int len;
    T_t_device device;
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    TRANS& trans = pAccTrans->trans;
    pAccTrans->trans.transcode = TC_CARDPAYMENT;
    des2src(pAccTrans->trans.opercode, rPack->semp);
    pAccTrans->trans.termid = rPack->lvol4;
//  if(!pAccTrans->trans.termid)
//      return E_INPUTNULL_TERMID;
    des2src(trans.refno, rPack->scust_auth);    //发送方凭证号
    trans.cardflag = 1;
    trans.usecardflag = 1;
    trans.cardno = rPack->lvol0;
    trans.purseno = PURSE_NO_ONE;
    trans.paycnt = rPack->lvol1 + 1;
    trans.cardbefbal = rPack->damt0;
    trans.termid = rPack->lvol4;
    trans.inputamt = rPack->damt1;
    trans.unusedamt = trans.inputamt;
    //des2src(trans.opercode,rPack->scust_no);
    trans.cardaftbal = trans.cardbefbal - trans.inputamt;
    //writelog(LOG_INFO,"oeprcode[%s],termid[%d]",trans.opercode,trans.termid);
    // 入账合法性检查
    ret = pAccTrans->InitTrans();
    if (ret)
        return ret;
    // 检查合法性
    if (amtcmp(trans.inputamt, trans.cardbefbal) > 0)
    {
        return ERRINFO(E_CARD_BALANCE_SHORTAGE, trans.cardbefbal);
    }
    // 卡的检查
    memset(&card_, 0, sizeof(card_));
    // 检查账户
    memset(&account_, 0, sizeof(account_));
    memset(&dtl_, 0, sizeof(dtl_));
    dtl_.exttype = rPack->lcert_code;
    ret = pAccTrans->CheckAcc(&card_, &account_, &dtl_);
    if (ret)
        return ret;
    // 保持第三方账号
    des2src(dtl_.extdata, rPack->sphone);
    len = strlen(dtl_.extdata);
    if (len < sizeof(dtl_.extdata) - 1)
        memcpy(dtl_.extdata + len, rPack->saddr, sizeof(dtl_.extdata) - 1 - len);
    ret = pAccTrans->GenTransdtl(&dtl_, DTLSTATUS_INIT);
    if (ret)
    {
        writelog(LOG_ERR, "GenTransdtl ret=%d", ret);
        return ret;
    }
    if (strlen(trans.opercode) < 1)
    {
        if (trans.termid > 0)
        {
            memset(&device, 0, sizeof device);
            ret = DB_t_device_read_by_deviceid(trans.termid, &device);
            if (ret)
            {
                if (DB_NOTFOUND == ret)
                    return E_NOTEXIST_DEVICE;
                else
                    return E_DB_DEVICE_R;
            }
            if (rPack->lvol5 > 0 && rPack->lvol5 < device.lastseqno)
            {
                return E_DEVICE_PARAM_ERR;
            }
        }
    }
    // 输出参数
    out_pack->lvol0 = trans.termseqno;
    out_pack->damt0 = trans.cardaftbal;
    out_pack->lvol5 = D2I(trans.cardaftbal * 100.0);
    out_pack->damt2 = trans.cardbefbal;
    out_pack->damt1 = trans.inputamt;
    des2src(out_pack->sname2, dtl_.refno);
    des2src(out_pack->sdate1, dtl_.accdate);
    des2src(out_pack->sdate3, trans.accdate);
    des2src(out_pack->sname2, trans.refno);
    out_pack->lwithdraw_flag = trans.termid;
    out_pack->lserial1 = trans.termseqno;
    return 0;
}
int CPaymentBase::get_refno()
{
    int ret = 0;
    T_t_refno tRefno;
    memset(&tRefno, 0, sizeof(tRefno));
    get_random(tRefno.mac);
    ret = GetNewRefno(tRefno.refno);
    if (ret)
        return ret;
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    des2src(tRefno.lastsaved, pAccTrans->trans.sysdatetime);
    ret = DB_t_refno_add(&tRefno);
    if (ret)
    {
        if (DB_REPEAT == ret)
            return E_DB_REFNO_E;
        else
            return E_DB_REFNO_I;
    }
    strcpy(refno_, tRefno.refno);
    strcpy(mac_, tRefno.mac);
    return 0;
}
int CPaymentBase::acc(ST_PACK *rPack, ST_PACK *out_pack, T_t_transdtl **transdtl)
{
    int ret;
    memset(&dtl_, 0, sizeof dtl_);
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    TRANS& trans = pAccTrans->trans;
    T_t_device device;
    T_t_transdtl tempdtl;
    ret = DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(
              trans.accdate, rPack->lvol4, rPack->lvol6, &dtl_);
    if (ret)
    {
        writelog(LOG_ERR, "accdate[%s]termid[%d]termseqno[%d]", trans.accdate, rPack->lvol4, rPack->lvol6);
        if (DB_NOTFOUND == ret)
            return E_DB_TRANSDTL_N;
        return E_DB_TRANSDTL_R;
    }
    // 流水已经入账
    if (dtl_.status[0] == DTLSTATUS_SUCCESS)
    {
        // TODO : 流水已经入账，直接返回
        strcpy(out_pack->vsmess, "交易成功");
        return 0;
    }
    /*
    if(strcmp(dtl_.opercode,rPack->scust_no) != 0)
    {
        ERRTIP("非法操作员号，不一致操作员");
        return E_COMMON_ERR;
    }
    */
    if (dtl_.exttype != rPack->lcert_code)
    {
        ERRTIP("非法交易请求，支付码不一致");
        return E_COMMON_ERR;
    }
    pAccTrans->trans.transcode = TC_CARDPAYMENT;
    trans.termseqno = dtl_.termseqno;
    trans.termid = dtl_.termid;
    des2src(trans.opercode, dtl_.opercode);
    ret = pAccTrans->InitTrans();
    if (ret)
    {
        writelog(LOG_ERR, "InitTrans ret[%d]", ret);
        return ret;
    }
    //GetCpackDataString(rPack,pAccTrans->cpackdata);
    trans.cardno = dtl_.cardno;
    trans.purseno = dtl_.purseno;
    trans.paycnt = dtl_.cardcnt;
    trans.cardbefbal = dtl_.cardbefbal;
    trans.cardaftbal = dtl_.cardbefbal;
    trans.inputamt = dtl_.amount;
    trans.unusedamt = trans.inputamt;
    pAccTrans->SetSummary(payment_.summary);
    // 卡的检查
    memset(&card_, 0, sizeof(card_));
    // 检查账户
    memset(&account_, 0, sizeof(account_));
    memset(&tempdtl, 0, sizeof tempdtl);
    ret = pAccTrans->CheckAcc(&card_, &account_, &tempdtl);
    if (ret)
        return ret;
    trans.custid = card_.custid;
    trans.feetype = card_.feetype;
    trans.cardflag = 1;
    trans.usecardflag = 1;
    // 交易次数更新
//  ret=UpdateCardBitmap(trans.cardno,trans.cardcnt,CARDBITMAPTYPE_DEC,0);
//  if(ret)
//      return ret;
    if (amtcmp(trans.inputamt, trans.cardbefbal) > 0)
        return ERRINFO(E_CARD_BALANCE_SHORTAGE, trans.cardbefbal);
    des2src(trans.cardaccno, account_.accno);
    // 商户信息
    strcpy(trans.shopaccno, shop_.accno);
    // 正式入账
    ret = pAccTrans->doMainTrans();
    if (ret)
    {
        writelog(LOG_ERR, "doMainTrans,accdate[%s]termid[%d],termseqno[%d],ret[%d]",
                 trans.accdate, trans.termid, trans.termseqno, ret);
        return ret;
    }
    if (strlen(trans.opercode) < 1)
    {
        if (trans.termid > 0)
        {
            memset(&device, 0, sizeof device);
            ret = DB_t_device_read_lock_by_c0_and_deviceid(trans.termid, &device);
            if (ret)
            {
                if (DB_NOTFOUND == ret)
                    return ERRINFO(E_NOTEXIST_DEVICE, trans.termid);
                else
                    return ret;
            }
            device.lastseqno = trans.termseqno;
            ret = DB_t_device_update_lock_by_c0(&device);
            if (ret)
            {
                return ret;
            }
        }
    }
    if (amtcmp(trans.unusedamt, 0) > 0)
        return E_INPUT_AMT;
    if (amtcmp(trans.unusedamt, 0) < 0)
        return E_AMT_LACK;
    *transdtl = &dtl_;
    // 输出参数
    out_pack->lvol0 = dtl_.termseqno;
    out_pack->damt0 = dtl_.cardaftbal;
    out_pack->lvol5 = D2I(dtl_.cardaftbal * 100.0);
    out_pack->damt2 = dtl_.cardbefbal;
    out_pack->damt1 = dtl_.amount;
    des2src(out_pack->sname2, dtl_.refno);
    des2src(out_pack->sdate1, dtl_.accdate);
    writelog(LOG_INFO, "refno[%s]befbal[%.2lf]aftbal[%.2lf]ext amt[%.2lf]", out_pack->sname2, out_pack->damt2, out_pack->damt0, out_pack->damt1);
    return  0;
}
// CNormalPayTrans
REGISTER_PAYMENT(CNormalPayTrans)
int CNormalPayTrans::fini(int result, ST_PACK *in_pack)
{
    int ret;
    ret = CPaymentBase::fini(result, in_pack);
    if (ret)
    {
        writelog(LOG_ERR, "error failed!");
        return ret;
    }
    if (result != 0)
    {
        writelog(LOG_ERR, "payment[%d] exception!", result);
        ERRTIP("支付交易异常，系统参数错误");
        return E_COMMON_ERR;
    }
    return 0;
}
int CNormalPayTrans::init(TRUSERID *handle, ST_CPACK *aPack, ST_PACK *in_pack)
{
    int ret;
    char sysdate[9], systime[7];
    pushflag_ = 0;
    memset(&payment_, 0, sizeof payment_);
    memset(&paypara_, 0, sizeof paypara_);
    // 通用支付
    this->req_paycode_ = in_pack->lcert_code;
    ret = DB_t_cfgpayment_read_by_paycode(this->req_paycode_, &payment_);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            writelog(LOG_ERR, "系统中未配置支付交易,交易码[%d]", this->req_paycode_);
            return ERRINFO(E_NOTEXIST_PAYCODE, this->req_paycode_);
        }
        return E_DB_CFGPAYMENT_R;
    }
    if (payment_.enabled != 1)
    {
        writelog(LOG_ERR, "支付交易[%d][%s]已经被系统禁用", payment_.paycode, payment_.summary);
        ERRTIP("%s暂停使用", payment_.summary);
        return E_COMMON_ERR;
    }
//  if(payment_.paytype != 0)
//  {
//      writelog(LOG_ERR,"支付码[%d]不是通用支付交易",payment_.paycode);
//      ERRTIP("支付码[%d]不是通用支付交易",payment_.paycode);
//      return E_COMMON_ERR;
//  }
    memset(&shop_, 0, sizeof shop_);
    if (payment_.shopid == 0)
    {
        // 根据设备商户信息查询
        ret = db_getsysdatetime(sysdate, systime);
        if (ret)
        {
            writelog(LOG_ERR, "db_getsysdatetime err=%d", ret);
            return ERRIF_DATABASE_DIS;
        }
        ret = GetShopidByDeviceid(in_pack->lvol4, sysdate, systime, &(payment_.shopid));
        if (ret)
        {
            writelog(LOG_ERR, "GetShopidByDeviceid error,termid[%d],ret[%d]", in_pack->lvol4, ret);
            return ret;
        }
    }
    ret = DB_t_shop_read_by_shopid(payment_.shopid, &shop_);
    if (ret)
    {
        writelog(LOG_ERR, "读取支付交易[%d]对应商户[%d]信息失败", payment_.paycode, payment_.shopid);
        return E_DB_SHOP_R;
    }
    if (shop_.status[0] != STATUS_NORMAL)
        return ERRINFO(E_SHOP_LOGOUT, shop_.shopid);
    if (shop_.shoptype != SHOPTYPE_COSUMESHOP)
    {
        return E_SHOP_NOT_COSUMESHOP;
    }
    if (payment_.onlinepay)
    {
        ret = DB_t_paypara_read_by_paycode_and_paraname(this->req_paycode_, "pushflag", &paypara_);
        if (ret)
        {
            if (DB_NOTFOUND == ret)
            {
                writelog(LOG_ERR, "支付码[%d]推送参数未配置", this->req_paycode_);
                return E_DB_PAYPARA_N;
            }
            else
                return E_DB_PAYPARA_R;
        }
        pushflag_ = atoi(paypara_.paraval);
    }
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    des2src(pAccTrans->trans.shopaccno, shop_.accno);
    return 0;
}
int CNormalPayTrans::pre_transfer(TRUSERID* handle, ST_PACK *rPack, ST_PACK *out_pack)
{
    int ret = 0;
    char systime[9] = {0};
    ret = db_getsystime(systime);
    if (ret)
    {
        return ERRIF_DATABASE_QRY;
    }
    if ((strncmp(systime, "235000", 6) > 0) || (strncmp(systime, "001000", 6) < 0))
    {
        ERRTIP("不在服务时间,服务时间00:10至23:50");
        return E_COMMON_ERR;
    }
    return 0;
}
int CNormalPayTrans::PackData(ST_PACK *rPack, ST_CPACK& sPack)
{
    if (0 == payment_.bccdrtpno ||
            0 == payment_.bccfuncno ||
            0 == payment_.ip[0] ||
            0 == payment_.port)
    {
        writelog(LOG_ERR, "与第三方通讯参数配置不完整,payment_.bccdrtpno=[%d],payment_.bccfuncno=[%d],payment_.ip[0]=[%s],payment_.port=[%d]", payment_.bccdrtpno, payment_.bccfuncno, payment_.ip[0], payment_.port);
        ERRTIP("与第三方通讯参数配置不完整");
        return E_COMMON_ERR;
    }
    int ret = 0;
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    if (strlen(pAccTrans->trans.stuempno) < 1)
    {
        ret = GetCustBaseInfoByCustID(pAccTrans->trans.custid,
                                      pAccTrans->trans.custname, pAccTrans->trans.stuempno,
                                      pAccTrans->trans.remark);
        if (ret)
            return ret;
    }
    sPack.pack.lcert_code = payment_.paycode;
    sPack.pack.lwithdraw_flag = rPack->lwithdraw_flag;
    sPack.pack.lserial1 = rPack->lserial1;
    strcpy(sPack.pack.semp, rPack->semp);
    strcpy(sPack.pack.saddr, rPack->saddr);
    strcpy(sPack.pack.sdate3, rPack->sdate3);
    strcpy(sPack.pack.stime3, rPack->stime3);
    memcpy(sPack.pack.sbank_acc, rPack->sbank_acc, sizeof(sPack.pack.sbank_acc));
    sPack.pack.lvol8 = rPack->lvol8;
    sPack.pack.lsafe_level2 = rPack->lsafe_level2;
    strcpy(sPack.pack.sdate0, pAccTrans->trans.accdate);
    strcpy(sPack.pack.stime0, pAccTrans->trans.acctime);
    strcpy(sPack.pack.sphone3, pAccTrans->trans.refno);
    sPack.pack.lwithdraw_flag = pAccTrans->trans.termid;
    des2src(sPack.pack.vsvarstr0, rPack->vsvarstr0);
    sprintf(sPack.pack.scust_limit, "%d", payment_.shopid);
    des2src(sPack.pack.sholder_ac_no2, payment_.ip);
    des2src(sPack.pack.spager, pAccTrans->trans.stuempno);      //学号
    des2src(sPack.pack.sall_name, pAccTrans->trans.custname);   //姓名
    sprintf(sPack.pack.sbank_acc2, "%d", pAccTrans->trans.cardno);
    sPack.pack.lvol0 = pAccTrans->trans.cardno;                 //卡号
    sPack.pack.lvol1 = (int)D4U5(pAccTrans->trans.inputamt * 100, 0); //
    sPack.pack.lvol7 = (int)D4U5(pAccTrans->trans.cardbefbal * 100, 0); //卡余额
    sPack.pack.lvol2 = pAccTrans->trans.custid;                 //客户号
    des2src(sPack.pack.sbranch_code0, pAccTrans->trans.remark); //校区
    if (rPack->lsafe_level)
    {
        sprintf(sPack.pack.vsvarstr0, "%d", rPack->lsafe_level); //水控余额
    }
    strcpy(sPack.pack.sbank_code2, rPack->sbank_code2);
    sPack.pack.lvol4 = payment_.port;
    if (payment_.timeout < 5)
        payment_.timeout = 5;
    sPack.pack.lsafe_level = payment_.timeout; //毫秒
    switch (payment_.payeeacctype)
    {
    case PAT_INPUT:
        des2src(sPack.pack.sbank_acc, rPack->sbank_acc);
        break;
    case PAT_CARDNO:
        sprintf(sPack.pack.sbank_acc, "%d", pAccTrans->trans.cardno);
        break;
    case PAT_CUSTID:
        sprintf(sPack.pack.sbank_acc, "%d", pAccTrans->trans.custid);
        break;
    case PAT_STUEMPNO:
        des2src(sPack.pack.sbank_acc, pAccTrans->trans.stuempno);
        break;
    default:
        ERRTIP("支付参数表收款人账户类型配置错误");
        return E_COMMON_ERR;
    }
    return 0;
}
int CNormalPayTrans::qry_acc(TRUSERID* handle, ST_PACK *rPack, ST_PACK *out_pack)
{
    int ret = 0;
    ST_PACK ArrayPack[10];      // 设置返回包
    ST_CPACK aPack;             // 设置应答包
    ST_CPACK sPack;             // 设置发送包
    memset(&ArrayPack, 0, sizeof(ArrayPack));
    ResetNormalCPack(&sPack, 0, 1);
    SetPackHeadCol(&sPack.head,
                   F_LSERIAL1,
                   F_LSAFE_LEVEL2,
                   F_LVOL8,
                   F_SEMP,
                   F_SDATE3,
                   F_STIME3,
                   F_SPHONE3,
                   F_SADDR,
                   F_LCERT_CODE,
                   F_SCUST_LIMIT,
                   F_SBANK_CODE,
                   F_SBANK_ACC,
                   F_SBANK_ACC2,
                   F_SCUSTTYPES,
                   F_SDATE0,
                   F_STIME0,
                   F_LVOL0,
                   F_LVOL1,
                   F_LVOL2,
                   F_LVOL7,
                   F_SPAGER,
                   F_SALL_NAME,
                   F_SSTATION0,
                   F_LSAFE_LEVEL,
                   F_LWITHDRAW_FLAG,
                   F_SBRANCH_CODE0,
                   F_SHOLDER_AC_NO2,
                   F_LVOL4,
                   F_VSMESS,
                   F_VSVARSTR0,
                   0);
    PackData(rPack, sPack);
    sPack.head.RequestType = 851001;
    strcpy(sPack.pack.sbank_code, "1000");
    if (pushflag_)
    {
        ret = g_pSvrLink->ExtTransfer(payment_.bccdrtpno, payment_.bccfuncno, &sPack, NULL);
        writelog(LOG_INFO, "Ext call payment.cpp. bccdrtpno=[%d],bccfuncno=[%d],pushflag=[%d]", payment_.bccdrtpno, payment_.bccfuncno, pushflag_);
        if (ret)
        {
            writelog(LOG_ERR, "CGDCTPayment ExtTransfer error,[%d]", ret);
            return ret;
        }
        return 0;
    }
    else
    {
        ret = ExtCall(0, payment_.bccdrtpno, payment_.bccfuncno, 0, payment_.timeout + 5, &sPack, &aPack, ArrayPack);
        if (ret < 0 || aPack.head.retCode != 0)
        {
            ERRTIP(aPack.pack.vsmess);
            if (ret < 0)
            {
                writelog(LOG_ERR, "ExtCall  error,errcode=[%d],retCode=[%d]msg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
                return ret;
            }
            else
            {
                writelog(LOG_ERR, "ExtCall  error,errcode=[%d],retCode=[%d]msg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
                // 可能成功了，认为成功了
                return aPack.head.retCode;
            }
        }
        memcpy(out_pack, &aPack.pack, sizeof(ST_PACK));
        if (aPack.pack.sstation0[0] != '1' || aPack.pack.sstation0[1] != '0')
        {
            ERRTIP(aPack.pack.vsmess);
            return E_COMMON_ERR;
        }
    }
    return 0;
}
int CNormalPayTrans::transfer(TRUSERID* handle, ST_PACK *rPack, ST_PACK *out_pack)
{
    int ret = 0;
    if (payment_.onlinepay < 1)
        return 0;
    //CAccTrans *pAccTrans = CAccTrans::getInstance();
    ST_PACK ArrayPack[10];      // 设置返回包
    ST_CPACK aPack;             // 设置应答包
    ST_CPACK sPack;             // 设置发送包
    memset(&ArrayPack, 0, sizeof(ArrayPack));
    ResetNormalCPack(&sPack, 0, 1);
    SetPackHeadCol(&sPack.head,
                   F_LSERIAL1,
                   F_LSAFE_LEVEL2,
                   F_LVOL8,
                   F_SEMP,
                   F_SDATE3,
                   F_STIME3,
                   F_SADDR,
                   F_LCERT_CODE,
                   F_SCUST_LIMIT,
                   F_SBANK_CODE,
                   F_SBANK_ACC,
                   F_SBANK_ACC2,
                   F_LVOL0,
                   F_LVOL1,
                   F_LVOL2,
                   F_LVOL4,
                   F_LVOL7,
                   F_SPAGER,
                   F_SALL_NAME,
                   F_SBRANCH_CODE0,
                   F_LWITHDRAW_FLAG,
                   F_SDATE0,
                   F_STIME0,
                   F_SPHONE3,
                   F_SBANK_CODE2,
                   F_VSVARSTR0,
                   F_SHOLDER_AC_NO2,
                   F_LSAFE_LEVEL, 0);
    PackData(rPack, sPack);
    sPack.head.RequestType = 851002;
    strcpy(sPack.pack.sbank_code, "1001");
    if (pushflag_)
    {
        ret = g_pSvrLink->ExtTransfer(payment_.bccdrtpno, payment_.bccfuncno, &sPack, NULL);
        if (ret)
        {
            writelog(LOG_ERR, "ExtTransfer error,[%d]", ret);
            return ret;
        }
        writelog(LOG_INFO, "ExtTransfer OK!");
    }
    else
    {
        ret = ExtCall(0, payment_.bccdrtpno, payment_.bccfuncno, 0, payment_.timeout + 5, &sPack, &aPack, ArrayPack);
        if (ret < 0 || aPack.head.retCode != 0)
        {
            ERRTIP(aPack.pack.vsmess);
            if (ret < 0)
            {
                writelog(LOG_ERR, "ExtCall  error,errcode=[%d],retCode=[%d]msg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
                return ret;
            }
            else
            {
                writelog(LOG_ERR, "ExtCall  error,errcode=[%d],retCode=[%d]msg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
                // 可能成功了，认为成功了
                return aPack.head.retCode;
            }
        }
        if (aPack.pack.lsafe_level)
        {
            ERRTIP(aPack.pack.vsmess);
            writelog(LOG_ERR, "与第三方系统交易失败,错误信息[%s]", aPack.pack.vsmess);
            return E_COMMON_ERR;
        }
    }
    return 0;
}
int CNormalPayTrans::transfer_reverse()
{
    return 0;
}

// CTestTrans
REGISTER_PAYMENT(CTestTrans)
int CTestTrans::pre_transfer(TRUSERID* handle, ST_PACK *in_pack, ST_PACK *out_pack)
{
    if (in_pack->lvol11 == 0)
        return 0;
    ERRTIP("测试支付交易返回错误");
    return E_COMMON_ERR;
}
int CTestTrans::transfer(TRUSERID* handle, ST_PACK *in_pack, ST_PACK *out_pack)
{
    if (in_pack->lvol11 == 0)
        return 0;
    ERRTIP("测试支付交易返回错误");
    return E_COMMON_ERR;
}
// CGDMobileTrans
REGISTER_PAYMENT(CGDMobileTrans)
int CGDMobileTrans::pre_transfer(TRUSERID* handle, ST_PACK *rPack, ST_PACK *out_pack)
{
    int ret = 0;
    char host[21] = {0};    //对方机器的ip
    char portchar[10] = {0};
    short port = 0;             //对方机器的port
    //char rcvdata[package_len+1] = {0};      //接收对方的传送数据
    char senddata[package_len+1] = {0}; //加密后的传送数据
    char tempdate[package_len+1-200] = {0};
    char c_drtbranch[10] = {0};
    char c_bccbasefuncno[10] = {0};
    int DRTP_BRANCH = 0;
    int BCC_BASEFUNCNO = 0;
    memset(tempdate, 0, sizeof tempdate);
    CTcpSocket tcpsocket ;
    ST_PACK ArrayPack;          // 设置返回包
    ST_CPACK aPack;             // 设置应答包
    ST_CPACK sPack;             // 设置发送包
    int iAmt = (int)D4U5(rPack->damt1 * 100, 0);
    switch (iAmt)
    {
    case 3000:
    case 5000:
    case 10000:
    case 30000:
        break;
    default:
        ERRTIP("充值金额不在允许范围内");
        return E_COMMON_ERR;
    }
    char systime[9] = {0};
    ret = db_getsystime(systime);
    if (ret)
    {
        return ERRIF_DATABASE_QRY;
    }
    if ((strncmp(systime, "235000", 6) > 0) || (strncmp(systime, "001000", 6) < 0))
    {
        ERRTIP("不在服务时间,服务时间00:10至23:50");
        return E_COMMON_ERR;
    }
    ret = GetSysParaVal(2104, host);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    ret = GetSysParaVal(2105, portchar);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    ret = GetSysParaVal(2106, c_drtbranch);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    ret = GetSysParaVal(2107, c_bccbasefuncno);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    port = atoi(portchar);
    DRTP_BRANCH = atoi(c_drtbranch);
    BCC_BASEFUNCNO = atoi(c_bccbasefuncno);
    ret = package_send_data(rPack, 1, senddata);
    if (ret) {
        writelog(LOG_ERR, "packege send data error,error code is [%d]", ret);
        return ret;
    }
    memcpy(tempdate, senddata, package_len - 200);
    ResetNormalCPack(&aPack, 0, 1);
    memset(&ArrayPack, 0, sizeof(ArrayPack));
    ResetNormalCPack(&sPack, 0, 1);
    SetHeadCol(&sPack, F_SSECTYPES, F_LVOL0, F_LVOL1, F_SCUST_AUTH, 0);   // 设置发送windows BU的头部视图信息
    sPack.head.RequestType = 250001;
    des2src(sPack.pack.ssectypes, tempdate);
    des2src(sPack.pack.scust_auth, host);
    sPack.pack.lvol0 = port;
    sPack.pack.lvol1 = 1;
    ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, 8, &sPack, &aPack, &ArrayPack);
    if (ret < 0 || aPack.head.retCode != 0)
    {
        ERRTIP(aPack.pack.vsmess);
        if (ret < 0)
        {
            writelog(LOG_ERR, "Call 250001 error,errcode=[%d],retCode=[%d]msg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
            return ret;
        }
        else
        {
            writelog(LOG_ERR, "Call 250001 error,errcode=[%d],retCode=[%d]msg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
            // 可能成功了，认为成功了
            if (aPack.head.retCode == E_MOBILE_TRANS_TIME_OUT
                    || E_MOBILE_CHECK_MAC == aPack.head.retCode
                    || E_MOBILE_CHECK_FAIL == aPack.head.retCode)
                return 0;
            return aPack.head.retCode;
        }
    }
    return 0;
}
int CGDMobileTrans::package_send_data(ST_PACK *rPack, int flag, char *send_data)
{
    //int ret = 0;
    //char cellphone[31]={0};   //充值手机号
    double money = 0;       //充值金额
    //char sysdate[11] = {0};
    //char systime[9] = {0};
    char sysdatetime[20] = {0};
    char serialno[20] = {0};
    char sMoney[20] = {0};
    ext_phone_trans_t* phone_trans_struct;
    phone_trans_struct = (ext_phone_trans_t*)send_data;
    memset(phone_trans_struct, 0, sizeof(ext_phone_trans_t));
    phone_trans_struct->prix[0] = 0x31;
    memcpy(phone_trans_struct->length, "0067", 4);
    if (1 == flag)
    {
        memcpy(phone_trans_struct->type, "0100", 4);
    }
    else if (2 == flag)
    {
        memcpy(phone_trans_struct->type, "0200", 4);
    }
    //memcpy(phone_trans_struct->bitery,"0000000000000000",16);
    memset(phone_trans_struct->bitery, '0', sizeof(phone_trans_struct->bitery));
    //
    sprintf(phone_trans_struct->custid, "%-22d", card_.cardno);
    money = dtl_.amount;
    int i_money = D2I(D4U5(money * 100, 0));
    sprintf(sMoney, "%07d", i_money);
    memcpy(phone_trans_struct->money, sMoney, sizeof(phone_trans_struct->money));
    strcpy(sysdatetime, dtl_.accdate + 4);
    strcat(sysdatetime, dtl_.acctime);
    memcpy(phone_trans_struct->datetime, sysdatetime, 10);
    memcpy(phone_trans_struct->tracenum, dtl_.accdate, 8);
    // TODO : 必须唯一
    memcpy(serialno, dtl_.refno + 8, 6);
    memcpy(phone_trans_struct->tracenum + 8, serialno, 6);
    memcpy(phone_trans_struct->phone, rPack->sphone, strlen(rPack->sphone));
    memcpy(phone_trans_struct->retnum, "00", 2);
    memset(phone_trans_struct->plugdata, 0x20, sizeof(phone_trans_struct->plugdata));
    return 0;
}
int CGDMobileTrans::transfer(TRUSERID* handle, ST_PACK *rPack, ST_PACK *out_pack)
{
    int ret = 0;
    char host[21] = {0};    //对方机器的ip
    char portchar[10] = {0};
    short port = 0;             //对方机器的port
    char rcvdata[package_len+1] = {0};      //接收对方的传送数据
    char senddata[package_len+1] = {0}; //加密后的传送数据
    char tempdate[package_len+1-200] = {0};
    char c_drtbranch[10] = {0};
    char c_bccbasefuncno[10] = {0};
    int DRTP_BRANCH = 0;
    int BCC_BASEFUNCNO = 0;
    memset(tempdate, 0, sizeof tempdate);
    CTcpSocket tcpsocket ;
    ST_PACK ArrayPack;          // 设置返回包
    ST_CPACK aPack;             // 设置应答包
    ST_CPACK sPack;             // 设置发送包
    ret = GetSysParaVal(2104, host);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return E_DB_TRADESERIALERROR_R;
    }
    ret = GetSysParaVal(2105, portchar);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return E_DB_TRADESERIALERROR_R;
    }
    ret = GetSysParaVal(2106, c_drtbranch);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    ret = GetSysParaVal(2107, c_bccbasefuncno);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    port = atoi(portchar);
    DRTP_BRANCH = atoi(c_drtbranch);
    BCC_BASEFUNCNO = atoi(c_bccbasefuncno);
    ret = package_send_data(rPack, 2, senddata);
    if (ret) {
        writelog(LOG_ERR, "packege send data error,error code is [%d]", ret);
        return ret;
    }
    memcpy(tempdate, senddata, package_len - 200);
    ResetNormalCPack(&aPack, 0, 1);
    memset(&ArrayPack, 0, sizeof(ArrayPack));
    ResetNormalCPack(&sPack, 0, 1);
    SetHeadCol(&sPack, F_SSECTYPES, F_LVOL0, F_LVOL1, F_SCUST_AUTH, 0);   // 设置发送windows BU的头部视图信息
    sPack.head.RequestType = 250001;
    des2src(sPack.pack.ssectypes, tempdate);
    des2src(sPack.pack.scust_auth, host);
    sPack.pack.lvol0 = port;
    sPack.pack.lvol1 = 1;
    ret = ExtCall(0, DRTP_BRANCH, BCC_BASEFUNCNO, 0, 15, &sPack, &aPack, &ArrayPack);
    if (ret < 0 || aPack.head.retCode != 0)
    {
        if (ret < 0)
        {
            writelog(LOG_ERR, "Call 250001 error,errcode=[%d],retCode=[%d]Errmsg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
            return ret;
        }
        else
        {
            writelog(LOG_ERR, "Call 250001 error,errcode=[%d],retCode=[%d]Errmsg[%s]", ret, aPack.head.retCode, aPack.pack.vsmess);
            return aPack.head.retCode;
        }
    }
    des2src(rcvdata, aPack.pack.ssectypes);
    return 0;
}

// CGDWaterTrans
REGISTER_PAYMENT(CGDWaterTrans)
int CGDWaterTrans::pre_transfer(TRUSERID* handle, ST_PACK *in_pack, ST_PACK *out_pack)
{
    int ret = 0;
    char price1[16] = {0};
    char price2[16] = {0};
    char price3[16] = {0};
    double d_price1 = 0;
    double d_price2 = 0;
    double d_price3 = 0;
    ret = GetSysParaVal(2201, price1);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    ret = GetSysParaVal(2202, price2);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    ret = GetSysParaVal(2203, price3);
    if (ret) {
        writelog(LOG_ERR, "get_parameter error,error code=[%d]", ret);
        return ret;
    }
    d_price1 = atof(price1);
    d_price2 = atof(price2);
    d_price3 = atof(price3);
//  CAccTrans *pAccTrans=CAccTrans::getInstance();
    SetCol(handle, 0);
    SetCol(handle, F_LVOL0, F_LVOL1, F_LVOL5, F_DAMT0, F_DAMT1, F_DAMT2, F_SDATE1, F_SDATE3, F_LSERIAL1, F_LWITHDRAW_FLAG,
           F_SBANKNAME, F_SADDR, F_SNAME2, F_VSMESS, F_DAMT10, F_DAMT11, F_DAMT12, 0);
    out_pack->damt10 = D4U5(d_price1 / 600, 4);
    out_pack->damt11 = D4U5(d_price2 / 600, 4);
    out_pack->damt12 = D4U5(d_price3 / 600, 4);
    out_pack->lvol1 = out_pack->lvol0;
//  out_pack->lwithdraw_flag=pAccTrans->trans.termid;
//  des2src(out_pack->sdate3,pAccTrans->trans.accdate);
//  out_pack->lserial1=pAccTrans->trans.termseqno;
//  des2src(out_pack->sname2,pAccTrans->trans.refno);
    return 0;
}
int CGDWaterTrans::transfer(TRUSERID* handle, ST_PACK *in_pack, ST_PACK *out_pack)
{
    return pre_transfer(handle, in_pack, out_pack);
    //return 0;
}

// 广州大学城空中充值接口
REGISTER_PAYMENT(CGDCTPayment)
int CGDCTPayment::pre_transfer(TRUSERID* handle, ST_PACK *in_pack, ST_PACK *out_pack)
{
    ST_CPACK sPack;
    int ret;
    memset(&sPack, 0, sizeof sPack);
    ResetNormalCPack(&sPack, 0, 1);
    SetPackHeadCol(&sPack.head,
                   F_LCERT_CODE,
                   F_SCUST_LIMIT,
                   F_SBANK_CODE,
                   F_SBANK_ACC,
                   F_SBANK_ACC2,
                   F_SCUSTTYPES,
                   F_SDATE0,
                   F_STIME0,
                   F_LVOL0,
                   F_LVOL1,
                   F_LVOL2,
                   F_LVOL7,
                   F_SPAGER,
                   F_SALL_NAME,
                   F_SSTATION0,
                   F_LSAFE_LEVEL,
                   F_LWITHDRAW_FLAG,
                   F_SBRANCH_CODE0,
                   F_SHOLDER_AC_NO2,
                   F_LVOL4,
                   F_LVOL5,
                   F_VSVARSTR1,
                   F_SBANK_CODE2,
                   F_SPHONE3,
                   F_VSMESS, 0);
    PackData(in_pack, sPack);
    sPack.head.RequestType = 851001;
    sPack.head.recCount = 1;
    strcpy(sPack.pack.sbank_code, "1000");
    des2src(sPack.pack.sphone3, dtl_.refno);
    des2src(sPack.pack.sbank_code2, in_pack->sbank_code2);
    writelog(LOG_DEBUG, "PushData,sno[%d]dno[%d]func[%d]", handle->SourceNo, payment_.bccdrtpno, payment_.bccfuncno);
    ret = g_pSvrLink->ExtTransfer(payment_.bccdrtpno, payment_.bccfuncno, &sPack, NULL);
    if (ret)
    {
        writelog(LOG_ERR, "CGDCTPayment ExtTransfer error,[%d]", ret);
        return ret;
    }
    else
        writelog(LOG_ERR, "CGDCTPayment ExtTransfer OK!");
    return 0;
}
int CGDCTPayment::transfer(TRUSERID* handle, ST_PACK *in_pack, ST_PACK *out_pack)
{
    int ret;
    //CAccTrans *pAccTrans = CAccTrans::getInstance();
    ST_CPACK sPack;             // 设置发送包
    ResetNormalCPack(&sPack, 0, 1);
    SetPackHeadCol(&sPack.head,
                   F_LCERT_CODE,
                   F_SCUST_LIMIT,
                   F_SBANK_CODE,
                   F_SBANK_ACC,
                   F_SBANK_ACC2,
                   F_LVOL0,
                   F_LVOL1,
                   F_LVOL2,
                   F_LVOL4,
                   F_LVOL7,
                   F_SPAGER,
                   F_SALL_NAME,
                   F_SBRANCH_CODE0,
                   F_LWITHDRAW_FLAG,
                   F_SDATE0,
                   F_STIME0,
                   F_SPHONE3,
                   F_SBANK_CODE2,
                   F_VSVARSTR0,
                   F_VSVARSTR1,
                   F_SHOLDER_AC_NO2,
                   F_SBANK_CODE2,
                   F_LVOL5,
                   F_LSAFE_LEVEL, 0);
    PackData(in_pack, sPack);
    sPack.head.RequestType = 851002;
    strcpy(sPack.pack.sbank_code, "1001");
    des2src(sPack.pack.sphone3, dtl_.refno);
    des2src(sPack.pack.sbank_code2, in_pack->sbank_code2);
    writelog(LOG_DEBUG, "PushData,sno[%d]dno[%d]func[%d]", handle->SourceNo, payment_.bccdrtpno, payment_.bccfuncno);
    ret = g_pSvrLink->ExtTransfer(payment_.bccdrtpno, payment_.bccfuncno, &sPack, NULL);
    if (ret)
    {
        writelog(LOG_ERR, "CGDCTPayment ExtTransfer error,[%d]", ret);
        return ret;
    }
    else
        writelog(LOG_ERR, "CGDCTPayment ExtTransfer OK!");
    return 0;
}

int CGDCTPayment::PackData(ST_PACK *rPack, ST_CPACK& sPack)
{
    if (0 == payment_.bccdrtpno ||
            0 == payment_.bccfuncno ||
            0 == payment_.ip[0] ||
            0 == payment_.port)
    {
        writelog(LOG_ERR, "与第三方通讯参数配置不完整,payment_.bccdrtpno=[%d],payment_.bccfuncno=[%d],payment_.ip[0]=[%s],payment_.port=[%d]", payment_.bccdrtpno, payment_.bccfuncno, payment_.ip[0], payment_.port);
        ERRTIP("与第三方通讯参数配置不完整");
        return E_COMMON_ERR;
    }
    int ret = 0;
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    if (strlen(pAccTrans->trans.stuempno) < 1)
    {
        ret = GetCustBaseInfoByCustID(pAccTrans->trans.custid,
                                      pAccTrans->trans.custname, pAccTrans->trans.stuempno,
                                      pAccTrans->trans.remark);
        if (ret)
            return ret;
    }
    sPack.pack.lcert_code = payment_.paycode;
    sPack.pack.lwithdraw_flag = rPack->lwithdraw_flag;
    strcpy(sPack.pack.sdate0, pAccTrans->trans.accdate);
    strcpy(sPack.pack.stime0, pAccTrans->trans.acctime);
    strcpy(sPack.pack.sphone3, pAccTrans->trans.refno);
    sPack.pack.lwithdraw_flag = pAccTrans->trans.termid;
    des2src(sPack.pack.vsvarstr0, rPack->vsvarstr0);
    sprintf(sPack.pack.scust_limit, "%d", payment_.shopid);
    des2src(sPack.pack.sholder_ac_no2, payment_.ip);
    des2src(sPack.pack.spager, pAccTrans->trans.stuempno);      //学号
    des2src(sPack.pack.sall_name, pAccTrans->trans.custname);   //姓名
    sprintf(sPack.pack.sbank_acc2, "%d", pAccTrans->trans.cardno);
    sPack.pack.lvol0 = pAccTrans->trans.cardno;                 //卡号
    sPack.pack.lvol1 = (int)D4U5(pAccTrans->trans.inputamt * 100, 0); //卡号
    sPack.pack.lvol7 = (int)D4U5(pAccTrans->trans.cardbefbal * 100, 0); //卡余额
    sPack.pack.lvol2 = pAccTrans->trans.custid;                 //客户号
    des2src(sPack.pack.sbranch_code0, pAccTrans->trans.remark); //校区
    sPack.pack.lvol5 = pAccTrans->trans.termseqno;              // 交易流水号
    if (rPack->lsafe_level)
    {
        sprintf(sPack.pack.vsvarstr0, "%d", rPack->lsafe_level); //水控余额
    }
    strcpy(sPack.pack.sbank_code2, rPack->sbank_code2);
    sPack.pack.lvol4 = payment_.port;
    if (payment_.timeout < 5)
        payment_.timeout = 5;
    sPack.pack.lsafe_level = payment_.timeout; //毫秒
    switch (payment_.payeeacctype)
    {
    case PAT_INPUT:
        des2src(sPack.pack.sbank_acc, rPack->sbank_acc);
        break;
    case PAT_CARDNO:
        sprintf(sPack.pack.sbank_acc, "%d", pAccTrans->trans.cardno);
        break;
    case PAT_CUSTID:
        sprintf(sPack.pack.sbank_acc, "%d", pAccTrans->trans.custid);
        break;
    case PAT_STUEMPNO:
        des2src(sPack.pack.sbank_acc, pAccTrans->trans.stuempno);
        break;
    default:
        ERRTIP("支付参数表收款人账户类型配置错误");
        return E_COMMON_ERR;
    }
    return 0;
}


