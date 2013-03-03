/* Original File : jun\usr2:\src\kiri_p\src\lst_r288.c */
/*@^s**************************************************************************
**@^1	lst_t30.c
**@^2	T30ÓÆÀ
**@^3	JCS (j.m)
**@^e*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\apl_msg.h"

#include	"\src\atlanta\ext_v\lst_tbl.h"
#include	"\src\atlanta\ext_v\mlt_data.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#if defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
 #if (PRO_MODEM == R288F)
	#if defined(HINOKI3)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
	#endif
 #endif
#endif
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#endif

#if defined(SATSUKI2) || defined(STOCKHM2)  /* Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#endif

#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ƒ[ƒ‹† *//* Add by O.Kimoto 1998/11/28 */
#include	"\src\atlanta\define\mntsw_h.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#endif

#if (PRO_MULTI_LINE == ENABLE) || (PRO_MODEM == R288F) /* PRO_MODEM is added by H.Kubo 1998/01/06 */

/*************************************************************************
	module		:[‚q‚Q‚W‚W‚eƒ‚ƒfƒ€“à•”ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒvƒŠƒ“ƒg]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	ProtoType	:[int near Print_R288FInternalMonitor(void){}]
	date		:[1996/05/23]
	author		:[–ØŒ³C]
*************************************************************************/
WORD	Print_R288FInternalMonitor(
						 void )			/*‚È‚µ*/
{
	UWORD	i;			/* loop */
	UBYTE	line_cnt;	/* c‚èˆóü‰Â”\s” */
	UBYTE	line_cnt_bkup;	/* c‚èˆóü‰Â”\s”‚Ì‰Šú’l */
	WORD	ret;		/* ÀsŒ‹‰Ê */
	UDWORD	sec_int_time;
	UWORD	msec_int_time;

#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ƒ[ƒ‹† *//* Add by O.Kimoto 1998/11/28 */
	UBYTE	list_cut_request;	/* Add by O.Kimoto 1998/11/28 */
#endif

	struct	ModemInternalStatusTable_def *inter_stat_tbl;	/** ƒ‚ƒfƒ€“à•”‘JˆÚƒXƒe[ƒ^ƒX **/
	inter_stat_tbl = &R288F_InternalStatus[0];	/** ƒ‚ƒfƒ€“à•”‘JˆÚƒXƒe[ƒ^ƒX **/

#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ƒ[ƒ‹† *//* Add by O.Kimoto 1998/11/28 */

#if (0)
** 	/* ‚l‚m‚s‚r‚v‚Ì‚ğ•W€‚ÅƒvƒŠƒ“ƒg‚·‚éƒŠƒXƒgŒn‚ÆƒT[ƒrƒXŒn‚É•ª—£‚µ‚Ü‚µ‚½B by O.Kimoto 1999/01/29 */
** 	if ((SYB_MaintenanceSwitch[MNT_SW_H1] & LIST_PRINT_NO_CUT) == LIST_PRINT_NO_CUT) {
** 		list_cut_request = 0;
** 	}
** 	else {
** 		list_cut_request = 1;
** 	}
#else
	if ((SYB_MaintenanceSwitch[MNT_SW_H1] & SERVICE_REPORT_PRINT_NO_CUT) == SERVICE_REPORT_PRINT_NO_CUT) {
		list_cut_request = 0;
	}
	else {
		list_cut_request = 1;
	}
#endif

#endif

	/* R288F Modem Internal Status Monitor Print */
	if (CHK_PrintR288FMonitorEnable()) {
		if ( (ret = Memory_Dump_Head( 0 ) ) != OK ) {
			return ( ret );
		}
		line_cnt_bkup = (UBYTE)(PaperSizeLen());	/* c‚èˆóü‰Â”\s”‚Ì‰Šú’l */
		line_cnt = (UBYTE)(line_cnt_bkup - 4 );

		/** ƒXƒe[ƒ^ƒXƒ‚ƒjƒ^[ƒwƒbƒhˆóš */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		CMN_StringCopy( List.S.Print, MonitorHead );

#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ƒ[ƒ‹† *//* Add by O.Kimoto 1998/11/28 */
		if (list_cut_request == 0) {
			if ( ( ret = CharacterPrint( LST_PRINT )) != OK ) {
				return ( ret );
			}
		}
		else {
			if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚Psˆóš */
				return ( ret );
			}
		}
#else
		if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚Psˆóš */
			return ( ret );
		}

