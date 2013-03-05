/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/CLOVER                                                */
/*  ファイル名   :                                                           */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1995/12/07                                                */
/*  概  要       : モデムのドライバーに準拠しそうなもの                      */
/*               : 今回はモデムがオートでやるので、ドライバーとの境目が      */
/*               : ようわからんと言うやつ                                    */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"
#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/08 */

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#if (PRO_DPRAM == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
/* #include "\src\atlanta\define\sys_pro.h" */

#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\fcm_def.h"
/*#include "\src\atlanta\define\sys_spd.h"*/
#include "\src\atlanta\define\syst30.h"
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/11 */
#include "\src\atlanta\define\sysrxsw.h"
 #endif
#endif

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\unisw_d.h"

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/07 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
 #endif
#include "\src\atlanta\define\cmn_pro.h"
#endif /* (PRO_MODEM == R288F) */

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\mdm\pana\ext_v\mdmudata.h"
#include "\src\atlanta\mdm\pana\define\mdm_udef.h"
#endif

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* 1999/02/22 by T.Soneoka */
 #if defined(POPLAR_F)
	#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
 #else
	#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
 #endif
#endif

static UWORD		tskno_v8_timeup = 0;		/* タイムアップタスク */
static UWORD		tskno_v8_sectxb = 0;		/* 送信ハンドシェークモニタタスク */
static UWORD		tskno_v8_secrxb = 0;		/* 受信ハンドシェークモニタタスク */
static UWORD		tskno_v8_abcode = 0;		/* ハンドシェークエラー監視タスク */
static UWORD		tskno_v8_stop = 0;			/* ストップＳＷ監視タスク */

CONST	UBYTE 	SW_Debug = 0;		/* debug 1996/03/12 */

/*************************************************************************
	module		:[起呼局初期設定]
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
	date		:[1995/11/25]
	author		:[村田]
*************************************************************************/
void 	V34_SetUpCallProcedure(void)
{
#if (PRO_MODEM == MN195006)
	UBYTE is_hdlc_mode;
	UBYTE i;

	/*--------------------------------------------------
	 * ワーク変数初期化
	*/
	MDM_ClearToSendAbort = FALSE;
	SYS_V8DetectATV25Flag = 0;		/* T.B.D */
	V8_ANSamDetectFlag = 0;			/* T.B.D */

	MDM_SavedTxVectorAddress = 0; /* 2001/12/27 K.Doukuni */

	if (StartUpData.Item != V34_TURNAROUND) {

		/*--------------------------------------------------
		 * 試行可能ＣＭデータ作成
		*/
		FCM_MakeFrameCMandJM();
		for (i = 0; i < TxInformationCategoryByteCount; i++) {
			V34SavedCM_Data[i] = MDM_ModemBuffer[0][i];
		}

		/*--------------------------------------------------
		 * モデムＩ／Ｆブロック設定
		*/
		ModemBlock.Type = TYPE_V8;
		ModemBlock.Mode = MODE_NONE;

		/*--------------------------------------------------
		 * モデム・コンフィグ
		*/
		MDM_SetUpV8Mode(TX_COM_MODE);

		/*--------------------------------------------------
		 * モデムデータ受信許可
		*/
		is_hdlc_mode = FALSE;
		MDM_EnableDataTx(is_hdlc_mode);
	}
#else
	WORD		i;
	UWORD		start_timer;
	UWORD		data;


	/* test 1996/08/27 */
	data = DspRamAccessReadMethod3(0xB47);


	SYS_V8DetectATV25Flag = 0;
	FCM_V8MonitorFlag = 1;
	start_timer = 0;
	MDM_ClearToSendAbort = FALSE;	/* 1996/06/20 */
	V8_ANSamDetectFlag = 0;			/* 1996/08/07 */

	start_timer = SYS_GeneralTimer;			/* 1996/03/12 */
	if (StartUpData.Item == V34_TURNAROUND) {	/** ターンアラウンドポーリング */
		MDM_SetUpTurnaroundModeORG();		/** 起呼局ターンアラウンドポーリング設定 */
	}
	else {
		MDM_SetUpV8Mode();		/** Ｖ８モード設定 */
	}

	FCM_MakeFrameCMandJM();		/** 試行可能ＣＭデータ作成 */
	for (i = 0; i < TxInformationCategoryByteCount; i++) {
		V34SavedCM_Data[i] = MDM_ModemBuffer[0][i];		/* 作成したＣＭをセーブする。*/
	}

	MDM_SetTerminalInformation(StartUpData.Allowed);	/** モデムに端末情報を与える */

	MDM_SetV34DataRate();		/** モデムデータ速度設定 */

	if (StartUpData.Item == V34_TURNAROUND) {	/** ターンアラウンドポーリング */
		while ((UWORD)(SYS_GeneralTimer - start_timer) < 7) {	/* within 70ms DTR ON 1996/03/12 *//*cast by M.Kotani 97/10/08*/
			wai_tsk(1);
		}
		MDM_StartGoTurnaroundModeORG();		/** 起呼局ターンアラウンドポーリング開始 */
	}
	else {
		MDM_StartGoV8Mode();	/** Ｖ８モード開始 */
	}
#endif
}


