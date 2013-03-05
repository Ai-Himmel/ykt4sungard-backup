/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : fla_main.c                                               */
/*  作成者       : 桑原美紀                                                 */
/*  日  付       : 1997/04/24                                               */
/*  概  要       : フラッシュメモリへのコマンド発行                         */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\flash\define\fla_pro.h"
#include	"\src\atlanta\flash\define\fla_def.h"
#include	"\src\atlanta\flash\ext_v\fla_tbl.h"
#include	"\src\atlanta\flash\define\sys_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\flash\ext_v\rom_tbl.h"	/* 1998/08/06 Y.Murata */

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/11 Y.Murata */
	#include	"\src\atlanta\flash\ext_v\sys_data.h"
	#include  "\src\atlanta\sh7043\define\sh_port.h"
#endif

#if (PRO_NEW_JIG == ENABLE)		/* 2002/06/04 T.Takagi */
#include	"\src\atlanta\flash\define\jig_led.h"
#include	"\src\atlanta\flash\ext_v\sys_data.h"
#endif

CONST UBYTE Title_Msg[]			= "Flash Mem Write Prog";
CONST UBYTE OK_Msg[]			= " OK         SUM:    ";
CONST UBYTE RomSum_Msg[]		= " ROM0:     ROM1:    ";
CONST UBYTE NG_AutoSelect_Msg[]	= " ID Read Error      ";
CONST UBYTE NG_ChipErase_Msg[]	= " Chip Erase Error   ";
CONST UBYTE NG_SectorErase_Msg[]= " Sector Erase Error ";
CONST UBYTE NG_Program_Msg[]	= " Write Error        ";
CONST UBYTE NG_SumCheck_Msg[]	= " Sum Check Error    ";
CONST UBYTE NG_TimeOver_Msg[]	= " Time Over Error    ";
CONST UBYTE Erasing_msg[]		= " Erasing...         ";
#if (1)
CONST UBYTE Test1[]				= " Test1              ";
CONST UBYTE Test2[]				= " Test2              ";
CONST UBYTE Test3[]				= " Test3              ";
CONST UBYTE Test4[]				= " Test4              ";
CONST UBYTE Test5[]				= " Test5              ";
CONST UBYTE Test6[]				= " Test6              ";
#endif
CONST UBYTE SectorNumber_msg[19][21] =   {".................. 0",
										">................. 1",
										">>................ 2",
										">>>............... 3",
										">>>>.............. 4",
										">>>>>............. 5",
										">>>>>>............ 6",
										">>>>>>>........... 7",
										">>>>>>>>.......... 8",
										">>>>>>>>>......... 9",
										">>>>>>>>>>........10",
										">>>>>>>>>>>.......11",
										">>>>>>>>>>>>......12",
										">>>>>>>>>>>>>.....13",
										">>>>>>>>>>>>>>....14",
										">>>>>>>>>>>>>>>...15",
										">>>>>>>>>>>>>>>>..16",
										">>>>>>>>>>>>>>>>>.17",
										">>>>>>>>>>>>>>>>>>18"};

CONST UBYTE	DEBUG_FlashCheck = 0;
CONST UBYTE CheckTitle_Msg[]	= "Flash Mem Check     ";
CONST UBYTE CheckNG_Msg[]		= "Address  Flash EPROM";
/*CONST UBYTE CheckNGL_Msg[]	= "xxxxxx   xxxx  xxxx ";*/
CONST UBYTE CheckErr_Msg[]		= "Verify Error:       ";
CONST UBYTE CheckCnt_Msg[]		= "        xxxxxx Words";

#if (PRO_NEW_JIG == ENABLE)	/* 2002/06/05 T.Takagi */
static UBYTE	CheckFlashDeviceCode(UWORD	manufacture_code, UWORD device_code);	/* 2001/07/04 M.iida */
#endif

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
	UWORD	sum;
	UWORD	rom0_sum;
	UWORD	rom1_sum;
	UBYTE	buffer[OPR_DISPLAY_MAX+1];
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
	UWORD	rom_no;
	UWORD	save_rom_no;

	for (sum = 0; sum < 6; sum++) {
		RomCheckSum[sum] = 0x0000;
	}

