/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_T30.C
*	Author		: ŒKŒ´ ”ü‹I
*	Date		: 1996/11/05
*	RealTimeOS	: ‚q‚h‚r‚bi‚r‚g‚V‚O‚S‚Rjƒ‚ƒjƒ^[
*	Description	: ‚s‚R‚Oƒ‚ƒjƒ^
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
/*#include	"\src\atlanta\define\mem_max.h"*/
#include	"\src\atlanta\define\mntsw_a.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysjrnl.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\unisw_a.h"

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_tbl.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\mem_data.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\memsw\define\mems_pro.h"

#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif

#if (PRO_MODEM == R288F)
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h" /* added by H.Kubo 1998/01/06 */
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
WORD		Print_R288FInternalMonitor(void );
#endif

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if ( PRO_CPU == SH7043 )
/*#include	"\src\atlanta\sh7043\define\def_mon.h"*/	/* 97/04/20 M.Kuwahara */
#include	"\src\atlanta\sh7043\ext_v\extv_mon.h"
extern	UWORD TaskStackBottom;
#endif

#if (PRO_PANEL == ANK)
/*#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"*/
extern UBYTE	*OPR_MemoryDumpAddress;
extern UDWORD	OPR_MemoryDumpLength;
#endif

#if (PRO_PANEL == KANJI)
/*#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"*/
extern UBYTE	*OPR_MemoryDumpAddress;
extern UDWORD	OPR_MemoryDumpLength;
#endif

/***
#define MDM_ERR_LINE_DATA_MAX	10
extern UWORD	MDM_RxTotalLineSave[MDM_ERR_LINE_DATA_MAX];
extern UWORD	MDM_RxErrorTotalLineSave[MDM_ERR_LINE_DATA_MAX];
***/

#if (PRO_MULTI_LINE == ENABLE)	/* 1996/12/17 Y.Murata */
	#include	"\src\atlanta\define\dpr_pro.h"
	#include	"\src\atlanta\define\mlt_pro.h"
	#include	"\src\atlanta\define\sys_line.h"
	#include	"\src\atlanta\define\sys_opt.h"
	#include	"\src\atlanta\ext_v\mlt_data.h"
	void	P_V34DataRate(UBYTE *data);
	WORD	Print_R288FInternalMonitor(void );
	UBYTE 	LST_CheckV34Communication(void );
	UBYTE 	V34_Communication = 0;
#elif (PRO_TX_SPEED == V34) /* added by H.Kubo 1998/07/24 */
	void	P_V34DataRate(UBYTE *data);
	WORD	Print_R288FInternalMonitor(void );
	UBYTE 	LST_CheckV34Communication(void );
	UBYTE 	V34_Communication = 0;
#endif
#if (PRO_MULTI_LINE == DISABLE)	/* 1998/02/17 H.Kubo */
	#include	"\src\atlanta\ext_v\mlt_data.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)  || (PRO_PRINT_TYPE == THERMAL)	/* 1998/09/30 By M.Kuwahara */
#include "\src\atlanta\define\mon_pro.h"
#endif

/*************************************************************************
	module		:[T30ƒ‚ƒjƒ^]
	function	:[T30ƒ‚ƒjƒ^‚ðˆóü‚·‚é]
	common		:[
		List						:
		FaxComPerformingFlag		:
		SYS_OptionT30Monitor.JournalType	:
		SYS_OptionT30Monitor				:
		SYS_ProtocolMonitorPrintRequest	:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD			Print_T30Monitor(
						 void )			/*‚È‚µ*/
{
	UWORD	i;					/*SYS_OptionT30Monitor.Buffer[]‚ÌˆÊ’u*/
	WORD		j;					/*1ÌÚ°Ñ‚É‘Î‚·‚éÃÞ°À•”‚Ìˆóü‚Å*/
										/*Œ»Ý‚Ìˆóüs‚ðŽ¦‚·*/
	UBYTE	w;					/*‘ÎÛÃÞ°À”*/
	UBYTE	one_char;			/*ÌÚ°ÑŽí•Ê*/
	UBYTE	s_frame;			/*ÌÚ°ÑŽí•Ê*/
	WORD		d_long;				/*ƒf[ƒ^‚Ì’·‚³*/
	UBYTE	frame_len;			/*ÌÚ°Ñ’·(1 or 2)*/
	UBYTE	page;				/*Íß°¼Þ*/
	UBYTE	line_cnt;			/*Žc‚èˆóü‰Â”\s”*/
	UBYTE	*pt;				/*ÌÚ°Ñ–¼¾¯ÄˆÊ’u*/
											/*TX‚©RX‚©‚ÅˆÊ’u‚ªˆá‚¤ˆ×*/
	UBYTE	err_flg;			/*ÌÚ°ÑŽí•ÊˆÙí*/
											/*OFF->ˆÙí‚È‚µ*/
											/*ON ->ˆÙí‚ ‚è*/
	UBYTE	time_flg;			/*ŽžŠÔÌÚ°ÑŽžŠÔ•ÛŽÌ×¸Þ*/
											/*OFF->ŽžŠÔ•ÛŽ‚µ‚Ä‚¢‚È‚¢*/
											/*ON ->ŽžŠÔ•ÛŽ’†*/
	UWORD	end_time;			/*ŽžŠÔÌÚ°ÑI—¹ŽžŠÔ*/
	UWORD	start_time;			/*ŽžŠÔÌÚ°ÑŠJŽnŽžŠÔ*/
	DWORD	time;				/*ŽžŠÔ*/
	UBYTE	prt_flg;			/*ˆóüÌ×¸Þ*/
											/*OFF->ˆóü‚ðs‚í‚È‚¢*/
											/*ON ->ˆóü‚ðs‚¤*/
											/*’Êí‚ÌÌÚ°Ñ‚È‚ç•K‚¸ˆóü‚·‚é‚ª*/
											/*T30_START_TIME,SYS_T30_END_TIME‚Ì*/
											/*Žž‚Íˆóü‚µ‚È‚¢Žž‚ª‚ ‚é‚½‚ß*/
	UBYTE	TxRxFlg;			/*‘O‰ñÌÚ°ÑŽí•Ê*/
									/*T30TX_FRAMEBIT  ‘O‰ñTX*/
									/*SYS_T30RX_FRAMEBIT  ‘O‰ñRx*/
	register WORD	ret;		/*ŽÀsŒ‹‰Ê*/
	UBYTE	speed_handshake_flg;	/**’ZkÊÝÄÞ¼ª°¸Ì×¸Þ */ /* For ANZU By H.Hirao Apr.11,1996 */
	UBYTE	d_buffer[20];			/*DIS,DTC,DCS‚Ì“ÁŽêˆ——pÊÞ¯Ì§*/ /* 97/10/21 By M.Kuwahara */

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MODEM == R288F)	/* 1997/09/12 Y.Matsukuma */
	UBYTE		print_mdm_stat_req;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */
#endif /* (PRO_MULTI_LINE == ENABLE) || (PRO_MODEM == R288F) */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
	UWORD	bak_pt;
#endif

#if (PRO_MULTI_LINE == ENABLE)	/* 1997/09/12 Y.Matsukuma */
	UWORD			cpy_cnt;

	CMN_MemorySet( d_buffer, 20, ' ' );	/* 97/10/21 By M.Kuwahara */
	d_buffer[0]	= '\0';	/* ‚Pƒ‰ƒCƒ“‹ó”’‚ðo‚³‚È‚¢‚½‚ß 1997/11/20 Y.Matsukuma */
	print_mdm_stat_req = 0;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */
	/* V34_Communication = 0;	*/ /* Add By O.Kimoto 1997/02/24 */ /* moved to below by H.Kubo 1998/07/23 */

	CMN_DisableInterrupt();
#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1998/2/4 */
	T30PrintStackNumber = (CHK_GetT30Sign() & 0x7f);
	InternalLineNumber = 0;
	if (CHK_GetT30Sign() & 0x80) {
		InternalLineNumber = 1;
	}
#else
	T30PrintStackNumber = CHK_GetT30Sign();
#endif
	CMN_EnableInterrupt();

	T30PrintFaxComPerforming = 0;
	T30PrintFaxComResult = 0;
	T30PrintCompatiError = 0;
	T30PrintLineNumber = 0;
	LST_T30_JournalType = 0;
	LST_T30_Index = 0;
#endif
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	/* 1997/09/12 Y.Matsukuma */ /* H.Kubo 1998/07/24 */
	V34_Communication = 0;	/* Add By O.Kimoto 1997/02/24 */
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
	bak_pt = SYS_T30_END_OF_FRAME;
#endif

#if (PRO_MULTI_LINE == DISABLE)	/* 1997/09/17 Y.Matsukuma */
	/*’ÊM’†A’ÊMÃÞ°À‚È‚µAÁª¯¸*/
 #if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)
	/* SYB_T30Monitor‚Ö‚ÌÅVƒf[ƒ^‚ÌƒZƒbƒg‚ªŠÔ‚É‡‚í‚È‚¢ 1998/09/30 M.Kuwahara */
	wai_tsk(120);
 #endif
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
	if (CHK_UNI_MultiT30Monitor() && LST_T30ConfNumber != 0xFF) {
		CMN_StringCopyNum(&SYS_OptionT30Monitor.JournalType, &(SYS_T30Monitor + LST_T30ConfNumber)->JournalType, 
						  (UWORD)sizeof(struct SYS_T30MonitorData_t));	/* 1998/09/16 H.Yoshikawa */
	}
	else {
		CMN_StringCopyNum(&SYS_OptionT30Monitor.JournalType, &SYB_T30Monitor.JournalType, 
						  (UWORD)sizeof(struct SYS_T30MonitorData_t));	/* 1998/09/16 H.Yoshikawa */
	}
 #else
	CMN_StringCopyNum(&SYS_OptionT30Monitor.JournalType, &SYB_T30Monitor.JournalType, 
					  (UWORD)sizeof(struct SYS_T30MonitorData_t));	/* 1998/09/16 H.Yoshikawa */
 #endif

 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
	if (CHK_UNI_MultiT30Monitor() && LST_T30ConfNumber != 0xFF) {
		if ( (SYS_OptionT30Monitor.JournalType == SYS_T30_EMPTY) /* ’ÊMÃÞ°À‚È‚µ‚Ì•¶Žš’è‹`‚É‚·‚é By H.Hirao Apr.08,1996 */
		  || (SYS_OptionT30Monitor.WritePointer == 0)) {
			if ( MEM_INDEX_FAT_DUMP == (SYB_MaintenanceSwitch[MNT_SW_A7] & MEM_INDEX_FAT_DUMP )) {
				ret = Memory_Dump();								/*ÒÓØDUMP*/
			}
			if (SYB_MaintenanceSwitch[MNT_SW_A7] & ITORON_MEMORY_DUMP) {
				ret = Tsk_Dump();									/*À½¸DUMP*/
			}
			if (SYB_MaintenanceSwitch[MNT_SW_A8] & DPRAM_MONITOR_PRINT) {
				ret = Dpram_Dump();								/* DRAM’ÊM—š—ð */
			}
			SYS_ProtocolMonitorPrintRequest = 0;
			return ( ret );
			/*Memory_Dump(),Tsk_Dump()‚ðíœ‚·‚éŽž‚ÍA‚±‚±‚ÍMSG_PRN_LST_NO_LIST‚ÅØÀ°Ý‚·‚éŽ–B*/
		}
	}
	else {
		if ( (FaxComPerformingFlag != YES && SYS_OptionT30Monitor.JournalType == SYS_T30_EMPTY) /* ’ÊMÃÞ°À‚È‚µ‚Ì•¶Žš’è‹`‚É‚·‚é By H.Hirao Apr.08,1996 */
		  || (SYS_OptionT30Monitor.WritePointer == 0)) {
			if ( MEM_INDEX_FAT_DUMP == (SYB_MaintenanceSwitch[MNT_SW_A7] & MEM_INDEX_FAT_DUMP )) {
				ret = Memory_Dump();								/*ÒÓØDUMP*/
			}
			if (SYB_MaintenanceSwitch[MNT_SW_A7] & ITORON_MEMORY_DUMP) {
				ret = Tsk_Dump();									/*À½¸DUMP*/
			}
			if (SYB_MaintenanceSwitch[MNT_SW_A8] & DPRAM_MONITOR_PRINT) {
				ret = Dpram_Dump();								/* DRAM’ÊM—š—ð */
			}
			SYS_ProtocolMonitorPrintRequest = 0;
			return ( ret );
			/*Memory_Dump(),Tsk_Dump()‚ðíœ‚·‚éŽž‚ÍA‚±‚±‚ÍMSG_PRN_LST_NO_LIST‚ÅØÀ°Ý‚·‚éŽ–B*/
		}
	}
 #else
	if ( (FaxComPerformingFlag != YES && SYS_OptionT30Monitor.JournalType == SYS_T30_EMPTY) /* ’ÊMÃÞ°À‚È‚µ‚Ì•¶Žš’è‹`‚É‚·‚é By H.Hirao Apr.08,1996 */
	  || (SYS_OptionT30Monitor.WritePointer == 0)) {
		if ( MEM_INDEX_FAT_DUMP == (SYB_MaintenanceSwitch[MNT_SW_A7] & MEM_INDEX_FAT_DUMP )) {
			ret = Memory_Dump();								/*ÒÓØDUMP*/
		}
		if (SYB_MaintenanceSwitch[MNT_SW_A7] & ITORON_MEMORY_DUMP) {
			ret = Tsk_Dump();									/*À½¸DUMP*/
		}
		if (SYB_MaintenanceSwitch[MNT_SW_A8] & DPRAM_MONITOR_PRINT) {
			ret = Dpram_Dump();								/* DRAM’ÊM—š—ð */
		}
		SYS_ProtocolMonitorPrintRequest = 0;
		return ( ret );
		/*Memory_Dump(),Tsk_Dump()‚ðíœ‚·‚éŽž‚ÍA‚±‚±‚ÍMSG_PRN_LST_NO_LIST‚ÅØÀ°Ý‚·‚éŽ–B*/
	}
 #endif

 #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/06 */
	MDM_GetInternalStatus();
	print_mdm_stat_req = 1;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */
 #endif /* (PRO_MODEM == R288F)*/
	LST_T30_JournalType = SYS_OptionT30Monitor.JournalType;	/* 1998/10/07 By M.Kuwahara */
	LST_T30_Index = SYS_OptionT30Monitor.Index;

#else	/* ‚Q‰ñü */

 #if defined(POPLAR_F)

	if (T30PrintStackNumber == 0xFF) {
		/* Nothing */
	}
	else {
		T30PrintLineNumber = OPT_GetMultiLinrNumber(T30PrintStackNumber);
		if (LST_T30ConfNumber == 0xFF) {
			if (T30PrintStackNumber == 0x00) {	/* Î½Ä */
				CMN_StringCopyNum(&SYS_OptionT30Monitor.JournalType, &SYB_T30Monitor.JournalType, 
									(UWORD)sizeof(struct SYS_T30MonitorData_t));
				if (FaxComPerformingFlag) {
					T30PrintFaxComPerforming = 1;
				}
				else {
					T30PrintFaxComPerforming = 0;
				}
				T30PrintFaxComResult = FaxComResult;
				T30PrintCompatiError = FaxCompatibleErrorCode;
				for (cpy_cnt = 0; cpy_cnt < OPT_ERR_LINE_DATA_MAX; cpy_cnt++) {
					LST_RxTotalLineSave[cpy_cnt] = MDM_RxTotalLineSave[cpy_cnt];
					LST_RxErrorTotalLineSave[cpy_cnt] = MDM_RxErrorTotalLineSave[cpy_cnt];
				}
				MDM_GetInternalStatus();
				print_mdm_stat_req = 1;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */
			}
			else {	/* µÌß¼®Ý */
				DPR_GetT30Buffer((UWORD *)&SYS_OptionT30Monitor.JournalType, (UWORD)(T30PrintStackNumber - 1));

				/* ‚q‚Q‚W‚W‚eƒ‚ƒfƒ€“à•”ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg */
				DPR_GetInternalStatus((UWORD)(T30PrintStackNumber - 1));
				print_mdm_stat_req = 1;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */

				if (SYS_OptionLineStatus[T30PrintStackNumber] & SYS_OPTION_LINE_BUSY) {
					T30PrintFaxComPerforming = 1;
				}
				else {
					T30PrintFaxComPerforming = 0;
				}
				T30PrintFaxComResult = SYS_Opt[T30PrintStackNumber].FaxComResult;
				T30PrintCompatiError = SYS_Opt[T30PrintStackNumber].FaxCompatibleErrorCode;
				for (cpy_cnt = 0; cpy_cnt < OPT_ERR_LINE_DATA_MAX; cpy_cnt++) {
					LST_RxTotalLineSave[cpy_cnt] = SYS_Opt[T30PrintStackNumber].MDM_RxTotalLineSave[cpy_cnt];
					LST_RxErrorTotalLineSave[cpy_cnt] = SYS_Opt[T30PrintStackNumber].MDM_RxErrorTotalLineSave[cpy_cnt];
				}
			}
			LST_T30_JournalType = MLT_T30Type[T30PrintStackNumber];
			LST_T30_Index = MLT_T30Index[T30PrintStackNumber];
		}
		else {
			CMN_StringCopyNum(	&SYS_OptionT30Monitor.JournalType, 
								&SYB_T30MonitorDRAM[LST_T30ConfNumber].JournalType, 
								(UWORD)sizeof(struct SYS_T30MonitorData_t));
			T30PrintCompatiError = SYB_CompatibleErrorCode[LST_T30ConfNumber];
			for (cpy_cnt = 0; cpy_cnt < OPT_ERR_LINE_DATA_MAX; cpy_cnt++) {
				LST_RxTotalLineSave[cpy_cnt] = 0;
				LST_RxErrorTotalLineSave[cpy_cnt] = 0;
			}
			LST_T30_JournalType = SYB_T30MonitorDRAM[LST_T30ConfNumber].JournalType;
			LST_T30_Index = SYB_T30MonitorDRAM[LST_T30ConfNumber].Index;
		}
	}

 #else

	if (T30PrintStackNumber == 0xFF) {
		/* Nothing */
	}
	else {
		T30PrintLineNumber = OPT_GetMultiLinrNumber(T30PrintStackNumber);
		if (T30PrintStackNumber == 0x00) {	/* Î½Ä */
			CMN_StringCopyNum(&SYS_OptionT30Monitor.JournalType, &SYB_T30Monitor.JournalType, (UWORD)sizeof(struct SYS_T30MonitorData_t));
			if (FaxComPerformingFlag) {
				T30PrintFaxComPerforming = 1;
			}
			else {
				T30PrintFaxComPerforming = 0;
			}
			T30PrintFaxComResult = FaxComResult;
			T30PrintCompatiError = FaxCompatibleErrorCode;
			for (cpy_cnt = 0; cpy_cnt < OPT_ERR_LINE_DATA_MAX; cpy_cnt++) {
				LST_RxTotalLineSave[cpy_cnt] = MDM_RxTotalLineSave[cpy_cnt];
				LST_RxErrorTotalLineSave[cpy_cnt] = MDM_RxErrorTotalLineSave[cpy_cnt];
			}
  #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/06 */
			MDM_GetInternalStatus();
			print_mdm_stat_req = 1;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */
  #else
			print_mdm_stat_req = 0;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO By O.Kimoto 1996/09/13 */
  #endif /* (PRO_MODEM == R288F)*/

		}
		else {	/* µÌß¼®Ý */
			DPR_GetT30Buffer((UWORD *)&SYS_OptionT30Monitor.JournalType, (UWORD)(T30PrintStackNumber - 1));

			/* ‚q‚Q‚W‚W‚eƒ‚ƒfƒ€“à•”ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg */
			DPR_GetInternalStatus((UWORD)(T30PrintStackNumber - 1));
			print_mdm_stat_req = 1;	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO */

			if (SYS_OptionLineStatus[T30PrintStackNumber] & SYS_OPTION_LINE_BUSY) {
				T30PrintFaxComPerforming = 1;
			}
			else {
				T30PrintFaxComPerforming = 0;
			}
			T30PrintFaxComResult = SYS_Opt[T30PrintStackNumber].FaxComResult;
			T30PrintCompatiError = SYS_Opt[T30PrintStackNumber].FaxCompatibleErrorCode;
			for (cpy_cnt = 0; cpy_cnt < OPT_ERR_LINE_DATA_MAX; cpy_cnt++) {
				LST_RxTotalLineSave[cpy_cnt] = SYS_Opt[T30PrintStackNumber].MDM_RxTotalLineSave[cpy_cnt];
				LST_RxErrorTotalLineSave[cpy_cnt] = SYS_Opt[T30PrintStackNumber].MDM_RxErrorTotalLineSave[cpy_cnt];
			}
		}
		LST_T30_JournalType = MLT_T30Type[T30PrintStackNumber];
		LST_T30_Index = MLT_T30Index[T30PrintStackNumber];
	}
 #endif
#endif

	page = 1;
	if ( (ret = Print_T30Monitor_Head( 0, page ) ) != OK ) {
		return ( ret );
	}
	line_cnt = (UBYTE)(PaperSizeLen() - 20);

	err_flg = OFF;
	time_flg = OFF;
	prt_flg = ON;
	i = 0;
	TxRxFlg = SYS_T30TX_FRAMEBIT;
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/30 Y.Matsukuma */
	while (1) {
		if (SYB_T30Monitor.Flag) {
			if (i == SYB_T30Monitor.A_Pointer 
				&& bak_pt != SYB_T30Monitor.B_Pointer) {
				i = SYB_T30Monitor.B_Pointer;
				bak_pt = SYB_T30Monitor.B_Pointer;
				/* 1sü */
				CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				line_cnt--;
				/*‰üÍß°¼Þ‚ÌÁª¯¸*/
				if ( line_cnt == 0) {
					page++;
					if ( (ret = Print_T30Monitor_Head( 1, page ) ) != OK ) {
						return ( ret );
					}
					if ( (ret = Print_T30Monitor_Head( 0, page ) ) != OK ) {
						return ( ret );
					}
					line_cnt = (UBYTE)(PaperSizeLen() - 4 );
				}
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				List.S.Print[1-1] = LST_KLINEI;
				List.S.Print[80-1] = LST_KLINEI;
			}
			else if (SYS_OptionT30Monitor.Buffer[i] == SYS_T30_END_OF_FRAME 
				&& bak_pt == SYB_T30Monitor.B_Pointer) {
				if (SYB_T30Monitor.A_Pointer == SYB_T30Monitor.B_Pointer) {
					break;
				}
				i = SYB_T30Monitor.A_Pointer;
				bak_pt = SYS_T30_END_OF_FRAME;
			}
			else if (SYS_OptionT30Monitor.Buffer[i] == SYS_T30_END_OF_FRAME 
				&& bak_pt == SYS_T30_END_OF_FRAME) {
				break;
			}
		}
		else {
			if (SYS_OptionT30Monitor.Buffer[i] == SYS_T30_END_OF_FRAME
				|| i > SYS_T30MONITOR_BUF_MAX) {
				break;
			}
		}
#else
	while ( SYS_OptionT30Monitor.Buffer[i] != SYS_T30_END_OF_FRAME
	  && i < SYS_T30MONITOR_BUF_MAX ) {
#endif
		if ( err_flg == ON ) {							/*ÌÚ°ÑŽí•ÊˆÙí*/
			break;
		}
		one_char = SYS_OptionT30Monitor.Buffer[i];
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[1-1] = LST_KLINEI;
		List.S.Print[80-1] = LST_KLINEI;

		/*TX/RX‚É‚æ‚é–¼Ì¾¯ÄˆÊ’u‚ÌÝ’è.TX/RX‚É‚æ‚é‘O‰ñÌÚ°ÑŽí•Ê‚ÌÝ’è*/
		pt = &List.S.Print[2-1];
		if ( one_char & SYS_T30RX_FRAMEBIT ) {			/*__________________________________________________*/
			pt = &List.S.Print[14-1];					/*| ÌÚ°ÑŽí•Ê | ÃÞ°À’· | Ì×¸Þ¼°¹Ý½ 8ËÞ¯Ä‚Ì–³‚¢HDLC | */
			TxRxFlg = SYS_T30RX_FRAMEBIT;				/*PPPPPPPPPPPPPPPPPPPPPPPPP*/
		}
		if ( one_char & SYS_T30TX_FRAMEBIT ){
			TxRxFlg = SYS_T30TX_FRAMEBIT;
		}
		/*ÌÚ°Ñ–¼Ì‚Ì¾¯Ä*/
		s_frame = 0;
		if ( one_char == SYS_T30_TX_FRAME || one_char == SYS_T30_RX_FRAME ) {
			i++;
			d_long = SYS_OptionT30Monitor.Buffer[i]-2;
			i += 3;
			s_frame = SYS_OptionT30Monitor.Buffer[i];
			GetFrameName( LST_FAX_CTRL, SYS_OptionT30Monitor.Buffer[i], pt );
			frame_len = 1;
			if ( *pt != '?' ) {
				/*PPS,EOR‚Í2ÊÞ²Äº°ÄÞ*/
				if ( Xmask(SYS_OptionT30Monitor.Buffer[i]) == PPS_F
				  || Xmask(SYS_OptionT30Monitor.Buffer[i]) == EOR_F ) {/*2byte */
					*(pt+3) = '.';
					GetFrameName( LST_FAX_CTRL, SYS_OptionT30Monitor.Buffer[i+1],
					  (pt+4) );
					frame_len ++;
				}
				/**ÌÚ°Ñ–¼Ì‚ªNSS‚Ì‚Æ‚«’ZkÊÝÄÞ¼ª°¸‚©‚Ç‚¤‚©‚ðÌ×¸Þ‚ÉƒZƒbƒg */ /**For ANZU By H.Hirao Apr.11,1996 */
				if ( Xmask(SYS_OptionT30Monitor.Buffer[i]) == NSS_F ) {
					if ( (SYS_OptionT30Monitor.Buffer[i+4] & 0x20) == 0x20 ) {		/**’ZkÊÝÄÞ¼ª°¸‚ÌËÞ¯Ä‚ª1‚Ìê‡ */
						speed_handshake_flg = YES;
					} else {
						speed_handshake_flg = NO;
					}
				}
			}
			else {
				/*Ì§¸¼ÐØ§ŒäÌ¨°ÙÄÞÃÞ°À‚ªˆÙí‚¾‚Á‚½ˆ×AÃÞ°Àˆóü‚ðÌ§¸¼ÐØ§Œä*/
				/*Ì¨°ÙÄÞ‚©‚çŽn‚ß‚é*/
			}
			time_flg = OFF;
		}
		else {
			if ( one_char & SYS_T30_TIMEBIT ) {
				prt_flg = OFF;
				d_long = 0;
				i++;
				if ( one_char == SYS_T30_END_TIME ) {
					end_time = ((UWORD)SYS_OptionT30Monitor.Buffer[i]*0x100)
					  + (UWORD)SYS_OptionT30Monitor.Buffer[i+1];
					time_flg = ON;
				}
				else {
					if ( time_flg == ON ) {
						start_time = ((UWORD)SYS_OptionT30Monitor.Buffer[i]
						  *0x100) + (UWORD)SYS_OptionT30Monitor.Buffer[i+1];
						time = start_time - end_time;
						if ( TxRxFlg == SYS_T30TX_FRAMEBIT ) {
							time += SYS_T30_TIME_ADJ_NEG;
						}
						else {
							time += SYS_T30_TIME_ADJ_POS;
						}
						if ( time < 0 ) {
							time = 0;
						}
						CMN_MemorySet( pt, 6, '-' );
						CMN_UnsignedIntToASC( (pt+7), (UWORD)time/100,
						  2, '0' );
						*(pt+9) = '"';
						CMN_UnsignedIntToASC( (pt+10), (UWORD)time%100,
						  2, '0' );
						CMN_MemorySet( (pt+13), 6, '-' );
						time_flg = OFF;
						if ( CHK_UNI_T30_IntervalPrint() ) {
							prt_flg = ON;
						}
					}
				}
				i += 2;
			}
			else {
				if ( SYS_OptionT30Monitor.Buffer[i] == SYS_T30_RX_TCF ) {
					/*RX_TCF‚ÌŽž‚Ì‚ÝÃÞ°À‚ ‚è*/
					i++;
					d_long = SYS_OptionT30Monitor.Buffer[i];
					i++;
				}
#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/06  */
				else if ( SYS_OptionT30Monitor.Buffer[i] == SYS_T30_TX_TCF ) {
					/*TX_TCF‚ÌŽž‚àÃÞ°À‚ ‚è*/
					i++;
					d_long = SYS_OptionT30Monitor.Buffer[i];
					i++;
				}
#endif
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34) 	/* 1997/09/04 Y.Matsukuma */ /* V34 is added by H.Kubo 1998/07/23 */
				else if ((SYS_OptionT30Monitor.Buffer[i] == SYS_T30_TX_PIX) || (SYS_OptionT30Monitor.Buffer[i] == SYS_T30_RX_PIX)) {
					if ((SYS_OptionT30Monitor.Buffer[i+1] == SYS_T30_V34_TX_RATE) ||
						(SYS_OptionT30Monitor.Buffer[i+1] == SYS_T30_V34_RX_RATE)) {

						if (SYS_OptionT30Monitor.Buffer[i+1] == SYS_T30_V34_TX_RATE) {
							one_char = SYS_T30_V34_TX_RATE;
						}
						else {
							one_char = SYS_T30_V34_RX_RATE;
						}
						i = i + 2;
						d_long = SYS_OptionT30Monitor.Buffer[i];
						i++;
					}
					else {
						d_long = 1;
					}
				}
#endif
				else {
					d_long = 1;
				}
				GetFrameName( LST_TCF_PIX, one_char, pt );
				if ( *pt == '?' ) {
					err_flg = ON;
				}
				/*i++;*/
				time_flg = OFF;
			}
		}
		/*ÃÞ°À‚Ì¾¯Ä‚Æˆóü*/
		j = 0;
		while ( 1 ) {
			if ( d_long > 0 ) {
				/*w -> 1s‚Éˆóü‚·‚éÃÞ°À”*/
				w = (UBYTE)(d_long - LST_T30_DATA_FLD*j);
				if ( w >= LST_T30_DATA_FLD ) {
					w = LST_T30_DATA_FLD;
				}
#if (PRO_MULTI_LINE == DISABLE) &&  (PRO_TX_SPEED != V34) /* V34 is added by H.Kubo 1998/07/23 */
				if (one_char != SYS_T30_TX_TCF && one_char != SYS_T30_TX_PIX && one_char != SYS_T30_RX_PIX) {
					/*ÃÞ°ÀÌ¨°ÙÄÞ•¶Žš—ñ•ÏŠ·*/
					DataFieldSet( &SYS_OptionT30Monitor.Buffer[i+j*LST_T30_DATA_FLD], w, &List.S.Print[27-1] );
				}
#else
#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* Tx TCF ‚Éƒ‚ƒfƒ€‚Ì CONF ‚ð•\Ž¦‚·‚éBby H.Kubo 1998/10/06  */
				if ((one_char != SYS_T30_TX_PIX) &&

#else
				if ((one_char != SYS_T30_TX_TCF) &&
					(one_char != SYS_T30_TX_PIX) &&
#endif
					(one_char != SYS_T30_RX_PIX) &&
					(one_char != SYS_T30_TX_CJ) &&
					(one_char != SYS_T30_TX_CI) &&
					(one_char != SYS_T30_TX_ANS) &&
					(one_char != SYS_T30_RX_CJ) &&
					(one_char != SYS_T30_RX_CI) &&
					(one_char != SYS_T30_RX_ANS) &&
					(one_char != SYS_T30_RX_CED)) {

					/*ÃÞ°ÀÌ¨°ÙÄÞ•¶Žš—ñ•ÏŠ·*/
					DataFieldSet( &SYS_OptionT30Monitor.Buffer[i+j*LST_T30_DATA_FLD],
					  w, &List.S.Print[27-1] );
				}
				if ((one_char == SYS_T30_V34_TX_RATE) || (one_char == SYS_T30_V34_RX_RATE)) {
					P_V34DataRate(&SYS_OptionT30Monitor.Buffer[i]);
				}
#endif
				/*DIS,DTC,DCS‚Ì“ÁŽêˆ—*/
				if ( Xmask(s_frame) == DIS_F || Xmask(s_frame) == DTC_F
				  || Xmask(s_frame) == DCS_F ) {
#if (PRO_MULTI_LINE == ENABLE)	|| (PRO_TX_SPEED == V34) /* Add By 1997/09/04 Y.Matsukuma */ /* V34 condition is added by H.Kubo 1998/07/23 */
					if (Xmask(s_frame) == DCS_F ) {
						V34_Communication = LST_CheckV34Communication();
					}
#endif
					if ( (UBYTE)(4+frame_len) <= w &&
					  w <= (UBYTE)(8+frame_len) ) {
						SettingName( TxRxFlg, speed_handshake_flg,
						  s_frame, &SYS_OptionT30Monitor.Buffer[i+frame_len+
						  j*LST_T30_DATA_FLD], (UBYTE)(w-frame_len),
						  &List.S.Print[60-1], &List.S.Attribute[60-1] );
					}
					else{				/* 97/10/21 Add By M.Kuwahara */
						SettingName( TxRxFlg, speed_handshake_flg,
						  s_frame, &SYS_OptionT30Monitor.Buffer[i+frame_len+
						  j*LST_T30_DATA_FLD], (UBYTE)(w-frame_len),
						  d_buffer, List.S.Work );
					}
				}
				/*CTC‚Ì“ÁŽêˆ—*/
				if ( Xmask(s_frame) == CTC_F &&
				  w == (UBYTE)(2+frame_len) ) {
					List.S.Print[60-1] = '[';
					List.S.Print[64-1] = ']';
					/*ÃÞ°ÀM†‘¬“x*/
					SettingSpeed(SYS_OptionT30Monitor.Buffer[i+frame_len+j*LST_T30_DATA_FLD+1],
								 &List.S.Print[61-1],
								 &List.S.Attribute[61-1]);
				}
			}
			if ( prt_flg == ON ) {
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				line_cnt--;
				/* DIS,DTC,DCS‚Ì[¥¥¥¥]‚ðˆês‚É‘‚«Ø‚ê‚È‚¢Žž,[¥¥¥¥]‚Í‰üs‚µ‚Äo—Í‚·‚é 97/10/21 By M.Kuwahara */
				if ( d_buffer[0] != '\0' ) {
#if (PRO_PAPER_TYPE==CUT_PAPER)	/* 1998/04/23 M.Kuwahara	 */
				/*‰üÍß°¼Þ‚ÌÁª¯¸*/
					if ( line_cnt == 0 ) {
						page++;
						if ( (ret = Print_T30Monitor_Head( 1, page ) ) != OK ) {
							return ( ret );
						}
						if ( (ret = Print_T30Monitor_Head( 0, page ) ) != OK ) {
							return ( ret );
						}
						line_cnt = (unsigned char)(PaperSizeLen() - 4 );
					}
#endif
					Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
					List.S.Print[1-1] = LST_KLINEI;
					/** List.S.Print[80-1] = LST_KLINEI; By M.Kuwahara 98/04/23 */
					/** CMN_StringCopy( &List.S.Print[60-1], d_buffer );*/
					CMN_StringCopyNumOrNULL( &List.S.Print[60-1], d_buffer, 19 );
					List.S.Print[80-1] = LST_KLINEI;
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					d_buffer[0]	= '\0';
					line_cnt--;
				}
			}
			prt_flg = ON;
#if (PRO_PAPER_TYPE==CUT_PAPER)
			/*‰üÍß°¼Þ‚ÌÁª¯¸*/
			if ( line_cnt == 0 && (
			  (j+1) < ((d_long+LST_T30_DATA_FLD-1)/LST_T30_DATA_FLD) ||
			  ( (j+1) >= ((d_long+LST_T30_DATA_FLD-1)/LST_T30_DATA_FLD) &&
			  CheckEndOfFrame(i+d_long) == NG ) )) {/*94/09/12 By j.masuda */
				page++;
				if ( (ret = Print_T30Monitor_Head( 1, page ) ) != OK ) {
					return ( ret );
				}
				if ( (ret = Print_T30Monitor_Head( 0, page ) ) != OK ) {
					return ( ret );
				}
				line_cnt = (UBYTE)(PaperSizeLen() - 4 );
			}
#endif
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = LST_KLINEI;
			List.S.Print[80-1] = LST_KLINEI;
/* #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 *//* 1998/10/27 By M.Kuwahara */
			CMN_MemorySet( d_buffer, 20, ' ' );	/* 97/10/21 By M.Kuwahara */
			d_buffer[0]	= '\0';	/* ‚Pƒ‰ƒCƒ“‹ó”’‚ðo‚³‚È‚¢‚½‚ß 1997/11/20 Y.Matsukuma */
/* #endif */
			j++;
			/*ÃÞ°À‚ª‘S‚Äˆóü‚³‚ê‚½‚©Áª¯¸*/
			if ( j >= ((d_long+LST_T30_DATA_FLD-1)/LST_T30_DATA_FLD) ) {
				break;
			}
		}
		i += d_long;
	}
	if ( (ret = Print_T30Monitor_Head( 2, page ) ) != OK ) {
		return ( ret );
	}

	if( CHK_ErrorLineDisplay() != 0 ) {
#if (PRO_PAPER_TYPE==CUT_PAPER)
		/*94/09/12 By j.masuda «««‰üÍß°¼ÞÁª¯¸‚ð’Ç‰Á*/
		/* line_cnt --;											@*94/09/12 Comment BY H.H 1997/01/30 */
		
		/** line_cnt == 0‚Å‚±‚ÌƒpƒX‚É“ü‚é‚Æ‰üƒy[ƒW‚ðs‚¦‚Ü‚¹‚ñ
		***		««««						BY H.H 1997/01/30
		**/
		if (line_cnt != 0) {
			line_cnt--;
		}
		/*‰ü•ÅÁª¯¸*/											/*94/09/12*/
		if ( line_cnt <= 0 ) {									/*94/09/12*/
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {	/*94/09/12*/
				return ( ret );									/*94/09/12*/
			}													/*94/09/12*/
			if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {	/*94/09/12*/
				return ( ret );									/*94/09/12*/
			}													/*94/09/12*/
			line_cnt = (UBYTE)(PaperSizeLen() - 4 );					/*94/09/12*/
		}														/*94/09/12*/
		/*94/09/12 By j.masuda ªªª*/
#endif
	/*Œ´e´×°s”‚Ìˆóü*/
		for ( i = 0 ; i < MDM_ERR_LINE_DATA_MAX; i++ ) {
#if (PRO_MULTI_LINE == ENABLE)
			if ( LST_RxTotalLineSave[i] == 0 ) {
				break;
			}
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = '[';
			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(i+1), 2, '0');
			List.S.Print[4-1] = ']';
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)LST_RxErrorTotalLineSave[i], 5, '0');
			List.S.Print[11-1] = '/';
			CMN_UnsignedIntToASC( &List.S.Print[12-1], (UWORD)LST_RxTotalLineSave[i], 5, '0');
#else
			if ( MDM_RxTotalLineSave[i] == 0 ) {
				break;
			}
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = '[';
			CMN_UnsignedIntToASC( &List.S.Print[2-1], (UWORD)(i+1), 2, '0');
			List.S.Print[4-1] = ']';
			CMN_UnsignedIntToASC( &List.S.Print[6-1], (UWORD)MDM_RxErrorTotalLineSave[i], 5, '0');
			List.S.Print[11-1] = '/';
			CMN_UnsignedIntToASC( &List.S.Print[12-1], (UWORD)MDM_RxTotalLineSave[i], 5, '0');
#endif
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
#if (PRO_PAPER_TYPE==CUT_PAPER)
			/*‰ü•ÅÁª¯¸*/
			line_cnt --;
			if ( line_cnt <= 0 ) {
#if (PRO_MULTI_LINE == ENABLE)								/* 97/12/05 By M.Kuwahara */
				if (((i + 1) >= MDM_ERR_LINE_DATA_MAX ) ||	/* ‘S‚Ä‚ÌƒGƒ‰[s”‚ðˆóŽš‚µ‚½‚©H 97/10/24 By M.Kuwahara */
					( LST_RxTotalLineSave[i+1] == 0 )) {
					break;
				}
#else
				if (((i + 1) >= MDM_ERR_LINE_DATA_MAX ) ||	/* ‘S‚Ä‚ÌƒGƒ‰[s”‚ðˆóŽš‚µ‚½‚©H 97/10/24 By M.Kuwahara */
					( MDM_RxTotalLineSave[i+1] == 0 )) {
					break;
				}
#endif
				if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
					return ( ret );
				}
				line_cnt = (UBYTE)(PaperSizeLen() - 4 );
			}
