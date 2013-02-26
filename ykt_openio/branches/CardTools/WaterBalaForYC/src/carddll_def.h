#ifndef _CARDDLL_DEF_H_
#define _CARDDLL_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif 
#pragma pack(1)

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
	BYTE work_mode;						// 工作模式
	int water_packet_limit;				// 水控钱包限额
	int transfer_limit;					// 水控转账限额
	BYTE data_length[3];				// 数据长度
	BYTE check_crc[2];					// 效验字节
	FEE_RIGHT_NO fee_right_num[256];	// 设置费率的个数
}FEE_RATE_CARD_INFO;

typedef struct  
{
	char   devphy999_id[9];
	double sum_balance;
}COLLECT_BALANCE;

/*******************************************************/
// 电量设置卡结构说明
/*******************************************************/
typedef struct  
{
	int card_id;					// 交易卡号
	int sum_elec_volume;			// 总电量
	int local_elec_volume;			// 本次电量
	int limit_elec_power;			// 电表限容功率
	int alarm_elec_volume;			// 报警显示电量
	int brake_elec_volume;			// 拉闸电量
}ELEC_VOLUME_CARD_INFO;

/*******************************************************/
// 校园卡结构说明
/*******************************************************/
typedef struct _CardInfo 
{
	int 	 card_id;			//交易卡号
	int 	 customer_id;		//客户号
	char     physical_no[9];	//物理卡号
	char     state_id[5];		//卡状态
	char     password[33];		//卡密码
} CardInfo;

/*******************************************************/
// 客户信息结构说明
/*******************************************************/
typedef struct _CutInfo 
{
	int 	 customer_id;				//客户号
	char 	 cut_name[21];				//客户名称
	char     classdept_no[11];			//部门编号
	char     class_no[11];				//班级
	char     classdept_name[151];		//联系人部门或者班级名称
} CutInfo;

/*******************************************************/
// 获取卡以及客户必要信息数据
/*******************************************************/
typedef struct _DataInfo              
{
	int      cut_id;                //客户ID号      
	char	 cut_name[21];			//客户名称
	char     class_no[11];			//班级
	char     classdept_no[11];		//部门编号
	char 	 classdept_name[151];	//联系人部门或者班级名称
	char     password[33];			//卡密码, 暂时作为保留字段
	char     state_id[5];			//卡状态, 保留字段
} DataInfo;

/*******************************************************/
// 获取卡以及客户必要信息数据(扩展)
/*******************************************************/
typedef struct _DataInfoEx              
{
	int      cut_id;                //客户ID号
	int		 card_id;				//交易卡号
	int		 cut_type;				//客户类别代码
	char     cut_type_name[21];		//客户类别名称
	char	 cut_name[21];			//客户名称
	char     sex[2];				//性别
	char     class_no[11];			//班级
	char     classdept_no[11];		//部门编号
	char 	 classdept_name[151];	//联系人部门或者班级名称
	char     password[33];			//卡密码, 暂时作为保留字段
	char     state_id[5];			//卡状态, 保留字段
	char     stuemp_no[21];			//学工号
	char     physical_no[9];		//物理卡号
} DataInfoEx;

#pragma pack()

//////////////////////////////////////////////////////////////////////////
// IMPLEMENT MACRO
#define CHARGE_TERMINAL			0x01			// 收费终端
#define MANAGE_CENTER			(0x01 << 1)		// 管理中心
#define SAVING_POS				(0x01 << 2)		// 充值终端
#define DOOR_DEVICE				(0x01 << 3)		// 门禁
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// 认证终端
#define AREA_CONTROL			(0x01 << 5)		// 区域控制
#define REMAIN_BIT_SEVEN		0				// 保留
#define REMAIN_BIT_EIGHT		0				// 保留

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
#define KS_ERR_NOMANAGEAUTHCARDFLAG		1019
#define KS_ERR_INPUTNULLFAILED			1020			
#define KS_ERR_INPUTZEROFAILED			1021			
#define KS_ERR_REFINECARDSECTOR			1022
#define KS_ERR_WRITECARDMONEY			1023
#define KS_ERR_WRTIECARDRIGHTTYPE		1024
#define KS_ERR_WRTIEDEADLINEDATE		1025
#define KS_ERR_WRTIEDPUBSECT			1026
#define	KS_ERR_WRTIEPUBSECTOR			1027

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
#define LOAD_DLLFUNC(handle,name) do { \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return err_exce.SearchErr(KS_ERR_LOADFUNC_ADDRESS); }while(0)
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
	{KS_ERR_INPUTWORKKEYLENGTH, "授权密钥长度出错"},
	{KS_ERR_INITAUTHCARD, "初始化授权卡失败"},
	{KS_ERR_RESETAUTHCARD, "回收授权卡失败"},
	{KS_ERR_INPUTSHOWIDLENGTH, "输入显示卡号长度出错"},
	{KS_ERR_REFINECARDSECTOR, "回收卡扇区失败"},
	{KS_ERR_WRITECARDMONEY, "写卡余额失败"},
	{KS_ERR_WRTIECARDRIGHTTYPE, "写卡权限类别失败"},
	{KS_ERR_WRTIEDEADLINEDATE, "写卡截止日期失败"},
	{KS_ERR_WRTIEDPUBSECT, "写公共扇区失败"},
	{KS_ERR_WRTIEPUBSECTOR, "公共扇区已经写过"},
	{KS_ERR_INPUTZEROFAILED, "输入数据为空"},
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
DCLR_DLLFUNC(int,SMT_GetPacketInfo,(int nPacketNo, MONEY_PACK_INFO *pPackInfo));
DCLR_DLLFUNC(int,ReadCardMainKey,(BYTE * main_key, short wantFlag, short * readFlag));
DCLR_DLLFUNC(int,RefineCardSector,(int sector, unsigned char login_key[7]));
DCLR_DLLFUNC(int,SMT_PacketSetMoney2,(int nPacketNo, int nMoney, int nCnt));
DCLR_DLLFUNC(int,SMT_PacketReset,(int nPacketNo));
DCLR_DLLFUNC(int,SMT_ChangeCardRightType,(unsigned char ucCardRightType[1]));
DCLR_DLLFUNC(int,SMT_ChangeDeadLineDate,(unsigned char ucDeadLineDate[3]));
DCLR_DLLFUNC(int,ReadCardPwd,(unsigned char pwd[6]));
DCLR_DLLFUNC(int,ReadCardMainKey2,(short flag));
DCLR_DLLFUNC(int,SMT_SetTxCnt,(int nPacketNo,int tx_cnt));
DCLR_DLLFUNC(int,WriteCardPwd,(unsigned char pwd[6]));
DCLR_DLLFUNC(int,SMT_SetNormalFlagByBlkVerion,(unsigned char pwd[12]));
DCLR_DLLFUNC(int,SMT_ClearCard,(void));
DCLR_DLLFUNC(int,SMT_ReadStuempNo,(unsigned char stuemp_no[21]));
DCLR_DLLFUNC(int,RequestCard,(char *ucSerialNo,char *ucType));
DCLR_DLLFUNC(int,ReadBalance,(int nPacketNo,int nBalance[1],int nCnt[1]));


#endif 

#ifdef __cplusplus
}
#endif

#endif