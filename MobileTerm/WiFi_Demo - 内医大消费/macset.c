/****************************************************************************
*
*�ļ�(File):         macset.c
*
*�޸�(Modify):       2011/7/20 15:13:15
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
| V1.00  2011/7/20 15:13:15           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"
int	input_date_time(int line,int maxNum,int minNum,int minValue,int maxValue,
	                char *pPrompt,int *retValue);	//�ж�ʱ������ڵ������Ƿ�Ϸ�

/***********************************************************************
		module		:	[�������ò���]
		function	:	[����ʱ��]
  		return		:	[0:�ɹ�
  						����:ʧ��]
		comment		:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date		:	[11/07/20]
 		author		:	[chen-zhengkai]
************************************************************************/
int setTime()
{
	typ_TIME	ttime;
	char	dBuf[40] = {0};
	const char	returnStr[] = "�����������";
	const char	cueStr[] = "������ʱ��:";
	int	ret = 0;
	int	hour = 0;
	int	minute = 0;
	int	second = 0;
	char	str1[20] = {0};
	char	str2[20] = {0};
	char	str3[20] = {0};
	
	
	RTC_Get_Time(&ttime);
	hour = ttime.hour;
	minute = ttime.min;
	second = ttime.sec;
		
	strcpy(str1,"ʱ:");
	strcpy(str2,"��:");
	strcpy(str3,"��:");
		
	while (1) {
//		sprintf(dBuf,"%02d:%02d:%02d",ttime.hour,ttime.min,ttime.sec);
//		DispStr_CE(0,0,dBuf,DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,0,cueStr,DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,4,str1,DISP_POSITION);
		DispStr_CE(0,8,str2,DISP_POSITION);
		DispStr_CE(0,12,str3,DISP_POSITION);
		
		ret = input_date_time(4,2,1,0,23,str1,&hour);
		if (ret == -1) {
			return ret;
		}
		ret = input_date_time(8,2,1,0,59,str2,&minute);	
		if (ret == -1) {
			continue;
		}
		ret = input_date_time(12,2,1,0,59,str3,&second);	
		if (ret != -1) {
			ttime.hour = hour;
			ttime.min = minute;
			ttime.sec = second;			
			RTC_Set_Time(&ttime);
			sprintf(dBuf,"%02d:%02d:%02d",hour,minute,second);						
			DispStr_CE(0,6,dBuf,DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,returnStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			return 0;
		}
	}
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[�ж������Ƿ�Ϸ�]
  		return		:	[0:�ɹ�	
  						����:ʧ��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/07/20]
 		author		:	[chen-zhengkai]
************************************************************************/
int	input_date_time(int line,int maxNum,int minNum,int minValue,int maxValue,
	                char *pPrompt,int *retValue)
{
	GETSTR_PARAM 	gs;
	int	ret = 0;
	char	dBuf[40] = {0};
	
	gs.qx = 0;
	gs.sFont = 0;
	gs.alpha = 0;
	gs.nullEnable = 1;
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = 0;
	gs.pStr = dBuf;
	gs.qEvent = 0;

	gs.qy = line;
	gs.maxNum = maxNum;
	gs.minNum = minNum;
	gs.minValue = minValue;
	gs.maxValue = maxValue;
	gs.pPrompt = pPrompt;
	gs.retNum = strlen((char*)dBuf);
	gs.qEvent = EXIT_KEY_F1|EXIT_KEY_CANCEL;
	
	ret = GetStr_E(&gs);
	if (ret == 0) {
		*retValue = gs.retValue;
	}
	return ret;
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[����ʱ��]
  		return		:	[0:�ɹ�	
  						����:ʧ��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
int setDate()
{
	typ_DATE	tdate;
	const char	returnStr[] = "�����������";
	const char	cueStr[] = "����������:";
	char	dBuf[40] = {0};
	int	ret = 0;
	int	year = 0;
	int	month = 0;
	int	day = 0;
	int	day_max = 0;
	char	str1[20] = {0};
	char	str2[20] = {0};
	char	str3[20] = {0};
	
	RTC_Get_Date(&tdate);
	year = tdate.year;
	month = tdate.month;
	day = tdate.day;
		
	strcpy(str1,"��:");
	strcpy(str2,"��:");
	strcpy(str3,"��:");
		
	while (1) {
//		sprintf(dBuf,"%04d/%02d/%02d",year,month,day);
//		DispStr_CE(0,0,dBuf,DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,0,cueStr,DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,4,str1,DISP_POSITION);
		DispStr_CE(0,8,str2,DISP_POSITION);
		DispStr_CE(0,12,str3,DISP_POSITION);
		
		ret = input_date_time(4,4,4,1980,2100,str1,&year);
		if (ret == -1) {
			return ret;
		}
		ret = input_date_time(8,2,1,1,12,str2,&month);	
		if (ret == -1) {
			continue;
		}
		
		//�ж�ÿ���µ�����
		switch (month) {
			case 1:
			case 3:
			case 5:
			case 7:
			case 8:
			case 10:
			case 12:
				day_max = 31;
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				day_max = 30;
				break;
			case 2:
				if (  ( ((year%4)==0)&&(year%100!=0) )
				   ||( (year%400)==0 )
				  ) {
					day_max = 29;
				}
				else {
					day_max = 28;
				}
				break;
			default:
				return -1;
		}
		ret = input_date_time(12,2,1,1,day_max,str3,&day);	
		if (ret != -1) {
			tdate.year = year;
			tdate.month = month;
			tdate.day = day;
			tdate.week = RTC_get_week(year,month,day);
			RTC_Set_Date(&tdate);
			
			sprintf(dBuf,"%04d/%02d/%02d",year,month,day);
			DispStr_CE(0,6,dBuf,DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,8,returnStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			
			return 0;
		}
	}
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[�����Զ�����ʱ��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void Set_Auto_Poweroff()
{
	GETSTR_PARAM 	gs;
	const char	cueStr[] = "������ʱ��(60-7200)";
	const char	retStr[] = "�����������";
	char	dspBuffer[30] = {0};
	char	qBuf[10] = {0};
	char	str[10] = {0};
	unsigned short	ac_time = 120;
	
	strcpy(str,"(��):");
	ac_time = Sys_Auto_Poweroff_Read();
	sprintf(qBuf,"%d",ac_time);
	DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
	
	gs.qx = 0;
	gs.qy = 4;
	gs.alpha = 0;
	gs.nullEnable = 1;
	gs.sFont = 0;
	gs.pPrompt = str;
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = 0;
	gs.pStr = qBuf;
	gs.maxNum = 4;
	gs.minNum = 2;
	gs.minValue = 60;
	gs.maxValue = 7200;
	gs.retNum = strlen(qBuf);
	gs.qEvent = 0;
	if ( GetStr_E(&gs) ) {
		return;
	}
	ac_time = gs.retValue;
	Sys_Auto_Poweroff_Set(ac_time);
	sprintf(dspBuffer,"%d�����óɹ�",ac_time);
	DispStr_CE(0,6,dspBuffer,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,retStr,DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	return;
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[���ñ���ƹر�ʱ��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void setBacklight()
{
	GETSTR_PARAM 	gs;
	const char	cueStr[] = "������ʱ��(5-1024)";
	const char	retStr[] = "�����������";
	char	dspBuffer[30] = {0};
	char	qBuf[10] = {0};
	char	str[10] = {0};
	unsigned short 	el_time = 0;
	
	strcpy(str,"(��):");
	el_time = EL_Get_Timeout();
	sprintf(qBuf,"%d",el_time);
	DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
	
	gs.qx = 0;
	gs.qy = 4;
	gs.alpha = 0;
	gs.nullEnable = 1;
	gs.sFont = 0;
	gs.pPrompt = str;
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = 0;
	gs.pStr = qBuf;
	gs.maxNum = 4;
	gs.minNum = 1;
	gs.minValue = 5;
	gs.maxValue = 1024;
	gs.retNum = strlen(qBuf);
	gs.qEvent = 0;
	if ( GetStr_E(&gs) ) {
		return;
	}
	el_time = gs.retValue;
	EL_set_time_out(el_time);
	sprintf(dspBuffer,"%d�����óɹ�",el_time);
	DispStr_CE(0,6,dspBuffer,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,retStr,DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	return;
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[���ð�������]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void setKeybeeper()
{
	SELE_INLINE	sss;
	char	str1[20] = {0};
	char	str2[20] = {0};
	char	str3[20] = {0};
	int	ret = 0;

	strcpy(str1,"����������");
	strcpy(str2,"��");
	strcpy(str3,"��");
	DispStr_CE(0,4,str1,DISP_CENTER|DISP_CLRSCR);

	sss.count = 2;
	sss.line = 10;
	sss.qEvent = EXIT_KEY_F1|EXIT_KEY_CANCEL|EXIT_KEY_POWER;
	sss.enable46 = 1;
	sss.defsele = 0;
	sss.autoexit = 0;
	sss.selepstr[0].xx = 80;
	sss.selepstr[1].xx = 135;
	strcpy( sss.selepstr[0].pstr, str2 );	
	strcpy( sss.selepstr[1].pstr, str3 );

	ret = EXT_Select_In_Line( &sss );
	switch (ret) {
		case 0:
			KEY_beep_mask_set(0x00000000);
			break;
		case 1:
			KEY_beep_mask_set(0xffffffff);
			break;		
		default:
			break;
	}
	return ;
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[����Ա������֤]
  		return		:	[0:	����ƥ��ɹ�
  						-1:	����ƥ�䲻�ɹ�
  						-2:	û����ȷ����
  						-3:	eeprom��дʧ��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
char adminPassword(int type)
{
//	GETSTR_PARAM 	gs;
	char	cueStr[30] = {0};
	char remwrds[] = "(6-8λ):";
	const char	retStr[] = "�����������";
	char admPsd[9] = {0};		//���������
	char admPsd_t[9] = {0};		//�ڴ��������
	
	if (type == 0) {
		strcpy(cueStr, "���������Ա����");
	}
	else {
		strcpy(cueStr, "������ɹ���Ա����");
	}
	DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
	if (input_password(remwrds, admPsd)) {
		DispStr_CE(0, 6, "����ʧ��", DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, retStr, DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return -2;
	}
	if (eeprom_read(admPsd_t, 9,  EEPROM_OFFSET_ADM_PSD)) {
		DispStr_CE(0, 6, "EEPROM��дʧ��", DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, retStr, DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return -3;
	}
	if ( strncmp(admPsd_t, admPsd, 8) ) {
		DispStr_CE(0, 6, "���벻��ȷ", DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, retStr, DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return -1;
	}
	return 0;
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[����Ա��������]
  		return		:	[0:	����ɹ�
  						-1:	����ʧ��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
int	input_password(char *pPrompt,char *dBuf)
{
	GETSTR_PARAM 	gs;
	int	ret = 0;
	
	gs.qx = 0;
	gs.sFont = 0;
	gs.alpha = 0;
	gs.nullEnable = 1;
	gs.csChar = '_';
	gs.pwChar = '*';
	gs.spChar = 0;
	gs.pStr = dBuf;
	gs.qEvent = 0;

	gs.qy = 4;
	gs.maxNum = 8;
	gs.minNum = 6;
	gs.minValue = -1;
	gs.maxValue = -1;
	gs.pPrompt = pPrompt;
	gs.retNum = strlen((char*)dBuf);
	gs.qEvent = EXIT_KEY_F1|EXIT_KEY_CANCEL;
	
	ret = GetStr_E(&gs);
	if ( !ret ) {
		return 0;
	}
	return -1;
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[�����ֳֻ�����ID]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void setPhyID(char flag)
{
	GETSTR_PARAM 	gs;
	unsigned char qBuf[15] = {0};
	char dispBuf[10] = "���óɹ�";
	if (flag) {					//�ǵ�һ�ο���
		if ( adminPassword(0) ) {
			return;
		}
	}
	gs.qx = 0;
	gs.qy = 4;
	gs.alpha = 1;
	gs.nullEnable = 1;
	gs.sFont = 0;
	gs.pPrompt = "ID(8λ): ";
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = 0;
	gs.pStr = qBuf;
	gs.maxNum = 8;
	gs.minNum = 8;
	gs.minValue = -1;
	gs.maxValue = -1;
	gs.retNum = strlen(qBuf);
	gs.qEvent = 0;
	DispStr_CE(0, 0, "�����豸ID", DISP_POSITION|DISP_CLRSCR);
	if ( GetStr_E(&gs) ) {
		return;
	}
	if ( eeprom_write(qBuf, strlen(qBuf), EEPROM_OFFSET_PHYID) ) {
		strcpy(dispBuf, "romд��ʧ��");
	}
	//debugFun(qBuf);
	DispStr_CE(0, 6, dispBuf, DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0, 10, "�����������", DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[�������ò���]
		function		:	[��ѯ�ֳֻ�����ID]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MAC_SET]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void checkPhyID()
{
	unsigned char qBuf[15] = {0};
	if ( eeprom_read(qBuf, 8, EEPROM_OFFSET_PHYID) ) {
		strcpy(qBuf, "eeprom��ȡʧ��");
	}
	//debugFun(qBuf);
	DispStr_CE(0, 10, "�����������", DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0, 8, qBuf, DISP_CENTER);
	DispStr_CE(0, 6, "�豸ID", DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}

