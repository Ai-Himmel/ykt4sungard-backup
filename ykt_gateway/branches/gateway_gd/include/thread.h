#ifndef _KSG_THREAD_H_
#define _KSG_THREAD_H_
/*! @file
 *	模块名:		一卡通通用前置机
 *	文件名: 	thread.h
 *	文件实现功能: 线程相关功能
 *	作者:		  汤成
 *	版本:		  V1.0
 *	备注:	
*/
#ifdef _MSC_VER
#pragma once
#endif

#include <boost/thread.hpp>
#include <boost/throw_exception.hpp>
#include <xutils/xtypelist.h>
#include <xutils/xtype_trait.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <cassert>
#include <list>
#include <cstddef>

//! 线程功能函数类
class KSGThreadUtil
{
public:
	static void Sleep(long msec);
	static boost::xtime Delay(long msec);
	static void yield();
};

/*!
* 单线程模型
*/
class KSGSingleThreadModel
{
public:
	typedef xutil::EmptyType MutexType;
	KSGSingleThreadModel(MutexType& mx)
	{}
	~KSGSingleThreadModel()
	{}
};

//! 多线程模型对象
/*!
* \param msec - 超时时间，毫秒,默认为 300 ms
*/
template<int msec = 300>
class KSGMultiThreadmModel
{
private:
	//<! 超时锁对象
	boost::timed_mutex::scoped_timed_lock _lock;

	//<! 超时时间
	static boost::xtime _s_timeout;
	static const boost::xtime::xtime_nsec_t _sc_msec = msec;
	static int _s_init;
	static int do_init()
	{
		boost::xtime_get(&_s_timeout,boost::TIME_UTC);
		_s_timeout.sec += _sc_msec/1000;
		_s_timeout.nsec += _sc_msec % 1000;
		return 1;
	}
public:
	//<! 互斥对象类型
	typedef boost::timed_mutex MutexType;
	/*! 
	* constructor
	* \param mx 互斥对象
	*/
	KSGMultiThreadmModel(MutexType& mx)
		:_lock(mx,false)
	{
		boost::xtime tv;
		boost::xtime_get(&tv,boost::TIME_UTC);
		tv.sec += _sc_msec/1000;
		tv.nsec += _sc_msec%1000;
		_lock.timed_lock(tv);
	}
	bool locked() 
	{
		return _lock.locked();
	}
	/*!
	* destructor
	*/
	~KSGMultiThreadmModel()
	{}
};

class KSGLockThreadModel
{
private:
	boost::mutex::scoped_lock _lock;
public:
	typedef boost::mutex MutexType;

	KSGLockThreadModel(MutexType& mx):_lock(mx)
	{}
	bool locked() 
	{
		return _lock.locked();
	}
	~KSGLockThreadModel(){}
};

template<class T>
class MTTssSpecificPtr
{
	typedef typename xutil::Selector<xutil::PointerTrait<T>::result,
		typename xutil::PointerTrait<T>::Pointer,T*>::Result ObjType;
	typedef typename boost::thread_specific_ptr<ObjType> PtrType;
private:
	PtrType _ptr;
public:
	explicit MTTssSpecificPtr(T* p):_ptr(p)
	{}
	explicit MTTssSpecificPtr():_ptr(NULL)
	{}
	~MTTssSpecificPtr()
	{
	}
	ObjType& operator*() const
	{
		return _ptr.operator *();
	}
	ObjType* operator->() const
	{
		return _ptr.operator ->();
	}
	ObjType* get() const
	{
		return _ptr.get();
	}
	bool operator!()
	{
		return _ptr.get() != NULL;
	}
	MTTssSpecificPtr& operator=(const MTTssSpecificPtr& rhs)
	{
		_ptr.reset(rhs.get());
		return *this;
	}
	MTTssSpecificPtr& operator=(ObjType* p)
	{
		_ptr.reset(p);
		return *this;
	}
};

class MTTheadModel
{
private:
	boost::mutex::scoped_lock _lock;
public:
	typedef boost::mutex MutexType;
	MTTheadModel(MutexType& mx):_lock(mx)
	{

	}
	~MTTheadModel()
	{}
};


template<int T>
boost::xtime KSGMultiThreadmModel<T>::_s_timeout = 
{0,KSGMultiThreadmModel<T>::_sc_msec};

template<int T>
int KSGMultiThreadmModel<T>::_s_init = KSGMultiThreadmModel<T>::do_init();

//////////////////////////////////////////////////////////////////////////
// boost 线程封装
template<class T,class ThreadModel>
class KSGObserverable;

