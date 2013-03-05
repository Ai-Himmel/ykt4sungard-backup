/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_RAM.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ラムチェックファンクション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mntsw_i.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syslifem.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\mem_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

/* Prototype
void	SF_SRAM_Check(void);
UBYTE	SRAM_Check(UBYTE, UBYTE **, UBYTE *);
UBYTE	SF_SelectStopOrContinue(void);
void	SF_DRAM_Check(void);
UBYTE	DRAM_Check(UBYTE);
UBYTE	DramAreaInput(UBYTE *);
void	DisplayDramInput(UBYTE);
void	DisplayDRAM_Check(UBYTE *);
void	ClearDRAM(void);
*/

/*************************************************************************
	module		:[(工場ファンクション)ＳＲＡＭチェック]
	function	:[
		1.ＨＥＸコードを入力し、ＳＲＡＭのチェックを行う
		2.割り込み禁止にする
		3.SRAMのスタック以外の領域に指定したＨＥＸコードを書き込む
		4.書き込みが終了したら読み出してチェックを行う。
		5.すべてのデータについてチェックが終われば終了
		6.終了したらシステムを再起動する
	]
	return		:[ない]
	common		:[]
	condition	:[]
	comment		:[PRG*B-E]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[96/02/20]
	author		:[松隈]
*************************************************************************/
void SF_SRAM_Check(void)
{
	UBYTE	hexcode;				/* ＨＥＸコード */
	UBYTE	*SRAM_StartAddress;		/* 検査開始アドレス */
	UBYTE	*SRAM_EndAddress;		/* 検査終了アドレス */
	UBYTE	check_step;				/* 検査ｱﾄﾞﾚｽ指定変数 */
	UBYTE	ram_check;				/* ﾃｽﾄ状態(0:ﾁｪｯｸ中,1:ﾁｪｯｸ終了) */
	UBYTE	error_check;			/* エラーチェック変数 */

	check_step = 0;
	hexcode = 0xFF;
	ram_check = 0;
	error_check = 0;

/*	DisplayStringHigh(0,D2W_SF_SRAMCheck);		/** "SRAMチェック"の表示 */

	/* ワンタッチＥを押されてからワンクッション置くように変更 97/08/19 By M.Kuwahara */
	if (ConfirmKeyInputOperation(D2W_SF_SRAMCheck, D2W_EnterStop, ENTER, STOP) != CONFIRM_EXEC) {
		return;
	}

	wai_tsk(100);	/**	アックブザーが鳴り続ける為 1994/7/29 対策by奥村	*/

	/**	割り込み禁止	*/
	CMN_DisableInterrupt();

	while (ram_check == 0) {

		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		ClearDisplayLow();
		CMN_HexToASC(&FunctionDisplayBufferLow[0], (UDWORD)hexcode, 2);
		FunctionDisplayBufferLow[2]  = ':';

		if (error_check == 0) {			/* エラーの時にｱﾄﾞﾚｽを初期化しないため */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/08/28 Y.Matsukuma */
			switch ( check_step ) {
			case 0:
				SRAM_StartAddress = OPR_BKUPRAM1_START;
				SRAM_EndAddress = OPR_BKUPRAM1_END;
				break;
			case 1:
				SRAM_StartAddress = OPR_BKUPRAM2_START;
				SRAM_EndAddress = OPR_BKUPRAM2_END;
				break;
			case 2:
				SRAM_StartAddress = OPR_HIGHSRAM_START;
				SRAM_EndAddress = OPR_HIGHSRAM_END;
				break;
			}
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1998/12/28 */
			switch ( check_step ) {
			case 0:
				SRAM_StartAddress = (UBYTE *)0x00800000L;
				SRAM_EndAddress = (UBYTE *)0x00807FFFL;
				break;
			case 1:
				SRAM_StartAddress = (UBYTE *)0x00D00000L;
				SRAM_EndAddress = (UBYTE *)0x00D1FFFFL;
				break;
			}
#else	/* POPLAR */
			switch ( check_step ) {
			case 0:
				SRAM_StartAddress = (UBYTE *)&SYS_SRAMCheckStartAddress;	/* 97/08/19 By M.Kuwahara */
				SRAM_EndAddress = OPR_BKUPRAM_END;
				break;
			case 1:
				SRAM_StartAddress = OPR_PATJOURNAL_START;
				SRAM_EndAddress = OPR_PATJOURNAL_END;
				break;
			}
#endif
		}

		if (SRAM_Check(hexcode, &SRAM_StartAddress, SRAM_EndAddress) == 0) {  		/* SRAMチェックで異常の時 */
			CMN_StringCopy(&FunctionDisplayBufferLow[3], D2W_SF_NG);
			DisplayStringLow(0, FunctionDisplayBufferLow);	/* 下段表示 */
			error_check = 1;
			if (SF_SelectStopOrContinue() == 0) {		/* 継続 or 終了の選択 */
				ClearDisplayHigh();
				ClearDisplayLow();
				break;
			}
		}
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/08/30 Y.Matsukuma */
		else {
			if (check_step != 2){
				check_step++;
			}
#else
		else {
			if (check_step == 0){
				check_step = 1;
			}
#endif
			else {
				CMN_StringCopy(&FunctionDisplayBufferLow[3], D2W_SF_OK);
				DisplayStringLow(0, FunctionDisplayBufferLow);	/* 下段表示 */
				if ( hexcode == 0x00 ) {	/* 全ての検査が終了した時 */
					ram_check = 1;
				}
				else {
					hexcode -= 0x55;
					check_step = 0;
					error_check = 0;
				}
				wai_tsk(200);	/* 400->200 1997/12/25 Y.Matsukuma */
			}
		}
	}
	RestartSystem();		/* システム再起動 */
}

/*************************************************************************
	module		:[ＳＲＡＭチェック]
	function	:[
		1. ＳＲＡＭにＨＥＸコードを書き込む
		2. ＳＲＡＭを読みだす
		3. 書き込んだＨＥＸコードと読み出したＨＥＸコードが等しいかどうか比較
		4. ＮＧであれば、エラーアドレスとデータを表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/15]
	author		:[松隈]
*************************************************************************/
UBYTE SRAM_Check(UBYTE Code, UBYTE *(*StartAddress), UBYTE *LimitAddress)
{
	UBYTE	EscapeMemory;
	UBYTE	ErrorData;

	/*	ＳＲＡＭ書き込み、読み出し、比較	*/
	for (; (UDWORD)(*StartAddress) <= (UDWORD)(LimitAddress); (*StartAddress)++) {	/** 終了アドレスまでループ */
		EscapeMemory = *(*StartAddress);			/** データの退避 */
		*(*StartAddress) = Code;					/** テストコードの書き込み */
		if (*(*StartAddress) != Code) {				/** 比較の結果、NGの場合 97/10/15 By M.Kuwahara */
			ErrorData = *(*StartAddress);
			*(*StartAddress) = EscapeMemory;		/** 退避したデータの書き戻し */
			/* エラーアドレスを表示 */
			CMN_UnsignedLongToHexASC_NULL(&FunctionDisplayBufferLow[11], (UDWORD)(*StartAddress), 6, ' ');
			/* エラーデータを表示 */
			CMN_HexToASC(&FunctionDisplayBufferLow[18], (UDWORD)ErrorData, 2);
			FunctionDisplayBufferLow[17]  = ':';

			(*StartAddress)++;
			return(0);			/** NGリターン */
		}
		*(*StartAddress) = EscapeMemory;	/** 退避したデータの書き戻し */
	}

	return(1);					/** OKリターン */
}


/*************************************************************************
	module		:[ＳＲＡＭ・ＤＲＡＭチェックの終了継続の選択]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/16]
	author		:[松隈]
*************************************************************************/
UBYTE SF_SelectStopOrContinue(void)
{
	UBYTE	key;

	while( 1 ) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		switch (key) {
		case STOP_KEY:
			return(0); 			/* 終了 */
		case FUNCTION_KEY:		/* 機能キー */
			return(1); 			/* 継続 */
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[DRAMテスト(工場ファンクション)]
	function	:[
		1.予め設定したＨＥＸコードでDRAMのチェックを行う
		2.割り込み禁止にする
		3.DRAM領域に指定したＨＥＸコードを書き込む
		4.書き込みが終了したら読み出してチェックを行う。
		5.すべてのデータについてチェックが終われば終了
		6.終了したらDRAMをクリアする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-F]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/28]
	author		:[松隈,桑原]
*************************************************************************/
void SF_DRAM_Check(void)
{
	UBYTE	DramNo;		/* 選択番号 */
	UBYTE	ret;

	DramNo	= 0;

	DisplayStringHigh(0,D2W_SF_DRAMCheck); 		/** "DRAM Check"の表示 */

	while (1) {
		if (DramAreaInput(&DramNo) == NG) {			/** ＤＲＡＭ拡張エリアチェック */
			return;
		}

		wai_tsk(100);
		/**	割り込み禁止	*/
		CMN_DisableInterrupt();

		if ( SYB_MaintenanceSwitch[MNT_SW_I4] & 0x01 ){
			if (( ret = DRAM_CheckFull( DramNo )) == NG ){		/** DRAMフルチェック */
				return;
			}
		}
		else{
			ret = DRAM_Check( DramNo );				/** DRAMチェック */
		}
		if ( ret == OK ) {
			AckBuzzer();
			wai_tsk( 20 );
			AckBuzzer();
			wai_tsk( 20 );
			AckBuzzer();
			wai_tsk( 200 );
		}
		else{
			NackBuzzer();
		}
		DramNo	= 0;
	}

	InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
	InitializeMachineStatus();									/** マシーンステータスのクリア	*/
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
	SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
	Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
	CMN_EnableInterrupt();										/** 割り込み許可				*/
}

/*************************************************************************
	module		:[ＤＲＡＭチェック]
	function	:[
		1. ＤＲＡＭにＨＥＸコードを書き込む
		2. ＤＲＡＭを読みだす
		3. 書き込んだＨＥＸコードと読み出したＨＥＸコードが等しいかどうか比較
	]
	return		:[ 	1:OK
			   		0:NG
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/16]
	author		:[松隈、桑原]
*************************************************************************/
UBYTE DRAM_Check(UBYTE DramNo)
{
	UBYTE	loop;
	UBYTE	loopt;
	UBYTE	size;				/* 拡張サイズ（Ｍ） */
	UBYTE	dram_chk[5];		/* DRAM状態格納ﾊﾞｯﾌｧ( OK or NG )*/
	UWORD	*DRAM_CheckAddress;	/* 拡張アドレス先頭 */
	UWORD	*addr;				/* データ書込み、読出しアドレス */
	UWORD	data;

	CMN_MemorySet(dram_chk, 5, 0xFF);
	switch( DramNo ){		/* 拡張サイズセット */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/06/16 Y.Matsukuma */
	case	ONETOUCH_A_KEY:
		size	= 2;
		CMN_MemorySet(dram_chk, 1, OK);
		break;
	case	ONETOUCH_B_KEY:
		size	= 4;
		CMN_MemorySet(dram_chk, 2, OK);
		break;
	case	ONETOUCH_C_KEY:
		size	= 6;
		CMN_MemorySet(dram_chk, 3, OK);
		break;
	case	ONETOUCH_D_KEY:
		size	= 10;
		CMN_MemorySet(dram_chk, 5, OK);
		break;
#else
	case	ONETOUCH_01_KEY:
		size	= 2;
		CMN_MemorySet(dram_chk, 1, OK);
		break;
	case	ONETOUCH_02_KEY:
		size	= 4;
		CMN_MemorySet(dram_chk, 2, OK);
		break;
	case	ONETOUCH_03_KEY:
		size	= 6;
		CMN_MemorySet(dram_chk, 3, OK);
		break;
	case	ONETOUCH_04_KEY:
		size	= 10;
		CMN_MemorySet(dram_chk, 5, OK);
		break;
#endif
	}
	for( loop = 0; loop < size; loop += 2 ){		/* 拡張ＤＲＡＭ分 */
		DRAM_CheckAddress = (UWORD *)(MEM_DRAM_START_ADDRESS + ( 0x00100000L * loop ));	/* 各先頭アドレスセット */
		/* 書込み */
		for( loopt = 0; loopt < 10; loopt++ ){		/* テスト件数分 */
			switch( loopt ){						/* テストデータ書込み */
			case	0:
				addr	= DRAM_CheckAddress;
				data	= 0x0000;
				break;
			case	8:
			case	9:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	= (0x5555 << (loopt - 8));
				break;
			default:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	= (0x0101 << loopt);
				break;
			}
			*addr	= data;
		}

		for( loopt = 0; loopt < 10; loopt++ ){	/* テスト件数分 */
			switch( loopt ){					/* テストデータ書込み */
			case	0:
				addr	= DRAM_CheckAddress;
				data	= 0x0000;
				break;
			case	8:
			case	9:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	= (0x5555 << (loopt - 8));
				break;
			default:
				addr	= (UWORD *)((UDWORD)DRAM_CheckAddress + (0x0001 << loopt));
				data	=(0x0101 << loopt);
				break;
			}
			if( *(addr) != data ){
				dram_chk[loop/2]	= NG;
				break;
			}
		}
	}
	DisplayDRAM_Check( dram_chk );			/* ＤＲＡＭ結果表示 */
	for( loop = 0; loop < 5; loop++ ){		/* エラーありか？ */
		if( dram_chk[loop] == 0xff ){
			break;
		}
		if( dram_chk[loop] == NG ){
			return( NG );
		}
	}
	return( OK );
}

/*************************************************************************
	module		:[ＤＲＡＭ拡張エリア選択オペレーション]
	function	:[
		1. ＤＲＡＭ領域（０ｘ１００００００～０ｘ１ＦＦＦＦＦＦ）の内
		   拡張エリアを選択するオペレーション
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/04]
	author		:[松隈、桑原]
*************************************************************************/
UBYTE DramAreaInput(UBYTE *DramNo)
{
	UBYTE key;
	UBYTE keytype;

	while(1) {
		DisplayDramInput( *DramNo );
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ONETOUCH:
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/06/16 Y.Matsukuma */
			if ((key >= ONETOUCH_A_KEY) && (key <= ONETOUCH_D_KEY)) {
				switch (key) {
				case ONETOUCH_A_KEY:	/* 標準ＤＲＡＭ ２Ｍ */
					*DramNo = ONETOUCH_A_KEY;
					break;
				case ONETOUCH_B_KEY:	/* 標準ＤＲＡＭ + 拡張ＤＲＡＭ ２Ｍ */
					*DramNo = ONETOUCH_B_KEY;
					break;
				case ONETOUCH_C_KEY:	/* 標準ＤＲＡＭ + 拡張ＤＲＡＭ ４Ｍ */
					*DramNo = ONETOUCH_C_KEY;
					break;
				case ONETOUCH_D_KEY:	/* 標準ＤＲＡＭ + 拡張ＤＲＡＭ ８Ｍ */
					*DramNo = ONETOUCH_D_KEY;
					break;
				}
			}
#else
			if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_04_KEY)) {
				switch (key) {
				case ONETOUCH_01_KEY:	/* 標準ＤＲＡＭ  ２Ｍ */
					*DramNo = ONETOUCH_01_KEY;
					break;
				case ONETOUCH_02_KEY:	/* 標準ＤＲＡＭ + 一番下の拡張ＤＲＡＭ ２Ｍ */
					*DramNo = ONETOUCH_02_KEY;
					break;
				case ONETOUCH_03_KEY:	/* 標準ＤＲＡＭ + 真ん中の拡張ＤＲＡＭ ４Ｍ */
					*DramNo = ONETOUCH_03_KEY;
					break;

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
				/* HINOKIは拡張DRAMは最大４Ｍまでです。 By O.Kimoto 1999/02/08 */
#else
				case ONETOUCH_04_KEY:	/* 標準ＤＲＡＭ + 一番上の拡張ＤＲＡＭ ８Ｍ */
					*DramNo = ONETOUCH_04_KEY;
					break;
#endif

				}
			}
#endif
			else {
				NackBuzzer();
				break;
			}
			break;
		case START:
			if( *DramNo == 0 ){			/* 選択されていない時 */
				NackBuzzer();
			}
			else{
				return(OK);
			}
			break;
		case STOP:
			return(NG);
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＤＲＡＭ拡張エリア選択オペレーション表示]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/10]
	author		:[桑原]
