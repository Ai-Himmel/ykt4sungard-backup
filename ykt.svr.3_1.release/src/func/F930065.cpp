/* --------------------------------------------
 * 程序名称: F930065.sqc
 * 创建日期: 20051008
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 采集LPORT补助名单
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

int F930065(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    /*
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

    if(strlen(in_pack->sdate0)==0)
    {
    	*pRetCode=E_DEVPHYID_NULL;
    	goto L_RETU;
    }
    memset(&tDevice,0,sizeof tDevice);
    ret = DB_t_device_read_by_devphyid(in_pack->sdate0,&tDevice);
    if(ret)
    {
    	if(DB_NOTFOUND == ret)
    	{
    		*pRetCode = E_DB_DEVICE_N;
    	}
    	*pRetCode = E_DB_DEVICE_R;
    	goto L_RETU;
    }
    // 检查设备是不是LPORT
    if(strncmp(tDevice.devtype,"5301",4))
    {
    	*pRetCode = E_DEVICE_TYPE_NOT_FIT;
    	goto L_RETU;
    }
    memset(&tMsgList,0,sizeof(tMsgList));

    AddXmlItemStr(tMsgList.reqdata,XML_KEY_DEV999_NO,in_pack->sdate0);
    AddXmlItemInt(tMsgList.reqdata,XML_KEY_CARDID,in_pack->lvol5);

    tMsgList.funcno = 930065;
    tMsgList.msglevel = 3;
    ret=AddMsgLst(&tMsgList);
    if(ret)
    {
    	*pRetCode=ret;
    	writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
    	goto L_RETU;
    }
    if(iRequest!=tMsgList.funcno)
    	return 0;
    ret=db_commit();
    if(ret)
    {
    	writelog(LOG_ERR,"db_commit ret[%d]",ret);
    	*pRetCode=E_DB_COMMIT;
    	goto  L_RETU;
    }
    msgid=tMsgList.msgid;
    des2src(out_pack->sdate0,in_pack->sdate0);
    for(cnt=0;(cnt<10)&&(tMsgList.errcode!=0);cnt++)
    {
    	sleep(1);
    	memset(&tMsgList,0,sizeof(tMsgList));
    	ret=DB_t_msglist_read_by_msgid(msgid, &tMsgList);
    	if(ret)
    	{
    		writelog(LOG_ERR,"DB_t_msglist_read_by_msgid err[%d]",ret);
    		*pRetCode=E_DB_MSGLIST_R;
    		goto L_RETU;
    	}
    }
    switch(tMsgList.errcode)
    {
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
    */
    return  -1;
}
