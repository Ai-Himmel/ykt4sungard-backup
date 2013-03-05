/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/KOBE                                                  */
/*  ファイル名   : FCM_CHK.C                                                 */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1997/06/11 kobeより移植                                   */
/*  概  要       : アンズオプションボード用チェック関数                      */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*               : 1996/06/13 ｽｷｬﾅに原稿を挿入したまま３分以上たってからｽｷｬﾅ */
/*               :            送信するとﾗﾝﾌﾟがつかずﾍﾞﾀ黒を送信する          */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\product.h"

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#if (PRO_MULTI_LINE == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#include "\src\atlanta\define\mon_pro.h" /* added by H.Kubo 1997/10/23 */

#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysjrnl.h"
#if (PRO_PAT_JOURNAL == ENABLE)
#include "\src\atlanta\define\pat_def.h"
#endif
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\lst_def.h"
#include "\src\atlanta\define\pro_def.h"
#include "\src\atlanta\define\param.h"
#include "\src\memsw\define\mem_sw_b.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\define\syscntpl.h"
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\define\syscph.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#if (PRO_MULTI_LINE == ENABLE)
#include "\src\atlanta\ext_v\dpr_data.h"
#endif
#include "\src\atlanta\ext_v\mlt_data.h"
#include "\src\atlanta\ext_v\opt_tbl.h"

#if (PRO_PAT_JOURNAL == ENABLE)
	#include "\src\atlanta\define\pat_pro.h"
	#include "\src\atlanta\ext_v\pat_data.h"
#endif

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_tbl.h"
 #endif
#endif /* (PRO_MODEM == R288F) */


/*************************************************************************
	module		:[スキャナ送信起動処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
void FCM_ScannerTxManagement(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	/* オプションでスキャナ送信なし */
#endif
}


/*************************************************************************
	module		:[スキャナ送信ページ間処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD FCM_ScnTxBetweenPageManagement(UWORD tx_total_page, UWORD tx_sm_type, UWORD is_scn_page_start)
{

#if (PRO_MULTI_LINE == ENABLE)
	/* オプションでスキャナ送信なし */
#endif
	return(0);
}


/*************************************************************************
	module		:[スキャナクローズ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
void FCM_ScannerCloseManagement(UWORD status, UWORD result)
{

#if (PRO_MULTI_LINE == ENABLE)
	/* オプションでスキャナ送信なし */
#endif
}


/*************************************************************************
	module		:[スキャナ送信縮小処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
void FCM_SCN_DecideReducPattern(struct SYS_DocBlockData_t *doc_block)
{
#if (PRO_MULTI_LINE == ENABLE)
	/* オプションでスキャナ送信なし */
#endif
}


/*************************************************************************
	module		:[代行受信続行可能否か]
	function	:[
		1.
		ホストのメモリ残量（空きブロック、空きページがボーダーラインより上か下かを判断する。
		グレープ側で会話予約しない機種は、常に「０」を返す。
		桐＋は常に「０」を返す。
	]
	return		:[
		０：代行受信続行可能
		１：代行受信続行不可能で会話予約する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD FCM_CheckMemRxContinueForVoice(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	/* オプションで会話予約なし*/
#endif
	return(0);

#if 0
//	例（RICEの場合)
//	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) <= SYS_MEMORY_EMPTY_BLOCK) 　　　　　　　|| (MEM_CountTotalEmptyPage() <= 0)){	/*代行受信続行不可*/
//		return(1);
//	}
//	else {
//		return(0);
//	}
#endif
}


/*************************************************************************
	module		:[ホストの１ブロックのメモリサイズを獲得する]
	function	:[
		1.
	]
	return		:[
			１ブロックのサイズ（バイト）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD FCM_GetMemoryBlockSize(void)
{
	return(MEM_BLOCK_SIZE);
}


/*************************************************************************
	module		:[グレープ側でメモリ受信可能かどうかの判断]
	function	:[
		1.
		桐＋では単にメモリ受信可能かどうかだけの判断であるが、２回線仕様ではグレープ側が
		メモリ受信してもよいかどうかの判断になる。
		グレープのコンパチチェックでコールされる
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD FCM_CheckMemoryReceiveEnable(void)
{
#if (PRO_MULTI_LINE == ENABLE)
 #if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */

	if ((CMN_CheckMemoryForMemRx())/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
		return(TRUE);
	}
	else {
		return(FALSE);
	}

 #else

	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
		return(TRUE);
	}
	else {
		return(FALSE);
	}
 #endif
#else
	return(0);
#endif
}


/*************************************************************************
	module		:[原稿センサー１の状態]
	function	:[
		1.
	]
	return		:[
					0:OFF
					1:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD SYS_GetDS1_ON(void)
{
	return(SYS_MachineStatus[SYS_SENSOR_STATUS] & SYS_SENSOR_DS1_ON);
}


/*************************************************************************
	module		:[スキャナカバーーの状態]
	function	:[
		1.
	]
	return		:[
					0:OFF
					1:ON
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD SYS_GetCoverScannerOpen(void)
{
	return(SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN);
}


/*************************************************************************
	module		:[スキャナランプエラーの状態]
	function	:[
		1.
	]
	return		:[
					0:ｴﾗｰなし
					1:ｴﾗｰ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD SYS_GetScannerLampError(void)
{
	return(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_LAMP_ERROR);
}


/*************************************************************************
	module		:[代行受信管理テーブルのファイアルＮＯを獲得する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD FCM_GetMemoryRxPrintWritePoint(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
	UWORD	number;
	UWORD	i;

	number = stack_number + 1;

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
		if (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_SETTING) {
#if (PRO_LINENUMBER == TWICE_LINE)
			/* ＱＡＴ不具合
			** 拡張回線で受信ができない不具合修正
			** 拡張回線の処理が抜けていた（ "& 0x7f")
			** by O.Kimoto 1998/04/13
			*/
			if ((SYB_MemoryRxPrint[i].StackNumber & 0x7f) == (UBYTE)number) {
				return(i);
			}
#else
			if (SYB_MemoryRxPrint[i].StackNumber == (UBYTE)number) {
				return(i);
			}
#endif
		}
	}
#endif
	return(0xFFFF);
#if 0
//	OptionMemoryRxWritePoint[stack_number]を返しても良い
#endif
}



/*************************************************************************
	module		:[ジャーナルの通番の獲得]
	function	:[
		1.どの回線の通番を返すか判断する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD	FCM_GetSYS_TxTotalCount(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
	return(SYB_OptionJournalTxTotalCount[(stack_number + 1)]);
#else
	return(0);
#endif
}


/*************************************************************************
	module		:[ジャーナルの通番の獲得]
	function	:[
		1.どの回線の通番を返すか判断する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD	FCM_GetSYS_RxTotalCount(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
	return(SYB_OptionJournalRxTotalCount[(stack_number + 1)]);
#else
	return(0);
#endif
}


/*--------------------*/
/* リモード診断用関数 */
/*--------------------*/


/*************************************************************************
	module		:[リモード診断 保護領域か否か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/04/19]
	author		:[村田]
*************************************************************************/
UWORD	DIAG_JudgeProtectAddress(UWORD segment, UWORD address)
{
	/* オプションでリモート診断なし */
	return(0);
}


/*************************************************************************
	module		:[リモート診断 データリード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/04/19]
	author		:[村田]
*************************************************************************/
void	DIAG_ReadFIF_DiagNSS(UWORD segment, UWORD address, UBYTE byte_cnt, UBYTE *set_buf)
{
	/* オプションでリモート診断なし */
}


/*************************************************************************
	module		:[リモート診断 データライト]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/04/19]
	author		:[村田]
*************************************************************************/
void	DIAG_WriteFIF_DiagNSS(UWORD segment, UWORD address, UBYTE byte_cnt, UBYTE *set_data)
{
	/* オプションでリモート診断なし */
}


/*************************************************************************
	module		:[ジャンクメイル防止用ＩＤ照合]
	function	:[
		ワンタッチ、短縮に登録されたＩＤと相手先ＩＤの照合を行う
	]
	return		:[照合ＯＫ: 1  照合ＮＧ: 0]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
UWORD FCM_RxCheckOwnDialAndID(UBYTE *standard_id)	/**標準ID格納ﾎﾟｲﾝﾀｰ*/
{
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	id[SYS_ID_MAX];

	DPRD_ByteTypeCopyV53toSH((UBYTE *)standard_id, (UBYTE *)&id[0], SYS_ID_MAX);

	return((UWORD)RxCheckOwnDialAndID(&id[0]));
#endif
	/**	リターンNO	*/
	return(NO);
}

/*************************************************************************
	module		:[送信画データ縮小変換率設定]
	function	:[
		1.オプションボードよりコールされる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/09/10]
	author		:[村田]
*************************************************************************/
#define	TX_NORM_POSI	0
#define	TX_FINE_POSI	2
#define TX_SFINE_POSI	4
#define	TX_HFINE_POSI	6
#define TX_EFINE_POSI	8
#define MEM_A4_POSI		0
#define	MEM_B4_POSI		5
#define MEM_A3_POSI		10
#define	MEM_NORM_POSI	0
#define	MEM_FINE_POSI	1
#define	MEM_SFINE_POSI	2
#define	MEM_HFINE_POSI	3
#define MEM_EFINE_POSI	4

