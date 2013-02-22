#include <stdio.h>
#include "shem.h"
//#include "transinfo.h"

// ipc全局变量
int shmid=0;
int semid=0;
char *shm = NULL;

int sem(key_t  key)
{
	union semun sem;
	int semid;
	int ret;
	sem.val=1;
	semid=semget(key,1,IPC_CREAT|0666);
	
	if(semid==-1)
	{
		perror("semget(key,1,IPC_CREAT|IPC_EXCL|0666)");
	}
	else
	{
		//初始化信号量
		ret=semctl(semid,0,SETVAL,sem);
		if(ret==-1)
			perror("semctl(semid,0,SETVAL,sem)");
	}
	
	return semid;
}
//删除信号量
void d_sem(int semid)
{
	union semun sem;
	sem.val=0;
	semctl(semid,0,IPC_RMID,0);
}
//信号量P操作
int p(int semid)
{
	int ret;
	struct sembuf sops={0,-1,SEM_UNDO};
	ret = semop(semid, &sops,1);
	if(ret != 0)
		perror("p(semid) semop(semid, &sops,1)");
	return ret;
}
//信号量V操作
int v(int semid)
{
	int ret;
	struct sembuf sops={0,+1,SEM_UNDO};
	ret = semop(semid,&sops,1);
	if(ret != 0)
		perror("v(semid) semop(semid,&sops,1)");
	return ret;
}

/******************************
add by hhd end at 2004-9-16 15:22
******************************/

