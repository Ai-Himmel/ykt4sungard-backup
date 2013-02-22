#ifndef _REQUEST_BG_INFO_H_
#define _REQUEST_BG_INFO_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================ 	
* 函数名：    Login
* 参数：      [in]  无
* 功能描述:   客户端发起到后台签到, 获取密钥, 配置drtp信息
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall Login();

/*================================================================ 
* 函数名：    GetCustomerInfo
* 参数：      [in]  (const char *szStuempNo)学工号
* 参数：      [out] (CustomerInfo *CutInfo)客户信息
* 功能描述:   获取客户信息
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall GetCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo);

/*================================================================ 
* 函数名：    GetCurBalance
* 参数：      [in]  (const char *szStuempNo)学工号
* 参数：      [out] (double *dCurBalance)获取的学生卡金额
* 功能描述:   获取客户信息
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall GetCurBalance(const char szStuempNo[21], double *dCurBalance);

/*================================================================ 
* 函数名：    GetTradeSerial
* 参数：      [in]  (int nDeviceId)设备号
* 参数：      [out] (TradeSerial **Serial)交易流水明细
* 参数：      [in]	(int *nNextFlag)获取是否有下一次包的标记
* 参数：      [in]	(int nInputFlag)输入可以获取的下一次包标记
* 参数：      [in]	(char *szBeginDate)流水发生开始(年:月:日)
* 参数：      [in]	(char *szEndDate)流水发生结束(年:月:日)

* 参数：      [in]	(char *szSerialYear)流水发生年份
* 参数：      [in]	(char *szSerialMonth)流水发生月份
* 参数：      [in]	(char *szBeginDay)流水发生开始日期
* 参数：      [in]	(char *szEndDay)流水发生结束日期
* 功能描述:   获取账户流水信息
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall GetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11]);

#ifdef __cplusplus
}
#endif

#endif