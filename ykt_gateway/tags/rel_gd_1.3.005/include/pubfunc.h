#ifndef _KSG_PUBFUNC_H_
#define _KSG_PUBFUNC_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <string>

//! 获取系统参数
/*!
 \param param 系统参数号
 \param value 系统参数值
 \return 成功返回0, 失败返回 -1
 */
int KsgGetSystemParam(int param,std::string& value);

#endif // _KSG_PUBFUNC_H_
