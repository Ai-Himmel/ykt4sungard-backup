#ifndef _LOCKQUEUE_H_
#define _LOCKQUEUE_H_
/*! @file
 *	ģ����:		һ��ͨͨ��ǰ�û�
 *	�ļ���:		lockqueue.h
 *	�ļ�ʵ�ֹ���: ͨ�ö��У��������ӷ�����
 *	����:	����
 *	�汾:	V1.0
 *	��ע:	
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

//! �߳�������
/*!
 * ������ֻ�ܴ�Ŷ���ָ�룬���������󲻿ɿ���
 * \param T ����Ԫ������
 * \param ThreadModel �߳�ģ�ͣ�Ĭ��Ϊ���߳�ģ��
 */
template<class T ,class ThreadModel = KSGLockThreadModel >
class KSGLockQueue
{
private:
	//<! ��������
	typedef T Obj_Type;
	//<! ������������
	typedef std::list<Obj_Type> ObjQueue;
	//<! ��������
	ObjQueue _queue;
	//<! �������
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
	 * ׷��һ��ָ����󣬶��ڶ��߳�ģ�ͽ�����һ�� timeout ��
	 * \return �ɹ����� true , ��ʱʧ�ܷ��� false
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
	 * �ж϶����Ƿ�Ϊ��
	 * \return ��Ϊ�շ��� true �����򷵻� false
	 */
	bool isEmpty() const
	{
		return _queue.empty();
	}
	/*!
	 * �Ӷ�����ȡ��һ������ͬʱ���Ӷ�����ɾ��, ����Ƕ��߳�ģ�ͳ�ʱ���� NULL
	 * \return ���������ж������û�з��� NULL �������ʱ���� NULL
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
	 * �������е����ж���ɾ��
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
	 * \return �����м�¼����
	 */
	inline size_t count() const
	{
		return _queue.size();
	}
	/*!
	 * ��ָ���������п������е�Ԫ�أ�����ǰ��ɾ��ԭ����Ԫ��
	 * \param M - Դ���е��߳�ģ��
	 * \param rhl - Դ���е�����
	 * \throw ������ڶ��߳�ģ�ͣ���������ʱ�׳��쳣��
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
			// ��¼��־
			throw KSGException();
		}
	}
};
#endif // _LOCKQUEUE_H_

