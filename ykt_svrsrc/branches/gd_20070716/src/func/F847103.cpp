/* --------------------------------------------
 * 程序名称: F47103.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能: 解挂卡
 * --------------------------------------------
 * 修改日期:2004-11-29
 * 修改人员:	闻剑
 * 修改描述: 修改业务逻辑、状态处理
 * 版本信息:1.0.0.1
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
#include "fdsqc.h"

static int SaveCancelLossSerial(T_t_tif_tradeserial  *pTradeserial)
{
	int ret;
	
	//	插入卡操作流水表
	ret = DB_t_tif_tradeserial_add(pTradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret [%d]",ret);
		if(DB_REPEAT==ret)
			return E_DB_TRADESERIAL_E;
		else
			return E_DB_TRADESERIAL_I;
	}
	return ret;
}
int F847103(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
  	int ret = 0;
	int	hi_cardid = 0;
	char	hi_Operator[33+1] = "";
	int	hi_Cut_id  = 0;
	int	hi_maindevice_id = 0;
	int	hi_device_id = 0;
	double	h_temp_Serial_no = 0;
	char  logicdate[11]="";
	char sysdate[11]="";
	char systime[8]="";
	char dbdate[9]="";
	char dbtime[7]="";
	char volume[13]="";

	T_t_tif_tradeserial tradeserial;
	T_t_pif_card		tCard;
       T_t_tif_meslist tMesList;
	T_t_pif_device		t_device;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);		//用于根据请求包整理本CPACK包的头清空包头位图和包体中的数据

	memset(&t_device,0,sizeof(t_device));
	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&tCard,0,sizeof(tCard));
	memset(&tMesList,0,sizeof(tMesList));

	hi_cardid = rPack->lvol1;													//卡标识
	hi_Cut_id = rPack->lvol2;													//客户号
	des2src(hi_Operator,rPack->scust_limit);										//操作员号
	hi_maindevice_id = rPack->lvol6;											//上传工作站标识
	hi_device_id = rPack->lvol7;												//采集设备标识
	if(hi_maindevice_id==0&&hi_device_id!=0) 
	{
		DB_t_pif_device_read_by_device_id(hi_device_id, &t_device);
		hi_maindevice_id=t_device.subsystem_id;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	//	检查卡状态是否为挂失
	ret = DB_t_pif_card_read_lock_by_cur_and_card_id(hi_cardid,&tCard);
	if (ret)
	{
		writelog(LOG_ERR,"card_id[%d]",hi_cardid);
		if(DB_NOTFOUND==ret)
			*pRetCode = E_CARDNO_NOT_EXIST;
		else
			*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	hi_Cut_id=tCard.cosumer_id;
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();	
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if('1'==tCard.state_id[CARDSTAT_TYPE_FREEZE])
	{
		DB_t_pif_card_free_lock_by_cur();	
		*pRetCode = E_CARDNO_FREEZE;
		goto L_RETU;
	}

	tCard.state_id[CARDSTAT_TYPE_LOST]=STATE_FALSE;
	strcpy(tCard.lost_date,"");	
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",hi_cardid);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_U;
		goto L_RETU;
	}
	DB_t_pif_card_free_lock_by_cur();
	
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&h_temp_Serial_no);  					//获得最大流水号
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	des2src(tradeserial.operate_date,sysdate);											//发生日期
	des2src(tradeserial.operate_time,systime);											//发生时间
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.serial_no = D2I(h_temp_Serial_no);											//流水号
	tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;								//解挂
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;								//流水状态
	tradeserial.maindevice_id = hi_maindevice_id;									//上传工作站标识
	tradeserial.device_id = hi_device_id;											//采集设备标识
	tradeserial.card_id = hi_cardid;													//交易卡号
	tradeserial.customer_id = hi_Cut_id;
	des2src(tradeserial.oper_code, hi_Operator);
	
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_LOST])
	{
		//允许重复解挂
		//再下传白名单
		//	插入黑名单表
		ret=InsertToBlkList(hi_cardid,DELETE_BLACKLIST);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
			goto L_RETU;
		}
		
			
		//广播黑名单
		/*
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,hi_cardid);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,DELETE_BLACKLIST);	//增删标志
		tMesList.funid = 930005;
		tMesList.pfunid = 930003;
		tMesList.max_send_cnt = 10;
		tMesList.level = MESLIST_PRIORITY_REALTIME;
		tMesList.msgtype = MESLIST_TYPE_ORDER;
		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
		*/
		ret = SaveCancelLossSerial(&tradeserial);
		if(ret)
		{
			*pRetCode = ret;
			writelog(LOG_ERR,"ret [%d]",ret);
			goto L_RETU;
		}
		ret=GetCardMaxBlkVerNo(hi_cardid,volume);
		if(ret)
		{
			*pRetCode = ret;
			goto L_RETU;
		}
		SetCol(handle,0);
		SetCol(handle,F_SSERIAL0,0);
		des2src(out_pack->sserial0,volume);		//卡版本号
		//writelog(LOG_ERR,"volume:[%s]",volume);
		PutRow(handle,out_pack,pRetCode,szMsg);
		
		return 0;
	}
	
	ret=IsExistNoLostCardByCustomId(hi_Cut_id);
	if(ret)
	{
		if(E_NORMALCARD_NOLOST==ret)
		{
			*pRetCode = E_BACK_CARD_FOR_NORCARD2;
		}
		else if( E_TEMPCARD_NOLOST==ret)
		{
			//如果存在正常使用的临时卡，则提示请退掉此卡，不能解挂
			if(tCard.type_id==CT_NORMAL)
				*pRetCode =E_BACK_CARD_FOR_NORCARD;
			else
				*pRetCode =E_BACK_CARD_FOR_TMPCARD;
		}
		else
		{
			*pRetCode = ret;
		}
		goto L_RETU;
	}
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//插入黑名单表
		ret=InsertToBlkList(hi_cardid,DELETE_BLACKLIST);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
			goto L_RETU;
		}
		//广播黑名单
//			AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,hi_cardid);
//			AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,DELETE_BLACKLIST);	//增删标志
//	
//			tMesList.funid = 930005;
//			tMesList.pfunid = 930003;
//			tMesList.max_send_cnt = 10;
//			tMesList.level = MESLIST_PRIORITY_REALTIME;
//			tMesList.msgtype = MESLIST_TYPE_ORDER;
//			ret=AddMsgLst(&tMesList);
//			if(ret)
//			{
//				*pRetCode=ret;
//				writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
//				goto L_RETU;
//			}
	}
	//	修改卡状态为解挂状态
//		ret = UpdateCardState(hi_cardid,CARDSTAT_TYPE_LOST,STATE_FALSE);
//		if (ret)
//		{
//			*pRetCode = ret;
//			goto L_RETU;
//		}
	//	准备数据插入交易流水表
	/////////////////
	ret = SaveCancelLossSerial(&tradeserial);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	ret=GetCardMaxBlkVerNo(hi_cardid,volume);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	SetCol(handle,0);
	SetCol(handle,F_SSERIAL0,0);
	des2src(out_pack->sserial0,volume);		//卡版本号
//	writelog(LOG_DEBUG,"volume:[%s]",volume);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

