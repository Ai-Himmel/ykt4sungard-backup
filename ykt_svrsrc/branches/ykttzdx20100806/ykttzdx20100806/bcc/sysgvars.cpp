// sysgvars.cpp: implementation of the SYSGVARS class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "mypub.h"
#include "slist.h"
#include "profile.h"
#include "string.h"
#include "logfile.h"
#include "sysgvars.h"
#include "comstru.h"
#include "MWThread.h"
#include "KSLog.h"

SYSGVARS g_Vars;
CLogFile g_LogFile;
TBDefine *g_BDefines=NULL;
CKSLog   g_KSLog;

typedef struct
{
   int reqno;  // 需要记录日志的功能号
} ST_FLOGLIST;

ST_FLOGLIST *g_FLogList=NULL;

#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

//////////////////////////////////////////////////////////////////////
bool UpdateCheckPath(char *path, char *defsub)
{
   char tmp[256];
   int l;

   if (path[0]=='\0')
   {
      if (getcwd(tmp,sizeof(tmp))!=NULL)
      {
         sprintf(path,"%s/%s",tmp,defsub);
      }
   }
   if (access(path,0)!=0)
   {
#ifdef WIN32
      if (mkdir(path)!=0)
#else
      if (mkdir(path,0777)!=0)
#endif
      {
         printf("Cannot create direct <%s> - error:%d <%s>!\n",path,errno,strerror(errno));
         return(false);
      }
   }
   l = strlen(path);
   if (path[l-1]!='/')
   {
      strcat(path,"/");
   }
   return(true);
}


