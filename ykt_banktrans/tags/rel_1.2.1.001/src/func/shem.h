#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>

#ifndef	SEGSIZE	
	#define 	SEGSIZE		1024	
#endif

extern int shmid;
extern int semid;
extern char *shm;

#define READTIME	1

union semun
{
	int val;
	struct semid_ds *buf;
	ushort* array;
};

int sem(key_t  key);

void d_sem(int semid);
int p(int semid);
int v(int semid);
