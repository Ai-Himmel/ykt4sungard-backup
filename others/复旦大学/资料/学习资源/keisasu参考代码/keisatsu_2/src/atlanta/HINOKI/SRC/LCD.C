/************************************************************************
*	System		: ＥＶＡ
*	File Name	: lcd20_2.c
*	Author		: 石橋正俊
*	Date		: 1997/10/24
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤ(２０文字１行用)ドライバモジュール
*	Maintenance	: \prj\eva\src\lcd.cからコピーし、ＨＩＮＯＫＩ用にメンテしました  1998/09/22 by T.Soneoka
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\opr\ank\define\opr_def.h"
#include "\src\atlanta\opr\ank\define\opr_pro.h"

#include "\src\atlanta\opr\ank\ext_v\opr_data.h"
#include "\src\atlanta\opr\ank\ext_v\opr_tbl.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\ext_v\sys_port.h"

#if 0 /* defined (HINOKI2) */	/* LCDドライバ変更対応　2002/05/15 T.Takagi */
// #include "\src\atlanta\ext_v\sys_data.h"
// #include "\src\atlanta\define\mon_pro.h"
#endif

void SetCGRAM(void);
/*
**	指定時間ループし、Waitするルーチン。
**	CPUパワーを放さないため、他タスクが動作しないくて良い場合のみ使用すること。
**	実測:10000:16ms、9000:15ms、6000:10ms、500:1ms
*/
void	WaitSoftWareTimer(UWORD time)
{
	while (time > 0) {
		time--;
	}
}

/*************************************************************************
	module		:[インストラクション発行]
	function	:[ＬＣＤコントローラにインストラクション(コマンド)を発行]
	return		:[]
	common		:[PortEStatus]
	comment		:[]
*************************************************************************/
void LCD_WriteInstruction(UBYTE instruction)
{
	while(!(Input(SCI_SSR0) & SSR_TDRE));		/* TDRE = 1 ? */
	Output(SCI_TDR0, instruction);
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE));

	while (!(Input(SCI_SSR0) & SSR_TEND));
	/* LE -> 1 */
	LcdDriverClockOn();
	/* LE -> 0 */
	LcdDriverClockOff();
}

/*************************************************************************
	module		:[ＬＣＤ初期化]
	function	:[]
	return		:[]
	common		:[]
	comment		:[]
*************************************************************************/
void	LCD_Initialize(void)
{

#if 0 /* defined (HINOKI2) */  /* LCD表示ずれる件調査用 2003/01/17 T.Takagi */
	UBYTE debug;
#endif

#if 0 /* defined (HINOKI2) */	/* 2002/05/15 LCDドライバ変更対応 */
	SYS_IsCGRAM_Writing = FALSE;
	SYS_IsDisplayingLCD = FALSE;
#endif


	Output(SCI_SCR0,SCR_TE);	/* SCI送信のみに設定 */

	/* 15msec以上待つ */
	WaitSoftWareTimer(10000);	/* 約16msec(10000) */

	/*------------------------*/
	/* ファンクションセット１ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	/* 4,1msec以上待つ */
	WaitSoftWareTimer(6000);	/* 約10msec(6000) */

	/*------------------------*/
	/* ファンクションセット２ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	/* 100usec以上待つ */
	WaitSoftWareTimer(500);		/* 約1msec(500) */

	/*------------------------*/
	/* ファンクションセット３ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	/* 15msec以上待つ */
	WaitSoftWareTimer(9000);	/* 約14msec(9000) */

	/*------------------------*/
	/* ファンクションセット４ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	WaitSoftWareTimer(500);		/* 約1msec(500) */

	/*----------------------*/
	/* 表示ＯＦＦ 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_DISPLAY_OFF);

	WaitSoftWareTimer(500);		/* 約1msec(500) */

	/*----------------------*/
	/* 表示クリア 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);

	WaitSoftWareTimer(500);			/* 約1msec(500) */

	/*----------------------*/
	/* エントリーモードセット */
	/*----------------------*/
	LCD_WriteInstruction(LCD_ENTRY_MODE);

	WaitSoftWareTimer(500);			/* 約1msec(500) */

	/*----------------------*/
	/* 特殊文字データセット	*/
	/*----------------------*/
    SetCGRAM();

	/*----------------------*/
	/* 表示ＯＮ 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_DISPLAY_ON);

	WaitSoftWareTimer(500);			/* 約1msec(500) */

	/*----------------------*/
	/* 表示クリア 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);

#if 0 /* defined (HINOKI2) */  /* LCD表示ずれる件調査用 2003/01/17 T.Takagi */
	debug = 0;
	if (debug == 1 || debug == 2) {
		LCD_WriteInstruction(0x1C);	/* 強制的に表示を右にシフトしてみる */
		/* 60usec以上待つ */
		WaitSoftWareTimer(500);		/* 約1msec(500) */
	}

	if (debug == 2) {
		LCD_WriteInstruction(0x02);	/* 表示をもとの位置に戻す */
		/* 1.64msec以上待つ */
		WaitSoftWareTimer(1000);		/* 約2msec(1000) */
	}
#endif

	/* KeyScan Rowセット */
	/* RS -> 1 */
	LcdDriverRegisterData();

	/* PLOAD -> 0 -> 1 */
	PanelDataLoadOff();
	PanelDataLoadOn();
	/* RS -> 0 */
	LcdDriverRegisterIR();

	Output(SCI_SCR0,0x00);		/* SCI 送受信不可(再初期化) */
	/* オーバランエラークリア(SCI) */
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_ORER));
	Output(SCI_SCR0,(SCR_RE + SCR_TE));		/* Tx/Rx可 */

	LcdScanPos = 0;
	LcdResetCount = 0;
	NewKey = 0;
	NewKeyData = 0;
	BeforeNewKey = 0;			/* 1回前のキー入力データ(割り込み内設定用) *//* Add by O.Kimoto 1999/02/26 */
	CursorBlinkCont = 0;

	/* DDRAMアドレスセット */
	while(!(Input(SCI_SSR0) & SSR_TDRE));		/* TDRE = 1 ? */
	Output(SCI_TDR0, DDRAM_FIRST_ROW_ADDRESS);
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE)); /* TDRE -> 0 */

	/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
	** byO.Kimoto 1999/02/06
	*/
	CMN_MemorySetNULL(LCD_DisplayBufferHigh,         OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(LCD_DisplayBufferLow,          OPR_DISPLAY_MAX, ' ');

}

