/* --------------------------------------------
 * 创建日期: 2010-12-10
 * 程序作者: tc
 * 版本信息: 3.0.0.0
 * 程序功能: 加密机请求转发
 * --------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "transcode.h"
#include "dbfunc_foo.h"
#include "acctrans.h"
#include "busqc.h"
#include "svrlink.h"

extern CSvrLink *g_pSvrLink;
extern ST_CPACK *g_pRequestCpack;

static int g_encsvrbrancno=0;
static int g_encsvrmainfunc=0;


////////////////////////////////////////////////////////////////////////////////
int F1001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	ST_CPACK aPack;
	ST_PACK *out_pack = &(aPack.pack);
	T_t_frontcfg cfg;
	int ret;

	ResetNormalCPack(&aPack,0,1);

	// 拷贝原包数据
	memcpy(aPack.head.ParmBits,g_pRequestCpack->head.ParmBits,sizeof(aPack.head.ParmBits));
	memcpy(out_pack,rPack,sizeof(ST_PACK));

	if(g_encsvrmainfunc==0)
	{
		ret = DB_t_frontcfg_read_by_paraname("encsvr.branchno",&cfg);
		if(ret)
		{
			ERRTIP("加密机前置未配置");
			return E_COMMON_ERR;
		}
		g_encsvrbrancno = atoi(cfg.paraval);

		ret = DB_t_frontcfg_read_by_paraname("encsvr.mainfunc",&cfg);
		if(ret)
		{
			ERRTIP("加密机前置未配置");
			return E_COMMON_ERR;
		}
		g_encsvrmainfunc = atoi(cfg.paraval);	
	}
	switch(iRequest)
	{
	case 10001:
		aPack.head.RequestType=1001;
		break;
	case 10002:
		aPack.head.RequestType=1002;
		break;
	default:
		ERRTIP("请求功能号错误");
		return E_COMMON_ERR;
	}
	writelog(LOG_ERR,"transfer request,branch[%d]mainfunc[%d]requesttype[%d]",g_encsvrbrancno,g_encsvrmainfunc,
		aPack.head.RequestType);
	g_pSvrLink->ExtTransfer(g_encsvrbrancno,g_encsvrmainfunc,&aPack,NULL);
	return 0;
	
}
