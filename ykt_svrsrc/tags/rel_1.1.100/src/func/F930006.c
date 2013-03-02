/* --------------------------------------------
 * 程序名称: F930006.sqc
 * 创建日期: 9 17 2004
 * 程序作者: 杜叶飞
 * 版本信息: 1.0.0.0
 * 程序功能: 下传搭伙费比率
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

int F930006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	double dMaxFeeRatio=0;
//	int iMaxFeeRatio=0;
	int iRow=0;
       T_t_tif_meslist tMesList;
//	T_t_cif_cuttypefee tCuttypefee;

	memset(&tMesList,0,sizeof(tMesList));
//	memset(&tCuttypefee,0,sizeof(tCuttypefee));

	des2src(tMesList.devphy999_id, in_pack->sdate0);
	trim(tMesList.devphy999_id);
	if(strlen(tMesList.devphy999_id)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}
	tMesList.funid = iRequest;
	tMesList.level = 1;
/*
	ret=GetMaxFeeRatioFromShop(&dMaxFeeRatio);
	if(ret)
	{
		*pRetCode=ret;
		goto L_RETU;
	}
	iMaxFeeRatio=dMaxFeeRatio*100;
	ret=DB_t_cif_cuttypefee_open_select_by_c0();
	if(ret)
	{
		*pRetCode=E_DB_CUTTYPEFEE_R;
		goto L_RETU;
	}
	while(1)
	{
		memset(&tCuttypefee,0,sizeof(tCuttypefee));
		memset(&tMesList.incontent,0,sizeof(tMesList.incontent));
		ret=DB_t_cif_cuttypefee_fetch_select_by_c0(&tCuttypefee);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			{
				if(iRow)
					break;
				else
				{
					*pRetCode= E_DB_CUTTYPEFEE_N;
					goto L_RETU;
				}
			}
			else
			{
				*pRetCode= E_DB_CUTTYPEFEE_R;
				goto L_RETU;
			}
		}
		iRow++;
		AddXmlItemInt(tMesList.incontent, XML_KEY_CARDTYPE,tCuttypefee.cut_type);	//卡类型
		if(strncmp(tCuttypefee.is_outfee,TYPE_YES,1)==0)
			AddXmlItemInt(tMesList.incontent, XML_KEY_FEE, iMaxFeeRatio);
		else
			AddXmlItemInt(tMesList.incontent, XML_KEY_FEE, 0);

		ret=AddMsgLst(&tMesList);
		if(ret)
		{
			*pRetCode=ret;
			writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
			goto L_RETU;
		}
	}
*/
	AddXmlItemInt(tMesList.incontent, XML_KEY_CARDTYPE,in_pack->lvol5);	//卡类型
	AddXmlItemInt(tMesList.incontent, XML_KEY_FEE, in_pack->lvol6);		//费率
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	return 0;
L_RETU:
	return  -1;
}