bool LoadIniFile(char *inifile)
{
   TIniFile tf;
   CSList tmplist;
   int i;
   char szBuf[1024];
   char sztmp[256];
   printf("Begin to read ini-file:%s...\n",inifile);
   if (!tf.Open(inifile))
   {
      sprintf(szBuf,"不能打开配置文件<%s>\n",inifile);
      DEBUG_RUNTIME_MSGOUT(szBuf);
      return(false);
   }

   g_Vars.iThisID = tf.ReadInt("COMMON","ID",1);
   g_Vars.iBaseFuncNo = tf.ReadInt("COMMON","BASEFUNCNO",29900);
   g_MWThread.nRouters = tf.ReadInt("COMMON","SERVERCOUNT",1);
   if (g_MWThread.nRouters>MAXROUTERS)
      g_MWThread.nRouters = MAXROUTERS;
   //g_bShowLog = (tf.ReadInt("COMMON","DEBUG",1)!=0);
   tf.ReadString("COMMON","FORWARD_PATH","",g_Vars.szForwardPath,sizeof(g_Vars.szForwardPath)-1);
   UpdateCheckPath(g_Vars.szForwardPath,"forward");
   g_MWThread.m_forwardclear = tf.ReadInt("COMMON","FORWARD_CLEAR",300);
   if (g_MWThread.m_forwardclear<30)
      g_MWThread.m_forwardclear = 30;
   g_MWThread.m_bToPush = (tf.ReadInt("COMMON","PUSHSUPPORT",1)!=0);
   g_MWThread.m_patime = tf.ReadInt("COMMON","PATIME",10);
   tf.ReadString("COMMON","PUSHDBFS_PATH","",g_Vars.szPushDbfPath,sizeof(g_Vars.szPushDbfPath)-1);
   UpdateCheckPath(g_Vars.szPushDbfPath,"pdbfs");

   tf.ReadString("COMMON","LOGPATH","log",sztmp,250);
   g_KSLog.SetFileMode(sztmp);
   g_KSLog.OpenLogFile();
   
   i = tf.ReadInt("COMMON","LOGOVERDUE",10);

   // 清除过期的日志文件和推送数据文件
   g_KSLog.RemoveOverdueKLogFile(i);
   g_LogFile.RemoveOverdueLogFile(i);
   RemoveOverdueFile(g_Vars.szPushDbfPath,".dbf",i);

   for (i=0;i<g_MWThread.nRouters;i++)
   {
      sprintf(sztmp,"SERVER%d",i+1);
      tf.ReadString("COMMON",sztmp,"127.0.0.1:2000",szBuf,255);
      if (!(tmplist.FillStrings(szBuf,':')))
      {
         sprintf(szBuf,"%s [COMMON] param %s error",inifile,sztmp);
         DEBUG_RUNTIME_MSGOUT(szBuf);
         return(false);
      }
      if (tmplist.GetCount()<2)
      {
         sprintf(szBuf,"%s [COMMON] param %s error[xxx.xxx.xxx.xxx:port]\n",inifile,sztmp);
         DEBUG_RUNTIME_MSGOUT(szBuf);
         return(false);
      }

      strcpy(g_MWThread.tRouters[i].IP,tmplist.GetAt(0));
      g_MWThread.tRouters[i].Port = atoi(tmplist.GetAt(1));
      g_MWThread.tRouters[i].tSFuncNos[0] = g_Vars.iBaseFuncNo;
      g_MWThread.tRouters[i].tSFuncNos[1] = g_Vars.iBaseFuncNo+g_Vars.iThisID;
   }
   
   for (i=0;i<PRIORITIES;i++)
   {
      sprintf(sztmp,"FIFOPROC%d",i+1);
      g_MWThread.bRPQProcFIFO[i] = (tf.ReadInt("COMMON",sztmp,0)!=0);      
   }

   g_MWThread.bToWriteAppInfo = (tf.ReadInt("COMMON","WRITEAPPINFO",0)!=0);
   
   g_Vars.iBULinkPort = tf.ReadInt("COMMON","BUPORT",6666);

   g_MWThread.rptimeout = tf.ReadInt("COMMON","REQTIMEOUT",10000);
   if (g_MWThread.rptimeout>120000)
      g_MWThread.rptimeout = 120000;

   if (g_MWThread.rptimeout>0 && g_MWThread.rptimeout<1000)
      g_MWThread.rptimeout = 1000;
   
   g_MWThread.freewait = tf.ReadInt("COMMON","FREEWAIT",5);
   if (g_MWThread.freewait>300)
      g_MWThread.freewait=300;

   // NOVBUWARN: 定义在多少时间内没有等待处理（空闲）的BU，则向前端发送信息提示，缺省为3000毫秒
   g_MWThread.nNoVBUWarnDelay = tf.ReadInt("COMMON","NOVBUWARN",3000);

   tf.ReadString("COMMON","BDFILE","function.lst",g_Vars.szBDefineFile,sizeof(g_Vars.szBDefineFile)-1);

   g_ShowLogLevel = g_MWThread.bumsgshowlevel = tf.ReadInt("COMMON","LOGSHOW",10000);



   g_MWThread.nBUnits = tf.ReadInt("COMMON","BUNITS",0);

   tf.ReadString("COMMON","BUPROG","",g_MWThread.szBUProg,sizeof(g_MWThread.szBUProg)-1);
   if (strlen(g_MWThread.szBUProg)<=0)
      g_MWThread.nBUnits = 0;
   if (g_MWThread.nBUnits>MAXBULINKS)
      g_MWThread.nBUnits = MAXBULINKS;
   tf.ReadString("COMMON","BUPATH","bunit",g_MWThread.szBUPath,sizeof(g_MWThread.szBUPath)-1);

   tf.ReadString("COMMON","FLOGFILE","flog.txt",sztmp,250);
   tf.Close();
   
   LoadFLogListFile(sztmp); 

   if (LoadBDefineFile(g_Vars.szBDefineFile)>0) 
      return(true);
   else
   {
      sprintf(szBuf,"在指定的功能列表文件(%s)中没有具体的功能表，或不能打开该文件!",g_Vars.szBDefineFile);
      return(false);
   }
}

