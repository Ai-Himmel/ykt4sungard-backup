/*******************************************************************************
*	System			: POPLAR_F
*	File Name		: MDM_CMD.C
*	Auther			: 
*	Date			: 1999/10/06
*	RealTimeOS		: ＲＩＣＥ（Ｖ５３）モニター
*					  ＲＩＣＥ（Ｈ８）モニター
*	Description		:
*	Maintenanceke	: 
*	Copyright (C) 1996 Murata Machinery Ltd., All rights reserved.
*******************************************************************************/

/*
** 新短縮ハンドシェイクには未対応。 1997/08/12 by H.Kubo
*/

/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\ncu_cnst.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\cmn_def.h"		/* 1997/07/17 H. Kubo */

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\ncu_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\man_pro.h"		/* 1996/03/11 Y.M */
#include "\src\atlanta\define\cmn_pro.h"		/* Add By O.Kimoto 1996/06/14 */
#include "\src\atlanta\define\mem_pro.h"		/* 1997/03/18 Y.Murata */
#include "\src\memsw\define\mems_pro.h"		/* H.Kubo 1997/07/07 */

#if defined (KEISATSU) /* 警察FAX 05/09/16 石橋正和 */
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\sys_data.h"
#endif

#if defined (KEISATSU) /* 警察FAX DVT_ID62 Added by SMuratec 夏 2005/12/08 */
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\define\sys_line.h"
#endif

/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

/* for Debug by O.Kimoto 1998/08/04 */
CONST UBYTE DEBUG_SPIX = 0;

/*************************************************************************
	module		:[命令送信]
	function	:[
		1.モデムタイプ・速度設定処理
		2.ＦＳＫ送信モデムオープン処理
		3.各フレーム送信処理（ＦＳＫ送信モデムライト）
		4.ＦＳＫ送信モデムクローズ
	]
	return		:[なし]
	common		:[
		SDCS_TransmitFlag
		MakerCodeRxFlag
		FaxComTXorRX_Sign
		AvailableTxBaudRate
		ModemBlock
		TxNonStandardFrameByteCount
		TxID_FrameByteCount
		TxStandardFrameByteCount
		DIS_ReceivedFlag
		MDM_ModemBuffer
		EchoFCF
	]
	condition	:[
		MDM_ModemBuffer[0][]	: 非標準フレーム
		MDM_ModemBuffer[1][]	: 被呼端末識別フレーム
		MDM_ModemBuffer[2][]	: 標準フレーム
		MDM_ModemBuffer[3][]	: ＰＷＤフレーム
		MDM_ModemBuffer[4][]	: ＳＥＰフレーム
		MDM_ModemBuffer[5][]	: ＳＵＢフレーム
	
	]
	comment		:[
		この関数を呼ぶ前に、モデムバッファに送出するフレーム及び、バイト数を設定しておくこと
		各フレーム送出バイト数で、そのフレーム送出するか判断する
	]
	date		:[1993/12/09]
	author		:[曽根岡拓]
*************************************************************************/
void 	MDM_TransmitCommand(void)
{
	InitializeModemWork();	/**	モデムワークエリアクリア	*/

	/****************************
	** モデムタイプ、速度設定処理
	****************************/
	/* Ｔ．３０ ＡｎｎｅｘＦ時 */
	if (SYS_V34ProcedureExecuting()) {
		ModemTypeSet(MDM_GetIO(POS_CONF));	/**	ＦＳＫモードに設定	*/
	}
	/* Ｔ．３０ Ｂａｓｅ時 */
	else {
		if (SDCS_TransmitFlag == 1) {	/**	短縮ハンドシェークの時	*/
			if (SYS_TxTotalPage == 0) {		/**	最初のページである	96/05/30 条件追加 By T.Yamaguchi */ /* Added by H.Kubo 1997/08/12 */
				ModemTypeSet(AvailableTxBaudRate);	/**	モデムタイプ・速度設定	*/
			}
			else { /* else block is added by H.Kubo 1997/08/12 */
				ModemTypeSet(TxBaudRate);	/**	モデムタイプ・速度設定	*/
			}
			if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
				ModemBlock.Training = TRAINING_LONG;	/**	トレーニングをロングに設定	*/
			}
			else {	/**	その他の時	*/
				ModemBlock.Training = TRAINING_SHORT;	/**	トレーニングをショートに設定	*/
			}
		}
		else {	/**	その他の時	*/
			ModemTypeSet(BPS300_V21);	/**	ＦＳＫモードに設定	*/
		}
	}

	/*	ハンドシェイク手順設定	*/
	ModemBlock.Chain = CHAIN_OFF;
	SaveT30TimingData(SYS_T30_START_TIME);	/**	Ｔ３０　ＦＳＫ送信開始　タイミングデータセット	*/

	/*=== Ported from ORANGE\src\mdm_cmd.c by H.Kubo 1997/08/12 ==*/
	/*----------------------------*/
	/* 海外認可共通対応           */
	/* FOREIGN_APPROVAL No.1-8 ⑤ */
	/*----------------------------*/
	/* 
	** 信号間ﾀｲﾐﾝｸﾞを調整する処理追加 150ms 1997/06/02  By T.Yamaguchi
	*/
	if(TimerCutStatus == 0){
    	wai_tsk( 15 );	/* add by M.HARADA  FSK間の時間75ms以上 '96/11/27 */
	}
	TimerCutStatus = 0;
	/*=== end of ported code. 1997/08/12 ===*/

	/*	ＦＳＫ送信モデムオープン	*/
	TxFskOpen();	/**	ＦＳＫ送信モデムオープン	*/


#if defined(JPN) || defined(USA)
	/** Ｆコード対応 */
	/**	ＰＷＤフレーム送出処理	*/
	if (TxPasswordFrameByteCount != 0) {	/**	ＰＷＤフレーム送出データ有りの時	*/
		if (DIS_ReceivedFlag == YES) {	/**	ＤＩＳを受信済み？	*/
			MDM_ModemBuffer[InPWD][2] |= 0x01;	/**	Ｘビット処理	*/
		}
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InPWD][0], (UBYTE)TxPasswordFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InPWD][0], TxPasswordFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/**	ＳＥＰフレーム送出処理	*/
	if (TxSelectiveFrameByteCount != 0) {	/**	ＳＥＰフレーム送出データ有りの時	*/
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InSEP][0], (UBYTE)TxSelectiveFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InSEP][0], TxSelectiveFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/**	ＳＵＢフレーム送出処理	*/
	if (TxSubaddressFrameByteCount != 0) {	/**	ＳＵＢフレーム送出データ有りの時	*/
		if (DIS_ReceivedFlag == YES) {	/**	ＤＩＳを受信済み？	*/
			MDM_ModemBuffer[InSUB][2] |= 0x01;	/**	Ｘビット処理	*/
		}
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InSUB][0], (UBYTE)TxSubaddressFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InSUB][0], TxSubaddressFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/*	非標準フレーム送出処理	*/
	if (TxNonStandardFrameByteCount != 0) {	/**	非標準フレーム送出データ有りの時	*/
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InNS][0], (UBYTE) TxNonStandardFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InNS][0], TxNonStandardFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/*	被呼端末識別フレーム送出処理	*/
	if (TxID_FrameByteCount != 0) {	/**	被呼端末識別フレーム送出データ有りの時	*/
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InID][0], (UBYTE)TxID_FrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InID][0], TxID_FrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/*	標準フレーム送出処理	*/
	if (TxStandardFrameByteCount != 0) {	/**	標準フレームデータ有りの時	*/
		if (DIS_ReceivedFlag == YES) {	/**	ＤＩＳを受信済み？	*/
			MDM_ModemBuffer[InSTD][2] |= 0x01;	/**	Ｘビット処理	*/
		}
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InSTD][0], (UBYTE)TxStandardFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		if (MDM_ModemBuffer[InSTD][2] != DIS_F) {	/**	エコーフレーム対策用処理	*/
			EchoFCF = MDM_ModemBuffer[InSTD][2];
		}
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InSTD][0], TxStandardFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

