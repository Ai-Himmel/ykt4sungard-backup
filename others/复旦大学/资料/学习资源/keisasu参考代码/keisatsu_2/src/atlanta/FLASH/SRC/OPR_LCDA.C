/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_LCD.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ＬＣＤドライバーモジュール
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"

#include "\src\atlanta\flash\define\sys_pro.h"
#include "\src\atlanta\flash\ext_v\sys_data.h"

#if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined (HINOKI3) /* HINOKI2 2001/11/13 T.Takagi */
#else
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
void LCD_SoftWearTimer(UWORD time)
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
void LCD_WriteInstruction(UBYTE instruction)
{
	/*--------------------------*/
	/*RS ->0:IR Registerを選択	*/
	/*R/W->0:Writeに設定		*/
	/*ENABLE->0					*/
	/*--------------------------*/
	SYS_LCDC_PortStatus &= ~(IO_BIT_RS | IO_BIT_R_W | IO_BIT_E);
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*---------------------------*/
	/*ENABLE->1					 */
	/*ﾃﾞｰﾀ書き込み開始			 */
	/*---------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_E;
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*---------------------------------------------------*/
	/*IR Registerにﾃﾞｰﾀ書き込み	    					 */
	/*---------------------------------------------------*/
	SYS_LCD_DataPortStatus = instruction;
	outpw(LCD_DATA_PORT, (UWORD)SYS_LCD_DataPortStatus);

	/*----------------------------*/
	/*ENABLE -> 0				  */
	/*ﾃﾞｰﾀ書き込み終了			  */
	/*LCDC内部動作開始(Busyｾｯﾄ)	  */
	/*----------------------------*/
	SYS_LCDC_PortStatus &= ~IO_BIT_E;
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
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
void LCD_BusyFlagWait(UWORD time)	/*ループ回数(待ち時間 500 or 200）*/
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
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	for ( ;time > 0; time--) {
		/*---------------------------*/
		/* ENABLE -> 1				 */
		/* ﾃﾞｰﾀ読み込み開始			 */
		/*---------------------------*/
		SYS_LCDC_PortStatus |= IO_BIT_E;
		outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

		LCD_SoftWearTimer(2);	/* 最低で220nsウェイトを置く By M.Tachibana 1997/05/12 */

		/*----------------------------*/
		/*ﾃﾞｰﾀ(BusyFlag)読み込み	  */
		/*----------------------------*/
		busy = (UBYTE)inpw(LCD_BUSY_PORT);

		/*----------------------------*/
		/*ENABLE -> 0				  */
		/*----------------------------*/
		SYS_LCDC_PortStatus &= ~IO_BIT_E;
		outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
		LCD_SoftWearTimer(1);	/* 最低で220nsウェイトを置く By M.Kotani 1997/08/06 */
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
void LCD_WriteData(UBYTE data)
{
	/*-------------------------------*/
	/* RS 		-> 1:DRを選択		 */
	/* R/W	　　-> 0:Writeに設定	 */
	/* ENABLE   -> 0				 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_RS;					/* RS     を 1    *//*ﾃﾞｰﾀﾚｼﾞｽﾀを選択*/
	SYS_LCDC_PortStatus &= ~(IO_BIT_R_W | IO_BIT_E);	/* R/W    を 0(W) *//*WRITEに設定*/
														/* Enable を 0    */
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*-------------------------------*/
	/* ENABLE -> 1					 */
	/* ﾃﾞｰﾀ書き込み開始			     */
	/* 書き込む所はDDRAM/CGRAM		 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus |= IO_BIT_E;		/* Enable を 1 *//*WRITEのﾄﾘｶﾞ*/
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);

	/*-------------------------------*/
	/* DR Registerへﾃﾞｰﾀ書き込み	 */
	/*-------------------------------*/
	SYS_LCD_DataPortStatus = data;
	outpw(LCD_DATA_PORT, (UWORD)SYS_LCD_DataPortStatus);

	/*-------------------------------*/
	/* ENABLE -> 0					 */
	/* ﾃﾞｰﾀ書き込み終了				 */
	/* LCDC内部動作開始(Busy Set)	 */
	/*-------------------------------*/
	SYS_LCDC_PortStatus &= ~IO_BIT_E;		/* Enable を 0 */
	outpw(LCDC_PORT, (UWORD)SYS_LCDC_PortStatus);
}

/*************************************************************************
	module		:[ＣＧＲＡＭにイメージデータを書き込む]
	function	:[
		1.
	]
	return		:[なし]
	common		:[SYS_LCD_DataPortStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void WriteCGRAM(UBYTE *pointer)
{
	UBYTE	counter;
	UBYTE	max;

	max = (UBYTE)(LCD_SPECIAL_CHARACTER_MAX * LCD_CGRAM_TABLE_MAX);

	/* CGRAMを選択 */
	LCD_WriteInstruction(LCD_CGRAM_ADDRESS);

	/* 内部処理が終了するまで、或いは次のコマンドを実行してもいいくらい十分時間が経過するまで待つ */
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	for (counter = 0; counter < max; counter++) {	/* （１文字あたり８byte）×（４文字） */
		LCD_WriteData(*pointer);
		LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
		pointer++;
	}
}

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
void LCD_Initialize(void)
{
	/** 15msec以上待つ */
/*	LCD_SoftWearTimer(7000);	@* 約19msec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(9000);	@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	LCD_SoftWearTimer(14000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	/** 4,1msec以上待つ */
/*	LCD_SoftWearTimer(2100);	@* 約6msec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(3000);	@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	LCD_SoftWearTimer(4200);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	/** 100usec以上待つ */
/*	LCD_SoftWearTimer(170);		@* 約566usec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(250);		@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	LCD_SoftWearTimer(340);		/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	/** 15msec以上待つ */
/*	LCD_SoftWearTimer(7000);	@* 約19msec:Ｖ５３エミュレータ実測値 */
/*	LCD_SoftWearTimer(9000);	@* 約??msec:ＲＩＳＣエミュレータ実測値 */
	LCD_SoftWearTimer(14000);	/* 約??msec:ＲＩＳＣエミュレータ実測値 */

	/** ファンクションセット */
	LCD_WriteInstruction(LCD_FUNCTION_SET);
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示ＯＦＦ */
	LCD_WriteInstruction(LCD_DISPLAY_OFF);
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示クリア */
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME10MSEC);

	/** エントリーモードセット */
	LCD_WriteInstruction(LCD_ENTRY_MODE);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/* 注）POPLAR_Bでオールラムクリアを実行されると、モードだけコピーモードに初期化されてしまい、
	** 　　ＣＧＲＡＭは曜日表示用のままなので、CMN_InitializeAllBackUpRAM()でも初期化します
	*/

	LCD_SoftWearTimer(3000);	/* ここにウエイトを置かないとＣＧＲＡＭにうまくセットできない */
	/** ＣＧＲＡＭにデータをセット */