#endif
		}
	}
	/*‚PsˆóŽši‰üsj*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
		return ( ret );
	}

#if (PRO_MULTI_LINE == DISABLE)	/* 1997/10/18 */
	SYS_ProtocolMonitorPrintRequest = 0;
#else

	if (SYS_DocumentPrintNo == 0) {
		SYS_ProtocolMonitorPrintRequest = 0;
	}
	else if (SYS_DocumentPrintNo == 1) {
		SYS_OptionLineT30PrintRequest = 0;
	}
	else {
		SYS_ProtocolMonitorPrintRequest = 0;
		SYS_OptionLineT30PrintRequest = 0;
	}

#endif

	if ( MEM_INDEX_FAT_DUMP == (SYB_MaintenanceSwitch[MNT_SW_A7] & MEM_INDEX_FAT_DUMP )) {
		ret = Memory_Dump();								/*ÒÓØDUMP*/
		if ( ret != OK ) {
			return ( ret );
		}
	}
	if (SYB_MaintenanceSwitch[MNT_SW_A7] & ITORON_MEMORY_DUMP) {
		ret = Tsk_Dump();									/*À½¸DUMP*/
		if ( ret != OK ) {
			return ( ret );
		}
	}
	if (SYB_MaintenanceSwitch[MNT_SW_A8] & DPRAM_MONITOR_PRINT) {
		ret = Dpram_Dump();								/* DRAM’ÊM—š—ð */
		if ( ret != OK ) {
			return ( ret );
		}
	}

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MODEM == R288F)	/* Add By 1997/09/12 Y.Matsukuma */ /* PRO_MODEM is added by H.Kubo 1998/01/06 */
	/* ‚q‚Q‚W‚W‚eƒ‚ƒfƒ€“à•”ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg
	** BY O.Kimoto 1996/12/20
	*/
	if (print_mdm_stat_req == 1) {	/* ƒ‚ƒfƒ€ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg—v‹ƒtƒ‰ƒO By O.Kimoto 1996/09/13 */
		ret = Print_R288FInternalMonitor();
		if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
			return ( ret );
		}
	}