#else
	/*--------------------------*/
	/* 海外認可共通対応         */
	/* FOREIGN_APPROVAL No.1-12 */
	/*--------------------------*/
	/* 手順信号送出順序
	*/
	/*	非標準フレーム送出処理	*/
	if (TxNonStandardFrameByteCount != 0) {	/**	非標準フレーム送出データ有りの時	*/
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InNS][0], (UBYTE) TxNonStandardFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InNS][0], TxNonStandardFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/** Ｆコード対応 */
	/**	ＰＷＤフレーム送出処理	*/
	if (TxPasswordFrameByteCount != 0) {	/**	ＰＷＤフレーム送出データ有りの時	*/
		if (DIS_ReceivedFlag == YES) {	/**	ＤＩＳを受信済み？	*/
			MDM_ModemBuffer[InPWD][2] |= 0x01;	/**	Ｘビット処理	*/
		}
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InPWD][0], (UBYTE)TxPasswordFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InPWD][0], TxPasswordFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/**	ＳＥＰフレーム送出処理	*/
	if (TxSelectiveFrameByteCount != 0) {	/**	ＳＥＰフレーム送出データ有りの時	*/
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InSEP][0], (UBYTE)TxSelectiveFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InSEP][0], TxSelectiveFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/**	ＳＵＢフレーム送出処理	*/
	if (TxSubaddressFrameByteCount != 0) {	/**	ＳＵＢフレーム送出データ有りの時	*/
		if (DIS_ReceivedFlag == YES) {	/**	ＤＩＳを受信済み？	*/
			MDM_ModemBuffer[InSUB][2] |= 0x01;	/**	Ｘビット処理	*/
		}
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InSUB][0], (UBYTE)TxSubaddressFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InSUB][0], TxSubaddressFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/*	被呼端末識別フレーム送出処理	*/
	if (TxID_FrameByteCount != 0) {	/**	被呼端末識別フレーム送出データ有りの時	*/
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InID][0], (UBYTE)TxID_FrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InID][0], TxID_FrameByteCount);	/**	Ｔ３０データセット処理	*/
	}

	/*	標準フレーム送出処理	*/
	if (TxStandardFrameByteCount != 0) {	/**	標準フレームデータ有りの時	*/
		if (DIS_ReceivedFlag == YES) {	/**	ＤＩＳを受信済み？	*/
			MDM_ModemBuffer[InSTD][2] |= 0x01;	/**	Ｘビット処理	*/
		}
		TxFskWrite((UBYTE *)&MDM_ModemBuffer[InSTD][0], (UBYTE)TxStandardFrameByteCount);	/**	ＦＳＫ送信モデムライト	*/
		if (MDM_ModemBuffer[InSTD][2] != DIS_F) {	/**	エコーフレーム対策用処理	*/
			EchoFCF = MDM_ModemBuffer[InSTD][2];
		}
		SaveT30Data(SYS_T30_TX_FRAME, &MDM_ModemBuffer[InSTD][0], TxStandardFrameByteCount);	/**	Ｔ３０データセット処理	*/
	}
#endif

	/*	ＦＳＫ送信モデムクローズ	*/
	TxFskClose();	/**	ＦＳＫ送信モデムクローズ	*/

	SaveT30TimingData(SYS_T30_END_TIME);	/**	Ｔ３０　ＦＳＫ送信終了　タイミングデータセット	*/

	/* R288F Internal Monitor By O.Kimoto 1996/05/24 */
	if (SDCS_TransmitFlag == 1) {	/**	短縮ハンドシェークの時	*/
		MDM_NewT30Status = (UBYTE)(MODE_TX_FSK | SPEED_HANDSHAKE_BIT);
	}
	else {
		MDM_NewT30Status = MODE_TX_FSK;
	}
}


/*************************************************************************
	module		:[命令受信]
	function	:[
		1.ＦＳＫ受信モードでオープンする
		2.ＦＳＫ受信フレーム監視タスクのタイマ値を設定する
		3.ＦＳＫ受信フレーム監視タスクを起動する
		4.ＦＳＫ受信フレーム監視タスクよりメッセージを受信する
		5.ＦＳＫ受信モードをクローズする
		6.ＦＳＫ受信フレーム監視タスクのメッセージ内容をそのまま戻り値とする
	]
	return		:[
		0:ＦＳＫ受信ＯＫ
		1:ＦＳＫ受信ＮＧ
	]
	common		:[
		RxECM_PixTimeoutFlag
		RxFskTimer
	]
	condition	:[]
	comment		:[]
	date		:[1993/12/10]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	MDM_ReceiveCommand(WORD receive_timer)
{
	MESSAGE_t	*MDM_Msg;
	UBYTE	rtn;

	InitializeModemWork();	/**	モデムワークエリアクリア	*/

	RxFskOpen();	/**	ＦＳＫ受信モデムオープン	*/

	/*	ＦＳＫ受信フレーム監視タスク起動	*/
	if (RxECM_PixTimeoutFlag == 1) {	/**	ＥＣＭタイムアウト回避フラグ有効の時	*/
		RxFskTimer = Set64K_PixTime();	/**	ＦＳＫ受信フレーム監視タスク用タイマを回避タイマ設定	*/
	}
	/**	その他の時	*/
	else {	
		RxFskTimer = receive_timer;
	}
	tskno_RxFrameControl = 0xffff;
	cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &RxFskTimer);	/**	ＦＳＫ受信フレーム監視タスク起動 */

	/*	メッセージ受信
	** 1.FSK_RECEIVE	:ＦＳＫ受信ＯＫ
	** 2.FSK_ERROR		:ＦＳＫ受信ＮＧ
	** 3.FSK_CC_RETRIN	:コントロールチャンネル  リトレイン
	*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
	} while (!((MDM_Msg->Message == MSG_FSK_RECEIVE) ||
				(MDM_Msg->Message == MSG_FSK_ERROR) ||
				(MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));

	/*	ＦＳＫ受信フレーム監視タスク終了	*/
	if (tskno_RxFrameControl != 0xffff) {
		del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレーム監視タスク終了	*/
	}

	RxFskClose();	/**	ＦＳＫ受信モデムクローズ	*/

	/*	戻り値設定	*/
	switch (MDM_Msg->Message) {	/**	メッセージ受信内容	*/
	case MSG_FSK_RECEIVE:	/**	ＦＳＫ受信の時	*/
		rtn = FSK_RECEIVE;	/**	戻り値ＦＳＫ受信設定	*/
		break;
	case MSG_CC_RETRAIN_DETECT:	/**	コントロールチャンネルリトレイン	*/
		rtn = CC_RETRAIN;	/**	戻り値コントロールチャンネルリトレイン	*/
		break;
	case MSG_FSK_ERROR:	/**	ＦＳＫエラーの時	*/
	default:	/**	その他の時	*/
		rtn = FSK_ERROR;	/**	戻り値エラー設定	*/
		break;
	}
	return (rtn);
}


