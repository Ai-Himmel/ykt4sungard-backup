#ifndef _KSG_FACTORY_H_
#define _KSG_FACTORY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <map>
#include <boost/function.hpp>
#include <boost/functional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include "ksgexception.h"
#include "xutils/xtype_trait.h"

//! singleton ���ԣ�Ϊ \class AbstractObject �ṩ singleton
/*
\param IType - ʵ����ʶ������
\param ObjType - ʵ������
*/
template<class IType,class ObjType>
class SingletonInstance
{
private:
	typedef std::map<IType,ObjType* > InstanceMapType;
	InstanceMapType _instances;
protected:
	void OnNewInstance(const IType& id,ObjType* p)
	{
		_instances.insert(typename InstanceMapType::value_type(id,p));
	}
	ObjType* Find(const IType& id)
	{
		typename InstanceMapType::iterator i = _instances.find(id);
		if(i != _instances.end())
		{
			return i->second;
		}
		return NULL;
	}
	void FreeInstanceObj(typename InstanceMapType::value_type& p)
	{
		delete p.second;
	}
public:
	virtual ~SingletonInstance()
	{
		std::for_each(_instances.begin(),_instances.end(),
			boost::bind(&SingletonInstance::FreeInstanceObj,this,_1));
	}
};

//! ���󹤳���
/*
\param IdentifierType ������ʶ����
\param ObjectType ���ɵĶ����������
\param Creator ����������
\param InstancePolicy ʵ���������
*/
template
<
	class IdentifierType,
	class ObjectType,
	class Creator = ObjectType* (*)(),
	template<class,class> class InstancePolicy = SingletonInstance
>
class AbstractObject : protected InstancePolicy< IdentifierType,ObjectType >
{
private:
	//<! ʵ�������������
	typedef InstancePolicy<IdentifierType,ObjectType> IP;
	//<! ʵ����������������
	typedef std::map<IdentifierType,Creator> AccMap;
	//<! ʵ��������
	AccMap _accs;
	//! ����ʵ��������
	/*
	\param id ʵ����ʶ
	\return ʵ������������
	\throw KSGException ���û���ҵ���ʶ����Ӧ�Ĵ������׳��쳣
	*/
	Creator FindCreator(const IdentifierType& id)
	{
		typename AccMap::iterator i = _accs.find(id);
		if(i == _accs.end())
		{
			throw KSGException();
		}
		return i->second;
	}
public:
	//<! ����������
	typedef Creator CreatorType;
	AbstractObject(){}
	virtual ~AbstractObject(){}
	//<! ��ȡ����
	/*
	\param id �����ʶ
	\return ���ر�ʶ��Ӧ�Ķ���ʵ��ָ��
	\throw KSGException �����ʶ�������׳��쳣
	*/
	ObjectType* Create(const IdentifierType& id)
	{
		ObjectType* obj = IP::Find(id);
		if(obj == NULL)
		{
			Creator cr = FindCreator(id);
			obj = cr();
			IP::OnNewInstance(id,obj);
		}
		return obj;
	}
	//! ע��һ����������
	/*
	\param id ��ʶ
	\param creator ������
	\throw KSGException �����ʶ�Ѵ����׳��쳣
	*/
	void Register(const IdentifierType& id,Creator creator)
	{
		typename AccMap::iterator i = _accs.find(id);
		if(i == _accs.end())
		{
			_accs.insert(typename AccMap::value_type(id,creator));
			return;
		}
		throw KSGException();
	}
	//<! ȡ��ע�����
	/*
	\param id ��ʶ
	*/
	void Unregister(const IdentifierType& id)
	{
		typename AccMap::iterator i = _accs.find(id);
		if(i == _accs.end())
		{
			return;
		}
		_accs.erase(i);
	}
};

//! ���󹤳����ڴ�����Ӧ�Ķ���Ľӿ�
/*
\param T �����Ķ�������
*/
template<class T>
class AbstractFactoryUnit
{
public:
	//<! ��������,������ʵ��
	virtual T* DoCreate(xutil::Type2Type<T>) = 0;
	//<! destructor
	virtual ~AbstractFactoryUnit(){}
};

//! ���󹤳��ӿ�
/*
\param TList �����Ʒ����
\param Unit ����������Ʒ�ӿ�����
*/
template<class TList,template<class> class Unit = AbstractFactoryUnit>
class AbstractFactory : 
	public xutil::GenScatterHierarchy<TList,Unit>
{
public:
	//<! ��Ʒ�����б�����
	typedef TList ProductList;
	//! ����������Ʒ
	/*
	\param T ��Ʒ����
	\return ���ش����Ĳ�Ʒ�����ָ��
	*/
	template<class T> T* Create()
	{
		Unit<T>& unit = *this;
		return unit.DoCreate(xutil::Type2Type<T>());
	}
};

//! ������Ʒ����
/*
\param AtomicType ��Ʒ����ӿ�����
\param Base �̳и���������
*/
template<class AtomicType,class Base>
class ConcreteFactoryUnit : Base
{
	//<! �������в�Ʒ�����б�����
	typedef typename Base::ProductList BaseProductList;
protected:
	//<! �����������һ����Ʒ����
	typedef typename BaseProductList::Tail ProductList;
public:
	//<! �������е�һ����Ʒ��������
	typedef typename BaseProductList::Head AbstractProduct;
	//<! ���󹤳��ӿڷ���,ʹ�� new ����������
	/*
	 \param xutil::Type2Type<AbstractProduct> ��Ʒ��������
	 */
	AtomicType* DoCreate(xutil::Type2Type<AbstractProduct>)
	{
		return new AtomicType;
	}
};

//! �����ӿڶ���
template<
	class AFactory,
	template<class,class> class AUnit,
	class TList = typename AFactory::ProductList
>
class ConcreteFactory : 
	public xutil::GenLinearHierarchy<
	typename xutil::TL::Reverse<TList>::Result,AUnit,AFactory>
{
public:
	typedef typename AFactory::ProductList AbstractProductList;
	typedef TList ProductList;
};


template
<
	class IdentityType,
	class AbstractType
>
class FactoryBuilder
{
private:
	typedef boost::shared_ptr<AbstractType> StorageType;
	typedef std::map<IdentityType,StorageType> FactoryMapType;
	FactoryMapType _s_Factories;
	void FreeAllFactories()
	{
		_s_Factories.clear();
	}
public:
	FactoryBuilder(){}
	~FactoryBuilder()
	{
		FreeAllFactories();
	}
	bool RegisterFactory(const IdentityType& fid,AbstractType* factory)
	{
		assert(factory != NULL);
		StorageType ptr(factory);
		if(!_s_Factories.empty())
			if(_s_Factories.find(fid) != _s_Factories.end())
			{
				throw DevTypeFactoryAlreadyExistsException();
			}
		return _s_Factories.insert(typename FactoryMapType::value_type(fid,ptr)).second;
	}
	AbstractType& GetFactory(const IdentityType& fid)
	{
		typename FactoryMapType::iterator i = _s_Factories.find(fid);
		if(i == _s_Factories.end())
		{
			throw DevTypeFactoryNotExists();
		}
		return *(i->second);
	}
};

#define DECLARE_FACTORY_CREATOR(clazz) \
	static bool clazz##Registered;			\
	static clazz* clazz##CreateObject() {\
	return new clazz; }

#define _CALL_FACTORY_CREATE(f,clazz) \
	f->Create<clazz>()


#endif // _KSG_FACTORY_H_
