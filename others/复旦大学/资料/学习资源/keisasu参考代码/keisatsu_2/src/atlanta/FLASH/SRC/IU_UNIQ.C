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

/* #include "\src\atlanta\opr\ank\ext_v\opr_data.h" */

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\ext_v\sys_port.h"

#include "\src\atlanta\flash\ext_v\sys_data.h"
/*
**	指定時間ループし、Waitするルーチン。
**	CPUパワーを放さないため、他タスクが動作しないくて良い場合のみ使用すること。
**	実測:10000:16ms、9000:15ms、6000:10ms、500:1ms
**  ＨＩＮＯＫＩでの実測は、ＬＯＴＵＳ／ＲＵＫＵＭＩより５倍早かった。
**  よって、単純にタイマー値を５倍します。
**  by O.Kimoto 1998/09/29
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
	IO__PEDR |= IO_BIT_LE;
	/* LE -> 0 */
	IO__PEDR &= ~IO_BIT_LE;
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
	Output(SCI_SCR0,SCR_TE);	/* SCI送信のみに設定 */

	/* 15msec以上待つ */
	WaitSoftWareTimer(50000);	/* 約16msec(10000) */

	/*------------------------*/
	/* ファンクションセット１ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	/* 4,1msec以上待つ */
	WaitSoftWareTimer(30000);	/* 約10msec(6000) */

	/*------------------------*/
	/* ファンクションセット２ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	/* 100usec以上待つ */
	WaitSoftWareTimer(2500);		/* 約1msec(500) */

	/*------------------------*/
	/* ファンクションセット３ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	/* 15msec以上待つ */
	WaitSoftWareTimer(45000);	/* 約14msec(9000) */

	/*------------------------*/
	/* ファンクションセット４ */
	/*------------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);

	WaitSoftWareTimer(2500);		/* 約1msec(500) */

	/*----------------------*/
	/* 表示ＯＦＦ 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_DISPLAY_OFF);

	WaitSoftWareTimer(2500);		/* 約1msec(500) */

	/*----------------------*/
	/* 表示クリア 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);

	WaitSoftWareTimer(2500);			/* 約1msec(500) */

	/*----------------------*/
	/* エントリーモードセット */
	/*----------------------*/
	LCD_WriteInstruction(LCD_ENTRY_MODE);

	WaitSoftWareTimer(2500);			/* 約1msec(500) */

	/*----------------------*/
	/* 表示ＯＮ 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_DISPLAY_ON);

	WaitSoftWareTimer(2500);			/* 約1msec(500) */

	/*----------------------*/
	/* 表示クリア 			*/
	/*----------------------*/
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);


	/* KeyScan Rowセット */
	/* RS -> 1 */
	IO__PEDR |= IO_BIT_LRS;

	/* PLOAD -> 0 -> 1 */
	IO__PEDR &= ~IO_BIT_PROAD;
	IO__PEDR |= IO_BIT_PROAD;
	/* RS -> 0 */
	IO__PEDR &= ~IO_BIT_LRS;

	Output(SCI_SCR0,0x00);		/* SCI 送受信不可(再初期化) */
	/* オーバランエラークリア(SCI) */
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_ORER));
	Output(SCI_SCR0,(SCR_RE + SCR_TE));		/* Tx/Rx可 */

	LcdScanPos = 0;
	NewKey = 0;

	/* DDRAMアドレスセット */
	while(!(Input(SCI_SSR0) & SSR_TDRE));		/* TDRE = 1 ? */
	Output(SCI_TDR0, DDRAM_FIRST_ROW_ADDRESS);
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE)); /* TDRE -> 0 */

	IO__PEDR |= IO_BIT_LEWR3;

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
		IO__PEDR &= ~IO_BIT_LRS;
		IO__PEDR |= IO_BIT_LE;
		IO__PEDR &= ~IO_BIT_LE;
	} else if (((LcdScanPos >= LCD_HIGH_START_POS) && (LcdScanPos < LCD_HIGH_END_POS))
		|| ((LcdScanPos >= LCD_LOW_START_POS) && (LcdScanPos < LCD_LOW_END_POS))){	
		/* LcdScanPos = 1-20 or 22-41 */
		IO__PEDR |= IO_BIT_LRS;
		IO__PEDR |= IO_BIT_LE;
		IO__PEDR &= ~IO_BIT_LE;
	} else if (LcdScanPos == LED1_WRITE_POS) {	/* = 42 */
		IO__PEDR |= IO_BIT_LEWR1;
		IO__PEDR &= ~IO_BIT_LEWR1;
	} else {
		IO__PEDR |= IO_BIT_LEWR2;
		IO__PEDR &= ~IO_BIT_LEWR2;
	}

	if (++LcdScanPos >= LCD_WR_MAX) {
		LcdScanPos = 0;
	}

	IO__PEDR &= ~IO_BIT_PROAD;
	IO__PEDR |= IO_BIT_PROAD;

	/* RS -> 0 */
	IO__PEDR &= ~IO_BIT_LRS;

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
		Output(SCI_TDR0, DisplayBufferHigh[LcdScanPos - LCD_HIGH_START_POS]);
	} else if ((LcdScanPos >= LCD_LOW_START_POS) && (LcdScanPos < LCD_LOW_END_POS)){	/* 22-41 */
		/* 表示ﾃﾞｰﾀ */
		Output(SCI_TDR0, DisplayBufferLow[LcdScanPos - LCD_LOW_START_POS]);
	} else if (LcdScanPos == LED1_WRITE_POS) {
		/* LED1の点灯/消灯 */
		Output(SCI_TDR0, 0xff);
	} else {
		/* LED2の点灯/消灯 */
		Output(SCI_TDR0, 0xff);
	}
	Output(SCI_SSR0, (Input(SCI_SSR0) & ~SSR_TDRE)); /* TDRE -> 0 */
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

	/* 表示文字列の書き込み */
	for (counter = pos; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;	/* 特殊文字変換 */
		if (write_data == 0x00) {	/* NULLの場合書き込み終了(文字列の最後にはNULLをいれておく) */
			break;
		}
		DisplayBufferHigh[counter] = write_data;
	}
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

	/* 表示文字列の書き込み  */
	for (counter = pos; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;	/* 特殊文字変換 */
		if (write_data == 0x00) {	/* NULLの場合書き込み終了(文字列の最後にはNULLをいれておく) */
			break;
		}
		DisplayBufferLow[counter] = write_data;
	}
}