/*************************************************************************
	module		:[応答受信]
	function	:[
		1.Ｔ３０規格の応答受信を行う
	]
	return		:[
		0:ＦＳＫ受信ＯＫ
		1:ＦＳＫ受信ＮＧ
	]
	common		:[
		SYS_FaxComType
		RxTotalPage
	]
	condition	:[
		FinalRxMode
		SYS_FaxComType
		SYS_RxTotalPage
	]
	comment		:[]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE MDM_ReceiveResponse(WORD receive_timer)
{
	MESSAGE_t	*MDM_Msg;
	UWORD	timer;
	UBYTE	rtn;

	InitializeModemWork();	/**	モデムワーククリア	*/

	/*	ＦＳＫ受信モデムオープン	*/
	RxFskOpen();	/**	ＦＳＫ受信モデムオープン	*/

	/*	Ｔ４タイマ値設定処理	*/
	/* 95.1.7 3line Insert for diagnostic */
	if (FinalRxMode == DIAGMODE) {
		timer = 6000/10;
	}
	else {
		timer = receive_timer;
	}

	/*	ＦＳＫ受信フレーム監視タスク起動	*/
	tskno_RxFrameControl = 0xffff;
	cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/

	/*	メッセージ受信
	** 1.FSK_RECEIVE	:ＦＳＫ受信ＯＫ
	** 2.FSK_ERROR		:ＦＳＫ受信ＮＧ
	** 3.CC_RETRAIN		:コントロールチャンネルリトレイン検出
	*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
	} while (!((MDM_Msg->Message == MSG_FSK_RECEIVE) ||
	           (MDM_Msg->Message == MSG_FSK_ERROR) ||
	           (MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));

	/*	ＦＳＫ受信フレーム監視タスク終了	*/
	if (tskno_RxFrameControl != 0xffff) {
		del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレーム監視タスク終了	*/
	}

	/*	ＦＳＫ受信モデムクローズ	*/
	RxFskClose();	/**	ＦＳＫ受信モデムクローズ	*/

	/*	戻り値設定	*/
	switch (MDM_Msg->Message) {	/**	メッセージ受信内容	*/
	case MSG_FSK_RECEIVE:	/**	ＦＳＫ受信の時	*/
		rtn = FSK_RECEIVE;	/**	戻り値ＦＳＫ受信設定	*/
		break;
	case MSG_CC_RETRAIN_DETECT:	/**	コントロールチャンネルリトレイン	*/
		rtn = CC_RETRAIN;	/**	戻り値コントロールチャンネルリトレイン	*/
		break;
	case MSG_FSK_ERROR:	/**	ＦＳＫエラーの時	*/
	default:	/**	その他の時	*/
		rtn = FSK_ERROR;	/**	戻り値ＦＳＫエラー設定	*/
		break;
	}
	return (rtn);
}

#if defined (KEISATSU) /* 警察FAX 05/09/16 */
/**************************************************************************************************/
/**
	@brief		応答受信(CNG同時監視)
	
	@li			
	@param		
	@return		FSK_RECEIVE:	FSK受信
				CC_RETRAIN:		コントロールチャンネルリトレイン
				MDM_DETECT_CNG:	CNG検出
				FSK_ERROR:		エラー
	@note		
	@date		2005/09/16 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE MDM_ReceiveResponseOrCNG(WORD receive_timer)
{
	MESSAGE_t	*MDM_Msg;
	UWORD	timer;
	UBYTE	rtn;
	
	struct ToneDetectMailBoxData_t td_mail_box;
	UWORD cng_det_tsk;

	InitializeModemWork();	/**	モデムワーククリア	*/

	/*	ＦＳＫ受信モデムオープン	*/
	RxFskOpen();	/**	ＦＳＫ受信モデムオープン	*/

	/*	Ｔ４タイマ値設定処理	*/
	/* 95.1.7 3line Insert for diagnostic */
	if (FinalRxMode == DIAGMODE) {
		timer = 6000/10;
	}
	else {
		timer = receive_timer;
	}
	
	MDM_FilterSet(CNG_FILTER);
	
	td_mail_box.ToneType = CNG_TONE;
	td_mail_box.SendMBX = mbxno.MDM_Task;
	cre_tsk(&cng_det_tsk, TSK_ATD_TONEDETECTPATTERN1TASK, &td_mail_box); /* CNG検出タスク起動 */
	
	/*	ＦＳＫ受信フレーム監視タスク起動	*/
	tskno_RxFrameControl = 0xffff;
	cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/

	/*	メッセージ受信
	** 1.FSK_RECEIVE	:ＦＳＫ受信ＯＫ
	** 2.FSK_ERROR		:ＦＳＫ受信ＮＧ
	** 3.CC_RETRAIN		:コントロールチャンネルリトレイン検出
	*/
	while (1) {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
		
		if (MDM_Msg->Item == FROM_MDM_RXFSKFRAMECONTROLTASK) {
			if ((MDM_Msg->Message == MSG_FSK_RECEIVE) || (MDM_Msg->Message == MSG_FSK_ERROR) || (MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)) {
				break;
			}
		}
		else if (MDM_Msg->Item == FROM_AUTODIAL) {
			if (MDM_Msg->Message == CNG_TONE) { /* CNG検出 */
				break;
			}
		}
	}

	/*	ＦＳＫ受信フレーム監視タスク終了	*/
	if (tskno_RxFrameControl != 0xffff) {
		del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレーム監視タスク終了	*/
	}
	
	del_tsk(&cng_det_tsk); /* CNG検出タスク終了 */
	
	/*	ＦＳＫ受信モデムクローズ	*/
	RxFskClose();	/**	ＦＳＫ受信モデムクローズ	*/

	/*	戻り値設定	*/
	if (MDM_Msg->Item == FROM_AUTODIAL) {
		rtn = MDM_DETECT_CNG; /* CNG検出 */
	}
	else {
		switch (MDM_Msg->Message) {	/**	メッセージ受信内容	*/
		case MSG_FSK_RECEIVE:	/**	ＦＳＫ受信の時	*/
			rtn = FSK_RECEIVE;	/**	戻り値ＦＳＫ受信設定	*/
			break;
		case MSG_CC_RETRAIN_DETECT:	/**	コントロールチャンネルリトレイン	*/
			rtn = CC_RETRAIN;	/**	戻り値コントロールチャンネルリトレイン	*/
			break;
		case MSG_FSK_ERROR:	/**	ＦＳＫエラーの時	*/
		default:	/**	その他の時	*/
			rtn = FSK_ERROR;	/**	戻り値ＦＳＫエラー設定	*/
			break;
		}
	}
	return (rtn);
}

