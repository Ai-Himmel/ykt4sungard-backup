#ifndef _CARDDLL_DEF_H_
#define _CARDDLL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif 


#ifndef WIN32
#ifndef DWORD
#define DWORD int
#endif

#ifndef WORD
#define WORD short
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef BOOL
#define BOOL int
#define TRUE 1
#define FALSE 0
#endif
	
#ifndef ULONG
#define ULONG unsigned long
#endif
#else
#include <windows.h>
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
	unsigned char area_code[3];				//院校代码
	int cut_id;								//客户ID号
	BYTE certificate_type[3];				//证件类型
	BYTE people[3];							//民族
	BYTE nationality[4];					//国籍
	BYTE open_card_flag[2];					//是否已经开卡,0未开卡,1已开卡
	BYTE card_version[2];					//制卡版本号
	unsigned char pub_card_flag[11];		//发卡注册标识号
	unsigned char ser_flag[11];				//服务注册标识号
	BYTE pwd_open_flag[2];					//启用密码开关0启用,1未启用
}TPublishCard;

typedef struct               
{
	unsigned int phyno;						// 物理卡号
	unsigned char CardNo[8];					//用户卡交易卡号
	unsigned char DeadLineDate[9];			//用户卡使用截止日期
	int CardRightType;						//用户卡使用权限类型（1--254）
	unsigned char ucName[9];				//姓名
	unsigned char ucCertificateNo[21];		//证件号码
	unsigned char ucDepartmentNo[11];		//部门编号
	unsigned char ucIdentifyNo[5];			//身份代码
	unsigned char ucSexNo[2];				//性别代码
	unsigned char ucCardNo[21];				//卡号（工号或学号）
	unsigned char ucPwd[6];					//卡密码
	int Money;								//金额（分）
	int cut_id;								//客户ID号
}TPublishCard2;

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
	int bala;
	int daybala;
	int total_cnt;
	int day_cnt;
	int time_cnt;
	int date;	//yyyymmdd
	int time;	//hhmmss
}MONEY_PACK_INFO;

typedef struct
{
	char cardtype;
	int termid;
	int remain;
	BYTE oldSerialNo[4];
}WATER_PACK_INFO;

/******************************************************/
// 费率结构
/******************************************************/
typedef struct  
{
	BYTE time_ladder[1];				// 时间阶梯
	BYTE deduct_time[1];				// 扣费的单位时间，以秒为单位
	BYTE deduct_fee[1];					// 扣费的单位金额，以分为单位
}FEE_RATE;

/******************************************************/
// 当前权限的费率个数
/******************************************************/
typedef struct
{
	short right_flag;					// 权限标志, 1打开, 0关闭
	short right_num;					// 传入当前权限下的费率个数
	FEE_RATE fee_rate[5];				// 最大设置为5个, 其实有一些没有用到
}FEE_RIGHT_NO;

