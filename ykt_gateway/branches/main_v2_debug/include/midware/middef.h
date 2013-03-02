#ifndef _KSG_MID_DEF_H_
#define _KSG_MID_DEF_H_

#ifdef _MSC_VER
#pragma once
#endif 

#include "ksglobal.h"
#include "mytypes.h"
namespace MIDSVR{
	enum MESSAGETYPE	// 信息码(为偶数的值表示报文发起方为终端一方，为奇数表示报文发起方为后台一方)
	{
		
		MID_POLICYCHECK					= 0x71, //鉴权
		MID_INCBLC						= 0x77 //充值
		
	};
}

#define KSG_MID_LISTENER 1002

#define MID_SYSPARAM_LISTEN_PORT 25333

#endif