/*************************************************************************
	module		:[応答局初期設定]
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
	date		:[1995/11/25]
	author		:[村田]
*************************************************************************/
void 	V34_SetUpAnswerProcedure(void)
{
#if (PRO_MODEM == MN195006)

	UBYTE is_hdlc_mode;
	UBYTE i;

	/*--------------------------------------------------
	 * ワーク変数初期化
	*/
	MDM_ClearToSendAbort = FALSE;

	MDM_SavedTxVectorAddress = 0; /* 2001/12/27 K.Doukuni */

	/*--------------------------------------------------
	 * 試行可能ＪＭデータ作成
	*/
	FCM_MakeFrameCMandJM();
	for (i = 0; i < TxInformationCategoryByteCount; i++) {
		V34SavedAvailableJM_Data[i] = MDM_ModemBuffer[0][i];
	}

	/*--------------------------------------------------
	 * モデムＩ／Ｆブロック設定
	*/
	ModemBlock.Type = TYPE_V8;
	ModemBlock.Mode = MODE_NONE;

	/*--------------------------------------------------
	 * モデム・コンフィグ
	*/
	MDM_SetUpV8Mode(RX_COM_MODE);

	/*--------------------------------------------------
	 * モデムデータ受信許可
	*/
	is_hdlc_mode = FALSE;
	MDM_EnableDataRx(is_hdlc_mode);
#else

	WORD		i;
	UWORD		data;

	/* test 1996/08/27 */
	data = DspRamAccessReadMethod3(0xB47);


	FCM_V8MonitorFlag = 1;
	MDM_ClearToSendAbort = FALSE;	/* 1996/06/20 */

	if (StartUpData.Item == V34_TURNAROUND) {	/** ターンアラウンドポーリング */
		MDM_SetUpTurnaroundModeANS();		/** 起呼局ターンアラウンドポーリング設定 */
	}
	else if (StartUpData.Item == V34_STANDARD) {	/** 通常通信 */
		MDM_SetUpV8Mode();		/** Ｖ８モード設定 */
	}
	else {	/* 一回Ｖ８手順を実行したが、再度Ｖ８モードを実行する時 */
			/* ＤＣＳ受信待ちの時にＣＩを検出した時 */
		/* ＣＩ受信の時にＶ８にコンフィグしてるので、ここでは何もしない */
		return;		/* 1996/03/15 */
	}

	FCM_MakeFrameCMandJM();		/** 試行可能ＣＭデータ作成 */
	for (i = 0; i < TxInformationCategoryByteCount; i++) {
		V34SavedAvailableJM_Data[i] = MDM_ModemBuffer[0][i];
	}

	MDM_SetTerminalInformation(StartUpData.Allowed);	/** モデムに端末情報を与える */

	MDM_SetV34DataRate();		/** モデムデータ速度設定 */

	/** L8153-3 Release Note 1.8 Fine tune Selection of 33.6/31.2 By O.Kimoto 1996/10/9 **/
 #if 0 /* この処理があると 26P で ANSam 異常になるので、13P, 20P 対策という条件に変えます。 by H.Kubo 1998/10/01 */
@@	if (SYS_ModemVersion != MDM_L6713_13P) {	/* 1996/10/11 Y.M */
@@		MDM_FinetuneSelection336or312();
@@	}
 #else
	if ((SYS_ModemVersion == MDM_L6713_14P) || SYS_ModemVersion == MDM_L6713_20P) {	/* 1996/10/11 Y.M */
		MDM_FinetuneSelection336or312();
	}
 #endif

/* #if defined(POPLAR_F)  */
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)	/* Add By O.Kimoto 2002/10/15 */
	/* シンボルレートチューニング処理
	** Ap-6713-0010にしたがって、リンク特性に対するシンボルレートの選択範囲を調整します。
	** 調整は機種固有スイッチD:4-4～6と7です。
	** By O.Kimoto 1999/10/18 */
	if (CHK_V34SymbolRateTuningDisable() == 0 ) {
		DspRamAccessWriteMethod1(0x06CC, 0x00, 0x0FB); /* Enable */
		DspRamAccessWriteMethod1(0x0689, CHK_V34SymbolRateTuningValue(), 0x0F0);
	}
	else {
		DspRamAccessWriteMethod1(0x06CC, 0x04, 0x0FB); /* Disable */
	}

 #else

	if (SYS_ModemVersion == MDM_L6713_26P) {
		/* シンボルレートチューニング処理
		** Ap-6713-0010にしたがって、リンク特性に対するシンボルレートの選択範囲を調整します。
		** 調整は機種固有スイッチD:4-4～6と7です。
		** By O.Kimoto 1999/10/18 */
		if (CHK_V34SymbolRateTuningDisable() == 0 ) {
			DspRamAccessWriteMethod1(0x06C1, 0x00, 0x0FB);
			DspRamAccessWriteMethod1(0x06A1, CHK_V34SymbolRateTuningValue(), 0x0F0);
		}
		else {
			DspRamAccessWriteMethod1(0x06C1, 0x04, 0x0FB);
		}
	}
 #endif

	MDM_StartGoV8Mode();		/** Ｖ８モード開始 */
#endif
}

/*************************************************************************
	module		:[Ｖ８モード中のアンサートーン検出タスク]
	function	:[
		1.V8ﾓｰﾄﾞ中(DTR ON)はATV25はｾｯﾄされません
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/12/07]
	author		:[村田]
*************************************************************************/
void  V34_DetectV25AnswerToneTask(void)
{
#if (PRO_MODEM == MN195006)
	MESSAGE_t		msg;
	unsigned long	on_timer;
	unsigned long	off_timer;

	msg.Item = FROM_V34_DETECT_V25TONE;

	/** アンサートーンのＡＮＳａｍを検出します */
	for (on_timer = off_timer = 0;;) {
		if (MDM_V8DetectANSam()) {	/** ＡＮＳａｍ検出 */
			SYS_V8DetectATV25Flag = 0;
			msg.Message = V25_ANSAM_TONE;
			snd_msg(mbxno.FCM_Task, &msg);
			wai_tsk(0xFFFF);
		}
 #if 1 /* このままだと時間はシステム依存 要修正 2001/12/14 K.Doukuni */
		if (MDM_IsCI_Transmit()) { /* CI送出中 */
			if (on_timer > 10) { /* CION期間 2s以下 */
				MDM_RTS_OFF();
				on_timer = 0;
			}
			else {
				on_timer++;
			}
		}
		else {
			if (off_timer > 8) { /* CIOFF期間 0.4s以上2s以下 */
				MDM_RTS_ON();
				off_timer = 0;
			}
			else {
				off_timer++;
			}
		}
 #endif
		wai_tsk(5);		/* 50ms */
	}
#else
	MESSAGE_t		msg;
	unsigned long	on_timer;
	unsigned long	off_timer;

	/*if (!(SYS_MemorySwitch[35] & 0x40)) { 1996/11/05 */
	if (CHK_V34DetectANSam_DuringCI() == 0) {

		msg.Item = FROM_V34_DETECT_V25TONE;

		/** アンサートーンのＡＮＳａｍを検出します */
		while(1) {
			if (MDM_V8DetectANSam()) {	/** ＡＮＳａｍ検出 */
				SYS_V8DetectATV25Flag = 0;
				msg.Message = V25_ANSAM_TONE;
				snd_msg(mbxno.FCM_Task, &msg);
				wai_tsk(0xFFFF);
			}
			wai_tsk(5);		/* 50ms */
		}

	}
	else {
	/* 1996/07/16 Y.M */
		if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {
			/* フィルター1 ＯＮのイベントを待ちます */
			wai_evt(EVT_TONE_FILTER1_ON);
			on_timer = 1;
			off_timer = 0;

			while(1) {
				if (MDM_GetIO(POS_TONEA)) {
					off_timer = 0;
					if (on_timer == 0) {	/* 検出やり直しの時にONがきた */
						on_timer = 1;
					}
				}
				else {
					off_timer++;
					if (off_timer > 10) {	/* 100ms瞬断 */
						on_timer = 0;		/* 検出やり直し */
					}
				}
				if (on_timer) {
					on_timer++;
					if (on_timer > 50) {	/* 500ms ON */
						break;
					}
				}
				if (MDM_V8DetectANSam()) {
					break;
				}
				wai_tsk(1);
			}

			msg.Item = FROM_V34_DETECT_V25TONE;
			SYS_V8DetectATV25Flag = 0;
			msg.Message = V25_ANSAM_TONE;
			snd_msg(mbxno.FCM_Task, &msg);
			wai_tsk(0xFFFF);

		}
		else {
			msg.Item = FROM_V34_DETECT_V25TONE;

			/** アンサートーンのＡＮＳａｍを検出します */
			while(1) {
				if (MDM_V8DetectANSam()) {	/** ＡＮＳａｍ検出 */
					SYS_V8DetectATV25Flag = 0;
					msg.Message = V25_ANSAM_TONE;
					snd_msg(mbxno.FCM_Task, &msg);
					wai_tsk(0xFFFF);
				}
				wai_tsk(5);		/* 50ms */
			}
		}

	}
#endif
}