#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/11 Y.Murata */
	UDWORD	counter;
	UBYTE	dummy;
#endif
	if (DEBUG_FlashCheck) {
		FlashMemoryCheck();
		return;
	}

	IO_Port_Initialize();

#if defined(SAKAKI)	/* 1999/10/18 H.Yoshikawa */
/*	InitializeGateArray(); */
#endif

#if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
	LCD_Initialize();
	InitializeGateArray();
#else
	SCN_Init();
	LCD_Initialize();
#endif

#if (PRO_PANEL == ANK)
	DisplayStringHigh(0, (UBYTE *)Title_Msg);
#else
	DisplayString0((UBYTE *)Title_Msg);
#endif


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/11 Y.Murata */
	SYS_COM_PortStatus = IO_BIT_CURV1;
	outpw(COM_PORT,SYS_COM_PortStatus);

	for (counter = 0; counter < 0x0000FFFF; counter++) {
		dummy++;
	}

	SYS_COM_PortStatus &= ~IO_BIT_CURV1;
	outpw(COM_PORT,SYS_COM_PortStatus);
#endif

#if (PRO_NEW_JIG == ENABLE)		/* YAWARAより移植 2002/06/04 T.Takagi */

	/* FLASH_MEM = RomDstTable[0].Adrs; */

	for (sum = 0; sum < JIG_LED_MAX; sum++) {
		JIG_SumCheckOnLed(0x0000, sum);		/* 0:0000、1:0000 を表示 */
	}

	for (sum = 0; sum < JIG_LED_MAX; sum++) {
		JIG_ReadWriteOnLed(sum, 1);	/* ROM指定、ドットLED ON */
	}
