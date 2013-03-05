/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_FLSH.C
*	Author		: 渡辺一章
*	Date		: 1996/10/18
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 点滅表示制御
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\std.h"
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/14 */
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\mntsw_h.h"	/* ＬＣＤ表示変更 By O.Kimoto 1999/02/25 */
#endif
#include	"\src\atlanta\define\timer10.h"
#if (PRO_MODEM == ORANGE3)	/* Add By H.Fujimura 1999/01/14 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* (DVT修正：メモリー送信の蓄積時でモードと濃度を表示不具合修正) Added by SMuratec 李 2004/08/05 */
#include	"\src\atlanta\ext_v\man_data.h"
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/14 */
#include	"\src\atlanta\ext_v\sys_data.h"
#endif

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
#include	"\src\atlanta\define\mntsw_g.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#endif

/* Prototype
void	OPR_DisplayFlashTask(void);
void	FunctionFlashControl(void);
UBYTE	WaitFlashTime(void);
void	FlashDisplayStringHigh(UBYTE *);
void	FlashDisplayStringLow(UBYTE *);
void	SetFlashBuffer(UBYTE *, UBYTE *, UBYTE *);
void	StopFunctionFlash(void);
void	StopFunctionFlashHigh(void);
void	StopFunctionFlashLow(void);
UBYTE	CheckFunctionFlash(void);
void	StartChildDisplay(void);
void	StopChildDisplay(void);
UBYTE	CheckChildDisplay(void);
UBYTE	CheckChildErrorDisplayReq(void);
void	ChildDisplayStringLow(CONST UBYTE *);
void	ChildDisplaySetCompleted(CONST UBYTE *);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void	ParamChildDisplayStringLow(UBYTE *);
#endif
*/

/*************************************************************************
	module		:[表示フラッシュタスク]
	function	:[
		1.フラッシュ起動フラグを500msecに１回監視してループ
		2.フラグがセットされていたら表示フラッシュ実行
		3.システム起動時から存在するタスクです
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		・\src\rice\h8\src\dsp_flsh.cのOPR_DispFlashTask()を変更
		・点滅表示は上段・下段どちらか一方でしか出来ません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void OPR_DisplayFlashTask(void)
{
	while (1) {
		wai_tsk(50);	/* このタイマーの時間はもっと短くせなあかんかも */
		if (CheckFunctionFlash()) {	/* 点滅表示要求あり */
		 	if (CheckChildDisplay() == FALSE) {	/* チャイルド表示中はあかん */
				FunctionFlashControl();
			}
		}
	}
}

