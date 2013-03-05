/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: CMN_CHK.C
*	Author		: 橘正樹
*	Date		: 1996/11/02
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニタ
*	Description	:
*	Maintenance	:
*				: Original:\src\kobe\anzu\src\cmn_chk.c
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\syslocal.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mntsw_i.h"	/* 1997/12/19 */

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\man_data.h"
#include "\src\atlanta\ext_v\rom_tbl.h"

#include "\src\atlanta\sh7043\define\io_pro.h"

#if (PRO_MULTI_LINE == ENABLE)
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\define\unisw_a.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\mlt_data.h"
#endif
#if (PRO_PC_PRINT == ENABLE)
#include "\src\atlanta\define\dpr_def.h"
#endif

/*************************************************************************
	module		:[プリンタ使用中か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:プリンタ使用中
		2.TRUE :プリンタ非使用中

		-> 混乱してしまうのでリターン値の論理を逆にさせてもらいます。1996/03/15 Eguchi
		TRUE	:プリンタ使用中
		FALSE	:プリンタ非使用中
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/15]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	CMN_CheckPrinting(void)
{
	if(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {
		return (TRUE);
	}
	else {
		return (FALSE);
	}
}


/*************************************************************************
	module		:[プリント可能か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:プリント不可能
		2.TRUE :プリント可能
	]
	common		:[]
	condition	:[]
	comment		:[
				作り替えた 1996/03/15 Eguchi
				ＰＣプリントを条件コンパイルとして、内容を変更 By J.Miyazaki
				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckPrintEnable(UWORD request_machine_status)
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/**スキャナー使用中のリストプリントはできない。追加 M.Kotani 1997/10/16*/
	if (request_machine_status == SYS_LIST_PRINT) {
		if ((CMN_CheckScanEnable() == FALSE)
		&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_IN) == 0)
		&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) == 0)) {
			return (FALSE);		/** プリント不可能 */
		}
	}
#endif
#if (PRO_PRINT_TYPE == LASER)
 #if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/25 */
	if ((CMN_CheckSuportPaperExist(SYS_AUTO_CASSETTE) == FALSE)		/** 紙なし */
	||	(CMN_CheckNoPrinterError()		== FALSE)		/** プリンターエラーあり */
	||	(CMN_CheckPrinterCoverClose()	== FALSE)		/** プリンターカバーオープン */
	||	(CMN_CheckBothCassetteClose()	== FALSE)		/** どちらかのカセットが開いている */
	||	(CMN_CheckPrinting()			== TRUE )) {	/** プリント中 */
		return (FALSE);		/** プリント不可能 */
	}
	else {
		return (TRUE);
	}
 #else
	if ((CMN_CheckPaperExist()		== FALSE)			/** 紙なし */
	||	(CMN_CheckNoPrinterError()	== FALSE)			/** プリンターエラーあり */
	||	(CMN_CheckPrinterCoverClose() == FALSE)			/** プリンターカバーオープン */
	||	(CMN_CheckBothCassetteClose() == FALSE)			/** どちらかのカセットが開いている */
	||	(CMN_CheckPrinting()		  == TRUE )) {		/** プリント中 */
		return (FALSE);		/** プリント不可能 */
	}
	else {
		return (TRUE);
	}
 #endif
#endif
#if (PRO_PRINT_TYPE == LED)
	if ((CMN_CheckPaperExist()		== FALSE)			/** 紙なし */
	||	(CMN_CheckNoPrinterError()	== FALSE)			/** プリンターエラーあり */
	||	(CMN_CheckPrinting()		== TRUE )) {		/** プリント中 */
		return (FALSE);		/** プリント不可能 */
	}
	else {
		return (TRUE);
	}
#endif
}

/*************************************************************************
	module		:[記録紙の有無を調べる]
	function	:[
		1.
	]
	return		:[
				TRUE:上下段カセットどちらかに記録紙あり
				FALSE:上下段カセットともに記録紙なし
				]
	common		:[
				SYS_MachineStatus:
				SYS_SecondCasseteFlag:下段カセットユニット有無フラグ
				]
	condition	:[]
	comment		:[杏で新規につくった]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/15]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE	CMN_CheckPaperExist(void)
{
#if (PRO_PRINT_TYPE == LASER)
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)	/* 上段記録紙なし*/
	&& ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) || (SYS_SecondCassetteFlag == 0))) {	/* 下段記録紙なしまたは下段カセットなし */
		return(FALSE);	/* 記録紙なし */
	}
	return(TRUE);
#endif
#if (PRO_PRINT_TYPE == LED)
	if (((SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_1ST_UNIT)
	  && !(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER))
	 || ((SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT)
	  && !(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2))
	 || ((SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT)
	  && !(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER3))) {
		return(TRUE);
	}
	return(FALSE);	/* 記録紙なし */
#endif
}

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/25 */
/*************************************************************************
	module		:[記録紙の有無及び、サポート記録紙の有無]
	function	:[
		1.
	]
	return		:[
				TRUE:上下段カセットどちらにも記録紙あり
					:下段カセットに記録紙があり
					:上段カセットに記録紙があり、かつ、それがＰＣプリント
					 以外のプリントでサポートしている用紙の場合
				FALSE:上下段カセットともに記録紙なし
					 :上段カセットに記録紙があっても、ＰＣプリント以外の
					  プリントでサポートしていない用紙の場合
				]
	common		:[
				SYS_MachineStatus:
				SYS_SecondCasseteFlag:下段カセットユニット有無フラグ
				]
	condition	:[]
	comment		:[ＰＣプリント用に新規につくった]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/09/25]
	author		:[宮崎]
*************************************************************************/
UBYTE	CMN_CheckSuportPaperExist(
UBYTE	cassette)
{
	if (cassette == SYS_AUTO_CASSETTE) {
		if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
		&& ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) || (SYS_SecondCassetteFlag == 0))) {
			return (FALSE); /** 記録紙なしをリターンします */
		}
		/** 上段に記録紙があり、下段に記録紙がない場合 */
		else if (!(SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER)
		&&	((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) || (SYS_SecondCassetteFlag == 0))) {
			/** 上段にＰＣプリント以外のプリントでサポートしていない記録紙がセットされている場合 */
#if defined(USA)	/* 1997/02/21 By J.Miyazaki 東南アジア仕様が入って来たら考える必要あり*/
			if ((SYS_Paper1Size != SYS_LT_PAPER) && (SYS_Paper1Size != SYS_LG_PAPER)) {
#elif defined(GBR) || defined(EC1) || defined(EC2) || defined(EC3) || defined(EUR) /* Add GBR EC BY Hirao 1997/04/23 */
																					/* 欧州仕様追加 by M.H 1999/09/15 */
			if ((SYS_Paper1Size != SYS_A4_PAPER)) {
#else
			if ((SYS_Paper1Size != SYS_A4_PAPER) && (SYS_Paper1Size != SYS_F4_PAPER)) { /* 東南アジア仕様 Add BY Hirao 1997/04/23 */
#endif
				return (FALSE);
			}
		}
	}
	else if (cassette == SYS_1ST_CASSETTE) {
		if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) {
			return (FALSE);
		}
		else {
#if defined(USA)
			if ((SYS_Paper1Size != SYS_LT_PAPER) && (SYS_Paper1Size != SYS_LG_PAPER)) {
#elif defined(GBR) || defined(EC1) || defined(EC2) || defined(EC3) || defined(EUR) /* Add GBR EC BY Hirao 1997/04/23 */
																					/* 欧州仕様追加 by M.H 1999/09/15 */
			if (SYS_Paper1Size != SYS_A4_PAPER) {
#else
			if ((SYS_Paper1Size != SYS_A4_PAPER) && (SYS_Paper1Size != SYS_F4_PAPER)) { /* 東南アジア仕様 Add BY Hirao 1997/04/23 */
#endif
				return (FALSE);
			}
		}
	}
	else if (cassette == SYS_2ND_CASSETTE) {
		if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER2) || SYS_SecondCassetteFlag == 0) {
			return (FALSE);
		}
	}
	return (TRUE);
}
#endif