/*	InitializeCGRAM_Data();	*/

	/** 表示ＯＮ */
	LCD_WriteInstruction(LCD_DISPLAY_ON);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** 表示クリア */
	LCD_WriteInstruction(LCD_CLEAR_DISPLAY);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME10MSEC);
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
void DisplayStringHigh(UBYTE pos,		/*表示位置(0～19)*/
					   UBYTE *string)	/*表示文字列*/
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/** セマフォの獲得 1995/12/14*/
/*	wai_sem(semno.lcd);	*/

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*---------------------------------*/
	/** ファンクションセット(不要かも) */
	/*---------------------------------*/
#if (0)
	LCD_WriteInstruction(LCD_FUNCTION_SET);
#endif
	/* 表示されなかった為、コメント無効にしました。 97/08/11 By M.Kuwahara */
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*--------------------------------------------*/
	/** DDRAMアドレスセット(表示開始位置のセット) */
	/*--------------------------------------------*/
	/* DDRAMを選択 */
	ddram_address = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;	/* DDRAM_FIRST_ROW_ADDRESS = 0x80*/
	LCD_WriteInstruction(ddram_address);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

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
		LCD_WriteData(write_data);
    	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
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
void DisplayStringLow(UBYTE pos,		/*表示位置(0～19)*/
					  UBYTE *string)	/*表示文字列*/
{
	UBYTE	write_data;
	UBYTE	counter;
	UBYTE	ddram_address;

	/** セマフォの獲得 1995/12/14*/
/*	wai_sem(semno.lcd);	*/

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

#if (0)
	/*-----------------------*/
	/** ファンクションセット */
	/*-----------------------*/
	LCD_WriteInstruction(LCD_FUNCTION_SET);
#endif
	/* 表示されなかった為、コメント無効にしました。 97/07/19 By M.Kuwahara */
	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*----------------------------------------------*/
	/** DDRAMのアドレスセット(表示開始位置のセット) */
	/*----------------------------------------------*/
	ddram_address = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;	/*DDRAM_SECOND_ROW_ADDRESS = 0xc0*/
	LCD_WriteInstruction(ddram_address);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

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
		LCD_WriteData(write_data);
    	LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
	}

	/** 点滅表示を停止する 1995/12/16 Eguchi *//* 点滅中に点滅タスク以外のタスクが表示を書き換えるには点滅をやめる時であるとする */
