/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_main.c                                               */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/24                                               */
/*  概  要       : フラッシュメモリへのコマンド発行                         */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\ATLANTA\FLA\define\fla_pro.h"
#include	"\src\ATLANTA\FLA\define\fla_def.h"
#include	"\src\ATLANTA\FLA\ext_v\fla_tbl.h"
#include	"\src\ATLANTA\FLA\define\sys_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\FCM_DEF.h"
void RestartSystem(void);

#if defined(HINOKI) || defined (HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
#include "\src\cpu\sh7043_a\irom\define\def_mon.h"
extern void *INT_HINO_VectorTable[];
#endif

extern UBYTE SYB_FlashROM_WriteStatus;
#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)

/*************************************************************************
	module		:[フラッシュ書き換えメインループ]
	function	:[
					1.ＬＣＤ、ＬＥＤ、ブザーの初期化を行う
					2.フラッシュの書き換え
					3.結果の判定
				]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/04/25]
	author		:[橘正樹]
*************************************************************************/
void	FlashMainControl(void)
{
	UBYTE	result;
	UBYTE	loop_count;
	UWORD	sum;
	UWORD	rom0_sum;
	UWORD	rom1_sum;
	UBYTE	buffer[OPR_DISPLAY_MAX+1];

#if defined(HINOKI) || defined (HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
	UWORD count;
	UDWORD *address;
	UDWORD initial_value;
#endif

#if 0
//	if (DEBUG_FlashCheck) {
//		FlashMemoryCheck();
//		return;
//	}
#endif

	FLA_IO_Port_Initialize();

#if defined(HINOKI)	|| defined(HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined (HINOKI3) /* Add By O.Kimoto 1998/12/21 */ /* HINOKI2 2001/11/13 T.Takagi */
	address = (UDWORD *)TOP_SMALL_ADDR;	/* MON_TOP_SMALL_ADDR; */
	for (count = 0; count < (STACK_PUSH_SIZE/4); count++) {
		if (count == 3) { /* SH-VBR のセット */
			initial_value = (UDWORD)&INT_HINO_VectorTable[0];
		}
		else {
			initial_value = 0;
		}
		*address++ = initial_value;
	}

	FLA_LCD_Initialize();
	FLA_InitializeGateArray();

#else
	FLA_SCN_Init();
	FLA_LCD_Initialize();
#endif


	loop_count = 10;	/* エラー時にフラッシュ書き込み最大１０回繰り返す */

	while (loop_count) {

#if (PRO_PANEL == ANK)
		FLA_DisplayStringHigh(0, (UBYTE *)Title_Msg);
#else
		FLA_DisplayString0((UBYTE *)Title_Msg);
#endif

		result = PASS_FLAG;
		result = Main_Function();

		switch (result) {
		case	PASS_FLAG:				/* 正常終了 */
/*			sum = GetWordSumCheck();			/* 書込みデータ取得 */
			sum = GetWordSumCheck( &rom0_sum, &rom1_sum );	/* 書込みデータ取得 */
			FLA_CMN_StringCopy(buffer, OK_Msg);		/* " OK        SUM:XXXX" */
			buffer[OPR_DISPLAY_MAX]	= 0x00;
			FLA_CMN_HexToASC(&buffer[16], (UDWORD)sum, 4);
/*			FLA_DisplayStringLow(0, (UBYTE *)buffer);*/

#if (PRO_PANEL == ANK)
			FLA_DisplayStringHigh(0, (UBYTE *)buffer);
#else
			FLA_DisplayString0((UBYTE *)buffer);
#endif

			FLA_CMN_StringCopy(buffer, RomSum_Msg);	/* " ROM0:XXXX ROM1:XXXX" */
			FLA_CMN_HexToASC(&buffer[6], (UDWORD)rom0_sum, 4);
			FLA_CMN_HexToASC(&buffer[16], (UDWORD)rom1_sum, 4);

#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)buffer);
#else
			FLA_DisplayString1((UBYTE *)buffer);
#endif

			/* FLA_EndBuzzerSound();	エンドブザーは外します */

#if defined(POPLAR_F)
			/* debug */
			FLA_wait_timer(150);
#endif
		
			/* 書き込み終了した時点でステータスとDRAMをクリアする */
			SYB_FlashROM_WriteStatus = ROM_WRITE_COMPLETE;
			/* ここでリセットに飛ばす */
			RestartSystem();
			break;
		case	ERROR_FLAG_AUTOSELECT:	/* メーカーＩＤ読み出しエラー */
#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)NG_AutoSelect_Msg);
#else
			FLA_DisplayString1((UBYTE *)NG_AutoSelect_Msg);
#endif
			FLA_ErrorAlarmSound();
			break;
		case	ERROR_FLAG_CHIP_ERASE:	/* チップ消去エラー */
#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)NG_ChipErase_Msg);
#else
			FLA_DisplayString1((UBYTE *)NG_ChipErase_Msg);
#endif
			FLA_ErrorAlarmSound();
			break;
		case	ERROR_FLAG_SECTOR_ERASE:	/* セクタ消去エラー */
#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)NG_SectorErase_Msg);
#else
			FLA_DisplayString1((UBYTE *)NG_SectorErase_Msg);
#endif
			FLA_ErrorAlarmSound();
			break;
		case	ERROR_FLAG_TIMEOVER:	/* 時間切れエラー */
#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)NG_TimeOver_Msg);
#else
			FLA_DisplayString1((UBYTE *)NG_TimeOver_Msg);
#endif
			FLA_ErrorAlarmSound();
			break;
	case	ERROR_FLAG_PROGRAM:		/* 書き込みエラー */
#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)NG_Program_Msg);
#else
			FLA_DisplayString1((UBYTE *)NG_Program_Msg);
#endif
			FLA_ErrorAlarmSound();
			break;
		case	ERROR_FLAG_SUMCHECK:	/* サムチェックエラー */
#if (PRO_PANEL == ANK)
			FLA_DisplayStringLow(0, (UBYTE *)NG_SumCheck_Msg);
#else
			FLA_DisplayString1((UBYTE *)NG_SumCheck_Msg);
#endif
			FLA_ErrorAlarmSound();
			break;
		default:
			FLA_ErrorAlarmSound();
			break;
		}
		loop_count--;
	}
}