UWORD	FCM_TxPixReductionSet(	UBYTE	src_size,
								UBYTE	src_mode,
								UBYTE	dst_size,
								UBYTE	dst_mode,
								UBYTE	mode_method)
{
#if (PRO_MULTI_LINE == ENABLE)
	UWORD	table_locate_x;
	UWORD	table_locate_y;
	UWORD	enc_inp_status;
	UWORD	pix_h_reduction;
	UWORD	pix_v_reduction;

	enc_inp_status = 0;		/* ｵﾌﾟｼｮﾝでのｽｷｬﾅ送信はない */
	pix_h_reduction = 0;
	pix_v_reduction = 0;
	/*----------------------------------*/
	/*	縮小率選択テーブルＸ軸設定処理	*/
	/*----------------------------------*/
	switch( dst_mode ){						/**	送信原稿モード	*/
	case	SYS_NORMAL:
		table_locate_x = TX_NORM_POSI;
		break;
	case	SYS_FINE:
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
		table_locate_x = TX_FINE_POSI;
		break;
	case	SYS_SFINE:
		table_locate_x = TX_SFINE_POSI;
		break;
	case	SYS_HFINE:
	case	SYS_E_HFINE:
		table_locate_x = TX_HFINE_POSI;
		break;
	case	SYS_EFINE:
		table_locate_x = TX_EFINE_POSI;
		break;
	}
	/*----------------------------------*/
	/*	縮小率選択テーブルＹ軸設定処理	*/
	/*----------------------------------*/
	switch( src_size ){						/**	蓄積原稿サイズ	*/
	case	SYS_DOCUMENT_A4_SIZE:
		table_locate_y = MEM_A4_POSI;
		break;
	case	SYS_DOCUMENT_B4_SIZE:
		table_locate_y = MEM_B4_POSI;
		break;
	case	SYS_DOCUMENT_A3_SIZE:
		table_locate_y = MEM_A3_POSI;
		break;
	default:
		break;
	}

	switch( src_mode ){		/**	蓄積原稿モード	*/
	case	SYS_NORMAL:
		table_locate_y += MEM_NORM_POSI;
		break;
	case	SYS_FINE:
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
		table_locate_y += MEM_FINE_POSI;
		break;
	case	SYS_SFINE:
		table_locate_y += MEM_SFINE_POSI;
		break;
	case	SYS_HFINE:
	case	SYS_E_HFINE:
		table_locate_y += MEM_HFINE_POSI;
		break;
	case	SYS_EFINE:
		table_locate_y += MEM_EFINE_POSI;
		break;
	}

	switch( dst_size ){						/**	送信原稿サイズ	*/
	case	SYS_DOCUMENT_A4_SIZE:
		pix_h_reduction = OPT_TxReductionA4_DocTbl[table_locate_y][table_locate_x];
		pix_v_reduction = OPT_TxReductionA4_DocTbl[table_locate_y][table_locate_x+1];
		break;
	case	SYS_DOCUMENT_B4_SIZE:
		pix_h_reduction = OPT_TxReductionB4_DocTbl[table_locate_y][table_locate_x];
		pix_v_reduction = OPT_TxReductionB4_DocTbl[table_locate_y][table_locate_x+1];
		break;
	case	SYS_DOCUMENT_A3_SIZE:
		pix_h_reduction = OPT_TxReductionA3_DocTbl[table_locate_y][table_locate_x];
		pix_v_reduction = OPT_TxReductionA3_DocTbl[table_locate_y][table_locate_x+1];
		break;
	}

	DPR_RemoteDataExecBuffer[0] = enc_inp_status;
	DPR_RemoteDataExecBuffer[1] = pix_h_reduction;
	DPR_RemoteDataExecBuffer[2] = pix_v_reduction;

	return (OK);
#endif
	return(0);
}

/*************************************************************************
	module		:[符号化ページ幅設定]
	function	:[
		1.オプションボードよりコールされる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/05]
	author		:[村田]
*************************************************************************/
UWORD	FCM_GetCodecSize(UWORD size, UWORD mode)
{
#if (PRO_MULTI_LINE == ENABLE)

	UWORD	codec_size;

	/* define を変換する */
#if 0	/* 1997/11/27 */
//	if (mode == SYS_E_HFINE) {
//		mode = SYS_HFINE;
//	}
#endif
	codec_size = GetCodecSize((UBYTE)size, (UBYTE)mode);
	return(codec_size);
#endif
	return(0);
	size++;	/* for warning */
	mode++;	/* for warning */
}

/************************************************************************/
/** ジャーナル関連処理 													*/
/************************************************************************/

/*************************************************************************
	module		:[自動送信時にジャーナルをセットする]
	function	:[
		1. 通番
		2. 相手先名
		3. 通信開始時刻
		4. 部門コード
		5. 備考
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/18]
	author		:[村田]
*************************************************************************/
void MltSetPatJournalDataAtAutoFax(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	UWORD			i;
	UWORD			que_num;
	UWORD			code;
	UBYTE	command_file_item;

	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
		if ((SYB_ExecQueue[i].Status == SYS_EXEC_EXECUTE) || (SYB_ExecQueue[i].Status == SYS_EXEC_FORWARD_EXECUTE)) {
			if (SYB_ExecQueue[i].StackNumber == (UBYTE)stack_number) {
				break;
			}
		}
	}
	if (i < SYS_EXEC_QUEUE_MAX) {
		/* ここにきてあたりまえ */
		que_num = i;
	}
	else {
		/* 1997/01/18 Y.Murata
		 *
		*/
		for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
			if (SYB_ExecQueue[i].Status == SYS_EXEC_ERASED) {
				if (SYB_ExecQueue[i].StackNumber == (UBYTE)stack_number) {
					break;
				}
			}
		}
		if (i < SYS_EXEC_QUEUE_MAX) {
			que_num = i;
		}
		else {
			/* ありえない */
			_asm {
				MOV		CS:WORD PTR [0],AX	;WriteProtectError for ICE
			}
			return;
		}
	}

	if (SYB_ExecQueue[que_num].Kind == SYS_COMMAND_TRX) {
		command_file_item = SYB_CommandFile[SYB_ExecQueue[que_num].Number.Command].Option.Item;
		code = SYB_CommandFile[SYB_ExecQueue[que_num].Number.Command].DepartmentCode;
		if ( SYB_ExecQueue[que_num].ExecDial.Item == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
			SYS_OptionDirectDial
			= SYB_CommandFile[SYB_ExecQueue[que_num].Number.Command].DialNumber[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Command].FaxNumber.Direct;		/** ダイレクトダイアルセーブ */
		}
	}
	else if (SYB_ExecQueue[que_num].Kind == SYS_BATCH_TX) {
		command_file_item = SYS_BATCH_MEMORY_TX;
		code = 0xFFFF;
		if ( SYB_ExecQueue[que_num].ExecDial.Item == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
			SYS_OptionDirectDial
			= SYB_BatchTxFile[SYB_ExecQueue[que_num].Number.Batch].DialNumber[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Command].FaxNumber.Direct;		/** ダイレクトダイアルセーブ */
		}
	}
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 1997/03/06 Y.Murata */
	else {
		command_file_item = SYS_CONTINUOUS_POLLING_RX;
		code = 0xFFFF;
		if ( SYB_ExecQueue[que_num].ExecDial.Item == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
			SYS_OptionDirectDial
			= SYB_ContinuousPolling.Dial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Command].FaxNumber.Direct;		/** ダイレクトダイアルセーブ */
		}
	}
#endif

	if (command_file_item == SYS_SCANNER_TX ||
		command_file_item == SYS_MEMORY_TX ||
		command_file_item == SYS_DELAYED_SCANNER_TX ||
		command_file_item == SYS_DELAYED_MEMORY_TX ||
		command_file_item == SYS_SCANNER_SECURE_TX ||
		command_file_item == SYS_MEMORY_SECURE_TX ||
		command_file_item == SYS_SCANNER_RELAY_BROADCAST ||
		command_file_item == SYS_MEMORY_RELAY_BROADCAST ||
		command_file_item == SYS_DELAYED_BROADCAST ||
		command_file_item == SYS_RELAYED_TX ||
		command_file_item == SYS_FX_MEMORY_RELAY_TX ||			/* FX仕様 */
		command_file_item == SYS_FX_SCANNER_RELAY_TX ||			/* FX仕様 */
		command_file_item == SYS_FX_MEMORY_SECURE_TX ||			/* FX仕様 */
		command_file_item == SYS_FX_SCANNER_SECURE_TX ||		/* FX仕様 */
		command_file_item == SYS_RELAYED_TX_REPORT ||		/* MIMIJI 1995/02/15 */
		command_file_item == SYS_BATCH_MEMORY_TX) {	/** 送信 */
	
			PAT_Journal2ndWorkFile.Number = OptionJournalTxTotalCount[stack_number];
	}
	else {	/** 受信 */
			PAT_Journal2ndWorkFile.Number = OptionJournalRxTotalCount[stack_number];
	}
	PAT_Journal2ndWorkFile.Kind = command_file_item;
	PAT_Journal2ndWorkFile.StartTime = SYS_OptionModemTime[stack_number].StartTime;
	PAT_Journal2ndWorkFile.DepartmentCode = (code != 0) ? code : 0;
	MltSetCOMEXEC_LocationJournal(que_num);		/* 相手先名 */

	MLT_JournalDataToImage(NUMBER, (UBYTE)stack_number);
	MLT_JournalDataToImage(LOCATION, (UBYTE)stack_number);
	MLT_JournalDataToImage(START, (UBYTE)stack_number);
	MLT_JournalDataToImage(DCODE, (UBYTE)stack_number);
	MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