/*************************************************************************
	module		:[Ｖ８コントロール・タスク]
	function	:[
		1.指定された状態まで達したかどうか、ハンドシェークモニタを監視する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/12/04]
	author		:[村田]
*************************************************************************/
void V34_V8ControlTask(struct FCM_V8ControlData_t *V8ControlData)
{
	MESSAGE_t			send_msg;
	MESSAGE_t			*msg;
	WORD			return_mbxno;
	UWORD			status;		/* ﾊﾝﾄﾞｼｪｰｸｽﾃｰﾀｽ */
	UBYTE	tx_or_rx;	/* 1:TxHandshakeMonitor read  0:RxHandshakeMonitor read */
	UBYTE	loop;

	V8TaskInitial();

	send_msg.Item = FROM_V34_V8CONTROL;
	return_mbxno = V8ControlData->ReturnMbxno;

	switch (V8ControlData->ControlStatus) {
		case CALL_CM_TX:				/* ＣＭ送信中になればＯＫ */
			status = ORG_SENDING_CM;
			tx_or_rx = 1;
			break;
		case CALL_JM_RX:				/* ＪＭを検出すればＯＫ */
			status = ORG_FOUND_JM;
			tx_or_rx = 0;
			break;
		case CALL_CJ_TX:				/* ＣＪ送信中になればＯＫ */
			status = ORG_SENDING_CJ;
			tx_or_rx = 1;
			break;
		case CALL_SILENCE_TX:			/* 無音送信中になればＯＫ */
			status = ORG_SENDING_SHORT_SILENCE;
			tx_or_rx = 1;
			break;
		case ANS_CM_RX:					/* ＣＭ受信と言うことはＣＭを検出すればＯＫ */
			status = ANS_FOUND_CM_LOOKING_FOR_CJ;
			tx_or_rx = 0;
			break;
		case ANS_JM_TX:					/* ＪＭ送信と言う事は、ＪＭ送信中になればＯＫ */
			status = ANS_SENDING_JM;
			tx_or_rx = 1;
			break;
		case ANS_CJ_RX:					/* ＣＪ受信と言う事は、ＣＪを検出すればＯＫ */
			status = ANS_CJ_DETECED;
			tx_or_rx = 0;
			break;
		case ANS_SILENCE_TX:
			status = ANS_SENDING_SHORT_SILENCE;	/* 無音送信と言うことは無音送信中になればＯＫ */
			tx_or_rx = 1;
			break;
		default:
			/* 絶対こない */
			break;
	}


#if (PRO_MODEM == MN195006)
	if (V8ControlData->ControlStatus == ANS_CM_RX) {
		while (1) {
			if (MDM_V8DetectCM()) {
				break;
			}
			wai_tsk(1);
		}
		send_msg.Message = V8_COMPLETE;
		send_msg.SubMessage1 = 0;
		snd_msg(return_mbxno, &send_msg);
		wai_tsk(0xFFFF);
	}
#endif

	/*------------------------------------*/
	/* ＡＢＣＯＤＥチェック・タスクを起動 */
	/*------------------------------------*/
	cre_tsk(&tskno_v8_abcode, TSK_MDM_ABCODE_TASK, &mbxno.FCM_V8Task);

	/*----------------------------------*/
	/* ハンドシェークモニタ・タスク起動 */
	/*----------------------------------*/
	if (tx_or_rx == 1) {
		cre_tsk(&tskno_v8_sectxb, TSK_V34_TXHANDSHAKEMONITORTASK, &mbxno.FCM_V8Task);
	}
	else {
		cre_tsk(&tskno_v8_secrxb, TSK_V34_RXHANDSHAKEMONITORTASK, &mbxno.FCM_V8Task);
	}

	loop = 1;
	while(loop == 1) {
		rcv_msg(mbxno.FCM_V8Task, &msg);
		switch (msg->Item) {
			case FROM_V34_TX_HANDSHAKE_MONITOR:
			case FROM_V34_RX_HANDSHAKE_MONITOR:
				if (msg->Message == 0x0FFF) {
					/* Ｖ８ハンドシェーク中にクリアダウン */
				}
				if (status <= msg->Message) {
					loop = 0;
					send_msg.Message = V8_COMPLETE;
					send_msg.SubMessage1 = 0;
				}
				break;
			case FROM_ABCODE:
				loop = 0;
				send_msg.Message = V8_NG;
				send_msg.SubMessage1 = msg->Message;
				break;
		}
	}

	snd_msg(return_mbxno, &send_msg);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[起呼スタートアップ・フェーズ２]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		－１３ＰのＷｏｒｋａｒｏｕｎｄ対応	By O.Kimoto 1996/10/04
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  V34_CallStartUpPhase2(void)
{
#if (PRO_MODEM == MN195006)
	UBYTE	ret;
	UWORD	timer;	/** By O.Kimoto 1996/08/10 **/

	FaxComPhaseStatus = CALL_PHASE2_1;

	ret = V34_ExecuteStartUp(V34_LINE_PROBING);

	if (ret != V34_PROCEDURE) {
		return(NG);
	}


	FaxComPhaseStatus = CALL_PHASE2_2;
	/*---------------------------------*/
	/** ラインプロービング終了時の処理 */
	/*---------------------------------*/
	if (V34PrimaryChannelDirection == TX_COM_MODE) {	/** 送信時 */
	}
	else {	/** 受信時 */
	}
	return(V34_PROCEDURE);
#else
	UBYTE	ret;
	UWORD	timer;	/** By O.Kimoto 1996/08/10 **/

	FaxComPhaseStatus = CALL_PHASE2_1;

	/*----------------------*/
	/* Initial Polling Test */
	/*----------------------*/
	if (V34PrimaryChannelDirection == RX_COM_MODE) {

#if (0) /** Move here to LINE:582 By O.Kimoto 1996/06/28 **/
*		while (1) {
*			ret = MDM_GetIO(POS_SECTXB);
*			if (ret == 0x05) {
*				MDM_FlipSrcRcp();	/* Polling By O.Kimoto 1996/06/26 */
*				break;
*			}
*			else {
*				wai_tsk(1);
*			}
*		}
#endif

		if (SYS_ModemVersion == MDM_L6713_13P) {
			timer = 0;	/** By O.Kimoto 1996/08/10 **/
			while(1) {
				/** ret = MDM_GetIO(POS_SECTXB); so slow By O.Kimoto 1996/06/28 **/
				ret = inp(MDM_REG_17_PORT);
				if ((ret == 0x2C) || (timer > 2000))  {
					MDM_FlipAnsOrg();	/* Polling By O.Kimoto 1996/06/26 */
					break;
				}
				else {
					wai_oneshot(1);
					timer ++;
				}
			}
			
			timer = 0;	/** By O.Kimoto 1996/08/10 **/
			while (1) {
				/** ret = MDM_GetIO(POS_SECRXB); so slow By O.Kimoto 1996/06/28 **/
				ret = inp(MDM_REG_16_PORT);
				/** if (ret == 0x2F) [ Can not detect SECRXB = 2F By O.Kimoto 1996/08/10 **/
				if ((ret >= 0x2F) || (timer > 2000)) {
					MDM_FlipAnsOrg();	/* Polling By O.Kimoto 1996/06/26 */
					break;
				}
				else {
					wai_oneshot(1);
					timer ++;
				}
			}
		}
	}


	ret = V34_ExecuteStartUp(V34_LINE_PROBING);

	if (ret != V34_PROCEDURE) {
		return(NG);
	}


	FaxComPhaseStatus = CALL_PHASE2_2;
	/*---------------------------------*/
	/** ラインプロービング終了時の処理 */
	/*---------------------------------*/
	if (V34PrimaryChannelDirection == TX_COM_MODE) {	/** 送信時 */
		/** シンボル速度リード */
		V34BaudDataRate = MDM_GetSelectedSymbolRate();
	}
	else {	/** 受信時 */
		/** シンボル速度リード */
		V34BaudDataRate = MDM_GetSelectedSymbolRate();
		MDM_V34ManagementAfterProbing();
	}
	return(V34_PROCEDURE);
#endif
}


/*************************************************************************
	module		:[起呼スタートアップ・フェーズ３]
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
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  V34_CallStartUpPhase3(void)
{
	UBYTE	ret;

	FaxComPhaseStatus = CALL_PHASE3;

	ret = V34_ExecuteStartUp(V34_EQUALIZER_TRAINING);

	return(ret);
}

/*************************************************************************
	module		:[応答スタートアップ・フェーズ２]
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
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  V34_AnswerStartUpPhase2(void)
{
	UBYTE	ret;

	FaxComPhaseStatus = ANS_PHASE2_1;

	ret = V34_ExecuteStartUp(V34_LINE_PROBING);

	if (ret != V34_PROCEDURE) {
		return(NG);
	}

	/*---------------------------------*/
	/** ラインプロービング終了時の処理 */
	/*---------------------------------*/
	FaxComPhaseStatus = ANS_PHASE2_2;

#if (PRO_MODEM == MN195006)
	if (V34PrimaryChannelDirection == TX_COM_MODE) {	/** 送信時 */
	}
	else {	/** 受信時 */
	}
	return(V34_PROCEDURE);
#else
	if (V34PrimaryChannelDirection == TX_COM_MODE) {	/** 送信時 */
		/** シンボル速度リード */
		V34BaudDataRate = MDM_GetSelectedSymbolRate();
	}
	else {	/** 受信時 */
		/** シンボル速度リード */
		V34BaudDataRate = MDM_GetSelectedSymbolRate();
		MDM_V34ManagementAfterProbing();
	}
	return(V34_PROCEDURE);
#endif
}


