/* --------------------------------------------
* 程序名称: F930117.c
* 创建日期: 2005-09-02
* 程序作者: 闻剑
* 版本信息: 1.0.0.0
* 程序功能:下传门禁名单
* --------------------------------------------
* 修改日期:
* 修改人员:
* 修改描述:
* 版本信息:
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
#include "dbfunc_foo.h"
#include "fdsqc.h"

int F930117(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	int ret = 0;
#if 0
	T_t_door_device_cardlist tCardlist;
	

	memset(&tCardlist,0,sizeof tCardlist);


	des2src(tCardlist.device_id, in_pack->sdate0);
	tCardlist.card_no = in_pack->lvol3;

	//AddXmlItemInt(tMesList.incontent,XML_KEY_FTFLAG,in_pack->lvol5);

	ret = process930117(&tCardlist,in_pack->lvol5);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
#endif
	return 0;
}