/*************************************************************************
	module		:[表示フラッシュ制御]
	function	:[
		1.ＬＣＤ下段の内容を点滅させます.(500msec毎)
		2.100msecに一回フラッシュ起動フラグの状態を見に行きます
	]
	return		:[なし]
	common		:[
		IsFlashDisplayLow	:
		FlashBufferLowMain	:
		FlashBufferLowSub	:
	]
	condition	:[]
	comment		:[
		点滅の起動を掛けるところで点滅用文字列を作成しておかないと、
		表示文字列の変更ができない可能性がある。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口]
*************************************************************************/
void FunctionFlashControl(void)
{
	UBYTE	*dsp_string;	/* 表示文字列のポインター */
	UBYTE	*flash_main;	/* 点滅表示バッファ（メイン）のポインター */
	UBYTE	*flash_sub;		/* 点滅表示バッファ（サブ）のポインター */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/14 */
	UWORD	mem_area;
	UBYTE	i;
	UBYTE	j;	/* ＬＣＤ表示変更 By O.Kimoto 1999/02/25 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/27 */
	UBYTE	DispFlashOn;
	
	DispFlashOn = FALSE;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/14 */
	if (SYB_MaintenanceSwitch[MNT_SW_H5] & DISPLAY_STORING_TYPE) {
		i = 3;
	}
	else {
		i = 4;
	}
#endif

	if (IsFlashDisplayHigh) {	/* 上段を点滅表示させる時 */
		flash_main = &FlashBufferHighMain[0];
		flash_sub  = &FlashBufferHighSub[0];
	}
	if (IsFlashDisplayLow) {	/* 下段を点滅表示させる時 */
		flash_main = &FlashBufferLowMain[0];
		flash_sub  = &FlashBufferLowSub[0];
	}
	dsp_string = flash_sub;

	/*----------------------*/
	/* 点滅をスタートします */
	/*----------------------*/
	while (1) {

#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* Add By H.Fujimura 1999/01/14 */
		/** セマフォの獲得 1995/12/14*/
		wai_sem(semno.lcd);
#endif

		/* 必ず表示を出す前に点滅停止か確認する */
		if (IsFlashDisplayHigh) {		/* 上段を点滅表示させる時 */
			DisplayFlashStringHigh(0, dsp_string);
		}
		else if (IsFlashDisplayLow) {	/* 下段を点滅表示させる時 */
#if (PRO_KEYPANEL == PANEL_HINOKI) /*|| (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)*/  /* (SATSUKI2はHINOKIと同じくない)Modify by SMuratec L.Z.W 2003/10/27 */	/* Add By H.Fujimura 1999/01/14 */

#if (0)
** 			/* 原稿蓄積中の動作をあらわす「＊＊＊＊＊」の点滅＆メモリ残量の点滅が一般ユーザーにとって
** 			** わかりにくいとの指摘を受け、表示内容を変更します。
** 			** 尚、ＴＷＮの関係で現状のタイプも残しておくことにします。
** 			** by O.Kimoto 1999/02/25
** 			*/
** 			if (CMN_StringCompare(FlashBufferLowMain, D2W_MemoryAreaLong2, OPR_WORDING_LEN) == STRCMP_EQUAL) {
** 				CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
** 				/* メモリー残量セット */
** 				CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaLong2);	/* "   *****     ﾒﾓﾘ   %" */
** 				if (dsp_string == flash_main || SYS_StorePause) {
** 					mem_area = (UWORD)MEM_CountEmptyBlockRate();
** 					CMN_UnsignedIntToASC(&DisplayBufferLow[16], mem_area, 3, ' ');
** 				}
** 				DisplayBufferLow[i++] = ' ';
** 				if (i == 8) {
** 					i = 3;
** 				}
** 				/* 原稿サイズワーディングセット */
** 				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/* 原稿蓄積中の時 */
** 					SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
** 				}
** 				else {															/* 原稿セット・繰り込み・排出中の時 */
** 					SetDocumentScanSizeWording(DisplayBufferLow, CMN_GetDocumentScanSize());
** 				}
** 				/* 原稿サイズ・ブック次原稿のあり／なし・メモリー残量表示 */
** 				DisplayFlashStringLow(0, DisplayBufferLow);
** 			}
** 			else {
** 				DisplayFlashStringLow(0, dsp_string);
** 			}
#else

			if (SYB_MaintenanceSwitch[MNT_SW_H5] & DISPLAY_STORING_TYPE) {
				/* 従来タイプ（ＴＷＮ用）*/
				if (CMN_StringCompare(FlashBufferLowMain, D2W_MemoryAreaLong2, OPR_WORDING_LEN) == STRCMP_EQUAL) {
					CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
					/* メモリー残量セット */
					CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaLong2);	/* "   *****     ﾒﾓﾘ   %" */
					if (dsp_string == flash_main || SYS_StorePause) {
						mem_area = (UWORD)MEM_CountEmptyBlockRate();
						CMN_UnsignedIntToASC(&DisplayBufferLow[16], mem_area, 3, ' ');
					}
					DisplayBufferLow[i++] = ' ';
					if (i == 8) {
						i = 3;
					}
/*
** 設計変更依頼 RDC-473-D86-003
** Ｂ４原稿蓄積終了間際に、表示が一瞬Ａ４となる不具合
** ここに来るときは、蓄積中が前提になるので、常にSYS_DocumentScanSizeを参照するように変更します
** 1999/06/10 by T.Soneoka
*/
#if (0)
**					/* 原稿サイズワーディングセット */
**					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/* 原稿蓄積中の時 */
**						SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
**					}
**					else {															/* 原稿セット・繰り込み・排出中の時 */
**						SetDocumentScanSizeWording(DisplayBufferLow, CMN_GetDocumentScanSize());
**					}
#else
					SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
#endif
					/* 原稿サイズ・ブック次原稿のあり／なし・メモリー残量表示 */
					DisplayFlashStringLow(0, DisplayBufferLow);
				}
				else {
					DisplayFlashStringLow(0, dsp_string);
				}
			}
			else {
				/* 改良タイプ（ＪＰＮ用）*/
				if (CMN_StringCompare(FlashBufferLowMain, D2W_MemoryAreaShort2, OPR_WORDING_LEN) == STRCMP_EQUAL) {
					CMN_MemorySetNULL(DisplayBufferLow, OPR_DISPLAY_MAX, ' ');
					/* メモリー残量セット */
					CMN_StringCopy(DisplayBufferLow, D2W_MemoryAreaShort2);	/* "   *****     ﾒﾓﾘ   %" */

					/* メモリ残量は定期的に更新したほうがわかりやすいので */
					mem_area = (UWORD)MEM_CountEmptyBlockRate();
					CMN_UnsignedIntToASC(&DisplayBufferLow[16], mem_area, 3, ' ');

					for (j = 3; j < i; j ++) {
						DisplayBufferLow[j] = '~';	/* → */
					}

					i ++;
#if (PRO_UI_WORDING == ENABLE)	/* by K.Watanabe 2004/10/22 */
					if (i >= 12) {
#else
					if (i >= 13) {
#endif
						i = 4;
					}

/*
** 設計変更依頼 RDC-473-D86-003
** Ｂ４原稿蓄積終了間際に、表示が一瞬Ａ４となる不具合
** ここに来るときは、蓄積中が前提になるので、常にSYS_DocumentScanSizeを参照するように変更します
** 1999/06/10 by T.Soneoka
*/
#if (0)
**					/* 原稿サイズワーディングセット */
**					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {	/* 原稿蓄積中の時 */
**						SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
**					}
**					else {															/* 原稿セット・繰り込み・排出中の時 */
**						SetDocumentScanSizeWording(DisplayBufferLow, CMN_GetDocumentScanSize());
**					}
#else
					SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
#endif
					/* 原稿サイズ・ブック次原稿のあり／なし・メモリー残量表示 */
					DisplayFlashStringLow(0, DisplayBufferLow);
				}
				else {
					DisplayFlashStringLow(0, dsp_string);
				}
			}

#endif

#elif (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (読み取り中の表示は「＊」を点滅させます)Added by SMuratec L.Z.W 2003/10/27 */
			/* （SATSUKI2専用）*/
			/*
			** オペレーション中であれば表示は更新しません。(注）電話中は、SYS_PANEL_BUSYがONしています。 **
			** チャイルド表示中はなにも表示しない。 **
			** by SMuratec L.Z.W 2003/11/17 **
			*/
			if (IsDocumentStoring && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE) &&
				!(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) &&
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* DVT修正：メモリー送信の蓄積時でモードと濃度を表示不具合修正 Added by SMuratec 李 2004/08/05 */
				(timer_store_fax_complete == 0xFF) &&
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
				!CheckChildDisplay()) {
 				/* (上段でメモリ残量を点滅表示の追加) Added by SMuratec L.Z.W 2003/11/04 */
				DisplayBufferHigh[19] = '%';
				mem_area = (UWORD)MEM_CountEmptyBlockRate();
				CMN_UnsignedIntToASC(&DisplayBufferHigh[16], mem_area , 3, ' '); 
				DisplayFlashStringHigh(16, &DisplayBufferHigh[16]);
				/* 点滅機能ある場合　*/
				if (CHK_StoringFlashEnable()) {
					SetDocumentScanSizeWording(DisplayBufferLow, SYS_DocumentScanSize);
					SetDocumentSetWording(DisplayBufferLow);
					DispFlashOn ^= TRUE;
					if (DispFlashOn) {
						DisplayBufferLow[18] = '*';
					}
					else {
						DisplayBufferLow[18] = ' ';
					}
					DisplayFlashStringLow(0, DisplayBufferLow);
				}
			}
			else {
				DisplayFlashStringLow(0, dsp_string);
			}
