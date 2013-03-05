/************************************************************************
*	System		: SIRAKABA
*	File Name	: JIG_LED.C
*	Author		: Masahiro Iida
*	Date		: 1999/10/16
*	Description	: 
*	Maintenance	: YAWARAから移植 2002/06/04 T.Takagi
*	Copyright (C) 1998 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\flash\define\jig_led.h"
#include "\src\atlanta\flash\define\sys_pro.h"
#include "\src\atlanta\flash\ext_v\sys_data.h"

CONST UBYTE	LED7Segment_Table[16] = {
	/* 0 */		0x24,
	/* 1 */		0x3f,
	/* 2 */		0x62,
	/* 3 */		0x2a,
	/* 4 */		0x39,
	/* 5 */		0xa8,
	/* 6 */		0xa0,
	/* 7 */		0x3c,
	/* 8 */		0x20,
	/* 9 */		0x28,
	/* A */		0x30,
	/* b */		0xa1,
	/* C */		0xe4,
	/* d */		0x23,
	/* E */		0xe0,
	/* F */		0xf0,
};

#if (PRO_NEW_JIG == ENABLE)		/* 白樺用梱包状態で書き換え可能治具 */
/*************************************************************************
	module		:[新治具対応：LEDのポート・アドレスの獲得]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
void	JIG_GetLedAddress(struct JIG_Led_t *led_pntr, UBYTE rom_number)
{
	switch (rom_number) {
	case ROM_NUMBER0:
	case ROM_NUMBER2:
	case CGROM_NUMBER0:
		led_pntr->UpperAddress = (UWORD *)PORT_LEFT_SUM_LED_HIGH;
		led_pntr->LowerAddress  = (UWORD *)PORT_LEFT_SUM_LED_LOW;
		break;
	case ROM_NUMBER1:
	case ROM_NUMBER3:
	case CGROM_NUMBER1:
	default:
		led_pntr->UpperAddress = (UWORD *)PORT_RIGHT_SUM_LED_HIGH;
		led_pntr->LowerAddress = (UWORD *)PORT_RIGHT_SUM_LED_LOW;
		break;
	}
}
/*************************************************************************
	module		:[新治具対応：LEDのポート・アドレスの獲得]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
void	JIG_RomNoOnLed(UBYTE rom_number)
{
	UWORD work1, work2;

	if (rom_number % 2) {	/* case ROM1/ROM3/CGROM1 */
		work1 = (SYS_ROM_LED_PortStatus & 0x00ff);
		work2 = ((UWORD)LED7Segment_Table[rom_number] << 8);
		work2 |= work1;
	} else {		/* case ROM0/ROM2/CGROM0 */
		work1 = (UWORD)LED7Segment_Table[rom_number];
		work2 = (SYS_ROM_LED_PortStatus & 0xff00);
		work2 |= work1;
	}
	SYS_ROM_LED_PortStatus = work2;
	outpw((UDWORD)PORT_ROM_NO_LED, SYS_ROM_LED_PortStatus);
}
/*************************************************************************
	module		:[新治具対応：LEDにチェックサムを表示する]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
void	JIG_SumCheckOnLed(UWORD CheckSum, UBYTE rom_number)
{
	struct JIG_Led_t port_addr;
	UWORD work1, work2;

	JIG_RomNoOnLed(rom_number);	  /* ROM番号LED点灯 */
	JIG_GetLedAddress(&port_addr, rom_number);

	work1 = (UWORD)LED7Segment_Table[((CheckSum & 0xf000) >> 12)];
	work2 = (UWORD)LED7Segment_Table[((CheckSum & 0x0f00) >> 8)];
	if (rom_number % 2) {	/* case ROM1/ROM3/CGROM1 : HARD BUG 1999.11.09  */
		work1 |= (work2 << 8);
		outpw((UDWORD)port_addr.UpperAddress, work1);
	} else {				/* case ROM0/ROM2/CGROM0 : HARD BUG 1999.11.09  */
		work2 |= (work1 << 8);
		outpw((UDWORD)port_addr.UpperAddress, work2);
	}
	work1 = (UWORD)LED7Segment_Table[((CheckSum & 0x00f0) >> 4)];
	work2 = (UWORD)LED7Segment_Table[((CheckSum & 0x000f) >> 0)];
	if (rom_number % 2) {	/* case ROM1/ROM3/CGROM1 : HARD BUG 1999.11.09 */
		work1 |= (work2 << 8);
		outpw((UDWORD)port_addr.LowerAddress, work1);
	} else {				/* case ROM0/ROM2/CGROM0 : HARD BUG 1999.11.09  */
		work2 |= (work1 << 8);
		outpw((UDWORD)port_addr.LowerAddress, work2);
	}
}
/*************************************************************************
	module		:[新治具対応：LEDに動作中表示する]
	function	:[指定されたLEDのDPを点灯/消灯させる]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
void	JIG_ReadWriteOnLed(UBYTE rom_number, UBYTE On)
{
	struct JIG_Led_t port_addr;
	UWORD work;

	JIG_RomNoOnLed(rom_number);	  /* ROM番号LED点灯 */
	JIG_GetLedAddress(&port_addr, rom_number);
	if (On != 0) {
		work = 0xdfdf;	/* Dot ON */
	} else {
		work = 0xffff;	/* All Off */
	}
	outpw((UDWORD)port_addr.UpperAddress, work);
	outpw((UDWORD)port_addr.LowerAddress, work);
}
/*************************************************************************
	module		:[新治具対応：LEDにエラーコードを表示する]
	function	:[指定されたLEDのDPを点灯/消灯させる]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
void	JIG_ErrorOnLed(UBYTE rom_number, UBYTE ErrorCode)
{
	struct JIG_Led_t port_addr;
	UWORD work1, work2;

	JIG_RomNoOnLed(rom_number);	  /* ROM番号LED点灯 */
	JIG_GetLedAddress(&port_addr, rom_number);
	if (rom_number % 2) {	/* case ROM1/ROM3/CGROM1 : HARD BUG 1999.11.09  */
		outpw((UDWORD)port_addr.UpperAddress, 0xdfe0);		/* E. */
	} else {				/* case ROM0/ROM2/CGROM0 : HARD BUG 1999.11.09  */
		outpw((UDWORD)port_addr.UpperAddress, 0xe0df);		/* E. */
	}
	work1 = (UWORD)LED7Segment_Table[((ErrorCode & 0xf0) >> 4)];
	work2 = (UWORD)LED7Segment_Table[((ErrorCode & 0x0f) >> 0)];
	if (rom_number % 2) {	/* case ROM1/ROM3/CGROM1 : HARD BUG 1999.11.09  */
		work1 |= (work2 << 8);
		outpw((UDWORD)port_addr.LowerAddress, work1);	/* E.xx */
	} else {				/* case ROM0/ROM2/CGROM0 : HARD BUG 1999.11.09  */
		work2 |= (work1 << 8);
		outpw((UDWORD)port_addr.LowerAddress, work2);	/* E.xx */
	}
}
/*************************************************************************
	module		:[新治具対応：LEDに消去する]
	function	:[指定されたLEDのすべて消灯させる]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
void	JIG_ClearLed(UBYTE rom_number)
{
	struct JIG_Led_t port_addr;

	JIG_GetLedAddress(&port_addr, rom_number);
	outpw((UDWORD)port_addr.UpperAddress, 0xffff);
	outpw((UDWORD)port_addr.LowerAddress, 0xffff);
}
/*************************************************************************
	module		:[新治具対応：CGROM有無をチェックする]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
UBYTE	JIG_CheckIsCGROM(void)
{
	if (inpw((UDWORD)PORT_CGROM_SWITCH) & IS_CGROM_BIT) {
		return(FALSE);
	}
	return(TRUE);
}
/*************************************************************************
	module		:[新治具対応：表示SWのON/OFFをチェックする]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1999/10/16]
	author		:[Masahiro Iida]
*************************************************************************/
UBYTE	JIG_CheckDisplayROM_Switch(void)
{
	UWORD counter;
	
	if (inpw((UDWORD)PORT_CGROM_SWITCH) & DISPLAY_ROMSW_BIT) {
		return(FALSE);
	}
	counter = 0;
	while (1) {
		if (inpw((UDWORD)PORT_CGROM_SWITCH) & DISPLAY_ROMSW_BIT) {
			if (counter > 200) {	/* 200回以上連続ON検出した場合 ONとみなす */
				return(TRUE);	/* SWを離した状態になってからONで抜ける */
			}
			return(FALSE);
		}
		if (counter < 65000) {
			counter++;
		}
	}
	return(FALSE);
}
#endif	/* (PRO_NEW_JIG == ENABLE) */
