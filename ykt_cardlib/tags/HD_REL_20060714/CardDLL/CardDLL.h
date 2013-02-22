//使用预编译指令保证头文件只能被包含一次
#ifndef __CardDLL_H__
#define __CardDLL_H__

//用预编译指令使C函数能被C++程序直接调用
#ifdef __cplusplus
extern "C" {
#endif


//发行卡结构定义
#pragma pack(1)

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

#pragma pack()

//十进制字符串转换为BCD字符串
int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);
//BCD字符串转换为十进制字符串
int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr);
//打开串口
int __stdcall ConnectMF(int,int);

//关闭串口
int __stdcall CloseMF(void);

//读写器授权
int __stdcall ReaderAuthor(unsigned char *);

//读卡物理序列号
int __stdcall RequestCard(char *,char *);

//发行卡
int __stdcall PublishCard(TPublishCard *pc);

//读卡信息
int __stdcall RedCardInfo(TPublishCard *pc);

//读用户卡钱包信息
int __stdcall ReadPacketInfo(LOOPPURSEINFO *LoopPurseInfo);

//更新卡信息
int __stdcall UpdateCardInfo(TPublishCard *CardInfo);

//读交易卡号
int __stdcall ReadCardNO(char *pCardNo);

int __stdcall WriteCardPwd(unsigned char pwd[6]);
int __stdcall ReadCardPwd(unsigned char pwd[6]);
int __stdcall Load_Dll();
int __stdcall GetLastErrMsg(int ecode[1],char *errmsg);
#ifdef __cplusplus
}
#endif

#endif
