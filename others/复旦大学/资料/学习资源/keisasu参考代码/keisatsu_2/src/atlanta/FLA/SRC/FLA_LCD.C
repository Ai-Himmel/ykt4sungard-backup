/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_LCD.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤドライバーモジュール
*	Maintenance	: opr_lcda.c と opr_lcdk.c を一つにまとめました。T.Nose 1998/04/28
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include "\src\ATLANTA\FLA\define\sys_def.h"
#include "\src\ATLANTA\FLA\define\sys_pro.h"
#include "\src\ATLANTA\ext_v\sys_port.h"
#include "\src\ATLANTA\define\scn_def.h"
#endif

#if (PRO_PANEL == KANJI)
#include "\src\ATLANTA\FLA\define\sys_pro.h"
#include "\src\atlanta\opr\kanji\define\opr_def.h"
#include "\src\atlanta\opr\kanji\define\lcd_def.h"
#include "\src\atlanta\opr\kanji\ext_v\lcd_buf.h"
#if (0) /* ＲＯＭ節約の為 1998/05/20 by T.Soneoka */
**extern CONST UBYTE FLA_ByteFont[256][16];
#else
extern CONST UBYTE FLA_ByteFont[128][16];
#endif
UBYTE * FLA_LCD_Display = 0;
/* void FLA_LCD_SoftWearTimer(UWORD time); */
#endif

#pragma section FLASHWRITE /*  "PFLASHWRITE" */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)

#if (PRO_PANEL == ANK) && (PRO_ANK_TO_KANJI == DISABLE)	/* PRO_ANK_TO_KANJIの条件追加 by K.Watanabe 1999/06/16 */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/* #if (PRO_KEYPANEL !=PANEL_HINOKI)	*/	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/09/14 */
 #if (PRO_KEYPANEL !=PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/09/14 *//* mode by SMuratec C.P 2004/05/28 */

/*************************************************************************
	module		:[ソフトウェアタイマー]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ループ１回あたりの処理時間は約３usec（V53エミュレータ実測値)]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/23]
	author		:[江口]
*************************************************************************/
void FLA_LCD_SoftWearTimer(UWORD time)
{
	while (time > 0) {
		time--;
	}
}

/*************************************************************************
	module		:[インストラクション発行]
	function	:[
		1.ＬＣＤコントローラにインストラクション（コマンド）を発行する。
	]
	return		:[]
	common		:[
		SYS_LCDC_PortStatus
		SYS_LCD_DataPortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/23]
	author		:[江口]
*************************************************************************/
void FLA_LCD_WriteInstruction(UBYTE instruction)
{
	/*--------------------------*/
	/*RS ->0:IR Registerを選択	*/
	/*R/W->0:Writeに設定		*/
	/*ENABLE->0					*/
	/*--------------------------*/
	SYS_LCDC_PortStatus &= ~(IO_BIT_RS | IO_BIT_R_W | IO_BIT_E);
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*---------------------------*/
	/*ENABLE->1					 */
	/*ﾃﾞｰﾀ書き込み開始			 */
	/*---------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_E;
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*---------------------------------------------------*/
	/*IR Registerにﾃﾞｰﾀ書き込み	    					 */
	/*---------------------------------------------------*/
	SYS_LCD_DataPortStatus = instruction;
	FLA_outpw(LCD_DATA_PORT, (UWORD)SYS_LCD_DataPortStatus);

	/*----------------------------*/
	/*ENABLE -> 0				  */
	/*ﾃﾞｰﾀ書き込み終了			  */
	/*LCDC内部動作開始(Busyｾｯﾄ)	  */
	/*----------------------------*/
	SYS_LCDC_PortStatus &= ~IO_BIT_E;
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
}

/*************************************************************************
	module		:[ビジーフラグ待ち]
	function	:[
		1.ＬＣＤコントローラに内部処理終了を待ちます
	]
	return		:[]
	common		:[
		SYS_LCDC_PortStatus
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/27]
	author		:[江口]
*************************************************************************/
void FLA_LCD_BusyFlagWait(UWORD time)	/*ループ回数(待ち時間 500 or 200）*/
{
	UBYTE	busy;

	/*---------------------------*/
	/* RS 	  -> 0:IRﾚｼﾞｽﾀを選択 */
	/* R/W	  -> 1:Readに設定	 */
	/* ENABLE -> 0				 */
	/*---------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_R_W;					/* R/W    を 1(R) */
	SYS_LCDC_PortStatus &= ~(IO_BIT_RS | IO_BIT_E);		/* Enable を 0    */
														/* RS     を 0    */
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	for ( ;time > 0; time--) {
		/*---------------------------*/
		/* ENABLE -> 1				 */
		/* ﾃﾞｰﾀ読み込み開始			 */
		/*---------------------------*/
		SYS_LCDC_PortStatus |= IO_BIT_E;
		FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

		FLA_LCD_SoftWearTimer(2);	/* 最低で220nsウェイトを置く By M.Tachibana 1997/05/12 */

		/*----------------------------*/
		/*ﾃﾞｰﾀ(BusyFlag)読み込み	  */
		/*----------------------------*/
		busy = (UBYTE)FLA_inpw(LCD_BUSY_PORT);

		/*----------------------------*/
		/*ENABLE -> 0				  */
		/*----------------------------*/
		SYS_LCDC_PortStatus &= ~IO_BIT_E;
		FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
		FLA_LCD_SoftWearTimer(1);	/* 最低で220nsウェイトを置く By M.Kotani 1997/08/06 */
  #if (PRO_KEYPANEL == PANEL_ANZU_L)		/* あんず＿Ｌタイプ */
		if (!(busy & IO_BIT_LCDBUSY)) {		/* Busyがこけている->内部処理終了 */
			return;
		}
  #else
		if (busy & IO_BIT_LCDBUSY) {		/* Busyがこけている->内部処理終了 */
			return;
		}
  #endif
	}
}


/*************************************************************************
	module		:[ＬＣＤデータ書き込み]
	function	:[
		1.CGRAM／DDRAMにデータを書き込む
	]
	return		:[]
	common		:[
		SYS_LCDC_PortStatus
		SYS_LCD_DataPortStatus
	]
	condition	:[]
	comment		:[
		CGRAM/DDRAMのどちらかを選択してからコールすること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/23]
	author		:[江口]
*************************************************************************/
void FLA_LCD_WriteData(UBYTE data)
{
	/*-------------------------------*/
	/* RS 		-> 1:DRを選択		 */
	/* R/W	　　-> 0:Writeに設定	 */
	/* ENABLE   -> 0				 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_RS;					/* RS     を 1    *//*ﾃﾞｰﾀﾚｼﾞｽﾀを選択*/
	SYS_LCDC_PortStatus &= ~(IO_BIT_R_W | IO_BIT_E);	/* R/W    を 0(W) *//*WRITEに設定*/
														/* Enable を 0    */
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*-------------------------------*/
	/* ENABLE -> 1					 */
	/* ﾃﾞｰﾀ書き込み開始			     */
	/* 書き込む所はDDRAM/CGRAM		 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_E;		/* Enable を 1 *//*WRITEのﾄﾘｶﾞ*/
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*-------------------------------*/
	/* DR Registerへﾃﾞｰﾀ書き込み	 */
	/*-------------------------------*/
	SYS_LCD_DataPortStatus = data;
	FLA_outpw(LCD_DATA_PORT, (UWORD)SYS_LCD_DataPortStatus);

	/*-------------------------------*/
	/* ENABLE -> 0					 */
	/* ﾃﾞｰﾀ書き込み終了				 */
	/* LCDC内部動作開始(Busy Set)	 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus &= ~IO_BIT_E;		/* Enable を 0 */
	FLA_outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
}

#if 0 /* 未使用 */
///*************************************************************************
//	module		:[ＣＧＲＡＭにイメージデータを書き込む]
//	function	:[
//		1.
//	]
//	return		:[なし]
//	common		:[SYS_LCD_DataPortStatus]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/02/23]
//	author		:[江口,渡辺一章]
//*************************************************************************/
//void FLA_WriteCGRAM(UBYTE *pointer)
//{
//	UBYTE	counter;
//	UBYTE	max;
//
//	max = (UBYTE)(LCD_SPECIAL_CHARACTER_MAX * LCD_CGRAM_TABLE_MAX);
//
//	/* CGRAMを選択 */
//	FLA_LCD_WriteInstruction(LCD_CGRAM_ADDRESS);
//
//	/* 内部処理が終了するまで、或いは次のコマンドを実行してもいいくらい十分時間が経過するまで待つ */
//	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
//
//	for (counter = 0; counter < max; counter++) {	/* （１文字あたり８byte）×（４文字） */
//		FLA_LCD_WriteData(*pointer);
//		FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
//		pointer++;
//	}
//}
#endif

/*************************************************************************
	module		:[ＬＣＤドライバ初期化]
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
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void FLA_LCD_Initialize(void)
{
	/** 15msec以上待つ */
