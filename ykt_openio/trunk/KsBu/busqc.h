/***********************************************************************************
  编码日志记录
  编码者: 陈永华
  编码日期 2004-2-7 15:36:16
  版本: V1.00 
  说明: 与各个sqc程序相关的全局变量和函数定义
  2004-9-9 14:22:26 : 为了能够支持多数据库连接而作的修改，
 ***********************************************************************************/
#ifndef _GMSQC_H
#define _GMSQC_H

#include "cpack.h"
#include "mypub.h"
#include "bupub.h"
#include "cpack.h"

#define  SC_OK       0
#define  SC_NOTFOUND 100  // No data found 


#ifdef __cplusplus
extern "C" {
#endif
//////////////////////////////////////////////////////////////////////
// 目前只考虑单一数据库连接

void SQLErrorHandler();
void SQLInitialize();
void SQLExit();

// 函数名: SQLConnectToServer
// 编程  : 陈永华 2004-2-7 23:24:49
// 描述  : 根据g_SqlDB中定义的SQL数据库连接参数，建立连接
// 返回  : long   0: 表示连接成功；其他则连接失败，检查g_SqlDB中的SQL处理失败信息
long SQLConnectToServer();
int  SQLIsConnectOK();
void SQLDisconnect();

bool SQLIsConnected();
int SaveCPackData(ST_CPACK* rpack);

#ifdef _IN_SQC_
// install Embedded SQL for C error handler

/* ****** Updated by CHENYH at 2004-7-1 9:35:44 ****** 
EXEC SQL WHENEVER SQLERROR CALL SQLErrorHandler();

#define SQLSTATE (char *)(sqlca->sqlstate)
*/

#endif

#ifdef __cplusplus
}
#endif

#endif
