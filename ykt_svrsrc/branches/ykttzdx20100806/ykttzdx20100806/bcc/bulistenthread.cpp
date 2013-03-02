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
         // Ŀǰ����������״̬����0.2����ټ��
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
   g_LogFile.WriteLogEx(100,"BUListenThread�˳�!");
   return(0);
}

bool CBUListenThread::Initialize(int port)
{
   if (listensock.Create()==false)
   {
      g_LogFile.WriteLogEx(11001,"���ܽ���BU�����׿�!");
      return(false);
   }
   if (listensock.Listen(port)==false)
   {
      listensock.Close();
      g_LogFile.WriteLogEx(11002,"���ܱ������Ѿ�ʹ���������˿�:%d����˲��ܽ���BU�����˿�!",port);
      return(false);
   }
   return(true);
}
