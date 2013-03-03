/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_D56.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: キャラクタプリントオープン、ラン、クローズ
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\mntsw_c.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\timer10.h"

#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\lst_def.h"

#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\lst_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\dma_data.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\sys_data.h"

#if (PRO_CPU == SH7043)
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#endif

#if (PRO_PRINT_TYPE == LED)
#include "\src\atlanta\prt\ph3\define\prn_pro.h"
#include "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#include "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#include "\src\atlanta\define\uni_pro.h"	/* by M.Tachibana 1999/10/06 */
#endif
#if (PRO_PRINT_TYPE == LASER)
#include "\src\atlanta\prt\sp322\define\prn_pro.h"
#include "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#include "\src\atlanta\prt\sp322\ext_v\prn_tbl.h"
#endif

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/30 */
#include "\src\atlanta\define\sysmcopy.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
WORD	PrintReturnedMailTextPart( UBYTE );
#endif

static UWORD	tskno_datatransferpage = 0;		/* コーデックからプリンタにDMAするタスク */
static UWORD	tskno_printererrordetect = 0;	/* プリンタのジャムを検出し擬似HSYNCを発生するタスク */
static UDWORD	DMA_start_address = 0;			/* DMAするアドレス */

extern CONST UBYTE LST_TEST;	/* debug */

#if (PRO_PRN_CODEC_TYPE != SOFTWARE)	/* 1998/06/10 H.Yoshikawa */
/*************************************************************************
	module		:[リストプリント(キャラクタ)の準備]
	function	:[
	]
	return		:[未定(エラーコード)]
	common		:[なし]
	condition	:[]
	comment		:[
		この関数をコールしたら、記録紙をフィードするため
		必ず、約３秒以内に文字列プリントを開始する事（紙が行き過ぎるため）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和]
*************************************************************************/
WORD	ListOpen(void)
{
	struct DMA_Data_t dma;
	UBYTE result;
	UBYTE	debug;

#if defined(ANZU_L)	/* debug 1997/12/09 */
	if (LST_Debug1) {
		outp((unsigned long)0,(unsigned char)0);
		debug++;
	}
	else {
		LST_Debug1 = 1;
	}
#endif


#if (PRO_PRINT_TYPE == LED)
	if (LST_PageCounter == 0) {
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;	/* ”しばらくお待ち下さい”を表示されるため */
	}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)
#else
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_LIST_PRINT;	/* StopSw by Kotani Nov.16) */
	PRN_TopStartTime = 0;	/* By H.Y 1994/10/31 */
	LST_SelectPaperSize();	/** カセット選択 */
	FontImageBufferAddress = &FontImageBuffer.Font[CDC_CHARACTER_PRINT_A][0][0];	/**フォント展開にＡ面を指定*/
#endif


#if (PRO_CPU == SH7043) /* ＣＰＵに依存 */
	DMA_start_address = (UDWORD)&FontImageBuffer.Font[CDC_CHARACTER_PRINT_A][0][0];	/**DMA開始アドレス*/
#endif
	/**V53DMAUをセットアップする*/
	dma.Channel = DMA_DRAM_PRNCDC_CH;					/*DMAチャンネル*/
	dma.Unit = DMA_WORD_TRANSFER;						/*DMA転送単位(DMA_WORD_TRANSFER or DMA_BYTE_TRANSFER)*/
	dma.Direction = DMA_MEMORY_TO_IO;					/*DMA転送方向(DMA_IO_TO_MEMORY or DMA_MEMORY_TO_IO)*/
	dma.SrcAddress = DMA_start_address;					/*DMA開始アドレス(絶対アドレス24ビットで指定)*/
	dma.Counter = 640;									/*DMA転送回数(ワード転送時=転送バイト数/2, バイト転送時=転送バイト数)*/
	DMA_SetupDMAU(&dma);

#if defined(ANZU_L)	/* debug 1997/12/09 */
	if (tskno_printererrordetect != 0xFFFF) {
		del_tsk(&tskno_printererrordetect);	/* プリンタのジャムを検出し擬似HSYNCを発生するタスク */
		outp((unsigned long)0,(unsigned char)0);
		debug++;
	}
#endif

	cre_tsk(&tskno_printererrordetect, TSK_LST_PRINTERERRORDETECTTASK, 0);	/* プリンタのジャムを検出し擬似HSYNCを発生するタスク */
	wai_tsk(10);
	result = LST_StartPrinter();	/**プリンタをスタートする*/

#if (PRO_PRINT_TYPE == LED)
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_WARMUP;
#endif

	/* By H.Y 1995/09/19 Start */
	if (result != OK) {

#if defined(ANZU_L)	/* debug 1997/12/09 */
		if (tskno_printererrordetect == 0xFFFF) {
			outp((unsigned long)0,(unsigned char)0);
			debug++;
		}
		LST_Debug1 = 0;
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
	}
