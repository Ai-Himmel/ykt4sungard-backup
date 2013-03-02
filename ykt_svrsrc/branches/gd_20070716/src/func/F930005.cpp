/* --------------------------------------------
 * 程序名称: F930005.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能:  广播黑名单下传
 * --------------------------------------------
 * 修改日期:2004-12-14
 * 修改人员:	闻剑
 * 修改描述: 修改业务逻辑
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

int F930005(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int cnt=0;
	int mesid=0;
	char sCardState[5]="";
       T_t_tif_meslist tMesList;
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_VSVARSTR0,0);

	memset(&tMesList,0,sizeof(tMesList));

//	des2src(tMesList.devphy999_id, in_pack->sdate0);

	ret=GetCardState(in_pack->lvol0,sCardState);
	if (ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	if('2'==sCardState[CARDSTAT_TYPE_REG])
	{
		*pRetCode = E_CARDNO_LOGOUT;
		goto L_RETU;
	}
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDID,in_pack->lvol0);
	AddXmlItemStr(tMesList.incontent, XML_KEY_VERNUM, in_pack->sserial0);
	AddXmlItemInt(tMesList.incontent, XML_KEY_ADDDELSIGN,in_pack->lvol4);	//增删标志

	tMesList.funid = 930005;
	tMesList.pfunid = 930003;
	tMesList.level = MESLIST_PRIORITY_REALTIME;
	tMesList.msgtype = MESLIST_TYPE_ORDER;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	if(iRequest!=930005)
		return 0;
	ret=db_commit();
	if(ret)
	{
		writelog(LOG_ERR,"db_commit ret[%d]",ret);
		*pRetCode=E_DB_COMMIT;
		goto  L_RETU;
	}
	mesid=tMesList.mesid;
	des2src(out_pack->sdate0,in_pack->sdate0);
	for(cnt=0;(cnt<10)&&(tMesList.ecode!=0);cnt++)
	{
		sleep(1);
		memset(&tMesList,0,sizeof(tMesList));
		ret=DB_t_tif_meslist_read_by_mesid(mesid, &tMesList);
		if(ret)
		{
			writelog(LOG_ERR,"DB_t_tif_meslist_read_by_mesid err[%d]",ret);
			*pRetCode=E_DB_MESLIST_R;
			goto L_RETU;
		}
	}
	switch(tMesList.ecode)
	{
		case 0:		//成功
			des2src(out_pack->vsvarstr0,"成功");
			break;
		case 9999:		//交易未处理
			des2src(out_pack->vsvarstr0,"前置机无应答");
			break;
		default:			//交易已经处理,但结果是失败
			des2src(out_pack->vsvarstr0,tMesList.emsg);
			break;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);

	return 0;
L_RETU:
	return  -1;
}