*************************************************************************/
void	DisplayDramInput( UBYTE	DramNo )
{
	UBYTE	no;			/* 選択番号 */
	UBYTE	size;		/* ＤＲＡＭサイズ */

	switch( DramNo ){
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/06/16 Y.Matsukuma */
	case	ONETOUCH_A_KEY:
		no		= 1;
		size	= 1;
		break;
	case	ONETOUCH_B_KEY:
		no		= 2;
		size	= 2;
		break;
	case	ONETOUCH_C_KEY:
		no		= 3;
		size	= 4;
		break;
	case	ONETOUCH_D_KEY:
		no		= 4;
		size	= 8;
		break;
	default:
		return;
#else
	case	ONETOUCH_01_KEY:
		no		= 1;
		size	= 1;
		break;
	case	ONETOUCH_02_KEY:
		no		= 2;
		size	= 2;
		break;
	case	ONETOUCH_03_KEY:
		no		= 3;
		size	= 4;
		break;
	case	ONETOUCH_04_KEY:
		no		= 4;
		size	= 8;
		break;
	default:
		return;
#endif
	}
	/* "DRAM Check         " */
	DisplayStringHigh(0,D2W_SF_DRAMCheck);
	/* "[01]:8M            " */
	ClearDisplayLow();
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');				/* 下段表示文字列を初期化 */
	if ( size == 1 ) {			/* "1M" -> "MAIN" 97/10/20 By M.Kuwahara */
		FunctionDisplayBufferLow[0]	= 'M';
		FunctionDisplayBufferLow[1]	= 'A';
		FunctionDisplayBufferLow[2]	= 'I';
		FunctionDisplayBufferLow[3]	= 'N';
	}
	else{
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[0], (UWORD)size, 1, '0');
		FunctionDisplayBufferLow[1]	= 'M';
	}
	DisplayStringLow(0,  FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[ＤＲＡＭ拡張チェック表示]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/10]
	author		:[桑原]
