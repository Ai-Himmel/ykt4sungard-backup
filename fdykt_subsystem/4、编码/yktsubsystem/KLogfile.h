// KLogfile.h: interface for the KLogfile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KLOGFILE_H__4B754F84_0DC1_4BE0_8C3C_633FD0912786__INCLUDED_)
#define AFX_KLOGFILE_H__4B754F84_0DC1_4BE0_8C3C_633FD0912786__INCLUDED_
/** 
 * 模块名					外接子系统
 * 文件名					KLogfile.h
 * 文件实现功能				日志功能类
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-01
 * 备注
 * $Id: KLogfile.h 15 2005-08-22 02:39:12Z cash $
 */
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <fstream>

class KLogfile  
{
private:
	/** 
	 * @brief 日志文件名
	 */
	std::string m_LogFileName;
	/** 
	 * @brief 日志输出流
	 */
	std::ofstream* m_logFileStream;
	/** 
	 * @brief 取得当前系统时间
	 * 
	 * @return 当前系统时间
	 */
	std::string GetCurrentTimeString();
	/** 
	 * @brief 日志是否打开
	 */
	bool m_IsLogOpen;
public:
	/** 
	 * @brief Constructor
	 */
	KLogfile();
	/** 
	 * @brief Constructor，根据日志文件名打开日志
	 * 
	 * @param filename - 日志文件名
	 */
	KLogfile(const char* filename);
	/** 
	 * @brief 打开日志，如果日志已经被打开则先关闭
	 * 
	 * @param logfile - 日志文件名
	 * 
	 * @return - 成功返回 0，失败返回 -1
	 */
	int OpenLogfile(const char * logfile);
	/** 
	 * @brief 关闭日志
	 * 
	 * @return - 成功返回0，失败返回 -1
	 */
	int CloseLog();
	/** 
	 * @brief 刷新日志缓存
	 */
	void Flush();
	/** 
	 * @brief 写入字符串到日志文件中
	 * 
	 * @param msg - 日志内容
	 * 
	 * @return - 返回日志类的引用
	 */
	KLogfile& operator<<(const char* msg);
	/** 
	 * @brief 写日志信息
	 * 
	 * @param fmt - 日志格式化字符串，同 printf
	 * @param ... - 可变参数
	 * 
	 * @return - 返回日志类的引用
	 */
	KLogfile& WriteLog(const char* fmt,...);
	/** 
	 * @brief destructor,关闭日志
	 */
	virtual ~KLogfile();
};

#endif // !defined(AFX_KLOGFILE_H__4B754F84_0DC1_4BE0_8C3C_633FD0912786__INCLUDED_)
