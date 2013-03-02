#ifndef _SMARTPOOL_H_
#define _SMARTPOOL_H_
/*! @file
 *	ģ����:			һ��ͨͨ��ǰ�û�
 *	�ļ���: 		smartpool.h
 *	�ļ�ʵ�ֹ���:	������Դ��
 *	����:	����
 *	�汾:	V1.0
 *	��ע:
 ����һ��������Դ����������Դ��ָ�롣
 1. Ŀ�����Զ�������Դ�ص���Դ����Դʹ����ɺ��Զ��ͷ���Դ��
 2. �������Դ���� delete ��
 3. ����ָ�뱻�����󣬶������ָ��ʹ�õ�����ͬһ����Դ��
 4. ��������ָ�� sp , if(sp) ... if(!sp) ... ���ǿ��Եģ��������ж���Դ����ɹ�
 5. ��������ָ��sp , &sp �������᷵�ض���Դ�ĵ�ַ����������ָ��ĵ�ַ
 6. ��Ҫ��ͼ����ResourcePool��Return()�������÷���������ָ�����
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


//! �������Դ�洢����
/*!
 \param T ����ԭʼ���ͣ�ʵ�ʱ�������͵�ָ��
 \param Pool �������Դ�Ļ��������
 */
template<class T,class Pool>
class ResourcePoolStorage
{
public:
	//<! ������Դ����
	typedef T* StoredType;
	//<! ��Դ��ָ������
	typedef T* PointerType;
	//<! ��Դ����������
	typedef T& ReferenceType;
public:
	//! constructor
	/*!
	 \param const StoredType ������Դ
	 */
	ResourcePoolStorage(const StoredType p):_pointee(p)
	{}
	//! default constructor
	ResourcePoolStorage():_pointee(Default())
	{}
	//! constructor
	/*!
	 \param const ResourcePoolStorage& ��Դ�洢����
	 */
	ResourcePoolStorage(const ResourcePoolStorage&):_pointee(0)
	{}
	//! constructor
	/*!
	 \param U ������Դ����
	 \param const ResourcePoolStorage<U,Pool>& ����������Դ��
	 */
	template<class U>
	ResourcePoolStorage(const ResourcePoolStorage<U,Pool>&):_pointee(0)
	{}
	//! destructor
	~ResourcePoolStorage()
	{}
	//! * ����������
	/*!
	 \return ��Դ���͵�����
	 */
	ReferenceType operator*() const
	{
		return *_pointee;
	}
	//! -> ����������
	/*!
	 \return ��Դ��ָ��
	 */
	PointerType operator->() const
	{
		return _pointee;
	}
	//! �����������Դ
	/*!
	 \param ResourcePoolStorage& ��������Դ�������
	 */
	void Swap(ResourcePoolStorage& rhl)
	{
		std::swap(_pointee,rhl._pointee);
	}
	//! ȡ�ô洢�����е�ָ��
	/*!
	 \param const ResourcePoolStorage& ��Դ�Ĵ洢����
	 \return  ����ָ������
	 */
	friend inline PointerType GetImpl(const ResourcePoolStorage& sp)
	{
		return sp._pointee;
	}
	//! ȡ�ô洢�����е�����
	/*!
	 \param const ResourcePoolStorage& ��Դ�Ĵ洢����
	 \return ���� \b ָ������ ������
	 */
	friend inline const StoredType& GetImplRef(const ResourcePoolStorage& sp)
	{
		return sp._pointee;
	}
	//! ȡ�ô洢�����е�����
	/*!
	 \param ResourcePoolStorage& ��Դ�Ĵ洢����
	 \return ���� \b ָ������ ������
	*/
	friend inline StoredType& GetImplRef(ResourcePoolStorage& sp)
	{
		return sp._pointee;
	}
protected:
	//! Ĭ�Ͽյ���Դ
	/*!
	 \return ���� \c NULL
	 */
	static StoredType Default()
	{
		return NULL;
	}
	//! ɾ���������Դ������Դ����������ء��÷�������û���ص� Return ����
	/*!
	 \param p ��Դ�����
	 */
	void Delete(Pool* p)
	{
		if(p)
			p->Return(_pointee);
	}
private:
	//<! �������Դ
	StoredType _pointee;
};

//! ��Դ�ص�ӵ���߲��ԣ�\class RefCounted ���ò��ԣ�ʵ�����ü�����
/*!
 \param T ��Դ����
 */