/*	LCD_SoftWearTimer(7000);	@* 約19msec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(9000);	@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	FLA_LCD_SoftWearTimer(14000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	FLA_LCD_WriteInstruction((UBYTE)LCD_FUNCTION_SET);
	/** 4,1msec以上待つ */
/*	LCD_SoftWearTimer(2100);	@* 約6msec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(3000);	@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	FLA_LCD_SoftWearTimer(4200);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	FLA_LCD_WriteInstruction((UBYTE)LCD_FUNCTION_SET);
	/** 100usec以上待つ */
/*	LCD_SoftWearTimer(170);		@* 約566usec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(250);		@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	FLA_LCD_SoftWearTimer(340);		/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	FLA_LCD_WriteInstruction((UBYTE)LCD_FUNCTION_SET);
	/** 15msec以上待つ */
/*	LCD_SoftWearTimer(7000);	@* 約19msec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(9000);	@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	FLA_LCD_SoftWearTimer(14000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	FLA_LCD_WriteInstruction((UBYTE)LCD_FUNCTION_SET);
	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示ＯＦＦ */
	FLA_LCD_WriteInstruction((UBYTE)LCD_DISPLAY_OFF);
	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示クリア */
	FLA_LCD_WriteInstruction((UBYTE)LCD_CLEAR_DISPLAY);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME10MSEC);

	/** エントリーモードセット */
	FLA_LCD_WriteInstruction((UBYTE)LCD_ENTRY_MODE);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/* 注）POPLAR_Bでオールラムクリアを実行されると、モードだけコピーモードに初期化されてしまい、
	** 　　ＣＧＲＡＭは曜日表示用のままなので、CMN_InitializeAllBackUpRAM()でも初期化します
	*/

	FLA_LCD_SoftWearTimer(3000);	/* ここにウエイトを置かないとＣＧＲＡＭにうまくセットできない */
	/** ＣＧＲＡＭにデータをセット */
/*	InitializeCGRAM_Data();	*/

	/** 表示ＯＮ */
	FLA_LCD_WriteInstruction((UBYTE)LCD_DISPLAY_ON);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示クリア */
	FLA_LCD_WriteInstruction((UBYTE)LCD_CLEAR_DISPLAY);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME10MSEC);
}

/*************************************************************************
	module		:[ＬＣＤ上段に文字列を表示]
	function	:[
		1.LCDの上段の指定された位置に文字列を表示
		2.表示位置:０～１９
	]
	return		:[]
	common		:[
				DisplayBufferHigh
				SYS_LCD_DataPortStatus
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/21]
	author		:[江口]
*************************************************************************/
void FLA_DisplayStringHigh(UBYTE pos,		/*表示位置(0～19)*/
					   UBYTE *string)	/*表示文字列*/
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/** セマフォの獲得 1995/12/14*/
/*	wai_sem(semno.lcd);	*/

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	FLA_CursorOff();

	/*---------------------------------*/
	/** ファンクションセット(不要かも) */
	/*---------------------------------*/
#if (0)
	FLA_LCD_WriteInstruction((UBYTE)LCD_FUNCTION_SET);
#endif
	/* 表示されなかった為、コメント無効にしました。 97/08/11 By M.Kuwahara */
	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*--------------------------------------------*/
	/** DDRAMアドレスセット(表示開始位置のセット) */
	/*--------------------------------------------*/
	/* DDRAMを選択 */
	ddram_address = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;	/* DDRAM_FIRST_ROW_ADDRESS = 0x80*/
	FLA_LCD_WriteInstruction(ddram_address);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*---------------------------*/
	/** 表示文字列のアドレス変換 */
	/*---------------------------*/
/*	string = CalculateStringAddress(string); @* 1996/03/12 Eguchi */

	/*-----------------------*/
	/** 表示文字列の書き込み */
	/*-----------------------*/
	for (counter = 0; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;
		if (write_data == 0x00) {	/*NULLの場合書き込み終了(文字列の最後にはNULLをいれておく*/
			break;
		}

#if (0)
		/**特殊文字(Ⅰ,Ⅱ,Ⅲなど)に対する変換処理*/
		write_data = CheckSpecialCharacter(write_data);
#endif

		/*----------------------------------------*/
		/** 表示文字データの書き込み(ＬＣＤ表示） */
		/*----------------------------------------*/
		FLA_LCD_WriteData(write_data);
    	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}

	/** セマフォの解放 1995/12/14*/
/*	sig_sem(semno.lcd);	*/
}

/*************************************************************************
	module		:[ＬＣＤ下段に文字列を表示]
	function	:[
		1.LCD下段の指定された位置に文字列を表示
	]
	return		:[]
	common		:[
				DisplayBufferLow
				SYS_LCD_DataPortStatus
				]
	condition	:[点滅表示には使用しないこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void FLA_DisplayStringLow(UBYTE pos,		/*表示位置(0～19)*/
					  UBYTE *string)	/*表示文字列*/
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/** セマフォの獲得 1995/12/14*/
/*	wai_sem(semno.lcd);	*/

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	FLA_CursorOff();

#if (0)
	/*-----------------------*/
	/** ファンクションセット */
	/*-----------------------*/
	FLA_LCD_WriteInstruction(LCD_FUNCTION_SET);
#endif
	/* 表示されなかった為、コメント無効にしました。 97/07/19 By M.Kuwahara */
	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*----------------------------------------------*/
	/** DDRAMのアドレスセット(表示開始位置のセット) */
	/*----------------------------------------------*/
	ddram_address = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;	/*DDRAM_SECOND_ROW_ADDRESS = 0xc0*/
	FLA_LCD_WriteInstruction(ddram_address);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*---------------------------*/
	/** 表示文字列のアドレス変換 */
	/*---------------------------*/
/*	string = CalculateStringAddress(string); @* 1996/03/12 Eguchi */

	/*-----------------------*/
	/** 表示文字列の書き込み */
	/*-----------------------*/
	for (counter = 0; counter < OPR_DISPLAY_MAX; counter++) {
		write_data = *string++;
		if (write_data == 0x00) {	/*NULLの場合書き込み終了(文字列の最後にはNULLをいれておく*/
			break;
		}

#if (0)
		/**特殊文字(Ⅰ,Ⅱ,Ⅲなど)に対する変換処理*/
		write_data = CheckSpecialCharacter(write_data);
#endif

		/*ﾃﾞｰﾀの書き込み*/
		FLA_LCD_WriteData(write_data);
    	FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}

	/** 点滅表示を停止する 1995/12/16 Eguchi *//* 点滅中に点滅タスク以外のタスクが表示を書き換えるには点滅をやめる時であるとする */
/*	StopFunctionFlash();	*/

	/** セマフォの解放 1995/12/14*/
/*	sig_sem(semno.lcd);	*/
}

#if 0 /* 未使用 1998/04/17  By T.Yamaguchi  */
///*************************************************************************
//	module		:[指定された位置にカーソルを表示]
//	function	:[
//		1.引数で指定された位置にカーソルを表示させる
//		2.表示位置：上段→０～１９、下段→２０～３９
//	]
//	return		:[]
//	common		:[SYS_LCD_DataPortStatus]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/02/23]
//	author		:[江口]
//*************************************************************************/
//void FLA_CursorOn(UBYTE pos)	/*表示位置(0～39)*/
//{
//	UBYTE	ddram_adr;
//
//	/** セマフォの獲得 1995/12/14*/
///*	wai_sem(semno.lcd);	*/
//	/*-----------------------------------*/
//	/** カーソル表示位置のアドレスを計算 */
//	/*-----------------------------------*/
//	if (pos < 20) { /*上段*/
//		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
//	}
//	else {							/*下段*/
//		pos -= 20;
//		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
//	}
//	
//	/*----------------------*/
//	/** DDRAMアドレスセット */
//	/*----------------------*/
//	FLA_LCD_WriteInstruction(ddram_adr);
//    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
//
//	/*---------------*/
//	/** カーソル表示 */
//	/*---------------*/
//	FLA_LCD_WriteInstruction(LCD_CURSOR_ON);
//    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
//
//	/** セマフォの解放 1995/12/14*/
///*	sig_sem(semno.lcd);	*/
//}
#endif

