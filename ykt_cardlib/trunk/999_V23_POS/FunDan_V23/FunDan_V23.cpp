#include "stdafx.h"
#include "stdlib.h"
#include "..\..\include\carddll_def.h"

// FunDan_V23�豸��Ҫ�ĵײ�Ӳ��
int icdev = -1;
int g_Port = 0;

TPublishCard global_card_info;
DataInfoEx global_data_info;

//////////////////////////////////////////////////////////////////////////
// ��̨ͨѶ�⺯��(������GW_KBC.dll)
HINSTANCE hGwKbcDLL = NULL;
typedef int (CALLBACK	*LPGW_Login)(void);
typedef int (CALLBACK	*LPGW_CreateNewHandle)(void);
typedef int (CALLBACK	*LPGW_CloseHandle)(void);
typedef int (CALLBACK	*LPGW_Exit)(void);
typedef int (CALLBACK	*LPGW_GetCardInfo)(char physical_no[9], CardInfo *card_info);
typedef int (CALLBACK	*LPGW_GetCustomerInfo)(int cut_id, char stuemp_no[22], CutInfo *cut_info);
typedef void (CALLBACK	*LPGW_GetLastErrorMsg)(char *error_msg);
typedef int (CALLBACK	*LPGW_GetSeedKey)(char *seed_key);
typedef int (CALLBACK	*LPGW_GetDataRecordExA)(int card_id, char physical_no[9], char stuemp_no[22], DataInfoEx *data_info);
typedef int (CALLBACK   *LPGW_DataInfo)(char physical_no[9], char stuemp_no[22], DataInfo *data_info);
typedef int (CALLBACK   *LPGW_CheckDeposit)(int card_id);

LPGW_Login				GW_Login = NULL;
LPGW_CreateNewHandle	GW_CreateNewHandle = NULL;
LPGW_CloseHandle		GW_CloseHandle = NULL;
LPGW_Exit				GW_Exit = NULL;
LPGW_GetCardInfo		GW_GetCardInfo = NULL;
LPGW_GetCustomerInfo	GW_GetCustomerInfo = NULL;
LPGW_GetLastErrorMsg	GW_GetLastErrorMsg = NULL;
LPGW_GetSeedKey			GW_GetSeedKey = NULL;
LPGW_GetDataRecordExA	GW_GetDataRecordExA = NULL;
LPGW_DataInfo			GW_DataInfo = NULL;
LPGW_CheckDeposit		GW_CheckDeposit = NULL;

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

