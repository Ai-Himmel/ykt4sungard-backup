/** 
 * 模块名				一卡通通用前置系统
 * 文件名				kcc_util.c
 * 文件实现功能			功能函数
 * 作者					汤成
 * 版本					V1.0
 * 日期					2005-07-13
 * 备注
 * $Id: kcc_util.c 25 2005-08-19 02:52:56Z cash $
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#ifdef SUNOS
#include <netinet/in.h>
#endif
#include <sys/types.h>
#include <sys/time.h>
#include <sys/file.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>

#include "kcc_util.h"
#include "kcc_conf.h"
#include "parseconf.h"
#include "md5.h"

char file_name[250];
int file_line;

void kcc_get_pos(char * filename,int lineno)
{
	kcc_strcpy(file_name,filename);
	file_line = lineno;
}
void kcc_log_msg(int log_level,const char * fmt,...)
{
	va_list args;
	char msg[4096] = "";
	char body[2048] = "";
	char head[512] = "";
	/*
#ifndef DEBUG
if(log_level == LOG_DEBUG)
{
return;
}
#endif
*/
	switch(g_debug_level)
	{
	case 1:
	case 2:
		// 只输出　LOG_ERR
		if(log_level != LOG_ERR)
		{
			return;
		}
		break;
	case 3:
	case 4:
		// 只输出 LOG_ERR & LOG_INFO
		if(log_level != LOG_ERR && log_level != LOG_INFO)
		{
			return;
		}
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	default:
		break;
	}
	sprintf(head,"F[%s]L[%d]P[%d]",file_name,file_line,getpid());
	kcc_strcpy(msg,head);
	va_start(args,fmt);
	vsprintf(body,fmt,args);
	va_end(args);
	kcc_strcat(msg,body);
	syslog(log_level,msg,strlen(msg));
}
void kcc_die(int exit_code,const char * fmt,...)
{
	va_list args;
	va_start(args,fmt);
	kcc_write_log(LOG_DEBUG,fmt,args);
	va_end(args);
	printf("%s exit code[%d]\n",KCC_NAME,exit_code);
	exit(exit_code);
}

void kcc_show_help()
{
	char msg[] = " YKT common client \n" \
		"options : \n" \
		"\t-d : run as daemon\n" \
		"\t-t timeval : reload timeval\n";
	printf("%s",msg);
}

void kcc_memcpy(void * dest,void *src ,int len)
{
	if(len == 0)
		return;
	memcpy(dest,src,len);	
}

void kcc_memset(void * src,int value,int len)
{
	if( src == NULL )
		return;
	if(len <= 0)
		return;
	memset(src,value,len);
}

int kcc_memcmp(void *src,void *dest,int len)
{
	if(len == 0)
		return 0;
	return memcmp(src,dest,len);
}

void kcc_memclr(void * src,int len)
{
	kcc_memset(src,0,len);
}

void * kcc_alloc(size_t size)
{
	if(size == 0)
		return NULL;
	return malloc(size);
}

void kcc_free(void *p)
{
	if( p == NULL )
		return;
	free(p);
}

void * kcc_realloc(void *p,size_t size)
{
	if(size == 0)
		return p;
	return realloc(p,size);
}

void kcc_sleep(int seconds)
{
	sleep(seconds);
}

int kcc_strlen(const char * src)
{
	if( src == NULL )
		return 0;
	return strlen(src);
}
char* kcc_strcpy(char * dest,const char *src)
{
	if(dest == NULL)
		return dest;
	if(src == NULL)
		return dest;
	return strcpy(dest,src);
}
char* kcc_strncpy(char * dest,const char * src,int len)
{
	if(dest == NULL)
		return dest;
	if(src == NULL)
		return dest;
	if(len == 0)
		return dest;
	return strncpy(dest,src,len);
}
int kcc_strcmp(const char * src,const char *dest)
{
	if(src == NULL)
		return 1;
	if(dest == NULL)
		return -1;
	return strcmp(src,dest);
}
int kcc_strncmp(const char * src,const char * dest,int len)
{
	if(src == NULL)
		return -1;
	if(dest == NULL)
		return 1;
	if(len == 0)
		return 0;
	return strncmp(src,dest,len);

}
char * kcc_strdup(const char * src)
{
	if( src == NULL )
		return NULL;
	return strdup(src);
}

char * kcc_strcat(char * dest,const char *src)
{
	if( dest == NULL )
		return NULL;
	if( src == NULL )
		return dest;
	return strcat(dest,src);
}

