#ifndef _GWLOOP_H_
#define _GWLOOP_H_

#include "localinterface.h"

#ifdef __cplusplus
extern "C" {
#endif 

#ifdef WIN32
#ifdef GWLOOP_EXPORTS
#define GWLOOP_API __declspec(dllexport)
#else
#define GWLOOP_API __declspec(dllimport)
#endif
#else
#define GWLOOP_API
#endif //WIN32


//! 初始化函数,系统加载时自动调用一次
/*!
 \return 返回0表示初始化成功,否则返回-1
 */
GWLOOP_API int __stdcall Initialize();
//! 释放资源函数,系统正常退出时自动调用,但系统在不正常退出时不一定调用.
/*!
 \return 返回 0 表示初始化成功, 否则返回 -1
 */
GWLOOP_API int __stdcall Uninitialize();
//! 接收请求函数
/*!
 \param request_no 请求交易号
 \param pack 请求数据包内容,也作为返回数据包
 \return 0 返回0 表示处理成功, 否则返回错误码,并在pack->outdata中保存错误信息
 */
GWLOOP_API int __stdcall ProcessRequest(int request_no,request_pack * pack);

#ifdef __cplusplus
}
#endif 
#endif // _GWLOOP_H_