#endif

	result = PASS_FLAG;
	result = Main_Function();

	switch (result) {
	case	PASS_FLAG:	/* 正常終了 */
#if (PRO_NEW_JIG == ENABLE)		/* NEW_JIG 2002/06/12 T.Takagi */
		buffer[OPR_DISPLAY_MAX]	= 0x00;
		sum = GetWordSumCheck( &rom0_sum, &rom1_sum );	/* 合計SUM計算、書込みデータ取得 */
		CMN_StringCopy(buffer, OK_Msg);		/* " OK        SUM:XXXX" */
		buffer[OPR_DISPLAY_MAX]	= 0x00;
		CMN_HexToASC(&buffer[16], (UDWORD)sum, 4);
 #if (PRO_PANEL == ANK)
		DisplayStringHigh(0, (UBYTE *)buffer);
 #else
		DisplayString0((UBYTE *)buffer);
 #endif
		CMN_StringCopy(buffer, RomSum_Msg);		/* " ROM0:XXXX ROM1:XXXX" */
		CMN_HexToASC(&buffer[6], (UDWORD)RomCheckSum[ROM_NUMBER0], 4);
		CMN_HexToASC(&buffer[16], (UDWORD)RomCheckSum[ROM_NUMBER1], 4);
 #if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)buffer);
 #else
		DisplayString0((UBYTE *)buffer);
 #endif
		EndBuzzerSound();
		save_rom_no = RomNumber;	/* Init. */
		rom_no = RomNumber - 2;	/* Last ROM Number */
		while (1) {
			if (save_rom_no != rom_no) {
				save_rom_no = rom_no;
				/* SumCheck Display */
				JIG_SumCheckOnLed(RomCheckSum[rom_no], rom_no);		/* ROM0/ROM2/CGROM0 */
				JIG_SumCheckOnLed(RomCheckSum[rom_no+1], rom_no+1);	/* ROM1/ROM3/CGROM1 */
			}
 #if 0	/* AtlantaはCGROMなし */
 //			if (JIG_CheckDisplayROM_Switch()) {	/* SW-ON検出した場合 */
 //				rom_no += 2;
 //				if (RomNumber > CGROM_NUMBER0) {	/* CGROMも書き換えた場合 */
 //					if (rom_no > CGROM_NUMBER1) {
 //						rom_no = ROM_NUMBER0;
 //					}
 //				} else {
 //					if (rom_no > ROM_NUMBER3) {
 //						rom_no = ROM_NUMBER0;
 //					}
 //				}
 //			}
 #endif
		}
#else 	/* OLD_JIG 白樺用梱包状態で書き換え可能治具以外 */
     /*	sum = GetWordSumCheck(); */			/* 書込みデータ取得 */
		sum = GetWordSumCheck( &rom0_sum, &rom1_sum );	/* 書込みデータ取得 */
		CMN_StringCopy(buffer, OK_Msg);		/* " OK        SUM:XXXX" */
		buffer[OPR_DISPLAY_MAX]	= 0x00;
		CMN_HexToASC(&buffer[16], (UDWORD)sum, 4);
     /*	DisplayStringLow(0, (UBYTE *)buffer); */

 #if (PRO_PANEL == ANK)
		DisplayStringHigh(0, (UBYTE *)buffer);
 #else
		DisplayString0((UBYTE *)buffer);
 #endif

		CMN_StringCopy(buffer, RomSum_Msg);	/* " ROM0:XXXX ROM1:XXXX" */
		CMN_HexToASC(&buffer[6], (UDWORD)rom0_sum, 4);
		CMN_HexToASC(&buffer[16], (UDWORD)rom1_sum, 4);

 #if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)buffer);
 #else
		DisplayString1((UBYTE *)buffer);
 #endif
		EndBuzzerSound();
#endif /* end of (PRO_NEW_JIG == ENABLE) */

		break;
	case	ERROR_FLAG_AUTOSELECT:	/* メーカーＩＤ読み出しエラー */
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_AutoSelect_Msg);
#else
		DisplayString1((UBYTE *)NG_AutoSelect_Msg);
#endif
		ErrorAlarmSound();
		break;
	case	ERROR_FLAG_CHIP_ERASE:	/* チップ消去エラー */
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_ChipErase_Msg);
#else
		DisplayString1((UBYTE *)NG_ChipErase_Msg);
#endif
		ErrorAlarmSound();
		break;
	case	ERROR_FLAG_SECTOR_ERASE:	/* セクタ消去エラー */
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_SectorErase_Msg);
#else
		DisplayString1((UBYTE *)NG_SectorErase_Msg);
#endif
		ErrorAlarmSound();
		break;
	case	ERROR_FLAG_TIMEOVER:	/* 時間切れエラー */
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_TimeOver_Msg);
#else
		DisplayString1((UBYTE *)NG_TimeOver_Msg);
#endif
		ErrorAlarmSound();
		break;
	case	ERROR_FLAG_PROGRAM:		/* 書き込みエラー */
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_Program_Msg);
#else
		DisplayString1((UBYTE *)NG_Program_Msg);
#endif
		ErrorAlarmSound();
		break;
	case	ERROR_FLAG_SUMCHECK:	/* サムチェックエラー */
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_SumCheck_Msg);
#else
		DisplayString1((UBYTE *)NG_SumCheck_Msg);
#endif
		ErrorAlarmSound();
		break;
	default:
#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
		JIG_ErrorOnLed(RomNumber, result);
