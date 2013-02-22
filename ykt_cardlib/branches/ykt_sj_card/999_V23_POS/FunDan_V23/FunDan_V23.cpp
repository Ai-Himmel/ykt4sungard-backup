#include "stdafx.h"
#include "stdlib.h"

#pragma  pack(1)
typedef struct               
{
	unsigned char ShowCardNo[11];			//�û�����ʾ����
	unsigned char CardNo[8];				//�û������׿���
	unsigned char DeadLineDate[9];			//�û���ʹ�ý�ֹ����
	int CardRightType;						//�û���ʹ��Ȩ�����ͣ�1--254��
	unsigned char ucName[9];				//����
	unsigned char ucDutyNo[9];				//ְ�����
	unsigned char ucCertificateNo[21];		//֤������
	unsigned char ucDepartmentNo[11];		//���ű��
	unsigned char ucIdentifyNo[5];			//��ݴ���
	unsigned char ucSexNo[2];				//�Ա����
	unsigned char ucCardNo[21];				//���ţ����Ż�ѧ�ţ�
	unsigned char ucPwd[6];					//������
	unsigned char ucLibraryNo[21];			//ͼ��֤��
	int Money;								//���֣�
	unsigned char isFormat;					//�Ƿ��ʽ����һ����
}TPublishCard;
#pragma  pack()

// FunDan_V23�豸��Ҫ�ĵײ�Ӳ��
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

// �ı����������unsigned char* �� char*
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

// ��������: ����
// ��������: ��
// ��������: ����0Ϊ�ɹ�������ʧ��
int _stdcall SMT_ControlBuzzer()
{
	int ret = 0;
	if (icdev)
	{
		return icdev;
	}
	// ���д�����󲻳���0x10
	ret = SMT_FUDAN_Beep(g_Port, 1);
	return 0;
}

// ��������: �򿪴���
// ��������: port(�˿ں�), baud(������)
/*	�����ʲ�����
0	19200         
1	9600
2	600
3	1200
4	2400
5	4800
6	14400
7	57600
*/
// ��������: ����0Ϊ�ɹ�������ʧ��
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

// ��������: ��Ǯ�������Ǯ
// ��������: nMoney(Ǯ��Ŀ), nFlowNo(��ˮ�ն˺�)
// ��������: ����0Ϊ�ɹ�������ʧ��
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

// ��������: ��Ǯ����ȡ�����
// ��������: nMoney(Ǯ��Ŀ)
// ��������: ����0Ϊ�ɹ�������ʧ��
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

// ��������: ��Ƭ����
// ��������: BnMoney(����ǰ���), AnMoney(���������)
// ��������: ����0Ϊ�ɹ�������ʧ��
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

// ��������: ��ȡ����Ϣ
// ��������: TPublishCard�ṹ��(��������ܶ࿴�ṹ˵��)
// ��������: ����0Ϊ�ɹ�������ʧ��
int _stdcall SMT_ReadCardInfo(TPublishCard *pc)
{
	int ret = 0;
	unsigned char ucTempBuffer[128] = "";
	unsigned char ucBuffer[256] = "";
	unsigned char ucBcdShowCardNo[5];							 // ��ʾ���� 
	unsigned char ucDeadLineDate[3];							 // �û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];							 // Ȩ��λ
	int nDealCardNo[1];											 // �û����׿���(��Ҫתһ��)
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x01, 0x00); // ��һ���������
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// ���׿���
	nDealCardNo[0] = ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2];
	// ��Ȩ������
	ucCardRightType[0] = ucBuffer[3];
	// ����ֹ����
	memcpy(ucDeadLineDate, ucBuffer + 4, 3);
	// ��ʾ����
	memcpy(ucBcdShowCardNo,ucBuffer + 7, 5);
	bcd2dec(ucBcdShowCardNo, 5, pc->ShowCardNo);
	sprintf((char*)pc->DeadLineDate, "20%02d%02d%02d", ucDeadLineDate[0], ucDeadLineDate[1], ucDeadLineDate[2]);
	sprintf((char*)pc->CardNo, "%d", nDealCardNo[0]);
	pc->CardRightType = ucCardRightType[0];
	// ѧ����
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
	// �ֿ�������
	memcpy(pc->ucName, ucBuffer, 8);
	// ְλ����
	memcpy(pc->ucDutyNo, ucBuffer + 8, 4);
	// ֤������
	memcpy(pc->ucCertificateNo, ucBuffer + 12, 4);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x01); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// ֤���������16���ֽ�
	memcpy(pc->ucCertificateNo + 4, ucBuffer, 16);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// ���ź���
	memcpy(pc->ucDepartmentNo, ucBuffer, 10);
	// ���֤����
	memcpy(pc->ucIdentifyNo, ucBuffer + 10, 4);
	// �Ա�
	memcpy(pc->ucSexNo, ucBuffer + 14, 1);

	return 0;
}

// ��������: ��ȡѧ����
// ��������: ucCardNo(ѧ��������)
// ��������: ����0Ϊ�ɹ�������ʧ��
int _stdcall SMT_ReadCardNo(unsigned char ucCardNo[21])
{
	int ret = 0; 
	unsigned char ucTempBuffer[128] = "";
	unsigned char ucBuffer[128] = "";
	// ѧ����
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

// ��������: ��ȡ�ڿ����
// ��������: ucBlackFlag(�ڿ����, 0��ʾ�ڿ�, ��0��ʾ�׿�)
// ��������: ����0Ϊ�ɹ�������ʧ��
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