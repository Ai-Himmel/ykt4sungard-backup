/********************************************************************
	created:	2007/10/10
	created:	10:10:2007   23:38
	filename: 	D:\proj\ksbass\testsmq\MsgQueue.cpp
	file path:	D:\proj\ksbass\testsmq
	file base:	MsgQueue
	file ext:	cpp
	author:		CHENYH
	
	purpose:	尽管本模式在单线程下，还算可以。
				可是由于许多系统中，如AIX中，存在共享内存的个数有限，极少
				导致不能用于需要许多队列的情况，因此，不建议采用本模式。
*********************************************************************/
// MsgQueue.cpp: implementation of the CMsgQueue class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MemQueue.h"
#include "MsgQueue.h"
#ifndef SHM_MQ
#error Unfixed 'MsgQueue.h' included (should SHM_MQ)!
#endif

#ifdef WIN32
#include "process.h"
bool bNotGetFrenquecy=true;
LARGE_INTEGER frenquecy;
void TestWindowsTime()
{
	LARGE_INTEGER p1,p2;
	char buf[256];
	int nms;
	printf("Enter test count of us:");
	gets(buf);
	nms = atoi(buf);
	if (bNotGetFrenquecy)
	{
		QueryPerformanceFrequency(&frenquecy);
		bNotGetFrenquecy = false;
	}
	LONGLONG dus;
	unsigned int dd=GetTickCount();
	QueryPerformanceCounter(&p1);
	Sleep(nms);
	QueryPerformanceCounter(&p2);
	dd = GetTickCount()-dd;
	dus = p2.QuadPart-p1.QuadPart;
	printf("Sleep(%d) - Ticks:%u - pc:%u us \n",nms,dd,(unsigned int)(dus*1000000/frenquecy.QuadPart));
}

void gettimeofday(struct timeval *pt,void *ptr)
{
	LARGE_INTEGER perfCount;
	if (bNotGetFrenquecy)
	{
		QueryPerformanceFrequency(&frenquecy);
		bNotGetFrenquecy = false;
	}
	QueryPerformanceCounter(&perfCount);
	if (frenquecy.QuadPart>0)
	{
		double dd = (double)perfCount.QuadPart/frenquecy.QuadPart;
		pt->tv_sec = (long)dd;
		pt->tv_usec = ((long)((dd-pt->tv_sec)*1000000.))%1000000;
	}
	else
	{
		pt->tv_sec = perfCount.QuadPart/1000000;
		pt->tv_usec = perfCount.QuadPart%1000000;
	}
	
/* ****** Updated by CHENYH at 2007-10-11 18:54:29 ****** 
	unsigned int tick = GetTickCount();
	pt->tv_usec = (tick%1000)*1000;
	pt->tv_sec = tick/1000;
*/
}
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMQFactory::CMQFactory()
{
   m_nMQs=0;
   m_pMQ=NULL;
}

CMQFactory::~CMQFactory()
{
   
}

bool CMQFactory::New(const char *name, int count)
{
   Destroy();
   if (count<1)
      return(false);
   m_pMQ = new CMsgQueue[count];
   if (NULL==m_pMQ)
      return(false);
   int i;
   for (i=0;i<(int)(sizeof(m_Name)-1)&&name[i]!='\0';i++)
   {
      m_Name[i]=name[i];
   }
   m_Name[i]='\0';
   char *ptr = (char *)m_bushm.Open(m_Name,count*m_pMQ->GetSize());
   if (ptr==NULL)
   {
      delete m_pMQ;
      m_pMQ = NULL;
      return(false);
   }
   else
   {
      for (m_nMQs=0;m_nMQs<count;m_nMQs++)
      {
         m_pMQ[m_nMQs].Init(ptr,m_nMQs,m_Name);
         ptr += m_pMQ[m_nMQs].GetSize();
      }
      return(true);
   }
}

