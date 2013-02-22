#ifndef _KSCOMDEF_H_
#define _KSCOMDEF_H_

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

#define DCLR_KSFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_KSFUNC(name) \
	LP##name name = NULL;	\

#define LOAD_KSFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
	return -1;

DCLR_KSFUNC(int,Load_Dll,());
DCLR_KSFUNC(int,Load_WorkKey,(char *ascWorkKey));
DCLR_KSFUNC(int,PacketAddMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,PacketDecMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,PacketSetMoney,(int nPacketNo,int nMoney));
DCLR_KSFUNC(int,ReadBalance,(int nPacketNo,int nBalance[1],int nCnt[1]));
DCLR_KSFUNC(int,ReadCardNo,(int nCardNo[1]));
DCLR_KSFUNC(int,SetBlackCardFlag,());
DCLR_KSFUNC(int,ComInit,(char *_ComType,int _Syn));
DCLR_KSFUNC(int,COMClose,());
DCLR_KSFUNC(int,ReadSerial,(unsigned char* serial));
DCLR_KSFUNC(int,SetNormalFlag,());
DCLR_KSFUNC(int,ChangePassWord,(unsigned char * newpwd));
DCLR_KSFUNC(int,UpdateCardInfo,(TPublishCard *CardInfo));
DCLR_KSFUNC(int,ReadInfoFromCard,(TPublishCard *pc));

#endif