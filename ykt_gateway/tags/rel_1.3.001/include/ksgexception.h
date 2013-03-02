#ifndef _KSGEXCEPTION_H_
#define _KSGEXCEPTION_H_
/*! @file
 *	模块名:	一卡通通用前置机
 *	文件名: 	ksgexception.h
 *	文件实现功能: 异常类定义
 *	作者:	汤成
 *	版本:	V1.0
 *	备注:	
*/
#ifdef _MSC_VER
#pragma once
#endif

#include <exception>

class KSGException : public std::exception
{
public:
	KSGException():std::exception()
	{}
};

//! \class 空指针异常
class NullPointerException : public KSGException
{};
//! \class 缓存池无可用资源异常
class NoneResourceException : public KSGException
{};
//! \class 设备接口重复定义
class DevIntrDuplication : public KSGException
{};
//! \class 指令不支持异常
class TaskNotSupportedException : public KSGException
{};
//! \class 指令已经存在异常
class TaskAlreadyExistsException : public KSGException
{};
//! \class 指令队列已满
class TaskQueueExceedException: public KSGException
{};

//! \class 配置已经被锁定异常
class ConfigFrozenException: public KSGException
{};
//! \class 设备地址信息不正确
class DeviceAddrUrlException: public KSGException
{};
//! \class 设备编号已存在
class DeviceIdAlreadyExists: public KSGException
{};
//! \class 不支持方法异常
class NotSupportedMethodException : public KSGException
{};
//! \class 设备类型已经注册
class DevTypeFactoryAlreadyExistsException : public KSGException
{};
//! \class 设备工厂类型不存在
class DevTypeFactoryNotExists: public KSGException
{};
//! \class 设备类型不存在
class DevTypeNotExists: public KSGException
{};
//! \class LOOP 设备不存在异常
class LoopDeviceNotExists: public KSGException
{};
//! \class 标识重复
class IdentifireAlreadyExists : public KSGException
{};
//! \class 超时错误
class TimeoutException : public KSGException
{};
//! \class 端口已被占用
class PortHasBeenUsedException : public KSGException
{};
//! \class 无法打开侦听异常
class CannotListenException : public KSGException
{};
//! \class 值无法找到
class KeyNotFoundException : public KSGException
{};

#endif // _KSGEXCEPTION_H_