#endif
		ErrorAlarmSound();
		break;
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
#if (PRO_NEW_JIG == ENABLE) 	/* YAWARAより移植 2002/06/03 T.Takagi */
UBYTE Main_Function( void )
{
	UBYTE	ret;
	UBYTE	sector_cnt;				/* ｾｸﾀｶｳﾝﾀ */
	UBYTE	sector_start;			/* スタートセクタ */
	UBYTE	sector_end;				/* 各ROMのエンドセクタ */
	UWORD	manufacture_code;		/* ﾏﾆｭﾌｧｸﾁｬｺｰﾄﾞ */
	UWORD	device_code;			/* ﾃﾞﾊﾞｲｽｺｰﾄﾞ */
	UWORD	data;					/* 書込みﾃﾞｰﾀ */
	UWORD	*flash_addr;			/* 書込みｱﾄﾞﾚｽ */
	UWORD	*master_addr;			/* ﾒｲﾝROM側ｱﾄﾞﾚｽ */
	UDWORD	word_cnt;				/* 1ｾｸﾀ内のｶｳﾝﾀ */
	UBYTE	rom_end_number;

	RomNumber = 0;		/* ErrorROM番号記録用 */
	master_addr = (UWORD *)JIG_MASTER_MEM;
	rom_end_number = ROM_NUMBER1;	/* ROM1で最後 */
 #if 0 /* AtlantaではCGROMなし 2002/06/12 T.Takagi */
 //	if (JIG_CheckIsCGROM() && (CGROM_ENABLE == 1)) {		/* CGROMまで書き換えるかチェック */
 //		rom_end_number = CGROM_NUMBER1;
 //	}
 #endif
 
	while (1) {
		if ((RomNumber == ROM_NUMBER0) || (RomNumber == CGROM_NUMBER0)) {
			Autoselect_Function( &manufacture_code, &device_code );		/* カードの検知 */
			if (!CheckFlashDeviceCode(manufacture_code, device_code)) {
				return( ERROR_FLAG_AUTOSELECT );
			}
		}

 #if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)Erasing_msg);	/**Add By M.Kotani 1997/08/06*/
 #else
		DisplayString1((UBYTE *)Erasing_msg);
 #endif

		switch (RomNumber) {
		case ROM_NUMBER0:
	/*	case CGROM_NUMBER0: */
			sector_start = 0;
			sector_end = SECTOR_ROM1;
			break;
		case ROM_NUMBER1:
	/*	case CGROM_NUMBER1: */
			sector_start = SECTOR_ROM1;
			sector_end = SECTOR_MAX;	/* ROM1で最後 */
			break;
 #if 0 /* AtlantaではROM1まで */
 //		case ROM_NUMBER2:
 //			sector_start = SECTOR_ROM2;
 //			sector_end = SECTOR_ROM3;
 //			break;
 //		case ROM_NUMBER3:
 //		default:
 //			sector_start = SECTOR_ROM3;
 //			sector_end = SECTOR_MAX;
 //			break;
 #else
 		default:
			sector_start = SECTOR_ROM1;
			sector_end = SECTOR_MAX;	/* ROM1で最後 */
			break;
 #endif
		}
		for( sector_cnt = sector_start; sector_cnt < SECTOR_MAX; sector_cnt++ ){
			if (sector_cnt >= sector_end) {
				break;
			}
			if( SYS_RomMap[sector_cnt].Status == NOT_ROM_USE ){		/* 未使用の時 */
				continue;
			}
			if (sector_cnt % 2) {
				JIG_ReadWriteOnLed(RomNumber, 1);	/* ROM指定、ドットLED ON */
			} else {
				JIG_ReadWriteOnLed(RomNumber, 0);	/* ROM指定、ドットLED OFF */
			}
			while (1) {
				/* ATHENS_HでFlashROMの消去時間が基板によって1分30秒～2分30秒とばらつきがあり,大分から */
				/* 製造ラインが組めないと指摘されています.原因はFlashROMに消去コマンドを送ってから */
				/* 消去が終了するまでの時間が基板によって異なっている為です by J.Kishida 00/08/22 */
				/* オーバイレーズ修正完了－＞再度、同じセクタ消去動作を行います */
				if ((ret = Sector_Erase_Function((UWORD *)(SYS_RomMap[sector_cnt].StartAddress+FLASH_MEM)))
					!= PASS_FLAG) {
					/**	消去不可－＞オーバイレーズ状態だった、オーバイレーズ是正処理	*/
					if (OverErase_Function((UWORD *)SYS_RomMap[sector_cnt].StartAddress,
							(UDWORD)SYS_RomMap[sector_cnt].Size) != PASS_FLAG) { /*オーバイレーズ処理実行*/
						return (ERROR_FLAG_SECTOR_ERASE);	/** 復旧せず(フラッシュ破壊している可能性あり）*/
					}
					/* オーバイレーズ修正完了－＞再度、同じセクタ消去動作を行います */
				}
				else {
					break;	/* 次のセクタ消去処理に移ります */
				}
			}
		}

		for( sector_cnt = sector_start; sector_cnt < SECTOR_MAX; sector_cnt++ ){
			if (sector_cnt >= sector_end) {
				break;
			}
			if( SYS_RomMap[sector_cnt].Status == NOT_ROM_USE ){		/* 未使用の時 */
				continue;
			}
 #if (PRO_PANEL == ANK)
			DisplayStringLow(0, (UBYTE *)(&SectorNumber_msg[sector_cnt][0]));	/**Add By M.Kotani 1997/08/06*/
 #else
			DisplayString1((UBYTE *)&SectorNumber_msg[sector_cnt][0]);
 #endif
			if (sector_cnt % 2) {
				JIG_ReadWriteOnLed(RomNumber, 1);	/* ROM指定、ドットLED ON */
			} else {
				JIG_ReadWriteOnLed(RomNumber, 0);	/* ROM指定、ドットLED OFF */
			}
			flash_addr = (UWORD *)SYS_RomMap[sector_cnt].StartAddress;
			for( word_cnt = 0; word_cnt < (UDWORD)SYS_RomMap[sector_cnt].Size; word_cnt	+= 2 ){
				data = *master_addr;
				if(( ret = Program_Function( flash_addr, data )) != PASS_FLAG ){	/* ﾃﾞｰﾀの書込み */
					if( ret == FAIL_FLAG ){
						return( ERROR_FLAG_PROGRAM );
					}else{
						return( ret );
					}
				}
				RomCheckSum[RomNumber] += data;
				master_addr ++;
				flash_addr ++;
			}
		}
		if (JIG_GetSumCheck(sector_start, sector_end) != RomCheckSum[RomNumber]) {
			return( ERROR_FLAG_SUMCHECK );
		}
		JIG_SumCheckOnLed(RomCheckSum[RomNumber], RomNumber);

		if (++RomNumber > rom_end_number) {
			return( PASS_FLAG );
		}
 #if 0 /* AtlangtaではCGROMなし 2002/06/12 T.Takagi */
 //		if (RomNumber == CGROM_NUMBER0) {
 //			FLASH_MEM = RomDstTable[3].Adrs; 	/* For CG-ROM */
 //		}
 #endif
	}
}
#else
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
	DisplayStringLow(0, (UBYTE *)Erasing_msg);	/**Add By M.Kotani 1997/08/06*/
