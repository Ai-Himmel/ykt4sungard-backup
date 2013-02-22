#ifndef _GW_KBC_H_
#define _GW_KBC_H_
#pragma once

#include "DataType.h"

/*================================================================ 
* 函数名：    GW_Login
* 功能描述:   登录网络(初始化drtp配置数据, 配置好通讯平台号, KCC功能号等)
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_Login();

/*================================================================ 
* 函数名：    GW_CreateNewHandle
* 功能描述:   创建客户端接口句柄
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_CreateNewHandle();

/*================================================================ 
* 函数名：    GW_CloseHandle
* 功能描述:   关闭网络请求资源
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_CloseHandle();

/*================================================================ 
* 函数名：    GW_Exit
* 功能描述:   退出接口库(陈永华这里未有实现)
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_Exit();

/*================================================================ 
* 函数名：    GW_CheckBillSerial
* 参数：      [out] (CheckBillSerial *serial)传入人员信息的ST_PACK字段
* 参数：      [out] (int *rec_count)获取返回的流水数目
* 参数：      [in]  (char begin_date[11])开始日期
* 参数：      [in]  (char end_date[11])结束日期
* 功能描述:   获取对账所需流水记录
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_CheckBillSerial(
								 CheckBillSerial serial[], 
								 int *rec_count,
								 char begin_date[11], 
								 char end_date[11]
							    );

/*================================================================ 
* 函数名：    GW_GetCardInfo
* 参数：      [in]	(char physical_no[9])传入的物理卡号
* 参数：      [out] (CardInfo *card_info)获取的卡信息
* 功能描述:   获取卡信息
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_GetCardInfo(char physical_no[9], CardInfo *card_info);

/*================================================================ 
* 函数名：    GW_GetLastErrorMsg
* 参数：      [out] (char *error_msg)获取上次操作失败的错误信息
* 功能描述:   获取错误信息
* 返回值：	  void
================================================================*/
void __stdcall GW_GetLastErrorMsg(char *error_msg);

/*================================================================ 
* 函数名：    GW_DataInfo
* 参数：      [in]	(char physical_no[9])传入的客户号
* 参数：      [out] (CutInfo *card_info)获取的客户信息
* 功能描述:   获取客户信息
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_DataInfo(char physical_no[9], char stuemp_no[22], DataInfo *data_info);

/*================================================================ 
* 函数名:     GW_GetDataRecordExA
* 参数:       [in] (card_id)传入的交易卡号
* 参数:       [in] (physical_no)传入的物理卡号
* 参数:		  [in] (stuemp_no)传入的学工号
* 参数:		  [out] (DataInfo *data_info)获取的数据信息
* 功能描述:   获取个人数据记录信息
* 返回值:     int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_GetDataRecordExA(int card_id, char physical_no[9], char stuemp_no[22], DataInfo *data_info);

/*================================================================ 
* 函数名：    GW_GetCustomerInfo
* 参数：      [in]	(int cut_id)传入的客户号
* 参数：      [out] (CutInfo *card_info)获取的客户信息
* 功能描述:   获取客户信息
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_GetCustomerInfo(int cut_id, CutInfo *cut_info);

/*================================================================ 
* 函数名：    GW_GetSeedKey
* 参数：      [out] (char *seed_key)获取后台种子密钥
* 功能描述:   获取后台种子密钥
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int __stdcall GW_GetSeedKey(char *seed_key);

/*================================================================ 
* 函数名：    GW_CheckDeposit
* 参数：      [in] (int card_id)传入的交易卡号
* 功能描述:   通过交易卡号查询学员是否交过押金
* 返回值:     int, -1:不需交 0:已交 1:应交 其他值错误
================================================================*/
int __stdcall GW_CheckDeposit(int card_id);

/*================================================================ 
* 函数名：    GW_DepositHandin
* 参数：      [in] card_info[0]:卡号, card_info[1]: 交易次数, card_info[2]:卡片金额(分)
* 参数：      [out] out_depinfo[0]:后台入账流水号, out_depinfo[1]: 押金(分), out_depinfo[2]:后台出卡值(分)
* 功能描述:   交押金
* 返回值:     int, 0正确 其他值错误
================================================================*/
int __stdcall GW_DepositHandin(int card_info[3],int out_depinfo[3]);

//退押金
int __stdcall GW_DepositHandback(int card_info[3],int out_depinfo[3]);

//写卡失败后冲正
int __stdcall GW_DepositBackoff(int card_id,int serial_no);

/*================================================================ 
* 函数名：    F950006
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [out] (char *seed_key)获取后台种子密钥
* 功能描述:   请求950006功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F950006(KBDCHandle handle, char *seed_key);

/*================================================================ 
* 函数名：    F841605
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [in]	(int cut_id)传入的客户号
* 参数：      [out] (CutInfo *cut_info)获取的客户信息
* 功能描述:   请求841605功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F841605(KBDCHandle handle, int cut_id, char stuemp_no[22], CutInfo *cut_info);

/*================================================================ 
* 函数名：    F847173
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [in]	(char physical_no[9])传入的物理卡号
* 参数：      [out] (CardInfo *card_info)获取的卡信息
* 功能描述:   请求847173功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F847173(KBDCHandle handle, char physical_no[9], CardInfo *card_info);

/*================================================================ 
* 函数名：    F842005
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [in]	(char *classdept_no)传入的部门编号
* 参数：      [out] (char *classdept_name)获取部门名称
* 功能描述:   请求842005功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F842005(KBDCHandle handle, char *classdept_no, char *classdept_name);

/*================================================================ 
* 函数名：    F847175
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [out] (CheckBillSerial *serial)传入人员信息的字段
* 参数：      [in]  (char begin_date[11])开始日期
* 参数：      [in]  (char end_date[11])结束日期
* 参数：      [out] (int *rec_count)获取返回的流水数目
* 功能描述:   请求847175功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F847175(KBDCHandle handle, CheckBillSerial serial[], char begin_date[11], char end_date[11], int *rec_count);

/*================================================================ 
* 函数名：    F841700
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [in]	(char physical_no[9])传入的物理卡号
* 参数：      [in]  (char stuemp_no[22])传入的学工号
* 参数：      [in]  (CutInfo *cut_info)传入的客户信息
* 参数：      [in]  (CardInfo *card_info)传入的卡信息
* 功能描述:   请求841700功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F841700(KBDCHandle handle, char physical_no[9], char stuemp_no[22], CutInfo *cut_info, CardInfo *card_info);

/*================================================================ 
* 函数名：    F841700ExA
* 参数：      [in]  (KBDCHandle handle)KDBC服务句柄
* 参数：      [in]	(char physical_no[9])传入的物理卡号
* 参数：      [in]  (char stuemp_no[22])传入的学工号
* 参数：      [in]  (CutInfo *cut_info)传入的客户信息
* 参数：      [in]  (CardInfo *card_info)传入的卡信息
* 参数：      [in]  (DataInfo *data_info)传入的数据信息
* 功能描述:   请求841700功能号
* 返回值：    int, 正确返回0, 失败可以返回其他错误码
================================================================*/
int F841700ExA(KBDCHandle handle, char physical_no[9], char stuemp_no[22], int card_id,
			   CutInfo *cut_info, CardInfo *card_info, DataInfoEx *data_info);

#endif