#else
		if (tskno_printererrordetect != 0xFFFF) {	/*Add By M.Kotani 1997/12/16*/
			del_tsk(&tskno_printererrordetect);	/* プリンタのジャムを検出し擬似HSYNCを発生するタスク */
		}
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_JAM_RECOVER;
	/*	if (result == MSG_PRN_IMAGE_PAPER_ERROR) {	下記内容に変更 By M.Tachibana 1997/05/22 */
		if (result == MSG_PRN_LST_PAPER_ERROR) {
			PRN_JamPrintStopFlag = 1;	/*記録紙JAM扱いとして､再プリントさせる*/
		}
		else {	/* MSG_PRN_IMAGE_STOPSW_ON */
			PRN_JamPrintStopFlag = 2;	/*STOP押下*/
		}
		return((WORD)result);
	}
	/* By H.Y 1995/09/19 End */
	PRN_PGEND_DetectFlag = 0;	/**ページエンドフラグ初期化*/
	if (!GetCodec(PRINTER_CODEC, CODEC_CHARACTER_PRINT)) {	/**プリンタコーデックを獲得する*/
		SaveReturnAddressAndJumpBegin();
	}
#endif

	cre_tsk(&tskno_datatransferpage, TSK_CDC_DATATRANSFERPAGETASK, 0);	/** コーデックからプリンタにDMAするタスク */

	return(OK);
}



/*************************************************************************
	module		:[文字1ライン分を展開、DMA転送(エラー処理なし)]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/08/24]
	auther		:[石橋正和]
*************************************************************************/
void	ListPrintRunWithoutError(void)
{
	UWORD debug;
	UWORD i;

	debug = 0;

#if (0)	/* タイマ割込みでカウントする By M.Tachibana 1997/09/09 */
//	/*	イベントが発生しない時にタイマーで抜ける。（５秒）By H.H 1996/08/23	*/
//	/**	タイマーセット	*/
//	LST10msEventTimer.Time = 800;			/**	8sec <- 5sec By M.Tachibana 1997/04/18	*/
//#if (PRO_PRINT_TYPE == LASER)
//	LST10msEventTimer.Event = EVT_PAPER_JAM;
//#else
//	LST10msEventTimer.Event = EVT_PRN_PRINTER_ERROR;
//#endif
//
//	if ( tskno_cmn_watchtimer10msevent != 0xffff ) {
//		del_tsk( &tskno_cmn_watchtimer10msevent );
//	}
//	cre_tsk(&tskno_cmn_watchtimer10msevent, TSK_CMN_WATCHTIMER10MSEVENTTASK, &LST10msEventTimer );
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else
	if (PRN_JamPrintStopFlag == 1) {	/* By M.Tachibana 1997/11/26 */
		return;
	}
#endif

	/** 片面のフォント展開 */
	DMA0_TC1Flag = 0; /* By H.H 1996/08/23 */

	if (LST_TEST) {
		if (LST_DebugData == 0) {
			GetOneLineCharacterImage(&List.S.Print[0], &List.S.Attribute[0], FontImageBufferAddress);
		}
		LST_DebugData++;
	}
	else {
	GetOneLineCharacterImage(&List.S.Print[0], &List.S.Attribute[0], FontImageBufferAddress);
	}

	if (debug) {	/*MN86064デバッグ*//* By M.Kotani 97/07/11 */
		for (i = 0; i < 16; i++) {
			*(FontImageBufferAddress + (i * 80)) = 0xFF;
		}
	}
	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, 640);					/**転送量の設定*/
	CMN_DisableInterrupt();						/**割り込み禁止*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);						/**転送許可（開始）*/

	LST_JAM_DetectCounter = 8000 / 10;
	wai_evt(EVT_DMA_DRAM_PRNCDC);
	LST_JAM_DetectCounter = 0;

#if (0)	/* タイマ割込みでカウントする By M.Tachibana 1997/09/09 */
//	if ( tskno_cmn_watchtimer10msevent != 0xffff ) {
//		del_tsk( &tskno_cmn_watchtimer10msevent );
//	}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else
	if ( (DMA0_TC1Flag == 0) && (PRN_JamPrintStopFlag == 0) ) {
		PRN_JamPrintStopFlag = 1;	/**	ジャム扱いにして再起動する	*/
/*		SYB_MaintenanceSwitch[MNT_SW_C1]++;		Del	BY M.Tachibana 1998/02/10 */
	}
#endif

}



/*************************************************************************
	module		:[文字1ライン分を展開、DMA転送]
	function	:[
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和]
*************************************************************************/
WORD	ListPrintRun(void)
{
	/* if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT) { By S.Kawasaki 1996/07/16 */
	if ((SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT) ||
		(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER) ) { /** ジャムリカバー中であれば */

		/** ストップキーが押された場合 */
		ListClose(); /** リストクローズ */
		return(MSG_PRN_LST_STOPSW_ON);
	}
	ListPrintRunWithoutError();
	return(OK);

}



