/********************************************************************
	created:	2004/03/31
	created:	31:3:2004   22:34
	filename: 	E:\proj\goldmem\ksbcc\ksbcc.cpp
	file path:	E:\proj\goldmem\ksbcc
	file base:	ksbcc
	file ext:	cpp
	author:		CHENYH
	
	purpose:	
   Revision 1.1.1.0  CYH
   2004-3-31 22:29:35 CYH ���� �Ż�CKSLog�еĲ��ֺ�����  ���ڴ����KLG�ļ���ʽ��
       Ϊ�˷�ֹ��ͬһ��Ŀ¼�£����еڶ���ʵ������KLGFile�е����ݴ�����LoadIniFile֮ǰ��������
          ��ˣ���Ҫ�����������ֵĴ���������LoadIniFile֮ǰ���������Ƿ��Ѿ�������ʵ��
                      
   2004-4-6  14:30:00 CYH --  ���
	1. Debug�� ��չ��־��Ϣ���ȵ����ƣ���256��չ����8K
	2. ���CLogFile���ļ���֯��ʽ���ɹ̶���־�ļ���Ϊ�ձ������־�ļ�
	3. ����ʱ��ɾ�����ڵ�LOG��־�ļ���KLG��־�ļ��Լ����������ļ�

             16:54 CYH
   BCC����KLG�Ĺ����ܹ���ѭintel��ʽ���Է�LogView���ܶ�ȡIBM AIX��KLG�ļ�

   2004-4-7  16:44 CYH
             ����ϵͳ״̬�ļ������ʽ��
             ���Ӱ汾��� ksbcc ver ����


   2004-4-20 
            13:00:00 CYH
               ����С�ͻ�����Big-endian�ֽ�����ˣ���Ҫ��CRCУ�鲿����reverse��ֵ��Ƚ�

            13:24:26 CYH
             ������HPС�ͻ�������֣�Program terminated with signal 10, Bus error
             64λ���������ϳ���Warning: unaligned access to 0x???????????, ip=0x??????????
             �޸��˳��������������䣬��Ϊmemcpy�����

  2004-4-30 
            10:30:00 CYH
            �������߳��У���Ϊȱ�����ˡ�A������Z�����֣����¿��ܻ����Щ��¼��һ�����Ͷ�����
            QBIN������ʱ���ֵ����⣬�޸��ˡ�

*********************************************************************/
#include "stdafx.h"
#include "mypub.h"
#include "sysgvars.h"
#include "logfile.h"
#include "MWThread.h"
#include "KSLog.h"

int iThisProcID=0;    // 0 as BCC ID
extern CKSLog g_KSLog;

#ifdef WIN32
int mygetch()
{
   if (kbhit())
      return(getch());
   else return(0);
}
#else
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include "sharememory.h"
CShareMemory g_shm;

#include "sharememory.cpp"

void sig_term(int signo)
{
	g_Vars.g_bToExit = true;
}


void setnoblockgetch()
{
   int oldstatus;
   oldstatus = fcntl(0,F_GETFL);
   fcntl(0,F_SETFL,oldstatus|O_NDELAY);
}

int mygetch()
{
   int rtn;
   char kbuf[2];
   rtn = read(0,kbuf,1);
   if (rtn<=0) return(0);
   else return(kbuf[0]);
}
#endif

#define STATUSFILE   "sysstatus.lst"
#define VERSION      "KSBCC Version 1.22 Copyright 2003-2004 Kingstar  ChenYH, On 2004-4-30"