/*************************************************************************
	module		:[プリンターエラーの有無を調べる]
	function	:[
		1.
	]
	return		:[
					TRUE:プリンターエラーなし
					FALSE:プリンターエラーあり
				]
	common		:[]
	condition	:[]
	comment		:[杏で新規につくった]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/15]
	author		:[江口]
*************************************************************************/
UBYTE	CMN_CheckNoPrinterError(void)
{
#if (PRO_PRINT_TYPE == LASER)
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & (SYS_PRINTER_NO_CARTRIDGE		|
												   SYS_PRINTER_NO_INK ))
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS2] & (SYS_PRINTER_PAPER_JAM		|
												   SYS_PRINTER_SIZE_ERROR		| /* By S.Kawasaki 1996/03/15 */
												   SYS_PRINTER_EXIT_JAM			|
												   SYS_PRINTER_MISS_FEED_JAM	|
												   SYS_PRINTER_REG_JAM ))
	 || (SYS_MachineStatus[SYS_PRINTER_STATUS3] & (SYS_PRINTER_RESET_ERROR		| /* By S.K Feb.23,1996 */
												   SYS_PRINTER_LASER_ABNORMAL	| /* By S.K Feb.23,1996 */
												   SYS_PRINTER_FAN_ABNORMAL		|
												   SYS_PRINTER_MOTOR_ABNORMAL	|
												   SYS_PRINTER_FUSER_ABNORMAL	|
												   SYS_PRINTER_SERIAL_ERROR ))) {/*プリンターエラー*/
		return (FALSE);
	}

	/*
	** トナー無し時のエラー発生時に印字の継続を行うかどうかのメモリスイッチ
	** を追加。
	** 初期値：印字継続
	** By S.Kawasaki 1996/06/20
	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_FEW_TONER) {
		if (!CHK_UNI_ContinueToPrintForTonar()) {	/** トナー無し時には印字中止 */
			return(FALSE);
		}
#if	(PRO_LOW_TONER_PRINT == PRINT_LIMIT)
		/** F-150 Low Toner時のプリント枚数制限処理 By O.Kimoto 1996/12/26 */
		if (SYB_RestPrintPages <= 0) {
			return(FALSE);
		}
#endif
	}
	return (TRUE);
#endif
#if (PRO_PRINT_TYPE == LED)
	if (CMN_CheckPrinterError() == TRUE) {
		return(FALSE);
	}
	return(TRUE);
#endif
}



/*************************************************************************
	module		:[プリンターカバーの状態を調べる]
	function	:[
		1.
	]
	return		:[
				TRUE :プリンターカバークローズ
				FALSE:プリンターカバーオープン
				]
	common		:[]
	condition	:[]
	comment		:[杏で新規につくった]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/15]
	author		:[江口]
*************************************************************************/
UBYTE	CMN_CheckPrinterCoverClose(void)
{
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN) {	/**カバーオープン */
		return (FALSE);
	}
	return (TRUE);
}



/*************************************************************************
	module		:[カセットの状態を調べる]
	function	:[
		1.
	]
	return		:[
				TRUE	:上下段カセットともクローズ
				FALSE	:]
	common		:[]
	condition	:[]
	comment		:[杏で新規につくった]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/15]
	author		:[江口]
*************************************************************************/
UBYTE	CMN_CheckBothCassetteClose(void)
{
#if (PRO_PRINT_TYPE == LASER)
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE1_OPEN) {	/* 上段カセットオープン */
		return (FALSE);
	}
	if ((SYS_SecondCassetteFlag == 1)	/* 下段カセットユニットあり */
	&&	(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_CASSETTE2_OPEN)) {	/* 下段カセットオープン */
		return (FALSE);
	}
	return (TRUE);
#endif
#if (PRO_PRINT_TYPE == LED)
	if (SYS_MachineStatus[SYS_COVER_STATUS] & (
											   SYS_COVER_JAM_OPEN			|
											   SYS_COVER_CASSETTE1_OPEN		|
											   SYS_COVER_CASSETTE2_OPEN		|
											   SYS_COVER_CASSETTE3_OPEN		|
											   SYS_COVER_2JAM_OPEN			|
											   SYS_COVER_3JAM_OPEN)) {
		return(FALSE);
	}
	return(TRUE);
#endif
}



/*************************************************************************
	module		:[メモリ受信原稿プリント可能か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:メモリ受信原稿プリント不可能
		2.TRUE :メモリ受信原稿プリント可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckMemRxPrintEnable(void)
{
	return(TRUE);
}

/*************************************************************************
	module		:[スキャン可能か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:スキャン不可能
		2.TRUE :スキャン可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckScanEnable(void)
{
	if(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) {
		return(FALSE);
	}
	else {
		return(TRUE);
	}
}

/*************************************************************************
	module		:[メモリ受信可能か否か]
	function	:[
				1.代行受信が１０件未満
				2.メモリーの空きブロックがＣＣＩＴＴ、ＮＯ．１チャート４枚分以上あり。
				3.インデックステーブルに空きテーブルあり。
				4.上記の３つの条件が全て成立したばあい、メモリー受信可能。
				代行受信管理の変更で見方を変更 1997/03/18  By T.Yamaguchi
	]
	return		:[
		1.FALSE:メモリ受信不可能
		2.TRUE :メモリ受信可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckMemoryReceiveEnable(void)
{
/* ●POPLAR変更 by 1997/03/07  By T.Yamaguchi */

	UWORD i;

	/*
	 * 通信が起動されてからコールする事
	*/
	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {
		if ((SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE) || (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_SETTING)) {
			if (SYB_MemoryRxPrint[i].StackNumber == 0) {
				break;
			}
		}
	}
	if (i >= SYS_MEMORY_RX_MAX) {
		return(FALSE);
	}

	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
		return(TRUE);
	}
	else {
		return(FALSE);
	}

#if 0
*	if ((SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_EMPTY)	/** 代行受信管理テーブルに空きあり */
*	&&	((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)	/** メモリーブロックに空きあり	   */
*	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
*		return(TRUE);
*	}
*	else {
*		return(FALSE);
*	}
#endif
}


/*************************************************************************
	module		:[自動受信可能か否か]
	function	:[
	]
	return		:[
		1.FALSE:自動受信不可能
		2.TRUE :自動受信可能
	]
	common		:[]
	condition	:[]
	comment		:[桐のパス以外は削除　1995/09/07 Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckAutoCalledEnable(void)
{
	/* POPLAR変更 1997/03/10  By T.Yamaguchi */
	return(CMN_CheckMultiLineReceiveEnable());
	/* return(CMN_CheckMemoryReceiveEnable()); */

#if 0
//	if (CMN_CheckMemoryReceiveEnable() == FALSE) {	/* メモリ受信可能か否か */
//		return(FALSE);
//	}
//	else {
//		/* メモリ受信ファイル空きチェック */
//		if (CMN_GetMemoryRxPrintWritePoint() == FALSE) {
//			return(FALSE);
//		}
//		else {
//			return(TRUE);
//		}
//	}
#endif
}


#if 0	/* 削除 1997/11/20  By T.Yamaguchi */
/*************************************************************************
	module		:[マルチ回線受信可能かどうかの判断]
	function	:[
		1.空きメモリおよび空きインデックがあるかチェックする
		2.代行受信管理テーブルの空きを見つける
		3.代行受信管理テーブルにスタックＮｏをセットに使用中にする
	]
	return		:[
					0xFFFF:   受信不可
					上記以外: 受信可能（獲得した代行受信管理テーブル番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/19]
	author		:[村田 山口]
*************************************************************************/
UWORD CMN_CheckMultiLineReceiveNumber(UBYTE StackNo, UBYTE ReceiveMode)
{
	UWORD	ret;

#if (PRO_MULTI_LINE == DISABLE)	/* 1997/03/19  By T.Yamaguchi */

#if (0) /* 二重にチェックが入っている 次の１行に変更 By M.Tachibana 1997/10/04 */
//	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)
//	&& (MEM_CountTotalEmptyPage() > 0)) {	/** 空きメモリおよび空きインデックス有り */
//		ret = CMN_GetMultiLineReceiveNumber(StackNo);
//		return(ret);
//	}
//	else {
//		return(0xFFFF);
//	}
#endif
	return(CMN_GetMultiLineReceiveNumber(StackNo));

#else
	UWORD	i;

	/* オペレーションで受信専用になっている時は、着信を拒否します。
	** by O.Kimoto 1997/02/08
	*/
	if (ReceiveMode == AUTO_RECEIVE) {
		if (OPT_CountModems() >1 ) {
			if (OPT_CHK_UNI_LineTxRx(StackNo) & EXCLUSIVE_TX) {
				return(0xFFFF);
			}
		}
	}

	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)
	&& (MEM_CountTotalEmptyPage() > 0)) {	/** 空きメモリおよび空きインデックス有り */

		if (StackNo == 0) {
			ret = MAN_GetMultiLineReceiveNumber(StackNo);
			return(ret);
		}
		else {
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) {	/* 内臓モデムがある */
				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
					if (FinalRxMode == DIAGMODE) {
						return(0xFFFF);
					}
				}
				ret = MAN_GetMultiLineReceiveNumber(StackNo);
				return(ret);
			}
			else {
				for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
					if (CHK_OptionLineExist((UBYTE)i)) {
						break;
					}
				}
				if (StackNo == (UBYTE)i) {
					ret = MAN_GetMultiLineReceiveNumber(StackNo);
					return(ret);
				}
				else {
					if (CHK_OptionLineBusy((UBYTE)i)) {
						if (SYS_Opt[i].FinalRxMode == DIAGMODE) {
							return(0xFFFF);
						}
					}
					ret = MAN_GetMultiLineReceiveNumber(StackNo);
					return(ret);
				}
			}
		}
	}
	else {
		return(0xFFFF);
	}