template<class T>
class RefCounted
{
private:
	//<! ��Դ����
	typedef T ObjectType;
	//<! ��Դָ������
	typedef T* PointerType;
	//<! ��Դ���ü���
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
	 \brief �������캯��
	 \param rhl �����Ķ���
	 */
	RefCounted(const RefCounted& rhl):_pRefCnt(rhl._pRefCnt)
	{}
	//! clone �����������ü����� 1 
	/*!
	 \param val ��Դ������
	 \return ������Դ������
	 */
	ObjectType Clone(const ObjectType& val)
	{
		++*_pRefCnt;
		return val;
	}
	//! �ͷ���Դ
	/*!
	 \param const T& ��Դ������ 
	 \return �����ü�����1, ������ü���Ϊ 0 ���� true ,���򷵻� false
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
	//! ������Դ
	/*!
	 \param rhl ��Ҫ��������Դ
	 */
	void Swap(RefCounted& rhl)
	{
		std::swap(_pRefCnt,rhl._pRefCnt);
	}
	//! �ݻٿ������� 
	enum { destructiveCopy = false };
};

//! ����ת�Ͳ���,����ת��
struct ConversionAllow
{
	enum {allowed = true };
	void Swap(ConversionAllow& )
	{}
};
//! ����ת�����ԣ�������ת��
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

//! �����ԣ��ǿռ��
/*!
 \param P ���ָ������
 */
template <class P>
struct RejectNullStrict
{
	//! constructor
	RejectNullStrict()
	{}
	//! copy-constructor, ������ʵ�ʵĿ�������
	/*!
	 \param P1 �������Ķ����ָ������
	 \param const RejectNullStrict<P1> 
	 */
	template <class P1>
	RejectNullStrict(const RejectNullStrict<P1>&)
	{}
	//! ��ʼ��ʱ��飬��� val Ϊ���׳��쳣
	/*!
	 \throw NullPointerException ��� val Ϊ NULL �׳��쳣
	 */
	static void OnInit(P val)
	{ if (!val) throw NullPointerException(); }
	
	//! ��鱻����ʱ��ָ�� \sa RejectNullStrict::OnInit
	void OnDereference(P val)
	{ OnInit(val); }
	//! ��鱻����ʱ��ָ�� \sa RejectNullStrict::OnInit
	void OnDereference(P val) const
	{ OnInit(val); }
	//! ����
	void Swap(RejectNullStrict&)
	{}        
};


//! ���� Pool ������ָ��
/*!
 ����ָ�벻���� new ���룬ʹ����ɺ���Զ�������Դ������أ�
 ������ָ�뱻����ʱ��������Դ���ÿ�����һ�ݣ�������ָ�����ͬһ����Դ��
 ����ָ��Ŀ������� thread-safe �ģ�����һ������ָ�벻Ҫ�ڶ���߳���ʹ�á�
 \param T  ����Ķ��������
 \param Pool �ض���
 \param OwnershipPolicy ӵ���߲���
 \param ConversionPolicy ����ת������
 \param StoragePolicy �������Ĳ���
 \param CheckPolicy ������
 \param ConstnessPolicy �������Ͳ���
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
	//<! �洢��������
	typedef StoragePolicy<T,Pool> SP;
	//<! ������Դ���ͣ�ָ��
	typedef typename SP::PointerType StoredType;
	
	//<! ���������
	typedef Pool PoolManageType;
	//<! ӵ���߲�������
	typedef OwnershipPolicy<StoredType> OP;
	//<! ת����������
	typedef ConversionPolicy CP;
	//<! ����������
	typedef CheckPolicy<StoredType> KP;
	
	struct NeverMatch;
	//<! ��ʽ��������
	typedef typename 
		xutil::Selector<CP::allowed,const StoredType&,NeverMatch>::Result ImplicitType;
	//<! ��ʽ��������
	typedef typename 
		xutil::Selector<!CP::allowed,const StoredType&,NeverMatch>::Result ExplicitType;
	//<! copy ���Զ���Ķ������ͣ����Ϊ copy-destructive ����Ϊ��const
	typedef typename 
		xutil::Selector<OP::destructiveCopy,PoolSmartObject,const PoolSmartObject>::Result CopyArg;
	//<! ��Դ����ض���
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
	//<! const pointer ����
	typedef typename ConstnessPolicy<T>::Result* ConstPointerType;
	//<! const reference ����
	typedef typename ConstnessPolicy<T>::Result& ConstReferenceType;
	//<! ��Դָ������
	typedef typename SP::PointerType PointerType;
	//<! ��Դ����������
	typedef typename SP::ReferenceType ReferenceType;
	//! copy-constructor
	/*!
	 \param rhs ����������ָ�����
	 */
	PoolSmartObject(CopyArg & rhs)
		:OP(rhs),SP(rhs),KP(rhs)
	{
		_pool = rhs._pool;
		GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
	}
	//! = ����������
	PoolSmartObject& operator=(CopyArg& rhs)
	{
		PoolSmartObject temp(rhs);
		temp.Swap(*this);
		return *this;
	}
	//! ��������,��Ԫ����
	/*!
	 \param p �����
	 \param o ��Դ����
	 \return ������Դ����ָ��
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
	//! ��������
	/*!
	 \param rhl Ҫ�����Ķ���
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
		// �����жԸö��������ȫ��ɾ����Pool �Զ����ն���
		if(OP::Release(GetImpl(*static_cast<SP*>(this))))
		{
			SP::Delete(_pool);
		}
	}
	//! -> ����������
	PointerType operator->()
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator->();
	}
	//! -> ����������
	ConstPointerType operator->() const
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator->();
	}
	//! * ����������
	ReferenceType operator*()
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator*();
	}
	//! * ����������
	ConstReferenceType operator*() const
	{
		KP::OnDereference(GetImplRef(*this));
		return SP::operator*();
	}
	//! ! ����������
	bool operator!() const // if(!sp)
	{
		return (GetImpl(*this) == 0);
	}
	//! == ����������
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
	//! != ����������
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
	//! < ����������
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
// PoolSmartObject ����������
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
//! ��Դ��
/*!
 \param T �������Դ����
 \param ThreadModel �߳�ģ�� Ĭ��Ϊ KSGMultiThreadmModel<1000>
 */
