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
	//! ��ȡ��ִ�г��������·��
	/*
	 \return ����·�������ʧ���׳� KSGException
	 */
	static void GetBaseDir(std::string& dir);
	//! ��Ŀ¼���ļ�������һ��
	/* 
	 \param base Ŀ¼·��
	 \param path �ļ�·��
	 \return ��Ϻ������·��
	 */
	static std::string JoinPath(const std::string& base,const std::string& path);
	//! ��ȡ����·���е� basename 
	/*
	 \param fullpath ����·��
	 \return ���� basename
	 */
	static std::string BaseName(const std::string& fullpath);
	//! ��ȡ·��
	/*
	 \param fullpath ����·��
	 \return ·�����������ļ�����
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