#endif
}
#endif	/* 削除 1997/11/20  By T.Yamaguchi */

/*************************************************************************
	module		:[マルチ回線仕様時メモリ受信できるかどうか]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/09/21]
	author		:[村田]
*************************************************************************/
UBYTE CMN_CheckMultiLineReceiveEnable(void)
{
	UBYTE i;

	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */

		for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
			if (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_EMPTY) {	/** 空きを見つける */
				return(TRUE);
			}
		}
		return(FALSE);
	}
	else {
		return(FALSE);
	}
}


/*************************************************************************
	module		:[自動ダイヤル可能か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:オートダイヤル不可能
		2.TRUE :オートダイヤル可能
	]
	common		:[]
	condition	:[]
	comment		:[H8のパス削除 Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/07]
	author		:[大西]
*************************************************************************/
UBYTE	CMN_CheckAutoDialEnable(void)
{
	return(TRUE);
}

/*************************************************************************
	module		:[回線使用可能か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:回線使用不可能
		2.TRUE :回線使用可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckLineEnable(void)
{
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRE_LINE_BUSY)
	||  (tskno_FCM_Task != 0xffff)
	||	(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK)) {
		return(FALSE);
	}
	else {
		return(TRUE);
	}
#else
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)
	||	(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRE_LINE_BUSY)) {	/* add SYS_PRE_LINE_BUSY  1994/07/18 Y.Murata */
		return(FALSE);
	}
	else {
		return(TRUE);
	}
#endif
}

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
/*************************************************************************
	module		:[使用可能回線チェック]
	function	:[
		1.引数 ０：標準回線 １：拡張回線
	]
	return		:[
		1.FALSE:回線使用不可能
		2.TRUE :回線使用可能
	]
	common		:[]
	condition	:[POPLAR_H]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/11/25]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE	CMN_CheckTwiceLineEnable(UBYTE line)
{
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRE_LINE_BUSY)
	||  (tskno_FCM_Task != 0xffff)
	||	(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_HOOK_KEY_OFF_HOOK)) {
		return(FALSE);
	}
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2が標準ライン側の場合	*/
		if (line == 0) {
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK)
			||  (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK)) {
				return(FALSE);
			}
			else {
				return(TRUE);
			}
		}
		else {
			return(TRUE);
		}
	}
	else {
		if (line == 0) {
			if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK) {
				return(FALSE);
			}
			else {
				return(TRUE);
			}
		}
		else {
			if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) {
				return(FALSE);
			}
			else {
				return(TRUE);
			}
		}
	}
}
#endif


/*************************************************************************
	module		:[マルチコピー可能か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:マルチコピー不可能
		2.TRUE :マルチコピー可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckMulicopyEnable(void)
{
	if (!CMN_CheckScanEnable()) {
		return(FALSE);
	}
	if (!CMN_CheckFeederCommandEmpty()) {
		return(FALSE);
	}
	return(TRUE);
}

/*************************************************************************
	module		:[フィーダ原稿が登録中でないか否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:フィーダ原稿が登録中
		2.TRUE :フィーダ原稿が登録中でない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckFeederCommandEmpty(void)
{
#if (0) /* 1996/08/05 Eguchi EGU */
//	UBYTE i;
//	/* スキャナコマンドか否か
//	 */
//	for (i = 0; i < SYS_COM_FILE_MAX; i++) {
//		if (CMN_CheckScannerTxCommand(i)) {
//			return(FALSE);
//		}
//	}
//	return(TRUE);
#endif

	UBYTE	com_no;
	UBYTE	exec_no;
	struct	SYS_CommandData_t	*com_ptr;
	struct	SYS_ExecQueueData_t	*exec_ptr;

	/* 予約中、実行中,実行まえのもののみ対象とする */
	/* スキャナ送信のチェックメッセージ等を印字中にスキャナが使用できなくなるのを防ぐため */

	for (com_no = 0; com_no < SYS_COM_FILE_MAX; com_no++) {
		com_ptr = &SYB_CommandFile[com_no];
		if ((com_ptr->Status == SYS_CMD_WAITING)
		||	(com_ptr->Status == SYS_CMD_EXECUTE)) {	/** 予約中・実行中 */
			switch (com_ptr->Option.Item) {
			case SYS_SCANNER_TX:
			case SYS_DELAYED_SCANNER_TX:
			case SYS_SCANNER_SECURE_TX:
			case SYS_SCANNER_RELAY_BROADCAST:
			case SYS_FX_SCANNER_RELAY_TX:	/* By H.Y 1994/10/26 */
			case SYS_FX_SCANNER_SECURE_TX:	/* By H.Y 1994/10/26 */
				if (com_ptr->Status == SYS_CMD_WAITING) {
					return (FALSE);/* 予約中のスキャナコマンドあり */
				}
				else {	/* com_ptr->Status == SYS_CMD_EXECUTE */
					for (exec_no = 0; exec_no < SYS_EXEC_QUEUE_MAX; exec_no++) {
						exec_ptr = &SYB_ExecQueue[exec_no];
						if ((exec_ptr->Status >= SYS_EXEC_WAITING)
						&&	(exec_ptr->Status <= SYS_EXEC_FORWARD_EXECUTE)
						&&	(exec_ptr->Kind == SYS_COMMAND_TRX)
						&&	(exec_ptr->Number.Command == com_no)){
							/* キューに展開されたスキャナコマンドあり */
							return (FALSE);
						}
					}
				}
			}
		}
	}
	return (TRUE);
}

/*************************************************************************
	module		:[通信予約がメモリ送信か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:通信予約がメモリ送信でない
		2.TRUE :通信予約がメモリ送信
	]
	common		:[SYB_CommandFile[]]
	condition	:[]
	comment		:[
		変更履歴
		1997/07/22	by K.Watanabe
			オペレーションで、コマンドファイルセット時のメモリ送信チェックの
			時点では、コマンドファイルのステータスはまだセット中のままなので
			ステータスのチェックがあると困るので、引数を追加しました
			（ステータスをチェックする以外は全く同じ関数がオペレーションに
			　存在しているために、オプションの種別が増えると２ヶ所変更する
			　必要があるので共通化しました）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康,渡辺一章]
*************************************************************************/
UBYTE	CMN_CheckMemoryTxCommand(UBYTE com_no, UBYTE status_chk)
{
	struct SYS_CommandData_t	*com_ptr;

	com_ptr = &SYB_CommandFile[com_no];

	if (com_no < SYS_COM_FILE_MAX) {
		if (status_chk == CMN_STATUS_CHK) {
			if ((com_ptr->Status != SYS_CMD_WAITING) && (com_ptr->Status != SYS_CMD_EXECUTE)) {
				return(FALSE);
			}
		}

		switch (com_ptr->Option.Item) {
		case SYS_MEMORY_TX:
		case SYS_DELAYED_MEMORY_TX:
		case SYS_MEMORY_SECURE_TX:
		case SYS_MEMORY_RELAY_BROADCAST:
		case SYS_DELAYED_BROADCAST:
		case SYS_RELAYED_TX:
		case SYS_MEMORY_SUB_ADDRESS_TX:
		case SYS_CIPHER_TX:
			return(TRUE);
		default:
			return(FALSE);
		}
	}
	else {
		return(FALSE);
	}
}

/*************************************************************************
	module		:[通信予約がスキャナ送信か否か]
	function	:[
		1.
	]
	return		:[
		1.FALSE:通信予約がスキャナ送信でない
		2.TRUE :通信予約がスキャナ送信
	]
	common		:[SYB_CommandFile[]]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1993/12/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE	CMN_CheckScannerTxCommand(UBYTE com_no)	/* 通信予約番号 */
{
	if (com_no < SYS_COM_FILE_MAX) {
		switch (SYB_CommandFile[com_no].Status) {
		case SYS_CMD_WAITING:
		case SYS_CMD_EXECUTE:
			switch (SYB_CommandFile[com_no].Option.Item) {
			case SYS_SCANNER_TX:
			case SYS_DELAYED_SCANNER_TX:
			case SYS_SCANNER_SECURE_TX:
			case SYS_SCANNER_RELAY_BROADCAST:
				return(TRUE);
			default:
				return(FALSE);
			}
		default:
			return(FALSE);
		}
	}
	else {
		return(FALSE);
	}
}


