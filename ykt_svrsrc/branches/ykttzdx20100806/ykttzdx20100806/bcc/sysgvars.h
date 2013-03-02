// sysgvars.h: interface for the SYSGVARS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSGVARS_H__B6044D10_9D38_4884_A57F_196A969FD4CF__INCLUDED_)
#define AFX_SYSGVARS_H__B6044D10_9D38_4884_A57F_196A969FD4CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "comstru.h"
#include "logfile.h"
#include "KSLog.h"

#ifndef WIN32
#define RUNNINGCODE  20040326
typedef struct
{
   // ��ʵ�ʽ�����д
   int iThisID;               // ��Ӧ�÷�������ID�ţ� + BASEFUNCNO���Ǹ�Ӧ�÷�������ͨѶƽ̨ע���˽�з����ܺ�
   pid_t main_pid;            // ��Ӧ�÷������ܹ���ϵͳ���̺�
   time_t main_start_time;    // �����ʽ����ʱ��
   time_t main_stop_time;     // ����˳�ʱ��
   int iBaseFuncNo;           // ��Ӧ�÷�������Ļ���ͨѶ���ܺ�

   int iRunningCode;             // �Ƿ���������

   // ��ksbcc stop ������д�������̶߳�ȡ��
   bool exitcode;     // ϵͳ�����˳��� ��to stop:���� SHM_EXITCODE

   // ��ksbcc show ������д�������̶߳�ȡ�Ͳ�����
   bool bToShow; 
} shm_pubctrl;
extern shm_pubctrl *g_pubctrl;  // �����ڴ�ͷ��ָ�򹫹��������ݿ�, �������������ط�����ԭʼ����
#endif


typedef struct 
{
   unsigned int RequestType;  // �����ܺ�
   char szRTName[80];         // ������ҵ������
   char szProgrammer[20];     // �����Ա��
   int  iPriority;            // ���ȼ� Ŀǰ��Ϊ1,2,3 �Ըߵ���
                              /* ͬʱҲ�����䴦������ȼ�
                                           1 - �����ࣨ���޸����ݵ����󣩻� �ؼ���ѯҵ�� ...
                                           2 - ���ʷ������ݲ�ѯ
                                           3 - ��ʷ������ݲ�ѯ
                              */
   bool bStoped;              // �Ƿ���ʱֹͣ��ҵ��
   unsigned int nSuccess;     // ����ɹ�����
   unsigned int nFail;        // ����ʧ�ܴ���
   double       dTakentime;   // ����ɹ��ۼ�ʱ�� �Ժ���ƣ����ڲ����ڱ�BCC�¸�ҵ��Ĵ����ٶ�
   unsigned int nTt_max;      // �����ʱ��
   unsigned int nTt_min;      // ��С����ʱ��
} TBDefine;

extern TBDefine *g_BDefines;

int LoadBDefineFile(char *bdfile);

// ������: FindBPFunction
// ���  : ������ 2004-2-11 22:50:46
// ����  : ���ݹ��ܺţ���ѯ��Ӧ�Ĺ��ܱ���
// ����  : int <0:û���ҵ���>=0:�ڹ��ܱ��ж�Ӧ�����
// ����  : unsigned int reqtype �����ܺ�
int FindBPFunction(unsigned int reqtype);

// ������: ListBPFunctions
// ���  : ������ 2004-2-11 22:41:18
// ����  : ��ʾ���ܱ��е�ͳ�ƻ򵼳����ļ���
// ����  : int �ǼǵĹ��ܸ���
// ����  : char *bpfile �� NULL �� ����������Ļ����ʾ�����򵼳���ָ���ļ���
int ListBPFunctions(char *bpfile=NULL,int wmode=0);

typedef struct 
{
   bool g_bToExit;
   // ���¼���ȫ�ֱ������ǹ����ο�ʱ�䣬�������߳���ʱ�䲻�Ǻ��ϸ��ʱ��ֱ�Ӷ�ȡ
   int g_iToday; // �������ڣ�YYYYMMDD
   int g_iHhmmss; // ����ʱ�䣺HHMMSS
   char g_szToday[12]; // "YYYYMMDD"
   char g_szHhmmss[12]; // "HH:MM:SS"

   // ϵͳ���ã�
   int  iThisID;  //���屾ҵ��������ĵ�ID����ͨѶƽ̨��ע���ض����ܺţ�APPPORT+ID
   int  iBaseFuncNo; // ��ҵ���������ע��ͨѶ�Ĺ������ܺ�
   int  nRouterCount;  // ���ӵ�ͨѶƽ̨����
   int  iBULinkPort;   // �����ṩ��BU��ҵ����Ԫ�������Ӷ˿ں�
   int  nTimeout;      // ������պ���û�б���ȡ�������ʾBUæµ��ȡ��������

   char szForwardPath[256];
   char szPushDbfPath[256];
   char szCfgFileName[256];  // ϵͳ�����ļ���
   char szBDefineFile[256];  // �������ö����ļ���
} SYSGVARS;

extern SYSGVARS g_Vars;
extern CLogFile g_LogFile;
extern CKSLog g_KSLog;

bool LoadIniFile(char *inifile);

void SetDateTime();  // Set date/time into g_Vars variables...


// ������: getlastaccesstime
// ���  : ������ 2004-3-1 12:59:32
// ����  : ȡָ���ļ�������ȡʱ��
// ����  : time_t 
// ����  : char *file
time_t getlastaccesstime(char *file);

bool UpdateCheckPath(char *path, char *defsub);

// ������: LoadFLogListFile
// ���  : ������ 2004-3-16 14:51:21
// ����  : װ�ع�����־��¼�嵥�ļ�
// ����  : int 
// ����  : char *szFLLFile
int LoadFLogListFile(char *szFLLFile);

// ������: NeedToSaveLog
// ���  : ������ 2004-3-16 16:19:36
// ����  : ����Ƿ�ù�����Ҫ��¼����־�ļ���
// ����  : bool 
// ����  : int reqno
bool NeedToSaveLog(int reqno);

#endif // !defined(AFX_SYSGVARS_H__B6044D10_9D38_4884_A57F_196A969FD4CF__INCLUDED_)