/**************************************************************************************************/
/**
	@brief		指令起動信号による一斉受信における最初の応答受信
	
	@li			
	@param		
	@return		FSK_RECEIVE:	FSK受信
				CC_RETRAIN:		コントロールチャンネルリトレイン
				MDM_DETECT_CNG:	CNG検出
				FSK_ERROR:		エラー
	@note		
	@date		2005/09/16 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE MDM_ReceiveResponseOrIsseiOpr(void)
{
	MESSAGE_t	*MDM_Msg;
	MESSAGE_t	MDM_Msg_Bk; /* 警察FAX DVT_ID82 Added by SMuratec 李 2005/12/26 */
	UWORD	timer;
	UBYTE	rtn;
	
	struct ToneDetectMailBoxData_t td_mail_box;
	UWORD cng_det_tsk;
	
	BOOL bmsg_rcv;
	
	bmsg_rcv = FALSE;

	InitializeModemWork();	/**	モデムワーククリア	*/

	/*	ＦＳＫ受信モデムオープン	*/
	RxFskOpen();	/**	ＦＳＫ受信モデムオープン	*/

	/*	Ｔ４タイマ値設定処理	*/
	timer = 0xFFFF;
	
	MDM_FilterSet(CNG_FILTER);
	
	/*	ＦＳＫ受信フレーム監視タスク起動	*/
	tskno_RxFrameControl = 0xffff;
	cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/

	/*	メッセージ受信
	** 1.FSK_RECEIVE	:ＦＳＫ受信ＯＫ
	** 2.FSK_ERROR		:ＦＳＫ受信ＮＧ
	** 3.CC_RETRAIN		:コントロールチャンネルリトレイン検出
	*/
	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) { /* 指令起動信号が依然としてONの場合 */
		FCM_ShireiKidoWaitFor1stDCS = TRUE;
		while (1) {
			bmsg_rcv = TRUE;
			rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
			
			/* 警察FAX DVT_ID82 Added by SMuratec 李 2005/12/26 */
			CMN_DisableInterrupt();			/* DI */
			MDM_Msg_Bk.Item = MDM_Msg->Item;
			MDM_Msg_Bk.Message = MDM_Msg->Message;
			MDM_Msg_Bk.SubMessage1 = MDM_Msg->SubMessage1;
			MDM_Msg_Bk.SubMessage2 = MDM_Msg->SubMessage2;
			MDM_Msg_Bk.SubMessage3 = MDM_Msg->SubMessage3;
			MDM_Msg_Bk.SubMessage4 = MDM_Msg->SubMessage4;
			MDM_Msg = &MDM_Msg_Bk;
			CMN_EnableInterrupt();			/* EI */

			if (MDM_Msg->Item == FROM_MDM_RXFSKFRAMECONTROLTASK) {
				if ((MDM_Msg->Message == MSG_FSK_RECEIVE) || (MDM_Msg->Message == MSG_FSK_ERROR) || (MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)) {
					break;
				}
			}
			else if (MDM_Msg->Item == FROM_MAIN) {
				if (MDM_Msg->Message == MSG_ISSEI_TX) { /* 一斉指令送信 */
					break;
				}
			}
			else if (MDM_Msg->Item == FROM_SENSOR) {
				if (MDM_Msg->Message == MSG_SHIREI_OFF) { /* 指令起動信号OFF */
					break;
				}
			}
		}
		FCM_ShireiKidoWaitFor1stDCS = FALSE;
	}

	/*	ＦＳＫ受信フレーム監視タスク終了	*/
	if (tskno_RxFrameControl != 0xffff) {
		del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレーム監視タスク終了	*/
	}
	
	/*	ＦＳＫ受信モデムクローズ	*/
	RxFskClose();	/**	ＦＳＫ受信モデムクローズ	*/

	/*	戻り値設定	*/
	if (bmsg_rcv == FALSE) {
		rtn = MDM_SHIREI_OFF;
	}
	else if (MDM_Msg->Item == FROM_MAIN) {
		switch (MDM_Msg->Message) {
		case MSG_ISSEI_TX: /* 一斉送信へ移行 */
			rtn = MDM_ISSEI_TX;
			break;
		default:
			rtn = FSK_ERROR;
			break;
		}
	}
	else if (MDM_Msg->Item == FROM_SENSOR) {
		switch (MDM_Msg->Message) {
		case MSG_SHIREI_OFF: /* 指令起動信号OFF */
			rtn = MDM_SHIREI_OFF;
			break;
		default:
			rtn = FSK_ERROR;
			break;
		}
	}
	else {
		switch (MDM_Msg->Message) {	/**	メッセージ受信内容	*/
		case MSG_FSK_RECEIVE:	/**	ＦＳＫ受信の時	*/
			rtn = FSK_RECEIVE;	/**	戻り値ＦＳＫ受信設定	*/
			break;
		case MSG_CC_RETRAIN_DETECT:	/**	コントロールチャンネルリトレイン	*/
			rtn = CC_RETRAIN;	/**	戻り値コントロールチャンネルリトレイン	*/
			break;
		case MSG_FSK_ERROR:	/**	ＦＳＫエラーの時	*/
		default:	/**	その他の時	*/
			rtn = FSK_ERROR;	/**	戻り値ＦＳＫエラー設定	*/
			break;
		}
	}
	return (rtn);
}
#endif