/*************************************************************************
	module		:[応答スタートアップ・フェーズ３]
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
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  V34_AnswerStartUpPhase3(void)
{
#if (PRO_MODEM == MN195006)
	UBYTE	ret;

	FaxComPhaseStatus = ANS_PHASE3;

	ret = V34_ExecuteStartUp(V34_EQUALIZER_TRAINING);

	return(ret);
#else
	UBYTE	ret;

	FaxComPhaseStatus = ANS_PHASE3;

	if (V34PrimaryChannelDirection == RX_COM_MODE) {
		/*--------------------------------------------*/
		/* 位相ジッタを測定し、最高通信速度を決定する */
		/*--------------------------------------------*/ /* 1996/08/27 Y.M */
		MDM_SetARA_PhaseJitterRate();
	}

	ret = V34_ExecuteStartUp(V34_EQUALIZER_TRAINING);

	return(ret);
#endif
}

/*************************************************************************
	module		:[変調モード解析]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/12/07]
	author		:[村田]
*************************************************************************/
UBYTE  V34_AnalizeModurationMode(UBYTE mode)
{
#if (PRO_MODEM == MN195006)
	UBYTE	ret;
	UBYTE	temp;
	
	ret = V34_PROCEDURE;
	
	if (mode == TX_COM_MODE) {
		/*-----------------------------*/
		/** プライマリチャネル指示判別 */
		/*-----------------------------*/
		if (StartUpData.Direction == TX_COM_MODE) {	/** ＣＭの起呼機能を「TX FAX」で設定している時 */
			if (FCM_CallFunctionData != TRANSMIT_CALL) {	/** ＪＭの起呼機能が「Transmit Facsimile form call station」設定でない */
				ret = NG;
				FaxCompatibleErrorCode = ORIGINATE_DIRECTION_TX_ERROR;
			}
			V34PrimaryChannelDirection = TX_COM_MODE;
		}
		else {	/** ＣＭの起呼機能を「RX FAX」で設定している時 */
			/** ＪＭの起呼機能が「Receive Facsimile at call station」設定でないか、相手機に原稿がない */
			if ((FCM_CallFunctionData != RECEIVE_CALL)  ||  ((V34SavedJM_Data[V8_MODURATION_0_POS] == MODURATION_TAG)
														  && (V34SavedJM_Data[V8_MODURATION_1_POS] == EXTENSION_OCTET)
														  && (V34SavedJM_Data[V8_MODURATION_2_POS] == EXTENSION_OCTET))) {
				ret = NG;
				FaxCompatibleErrorCode = ORIGINATE_DIRECTION_RX_ERROR;
			}
			V34PrimaryChannelDirection = RX_COM_MODE;
		}

		/* T.B.D */
		if (ret != NG) {
			if (MDM_ModemBuffer[V8FrmPos][V8_MODURATION_0_POS] & V34_HALF_DUPLEX) {
			}
			else {
				ret = T30_PROCEDURE;
			}
		}

		if ((ret == NG) && (FaxCompatibleErrorCode == 0)) {
			FaxCompatibleErrorCode = ORIGINATE_MODURATION_ERROR;
		}
	}
	else {
		/*-------------------------------*/
		/** プライマリ・チャネル指示判別 */
		/*-------------------------------*/
		switch (FCM_CallFunctionData) {	/** ＣＭの起呼機能カテゴリ */
		case TRANSMIT_CALL:	/** 起呼局よりＦＡＸ送信 */
			if (StartUpData.Allowed & TX_COM_MODE) {	/** 自局が起呼局よりＦＡＸ送信しても良いか */
				V34PrimaryChannelDirection = RX_COM_MODE;
			}
			else {
				ret = NG;
				FaxCompatibleErrorCode = ANSWER_DIRECTION_TX_ERROR;
				V34PrimaryChannelDirection = TX_COM_MODE;
			}
			break;
		case RECEIVE_CALL:	/** 起呼局がＦＡＸ受信 */
			if (StartUpData.Allowed & RX_COM_MODE) {	/** 自局が起呼局がＦＡＸ受信しても良いか */
				V34PrimaryChannelDirection = TX_COM_MODE;
			}
			else {
				ret = NG;
				FaxCompatibleErrorCode = ANSWER_DIRECTION_RX_ERROR;
				V34PrimaryChannelDirection = RX_COM_MODE;
			}
			break;
		default:
			ret = NG;
			FaxCompatibleErrorCode = DIRECTION_ERROR;
			break;
		}

		if (ret != NG) {
			V34SavedJM_Data[V8_INFIRMATION_POS] = 0xFF;
			V34SavedJM_Data[V8_SYNCHRONIZATION_POS] = 0xE0;
			V34SavedJM_Data[V8_CALL_FUNC_POS] = FCM_CallFunctionData;

			V34SavedJM_Data[V8_MODURATION_0_POS]
			 = (MDM_ModemBuffer[V8FrmPos][V8_MODURATION_0_POS] & V34SavedAvailableJM_Data[V8_MODURATION_0_POS]);

			V34SavedJM_Data[V8_MODURATION_1_POS]
			 = (MDM_ModemBuffer[V8FrmPos][V8_MODURATION_1_POS] & V34SavedAvailableJM_Data[V8_MODURATION_1_POS]);

			V34SavedJM_Data[V8_MODURATION_2_POS]
			 = (MDM_ModemBuffer[V8FrmPos][V8_MODURATION_2_POS] & V34SavedAvailableJM_Data[V8_MODURATION_2_POS]);

			if ((V34SavedJM_Data[V8_MODURATION_0_POS] & 0x0F) == MODURATION_TAG) {
				if (V34SavedJM_Data[V8_MODURATION_0_POS] & V34_HALF_DUPLEX) {
				}
				else {
					ret = T30_PROCEDURE;
				}

				if ((V34SavedJM_Data[V8_MODURATION_1_POS] & 0x38)== EXTENSION_OCTET) {
					if (V34SavedJM_Data[V8_MODURATION_1_POS] & ~0x38) {
					}
					else {
						ret = NG;
					}
				}
				else {
					ret = NG;
				}
			}
		}
		else {	/* プライマリ指示不一致 */
#if 0 /* どっちでもいい気もしますが 2002/01/09 K.Doukuni */
//			V34SavedJM_Data[V8_CALL_FUNC_POS] = TRANSMIT_CALL;
#else
			V34SavedJM_Data[V8_CALL_FUNC_POS] = FCM_CallFunctionData;
#endif
			V34SavedJM_Data[V8_MODURATION_0_POS] = MODURATION_TAG;
			V34SavedJM_Data[V8_MODURATION_1_POS] = EXTENSION_OCTET;
			V34SavedJM_Data[V8_MODURATION_2_POS] = EXTENSION_OCTET;
		}


		if ((ret == NG) && (FaxCompatibleErrorCode == 0)) {
			FaxCompatibleErrorCode = ANSWER_MODURATION_ERROR;
		}
	}
	
	return(ret);
#else
	UBYTE	ret;
	UBYTE	temp;
	UWORD	timer;	/** By O.Kimoto 1996/08/10 **/

	V8ConfigMode = MDM_GetIO(POS_CONF);

	switch (V8ConfigMode) {
		case BPS33600_V34:
		case BPS31200_V34:
		case BPS28800_V34:
		case BPS26400_V34:
		case BPS24000_V34:
		case BPS21600_V34:
		case BPS19200_V34:
		case BPS16800_V34:
		case BPS14400_V34:
		case BPS12000_V34:
		case BPS9600_V34:
		case BPS7200_V34:
		case BPS4800_V34:
		case BPS2400_V34:
			ret = V34_PROCEDURE;
			break;

		case BPS14400_V33:
		case BPS12000_V33:
		case BPS9600_V33:
		case BPS7200_V33:
		case BPS14400_V17:
		case BPS12000_V17:
		case BPS9600_V17:
		case BPS7200_V17:
		case BPS9600_V29:
		case BPS7200_V29:
		case BPS4800_V29:
		case BPS4800_V27:
		case BPS2400_V27:
		case BPS300_V21:		/* Channel 2 */
			ret = T30_PROCEDURE;
			break;
		default:
			ret = NG;
			break;
	}

	if (mode == TX_COM_MODE) {
		/*-----------------------------*/
		/** プライマリチャネル指示判別 */
		/*-----------------------------*/
		if (StartUpData.Direction == TX_COM_MODE) {	/** ＣＭの起呼機能を「TX FAX」で設定している時 */
			if (FCM_CallFunctionData != TRANSMIT_CALL) {	/** ＪＭの起呼機能が「Transmit Facsimile form call station」設定でない */
				FaxCompatibleErrorCode = ORIGINATE_DIRECTION_TX_ERROR;
			}
			V34PrimaryChannelDirection = TX_COM_MODE;
		}
		else {	/** ＣＭの起呼機能を「RX FAX」で設定している時 */
			if (FCM_CallFunctionData != RECEIVE_CALL) {	/** ＪＭの起呼機能が「Receive Facsimile at call station」設定でない */
				FaxCompatibleErrorCode = ORIGINATE_DIRECTION_RX_ERROR;
			}
			V34PrimaryChannelDirection = RX_COM_MODE;
			/** MDM_SetAnswerMode(); No Need By Mr.Palm 1996/06/27 **/

			if (ret != NG) {	/* add if 1996/08/03 Y.Murata */
				timer = 0;	/** By O.Kimoto 1996/08/10 **/
				while (1) {
					temp = inp(MDM_REG_17_PORT);
					if ((temp == 0x20) || (timer > (UWORD)(2000/10))){
						MDM_FlipSrcRcp();	/* Polling By O.Kimoto 1996/06/26 */
						break;
					}
					else {
						wai_tsk(1);
						timer ++;
					}
				}
			}

		}
		if ((ret == NG) && (FaxCompatibleErrorCode == 0)) {
			FaxCompatibleErrorCode = ORIGINATE_MODURATION_ERROR;
		}
	}
	else {
		/*-------------------------------*/
		/** プライマリ・チャネル指示判別 */
		/*-------------------------------*/
		switch (FCM_CallFunctionData) {	/** ＣＭの起呼機能カテゴリ */

			case TRANSMIT_CALL:	/** 起呼局よりＦＡＸ送信 */
				if (StartUpData.Allowed & TX_COM_MODE) {	/** 自局が起呼局よりＦＡＸ送信しても良いか */
					/*V34PrimaryChannelDirection = TX_COM_MODE; 1996/02/10 */
					V34PrimaryChannelDirection = RX_COM_MODE;
				}
				else {
					FaxCompatibleErrorCode = ANSWER_DIRECTION_TX_ERROR;
					V34PrimaryChannelDirection = TX_COM_MODE;	/* 1996/09/13 */
				}
				break;
			case RECEIVE_CALL:	/** 起呼局がＦＡＸ受信 */
				if (StartUpData.Allowed & RX_COM_MODE) {	/** 自局が起呼局がＦＡＸ受信しても良いか */
					/*V34PrimaryChannelDirection = RX_COM_MODE; 1996/02/10 */
					V34PrimaryChannelDirection = TX_COM_MODE;
					/** MDM_SetOriginateMode(); No Need By Mr.Palm 1996/06/27 **/

					timer = 0;
					while (1) {
						temp = inp(MDM_REG_16_PORT);
						if ((temp == 0x20) || (timer > (UWORD)(2000/10))) {
							MDM_FlipSrcRcp();	/* Polling By O.Kimoto 1996/06/26 */
							break;
						}
						else {
							wai_tsk(1);
							timer ++;
						}
					}

				}
				else {
					FaxCompatibleErrorCode = ANSWER_DIRECTION_RX_ERROR;
					V34PrimaryChannelDirection = RX_COM_MODE;	/* 1996/09/13 */
				}
				break;
			default:
				FaxCompatibleErrorCode = DIRECTION_ERROR;
				break;
		}
		if ((ret == NG) && (FaxCompatibleErrorCode == 0)) {
			FaxCompatibleErrorCode = ANSWER_MODURATION_ERROR;
		}
	}

	return(ret);
#endif
}


