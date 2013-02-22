#include "stdafx.h"
#include "stdlib.h"

#pragma  pack(1)
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
#pragma  pack()

// FunDan_V23设备需要的底层硬件
int icdev = -1;
int g_Port = 0;

typedef int (__stdcall* lp_SMT_FUDAN_ReadMoney)(int ComPort,int &nMoney);
typedef int (__stdcall* lp_SMT_FUDAN_DecCard)(int ComPort,int DecMoney,int &nFlowNo);
typedef int (__stdcall* lp_SMT_FUDAN_ReadCardBlock)(int ComPort, unsigned char *Data, char cSector, char cBlock);
typedef int (__stdcall* lp_IniCom)(int ComPort,int BaudRate);
typedef int (__stdcall* lp_CloseCom)(int ComPort);
typedef int (__stdcall* lp_SMT_FUDAN_Beep)(int ComPort,char cBeep);
typedef int (__stdcall* lp_SMT_FUDAN_Mend)(int ComPort,int &BnMoney,int &AnMoney);

HINSTANCE						hDLL = NULL;
lp_SMT_FUDAN_ReadMoney			SMT_FUDAN_ReadMoney = NULL;
lp_SMT_FUDAN_DecCard			SMT_FUDAN_DecCard = NULL;
lp_SMT_FUDAN_ReadCardBlock		SMT_FUDAN_ReadCardBlock = NULL;
lp_IniCom						IniCom = NULL;
lp_CloseCom						CloseCom = NULL;
lp_SMT_FUDAN_Beep				SMT_FUDAN_Beep = NULL;
lp_SMT_FUDAN_Mend				SMT_FUDAN_Mend = NULL;

//////////////////////////////////////////////////////////////////////////
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

int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
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

int bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr)
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

// 改变第三个参数unsigned char* 到 char*
int bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr)
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

int SMT_LoadDll()
{
	if (hDLL)
	{
		return 0;
	}
	hDLL = LoadLibrary("SmartCom411SFJ.dll");
	if (!hDLL)
	{
		return -1;
	}
	SMT_FUDAN_ReadMoney			= (lp_SMT_FUDAN_ReadMoney)GetProcAddress(hDLL, "SMT_FUDAN_ReadMoney");
	SMT_FUDAN_DecCard			= (lp_SMT_FUDAN_DecCard)GetProcAddress(hDLL, "SMT_FUDAN_DecCard");
	SMT_FUDAN_ReadCardBlock     = (lp_SMT_FUDAN_ReadCardBlock)GetProcAddress(hDLL, "SMT_FUDAN_ReadCardBlock");
	IniCom						= (lp_IniCom)GetProcAddress(hDLL,"IniCom");
	CloseCom					= (lp_CloseCom)GetProcAddress(hDLL,"CloseCom");
	SMT_FUDAN_Beep				= (lp_SMT_FUDAN_Beep)GetProcAddress(hDLL, "SMT_FUDAN_Beep");	
	SMT_FUDAN_Mend				= (lp_SMT_FUDAN_Mend)GetProcAddress(hDLL, "SMT_FUDAN_Mend");		
	if (
		(!SMT_FUDAN_ReadMoney) ||
		(!SMT_FUDAN_DecCard) ||
		(!SMT_FUDAN_ReadCardBlock) ||
		(!IniCom) ||
		(!CloseCom) ||
		(!SMT_FUDAN_Beep) ||
		(!SMT_FUDAN_Mend) 
		)
	{
		FreeLibrary(hDLL);
		hDLL = NULL;
		return -2;
	}
	return 0;
}

// 函数功能: 蜂鸣
// 函数参数: 无
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_ControlBuzzer()
{
	int ret = 0;
	if (icdev)
	{
		return icdev;
	}
	// 鸣叫次数最大不超过0x10
	ret = SMT_FUDAN_Beep(g_Port, 1);
	return 0;
}

// 函数功能: 打开串口
// 函数参数: port(端口号), baud(波特率)
/*	波特率参数：
0	19200         
1	9600
2	600
3	1200
4	2400
5	4800
6	14400
7	57600
*/
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_ConnectMF280(int port, int baud)
{
	int ret = 0;
	ret = SMT_LoadDll();
	if(ret)
		return ret;
	g_Port = port;
	icdev = IniCom(g_Port, baud);
	if(icdev < 0)
	{
		return  icdev;
	}
	return 0;
}

int _stdcall SMT_CloseMF280()
{
	int ret = 0;
	ret = CloseCom(g_Port);
	if (ret)
	{
		return ret;
	}
	return 0;
}