/*================================================================ 
* ������:     SMT_LoadDll
* ����:       [void] 
* ��������:   ����POS�������⺯��
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ������:     Load_Dll
* ����:       [void] 
* ��������:   ���غ�̨ͨѶ�⺯��
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int Load_Dll()
{
	if (hGwKbcDLL)
	{
		return 0;
	}
	hGwKbcDLL = LoadLibrary("GW_KBC.dll");
	if (!hGwKbcDLL)
	{
		return -1;
	}
	GW_Login			= (LPGW_Login)GetProcAddress(hGwKbcDLL, "GW_Login");
	GW_CreateNewHandle	= (LPGW_CreateNewHandle)GetProcAddress(hGwKbcDLL, "GW_CreateNewHandle");
	GW_CloseHandle		= (LPGW_CloseHandle)GetProcAddress(hGwKbcDLL, "GW_CloseHandle");
	GW_Exit				= (LPGW_Exit)GetProcAddress(hGwKbcDLL, "GW_Exit");
	GW_GetCardInfo		= (LPGW_GetCardInfo)GetProcAddress(hGwKbcDLL, "GW_GetCardInfo");
	GW_GetCustomerInfo	= (LPGW_GetCustomerInfo)GetProcAddress(hGwKbcDLL, "GW_GetCustomerInfo");
	GW_GetLastErrorMsg  = (LPGW_GetLastErrorMsg)GetProcAddress(hGwKbcDLL, "GW_GetLastErrorMsg");
	GW_GetSeedKey		= (LPGW_GetSeedKey)GetProcAddress(hGwKbcDLL, "GW_GetSeedKey");
	GW_GetDataRecordExA	= (LPGW_GetDataRecordExA)GetProcAddress(hGwKbcDLL, "GW_GetDataRecordExA");
	GW_DataInfo			= (LPGW_DataInfo)GetProcAddress(hGwKbcDLL, "GW_DataInfo");
	GW_CheckDeposit     = (LPGW_CheckDeposit)GetProcAddress(hGwKbcDLL,"GW_CheckDeposit");
	if (
		(!GW_Login)				|| 
		(!GW_CreateNewHandle)	||
		(!GW_CloseHandle)		||
		(!GW_Exit)				||
		(!GW_GetCardInfo)		||
		(!GW_GetCustomerInfo)	||
		(!GW_GetLastErrorMsg)	||
		(!GW_GetSeedKey)		||
		(!GW_GetDataRecordExA)	||
		(!GW_DataInfo)			||
		(!GW_CheckDeposit)		
		)
	{
		FreeLibrary(hGwKbcDLL);
		hGwKbcDLL = NULL;
		return -2;
	}
	return 0;
}

/*================================================================ 
* ������:     SMT_ControlBuzzer
* ����:       [void] 
* ��������:   POS������
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ������:     SMT_ConnectMF280
* ����:       [in] (int port)���ں�	  
*			  [in] (int baud)������
*			  �����ʲ���:
*			  0		19200         
*			  1		9600
*			  2		600
*			  3		1200
*			  4		2400
*			  5		4800
*			  6		14400
*			  7		57600			 
* ��������:   �򿪴���
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ������:     SMT_CloseMF280
* ����:       [void]
* ��������:   �رմ���
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ������:     SMT_PacketDelMomey
* ����1:      [in] (int nMoney)��Ƭ���
* ����2:	  [out] (int &nFlowNo)�ն���ˮ��
* ��������:   ��ȡ��Ǯ�����
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int _stdcall SMT_PacketDelMomey(int nMoney, int &nFlowNo)
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

/*================================================================ 
* ������:     SMT_ReadBalance
* ����:       [out] (int &nMoney)��Ƭ���
* ��������:   ��ȡ��Ǯ�����
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ������:     SMT_MendPacket
* ����1:      [out] (int &BnMoney)����ǰ���
* ����2:	  [out] (int &AnMoney)���������
* ��������:   POS���Կ�����
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int _stdcall SMT_MendPacket(int &BnMoney, int &AnMoney)
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

/*================================================================ 
* ������:     SMT_ReadCardInfo
* ����:       [out] (TPublishCard *pc)��Ҫ���ĵ��ṹ					
* ��������:   ��ȡ����Ϣ����
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ������:     SMT_ReadCardNo
* ����:       [out] (unsigned char ucCardNo[21])ѧ����					
* ��������:   ��ȡ���ϵ�ѧ����
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

int _stdcall SMT_ReadCardID(int *cardid)
{
	int ret = 0; 
	unsigned char ucBuffer[16] = "";
	// ѧ����
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucBuffer, 0x01, 0x00); 
	if (ret != 0)
	{
		return ret;
	}
	int no;
	no = ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2];
	*cardid = no;
	return 0;
}

/*================================================================ 
* ������:     SMT_ReadBlackCardFlag
* ����:       [out] (unsigned char *ucBlackFlag)��������־		
* ��������:   ��ȡ���ϵĺ�������־
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
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

/*================================================================ 
* ��������    SMT_GetCardRecord
* ������      [in] (void)					
* ��������:   ��ȡ����¼�ֶ�
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall SMT_GetCardRecord()
{
	int ret = 0;
	unsigned char ucTempBuffer[128] = "";
	unsigned char ucBuffer[256] = "";
	unsigned char ucBcdShowCardNo[5];							 // ��ʾ���� 
	unsigned char ucDeadLineDate[3];							 // �û���ʹ�ý�ֹ����
	unsigned char ucCardRightType[1];							 // Ȩ��λ
	int nDealCardNo[1];											 // �û����׿���(��Ҫתһ��)
	memset(&global_card_info, 0, sizeof(global_card_info));

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
	bcd2dec(ucBcdShowCardNo, 5, global_card_info.ShowCardNo);
	sprintf((char*)global_card_info.DeadLineDate, "20%02d%02d%02d", ucDeadLineDate[0], ucDeadLineDate[1], ucDeadLineDate[2]);
	sprintf((char*)global_card_info.CardNo, "%d", nDealCardNo[0]);
	global_card_info.CardRightType = ucCardRightType[0];
	// ѧ����
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x00, 0x01); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	memcpy(global_card_info.ucCardNo, ucBuffer, 16);
	
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x00, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	memcpy(global_card_info.ucCardNo + 16, ucBuffer, 4);
	
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x00); // ucBuffer to ucBuffer1
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// �ֿ�������
	memcpy(global_card_info.ucName, ucBuffer, 8);
	// ְλ����
	memcpy(global_card_info.ucDutyNo, ucBuffer + 8, 4);
	// ֤������
	memcpy(global_card_info.ucCertificateNo, ucBuffer + 12, 4);
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x01); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// ֤���������16���ֽ�
	memcpy(global_card_info.ucCertificateNo + 4, ucBuffer, 16);
	
	ret = SMT_FUDAN_ReadCardBlock(g_Port, ucTempBuffer, 0x02, 0x02); 
	if (ret != 0)
	{
		return ret;
	}
	hex2dec((char*)ucTempBuffer, ucBuffer, 32);
	// ���ź���
	memcpy(global_card_info.ucDepartmentNo, ucBuffer, 10);
	// ���֤����
	memcpy(global_card_info.ucIdentifyNo, ucBuffer + 10, 4);
	// �Ա�
	memcpy(global_card_info.ucSexNo, ucBuffer + 14, 1);

	return 0;
}

/*================================================================ 
* ��������    SMT_ReadCardInfoExA
* ������      [in] (const char *field_name)��ȡ���ݵ�������
*			  showno----��ʾ����
*             cardno----���׿���
*			  deallinedate----�û�����������
*			  righttype----�û���Ȩ������
*			  name---����
*			  dutyno----ְλ����
*			  cerno----֤������
*			  departno----���Ŵ���
*			  sex----�Ա�
*			  stuempno----ѧ����
*			  pwd----����
*             [out] (char *field_value)��ȡ��Ƭ����������Ӧ������ 					
* ��������:   ��ȡ����Ϣ�ֶ�
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int _stdcall SMT_ReadCardInfoExA(const char *field_name, unsigned char *field_value)
{
	if (!field_name)
	{
		return 2;
	}

	if (0 == strcmp(field_name, "showno"))
	{
		memcpy(field_value, global_card_info.ShowCardNo, sizeof(global_card_info.ShowCardNo));
	}
	else if (0 == strcmp(field_name, "cardno"))
	{
		memcpy(field_value, global_card_info.CardNo, sizeof(global_card_info.CardNo));
	}
	else if (0 == strcmp(field_name, "deallinedate"))
	{
		memcpy(field_value, global_card_info.DeadLineDate, sizeof(global_card_info.DeadLineDate));
	}
	else if (0 == strcmp(field_name, "righttype"))
	{
		sprintf((char *)field_value, "%d", global_card_info.CardRightType);
	}
	else if (0 == strcmp(field_name, "name"))
	{
		memcpy(field_value, global_card_info.ucName, sizeof(global_card_info.ucName));			
	}
	else if (0 == strcmp(field_name, "dutyno"))
	{
		memcpy(field_value, global_card_info.ucDutyNo, sizeof(global_card_info.ucDutyNo));			
	}
	else if (0 == strcmp(field_name, "cerno"))
	{
		memcpy(field_value, global_card_info.ucCertificateNo, sizeof(global_card_info.ucCertificateNo));			
	}
	else if (0 == strcmp(field_name, "departno"))
	{
		memcpy(field_value, global_card_info.ucDepartmentNo, sizeof(global_card_info.ucDepartmentNo));			
	}
	else if (0 == strcmp(field_name, "sex"))
	{
		memcpy(field_value, global_card_info.ucSexNo, sizeof(global_card_info.ucSexNo));			
	}
	else if (0 == strcmp(field_name, "stuempno"))
	{
		memcpy(field_value, global_card_info.ucCardNo, sizeof(global_card_info.ucCardNo));			
	}
	else if (0 == strcmp(field_name, "pwd"))
	{
		memcpy(field_value, global_card_info.ucPwd, sizeof(global_card_info.ucPwd));			
	}
	else
	{
		return 0;
	}

	return 0;
}

/*================================================================ 
* ��������    YKTSVR_Login
* ������      [in] (void)					
* ��������:   ��¼һ��ͨ��̨������
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int _stdcall YKTSVR_Login()
{
	int ret = 0;
	if (ret = Load_Dll()) { return ret; }

	return GW_Login();
}

/*================================================================ 
* ��������    YKTSVR_Create
* ������      [in] (void)					
* ��������:   ����һ��ͨ��̨�������Դ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_Create()
{
	if (!GW_CreateNewHandle) { return 0; }
	return GW_CreateNewHandle();
}

/*================================================================ 
* ��������    YKTSVR_Close
* ������      [in] (void)					
* ��������:   �ر�����������Դ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_Close()
{
	if (!GW_CloseHandle) { return 0; }
	return GW_CloseHandle();
}

/*================================================================ 
* ��������    YKTSVR_Exit
* ������      [in] (void)					
* ��������:   �ǳ�һ��ͨ��̨������
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_Exit()
{
	if (!GW_Exit) { return 0; }
	return GW_Exit();
}

/*================================================================ 
* ��������    YKTSVR_GetLastErrorMsg
* ������      [out] (char *error_msg)��ȡ�ϴβ���ʧ�ܵĴ�����Ϣ
* ��������:   ��ȡ������Ϣ
* ����ֵ��	  void
================================================================*/
void __stdcall YKTSVR_GetLastErrorMsg(char *error_msg)
{
	if (!GW_GetLastErrorMsg) { return ; }
	return GW_GetLastErrorMsg(error_msg);
}