#endif	/* End of PAT_JOURANL */
#endif	/* End Of MULTI_LINE */

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[手動送信時にジャーナルをセットする]
	function	:[
		1. 通番
		2. 通信開始時刻
		3. 備考
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/18]
	author		:[村田]
*************************************************************************/
void MltSetPatJournalAtManualTx(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_Journal2ndWorkFile.Number = OptionJournalTxTotalCount[stack_number];
	PAT_Journal2ndWorkFile.StartTime = SYS_OptionModemTime[stack_number].StartTime;
	PAT_Journal2ndWorkFile.Kind = SYS_MANUAL_TRANSMIT;
	
	MLT_JournalDataToImage(NUMBER, (UBYTE)stack_number);
	MLT_JournalDataToImage(START, (UBYTE)stack_number);
	MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
#endif	/* End of PAT_JOURANL */
#endif	/* End Of MULTI_LINE */

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[手動受信時にジャーナルをセットする]
	function	:[
		1. 通番
		2. 通信開始時刻
		3. 備考
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/18]
	author		:[村田]
*************************************************************************/
void MltSetPatJournalAtManualRx(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_Journal2ndWorkFile.Number = OptionJournalRxTotalCount[stack_number];
	PAT_Journal2ndWorkFile.StartTime = SYS_OptionModemTime[stack_number].StartTime;
	PAT_Journal2ndWorkFile.Kind = SYS_MANUAL_RECEIVE;
	
	MLT_JournalDataToImage(NUMBER, (UBYTE)stack_number);
	MLT_JournalDataToImage(START, (UBYTE)stack_number);
	MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
#endif	/* End of PAT_JOURANL */
#endif	/* End Of MULTI_LINE */

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[自動受信時にジャーナルをセットする]
	function	:[
		1. 通番
		2. 通信開始時刻
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/18]
	author		:[村田]
*************************************************************************/
void MltSetPatJournalAtAutoCalled(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_Journal2ndWorkFile.Number = OptionJournalRxTotalCount[stack_number];
	PAT_Journal2ndWorkFile.StartTime = SYS_OptionModemTime[stack_number].StartTime;
				
	MLT_JournalDataToImage(NUMBER, (UBYTE)stack_number);
	MLT_JournalDataToImage(START, (UBYTE)stack_number);
#endif
#endif

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[自動受信時（ポーリング）にジャーナルをセットする]
	function	:[
		1. 通番再設定
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/18]
	author		:[村田]
*************************************************************************/
void MltSetPatJournalAtPollAutoCall(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_Journal2ndWorkFile.Number = OptionJournalTxTotalCount[stack_number];
	MLT_JournalDataToImage(NUMBER, (UBYTE)stack_number);
#endif
#endif

	stack_number++;		/* for warning */
}

/*************************************************************************
	module		:[ジャーナル用ワークバッファクリア]
	function	:[
		1. ワークバッファクリア
		2. 部門コード「００００」
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
void MltClearPatJournalWorkArea(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	/** ジャーナルのイメージ展開バッファをクリア */
	UWORD	i;
	UDWORD	*add;

	add = (UDWORD *)&PAT_Journal2ndImageBuffer[0][0];

	for (i = 0; i < 16*80/4; i++) {
		*(add++) = 0x00000000;
	}

	PAT_Journal2ndWorkFile.Number			= 0x00;
	PAT_Journal2ndWorkFile.RemoteID_TTI[0] 	= 0x00;
	PAT_Journal2ndWorkFile.Mode				= 0x00;
	PAT_Journal2ndWorkFile.StartTime		= 0x00;
	PAT_Journal2ndWorkFile.TotalTime		= 0x00;
	PAT_Journal2ndWorkFile.Page				= 0x00;
#if (PRO_DEPARTMENT == ENABLE)
	PAT_Journal2ndWorkFile.DepartmentCode	= 0x00;
#endif
	PAT_Journal2ndWorkFile.Result			= 0x00;
	PAT_Journal2ndWorkFile.Kind				= 0x00;


	PAT_Journal2ndWorkFile.DepartmentCode = 0;		/** ジャーナルの部門を「００００」でイメージバッファに展開(初期化) */
	MLT_JournalDataToImage(DCODE, (UBYTE)stack_number);
#endif
#endif

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[通信終了時にジャーナルをセットする]
	function	:[
		1. 
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/18]
	author		:[村田]
*************************************************************************/
void MltSetPatJournalAtAfter(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	UWORD	period;

	period = (UWORD)(SYS_OptionModemTime[stack_number].EndTime - SYS_OptionModemTime[stack_number].StartTime);

	/*--------------------------*/
	/* 送信用ジャーナル・データ */
	/*--------------------------*/
	if ( SYS_Opt[stack_number].FaxComTXorRX_Sign == TX_COM_MODE ) {		/** 送信 */

		if (SYS_Opt[stack_number].SYS_FaxComType != SYS_COMMAND_EXECUTE) {
	
			/* 相手先名 */
			MltSetRemoteID_ToLocJournal(stack_number);
			MLT_JournalDataToImage(LOCATION, (UBYTE)stack_number);
	
		}
		if ( SYS_Opt[stack_number].GrayModeFlag == 1 ) {
			PAT_Journal2ndWorkFile.Mode  = SYS_Opt[stack_number].FirstTxMode;			/** 通信モード */
			if (PAT_Journal2ndWorkFile.Mode == SYS_E_HFINE) {	/* 1997/02/05 */
				PAT_Journal2ndWorkFile.Mode = SYS_HFINE;
			}
		}
		else{
			PAT_Journal2ndWorkFile.Mode  = SYS_Opt[stack_number].TxMode;
			if (PAT_Journal2ndWorkFile.Mode == SYS_E_HFINE) {	/* 1997/02/05 */
				PAT_Journal2ndWorkFile.Mode = SYS_HFINE;
			}
		}

		PAT_Journal2ndWorkFile.TotalTime = period;						/** 通信時間 */
		PAT_Journal2ndWorkFile.Page      = (UBYTE)SYS_Opt[stack_number].SYS_TxTotalPage;		/** 通信ページ数 */
		PAT_Journal2ndWorkFile.Result    = SYS_Opt[stack_number].FaxComResult;						/** 交信結果 */

		if (SYS_Opt[stack_number].SYS_V34ProcedureExecutingFlag) {
			PAT_Journal2ndWorkFile.Result |= V34_MODE_SET;
		}

		if (SYS_Opt[stack_number].SYS_FaxComType == SYS_AUTO_CALLED) {
			switch (SYS_Opt[stack_number].TxMemoryFileItem) {		/** メモリ送信種別 */
				case SYS_MEM_POLLING_FILE:		/** ポーリング送信原稿 */
					PAT_Journal2ndWorkFile.Kind = SYS_POLLING_TX;
					break;

				case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング送信原稿 */
					PAT_Journal2ndWorkFile.Kind = SYS_DB_POLLING_TX;
					break;

				default:
					PAT_Journal2ndWorkFile.Kind = 0xFF;
					break;
			}
			MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
		}

		MLT_JournalDataToImage(MODE, (UBYTE)stack_number);
		MLT_JournalDataToImage(TIME, (UBYTE)stack_number);
		MLT_JournalDataToImage(PAGE, (UBYTE)stack_number);
		MLT_JournalDataToImage(RESULT, (UBYTE)stack_number);
	}
	/*--------------------------*/
	/* 受信用ジャーナル・データ */
	/*--------------------------*/
	else if ( SYS_Opt[stack_number].FaxComTXorRX_Sign == RX_COM_MODE ) {		/** 受信 */

		if (SYS_Opt[stack_number].SYS_FaxComType != SYS_COMMAND_EXECUTE) {
	
			/* 相手先名 */
			MltSetRemoteID_ToLocJournal(stack_number);
			MLT_JournalDataToImage(LOCATION, (UBYTE)stack_number);
	
		}
		PAT_Journal2ndWorkFile.Mode	   = SYS_Opt[stack_number].RxMode;							/** 通信モード */
		if (PAT_Journal2ndWorkFile.Mode == SYS_E_HFINE) {	/* 1997/02/05 */
			PAT_Journal2ndWorkFile.Mode = SYS_HFINE;
		}
		PAT_Journal2ndWorkFile.TotalTime  = period;						/** 交信時間 */
		PAT_Journal2ndWorkFile.Page	   = (UBYTE)SYS_Opt[stack_number].SYS_RxTotalPage;	/** 通信ページ数 */
		PAT_Journal2ndWorkFile.Result	   = SYS_Opt[stack_number].FaxComResult;						/** 交信結果 */

		if (SYS_Opt[stack_number].SYS_V34ProcedureExecutingFlag) {
			PAT_Journal2ndWorkFile.Result |= V34_MODE_SET;
		}

		MLT_JournalDataToImage(MODE, (UBYTE)stack_number);
		MLT_JournalDataToImage(TIME, (UBYTE)stack_number);
		MLT_JournalDataToImage(PAGE, (UBYTE)stack_number);
		MLT_JournalDataToImage(RESULT, (UBYTE)stack_number);

		if (SYS_Opt[stack_number].SYS_FaxComType == SYS_AUTO_CALLED) {	/** 自動着信 */

			switch ( SYS_Opt[stack_number].SYS_RxMemoryFileItem ) {	/** 受信原稿 */

				case SYS_MEM_SECURE_RX_FILE :		/** 親展受信原稿 */

					PAT_Journal2ndWorkFile.Kind = SYS_SECURE_RX;
					MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
					break;

				case SYS_MEM_TX_FILE		:		/** メモリ送信原稿 (中継指示受信) */

					PAT_Journal2ndWorkFile.Kind = SYS_RELAY_RX;
					MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
					break;

				case SYS_MEM_REMOTE_TX_FILE :		/** リモートＦＡＸ受信 */

					PAT_Journal2ndWorkFile.Kind = SYS_REMOTE_RX;				/** リモートＦＡＸ受信 */
					MLT_JournalDataToImage(NOTE, (UBYTE)stack_number);
					break;

				default:
					break;
			}
		}
	}
#endif	/* End of PAT_JOURANL */
#endif	/* End of MULTI_LINE */

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[ジャーナル・データの相手先名をセットする（発呼）]
	function	:[]
	commom		:[
		SYB_SpeedDial[]			: 短縮ダイアル
		SYS_2ndSpeedDial[]		: 第２短縮ダイアル
		SYB_OnetouchDial[]		: ワンタッチダイアル
		SYS_2ndOnetouchDial[]	: 第２ワンタッチダイアル
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	MltSetCOMEXEC_LocationJournal(UWORD que_num)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	switch (SYB_ExecQueue[que_num].ExecDial.Item) {	/** ダイアル種別 */

		/*================*/
		/*= 短縮ダイアル =*/
		/*================*/
		case SYS_SPEED_DIAL:		/** スピード・ダイアル */
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_SpeedDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Speed].Dial);

			if ( SYB_ExecQueue[que_num].ExecDial.ExecNumber.Speed < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 */
				if (SYB_SpeedDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Speed].Name[0] != 0x00) {	/** 相手先名が登録されている */
					CMN_StringCopyNumOrNULL(PAT_Journal2ndWorkFile.RemoteID_TTI, SYB_SpeedDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Speed].Name, 20);		/** 相手先名セット */
				}
				else if ((SYB_SpeedDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Speed].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている */
					CMN_StringCopyNumOrNULL(&PAT_Journal2ndWorkFile.RemoteID_TTI[0],
											&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
				}
			}
			break;

		/*========================*/
		/*= ワンタッチ・ダイアル =*/
		/*========================*/
		case SYS_ONETOUCH_DIAL:		/** ワンタッチ・ダイアル */
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_OnetouchDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Onetouch].Dial);

			if (SYB_OnetouchDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Onetouch].Name[0] != 0x00) {	/** 相手先名が登録されている */
				CMN_StringCopyNumOrNULL(PAT_Journal2ndWorkFile.RemoteID_TTI,SYB_OnetouchDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Onetouch].Name, 20);		/** 相手先名セット */
			}
			else if ((SYB_OnetouchDial[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Onetouch].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている */
				CMN_StringCopyNumOrNULL(&PAT_Journal2ndWorkFile.RemoteID_TTI[0],
										&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
			}
			break;

		/*================*/
		/*= 直接ダイアル =*/
		/*================*/
		case SYS_DIRECT_DIAL:		/** 直接ダイアル */
				FCM_GetDialData(&SYS_OptionDialBuffer[0], SYS_OptionDirectDial );
				CMN_StringCopyNumOrNULL(PAT_Journal2ndWorkFile.RemoteID_TTI, &SYS_OptionDialBuffer[0], 20);		/** ダイアル・データを相手先名にセット */
				break;
		default:
				break;
	}
#endif	/* End of PAT_JOURANL */
#endif	/* End of MULTI_LINE */

	que_num++;	/* for warning */
}


