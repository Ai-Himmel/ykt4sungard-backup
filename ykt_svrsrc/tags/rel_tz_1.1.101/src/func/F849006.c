/* --------------------------------------------
 * 程序名称: F849006.c
 * 创建日期: 2006-7-31
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 水控写卡失败更新卡状态
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
#include "fdsqc.h"

int F849006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	T_t_pif_card tCard;
	T_t_tif_tradeserial tTradeSerial;
	char logcaldate[11] = "";

	memset(&tTradeSerial,0,sizeof tTradeSerial);
	memset(&tCard,0,sizeof tCard);

	if(  in_pack->lvol3 != 0 && in_pack->lvol3 != 1)
	{
		*pRetCode = E_INPUT_ERROR;
		goto L_RETU;
	}
	ret = DB_t_tif_tradeserial_read_by_serial_no(in_pack->lvol1,&tTradeSerial);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_TRADESERIAL_N;
		else
			*pRetCode = E_DB_TRADESERIAL_R;
		goto L_RETU;
	}

	ret = DB_t_pif_card_read_lock_by_cur_and_card_id(tTradeSerial.card_id,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_CARD_N;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}

	GetLogicDate(logcaldate);
	AddXmlItemStr(tCard.comments,XML_KEY_OPERATEDATE2,logcaldate);
	AddXmlItemInt(tCard.comments,XML_KEY_SERIALNO2,in_pack->lvol2);

	// 大钱包写卡失败
	if(0 == in_pack->lvol3 )
	{
		// 大钱包写失败
		AddXmlItemInt(tCard.comments,XML_KEY_SERIALNO,in_pack->lvol1);
		AddXmlItemStr(tCard.comments,XML_KEY_OPERATEDATE,logcaldate);
		AddXmlItemInt(tCard.comments,XML_KEY_TRADECODE,tTradeSerial.serial_type);
		tCard.state_id[CARDSTAT_TYPE_WFAIL]=STATE_TRUE;
	}
	else
		tCard.state_id[CARDSTAT_TYPE_WFAIL]=STATE_FALSE;
	
	tCard.is_managefee[0] = CARDWFAIL_WATER;
	
	ret = DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		*pRetCode = E_DB_CARD_U;
		goto L_RETU;
	}
	
	DB_t_pif_card_free_lock_by_cur();
	
	return 0;
L_RETU:
	return -1;
}