/*************************************************************************
	module		:[テストパターンプリント]
	function	:[
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/07/20]
	auther		:[石橋正和]
*************************************************************************/
WORD	ListImagePrint(void)
{
	if (PRN_JamPrintStopFlag == 1) {	/* By M.Tachibana 1997/11/26 */
/*		return(MSG_PRN_LST_PAPER_ERROR);	*/
		return(OK);	/* ListClose()を通すため By M.Tachibana 1997/12/11 */
	}

	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
/*	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, 1216);	@**転送量の設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, LST_WORD_WIDTH*4);	/**転送量の設定*/
	CMN_DisableInterrupt();				/**割り込み禁止*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/

	LST_JAM_DetectCounter = 8000 / 10;
	wai_evt(EVT_DMA_DRAM_PRNCDC);		/**4ラインの転送終了を待つ*/
	LST_JAM_DetectCounter = 0;
	return(OK);
}

/*************************************************************************
	module		:[テストパターンプリント]
	function	:[
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1997/07/22]
	auther		:[橘正樹]
*************************************************************************/
WORD	ListImageLinePrint(
UBYTE	line )
{
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else
	if (PRN_JamPrintStopFlag == 1) {	/* By M.Tachibana 1997/11/26 */
/*		return(MSG_PRN_LST_PAPER_ERROR);	*/
		return(OK);	/* ListClose()を通すため By M.Tachibana 1997/12/11 */
	}
#endif

	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, (UWORD)LST_WORD_WIDTH*(UWORD)line);	/**転送量の設定*/
	CMN_DisableInterrupt();				/**割り込み禁止*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/

	LST_JAM_DetectCounter = 8000 / 10;
	wai_evt(EVT_DMA_DRAM_PRNCDC);		/**4ラインの転送終了を待つ*/
	LST_JAM_DetectCounter = 0;
	return(OK);
}



/*************************************************************************
	module		:[引数分の行の空白をプリントする(エラー処理なし)]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/08/24]
	auther		:[石橋正和]
*************************************************************************/
void	ListLineFeedWithoutError(
		UBYTE line)	/* 出力する空白行数 */
{
	UBYTE i;
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

	if (PRN_JamPrintStopFlag == 1) {	/* By M.Tachibana 1997/11/26 */
		return;
	}
#endif

	if (line == 0) {
		line = 1;	/* ?上位関数との整合性をはかるため */
	}
	/** 片面のフォント展開(すべて0を代入) */
	CMN_MemorySet(FontImageBufferAddress, 1280, 0); /* 1280 = 80*16 */
	for (i = 0; i < line ;i++) {
		DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
		DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, 640);			/**転送量の設定*/
		CMN_DisableInterrupt();				/**割り込み禁止*/
		DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/

		LST_JAM_DetectCounter = 8000 / 10;
		wai_evt(EVT_DMA_DRAM_PRNCDC);		/**1ラインの転送終了を待つ*/
		LST_JAM_DetectCounter = 0;
	}
}



/*************************************************************************
	module		:[引数分の行の空白をプリントする]
	function	:[
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[エラー処理が未定。例えば、途中で用紙の最後にいった場合など。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/13]
	auther		:[石橋正和]
*************************************************************************/
WORD	ListLineFeed(
		UBYTE line)	/* 出力する空白行数 */
{
	ListLineFeedWithoutError(line);
	return(OK);
}



/*************************************************************************
	module		:[プリンタをクローズする(キャラクタプリント時)]
	function	:[
		1.プリンタをクローズする(キャラクタプリント時)
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/06/08]
	auther		:[石橋正和]
*************************************************************************/
static UWORD	safety_timer; /* By S.Kawasaki 1996/07/15 */

WORD	ListClose(void)
{
	UBYTE debug;
#if defined(ANZU_L)	/* debug 1997/12/09 */
	if (LST_Debug1) {
		LST_Debug1 = 0;
	}
	else {
		outp((unsigned long)0,(unsigned char)0);
		debug++;
	}
#endif


	ListLineFeed(2);		/**２面バッファをクリアする*//* 出力する空白行数 */

	DMA_AutoInitializeEnable(DMA_DRAM_PRNCDC_CH);		/** DMAU AutoInitializeMode Enable */
	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, 640);			/**転送量の設定*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

	if (!PRN_TopStartTime) {		/* By H.Y 1994/10/31 */
		PRN_TopStartTime = SYS_GeneralTimer;
	}
#endif

#if (PRO_PRINT_TYPE == LASER)
	/* while ((UWORD)(SYS_GeneralTimer - PRN_TopStartTime) < PRN_t11Table[SelectedPaper]) {	By S.Kawasaki 1996/07/16 *//**空白行をページエンドまで出力する*/
	while (((UWORD)(SYS_GeneralTimer - PRN_TopStartTime) < PRN_t11Table[SelectedPaper]) && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER))  {/* By S.Kawasaki 1996/07/16 */	/**空白行をページエンドまで出力する*/
		wai_tsk(5);
	}
#endif
#if (PRO_PRINT_TYPE == LED)
	while ((PrinterStatus[PRN_STATUS_0] & PRN_S0_PAPER_CARRY)
	/*	&& ((UWORD)(SYS_GeneralTimer - PRN_TopStartTime) < PRN_t11Table[SelectedPaper]) */
		&& !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER)) {
		/* ストップキー押下で原稿排出中にジャムが発生するおそれあり */
		wai_tsk(5);
	}