/*************************************************************************
	module		:[送信側（被）会話予約処理用命令受信]
	function	:[
		1.Ｔ３タイムの間、オフフック検出及び、ＦＳＫ受信を監視する
		2.Ｔ３タイムオーバ時、モードに応じてＴ１タイマの間命令受信する
	]
	return		:[
		0:ＦＳＫ受信ＯＫ
		1:ＦＳＫ受信ＮＧ
		2:オフフック検出
		3:Ｔ３タイムオーバ
		4:Ｔ１タイムオーバ
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	MDM_TxVoiceReqRcvCmd(UBYTE	mode)
{
	MESSAGE_t	*MDM_Msg;
	UBYTE		rtn;
	UWORD		timer;
	struct Timer10msData_t	t3timer;
	struct Timer10msData_t	t1timer;
	struct GenerateRingData_t ring_data;		/*  1994/8/31 Y.Suzuki */
	/* Added by H.Kubo 1997/08/12 */
	UBYTE		timerID_T1_Timer;
	UBYTE		timerID_T3_Timer;

	tskno_Bell = 0xFFFF;

	InitializeModemWork();	/**	モデムワークエリアクリア	*/

	/*	ＦＳＫ受信モデムオープン	*/
	RxFskOpen();	/**	ＦＳＫ受信モデムオープン	*/

	/*	ＦＳＫ受信フレーム監視タスク起動	*/
	timer = T2_TIME / 10;	/**	Ｔ２タイマ設定	*/
	cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/

	/*	ＯＨ検出・呼び出しベル鳴動タスク起動	*/
	/* 以下H8からとって来ました 1994/8/31 Y.Suzuki */
	GenerateRingStartRelayControl();
	ring_data.StartTime		= 0;
	ring_data.SendMBX		= mbxno.MDM_Task;
	ring_data.RingingTel	= ALL_TEL_RINGING;

	cre_tsk(&tskno_Bell, TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );	/** ＯＨ検出・呼び出しベル鳴動タスク起動 */

	/*	Ｔ３タイマ用タイマタスク起動処理	*/
	t3timer.Time = 1200;/* (T3_TIME/10) 実測値短いので伸ばす。 94/11/21 Y.Suzuki	*/
	t3timer.SendMBX = mbxno.MDM_Task;	/**	Ｔ３タイマ、メイルボックス設定	*/
	t3timer.ReturnValue = MSG_T3_TIME_OVER;	/**	戻り値設定	*/
	timerID_T3_Timer = 0xff;
	CMN_MultiTimer10msStart(&timerID_T3_Timer, &t3timer); /* Ported from ORANGE\src\mdm_cmd.c by H.Kubo 1997/08/12 */

	while ( 1 ) {
		/*	メッセージ受信
		** 1.MSG_FSK_RECEIVE	:ＦＳＫ受信ＯＫ	(10)
		** 2.MSG_FSK_ERROR		:ＦＳＫ受信ＮＧ	(11)
		** 3.FCOM_TEL1_OFF_HOOK					(7)
		** 4.FCOM_TEL2_OFF_HOOK					(8)
		** 5.FCOM_HOOK_KEY						(9)
		** 6.FCOM_STOP_KEY						(5)
		** 7:MSG_T3_TIME_OVER	:Ｔ３タイムオーバ(13)
		*/
		do {
			rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
		} while (!((MDM_Msg->Message == MSG_FSK_RECEIVE) ||
					(MDM_Msg->Message == MSG_FSK_ERROR) ||
					(MDM_Msg->Message == FCOM_TEL1_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_TEL2_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_HOOK_KEY) ||
					(MDM_Msg->Message == FCOM_STOP_KEY) ||
					(MDM_Msg->Message == MSG_T3_TIME_OVER) ||
					(MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));

		rtn = (UBYTE)MDM_Msg->Message;
		
/* 警察FAX DVT_ID62 Added start by SMuratec 夏 2005/12/08 */ 
#if defined(KEISATSU)
		if (rtn == MSG_T3_TIME_OVER) {
			if ( CHK_LineSetting()		/* 回線設定 == 標準回線 */
				&& HDST_RelaySetting() ) {	/* ハンドセットは拡張回線側接 */
				switch (NCU_LineStatus & EXT_LINE_STATUS) {
				case EXT_CI_IN:
		 			break;
				default:
					HDST_RelayOff();        /* ハンドセットを標準回線に接続する */
					break;
				}
			}
			else if ( !CHK_LineSetting()		/* 回線設定 == 拡張回線 */
					&& !HDST_RelaySetting() ) {			/* ハンドセットは標準回線側接 */
				switch (NCU_LineStatus & STD_LINE_STATUS) {
				case STD_CI_IN:
		 			break;
				default:
					HDST_RelayOn();        /* ハンドセットを拡張回線に接続する */
					break;
				}
			}
			UpdateLCD();
		}
#endif
/* 警察FAX DVT_ID62 Added end by SMuratec 夏 2005/12/08 */ 

		/*	ＦＳＫ受信エラー時、再起動処理	*/
		if (rtn == MSG_FSK_ERROR) {	/**	メッセージ受信内容ＦＳＫエラーの時	*/

			/*	ＦＳＫ受信モデムクローズ	*/
			RxFskClose();/* 94/11/20 Y.Suzuki */	/**	ＦＳＫ受信モデムクローズ	*/

			/*	ＦＳＫ受信フレーム監視タスク終了	*/
			del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレーム監視タスク終了	*/

			/*	ＦＳＫ受信フレーム監視タスク再起動	*/
			RxFskOpen();/* 94/11/18 Y.Suzuki */	/**	ＦＳＫ受信モデムオープン	*/
			cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/*	ＦＳＫ受信フレーム監視タスク再起動	*/
		}
		else {	/**	その他の時	*/
			break;	/**	ループ抜ける	*/
		}
	}
	/*	タイマタスク終了	*/
	if (timerID_T3_Timer != 0xff) { /* Ported from ORANGE by H.Kubo 1997/08/12 */
		CMN_MultiTimer10msStop(&timerID_T3_Timer);
	}

	/*	ＯＨ検出・呼び出しベル鳴動タスク終了	*/
	if (tskno_Bell != 0xFFFF) {
		del_tsk( &tskno_Bell  );	/**	ＯＨ検出・呼び出しベル鳴動タスク終了	*/
	}

	/*	ＦＳＫ受信フレームコントロールタスク終了	*/
	del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレームコントロールタスク終了	*/

	/*	ＦＳＫ受信モデムクローズ	*/
	RxFskClose();/* 94/11/20 Y.Suzuki */	/**	ＦＳＫ受信モデムクローズ	*/

	/*	Ｔ１タイマの間、命令受信しつづける
	**	今受信したポストメッセージが（ＰＲＩ－）ＥＯＰで応答がＰＩＰの時以外
	*/
	if ((rtn == MSG_T3_TIME_OVER) &&
		(mode == MODE_T3_T1_TIMER)) {	/**	メッセージ受信内容がＴ３タイムオーバ＆＆Ｔ１タイマ間命令受信指定有りの時	*/
		/*	Ｔ１タイマ用タイマタスク起動処理	*/
		t1timer.Time = (T1_TIME/10);	/**	Ｔ１タイマ値設定	*/
		t1timer.SendMBX = mbxno.MDM_Task;	/**	Ｔ１タイマ、メイルボックス設定	*/
		t1timer.ReturnValue = MSG_T1_TIME_OVER;	/**	戻り値設定	*/
		timerID_T1_Timer = 0xff;
		CMN_MultiTimer10msStart(&timerID_T1_Timer, &t1timer);/* Ported from ORANGE by H.Kubo 1997/08/12 */

		/*	ＦＳＫ受信フレーム監視タスク起動	*/
		timer = T2_TIME/10;	/**	Ｔ２タイマ設定	*/
		RxFskOpen();/* 94/11/18 Y.Suzuki */
		cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/
		while (1) {
			/*	メッセージ受信
			** 1.MSG_FSK_RECEIVE	:ＦＳＫ受信ＯＫ
			** 2.MSG_FSK_ERROR		:ＦＳＫ受信ＮＧ
			** 3:MSG_T1_TIME_OVER	:Ｔ１タイムオーバ
			*/
			do {
				rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
			} while (!((MDM_Msg->Message == MSG_FSK_RECEIVE) ||
					(MDM_Msg->Message == MSG_FSK_ERROR) ||
					(MDM_Msg->Message == MSG_T1_TIME_OVER) ||
					(MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));

			rtn = (UBYTE)MDM_Msg->Message;

			/*	ＦＳＫ受信エラー時、再起動処理	*/
			if (rtn == MSG_FSK_ERROR) {	/**	メッセージ受信ＦＳＫエラーの時	*/
				/*	ＦＳＫ受信モデムクローズ	*/
				RxFskClose();/* 94/11/20 Y.Suzuki */	/**	ＦＳＫ受信モデムクローズ	*/

				/*	ＦＳＫ受信フレーム監視タスク終了	*/
				del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレーム監視タスク終了	*/

				/*	ＦＳＫ受信モデムオープン	*/
				RxFskOpen();/* 94/11/20 Y.Suzuki */	/**	ＦＳＫ受信モデムオープン	*/

				/*	ＦＳＫ受信フレーム監視タスク再起動	*/
				cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク再起動	*/
			}
			else {	/**	その他の時	*/
				break;
			}
		}
		/*	タイマタスク終了	*/
		if (timerID_T1_Timer != 0xff) { /* Ported from ORANGE by H.Kubo 1997/08/12 */
			CMN_MultiTimer10msStop(&timerID_T1_Timer);
		}

		/*	ＦＳＫ受信フレームコントロールタスク終了	*/
		del_tsk(&tskno_RxFrameControl);	/**	ＦＳＫ受信フレームコントロールタスク終了	*/
	}
	/*	ＦＳＫ受信モデムクローズ	*/
	RxFskClose();	/**	ＦＳＫ受信モデムクローズ	*/

	/*	戻り値設定	*/
	/*switch (MDM_Msg->Message) { 1997/02/24 Y.Murata */
	switch (rtn) {
	case MSG_FSK_RECEIVE:
		rtn = FSK_RECEIVE;
		break;
	case MSG_FSK_ERROR:
		rtn = FSK_ERROR;
		break;
	case FCOM_TEL1_OFF_HOOK:
		rtn = TEL1_OH_DETECT;
		break;
	case FCOM_TEL2_OFF_HOOK:
		rtn = TEL2_OH_DETECT;
		break;
	case FCOM_HOOK_KEY:
		rtn = HOOK_KEY_OH_DETECT;
		break;
	case MSG_T3_TIME_OVER:
	case FCOM_STOP_KEY:/* H8 と同じにする */
		rtn = T3_TIME_OVER;
		break;
	case MSG_CC_RETRAIN_DETECT:	/**	コントロールチャンネルリトレイン	*/
		rtn = CC_RETRAIN;	/**	戻り値ＦＳＫ受信設定	*/
		break;
	case MSG_T1_TIME_OVER:
	default:
		rtn = T1_TIME_OVER;
		break;
	}
	GenerateRingEndRelayControl();/* 94/11/18 Y.Suzuki */
	return (rtn);
}


/*************************************************************************
	module		:[受信側被会話予約処理用命令受信]
	function	:[
		1.Ｔ３タイマの間、オフフック検出及びＦＳＫ受信を監視する
		2.ＰＲＩ－Ｑを３回受信するまで、再度ＦＳＫ受信を実行する
	]
	return		:[
		0:ＦＳＫ受信ＯＫ
		1:ＦＳＫ受信ＮＧ
		2:オフフック検出
		3:Ｔ３タイムオーバ
	]
	common		:[
		MDM_ModemBuffer
	]
	condition	:[]
	comment		:[
		＜関数脱出条件＞
		1.ＰＲＩ－Ｑを３回受信した時
		2.ＰＲＩ－Ｑ以外のＦＳＫを受信した時
		3.Ｔ３タイマ経過した時
		4.オフフックを検出した時
	]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	MDM_RxVoiceReqFromTxRcvCmd(void)
{
	MESSAGE_t	*MDM_Msg;
	UWORD			timer;
	UBYTE			rtn;
	struct Timer10msData_t	t3timer;
	struct GenerateRingData_t ring_data;		/*  1994/9/1 Y.Suzuki */

	UBYTE offhook_flag;
	UBYTE loop;
	UBYTE fsk_count;

	tskno_Bell = 0xFFFF;

	InitializeModemWork();	/**	モデムワーククリア	*/

	/*	ＦＳＫ受信モデムオープン	*/
	RxFskOpen();	/**	ＦＳＫ受信モデムオープン	*/

	/*	ＦＳＫ受信フレーム監視タスク起動	*/
	timer = T2_TIME/10;	/**	Ｔ２タイマ設定	*/
	cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/

	/*	ＯＨ検出・呼び出しベル鳴動タスク起動	*/
	/* 以下H8からとって来ました 1994/9/1 Y.Suzuki */
	GenerateRingStartRelayControl();
	ring_data.StartTime		= 0;
	ring_data.SendMBX		= mbxno.MDM_Task;
	ring_data.RingingTel	= ALL_TEL_RINGING;

	cre_tsk(&tskno_Bell, TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );	/** ＯＨ検出・呼び出しベル鳴動タスク起動 */

	/*	Ｔ３タイマ用タイマタスク起動処理	*/
	/* ＦＳＫを３回受信(または、１回受信＋２回T2ﾀｲﾑｵｰﾊﾞ)したら、タイムオーバーとする。94/11/20 Y.Suzuki */
	t3timer.Time = (T3_TIME/10);	/**	３０秒タイマ値設定	*/
	t3timer.SendMBX = mbxno.MDM_Task;	/**	Ｔ３タイマ、メイルボックス設定	*/
	t3timer.ReturnValue = MSG_T3_TIME_OVER;	/**	戻り値設定	*/
	/*cre_tsk(&tskno_T3_Timer, TSK_CMN_MAN_TIMER10MSTASK, &t3timer);94/11/20 Y.Suzuki */
	loop = 1;/* 94/11/20 Y.Suzuki */
	fsk_count = 0;/* 94/11/20 Y.Suzuki */
	offhook_flag = 0;/* 94/11/20 Y.Suzuki */

	while (loop) {
		/*	メッセージ受信
		** 1.MSG_FSK_RECEIVE	:ＦＳＫ受信ＯＫ	(10)
		** 2.MSG_FSK_ERROR		:ＦＳＫ受信ＮＧ	(11)
		** 3.FCOM_TEL1_OFF_HOOK					(7)
		** 4.FCOM_TEL2_OFF_HOOK					(8)
		** 5.FCOM_HOOK_KEY						(9)
		** 6.FCOM_STOP_KEY						(5)
		** 7:MSG_T3_TIME_OVER	:Ｔ３タイムオーバ(13)使用せず
		*/
		do {
			rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
		} while (!((MDM_Msg->Message == MSG_FSK_RECEIVE) ||
					(MDM_Msg->Message == MSG_FSK_ERROR) ||
					(MDM_Msg->Message == FCOM_TEL1_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_TEL2_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_HOOK_KEY) ||
					(MDM_Msg->Message == FCOM_STOP_KEY) ||
					(MDM_Msg->Message == MSG_T3_TIME_OVER) ||
					(MDM_Msg->Message == MSG_CC_RETRAIN_DETECT)));

		/*	ＦＳＫ受信時	*/
		if (MDM_Msg->Message == MSG_FSK_RECEIVE) {	/**	メッセージ受信ＦＳＫ受信の時	*/
			fsk_count++;	/* 94.10.17 */
			if (offhook_flag == 1) {
				loop = 0;	/* rtn:セット済み */
			}
			else {
				AnalyzeRxPostMessageFrame();		/* 竹内 Oct.27.1994 */
				if (PRI_Q_RxFlag == 1) {		/**	ＰＲＩ－Ｑ	*/
					if (PRI_Q_RxCount >= 3) {	/**	ＰＲＩ－Ｑが３回目の時	*/
						rtn = FSK_RECEIVE;
						loop = 0;
					}
					else{	/**	再度ＦＳＫ受信処理へ	*/
						/**	ＦＳＫ受信モデムクローズ	*/
						RxFskClose();/* 94/11/20 Y.Suzuki */
						if (tskno_RxFrameControl != 0xffff) {
							del_tsk(&tskno_RxFrameControl);
						}

						/**	ＦＳＫ受信モデムオープン	*/
						RxFskOpen();/* 94/11/18 Y.Suzuki */
						cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/
					}
				}
				else{	/**	ＦＳＫ受信	*/
					rtn = FSK_RECEIVE;
					loop = 0;
				}
			}
		}
		/*	ＦＳＫエラー時（Ｔ２タイムオーバ時）	*/
		else if (MDM_Msg->Message == MSG_FSK_ERROR) {	/**	ＦＳＫエラー時（Ｔ２タイムオーバ時）	*/
			fsk_count++;	/* 94.10.17 */
			if (offhook_flag == 1) {
				loop = 0;	/* rtn:セット済み */
			}
			else {
				if (fsk_count >= 2) {	/* fsk_count追加 94/11/20 Y.Suzuki */
					rtn = FSK_ERROR;
					loop = 0;
				}
				else {
					/**	ＦＳＫ受信モデムクローズ	*/
					RxFskClose();/* 94/11/20 Y.Suzuki */
					if (tskno_RxFrameControl != 0xffff) {
						del_tsk(&tskno_RxFrameControl);
					}
					RxFskOpen();/* 94/11/20 Y.Suzuki */
					cre_tsk(&tskno_RxFrameControl, TSK_MDM_RXFSKFRAMECONTROLTASK, &timer);	/**	ＦＳＫ受信フレーム監視タスク起動	*/
				}
			}
		}
		/*	オフフック検出時	*/
		else if ((MDM_Msg->Message == FCOM_TEL1_OFF_HOOK) || (MDM_Msg->Message == FCOM_TEL2_OFF_HOOK)
			 || (MDM_Msg->Message == FCOM_HOOK_KEY)) {	/**	オフフック検出時	*/
			switch(MDM_Msg->Message) {
			case FCOM_TEL1_OFF_HOOK:
				rtn = TEL1_OH_DETECT;
				break;
			case FCOM_TEL2_OFF_HOOK:
				rtn = TEL2_OH_DETECT;
				break;
			case FCOM_HOOK_KEY:
				rtn = HOOK_KEY_OH_DETECT;
				break;
			}
			offhook_flag = 1;
		}
		/*	コントロールチャンネルリトレイン検出時	*/
		else if (MDM_Msg->Message == MSG_CC_RETRAIN_DETECT) {
			rtn = CC_RETRAIN;
			loop = 0;
		}
		/*	Ｔ３タイムオーバ時／ＳＴＯＰキー		*/
		else {	/**	Ｔ３タイムオーバ時／ＳＴＯＰキー		*/
			rtn = T3_TIME_OVER;
			loop = 0;
		}
	}
	/*	ＦＳＫ受信フレーム監視タスク終了	*/
	if (tskno_RxFrameControl != 0xffff) {
		del_tsk( &tskno_RxFrameControl );	/**	ＦＳＫ受信フレーム監視タスク終了	*/
	}
	/*	ＯＨ検出・呼び出しベル鳴動タスク終了	*/
	if (tskno_Bell != 0xFFFF) {
		del_tsk( &tskno_Bell  );	/**	ＯＨ検出・呼び出しベル鳴動タスク終了	*/
	}

	/*	タイマタスク終了	*/

	/*	ＦＳＫ受信モデムクローズ	*/
	RxFskClose();	/**	ＦＳＫ受信モデムクローズ	*/

	/**	戻り値設定	*/
	/*-----既にセット済み------------------
	switch (rtn) {
	case MSG_FSK_RECEIVE:
		rtn = FSK_RECEIVE;
		break;
	case MSG_FSK_ERROR:
		rtn = FSK_ERROR;
		break;
	case FCOM_TEL1_OFF_HOOK:
		rtn = TEL1_OH_DETECT;
		break;
	case FCOM_TEL2_OFF_HOOK:
		rtn = TEL2_OH_DETECT;
		break;
	case FCOM_HOOK_KEY:
		rtn = HOOK_KEY_OH_DETECT;
		break;
	case MSG_CC_RETRAIN_DETECT:
		rtn = CC_RETRAIN;
		break;
	case MSG_T3_TIME_OVER:
	default:
		rtn = T3_TIME_OVER;
		break;
	}
	--------------------------------------*/
	GenerateRingEndRelayControl();/* 94/11/18 Y.Suzuki */
	return (rtn);
}