/*================================================================ 
* ��������    YKTSVR_GetDataRecordExA
* ������      [in] (card_id)���׿���					
* ��������:   ��ȡһ��ͨ��̨��¼
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_GetDataRecordExA(int card_id)
{
	int ret = 0;
	char physical_no[9] = "";
	char stuemp_no[22] = "";
	memset(&global_data_info, 0, sizeof(global_data_info));
	if (!GW_GetDataRecordExA) { return 0; }
	ret = GW_GetDataRecordExA(card_id, physical_no, stuemp_no, &global_data_info);
	if (ret)
	{
		return ret;
	}

	return 0;
}

/*================================================================ 
* ��������    YKTSVR_GetDataInfoExA
* ������      [in] (const char *field_name)��ȡ���ݵ�������
*			  cutid----�ͻ���
*             cardno----���׿���
*			  name---����
*			  sex----�Ա�
*			  deptname----��������
*			  cuttype----�ͻ�������(����12)
*			  typename----�ͻ��������(���� 12����ѧ��)
*			  classname---"�༶����"
*			  stuempno----ѧ����
*             [out] (char *field_value)��ȡ��Ƭ����������Ӧ������ 					
* ��������:   ��ȡһ��ͨ��̨���ݼ���¼
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ					
================================================================*/
int __stdcall YKTSVR_GetDataInfoExA(const char *field_name, 
									char *field_value)
{
	if (!field_name)
	{
		return 2;
	}

	if (0 == strcmp(field_name, "cutid"))
	{
		sprintf(field_value, "%d", global_data_info.cut_id);
	}
	else if (0 == strcmp(field_name, "cardno"))
	{
		sprintf(field_value, "%d", global_data_info.card_id);
	}
	else if (0 == strcmp(field_name, "name"))
	{
		memcpy(field_value, global_data_info.cut_name, sizeof(global_data_info.cut_name));
	}
	else if (0 == strcmp(field_name, "sex"))
	{
		memcpy(field_value, global_data_info.sex, sizeof(global_data_info.sex));
	}
	else if (0 == strcmp(field_name, "deptname"))
	{
		memcpy(field_value, global_data_info.classdept_name, sizeof(global_data_info.classdept_name));			
	}
	else if (0 == strcmp(field_name, "cuttype"))
	{
		sprintf(field_value, "%d", global_data_info.cut_type);			
	}
	else if (0 == strcmp(field_name, "typename"))
	{
		memcpy(field_value, global_data_info.cut_type_name, sizeof(global_data_info.cut_type_name));			
	}
	else if (0 == strcmp(field_name, "classname"))
	{
		memcpy(field_value, global_data_info.class_no, sizeof(global_data_info.class_no));			
	}
	else if (0 == strcmp(field_name, "stuempno"))
	{
		memcpy(field_value, global_data_info.stuemp_no, sizeof(global_data_info.stuemp_no));			
	}
	else
	{
		return 0;
	}

	return 0;
}

