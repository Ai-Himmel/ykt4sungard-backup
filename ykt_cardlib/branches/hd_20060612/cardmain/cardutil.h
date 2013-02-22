#ifndef CARDUTIL_H
#define CARDUTIL_H

#define SELECTSMARTCARDTYPE 0x18

// 
#ifdef __cplusplus
extern "C" {
#endif

	//发行卡结构定义
#pragma pack(1)

#define WATER_AUTH_CARD 1
#define WATER_COMMON_CARD 2
#define WATER_CLEAR_CARD 3
#define WATER_NEW_CARD 4
#define WATER_FIXED_CARD 5
	
	typedef struct               
	{
		unsigned char ShowCardNo[11];			//用户卡显示卡号
		unsigned char CardNo[8];				//用户卡交易卡号
		unsigned char DeadLineDate[9];			//用户卡使用截止日期
		int CardRightType;						//用户卡使用权限类型（1--254）
		unsigned char ucName[9];				//姓名
		unsigned char ucDutyNo[9];				//职务代码
		unsigned char ucCertificateNo[21];		//证件号码
		unsigned char ucDepartmentNo[11];		//部门编号
		unsigned char ucIdentifyNo[5];			//身份代码
		unsigned char ucSexNo[2];				//性别代码
		unsigned char ucCardNo[21];				//卡号（工号或学号）
		unsigned char ucPwd[6];					//卡密码
		unsigned char ucLibraryNo[21];			//图书证号
		int Money;								//金额（分）
		unsigned char isFormat;					//是否格式化第一扇区
	}TPublishCard;
	
	typedef struct
	{
		DWORD RemainMoney;			// 电子钱包余额
		WORD DealTimes;				// 用户卡交易流水号
		BYTE DealYear;				// 交易日期
		BYTE DealMonth; 
		BYTE DealDay;
		BYTE DealHour;
		BYTE DealMin;
		BYTE DealTimes_CurTime;		// 累计交易次数(当前时间段内)
		BYTE DealTimes_CurDay;		// 累计交易次数(当日内)
	} LOOPPURSEINFO ,*LPLOOPPURSEINFO;
	
	typedef struct
	{
		char cardtype;
		int termid;
		int remain;
		BYTE oldSerialNo[4];
	}WATER_PACK_INFO;
#pragma pack()

#define CARDUTIL_API __declspec(dllimport) 

#ifdef __cplusplus
}
#endif

#endif