/*	StopFunctionFlash();	*/

	/** セマフォの解放 1995/12/14*/
/*	sig_sem(semno.lcd);	*/
}

/*************************************************************************
	module		:[指定された位置にカーソルを表示]
	function	:[
		1.引数で指定された位置にカーソルを表示させる
		2.表示位置：上段→０～１９、下段→２０～３９
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
void CursorOn(UBYTE pos)	/*表示位置(0～39)*/
{
	UBYTE	ddram_adr;

	/** セマフォの獲得 1995/12/14*/
/*	wai_sem(semno.lcd);	*/
	/*-----------------------------------*/
	/** カーソル表示位置のアドレスを計算 */
	/*-----------------------------------*/
	if (pos < 20) { /*上段*/
		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
	}
	else {							/*下段*/
		pos -= 20;
		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
	}
	
	/*----------------------*/
	/** DDRAMアドレスセット */
	/*----------------------*/
	LCD_WriteInstruction(ddram_adr);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/*---------------*/
	/** カーソル表示 */
	/*---------------*/
	LCD_WriteInstruction(LCD_CURSOR_ON);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** セマフォの解放 1995/12/14*/
/*	sig_sem(semno.lcd);	*/
}

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
void CursorOff(void)
{
	LCD_WriteInstruction(LCD_CURSOR_OFF);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);
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
	UBYTE	ddram_adr;

	/** セマフォの獲得 1995/12/14*/
/*	wai_sem(semno.lcd);	*/

	/** カーソルをＯＦＦする 1996/01/06 Eguchi */
	CursorOff();

	/*-------------------------*/
	/** 表示位置のアドレス計算 */
	/*-------------------------*/
	if (pos < 20) {
		ddram_adr = (UBYTE)DDRAM_FIRST_ROW_ADDRESS + pos;
	}
	else {
		pos -= 20;
		ddram_adr = (UBYTE)DDRAM_SECOND_ROW_ADDRESS + pos;
	}

	/*----------------------------------------*/
	/** DDRAMアドレスセット(表示位置のセット) */
	/*----------------------------------------*/
	LCD_WriteInstruction(ddram_adr);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	
	/*文字がNULLの場合終了*/
	if (dsp_char == 0x00) {
		return;
	}

#if (0)
	/**特殊文字(Ⅰ,Ⅱ,Ⅲ,Ⅳなど）に対する処理*/
	dsp_char = CheckSpecialCharacter(dsp_char);
#endif

	/*-------------*/
	/** 文字を表示 */
	/*-------------*/
	LCD_WriteData(dsp_char);
    LCD_BusyFlagWait(LCD_BUSY_WAIT_TIME200USEC);

	/** セマフォの解放 1995/12/14*/
/*	sig_sem(semno.lcd);	*/
}

/*************************************************************************
	module		:[ＬＣＤ上段表示クリア]
	function	:[
		1.LCD上段の表示をクリア(スペースを書き込む）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearDisplayHigh(void)
{
	UBYTE	clear_buffer[OPR_WORDING_LEN];

	CMN_MemorySetNULL(clear_buffer, OPR_DISPLAY_MAX, ' ');
	DisplayStringHigh(0, clear_buffer);
}

/*************************************************************************
	module		:[ＬＣＤ下段表示クリア]
	function	:[
		1.ＬＣＤ下段の表示をクリアする（スペースを書き込む）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearDisplayLow(void)
{
	UBYTE	clear_buffer[OPR_WORDING_LEN];

	CMN_MemorySetNULL(clear_buffer, OPR_DISPLAY_MAX, ' ');
	DisplayStringLow(0, clear_buffer);
}

#endif