/*************************************************************************
	module		:[カーソルＯＦＦ]
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
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void FLA_CursorOff(void)
{
	FLA_LCD_WriteInstruction(LCD_CURSOR_OFF);
    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
}

#if 0 /* 未使用 1998/04/17  By T.Yamaguchi */
///*************************************************************************
//	module		:[指定した位置に一文字表示]
//	function	:[
//		1.引数で指定された位置に一文字表示する
//		2.表示位置：上段ｰ>0～19､下段->20～39
//	]
//	return		:[]
//	common		:[SYS_LCD_DataPortStatus]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/02/23]
//	author		:[江口]
//*************************************************************************/
//void FLA_DisplayChar(UBYTE pos,			/*表示位置 0-39*/
//				 UBYTE dsp_char)	/*表示文字*/
//{
//	UBYTE	ddram_adr;
//
//	/** セマフォの獲得 1995/12/14*/
///*	wai_sem(semno.lcd);	*/
//
//	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
//	FLA_CursorOff();
//
//	/*-------------------------*/
//	/** 表示位置のアドレス計算 */
//	/*-------------------------*/
//	if (pos < 20) {
//		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
//	}
//	else {
//		pos -= 20;
//		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
//	}
//
//	/*----------------------------------------*/
//	/** DDRAMアドレスセット(表示位置のセット) */
//	/*----------------------------------------*/
//	FLA_LCD_WriteInstruction(ddram_adr);
//    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
//
//	
//	/*文字がNULLの場合終了*/
//	if (dsp_char == 0x00) {
//		return;
//	}
//
//#if (0)
//	/**特殊文字(Ⅰ,Ⅱ,Ⅲ,Ⅳなど）に対する処理*/
//	dsp_char = CheckSpecialCharacter(dsp_char);
//#endif
//
//	/*-------------*/
//	/** 文字を表示 */
//	/*-------------*/
//	FLA_LCD_WriteData(dsp_char);
//    FLA_LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
//
//	/** セマフォの解放 1995/12/14*/
///*	sig_sem(semno.lcd);	*/
//}
//
///*************************************************************************
//	module		:[ＬＣＤ上段表示クリア]
//	function	:[
//		1.LCD上段の表示をクリア(スペースを書き込む）
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/02/23]
//	author		:[江口,渡辺一章]
//*************************************************************************/
//void FLA_ClearDisplayHigh(void)
//{
//	UBYTE	clear_buffer[OPR_WORDING_LEN];
//
//	FLA_CMN_MemorySetNULL(clear_buffer, OPR_DISPLAY_MAX, ' ');
//	FLA_DisplayStringHigh(0, clear_buffer);
//}
//
///*************************************************************************
//	module		:[ＬＣＤ下段表示クリア]
//	function	:[
//		1.ＬＣＤ下段の表示をクリアする（スペースを書き込む）
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[OPR]
//	date		:[1995/02/23]
//	author		:[江口,渡辺一章]
//*************************************************************************/
//void FLA_ClearDisplayLow(void)
//{
//	UBYTE	clear_buffer[OPR_WORDING_LEN];
//
//	FLA_CMN_MemorySetNULL(clear_buffer, OPR_DISPLAY_MAX, ' ');
//	FLA_DisplayStringLow(0, clear_buffer);
//}
#endif

 #endif	/* #if (PRO_KEYPANEL !=PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */


#endif /* (PRO_PANEL == ANK) && (PRO_ANK_TO_KANJI == DISABLE) */

/***********************************
* 以下、グラフィックＬＣＤパネル用 *
* ディスプレイドライバ群           *
***********************************/
#if (PRO_PANEL == KANJI)

#if (0)
** /*************************************************************************
** 	module		:[ソフトウェアタイマー]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[ループ１回あたりの処理時間は約３usec（V53エミュレータ実測値)]
** 	machine		:[SH7043]
** 	language	:[SHC]
** 	keyword		:[OPR]
** 	date		:[1995/11/23]
** 	author		:[江口]
** *************************************************************************/
** void FLA_LCD_SoftWearTimer(UWORD time)
** {
** 	while (time > 0) {
** 		time--;
** 	}
** }
#endif


/*************************************************************************
	module		:[LCD表示の初期設定]
	function	:[
		1.フレームバッファのアドレスを指定する
		2.LCTCを1RAMグラフィックに設定する
		3.LCTCをリセットする
		4.全画面クリア
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/05/13]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_LCD_Initialize(void)
{
#if (0)
/*------- ＬＣＤＣ変更(MITUBISHI M66270FP) By M.Shimizu 1996/3/11 --------*/

	/**　ＶＲＡＭ のアドレスを指定 */

	FLA_LCD_Display = (UBYTE  *)&LCD_PageRAM[0];

	/** LCTCの内部レジスタの初期設定 */
	LCD_RegisterSet( LCTC_REG1, 0x18);						/* R1: モードレジスタ（1/8分周に設定) */
	LCD_RegisterSet( LCTC_REG2, LCD_WIDTH );				/* R2: 水平表示文字数 */
	LCD_RegisterSet( LCTC_REG3, 64 );						/* R3: 水平同期パルス幅 */

	/** 変更 -- No Wait区間を作る 1997/05/29 M.Shimizu */
	LCD_RegisterSet( LCTC_REG4, 2 );						/* R4: サイクルスチールイネーブル幅 */

	LCD_RegisterSet( LCTC_REG5, LCD_HEIGHT*LCD_DOT_LINE );	/* R5: 垂直ライン数 */
	LCD_RegisterSet( LCTC_REG6, 0 );						/* R6: 表示開始アドレス（下位）*/
	LCD_RegisterSet( LCTC_REG7, 0 );						/* R7: 表示開始アドレス（上位）*/
	LCD_RegisterSet( LCTC_REG8, 0 );						/* R8: Ｍ出力周期可変レジスタ */

	/** ＶＲＡＭのクリア */
	ClearDisplay();

	/** LCD表示開始 */
	LCD_RegisterSet( LCTC_REG1, 0x1c );

/*------------------------------------------------------------------------*/
#else
/*------- ＬＣＤＣ変更(MITUBISHI M66270FP) By M.Shimizu 1996/3/11 --------*/

	/**　ＶＲＡＭ のアドレスを指定 */

	FLA_LCD_Display = (UBYTE  *)&LCD_PageRAM[0];

	/** LCTCの内部レジスタの初期設定 */
	FLA_LCD_RegisterSet( LCTC_REG1, 0x18);						/* R1: モードレジスタ（1/8分周に設定) */
	FLA_LCD_RegisterSet( LCTC_REG2, LCD_WIDTH );				/* R2: 水平表示文字数 */
	FLA_LCD_RegisterSet( LCTC_REG3, 64 );						/* R3: 水平同期パルス幅 */

	/** 変更 -- No Wait区間を作る 1997/05/29 M.Shimizu */
	FLA_LCD_RegisterSet( LCTC_REG4, 2 );						/* R4: サイクルスチールイネーブル幅 */

	FLA_LCD_RegisterSet( LCTC_REG5, LCD_HEIGHT*LCD_DOT_LINE );	/* R5: 垂直ライン数 */
	FLA_LCD_RegisterSet( LCTC_REG6, 0 );						/* R6: 表示開始アドレス（下位）*/
	FLA_LCD_RegisterSet( LCTC_REG7, 0 );						/* R7: 表示開始アドレス（上位）*/
	FLA_LCD_RegisterSet( LCTC_REG8, 0 );						/* R8: Ｍ出力周期可変レジスタ */

	/** ＶＲＡＭのクリア */
	FLA_ClearDisplay();

	/** LCD表示開始 */
	FLA_LCD_RegisterSet( LCTC_REG1, 0x1c );

/*------------------------------------------------------------------------*/

#endif
}


/*************************************************************************
	module		:[1段目にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_DisplayString0(
		UBYTE  *string)	/* 表示するストリング */
{
#if (0)
	UWORD	count;
	UWORD * lcd_buf_ptr;
	
	lcd_buf_ptr = (UWORD *)(FLA_LCD_Display + (0 * LCD_DOT_LINE * LCD_WIDTH));

	for (count = 0; count < ((LCD_DOT_LINE * LCD_WIDTH)/2); count ++) {
			*(lcd_buf_ptr + count) = 0; /* FLA_LCD_Display->DotPattern[0][count2][count3] = 0; */
	}

	FLA_DisplayStringAttribute((UBYTE)0, string, ATTRIBUTE_NORMAL);
#else
	FLA_DisplayStringAttribute((UBYTE)0, string, ATTRIBUTE_NORMAL);
#endif
}


/*************************************************************************
	module		:[2段目にストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_DisplayString1(
		UBYTE  *string)	/* 表示するストリング */
{
#if (0)
	UWORD	count;
	UWORD * lcd_buf_ptr;
	
	lcd_buf_ptr = (UWORD *)(FLA_LCD_Display + (1 * LCD_DOT_LINE * LCD_WIDTH));
	for (count = 0; count < ((LCD_DOT_LINE * LCD_WIDTH)/2); count ++) {
		*(lcd_buf_ptr + count) = 0; /* FLA_LCD_Display->DotPattern[1][count2][count3] = 0; */
	}

	FLA_DisplayStringAttribute((UBYTE)30, string, ATTRIBUTE_NORMAL);
#else
	FLA_DisplayStringAttribute((UBYTE)30, string, ATTRIBUTE_NORMAL);
#endif
}


