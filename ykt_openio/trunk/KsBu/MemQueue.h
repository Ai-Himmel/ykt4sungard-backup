// MemQueue.h: interface for the CMemQueue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMQUEUE_H__B109FE32_626A_4390_BC5E_A9034BF5893A__INCLUDED_)
#define AFX_MEMQUEUE_H__B109FE32_626A_4390_BC5E_A9034BF5893A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MsgQueue.h"


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

typedef struct _T_QUEUE
{
	unsigned short qblen;
	char qbuf[MAXMSGQLEN];
} __PACKED__ T_QUEUE;

typedef struct _T_MQUEUE
{
	T_QUEUE q_items[MAX_QUEUES];  // Message Buffers
	int r_item;  // read item number
	int w_item;  // write item number
} __PACKED__ T_MQUEUE;

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

#define MQE_CLOSED	-10	// MQ Closed
//#define MQE_RETRY    -3    // retry for MQ_Read (data incomplete) 
#define MQE_DATALEN	-2		// invalid data length of MQ_Write
#define MQE_FULL		-1		// No queue free of MQ_Write
#define MQE_EMPTY		0		// No data in queue on reading 

void MQ_Init(T_MQUEUE *pmq);
int MQ_Read(T_MQUEUE *pmq, void *data);
int MQ_Write(T_MQUEUE *pmq, void *data, int len);
void MQ_RClose(T_MQUEUE *pmq);
void MQ_WClose(T_MQUEUE *pmq);

//int MQ_Read_Test(T_MQUEUE *pmq, void *data,int *ritem);

#endif // !defined(AFX_MEMQUEUE_H__B109FE32_626A_4390_BC5E_A9034BF5893A__INCLUDED_)
