#include "stdafx.h"
#include "mypub.h"

#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#define PATHMARK  '\\'
#define MAKEPATH(a) mkdir(a)
#else
#include <sys/types.h>
#include <dirent.h>
#define PATHMARK  '/'
#define MAKEPATH(a) mkdir(a,0777)
#endif

/* ȥ�����ҿո�   */
char *mytrim(char *s)
{
	int i,len;

	len=strlen(s);
	for (i=len-1;i>=0;i--)
	{
		if ((s[i] != ' ') && (s[i] != '\t'))
			break;
		else
			s[i]=0;
	}
	for (i=0; i<len; i++)
	{
		if ((s[i] != ' ') && (s[i] != '\t'))
			break;
	}
	if (i != 0)
	{
		strncpy(s,s+i,len-i);
		s[len-i]=0;
	}
	return s;
}

// ������: *Strncpy
// ���  : ������ 2004-2-21 13:39:08
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy(char *dest,char *source,unsigned int count)
{
   strncpy(dest,source,count);
   dest[count-1]='\0';
   return(dest);
}


// ������: *Strncpy_t
// ���  : ������ 2004-2-21 13:39:12
// ����  : ��source����ิ��count�ַ���dest��������dest[count-1]����ֵΪ'\0'�ַ���������
//        ͬʱȥ�����ҿո�
// ����  : char 
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy_t(char *dest,char *source,unsigned int count)
{
   mytrim(Strncpy(dest,source,count));
   return(dest);
}


// ������: mytrim_r
// ���  : ������ 2004-2-21 13:45:29
// ����  : ����ַ����ұߵ�' '��'\t'
// ����  : char *
// ����  : char *dest
char *mytrim_r(char *dest)
{
   int i;
   i = strlen(dest)-1;
   for (;i>=0;i--)
   {
		if ((dest[i] != ' ') && (dest[i] != '\t'))
			break;
		else
			dest[i]=0;
   }
   return(dest);
}


// ������: Strncpy_rt
// ���  : ������ 2004-2-21 13:46:22
// ����  : ���Ʋ����dest�ұߵ�' '��'\t'
// ����  : char * ����dest��ָ��
// ����  : char *dest
// ����  : char *source
// ����  : size_t count
char *Strncpy_rt(char *dest,char *source,unsigned int count)
{
   Strncpy(dest,source,count);
   return(mytrim_r(dest));
}



// ������: percolate
// ���  : ������ 2003-9-24 13:38:37
// ����  : ���ַ����н��Ƿ��ַ����˵���ͬʱ����//��Ϊ����Ϊע������Ҳͬ//һ����˵�
// ����  : int �������ĳ���
// ����  : char *str In��Out
int percolate(char *str)
{
   int l,i;
   l = strlen(str)-1;
   for (;l>=0;l--)
   {
      if ((unsigned char)(str[l])<0x20)
         str[l]='\0';
      else break;
   }
   for (i=0;i<=l;i++)
   {
      if (str[i]=='/' && str[i+1]=='/') 
      {
         str[i]='\0';
         break;
      }
   }
   return(i);
}


// ������: mysleep
// ���  : ������ 2004-2-11 12:35:51
// ����  : ���߳̽���˯��״̬milliseconds����
// ����  : void 
// ����  : unsigned int milliseconds
void mysleep(unsigned int milliseconds)
{
#ifdef WIN32
   Sleep(milliseconds);
#else
#ifdef AIX
	 struct timespec delay;
	 delay.tv_sec =0;
	 delay.tv_nsec = milliseconds*1000;
    pthread_delay_np(&delay);
#else
    usleep(milliseconds*1000);
#endif
#endif
}