/*
**	2.5ms毎にG/Aからくる割込み処理ルーチン１
*/
void GA_Interrupt1(void)
{
	++IntTimerCounter;

	/* 2.5ms毎に行うルーチンを記述 */
	/* 画処理 & 送信モータ制御 */
	if (IntTimerCounter & 0x00000001) {	/* 5msに１回処理 */
		/* LCD/LED制御 */
		DisplayLCD();
	}
}


void InitializeGateArray(void)
{
	/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, A4 */
	GA_MWR_Status = ((UWORD)(((UWORD)(0x00800500) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN);
	OutputWORD(GA_MWR, GA_MWR_Status);

	/* CI, 2.5ms割込みスタート */
#if defined (KEISATSU) /* 警察FAX 05/06/30 石橋正和 */
	GA_IntMaskStatus = (IMASK_INTSP | IMASK_XCI | IMASK_XCIEX);	
#else
	GA_IntMaskStatus = (IMASK_INTSP | IMASK_XCI);
#endif
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	GaPrtcStatus = 0;
	OutputWORD(GA_PRTC, GaPrtcStatus);

	IntTimerCounter = 0;

#if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (HINOKI3)	/* 治具書き換え後、放置にてモータが熱くなる不具合修正 1999/11/15 by T.Soneoka */ /* HINOKI2 2001/11/13 T.Takagi */
	/* 送信モータ励磁ＯＦＦ */
	GaTmr0Status &= ~TMEXCT;
	OutputWORD(GA_TMR0, GaTmr0Status);

	/* 受信モータ励磁ＯＦＦ */
	GaRmrStatus &= ~RMEXCT;
	OutputWORD(GA_RMR, GaRmrStatus);

 #if defined(SATSUKI2)	/* SATSUKI2 PC -> PCONに変更 by Y.Kano 2003/07/15 */
	/* ２４Ｖ ＰＣＯＮ ＯＦＦ */
 	IO__PDDRH &= ~IO_BIT_PCON;
 #else
	/* ２４Ｖ ＰＣＯＮ ＯＦＦ */
 	RelayPortStatus &= ~IO_BIT_PC;
 	OutputWORD(GA_PGADR, RelayPortStatus);
 #endif
#endif
}
