// Pubdef.h
#pragma once

//enum ESAM_SLOT{ SAM1 = 1,						// SAM卡槽编号
//                SAM2 = 2
//};

// 区分硬件版本使用
#define HD_DAMIN        0 // 大明读写器，带LCD显示屏
#define HD_SUOTIAN    1 // 索天读写器


typedef struct _Purchase_Search {
	DWORD		dwPhysicalID;					// 票卡物理卡号
	BYTE		ucLogicalID[8];					// 票卡逻辑卡号
	BYTE		ucCardType;						// 票卡类型
	WORD		wDeposite;						// 票卡押金
	BYTE		ucEndDate[2];					// 票卡有效期
	BYTE		ucPSCert_Type[2];				// 个人证件类型
	BYTE		ucPSCert_EndDate[2];			// 个人证件有效期
	WORD		wTs_SN;							// 票卡交易计数
	WORD		wMaxBalance;					// 票卡最高限额，单位：元
	DWORD		dwBalance;						// 票卡余额，单位：分
	BYTE		ucTs_Flag;						// 票卡交易状态
}PURCHSEARCH, *PPURCHSEARCH;

/* 充值数据结构 */
typedef struct _Purchase_Increase {
	BOOL				bVaild;					// 指示数据是否有效
    DWORD               dwAdminID;				// 管理卡逻辑卡号
    DWORD               dwSysSeq;				// 系统流水号
    WORD				wStatus1;				// 交易状态
    WORD				wStatus2;				// 票卡操作状态
    // 票卡充值前数据
    DWORD				dwPhysicalID;			// 票卡物理卡号
    BYTE		        ucLogicalID[8];			// 票卡逻辑卡号
    BYTE		        ucCardType;				// 票卡类型
    WORD		        wDeposite;				// 票卡押金
    BYTE		        ucEndDate[2];			// 票卡有效期
    BYTE		        ucPSCert_Type[2];		// 个人证件类型
    BYTE		        ucPSCert_EndDate[2];	// 个人证件有效期
    WORD		        wTs_SN;					// 票卡交易计数
    WORD		        wMaxBalance;			// 票卡最高限额，单位：元
    DWORD				dwPreBalance;			// 票卡充值前余额，单位：分
    BYTE		        ucTs_Flag;				// 票卡交易状态
    // 票卡充值后数据
    DWORD           dwSithBalance;				// 充值后票卡余额,单位：分
}PURCHASEINCREASE, *PPURCHASEINCREASE;

typedef struct _Purchase_Prepare {
	DWORD		dwTradeSeq;						// 脱机交易流水号
	BYTE		ucLogicalID[8];					// 票卡逻辑卡号
	DWORD		dwPhysicalID;					// 票卡物理卡号
	DWORD		dwLastDeviceID;					// 上次交易的设备号
	BYTE		ucLastTime[7];					// 上次交易时间
	BYTE		dwDeviceID;						// 本次交易设备号
	BYTE		ucThisTime[7];					// 本次交易时间
	DWORD		dwValue;						// 交易金额
	DWORD		dwBalance;						// 本次交易后的余额
	BYTE		ucTradeType;					// 本次交易类型
	DWORD		dwTradeCount;					// 交易计数
	DWORD		dwEntryDeviceID;				// 本次交易入口设备编号
	BYTE		ucEntryTime[7];					// 本次交易入口日期时间
	BYTE		ucAI;							// 分账信息
	BYTE		ucVC;							// 校验码
	DWORD		dwTAC;							// TAC码
}PURCHPREPARE, *PPURCHPREPARE;


typedef struct _Ticket_Lock {
	BYTE		ucTime[7];						// 交易处理时间
	BYTE		ucLogicalID[8];					// 票卡逻辑卡号
	BYTE		ucPhysicalID[4];				// 票卡物理卡号
	BYTE		ucListType;						// 黑名单类型
}TICKETLOCK, *PTICKETLOCK;
