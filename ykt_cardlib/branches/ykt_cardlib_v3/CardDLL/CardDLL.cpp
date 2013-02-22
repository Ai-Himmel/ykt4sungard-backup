/*=================================================================================================
* 模块名:	    一卡通操作卡功能动态库
* 文件名:		CardDLL.cpp 
* 相关文件:     CardDLL.h
* 文件实现功能: 对卡功能操作 
* 作者:		    李翔 
* 版本:			主干版本 
* -------------------------------------------------------------------------------------------------
* 备注:          
* -------------------------------------------------------------------------------------------------
* 修改记录: 
* 日期			 版本			修改人			修改内容		 					
* 2006-9-25		 ---		    李翔            将业务模块和基础模块分开
* 修改记录: 
* 日期			 版本			修改人			修改内容		 					
* 2007-7-12		 1.1.000		李翔            添加广州大学城专有卡片扇区
*
* 日期			 版本			修改人			修改内容		 					
* 2007-8-13		 1.1.001		李翔            (1) 添加初始化卡写卡标志到0扇区
*												(2) 修改发行授权卡将0扇区卡标志写掉
*													的问题
*												(3) 修改设置授权卡黑名单版本写错内容
*													的问题
*											    (4) 修改登录授权卡密钥扇区函数, 当参数
*													赋空导致程序down掉的问题
*
* 2007-8-14		 1.1.002		李翔            修改内容
*												(1) 修改打开串口函数引起加载动态库
*													逻辑出错的问题
*                                               (2) 添加日志类, 便于遇到错误调试
*												(3) 修改读取授权卡函数的堆数组错误
*
* 2007-8-18		 1.1.003		李翔            修改内容
*												(1) 增加初始化洗衣机设置卡(InitWashCard)函数
*												(2) 增加发行洗衣机设置卡(PublishNewWashCard)函数
*												(3) FEE_RATE_CARD_INFO结构增加工作地点字段
*
* 2007-9-3		 1.1.004		李翔            修改内容
*												(1) 修改(CollectionCardReceiveData)函数
*													不能采集每个扇区第三块的问题
*
* 2007-9-27		 1.1.005		李翔            修改内容
*												(1) 修改(PublishFeeRateCard)函数, FEE_RATE_CARD_INFO
*													结构新增转账金额限制和水控钱包金额限制
*												(2) 新增汇多水控转账卡读取函数ReadWaterFeeCardInfo		
*
* 2007-10-15	 1.1.006		李翔            修改内容
*												(1) 增加国光圈存机读卡功能库KS_GG	
*
* 2007-10-31	 1.1.007		李翔            修改内容
*												(1) 新增GW_KBC后台交易功能库(网络通讯用)	
*												(2) 新增函数名以YKTSVR开头的通讯函数和交易函数
*
* 2008-01-28	 1.1.008		李翔            修改内容
*												(1) 新增写补助信息功能	
*												(2) 新增读取补助信息功能
*
* 2008-03-11	 1.1.008		李翔            修改内容
*												(1) 新增读取校区代码(SMT_ReadAreaCode)函数功能	
*												(2) 新增写校区代码(SMT_WriteAreaCode)函数功能
*												(3) 在Load_Dll函数中修改加载GW_KBC库的方式, 可以在
*													配置文件里面进行配置
* =================================================================================================
*/
#include "Stdafx.h"
#include "CardDLL.h"

extern CLogFile g_log_file;

int InitInstance();
int ifReadyOK();
//int isConnectMF = -1;    //判断读写器是否成功初始化
static int	ErrCode;
static char ErrMsg[1024];
static int pos_hwnd = 0;

// 来自于SMARTCOM411DXQ.dll
unsigned char SMT_UCWORKINGKEY[256]="";
int nAutoFlag = 0;
char msg[128] = "";
static unsigned char LOGIN_AREA_KEY[7] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06};

//////////////////////////////////////////////////////////////////////////
// 初始化卡
// 初始化扇区数
//#define SMARD_CARD_SECT_NO 32
static int smart_card_sect_no = 32;
// 授权卡扇区数
#define AUTH_CARD_SECT_NO 32
// 密钥长度
#define CARD_KEY_LEN 6
// 初始化卡时写入的控制位
static BYTE CARD_NEW_CTRL_BIT[] = {0x7F,0x07,0x88,0x00};
// 出厂时的控制位
static BYTE CARD_INIT_CTRL_BIT[] = {0xFF,0x07,0x80,0x69};   // KEYA和KEYB具有相同权限, 出厂控制位KEYB操作无效
// 上大14扇区控制位
static BYTE CARD_FOR14_CTRL_BIT[] = {0x78,0x77,0x88,0x00};	// KEYA读KEYB写
// PHILIP卡类型
static BYTE PHILIPS_CARD_TYPE[] = {0x18,0};
// 密钥所在的块号
#define PASSWD_BLOCK_NUM 3
// 授权密钥
static BYTE CARD_MAIN_KEY[9] = "";
// 判断串口是否已经打开
static BOOL com_is_open = FALSE;
// 0代表KEYA, 1代表KEYB
#define CARD_KEY_A 0
#define CARD_KEY_B 1
#define CARD_KEY_C 1

// 判断卡类型
#define BARE_CARD_TYPE 1
#define INIT_CARD_TYPE 2
#define UNRECOGNISE_CARD_TYPE 3

// 初始化的健值
static BYTE CARD_INIT_KEY[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

// 判断是否已读授权卡
static BOOL has_read_main_key = FALSE;
// 授权标志
static short AUTH_CARD_FLAG = -1;
static unsigned char s_water_common_card[2] = {0xF9,0x9E};
static unsigned char s_water_clear_card[2] = {0xF9,0x9C};
static unsigned char s_water_clear_card2[2] = {0xF9,0x9A};
static unsigned char s_water_new_card[2] = {0xF9,0x9D};
static unsigned char s_water_auth_card[2] = {0xF9,0x9F};

// 广州大学城专有卡片扇区内容
#define GZ_UNIVERSITY_TOWN 1

// 上海理工大学水控错误码设置
#define COLLECT_CARD_SECT_NO 32				// 采集卡有效数据区 

// 生成授权卡密钥时的种子
static BYTE AUTH_CARD_SEED[8] = "";

// 一卡通通讯库专有宏
#ifndef YKTSERVER
#define YKTSERVER
#endif
//////////////////////////////////////////////////////////////////////////
char bufSmartCom[1024] = "";
char bufDesdll[1024] = "";
char bufGwKBCdll[1024] = "";
char buf_pos_dll[1024] = "";
int  dll_flag = 0;
char pathBuf[512] = "";
char iniFilePathBuf[512] = "";

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	GetModuleFileName((HMODULE)hModule, iniFilePathBuf, sizeof(iniFilePathBuf));
 	GetIniFileFromDll(iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL1", "", bufSmartCom, sizeof(bufSmartCom), iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLL2", "", bufDesdll, sizeof(bufDesdll), iniFilePathBuf);
    GetPrivateProfileString("LOADLIBRARY", "DLLCOMM", "", bufGwKBCdll, sizeof(bufGwKBCdll), iniFilePathBuf);
	dll_flag = GetPrivateProfileInt("LOADLIBRARY", "DLLFLAG", 0, iniFilePathBuf);
	GetPrivateProfileString("LOADLIBRARY", "DLLPOS2", "", buf_pos_dll, sizeof(buf_pos_dll), iniFilePathBuf);

	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

HINSTANCE hDLL = NULL;
typedef INT (CALLBACK* LPSMT_ConnectMF280)(int, int);
typedef INT (CALLBACK* LPSMT_ControlBuzzer)(void);
typedef INT (CALLBACK* LPSMT_CloseMF280)(void);	
typedef INT (CALLBACK* LPSMT_RequestCardExist)(unsigned char *,unsigned char *);
typedef INT (CALLBACK* LPSMT_SleepCard)();
typedef void (CALLBACK* LPSetLastErrMsg)(int err_code,char* format, ...);
typedef void (CALLBACK* LPGetMFLastErr)();
typedef INT	(CALLBACK* LPMF_ReadSeriesNo)(unsigned char *Buffer);
typedef INT (CALLBACK* LPSMT_ExeCommand)(unsigned char *Buffer,int Len);
typedef INT (CALLBACK* LPSMT_Login_With_UserKey)(int Sector, unsigned char *Buffer, int PaDSelect);
typedef INT (CALLBACK* LPSMT_WriteBlock)(int Sector,int BlockNo,unsigned char *BlockBuf);
typedef INT (CALLBACK* LPSMT_ReadBlock)(int Sector,int BlockNo, unsigned char *BlockBuf);
typedef void (CALLBACK* LPSMT_CopyWorkingKey)(unsigned char *SMT_UCWORKINGKEY);

LPSMT_ConnectMF280				SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer				SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280				SMT_CloseMF280=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;

//钱包操作
LPSMT_SleepCard		 SMT_SleepCard=NULL;

// 登陆卡
LPSMT_Login_With_UserKey SMT_Login_With_UserKey = NULL;

// 读取串行号
LPMF_ReadSeriesNo MF_ReadSeriesNo = NULL;

// 读, 写入数据块
LPSMT_ReadBlock SMT_ReadBlock = NULL; 
LPSMT_WriteBlock SMT_WriteBlock = NULL;

// 设置出错信息
LPSetLastErrMsg SetLastErrMsg = NULL;
LPGetMFLastErr GetMFLastErr = NULL;

// 复制全局字符串
LPSMT_CopyWorkingKey SMT_CopyWorkingKey = NULL;

// 密钥计算函数(来自于Desdll.dll)
HINSTANCE hDesDLL = NULL;
typedef long (CALLBACK * lpgen_user_card_keyA )(unsigned char *key,unsigned char *text,unsigned char *keyA);;
typedef long (CALLBACK * lpgen_user_card_keyB )(unsigned char *key,unsigned char *text,unsigned char *keyA);;
typedef INT (CALLBACK *lpencrypt_work_key)(unsigned char* text,unsigned char* mtext);
typedef long (CALLBACK * lpgen_auth_card_keyA)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK * lpgen_auth_card_keyB)(BYTE seed[8],BYTE key[6]);
typedef long (CALLBACK* lpdecrypt_work_key)(BYTE src_key[8],BYTE des_key[8]);
typedef long (CALLBACK* lpget_check_char)(BYTE buf[16]);
lpgen_user_card_keyA	gen_user_card_keyA = NULL;
lpgen_user_card_keyB	gen_user_card_keyB = NULL;
lpencrypt_work_key      encrypt_work_key = NULL; 
lpgen_auth_card_keyA	gen_auth_card_keyA = NULL;
lpgen_auth_card_keyB	gen_auth_card_keyB = NULL;
lpdecrypt_work_key		decrypt_work_key   = NULL;
lpget_check_char		get_check_char	   = NULL;

// 后台通讯库函数(来自于GW_KBC.dll)
HINSTANCE hGwKbcDLL = NULL;
typedef int (CALLBACK	*LPGW_Login)(void);
typedef int (CALLBACK	*LPGW_CreateNewHandle)(void);
typedef int (CALLBACK	*LPGW_CloseHandle)(void);
typedef int (CALLBACK	*LPGW_Exit)(void);
typedef int (CALLBACK	*LPGW_GetCardInfo)(char physical_no[9], CardInfo *card_info);
typedef int (CALLBACK	*LPGW_GetCustomerInfo)(int cut_id, char stuemp_no[22], CutInfo *cut_info);
typedef void (CALLBACK	*LPGW_GetLastErrorMsg)(char *error_msg);
typedef int (CALLBACK	*LPGW_GetSeedKey)(char *seed_key);
LPGW_Login				GW_Login = NULL;
LPGW_CreateNewHandle	GW_CreateNewHandle = NULL;
LPGW_CloseHandle		GW_CloseHandle = NULL;
LPGW_Exit				GW_Exit = NULL;
LPGW_GetCardInfo		GW_GetCardInfo = NULL;
LPGW_GetCustomerInfo	GW_GetCustomerInfo = NULL;
LPGW_GetLastErrorMsg	GW_GetLastErrorMsg = NULL;
LPGW_GetSeedKey			GW_GetSeedKey = NULL;

// POS机硬件(统一封装)
HINSTANCE h_pos_dll = NULL;
typedef long (CALLBACK	*LPPOS_ConnectMF)(int port, int baud, int hwnd);
typedef long (CALLBACK	*LPPOS_CloseMF)(void);
typedef int (CALLBACK *LPPOS_PacketDelMoney)(int money, int &flow_no);
typedef int (CALLBACK *LPPOS_ReadBalance)(int &money);
typedef int (CALLBACK *LPPOS_MendPacket)(int &bmoney, int &amoney);
typedef int (CALLBACK *LPPOS_ControlBuzzer)(unsigned short beep);
typedef int (CALLBACK *LPPOS_ReadStuempNo)(unsigned char stuemp_no[21]);
typedef int (CALLBACK *LPPOS_ReadSerial)(unsigned char serial[5]);
typedef int (CALLBACK *LPPOS_ReadCardNO)(int nCardNo[1]);
typedef int (CALLBACK *LPGetLastRecord)(POSRECORD *pCardRecord);

LPPOS_ConnectMF			POS_ConnectMF = NULL;
LPPOS_CloseMF			POS_CloseMF = NULL;
LPPOS_PacketDelMoney	POS_PacketDelMoney = NULL;
LPPOS_ReadBalance		POS_ReadBalance = NULL;
LPPOS_MendPacket		POS_MendPacket = NULL;
LPPOS_ControlBuzzer		POS_ControlBuzzer = NULL;
LPPOS_ReadStuempNo		POS_ReadStuempNo = NULL;
LPPOS_ReadSerial		POS_ReadSerial = NULL;
LPPOS_ReadCardNO		POS_ReadCardNO = NULL;
LPGetLastRecord			GetLastRecord = NULL;

// 计算KEYA
static void SMT_Cal_KeyA(unsigned char *key, unsigned char *ucSerialNo, unsigned char *ucKeyA)
{
	gen_user_card_keyA(key, ucSerialNo, ucKeyA);
}

// 计算KEYB
static void SMT_Cal_KeyB(unsigned char *key, unsigned char *ucSerialNo, unsigned char *ucKeyB)
{
	gen_user_card_keyB(key, ucSerialNo, ucKeyB);
}

//使用复旦密钥体系登陆卡片
static int Login_Card(int sector)
{
	unsigned char ucSerialNo[5], ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	//1 --- 计算KEYA
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(sector,ucKeyA,0);                       
	if(ret != 0)
	{
		return -2;//卡片登陆失败
	}
	return 0;
}

static int Login_Card_Keyb(int sector)
{
	unsigned char ucSerialNo[5], ucKeyB[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
	{
		DEBUG_CARD_MSGOUT(ret, "读取物理卡号失败");
		return -1;
	}
	//1 --- 计算KEYB
	SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	ret = SMT_Login_With_UserKey(sector, ucKeyB, 1);                       
	if (ret != 0)
	{
		DEBUG_CARD_MSGOUT(ret, "使用KEYB登录失败");
		return -2;
	}
	return 0;
}

void SetErrMsg(int ecode,char *errmsg)
{
	ErrCode=ecode;;
	strcpy(ErrMsg,errmsg);
}

int __stdcall GetLastErrMsg(int ecode[1], char *errmsg)
{
#ifdef YKTSERVER
	if (GW_GetLastErrorMsg != NULL)	{ GW_GetLastErrorMsg(errmsg); }
#else
	ecode[0]=ErrCode;
	strcpy(errmsg,ErrMsg);
#endif	
	return 0;
}

void __stdcall SetCardSectLength(const int card_sect_length)
{
	smart_card_sect_no = card_sect_length;
	return ;
}

int __stdcall ConnectMF(int com,int baud)
{
	int ret = 0;
	if (hDLL == NULL || hDesDLL == NULL || hGwKbcDLL == NULL || h_pos_dll == NULL)
	{
		ret = Load_Dll();
		if (ret)
		{
			return -1;
		}
			
	}
	if (com < 0)
	{
		com = 1;       //默认串口1
	}
	if (baud < 1)
	{
		baud = 19200;  //默认19200
	}
	
	ret = SMT_ConnectMF280(com,baud);
	strcpy(msg, "打开读卡器串口失败");

	RET_ERROR(ret, "打开串口失败")
	com_is_open = TRUE;
	ControlBuzzer();

	return 0;
}

int __stdcall CloseMF(void)
{
	int ret = 0;
	/*
	ret = SMT_CloseMF280();
	if(ret)
	{
		SetErrMsg(ret,"关闭串口失败");
		return ret;
	}
	*/

	FUNC0(SMT_CloseMF280, POS_CloseMF, dll_flag, ret)
	RET_ERROR(ret, "关闭串口失败")

	return 0;
}

int __stdcall ControlBuzzer()
{
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall HaltCard(void)
{
	int ret = 0;
	ret = SMT_SleepCard();
	if (ret)
	{
		SetErrMsg(ret, "休眠卡失败");
		return ret;
	}
	return 0;
}

//发行卡
int __stdcall PublishCard(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	BOOL bPersonalFlag=TRUE;
	BOOL bStateFlag=TRUE;
	BOOL bBankInfo=TRUE;
	BOOL bPacketFlag[8]={TRUE,TRUE,TRUE,TRUE,FALSE,FALSE,FALSE,FALSE};
	int iCardNo[1];
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	ret=SMT_ClearCard();
	if(ret)
	{
		SetErrMsg(ret,"格式化卡失败");
		return ret;
	}
	ret = strlen((char*)pc->ShowCardNo);
	if( 10==ret )	
	{
		//SetErrMsg(ret,"显示卡号长度不是10位");
		//return -4;		     //显示卡号位数错误
		//转换为BCD码
		dec2bcd(pc->ShowCardNo,ucBcdShowCardNo,5);
	}
	//转换为进制
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear,0,sizeof(sYear));
	memset(sMon,0,sizeof(sMon));
	memset(sDay,0,sizeof(sDay));

	memcpy(sYear,pc->DeadLineDate+2,2);
	memcpy(sMon,pc->DeadLineDate+4,2);
	memcpy(sDay,pc->DeadLineDate+6,2);
	
	ucDeadLineDate[0]=atoi(sYear);
	ucDeadLineDate[1]=atoi(sMon);
	ucDeadLineDate[2]=atoi(sDay);
	iCardNo[0]=atoi((char*)pc->CardNo);
	ucCardRightType[0]=pc->CardRightType;
	ret = SMT_WriteCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if(ret)
	{
		SetErrMsg(ret,"写卡基本信息失败");
		return ret;           //写基本信息错误
	}
	
	//备注,暂缺读写工号或学号的接口
	//写持卡人人事信息
	ret = SMT_WritePersonalInfo(pc->ucName,
								pc->ucDutyNo,
								pc->ucCertificateNo,
								pc->ucDepartmentNo,
								pc->ucIdentifyNo,
								pc->ucSexNo,
								pc->ucCardNo);
	if(ret)
	{
		SetErrMsg(ret,"写人事信息失败");
		return ret;           //
	}
	ret=SMT_WriteLibraryNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"写图书证号失败");
		return ret;
	}
	ret=WriteCardPwd(pc->ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"写卡密码失败");
		return ret;
	}
	//预存金额
	unsigned short int PacketNo = 1;
	int Money;
	Money = pc->Money;
	ret = SMT_PacketSetMoney(PacketNo,Money);
	if(ret)
	{
		SetErrMsg(ret,"设置钱包余额失败");
		return ret;		
	}
	SMT_ControlBuzzer();
	return 0;
}

int ifReadyOK()
{
	int ret = 0;
	//检查读写器是否授权
	ret = SMT_JudgeAutoFlag();
	if(ret!=1)
	{
		SetErrMsg(ret,"读卡器未授权");
		return ret;
	}
	//检查用户卡是否在感应区
	char ucSerialNo[9];
	char ucType[3];

	ret = RequestCard(ucSerialNo,ucType);
	if(ret)
	{
		return ret;
	}
	return 0;
}

int __stdcall ReaderAuthor(unsigned char *ucAuthorInfo)
{
	int ret = 0;
	unsigned char ucAuthor[9];
	memset(ucAuthor,0,sizeof(ucAuthor));
	memcpy(ucAuthor,ucAuthorInfo,8);
	//给读写器授权
	ret = SMT_AutoDll(ucAuthor);
	if(ret)
	{
		SetErrMsg(ret,"读卡器授权失败");
		return ret;
	}
    // 传出全局变量workingkey
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall RequestCard(char *ucSerialNo,char *ucType)
{

	int ret = 0;
	unsigned char SerialNo[4],Type[1];
	memset(SerialNo,0,4);
	memset(Type,0,1);

	//检查用户卡是否在感应区
	ret = SMT_RequestCardExist(SerialNo,Type);
	if(ret)
	{
		SetErrMsg(ret,"卡不在读卡器感应区");
		return ret;
	}
	sprintf(ucSerialNo,"%02X%02X%02X%02X",
		SerialNo[0],
		SerialNo[1],
		SerialNo[2],
		SerialNo[3]);
	sprintf(ucType,"%02X",Type[0]);
	return 0;
}

// 函数作用: 读取卡的状态信息, 
// 函数参数: 参数同上
int __stdcall SMT_ReadCardStateInfo(unsigned char ucShowCardNo[5],
								   int nDealCardNo[1],
								   unsigned char ucDeadLineDate[3],
								   unsigned char ucCardRightType[1])
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(1,0,ucBuffer);
	if(ret != 0)
		return -6; //读卡失败
	nDealCardNo[0] = ucBuffer[0]*256*256+ucBuffer[1]*256+ucBuffer[2];
	ucCardRightType[0] = ucBuffer[3];
	memcpy(ucDeadLineDate,ucBuffer+4,3);
	memcpy(ucShowCardNo,ucBuffer+7,5);
	return 0;
}

int __stdcall ReadCardInfo(TPublishCard *pc)
{
	int ret = 0; 
	int next_len = 0;
	unsigned char t;
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//用户卡使用截止日期
	unsigned char ucCardRightType[1];		//权限位
	int iCardNo[1];
	int show_card_len = 0;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	ret = SMT_ReadCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"读卡基本信息失败");
		return ret;    
	}

	while(show_card_len < 5)
	{
		t = ucBcdShowCardNo[show_card_len];
		if((t >> 4) == 0x0F)
			break;
		if((t & 0x0F) == 0x0F)
		{
			next_len = 1;
			break;
		}
		show_card_len++;
	}
	bcd2dec(ucBcdShowCardNo,show_card_len,pc->ShowCardNo);
	if(next_len>0)
	{
		pc->ShowCardNo[show_card_len*2] = ((ucBcdShowCardNo[show_card_len] >> 4) & 0x0F) + '0';
		pc->ShowCardNo[show_card_len*2 + 1] = '\0';
	}
	
	//转换hex日期格式到十进制
	sprintf((char*)pc->DeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo,"%d",iCardNo[0]);
	pc->CardRightType=ucCardRightType[0];
	ret = SMT_ReadPersonalInfo(pc->ucName,pc->ucDutyNo,pc->ucCertificateNo,pc->ucDepartmentNo,pc->ucIdentifyNo,pc->ucSexNo,pc->ucCardNo);
	if (ret !=0)
	{
		SetErrMsg(ret,"读卡人事信息失败");
		return ret;     
	}
	
	ret=SMT_ReadLibraryNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"写图书证号失败");
		return ret;
	}
	return 0;
}

//更新卡信息
int __stdcall UpdateCardInfo (TPublishCard *CardInfo)
{
	int ret = 0; 
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	unsigned char ucBcdShowCardNo[5];
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	//备注,暂缺读写工号或学号的接口
	//转换为进制
	memset(sYear,0,sizeof(sYear));
	memset(sMon,0,sizeof(sMon));
	memset(sDay,0,sizeof(sDay));
	memset(ucBcdShowCardNo,0,sizeof(ucBcdShowCardNo));

	memcpy(sYear,CardInfo->DeadLineDate+2,2);
	memcpy(sMon,CardInfo->DeadLineDate+4,2);
	memcpy(sDay,CardInfo->DeadLineDate+6,2);
	
	ucDeadLineDate[0]=atoi(sYear);
	ucDeadLineDate[1]=atoi(sMon);
	ucDeadLineDate[2]=atoi(sDay);

	ret = SMT_ChangeDeadLineDate(ucDeadLineDate);					//修改使用截止日期（8个字节日期(年月日)格式为："yy-mm-dd"）
	if(ret != 0)
	{
		SetErrMsg(ret,"修改截止日期时出错");
		return ret;
	}
	ucCardRightType[0]=CardInfo->CardRightType;
	ret = SMT_ChangeCardRightType(ucCardRightType);					//修改使用权限类型（1--254）	
	if(ret != 0)
	{
		SetErrMsg(ret,"修改卡权限类型时出错");
		return ret;
	}
	ret = SMT_ChangeName(CardInfo->ucName);							
	if(ret != 0)
	{
		SetErrMsg(ret,"修改姓名时出错");
		return ret;	
	}
	ret = SMT_ChangeDutyNo(CardInfo->ucDutyNo);						
	if(ret != 0)
	{
		SetErrMsg(ret,"修改职务代码时出错");
		return ret;
	}
	ret = SMT_ChangeCerificateNo(CardInfo->ucCertificateNo);		
	if(ret != 0)
	{
		SetErrMsg(ret,"修改证件号码时出错");
		return ret;	
	}
	ret = SMT_ChangeDepartmentNo(CardInfo->ucDepartmentNo);			
	if(ret != 0)
	{
		SetErrMsg(ret,"修改部门代码时出错");
		return ret;
	}
	ret = SMT_ChangeIdentifyNo(CardInfo->ucIdentifyNo);				
	if(ret != 0)
	{
		SetErrMsg(ret,"修改身份代码时出错");
		return ret;
	}
	ret = SMT_ChangeSexNo(CardInfo->ucSexNo);						
	if(ret != 0)
	{
		SetErrMsg(ret,"修改性别时出错");
		return ret;
	}
	ret = SMT_ChangeCardNo(CardInfo->ucCardNo);				
	if(ret != 0)
	{
		SetErrMsg(ret,"修改学工号时出错");
		return ret;
	}
	ret = SMT_WriteLibraryNo(CardInfo->ucLibraryNo);	
	if(ret != 0)
	{
		SetErrMsg(ret,"修改图书证号时出错");
		return ret;
	}
	ret = strlen((char*)CardInfo->ShowCardNo);
	if( 10==ret )	
	{
		//转换为BCD码
		dec2bcd(CardInfo->ShowCardNo,ucBcdShowCardNo,5);
		ret = SMT_ChangeShowCardNo(ucBcdShowCardNo);	
		if(ret != 0)
		{
			SetErrMsg(ret,"修改显示卡号时出错");
			return ret;
		}
	}
	return 0;
}

int __stdcall ReadPacketInfo( LPLOOPPURSEINFO LoopPurseInfo )
{
	int ret = 0; 

	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	int nPacketNo = 1;
	
	memset(LoopPurseInfo,0,sizeof(LOOPPURSEINFO));  //以前分配内存发生错误的原因是没有#pragma pack(1)

	ret = SMT_ReadPacketInfo(nPacketNo,LoopPurseInfo);
	if (ret !=0)
	{
		SetErrMsg(ret,"读包信息失败");
		return ret;
	}
	return ret;
}


