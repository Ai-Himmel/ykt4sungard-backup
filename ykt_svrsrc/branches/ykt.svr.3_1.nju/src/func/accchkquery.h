/* --------------------------------------------
 * 创建日期: 2009-08-24
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 对账结果查询
 * --------------------------------------------*/
#ifndef ACC_CHKQUERY_H_
#define ACC_CHKQUERY_H_

#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "pubdb.h"
#include "pubdef.h"
#include "errdef.h"
#include "dbfunc.h"
#include "busqc.h"
#include "bupub.h"


// 圈存对账结果查询
int bankaccchkquery(TRUSERID *handle,ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg);
int mobileaccchkquery(TRUSERID *handle,ST_PACK *in_pack,ST_PACK *out_pack,int *pRetCode,char *szMsg);
#endif