void kcc_str_trim(char * src,char * dest,char * trim)
{
	if(src == NULL || dest == NULL || trim == NULL )
		return;
	int i,j,k;
	int trim_len = kcc_strlen(trim);
	j = kcc_strlen(src);
	while(j > 0)
	{
		for(k = 0;k < trim_len;++k)
			if(trim[k] == src[j])
				break;
		if(k == trim_len)
			break;
		--j;
	}
	i = 0;
	while(i < j)
	{
		for(k = 0;k < trim_len;++k)
			if(trim[k] == src[i])
				break;
		if(k == trim_len)
			break;
		++i;
	}
	if( i == j )
		return;
	kcc_strncpy(dest,src+i,j-i);
	dest[j-i] = '\0';
}

int kcc_toupper(int c)
{
	return toupper(c);
}

void kcc_toupper_str(char * src)
{
	int len,i;
	len = kcc_strlen(src);
	for(i = 0;i < len;++i)
		src[i] = kcc_toupper(src[i]);
}

int kcc_atoi(const char * src)
{
	if(src == NULL)
		return 0;
	return atoi(src);
}

int kcc_str_equals(const char * src,const char * dest)
{
	return (kcc_strcmp(src,dest) ==0);
}

char * kcc_read_file_str(FILE * fp)
{
	long file_len;
	long i;
	char * p;
	// get file length
	if(fseek(fp,0L,SEEK_END))
		kcc_die(1,"read file error!");
	file_len = ftell(fp);
	p = (char*)kcc_alloc(file_len + 1);
	// read file into the buffer
	i = 0;
	fseek(fp,0L,SEEK_SET);
	while(!feof(fp) && i < file_len)
	{
		i += fread(p+i,1,1024,fp);
	}
	*(p+file_len) = '\0';
	// return pointer to the buffer
	return p;
}

char* kcc_strtok(char* token,const char* delimit)
{
	if(delimit == NULL)
		return NULL;
	return strtok(token,delimit);
}

unsigned long kcc_strtoul(const char* begin,char** end,int base)
{
	if(begin == NULL && *end == NULL)
		return 0;
	return strtoul(begin,end,base);
}

char * kcc_str_readline(char * buf,unsigned int pos)
{
	int i,count;
	char * line;
	i = pos;
	while(1)
	{
		if(buf[i] == '\n' || buf[i] == '\0')
		{
			count = i - pos;
			line = (char*)kcc_alloc(count+1);
			kcc_strncpy(line,buf+pos,count);
			line[count] = '\0';
			return line;
		}
		++i;
	}
	return NULL;
}

int kcc_add_path_sep(char * path,int len)
{
	int dlen = len;
	if(len <= 0)
		return 0;
	if(path[len - 1] != FILE_SEPERATOR)
	{
		path[len] = FILE_SEPERATOR;
		dlen++;
		dlen++;
	}
	path[dlen] = '\0';
	return dlen;
}

int kcc_trim_path_sep(char * path,int len)
{
	int dlen = len;
	if(path[len - 1] == FILE_SEPERATOR)
	{
		dlen--;
		path[dlen] = '\0';
	}
	return dlen;
}

void kcc_activate_nonblock(int fd)
{
	int ret;
	/*
	int curr_flags = fcntl(fd,F_GETFL);
	if ( curr_flags < 0 )
	{
		kcc_write_log(LOG_DEBUG,"get file descriptor flag error!");
		return;
	}
	curr_flags |= O_NONBLOCK;
	*/
	ret = fcntl(fd,F_SETFL,O_NONBLOCK);
	if( ret != 0 )
	{
		kcc_write_log(LOG_DEBUG,"set file descriptor flag error!");
	}
}

void kcc_deactivate_nonblock(int fd)
{
	int ret;
	int curr_flags = fcntl(fd,F_GETFL);
	if ( curr_flags < 0 )
	{
		kcc_write_log(LOG_DEBUG,"get file descriptor flag error!");
		return;
	}
	curr_flags &= ~O_NONBLOCK;
	ret = fcntl(fd,F_SETFL,curr_flags);
	if( !ret )
	{
		kcc_write_log(LOG_DEBUG,"set file descriptor flag error!");
	}
}

long kcc_get_tick_count()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int kcc_sock_connect_to(char * ip,int port)
{
	int sock;
	struct sockaddr_in svradd;
	struct hostent * host;

	sock = socket(AF_INET,SOCK_STREAM,0);
	if( sock == -1 )
	{
		kcc_write_log(LOG_ERR,"create socket error");
		return -1;
	}
	kcc_memclr(&svradd,sizeof(svradd));
	host = gethostbyname(ip);

	if( host == NULL )
	{
		kcc_write_log(LOG_ERR,"get host by name error[%s]",ip);
		return -1;
	}

	kcc_memcpy(&svradd.sin_addr,(struct in_addr*)host->h_addr,
			   sizeof(svradd.sin_addr));
	svradd.sin_port = htons((short)port);
	svradd.sin_family = AF_INET;

	kcc_write_log(LOG_INFO,"[%s]connecting ..... ",ip);
	alarm(g_connect_timeout);
	if(connect(sock,(struct sockaddr*)&svradd,sizeof(svradd)) != 0)
	{
		alarm(0);
		close(sock);
		kcc_write_log(LOG_ERR,"connect to server error![%s][%d]",ip,port);
		return -1;
	}
	alarm(0);
	kcc_write_log(LOG_INFO,"connect to server success!!![%s][%d]",
				  ip,port);
	return sock;
}

