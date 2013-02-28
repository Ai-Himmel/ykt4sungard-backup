/* --------------------------------------------
 * 程序名称: F930031.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能:   采集自助挂失\解挂流水
 * --------------------------------------------*/
#define _IN_SQC_
#include <string.h>
#include <stdio.h>
#include "pubdef.h"
#include "errdef.h"
#include "busqc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "pubfunc.h"

int F930032(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;						//返回码
	int hi_sign = 0;					//挂失解挂标志
	double h_temp_Serial_no = 0;		//本地流水号
	char logicdate[11]="";
	char sysdate[11]="";
	char systime[9]="";
	int dev_id=0;
	T_t_tif_tradeserial  tradeserial;

	memset(&tradeserial,0,sizeof(tradeserial));
	hi_sign = in_pack->lvol6;												//挂失解挂标志

	ret=chk_dyn_key(in_pack->lcert_code,in_pack->scust_limit2);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	getsysdate(sysdate);
	getsystime(systime);
	ret=GetLogicDate(logicdate);												//业务日期
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	switch (hi_sign)
	{
		case 0:
			tradeserial.serial_type = TXCODE_CARD_LOSS;					//挂失
			break;
		case 1:
			tradeserial.serial_type = TXCODE_CARD_COMEBACK_LOSS;			//解挂
			break;
		case 2:
			tradeserial.serial_type = TXCODE_MODIFICATIONPW;				//修改密码
			break;
		default:
			*pRetCode = -1;
			writelog(LOG_ERR,"挂失解挂修改密码标志出错。ERRCODE[%d] ",*pRetCode);
			goto L_RETU;
			break;
	}
	/*	读取设备ID	*/
	ret = GetDevIdByDevPhyId(&dev_id,in_pack->sdate1);	
	if (ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"GetDevIdByDevPhyId err[%d] ",ret);
		goto L_RETU;
	}	
	
	tradeserial.serial_state = SERISTAT_NODEBT;								//流水状态

	ret = getNewUniqNo(KEYTYPE_TRADESERIAL,&h_temp_Serial_no);  			
	if(ret)
	{
		*pRetCode = ret;
		writelog(LOG_ERR,"获取最大流水号错误: ERRCODE = [%d]",ret);
		goto L_RETU;
	}
	tradeserial.serial_no = D2I(h_temp_Serial_no);													//流水号

 	snprintf(tradeserial.operate_date,9,"20%s",in_pack->spost_code);		//发生日期(格式化输入的日期)
	des2src(tradeserial.operate_time,in_pack->spost_code2);			//发生时间(格式化输入的时间)
	des2src(tradeserial.collect_date,sysdate);												//采集日期
	des2src(tradeserial.collect_time,systime);												//采集时间
	des2src(tradeserial.enteract_date,logicdate);											//处理日期
	des2src(tradeserial.enteract_time,systime);											//处理时间
	tradeserial.other_seri_no = in_pack->lvol4;													//上传端流水号
	tradeserial.serial_state = SERISTAT_DEBT;													//流水状态
	tradeserial.maindeviceid = in_pack->lcert_code;												//上传工作站标识
	tradeserial.deviceid = dev_id;														//采集设备标识
	tradeserial.cardno = in_pack->lvol5;														//卡号
	Strncpy_t(tradeserial.showid,in_pack->sstation0,sizeof(tradeserial.showid));						//显示卡号
	Strncpy_t(tradeserial.oldpwd,in_pack->sstock_code,sizeof(tradeserial.oldpwd));					//原始密码
	Strncpy_t(tradeserial.newpwd,in_pack->sstock_code2,sizeof(tradeserial.newpwd));				//更新密码
	des2src(tradeserial.opercode,"system");
	
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