/*************************************************************************
	module		:[ジャーナル・データの相手先名をセットする]
	function	:[]
	commom		:[
		NonStandardID[]		: 非標準ＩＤ
		StandardID[]		: 標準ＩＤ
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void	MltSetRemoteID_ToLocJournal(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	if (SYS_Opt[stack_number].NonStandardID[0] != 0x00) {		/** 交信相手機の村田（／ＯＥＭ）ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(PAT_Journal2ndWorkFile.RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].NonStandardID[0], 20);		/** 相手先名セット */
	}
	else if (SYS_Opt[stack_number].StandardID[0] != 0x00) {	/** 交信相手機の標準ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(PAT_Journal2ndWorkFile.RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].StandardID[0], 20);		/** 相手先名セット */
	}
	else {
		/* ジャーナルに前のデータがのる 1997/04/11 Y.Murata */
		PAT_Journal2ndWorkFile.RemoteID_TTI[0] 	= 0x00;
	}
#endif
#endif

	stack_number++;		/* for warning */
}


/*************************************************************************
	module		:[ジャーナルのメンバをイメージに展開する]
	function	:[
		1. 通信タスク内でジャーナルの各メンバの内容が決定すれば
		   通信タスクはＰＡＴジャーナル用ワークバッファにデータをセットし
		   本関数をコールする。
		2. 本関数は指定されたメンバのみイメージに展開する
	]
	return		:[なし]
	common		:[

	struct SYS_JournalData	far PAT_JournalWorkFile
							ＰＡＴジャーナル用ワークバッファ(通常のSRAM)
	UBYTE far PAT_JournalImageBuffer[16][80]
							ジャーナルデータイメージ展開バッファ(PAT用SRAM)

	オフセット
		#define NO_OFFSET		(1-1)			/ 通番			/
		#define LOCA_OFFSET		(5-1)			/ 相手先名		/
		#define MODE_OFFSET		(26-1)			/ 通信モード	/
		#define START_OFFSET	(36-1)			/ 通信開始時間	/
		#define TIME_OFFSET		(49-1)			/ 通信時間		/
		#define PAGE_OFFSET		(56-1)			/ 通信ページ数	/
#if (PRO_DEPARTMENT == ENABLE)
		#define CODE_OFFSET		(61-1)			/ 部門コード	/
		#define RESULT_OFFSET	(67-1)			/ 通信結果		/
		#define NOTE_OFFSET		(74-1)			/ 通信種類(備考) /
#else
		#define CODE_OFFSET		(61-1)			/ 部門コード	/
		#define RESULT_OFFSET	(61-1)			/ 通信結果		/
		#define NOTE_OFFSET		(70-1)			/ 通信種類(備考) /
#endif
	文字数
		#define NO_CNT			3				/ 通番			/
		#deifne LOCA_CNT		20				/ 相手先名		/
		#define MODE_CNT		9				/ 通信モード	/
		#define START_CNT		12				/ 通信開始時間 /
		#define TIME_CNT		6				/ 通信時間		/
		#define PAGE_CNT		3				/ 通信ページ数	/
#if (PRO_DEPARTMENT == ENABLE)
		#define CODE_CNT		4				/ 部門コード	/
#else
		#define CODE_CNT		0				/ 部門コード	/
#endif
		#define RESULT_CNT		7				/ 通信結果		/
		#define NOTE_CNT		(11-CODE)		/ 通信種類(備考) /
	]
	condition	:[

	引き数	#define NUMBER		0		/ 通番			/
			#define LOCATION	1		/ 相手先名		/
			#define MODE		2		/ 通信モード	/
			#define START		3		/ 通信開始時間 /
			#define TIME		4		/ 通信時間		/
			#define PAGE		5		/ 通信ページ数	/
			#define CODE		6		/ 部門コード	/
			#define RESULT		7		/ 通信結果		/
			#define NOTE		8		/ 通信種類(備考) /
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[]
	date		:[]
	author		:[村田]
*************************************************************************/
void MLT_JournalDataToImage(UBYTE menber, UBYTE stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)

 #if (PRO_PANEL == KANJI)
	UBYTE string[20];
	UBYTE attribute[20];
	UBYTE work[20];
 #endif
 #if (PRO_PANEL == ANK)
	UBYTE string[21];
	UBYTE attribute[21];
	UBYTE work[21];
 #endif

	UBYTE sp;
	UBYTE i;
	UBYTE point;
	struct SYS_JournalData_t *work_file;


	if (stack_number) {
		point = 1;
		work_file = &PAT_Journal2ndWorkFile;
	}
	else {
		point = 0;
		work_file = &PAT_JournalWorkFile;
	}

 #if (PRO_PANEL == KANJI)
	for (i = 0; i < 20; i++) {
		string[i]	 = 0x00;
		attribute[i] = 0x00;
		work[i]		 = 0x00;
	}
 #endif
 #if (PRO_PANEL == ANK)
	for (i = 0; i < 20; i++) {
		string[i]	 = ' ';
		attribute[i] = ' ';
	}
	string[20]	  = 0x00;
	attribute[20] = 0x00;
	for (i = 0; i < 21; i++) {
		work[i]		 = 0x00;
	}
 #endif

	sp = 0x00;

#if (PRO_CPU == H8)
	 if (SYS_PatJournalEnableFlag == 1) {	/* ジャーナル用ＳＲＡＭがある（Ｈ８のみ）*/
#endif
		switch(menber) {	/** ジャーナルのメンバ */

			case NUMBER:	/** 通番 */

				/** 通番をアスキーに変換 */
				CMN_UnsignedIntToASC(&string[0],(UWORD)work_file->Number, NO_CNT, '0');
				/** 通番をイメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], NO_CNT, NO_OFFSET, point);
				break;

			case LOCATION:	/** 相手先名 */

				/** 文字列を作成 */
				WRD_StringCopy(&string[0], &work_file->RemoteID_TTI[0]);
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], LOCA_CNT, LOCA_OFFSET, point);
				break;

			case MODE:		/** 通信モード */

				/** 番号で示される通信ﾓｰﾄﾞを、対応する通信ﾓｰﾄﾞ名称の文字列に変換 */
				CommunicationModeName(work_file->Mode, &string[0], &attribute[0]);
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], MODE_CNT, MODE_OFFSET, point);
				break;

			case START:		/** 通信開始時間 */

				/** １９９２年１月１日を基準とした分の積算値を、日時の文字列に変換 */
				CriterionMinuteToDayTimeAsc(work_file->StartTime/60, LST_MMDDHHMM,&work[0] );
				WRD_StringCopy(&string[0], &work[0] );
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], START_CNT, START_OFFSET, point);
				break;

			case TIME:		/** 通信時間 */

				/** 秒値を、分’秒”形式文字列に変換 */
				SecondToMinuteSecondAsc(work_file->TotalTime, &work[0], ' ' );
				WRD_StringCopy(&string[0], &work[0] );
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], TIME_CNT, TIME_OFFSET, point);
				break;

			case PAGE:		/** 通信ページ数 */

				/** 通信ページをアスキーに変換 */
				CMN_UnsignedIntToASC(&string[0],(UWORD)work_file->Page, PAGE_CNT, ' ' );
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], PAGE_CNT, PAGE_OFFSET, point);
				break;

			case DCODE:		/** 部門コード */

