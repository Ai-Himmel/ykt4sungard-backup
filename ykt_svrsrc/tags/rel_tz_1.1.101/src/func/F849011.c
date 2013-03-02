/* --------------------------------------------
 * 程序名称: F849009.c
 * 创建日期: 2006-8-1
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 补写水控钱包确认
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

int F849011(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int card_id = 0;
	T_t_pif_card tCard;
	char buf[64] = "";
	char comments[101] = "";

	card_id = in_pack->lvol1;
	if(card_id <= 0 )
	{
		*pRetCode = E_INPUT_CARDNO_CANNOT_NULL;
		goto L_RETU;
	}

	ret = DB_t_pif_card_read_lock_by_cur_and_card_id(card_id,&tCard);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			*pRetCode = E_DB_CARD_N;
		else
			*pRetCode = E_DB_CARD_R;
		goto L_RETU;
	}

	if(TXCODE_WATER_REWRITE_CARD == in_pack->lvol2)
	{
		if(tCard.is_managefee[0] != CARDWFAIL_WATER)
		{
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode = E_CARDSTATE_NOTWRITEFAIL;
			goto L_RETU;
		}
		if(STATE_TRUE == tCard.state_id[CARDSTAT_TYPE_WFAIL])
		{
			ret = GetXmlValue(buf,sizeof buf,XML_KEY_TRADECODE,tCard.comments);
			if(ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			AddXmlItemStr(comments,XML_KEY_TRADECODE,buf);
			
			ret = GetXmlValue(buf,sizeof buf,XML_KEY_SERIALNO,tCard.comments);
			if(ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			AddXmlItemStr(comments,XML_KEY_SERIALNO,buf);

			ret = GetXmlValue(buf,sizeof buf,XML_KEY_OPERATEDATE,tCard.comments);
			if(ret)
			{
				*pRetCode = ret;
				goto L_RETU;
			}
			AddXmlItemStr(comments,XML_KEY_OPERATEDATE,buf);
			
			memset(tCard.comments,0,sizeof (tCard.comments));
			des2src(tCard.comments,comments);
			
		}
		else
		{
			memset(tCard.comments,0,sizeof tCard.comments);
		}
		tCard.is_managefee[0] = CARDWFAIL_NORMAL;
		ret = DB_t_pif_card_update_lock_by_cur(&tCard);
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
		*pRetCode = E_TXCODE_NOT_EXIST;
		DB_t_pif_card_free_lock_by_cur();
		goto L_RETU;
	}
	
	return 0;
L_RETU:
	return -1;
}

