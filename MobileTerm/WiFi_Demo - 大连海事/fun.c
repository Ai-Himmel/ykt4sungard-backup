/****************************************************************************
*
*�ļ�(File):         fun.c
*
*�޸�(Modify):       2011/7/20 14:05:46
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
| V1.00  2011/7/20 14:05:46           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"
/***********************************************************************
		module		:	[�˵�����]
		function		:	[���˵�����]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/07/20]
 		author		:	[chen-zhengkai]
************************************************************************/
void main_task()
{
	int select = -1;
	char main_menu_str[] =		"1. ���ڴ�  "
							"2. ��ѯ��¼  "
							"3. ���ݴ���  "
							"4. ���ʶ��  "
							"5. ��������  "
							"6. ����Ա����";
	BROWINFO	INFO_main;
	INFO_main.iStr = main_menu_str;			
	INFO_main.lPtr = 0;
	INFO_main.cPtr = 0;
	//Disp_Set_Magnification(2);	//�Ŵ�����
	while (1) {
		//����BROWINFO�ṹ��Ա�����������ѭ�����п��ܻᱻEXT_Brow_Select�����ı�
		INFO_main.startLine = 2;		//��LCD�ϵ���ʾ��ʼ��
		INFO_main.dispLines = 6;		//��LCD�ϵ���ʾ����
		INFO_main.mInt = 6;			//��ʾ���ݵ�������
		INFO_main.lineMax = 13;		//ÿ������ַ���
		INFO_main.sFont = 0;			//7x9��������ʾ
		INFO_main.numEnable = 0;		//�Ƿ��������ּ����淽�����
		INFO_main.qEvent = EXIT_AUTO_QUIT;	 //�ɵ��º����˳����¼���־
		INFO_main.autoexit = 1200;		//�Զ��˳���ʱ��
		//�˵�
		Disp_Clear();
		DispStr_CE(0, 0, "���˵�", DISP_CENTER);
		select = EXT_Brow_Select(&INFO_main);
		switch (select) {
			case 0:		//���ڴ�
				workAttendance_task();
				break;
			case 1:		//��ѯ��¼
				vstDatabase_task();
				break;
			case 2:		//���ݴ���
				dataUpload_task();
				break;
			case 3:		//���ʶ��
				discernID_task();
				break;
			case 4:		//��������
				funSet_task();
				break;
			case 5:		//���ù���Ա����
				setAdmPsd_task();
				break;
			default:	//����CPUռ���ʣ������ܺ�
				Sys_Power_Sleep(3);
				break;
		}
	}
}
/***********************************************************************
		module		:	[�˵�����]
		function	:	[�������ò˵�����]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date		:	[11/07/20]
 		author		:	[chen-zhengkai]
************************************************************************/
void funSet_task()
{
	int select = -1;
	char fun_menu_str[] =	"1. ʱ������      "
							"2. ��������      "
							"3. ����ʱ������  "
							"4. �����ʱ������"
							"5. ����������    "
							"6. ����������ѯ  "
							"7. ��ȡ��Ȩ��    ";
	BROWINFO	info;
	info.iStr = fun_menu_str;		//�������ָ��
	info.lPtr = 0;					//��ʾ����iStr����ʼ��ʾ��
	info.cPtr = 0;					//��ǰѡ����
	

	
	while (1) {
		//����BROWINFO�ṹ��Ա�����������ѭ�����п��ܻᱻEXT_Brow_Select�����ı�
		info.startLine = 2;				//��LCD�ϵ���ʾ��ʼ��
		info.dispLines = 7;				//��LCD�ϵ���ʾ����
		info.mInt = 7;					//��ʾ���ݵ�������
		info.lineMax = 17;				//ÿ������ַ���
		info.sFont = 0;					//7x9��������ʾ
		info.numEnable = 0;				//�Ƿ��������ּ����淽�����
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //�ɵ��º����˳����¼���־
		info.autoexit = 1200;			//�Զ��˳���ʱ��
		//�˵�
		Disp_Clear();
		DispStr_CE(0, 0, "�������ò˵�", DISP_CENTER);
		select = EXT_Brow_Select(&info);
		switch (select) {
			case 0:		//ʱ������
				setTime();
				break;
			case 1:		//��������
				setDate();
				break;
			case 2:		//����ʱ������
				Set_Auto_Poweroff();
				break;
			case 3:		//�����ʱ������
				setBacklight();
				break;
			case 4:		//����������
				setKeybeeper();
				break;
			case 5:		//����������ѯ
				break;
			case 6:		//��ȡ��Ȩ��
				getAuthorize();
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
		module		:	[�˵�����]
		function	:	[���ݲ�ѯ�˵�����]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date		:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void vstDatabase_task()
{
	int select = -1;
	char db_menu_str[] =	"1. ��ѯ�Ѽ�¼��      "
							"2. ���ʣ����ü�¼��"
							"3. ɾ�����м�¼      "
							"4. ��ʼ�����ݿ�      ";
	BROWINFO	info;
	info.iStr = db_menu_str;		//�������ָ��
	info.lPtr = 0;					//��ʾ����iStr����ʼ��ʾ��
	info.cPtr = 0;					//��ǰѡ����

	while (1) {
		//����BROWINFO�ṹ��Ա�����������ѭ�����п��ܻᱻEXT_Brow_Select�����ı�
		info.startLine = 2;				//��LCD�ϵ���ʾ��ʼ��
		info.dispLines = 6;				//��LCD�ϵ���ʾ����
		info.mInt = 4;					//��ʾ���ݵ�������
		info.lineMax = 21;				//ÿ������ַ���
		info.sFont = 0;					//7x9��������ʾ
		info.numEnable = 0;				//�Ƿ��������ּ����淽�����
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //�ɵ��º����˳����¼���־
		info.autoexit = 1200;			//�Զ��˳���ʱ��
		//�˵�
		Disp_Clear();
		DispStr_CE(0, 0, "��ѯ��¼�˵�", DISP_CENTER);
		select = EXT_Brow_Select(&info);
		switch (select) {
			case 0:		//��ѯ�Ѽ�¼��
				check_recordsCnt();
				break;
			case 1:		//���ʣ����ü�¼��
				check_dbCapcity();
				break;
			case 2:		//ɾ�����м�¼
				del_Allrecords();
				break;
			case 3:		//��ʼ�����ݿ�
				db_init_menu();
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
		module		:	[�˵�����]
		function	:	[���ݴ���˵�����]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date		:	[11/07/22]
 		author		:	[chen-zhengkai]
************************************************************************/
void dataUpload_task()
{
	int select = -1;
	char db_menu_str[] =	"1. USB���� ";
							//"2. WIFI����";
	BROWINFO	info;
	info.iStr = db_menu_str;		//�������ָ��
	info.lPtr = 0;					//��ʾ����iStr����ʼ��ʾ��
	info.cPtr = 0;					//��ǰѡ����

	while (1) {
		//����BROWINFO�ṹ��Ա�����������ѭ�����п��ܻᱻEXT_Brow_Select�����ı�
		info.startLine = 0;				//��LCD�ϵ���ʾ��ʼ��
		info.dispLines = 2;				//��LCD�ϵ���ʾ����
		info.mInt = 1;					//��ʾ���ݵ�������
		info.lineMax = 11;				//ÿ������ַ���
		info.sFont = 0;					//7x9��������ʾ
		info.numEnable = 0;				//�Ƿ��������ּ����淽�����
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //�ɵ��º����˳����¼���־
		info.autoexit = 1200;			//�Զ��˳���ʱ��
		//�˵�
		Disp_Clear();
		select = EXT_Brow_Select(&info);
		switch (select) {
			case 0:		//USB����
				usb_upload_menu();
				break;
			case 1:		//WIFI����
				//wifi_upload_menu();
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
		module		:	[�˵�����]
		function		:	[��ȡ��Ȩ���������Կ��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/07/28]
 		author		:	[chen-zhengkai]
************************************************************************/
void getAuthorize()
{
	if ( !readM1Card(readAuthorizeCard) ) {
		DispStr_CE(0,6,"��Ȩ�ɹ�",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,10,"�����������",DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[�˵�����]
		function		:	[���ڼ�¼]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/01]
 		author		:	[chen-zhengkai]
************************************************************************/
void workAttendance_task()
{
	//if ( !readM1Card(workAttendance) ) {
	if ( !readM1Card(workAttendance_Dalian) ) {
		DispStr_CE(0,12,"��¼�ɹ�",DISP_CENTER);
		DispStr_CE(0,14,"�����������",DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[�˵�����]
		function		:	[���ʶ��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void discernID_task()
{
	if ( !readM1Card(discernID) ) {
		DispStr_CE(0,14,"�����������",DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[�˵�����]
		function		:	[���ù���Ա����]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void setAdmPsd_task()
{
	GETSTR_PARAM 	gs;
	char	cueStr[30] = "�������¹���Ա����";
	char remwrds[] = "(6-8λ):";
	char dspBuf[30] = {0};
	const char retStr[] = "�����������";
	char admPsd[9] = {0};
	char psdtmp[9] = {0};
	char ret = 1;

	if ( !adminPassword(1) ) {	//����ɵĹ���Ա������֤
		DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
		if (input_password(remwrds, psdtmp) ) {
			strcpy(dspBuf, "����ʧ��");
			ret = 0;
		}
		if (ret) {
			strcpy(cueStr, "���ٴ���������");
			DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
			if ( input_password(remwrds ,admPsd) ) {
				strcpy(dspBuf, "����ʧ��");
				ret = 0;
			}
		}
		if (ret && strncmp(admPsd, psdtmp, 8) ) {	//�������벻һ��
			strcpy(dspBuf, "�������벻һ��");
			ret = 0;	
		}
		if (ret && eeprom_write(admPsd, sizeof(admPsd), EEPROM_OFFSET_ADM_PSD)) {
			strcpy(dspBuf, "EEPROM��дʧ��");
			ret = 0;
		}
		if (ret) {
			strcpy(dspBuf, "�������óɹ�");
		}
		DispStr_CE(0, 6, dspBuf, DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, retStr, DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[�˵�����]
		function		:	[һ���Գ�ʼ������Ա���룬�˿ڣ�SSID��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void adminPsd_init()
{
	unsigned char psdctrl[1] = {0};
	if (eeprom_read(psdctrl, 1, EEPROM_OFFSET_ADM_CTRL)) {
		DispStr_CE(0, 6, "EEPROM�쳣", DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, "�����������", DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return;
	}
	if ( *psdctrl != 0xA5 ) {	//��Ҫ��ʼ��
		*psdctrl = 0xA5;
		if (eeprom_write(psdctrl, 1, EEPROM_OFFSET_ADM_CTRL) || eeprom_write("11111111", 8, EEPROM_OFFSET_ADM_PSD)
		|| eeprom_write("6295", 8, EEPROM_OFFSET_SERVERPORT) ||  eeprom_write("ChinaNet1", 16, EEPROM_OFFSET_SERVERSSID)
		|| eeprom_write("12345678", 16, EEPROM_OFFSET_SEVPASSWORD)) {
			DispStr_CE(0, 6, "EEPROM�쳣", DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0, 10, "�����������", DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			return;
		}
	}
}


