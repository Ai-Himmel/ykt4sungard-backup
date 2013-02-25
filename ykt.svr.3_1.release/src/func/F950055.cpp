/* --------------------------------------------
 * ��������: 2010-06-10
 * ��������: �Ž�
 * �汾��Ϣ: 3.0.0.0
 * ������: ��������POS���ѽ��׳�����ȡ����ˮ
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
#include <string>
#include <sstream>

using namespace std;


int F950055(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret=0;

    T_t_posdtl posdtl;
    memset(&posdtl,0,sizeof(posdtl));

    Cpack2Posdtl(rPack,posdtl);

    if(strlen(posdtl.transdate)!=8) {
        writelog(LOG_ERR,"recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
        return ERRIF_SYSTEM;
    }
    if(strlen(posdtl.transtime)!=6) {
        writelog(LOG_ERR,"recv offline posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
        return ERRIF_SYSTEM;
    }
    if(!strlen(posdtl.devphyid)) {
        writelog(LOG_ERR,"recv posdtl err: devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
        return ERRIF_POS_TERMID;
    }
    ret=GetDeviceidByDevphyid(posdtl.devphyid,&(posdtl.termid));
    if(ret) {
        if(ret!=ERRIF_POS_NOREG)
            return ret;
    }
    if(posdtl.cardno<1)
        return ERRIF_CARD_NOTEXIST;

    ret=PosTransCancelProcess(posdtl);
    if(ret) {
        db_rollback();
        writelog(LOG_ERR,"OnlineTransCancelProcess ret[%d]transdate[%s]devphyid[%s]devseqno[%d]",ret,posdtl.transdate,posdtl.devphyid,posdtl.devseqno);
        posdtl.status[0]=DTLSTATUS_FAIL;
    } else {
        posdtl.status[0]=DTLSTATUS_SUCCESS;
    }
    ret = DB_t_posdtl_add(&posdtl);
    if (ret) {
        writelog(LOG_ERR,"ret[%d]devphyid[%s]devseqno[%d]cardno[%d]cardcnt[%d]transdate[%s]transtime[%s]",ret,posdtl.devphyid,posdtl.devseqno,posdtl.cardno,posdtl.cardcnt,posdtl.transdate,posdtl.transtime);
        if(DB_REPEAT!=ret)
            return ERRIF_DATABASE_INS;
    }
    return 0;
}

