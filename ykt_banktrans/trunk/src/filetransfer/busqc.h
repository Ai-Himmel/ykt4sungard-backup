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
#include "bufunc.h"
#define  SC_OK       0
#define  SC_NOTFOUND 100  // No data found 

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

#endif
