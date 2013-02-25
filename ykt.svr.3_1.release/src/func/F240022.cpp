/* --------------------------------------------
 * 程序名称: F240022.sqc
 * 创建日期: 2009-8-12
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 银行卡绑定管理
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"
#include "dbfunc_foo.h"

static int do_add_F240022(ST_PACK *rPack) {
    int ret;
    int custid;
    T_t_customer customer;

    ret = get_custid_by_stuempno(rPack->scust_auth2,&custid);
    if(ret)
        return ret;

    ret = DB_t_bankcard_del_by_custid(custid);
    if(ret) {
        if(DB_NOTFOUND != ret)
            return E_DB_BANKCARD_D;
    }
    memset(&customer,0,sizeof customer);
    ret = DB_t_customer_read_by_custid(custid,&customer);
    if(ret) {
        if(DB_NOTFOUND == ret)
            return E_DB_CUSTOMER_N;
        else
            return E_DB_CUSTOMER_R;
    }

    /*
    if(strncmp(rPack->scust_limit,customer.custname) !=0)			// 姓名
    {
    	return E_NAME_ERR
    }
    */
    if(strncmp(rPack->sname,customer.idno,18) !=0) {		// 身份证号
        return E_IDNO_ERR;
    }

    T_t_bankcard bankcard;
    memset(&bankcard,0,sizeof(bankcard));

    bankcard.custid=custid;
    des2src(bankcard.bankcardno,rPack->scust_auth);
    des2src(bankcard.bankcode,rPack->sbank_code);				// 前置上传
    des2src(bankcard.lastsaved,CAccTrans::getInstance()->trans.sysdatetime);
    des2src(bankcard.createddate,rPack->sdate1);				// 银行清算日期
    des2src(bankcard.batchno,rPack->scust_no);					// 银行方流水号
    ret=DB_t_bankcard_add(&bankcard);
    if(ret) {
        if(DB_REPEAT!=ret)
            return E_DB_BANKCARD_I;
    }

    return 0;

}


static int do_delete_F240022(ST_PACK *rPack) {
    int ret;
    int custid;
    ret = get_custid_by_stuempno(rPack->scust_auth2,&custid);
    if(ret)
        return ret;

    ret = DB_t_bankcard_del_by_custid(custid);
    if(ret) {
        if(DB_NOTFOUND != ret)
            return E_DB_BANKCARD_D;
    }
    return 0;
}

int F240022(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret = 0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    switch(rPack->sstatus0[0]) {
    case 'A':
        pAccTrans->trans.transcode=MAKETRANSCODEADD(TCM_BANKCARD);
        ret = do_add_F240022(rPack);
        break;
    case 'D':
        pAccTrans->trans.transcode=MAKETRANSCODEDEL(TCM_BANKCARD);
        ret = do_delete_F240022(rPack);
        break;
    default:
        break;
    }
    if(ret)
        return ret;
    /*
    ret=pAccTrans->addOperDtl(rPack->semp);
    if(ret)
    	return ret;
    */
    return 0;
}