#else

			DisplayFlashStringLow(0, dsp_string);
#endif
		}
		else {

#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* Add By H.Fujimura 1999/01/14 */
			/** セマフォの解放 */
			sig_sem(semno.lcd);
#endif

			break;
		}

#if (PRO_KEYPANEL != PANEL_HINOKI) && (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* Add By H.Fujimura 1999/01/14 */
		/** セマフォの解放 1995/12/14*/
		sig_sem(semno.lcd);
#endif

		/* 500msec待つ */
		if (WaitFlashTime()) {	/* 点滅継続 */
			/* 表示文字列の交換 */
			if (dsp_string == flash_main) {
 				dsp_string = flash_sub;
			}
			else {
				dsp_string = flash_main;
			}
		}
		else {					/* 点滅終了 */
			break;
		}
	}
}

/*************************************************************************
	module		:[点滅表示切り替え時間待ち処理]
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
	author		:[江口]
*************************************************************************/
UBYTE WaitFlashTime(void)
{
	UWORD	timer;

	for (timer = 0; timer < 5; timer++) {
		wai_tsk(10);
		if (!CheckFunctionFlash()) {
			return(FALSE);
		}
	}
	return(TRUE);
}

/*************************************************************************
	module		:[上段点滅表示]
	function	:[
		1.上段点滅表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/25]
	author		:[渡辺一章]
*************************************************************************/
void FlashDisplayStringHigh(UBYTE *flash_string)
{
	/* これから表示させる文字列を、既に上段に点滅表示している時は、処理を省きます */
	if ((IsFlashDisplayHigh)
	 && (CMN_StringCompare(flash_string, FlashBufferHighMain, OPR_WORDING_LEN) == STRCMP_EQUAL)) {
		return;
	}

	/** 現在点滅表示中の時は、点滅表示を停止します（上下段は問いません） */
	StopFunctionFlash();

	/* フラッシュ表示の時に、フラッシュタスクの中だけで表示を行うと
	** 表示の開始が一瞬遅れるので、先に表示を行います
	*/
	DisplayStringHigh(0, flash_string);

	/** 点滅表示文字列の作成 */
	SetFlashBuffer(FlashBufferHighMain, FlashBufferHighSub, flash_string);

	/** 点滅表示起動 */
	IsFlashDisplayHigh = TRUE;
}

