/* --------------------------------------------
 * 程序名称: F950999.cpp
 * 创建日期: 2008-1-11
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 上传数据文件
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "svrlink.h"

extern CSvrLink *g_pSvrLink;

static int do_get_packtype()
{
	ST_PACKHEAD head;
	memset(&head,0,sizeof head);
	g_pSvrLink->GetRequestHead(&head);
	int i;
	for(i = 0;i < PARMBYTES; ++i)
	{
		// 表示 st_pack
		if(head.ParmBits[i] != 0x00)
			return 0;
	}
	// 表示 st_sdpack
	return 1;
}

int F950999(TRUSERID *handle, int iRequest, ST_PACK *rpack, int *pRetCode, char *szMsg)
{
	char szfile[256];
	char full_path[512] = "";
	char temp_path[512] = "";
	int maxlen,ret,head_len;
	char temp[5] = "";
	int file_len,flag;
	FILE *fp;
	ST_SDPACK *psd;
	char *pend;
	struct stat fst;
	memset(&fst,0,sizeof fst);

	maxlen = 4096;
	
	//writelog(LOG_DEBUG,"orign file[%s]total[%d]",rpack->vsmess,rpack->lvol0);
	
	// 获取文件存放路径
	ret = GetSysParaVal(GLOBAL_UPLOAD_PATH,full_path);
	if(ret)
	{
		*pRetCode = ret;
		return -1;
	}
	// 认为是第一个请求包与最后一个请求包
	if(do_get_packtype() == 0)
	{
		// 获取文件名, 去掉路径
		file_len = rpack->lvol0;
		pend = strrchr(rpack->vsmess,'/');
		if(pend)
		{
			if(pend >= strlen(rpack->vsmess) + rpack->vsmess)
			{
				*pRetCode = E_INPUT_DATA_INVAILD;
				return -1;
			}
			strcpy(szfile,pend+1);
		}
		else
			strcpy(szfile, rpack->vsmess);
		strcat(full_path,"/");
		strcpy(temp_path,full_path);
		strcat(full_path,szfile);
		
		SetCol(handle,F_LVOL0,F_SCUST_LIMIT, F_VSMESS, 0);
		
		if(rpack->lvol1 == 0xFF)
		{
			strcat(temp_path,rpack->scust_limit);
			// 文件结束,判断文件大小
			stat(temp_path, &fst);
			if(fst.st_size != file_len)
			{
				*pRetCode = E_UPLOAD_FILE_CRC;
				writelog(LOG_DEBUG,"upload file[%s] length error,orign[%d],[%d]!"
					,full_path,file_len,fst.st_size);
				return -1;
			}
			// 重命名文件
			
			if(rename(temp_path,full_path))
			{
				*pRetCode = E_UPLOAD_CONFLICT;
				return -1;
			}
			writelog(LOG_DEBUG,"upload file[%s] success!",full_path);
		}
		else
		{
			// 第一个包删除原始文件
			unlink(full_path);
			writelog(LOG_DEBUG,"begin upload file[%s]!",full_path);
			// 生成session id
			gen_session_id(rpack->scust_limit,10);
		}
		// 返回文件名
		rpack->lvol0 = file_len;
		des2src(rpack->vsmess,szfile);
		PutRow(handle, rpack, pRetCode, szMsg);
		return 0;
	}
	// 认为是后续包
	psd = (ST_SDPACK *)rpack;
	// 取包头长度
	strncpy(temp,psd->data,4);
	temp[4] = '\0';
	head_len = strtoul(temp,NULL,16);
	if(head_len > psd->usDataLength)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		return -1;
	}
	// 文件名
	strncpy(szfile,psd->data+4,head_len-5);
	szfile[head_len-5] = '\0';
	// 包的标志
	flag = psd->data[head_len-1];
	// 文件全路径
	strcat(full_path,"/");
	strcat(full_path,szfile);
	//writelog(LOG_DEBUG,"write file[%s]",full_path);
	
	if(flag != 0xFF)
	{
		// 以二进制打开文件
		fp = fopen(full_path, "a+b");
		if (fp == NULL)
		{
			sprintf(szMsg, "Cannot open the file:<%s>!", szfile);
			*pRetCode = 9980;
		}
		else
		{
			fwrite(psd->data+head_len,psd->usDataLength-head_len,1,fp);
			fclose(fp);
			stat(full_path, &fst);
			sprintf(szMsg, "%ld", fst.st_mtime);
			if(flag == 0xFF)
			{
				// 文件上传完成,校验文件
			}
			*pRetCode = 0;
		}
	}
	SetCol(handle,F_LVOL0, F_VSMESS, 0);
	// 文件大小
	rpack->lvol0 = fst.st_size;
	des2src(rpack->vsmess, szMsg);
	PutRow(handle, rpack, pRetCode, szMsg);
	return 0;

}
