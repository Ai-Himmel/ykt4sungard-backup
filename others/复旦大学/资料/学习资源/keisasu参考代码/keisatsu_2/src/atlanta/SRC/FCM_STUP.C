/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/CLOVER                                                */
/*  ファイル名   : FCM_STUP.C                                                */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1995/10/27                                                */
/*  概  要       : Ｖ８／Ｖ３４スタートアップモジュール                      */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*               : 1996/07/12 CM送信にﾀｲﾑｵｰﾊﾞｰを設け、ﾀｲﾑｵｰﾊﾞｰ時はT30へ移行  */
/*               : 1997/08/11 POPLAR_H へ移植 by H.Kubo                      */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\uni_pro.h"
/* #include "\src\atlanta\define\mems_pro.h" */

#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\fcm_def.h"
/* #include "\src\atlanta\define\sys_spd.h" */
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\atd_def.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
 #endif
#include "\src\atlanta\define\timer10.h"	/* by O.Kimoto 1998/04/14 */
#endif /* (PRO_MODEM == R288F) */

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#include "\src\atlanta\define\timer10.h"	/* by O.Kimoto 1998/04/14 */
#include "\src\atlanta\mdm\mn195006\define\mmd_pro.h"
#include "\src\atlanta\mdm\mn195006\define\mmd_def.h"
#endif



static UWORD		tskno_timeup = 0;		/* タイムアップタスク */
static UWORD		tskno_anstone = 0;		/* アンサートーン検出タスク */
static UWORD		tskno_v21ch2 = 0;		/* Ｖ２１チャンネル２フラグ検出タスク */
static UWORD		tskno_v8control = 0;	/* Ｖ８コントロールタスク */
static UWORD		tskno_timeup2 = 0;		/* タイムアップタスク *//* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/14 */

/*************************************************************************
	module		:[Ｖ８スタートアップ起呼処理]
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
UBYTE 	FCM_CallStartUpProcedure(void)
{
	UBYTE	ret_value;
	ret_value = 0;

	FaxComPhaseStatus = CALL_PHASE1_1;
	V34_SetUpCallProcedure();		/** Ｖ８初期設定 */

	/*--------------------*/
	/* スタートアップ処理 */
	/*--------------------*/
	ret_value = FCM_CallStartUpPhase1();	/** Ｖ８手順実行 ANS CM JM CJ 無音*/

	if (ret_value == V34_PROCEDURE) {	/** Ｖ３４半二重モードでＶ８モード成立 */

		ret_value = V34_CallStartUpPhase2();	/** プロービング処理 */

		if (ret_value == V34_PROCEDURE) {	/** プロービング終了 */
			ret_value = V34_CallStartUpPhase3();	/** 等化器トレーニング */

			if (ret_value == V34_PROCEDURE) {	/** 等化器トレーニング終了  */
				FaxComPhaseStatus = CALL_PHASE4;
#if (PRO_MODEM == MN195006)
				if (StartUpData.Item == V34_TURNAROUND) {
					MDMD_SetControlChReturnMode(CCHRETMD_PC_START); /* コントロールチャネルクローズ後の遷移先をプライマリチャネルにセット */
				}
#endif
				return(ret_value);			/** Ｖ３４成立ＧＯ！ */
			}
			FCM_SetV8Error(V34_PHASE_3, TX_COM_MODE);
		}
		else {
			FCM_SetV8Error(V34_PHASE_2, TX_COM_MODE);
			MDM_ManagementV34StartUpEnd();	/** エラー！　回線断だ～ */
		}
	}
	else if (ret_value == T30_PROCEDURE) {	/** Ｖ３４半二重モードがなくてＶ８モード終了 */
		MDM_ManagementV8EndToT30();		/** Ｖ８終了処理  モデムをＶ２１チャンネル２にコンフィグ */
	}

	/* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/15 */
	else if (ret_value == TONE_CHECK_TIME_OUT) {
		FCM_SetV8Error(V34_INITIAL, TX_COM_MODE);
		MDM_ManagementV34StartUpEnd();	/** Ｖ８終了処理 */
	}

	else {	/* エラー！　回線断だ～ */
		FCM_SetV8Error(V34_PHASE_1, TX_COM_MODE);
		MDM_ManagementV34StartUpEnd();	/** Ｖ８終了処理 注意*/
	}
	return(ret_value);		/** Ｖ３４成立せず */
}


/*************************************************************************
	module		:[スタートアップ応答処理]
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
UBYTE 	FCM_AnswerStartUpProcedure(void)
{
	UBYTE	ret_value;
	ret_value = 0;

	FaxComPhaseStatus = ANS_PHASE1_1;

	V34_SetUpAnswerProcedure();		/** Ｖ８初期設定 */

	/*--------------------*/
	/* スタートアップ処理 */
	/*--------------------*/
	ret_value = FCM_AnswerStartUpPhase1();	/** Ｖ８手順実行 */

	if (ret_value == V34_PROCEDURE) {	/** Ｖ３４半二重モードでＶ８モード成立 */

		ret_value = V34_AnswerStartUpPhase2();	/** プロービング処理 */

		if (ret_value == V34_PROCEDURE) {	/** プロービング終了 */
			ret_value = V34_AnswerStartUpPhase3();	/** 等化器トレーニング */

			if (ret_value == V34_PROCEDURE) {	/** 等化器トレーニング終了 */
				FaxComPhaseStatus = ANS_PHASE4;
				return(ret_value);			/** Ｖ３４成立ＧＯ！ */
			}
			FCM_SetV8Error(V34_PHASE_3, RX_COM_MODE);
		}
		else {
			/** エラー！　回線断だ～ */
			FCM_SetV8Error(V34_PHASE_2, RX_COM_MODE);
			MDM_ManagementV34StartUpEnd();
		}
	}
	else if (ret_value == T30_PROCEDURE) {	/** Ｖ３４半二重モードでなくＶ８モード終了 */
		MDM_ManagementV8EndToT30();		/** Ｖ８終了処理  モデムをＶ２１チャンネル２にコンフィグ */
	}
	else {	/** エラー！　回線断だ～ */
		FCM_SetV8Error(V34_PHASE_1, RX_COM_MODE);
		MDM_ManagementV34StartUpEnd();	/** Ｖ８終了処理 */
	}
	return(ret_value);		/** Ｖ３４成立せず */
}


