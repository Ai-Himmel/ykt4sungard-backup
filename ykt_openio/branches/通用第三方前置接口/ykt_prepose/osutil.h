#ifndef _OSUTIL_H_
#define _OSUTIL_H_

#include "ksglobal.h"
#include <string>

#define ABS(x) ((x) > 0 ? (x) : -(x))

class KSGOSUtil
{
private:
	static std::string _exec_file_path;
public:
#ifdef WIN32
	static const char sc_path_sep = '\\';
#else
	static const char sc_path_sep = '/';
#endif
	//! 获取可执行程序的完整路径
	/*
	 \return 完整路径，如果失败抛出 KSGException
	 */
	static void GetBaseDir(std::string& dir);
	//! 将目录与文件名加在一起
	/* 
	 \param base 目录路径
	 \param path 文件路径
	 \return 组合后的完整路径
	 */
	static std::string JoinPath(const std::string& base,const std::string& path);
	//! 获取完整路径中的 basename 
	/*
	 \param fullpath 完整路径
	 \return 返回 basename
	 */
	static std::string BaseName(const std::string& fullpath);
	//! 获取路径
	/*
	 \param fullpath 完整路径
	 \return 路径（不包含文件名）
	 */
	static std::string GetPathName(const std::string& fullpath);

	static bool FileExists(const std::string& fullpath);

	static void GetTimestamp(std::string& timestamp);

	static void Program_name(const char* prg);
};

class KSGCryptUtil
{
public:
	static void CalcMD5(const unsigned char* buf,unsigned int len
		,unsigned char md5[16]);

};

class KSGMathUtil
{
public:
	static double D4U5(double v,int precision=2);
};

#ifdef WIN32
#define DLL_CALLCONVERSION __stdcall
#else
#define DLL_CALLCONVERSION
#endif

#define DECLARE_DLL_FUNC(r,n,p) \
	typedef r (DLL_CALLCONVERSION * lp##n) p

#define DEFINE_DLL_FUNC(n) \
	lp##n n

#define LOAD_DLL_FUNC(dll,n) \
	n = (lp##n) (dll)->symbol(#n,0); \
	if(n == NULL) return -1


#endif // _OSUTIL_H_


