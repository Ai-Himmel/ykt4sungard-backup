#ifndef _SMARTPOOL_H_
#define _SMARTPOOL_H_
/*! @file
 *	模块名:			一卡通通用前置机
 *	文件名: 		smartpool.h
 *	文件实现功能:	智能资源池
 *	作者:	汤成
 *	版本:	V1.0
 *	备注:
 定义一套智能资源池与智能资源池指针。
 1. 目标是自动管理资源池的资源，资源使用完成后，自动释放资源。
 2. 申请的资源不能 delete 。
 3. 智能指针被拷贝后，多个智能指针使用的仍是同一个资源。
 4. 对于智能指针 sp , if(sp) ... if(!sp) ... 都是可以的，它将会判断资源申请成功
 5. 对于智能指针sp , &sp 操作不会返回对资源的地址，而是智能指针的地址
 6. 不要试图调用ResourcePool的Return()方法，该方法由智能指针调用
*/
#ifdef _MSC_VER
#pragma once
#endif

#include <algorithm>
#include <stdexcept>
#include <functional>
#include <exception>
#include <assert.h>
#include <xutils/xtype_trait.h>
#include <xutils/xtypelist.h>
#include <vector>
#include <boost/function.hpp>
#include <boost/throw_exception.hpp>
#include "thread.h"
#include "ksgexception.h"


//! 缓存池资源存储策略
/*!
 \param T 保存原始类型，实际保存该类型的指针
 \param Pool 保存该资源的缓存池类型
 */
template<class T,class Pool>
class ResourcePoolStorage
{
public:
	//<! 保存资源类型
	typedef T* StoredType;
	//<! 资源的指针类型
	typedef T* PointerType;
	//<! 资源的引用类型
	typedef T& ReferenceType;
public:
	//! constructor
	/*!
	 \param const StoredType 保存资源
	 */
	ResourcePoolStorage(const StoredType p):_pointee(p)
	{}
	//! default constructor
	ResourcePoolStorage():_pointee(Default())
	{}
	//! constructor
	/*!
	 \param const ResourcePoolStorage& 资源存储策略
	 */
	ResourcePoolStorage(const ResourcePoolStorage&):_pointee(0)
	{}
	//! constructor
	/*!
	 \param U 参数资源类型
	 \param const ResourcePoolStorage<U,Pool>& 被拷贝的资源池
	 */
	template<class U>
	ResourcePoolStorage(const ResourcePoolStorage<U,Pool>&):_pointee(0)
	{}
	//! destructor
	~ResourcePoolStorage()
	{}
	//! * 操作符重载
	/*!
	 \return 资源类型的引用
	 */
	ReferenceType operator*() const
	{
		return *_pointee;
	}
	//! -> 操作符重载
	/*!
	 \return 资源的指针
	 */
	PointerType operator->() const
	{
		return _pointee;
	}
	//! 交换保存的资源
	/*!
	 \param ResourcePoolStorage& 交换的资源保存策略
	 */
	void Swap(ResourcePoolStorage& rhl)
	{
		std::swap(_pointee,rhl._pointee);
	}
	//! 取得存储策略中的指针
	/*!
	 \param const ResourcePoolStorage& 资源的存储策略
	 \return  返回指针类型
	 */
	friend inline PointerType GetImpl(const ResourcePoolStorage& sp)
	{
		return sp._pointee;
	}
	//! 取得存储策略中的引用
	/*!
	 \param const ResourcePoolStorage& 资源的存储策略
	 \return 返回 \b 指针类型 的引用
	 */
	friend inline const StoredType& GetImplRef(const ResourcePoolStorage& sp)
	{
		return sp._pointee;
	}
	//! 取得存储策略中的引用
	/*!
	 \param ResourcePoolStorage& 资源的存储策略
	 \return 返回 \b 指针类型 的引用
	*/
	friend inline StoredType& GetImplRef(ResourcePoolStorage& sp)
	{
		return sp._pointee;
	}
protected:
	//! 默认空的资源
	/*!
	 \return 返回 \c NULL
	 */
	static StoredType Default()
	{
		return NULL;
	}
	//! 删除保存的资源，将资源返还给缓存池。该方法会调用缓存池的 Return 方法
	/*!
	 \param p 资源缓存池
	 */
	void Delete(Pool* p)
	{
		if(p)
			p->Return(_pointee);
	}
private:
	//<! 缓存的资源
	StoredType _pointee;
};

//! 资源池的拥有者策略，\class RefCounted 引用策略，实现引用计数器
/*!
 \param T 资源类型
 */
