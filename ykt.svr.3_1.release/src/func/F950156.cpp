/* --------------------------------------------
 * 创建日期: 2009-04-28
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:鑫三强CPU卡脱机流水保存
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
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include "interfacefunc.h"
#include "interface.h"
#include "transfunc.h"

int F950156(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

    CAccTrans *pAccTrans=CAccTrans::getInstance();

    T_t_posdtl posdtl;
    memset(&posdtl,0,sizeof(posdtl));
    Cpack2Posdtl(rPack,posdtl);
    posdtl.shopid=0;//重置商户号为0
    des2src(posdtl.coldate,pAccTrans->trans.transdate);
    des2src(posdtl.coltime,pAccTrans->trans.transtime);
    if(!strlen(posdtl.devphyid)) {
        writelog(LOG_ERR,"recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
        return ERRIF_POS_TERMID;
    }
    ret=GetDeviceidByDevphyid(posdtl.devphyid,&(posdtl.termid));
    if(ret) {
        writelog(LOG_ERR,"recv offline posdtl ret[%d]devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",ret,posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
    }
    posdtl.status[0]='1';
    switch(posdtl.transmark) {
    case 1:
        posdtl.transmark = 0x99;
        break;
    case 2:
        posdtl.transmark = 0x02;
        break;
    case 3:
        posdtl.transmark = 0xFE;
        break;
    case 5:
        posdtl.transmark = 0x00;
        break;
    default:
        break;
    }
    g_dbchkerr=0;
    ret = DB_t_posdtl_add(&posdtl);
    if (ret) {
        g_dbchkerr=1;
        if(DB_REPEAT!=ret) {
            writelog(LOG_ERR,"ret[%d]devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",ret,posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
            return ERRIF_DATABASE_INS;
        }
    }
    g_dbchkerr=1;
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_LVOL4,F_SPHONE3,0);
    out_pack->lvol4 = rPack->lvol4;
    des2src(out_pack->sphone3,posdtl.devphyid);
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
}