/*************************************************************************
	module		:[下段点滅表示]
	function	:[
		1.下段点滅表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/12]
	author		:[渡辺一章]
*************************************************************************/
void FlashDisplayStringLow(UBYTE *flash_string)
{
	/* これから表示させる文字列を、既に下段に点滅表示している時は、処理を省きます */
	if ((IsFlashDisplayLow)
	 && (CMN_StringCompare(flash_string, FlashBufferLowMain, OPR_WORDING_LEN) == STRCMP_EQUAL)) {
		return;
	}

	/** 現在点滅表示中の時は、点滅表示を停止します（上下段は問いません） */
	StopFunctionFlash();

	/* フラッシュ表示の時に、フラッシュタスクの中だけで表示を行うと
	** 表示の開始が一瞬遅れるので、先に表示を行います
	*/
	DisplayStringLow(0, flash_string);

	/** 点滅表示文字列の作成 */
	SetFlashBuffer(FlashBufferLowMain, FlashBufferLowSub, flash_string);

	/** 点滅表示起動 */
	IsFlashDisplayLow = TRUE;
}

/*************************************************************************
	module		:[点滅表示用文字列作成]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/25]
	author		:[渡辺一章]
*************************************************************************/
void SetFlashBuffer(UBYTE *flash_buf_main, UBYTE *flash_buf_sub, UBYTE *flash_string)
{
	UBYTE	i;	/* ループ変数 */

	/** 点滅表示用バッファの初期化 */
	CMN_MemorySetNULL(flash_buf_main, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(flash_buf_sub,  OPR_DISPLAY_MAX, ' ');

	/** 点滅表示文字列の作成（メイン） */
	CMN_StringCopyNULL(flash_buf_main, flash_string);

	/** 点滅表示文字列の作成（サブ） */
	for (i = 0; i < OPR_DISPLAY_MAX; i++) {
		if (flash_buf_main[i] == '/') {
			flash_buf_sub[i] = '/';
#if !(PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2の場合、'/'が２個あるので省きます。by Y.kano 2003/09/01 */
			break;
#endif
		}
	}
}

/*************************************************************************
	module		:[点滅表示停止]
	function	:[
		1.点滅表示を停止します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/02/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void StopFunctionFlash(void)
{
	StopFunctionFlashHigh();
	StopFunctionFlashLow();
}

/*************************************************************************
	module		:[上段点滅表示停止]
	function	:[
		1.上段点滅表示を停止します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		点滅表示用バッファは点滅表示開始時にクリアします
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/25]
	author		:[渡辺一章]
*************************************************************************/
void StopFunctionFlashHigh(void)
{
	if (IsFlashDisplayHigh) {
		IsFlashDisplayHigh = FALSE;
	}
}

/*************************************************************************
	module		:[下段点滅表示停止]
	function	:[
		1.下段点滅表示を停止します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		点滅表示用バッファは点滅表示開始時にクリアします
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/25]
	author		:[渡辺一章]
*************************************************************************/
void StopFunctionFlashLow(void)
{
	if (IsFlashDisplayLow) {
		IsFlashDisplayLow = FALSE;
	}
}

/*************************************************************************
	module		:[点滅チェック]
	function	:[
		1.表示が点滅しているかチェックします
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		点滅表示は、上段・下段のどちらか一方でしか出来ないので、
		このチェックでＯＫです
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/17]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckFunctionFlash(void)
{
	if ((IsFlashDisplayHigh) || (IsFlashDisplayLow)) {
		return(TRUE);
	}

	return(FALSE);
}

/*************************************************************************
	module		:[チャイルド表示開始]
	function	:[
		1.チャイルド表示中であればチャイルド表示を中止します
		2.点滅表示であれば点滅を中断します
		3.２秒(チャイルド表示の時間）をはかるタスクを起動
		4.チャイルド表示中かどうかはタイマーのTIDの値で判断して。
	]
	return		:[なし]
	common		:[
		H8のものとは少しかえた　->　キータイマーをなくし、共通のタイマーを使用。
		,　　　　　　　　　　　　　 チャイルド中を表すフラグ削除し、TIDで代用
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/10]
	author		:[江口]
*************************************************************************/
void StartChildDisplay(void)
{
	/* ２秒間を監視するタイマータスクを起動（タイムアップのメッセージはキー取り込み部に送信される） */
	cre_tsk(&tskno_OPR_ChildTimerTask, TSK_CMN_MAN_TIMER10MSTASK, &ChildTimer);
}

/*************************************************************************
	module		:[チャイルド表示チェック及び終了]
	function	:[
		1.チャイルド表示かどうかチェックし、チャイルド表示中なら表示をやめる
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/03/10]
	author		:[江口]
*************************************************************************/
void StopChildDisplay(void)
{
	if (CheckChildDisplay() == TRUE) {	/** チャイルド表示タイマー起動中 -> チャイルド表示中 */
		del_tsk(&tskno_OPR_ChildTimerTask);
	}
}

/*************************************************************************
	module		:[チャイルド表示中かどうか調べる]
	function	:[
		1.
	]
	return		:[
		TRUE;チャイルド表示中
		FLASE:チャイルド表示中でない
	]
	common		:[tskno_OPR_ChildTimerTask]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/27]
	author		:[江口]
*************************************************************************/
UBYTE CheckChildDisplay(void)
{
	if (tskno_OPR_ChildTimerTask != 0xFFFF) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[チャイルド表示要求があるか調べる]
	function	:[
		1.オペレーションの入力エラー等によりチャイルド表示要求があるか調べる
	]
	return		:[
		TRUE:チャイルド表示要求有り
		FALSE:チャイルド表示要求なし
	]
	common		:[OPR_ChildErrorFlag]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/09/27]
	author		:[江口]
*************************************************************************/
UBYTE CheckChildErrorDisplayReq(void)
{
	if (OPR_ChildErrorFlag != OPR_NO_ERROR) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[チャイルドＬＣＤ表示]
	function	:[
		1.完了表示を出す
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		変更履歴
		・1997/11/08 by K.Watanabe
			ポプラＢのコピーモードで、ソート，拡大・縮小キーが押された時のために、
			チャイルドタイマーを使用する別関数を作ったので、毎回タイマー時間を
			セットするように変更しました（時間を引数として追加してもよかったが、
			上記以外は２秒なので呼び出す側は現状のまま変更しないようにしました）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/06/03]
	author		:[江口]
*************************************************************************/
void ChildDisplayStringLow(CONST UBYTE *Data)	/* 文字列 */
{
	StopChildDisplay();		/* チャイルド表示中ならチャイルドDELETE この中でタイマータスクのTIDが0XFFFFに戻ってる*/
	ChildTimer.Time = 200;	/* チャイルド表示時間（２秒） */
	StartChildDisplay();
	DisplayStringLow(0, (UBYTE *)Data);
}

/*************************************************************************
	module		:[セット完了ＬＣＤ表示]
	function	:[
		1.セット完了のＬＣＤ表示を行う
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[H8から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/06/03]
	author		:[江口]
*************************************************************************/
void ChildDisplaySetCompleted(CONST UBYTE *ItemWording)	/*表示メッセージ*/
{
	DisplayStringHigh(0, (UBYTE *)ItemWording);
	ChildDisplayStringLow(D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
}

/*************************************************************************
	module		:[パラメーター表示用チャイルド表示]
	function	:[
		1.指定の文字列をチャイルド表示で表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		ポプラＢのコピーモードで、ソート，拡大・縮小キーが押された時に
		ChildDisplayStringLow()を使用していたが、表示時間を長くしてほしい
		と言う要望を満たすためにチャイルド時間を変更した別関数を作りました
		注）ChildDisplayStringLow()に、時間を引数として追加してもよかったが、
			上記以外は２秒なので呼び出す側は現状のまま変更しないようにしました
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/08]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
void ParamChildDisplayStringLow(UBYTE *Data)
{
	StopChildDisplay();
	ChildTimer.Time = (UWORD)(SYB_MaintenanceSwitch[MNT_SW_G9] * 10);	/* パラメーター表示時間をセット */
	StartChildDisplay();
	DisplayStringLow(0, Data);
}
#endif
