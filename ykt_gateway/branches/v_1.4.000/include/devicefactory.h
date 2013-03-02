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
#include <ace/Singleton.h>
#include <xutils/xtypelist.h>
#include <boost/shared_ptr.hpp>
#include <string>
#include <map>

// 
typedef AbstractObject<NormalDeviceType,KSGDevice> DevAbstractObject;

typedef FactoryBuilder<std::string,DevAbstractObject> DevFactory;

typedef ACE_Singleton
<
DevFactory,ACE_SYNCH_MUTEX
>DeviceFactoryBuilder;


#endif // _DEVICE_FACTORY_H_