#endif

	return ( OK );
}

/*************************************************************************
	module		:[T30ƒ‚ƒjƒ^ƒwƒbƒ_ˆóü]
	function	:[T30ƒ‚ƒjƒ^‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List					:
		FaxComPerformingFlag	:
		SYS_FaxComResult		:
		SYB_JournalFile			:
		SYS_MemorySwitch		:
		FaxCompatibleErrorCode	:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µi‰üƒy[ƒW‚ ‚èj
		,	2->ƒy[ƒWƒGƒ“ƒhŒ©o‚µi‰üƒy[ƒW‚È‚µj
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_T30Monitor_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

#if (PRO_MULTI_LINE == ENABLE)	/* 1997/09/04 Y.Matsukuma */
	UBYTE	type;
	UBYTE	board;
	UBYTE	data;

	type = 0;								/* 1996/09/20 Y.M */
	data = 0;
#endif

	if ( Category == 0 ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if ( Page == 1 ) {
			/*‚P‰üs{”­MŒ³–¼A”Ô†ˆóü{‚Q‰üs{Œ©o‚µ{‚P‰üs*/
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
			if ( (ret = Print_Head1_Common( PWRD_T30Monitor_K, LST_NOT, 24-1 )) != OK ) {
				return ( ret );
			}
#else
			if ( (ret = Print_Head1_Common( PWRD_T30Monitor, LST_XXX_TWI_XXX, 24-1 )) != OK ) {
				return ( ret );
			}
#endif

#if (PRO_JOURNAL_PRINT_TIME == ENABLE)	/* “ú—§“Á‹–‰ñ”ð(ƒvƒŠƒ“ƒgŽžŠÔ‚ðˆóŽš‚µ‚È‚¢) By M.Tachibana 1998/04/22 */
			/*Œ»ÝŽžŠÔ*/
			if ( (ret = CurrentTimePrint( 60-1 )) != OK ) {
				return ( ret );
			}
#else
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
#endif

#if (PRO_MULTI_LINE == DISABLE)	/* 1997/09/04 Y.Matsukuma */
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/13 */
			if ((CHK_UNI_MultiT30Monitor() && LST_T30ConfNumber != 0xFF)
			 || ((FaxComPerformingFlag != YES)
  #if (PRO_TX_SPEED == V34) /* V34 ‚Ì Phase2 ‚ÅŒðM‚ªƒGƒ‰[I—¹‚µ‚½‚Æ‚«‚Ìˆ—B added by H.Kubo 1999/04/05 */
			  && ((FaxComResult & 0x0cff) != (RECEIVEERROR | 0x008A))
			  && ((FaxComResult & 0x0cff) != (RECEIVEERROR | 0x008B))
  #endif
			  && ((FaxComResult & 0x0cff) != (RECEIVEERROR | 0x0011)))) {
 #else
			if ( (FaxComPerformingFlag != YES)
  #if (PRO_TX_SPEED == V34) /* V34 ‚Ì Phase2 ‚ÅŒðM‚ªƒGƒ‰[I—¹‚µ‚½‚Æ‚«‚Ìˆ—B added by H.Kubo 1999/04/05 */
			 && ((FaxComResult & 0x0cff) !=	 (RECEIVEERROR | 0x008A))
			 && ((FaxComResult & 0x0cff) !=	 (RECEIVEERROR | 0x008B))
  #endif
			 && ((FaxComResult & 0x0cff) !=	 (RECEIVEERROR | 0x0011)) ) {
 #endif
#else
 #if defined(POPLAR_F)
			if ( (T30PrintFaxComPerforming != YES)
			 && ((T30PrintFaxComResult & 0x0cff) !=	(RECEIVEERROR | 0x0011)) /*’ÊM’†Áª¯¸*/
			 && ((T30PrintFaxComResult & 0x00ff) != (0x008A)) /* *.8.10	  */
			 && ((T30PrintFaxComResult & 0x00ff) != (0x008B)) /* *.8.11   */
			 && ((T30PrintFaxComResult & 0x0C00) != DIALERROR) ) {					 /*ÀÞ²ÔÙ´×°  */
 #else
			if ( (T30PrintFaxComPerforming != YES)
				 /* V34 ‚Ì Phase2 ‚ÅŒðM‚ªƒGƒ‰[I—¹‚µ‚½‚Æ‚«‚Ìˆ—‚ð“ñs’Ç‰ÁB added by H.Kubo 1999/04/05 */
				 && ((T30PrintFaxComResult & 0x0cff) !=	 (RECEIVEERROR | 0x008A))
				 && ((T30PrintFaxComResult & 0x0cff) !=	 (RECEIVEERROR | 0x008B))
			 && ((T30PrintFaxComResult & 0x0cff) !=	 (RECEIVEERROR | 0x0011)) ) {
 #endif
#endif
																/*’ÊM’†Áª¯¸*/
				/*†®†¢†¢†¢†Î†¢†¢†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†Î†¢†¢†¢†Î†¢†¢†Î†¢†¢†²*/
				Print_DelMemoryRcv_Line( 0, LST_RX, List.S.Print, List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}

#if (PRO_MULTI_LINE == DISABLE)	/* 1997/09/04 Y.Matsukuma */
				if ( SYS_OptionT30Monitor.JournalType == SYS_T30_TXJOURNAL ) {
					/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò²†¤Ó°ÄÞ†¤¶²¼¼Þº¸†¤¼Þ¶Ý`†¤¹¯¶†¤ËÞº³†¤*/
					Print_DelMemoryRcv_Line( 1 ,LST_TX, List.S.Print, List.S.Attribute );
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					/*†¾†¢†¢†Þ†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢ ` †¢†Þ†¢†¢†¢†Æ*/
					/*†¤999 †¤xxxxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99" ` XX†¤XXXXXX†¤*/
					if ((ret = Print_T30_Journal_Specifi(LST_TX,
														 (struct SYS_JournalData_t *)SYB_JournalFile,
														 SYS_OptionT30Monitor.Index)) != OK) {
						return ( ret );
					}
				}
				else {
					/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò²†¤Ó°ÄÞ†¤¶²¼¼Þº¸†¤¼Þ¶Ý`†¤¹¯¶†¤ËÞº³†¤*/
					Print_DelMemoryRcv_Line( 1 ,LST_RX, List.S.Print, List.S.Attribute );
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					/*†¾†¢†¢†Þ†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢ ` †¢†Þ†¢†¢†¢†Æ*/
					/*†¤999 †¤xxxxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99" ` XX†¤XXXXXX†¤*/
					if ( (ret = Print_T30_Journal_Specifi( LST_RX,
					  (struct SYS_JournalData_t *)SYB_JournalFile,
					  SYS_OptionT30Monitor.Index )) != OK ) {
						return ( ret );
					}
				}
#else
				if ( LST_T30_JournalType == SYS_T30_TXJOURNAL ) {
					type = LST_TX;
				}
				else {
					type = LST_RX;
				}
				/*†¤ Â³ÊÞÝ†¤±²Ã»·Ò²†¤Ó°ÄÞ†¤¶²¼¼Þº¸†¤¼Þ¶Ý`†¤¹¯¶†¤ËÞº³†¤*/
				Print_DelMemoryRcv_Line( 1 ,type, List.S.Print, List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				/*†¾†¢†¢†Þ†¢†¢†¢†Þ†¢†¢†Þ†¢†¢†¢†¢†Þ†¢†¢†¢ ` †¢†Þ†¢†¢†¢†Æ*/
				/*†¤999 †¤xxxxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99" ` XX†¤XXXXXX†¤*/
				if ((ret = Print_T30_Journal_Specifi(type,
													 (struct SYS_JournalData_t *)SYB_JournalFile,
													 LST_T30_Index)) != OK) {
					return ( ret );
				}
#endif

				/*†¶†¢†¢†Ö†¢†¢†¢†Ö†¢†¢†Ö†¢†¢†¢†¢†Ö†¢†¢†¢†Ö†¢ ` †¢†Ö†¢†¢†¢†º*/
				Print_DelMemoryRcv_Line( 4, LST_RX, List.S.Print,
				  List.S.Attribute );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
#if (PRO_MULTI_LINE == ENABLE)	 /* 1997/09/04 Y.Matsukuma */				
				/*1sˆóŽši‰üsj ROM Ver–¼’Ç‰Á‚Ì‚½‚ß3¨2s‚É‚µ‚½ 94.11.09 Toyoda */
				if ( (ret = CharacterPrint( LST_LINE_FEED +1 )) != OK ) {
					return ( ret );
				}
#else
				/*2sˆóŽši‰üsj ROM Ver–¼’Ç‰Á‚Ì‚½‚ß3¨2s‚É‚µ‚½ 94.11.09 Toyoda */
				if ( (ret = CharacterPrint( LST_LINE_FEED +2 )) != OK ) {
					return ( ret );
				}
#endif
			}
			/* ROM Ver–¼ 94.11.09 Toyoda */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			CMN_StringCopy( &List.S.Print[63-1], ROM_Revision );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
#if (PRO_MULTI_LINE == ENABLE)	 /* 1997/09/04 Y.Matsukuma */
			/* ƒIƒvƒVƒ‡ƒ“‰ñüROM Ver–¼  */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			for (board = 1; board < SYS_OPTION_BOARD_MAX; board++) {
				if (SYB_OptionROM_Revision[board][0] != 0) { /* 1997/03/12 Y.Matsukuma */
					CMN_UnsignedIntToASC( &List.S.Print[data], board, 1, '0' );
					List.S.Print[data+1] = ':';
					CMN_StringCopy( &List.S.Print[data+2], 
									(UBYTE *)&SYB_OptionROM_Revision[board][0] );
					data += 20;
				}
				if (board == 4) {
					/* ƒIƒvƒVƒ‡ƒ“‚P‚©‚ç‚S‚ðˆóŽš */
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
					data = 0;
				}
			}
			/* ƒIƒvƒVƒ‡ƒ“‚T‚©‚ç‚W‚ðˆóŽš */
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
#endif
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
			List.S.Print[80-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*†¤ TX_Frame RX_Frame DATA	 †¤*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = LST_KLINEI;
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_TxFrame, LST_NOT );
			AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], PWRD_RxFrame, LST_NOT );
			AttributeSet( &List.S.Print[27-1], &List.S.Attribute[27-1], PWRD_Datalong, LST_NOT );
#if (PRO_MULTI_LINE == ENABLE)	 /* 1997/09/04 Y.Matsukuma */
	#if (PRO_LINENUMBER == TWICE_LINE)	/* ‹^Ž—‚Q‰ñüŽd—l by T.Soneoka 1998/2/4 */
			List.S.Print[53-1] = '<';
			AttributeSet( &List.S.Print[55-1], &List.S.Attribute[55-1], PWRD_LineNumber, LST_NOT );
			/*Line Number*/
			if (T30PrintLineNumber == 1) {
				AttributeSet( &List.S.Print[67-1], &List.S.Attribute[67-1],&PWRD_LineName[InternalLineNumber][0], LST_NOT );
			}
			else {
				AttributeSet( &List.S.Print[67-1], &List.S.Attribute[67-1],&PWRD_LineName[2][0], LST_NOT );
			}
			List.S.Print[71-1] = '>';
	#else
			/* ‰º‹L < Line Number:X >‚Í•¡”‰ñüÚ‘±Žž‚Ì‚ÝƒvƒŠƒ“ƒg‚·‚é‚æ‚¤‚É‚µ‚Ü‚·B
			** by O.kimoto 1997/02/19
			*/
			if (OPT_CountModems() >= 2) {
				List.S.Print[53-1] = '<';
				AttributeSet( &List.S.Print[55-1], &List.S.Attribute[55-1], PWRD_LineNumber, LST_NOT );
				/*Line Number*/
				CMN_UnsignedIntToASC( &List.S.Print[67-1], T30PrintLineNumber, 1, '0' );
				List.S.Print[69-1] = '>';
			}
	#endif
#endif
			/*ºÝÊßÁ´×°*/
			List.S.Print[76-1] = '[';

#if (PRO_MULTI_LINE == DISABLE)
			CMN_UnsignedIntToASC( &List.S.Print[77-1], FaxCompatibleErrorCode, 2, '0' );
#else
			CMN_UnsignedIntToASC( &List.S.Print[77-1], T30PrintCompatiError, 2, '0' );
#endif
			List.S.Print[79-1] = ']';
			List.S.Print[80-1] = LST_KLINEI;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*†¾†¢†¢†¢†¢†¢†¢†¢†¢†Æ*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = LST_KLINE4;
			CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
			List.S.Print[80-1] = LST_KLINE6;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			/*†®†¢†¢†¢†¢†¢†¢†¢†¢†²*/
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = LST_KLINE7;
			CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
			List.S.Print[80-1] = LST_KLINE9;
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*†¶†¢†¢†¢†¢†¢†¢†¢†¢†º*/
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[1-1] = LST_KLINE1;
		CMN_MemorySet( &List.S.Print[2-1], 78, LST_KLINE_ );
		List.S.Print[80-1] = LST_KLINE3;
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if ( Category == 1 ) {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
				return ( ret );
			}
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[T30ƒ‚ƒjƒ^’ÊMŠÇ—–¾×ˆóü]
	function	:[T30ƒ‚ƒjƒ^’ÊMŠÇ—‚Ì–¾×•”•ª‚ðˆóü‚·‚é]
	common		:[
		List				:
	]
	condition	:[
		‘—ŽóM‹æ•ª
		,	TXTYPE
		,	LST_RX
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Print_T30_Journal_Specifi(
						 UBYTE TxRx,				/*‘—ŽóM‹æ•ª*/
						 struct SYS_JournalData_t JournalFile[],/*’ÊM‹L˜^ƒf[ƒ^*/
						 UBYTE Point )			/*’ÊM‹L˜^ƒf[ƒ^”Ô†*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

#if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/10 *//* by K.Watanabe 2004/10/12 */
//	UWORD	length;
#endif			/*	End of defined(STOCKHM2)	*/

	/*†¾†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Þ†¢†Æ*/
	Print_DelMemoryRcv_Line( 2, TxRx, List.S.Print, List.S.Attribute );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	/*†¤9999†¤xxxxxx†¤xxxx†¤Z9,Z9:99†¤Z9'99"†¤ZZ9†¤9999†¤XXXX†¤XXXXXX†¤*/
	Print_DelMemoryRcv_Line( 3, TxRx, List.S.Print, List.S.Attribute );
	/*Â³ÊÞÝ*/
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/13 */
 #if defined(POPLAR_F)
	CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)JournalFile[Point].Number, 3, '0' );
 #else
	if (CHK_UNI_MultiT30Monitor()) {
		if (((SYS_T30Monitor + Point)->JournalType != SYS_T30_EMPTY)
		 && ((SYS_T30Monitor + Point)->WritePointer != 0)) {
			CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)Point, 3, '0' );
		}
		else {
			List.S.Print[3-1] = '-';
			List.S.Print[4-1] = '-';
			List.S.Print[5-1] = '-';
		}
	}
	else {
		CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)JournalFile[Point].Number, 3, '0' );
	}
 #endif