#endif
	/*
	** ジャム発生時にLST_PrintErrorDetectTask()より上記タイマー処理の方が
	** 早く終了する場合があるので、次に処理でウェイトする。
	** 症状：ジャム発生しているのにも関わらず"Complete”表示が出る。
	** By S.Kawasaki 1996/07/15
	*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

	safety_timer = SYS_GeneralTimer;
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER) { /** ジャムリカバー中であれば */
		if (PRN_PGEND_DetectFlag != 2) {
			while ((PRN_PGEND_DetectFlag != 2)&&((UWORD)(SYS_GeneralTimer - safety_timer) < (UWORD)(2 * 60 * 100))) { /** 安全の為２分タイマーを起動 */
				wai_tsk(10); /** 100msウェイト */
			}
		}
	}

#endif
	DMA_AutoInitializeDisable(DMA_DRAM_PRNCDC_CH);		/** DMAU AutoInitializeMode Disable */
	DMA_RequestMask(DMA_DRAM_PRNCDC_CH);					/**転送End*/
	del_tsk(&tskno_datatransferpage);	/** コーデックからプリンタにDMAするタスク */
	del_tsk(&tskno_printererrordetect);	/* プリンタのジャムを検出し擬似HSYNCを発生するタスク */
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_JAM_RECOVER;	/* 桐用ＪＡＭリカバー中解除 *//* 1994/10/28 */
	if (!ReleaseCodec(PRINTER_CODEC, CODEC_CHARACTER_PRINT)) {	/**プリンタコーデックを開放する*/
		SaveReturnAddressAndJumpBegin();	/*941202 Kotani*/
	}
	LST_EndPrinter();		/* /TOP割込みを禁止する */
#if (PRO_PRINT_TYPE == LED)
	LST_StopPrinter();
	if ((PRN_JamPrintStopFlag == 1) || (PRN_PGEND_DetectFlag == 2)) {
		LST_StopMotor();
		PRN_ResetPrinterGA();
	}
	else {
		PRN_SetPrintCount(SelectedPaper);
	}
#endif

#if (PRO_PRINT_TYPE == LASER)
	/** 2Lineのトグルバッファに白データを貼る */
	PRN_OutDummyHSYNC();	/* プリント後に移動  by NOBUKO  Nov.10,94 */
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
	if (0) {
#else

	if (PRN_PGEND_DetectFlag == 2) {	/**ページエンド時ペーパジャム発生(LST_PrinterErrorDetectTaskでセット)*/
#endif


#if (PRO_PRINT_TYPE == LASER)
		return(MSG_PRN_LST_STOPSW_ON);
#endif
#if (PRO_PRINT_TYPE == LED)
		return(MSG_PRN_LST_PAPER_ERROR);
#endif
	}

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT) {
		/** ストップキーが押された場合 */
		return(MSG_PRN_LST_STOPSW_ON);
	}
	if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {
		/**	サイズエラーの場合 Add By H.Hirao 1996/06/13	*/
		return(MSG_PRN_LST_STOPSW_ON);
	}
#endif

	return(OK);
}



/*************************************************************************
	module		:[プリンタをクローズする(イメージプリント時のキャラクタプリント終了時)]
	function	:[
		1.プリンタをクローズする(イメージプリント時のキャラクタプリント終了時)
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/07/27]
	auther		:[吉川弘康]
*************************************************************************/
WORD	ListImagePreClose(void)
{
	UBYTE debug;
#if defined(ANZU_L)	/* debug 1997/12/09 */
	if (LST_Debug1) {
		LST_Debug1 = 0;
	}
	else {
		outp((unsigned long)0,(unsigned char)0);
		debug++;
	}
#endif

#if (PRO_PRINT_TYPE == LASER)
	/* ここでTOP割込みを禁止すると画データ付き送信証プリントで
	** 画データのみ次ページにプリントする際、TOP検出するまでにこのルーチンが
	** コールされるためジャムが発生する By M.Tachibana 1997/09/09
	** ANZUも確認してね
	*/
	LST_EndPrinter();		/* /TOP割込みを禁止する */
#endif

	ListLineFeed(4);		/**２面バッファをクリアする*//* 出力する空白行数 */
	wai_tsk(14);	/**Warning!! Effect for Pat_journal Print*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_PRINT_JAM_RECOVER) {

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

		if (PRN_PGEND_DetectFlag != 2) {
			wai_evt(EVT_DMA_DRAM_PRNCDC);	/**DummyHSYNC Outの終了を待つ*/
		}
#endif

	}

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	/* ここでアボートしてイメージのプリントするときコーデックの初期化をしない様にする
	** DMAが初期化することによりリストと原稿の間で位相ずれが発生する
	** by M.Kotani 1998/01/30
	** POPLAR_Lも確認してね
	*/
	DMA_AutoInitializeEnable(DMA_DRAM_PRNCDC_CH);		/** DMAU AutoInitializeMode Enable */
	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, 640);			/**転送量の設定*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/
	AbortCodecCommand(PRINTER_CODEC);	/*データ転送をアボートする*/
	DMA_AutoInitializeDisable(DMA_DRAM_PRNCDC_CH);		/** DMAU AutoInitializeMode Disable */
	DMA_RequestMask(DMA_DRAM_PRNCDC_CH);					/**転送End*/