/*************************************************************************
	module		:[受信側会話予約処理用擬似ベル鳴動]
	function	:[
		1.Ｔ３タイマの間、擬似ベルを鳴らしながらオフフックを検出する（ＦＳＫ受信は監視しない）
	]
	return		:[
		2:オフフック検出
		3:Ｔ３タイムオーバ
	]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1993/12/13]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	MDM_RxVoiceReq(void)
{
	MESSAGE_t	*MDM_Msg;
	struct Timer10msData_t	t3timer;
	UBYTE	rtn;
	struct GenerateRingData_t ring_data;		/*  1994/9/1 Y.Suzuki */
	UBYTE	timerID_T3_Timer; /* Added by H.Kubo 1997/08/12 */

	tskno_Bell = 0xFFFF;

	/*	ＯＨ検出・呼び出しベル鳴動タスク起動	*/
	/* 以下H8からとって来ました 1994/9/1 Y.Suzuki */
	GenerateRingStartRelayControl();
	ring_data.StartTime		= 0;
	ring_data.SendMBX		= mbxno.MDM_Task;
	ring_data.RingingTel	= ALL_TEL_RINGING;

	cre_tsk(&tskno_Bell, TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );	/** ＯＨ検出・呼び出しベル鳴動タスク起動 */

	/*	Ｔ３タイマ用タイマタスク起動処理	*/
	t3timer.Time = 1200;/* (T3_TIME/10) 実測値短いので伸ばす。 94/11/21 Y.Suzuki	**	１０秒タイマ値設定	*/
	t3timer.SendMBX = mbxno.MDM_Task;	/**	Ｔ３タイマ、メイルボックス設定	*/
	t3timer.ReturnValue = MSG_T3_TIME_OVER;	/**	戻り値設定	*/
	timerID_T3_Timer = 0xff;
	CMN_MultiTimer10msStart(&timerID_T3_Timer, &t3timer);

	/*	メッセージ受信
	** 1.FCOM_TEL1_OFF_HOOK					(7)
	** 2.FCOM_TEL2_OFF_HOOK					(8)
	** 3.FCOM_HOOK_KEY						(9)
	** 4.FCOM_STOP_KEY						(5)
	** 5:MSG_T3_TIME_OVER	:Ｔ３タイムオーバ(13)
	*/
	do {
		rcv_msg(mbxno.MDM_Task, &MDM_Msg);	/**	メッセージ受信	*/
	} while (!((MDM_Msg->Message == FCOM_TEL1_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_TEL2_OFF_HOOK) ||
					(MDM_Msg->Message == FCOM_HOOK_KEY) ||
					(MDM_Msg->Message == FCOM_STOP_KEY) ||
					(MDM_Msg->Message == MSG_T3_TIME_OVER)));

	rtn = (UBYTE)MDM_Msg->Message;	/* 1997/02/24 Y.Murata */

	/*	ＯＨ検出・呼び出しベル鳴動タスク終了	*/
	if (tskno_Bell != 0xFFFF) {
		del_tsk( &tskno_Bell  );	/**	ＯＨ検出・呼び出しベル鳴動タスク終了	*/
	}

	/*	タイマタスク終了	*/
	if (timerID_T3_Timer != 0xff) { /* Ported from ORANGE by H.Kubo 1997/08/12 */
		CMN_MultiTimer10msStop(&timerID_T3_Timer);
	}

	/*	戻り値設定	*/
	/*switch(MDM_Msg->Message) { 1997/02/24 Y.Murata */
	switch(rtn) {
	case FCOM_TEL1_OFF_HOOK:
		rtn = TEL1_OH_DETECT;
		break;
	case FCOM_TEL2_OFF_HOOK:
		rtn = TEL2_OH_DETECT;
		break;
	case FCOM_HOOK_KEY:
		rtn = HOOK_KEY_OH_DETECT;
		break;
	default:
		rtn = T3_TIME_OVER;
	}
	GenerateRingEndRelayControl();/* 94/11/18 Y.Suzuki */
	return (rtn);
}