/*************************************************************************
	module		:[指定した位置に一文字表示]
	function	:[1.表示バッファのを順次スキャンし内容をＤＤＲＡＭへ書き込む
				  2.表示位置：上段ｰ>0～19､下段->20～39
	]
	return		:[]
	common		:[LcdScanPos]
	comment		:[５ｍｓ割り込み]
*************************************************************************/
void DisplayLCD(void)
{
	/* SCIリード(key入力取り込み) */
	while(!(Input(SCI_SSR0) & SSR_RDRF));	/* RDRF = 1 ? */
	NewKey = Input(SCI_RDR0);
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_RDRF));

	/* LCDにﾃﾞｰﾀ書き込み処理(前回の割込でｼﾘｱﾙに書いたﾃﾞｰﾀをLCDに送る) */
	if ((LcdScanPos == LCD_HIGH_INST_POS) || (LcdScanPos == LCD_LOW_INST_POS)) {
		/* LcdScanPos = 0 or 21 */
		LcdDriverRegisterIR();
		LcdDriverClockOn();
		LcdDriverClockOff();
	} else if (((LcdScanPos >= LCD_HIGH_START_POS) && (LcdScanPos < LCD_HIGH_END_POS))
		|| ((LcdScanPos >= LCD_LOW_START_POS) && (LcdScanPos < LCD_LOW_END_POS))){	
		/* LcdScanPos = 1-20 or 22-41 */
		LcdDriverRegisterData();
		LcdDriverClockOn();
		LcdDriverClockOff();
	} else if (LcdScanPos == LED1_WRITE_POS) {	/* = 42 */
		LedPortSelect1On();
		LedPortSelect1Off();
	} else {
		LedPortSelect2On();
		LedPortSelect2Off();
	}

	if (++LcdScanPos >= LCD_WR_MAX) {
		LcdScanPos = 0;
	}

	PanelDataLoadOff();
	PanelDataLoadOn();

	/* RS -> 0 */
	LcdDriverRegisterIR();

	/* Data Write */
	while(!(Input(SCI_SSR0) & SSR_TDRE));		/* TDRE = 1 ? */
	if ((LcdScanPos == LCD_HIGH_INST_POS) || (LcdScanPos == LCD_LOW_INST_POS)) {
		/* DDRAMアドレス */
		if (LcdScanPos == LCD_HIGH_INST_POS) {
			Output(SCI_TDR0, DDRAM_FIRST_ROW_ADDRESS);
		} else {
			Output(SCI_TDR0, DDRAM_SECOND_ROW_ADDRESS);
		}
	} else if ((LcdScanPos >= LCD_HIGH_START_POS) && (LcdScanPos < LCD_HIGH_END_POS)) {	 /* 1-20 */
		/* 表示ﾃﾞｰﾀ */
		if ((LcdScanPos == LcdCursorPos) && (CursorBlinkFlag)) {
			Output(SCI_TDR0, 0xFF);		/* 全黒をセット */
		} else {

#if (0)
** 			/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** 			** byO.Kimoto 1999/02/06
** 			*/
** 			Output(SCI_TDR0, DisplayBufferHigh[LcdScanPos - LCD_HIGH_START_POS]);
#else
			Output(SCI_TDR0, LCD_DisplayBufferHigh[LcdScanPos - LCD_HIGH_START_POS]);
#endif

		}
	} else if ((LcdScanPos >= LCD_LOW_START_POS) && (LcdScanPos < LCD_LOW_END_POS)){	/* 22-41 */
		/* 表示ﾃﾞｰﾀ */
		if ((LcdScanPos == LcdCursorPos) && (CursorBlinkFlag)) {
			Output(SCI_TDR0, 0xFF);		/* 全黒をセット */
		} else {

#if (0)
** 			/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** 			** byO.Kimoto 1999/02/06
** 			*/
** 			Output(SCI_TDR0, DisplayBufferLow[LcdScanPos - LCD_LOW_START_POS]);
#else
			Output(SCI_TDR0, LCD_DisplayBufferLow[LcdScanPos - LCD_LOW_START_POS]);
#endif

		}
	} else if (LcdScanPos == LED1_WRITE_POS) {
		/* LED1の点灯/消灯 */
		Output(SCI_TDR0, ~SYS_LED1_PortStatus);
	} else {
		/* LED2の点灯/消灯 */
		Output(SCI_TDR0, ~SYS_LED2_PortStatus);
	}

	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE)); /* TDRE -> 0 */
	/* カーソル点滅 */
	CursorBlinkCont++;
	if (!(CursorBlinkCont % 100)) {	/* 500ms間隔 */
		CursorBlinkFlag ^= 0x01;
	}
	if (CursorBlinkCont >= 200) {	/* 1000ms間隔 */
#if (0)
		BlinkLED();			/* LED点滅 */
#endif
		CursorBlinkCont = 0;
	}
}

