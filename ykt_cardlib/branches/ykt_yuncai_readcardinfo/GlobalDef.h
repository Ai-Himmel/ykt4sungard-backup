#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_
#pragma once 

#define CHARGE_TERMINAL			0x01			//  ’∑—÷’∂À
#define MANAGE_CENTER			(0x01 << 1)		// π‹¿Ì÷––ƒ
#define SAVING_POS				(0x01 << 2)		// ≥‰÷µ÷’∂À
#define DOOR_DEVICE				(0x01 << 3)		// √≈Ω˚
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// »œ÷§÷’∂À
#define AREA_CONTROL			(0x01 << 5)		// «¯”Úøÿ÷∆
#define REMAIN_BIT_SEVEN		0				// ±£¡Ù
#define REMAIN_BIT_EIGHT		0				// ±£¡Ù

#define  CARDSTAT_TYPE_REG	 		0     	//ø®◊¥Ã¨:π“ ß1-’˝≥£2-π“ ß
#define  CARDSTAT_TYPE_LOST	 		1     	//ø®◊¥Ã¨:π“ ß0-’˝≥£1-π“ ß
#define  CARDSTAT_TYPE_FREEZE		2     	//ø®◊¥Ã¨ ∂≥Ω·0-’˝≥£1-∂≥Ω·
#define  CARDSTAT_TYPE_WFAIL 		3  		//ø®◊¥Ã¨:–¥ø® ß∞‹0-’˝≥£1-–¥ø® ß∞‹

#endif	_GLOBAL_DEF_H_