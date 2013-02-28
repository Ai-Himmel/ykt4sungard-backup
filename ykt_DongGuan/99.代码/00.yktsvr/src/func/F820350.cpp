/* --------------------------------------------
 * 创建日期: 2008-07-04
 * 程序作者: 闻剑
 * 版本信息: 1.0.0.0
 * 程序功能: 前台发送机器码
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
#include "acctrans.h"
#include "busqc.h"


int F820350(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	T_t_machinecode machinecode;
	memset(&machinecode,0,sizeof(machinecode));
	
	des2src(machinecode.machinecode,rPack->scard1);
	des2src(machinecode.ip,rPack->sphone);

	DB_t_machinecode_del_by_ip(machinecode.ip);
	DB_t_machinecode_del_by_machinecode(machinecode.machinecode);
	des2src(machinecode.lastsaved,CAccTrans::GetInst().hostdatetime);
	ret=DB_t_machinecode_add(&machinecode);
	if(ret)
	{
	  if(DB_REPEAT==ret)
		return E_DB_MACHINECODE_E;
	  else
		return E_DB_MACHINECODE_I;
	}
	T_t_site site;
	memset(&site,0,sizeof(site));
	ret=DB_t_site_read_by_ip(machinecode.ip,&site);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return 0;
		else return E_DB_SITE_R;
	}
	if(strlen(site.machinecode))
		return 0;
	else
	{
		des2src(site.machinecode,machinecode.machinecode);
		ret=DB_t_site_update_by_siteno(site.siteno,&site);
		if(ret)
		{
			if(DB_NOTFOUND==ret)
			  return E_DB_SITE_N;
			else
			  return E_DB_SITE_U;
		}
	}
	return 0;
}
