/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MSW.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: メモリスイッチ
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mntsw_a.h"
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\unisw_g.h" /* 1996/07/09 Eguchi */

#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\atd_tbl.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\cmn_tbl.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\lst_wrd.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"

#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\define\prn_stat.h"
#include	"\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include	"\src\atlanta\prt\sp322\define\prn_stat.h"
#include	"\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)
#include	"\src\atlanta\prt\thermal\define\prn_stat.h"
#include	"\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif
#if (PRO_MULTI_LINE == ENABLE)	/* Add By M.Kotani 1997/06/26 */
#include	"\src\atlanta\define\unisw_d.h"
#include	"\src\atlanta\define\unisw_g.h"
#endif

#undef	PRO_JIS_CODE
#define	PRO_JIS_CODE		DISABLE				/* 漢字ＣＧＲＯＭ対応 */

/*************************************************************************
	module		:[メモリスイッチ]
	function	:[メモリスイッチを印刷する]
	common		:[
		List						:
		SYB_MachineParameter		:
		MachineParameterInitialTable:
		SYS_MemorySwitch			:
		MemorySwitchInitialTable	:
	]
	condition	:[]
	commment	:[機種固有のメモリスイッチを追加 By H.Hirao Mar,03.1996]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD				Print_Memory_switch(
						 void )			/*なし*/
{
	UBYTE	i;					/** loop */
	UBYTE	j;
	register WORD	ret;				/** 実行結果 */
	UBYTE	sw1;				/** ｽｲｯﾁ ﾜｰｸ */
	UBYTE	sw2;				/** ｽｲｯﾁ ﾜｰｸ */
	UBYTE	country_code;		/** ｶﾝﾄﾘｰｺｰﾄﾞ */
	UBYTE	is_last_page;		/** 印刷終了フラグ */
	UBYTE	line_cnt;			/** 行数 */

	is_last_page	= FALSE;
	for ( j = 0; j <= 3; j++ ) {
		if( is_last_page == TRUE ){		/* 保守スイッチ無しの時終了  */
			break;
		}

		if ( (ret = Print_MemorySwitch_Head( 0 ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
			return( ret );
		}
		line_cnt = (UBYTE)(PaperSizeLen() - 6);/*印刷可能行数ｾｯﾄ*/
		/** 明細印刷 */
		if ( j == 0 ) { /* 機器パラメータの明細を印刷 */
			country_code = MachineParameterInitialTable[COUNTRY_CODE];
			if ( country_code > 7) {	/* 国別コードが0～7の場合 */
				country_code = 0;
			}

			for ( i = 0; i < (UBYTE)(SYS_MACHINE_PARAMETER_MAX/2); i++ ) {
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				if ( i == 0 ) {
					AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1],
					  PWRD_Machine_P, LST_NOT );
				}
				if ( (i % 10) == 0 ) {
					if( line_cnt <= 10 ){
						if ( (ret = Print_MemorySwitch_Head( 1 ) ) != OK ) {/*ﾌｯﾀ印刷*/
							return ( ret );
						}
						if ( (ret = Print_MemorySwitch_Head( 0 ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
							return( ret );
						}
						line_cnt = (UBYTE)(PaperSizeLen() - 6);/*印刷可能行数ｾｯﾄ*/
						Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
						AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1],
						  PWRD_Machine_P, LST_NOT );
					}

					

/* 表示変更　Modify by SMuratec K.W.Q 2003/11/11 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
				}
				
				List.S.Print[19-1] = (UBYTE)('0' + i/10);
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[54-1] = (UBYTE)('0' + i/10 + 5);
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#else
					List.S.Print[16-1] = (UBYTE)('A' + i/10);
					List.S.Print[51-1] = (UBYTE)('A' + i/10 + 5);
				}
				
				List.S.Print[18-1] = '-';
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[53-1] = '-';
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#endif
				sw1 = MachineParameterInitialTable[i];
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.23 K.Kawata	*/
				if (CHK_OCA_Specification()) {
					switch (i) {
						case 31:
							sw1 = 0x08;
						break;
						case 32:
							sw1 = 0xff;
						break;
						case 33:
							sw1 = 0xf6;
						break;
						case 34:
							sw1 = 0xeb;
						break;
						case 36:
							sw1 = 0x00;
						break;
					}
				}
#endif
				/*この部分はcmn_ini.cのCMN_InitializeMachineParameter()に合わせて*/
				/*作成されています。masuda*/
				switch ( i ) {
					case COUNTRY_CODE:
						sw1 = country_code;
						break;
					case MACHINE_PARA_1:
						/** 変更 -- 1998/03/04  By T.Yamaguchi */
						/** sw1 |= CountryTable[country_code][COUNTRY_SW_15];   */
						/* 送出レベル画データ(減衰器設定値) */

#if (PRO_PRINT_TYPE == THERMAL)
						/* 「送出レベルの設定は、基本的には、機器パラメーターＡ：１で行う。
						**   個別に設定が必要な場合はメモリスイッチＢ：１を使う 」というのが一般的なフィールドでの対応らしい。
						** ということで、初期化を行う時に国別設定を機器パラに代入するようにする。
						** パラメーターの一覧をプリントする時も変更もしていないのに、初期値と設定値が異なるのは、
						** 後々、フィールドで混乱するので、必ず一致させるようにとのＣＳサービスから強い要望がありました。
						** とりあえず、ＨＩＮＯＫＩはＣＳサービスから槍玉に挙げられていますので、対応しておきます。
						** By O.Kimoto 1999/03/03
						*/
						sw1 &= ~ATTENATION_MACHINE_PARA;
						sw1 |= CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15];	/* 送出レベル画データ(減衰器設定値) */
#endif

					break;
					case MACHINE_PARA_2:
					/*DialTable[]はCTRY_DialTable()関数でにるべきだが、内部で
					ｶﾝﾄﾘｰｺ-ﾄﾞを見ている為、このようにしている。masuda*/
					sw1 |= DialTable[country_code].LevelDTMF;
										/* 送出レベルDTMF(減衰器設定値) */
					break;
				}
				sw2 = MachineParameterInitialTable[i+SYS_MACHINE_PARAMETER_MAX/2];
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.23 K.Kawata	*/
				if (CHK_OCA_Specification()) {
					switch (i+SYS_MACHINE_PARAMETER_MAX/2) {
						case 75:
							sw2 = 0x17;
						break;
						case 77:
							sw2 = 0x15;
						break;
						case 79:
							sw2 = 0x13;
						break;
					}
				}
#endif
				Dip_String_Set( sw1, &List.S.Print[24-1], &List.S.Attribute[24-1] );
				Dip_String_Set( SYB_MachineParameter[i], &List.S.Print[36-1], &List.S.Attribute[36-1] );
				Dip_String_Set( sw2, &List.S.Print[59-1], &List.S.Attribute[59-1] );
				Dip_String_Set( SYB_MachineParameter[i+SYS_MACHINE_PARAMETER_MAX/2],
				  &List.S.Print[71-1], &List.S.Attribute[71-1] );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				line_cnt--;
			}
		}

		if ( j == 1 ) { /* メモリスイッチの明細を印刷 */
			for ( i = 0; i < (UBYTE)(SYS_MEMORY_SWITCH_MAX/2); i++ ) {
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				if ( i == 0 ) {
					AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_Memory_S, LST_NOT );
				}

				if ( (i % 10) == 0 ) {
					if( line_cnt <= 10 ){
						if ( (ret = Print_MemorySwitch_Head( 1 ) ) != OK ) {/*ﾌｯﾀ印刷*/
							return ( ret );
						}
						if ( (ret = Print_MemorySwitch_Head( 0 ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
							return( ret );
						}
						line_cnt = (UBYTE)(PaperSizeLen() - 6);/*印刷可能行数ｾｯﾄ*/
						Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
						AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_Memory_S, LST_NOT );
					}
					
/* 表示変更　Modify by SMuratec K.W.Q 2003/11/11 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
				}
				
				List.S.Print[19-1] = (UBYTE)('0' + i/10);
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[54-1] = (UBYTE)('0' + i/10 + 5);
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#else

					List.S.Print[16-1] = (UBYTE)('A' + i/10);
					List.S.Print[51-1] = (UBYTE)('A' + i/10 + 5);
				}

				List.S.Print[18-1] = '-';
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[53-1] = '-';
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#endif

#if (0) /* Delete BY H.H 1997/04/15 */
				Dip_String_Set( MemorySwitchInitialTable[i], &List.S.Print[24-1], &List.S.Attribute[24-1] );
				Dip_String_Set( SYS_MemorySwitch[i], &List.S.Print[36-1], &List.S.Attribute[36-1] );
				Dip_String_Set( MemorySwitchInitialTable[i+SYS_MEMORY_SWITCH_MAX/2],
				  &List.S.Print[59-1], &List.S.Attribute[59-1] );
				Dip_String_Set( SYS_MemorySwitch[i+SYS_MEMORY_SWITCH_MAX/2],
				  &List.S.Print[71-1], &List.S.Attribute[71-1] );
#endif
#if (1)
				/* トーンアッテネータの初期値は国別テーブルより参照するように変更
				** BY H.H 1997/04/15
				*/
				sw1 = MemorySwitchInitialTable[i];
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.23 K.Kawata	*/
				if (CHK_OCA_Specification()) {
					if (i == 15) {
						sw1 = 0x06;
					}
				}
#endif
				sw2 = MemorySwitchInitialTable[i+SYS_MEMORY_SWITCH_MAX/2];
				/* 国別テーブルより初期値を決定 */
				switch ( i ) {
/*				case MEMORY_SW_B1: @** トーンアッテネータの初期値 */
				case 11:		 /** トーンアッテネータの初期値 */
					sw1 &= 0xF0;
					sw1 |= (unsigned char)(CountryTable[country_code][COUNTRY_SW_15] & 0x0F);
					break;
				default:
					break;
				}
				Dip_String_Set( sw1, &List.S.Print[24-1], &List.S.Attribute[24-1] );
				Dip_String_Set( SYS_MemorySwitch[i], &List.S.Print[36-1], &List.S.Attribute[36-1] );
				Dip_String_Set( sw2, &List.S.Print[59-1], &List.S.Attribute[59-1] );
				Dip_String_Set( SYS_MemorySwitch[i+SYS_MEMORY_SWITCH_MAX/2],
				  &List.S.Print[71-1], &List.S.Attribute[71-1] );
#endif
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				line_cnt--;
			}
		}
		if ( j == 2 ) { /* 機種固有メモリスイッチの明細を印刷 */
			for ( i = 0; i < (UBYTE)(SYS_MEMORY_SWITCH_MAX/2); i++ ) {
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				if ( i == 0 ) {
					AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_Uniq_S, LST_NOT );
				}

				if ( (i % 10) == 0 ) {
					if( line_cnt <= 10 ){
						if ( (ret = Print_MemorySwitch_Head( 1 ) ) != OK ) {/*ﾌｯﾀ印刷*/
							return ( ret );
						}
						if ( (ret = Print_MemorySwitch_Head( 0 ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
							return( ret );
						}
						line_cnt = (UBYTE)(PaperSizeLen() - 6);/*印刷可能行数ｾｯﾄ*/
						Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
						AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_Uniq_S, LST_NOT );
					}

/* 表示変更　Modify by SMuratec K.W.Q 2003/11/11 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
				}
				
				List.S.Print[19-1] = (UBYTE)('0' + i/10);
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[54-1] = (UBYTE)('0' + i/10 + 5);
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#else
					List.S.Print[16-1] = (UBYTE)('A' + i/10);
					List.S.Print[51-1] = (UBYTE)('A' + i/10 + 5);
				}

				List.S.Print[18-1] = '-';
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[53-1] = '-';
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#endif

#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/06/26 */
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.3.23 K.Kawata	*/
				if (CHK_OCA_Specification() && (i == 23)) {
						Dip_String_Set(0xf0, &List.S.Print[24-1], &List.S.Attribute[24-1]);
				}
				else {
						Dip_String_Set( UniqSwitchInitialTable[i], &List.S.Print[24-1], &List.S.Attribute[24-1] );
				}
#else
				Dip_String_Set( UniqSwitchInitialTable[i], &List.S.Print[24-1], &List.S.Attribute[24-1] );
#endif
				Dip_String_Set( SYB_MachineUniqSwitch[i], &List.S.Print[36-1], &List.S.Attribute[36-1] );
				/* 機種固有スイッチのＧ１はDialTable[]の値で初期化するため、ちょっと変更します */
				/* 1996/07/09　Eguchi */
				if (i + SYS_MEMORY_SWITCH_MAX/2 == UNIQ_SW_G1) {
					/* カントリーコードはマシーンパラメータ印字の所で使用したものを使う */
					Dip_String_Set( DialTable[country_code].FlashTime , &List.S.Print[59-1], &List.S.Attribute[59-1] );
				}
				else {
					Dip_String_Set( UniqSwitchInitialTable[i+SYS_MEMORY_SWITCH_MAX/2],
					  &List.S.Print[59-1], &List.S.Attribute[59-1] );
				}
				Dip_String_Set( SYB_MachineUniqSwitch[i+SYS_MEMORY_SWITCH_MAX/2],
				  &List.S.Print[71-1], &List.S.Attribute[71-1] );
#else
				sw1 = UniqSwitchInitialTable[i];
				sw2 = UniqSwitchInitialTable[i+SYS_MEMORY_SWITCH_MAX/2];
				/* 国別テーブルより初期値を決定 */
				switch ( i ) {
				case UNIQ_SW_D4:
					sw1 &= 0xF0;
					sw1 |= (UBYTE)(CountryOptionTable[country_code][COUNTRY_OPTION__SW_0] & 0x0F);
					break;
				case UNIQ_SW_D5:
					sw1 &= 0xF0;
					sw1 |= (UBYTE)(CountryOptionTable[country_code][COUNTRY_OPTION__SW_1] & 0x0F);
					break;
				default:
					break;
				}
				switch (i + SYS_MEMORY_SWITCH_MAX/2) {
				case UNIQ_SW_G1:
					sw2 = DialTable[country_code].FlashTime;
					break;
				default:
					break;
				}
				Dip_String_Set( sw1, &List.S.Print[24-1], &List.S.Attribute[24-1] );
				Dip_String_Set( SYB_MachineUniqSwitch[i], &List.S.Print[36-1],		/**SYS -> SYB 970626 By M.Kotani*/
				  &List.S.Attribute[36-1] );
				Dip_String_Set( sw2, &List.S.Print[59-1], &List.S.Attribute[59-1] );
				Dip_String_Set( SYB_MachineUniqSwitch[i+SYS_MACHINE_PARAMETER_MAX/2], /**SYS -> SYB 970626 By M.Kotani*/				  &List.S.Print[71-1], &List.S.Attribute[71-1] );
#endif

				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				line_cnt--;
			}
			/* 保守用スイッチの印刷無しの時 97/03/04 M.kuwahra */
			if((SYB_MaintenanceSwitch[MNT_SW_A8] & MNT_SW_LIST_PRINT) == 0x00 ){
				is_last_page	= TRUE;
			}
		}

		if ( j == 3 ) { /* 保守用メモリスイッチの明細を印刷 *//* 追加 97/03/04 M.Kuwahara */
			for ( i = 0; i < (UBYTE)(SYS_MEMORY_SWITCH_MAX/2); i++ ) {
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				if ( i == 0 ) {
					AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_MainteSwitch, LST_NOT );
				}

				if ( (i % 10) == 0 ) {
					if( line_cnt <= 10 ){
						if ( (ret = Print_MemorySwitch_Head( 1 ) ) != OK ) {/*ﾌｯﾀ印刷*/
							return ( ret );
						}
						if ( (ret = Print_MemorySwitch_Head( 0 ) ) != OK ) {/*ﾍｯﾀﾞ印刷*/
							return( ret );
						}
						Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
						line_cnt = (UBYTE)(PaperSizeLen() - 6);/*印刷可能行数ｾｯﾄ*/
						AttributeSet( &List.S.Print[1-1], &List.S.Attribute[1-1], PWRD_MainteSwitch, LST_NOT );
					}

/* 表示変更　Modify by SMuratec K.W.Q 2003/11/11 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
				}
				
				List.S.Print[19-1] = (UBYTE)('0' + i/10);
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[54-1] = (UBYTE)('0' + i/10 + 5);
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#else
					List.S.Print[16-1] = (UBYTE)('A' + i/10);
					List.S.Print[51-1] = (UBYTE)('A' + i/10 + 5);
				}

				List.S.Print[18-1] = '-';
				List.S.Print[20-1] = (UBYTE)('0' + (i % 10));
				List.S.Print[53-1] = '-';
				List.S.Print[55-1] = (UBYTE)('0' + (i % 10));
#endif

				Dip_String_Set( MaintenanceSwInitialTable[i], &List.S.Print[24-1], &List.S.Attribute[24-1] );
				Dip_String_Set( SYB_MaintenanceSwitch[i], &List.S.Print[36-1], &List.S.Attribute[36-1] );
				Dip_String_Set( MaintenanceSwInitialTable[i+SYS_MEMORY_SWITCH_MAX/2],
				  &List.S.Print[59-1], &List.S.Attribute[59-1] );
				Dip_String_Set( SYB_MaintenanceSwitch[i+SYS_MEMORY_SWITCH_MAX/2],
				  &List.S.Print[71-1], &List.S.Attribute[71-1] );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				line_cnt--;
			}
			is_last_page	= TRUE;
		}

		/*１行印字（改行）*/
		if( is_last_page == TRUE ){

#if (0)
** 			/* 以下の空行はライフモニタープリントを行う際に、体裁を整えるために入れるべきである。
** 			** よって、MEMSW_LIFE_MONITOR_PRINTのビットが１のときだけ空行を挿入するように変更
** 			** by O.Kimoto 1998/12/04
** 			*/
** 			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
** 				return ( ret );
** 			}
#endif

			if( SYB_MaintenanceSwitch[MNT_SW_A8] & MEMSW_LIFE_MONITOR_PRINT ){
				/* ﾌﾟﾘﾝﾀｰのSTATUSをﾒﾓﾘｽｲｯﾁのﾍﾟｰｼﾞに記載する */

				/* 以下の空行はライフモニタープリントを行う際に、体裁を整えるために入れるべきである。
				** よって、MEMSW_LIFE_MONITOR_PRINTのビットが１のときだけ空行を挿入するように変更
				** by O.Kimoto 1998/12/04
				*/
				if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
					return ( ret );
				}

#if (PRO_PRINT_TYPE == LASER) || (PRO_PRINT_TYPE == LED)	/* 1998/06/09 H.Yoshikawa */
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				List.S.Print[0] = 'P';
				List.S.Print[1] = ' ';
				List.S.Print[2] = ':';
				List.S.Print[3] = ' ';
				for ( i = 0; i < PRN_STATUS_MAX; i++ ) {
					if( (UBYTE)((PrinterStatus[i] & 0xF0) >> 4) < 10 ){
						List.S.Print[4+(3*i)+0] = (UBYTE)(((PrinterStatus[i] & 0xF0) >> 4) + '0');
					}
					else {
						List.S.Print[4+(3*i)+0] = (UBYTE)(((PrinterStatus[i] & 0xF0) >> 4) + 'A' - 0x0A);
					}
					if( (UBYTE)(PrinterStatus[i] & 0x0F) < 10 ) {
						List.S.Print[4+(3*i)+1] = (UBYTE)((PrinterStatus[i] & 0x0F) + '0');
					}
					else {
						List.S.Print[4+(3*i)+1] = (UBYTE)((PrinterStatus[i] & 0x0F) + 'A' - 0x0A);
					}
					if ( i < (PRN_STATUS_MAX - 1) ) {
						List.S.Print[4+(3*i)+2] = ',';
					}
				}
				List.S.Print[4+(3*i)+2] = NULL;
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
				if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
					return ( ret );
				}
				
				/* ライフモニターの情報を印字する */
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				List.S.Print[0] = 'S';		/* ScanCount */
				List.S.Print[13] = 'P';		/* PrintCount */
				List.S.Print[26] = 'T';		/* TransmitCount */
				List.S.Print[39] = 'D';		/* DrumLifeCount */
				List.S.Print[51] = 'D';		
				List.S.Print[52] = 'R';		/* DrumReplaceCount */
				for ( i = 2; i <= 54; i += 13 ) {
					List.S.Print[i] = ':';
				}
				/* ↓ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
				CMN_UnsignedLongToASC( &List.S.Print[4], SYB_LifeMonitor.ScanCount, 6, NULL );
				CMN_UnsignedLongToASC( &List.S.Print[17], SYB_LifeMonitor.PrintCount, 6, NULL );
				CMN_UnsignedLongToASC( &List.S.Print[30], SYB_LifeMonitor.TransmitCount, 6, NULL );
				CMN_UnsignedLongToASC( &List.S.Print[43], SYB_LifeMonitor.DrumLifeCount, 6, NULL );
				CMN_UnsignedLongToASC( &List.S.Print[57], SYB_LifeMonitor.DrumReplaceCount, 6, NULL );
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
#endif
#if (PRO_PRINT_TYPE == THERMAL) || (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/06/09 H.Yoshikawa */
				/* ライフモニターの情報を印字する */
				Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
				List.S.Print[0] = 'S';		/* ScanCount */
				List.S.Print[13] = 'P';		/* PrintCount */
				List.S.Print[26] = 'T';		/* TransmitCount */
#if (0)	/* 1998/06/09 H.Yoshikawa */
//				List.S.Print[39] = 'D';		/* DrumLifeCount */
//				List.S.Print[51] = 'D';		
//				List.S.Print[52] = 'R';		/* DrumReplaceCount */
#endif

				for ( i = 2; i <= 54; i += 13 ) {
					List.S.Print[i] = ':';
				}
				/* ↓ Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */
				CMN_UnsignedLongToASC( &List.S.Print[4], SYB_LifeMonitor.ScanCount, 6, NULL );
				CMN_UnsignedLongToASC( &List.S.Print[17], SYB_LifeMonitor.PrintCount, 6, NULL );
				CMN_UnsignedLongToASC( &List.S.Print[30], SYB_LifeMonitor.TransmitCount, 6, NULL );
#if (0)	/* 1998/06/09 H.Yoshikawa */
//				CMN_UnsignedLongToASC( &List.S.Print[43], SYB_LifeMonitor.DrumLifeCount, 6, NULL );
//				CMN_UnsignedLongToASC( &List.S.Print[57], SYB_LifeMonitor.DrumReplaceCount, 6, NULL );
#endif
				if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
					return ( ret );
				}
#endif
			}

			/*１行印字（改行）*/
			if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
				return ( ret );
			}
    	}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
}


