#ifndef _KSG_MID_DEF_H_
#define _KSG_MID_DEF_H_

#ifdef _MSC_VER
#pragma once
#endif 

#include "ksglobal.h"
#include "mytypes.h"
namespace MIDSVR{
	enum MESSAGETYPE	// ��Ϣ��(Ϊż����ֵ��ʾ���ķ���Ϊ�ն�һ����Ϊ������ʾ���ķ���Ϊ��̨һ��)
	{
		
		MID_POLICYCHECK					= 0x71, //��Ȩ
		MID_INCBLC						= 0x77 //��ֵ
		
	};
}

#define KSG_MID_LISTENER 1002

#define MID_SYSPARAM_LISTEN_PORT 25333

#endif