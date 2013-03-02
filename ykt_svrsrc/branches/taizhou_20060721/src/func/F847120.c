/* --------------------------------------------
 * 程序名称: F847120.sqc
 * 创建日期: 2005-03-27
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 交易确认
 * --------------------------------------------
 * 修改日期:
 * 修改人员:
 * 修改描述:
 * 版本信息:
 * 备注信息:
 * --------------------------------------------*/
#define _IN_SQC_
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

int F847120(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int card_id=0;
	T_t_pif_card card;
	char comments[101] = "";
	char buf[64] = "";

	memset(&card,0,sizeof(card));

	card_id=rPack->lvol0;
	//判断卡状态是否为写卡未成功状态
	if(card_id<1)
	{
		*pRetCode= E_INPUT_CARDNO_CANNOT_NULL;
		goto L_RETU;
	}
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}

	switch(rPack->lserial0)
	{
		case 847119:
			if(STATE_FALSE==card.state_id[CARDSTAT_TYPE_WFAIL])
			{
				DB_t_pif_card_free_lock_by_cur();
				*pRetCode=E_CARDSTATE_NOTWRITEFAIL;
				goto L_RETU;
			}
			card.state_id[CARDSTAT_TYPE_WFAIL]=STATE_FALSE;	//修改状态
			// 如果有小钱包写卡失败
			if(CARDWFAIL_WATER == card.is_managefee[0])
			{
				/*
				ret = GetXmlValue(buf,sizeof buf,XML_KEY_TRADECODE2,card.comments);
				if(ret)
				{
					*pRetCode = ret;
					goto L_RETU;
				}
				AddXmlItemStr(comments,XML_KEY_TRADECODE2,buf);
				*/
				ret = GetXmlValue(buf,sizeof buf,XML_KEY_SERIALNO2,card.comments);
				if(ret)
				{
					*pRetCode = ret;
					goto L_RETU;
				}
				AddXmlItemStr(comments,XML_KEY_SERIALNO2,buf);

				ret = GetXmlValue(buf,sizeof buf,XML_KEY_OPERATEDATE2,card.comments);
				if(ret)
				{
					*pRetCode = ret;
					goto L_RETU;
				}
				AddXmlItemStr(comments,XML_KEY_OPERATEDATE2,buf);
				
				memset(card.comments,0,sizeof (card.comments));
				des2src(card.comments,comments);
				
			}
			else
				memset(card.comments,0,sizeof(card.comments));
			
			break;
		case 847123:
			if('3'!=card.state_id[CARDSTAT_TYPE_REG])
			{
				DB_t_pif_card_free_lock_by_cur();
				*pRetCode=E_CARD_STATE_NOT_CHANGE;
				goto L_RETU;
			}
			card.state_id[CARDSTAT_TYPE_REG]=STATE_TRUE;		//修改状态
			break;
		default:
			DB_t_pif_card_free_lock_by_cur();
			*pRetCode= E_TXCODE_NOT_EXIST;
			goto L_RETU;
	}
	ret=DB_t_pif_card_update_lock_by_cur(&card);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();

	return 0;
L_RETU:
	return -1;
}