#else
	CMN_UnsignedIntToASC( &List.S.Print[3-1], (UWORD)JournalFile[Point].Number, 3, '0' );
#endif

	/*±²Ã»·Ò²*/
#if 0	/* ƒvƒŒƒtƒBƒbƒNƒX{ƒ_ƒCƒ„ƒ‹”Ô†‚Å40Œ…‚ð’´‚¦‚Ä‚àÜ‚è•Ô‚µ‚ÄˆóŽš‚µ‚È‚¢‚Ì‚ÅA‘å“‡‚³‚ñŠm”F‚ÌãAƒŠƒXƒg‚Å‚Ì“WŠJ‚ÍŽ~‚ß‚Ü‚· by K.Watanabe 2004/11/12 */
//#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT: Added by SMuratec K.W.Q 2004/09/09 *//* by K.Watanabe 2004/10/12 */
//	if (JournalFile[Point].RemoteID_TTI[0] == '!'){
//		length = CMN_StringLength(SYB_MercuryDialBuffer);	/* ƒ}ƒLƒ…ƒŠ[“o˜^Œ… */
//
//		List.S.Print[7] = '[';
//		if (length > 18){
//			CMN_StringCopyNumUntilNull( &List.S.Print[8], SYB_MercuryDialBuffer, 19);
//		}
//		else{
//			List.S.Print[8 + length] = ']';
//			
//			CMN_StringCopyNumUntilNull( &List.S.Print[8], SYB_MercuryDialBuffer, length);
//			CMN_StringCopyNumUntilNull( &List.S.Print[9 + length], &JournalFile[Point].RemoteID_TTI[1],
//				(18 - length) );
//		}
//	}
//	else{
//		CMN_StringCopy( &List.S.Print[8-1], JournalFile[Point].RemoteID_TTI );
//	}
#else
	CMN_StringCopy( &List.S.Print[8-1], JournalFile[Point].RemoteID_TTI );
#endif

	/*Ó°ÄÞ*/
	CommunicationModeName( JournalFile[Point].Mode, &List.S.Print[29-1], &List.S.Attribute[29-1] );
	/*¶²¼ ÆÁ¼Þ*/
	CriterionMinuteToDayTimeAsc( JournalFile[Point].StartTime/60, LST_DDHHMM, List.S.Work );
	CMN_StringCopy( &List.S.Print[39-1], List.S.Work );
	/*¼Þ¶Ý*/
	SecondToMinuteSecondAsc( JournalFile[Point].TotalTime, List.S.Work , ' ' );
	CMN_StringCopy( &List.S.Print[48-1], List.S.Work );
	/*Ï²½³*/
	CMN_UnsignedIntToASC( &List.S.Print[55-1], (UWORD)JournalFile[Point].Page, 3, ' ' );
#if ( PRO_DEPARTMENT == ENABLE )	/* •”–å */
	/* •”–åŠÇ—ON‚ÅAƒvƒƒeƒNƒgON‚ÌŽžA•”–åƒR[ƒh‚ðƒ}ƒXƒN‚·‚é‚½‚ß‚Ìif else•¶’Ç‰Á By H.Hirao 1996/08/13 */
	if ( (CHK_DepartmentON() != OFF) && (CHK_SectionCheckProtect() != OFF) ) {
		List.S.Print[59] = '*';
		List.S.Print[60] = '*';
		List.S.Print[61] = '*';
		List.S.Print[62] = '*';
	}
	else {
		if (JournalFile[Point].DepartmentCode != 0xffff) { /* ‰Šú’l‚ª0xffff‚É•ÏX‚Ì‚½‚ß */
			CMN_UnsignedIntToASC( &List.S.Print[60-1], (UWORD)JournalFile[Point].DepartmentCode, 4, '0' );
		}
	}
	/*ECM*/
	if ( (JournalFile[Point].Result & LST_ECM) != 0 ) {
		List.S.Print[65-1] = '*';
	}
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	 /* ‚Q‰ñüF’Ç‰Á 1997/09/04 Y.Matsukuma *//* 1998/10/01 By M.Kuwahara */
	if ( (JournalFile[Point].Result & V34_MODE_SET) != 0 ) {
		List.S.Print[65-1] = '#';
	}
#endif
	/*¹¯¶*/
	CommunicationResultName(JournalFile[Point].Result,
							LST_NAME_SHORT,
							LST_RESULT_COMMON,
							&List.S.Print[66-1],
							&List.S.Attribute[66-1]);
	/*ËÞº³*/
	CommunicationKindName( JournalFile[Point].Kind, LST_NAME_1,&List.S.Print[73-1], &List.S.Attribute[74-1] );
#else
	/*ECM*/
	if ( (JournalFile[Point].Result & LST_ECM) != 0 ) {
		List.S.Print[60-1] = '*';
	}
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)/* ‚Q‰ñüF’Ç‰Á 1997/09/04 Y.Matsukuma */ /* V34 By H.Kubo 1998/10/01  */
	if ( (JournalFile[Point].Result & V34_MODE_SET) != 0 ) {
		List.S.Print[60-1] = '#';
	}
