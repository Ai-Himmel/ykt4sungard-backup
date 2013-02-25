/* --------------------------------------------
 * 程序名称: F950044.sqc
 * 创建日期: 2010-8-24
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能:  下传水控费率
 * --------------------------------------------*/
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

int F950044(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret,i,j;
    T_t_device tDevice;
    T_t_msglist tMsg;
    int retries = 0;
    int msgid;
    char msg[257] = "";
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    T_t_waterfeecfg tWaterFeeCfg;

    memset(&tMsg,0,sizeof tMsg);
    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_VSVARSTR0,0);

    memset(&tDevice,0,sizeof tDevice);


    if(rPack->lcert_code < 1) {
        return E_NOTEXIST_DEVICE;
    }

    ret = DB_t_waterfeecfg_read_by_feeid(rPack->lvol1,&tWaterFeeCfg);
    if(ret) {
        if(DB_NOTFOUND == ret) {
            writelog(LOG_ERR,"F950044,ret=[%d]",ret);
            return E_DB_WATERFEECFG_N;
        } else {
            writelog(LOG_ERR,"F950044,ret=[%d]",ret);
            return E_DB_WATERFEECFG_R;
        }
    }
    if((ret = DB_t_device_read_by_deviceid(rPack->lcert_code,&tDevice))) {
        if(DB_NOTFOUND==ret)
            return ERRINFO(E_NOTEXIST_DEVICE,rPack->lcert_code);
        else
            return E_DB_DEVICE_R;

    }

    if(tDevice.status[0]!=STATUS_NORMAL) {
        return ERRINFO(E_NOTEXIST_DEVICE,tDevice.devphyid);
    }

    tMsg.funcno = 950047;
    tMsg.msglevel=1;
    tMsg.maxsendcnt = 1;
    tMsg.deviceid= tDevice.deviceid;
    AddXmlItemInt(tMsg.reqdata,XML_KEY_FEE,tWaterFeeCfg.feeid);
    if((ret = AddMsgLst(&tMsg))) {
        return  ret;
    }
    strcpy(out_pack->vsvarstr0,"成功");
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
}

