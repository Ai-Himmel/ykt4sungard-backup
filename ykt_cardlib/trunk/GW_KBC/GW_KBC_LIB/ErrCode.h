#ifndef _ERR_CODE_H_
#define _ERR_CODE_H_
#pragma once

#define GW_ERR_INITFAILED				-1001			// KDBC初始化失败
#define GW_ERR_CREATEHANDLEFAILED		-1002			// 创建新的KDBC句柄失败
#define GW_ERR_HANDLENOTCREATE			-1003			// 未有创建新的KDBC句柄
#define GW_ERR_REQUESTFUNCFAILED		-1004			// 请求功能号失败
#define GW_ERR_REQUESTSERVERFAILED		-1005			// 请求服务器失败
#define GW_ERR_REQUESTPACKFAILED		-1006			// 请求数据包出错
#define GW_ERR_INPUTNULLFAILED			-1007			// 输入数据为空
#define GW_ERR_INPUTZEROFAILED			-1008			// 输入数据为零
#define GW_ERR_INPUTCARDIDFAILED		-1009			// 输入交易卡号不符
#define GW_ERR_INPUTPHYNOFAILED			-1010			// 输入物理卡号不符
#define GW_ERR_INPUTSTUEMPNOFAILED		-1011			// 输入学工号不符
#define GW_ERR_GETRETCODE				-1012			// 服务端返回码出错
#endif