/*************************************************************************
	module		:[ＬＣＤ上段に文字列を表示]
	function	:[1.ＬＣＤの上段の指定された位置に文字列を表示
				  2.表示位置:０～１９
	]
	return		:[]
	common		:[DisplayBufferHigh]
	comment		:[]
*************************************************************************/
void DisplayStringHigh(
	UBYTE pos,				/* 表示位置(0～19) */
	CONST UBYTE *string)	/* 表示文字列 */
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	IntEnble;		/* 表示がとろすぎてＬＣＤ表示がつぶれます。by O.Kimoto 1999/02/26 */

	/** カーソルをＯＦＦする By H.Fujimura 1998/11/05 */
	CursorOff();

	/* 表示文字列のアドレス変換 */
	string = CalculateStringAddress(string);

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching 防止のため */

	/* LCD_DisplayBufferHigh[]にコピーする前に点滅を止めるようにする T.Nose 2005/03/10 */
	/** 点滅表示を停止する By H.Fujimura 1998/12/02 */
	StopFunctionFlashHigh();

	/* 表示文字列の書き込み */
	for (counter = pos; counter < OPR_DISPLAY_MAX; counter++) {

		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了(文字列の最後にはNULLをいれておく) */
			break;
		}

#if (0)
** 		/* 関数置き換え By O.Kimoto 1998/09/25 */
** 		write_data = ConvSpecialChar(*string++);	/* 特殊文字変換 */
#else
		write_data = CheckSpecialCharacter(write_data);	/* 特殊文字変換 */
#endif

#if (0)
** 			/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** 			** byO.Kimoto 1999/02/06
** 			*/
** 		DisplayBufferHigh[counter] = write_data;
#else
		LCD_DisplayBufferHigh[counter] = write_data;
#endif

	}

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	if (IntEnble) {
		CMN_EnableInterrupt();
	}

#if 0 /* LCD_DisplayBufferHigh[]にコピーする前に点滅を止めるようにする T.Nose 2005/03/10 */
	/** 点滅表示を停止する By H.Fujimura 1998/12/02 */
	StopFunctionFlashHigh();
#endif
}

