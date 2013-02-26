// BUSem.cpp: implementation of the CBUSem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BUSem.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifdef WIN32
#else
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/sem.h>

#define SH_DENYNO    0x40
#define SH_DENYRW    0x10
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBUSem::CBUSem()
{
   m_sempid = INVALID_SEMP;
   m_sempno = -1;
}

CBUSem::~CBUSem()
{

}


bool CBUSem::Open(const char *name, int semid, int maxvalue)
{
   char buf[1024];
   Close();
#ifdef WIN32
   int i;
   sprintf(buf,"%s%d.sem",name,semid);
   for (i=0;i<sizeof(buf);i++)
   {
      if ('\\'==buf[i])
         buf[i]='_';
      else if (0==buf[i])
         break;
   }
   if (maxvalue>0)
      m_sempid = CreateSemaphore(NULL,0,maxvalue,buf);
   else
      m_sempid = INVALID_SEMP;
   if (m_sempid==INVALID_SEMP)
   {
      m_sempid = OpenSemaphore(SEMAPHORE_ALL_ACCESS,TRUE,buf);
   }
#else
   int handle;

/* ****** Updated by CHENYH at 2007-11-21 15:34:33 ****** 
   sprintf(buf,"%s_%d.sem",name,semid); // 由于一个进程最多可打开的sem个数有限
********************************************************/
   sprintf(buf,"%s%d.sem",name,semid/MAXSEMPNO);
   handle = sh_open(buf,O_RDWR,SH_DENYNO);
   if (handle == -1)
   {
      handle = sh_open(buf,O_CREAT|O_RDWR,SH_DENYNO);
   }   
   if (handle == -1)
   {
      return -2;
   }
   else
   {
      close(handle);
   }
   
   //key_t semkey = ftok(buf,semid/MAXSEMPNO); 这种情况下，AIX下得到的semkey会变成0xffffffff, 即ftok的proj不适合用0
   //key_t semkey = ftok(buf,(semid/MAXSEMPNO)+1);
   // 另外，奇怪的是0-99线程部分很慢，而>99号的线程却能很快
   key_t semkey = ftok(buf,(semid/MAXSEMPNO)+10);
   if (maxvalue>0)
   {
      m_sempid = semget(semkey,MAXSEMPNO,0777|IPC_CREAT);
   }
   else
   {
      m_sempid = INVALID_SEMP;
   }
   if (m_sempid==INVALID_SEMP)
   {
      m_sempid = semget(semkey,0,0);
   }
   m_sempno = semid%MAXSEMPNO;
#endif
   return(m_sempid!=INVALID_SEMP);   
}


void CBUSem::Close()
{
   if (m_sempid!=INVALID_SEMP)
   {
#ifdef WIN32
      CloseHandle(m_sempid);
#else
#endif
      m_sempid = INVALID_SEMP;
   }
}


void CBUSem::Remove(const char *name, int semid)
{
#ifdef WIN32
#else
   if (Open(name,semid,0))
   {
      semctl(m_sempid,m_sempno,IPC_RMID,0);
      m_sempid = INVALID_SEMP;
   }
#endif   
}


int CBUSem::P(int usTimeout)
{
   if (m_sempid==INVALID_SEMP)
      return -100;
   if (usTimeout<=0)
   {
      usTimeout = 0;      
   }
#ifdef WIN32
   switch (WaitForSingleObject(m_sempid,usTimeout/1000))
   {
   case WAIT_OBJECT_0:
      return(1);
   case WAIT_TIMEOUT:
      return(0);
   default: // WAIT_ABANDONED
      return(-1); 
   }
#else
   struct timespec tsto;
   tsto.tv_sec = usTimeout/1000000;
   tsto.tv_nsec = (usTimeout%1000000)*1000;
   struct sembuf sempb;
   sempb.sem_num = m_sempno;
   sempb.sem_op = -1;
   sempb.sem_flg = 0;
   if (semtimedop(m_sempid,&sempb,1,&tsto)==0)
      return(1);
   else if (errno==EAGAIN)
      return(0);
   else
      return(-1);
#endif
}

int CBUSem::V()
{
   if (m_sempid==INVALID_SEMP)
      return -100;
#ifdef WIN32
   long lv;
   if (ReleaseSemaphore(m_sempid,1,&lv))
      return(1);
   else
      return(-1);
#else
   struct sembuf sempb;
   sempb.sem_num = m_sempno;
   sempb.sem_op = 1;
   sempb.sem_flg = 0;
   if (semop(m_sempid,&sempb,1)==0)
      return(1);
   else
   {
      printf("errno=%d\n",errno);  // 在AIX上出现了这个错误
      return(-1);
   }
#endif
}

bool CBUSem::IsOpened()
{
   return(m_sempid!=INVALID_SEMP);
}

int CBUSem::GetValue()
{
   if (m_sempid==INVALID_SEMP)
      return -100;
#ifdef WIN32
   long lv;
   if (ReleaseSemaphore(m_sempid,1,&lv))
   {
      switch (WaitForSingleObject(m_sempid,10000))
      {
      case WAIT_OBJECT_0:
         return(lv);
      default:
         return(-2);
      }
   }
   else
      return(-1);
#else
   return(semctl(m_sempid,m_sempno,GETVAL));
#endif
}

void CBUSem::SetValue(int value)
{
   if (m_sempid==INVALID_SEMP)
      return;
#ifdef WIN32
   int rtn;
   do 
   {
      rtn = GetValue();
      if (rtn==value)
         break;
      else if (rtn>value)
         P(1000);
      else
         V();
   } while(1);
#else
   semctl(m_sempid,m_sempno,SETVAL,value);
#endif
   return;
}