#endif

		/** ‰¡Œrüˆóš */
		CMN_MemorySet( (UBYTE *)&List.S.Print[1-1], 80, LST_KLINE_ );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		for ( i = 0; i < MODEM_STATUS_TABLE_MAX; i++ ) {
			Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
			if ( inter_stat_tbl->Timer == (UDWORD)0xffffffff ) {
				break;
			}

			/** ‚r‚d‚b‚s‚w‚a */
			if (inter_stat_tbl->Tx_Phase == 0xFF) {
				List.S.Print[1-1] = '_';
				List.S.Print[2-1] = '_';
			}
			else {
				List.S.Print[1-1] = CMN_DecimalToHex((UBYTE)((inter_stat_tbl->Tx_Phase & 0xf0) >> 4));
				List.S.Print[2-1] = CMN_DecimalToHex((UBYTE)( inter_stat_tbl->Tx_Phase & 0x0f));
			}

			/** ‚r‚d‚b‚q‚w‚a */
			if (inter_stat_tbl->Rx_Phase == 0xFF) {
				List.S.Print[5-1] = '_';
				List.S.Print[6-1] = '_';
			}
			else {
				List.S.Print[5-1] = CMN_DecimalToHex((UBYTE)((inter_stat_tbl->Rx_Phase & 0xf0) >> 4));
				List.S.Print[6-1] = CMN_DecimalToHex((UBYTE)( inter_stat_tbl->Rx_Phase & 0x0f));
			}

			/** ‚c‚s‚q */
			if (inter_stat_tbl->DTR_Status == 0x03) {
				List.S.Print[10-1] = '_';
			}
			else {
				List.S.Print[10-1] = (UBYTE)((inter_stat_tbl->DTR_Status & 0x03) ? '1' : '0');
			}

			/** ‚q‚s‚r */
			if (inter_stat_tbl->RTS_Status == 0x03) {
				List.S.Print[14-1] = '_';
			}
			else {
				List.S.Print[14-1] = (UBYTE)((inter_stat_tbl->RTS_Status & 0x03) ? '1' : '0');
			}

			/** ‚b‚s‚r */
			if (inter_stat_tbl->CTS_Status == 0x03) {
				List.S.Print[18-1] = '_';
			}
			else {
				List.S.Print[18-1] = (UBYTE)((inter_stat_tbl->CTS_Status & 0x03) ? '1' : '0');
			}

			/** ‚o‚m‚c‚d‚s */
			if (inter_stat_tbl->PNDET_Status == 0x03) {
				List.S.Print[22-1] = '_';
			}
			else {
				List.S.Print[22-1] = (UBYTE)((inter_stat_tbl->PNDET_Status & 0x03) ? '1' : '0');
			}

			/** ‚o‚m‚r‚t‚b */
			if (inter_stat_tbl->PNSUC_Status == 0x03) {
				List.S.Print[26-1] = '_';
			}
			else {
				List.S.Print[26-1] = (UBYTE)((inter_stat_tbl->PNSUC_Status & 0x03) ? '1' : '0');
			}

			/** ‚e‚d‚c */
			if (inter_stat_tbl->FED_Status == 0x03) {
				List.S.Print[30-1] = '_';
			}
			else {
				List.S.Print[30-1] = (UBYTE)((inter_stat_tbl->FED_Status & 0x03) ? '1' : '0');
			}

			/** ‚q‚k‚r‚c */
			if (inter_stat_tbl->RLSD_Status == 0x03) {
				List.S.Print[34-1] = '_';
			}
			else {
				List.S.Print[34-1] = (UBYTE)((inter_stat_tbl->RLSD_Status & 0x03) ? '1' : '0');
			}

			/** ‚c‚l‚x‚S */
			if (inter_stat_tbl->DMY4_Status == 0x03) {
				List.S.Print[38-1] = '_';
			}
			else {
				List.S.Print[38-1] = (UBYTE)((inter_stat_tbl->DMY4_Status & 0x03) ? '1' : '0');
			}

			/** T30 Status **/
#if defined(HINOKI)	|| defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2) /* For Debug by O.Kimoto 1998/12/01 */ /* HINOKI2 2001/11/13 T.Takagi */
			if ((inter_stat_tbl->T30Status == 0xFF) || (inter_stat_tbl->T30Status == 0x00)) {
				CMN_StringCopy( (UBYTE *)&List.S.Print[42-1], (UBYTE *)T30Message[MODE_NULL] );
			}
			else {
				CMN_StringCopy( (UBYTE *)&List.S.Print[42-1], 
					(UBYTE *)T30Message[(inter_stat_tbl->T30Status & 0x0F)-1] );
			}
#else
			if ((inter_stat_tbl->T30Status == 0xFF) || (inter_stat_tbl->T30Status == 0x00)) {
				CMN_StringCopy( (UBYTE *)&List.S.Print[42-1], (UBYTE *)T30Message[11] );
			}
			else {
				CMN_StringCopy( (UBYTE *)&List.S.Print[42-1], 
					(UBYTE *)T30Message[(inter_stat_tbl->T30Status & 0x0F)-1] );
			}
#endif

			/** Abort Code **/
			if ((inter_stat_tbl->AbortCode == 0xFF) || (inter_stat_tbl->AbortCode == 0x00)) {
				List.S.Print[50-1] = '_';
				List.S.Print[51-1] = '_';
			}
			else {
				List.S.Print[50-1] = CMN_DecimalToHex((UBYTE)((inter_stat_tbl->AbortCode & 0xf0) >> 4));
				List.S.Print[51-1] = CMN_DecimalToHex((UBYTE)( inter_stat_tbl->AbortCode & 0x0f));
			}

			/** ƒXƒe[ƒ^ƒX•Ï‰»ŠÔŠui~‚P‚O‚‚“j */
			sec_int_time = (UDWORD)(inter_stat_tbl->Timer / 100);
			msec_int_time = (UWORD)(inter_stat_tbl->Timer % 100);

			CMN_LongTimeToBCD( (TIME_DATA_t *)&ListTime.Year, sec_int_time );

			/** ƒ~ƒŠ•b */
			List.S.Print[60-1] = '"';
			CMN_UnsignedIntToASC( (UBYTE *)(&List.S.Print[61-1]), (UWORD)msec_int_time,2, '0' );
			List.S.Print[63-1] = '0';

			/** •b */
			List.S.Print[57-1] = '\'';
			List.S.Print[58-1] = CMN_DecimalToHex((UBYTE)((ListTime.Second & 0xf0) >> 4));
			List.S.Print[59-1] = CMN_DecimalToHex((UBYTE)( ListTime.Second & 0x0f));

			/** •ª */
			List.S.Print[54-1] = ' ';
			List.S.Print[55-1] = CMN_DecimalToHex((UBYTE)((ListTime.Minute & 0xf0) >> 4));
			List.S.Print[56-1] = CMN_DecimalToHex((UBYTE)( ListTime.Minute & 0x0f));

#if (PRO_PAPER_TYPE == ROLL_PAPER)	/* ƒ[ƒ‹† *//* Add by O.Kimoto 1998/11/28 */
			if (list_cut_request == 0) {
				if ( ( ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
			}
			else {
				if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚Psˆóš */
					return ( ret );
				}
			}
#else
			if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* ‚Psˆóš */
				return ( ret );
			}
#endif

			if (line_cnt == line_cnt_bkup) {
				line_cnt -= 2;
			}
			
			inter_stat_tbl++;
		}

		if ( (ret = Memory_Dump_Head( 1 ) ) != OK ) {
			return ( ret );
		}
	}
	else {
		return ( MSG_PRN_LST_NO_LIST );
	}

	return( OK );
}

#endif
