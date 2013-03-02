#ifndef _LOCKQUEUE_H_
#define _LOCKQUEUE_H_
/*! @file
 *	模块名:		一卡通通用前置机
 *	文件名:		lockqueue.h
 *	文件实现功能: 通用队列，可以增加访问锁
 *	作者:	汤成
 *	版本:	V1.0
 *	备注:	
*/
#ifdef _MSC_VER
#pragma once
#endif
#include <boost/thread/mutex.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/throw_exception.hpp>
#include <xutils/xtype_trait.h>
#include <vector>
#include <algorithm>
#include "thread.h"

//! 线程锁队列
/*!
 * 该容器只能存放对象指针，该容器对象不可拷贝
 * \param T 容器元素类型
 * \param ThreadModel 线程模型，默认为多线程模型
 */
template<class T ,class ThreadModel = KSGLockThreadModel >
class KSGLockQueue
{
private:
	//<! 对象类型
	typedef T Obj_Type;
	//<! 队列容器类型
	typedef std::list<Obj_Type> ObjQueue;
	//<! 队列容器
	ObjQueue _queue;
	//<! 互斥变量
	typename ThreadModel::MutexType _mutex;
public:
	//! default constructor
	explicit KSGLockQueue(){}
	//! destructor
	~KSGLockQueue()
	{
		clear();
	}
	/*!
	 * 追加一个指令对象，对于多线程模型将会有一个 timeout 锁
	 * \return 成功返回 true , 超时失败返回 false
	 */
	bool append(Obj_Type& obj)
	{
		try
		{
			ThreadModel lock(_mutex);
			_queue.push_back(obj);
			return true;
		}
		catch (boost::lock_error & )
		{
			return false;
		}
	}
	bool insert(Obj_Type& obj)
	{
		try
		{
			ThreadModel lock(_mutex);
			_queue.push_front(obj);
			return true;
		}
		catch(boost::lock_error& )
		{
			return false;
		}
	}
	/*!
	 * 判断队列是否为空
	 * \return 不为空返回 true ，否则返回 false
	 */
	bool isEmpty() const
	{
		return _queue.empty();
	}
	/*!
	 * 从队列中取出一个对象，同时将从队列中删除, 如果是多线程模型超时返回 NULL
	 * \return 返回容器中对象，如果没有返回 NULL ，如果超时返回 NULL
	 */
	Obj_Type peek()
	{
		try
		{
			ThreadModel lock(_mutex);
			if(!_queue.empty())
			{
				//typename ObjQueue::iterator i = _queue.begin();
				Obj_Type p = _queue.front();
				_queue.pop_front();
				return p;
			}
			// maybe error
			throw NoneResourceException();
		}
		catch (boost::lock_error&)
		{
			throw TimeoutException();
		}
	}
	/*!
	 * 将队列中的所有对象删除
	 */
	void clear()
	{
		try
		{
			ThreadModel lock(_mutex);
			_queue.clear();
		}
		catch (boost::lock_error&)
		{
			// TODO : log
		}
	}
	/*!
	 * \return 队列中记录条数
	 */
	inline size_t count() const
	{
		return _queue.size();
	}
	/*!
	 * 从指定的容器中拷贝所有的元素，拷贝前会删除原来的元素
	 * \param M - 源队列的线程模型
	 * \param rhl - 源队列的引用
	 * \throw 如果对于多线程模型，当加锁超时抛出异常。
	 */
	template<class M>
	KSGLockQueue& operator=(const KSGLockQueue<T,M>& rhl)
	{
		try
		{
			ThreadModel lock(_mutex);
			M lock2(rhl._mutex);
			_queue.clear();
			std::copy(rhl._queue.begin(),rhl._queue.end(),_queue.begin());
			return *this;
		}
		catch (boost::lock_error &e)
		{
			// 记录日志
			throw KSGException();
		}
	}
};
#endif // _LOCKQUEUE_H_

