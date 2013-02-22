// Pubdef.h
#pragma once

//enum ESAM_SLOT{ SAM1 = 1,						// SAM卡槽编号
//                SAM2 = 2
//};

// 区分硬件版本使用
#define HD_DAMIN        0 // 大明读写器，带LCD显示屏
#define HD_SUOTIAN    1 // 索天读写器

// 功能选择
#define ONLY_ALL        0 // 充值消费都有
#define ONLY_PSAM       1 // 只有消费
#define ONLY_PKI        2   // 只有充值

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
	DWORD		dwTradeSeq;					// 脱机交易流水号
	BYTE		ucLogicalID[8];					// 票卡逻辑卡号
	DWORD		dwPhysicalID;					// 票卡物理卡号
	DWORD		dwLastDeviceID;					// 上次交易的设备号
	BYTE		ucLastTime[7];					// 上次交易时间
	DWORD		dwDeviceID;						// 本次交易设备号
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

// 月票充值数据结构
typedef struct _CommTicket_Increase {
	BYTE	CommTicketType;						// 月票类型
	BYTE	SetMealType;						// 套餐类型
	BYTE	SetMealLevel;						// 套餐档次
	BYTE	StartDate[4];						// 起始日期
	BYTE	Counts[4];							// 计数
	BYTE	Line1[6];							// 线路号1
	BYTE	Line2[6];							// 线路号2
	BYTE	Line3[6];							// 线路号3
}CommTicket_Increase_t, *pCommTicket_Increase_t;

typedef struct _CommTicket_Info{
	BYTE	LogicId[8];							// 票卡逻辑卡号
	BYTE	PhyId[4];							// 物理卡号
	BYTE	Type;								// 票卡类型
	BYTE	StartDate[4];						// 起始日期
	DWORD	dwValue;							// 价格
	BYTE	SysCounts[5];						// 系统流水号
	BYTE	ServerTime[7];						// 服务器时间
	BYTE	Line1Name[20];						// 线路1名称
	BYTE	Line2Name[20];						// 线路2名称
	BYTE	Line3Name[20];						// 线路3名称
	BYTE	IncCounts[4];						// 充值次数
}CommTicket_Info_t, *pCommTicket_Info_t;

typedef struct _CommTicket_Charge_Info{
	BYTE	SysCounts[5];						// 系统流水号
	BYTE	ChargeTime[7];						// 交易时间
	BYTE	AuthCode[4];						// 授权码
	BYTE	Flag;								// 冲正标志
}CommTicket_Charge_Info, *pCommTicket_Charge_Info;

typedef struct _MT_Info_Block4
{
	BYTE	CityCode[2];	// 城市代码2
	BYTE	TradeCode[2];	// 行业代码2
	BYTE	CardType;		// 卡类型1
	BYTE	Marker_Ver;		// 钱包标识+版本1
	BYTE	LogicId[4];		// 逻辑卡号序列号 4
	BYTE	AuthCode[4];	// 卡号认证码 4
	BYTE	LifeTime[2];	// 有效期 2	
}MT_Info_Block4_t;

typedef struct _MT_Info_Block21
{
	BYTE	CIDName[2];					// 证件名称代码2
	BYTE	CIDUsefulLife[2];			// 证件有效期2 bcd
	BYTE	CIDCode[2];					// 个人化设备代码2 hex
	BYTE	CIDNum[10];					// 有效证件号码	10 BCD
}MT_Info_Block21_t;

// 脱机月票信息
typedef struct _MT_CommTicket_Info
{
	BYTE	Cycle1_StartDate[3];	// 周期1充值生效期	3	BCD（YYMMDD）
	BYTE	Cycle1_EndDate[3];		// 周期1充值截止期	3	BCD（YYMMDD）
	BYTE	Cycle1_Flag;			// 周期1通票标志	1	HEX
	
	BYTE	Cycle2_StartDate[3];	// 周期2充值生效期	3	BCD（YYMMDD）
	BYTE	Cycle2_EndDate[3];		// 周期2充值截止期	3	BCD（YYMMDD）
	BYTE	Cycle2_Flag;			// 周期2通票标志	1	HEX
	
	BYTE	RFU[2];					// 备用	2	HEX
	
	BYTE	Cycle1_ChargeTime[2];	// 周期1充值次数	2	HEX
	BYTE	Cycle1_ChargeCode[2];	// 周期1充值机代码	2	BCD
	BYTE	Cycle1_ChargeDate[3];	// 周期1充值时间	3	BCD（YYMMDD）
	BYTE	Cycle1_LineCode[9];		// 周期1线路编码（三条）	9	BCD
	
	BYTE	Cycle2_ChargeTime[2];	// 周期2充值次数	2	HEX
	BYTE	Cycle2_ChargeCode[2];	// 周期2充值机代码	2	BCD
	BYTE	Cycle2_ChargeDate[3];	// 周期2充值时间	3	BCD（YYMMDD）
	BYTE	Cycle2_LineCode[9];		// 周期2线路编码（三条）	9	BCD
}MT_CommTicket_Info_t;

typedef struct _CommTicket_ReadInfo_Offline{
	DWORD					dwPhysicalID;	// 票卡物理卡号
	MT_Info_Block4_t		Block4;			// 卡内块4信息
	MT_Info_Block21_t		Block21;		// 卡内块21信息
	MT_CommTicket_Info_t	CommTickInfo;	// 月票信息 
	DWORD					dwBalance;		// 月票乘次余额，单位：次
	BYTE					Mac[4];			// MAC(重要数据的校验码)4
}CommTicket_ReadInfo_Offline_t, *pCommTicket_ReadInfo_Offline_t;

typedef struct _CommTicket_SignIn_Info{
	BYTE	SHID[8];			// 握手流水号
	BYTE	SK[32];				// 会话密钥（取前16个字节），3DES密钥
	BYTE	SERVER_TIME[6];		// 服务器时间
}CommTicket_SignIn_Info_t, *pCommTicket_SignIn_Info_t;

typedef struct _CommTicket_Online_Info{
	BYTE	AdminLogicId[4];		// 管理卡逻辑卡号 BCD
	BYTE	SysCounts[5];			// 系统流水号 BCD
	BYTE	Retval;					// 返回码 HEX
	WORD	wInfolen;				// 月票信息长度 HEX 高位在前
	BYTE	Info[512];				// 月票信息(长度可变)
}CommTicket_Online_Info_t, *pCommTicket_Online_Info_t;

// 易票联扣费接口
typedef struct _CommTicket_Deduction_Struct{
	DWORD	dwAdminID;							// PKI管理员卡号
	BYTE	LogicId[8];							// 票卡逻辑卡号
	BYTE	PhyId[4];							// 物理卡号
	BYTE	Type;								// 票卡类型
	DWORD	dwValue;							// 价格
	BYTE	SysCounts[5];						// 系统流水号
	BYTE	ChargeTime[7];						// 交易时间
	BYTE	IncCounts[4];						// 充值次数
}CommTicket_Deduction_Struct_t, *pCommTicket_Deduction_Struct_t;
