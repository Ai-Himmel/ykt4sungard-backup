#ifndef _MEMUTIL_H_
#define _MEMUTIL_H_
/*! @file
 *	模块名:			一卡通前置机
 *	文件名: 		memutil.h
 *	文件实现功能:	内存管理定义	
 *	作者:			汤成
 *	版本:			V1.0
 *	备注:			基于boost库
*/
#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include "ksgexception.h"
#include <boost/pool/object_pool.hpp>

template<class T>
class BoostPoolCreator
{
private:
	static boost::object_pool<T> _s_pool;
public:
	static T* Create()
	{
		return _s_pool.malloc();
	}
	static void Destroy(T* p)
	{
		if(_s_pool.is_from(p))
			_s_pool.free(p);
		else
			throw KSGException();
	}
};

template<class T>
boost::object_pool<T> BoostPoolCreator<T>::_s_pool;

//! 自增加键
template<class ThreadModel>
class KSGSequenceGenerator
{
private:
	unsigned long _seed;
	typename ThreadModel::MutexType _mutex;
	static const int MAX_SEQNO = 0x7FFFFFFF;
public:
	KSGSequenceGenerator(long start = 0):_seed(0)
	{}
	~KSGSequenceGenerator()
	{}
	long GetNextVal()
	{
		ThreadModel lock(_mutex);
		_seed++;
		if(_seed > MAX_SEQNO)
			_seed = 1;
		return _seed;
	}
	long GetCurrVal()
	{
		ThreadModel lock(_mutex);
		return _seed;
	}
};

class KSG_Memory_Util
{
public:
	static void revert_buffer(const unsigned char *in_buf,size_t len
		,unsigned char *out_buf)
	{
		for (size_t i = 0; i < len/2; ++i)
		{
			out_buf[len - i - 1] = in_buf[i];
			out_buf[i] = in_buf[len - i - 1];
		}
	}
	static void revert_buffer(unsigned char *buf,size_t len)
	{
		for (size_t i = 0; i < len/2; ++i)
		{
			unsigned char t = buf[i];
			buf[i] = buf[len - i - 1];
			buf[len - i - 1] = t;
		}
	}
};

#endif // _MEMUTIL_H_

