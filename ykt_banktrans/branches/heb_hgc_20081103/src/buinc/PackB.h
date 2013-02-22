/********************************************************************
	created:	2004/09/23
	created:	23:9:2004   16:35
	filename: 	e:\proj\goldmem\ksbcc\packbase\packb.h
	file path:	e:\proj\goldmem\ksbcc\packbase
	file base:	packb
	file ext:	h
	author:		ChenYH
	
	purpose:	为了消除CPACK中几个致命的缺陷，采用一个不强制约定ST_PACK结构
            能够支持：
            １．能够采用非强制结构的ST_PACK；
            ２．能够支持包体数据为RAW-DATA-BLOCK(ST_SDPACK); 方便传输文件或自定义数据块；
            ３．强化对ST_CPACK操作函数；
*********************************************************************/
#ifndef __PACKB_H_
#define __PACKB_H_

/* 定义了PARMBITS的最大大小了每字节的BITS数 */
#define PARMBITS	   255   //(256) 最后一个位图标专门用于标志新CYH的打包方式，含版本标志第一个字节为PACK架构版本，第二字节为PACK数据结构版本
#define BITSPERBYTE	(8)
#define PARMBYTES 32       // PARMBITS/BITSPERBYTE -- 应该可以提高系统处理速度

enum PDLTYPES
{
   PDL_CHAR=1,          // 普通字符串模式，约定长度，最长不超过255
   PDL_VCHAR=2,         // 变长字符，最长不超过255
   PDL_UCHAR=3,         // 用于存放二进制数据的字段，比如权限等
   PDL_INT=4,           // 整数字段，（由于在64位机中，long属于64位，而在32位机中则为32位，对于int则是固定的，因此本协议中不再采用long）
   PDL_DOUBLE=5         // double类型字段
};

#ifdef __cplusplus
extern "C" {
#endif

/* 以下代码是用来字节对齐使用的 */
#ifdef WIN32
   #define __PACKED__ 
   #pragma pack(push,1)
#else
   #ifdef __GNUC__
      #define __PACKED__	__attribute__ ((packed))
      //#pragma pack(push,1)
   #else
      #ifdef HP_UX
         #define __PACKED__
         #pragma pack 1
      #else
         #define __PACKED__
         #pragma options align=packed
      #endif
   #endif
#endif

   // 用于定义ST_PACK结构的数据结构：
   typedef struct  _ST_PDATALIST {
      char szName[32];
      char wType;    // 0 - None; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double
      int  nLength;  // 0 - None.
      unsigned int  dwOffset; // 
   } __PACKED__ ST_PDATALIST;

   
   /*
   地址资料
   */
   typedef struct _ST_ADDR
   {
      unsigned char addr[6];
   } __PACKED__ ST_ADDR;
   
   typedef struct _ST_HOOK
   {
      unsigned int	UserID;					/* 请求者的ID号码*/
      char hostname[33];						/* 主机名 */
      char queuename[33];						/* 队列名 */
      unsigned int	queuetype;				/* 队列类型 */
   } __PACKED__ ST_HOOK;
   
   /* 
   包头结构
   */
   typedef struct _ST_PACKHEAD
   {
      unsigned int	RequestType;
      unsigned char	firstflag;				/* 是否第一个请求（首包请求）*/
      unsigned char	nextflag;					/* 是否后续包请求*/
      unsigned int	recCount;					/* 本包的记录数*/
      unsigned int	retCode;					/* 返回代码*/
      
      ST_ADDR			addr;						/* 请求着的地址（6个子节）*/
      ST_HOOK         hook;	                    /*                    */
      unsigned int    userdata;					/*					*/
      
      unsigned char ParmBits[PARMBYTES];
   } __PACKED__ ST_PACKHEAD;
   

   typedef struct _ST_SDPACK
   {
      unsigned short usDataLength;        /* 开发者自定义数据长度，这里的字节序由本编码和解码自动完成 */
      char data[1];              /* 自定义的数据内容，注意交换双方的主机的字节序 */
   } __PACKED__ ST_SDPACK;                
   /*
    *	本报文结构是为了支持自定义数据设计的，其中usDataLength是指data中实际的数据长度，用户自行定义的数据
    * 则为data部分，这部分在不同字节序的主机之间交换数据，其数据的字节序需要自己控制，本编码解码模块不作控制
    */


   
#ifdef WIN32
   #pragma pack(pop)
#else
   #ifdef __GNUC__
   #else
      #ifdef HP_UX
         #pragma pack 0
      #else
         #pragma options align=reset
      #endif
   #endif
#endif
#undef __PACKED__
   
   #define MAXPACKROWS 100


   // 以下为C/C++都能调用的一些基本函数：
   
#ifdef __cplusplus
}
#endif

#endif