int LoadBDefineFile(char *bdfile)
{
   FILE *fp;
   char szbuf[400];
   int ilen;
   int n=0;
   CSList tmplst;
   if (g_BDefines!=NULL)
      delete []g_BDefines;
   g_BDefines = NULL;
   fp = fopen(bdfile,"rt");
   if (fp!=NULL)
   {
      ilen = 0;
      while (fgets(szbuf,sizeof(szbuf),fp)!=NULL)
      {
         ilen++;
      }
      g_BDefines = new TBDefine[ilen+1];
      if (g_BDefines==NULL)
      {
         fclose(fp);
         return(-2);
      }
      int i;
      TBDefine *pbd = g_BDefines;
      fseek(fp,0,SEEK_SET);
      for (i=0;i<ilen;i++)
      {
         fgets(szbuf,sizeof(szbuf),fp);

         if (percolate(szbuf)>0 && tmplst.FillStrings(szbuf,'|'))
         {
            if (tmplst.GetCount()>=4)
            {
               pbd->RequestType=atoi(tmplst.GetAt(0));
               strcpy(pbd->szRTName,tmplst.GetAt(1));
               strcpy(pbd->szProgrammer,tmplst.GetAt(2));
               pbd->iPriority = atoi(tmplst.GetAt(3));
               if (pbd->iPriority<1)
                  pbd->iPriority = 1;
               else if (pbd->iPriority>3)
                  pbd->iPriority = 3;
               pbd->bStoped=false;
               pbd->nSuccess=0;
               pbd->nFail=0;
               pbd->dTakentime=0;
               pbd->nTt_max=0;
               pbd->nTt_min=0;
               if (pbd->RequestType>0)
               {
                  pbd++;
                  n++;
               }
            }
         }
      }
      memset(pbd,0,sizeof(TBDefine));
      pbd->RequestType = 0;  // Mark as end of the list
      fclose(fp);
      return(n);
   }
   return(-1);   
}

// 函数名: FindBPFunction
// 编程  : 陈永华 2004-2-11 22:50:46
// 描述  : 根据功能号，查询对应的功能表项
// 返回  : int <0:没有找到；>=0:在功能表中对应的序号
// 参数  : unsigned int reqtype ：功能号
int FindBPFunction(unsigned int reqtype)
{
   int i;
   if (reqtype==0||g_BDefines==NULL)
      return(-2);
   for (i=0;;i++)
   {
      if (g_BDefines[i].RequestType==0)
         break;
      if (g_BDefines[i].RequestType==reqtype)
         return(i);
   }
   return(-1);
}

// 函数名: ListBPFunctions
// 编程  : 陈永华 2004-2-11 22:41:18
// 描述  : 显示功能表中的统计或导出到文件中
// 返回  : int 登记的功能个数
// 参数  : char *bpfile ： NULL 或 “”则在屏幕上显示，否则导出到指定文件中
int ListBPFunctions(char *bpfile,int wmode)
{
   int i;
   TBDefine *pbd=g_BDefines;
   FILE *fp=NULL;
   //char szmsg[20];
   if (bpfile!=NULL && bpfile[0]!='\0')
   {
      if (wmode==0)
         fp = fopen(bpfile,"wt");
      else
         fp = fopen(bpfile,"a+t");
   }
   if (fp==NULL)
   {
      //      12345678901234567890123456789012345678901234567890123456789012345678901234567890
      //      123456 12345 1234 1234567890 1234567890 123456789012345 123456 123456
      printf("funcno|class|active|   success|   failure|           time| t_max| t_min\n");
   }
   else if (wmode)
   {
      fprintf(fp,"Function Status at %d (TickCount=%u)---\n",g_Vars.g_iHhmmss,GetTickCount());
      fprintf(fp,"funcno|class|active|success|failure|           time| t_max| t_min|Description       | Programmer   \n");
   }
   for (i=0;;i++,pbd++)
   {
      if (pbd->RequestType==0)
         break;
      if (fp==NULL)
      {
         printf("%6u|%5d|    %c|%10u|%10u|%15.0lf|%6u|%6u\n",
            pbd->RequestType,
            pbd->iPriority,
            pbd->bStoped?'N':'Y',
            pbd->nSuccess,
            pbd->nFail,
            pbd->dTakentime,
            pbd->nTt_max,
            pbd->nTt_min
            );
      }
      else if (wmode)
      {
         /* ****** Updated by CHENYH at 2004-4-7 16:59:15 ****** 
         增加一种便于浏览的状态信息输出格式：
         */
         fprintf(fp,"%6u|%5d|     %c|%7u|%7u|%15.0lf|%6u|%6u|%s|%s\n",
            pbd->RequestType,
            pbd->iPriority,
            pbd->bStoped?'N':'Y',
            pbd->nSuccess,
            pbd->nFail,
            pbd->dTakentime,
            pbd->nTt_max,
            pbd->nTt_min,
            pbd->szRTName,
            pbd->szProgrammer
            );
      }
      else
      {
         // 作为独立输出到功能文件中：
         fprintf(fp,"%u|%s|%s|%d|%c|%u|%u|%.0lf|%u|%u\n",
            pbd->RequestType,
            pbd->szRTName,
            pbd->szProgrammer,
            pbd->iPriority,
            pbd->bStoped?'N':'Y',
            pbd->nSuccess,
            pbd->nFail,
            pbd->dTakentime,
            pbd->nTt_max,
            pbd->nTt_min
            );
      }
   }
   if (fp!=NULL)
      fclose(fp);
   return(i);
}

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


