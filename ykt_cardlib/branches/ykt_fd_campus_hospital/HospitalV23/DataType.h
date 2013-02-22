#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_
#pragma once

#pragma pack(1)
typedef struct _hCustomerInfo 
{
	char szName[20 + 1];					// 联系人姓名
	char szStuempNo[20 + 1];			    // 学工号
	char szSex[1 + 1];					    // 性别
	char szManId[20 + 1];					// 身份证号
	char szClassDeptName[150 + 1];		    // 部门名称
	char szTel[20 + 1];						// 联系电话
	int  nMendFeeType;						// 医疗收费类型(1为公费, 2为自费)
	int  nCustomerId;						// 客户号
}CustomerInfo;

typedef struct _hTradeSerial 
{
	int	   nSerialNo;						// 流水号
	int	   nOtherSerialNo;					// 上传端流水号
	int    nSerialType;						// 流水类型
	int    nSerialState;					// 流水状态
	char   szOperateDate[10 + 1];			// 发生日期
	char   szOperateTime[8 + 1];			// 发生时间
	char   szCollectDate[10 + 1];			// 采集日期
	char   szCollectTime[8 + 1];			// 采集时间
	char   szEnteractDate[10 + 1];			// 入账日期
	char   szEnteractTime[8 + 1];			// 入账时间
	int    nMainDeviceId;					// 上传工作站标识
	int    nDeviceId;						// 交易发生设备标识
	char   szDevphy999Id[8 + 1];			// 三九设备物理ID
	char   szShowId[10 + 1];				// 显示卡号
	int    nCardId;							// 交易卡号
	int    nPurseId;						// 钱包号
	int	   nTradeCount;						// 交易次数
	double dTradeFee;						// 交易金额
	double dInBalance;						// 入卡值
	double dOutBalance;						// 出卡值
	double dDepositFee;						// 押金金额
	double dInFee;							// 手续费
	double dCostFee;						// 卡成本费
	double dBoardFee;						// 搭伙费
	int    nCoustomerId;					// 客户ID号
	char   szOperCode[10 + 1];				// 操作员号
	char   szOutAccountId[16 + 1];			// 出帐帐号
	char   szInAccountId[16 + 1];			// 入账帐号
	int    nSysId;							// 外部系统标识
	int    nTmark;							// 交易标记
	int    nErrCode;						// 返回码
	int    nReviseSerialNo;					// 冲正流水号
}TradeSerial;
#pragma pack()

#endif