/*************************************************************************
	module		:[任意の位置にアトリビュートを加えてストリングを出力]
	function	:[
		1.ストリングがLCDの最右端を越える場合は、以下を表示しない
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_DisplayStringAttribute(
		UBYTE dsp_pos,		/* 表示する位置(0～119) */
		UBYTE  *string,	/* 入力するストリング   */
		UWORD attr)			/* 文字のアトリビュート */
{
#if (0)
	UBYTE x0;        /* x座標の初期値 */
	UBYTE xc;        /* x座標 */
	UBYTE yc;        /* y座標 */
	UBYTE c;
	UBYTE c1;

	/* string = CalculateStringAddress(string); */	/* マルチワーディングアドレス変換 By O.Kimoto 1997/09/18 */

	if (dsp_pos >= LCD_TOTAL_CHARACTERS) { /** 位置が120以上の場合 */
		return;              /** リターン */
	}
	yc = dsp_pos / LCD_WIDTH; /** 座標の算出 */
	x0 = dsp_pos % LCD_WIDTH;

	for (xc = x0; xc < LCD_WIDTH; xc++) { /** LCDの枠いっぱいに書き切るまでループ */
		c  = *(string + (xc - x0));
		c1 = *(string + (xc - x0) + 1);
		if (c == '\0') { /** NULLなら終了 */
			break;
		}

		FLA_GetByteCharacterDotPattern(xc, yc, c, attr); /** フレームバッファにドットパターンを格納 */
	}
#else
	UBYTE x0;        /* x座標の初期値 */
	UBYTE xc;        /* x座標 */
	UBYTE yc;        /* y座標 */
	UBYTE c;
	UBYTE c1;

#if (0)
	string = CalculateStringAddress(string);	/* マルチワーディングアドレス変換 By O.Kimoto 1997/09/18 */
#endif

	if (dsp_pos >= LCD_TOTAL_CHARACTERS) { /** 位置が120以上の場合 */
		return;              /** リターン */
	}

#if (0) /* ライブラリを使用しないように変更します 1998/06/01 by T.Soneoka */
**	yc = dsp_pos / LCD_WIDTH; /** 座標の算出 */
**	x0 = dsp_pos % LCD_WIDTH;
#else
	if ((dsp_pos >= 0) && (dsp_pos < LCD_WIDTH)) {
		yc = 0;
		x0 = dsp_pos;
	}
	else if ((dsp_pos >= LCD_WIDTH) && (dsp_pos < (LCD_WIDTH*2))) {
		yc = 1;
		x0 = dsp_pos - LCD_WIDTH;
	}
	else if (((dsp_pos >= (LCD_WIDTH*2)) && (dsp_pos < LCD_WIDTH*3))) {
		yc = 2;
		x0 = dsp_pos - (LCD_WIDTH*2);
	}
	else {
		yc = 3;
		x0 = dsp_pos - (LCD_WIDTH*3);
	}
#endif

	for (xc = x0; xc < LCD_WIDTH; xc++) { /** LCDの枠いっぱいに書き切るまでループ */
		c  = *(string + (xc - x0));
		c1 = *(string + (xc - x0) + 1);
		if (c == '\0') { /** NULLなら終了 */
			break;
		}

#if (0)
		if (c >= LCD_PICFONT && c1 == LCD_PICFONT_LOWER) {		/** 絵文字コードの場合 */
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', attr); /* 半角スペースを表示 */
				break; /** 終了 */
			}

			GetPictureFontDotPattern(xc, yc, (UBYTE)(c & 0xf), attr); /** 絵文字表示 */
			xc++; /** x座標を半角分進める */
			continue;
		}
		/* 第２水準対応 By O.Kimoto 1998/01/28 */
		if (CheckFontJIS2(c, c1)!= KANJI2_NONE) {
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', attr); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			Get2ndWordCharacterDotPattern(xc, yc, c, *(string + (xc - x0 + 1)), attr); /** フレームバッファにドットパターンを格納 */
			xc++; /** x座標を半角分進める */
		}
		else if (c >= WORD_CHARACTER_MIN && c <= WORD_CHARACTER_MAX) { /** 全角の場合(第1水準) */
			if (xc == LCD_WIDTH - 1) { /** 枠の1つ手前の場合 */
				GetByteCharacterDotPattern(xc, yc, ' ', attr); /* 半角スペースを表示 */
				break; /** 終了 */
			}
			GetWordCharacterDotPattern(xc, yc, c, *(string + (xc - x0 + 1)), attr); /** フレームバッファにドットパターンを格納 */
			xc++; /** x座標を半角分進める */
		}
		else { /** 半角の場合 */
			GetByteCharacterDotPattern(xc, yc, c, attr); /** フレームバッファにドットパターンを格納 */
		}
#else
		FLA_GetByteCharacterDotPattern(xc, yc, c, attr); /** フレームバッファにドットパターンを格納 */
#endif
	}
#endif
}


