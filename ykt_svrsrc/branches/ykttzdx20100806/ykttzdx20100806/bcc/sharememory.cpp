// ShareMemory.cpp: implementation of the CShareMemory class.
//
//////////////////////////////////////////////////////////////////////

/* ****** Updated by CHENYH at 2004-3-28 21:31:26 ****** 
   // 为了能够在工程中不直接用本文件提供CShareMemory，来保证在WINDOWS平台下编译正常
   // 特别将本文件通过include在ksbcc.cpp中，来间接提供CShareMemory
#include "stdafx.h"
#include "sharememory.h"
*/
#include "sys/ipc.h"
#include "sys/shm.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CShareMemory::CShareMemory()
{
	m_shmid=-1;
	memset(m_memoryname,0,sizeof(m_memoryname));
}

CShareMemory::~CShareMemory()
{

}

void *CShareMemory::openshare(char *memoryname,int buffersize,void * shmaddr,int flag)
{
	key_t key=myftok(memoryname,1);
	strcpy(m_memoryname,memoryname);
	if((m_shmid=shmget(key,1024*buffersize,0777|IPC_CREAT))==-1)
	{
		m_shmid = shmget(key,0,flag);
	}
	if(m_shmid>=0)
	{
//		printf("[%s] shmid=%d %d\n",memoryname,m_shmid,key);
		if((shmaddr=shmat(m_shmid,(char *) 0,flag)) !=NULL) 
		{
//			printf("*****%d\n",shmaddr);
			return  shmaddr;
		}
		else return NULL;
	}
	else
	{
		printf("open share memory [%s] error %d\n",m_memoryname,errno);
		return NULL;
	}
}

void CShareMemory::deleteshare(char *memoryname)
{
	char shname[80];
	if(m_shmid == -1)
	{
		if(memoryname==NULL)
			 strcpy(shname,m_memoryname);
		else strcpy(shname,memoryname);
		m_shmid = shmget(myftok(shname,1),0,SHM_SHARE_MMU);
	}
	if(shmctl(m_shmid,IPC_RMID,0) == -1)
		printf("delete share momory [%s] error : %s \n",shname,strerror(errno));
}

void CShareMemory::showinfo(char *memoryname)
{
	struct shmid_ds info;
	gethandle(memoryname);
	if(shmctl(m_shmid,IPC_STAT,(struct shmid_ds*)&info)!=-1)
	{
       printf("read-write:%03o,segszs=%d,lpid=%d,cpid=%d curid=%d \n",info.shm_perm.mode&0777,(int)info.shm_segsz,(int)info.shm_lpid,(int)info.shm_cpid,getpid());
	}
}

int CShareMemory::closeshare(const void *shmaddr)
{
	int iRet;
	if(NULL != shmaddr );
	iRet=shmdt(shmaddr);
	shmaddr=NULL;
	return iRet;
}

int CShareMemory::gethandle(char *memoryname)
{
	char shname[80];
	if(m_shmid == -1)
	{
		if(memoryname==NULL)
			 strcpy(shname,m_memoryname);
		else strcpy(shname,memoryname);
		m_shmid = shmget(myftok(shname,1),0,SHM_SHARE_MMU);
	}
	return m_shmid;
}

key_t CShareMemory::myftok(char *path, int ID)
{
	char buffer[255];
	char current_path[255];
	int  handle;
	memset(buffer,0,sizeof(buffer));
	memset(current_path,0,sizeof(current_path));
	if(NULL != getcwd(current_path,sizeof(current_path)))
	{
	    sprintf(buffer,"%s/%s.shm",current_path,path);
	}
	else 
		sprintf(buffer,"/tmp/%s.shm",path);
//	printf("[%s]\n",buffer);

	handle=open(buffer,O_RDWR);
	if (handle == -1)
	{
		handle=creat(buffer,S_IREAD|S_IWRITE);
		if (handle == -1)
		{
			return -2;
		}
		else
		{
			close(handle);
		}
	}
	else
	{
		close(handle);
	}
	return ftok(buffer,ID);
}

void CShareMemory::setshname(char *shmname)
{
	strcpy(m_memoryname,shmname);
}