/*************************************************************************
	module		:[原稿がフィーダに存在するか]
	function	:[
		1.
	]
	return		:[
		1.FALSE:フィーダーに原稿が存在しない
		2.TRUE :フィーダーに原稿が存在する
	]
	common		:[]
	condition	:[]
	comment		:[ANZUはDS3はない 1995/09/07 Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/04/29]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	CMN_CheckDocumentOnFeeder(void)
{
	if (DS1() || DS2()) {
		return(TRUE);
	}
	return(FALSE);
}

/*************************************************************************
	module		:[読み取り用原稿がフィーダに存在するか]
	function	:[
		1.
	]
	return		:[
		TRUE	:フィーダーに読み取り用原稿が存在する
		FALSE	:フィーダーに読み取り用原稿が存在しない
	]
	common		:[]
	condition	:[]
	comment		:[
		ポプラで原稿読み取り時に、CMN_CheckDocumentOnFeeder()で原稿の有り無しを判断していたが、
		アンズと同じ条件だと、メモリオーバー・送信中止等で原稿が途中まで繰り込まれている状態の
		原稿に対しても、読み取りが行われるので読み取り時の原稿チェックを別関数にしました
		理由）ポプラの場合、ストップキーでの原稿排出等では DS2()がONしている必要があるが、
			　読み取りの場合は DS2()がOFFしている必要があるために条件が別になるため
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/13]
	author		:[渡辺一章]
*************************************************************************/
UBYTE	CMN_CheckScanDocOnFeeder(void)
{
#if (PRO_DOC_IN == ENABLE)
	if (DS1() || DS2()) {
		return(TRUE);
	}
#else
	if (DS1() && !DS2()) {
		return(TRUE);
	}
#endif

	return(FALSE);
}

/*************************************************************************
	module		:[着信時に通信のためにプリンタがキープされたか]
	function	:[
		1. 着信時、メインはプリンターが未使用ならプリンターをキープする。
		2. 着信時、プリンターが使用中なら通信はメモリ受信する。
	]
	return		:[
		TRUE  1 : 着信時に通信のためにプリンタがキープされた
		FALSE 0 : スキャナコピー、リストプリント、イメージプリントでプリンタが使用中
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1994/05/18]
	author		:[村田]
*************************************************************************/
UBYTE	CMN_CheckFaxComPrinterEnable(void)
{
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {	/** プリンターが使用中？ */
		/** スキャナコピー、マルチコピー、リストプリント、イメージプリントでプリンタが使用中？ */
#if (PRO_PRINT_TYPE == LASER)
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_SCANNER_COPY	|
													 SYS_MULTI_COPY		|
													 SYS_LIST_PRINT		|
													 SYS_BUFFERING_PRINT|
													 SYS_IMAGE_PRINT    |
													 SYS_PRINT_WARMUP )) {	/* プリンターウォームアップの条件追加 1997/07/09  By T.Yamaguchi */
			return(FALSE);
		}
		else {
			return(TRUE);
		}
#else	/* PRO_PRINT_TYPE == LED */
		if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_SCANNER_COPY	|
													 SYS_MULTI_COPY		|
													 SYS_LIST_PRINT		|
													 SYS_BUFFERING_PRINT|
													 SYS_IMAGE_PRINT    |
													 SYS_PRINT_WARMUP ))	/* プリンターウォームアップの条件追加 1997/07/09  By T.Yamaguchi */
		|| (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINT_END_WAIT)) {	/* By M.Tachibana 1997/10/13 */
			return(FALSE);
		}
		else {
			return(TRUE);
		}
#endif
	}
	else {	/* 着信時にメインがプリンタが空いていたらキープする。PRINTERは未使用でも通信はメモリ受信をする 1994/06/02 Y.Murata */
		return(FALSE);
	}
}


/*************************************************************************
	module		:[スキャナカバーが閉じていることチェックする]
	function	:[
		1.
	]
	return		:[
		TRUE	:スキャナカバーが閉じている
		FALSE	:スキャナカバーが開いている
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/05/19]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE	CMN_CheckScannerCoverClose(void)
{
	if (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN) {
		return(FALSE);
	}
	else {
		return(TRUE);
	}
}


/*************************************************************************
	module		:[プリンターエラーチェック]
	function	:[
		1.プリンターエラーとカバーオープンをチェックする
	]
	return		:[
		TRUE	:プリンターエラーまたはプリンターカバーオープン
		FALSE	:正常
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/21]
	author		:[鈴木郁二,竹内茂樹]
*************************************************************************/
UBYTE	CMN_CheckFaxComPrinterError(void)
{
#if (PRO_PRINT_TYPE == THERMAL)	/* Add by O.Kimoto 1998/12/18 */
	if ((CMN_CheckNoPrinterError() == FALSE)		/* プリンターエラーあり */
	|| (CMN_CheckPrinterCoverClose() == FALSE)		/* カバーオープン */
	|| (CMN_CheckPaperExist() == FALSE)) {			/** 紙なし *//* Add by O.Kimoto 1998/12/18 */
		return(TRUE);
	}
	return(FALSE);
#else
	if ((CMN_CheckNoPrinterError() == FALSE)		/* プリンターエラーあり */
	||	(CMN_CheckPrinterCoverClose() == FALSE)) {	/* カバーオープン */
		return(TRUE);
	}
	return(FALSE);
#endif

}


/*************************************************************************
	module		:[ポリーング受信可能か否か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[桐のパス以外削除 1995/089/07 Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/07/15]
	author		:[村田]
*************************************************************************/
UBYTE	CMN_CheckPollingReceiveEnable(void)
{
#if 0	/* POPLAR変更 1997/03/17  By T.Yamaguchi */
//	if (CMN_CheckMemoryReceiveEnable() == FALSE) {	/* メモリ受信可能か否か */
//		return(FALSE);
//	}
//	else {
//		return(TRUE);
//	}
#endif
/*	return(CMN_CheckMemoryReceiveEnable());	*/
	return(CMN_CheckMultiLineReceiveEnable());
}

#if (0)
/*************************************************************************
	module		:[マルチコピープリント可能か否かの獲得]
	function	:[
		1.
	]
	return		:[
		1.FALSE:プリント不可能
		2.TRUE :プリント可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/07/21]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CMN_CheckMultiCopyPrintEnable(void)
{
	if (SYB_MultiCopyFile[SYB_MultiCopyReadPoint].Status == SYS_MCOPY_PRINT) { /* マルチ・コピー原稿の有無確認 */
		switch (SYB_MultiCopyFile[SYB_MultiCopyReadPoint].Cassette) {
		case SYS_1ST_CASSETTE:	/** 上段カセット選択 */
			if ((SYS_Paper1Size == SYS_NO_PAPER) || (SYS_Paper1Size == SYS_NO_CASSETTE)) {
				return(FALSE);
			}
			break;
		case SYS_2ND_CASSETTE:	/** 下段カセット選択 */
			if ((SYS_Paper2Size == SYS_NO_PAPER) || (SYS_Paper2Size == SYS_NO_CASSETTE)) {
				return(FALSE);
			}
			break;
		default:/**自動選択 */
			break;
		}
		return(TRUE);
	}
	return(FALSE);
}
#endif