/*************************************************************************
	module		:[ＬＣＤ下段に文字列を表示]
	function	:[ＬＣＤ下段の指定された位置に文字列を表示]
	return		:[]
	common		:[DisplayBufferLow]
	condition	:[点滅表示には使用しないこと]
	comment		:[]
*************************************************************************/
void DisplayStringLow(
	UBYTE pos,		/* 表示位置(0～19) */
	CONST UBYTE *string)	/* 表示文字列 */
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	IntEnble;		/* 表示がとろすぎてＬＣＤ表示がつぶれます。by O.Kimoto 1999/02/26 */

	/** カーソルをＯＦＦする By H.Fujimura 1998/11/05 */
	CursorOff();

	/* 表示文字列のアドレス変換 */
	string = CalculateStringAddress(string);

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching 防止のため */

	/* LCD_DisplayBufferLow[]にコピーする前に点滅を止めるようにする T.Nose 2005/03/10 */
	/** 点滅表示を停止する By H.Fujimura 1998/12/02 */
	/* 点滅中に点滅タスク以外のタスクが表示を書き換えるには点滅をやめる時であるとする */
	StopFunctionFlashLow();

	/* 表示文字列の書き込み */
	for (counter = pos; counter < OPR_DISPLAY_MAX; counter++) {

		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了(文字列の最後にはNULLをいれておく) */
			break;
		}

#if (0)
** 		/* 関数置き換え By O.Kimoto 1998/09/25 */
** 		write_data = ConvSpecialChar(*string++);	/* 特殊文字変換 */
#else
		write_data = CheckSpecialCharacter(write_data);	/* 特殊文字変換 */
#endif

#if (0)
** 			/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** 			** byO.Kimoto 1999/02/06
** 			*/
** 		DisplayBufferLow[counter] = write_data;
#else
		LCD_DisplayBufferLow[counter] = write_data;
#endif

	}

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	if (IntEnble) {
		CMN_EnableInterrupt();
	}

#if 0 /* LCD_DisplayBufferLow[]にコピーする前に点滅を止めるようにする T.Nose 2005/03/10 */
	/** 点滅表示を停止する By H.Fujimura 1998/12/02 */
	/* 点滅中に点滅タスク以外のタスクが表示を書き換えるには点滅をやめる時であるとする */
	StopFunctionFlashLow();
#endif
}


#if (0)
** /* CheckSpecialCharacter()に置き換えます。 By O.Kimoto 1998/09/25 */
** /*-----------------------------------------------------------------------*
** 	module		:[特殊記号を表示形式に変換する]
** 	function	:[]
** 	return		:[表示上表現値]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** *-----------------------------------------------------------------------*/
** UBYTE ConvSpecialChar(UBYTE data)
** {
** 	UBYTE	ret;
** 
** 	switch(data) {
** 	case OPR_ONETOUCH_MARK:			/* ワンタッチＵ１～Ｕ８のＵ */
** 		ret = 'U';
** 		break;
** 	case OPR_SPEED_MARK:			/* 短縮記号 */
** 		ret = 'S';
** 		break;
** #if (0)	/*** 使用していない ***/
** 	case OPR_GROUP_MARK:			/* グループ記号 *//** 未使用 **/
** 		ret = 'G';
** 		break;
** #endif
** 	case OPR_PIN_MARK:				/* ＰＩＮ記号 */
** 		ret = '*';
** 		break;
** 	default:
** 		ret = data;
** 		break;
** 	}
** 	return(ret);
** }
#endif


/*************************************************************************
	module		:[ＬＣＤ上段表示クリア]
	function	:[ＬＣＤ上段の表示をクリア(スペースを書き込む)]
	return		:[]
	common		:[]
	comment		:[]
*************************************************************************/
void ClearDisplayHigh(void)
{
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	DisplayStringHigh(0, DisplayBufferHigh);
}


/*************************************************************************
	module		:[ＬＣＤ下段表示クリア]
	function	:[1.ＬＣＤ下段の表示をクリアする(スペースの書き込み)]
	return		:[]
	common		:[]
	comment		:[]
*************************************************************************/
void ClearDisplayLow(void)
{
	CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	DisplayStringLow(0, DisplayBufferLow);
}


/*************************************************************************
	module		:[カーソル動作制御の初期化を行う]
	function	:[1.引数で指定された位置にカーソルを表示させる
				  2.表示位置：上段→０～１９、下段→２０～３９
	]
	return		:[]
	common		:[]
	comment		:[CursorRightMove/CursorLeftMove使用時のみ有効]
*************************************************************************/
void CursorCtrlInit(
UBYTE	type,			/* 0:Limit , 1:Rotation  */
UBYTE	start_col,		/* カーソル移動範囲左端(カラム位置) */
UBYTE	end_col)		/* カーソル移動範囲右端(カラム位置) */
{
	CursorActionType = type;		/* 動作種別(0:Limit,1:Rotation) */
	CursorLeftLimit = start_col;	/* カーソル移動範囲：左端 */
	CursorRightLimit = end_col;		/* カーソル移動範囲：右端 */
	CursorCurrentPos = start_col;	/* カーソル現在位置 */
}


