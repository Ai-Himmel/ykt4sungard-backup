/* --------------------------------------------
 * 程序名称: F847305.cpp
 * 创建日期: 2006-12-20
 * 程序作者: 李翔
 * 版本信息: 1.0.0.0
 * 程序功能:
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
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

#define     PURESE_COUNT 4

int F847305(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) {
    /*
        int ret=0;
    	int cardno = 0;
    	int cnt_purse_no = 0;
    	char deal_flag[1 + 1] = "";
    	T_t_card tCard;
    	T_t_tif_writefailed tWriteFailed;
    	memset(&tCard, 0, sizeof tCard);
        memset(&tWriteFailed, 0, sizeof(tWriteFailed));

        deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
        cardno = in_pack->lvol1;
        if (cardno <= 0)
        {
            *pRetCode = E_INPUT_CARDNO_CANNOT_NULL;
    		goto L_RETU;
        }

        ret = DB_t_card_read_lock_by_cur_and_cardno(cardno,&tCard);
        if (ret)
        {
            if (DB_NOTFOUND == ret)
                *pRetCode = E_DB_CARD_N;
            else
                *pRetCode = E_DB_CARD_R;
            goto L_RETU;
        }

        if (TXCODE_REWRITE_CARD == in_pack->lvol2)
        {// 当出现一个交易卡号, 多钱包号的时候, 必须所有的钱包都必须补写完成才能修改卡标志
            for (cnt_purse_no = 0; cnt_purse_no < PURESE_COUNT; cnt_purse_no++)
            {
                ret = DB_t_tif_writefailed_read_by_cardno_and_purese_no_and_deal_flag(tCard.cardno,cnt_purse_no,&deal_flag[0],&tWriteFailed);
                if (ret)
                {
                    if (DB_NOTFOUND == ret)
                    {
                        continue;
                    }
                    else
                    {
                        *pRetCode = E_DB_WRITEFAILED_R;
                        goto L_RETU;
                    }
                }
                // 查找出来有未有写入写卡标志的钱包号
    //          writelog(LOG_ERR,"第[%d]个钱包未有补写",cnt_purse_no+1);
                *pRetCode = E_CARD_REWRITE_REMAIN;
                goto L_RETU;
    */
    /*
    if (tWriteFailed.deal_flag[0] != CARDWFAIL_PACKET_DEAL_FLAG_N)
    {
        *pRetCode = E_CARD_REWRITE_REMAIN;
        goto L_RETU;
    }
    */
    /*
            }
            if (STATE_TRUE == tCard.cardstatus[CARDSTAT_TYPE_WFAIL])
            {
                tCard.cardstatus[CARDSTAT_TYPE_WFAIL] = STATE_FALSE;
            }
            ret = DB_t_card_update_lock_by_cur(&tCard);
            if(ret)
    		{
    			if(DB_NOTFOUND == ret)
    				*pRetCode = E_DB_CARD_N;
    			else
    				*pRetCode = E_DB_CARD_U;
    			goto L_RETU;
    		}
        }
        else
        {
            *pRetCode = E_NOTEXIST_TRANSCODE;
            DB_t_card_free_lock_by_cur();
    		goto L_RETU;
        }
        DB_t_card_free_lock_by_cur();
        return 0;
    L_RETU:
        return -1;
    */
    return 0;
}

