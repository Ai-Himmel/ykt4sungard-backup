/********************************************************************
	created:	2006/12/30
	created:	30:12:2006   14:42
	filename: 	D:\proj\ksbass\bcclink\KBDClt\kdcdemo.cpp
	file path:	D:\proj\ksbass\bcclink\KBDClt
	file base:	kdcdemo
	file ext:	cpp
	author:		CHENYH
	
	purpose:	 用于测试 KBDC 接口库的主程序
*********************************************************************/

#include "stdafx.h"
//#include "KBDClt.h"
#include "kbclt.h"
#include "CIniFile.h"
#include "logfile.h"


KSYkt_Log_Writer g_logger("dbcrinfo");

typedef struct {
	string dbacc;
	string cracc;
	string dbcrtamt;
	string oper;
	string checkoper;
	string checkoperpwd;
}dbcrt_info_t;

//void call847127(KBDCHandle ch,string dbcramt,string dbacc,string cracc,string oper,string checkoper,string checkoperpwd)
int call847127(KBDCHandle ch,dbcrt_info_t *dbcrt)
{
	char eMsg[1024]; // 注意尽量给出缓存为 >=1024字节
	char fvalue[1024]; // 注意必须给出缓存为 >=1024字节
	int rtn;
	//printf("set request to 847127\n");
	
	//需在配置文件KSSICLT.lkc req项中配置功能号
	rtn = KBDCBeginRequest(ch,847127,eMsg);
	if (rtn<0)
	{
		printf("KBDCBeginRequest Error %d:%s",rtn,eMsg);
		return -1;
	}
	//printf("Set request fields\n");
	
	KBDCSetFieldValue(ch,"damt0",dbcrt->dbcrtamt.c_str());
	KBDCSetFieldValue(ch,"sbank_acc",dbcrt->dbacc.c_str());
	KBDCSetFieldValue(ch,"sbank_acc2",dbcrt->cracc.c_str());
	KBDCSetFieldValue(ch,"scust_limit",dbcrt->oper.c_str());
	KBDCSetFieldValue(ch,"scust_limit2",dbcrt->checkoper.c_str());
	KBDCSetFieldValue(ch,"semp_pwd",dbcrt->checkoperpwd.c_str());
	KBDCSetFieldValue(ch,"lvol6","9999");
	
	if (KBDCCallSvr(ch,5000,eMsg)<0)
	{
		printf("KBDCCallSvr Error:%s\n",eMsg);
		g_logger.writelog("callerr 借方账号[%s],贷方账号[%s],金额[%s]",dbcrt->dbacc.c_str(),
			dbcrt->cracc.c_str(),dbcrt->dbcrtamt.c_str());
		return -1;
	}
	
	//printf("Return Code:%d at Time:%u\n",KBDCGetRetCode(ch),GetTickCount());
	memset(eMsg,0,sizeof eMsg);
	rtn = KBDCGetRetCode(ch);
	if(rtn ==0)
	{
		//KBDCGetFieldValue(ch,"lserial1",fvalue,eMsg);
		//printf("serial[%s],",fvalue);
		KBDCGetFieldValue(ch,"vsmess",fvalue,eMsg);
		//printf("%s\n",fvalue);
		g_logger.writelog("%s",fvalue);
		return 0;
	}		
	else
	{
		KBDCGetFieldValue(ch,"vsmess",fvalue,eMsg);
		sprintf(eMsg,fvalue);
		g_logger.writelog("error 借方账号[%s,%s,%s]",dbcrt->dbacc.c_str(),
			dbcrt->cracc.c_str(),dbcrt->dbcrtamt.c_str());
		g_logger.writelog("retcode[%d]message[%s]",rtn,eMsg);
		return -1;
	}
}

char *trim(char *str)
{
	char *p1 = str;
	char *p2;

	if (str == NULL)
		return NULL;
	p2 = str + strlen(str) - 1;
	if(p2<str)
		return str;
	while (*p1 == ' ' || *p1 == '\t' || *p1 == '\n' || *p1 == '\r')
		p1++;
	while (*p2 == ' ' || *p2 == '\t' || *p2 == '\n' || *p2 == '\r')
	{
		*p2 = 0;
		p2--;
		if(p2<p1)
			break;
	}
	if(p1!=str)
		strcpy(str, p1);
	return str;
}

