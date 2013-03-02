/***********************************************************************************
  ������־��¼
  ������: ������
  �������� 2004-2-7 15:36:16
  �汾: V1.00 
  ˵��: �����sqc������ص�ȫ�ֱ����ͺ�������
 ***********************************************************************************/
#ifndef _FDSQC_H
#define _FDSQC_H

#include "cpack.h"
#include "mypub.h"
#include "bupub.h"
#include "pubfunc.h"

#define  SC_OK       0
#define  SC_NOTFOUND 100  	// No data found 
#define	 SC_SEVERE_ERR	-10000	// <10000��Ϊ���ش���
#include <sqlca.h>
extern struct sqlca sqlca;	// ȫ��sqlca, ��fdsqc.sqc�ﶨ��

#ifdef __cplusplus
extern "C" {
#endif
//////////////////////////////////////////////////////////////////////
// Ŀǰֻ���ǵ�һ���ݿ�����

void SQLErrorHandler();
void SQLInitialize();
void SQLExit();

// ������: SQLConnectToServer
// ���  : ������ 2004-2-7 23:24:49
// ����  : ����g_SqlDB�ж����SQL���ݿ����Ӳ�������������
// ����  : long   0: ��ʾ���ӳɹ�������������ʧ�ܣ����g_SqlDB�е�SQL����ʧ����Ϣ
long SQLConnectToServer();
int  SQLIsConnectOK();
int  TestSQLConnect();
void SQLDisconnect();

#ifdef _IN_SQC_

#ifdef SQLSERVER
EXEC SQL WHENEVER SQLERROR CALL SQLErrorHandler();
#else
#define SQLERRD1	(sqlca.sqlerrd[1])
//#define SQLERRMC	(char*) (sqlca.sqlerrmc)
#endif

#define SQLSTATE (char *)(sqlca.sqlstate)

#endif

#ifdef __cplusplus
}
#endif

#endif
