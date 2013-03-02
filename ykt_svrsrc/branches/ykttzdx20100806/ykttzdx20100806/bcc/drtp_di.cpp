/********************************************************************
	created:	2004/03/17
	created:	17:3:2004   14:50
	filename: 	E:\proj\goldmem\ksbcc\drtp_di.cpp
	file path:	E:\proj\goldmem\ksbcc
	file base:	drtp_di
	file ext:	cpp
	author:		CHENYH
	
	purpose:	为了新通讯平台版本   _DRTP_V4
*********************************************************************/
// 使用本程序，必须定义 _DRTP_V4, 否则，版本会有出入的

#include "stdafx.h"
#include "mypub.h"
#include "drtp_di.h"

#include "drtplib.h"

#include "drtperr.h"



#define SYSHEAD_OFF 14  // 为了能够兼容各类接口（期货，证券集中交易等）


void CopyString(const char *source,char *dest,int destsize)
{
   int i;
   if (dest==NULL||destsize<=1||source==NULL)
      return;
   for (i=0;i<destsize-1;i++)
   {
      if (source[i]=='\0') break;
      dest[i]=source[i];
   }
   dest[i]='\0';
}

void reverse(void *data,int len)
{
   unsigned char *p=(unsigned char *)data;
   unsigned char buf[16];
   int i;
   
   memcpy(buf,data,len);
   for (i=0;i<len;i++)
   {
      p[i]=buf[len-i-1];
   }
}


bool DRTPInitialize(int nrouters)
{
   long errcode;   
   char errmsg[300];   
   if (DrtpInit(&errcode,errmsg))
      return(true);   
   else
      return(false);
}

void DRTPUninitialize()
{
   DrtpExit();
}

CDRTPClient::CDRTPClient()
{
   classdataid = DRTPCLIENTID;
   handle = -1;
}

CDRTPClient::~CDRTPClient()
{
   Close();
}

bool CDRTPClient::Connect(char *routerip,int port,char *szMsg,int nMsgSize)
{
   long errcode;
   char errmsg[300];
   CPMUTEX amutex(&m_mutex);
   
   Close();

   handle=DrtpConnect(routerip,port,&errcode,errmsg);
   
   if (handle <= 0)      
   {
      CopyString(errmsg,szMsg,nMsgSize);      
      return false;
   }
   return(true);
}

bool CDRTPClient::Close()
{
   if (handle>0)
   {
      DrtpClose(handle);
      handle = -1;
   }
   return(true);
}

bool CDRTPClient::Send(unsigned short branchno, unsigned short function, void *senddata, int senddatalen, char *szMsg, int nMsgSize, bool bDesign)
{
   BOOL bret;
   long errcode;   
   char errmsg[300];   
   TAG_DRTPHANDLE drtphandle;
   CPMUTEX amutex(&m_mutex);
   
   if (bDesign)      
   {
      if (!DrtpGetHandle(handle,&drtphandle,&errcode,errmsg))         
      {
         Close();
         CopyString(errmsg,szMsg,nMsgSize);
         return false;
      }
      bret=DrtpSendMessage((char *)senddata,senddatalen,&errcode,errmsg,&drtphandle);
   }
   else      
   {
      bret=DrtpPostMessage(3,branchno,function,(char *)senddata,senddatalen,&errcode,errmsg,handle);      
   }
   
   if (bret==FALSE)
   {
      Close();
      CopyString(errmsg,szMsg,nMsgSize);
      return(false);
   }
   return true;
}

int CDRTPClient::Receive(void *recvbuf, int &recvbufsize, char *szMsg, int nMsgSize, int wtime)
{
	BOOL bret;
	long len;
	TAG_DRTPHANDLE drtphandle;
	long errcode;
	char errmsg[300];

	if (wtime < 0)
	{
		bret=DrtpReadMessage((char *)recvbuf,recvbufsize,&len,handle,&drtphandle,&errcode,errmsg);
	}
	else
	{
		bret=DrtpReadMessage((char *)recvbuf,recvbufsize,&len,handle,&drtphandle,&errcode,errmsg,wtime);
	}
	if (bret == TRUE)
	{
		recvbufsize=len;
		return len;
	}
	else
	{
		CopyString(errmsg,szMsg,nMsgSize);
		if (errcode == ERROR_SOCKET)
		{
         Close();
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

bool CDRTPClient::IsOpenning()
{
   return(handle>0);
}


////////////////////////////////////////////////////////////////////////////////////////////////
CDRTPServer::CDRTPServer()
{
   classdataid = DRTPSERVERID;
   handle = -1;
}

CDRTPServer::~CDRTPServer()
{
   Close();
}

bool CDRTPServer::Connect(char *routerip, int port, int funcount, unsigned short *functions, char *szMsg, int nMsgSize)
{
	long errcode;
	char errmsg[300];
	long function;
	int i;
   Close();
	handle=DrtpConnect(routerip,port,&errcode,errmsg);
	if (handle <= 0)
	{
		CopyString(errmsg,szMsg,nMsgSize);
		return false;
	}

	for (i=0; i<funcount; i++)
	{
		function=*(functions+i);
		if (DrtpAddFunction(function,&errcode,errmsg,handle) == FALSE)
		{
			CopyString(errmsg,szMsg,nMsgSize);
			DrtpClose(handle);
			return false;
		}
	}
   return(true);
}

bool CDRTPServer::Close()
{
   if (handle>0)
   {
      DrtpClose(handle);
      handle = -1;
   }
   return(true);
}

bool CDRTPServer::Send(SYS_HEAD *pHead, void *senddata, int senddatalen, char *szMsg, int nMsgSize)
{
	long errcode;
	char errmsg[300];
	TAG_DRTPHANDLE drtphandle;
	BOOL bret;
   char *ph = (char *)pHead;
	memcpy(drtphandle.buf,ph+SYSHEAD_OFF,sizeof(drtphandle.buf));
	bret=DrtpSendMessage((char *)senddata,senddatalen,&errcode,errmsg,&drtphandle);
	if (bret == FALSE)
	{
      Close();
		CopyString(errmsg,szMsg,nMsgSize);
		return false;
	}
	return true;
}

int CDRTPServer::Receive(SYS_HEAD *pHead, void *recvbuf, int &recvbufsize, char *szMsg, int nMsgSize, int wtime)
{
	BOOL bret;
	long len;
	TAG_DRTPHANDLE drtphandle;
	long errcode;
	char errmsg[300];
   char *ph = (char *)pHead;
	if (wtime == 0)
	{
		bret=DrtpReadMessage((char *)recvbuf,recvbufsize,&len,handle,&drtphandle,&errcode,errmsg);
	}
	else
	{
		bret=DrtpReadMessage((char *)recvbuf,recvbufsize,&len,handle,&drtphandle,&errcode,errmsg,wtime);
	}
	memcpy(ph+SYSHEAD_OFF,&drtphandle,sizeof(drtphandle));
	if (bret == TRUE)
	{
      recvbufsize = len;
		return len;
	}
	else
	{
		CopyString(errmsg,szMsg,nMsgSize);
		if (errcode == ERROR_SOCKET)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

bool CDRTPServer::IsOpenning()
{
   return(handle>0);
}