/*******************************************************/
// 费率卡结构说明
/*******************************************************/
typedef struct  
{
	BYTE water_card_flag[5];			// 水控卡标志
	char packet_num;					// 水控钱包号
	BYTE main_work_key[9];				// 主工作密钥(明文)
	BYTE packet_work_key[9];			// 小钱包工作密钥(明文)
	BYTE data_length[3];				// 数据长度
	BYTE check_crc[2];					// 效验字节
	FEE_RIGHT_NO fee_right_num[256];	// 设置费率的个数
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

#define WATER_AUTH_CARD 1
#define WATER_COMMON_CARD 2
#define WATER_CLEAR_CARD 3
#define WATER_NEW_CARD 4
#define WATER_FIXED_CARD 5
#define WATER_CLEAR_CARD2 6

#define CHARGE_TERMINAL			0x01			// 收费终端
#define MANAGE_CENTER			(0x01 << 1)		// 管理中心
#define SAVING_POS				(0x01 << 2)		// 充值终端
#define DOOR_DEVICE				(0x01 << 3)		// 门禁
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// 认证终端
#define AREA_CONTROL			(0x01 << 5)		// 区域控制
#define REMAIN_BIT_SEVEN		0				// 保留
#define REMAIN_BIT_EIGHT		0				// 保留

// 广州大学城水控钱包定义
typedef struct
{
	double price1;
	double price2;
	double price3;
	double balance;
}WATER_PACK_INFO2;

typedef struct
{
	int price1;
	int price2;
	int price3;
	int balance;
}WATER_PACK_INFO3;

// 来自于COMM.H的数据结构
// #define	STX1	0xC0
// #define	ETX1	0xC1
// #define	STX2	0xC2
// #define	ETX2	0xC3
// //----------------------------
// int ErrorCode;
// BYTE Dll_RetData[500];
// int Dll_CommByte;
// int Dll_bps = 19200;
// BYTE Dll_MacNo;
// COMMTIMEOUTS CommTimeOuts;
// unsigned char subkey[17][49];

// 来自于COMM.H的数据结构

#pragma pack()


//////////////////////////////////////////////////////////////////////////
// IMPLEMENT MACRO
#define KS_ERR_EXIT						-1
#define KS_ERR_LOADLIBRARY				1001			
#define KS_ERR_LOADFUNC_ADDRESS			1002			
#define KS_ERR_GETVERSION				1003			
#define KS_ERR_NOINITFILE				1004
#define KS_ERR_NOLOCALEXE				1005
#define KS_ERR_PORTNOEXIST				1006
#define KS_ERR_OPENCOM					1007
#define KS_ERR_NOTOPENCOM				1008
#define KS_ERR_CLOSECOM					1009
#define KS_ERR_READAUTHCARD				1010
#define KS_ERR_CHANGECARDID				1011
#define KS_ERR_CHANGESHOWCARDID			1012
#define KS_ERR_READCARDINFO				1013
#define KS_ERR_CHANGESEPNO				1014
#define KS_ERR_INPUTWORKKEYLENGTH	    1015
#define KS_ERR_INITAUTHCARD				1016
#define KS_ERR_RESETAUTHCARD			1017
#define KS_ERR_INPUTSHOWIDLENGTH		1018

// 收费终端
#define KS_ACR_CONSUME_TERM		0x01
// 管理中心
#define KS_ACR_MANAGE_CENTER 	0x01<<1
// 充值终端
#define KS_ACR_ADD_MONEY_TERM   0x01<<2
// 门禁设备
#define KS_ACR_GATE				0x01<<3
// 认证终端
#define KS_ACR_AUTH_TERM		0x01<<4
// 区域控制
#define KS_ACR_AREA_RESTRICT    0x01<<5	

#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#ifdef NOUSE_MFC
#define LOAD_DLLFUNC(handle,name) do { \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return -1; } while(0)
#else
#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return err_exce.SearchErr(KS_ERR_LOADFUNC_ADDRESS);
#endif
	
//////////////////////////////////////////////////////////////////////////
// ERROR INFOMATION
static struct Err_Def 
{
	int err_code;
	char err_info[32];
}g_Err_Def[] = 
{
	{KS_ERR_LOADLIBRARY, "读取动态库错误"},
	{KS_ERR_LOADFUNC_ADDRESS, "读取函数地址错误"},
	{KS_ERR_GETVERSION, "读取动态库版本错误"},
	{KS_ERR_NOINITFILE, "没有ini配置文件"},
	{KS_ERR_NOLOCALEXE, "没有本地exe程序"},
	{KS_ERR_PORTNOEXIST, "端口不存在"},
	{KS_ERR_OPENCOM, "打开串口错误"},
	{KS_ERR_NOTOPENCOM, "没有打开串口"},
	{KS_ERR_CLOSECOM, "关闭串口错误"},
	{KS_ERR_READAUTHCARD, "读取授权卡错误"},
	{KS_ERR_CHANGECARDID, "修改交易卡号错误"},
	{KS_ERR_CHANGESHOWCARDID, "修改显示卡号错误"},
	{KS_ERR_READCARDINFO, "读取卡信息错误"},
	{KS_ERR_CHANGESEPNO, "修改学工号错误"},
	{KS_ERR_INPUTWORKKEYLENGTH, "输入授权工作密钥长度出错"},
	{KS_ERR_INITAUTHCARD, "初始化授权卡失败"},
	{KS_ERR_RESETAUTHCARD, "回收授权卡失败"},
	{KS_ERR_INPUTSHOWIDLENGTH, "输入显示卡号长度出错"},
	{KS_ERR_EXIT, "无此类错误信息"}
};

//////////////////////////////////////////////////////////////////////////
// IMPORT FUNCTION
#ifndef CARDDLL_EXPORTS
DCLR_DLLFUNC(int,ConnectMF,(int nPortNo, int nBaudRate));
DCLR_DLLFUNC(int,CloseMF,());
DCLR_DLLFUNC(int,SMT_ChangeShowCardNo,(unsigned char ucShowCardNo[5]));
DCLR_DLLFUNC(int,SMT_ChangeDealCardNo,(int nDealCardNo));
DCLR_DLLFUNC(int,SMT_ReadCardStateInfo,(unsigned char ucShowCardNo[5],
										int nDealCardNo[1],
										unsigned char ucDeadLineDate[3],
										unsigned char ucCardRightType[1]));
DCLR_DLLFUNC(int,ReadCardMainKey,(BYTE * main_key, short wantFlag, short * readFlag));
DCLR_DLLFUNC(int,SMT_AutoDll,(unsigned char *ucWorkingKey));
DCLR_DLLFUNC(int,ControlBuzzer,(void));
DCLR_DLLFUNC(int,ReadCardInfo,(TPublishCard *pc));
DCLR_DLLFUNC(int,SMT_ChangeCardNo,(unsigned char ucCardNo[20]));
DCLR_DLLFUNC(int,ProcessCallBack,(int step));
DCLR_DLLFUNC(int,InitNewAuthCard,(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack));
DCLR_DLLFUNC(int,ResetNewAuthCard,(int * err_code, LPProcessCallBack lpCallBack));
DCLR_DLLFUNC(int,SMT_ReadAuthorWorkKeyAndFlag,(BYTE auth_work_key[8], BYTE *flag));
DCLR_DLLFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_DLLFUNC(int,ReadSerial,(unsigned char *serial));
DCLR_DLLFUNC(int,ReadPacketInfo,( LPLOOPPURSEINFO LoopPurseInfo ));
DCLR_DLLFUNC(int,SMT_ReadPacketInfo,(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo)); 
DCLR_DLLFUNC(int,ReadCardNO,(int CardNo[1]));
DCLR_DLLFUNC(int,SMT_PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_DLLFUNC(int,SMT_PacketSetMoney2,(int nPacketNo, int nMoney, int nCnt));
DCLR_DLLFUNC(int,SMT_GetPacketInfo,(int nPacketNo, MONEY_PACK_INFO *pPackInfo));
DCLR_DLLFUNC(int,Load_Dll,());
DCLR_DLLFUNC(int,ReadCardPwd,(unsigned char pwd[6]));
DCLR_DLLFUNC(int,HaltCard,(void));
DCLR_DLLFUNC(int,ReadCardInfo2,(TPublishCard2 *pc));
DCLR_DLLFUNC(int,SetCardMainKey,(BYTE main_key[8]));
DCLR_DLLFUNC(int,YKT_encrypt_cardpwd,(int cut_id,const char seedkey[32],const char pwd[8],char mpwd[32]));
DCLR_DLLFUNC(int,YKT_decrypt_cardpwd,(int cut_id,const char seedkey[32],const char mpwd[64],char pwd[8]));


DCLR_DLLFUNC(int,SMT_ReadWaterPackInfo2,(WATER_PACK_INFO3* info));
DCLR_DLLFUNC(int,SMT_WriteWaterPackInfo2,(WATER_PACK_INFO3* info));
DCLR_DLLFUNC(int,SMT_TransWaterPacket,(int main_money,WATER_PACK_INFO3* info));
DCLR_DLLFUNC(int,XT2JD_Card,());
DCLR_DLLFUNC(int,JD2XT_Card,());
DCLR_DLLFUNC(int,SMT_TransWaterPacket_XT,(int main_money,WATER_PACK_INFO3* info));
DCLR_DLLFUNC(int,SMT_ReadWaterPackInfo_XT,(WATER_PACK_INFO3* info));
DCLR_DLLFUNC(int,SMT_WriteWaterPackInfo_XT,(WATER_PACK_INFO3* info));


#endif 

#ifdef __cplusplus
}
#endif

#endif