/*************************************************************************
	module		:[起呼Ｖ８手順の実行 ]
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
UBYTE  FCM_CallStartUpPhase1(void)
{
	WORD			i;
	UBYTE	ret;

#if (PRO_MODEM == MN195006)
	UWORD	counter;
	UBYTE	jump_ret;
#endif


#if (PRO_MODEM == MN195006)
	if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) { /* CI送出とANSam検出が必要 */
		MDM_SetTerminalInformation(TX_COM_MODE);	/* 松下モデムではCITXモードに入る前にCM作成 */
	}
#endif
	/*--------------------*/
	/* アンサートーン検出 */
	/*--------------------*/
	FaxComPhaseStatus = CALL_PHASE1_2;
	if (StartUpData.Item != V34_TURNAROUND) {	/* ﾀｰﾝｱﾗｳﾝﾄﾞﾎﾟｰﾘﾝｸﾞ時はANSamは出ません */
		V34_TransmitCIinV8Mode();	/** ＣＩ送信 */
		ret = FCM_CallDetectAnswerTone();	/** アンサートーン検出 */
		V34_StopCIinV8Mode();	/** ＣＩを停止 */
		if (ret == V34_PROCEDURE) {	/** ＡＮＳａｍ検出 */
#if (PRO_MODEM == MN195006)
			/* ＣＭ作成＆Ｖ３４セットアップ */
			MDM_SetTerminalInformation(TX_COM_MODE);
			MDM_SetUpV34Mode(TX_COM_MODE);
#endif
			/* 次のステップへＧＯ！ */
		}
		else {
			return(ret);
		}
	}
#if (PRO_MODEM == MN195006)
	else { /* V34_TURNAROUND の時 */
		for (counter = 0; counter < 100; counter++) { /*  */
			/*
			** MDSEQSTS が 0x11 (CM送信。注意!) になるか、1s 経つのを待つ。
			** MN1905006A の不具合で 0x10 にならない。
			** 仮になったとしても時間が非常に短いらしく、苦肉の策
			*/
			if (MDMD_GetRES_MDSEQSTS() == 0x11) {
				break;
			}
			wai_tsk(1);
		}
	}
#endif

	/*----------*/
	/* ＣＭ送信 */
	/*----------*/
	FaxComPhaseStatus = CALL_PHASE1_3;

	ret = FCM_ExecuteV8Mode(TX_COM_MODE, CALL_CM_TX);	/** ＣＭ送信開始 */
	if (ret == V34_PROCEDURE) {	/** ＣＭ送信開始 */
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}
	/* ここでＴ３０にＣＭセットしたいな～ */
	SaveT30TimingData(SYS_T30_START_TIME);
	SavedV8Data(SYS_T30_TX_FRAME, &V34SavedCM_Data[0], TxInformationCategoryByteCount, CM_F);

	/*----------*/
	/* ＪＭ受信 */
	/*----------*/
	FaxComPhaseStatus = CALL_PHASE1_4;
	ret = FCM_ExecuteV8Mode(TX_COM_MODE, CALL_JM_RX);	/** ＪＭ受信 */
	if (ret == V34_PROCEDURE) {	/** ＪＭ受信 */
		FCM_V8MonitorFlag = 0;
#if (PRO_MODEM == MN195006)
		MDM_V8OctetMonitoring(1);	/** 受信データ読み込み */
		FCM_CallFunctionData = MDM_V8StatusCallFunctionData(1);
#else
		MDM_V8OctetMonitoring();	/** 受信データ読み込み */
		FCM_CallFunctionData = MDM_V8StatusCallFunctionData();
#endif
		FCM_CallFunctionData |= CALL_FUNC_TAG;
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}

	FCM_GetV8FrameLine();		/** ＪＭデータリード */
	for (i = 0; i < RxInformationCategoryByteCount; i++) {
		V34SavedJM_Data[i] = MDM_ModemBuffer[V8FrmPos][i];	/* 受信したＪＭをセーブする */
	}
	/* ここでＴ３０にＪＭセットしたいな～ */
	SaveT30TimingData(SYS_T30_START_TIME);
	SavedV8Data(SYS_T30_RX_FRAME, &V34SavedJM_Data[0], RxInformationCategoryByteCount, JM_F);

	/*----------*/
	/* ＣＪ送信 */
	/*----------*/
	FaxComPhaseStatus = CALL_PHASE1_5;
	ret = FCM_ExecuteV8Mode(TX_COM_MODE, CALL_CJ_TX);	/** ＣＪ送信 */
	if (ret == V34_PROCEDURE) {	/** ＣＪ送信 */
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}
	/* ここでＴ３０にＣＪセットしたいな～ */
	SaveT30TimingData(SYS_T30_START_TIME);
	SaveT30Data(SYS_T30_TX_CJ, &V34SavedJM_Data[0], 0);

