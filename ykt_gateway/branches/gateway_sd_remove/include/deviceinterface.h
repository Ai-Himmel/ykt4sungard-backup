#ifndef _DEVICE_INTERFACE_H_
#define _DEVICE_INTERFACE_H_
/*! @file
 *	模块名:			一卡通前置机
 *	文件名: 		deviceinterface.h
 *	文件实现功能:	系统运行时设备工厂方法接口定义
 *	作者:			汤成
 *	版本:			V1.0
 *	备注:	
*/
#ifdef _MSC_VER
#pragma once
#endif
#include "factory.h"
#include "ksgexception.h"
#include "devicefactory.h"
#include "ksglobal.h"
#include "taskqueue.h"
#include "executor.h"
#include "thread.h"
#include "xutils/xsingleton.h"
#include <string>

typedef std::string DevIdentifierType;
//<! 指令执行器抽象接口定义
typedef AbstractObject<int,KSGTaskExecutor> TaskExecutorFactory;
typedef xutil::SingletonHolder<
AbstractObject<int,KSGTaskExecutor>,MTTheadModel
>KSGTaskExecutorFactory;

class TaskExecutorLoader
{
public:
	virtual int LoadExecutor()
	{
		return -1;
	}
};

//! 抽象工厂,用于产生所有的接口类
typedef AbstractFactory
<
TYPELIST_4(DevAbstractObject,KSGDeviceLoader,KSGDeviceInterfaceLoader,TaskExecutorLoader)
> AbstractDeviceInterfaceFactory;


//! 使用singleton模式创建产品方法,具体工厂接口类定义
/*
\param AtomicType 产品抽象接口类型
\param Base 继承父对象类型
*/
template<class AtomicType,class Base>
class SingletonConcreteFactoryUnit : Base
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
		typedef typename xutil::SingletonHolder<AtomicType,KSGSingleThreadModel> 
			AtomicSingleton;
		return &(AtomicSingleton::Instance());
	}
};

//<! 系统抽象工厂类类型定义
typedef FactoryBuilder<DevIdentifierType,AbstractDeviceInterfaceFactory> 
		KSGFactoryInterface;
//<! 系统抽象工厂类 singleton
typedef xutil::SingletonHolder
<
KSGFactoryInterface,MTTheadModel
>KSGFactoryBuilder;

//! 具体工厂类定义的接口
/*
 定义具体工厂时不用通过 ConcreteFactory 来定义,使用 KSGDeviceInterfaceFactory 来定义
 \param TList 工厂产品类型列表
 */
template<class TList>
struct KSGDeviceInterfaceFactory
{
	typedef ConcreteFactory<
		AbstractDeviceInterfaceFactory,
		SingletonConcreteFactoryUnit,
		TList> Result; 
};

template<class T>
bool inline _RegisterDeviceInterface(const DevIdentifierType& id)
{
	AbstractDeviceInterfaceFactory* factory = 
		reinterpret_cast<AbstractDeviceInterfaceFactory*>(new T);
	return KSGFactoryBuilder::Instance().RegisterFactory(id,factory);
}

//! \def KSG_REG_FACTORY_INTERFACE 注册一个工厂类实例
#define KSG_REG_FACTORY_INTERFACE(id,clazz) \
	static bool clazz##Registered = _RegisterDeviceInterface<clazz>(id)

//! \def KSG_GET_FACTORY_INTERFACE 获取工厂类实例
/*
 \throw DevTypeFactoryNotExists 当标识为id的工厂不存在抛出异常
 */
#define KSG_GET_FACTORY_INTERFACE(id,inter) \
	try { \
	AbstractDeviceInterfaceFactory& _f = KSGFactoryBuilder::Instance().GetFactory(id); \
	inter = &_f; \
	} catch(DevTypeFactoryNotExists& e) { throw e; } 

//! \def _KSG_GET_FACTORY_INTERFACE_OBJECT 从工厂类中创建一个对象
/*
 \throw DevTypeFactoryNotExists 当标识为id设备工厂不存在抛出异常
 */
