/* --------------------------------------------
 * 创建日期: 2008-06-27
 * 程序作者:
 * 版本信息: 1.0.0.0
 * 程序功能: 一卡通交易冲正
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
int F846324(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    char oldaccdate[9]="";
    des2src(oldaccdate,rPack->sdate3);
    int oldtermid=rPack->lwithdraw_flag;
    int oldtermseqno=rPack->lserial1;

    if(strlen(oldaccdate)<1)
        return E_INPUTNULL_ACCDATE;
    if(oldtermid<1)
        return E_INPUTNULL_TERMID;
    if(oldtermseqno<1)
        return E_INPUTNULL_TERMSEQNO;

    T_t_transdtl transdtl;
    memset(&transdtl,0,sizeof(transdtl));
    ret=DB_t_transdtl_read_lock_by_c0_and_accdate_and_termid_and_termseqno(oldaccdate,oldtermid,oldtermseqno,&transdtl);
    if(ret) {
        writelog(LOG_ERR,"ret[%d]accdate[%s]termid[%d]termseqno[%d]",ret,oldaccdate,oldtermid,oldtermseqno);
        if(DB_NOTFOUND==ret)
            return E_DB_TRANSDTL_N;
        else
            return E_DB_TRANSDTL_R;
    }
    transdtl.status[0]=DTLSTATUS_FAIL;
    strcpy(transdtl.remark,"交易失败");
    ret=DB_t_transdtl_update_lock_by_c0(&transdtl);
    if(ret) {
        if(DB_NOTFOUND==ret)
            return E_DB_TRANSDTL_N;
        else
            return E_DB_TRANSDTL_U;
    }
    return 0;
}