#endif

#if (PRO_PRINT_TYPE == LED)	/* V851 原稿付きﾁｪｯｸﾒｯｾｰｼﾞごみ対策 By M.Tachibana 2002/09/28 */
 #if defined(POPLAR_H) && defined(JP0)
	if (SYB_MachineUniqSwitch[90] & 0x10) {	/* UNIQ_SW_J0 */
		PRN_DisableStrobe();
	}
 #endif
#endif

	del_tsk(&tskno_datatransferpage);		/** コーデックからプリンタにDMAするタスク */
	del_tsk(&tskno_printererrordetect);		/* プリンタのジャムを検出し擬似HSYNCを発生するタスク */
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_JAM_RECOVER;	/* 桐用ＪＡＭリカバー中解除 *//* 1994/10/28 */
	if (!ReleaseCodec(PRINTER_CODEC, CODEC_CHARACTER_PRINT)) {	/**プリンタコーデックを開放する*/
		SaveReturnAddressAndJumpBegin();	/*941202 Kotani*/
	}
	return(OK);
}



/*************************************************************************
	module		:[プリンタをクローズする(イメージプリント時)]
	function	:[
		1.プリンタをクローズする(イメージプリント時)
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[1994/07/27]
	auther		:[吉川弘康]
*************************************************************************/
WORD	ListImageClose(void)
{
	LST_EndPrinter();		/* /TOP割込みを禁止する */

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

	if (!PRN_TopStartTime) {		/* By H.Y 1994/10/31 */
		PRN_TopStartTime = SYS_GeneralTimer;
	}
#endif

	/*
	** ジャム発生時のプリンターリセット処理追加のため
	** By S.Kawasaki 1996/07/17
	*/
#if (PRO_PRINT_TYPE == LASER)
	/* while ((UWORD)(SYS_GeneralTimer - PRN_TopStartTime) < PRN_t11Table[SelectedPaper]) {	By S.Kawasaki 1996/07/17 *//** 原稿排出終了までウエイトする*/
	while (((UWORD)(SYS_GeneralTimer - PRN_TopStartTime) < PRN_t11Table[SelectedPaper]) &&
			!(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM) &&
			(PRN_JamPrintStopFlag != 1)) {	/** 原稿排出終了までウエイトする*/
		wai_tsk(5);
	}
#endif
#if (PRO_PRINT_TYPE == LED)
	while ((PrinterStatus[PRN_STATUS_0] & PRN_S0_PAPER_CARRY)
	/*	&& ((UWORD)(SYS_GeneralTimer - PRN_TopStartTime) < PRN_t11Table[SelectedPaper]) */
		&& !(SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_PAPER_JAM)	/* このビットはＯＮしない */
		&& (PRN_JamPrintStopFlag != 1)) {	/** 原稿排出終了までウエイトする*/
		wai_tsk(5);
	}
#endif

#if (PRO_PRINT_TYPE == LED)
	LST_StopPrinter();
#endif

	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_PRINT_JAM_RECOVER;	/* 桐用ＪＡＭリカバー中解除 *//* 1994/11/28 */
	return(OK);
}