/*************************************************************************
	module		:[短縮ハンドシェーク]
	function	:[
		1. ＥＣＭ受信のコンフィギュレーションを設定します
		2. ＥＣＭ受信をオープンします
		3. トレーニングを検出します
		4. ＦＳＫ高速信号の受信を行います
		5. ＥＣＭ受信をクローズします
	]
	return		:[
		FSK_RECEIVE		0		受信正常
		FSK_ERROR		1		受信異常
	]
	common		:[
		AttemptRxBaudRate
	]
	condition	:[]
	comment		:[]
	date		:[1994/11/15]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE 	MDM_RxSpeedHandshake(void)
{
	MESSAGE_t	*MDM_Msg;
	struct	Timer10msData_t Timer1;
	struct	Timer10msData_t Timer2;
	struct	Timer10msData_t TimerEqz;
	UBYTE	ret;
	UBYTE	t30_start;
	UBYTE	flgdet;
	UBYTE	loopout;
	UBYTE	timerID_Timer1; /* Added by H.Kubo 1997/08/12 */
	UBYTE	timerID_Timer2; /* Added by H.Kubo 1997/10/03 */
	UBYTE	timerID_TimerEqz; /* Added by H.Kubo 1997/10/03 */

	t30_start = 0;
	flgdet = 0;
	ret = FSK_RECEIVE;

	tskno_ModemStatusCheck = 0xffff;
	tskno_RxFlagDetect = 0xffff;

	timerID_Timer1 = 0xff;
	timerID_Timer2 = 0xff;
	timerID_TimerEqz = 0xff;

	ModemTypeSet(AttemptRxBaudRate);	/**	モデムタイプ・スピード設定	*/
	if (ModemBlock.Type == TYPE_V17 ){	/**	モデムタイプがＶ１７の時	*/
		ModemBlock.Training = TRAINING_LONG;	/**	モデムＩ／Ｆブロックのトレーニング種別をトレーニングロングに設定	*/
	}
	else {	/**	その他	*/
		ModemBlock.Training = TRAINING_SHORT;	/**	モデムＩ／Ｆブロックのトレーニング種別をトレーニングショートに設定	*/
	}
	ModemBlock.RxCheck = RX_CHKONLY;	/**	モデムＩ／Ｆブロックの受信チェックを１回チェックに設定	*/

/* for Debug by O.Kimoto 1998/08/04 */
if (DEBUG_SPIX == 1) {
	MDM_SetIO(POS_CONF, BPS300_V21);
	MDM_SetIO_NewcAfterConf(POS_NEWC,ON, V21_300_NEWC_TIME);

	while ((inp(MDM_REG_0F_PORT) & IO_BIT_FED) || (inp(MDM_REG_0F_PORT) & IO_BIT_RLSD)) {
		wai_tsk(10/10);
	}
	MDM_SetIO(POS_CONF, BPS300_V21);
	MDM_SetIO_NewcAfterConf(POS_NEWC,ON, V21_300_NEWC_TIME);
}

	/*	モデムステータス監視タスク起動	*/
	ModemStatusFlag = 0;	/**	モデムステータス監視フラグをクリア	*/
	ModemWaitStatus = (PHS_STAT_CHECK_SEQ_BIT + PHS_STAT_CHECK_TRDETON);	/**	モデム待ち状態をトレーニングに設定	*/
	cre_tsk(&tskno_ModemStatusCheck, TSK_MDM_MODEMSTATUSCHECKTASK, &mbxno.MDM_TaskSub);	/**	モデムステータス監視タスク起動	*/

