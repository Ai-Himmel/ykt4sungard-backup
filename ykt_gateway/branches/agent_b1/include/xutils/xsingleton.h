#ifndef _XSINGLETON_H_
#define _XSINGLETON_H_

XUTIL_NAMESPACE_BEGIN

#include <cassert>
#include <cstdlib>

#ifdef _MSC_VER
#define XUITL_CALLING_CONVERSION __cdecl
#else
#define XUITL_CALLING_CONVERSION
#endif

typedef void (XUITL_CALLING_CONVERSION *atexit_pfn_t)();

template<class T>
class CreationUsingNew
{
public:
	static T* Create()
	{
		return new T;
	}
	static void Destroy(T* p)
	{
		delete p;
	}
};

template<class T>
class NoDetroy
{
public:
	static void OnDeadReference()
	{

	}
	static void ScheduleDestroy(T* p,atexit_pfn_t pFunc)
	{

	}
};

template<class T>
class DefaultLifetime
{
public:
	static void OnDeadReference()
	{
		//
	}
	static void ScheduleDestroy(T* p,atexit_pfn_t pFunc)
	{
		atexit(pFunc);
	}
};

template<class T>
class NormalPointerStorage
{
	typedef typename xutil::Selector<xutil::PointerTrait<T>::result,
		typename xutil::PointerTrait<T>::Pointer,T>::Result ObjType;
	typedef ObjType* PtrType;
private:
	volatile PtrType _ptr;
public:
	explicit NormalPointerStorage(ObjType* p):_ptr(p)
	{}
	explicit NormalPointerStorage()
	{}
	~NormalPointerStorage()
	{
	}
	ObjType& operator*() const
	{
		return *_ptr;
	}
	ObjType* operator->() const
	{
		return _ptr;
	}
	ObjType* get() const
	{
		return _ptr;
	}
	bool operator!()
	{
		return (_ptr == NULL);
	}
	NormalPointerStorage& operator=(const NormalPointerStorage& rhs)
	{
		_ptr = rhs.get();
		return *this;
	}
	NormalPointerStorage& operator=(ObjType* p)
	{
		_ptr = p;
		return *this;
	}
};

template<
	class T,
	class ThreadModel,
	template<class> class CreatorPolicy = CreationUsingNew,
	template<class> class LifetimePolicy = DefaultLifetime,
	template<class> class PtrStoragePolicy = NormalPointerStorage
>
class SingletonHolder
{
public:
	typedef T ObjectType;
private:
	typedef PtrStoragePolicy<T> PtrInstanceType;
	typedef typename ThreadModel::MutexType MutexType;

	struct Initializer
	{
		MutexType _mtx;
		bool _init;
		Initializer():_init(false),_mtx()
		{
			_init = true;
		}
		~Initializer()
		{
			
		}
	};
	static Initializer _s_mutex;
	static PtrInstanceType _s_instance;
	static bool _s_detroyed;
	static void MakeInstance()
	{
		if(_s_mutex._init)
			ThreadModel lock(_s_mutex._mtx);
		if(!_s_instance)
		{
			if(_s_detroyed)
			{
				_s_detroyed = false;
				LifetimePolicy<T>::OnDeadReference();
			}
			_s_instance = CreatorPolicy<T>::Create();
			LifetimePolicy<T>::ScheduleDestroy(_s_instance.get(),&DestroyInstance);
		}
	}
	static void XUITL_CALLING_CONVERSION DestroyInstance()
	{
		assert(!_s_detroyed);
		try
		{
			CreatorPolicy<T>::Destroy(_s_instance.operator->());
			_s_instance = NULL;
			_s_detroyed = true;
		}
		catch(...)
		{
			// do nothing
		}
		
	}
protected:
	SingletonHolder(){}
public:
	static T& Instance()
	{
		if(!_s_instance)
		{
			MakeInstance();
		}
		return *_s_instance;
	}
};

template<class T,class TP,template<class> class CP,template<class> class LP,template<class> class SP>
typename SingletonHolder<T,TP,CP,LP,SP>::Initializer SingletonHolder<T,TP,CP,LP,SP>::_s_mutex;

template<class T,class TP,template<class> class CP,template<class> class LP,template<class> class SP>
typename SingletonHolder<T,TP,CP,LP,SP>::PtrInstanceType SingletonHolder<T,TP,CP,LP,SP>::_s_instance;

template<class T,class TP,template<class> class CP,template<class> class LP,template<class> class SP>
bool SingletonHolder<T,TP,CP,LP,SP>::_s_detroyed;

XUTIL_NAMESPACE_END

#endif // _XSINGLETON_H_