int __stdcall ReadCardNO(int nCardNo[1])
{
	int ret;
	unsigned char ucBuffer[16];	
	ret = Login_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1,0,ucBuffer);
	if(ret != 0)	
		return ret;
	nCardNo[0] = ucBuffer[0]*256*256+ucBuffer[1]*256+ucBuffer[2];
	return 0;
}

int __stdcall WriteCardPwd(unsigned char pwd[6])
{
	int ret=0;
	unsigned char ucPwd[3];
	dec2bcd(pwd,ucPwd,3);
	ret=SMT_WritePersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"写卡密码失败");
		return ret;
	}
	return 0;
}

int __stdcall ReadCardPwd(unsigned char pwd[6])
{
	int ret=0;
	unsigned char ucPwd[3];
	ret=SMT_ReadPersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"读卡密码失败");
		return ret;
	}
	bcd2dec(ucPwd,3,pwd);
	return 0;
}

int __stdcall Load_Dll()
{
	char msg[512];
	if (NULL == hDLL)
	{
		hDLL = LoadLibrary(bufSmartCom);
		if (!hDLL)
		{
			return -1;
		}
		
		SMT_ConnectMF280		 = (LPSMT_ConnectMF280)GetProcAddress(hDLL,"SMT_ConnectMF280");
		SMT_ControlBuzzer        = (LPSMT_ControlBuzzer)GetProcAddress(hDLL,"SMT_ControlBuzzer");
		SMT_CloseMF280           = (LPSMT_CloseMF280)GetProcAddress(hDLL,"SMT_CloseMF280");
		SMT_RequestCardExist  	 = (LPSMT_RequestCardExist)GetProcAddress(hDLL,"SMT_RequestCardExist");
		SMT_SleepCard            = (LPSMT_SleepCard)GetProcAddress(hDLL,"SMT_SleepCard");
		MF_ReadSeriesNo          = (LPMF_ReadSeriesNo)GetProcAddress(hDLL, "MF_ReadSeriesNo");
		SMT_Login_With_UserKey   = (LPSMT_Login_With_UserKey)GetProcAddress(hDLL, "SMT_Login_With_UserKey");
		SMT_WriteBlock           = (LPSMT_WriteBlock)GetProcAddress(hDLL, "SMT_WriteBlock");
		SMT_ReadBlock            = (LPSMT_ReadBlock)GetProcAddress(hDLL, "SMT_ReadBlock");
		SetLastErrMsg            = (LPSetLastErrMsg)GetProcAddress(hDLL, "SetLastErrMsg");
		GetMFLastErr             = (LPGetMFLastErr)GetProcAddress(hDLL, "GetMFLastErr");
		if ((!SMT_ConnectMF280)			||
			(!SMT_ControlBuzzer)		||
			(!SMT_CloseMF280)			||
			(!SMT_WriteBlock)			||
			(!SMT_ReadBlock)			||
			(!MF_ReadSeriesNo)			||
			(!SMT_RequestCardExist)		||
			(!SMT_Login_With_UserKey)	||
			(!SMT_SleepCard)			||
			(!SetLastErrMsg)			||
			(!GetMFLastErr) 
			)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
			sprintf(msg,"加载基础库失败[%s]",bufSmartCom);
			DEBUG_CARD_MSGOUT(-2,msg);
			return -2;
		}
	}
	
	if (NULL == hDesDLL)
	{
		// 加载dessdll.dll库
		hDesDLL = LoadLibrary(bufDesdll);
		if (!hDesDLL)
		{
			return -1;
		}
		gen_user_card_keyA	= (lpgen_user_card_keyA)GetProcAddress(hDesDLL, "gen_user_card_keyA");
		gen_user_card_keyB	= (lpgen_user_card_keyB)GetProcAddress(hDesDLL, "gen_user_card_keyB");
		encrypt_work_key	= (lpencrypt_work_key)GetProcAddress(hDesDLL, "encrypt_work_key");
		gen_auth_card_keyA	= (lpgen_auth_card_keyA)GetProcAddress(hDesDLL, "gen_auth_card_keyA");
		gen_auth_card_keyB	= (lpgen_auth_card_keyB)GetProcAddress(hDesDLL, "gen_auth_card_keyB");
		decrypt_work_key	= (lpdecrypt_work_key)GetProcAddress(hDesDLL, "decrypt_work_key");
		get_check_char		= (lpget_check_char)GetProcAddress(hDesDLL, "get_check_char");
		if (
			(!gen_user_card_keyA) || 
			(!gen_user_card_keyB) ||
			(!encrypt_work_key)   ||
			(!gen_auth_card_keyA) ||
			(!gen_auth_card_keyB) ||
			(!decrypt_work_key)	  ||	
			(!get_check_char)     
			)
		{
			FreeLibrary(hDesDLL);
			hDesDLL = NULL;
#ifdef _DEBUG
			DEBUG_CARD_MSGOUT(-2, "加载DES库失败")
#endif
			return -2;
		}
	}

	if (NULL == hGwKbcDLL)
	{
		/************************************************************************/
		/* 加载GW_KBC库注意:															
		/* (1) 不在CardDLL.ini中增加DLLCOM选项则不加载GW_KBC库
		/* (2) 在CardDLL.ini中增加DLLCOM选项需要加载GW_KBC库和相关dll
		/* (3) 不加载GW_KBC调用其中相关函数需要判断函数地址
		/************************************************************************/
		hGwKbcDLL = LoadLibrary(bufGwKBCdll);
		if (!hGwKbcDLL)
		{
			DEBUG_CARD_MSGOUT(0, "不启用GW_KBC库");
			goto L_RET_POS;
			return 0;
		}
		GW_Login			= (LPGW_Login)GetProcAddress(hGwKbcDLL, "GW_Login");
		GW_CreateNewHandle	= (LPGW_CreateNewHandle)GetProcAddress(hGwKbcDLL, "GW_CreateNewHandle");
		GW_CloseHandle		= (LPGW_CloseHandle)GetProcAddress(hGwKbcDLL, "GW_CloseHandle");
		GW_Exit				= (LPGW_Exit)GetProcAddress(hGwKbcDLL, "GW_Exit");
		GW_GetCardInfo		= (LPGW_GetCardInfo)GetProcAddress(hGwKbcDLL, "GW_GetCardInfo");
		GW_GetCustomerInfo	= (LPGW_GetCustomerInfo)GetProcAddress(hGwKbcDLL, "GW_GetCustomerInfo");
		GW_GetLastErrorMsg  = (LPGW_GetLastErrorMsg)GetProcAddress(hGwKbcDLL, "GW_GetLastErrorMsg");
		GW_GetSeedKey		= (LPGW_GetSeedKey)GetProcAddress(hGwKbcDLL, "GW_GetSeedKey");
		if (
			(!GW_Login)				|| 
			(!GW_CreateNewHandle)	||
			(!GW_CloseHandle)		||
			(!GW_Exit)				||
			(!GW_GetCardInfo)		||
			(!GW_GetCustomerInfo)	||
			(!GW_GetLastErrorMsg)	||
			(!GW_GetSeedKey)
			)
		{
			FreeLibrary(hDesDLL);
			hGwKbcDLL = NULL;
			DEBUG_CARD_MSGOUT(-2, "加载GW_KBC库失败");
			return -2;
		}
		DEBUG_CARD_MSGOUT(0, "加载GW_KBC库成功");	
	}

L_RET_POS:

	if (NULL == h_pos_dll)
	{
		/************************************************************************/
		/* 加载POS硬件库注意事项:															
		/* (1) 通过CardDLL.ini的dll_flag表示加载的POS硬件库有哪些, 0-不加载硬件库, 
		/*	   1-加载
		/* (2) 不加载硬件库的时候不调用相关硬件功能库
		/* (3) 加载硬件功能库的时候同时加载读卡器的功能库, 保证兼容性和程序完整性
		/************************************************************************/
		if (0 == dll_flag)
		{
			sprintf(msg, "不加载POS库--dll_flag=[%d]", dll_flag);
			DEBUG_CARD_MSGOUT(0, msg)
			return 0;
		}
		
		h_pos_dll = LoadLibrary(buf_pos_dll);
		if (!h_pos_dll)
		{
			sprintf(msg,"加载h_pos_dll句柄失败,[%s]",buf_pos_dll);
			DEBUG_CARD_MSGOUT(0,msg);
			return -1;
		}

		POS_ConnectMF		= (LPPOS_ConnectMF)GetProcAddress(h_pos_dll, "POS_ConnectMF");
		POS_CloseMF			= (LPPOS_CloseMF)GetProcAddress(h_pos_dll, "POS_CloseMF");
		POS_PacketDelMoney	= (LPPOS_PacketDelMoney)GetProcAddress(h_pos_dll, "POS_PacketDelMoney");
		POS_ReadBalance		= (LPPOS_ReadBalance)GetProcAddress(h_pos_dll, "POS_ReadBalance");
		POS_MendPacket		= (LPPOS_MendPacket)GetProcAddress(h_pos_dll, "POS_MendPacket");
		POS_ControlBuzzer	= (LPPOS_ControlBuzzer)GetProcAddress(h_pos_dll, "POS_ControlBuzzer");
		POS_ReadStuempNo	= (LPPOS_ReadStuempNo)GetProcAddress(h_pos_dll, "POS_ReadStuempNo");
		POS_ReadSerial		= (LPPOS_ReadSerial)GetProcAddress(h_pos_dll, "POS_ReadSerial");
		POS_ReadCardNO		= (LPPOS_ReadCardNO)GetProcAddress(h_pos_dll, "POS_ReadCardNO");
		GetLastRecord		= (LPGetLastRecord)GetProcAddress(h_pos_dll, "GetLastRecord");
		if (
				(!POS_ConnectMF)		|| 
				(!POS_CloseMF)			||
				(!POS_PacketDelMoney)   ||
				(!POS_ReadBalance)		||
				(!POS_MendPacket)		||
				(!POS_ControlBuzzer)	||	
				(!POS_ReadStuempNo)		||
				(!POS_ReadSerial)		||
				(!POS_ReadCardNO)		||
				(!GetLastRecord)
			)
		{
			FreeLibrary(h_pos_dll);
			h_pos_dll = NULL;
			sprintf(msg,"加载POS库失败,[%s]",buf_pos_dll);
			DEBUG_CARD_MSGOUT(-2,msg);
			return -2;
		}
	}

	return 0;
}
/************************************************************************/
/*           新添加的函数， 操作功能函数, 来源于SMARTCOM411DXQ          */
/************************************************************************/

// ascWorkKey种子明文密钥
// 函数功能: 密码认证 
// 用于新大陆和明华的设备, 三九不用
int  _stdcall Load_WorkKey(char *ascWorkKey)
{
	//计算扇区密钥
	int ret=0;
	int i=0;
	unsigned char ucCryptWorkKey[17];
	memset(SMT_UCWORKINGKEY, 0, sizeof(SMT_UCWORKINGKEY));
	hex2dec(ascWorkKey, ucCryptWorkKey, 8);
	encrypt_work_key(ucCryptWorkKey, SMT_UCWORKINGKEY);
	nAutoFlag = 1;										// 这里新增加的东西
	return 0;
}

// 函数功能: 判断标志
// 函数参数: 无
int __stdcall SMT_JudgeAutoFlag()
//返回值：     0：未授权     1：授权
{
	return nAutoFlag;
}

// 函数功能: 密码认证
// 函数参数: uckWorkingKey种子密钥 
int __stdcall SMT_AutoDll(unsigned char *ucWorkingKey)
{
	int i;
	memcpy(SMT_UCWORKINGKEY, ucWorkingKey, 8);
	for(i=0;i<8;i++)
		SMT_UCWORKINGKEY[i+8] = ~ucWorkingKey[i];
	has_read_main_key = TRUE;
	nAutoFlag = 1;
	return 0;
}

// 函数功能: 读取序列号
// 函数参数: 序列号数组
int __stdcall ReadSerial(unsigned char *serial)
{
//	return FUNC1(MF_ReadSeriesNo, POS_ReadSerial, dll_flag, serial)
	return MF_ReadSeriesNo(serial);
}

// 函数功能: 创建裸卡
// 函数参数: bPersonalFlag(个人信息标志), bStateFlag(状态标志), bBankInfo(存储信息), bPacketFlag(包标志)
int __stdcall SMT_CreateGreyCard(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8])
{
	unsigned char ucSerialNo[5];
	unsigned char ucKeyA[6],ucKeyB[6];
	unsigned char ucRawData[256],ucTmpRawData[16],ucDesData[256];
	
	int i,j,startSector=4;
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
		return -1;//卡片不在感应区
	//1、使用出场密码登陆卡片  前32个扇区
	memset(ucKeyA,0xFF,6);
	memset(ucKeyB,0xFF,6);
	memset(ucRawData,0x00,16);
	for(i=0;i<32;i++)
	{
		ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		if(ret != 0)
			return -2; //非出厂卡
//		ret = SMT_Login_With_UserKey(i,ucKeyB,1);
//		if(ret != 0)
//			return -3; //非出厂卡
		for(j=0;j<3;j++)
		{
			if(i==0&&j==0)
				continue;
			ret=SMT_WriteBlock(i,j,ucRawData);
			if(ret)
				return -4;
		}
	}
	//2、更改KEYA、KEYB发行钱包扇区
	//1 --- 计算KEYA
	//////////////////////////////////////////////////////
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	//计算KEYB
	//////////////////////////////////////////////////////
	SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	///////////////////////////////////////////////////////
	memcpy(ucRawData,ucKeyA,6);
	ucRawData[6] = 0x7F;
	ucRawData[7] = 0x07;
	ucRawData[8] = 0x88;
	ucRawData[9] = 0x00;
	memcpy(ucRawData+10,ucKeyB,6);
	memset(ucDesData,0xFF,6);
	for(i=0;i<32;i++)
	{
		ret = SMT_Login_With_UserKey(i,ucDesData,0);
		if(ret != 0)
			return -5; //非出厂卡
		memcpy(ucTmpRawData,ucRawData,16);
		ret = SMT_WriteBlock(i,3,ucTmpRawData);
		if(ret != 0)
			return -6; //卡片加密失败
		ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		if(ret)
			return -11;
	}
	//发行钱包区 第0块
	j = 0;
	for(i=0;i<8;i++)
	{
		if(bPacketFlag[i] == TRUE)
			ucRawData[j] = 0x00;
		else
			ucRawData[j] = 0xFF;
		j = j + 1;
		if(bPacketFlag[i] == TRUE)
		{
			ucRawData[j] = startSector;
			startSector+=1;
		}
		else
			ucRawData[j] = 0xFF;
		j=j+1;
	}
	//1 使用用户密码登陆
	ret = SMT_Login_With_UserKey(3,ucKeyA,0);
	if(ret != 0)
		return -7;//使用用户密码KEYA不能登陆
	ret = SMT_WriteBlock(3,0,ucRawData);
	if(ret != 0)
		return -8;//无法写卡
	memset(ucRawData,0xFF,16);
	for(i=0;i<8;i++)
	{
		if(bPacketFlag[i] == TRUE)
		{
			ucRawData[i] = startSector;
			startSector += 1;
		}
		else
			ucRawData[i] = 0xFF;
	}
	ret = SMT_WriteBlock(3,1,ucRawData);
	if(ret != 0)
		return -9;//无法写卡
	memset(ucRawData,0xFF,16);  //20050305增加
	ret = SMT_WriteBlock(3,2,ucRawData);
	if(ret != 0)
		return -10;//无法写卡
	return 0;
}

// 函数作用: 写入卡的状态信息 
// 函数参数: ucShowCardNo(用户显示卡号), nDealCardNo(用户交易卡号), 
// ucDeadLineDate(卡的截止日期), ucCardRightType(用户卡使用类型权限)
int __stdcall SMT_WriteCardStateInfo(unsigned char ucShowCardNo[5], 
						   int nDealCardNo[1], 
						   unsigned char ucDeadLineDate[3], 
						   unsigned char ucCardRightType[1])
{
	unsigned char ucSerialNo[5],ucRawData[256],ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	//1 --- 计算KEYA
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(1, ucKeyA, 0);
	if(ret != 0)
		return -2;//卡片登陆失败
	//第0块数据组织
	if(nDealCardNo[0] > 0x0FFFFF)
		return -3;//交易卡号过大
	memset(ucRawData,0xFF,16);
	ucRawData[0] = nDealCardNo[0] / 256 / 256;
	ucRawData[1] = nDealCardNo[0] / 256;
	ucRawData[2] = nDealCardNo[0] % 256;
	ucRawData[3] = ucCardRightType[0];
	memcpy(ucRawData + 4, ucDeadLineDate, 3);
	memcpy(ucRawData + 7, ucShowCardNo, 5);
	ret = SMT_WriteBlock(1, 0, ucRawData);
	if(ret != 0)
		return -5; //写卡失败
	return 0;				
}

// 函数作用: 修改用户卡号
// 函数参数: 用户卡号 
int __stdcall SMT_ChangeShowCardNo(unsigned char ucShowCardNo[5])
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(1,0,ucBuffer);
	if(ret != 0)
		return -6; //读卡失败
	memcpy(ucBuffer+7,ucShowCardNo,5);
	ret = SMT_WriteBlock(1,0,ucBuffer);
	if(ret != 0)
		return -5; //写卡失败
	return 0;
}

// 函数作用: 修改交易卡号
// 函数参数: 交易卡号
int __stdcall SMT_ChangeDealCardNo(int nDealCardNo)
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -6; //读卡失败
	ucBuffer[0] = nDealCardNo/256/256;
	ucBuffer[1] = nDealCardNo/256;
	ucBuffer[2] = nDealCardNo%256;
	ret = SMT_WriteBlock(1,0,ucBuffer);
	if(ret != 0)
		return -5; //写卡失败
	return 0;
}

// 函数作用: 修改卡片使用截至日期
// 函数参数: 截止日期时间
int __stdcall SMT_ChangeDeadLineDate(unsigned char ucDeadLineDate[3])
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -6; //读卡失败
	memcpy(ucBuffer + 4, ucDeadLineDate, 3);
	ret = SMT_WriteBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -5; //写卡失败
	return 0;
}

// 函数作用: 修改卡片权限类型
// 函数参数: 卡片权限类型
int __stdcall SMT_ChangeCardRightType (unsigned char ucCardRightType[1])
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(1,0,ucBuffer);
	if(ret != 0)
		return -6; //读卡失败
	memcpy(ucBuffer+3,ucCardRightType,1);
	ret = SMT_WriteBlock(1,0,ucBuffer);
	if(ret != 0)
		return -5; //写卡失败
	return 0;
}

// 函数作用：写入卡片个人信息
// 函数参数: ucName(姓名), ucDutyNo(职务代码), ucCertificateNo(证件代码)
// ucDepartmentNo(部门编号), ucIdentifyNo(身份代码), ucSexNo(性别), ucCardNo(卡号)
int __stdcall SMT_WritePersonalInfo(unsigned char ucName[8],
									unsigned char ucDutyNo[4],
									unsigned char ucCertificateNo[20],
									unsigned char ucDepartmentNo[10],
									unsigned char ucIdentifyNo[4],
									unsigned char ucSexNo[1],
									unsigned char ucCardNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card_Keyb(0);
	if(ret != 0)	return ret;
	memcpy(ucBuffer,ucCardNo,16);
	ret = SMT_WriteBlock(0,1,ucBuffer);
	if(ret != 0)	return -5;
	memset(ucBuffer,0xFF,16);
	memcpy(ucBuffer,ucCardNo+16,4);
	ret = SMT_WriteBlock(0,2,ucBuffer);
	if(ret != 0)	return -5;
	//第2扇区0块操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	memcpy(ucBuffer,ucName,8);
	memcpy(ucBuffer+8,ucDutyNo,4);
	memcpy(ucBuffer+12,ucCertificateNo,4);
	ret = SMT_WriteBlock(2,0,ucBuffer);
	if(ret != 0)	return -5;
	memcpy(ucBuffer,ucCertificateNo+4,16);
	ret = SMT_WriteBlock(2,1,ucBuffer);
	if(ret != 0)	return -5;
	memcpy(ucBuffer,ucDepartmentNo,10);
	memcpy(ucBuffer+10,ucIdentifyNo,4);
	memcpy(ucBuffer+14,ucSexNo,1);
	ret = SMT_WriteBlock(2,2,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 读取卡片个人信息
// 函数参数: 如上所示
int __stdcall SMT_ReadPersonalInfo(unsigned char ucName[8],
								   unsigned char ucDutyNo[4],
								   unsigned char ucCertificateNo[20],
								   unsigned char ucDepartmentNo[10],
								   unsigned char ucIdentifyNo[4],
								   unsigned char ucSexNo[1],
								   unsigned char ucCardNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card_Keyb(0);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(0,1,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucCardNo,ucBuffer,16);
	ret = SMT_ReadBlock(0,2,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucCardNo+16,ucBuffer,4);

	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,0,ucBuffer);
	if(ret != 0 )	return -6;
	memcpy(ucName,ucBuffer,8);
	memcpy(ucDutyNo,ucBuffer+8,4);
	memcpy(ucCertificateNo,ucBuffer+12,4);
	ret = SMT_ReadBlock(2,1,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucCertificateNo+4,ucBuffer,16);
	ret = SMT_ReadBlock(2,2,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucDepartmentNo,ucBuffer,10);
	memcpy(ucIdentifyNo,ucBuffer+10,4);
	memcpy(ucSexNo,ucBuffer+14,1);
	return 0;
}

// 函数作用: 修改用户姓名
// 函数参数: 用户名
int __stdcall SMT_ChangeName(unsigned char ucName[8])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,0,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucBuffer,ucName,8);
	ret = SMT_WriteBlock(2,0,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数名称: 修改职务代码
// 函数参数: 职务编号
int __stdcall SMT_ChangeDutyNo(unsigned char ucDutyNo[4])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,0,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucBuffer+8,ucDutyNo,4);
	ret = SMT_WriteBlock(2,0,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用：修改证件号码
// 函数参数: 证件号
int __stdcall SMT_ChangeCerificateNo (unsigned char ucCertificateNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,0,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucBuffer+12,ucCertificateNo,4);
	ret = SMT_WriteBlock(2,0,ucBuffer);
	if(ret != 0)	return -5;
	memcpy(ucBuffer,ucCertificateNo+4,16);
	ret = SMT_WriteBlock(2,1,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 修改部门编号
// 函数参数: 部门编号
int __stdcall SMT_ChangeDepartmentNo(unsigned char ucDepartmentNo[10])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,2,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucBuffer,ucDepartmentNo,10);
	ret = SMT_WriteBlock(2,2,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 修改身份代号
// 函数参数: 身份代号
int __stdcall SMT_ChangeIdentifyNo (unsigned char ucIdentifyNo[4])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,2,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucBuffer+10,ucIdentifyNo,4);
	ret = SMT_WriteBlock(2,2,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 修改性别代码
// 函数参数: 性别代号
int __stdcall SMT_ChangeSexNo (unsigned char ucSexNo[1])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card(2);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(2,2,ucBuffer);
	if(ret != 0)	return -6;
	memcpy(ucBuffer+14,ucSexNo,1);
	ret = SMT_WriteBlock(2,2,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 修改(学工号)
// 函数参数: 学工号
int __stdcall SMT_ChangeCardNo(unsigned char ucCardNo[20])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card_Keyb(0);
	if(ret != 0)	return ret;
	memcpy(ucBuffer,ucCardNo,16);
	ret = SMT_WriteBlock(0,1,ucBuffer);
	if(ret != 0)	return -6;
	memset(ucBuffer,0xFF,16);
	memcpy(ucBuffer,ucCardNo+16,4);
	ret = SMT_WriteBlock(0,2,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 写入个人密码
// 函数参数: 个人密码
int __stdcall SMT_WritePersonalPassword(unsigned char PersonalPsd[3])
{
	int ret;
	unsigned char ucBuffer[16];
	
	ret = Login_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1,1,ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer,PersonalPsd,3);
	ret = SMT_WriteBlock(1,1,ucBuffer);
	if(ret != 0)	
		return ret;
	return 0;
}

// 函数作用: 读取个人密码
// 函数参数: 个人密码(3位)
int __stdcall SMT_ReadPersonalPassword(unsigned char PersonalPsd[3])
{
	int ret;
	unsigned char ucBuffer[16];
	
	ret = Login_Card(1);
	if(ret != 0)	
		return ret;
	//memset(ucBuffer,0xFF,16);
	ret = SMT_ReadBlock(1,1,ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(PersonalPsd,ucBuffer,3);
	return 0;
}

// 函数作用: 写图书证号
// 函数参数: 图书证号
int __stdcall SMT_WriteLibraryNo(unsigned char ucLibraryNo[13])
{
	int ret;
	unsigned char ucBuffer[16];
	
	ret = Login_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1,1,ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer+3,ucLibraryNo,13);
	ret = SMT_WriteBlock(1,1,ucBuffer);
	if(ret != 0)	
		return ret;
	return 0;
}

// 函数作用: 读图书证号
// 函数参数: 图书证号
int __stdcall SMT_ReadLibraryNo(unsigned char ucLibraryNo[13])
{
	int ret;
	unsigned char ucBuffer[16];
	
	ret = Login_Card(1);
	if(ret != 0)	
		return ret;
	//memset(ucBuffer,0xFF,16);
	ret = SMT_ReadBlock(1,1,ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(ucLibraryNo,ucBuffer+3,13);
	return 0;
}

// 函数作用: 写银行卡号
// 函数参数: 银行卡号
int __stdcall SMT_WriteBankCardNo(unsigned char ucBankCardNo[10])
{
	int ret;
	unsigned char ucBuffer[16];
	
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	memset(ucBuffer,0xFF,16);
	memcpy(ucBuffer,ucBankCardNo,10);
	ret = SMT_WriteBlock(1,2,ucBuffer);
	if(ret != 0)	return -5;
	return 0;
}

// 函数作用: 读银行卡号
// 函数参数: 银行卡号
int __stdcall SMT_ReadBankCardNo(unsigned char  ucBankCardNo[10])
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(1);
	if(ret != 0)	return ret;
	memset(ucBuffer,0xFF,16);
	ret = SMT_ReadBlock(1,2,ucBuffer);
	if(ret != 0)	return -5;
	memcpy(ucBankCardNo,ucBuffer,10);
	return 0;
}

// 函数作用: 读钱包信息
// 函数参数: nPacketNo(钱包号), LoopPurseInfo(电子钱包信息)
int __stdcall SMT_ReadPacketInfo(int nPacketNo, LOOPPURSEINFO *LoopPurseInfo)   
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)	
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:登录3扇区失败",__FILE__,__LINE__,ret);
		return ret;
	}
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读3扇区失败",__FILE__,__LINE__,ret);	
		return -5;
	}
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
	{
		SetLastErrMsg(1,"File:%s\nLine:%d\nError:%d\nMessage:钱包%d未开通",__FILE__,__LINE__,ret,nPacketNo);	
		return 1; //钱包不允许使用
	}
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:登陆第%d扇区失败",__FILE__,__LINE__,ret,sector);	
		return ret;
	}

	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区失败",__FILE__,__LINE__,ret,sector);	
		return -5;
	}
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		LoopPurseInfo->RemainMoney = ucBuf1[0]+ucBuf1[1]*256+ucBuf1[2]*256*256;
		LoopPurseInfo->DealTimes   = ucBuf1[3]*256+ucBuf1[4];
		LoopPurseInfo->DealYear    = ucBuf1[5];
		LoopPurseInfo->DealMonth   = ucBuf1[6];
		LoopPurseInfo->DealDay     = ucBuf1[7];
		LoopPurseInfo->DealHour    = ucBuf1[8];
		LoopPurseInfo->DealMin     = ucBuf1[9];
		LoopPurseInfo->DealTimes_CurTime = ucBuf1[0x0D];
		LoopPurseInfo->DealTimes_CurDay  = ucBuf1[0X0E];
		return 0;
	}
	else
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区校验和错误,开始读备份扇区",__FILE__,__LINE__,0,sector);	
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)
		{
			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区失败",__FILE__,__LINE__,ret,sector);	
			return -5;
		}
		ucCheck = 0;
		for(i=0;i<15;i++)
			ucCheck+=ucBuf2[i];
		if(ucCheck == ucBuf2[15])
		{
			LoopPurseInfo->RemainMoney = ucBuf2[0]+ucBuf2[1]*256+ucBuf2[2]*256*256;
			LoopPurseInfo->DealTimes   = ucBuf2[3]*256+ucBuf2[4];
			LoopPurseInfo->DealYear    = ucBuf2[5];
			LoopPurseInfo->DealMonth   = ucBuf2[6];
			LoopPurseInfo->DealDay     = ucBuf2[7];
			LoopPurseInfo->DealHour    = ucBuf2[8];
			LoopPurseInfo->DealMin     = ucBuf2[9];
			LoopPurseInfo->DealTimes_CurTime = ucBuf2[0x0D];
			LoopPurseInfo->DealTimes_CurDay  = ucBuf2[0X0E];
			return 0;
		}
		else
		{
			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区备份块校验和错误",__FILE__,__LINE__,ret,sector);	
			return 2;
		}
	}
	return 2;
}

