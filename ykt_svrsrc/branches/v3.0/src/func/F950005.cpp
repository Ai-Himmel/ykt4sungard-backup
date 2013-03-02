/* --------------------------------------------
 * 创建日期: 2007-4-29
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 下载前置机bcc 配置参数
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
#include "busqc.h"
#include "dbfunc_foo.h"
int F950005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret;
	int sysid = rPack->lcert_code;

	T_t_subsyspara  subsyspara;
	memset(&subsyspara,0,sizeof(subsyspara));

	ret=DB_t_subsyspara_read_by_sysid(sysid,&subsyspara);
	if(ret)
	{
		if(DB_NOTFOUND == ret)
			return E_DB_SUBSYSPARAMS_N;
		else
			return E_DB_SUBSYSPARAMS_R;
	}
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_SPHONE,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4,0);
	des2src(out_pack->sphone,subsyspara.bccdrtpip);
	out_pack->lvol0 = subsyspara.bccdrtpport;
	out_pack->lvol1 = subsyspara.bccdrtpno;
	out_pack->lvol2 = subsyspara.bccmainfuncno;
	out_pack->lvol3 = 0;
	out_pack->lvol4 = subsyspara.bccinterval;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}
