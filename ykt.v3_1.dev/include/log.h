
//log.h
//hujinshan@2004.1.3 Airforce Engineering University
/*
//CLog* CLog::_instance = NULL;

CLog::GetObj().Write( "******* 初始化完成 *******" ) <<endl;
CLog::GetObj().tmWrite( "******* 开始渲染No1. *******" ) <<endl ;
CLog::GetObj()<<  "******* 注销钩子 *******" <<endl;

  在Clog文件中有 #define CLog /##/ 的语句，
  这是为了使日志在release版无效，
  使用单行注释，所以如果调用时如果要换行，
  请务必在换行最后加上 \ 符号,

*/

#ifndef _DEBUG
#define CLog /##/
#define _CLOG_H
#endif

#ifndef _CLOG_H
#define _CLOG_H
#pragma once

#include <sstream>
#include <iostream> 
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std; 

class CLog
{
	CLog(char *logfile)
	{	
		pf.open(logfile,ios::out | ios::app);
	}
	static CLog* _instance;
	ofstream pf;
public:
	~CLog()
	{
		_instance=0;		
		pf.close();
	}

	static CLog* GetPtr()
	{
 		if(!_instance)
			_instance=new CLog("c:\\error.log");
		return(_instance);
	}

	static CLog& GetObj()
	{
 		if(!_instance)
			_instance=new CLog("c:\\error.log");
		return(*_instance);
	}
	static CLog* GetPtr(char *logfile)
	{
		if(!_instance)
			_instance=new CLog(logfile);
		return(_instance);
	}

	static CLog& GetObj(char *logfile)
	{
		if(!_instance)
			_instance=new CLog(logfile);
		return(*_instance);
	}	
	static void FreeObj()
	{
		if(_instance)
		{
			delete _instance;
			_instance=NULL;
		}
	}

	template<class T> inline CLog& Write(T val)
	{
		pf << val ;
		pf.flush(); 
		return *this;
	}
	
	template<class T> inline CLog& tmWrite(T val)
	{
		time_t ltime;
		time( &ltime );
		pf << "---  "<< ctime( &ltime ) << val ;
		pf.flush(); 
		return *this;
	}
	inline CLog& WriteTime()
	{
		time_t now;
		struct tm *t;
		time(&now);
		t = localtime(&now);
		char dt[21];
		sprintf(dt,"%04d-%02d-%02d %02d:%02d:%02d ",t->tm_year+1900,t->tm_mon+1,t->tm_mday,
			t->tm_hour,t->tm_min,t->tm_sec);	
		pf.write(dt,strlen(dt));
		pf.flush(); 
		return *this;
	}

	template<class T> inline CLog& operator<< (T val)
	{
		std::ostringstream oss;
		oss<<val;
		pf<<oss.str();
		pf.flush(); 
		return *this;
	}

};

#endif
//end of file
