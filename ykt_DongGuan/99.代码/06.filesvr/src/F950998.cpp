/* --------------------------------------------
 * 程序名称: F950998.cpp
 * 创建日期: 2010-12-7
 * 程序作者: 汤成
 * 程序功能:  下传数据文件
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "filesvr.h"

int F950998(BCCHandle &handle, char *szMsg)
{
	char szfile[256]={0};
	char full_path[512] = "";
	char data[4096];
	int maxlen,ret,is_del,read_len;
	FILE *fp;
	struct stat fst;
	memset(&fst,0,sizeof fst);

	handle.GetIntFieldByName("lvol0",&is_del);
	// 获取文件名, 去掉路径
	handle.GetStringFieldByName("vsmess",szfile);
	
	maxlen = sizeof(data);
	// 获取文件存放路径
	ret = KSConfiguration::getInstance()->GetStringPara("downloaddir",full_path);
	if(ret)
	{
		strcpy(szMsg,"未配置主目录");
		return ret;
	}
	strcat(full_path,FILE_SEP);
	strcat(full_path,szfile);
	// 以二进制打开文件
	fp = fopen(full_path, "rb");
	if (fp == NULL)
	{
		sprintf(szMsg, "Cannot open the file:<%s>!", full_path);
		return 9980;
	}
	else
	{
		while (!feof(fp))
		{
			read_len = fread(data, 1, maxlen, fp);
			if(read_len > 0)
			{
				BSSetRawRecord(handle.bcc_handle_,data,read_len);
				handle.PutRow(0);
			}
		}
		fclose(fp);
		stat(full_path, &fst);
		sprintf(szMsg, "%ld", fst.st_mtime);
		if(is_del == 1)
		{
			// 删除原始文件
			unlink(full_path);
		}
	}
	//SetCol(handle,F_LVOL0, F_VSMESS, 0);
	// 文件大小
	handle.SetIntFieldByName("lvol0",fst.st_size);
	handle.SetStringFieldByName("vsmess",szMsg);
	handle.PutRow(0);
	return 0;
}