#else
	DisplayString1((UBYTE *)Erasing_msg);
#endif

#if (0) /* オーバイレーズ機能対応のため、消去方法をセクタ単位の消去に変更します 1998/04/14 by T.Soneoka */
**	if((ret = Chip_Erase_Function()) != PASS_FLAG ){			/* 全セクタ消去 */
**		if( ret == FAIL_FLAG ){
**			return( ERROR_FLAG_CHIP_ERASE );
**		}else{
**			return( ret );
**		}
**	}
#else

	for( sector_cnt = 0; sector_cnt < SECTOR_MAX; sector_cnt++ ){
		if( SYS_RomMap[sector_cnt].Status == NOT_ROM_USE ){		/* 未使用の時 */
			continue;
		}
		while (1) {
			/* オーバイレーズ修正完了－＞再度、同じセクタ消去動作を行います */
			if ((ret = Sector_Erase_Function((UWORD *)(SYS_RomMap[sector_cnt].StartAddress+FLASH_MEM))) != PASS_FLAG) {
				/**	消去不可－＞オーバイレーズ状態だった、オーバイレーズ是正処理	*/
				if (OverErase_Function((UWORD *)SYS_RomMap[sector_cnt].StartAddress,
				                       (UDWORD)SYS_RomMap[sector_cnt].Size) != PASS_FLAG) {	/* オーバイレーズ処理実行 */
					return (ERROR_FLAG_SECTOR_ERASE);	/** 復旧せず（フラッシュ破壊している可能性あり） */
				}
				/* オーバイレーズ修正完了－＞再度、同じセクタ消去動作を行います */
			}
			else {
				break;	/* 次のセクタ消去処理に移ります */
			}
		}
	}
