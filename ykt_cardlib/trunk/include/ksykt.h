#ifndef _KSYKT_H_
#define _KSYKT_H_

#ifndef NOUSE_MFC
#define NOUSE_MFC
#endif

#include "carddll_def.h"

//用预编译指令使C函数能被C++程序直接调用
#ifdef __cplusplus
extern "C" {
#endif

	

//发行卡结构定义
#pragma pack(1)



#pragma pack()

#ifndef CALLAPI
#define CALLAPI __stdcall
#endif

#ifdef __cplusplus
}
#endif

#endif // _KSYKT_H_
