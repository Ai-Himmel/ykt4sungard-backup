#ifndef _KSGLOBAL_H_
#define _KSGLOBAL_H_
/*! @file
 *	ģ����:		һ��ͨͨ��ǰ�û�
 *	�ļ���: 	ksglobal.h
 *	�ļ�ʵ�ֹ���:	���ó����Ķ���
 *	����:	����
 *	�汾:	V1.0
 *	��ע:	
*/
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
//#include <tchar.h>
#include <Windows.h>
#endif

#ifdef _MSC_VER 
#pragma once
#if (_MSC_VER == 1200) // for vc6
#pragma warning (disable: 4786)
#endif
#if (_MSC_VER >= 1400) // for vc 2005
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#pragma warning (disable: 4996)
#pragma warning (disable: 4244)
#endif
#pragma warning (disable: 4099)
#pragma warning (disable: 4819)
#endif


// ����
class KSGateway;
extern KSGateway* theGlobalGateWay;
inline KSGateway* KsgGetGateway()
{
	return theGlobalGateWay;
}

#ifdef KSG_DUMP_EXCEPTION
#undef KSG_DUMP_EXCEPTION
#endif

#ifdef _DEBUG
#define KSG_DUMP_EXCEPTION(x) do { \
	ACE_DEBUG((LM_ERROR,"Dump Exception id(%s)",typeid(x).name()));  \
	} while(0) 
#else
#define KSG_DUMP_EXCEPTION(x)
#endif 

#ifdef DECLARE_NAMESPACE_BEGIN
#undef DECLARE_NAMESPACE_BEGIN
#endif

#define DECLARE_NAMESPACE_BEGIN(x) namespace x {

#ifdef DECLARE_NAMESPACE_END
#undef DECLARE_NAMESPACE_END
#endif

#define DECLARE_NAMESPACE_END(x) }

//<! ���������ļ�������
#define KSG_COMMON_SECT "COMMON"
#define KSG_MAJOR_VER	"MAJOR"
#define KSG_MINOR_VER	"MINOR"
//
#define KSG_SERVER_SECT "SERVER"
#define KSG_SVR_IP		 "ip"
#define KSG_SVR_PORT	 "port"
#define KSG_SVR_MAINFUNC "mainfunc"
#define KSG_SVR_BRANCE_NO "drtpno"
#define KSG_SVR_POOL_CONN "poolconn"

#define KSG_GATEWAY_SECT "GATEWAY"
#define KSG_GW_IP "ip"

#define KSG_SCHEDULER_SECT "SCHEDULER"
#define KSG_SCHD_IDS	  "SCHDID"
#define KSG_LISTENER_IDS  "LISTENER"
#define KSG_SCHD_ALG	"ALGORITHM"

#define KSG_LOG_SECT "LOG"
#define KSG_LOG_LEVEL "LEVEL"
#define KSG_LOG_APPENDER "APPENDER"
#define KSG_LOG_FILE "FILE"
#define KSG_LOG_FILEMAX "FILEMAX"
#define KSG_LOG_MAX_COUNT "MAXCOUNT"

//<! �豸�������Ͷ���
#define KSG_999_DEV		"999"
#define KSG_HD_DEV		"hd"
#define KSG_HUNDURE_DEV "hundure"
#define KSG_LOOP_DEV	"loop"

#define KSG_LOOP_DEV_TYPE "LOOP"
#define KSG_NULL_DEV_TYPE "XXXX"


//////////////////////////////////////////////////////////////////////////
// ���������߳� ID ��
#define KSG_SCHD_RECV_TASK 1000
#define KSG_SCHD_COLL_HEARTBEAT 1001
#define KSG_SCHD_HD_TCP_SVR 1002
#define KSG_SCHD_COLL_SERIAL 1003
#define KSG_SCHD_LOOP_SVR	1004

//<! ���� DRTP ���ܺ�
//<! ǩ�����ܺ�
#define KSG_DRTP_ENROLL		950001
//<! ����ǰ�û����в������ܺ�
#define KSG_DRTP_DW_PARAMS	950002
//<! ���س������͵Ĺ��ܺ�
#define KSG_DRTP_VENDOR_CONFIG 950100
//<! ����ϵͳ����ʱ����
#define KSG_GET_SYSTEM_PARAM 950006


//////////////////////////////////////////////////////////////////////////
// ָ��ִ�еĴ�����
/*!
 \def TASK_SUCCESS 
 ָ��ִ�гɹ�
 */
#define TASK_SUCCESS			0
/*!
 \def TASK_ERR_BASE
 ָ����������ֵ
 */
#define TASK_ERR_BASE			1000
/*!
 \def TASK_ERR_TIMEOUT
 ָ��ִ�г�ʱ
 */
#define TASK_ERR_TIMEOUT		TASK_ERR_BASE + 1
/*!
 \def TASK_ERR_NOT_SUPPORT
 ָ�֧��
 */
#define TASK_ERR_NOT_SUPPORT	TASK_ERR_BASE + 2
/*!
 \def TASK_ERR_CONNECT
 �����豸ʧ��
 */
#define TASK_ERR_CONNECT		TASK_ERR_BASE + 3
/*!
 \def TASK_ERR_COMMON
 һ�����
 */
#define TASK_ERR_COMMON			TASK_ERR_BASE + 4

/*!
 \def TASK_ERR_EXECUTE
 �豸ִ��ָ��ʧ��
 */
#define TASK_ERR_EXECUTE		TASK_ERR_BASE + 5

/*!
 \def TASK_ERR_PARAM ��������
*/
#define TASK_ERR_PARAM			TASK_ERR_BASE + 6

#endif // _KSGLOBAL_H_