/*************************************************************************
	module		:[半角1文字分のドットパターンとアトリビュートをフレームバッファに格納]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_GetByteCharacterDotPattern(
		UBYTE xc,		/* LCD上の半角文字のx座標(0～29) */
		UBYTE yc,		/* LCD上の半角文字のy座標(0～3)  */
		UBYTE ascii,	/* 半角ASCIIコード               */
		UWORD attr)		/* 文字のアトリビュート          */
{
#if (0)
/*------- ＬＣＤＣ変更(MITUBISHI M66270FP) By M.Shimizu 1996/3/11 --------*/

	UBYTE reverse;		/* アトリビュートをソフトウェアで行うための変数 */
	UWORD voffset;		/* ＶＲＡＭの転送位置 */
	UWORD vrambit;
	UBYTE line;
	UWORD * putptr;

	reverse = 0;
	if( attr == ATTRIBUTE_REVERSE) {	/** アトリビュートが反転機能 */
     	reverse = 0xff;		/** ソフトウェア反転ビットＯＮ */
	}
	/*voffset = (yc*LCD_DOT_LINE*LCD_WIDTH + xc) - LCD_WIDTH;*/
	voffset = (yc*LCD_DOT_LINE*LCD_WIDTH + xc);

	/* 以下のインラインアセンブラは上記のようにＣ言語に戻しました By O.Kimoto 1997/08/13 */
	if( voffset & 1 ) {		/** 奇数バイトの書き込み */
		voffset &= 0xfffe;       	/** 転送位置をワード境界に合わせる */
		for (line = 0; line < 16; line++) {	/** １６ライン繰り替えす */
			putptr  = (UWORD *)(FLA_LCD_Display + voffset + (line*LCD_WIDTH)); /** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0x00ff) | (UWORD)(FLA_ByteFont[ascii][line] ^ reverse) << 8;
		}
	} else {
		for (line = 0; line < 16; line++) {	/** １６ライン繰り替えす */
			putptr  = (UWORD *)(FLA_LCD_Display + voffset + (line*LCD_WIDTH)); /** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0xff00) | (UWORD)(FLA_ByteFont[ascii][line] ^ reverse);
		}
	}

/*------------------------------------------------------------------------*/
#else
/*------- ＬＣＤＣ変更(MITUBISHI M66270FP) By M.Shimizu 1996/3/11 --------*/

	UBYTE reverse;		/* アトリビュートをソフトウェアで行うための変数 */
	UWORD voffset;		/* ＶＲＡＭの転送位置 */
	UWORD vrambit;
	UBYTE line;
	UWORD * putptr;

	reverse = 0;
	if( attr == ATTRIBUTE_REVERSE) {	/** アトリビュートが反転機能 */
     	reverse = 0xff;		/** ソフトウェア反転ビットＯＮ */
	}
	/*voffset = (yc*LCD_DOT_LINE*LCD_WIDTH + xc) - LCD_WIDTH;*/
	voffset = (yc*LCD_DOT_LINE*LCD_WIDTH + xc);

	/* 以下のインラインアセンブラは上記のようにＣ言語に戻しました By O.Kimoto 1997/08/13 */
	if( voffset & 1 ) {		/** 奇数バイトの書き込み */
		voffset &= 0xfffe;       	/** 転送位置をワード境界に合わせる */
		for (line = 0; line < 16; line++) {	/** １６ライン繰り替えす */
			putptr  = (UWORD *)(FLA_LCD_Display + voffset + (line*LCD_WIDTH)); /** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0x00ff) | (UWORD)(FLA_ByteFont[ascii][line] ^ reverse) << 8;
		}
	} else {
		for (line = 0; line < 16; line++) {	/** １６ライン繰り替えす */
			putptr  = (UWORD *)(FLA_LCD_Display + voffset + (line*LCD_WIDTH)); /** フォントデータを書き込む */
			vrambit = *putptr;
			*putptr = (vrambit & 0xff00) | (UWORD)(FLA_ByteFont[ascii][line] ^ reverse);
		}
	}

#if (0)
	/** 仮想フレームバッファへ出力 */
	LCD_VirtualFrameBuffer[yc][xc] = (attr & 0xff00) | ascii;
#endif

/*------------------------------------------------------------------------*/
#endif
}


/*************************************************************************
	module		:[全画面消去]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_ClearDisplay(void)
{
#if (0)
 	/* 以下のインラインアセンブラは上記のようにＣ言語に戻しました By O.Kimoto 1997/08/13 */
	UWORD	count1;
	UWORD	count2;
	UWORD * lcd_buf_ptr;
	
	lcd_buf_ptr = (UWORD *)(FLA_LCD_Display + (0 * LCD_DOT_LINE * LCD_WIDTH));
	
	for (count1 = 0; count1 < ((LCD_HEIGHT * LCD_DOT_LINE * LCD_WIDTH)/2); count1 ++) {
		*(lcd_buf_ptr + count1) = 0;	/* FLA_LCD_Display->DotPattern[count1][count2][count3] = 0; */
	}
#else
 	/* 以下のインラインアセンブラは上記のようにＣ言語に戻しました By O.Kimoto 1997/08/13 */
	UWORD	count1;
	UWORD	count2;
	UWORD * lcd_buf_ptr;
	
	lcd_buf_ptr = (UWORD *)(FLA_LCD_Display + (0 * LCD_DOT_LINE * LCD_WIDTH));
	
	for (count1 = 0; count1 < ((LCD_HEIGHT * LCD_DOT_LINE * LCD_WIDTH)/2); count1 ++) {
		*(lcd_buf_ptr + count1) = 0;	/* FLA_LCD_Display->DotPattern[count1][count2][count3] = 0; */
	}

#if (0)
	for (count1 = 0; count1 < LCD_HEIGHT; count1 ++) {
		for (count2 = 0; count2 < LCD_WIDTH; count2 ++) {
			LCD_VirtualFrameBuffer[count1][count2] = 0x20;
		}
	}
#endif
#endif
}

/*************************************************************************
	module		:[LCTCのレジスタのセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyward		:[OPR]
	date		:[1994/01/24]
	auther		:[石橋正和]
*************************************************************************/
void  FLA_LCD_RegisterSet(
		UDWORD address,	/* セットするレジスタのアドレス *//* Change UBYTE to UDWORD By O.Kimoto 1997/08/18 */
		UBYTE data)		/* セットするデータ */
{
/*------- ＬＣＤＣ変更(MITUBISHI M66270FP) By M.Shimizu 1996/3/11 --------*/
	FLA_outp(address,data);
/*------------------------------------------------------------------------*/
}
/* ＲＯＭ節約の為 1998/05/20 from 256 to 128 by T.Soneoka */
CONST unsigned char FLA_ByteFont[128][16] = {
              /*  SPC 00    */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  SPC 01    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  SPC 02    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  SPC 03    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  SPC 04    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  S(短縮用) */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x40,      /*  01000000  */
   0x20,      /*  00100000  */
   0x1C,      /*  00011100  */
   0x02,      /*  00000010  */
   0x01,      /*  00000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /* G(ｸﾞﾙｰﾌﾟ用)*/
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1E,      /*  00011110  */
   0x21,      /*  00100001  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x4F,      /*  01001111  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x21,      /*  00100001  */
   0x1E,      /*  00011110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  SPC 07    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x08 */
{              /*  SUN       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7E,      /*  01111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x7E,      /*  01111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x7E,      /*  01111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x09 */
{              /*  MON       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7E,      /*  01111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x7E,      /*  01111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x7E,      /*  01111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x82,      /*  10000010  */
   0x82,      /*  10000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x0A */
{              /*  TUE       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x92,      /*  10010010  */
   0x92,      /*  10010010  */
   0x92,      /*  10010010  */
   0x92,      /*  10010010  */
   0x10,      /*  00010000  */
   0x28,      /*  00101000  */
   0x28,      /*  00101000  */
   0x44,      /*  01000100  */
   0x44,      /*  01000100  */
   0x82,      /*  10000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x0B */
{              /*  WED       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x12,      /*  00010010  */
   0xF4,      /*  11110100  */
   0x38,      /*  00111000  */
   0x58,      /*  01011000  */
   0x54,      /*  01010100  */
   0x94,      /*  10010100  */
   0x12,      /*  00010010  */
   0x10,      /*  00010000  */
   0x30,      /*  00110000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x0C */
{              /*  THU       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0xFE,      /*  11111110  */
   0x38,      /*  00111000  */
   0x54,      /*  01010100  */
   0x54,      /*  01010100  */
   0x92,      /*  10010010  */
   0x92,      /*  10010010  */
   0x92,      /*  10010010  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x0D*/
{              /*  FRI       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x28,      /*  00101000  */
   0x44,      /*  01000100  */
   0xFE,      /*  11111110  */
   0x92,      /*  10010010  */
   0x10,      /*  00010000  */
   0x7C,      /*  01111100  */
   0x10,      /*  00010000  */
   0x54,      /*  01010100  */
   0x38,      /*  00111000  */
   0xFE,      /*  11111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x0E */
{              /*  SAT       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x7C,      /*  01111100  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0xFE,      /*  11111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x0F */
{              /*  YEAR      */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x40,      /*  01000000  */
   0x7E,      /*  01111110  */
   0x88,      /*  10001000  */
   0x08,      /*  00001000  */
   0x7C,      /*  01111100  */
   0x08,      /*  00001000  */
   0x48,      /*  01001000  */
   0x48,      /*  01001000  */
   0xFE,      /*  11111110  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x10 */
{
              /*  SPC 10    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x22,      /*  00100010  */
   0x77,      /*  01110111  */
   0x22,      /*  00100010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x11 */
{              /*  SPC 11    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x12 */
{              /*  SPC 12    */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x13 */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0xFF,      /*  11111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x14 */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0xFF      /*  11111111  */
},
/* 0x15 */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0F,      /*  00001111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x16 */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x0F,      /*  00001111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x17 */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x0F,      /*  00001111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x18 */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0xFF,      /*  11111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x19 */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0xFF,      /*  11111111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x1A */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0xFF,      /*  11111111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x1B */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0xFF,      /*  11111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x1C */
{
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0xF8,      /*  11111000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x1D */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0xF8,      /*  11111000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x1E */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0xF8,      /*  11111000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x1F */
{
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08      /*  00001000  */
},
/* 0x20 */
{             /*  SPC       */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x21 */
{              /*  !         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x22 */
{              /*  "         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x14,      /*  00010100  */
   0x14,      /*  00010100  */
   0x14,      /*  00010100  */
   0x14,      /*  00010100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x23 */
{              /*  #         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x7F,      /*  01111111  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x7F,      /*  01111111  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x24 */
{              /*  $         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x14,      /*  00010100  */
   0x3E,      /*  00111110  */
   0x55,      /*  01010101  */
   0x54,      /*  01010100  */
   0x54,      /*  01010100  */
   0x3E,      /*  00111110  */
   0x15,      /*  00010101  */
   0x15,      /*  00010101  */
   0x55,      /*  01010101  */
   0x3E,      /*  00111110  */
   0x14,      /*  00010100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x25 */
{              /*  %         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x30,      /*  00110000  */
   0x48,      /*  01001000  */
   0x49,      /*  01001001  */
   0x32,      /*  00110010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x26,      /*  00100110  */
   0x49,      /*  01001001  */
   0x09,      /*  00001001  */
   0x06,      /*  00000110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x26 */
{              /*  &         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x38,      /*  00111000  */
   0x44,      /*  01000100  */
   0x44,      /*  01000100  */
   0x44,      /*  01000100  */
   0x28,      /*  00101000  */
   0x30,      /*  00110000  */
   0x48,      /*  01001000  */
   0x45,      /*  01000101  */
   0x42,      /*  01000010  */
   0x25,      /*  00100101  */
   0x18,      /*  00011000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x27 */
{              /*  '         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x0C,      /*  00001100  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x28 */
{              /*  (         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x20,      /*  00100000  */
   0x20,      /*  00100000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00	      /*  00000000  */
},
/* 0x29 */
{              /*  )         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00 	  /*  00000000  */
},
/* 0x2A */
{              /*  *         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x49,      /*  01001001  */
   0x2A,      /*  00101010  */
   0x1C,      /*  00011100  */
   0x2A,      /*  00101010  */
   0x49,      /*  01001001  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x2B */
{              /*  +         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x7F,      /*  01111111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x2C */
{              /*  ,         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x0C,      /*  00001100  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x2D */
{              /*  -         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x2E */
{              /*  .         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x30,      /*  00110000  */
   0x30,      /*  00110000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x2F */
{              /*  /         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x01,      /*  00000001  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x40,      /*  01000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x30 */
{              /*  0         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00       /*  00000000  */
},
/* 0x31 */
{              /*  1         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x18,      /*  00011000  */
   0x28,      /*  00101000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x3E,      /*  00111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x32 */
{              /*  2         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x7E,      /*  01111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x33 */
{              /*  3         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x02,      /*  00000010  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x34 */
{              /*  4         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x06,      /*  00000110  */
   0x0A,      /*  00001010  */
   0x0A,      /*  00001010  */
   0x12,      /*  00010010  */
   0x12,      /*  00010010  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x42,      /*  01000010  */
   0x7F,      /*  01111111  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x35 */
{              /*  5         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7E,      /*  01111110  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7C,      /*  01111100  */
   0x02,      /*  00000010  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x42,      /*  01000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x36 */
{              /*  6         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1E,      /*  00011110  */
   0x20,      /*  00100000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x37 */
{              /*  7         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x38 */
{              /*  8         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x39 */
{              /*  9         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x23,      /*  00100011  */
   0x1D,      /*  00011101  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x02,      /*  00000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x3A */
{              /*  :         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x0C,      /*  00001100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x0C,      /*  00001100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x3B */
{              /*  ;         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x0C,      /*  00001100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x0C,      /*  00001100  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x3C */
{              /*  <         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x40,      /*  01000000  */
   0x20,      /*  00100000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x02,      /*  00000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x3D */
{              /*  =         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x3E */
{              /*  >         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x20,      /*  00100000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x02,      /*  00000010  */
   0x01,      /*  00000001  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x3F */
{              /*  ?         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x40 */
{              /*  @         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x01,      /*  00000001  */
   0x19,      /*  00011001  */
   0x29,      /*  00101001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x2A,      /*  00101010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x41 */
{              /*  A         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x7F,      /*  01111111  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x42 */
{              /*  B         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7E,      /*  01111110  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x3E,      /*  00111110  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x7E,      /*  01111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x43 */
{              /*  C         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1E,      /*  00011110  */
   0x21,      /*  00100001  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x21,      /*  00100001  */
   0x1E,      /*  00011110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x44 */
{              /*  D         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7C,      /*  01111100  */
   0x22,      /*  00100010  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x21,      /*  00100001  */
   0x22,      /*  00100010  */
   0x7C,      /*  01111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x45 */
{              /*  E         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7C,      /*  01111100  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x46 */
{              /*  F         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7C,      /*  01111100  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x47 */
{              /*  G         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1E,      /*  00011110  */
   0x21,      /*  00100001  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x4F,      /*  01001111  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x21,      /*  00100001  */
   0x1E,      /*  00011110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x48 */
{              /*  H         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x7F,      /*  01111111  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x49 */
{              /*  I         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3E,      /*  00111110  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x3E,      /*  00111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x4A */
{              /*  J         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1F,      /*  00011111  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x44,      /*  01000100  */
   0x38,      /*  00111000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x4B */
{              /*  K         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x42,      /*  01000010  */
   0x44,      /*  01000100  */
   0x48,      /*  01001000  */
   0x50,      /*  01010000  */
   0x60,      /*  01100000  */
   0x50,      /*  01010000  */
   0x48,      /*  01001000  */
   0x44,      /*  01000100  */
   0x42,      /*  01000010  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x4C */
{              /*  L         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x4D */
{              /*  M         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x63,      /*  01100011  */
   0x55,      /*  01010101  */
   0x55,      /*  01010101  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x4E */
{              /*  N         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x61,      /*  01100001  */
   0x51,      /*  01010001  */
   0x51,      /*  01010001  */
   0x49,      /*  01001001  */
   0x45,      /*  01000101  */
   0x45,      /*  01000101  */
   0x43,      /*  01000011  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x4F */
{              /*  O         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3E,      /*  00111110  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x3E,      /*  00111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x50 */
{              /*  P         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7C,      /*  01111100  */
   0x42,      /*  01000010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x42,      /*  01000010  */
   0x7C,      /*  01111100  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x51 */
{              /*  Q         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x49,      /*  01001001  */
   0x45,      /*  01000101  */
   0x22,      /*  00100010  */
   0x1D,      /*  00011101  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x52 */
{              /*  R         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7C,      /*  01111100  */
   0x42,      /*  01000010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x42,      /*  01000010  */
   0x7C,      /*  01111100  */
   0x50,      /*  01010000  */
   0x48,      /*  01001000  */
   0x44,      /*  01000100  */
   0x42,      /*  01000010  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x53 */
{              /*  S         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1C,      /*  00011100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x40,      /*  01000000  */
   0x20,      /*  00100000  */
   0x1C,      /*  00011100  */
   0x02,      /*  00000010  */
   0x01,      /*  00000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x54 */
{              /*  T         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x55 */
{              /*  U         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x56 */
{              /*  V         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x14,      /*  00010100  */
   0x14,      /*  00010100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x57 */
{              /*  W         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x36,      /*  00110110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x58 */
{              /*  X         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x14,      /*  00010100  */
   0x08,      /*  00001000  */
   0x14,      /*  00010100  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x59 */
{              /*  Y         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x14,      /*  00010100  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x5A */
{              /*  Z         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x01,      /*  00000001  */
   0x01,      /*  00000001  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x5B */
{              /*  [         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x1E,      /*  00011110  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x1E,      /*  00011110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x5C */
{              /*  \         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x14,      /*  00010100  */
   0x7f,      /*  01111111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x7f,      /*  01111111  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x5D */
{              /*  ]         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x5E */
{              /*  ^         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x14,      /*  00010100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x5F */
{              /*  _         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7F,      /*  01111111  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x60 */
{              /*  `         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x40,      /*  01000000  */
   0x20,      /*  00100000  */
   0x10,      /*  00010000  */
   0x08,      /*  00001000  */
   0x04,      /*  00000100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
/* 0x61 */
{              /*  a         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x3E,      /*  00111110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x3D,      /*  00111101  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  b         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x62,      /*  01100010  */
   0x5C,      /*  01011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  c         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x42,      /*  01000010  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x42,      /*  01000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  d         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x3A,      /*  00111010  */
   0x46,      /*  01000110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x46,      /*  01000110  */
   0x3A,      /*  00111010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  e         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x7E,      /*  01111110  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x42,      /*  01000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  f         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x12,      /*  00010010  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x7C,      /*  01111100  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  g         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3A,      /*  00111010  */
   0x46,      /*  01000110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x46,      /*  01000110  */
   0x3A,      /*  00111010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x42,      /*  01000010  */
   0x3C      /*  00111100  */
},
{              /*  h         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  i         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x18,      /*  00011000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  j         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x00,      /*  00000000  */
   0x06,      /*  00000110  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x44,      /*  01000100  */
   0x38      /*  00111000  */
},
{              /*  k         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x42,      /*  01000010  */
   0x44,      /*  01000100  */
   0x48,      /*  01001000  */
   0x50,      /*  01010000  */
   0x70,      /*  01110000  */
   0x48,      /*  01001000  */
   0x44,      /*  01000100  */
   0x42,      /*  01000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  l         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x18,      /*  00011000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x1C,      /*  00011100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  m         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x36,      /*  00110110  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  n         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  o         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  p         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x62,      /*  01100010  */
   0x5C,      /*  01011100  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40      /*  01000000  */
},
{              /*  q         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3A,      /*  00111010  */
   0x46,      /*  01000110  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x46,      /*  01000110  */
   0x3A,      /*  00111010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x01      /*  00000001  */
},
{              /*  r         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x5C,      /*  01011100  */
   0x62,      /*  01100010  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x40,      /*  01000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  s         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x3C,      /*  00111100  */
   0x42,      /*  01000010  */
   0x40,      /*  01000000  */
   0x30,      /*  00110000  */
   0x0C,      /*  00001100  */
   0x02,      /*  00000010  */
   0x42,      /*  01000010  */
   0x3C,      /*  00111100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  t         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x7C,      /*  01111100  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x12,      /*  00010010  */
   0x0C,      /*  00001100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  u         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x46,      /*  01000110  */
   0x39,      /*  00111001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  v         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x22,      /*  00100010  */
   0x14,      /*  00010100  */
   0x14,      /*  00010100  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  w         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x41,      /*  01000001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x49,      /*  01001001  */
   0x36,      /*  00110110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  x         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x41,      /*  01000001  */
   0x22,      /*  00100010  */
   0x14,      /*  00010100  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x14,      /*  00010100  */
   0x22,      /*  00100010  */
   0x41,      /*  01000001  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  y         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x42,      /*  01000010  */
   0x46,      /*  01000110  */
   0x3A,      /*  00111010  */
   0x02,      /*  00000010  */
   0x02,      /*  00000010  */
   0x44,      /*  01000100  */
   0x38      /*  00111000  */
},
{              /*  z         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x7E,      /*  01111110  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x08,      /*  00001000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x40,      /*  01000000  */
   0x7E,      /*  01111110  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  {         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x0C,      /*  00001100  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x20,      /*  00100000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x10,      /*  00010000  */
   0x0C,      /*  00001100  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  |         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*  }         */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x18,      /*  00011000  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x02,      /*  00000010  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x04,      /*  00000100  */
   0x18,      /*  00011000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*            */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x06,      /*  00000110  */
   0x7F,      /*  01111111  */
   0x06,      /*  00000110  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
},
{              /*            */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x08,      /*  00001000  */
   0x30,      /*  00110000  */
   0x7F,      /*  01111111  */
   0x30,      /*  00110000  */
   0x08,      /*  00001000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00,      /*  00000000  */
   0x00      /*  00000000  */
}

#if (0) /* ＲＯＭ節約の為 1998/05/20 by T.Soneoka */
**/*--------------------------*/
**/* 0x80 ～ 0x9F 未使用		*/
**/* 全てスペース				*/
**/*--------------------------*/
**/* 0x80 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x81 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x82 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x83 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x84 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x85 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x86 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x87 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x88 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x89 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x8A */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x8B */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x8C */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x8D */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x8E */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x8F */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x90 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x91 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x92 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x93 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x94 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x95 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0X96 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x97 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x98 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x99 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x9A */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x9B */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x9C */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x9D */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x9E */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0x9F */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA0  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA1  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x60,      /*  01100000  */
**   0x90,      /*  10010000  */
**   0x90,      /*  10010000  */
**   0x60,      /*  01100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA2  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7E,      /*  01111110  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA3  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0xFC,      /*  11111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA4  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x80,      /*  10000000  */
**   0x40,      /*  01000000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA5  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x18,      /*  00011000  */
**   0x18,      /*  00011000  */
**   0x18,      /*  00011000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA6   ｦ*/
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA7   ｧ*/
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7C,      /*  01111100  */
**   0x04,      /*  00000100  */
**   0x24,      /*  00100100  */
**   0x28,      /*  00101000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA8   ｨ*/
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x30,      /*  00110000  */
**   0x50,      /*  01010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xA9  */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x7C,      /*  01111100  */
**   0x44,      /*  01000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xAA */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x38,      /*  00111000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x7C,      /*  01111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xAB */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x08,      /*  00001000  */
**   0x7C,      /*  01111100  */
**   0x08,      /*  00001000  */
**   0x18,      /*  00011000  */
**   0x18,      /*  00011000  */
**   0x28,      /*  00101000  */
**   0x48,      /*  01001000  */
**   0x08,      /*  00001000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xAC */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x20,      /*  00100000  */
**   0x7C,      /*  01111100  */
**   0x24,      /*  00100100  */
**   0x28,      /*  00101000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xAD */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x38,      /*  00111000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x3C,      /*  01111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xAE */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7C,      /*  01111100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x7C,      /*  01111100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x7C,      /*  01111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xAF */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x54,      /*  01010100  */
**   0x54,      /*  01010100  */
**   0x54,      /*  01010100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB0 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB1 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x14,      /*  00010100  */
**   0x18,      /*  00011000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x80,      /*  10000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB2 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x30,      /*  00110000  */
**   0x50,      /*  01010000  */
**   0x90,      /*  10010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB3 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x30,      /*  00110000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB4 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7C,      /*  01111100  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB5 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0xFE,      /*  11111110  */
**   0x08,      /*  00001000  */
**   0x18,      /*  00011000  */
**   0x18,      /*  00011000  */
**   0x28,      /*  00101000  */
**   0x28,      /*  00101000  */
**   0x48,      /*  01001000  */
**   0x48,      /*  01001000  */
**   0x88,      /*  10001000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB6 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0xFE,      /*  11111110  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x42,      /*  01000010  */
**   0x44,      /*  01000100  */
**   0x88,      /*  10001000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB7 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB8 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x3E,      /*  00111110  */
**   0x22,      /*  00100010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x82,      /*  10000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0xC0,      /*  11000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xB9 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x7E,      /*  01111110  */
**   0x84,      /*  10000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xBA */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xBB */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x44,      /*  01000100  */
**   0x44,      /*  01000100  */
**   0xFE,      /*  11111110  */
**   0x44,      /*  01000100  */
**   0x44,      /*  01000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xBC */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xE0,      /*  11100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xE0,      /*  11100000  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0xE0,      /*  11100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xBD */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x18,      /*  00011000  */
**   0x14,      /*  00010100  */
**   0x24,      /*  00100100  */
**   0x42,      /*  01000010  */
**   0x82,      /*  10000010  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xBE */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0xFE,      /*  11111110  */
**   0x42,      /*  01000010  */
**   0x44,      /*  01000100  */
**   0x48,      /*  01001000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x20,      /*  00100000  */
**   0x1E,      /*  00011110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xBF */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x82,      /*  10000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x60,      /*  01100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC0 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x3E,      /*  00111110  */
**   0x22,      /*  00100010  */
**   0x62,      /*  01100010  */
**   0x92,      /*  10010010  */
**   0x0A,      /*  00001010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC1 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0xF0,      /*  11110000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x80,      /*  10000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC2 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC3 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7C,      /*  01111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC4 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x30,      /*  00110000  */
**   0x28,      /*  00101000  */
**   0x24,      /*  00100100  */
**   0x22,      /*  00100010  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC5 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC6 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7C,      /*  01111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC7 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0xC8,      /*  11001000  */
**   0x28,      /*  00101000  */
**   0x10,      /*  00010000  */
**   0x18,      /*  00011000  */
**   0x24,      /*  00100100  */
**   0x42,      /*  01000010  */
**   0x82,      /*  10000010  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC8 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x18,      /*  00011000  */
**   0x34,      /*  00110100  */
**   0xD2,      /*  11010010  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xC9 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0xC0,      /*  11000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xCA */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x08,      /*  00001000  */
**   0x04,      /*  00000100  */
**   0x44,      /*  01000100  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x82,      /*  10000010  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xCB */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0xFE,      /*  11111110  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x40,      /*  01000000  */
**   0x3E,      /*  00111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xCC */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xCD */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x20,      /*  00100000  */
**   0x50,      /*  01010000  */
**   0x48,      /*  01001000  */
**   0x88,      /*  10001000  */
**   0x84,      /*  10000100  */
**   0x04,      /*  00000100  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xCE */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0xFE,      /*  11111110  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x54,      /*  01010100  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x92,      /*  10010010  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xCF */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x50,      /*  01010000  */
**   0x30,      /*  00110000  */
**   0x10,      /*  00010000  */
**   0x08,      /*  00001000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD0 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x80,      /*  10000000  */
**   0x60,      /*  01100000  */
**   0x18,      /*  00011000  */
**   0x86,      /*  10000110  */
**   0x60,      /*  01100000  */
**   0x18,      /*  00011000  */
**   0x06,      /*  00000110  */
**   0x80,      /*  10000000  */
**   0x60,      /*  01100000  */
**   0x18,      /*  00011000  */
**   0x06,      /*  00000110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD1 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**   0x48,      /*  01001000  */
**   0x84,      /*  10000100  */
**   0x82,      /*  10000010  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD2 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x24,      /*  00100100  */
**   0x14,      /*  00010100  */
**   0x08,      /*  00001000  */
**   0x14,      /*  00010100  */
**   0x22,      /*  00100010  */
**   0x40,      /*  01000000  */
**   0x80,      /*  10000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD3 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0xFE,      /*  11111110  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x1E,      /*  00011110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD4 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0xFE,      /*  11111110  */
**   0x22,      /*  00100010  */
**   0x24,      /*  00100100  */
**   0x28,      /*  00101000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD5 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xF8,      /*  11111000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0x08,      /*  00001000  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD6 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD7 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x7C,      /*  01111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD8 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xD9 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x50,      /*  01010000  */
**   0x50,      /*  01010000  */
**   0x50,      /*  01010000  */
**   0x50,      /*  01010000  */
**   0x50,      /*  01010000  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x52,      /*  01010010  */
**   0x54,      /*  01010100  */
**   0x58,      /*  01011000  */
**   0x90,      /*  10010000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xDA */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x80,      /*  10000000  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x84,      /*  10000100  */
**   0x88,      /*  10001000  */
**   0x90,      /*  10010000  */
**   0xA0,      /*  10100000  */
**   0xC0,      /*  11000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xDB */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0xFE,      /*  11111110  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xDC */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xFE,      /*  11111110  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x82,      /*  10000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0x20,      /*  00100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xDD */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xE0,      /*  11100000  */
**   0x00,      /*  00000000  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x04,      /*  00000100  */
**   0x04,      /*  00000100  */
**   0x08,      /*  00001000  */
**   0x10,      /*  00010000  */
**   0xE0,      /*  11100000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xDE */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0xA0,      /*  10100000  */
**   0x50,      /*  01010000  */
**   0x28,      /*  00101000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xDF */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x18,      /*  00011000  */
**   0x24,      /*  00100100  */
**   0x24,      /*  00100100  */
**   0x18,      /*  00011000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**
**/*0xE0*/
**{
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x31,	/*  00110001  */
**	0x4A,	/*  01001010  */
**	0x44,	/*  01000100  */
**	0x44,	/*  01000100  */
**	0x44,	/*  01000100  */
**	0x44,	/*  01000100  */
**	0x4A,	/*  01001010  */
**	0x31,	/*  00110001  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**},
**
**/* 0xE1 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x42,      /*  00100010  */
**   0x42,      /*  00100010  */
**   0x00,      /*  00000000  */
**   0x3C,      /*  00111100  */
**   0x02,      /*  00000010  */
**   0x02,      /*  00000010  */
**   0x3E,      /*  00111110  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x3D,      /*  00111101  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**
**/* 0xE2*/
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x18,      /*  00011000  */
**   0x24,      /*  00100100  */
**   0x42,      /*  01000010  */
**   0x44,      /*  01000100  */
**   0x58,      /*  01011000  */
**   0x44,      /*  01000100  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x4C,      /*  01001100  */
**   0x40,      /*  01000000  */
**   0x40,      /*  01000000  */
**   0x40      /*  01000000  */
**},
**
**/* 0xE3 */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x3E,	/* 00111110 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x3C,	/* 00111100 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x3E,	/* 00111110 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xE4 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x22,      /*  00100010  */
**   0x3D,      /*  00111101  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x20,      /*  00100000  */
**   0x40,      /*  01000000  */
**},
**
**/* 0xE5 */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x0C,      /*  00001100  */
**   0x10,      /*  00010000  */
**   0x08,      /*  00001000  */
**   0x04,      /*  00000100  */
**   0x1C,      /*  00011100  */
**   0x22,      /*  00100010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x24,      /*  00100100  */
**   0x18,      /*  00011000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**},
**
**/* 0xE6 */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x0E,	/* 00001110 */
**	0x11,	/* 00010001 */
**	0x21,	/* 00100001 */
**	0x61,	/* 01100001 */
**	0x5E,	/* 01011110 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xE7 */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x3F,	/* 00111111 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41 ,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x3F,	/* 00111111 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x02,	/* 00000010 */
**	0x7C,	/* 01111100 */
**},
**/*0xE8*/
**{
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x0F,	/*  00001111  */
**	0x08,	/*  00001000  */
**	0x08,	/*  00001000  */
**	0x08,	/*  00001000  */
**	0x08,	/*  00001000  */
**	0x08,	/*  00001000  */
**	0x08,	/*  00001000  */
**	0x48,	/*  01001000  */
**	0x28,	/*  00101000  */
**	0x18,	/*  00011000  */
**	0x08,	/*  00001000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00	/*  00000000  */
**},
**
**/* 0xE9 */
**{ 
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x7A,	/* 01111010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**/* 0xEA */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x00,	/* 00000000 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x02,	/* 00000010 */
**	0x42,	/* 01000010 */
**	0x44,	/* 01000100 */
**	0x38	/* 00111000 */
**},
**/* 0xEB */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x44,	/* 01000100 */
**	0x28,	/* 00101000 */
**	0x10,	/* 00010000 */
**	0x28,	/* 00101000 */
**	0x44,	/* 01000100 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**/* 0xEC */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x3E,	/* 00111110 */
**	0x48,	/* 01001000 */
**	0x48,	/* 01001000 */
**	0x49,	/* 01001001 */
**	0x3E ,	/* 00111110 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xED */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x20,	/* 00100000 */
**	0x20,	/* 00100000 */
**	0x20,	/* 00100000 */
**	0x7C,	/* 01111100 */
**	0x20,	/* 00100000 */
**	0x20,	/* 00100000 */
**	0x7C,	/* 01111100 */
**	0x20,	/* 00100000 */
**	0x20,	/* 00100000 */
**	0x20,	/* 00100000 */
**	0x3F,	/* 00111111 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**/* 0xEE */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x3E,	/* 01111110 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x5C,	/* 01011100 */
**	0x62,	/* 01100010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00 	/* 00000000 */
**},
**/* 0xEF */
**{
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x3C,      /*  00111100  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x42,      /*  01000010  */
**   0x3C,      /*  00111100  */
**   0x00,      /*  00000000  */
**   0x00,      /*  00000000  */
**   0x00      /*  00000000  */
**},
**/* 0xF0 */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x40,	/* 01000000 */
**	0x5E,	/* 01011110 */
**	0x61,	/* 01100001 */
**	0x61,	/* 01100001 */
**	0x60,	/* 01100001 */
**	0x5E,	/* 01011110 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40,	/* 01000000 */
**	0x40	/* 01000000 */
**},
**/* 0xF1 */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000001 */
**	0x3D,	/* 00111101 */
**	0x43,	/* 01000011 */
**	0x43,	/* 01000011 */
**	0x43,	/* 01000011 */
**	0x3D,	/* 00111101 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x01	/* 00000001 */
**},
**/* 0xF2*/
**{
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x08,	/*  00001000  */
**	0x14,	/*  00010100  */
**	0x22,	/*  00100010  */
**	0x22,	/*  00100010  */
**	0x22 ,	/*  00100010  */
**	0x3E,	/*  00111110  */
**	0x22,	/*  00100010  */
**	0x22,	/*  00100010  */
**	0x22,	/*  00100010  */
**	0x14,	/*  00010100  */
**	0x08,	/*  00001000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00 	/*  00000000  */
**},
**/* 0xF3*/
**{
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x36,	/*  00110110  */
**	0x49,	/*  01001001  */
**	0x49,	/*  01001001  */
**	0x49,	/*  01001001  */
**	0x36,	/*  00110110  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00	/*  00000000  */
**},
**/* 0xF4*/
**{
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x1C,	/*  00011100  */
**	0x22,	/*  00100010  */
**	0x41,	/*  01000001  */
**	0x41,	/*  01000001  */
**	0x41,	/*  01000001  */
**	0x41,	/*  01000001  */
**	0x22,	/*  00100010  */
**	0x14,	/*  00010100  */
**	0x55,	/*  01010101  */
**	0x77,	/*  01110111  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00	/*  00000000  */
**},
**/* 0xF5 */
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x42,	/* 01000010 */
**	0x3D,	/* 00111101 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**/* 0xF6*/
**{
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x7F,	/*  01111111  */
**	0x41,	/*  01000001  */
**	0x20,	/*  00100000  */
**	0x10,	/*  00010000  */
**	0x08,	/*  00001000  */
**	0x04 ,	/*  00000100  */
**	0x08,	/*  00001000  */
**	0x10,	/*  00010000  */
**	0x20,	/*  00100000  */
**	0x41,	/*  01000001  */
**	0x7F,	/*  01111111  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00	/*  00000000  */
**},
**/* 0xF7*/
**{
**
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x3F,	/*  00111111  */
**	0x52 ,	/*  01010010  */
**	0x12,	/*  00010010  */
**	0x12,	/*  00010010  */
**	0x12,	/*  00010010  */
**	0x12,	/*  00010010  */
**	0x12,	/*  00010010  */
**	0x00,	/*  00000000  */
**	0x00,	/*  00000000  */
**	0x00	/*  00000000  */
**},
**/* 0xF8*/
**{
**
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x3F,	/* 01111111 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x41,	/* 01000001 */
**	0x22,	/* 00100010 */
**	0x14,	/* 00010100 */
**	0x08,	/* 00001000 */
**	0x14,	/* 00010100 */
**	0x22,	/* 00100010 */
**	0x41,	/* 01000001 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xF9*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x3F,	/* 00111111 */
**	0x01,	/* 00000001 */
**	0x01,	/* 00000001 */
**	0x02,	/* 00000010 */
**	0x7C 	/* 01111100 */
**},
**/* 0xFA*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x01,	/* 00000001 */
**	0x02,	/* 00000010 */
**	0x7C,	/* 01111100 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x7F,	/* 01111111 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x08,	/* 00001000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**/* 0xFB*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x7F,	/* 01111111 */
**	0x10,	/* 00010000 */
**	0x10,	/* 00010000 */
**	0x10,	/* 00010000 */
**	0x1F,	/* 00011111 */
**	0x11,	/* 00010001 */
**	0x11,	/* 00010001 */
**	0x11,	/* 00010001 */
**	0x11,	/* 00010001 */
**	0x22,	/* 00100010 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xFC*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x7F,	/* 01111111 */
**	0x49,	/* 01001001 */
**	0x49,	/* 01001001 */
**	0x49,	/* 01001001 */
**	0x49,	/* 01001001 */
**	0x7F,	/* 01111111 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x41,	/* 01000001 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xFD*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00, 	/* 00000000 */
**	0x18,	/* 00011000 */
**	0x24,	/* 00100100 */
**	0x24,	/* 00100100 */
**	0x18,	/* 00011000 */
**	0x00,	/* 00000000 */
**	0x7E,	/* 01111110 */
**	0x00,	/* 00000000 */
**	0x18,	/* 00011000 */
**	0x24,	/* 00100100 */
**	0x24,	/* 00100100 */
**	0x18,	/* 00011000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xFE*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**},
**
**/* 0xFF*/
**{
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x7F,	/* 01111111 */
**	0x00,	/* 00000000 */
**	0x00,	/* 00000000 */
**	0x00	/* 00000000 */
**}
#endif
};
#endif /* PRO_PANEL == KANJI */

#endif /* PRO_RDS_FLASH_ROM_WRITE == ENABLE */
#pragma section