// 函数作用: 钱包增加钱
// 函数参数: nPacketNo(钱包号), nMoney(钱数量)　
// 说明: 这个函数有变动, 将时间替换成为了API的形式
int __stdcall SMT_PacketAddMomey(int nPacketNo,int nMoney)
{
	int ret,sector;
	if(nPacketNo<1)
		return -1;
	if(nMoney<0)
		return -1;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;
	
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; //钱包不允许使用
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)	
		return -6;
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;
		i = ucBuf1[0]+ucBuf1[1]*256+ucBuf1[2]*256*256;
		i = i + nMoney;
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
//		CTime tm = CTime::GetCurrentTime();                               这里修改过
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf1[7])                                   // (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf1[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
		return 0;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = ucBuf2[0]+ucBuf2[1]*256+ucBuf2[2]*256*256;
		i = i + nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf2[7])                                  // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf2[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if(ret != 0)	
			return -12;
	}
	return 0;
}

// 函数作用: 钱包减钱
// 函数参数: 如上所示
int __stdcall SMT_PacketDelMomey(int nPacketNo,int nMoney)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
	if(nMoney<0)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;
	
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; //钱包不允许使用
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)	
		return -5;
	int i;
	
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;
		i = ucBuf1[0]+ucBuf1[1]*256+ucBuf1[2]*256*256;
		if(i<nMoney)	
			return 3;
		i = i - nMoney;
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf1[7])                                      //(tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);                           // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)(tm.wMonth);                                 // tm.GetMonth();
		ucBuf1[7] = (BYTE)(tm.wDay);                                   // tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;                                    // tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;                                  // tm.GetMinute();
		ucBuf1[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -6;
		return 0;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -5;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = ucBuf2[0]+ucBuf2[1]*256+ucBuf2[2]*256*256;
		if(i<nMoney)	
			return 3;
		i = i - nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
	//	CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf2[7])                              // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);                   // tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)(tm.wMonth);                         // tm.GetMonth();
		ucBuf2[7] = (BYTE)(tm.wDay);                           // tm.GetDay();
		ucBuf2[8] = (BYTE)(tm.wHour);                          // tm.GetHour();
		ucBuf2[9] = (BYTE)(tm.wMinute);                        // tm.GetMinute();
		ucBuf2[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if(ret != 0)	
			return -6;
		return 0;
	}
	return 0;
}


// 函数作用: 修改钱包信息
// 函数参数: 入上所示
int __stdcall SMT_PacketSetMoney(int nPacketNo,int nMoney)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
	if(nMoney<0)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;
	
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; //钱包不允许使用
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)	
		return -6;
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;
		i = nMoney;
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
// 		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf1[7])									// (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);                        // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;								// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;									// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;									// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;								// tm.GetMinute();
		ucBuf1[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
		return 0;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf2[7])                               // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);					// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;							// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;								// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;								// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;							// tm.GetMinute();
		ucBuf2[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if(ret != 0)	
			return -12;
	}
	return 0;
}

// 函数作用: 修改钱包信息
// 函数参数: 入上所示
int __stdcall SMT_PacketSetMoney2(int nPacketNo, int nMoney, int nCnt)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
	if(nMoney<0)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;

	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; //钱包不允许使用
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区

	ret = Login_Card(sector);
	if(ret != 0)
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)	
		return -6;
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;
		i = nMoney;
		ucBuf1[0] = i % 256;
		ucBuf1[1] = i / 256;
		ucBuf1[2] = i / 256 / 256;
	
		ucBuf1[3] = nCnt / 256;
		ucBuf1[4] = nCnt % 256;
		// 		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf1[7])									// (tm.GetDay()!=ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);                        // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;								// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;									// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;									// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;								// tm.GetMinute();
		ucBuf1[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
		return 0;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = nMoney;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;

		ucBuf2[3] = nCnt / 256;
		ucBuf2[4] = nCnt % 256;
		//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf2[7])                               // (tm.GetDay()!=ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);					// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;							// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;								// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;								// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;							// tm.GetMinute();
		ucBuf2[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if(ret != 0)	
			return -12;
	}
	return 0;
}

// 函数作用：钱包重置
// 函数参数: 钱包号
int __stdcall SMT_PacketReset(int nPacketNo)
{
	int ret,sector;
	if(nPacketNo<1)
		return -1;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)	return ret;
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;

	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; //钱包不允许使用
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	// 
	memset(ucBuffer,0,sizeof ucBuffer);
	ret = Login_Card(sector);
	if(ret != 0)
		return ret;
	ret = SMT_WriteBlock(sector,0,ucBuffer);
	if(ret != 0)
		return ret;
	memset(ucBuffer,0,sizeof ucBuffer);
	ret = SMT_WriteBlock(sector,2,ucBuffer);
	return ret;
}

// 写帮助信息
int __stdcall SMT_WriteAssistInfo (int nBatchNo[1],int nMoney[1])
{
	return 0;
}

// 读取帮助信息
int __stdcall SMT_ReadAssisInfo(int nBatchNo[1],int nMoney[1],unsigned char ucBatchTime[5],unsigned char ucMacNo[4])
{
	return 0;
}

// 函数功能: 设置黑卡标记, 开头两字符黑卡为00, 白卡为FF
// 函数参数: 无
int __stdcall SMT_SetBlackCardFlag()
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)	return ret;
	memset(ucBuffer,0xFF,16);
	ucBuffer[0] = 0x00;
	ret = SMT_WriteBlock(3,2,ucBuffer);
	if(ret != 0)	return -6;
	return 0;
}

// 函数功能: 设置普通卡标记(非黑卡)
// 函数参数: 无
int __stdcall SMT_SetNormalFlag()
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)	
		return ret;
//	CTime tm = CTime::GetCurrentTime();
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	unsigned char ucDateTime[20];
	unsigned char ucBcdDateTime[6];
	memset(ucDateTime,0,sizeof(ucDateTime));
	memset(ucBcdDateTime,0,sizeof(ucBcdDateTime));
//	sprintf((char*)ucDateTime,"%02d%02d%02d%02d%02d%02d",tm.GetYear()-2000,tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
	sprintf((char*)ucDateTime, "%02d%02d%02d%02d%02d%02d", (BYTE)(tm.wYear - 2000), (BYTE)tm.wMonth, (BYTE)tm.wDay, (BYTE)tm.wHour, (BYTE)tm.wMinute, (BYTE)tm.wSecond);
	dec2bcd(ucDateTime,ucBcdDateTime,6);
	memset(ucBuffer,0xFF,16);
	memcpy(ucBuffer+1,ucBcdDateTime,6);
	ret = SMT_WriteBlock(3,2,ucBuffer);
	if(ret != 0)	
		return -6;
	return 0;
}

// 函数作用: 由不同版本设置普通标记
// 函数参数: 版本号
int __stdcall SMT_SetNormalFlagByBlkVerion(char *blkversion)
{
	int ret;
	unsigned char ucBlkVer[12];
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)	
		return ret;
	if(strlen(blkversion)!=12)
	{
		return -1;	
	}
	dec2bcd((unsigned char*)blkversion,ucBlkVer,6);
	memset(ucBuffer,0xFF,16);
	memcpy(ucBuffer+1,ucBlkVer,6);
	ret = SMT_WriteBlock(3,2,ucBuffer);
	if(ret != 0)	
		return -6;
	return 0;
}

// 函数作用: 清除卡信息
// 函数参数: 无
int __stdcall SMT_ClearCard()
{
	unsigned char ucSerialNo[5];
	unsigned char ucKeyA[6];
	unsigned char ucRawData[256];
	
	int i,j,startSector=4;
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	//1、使用出场密码登陆卡片  前32个扇区
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	/************************************************************************/
	/* 1: 松江大学城单独需求, 清除卡片信息, 扇区公开为0-8扇区
	/* 2: 0-2为客户信息
	/* 3: 3扇区为钱包索引扇区(使用4-7的索引, 没有补助索引), 4-7为钱包扇区
	/* 4: 8为保留扇区
	/************************************************************************/
	for (i = 0; i < 9; i++)																			
	{
		if (i == 3)
			continue;
		
		if (0 == i)
			ret = Login_Card_Keyb(0);
		else
			ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		
		if (ret != 0)
		{
			DEBUG_CARD_MSGOUT(ret, "登录卡片失败");
			return -2; 
		}
		
		for (j = 0; j < 3; j++)
		{
			if (i == 0 && j == 0)
				continue;

			if (i == 1 && j == 0)
			{
				//  如果是第1扇区第0块，读取显示卡号，不要删除该数据
				ret = SMT_ReadBlock(i,j,ucRawData);
				if(ret)
					return -3;
				// 清除除显示卡号以外的其它数据
				memset(ucRawData,0x00,7);
				memset(ucRawData+12,0x00,4);
			}
			else
			{
				memset(ucRawData,0x00,16);
			}
			ret = SMT_WriteBlock(i,j,ucRawData);
			if (ret)
				return -3;
		}
	}

	memset(ucRawData,0xFF,16);
	j = 0;
	for(i=0;i<4;i++)
	{
		ucRawData[j] = 0x00;							   // 打开四个钱包扇区
		j=j+1;
		ucRawData[j] = startSector;                        // 注意只能改第四个
		startSector+=1;
		j=j+1;
	}
	//1 使用用户密码登陆
	ret = SMT_Login_With_UserKey(3, ucKeyA, 0);
	if (ret != 0)
		return -4;//使用用户密码KEYA不能登陆
	ret = SMT_WriteBlock(3, 0, ucRawData);
	if (ret != 0)
		return -5;//无法写卡
	
	memset(ucRawData, 0x00, 16);  //20050305增加
	ucRawData[0] = 0xFF;		  //白卡
	ret = SMT_WriteBlock(3,2,ucRawData);
	if(ret != 0)
		return -7;//无法写卡
	return 0;
}

// 函数功能: 读取认证卡标记
// 函数参数: flag(标记位置)
int __stdcall SMT_ReadAuthCardFlag(short * flag)
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[6]="",ucInitKeyB[6]="";	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
		return -1;//卡片不在感应区
	}
	memcpy(ucInitKeyA,ucSerialNo,4);
	//读第7扇区
	sprintf((char*)&ucInitKeyA[4],"%02X",7);
	ret = SMT_Login_With_UserKey(7,ucInitKeyA,0);
	if(ret != 0)
		return -2; //非出厂卡
	int  iWorkKeyAtBlockNo;
	int  iWorkKeyAtBlockStartPos;
	unsigned char ucAuthKeyA[6];
//	unsigned char ucAuthKeyB[6];
	unsigned char ucBuf1[16]="";
	ret = SMT_ReadBlock(7,1,ucBuf1);
	if(ret != 0)	
		return -3;	
//	memcpy(ucAuthKeyB,ucBuf1,6);
	iWorkKeyAtBlockNo=ucBuf1[6]-'0';
	iWorkKeyAtBlockStartPos=ucBuf1[7]-'0';

	unsigned char ucBuf2[16]="";
	unsigned char ucSector[3]="";
	int iWorkKeyAtSectorNo;
	//读第15扇区
	sprintf((char*)&ucInitKeyA[4],"%02X",15);
	ret = SMT_Login_With_UserKey(15,ucInitKeyA,0);
	if(ret != 0)
		return -4; //非出厂卡
	ret = SMT_ReadBlock(15,2,ucBuf2);
	if(ret != 0)	
		return -5;	
	//读工作密钥扇区
	memset(ucSector,0,sizeof(ucSector));
	memcpy(ucSector,ucBuf2+14,2);
	iWorkKeyAtSectorNo=strtoul((char*)ucSector,NULL,16);
	memcpy(ucAuthKeyA,ucBuf2+8,6);
	ret = SMT_Login_With_UserKey(iWorkKeyAtSectorNo,ucAuthKeyA,0);
	if(ret != 0)
		return -6; //非出厂卡
	unsigned char ucBuf3[256]="";
	memset(ucBuf3,0,sizeof(ucBuf3));
	ret = SMT_ReadBlock(iWorkKeyAtSectorNo,iWorkKeyAtBlockNo,ucBuf3);
	if(ret != 0)	
		return -7;
	*flag = (short)ucBuf3[iWorkKeyAtBlockStartPos+9];
	return 0;
}

// 函数功能: 读取认证卡2
// 函数参数: ucWorkKey(种子密钥), flag(标记位置)
int __stdcall SMT_ReadAuthCard2(unsigned char ucWorkKey[8],short * flag)
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[7]="",ucInitKeyB[7]="";
	//////////////////////////////////////////////////////////////////////////
	// 测试用
	ret = Load_Dll();
	if (ret != 0)
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
		return -1;//卡片不在感应区
	}
	memcpy(ucInitKeyA,ucSerialNo,4);
	//读第7扇区
	sprintf((char*)&ucInitKeyA[4],"%02X",7);
	ret = SMT_Login_With_UserKey(7,ucInitKeyA,0);
	if(ret != 0)
		return -2; //非出厂卡
	int  iWorkKeyAtBlockNo;
	int  iWorkKeyAtBlockStartPos;
	unsigned char ucAuthKeyA[6];
//	unsigned char ucAuthKeyB[6];
	unsigned char ucBuf1[16]="";
	ret = SMT_ReadBlock(7,1,ucBuf1);
	if(ret != 0)	
		return -3;	
//	memcpy(ucAuthKeyB,ucBuf1,6);
	iWorkKeyAtBlockNo=ucBuf1[6]-'0';
	iWorkKeyAtBlockStartPos=ucBuf1[7]-'0';

	unsigned char ucBuf2[16]="";
	unsigned char ucSector[3]="";
	int iWorkKeyAtSectorNo;
	//读第15扇区
	sprintf((char*)&ucInitKeyA[4],"%02X",15);
	ret = SMT_Login_With_UserKey(15,ucInitKeyA,0);
	if(ret != 0)
		return -4; //非出厂卡
	ret = SMT_ReadBlock(15,2,ucBuf2);
	if(ret != 0)	
		return -5;	
	//读工作密钥扇区
	memset(ucSector,0,sizeof(ucSector));
	memcpy(ucSector,ucBuf2+14,2);
	iWorkKeyAtSectorNo=strtoul((char*)ucSector,NULL,16);
	memcpy(ucAuthKeyA,ucBuf2+8,6);
	ret = SMT_Login_With_UserKey(iWorkKeyAtSectorNo,ucAuthKeyA,0);
	if(ret != 0)
		return -6; //非出厂卡
	unsigned char ucBuf3[256]="";
	memset(ucBuf3,0,sizeof(ucBuf3));
	ret = SMT_ReadBlock(iWorkKeyAtSectorNo,iWorkKeyAtBlockNo,ucBuf3);
	if(ret != 0)	
		return -7;	
	memcpy(ucWorkKey,ucBuf3+iWorkKeyAtBlockStartPos,8);
	*flag = (short)ucBuf3[iWorkKeyAtBlockStartPos+8];
	return 0;
}


// 函数功能: 读取认证卡1
// 函数参数: ucWorkKey(种子密钥)
int __stdcall SMT_ReadAuthCard(unsigned char ucWorkKey[8])
{
	int ret;
	unsigned char ucSerialNo[5]="";
	unsigned char ucInitKeyA[6]="",ucInitKeyB[6]="";	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
		return -1;//卡片不在感应区
	}
	memcpy(ucInitKeyA,ucSerialNo,4);
	//读第7扇区
	sprintf((char*)&ucInitKeyA[4],"%02X",7);
	ret = SMT_Login_With_UserKey(7,ucInitKeyA,0);
	if(ret != 0)
		return -2; //非出厂卡
	int  iWorkKeyAtBlockNo;
	int  iWorkKeyAtBlockStartPos;
	unsigned char ucAuthKeyA[6];
//	unsigned char ucAuthKeyB[6];
	unsigned char ucBuf1[16]="";
	ret = SMT_ReadBlock(7,1,ucBuf1);
	if(ret != 0)	
		return -3;	
//	memcpy(ucAuthKeyB,ucBuf1,6);
	iWorkKeyAtBlockNo=ucBuf1[6]-'0';
	iWorkKeyAtBlockStartPos=ucBuf1[7]-'0';

	unsigned char ucBuf2[16]="";
	unsigned char ucSector[3]="";
	int iWorkKeyAtSectorNo;
	//读第15扇区
	sprintf((char*)&ucInitKeyA[4],"%02X",15);
	ret = SMT_Login_With_UserKey(15,ucInitKeyA,0);
	if(ret != 0)
		return -4; //非出厂卡
	ret = SMT_ReadBlock(15,2,ucBuf2);
	if(ret != 0)	
		return -5;	
	//读工作密钥扇区
	memset(ucSector,0,sizeof(ucSector));
	memcpy(ucSector,ucBuf2+14,2);
	iWorkKeyAtSectorNo=strtoul((char*)ucSector,NULL,16);
	memcpy(ucAuthKeyA,ucBuf2+8,6);
	/*
	{
		char szMsg[256]="";
		char keyA[17]="";
		sprintf(szMsg,"iWorkKeyAtSectorNo=%d",iWorkKeyAtSectorNo);
		::AfxMessageBox(szMsg);
		sprintf(szMsg,"iWorkKeyAtBlockNo=%d",iWorkKeyAtBlockNo);
		::AfxMessageBox(szMsg);
		sprintf(szMsg,"iWorkKeyAtBlockStartPos=%d",iWorkKeyAtBlockStartPos);
		::AfxMessageBox(szMsg);
		for(int i=0;i<6;i++)
			sprintf(&keyA[2*i],"%02X",ucAuthKeyA[i]);
		sprintf(szMsg,"ucAuthKeyA=%d",keyA);
		::AfxMessageBox(szMsg);
	}
	*/
	ret = SMT_Login_With_UserKey(iWorkKeyAtSectorNo,ucAuthKeyA,0);
	if(ret != 0)
		return -6; //非出厂卡
	unsigned char ucBuf3[256]="";
	memset(ucBuf3,0,sizeof(ucBuf3));
	ret = SMT_ReadBlock(iWorkKeyAtSectorNo,iWorkKeyAtBlockNo,ucBuf3);
	if(ret != 0)	
		return -7;	
	memcpy(ucWorkKey,ucBuf3+iWorkKeyAtBlockStartPos,8);
	return 0;
}

// 函数功能: 卡片发行
// 函数参数: 无
int __stdcall SMT_ResetCard()
{
	unsigned char ucSerialNo[5];
	unsigned char ucKeyA[6],ucKeyB[6],ucInitKeyA[6],ucInitKeyB[6];
	unsigned char ucRawData[256],ucTmpRawData[16];
	int ret;
	int i;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
	{
		MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
		return -1;//卡片不在感应区
	}
	//1 --- 计算KEYA
	SMT_Cal_KeyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	//计算KEYB
	SMT_Cal_KeyB(SMT_UCWORKINGKEY, ucSerialNo, ucKeyB);
	memset(ucRawData,0xFF,sizeof(ucRawData));
	memset(ucInitKeyA,0xFF,sizeof(ucInitKeyA));
	memset(ucInitKeyB,0,sizeof(ucInitKeyB));
//	ucRawData[6] = 0x7F;
//	ucRawData[7] = 0x07;
//	ucRawData[8] = 0x88;
//	ucRawData[9] = 0x00;

	ucRawData[6] = 0xFF;
	ucRawData[7] = 0x07;
	ucRawData[8] = 0x80;
	ucRawData[9] = 0x69;

	for(i=0;i<32;i++)
	{
		switch(1)
		{
		case 1:
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
				return -1;//卡片不在感应区
			}
			ret = SMT_Login_With_UserKey(i,ucKeyB,1);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"使用加密后KeyB登录第%d扇区失败",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用加密后KeyB写第%d扇区失败",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用加密后KeyB写第%d扇区成功",i);
					//AfxMessageBox(szMsg);

				}
			}
		case 2:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
				return -1;//卡片不在感应区
			}
			ret = SMT_Login_With_UserKey(i,ucKeyA,0);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"使用加密后KeyA登录第%d扇区失败",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用加密后KeyA写第%d扇区失败",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用加密后KeyA写第%d扇区成功",i);
					//AfxMessageBox(szMsg);
				}
			}
		case 3:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
				return -1;//卡片不在感应区
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyA,0);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"使用出厂KeyA=0xFF登录第%d扇区失败",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyA=0xFF写第%d扇区失败",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyA=0xFF写第%d扇区成功",i);
					//AfxMessageBox(szMsg);
				}
			}
		case 4:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
				return -1;//卡片不在感应区
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyA,1);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"使用出厂KeyB=0xFF登录第%d扇区失败",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyB=0xFF写第%d扇区失败",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyB=0xFF写第%d扇区成功",i);
					//AfxMessageBox(szMsg);
				}
			}
			break;
		case 5:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
				return -1;//卡片不在感应区
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyB,0);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"使用出厂KeyA=0x00登录第%d扇区失败",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用KeyA=0x00写第%d扇区失败",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyA=0x00写第%d扇区成功",i);
					//AfxMessageBox(szMsg);
				}
			}
		case 6:
			if(ret==0)
				break;
			ret = MF_ReadSeriesNo(ucSerialNo);
			if(ret < 0)
			{
				MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
				return -1;//卡片不在感应区
			}
			ret = SMT_Login_With_UserKey(i,ucInitKeyB,1);//1
			if(ret != 0)
			{
				//char szMsg[256]="";
				//sprintf(szMsg,"使用出厂KeyB=0x00登录第%d扇区失败",i);
				//AfxMessageBox(szMsg);
			}
			else
			{
				memcpy(ucTmpRawData,ucRawData,16);
				ret = SMT_WriteBlock(i,3,ucTmpRawData);
				if(ret != 0)
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyB=0x00写第%d扇区失败",i);
					//AfxMessageBox(szMsg);
				}
				else
				{
					//char szMsg[256]="";
					//sprintf(szMsg,"使用出厂KeyB=0x00写第%d扇区成功",i);
					//AfxMessageBox(szMsg);
				}
			}
			break;
		default:
			break;
		}
		ret = MF_ReadSeriesNo(ucSerialNo);
		if(ret < 0)
		{
			MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
			return -1;//卡片不在感应区
		}
		ret = SMT_Login_With_UserKey(i,ucInitKeyA,0);
		if(ret != 0)
		{
			char szMsg[256]="";
			sprintf(szMsg,"初始化第%d扇区成功后重新登录失败",i);
			MessageBox(NULL, szMsg, NULL, MB_OK);
			return -7; //非出厂卡
		}
		else
		{
			//char szMsg[256]="";
			//sprintf(szMsg,"初始化第%d扇区成功",i);
			//AfxMessageBox(szMsg);
		}
	}
	return 0;
}


// 函数功能: 重新设置钱包信息
// 函数参数: 钱包号
int __stdcall SMT_ResetPacketInfo(int nPacketNo)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:登录3扇区失败",__FILE__,__LINE__,ret);		
		return ret;
	}
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读3扇区失败",__FILE__,__LINE__,ret);	
		return -5;
	}
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
	{
		SetLastErrMsg(1,"File:%s\nLine:%d\nError:%d\nMessage:钱包%d未开通",__FILE__,__LINE__,ret,nPacketNo);		
		return 1; //钱包不允许使用
	}
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:登陆第%d扇区失败",__FILE__,__LINE__,ret,sector);	
		return ret;
	}
	unsigned char ucBuf1[16];

	memset(ucBuf1,0,sizeof(ucBuf1));
	ret = SMT_WriteBlock(sector,0,ucBuf1);
	if(ret != 0)	
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:写第%d扇区第0块失败",__FILE__,__LINE__,ret,sector);	
		return -8;
	}
	memset(ucBuf1,0,sizeof(ucBuf1));
	ret = SMT_WriteBlock(sector,2,ucBuf1);
	if(ret != 0)	
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:写第%d扇区备份块失败",__FILE__,__LINE__,ret,sector);	
		return -8;
	}
	return 0;
}

// 函数功能: 获得钱包信息
// 函数参数: nPacketNo(钱包号), pPcakInfo(钱包信息指针)
int __stdcall SMT_GetPacketInfo(int nPacketNo, MONEY_PACK_INFO *pPackInfo)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)	
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:登录3扇区失败",__FILE__,__LINE__,ret);
		return ret;
	}
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读3扇区失败",__FILE__,__LINE__,ret);	
		return -5;
	}
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
	{
		SetLastErrMsg(1,"File:%s\nLine:%d\nError:%d\nMessage:钱包%d未开通",__FILE__,__LINE__,ret,nPacketNo);	
		return 1; //钱包不允许使用
	}
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:登陆第%d扇区失败",__FILE__,__LINE__,ret,sector);	
		return ret;
	}

	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区失败",__FILE__,__LINE__,ret,sector);	
		return -5;
	}
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		pPackInfo->bala = ucBuf1[0]+ucBuf1[1]*256+ucBuf1[2]*256*256;
		pPackInfo->total_cnt   = ucBuf1[3]*256+ucBuf1[4];
		pPackInfo->date    = (ucBuf1[5]+2000)*10000+ucBuf1[6]*100+ucBuf1[7];
		pPackInfo->time    = ucBuf1[8]*100+ucBuf1[9];
		pPackInfo->daybala =ucBuf1[10]+ucBuf1[11]*256+ucBuf1[12]*256*256;
		pPackInfo->time_cnt=ucBuf1[0X0D];
		pPackInfo->day_cnt=ucBuf1[0X0E];
		return 0;
	}
	else
	{
		SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区校验和错误,开始读备份扇区",__FILE__,__LINE__,0,sector);	
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)
		{
			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区失败",__FILE__,__LINE__,ret,sector);	
			return -5;
		}
		ucCheck = 0;
		for(i=0;i<15;i++)
			ucCheck+=ucBuf2[i];
		if(ucCheck == ucBuf2[15])
		{
			pPackInfo->bala = ucBuf2[0]+ucBuf2[1]*256+ucBuf2[2]*256*256;
			pPackInfo->total_cnt   = ucBuf2[3]*256+ucBuf2[4];
			pPackInfo->date    = (ucBuf2[5]+2000)*10000+ucBuf2[6]*100+ucBuf2[7];
			pPackInfo->time    = ucBuf2[8]*100+ucBuf2[9];
			pPackInfo->daybala =ucBuf2[10]+ucBuf2[11]*256+ucBuf2[12]*256*256;
			pPackInfo->time_cnt=ucBuf2[0X0D];
			pPackInfo->day_cnt=ucBuf2[0X0E];
			return 0;
		}
		else
		{
			SetLastErrMsg(ret,"File:%s\nLine:%d\nError:%d\nMessage:读第%d扇区备份块校验和错误",__FILE__,__LINE__,ret,sector);	
			return 2;
		}
	}
	return 2;
}


