#ifndef _HANDLE_CARD_H_
#define _HANDLE_CARD_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/*================================================================ 
* 函数名：    ConnectMF
* 参数：      [in] (int port)端口
* 参数：      [in] (int baud)波特率
* 功能描述:   打开串口
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall ConnectMF(int port, int baud);

/*================================================================ 
* 函数名：    CloseMF
* 参数：      [in] 无
* 功能描述:   关闭串口
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall CloseMF();

/*================================================================ 
* 函数名：    DelMomey
* 参数：      [in]  (int nMoney)扣款金额
* 参数：      [out] (int &nFlowNo)消费流水号
* 功能描述:   POS扣费
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall DelMomey(int nMoney,int &nFlowNo);

/*================================================================ 
* 函数名：    MendPacket
* 参数：      [out] (int &BnMoney)冲正前余额
* 参数：      [out] (int &AnMoney)冲正后余额
* 功能描述:   最后一笔金额冲正
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall MendPacket(int &BnMoney,int &AnMoney);

/*================================================================ 
* 函数名：    ReadStuEmpNo
* 参数：      [out] (BYTE *ucStuEmpNo)可获得的学工号
* 功能描述:   读取学工号
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall ReadStuEmpNo(unsigned char ucStuEmpNo[21]);

/*================================================================ 
* 函数名：    ReadBalance
* 参数：      [out] (int &nMoney)卡余额
* 功能描述:   POS读取卡余额
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall ReadBalance(int &nMoney);

/*================================================================ 
* 函数名：    GetCustomerInfo
* 参数：      [in]  (const char *szStuempNo)学工号
* 参数：      [out] (CustomerInfo *CutInfo)客户信息
* 功能描述:   获取客户信息
* 返回值：    int, 正确返回0, 失败返回错误码
================================================================*/
int __stdcall GetCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo);

int __stdcall ReadCutName(unsigned char ucCutName[9]);

int __stdcall ReadCutSex(unsigned char ucCutSex[2]);

#ifdef __cplusplus
}
#endif

#endif