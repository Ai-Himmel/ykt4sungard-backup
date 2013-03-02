/* --------------------------------------------
 * 程序名称: F847119.sqc
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

int F847117(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
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
		*pRetCode=ret;
		goto L_RETU;
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
		*pRetCode = ret;
		goto L_RETU;
	}
	if('2'==sCardState[CARDSTAT_TYPE_REG])
	{
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	if(STATE_TRUE==sCardState[CARDSTAT_TYPE_FREEZE])
	{
		*pRetCode = E_CARDNO_FREEZE;
		goto L_RETU;
	}
	//	修改卡状态为冻结
	ret = UpdateCardState(card_id,CARDSTAT_TYPE_FREEZE,STATE_TRUE);
	if (ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"SQLCODE=[%d]",ret);
		goto L_RETU;
	}

	ret=InsertToBlkList(card_id,ADD_BLACKLIST);
	if (ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"InsertToBlkList err[%d]",ret);
		goto L_RETU;
	}
	
	//广播黑名单
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,card_id);
	//AddXmlItemStr(tMesList.incontent, XML_KEY_VERNUM, black_sheet.volume);
	AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,ADD_BLACKLIST);	//增删标志

	tMesList.funid = 930005;
	tMesList.level = 1;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	//	准备数据插入交易流水表
	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&dSerial_no);  					//获得最大流水号
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
			*pRetCode = E_DB_TRADESERIAL_E;
		else
			*pRetCode = E_DB_TRADESERIAL_I;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
