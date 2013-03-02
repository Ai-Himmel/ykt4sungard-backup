/* ----------------------------------------------------------
 * 创建日期：2009-12-20
 * 程序作者：汤成
 * 版本信息：3.0.0.0
 * 程序功能：第三方参数查询
 * ----------------------------------------------------------*/
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "errdef.h"
#include "pubdb.h"
#include "busqc.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "pubfunc.h"
#include "acctrans.h"

int F850007(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
	T_v_thirdpara third;
    memset(&third,0,sizeof third);
    ret = DB_v_thirdpara_read_by_thirdname_and_paraname(rPack->sname,rPack->sname2,&third);
    if(ret)
    {
        *pRetCode = E_DB_NOTFOUND;
        return -1;
    }
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_SNAME,F_SNAME2,F_VSVARSTR0,F_VSVARSTR1,F_LVOL0,0);
    des2src(out_pack->sname,rPack->sname);
    des2src(out_pack->sname2,rPack->sname2);
    des2src(out_pack->vsvarstr0,third.paraval);
    des2src(out_pack->vsvarstr1,third.remark);
    out_pack->lvol0 = third.paraflag;
    PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