#endif
	/*¹¯¶*/
	CommunicationResultName(JournalFile[Point].Result,
							LST_NAME_SHORT,
							LST_RESULT_COMMON,
							&List.S.Print[61-1],
							&List.S.Attribute[66-1]);
	/*ËÞº³*/
	CommunicationKindName( JournalFile[Point].Kind, LST_NAME_1, &List.S.Print[68-1], &List.S.Attribute[68-1] );
#endif
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}
	return ( OK );
}
/*************************************************************************
	module		:[ƒtƒŒ[ƒ€–¼Žæ“¾]
	function	:[ƒtƒŒ[ƒ€ƒR[ƒh‚É‘Î‚·‚éƒtƒŒ[ƒ€–¼‚ðŽæ“¾‚·‚é]
	common		:[
		List:
	]
	condition	:[
		ƒtƒŒ[ƒ€Ží—Þ
		,	LST_TCF_PIX
		,	LST_FAX_CTRL
	]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				GetFrameName(
						 UBYTE FrameCategory,	/*ƒtƒŒ[ƒ€Ží—Þ*/
						 UBYTE FrameCode,		/*ƒtƒŒ[ƒ€ƒR[ƒh*/
						 UBYTE* FrameName )		/*ƒtƒŒ[ƒ€–¼Ì*/
{
	UBYTE	i;			/*loop*/

	*(FrameName+0) = '?';
	*(FrameName+1) = '?';
	*(FrameName+2) = '?';
	if ( FrameCategory == LST_TCF_PIX ) {
#if ( PRO_PANEL == KANJI ) || ( PRO_JIS_CODE == ENABLE )
		switch ( FrameCode ) {
			case	SYS_T30_TX_TCF:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[0][0], LST_INV_XXX_XXX );
				break;
	#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34) /* 1997/09/04 Y.Matsukuma */ /* 1998/09/17 By M.Kuwahara */
			case	SYS_T30_V34_TX_RATE:
	#endif
			case	SYS_T30_TX_PIX:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[1][0], LST_INV_XXX_XXX );
				break;
			case	SYS_T30_RX_TCF:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[0][0], LST_INV_XXX_XXX );
				break;
	#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)/* 1997/09/04 Y.Matsukuma */ /* 1998/09/17 By M.Kuwahara */
			case	SYS_T30_V34_RX_RATE:
	#endif
			case	SYS_T30_RX_PIX:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[1][0], LST_INV_XXX_XXX );
				break;
	#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)/* 1997/09/04 Y.Matsukuma */ /* 1998/09/17 By M.Kuwahara */
			case	SYS_T30_TX_CJ:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[2][0], LST_NOT );
				break;
			case	SYS_T30_TX_CI:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[3][0], LST_NOT );
				break;
			case	SYS_T30_TX_ANS:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[4][0], LST_NOT );
				break;
			case	SYS_T30_RX_CJ:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[2][0], LST_NOT );
				break;
			case	SYS_T30_RX_CI:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[3][0], LST_NOT );
				break;
			case	SYS_T30_RX_ANS:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[4][0], LST_NOT );
				break;
			case	SYS_T30_RX_CED:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[5][0], LST_NOT );
				break;
	#endif
		}
#else
		switch ( FrameCode ) {
			case	SYS_T30_TX_TCF:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
				  &P_Frm_S_Name[0][0], LST_INV_XXX_XXX ); /**	For ANZU MES -> INV By H.Hirao1996/05/23	*/
				break;
	#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	/* 1997/09/04 Y.Matsukuma */ /* "PRO_TX_SPEED == V34"added by H.Hirao 1999/03/15 */
			case	SYS_T30_V34_TX_RATE:
	#endif
			case	SYS_T30_TX_PIX:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1],
				  &P_Frm_S_Name[1][0], LST_INV_XXX_XXX ); /**	For ANZU MES -> INV By H.Hirao1996/05/23	*/
				break;
			case	SYS_T30_RX_TCF:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1],
				  &P_Frm_S_Name[0][0], LST_INV_XXX_XXX ); /**	For ANZU MES -> INV By H.Hirao1996/05/23	*/
				break;
	#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	/* 1997/09/04 Y.Matsukuma */ /* "PRO_TX_SPEED == V34"added by H.Hirao 1999/03/15 */
			case	SYS_T30_V34_RX_RATE:
	#endif
			case	SYS_T30_RX_PIX:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1],
				  &P_Frm_S_Name[1][0], LST_INV_XXX_XXX ); /**	For ANZU MES -> INV By H.Hirao1996/05/23	*/
				break;
	#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	/* 1997/09/04 Y.Matsukuma */ /* "PRO_TX_SPEED == V34"added by H.Hirao 1999/03/15 */
			case	SYS_T30_TX_CJ:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[2][0], LST_NOT );
				break;
			case	SYS_T30_TX_CI:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[3][0], LST_NOT );
				break;
			case	SYS_T30_TX_ANS:
				AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], &P_Frm_S_Name[4][0], LST_NOT );
				break;
			case	SYS_T30_RX_CJ:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[2][0], LST_NOT );
				break;
			case	SYS_T30_RX_CI:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[3][0], LST_NOT );
				break;
			case	SYS_T30_RX_ANS:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[4][0], LST_NOT );
				break;
			case	SYS_T30_RX_CED:
				AttributeSet( &List.S.Print[14-1], &List.S.Attribute[14-1], &P_Frm_S_Name[5][0], LST_NOT );
				break;
	#endif
		}
#endif
	}
	else {
		for ( i = 0; i < LST_FRAME_N_MAX; i++ ) {
			if ( P_Frm_N_Cd[i] == (UBYTE)(FrameCode & (P_Frm_N_Msk[i] ^ 0xff)) ) {
				CMN_StringCopy( FrameName, &P_Frm_N_Name[i][0] );
			}
		}
	}
}

/*************************************************************************
	module		:[T30ƒf[ƒ^ƒtƒB[ƒ‹ƒh•¶Žš—ñ•ÏŠ·]
	function	:[T30ƒf[ƒ^ƒtƒB[ƒ‹ƒh‚ð16i‚Ì•¶Žš—ñ‚É•ÏŠ·‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				DataFieldSet(
						 UBYTE *Data,			/*T30ƒf[ƒ^*/
						 UBYTE DataSize,			/*T30ƒf[ƒ^”*/
						 register UBYTE* PrnString )/*ˆóü•¶Žš—ñ*/
{
	UBYTE	i;			/*loop*/
	UBYTE	j;			/*data*/
	UBYTE	w;			/*work*/

	for ( i = 0; i < DataSize; i++ ) {
		j = *(Data+i);
		w = (UBYTE)( (j & 0xf0) >> 4 );
		*(PrnString+(i*3)+0) = CMN_DecimalToHex( w );
		w = (UBYTE)( j & 0x0f );
		*(PrnString+(i*3)+1) = CMN_DecimalToHex( w );
	}
}

/*************************************************************************
	module		:[DIS,DTC,DCSÝ’è–¼Ì•ÏŠ·]
	function	:[DIS,DTC,DCS‚ÌÝ’è‚ðA–¼Ì‚Ì•¶Žš—ñ‚É•ÏŠ·‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				SettingName(
						 UBYTE TxRxFlag,			/**ÌÚ°ÑŽí•Ê */ /* ’Ç‰Á(ANZU) By H.Hirao Apr.11,1996 */
						 UBYTE speed_handshakeflag,	/**’ZkÊÝÄÞ¼ª°¸Ì×¸Þ */ /* ’Ç‰Á(ANZU) By H.Hirao Apr.11,1996 */
						 UBYTE Frame,				/*ƒtƒŒ[ƒ€ƒR[ƒh*/
						 UBYTE *Data,			/*T30ƒf[ƒ^*/
						 UBYTE DataSize,			/*T30ƒf[ƒ^”*/
						 register UBYTE* PrnString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE* AttString )/*Cü•¶Žš—ñ*/
{
	UBYTE flag;		/**‰ð‘œ“x‚ðÝ’è‚·‚é‚Æ‚«‚ÌÌ×¸Þ */

	PrnString[ 0] = '[';
	PrnString[18] = ']';
	/*ÃÞ°ÀM†‘¬“x*/
	if ( Xmask(Frame) == DCS_F ) {
		SettingSpeed( Data[1], &PrnString[1], &AttString[1] );
	}
	else {
		switch ( Data[1] & LST_T30_SPEED ) {
			case LST_V27_FB:
			case LST_V27:
				AttributeSet( &PrnString[1], &AttString[1], PWRD_V27, LST_NOT );
				break;
			case LST_V29:
			case LST_V29_PLUS:
				AttributeSet( &PrnString[1], &AttString[1], PWRD_V29, LST_NOT );
				break;
			case LST_V33_PLUS:
				AttributeSet( &PrnString[1], &AttString[1], PWRD_V33, LST_NOT );
				break;
			case LST_V17_PLUS:
				AttributeSet( &PrnString[1], &AttString[1], PWRD_V17, LST_NOT );
				break;
		}
	}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if  ((Data[9] & LST_T30_JBIG)
	&&  (DataSize >= 10)) {
		AttributeSet( &PrnString[5], &AttString[5], PWRD_JBG, LST_NOT );
	}
	else if ( ((Data[3] & LST_T30_CODING ) == LST_T30_CODING )
	 	  &&  (DataSize >= 4)) {	/* ƒf[ƒ^‚ª4ƒoƒCƒgˆÈã‚ ‚éŽž‚Ì‚Ý 1998/05/19 By M.Kuwahara */
		AttributeSet( &PrnString[5], &AttString[5], PWRD_MMR, LST_NOT );
	}
	else if ( (Data[1] & LST_T30_TWO_DMS ) == LST_T30_TWO_DMS ) {
		AttributeSet( &PrnString[5], &AttString[5], PWRD_MR, LST_NOT );
	} else {
		AttributeSet( &PrnString[5], &AttString[5], PWRD_MH, LST_NOT );
	}
#else
	if (((Data[3] & LST_T30_CODING ) == LST_T30_CODING )
	 &&  (DataSize >= 4)) {	/* ƒf[ƒ^‚ª4ƒoƒCƒgˆÈã‚ ‚éŽž‚Ì‚Ý 1998/05/19 By M.Kuwahara */
		AttributeSet( &PrnString[5], &AttString[5], PWRD_MMR, LST_NOT );
	}
	else {
		if ( (Data[1] & LST_T30_TWO_DMS ) == LST_T30_TWO_DMS ) {
			AttributeSet( &PrnString[5], &AttString[5], PWRD_MR, LST_NOT );
		}
		else {
			AttributeSet( &PrnString[5], &AttString[5], PWRD_MH, LST_NOT );
		}
	}
#endif
	/*‹L˜^•”\—Í*/
	PrnString[ 9] = '-';
	PrnString[10] = '-';
	if ( (Data[3] & 0x80) == 0x80 ) {
		if ( (Data[4] & LST_T30_WIDTH ) == LST_T30_WIDTH ) {
			if ( Xmask(Frame) == DCS_F ) {
				switch ( Data[4] & LST_T30_WIDTH1 ) {
					case	LST_RW_A5_1216:
						AttributeSet( &PrnString[9], &AttString[9], PWRD_A5, LST_NOT );
						break;
					case	LST_RW_A6_864:
						AttributeSet( &PrnString[9], &AttString[9], PWRD_A6, LST_NOT );
						break;
				}
			}
			else {
				switch ( Data[4] & LST_T30_WIDTH1 ) {
					case	LST_RW_A5_1216:
					case	LST_RW_A5_1728:
						AttributeSet( &PrnString[9], &AttString[9], PWRD_A5, LST_NOT );
						break;
					case	LST_RW_A6_864:
					case	LST_RW_A6_1728:
						AttributeSet( &PrnString[9], &AttString[9], PWRD_A6, LST_NOT );
						break;
				}
			}
		}
		else {
			switch ( Data[2] & LST_T30_WIDTH2 ) {
				case	LST_RW_A4:
					AttributeSet( &PrnString[9], &AttString[9], PWRD_A4, LST_NOT );
					break;
				case	LST_RW_B4:
					AttributeSet( &PrnString[9], &AttString[9], PWRD_B4, LST_NOT );
					break;
				case	LST_RW_A3:
					AttributeSet( &PrnString[9], &AttString[9], PWRD_A3, LST_NOT );
					break;
			}
		}
	}
	else {
		switch ( Data[2] & LST_T30_WIDTH2 ) {
			case	LST_RW_A4:
				AttributeSet( &PrnString[9], &AttString[9], PWRD_A4, LST_NOT );
				break;
			case	LST_RW_B4:
				AttributeSet( &PrnString[9], &AttString[9], PWRD_B4, LST_NOT );
				break;
			case	LST_RW_A3:
				AttributeSet( &PrnString[9], &AttString[9], PWRD_A3, LST_NOT );
				break;
		}
	}
	/*Å¬‘–¸ŽžŠÔ”\—Í*/
	switch ( Data[2] & LST_T30_TIME ) {
		case	LST_20MS:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait20, LST_NOT );
			break;
		case	LST_40MS:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait40, LST_NOT );
			break;
		case	LST_10MS:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait10, LST_NOT );
			break;
		case	LST_5MS:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait5, LST_NOT );
			break;
		case	LST_10MS_H:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait10, LST_NOT );
			break;
		case	LST_20MS_H:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait20, LST_NOT );
			break;
		case	LST_40MS_H:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait40, LST_NOT );
			break;
		case	LST_0MS:
			AttributeSet( &PrnString[12], &AttString[12], PWRD_Wait0, LST_NOT );
			break;
	}
	/*‰ð‘œ“x*/
	flag = 1; /**Ì×¸Þ‚ð²Æ¼¬×²½Þ */

	if ( (Data[3] & 0x80) != 0x80 ) { /* Šg’£Ì¨°ÙÄÞ‚ÌËÞ¯Ä‚ª0‚ÌŽž‚ÍAFine‚©Normal‚µ‚©‚È‚¢B*/
		if ( (Data[1] & LST_T30_FINE ) == LST_T30_FINE ) {
			AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeFN, LST_NOT );
		}
		else {
			AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeNR, LST_NOT );
		}
	}
	else {	/* Šg’£Ì¨°ÙÄÞ‚ª1‚ÌŽž‚ÍASFineˆÈã‚ª‚ ‚é */
		/* if ( (Data[5] & LST_T30_HFINE ) == LST_T30_HFINE ) {
			AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeHF, LST_NOT );
		} */ /**ˆÇ‚ÌH°FINE‚ª300~400‚Å‚ ‚é‚½‚ß•\Ž¦•û–@‚ª•ÏX By H.Hirao Apr.10,1996 */
		/** ‚±‚ê‚æ‚èˆÈ‰º33s’Ç‰Á For ANZU By H.Hirao Apr.11,1996 */
		if ( TxRxFlag == SYS_T30RX_FRAMEBIT ) {		/**ŽóMÌÚ°Ñ‚Ìê‡ */
			/**NSF, NSS, NSC‚Ì300dpi‚Ì”\—Í‚ðŽ¦‚·ËÞ¯Ä‚ðŽó‚¯‚½ê‡ ŠŽ‚Â •W€ÌÚ°Ñ‚ÌS-FINEËÞ¯Ä‚ª1‚Ìê‡ */
			if ( (SYB_T30_RxFrame300dpiFlag == YES) && ((Data[5] & LST_T30_SFINE ) == LST_T30_SFINE) ) {
				AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeHF, LST_NOT );
				flag = 0;
			}
		} else {		/**‘—MÌÚ°Ñ‚Ìê‡ */
			if ( Xmask(Frame) == DIS_F || Xmask(Frame) == DTC_F ) {		/**ÌÚ°Ñº°ÄÞ‚ªDIS, DTC‚Ìê‡ */
				/**300dpi‚Ì”\—Í‚ðŽ¦‚·ËÞ¯Ä‚ðŽó‚¯‚½ê‡ ŠŽ‚Â •W€ÌÚ°Ñ‚ÌS-FINEËÞ¯Ä‚ª1‚Ìê‡ */
				if ( (SYB_T30_TxFrame300dpiFlag == YES) && ((Data[5] & LST_T30_SFINE ) == LST_T30_SFINE) ) {
					AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeHF, LST_NOT );
					flag = 0;
				}
			} else {		/**ÌÚ°Ñº°ÄÞ‚ªDCS‚Ìê‡ */
				if ( speed_handshakeflag == YES ) {		/**’ZkÊÝÄÞ¼ª°¸‚Ìê‡ */
					/**300dpi‚Ì”\—Í‚ðŽ¦‚·ËÞ¯Ä‚ðŽó‚¯‚½ê‡ ŠŽ‚Â •W€ÌÚ°Ñ‚ÌS-FINEËÞ¯Ä‚ª1‚Ìê‡ */
					if ( (SYB_T30_TxFrame300dpiFlag == YES) && ((Data[5] & LST_T30_SFINE ) == LST_T30_SFINE) ) {
						AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeHF, LST_NOT );
						flag = 0;
					}
				} else {		/**’ZkÊÝÄÞ¼ª°¸‚Å‚È‚¢ê‡ */
					/**300dpi‚Ì”\—Í‚ðŽ¦‚·ËÞ¯Ä‚ðŽó‚¯‚½ê‡ ŠŽ‚Â •W€ÌÚ°Ñ‚ÌS-FINEËÞ¯Ä‚ª1‚Ìê‡ */
					if ((SYB_T30_TxFrame300dpiFlag == YES)
					 && (SYB_T30_RxFrame300dpiFlag == YES)
					 && ((Data[5] & LST_T30_SFINE) == LST_T30_SFINE)) {
						AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeHF, LST_NOT );
						flag = 0;
					}
				}
			}
		}
		if ( flag == 1 ) {
			if ( (Data[5] & LST_T30_HFINE ) == LST_T30_HFINE ) {
				AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeHF, LST_NOT );
			}
			else {
				if ( (Data[5] & LST_T30_SFINE ) == LST_T30_SFINE ) {
					AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeSF, LST_NOT );
				}
				else {
					if ( (Data[1] & LST_T30_FINE ) == LST_T30_FINE ) {
						AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeFN, LST_NOT );
					}
					else {
						AttributeSet( &PrnString[15], &AttString[15], PWRD_ModeNR, LST_NOT );
					}
				}
			}
		}
	}
	/*Œë‚è’ù³•ûŽ®*/
	if ( (Data[3] & LST_T30_PARITY ) == LST_T30_PARITY ) {
		PrnString[17] = 'E';
	}
	else {
		PrnString[17] = '-';
	}
}

