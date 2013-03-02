#include <string.h>
#include <time.h>
#include "osutil.h"
#include "hxdev/hxkqinfo.h"
#include "ksglobal.h"
#include "ksgateway.h"

int FileParse::getOffset()
{
	FILE *fp = NULL;
	char lineNum[10];
	fp = fopen(m_offsetFileName,"a+");
	if(!fp)
		return -1;
	fgets(lineNum,10,fp);
	m_offset = atol(lineNum);
	fclose(fp);
	return 0;
}

int FileParse::setOffset(long offset)
{
	FILE *fp = NULL;
	char lineNum[10];
	fp = fopen(m_offsetFileName,"w");
	if(!fp)
		return -1;
	sprintf(lineNum,"%ld",m_offset);
	fputs(lineNum,fp);
	fclose(fp);
	return 0;
}
int FileParse::getKqInfo(std::vector<KQINFO> &vecKqInfo)
{
	FILE *fp = NULL;
	if (strlen(m_fileName) <= 0)
		return -1;

	getOffset();

	fp = fopen(m_fileName,"r");
	if(!fp)
		return -1;	
	
	fseek(fp,m_offset,SEEK_SET);
	char strBuf[50];
	KQINFO kqInfo;	
	memset(&kqInfo,0,sizeof(kqInfo));
	while(fgets(strBuf,50,fp))
	{
		memcpy(kqInfo.phyCardID,strBuf,10);
		memcpy(kqInfo.date,strBuf+10,8);
		memcpy(kqInfo.time,strBuf+18,6);
		vecKqInfo.push_back(kqInfo);
	}
	fseek(fp,0,SEEK_END);
	m_offset = ftell(fp);
	fclose(fp);

	if (m_offset > 320000)
		moveKqFile();
	
	setOffset(m_offset);

	moveCardInfoDir();
	return 0;
}
int FileParse::moveCardInfoDir()
{
	char date[8] ="";
	getDate(date);
	if(atoi(date)%2 == 0)		//两天移动一次
	{
		char oldDir[MAX_PATH] = "";
		char newDir[MAX_PATH]="";
		sprintf(oldDir,"%s\\cardinfo",KsgGetGateway()->GetConfig()->_basedir.c_str());
		sprintf(newDir,"%s\\cardinfolog",KsgGetGateway()->GetConfig()->_basedir.c_str());
		if(test_log_dir(newDir))
			return -1;
		sprintf(newDir,"%s\\cardinfo_%s",newDir,date);
		if(rename(oldDir,newDir))
			return -1;
	}
	
	return 0;
}
char *FileParse::getDate(char date[8])
{
	std::string timestamp;
	KSGOSUtil::GetTimestamp(timestamp);
	memcpy(date,timestamp.c_str(),6);
	return date;
}

int FileParse::moveKqFile()
{
	char date[8]="";
	char newFile[MAX_PATH]="";
	sprintf(newFile,"%s\\kqlog\\%d\\%s_%s",KsgGetGateway()->GetConfig()->_basedir.c_str(),m_termID,m_fileName,getDate(date));
	if(rename(m_fileName,newFile))
		return -1;

	m_offset = 0;
	return 0;
}
int FileParse::test_log_dir(const char *log_dir)
{
	int create_dir = 0;
#ifdef WIN32
	DWORD dir_attr;
	dir_attr = GetFileAttributes(log_dir);
	if(dir_attr == INVALID_FILE_ATTRIBUTES )
		create_dir = 1;
	else if(dir_attr != FILE_ATTRIBUTE_DIRECTORY)
		return 0;
	if(create_dir)
	{
		if(!CreateDirectory(log_dir,NULL))
			return -1;
	}
#else
#endif
	return 0;
}

int FileParse::writeLog(std::vector<KQINFO> &vecKqInfo)
{
	char date[8]="";
	char filePath[MAX_PATH]="";
	sprintf(filePath,"%s\\kqlog",KsgGetGateway()->GetConfig()->_basedir.c_str());

	if(test_log_dir(filePath))
		return -1;

	sprintf(filePath+strlen(filePath),"\\%d",m_termID);
	if(test_log_dir(filePath))
		return -1;

	sprintf(filePath+strlen(filePath),"\\%s.txt",getDate(date));
	FILE *fp = fopen(filePath,"a+");
	if(fp == NULL)
		return -1;
	char buf[64]="";
	std::vector<KQINFO>::iterator iter;
	std::string timestamp;
	KSGOSUtil::GetTimestamp(timestamp);
	for (iter = vecKqInfo.begin();iter != vecKqInfo.end();iter++ )
	{
		sprintf(buf,"collectTime:%s,phyCardID:%s,phyID:%08X,date:%s,time:%s\n",timestamp.c_str(),iter->phyCardID,atol(iter->phyCardID),iter->date,iter->time);
		fputs(buf,fp);
	}
	fclose(fp);
	return 0;
}