/*************************************************************************
	module		:[指定された位置にカーソルを表示]
	function	:[1.引数で指定された位置にカーソルを表示させる
				  2.表示位置：上段→０～１９、下段→２０～３９
	]
	return		:[]
	common		:[SYS_LCD_DataPortStatus]
	comment		:[]
*************************************************************************/
void CursorOn(UBYTE pos)	/* 表示位置(0～39) */
{
	/* カーソル位置の変換 */
	if (pos <= 19) {	/* 0 ～ 19 */
		pos++;
	} else {			/* 20 ～ 39 */
		pos += 2;
	}
	LcdCursorPos = pos;
	CursorBlinkFlag = 1;
}


/*************************************************************************
	module		:[カーソルＯＦＦ]
	function	:[]
	return		:[]
	common		:[]
	comment		:[]
*************************************************************************/
void CursorOff(void)
{
	/* 点滅フラグの初期化 */
	CursorBlinkFlag = 0;
	LcdCursorPos = 0xFF;
}


/*************************************************************************
	module		:[]
	function	:[]
	return		:[]
	common		:[]
	comment		:[KURUMIの場合のみ必要]
*************************************************************************/
void SetCursorPos(UBYTE pos)
{
	if (pos <= 19) {	/* 0 ～ 19 */
		pos++;
	} else {			/* 20 ～ 39 */
		pos += 2;
	}
	LcdCursorPos = pos;
}


/*************************************************************************
	module		:[カーソル右移動]
	function	:[]
	return		:[]
	common		:[]
	comment		:[]
*************************************************************************/
void CursorRightMove(void)
{
	if (CursorActionType) {	/* Rotation Type */
		if (CursorCurrentPos < CursorRightLimit) {
			CursorCurrentPos++;
		} else {
			CursorCurrentPos = CursorLeftLimit;
		}
	} else {				/* Limit Type */
		if (CursorCurrentPos < CursorRightLimit) {
			CursorCurrentPos++;
		} else {
			NackBuzzer();
		}
	}
	if (CursorLeftLimit < 20) {
		LcdCursorPos = CursorCurrentPos;
	} else {
		LcdCursorPos = (CursorCurrentPos + 2);
	}
}


/*************************************************************************
	module		:[カーソル左移動]
	function	:[]
	return		:[]
	common		:[]
	comment		:[]
*************************************************************************/
void CursorLeftMove(void)
{
	if (CursorActionType) {	/* Rotation Type */
		if (CursorCurrentPos > CursorLeftLimit) {
			CursorCurrentPos--;
		} else {
			CursorCurrentPos = CursorRightLimit;
		}
	} else {				/* Limit Type */
		if (CursorCurrentPos > CursorLeftLimit) {
			CursorCurrentPos--;
		} else {
			NackBuzzer();
		}
	}
	if (CursorLeftLimit < 20) {
		LcdCursorPos = CursorCurrentPos;
	} else {	/* 20以上 */
		LcdCursorPos = (CursorCurrentPos + 2);
	}
}


/*************************************************************************
	module		:[]
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
	date		:[]
	author		:[]
*************************************************************************/
void DisplayAllBlack(void)
{
	CMN_MemorySetNULL(DisplayBufferHigh, OPR_DISPLAY_MAX, 0xFF);
	DisplayStringHigh(0, DisplayBufferHigh);
	DisplayStringLow(0, DisplayBufferHigh);
}


/*************************************************************************
	module		:[特殊文字処理]
	function	:[
		1.Ⅰ,Ⅱ,Ⅲ,Ⅳに対する処理を行う-> ＡＮＺＵではいらなくなった 1995/12/12
		2.グループ記号、短縮記号に対する処理をおこなう
		3.ワンタッチ記号の、ＰＩＮ記号に対する処理を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/25]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckSpecialCharacter(UBYTE character)
{
	UBYTE	ret_value;

	ret_value = character;

	switch (character) {
	case OPR_ONETOUCH_MARK_LEFT:	/* ワンタッチ［０１］～［７２］の左かっこ */
	case OPR_PROGRAM_MARK_LEFT:		/* プログラムワンタッチ［７３］～［８０］の左かっこ */
		ret_value = '[';
		break;
	case OPR_ONETOUCH_MARK_RIGHT:	/* ワンタッチ［０１］～［７２］の右かっこ */
	case OPR_PROGRAM_MARK_RIGHT:	/* プログラムワンタッチ［７３］～［８０］の右かっこ */
		ret_value = ']';
		break;
	case OPR_ONETOUCH_MARK:			/* ワンタッチＵ１～Ｕ８のＵ */
		ret_value = 'U';
		break;
	case OPR_PROGRAM_MARK:			/* プログラムワンタッチＰ１～Ｐ５のＰ */
		ret_value = 'P';
		break;
	case OPR_SPEED_MARK:			/* 短縮記号 */
		ret_value = 'S';
		break;
	case OPR_GROUP_MARK:			/* グループ記号 */
		ret_value = 'G';
		break;
	case OPR_PIN_MARK:				/* ＰＩＮ記号 */
		ret_value = '*';
		break;
