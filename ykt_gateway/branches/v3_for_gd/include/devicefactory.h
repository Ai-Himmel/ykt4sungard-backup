#ifndef _DEVICE_FACTORY_H_
#define _DEVICE_FACTORY_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include "ksgexception.h"
#include "thread.h"
#include "factory.h"
#include "device.h"
#include <xutils/xsingleton.h>
#include <xutils/xtypelist.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

// 
typedef AbstractObject<NormalDeviceType,KSGDevice> DevAbstractObject;

typedef FactoryBuilder<std::string,DevAbstractObject> DevFactory;

typedef xutil::SingletonHolder
<
DevFactory,MTTheadModel
>DeviceFactoryBuilder;


#endif // _DEVICE_FACTORY_H_