// 函数功能: 设置钱包信息
// 函数参数: nPacketNo(钱包号), pPackInfo(钱包信息指针)
int __stdcall SMT_SetPacketInfo(int nPacketNo,MONEY_PACK_INFO *pPackInfo)
{
	int ret,sector;
	unsigned char ucBuffer[16];
	if(nPacketNo<1)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)
	{
		return ret;
	}
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)
	{
		return -5;
	}
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
	{
		return 1; //钱包不允许使用
	}
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
	{
		return ret;
	}
	unsigned char ucBuf1[16],ucBuf2[16],ucBufTmp[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)
	{
		return -6;
	}
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;
		if(pPackInfo->bala>=0)
		{
			i = pPackInfo->bala;
			ucBuf1[0] = i%256;
			ucBuf1[1] = i/256;
			ucBuf1[2] = i/256/256;
		}
		if(pPackInfo->total_cnt>=0)
		{
			i = pPackInfo->total_cnt;
			ucBuf1[3] = i/256;
			ucBuf1[4] = i%256;
		}
		/*
		 *	date: -1 则不修改,0-修改为系统时间,>0-修改为传入时间
		 */
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		if(0==pPackInfo->date)
		{
			ucBuf1[5] = (BYTE)(tm.wYear - 2000); // tm.GetYear()-2000;
			ucBuf1[6] = (BYTE)(tm.wMonth);		 // tm.GetMonth();
			ucBuf1[7] = (BYTE)(tm.wDay);		 // tm.GetDay();
		}
		else if(pPackInfo->date>20000000&&pPackInfo->date<30000000)
		{
			int day  = pPackInfo->date%100;
			int mon  = pPackInfo->date/100%100;
			int year = pPackInfo->date/10000%100;
		
			ucBuf1[5] = year;
			ucBuf1[6] = mon;
			ucBuf1[7] = day;
		}
		if(0==pPackInfo->time)
		{
			ucBuf1[8] = (BYTE)tm.wHour;			 // tm.GetHour();
			ucBuf1[9] = (BYTE)tm.wMinute;		 // tm.GetMinute();
		}
		else if(pPackInfo->time>0)
		{
			int hour=pPackInfo->time/100;
			int minute=pPackInfo->time%100;
			ucBuf1[8] = hour;
			ucBuf1[9] = minute;
		}
		if(pPackInfo->daybala>=0)
		{
			i = pPackInfo->daybala;
			ucBuf1[10] = i%256;
			ucBuf1[11] = i/256;
			ucBuf1[12] = i/256/256;
		}
		ucBuf1[15]=0;
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
		return 0;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		if(pPackInfo->bala>=0)
		{
			i = pPackInfo->bala;
			ucBuf2[0] = i%256;
			ucBuf2[1] = i/256;
			ucBuf2[2] = i/256/256;
		}
		if(pPackInfo->total_cnt>=0)
		{
			i = pPackInfo->total_cnt;
			ucBuf2[3] = i/256;
			ucBuf2[4] = i%256;
		}
		/*
		 *	date: -1 则不修改,0-修改为系统时间,>0-修改为传入时间
		 */
//		CTime tm = CTime::GetCurrentTime();
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		if(0==pPackInfo->date)
		{
			ucBuf2[5] = (BYTE)tm.wYear;					// tm.GetYear()-2000;
			ucBuf2[6] = (BYTE)tm.wMonth;				// tm.GetMonth();
			ucBuf2[7] = (BYTE)tm.wDay;					// tm.GetDay();
		}
		else if(pPackInfo->date>20000000 && pPackInfo->date<30000000)
		{
			int day  = pPackInfo->date%100;
			int mon  = pPackInfo->date/100%100;
			int year = pPackInfo->date/10000%100;
			
			ucBuf2[5] = year;
			ucBuf2[6] = mon;
			ucBuf2[7] = day;
		}
		if(0==pPackInfo->time)
		{
			ucBuf2[8] = (BYTE)tm.wHour;					// tm.GetHour();
			ucBuf2[9] = (BYTE)tm.wMinute;				// tm.GetMinute();
		}
		else if(pPackInfo->time>0)
		{
			int hour=pPackInfo->time/100;
			int minute=pPackInfo->time%100;
		
			ucBuf2[8] = hour;
			ucBuf2[9] = minute;
		}
		if(pPackInfo->daybala>=0)
		{
			i = pPackInfo->daybala;
			ucBuf2[10] = i%256;
			ucBuf2[11] = i/256;
			ucBuf2[12] = i/256/256;
		}
		ucBuf2[15]=0;
		for(i=0;i<15;i++)	
			ucBuf2[15] += ucBuf2[i];

		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if(ret != 0)	
			return -12;
	}
	return 0;
}

// 函数功能: 设置交易次数
// 函数参数: nPacketNo(钱包号), tx_cnt(交易次数计数)
int __stdcall SMT_SetTxCnt(int nPacketNo,int tx_cnt)
{
	int ret,sector;
	unsigned char ucBuffer[16]="";
	if(nPacketNo<1)
		return -1;
	if(tx_cnt<0)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)
	{
		return ret;
	}
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)
	{
		return -5;
	}
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
	{
		return 1; //钱包不允许使用
	}
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	
	ret = Login_Card(sector);
	if(ret != 0)
	{
		return ret;
	}
	unsigned char ucBuf1[16]="";
	unsigned char ucBuf2[16]="";
	unsigned char ucBufTmp[16]="";
	unsigned char ucCheck=0;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)
	{
		return -6;
	}
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;
		ucBuf1[3] = tx_cnt/256;
		ucBuf1[4] = tx_cnt%256;
		ucBuf1[15]=0;
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		ucBuf2[3] = tx_cnt/256;
		ucBuf2[4] = tx_cnt%256;
		ucBuf2[15]=0;
		for(i=0;i<15;i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if(ret != 0)	
			return -10;
	}
	return 0;
}

// 读取黑名单列表版本
int __stdcall SMT_ReadBlackNameListVersion(int *flag,char *version)
{
	int ret;
	unsigned char ucBuffer[16]="";
	char sVersion[13]="";
	ret = Login_Card(3);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(3,2,ucBuffer);
	if(ret != 0)	
		return -6;
	if(0==ucBuffer[0])
		*flag=1;
	else
		*flag=0;
	dec2hex(ucBuffer + 1, 6, sVersion);
	strcpy(version, sVersion);
	return 0;
}

// 读取钱包余额
int __stdcall ReadBalance(int nPacketNo,int nBalance[1],int nCnt[1])
{
	char line[10]="";
	int ret,sector;
	unsigned char ucBuffer[16];
	ret = Login_Card(3);
	if(ret != 0)
		return ret;

	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)
		return ret;
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
	{
		return 1; //钱包不允许使用
	}
	sector = ucBuffer[(nPacketNo-1)*2+1]; //钱包所在扇区
	if(sector<4)
	{
		return -1;
	}
	ret = Login_Card(sector);
	if(ret != 0)	
		return ret;
	unsigned char ucBuf1[16],ucBuf2[16];
	unsigned char ucCheck;
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)
		return ret;
	int i;
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		nBalance[0] = ucBuf1[0]+ucBuf1[1]*256+ucBuf1[2]*256*256;
		nCnt[0]=ucBuf1[3]*256+ucBuf1[4];
	}
	else 
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return ret;
		ucCheck = 0;
		for(i=0;i<15;i++)
			ucCheck+=ucBuf2[i];
		if(ucCheck == ucBuf2[15])
		{
			nBalance[0] = ucBuf2[0]+ucBuf2[1]*256+ucBuf2[2]*256*256;
			nCnt[0]=ucBuf2[3]*256+ucBuf2[4];
			return 0;
		}
		else
		{
			return 2;
		}
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////
//	初始化卡程序
//  2006-8-14
///////////////////////////////////////////////////////////////////////////

static BOOL Is_Com_open()
{
	return com_is_open;
}

static BOOL Read_Author_Key()
{
	if( TRUE == has_read_main_key)
	{
		return TRUE;
	}
	if( SMT_ReadAuthCard2(SMT_UCWORKINGKEY,&AUTH_CARD_FLAG) == 0 )
	{
		has_read_main_key = TRUE;
		SMT_AutoDll(SMT_UCWORKINGKEY);
		SMT_ControlBuzzer();
		return TRUE;
	}
	return FALSE;
}

/** 
 * @brief 使用密钥登录卡扇区
 * 
 * @param sect - 要登录的扇区
 * @param key - 登录密钥
 * @param flag - 密钥是KEY-A还是KEY-B
 * @param card_type - 卡类型
 * 
 * @return - 成功返回0，失败返回-1
 */
static int LoginCardSect(long sect,BYTE * key,long flag,BYTE * card_type)
{
	//char msg[500] = "";
	BYTE tmp_card_id[5] = "";
	BYTE tmp_card_type[2] = "";
	// 如果上次登录不成功，就需要重新检测一下卡，才能继续登录
	static bool lastLoginSuccess = false;
	
	assert(sect >= 0 || sect < smart_card_sect_no);

//	if( !lastLoginSuccess )
//	{
	if (SMT_RequestCardExist(tmp_card_id,tmp_card_type) !=0)
	{
		return -1;
	}
//	}
	if( SMT_Login_With_UserKey(sect,key,flag) == 0 )
	{
		// 登录成功
		lastLoginSuccess = true;
		//printf("Login card sect[%d] key [%s]",sect,key);
		//TRACE0(msg);
		return 0;
	}
	// 登录失败
	lastLoginSuccess = false;
	return -1;
}

static int WriteCardBlock(int *err_code,PWriteDataFunc pFunc,LPProcessCallBack lpCallBack)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[7] = "";
	BYTE card_key_b[7] = "";
	BYTE card_key_c[] = {0x56, 0xDD, 0xA9, 0x59, 0xDD, 0xF0};

	int current_key, old_key;
	int ret;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[6];			// 3 改为 4
	
	int sect = 0;
	// 判断打开串口
	if (!Is_Com_open())
	{
		*err_code = E_COM_NOT_OPEN;
		return -1;
	}
	// 读取授权密钥
	if( FALSE == Read_Author_Key())
	{
		*err_code = E_MAIN_KEY_ERROR;
		return -1;
	}
	// 检查卡是否存在
	if ( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		*err_code = E_READ_CARD_ERROR;
		return -1;
	}

	// 计算卡的 keyA , keyB
	if( gen_user_card_keyA(SMT_UCWORKINGKEY,card_id
			,card_key_a) != 0 )
	{
		*err_code = E_GEN_CARD_KEY_A_ERROR;
		return -1;
	}
	if( gen_user_card_keyB(SMT_UCWORKINGKEY,card_id
			,card_key_b) != 0 )
	{
		*err_code = E_GEN_CARD_KEY_B_ERROR;
		return -1;
	}
	// 初始化 key 的数组
	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	// 这里位置可以作为初始化卡时候的修改过的KEYA
	memcpy(card_key[0].key,CARD_INIT_KEY,sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key,card_key_a,sizeof(card_key_a));

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key,card_key_b,sizeof(card_key_b));
	
	//重新添加一个KEYC
 	card_key[3].flag = CARD_KEY_C;
	memcpy(card_key[3].key, card_key_c, sizeof(card_key_c));
	
	// 再读一次卡检查一下卡 ID
	BYTE card_id_2[5] = "";
	SMT_RequestCardExist(card_id_2,card_type);
	if( memcmp(card_id,card_id_2,4) != 0)
	{
		* err_code = E_READ_CARD_ERROR;
		return -1;
	}
	// 保存可以登录的 key 有索引
	current_key = 0;
