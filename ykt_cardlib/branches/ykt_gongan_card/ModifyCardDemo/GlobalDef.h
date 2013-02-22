#ifndef _GLOBAL_DEFINE_H_
#define _GLOBAL_DEFINE_H_

#include "ExceptionErr.h"

#ifdef __cplusplus
extern "C" {
#endif

extern CExceptionErr err_exce;

//////////////////////////////////////////////////////////////////////////
// DATA STRUCT
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

#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
		return err_exce.SearchErr(KS_ERR_LOADFUNC_ADDRESS);
	
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
	{KS_ERR_EXIT, "无此类错误信息"}
};

//////////////////////////////////////////////////////////////////////////
// IMPORT FUNCTION
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

#ifdef __cplusplus
}
#endif

#endif