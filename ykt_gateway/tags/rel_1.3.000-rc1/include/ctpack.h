

/***********************************************************************************
  编码日志记录
  编码者: 陈永华
  编码日期 2003-1-20 15:18:06
  版本: V2.00 - CT版本 
  说明: 本版本是大集中交易系统上的CTPACK
 ***********************************************************************************/


#ifndef __CTPACK_H
#define __CTPACK_H

#include "cpack.h"

#ifdef CTPACK_EXPORTS
#define CTPACK_API __declspec(dllexport)
#else
#define CTPACK_API __declspec(dllimport)
#endif

#define CTPACKVER  231      // 2xx为大集中版本所用
#define CTPACKDATE 20021129

   /* 以下代码是用来字节对齐使用的 */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#pragma options align=packed
#else
#define __PACKED__	__attribute__ ((packed))
#pragma pack(push,1)
#endif
#else
#define __PACKED__ 
#pragma pack(push,1)
#endif


typedef struct st_hookc
{
    unsigned int	UserID;					/* 请求者的ID号码*/
	char hostname[33];						/* 主机名 */
	char queuename[33];						/* 队列名 */
	unsigned int	queuetype;				/* 队列类型 */
}__PACKED__ ST_HOOKC;

/* 
	包头结构
*/
typedef struct st_packheadc
{
	unsigned int	RequestType;
	unsigned char	firstflag;				/* 是否第一个请求（首包请求）*/
	unsigned char	nextflag;					/* 是否后续包请求*/
	unsigned int	recCount;					/* 本包的记录数*/
	unsigned int	retCode;					/* 返回代码*/
	
	ST_ADDR			addr;						/* 请求着的地址（6个子节）*/
	ST_HOOKC       hook;	                    /*                    */
	unsigned int   userdata;					/*					*/

	unsigned char ParmBits[32];
}__PACKED__ ST_PACKHEADC;


typedef struct st_ctpack
{
   ST_PACKHEADC head;
   ST_PACKDATA	pack;
}__PACKED__ ST_CPACKC;


#ifdef __cplusplus
extern "C" {
#endif

#ifndef WIN32
#ifndef __GNUC__
#pragma options align=reset
#else
#pragma pack(pop)
#endif
#else
#pragma pack(pop)
#endif

CTPACK_API int  CTPackDllDate(int dversion=CTPACKVER);


//清除某个字段的位图, 
// 在实际使用中似乎没有用处
//入口参数：head：包头
//          fieldParam：将要清除的字段的位图
//返回值：成功：TRUE
//        失败：FALSE
CTPACK_API bool ClearParmBitC(ST_PACKHEADC *head, int fieldid);

//设置某个字段的位图
//入口参数：head：包头
//          fieldid：将要设置的字段的位图
//返回值：成功：TRUE
//        失败：FALSE
CTPACK_API bool SetParmBitC(ST_PACKHEADC *head, int fieldid);

CTPACK_API BOOL DecodeBufC(unsigned char *buf,int len,ST_CPACKC *pPack,char *eMsg);
CTPACK_API BOOL DecodeBufWithArrayC(unsigned char *buf,int len,ST_CPACKC *pPack,ST_PACKDATA *packArray,
                        int *recCount,char *eMsg);
CTPACK_API BOOL EncodeBufC(ST_CPACKC *pPack,unsigned char *buf,int *len,char *eMsg);
CTPACK_API BOOL EncodeBufArrayC(ST_CPACKC *pPack,ST_PACKDATA *pArray,unsigned char *buf,int *len,char *eMsg);

#ifdef __cplusplus
}
#endif

#endif