//	current_key = 1;					 // 修改过, 用完了还得返回去, 用keyA登陆 
	for(sect = 0;sect < smart_card_sect_no; ++sect)
	{
		if (0 == sect)
		{
			memcpy(card_key[1].key, LOGIN_AREA_KEY, sizeof(card_key[1].key));
			memcpy(card_key[2].key, card_key_b, sizeof(card_key[2].key));
		}
		else
		{
			memcpy(card_key[1].key, card_key_a, sizeof(card_key[1].key));
			memcpy(card_key[2].key, card_key_b, sizeof(card_key[2].key));	
		}
		// 调用回调函数
		if( lpCallBack != NULL )
			lpCallBack(sect);
		// 依次初始化每个扇区
		old_key = current_key;
		login_sect_succ = FALSE;
		// 查找可以登录的 key 
		while(TRUE)
		{
			// 如果登录成功 跳出循环
			if( LoginCardSect(sect,card_key[current_key].key
				,card_key[current_key].flag,card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key--;
			if( current_key < 0 )
				current_key = 3;			// 这里原来是2, 现在改为3
			if (current_key == old_key)
				break;
		}
		// 判断当前扇区是否成功登录
		if (login_sect_succ == FALSE)
		{
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
		// 调用写卡回调函数
		if( pFunc != NULL )
		{
			if( (ret = pFunc(sect,&card_key[1],&card_key[2],card_type,
				&card_key[current_key])) != 0)
			{
				// 写卡不成功
				*err_code = E_CARD_WRITE_ERROR;
				return ret;
			}
		}
	}
	return 0;
}

static int WriteCardData(long sect,long block,BYTE * buf)
{
	assert(buf != NULL);
	return SMT_WriteBlock(sect,block,buf);
}

static int WriteInitNewCardData(long sect,CardKeyData * keya,CardKeyData *keyb
								,BYTE * card_type,CardKeyData * login_key)
{
	BYTE sect_data[17] = "";
	// 初始化写入的数据位
	memset(sect_data,0,sizeof(sect_data));
	// key A
	memcpy(sect_data,keya->key,CARD_KEY_LEN);
	// control bit
//	memcpy(sect_data+CARD_KEY_LEN,CARD_NEW_CTRL_BIT,sizeof(CARD_NEW_CTRL_BIT));
	
	if ((0 == sect) && (card_type[2] != 0x10))
		memcpy(sect_data+CARD_KEY_LEN, CARD_FOR14_CTRL_BIT, sizeof(CARD_FOR14_CTRL_BIT));
	else
		memcpy(sect_data+CARD_KEY_LEN, CARD_NEW_CTRL_BIT, sizeof(CARD_NEW_CTRL_BIT));
//		memcpy(sect_data+CARD_KEY_LEN+sizeof(CARD_NEW_CTRL_BIT),keyb->key,CARD_KEY_LEN);
	
	// key B
	memcpy(sect_data+CARD_KEY_LEN+sizeof(CARD_NEW_CTRL_BIT),keyb->key,CARD_KEY_LEN);

	if (0 == WriteCardData(sect,PASSWD_BLOCK_NUM,sect_data))
	{
		return 0;
	}
	return -1;
}

int __stdcall InitNewCard(int * err_code,const char* showcardno
								   ,LPProcessCallBack lpCallBack)
{
	int ret = 0;
	if((ret = WriteCardBlock(err_code,WriteInitNewCardData,lpCallBack)) != 0)
	{
		//*err_code = E_CARD_WRITE_ERROR;
		return ret;
	}
	
	if(showcardno != NULL)
	{
		// 计算BCD码
		int card_len = strlen(showcardno);
		unsigned char bcdshowcard[5] = "";
		memset(bcdshowcard,0xFF,sizeof bcdshowcard);
		int len = card_len - card_len % 2;
		int i;
		for(i = 0;i < len;i+=2)
		{
			bcdshowcard[i/2] = (((showcardno[i] - '0') << 4) & 0xF0)
				| ((showcardno[i+1] - '0') & 0x0F);
		}
		if(card_len > len)
		{
			bcdshowcard[i/2] = (((showcardno[i] - '0') << 4) & 0xF0) | 0x0F;
		}
		// 写显示卡号
		if(SMT_ChangeShowCardNo(bcdshowcard) != 0)
		{
			return -1;
		}
	}
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall ReadCardMainKey(BYTE * main_key,short wantFlag,
									   short * readFlag)
{
	int ret = -1;
	if( NULL == readFlag )
	{
		return -1;
	}
	if( TRUE == has_read_main_key 
		&& (AUTH_CARD_FLAG == wantFlag || -1 == wantFlag ))
	{
		return 0;
	}
	unsigned char work_key[9] = "";
	if( SMT_ReadAuthCard2(work_key,&AUTH_CARD_FLAG) == 0 )
	{
		if(AUTH_CARD_FLAG == wantFlag || -1 == wantFlag)
		{
			has_read_main_key = TRUE;
			ret = 0;
			SMT_AutoDll(work_key);
			SMT_ControlBuzzer();
			memcpy(main_key,work_key,sizeof(main_key));
			*readFlag = AUTH_CARD_FLAG;
		}
	}
	return ret;
}

int __stdcall ReadCardMainKey2(short wantFlag)
{
	int ret = -1;

	if (TRUE == has_read_main_key && 
		(AUTH_CARD_FLAG == wantFlag || -1 == wantFlag)
		)
	{
		return 0;
	}

	unsigned char work_key[9] = "";
	if (SMT_ReadAuthCard2(work_key, &AUTH_CARD_FLAG) == 0)
	{
		if(AUTH_CARD_FLAG == wantFlag || -1 == wantFlag)
		{
			has_read_main_key = TRUE;
			ret = 0;
			SMT_AutoDll(work_key);
			SMT_ControlBuzzer();
		}
	}

	return ret;
}

int __stdcall ReadCardPhyID(BYTE card_id[4],BYTE card_type[2])
{
	return SMT_RequestCardExist(card_id,card_type);
}

/** 
 * @brief 回收卡的回调函数
 * 
 * @param sect - 扇区号
 * @param keya - KEYA
 * @param keyb - KEYB
 * @param card_type - 卡类型
 * @param login_key - 登录密钥
 * 
 * @return - 成功返回0，失败返回-1
 */
static int WriteRefineCardData(long sect,CardKeyData * keya,CardKeyData * keyb
							   ,BYTE * card_type,CardKeyData * login_key)
{	
	BYTE sect_data[17] = "";
	int ret = 0;
	// 初始化写入的数据位
	memset(sect_data,0,sizeof(sect_data));
	// key A, 这里可以在回收的时候写入KEYA
	memcpy(sect_data,CARD_INIT_KEY,CARD_KEY_LEN);
	// control bit
	memcpy(sect_data+CARD_KEY_LEN,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
	// key B
	memcpy(sect_data+CARD_KEY_LEN+sizeof(CARD_INIT_CTRL_BIT),CARD_INIT_KEY,CARD_KEY_LEN);

	return 	WriteCardData(sect,PASSWD_BLOCK_NUM,sect_data);
}

int __stdcall RefineCard(int *err_code, LPProcessCallBack lpFunc)
{
	if(SMT_ClearCard() != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
	}

	if(WriteCardBlock(err_code, WriteRefineCardData, lpFunc) != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

int __stdcall ReadCardBlock(int startSect,int endSect
									 ,short block,LPGetBlockData lpFunc)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[7] = "";
	BYTE card_key_b[7] = "";
	
	BYTE buf[16] = "";
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[6];
	
	int sect = 0;
	// 判断打开串口
	if (!Is_Com_open())
	{
		return -1;
	}
	// 读取授权密钥
	if( FALSE == Read_Author_Key())
	{
		return -1;
	}
	// 检查卡是否存在
	if ( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		return -1;
	}

	// 计算卡的 keyA , keyB
	if( gen_user_card_keyA(SMT_UCWORKINGKEY,card_id
			,card_key_a) != 0 )
	{
		return -1;
	}
	if( gen_user_card_keyB(SMT_UCWORKINGKEY,card_id
			,card_key_b) != 0 )
	{
		return -1;
	}
	// 初始化 key 的数组
	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	// 这里可以读出回收后的KEYA
	memcpy(card_key[0].key,CARD_INIT_KEY,sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key,card_key_a,sizeof(card_key_a));

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key,card_key_b,sizeof(card_key_b));
	
	// 保存可以登录的 key 有索引
	current_key = 1;
	for(sect = startSect;sect < endSect + 1; ++sect)
	{
		if (0 == sect)
		{
			memcpy(card_key[1].key, LOGIN_AREA_KEY, sizeof(card_key[1].key));
			memcpy(card_key[2].key, card_key_b, sizeof(card_key[2].key));
		}
		else
		{
			memcpy(card_key[1].key, card_key_a, sizeof(card_key[1].key));
			memcpy(card_key[2].key, card_key_b, sizeof(card_key[2].key));	
		}
		// 依次初始化每个扇区
		old_key = current_key;
		login_sect_succ = FALSE;
		// 查找可以登录的 key 
		while(TRUE)
		{
			// 如果登录成功 跳出循环
			if( LoginCardSect(sect,card_key[current_key].key
				,card_key[current_key].flag,card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key > 2 )
				current_key = 0;
			if (current_key == old_key)
				break;
		}
		// 判断当前扇区是否成功登录
		if (login_sect_succ == FALSE)
		{
			return -1;
		}
		// 读取卡扇区数据
		for(int b = 0;b < 4;++b)
		{
			if(block & (1 << b))
			{
				memset(buf,0,sizeof(buf));
				if(SMT_ReadBlock(sect,b,buf) != 0)
				{
					return -1;
				}
				// 调用读卡回调函数
				if( lpFunc != NULL )
				{
					lpFunc(sect,b,buf,
						card_key[current_key].key,
						card_key[current_key].flag);	
				}
			}
		}
		
	}
	return 0;
}

int __stdcall ResetAuthCard(int * err_code,LPProcessCallBack lpCallBack)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	BYTE tmpBuf[17] = "";
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	BYTE tmpSect[3] = "";
	char tmp[3] = "";
	short priBlock,priStartPos,priSect;
	unsigned short sect;

	if( !Is_Com_open() )
	{
		* err_code = E_COM_NOT_OPEN;
		return -1;
	}

	if(SMT_RequestCardExist(card_id,card_type) != 0)
	{
		* err_code = E_READ_CARD_ID_ERROR;
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// 读取 7 扇区
	sect = 7;
	memset(card_key,0,sizeof(card_key));
	memcpy(card_key,card_id,sizeof(card_id));
	// 卡 ID 为 4 位
	sprintf((char*)card_key + 4,"%02X",sect);
	//memcpy(card_key+4,((char*)&sect)+1,1);
	//memcpy(card_key+5,((char*)&sect),1);
	
	// 读取 Key B
	if( LoginCardSect(sect,card_key,CARD_KEY_A,card_type) != 0)
	{
		//AfxMessageBox("登录扇区失败！");
		MessageBox(NULL, "登录扇区失败！", "", NULL);
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect,1,buf) != 0)
	{
		//AfxMessageBox("读取扇区失败！");
		MessageBox(NULL, "读取扇区失败！", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key b
	memcpy(priKeyB,buf,CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if( priBlock < 0 || priBlock > 2)
	{
		//AfxMessageBox("数据不合法！");
		MessageBox(NULL, "数据不合法！", "", NULL);
		* err_code = E_INVALID_CARD;
		return -3;
	}
	// start pos
	// priStartPos = char2int((const char*)&buf[7],1,true);
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp,NULL,16);
	if( priStartPos < 0 || priStartPos > 10)
	{
		//AfxMessageBox("数据不合法！");
		MessageBox(NULL, "数据不合法！", "", NULL);
		* err_code = E_INVALID_CARD;
		return -3;
	}
	
	//////////////////////////////////////////////////////////////////////////
	// 读 15 扇区
	sect = 15;
	memset(card_key,0,sizeof(card_key));
	memcpy(card_key,card_id,sizeof(card_id));
	// 卡 ID 为 4 位
	sprintf((char*)card_key + 4,"%02X",sect);
	// 读取 Key a
	if( LoginCardSect(sect,card_key,CARD_KEY_A,card_type) != 0)
	{
		//AfxMessageBox("登录扇区失败！");
		MessageBox(NULL, "登录扇区失败！", "", NULL);
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect,2,buf) != 0)
	{
		//AfxMessageBox("读取扇区失败！");
		MessageBox(NULL, "读取扇区失败！", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key a
	strncpy((char*)priKeyA,(char*)buf+8,CARD_KEY_LEN);
	// private key section no
	priSect = (short)strtoul((char*)buf+14,NULL,16);
	//////////////////////////////////////////////////////////////////////////
	// 生成初始状态
	memset((char*)buf,255,sizeof(buf) - 1);
	strncpy((char*)buf + sizeof(CARD_INIT_KEY),(char*)CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));

	if(lpCallBack)
		lpCallBack(0);
	bool isClear = false;
	// 回收密钥扇区
	if(LoginCardSect(priSect,priKeyA,CARD_KEY_A,card_type) == 0)
	{
		memset(tmpBuf,0,sizeof(tmpBuf));
		
		if(SMT_WriteBlock(priSect,priBlock,tmpBuf) != 0)
		{
			isClear = false;
			goto L_TRY_KEY_B;
		}
		// 写控制位扇区
		strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
		if(SMT_WriteBlock(priSect,3,tmpBuf) != 0)
		{
			// 写卡失败，使用Key B 重试
			isClear = false;
		}
		else
			isClear = true;
		
	}
L_TRY_KEY_B:
	if(lpCallBack)
		lpCallBack(0);
	if(!isClear)
	{
		// 用 key B 测试
		if(LoginCardSect(priSect,priKeyB,CARD_KEY_B,card_type) == 0)
		{
			memset(tmpBuf,0,sizeof(tmpBuf));
			
			if(SMT_WriteBlock(priSect,priBlock,tmpBuf) != 0)
			{
			//	AfxMessageBox("写扇区数据失败！");
				MessageBox(NULL, "写扇区数据失败！", "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// 写控制位扇区
			strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
			if(SMT_WriteBlock(priSect,3,tmpBuf) != 0)
			{
				// key B 也无法写。
				//AfxMessageBox("写扇区数据失败！");
				MessageBox(NULL, "写扇区数据失败！", "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			
		}
		else
		{
			// 无法用 key b 登录，
		//	AfxMessageBox("登录扇区失败！");
			MessageBox(NULL, "登录扇区失败！", "", NULL);
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
	}

	// 测试是否回收成功
	if( LoginCardSect(priSect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
	{
		//AfxMessageBox("回收扇区失败！");
		MessageBox(NULL, "回收扇区失败！", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	char msg[128] = "";
	// 回收其它扇区
	for(sect = 0;sect < AUTH_CARD_SECT_NO;++sect)
	{
		if(lpCallBack)
			lpCallBack(0);
		// 密钥扇区不用初始化
		if( sect == priSect)
			continue;
		memset(card_key,0,sizeof(card_key));
		memcpy(card_key,card_id,sizeof(card_id));
		// 卡 ID 为 4 位
		sprintf((char*)(card_key+4),"%02X",sect);
		
		if( LoginCardSect(sect,card_key
				,CARD_KEY_A,card_type) == 0)
		{
			strncpy((char*)tmpBuf,(char*)buf,sizeof(tmpBuf));
			// 登录成功
			// 回收控制位
			if( SMT_WriteBlock(sect,3,tmpBuf) != 0)
			{
				sprintf(msg,"回收[%d]扇区失败！",sect);
				//AfxMessageBox(msg);
				MessageBox(NULL, msg, "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// 用Key A 登录测试
			if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
			{
				sprintf(msg,"测试登录%d扇区失败！",sect);
			//	AfxMessageBox(msg);
				MessageBox(NULL, msg, "", NULL);
				* err_code = E_CARD_LOGIN_ERROR;
				return -1;
			}
		}
		else if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) == 0)
		{
			// 使用 初始化 密钥进行登录测试
			sprintf(msg,"扇区%d使用初始密钥登录成功。\n是否继续回收？",sect);
		//	if(AfxMessageBox(msg,MB_OKCANCEL) == IDCANCEL)
			if (MessageBox(NULL, msg, "", MB_OKCANCEL) == IDCANCEL)
			{
				// 如果不继续回收,则返回
				* err_code = E_CARD_LOGIN_ERROR;
				return -2;
			}
		}
		else
		{
			sprintf(msg,"登录卡第%d扇区失败",sect);
			//AfxMessageBox(msg);
			MessageBox(NULL, msg, "", NULL);
			* err_code = E_CARD_LOGIN_ERROR;
			return -2;
		}
	}
	return 0;
}

/** 
 * @brief 库接口函数，重新读取授权卡
 * 
 * @return - 成功返回0，失败返回-1
 */

int __stdcall ResetMainKey()
{
//	if( ReaderAuthor((char *)CARD_MAIN_KEY) == 0 )
	if( ReaderAuthor(CARD_MAIN_KEY) == 0 )	
	{
		SMT_AutoDll(CARD_MAIN_KEY);
		has_read_main_key = TRUE;
		return TRUE;
	}
	return FALSE;
}

/** 
 * @brief 初始化授权卡的每个扇区密钥, 上海理工
 * 
 * @param card_id - 卡物理ID号
 * @param card_type - 卡类型
 * @param lpCallBack - 回调函数，处理卡时调用 ，可以为NULL
 * 
 * @return - 成功返回0，失败返回-1
 */
static int NewAuthCard_Init_Sect(BYTE card_id[4],BYTE card_type[2],
								 LPProcessCallBack lpCallBack)
{
	int sect;
	char msg[256] = "";
	BYTE buf[16] = "";
	BYTE card_key[7] = "";
	memcpy(card_key,card_id,sizeof(card_id));
	// 读取一次卡,以免用户同时放多张卡
	for(sect = 0;sect < AUTH_CARD_SECT_NO;++sect)
	{
		if(lpCallBack)
			lpCallBack(sect);
		// 一定要使用大写
		sprintf((char*)card_key+4,"%02X",sect);

		//////////////////////////////////////////////////////////////////////////
		if( LoginCardSect(sect,CARD_INIT_KEY,CARD_KEY_A,card_type) != 0)
		{
			if(LoginCardSect(sect,card_key,CARD_KEY_B,card_type) != 0)
			{
				sprintf(msg,"登录卡第%d扇区失败",sect);
				MessageBox(NULL, msg, NULL, NULL);
				return -1;
			}
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////
		memcpy(buf,card_key,sizeof(card_key));
		memcpy(buf+6,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
		memcpy(buf+10,card_key,sizeof(card_key));
		// 写扇区信息
		SMT_WriteBlock(sect,3,buf);
		/*
		{
			sprintf(msg,"初始化第%d扇区失败",sect);
			AfxMessageBox(msg);
			return -1;
		}
		*/
		if( LoginCardSect(sect,card_key,CARD_KEY_A,card_key) != 0)
		{
			sprintf(msg,"测试第%d扇区登录失败!\n写卡第%d扇区密钥失败!"
				,sect,sect);
			MessageBox(NULL, msg, NULL, NULL);
			return -1;
		}
		//////////////////////////////////////////////////////////////////////////
	}
	return 0;
}

/** 
 * @brief 初始化授权卡的每个扇区密钥, 上大
 * 
 * @param card_id - 卡物理ID号
 * @param card_type - 卡类型
 * @param lpCallBack - 回调函数，处理卡时调用 ，可以为NULL
 * 
 * @return - 成功返回0，失败返回-1
 */
static int NewAuthCard_Init_Sect(BYTE card_id[4],BYTE card_type[2],
								 LPProcessCallBack lpCallBack, int pri_sect)
{
	int sect;
	int nWorkKeySector = 0;
	int ret = 0;
	char msg[256] = "";
	BYTE buf[17] = "";
	BYTE card_key[7] = "";
	memcpy(card_key,card_id,sizeof(card_id));
	// 读取一次卡,以免用户同时放多张卡
	for(sect = 0;sect < AUTH_CARD_SECT_NO;++sect)
	{
		if(lpCallBack)
			lpCallBack(sect);
		// 一定要使用大写
		sprintf((char*)card_key+4,"%02X",sect);

		//////////////////////////////////////////////////////////////////////////
		if(LoginCardSect(sect, CARD_INIT_KEY, CARD_KEY_A, card_type) != 0)
		{
			if(LoginCardSect(sect, card_key, CARD_KEY_B, card_type) != 0)
			{	// 产生一个补救的机会, 如果7扇区或者15扇区坏掉了卡就废掉了, 补写7扇区和15扇区
				if (sect == pri_sect)
				{
					if (SMT_LoginWorkKeySector(NULL, NULL, NULL, NULL))
					{
						ret = 10;		// 产生补救的机会 
					}
					else
					{
						ret = 11;		// 已经初始化过了
					}
					continue ;
				}
				else
				{
					sprintf(msg,"登录卡第%d扇区失败",sect);
					MessageBox(NULL, msg, NULL, NULL);
					return -1;	
				}	
			}
			else
			{
				continue ; 
			}
		}
		//////////////////////////////////////////////////////////////////////////
		memcpy(buf,card_key,sizeof(card_key));
		memcpy(buf+6,CARD_INIT_CTRL_BIT,sizeof(CARD_INIT_CTRL_BIT));
		memcpy(buf+10,card_key,sizeof(card_key));
		// 写扇区信息
		SMT_WriteBlock(sect, 3, buf);
		/*
		if ( LoginCardSect(sect,card_key,CARD_KEY_A,card_key) != 0 )
		{
			sprintf(msg,"测试第%d扇区登录失败!\n写卡第%d扇区密钥失败!"
				,sect,sect);
			MessageBox(NULL, msg, NULL, NULL);
			return -1;
		}
		*/
		if (LoginCardSect(sect,card_key,CARD_KEY_A,card_type) != 0)
		{
			// 登陆了工作密钥扇区
			if (!SMT_LoginWorkKeySector(NULL, NULL, NULL, NULL))
			{
				sprintf(msg,"测试第%d扇区登录失败!\n写卡第%d扇区密钥失败!"
					,sect,sect);
				MessageBox(NULL, msg, NULL, NULL);
				return -1;
			}
		}
		//////////////////////////////////////////////////////////////////////////
	}
	return ret;
}

/** 
 * @brief 计算授权卡CRC校验值
 * 
 * @param keya - 授权卡密钥扇区KEYA
 * @param keyb - 授权卡密钥扇区KEYB
 * @param sect - 授权卡密钥扇区号
 * @param block - 授权卡密钥块号
 * @param pos -   授权卡密钥块起始位置
 * 
 * @return - 返回CRC校验值 
 */
static long CalAuthCardCRC(BYTE keya[6],BYTE keyb[6],int sect,int block,int pos)
{
	BYTE buf[17] = "";
	long crc;
	int i;
	memcpy(buf,keyb,CARD_KEY_LEN);
	i = sprintf((char*)buf+CARD_KEY_LEN,"%c%c%02X",
		block+0x30,pos+0x30,sect);
	i += CARD_KEY_LEN;
	memcpy((char *)buf + i,keya,CARD_KEY_LEN);
	// 计算校验位
	crc = get_check_char(buf);
	return crc;
}

/** 
 * @brief 生成授权卡扇区密钥种子
 * 
 * @return - 成功返回0，失败返回-1
 */
static int ResetAuthCardKeySeed()
{
	int i;
	srand((unsigned)time( NULL ));
	for(i = 0;i < sizeof(AUTH_CARD_SEED);++i)
	{
		AUTH_CARD_SEED[i] = rand() % 255;
	}
	return 0;
}

/** 
 * @brief 库接口函数，发行授权卡
 * 
 * @param main_key - 授权密钥
 * @param pri_sect - 授权密钥所在扇区
 * @param pri_block- 授权密钥所在块号
 * @param pri_startpos - 授权密钥起始位置
 * @param flag - 授权卡级别标志，标志内容见授权卡结构文档
 * @param lpCallBack - 回调函数，处理卡时调用，可以为NULL
 * 
 * @return - 成功返回0，失败返回-1
 */
int __stdcall NewAuthCard(BYTE main_key[8],int pri_sect
								   ,int pri_block,int pri_startpos
								   ,int flag,LPProcessCallBack lpCallBack)
{
	// 发行授权卡
	// modify by Cash 2005-8-8
	// 为授权卡增加了标志位
	if((pri_sect == 7) || (pri_sect == 15 ) 
		|| (pri_sect == 30) || (pri_sect < 1)
		|| (pri_sect > 31)
		||(pri_block < 0) || (pri_block > 2)
		||(pri_startpos < 0) || (pri_startpos > 7))
	{
		MessageBox(NULL, "授权卡参数错误", NULL, NULL);
		return -1;
	}
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	long crc;
	short sect;
	if( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		MessageBox(NULL, "请放卡！", NULL, NULL);
		return -1;
	}
	// 计算密钥
	BYTE auth_key[8] = "";
	if( decrypt_work_key(main_key,auth_key) != 0)
	{
		MessageBox(NULL, "计算密钥失败！", NULL, NULL);
		return -1;
	}
	// 初始化所有扇区
	if( NewAuthCard_Init_Sect(card_id,card_type,lpCallBack) != 0)
	{
		return -1;
	}
	ResetAuthCardKeySeed();
	BYTE auth_key_a[6] = "";
	BYTE auth_key_b[6] = "";
	if(gen_auth_card_keyA(AUTH_CARD_SEED,auth_key_a) != 0 )
	{
		MessageBox(NULL, "生成密钥A失败！", NULL, NULL);
		return -2;
	}
	if(gen_auth_card_keyB(AUTH_CARD_SEED,auth_key_b) != 0)
	{
		MessageBox(NULL, "生成密钥B失败！", NULL, NULL);
		return -2;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// 第 7 扇区
	sect = 7;
	memset(buf,0,sizeof(buf));
	memcpy(buf,auth_key_b,sizeof(auth_key_b));
	sprintf((char*)buf+6,"%01X",pri_block);
	//buf[6] = (char)pri_block;
	sprintf((char*)buf+7,"%01X",pri_startpos);
	//buf[7] = (char)pri_startpos;
	memcpy(card_key,card_id,sizeof(card_id));
	sprintf((char*)card_key+4,"%02X",sect);
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		MessageBox(NULL, "登录扇区失败！", NULL, NULL);
		return -2;
	}
	if( SMT_WriteBlock(sect,1,buf) !=0 )
	{
		MessageBox(NULL, "写卡失败！", NULL, NULL);
		return -3;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// 第 15 扇区
	sect = 15;
	memset(buf,0,sizeof(buf));
	memcpy(buf+8,auth_key_a,sizeof(auth_key_a));
	sprintf((char*)buf+14,"%02X",pri_sect);
	
	memcpy(card_key,card_id,sizeof(card_id));
	sprintf((char*)card_key+4,"%02X",sect);
	
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		MessageBox(NULL, "登录扇区失败！", NULL, NULL);
		return -2;
	}
	if( SMT_WriteBlock(sect,2,buf) !=0 )
	{
		MessageBox(NULL, "写卡失败！", NULL, NULL);
		return -3;
	}
	if( lpCallBack )
		lpCallBack(0);
	//////////////////////////////////////////////////////////////////////////
	// 写校验位
	sect = 30;
	memset(buf,0,sizeof(buf));
	sprintf((char*)card_key+4,"%02X",sect);
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		MessageBox(NULL, "登录扇区失败！", NULL, NULL);
		return -2;
	}
	crc = CalAuthCardCRC(auth_key_a,auth_key_b,pri_sect,pri_block,pri_startpos);
	buf[11] = (unsigned char)crc;
	if(SMT_WriteBlock(sect,0,buf) != 0)
	{
		MessageBox(NULL, "写校验位失败", NULL, NULL);
	}
	//////////////////////////////////////////////////////////////////////////
	// 第 pri_sect 扇区
	sect = pri_sect;
	memset(buf,0,sizeof(buf));
	memcpy(buf+pri_startpos,auth_key,sizeof(auth_key));
	// modify by Cash 2005-8-8
	// 增加控制标志位
	*(buf+pri_startpos+sizeof(auth_key)) = (BYTE)flag;
	sprintf((char*)card_key+4,"%02X",sect);
	// 写密钥
	if(LoginCardSect(sect,card_key,CARD_KEY_A,card_type) !=0)
	{
		MessageBox(NULL, "登录扇区失败！", NULL, NULL);
		return -2;
	}
	if( SMT_WriteBlock(sect,pri_block,buf) !=0 )
	{
		MessageBox(NULL, "写卡失败！", NULL, NULL);
		return -3;
	}
	// 写控制位
	memset(buf,0,sizeof(buf));
	memcpy(buf,auth_key_a,sizeof(auth_key_a));
	memcpy(buf+sizeof(auth_key_a),CARD_INIT_CTRL_BIT,
		sizeof(CARD_INIT_CTRL_BIT));
	memcpy(buf+sizeof(auth_key_a)+sizeof(CARD_INIT_CTRL_BIT),
		auth_key_b,sizeof(auth_key_b));
	
	if( SMT_WriteBlock(sect,3,buf) != 0)
	{
		MessageBox(NULL, "写密钥扇区失败！", NULL, NULL);
		return -3;
	}	
	/*
	if( !Read_Author_Key() )
	{
		AfxMessageBox("初始化授权卡失败！");
		return -4;
	}
	*/
	return 0;
}

/** 
 * @brief 库接口函数，使用密钥为库授权
 * 
 * @param main_key - 授权密钥，长度为8字节
 * 
 * @return - 成功返回0，失败返回-1
 */
int __stdcall SetCardMainKey(BYTE main_key[8])
{
	if(!Is_Com_open())
	{
		MessageBox(NULL, "请打开串口!", NULL, NULL);
		return -1;
	}
	memcpy(CARD_MAIN_KEY,main_key,sizeof(CARD_MAIN_KEY));
	SMT_AutoDll(CARD_MAIN_KEY);
	SMT_ControlBuzzer();
	has_read_main_key = TRUE;
	return 0;
}

/** 
 * @brief 库接口函数，检测卡类型--裸卡, 初始化过的卡, 不可识别的卡
 * 
 * @param 无
 * 
 * @return - 返回1表示裸卡，2表示初始化过的卡, 3表示不可识别的卡
 */

int __stdcall SMT_CheckForCard()
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_b[7] = "";
	BYTE buf[16] = "";
	int current_key;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[2];
	int nFirstSect = 0;
	if (!Is_Com_open())
	{
		return -1;
	}
	if (FALSE == Read_Author_Key())
	{
		return -1;
	}
	if (SMT_RequestCardExist(card_id, card_type))
	{
		return -1;
	}

	if (gen_user_card_keyB(SMT_UCWORKINGKEY, card_id, card_key_b) != 0)
	{
		return -1;
	}
	memset((void *)card_key, 0, sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	memcpy(card_key[0].key, CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	card_key[1].flag = CARD_KEY_B;
	memcpy(card_key[1].key, card_key_b, sizeof(card_key_b));
	current_key = 0;
	if (0 == LoginCardSect(nFirstSect, card_key[current_key].key, card_key[current_key].flag, card_type))
	{
		return BARE_CARD_TYPE;
	}
	current_key++;
	if (0 == LoginCardSect(nFirstSect, card_key[current_key].key, card_key[current_key].flag, card_type))
	{
		return INIT_CARD_TYPE;
	}
	return UNRECOGNISE_CARD_TYPE;
}

/** 
 * @brief 库接口函数，充值平台检测钱包好坏
 * 
 * @param ucCardNo 学工号, ucCardReadKey 登陆的只读KEY
 * 
 * @return - 返回0表示检测成功, 否则-1表示钱包不允许使用, -2表示钱包坏掉了, -3表示登陆扇区失败, -4读扇区错误
 */
int __stdcall SMT_CheckForMoneyPacket()
{
	int ret = -100; 
	int sector = 0; 
	int	nPacketNo = 1;
	unsigned char ucBuffer[16] = "";
	unsigned char ucBuf1[16] = "",
				  ucBuf2[16] = "";
	unsigned char ucCheck = 0;
	int i;
	ret = Login_Card(3);
	if(ret != 0)	
		return -3;
	ret = SMT_ReadBlock(3, 0, ucBuffer);
	if(ret != 0)	
		return -4;
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return -1; // 钱包不允许使用
	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //钱包所在扇区
	ret = Login_Card(sector);
	if(ret != 0)
		return -3;
	ret = SMT_ReadBlock(sector, 0, ucBuf1);
	if(ret != 0)	
		return -2;	// 物理读取钱包错误
	for(i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck != ucBuf1[15])
	{
		ret = SMT_ReadBlock(sector, 2, ucBuf2);	// 读取备份钱包
		if(ret != 0)	
			return -2;  // 物理读取钱包错误
		ucCheck = 0;
		for(i = 0; i < 15; i++)
		{
			ucCheck += ucBuf2[i];
		}
		if(ucCheck != ucBuf2[15])	
			return -2;	// 读取钱包格式错误
	}
	return 0;
}

/** 
 * @brief 库接口函数，上大14扇区写入学工号
 * 
 * @param ucCardNo学工号, ucCardWriteKey登陆的可写KEY
 * 
 * @return - 返回0表示写入正确, 否则表示失败
 */
int __stdcall SMT_WriteCardNoFor14(unsigned char ucCardNo[20], unsigned char ucCardWriteKey[6])
{
	int ret = -5;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
	{
		return -1;	//卡片不在感应区
	}
	ret = SMT_Login_With_UserKey(14, ucCardWriteKey, 1);
	if (ret != 0)
	{
		return -2;	// 密钥登陆不上
	}
	memcpy(ucBuffer, ucCardNo, 16);
	ret = SMT_WriteBlock(14, 1, ucBuffer);
	if (ret != 0)	
	{
		return -3;  // 写入的14扇区, 1块的学工号前16位出错
	}
	memset(ucBuffer, 0xFF, 16);
	memcpy(ucBuffer, ucCardNo + 16, 4);
	ret = SMT_WriteBlock(14, 2, ucBuffer);
	if(ret != 0)	
	{
		return -4;	// 写入的14扇区, 2块的学工号后4位出错
	}
	return 0;
}

/** 
 * @brief 库接口函数，上大14扇区读取学工号
 * 
 * @param ucCardNo 学工号, ucCardReadKey 登陆的只读KEY
 * 
 * @return - 返回0表示写入正确, 否则表示失败
 */
int __stdcall SMT_ReadCardNoFor14(unsigned char ucCardNo[20], unsigned char ucCardReadKey[6])
{
	int ret = -5;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
	{
		return -1;	//卡片不在感应区
	}
	ret = SMT_Login_With_UserKey(14, ucCardReadKey, 0);
	if (ret != 0)
	{
		return -2;	// 密钥登陆不上
	}
	ret = SMT_ReadBlock(14, 1, ucBuffer);
	if (ret != 0)
	{
		return -3;	// 读取数据错误
	}
	memcpy(ucCardNo, ucBuffer, 16);
	memset(ucBuffer, 0x00, 16);
	ret = SMT_ReadBlock(14, 2, ucBuffer);
	if (ret != 0)
	{
		return -4;	// 读取数据错误
	}
	memcpy(ucCardNo + 16, ucBuffer, 4);
	return 0;
}

/************************************************************************/
/* 新授权卡操作函数描述                                                 */
/************************************************************************/
/** 
 * @brief 库接口函数，上大新发行授权卡
 * 
 * @param main_key - 授权密钥
 * @param pri_sect - 授权密钥所在扇区
 * @param pri_block- 授权密钥所在块号
 * @param pri_startpos - 授权密钥起始位置
 * @param flag - 授权卡级别标志，标志内容见授权卡结构文档
 * @param lpCallBack - 回调函数，处理卡时调用，可以为NULL
 * 
 * @return - 成功返回0，失败返回-1
 */
int __stdcall InitNewAuthCard(BYTE main_key[8], BYTE flag, LPProcessCallBack lpCallBack)
{
	// 函数中的获取工作密钥的扇区, 块数, 起始位置写死. 27扇区, 块0, 第4个字节开始
	// 发行新授权卡
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[6] = "";
	BYTE buf[17] = "";
	BYTE ucCryptWorkKey[17] = "";
	int ret = 0;
	long crc;
	short sect;
	int nPri_sect = 27;
	if(SMT_RequestCardExist(card_id,card_type) != 0)
	{
		return -1;
	}
	// 计算密钥
	BYTE auth_key[8] = "";
//	BYTE auth_key[8] = {0x43, 0x44, 0x33, 0x45, 0x39, 0x41, 0x38, 0x46};
//	BYTE auth_key[8] = {0x8E, 0x8B, 0xFC, 0x8F, 0xF6, 0x8F, 0xF4, 0x88};
	ResetAuthCardKeySeed();
 	BYTE auth_key_a[6] = "";
 	BYTE auth_key_b[6] = "";
 	if( gen_auth_card_keyA(AUTH_CARD_SEED,auth_key_a) != 0 )
 	{
 		return -6;
 	}
 	if(gen_auth_card_keyB(AUTH_CARD_SEED,auth_key_b) != 0)
 	{
 		return -6;
 	}
	// 计算扇区密钥
	encrypt_work_key(main_key, auth_key);

	// 初始化所有扇区
	ret = NewAuthCard_Init_Sect(card_id, card_type, lpCallBack, nPri_sect);
	if (ret != 0 && ret != 10 && ret != 11)
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// 已经初始化过了
	if (11 == ret)
	{
		goto L_END;
	}
	//////////////////////////////////////////////////////////////////////////
	if( lpCallBack )
		lpCallBack(0);
	
	//////////////////////////////////////////////////////////////////////////
	// 第 7 扇区
	sect = 7;
	memset(buf, 0, sizeof(buf));
	memcpy(buf, auth_key_b, sizeof(auth_key_b));
	sprintf((char*)buf + 6, "%01X", 0);                  // 第0块
	//buf[6] = (char)pri_block;
	sprintf((char*)buf + 7, "%01X", 4);				     // 第4个位置
	//buf[7] = (char)pri_startpos;
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if (SMT_WriteBlock(sect, 1, buf) != 0)
	{
		return -3;
	}
	if( lpCallBack )
		lpCallBack(0);

	//////////////////////////////////////////////////////////////////////////
	// 第 15 扇区
	sect = 15;
	memset(buf, 0, sizeof(buf));
	memcpy(buf + 8, auth_key_a, sizeof(auth_key_a));
	sprintf((char*)buf + 14, "%02X", 27);
	
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) !=0)
	{
		return -2;
	}
	if ( SMT_WriteBlock(sect, 2, buf) !=0 )
	{
		return -3;
	}
	if ( lpCallBack )
		lpCallBack(0);

	//////////////////////////////////////////////////////////////////////////
	// 补写工作密钥扇区
	if (ret == 10)
	{
		goto L_END ;
	}

	//////////////////////////////////////////////////////////////////////////
	// 写校验位
	sect = 30;
	memset(buf, 0, sizeof(buf));
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) !=0)
	{
		return -2;
	}
	crc = CalAuthCardCRC(auth_key_a, auth_key_b, 27, 0, 4);
	buf[11] = (unsigned char)crc;
	if(SMT_WriteBlock(sect, 0, buf) != 0)
	{
		return -4;
	}

	//////////////////////////////////////////////////////////////////////////
	// 第 pri_sect 扇区
	sect = 27;
	memset(buf, 0, sizeof(buf));
	memcpy(buf + 4, auth_key, sizeof(auth_key));
	// modify by Cash 2005-8-8
	// 增加控制标志位
	*(buf + 4 + sizeof(auth_key)) = flag;
	sprintf((char*)card_key + 4, "%02X", sect);
	// 写密钥
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if (SMT_WriteBlock(sect, 0, buf) != 0)
	{
		return -3;
	}

	//////////////////////////////////////////////////////////////////////////
	// 写控制位
	memset(buf, 0, sizeof(buf));
	memcpy(buf, auth_key_a, sizeof(auth_key_a));
	memcpy(buf + sizeof(auth_key_a), CARD_INIT_CTRL_BIT,
		sizeof(CARD_INIT_CTRL_BIT));
	memcpy(buf + sizeof(auth_key_a) + sizeof(CARD_INIT_CTRL_BIT),
		auth_key_b, sizeof(auth_key_b));
	
	if (SMT_WriteBlock(sect, 3, buf) != 0)
	{
		MessageBox(NULL, "写密钥扇区失败！", NULL, NULL);
		return -3;
	}

	//////////////////////////////////////////////////////////////////////////
	// 第0扇区快2需要添加控制位标志
	sect = 0;
	memset(buf, 0, sizeof(buf));
	memcpy(card_key, card_id, sizeof(card_id));
	sprintf((char*)card_key + 4, "%02X", sect);
	buf[11] = flag;
	
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) !=0)
	{
		return -2;
	}
	
	if (SMT_WriteBlock(sect, 2, buf) != 0)
	{
		return -3;
	}

L_END:
	return 0;
}

/** 
 * @brief 库接口函数，回收新授权卡函数
 * 
 * @return - 成功返回0，失败返回负数
 */
int __stdcall ResetNewAuthCard(int * err_code, LPProcessCallBack lpCallBack)
{
	// 回收扇区暂时写死掉
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	BYTE tmpBuf[17] = "";
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	BYTE tmpSect[3] = "";
	char tmp[3] = "";
	short priBlock = -1, 
		  priStartPos = -1, 
		  priSect = -1;
	unsigned short sect;

	if( !Is_Com_open() )
	{
		* err_code = E_COM_NOT_OPEN;
		return -1;
	}

	if(SMT_RequestCardExist(card_id, card_type) != 0)
	{
		* err_code = E_READ_CARD_ID_ERROR;
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// 读取 7 扇区
	sect = 7;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// 卡 ID 为 4 位
	sprintf((char*)card_key + 4, "%02X", sect);
	
	// 读取 Key B
	if( LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		MessageBox(NULL, "登录扇区失败！", "", NULL);
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect, 1, buf) != 0)
	{
//		MessageBox(NULL, "读取扇区失败！", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key b
	memcpy(priKeyB, buf, CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if( priBlock < 0 || priBlock > 2)
	{
//		MessageBox(NULL, "数据不合法！", "", NULL);
		* err_code = E_INVALID_CARD;
		return -3;
	}
	// start pos
	// priStartPos = char2int((const char*)&buf[7],1,true);
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp, NULL, 16);
	if( priStartPos < 0 || priStartPos > 10)
	{
//		MessageBox(NULL, "数据不合法！", "", NULL);
		* err_code = E_INVALID_CARD;
		return -3;
	}
	//////////////////////////////////////////////////////////////////////////
	// 读 15 扇区
	sect = 15;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// 卡 ID 为 4 位
	sprintf((char*)card_key + 4, "%02X", sect);
	// 读取 Key a
	if( LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
//		MessageBox(NULL, "登录扇区失败！", "", NULL);
		* err_code = E_CARD_LOGIN_ERROR;
		return -2;
	}
	if( SMT_ReadBlock(sect, 2, buf) != 0)
	{
//		MessageBox(NULL, "读取扇区失败！", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -3;
	}
	// key a
	strncpy((char*)priKeyA, (char*)buf + 8, CARD_KEY_LEN);
	// private key section no
	priSect = (short)strtoul((char*)buf + 14, NULL, 16);
	//////////////////////////////////////////////////////////////////////////
	// 生成初始状态
	memset((char*)buf, 255, sizeof(buf) - 1);
	strncpy((char*)buf + sizeof(CARD_INIT_KEY), (char*)CARD_INIT_CTRL_BIT, sizeof(CARD_INIT_CTRL_BIT));
	
	if(lpCallBack)
		lpCallBack(0);
	bool isClear = false;
	// 回收密钥扇区
	if(LoginCardSect(priSect, priKeyA, CARD_KEY_A, card_type) == 0)
	{
		memset(tmpBuf, 0, sizeof(tmpBuf));
		// 将授权工作密钥扇区清零
		if(SMT_WriteBlock(priSect, priBlock, tmpBuf) != 0)
		{
			isClear = false;
			goto L_TRY_KEY_B;
		}
		// 写控制位扇区
		strncpy((char*)tmpBuf, (char*)buf, sizeof(tmpBuf));
		if(SMT_WriteBlock(priSect, 3, tmpBuf) != 0)
		{
			// 写卡失败，使用Key B 重试
			isClear = false;
		}
		else
			isClear = true;	
	}
L_TRY_KEY_B:
	if(lpCallBack)
		lpCallBack(0);
	if(!isClear)
	{
		// 用 key B 测试
		if (LoginCardSect(priSect, priKeyB, CARD_KEY_B, card_type) == 0)
		{
			memset(tmpBuf, 0, sizeof(tmpBuf));
			
			if (SMT_WriteBlock(priSect, priBlock, tmpBuf) != 0)
			{
//				MessageBox(NULL, "写扇区数据失败！", "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// 写控制位扇区
			strncpy((char*)tmpBuf, (char*)buf, sizeof(tmpBuf));
			if(SMT_WriteBlock(priSect, 3, tmpBuf) != 0)
			{
				// key B 也无法写。
//				MessageBox(NULL, "写扇区数据失败！", "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			
		}
		else
		{
			// 无法用 key b 登录，
//			MessageBox(NULL, "登录扇区失败！", "", NULL);
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;
		}
	}

	// 测试是否回收成功
	if( LoginCardSect(priSect, CARD_INIT_KEY, CARD_KEY_A, card_type) != 0)
	{
//		MessageBox(NULL, "回收扇区失败！", "", NULL);
		* err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	char msg[128] = "";
	// 清空有数据的0, 1, 2扇区
	if (SMT_ClearAuthCard() != 0)
	{
		*err_code = E_CARD_WRITE_ERROR;
		return -2;
	}
	for(sect = 0; sect < AUTH_CARD_SECT_NO; ++sect)
	{
		if(lpCallBack)
			lpCallBack(0);
		// 密钥扇区不用初始化
		if( sect == priSect)
			continue;
		memset(card_key, 0, sizeof(card_key));
		memcpy(card_key, card_id, sizeof(card_id));
		// 卡 ID 为 4 位
		sprintf((char*)(card_key + 4), "%02X", sect);
		
		if( LoginCardSect(sect, card_key
				,CARD_KEY_A, card_type) == 0)
		{
			strncpy((char*)tmpBuf, (char*)buf, sizeof(tmpBuf));
			// 登录成功
			// 回收控制位
			if( SMT_WriteBlock(sect, 3, tmpBuf) != 0)
			{
				sprintf(msg, "回收[%d]扇区失败！", sect);
//				MessageBox(NULL, msg, "", NULL);
				* err_code = E_CARD_WRITE_ERROR;
				return -2;
			}
			// 用Key A 登录测试
			if( LoginCardSect(sect, CARD_INIT_KEY, CARD_KEY_A, card_type) != 0)
			{
				sprintf(msg, "测试登录%d扇区失败！", sect);
//				MessageBox(NULL, msg, "", NULL);
				* err_code = E_CARD_LOGIN_ERROR;
				return -1;
			}
		}
		else if( LoginCardSect(sect, CARD_INIT_KEY, CARD_KEY_A, card_type) == 0)
		{
			// 使用 初始化 密钥进行登录测试
			sprintf(msg,"扇区%d使用初始密钥登录成功。\n是否继续回收？",sect);
			if (MessageBox(NULL, msg, "", MB_OKCANCEL) == IDCANCEL)
			{
				// 如果不继续回收,则返回
				* err_code = E_CARD_LOGIN_ERROR;
				return -2;
			}
		}
		else
		{
			sprintf(msg,"登录卡第%d扇区失败",sect);
//			MessageBox(NULL, msg, "", NULL);
			* err_code = E_CARD_LOGIN_ERROR;
			return -2;
		}
	}
	SMT_ControlBuzzer();
	return 0;
}

// 登陆授权卡扇区, 使用KEYA登陆
static int Login_Auth_Card(int sector)
{
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_key[7] = "";
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;	// 卡片不在感应区
	memcpy(ucCard_key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_key + 4, "%02X", sector);
	ret = SMT_Login_With_UserKey(sector, ucCard_key, 0);                     
	if(ret != 0)
	{
		return -2;	// 卡片登陆失败
	}
	return 0;
}

// 发行授权卡
int __stdcall PublishAuthCard(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];
	unsigned char ucCardRightType[1];
	BOOL bPersonalFlag = TRUE;
	BOOL bStateFlag = TRUE;
	BOOL bBankInfo = TRUE;
	BOOL bPacketFlag[8] = {TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE};
	int iCardNo[1];
	memset(ucBcdShowCardNo, 0, sizeof(ucBcdShowCardNo));

/*
	ret = ifAuthorReadyOK();
	if (ret !=0)
		return ret;				// 检测授权卡是否有密码登陆, 现在密钥现成, 以后有进入授权卡的密钥获得登陆
*/
/*
	ret = SMT_ClearAuthCard();
	if(ret)
	{
		SetErrMsg(ret,"格式化卡失败");
		return ret;
	}
*/
	ret = strlen((char*)pc->ShowCardNo);
	if(10 == ret)	
	{
		//转换为BCD码
		dec2bcd(pc->ShowCardNo,ucBcdShowCardNo,5);
	}
	//转换为进制
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear, 0, sizeof(sYear));
	memset(sMon, 0, sizeof(sMon));
	memset(sDay, 0, sizeof(sDay));

	memcpy(sYear, pc->DeadLineDate + 2, 2);
	memcpy(sMon, pc->DeadLineDate + 4, 2);
	memcpy(sDay, pc->DeadLineDate + 6, 2);
	
	ucDeadLineDate[0] = atoi(sYear);
	ucDeadLineDate[1] = atoi(sMon);
	ucDeadLineDate[2] = atoi(sDay);
	iCardNo[0] = atoi((char*)pc->CardNo);
	ucCardRightType[0] = pc->CardRightType;
	// 写一扇区的个人信息, 以下函数扇区不对, 重新做
	ret = SMT_WriteAuthCardStateInfo(ucBcdShowCardNo, iCardNo, ucDeadLineDate, ucCardRightType); 
	if(ret)
	{
		SetErrMsg(ret,"写卡基本信息失败");
		return ret;           //写基本信息错误
	}
	
	// 写持二扇区公开信息, 以下函数不对, 重新做
	ret = SMT_WriteAuthPersonalInfo(pc->ucName,
									pc->ucDutyNo,
									pc->ucCertificateNo,
									pc->ucDepartmentNo,
									pc->ucIdentifyNo,
									pc->ucSexNo,
									pc->ucCardNo);
	if(ret)
	{
		SetErrMsg(ret,"写人事信息失败");
		return ret;           //
	}
	ret = SMT_WriteAuthorNo(pc->ucLibraryNo);
	if (ret)
	{
		SetErrMsg(ret, "写管理员号失败");
		return ret;
	}
	ret = WriteAuthCardPwd(pc->ucPwd);
	if(ret)
	{
		SetErrMsg(ret,"写卡密码失败");
		return ret;
	}
	ret = SMT_InitAuthBlackCardFlag();
	if (ret)
	{
		SetErrMsg(ret, "初始化黑卡标记失败");
		return ret;
	}
	//预存金额
/*
	unsigned short int PacketNo = 1;
	int Money;
	Money = pc->Money;
	ret = SMT_PacketSetMoney(PacketNo,Money);
	if(ret)
	{
		SetErrMsg(ret,"设置钱包余额失败");
		return ret;		
	}
*/
	SMT_ControlBuzzer();		
	return 0;
}

int __stdcall SMT_ClearAuthCard()
{
	unsigned char ucSerialNo[5] = "";
	unsigned char ucRawData[256] = "";
	unsigned char ucCard_key[6] = "";
	int nSector, 
		nBlock, 
		startSector = 4;
	int ret = 0;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	memcpy(ucCard_key, ucSerialNo, sizeof(ucSerialNo));
	//1、使用出厂密码登陆卡片  前32个扇区
	for(nSector = 0; nSector < 12; nSector++)
	{
		sprintf((char*)ucCard_key + 4, "%02X", nSector);
		if(nSector == 3)
			continue;
		ret = SMT_Login_With_UserKey(nSector, ucCard_key, 0);
		if(ret != 0)
			return -2; //非出厂卡
		for(nBlock = 0; nBlock < 3; nBlock++)
		{
			if(nSector == 0 && nBlock == 0)
				continue;
			if(nSector == 1 && nBlock == 0)
			{
				//  如果是第1扇区第0块，读取显示卡号，不要删除该数据
				ret = SMT_ReadBlock(nSector, nBlock, ucRawData);
				if(ret)
					return -3;
				// 清除除显示卡号以外的其它数据
				memset(ucRawData, 0x00, 7);
				memset(ucRawData + 12, 0x00, 4);
			}
			else
			{
				memset(ucRawData, 0x00, 16);
			}
			ret = SMT_WriteBlock(nSector, nBlock, ucRawData);
			if(ret)
				return -3;
		}
	}
	memset(ucRawData,0xFF,16);
	nBlock = 0;
	for(nSector = 0; nSector < 4; nSector++)
	{
		// 使得1, 2, 3, 4号钱包可用, 同时记录使用钱包的扇区号
		ucRawData[nBlock] = 0x00;
		nBlock++;
		ucRawData[nBlock] = startSector;                        // 注意只能改第四个
		startSector += 1;
		nBlock++;
	}
	sprintf((char*)ucCard_key + 4, "%02X", 3);
	//1 使用用户密码登陆
	ret = SMT_Login_With_UserKey(3, ucCard_key, 0);
	if(ret != 0)
		return -4;//使用用户密码KEYA不能登陆
	ret = SMT_WriteBlock(3, 0, ucRawData);
	if(ret != 0)
		return -5;//无法写卡
	memset(ucRawData, 0xFF, 16);

	for(nSector = 0; nSector < 4; nSector++)
	{
		// 1, 2, 3, 4号钱包补助信息所在的扇区
		ucRawData[nSector] = startSector;
		startSector++;
	}
	ret = SMT_WriteBlock(3, 1, ucRawData);
	if(ret != 0)
		return -6;//无法写卡
	// 回收后变成黑卡, 将学工号后面四位也清空
	memset(ucRawData, 0x00, 16);  
//	ucRawData[4] = 0xFF;
	sprintf((char*)ucCard_key + 4, "%02X", 0);
	ret = SMT_Login_With_UserKey(0, ucCard_key, 0);
	if(ret != 0)
		return -4;//使用用户密码KEYA不能登陆
	ret = SMT_WriteBlock(0, 2, ucRawData);
	if(ret != 0)
		return -7;//无法写卡
	return 0;	
}

// 函数功能: 初始化时设置授权卡黑名单标记, 开头两字符黑卡为00, 白卡为FF
// 函数参数: 无
int __stdcall SMT_InitAuthBlackCardFlag()
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 0);
	ret = SMT_Login_With_UserKey(0, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if (ret != 0)
		return ret;
	ucBuffer[4] = 0xFF;					// 白卡
	memset(ucBuffer + 5, 0x00, 6);		// 后面6个字节置0 
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	return 0;
}

// 函数功能: 设置授权卡黑名单版本号, 开头两字符黑卡为00, 白卡为FF
// 函数参数: blkversion 授权卡黑名单版本
int __stdcall SMT_SetAuthNormalFlagByBlkVerion(char *auth_black_version)
{
	int ret;
	unsigned char ucBlkVer[12];
	unsigned char ucBuffer[16];
	ret = Login_Auth_Card(0);
	if (ret != 0)	
		return ret;
	if (strlen(auth_black_version) != 12)
	{
		return -1;	
	}
	dec2bcd((unsigned char*)auth_black_version, ucBlkVer, 6);
//	memset(ucBuffer, 0xFF, 16);
	if (ret = SMT_ReadBlock(0, 2, ucBuffer))
		return -3;

	memcpy(ucBuffer + 5, ucBlkVer, 6);
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if (ret != 0)	
		return -6;
	SMT_ControlBuzzer();
	return 0;
}

// 函数作用: 写入授权卡管理员个人密码3个字节, 6个字符
// 函数参数: 授权卡个人密码
int __stdcall SMT_WriteAuthPersonalPassword(unsigned char ucAuthPersonalPsd[3])
{
	int ret = 0;
	unsigned char ucBuffer[16];
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 1);
	ret = SMT_Login_With_UserKey(1, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucAuthPersonalPsd, 3);
	ret = SMT_WriteBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	return 0;
}

// 函数作用: 写入授权卡管理员个人密码6个字符
// 函数参数: 授权卡个人密码
int __stdcall WriteAuthCardPwd(unsigned char ucAuthoPwd[6])
{
	int ret = 0;
	unsigned char ucPwd[3];
	dec2bcd(ucAuthoPwd, ucPwd, 3);
	ret = SMT_WriteAuthPersonalPassword(ucPwd);
	if(ret)
	{
		SetErrMsg(ret, "写卡密码失败");
		return ret;
	}
	return 0;
}

// 函数作用: 写入授权卡的状态信息 
// 函数参数: ucShowCardNo(用户显示卡号), nDealCardNo(用户交易卡号), 
//			 ucDeadLineDate(卡的截止日期), ucCardRightType(用户卡使用类型权限)
int __stdcall SMT_WriteAuthCardStateInfo(unsigned char ucShowCardNo[5], 
										 int nDealCardNo[1], 
										 unsigned char ucDeadLineDate[3], 
										 unsigned char ucCardRightType[1])
{
	unsigned char ucCard_Key[6] = "";
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	int ret = 0;
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 1);
	ret = SMT_Login_With_UserKey(1, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(1);
	if(ret != 0)
		return -2;//卡片登陆失败
	//第0块数据组织
	if(nDealCardNo[0] > 0x0FFFFF)
		return -3;//交易卡号过大
	memset(ucBuffer, 0xFF, 16);
	ucBuffer[0] = nDealCardNo[0] / 256 / 256;
	ucBuffer[1] = nDealCardNo[0] / 256;
	ucBuffer[2] = nDealCardNo[0] % 256;
	ucBuffer[3] = ucCardRightType[0];
	memcpy(ucBuffer + 4, ucDeadLineDate, 3);
	memcpy(ucBuffer + 7, ucShowCardNo, 5);
	ret = SMT_WriteBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -5; //写卡失败
	return 0;							
}

// 函数作用：写入授权卡片个人信息
// 函数参数: ucName(姓名), ucDutyNo(职务代码), ucCertificateNo(证件代码)
//			 ucDepartmentNo(部门编号), ucIdentifyNo(身份代码), ucSexNo(性别), ucCardNo(学工号)
int __stdcall SMT_WriteAuthPersonalInfo(unsigned char ucName[8],
										unsigned char ucDutyNo[4],
										unsigned char ucCertificateNo[20],
										unsigned char ucDepartmentNo[10],
										unsigned char ucIdentifyNo[4],
										unsigned char ucSexNo[1],
										unsigned char ucCardNo[20])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 0);
	//工号学号操作
	ret = SMT_Login_With_UserKey(0, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucCardNo, 16);
	ret = SMT_WriteBlock(0, 1, ucBuffer);
	if(ret != 0)	
		return -5;
//	memset(ucBuffer, 0xFF, 16);
	if (ret = SMT_ReadBlock(0, 2, ucBuffer))
		return -4;
	memcpy(ucBuffer, ucCardNo + 16, 4);
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if (ret != 0)	
		return -5;
	
	//第2扇区0块操作
	/*
	sprintf((char*)ucCard_Key + 4, "%02X", 2);
	ret = SMT_Login_With_UserKey(2, ucCard_Key, 0);
	*/
	ret = Login_Auth_Card(2);  
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer, ucName, 8);
	memcpy(ucBuffer + 8, ucDutyNo, 4);
	memcpy(ucBuffer + 12, ucCertificateNo, 4);
	ret = SMT_WriteBlock(2, 0, ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(ucBuffer,ucCertificateNo + 4, 16);
	ret = SMT_WriteBlock(2, 1, ucBuffer);
	if(ret != 0)	
		return -5;
	memcpy(ucBuffer, ucDepartmentNo, 10);
	memcpy(ucBuffer + 10, ucIdentifyNo, 4);
	memcpy(ucBuffer + 14, ucSexNo, 1);
	ret = SMT_WriteBlock(2, 2, ucBuffer);
	if(ret != 0)	
		return -5;
	return 0;
}

// 函数作用: 写操作员号10个字节
// 函数参数: 操作员号
int __stdcall SMT_WriteAuthorNo(unsigned char ucAuthorId[10])
{
	int ret;
	unsigned char ucBuffer[16] = "";
	unsigned char ucSerialNo[5] = "";
	unsigned char ucCard_Key[6] = "";
	/*
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	memcpy(ucCard_Key, ucSerialNo, sizeof(ucSerialNo));
	sprintf((char*)ucCard_Key + 4, "%02X", 1);
	ret = SMT_Login_With_UserKey(1, ucCard_Key, 0);	
	*/
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	memcpy(ucBuffer + 3, ucAuthorId, 10);
	ret = SMT_WriteBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return ret;
	return 0;
}

int __stdcall ReadAuthCardInfo(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//用户卡使用截止日期
	unsigned char ucCardRightType[1];		//权限位
	int iCardNo[1];

	ret = SMT_ReadAuthCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"读卡基本信息失败");
		return ret;    
	}
	bcd2dec(ucBcdShowCardNo,5,pc->ShowCardNo);
	//转换hex日期格式到十进制
	sprintf((char*)pc->DeadLineDate,"20%02d%02d%02d",ucDeadLineDate[0],ucDeadLineDate[1],ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo,"%d",iCardNo[0]);
	pc->CardRightType=ucCardRightType[0];
	ret = SMT_ReadAuthPersonalInfo(pc->ucName,pc->ucDutyNo,pc->ucCertificateNo,pc->ucDepartmentNo,pc->ucIdentifyNo,pc->ucSexNo,pc->ucCardNo);
	if (ret !=0)
	{
		SetErrMsg(ret,"读卡人事信息失败");
		return ret;     
	}
	ret = SMT_ReadAuthPersonalPassword(pc->ucPwd);
	if (ret != 0)
	{
		SetErrMsg(ret, "读取操作员密码失败");
		return ret;
	}
	ret = SMT_ReadAuthorNo(pc->ucLibraryNo);
	if(ret)
	{
		SetErrMsg(ret,"写图书证号失败");
		return ret;
	}
	return 0;
}

// 函数作用: 读取授权卡操作员密码
// 函数参数: 操作员个人密码(6位)
int __stdcall SMT_ReadAuthPersonalPassword(unsigned char PersonalPsd[6])
{
	int ret;
	unsigned char ucBuffer[16] = "";
	unsigned char ucTempPersonalPsd[16] = "";
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)	
		return -5;
	bcd2dec(ucBuffer, 3, ucTempPersonalPsd);
	memcpy(PersonalPsd, ucTempPersonalPsd, 6);
	return 0;
}

int __stdcall SMT_ReadAuthCardStateInfo(unsigned char ucShowCardNo[5],
										int nDealCardNo[1],
										unsigned char ucDeadLineDate[3],
										unsigned char ucCardRightType[1])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if(ret != 0)
		return -6; //读卡失败
	nDealCardNo[0] = ucBuffer[0]*256*256+ucBuffer[1]*256+ucBuffer[2];
	ucCardRightType[0] = ucBuffer[3];
	memcpy(ucDeadLineDate, ucBuffer + 4, 3);
	memcpy(ucShowCardNo, ucBuffer + 7, 5);
	return 0;
}

int __stdcall SMT_ReadAuthPersonalInfo(unsigned char ucName[8],
									   unsigned char ucDutyNo[4],
									   unsigned char ucCertificateNo[20],
									   unsigned char ucDepartmentNo[10],
									   unsigned char ucIdentifyNo[4],
									   unsigned char ucSexNo[1],
									   unsigned char ucCardNo[20])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	//工号学号操作
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(0, 1, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucCardNo, ucBuffer, 16);
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucCardNo + 16, ucBuffer, 4);
	ret = Login_Auth_Card(2);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(2, 0, ucBuffer);
	if(ret != 0 )	
		return -6;
	memcpy(ucName, ucBuffer, 8);
	memcpy(ucDutyNo, ucBuffer + 8, 4);
	memcpy(ucCertificateNo, ucBuffer + 12, 4);
	ret = SMT_ReadBlock(2, 1, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucCertificateNo + 4, ucBuffer, 16);
	ret = SMT_ReadBlock(2, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	memcpy(ucDepartmentNo, ucBuffer, 10);
	memcpy(ucIdentifyNo, ucBuffer + 10, 4);
	memcpy(ucSexNo, ucBuffer + 14, 1);
	return 0;
}

// 函数作用: 读取操作员号10个字节
// 函数参数: 操作员号
int __stdcall SMT_ReadAuthorNo(unsigned char ucAuthorId[10])
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	ret = Login_Auth_Card(1);
	if(ret != 0)	
		return ret;
	//memset(ucBuffer,0xFF,16);
	ret = SMT_ReadBlock(1, 1, ucBuffer);
	if(ret != 0)
		return -5;
	memcpy(ucAuthorId, ucBuffer + 3, 10);
	return 0;
}

// 读取授权卡黑名单列表版本
int __stdcall SMT_ReadAuthBlackNameListVersion(int *nflag, char *sVersion)
{
	int ret;
	unsigned char ucBuffer[16] = "";
	char sTempVersion[13] = "";
	ret = Login_Auth_Card(0);
	if(ret != 0)	
		return ret;
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if(ret != 0)	
		return -6;
	if(0 == ucBuffer[0])
		*nflag = 1;		// 黑卡
	else	
		*nflag = 0;		// 白卡
	dec2hex(ucBuffer + 1, 6, sTempVersion);
	strcpy(sVersion, sTempVersion);
	return 0;
}

int __stdcall ReadAuthCardBlock(int startSect, int endSect, short block, LPGetBlockData lpFunc)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key_a[7] = "";
	BYTE card_key_b[7] = "";
	BYTE buf[16] = "";
	int current_key, old_key;
	int nWorkKeySector = 0;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[3];
	
	int sect = 0;
	// 判断打开串口
	if (!Is_Com_open())
	{
		return -1;
	}
	// 检查卡是否存在
	if ( SMT_RequestCardExist(card_id,card_type) != 0 )
	{
		return -1;
	}
	memcpy(card_key_a, card_id, sizeof(card_id));
	memcpy(card_key_b, card_id, sizeof(card_id));
	// 初始化 key 的数组
	memset((void *)card_key,0,sizeof(card_key));
	card_key[0].flag = CARD_KEY_A;
	// 这里可以读出回收后的KEYA
	memcpy(card_key[0].key, CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	card_key[1].flag = CARD_KEY_A;
	card_key[2].flag = CARD_KEY_B;	
	// 保存可以登录的 key 有索引
	current_key = 1;
	for(sect = startSect; sect < endSect + 1; ++sect)
	{
		
		sprintf((char*)card_key_a + 4, "%02X", sect);
		sprintf((char*)card_key_b + 4, "%02X", sect);
		memcpy(card_key[1].key, card_key_a, sizeof(card_key_a));
		memcpy(card_key[2].key, card_key_b, sizeof(card_key_b));
		// 依次初始化每个扇区
		old_key = current_key;
		login_sect_succ = FALSE;
		// 查找可以登录的 key 
		while(TRUE)
		{
			// 如果登录成功 跳出循环
			if( LoginCardSect(sect, card_key[current_key].key
				, card_key[current_key].flag, card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key > 2 )
				current_key = 0;
			if (current_key == old_key)
			{	// 循环密钥登陆不上, 看看是不是密钥扇区
				if (SMT_LoginWorkKeySector(NULL, NULL, NULL, NULL) != 0)
				{
					login_sect_succ = FALSE;
				}
				else
				{
					login_sect_succ = TRUE;
				}
				break;
			}		
		}
		// 判断当前扇区是否成功登录
		if (login_sect_succ == FALSE)
		{
			return -1;
		}
		// 读取卡扇区数据
		for(int b = 0;b < 4;++b)
		{
			if(block & (1 << b))
			{
				memset(buf, 0, sizeof(buf));
				if(SMT_ReadBlock(sect, b, buf) != 0)
				{
					return -1;
				}
				// 调用读卡回调函数
				if( lpFunc != NULL )
				{
					lpFunc(sect, b, buf,
						card_key[current_key].key,
						card_key[current_key].flag);
					
				}
			}
		}
		
	}
	return 0;
}

int __stdcall SMT_LoginWorkKeySector(BYTE pri_key_a[6], BYTE pri_key_b[6], short *pri_sect, short *pri_block)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE card_key[7] = "";
	BYTE buf[17] = "";
	BYTE tmpBuf[17] = "";
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	BYTE tmpSect[3] = "";
	char tmp[3] = "";
	short priBlock, priStartPos, priSect;
	unsigned short sect;
	if (SMT_RequestCardExist(card_id, card_type) != 0)
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////////////////
	// 读取 7 扇区
	sect = 7;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// 卡 ID 为 4 位
	sprintf((char*)card_key + 4, "%02X", sect);
	
	// 读取 Key B
	if( LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if( SMT_ReadBlock(sect, 1, buf) != 0)
	{
		return -3;
	}
	// key b
	memcpy(priKeyB, buf, CARD_KEY_LEN);
	// block
	priBlock = buf[6] - '0';
	if (priBlock < 0 || priBlock > 2)
	{
		return -3;
	}
	
	if (pri_block != NULL)
		*pri_block = priBlock;
	
	// start pos
	tmp[0] = buf[7];
	priStartPos = (short)strtoul(tmp, NULL, 16);
	if (priStartPos < 0 || priStartPos > 10)
	{
		return -3;
	}
	//////////////////////////////////////////////////////////////////////////
	// 读 15 扇区
	sect = 15;
	memset(card_key, 0, sizeof(card_key));
	memcpy(card_key, card_id, sizeof(card_id));
	// 卡 ID 为 4 位
	sprintf((char*)card_key + 4, "%02X", sect);
	// 读取 Key a
	if (LoginCardSect(sect, card_key, CARD_KEY_A, card_type) != 0)
	{
		return -2;
	}
	if (SMT_ReadBlock(sect, 2, buf) != 0)
	{
		return -3;
	}
	// key a
	strncpy((char*)priKeyA, (char*)buf + 8, CARD_KEY_LEN);
	// private key section no
	priSect = (short)strtoul((char*)buf + 14, NULL, 16);
	if (LoginCardSect(priSect, priKeyA, CARD_KEY_A, card_type) != 0) 
//		|| LoginCardSect(priSect, priKeyB, CARD_KEY_B, card_type) != 0)
	{
		return -5;
	}

	if (pri_sect != NULL)
		*pri_sect = priSect;
	
	if (pri_key_a != NULL) 
		memcpy(pri_key_a, priKeyA, sizeof(priKeyA));
	
	if (pri_key_b != NULL)
		memcpy(pri_key_b, priKeyB, sizeof(priKeyB));

	return 0;	
}

int __stdcall SMT_ReadAuthorWorkKeyAndFlag(BYTE auth_work_key[8], BYTE *flag)
{
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	short priSect = 0;
	short priBlock = 0;
	int ret = 0;
	BYTE buf[17] = "";

	if (ret = SMT_LoginWorkKeySector(priKeyA, priKeyB, &priSect, &priBlock))
		return ret;
	
	if (SMT_Login_With_UserKey(priSect, priKeyA, 0))
	{
		return -9;	// 卡片登陆失败
	}

	if (SMT_ReadBlock(priSect, priBlock, buf) != 0)
	{
		return -10;
	}

	memcpy(auth_work_key, buf + 4, sizeof(BYTE) * 8);
	*flag = *(buf + 4 + sizeof(BYTE) * 8);
	return 0;
}

int __stdcall SMT_ModifyDeadLineDateAndFlag(BYTE DeadLineDate[8], BYTE flag)
{
	BYTE priKeyA[7] = "";
	BYTE priKeyB[7] = "";
	short priSect = 0;
	short priBlock = 0;
	int ret = 0;
	BYTE buf[17] = "";

	if (ret = SMT_LoginWorkKeySector(priKeyA, priKeyB, &priSect, &priBlock))
		return ret;

	if (SMT_Login_With_UserKey(priSect, priKeyA, 0))                     
		return -9;	// 卡片登陆失败

	if (SMT_ReadBlock(priSect, 0, buf) != 0)
		return -10;

	*(buf + 4 + sizeof(BYTE) * 8) = flag;
	if (SMT_WriteBlock(priSect, priBlock, buf) != 0)
		return -11;
	
	/************************************************************************/
	/* 更新0扇区块2的11字节标志
	/************************************************************************/
	ret = Login_Auth_Card(0);
	if (ret != 0) { return -12; }

	memset(buf, 0, sizeof(buf));

	if (SMT_ReadBlock(0, 2, buf)) { return -13; }
	buf[11] = flag;
	if (SMT_WriteBlock(0, 2, buf)) { return -14; }

	//////////////////////////////////////////////////////////////////////////
	// 写截止日期
	BYTE ucDeadLineDate[3] = "";
	BYTE ucBuffer[17] = "";
	char sYear[3];
	char sMon[3];
	char sDay[3];
	
	memset(sYear, 0, sizeof(sYear));
	memset(sMon, 0, sizeof(sMon));
	memset(sDay, 0, sizeof(sDay));

	memcpy(sYear, DeadLineDate + 2, 2);
	memcpy(sMon, DeadLineDate + 4, 2);
	memcpy(sDay, DeadLineDate + 6, 2);
	
	ucDeadLineDate[0] = atoi(sYear);
	ucDeadLineDate[1] = atoi(sMon);
	ucDeadLineDate[2] = atoi(sDay);
	
	ret = Login_Auth_Card(1);
	if(ret != 0)
		return -12;//卡片登陆失败

	if (SMT_ReadBlock(1, 0, ucBuffer))
		return -13;

	memcpy(ucBuffer + 4, ucDeadLineDate, 3);
	if (SMT_WriteBlock(1, 0, ucBuffer))
		return -14;

	SMT_ControlBuzzer();
	return	0;
}

/************************************************************************/
/* 上海理工大学水控对接费率设置卡和采集卡设置                           */
/************************************************************************/
/** 
 * @brief 上海理工大学费率卡和采集卡登陆密钥算法
 * 
 * @param Srn - 卡片序列号
 * @param KeyA - 登陆采集卡A密钥
 * @return - 成功返回0，失败返回-1
 */
void GenerateKeyA(BYTE Srn[4],unsigned char KeyA[6])
{
	unsigned char i;	
	unsigned int BCC;

	BCC = 0;
	for(i=0;i<4;i++)
	BCC += Srn[i];

	memcpy(KeyA,Srn,4);
    KeyA[4] =(unsigned char)(BCC>>8);
	KeyA[5]	=(unsigned char)BCC;
    return;
}

static int WriteWaterCardBlock(int *err_code, PWriteDataFunc pFunc, LPProcessCallBack lpCallBack)
{
	BYTE card_id[5] = "";
	BYTE card_type[5] = "";	// 第三个字节表示卡结构, 0x10表示费率设置卡和采集卡
	BYTE buf[17] = "";
	long crc = 0;
	short sect = 0;
	int ret = 0;
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	BYTE key_a[7] = "";
	BYTE key_b[7] = "";
	CardKeyData card_key[3];

	memset((void *)card_key, 0, sizeof card_key);
	if (!Is_Com_open())
	{
		*err_code = E_COM_NOT_OPEN;
		return -1;
	}
	
	if (SMT_RequestCardExist(card_id, card_type) != 0)
	{
		*err_code = E_READ_CARD_ERROR;
		return -1;
	}
	GenerateKeyA(card_id, key_a);
	memcpy(key_b, key_a, sizeof key_b);			// 暂时KEYA和KEYB同一个密钥
	
	card_key[0].flag = CARD_KEY_A;
	
	memcpy(card_key[0].key,CARD_INIT_KEY,sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key, key_a, sizeof key_a);

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key, key_b, sizeof key_b);
	
	// 再读一次卡检查一下卡 ID
	memset(card_id, 0, sizeof card_id);
	if (SMT_RequestCardExist(card_id, card_type) != 0)
	{
		*err_code = E_READ_CARD_ERROR;
		return -1;
	}
	
	card_type[2] = 0x10;

	current_key = 0;
	for (sect = 0; sect < COLLECT_CARD_SECT_NO; sect++)
	{
		if (lpCallBack != NULL)
			lpCallBack(sect);
		old_key = current_key;
		login_sect_succ = FALSE;
		while (TRUE)
		{
			if (0 == LoginCardSect(sect,card_key[current_key].key
				,card_key[current_key].flag,card_type))
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key--;
			if (current_key < 0)
				current_key = 2;
			if (current_key == old_key)
				break;
		}
		
		if (FALSE == login_sect_succ)
		{
			*err_code = E_CARD_LOGIN_ERROR;
			return -1;	
		}
		
		if (pFunc != NULL)
		{
			if ((ret = pFunc(sect, &card_key[1], &card_key[2], card_type, &card_key[current_key])) != 0)
			{
				*err_code = E_CARD_WRITE_ERROR;
				return ret;
			}		
		}
	}
	return 0;
}

/** 
 * @brief 上海理工大学初始化费率设置卡
 * 
 * @param err_code - 错误返回码
 * @param lpCallBack - 回调函数，处理卡时调用，可以为NULL
 * @return - 成功返回0，失败返回-1
 */
int __stdcall InitNewFeeRateCard(int *err_code, LPProcessCallBack lpCallBack)
{
	int ret = 0;
	if (WriteWaterCardBlock(err_code, WriteInitNewCardData, lpCallBack) != 0)
	{
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

/** 
 * @brief 上海理工大学初始化采集卡
 * 
 * @param err_code - 错误返回码
 * @param lpCallBack - 回调函数，处理卡时调用，可以为NULL
 * @return - 成功返回0，失败返回-1
 */
int __stdcall InitNewCollectionCard(int *err_code, LPProcessCallBack lpCallBack)
{
	/*
	BYTE test[5] = "";
	return SMT_ReadWaterCardFlag(test);
	*/
	int ret = 0;
	BYTE water_card_flag[5] = "LYCJ";
	if (WriteWaterCardBlock(err_code, WriteInitNewCardData, lpCallBack) != 0)
	{
		return -1;
	}
	if ((ret = SMT_WriteWaterCardFlag(water_card_flag)) != 0)
	{
		*err_code = ret;
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

/** 
 * @brief 上海理工大学采集卡回收数据
 * 
 * @param err_code					- 错误返回码
 * @param shop_id					- 商户ID号, 4个字节
 * @param shop_card_total_sum		- 商户总余额, 4个字节
 * @return - 成功返回0，失败返回-1
 */
int __stdcall CollectionCardReceiveData(int *err_code, COLLECT_BALANCE collect_balance[90], int *collect_count)
{
	//////////////////////////////////////////////////////////////////////////
	/*
	Login_Collect_Card(1);
	BYTE buf_test[17] = {0x00, 0x0a, 0x61, 0x06, 0xaf, 0x23};
	if (SMT_WriteBlock(1, 0, buf_test))
	{
		return 0;
	}
	*/
	//////////////////////////////////////////////////////////////////////////
	int ret = 0;
	int sect = 0;
	int block = 1;
	int byte_length = 4;
	int offset = 0;
	int buf_offset = 0;
	int count = 0;
	BYTE buf[17] = "";
	BYTE cmp_buf[17] = "";
	BYTE buf_balance[5] = "";
	BYTE water_card_flag[5] = "LYCJ";
	Login_Collect_Card(sect);
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		*err_code = ret;	
	}
	if (_mbsncmp(water_card_flag, buf, sizeof(water_card_flag) - 1))
	{
		*err_code = E_CARD_FLAG_ERROR;
	}
	memset(buf, 0, sizeof(buf) -1);
	block = 0;
	for (sect = 1; sect < 32; sect++)
	{
		Login_Collect_Card(sect);
		while (block < 3)
		{
			ret = SMT_ReadBlock(sect, block, buf);
			if (ret)
			{
				*err_code = ret;
			}
			
			if (0 == memcmp(buf, cmp_buf, sizeof(buf) - 1))
			{
				*collect_count = count;
				return 0;
			}

//			memcpy(collect_balance[count].devphy999_id, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			dec2hex(buf + buf_offset * 2, sizeof(BYTE) * byte_length, collect_balance[count].devphy999_id);	
			memcpy(buf_balance, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			collect_balance[count].sum_balance = ((double)(buf_balance[3] * 256 * 256 * 256 + buf_balance[2] * 256 * 256 + buf_balance[1] * 256 + buf_balance[0]) / 100);
			offset += 4;
			buf_offset = 4;
			count++;
			
			if (memcmp(buf + 8, cmp_buf, sizeof(BYTE) * 8) == 0)
			{
				*collect_count = count;
				return 0;
			}
			
//			memcpy(collect_balance[count].devphy999_id, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			dec2hex(buf + buf_offset * 2, sizeof(BYTE) * byte_length, collect_balance[count].devphy999_id);
			memcpy(buf_balance, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			collect_balance[count].sum_balance = ((double)(buf_balance[3] * 256 * 256 * 256 + buf_balance[2] * 256 * 256 + buf_balance[1] * 256 + buf_balance[0]) / 100);
			count++;
			/*
			memcpy(shop_id + offset, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			memcpy(shop_card_total_sum + offset, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			offset += 4;
			buf_offset = 4;
			memcpy(shop_id + offset, buf + buf_offset * 2, sizeof(BYTE) * byte_length);
			memcpy(shop_card_total_sum + offset, buf + byte_length + buf_offset * 2, sizeof(BYTE) * byte_length);
			block++;
			*/
			block++;
			buf_offset = 0;
		}
		block = 0;
	}
	return 0;
}

/** 
 * @brief 上海理工大学回收采集卡和费率设置卡
 * 
 * @param err_code - 错误返回码
 * @param LPProcessCallBack - 回调函数，处理卡时调用，可以为NULL
 * @return - 成功返回0，失败返回-1
 */
int __stdcall RefineWaterCard(int *err_code, LPProcessCallBack lpFunc)
{
	int ret = 0;
	if ((ret = SMT_ClearWaterCard()) != 0)
	{
		*err_code = ret;
		return -1;
	}

	if (WriteWaterCardBlock(err_code, WriteRefineCardData, lpFunc) != 0)
	{
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

int Login_Collect_Card(int sector)
{
	unsigned char ucSerialNo[5], ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret < 0)
		return -1;//卡片不在感应区
	//1 --- 计算KEYA
	GenerateKeyA(ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(sector,ucKeyA,0);                       
	if(ret != 0)
	{
		return -2;//卡片登陆失败
	}
	return 0;
}

int __stdcall SMT_ClearWaterCard()
{
	unsigned char ucSerialNo[5] = "";
	unsigned char ucKeyA[6] = "";
	unsigned char buf[16] = "";
	int ret = 0;
	int block = 0;
	//1、使用出场密码登陆卡片  前16个扇区
	for (int sect = 0; sect < COLLECT_CARD_SECT_NO; sect++)
	{
		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}

		for (block = 0; block < 3; block++)
		{
			if (0 == sect && 0 == block)
				continue;

			ret = SMT_WriteBlock(sect, block, buf);
			if (ret)
			{
				return E_CARD_WRITE_ERROR;
			}
		}			
	}
	return 0;
}

int __stdcall SMT_WriteWaterCardFlag(BYTE water_card_flag[4])
{
	int sect = 0;
	int block = 1;
	BYTE buf[17] = "";
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	memcpy(buf, water_card_flag, sizeof(BYTE) * 4);
	if (SMT_WriteBlock(sect, block, buf) != 0)
	{	
		return E_CARD_WRITE_ERROR;
	}
	return 0;
}

int __stdcall ReadWaterCardBlock(int startSect,int endSect
									 ,short block,LPGetBlockData lpFunc)
{
	BYTE card_id[5] = "";
	BYTE card_type[2] = "";
	BYTE key_a[7] = "";
	BYTE key_b[7] = "";
	BYTE buf[16] = "";
	int current_key, old_key;
	BOOL login_sect_succ = FALSE;
	
	CardKeyData card_key[3];
	int sect = 0;

	// 判断打开串口
	if (!Is_Com_open())
	{
		return -1;
	}

	// 检查卡是否存在
	if (SMT_RequestCardExist(card_id,card_type) != 0)
	{
		return -1;
	}

	// 计算卡的 keyA , keyB
	GenerateKeyA(card_id, key_a);
	memcpy(key_b, key_a, sizeof key_b);

	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	// 这里可以读出回收后的KEYA
	memcpy(card_key[0].key, CARD_INIT_KEY, sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key, key_a, sizeof key_a);

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key, key_b, sizeof key_b);

	// 保存可以登录的 key 有索引
	current_key = 1;
	for(sect = startSect; sect < endSect + 1; ++sect)
	{
		// 依次初始化每个扇区
		old_key = current_key;
		login_sect_succ = FALSE;
		// 查找可以登录的 key 
		while(TRUE)
		{
			// 如果登录成功 跳出循环
			if( LoginCardSect(sect, card_key[current_key].key
				,card_key[current_key].flag, card_type) == 0)
			{
				login_sect_succ = TRUE;
				break;
			}
			current_key++;
			if( current_key > 3 )
				current_key = 0;
			if (current_key == old_key)
				break;
		}
		// 判断当前扇区是否成功登录
		if (login_sect_succ == FALSE)
		{
			return -1;
		}
		// 读取卡扇区数据
		for(int b = 0;b < 4;++b)
		{
			if(block & (1 << b))
			{
				memset(buf, 0, sizeof(buf));
				if (SMT_ReadBlock(sect, b, buf) != 0)
				{
					return -1;
				}
				// 调用读卡回调函数
				if(lpFunc != NULL)
				{
					lpFunc(sect, b, buf,
						card_key[current_key].key,
						card_key[current_key].flag);			
				}
			}
		}	
	}
	return 0;
}

/** 
 * @brief 上海理工大学发行费率设置卡
 * 
 * @param -  fee_rate_card_info 费率卡结构
 * @return - 成功返回0，失败返回错误码
 */
int __stdcall PublishFeeRateCard(FEE_RATE_CARD_INFO *fee_rate_card_info)
{
	int ret = 0;
	int sect = 0;
	int block = 1;
	int block_num = 0;
	short fee_rate_data_length = 0;
	char msg[128] = "";
	BYTE buf[17] = "";
	BYTE right_type_bit[32] = "";
	BYTE check_crc = 0;
	BYTE auth_key[8] = "";
	BYTE temp = 0;
	int offset = 0;
	int right_type_num = 0;

	if (ret = SMT_ClearWaterCard())
	{
		return	ret; 
	}
	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		sprintf(msg, "费率标志--[%d]", fee_rate_card_info->fee_right_num[right_type_num].right_flag);
		DEBUG_CARD_MSGOUT(right_type_num, msg);
		if (0 == fee_rate_card_info->fee_right_num[right_type_num].right_flag)
			continue;
		fee_rate_data_length += fee_rate_card_info->fee_right_num[right_type_num].right_num * 3 + 1;
	}

//	memcpy(&fee_rate_data_length, &(fee_rate_card_info->data_length), sizeof(fee_rate_card_info->data_length) - 1);
	BYTE fee_rate_data_buf[512] = "";
//	memcpy(fee_rate_data_buf, &fee_rate_data_length, sizeof(BYTE) * 2);
	fee_rate_data_buf[0] = fee_rate_data_length >> 8 & 0xff;
	fee_rate_data_buf[1] = fee_rate_data_length & 0xff;
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	// 第0扇区
	memcpy(buf, fee_rate_card_info->water_card_flag, offset += (sizeof(fee_rate_card_info->water_card_flag) -1));
//	memcpy(buf + offset, (void)fee_rate_card_info->packet_no, offset += sizeof(fee_rate_card_info->packet_no));
	buf[offset] = fee_rate_card_info->packet_num;
	offset += sizeof(fee_rate_card_info->packet_num);
	
	buf[offset] = fee_rate_card_info->work_mode;
	offset += sizeof(fee_rate_card_info->work_mode);
	sprintf(msg,"write work mode[%d]",fee_rate_card_info->work_mode);
	DEBUG_CARD_MSGOUT(1001,msg);
	/*
	buf[offset] = fee_rate_card_info->transfer_limit >> 8 & 0xff;
	buf[offset + 1] = fee_rate_card_info->transfer_limit & 0xff;
	offset += 2;
	buf[offset] = fee_rate_card_info->water_packet_limit >> 8 & 0xff;
	buf[offset + 1] = fee_rate_card_info->water_packet_limit & 0xff;
	offset += 2;
	*/
//	memset(buf + offset, 0xFF, 16 - offset);						全FF则check_crc越界
	for (int address = 0; address < 15; address++)
	{
		check_crc += buf[address];
	}
	buf[15] = check_crc;
	ret = SMT_WriteBlock(sect, block, buf);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;		
	}
	
	memset(buf, 0x00, sizeof(buf) -1);
//	MessageBox(NULL, (char*)fee_rate_card_info->main_work_key, NULL, NULL);
	encrypt_work_key(fee_rate_card_info->main_work_key, auth_key);
//	memcpy(buf, fee_rate_card_info->main_work_key, sizeof(fee_rate_card_info->main_work_key) - 1);
//	memcpy(buf + 8, fee_rate_card_info->packet_work_key, sizeof(fee_rate_card_info->packet_work_key) - 1);
	memcpy(buf, auth_key, sizeof(BYTE) * 8);				// 8字节写死了
	encrypt_work_key(fee_rate_card_info->packet_work_key, auth_key);
	memcpy(buf + 8, auth_key, sizeof(BYTE) * 8);
	
	ret = SMT_WriteBlock(sect, block + 1, buf);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}
	sect = 1;			// 第一扇区0块开始以后每个块都能够用
	block = 0;
	offset = 2;
	check_crc = 0;
	// 收费扇区设置
	memset(buf, 0x00, sizeof(buf) - 1);
	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate_card_info->fee_right_num[right_type_num].right_flag)
			continue;
		right_type_bit[(255 - right_type_num) / 8] |= 1 << (right_type_num % 8);
		memcpy(fee_rate_data_buf + offset, &(fee_rate_card_info->fee_right_num[right_type_num].right_num), sizeof BYTE);
		
		check_crc += fee_rate_card_info->fee_right_num[right_type_num].right_num;		// 累加效验和
/*		
		itoa(fee_rate_card_info->fee_right_num[right_type_num].right_num, test, 10);
		MessageBox(NULL, test, NULL, NULL);
*/		
		for (int right_num = 0; right_num < fee_rate_card_info->fee_right_num[right_type_num].right_num; right_num++)
		{
			memcpy(fee_rate_data_buf + offset + 1, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].time_ladder), 1);
			memcpy(fee_rate_data_buf + offset + 2, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_time), 1);
			memcpy(fee_rate_data_buf + offset + 3, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee), 1);
			check_crc += fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].time_ladder[0] + 
						fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_time[0] +
						fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee[0]; 
			offset += 3;	// 里层循环+3
		}
		offset += 1;		// 外层+1添加一个字节的权限费率个数
	}

	// 登陆第一扇区的块0和块1, 写入权限位图
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	
	ret = SMT_WriteBlock(sect, block, right_type_bit);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}
	
	ret = SMT_WriteBlock(sect, block += 1, right_type_bit + 16);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}

	int block_byte_num = 0;
	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;

	block = 2;															// block = 2的时候进来
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// 计算出来的扇区块数目进行比较
	{
		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}
	
		ret = SMT_WriteBlock(sect, block, fee_rate_data_buf + block_byte_num);
		if (ret)
		{
			return E_CARD_WRITE_ERROR;
		}
		
		block_byte_num += 16;
		++block_num;													// 已经写入一个块
		++block;

		if (block >= 2)
		{
			block = 0;
			++sect;
			continue;
		}
		// 拷贝剩余数据
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
																		//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = SMT_WriteBlock(sect, block, fee_rate_data_buf + block_byte_num);
				if (ret)
				{
					return E_CARD_WRITE_ERROR;
				}
				return 0;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

