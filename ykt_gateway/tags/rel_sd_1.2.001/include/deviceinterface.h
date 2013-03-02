#ifndef _DEVICE_INTERFACE_H_
#define _DEVICE_INTERFACE_H_
/*! @file
 *	ģ����:			һ��ͨǰ�û�
 *	�ļ���: 		deviceinterface.h
 *	�ļ�ʵ�ֹ���:	ϵͳ����ʱ�豸���������ӿڶ���
 *	����:			����
 *	�汾:			V1.0
 *	��ע:	
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
//<! ָ��ִ��������ӿڶ���
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

//! ���󹤳�,���ڲ������еĽӿ���
typedef AbstractFactory
<
TYPELIST_4(DevAbstractObject,KSGDeviceLoader,KSGDeviceInterfaceLoader,TaskExecutorLoader)
> AbstractDeviceInterfaceFactory;


//! ʹ��singletonģʽ������Ʒ����,���幤���ӿ��ඨ��
/*
\param AtomicType ��Ʒ����ӿ�����
\param Base �̳и���������
*/
template<class AtomicType,class Base>
class SingletonConcreteFactoryUnit : Base
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
		typedef typename xutil::SingletonHolder<AtomicType,KSGSingleThreadModel> 
			AtomicSingleton;
		return &(AtomicSingleton::Instance());
	}
};

//<! ϵͳ���󹤳������Ͷ���
typedef FactoryBuilder<DevIdentifierType,AbstractDeviceInterfaceFactory> 
		KSGFactoryInterface;
//<! ϵͳ���󹤳��� singleton
typedef xutil::SingletonHolder
<
KSGFactoryInterface,MTTheadModel
>KSGFactoryBuilder;

//! ���幤���ඨ��Ľӿ�
/*
 ������幤��ʱ����ͨ�� ConcreteFactory ������,ʹ�� KSGDeviceInterfaceFactory ������
 \param TList ������Ʒ�����б�
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

//! \def KSG_REG_FACTORY_INTERFACE ע��һ��������ʵ��
#define KSG_REG_FACTORY_INTERFACE(id,clazz) \
	static bool clazz##Registered = _RegisterDeviceInterface<clazz>(id)

//! \def KSG_GET_FACTORY_INTERFACE ��ȡ������ʵ��
/*
 \throw DevTypeFactoryNotExists ����ʶΪid�Ĺ����������׳��쳣
 */
#define KSG_GET_FACTORY_INTERFACE(id,inter) \
	try { \
	AbstractDeviceInterfaceFactory& _f = KSGFactoryBuilder::Instance().GetFactory(id); \
	inter = &_f; \
	} catch(DevTypeFactoryNotExists& e) { throw e; } 

//! \def _KSG_GET_FACTORY_INTERFACE_OBJECT �ӹ������д���һ������
/*
 \throw DevTypeFactoryNotExists ����ʶΪid�豸�����������׳��쳣
 */
#define _KSG_GET_FACTORY_INTERFACE_OBJECT(id,clazz,obj) do{ \
	AbstractDeviceInterfaceFactory* _f1; \
	KSG_GET_FACTORY_INTERFACE(id,_f1); \
	obj = reinterpret_cast<clazz*>(_CALL_FACTORY_CREATE(_f1,clazz)); }while(0)

//! \def KSG_GET_DEV_ABSTRACT_OBJ �ӹ������д���һ���豸���󹤳�����
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

//! \def KSG_REG_DEVICE_OBJECT�����豸���󹤳���ע��һ���豸����
/*
 ����ע����豸���붨�塡DECLARE_FACTORY_CREATOR
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



