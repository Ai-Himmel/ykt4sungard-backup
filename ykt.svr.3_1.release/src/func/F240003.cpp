/* --------------------------------------------
 * 程序名称: F240003.sqc
 * 创建日期: 2007-07-21
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 待冲正交易登记
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"


int F240003(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {

    int ret=0;
#if 0
    T_t_tif_tradeserial  tradeserial;
    T_t_card	card;
    int iSeqno=0;
    memset(&tradeserial,0,sizeof(T_t_tif_tradeserial));			//清空流水结构体
    memset(&card,0,sizeof card);

    ret=getNewUniqNo(KEYTYPE_TRADESERIAL, &iSeqno);			//流水号
    if(ret) {
        writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
        *pRetCode=E_TRANS_UNKNOW_ERROR;
        goto L_RETU;
    }
    ret=DB_t_card_read_by_cardno(atoi(rPack->sserial0),&card);
    if(ret) {
        *pRetCode=E_TRANS_SCHACC_NOEXIT;
        writelog(LOG_ERR,"Create serial_no error,error code=[%d]",ret);
        goto L_RETU;
    }


    tradeserial.cardno=atoi(rPack->sserial0);
    tradeserial.custid=card.custid;
    tradeserial.purseno=0;
    tradeserial.serial_no=iSeqno;
    tradeserial.serial_type=TXCODE_BANK_DETRANS;			//交易代码
    tradeserial.serial_state=SERISTAT_NONEEDDEBT;			//流水状态
    ret=get_datetime_from_db(tradeserial.operate_date,tradeserial.operate_time);
    if(ret) {
        writelog(LOG_ERR,"get_datetime_from_db error,error code=[%d]",ret);
        des2src(tradeserial.operate_date,getsysdate(NULL));		//交易日期
        des2src(tradeserial.operate_time,getsystime(NULL));		//交易时间
    }
    des2src(tradeserial.collect_date,tradeserial.operate_date);//采集日期
    des2src(tradeserial.collect_time,tradeserial.operate_time);//采集时间
    tradeserial.maindeviceid=GetTransferSystemId();		//子系统号码
    tradeserial.deviceid=atoi(rPack->sorder2);			//终端ID
    tradeserial.trade_fee=rPack->lvol5/100.0;		//转帐金额
    tradeserial.cardbefbal=rPack->lvol6/100.0;		//入卡金额
    tradeserial.cardaftbal=tradeserial.cardbefbal;		//出卡金额
    des2src(tradeserial.b_act_id,rPack->scust_auth);		//银行卡号
    tradeserial.sysid=rPack->lvol2;						//外部系统标识，此处为配置文件中读取参数
    tradeserial.condition_id=SELF_TRANS;				//自动/自助转帐标识
    des2src(tradeserial.opercode,OPER_SYSTEM_KEY);	//操作员代码
    tradeserial.reviseserial_no=rPack->lvol0;				//原始流水号
    tradeserial.trade_count=rPack->lvol1+1;				//交易次数
    tradeserial.tmark=0;

    ret=DB_t_tif_tradeserial_add(&tradeserial);
    if(ret) {
        writelog(LOG_ERR,"Insert t_tif_tradeserial table error,error code=[%d]",ret);
        *pRetCode=E_TRANS_UNKNOW_ERROR;
        goto L_RETU;
    }
#endif
    return 0;
}


