/****************************************************************************
*
*�ļ�(File):         eeprom.c
*
*�޸�(Modify):       2011/7/27 10:35:09
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
| V1.00  2011/7/27 10:35:09           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"
/***********************************************************************
		module		:	[EEPROM]
		function		:	[EEPROM��]
  		return		:	[0:��ȡ�ɹ�
  						-1:��ȡʧ��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[EEPROM]
		date			:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
char eeprom_read(unsigned char* readBuffer, unsigned short sizelen, int romOffset)
{
	unsigned short idx = 0;
	char ret = 0;
	EEPROM_Init(EEPROM_ON);
	for (idx = 0; idx < sizelen; idx++) {
		if (EEPROM_Read_Byte(idx+romOffset, &readBuffer[idx])) {	//��ȡʧ��
			ret = -1;	//��ȡʧ��
			break;
		}
	}
	EEPROM_Init(EEPROM_OFF);
	return ret;
}
/***********************************************************************
		module		:	[EEPROM]
		function		:	[EEPROMд]
  		return		:	[0:д��ɹ�
  						-1:д��ʧ��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[EEPROM]
		date			:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
char eeprom_write(unsigned char* writeBuffer, unsigned short sizeLen, int romOffset)
{
	unsigned short idx = 0;
	char ret = 0;
	EEPROM_Init(EEPROM_ON);
	for (idx = 0; idx < sizeLen; idx++) {
		if (EEPROM_Write_Byte(idx+romOffset, writeBuffer[idx])) {	//д��ʧ��
			ret = -1;	//д��ʧ��
			break;
		}
	}
	EEPROM_Init(EEPROM_OFF);
	return ret;
}
/***********************************************************************
		module		:	[EEPROM]
		function		:	[shortתchar����]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[EEPROM]
		date			:	[11/07/28]
 		author		:	[chen-zhengkai]
************************************************************************/
void shortTochar(unsigned short* sh, unsigned char* s)
{
	s[0] = sh[0]>>8;
	s[1] = sh[0]&0xff;
}
/***********************************************************************
		module		:	[EEPROM]
		function		:	[char����תshort]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[EEPROM]
		date			:	[11/07/28]
 		author		:	[chen-zhengkai]
************************************************************************/
void charToshort(unsigned short* sh, unsigned char* s)
{
	sh[0] = (0xff & s[0])<<8;
	sh[0] = sh[0] | s[1];
}

