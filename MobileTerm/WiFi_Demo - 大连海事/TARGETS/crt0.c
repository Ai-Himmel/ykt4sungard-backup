#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#undef errno


extern char _stext;     
extern char _etext;
extern char _data;
extern char _edata;
extern char _start_bss;
extern char _end_bss;
extern char _end;
extern int main(void);

typedef int (*pfunc)(void);


char *__env[1] = { 0 };
char **environ = __env;
char *stack_ptr = (char *)0x0C700000;           //8M SDRAM
//char *stack_ptr = (char *)0x0DF00000;           //32M SDRAM

int 	errno;

pfunc	funcmain = main;


int	_start(void)
{
	register char *ptrDes = (char *)0x0C060000;
	register char *ptrSrc = (char *)0x60000;
	while (ptrDes < &_edata)
	{
		*ptrDes++ = *ptrSrc++;
	}
    	
    	ptrDes=&_start_bss;
    	while(ptrDes < &_end_bss)
    	{
		*ptrDes++ = 0;
	}
	
	funcmain();
	
	return 0;
}



//_exit()
//{
//	for(;;);
//}

int close(int file)
{
	file = file;
	return -1;
}

int _close_r(void *reent, int fd)
{
        fd = fd;
        reent=reent;
        return -1;
}

int execve(char *name, char **argv, char **env)
{
	name = name;
	argv = argv;
	env = env;
	errno = ENOMEM;
	return -1;
}

int fork(void)
{
	errno = EAGAIN;
	return -1;
}

int _fork_r(void *reent)
{
	reent=reent;
	errno = EAGAIN;
	return -1;
}

int fstat(int file, struct stat *st)
{
	file = file;
	st->st_mode = S_IFCHR;
	return 0;
}

int _fstat_r(void *reent,int fd, struct stat *pstat)
{
	reent=reent;
	fd = fd;
	pstat->st_mode = S_IFCHR;
	return 0;
}

int _fstat64_r(void *reent, int fd, struct stat *pstat)
{
	reent=reent;
	fd = fd;
	pstat->st_mode = S_IFCHR;
	return 0;
}


int getpid(void)
{
	return 1;
}

int isatty(int file)
{
	file = file;
        return 1;
}

int kill(int pid, int sig)
{
	pid = pid;
	sig = sig;
	errno = EINVAL;
	return -1;
}

int link(char *old, char *new)
{
	old=old;
	new=new;
	errno = EMLINK;
	return -1;
}

int _link_r(void *reent, const char *old, const char *new)
{
	reent=reent;
	old=old;
	new=new;
	errno = EMLINK;
	return -1;
}

int lseek(int file, int ptr, int dir)
{
	file = file;
	ptr = ptr;
	dir = dir;
	return 0;
}

off_t _lseek_r(void *reent,int fd, off_t pos, int whence)
{
	reent=reent;
	fd = fd;
	pos = pos;
	whence = whence;
	return 0;
}

off_t _lseek64_r(void *reent,int fd, off_t pos, int whence)
{
	reent=reent;
	fd = fd;
	pos = pos;
	whence = whence;
	return 0;
}
          
int open(const char *name, int flags, int mode)
{
	name = name;
	flags = flags;
	mode = mode;
	return -1;
}

int _open_r(void *reent, const char *file, int flags, int mode)
{
	reent=reent;
	file = file;
	flags = flags;
	mode = mode;
	return -1;
}

int _open64_r(void *reent, const char *file, int flags, int mode)
{
	reent=reent;
	file = file;
	flags = flags;
	mode = mode;
	return -1;
}

int read(int file, char *ptr, int len)
{
	file = file;
	ptr = ptr;
	len = len;
	return 0;
}

long _read_r(void *reent, int fd, void *buf, size_t cnt)
{
	reent=reent;
	fd = fd;
	buf = buf;
	cnt = cnt;	
	return 0;
}

          
caddr_t sbrk(int incr)
{
	static char *heap_end;
	char *prev_heap_end;
          
	if(heap_end == 0)
	{
		heap_end = &_end;
	}
	prev_heap_end = heap_end;
	if (heap_end + incr > stack_ptr)
	{
		errno = ENOMEM;
       		return ((char *)-1);
	}
	
	heap_end += incr;
	return (caddr_t) prev_heap_end;
}


char *_sbrk_r(void *reent, size_t incr)
{
	static char *heap_end;
	char *prev_heap_end;
        
        reent=reent;
          
	if(heap_end == 0)
	{
		heap_end = &_end;
	}
	prev_heap_end = heap_end;
	if (heap_end + incr > stack_ptr)
	{
		errno = ENOMEM;
       		return ((char *)-1);
	}
	
	heap_end += incr;
	return (caddr_t) prev_heap_end;
}


int stat(const char *file, struct stat *st)
{
	file = file;
	st->st_mode = S_IFCHR;
	return 0;
}

int _stat_r(void *reent, const char *file, struct stat *pstat)
{
	reent=reent;
	file = file;
	pstat->st_mode = S_IFCHR;
	return 0;
}

clock_t times(struct tms *buf)
{
	buf=buf;
	return -1;
}

int unlink(char *name)
{
	name = name;
	errno = ENOENT;
	return -1;
}

int _unlink_r(void *reent, const char *file)
{
	reent=reent;
	file = file;
	errno = ENOENT;
	return -1;
}

int wait(int *status)
{
	status = status;
	errno = ECHILD;	
	return -1;
}

int _wait_r(void *reent, int *status)
{
	reent=reent;
	status = status;
	errno = ECHILD;
	return -1;
}
          
int write(int file, char *ptr, int len)
{
	file = file;
	ptr = ptr;
	len = len;
	return 0;
}

long _write_r(void *reent, int fd, const void *buf, size_t cnt)
{
	reent=reent;
	fd = fd;
	buf = buf;
	cnt = cnt;
	return 0;
}


int	GetBaseOfRO(void)
{
    return (int)(&_stext);
}                    


int 	GetEndOfRO(void)
{
    return (int)(&_etext);
}

int  	GetBaseOfRW(void)
{
    return (int)(&_data);
}

int	GetEndOfRW(void)
{
    return (int)(&_edata);
}

int 	GetBaseOfZI(void)
{
    return (int)(&_start_bss);
}

int  	GetEndOfZI(void)
{
    return (int)(&_end_bss);
}

