/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: fcm_tbl.c
*	Author			: 橘正樹
*	Date			: 1997/06/23
*	RealTimeOS		: RISCモニタ
*	Description		: 
*	Maintenance		: 
*
*	Copyright (C) 1997 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\fcm_def.h"

CONST UWORD	FaxComErrorMonitorTable[SYS_FAXCOM_ERROR_MONITOR_MAX] = {
	TRANSMITERROR|0x11,		/* 0 : T.1.1	*/
	TRANSMITERROR|0x12,		/* 1 : T.1.2	*/
	TRANSMITERROR|0x14,		/* 2 : T.1.4	*/
	TRANSMITERROR|0x21,		/* 3 : T.2.1	*/
	TRANSMITERROR|0x22,		/* 4 : T.2.2	*/
	TRANSMITERROR|0x23,		/* 5 : T.2.3	*/
	TRANSMITERROR|0x31,		/* 6 : T.3.1	*/
	TRANSMITERROR|0x32,		/* 7 : T.3.2	*/
	TRANSMITERROR|0x41,		/* 8 : T.4.1	*/
	TRANSMITERROR|0x42,		/* 9 : T.4.2	*/
	TRANSMITERROR|0x44,		/* 10: T.4.4	*/
	TRANSMITERROR|0x51,		/* 11: T.5.1	*/
	TRANSMITERROR|0x52,		/* 12: T.5.2	*/
	TRANSMITERROR|0x53,		/* 13: T.5.3	*/
	TRANSMITERROR|0x81,		/* 14: T.8.1	*/
	TRANSMITERROR|0x82,		/* 15: T.8.2	*/
	TRANSMITERROR|0x83,		/* 16: T.8.3	*/
	TRANSMITERROR|0x8A,		/* 17: T.8.A	*/
	TRANSMITERROR|0x8B,		/* 18: T.8.B	*/
	RECEIVEERROR|0x11,		/* 19: R.1.1	*/
	RECEIVEERROR|0x12,		/* 20: R.1.2	*/
	RECEIVEERROR|0x14,		/* 21: R.1.4	*/
	RECEIVEERROR|0x15,		/* 22: R.1.5	*/
	RECEIVEERROR|0x23,		/* 23: R.2.3	*/
	RECEIVEERROR|0x31,		/* 24: R.3.1	*/
	RECEIVEERROR|0x32,		/* 25: R.3.2	*/
	RECEIVEERROR|0x33,		/* 26: R.3.3	*/
	RECEIVEERROR|0x34,		/* 27: R.3.4	*/
	RECEIVEERROR|0x35,		/* 28: R.3.5	*/
	RECEIVEERROR|0x41,		/* 29: R.4.1	*/
	RECEIVEERROR|0x42,		/* 30: R.4.2	*/
	RECEIVEERROR|0x44,		/* 31: R.4.4	*/
	RECEIVEERROR|0x45,		/* 32: R.4.5	*/
	RECEIVEERROR|0x46,		/* 33: R.4.6	*/
	RECEIVEERROR|0x51,		/* 34: R.5.1	*/
	RECEIVEERROR|0x52,		/* 35: R.5.2	*/
	RECEIVEERROR|0x81,		/* 36: R.8.1	*/
	RECEIVEERROR|0x82,		/* 37: R.8.2	*/
	RECEIVEERROR|0x83,		/* 38: R.8.3	*/
	RECEIVEERROR|0x8A,		/* 39: R.8.A	*/
	RECEIVEERROR|0x8B,		/* 40: R.8.B	*/
	DIALERROR|0x01,			/* 41: D.0.1	*/
	DIALERROR|0x02,			/* 42: D.0.2	*/
	DIALERROR|0x03,			/* 43: D.0.3	*/
	DIALERROR|0x06,			/* 44: D.0.6	*/
	DIALERROR|0x07,			/* 45: D.0.7	*/
	DIALERROR|0x08,			/* 46: D.0.8	*/
	DIALERROR|0x09,			/* 47: D.0.9	*/
	DIALERROR|0x0A,			/* 48: D.0.A	*/
	DIALERROR|0x0B,			/* 49: D.0.B	*/
	DIALERROR|0x0C,			/* 50: D.0.C	*/
	DIALERROR|0x0D,			/* 51: D.0.D	*/

#if defined (KEISATSU) /* 警察FAX 05/06/28 石橋正和 */
	TRANSMITERROR|0x91,		/* 52: T.9.1 指令起動信号印加/警電着信による強制終了 */
	RECEIVEERROR|0x91,		/* 53: R.9.1 指令起動信号印加/警電着信による強制終了 */
#else
										/* For NTT		*/
	0xffff,	/*TRANSMITERROR|0x29,*/		/* 52: T.2.9	*/
	0xffff,	/*TRANSMITERROR|0x2A,*/		/* 53: T.2.A	*/
#endif
	0xffff, /*TRANSMITERROR|0x2B,*/		/* 54: T.2.B	*/
	0xffff,	/*TRANSMITERROR|0x2C,*/		/* 55: T.2.C	*/
	0xffff,	/*TRANSMITERROR|0x2D,*/		/* 56: T.2.D	*/
	0xffff,	/*TRANSMITERROR|0x2E,*/		/* 57: T.2.E	*/
	0xffff,	/*TRANSMITERROR|0x2F,*/		/* 58: T.2.F	*/
	0xffff,	/*RECEIVEERROR|0x13,*/		/* 59: T.1.3	*/
	0xffff,	/*RECEIVEERROR|0x28,*/		/* 60: T.2.8	*/
	0xffff,	/*RECEIVEERROR|0x29,*/		/* 61: T.2.9	*/
	0xffff,	/*RECEIVEERROR|0x2B,*/		/* 62: T.2.B	*/
	0xffff,	/*RECEIVEERROR|0x2C,*/		/* 63: T.2.C	*/
	0xffff,	/*RECEIVEERROR|0x2E,*/		/* 64: T.2.E	*/
	0xffff,	/*RECEIVEERROR|0x2F,*/		/* 65: T.2.F	*/

	0xffff,					/* 66: 未定義	*/
	0xffff,					/* 67: 未定義	*/
	0xffff,					/* 68: 未定義	*/
	0xffff,					/* 69 :未定義	*/
};
