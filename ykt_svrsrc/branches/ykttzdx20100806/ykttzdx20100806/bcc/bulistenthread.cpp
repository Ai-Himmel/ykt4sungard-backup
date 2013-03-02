// bulistenthread.cpp: implementation of the CBUListenThread class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "tcp.h"
#include "bulistenthread.h"
#include "MWThread.h"
#include "sysgvars.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBUListenThread::CBUListenThread()
{

}

CBUListenThread::~CBUListenThread()
{

}

int CBUListenThread::Run()
{
   CBULinkThread *pBULink;

   while (g_Vars.g_bToExit==false)
   {
      pBULink = g_MWThread.FindFreeBULink();
      if (pBULink==NULL)
      {
         // 目前都属于连接状态，等0.2秒后再检查
         mysleep(200);
      }
      else
      {
         if (listensock.Accept(pBULink->linksock))
         {
            pBULink->ToLink();
         }
      }
   }
   listensock.Close();
   g_LogFile.WriteLogEx(100,"BUListenThread退出!");
   return(0);
}

bool CBUListenThread::Initialize(int port)
{
   if (listensock.Create()==false)
   {
      g_LogFile.WriteLogEx(11001,"不能建立BU侦听套口!");
      return(false);
   }
   if (listensock.Listen(port)==false)
   {
      listensock.Close();
      g_LogFile.WriteLogEx(11002,"可能本机上已经使用了侦听端口:%d，因此不能建立BU侦听端口!",port);
      return(false);
   }
   return(true);
}