/*************************************************************************
	module		:[コマンド発行メインループ]
	function	:[
					1. オートセレクト・コマンド発行
					2. 全セクタ分ループし、セクタ使用可能まで検索
						2.1  サイズ分ループしデータ終了時までループ
						2.2  アドレス、データをセットし書込みコマンド発行
					3. 書込みデータチェック
				]
	return		:[
					ERROR_FLAG(2)	-> NG
					PASS_FLAG(0)	-> OK
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/04/25]
	author		:[桑原美紀]
*************************************************************************/
UBYTE Main_Function( void )
{
	UBYTE	ret;
	UBYTE	sector_cnt;				/* ｾｸﾀｶｳﾝﾀ */
	UWORD	manufacture_code;		/* ﾏﾆｭﾌｧｸﾁｬｺｰﾄﾞ */
	UWORD	device_code;			/* ﾃﾞﾊﾞｲｽｺｰﾄﾞ */
	UWORD	data;					/* 書込みﾃﾞｰﾀ */
	UWORD	*flash_addr;			/* 書込みｱﾄﾞﾚｽ */
	UWORD	*master_addr;			/* ﾒｲﾝROM側ｱﾄﾞﾚｽ */
	UWORD	main_sum;				/* 書込みﾃﾞｰﾀ合計数 */
	UDWORD	word_cnt;				/* 1ｾｸﾀ内のｶｳﾝﾀ */
	UWORD	rom0_sum;				/* ROM0の合計数 */
	UWORD	rom1_sum;				/* ROM1の合計数 */

	Autoselect_Function( &manufacture_code, &device_code );		/* カードの検知 */
	if(( manufacture_code != 0x0004 ) ||			/* 正しくｾｯﾄされているか */
	   ( device_code != 0x2258 )){
		return( ERROR_FLAG_AUTOSELECT );
	}
#if (PRO_PANEL == ANK)
	FLA_DisplayStringLow(0, (UBYTE *)Erasing_msg);	/**Add By M.Kotani 1997/08/06*/
#else
	FLA_DisplayString1((UBYTE *)Erasing_msg);
#endif

	master_addr = (UWORD *)MASTER_MEM;
	data = *master_addr;
	main_sum = 0;

	for( sector_cnt = 0; sector_cnt < SECTOR_MAX; sector_cnt++ ){
		if( SYS_RomMap[sector_cnt].Status == NOT_ROM_USE ){		/* 未使用の時 */
			continue;
		}
		while (1) {
			if((ret = Sector_Erase_Function((UWORD *)(SYS_RomMap[sector_cnt].StartAddress+FLASH_MEM))) != PASS_FLAG) {
				/**	消去不可－＞オーバイレーズ状態だった、オーバイレーズ是正処理	*/
				if (OverErase_Function((UWORD *)SYS_RomMap[sector_cnt].StartAddress,
				                       (UDWORD)SYS_RomMap[sector_cnt].Size) != PASS_FLAG) {
					return (ERROR_FLAG_SECTOR_ERASE);	/** 復旧せず（フラッシュ破壊している可能性あり） */
				}
				/* オーバイレース修正完了－＞再度、同じセクタ消去動作を行います */
			}
			else {
				break;	/* 書き込み処理に移ります */
			}
		}

#if (PRO_PANEL == ANK)
		FLA_DisplayStringLow(0, (UBYTE *)(&SectorNumber_msg[sector_cnt][0]));	/**Add By M.Kotani 1997/08/06*/
#else
		FLA_DisplayString1((UBYTE *)&SectorNumber_msg[sector_cnt][0]);
#endif
		flash_addr = (UWORD *)SYS_RomMap[sector_cnt].StartAddress;
		for( word_cnt = 0; word_cnt < (UDWORD)SYS_RomMap[sector_cnt].Size; word_cnt	+= 2 ){
			if(( ret = Program_Function( flash_addr, data )) != PASS_FLAG ){	/* ﾃﾞｰﾀの書込み */
				if( ret == FAIL_FLAG ){
					return( ERROR_FLAG_PROGRAM );
				}else{
					return( ret );
				}
			}
			main_sum += *master_addr;		/* サムチェック用 */
			master_addr ++;
			flash_addr ++;
			data = *master_addr;
		}
	}
#if 0	/* TEST */
//	if((ret = Chip_Erase_Function()) != PASS_FLAG ){			/* 全セクタ消去 */
//		if( ret == FAIL_FLAG ){
//			return( ERROR_FLAG_CHIP_ERASE );
//		}else{
//			return( ret );
//		}
//	}
//
//	master_addr = (UWORD *)MASTER_MEM;
//	data = *master_addr;
//	main_sum = 0;
//	for( sector_cnt = 0; sector_cnt < SECTOR_MAX; sector_cnt++ ){
//		if( SYS_RomMap[sector_cnt].Status == NOT_ROM_USE ){		/* 未使用の時 */
//			continue;
//		}
// #if (PRO_PANEL == ANK)
//		FLA_DisplayStringLow(0, (UBYTE *)(&SectorNumber_msg[sector_cnt][0]));	/**Add By M.Kotani 1997/08/06*/
// #else
//		FLA_DisplayString1((UBYTE *)&SectorNumber_msg[sector_cnt][0]);
// #endif
//		flash_addr = (UWORD *)SYS_RomMap[sector_cnt].StartAddress;
//		for( word_cnt = 0; word_cnt < (UDWORD)SYS_RomMap[sector_cnt].Size; word_cnt	+= 2 ){
//			if(( ret = Program_Function( flash_addr, data )) != PASS_FLAG ){	/* ﾃﾞｰﾀの書込み */
//				if( ret == FAIL_FLAG ){
//					return( ERROR_FLAG_PROGRAM );
//				}else{
//					return( ret );
//				}
//			}
//			main_sum += *master_addr;		/* サムチェック用 */
//			master_addr ++;
//			flash_addr ++;
//			data = *master_addr;
//		}
//	}
#endif

	/*	if( GetWordSumCheck() != main_sum ){	/* 書込みデータチェック */
	if( GetWordSumCheck( &rom0_sum, &rom1_sum ) != main_sum ){	/* 書込みデータチェック */
		return( ERROR_FLAG_SUMCHECK );
	}
/****** テストの為に入れてみる ********/
#if (0)
//	if((ret = Sector_Erase_Function( (UWORD *)(SYS_RomMap[0].StartAddress+FLASH_MEM) )) != PASS_FLAG){
//		if( ret == FAIL_FLAG ){
//			return( ERROR_FLAG_SECTOR_ERASE );
//		}else{
//			return( ret );
//		}
//	}
#endif
/**************************************/
	return( PASS_FLAG );
}