#if (PRO_MODEM == MN195006)
 #if 1 /* ダサすぎる･･･イマ４ 2002/01/10 K.Doukuni */
	jump_ret = V34_PROCEDURE;
	/*-----------------------*/
	/** 相手先変調モード解析 */
	/*-----------------------*/
	ret = V34_AnalizeModurationMode(TX_COM_MODE);
	if (ret == V34_PROCEDURE) {
		MDM_SetDirectionAfterPhase1(V34PrimaryChannelDirection); /* 通信方向をモデムに指示。無音送出後に判断・方向指示を行うのではちょっと遅い？ */
	}
	else if (ret == NG) {
		jump_ret = ret; /* NGでも無音送出は監視する。相手機ポーリング原稿なし時の処理のため */
	}
	else {
		return(ret);
	}
 #endif
#endif

	/*----------*/
	/* 無音送出 */
	/*----------*/
	FaxComPhaseStatus = CALL_PHASE1_6;
	ret = FCM_ExecuteV8Mode(TX_COM_MODE, CALL_SILENCE_TX);	/** 無音送信 */
	if (ret == V34_PROCEDURE) {	/** 無音送信 */
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}
	SaveT30TimingData(SYS_T30_END_TIME);

	FaxComPhaseStatus = CALL_PHASE1_7;
#if (PRO_MODEM == MN195006)
	if (jump_ret == NG) {
		ret = NG;
	}	
#else
	/*-----------------------*/
	/** 相手先変調モード解析 */
	/*-----------------------*/
	return(V34_AnalizeModurationMode(TX_COM_MODE));
#endif
}



/*************************************************************************
	module		:[応答Ｖ８手順実行]
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
UBYTE  FCM_AnswerStartUpPhase1(void)
{
	WORD			i;
	UBYTE	ret;

	FaxComPhaseStatus = ANS_PHASE1_2;

	if (MDM_V8DetectCI()) {
		SaveT30TimingData(SYS_T30_START_TIME);
		SaveT30Data(SYS_T30_RX_CI, &V34SavedCM_Data[0], 0);
	}

	/*--------------------------------*/
	/* ＡＮＳａｍ送信しながらＣＭ受信 */
	/*--------------------------------*/
	if (StartUpData.Item != V34_TURNAROUND) {
		MDM_V8TransmitANSam();		/** ＡＮＳａｍ送出開始（指示） */

		SaveT30TimingData(SYS_T30_START_TIME);
		SaveT30Data(SYS_T30_TX_ANS, &V34SavedCM_Data[0], 0);
	}
	else {		/* 1996/02/19 */
		if (MDM_V8CheckTransmittingANSam()) {	/* この時このﾊﾟｽを通ったら本当はおかしい */
			SaveT30TimingData(SYS_T30_START_TIME);
			SaveT30Data(SYS_T30_TX_ANS, &V34SavedCM_Data[0], 0);
		}
	}

	ret = FCM_ExecuteV8Mode(RX_COM_MODE, ANS_CM_RX);	/** ＣＭ受信 */

	MDM_V8StopANSam();			/** ＡＮＳａｍ停止（指示） */

	if (ret == V34_PROCEDURE) {	/** ＣＭ受信 */
		FCM_V8MonitorFlag = 0;
#if (PRO_MODEM == MN195006)
		MDM_V8OctetMonitoring(0);	/** ＣＭデータ読み込み */
		FCM_CallFunctionData = MDM_V8StatusCallFunctionData(0);
#else
		MDM_V8OctetMonitoring();	/** ＣＭデータ読み込み */
		FCM_CallFunctionData = MDM_V8StatusCallFunctionData();
#endif
		FCM_CallFunctionData |= CALL_FUNC_TAG;
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}

	FaxComPhaseStatus = ANS_PHASE1_3;
	FCM_GetV8FrameLine();		/** ＣＭデータリード */
	for (i = 0; i < RxInformationCategoryByteCount; i++) {
		V34SavedCM_Data[i] = MDM_ModemBuffer[V8FrmPos][i];		/* 受信したＣＭをセーブする */
	}
	/* ここでＴ３０にＣＭをセットしたいな～ */
#if (PRO_MODEM == MN195006)
#else
	if (MDM_V8DetectCI()) {
		SaveT30TimingData(SYS_T30_START_TIME);
		SaveT30Data(SYS_T30_RX_CI, &V34SavedCM_Data[0], 0);
	}
