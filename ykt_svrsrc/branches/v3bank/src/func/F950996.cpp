/* --------------------------------------------
 * 程序名称: F950996.sqc
 * 创建日期: 2009-07-28
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能: 上送对账文件
 * --------------------------------------------*/

#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "cpack.h"
#include "bupub.h"
#include "tcp.h"


int F950996(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	//ST_SDPACK *psd;
	ST_SDPACK *psd=(ST_SDPACK *)rPack;
	char sCommand[128] = "";
	char filepath[256]="";
	char sFileName[256]="";
	char chkdate[9] = "";
	FILE *fp;
	struct stat fst;
	memset(&fst,0,sizeof fst);


	des2src(filepath,rPack->vsvarstr0);
	des2src(sFileName,rPack->vsmess);
	des2src(chkdate,rPack->sdate1);			// 对账时间

	/* 重命名文件
	将银行chkdate 那天的对账文件，改名为 sFileName
	*/
	sprintf(sCommand,"bank_accchk_rename.sh %s %s %s",filepath,sFileName,chkdate);

	if(system(sCommand) != 0)
	{
		writelog(LOG_ERR,"rename error[%s]", sCommand);
		sprintf(szMsg, "rename error[%s]", sCommand);
		return  E_TRANS_UNKNOW_ERROR;
	}
	
	//sprintf(filepath,"%s",sFileName);
	
	//stat(sFileName, &fst);
	//writelog(LOG_DEBUG,"filelen[%d]", fst.st_size);

	int maxlen = sizeof(ST_PACK) - 4;
	//writelog(LOG_DEBUG,"max len[%d]", maxlen);
	if (maxlen > 4000)
		maxlen = 4000;
	fp = fopen(sFileName, "rb");
	if (fp == NULL)
	{
		sprintf(szMsg, "Cannot open the file:<%s>!", filepath);
		writelog(LOG_ERR,szMsg);
		return  9999;
	}
	while (!feof(fp))
	{	
		psd->usDataLength = fread(psd->data, 1, maxlen, fp);
		PutRowData(rPack);
	}
	fclose(fp);		
	unlink(sFileName);
	return 0;
}

