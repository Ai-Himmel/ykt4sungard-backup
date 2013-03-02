/* --------------------------------------------
 * 程序名称: F847102.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:  挂失卡
 * --------------------------------------------
 * 修改日期:2004-11-29
 * 修改人员:	闻剑
 * 修改描述: 修改状态处理
 * 版本信息:1.0.0.1
 * 备注信息:
 * --------------------------------------------
 * 修改日期:2004-11-29
 * 修改人员:	韩海东
 * 修改描述: 增加根据学工号或者客户号进行挂失
 			为了实现圈存终端或者多媒体等的挂失申请
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

int F847102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
  	int ret = 0;
//	char logicdate[11] = "";
//	char enddate[10 + 1] = "";
	int	card_id = 0;
	char	Operator[33+1] = "";
	char badcard_status[2]="";
//	int	Cut_id  = 0;
	int	maindevice_id = 0;
	int	device_id = 0;
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	double	dUniqno = 0;
	char stuemp_no[20+1]="";
	int	cut_id=0;
	T_t_pif_cardlossinfo cardlossinfo;
	T_t_tif_black_sheet black_sheet;
	T_t_tif_tradeserial  tradeserial;
       T_t_tif_meslist tMesList;
	T_t_pif_card	tCard;

	memset(&tradeserial,0,sizeof(tradeserial));
	memset(&cardlossinfo,0,sizeof(cardlossinfo));
	memset(&black_sheet,0,sizeof(black_sheet));
	memset(&tMesList,0,sizeof(tMesList));
	memset(&tCard,0,sizeof(tCard));

	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);								//业务日期
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	card_id = rPack->lvol1;													//卡标识
//	Cut_id = rPack->lvol0;													//客户号
	des2src(Operator,rPack->scust_limit);									//操作员号
	maindevice_id = rPack->lvol6;											//上传工作站标识
	device_id = rPack->lvol7;												//采集设备标识
	cut_id=rPack->lvol8;
	des2src(stuemp_no,rPack->scust_auth);
	if(0==card_id)
	{
		if(0==cut_id)
		{
			ret=get_tradecard_no_by_stupid(stuemp_no,&card_id);			//卡标识
			if(ret)
			{
				if(100==ret)
				{
					writelog(LOG_ERR,"get_tradecard_no_by_stupid have no recode,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHACC_NOEXIT;
					goto L_RETU;
				}
				if(-811==ret)
				{
					writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHCARD_TWICE;
					goto L_RETU;
				}
				writelog(LOG_ERR,"get_tradecard_no_by_stupid error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
		}
		else if(strlen(stuemp_no)!=0)
		{
			ret=GetLostCardIdByCustomId(cut_id, &card_id);
			if(ret)
			{
				if(100==ret)
				{
					writelog(LOG_ERR,"GetLostCardIdByCustomId have no recode,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHACC_NOEXIT;
					goto L_RETU;
				}
				if(-811==ret)
				{
					writelog(LOG_ERR,"This customer have more than one card,errcode=[%d]",ret);
					*pRetCode=E_TRANS_SCHCARD_TWICE;
					goto L_RETU;
				}
				writelog(LOG_ERR,"GetLostCardIdByCustomId error,errcode=[%d]",ret);
				*pRetCode=E_DB_CARD_R;
				goto L_RETU;
			}
		}
	}
	
	//检查客户信息，判断是否可以挂失
	//修改卡标志，置为正常状态
	ret=DB_t_pif_card_read_lock_by_cur_and_card_id(card_id, &tCard);
	if(ret)
	{
		writelog(LOG_ERR,"card_id[%d]",card_id);
		if(DB_NOTFOUND==ret)
			*pRetCode= E_CARDNO_NOT_EXIST;
		else
			*pRetCode= E_DB_CARD_R;
		goto L_RETU;
	}
	if(card_id!=tCard.card_id)
	{
		DB_t_pif_card_free_lock_by_cur();
		writelog(LOG_ERR,"card_id[%d] db card_id[%d]",card_id,tCard.card_id);
		*pRetCode=E_DB_CARD_R;
		goto L_RETU;
	}
	if('2'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if('3'==tCard.state_id[CARDSTAT_TYPE_REG])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_WFAIL;
		goto L_RETU;
	}	
	if(STATE_TRUE==tCard.state_id[CARDSTAT_TYPE_LOST])
	{
		DB_t_pif_card_free_lock_by_cur();
		*pRetCode = E_CARDNO_LOST;
		goto L_RETU;
	}
	//	修改卡状态为挂失
	tCard.state_id[CARDSTAT_TYPE_LOST]=STATE_TRUE;
	//坏卡状态
	if(rPack->lvol2==1)
		tCard.bad_status[0]='1';
	ret=DB_t_pif_card_update_lock_by_cur(&tCard);
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

	//	插入卡挂失有效期限表
/*
	ret=GetLostCardValiddate(sysdate,enddate);											//获得挂失有效期限
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	cardlossinfo.card_id = card_id;													//卡号
	des2src(cardlossinfo.begin_date,sysdate);											//起始日期
	des2src(cardlossinfo.end_date,enddate);											//截至日期
	des2src(cardlossinfo.operate_date,sysdate);										//操作日期
	des2src(cardlossinfo.operate_time,systime);										//操作时间
	cardlossinfo.state_id=STATE_VALID;												//有效
	ret = DB_t_pif_cardlossinfo_add(&cardlossinfo);
	if (ret)
	{
		*pRetCode = E_DB_CARDLOSSINFO_I;
		writelog(LOG_ERR,"errcode[%d] ",ret);
		goto L_RETU;
	}
*/
	//如果该卡号被冻结,则挂失时对黑名单不处理
	if(STATE_FALSE==tCard.state_id[CARDSTAT_TYPE_FREEZE])
	{
		//	插入黑名单表
		ret=DB_t_tif_black_sheet_del_by_card_id_and_is_ad(tCard.card_id,DELETE_BLACKLIST);
		if(ret)
		{
			if(ret!=DB_NOTFOUND)
			{
				*pRetCode=ret;
				goto L_RETU;
			}
		}
		ret=InsertToBlkList(tCard.card_id,ADD_BLACKLIST);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
			goto L_RETU;
		}
		//广播黑名单
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
		AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//增删标志

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
	}
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dUniqno);  					//获得最大流水号
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
	tradeserial.serial_no = D2I(dUniqno);										//流水号
	tradeserial.serial_type = TXCODE_CARD_LOSS;								//挂失
	tradeserial.serial_state = SERISTAT_NONEEDDEBT;							//流水状态
	tradeserial.maindevice_id = maindevice_id;									//上传工作站标识
	tradeserial.device_id = device_id;											//采集设备标识
	tradeserial.card_id = card_id;											//交易卡号
	tradeserial.customer_id=tCard.cosumer_id;									//客户号
	des2src(tradeserial.oper_code,Operator);

	ret = DB_t_tif_tradeserial_add(&tradeserial);
	if (ret)
	{
		writelog(LOG_ERR,"ret[%d]",ret);
		if(DB_REPEAT==ret)
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
