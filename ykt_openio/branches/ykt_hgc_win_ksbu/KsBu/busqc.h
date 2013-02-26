/***********************************************************************************
  ������־��¼
  ������: ������
  �������� 2004-2-7 15:36:16
  �汾: V1.00 
  ˵��: �����sqc������ص�ȫ�ֱ����ͺ�������
  2004-9-9 14:22:26 : Ϊ���ܹ�֧�ֶ����ݿ����Ӷ������޸ģ�
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