template<class T,class ThreadModel=KSGMultiThreadmModel<1000> >
class ResourcePool
{
public:
	//<! ����ָ���������
	typedef PoolSmartObject<T,ResourcePool<T,ThreadModel> > SmartObject;
	//<! �����������
	typedef T ObjType;
	//<! ��������ָ������
	typedef typename SmartObject::PointerType PointerType;
	//<! ���������
	typedef ResourcePool<ObjType,ThreadModel> PoolType;
	//<! ����ؿ��ö������
	typedef std::vector<PointerType> PoolQueueType;
	//<! ������������functor ����
	typedef boost::function0<PointerType> FunctorType;
private:
	//<! ���������
	int _poolMaxSize;
	//<! ������Դ�� functor
	FunctorType _functor;
	//<! logger
	// static log4cxx::LoggerPtr logger;
	//<! ������Դ����
	PoolQueueType _freeQueue;
	//<! �߳�ģ�͵Ļ������
	typename ThreadModel::MutexType _mutex;
public:
	//! default constructor
	ResourcePool()
	{}
	//! constructor
	/*!
	 \param func ������Դ�� functor \sa ResourcePool::FunctorType
	 */
	ResourcePool(FunctorType func):_functor(func)
	{}
	~ResourcePool()
	{
		Free();
	}
	//! ��ʼ�������
	/*!
	 \param maxsize ������������
	 \param func ��������ض���� functor \sa ResourcePool::FunctorType
	 */
	void Init(int maxsize,FunctorType func)
	{
		_poolMaxSize = maxsize;
		_functor = func;
		Init(maxsize);
	}
	//! ��ʼ�������
	/*!
	 \param maxsize ������������
	 */
	void Init(int maxsize)
	{
		_poolMaxSize = maxsize;
		//LOG4CXX_INFO(logger,_T("���ػ����,��С:")<<_poolMaxSize);
		Free();
		for (int i = 0;i < _poolMaxSize;++i)
		{
			PointerType p = _functor();
			if(!p)
				throw NullPointerException();
			_freeQueue.push_back(p);
		}

	}
	//! �ͷ����л����еĶ���
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
	//! ������������
	inline int MaxSize() const
	{
		return _poolMaxSize;
	}
	//! ����ص�ǰ������
	inline int Count() const
	{
		return static_cast<int>(_freeQueue.size());
	}
	//! ������Դ���������
	void Return(PointerType p)
	{
		//LOG4CXX_DEBUG(logger,_T("�黹������Դ"));
		ThreadModel lock(_mutex);
		_freeQueue.push_back(p);
	}
	//! ������Դ�����û����Դ�������׳� NoneResourceException �쳣
	/*!
	 \param obj ���������Դ���浽 obj ��
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
		//LOG4CXX_DEBUG(logger,_T("������Դ�ɹ�"));
	}
	//! ������Դ�����û����Դ�������׳� NoneResourceException �쳣
	/*!
	 \return ������Դ������ָ��
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
		//LOG4CXX_DEBUG(logger,_T("������Դ�ɹ�"));
		return temp;
	}
	//! == ����������
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