time_t getlastaccesstime(char *file)
{
   time_t t;
   struct stat buf;
   if (stat(file,&buf)==0)
   {
      t = buf.st_atime;
      if (t<buf.st_ctime)
         t = buf.st_ctime;
      if (t<buf.st_mtime)
         t = buf.st_mtime;
      return(t);
   }
   else
      return(0);  
}


/* ****** Updated by CHENYH at 2004-3-11 22:00:43 ****** 
void printbulog(unsigned short bloglen,int buid,RP_BCCLOG *pbl)
{
   printf("BU%dLog:%c-%d<%s> dlen%d\n",
      buid,pbl->logtype,pbl->logid,pbl->logtext,bloglen-sizeof(RP_BCCLOG)
      );
}
*/


// 函数名: LoadFLogListFile
// 编程  : 陈永华 2004-3-16 14:51:21
// 描述  : 装载功能日志记录清单文件
// 返回  : int 
// 参数  : char *szFLLFile
int LoadFLogListFile(char *szFLLFile)
{
   FILE *fp;
   char szbuf[400];
   int n=0;
   int i;
   if (g_FLogList!=NULL)
      delete []g_FLogList;
   g_FLogList = NULL;
   fp = fopen(szFLLFile,"rt");
   if (fp!=NULL)
   {
      while (fgets(szbuf,sizeof(szbuf),fp)!=NULL)
         n++;
      g_FLogList = new ST_FLOGLIST[n+1];
      if (g_FLogList==NULL)
      {
         fclose(fp);
         return(-2);
      }
      fseek(fp,0,SEEK_SET);
      for (i=0;i<n;)
      {
         if (fgets(szbuf,sizeof(szbuf),fp)==NULL) break;
         g_FLogList[i].reqno = atoi(szbuf);
         if (g_FLogList[i].reqno>0) 
            i++;
      }
      n = i;
      fclose(fp);
      g_FLogList[n].reqno = 0;
   }
   else 
   {
      n = 0;
   }
   return(n);
}



// 函数名: NeedToSaveLog
// 编程  : 陈永华 2004-3-16 16:19:36
// 描述  : 检查是否该功能需要记录到日志文件中
// 返回  : bool 
// 参数  : int reqno
bool NeedToSaveLog(int reqno)
{
   ST_FLOGLIST *plist=g_FLogList;
   while (plist!=NULL && plist->reqno>0)
   {
      if (reqno==plist->reqno)
         return(true);
      plist++;
   }
   return(false);
}