/*************************************************************************
	module		:[マルチコピープリント可能か否かの獲得]
	function	:[
		1.
	]
	return		:[
		1.FALSE:プリント不可能
		2.TRUE :プリント可能
	]
	common		:[]
	condition	:[]
	comment		:[
		1.Ｓｔａｔｕｓ：１ページ目蓄積開始から蓄積終了までの間がSYS_MCOPY_STOREになる
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/07/21]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE CMN_CheckMultiCopyPrintEnable(void)
{
	UBYTE	i;
	UBYTE	print_start;
	UBYTE	write_point;
	struct SYS_MultiCopyData_t *mcopy_ptr;

/**
	if (CHK_MNT_SwCopyContinueMode()) {
		return(FALSE);
	}
	if (CMN_CheckPrinterError() == TRUE) {
		return(FALSE);
	}
**/
	if(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {
		return(FALSE);
	}

	/* --------------------------------------------------------------------
	** 何かの間違いで、MultiCopyReadPointとMultiCopyWritePointのつじつまが合わなくなった場合に、
	** WritePointが正しいとして、ReadPointを再設定するようにする。
	*/
	write_point = SYB_MultiCopyWritePoint;
	write_point ++;
	if (write_point >= SYS_MULTI_COPY_MAX) {
		write_point = 0;
	}

	for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
		if (SYB_MultiCopyFile[write_point].Status != SYS_MCOPY_EMPTY) {
			break;
		}
		write_point ++;
		if (write_point >= SYS_MULTI_COPY_MAX) {
			write_point = 0;
		}
	}
	if (i < SYS_MULTI_COPY_MAX) {
		SYB_MultiCopyReadPoint = write_point;
	}

	mcopy_ptr = &SYB_MultiCopyFile[SYB_MultiCopyReadPoint];
	print_start = FALSE;

/* #if (PRO_FBS == ENABLE) 1997/11/13  By T.Yamaguchi */
	/*---------------------------------------------------------------------
	** フライングコピー
	** ＡＤＦ、ノンソート、１ページ蓄積済で起動する
	** ステータスがメモリオーバーであっても、未プリントの原稿があることがある。
	*/
	if (mcopy_ptr->Status == SYS_MCOPY_STORE) {
		if ((mcopy_ptr->ScanType == SYS_ADF_SCAN) && (mcopy_ptr->SortType == SYS_NONE_SORT)) {
			if (mcopy_ptr->StorePage >= 1) {
				print_start = TRUE;
			}
		}
	}

	/*---------------------------------------------------------------------
	** ステータスがメモリオーバーであっても、未プリントの原稿があることがある。
	** ＡＤＦノンソートコピーで未プリント原稿がある場合はプリントを行う。
	** ＦＢＳ、ＡＤＦノンソートコピーで未プリント原稿なしの場合はメモリ消去する。
	** ＡＤＦソートコピーの場合は、SYS_MCOPY_MEMORY_OVERにはならない。
	*/
	if (mcopy_ptr->Status == SYS_MCOPY_MEMORY_OVER) {
		if ((mcopy_ptr->ScanType == SYS_ADF_SCAN) && (mcopy_ptr->SortType == SYS_NONE_SORT)
		&&  (mcopy_ptr->StorePage >= mcopy_ptr->PrintPage)) {
			print_start = TRUE;
		}
		else {
			mcopy_ptr->Status = SYS_MCOPY_EMPTY;
			MEM_ClearDoc(SYS_MEM_MULTI_COPY_FILE, SYB_MultiCopyReadPoint, MEM_IGNORE_BOX_NUMBER);
		}
	}

#if (PRO_FBS == ENABLE)
	/*---------------------------------------------------------------------
	** ＦＣＯＴ追求コピー
	** Ａ４縦、ＦＢＳ、で起動する。
	*/
	if ((mcopy_ptr->Status == SYS_MCOPY_STORE) && (mcopy_ptr->ScanType == SYS_FBS_SCAN)) {
		print_start = TRUE;
	}
#endif

	if ((print_start == TRUE) || (mcopy_ptr->Status == SYS_MCOPY_PRINT)) { /* マルチ・コピー原稿の有無確認 */
		return(CMN_CheckCassettePaper(mcopy_ptr->Cassette));
	}
	return(FALSE);
}

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[手差しマルチコピープリント可能か否かの獲得]
	function	:[
		1.
	]
	return		:[
		1.FALSE:プリント不可能
		2.TRUE :プリント可能
	]
	common		:[]
	condition	:[]
	comment		:[
		1.記録紙なしでもプリント可能状態とする。後で記録紙がセットされるとプリントを起動する
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/07/21]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE CMN_CheckManualCopyPrintEnable(void)
{
	struct SYS_MultiCopyData_t *mcopy_ptr;

	if (CMN_CheckPrinterError() == TRUE) {
		return(FALSE);
	}
	if(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {
		return(FALSE);
	}

	/*---------------------------------------------------------------------
	** フライングコピー
	** ＡＤＦ、ノンソート、１ページ蓄積済で起動する
	*/
	mcopy_ptr = &SYB_ManualCopyFile;
#if (0)
	if (mcopy_ptr->Status == SYS_MCOPY_STORE) {
		if ((mcopy_ptr->ScanType == SYS_ADF_SCAN) && (mcopy_ptr->SortType == SYS_NONE_SORT)) {
			if (mcopy_ptr->StorePage >= 1) {
				return(TRUE);
			}
		}
	}

	/*---------------------------------------------------------------------
	** ステータスがメモリオーバーであっても、未プリントの原稿があることがある。
	** ＡＤＦノンソートコピーで未プリント原稿がある場合はプリントを行う。
	** ＦＢＳ、ＡＤＦノンソートコピーで未プリント原稿なしの場合はメモリ消去する。
	** ＡＤＦソートコピーの場合は、SYS_MCOPY_MEMORY_OVERにはならない。
	** 1997/02/26 H.Yoshikawa
	*/
	if (mcopy_ptr->Status == SYS_MCOPY_MEMORY_OVER) {
		if ((mcopy_ptr->ScanType == SYS_ADF_SCAN) && (mcopy_ptr->SortType == SYS_NONE_SORT)
		&&  (mcopy_ptr->StorePage >= mcopy_ptr->PrintPage)) {
			return(TRUE);
		}
		else {
			mcopy_ptr->Status = SYS_MCOPY_EMPTY;
			MEM_ClearDoc(SYS_MEM_MANUAL_COPY_FILE, 0, MEM_IGNORE_BOX_NUMBER);
			return(FALSE);
		}
	}

	/*---------------------------------------------------------------------
	** ＦＣＯＴ追求コピー
	*/
	if ((mcopy_ptr->Status == SYS_MCOPY_STORE) && (mcopy_ptr->ScanType == SYS_FBS_SCAN)) {
		return(TRUE);
	}
#endif

	if (mcopy_ptr->Status == SYS_MCOPY_PRINT) { /* 手差しコピー原稿の有無確認 */
		return(TRUE);
	}

	return(FALSE);
}
#endif

/*************************************************************************
	module		:[プリンタ部がエラー状態か否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1.FALSE:プリントがエラー状態でプリントできない
		2.TRUE :プリントがエラー状態でないので、記録紙があればプリントできる

	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/10/23]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE CMN_CheckPrinterError(void)
{
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & (SYS_PRINTER_NO_CARTRIDGE		|
												   SYS_PRINTER_NO_INK			|
												   SYS_PRINTER_END_TONER		|
												   SYS_PRINTER_NO_DRUM))
	|| (SYS_MachineStatus[SYS_PRINTER_STATUS2] &  (SYS_PRINTER_PAPER_JAM		|
												   SYS_PRINTER_MISS_FEED_JAM	|
												   SYS_PRINTER_1ST_FEED_JAM		|
												   SYS_PRINTER_2ND_FEED_JAM		|
												   SYS_PRINTER_3RD_FEED_JAM		|
												   SYS_PRINTER_MANUAL_FEED_JAM	|
												   SYS_PRINTER_REG_JAM			|
												   SYS_PRINTER_EXIT_JAM			|
												   SYS_PRINTER_SIZE_ERROR))
	|| (SYS_MachineStatus[SYS_PRINTER_STATUS3] &  (SYS_PRINTER_FUSER_ABNORMAL	|
												   SYS_PRINTER_FAN_ABNORMAL		|
												   SYS_PRINTER_MOTOR_ABNORMAL	|
												   SYS_PRINTER_LASER_ABNORMAL	|
												   SYS_PRINTER_SERIAL_ERROR		|
												   SYS_PRINTER_RESET_ERROR		|
												   SYS_PRINTER_DRUM_ABNORMAL	|
												   SYS_PRINTER_HV_FUSE_ERROR	|
												   SYS_PRINTER_PS_FAN_ABNORMAL))
	|| (SYS_MachineStatus[SYS_COVER_STATUS] &     (SYS_COVER_PRINTER_OPEN		|
												   SYS_COVER_JAM_OPEN			|
												   SYS_COVER_CASSETTE1_OPEN		|
												   SYS_COVER_CASSETTE2_OPEN		|
												   SYS_COVER_CASSETTE3_OPEN		|
												   SYS_COVER_2JAM_OPEN			|
												   SYS_COVER_3JAM_OPEN))) {
		return(TRUE);
	}
	return(FALSE);
}

/*************************************************************************
	module		:[指定されたカセットでプリントできるか否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1.ＴＲＵＥ：プリント可能
		2.ＦＡＬＳＥ：プリント不可
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/11]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE CMN_CheckCassettePaper(UBYTE cassette)
{
#if (PRO_PRINT_TYPE == LASER)
	switch (cassette) {
	case SYS_1ST_CASSETTE:	/** 上段カセット選択 */
		if ((SYS_Paper1Size == SYS_NO_PAPER) || (SYS_Paper1Size == SYS_NO_CASSETTE)) {
			return(FALSE);
		}
		break;
	case SYS_2ND_CASSETTE:	/** 下段カセット選択 */
		if ((SYS_Paper2Size == SYS_NO_PAPER) || (SYS_Paper2Size == SYS_NO_CASSETTE)) {
			return(FALSE);
		}
		break;
	default:/**自動選択 */
		break;
	}
	return(TRUE);