/*************************************************************************
	module		:[DCS,TCTƒXƒs[ƒhÝ’è–¼Ì•ÏŠ·]
	function	:[DCS,TCT‚ÌƒXƒs[ƒhÝ’è‚ðA–¼Ì‚Ì•¶Žš—ñ‚É•ÏŠ·‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[‚È‚µ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
void				SettingSpeed(
						 UBYTE Data,				/*T30ƒf[ƒ^*/
						 register UBYTE* PrnString,	/*ˆóü•¶Žš—ñ*/
						 register UBYTE* AttString )/*Cü•¶Žš—ñ*/
{
#if (PRO_MULTI_LINE == ENABLE) || (PRO_TX_SPEED == V34)	/*  1997/09/04 Y.Matsukuma *//* 1998/10/01 By M.Kuwahara */
	if (V34_Communication == TRUE) {
		return;
	}
#endif
	switch ( Data & LST_T30_SPEED ) {
		case LST_14400BPS_V17:
		case LST_14400BPS_V33:
			AttributeSet( PrnString, AttString, PWRD_Rs144, LST_NOT );
			break;
		case LST_12000BPS_V17:
		case LST_12000BPS_V33:
			AttributeSet( PrnString, AttString, PWRD_Rs120, LST_NOT );
			break;
		case LST_9600BPS_V17:
		case LST_9600BPS_V29:
			AttributeSet( PrnString, AttString, PWRD_Rs96, LST_NOT );
			break;
		case LST_7200BPS_V17:
		case LST_7200BPS_V29:
			AttributeSet( PrnString, AttString, PWRD_Rs72, LST_NOT );
			break;
		case LST_4800BPS_V27:
			AttributeSet( PrnString, AttString, PWRD_Rs48, LST_NOT );
			break;
		case LST_2400BPS_V27:
			AttributeSet( PrnString, AttString, PWRD_Rs24, LST_NOT );
			break;
	}
}

/*************************************************************************
	module		:[X bit ƒ}ƒXƒN]
	function	:[X bit ƒ}ƒXƒN]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[x bit ƒ}ƒXƒN ƒtƒŒ[ƒ€ƒR[ƒh]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
UBYTE		Xmask(
						 UBYTE FrameCode )	/*ƒtƒŒ[ƒ€ƒR[ƒh*/
{
	UBYTE	i;			/*loop*/
	UBYTE	ret;		/*frame code x bit mask*/

	ret = FrameCode;
	for ( i = 0; i < LST_FRAME_N_MAX; i++ ) {
		if ( P_Frm_N_Cd[i] == (UBYTE)(FrameCode & (P_Frm_N_Msk[i] ^ 0xff)) ) {
			ret = (UBYTE)(FrameCode & (P_Frm_N_Msk[i] ^ 0xff));
		}
	}
	return ( ret );
}

/*************************************************************************
	module		:[ƒ^ƒXƒNî•ñƒ_ƒ“ƒv]
	function	:[ƒ^ƒXƒNî•ñ‚ðƒ_ƒ“ƒv‚·‚é]
	common		:[
		List				:
		SYS_MemorySwitch	:
		tsk_access			:
		tsk_cntl_blk		:
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Tsk_Dump(
						 void )			/*‚È‚µ*/
{
	UBYTE		i,k;				/*loop, work*/
	register UWORD		j;			/* */
	UBYTE 		*tsk_p;				/*À½¸Îß²ÝÀ°*/
	UBYTE		page;				/*Íß°¼Þ*/
	UBYTE		line_cnt;			/*Žc‚èˆóü‰Â”\s”*/
	register WORD		ret;				/*ŽÀsŒ‹‰Ê*/
	UDWORD		stack_address;		/*½À¯¸±ÄÞÚ½*/
	UWORD		stack_size;			/*½À¯¸»²½Þ*/

	page = 1;
	if ( (ret = Tsk_Dump_Head( 0, page ) ) != OK ) {
		return ( ret );
	}
	line_cnt = (UBYTE)(PaperSizeLen() - 7 );
/*	stack_address = (UDWORD)TaskStackBottom;*/	/* 0x2200	FE00:2200  FE00‚ÍŒÅ’è */
	stack_address = (UDWORD)TASK_STACK_START;	/* 0x2200	FE00:2200  FE00‚ÍŒÅ’è */
/*	for ( i = 0; i < READY_STACK_MAX; i++ ) {	*/
	for ( i = 0; i < TOTAL_STACK_MAX; i++ ) {
#if (0) /* 1997/12/16 Y.Matsukuma */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[ 1-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat >> 4));						/*tsk_stat*/
		List.S.Print[ 2-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat & 0x0f));
		List.S.Print[ 4-1] = CMN_DecimalToHex((UBYTE)(tcb[i].prog_no >> 4));						/*prog_no*/
		List.S.Print[ 5-1] = CMN_DecimalToHex((UBYTE)(tcb[i].prog_no & 0x0f));
		List.S.Print[ 7-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_link >> 4));						/*tsk_link*/
		List.S.Print[ 8-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_link & 0x0f));
		List.S.Print[10-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0xf000) >> 12));			/*stack_addr*/
		List.S.Print[11-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x0f00) >> 8));
		List.S.Print[13-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x00f0) >> 4));
		List.S.Print[14-1] = CMN_DecimalToHex((UBYTE)((UDWORD)tcb[i].stack_addr & 0x000f));
		List.S.Print[16-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat_tpo >> 4));					/*tsk_stat_tpo*/
		List.S.Print[17-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat_tpo & 0x0f));
		List.S.Print[19-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0xf00000) >> 20));	/*wait_param*/
		List.S.Print[20-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x0f0000) >> 16));
		List.S.Print[22-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x00f000) >> 12));
		List.S.Print[23-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x000f00) >> 8));
		List.S.Print[25-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x0000f0) >> 4));	/*run_tid*/
		List.S.Print[26-1] = CMN_DecimalToHex((UBYTE)((UDWORD)tcb[i].wait_param.sndmsg & 0x00000f));
			List.S.Print[27-1] = '[';
		List.S.Print[32-1] = ']';
		List.S.Print[34-1] = '-';
		List.S.Print[35-1] = '-';
			if ( i < SMALL_STACK_MAX ) {
			/* Nov.26,1994 stack_size = 128; *//* 16*16; */
			stack_size = SMALL_STACK;	/* KIRI:128 MOMIJI:256 */
		}
		else {
			stack_size = LARGE_STACK; /* 16*32; */
		}
		stack_address -= stack_size;
		List.S.Print[28-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x00f000) >> 12) );
		List.S.Print[29-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x000f00) >> 8 ) );
		List.S.Print[30-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x0000f0) >> 4 ) );
		List.S.Print[31-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x00000f) ));
#endif
	/* ‚±‚Á‚¿‚É•ÏX 1997/12/16 Y.Matsukuma */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[ 1-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat >> 4));						/*tsk_stat*/
		List.S.Print[ 2-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat & 0x0f));
		List.S.Print[ 4-1] = CMN_DecimalToHex((UBYTE)(tcb[i].prog_no >> 4));						/*prog_no*/
		List.S.Print[ 5-1] = CMN_DecimalToHex((UBYTE)(tcb[i].prog_no & 0x0f));
		List.S.Print[ 7-1] = CMN_DecimalToHex((UBYTE)(tcb[i].priority >> 4));						/*priority*/
		List.S.Print[ 8-1] = CMN_DecimalToHex((UBYTE)(tcb[i].priority & 0x0f));
		List.S.Print[10-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_link >> 4));						/*tsk_link*/
		List.S.Print[11-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_link & 0x0f));
		List.S.Print[13-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat_tpo >> 4));					/*tsk_stat_tpo*/
		List.S.Print[14-1] = CMN_DecimalToHex((UBYTE)(tcb[i].tsk_stat_tpo & 0x0f));
		List.S.Print[16-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0xf0000000) >> 28));	/*wait_param*/
		List.S.Print[17-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x0f000000) >> 24));
		List.S.Print[19-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x00f00000) >> 20));
		List.S.Print[20-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x000f0000) >> 16));
		List.S.Print[22-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x0000f000) >> 12));
		List.S.Print[23-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x00000f00) >> 8));
		List.S.Print[25-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].wait_param.sndmsg & 0x000000f0) >> 4));
		List.S.Print[26-1] = CMN_DecimalToHex((UBYTE)((UDWORD)tcb[i].wait_param.sndmsg & 0x0000000f));
		List.S.Print[28-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0xf0000000) >> 28));			/*stack_addr*/
		List.S.Print[29-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x0f000000) >> 24));
		List.S.Print[31-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x00f00000) >> 20));
		List.S.Print[32-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x000f0000) >> 16));
		List.S.Print[34-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x0000f000) >> 12));
		List.S.Print[35-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x00000f00) >> 8));
		List.S.Print[37-1] = CMN_DecimalToHex((UBYTE)(((UDWORD)tcb[i].stack_addr & 0x000000f0) >> 4));
		List.S.Print[38-1] = CMN_DecimalToHex((UBYTE)((UDWORD)tcb[i].stack_addr & 0x0000000f));
		List.S.Print[40-1] = '[';
		List.S.Print[52-1] = ']';
			if ( i < SMALL_STACK_MAX ) {
			/* Nov.26,1994 stack_size = 128; *//* 16*16; */
			stack_size = SMALL_STACK;	/* KIRI:128 MOMIJI:256 */
		}
		else {
			stack_size = LARGE_STACK; /* 16*32; */
		}
		stack_address -= stack_size;
		List.S.Print[41-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0xf0000000) >> 28) );
		List.S.Print[42-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x0f000000) >> 24) );
		List.S.Print[44-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x00f00000) >> 20) );
		List.S.Print[45-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x000f0000) >> 16) );
		List.S.Print[47-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x0000f000) >> 12) );
		List.S.Print[48-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x00000f00) >> 8 ) );
		List.S.Print[50-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x000000f0) >> 4 ) );
		List.S.Print[51-1] = CMN_DecimalToHex((UBYTE)((stack_address & 0x0000000f) ));

		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line_cnt--;	/* ‚±‚±‚Å‚O‚É‚È‚é‚Æ‰ü•Å‚³‚ê‚È‚¢ By M.Tachibana 1998/04/17 */

		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
/*		if ( tcb[i][0] != 0xc0 ) {	*/
		if ( tcb[i].prog_no != 0xff ) {	/* CO 10 ¥¥¥‚ÌŽž‚Å‚à½À¯¸“à—e‚ð‘‚­ '94.11.15 H.T */
			tsk_p = (UBYTE *)stack_address;
			k = 0;
			for (j = 0; j < stack_size; j++ ){
				List.S.Print[33+k*3+0] = CMN_DecimalToHex((UBYTE)( (*tsk_p) >> 4) );
				List.S.Print[33+k*3+1] = CMN_DecimalToHex((UBYTE)( (*tsk_p) & 0x0f ) );
				k++;
			tsk_p++;
				if ( k > 15 ) {
					if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
						return ( ret );
					}
					line_cnt--;
					if ( line_cnt == 0 &&
					  (i < (TOTAL_STACK_MAX-1) || j < (stack_size-1)) ) {
							/*Íß°¼Þ‚ÌI‚í‚è‚ÅA‚©‚ÂAiÃÞ°À‚ÌI—¹‚Å‚È‚¢‚©*/
							/*‚Ü‚½‚ÍAÀÞÝÌßÃÞ°À‚ÌI‚í‚è‚Å‚È‚¢j*/
						if ( (ret = Tsk_Dump_Head( 1, page ) ) != OK ) {
							return ( ret );
						}
						page++;
						if ( (ret = Tsk_Dump_Head( 0, page ) ) != OK ) {
							return ( ret );
						}
						line_cnt = (UBYTE)(PaperSizeLen() - 5 );
					}
					Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
					k = 0;
				}
			}
		}
		else {	/* C0 FF ¥¥¥‚ÌŽž‚Í‰Šú‰»‚Ìó‘Ô‚È‚Ì‚Å½À¯¸“à—e‚ð‘‚©‚È‚¢ '94.11.15 H.T */
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			line_cnt--;
			if ( line_cnt == 0 && i < (TOTAL_STACK_MAX-1) ) {
					/*Íß°¼Þ‚ÌI‚í‚è‚ÅA‚©‚ÂAÃÞ°À‚ÌI—¹‚Å‚È‚¢*/
				if ( (ret = Tsk_Dump_Head( 1, page ) ) != OK ) {
					return ( ret );
				}
				page++;
				if ( (ret = Tsk_Dump_Head( 0, page ) ) != OK ) {
					return ( ret );
				}
				line_cnt = (UBYTE)(PaperSizeLen() - 5 );
			}
		}
		if (line_cnt != (UBYTE)(PaperSizeLen() - 5) && i < (TOTAL_STACK_MAX-1)) {	/*‰üÍß°¼Þ‚Ì’¼Œã‚Å‚È‚­A‚©‚ÂA*/
																					/*ÃÞ°À‚ÌI—¹‚Å‚È‚¢*/
			line_cnt--;
			if ( line_cnt > 0 ) {	/*ŽŸ‚Å‰üÍß°¼Þ‚³‚ê‚éŽž‚ÍA‰üs‚µ‚È‚¢*/
				/*‚PsˆóŽši‰üsj*/
				if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
					return ( ret );
				}
			}
			/*--------------------------------------------------------------------
			** TCB‚Ì“à—e‚ð1s‘‚¢‚½Œã‚Åƒ‰ƒCƒ“”‚ª‚O‚É‚È‚é‚Æ‰ü•Å‚Ìˆ—‚ª‚È‚¢‚½‚ß
			** ŽŸ‚Ìƒy[ƒW‚ðƒvƒŠƒ“ƒg‚µ‚È‚¢Bƒ‰ƒCƒ“”‚O‚Å‰ü•Å‚Ìˆ—‚ð“ü‚ê‚Ä‚à—Ç‚¢‚ª
			** ƒR[ƒh—Ê‚ª‘½‚­‚È‚é‚½‚ß‚±‚±‚Å×H‚·‚éB
			** By M.Tachibana 1998/04/17
			*/
