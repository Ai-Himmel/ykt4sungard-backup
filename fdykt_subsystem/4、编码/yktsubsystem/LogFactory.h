// LogFactory.h: interface for the KLogFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGFACTORY_H__CE52BE19_F63E_4C35_9D8A_7C01CD6E32D4__INCLUDED_)
#define AFX_LOGFACTORY_H__CE52BE19_F63E_4C35_9D8A_7C01CD6E32D4__INCLUDED_
/** 
 * 模块名					外接子系统
 * 文件名					LogFactory.h
 * 文件实现功能				日志类工厂方法类
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-01
 * 备注
 * $Id: LogFactory.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
#include "KLogfile.h"

/** 
 * @brief 日志工厂类
 */
class KLogFactory  
{
	/** 
	 * @brief 互斥类
	 */
	class KMutex
	{
	private:
#ifdef WIN32
		/** 
		 * @brief 系统互斥变量
		 */
		CRITICAL_SECTION m_mutex;
#else
#endif
	public:
		/** 
		 * @brief 进入互斥区，如果已经有其它线程进入了互斥区，则该函数被阻塞
		 * 
		 * @return - 失败返回 -1 ，成功返回 0
		 */
		int Lock();
		/** 
		 * @brief 离开互斥区
		 * 
		 * @return - 成功返回 0，失败返回 -1
		 */
		int UnLock();
		/** 
		 * @brief 构造函数
		 */
		KMutex();
		/** 
		 * @brief 析构函数
		 */
		virtual ~KMutex();
	};
private:
	/** 
	 * @brief 工厂类的唯一实例
	 */
	static KLogFactory* ms_Instance;
	/** 
	 * @brief 互斥变量
	 */
	static KMutex ms_Mutex;
	/** 
	 * @brief 日志文件名
	 */
	static std::string ms_LogFileName;
	/** 
	 * @brief 日志文件路径
	 */
	static std::string ms_LogDir;

private:
	/** 
	 * @brief 日志文件类
	 */
	KLogfile m_logfile;
	/** 
	 * @brief 构造函数
	 */
	KLogFactory();
	/** 
	 * @brief 当前时间
	 */
	std::string m_CurrentDate;
	/** 
	 * @brief 获取当前系统时间
	 * 
	 * @return - 返回系统时间
	 */
	std::string GetCurrentDateString();
	/** 
	 * @brief 获得System  Tick　Count
	 * 
	 * @return - 
	 */
	long GetTickCount();
	/** 
	 * @brief 根据时间生成新的日志文件名
	 * 
	 * @param timestampe - 时间
	 * 
	 * @return - 成功返回0，失败返回 -1
	 */
	int RenameFile(const std::string& timestampe);
	/** 
	 * @brief 根据文件名前缀与时间生成日志文件名
	 * 
	 * @param filename - 文件名前缀
	 * @param timestampe - 时间
	 */
	void GenLogFileName(std::string& filename,
		const std::string& timestampe);
public:
	/** 
	 * @brief 设置当前日志系统的路径
	 * 
	 * @param path - 路径
	 */
	static void SetLogFileDirectory(const std::string& path);
	/** 
	 * @brief 获取工厂类的唯一实例
	 * 
	 * @return - 返回唯一实例
	 */
	static KLogFactory* GetInstance();
	/** 
	 * @brief 释放工厂类的唯一实例
	 */
	static void Release();
public:
	/** 
	 * @brief 取得当前的日志文件类
	 * 
	 * @return - 日志文件类的指针
	 */
	virtual KLogfile* GetLogSys();
	/** 
	 * @brief 析构函数
	 */
	virtual ~KLogFactory();
};

#endif // !defined(AFX_LOGFACTORY_H__CE52BE19_F63E_4C35_9D8A_7C01CD6E32D4__INCLUDED_)