/*************************************************************************
	module		:[Ｖ３４スタートアップ処理実行]
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
	date		:[1995/12/08]
	author		:[村田]
*************************************************************************/
UBYTE  V34_ExecuteStartUp(UWORD Status)
{
#if (PRO_MODEM == MN195006)
	UBYTE	loop;
	MESSAGE_t			*msg;
	UBYTE	value;

	V8TaskInitial();

	if (Status == V34_LINE_PROBING) {
		Status = 0x43;	/* T.B.D */
	}
	else {
		Status = 0x56;	/* T.B.D */
	}

	/*------------------------------------*/
	/* ＡＢＣＯＤＥチェック・タスクを起動 */
	/*------------------------------------*/
	cre_tsk(&tskno_v8_abcode, TSK_MDM_ABCODE_TASK, &mbxno.FCM_Task); /* T.B.D. 現状は空 */
	/*------------------------------------*/
	/* ハンドシェークモニタ監視タスク起動 */
	/*------------------------------------*/
	cre_tsk(&tskno_v8_secrxb, TSK_V34_RXHANDSHAKEMONITORTASK, &mbxno.FCM_Task);
	/*-------------------------------------------*/
	/** 異常処理のためにタイムアップタスクを起動 */
	/*-------------------------------------------*/
	FCM_TimeUp.Time			= 3000;			/* 30秒 */
	FCM_TimeUp.SendMBX		= mbxno.FCM_Task;
	FCM_TimeUp.ReturnValue	= FCM_TIME_UP;	/* 0x00FE */
	cre_tsk(&tskno_v8_timeup, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);
	/*------------------*/
	/*  ｽﾄｯﾌﾟｷｰ検出ﾀｽｸ	*/
	/*------------------*/
	if (tskno_v8_stop == 0xFFFF) {	/* 1996/08/27 */
		cre_tsk(&tskno_v8_stop, TSK_ATD_CHECKSTOPTASK, 0);
	}

	loop = 1;
	while (loop) {
		rcv_msg(mbxno.FCM_Task, &msg);
		switch (msg->Item) {
			case FROM_V34_RX_HANDSHAKE_MONITOR:
				if (Status <= msg->Message) {
					loop = 0;
					value = V34_PROCEDURE;
				}
				break;
			case FROM_ABCODE:
				V34ErrorCode = (UBYTE)msg->Message;
				loop = 0;
				value = NG;
				break;
			default:
				loop = 0;
				value = NG;
				break;
		}
	}
	V8TaskDelete();

	return(value);
#else
	UBYTE	loop;
	MESSAGE_t			*msg;
	UBYTE	value;

	V8TaskInitial();

	if (Status == V34_LINE_PROBING) {
		Status = RX_PHASE3;
	}
	else {
		Status = RX_PHASE4;
	}

#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* ARCビットを立てる処理をMDM_V34DataRate から移動。  by H.Kubo 1998/10/02 */
	/* Release-2 Known Issues.#2.の情報によりテスト的に入れます。 by O.Kimoto 1996/03/28 */
	/* ARC/EARC ﾋﾞｯﾄをｾｯﾄものでｾｯﾄします 1996/04/18 Y.M */
	if (CHK_V34ARA_AlgorithmEnable()) {
		MDM_SetIO(POS_EARC,ON);
		MDM_SetIO(POS_ARC,ON);		/* Automatic Rate Change Enable */
	}
	else {
		MDM_SetIO(POS_EARC,OFF);
		MDM_SetIO(POS_ARC,OFF);		/* Automatic Rate Change Enable */
	}
#endif

	/*------------------------------------*/
	/* ＡＢＣＯＤＥチェック・タスクを起動 */
	/*------------------------------------*/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
	cre_tsk(&tskno_v8_abcode, TSK_MDM_ABCODE_TASK, &mbxno.FCM_V34Task);
#else
	cre_tsk(&tskno_v8_abcode, TSK_MDM_ABCODE_TASK, &mbxno.FCM_Task);
#endif
	/*------------------------------------*/
	/* ハンドシェークモニタ監視タスク起動 */
	/*------------------------------------*/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
	cre_tsk(&tskno_v8_secrxb, TSK_V34_RXHANDSHAKEMONITORTASK, &mbxno.FCM_V34Task);
#else
	cre_tsk(&tskno_v8_secrxb, TSK_V34_RXHANDSHAKEMONITORTASK, &mbxno.FCM_Task);
#endif
	/*-------------------------------------------*/
	/** 異常処理のためにタイムアップタスクを起動 */
	/*-------------------------------------------*/
	FCM_TimeUp.Time			= 3000;			/* 30秒 */
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
	FCM_TimeUp.SendMBX		= mbxno.FCM_V34Task;
#else
	FCM_TimeUp.SendMBX		= mbxno.FCM_Task;
#endif
	FCM_TimeUp.ReturnValue	= FCM_TIME_UP;	/* 0x00FE */
	cre_tsk(&tskno_v8_timeup, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);
	/*------------------*/
	/*ｽﾄｯﾌﾟｷｰ検出ﾀｽｸ	*/
	/*------------------*/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
	if ((AttemptRxModeSwitch == SYS_TEL_FAX_READY)
	 || (AttemptRxModeSwitch == SYS_FAX_TEL_READY )
	 || (AttemptRxModeSwitch == SYS_ANS_FAX_READY)) {	/* for NTT */
		;
	}
	else {
		if (tskno_v8_stop == 0xFFFF) {	/* 1996/08/27 */
			cre_tsk(&tskno_v8_stop, TSK_ATD_CHECKSTOPTASK, 0);
		}
	}
#else
	if (tskno_v8_stop == 0xFFFF) {	/* 1996/08/27 */
		cre_tsk(&tskno_v8_stop, TSK_ATD_CHECKSTOPTASK, 0);
	}
#endif

	loop = 1;
	while (loop) {
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
		rcv_msg(mbxno.FCM_V34Task, &msg);
#else
		rcv_msg(mbxno.FCM_Task, &msg);
#endif
		switch (msg->Item) {
			case FROM_V34_RX_HANDSHAKE_MONITOR:
				if (Status <= msg->Message) {
					loop = 0;
					value = V34_PROCEDURE;
				}
				break;
			case FROM_ABCODE:
				V34ErrorCode = (UBYTE)msg->Message;
				loop = 0;
				value = NG;
				break;
			default:
				loop = 0;
				value = NG;
				break;
		}
	}
	V8TaskDelete();

	return(value);
#endif
}