/*************************************************************************
	module		:[デイップスイッチビット内容文字列変換]
	function	:[デイップスイッチのビット内容を文字列に変換する。]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void				Dip_String_Set(
						 UBYTE DipSwitch,			/*デイップスイッチ データ*/
						 register UBYTE *AscString,	/*印刷文字列*/
						 register UBYTE *AttString )/*修飾文字列*/
{
	UBYTE	i;						/*bit test*/

	for ( i = 0x80; i != 0; i >>= 1 ) {
		if ( ( DipSwitch & i) != 0 ) {
			*AscString = '1';
		}
		else {
			*AscString = '0';
		}
		AscString++;
		if ( i == 0x10 ) {
			AscString++;
		}
	}
}

/*************************************************************************
	module		:[メモリスイッチリストヘッダ印刷]
	functiom	:[メモリスイッチリストのヘッダを印刷する]
	common		:[
		List	:
	]
	condition	:[
		ﾍｯﾀﾞ種類
			0->ﾍﾟｰｼﾞ先頭見出し
			1->ﾍﾟｰｼﾞｴﾝﾄﾞ見出し
	]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[97/05/06]
	author		:[桑原美紀]
*************************************************************************/
WORD				Print_MemorySwitch_Head(
						 UBYTE Category)	/*ヘッダ種類*/
{
	WORD	ret;

	if ( Category == 0 ) {
		/** マシンパラメータの印刷 */
		if ( (ret = CharacterPrint( LST_OPEN )) != OK ) {
			return ( ret );
		}

		/**１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}

		/** ｼｮｷﾁ ｾｯﾃｲﾁ  ｼｮｷﾁ ｾｯﾃｲﾁ */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_Default, LST_NOT );
		AttributeSet( &List.S.Print[36-1], &List.S.Attribute[36-1], PWRD_AutoSet, LST_NOT );
		AttributeSet( &List.S.Print[59-1], &List.S.Attribute[59-1], PWRD_Default, LST_NOT );
		AttributeSet( &List.S.Print[71-1], &List.S.Attribute[71-1], PWRD_AutoSet, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/** 7654 3210	 7654 3210 */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		AttributeSet( &List.S.Print[24-1], &List.S.Attribute[24-1], PWRD_BitNumber, LST_NOT );
		AttributeSet( &List.S.Print[36-1], &List.S.Attribute[36-1], PWRD_BitNumber, LST_NOT );
		AttributeSet( &List.S.Print[59-1], &List.S.Attribute[59-1], PWRD_BitNumber, LST_NOT );
		AttributeSet( &List.S.Print[71-1], &List.S.Attribute[71-1], PWRD_BitNumber, LST_NOT );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/** ---- ----	 ---- ---- */
		Prn_Att_Str_Clear( List.S.Print, List.S.Attribute );
		CMN_MemorySet( &List.S.Print[24-1], 21, LST_KLINE_ );
		CMN_MemorySet( &List.S.Print[59-1], 21, LST_KLINE_ );
		if ( (ret = CharacterPrint( LST_PRINT )) != OK ) {
			return ( ret );
		}

		/**１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
	}
	else{
		/*１行印字（改行）*/
		if ( (ret = CharacterPrint( LST_LINE_FEED )) != OK ) {
			return ( ret );
		}
		if ( (ret = CharacterPrint( LST_CLOSE )) != OK ) {
			return ( ret );
		}
	}
	return( OK );
}
