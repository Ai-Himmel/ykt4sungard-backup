/* --------------------------------------------
 * 程序名称: F847302.sqc
 * 创建日期: 2006-12-15
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能: 转帐失败
 * --------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "mypub.h"
#include "pubfunc.h"
#include "acctrans.h"
#include "busqc.h"
#include "dbfunc_foo.h"

int F847302(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg) {
    int ret = 0;
    /*
    T_t_card tCard;
    T_t_tif_tradeserial tTradeSerial, tPacketSerial;
    T_t_tif_writefailed tWriteFailed;
    char logicdate[11] = "";
    double dUniqNo = 0;

    memset(&tCard, 0, sizeof tCard);
    memset(&tTradeSerial, 0, sizeof tTradeSerial);
    memset(&tPacketSerial, 0, sizeof tPacketSerial);
    memset(&tWriteFailed, 0, sizeof tWriteFailed);

    if (rPack->lvol3 != 0 && rPack->lvol3 != 1)
    {
        writelog(LOG_DEBUG,"输入标志错误[%d]",rPack->lvol3);
        *pRetCode = E_INPUT_ERROR;
        goto L_RETU;
    }

    ret = DB_t_tif_tradeserial_read_by_serial_no(rPack->lvol1,&tTradeSerial);  //消费流水号
    if (ret)
    {
        writelog(LOG_DEBUG,"输入号不存在消费流水号[%d]",rPack->lvol1);
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_TRADESERIAL_N;
        }
        else
        {
            *pRetCode = E_DB_TRADESERIAL_R;
        }
        goto L_RETU;
    }

    ret = DB_t_card_read_lock_by_cur_and_cardno(tTradeSerial.cardno,&tCard);
    if (ret)
    {
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_CARD_N;
        }
        else
        {
            *pRetCode = E_DB_CARD_R;
        }
        goto L_RETU;
    }

    ret = DB_t_tif_tradeserial_read_by_serial_no(rPack->lvol2,&tPacketSerial); //充值流水号
    if (ret)
    {
        writelog(LOG_DEBUG,"输入号不存在充值流水号[%d]",rPack->lvol2);
        if (DB_NOTFOUND == ret)
        {
            *pRetCode = E_DB_TRADESERIAL_N;
        }
        else
        {
            *pRetCode = E_DB_TRADESERIAL_R;
        }
        goto L_RETU;
    }
    GetLogicDate(logicdate);
    tWriteFailed.cardno = tCard.cardno;
    des2src(tWriteFailed.transdate,logicdate);
    writelog(LOG_DEBUG,"大钱包交易金额[%f]",tTradeSerial.trade_fee);

    // 大钱包写卡失败
    if (0 == rPack->lvol3)
    {
        // 大钱包写卡失败
        ret = getNewUniqNo(KEYTYPE_WRITEFAILED, &dUniqNo);              //获得写卡失败表最大ID号
        if (ret)
        {
            writelog(LOG_ERR,"ret[%d]",ret);
            *pRetCode = ret;
            goto L_RETU;
        }
        tWriteFailed.id = D2I(dUniqNo);
        tWriteFailed.serial_no = tTradeSerial.serial_no;
        tWriteFailed.serial_type = tTradeSerial.serial_type;
        tWriteFailed.purese_no = PURSE_NO_ONE;
        tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
        tWriteFailed.deal_bala = tTradeSerial.trade_fee;
        des2src(tWriteFailed.comments, "大钱包写卡失败");
        ret = DB_t_tif_writefailed_add(&tWriteFailed);
        if (ret)
        {
            *pRetCode = E_DB_WRITEFAILED_I;
            goto L_RETU;
        }
    }
    tCard.cardstatus[CARDSTAT_TYPE_WFAIL] = STATE_TRUE;
    ret = DB_t_card_update_lock_by_cur(&tCard);
    if (ret)
    {
        *pRetCode = E_DB_CARD_U;
         goto L_RETU;
    }
    DB_t_card_free_lock_by_cur();

    ret = getNewUniqNo(KEYTYPE_WRITEFAILED, &dUniqNo);
    if (ret)
    {
        writelog(LOG_ERR,"ret[%d]",ret);
        *pRetCode = ret;
        goto L_RETU;
    }
    writelog(LOG_DEBUG,"小钱包交易金额[%f]",tPacketSerial.trade_fee);
    tWriteFailed.id = D2I(dUniqNo);
    tWriteFailed.serial_no = tPacketSerial.serial_no;
    tWriteFailed.serial_type = tPacketSerial.serial_type;
    tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
    tWriteFailed.purese_no = PURSE_NO_TWO;
    tWriteFailed.deal_bala = tPacketSerial.trade_fee;
    des2src(tWriteFailed.comments, "小钱包充值失败");
    ret = DB_t_tif_writefailed_add(&tWriteFailed);
    if (ret)
    {
        *pRetCode = E_DB_WRITEFAILED_I;
        goto L_RETU;
    }
    */
    return 0;
L_RETU:
    return -1;
}