#if 0 /* 未使用  1998/04/17  By T.Yamaguchi */
///*************************************************************************
//	module		:[フラッシュメモリのベリファイ]
//	function	:[]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[FLASH]
//	date		:[1997/08/20]
//	author		:[橘正樹]
//*************************************************************************/
//void	FlashMemoryCheck(void)
//{
//	UBYTE	buffer[OPR_DISPLAY_MAX+1];
//	UWORD	manufacture_code;		/* ﾏﾆｭﾌｧｸﾁｬｺｰﾄﾞ */
//	UWORD	device_code;			/* ﾃﾞﾊﾞｲｽｺｰﾄﾞ */
//	UWORD	*flash_addr;			/* ﾌﾗｯｼｭｱﾄﾞﾚｽ */
//	UWORD	*flash_end_addr;		/* ﾌﾗｯｼｭｱﾄﾞﾚｽ */
//	UWORD	*master_addr;			/* ﾒｲﾝROM側ｱﾄﾞﾚｽ */
//	UWORD	sum;
//	UWORD	rom0_sum;
//	UWORD	rom1_sum;
//	UDWORD	error_count;
//
//	FLA_IO_Port_Initialize();
//	FLA_SCN_Init();
//	FLA_LCD_Initialize();
//
//#if (PRO_PANEL == ANK)
//	FLA_DisplayStringHigh(0, (UBYTE *)CheckTitle_Msg);
//#else
//	FLA_DisplayString0((UBYTE *)CheckTitle_Msg);
//#endif
//
//	Autoselect_Function( &manufacture_code, &device_code );		/* カードの検知 */
//	if(( manufacture_code != 0x0004 ) ||			/* 正しくｾｯﾄされているか */
//	   ( device_code != 0x2258 )){
//#if (PRO_PANEL == ANK)
//		FLA_DisplayStringLow(0, (UBYTE *)NG_AutoSelect_Msg);	/* メーカーＩＤ読み出しエラー */
//#else
//		FLA_DisplayString1((UBYTE *)NG_AutoSelect_Msg);
//#endif
//		FLA_ErrorAlarmSound();
//		return;
//	}
//
//	master_addr		= (UWORD *)MASTER_MEM;
//	flash_addr		= (UWORD *)FLASH_MEM;
//	flash_end_addr	= (UWORD *)(FLASH_MEM + 0x100000L);	/* 8Mbit */
//	error_count = 0;
//
//	while (flash_addr < flash_end_addr) {
//		if (*master_addr != *flash_addr) {
//			error_count++;
//			if (DEBUG_FlashCheck == 2) {
//				FLA_CMN_MemorySetNULL(buffer, OPR_DISPLAY_MAX, ' ');
//				FLA_CMN_HexToASC(&buffer[0], (UDWORD)flash_addr, 6);
//				FLA_CMN_HexToASC(&buffer[9], (UDWORD)*flash_addr, 4);
//				FLA_CMN_HexToASC(&buffer[15], (UDWORD)*master_addr, 4);
//#if (PRO_PANEL == ANK)
//				FLA_DisplayStringHigh(0, (UBYTE *)CheckNG_Msg);
//				FLA_DisplayStringLow(0, (UBYTE *)buffer);
//#else
//				FLA_DisplayString0((UBYTE *)CheckNG_Msg);
//				FLA_DisplayString1((UBYTE *)buffer);
//#endif
//				FLA_NackBuzzerSound();
//				/*wait_timer(100);*/
//			}
//		}
//		master_addr++;
//		flash_addr++;
//	}
//
//	if (error_count) {
//		FLA_CMN_StringCopy(buffer, CheckCnt_Msg);		/* "        xxxxxx Words" */
//		buffer[OPR_DISPLAY_MAX]	= 0x00;
//		FLA_CMN_UnsignedLongToASC(&buffer[8], (UDWORD)error_count, 6, ' ');
//#if (PRO_PANEL == ANK)
//		FLA_DisplayStringHigh(0, (UBYTE *)CheckErr_Msg);
//		FLA_DisplayStringLow(0, (UBYTE *)buffer);
//#else
//		FLA_DisplayString0((UBYTE *)CheckErr_Msg);
//		FLA_DisplayString1((UBYTE *)buffer);
//#endif
//		FLA_ErrorAlarmSound();
//	}
//	else {
//		sum = GetWordSumCheck( &rom0_sum, &rom1_sum );	/* 書込みデータ取得 */
//		FLA_CMN_StringCopy(buffer, OK_Msg);		/* " OK        SUM:XXXX" */
//		buffer[OPR_DISPLAY_MAX]	= 0x00;
//		FLA_CMN_HexToASC(&buffer[16], (UDWORD)sum, 4);
//#if (PRO_PANEL == ANK)
//		FLA_DisplayStringHigh(0, (UBYTE *)buffer);
//#else
//		FLA_DisplayString0((UBYTE *)buffer);
//#endif
//
//		FLA_CMN_StringCopy(buffer, RomSum_Msg);	/* " ROM0:XXXX ROM1:XXXX" */
//		FLA_CMN_HexToASC(&buffer[6], (UDWORD)rom0_sum, 4);
//		FLA_CMN_HexToASC(&buffer[16], (UDWORD)rom1_sum, 4);
//#if (PRO_PANEL == ANK)
//		FLA_DisplayStringLow(0, (UBYTE *)buffer);
//#else
//		FLA_DisplayString1((UBYTE *)buffer);
//#endif
//		FLA_EndBuzzerSound();
//	}
//
//}
#endif

#endif
#pragma section
