#include "stdafx.h"
#include "CardDLL.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
int InitInstance();
int ifReadyOK();
//int isConnectMF = -1;    //判断读写器是否成功初始化
static int	ErrCode;
static char ErrMsg[256];

// 来自于SMARTCOM411DXQ.dll
unsigned char SMT_UCWORKINGKEY[256]="";
int nAutoFlag = 0;

// 来自于COMM.H的数据结构

// 来自于COMM.H的数据结构

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
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
typedef INT (CALLBACK* LPSMT_ConnectMF280)(int ,int);
typedef INT (CALLBACK* LPSMT_ControlBuzzer)(void);
typedef INT (CALLBACK* LPSMT_CloseMF280)(void);	
// typedef INT (CALLBACK* LPSMT_CreateGreyCard)(BOOL bPersonalFlag,BOOL bStateFlag, BOOL bBankInfo,BOOL bPacketFlag[8]);
// typedef INT (CALLBACK* LPSMT_WriteCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
// typedef INT (CALLBACK* LPSMT_PacketAddMomey)(int ,int );
// typedef INT (CALLBACK* LPSMT_PacketSetMoney)(int ,int );
// typedef INT (CALLBACK* LPSMT_AutoDll)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_JudgeAutoFlag)();
typedef INT (CALLBACK* LPSMT_RequestCardExist)(unsigned char *,unsigned char *);
// typedef INT (CALLBACK* LPSMT_ReadCardStateInfo)(unsigned char ucShowCardNo[5],int nDealCardNo[1],unsigned char ucDeadLineDate[3],unsigned char ucCardRightType[1]);
// typedef INT (CALLBACK* LPSMT_WritePersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo[20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1], unsigned char ucCardNo[20]);
// typedef INT (CALLBACK* LPSMT_ReadPersonalInfo)(unsigned char ucName[8],unsigned char ucDutyNo[4],unsigned char ucCertificateNo [20],unsigned char ucDepartmentNo[10],unsigned char ucIdentifyNo[4],unsigned char ucSexNo[1] ,unsigned char ucCardNo[20]);
// typedef INT (CALLBACK* LPSMT_ChangeName)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ChangeDutyNo)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ChangeCerificateNo)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ChangeDepartmentNo)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ChangeIdentifyNo)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ChangeSexNo)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ReadPacketInfo)(int,LOOPPURSEINFO *LoopPurseInfo);
// typedef INT (CALLBACK* LPSMT_ChangeDeadLineDate)(unsigned char *);
// typedef INT (CALLBACK* LPSMT_ChangeCardRightType)(unsigned char ucCardRightType[1]);
// typedef INT (CALLBACK* LPSMT_WritePersonalPassword)(unsigned char PersonalPsd[3]);
// typedef INT (CALLBACK* LPSMT_ReadPersonalPassword)(unsigned char PersonalPsd[3]);
// typedef INT (CALLBACK* LPSMT_ClearCard)();
typedef INT (CALLBACK* LPSMT_SleepCard)();
typedef void (CALLBACK* LPSMT_Cal_KeyA)(unsigned char *ucRawData, unsigned char *ucSerialNo, unsigned char *ucDesData, unsigned char *ucKeyA);
typedef void (CALLBACK* LPSMT_Cal_KeyB)(unsigned char *ucRawData, unsigned char *ucSerialNo, unsigned char *ucDesData, unsigned char *ucKeyB);
typedef void (CALLBACK* LPSetLastErrMsg)(int err_code,char* format, ...);
typedef void (CALLBACK* LPGetMFLastErr)();
typedef INT	(CALLBACK* LPMF_ReadSeriesNo)(unsigned char *Buffer);
typedef INT (CALLBACK* LPSMT_ExeCommand)(unsigned char *Buffer,int Len);
typedef INT (CALLBACK* LPSMT_Login_With_UserKey)(int Sector, unsigned char *Buffer, int PaDSelect);
typedef INT (CALLBACK* LPSMT_WriteBlock)(int Sector,int BlockNo,unsigned char *BlockBuf);
typedef INT (CALLBACK* LPLogin_Card)(int sector);
typedef INT (CALLBACK* LPSMT_ReadBlock)(int Sector,int BlockNo, unsigned char *BlockBuf);
typedef void (CALLBACK* LPSMT_CopyWorkingKey)(unsigned char *SMT_UCWORKINGKEY);
// typedef INT (CALLBACK* LPSMT_WriteLibraryNo)(unsigned char ucLibraryNo[13]);
// typedef INT (CALLBACK* LPSMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
// typedef INT (CALLBACK* LPSMT_ChangeCardNo)(unsigned char ucCardNo[20]);
// typedef INT (CALLBACK* LPSMT_ChangeShowCardNo)(unsigned char ucShowCardNo[5]);

