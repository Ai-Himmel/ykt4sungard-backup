/* Original File : jun\usr2:\src\kiri_p\src\lst_r288.c */
/*@^s**************************************************************************
**@^1	lst_t30.c
**@^2	T30ﾓﾆﾀ
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

#if (PRO_SGP_TEST_ROM == ENABLE) /* by S.Wang 98/07/24 */

/*************************************************************************
	module		:[シンガポール市場調査レポートプリント]
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
	ProtoType	:[int  Print_Sgp_Report_list(void){}]
	date		:[1998/07/24]
	author		:[王 慎]
	
	0         1         2         3         4         5         6         7        8
    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	 No.  Location             Maker         Modem Code Size STime Mode Ecm Result  
	--------------------------------------------------------------------------------
    00001 111-1111             Muratec       V17   JBIG A3   0     H    E
    00002 111-1112                                                          D.0.7
    00003 111-1113             Matsushita    V17   JBIG A3   40    S    E
    00004 111-1114             45            V17   MMR  A3   40    S    E
    
    
*************************************************************************/
WORD	Print_Sgp_Report_list(
						 void )			/*なし*/
{
	UWORD	i;			/* loop */
	UBYTE	line_cnt;	/* 残り印刷可能行数 */
	UBYTE	line_cnt_bkup;	/* 残り印刷可能行数の初期値 */
	WORD	ret;		/* 実行結果 */


	if ( (ret = Memory_Dump_Head( 0 ) ) != OK ) {
		return ( ret );
	}
	line_cnt_bkup = (UBYTE)(PaperSizeLen());	/* 残り印刷可能行数の初期値 */
	line_cnt = (UBYTE)(line_cnt_bkup - 4 );

	/** ヘッド印字 */
	Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
	CMN_StringCopy( List.S.Print, SgpReportHead );
	if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* １行印字 */
		return ( ret );
	}

	/** 横罫線印字 */
	CMN_MemorySet( (UBYTE *)&List.S.Print[1-1], 80, LST_KLINE_ );
	if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
		return ( ret );
	}

	for ( i = 0; i < SYS_SGP_REPORT_MAX; i++ ) {
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );

		/** 通番 */
		CMN_UnsignedIntToASC( &List.S.Print[1-1], SYB_PerformanceFile[i].Number, 5, '0' );

		/* ダイアル番号 */
		CMN_StringCopy( &List.S.Print[7-1], SYB_PerformanceFile[i].RemoteID );
			
		/* メーカーコード */
		switch (SYB_PerformanceFile[i].Maker ) {
			case 0xA2: /* 村田機械			Muratec */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[0] );
				break;
			case 0x6A: /* ﾌﾞﾗｻﾞｰ工業			Brother */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[1] );
				break;
			case 0x81: /* Ｃａｎｏｎ １		Cannon1 */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[2] );
				break;
			case 0x83: /* Ｃａｎｏｎ ２		Cannon2 */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[3] );
				break;
			case 0x84: /* 沖電気				Oki     */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[4] );
				break;
			case 0x88: /* ｷｬﾉﾝ				Cannon3 */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[5] );
				break;
			case 0x8A: /* 三洋電機			Sanyo   */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[6] );
				break;
			case 0x8C: /* ｼｬｰﾌﾟ				Sharp   */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[7] );
				break;
			case 0x92: /* 日本電気(NEC)		NEC	    */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[8] );
				break;
			case 0x98: /* 富士ｾﾞﾛｯｸｽ			Xerox   */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[9] );
				break;
			case 0x9C: /* 松下電気			Pana    */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[10] );
				break;
			case 0x9E: /* 松下電送			Densou  */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[11] );
				break;
			case 0xA0: /* 三菱電気		 Mitsubishi */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[12] );
				break;
			case 0xA4: /* ﾘｺｰ				Ricoh   */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[13] );
				break;
			case 0xAE: /* 東京電気(TEC)		TEC     */
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], (UBYTE *)SgpReportMaker[14] );
				break;
			default:
				CMN_StringCopy( (UBYTE *)&List.S.Print[28-1], &SYB_PerformanceFile[i].Maker );
				break;
		}
			
		/* モデム能力 */
		switch (SYB_PerformanceFile[i].Baudrate ) {
			case (PER_MODEM_BAUDRATE_V17):
				AttributeSet( &List.S.Print[42], &List.S.Attribute[42], PWRD_V17, LST_NOT );
				break;
			case (PER_MODEM_BAUDRATE_V33):
				AttributeSet( &List.S.Print[42], &List.S.Attribute[42], PWRD_V33, LST_NOT );
				break;
			case (PER_MODEM_BAUDRATE_V29):
				AttributeSet( &List.S.Print[42], &List.S.Attribute[42], PWRD_V29, LST_NOT );
				break;
			case (PER_MODEM_BAUDRATE_V27):
				AttributeSet( &List.S.Print[42], &List.S.Attribute[42], PWRD_V27, LST_NOT );
				break;
		}
				
		/* 符号化方式 */
		switch (SYB_PerformanceFile[i].Code ) {
			case (PER_CODE_JBIG):
				AttributeSet( &List.S.Print[48], &List.S.Attribute[48], PWRD_JBG, LST_NOT );
				break;
			case (PER_CODE_MMR):
				AttributeSet( &List.S.Print[48], &List.S.Attribute[48], PWRD_MMR, LST_NOT );
				break;
			case (PER_CODE_MR):
				AttributeSet( &List.S.Print[48], &List.S.Attribute[48], PWRD_MR, LST_NOT );
				break;
			case (PER_CODE_MH):
				AttributeSet( &List.S.Print[48], &List.S.Attribute[48], PWRD_MH, LST_NOT );
				break;
		}
			
		/* 記録幅 */
		switch (SYB_PerformanceFile[i].Size ) {
			case (PER_SIZE_A4):
				AttributeSet( &List.S.Print[53], &List.S.Attribute[53], PWRD_A4, LST_NOT );
				break;
			case (PER_SIZE_B4):
				AttributeSet( &List.S.Print[53], &List.S.Attribute[53], PWRD_B4, LST_NOT );
				break;
			case (PER_SIZE_A3):
				AttributeSet( &List.S.Print[53], &List.S.Attribute[53], PWRD_A3, LST_NOT );
				break;
		}
			
		/* 受信最小電送時間 */
		switch (SYB_PerformanceFile[i].ScanningTime ) {
			case (PER_SCAN_TIME0):
				AttributeSet( &List.S.Print[58], &List.S.Attribute[58], PWRD_Wait0, LST_NOT );
				break;
			case (PER_SCAN_TIME10):
				AttributeSet( &List.S.Print[58], &List.S.Attribute[58], PWRD_Wait10, LST_NOT );
				break;
			case (PER_SCAN_TIME20):
				AttributeSet( &List.S.Print[58], &List.S.Attribute[58], PWRD_Wait20, LST_NOT );
				break;
			case (PER_SCAN_TIME40):
				AttributeSet( &List.S.Print[58], &List.S.Attribute[58], PWRD_Wait40, LST_NOT );
				break;
			case (PER_SCAN_TIME5):
				AttributeSet( &List.S.Print[58], &List.S.Attribute[58], PWRD_Wait5, LST_NOT );
				break;
		}
			
		/* 受信線密度 */
		switch (SYB_PerformanceFile[i].Mode ) {
			case (PER_MODE_NORMAL):
				AttributeSet( &List.S.Print[64], &List.S.Attribute[54], PWRD_ModeNR, LST_NOT );
				break;
			case (PER_MODE_FINE):
				AttributeSet( &List.S.Print[64], &List.S.Attribute[54], PWRD_ModeFN, LST_NOT );
				break;
			case (PER_MODE_S_FINE):
				AttributeSet( &List.S.Print[64], &List.S.Attribute[54], PWRD_ModeSF, LST_NOT );
				break;
			case (PER_MODE_O_FINE):
				List.S.Print[64-1] = 'O';
				break;
			case (PER_MODE_H_FINE):
				AttributeSet(&List.S.Print[64], &List.S.Attribute[54], PWRD_ModeHF, LST_NOT );
				break;
		}
			
		/* ＥＣＭ機能 */
		if (SYB_PerformanceFile[i].EcmMode == 1) {
			List.S.Print[69-1] = 'E';
		}
		else {
			List.S.Print[69-1] = ' ';
		}
			
		/* 結果 */
		if (SYB_PerformanceFile[i].Result == 0) {
			List.S.Print[73-1] = ' ';
		}
		else {
			CommunicationResultName(SYB_PerformanceFile[i].Result,
									LST_NAME_SHORT,
									LST_RESULT_COMMON,
									&List.S.Print[73-1],
									&List.S.Attribute[73-1]);
		}
				
		if ( (ret = Memory_Dump_1Line( &line_cnt )) != OK ) {	/* １行印字 */
			return ( ret );
		}
			
		if (line_cnt == line_cnt_bkup) {
			line_cnt -= 2;
		}
	}
	if ( (ret = Memory_Dump_Head( 1 ) ) != OK ) {
		return ( ret );
	}
	return( OK );
}

#endif