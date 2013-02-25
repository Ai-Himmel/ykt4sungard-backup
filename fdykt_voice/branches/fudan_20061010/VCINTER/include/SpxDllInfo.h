#ifndef __SPXDLLINFO_H__
#define __SPXDLLINFO_H__

#include "SList.h"

typedef BOOL (*FORMPACKFUNC)(int nFunction, char *buffer, CSList *plist, void *pvoid, int DestNO);
typedef BOOL (*FORMSTRFUNC)(int nFunction, char *buffer, CSList *plist, void *pvoid, bool bFirstRow);
typedef BOOL (*INITFUNC)(char *IniFileName);
typedef BOOL (*EXITFUNC)(void);

typedef struct  
{
	int	 nFunction;		// 本功能SPX编号
	char     szName[48];		// 本功能名称
	int	 nRequestType;		// 本功能后台CPACK协议编号
	int      type;          /* 功能类型：
                                           0 - 交易类请求
                                           1 - 单笔返回数据查询
                                           2 - 多笔返回数据查询
				*/
	FORMPACKFUNC  pFormPackFunc;		// 向后台打包的函数指针
	FORMSTRFUNC  pFormStrFunc;		// 将CPACK包解包并向前台打包返回的函数指针
} DLLFUNCENTRY, *LPDLLFUNCENTRY;

typedef  struct 
{
	int		iFuncNum;               // 功能数目
	DLLFUNCENTRY	*pDllFunc;		// 功能说明项数组
	INITFUNC	pFuncInit;		// 初始化函数的指针
	EXITFUNC	pFuncExit;		// 退出函数的指针
	FORMPACKFUNC	pDefaultFormPackFunc;	// 将CPACK包解包并向前台打包返回的函数指针
	FORMSTRFUNC	pDefaultFormStrFunc;	// 向后台打包的函数指针
	int		m_MinFuncNo,m_MaxFuncNo;	// 最小功能号索引   最大功能号索引
	char		m_productName[40];		// 模块名称:
						// V7Inter/VCInter
	int		m_Version;			// 版本号 i.e.130:Ver1.30 / 100:Ver1.00
	int		m_BuildDate;			// 编译日期 yyyymmdd
	char		m_programmer[12];		// DLL开发员  

} DLLINFO, *LPDLLINFO;

#ifdef SPXDLL_EXPORTS
#define SPXDLL_API __declspec(dllexport)
#else
#define SPXDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {  //以“c”方式编译，是防止函数名被编译器改变
#endif
      SPXDLL_API DLLINFO *GetDllInfo(void);

#ifdef __cplusplus
}
#endif


#endif //__SPXDLLINFO_H__