#if (0)	/* for Debug by O.kimoto 1998/07/23 */
** 	/* 1997/09/11 Y.Murata
** 	 * フラグ検出は、高速信号を検出してから起動する
** 	*/
** 
** 	/*	フラグ検出タスク起動	*/
** 	cre_tsk(&tskno_RxFlagDetect, TSK_MDM_FLAGDETECTTASK, &mbxno.MDM_TaskSub);	/**	フラグ検出タスク起動	*/
#endif

	/*	タイマタスク１起動	*/
	Timer1.Time = (2000/10);
	Timer1.SendMBX = mbxno.MDM_TaskSub;
	Timer1.ReturnValue = TIME_2SEC_OVER;
	CMN_MultiTimer10msStart(&timerID_Timer1, &Timer1); /* Ported from ORANGE by H.Kubo 1997/08/12 */

	/*	タイマタスク２起動	*/
	Timer2.Time = (10/10);
	Timer2.SendMBX = mbxno.MDM_TaskSub;
	Timer2.ReturnValue = MSG_RX_SPEED_TIME_OVER;
	CMN_MultiTimer10msStart(&timerID_Timer2, &Timer2);

/* for Debug by O.Kimoto 1998/08/04 */
if (DEBUG_SPIX == 0) {
	RxEcmOpen(); /** ＥＣＭ受信オープン	*/ /* argument is deleted by H.Kubo 997/08/18 */
	ModemBlock.Mode = MODE_RX_FSK;
}

	/* for Debug by O.Kimoto 1998/07/23 */
	MDM_SetIO(POS_STRN,OFF);		/* 1997/09/08 Y.Murata */
	MDM_FilterSet(FSK_FILTER);	/* 1998/01/13 DEBUG */

	loopout = 1;	/**	ループ制御フラグ１に設定	*/
    do{
		rcv_msg(mbxno.MDM_TaskSub, &MDM_Msg);	/**	メッセージ受信	*/
		switch (MDM_Msg->Message) {	/**	メッセージ受信内容	*/
		case MSG_ENABLE_MODEM_STATUS:	/**	トレーニング受信	*/

			/* for Debug by O.Kimoto 1998/07/23 */
			ModemBlock.Mode = MODE_RX_FSK;
			
			/* 1997/09/11 Y.Murata
			 * フラグ検出は、高速信号を検出してから起動する
			*/
			/*	フラグ検出タスク起動	*/
			cre_tsk(&tskno_RxFlagDetect, TSK_MDM_FLAGDETECTTASK, &mbxno.MDM_TaskSub);	/**	フラグ検出タスク起動	*/

			if (timerID_Timer1 != 0xff) {
				CMN_MultiTimer10msStop(&timerID_Timer1);
			}

			Timer1.Time = (3000/10);
			Timer1.SendMBX = mbxno.MDM_TaskSub;
			Timer1.ReturnValue = TIME_2SEC_OVER;
			CMN_MultiTimer10msStart(&timerID_Timer1, &Timer1); /* Ported from ORANGE by H.Kubo 1997/08/12 */

			if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
				TimerEqz.Time = (1000/10);
				TimerEqz.SendMBX = mbxno.MDM_TaskSub;
				TimerEqz.ReturnValue = EQZ_TIME_OVER;
				CMN_MultiTimer10msStart(&timerID_TimerEqz, &TimerEqz);
			}
			break;
		case MSG_FLAG_DETECT:	/**	フラグ検出時	*/
			flgdet = 1;	/**	フラグ検出フラグＯＮ	*/
			if (tskno_RxFlagDetect != 0xffff) {
				del_tsk(&tskno_RxFlagDetect);	/**	フラグ検出タスク終了	*/
			}
			if (t30_start == 0) {	/**	Ｔ３０スタートフラグが０の時	*/
				SaveT30TimingData(SYS_T30_START_TIME);	/**	Ｔ３０スタートタイム設定	*/
				t30_start = 1;	/**	Ｔ３０スタートフラグを１に設定	*/
			}

			/* for Debug by O.Kimoto 1998/07/23 */
			/* 1997/09/08 Y.Murata
			 * フラグを検出したと言うことはＲＬＳＤはＯＮになっているのでここでショートトレーニングセット
			*/
			if (ModemBlock.Type	== TYPE_V17) {	/**	モデムタイプ　Ｖ１７設定	*/
				MDM_SetIO(POS_STRN,ON);
			}
			MDM_SetIO(POS_RTDIS,ON);	/* 1998/01/14 debug */

			break;
		case TIME_2SEC_OVER:	/**	２秒タイムアップの時	*/
			ret = FSK_ERROR;	/**	戻り値ＦＳＫエラー設定	*/
			loopout = 0;	/**	ループ制御フラグ０に設定	*/
			break;
		case MSG_RX_SPEED_TIME_OVER:	/**	３秒タイムアップの時	*/
			if (flgdet == 1) {	/**	フラグ検出フラグが１の時	*/
				if (RxEcmRead() == RCV_BLOCK) {	/**	受信フレーム有りの時	*/
					if (MDM_ModemBuffer[ModemControl.ReadPoint][1] == 0x13) {	/**	コントロールフィールドが最終フレームの時	*/
						if ((MDM_ModemBuffer[ModemControl.ReadPoint][2] & 0xfe) == CRP_F) {	/**	ＣＲＰフレームの時	*/
							ret = FSK_ERROR;	/**	戻り値ＦＳＫエラーセット	*/
						}
						else {	/**	その他のフレームの時	*/
							SaveReceivedT30Data();	/**	Ｔ３０にフレームデータ登録	*/
							SaveT30TimingData(SYS_T30_END_TIME);	/**	Ｔ３０にエンドタイム登録	*/
							ret = FSK_RECEIVE;	/**	戻り値ＦＳＫ受信セット	*/
							MDM_NewT30Status = (UBYTE)(MODE_RX_FSK | SPEED_HANDSHAKE_BIT);	/* R288F Internal Monitor By O.Kimoto 1996/05/21 */
						}
						loopout = 0;	/**	ループ制御フラグを０に設定	*/
					}
					else {	/**	コントロールフレームが非最終フレームの時	*/
						NextMdmBufReadPointSetExtRom();
					}
				}
			}
			if (timerID_Timer2 != 0xff) {
				CMN_MultiTimer10msStop(&timerID_Timer2);
			}
			/*	１０ｍｓタイムアップ　タイマタスク起動	*/
			Timer2.Time = (10/10);
			Timer2.SendMBX = mbxno.MDM_TaskSub;
			Timer2.ReturnValue = MSG_RX_SPEED_TIME_OVER;
			CMN_MultiTimer10msStart(&timerID_Timer2, &Timer2);
			break;
		case EQZ_TIME_OVER:	/**	1秒タイムアップの時	*/
			EqualizerHoldOn();	/**	イコライザホールドに設定	*/
			break;
		default:
			break;
		}
	} while (loopout);	/**	ループ監視フラグ１の時	*/

	if (tskno_RxFlagDetect != 0xffff) {
		del_tsk(&tskno_RxFlagDetect);	/**	フラグ検出タスク終了	*/
	}
	if (timerID_Timer1 != 0xff) {
		CMN_MultiTimer10msStop(&timerID_Timer1);
	}
	if (timerID_Timer2 != 0xff) {
		CMN_MultiTimer10msStop(&timerID_Timer2);
	}
	ModemWaitStatus = 0;	/**	モデム待ち状態クリア	*/
	if (tskno_ModemStatusCheck != 0xffff) {
		del_tsk(&tskno_ModemStatusCheck);	/**	モデムステータス監視タスク終了	*/
	}
	ModemStatusFlag = 0;	/**	モデムステータス監視フラグをクリア	*/
	if (timerID_TimerEqz != 0xff) {
		CMN_MultiTimer10msStop(&timerID_TimerEqz);
	}
	RxEcmClose();	/**	ＥＣＭ受信クローズ	*/

	/* For Debug By O.Kimoto 1998/08/05 */
	if (ret == FSK_ERROR) {	/**	戻り値ＦＳＫエラーセット	*/
		MDM_SetIO(POS_EQFZ,OFF);	/**	イコライザホールドに設定	*/
		MDM_SetIO(POS_RTDIS,OFF);	/* 1998/01/14 debug */
	}
	else {
		MDM_SetIO(POS_RTDIS,ON);	/* 1998/01/14 debug */
	}
	return (ret);
}