//typedef INT (CALLBACK* LPSMT_SMT_ReadLibraryNo)(unsigned char ucLibraryNo[13]);
LPSMT_ConnectMF280				SMT_ConnectMF280=NULL;
LPSMT_ControlBuzzer				SMT_ControlBuzzer=NULL;
LPSMT_CloseMF280				SMT_CloseMF280=NULL;
// LPSMT_CreateGreyCard			SMT_CreateGreyCard=NULL;
// LPSMT_WriteCardStateInfo		SMT_WriteCardStateInfo=NULL;
//LPSMT_AutoDll					SMT_AutoDll=NULL;
//LPSMT_JudgeAutoFlag				SMT_JudgeAutoFlag=NULL;
LPSMT_RequestCardExist			SMT_RequestCardExist=NULL;
//LPSMT_ReadCardStateInfo			SMT_ReadCardStateInfo=NULL;
//LPSMT_WritePersonalInfo			SMT_WritePersonalInfo=NULL;
//LPSMT_ReadPersonalInfo			SMT_ReadPersonalInfo=NULL;
//LPSMT_WriteLibraryNo			SMT_WriteLibraryNo=NULL;
//LPSMT_ReadLibraryNo				SMT_ReadLibraryNo=NULL;
//LPSMT_ChangeName				SMT_ChangeName=NULL;
//LPSMT_ChangeDutyNo				SMT_ChangeDutyNo=NULL;
//LPSMT_ChangeCerificateNo		SMT_ChangeCerificateNo=NULL;
//LPSMT_ChangeDepartmentNo		SMT_ChangeDepartmentNo=NULL;
//LPSMT_ChangeIdentifyNo			SMT_ChangeIdentifyNo=NULL;
//LPSMT_ChangeSexNo				SMT_ChangeSexNo=NULL;
//LPSMT_ChangeCardNo				SMT_ChangeCardNo=NULL;
//LPSMT_ChangeDeadLineDate		SMT_ChangeDeadLineDate=NULL;
//LPSMT_ChangeCardRightType		SMT_ChangeCardRightType=NULL;
//LPSMT_WritePersonalPassword		SMT_WritePersonalPassword=NULL;
//LPSMT_ReadPersonalPassword		SMT_ReadPersonalPassword=NULL;

//钱包操作
//LPSMT_PacketSetMoney     SMT_PacketSetMoney=NULL;
//LPSMT_PacketAddMomey     SMT_PacketAddMomey=NULL;
//LPSMT_ReadPacketInfo	 SMT_ReadPacketInfo=NULL;
//LPSMT_ClearCard		 SMT_ClearCard=NULL;
LPSMT_SleepCard		 SMT_SleepCard=NULL;
// LPSMT_ChangeShowCardNo	SMT_ChangeShowCardNo=NULL;

// 登陆卡
LPLogin_Card Login_Card = NULL;
LPSMT_Login_With_UserKey SMT_Login_With_UserKey = NULL;

// 执行命令操作
LPSMT_ExeCommand SMT_ExeCommand = NULL;

// 对密码的计算(A或者B)
LPSMT_Cal_KeyA SMT_Cal_KeyA = NULL;
LPSMT_Cal_KeyB SMT_Cal_KeyB = NULL;

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

//FreeLibrary(hDLL);
void SetErrMsg(int ecode,char *errmsg)
{
	ErrCode=ecode;;
	strcpy(ErrMsg,errmsg);
}

int __stdcall GetLastErrMsg(int ecode[1],char *errmsg)
{
	ecode[0]=ErrCode;
	strcpy(errmsg,ErrMsg);
	return 0;
}

int __stdcall dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}

int __stdcall bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 新入计算函数
void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}

void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

