
#include "osutil.h"
#include "ksgexception.h"
#include <boost/filesystem/path.hpp>
#include <ace/OS.h>
#include <ace/ACE.h>
#include "md5.h"

std::string KSGOSUtil::_exec_file_path = "";

void KSGOSUtil::Program_name(const char *prg)
{
	_exec_file_path = prg;
}
void KSGOSUtil::GetBaseDir(std::string& dir)
{
	/*
#ifdef WIN32
	char modulepath[1024 + 1] = "";
	int len = GetModuleFileName(NULL,modulepath,1024);
	if(len > 0)
	{
		modulepath[len] = '\0';
		dir = modulepath;
		return;
	}
	throw KSGException();
#else
	throw KSGException();
#endif
	*/
	char modulepath[1024+1] = "";
#ifdef WIN32
	//ACE_OS::realpath("gwmain.exe",modulepath);
	int len = GetModuleFileName(NULL,modulepath,sizeof(modulepath) - 1);
	if(len > 0)
	{
		modulepath[len] = '\0';
		dir = modulepath;
		return;
	}
#else
	ACE_OS::realpath(_exec_file_path.c_str(),modulepath);
#endif
	dir = modulepath;

}

std::string KSGOSUtil::JoinPath(const std::string& base,const std::string& path)
{
	boost::filesystem::path ret(base,boost::filesystem::native);
	ret /= path;
	return ret.native_directory_string();
}

std::string KSGOSUtil::BaseName(const std::string& fullpath)
{
	boost::filesystem::path ret(fullpath,boost::filesystem::native);
	return ret.leaf();
}

std::string KSGOSUtil::GetPathName(const std::string& fullpath)
{
	//boost::filesystem::path ret(fullpath,boost::filesystem::native);
	//return ret.branch_path().native_directory_string();
	return std::string(ACE::dirname(fullpath.c_str()));
}

bool KSGOSUtil::FileExists(const std::string& fullpath)
{
	ACE_stat state;
	if(ACE_OS::stat(fullpath.c_str(),&state))
	{
		return false;
	}
	return true;
}

void KSGOSUtil::GetTimestamp(std::string& timestamp)
{
	time_t now = ACE_OS::gettimeofday().sec();
	struct tm* tv = ACE_OS::localtime(&now);
	char buf[34] = "";
	ACE_OS::sprintf(buf,"%.02d%.02d%.02d%.02d%.02d%.02d",
		(tv->tm_year + 1900) % 2000,tv->tm_mon + 1,tv->tm_mday
		,tv->tm_hour,tv->tm_min,tv->tm_sec);
	timestamp = buf;
}

void KSGCryptUtil::CalcMD5(const unsigned char* buf,unsigned int len,unsigned char md5[16])
{
	MD5_CTX ctx;
	memset(&ctx,0,sizeof ctx);
	MD5Init(&ctx);
	MD5Update(&ctx,(unsigned char*)buf,len);
	MD5Final(md5,&ctx);
}