/*************************************************************************
	module		:[ＣＩ送信]
	function	:[
		1.ＣＩ送信設定であればＣＩ送信処理を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/12/08]
	author		:[村田]
*************************************************************************/
void  V34_TransmitCIinV8Mode(void)
{
	if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {	/** ＣＩ送信設定である */
		MDM_V8TransmitCI();			/** ＣＩフレーム送信 */

		SaveT30TimingData(SYS_T30_START_TIME);
		SaveT30Data(SYS_T30_TX_CI, &V34SavedCM_Data[0], 0);
	}
}

/*************************************************************************
	module		:[ＣＩ送信停止]
	function	:[
		1.ＣＩ送信中であればＣＩを停止する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/12/08]
	author		:[村田]
*************************************************************************/
void  V34_StopCIinV8Mode(void)
{
	if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {	/** ＣＩ送信設定である */
		MDM_V8StopCI();					/** ＣＩを３フレーム送出して停止 */
	}
}


/*************************************************************************
	module		:[ハンドシェーク状態のチェックを行う　Transmitter Handshake Phase]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	ハンドシェーク状態
				Originate Mode					Answer Mode
		0x00	Phase1	Pausing 400ms			Sending ANSam
		0x01	Phase1	Sending CI				Sending JM
		0x02	Phase1	Sending Silence			Sending Silence
		0x03	Phase1	Sending CM
		0x04	Phase1	Sending CJ
		0x05	Phase1	Sending Silence
		0x20	Phase2
		0x40	Phase3
		0x60	Phase4
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  V34_TxHandshakeMonitorTask(WORD *return_mbxno)
{

#if (PRO_MODEM == MN195006)

	MESSAGE_t		msg;
	UBYTE bkup_status;
	UBYTE current_status;

	bkup_status = 0;
	current_status = 0;

	while(1) {
		DEBUG_ModemStatus = (UWORD)MDMD_GetRES_MDSEQSTS();
		current_status = DEBUG_ModemStatus;

		if (current_status != bkup_status) {
			msg.Item = FROM_V34_TX_HANDSHAKE_MONITOR;
			msg.Message = (UWORD)current_status;
			snd_msg(*return_mbxno, &msg);
			bkup_status = current_status;
		}
		wai_tsk(1);
	}

#else

	MESSAGE_t		msg;
	UBYTE bkup_sectxb;
	UBYTE current_sectxb;

	bkup_sectxb = 0;
	current_sectxb = 0;

	while(1) {
		current_sectxb = MDM_GetIO(POS_SECTXB);

		/*---------------------*/
		/* V8 Octet Monitoring */
		/*---------------------*/
		if (((current_sectxb & 0xE0) == 0x00) && (FCM_V8MonitorFlag == 1)) {/* V8ﾓｰﾄﾞ中(Phase1) */
			if (MDM_RxSize[0] < (MODEM_BUFFER_LENGTH * 2)) {		/* MAX ﾓﾃﾞﾑﾊﾞｯﾌｧ2本(余裕をもって) */
				if (MDM_GetIO(POS_RDBF)) {
					MDM_ModemBuffer[0][MDM_RxSize[0]] = MDM_GetIO(POS_RBUFFER);
					MDM_SetIO(POS_RDBF, OFF);
					MDM_RxSize[0]++;
					if (MDM_GetIO(POS_OE)) {
						MDM_SetIO(POS_OE,OFF);
					}
				}

			}
		}

		if (current_sectxb != bkup_sectxb) {
			msg.Item = FROM_V34_TX_HANDSHAKE_MONITOR;
			msg.Message = (UWORD)current_sectxb;
			snd_msg(*return_mbxno, &msg);
			bkup_sectxb = current_sectxb;
		}

		if (MDM_GetIO(POS_CONF) == V8_CLEARDOWN) {	/** Ｖ８クリアダウン */
			msg.Message = 0x0FFF;			/** 強引にフェーズを進める */
			snd_msg(*return_mbxno, &msg);
		}
		wai_tsk(1);
	}