template<class T>
class RefCounted
{
private:
	//<! 资源类型
	typedef T ObjectType;
	//<! 资源指针类型
	typedef T* PointerType;
	//<! 资源引用计数
	unsigned int * _pRefCnt;
public:
	//! default constructor
	RefCounted()
	{
		_pRefCnt = new unsigned int;
		assert(_pRefCnt != NULL);
		*_pRefCnt = 1;
	}
	//! constructor
	/*!
	 \brief 拷贝构造函数
	 \param rhl 拷贝的对象
	 */
	RefCounted(const RefCounted& rhl):_pRefCnt(rhl._pRefCnt)
	{}
	//! clone 函数，将引用计数加 1 
	/*!
	 \param val 资源的引用
	 \return 返回资源的引用
	 */
	ObjectType Clone(const ObjectType& val)
	{
		++*_pRefCnt;
		return val;
	}
	//! 释放资源
	/*!
	 \param const T& 资源的引用 
	 \return 将引用计数减1, 如果引用计数为 0 返回 true ,否则返回 false
	 */
	bool Release(const T&)
	{
		(*_pRefCnt)--;
		if(*_pRefCnt == 0)
		{
			::delete _pRefCnt;
			_pRefCnt = NULL;
			return true;
		}
		return false;
	}
	//! 交换资源
	/*!
	 \param rhl 需要交换的资源
	 */
	void Swap(RefCounted& rhl)
	{
		std::swap(_pRefCnt,rhl._pRefCnt);
	}
	//! 摧毁拷贝开关 
	enum { destructiveCopy = false };
};

//! 类型转型策略,允许转型
struct ConversionAllow
{
	enum {allowed = true };
	void Swap(ConversionAllow& )
	{}
};
//! 类型转换策略，不允许转型
struct ConversionDisallow
{
	enum {allowed = false };
	void Swap(ConversionAllow&)
	{}
	ConversionDisallow()
	{}
	ConversionDisallow(ConversionAllow&)
	{}
};

//! 检查策略，非空检查
/*!
 \param P 检查指针类型
 */
template <class P>
struct RejectNullStrict
{
	//! constructor
	RejectNullStrict()
	{}
	//! copy-constructor, 不产生实际的拷贝动作
	/*!
	 \param P1 被拷贝的对象的指针类型
	 \param const RejectNullStrict<P1> 
	 */
	template <class P1>
	RejectNullStrict(const RejectNullStrict<P1>&)
	{}
	//! 初始化时检查，如果 val 为空抛出异常
	/*!
	 \throw NullPointerException 如果 val 为 NULL 抛出异常
	 */
	static void OnInit(P val)
	{ if (!val) throw NullPointerException(); }
	
	//! 检查被引用时的指针 \sa RejectNullStrict::OnInit
	void OnDereference(P val)
	{ OnInit(val); }
	//! 检查被引用时的指针 \sa RejectNullStrict::OnInit
	void OnDereference(P val) const
	{ OnInit(val); }
	//! 交换
	void Swap(RejectNullStrict&)
	{}        
};


//! 用于 Pool 的智能指针
/*!
 智能指针不能用 new 申请，使用完成后会自动返还资源给缓存池，
 将智能指针被拷贝时，并将资源引用拷贝了一份，即它们指向的是同一个资源。
 智能指针的拷贝不是 thread-safe 的，对于一个智能指针不要在多个线程中使用。
 \param T  保存的对象的类型
 \param Pool 池对象
 \param OwnershipPolicy 拥有者策略
 \param ConversionPolicy 类型转换策略
 \param StoragePolicy 保存对象的策略
 \param CheckPolicy 检查策略
 \param ConstnessPolicy 常量类型策略
 */
template<
	class T,
	class Pool,
	template<class> class OwnershipPolicy = RefCounted,
	class ConversionPolicy = ConversionDisallow,
	template<class,class> class StoragePolicy = ResourcePoolStorage,
	template<class> class CheckPolicy = RejectNullStrict,
	template<class> class ConstnessPolicy = xutil::ConstnessTrait