#if (PRO_DEPARTMENT == ENABLE)
				/** コードをアスキーに変換 */
				 /* 部門管理ONで、プロテクトONの時、部門コードをマスクするためのif else文追加 By H.Hirao 1996/08/13 */
				if ( (CHK_DepartmentON() != OFF) && (CHK_SectionCheckProtect() != OFF) ) {
					string[0] = '*';
					string[1] = '*';
					string[2] = '*';
					string[3] = '*';
				}
				else {
					if (work_file->DepartmentCode != 0xffff) { /* 初期値が0xffffに変更のため */
						CMN_UnsignedIntToASC( &string[0], (UWORD)work_file->DepartmentCode, CODE_CNT, '0' );
					}
				}
					
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], CODE_CNT, CODE_OFFSET, point);
				break;
#endif
			case RESULT:	/** 通信結果 */

				if( (work_file->Result & LST_ECM) != 0 ) {		/** ＥＣＭ */
					string[0] = '*';
				}
				if( (work_file->Result & V34_MODE_SET) != 0 ) {	/* Ｖ３４交信時 */
					string[0] = '#';
				}
				if( work_file->Type == TXTYPE ) {					/** 送信の時 */
					sp = LST_JOURNAL_TX;
				}
				else {												/** 受信の時 */
					sp = LST_JOURNAL_RX;
				}

				/** 通信結果番号を通信結果名称文字列に変換 */
				CommunicationResultName( work_file->Result, LST_NAME_SHORT, sp, &string[1], &attribute[1] );

				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], RESULT_CNT, RESULT_OFFSET, point);
				break;

			case NOTE:		/** 通信種類(備考) */

				/** 通信種類番号を通信種類文字列に変換 */
				CommunicationKindName( work_file->Kind, LST_NAME_1, &string[0], &attribute[0] );
				/** イメージに展開 */
				MLT_StringToCharacterImage(&string[0], &attribute[0], NOTE_CNT, NOTE_OFFSET, point);
				break;
		}
 #if (PRO_CPU == H8)
	}	/* End of SYS_PatJournalEnableFlag == 1 */
 #endif
#endif	/* End of PAT_JOURNAL */
#endif	/* End of MULTI_LINE */


	menber++;		/* for warning */
	stack_number++;	/* for warning */
}

/*************************************************************************
	module		:[任意の文字列をイメージに展開する]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[]
	date		:[]
	author		:[村田]
*************************************************************************/
void MLT_StringToCharacterImage(
		UBYTE *string,		/* 展開する文字列の先頭アドレス */
		UBYTE *attribute,	/* 展開する文字列アトリビュートの先頭アドレス */
		UBYTE	  length,		/* 文字数 */
		UBYTE	  offset,		/* オフセット */
		UBYTE	  point)		/* */
{
#if (PRO_MULTI_LINE == ENABLE)
#if (PRO_PAT_JOURNAL == ENABLE)
	UBYTE xc;
	UBYTE *buffer;

	if (point) {
		buffer = (UBYTE *)&PAT_Journal2ndImageBuffer[0][0];
	}
	else {
		buffer = (UBYTE *)&PAT_JournalImageBuffer[0][0];
	}

	for (xc = offset; xc < (offset + length) ; xc++) {

#if (PRO_PANEL == KANJI)
		if (*string >= WORD_CHARACTER_MIN && *string <= WORD_CHARACTER_MAX) { /** 全角の場合(第1水準) */
			WordStringToCharacterImage(string, attribute, buffer, xc);
			xc++; /* x座標を半角分進める */
			string++;
			attribute++;
		}
		else { /** 半角の場合 */
#endif
			ByteStringToCharacterImage(*string, *attribute, buffer, xc);
#if (PRO_PANEL == KANJI)
		}
#endif /* KANJI */
		string++;
		attribute++;
	}
#endif	/* End of PAT_JOURANL */
#endif	/* End of MULTI_LINE */
}


/*************************************************************************
	module		:[
		クローバー側で交信する時にどのデータ信号速度(V34,V17,V29)で交信するかを獲得する。
		クローバーがとのデータ信号速度で通信していいかを獲得する。
	]
	function	:[
		1.
	]
	return		:[
		0x0001 : Ｖ３４（２８．８Ｋ）
		0X0002 : Ｖ１７（１４．４Ｋ）
		0X0004 : Ｖ２９（９．６Ｋ）
		0x0008 : Ｖ２７ｔｅｒ（４．８Ｋ）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/27]
	author		:[村田]
*************************************************************************/
UWORD FCM_GetDataSignalingRate(UWORD stack_number)
{
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	type;
	UBYTE	num;

	if (CHK_V34SiganalRateV34Mask()) {	/* UNISW D3:6 V17固定 1997/01/26 */
		return(0x000E);
	}
	else {
		num = (UBYTE)(stack_number + 1);
		type = SYS_Opt[num].SYS_FaxComType;
		if ((type == SYS_MANUAL_TX) || (type == SYS_MANUAL_RX)) {
			if (CHK_ManualFaxComV8Enable()) {
				return(0x000F);
			}
			else {
				return(0x000E);
			}
		}
		else {
			return(0x000F);
		}
	}
#endif
	return(0);
}


/*************************************************************************
	module		:[
			カントリーコード獲得
	]
	function	:[
		1.
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/28]
	author		:[村田]
*************************************************************************/
UWORD FCM_CheckCountryCode(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	UWORD	value;

	value = 0;

	#if defined(JPN)
		value = JPN_CODE;
	#endif
	#if defined(USA)
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = USA_CODE;
			break;
		case 1:
			value = USA_CODE;	/* CAN */
			break;
		case 2:
			value = AUS_CODE;
			break;
		default:
			value = USA_CODE;
			break;
		}
	#endif
	#if defined(GBR)
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = GBR_CODE;
			break;
		default:
			value = GBR_CODE;
			break;
		}
	#endif
	#if defined(DEU)
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = DEU_CODE;
			break;
		default:
			value = DEU_CODE;
			break;
		}
	#endif
	#if defined(FRA)
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = FRA_CODE;
			break;
		default:
			value = FRA_CODE;
			break;
		}
	#endif
	#if defined(AUS)
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = AUS_CODE;
			break;
		case 1:
			value = THA_CODE;
			break;
		case 2:
			value = SGP_CODE;
			break;
		default:
			value = AUS_CODE;
			break;
		}
	#endif
	#if defined(TWN)
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = TWN_CODE;
			break;
		case 1:					/* by M.H  10/Feb/98 */
			value = SGP_CODE;	/* SGP/HKG/MYS */
			break;
		case 2:					/* by M.H  10/Feb/98 */
			value = THA_CODE;	/* THA */
			break;
		default:
			value = TWN_CODE;
			break;
		}
	#endif
	#if defined(EC1)	/* by M.H  10/Apr/98 */
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = BEL_CODE;
			break;
		case 1:
			value = NLD_CODE;	
			break;
		case 2:
			value = ITA_CODE;	
			break;
		case 3:
			value = ESP_CODE;	
			break;
		case 4:
			value = NOR_CODE;	
			break;
		case 5:
			value = SWE_CODE;	
			break;
		case 6:
			value = FIN_CODE;	
			break;
		case 7:
			value = DNK_CODE;	
			break;
		default:
			value = BEL_CODE;
			break;
		}
	#endif
	#if defined(EUR)	/* 欧州仕様追加(CTR21) by M.H 1999/09/15 */
		switch (SYB_MachineParameter[COUNTRY_CODE]) {
		case 0:
			value = EUR_CTR_33_CODE;	/* GBR(Euro一般) */
			break;
		case 1:
			value = DEU_CTR_CODE;		/* DEU(CTR) */
			break;
		case 2:
			value = EUR_CTR_33_CODE;	/* FRA */
			break;
		case 3:
			value = EUR_CTR_40_CODE;	/* ITA */
			break;
		case 4:
			value = EUR_CTR_33_CODE;	/* ESP */
			break;
		case 5:
			value = EUR_CTR_33_CODE;	/* PRT */
			break;
		case 6:
			value = EUR_CTR_33_CODE;	/* XXX */
			break;
		case 7:
			value = EUR_CTR_33_CODE;	/* XXX */
			break;
		default:
			value = EUR_CTR_33_CODE;
			break;
		}
	#endif

	return(value);
#endif
	return(0);
}


