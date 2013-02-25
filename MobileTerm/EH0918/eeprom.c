/****************************************************************************
*
*文件(File):         eeprom.c
*
*修改(Modify):       2011/7/27 10:35:09
*
*作者(Author):       USER
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
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
		function		:	[EEPROM读]
  		return		:	[0:读取成功
  						-1:读取失败]
		comment	:	[全局普通函数]
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
		if (EEPROM_Read_Byte(idx+romOffset, &readBuffer[idx])) {	//读取失败
			ret = -1;	//读取失败
			break;
		}
	}
	EEPROM_Init(EEPROM_OFF);
	return ret;
}
/***********************************************************************
		module		:	[EEPROM]
		function		:	[EEPROM写]
  		return		:	[0:写入成功
  						-1:写入失败]
		comment	:	[全局普通函数]
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
		if (EEPROM_Write_Byte(idx+romOffset, writeBuffer[idx])) {	//写入失败
			ret = -1;	//写入失败
			break;
		}
	}
	EEPROM_Init(EEPROM_OFF);
	return ret;
}
/***********************************************************************
		module		:	[EEPROM]
		function		:	[short转char数组]
  		return		:	[无]
		comment	:	[全局普通函数]
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
		function		:	[char数组转short]
  		return		:	[无]
		comment	:	[全局普通函数]
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

