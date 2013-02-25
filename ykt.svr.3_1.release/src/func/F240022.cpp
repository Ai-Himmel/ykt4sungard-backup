/* --------------------------------------------
 * ��������: F240022.sqc
 * ��������: 2009-8-12
 * ��������: �����
 * �汾��Ϣ: 1.0.0.0
 * ������: ���п��󶨹���
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
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
    if(strncmp(rPack->scust_limit,customer.custname) !=0)			// ����
    {
    	return E_NAME_ERR
    }
    */
    if(strncmp(rPack->sname,customer.idno,18) !=0) {		// ���֤��
        return E_IDNO_ERR;
    }

    T_t_bankcard bankcard;
    memset(&bankcard,0,sizeof(bankcard));

    bankcard.custid=custid;
    des2src(bankcard.bankcardno,rPack->scust_auth);
    des2src(bankcard.bankcode,rPack->sbank_code);				// ǰ���ϴ�
    des2src(bankcard.lastsaved,CAccTrans::getInstance()->trans.sysdatetime);
    des2src(bankcard.createddate,rPack->sdate1);				// ������������
    des2src(bankcard.batchno,rPack->scust_no);					// ���з���ˮ��
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