/*************************************************************************
	module		:[メモリライトオープン（マルチ回線対応）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		実質この関数を使う意味はありません。親展受信ボックスの排他処理は、コンパチチェックでやってます。 1998/05/08
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/01/10]
	author		:[村田]
*************************************************************************/
UWORD FCM_MEM_WriteOpen(struct MEM_StoreData_t *StoreP, struct MEM_ExecData_t *ExecP)
{
	UWORD	mem_ret;
	UWORD	result;

	mem_ret = 0;
	if (StoreP->Item == SYS_MEM_SECURE_RX_FILE) {
		mem_ret = MEM_CheckConflictIndexNo(StoreP);
		if (mem_ret == MEM_NO_INDEX) {	/* 競合してない */

			result = MEM_WriteOpen(StoreP, ExecP);
		}
		else {
			result = MEM_INDEX_CONFLICT;
		}
	}
	else {
		result = MEM_WriteOpen(StoreP, ExecP);
	}
	return(result);
	return(0);
}

/*************************************************************************
	module		:[Ｖ８属性のセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/12/01]
	author		:[村田]
*************************************************************************/
void V8CapableAttributeSet(void)
{
	if (PartnerV8Capable != 0xFF) {	/* 条件追加 1996/08/03 Y.M */
		if (SYS_CurrentExecutingCommand->Option & SYS_V34_STUP_RECOVER) {	/* 1996/09/05 Y.Murata */
			/* Nothing */
		}
		else {
			if (PartnerV8Capable == 1) {
				if (SYS_CurrentExecutingCommand->ExecDial.Item == SYS_SPEED_DIAL) {		/** 短縮ダイアル */
					SYB_SpeedDial[SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed].Attribute4 |= SPEED_HANDSHAKE_V8;
				}
				else if (SYS_CurrentExecutingCommand->ExecDial.Item == SYS_ONETOUCH_DIAL) {		/** ワンタッチ・ダイアル */
					SYB_OnetouchDial[SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch].Attribute4 |= SPEED_HANDSHAKE_V8;
				}
			}
			else {
				if (SYS_CurrentExecutingCommand->ExecDial.Item == SYS_SPEED_DIAL) {		/** 短縮ダイアル */
					SYB_SpeedDial[SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed].Attribute4 &= ~SPEED_HANDSHAKE_V8;
				}
				else if (SYS_CurrentExecutingCommand->ExecDial.Item == SYS_ONETOUCH_DIAL) {		/** ワンタッチ・ダイアル */
					SYB_OnetouchDial[SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch].Attribute4 &= ~SPEED_HANDSHAKE_V8;
				}
			}
		}
	}
}


/*************************************************************************
	module		:[リモート診断可能か否か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/01/21]
	author		:[村田]
*************************************************************************/
UWORD FCM_CheckRemotoDiag(UWORD number)
{
#if (PRO_MULTI_LINE == ENABLE)
	UWORD	num;
	UWORD	i;

	num = number + 1;

	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) {
		return(0);
	}
	else {
		for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {
			if (CHK_OptionLineBusy((UBYTE)i)) {
				if (num == i) {
				}
				else {
					return(0);
				}
			}
		}
	}
	return(1);
#endif
	return(0);
}


/*************************************************************************
	module		:[ボリュームの大きさ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/01/27]
	author		:[村田]
*************************************************************************/
UWORD FCM_GetMonitorSpeakerOutLevel(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	return((UWORD)SYB_MonitorSpeakerOutLevel);
#endif
	return(0);
}


/*************************************************************************
	module		:[新ダイレクトメール防止モード編]
	function	:[
		1.
	]
	return		:[
			0x0000:OK
			0x0001:TSI 受信せず
			0x0002:標準IDなし
			0x0003:TSIと自機NOの照合NG
			0xffff:ﾀﾞｲﾚｸﾄﾒｰﾙ防止設定でない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/09/14]
	author		:[村田]
*************************************************************************/
UWORD FCM_CheckJunkFax(UWORD frame_name, UBYTE *standard_id)
{
	UBYTE	id[SYS_ID_MAX];
	UBYTE	mode;

	DPRD_ByteTypeCopyV53toSH((UBYTE *)standard_id, (UBYTE *)&id[0], SYS_ID_MAX);

	return(FCM_CompJunkFax(frame_name, &id[0]));

}

/*************************************************************************
	module		:[新ダイレクトメール防止モード編]
	function	:[
		1.
	]
	return		:[
			0x0000:OK
			0x0001:TSI 受信せず
			0x0002:標準IDなし
			0x0003:TSIと自機NOの照合NG
			0xffff:ﾀﾞｲﾚｸﾄﾒｰﾙ防止設定でない
	]
	common		:[１回線目と２回線目で共通に使える様に変更作成]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1997/10/20]
	author		:[山口]
*************************************************************************/
UWORD FCM_CompJunkFax(UWORD frame_name, UBYTE *std_id)
{
	UBYTE	junk_mode;
	UBYTE	uni_swc2_2;
	
	junk_mode = CHK_BlockJunkFaxMode();
	uni_swc2_2 = CHK_UNI_JunkMode2_Rx_No_TSI();
	
	if (junk_mode == BLOCK_JUNK_FAX_OFF) {
		return(0xFFFF);
	}
	if (frame_name == NO) {
		if ((junk_mode == BLOCK_JUNK_FAX_MODE2) && (!uni_swc2_2)) {
			return(0x0000);
		}
		else {
			return(0x0001);
		}
	}
	else if (std_id == NULL) {
		if ((junk_mode == BLOCK_JUNK_FAX_MODE2) && (!uni_swc2_2)) {
			return(0x0000);
		}
		else {
			return(0x0002);
		}
	}

	if (junk_mode != (UBYTE)BLOCK_JUNK_FAX_MODE1) {
		if (RxCheckJunkDialAndID(std_id) == NO) {
			return(0x0003);		/* 受信しない */
		}
	}

	if (junk_mode != (UBYTE)BLOCK_JUNK_FAX_MODE2) {
		if (RxCheckOwnDialAndID(std_id) == NO) {
			return(0x0003);
		}
	}

	/**	リターンYES	*/
	return(0x0000);
	
}

/*************************************************************************
	module		:[空き暗号化ＢＯＸ獲得]
	function	:[
		1.
	]
	return		:[
			0xFFFF:空きなし
			0xFFFF以外:空きＢＯＸ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/10/08]
	author		:[村田]
*************************************************************************/
UWORD FCM_GetCipherBoxNo(UWORD stack_number)
{
#if (PRO_CIPHER == ENABLE)
	UBYTE i;

	/* 空、暗号化受信番号の獲得 */
	CMN_DisableInterrupt();
	for (i = 0; i < SYS_CIPHERBOX_MAX; i++) {
		if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_NO) {
			break;
		}
	}
	if (i == SYS_CIPHERBOX_MAX) {	/* 全てのBOXが使用中、受信できない */
		CMN_EnableInterrupt();
		return(0xFFFF);
	}

	/* バックアップのため */
	SYB_CipherBox[i].Status = SYS_CIPHERBOX_RECEIVING;
	CMN_EnableInterrupt();

	return((UWORD)i);
#else
	return(0xFFFF);
#endif
}


/*************************************************************************
	module		:[暗号化ＢＯＸセット]
	function	:[
		1.
	]
	return		:[
			0xFFFF:空きなし
			0xFFFF以外:空きＢＯＸ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/10/08]
	author		:[村田]
*************************************************************************/
void FCM_SendBackCipherStatus(UWORD status, UWORD number, UWORD data, UWORD stack_number)
{
	UWORD box_status;

	box_status = 0xFFFF;

	switch (status) {
	case SYS_OPT_CIPHER_OK:
		if (number < SYS_CIPHERBOX_MAX) {
			CMN_DisableInterrupt();
			SYB_CipherBox[number].MessageStatus = SYS_CIPHERBOX_RECEIVE;
			SYB_CipherBox[number].Status  = SYS_CIPHERBOX_RECEIVE;
			CMN_EnableInterrupt();
		}
		else {
			SaveReturnAddressAndJumpBegin();	/* ここに来るのはおかしい */
		}
		break;
	case SYS_OPT_CIPHER_NG:
		if (number < SYS_CIPHERBOX_MAX) {
			CMN_DisableInterrupt();
			SYB_CipherBox[number].Status  = SYS_CIPHERBOX_NO;
			CMN_EnableInterrupt();
		}
		else {
			SaveReturnAddressAndJumpBegin();	/* ここに来るのはおかしい */
		}
		break;
	case SYS_OPT_CIPHER_NOTHING:
		SaveReturnAddressAndJumpBegin();	/* ここに来るのはおかしい */
		break;
	}

}