void CMQFactory::Destroy()
{
   int i;
   if (m_pMQ==NULL||m_nMQs<1)
      return;
   for (i=0;i<m_nMQs;i++)
   {
      m_pMQ[i].Exit(); // to destroy MQ
   }
   delete []m_pMQ;
   m_pMQ = NULL;
   m_nMQs = 0;
   m_bushm.Close();
}

CMsgQueue * CMQFactory::GetMQ(int mqid)
{
   if (mqid<0||mqid>=m_nMQs)
      return(NULL);
   return(m_pMQ+mqid);
}


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsgQueue::CMsgQueue()
{
   s_ptr = r_ptr = NULL;
   m_openmode = OM_INVALID;
   m_chkusec = 1000;
   m_iID = -1;
   ptr0 = NULL;
   pMQFName = NULL;
}

CMsgQueue::~CMsgQueue()
{
//	Close();
}

int CMsgQueue::GetSHMSize()
{
	return (((sizeof(T_MQUEUE)+7)>>3)<<3);
}

void CMsgQueue::Close()
{
	if (m_openmode==OM_INVALID)
		return;
   s_sempid.Close();
   r_sempid.Close();

	m_openmode = OM_INVALID;
	if (s_ptr!=NULL)
	{
		MQ_WClose((T_MQUEUE *)s_ptr);
		s_ptr = NULL;
	}
	if (r_ptr!=NULL)
	{
		MQ_RClose((T_MQUEUE *)r_ptr);
		r_ptr = NULL;
	}
	if (m_chkusec>0)
	{
		myusleep(m_chkusec<<1); // avoid releasing memory when Recv/Send.
	}
}

#define MIN_CHKUS 1
#define MAX_CHKUS 100000
bool CMsgQueue::Open(int omode, int uscheck)
{
	Close();
	if (ptr0==NULL)
		return(false);
	if (omode!=OM_CREATE&&omode!=OM_OPEN)
		return(false);
   if (pMQFName==NULL)
      return(false);
	if (uscheck<MIN_CHKUS)
		uscheck = MIN_CHKUS;
	if (uscheck>MAX_CHKUS)
		uscheck = MAX_CHKUS;
	m_chkusec = uscheck;
   char sempname[256];
   sprintf(sempname,"%s_s",pMQFName);
   if (OM_CREATE==omode)
      s_sempid.Open(sempname,m_iID,MAX_QUEUES);
   else
      r_sempid.Open(sempname,m_iID,MAX_QUEUES);
   sprintf(sempname,"%s_r",pMQFName);
   if (OM_CREATE==omode)
      r_sempid.Open(sempname,m_iID,MAX_QUEUES);
   else
      s_sempid.Open(sempname,m_iID,MAX_QUEUES);
   if (!(r_sempid.IsOpened()) || !(s_sempid.IsOpened()))  // for error check at first... 2007-11-22 10:48:04
      return(false);
 	if (OM_CREATE==omode)
 	{
 		s_ptr = ptr0;
 		r_ptr = ptr0+GetSHMSize();
 	   MQ_Init((T_MQUEUE*)s_ptr);  // SHM_MQ must reset when Open for next Send/Recv to avoid error.
	   MQ_Init((T_MQUEUE*)r_ptr);
      s_sempid.SetValue(0);
      r_sempid.SetValue(0);
 	}
 	else
 	{
 		s_ptr = ptr0+GetSHMSize();
 		r_ptr = ptr0;
	}
   m_openmode = omode;
	return(true);
}



void CMsgQueue::myusleep(unsigned int useconds)
{
#ifdef WIN32
/* ****** Updated by CHENYH at 2007-10-26 14:14:57 ****** 
   // 在Windows XP下，测试结果，即使useconds=1, 实际等待将会在10毫秒左右，因此基本上和Sleep(1)相同
	if (m_socket!=-1)
   {
      fd_set rset;
		struct timeval tv;
		FD_ZERO(&rset);
		FD_SET(m_socket, &rset);
		tv.tv_sec = useconds/1000000;
		tv.tv_usec = useconds%1000000;
		select(m_socket+1, &rset, NULL, NULL, &tv);
   }
	else
*********************************************************/
		Sleep(useconds/1000);
#else
	#define MAXUSLEEPUNIT 500000
   /******* Updated by CHENYH at 2005-10-29 0:39:25 ******/
   // 由于HP-UX测试时候，发现usleep最大可输入的参数值为1000000,
   // 因此不能直接用usleep(milliseconds*10000)来操作
   unsigned int i;
   do {
   	if (useconds>MAXUSLEEPUNIT)
      {
         i = MAXUSLEEPUNIT;
      }
      else
      {
         i = useconds;
      }
      useconds -= i;
      usleep(i);
   } while(useconds>0);
#endif
}


