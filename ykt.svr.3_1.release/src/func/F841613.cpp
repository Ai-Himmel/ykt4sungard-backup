/* --------------------------------------------
 * 程序名称: F841613.cpp
 * 创建日期: 2008-03-03
 * 程序作者: auto creat by wen jian
 * 版本信息: 1.0.0.0
 * 程序功能: 导入客户信息删除
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
#include "dbfunc_foo.h"

int F841613(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int    ret=0;
    CAccTrans *pAccTrans=CAccTrans::getInstance();
    pAccTrans->clear();
    GetCpackDataString(rPack,pAccTrans->cpackdata);
    pAccTrans->trans.transcode=TC_CUSTOMERTMPDEL;
    ret=pAccTrans->addOperDtl(rPack->semp);
    if(ret)
        return ret;
    char  stuempno[30+1]="";           	//学号或员工号

    char sqlcmd[512]="";

    des2src(stuempno,rPack->scert_no);
    if(!strlen(stuempno)) {
        return E_INPUT_STUEMP_NO;
    }
    sprintf(sqlcmd,"delete ykt_cur.t_customertmp where  stuempno='%s' ",stuempno);
    ret=DynamicStmtExecute(sqlcmd);
    if(ret) {
        writelog(LOG_ERR,"sql:[%s]",sqlcmd);
        if(DB_NOTFOUND==ret)
            return E_DB_CUSTOMER_TMP_N;
        else
            return E_DB_CUSTOMER_TMP_D;
    }
    return 0;
}