int main(int argc,char *argv[])
{
   bool brtn;
   //int rtn;
   printf("%s\n",VERSION);
   SetDateTime();
   g_LogFile.Open("tlog");
#ifndef WIN32
   g_pubctrl = (shm_pubctrl *)g_shm.openshare("KSBCC",8,g_pubctrl);
   if (g_pubctrl==NULL)
   {
      printf("Cannot open share memory, Exit!\n");
      return(-99);
   }
#endif
   // Ϊ�˷�ֹ��ͬһ��Ŀ¼�£����еڶ���ʵ������KLGFile�е����ݴ�����LoadIniFile֮ǰ��������
   // ��ˣ���Ҫ��������
/* ****** Updated by CHENYH at 2004-3-31 22:29:35 ****** 
   if (argc<2)
      brtn = LoadIniFile("ksbcc.ini");
#ifndef WIN32
   else if (strcmp(argv[1],"show")==0)
   {
      g_pubctrl->bToShow = true;
      printf("You may list the system status from <%s>!\n",STATUSFILE);
      return(0);
   }
   else if (strcmp(argv[1],"stop")==0)
   {
      g_pubctrl->exitcode = true;
      return(0);
   }
#endif
   else
      brtn = LoadIniFile(argv[1]);

   if (!brtn)
      return(-100);
#ifndef WIN32
   if (g_pubctrl->iRunningCode==RUNNINGCODE && g_pubctrl->exitcode==false)
   {
      printf("This KSBCC have be started! EXIT now!\n");
      return(-101);
   }
*/
#ifndef WIN32
   if (argc>1)
   {
      if (strcmp(argv[1],"show")==0)
      {
         g_pubctrl->bToShow = true;
         printf("You may list the system status from <%s>!\n",STATUSFILE);
         return(0);
      }
      else if (strcmp(argv[1],"stop")==0)
      {
         if (g_pubctrl->iRunningCode==RUNNINGCODE)
            printf("The running KSBCC will be exited!\n");
         else
            printf("No running KSBCC under this enviroment\n");
         g_pubctrl->exitcode = true;
         return(0);
      }
      else if (memcmp(argv[1],"ver",3)==0)
      {
         printf("%s\n",VERSION);
         return(0);
      }
   }
   if (g_pubctrl->iRunningCode==RUNNINGCODE && g_pubctrl->exitcode==false)
   {
      printf("One KSBCC instance has been started !\n");
      return(-101);
   }
#endif
   if (argc<2)
      brtn = LoadIniFile("ksbcc.ini");
   else
      brtn = LoadIniFile(argv[1]);
   if (!brtn)
   {
      printf("Load Ini File Error! STOP!\n");
      return(-100);
   }

#ifndef WIN32
#ifndef _GDBTEST_
   // ��Ϊ��̨�������У�
   if(fork()!=0) exit(0);
   setpgrp();
   if(fork()!=0) exit(0);
   umask(0);
   signal(SIGPIPE, SIG_IGN);
   signal(SIGHUP, SIG_IGN);
   signal(SIGINT, SIG_IGN);
   signal(SIGTERM, sig_term);
   signal(SIGUSR1, SIG_IGN);
#endif
   g_pubctrl->iThisID = g_Vars.iThisID;
   g_pubctrl->iBaseFuncNo = g_Vars.iBaseFuncNo;
   g_pubctrl->main_pid = getpid();
   g_pubctrl->main_start_time = time(NULL);
   g_pubctrl->main_stop_time = 0;
   g_pubctrl->bToShow = false;
   g_pubctrl->exitcode = false;
   g_pubctrl->iRunningCode = RUNNINGCODE;
#endif

   g_MWThread.Reset();

   g_Vars.g_bToExit = false;
   if (g_MWThread.CreateThread())
      g_Vars.g_bToExit = false;
   else
      g_Vars.g_bToExit = true;
   mysleep(500);

/* ****** Updated by CHENYH at 2004-3-27 0:03:00 ****** 
#ifndef WIN32
   setnoblockgetch();
#endif
*/
   int loops=0;
   while (g_Vars.g_bToExit==false)
   {
      SetDateTime();
#ifdef WIN32
      switch (mygetch())
      {
      case '?':
      case 'h':
      case 'H':
         printf("(%s %s) Help Infomation:\n",argv[0],argc>1?argv[1]:"ksbcc.ini");
         printf("%s\n",VERSION);
         printf("\t ? h H: to display this Help information\n");
         printf("\t x X: to eXit\n");
         printf("\t f F: to reload business information File\n");
         printf("\t l L: to List business information into file:functions.lst\n");
         printf("\t d D: to Display business information\n");
         printf("\t b B: to display BULink information\n");
         printf("\t r R: to display Router information\n");
         printf("\t q Q: to display reqpackQueue information\n");
         printf("\t a A: to list all information into file:sysstatus.lst\n");
         printf("Enter your select:\n");
         break;
      case 'x':
      case 'X':
         g_Vars.g_bToExit = true;  // ask to exit...
         break;
      case 'L':
      case 'l':
         ListBPFunctions("function.lst");
         break;
      case 'D':
      case 'd':
         ListBPFunctions();
         break;
      case 'B':
      case 'b':
         g_MWThread.ListBULinkStatus();
         break;
      case 'R':
      case 'r':
         g_MWThread.ListRouterStatus();
         break;
      case 'Q':
      case 'q':
         g_MWThread.ListRPQStatus();
         break;
      case 'A':
      case 'a':
         ListBPFunctions(STATUSFILE,1);
         g_MWThread.ListBULinkStatus(STATUSFILE,1);
         g_MWThread.ListRouterStatus(STATUSFILE,1);
         g_MWThread.ListRPQStatus(STATUSFILE,1);
         break;
      case 'F':
      case 'f':
         LoadBDefineFile(g_Vars.szBDefineFile);
         break;
      }
#else
      if (g_pubctrl->bToShow)
      {
         g_MWThread.ListBULinkStatus(STATUSFILE,0);
         ListBPFunctions(STATUSFILE,1);
         g_MWThread.ListRouterStatus(STATUSFILE,1);
         g_MWThread.ListRPQStatus(STATUSFILE,1);
         g_pubctrl->bToShow = false;
      }
      else if (g_pubctrl->exitcode)
      {
         g_Vars.g_bToExit = true;
      }
#endif
      g_MWThread.CheckStartupBU();
      if (g_MWThread.m_forwardclear>0)
         g_MWThread.RemoveForwardFiles(NULL,g_MWThread.m_forwardclear);
      if (++loops>=100)
      {
         g_KSLog.FlushToKLogFile();
         loops=0;
      }
   }
   g_LogFile.WriteLogEx(0,"ϵͳ׼���˳�...");
   while (g_MWThread.IsStoped()==false)
   {
      mysleep(500);
   }
#ifndef WIN32
   g_pubctrl->iRunningCode=0;
   g_pubctrl->exitcode=true;
   g_shm.closeshare(g_pubctrl);
#endif
   g_LogFile.WriteLogEx(0,"ϵͳ�����˳���");
   g_LogFile.Close();
   printf("%s\n",VERSION);
   printf("KSBCC exit now -- ϵͳ�����˳���");
   return(0);   
}