int __stdcall ReadCollectCardInfo(FEE_RATE_CARD_INFO *fee_rate_card_info)
{
	int sect = 0;
	int block = 1;
	int ret = 0;
	int fee_rate_data_length = 0;
	int right_type_num = 0;
	int offset = 0;
	int block_num = 0;
	int block_byte_num = 0;
	BYTE fee_rate_count = 0;
	BYTE buf[17] = "";
	BYTE right_type_bit[33] = "";
	BYTE fee_rate_data_buf[512] = "";
	char msg[128] = "";
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}	
	memcpy(fee_rate_card_info->water_card_flag, buf, sizeof(fee_rate_card_info->water_card_flag) - 1);
	memcpy(&(fee_rate_card_info->packet_num), buf + 4, sizeof(fee_rate_card_info->packet_num));
	memcpy(&(fee_rate_card_info->work_mode), buf + 5, sizeof(fee_rate_card_info->work_mode));		// 工作地点00:公寓 FF: 浴室
	sprintf(msg,"read card work_mode [%d]",fee_rate_card_info->work_mode);
	DEBUG_CARD_MSGOUT(1000,msg);
	memcpy(fee_rate_card_info->check_crc, buf + 15, sizeof(fee_rate_card_info->check_crc) - 1);
	block++;
	memset(buf, 0, sizeof(buf) - 1);
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	memcpy(fee_rate_card_info->main_work_key, buf, sizeof(fee_rate_card_info->main_work_key) - 1);
	memcpy(fee_rate_card_info->packet_work_key, buf + 8, sizeof(fee_rate_card_info->packet_work_key) - 1);
	
	sect = 1;
	block = 0;
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	ret = SMT_ReadBlock(sect, block, right_type_bit);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	block = 1;
	ret = SMT_ReadBlock(sect, block, right_type_bit + 16);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	block = 2;
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	memcpy(fee_rate_card_info->data_length, buf, sizeof(BYTE) * 2);
	//memcpy(&fee_rate_data_length, fee_rate_card_info->data_length, sizeof(BYTE) * 2);
	//fee_rate_card_info->data_length = ((buf[0] << 8) & 0xff00) | buf[1];
	fee_rate_data_length = ((buf[0] << 8) & 0xff00) | buf[1];