#if (PRO_JIS_CODE == ENABLE)
	case OPR_KANJI_CODE_MARK_LEFT:	/* 漢字コードの左かっこ */
		ret_value = '(';
		break;
	case OPR_KANJI_CODE_MARK_RIGHT:	/* 漢字コードの右かっこ */
		ret_value = ')';
		break;
#endif
	case OPR_PAPER_SIZE_R:			/* 紙サイズのＲを表すグラフィック（ﾜｰﾃﾞｨﾝｸﾞで直接使用） */
		ret_value = 0xF5;
		break;
	default:
		break;
	}

	/*
	** ＣＧＲＡＭをアクセスするために変換する
	** ユーザーフォントコード	０ｘＦ０～０ｘＦ７（割り当て）
	** ＣＧＲＡＭコード			０ｘ００～０ｘ０７（固定）
	*/

#if 0 /* defined (HINOKI2) */	/* LCDドライバ変更対応 2002/05/01 T.Takagi */
	if ((ret_value >= OPR_CG_FONT_0) && (ret_value <= OPR_CG_FONT_7)) {
		ret_value -= OPR_CG_FONT_0;
	}
#else
	if (0x1C <= ret_value && ret_value <= 0x1F) {
		ret_value -= 0x1C;        /*ⅠⅡⅢⅣの時*/
	}
#endif
#if !defined(JPN) /* 日本以外の特殊文字対応 By 小原 */
	if (0xA0 <= ret_value && ret_value <= 0xBF) {
		ret_value -= 0x20;
	}
	if (0xC0 <= ret_value && ret_value <= 0xDF) {
		ret_value += 0x20;
	}
#endif
	return (ret_value);
}


/*************************************************************************
	module		:[指定した位置に一文字表示]
	function	:[
		1.引数で指定された位置に一文字表示する
		2.表示位置：上段ｰ>0～19､下段->20～39
	]
	return		:[]
	common		:[SYS_LCD_DataPortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void DisplayChar(UBYTE pos,			/*表示位置 0-39*/
				 UBYTE dsp_char)	/*表示文字*/
{

	UBYTE	IntEnble;		/* 表示がとろすぎてＬＣＤ表示がつぶれます。by O.Kimoto 1999/02/26 */

#if (0)
** /* 現状のＬＯＴＵＳ／ＫＵＲＵＭＩは、ＬＣＤの途中から文字を表示すると言う考え方が基本的に存在しない。
** ** よって、暫定的にこの関数が呼ばれると、上下のどちらかのバッファに指定文字をセットし、後の表示に関しては
** ** 表示割り込み処理に任せるものとする。
** ** By O.Kimoto 1998/09/25
** */
** 	UBYTE	ddram_adr;
** 
** 	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
** 	CursorOff();
** 
** 	/*-------------------------*/
** 	/** 表示位置のアドレス計算 */
** 	/*-------------------------*/
** 	if (pos < 20) {
** 		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
** 	}
** 	else {
** 		pos -= 20;
** 		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
** 	}
** 
** 	/*----------------------------------------*/
** 	/** DDRAMアドレスセット(表示位置のセット) */
** 	/*----------------------------------------*/
** 	LCD_WriteInstruction(ddram_adr);
**     LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
** 
** 	
** 	/* 文字がNULLの場合終了 */
** 	if (dsp_char == 0x00) {
** 		return;
** 	}
** 
** 	/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する処理 */
** 	dsp_char = CheckSpecialCharacter(dsp_char);
** 
** 	/*-------------*/
** 	/** 文字を表示 */
** 	/*-------------*/
** 	LCD_WriteData(dsp_char);
**     LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
#else
	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/* 文字がNULLの場合終了 */
	if (dsp_char == 0x00) {
		return;
	}

	/** 特殊文字（Ⅰ,Ⅱ,Ⅲ等）に対する処理 */
	dsp_char = CheckSpecialCharacter(dsp_char);

	/*-------------*/
	/** 文字を表示 */
	/*-------------*/

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching 防止のため */

	/*-------------------------*/
	/** 表示位置のアドレス計算 */
	/*-------------------------*/
	if (pos < 20) {

#if (0)
** /* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** ** byO.Kimoto 1999/02/06
** */
** 		DisplayBufferHigh[pos] = dsp_char;
#else
		LCD_DisplayBufferHigh[pos] = dsp_char;
#endif

	}
	else {

#if (0)
** 		/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** 		** byO.Kimoto 1999/02/06
** 		*/
** 		DisplayBufferLow[(pos - 20)] = dsp_char;
#else
		LCD_DisplayBufferLow[(pos - 20)] = dsp_char;
#endif

	}

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	if (IntEnble) {
		CMN_EnableInterrupt();
	}

#endif
}


