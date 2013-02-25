/* --------------------------------------------、
 * 创建日期: 2009-06-17
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 批量生成临时客户号
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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


int F841609(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    int CustomerCount=0;
    int start_no=0;
    char temp[256] ="";
    CAccTrans *pAccTrans=CAccTrans::getInstance();

    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_VSMESS,0);

    CustomerCount=rPack->lvol0;//	数量

    T_t_customer  tCustomer;
    memset(&tCustomer,0,sizeof tCustomer);

//先增加客户
    ret = GetSysParaVal(GLOBE_FLAG_TEMPCARD_CUTTYPE,temp);
    if(ret) {
        ERRTIP("系统参数表没有配置参数标识为14的临时卡的客户类别");
        return ret;
    }
    tCustomer.custtype=atoi(temp);

    T_t_custtype tCustType;
    memset(&tCustType,0,sizeof(tCustType));

    ret=DB_t_custtype_read_by_custtype(tCustomer.custtype,&tCustType);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_CUSTTYPE,tCustomer.custtype);
        else
            return E_DB_CUSTTYPE_R;
    }
    if(tCustType.feetype < 1) {
        ERRTIP("客户类别[%d]类别名称[%s]没有设置收费类别",tCustType.custtype,tCustType.custtypename);
        return E_COMMON_ERR;
    }
    tCustomer.feetype=tCustType.feetype;

    T_t_feetype tFeetype;
    memset(&tFeetype,0,sizeof tFeetype);
    ret = DB_t_feetype_read_by_feetype(tCustomer.feetype,&tFeetype);
    if(ret) {
        if(DB_NOTFOUND == ret) {
            return ERRINFO(E_NOTEXIST_FEETYPE,tCustomer.feetype);
        } else
            return E_DB_FEETYPE_R;
    }
    tCustomer.status[0]=STATUS_NORMAL;
    strcpy(tCustomer.custname,"临时人员");	//客户名称
    tCustomer.custattr[0]='2';				//身份禁用标志1-禁用2-启用
    tCustomer.useflag[0]='0';
    strcpy(tCustomer.areacode,rPack->sbranch_code0);	//校区
    strcpy(tCustomer.batchno,pAccTrans->trans.sysdatetime);
    strcpy(tCustomer.opendate,pAccTrans->trans.accdate);

    for(int i=0; i<CustomerCount; i++) {
        ret=GetNewCustIDByShoolCode(rPack->sbranch_code0,tCustomer.custid);
        if(ret) {
            writelog(LOG_ERR,"school_code[%s]",rPack->sbranch_code0);
            return ret;
        }
        ret=DB_t_customer_add(&tCustomer);
        if(ret) {
            writelog(LOG_ERR,"DB_t_customer_add ret[%d]",ret);
            if(DB_REPEAT==ret)
                return  ERRINFO(E_DB_CUSTOMER_E,tCustomer.custid);
            else
                return  E_DB_CUSTOMER_I;
        }
        if(0==i)
            start_no=tCustomer.custid;
    }
    sprintf(out_pack->vsmess,"生成批次号%s,客户号从%d到%d共%d个客户自动生成完成",tCustomer.batchno,start_no,tCustomer.custid,CustomerCount);
    PutRow(handle,out_pack,pRetCode,szMsg);
    //writelog(LOG_DEBUG,out_pack->vsmess);
    return 0;
}
