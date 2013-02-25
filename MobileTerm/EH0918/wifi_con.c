/****************************************************************************
*
*�ļ�(File):         wifi_con.c
*
*�޸�(Modify):       2011/7/25 15:39:59
*
*����(Author):       USER
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
*
*
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011/7/25 15:39:59           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"

static char  g_RBackInfo[32];       //..�ص�������ʾ 
u16 g_pHandle[1] = {0};	//wifi���Ӿ��

char wifi_init();	//WIFI��ʼ��
void wifinet_set();	//���������Ӳ˵�
unsigned long WiFi_MsgDisplay(char *WiFiMsg, u16 WiFiMsgID, u8 WiFiMsgType);	//�ص���������ʾ
void InputData(char *pShowMsg, char *pRtnInfo, char alphaInput);		//..��ü�����������
void setIP();		//����IP
void setNetMask();	//������������
void setGateway();	//��������
void setServerIP();	//���÷�����IP
void setServerPort();	//���÷������˿�
void setServerSSID();	//����SSID
void setPassword();	//��������
void clearPSK();		//��հ�ȫ����
void connectWifi();	//��������
void disConnect();	//�Ͽ�����
void resetWifi();	//����ģ��
void sendRecords();	//�������ݣ��˵����ã�
//char sendRecords(char* data_buffer, int bufferMax)	//��������
/***********************************************************************
		module		:	[WIFI]
		function		:	[wifi�ϴ��˵�]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void wifi_upload_menu()
{
	int select = -1;
	//int conStatus = 0;		//����״̬��0����������
	char db_menu_str[] =	"1. ��������"
							"2. �ϴ�����"
							"3. ��������"
							"4. �Ͽ�����"
							"5. ����ģ��";

	BROWINFO	info;
	info.iStr = db_menu_str;		//�������ָ��
	info.lPtr = 0;					//��ʾ����iStr����ʼ��ʾ��
	info.cPtr = 0;					//��ǰѡ����

	while (1) {
		//����BROWINFO�ṹ��Ա�����������ѭ�����п��ܻᱻEXT_Brow_Select�����ı�
//		 conStatus = CWiFi_GetRepStatus(g_pHandle[0]);
//		 if (!conStatus) {
//		 	strncpy(db_menu_str, "1. �Ͽ����ӣ������ӣ�", 21);
//		}
//		else {
//			strncpy(db_menu_str, "1. �������ӣ�δ���ӣ�", 21);
//		}
		info.startLine = 2;				//��LCD�ϵ���ʾ��ʼ��
		info.dispLines = 5;				//��LCD�ϵ���ʾ����
		info.mInt = 5;					//��ʾ���ݵ�������
		info.lineMax = 11;				//ÿ������ַ���
		info.sFont = 0;					//7x9��������ʾ
		info.numEnable = 0;				//�Ƿ��������ּ����淽�����
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //�ɵ��º����˳����¼���־
		info.autoexit = 1200;			//�Զ��˳���ʱ��
		//�˵�
		Disp_Clear();
		DispStr_CE(0, 0, "wifi����˵�", DISP_CENTER);
		select = EXT_Brow_Select(&info);

		switch (select) {
			case 0:		//�������ӣ��Ͽ�����
				connectWifi();	//��������
				break;
			case 1:		//�ϴ�����
				sendRecords();
				break;
			case 2:		//��������
				wifinet_set();
				break;
			case 3:		//�Ͽ�����
				disConnect();
				break;
			case 4:		//����ģ��
				resetWifi();
				break;
			default:	//����CPUռ���ʣ������ܺ�
				if (info.qEvent == EXIT_KEY_F1  || EXIT_AUTO_QUIT 
                                || EXIT_KEY_POWER || EXIT_KEY_CANCEL) { //�����ϼ��˵� 
					return;
				}
				Sys_Power_Sleep(3);
				break;
		}
	}
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[�Ͽ�����]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void disConnect()
{
	CWiFi_Disconnect(g_pHandle[0]);
	DispStr_CE(0,6,"�����ѶϿ�",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[����ģ��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void resetWifi()
{
	CWiFi_CloseMould();
	CWiFi_OpenMould();
	DispStr_CE(0,6,"ģ��������",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[wifi��ʼ�����������ã�]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void wifiInit_open()
{
	char ret = 0;	//wifi��ʼ�����
	char errBuf[25] = {0};	//������Ϣ
	char retBuf[] = "�����������";	//������Ϣ
	
	DispStr_CE(0,6,"WIFI��ʼ����",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����ĵȴ�...",DISP_CENTER);
	ret = wifi_init();
	switch ((int)ret) {
		case -1:
			strcpy(errBuf, "ģ���ʼ��ʧ��");
			break;
		case -2:
			strcpy(errBuf, "ģ������ʧ��");
			break;
		case -3:
			strcpy(errBuf, "��Դ����ʧ��");
			break;
		case -4:
			strcpy(errBuf, "�ŵ�����ʧ��");
			break;
		case -5:
			strcpy(errBuf, "ͨ����������ʧ��");
			break;
	}
	if (ret) {
		DispStr_CE(0,6,errBuf,DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,8,retBuf,DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[wifi��ʼ��]
  		return		:	[0:�ɹ�
  						-1:ģ���ʼ��ʧ��
  						-2:ģ������ʧ��
  						-3:��Դ����ʧ��
  						-4:�ŵ�����ʧ��
  						-5:ͨ����������ʧ��
  		]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
char wifi_init()
{
	char ret = 0;
	short MinVol          = 0;
	if(MinVol > SYS_Read_Vol()) {
		DispStr_E(0,6,"��������",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		Sys_Delay_MS(1000);
		Sys_Power_Sleep(2);
	}
	CWiFi_SetMSGCallBack((WiFiMSG_CALLBACK)WiFi_MsgDisplay);	//�ص����������У���������
	if (CWiFi_InitModule(0,0) != NaNo_OK) {		//��ʼ��ģ��
		ret = -1;
	}
	if (CWiFi_ConnState(0) != NaNo_OK) {	//ģ������״̬
		ret = -2;
	}
	if (CWiFi_SetPowerMode(10,2,120) != NaNo_OK) {	//���õ�Դ
		ret = -3;
	}
	if ( CWiFi_SetWiFiChanle(0) != NaNo_OK) {		//�ŵ�����ʧ��
		ret = -4;
	}
	if (CWiFi_SetWiFiTransRate(0) != NaNo_OK) {	//����ͨ������
		ret = -5;
	}
	return ret;
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[�ص�(��ʾ)����]
  		return		:	[]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
unsigned long WiFi_MsgDisplay(char *WiFiMsg,
                              u16   WiFiMsgID,
                              u8    WiFiMsgType)
{
    memset(g_RBackInfo,0x00,32);
    //sprintf(&RBackInfo[0], " MID:%d,TID:%d,%s\n", WiFiMsgID,WiFiMsgType,WiFiMsg);
    sprintf(&g_RBackInfo[0], "%s",WiFiMsg);
    return 0;
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[WIFI���������Ӳ˵�]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void wifinet_set()
{
	int select = -1;
	char db_menu_str[] =		"1. ���ñ���IP  "
							"2. ������������"
							"3. ��������    "
							"4. ���÷�����IP"
							"5. ���ö˿�    "
							"6. ����ssid    "
							"7. ��������    "
							"8. ��հ�ȫ����";

//	if ( adminPassword(0) ) {
//		return;
//	}
	BROWINFO	info;
	info.iStr = db_menu_str;		//�������ָ��
	info.lPtr = 0;					//��ʾ����iStr����ʼ��ʾ��
	info.cPtr = 0;					//��ǰѡ����

	while (1) {
		//����BROWINFO�ṹ��Ա�����������ѭ�����п��ܻᱻEXT_Brow_Select�����ı�
		info.startLine = 0;				//��LCD�ϵ���ʾ��ʼ��
		info.dispLines = 7;				//��LCD�ϵ���ʾ����
		info.mInt = 8;					//��ʾ���ݵ�������
		info.lineMax = 15;				//ÿ������ַ���
		info.sFont = 0;					//7x9��������ʾ
		info.numEnable = 0;				//�Ƿ��������ּ����淽�����
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //�ɵ��º����˳����¼���־
		info.autoexit = 1200;			//�Զ��˳���ʱ��
		//�˵�
		Disp_Clear();
		select = EXT_Brow_Select(&info);

		switch (select) {
			case 0:		//���ñ���IP
				setIP();
				break;
			case 1:		//������������
				setNetMask();
				break;
			case 2:		//��������
				setGateway();
				break;
			case 3:		//���÷�����IP
				setServerIP();
				break;
			case 4:		//���ö˿�
				setServerPort();
				break;
			case 5:		//����SSID
				setServerSSID();
				break;
			case 6:		//��������
				setPassword();
				break;
			case 7:		//��հ�ȫ����
				clearPSK();
				break;
			default:	//����CPUռ���ʣ������ܺ�
				if (info.qEvent == EXIT_KEY_F1  || EXIT_AUTO_QUIT 
                                || EXIT_KEY_POWER || EXIT_KEY_CANCEL) { //�����ϼ��˵� 
					return;
				}
				Sys_Power_Sleep(3);
				break;
		}
	}
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[����IP]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setIP()
{
	char plIPAddr[16];
	char retStr[16] = {0};
	memset(plIPAddr,0x00,16);
	CWiFi_GetLocalAddress(plIPAddr);	
	InputData((char*)"����IP",plIPAddr, 0);
	if (NaNo_OK == CWiFi_SetLocalAddress(plIPAddr)) {
		strcpy(retStr, "���óɹ�");
	}
	else {
		strcpy(retStr, "����ʧ��");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 ); 
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[������������]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setNetMask()
{
	char netMask[16];
	char retStr[16] = {0};
	memset(netMask,0x00,16);
	CWiFi_GetLocalNetMask(netMask);	
	InputData((char*)"��������",netMask, 0);
	if (NaNo_OK == CWiFi_SetLocalNetMask(netMask)) {
		strcpy(retStr, "���óɹ�");
	}
	else {
		strcpy(retStr, "����ʧ��");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 ); 
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[��������]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setGateway()
{
	char geteWay[16];
	char retStr[16] = {0};
	memset(geteWay,0x00,16);
	CWiFi_GetGatewayAddress(geteWay);	
	InputData((char*)"����",geteWay, 0);
	if (NaNo_OK == CWiFi_SetGatewayAddress(geteWay)) {
		strcpy(retStr, "���óɹ�");
	}
	else {
		strcpy(retStr, "����ʧ��");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 ); 
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[�������ӷ�����IP]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setServerIP()
{
	char retStr[20] = {0};
	char ret = -2;	//����ʧ��
	unsigned char serverIPAdd[25] = {0};	//������IP

	memset(serverIPAdd,0x00,16);

	if (eeprom_read(serverIPAdd, 16, EEPROM_OFFSET_SERVERIPADD)) {
		ret = -1;	//��ȡʧ��
	}
	if (ret != -1) {
		InputData((char*)"������IP",serverIPAdd, 0);
		if (serverIPAdd[0] != 0) {	//�ж��ַ�����Ϊ��
			if (eeprom_write(serverIPAdd, strlen(serverIPAdd)+1, EEPROM_OFFSET_SERVERIPADD)) {
				ret = -2;	//����ʧ��
			}
			else {
				ret = 0;	//���óɹ�
			}
		}
	}

	if (!ret) {
		strcpy(retStr, "���óɹ�");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM����ʧ��");
	}
	else if (ret == -2) {
		strcpy(retStr, "����ʧ��");
	}	
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[�������ӷ������˿�]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
void setServerPort()
{
	char serverPort[10] = {0};
	char retStr[20] = {0};
	char ret = -2;	//����ʧ��
	//strcpy(dspBuf, "�˿����óɹ�");

	if (eeprom_read(serverPort, 8, EEPROM_OFFSET_SERVERPORT)) {
		ret = -1;
	}
	if (ret != -1) {
		 InputData((char*)"�������˿�", serverPort, 0);
		if (serverPort[0] != 0) {	//�ж��ַ�����Ϊ��
			if (eeprom_write(serverPort, 8, EEPROM_OFFSET_SERVERPORT)) {
				ret = -2;	//����ʧ��
			}
			else {
				ret = 0;	//���óɹ�
			}
		}
	}
	 if (!ret) {
		strcpy(retStr, "���óɹ�");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM����ʧ��");
	}
	else if (ret == -2) {
		strcpy(retStr, "����ʧ��");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[�������ӷ�����SSID]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
void setServerSSID()
{
	char pUserName[20] = {0};
	char retStr[20] = {0};
	char ret = -2;	//����ʧ��
	//strcpy(dspBuf, "�˿����óɹ�");

	if (eeprom_read(pUserName, 16, EEPROM_OFFSET_SERVERSSID)) {
		ret = -1;
	}
	if (ret != -1) {
		 InputData((char*)"SSID", pUserName, 1);
		if (pUserName[0] != 0) {	//�ж��ַ�����Ϊ��
			if (eeprom_write(pUserName, 16, EEPROM_OFFSET_SERVERSSID)) {
				ret = -2;	//����ʧ��
			}
			else {
				ret = 0;	//���óɹ�
			}
		}
	}
	 if (!ret) {
		strcpy(retStr, "���óɹ�");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM����ʧ��");
	}
	else if (ret == -2) {
		strcpy(retStr, "����ʧ��");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[�������ӷ���������]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
void setPassword()
{
	char password[20] = {0};
	char retStr[20] = {0};
	char ret = -2;	//����ʧ��
	
	if (eeprom_read(password, 16, EEPROM_OFFSET_SEVPASSWORD)) {
		ret = -1;
	}
	if (ret != -1) {
		 InputData((char*)"����", password, 1);
		if (password[0] != 0) {	//�ж��ַ�����Ϊ��
			if (eeprom_write(password, 16, EEPROM_OFFSET_SEVPASSWORD)) {
				ret = -2;	//����ʧ��
			}
			else {
				ret = 0;	//���óɹ�
			}
		}
	}
	 if (!ret) {
		strcpy(retStr, "���óɹ�");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM����ʧ��");
	}
	else if (ret == -2) {
		strcpy(retStr, "����ʧ��");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[��հ�ȫ����]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
int CNaNoWiFi_ClearRoutePSK()
{
    return 0;
}



void clearPSK()
{
	if(NaNo_OK == CNaNoWiFi_ClearRoutePSK()) {
		DispStr_CE(0,4,"����ɹ�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	else {
		DispStr_CE(0,4,"���ʧ��",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[��������]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
void connectWifi()
{
	//u16 pHandle[1] = {0};	//wifi���Ӿ��
	//unsigned char pHandle_char[2] = {0};	//wifi���Ӿ���������
	char dspBuf[20] = {0};
	char serverPort[20] = {0};
	unsigned char serverIPAdd[16] = {0};
	
	//CWiFi_OpenMould();
	if (eeprom_read(serverIPAdd, sizeof(serverIPAdd), EEPROM_OFFSET_SERVERIPADD)) {
		strcpy(dspBuf, "��ȡIPʧ��");
	}
	if (eeprom_read(serverPort, 8, EEPROM_OFFSET_SERVERPORT)) {
		strcpy(dspBuf, "��ȡ�˿�ʧ��");
	}
	else if(NaNo_OK == CWiFi_Connect(g_pHandle, (char*)serverIPAdd, serverPort, 0)) {
		strcpy(dspBuf, "���ӳɹ�");
		//shortTochar(g_pHandle, pHandle_char);
		//eeprom_write(pHandle_char, sizeof(pHandle_char), EEPROM_OFFSET_WIFI_HANDLE);
	}
	else {
		//..ע��������ʧ�ܣ�����Ҫ30����ٴ�����
		strcpy(dspBuf, "����ʧ��");
		CWiFi_ConnState(0);
	}

	DispStr_CE(0,6,dspBuf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[��������]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void InputData(char *pShowMsg, char *pRtnInfo, char alphaInput)             //..��ü����������� 
{
	GETSTR_PARAM   gs;
	char           strbuf[50];
	memset(strbuf,0x00,50);
	memcpy(strbuf,pRtnInfo,strlen(pRtnInfo));
	memset(pRtnInfo,0x00,strlen(pRtnInfo));

	DispStr_CE(0,2,pShowMsg,DISP_POSITION|DISP_REVERSE|DISP_CLRSCR);
	gs.qx = 0;
	gs.qy = 4;
	gs.alpha = alphaInput;       //..�Ƿ���������ĸ�����ţ� 0��������1������  
	gs.sFont = 0;
	gs.pPrompt = "";
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = '.';
	gs.pStr = strbuf;	//store the input words
	gs.maxNum = 1024;
	gs.minNum = 1;
	gs.minValue = -1;
	gs.maxValue = -1;
	gs.retNum = strlen(strbuf);
	gs.qEvent = EXIT_KEY_F1;
	if ( GetStr_E(&gs) ) {
		return;
	}
	memcpy(pRtnInfo,strbuf,strlen(strbuf));
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[��������]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
void sendRecords()
{
	char retStr[20] = {0};
	char temp[20] = {0};
	int templen = 0;
	//unsigned char data_buffer[1000] = {0};	//Ҫ���͵�����
	unsigned char aBuffer[200] = {0};	
	unsigned char rb8583[50] = {0};
	unsigned char send_buf[200] = {0};	//ÿ���ϴ���������
	int send_len = 0;
	//unsigned char* pdBuffer = NULL;		//ÿ���ϴ�����ָ��
	USER_INFO* pinfo = NULL;
	char infotemp[10] = {0};
	unsigned long	db_cnt = 0;					//���ݿ��¼��
	unsigned short	send_cnt = 0;				//�ϴ�����
	char* pTemp = NULL;
	char	rec_flag = 0;
	
	strcpy(retStr, "�����ϴ��ɹ�");
	db_cnt = DB_count_records(0);	//�������ݿ��Ѽ�¼������(������ɾ��)
	if (!db_cnt) {
		strcpy(retStr, "���ݿ��޼�¼");
	}
	else {
		DispStr_CE(0,6,"�����ϴ���",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,8,"�����ĵȴ�",DISP_CENTER);
		DispStr_CE(0,10,"��F1�˳�...",DISP_CENTER);

	//	for (send_cnt = 0; send_cnt < db_cnt; send_cnt++) {
			pinfo = (USER_INFO*)DB_jump_to_record(ATTENDANCE_INDEX, send_cnt, &rec_flag);
			if (rec_flag) {	//��¼��ɾ��
	//			continue;
			}
			dec2hex(pinfo->phyNo, 4, infotemp);
			memcpy(rb8583, infotemp,  8);		//������
			//memcpy(rb8583+8, pinfo->time, 16);	//����ʱ��
			atd_pack(aBuffer, rb8583, 24);
			hex2dec(aBuffer, 58, (unsigned char*)send_buf, &send_len);
			//send_len = 58;
#if 0
			if (NaNo_OK !=  CWiFi_Write(g_pHandle[0], send_buf,  send_len+1) ){	//ע�����ȱ����һ�ַ�
				strcpy(retStr, "�����ϴ�ʧ��");
				break;
			}
#else
			char tempBuf[300] = {0};
			//memcpy(tempBuf, "008A600031000008000038000001C00010000001090931201104084444444444444444444431323334353630303031393930323130333131343030313030303139390072A00000000386980701202020202020203030303030303030303030303030303030303030303030303030303030304646303130303030303130312020202020203030303030303030", sizeof("008A600031000008000038000001C00010000001090931201104084444444444444444444431323334353630303031393930323130333131343030313030303139390072A00000000386980701202020202020203030303030303030303030303030303030303030303030303030303030304646303130303030303130312020202020203030303030303030"));
			memcpy(tempBuf, "ABCDEFGHIJK", 11);
			int m = strlen(tempBuf);
			//hex2dec(tempBuf, strlen(tempBuf), (unsigned char*)send_buf,  &m);
			if (NaNo_OK !=  CWiFi_Write(g_pHandle[0], tempBuf,  11+1) ){	//ע�����ȱ����һ�ַ�
				strcpy(retStr, "�����ϴ�ʧ��");
		//		break;
			}
#endif
			if( KEY_F1 == KEY_Read()) {
				strcpy(retStr, "�����ϴ��ж�");
			//	break;
			}
			Sys_Delay_MS(100);	//��ʱ100����
	//	}
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[��������]
  		return		:	[0:���ͳɹ�
  						-1:û������
  						-2:����ʧ��
  						-3:�ϴ��ж�]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
#if 0
char sendRecords(char* data_buffer, int bufferMax)
{
	unsigned char* pdBuffer = data_buffer;		//ÿ���ϴ�����ָ��
	unsigned char send_buffer[1024] = {0};		//ÿ���ϴ���������
	unsigned long	db_cnt = 0;					//���ݿ��¼��
	unsigned short	send_cnt = 0;				//�ϴ�����
	unsigned int	send_length = 0;			//�ϴ����鳤�ȣ�ÿ���ϴ����1000��
	db_cnt = DB_count_records(0);	//�������ݿ��Ѽ�¼������(������ɾ��)
	
	if (!db_cnt) {
		return -1;
	}
	db_to_str(data_buffer, bufferMax, db_cnt);	//���ݿ��¼���ַ���
	send_length = db_cnt*sizeof(USER_INFO);		//Ҫ���͵����ݳ���
	send_cnt	= send_length/MAX_SEND_BUFFER;	//Ҫ�������ݵĴ�����ÿ����෢��1000�ֽ�
	if (send_cnt%MAX_SEND_BUFFER) {
		send_cnt++;
	}
	while (send_cnt) {
		memcpy(send_buffer, pdBuffer, MAX_SEND_BUFFER);
		if (NaNo_OK ==  CWiFi_Write(g_HandleID,/*send_buffer,strlen(send_buffer)+1*/ "abcdefg", 8)) {	//ע�����ȱ����һ�ַ�
			send_cnt--;
			pdBuffer += MAX_SEND_BUFFER;
			memset(send_buffer, 0x00, 1024);
		}
		else {
			return -2;
		}
		if( KEY_F1 == KEY_Read()) {	//��F1�˳�
			return -3;
			break;
		}
		Sys_Delay_MS(100);	//��ʱ100����
	}
	return 0;
}
#endif
