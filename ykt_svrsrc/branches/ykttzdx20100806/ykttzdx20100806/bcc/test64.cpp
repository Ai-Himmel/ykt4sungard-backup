#include "stdafx.h"
#include "mypub.h"
#include "KSLog.h"
#include "sysgvars.h"

SYSGVARS g_Vars;

void SetDateTime()
{
   time_t timet;
   struct tm tmloc;
   time(&timet);
   memcpy(&tmloc,localtime(&timet),sizeof(struct tm));
   g_Vars.g_iHhmmss = tmloc.tm_sec+(tmloc.tm_hour*100+tmloc.tm_min)*100;
   g_Vars.g_iToday = ((tmloc.tm_year+1900)*100+tmloc.tm_mon+1)*100+tmloc.tm_mday;
   sprintf(g_Vars.g_szHhmmss,"%06d",g_Vars.g_iHhmmss);
   sprintf(g_Vars.g_szToday,"%08d",g_Vars.g_iToday);
}

int iThisProcID=0;

#define LOOPS 10000000
int main()
{
   char buf[1024];
   char s[4];
   unsigned int tb,t1,t2;
   int i;

   printf("Test int64 and double operating speed:\n");
   tb = GetTickCount();
   for (i=0;i<LOOPS;i++)
   {
#ifdef WIN32
      __int64 a,b,c;
#else
      long long a,b,c;
#endif
      a = 10000000-i;
      b = 100000+a;
      c = a*b;
   }
   t1 = GetTickCount()-tb;
   printf("int64 operating took %u MS\n",t1);
   tb = GetTickCount();
   for (i=0;i<LOOPS;i++)
   {
      double a,b,c;
      a = 10000000-i;
      b = 100000+a;
      c = a*b;
   }
   t2 = GetTickCount()-tb;
   printf("double operating took %u MS\n",t2);

   while (1)
   {
      printf("Input test string to trim:");
      if (gets(buf)==NULL) return 0;
      Strncpy(s,buf,sizeof(s));
      mytrim(buf);
      printf("After trim:<%s>\n",buf);
      if (strcmp(buf,"testklg")==0) break;
      if (strcmp(buf,"exit")==0) return(2);
   }
   CKSLog klg;
   SetDateTime();
   klg.SetFileMode("testlog");
   klg.OpenLogFile();

   klg.WriteLog(1000,"Test Message!");
   klg.CloseLogFile();
   return(0);
}