/*************************************************************************
	module		:[画像付きリストのプリントのメイン関数]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[Apr.17,1996		送信証の仕様変更により蓄積原稿を印字することになった。ﾁｪｯｸﾒｯｾｰｼﾞ
								と処理が同じなのでここに追加するが、本当はPRN_ImagePrintTask()で
								分岐すべきだと思う。								By H.Hirao
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1994/07/28]
	author		:[吉川弘康]
*************************************************************************/
void	ListImagePrintMain(void)
{
	WORD ret;

	ret = 0;				/** Add By H.Hirao 1996/07/09 */
	LST_PageCounter = 0;	/* Add By M.Tachibana 1997/05/27 */

	/* By H.Y 1995/09/19 Start */
	/* プリンタがウオームアップ中にカバーオープンすると、「プリント中」表示のままとなる件 */
	if (CharacterPrint(LST_OPEN) != OK) {
		return;
	} /* By H.Y 1995/09/19 End */

	/**if文以下5行を追加 (ANZU) By H.Hirao Apr.17,1996 */
	switch( SYS_DocumentPrintClass ) {	/**TCR ON */
	case	SYS_PRINT_CLASS_LIST_MONITOR:
		ret = Print_TxConf( LST_ERR_CLOSE_NOT );
		break;
#if (PRO_CIPHER == ENABLE)
	case	SYS_PRINT_CLASS_LIST_CIPHER:
		ret	= Print_CipherRecieve_Notice();
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	case	SYS_PRINT_CLASS_RETURNED_MAIL:
		/* ｲﾝﾀｰﾈｯﾄFAX　不達通知ﾌﾟﾘﾝﾄのﾊﾟｽ。原稿付きﾁｪｯｸﾒｯｾｰｼﾞのような感じで印字する　*/
		ret	= PrintReturnedMailTextPart( LST_ERR_CLOSE_NOT );
		break;
#endif
	default:
		ret = Doc_ChkMsg();
		break;
	}
	/**	ListClose()からジャムやサイズエラーでぬけてきた場合	*/ /* Add By H.Hirao 1996/06/14 */
	if (( ret == MSG_PRN_LST_STOPSW_ON ) ||						/* 97/12/09 By M.Kuwahara */
	    ( ret == MSG_PRN_LST_PAPER_ERROR )) {
		/** ストップキーが押された場合 */

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else
		if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT) {
			PRN_JamPrintStopFlag = 2;
		}
		/**	ページエンド時ペーパジャム発生(LST_PrinterErrorDetectTaskでセット)	*/
		if (PRN_PGEND_DetectFlag == 2) {
			PRN_JamPrintStopFlag = 1;
		}
		/**	サイズエラーの場合	*/
		if (SYS_MachineStatus[SYS_PRINTER_STATUS2] & SYS_PRINTER_SIZE_ERROR) {
			PRN_JamPrintStopFlag = 1;	/**	ジャム扱いにして再起動する	*/
		}
#endif

#if (PRO_PRINT_TYPE == LED)
/*		LST_StopPrinter();		@* By M.Tachibana 1997/11/03*//* 97/12/09 By M.Kuwahara */
#endif

#if defined(ANZU_L)	/* debug 1997/12/09 */
	if (tskno_datatransferpage != 0xFFFF) {
		outp((unsigned long)0,(unsigned char)0);
	}
	if (tskno_printererrordetect != 0xFFFF) {
		outp((unsigned long)0,(unsigned char)0);
	}
#endif

		return;
	}
	ListImagePreClose();

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 198.6.1 K.Kawata */
#else

	if (PRN_PGEND_DetectFlag == 2) {	/**ヘッダ部で既にジャムしていた場合*/
		PRN_JamPrintStopFlag = 1;	/**ジャム発生によりプリント停止フラグをセット*/
	}
	else {
		LST_ImagePrint();
	}
#endif

	ListImageClose();
}



