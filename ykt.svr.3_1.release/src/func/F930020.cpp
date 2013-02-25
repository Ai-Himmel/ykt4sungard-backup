/* --------------------------------------------
 * 程序名称: F930020.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:下传补助发放名单
 * --------------------------------------------
 * 修改日期:2004-12-14
 * 修改人员:	闻剑
 * 修改描述: 修改业务逻辑
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------
 * 修改日期:2005-09-27
 * 修改人员:汤成
 * 修改描述: 修改业务逻辑
 * 版本信息:1.0.0.2
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"

int F930020(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    int ret = 0;
    int cnt=0;
    int msgid=0;
    T_t_msglist tMsgList;
    T_t_device	tDevice;

    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);

    ResetNormalCPack(&aPack,0,1);
    SetCol(handle,0);
    SetCol(handle,F_VSVARSTR0,0);

    if(strlen(in_pack->sdate0)==0) {
        *pRetCode=E_DEVPHYID_NULL;
        goto L_RETU;
    }
    memset(&tMsgList,0,sizeof(tMsgList));
    memset(&tDevice,0,sizeof tDevice);

    AddXmlItemStr(tMsgList.reqdata,XML_KEY_DEV999_ID,in_pack->sdate0);
    AddXmlItemInt(tMsgList.reqdata,XML_KEY_CARDID,in_pack->lvol5);
    AddXmlItemInt(tMsgList.reqdata,XML_KEY_SERIALNO,in_pack->lvol4);
    AddXmlItemInt(tMsgList.reqdata,XML_KEY_OUTNUM,in_pack->lvol6);
    AddXmlItemInt(tMsgList.reqdata,XML_KEY_SUBSIDYFEE,in_pack->lvol7);
    AddXmlItemStr(tMsgList.reqdata,XML_KEY_SUBSIDYTYPE,in_pack->sstatus0);
    AddXmlItemStr(tMsgList.reqdata,XML_KEY_SUBSIDYFLAG,in_pack->scurrency_type);
    AddXmlItemStr(tMsgList.reqdata,XML_KEY_ENDDT,in_pack->sdate1);

    if((ret = get_devinfo_by_phyid(in_pack->sdate0,&tDevice))) {
        *pRetCode = ret;
        goto L_RETU;
    }
    tMsgList.deviceid = tDevice.deviceid;
    tMsgList.funcno = 930020;
    tMsgList.msglevel = 2;
    ret=AddMsgLst(&tMsgList);
    if(ret) {
        *pRetCode=ret;
        writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
        goto L_RETU;
    }
    if(iRequest!=tMsgList.funcno)
        return 0;
    ret=db_commit();
    if(ret) {
        writelog(LOG_ERR,"db_commit ret[%d]",ret);
        *pRetCode=E_DB_COMMIT;
        goto  L_RETU;
    }
    msgid=tMsgList.msgid;
    des2src(out_pack->sdate0,in_pack->sdate0);
    for(cnt=0; (cnt<10)&&(tMsgList.errcode!=0); cnt++) {
        sleep(1);
        memset(&tMsgList,0,sizeof(tMsgList));
        ret=DB_t_msglist_read_by_msgid(msgid, &tMsgList);
        if(ret) {
            writelog(LOG_ERR,"DB_t_msglist_read_by_msgid err[%d]",ret);
            *pRetCode=E_DB_MSGLIST_R;
            goto L_RETU;
        }
    }
    switch(tMsgList.errcode) {
    case 0:		//成功
        des2src(out_pack->vsvarstr0,"成功");
        break;
    case 9999:		//交易未处理
        des2src(out_pack->vsvarstr0,"前置机无应答");
        break;
    default:			//交易已经处理,但结果是失败
        des2src(out_pack->vsvarstr0,tMsgList.errmsg);
        break;
    }
    PutRow(handle,out_pack,pRetCode,szMsg);
    return 0;
L_RETU:
    return  -1;
}





