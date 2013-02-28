/* --------------------------------------------
 * ��������: F9001.cpp
 * ��������: 2010-12-07
 * ��������: ����
 * ������: �ϴ������ļ�
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
		strcpy(szMsg,"δ����command");
		return -1;
	}
	strcat(cmdArg," ");
	strcat(cmdArg,inputArg);
	ret = ExecuteCommand(cmdStr,cmdArg,content);
	if(ret)
	{
		BSKLGMsg("ִ������ʧ��");
		strcpy(szMsg,"ִ������ʧ��");
		return -1;
	}
	handle.SetStringFieldByName("vsmess",content.c_str());
	handle.PutRow(0);
	return 0;
}