/*			if ( line_cnt == 0 && i < (TOTAL_STACK_MAX-1) ) {	*/
			if ( (line_cnt <= 1) && (i < (TOTAL_STACK_MAX-1)) ) {
				if ( (ret = Tsk_Dump_Head( 1, page ) ) != OK ) {
					return ( ret );
				}
				page++;
				if ( (ret = Tsk_Dump_Head( 0, page ) ) != OK ) {
					return ( ret );
				}
				line_cnt = (UBYTE)(PaperSizeLen() - 5 );
			}
		}
	}
	if ( (ret = Tsk_Dump_Head( 1, page ) ) != OK ) {
		return ( ret );
	}
	return (OK);
}

/*************************************************************************
	module		:[ƒ^ƒXƒNî•ñƒ_ƒ“ƒvƒwƒbƒ_ˆóü]
	function	:[ƒ^ƒXƒNî•ñƒ_ƒ“ƒv‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
WORD				Tsk_Dump_Head(
						 UBYTE Category,		/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )			/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		/* Page */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[75-1] = 'P';
		List.S.Print[76-1] = '.';
		CMN_UnsignedIntToASC( &List.S.Print[77-1], (UWORD)Page, 3, '0' );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		if ( Page == 1 ) {
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			List.S.Print[1-1] = CMN_DecimalToHex((UBYTE)((real_run_tid & 0xf0) >> 4));
			List.S.Print[2-1] = CMN_DecimalToHex((UBYTE)((real_run_tid & 0x0F)));
			List.S.Print[4-1] = CMN_DecimalToHex((UBYTE)((top_ready_tid & 0xf0) >> 4));
			List.S.Print[5-1] = CMN_DecimalToHex((UBYTE)((top_ready_tid & 0x0F)));
			List.S.Print[7-1] = CMN_DecimalToHex((UBYTE)((wai_tsk_tid & 0xf0) >> 4));
			List.S.Print[8-1] = CMN_DecimalToHex((UBYTE)((wai_tsk_tid & 0x0F)));
			List.S.Print[10-1] = CMN_DecimalToHex((UBYTE)((wai_1shot_tid & 0xf0) >> 4));
			List.S.Print[11-1] = CMN_DecimalToHex((UBYTE)((wai_1shot_tid & 0x0F)));
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[T30ƒf[ƒ^ƒGƒ“ƒhƒ`ƒFƒbƒN]
	function	:[T30‚Ìƒf[ƒ^ƒGƒ“ƒh‚ðƒ`ƒFƒbƒN‚·‚é]
	common		:[
		SYS_OptionT30Monitor:
	]
	condition	:[]
	commment	:[
		94/09/12	ŠÖ”’Ç‰Á
	]
	return		:[
		ŒŸ¸Œ‹‰Ê
		,	OK	ÃÞ°À´ÝÄÞ
		,	NG	ÃÞ°À´ÝÄÞ‚Å‚È‚¢
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/09/12]
	author		:[‘“cŽŸ˜Y]
*************************************************************************/
UBYTE		CheckEndOfFrame(
						 UWORD Point )			/*T30ƒf[ƒ^ˆÊ’u*/
{
	if ( SYS_OptionT30Monitor.Buffer[Point] == SYS_T30_END_OF_FRAME ||
	  (SYS_OptionT30Monitor.Buffer[Point] == SYS_T30_END_TIME &&
	  SYS_OptionT30Monitor.Buffer[Point+3] == SYS_T30_END_OF_FRAME ) ) {
	  	return ( OK );		/*ÃÞ°À´ÝÄÞ*/
	}
	else {
	  	return ( NG );		/*ÃÞ°À´ÝÄÞ‚Å‚È‚¢*/
	}
}

/*************************************************************************
	module		:[ƒƒ‚ƒŠî•ñƒ_ƒ“ƒv]
	function	:[ƒƒ‚ƒŠî•ñ‚ðƒ_ƒ“ƒv‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/10/19]
	author		:[“n•ÓˆêÍ]
*************************************************************************/
WORD			Memory_Dump(void)
{
	UWORD	i;			/* loop */
	UBYTE	line_cnt;	/* Žc‚èˆóü‰Â”\s” */
	UWORD	j;			/* loop */
	WORD	ret;		/* ŽÀsŒ‹‰Ê */

	/* ÒÓØÀÞÝÌß */

	if ( (ret = Memory_Dump_Head( 0 ) ) != OK ) {
		return ( ret );
	}
	line_cnt = (UBYTE)( PaperSizeLen() - 1 );	/* -1‚ð’Ç‰Á 1997/11/07 Y.Matsukuma */

	/*-------------------*/
	/* MEM_TopEmptyBlock */
	/*-------------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( List.S.Print, Disp_TopEmptyBlock );
	List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)((MEM_TopEmptyBlock & 0xf000) >> 12) );
	List.S.Print[32-1] = CMN_DecimalToHex( (UBYTE)((MEM_TopEmptyBlock & 0x0f00) >> 8) );
	List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)((MEM_TopEmptyBlock & 0x00f0) >> 4) );
	List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)(MEM_TopEmptyBlock & 0x000f) );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

	/*----------------------------*/
	/* MEM_TotalStoreBlockCounter */
	/*----------------------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( List.S.Print, Disp_TotalStoreBlockCounter );
	List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)((MEM_TotalStoreBlockCounter & 0xf000) >> 12) );
	List.S.Print[32-1] = CMN_DecimalToHex( (UBYTE)((MEM_TotalStoreBlockCounter & 0x0f00) >> 8) );
	List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)((MEM_TotalStoreBlockCounter & 0x00f0) >> 4) );
	List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)(MEM_TotalStoreBlockCounter & 0x000f) );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

	/*--------------*/
	/* MEM_EndBlock */
	/*--------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( List.S.Print, Disp_EndBlock );
	List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)((MEM_EndBlock & 0xf000) >> 12) );
	List.S.Print[32-1] = CMN_DecimalToHex( (UBYTE)((MEM_EndBlock & 0x0f00) >> 8) );
	List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)((MEM_EndBlock & 0x00f0) >> 4) );
	List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)(MEM_EndBlock & 0x000f) );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

	/*-------------------------------*/
	/* MEM_TotalAvailableStoreBlkCnt */
	/*-------------------------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)((MEM_TotalAvailableStoreBlkCnt & 0xf000) >> 12) );
	List.S.Print[32-1] = CMN_DecimalToHex( (UBYTE)((MEM_TotalAvailableStoreBlkCnt & 0x0f00) >> 8) );
	List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)((MEM_TotalAvailableStoreBlkCnt & 0x00f0) >> 4) );
	List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)(MEM_TotalAvailableStoreBlkCnt & 0x000f) );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

	/*-------------------------*/
	/* MEM_AvailableMaxFATArea */
	/*-------------------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)((MEM_AvailableMaxFATArea & 0xf000) >> 12) );
	List.S.Print[32-1] = CMN_DecimalToHex( (UBYTE)((MEM_AvailableMaxFATArea & 0x0f00) >> 8) );
	List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)((MEM_AvailableMaxFATArea & 0x00f0) >> 4) );
	List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)(MEM_AvailableMaxFATArea & 0x000f) );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

#if ( PRO_MAKER == FX )
	/*-----------------------------*/
	/* MEM_MultiProgramOpenIndexNo */
	/*-----------------------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( List.S.Print, Disp_MultiProgramOpenIndexNo );
	for ( j = 0; j < SYS_JOB_MAX; j++ ) {	/* SYS_JOB_MAX‚ª6‚È‚Ì‚ÅA‚Ps•ª‚µ‚©‘Î‰ž‚µ‚Ä‚¢‚Ü‚¹‚ñ 94.10.26 Toyoda */
		List.S.Print[(31-1)+(j*5)] = CMN_DecimalToHex( (UBYTE)((MEM_MultiProgramOpenIndexNo[j] & 0xf000) >> 12) );
		List.S.Print[(32-1)+(j*5)] = CMN_DecimalToHex( (UBYTE)((MEM_MultiProgramOpenIndexNo[j] & 0x0f00) >> 8) );
		List.S.Print[(33-1)+(j*5)] = CMN_DecimalToHex( (UBYTE)((MEM_MultiProgramOpenIndexNo[j] & 0x00f0) >> 4) );
		List.S.Print[(34-1)+(j*5)] = CMN_DecimalToHex( (UBYTE)(MEM_MultiProgramOpenIndexNo[j] & 0x000f) );
	}
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}
#endif

	/*-----------------*/
	/* ‚PsˆóŽši‰üsj*/
	/*-----------------*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	line_cnt--;

	/*------------------*/
	/* MEM_IndexTable[] */
	/*------------------*/
	for ( i = 0; i < MEM_INDEX_TABLE_MAX; i++ ) {
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		/*if ( MEM_IndexTable[i].Code == 0xff ) {
			break;
		} @MEM_IndexTable‚ð‘S‚ÄˆóŽš‚·‚é‚æ‚¤‚É•ÏX By H.Hirao 1996/08/13 */
		CMN_StringCopy( List.S.Print, Disp_IndexTable );
		CMN_UnsignedIntToASC( &List.S.Print[16-1], (UWORD)i, 3, '0' );
		List.S.Print[23-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].No & 0xf000) >> 12) );
		List.S.Print[24-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].No & 0x0f00) >> 8) );
		List.S.Print[25-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].No & 0x00f0) >> 4) );
		List.S.Print[26-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].No & 0x000f) );
		List.S.Print[28-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].Page & 0xf000) >> 12) );
		List.S.Print[29-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].Page & 0x0f00) >> 8) );
		List.S.Print[30-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].Page & 0x00f0) >> 4) );
		List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Page & 0x000f) );
		List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Item >> 4) );
		List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Item & 0x0f) );
		List.S.Print[36-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].BoxNumber >> 4) );
		List.S.Print[37-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].BoxNumber & 0x0f) );
		List.S.Print[40-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Code >> 4) );
		List.S.Print[41-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Code & 0x0f) );
		List.S.Print[43-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Mode >> 4) );
		List.S.Print[44-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Mode & 0x0f) );
		List.S.Print[46-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Size >> 4) );
		List.S.Print[47-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].Size & 0x0f) );
		List.S.Print[50-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].LineCount & 0xf000) >> 12) );
		List.S.Print[51-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].LineCount & 0x0f00) >> 8) );
		List.S.Print[52-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].LineCount & 0x00f0) >> 4) );
		List.S.Print[53-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].LineCount & 0x000f) );
		List.S.Print[56-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].StartBlockNo & 0xf000) >> 12) );
		List.S.Print[57-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].StartBlockNo & 0x0f00) >> 8) );
		List.S.Print[58-1] = CMN_DecimalToHex( (UBYTE)((MEM_IndexTable[i].StartBlockNo & 0x00f0) >> 4) );
		List.S.Print[59-1] = CMN_DecimalToHex( (UBYTE)(MEM_IndexTable[i].StartBlockNo & 0x000f) );
		if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
			return ( ret );
		}
	}

	/*-----------------*/
	/* ‚PsˆóŽši‰üsj*/
	/*-----------------*/
	if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
		return ( ret );
	}
	line_cnt--;

	/*---------------*/
	/* MEM_FATArea[] */
	/*---------------*/
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( List.S.Print, Disp_FATArea );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	for ( j = 0; j < MEM_FAT_AREA_MAX; j++ ) {
/*			if ( MEM_FATArea[j] == 0x7ffe ) {		*/
/*				break;								*/
/*			}										*/
		if ( (j != 0) && ( (j % 16) == 0 ) ) {
			if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {/* ‚PsˆóŽš */
				return ( ret );
			}
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		}
		List.S.Print[((j%16)*5)+1] = CMN_DecimalToHex( (UBYTE)((MEM_FATArea[j] & 0xf000) >> 12) );
		List.S.Print[((j%16)*5)+2] = CMN_DecimalToHex( (UBYTE)((MEM_FATArea[j] & 0x0f00) >> 8) );
		List.S.Print[((j%16)*5)+3] = CMN_DecimalToHex( (UBYTE)((MEM_FATArea[j] & 0x00f0) >> 4) );
		List.S.Print[((j%16)*5)+4] = CMN_DecimalToHex( (UBYTE)(MEM_FATArea[j] & 0x000f) );
	}
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚PsˆóŽš */
		return ( ret );
	}

	if ( (ret = Memory_Dump_Head( 1 ) ) != OK ) {
		return ( ret );
	}

	return( OK );
}