int CMsgQueue::Send(char *ptr, int nDesignedSize, int type)
{
	T_MQUEUE *pmq = (T_MQUEUE *)s_ptr;
	if (m_openmode==OM_INVALID || pmq==NULL)
		return(-1);
	if (nDesignedSize>MAXMSGQLEN)
		return(-2);
	if (nDesignedSize<=0)
		return(0);
	while(1)
	{
		int rtn = MQ_Write(pmq,ptr,nDesignedSize);
		if (rtn!=MQE_FULL)
		{
			if (rtn>0)
         {
            rtn = s_sempid.V();
            if (rtn!=1)
            {
               printf("S_SEMP.V return %d\n",rtn);
            }
				return(nDesignedSize);
         }
			else
			{
            printf("Error on MQ_Write:%d\n",rtn);
				Close();
				return(-3);
			}
		}
		myusleep(m_chkusec);
	}
}

#define MQRWAITUS   100000  // 1000
#define MQ_MAXTIMEOUT 2100000  // ~= 0x7FFFFFFF/1000 = 2147483
int CMsgQueue::Recv(char *vptr, int nDesignedSize, int timeout, int type)
{
	int len;
	T_MQUEUE *pmq = (T_MQUEUE *)r_ptr;
	if (m_openmode==OM_INVALID || pmq==NULL)
		return(-1);
	if (nDesignedSize<=0)
		return(-10); 
	if (timeout<0||timeout>MQ_MAXTIMEOUT)
	{
		timeout = MQ_MAXTIMEOUT;
	}
   
   timeout *= 1000;
   if (r_sempid.IsOpened())
   {
      struct timeval tv0,tv1; 
      gettimeofday(&tv0,NULL);
      do 
      {
         r_sempid.P(MQRWAITUS);
         len = MQ_Read(pmq,vptr);
         if (len>0)
            return(len); // OK
         else if (len!=MQE_EMPTY)
         {
            printf("Error on MQ_Read: %d\n",len);
            Close(); // closed by partner
            return(-1);
         }
         //printf("UN-SYNCH. between R_SEMPID.P and SHMQ Write (ritem=%d witem=%d)!\n",pmq->r_item,pmq->w_item);
         gettimeofday(&tv1,NULL);
         if ((tv1.tv_sec-tv0.tv_sec)*1000000+tv1.tv_usec-tv0.tv_usec>timeout)
            return(0);
      } while(1);
   }
	do {
		len = MQ_Read(pmq,vptr);
		if (len>0)
			return(len); // OK
		else if (len!=MQE_EMPTY)
		{
			Close(); // closed by partner
			return(-1);
		}
		if (timeout<=0)
			return(0); // as timeout
		myusleep(m_chkusec);
		timeout -= m_chkusec;
	} while(1);
}



bool CMsgQueue::IsOpened()
{
	return(m_openmode==OM_CREATE||m_openmode==OM_OPEN);
}

int CMsgQueue::GetMQID()
{
	return(m_iID);
}

int CMsgQueue::GetOpenMode()
{
	return(m_openmode);
}

void CMsgQueue::Init(char *baseptr, int iID, char *pname)
{
   pMQFName = pname;
   m_iID = iID;
   ptr0 = baseptr;
}

int CMsgQueue::GetSize()
{
	return(GetSHMSize()<<1);
}

void CMsgQueue::Exit()
{
   Close();
   ptr0 = NULL;
   m_iID = -1;
   pMQFName = NULL;
}