#endif
}

/*************************************************************************
	module		:[ハンドシェーク状態のチェックを行う　Receiver Handshake Phase]
	function	:[
		1.任意のハンドシェーク状態に達したかどうかチェックする。
	]
	return		:[
					1: 指定したハンドシェーク中又は、終わっている
					0: 指定したハンドシェークまで、まだ達してない
	]
	common		:[]
	condition	:[]
	comment		:[
	ハンドシェーク状態
				Originate Mode							Answer Mode
		0x00	Phase1	Looking for ANSam				Looking for CI or CM
		0x01	Phase1	Found ANSam,looking for JM		Found CI,looking for CM
		0x02	Phase1	Found JM						Found CM,looking for CJ
		0x03	Phase1									CJ Detected
		0x20	Phase2
		0x40	Phase3
		0x60	Phase4
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[]
	date		:[]
	author		:[]
*************************************************************************/
void  V34_RxHandshakeMonitorTask(WORD *return_mbxno)
{
#if (PRO_MODEM == MN195006)
	MESSAGE_t		msg;
	UBYTE bkup_status;
	UBYTE current_status;

	bkup_status = 0;
	current_status = 0;

	while(1) {
		DEBUG_ModemStatus = (UWORD)MDMD_GetRES_MDSEQSTS();
		current_status = DEBUG_ModemStatus;

		if (current_status != bkup_status) {
			msg.Item = FROM_V34_RX_HANDSHAKE_MONITOR;
			msg.Message = (UWORD)current_status;
			snd_msg(*return_mbxno, &msg);
			bkup_status = current_status;
		}
		wai_tsk(1);
	}
#else
	MESSAGE_t		msg;
	UBYTE bkup_secrxb;
	UBYTE current_secrxb;

	bkup_secrxb = 0;
	current_secrxb = 0;

	while(1) {
		current_secrxb = MDM_GetIO(POS_SECRXB);

	/* Monitot Test */
		if ((current_secrxb & 0xE0) == 0x00) {
			if (MDM_RxSize[0] < MODEM_BUFFER_LENGTH) {
				if (MDM_GetIO(POS_RDBF)) {
					MDM_ModemBuffer[0][MDM_RxSize[0]] = MDM_GetIO(POS_RBUFFER);
					MDM_SetIO(POS_RDBF, OFF);
					MDM_RxSize[0]++;
				}
			}
		}

		if (current_secrxb != bkup_secrxb) {
			msg.Item = FROM_V34_RX_HANDSHAKE_MONITOR;
			msg.Message = (UWORD)current_secrxb;
			snd_msg(*return_mbxno, &msg);
			bkup_secrxb = current_secrxb;
		}

		if (MDM_GetIO(POS_CONF) == V8_CLEARDOWN) {	/** Ｖ８クリアダウン */
			msg.Message = 0x0FFF;			/** 強引にフェーズを進める */
			snd_msg(*return_mbxno, &msg);
		}

		wai_tsk(1);
	}
#endif
}


/*************************************************************************
	module		:[Ｖ８コントロールタスク終了処理]
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
	date		:[1995/12/13]
	author		:[村田]
*************************************************************************/
void  V34_V8ControlTaskExit(void)
{
	if (tskno_v8_timeup != 0xFFFF) {
		del_tsk(&tskno_v8_timeup);		/* タイムアップタスク */
	}
	if (tskno_v8_sectxb != 0xFFFF) {
		del_tsk(&tskno_v8_sectxb);		/* 送信ハンドシェークモニタタスク */
	}
	if (tskno_v8_secrxb != 0xFFFF) {
		del_tsk(&tskno_v8_secrxb);		/* 受信ハンドシェークモニタタスク */
	}
	if (tskno_v8_abcode != 0xFFFF) {
		del_tsk(&tskno_v8_abcode);		/* ハンドシェークエラー監視タスク */
	}
	if (tskno_v8_stop != 0xFFFF) {
		del_tsk(&tskno_v8_stop);		/* ストップＳＷ監視タスク */ /* 1996/08/27 */
	}
	exi_tsk();
}

/*------------------------------*/
/* タスクＩＤ格納アドレス初期化 */
/*------------------------------*/
#if (PRO_MODEM == MN195006)
void V8TaskInitial(void)
#else
void near V8TaskInitial(void)
#endif
{
	tskno_v8_timeup = 0xFFFF;		/* タイムアップタスク */
	tskno_v8_sectxb = 0xFFFF;		/* 送信ハンドシェークモニタタスク */
	tskno_v8_secrxb = 0xFFFF;		/* 受信ハンドシェークモニタタスク */
	tskno_v8_abcode = 0xFFFF;		/* ハンドシェークエラー監視タスク */
	tskno_v8_stop   = 0xFFFF;		/* ストップＳＷ監視タスク */ /* 1996/08/27 */
}