>
class PoolSmartObject
	: public StoragePolicy<T,Pool>
	, public OwnershipPolicy<typename StoragePolicy<T,Pool>::PointerType >
	, public ConversionPolicy
	, public CheckPolicy<typename StoragePolicy<T,Pool>::PointerType>
{
private:
	//<! 存储策略类型
	typedef StoragePolicy<T,Pool> SP;
	//<! 保存资源类型，指针
	typedef typename SP::PointerType StoredType;
	
	//<! 缓存池类型
	typedef Pool PoolManageType;
	//<! 拥有者策略类型
	typedef OwnershipPolicy<StoredType> OP;
	//<! 转换策略类型
	typedef ConversionPolicy CP;
	//<! 检查策略类型
	typedef CheckPolicy<StoredType> KP;
	
	struct NeverMatch;
	//<! 隐式参数类型
	typedef typename 
		xutil::Selector<CP::allowed,const StoredType&,NeverMatch>::Result ImplicitType;
	//<! 显式参数类型
	typedef typename 
		xutil::Selector<!CP::allowed,const StoredType&,NeverMatch>::Result ExplicitType;
	//<! copy 策略定义的对象类型，如果为 copy-destructive 类型为非const
	typedef typename 
		xutil::Selector<OP::destructiveCopy,PoolSmartObject,const PoolSmartObject>::Result CopyArg;
	//<! 资源缓存池对象
	PoolManageType* _pool;
protected:
	//! constructor
	PoolSmartObject(PoolManageType * p):_pool(p)
	{KP::OnInit(GetImpl(*this)); }
	//! constructor
	explicit PoolSmartObject(PoolManageType * p,ExplicitType arg):SP(arg),_pool(p)
	{ KP::OnInit(GetImpl(*this)); }
	//! constructor
	PoolSmartObject(PoolManageType * p,ImplicitType arg):SP(arg),_pool(p)
	{ KP::OnInit(GetImpl(*this)); }

public:	
	//<! const pointer 类型
	typedef typename ConstnessPolicy<T>::Result* ConstPointerType;
	//<! const reference 类型
	typedef typename ConstnessPolicy<T>::Result& ConstReferenceType;
	//<! 资源指针类型
	typedef typename SP::PointerType PointerType;
	//<! 资源的引用类型
	typedef typename SP::ReferenceType ReferenceType;
	//! copy-constructor
	/*!
	 \param rhs 拷贝的智能指针对象
	 */
	PoolSmartObject(CopyArg & rhs)
		:OP(rhs),SP(rhs),KP(rhs)
	{
		_pool = rhs._pool;
		GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
	}
	//! = 操作符重载
	PoolSmartObject& operator=(CopyArg& rhs)
	{
		PoolSmartObject temp(rhs);
		temp.Swap(*this);
		return *this;
	}
	//! 创建对象,友元函数
	/*!
	 \param p 缓存池
	 \param o 资源对象
	 \return 返回资源智能指针
	 */
	friend inline PoolSmartObject CreateNewObject(PoolManageType* p,StoredType o)
	{
		PoolSmartObject temp(p,o);
		return temp;
	}
	//! default constructor
	PoolSmartObject():_pool(NULL)
	{
		// KP::OnDefault(GetImpl(*this));
	}
	/*
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1
	>
	PoolSmartObject(PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1>& rhs)
	:SP(rhs),OP(rhs),KP(rhs)
	{
		_pool = rhs._pool;
		GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
	}
	
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1
	>
	PoolSmartObject(const PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1>& rhs)
	:SP(rhs),OP(rhs),KP(rhs)
	{
		_pool = rhs._pool;
		GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
	}
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1
	>
	PoolSmartObject& operator=(const PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1>& rhs)
	:SP(rhs),OP(rhs),KP(rhs)
	{
		PoolSmartObject temp(rhs);
		temp.Swap(*this);
		return *this;
	}
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1
	>
	PoolSmartObject& operator=(PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1>& rhs)
	{
		PoolSmartObject temp(rhs);
		temp.Swap(*this);
		return *this;
	}
	*/
	//! 交换函数
	/*!
	 \param rhl 要交换的对象
	 */
	void Swap(PoolSmartObject& rhl)
	{
		OP::Swap(rhl);
		// CP::Swap(rhl);
		KP::Swap(rhl);
		SP::Swap(rhl);
		std::swap(_pool,rhl._pool);
	}
	//! destructor
	~PoolSmartObject()
	{
		// 当所有对该对象的引用全部删除后，Pool 自动回收对象
		if(OP::Release(GetImpl(*static_cast<SP*>(this))))
		{
			SP::Delete(_pool);
		}
	}
	//! -> 操作符重载
	PointerType operator->()
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator->();
	}
	//! -> 操作符重载
	ConstPointerType operator->() const
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator->();
	}
	//! * 操作符重载
	ReferenceType operator*()
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator*();
	}
	//! * 操作符重载
	ConstReferenceType operator*() const
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator*();
	}
	//! ! 操作符重载
	bool operator!() const // if(!sp)
	{
		return (GetImpl(*this) == 0);
	}
	//! == 操作符重载
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1,
		template<class> class CNP1
	>
	bool operator==(const PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1,CNP1>& rhs)
	{
		return (GetImpl(*this) == GetImpl(rhs));
	}
	//! != 操作符重载
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1,
		template<class> class CNP1
	>
	bool operator!=(const PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1,CNP1>& rhs)
	{
		return !(*this == rhs);
	}
	//! < 操作符重载
	template
	<
		class T1,
		class Pool1,
		template<class> class OP1,
		class CP1,
		template<class,class> class SP1,
		template<class> class KP1,
		template<class> class CNP1
	>
	bool operator<(const PoolSmartObject<T1,Pool1,OP1,CP1,SP1,KP1,CNP1>& rhs)
	{
		return GetImpl(*this) < GetImpl(rhs);
	}
