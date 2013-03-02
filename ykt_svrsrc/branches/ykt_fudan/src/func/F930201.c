/* --------------------------------------------
 * 程序名称: F930201.sqc
 * 创建日期: 2005-11-22
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 通知计时宝需要下载名单
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


int F930201(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret;
	T_t_tif_meslist tMeslist;
	memset(&tMeslist,0,sizeof tMeslist);
	if(strlen(in_pack->sdate0) != 8)
	{
		return E_DEVPHYID_NULL;
	}
	tMeslist.funid = 930201;
	tMeslist.level = 2;
	tMeslist.max_send_cnt = 10;
	tMeslist.del_flag[0] = '0';
	AddXmlItemStr(tMeslist.incontent,XML_KEY_DEVPHY999_NO,in_pack->sdate0);
	des2src(tMeslist.devphy999_id,in_pack->sdate0);
	ret = DB_t_tif_meslist_del_by_devphy999_id_and_funid(tMeslist.devphy999_id,tMeslist.funid);
	if(ret)
	{
		if(ret != DB_NOTFOUND)
		{
			return E_DB_MESLIST_D;
		}
	}
	ret = AddMsgLst(&tMeslist);
	if(ret)
	{
		writelog(LOG_ERR,"add message list 930201 error!");
		return E_DB_MESLIST_I;
	}
	return 0;
}
