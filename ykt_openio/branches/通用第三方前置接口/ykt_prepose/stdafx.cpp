// stdafx.cpp : 只包括标准包含文件的源文件
// ykt_prepose.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
#include "md5.h"
#include "Data.h"
#include "writelog.h"
// TODO: 在 STDAFX.H 中
// 引用任何所需的附加头文件，而不是在此文件中引用
char * addleftzero(char * ptr,int len)
{   
	char result[1024]=""; 
	size_t strl=0;
	strl=len-strlen(ptr);
	if (strl>len)
		return ptr;
	for (size_t i=0;i<strl;i++)
	{
	 strcat(result,"0");
	}
	strcat(result,ptr);
	return result;

}
char * addrightsqace(char * ptr,int len)
{   
	char result[1024]=""; 
	size_t strl=0;
	strl=len-strlen(ptr);
	if (strl>len)
		return ptr;
	strcat(result,ptr);	
	for (size_t i=0;i<strl;i++)
	{
	 strcat(result," ");
	}
	return result;

}
int file2memory(char **bufp, size_t *size, FILE *file)
{
  char *newbuf;
  char *buffer = NULL;
  size_t alloc = 512;
  size_t nused = 0;
  size_t nread;

  if(file) {
    do {
      if(!buffer || (alloc == nused)) {
        /* size_t overflow detection for huge files */
        if(alloc+1 > ((size_t)-1)/2) {
          if(buffer)
            free(buffer);
          return -1;
        }
        alloc *= 2;
        /* allocate an extra char, reserved space, for null termination */
        if((newbuf =(char*) realloc(buffer, alloc+1)) == NULL) {
          if(buffer)
            free(buffer);
          return -1;
        }
        buffer = newbuf;
      }
      nread = fread(buffer+nused, 1, alloc-nused, file);
      nused += nread;
    } while(nread);
    /* null terminate the buffer in case it's used as a string later */
    buffer[nused] = '\0';
    /* free trailing slack space, if possible */
    if(alloc != nused) {
      if((newbuf = (char*)realloc(buffer, nused+1)) != NULL)
        buffer = newbuf;
    }
    /* discard buffer if nothing was read */
    if(!nused) {
      free(buffer);
      buffer = NULL; /* no string */
    }
  }
  *size = nused;
  *bufp = buffer;
  return 0;
}

int makestr(char *type,char *data,char *rtdata)
{   size_t i=0;
	char *s=new char[4]; 
	char str[200]="";
	char *temp=rtdata;
	i=strlen(data);
    _itoa((int)i,s,10);
	i=i+strlen(s)+2;
	strcat(str,":");
	strcat(str,type);
	strcat(str,s);
	strcat(str,":");
	strcat(str,data);
	strncpy(temp,str,strlen(str));
	temp[i+1]='\0';
	delete [] s;
	return 0;

}

 void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02x",k);
	}
}
void CalcMD5(unsigned char* buf,unsigned int len,unsigned char md5[16])
{
	MD5_CTX ctx;
	memset(&ctx,0,sizeof ctx);
	MD5Init(&ctx);
	MD5Update(&ctx,buf,len);
	MD5Final(md5,&ctx);
}

char * trim(char * ptr)
{
    size_t start,end,i;
	
	if (strlen(ptr)==0)
	{
	return NULL;
	}
		if (ptr)
    {
        for(start=0; isspace(ptr[start]); start++)
            ;
        for(end=strlen(ptr)-1; isspace(ptr[end]); end--)
            ;
        for(i=start; i<=end; i++)
            ptr[i-start]=ptr[i];
        ptr[end-start+1]='\0';
        return (ptr);
    }
    else
        return NULL;
}
char *getnextstr(char *s, const char *delim,char *rtstr )
{
	 char str[1000]=""; 
	if (s==NULL)
	 return (NULL);
	if (strlen(s)==0)
		return s;
	char *buf = strstr( s, delim);
    buf = strstr( s, delim);
	if (buf==NULL)
	{
		return (NULL);;
	}
	buf[0]='\0';
    s = buf + strlen(delim);
    buf = strstr( s, delim);
	if (buf!=NULL)
	buf[0]='\0';
	strcpy(str,s);
	 s = buf + strlen(delim);
	if (buf!=NULL)
    strcpy(rtstr,s);
	return str;
}

 void reverse_str(char *ch)   /*不用中间变量*/
    {
       size_t len;
       int i;
       len = strlen(ch)-1;
      

       for(i = 0; i < len-i; i++)
       {
             ch[i] = ch[i] ^ ch[len-i];
             ch[len-i] = ch[i] ^ ch[len-i];
             ch[i] = ch[i] ^ ch[len-i];
       }
       ch[len+1] = 0;
    }