/*************************************************************************
	module		:[選択用紙確定]
	function	:[
		どのサイズの用紙が選択されているかを調べる。
	]
	common		:[
	]
	condition	:[]
	commment	:[]
	return		:[用紙サイズ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1994/09/01]
	author		:[小谷正樹]
*************************************************************************/
void	LST_SelectPaperSize(void)
{
#if (PRO_PRINT_TYPE == LASER)
	UBYTE cassette;	/* プリントカセット(上段/下段) */

	/** カセット選択 */
	if ( SYS_DocumentPrintItem == LST_PATTERN_PRINT && SYS_DocumentPrintNo != LST_CLEANING_PAPER) {
 #if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/30 */
		/**テストプリントのとき(クリーニングペーパーを除く 追加 石橋正和 94/09/13)*/
		/** 上段カセットにリストプリントでサポートしている記録紙がセットされている場合 */
		/** テストプリントはすべての紙サイズに対応したのでコメントにします By H.H 1996/11/21 */
		/* if (CMN_CheckSuportPaperExist(SYS_UPPER_CASSETTE)) { */

  #if (PRO_PRIORITY_CASSETTE	== DISABLE)	/* 記録紙選択でカセット優先 by O.Kimoto 1997/02/18 */
			if (SYS_Paper1Size == SYS_A3_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A3_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_B4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_B4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LG_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else {
				cassette = PRN_MAIN_CASSETTE;
			}
		/* } */ /* テストプリントは全ての紙サイズに対応したのでコメントにします By H.H 1996/11/21 */
		/* 上段カセットにリストプリントでサポートしている記録紙がセットされていない場合 */
		/* else { */
			/* cassette = PRN_AUX_CASSETTE; */
		/* } */
  #else
 			/* 基本的に、上下段の見る順番を入れ替えただけです。
 			** 尚、最後のＦ４に付いては変更していません。
 			** また、いずれのＩＦ文にも引っかからない場合は下段とします
 			** ただし、この関数は記録紙無しが発生していない状態で呼ばれることが
 			** 大前提です。
 			** by O.Kimoto 1997/02/18
 			*/
			if (SYS_Paper2Size == SYS_A3_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A3_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_B4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_B4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LG_PAPER) { /* 追加 (For F-150) 97/02/18 By O.Kimoto */
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LG_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_F4_PAPER) { /* 追加 (For F-150) 97/02/18 By O.Kimoto */
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else {
				cassette = PRN_AUX_CASSETTE;
			}
  #endif
 #else
		/**テストプリントのとき(クリーニングペーパーを除く 追加 石橋正和 94/09/13)*/
  #if (PRO_PRIORITY_CASSETTE	== DISABLE)	/* 記録紙選択でカセット優先 by O.Kimoto 1997/02/18 */
		if (SYS_Paper1Size == SYS_A3_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A3_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_B4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_B4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LG_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else {
			cassette = PRN_MAIN_CASSETTE;
		}
  #else
		/* 基本的に、上下段の見る順番を入れ替えただけです。
		** 尚、最後のＦ４に付いては変更していません。
		** また、いずれのＩＦ文にも引っかからない場合は下段とします
		** ただし、この関数は記録紙無しが発生していない状態で呼ばれることが
		** 大前提です。
		** by O.Kimoto 1997/02/18
		*/
		if (SYS_Paper2Size == SYS_A3_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A3_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_B4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_B4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LT_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LG_PAPER) { /* 追加 (For F-150) 97/02/18 By O.kimoto */
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LG_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_F4_PAPER) { /* 追加 (For F-150) 97/02/18 By O.kimoto */
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/03/21 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else {
			cassette = PRN_AUX_CASSETTE;
		}
  #endif
 #endif
	}
	/**リストプリントのとき*/
	else {
 #if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/30 */
		if (CMN_CheckSuportPaperExist(SYS_1ST_CASSETTE)) {

  #if (PRO_PRIORITY_CASSETTE	== DISABLE)	/* 記録紙選択でカセット優先 by O.Kimoto 1997/02/18 */
			if (SYS_Paper1Size == SYS_A4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_B4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_B4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A3_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A3_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LT_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LT_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LG_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LG_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A4R_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A4R_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_B5_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_B5_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A5_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A5_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/02/05 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else {
				cassette = PRN_MAIN_CASSETTE;
			}
		}
		else {
			cassette = PRN_AUX_CASSETTE;
		}
  #else
			/* 基本的に、上下段の見る順番を入れ替えただけです。
			** 尚、最後のＦ４に付いては変更していません。
			** また、いずれのＩＦ文にも引っかからない場合は下段とします
			** ただし、この関数は記録紙無しが発生していない状態で呼ばれることが
			** 大前提です。
			** by O.Kimoto 1997/02/18
			*/
			if (SYS_Paper2Size == SYS_A4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_B4_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_B4_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A3_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A3_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LT_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LT_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_LG_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_LG_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A4R_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A4R_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_B5_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_B5_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_A5_PAPER) {
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_A5_PAPER) {
				cassette = PRN_MAIN_CASSETTE;
			} else if (SYS_Paper2Size == SYS_F4_PAPER) { /* 追加 (For F-150) 97/02/18 By O.kimoto */
				cassette = PRN_AUX_CASSETTE;
			} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/02/05 H.Hirao */
				cassette = PRN_MAIN_CASSETTE;
			} else {
				cassette = PRN_AUX_CASSETTE;
			}
		}
		else {
			cassette = PRN_AUX_CASSETTE;
		}
  #endif
 #else

  #if (PRO_PRIORITY_CASSETTE	== DISABLE)	/* 記録紙選択でカセット優先 by O.Kimoto 1997/02/18 */
		if (SYS_Paper1Size == SYS_A4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_B4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_B4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A3_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A3_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LT_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LT_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LG_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LG_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A4R_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A4R_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_B5_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_B5_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A5_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A5_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/02/05 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else {
			cassette = PRN_MAIN_CASSETTE;
		}
  #else
		/* 基本的に、上下段の見る順番を入れ替えただけです。
		** 尚、最後のＦ４に付いては変更していません。
		** また、いずれのＩＦ文にも引っかからない場合は下段とします
		** ただし、この関数は記録紙無しが発生していない状態で呼ばれることが
		** 大前提です。
		** by O.Kimoto 1997/02/18
		*/
		if (SYS_Paper2Size == SYS_A4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_B4_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_B4_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A3_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A3_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LT_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LT_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_LG_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_LG_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A4R_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A4R_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_B5_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_B5_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_A5_PAPER) {
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_A5_PAPER) {
			cassette = PRN_MAIN_CASSETTE;
		} else if (SYS_Paper2Size == SYS_F4_PAPER) { /* 追加 (For F-150) 97/02/18 By O.kimoto */
			cassette = PRN_AUX_CASSETTE;
		} else if (SYS_Paper1Size == SYS_F4_PAPER) { /* 追加 (For ANZU) 96/02/05 H.Hirao */
			cassette = PRN_MAIN_CASSETTE;
		} else {
			cassette = PRN_AUX_CASSETTE;
		}
  #endif
 #endif
	}
	if (cassette == PRN_MAIN_CASSETTE) {
		SelectedPaper = SYS_Paper1Size;
	} else {
		SelectedPaper = SYS_Paper2Size;
	}
	SelectedCassette = cassette;
	PRN_SelectCassette(SelectedCassette);		/** カセット選択 */

#endif

#if (PRO_PRINT_TYPE == LED)
	UBYTE i;
	UBYTE cassette;
	UBYTE primary_size;

	/* 優先記録紙サイズ対応 By M.Tachibana 1999/10/06  */
	if (SYS_DocumentPrintItem != LST_PATTERN_PRINT) {	/*普通のリスト*/
		primary_size = CHK_UNI_PrimaryListSize();
	}
	else {
		primary_size = CHK_UNI_PrimaryTestSize();
	}
	if (primary_size != 0) {
		switch (primary_size) {
		case 1:	/* B4 */
			primary_size = SYS_B4_PAPER;
			break;
		case 2:	/* A4 */
			primary_size = SYS_A4_PAPER;
			break;
		case 3:	/* B5R */
			primary_size = SYS_B5R_PAPER;
			break;
		case 4:	/* A5R */
			primary_size = SYS_A5R_PAPER;
			break;
		case 5:	/* LT */
			primary_size = SYS_LT_PAPER;
			break;
		case 6:	/* LG */
			primary_size = SYS_LG_PAPER;
			break;
		case 7:	/* F4 */
			primary_size = SYS_F4_PAPER;
			break;
		default:
			primary_size = SYS_A4_PAPER;
			break;
		}
		for (i = 0; i <= PRN_3RD_CASSETTE; i++) {
			if (*PaperSizeTable[i] == primary_size) {
				SelectedPaper = *PaperSizeTable[i];
				SelectedCassette = i;
				return;
			}
		}
	}
	/* 優先記録紙サイズ対応 ここまで  */

	/*------------------------------------------------------------------------
	** 手差しのリストプリントはなし（カセットＭＡＸはPRN_CASSETTE_MAX - 1）
	*/

	/* かならず、いづれかのカセットに用紙があるはず */
	for (i = 0; i <= PRN_3RD_CASSETTE; i++) {
		if ((*PaperSizeTable[i] != SYS_NO_PAPER) && (*PaperSizeTable[i] != SYS_NO_CASSETTE)) {
			break;
		}
	}

	/*---------------------------------------------------------------------------
	** 複数枚のリストプリントで１つのカセットだけ記録紙を入れておく
	** １枚プリント中にカセットを開け、次のプリント起動前に（後クリーニング中に）
	** にカセットを閉じた場合、ｉ＝３となり手差し用紙を引いてくる
	**  By M.Tachibana 1998/02/25
	*/
	if (i > PRN_3RD_CASSETTE) {
		SelectedPaper = SYS_NO_PAPER;
		SelectedCassette = PRN_NO_CASSETTE;
		return;
	}

	cassette = i;
	/** カセット選択 */
	if ( SYS_DocumentPrintItem == LST_PATTERN_PRINT && SYS_DocumentPrintNo != LST_CLEANING_PAPER) {
		for (; i <= PRN_3RD_CASSETTE; i++) {
			if ((*PaperSizeTable[i] != SYS_NO_PAPER) && (*PaperSizeTable[i] != SYS_NO_CASSETTE)) {
				if (PRN_PatternPrintSizeTable[*PaperSizeTable[i]] < PRN_PatternPrintSizeTable[*PaperSizeTable[cassette]]) {
					cassette = i;
				}
			}
		}
	}
	/**リストプリントのとき*/
	else {
		for (; i <= PRN_3RD_CASSETTE; i++) {
			if ((*PaperSizeTable[i] != SYS_NO_PAPER) && (*PaperSizeTable[i] != SYS_NO_CASSETTE)) {
				if (PRN_ListPrintSizeTable[*PaperSizeTable[i]] < PRN_ListPrintSizeTable[*PaperSizeTable[cassette]]) {
					cassette = i;
				}
			}
		}
	}

	/** カセット選択 */
	SelectedPaper = *PaperSizeTable[cassette];
	SelectedCassette = cassette;

#endif
}

/*************************************************************************
	module		:[機器設定リスト用、行間隔挿入]
	function	:[
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[Feb 28,1996]
	auther		:[平尾英典]
*************************************************************************/
WORD	ListSpacePrint(void)
{
	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, LST_PRM_SPACE*40);			/**転送量の設定*/
	CMN_DisableInterrupt();				/**割り込み禁止*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/
	wai_evt(EVT_DMA_DRAM_PRNCDC);		/**転送終了を待つ*/
	return(OK);
}

/*************************************************************************
	module		:[ﾃｽﾄﾊﾟﾀｰﾝﾌﾟﾘﾝﾄ用、ﾍｯﾄﾞ挿入]
	function		:[ﾃｽﾄﾊﾟﾀｰﾝﾌﾟﾘﾝﾄのTopから9ﾗｲﾝに白ﾃﾞｰﾀを入れるための関数
	]
	return		:[エラーコード]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyward		:[LST]
	date		:[Apr.04,1996]
	auther		:[平尾英典]
*************************************************************************/
WORD	ListHeadPrint(void)
{
	DMA_SetDMA_Address(DMA_DRAM_PRNCDC_CH, DMA_MEMORY_TO_IO, DMA_start_address);	/**転送アドレスの設定*/
	DMA_SetDMA_Counter(DMA_DRAM_PRNCDC_CH, LST_WORD_WIDTH);		/**転送量の設定*/
	CMN_DisableInterrupt();				/**割り込み禁止*/
	DMA_RequestEnable(DMA_DRAM_PRNCDC_CH);				/**転送許可（開始）*/
	wai_evt(EVT_DMA_DRAM_PRNCDC);		/**	転送終了を待つ	*/
	return(OK);
}



/* 1997/12/09 debug */
void LST_DebugInit(void)
{
	tskno_printererrordetect = 0xFFFF;
	LST_Debug1 = 0;
}

#endif	/* 1998/06/11 H.Yoshikwa */
