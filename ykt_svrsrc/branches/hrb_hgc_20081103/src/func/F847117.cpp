/* --------------------------------------------
 * 程序名称: F847117.sqc
 * 创建日期: Sep 29 2004
 * 程序作者: 耿刚
 * 版本信息: 1.0.0.0
 * 程序功能: 冻结卡
 * --------------------------------------------
 * 修改日期: 2004-11-29
 * 修改人员: 闻剑
 * 修改描述: 修改状态处理
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
	 
	 
static int do_froze_onecard(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int  ret = 0;
	int	card_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	char	oper[33+1] = "";
	int	cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	double dSerial_no = 0;
	char sCardState[5] = "";
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
    T_t_tif_meslist tMesList;

	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tMesList,0,sizeof(tMesList));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		return ret;
	}
	//	准备输入信息
	card_id = rPack->lvol1;												//卡标识
	cut_id = rPack->lvol0;												//客户号
	des2src(oper,rPack->scust_limit);									//操作员号
	maindevice_id = rPack->lvol6;											//上传工作站标识
	device_id = rPack->lvol7;												//采集设备标识

	//	检查客户信息，判断是否可以冻结
	ret = GetCardState(card_id,sCardState);
	if (ret)
	{
		writelog(LOG_ERR,"card_id[%d]",sCardState);
		return ret;
	}
	if('2'==sCardState[CARDSTAT_TYPE_REG])
	{
		ret = E_CARDNO_LOGOUT;
		return ret;
	}
	if(STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE])
	{
		ret = E_CARDNO_FREEZE;
		return ret;
	}
	//	修改卡状态为冻结
	ret = UpdateCardState(card_id,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		writelog(LOG_ERR,"SQLCODE=[%d]",ret);
		return ret;
	}

	ret=InsertToBlkList(card_id,ADD_BLACKLIST);
	if (ret)
	{
		writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
		return ret;
	}
	
	//广播黑名单
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
	AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//增删标志

	tMesList.funid = 930005;
	tMesList.level = 1;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		return ret;
	}
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//获得最大流水号
	if(ret)
	{
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		return ret;
	}
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.serial_no = D2I(dSerial_no);									//流水号
	tradeserial.serial_type = TXCODE_FREEZE_CARD;								//挂失
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//流水状态
	tradeserial.maindevice_id = maindevice_id;									//上传工作站标识
	tradeserial.device_id = device_id;											//采集设备标识
	tradeserial.card_id = card_id;												//交易卡号
	tradeserial.customer_id=cut_id;											//客户号
	des2src(tradeserial.oper_code,oper);
	//	插入交易流水表
	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			ret = E_DB_TRADESERIAL_E;
		else
			ret = E_DB_TRADESERIAL_I;
		return ret;
	}
	return 0;
}

static int do_fronze_by_stuempno(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int cust_id;
	int ret,count;
	T_t_pif_card card;
	int all_card_id[100];
	
	// 查询客户号
	ret = get_cut_id_by_stuemp_no(rPack->scust_no,&cust_id);
	if(ret)
	{
		writelog(LOG_ERR,"find cust_id by stuemp_no error, stuemp_no[%s]",rPack->scust_no);
		return ret;
	}
	//  处理所有卡
	ret = DB_t_pif_card_open_select_for_update_by_c5_and_cosumer_id(cust_id);
	if(ret)
	{
		writelog(LOG_ERR,"stuemp_no not exists [%s]",rPack->scust_no);
		if(DB_NOTFOUND == ret)
			return DB_NOTFOUND;
		return E_DB_CARD_R;
	}
	count = 0;
	while(1)
	{
		memset(&card,0,sizeof card);
		ret = DB_t_pif_card_fetch_select_by_c5(&card);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(count == 0)
					return DB_NOTFOUND;
				break;
			}
			return E_DB_CARD_R;
		}
		//writelog(LOG_ERR,"read stuemp_no[%s], card_id[%d],state[%s]",rPack->scust_no,card.card_id,card.state_id);
		if('2' == card.state_id[CARDSTAT_TYPE_REG] 
		 || STATE_TRUE == card.state_id[CARDSTAT_TYPE_FREEZE])
			continue; // 不用处理
			
		if(STATE_TRUE == card.state_id[CARDSTAT_TYPE_LOST])
		{
			// 已经挂失的卡，只需设置为冻结标志即可
			card.state_id[CARDSTAT_TYPE_FREEZE] = STATE_TRUE;
			ret = DB_t_pif_card_update_lock_by_c5(&card);
			if(ret)
			{
				return E_DB_CARD_U;
			}
			continue;
		}
		// 正常的卡需要冻结
		all_card_id[count] = card.card_id;
		count++;
	}
	// 其实从逻辑上来讲，应该只有一张这样的卡，不管了，统一处理
	for(;count>0;--count)
	{
		// 冻结卡
		rPack->lvol0 = cust_id;
		rPack->lvol1 = all_card_id[count-1];
		//writelog(LOG_ERR,"input card [%d]",all_card_id[count-1]);
		sleep(1);
		ret = do_froze_onecard(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)
		{
			return ret;
		}
	}
	return 0;
}

static int do_fronze_by_stuempno_ex(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	ret = do_fronze_by_stuempno(handle,iRequest,rPack,pRetCode,szMsg);
	if(ret)
	{
		writelog(LOG_ERR,"froze card error ,stuemp_no[%s],ret[%d]",rPack->scust_no,ret);
		if(db_rollback())
		{
			return E_DB_ROLLBACK;
		}
		return ret;
	}
	writelog(LOG_DEBUG,"froze card success , stuemp_no[%s] ",rPack->scust_no);
	return 0;
}
int F847117(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
  	if(strlen(rPack->scust_no)>0)
	{
		// 通过学号挂失
		ret = do_fronze_by_stuempno_ex(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)
		{
			*pRetCode =ret;
			return -1;
		}
		return 0;
	}
	else
	{
		// 原挂失方式
		ret = do_froze_onecard(handle,iRequest,rPack,pRetCode,szMsg);
		if(ret)
		{
			*pRetCode =ret;
			return -1;
		}
		return 0;
	}
}