//	fee_rate_data_length = fee_rate_card_info->data_length;
//	memcpy(&fee_rate_count, buf + 2, sizeof(fee_rate_count));	
//	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;
	// block = 2的时候进来
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// 计算出来的扇区块数目进行比较
	{

		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}
	
		ret = SMT_ReadBlock(sect, block, fee_rate_data_buf + block_byte_num);
		if (ret)
		{
			return E_READ_CARD_ERROR;
		}
		
		block_byte_num += 16;
		++block_num;													// 已经写入一个块
		++block;

		if (block >= 2)
		{
			block = 0;
			++sect;
			continue;
		}
		// 拷贝剩余数据
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
				//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = SMT_ReadBlock(sect, block, fee_rate_data_buf + block_byte_num);
				if (ret)
				{
					return E_READ_CARD_ERROR;
				}
			}
			++block_num;
		}
	}
	
	memcpy(fee_rate_card_info->check_crc, &fee_rate_data_buf[fee_rate_data_length + 2], sizeof(BYTE));
	
	offset = 2;
	for (right_type_num = 0; right_type_num < 32; right_type_num++)
	{
		if (right_type_bit[31 - right_type_num] != 0)
		{
			for (int bit = 0; bit < 8; bit++)
			{
				if ((right_type_bit[31 - right_type_num] & (1 << bit)) != 0)
				{
					fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].right_flag = 1;
					fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].right_num = fee_rate_data_buf[offset];
					offset += 1;
					for (int count = 0; count < fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].right_num; count++)
					{
						memcpy(&(fee_rate_card_info->fee_right_num[right_type_num * 8 + bit].fee_rate[count]), fee_rate_data_buf + offset, sizeof(BYTE) * 3);
						offset += 3;
					}
//					offset += 1;
				}			
			}
		}
	}
	return 0;
}

