/* --------------------------------------------
 * 创建日期: Sep 23 2004
 * 程序作者: auto creat by wen jian
 * 版本信息: 1.0.0.0
 * 程序功能: 更新设备监控表
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
int F930057(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    char		devphyid[31]="";
    int 		ret=0;
    T_t_devmonitor  devmonitor;
    memset(&devmonitor,0,sizeof(devmonitor));

    devmonitor.deviceid=atoi(rPack->sorder2);

    if(devmonitor.deviceid<1) {
        des2src(devphyid, rPack->sdate1);
        ret = GetDevIdByDevPhyId(&(devmonitor.deviceid),devphyid);
        if(0 != ret) {
            writelog(LOG_ERR,"devphyid:%s",devphyid);
            return  ret;
        }
    }
    /*得到CPACK数据*/
    des2src(devmonitor.optime,CAccTrans::getInstance()->trans.sysdatetime);
    des2src(devmonitor.coltime,CAccTrans::getInstance()->trans.sysdatetime);
    devmonitor.beatstatus=rPack->lvol2;
    des2src(devmonitor.cardverno,rPack->sserial4);
    devmonitor.hardiskper=rPack->damt0;
    devmonitor.memoryper=rPack->damt1;
    devmonitor.cpuper=rPack->damt2;
    des2src(devmonitor.devtime,rPack->sholder_ac_no2);

    ret=DB_t_devmonitor_update_by_deviceid(devmonitor.deviceid,&devmonitor);
    if(ret) {
        if(DB_NOTFOUND==ret) {
            //设备心跳记录不存在（初始化时），则进行插入操作
            SQLCODE=0;
            ret=DB_t_devmonitor_add(&devmonitor);
            if(ret) {
                return E_DB_DEVMONITOR_I;
            }
            return 0;
        } else {
            return E_DB_DEVMONITOR_U;
        }
    }
    return 0;
}