void kcc_md5(const char * buf,int len,char * md5)
{
	MD5_CTX ctx;
	MD5Init(&ctx);
	MD5Update(&ctx,(unsigned char*)buf,len);
	MD5Final((unsigned char*)md5,&ctx);
}

int kcc_get_file_md5(FILE * fp,char * md5)
{
	MD5_CTX ctx;
	char buf[1024] = "";
	int readlen;

	MD5Init(&ctx);
	if(fseek(fp,SEEK_SET,0L) == -1)
	{
		return -1;
	}
	while(!feof(fp))
	{
		readlen = fread(buf,1,sizeof(buf),fp);
		if( readlen > 0 )
		{
			MD5Update(&ctx,(unsigned char*)buf,readlen);
		}
	}
	MD5Final((unsigned char*)md5,&ctx);
	return 0;
}

void kcc_hex2src(const char * src,int len,char * value)
{
	int i,j;
	j = 0;
	for(i = 0;i < len;++i)
		j += sprintf(value+j,"%02X",(unsigned char)src[i]);
}

int kcc_sigprocmask(sigset_t * oldset,int how,...)
{
	va_list list;
	sigset_t sig;
	int signum;

	sigemptyset(&sig);
	va_start(list,how);
	signum = va_arg(list,int);
	while( signum > 0 )
	{
		sigaddset(&sig,signum);
		signum = va_arg(list,int);
	}
	va_end(list);
	return sigprocmask(how,&sig,oldset);
}

int kcc_lock_file(const char * filename,int function)
{
	FILE * fp;
	fp = fopen(filename,"w");
	if( NULL == fp )
	{
		kcc_write_log(LOG_CRIT,"create lock file error!");
		return -1;
	}
	if(lockf(fileno(fp),F_TEST,0L) != 0)
	{
		kcc_write_log(LOG_INFO,"pid file has been locked");
		goto L_END;
	}
	if(lockf(fileno(fp),function,0L))
	{
		kcc_write_log(LOG_ERR,"lock pid file error!");
		goto L_END;
	}
	return 0;
L_END:
	fclose(fp);
	return -1;

}

int kcc_test_lock_file(const char* filename)
{
	FILE * fp;
	int ret;
	if((fp = fopen(filename,"w")) == NULL)
	{
		return -1;
	}
	ret = lockf(fileno(fp),F_TEST,0L);
	fclose(fp);
	return ret;
}
void kcc_set_signal(int signum,void (*handler)(int n))
{
	struct sigaction act,oldact;
	act.sa_handler = handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;//SA_INTERRUPT;
	sigaction(signum,&act,&oldact);
}
int kcc_write_buf(int fd,void * buf,int len)
{
	int writelen;
	int haswrite;
	writelen = 0;
	haswrite = 0;
	while(1)
	{
		writelen = write(fd,((char*)buf)+haswrite,len - haswrite);
		if( writelen <= 0 )
		{
			return haswrite;
		}
		haswrite += writelen;
		if( haswrite > len )
		{
			// maybe write data more than buffer
			return -1;
		}
	}
}

int kcc_read_buf(int fd,void * buf,int len)
{
	int readlen;
	int hasread;
	readlen = 0;
	hasread = 0;
	while(1)
	{
		readlen = read(fd,((char*)buf)+hasread,len - hasread);
		if( readlen <= 0)
		{
			return hasread;
		}
		hasread += readlen;
		if( hasread > len )
		{
			// maybe read more than buffer length
			return -1;
		}
	}
}
void do_default_alarm_handle(int signum)
{
	// do nothing
}
void kcc_setup_alarm_handle()
{
	kcc_set_signal(SIGALRM,do_default_alarm_handle);
}

int kcc_get_file_ext(const char* filename,char * ext,int * extlen)
{
	char * pos;
	if((pos = strrchr(filename,'.')) != NULL)
	{
		kcc_strcpy(ext,pos+1);
		if(extlen != NULL)
		{
			*extlen = kcc_strlen(ext);
		}
		return 0;
	}
	return -1;
}