#endif
#if (PRO_PRINT_TYPE == LED)
	switch (cassette) {
	case SYS_1ST_CASSETTE:	/** １段カセット選択 */
		if ((SYS_Paper1Size == SYS_NO_PAPER) || (SYS_Paper1Size == SYS_NO_CASSETTE)) {
/*			SYS_SupplyPaperInCassette |= SYS_PRINTER_NO_PAPER;*/	/* ICHOU追加 by T.Soneoka 1996/09/28 */
			return(FALSE);
		}
/*		SYS_SupplyPaperInCassette &= ~SYS_PRINTER_NO_PAPER;*/	/* ICHOU追加 by T.Soneoka 1996/09/28 */
		break;
	case SYS_2ND_CASSETTE:	/** ２段カセット選択 */
		if ((SYS_Paper2Size == SYS_NO_PAPER) || (SYS_Paper2Size == SYS_NO_CASSETTE)) {
/*			SYS_SupplyPaperInCassette |= SYS_PRINTER_NO_PAPER2;*/	/* ICHOU追加 by T.Soneoka 1996/09/28 */
			return(FALSE);
		}
/*		SYS_SupplyPaperInCassette &= ~SYS_PRINTER_NO_PAPER2;*/	/* ICHOU追加 by T.Soneoka 1996/09/28 */
		break;
	case SYS_3RD_CASSETTE:	/** ３段カセット選択 */
		if ((SYS_Paper3Size == SYS_NO_PAPER) || (SYS_Paper3Size == SYS_NO_CASSETTE)) {
/*			SYS_SupplyPaperInCassette |= SYS_PRINTER_NO_PAPER3;*/	/* ICHOU追加 by T.Soneoka 1996/09/28 */
			return(FALSE);
		}
/*		SYS_SupplyPaperInCassette &= ~SYS_PRINTER_NO_PAPER3;*/	/* ICHOU追加 by T.Soneoka 1996/09/28 */
		break;
	default:
		return(TRUE);
	}
	return(TRUE);
#endif
}

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/21 */
/*************************************************************************
	module		:[指定されたカセットでプリントできるか否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1.ＴＲＵＥ：プリント可能
		2.ＦＡＬＳＥ：プリント不可
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/11]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE CMN_CheckPcCassettePaper(UBYTE cassette)
{
#if (PRO_PRINT_TYPE == LASER)
	if (cassette == DPR_PCR_AUTO_CASSETTE) {
		if ((SYS_Paper1Size != SYS_NO_CASSETTE) && (SYS_Paper1Size != SYS_NO_PAPER)) {
			return (TRUE);
		}
		if ((SYS_Paper2Size != SYS_NO_CASSETTE) && (SYS_Paper2Size != SYS_NO_PAPER)) {
			return (TRUE);
		}
	}
	else if (cassette == DPR_PCR_MANUAL_CASSETTE) {
		if ((SYS_Paper1Size != SYS_NO_CASSETTE) && (SYS_Paper1Size != SYS_NO_PAPER)) {
			return (TRUE);
		}
	}
	else {	/* DPR_PCR_CASSETTE1 */
		if ((SYS_Paper2Size != SYS_NO_CASSETTE) && (SYS_Paper2Size != SYS_NO_PAPER)) {
			return (TRUE);
		}
	}
	return (FALSE);
#endif
#if (PRO_PRINT_TYPE == LED)
	switch (cassette) {
	case DPR_PCR_CASSETTE1:	/** １段カセット選択 */
		if ((SYS_Paper1Size == SYS_NO_PAPER) || (SYS_Paper1Size == SYS_NO_CASSETTE)) {
			return(FALSE);
		}
		break;
	case DPR_PCR_CASSETTE2:	/** ２段カセット選択 */
		if ((SYS_Paper2Size == SYS_NO_PAPER) || (SYS_Paper2Size == SYS_NO_CASSETTE)) {
			return(FALSE);
		}
		break;
	case DPR_PCR_CASSETTE3:	/** ３段カセット選択 */
		if ((SYS_Paper3Size == SYS_NO_PAPER) || (SYS_Paper3Size == SYS_NO_CASSETTE)) {
			return(FALSE);
		}
		break;
	case DPR_PCR_CASSETTE4:	/** ４段カセット選択 */
		return(FALSE);
		break;
	default:
		return(TRUE);
	}
	return(TRUE);
#endif
}
#endif

/*************************************************************************
	module		:[現在実行中のプリントを停止して、割り込みプリントを実行するか否かの獲得]
	function	:[
		1.
	]
	return		:[
		1.FALSE:割り込みプリントなし
		2.TRUE :割り込みプリントあり
	]
	common		:[]
	condition	:[]
	comment		:[
		1.Ｓｔａｔｕｓ：１ページ目蓄積開始から蓄積終了までの間がSYS_MCOPY_STOREになる
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[PRN]
	date		:[1996/08/08]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE	CMN_CheckPrinterStop(void)
{
	UBYTE print_stop;

	if (CHK_UNI_CopyPrimaryPrint()) {
		if (SYS_DocumentPrintItem == SYS_MEM_RX_FILE) {
			print_stop = CMN_WaitingPrintDocument(&SYB_MultiCopyFile[SYB_MultiCopyReadPoint]);
			if (print_stop == FALSE) {
				print_stop = CMN_WaitingPrintDocument(&SYB_ManualCopyFile);
			}
			/*-------------------------------------------------------------
			** 受信原稿プリント中にＰＣプリント指示があった場合は、ＰＣ原稿プリントを優先する
			** ICHOU 1997/07/28
			*/
#if (PRO_PC_PRINT == ENABLE)
			if ((SYB_PcRxPrint.Status == SYS_PC_RX_STORE) || (SYB_PcRxPrint.Status == SYS_PC_RX_PRINT)) {
				print_stop = TRUE;
			}
#endif
			return(print_stop);
		}
	}
	return(FALSE);
}

/*************************************************************************
	module		:[指定された、マルチコピー原稿がプリント可能か否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1.ＴＲＵＥ：  プリント可能原稿あり
		2.ＦＡＬＳＥ：プリント可能原稿なし
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[PRN]
	date		:[1997/01/23]
	author		:[吉川弘康・橘正樹]
*************************************************************************/
UBYTE	CMN_WaitingPrintDocument(struct SYS_MultiCopyData_t *mcopy_ptr)
{
	if (mcopy_ptr->Status == SYS_MCOPY_PRINT) { /* マルチ・コピー原稿の有無確認 */
		return(TRUE);
	}
	if ((mcopy_ptr->Status == SYS_MCOPY_STORE) && (mcopy_ptr->StorePage > 1) &&
		(mcopy_ptr->ScanType == SYS_ADF_SCAN)  && (mcopy_ptr->SortType == SYS_NONE_SORT)) {
		return(TRUE);
	}
	return(FALSE);
}


/*************************************************************************
	module		:[電源投入時にストップキーがおされているか]
	function	:[
		1.ラベンダーＤＲＡＭバックアップ機能のため
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[H8/300]
	language	:[H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/11/14]
	author		:[村田]
*************************************************************************/
UBYTE	CMN_CheckInitializeKeyON(void)
{
	return(0);
}

/*************************************************************************
	module		:[ＤＳ１がＯＮになっているか調べる]
	function	:[
		1.マシンステータスのＤＳ１のビットをチェックする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/11/29]
	author		:[山口]
*************************************************************************/
UBYTE	CMN_CheckDS1Status(void)
{
	if (SYS_MachineStatus[SYS_SENSOR_STATUS] & SYS_SENSOR_DS1_ON) {
		return(TRUE);
	}
	return(FALSE);
}