#endif

	master_addr = (UWORD *)MASTER_MEM;
	data = *master_addr;
	main_sum = 0;
	for( sector_cnt = 0; sector_cnt < SECTOR_MAX; sector_cnt++ ){
		if( SYS_RomMap[sector_cnt].Status == NOT_ROM_USE ){		/* 未使用の時 */
			continue;
		}
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)(&SectorNumber_msg[sector_cnt][0]));	/**Add By M.Kotani 1997/08/06*/
#else
		DisplayString1((UBYTE *)&SectorNumber_msg[sector_cnt][0]);
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

	/*	if( GetWordSumCheck() != main_sum ){	/* 書込みデータチェック */
	if( GetWordSumCheck( &rom0_sum, &rom1_sum ) != main_sum ){	/* 書込みデータチェック */
		return( ERROR_FLAG_SUMCHECK );
	}
/****** テストの為に入れてみる ********/
#if (0)
	if((ret = Sector_Erase_Function( (UWORD *)(SYS_RomMap[0].StartAddress+FLASH_MEM) )) != PASS_FLAG){
		if( ret == FAIL_FLAG ){
			return( ERROR_FLAG_SECTOR_ERASE );
		}else{
			return( ret );
		}
	}
#endif
/**************************************/
	return( PASS_FLAG );
}
#endif /* end of (PRO_NEW_JIG == ENABLE) */

/*************************************************************************
	module		:[フラッシュメモリのベリファイ]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[1997/08/20]
	author		:[橘正樹]
*************************************************************************/
void	FlashMemoryCheck(void)
{
	UBYTE	buffer[OPR_DISPLAY_MAX+1];
	UWORD	manufacture_code;		/* ﾏﾆｭﾌｧｸﾁｬｺｰﾄﾞ */
	UWORD	device_code;			/* ﾃﾞﾊﾞｲｽｺｰﾄﾞ */
	UWORD	*flash_addr;			/* ﾌﾗｯｼｭｱﾄﾞﾚｽ */
	UWORD	*flash_end_addr;		/* ﾌﾗｯｼｭｱﾄﾞﾚｽ */
	UWORD	*master_addr;			/* ﾒｲﾝROM側ｱﾄﾞﾚｽ */
	UWORD	sum;
	UWORD	rom0_sum;
	UWORD	rom1_sum;
	UDWORD	error_count;

	IO_Port_Initialize();
	SCN_Init();
	LCD_Initialize();

#if (PRO_PANEL == ANK)
	DisplayStringHigh(0, (UBYTE *)CheckTitle_Msg);
#else
	DisplayString0((UBYTE *)CheckTitle_Msg);
#endif

	Autoselect_Function( &manufacture_code, &device_code );		/* カードの検知 */
	if(( manufacture_code != 0x0004 ) ||			/* 正しくｾｯﾄされているか */
	   ( device_code != 0x2258 )){
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)NG_AutoSelect_Msg);	/* メーカーＩＤ読み出しエラー */
#else
		DisplayString1((UBYTE *)NG_AutoSelect_Msg);
