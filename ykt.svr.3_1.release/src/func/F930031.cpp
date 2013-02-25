/* --------------------------------------------
 * 程序名称: F930031.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:  收集消费流水入账
 * --------------------------------------------
 * 修改日期:2004-10-12
 * 修改人员:    闻剑
 * 修改描述:增加记账交易处理
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------
 * 修改日期:2011-06-19
 * 修改人员:    彭海宇
 * 修改描述:增加主钱包水控交易过滤，超过100元则直接标记为异常流水
 *          增加主钱包普通交易过滤，超过1000元则直接标记为异常流水
 * 版本信息:1.0.0.2
 * 备注信息:
 * --------------------------------------------
 * 修改日期:2011-12-18
 * 修改人员:    彭海宇
 * 修改描述:增加主钱包水控交易过滤，超过100元则直接标记为异常流水
 *          增加主钱包普通交易过滤，超过1000元则直接标记为异常流水
 * 版本信息:1.0.0.2
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "interfacefunc.h"
#include "busqc.h"
int F930031(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg) {
    CAccTrans *pAccTrans = CAccTrans::getInstance();
    int ret = 0;
    T_t_posdtl posdtl;
    memset(&posdtl, 0, sizeof(posdtl));
    writelog(LOG_INFO, "phyid:sphone3[%s],sdate1[%s]", rPack->sphone3, rPack->sdate1);
    if (strlen(rPack->sphone3) > 0)
        des2src(posdtl.devphyid, rPack->sphone3);               // 汇多设备物理ID(10位)
    else
        des2src(posdtl.devphyid, rPack->sdate1);                //物理设备ID
    ret = GetDeviceidByDevphyid(posdtl.devphyid, &(posdtl.termid));
    if (ret) {
        if (ret != ERRIF_POS_NOREG)
            return ret;
    }
    T_t_device tDevice;
    memset(&tDevice, 0, sizeof(tDevice));
    ret = DB_t_device_read_by_deviceid(posdtl.termid, &tDevice);
    if (ret) {
        if (DB_NOTFOUND == ret) {
            //因为三九联机交易设备物理ID可能突变,导致找不到设备,所以先置status为4(无效流水不入账)，避免三九前置渡塞后续流水
//          if((strcmp(tDevice.devtypecode,"0244")==0)||(strcmp(tDevice.devtypecode,"0245")==0))
//          {
            posdtl.status[0] = '4';
            posdtl.errcode = E_NOTEXIST_DEVICE;
//          }else{
//              return E_NOTEXIST_DEVICE;
//          }
        } else
            return E_DB_DEVICE_R;
    }
    des2src(posdtl.coldate, pAccTrans->trans.transdate);
    des2src(posdtl.coltime, pAccTrans->trans.transtime);
    posdtl.devseqno = rPack->lvol4;                         //上传端流水号
    posdtl.transmark = rPack->lvol12;                       //999交易标记
    posdtl.sysid  = rPack->lcert_code;                      //上传工作站标识(前置机注册号)
//  posdtl.managefee= rPack->lvol11;                        //
    posdtl.cardno = rPack->lvol5;                           //交易卡号
    posdtl.purseno = 0;
    posdtl.cardbefbal = rPack->lvol9 / 100.0;                       //入卡金额
    posdtl.cardaftbal = rPack->lvol10 / 100.0;                      //出卡金额
    posdtl.amount = rPack->lvol8 / 100.0;                       //本次消费金额
    posdtl.cardcnt = rPack->lvol7;                          //当前卡中帐户消费次数(累计使用次数)
    snprintf(posdtl.transdate, 9, "20%s", rPack->spost_code);   //发生日期(格式化输入的日期)
    des2src(posdtl.transtime, rPack->spost_code2);          //发生时间(格式化输入的时间)
    if (posdtl.status[0] == 0) {
        posdtl.status[0] = '1';
    }
    if (strcmp(posdtl.transdate, "20000000") != 0) {
        ret = IsInvalidDateTime(posdtl.transdate, "YYYYMMDD");
        if (ret) {
            posdtl.errcode = E_999_DATE; //上传流水交易日期有误
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "发生日期格式错误");
        }
        ret = IsInvalidDateTime(posdtl.transtime, "HHMMSS");
        if (ret) {
            posdtl.errcode = E_999_TIME; //上传流水交易时间有误
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "发生时间格式错误");
        }
    } else {
        des2src(posdtl.transdate, posdtl.coldate);
        des2src(posdtl.transtime, posdtl.coltime);
    }
    //维护设备监控状态
    T_t_devmonitor dev_monitor;
    memset(&dev_monitor, 0, sizeof dev_monitor);
    ret = DB_t_devmonitor_read_by_deviceid(tDevice.deviceid, &dev_monitor);
    des2src(dev_monitor.optime, CAccTrans::getInstance()->trans.sysdatetime);
    des2src(dev_monitor.coltime, CAccTrans::getInstance()->trans.sysdatetime);
    des2src(dev_monitor.devtime, CAccTrans::getInstance()->trans.sysdatetime);
    dev_monitor.deviceid = tDevice.deviceid;
    dev_monitor.beatstatus = 1;
    if (ret) {
        if (DB_NOTFOUND == ret) {
            ret = DB_t_devmonitor_add(&dev_monitor);
            if (ret) {
                writelog(LOG_ERR, "增加设备监控记录失败!deviceid=[%d]", tDevice.deviceid);
            }
        }
    } else {
        ret = DB_t_devmonitor_update_by_deviceid(tDevice.deviceid, &dev_monitor);
        if (ret) {
            writelog(LOG_ERR, "更新设备监控记录失败!deviceid=[%d]",tDevice.deviceid);
            if (DB_NOTFOUND == ret) {
                ret = DB_t_devmonitor_add(&dev_monitor);
                if (ret) {
                    writelog(LOG_ERR, "更新设备失败后增加设备监控记录也失败!deviceid=[%d]", tDevice.deviceid);
                }
            }
        }
    }
    if ((strcmp(tDevice.devtypecode, "0244") == 0) || (strcmp(tDevice.devtypecode, "0245") == 0)) {
        //水控消费
        T_t_purseposdtl purseposdtl;
        memset(&purseposdtl, 0, sizeof(purseposdtl));
        des2src(purseposdtl.coldate, posdtl.coldate);
        des2src(purseposdtl.coltime, posdtl.coltime);
        purseposdtl.devseqno = posdtl.devseqno;                         //上传端流水号
        purseposdtl.transmark = posdtl.transmark;                       //999交易标记
        purseposdtl.sysid  = posdtl.sysid;                      //上传工作站标识(前置机注册号)
        des2src(purseposdtl.devphyid, posdtl.devphyid);
        purseposdtl.cardno = posdtl.cardno;                         //交易卡号
        purseposdtl.pursetype = 4;                              //三九水控钱包号
        purseposdtl.cardbefbal = posdtl.cardbefbal;                         //入卡金额
        purseposdtl.cardaftbal = posdtl.cardaftbal;                     //出卡金额
        purseposdtl.amount = posdtl.amount;                         //本次消费金额
        purseposdtl.cardcnt = posdtl.cardcnt;                           //当前卡中帐户消费次数(累计使用次数)
        purseposdtl.status[0] = posdtl.status[0];
        purseposdtl.errcode = posdtl.errcode;
        if (tDevice.devphytype == PHYTYPE_999_DEV) {
            des2src(purseposdtl.transdate, posdtl.coldate);
            des2src(purseposdtl.transtime, posdtl.coltime);
        } else {
            des2src(purseposdtl.transdate, posdtl.transdate);
            des2src(purseposdtl.transtime, posdtl.transtime);
        }
        if ((amtcmp(posdtl.amount, -100) < 0) || (amtcmp(posdtl.amount, 100) > 0)) {
            posdtl.errcode = E_999_AMT; //金额错误
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "发生金额太大");
        }
        g_dbchkerr = 0;
        ret = DB_t_purseposdtl_add(&purseposdtl);
        if (ret) {
            g_dbchkerr = 1;
            if (DB_REPEAT == ret) {
                writelog(LOG_ERR, "serial_no[%d]cardno[%d]devphyid[%s]transdate[%s]transtime[%s]ret[%d]", posdtl.devseqno, posdtl.cardno, posdtl.devphyid, posdtl.transdate, posdtl.transtime, ret);
                return 0;
            } else
                return E_DB_PURSEPOSDTL_I;
        }
        g_dbchkerr = 1;
    } else {
        //普通消费
        if ((amtcmp(posdtl.amount, -1000) < 0) || (amtcmp(posdtl.amount, 1000) > 0)) {
            posdtl.errcode = E_999_AMT; //金额错误
            posdtl.status[0] = '4';
            strcpy(posdtl.errmsg, "发生金额太大");
        }
        g_dbchkerr = 0;
        ret = DB_t_posdtl_add(&posdtl);
        if (ret) {
            g_dbchkerr = 1;
            if (DB_REPEAT == ret) {
                writelog(LOG_ERR, "交易流水重复，serial_no=[%d],cardno=[%d],devphyid=[%s],transdate=[%s],transtime=[%s],ret=[%d]", posdtl.devseqno, posdtl.cardno, posdtl.devphyid, posdtl.transdate, posdtl.transtime, ret);
                return 0;
            } else
                return E_DB_POSDTL_I;
        }
        g_dbchkerr = 1;
    }
    return 0;
}