/************************************************************************
	module		:[Ｆコード受信後処理]
	function	:[
		1. Ｆコード受信後の処理を行う
		2. 消去時間を設定する
		3. 受信中のデータステータスを戻す
	]
	return		:[]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1997/10/13]
	author		:[山口]
************************************************************************/
void FCM_SetRxSubAddressBox(UWORD rx_file_item, UWORD file_no, UWORD rx_total_page, UWORD box_number)
{
	UBYTE file_item;
	UBYTE rx_file_box_number;

	file_item = (UBYTE)rx_file_item;
	rx_file_box_number = (UBYTE)box_number;
	
	if (rx_total_page >= 1) {				/** サブアドレス受信処理（１枚以上受信） */
		/*----------------------------------------------------------------*/
		/** サブアドレス受信後の受信ﾒｯｾｰｼﾞ印字用ﾃﾞｰﾀｾｯﾄ					  */
		/** サブアドレス受信時は１枚でも受信していれば２枚目がｴﾗｰでもﾒｯｾｰｼﾞを印字 */
		/*----------------------------------------------------------------*/
		if (!CHK_UNI_Fcode_RxMessageOff()) {	/* UNI_SW_H3-2 */
			SYB_SubAddressBoxTable[rx_file_box_number - 1].MessageStatus = SYS_SUB_ADDRESS_BOX_RCV_MSG;	/** 受信通知メッセージ */
		}
		if (SYB_SubAddressBoxTable[rx_file_box_number - 1].HoldTime == 0) {
			SYB_SubAddressBoxTable[rx_file_box_number - 1].ErasedTime = (UDWORD)0xffffffff;
		}
		else {
			SYB_SubAddressBoxTable[rx_file_box_number - 1].ErasedTime	  = ( SYB_CurrentTime ) +
				( (UDWORD)SYB_SubAddressBoxTable[rx_file_box_number - 1].HoldTime * 24L * 60L * 60L );	/** 消去時間 現在時間（秒）＋ 保持期間（日）× ２４時間×６０分×６０秒 */
		}
		/* プリント中の場合ありなので条件を入れる 1997/05/14  By T.Yamaguchi */
		CMN_DisableInterrupt();
		if (SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  == SYS_SUB_ADDRESS_BOX_PRT_RX) {	/** プリント中 */
			SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  = SYS_SUB_ADDRESS_BOX_PRINTING;		/** 蓄積原稿プリント中 */
		}
		else {
			SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  = SYS_SUB_ADDRESS_BOX_RECEIVE;		/** 受信原稿有り */
		}
		CMN_EnableInterrupt();
		/* ここではまだ消さない 受信メッセージプリント後クリアする */
		/* SYB_SubAddressBoxTable[rx_file_box_number - 1].RxStoringNo = 0;	 受信中ファイル番号リセット */
		SYB_SubAddressBoxTable[rx_file_box_number - 1].StoredDocBit |= (UDWORD)(1 << (file_no - 1));	/* 受信蓄積ファイル番号セット */
		if (file_item == SYS_MEM_SUB_BULLETIN_FILE) {
			SYB_SelectPollDocumentStatus = 1;
		}
	}
	else {
		/*------------------------------------------------------------------*/
		/* サブアドレス受信失敗時のクリア									*/
		/* 受信で１枚も受信していなくても過去にサブアドレス受信の原稿がある時は */
		/* ステータスを有りにセットする										*/
		/*------------------------------------------------------------------*/
		if(rx_file_box_number != 0) {
			/* ﾎﾞｯｸｽなし、ﾊﾟｽｺｰﾄﾞｴﾗｰ時は、以下の処理を行わない。*/
			if (MEM_CountTotalBoxPage((UBYTE)file_item, (UBYTE)rx_file_box_number) == MEM_NO_INDEX) {	/** 以前にも受信・蓄積原稿がない */
				CMN_DisableInterrupt();
				SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  = SYS_SUB_ADDRESS_BOX_NO_SET;		/** 親展受信原稿無し */
				SYB_SubAddressBoxTable[rx_file_box_number - 1].RxStoringNo = 0;	/* 受信中ファイル番号リセット */
				CMN_EnableInterrupt();
			}
			else {	/** 以前に受信・蓄積をしている */
				CMN_DisableInterrupt();
				if (SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  == SYS_SUB_ADDRESS_BOX_PRT_RX) {	/** プリント中 */
					SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  = SYS_SUB_ADDRESS_BOX_PRINTING;		/** 蓄積原稿プリント中 */
				}
				else {	/* 	SYS_SUB_ADDRESS_BOX_RECEIVING */
					SYB_SubAddressBoxTable[rx_file_box_number - 1].DataStatus  = SYS_SUB_ADDRESS_BOX_STORED;	/** 親展受信原稿有り */
				}
				CMN_EnableInterrupt();
			}
		}
	}
}