//! 观察者接口
template<class T,class ThreadModel = KSGSingleThreadModel>
class KSGObserver
{
public:
	typedef ThreadModel ThreadModelType;
	//typedef typename KSGObserverable<ThreadModelType> ObserverableType;
	typedef T ObserverableType;
protected:
	typename ThreadModelType::MutexType _mutex;
public:
	//! 被观察者通知接口
	/*
	 \param obj 通知者 
	 */
	virtual void Update(ObserverableType& obj)
	{
		//
	}
};

//<! 多线程模型的观察者类类型
// typedef KSGObserver<KSGMultiThreadmModel<500> > KSGMTObserver;
//! 被观察者对象接口
template<class T,class ThreadModel>
class KSGObserverable
{
protected:
	typedef KSGObserver<T,ThreadModel> ObserverType;
private:
	typedef std::list<ObserverType*> ObserverListType;
	//<! 观察者列表
	ObserverListType _observers;
	typename ThreadModel::MutexType _mutex;
public:
	//! constructor
	KSGObserverable(){}
	//! destructor
	virtual ~KSGObserverable(){}
	//! 增加观察者
	/*
	 \param Observer 观察者类型,一定要是 \class KSGObserver 的子类
	 \param observer 观察者对象指针
	 */
	template<class Observer>
	void Attach(Observer* observer)
	{
		ObserverType * o = reinterpret_cast<ObserverType*>(observer);
		assert(o != NULL);
		ThreadModel lock(_mutex);
		_observers.push_back(o);
	}
	//! 删除观察者
	/*
	\param Observer 观察者类型,一定要是 \class KSGObserver 的子类
	\param observer 观察者对象指针
	*/
	template<class Observer>
	void Dettach(Observer* observer)
	{
		ObserverType * o = reinterpret_cast<ObserverType*>(observer);
		assert(o != NULL);
		ThreadModel lock(_mutex);
		_observers.remove(o);
	}
	//! 通知所有的观察者
	void Notify()
	{
		ThreadModel lock(_mutex);
		for(typename ObserverListType::iterator i = _observers.begin();i != _observers.end();++i)
		{
			(*i)->Update(GetObserverable());
		}
	}
protected:
	//<! 必须由子类实现
	virtual T& GetObserverable() = 0;
};
//! 线程接口类
template<class Runner>
class KSGThreadExec
{
private:
	int _usenew;
	bool _suspend;
	bool _isTerminated;
	bool _freeOnTerm;
	typedef boost::mutex::scoped_lock LockType;
	boost::mutex _monitor;
	boost::thread* _thread;
protected:
	virtual void StartThread(KSGThreadExec* p)
	{
		boost::function0<void> func;
		func = boost::bind(boost::mem_fn(&Runner::DoRun),GetRunnerImpl(p));
		_isTerminated = false;
		_thread = new boost::thread(func);
		_suspend = false;
	}
	virtual Runner* GetRunnerImpl(KSGThreadExec* p)
	{
		return reinterpret_cast<Runner*>(p);
	}
	void DoRun()
	{
		Run();
		_isTerminated = true;
		if(_freeOnTerm && _usenew == 0)
			delete this;
	}
	virtual void Run() = 0;
public:
	//<! constructor
	KSGThreadExec(bool suspend = true,bool autoFree = false)
		:_suspend(suspend),_isTerminated(true),_thread(NULL)
		,_freeOnTerm(autoFree)
	{
#ifdef KSG_MUST_NEW_THREAD
		assert(_usenew == 0);
#endif
		if(!_suspend)
		{
			Start();
		}
	}
	virtual ~KSGThreadExec()
	{
		_usenew = -1;
		if(_thread)
		{
			delete _thread;
		}
	}
	inline bool IsTerminated() const
	{
		return _isTerminated;
	}
	void Start()
	{
		if(_suspend)
		{
			StartThread(this);
		}
	}
	void Terminate()
	{
		if(IsTerminated())
			return;
		LockType lock(_monitor);
		_isTerminated = true;
		if(_thread)
		{
			_thread->join();
			delete _thread;
			_thread = NULL;
		}
	}
	bool IsSuspend() const
	{
		return _suspend;
	}
	void * operator new(size_t size)
	{
		KSGThreadExec* p = (KSGThreadExec*)::operator new(size);
		p->_usenew = 0;
		return p;
	}
	void operator delete(void* p)
	{
		::operator delete(p);
	}
	static void Sleep(long msec)
	{
		KSGThreadUtil::Sleep(msec);
	}
};
#endif	// _KSG_THREAD_H_