// 函数功能: 从钱包里面扣钱
// 函数参数: nMoney(钱数目), nFlowNo(流水终端号)
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_PacketDelMomey(int nMoney,int &nFlowNo)
{
	int ret = 0;
	if (icdev)
	{
		return icdev;
	}
	ret =  SMT_FUDAN_DecCard(g_Port, nMoney, nFlowNo);
	if (ret)
	{
		return ret;
	}
	return 0;
}

// 函数功能: 从钱包读取卡余额
// 函数参数: nMoney(钱数目)
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_ReadBalance(int &nMoney)
{
	int ret = 0;
	if (icdev)
	{
		return icdev;		
	}
	ret = SMT_FUDAN_ReadMoney(g_Port, nMoney);
	if (ret)
	{
		return ret;
	}
	return 0;
}

// 函数功能: 卡片冲正
// 函数参数: BnMoney(冲正前余额), AnMoney(冲正后余额)
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_MendPacket(int &BnMoney,int &AnMoney)
{
	int ret = 0;
	if (icdev)
	{
		return icdev;
	}
	ret = SMT_FUDAN_Mend(g_Port, BnMoney, AnMoney);
	if (ret)
	{
		return ret;
	}
	return 0;
}

// 函数功能: 读取卡信息
// 函数参数: TPublishCard结构体(传入参数很多看结构说明)
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_ReadCardInfo(TPublishCard *pc)
{
	int ret = 0;
	unsigned char ucTempBuffer[128] = "";
	unsigned char ucBuffer[256] = "";
	unsigned char ucBcdShowCardNo[5];							 // 显示卡号 
	unsigned char ucDeadLineDate[3];							 // 用户卡使用截止日期
	unsigned char ucCardRightType[1];							 // 权限位
	int nDealCardNo[1];											 // 用户交易卡号(需要转一道)
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x01, 0x00); // 第一扇区第零块
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// 交易卡号
	nDealCardNo[0] = ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2];
	// 卡权限类型
	ucCardRightType[0] = ucBuffer[3];
	// 卡截止日期
	memcpy(ucDeadLineDate, ucBuffer + 4, 3);
	// 显示卡号
	memcpy(ucBcdShowCardNo,ucBuffer + 7, 5);
	bcd2dec(ucBcdShowCardNo, 5, pc->ShowCardNo);
	sprintf((char*)pc->DeadLineDate, "20%02d%02d%02d", ucDeadLineDate[0], ucDeadLineDate[1], ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo, "%d", nDealCardNo[0]);
	pc->CardRightType = ucCardRightType[0];
	// 学工号
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x00, 0x01); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	memcpy(pc->ucCardNo, ucBuffer, 16);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x00, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	memcpy(pc->ucCardNo + 16, ucBuffer, 4);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x00); // ucBuffer to ucBuffer1
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// 持卡人名字
	memcpy(pc->ucName, ucBuffer, 8);
	// 职位代码
	memcpy(pc->ucDutyNo, ucBuffer + 8, 4);
	// 证件号码
	memcpy(pc->ucCertificateNo, ucBuffer + 12, 4);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x01); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// 证件号码后面16个字节
	memcpy(pc->ucCertificateNo + 4, ucBuffer, 16);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// 部门号码
	memcpy(pc->ucDepartmentNo, ucBuffer, 10);
	// 身份证号码
	memcpy(pc->ucIdentifyNo, ucBuffer + 10, 4);
	// 性别
	memcpy(pc->ucSexNo, ucBuffer + 14, 1);

	return 0;
}

// 函数功能: 读取学工号
// 函数参数: ucCardNo(学工号数组)
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_ReadCardNo(unsigned char ucCardNo[21])
{
	int ret = 0; 
	unsigned char ucTempBuffer[128] = "";
	unsigned char ucBuffer[128] = "";
	// 学工号
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x00, 0x01); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	memcpy(ucCardNo, ucBuffer, 16);
	/*
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x00, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	memcpy(pc->ucCardNo + 16, ucBuffer, 4);
	*/
	return 0;
}

// 函数功能: 读取黑卡标记
// 函数参数: ucBlackFlag(黑卡标记, 0表示黑卡, 非0表示白卡)
// 函数返回: 返回0为成功，否则失败
int _stdcall SMT_ReadBlackCardFlag(unsigned char *ucBlackFlag)
{
	int ret = 0;
	unsigned char ucBuffer[128] = "";
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucBuffer, 0x03, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	*ucBlackFlag = ucBuffer[0];
	return 0;
}