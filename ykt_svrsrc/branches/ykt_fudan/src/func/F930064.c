/* --------------------------------------------
 * 程序名称: F930064.sqc
 * 创建日期: 2005-3-16
 * 程序作者: 韩海东
 * 版本信息: 1.0.0.0
 * 程序功能: 获取lport指定端口的设备参数
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

int F930064(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
	int cnt=0;
	int mesid=0;
	char dev999_no[20]="";
     	T_t_tif_meslist tMesList;

	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);

	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);	
	SetCol(handle,F_SDATE0,F_SDATE2,F_SDATE3,F_LVOL3,F_VSVARSTR0,0);
	memset(&tMesList,0,sizeof(tMesList));

	des2src(tMesList.devphy999_id, in_pack->sdate0);
	trim(tMesList.devphy999_id);
	if(strlen(tMesList.devphy999_id)==0)
	{
		*pRetCode=E_DEVPHYID_NULL;
		goto L_RETU;
	}

	AddXmlItemInt(tMesList.incontent, XML_KEY_MAXTRADE, in_pack->lvol4);

	tMesList.funid = 930064;
	tMesList.level = 2;
	ret=AddMsgLst(&tMesList);
	if(ret)
	{
		*pRetCode=ret;
		writelog(LOG_ERR,"AddMsgLst err[%d]",ret);
		goto L_RETU;
	}
	if(iRequest!=tMesList.funid)
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

			ret=GetXmlValue(out_pack->sdate0,sizeof(out_pack->sdate0),XML_KEY_DEVPHY999_NO, tMesList.outcontent);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}			
			ret=GetXmlValue(dev999_no,sizeof(dev999_no),XML_KEY_DEV999_NO, tMesList.outcontent);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}	
			out_pack->lvol3=atoi(dev999_no);
			ret=GetXmlValue(out_pack->sdate2,sizeof(out_pack->sdate2),XML_KEY_DEV999_ID, tMesList.outcontent);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}			
			ret=GetXmlValue(out_pack->semp,sizeof(out_pack->semp),XML_KEY_DEVTYPE, tMesList.outcontent);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}						
			ret=GetXmlValue(out_pack->sdate3,sizeof(out_pack->sdate3),XML_KEY_DEVVERSION, tMesList.outcontent);
			if(ret)
			{
				*pRetCode=ret;
				goto L_RETU;
			}						
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
