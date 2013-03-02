/* --------------------------------------------
 * 创建日期: 2009-01-06
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能:  挂失卡
 * --------------------------------------------
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
#include "acctrans.h"
int F846307(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg);
int F847102(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	ST_PACK sPack;
	memset(&sPack,0,sizeof(sPack));
    sPack.sstatus1[0]='1';
   	sPack.lwithdraw_flag=2;
  	sPack.lvol0=rPack->lvol1;
	int ret=F846307(handle,iRequest,&sPack,pRetCode,szMsg);
	return ret;
}
