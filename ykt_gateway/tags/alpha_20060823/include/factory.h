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

//! singleton 策略，为 \class AbstractObject 提供 singleton
/*
\param IType - 实例标识号类型
\param ObjType - 实例类型
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

//! 抽象工厂类
/*
\param IdentifierType 主键标识类型
\param ObjectType 生成的对象抽象类型
\param Creator 创建器类型
\param InstancePolicy 实例管理策略
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
	//<! 实例管理策略类型
	typedef InstancePolicy<IdentifierType,ObjectType> IP;
	//<! 实例创建器容器类型
	typedef std::map<IdentifierType,Creator> AccMap;
	//<! 实例创建器
	AccMap _accs;
	//! 查找实例创建器
	/*
	\param id 实例标识
	\return 实例创建器对象
	\throw KSGException 如果没有找到标识所对应的创建器抛出异常
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
	//<! 创建器类型
	typedef Creator CreatorType;
	AbstractObject(){}
	virtual ~AbstractObject(){}
	//<! 获取对象
	/*
	\param id 对象标识
	\return 返回标识对应的对象实例指针
	\throw KSGException 如果标识不存在抛出异常
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
	//! 注册一个对象类型
	/*
	\param id 标识
	\param creator 创建器
	\throw KSGException 如果标识已存在抛出异常
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
	//<! 取消注册对象
	/*
	\param id 标识
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

//! 抽象工厂用于创建对应的对象的接口
/*
\param T 创建的对象类型
*/
template<class T>
class AbstractFactoryUnit
{
public:
	//<! 创建对象,由子类实现
	virtual T* DoCreate(xutil::Type2Type<T>) = 0;
	//<! destructor
	virtual ~AbstractFactoryUnit(){}
};

//! 抽象工厂接口
/*
\param TList 抽象产品类型
\param Unit 创建工厂产品接口类型
*/
template<class TList,template<class> class Unit = AbstractFactoryUnit>
class AbstractFactory : 
	public xutil::GenScatterHierarchy<TList,Unit>
{
public:
	//<! 产品类型列表类型
	typedef TList ProductList;
	//! 创建工厂产品
	/*
	\param T 产品类型
	\return 返回创建的产品对象的指针
	*/
	template<class T> T* Create()
	{
		Unit<T>& unit = *this;
		return unit.DoCreate(xutil::Type2Type<T>());
	}
};

//! 创建产品方法
/*
\param AtomicType 产品抽象接口类型
\param Base 继承父对象类型
*/
template<class AtomicType,class Base>
class ConcreteFactoryUnit : Base
{
	//<! 父对象中产品类型列表类型
	typedef typename Base::ProductList BaseProductList;
protected:
	//<! 父对象中最后一个产品类型
	typedef typename BaseProductList::Tail ProductList;
public:
	//<! 父对象中第一个产品对象类型
	typedef typename BaseProductList::Head AbstractProduct;
	//<! 抽象工厂接口方法,使用 new 来创建对象
	/*
	 \param xutil::Type2Type<AbstractProduct> 产品抽象类型
	 */
	AtomicType* DoCreate(xutil::Type2Type<AbstractProduct>)
	{
		return new AtomicType;
	}
};

//! 工厂接口对象
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
