#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <arpa/inet.h>
#include "cpack.h"
#include "XPack.h"
#include "svrlink.h"
#include "bufunc.h"
#include "pubfunc.h"
extern ST_BUNIT g_BUnit;
extern CSvrLink g_SvrLink;

extern "C" void GetPack(ST_CPACK *pack,char *buf);


CXPack *pXPack=(CXPack *)GetDefaultXPack();

int GetCpackDataString(ST_CPACK *cpack,char *buf)
{
	if(NULL==cpack)
		return -1;
	int iLastFidx;
	char sFieldValue[512];
	
	const ST_PDATALIST *PDataList;
	PDataList=pXPack->GetPackDef(iLastFidx);
	for(int i=0;i<iLastFidx;i++)
	{
		if(pXPack->IsValidField(&(cpack->head),i))
		{
			pXPack->GetFieldValue(&(cpack->pack),i,sFieldValue);
			sprintf(buf+strlen(buf),"%s:%d:%s\n",PDataList[i].szName,strlen(sFieldValue),sFieldValue);
		}
	}
	return 0;
}
int GetCpackDataString(ST_PACK *pack,char *buf)
{
	if(NULL==pack)
		return -1;
	int iLastFidx;
	char sFieldValue[512];
	buf[0]=0;
	ST_CPACK* cpack=(ST_CPACK*)((char*)pack-sizeof(ST_PACKHEAD));
	
	const ST_PDATALIST *PDataList;
	PDataList=pXPack->GetPackDef(iLastFidx);
	for(int i=0;i<iLastFidx;i++)
	{
		if(pXPack->IsValidField(&(cpack->head),i))
		{
			pXPack->GetFieldValue(&(cpack->pack),i,sFieldValue);
			sprintf(buf+strlen(buf),"%s:%d:%s\n",PDataList[i].szName,strlen(sFieldValue),sFieldValue);
		}
	}
	return 0;
}
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

int CopyHeadCol(ST_PACK* rPack,ST_CPACK* sPack)
{
	int iLastFidx;
	ST_CPACK* cpack=(ST_CPACK*)((char*)rPack-sizeof(ST_PACKHEAD));
	
	pXPack->GetPackDef(iLastFidx);
	for(int i=0;i<iLastFidx;i++)
	{
		if(pXPack->IsValidField(&(cpack->head),i))
		{
			SetParmBit(&(sPack->head),i);
		}
	}
	return(g_SvrLink.SetCol(0, sPack->head.ParmBits));
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
    //writelog(LOG_ERR,"addr[%s]",address);
    /*
    i = sprintf(pTransHandle,"%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d%04d",
        psh->RouterIn[0],
        psh->RouterIn[1],
        psh->RouterIn[2],
        psh->RouterIn[3],
        psh->RouterIn[4],
        psh->RouterIn[5],
        psh->RouterOut[0],
        psh->RouterOut[1],
        psh->RouterOut[2],
        psh->RouterOut[3],
        psh->RouterOut[4],
        psh->RouterOut[5]);
        */
    for(j=0,i=0;j<6;++j)
    {
        i += sprintf(pTransHandle+i,"%04X",psh->RouterIn[j]);
        //writelog(LOG_DEBUG,"routein[%d]=%X",j,psh->RouterIn[j]);
    }
    for(j=0;j<6;++j)
    {
        i += sprintf(pTransHandle+i,"%04X",psh->RouterOut[j]);
        //writelog(LOG_DEBUG,"routeout[%d]=%d",j,psh->RouterIn[j]);
    }
    //writelog(LOG_ERR,"route len[%d]",i);
    sprintf(pTransHandle+i,"%01d%05d%1d%012d%s|",
        psh->RouterIndex,
        psh->Function,
        psh->FunctionPriority,
        psh->LastConnectTime,
        address
      );
    //writelog(LOG_ERR,"RouterIndex[%d]Function[%d]FunctionPriority[%d]Conn[%d]",
    //    psh->RouterIndex,psh->Function,psh->FunctionPriority,psh->LastConnectTime);
}

void SetTransHandle(void *handle,char *pTransHandle)
{
    int i,offset;
    char temp[64];
    in_addr_t in;
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