#define _KSG_GET_FACTORY_INTERFACE_OBJECT(id,clazz,obj) do{ \
	AbstractDeviceInterfaceFactory* _f1; \
	KSG_GET_FACTORY_INTERFACE(id,_f1); \
	obj = reinterpret_cast<clazz*>(_CALL_FACTORY_CREATE(_f1,clazz)); }while(0)

//! \def KSG_GET_DEV_ABSTRACT_OBJ 从工厂类中创建一个设备抽象工厂对象
#define KSG_GET_DEV_ABSTRACT_OBJ(id,abobj) \
	_KSG_GET_FACTORY_INTERFACE_OBJECT(id,DevAbstractObject,abobj);

inline bool _DeviceObjectRegister(const DevIdentifierType& dev,NormalDeviceType dtype
							,DevAbstractObject::CreatorType cr)
{
	DevAbstractObject * factory; 
	KSG_GET_DEV_ABSTRACT_OBJ(dev,factory);
	if(factory)
	{
		factory->Register(dtype,cr); 
		return true;
	}
	throw KSGException();
}

//! \def KSG_REG_DEVICE_OBJECT　向设备抽象工厂中注册一个设备类型
/*
 可以注册的设备必须定义　DECLARE_FACTORY_CREATOR
 */
#define KSG_REG_DEVICE_OBJECT(dev,dtype,clazz) \
	bool clazz::clazz##Registered = _DeviceObjectRegister((dev),(dtype)\
	,reinterpret_cast<DevAbstractObject::CreatorType>((clazz::clazz##CreateObject)));

//! \def KSG_GET_DEVICE_OBJECT
#define KSG_GET_DEVICE_OBJECT(dev,dtype,devobj) do{ \
	DevAbstractObject * _f2 = NULL; \
	KSGDevice * temp = NULL; \
	KSG_GET_DEV_ABSTRACT_OBJ(dev,_f2); \
	if(_f2) { \
		temp = _f2->Create(dtype); \
	} \
	devobj = temp; } while(0)

#define KSG_GET_DEVICE_LOADER(dev,l) \
	_KSG_GET_FACTORY_INTERFACE_OBJECT(dev,KSGDeviceLoader,l)

#define KSG_GET_DEVINT_LOADER(dev,l) \
	_KSG_GET_FACTORY_INTERFACE_OBJECT(dev,KSGDeviceInterfaceLoader,l)

inline bool _DeviceInterfaceRegister(const DevIdentifierType& dev,
									int intcode,
									AbstractDevInterObject::CreatorType cr)
{
	KSGDeviceInterfaceLoader* l = NULL;
	KSG_GET_DEVINT_LOADER(dev,l);
	if(l)
	{
		l->Register(intcode,cr);
		return true;
	}
	throw IdentifireAlreadyExists();
}
#define KSG_REG_DEV_INTERFACE(dev,code,clazz) \
	bool clazz::clazz##Registered = _DeviceInterfaceRegister((dev),(code), \
		reinterpret_cast<KSGDeviceInterfaceLoader::CreatorType>((clazz::clazz##CreateObject)))

#define KSG_GET_DEV_INTERFACE(dev,code,inter) do{ \
	KSGDeviceInterfaceLoader* _dloader1 = NULL; \
	KSG_GET_DEVINT_LOADER(dev,_dloader1); \
	if(_dloader1) {inter = _dloader1->Create(code);} \
	}while(0)

#define KSG_ADD_DEVICE_INTERFACE(dev,devtype,code) do{\
	KSGDevice* _d = NULL; \
	KSG_GET_DEVICE_OBJECT(dev,devtype,_d); \
	KSGDeviceInterface* _di1 = NULL; \
	KSG_GET_DEV_INTERFACE(dev,code,_di1); \
	if(_d) _d->AddInterface(_di1); else throw DevTypeNotExists(); }while(0)

#define KSG_REGISTER_TASK_EXECUTOR(code,clazz) \
	KSGTaskExecutorFactory::Instance().Register(code,\
	reinterpret_cast<TaskExecutorFactory::CreatorType>(clazz::clazz##CreateObject))


#endif // _DEVICE_INTERFACE_H_