#endif
	SaveT30TimingData(SYS_T30_START_TIME);
	SavedV8Data(SYS_T30_RX_FRAME, &V34SavedCM_Data[0], RxInformationCategoryByteCount, CM_F);

	/*----------*/
	/* ＪＭ送信 */
	/*----------*/
	ret = FCM_ExecuteV8Mode(RX_COM_MODE, ANS_JM_TX);	/** ＪＭ送信 */
	if (ret == V34_PROCEDURE) {	/** ＪＭ送信中 */
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}

	MDM_GetJmFrame();			/** 送信したＪＭをリード */
	FCM_GetV8FrameLine();
	for (i = 0; i < RxInformationCategoryByteCount; i++) {
		V34SavedJM_Data[i] = MDM_ModemBuffer[V8FrmPos][i];		/* 送信したＪＭをセーブする */
	}
	/* ここでＴ３０にＪＭをセットしたいな～ */
	SavedV8Data(SYS_T30_TX_FRAME, &V34SavedJM_Data[0], RxInformationCategoryByteCount, JM_F);
	SaveT30TimingData(SYS_T30_START_TIME);

	/*----------*/
	/* ＣＪ受信 */
	/*----------*/
	FaxComPhaseStatus = ANS_PHASE1_4;
	ret = FCM_ExecuteV8Mode(RX_COM_MODE, ANS_CJ_RX);	/** ＣＪ受信 */
	if (ret == V34_PROCEDURE) {	/** ＣＪ受信 */
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}

	/* Ｖ．８ハンドシェーク中のノイズ対策 by O.Kimoto 1999/04/13 */
	/* ＣＪを受信しているときにノイズが入ると、ＳＥＣＲＸＢの値が０４となる。
	** しかし、モデムのステータス表にはこの値は定義されておらず、意味不明。
	** ですが、現状はその値でもＣＪ受信ＯＫとなって次にＰｈａｓｅへ進んでしまうので
	** それはそれでまずい。
	** よって、ここでＣＪが正しく受信できたかどうかＤＳＰ－ＲＡＭの値を読み出すことで
	** 確認し、ビットが立っていない場合はとりあえずＴ．３０（ＤＩＳ送出）のパスへ
	** 戻ることにします。（特許要注意です。！！！！）
	** by O.Kimoto 1999/04/07
	*/
#if (PRO_MODEM == MN195006)
#else
	if ((MDM_GetV8StatusRegister1() & 0x08) == 0x00) {
		V34ErrorCode = (UBYTE)(MDM_NewSecRxb);
		return(T30_PROCEDURE);	/* Ｔ．３０手順へ戻る */
	}
#endif

	/* ここでＴ３０にＣＪセットしたいな～  */
	SaveT30Data(SYS_T30_RX_CJ, &V34SavedJM_Data[0], 0);
	SaveT30TimingData(SYS_T30_END_TIME);

	/*----------*/
	/* 無音送信 */
	/*----------*/
	FaxComPhaseStatus = ANS_PHASE1_5;
	ret = FCM_ExecuteV8Mode(RX_COM_MODE, ANS_SILENCE_TX);	/** 無音送信 */
	if (ret == V34_PROCEDURE) {	/** 無音送信中 */
		/* 次のステップへＧＯ！ */
	}
	else {
		return(ret);
	}

	FaxComPhaseStatus = ANS_PHASE1_6;
	/*-----------------------*/
	/** 相手先変調モード解析 */
	/*-----------------------*/
	return(V34_AnalizeModurationMode(RX_COM_MODE));
}