int __stdcall WaterTransferSmallPacket(int BigPacketNo, int SmallPacketNo, int nMoney)
{
	int ret = 0;
//	int purse_packet_one = 1;
//	int purse_packet_two = 2;
	int packet_one_money = 0;
	int packet_two_money = 0;
	int transfer_money_use = 0;
//	double transfer_money = 0;
//	CString str_transfer_money = "";
	LOOPPURSEINFO LoopPurseInfoOne;
	LOOPPURSEINFO LoopPurseInfoTwo;
	memset(&LoopPurseInfoOne, 0, sizeof LoopPurseInfoOne);
	memset(&LoopPurseInfoTwo, 0, sizeof LoopPurseInfoTwo);
	transfer_money_use = nMoney;
	if (transfer_money_use <= 0)
	{
//		AfxMessageBox("请输入正数金额");
		return -1001;
	}
	if(SMT_ReadPacketInfo(BigPacketNo, &LoopPurseInfoOne))
	{
//		AfxMessageBox("读取大钱包信息失败");
		return -1002;
	}
	if (LoopPurseInfoOne.RemainMoney < 0)
	{
//		AfxMessageBox("大钱包余额不足");
		return -1003;
	}
	if(SMT_ReadPacketInfo(SmallPacketNo, &LoopPurseInfoTwo))
	{
//		AfxMessageBox("读取999钱包信息失败");
		return -1004;
	}
	if (LoopPurseInfoTwo.RemainMoney < 0)
	{
//		AfxMessageBox("999钱包余额不足");
		return -1005;
	}
	packet_one_money = LoopPurseInfoOne.RemainMoney;
	packet_two_money = LoopPurseInfoTwo.RemainMoney;
	
	ret = SMT_PacketSetMoney(BigPacketNo, (packet_one_money - transfer_money_use));
	if (ret)
	{
//		AfxMessageBox("写入大钱包失败");
		return -1006;
	}
	ret = SMT_PacketSetMoney(SmallPacketNo, (packet_two_money + transfer_money_use));
	if (ret)
	{
//		AfxMessageBox("写入999钱包失败");
		return -1007;
	}
//	AfxMessageBox("转钱包成功");
	return 0;
}

int __stdcall SMT_ClearCollectCardData()
{
	int ret = 0;
	BYTE water_card_flag[5] = "LYCJ";
	if (ret = SMT_ClearWaterCard())
	{
		return ret;
	}
	if ((ret = SMT_WriteWaterCardFlag(water_card_flag)) != 0)
	{
		return ret;
	}
	return 0;
}

int __stdcall SMT_ReadWaterCardFlag(BYTE WaterCardFlag[4])
{
	int sect = 0;
	int block = 1;
	BYTE buf[17] = "";
	BYTE init_key[7] = "";
	BYTE card_type[3] = "";
	memcpy(init_key, CARD_INIT_KEY, sizeof(CARD_INIT_KEY));
	
	//判断是否为裸卡
	if (0 == LoginCardSect(sect, init_key, 0, card_type))
	{
		memset(WaterCardFlag, 0, sizeof(BYTE) * 4);
		return 0;
	}

	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	
	if (SMT_ReadBlock(sect, block, buf))
	{
		return E_READ_CARD_ERROR;	
	}
	
	memcpy(WaterCardFlag, buf, sizeof(BYTE) * 4);
	return 0;
}

/*================================================================ 
* 函数名：    InitWashCard
* 参数：      [out] (int *err_cod)返回的错误码
*             [in]  (LPProcessCallBack lpCallBack)处理卡片信息的回调函数 					
* 功能描述:   初始化洗衣机卡 
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int __stdcall InitWashCard(int *err_code, LPProcessCallBack lpCallBack)
{
	int ret = 0;
	if (WriteWaterCardBlock(err_code, WriteInitNewCardData, lpCallBack) != 0)
	{
		return -1;
	}
	SMT_ControlBuzzer();
	return 0;
}

/*================================================================ 
* 函数名：    PublisNewWashCard
* 参数：      [in] (FEE_RATE_CARD_INFO *fee_rate_card_info)
*					fee_rate_card_info结构看carddll_def.h
* 功能描述:   发行洗衣机卡 
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int __stdcall PublishNewWashCard(FEE_RATE_CARD_INFO *fee_rate_card_info)
{
	int ret = 0;
	int sect = 0;
	int block = 1;
	int block_num = 0;
	short fee_rate_data_length = 0;
	BYTE buf[17] = "";
	BYTE right_type_bit[32] = "";
	BYTE check_crc = 0;
	BYTE auth_key[8] = "";
	BYTE temp = 0;
	int offset = 0;
	int right_type_num = 0;

	if (ret = SMT_ClearWaterCard())
	{
		return	ret; 
	}

	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate_card_info->fee_right_num[right_type_num].right_flag)
			continue;
		fee_rate_data_length += fee_rate_card_info->fee_right_num[right_type_num].right_num * 3 + 1;
	}

	BYTE fee_rate_data_buf[512] = "";
	fee_rate_data_buf[0] = fee_rate_data_length >> 8 & 0xff;
	fee_rate_data_buf[1] = fee_rate_data_length & 0xff;
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}
	// 第0扇区
	memcpy(buf, fee_rate_card_info->water_card_flag, offset += (sizeof(fee_rate_card_info->water_card_flag) -1));
	buf[offset] = fee_rate_card_info->packet_num;
	offset += sizeof(fee_rate_card_info->packet_num);
	buf[offset] = fee_rate_card_info->work_mode;
	offset += sizeof(fee_rate_card_info->work_mode);
	// 全FF则check_crc越界
	for (int address = 0; address < 15; address++)
	{
		check_crc += buf[address];
	}
	buf[15] = check_crc;
	ret = SMT_WriteBlock(sect, block, buf);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;		
	}

	memset(buf, 0x00, sizeof(buf) -1);
	encrypt_work_key(fee_rate_card_info->main_work_key, auth_key);
	memcpy(buf, auth_key, sizeof(BYTE) * 8);				// 8字节写死了
//	encrypt_work_key(fee_rate_card_info->packet_work_key, auth_key);
//	memcpy(buf + 8, auth_key, sizeof(BYTE) * 8);

	ret = SMT_WriteBlock(sect, block + 1, buf);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}
	sect = 1;			// 第一扇区0块开始以后每个块都能够用
	block = 0;
	offset = 2;
	check_crc = 0;
	// 收费扇区设置
	memset(buf, 0x00, sizeof(buf) - 1);
	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate_card_info->fee_right_num[right_type_num].right_flag)
			continue;
		right_type_bit[(255 - right_type_num) / 8] |= 1 << (right_type_num % 8);
		memcpy(fee_rate_data_buf + offset, &(fee_rate_card_info->fee_right_num[right_type_num].right_num), sizeof BYTE);

		check_crc += fee_rate_card_info->fee_right_num[right_type_num].right_num;		// 累加效验和

		for (int right_num = 0; right_num < fee_rate_card_info->fee_right_num[right_type_num].right_num; right_num++)
		{
			memcpy(fee_rate_data_buf + offset + 1, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].time_ladder), 1);
			memcpy(fee_rate_data_buf + offset + 2, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_time), 1);
			memcpy(fee_rate_data_buf + offset + 3, &(fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee), 1);
			check_crc += fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].time_ladder[0] + 
				fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_time[0] +
				fee_rate_card_info->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee[0]; 
			offset += 3;	// 里层循环+3
		}
		offset += 1;		// 外层+1添加一个字节的权限费率个数
	}

	// 登陆第一扇区的块0和块1, 写入权限位图
	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}

	ret = SMT_WriteBlock(sect, block, right_type_bit);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}

	ret = SMT_WriteBlock(sect, block += 1, right_type_bit + 16);
	if (ret)
	{
		return E_CARD_WRITE_ERROR;
	}

	int block_byte_num = 0;
	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;

	block = 2;															// block = 2的时候进来
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// 计算出来的扇区块数目进行比较
	{
		if (Login_Collect_Card(sect) != 0)
		{
			return E_CARD_LOGIN_ERROR;
		}

		ret = SMT_WriteBlock(sect, block, fee_rate_data_buf + block_byte_num);
		if (ret)
		{
			return E_CARD_WRITE_ERROR;
		}

		block_byte_num += 16;
		++block_num;													// 已经写入一个块
		++block;

		if (block >= 2)
		{
			block = 0;
			++sect;
			continue;
		}
		// 拷贝剩余数据
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
				//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = SMT_WriteBlock(sect, block, fee_rate_data_buf + block_byte_num);
				if (ret)
				{
					return E_CARD_WRITE_ERROR;
				}
				return 0;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}

int __stdcall ReadWaterFeeCardInfo(FEE_RATE_CARD_INFO *fee_rate_card_info)
{
	int sect = 0;
	int block = 1;
	int ret = 0;
	int offset = 0;
	int block_num = 0;
	BYTE fee_rate_count = 0;
	BYTE buf[17] = "";
	BYTE check_crc = 0;

	if (Login_Collect_Card(sect) != 0)
	{
		return E_CARD_LOGIN_ERROR;
	}

	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}	
	memcpy(fee_rate_card_info->water_card_flag, buf, sizeof(fee_rate_card_info->water_card_flag) - 1);
	memcpy(&(fee_rate_card_info->packet_num), buf + 4, sizeof(fee_rate_card_info->packet_num));
	fee_rate_card_info->transfer_limit = buf[5] * 256 + buf[6];
	fee_rate_card_info->water_packet_limit = buf[7] * 256 + buf[8];
	memcpy(fee_rate_card_info->check_crc, buf + 15, sizeof(fee_rate_card_info->check_crc) - 1);
	
	for (int address = 0; address < 15; address++) { check_crc += buf[address]; }
	
	if (fee_rate_card_info->check_crc[0] != check_crc) { return E_CHECK_SUM_ERROR; }

	block++;
	memset(buf, 0, sizeof(buf) - 1);
	ret = SMT_ReadBlock(sect, block, buf);
	if (ret)
	{
		return E_READ_CARD_ERROR;
	}
	memcpy(fee_rate_card_info->main_work_key, buf, sizeof(fee_rate_card_info->main_work_key) - 1);
	memcpy(fee_rate_card_info->packet_work_key, buf + 8, sizeof(fee_rate_card_info->packet_work_key) - 1);

	return 0;
}

/*================================================================ 
* 函数名：    SMT_ReadAreaCode
* 参数：      [out] (int *area_code)
*             学校院校代码, 代表学校所在区域, 多个学校也可能在一个区域
* 功能描述:   读取学校院校代码
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int __stdcall SMT_ReadAreaCode(int *area_code)
{
	int ret = 0;
	unsigned char ucBuffer[16] = "";
	ret = Login_Card_Keyb(0);
	if (ret != 0)	
	{
		DEBUG_CARD_MSGOUT(ret, "使用KEYA登录失败");
		return ret;
	}

	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if (ret != 0)
	{
		DEBUG_CARD_MSGOUT(ret, "读取卡信息失败");
		return ret;
	}

	memcpy(area_code, ucBuffer + 4, 3);

	return 0;
}

/*================================================================ 
* 函数名：    SMT_WriteAreaCode
* 参数：      [in] (int area_code)
*             学校院校代码, 代表学校所在区域, 多个学校也可能在一个区域
* 功能描述:   写入学校院校代码
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int __stdcall SMT_WriteAreaCode(int area_code)
{
	int ret;
	unsigned char ucBuffer[16];
	ret = Login_Card_Keyb(0);
	if (ret != 0)	
	{
		DEBUG_CARD_MSGOUT(ret, "使用KEYB登录失败");
			return ret;
	}
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if (ret != 0)
	{
		DEBUG_CARD_MSGOUT(ret, "读取卡信息失败");
			return ret;
	}

	memcpy(ucBuffer + 4, &area_code, 3);
	ret = SMT_WriteBlock(0, 2, ucBuffer);
	if (ret != 0)
	{
		DEBUG_CARD_MSGOUT(ret, "读取卡信息失败");
			return -5; //写卡失败
	}

	return 0;
}

/*================================================================ 
* 函数名：    SMT_WriteSubsidy
* 参数：      [in] (int money)		金额
*             [in] (int batch_no)	批次号
* 功能描述:   写补助信息:
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int __stdcall SMT_WriteSubsidy(int money, int batch_no)
{
	int ret = 0;
	int i;
	bool main_packet_flag = false;
	bool backup_packet_flag = false;
	unsigned char ucBuffer[16] = "";
	unsigned char subsidy_batch_no[3] = "";
	unsigned char ucBuf1[16], ucBuf2[16], ucBufTmp[16];
	unsigned char ucCheck;

	ret = Login_Card(4);
	if (ret != 0)	
		return -1001;

	ret = SMT_ReadBlock(4, 0, ucBuf1);						// 大钱包扇区
	if (ret != 0)	
		return -1002;

	ucCheck = 0;
	for (i = 0; i < 15; i++)
		ucCheck += ucBuf1[i];
	if (ucCheck == ucBuf1[15])
	{
		main_packet_flag = true;
	}
	else
	{
		ret = SMT_ReadBlock(4, 2, ucBuf2);
		if (ret != 0)	
			return -1003;

		ucCheck = 0;
		for (i = 0; i < 15; i++)
			ucCheck += ucBuf2[i];

		if (ucCheck == ucBuf2[15])
		{
			backup_packet_flag = true;
		}
		else
		{
			DEBUG_CARD_MSGOUT(ret, "备份块主校验和计算有误");
				return 2;
		}
	}

	subsidy_batch_no[0] = batch_no >> 8 & 0xFF;
	subsidy_batch_no[1] = batch_no & 0xFF;

	if (main_packet_flag)
	{
		memcpy(ucBufTmp, ucBuf1, sizeof(ucBufTmp));
		ret = SMT_WriteBlock(4, 2, ucBufTmp);				// 写备份钱包
		if (ret != 0)
		{
			DEBUG_CARD_MSGOUT(ret, "写主钱包备份块失败");
				return -1005;
		}
		i = money;
		ucBuf1[0] = i % 256;
		ucBuf1[1] = i / 256;
		ucBuf1[2] = i / 256 / 256;
		i = ucBuf1[3] * 256 + ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf1[7])
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		ucBuf1[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf1[13] = subsidy_batch_no[0];		// 补助批次号, 高位在前	
		ucBuf1[14] = subsidy_batch_no[1];		// 补助批次号
		ucBuf1[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf1[15] += ucBuf1[i];

		ret = SMT_WriteBlock(4, 0, ucBuf1);
		if (ret != 0)
		{
			DEBUG_CARD_MSGOUT(ret, "写主钱包失败");
				return -1007;
		}
	}
	else
	{
		if (!backup_packet_flag)
			return 2;

		ret = SMT_ReadBlock(4, 2, ucBuf2);
		if (ret != 0)
		{
			DEBUG_CARD_MSGOUT(ret, "读取主钱包备份块失败");
				return -1008;
		}

		i = money;
		ucBuf2[0] = i % 256;
		ucBuf2[1] = i / 256;
		ucBuf2[2] = i / 256 / 256;
		i = ucBuf2[3] * 256 + ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i / 256;
		ucBuf2[4] = i % 256;
		SYSTEMTIME tm;
		GetLocalTime(&tm);
		//如果上次交易日期与当前时间不同，则把累计消费金额清零
		if (tm.wDay != ucBuf2[7])
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tm.wYear - 2000);	// tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;			// tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;				// tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wHour;				// tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;			// tm.GetMinute();
		ucBuf2[13] = subsidy_batch_no[0];		// 补助批次号, 高位在前	
		ucBuf2[14] = subsidy_batch_no[1];		// 补助批次号
		ucBuf2[15]=0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];

		ret = SMT_WriteBlock(4, 0, ucBuf2);
		if (ret != 0)
		{
			DEBUG_CARD_MSGOUT(ret, "写主钱包失败");
				return -1009;
		}
	}

	return 0;	
}

/*================================================================ 
* 函数名：    SMT_ReadSubsidy
* 参数：      [in] (int *batch_no)	批次号
* 功能描述:   读补助信息: 以钱包扇区批次号为准              
* 返回值：    int, 正确返回0, 失败返回其他值
================================================================*/
int __stdcall SMT_ReadSubsidy(int *batch_no)
{
	int ret = 0;
	int i = 0;
	unsigned char check = 0;
	unsigned char buf_main[16] = "";
	unsigned char buf_backup[16] = "";

	ret = Login_Card(4);
	if (ret != 0)
	{
		return -1001;
	}

	ret = SMT_ReadBlock(4, 0, buf_main);			// 大钱包扇区
	if (ret != 0)
	{
		DEBUG_CARD_MSGOUT(ret, "读取主钱包块失败");
			return -1002;
	}

	for (i = 0; i < 15; i++)
		check += buf_main[i];

	if (check == buf_main[15])
	{
		*batch_no = buf_main[13] * 256 + buf_main[14];	// packet_batch_no[0] * 256 + packet_batch_no[1];
	}
	else	
	{
		ret = SMT_ReadBlock(4, 2, buf_backup);
		if (ret != 0)
		{
			DEBUG_CARD_MSGOUT(ret, "读取主钱包备份块失败");
				return ret;
		}

		check = 0;
		for (i = 0; i < 15; i++)
			check += buf_backup[i];

		if (check == buf_backup[15])
		{
			*batch_no = buf_backup[13] * 256 + buf_backup[14];
		}
		else
		{
			DEBUG_CARD_MSGOUT(ret, "备份块主校验和计算有误");
				return 2;
		}
	}

	return 0;
}

int __stdcall YKTSVR_Login()
{
	if (GW_Login) return GW_Login();
	return 0;
}

int __stdcall YKTSVR_Create()
{
	if (GW_CreateNewHandle)	return GW_CreateNewHandle();
	return 0;
}

int __stdcall YKTSVR_Close()
{
	if (GW_CloseHandle) return GW_CloseHandle();
	return 0;
}

int __stdcall YKTSVR_Exit()
{
	if (GW_Exit) return GW_Exit();
	return 0;
}

int __stdcall YKTSVR_GetCardInfo(char physical_no[9], CardInfo *card_info)
{
	if (GW_GetCardInfo) return GW_GetCardInfo(physical_no, card_info);
	return 0;
}

int __stdcall YKTSVR_GetCustomerInfo(int cut_id, CutInfo *card_info)
{
	if (GW_GetCustomerInfo) return GW_GetCustomerInfo(cut_id, "", card_info);
	return 0;
}

int __stdcall YKTSVR_GetDataInfo(char physical_no[9],  char stuemp_no[22], DataInfo *data_info)
{
	if (!GW_GetCardInfo) return 0;
		
	if (!GW_GetCustomerInfo) return 0;

	if (!GW_GetCustomerInfo) return 0;

	int ret = 0;
	CardInfo card_info;
	CutInfo cut_info;
	memset(&card_info, 0, sizeof(card_info));
	memset(&cut_info, 0, sizeof(cut_info));

	if (NULL == physical_no || NULL == stuemp_no) { return KS_ERR_INPUTNULLFAILED; }
	
	if (memcmp(physical_no, "", sizeof(physical_no) - 1) != 0)
	{
		if (ret = GW_GetCardInfo(physical_no, &card_info)) { return ret; }
		if (ret = GW_GetCustomerInfo(card_info.customer_id, stuemp_no, &cut_info)) { return ret; }
	}
	else
	{
		if (memcmp(stuemp_no, "", sizeof(stuemp_no) - 1) != 0)
		{
			if (ret = GW_GetCustomerInfo(card_info.customer_id, stuemp_no, &cut_info)) { return ret; }
		}
	}

	data_info->cut_id = card_info.customer_id;
	memcpy(data_info->classdept_name, cut_info.classdept_name, sizeof(data_info->classdept_name));
	memcpy(data_info->class_no, cut_info.class_no, sizeof(data_info->class_no));
	memcpy(data_info->cut_name, cut_info.cut_name, sizeof(data_info->cut_name));
	memcpy(data_info->classdept_no, cut_info.classdept_no, sizeof(data_info->classdept_no));

	return 0;
}

int __stdcall YKTSVR_SetCardKey()
{
	if (!GW_GetSeedKey) return 0;

	int ret = 0;
	char seed_key[17] = "";
	if (ret = GW_GetSeedKey(seed_key)) { return ret; }
	Load_WorkKey(seed_key);

	return 0;
}

int __stdcall RefineCardSector(int sector, unsigned char login_key[7])
{
	CardKeyData card_key[4];
	unsigned char card_id[5] = "";
	unsigned char card_type[2] = "";
	unsigned char card_key_a[7] = "";
	unsigned char card_key_b[7] = "";
	unsigned char sect_data[17] = "";
	int key_pos = 0;
	int ret = 0;

	// 读取授权密钥
	if( FALSE == Read_Author_Key())
	{
		return E_MAIN_KEY_ERROR;
	}
	// 检查卡是否存在
	if (SMT_RequestCardExist(card_id, card_type) != 0 )
	{
		return E_READ_CARD_ERROR;
	}

	// 计算卡的 keyA , keyB
	if (gen_user_card_keyA(SMT_UCWORKINGKEY, card_id
		, card_key_a) != 0)
	{
		return E_GEN_CARD_KEY_A_ERROR;
	}
	
	if (gen_user_card_keyB(SMT_UCWORKINGKEY,card_id
		,card_key_b) != 0)
	{
		return E_GEN_CARD_KEY_B_ERROR;
	}

	// 初始化 key 的数组
	memset((void *)card_key,0,sizeof(card_key));

	card_key[0].flag = CARD_KEY_A;
	// 这里位置可以作为初始化卡时候的修改过的KEYA
	memcpy(card_key[0].key, CARD_INIT_KEY, sizeof(CARD_INIT_KEY));

	card_key[1].flag = CARD_KEY_A;
	memcpy(card_key[1].key, card_key_a, sizeof(card_key_a));

	card_key[2].flag = CARD_KEY_B;
	memcpy(card_key[2].key, card_key_b, sizeof(card_key_b));
	
	card_key[3].flag = CARD_KEY_B;
	memcpy(card_key[3].key, login_key, sizeof(card_key_b));

	if (LoginCardSect(sector, card_key[2].key
		,card_key[2].flag, card_type) == 0)
	{
		key_pos = 2;
	}
	else if (LoginCardSect(sector, card_key[1].key
		,card_key[1].flag, card_type) == 0)
	{
		key_pos = 1;
	}
	else if (LoginCardSect(sector, card_key[3].key
		,card_key[3].flag, card_type) == 0)
	{
		key_pos = 3;
	}
	else if (LoginCardSect(sector, card_key[0].key
		,card_key[0].flag, card_type) == 0)
	{
		key_pos = 0;
	}
	else
	{
		return E_CARD_LOGIN_ERROR;
	}

	memset(sect_data, 0, sizeof(sect_data));
	// key A, 这里可以在回收的时候写入KEYA
	memcpy(sect_data, CARD_INIT_KEY, CARD_KEY_LEN);
	// control bit
	memcpy(sect_data + CARD_KEY_LEN, CARD_INIT_CTRL_BIT, sizeof(CARD_INIT_CTRL_BIT));
	// key B
	memcpy(sect_data + CARD_KEY_LEN + sizeof(CARD_INIT_CTRL_BIT), CARD_INIT_KEY, CARD_KEY_LEN);
	
	if (ret = WriteCardData(sector, PASSWD_BLOCK_NUM, sect_data)) { return ret; }

	return 0;
}

int __stdcall SMT_ReadStuempNo(unsigned char stuemp_no[21])
{
	int ret;
	unsigned char ucBuffer[16];
	//工号学号操作
	ret = Login_Card_Keyb(0);
	if (ret != 0)	return ret;
	
	ret = SMT_ReadBlock(0, 1, ucBuffer);
	if (ret != 0)	return -6;
	
	memcpy(stuemp_no, ucBuffer,16);
	
	ret = SMT_ReadBlock(0, 2, ucBuffer);
	if (ret != 0)	return -6;
	
	memcpy(stuemp_no + 16, ucBuffer, 4);	
	return 0;
}

int __stdcall THIRD_PacketDelMoney(int money, int &flow_no)
{
	int ret = 0;
	if (KS_READER == dll_flag)
	{
		ret = SMT_PacketDelMomey(1, money);
		flow_no = 0;
	}
	else
	{
		ret = POS_PacketDelMoney(money, flow_no);
	}

	RET_ERROR(ret, "扣款失败")

	return 0;
}

int __stdcall THIRD_ReadBalance(int &money)
{
	int ret = 0;
	int cnt = 0;
	if (KS_READER == dll_flag)
	{
		ret = ReadBalance(1, &money, &cnt);
	}
	else
	{
		ret = POS_ReadBalance(money);
	}
	
	RET_ERROR(ret, "读取余额失败")
	return 0;
}

int __stdcall THIRD_MendPacket(int &bmoney, int &amoney)
{
	int ret = 0;
	if (KS_READER == dll_flag)
	{
		return 0;
	}
	else
	{
		ret = POS_MendPacket(bmoney, amoney);
	}

	RET_ERROR(ret, "卡余额冲正")
	return 0;
}

int __stdcall THIRD_ControlBuzzer()
{
	int ret = 0;
//	FUNC0(SMT_ControlBuzzer, POS_ControlBuzzer, dll_flag, ret)
	int beep = 0x000F;
	if (KS_READER == dll_flag)
	{
		return SMT_ControlBuzzer();
	}
	else
	{
		ret = POS_ControlBuzzer(beep);
	}

	RET_ERROR(ret, "设备鸣叫失败")
	return 0;
}

int __stdcall THIRD_ReadStuempNo(unsigned char stuemp_no[21])
{
	int ret = 0;
	FUNC1(SMT_ReadStuempNo, POS_ReadStuempNo, dll_flag, stuemp_no, ret)
	RET_ERROR(ret, "读取学工号失败");

	return 0;
}

int __stdcall THIRD_ReadSerial(unsigned char serial[5])
{
	int ret = 0;
	FUNC1(ReadSerial, POS_ReadSerial, dll_flag, serial, ret)
	RET_ERROR(ret, "读取物理卡号失败");

	return 0;
}

int __stdcall THIRD_ReadCardNO(int nCardNo[1])
{
	int ret = 0;
	FUNC1(ReadCardNO, POS_ReadCardNO, dll_flag, nCardNo, ret)
	RET_ERROR(ret, "读取交易卡号失败");

	return 0;
}

int __stdcall THIRD_GetLastRecord(POSRECORD *pCardRecord)
{
	int ret = 0;
	if (KS_READER == dll_flag)
	{
		return 0;
	}
	else
	{
		ret = GetLastRecord(pCardRecord);
	}

	RET_ERROR(ret, "获取POS机最后一笔流水失败")
	return 0;
}

int __stdcall THIRD_ConnectMF(int port, int baud, int hwnd)
{
	int ret = 0;
	pos_hwnd = hwnd;
	if (KS_POS == dll_flag) 
	{ 
		if (ret = Load_Dll()) { return ret; }
		ret = POS_ConnectMF(port, baud, hwnd);
		strcpy(msg, "打开POS机串口失败");
	}
	else
	{ 
		ret = ConnectMF(port, baud);
		strcpy(msg, "打开读卡器串口失败");
	}
	RET_ERROR(ret, msg);

	return 0;
}