*************************************************************************/
void DisplayDRAM_Check(
					UBYTE	*DramCheck )			/* 拡張チェック結果 */
{
	UBYTE	loop;

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');				/* 上段表示文字列を初期化 */
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');				/* 下段表示文字列を初期化 */

	for( loop = 0; loop < 5; loop++ ){				/* 表示最大値分 */
		if( DramCheck[loop] == 0xff ){
			break;
		}
		if( loop == 0 ){							/* MAINの時 */
			FunctionDisplayBufferHigh[0]	= 'M';				/* "M:" */
			FunctionDisplayBufferHigh[1]	= ':';
			if( DramCheck[loop] == OK ){
				FunctionDisplayBufferHigh[2]	= 'O';
				FunctionDisplayBufferHigh[3]	= 'K';
			}
			else{
				FunctionDisplayBufferHigh[2]	= 'N';
				FunctionDisplayBufferHigh[3]	= 'G';
			}
		}
		else{
			if( loop * 7 < 20 ){					/* 上段表示 */
				FunctionDisplayBufferHigh[loop*7]	= 'I';		/* "IC1:" */
				FunctionDisplayBufferHigh[loop*7+1]	= 'C';		/* "IC2:" */
				FunctionDisplayBufferHigh[loop*7+2]	= (UBYTE)(loop + 0x30);
				FunctionDisplayBufferHigh[loop*7+3]	= ':';
				if( DramCheck[loop] == OK ){
					FunctionDisplayBufferHigh[loop*7+4]	= 'O';
					FunctionDisplayBufferHigh[loop*7+5]	= 'K';
				}
				else{
					FunctionDisplayBufferHigh[loop*7+4]	= 'N';
					FunctionDisplayBufferHigh[loop*7+5]	= 'G';
				}
			}
			else{									/* 下段表示 */
				FunctionDisplayBufferLow[(loop-2)*7]	= 'I';	/* "IC3:" */
				FunctionDisplayBufferLow[(loop-2)*7+1]	= 'C';	/* "IC4:" */
				FunctionDisplayBufferLow[(loop-2)*7+2]	= (UBYTE)(loop + 0x30);
				FunctionDisplayBufferLow[(loop-2)*7+3]	= ':';
				if( DramCheck[loop] == OK ){
					FunctionDisplayBufferLow[(loop-2)*7+4]	= 'O';
					FunctionDisplayBufferLow[(loop-2)*7+5]	= 'K';
				}
				else{
					FunctionDisplayBufferLow[(loop-2)*7+4]	= 'N';
					FunctionDisplayBufferLow[(loop-2)*7+5]	= 'G';
				}
			}
		}
	}
	ClearDisplayHigh();
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[ＤＲＡＭチェック（全ＤＲＡＭチェック）]
	function	:[
		1. ＤＲＡＭにＨＥＸコードを書き込む
		2. ＤＲＡＭを読みだす
		3. 書き込んだＨＥＸコードと読み出したＨＥＸコードが等しいかどうか比較
		4. ＮＧであれば、エラーアドレスとデータを表示
			＊大幅に変更	97/10/30 By M.Kuwahara
	]
	return		:[ 	1:OK
			   		0:NG
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/16]
	author		:[松隈、桑原]
*************************************************************************/
UBYTE DRAM_CheckFull(UBYTE DramNo)
{
	UBYTE	loop;
	UBYTE	DRAM_Size;
	UBYTE	*DRAM_CheckAddress;
	UBYTE	error_data;
	UBYTE	area;
	UBYTE	code;
	UDWORD	loopt;

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/06/16 Y.Matsukuma */
	switch( DramNo ){		/* 拡張サイズセット */
	case	ONETOUCH_A_KEY:
	case	ONETOUCH_B_KEY:
	case	ONETOUCH_C_KEY:
	case	ONETOUCH_D_KEY:
		/* 標準DRAM2M */
		area = (DramNo - ONETOUCH_A_KEY) * 2;
		if (area == 6) {
			DRAM_Size = 4;
		}
		else {
			DRAM_Size = 2;
		}
		break;
	}
#else	/* POPLAR */
 /*#if (PRO_DRAM_SIZE == DRAM_2M)		* 1998/05/15 By M.Kuwahara */
	switch( DramNo ){		/* 拡張サイズセット */
	case	ONETOUCH_01_KEY:
		area	= 0;
		break;
	case	ONETOUCH_02_KEY:
		area	= 2;
		break;
	case	ONETOUCH_03_KEY:
		area	= 4;
		break;
	case	ONETOUCH_04_KEY:
		area	= 6;
		break;
	}

	if (area == 6) {
		DRAM_Size = 4;
	}
	else {
		DRAM_Size = 2;
	}
 /*#else*/
 #if(0)/*By Y.Suzuki 1998/05/18*/
**	switch( DramNo ){		/* 拡張サイズセット */
**	case	ONETOUCH_01_KEY:
**		area	= 0;
**		DRAM_Size = 1;
**		break;
**	case	ONETOUCH_02_KEY:
**		area	= 1;
**		DRAM_Size = 2;
**		break;
**	case	ONETOUCH_03_KEY:
**		area	= 3;
**		DRAM_Size = 2;
**		break;
**	case	ONETOUCH_04_KEY:
**		area	= 5;
**		DRAM_Size = 4;
**		break;
**	}
 #endif
 /*#endif*/
#endif

#if (PRO_DRAM_SIZE == DRAM_2M)		/* By Y.Suzuki 1998/05/18 */
	DRAM_CheckAddress = (UBYTE *)(MEM_DRAM_START_ADDRESS + ( 0x00100000L * area ));	/* 各先頭アドレスセット */
#else
	DRAM_CheckAddress = (UBYTE *)(MEM_DRAM_CHECK_START_ADDRESS + ( 0x00100000L * area ));	/* 各先頭アドレスセット */
#endif
	DRAM_Size = (UBYTE)(DRAM_Size * 16);
	code = 0xFF;

	while(1) {
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		ClearDisplayLow();
		CMN_HexToASC(&FunctionDisplayBufferLow[0], (UDWORD)code, 2);
		FunctionDisplayBufferLow[2]  = ':';
		DisplayStringLow(0, FunctionDisplayBufferLow);	/* 下段表示 */
		/**	ＤＲＡＭに書き込む	*/
		for (loop = 0; loop < DRAM_Size; loop++) {
			for (loopt = 0; loopt < 0x10000; loopt++) {					/*	0<loopt<64k	*/
				*(DRAM_CheckAddress + (loop * 0x10000) + loopt ) = code;
			}
		}

		/**	ＤＲＡＭから読みだして比較	*/
		for (loop = 0; loop < DRAM_Size; loop++) {
			for (loopt = 0; loopt < 0x10000; loopt++) {						/*	0<loopt<64k	*/
				if (*(DRAM_CheckAddress + (loop * 0x10000) + loopt) != code) {
					/* エラーアドレスを表示 */
					CMN_UnsignedLongToHexASC_NULL(&FunctionDisplayBufferLow[10],
												  (UDWORD)(DRAM_CheckAddress + (loop * 0x10000) + loopt),
												  7, '0');
					error_data = (UBYTE)*(DRAM_CheckAddress + (loop * 0x10000) + loopt);
					/* エラーデータを表示 */
					CMN_HexToASC(&FunctionDisplayBufferLow[18], error_data, 2);
					FunctionDisplayBufferLow[17]  = ':';
					CMN_StringCopy(&FunctionDisplayBufferLow[3], D2W_SF_NG);
					DisplayStringLow(0, FunctionDisplayBufferLow);	/* 下段表示 */
					if (SF_SelectStopOrContinue() == 0) {					/* 継続 or 終了の選択 */
						return(NG);
					}
					ClearDisplayLow();
				}
			}
		}
		CMN_StringCopy(&FunctionDisplayBufferLow[3], D2W_SF_OK);
		DisplayStringLow(0, FunctionDisplayBufferLow);	/* 下段表示 */
		wai_tsk(200);	/* 400->200 1997/12/25 Y.Matsukuma */
		if (code == 0x00) { /* ここで判断します 1997/12/05 Y.Matsukuma */
			break;
		}
		code -= 0x55;
	}
	ClearDisplayLow();
	return(OK);	/* OK */
}

/*************************************************************************
	module		:[ＤＲＡＭクリア]
	function	:[
		1. ＤＲＡＭをクリアする
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/30]
	author		:[渡辺一章]
*************************************************************************/
void ClearDRAM(void)
{
#if defined(POPLAR_F)	/* 2000/03/01 Y.Murata */
	/* パワーＯＮ時のウォームアップ中は、キー操作禁止 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON) {
		NackBuzzer();
		return;
	}
#endif

	switch (ConfirmKeyInputOperation(D2W_SF_ClearDRAM, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
	case CONFIRM_EXEC:
		/* 動作上の問題は特に無いですが、KANJIに合わせて、機器動作中は弾きます by K.Watanabe 1998/12/04 */
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & ~SYS_PANEL_BUSY) {	/** 機器動作中 */
			NackBuzzer();
		}
		else {
			InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
			InitializeMachineStatus();									/** マシーンステータスのクリア	*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
			SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
			Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
			InitializeSensor();											/** センサーを初期化			*/
			ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
		}
		break;
	case CONFIRM_ABORT:
	case OPR_END:
		break;
	default:
		break;
	}
}
