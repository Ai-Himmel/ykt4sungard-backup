/* --------------------------------------------
 * 创建日期: 2010-11-25
 * 程序作者: 闻剑
 * 版本信息: 3.0.0.0
 * 程序功能: 下传对账文件
 * --------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpack.h"
#include "bupub.h"
#include "tcp.h"
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

int FPutFile(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	//ST_SDPACK *psd;
	char szCmd[256] = "";
	char filepath[256]="";
	char sFileName[256]={0};
	char chkdate[9] = "";
	FILE *fp;
	struct stat fst;
	memset(&fst,0,sizeof fst);


	/* 重命名文件
	将银行chkdate 那天的对账文件，改名为 sFileName
	*/
	sprintf(szCmd,"getbankchkfile.sh %s",rPack->vsmess);

	if((fp = popen(szCmd, "r"))==NULL)
	{
		sprintf(szMsg, "exec cmd[%s] error",szCmd);
		return -1;
	}
	char line[1024]={0};
	char lastline[1024]={0};
	while(!feof(fp))
	{
		memset(line,0,sizeof(line));
		if(fgets(line, sizeof(line),fp)==NULL)
		{
			if(feof(fp))
				break;
			else
			{
			
				pclose(fp);
				return -1;
			}
		}
		strcpy(lastline,line);
		if(strstr(line,"filename:")!=0)
		{
			strcpy(sFileName,line+strlen("filename:"));
			break;
		}		
	}
	pclose(fp);
	if(strlen(sFileName)<1)
	{
		strcpy(szMsg,lastline);
		return -1;
	}
	trim(sFileName);
	printf("downfile:[%s]\n",sFileName);
	stat(sFileName, &fst);
	printf("filelen:%d\n", fst.st_size);
	int maxlen = sizeof(ST_PACK) - 4;
	if (maxlen > 4000)
		maxlen = 4000;
	fp = fopen(sFileName, "rb");
	if (fp == NULL)
	{
		sprintf(szMsg, "Cannot open the file:<%s>!", sFileName);
		return  9999;
	}
	ST_SDPACK *psd=(ST_SDPACK *)rPack;
	if(fst.st_size>0)
	{
		while (!feof(fp))
		{	
			psd->usDataLength = fread(psd->data, 1, maxlen, fp);
			PutRowData(rPack);
		}
	}
	fclose(fp);		
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_VSVARSTR0,F_VSMESS, 0);
	outPack->lvol0 = fst.st_size;
	strcpy(outPack->vsvarstr0, sFileName);
	strcpy(outPack->vsmess, szMsg);
	PutRow(handle, outPack, pRetCode, szMsg);
	return 0;
}