/*************************************************************************
	module		:[アンサートーン検出]
	function	:[
		1.ＡＮＳａｍ、ＣＥＤを検出する。
		2.ＤＩＳも検出する。
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
#if (0)
** /* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/14 */
** UBYTE 	FCM_CallDetectAnswerTone(void)
** {
** 	MESSAGE_t			*msg;
** 	MESSAGE_t			data;
** 	UBYTE	value;
** 
** 	value = 0xFF;
** 	StartUpTaskInitial();
** 
** 	/* ダイアラーでアンサートーンを検出した場合はアンサートーンの種別のみを判別 */
** 	if (StartUpData.Item == V34_MANUAL) {
** 		/* T.B.D */
** 		if (tskno_v21ch2 == 0xFFFF) {
** 
** 			/*if (SYS_MemorySwitch[35] & 0x40) { 1996/11/05 */	/* 手動特別対応 1996/07/16 Y.M */
** 			if (CHK_V34DetectANSam_DuringCI()) {
** 				MDM_FilterSet(TX_V8_TONE_FILTER);
** 			}
** 			else {
** 				MDM_FilterSet(V8_TONE_FILTER);
** 			}
** 			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
** 			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
** 			cre_tsk(&tskno_v21ch2, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
** 		}
** 		FCM_TimeUp.Time = 3000;			/* ３０秒 */
** 	}
** 	else {
** 		if (tskno_v21ch2 == 0xFFFF) {
** 			MDM_FilterSet(V8_TONE_FILTER);
** 			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
** 			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
** 			cre_tsk(&tskno_v21ch2, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
** 		}
** 
** 		FCM_TimeUp.Time = 400;			/* ４秒 because Recommendation is 2.6-4.0sec */
** 	}
** 	FCM_TimeUp.SendMBX = mbxno.FCM_Task;
** 	FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
** 	if (tskno_timeup == 0xFFFF) {
** 		cre_tsk(&tskno_timeup, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
** 	}
** 
** 	if (tskno_anstone == 0xFFFF) {
** 		cre_tsk(&tskno_anstone, TSK_V34_DETECTV25ANSWERTONETASK, 0);/** Ｖ８モード中のアンサートーン（ＡＮＳａｍ／ＣＥＤ）検出タスク起動 */
** 	}
** 
** 	rcv_msg(mbxno.FCM_Task, &msg);		/** 受信メッセージ判別 */
** 	switch (msg->Item) {
** 		case FROM_V34_DETECT_V25TONE:
** 			switch (msg->Message) {
** 				case V25_ANSAM_TONE:
** 					value = V34_PROCEDURE;
** 
** /*#if 0 /@ test 1996/07/09 Y.M */
** 			/* debug 1996/07/02 */
** 					if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {
** #if (0)	/*Comment By M.Kotani 1996/07/05*/
** //						MDM_SetIO(POS_DTR, OFF);
** //						StartUpData.Option.TransmitCI = 0;
** //						V34_SetUpCallProcedure();
** #endif
** 						/*Add By M.Kotani 1996/07/05*/
** 						DspRamAccessWriteMethod1((UWORD)0x304, 0x00, 0xFB);
** 						DspRamAccessWriteMethod1((UWORD)0x38F, 0x08, 0xF7);
** 						MDM_SetIO(POS_NEWC, ON);
** 						/* MDM_SetIO(POS_NEWC, ON); By O.Kimoto 1996/07/11 */
** 					}
** 			/********************/
** /* #endif */
** 					SaveT30TimingData(SYS_T30_START_TIME);
** 					SaveT30Data(SYS_T30_RX_ANS, &V34SavedCM_Data[0], 0);
** 					V8_ANSamDetectFlag = 1;
** 					break;
** 				default:
** 					value = NG;
** 					break;
** 			}
** 			break;
** 		default:
** 			switch (msg->Message) {
** 				case V21_CH2_FLAG:
** 					value = T30_PROCEDURE;
** 					break;
** 				case FCM_TIME_UP:
** 					if (StartUpData.Item == V34_MANUAL) {
** 						value = NG;
** 					}
** 					else {
** 						value = T30_PROCEDURE;
** 						SaveT30TimingData(SYS_T30_START_TIME);
** 						SaveT30Data(SYS_T30_RX_CED, &V34SavedCM_Data[0], 0);
** 					}
** 					break;
** 				default:
** 					value = NG;
** 					break;
** 			}
** 			break;
** 	}
** 	/*-------------*/
** 	/** タスク削除 */
** 	/*-------------*/
** 	StartUpTaskDelete();
** 
** 	return(value);
** }
#else
UBYTE 	FCM_CallDetectAnswerTone(void)
{
	MESSAGE_t			*msg;
	MESSAGE_t			data;
	struct Timer10msData_t		data2;	/*  By O.Kimoto 1998/04/14 */
	UBYTE	value;

	value = 0xFF;
	StartUpTaskInitial();
	tskno_timeup2 = 0xffff;	/*  By O.Kimoto 1998/04/14 */

	/* ダイアラーでアンサートーンを検出した場合はアンサートーンの種別のみを判別 */
	if (StartUpData.Item == V34_MANUAL) {
		/* T.B.D */
		if (tskno_v21ch2 == 0xFFFF) {

#if (PRO_MODEM == MN195006)
			/*if (SYS_MemorySwitch[35] & 0x40) { 1996/11/05 */	/* 手動特別対応 1996/07/16 Y.M */
 #if 0 /* ここに来る時はCITXモード。カスタムフィルタは利用不可? 2002/01/16 K.Doukuni */
//			if (CHK_V34DetectANSam_DuringCI()) {
//				/* T.B.D MDM_FilterSet(TX_V8_TONE_FILTER); */
//			}
//			else {
//				/* T.B.D MDM_FilterSet(V8_TONE_FILTER); */
//			}
 #endif
#else
			if (CHK_V34DetectANSam_DuringCI()) {
				MDM_FilterSet(TX_V8_TONE_FILTER);
			}
			else {
				MDM_FilterSet(V8_TONE_FILTER);
			}
#endif
			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
			cre_tsk(&tskno_v21ch2, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
		}
		FCM_TimeUp.Time = 3000;			/* ３０秒 */
	}
	else {
		if (tskno_v21ch2 == 0xFFFF) {
#if (PRO_MODEM == MN195006)
#else
			MDM_FilterSet(V8_TONE_FILTER);
#endif
			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
			cre_tsk(&tskno_v21ch2, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
		}

#if (0)
** 		/* テスト的にＴ１タイマー（３５秒）を突っ込んどきます。 By O.Kimoto 1998/04/14 */
** 		FCM_TimeUp.Time = 400;			/* ４秒 because Recommendation is 2.6-4.0sec */
#else
		/* ここでは、ダイヤル後のトーン検出で消費した時間をここで調整しておきます。 By O.Kimoto 1998/04/20 */
		if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {	/* add if() 2000/03/24 Y.Murata */
			if (CHK_AFTER_DIAL_DELAY_TIME()) {	/* By M.Tachibana 1997/06/09 */
				AfterToneCheckTime = ((UWORD)CHK_AFTER_DIAL_DELAY_TIME()*100);   /*着信検出時間*/
			}
			else {
				AfterToneCheckTime = ((struct ToneParameters_t *)CTRY_BusyTone())->MaxDetectTime;	/*着信検出時間*/
			}
		
			SYS_ToneCheckTimer = (UWORD)(AfterToneCheckTime - (SYS_GeneralTimer - AfterToneCheckStartTimer));

			if (SYS_ToneCheckTimer == 0) {
				if (CHK_AFTER_DIAL_DELAY_TIME()) {	/* By M.Tachibana 1997/06/09 */
					FCM_TimeUp.Time = ((UWORD)CHK_AFTER_DIAL_DELAY_TIME()*100);   /*着信検出時間*/
				}
				else {
					FCM_TimeUp.Time = ((struct ToneParameters_t *)CTRY_BusyTone())->MaxDetectTime;	/*着信検出時間*/
				}
			}
			else {
				FCM_TimeUp.Time = SYS_ToneCheckTimer;			/* ４秒 because Recommendation is 2.6-4.0sec */
			}
		}
		else {
			FCM_TimeUp.Time = 400;			/* ４秒 because Recommendation is 2.6-4.0sec */
		}
#endif

	}
	FCM_TimeUp.SendMBX = mbxno.FCM_Task;
	FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
	if (tskno_timeup == 0xFFFF) {
		cre_tsk(&tskno_timeup, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
	}

	/* ＣＮＧ用タイマータスク起動 By O.Kimoto 1998/04/14 */
	data2.Time = 4000/10;			/* ３秒 */
	data2.SendMBX = mbxno.FCM_Task;
	data2.ReturnValue = FCM_CNG_OFF_TIME_UP;
	cre_tsk(&tskno_timeup2, TSK_CMN_MAN_TIMER10MSTASK, &data2);/** タイムアップ・タスク起動 */

	if (tskno_anstone == 0xFFFF) {
		cre_tsk(&tskno_anstone, TSK_V34_DETECTV25ANSWERTONETASK, 0);/** Ｖ８モード中のアンサートーン（ＡＮＳａｍ／ＣＥＤ）検出タスク起動 */
	}

	/* この関数内では、ＣＮＧが送出されないのでするように変更 By O.Kimoto 1998/04/14 */
	while (value == 0xFF) {	/*  By O.Kimoto 1998/04/14 */
		rcv_msg(mbxno.FCM_Task, &msg);		/** 受信メッセージ判別 */
		switch (msg->Item) {
			case FROM_V34_DETECT_V25TONE:
				switch (msg->Message) {
					case V25_ANSAM_TONE:
						value = V34_PROCEDURE;
#if (PRO_MODEM == MN195006)
#else
	/*#if 0 /@ test 1996/07/09 Y.M */
				/* debug 1996/07/02 */
						if (StartUpData.Option.TransmitCI == TRANSMIT_CI_IN_V8) {
	#if (0)	/*Comment By M.Kotani 1996/07/05*/
	//						MDM_SetIO(POS_DTR, OFF);
	//						StartUpData.Option.TransmitCI = 0;
	//						V34_SetUpCallProcedure();
	#endif
							/*Add By M.Kotani 1996/07/05*/
							DspRamAccessWriteMethod1((UWORD)0x304, 0x00, 0xFB);
							DspRamAccessWriteMethod1((UWORD)0x38F, 0x08, 0xF7);
							MDM_SetIO(POS_NEWC, ON);
							/* MDM_SetIO(POS_NEWC, ON); By O.Kimoto 1996/07/11 */
						}
				/********************/
	/* #endif */
#endif
						SaveT30TimingData(SYS_T30_START_TIME);
						SaveT30Data(SYS_T30_RX_ANS, &V34SavedCM_Data[0], 0);
						V8_ANSamDetectFlag = 1;
						break;
					default:
						/* プログラム的にはここへ来ることは有りません。一応保険 */
						value = NG;
						break;
				}
				break;
			default:
				switch (msg->Message) {
					case V21_CH2_FLAG:
						value = T30_PROCEDURE;
						break;
					case FCM_TIME_UP:
						if (StartUpData.Item == V34_MANUAL) {
							value = NG;
						}
						else {

#if (0)
** 							value = T30_PROCEDURE;
** 							SaveT30TimingData(SYS_T30_START_TIME);
** 							SaveT30Data(SYS_T30_RX_CED, &V34SavedCM_Data[0], 0);
#else
							/* 2000/03/23 Y.Murata
							 * 手動送信で、CEDだけがきて後何もこない時に、T.0.0となる
							*/
							/*value = TONE_CHECK_TIME_OUT;*/

							if (SYS_FaxComType == SYS_COMMAND_EXECUTE) {
								value = TONE_CHECK_TIME_OUT;
							}
							else {
								value = T30_PROCEDURE;
								SaveT30TimingData(SYS_T30_START_TIME);
								SaveT30Data(SYS_T30_RX_CED, &V34SavedCM_Data[0], 0);
							}

#endif

						}
						break;
					case FCM_CNG_OFF_TIME_UP:	/*  By O.Kimoto 1998/04/14 */
						FaxTransmit1080Hz();
						if (tskno_timeup2 != 0xFFFF) {
							del_tsk(&tskno_timeup2);			/* タイムアップタスク */
						}
						data2.Time = 3000/10;			/* ３０秒 */
						data2.SendMBX = mbxno.FCM_Task;
						data2.ReturnValue = FCM_CNG_OFF_TIME_UP;
						cre_tsk(&tskno_timeup2, TSK_CMN_MAN_TIMER10MSTASK, &data2);/** タイムアップ・タスク起動 */
#if (PRO_MODEM == MN195006)
#else
						MDM_SetIO(POS_CONF,V8_SETUP);		/* 1996/02/19 Y.M */
						MDM_SetIO(POS_NEWC,ON);
						MDM_SetIO(POS_NEWC,ON);	/** Add by O.Kimoto **/
#endif

						/* 1998/07/03 Y.Murata
						 * ＣＮＧタイマーの合間にストップＳＷを見ます
						*/
						if (SYS_FaxComStopSwitch()) {
							value = NG;
						}

						break;
					default:
						value = NG;
						break;
				}
				break;
		}
	}	/*  By O.Kimoto 1998/04/14 */

	/*-------------*/
	/** タスク削除 */
	/*-------------*/
	StartUpTaskDelete();
	
	if (tskno_timeup2 != 0xFFFF) {
		del_tsk(&tskno_timeup2);			/* タイムアップタスク */
	}

	return(value);
}
#endif


/*************************************************************************
	module		:[Ｖ８モードの実行]
	function	:[]
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
UBYTE  FCM_ExecuteV8Mode(UBYTE Direction, UBYTE Status)
{
	MESSAGE_t			data;
	MESSAGE_t			*msg;
	UBYTE	value;

	StartUpTaskInitial();

	FCM_V8Control.Direction = Direction;
	FCM_V8Control.ControlStatus = Status;
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	FCM_V8Control.ReturnMbxno = mbxno.FCM_V34Task;
#else
	FCM_V8Control.ReturnMbxno = mbxno.FCM_Task;
#endif
	cre_tsk(&tskno_v8control,TSK_V34_V8CONTROLTASK, &FCM_V8Control);/** Ｖ８コントロールタスク起動 */

	/*if ((Status == CALL_CM_TX) || (Status == CALL_JM_RX)) { 1996/08/03 Y.M */
	if (Status == CALL_CM_TX) {

		MDM_FilterSet(V8_TONE_FILTER);
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
		data.Item = mbxno.FCM_V34Task;		/* 送信メイルＢＯＸ */
#else
		data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
#endif
		data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
		cre_tsk(&tskno_v21ch2, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** 同時にＤＩＳのフラグも検出します */
	}

	if (Status == ANS_CM_RX) {
		if (StartUpData.Item == V34_TURNAROUND) {	/** ターンアラウンドポーリング */
			FCM_TimeUp.Time			= 600;			/* 6秒 CM検出時間 */
		}
		else {
			if (CHK_V8TransmitANSamTime()) {
				/*FCM_TimeUp.Time			= 400;*//* 4秒 ANSam送出時間 */
				/*勧告の4秒を超えないように少な目 1997/02/01 */
				FCM_TimeUp.Time			= 390;		/* 4秒 ANSam送出時間 */
			}
			else {
				FCM_TimeUp.Time			= 300;		/* 3秒 ANSam送出時間 */
			}
		}
	}
	else if (Status == CALL_JM_RX) {	/* CM送信にﾀｲﾑｵｰﾊﾞｰを設け,ﾀｲﾑｵｰﾊﾞｰ時はT30へ移行 1996/07/12 Y.Murata */
		FCM_TimeUp.Time			= 400;			/* とりあえず4秒 (ﾌﾟﾘｱﾝﾌﾞﾙ1sec + 応答受信3sec) */
	}
	else {
		FCM_TimeUp.Time			= 3000;			/* 30秒 */
	}
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	FCM_TimeUp.SendMBX		= mbxno.FCM_V34Task;
#else
	FCM_TimeUp.SendMBX		= mbxno.FCM_Task;
#endif
	FCM_TimeUp.ReturnValue	= FCM_TIME_UP;	/* 0x00FE */
	cre_tsk(&tskno_timeup, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** 異常処理のためにタイムアップタスクを起動 */

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	rcv_msg(mbxno.FCM_V34Task, &msg);	/** 受信メッセージ判別 */
#else
	rcv_msg(mbxno.FCM_Task, &msg);	/** 受信メッセージ判別 */
#endif
	switch (msg->Item) {
		case FROM_V34_V8CONTROL:
			switch (msg->Message) {
				case V8_COMPLETE:
					value = V34_PROCEDURE;
					break;
				case V8_NG:
					value = NG;
					V34ErrorCode = (UBYTE)(msg->SubMessage1);
					break;
			}
			break;
		default:
			switch (msg->Message) {
				case V21_CH2_FLAG:
					value = T30_PROCEDURE;
					break;
				case FCM_TIME_UP:
					if ((Status == ANS_CM_RX) && (StartUpData.Item != V34_TURNAROUND)) {	/* ANSam Time Over */
						value = T30_PROCEDURE;
					}
					/* CM送信にﾀｲﾑｵｰﾊﾞｰを設け,ﾀｲﾑｵｰﾊﾞｰ時はT30へ移行 1996/07/12 Y.Murata */
					else if ((Status == CALL_JM_RX) && (StartUpData.Item != V34_TURNAROUND)) {	/* ANSam Time Over */
						value = T30_PROCEDURE;
					}
					else {
						value = NG;
					}
					break;
			}
			break;
	}

	StartUpTaskDelete();
	return(value);
}


/*************************************************************************
	module		:[フレーム取り込み]
	function	:[]
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
void  FCM_GetV8FrameLine(void)
{
	WORD			i;
	UBYTE	pos;

	pos = 0;
	V8FrmPos = 0;
	V8CallFunctionPos = 0;
	RxInformationCategoryByteCount = 0;

	while (pos < 8) {		/**	モデムバッファポインター < 8	*/
		if (MDM_RxSize[pos] != 0) {		/**	受信バイト数 > 0	*/
			if (MDM_ModemBuffer[pos][V8_SYNCHRONIZATION_POS] == 0xE0)	{	/** ＣＭ／ＪＭフレーム受信 */
				RxInformationCategoryByteCount = MDM_RxSize[pos];
				V8FrmPos = pos;
				for (i = 0; i < 262; i++) {
					if ((MDM_ModemBuffer[pos][i] & 0x0F) == CALL_FUNC_TAG) {
						V8CallFunctionPos = i;
						break;
					}
				}
			}
		}
		pos++;
	}
}


/*************************************************************************
	module		:[ＣＭ／ＪＭフレーム作成]
	function	:[]
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
void  FCM_MakeFrameCMandJM(void)
{
	/* ﾌﾟﾘｱﾝﾌﾞﾙ */
	MDM_ModemBuffer[0][V8_INFIRMATION_POS] = 0xFF;	/** 情報シーケンス先行する連続「１」 */
	MDM_ModemBuffer[0][V8_SYNCHRONIZATION_POS] = 0xE0;	/** ＣＭ、ＪＭシーケンス同期符号 */

	if (StartUpData.Direction == TX_COM_MODE) {

		/* TX FAX ｾｯﾄ */
		MDM_ModemBuffer[0][2] = TRANSMIT_CALL;
		/* 変調モード */
		MDM_ModemBuffer[0][3] = MODURATION_TAG;
		MDM_ModemBuffer[0][3] |= V34_HALF_DUPLEX;

		switch (AvailableTxBaudRate) {
			case BPS14400_V17:
			case BPS12000_V17:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				MDM_ModemBuffer[0][4] |= V17_AVAILABLE;
				MDM_ModemBuffer[0][4] |= V29_AVAILABLE;
				MDM_ModemBuffer[0][4] |= V27_AVAILABLE;
				break;
			case BPS9600_V29:
			case BPS7200_V29:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				MDM_ModemBuffer[0][4] |= V29_AVAILABLE;
				MDM_ModemBuffer[0][4] |= V27_AVAILABLE;
				break;
			case BPS4800_V27:
			case BPS2400_V27:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				MDM_ModemBuffer[0][4] |= V27_AVAILABLE;
				break;
			default:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				break;
		}
		MDM_ModemBuffer[0][5] = EXTENSION_OCTET;
		MDM_ModemBuffer[0][5] |= V21_AVAILABLE;
	}
	else {
		/* RX FAX ｾｯﾄ */
		MDM_ModemBuffer[0][2] = RECEIVE_CALL;
		/* 変調モード */
		MDM_ModemBuffer[0][3] = MODURATION_TAG;
		MDM_ModemBuffer[0][3] |= V34_HALF_DUPLEX;

		switch (AvailableRxBaudRate) {
			case BPS14400_V17:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				MDM_ModemBuffer[0][4] |= V17_AVAILABLE;
				MDM_ModemBuffer[0][4] |= V29_AVAILABLE;
				MDM_ModemBuffer[0][4] |= V27_AVAILABLE;
				break;
			case BPS9600_V29:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				MDM_ModemBuffer[0][4] |= V29_AVAILABLE;
				MDM_ModemBuffer[0][4] |= V27_AVAILABLE;
				break;
			case BPS4800_V27:
			case BPS2400_V27:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				MDM_ModemBuffer[0][4] |= V27_AVAILABLE;
				break;
			default:
				MDM_ModemBuffer[0][4] = EXTENSION_OCTET;
				break;
		}
		MDM_ModemBuffer[0][5] = EXTENSION_OCTET;
		MDM_ModemBuffer[0][5] |= V21_AVAILABLE;
	}

	TxInformationCategoryByteCount = 6;
}


/*------------------------------*/
/* タスクＩＤ格納アドレス初期化 */
/*------------------------------*/
void  StartUpTaskInitial(void)
{
	tskno_timeup = 0xFFFF;		/* タイムアップタスク */
	tskno_anstone = 0xFFFF;		/* アンサートーン検出タスク */
	tskno_v21ch2 = 0xFFFF;		/* Ｖ２１チャンネル２フラグ検出タスク */
	tskno_v8control = 0xFFFF;	/* Ｖ８コントロールタスク */
}

/*------------*/
/* タスク削除 */
/*------------*/
void  StartUpTaskDelete(void)
{
	if (tskno_timeup != 0xFFFF) {
		del_tsk(&tskno_timeup);			/* タイムアップタスク */
	}
	if (tskno_anstone != 0xFFFF) {
		del_tsk(&tskno_anstone);		/* アンサートーン検出タスク */
	}
	if (tskno_v21ch2 != 0xFFFF) {
		del_tsk(&tskno_v21ch2);			/* Ｖ２１チャンネル２フラグ検出タスク */
	}
	if (tskno_v8control != 0xFFFF) {
		del_tsk(&tskno_v8control);		/* Ｖ８コントロールタスク */
	}
}





void  SavedV8Data(UBYTE FrameKind, UBYTE *SourceBuffer, UWORD NumberOfByte, UBYTE Name)
{
	UWORD			byte, i;
	UBYTE	buffer[20];

	if (NumberOfByte == 0) {
		buffer[0] = 0xFF;
		buffer[1] = 0xE0;
		buffer[2] = Name;
		SaveT30Data(FrameKind, &buffer[0], 3);
		return;
	}

	for (i = 0; i < NumberOfByte; i++ ) {
		if (*(SourceBuffer + i) == 0xE0) {
			break;
		}
	}
	if ( i >= NumberOfByte) {
		SaveT30Data(FrameKind, SourceBuffer, NumberOfByte);
	}
	else {
		buffer[0] = 0xFF;
		buffer[1] = 0xE0;
		buffer[2] = Name;
		byte = 3;

		while(byte < 20) {
			buffer[byte] = *(SourceBuffer + i + 1);
			if (i >= (NumberOfByte -1)) {
				break;
			}
			byte++;
			i++;
		}
		SaveT30Data(FrameKind, &buffer[0], byte);
	}
}



/* End of File */