/************************************************************************
	module		:[Ｆコード送信後処理]
	function	:[
		1. Ｆコードポーリング送信後の処理を行う
		2. 原稿消去設定なら原稿を消去する
		3. 送信中のデータステータスを元に戻す
	]
	return		:[]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1997/10/13]
	author		:[山口]
************************************************************************/
void FCM_SetTxSubAddressBox(UWORD tx_file_item, UWORD box_number, UWORD com_result)
{
	UBYTE file_item;
	UBYTE tx_box_number;

	file_item = (UBYTE)tx_file_item;
	tx_box_number = (UBYTE)(box_number - 1);

	/* 
	** ボックス番号が登録されていない時は、ｽﾃｰﾀｽをｾｯﾄしていないので何もしない
	*/
	if (box_number == 0) {
		return;
	}
	
	if ( ((com_result & 0x0C00) == NO_ERROR)
	  && (file_item == SYS_MEM_SUB_BULLETIN_FILE)) {
		/* 送信原稿消去設定の場合は本来コンパチエラーになるが送信中に設定が変更された時の処理 */
		/* プリント中に送信する時に原稿消去設定にかえられた場合は原稿消去しない 1997/05/14  By T.Yamaguchi */
		CMN_DisableInterrupt();
		if (SYB_SubAddressBoxTable[tx_box_number].DataStatus  == SYS_SUB_ADDRESS_BOX_PRT_TX) {	/** プリント中 */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus  = SYS_SUB_ADDRESS_BOX_PRINTING;		/** 蓄積原稿プリント中 */
		}
		/* 蓄積中に送信する時に原稿消去設定にかえられた場合は原稿消去しない 1997/05/14  By T.Yamaguchi */
		else if (SYB_SubAddressBoxTable[tx_box_number].DataStatus  == SYS_SUB_ADDRESS_BOX_STR_TX) {	/** 蓄積中 */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus  = SYS_SUB_ADDRESS_BOX_STORING;
		}
		else if (SYB_SubAddressBoxTable[tx_box_number].DataStatus == SYS_SUB_ADDRESS_BOX_TXING) {	/* 送信中をセット */
			if ((SYB_SubAddressBoxTable[tx_box_number].Option & SUB_ADDRESS_OPTION_ERASE) == SUB_ADDRESS_OPTION_ERASE) {	/* 送信時原稿消去 */
				CMN_EnableInterrupt();
				/* 
				** Fｺｰﾄﾞﾎﾟｰﾘﾝｸﾞ送信後の原稿消去で消去するべきBOXの原稿が消去されない不具合
				** 消去するBOXの引数が違っていたのを修正 1998/10/28  By T.Yamaguchi
				** MEM_ClearDoc(SYS_MEM_SUB_BULLETIN_FILE, MEM_ALL_NO, tx_box_number); /@@ ポーリング原稿消去 @/
				*/
				MEM_ClearDoc(SYS_MEM_SUB_BULLETIN_FILE, MEM_ALL_NO, (UBYTE)box_number); /** ポーリング原稿消去 */
				CMN_DisableInterrupt();
				SYB_SubAddressBoxTable[tx_box_number].StoredDocBit = 0;
				SYB_SubAddressBoxTable[tx_box_number].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
				SYB_SubAddressBoxTable[tx_box_number].MessageStatus = 0;
				CMN_EnableInterrupt();
				if (MEM_CountItemTotalPage(SYS_MEM_SUB_BULLETIN_FILE) == MEM_NO_INDEX) {
					SYB_SelectPollDocumentStatus = 0; /** 選択ポーリング無しセット */
				}
			}
			else {
				SYB_SubAddressBoxTable[tx_box_number].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
			}
		}
		CMN_EnableInterrupt();
	}
	else if ( ((com_result & 0x0C00) == NO_ERROR)
		  &&  (file_item == SYS_MEM_SUB_SECURE_FILE)
		  &&  (CHK_UNI_FcodeSecureDocPollTx()) ) {
		/* 送信原稿消去設定の場合は本来コンパチエラーになるが送信中に設定が変更された時の処理 */
		/* プリント中に送信する時に原稿消去設定にかえられた場合は原稿消去しない 1997/05/14  By T.Yamaguchi */
		CMN_DisableInterrupt();
		if (SYB_SubAddressBoxTable[tx_box_number].DataStatus  == SYS_SUB_ADDRESS_BOX_PRT_TX) {	/** プリント中 */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus  = SYS_SUB_ADDRESS_BOX_PRINTING;		/** 蓄積原稿プリント中 */
		}
		/* 蓄積中に送信する時に原稿消去設定にかえられた場合は原稿消去しない 1997/05/14  By T.Yamaguchi */
		else if (SYB_SubAddressBoxTable[tx_box_number].DataStatus  == SYS_SUB_ADDRESS_BOX_STR_TX) {	/** 蓄積中 */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus  = SYS_SUB_ADDRESS_BOX_STORING;
		}
		else if (SYB_SubAddressBoxTable[tx_box_number].DataStatus == SYS_SUB_ADDRESS_BOX_TXING) {	/* 送信中をセット */
			if ((SYB_SubAddressBoxTable[tx_box_number].Option & SUB_ADDRESS_OPTION_ERASE) == SUB_ADDRESS_OPTION_ERASE) {	/* 送信時原稿消去 */
				CMN_EnableInterrupt();
				/* MEM_ClearDoc(SYS_MEM_SUB_SECURE_FILE, MEM_ALL_NO, tx_box_number); /@@ ポーリング原稿消去 */
				MEM_ClearDoc(SYS_MEM_SUB_BULLETIN_FILE, MEM_ALL_NO, (UBYTE)box_number); /** ポーリング原稿消去 */
				CMN_DisableInterrupt();
				SYB_SubAddressBoxTable[tx_box_number].StoredDocBit = 0;
				SYB_SubAddressBoxTable[tx_box_number].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
				SYB_SubAddressBoxTable[tx_box_number].MessageStatus = 0;
			}
			else {
				SYB_SubAddressBoxTable[tx_box_number].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVE;
			}
		}
		CMN_EnableInterrupt();
	}
	/* Ｆコードポーリング送信エラー時は、ｽﾃｰﾀｽを戻す */
	else if ( ((com_result & 0x0C00) == TRANSMITERROR)
		  &&  ((file_item == SYS_MEM_SUB_BULLETIN_FILE)
		   ||  ((file_item == SYS_MEM_SUB_SECURE_FILE)
		   	&&  (CHK_UNI_FcodeSecureDocPollTx())) ) ) {
		CMN_DisableInterrupt();
		if (SYB_SubAddressBoxTable[tx_box_number].DataStatus  == SYS_SUB_ADDRESS_BOX_PRT_TX) {	/** プリント中 */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus  = SYS_SUB_ADDRESS_BOX_PRINTING;		/** 蓄積原稿プリント中 */
		}
		else if (SYB_SubAddressBoxTable[tx_box_number].DataStatus  == SYS_SUB_ADDRESS_BOX_STR_TX) {	/** 蓄積中 */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus  = SYS_SUB_ADDRESS_BOX_STORING;
		}
		else if (SYB_SubAddressBoxTable[tx_box_number].DataStatus == SYS_SUB_ADDRESS_BOX_TXING) {	/* 送信中をセット */
			SYB_SubAddressBoxTable[tx_box_number].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVE;
		}
		CMN_EnableInterrupt();
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
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[]
	date		:[1997/10/20]
	author		:[村田]
*************************************************************************/
UWORD FCM_CheckMailBoxStatusSet(UWORD mail_box_no, UWORD type, UWORD stack_number)
{
	UWORD status;

	if (type == 1) {
		CMN_DisableInterrupt();
		status = (UWORD)SYB_MailBox[mail_box_no].Status;
		switch (status) {
		case SYS_MAILBOX_NO_SET:
		case SYS_MAILBOX_RECEIVING:
		case SYS_MAILBOX_RCV_TO_RECEVING:
			break;
		case SYS_MAILBOX_SET:
			SYB_MailBox[mail_box_no].Status = SYS_MAILBOX_RECEIVING;
			break;
		case SYS_MAILBOX_RECEIVE:
			SYB_MailBox[mail_box_no].Status = SYS_MAILBOX_RCV_TO_RECEVING;
			break;
		default:
			status = 0xFFFF;
			break;
		}
		SYS_Opt[stack_number].SYS_RxMemoryFileItem = SYS_MEM_SECURE_RX_FILE;
		CMN_EnableInterrupt();
		return(status);
	}
	else {
		SYB_MailBox[mail_box_no].MessageStatus = SYS_MAILBOX_MSG_EMPTY;	/** 親展受信通知メッセージ出力しない */
		if (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,mail_box_no, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) {	/** 以前にも親展受信原稿がない */
			SYB_MailBox[mail_box_no].Status	  = SYS_MAILBOX_SET;		/** 親展受信原稿無し */
		}
		else {	/** 以前に親展受信をしている */
			SYB_MailBox[mail_box_no].Status	  = SYS_MAILBOX_RECEIVE;	/** 親展受信原稿有り */
		}
		return(0xFFFE);
	}
}

/*************************************************************************
	module		:[BCDのﾊﾞｯﾌｧの下４桁の有効数字をBCDで返す]
	function	:[
		1.終端コードを見つけて最終桁を獲得する
		2.最終桁から有効数字を４桁抜き出しで返す
		3.４桁に満たない場合は0xFFFFが入っている
		4.数字以外の文字を合わせて４桁以上のときで数字が３桁以下のときは
		  0xF???が入る
	]
	return		:[
		 ３桁以下の時:0xFFFF
		 
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/21]
	author		:[山口哲治]
*************************************************************************/
UWORD	PickOutLastFourFigure(UBYTE *id_buf, UBYTE count)
{
	UBYTE i;
	UBYTE figure;	/* 有効桁数（終端コードまでの桁数) */
	UBYTE bcd_buffer[4];
	UBYTE work;
	UBYTE even;		/* 読み出し位置が奇数位置か偶数位置かを保持*/
	UWORD result;
	
	result = 0xFFFF;
	figure = 0;

	for (i = 0; i < 4; i++) {
		bcd_buffer[i] = 0xFF;
 	}

	/* 最終桁を見つける */
	for (i = 0; i < count; i++) {
		if ((*(id_buf + i) & 0xF0) == 0xF0) {
			break;
		}
		figure++;
		if ((*(id_buf + i) & 0x0F) == 0x0F) {
			break;
		}
		figure++;
	}
	
	if (figure <= 3) {	/* ３桁未満 */
		return(0xFFFF);
	} 

	count = figure / 2;
	even = figure % 2;
	i = 0;

	if (even == 1) {	/* 奇数桁の場合 */
		if ((work = ( ( (*(id_buf + count)) >> 4) & 0x0F) ) <= 0x09) {
			bcd_buffer[i] = work;
			i++;
		}
	}
	count--;
	
	while(1) { /* 偶数桁の場合 */
		if (i == 4) {	/* ４桁見つけたとき */
			break;
		}
		if ((work = (*(id_buf + count) & 0x0F)) <= 0x09) {
			bcd_buffer[i] = work;
			i++;
		}
		if (i == 4) {	/* ４桁見つけたとき */
			break;
		}
		if ((work = ((*(id_buf + count) >> 4) & 0x0F)) <= 0x09) {
			bcd_buffer[i] = work;
			i++;
		}
		if (count == 0) {
			break;	/* 最終桁までﾁｪｯｸ終了 */
		}
		count--;
	}

	if (i <= 3) {	/* 有効数字３桁未満 */
		return(0xFFFF);
	}
	result = (UWORD)(((UWORD)(bcd_buffer[3] & 0x0F) << 12) + ((UWORD)(bcd_buffer[2] & 0x0F) << 8) + ((UWORD)(bcd_buffer[1] & 0x0F) << 4) + (UWORD)(bcd_buffer[0] & 0x0F));

	return(result);
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1999/10/22]
	author		:[山口哲治]
*************************************************************************/
void SetJunkOwnDial(void)
{
	UBYTE i;
	
	for (i = 0; i < SYS_ONETOUCH_MAX; i++)	{/**	ワンタッチダイヤルの個数回	*/
		SYB_OnetouchJunkDial[i] = PickOutLastFourFigure(&SYB_OnetouchDial[i].Dial[0], 40);
	}
	for (i = 0 ; i < SYS_SPEED_DIAL_MAX; i++)  {	/**	短縮ダイヤルの個数回	*/
		SYB_SpeedJunkDial[i] = PickOutLastFourFigure(&SYB_SpeedDial[i].Dial[0], 40);
	}
}


/*************************************************************************
	module		:[キャラクタジャーナル記載用データセット CHAR_JOURNAL]
	function	:[
		1.DPRD_StoreExecQueue()よりコールされる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[DPR]
	date		:[1998/02/03]
	author		:[村田]
*************************************************************************/
void FCM_SetJournalQueueOptionLine(UWORD number, UWORD num)	/* 第一引数:キュー番号、 第二引数:回線(ﾎﾞｰﾄﾞ)番号 */
{
	UWORD	com_num;
	UWORD	bat_num;
	
	com_num = 0;
	bat_num = 0;

	if (SYB_ExecQueue[number].Kind == SYS_COMMAND_TRX) {
		com_num = SYB_ExecQueue[number].Number.Command;
		SYS_Opt[num].CommandFileOptionItem = SYB_CommandFile[com_num].Option.Item;
		SYS_Opt2[num].CommandDepartmentCode = SYB_CommandFile[com_num].DepartmentCode;
	}
	else if (SYB_ExecQueue[number].Kind == SYS_BATCH_TX) {
		bat_num = SYB_ExecQueue[number].Number.Batch;
	}
	SYS_Opt2[num].QueueKind = SYB_ExecQueue[number].Kind;
	SYS_Opt2[num].QueueDialItem = SYB_ExecQueue[number].ExecDial.Item;
	switch (SYS_Opt2[num].QueueDialItem) {
	case SYS_ONETOUCH_DIAL:
		SYS_Opt2[num].QueueDialOffset = (UWORD)SYB_ExecQueue[number].ExecDial.ExecNumber.Onetouch;
		break;
	case SYS_SPEED_DIAL:
		SYS_Opt2[num].QueueDialOffset = (UWORD)SYB_ExecQueue[number].ExecDial.ExecNumber.Speed;
		break;
	case SYS_DIRECT_DIAL:
		if (SYS_Opt2[num].QueueKind == SYS_COMMAND_TRX) {
			CMN_StringCopyNum(&SYS_Opt2[num].CommandDirectDial[0], &SYB_CommandFile[com_num].DialNumber.Direct[SYB_ExecQueue[number].ExecDial.ExecNumber.Command][0], 20);
		}
		else if (SYS_Opt2[num].QueueKind == SYS_BATCH_TX) {
			CMN_StringCopyNum(&SYS_Opt2[num].CommandDirectDial[0], SYB_BatchTxFile[bat_num].DialNumber[SYB_ExecQueue[number].ExecDial.ExecNumber.Command].FaxNumber.Direct, 20);
		}
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		else {
			CMN_StringCopyNum(&SYS_Opt2[num].CommandDirectDial[0], SYB_ContinuousPolling.DialNumber.Direct[SYB_ExecQueue[number].ExecDial.ExecNumber.Command], 20);
		}
#endif
		break;
	default:
		break;
	}
}