/*================================================================ 
* ��������    YKTSVR_SetCardKey
* ������      [in] (void)					
* ��������:   ��ȡһ��ͨ��̨��Կ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_SetCardKey()
{
	return 0;
}

/*================================================================ 
* ������:     YKTSVR_GetCardInfo
* ����1:      [in] (char physical_no[9])�����������
* ����2:	  [out] (CardInfo *card_info)�����Ŀ���Ϣ����
* ��������:   ��ȡһ��ͨ��̨����Ϣ����
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_GetCardInfo(char physical_no[9], CardInfo *card_info)
{
	return GW_GetCardInfo(physical_no, card_info);
}

/*================================================================ 
* ������:     YKTSVR_GetCustomerInfo
* ����1:      [in] (int cut_id)����Ŀͻ���
* ����2:	  [out] (CutInfo *card_info)�����Ŀͻ���Ϣ����
* ��������:   ��ȡһ��ͨ��̨�ͻ���Ϣ
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_GetCustomerInfo(int cut_id, CutInfo *card_info)
{
	return GW_GetCustomerInfo(cut_id, "", card_info);
}

/*================================================================ 
* ������:     YKTSVR_GetDataInfo
* ����1:      [in] (char physical_no[9])������
* ����2:	  [in] (char stuemp_no[22])ѧ����
* ����3:	  [out] (DataInfo *data_info)������������Ϣ
* ��������:   ��ȡһ��ͨ��̨������Ϣ
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_GetDataInfo(char physical_no[9],  char stuemp_no[22], DataInfo *data_info)
{
	int ret = 0;
	CardInfo card_info;
	CutInfo cut_info;
	memset(&card_info, 0, sizeof(card_info));
	memset(&cut_info, 0, sizeof(cut_info));

	if (NULL == physical_no || NULL == stuemp_no) { return KS_ERR_INPUTNULLFAILED; }

	if (memcmp(physical_no, "", sizeof(physical_no) - 1) == 0 && memcmp(stuemp_no, "", sizeof(stuemp_no) - 1) == 0)
		return KS_ERR_INPUTNULLFAILED;

	if (ret = GW_DataInfo(physical_no, stuemp_no, data_info)) { return ret; }

	return 0;
}

/*================================================================ 
* ������:     GetLastErrMsg
* ����1:      [out] (int ecode[1])��ȡ�Ĵ������
* ����2:	  [out] (char *errmsg)��ȡ�Ĵ�����Ϣ
* ��������:   ��ȡ������Ϣ
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall GetLastErrMsg(int ecode[1], char *errmsg)
{
	if (GW_GetLastErrorMsg != NULL)	{ GW_GetLastErrorMsg(errmsg); }
	
	return 0;
}

/*================================================================ 
* ������:     YKTSVR_GetDataFromPhy
* ����1:      [in] (char physical_no[9])������
* ����2:	  [out] (DataInfoEx *data_info_ex)��ȡ��������Ϣ
* ��������:   ͨ�������Ż�ȡһ��ͨ��̨��¼
* ����ֵ:     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int __stdcall YKTSVR_GetDataFromPhy(char physical_no[9], DataInfoEx *data_info_ex)
{
	int ret = 0;
	int card_id = 0;
	char stuemp_no[22] = "";

	memset(&global_data_info, 0, sizeof(global_data_info));
	if (!GW_GetDataRecordExA) { return 0; }
	ret = GW_GetDataRecordExA(card_id, physical_no, stuemp_no, data_info_ex);
	if (ret)
	{
		return ret;
	}

	return 0;
}


/*================================================================ 
* ������:     YKTSVR_CheckDeposit
* ����1:      [in] (int card_id)���׿���
* ��������:   ͨ�������Ų�ѯѧԱ�Ƿ񽻹�Ѻ��
* ����ֵ:     int, -1:���轻 0:�ѽ� 1:Ӧ�� ����ֵ����
================================================================*/
int __stdcall YKTSVR_CheckDeposit(int card_id)
{
	if(!GW_CheckDeposit)
		return 0;
	return GW_CheckDeposit(card_id);
}