int main(int argc,char *argv[])
{
   char eMsg[1024];  // 注意尽量给出缓存为 >=1024字节
   ///////////////////////////////// Begin1 //////////////////////////////////////
   // 以下这个函数必须在主线程内，启用其他函数之前调用，并且必须为成功才行
#ifdef _DEBUG
   if (KBDCInit(1,"",eMsg)<0)
#else
   if (KBDCInit(0,"",eMsg)<0)
#endif
   {
      printf("KBDCInit Error:%s\n",eMsg);
      return(-1);
   }
   char file_name[1024];
   if(argc>1)
	   strcpy(file_name,argv[1]);
   else
	   strcpy(file_name,"cracc.txt");
   ////////////////////////////////// End 1 ////////////////////////////////////////

   KBDCHandle ch;
   ch = KBDCNewHandle(eMsg);
   if (ch==NULL)
   {
      printf("KBDCNewHandle Error:%s\n",eMsg);
   }
   ////////////////////////////////// SUB ////////////////////////////////////////
   // 这部分可以由各自线程去管理完成，不过KBDCHandle的创建，最好为主线程下逐个初试化好
   else
   {
	   FILE *fp = NULL;
	   string cracc,oper,checkoper,checkoperpwd;
	   int flag = 0;
	  // char accstr[32]="";	   
	  // char dbcramt[16]="";
	   char line[64]="";
	   int i,count;
	   char *token=NULL;
	   char sep[]=" ,";
	   vector<string> dbaccvec;
	   vector<string> dbcramtvec;
	   vector<string> crtaccvec;
	   char path[MAX_PATH]="";
	  // GetMoudleFileName(GetModuleHandle(NULL),path,MAX_PATH);
	   getcwd(path,MAX_PATH);
	    g_logger.openlog(path);
	   strcat(path,"\\info.ini");
	   CCIniFile inifile(path);			///必须指明全路径
	   //dbcramt = inifile.ReadString("info","money","");
	   //cracc = inifile.ReadString("info","cracc","");
	   oper = inifile.ReadString("info","oper","");
	   checkoper = inifile.ReadString("info","checkoper","");
	   checkoperpwd= inifile.ReadString("info","checkoperpwd","");
	   //flag= inifile.ReadInteger("info","flag",0);

	   fp = fopen(file_name,"r+");
	   if(!fp)
	   {
		   printf("cannot open %st\n",file_name);
		   goto L_RET;
	   }
	   count = 0;
	   while(fgets(line,64,fp))
	   {	
		   i = -1;
		   token = strtok(line,sep);
		   while(trim(token))
		   {
			   i++;
			  // printf("%s\n",token);
			   if(i ==0)
				   dbaccvec.push_back(token);
			   else if(i==1)
				   crtaccvec.push_back(token);
			   else
				   dbcramtvec.push_back(token);
			   token = strtok(NULL,sep);
		   }
		   count++;
	   }

	   fclose(fp);

	   dbcrt_info_t dbcrt;
	   dbcrt.checkoper = checkoper;
	   dbcrt.checkoperpwd = checkoperpwd;
	   dbcrt.oper = oper;
	   for (i=0;i<count;i++)
	   {
		   //printf("dbacc[%s]\n",accvec[i].c_str());
		   dbcrt.cracc = crtaccvec[i];
		   dbcrt.dbacc = dbaccvec[i];
		   dbcrt.dbcrtamt = dbcramtvec[i];
		   printf("debit[%s]crebit[%s][%s]\n",dbcrt.dbacc.c_str()
			   ,dbcrt.cracc.c_str(),dbcrt.dbcrtamt.c_str());
		  
			call847127(ch,&dbcrt);   //借一个贷多个
	   }	   
   }
   
L_RET:
   KBDCDeleteHandle(ch);
   KBDCExit();
   system("pause");
   return(0);
}