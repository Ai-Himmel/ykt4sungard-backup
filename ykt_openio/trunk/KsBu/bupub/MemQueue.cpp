/********************************************************************
	created:	2007/10/08
	created:	8:10:2007   23:05
	filename: 	D:\proj\ksbass\testsmq\MemQueue.cpp
	file path:	D:\proj\ksbass\testsmq
	file base:	MemQueue
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 内存队列类：不保证线程安全的
				 仅由一个线程可以读的, 也只仅由一个队列可以写
				 但读和写的线程可以不同
*********************************************************************/
// MemQueue.cpp: implementation of the CMemQueue class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "memory.h"
#include "MemQueue.h"

void MQ_Init(T_MQUEUE *pmq)
{
	if (pmq==NULL)
		return;
   int i;
   for (i=0;i<MAX_QUEUES;i++)
   {
      pmq->q_items[i].qblen = 0xFFFF;
   }
	pmq->r_item = pmq->w_item = 0;
}

void MQ_RClose(T_MQUEUE *pmq)
{
	if (pmq==NULL)  // 尤其怕在多线程下，被别的程序给关闭了
		return;
	pmq->r_item = -1;
}

void MQ_WClose(T_MQUEUE *pmq)
{
	if (pmq==NULL)  // 尤其怕在多线程下，被别的程序给关闭了
		return;
	pmq->w_item = -1;
}

int MQ_Read(T_MQUEUE *pmq, void *data)
{
	if (pmq==NULL||pmq->w_item<0||pmq->r_item<0)
		return(MQE_CLOSED);
	int dlen;
	if (pmq->r_item==pmq->w_item)
		return(MQE_EMPTY);
   int ri=pmq->r_item;
	dlen = pmq->q_items[ri].qblen;
   if (dlen<=0)
   {
      printf("MEMQUEUE data length Error:%d\n",dlen);
   }
   if (dlen>MAXMSGQLEN)
   {
      printf("MEMQUEUE renews UN-SYNCH.\n");
      return(MQE_EMPTY);
   }
   pmq->q_items[ri].qblen = 0xFFFF;
	memcpy(data,pmq->q_items[ri].qbuf,dlen);
	if (++ri>=MAX_QUEUES)
      ri = 0;
   pmq->r_item = ri;
	return(dlen);
}


/* ****** Updated by CHENYH at 2007-11-19 17:46:07 ****** 
int MQ_Read_Test(T_MQUEUE *pmq, void *data,int *ritem)
{
   if (pmq==NULL||pmq->w_item<0||pmq->r_item<0)
      return(MQE_CLOSED);
   int dlen;
   if (pmq->r_item==pmq->w_item)
      return(MQE_EMPTY);
   int ri=pmq->r_item;
   if (ri!=*ritem)
   {
      printf("TEST: Error for r_item (%d!=%d)\n",ri,*ritem);
   }
   dlen = pmq->q_items[ri].qblen;
   if (dlen<=0)
   {
      printf("MEMQUEUE data length Error:%d\n",dlen);
   }
   if (dlen>MAXMSGQLEN)
   {
      printf("MEMQUEUE renews UN-SYNCH.\n");
      return(MQE_EMPTY);
   }
   pmq->q_items[ri].qblen = 0xFFFF;
   memcpy(data,pmq->q_items[ri].qbuf,dlen);
   ++ri;
   if (ri>=MAX_QUEUES)
   {
      ri = 0;
   }
   *ritem = ri;
   pmq->r_item = ri;
   return(dlen);
}
************************************************************/

int MQ_Write(T_MQUEUE *pmq, void *data, int len)
{
	int i,i0;
	if (len<=0||len>MAXMSGQLEN)
		return(MQE_DATALEN);
	if (pmq==NULL||pmq->w_item<0||pmq->r_item<0)
		return(MQE_CLOSED);
	i = i0 = pmq->w_item;
	if (++i>=MAX_QUEUES)
		i = 0;
	if (i==pmq->r_item)
		return(MQE_FULL);
	memcpy(pmq->q_items[i0].qbuf,data,len);
	pmq->q_items[i0].qblen = len;
	pmq->w_item = i;
	return(i0+1);
}