/*************************************************************************
	module		:[ＣＧＲＡＭ書き換え検査]
	function	:[
		1.表示する文字列の中に、縦原稿を表すコードがあれば、ＣＧＲＡＭを
		　使用するので、書き換えます
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/26]
	author		:[渡辺一章]
*************************************************************************/
void CheckChangeCGRAM(UBYTE *string)
{

#if (0)
** /* ＨＩＮＯＫＩでは不要（？） By O.Kimoto 1998/09/25 */
** 	UBYTE	i;	/* ループ変数 */
** 
** 	for (i = 0; i < OPR_DISPLAY_MAX; i++) {
** 		if (*string == NULL) {
** 			break;
** 		}
** 		if (*string++ == OPR_PAPER_SIZE_R) {	/* 文字列の中に、縦原稿があった時 */
** 			/* ＣＧＲＡＭに縦原稿表示用のデータを書き込みます */
** 			WriteCGRAM((UBYTE *)CG_RamTableCopyModeDensity);
** 			break;
** 		}
** 	}
#endif
	return;
}


/*************************************************************************
	module		:[ＬＣＤ上段に文字列を表示]
	function	:[
		1.LCDの上段の指定された位置に文字列を表示
		2.点滅表示専用の関数です
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/12/02]
	author		:[藤村春夫]
*************************************************************************/
void DisplayFlashStringHigh(UBYTE pos,		/*表示位置(0～19)*/
							UBYTE *string)	/*表示文字列*/
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	IntEnble;		/* 表示がとろすぎてＬＣＤ表示がつぶれます。by O.Kimoto 1999/02/26 */

	/** カーソルをＯＦＦする By H.Fujimura 1998/11/05 */
	CursorOff();

	/* 表示文字列のアドレス変換 */
	string = CalculateStringAddress(string);

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching 防止のため */

	/* 表示文字列の書き込み */
	for (counter = pos; counter < OPR_DISPLAY_MAX; counter++) {

		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了(文字列の最後にはNULLをいれておく) */
			break;
		}

#if (0)
** 		/* 関数置き換え By O.Kimoto 1998/09/25 */
** 		write_data = ConvSpecialChar(*string++);	/* 特殊文字変換 */
#else
		write_data = CheckSpecialCharacter(write_data);	/* 特殊文字変換 */
#endif

#if (0)
** /* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** ** byO.Kimoto 1999/02/06
** */
** 		DisplayBufferHigh[counter] = write_data;
#else
		LCD_DisplayBufferHigh[counter] = write_data;
#endif

	}

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	if (IntEnble) {
		CMN_EnableInterrupt();
	}
	
}

/*************************************************************************
	module		:[ＬＣＤ下段に文字列を表示]
	function	:[
		1.LCD下段の指定された位置に文字列を表示
		2.点滅表示専用の関数です
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/12/02]
	author		:[藤村春夫]
*************************************************************************/
void DisplayFlashStringLow(UBYTE pos,		/*表示位置(0～19)*/
						   UBYTE *string)	/*表示文字列*/
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	IntEnble;		/* 表示がとろすぎてＬＣＤ表示がつぶれます。by O.Kimoto 1999/02/26 */

	/** カーソルをＯＦＦする By H.Fujimura 1998/11/05 */
	CursorOff();

	/* 表示文字列のアドレス変換 */
	string = CalculateStringAddress(string);

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	IntEnble = CheckInterruptEnable();
	CMN_DisableInterrupt();					/* Task Switching 防止のため */

	/* 表示文字列の書き込み */
	for (counter = pos; counter < OPR_DISPLAY_MAX; counter++) {

		write_data = *string++;
		if (write_data == 0x00) {	/* NULLの場合書き込み終了(文字列の最後にはNULLをいれておく) */
			break;
		}

#if (0)
** 		/* 関数置き換え By O.Kimoto 1998/09/25 */
** 		write_data = ConvSpecialChar(*string++);	/* 特殊文字変換 */
#else
		write_data = CheckSpecialCharacter(write_data);	/* 特殊文字変換 */
#endif

#if (0)
** 		/* ＬＣＤ表示がちらつくので、ローカル用バッファに一旦コピーしてから表示するように変更
** 		** byO.Kimoto 1999/02/06
** 		*/
** 		DisplayBufferLow[counter] = write_data;
#else
		LCD_DisplayBufferLow[counter] = write_data;
#endif

	}

	/* 表示がとろすぎてＬＣＤ表示がつぶれます。
	** by O.Kimoto 1999/02/26
	*/
	if (IntEnble) {
		CMN_EnableInterrupt();
	}

}