/*------------*/
/* タスク削除 */
/*------------*/
#if (PRO_MODEM == MN195006)
void V8TaskDelete(void)
#else
void near V8TaskDelete(void)
#endif
{
	if (tskno_v8_timeup != 0xFFFF) {
		del_tsk(&tskno_v8_timeup);		/* タイムアップタスク */
	}
	if (tskno_v8_sectxb != 0xFFFF) {
		del_tsk(&tskno_v8_sectxb);		/* 送信ハンドシェークモニタタスク */
	}
	if (tskno_v8_secrxb != 0xFFFF) {
		del_tsk(&tskno_v8_secrxb);		/* 受信ハンドシェークモニタタスク */
	}
	if (tskno_v8_abcode != 0xFFFF) {
		del_tsk(&tskno_v8_abcode);		/* ハンドシェークエラー監視タスク */
	}
	if (tskno_v8_stop != 0xFFFF) {
		del_tsk(&tskno_v8_stop);		/* ストップＳＷ監視タスク */ /* 1996/08/27 */
	}
}


/*************************************************************************
	module		:[Ｖ８から通常Ｔ３０への移行処理（桐＋）]
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
	date		:[1996/03/12]
	author		:[村田]
*************************************************************************/
void FCM_CommunicationV8toT30(void)
{

	/* 1997/01/28 Y.Murata
	 * Ｖ３４手動のパスで交信性が非常に悪い、全フレームエラーする
	 * 原因不明なので、とりあえずユニークＳＷで禁止する
	*/
	if (CHK_V34ManualProcedureEnable()) {	/* UNISW D6:0 */
	}
	else {
		if ((SYS_FaxComType == SYS_COMMAND_EXECUTE) || (SYS_FaxComType == SYS_MANUAL_TX)) {	/* 送信の時はやめる 1997/02/06 */
			SYS_DataSignalingRate &= 0xFFFE;
		}
	}
}


/*************************************************************************
	module		:[Ｖ８モード中のCI検出タスク]
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
	date		:[1996/03/14]
	author		:[村田]
*************************************************************************/
void  V34_DetectV8CITask(void)
{
#if (PRO_MODEM == MN195006)
	MESSAGE_t		msg;

	unsigned long	on_timer;
	unsigned long	off_timer;
	UBYTE	ret;
	UBYTE	ret2;
	
	if (CHK_V34DetectCIforMGCS() == 0) { /* 松下対策なし？ */
		msg.Item = FROM_V34_DETECT_V8CI;
		while(1) {
			if (MDM_V8DetectCI()) {
				break;
			}
			wai_tsk(5);		/* 50ms */
		}
 #if 0
//		ret2 = DspRamAccessReadMethod1(0x300);	/* DSP RAM でANSam送出中かﾁｪｯｸ */
//		if (ret2 & 0x01) {
//		}
//		else {
//			MDM_SetIO(POS_DTR, OFF);
 #endif
			MDM_SetToneDetectModeExit();
			StartUpData.Item = V34_STANDARD;
			V34_SetUpAnswerProcedure();
			StartUpData.Item = V34_MANUAL;
 #if 0
//		}
 #endif
		msg.Item = FROM_V34_DETECT_V8CI;
		msg.Message = V8_CI_DETECT;
		snd_msg(mbxno.FCM_Task, &msg);
		wai_tsk(0xFFFF);
	}
 #if 0 /* 2001/12/19 とりあえず一旦外す */
//	else {　/* 松下対策あり？ */
//		/* フィルター1 ＯＮのイベントを待ちます */
//		wai_evt(EVT_TONE_FILTER1_ON);
//		on_timer = 1;
//		off_timer = 0;
//		
//		while(1) {
//			if (MDM_GetIO(POS_TONEA)) {
//				off_timer = 0;
//				if (on_timer == 0) {	/* 検出やり直しの時にONがきた */
//					on_timer = 1;
//				}
//			}
//			else {
//				off_timer++;
//				if (off_timer > 10) {	/* 100ms瞬断 */
//					on_timer = 0;		/* 検出やり直し */
//				}
//			}
//			if (on_timer) {
//				on_timer++;
//				if (on_timer > 25) {	/* 250ms ON */
//					break;
//				}
//			}
//			wai_tsk(1);
//		}
//		
//		ret = MDM_V8DetectCI();		/* DSP RAM でCI検出したかﾁｪｯｸ */
//		
//		ret2 = DspRamAccessReadMethod1(0x300);	/* DSP RAM でANSam送出中かﾁｪｯｸ */
//		if (ret2 & 0x01) {
//		}
//		else {
//			MDM_SetIO(POS_DTR, OFF);
//			StartUpData.Item = V34_STANDARD;
//			V34_SetUpAnswerProcedure();
//			StartUpData.Item = V34_MANUAL;
//		}
//		msg.Item = FROM_V34_DETECT_V8CI;
//		msg.Message = V8_CI_DETECT;
//		snd_msg(mbxno.FCM_Task, &msg);
//		wai_tsk(0xFFFF);
//	}
 #endif
#else
	MESSAGE_t		msg;

	unsigned long	on_timer;
	unsigned long	off_timer;
	UBYTE	ret;
	UBYTE	ret2;

	/*if (!(SYS_MemorySwitch[34] & 0x80)) { 1996/11/05 */
	if (CHK_V34DetectCIforMGCS() == 0) {

	msg.Item = FROM_V34_DETECT_V8CI;
	while(1) {
		if (MDM_V8DetectCI()) {
			msg.Message = V8_CI_DETECT;
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
			snd_msg(mbxno.FCM_V34Task, &msg);
#else
			snd_msg(mbxno.FCM_Task, &msg);
#endif
			wai_tsk(0xFFFF);
		}
		wai_tsk(5);		/* 50ms */
	}

	}
	else {	/* else SYS_MemorySwitch[34] & 0x80 */

	/* Ｖ８中にＣＩ（V21_L)をフィルターで検出 松下のＣＩ対策用 1996/07/16 Y.M */

	/* フィルター1 ＯＮのイベントを待ちます */
	wai_evt(EVT_TONE_FILTER1_ON);
	on_timer = 1;
	off_timer = 0;

	while(1) {
		if (MDM_GetIO(POS_TONEA)) {
			off_timer = 0;
			if (on_timer == 0) {	/* 検出やり直しの時にONがきた */
				on_timer = 1;
			}
		}
		else {
			off_timer++;
			if (off_timer > 10) {	/* 100ms瞬断 */
				on_timer = 0;		/* 検出やり直し */
			}
		}
		if (on_timer) {
			on_timer++;
			if (on_timer > 25) {	/* 250ms ON */
				break;
			}
		}
		wai_tsk(1);
	}

	ret = MDM_V8DetectCI();		/* DSP RAM でCI検出したかﾁｪｯｸ */

	ret2 = DspRamAccessReadMethod1(0x300);	/* DSP RAM でANSam送出中かﾁｪｯｸ */
	if (ret2 & 0x01) {
	}
	else {
		MDM_SetIO(POS_DTR, OFF);
		StartUpData.Item = V34_STANDARD;
		V34_SetUpAnswerProcedure();
		StartUpData.Item = V34_MANUAL;
	}
	msg.Item = FROM_V34_DETECT_V8CI;
	msg.Message = V8_CI_DETECT;
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Mod. by J.Kishida 2002/09/09 */
	snd_msg(mbxno.FCM_V34Task, &msg);
#else
	snd_msg(mbxno.FCM_Task, &msg);
#endif
	wai_tsk(0xFFFF);


	}	/* End of SYS_MemorySwitch[34] & 0x80 */
#endif
}

#endif /* (PRO_TX_SPEED == V34) */
