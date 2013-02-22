/********************************************************************
created:	2004/10/12 15:07:21
filename:cpack.h
author:chenyh
purpose:	ST_PACK data structure defined file 
		 created from cpack.dbf
*********************************************************************/
#ifndef __CPACK_H
#define __CPACK_H

#include "PackB.h"

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

typedef struct _ST_PACK 
{
   char  dbuf[8192];  // 2005-8-3 10:14:30 原来只是定义了dbuf[1]，在实际中，很有可能出现越界导致异常
} __PACKED__ ST_PACK;
typedef struct _ST_CPACK
{
	ST_PACKHEAD head;
	ST_PACK     pack;
} __PACKED__ ST_CPACK;

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

#include "PackC.h"

#endif
