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
   // 由实际进程填写
   int iThisID;               // 本应用服务器的ID号， + BASEFUNCNO就是该应用服务器在通讯平台注册的私有服务功能号
   pid_t main_pid;            // 本应用服务器架构的系统进程号
   time_t main_start_time;    // 框架正式启动时间
   time_t main_stop_time;     // 框架退出时间
   int iBaseFuncNo;           // 该应用服务器类的基本通讯功能号

   int iRunningCode;             // 是否正在运行

   // 由ksbcc stop 进程填写，主控线程读取：
   bool exitcode;     // 系统控制退出码 当to stop:设置 SHM_EXITCODE

   // 由ksbcc show 进程填写，主控线程读取和擦除：
   bool bToShow; 
} shm_pubctrl;
extern shm_pubctrl *g_pubctrl;  // 共享内存头部指向公共控制数据块, 请自行在其他地方定义原始变量
#endif


typedef struct 
{
   unsigned int RequestType;  // 请求功能号
   char szRTName[80];         // 本功能业务名称
   char szProgrammer[20];     // 编程人员名
   int  iPriority;            // 优先级 目前分为1,2,3 自高到低
                              /* 同时也决定其处理的优先级
                                           1 - 交易类（会修改数据的请求）或 关键查询业务 ...
                                           2 - 单笔返回数据查询
                                           3 - 多笔返回数据查询
                              */
   bool bStoped;              // 是否暂时停止本业务
   unsigned int nSuccess;     // 处理成功次数
   unsigned int nFail;        // 处理失败次数
   double       dTakentime;   // 处理成功累计时间 以毫秒计，用于测试在本BCC下该业务的处理速度
   unsigned int nTt_max;      // 最大处理时间
   unsigned int nTt_min;      // 最小处理时间
} TBDefine;

extern TBDefine *g_BDefines;

int LoadBDefineFile(char *bdfile);

// 函数名: FindBPFunction
// 编程  : 陈永华 2004-2-11 22:50:46
// 描述  : 根据功能号，查询对应的功能表项
// 返回  : int <0:没有找到；>=0:在功能表中对应的序号
// 参数  : unsigned int reqtype ：功能号
int FindBPFunction(unsigned int reqtype);

// 函数名: ListBPFunctions
// 编程  : 陈永华 2004-2-11 22:41:18
// 描述  : 显示功能表中的统计或导出到文件中
// 返回  : int 登记的功能个数
// 参数  : char *bpfile ： NULL 或 “”则在屏幕上显示，否则导出到指定文件中
int ListBPFunctions(char *bpfile=NULL,int wmode=0);

typedef struct 
{
   bool g_bToExit;
   // 如下几个全局变量，是公共参考时间，供其他线程在时间不是很严格的时候直接读取
   int g_iToday; // 机器日期：YYYYMMDD
   int g_iHhmmss; // 机器时间：HHMMSS
   char g_szToday[12]; // "YYYYMMDD"
   char g_szHhmmss[12]; // "HH:MM:SS"

   // 系统配置：
   int  iThisID;  //定义本业务控制中心的ID，在通讯平台上注册特定功能号：APPPORT+ID
   int  iBaseFuncNo; // 本业务控制中心注册通讯的公共功能号
   int  nRouterCount;  // 连接的通讯平台个数
   int  iBULinkPort;   // 定义提供给BU（业务处理单元）的连接端口号
   int  nTimeout;      // 请求接收后多久没有被提取处理，则表示BU忙碌，取消本请求

   char szForwardPath[256];
   char szPushDbfPath[256];
   char szCfgFileName[256];  // 系统配置文件名
   char szBDefineFile[256];  // 功能配置定义文件名
} SYSGVARS;

extern SYSGVARS g_Vars;
extern CLogFile g_LogFile;
extern CKSLog g_KSLog;

bool LoadIniFile(char *inifile);

void SetDateTime();  // Set date/time into g_Vars variables...


// 函数名: getlastaccesstime
// 编程  : 陈永华 2004-3-1 12:59:32
// 描述  : 取指定文件的最后存取时间
// 返回  : time_t 
// 参数  : char *file
time_t getlastaccesstime(char *file);

bool UpdateCheckPath(char *path, char *defsub);

// 函数名: LoadFLogListFile
// 编程  : 陈永华 2004-3-16 14:51:21
// 描述  : 装载功能日志记录清单文件
// 返回  : int 
// 参数  : char *szFLLFile
int LoadFLogListFile(char *szFLLFile);

// 函数名: NeedToSaveLog
// 编程  : 陈永华 2004-3-16 16:19:36
// 描述  : 检查是否该功能需要记录到日志文件中
// 返回  : bool 
// 参数  : int reqno
bool NeedToSaveLog(int reqno);

#endif // !defined(AFX_SYSGVARS_H__B6044D10_9D38_4884_A57F_196A969FD4CF__INCLUDED_)