/*************************************************************************
	module		:[ƒƒ‚ƒŠî•ñƒ_ƒ“ƒvƒwƒbƒ_ˆóü]
	function	:[ƒƒ‚ƒŠî•ñƒ_ƒ“ƒv‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/10/19]
	author		:[“n•ÓˆêÍ]
*************************************************************************/
WORD			Memory_Dump_Head(UBYTE Category)
{
	register WORD	ret;	/* ŽÀsŒ‹‰Ê */

	if ( Category == 0 ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	else {
 		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

/*************************************************************************
	module		:[‚PsˆóŽš]
	function	:[‚Ps•¶‚Ìƒf[ƒ^‚ðˆóü‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[94/10/19]
	author		:[“n•ÓˆêÍ]
*************************************************************************/
WORD			Memory_Dump_1Line(UBYTE *LineCnt)
{
	WORD	ret;	/* ŽÀsŒ‹‰Ê */

	if ( ( ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	(*LineCnt)--;
	if ( *LineCnt == 0 ) {	/* Íß°¼Þ‚ÌI‚í‚è‚ÌŽž */
		if ( (ret = Memory_Dump_Head( 1 ) ) != OK ) {
			return ( ret );
		}
		if ( (ret = Memory_Dump_Head( 0 ) ) != OK ) {
			return ( ret );
		}
		*LineCnt = (UBYTE)( PaperSizeLen() - 1 );	/* -1‚ð’Ç‰Á 1997/11/07 Y.Matsukuma */
	}

	return( OK );
}

/*************************************************************************
	module		:[‚c‚o‚q‚`‚l’ÊM—š—ðˆóü]
	functiom	:[‚c‚o‚q‚`‚l’ÊM—š—ð‚ðˆóü‚·‚é]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/12]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD			Dpram_Dump(
						 void )				/*‚È‚µ*/
{
	UBYTE	page;					/*Íß°¼Þ*/
	UBYTE	tx_point;				/*‘—MÃÞ°À”Ô†*/
	UBYTE	rx_point;				/*ŽóMÃÞ°À”Ô†*/
	UBYTE	bk_cnt;					/*Ù°Ìß*/
	UBYTE	line_cnt;				/*s”*/
	register WORD	ret;			/*ŽÀsŒ‹‰Ê*/

	page = 1;
	tx_point = (UBYTE)DPR_SamplingTxPointer;	/* add (UBYTE) 1997/06/24 Y.Matsukuma */
	rx_point = (UBYTE)DPR_SamplingRxPointer;	/* add (UBYTE) 1997/06/24 Y.Matsukuma */
	bk_cnt = 0;
	while ( bk_cnt != DPR_MAX_SAMPLING ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		if( page == 1 ){
			line_cnt = (UBYTE)(PaperSizeLen() - 4);		/*ˆóü‰Â”\s”¾¯Ä*/
		}
		else{
			line_cnt = (UBYTE)(PaperSizeLen() - 1);		/*ˆóü‰Â”\s”¾¯Ä*/
		}
		if ( (ret = Dpram_Dump_Head( 0, page ) ) != OK ) {/*Í¯ÀÞˆóü*/
			return ( ret );
		}
		while( line_cnt > 1 ){
/*		for ( ; line_cnt >= 1; line_cnt-- ) {*/
			if ( bk_cnt == DPR_MAX_SAMPLING ) {
				break;
			}
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			/** ƒŠƒZƒbƒgŒã‚Ì‰ß‹Ž‚P‚O’ÊM‚Ì—š—ð‚ðŽc‚·i‘—Mj */
			List.S.Print[1-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxResetBuffer[bk_cnt] & 0xf000) >> 12) );
			List.S.Print[2-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxResetBuffer[bk_cnt] & 0x0f00) >> 8) );
			List.S.Print[3-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxResetBuffer[bk_cnt] & 0x00f0) >> 4) );
			List.S.Print[4-1] = CMN_DecimalToHex( (UBYTE)( DPR_SamplingTxResetBuffer[bk_cnt] & 0x000f) );
			/** ƒŠƒZƒbƒgŒã‚Ì‰ß‹Ž‚P‚O’ÊM‚Ì—š—ð‚ðŽc‚·iŽóMj */
			List.S.Print[11-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxResetBuffer[bk_cnt] & 0xf000) >> 12) );
			List.S.Print[12-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxResetBuffer[bk_cnt] & 0x0f00) >> 8) );
			List.S.Print[13-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxResetBuffer[bk_cnt] & 0x00f0) >> 4) );
			List.S.Print[14-1] = CMN_DecimalToHex( (UBYTE)( DPR_SamplingRxResetBuffer[bk_cnt] & 0x000f) );
			/** ƒŠƒZƒbƒgŒã‚Ì‰ß‹Ž‚P‚O’ÊM‚Ì—š—ð‚ðŽc‚·i‘—Mj */
			List.S.Print[21-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxSaveBuffer[bk_cnt] & 0xf000) >> 12) );
			List.S.Print[22-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxSaveBuffer[bk_cnt] & 0x0f00) >> 8) );
			List.S.Print[23-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxSaveBuffer[bk_cnt] & 0x00f0) >> 4) );
			List.S.Print[24-1] = CMN_DecimalToHex( (UBYTE)( DPR_SamplingTxSaveBuffer[bk_cnt] & 0x000f) );
			/** ƒŠƒZƒbƒgŒã‚Ì‰ß‹Ž‚P‚O’ÊM‚Ì—š—ð‚ðŽc‚·iŽóMj */
			List.S.Print[31-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxSaveBuffer[bk_cnt] & 0xf000) >> 12) );
			List.S.Print[32-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxSaveBuffer[bk_cnt] & 0x0f00) >> 8) );
			List.S.Print[33-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxSaveBuffer[bk_cnt] & 0x00f0) >> 4) );
			List.S.Print[34-1] = CMN_DecimalToHex( (UBYTE)( DPR_SamplingRxSaveBuffer[bk_cnt] & 0x000f) );
			/** ‰ß‹Ž‚P‚O’ÊM‚Ì—š—ð‚ð‹L˜^‚·‚éƒoƒbƒtƒ@i‘—Mj */
			List.S.Print[41-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxBuffer[tx_point] & 0xf000) >> 12) );
			List.S.Print[42-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxBuffer[tx_point] & 0x0f00) >> 8) );
			List.S.Print[43-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingTxBuffer[tx_point] & 0x00f0) >> 4) );
			List.S.Print[44-1] = CMN_DecimalToHex( (UBYTE)( DPR_SamplingTxBuffer[tx_point] & 0x000f) );
			/** ‰ß‹Ž‚P‚O’ÊM‚Ì—š—ð‚ð‹L˜^‚·‚éƒoƒbƒtƒ@iŽóMj */
			List.S.Print[51-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxBuffer[rx_point] & 0xf000) >> 12) );
			List.S.Print[52-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxBuffer[rx_point] & 0x0f00) >> 8) );
			List.S.Print[53-1] = CMN_DecimalToHex( (UBYTE)((DPR_SamplingRxBuffer[rx_point] & 0x00f0) >> 4) );
			List.S.Print[54-1] = CMN_DecimalToHex( (UBYTE)( DPR_SamplingRxBuffer[rx_point] & 0x000f) );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			tx_point++;
			if( tx_point >= DPR_MAX_SAMPLING ){
				tx_point	= 0;
			}
			rx_point++;
			if( rx_point >= DPR_MAX_SAMPLING ){
				rx_point	= 0;
			}
			bk_cnt++;
			line_cnt--;
		}
		if ( (ret = Dpram_Dump_Head( 1, page) ) != OK ) {	/*Ì¯Àˆóü*/
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
		page++;
	}
	return ( OK );
}

/*************************************************************************
	module		:[‚c‚o‚q‚`‚l’ÊM—š—ðƒwƒbƒ_ˆóü]
	functiom	:[‚c‚o‚q‚`‚l’ÊM—š—ð‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List	:
	]
	condition	:[
		Í¯ÀÞŽí—Þ
			0->Íß°¼Þæ“ªŒ©o‚µ
			1->Íß°¼Þ´ÝÄÞŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/12]
	author		:[ŒKŒ´”ü‹I]
*************************************************************************/
WORD			Dpram_Dump_Head(
						 UBYTE Category,	/*ƒwƒbƒ_Ží—Þ*/
						 UBYTE Page )		/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( Page == 1 ) {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
			/* MAN     ƒAƒhƒŒƒX */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_Main, LST_NOT );

			List.S.Print[10-1] = CMN_DecimalToHex((UBYTE)(( SYB_MaintenanceSwitch[MNT_SW_A1] & 0xf0) >> 4));
			List.S.Print[11-1] = CMN_DecimalToHex((UBYTE)( SYB_MaintenanceSwitch[MNT_SW_A1] & 0x0f));
			List.S.Print[12-1] = CMN_DecimalToHex((UBYTE)(( SYB_MaintenanceSwitch[MNT_SW_A2] & 0xf0) >> 4));
			List.S.Print[13-1] = CMN_DecimalToHex((UBYTE)( SYB_MaintenanceSwitch[MNT_SW_A2] & 0x0f));
			List.S.Print[15-1] = CMN_DecimalToHex((UBYTE)(( SYB_MaintenanceSwitch[MNT_SW_A3] & 0xf0) >> 4));
			List.S.Print[16-1] = CMN_DecimalToHex((UBYTE)( SYB_MaintenanceSwitch[MNT_SW_A3] & 0x0f));
			List.S.Print[17-1] = CMN_DecimalToHex((UBYTE)(( SYB_MaintenanceSwitch[MNT_SW_A4] & 0xf0) >> 4));
			List.S.Print[18-1] = CMN_DecimalToHex((UBYTE)( SYB_MaintenanceSwitch[MNT_SW_A4] & 0x0f));
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/* Res		Err		Now */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], PWRD_Reset, LST_NOT );
			AttributeSet( &List.S.Print[22-1], &List.S.Attribute[22-1], PWRD_Error, LST_NOT );
			AttributeSet( &List.S.Print[42-1], &List.S.Attribute[42-1], PWRD_Now, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
			/* Tx	Rx	Tx	Rx	Tx	Rx */
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			AttributeSet( &List.S.Print[2-1], &List.S.Attribute[2-1], 	PWRD_DpramTx, LST_NOT );
			AttributeSet( &List.S.Print[12-1], &List.S.Attribute[12-1], PWRD_DpramRx, LST_NOT );
			AttributeSet( &List.S.Print[22-1], &List.S.Attribute[22-1], PWRD_DpramTx, LST_NOT );
			AttributeSet( &List.S.Print[32-1], &List.S.Attribute[32-1], PWRD_DpramRx, LST_NOT );
			AttributeSet( &List.S.Print[42-1], &List.S.Attribute[42-1], PWRD_DpramTx, LST_NOT );
			AttributeSet( &List.S.Print[52-1], &List.S.Attribute[52-1], PWRD_DpramRx, LST_NOT );
			if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else {
			/*‚PsˆóŽši‰üsj*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
		}
	}
	else {
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	return( OK );
}

/*************************************************************************
	module		:[‘Sƒƒ‚ƒŠƒ_ƒ“ƒv]
	function	:[ƒƒ‚ƒŠ‚ðƒ_ƒ“ƒv‚·‚é]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/03/05]
	author		:[‘]ª‰ª‘ñ]
*************************************************************************/
WORD MemoryDumpList(void)
{
	UBYTE			i;
	register UWORD	j;
	UBYTE			page;				/*Íß°¼Þ*/
	UBYTE			line_cnt;			/*Žc‚èˆóü‰Â”\s”*/
	register WORD	ret;				/*ŽÀsŒ‹‰Ê*/
	UBYTE			data[9];
	UDWORD			add_p;
	UBYTE			*dat;

	page = 1;
	if ( (ret = MemoryDumpListHead( 0, page ) ) != OK ) {
		return ( ret );
	}
	line_cnt = (UBYTE)(PaperSizeLen() - 2);

	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

	add_p = (UDWORD)OPR_MemoryDumpAddress;
	for (j = 0; j < (UWORD)(OPR_MemoryDumpLength / 16); j++ ) {
		dat = (UBYTE *)add_p;
		CMN_UnsignedLongToHexASC_NULL(data, (UDWORD)dat, 8, '0');
		List.S.Print[1] = '[';
		CMN_StringCopy(&List.S.Print[3], data);
		List.S.Print[12] = ']';
		for (i = 0; i < 16 ;i++) {
			dat = (UBYTE *)add_p;
			List.S.Print[15 + i * 3 + 0] = CMN_DecimalToHex((UBYTE)( (*dat) >> 4) );
			List.S.Print[15 + i * 3 + 1] = CMN_DecimalToHex((UBYTE)( (*dat) & 0x0f ) );
			add_p++;
		}
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
		line_cnt--;
		if (line_cnt == 0) {
			if ( (ret = MemoryDumpListHead( 1, page ) ) != OK ) {
				return ( ret );
			}
			page++;
			if ( (ret = MemoryDumpListHead( 0, page ) ) != OK ) {
				return ( ret );
			}
			line_cnt = (UBYTE)(PaperSizeLen() - 5 );
		}
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	}
	if ( (ret = MemoryDumpListHead( 1, page ) ) != OK ) {
		return ( ret );
	}
	return (OK);
}

/*************************************************************************
	module		:[‘Sƒƒ‚ƒŠƒ_ƒ“ƒvƒwƒbƒ_ˆóü]
	function	:[‘Sƒƒ‚ƒŠƒ_ƒ“ƒv‚Ìƒwƒbƒ_‚ðˆóü‚·‚é]
	common		:[
		List:
	]
	condition	:[
		ƒwƒbƒ_Ží—Þ
		,	0->ƒy[ƒWæ“ªŒ©o‚µ
		,	1->ƒy[ƒWƒGƒ“ƒhŒ©o‚µ
	]
	commment	:[]
	return		:[ˆóüŒ‹‰Ê]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[]
	author		:[]
*************************************************************************/
WORD MemoryDumpListHead(UBYTE Category,		/*ƒwƒbƒ_Ží—Þ*/
						UBYTE Page)			/*ƒy[ƒW*/
{
	register WORD	ret;					/*ŽÀsŒ‹‰Ê*/

	if ( Category == 0 ) {
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		/* Page */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		List.S.Print[75-1] = 'P';
		List.S.Print[76-1] = '.';
		CMN_UnsignedIntToASC( &List.S.Print[77 - 1], (UWORD)Page, 3, '0' );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}
	}
	else {
		/*‚PsˆóŽši‰üsj*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
	return ( OK );
}

#if (PRO_MULTI_LINE == ENABLE)	|| (PRO_TX_SPEED == V34) /* 1997/09/04 Y.Matsukuma */ /* V34 condition is added by H.Kubo 1998/07/23 */
/*************************************************************************
	module		:[‚u‚R‚Sƒf[ƒ^ƒŒ[ƒg]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/04]
	author		:[¼ŒG]
*************************************************************************/
void	P_V34DataRate(UBYTE *data)
{
	List.S.Print[69-1] = '[';
	List.S.Print[78-1] = ']';

	switch (*data) {
	case 0:
		AttributeSet( &List.S.Print[70-1], &List.S.Attribute[70-1], &P_Sym_Rate[0][0], LST_NOT );
		break;
	case 2:
		AttributeSet( &List.S.Print[70-1], &List.S.Attribute[70-1], &P_Sym_Rate[1][0], LST_NOT );
		break;
	case 3:
		AttributeSet( &List.S.Print[70-1], &List.S.Attribute[70-1], &P_Sym_Rate[2][0], LST_NOT );
		break;
	case 4:
		AttributeSet( &List.S.Print[70-1], &List.S.Attribute[70-1], &P_Sym_Rate[3][0], LST_NOT );
		break;
	case 5:
		AttributeSet( &List.S.Print[70-1], &List.S.Attribute[70-1], &P_Sym_Rate[4][0], LST_NOT );
		break;
	default:
		AttributeSet( &List.S.Print[70-1], &List.S.Attribute[70-1], &P_Sym_Rate[5][0], LST_NOT );
		break;
	}

	switch (*(data+1)) {
	case 0xCE:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[7][0], LST_NOT );
		break;
	case 0xCD:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[6][0], LST_NOT );
		break;
	case 0xCC:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[5][0], LST_NOT );
		break;
	case 0xCB:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[4][0], LST_NOT );
		break;
	case 0xCA:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[3][0], LST_NOT );
		break;
	case 0xC9:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[2][0], LST_NOT );
		break;
	case 0xC8:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[1][0], LST_NOT );
		break;
	case 0xC7:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[0][0], LST_NOT );
		break;
	case 0xC6:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], PWRD_Rs144, LST_NOT );
		break;
	case 0xC5:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], PWRD_Rs120, LST_NOT );
		break;
	case 0xC4:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], PWRD_Rs96, LST_NOT );
		break;
	case 0xC3:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], PWRD_Rs72, LST_NOT );
		break;
	case 0xC2:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], PWRD_Rs48, LST_NOT );
		break;
	case 0xC1:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], PWRD_Rs24, LST_NOT );
		break;
	default:
		AttributeSet( &List.S.Print[75-1], &List.S.Attribute[75-1], &P_Data_Rate[8][0], LST_NOT );
		break;
	}
}


/*************************************************************************
	module		:[‚uD‚R‚SŒðM‚©‚Ç‚¤‚©‚ð’²‚×‚éŠÖ”]
	function	:[
		1.
	]
	return		:[
		1 : V.34 Coummunication
		0 : under V.34 Communication
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	ProtoType	:[UBYTE LST_CheckV34Communication(void){}]
	date		:[1997/02/24]
	author		:[–ØŒ³C]
*************************************************************************/
UBYTE	 LST_CheckV34Communication()
{
	if ( (SYB_JournalFile[LST_T30_Index].Result & V34_MODE_SET) != 0 ) {
		return(1);
	}
	else {
		return(0);
	}
}

#endif	/* End of (PRO_MULTI_LINE == ENABLE) */



