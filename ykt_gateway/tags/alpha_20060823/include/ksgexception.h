#ifndef _KSGEXCEPTION_H_
#define _KSGEXCEPTION_H_
/*! @file
 *	ģ����:	һ��ͨͨ��ǰ�û�
 *	�ļ���: 	ksgexception.h
 *	�ļ�ʵ�ֹ���: �쳣�ඨ��
 *	����:	����
 *	�汾:	V1.0
 *	��ע:	
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

//! \class ��ָ���쳣
class NullPointerException : public KSGException
{};
//! \class ������޿�����Դ�쳣
class NoneResourceException : public KSGException
{};
//! \class �豸�ӿ��ظ�����
class DevIntrDuplication : public KSGException
{};
//! \class ָ�֧���쳣
class TaskNotSupportedException : public KSGException
{};
//! \class ָ���Ѿ������쳣
class TaskAlreadyExistsException : public KSGException
{};
//! \class ָ���������
class TaskQueueExceedException: public KSGException
{};

//! \class �����Ѿ��������쳣
class ConfigFrozenException: public KSGException
{};
//! \class �豸��ַ��Ϣ����ȷ
class DeviceAddrUrlException: public KSGException
{};
//! \class �豸����Ѵ���
class DeviceIdAlreadyExists: public KSGException
{};
//! \class ��֧�ַ����쳣
class NotSupportedMethodException : public KSGException
{};
//! \class �豸�����Ѿ�ע��
class DevTypeFactoryAlreadyExistsException : public KSGException
{};
//! \class �豸�������Ͳ�����
class DevTypeFactoryNotExists: public KSGException
{};
//! \class �豸���Ͳ�����
class DevTypeNotExists: public KSGException
{};
//! \class LOOP �豸�������쳣
class LoopDeviceNotExists: public KSGException
{};
//! \class ��ʶ�ظ�
class IdentifireAlreadyExists : public KSGException
{};
//! \class ��ʱ����
class TimeoutException : public KSGException
{};
//! \class �˿��ѱ�ռ��
class PortHasBeenUsedException : public KSGException
{};
//! \class �޷��������쳣
class CannotListenException : public KSGException
{};
//! \class ֵ�޷��ҵ�
class KeyNotFoundException : public KSGException
{};

#endif // _KSGEXCEPTION_H_
