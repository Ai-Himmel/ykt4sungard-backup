/* --------------------------------------------
 * ��������: F847304.cpp
 * ��������: 2007-08-08
 * ��������: ����
 * �汾��Ϣ: 1.0.0.0
 * ������: ת��д��ʧ��
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
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
#include "fdsqc.h"

int F847304(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
    T_t_pif_card tCard;
    T_t_tif_writefailed tWriteFailed;
    T_t_tif_tradeserial tTradeSerial;
    char logicdate[11] = "";
    double dUniqNo = 0; 
    
    memset(&tCard, 0, sizeof tCard);
    memset(&tWriteFailed, 0, sizeof tWriteFailed);
	memset(&tTradeSerial, 0, sizeof(tTradeSerial));
	
    ret = DB_t_tif_tradeserial_read_by_serial_no(in_pack->lvol1, &tTradeSerial);  //������ˮ��
    if (ret)
    {
        writelog(LOG_DEBUG,"����Ų�����������ˮ��[%d]",in_pack->lvol1);
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
    
    ret = DB_t_pif_card_read_lock_by_cur_and_card_id(tTradeSerial.card_id, &tCard);
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

  	ret = DB_t_tif_writefailed_read_by_card_id_and_serial_no(tCard.card_id, tTradeSerial.serial_no, &tWriteFailed);
    if (ret)
    {
        if (DB_NOTFOUND != ret)
        {
            *pRetCode = E_DB_WRITEFAILED_R;
            goto L_RETU;
        }
    }
    else
    {
         if (CARDWFAIL_PACKET_DEAL_FLAG_Y == tWriteFailed.deal_flag[0])
            *pRetCode = E_WRITEFAILED_DEAL_FLAG_Y;
         else
            *pRetCode = E_WRITEFAILED_DEAL_FLAG_N;
         goto L_RETU; 
    }
    
    ret = getNewUniqNo(KEYTYPE_WRITEFAILED, &dUniqNo);              // ���д��ʧ�ܱ����ID��
    if (ret)
    {
        writelog(LOG_ERR,"ret[%d]",ret);
        *pRetCode = ret;
        DB_t_pif_card_free_lock_by_cur();
        goto L_RETU;
    }
    GetLogicDate(logicdate);
    tWriteFailed.card_id = tCard.card_id;
    des2src(tWriteFailed.tx_date,logicdate);
    tWriteFailed.id = D2I(dUniqNo);
    tWriteFailed.serial_no = tTradeSerial.serial_no;
    tWriteFailed.serial_type = tTradeSerial.serial_type;
    tWriteFailed.purese_no = tTradeSerial.purse_id;
    tWriteFailed.deal_flag[0] = CARDWFAIL_PACKET_DEAL_FLAG_Y;
    tWriteFailed.deal_bala = tTradeSerial.trade_fee;
//    des2src(tWriteFailed.comments, "��Ǯ��д��ʧ��");
	des2src(tWriteFailed.comments, in_pack->vsmess);			     // ע��д��ʧ��ԭ��		
    ret = DB_t_tif_writefailed_add(&tWriteFailed);
    if (ret)
    {
        *pRetCode = E_DB_WRITEFAILED_I;
        DB_t_pif_card_free_lock_by_cur();
        goto L_RETU;
    }
    
    tCard.state_id[CARDSTAT_TYPE_WFAIL] = STATE_TRUE;
    ret = DB_t_pif_card_update_lock_by_cur(&tCard);
    if (ret)
    {
        *pRetCode = E_DB_CARD_U;
         goto L_RETU;
    }
    DB_t_pif_card_free_lock_by_cur();

	return 0;
L_RETU:
	return -1;
}