// 改变第三个参数unsigned char* 到 char*
int  bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr)
{	
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////

int __stdcall ConnectMF(int com,int baud)
{
	int ret = 0;
	if(hDLL==NULL)
	{
		ret=Load_Dll();
		if(ret)
			return -1;
	}
	if (com < 1)
	{
		com = 1;       //默认串口1
	}
	if (baud < 1)
	{
		baud = 19200;  //默认19200
	}
	SMT_CloseMF280();
	ret = SMT_ConnectMF280(com,baud);
	if(ret!= 0)
	{
		char  sEmsg[256]="";
		sprintf(sEmsg,"连接到COM%d失败",com);
		SetErrMsg(ret,sEmsg);
		return ret;
	}
	SMT_ControlBuzzer();

	return 0;
}

int __stdcall CloseMF(void)
{
	int ret = 0;

	ret = SMT_CloseMF280();
	if(ret)
	{
		SetErrMsg(ret,"关闭串口失败");
		return ret;
	}
//	isConnectMF=-1;
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
//	if (isConnectMF) return isConnectMF;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;
	/*
	if(pc->isFormat=='Y'||pc->isFormat=='y')
	{
		ret = SMT_CreateGreyCard(bPersonalFlag,bStateFlag,bBankInfo,bPacketFlag);
		if(ret != 0)
		{
			sprintf(szMsg,"初始化卡失败,ret %d",ret);
			MessageBox(NULL,szMsg,"错误",0);		
			return ret;
		}
	}
	*/
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
//	if (isConnectMF) return isConnectMF;

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
//	if (isConnectMF) return isConnectMF;
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

//	if (isConnectMF) return isConnectMF;
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

int __stdcall RedCardInfo(TPublishCard *pc)
{
	int ret = 0; 
	unsigned char ucBcdShowCardNo[5];
	unsigned char ucDeadLineDate[3];		//用户卡使用截止日期
	unsigned char ucCardRightType[1];		//权限位
	int iCardNo[1];

//	if (isConnectMF) return isConnectMF;

	ret = ifReadyOK();
	if (ret !=0)
		return ret;


	memset(pc,0,sizeof(TPublishCard));

	ret = SMT_ReadCardStateInfo(ucBcdShowCardNo,iCardNo,ucDeadLineDate,ucCardRightType);
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
	ret = SMT_ChangeName(CardInfo->ucName);							//修改姓名
	if(ret != 0)
	{
		SetErrMsg(ret,"修改姓名时出错");
		return ret;	
	}
	ret = SMT_ChangeDutyNo(CardInfo->ucDutyNo);						//修改职务代码
	if(ret != 0)
	{
		SetErrMsg(ret,"修改职务代码时出错");
		return ret;
	}
	ret = SMT_ChangeCerificateNo(CardInfo->ucCertificateNo);		//修改证件号码
	if(ret != 0)
	{
		SetErrMsg(ret,"修改证件号码时出错");
		return ret;	
	}
	ret = SMT_ChangeDepartmentNo(CardInfo->ucDepartmentNo);			//修改部门编码
	if(ret != 0)
	{
		SetErrMsg(ret,"修改部门代码时出错");
		return ret;
	}
	ret = SMT_ChangeIdentifyNo(CardInfo->ucIdentifyNo);				//修改身份代码
	if(ret != 0)
	{
		SetErrMsg(ret,"修改身份代码时出错");
		return ret;
	}
	ret = SMT_ChangeSexNo(CardInfo->ucSexNo);						//修改性别代码
	if(ret != 0)
	{
		SetErrMsg(ret,"修改性别时出错");
		return ret;
	}
	ret = SMT_ChangeCardNo(CardInfo->ucCardNo);					//
	if(ret != 0)
	{
		SetErrMsg(ret,"修改学工号时出错");
		return ret;
	}
	ret = SMT_WriteLibraryNo(CardInfo->ucLibraryNo);	//
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
		ret = SMT_ChangeShowCardNo(ucBcdShowCardNo);	//
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

//	if (isConnectMF) return isConnectMF;

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

int __stdcall ReadCardNO(char *pCardNo)
{
	int ret = 0;
	int CardNo[1]={0};
	unsigned char sBcdShowCardNo[5];
	unsigned char ShowCardNo[11];			//用户卡显示卡号
	unsigned char DeadLineDate[3];			//用户卡使用截止日期
	unsigned char CardRightType[1];			//用户卡使用权限类型（1--254）

	memset(ShowCardNo,0,sizeof(ShowCardNo));
	memset(CardNo,0,sizeof(CardNo));
	memset(DeadLineDate,0,sizeof(DeadLineDate));

//	if (isConnectMF) return isConnectMF;
	
	ret = ifReadyOK();
	if (ret !=0)
		return ret;

	ret = SMT_ReadCardStateInfo(sBcdShowCardNo,CardNo,DeadLineDate,CardRightType);
	if (ret !=0)
	{
		SetErrMsg(ret,"读卡基本信息失败");
		return ret;     
	}
	sprintf(pCardNo,"%d",CardNo[0]);
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
	if(hDLL)
		return 0;
    hDLL = LoadLibrary("SmartCom411DXQ.dll");
	if(!hDLL)
	{
		SetErrMsg(-1,"装载SmartCom411DXQ.dll动态库失败");
		return -1;
	}

	SMT_ConnectMF280		 = (LPSMT_ConnectMF280)GetProcAddress(hDLL,"SMT_ConnectMF280");
	SMT_ControlBuzzer        = (LPSMT_ControlBuzzer)GetProcAddress(hDLL,"SMT_ControlBuzzer");
	SMT_CloseMF280           = (LPSMT_CloseMF280)GetProcAddress(hDLL,"SMT_CloseMF280");
//	SMT_CreateGreyCard       = (LPSMT_CreateGreyCard)GetProcAddress(hDLL,"SMT_CreateGreyCard");
//	SMT_WriteCardStateInfo   = (LPSMT_WriteCardStateInfo)GetProcAddress(hDLL,"SMT_WriteCardStateInfo");
//	SMT_PacketAddMomey       = (LPSMT_PacketAddMomey)GetProcAddress(hDLL,"SMT_PacketAddMomey");
//	SMT_PacketSetMoney       = (LPSMT_PacketSetMoney)GetProcAddress(hDLL,"SMT_PacketSetMoney");
// 	SMT_AutoDll				 = (LPSMT_AutoDll)GetProcAddress(hDLL,"SMT_AutoDll");
// 	SMT_JudgeAutoFlag  	     = (LPSMT_JudgeAutoFlag)GetProcAddress(hDLL,"SMT_JudgeAutoFlag");
    SMT_RequestCardExist  	 = (LPSMT_RequestCardExist)GetProcAddress(hDLL,"SMT_RequestCardExist");
//	SMT_ReadCardStateInfo  	 = (LPSMT_ReadCardStateInfo)GetProcAddress(hDLL,"SMT_ReadCardStateInfo");
//  SMT_WritePersonalInfo  	 = (LPSMT_WritePersonalInfo)GetProcAddress(hDLL,"SMT_WritePersonalInfo");
//	SMT_ReadPersonalInfo     = (LPSMT_ReadPersonalInfo)GetProcAddress(hDLL,"SMT_ReadPersonalInfo");
//	SMT_ChangeName           = (LPSMT_ChangeName)GetProcAddress(hDLL,"SMT_ChangeName");
//	SMT_ChangeDutyNo         = (LPSMT_ChangeDutyNo)GetProcAddress(hDLL,"SMT_ChangeDutyNo");
//	SMT_ChangeCerificateNo   = (LPSMT_ChangeCerificateNo)GetProcAddress(hDLL,"SMT_ChangeCerificateNo");
//	SMT_ChangeDepartmentNo   = (LPSMT_ChangeDepartmentNo)GetProcAddress(hDLL,"SMT_ChangeDepartmentNo");
//	SMT_ChangeIdentifyNo     = (LPSMT_ChangeIdentifyNo)GetProcAddress(hDLL,"SMT_ChangeIdentifyNo");
//	SMT_ChangeSexNo          = (LPSMT_ChangeSexNo)GetProcAddress(hDLL,"SMT_ChangeSexNo");
//  SMT_ReadPacketInfo       = (LPSMT_ReadPacketInfo)GetProcAddress(hDLL,"SMT_ReadPacketInfo");
//	SMT_ChangeDeadLineDate   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hDLL,"SMT_ChangeDeadLineDate");
//	SMT_ChangeCardRightType  = (LPSMT_ChangeCardRightType)GetProcAddress(hDLL,"SMT_ChangeCardRightType");
//	SMT_WritePersonalPassword   = (LPSMT_ChangeDeadLineDate)GetProcAddress(hDLL,"SMT_WritePersonalPassword");
//	SMT_ReadPersonalPassword  = (LPSMT_ChangeCardRightType)GetProcAddress(hDLL,"SMT_ReadPersonalPassword");
	SMT_SleepCard            = (LPSMT_SleepCard)GetProcAddress(hDLL,"SMT_SleepCard");
	SMT_ExeCommand           = (LPSMT_ExeCommand)GetProcAddress(hDLL, "SMT_ExeCommand");	
	SMT_Cal_KeyA             = (LPSMT_Cal_KeyA)GetProcAddress(hDLL, "SMT_Cal_KeyA");
	SMT_Cal_KeyB             = (LPSMT_Cal_KeyB)GetProcAddress(hDLL, "SMT_Cal_KeyB");
	MF_ReadSeriesNo          = (LPMF_ReadSeriesNo)GetProcAddress(hDLL, "MF_ReadSeriesNo");
	SMT_Login_With_UserKey   = (LPSMT_Login_With_UserKey)GetProcAddress(hDLL, "SMT_Login_With_UserKey");
	SMT_WriteBlock           = (LPSMT_WriteBlock)GetProcAddress(hDLL, "SMT_WriteBlock");
	Login_Card               = (LPLogin_Card)GetProcAddress(hDLL, "Login_Card");
	SMT_ReadBlock            = (LPSMT_ReadBlock)GetProcAddress(hDLL, "SMT_ReadBlock");
    SetLastErrMsg            = (LPSetLastErrMsg)GetProcAddress(hDLL, "SetLastErrMsg");
	GetMFLastErr             = (LPGetMFLastErr)GetProcAddress(hDLL, "GetMFLastErr");
    SMT_CopyWorkingKey       = (LPSMT_CopyWorkingKey)GetProcAddress(hDLL, "SMT_CopyWorkingKey");
//	SMT_ClearCard			 = (LPSMT_ClearCard)GetProcAddress(hDLL,"SMT_ClearCard");
//	SMT_WriteLibraryNo		 = (LPSMT_WriteLibraryNo)GetProcAddress(hDLL,"SMT_WriteLibraryNo");
//	SMT_ReadLibraryNo		 = (LPSMT_ReadLibraryNo)GetProcAddress(hDLL,"SMT_ReadLibraryNo");
//	SMT_ChangeCardNo		 = (LPSMT_ChangeCardNo)GetProcAddress(hDLL,"SMT_ChangeCardNo");
//	SMT_ChangeShowCardNo	 = (LPSMT_ChangeShowCardNo)GetProcAddress(hDLL,"SMT_ChangeShowCardNo");
	if ((!SMT_ConnectMF280) ||
		(!SMT_ControlBuzzer) ||
		(!SMT_CloseMF280) ||
//		(!SMT_CreateGreyCard) ||
	//	(!SMT_WriteCardStateInfo) ||
        (!SMT_WriteBlock)  ||
		(!SMT_ReadBlock)   ||
		(!MF_ReadSeriesNo) ||
		(!SMT_Cal_KeyA) ||
		(!SMT_Cal_KeyB) || 
		(!SMT_ExeCommand) ||
//		(!SMT_PacketAddMomey) ||
//		(!SMT_PacketSetMoney) ||
		(!Login_Card)  ||
//		(!SMT_AutoDll) ||
//		(!SMT_JudgeAutoFlag) ||
		(!SMT_RequestCardExist) ||
//		(!SMT_ReadCardStateInfo) ||
//		(!SMT_WritePersonalInfo) ||
//		(!SMT_ReadPersonalInfo) ||
//		(!SMT_ChangeName) ||
//		(!SMT_ChangeDutyNo) ||
//		(!SMT_ChangeCerificateNo) ||
//		(!SMT_ChangeDepartmentNo) ||
//		(!SMT_ChangeIdentifyNo) ||
//		(!SMT_ChangeSexNo) ||
//		(!SMT_ReadPacketInfo) ||
//		(!SMT_ChangeDeadLineDate) ||
//		(!SMT_ChangeCardRightType) ||
//		(!SMT_WritePersonalPassword)||
//		(!SMT_ReadPersonalPassword)||
		(!SMT_Login_With_UserKey) ||
		(!SMT_SleepCard)||
		(!SetLastErrMsg)||
		(!GetMFLastErr) ||
		(!SMT_CopyWorkingKey)
//		(!SMT_ClearCard)
//		(!SMT_WriteLibraryNo)||
//		(!SMT_ReadLibraryNo)
//		(!SMT_ChangeCardNo)
//		(!SMT_ChangeShowCardNo)
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}
/************************************************************************/
/*           新添加的函数， 操作功能函数, 来源于SMARTCOM411DXQ          */
/************************************************************************/

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
	nAutoFlag = 1;
	SMT_CopyWorkingKey(SMT_UCWORKINGKEY);
	return 0;
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
	// void SMT_Cal_KeyA(unsigned char *ucRawData, unsigned char *ucSerialNo, unsigned char *ucDesData, unsigned char *ucKeyA) 
	SMT_Cal_KeyA(ucRawData, ucSerialNo, ucDesData, ucKeyA);
// 	memcpy(ucRawData,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i+4] = ~ucRawData[i];
// 	des_code(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_KeyA(ucDesData,ucKeyA);
	//////////////////////////////////////////////////////
//	Cal_Key(ucDesData, ucKeyA);
	//计算KEYB
	//////////////////////////////////////////////////////
	// void SMT_Cal_KeyB(unsigned char *ucRawData, unsigned char *ucSerialNo, unsigned char *ucDesData, unsigned char *ucKeyB)
	SMT_Cal_KeyB(ucRawData, ucSerialNo, ucDesData, ucKeyB);
// 	memcpy(ucRawData+4,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i] = ~ucRawData[i+4];
// 	TriDes(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_Key(ucDesData, ucKeyB);
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
//		ret = SMT_Login_With_UserKey(i,ucDesData,1);
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
	unsigned char ucSerialNo[5],ucRawData[256],ucDesData[256],ucKeyA[6];
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
		return -1;//卡片不在感应区
	//1 --- 计算KEYA
// 	memcpy(ucRawData,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i+4] = ~ucRawData[i];
// 	des_code(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_KeyA(ucDesData,ucKeyA);
//	Cal_Key(ucDesData, ucKeyA);
	SMT_Cal_KeyA(ucRawData, ucSerialNo, ucDesData, ucKeyA);
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
	ret = Login_Card(0);
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
	ret = Login_Card(0);
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
	ret = Login_Card(0);
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
		ucBuf1[5] = (BYTE)(tm.wYear - 2000); // tm.GetYear()-2000;
		ucBuf1[6] = (BYTE)tm.wMonth;       // tm.GetMonth();
		ucBuf1[7] = (BYTE)tm.wDay;         // tm.GetDay();
		ucBuf1[8] = (BYTE)tm.wHour;        // tm.GetHour();
		ucBuf1[9] = (BYTE)tm.wMinute;      // tm.GetMinute();
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
		ucBuf2[5] = (BYTE)(tm.wYear - 2000); // tm.GetYear()-2000;
		ucBuf2[6] = (BYTE)tm.wMonth;       // tm.GetMonth();
		ucBuf2[7] = (BYTE)tm.wDay;         // tm.GetDay();
		ucBuf2[8] = (BYTE)tm.wMonth;       // tm.GetHour();
		ucBuf2[9] = (BYTE)tm.wMinute;      // tm.GetMinute();
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
		if (tm.wDay != ucBuf2[7])                               // (tm.GetDay()!=ucBuf2[7])
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
		if (tm.wDay != ucBuf1[7])    // (tm.GetDay()!=ucBuf1[7])
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

// 函数功能: 设置卡标记
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

// 函数功能: 设置普通标记
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
	unsigned char ucRawData[256],ucDesData[256];
	
	int i,j,startSector=4;
	int ret;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
		return -1;//卡片不在感应区
	//1、使用出场密码登陆卡片  前32个扇区
	SMT_Cal_KeyA(ucRawData, ucSerialNo, ucDesData, ucKeyA);
// 	memcpy(ucRawData,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i+4] = ~ucRawData[i];
// 	des_code(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_KeyA(ucDesData,ucKeyA);
//	Cal_Key(ucDesData, ucKeyA);
	for(i=0;i<12;i++)
	{
		if(i==3)
			continue;
		ret = SMT_Login_With_UserKey(i,ucKeyA,0);
		if(ret != 0)
			return -2; //非出厂卡
		for(j=0;j<3;j++)
		{
			if(i==0&&j==0)
				continue;
			if(i == 1 && j == 0)
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
			ret=SMT_WriteBlock(i,j,ucRawData);
			if(ret)
				return -3;
		}
	}
	memset(ucRawData,0xFF,16);
	j = 0;
	for(i=0;i<4;i++)
	{
		ucRawData[j] = 0x00;
		j=j+1;
		ucRawData[j] = startSector;
		startSector+=1;
		j=j+1;
	}
	//1 使用用户密码登陆
	ret = SMT_Login_With_UserKey(3,ucKeyA,0);
	if(ret != 0)
		return -4;//使用用户密码KEYA不能登陆
	ret = SMT_WriteBlock(3,0,ucRawData);
	if(ret != 0)
		return -5;//无法写卡
	memset(ucRawData,0xFF,16);

	for(i=0;i<4;i++)
	{
		ucRawData[i] = startSector;
		startSector += 1;
	}
	ret = SMT_WriteBlock(3,1,ucRawData);
	if(ret != 0)
		return -6;//无法写卡
	memset(ucRawData,0xFF,16);  //20050305增加
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
	if(ret <= 0)
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
	unsigned char ucInitKeyA[6]="",ucInitKeyB[6]="";	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
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
	if(ret <= 0)
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
	unsigned char ucRawData[256],ucTmpRawData[16],ucDesData[256];
	int ret;
	int i;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
	{
		MessageBox(NULL, "卡片不在感应区", NULL, MB_OK);
		return -1;//卡片不在感应区
	}
	//1 --- 计算KEYA
	SMT_Cal_KeyA(ucRawData, ucSerialNo, ucDesData, ucKeyA);
// 	memcpy(ucRawData,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i+4] = ~ucRawData[i];
// 	des_code(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_KeyA(ucDesData,ucKeyA);
//	Cal_Key(ucDesData, ucKeyA);
	//计算KEYB
	SMT_Cal_KeyB(ucRawData, ucSerialNo, ucDesData, ucKeyB);
// 	memcpy(ucRawData+4,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i] = ~ucRawData[i+4];
// 	TriDes(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_Key(ucDesData,ucKeyB);
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
			if(ret <= 0)
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
			if(ret <= 0)
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
			if(ret <= 0)
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
			if(ret <= 0)
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
			if(ret <= 0)
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
			if(ret <= 0)
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
		if(ret <= 0)
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

// 函数功能: ????
// 函数参数: nPacketNo(钱包号), tx_cnt(???)
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

//////////////////////////////////////////////////////////////////////////
#define WATER_SECT_NO  0x0E
#define WATER_SECT_BLK_NO 1
static unsigned char s_water_temp_key[4] = {0x22,0x33,0x44,0x55};
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 计算函数
//////////////////////////////////////////////////////////////////////////
static unsigned char add_2(unsigned char add1, unsigned char add2)
{
	unsigned char ad1, ad2, sum;
	ad1 = add1;
	ad2 = add2;
	sum = (ad1 + ad2) % 0x100;
	return sum;
}

static void dess_ming(unsigned char key[4],unsigned char Source[4],unsigned char dest[4])
{
	unsigned char x0, x1, x2, x3, y0, y1, y2, y3, m, n, add1, add2;
	x0 = key[0];
	x1 = key[1];
	x2 = key[2];
	x3 = key[3];
	y0 = Source[0];
	y1 = Source[1];
	y2 = Source[2];
	y3 = Source[3];
	m = x0 ^ x1;
	add1 = m;
	add2 = y2;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	n = add_2(add1, add2);
	add1 = n;
	add2 = y3;
	n = add_2(add1, add2);
	m = m ^ y0;
	n = n ^ y1;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y2;
	n = n ^ y3;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x3;
	m = add_2(add1, add2); 
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = y3;
	add2 = x0 ^ x3;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = y2;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	add1 = m;
	add2 = x2 ^ x3;
	m = add_2(add1, add2);
	add1 = x2;
	add2 = x3;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = y1;
	add2 = x1 ^ x2;
	m = add_2(add1, add2);
	add1 = x1;
	add2 = x2;
	add1 = add_2(add1, add2);
	add2 = y0;
	n = add_2(add1, add2);
	m = m ^ y3;
	n = n ^ y2;
	y2 = m;
	y3 = n;
	add1 = m;
	add2 = x0 ^ x1;
	m = add_2(add1, add2);
	add1 = x0;
	add2 = x1;
	add1 = add_2(add1, add2);
	add2 = n;
	n = add_2(add1, add2);
	m = m ^ y1;
	n = n ^ y0;
	y0 = m;
	y1 = n;
	dest[0] = y0;
	dest[1]= y1;
	dest[2] = y2;
	dest[3] = y3;
}

static int gen_extra_keyA(unsigned char* key,unsigned char* text,unsigned char* keyA)
{
	unsigned int i;
	unsigned char sPlain[9] = "";
	unsigned char workKey[4] = "";
	memcpy(workKey,key,sizeof(workKey));
	for(i = 0;i < 4;++i)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
	}
	dess_ming(workKey,sPlain,keyA);
	dess_ming(workKey,sPlain+4,keyA+4);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 对于流水的操作
//////////////////////////////////////////////////////////////////////////

// 登陆流水片段
static int LoginWaterSection()
{
	unsigned char ucSerialNo[5];// = {0x11,0x22,0x33,0x44};
	unsigned char ucKey[8] = "";
	int ret = 1;
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
		return -1;//卡片不在感应区
	/*
	unsigned char workey[4] = {0x8E,0x8B,0xFC,0x8F};
	if(gen_extra_keyA(workey,ucSerialNo,ucKey))
		return -1;
	*/
	// FIXME : 
	if(gen_extra_keyA(s_water_temp_key,ucSerialNo,ucKey))
		return -1;
	
	if(SMT_Login_With_UserKey(WATER_SECT_NO,ucKey,0))
		return -2;
	return 0;
}

// 读取流水包信息
int __stdcall SMT_ReadWaterPackInfo(WATER_PACK_INFO* info)
{
	unsigned char ucBuffer[16] = "";
	int ret;
	ret = LoginWaterSection();
	if(ret)
		return -1;
	ret = SMT_ReadBlock(WATER_SECT_NO,WATER_SECT_BLK_NO,ucBuffer);
	if(ret)
		return -6;
	unsigned char termid[2] = "";
	memcpy(termid,ucBuffer,sizeof(info->termid));
	char buf[12] = "";
	if(bcd2decA(ucBuffer+4,3,buf))
		return -7;
	info->remain = atoi(buf);
	
	if(memcmp(termid,s_water_clear_card,2) == 0)
	{
		info->cardtype = WATER_CLEAR_CARD;
	}
	else if(memcmp(termid,s_water_new_card,2) == 0)
	{
		info->cardtype = WATER_NEW_CARD;
	}
	else if(memcmp(termid,s_water_common_card,2) == 0)
	{
		info->cardtype = WATER_COMMON_CARD;
	}
	else
	{
		info->cardtype = WATER_FIXED_CARD;
		memset(buf,0,sizeof(buf));
		bcd2decA(termid,2,buf);
		info->termid = atoi(buf);
	}
	memcpy(info->oldSerialNo,ucBuffer,4);
	return 0;
}

// 写入流水信息
int __stdcall SMT_WriteWaterPackInfo(WATER_PACK_INFO* info)
{
	unsigned char ucRawData[256] = "";
	char bcdtmp[16] = "";
	unsigned char termid[2] = "";

	switch(info->cardtype)
	{
	case WATER_CLEAR_CARD:
		memcpy(termid,s_water_clear_card,2);
		break;
	case WATER_NEW_CARD:
		memcpy(termid,s_water_new_card,2);
		break;
	case WATER_COMMON_CARD:
		memcpy(termid,s_water_common_card,2);
		break;
	case WATER_FIXED_CARD:
		sprintf(bcdtmp,"%d",info->termid);
		if(dec2bcd((unsigned char*)bcdtmp,termid,2))
			return -2;
		break;
	default:
		return -1;
	}

	if(LoginWaterSection())
	{
		return -2;
	}
	// 写数据
	memset(ucRawData,0,sizeof(ucRawData));
	memcpy(ucRawData,termid,sizeof(termid));
	memset(bcdtmp,0,sizeof(bcdtmp));
	sprintf(bcdtmp,"%.06d",info->remain);
	if(dec2bcd((unsigned char*)bcdtmp,ucRawData+4,strlen(bcdtmp)))
		return -3;
	if(SMT_WriteBlock(WATER_SECT_NO,WATER_SECT_BLK_NO,ucRawData))
	{
		return -4;
	}
	return 0;
}

// 设置流水容量
int __stdcall SMT_WaterSetCapability(int value)
{
	if(value < 0 || value > 99999)
		return -2;
	unsigned char ucBuffer[16] = "";
	int ret;
	ret = LoginWaterSection();
	if(ret)
		return -1;
	ret = SMT_ReadBlock(WATER_SECT_NO,WATER_SECT_BLK_NO,ucBuffer);
	if(ret)
		return -3;
	char buffer[20] = "";
	sprintf(buffer,"%.06d",value);
	if(dec2bcd((unsigned char*)buffer,ucBuffer+4,3))
		return -3;
	ret = SMT_WriteBlock(WATER_SECT_NO,WATER_SECT_BLK_NO,ucBuffer);
	if(ret)
		return -4;
	return 0;
}

// 登陆初始卡
static int LoginOriginalCard(int sect,int keytype = 1)
{
	unsigned char uckey[8];
	unsigned char ucSerialNo[5] = "";
	if(MF_ReadSeriesNo(ucSerialNo) <= 0)
		return -1;
	memset(uckey,0xFF,sizeof(uckey));
	if(SMT_Login_With_UserKey(sect,uckey,keytype))
		return -1;
	return 0;
}

// 初始化流水信息
int __stdcall SMT_InitWaterInfo(const WATER_PACK_INFO* info)
{
	unsigned char ucRawData[256] = "";
	unsigned char ucDesData[256] = "";
	unsigned char ucKeyA[8] = "";
	unsigned char ucKeyB[8] = "";
	unsigned char ucSerialNo[5] = "";
	char bcdtmp[16] = "";
	unsigned char termid[2] = "";
//	int i;
	switch(info->cardtype)
	{
	case WATER_CLEAR_CARD:
		memcpy(termid,s_water_clear_card,2);
		break;
	case WATER_NEW_CARD:
		memcpy(termid,s_water_new_card,2);
		break;
	case WATER_COMMON_CARD:
		memcpy(termid,s_water_common_card,2);
		break;
	case WATER_FIXED_CARD:
		termid[0] = ((info->termid&0xFF00)>>8);
		termid[1] = (info->termid&0xFF);
		//if(dec2bcd((unsigned char*)bcdtmp,termid,2))
		//	return -2;
		break;
	default:
		return -1;
	}
	int ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <= 0)
		return -1;//卡片不在感应区
	// FIXME : 使用授权密钥
	if(gen_extra_keyA(s_water_temp_key,ucSerialNo,ucKeyA))
		return -1;

	int needInit = 0;
	if(!Login_Card(WATER_SECT_NO))
	{
		//计算KEYB	
		SMT_Cal_KeyB(ucRawData, ucSerialNo, ucRawData, ucKeyB);
// 		memcpy(ucRawData+4,ucSerialNo,4);
// 		for(i=0;i<4;i++)
// 			ucRawData[i] = ~ucRawData[i+4];
// 		TriDes(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 		Cal_Key(ucDesData,ucKeyB);
//		Cal_Key(ucDesData, ucKeyA);
		// 使用 KeyB 登录先
		if(SMT_Login_With_UserKey(WATER_SECT_NO,ucKeyB,1))
			return -1;
		needInit = 1;
	}
	else if(!LoginOriginalCard(WATER_SECT_NO))
	{
		needInit = 1;
	}
	if(needInit)
	{
		// 初始化密钥扇区
		memset(ucRawData,0xFF,sizeof(ucRawData));
		memcpy(ucRawData,ucKeyA,sizeof(ucKeyA));
		memcpy(ucRawData+10,ucKeyB,sizeof(ucKeyB));
		ucRawData[6] = 0x7F;
		ucRawData[7] = 0x07;
		ucRawData[8] = 0x88;
		ucRawData[9] = 0x00;
		// 写密钥
		if(SMT_WriteBlock(WATER_SECT_NO,3,ucRawData))
		{
			return -1;
		}
	}
	if(LoginWaterSection())
	{
		return -2;
	}
	// 写数据
	memset(ucRawData,0,sizeof(ucRawData));
	memcpy(ucRawData,termid,sizeof(termid));
	memset(bcdtmp,0,sizeof(bcdtmp));
	sprintf(bcdtmp,"%.06d",info->remain);
	if(dec2bcd((unsigned char*)bcdtmp,ucRawData+4,3))
		return -3;
	memcpy(ucRawData+8,info->oldSerialNo,sizeof(info->oldSerialNo));
	if(SMT_WriteBlock(WATER_SECT_NO,WATER_SECT_BLK_NO,ucRawData))
	{
		return -4;
	}
	return 0;
}

// 流水认证
int __stdcall SMT_WaterNewAuthCard()                                      // 这里修改过_stdcall
{
	unsigned char keyA[6] = {0x48, 0x43, 0x43, 0x48, 0x43, 0x43};
	unsigned char keyB[6] = "";
	unsigned char ucSerialNo[5] = "";
	int ret;                                                              // ,i;
	unsigned char ucRawData[24] = "";
	unsigned char ucDesData[24] = "";
	
	ret = MF_ReadSeriesNo(ucSerialNo);
	if(ret <=0 )
		return -1;

	if(LoginOriginalCard(WATER_SECT_NO))
	{
		return -4;
	}
	
	// 计算 keyB
	SMT_Cal_KeyB(ucRawData, ucSerialNo, ucDesData, keyB);
// 	memcpy(ucRawData+4,ucSerialNo,4);
// 	for(i=0;i<4;i++)
// 		ucRawData[i] = ~ucRawData[i+4];
// 	TriDes(UCWORKINGKEY,ucRawData,ucDesData,'0');
// 	Cal_Key(ucDesData,keyB);
	memset(ucRawData,0xFF,sizeof(ucRawData));
	memcpy(ucRawData,keyA,sizeof(keyA));
	memcpy(ucRawData+10,keyB,sizeof(keyB));
	ucRawData[6] = 0x7F;
	ucRawData[7] = 0x07;
	ucRawData[8] = 0x88;
	ucRawData[9] = 0x00;
	SMT_WriteBlock(WATER_SECT_NO,3,ucRawData);
	if(SMT_Login_With_UserKey(WATER_SECT_NO,keyA,0))
	{
		if(LoginOriginalCard(WATER_SECT_NO,0))
		{
			return -4;
		}
		
		memset(ucRawData,0xFF,sizeof(ucRawData));
		memcpy(ucRawData,keyA,sizeof(keyA));
		memcpy(ucRawData+10,keyB,sizeof(keyB));
		ucRawData[6] = 0x7F;
		ucRawData[7] = 0x07;
		ucRawData[8] = 0x88;
		ucRawData[9] = 0x00;
		SMT_WriteBlock(WATER_SECT_NO,3,ucRawData);
		if(SMT_Login_With_UserKey(WATER_SECT_NO,keyA,0))
		{
			return -2;
		}
	}
	memset(ucRawData,0,sizeof(ucRawData));
	memcpy(ucRawData,s_water_auth_card,2);
	//FIXME: 
	memcpy(ucRawData+8,s_water_temp_key,4);
	if(SMT_WriteBlock(WATER_SECT_NO,WATER_SECT_BLK_NO,ucRawData))
	{
		return -3;
	}
	return 0;
}