#endif
		ErrorAlarmSound();
		return;
	}

	master_addr		= (UWORD *)MASTER_MEM;
	flash_addr		= (UWORD *)FLASH_MEM;
	flash_end_addr	= (UWORD *)(FLASH_MEM + 0x100000L);	/* 8Mbit */
	error_count = 0;

	while (flash_addr < flash_end_addr) {
		if (*master_addr != *flash_addr) {
			error_count++;
			if (DEBUG_FlashCheck == 2) {
				CMN_MemorySetNULL(buffer, OPR_DISPLAY_MAX, ' ');
				CMN_HexToASC(&buffer[0], (UDWORD)flash_addr, 6);
				CMN_HexToASC(&buffer[9], (UDWORD)*flash_addr, 4);
				CMN_HexToASC(&buffer[15], (UDWORD)*master_addr, 4);
#if (PRO_PANEL == ANK)
				DisplayStringHigh(0, (UBYTE *)CheckNG_Msg);
				DisplayStringLow(0, (UBYTE *)buffer);
#else
				DisplayString0((UBYTE *)CheckNG_Msg);
				DisplayString1((UBYTE *)buffer);
#endif
				NackBuzzerSound();
				/*wait_timer(100);*/
			}
		}
		master_addr++;
		flash_addr++;
	}

	if (error_count) {
		CMN_StringCopy(buffer, CheckCnt_Msg);		/* "        xxxxxx Words" */
		buffer[OPR_DISPLAY_MAX]	= 0x00;
		CMN_UnsignedLongToASC(&buffer[8], (UDWORD)error_count, 6, ' ');
#if (PRO_PANEL == ANK)
		DisplayStringHigh(0, (UBYTE *)CheckErr_Msg);
		DisplayStringLow(0, (UBYTE *)buffer);
#else
		DisplayString0((UBYTE *)CheckErr_Msg);
		DisplayString1((UBYTE *)buffer);
#endif
		ErrorAlarmSound();
	}
	else {
		sum = GetWordSumCheck( &rom0_sum, &rom1_sum );	/* 書込みデータ取得 */
		CMN_StringCopy(buffer, OK_Msg);		/* " OK        SUM:XXXX" */
		buffer[OPR_DISPLAY_MAX]	= 0x00;
		CMN_HexToASC(&buffer[16], (UDWORD)sum, 4);
#if (PRO_PANEL == ANK)
		DisplayStringHigh(0, (UBYTE *)buffer);
#else
		DisplayString0((UBYTE *)buffer);
#endif

		CMN_StringCopy(buffer, RomSum_Msg);	/* " ROM0:XXXX ROM1:XXXX" */
		CMN_HexToASC(&buffer[6], (UDWORD)rom0_sum, 4);
		CMN_HexToASC(&buffer[16], (UDWORD)rom1_sum, 4);
#if (PRO_PANEL == ANK)
		DisplayStringLow(0, (UBYTE *)buffer);
#else
		DisplayString1((UBYTE *)buffer);
#endif
		EndBuzzerSound();
	}

}

#if (PRO_NEW_JIG == ENABLE)	/* YAWARAより移植 2002/06/04 T.Takagi */
/*************************************************************************
	module		:[フラッシュメモリのマニファクチャコード、デバイスコードのチェック]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FLASH]
	date		:[2001/07/03]
	author		:[飯田雅浩]
*************************************************************************/
static UBYTE	CheckFlashDeviceCode(UWORD	manufacture_code,		/* ﾏﾆｭﾌｧｸﾁｬｺｰﾄﾞ */
									UWORD	device_code)			/* ﾃﾞﾊﾞｲｽｺｰﾄﾞ */
{
	struct FlashDev_t *pntr;
	
	for (pntr = FlashDeviceCode; ;pntr++) {
		if ((pntr->ManufactureCode == manufacture_code)
			&& (pntr->DeviceCode == device_code)) {
			return(1);
		}
		if ((pntr->ManufactureCode == 0x0000)
			&& (pntr->DeviceCode == 0x0000)) {
			return(0);
		}
	}
}
#endif