// ������: *getfmttime
// ���  : ������ 2003-10-14 11:23:47
// ����  : ��tm��ʱ��ת��Ϊ����ʱ��ĸ�ʽ���ַ���������ϵͳ��non-thread-safe
// ����  : char * ��ʽ�����ַ���ָ��, NULL ��ʹ���ڲ���̬�ռ��Ÿ�ʽ�����ַ�����
// ����  : time_t *ptm ����Ҫת����ʱ�� ==NULL ��Ϊת��ʱʱ���
// ����  : int fmttype 
/*
            0 : hh:mm:ss
            1 : MM/DD-hh:mm:ss
            2 : YYYY/MM/DD-hh:mm:ss
            3 : YYYYMMDD
            4 : hhmmss
            ���� : YYYYMMDDhhmmss
*/
// ����  : char *outstr ����ַ����Ļ��棬=NULL��ʹ���ڲ��ľ�̬���棬�䳤����Ҫ��fmttype����
char *getfmttime(void *ptm,int fmttype,char *outstr)
{
   static char tstr[80];
   struct tm tmloc;
   time_t timet;
   
   if (ptm==NULL)
   {
      ptm = &timet;
      time(&timet);
   }
   else
   {
      memcpy(&timet,ptm,sizeof(timet));
   }
   if (outstr==NULL)
   {
      outstr = tstr;
   }
   //localtime_r(&tm,&tmloc);
   memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
   if (fmttype==0)
   {
      // %H:%M:%S:
      strftime(outstr,79,"%H:%M:%S",&tmloc);
   }
   else if (fmttype==1)
   {
      // %m/%d-%H:%M:%S
      strftime(outstr,79,"%m/%d %H:%M:%S",&tmloc);
   }
   else if (fmttype==2)
   {
      strftime(outstr,79,"%Y/%m/%d %H:%M:%S",&tmloc);
   }
   else if (fmttype==3)
   {
      strftime(outstr,79,"%Y%m%d",&tmloc);
   }
   else if (fmttype==4)
   {
      strftime(outstr,79,"%H%M%S",&tmloc);
   }
   else 
   {
      strftime(outstr,79,"%Y%m%d%H%M%S",&tmloc);
   }
   return(outstr);
}


void OutErrorFile(char *efilename,char *msg,char *sourcefile,int lineno)
{
   FILE *fp;
   fp = fopen(efilename,"a+t");
   if (fp!=NULL)
   {
      fprintf(fp,
         "%s FILE:%s LINENO:%d -- [%s]\n",
         getfmttime(NULL,1,NULL),
         sourcefile,
         lineno,
         msg
         );      
      fclose(fp);
   }
}

void DebugFileOut(char *dfilename,char *msg,char *sourcefile,int lineno)
{
   char *pmsg;

/* ****** Updated by CHENYH at 2004-4-28 9:58:39 ****** 
   char szDRMMsg[1025];
   if (strlen(msg)<900) 
   {
      sprintf(szDRMMsg,"BU%d:%s",iThisProcID,msg);
      pmsg = szDRMMsg;
   }
   else
*/
   {
      pmsg = msg;
   }
   OutErrorFile(dfilename,pmsg,sourcefile,lineno);
   if (pmsg[strlen(pmsg)-2]=='\n')
   {
      printf("%s",pmsg);
   }
   else
   {
      printf("%s\n",pmsg);
   }
}

#ifdef WIN32
unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1)
{
   return(tc2-tc1);
}
#else
unsigned int tc2_tc1(unsigned int tc2,unsigned int tc1)
{
   if (tc2<tc1)
   {
      return(86400000-tc1+tc2);
   }
   else
   {
      return(tc2-tc1);
   }
}
unsigned int GetTickCount()
{
   struct timeval CurrentTime;
   gettimeofday(&CurrentTime, NULL);
   return ((CurrentTime.tv_sec * 1000) + (CurrentTime.tv_usec / 1000));   
}

#endif


// ������: RemoveOverdueFile
// ���  : ������ 2004-4-6 9:52:41
// ����  : �����ָ����Ŀ¼path_mark�µ��޸���������overdue���������ļ�
// ����  : int ɾ�����ļ���
// ����  : char *path_mark ָ����Ŀ¼�������ҪӦ�ð���Ŀ¼�ָ�������MS����ϵͳ��'\\' ��������'/'��
// ����  : char *ext �ļ���չ�������� '.'
// ����  : int overdue  ָ�����ڵ�����
int RemoveOverdueFile(char *path_mark,char *ext,int overdue)
{
   int nfs=0;
   char szfile[1024];
   time_t odtime;
   if (overdue<1)
      return(0);
   odtime = time(NULL)-(overdue*86400);   
   sprintf(szfile,"%s*%s",path_mark,ext);
#ifdef WIN32
   struct _finddata_t fd;
   int dh;
   dh = _findfirst(szfile,&fd);
   if (dh==-1) 
      return(0);
   do
   {
      if ((odtime>fd.time_write) && strstr(fd.name,ext)!=NULL)
      {
         sprintf(szfile,"%s%s",path_mark,fd.name);
         remove(szfile);
         nfs++;
      }
   } while (_findnext(dh,&fd)!=-1);
   _findclose(dh);
#else
   DIR *dp;
   struct dirent *dirp;
   struct stat fst;
   dp = opendir(path_mark);
   if (dp==NULL) 
      return(0);
   while ((dirp=readdir(dp))!=NULL)
   {
      sprintf(szfile,"%s%s",path_mark,dirp->d_name);
      if (strstr(dirp->d_name,ext)!=NULL 
         && stat(szfile,&fst)==0 
         && odtime>fst.st_mtime)
      {
         remove(szfile);
         nfs++;
      }
   }
   closedir(dp);
#endif
   return(nfs);
}
