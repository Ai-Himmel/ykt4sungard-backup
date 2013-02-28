/* --------------------------------------------
 * 程序名称: F9001.cpp
 * 创建日期: 2010-12-07
 * 程序作者: 汤成
 * 程序功能: 上传数据文件
 * --------------------------------------------*/
#include <stdlib.h>
#include <string.h>
#include <string>
#include "filesvr.h"


int F9001(BCCHandle &handle, char *szMsg)
{
	char cmdStr[1024] = {0};
	char cmdArg[1024] = {0};
	char inputArg[1024] = {0};
	std::string content;
	int ret;
	KSConfiguration::getInstance()->GetStringPara("cmd",cmdStr);
	KSConfiguration::getInstance()->GetStringPara("cmdarg",cmdArg);
	handle.GetStringFieldByName("vsmess",inputArg);
	if(strlen(cmdStr) == 0)
	{
		strcpy(szMsg,"未配置command");
		return -1;
	}
	strcat(cmdArg," ");
	strcat(cmdArg,inputArg);
	ret = ExecuteCommand(cmdStr,cmdArg,content);
	if(ret)
	{
		BSKLGMsg("执行任务失败");
		strcpy(szMsg,"执行任务失败");
		return -1;
	}
	handle.SetStringFieldByName("vsmess",content.c_str());
	handle.PutRow(0);
	return 0;
}

