#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#ifndef WIN32
#include <arpa/inet.h>
#endif
#include "cpack.h"
#include "svrlink.h"
#include "bufunc.h"
extern ST_BUNIT g_BUnit;
extern CSvrLink g_SvrLink;

int SetHeadCol(ST_CPACK *cpack, ...)
{
	va_list ap;
	int arg;
	va_start(ap, cpack);
	while ((arg = va_arg(ap, int)) >= 0)
	{
		SetParmBit(&(cpack->head), arg);
	}
	va_end(ap);
    return(g_SvrLink.SetCol(0, cpack->head.ParmBits));
}

void GetTransHandle(void *handle, char *pTransHandle)
{
	TRUSERID *ph=(TRUSERID *)handle;
	SYS_HEAD *psh = (SYS_HEAD *)ph->syshead.buf;
	char address[32];
	struct in_addr in;
	int i,j;
	memset(&in,0,sizeof(in));
	in.s_addr=psh->CRC;
	strcpy(address,inet_ntoa(in));
	for(j=0,i=0;j<6;++j)
	{
		i += sprintf(pTransHandle+i,"%04X",psh->RouterIn[j]);
	}
	for(j=0;j<6;++j)
	{
		i += sprintf(pTransHandle+i,"%04X",psh->RouterOut[j]);
	}
	sprintf(pTransHandle+i,"%01d%05d%1d%012d%s|",
		psh->RouterIndex,
		psh->Function,
		psh->FunctionPriority,
		psh->LastConnectTime,
		address
		);
}

void SetTransHandle(void *handle,char *pTransHandle)
{
    int i,offset;
    char temp[64];
#ifdef WIN32
	unsigned long in;
#else
    in_addr_t in;
#endif
    struct in_addr addr;
    TRUSERID *ph=(TRUSERID *)handle;
    char *p;
    SYS_HEAD *psh = (SYS_HEAD *)ph->syshead.buf;
    memset(temp,0,sizeof temp);
    offset = 0;
    for(i=0;i<6;++i)
    {
        memcpy(temp,pTransHandle+i*4,4);
        psh->RouterIn[i] = strtoul(temp,NULL,16);
    }
    offset = 4 * 6;
    for(i=0;i<6;++i)
    {
        memcpy(temp,pTransHandle+offset+i*4,4);
        psh->RouterOut[i] = strtoul(temp,NULL,16);
    }
    offset += 4 * 6;
    memset(temp,0,sizeof temp);
    memcpy(temp,pTransHandle+offset,1);
    psh->RouterIndex = atoi(temp);
    offset++;

    memset(temp,0,sizeof temp);
    memcpy(temp,pTransHandle+offset,5);
    psh->Function = atoi(temp);
    offset += 5;

    memset(temp,0,sizeof temp);
    memcpy(temp,pTransHandle+offset,1);
    psh->FunctionPriority = atoi(temp);
    offset++;

    memset(temp,0,sizeof temp);
    memcpy(temp,pTransHandle+offset,12);
    psh->LastConnectTime = atoi(temp);
    offset+=12;

    memset(temp,0,sizeof temp);
    p = strrchr(pTransHandle+offset,'|');
    if(p!=NULL)
    {
        memcpy(temp,pTransHandle+offset,p - (pTransHandle+offset));
    }
    else
    {
        memcpy(temp,pTransHandle+offset,strlen(pTransHandle)-offset);
    }
    
    in = inet_addr(temp);
    memcpy(&addr,&in,4);
    psh->CRC = addr.s_addr;
    
}