/*************************************************************************
	module		:[ＣＧＲＡＭにデータを書き込む]
	function	:[
		1.
		CGRAMにⅠを書き込む
		CGRAMにⅡを書き込む
		CGRAMにⅢを書き込む
		CGRAMにⅣを書き込む
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[LCD]
	ProtoType	:[void SetCGRAM(void){}]
	date		:[1998/10/07]
	author		:[木元  修]
*************************************************************************/
void SetCGRAM(void)
{
    UBYTE *Pointer;
    UBYTE Counter;

#if 0 /* defined (HINOKI2) */ /* LCDドライバ変更対応 2002/05/14 T.Takagi */
    Pointer = &CG_RamTableFaxReadyKanji[0][0];
#else
    Pointer = &CG_RamTableNumericSymbol[0][0];
#endif

	LcdDriverRegisterIR();

	LCD_WriteInstruction(LCD_CGRAM_ADDRESS);	/* Set CGRAM Address */
	WaitSoftWareTimer(500);			/* 約1msec(500) */
	/* wai_tsk(1); */
	LcdDriverRegisterData();

#if 0 /* defined (HINOKI2) */	/* LCDドライバ変更対応 2002/04/27 T.Takagi */
    for (Counter = 0; Counter < LCD_CGRAM_WRITE_DATA_COUNT; Counter++) {
#else
    for (Counter = 0; Counter < 32; Counter++) {
#endif
		/* Data Write */
		LCD_WriteInstruction(*Pointer);	/* Set CGRAM Address */
		WaitSoftWareTimer(500);			/* 約1msec(500) */
		/* wai_tsk(1); */
		Pointer ++;
    }
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE)); /* TDRE -> 0 */

	LcdDriverRegisterIR();
}

#if 0 /* defined (HINOKI2) */	/* 2002/05/15 LCDドライバ変更対応 */
/*************************************************************************
	module		:[ＣＧＲＡＭ書き込みデータ初期化]
	function	:[
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2002/05/14]
	author		:[高木智史]
*************************************************************************/
void	InitializeCGRAM_Data(void)
{
	
	CMN_DisableInterrupt();
	if (!SYS_IsDisplayingLCD) {
		SYS_IsCGRAM_Writing = TRUE;
		CMN_EnableInterrupt();

		Output(SCI_SCR0,SCR_TE);	/* SCI送信のみに設定 */
		Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_RDRF));

		SetCGRAM();		/* CGRAMが化けている可能性があるので、再セット */

		/*----------------------*/
		/* 表示ＯＮ 			*/
		/*----------------------*/
		LCD_WriteInstruction(LCD_DISPLAY_ON);

		wai_tsk(1);
		/* WaitSoftWareTimer(500); */		/* 約1msec(500) */

		/*----------------------*/
		/* 表示クリア 			*/
		/*----------------------*/
		LCD_WriteInstruction(LCD_CLEAR_DISPLAY);


		/* KeyScan Rowセット */
		/* RS -> 1 */
		LcdDriverRegisterData();

		/* PLOAD -> 0 -> 1 */
		PanelDataLoadOff();
		PanelDataLoadOn();
		/* RS -> 0 */
		LcdDriverRegisterIR();

		Output(SCI_SCR0,0x00);		/* SCI 送受信不可(再初期化) */
		Output(SCI_SCR0,(SCR_RE + SCR_TE));		/* Tx/Rx可 */

		LcdScanPos = 0;

		while(!(Input(SCI_SSR0) & SSR_TDRE));		/* TDRE = 1 ? */
		Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE)); /* TDRE -> 0 */

		SYS_IsCGRAM_Writing = FALSE;
	}
	CMN_EnableInterrupt();
}
#endif