private:
	struct Tester
	{
		Tester(int){}
		void dummy(){}
	};
	typedef void (Tester::*_unspecified_boolean_type)();
	typedef typename xutil::Selector<CP::allowed,Tester,
		_unspecified_boolean_type>::Result unspecified_boolean_type;
public:
	operator unspecified_boolean_type() const
	{
		return !*this ? 0 : &Tester::dummy;
	}
};
//////////////////////////////////////////////////////////////////////////
// PoolSmartObject 操作符重载
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator==(const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& lhs,U* rhs)
{
	return GetImpl(lhs) == rhs;
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator==(U* lhs,const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& rhs)
{
	return rhs == lhs;
}

template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator!=(const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& lhs,U* rhs)
{
	return !(lhs == rhs);
}

template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator!=(U* lhs,const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& rhs)
{
	return rhs != lhs;
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator<(const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& lhs,U* rhs)
{
	return GetImpl(lhs) < rhs;
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator<(U* lhs,const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& rhs)
{
	return lhs < GetImpl(rhs);
}

template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator>(const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& lhs,U* rhs)
{
	return rhs < lhs;
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator>(U* lhs,const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& rhs)
{
	return rhs < lhs;
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator<=(const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& lhs,U* rhs)
{
	return !(lhs > rhs);
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator<=(U* lhs,const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& rhs)
{
	return !(lhs > rhs);
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator>=(const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& lhs,U* rhs)
{
	return !(lhs < rhs);
}
template
<
	class T,
	class Pool,
	template<class> class OP,
	class CP,
	template<class,class> class SP,
	template<class> class KP,
	template<class> class CNP,
	class U
>
inline bool operator>=(U* lhs,const PoolSmartObject<T,Pool,OP,CP,SP,KP,CNP>& rhs)
{
	return !(lhs < rhs);
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
namespace std
{
	template
	<
		class T,
		class Pool,
		template<class> class OP,
		class CP,
		template<class,class> class SP,
		template<class> class KP
	>
	struct less< PoolSmartObject<T,Pool,OP,CP,SP,KP > >
		:public binary_function< PoolSmartObject<T,Pool,OP,CP,SP,KP >
		, PoolSmartObject<T,Pool,OP,CP,SP,KP > , bool >
	{
		bool operator()(const PoolSmartObject<T,Pool,OP,CP,SP,KP >& lhs
			,PoolSmartObject<T,Pool,OP,CP,SP,KP >& rhs)
		{
			return less<T*>(GetImpl(lhs),GetImpl(rhs));
		}
	};
}

#include <boost/function.hpp>
#include <boost/throw_exception.hpp>
//! 资源池
/*!
 \param T 缓存的资源类型
 \param ThreadModel 线程模型 默认为 KSGMultiThreadmModel<1000>
 */
template<class T,class ThreadModel=KSGMultiThreadmModel<1000> >
class ResourcePool
{
public:
	//<! 智能指针对象类型
	typedef PoolSmartObject<T,ResourcePool<T,ThreadModel> > SmartObject;
	//<! 缓存对象类型
	typedef T ObjType;
	//<! 缓存对象的指针类型
	typedef typename SmartObject::PointerType PointerType;
	//<! 缓存池类型
	typedef ResourcePool<ObjType,ThreadModel> PoolType;
	//<! 缓存池可用对象队列
	typedef std::vector<PointerType> PoolQueueType;
	//<! 创建缓存对象的functor 类型
	typedef boost::function0<PointerType> FunctorType;
private:
	//<! 缓存池容量
	int _poolMaxSize;
	//<! 创建资源的 functor
	FunctorType _functor;
	//<! logger
	// static log4cxx::LoggerPtr logger;
	//<! 可用资源队列
	PoolQueueType _freeQueue;
	//<! 线程模型的互斥变量
	typename ThreadModel::MutexType _mutex;
public:
	//! default constructor
	ResourcePool()
	{}
	//! constructor
	/*!
	 \param func 创建资源的 functor \sa ResourcePool::FunctorType
	 */
	ResourcePool(FunctorType func):_functor(func)
	{}
	~ResourcePool()
	{
		Free();
	}
	//! 初始化缓存池
	/*!
	 \param maxsize 缓存池最大数量
	 \param func 创建缓存池对象的 functor \sa ResourcePool::FunctorType
	 */
	void Init(int maxsize,FunctorType func)
	{
		_poolMaxSize = maxsize;
		_functor = func;
		Init(maxsize);
	}
	//! 初始化缓存池
	/*!
	 \param maxsize 缓存池最大数量
	 */
	void Init(int maxsize)
	{
		_poolMaxSize = maxsize;
		//LOG4CXX_INFO(logger,_T("加载缓存池,大小:")<<_poolMaxSize);
		Free();
		for (int i = 0;i < _poolMaxSize;++i)
		{
			PointerType p = _functor();
			if(!p)
				throw NullPointerException();
			_freeQueue.push_back(p);
		}

	}
	//! 释放所有缓存中的对象
	void Free()
	{
		ThreadModel lock(_mutex);
		typename PoolQueueType::iterator i;
		for(i = _freeQueue.begin();i != _freeQueue.end();++i)
		{
			PointerType p = *i;
			delete p;
		}
		_freeQueue.clear();
	}
	//! 缓存池最大数量
	inline int MaxSize() const
	{
		return _poolMaxSize;
	}
	//! 缓存池当前的数量
	inline int Count() const
	{
		return static_cast<int>(_freeQueue.size());
	}
	//! 返还资源到缓存池中
	void Return(PointerType p)
	{
		//LOG4CXX_DEBUG(logger,_T("归还请求资源"));
		ThreadModel lock(_mutex);
		_freeQueue.push_back(p);
	}
	//! 申请资源，如果没有资源可以用抛出 NoneResourceException 异常
	/*!
	 \param obj 将申请的资源保存到 obj 中
	 */
	void Alloc(SmartObject& obj)
	{
		ThreadModel lock(_mutex);
		if(_freeQueue.size() == 0)
		{
			throw NoneResourceException();
		}
		typename PoolQueueType::iterator i = _freeQueue.begin();
		PointerType p = *i;
		obj = CreateNewObject((PoolType*)this,p);
		_freeQueue.erase(i);
		//LOG4CXX_DEBUG(logger,_T("申请资源成功"));
	}
	//! 申请资源，如果没有资源可以用抛出 NoneResourceException 异常
	/*!
	 \return 返回资源的智能指针
	 */
	SmartObject Alloc()
	{
		ThreadModel lock(_mutex);
		if(_freeQueue.size() == 0)
		{
			throw NoneResourceException();
		}
		typename PoolQueueType::iterator i = _freeQueue.begin();
		PointerType p = *i;
		SmartObject temp = CreateNewObject((PoolType*)this,p);
		_freeQueue.erase(i);
		//LOG4CXX_DEBUG(logger,_T("申请资源成功"));
		return temp;
	}
	//! == 操作符重载
	template<class T1,class TM1> 
	bool operator==(const ResourcePool<T1,TM1>& rhs)
	{
		return (this == &rhs);
	}
};

template
<
	class T,
	class Allocator,
	class ThreadModel
>
class SmartPtrPool : public KSGObserverable<T,ThreadModel>
{
public:
	typedef PoolSmartObject<T,SmartPtrPool<T,Allocator,ThreadModel> > SmartPtr;
private:
	typedef typename SmartPtr::PointerType PointerType;
	Allocator _alloc;
	typename ThreadModel::MutexType _mutex;
public:
	explicit SmartPtrPool(){}
	SmartPtrPool(const SmartPtrPool& rhs)
	{
		_alloc = rhs._alloc;
	}
	~SmartPtrPool(){}
	SmartPtr Alloc()
	{
		return CreateNewObject(this,_alloc.construct());
	}
#include "detail/smart_ptr_pool_construct.inc"
	void Return(PointerType p)
	{
		ThreadModel lock(_mutex);
		_currPtr = p;
		_alloc.free(p);
	}
protected:
	T* _currPtr;
	virtual T& GetObserverable()
	{
		return *_currPtr;
	}

};
#endif // _SMARTPOOL_H_

