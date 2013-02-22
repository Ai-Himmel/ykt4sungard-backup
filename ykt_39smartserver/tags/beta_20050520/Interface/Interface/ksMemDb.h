#ifndef __KSMEMDB_H
#define __KSMEMDB_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSMEMDB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSMEMDB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef KSMEMDB_EXPORTS
#define KSMEMDB_API __declspec(dllexport)
#else
#define KSMEMDB_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksMemDbd.lib")
#pragma message("automatic link ksMemDbd.dll")
#else
#pragma comment(lib,"../lib/ksMemDb.lib")
#pragma message("automatic link ksMemDb.dll")
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif
//功能：
//初始化，打开或者创建内存数据库
//参数说明：
//szDbName[输入]：内存数据库名字
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_Init(char *szDbName,char *szMsg);

//功能：
//关闭内存数据库，释放资源
//返回值：
//无
void KSMEMDB_API WINAPI KSMEMDB_Free();

//功能：
//表加锁
//参数说明：
//szTableName[输入]：表名
//nTimeOut[输入]：超时时间（毫秒），如果为0，则阻塞
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_LockTable(char *szTableName, int nTimeOut,char *szMsg);

//功能：
//表解锁
//参数说明：
//szTableName[输入]：表名
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_UnLockTable(char *szTableName,char *szMsg);

//功能：
//增加首个查询条件（类似于where后面的内容）
//参数说明：
//szTableName[输入]：表名
//str[输入]：条件内容
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_AddFirstCondition(char *szTableName, char *str,char *szMsg);

//功能：
//增加数值型查询条件（类似于where后面的内容）
//参数说明：
//szTableName[输入]：表名
//value[输入]：条件内容
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_AddConditionOfValue(char *szTableName, int *value,char *szMsg);

//功能：
//增加字符型查询条件（类似于where后面的内容）
//参数说明：
//szTableName[输入]：表名
//value[输入]：条件内容
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_AddConditionOfStr(char *szTableName, char *value,char *szMsg);

//功能：
//向表中插入数据
//参数说明：
//szTableName[输入]：表名
//buf[输入]：记录内容
//nbufsize[输入]：缓冲的大小
//multi[输入]：是否允许重复记录插入
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_Insert(char *szTableName, char *buf, int nbufsize,bool multi,char *szMsg);

//功能：
//清空条件（在调用AddFirstCondition时候系统自动调用）
//参数说明：
//szTableName[输入]：表名
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_Reset(char *szTableName,char *szMsg);

//功能：
//选出当前行的记录
//参数说明：
//szTableName[输入]：表名
//buf[输出]：记录内容
//nbufsize[输入]：缓冲的大小
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_SelectCurrent(char *szTableName, char *buf,int nbufsize,char *szMsg);

//功能：
//将当前行数据删除
//参数说明：
//szTableName[输入]：表名
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_SelectDelete(char *szTableName,char *szMsg);

//功能：
//得到第一条记录
//参数说明：
//szTableName[输入]：表名
//buf[输出]：记录内容
//nbufsize[输入]：缓冲的大小
//condition[输入]：是否使用where条件
//szMsg[输出]：报错信息
//返回值：
//>=0 返回的符合条件的纪录个数
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_SelectFirst(char *szTableName, char *buf, int nbufsize,bool condition,char *szMsg);

//功能：
//得到后续记录
//参数说明：
//szTableName[输入]：表名
//buf[输出]：记录内容
//nbufsize[输入]：缓冲的大小
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_SelectNext(char *szTableName, char *buf,int nbufsize,char *szMsg);

//功能：
//修改当前select的记录内容
//参数说明：
//szTableName[输入]：表名
//buf[输入]：记录内容
//nbufsize[输入]：缓冲的大小
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_SelectUpdate(char *szTableName, char *buf,int nbufsize,char *szMsg);

//功能：
//update记录
//参数说明：
//szTableName[输入]：表名
//buf[输入]：记录内容
//nbufsize[输入]：缓冲的大小
//condition[输入]：是否使用where条件
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_Update(char *szTableName, char *buf, int nbufsize,bool condition,char *szMsg);

//功能：
//删除纪录
//参数说明：
//szTableName[输入]：表名
//condition[输入]：是否使用where条件
//szMsg[输出]：报错信息
//返回值：
//0 成功
//-1 失败，失败原因从szMsg返回
int KSMEMDB_API WINAPI KSMEMDB_Delete(char *szTableName, bool condition,char *szMsg);
#ifdef __cplusplus
}
#endif

#endif