#if 0 /*  MAN_GetMemoryRxPrintNumber(void)と同じなので削除 */
// UWORD CMN_GetMemoryRxPrintNumber(void)
// UWORD CMN_GetMultiLineReceiveNumber(UBYTE StackNo)
/*************************************************************************
	module		:[受信原稿プリントＮｏ獲得]
	function	:[
		1.代行受信テーブルの０番目から検索
		2.１枚以上受信しているテーブルを見つける
		3.一番古い時間に受信しているテーブルＮｏを獲得する
	]
	return		:[
					0xFFFF:               代行受信原稿なし
					0～SYS_MEMORY_RX_MAX: 代行受信原稿プリントする番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/11/08]
	author		:[村田、 山口]
*************************************************************************/
UWORD CMN_GetMemoryRxPrintNumber(void)
{
	UWORD			i;
	UWORD			number;
	UDWORD			receive_time;

	i = 0;
	number = 0xFFFF;
	receive_time = 0xFFFFFFFF;

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
		if (CMN_CheckMemRxPrintStatus(i)) {	/* 受信している */

			if (receive_time == 0xFFFFFFFF) {	/** １発目 */
				receive_time = SYB_MemoryRxPrint[i].ReceiveTime;
				number = i;
			}
			else {
				/** 受信時間が同じ時は、ナンバーの若いのを優先する */
				if (receive_time > SYB_MemoryRxPrint[i].ReceiveTime) {
					receive_time = SYB_MemoryRxPrint[i].ReceiveTime;
					number = i;
				}
			}
		}
	}
	return(number);
}

/*************************************************************************
	module		:[受信原稿プリントするステータスをチェック]
	function	:[
		1.
	]
	return		:[
					1:ﾌﾟﾘﾝﾄできる
					0:ﾌﾟﾘﾝﾄなし

	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/11/08]
	author		:[村田、山口]
*************************************************************************/
UBYTE CMN_CheckMemRxPrintStatus(UWORD No)
{
	if (CHK_UNI_MemoryRxAndPrint()) {
		if ((SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_STORE)
		||	(SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_PRINT)) {

			return(1);
		}
	}
	else {
		if (SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_PRINT) {
			return(1);
		}
	}
	return(0);
}
#endif	/* 削除 */
#if 0 /* 1997/11/20  By T.Yamaguchi MAN_GetMultiLineReceiveNumberを使う */
/*************************************************************************
	module		:[マルチ回線代行受信管理テーブル獲得]
	function	:[
		1.代行受信管理テーブルの空きを見つける
		2.代行受信管理テーブルにスタックＮｏをセットに使用中にする
	]
	return		:[
					0xFFFF:   受信不可
					上記以外: 受信可能（獲得した代行受信管理テーブル番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/12/24]
	author		:[村田]
*************************************************************************/
UWORD CMN_GetMultiLineReceiveNumber(UBYTE StackNo)
{
	UWORD	i;

	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)
	&& (MEM_CountTotalEmptyPage() > 0)) {	/** 空きメモリおよび空きインデックス有り */

		for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
			if (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_EMPTY) {	/** 空きを見つける */
				SYB_MemoryRxPrint[i].StackNumber = StackNo;				/** スタックＮｏセット */
				SYB_MemoryRxPrint[i].JournalPoint = 0;					/** ジャーナルポイント初期化 */
				SYB_MemoryRxPrint[i].Status = SYS_MEMORY_RX_SETTING;	/** 空き代行受信管理テーブルをキープする */
#if (PRO_MULTI_LINE == ENABLE)	/* 1997/03/19  By T.Yamaguchi */
				SYB_OptionMemoryRxWritePoint[StackNo] = i;
#endif
				return(i);
			}
		}
	}
	return(0xFFFF);
}
#endif

/*************************************************************************
	module		:[コピー中かどうか]
	function	:[
		コピー中でスキャンとプリントが対応しているかどうかを見る
		マルチコピーならMultiCopyWritePointと～Read～を比較する
		手差しコピーなら対応しているとする
		ADF/FBSは区別しない
	]
	return		:[
		TRUE	スキャンとプリントが対応してコピー中
		FALSE	スキャンとプリントは対応していない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/17]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CMN_CheckScanFilePrinting( void )
{
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY) {
		if (SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE) {
			if (SYB_MultiCopyWritePoint == SYB_MultiCopyReadPoint) {
				return (TRUE);
			}
		}
		else if (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE) {
			return (TRUE);
		}
	}

	return (FALSE);
}

/*************************************************************************
	module		:[１～３段目カセットあり／なし]
	function	:[
		1.
	]
	return		:[
		0                    :未装着
		SYS_1ST_UNIT(1)      :カセット１装着
		SYS_2ND_UNIT(2)      :カセット１・２装着
		SYS_3RD_UNIT(3)      :カセット１・２・３装着
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/07/04]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CMN_CheckCassetteUnit(void)
{
	if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_3RD_UNIT) {
		return(3);
	}
	else if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_2ND_UNIT) {
		return(2);
	}
	else if (SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] & SYS_1ST_UNIT) {
		return(1);
	}
	return(0);
}

/*************************************************************************
	module		:[ＦＣＯＴ用ミラー待機位置移動判定]
	function	:[
	]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[Dec.11.1996]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CMN_CheckFCOT_Enable(void)
{
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) ||
	    (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_BOOK_OPEN)) {
		return(FALSE);
	}
	return(TRUE);
}
/*************************************************************************
	module		:[原稿蓄積時ＭＧ３、ＪＢＩＧ符号化可能かどうかチェックする]
	function	:[
	]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997.04.23]
	author		:[山口]
*************************************************************************/
UBYTE CMN_CheckEncodeMG3_Enable(UBYTE item)
{
	switch (item) {
	case SYS_MEM_TX_FILE:
	case SYS_MEM_POLLING_FILE:
	case SYS_MEM_DB_POLLING_FILE:
	case SYS_MEM_FIP_FILE:
	case SYS_MEM_BATCH_TX_FILE1:
	case SYS_MEM_BATCH_TX_FILE2:
	case SYS_MEM_BATCH_TX_FILE3:
	case SYS_MEM_BATCH_TX_FILE4:
	case SYS_MEM_BATCH_TX_FILE5:
	case SYS_MEM_REMOTE_TX_FILE:
	case SYS_MEM_CLASS1_TX_FILE:
	case SYS_MEM_ROTATE_FILE:
	case SYS_MEM_SUB_SECURE_FILE:
	case SYS_MEM_SUB_BULLETIN_FILE:
	case SYS_MEM_CIPHER_FILE:
	case SYS_MEM_DECIPHER_FILE:
	case SYS_MEM_TX_DECIPHER_FILE:
		return(FALSE);
	}
	return(TRUE);
}

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[通信コマンドがＦコード通信かどうかチェックする]
	function	:[
	]
	return		:[TRUE:Fｺｰﾄﾞ通信
				  FALSE:その他
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997.04.23]
	author		:[山口]
*************************************************************************/
UBYTE CMN_CheckFcodeCommand(UBYTE item)
{
	switch (item) {
	case SYS_SCANNER_SUB_ADDRESS_TX:	/* Ｆコード送信 */
	case SYS_MEMORY_SUB_ADDRESS_TX:		/* Ｆコード送信 */
	case SYS_SELECT_POLLING_RX:			/* Ｆコードポーリング受信 */
		return(TRUE);
	}
	return(FALSE);
}
#endif

/*************************************************************************
	module		:[メモリー送信の設定を調べる]
	function	:[
		1.メモリー送信のローカルステータスのセット状態を調べる
	]
	return		:[]
	common		:[SYB_LocalStatus]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/07/07]
	author		:[江口]
*************************************************************************/
UBYTE CMN_CheckMemoryTxSetting(void)
{
	if (SYB_LocalStatus[0] & SYS_MEMORY_TX_ON) {
		return(TRUE);
	}
	return(FALSE);
}

#if ( PRO_MODEM == R288F ) || (PRO_MODEM == MN195006)

/*************************************************************************
	module		:[Ｆコード機能有り／無し]
	function	:[
		1.
	]
	return		:[]
	common		:[
		Ｆコード対応
		Ｆコードは通工会　相互接続試験用です。
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[unsigned char far CMN_CheckFcodeEnable(void){}]
	date		:[1996/06/14]
	author		:[木元修]
*************************************************************************/
unsigned char far CMN_CheckFcodeEnable(void)
{
	return( (UBYTE) 0 );

}

#endif /* ( PRO_MODEM == R288F ) */

