/* --------------------------------------------
 * 程序名称: F930101.sqc
 * 创建日期: 2005-08-22
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 收集门禁流水
 * --------------------------------------------
 * 修改日期: 2009-11-30
 * 修改人员:    xlh
 * 修改描述:    增加考勤流水收集功能
 * 版本信息:    1.0.0.1
 * 备注信息:
 * --------------------------------------------
 * 修改日期: 2011-09-15
 * 修改人员:    phy
 * 修改描述:    增加三九手持机考勤流水收集功能
 * 版本信息:    1.0.0.2
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
#include "busqc.h"
#include "dbfunc_foo.h"

int F930101(TRUSERID *handle, int iRequest, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    int device_id = 0;
    int devusage = 0;
    T_t_doordtl doordtl;
    T_t_card tCard;
    T_t_customer customer;
    if (!strlen(rPack->sdate0))
    {
        return E_DEVPHYID_NULL;
    }
    memset(&doordtl, 0, sizeof(doordtl));
    memset(&tCard, 0, sizeof(tCard));
    memset(&customer, 0, sizeof(customer));
    ret = GetDevIdByDevPhyId(&device_id, rPack->sdate0);
    if (ret)
    {
        writelog(LOG_ERR, "设备物理号[%s]ret[%d]", rPack->sdate0, ret);
    }
    if (device_id)
    {
        ret = GetDevusageByDeviceID(device_id, &devusage);
        if (ret)
        {
            return ret;
        }
    }
    SQLCODE = 0;
    if (rPack->lvol7)
    {
        ret = DB_t_card_read_by_cardno(rPack->lvol7, &tCard);
        if (ret)
        {
            if (DB_NOTFOUND != ret)
                return E_DB_CARD_R;
        }
    }
    SQLCODE = 0;
    if (tCard.custid > 0)
    {
        ret = DB_t_customer_read_by_custid(tCard.custid, &customer);
        if (ret)
        {
            if (DB_NOTFOUND != ret)
                return E_DB_CUSTOMER_R;
        }
    }
    if (strlen(rPack->sdate1) == 6)
        sprintf(doordtl.transdate, "20%s", rPack->sdate1);
    else
        des2src(doordtl.transdate, rPack->sdate1);        //发生日期(格式化输入的日期)
    des2src(doordtl.transtime, rPack->spost_code2);       //发生时间(格式化输入的时间)
    doordtl.deviceid = device_id;                         //设备号
    des2src(doordtl.devphyid, rPack->sdate0);             // 设备物理号
    doordtl.devseqno = rPack->lvol3;                      //上传端流水号
    getsysdate(doordtl.coldate);                          //采集日期
    getsystime(doordtl.coltime);                          //采集时间
    doordtl.cardno = rPack->lvol7;                        //交易卡号
    des2src(doordtl.cardphyid, tCard.cardphyid);          //物理卡号
    des2src(doordtl.showcardno, tCard.showcardno);        //显示卡号
    des2src(doordtl.stuempno, customer.stuempno);         //学工号
    des2src(doordtl.custname, customer.custname);         //姓名
    doordtl.custid = tCard.custid;                        //客户号
    doordtl.transmark = rPack->lvol11;                    //999交易标志
    doordtl.sysid  = rPack->lcert_code;                   //上传工作站标识(前置机注册号)
    ret = DB_t_doordtl_add(&doordtl);
    if (ret)
    {
        if (DB_REPEAT == ret)
            return 0;
        else
            return E_DB_DOORDTL_I;
    }
    if (devusage == DU_JSB_ATTENDANCE)
    {
        ret = SaveKQSerial(&doordtl);
        if (ret)
        {
            writelog(LOG_ERR, "插入考勤流水表失败,errcode[%d]", ret);
        }
    }
    return 0;
}