/*************************************************************************
	module		:[ＣＬ１メモリ受信可能か否か]
	function	:[
	]
	return		:[
		1.FALSE:メモリ受信不可能
		2.TRUE :メモリ受信可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0)
	keyword		:[CMN]
	date		:[1996/12/24]
	author		:[村田]
*************************************************************************/
#if (PRO_CLASS1 == ENABLE)
UBYTE	CMN_CL1CheckMemoryReceiveEnable(void)
{
/* #if (PRO_FAT_MEMORY == ENABLE)	*/

	if ((SYB_CL1_MemoryRxPrint[CL1_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_EMPTY)/** 代行受信管理テーブルに空きあり */
	&&	((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
		return(TRUE);
	}
	else {
		return(FALSE);
	}

/* #else
//		return(FALSE);
// #endif
*/
}
#endif

#if (PRO_TX_SPEED == V34 )
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
/* Ported from CLOVER\SRC\CMN_CHK.C by H.Kubo 1997/07/22 */
/*************************************************************************
	module		:[Class1実行中かどうかを判断する。]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ANSam対策
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CMN_CheckActiveClass1(void){}]
	date		:[1997/06/02]
	author		:[木元修]
*************************************************************************/
UBYTE CMN_CheckActiveClass1(void)
{
	if (((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY) == SYS_LINE_BUSY) &&
	((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM) == SYS_FAXMODEM)) {
		return((UBYTE) 1);
	}
	else {
		return((UBYTE) 0);
	}
}
#endif /* (PRO_MODEM == R288F) */
#endif /* (PRO_TX_SPEED == V34 ) */



#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
/*************************************************************************
	module		:[マルチカセットあり（ダミー関数]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＩＣＨＯＵのソースを流用するために、やむを得ずダミー関数を作ります。
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CMN_CheckMultiCasseteUnit(void){}]
	date		:[1997/07/22]
	author		:[木元修]
*************************************************************************/
UBYTE CMN_CheckMultiCasseteUnit(void)
{
	return((UBYTE)0);
}
#endif


/*************************************************************************
	module		:[メモリ送信原稿を蓄積しているか]
	function	:[
		1. メモリ送信原稿蓄積中か判断する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/08/30]
	author		:[橘正樹]
*************************************************************************/
UBYTE CMN_CheckMemoryTxDocStoring(void)
{
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
	 && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)) {
		switch (SYS_DocumentStoreItem) {
		case SYS_MEM_TX_FILE:
		case SYS_MEM_BATCH_TX_FILE1:
		case SYS_MEM_BATCH_TX_FILE2:
		case SYS_MEM_BATCH_TX_FILE3:
		case SYS_MEM_BATCH_TX_FILE4:
		case SYS_MEM_BATCH_TX_FILE5:
		case SYS_MEM_CIPHER_FILE:
			return(TRUE);
		}
		return(FALSE);
	}
	else {
		return(FALSE);
	}
}


/*************************************************************************
	module		:[ﾊﾟﾈﾙ使用中か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/08]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE CMN_CheckPanelBusy(void)
{
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PANEL_BUSY) {
		return(TRUE);
	}
	return(FALSE);
}

/*************************************************************************
	module		:[ダイヤルイン番号が登録されているか]
	function	:[
		1.ダイヤルイン番号が登録されているか判断します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/23]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_DIALIN == ENABLE)
UBYTE CMN_CheckInputDialInNumber(void)
{
	if ((SYB_Dialin.FaxNumber[0]  != '*')
	 || (SYB_Dialin.Tel1Number[0] != '*')
	 || (SYB_Dialin.Tel2Number[0] != '*')) {	/* ダイヤルイン番号が登録されている時 */
		return(TRUE);
	}
	return(FALSE);
}
#endif

/*************************************************************************
	module		:[複数宛先コマンドかどうか]
	function	:[
		1.	指定されたExecQueue番号と同じCommandFileから展開された
		.	待ち/実行中の他のExecQueueを探す
		2.	但し、指定されたExecQueueが最終宛先の場合は
		.	一宛先コマンド扱いとする
	]
	return		:[
		TRUE	複数宛先コマンド(同報/マルチポーリング)
		FALSE	一宛先コマンド、または複数宛先コマンドの最終宛先
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/10/06]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CMN_CheckBroadcastCommand(
	UWORD	exec_no)	/* ExecQueue番号 */
{
	struct SYS_ExecQueueData_t	*exec_queue;
	struct SYS_ExecQueueData_t	*work_queue;
	UWORD						number;

	exec_queue = &SYB_ExecQueue[exec_no];

	for (number = 0; number < SYS_EXEC_QUEUE_MAX; number++) {	/** 全ExecQueue検索 */
		work_queue = &SYB_ExecQueue[number];
		if ((work_queue->Number.Command == exec_queue->Number.Command)
		&&	(exec_no != number)) {		/** 同じCommandFileで違うExecQueueがある */
			if ((work_queue->Status == SYS_EXEC_WAITING)
			||	(work_queue->Status == SYS_EXEC_FORWARD_WAITING)
			||	(work_queue->Status == SYS_EXEC_EXECUTE)
			||	(work_queue->Status == SYS_EXEC_FORWARD_EXECUTE)) {
				return (TRUE);	/** 待ち/実行中Queueあり */
			}
		}
	}

	return (FALSE);	/** 同報コマンドではない */
}


/*************************************************************************
	module		:[デゥアル機能制限ありか否か]
	function	:[
		1. Ｆ１００かどうかを判断します
	]
	return		:[
			1: F100
			0: F100でない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/05]
	author		:[村田]
*************************************************************************/
UBYTE CMN_CheckF100Model(void)
{
#if (PRO_PRINT_TYPE == LASER)

	if (ROM_Revision[2] == '0') {	/* F100R */
		return(1);
	}
	if (ROM_Revision[4] == 'L') {	/* D65RL */
		return(1);
	}
	return(0);

#else
	return(0);
#endif
}

/*************************************************************************
	module		:[ノーマルモードを４秒で読取るかどうか]
	function	:[
	]
	return		:[
		０    ：４秒読取りでない（２秒）
		１    ：４秒読取り
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/08]
	author		:[村田]
*************************************************************************/
UBYTE CMN_NormalScan4Sec(void)
{
#if (PRO_PRINT_TYPE == LASER)

	if (CMN_CheckF100Model()) {
		return(1);	/* 4sec */
	}
	else {
		return(0);	/* 2sec */
	}

#else

	if (CHK_UNI_NormalScan4Sec()) {
		return(1);	/* 4sec */
	}
	else {
		return(0);	/* 2sec */
	}

#endif
}


#if (PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[スクランブル処理中か]
	function	:[
		1.SYS_MachineStatus[CIPHER_STATUS]をチェックする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/12/10]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE CMN_CheckScrambleBusy(void)
{
	if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_EXEC) {
		return(TRUE);
	}
	else if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC) {
		return(TRUE);
	}
	return(FALSE);
}
#endif


/*************************************************************************
	module		:[ＴＥＬ／ＦＡＸ、ＡＮＳ／ＦＡＸをサポートするか否か]
	function	:[
		1.
	]
	return		:[
			1: サポートする
			0: サポートしない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/19]
	author		:[村田]
*************************************************************************/
UBYTE CMN_CheckTelFaxSuport(void)
{
#if (PRO_PRINT_TYPE == LASER)
  #if defined(USA)

	if (SYB_MaintenanceSwitch[MNT_SW_I4] & 0x40) {	/* ﾒﾝﾃSW I4:6 */
		if (CMN_CheckF100Model()) {	/* F100R */
			return(1);
		}
		else {	/* F120R */
			return(0);
		}
	}
	else {
		return(0);
	}

  #else

		return(1);

  #endif

#else

  #if defined(USA)
	return(0);
  #else
	return(1);
  #endif
#endif
}

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[オプションボードが動作実行中かどうか判断する]
	function	:[
		1.
	]
	return		:[
		1.FALSE:動作実行中でない。
		2.TRUE :動作実行中である。
				通信ボードの場合は、通信中である。
				プリンタボードの場合は、プリントデータ転送中である。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/12/21]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CMN_CheckOptionBoardExecuting(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE board_number;
#endif

#if (PRO_PC_PRINT == ENABLE)
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PC_PRINTDATA_RX) {
		return (TRUE);
	}
#endif

#if (PRO_MULTI_LINE == ENABLE)
	for (board_number = 1; board_number < SYS_OPTION_BOARD_MAX; board_number++) {
		if (CHK_OptionLineBusy(board_number)) {
			return (TRUE);
		}
	}
#endif

#if (PRO_ROTATE == ENABLE)
	if (MAN_RotateIsBusy) {
		return (TRUE);
	}
#endif

	return (FALSE);
}
#endif
