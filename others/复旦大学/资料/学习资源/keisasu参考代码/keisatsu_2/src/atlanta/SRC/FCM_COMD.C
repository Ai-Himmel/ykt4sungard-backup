/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/CLOVER                                                */
/*  ファイル名   : FCM_COMD.C                                                */
/*  モジュール   :                                                           */
/*               : FCM_TransmitCommand()                                     */
/*               : FCM_ReceiveCommand()                                      */
/*               : FCM_ReceiveResponse()                                     */
/*               : FCM_ReceiveTCF()                                          */
/*               : FCM_FskHighSpeedCheck()                                   */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1995/10/30                                                */
/*  概  要       : 命令送信／応答受信／命令受信                              */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*               : 1995/12/19 応答受信時のT4ﾀｲﾏｰの設定は、RICE時はﾓﾃﾞﾑで設定 */
/*               :            していたが、今回からFCMで設定し大域値引き数渡し*/
/*---------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"

#if (PRO_TX_SPEED == V34) /* This file only includes V34 related functions. */
							/* Ported from Clover by H.Kubo 1997/08/07 */

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\message.h"

#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\fcm_def.h"

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
#include "\src\atlanta\define\atd_def.h"
 #endif
#endif

#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#elif (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/07 */
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
#endif /* (PRO_MODEM == R288F) */


CONST UBYTE far DBG_CONTROL_CONTINU = 0;	/* ｺﾝﾄﾛｰﾙCH測定用 1996/12/10 */

/*************************************************************************
	module		:[命令送信]
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
	date		:[1995/10/30]
	author		:[村田]
*************************************************************************/
void far FCM_TransmitCommand(void)	/* near->far 1996/03/12 */
{
#if (PRO_MODEM == MN195006)
	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		/* 何もしない */
		wai_tsk(1);
		return;
	}
	MDM_TransmitCommand();
#else
/* test */
	if (DBG_CONTROL_CONTINU) {
		return;
	}

	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		/* 何もしない */
		wai_tsk(1);				/* 1999/7/7 Y.Murata NAGANOより 1999/10/21 Y.Murata */
	}
	else {
		MDM_TransmitCommand();
	}
#endif
}


/*************************************************************************
	module		:[命令受信]
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
	date		:[1995/10/30]
	author		:[村田]
*************************************************************************/
UBYTE far FCM_ReceiveCommand(WORD	timer, UBYTE cc_try)	/* near->far 1996/03/12 */
{
	UBYTE	value;
	UBYTE	dummy;

#if (PRO_MODEM == MN195006)	/* 松下モデム評価用 */
	struct	MDM_RxFskControlData_t fsk_control;

	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		wai_tsk(1);
		value = FSK_ERROR;
		return( value );
	}

	fsk_control.PhaseMode = MDM_FSK_FLAG_MODE;
	fsk_control.Ability = 0;
	if (RxECM_PixTimeoutFlag == 1) {	/* ＥＣＭタイムアウト回避の時 */
		fsk_control.Ability |= ECM_PIX_TIMEOUT;
		fsk_control.Timer = Set64K_PixTime();	/* ＦＳＫ受信フレーム監視タスク用タイマを回避タイマ設定 */
	}
	else {
		fsk_control.Timer = timer;
	}
	value = MDM_ReceiveCommand(&fsk_control);
	return(value);

#else


 #if 0	/* 1996/04/25 */
//	return(MDM_ReceiveCommand(timer));
 #endif

/* test */
	if (DBG_CONTROL_CONTINU) {
		value = FSK_ERROR;
		return(value);
	}

	/* 1996/08/07 */
	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		wai_tsk(1);				/* 1999/7/7 Y.Murata NAGANOより 1999/10/21 Y.Murata */
		value = FSK_ERROR;
		return(value);
	}

	/* 受信レベル測定 1997/01/28 */
	if (SYS_V34ProcedureExecuting() == 0) {
		if (MDM_FirstV21Ch2FlagReceive == 1) {
			MDM_V21MeasureStartGo = 1;
		}
	}
	MDM_FirstV21Ch2FlagReceive = 0;
	MDM_FskFcsTimeOutFlag = 0;		/* 1997/02/08 */

	value = MDM_ReceiveCommand(timer);

	/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
	if (SYS_V34ProcedureExecuting()) {
		if (value == FSK_ERROR) {
			if (CHK_V34ControlChannelRetrain()) {
				MDM_SetControlChannelRetrain();
			}
		}

		/* 1996/5/17 Y.Murata
		 * リトレーンを検出すれば、もう１回受信しなおす
		*/
		if (cc_try == CONTINUE_CCRETRAIN) {
			if (value == CC_RETRAIN) {
				value = MDM_ReceiveCommand(timer);

				/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
				if (SYS_V34ProcedureExecuting()) {
					if (value == FSK_ERROR) {
						if (CHK_V34ControlChannelRetrain()) {
							MDM_SetControlChannelRetrain();
						}
					}
				}
			}
		}
	}
	else {	/* 1997/02/08 */
		if (MDM_FskFcsTimeOutFlag == 1) {
			if (cc_try == CONTINUE_CCRETRAIN) {
				value = MDM_ReceiveCommand(timer);
				if (value == FSK_ERROR) {
					dummy = 1;
				}
				else {
					dummy = 2;
				}
			}
		}
	}
	if (value == CC_RETRAIN) {
		value = FSK_ERROR;
	}
	return(value);
#endif
}


/*************************************************************************
	module		:[応答受信]
	function	:[
		1.ＣＩ検出も同時に行う時はＣＩ検出までＡＮＳａｍを送信しない設定に
		　しておき、Ｖ２１ＨＤＬＣフラグを検出する。
		2.Ｖ２１ＨＤＬＣフラグを検出すれば通常Ｔ３０を実行する。
		3.ＣＩを検出すればＡＮＳａｍを送出しＶ８モード実行する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/10/30]
	author		:[村田]
*************************************************************************/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
UBYTE far FCM_ReceiveResponse(UBYTE DetectCI_Enable, UBYTE cc_try)	/* near->far 1996/03/12 */
{
 #if (PRO_MODEM == MN195006)

	MESSAGE_t	*msg;
	MESSAGE_t	data;
	UWORD		tskno_v21flag_detect;
	UWORD		tskno_response_time;
	UWORD		tskno_v8_CI_detect;
	WORD		i;
	UBYTE		value;
	UBYTE		dummy;
		
	struct MDM_RxFskControlData_t fsk_control;

	tskno_v21flag_detect = 0xFFFF;
	tskno_response_time = 0xFFFF;
	tskno_v8_CI_detect = 0xFFFF;
	value = 0xFF;
	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		wai_tsk(1);
		value = FSK_ERROR;
		return(value);
	}

  #if 0
//	MDM_FirstV21Ch2FlagReceive = 0;
//	MDM_FskFcsTimeOutFlag = 0;		/* 1997/02/08 */
  #endif

	if (DetectCI_Enable == 1) {

		/* time up task */	/* 下から移動 1999/09/08 Y.Murata */
		if (tskno_response_time == 0xFFFF) {
			FCM_TimeUp.Time = FCM_ReceiveResponseTime;
			FCM_TimeUp.SendMBX = mbxno.FCM_Task;
			FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
			cre_tsk(&tskno_response_time, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
		}

		/*--------------------------------------*/
		/* V8 Config                            */
		/* No TX of ANSam until CI detected ｾｯﾄ */
		/*--------------------------------------*/

		StartUpData.Item = V34_MANUAL;
		StartUpData.Option.TransmitCI = 0;
		StartUpData.Direction = TX_COM_MODE;

	 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
		|| (SYB_DB_PollingDocumentStatus == 1)
		|| (SYB_SelectPollDocumentStatus == 1)
		|| (CheckPollingTxType() != 0) /* added by H.Kubo 1998/04/24 */
		|| (CHK_UNI_FcodeSecureDocPollTx())) {
			StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
		}
		else {
			StartUpData.Allowed = TX_COM_MODE;
		}

		MDM_ToneANSModeConfig();		/** TONAL5-ANS */

		/* CI検出task*/
		if (tskno_v8_CI_detect == 0xFFFF) {
			cre_tsk(&tskno_v8_CI_detect, TSK_V34_DETECTV8CITASK, 0);
		}

		/* V21H Channel Flag 検出 */
		if (tskno_v21flag_detect == 0xFFFF) {
			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
			/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
			cre_tsk(&tskno_v21flag_detect, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);
		}

		rcv_msg(mbxno.FCM_Task, &msg);		/** 受信メッセージ判別 */
		switch (msg->Item) {
			case FROM_V34_DETECT_V8CI:
				switch (msg->Message) {
					case V8_CI_DETECT:
						value = CALL_INDICATOR_RECEIVE;
						break;
					default:
						value = TIME_OVER;
						break;
				}
				break;
			default:
				switch (msg->Message) {
					case V21_CH2_FLAG:
						value = FSK_RECEIVE;
						break;
					case FCM_TIME_UP:
					default:
						value = TIME_OVER;
						break;
				}
				MDM_ManagementV8EndToT30();
				break;
		}
		
		if (tskno_v21flag_detect != 0xFFFF) {
			del_tsk(&tskno_v21flag_detect);
		}
		if (tskno_response_time != 0xFFFF) {
			del_tsk(&tskno_response_time);
		}
		if (tskno_v8_CI_detect != 0xFFFF) {
			del_tsk(&tskno_v8_CI_detect);
		}

		if (value == FSK_RECEIVE) {
			DetectCI_Enable = 0;
		}
		else {
			return(value);
		}
	}	/* end of DetectCI_Enable */

	fsk_control.PhaseMode = MDM_FSK_FLAG_MODE;
	fsk_control.Ability = 0;
	fsk_control.Timer = FCM_ReceiveResponseTime;

	value = MDM_ReceiveResponse(&fsk_control);

	/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする *//* copied by K.Doukuni 2001/12/22 */
	if (SYS_V34ProcedureExecuting()) {
		if (value == FSK_ERROR) {
			if (CHK_V34ControlChannelRetrain()) {
				MDM_SetControlChannelRetrain();
			}
		}

		/* 1996/5/17 Y.Murata
		 * リトレーンを検出すれば、もう１回受信しなおす
		*/
		if (cc_try == CONTINUE_CCRETRAIN) {
			if (value == CC_RETRAIN) {
				value = MDM_ReceiveResponse(&FCM_ReceiveResponseTime);	/* err これって危険？ */

				/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
				if (SYS_V34ProcedureExecuting()) {
					if (value == FSK_ERROR) {
						if (CHK_V34ControlChannelRetrain()) {
							MDM_SetControlChannelRetrain();
						}
					}
				}
			}
		}
	}
	else {	/* 1997/02/08 */
		if (MDM_FskFcsTimeOutFlag == 1) {
			if (cc_try == CONTINUE_CCRETRAIN) {
				value = MDM_ReceiveResponse(&FCM_ReceiveResponseTime);	/* err これって危険？ */
				if (value == FSK_ERROR) {
					dummy = 1;
				}
				else {
					dummy = 2;
				}
			}
		}
	}
	if (value == CC_RETRAIN) {
		value = FSK_ERROR;
	}

	return(value);

 #else	/* (PRO_MODEM_MN195006 == ENABLE) */
	MESSAGE_t			*msg;
	MESSAGE_t			data;
	UWORD			tskno_v21flag_detect;
	UWORD			tskno_response_time;
	UWORD			tskno_v8_CI_detect;
	WORD			i;
	UBYTE	value;
	UBYTE	dummy;
/* #if defined(POPLAR_F) *//* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
	UWORD			tskno_busy_tone_detect;
	struct			ToneDetectMailBoxData_t	BusyToneDetectMailBox;
/* #endif */

	tskno_v21flag_detect = 0xFFFF;
	tskno_response_time = 0xFFFF;
	tskno_v8_CI_detect = 0xFFFF;
	value = 0xFF;

/* #if defined(POPLAR_F) *//* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
	tskno_busy_tone_detect = 0xFFFF;
/* #endif */

/* test */
	if (DBG_CONTROL_CONTINU) {
		value = FSK_ERROR;
		return(value);
	}

	/* 1996/08/07 */
	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		wai_tsk(1);				/* 1999/7/7 Y.Murata NAGANOより 1999/10/21 Y.Murata */
		value = FSK_ERROR;
		return(value);
	}

	/* 受信レベル測定 1997/01/28 */
	if (SYS_V34ProcedureExecuting() == 0) {
		if (MDM_FirstV21Ch2FlagReceive == 1) {
			MDM_V21MeasureStartGo = 1;
		}
	}
	MDM_FirstV21Ch2FlagReceive = 0;
	MDM_FskFcsTimeOutFlag = 0;		/* 1997/02/08 */

	if (DetectCI_Enable == 1) {

		/* time up task */
/* #if defined(POPLAR_F) *//* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
		if (tskno_response_time == 0xFFFF) {
			FCM_TimeUp.Time = FCM_ReceiveResponseTime;
			FCM_TimeUp.SendMBX = mbxno.FCM_V34Task;
			FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
			cre_tsk(&tskno_response_time, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
		}
/* #endif */
		/*--------------------------------------*/
		/* V8 Config                            */
		/* No TX of ANSam until CI detected ｾｯﾄ */
		/*--------------------------------------*/
		/* 1997/01/28 debug */
		MDM_SetIO(POS_CEQ, ON);

		StartUpData.Item = V34_MANUAL;
		StartUpData.Option.TransmitCI = 0;
		StartUpData.Direction = TX_COM_MODE;

	 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
		|| (SYB_DB_PollingDocumentStatus == 1)
		|| (SYB_SelectPollDocumentStatus == 1)
		|| (CheckPollingTxType() != 0) /* added by H.Kubo 1998/04/24 */
		|| (CHK_UNI_FcodeSecureDocPollTx())) {
			StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
		}
		else {
			StartUpData.Allowed = TX_COM_MODE;
		}
#if (0)/* 2001/10/18 Y.Murata */
**		if ((SYB_PollingDocumentStatus == 1) || (SYB_DB_PollingDocumentStatus == 1)) {
**			StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
**		}
**		else {
**			StartUpData.Allowed = TX_COM_MODE;
**		}
#endif

		MDM_SetUpV8Mode();		/** Ｖ８モード設定 */
		FCM_MakeFrameCMandJM();		/** 試行可能ＣＭデータ作成 */
		for (i = 0; i < TxInformationCategoryByteCount; i++) {
			V34SavedAvailableJM_Data[i] = MDM_ModemBuffer[0][i];
		}
		MDM_SetTerminalInformation(StartUpData.Allowed);	/** モデムに端末情報を与える */
		MDM_SetV34DataRate();		/** モデムデータ速度設定 */

		/* 1997/01/20
		 * L8153-3 Release Note 1.8 Fine tune Selection of 33.6/31.2
		 * 手動の時のパスで抜けていたので追加
		*/
		/* Ｒ６７１３－２２Ｐでは、過去のＷｏｒｋａｒｏｕｎｄをすべて外すようにロックウェルから指示が
		** あったので、下記の条件を変更します。
		** By O.Kimoto 1997/07/02 
		*/
#if (0)
** 		if (SYS_ModemVersion != MDM_L6713_13P) [
#endif
 		if ((SYS_ModemVersion == MDM_L6713_14P) || (SYS_ModemVersion == MDM_L6713_20P)) {
			MDM_FinetuneSelection336or312();
		}

		MDM_StartGoV8Mode();		/** Ｖ８モード開始 */

		/*if (SYS_MemorySwitch[34] & 0x80) { 1996/11/05 */	/* 松下対策 1996/07/16 Y.M */
		if (CHK_V34DetectCIforMGCS()) {
			MDM_FilterSet(RX_V8_TONE_FILTER);
		}
		else {
			/* V21H Channel Flag検出用ﾌｨﾙﾀｰｾｯﾄ */
			/* Not Detect NSS by V21H Mode because Filter Set has Long Time 1996/10/23 Y.Murata */
			/*MDM_FilterSet(V8_TONE_FILTER);*/
			MDM_FilterSet(V8_MODE_FSK_TONE_FILTER);
		}

		/* CI検出task*/
		if (tskno_v8_CI_detect == 0xFFFF) {
			cre_tsk(&tskno_v8_CI_detect, TSK_V34_DETECTV8CITASK, 0);
		}

		/* V21H Channel Flag 検出 */
		if (tskno_v21flag_detect == 0xFFFF) {
/* #if defined(POPLAR_F) */
#if (1)	/* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
			data.Item = mbxno.FCM_V34Task;		/* 送信メイルＢＯＸ */
#else
//			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
#endif
			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
			cre_tsk(&tskno_v21flag_detect, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
		}

/* #if defined(POPLAR_F) */
/* #else */
#if (0)	/* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
//		/* time up task */
//		if (tskno_response_time == 0xFFFF) {
//			FCM_TimeUp.Time = FCM_ReceiveResponseTime;
//			FCM_TimeUp.SendMBX = mbxno.FCM_Task;
//			FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
//			cre_tsk(&tskno_response_time, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
//		}
#endif

/* #if defined(POPLAR_F) *//* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
		if (FCM_BusyToneDetectStatus) {
			if (tskno_busy_tone_detect == 0xFFFF) {
				BusyToneDetectMailBox.ToneType = PHB1_BUSY;
				BusyToneDetectMailBox.SendMBX = mbxno.FCM_V34Task;
				/* PhaseB1時のBUSYトーンはON/OFF/ON/OFF検出 */
				cre_tsk(&tskno_busy_tone_detect, TSK_ATD_TONEDETECTPATTERN1TASK, &BusyToneDetectMailBox);
			}
		}
/* #endif */

/* #if defined(POPLAR_F) */
#if (1)	/* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
		if (SYS_PhaseB1Flag) {	/* TEL/FAX待機中のFaseB1でのBUSY検出時 */	/* NTT BUSY検出 */
			SYS_Busy_detecting = 1;
			rcv_msg(mbxno.FCM_V34Task, &msg);		/** 受信メッセージ判別 */
			SYS_Busy_detecting = 0;
		}
		else {
			rcv_msg(mbxno.FCM_V34Task, &msg);		/** 受信メッセージ判別 */
		}
#else
//		rcv_msg(mbxno.FCM_Task, &msg);		/** 受信メッセージ判別 */
#endif
		switch (msg->Item) {
			case FROM_V34_DETECT_V8CI:
				switch (msg->Message) {
					case V8_CI_DETECT:
						value = CALL_INDICATOR_RECEIVE;
						break;
					default:
						value = TIME_OVER;
						break;
				}
				break;
/* #if defined(POPLAR_F) *//* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
			case FROM_AUTODIAL:
				switch (msg->Message) {
					case PHB1_BUSY:
						value = PHB1_DETECT_BUSY_TONE;
						break;
					default:
						value = TIME_OVER;
						break;
				}
				break;
/* #endif */
			default:
				switch (msg->Message) {
					case V21_CH2_FLAG:
						value = FSK_RECEIVE;
						break;
					case FCM_TIME_UP:
					default:
						value = TIME_OVER;
						break;
				}
				MDM_ManagementV8EndToT30();
				break;
		}
		if (tskno_v21flag_detect != 0xFFFF) {
			del_tsk(&tskno_v21flag_detect);
		}
		if (tskno_response_time != 0xFFFF) {
			del_tsk(&tskno_response_time);
		}
		if (tskno_v8_CI_detect != 0xFFFF) {
			del_tsk(&tskno_v8_CI_detect);
		}

/* #if defined(POPLAR_F) *//* “#if defined(POPLAR_F)”を2重に使っているのでふさぎます by J.Kishida 2002/09/09 */
		if (tskno_busy_tone_detect != 0xFFFF) {
			del_tsk(&tskno_busy_tone_detect);
		}
/* #endif */

		if (value == FSK_RECEIVE) {
			DetectCI_Enable = 0;
		}
		else {
			return(value);
		}

	}	/* end of DetectCI_Enable */

#if 0	/* 1996/04/25 */
//	return(MDM_ReceiveResponse(FCM_ReceiveResponseTime, DetectCI_Enable));
#endif

	value = MDM_ReceiveResponse(FCM_ReceiveResponseTime);

	/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
	if (SYS_V34ProcedureExecuting()) {
		if (value == FSK_ERROR) {
			if (CHK_V34ControlChannelRetrain()) {
				MDM_SetControlChannelRetrain();
			}
		}

		/* 1996/5/17 Y.Murata
		 * リトレーンを検出すれば、もう１回受信しなおす
		*/
		if (cc_try == CONTINUE_CCRETRAIN) {
			if (value == CC_RETRAIN) {
				value = MDM_ReceiveResponse(FCM_ReceiveResponseTime);

				/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
				if (SYS_V34ProcedureExecuting()) {
					if (value == FSK_ERROR) {
						if (CHK_V34ControlChannelRetrain()) {
							MDM_SetControlChannelRetrain();
						}
					}
				}
			}
		}
	}
	else {	/* 1997/02/08 */
		if (MDM_FskFcsTimeOutFlag == 1) {
			if (cc_try == CONTINUE_CCRETRAIN) {
				value = MDM_ReceiveResponse(FCM_ReceiveResponseTime);
				if (value == FSK_ERROR) {
					dummy = 1;
				}
				else {
					dummy = 2;
				}
			}
		}
	}
	if (value == CC_RETRAIN) {
		value = FSK_ERROR;
	}

	return(value);
 #endif
}

#else	/* NTT音声応答が入ってない機種 || ORANGEモデムを使っている音声応答対応の機種 */

UBYTE far FCM_ReceiveResponse(UBYTE DetectCI_Enable, UBYTE cc_try)	/* near->far 1996/03/12 */
{
	
 #if (PRO_MODEM == MN195006)

	MESSAGE_t	*msg;
	MESSAGE_t	data;
	UWORD		tskno_v21flag_detect;
	UWORD		tskno_response_time;
	UWORD		tskno_v8_CI_detect;
	WORD		i;
	UBYTE		value;
	UBYTE		dummy;
		
	struct MDM_RxFskControlData_t fsk_control;

	tskno_v21flag_detect = 0xFFFF;
	tskno_response_time = 0xFFFF;
	tskno_v8_CI_detect = 0xFFFF;
	value = 0xFF;
	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		wai_tsk(1);
		value = FSK_ERROR;
		return(value);
	}

  #if 0
//	MDM_FirstV21Ch2FlagReceive = 0;
//	MDM_FskFcsTimeOutFlag = 0;		/* 1997/02/08 */
  #endif

	if (DetectCI_Enable == 1) {

		/* time up task */	/* 下から移動 1999/09/08 Y.Murata */
		if (tskno_response_time == 0xFFFF) {
			FCM_TimeUp.Time = FCM_ReceiveResponseTime;
			FCM_TimeUp.SendMBX = mbxno.FCM_Task;
			FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
			cre_tsk(&tskno_response_time, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
		}

		/*--------------------------------------*/
		/* V8 Config                            */
		/* No TX of ANSam until CI detected ｾｯﾄ */
		/*--------------------------------------*/

		StartUpData.Item = V34_MANUAL;
		StartUpData.Option.TransmitCI = 0;
		StartUpData.Direction = TX_COM_MODE;

	 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
		|| (SYB_DB_PollingDocumentStatus == 1)
		|| (SYB_SelectPollDocumentStatus == 1)
		|| (CheckPollingTxType() != 0) /* added by H.Kubo 1998/04/24 */
		|| (CHK_UNI_FcodeSecureDocPollTx())) {
			StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
		}
		else {
			StartUpData.Allowed = TX_COM_MODE;
		}

		MDM_ToneANSModeConfig();		/** TONAL5-ANS */

		/* CI検出task*/
		if (tskno_v8_CI_detect == 0xFFFF) {
			cre_tsk(&tskno_v8_CI_detect, TSK_V34_DETECTV8CITASK, 0);
		}

		/* V21H Channel Flag 検出 */
		if (tskno_v21flag_detect == 0xFFFF) {
			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
			/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
			cre_tsk(&tskno_v21flag_detect, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);
		}

		rcv_msg(mbxno.FCM_Task, &msg);		/** 受信メッセージ判別 */
		switch (msg->Item) {
		case FROM_V34_DETECT_V8CI:
			switch (msg->Message) {
			case V8_CI_DETECT:
				value = CALL_INDICATOR_RECEIVE;
				break;
			default:
				value = TIME_OVER;
				break;
			}
			break;
		default:
			switch (msg->Message) {
			case V21_CH2_FLAG:
				value = FSK_RECEIVE;
				break;
			case FCM_TIME_UP:
			default:
				value = TIME_OVER;
				break;
			}
			MDM_ManagementV8EndToT30();
			break;
		}
		
		if (tskno_v21flag_detect != 0xFFFF) {
			del_tsk(&tskno_v21flag_detect);
		}
		if (tskno_response_time != 0xFFFF) {
			del_tsk(&tskno_response_time);
		}
		if (tskno_v8_CI_detect != 0xFFFF) {
			del_tsk(&tskno_v8_CI_detect);
		}

		if (value == FSK_RECEIVE) {
			DetectCI_Enable = 0;
		}
		else {
			return(value);
		}
	}	/* end of DetectCI_Enable */

	fsk_control.PhaseMode = MDM_FSK_FLAG_MODE;
	fsk_control.Ability = 0;
	fsk_control.Timer = FCM_ReceiveResponseTime;

	value = MDM_ReceiveResponse(&fsk_control);

	/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする *//* copied by K.Doukuni 2001/12/22 */
	if (SYS_V34ProcedureExecuting()) {
		if (value == FSK_ERROR) {
			if (CHK_V34ControlChannelRetrain()) {
				MDM_SetControlChannelRetrain();
			}
		}

		/* 1996/5/17 Y.Murata
		 * リトレーンを検出すれば、もう１回受信しなおす
		*/
		if (cc_try == CONTINUE_CCRETRAIN) {
			if (value == CC_RETRAIN) {
				value = MDM_ReceiveResponse(&FCM_ReceiveResponseTime);	/* err これって危険？ */

				/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
				if (SYS_V34ProcedureExecuting()) {
					if (value == FSK_ERROR) {
						if (CHK_V34ControlChannelRetrain()) {
							MDM_SetControlChannelRetrain();
						}
					}
				}
			}
		}
	}
	else {	/* 1997/02/08 */
		if (MDM_FskFcsTimeOutFlag == 1) {
			if (cc_try == CONTINUE_CCRETRAIN) {
				value = MDM_ReceiveResponse(&FCM_ReceiveResponseTime);	/* err これって危険？ */
				if (value == FSK_ERROR) {
					dummy = 1;
				}
				else {
					dummy = 2;
				}
			}
		}
	}
	if (value == CC_RETRAIN) {
		value = FSK_ERROR;
	}

	return(value);

 #else	/* (PRO_MODEM_MN195006 == ENABLE) */
	MESSAGE_t			*msg;
	MESSAGE_t			data;
	UWORD			tskno_v21flag_detect;
	UWORD			tskno_response_time;
	UWORD			tskno_v8_CI_detect;
	WORD			i;
	UBYTE	value;
	UBYTE	dummy;

	tskno_v21flag_detect = 0xFFFF;
	tskno_response_time = 0xFFFF;
	tskno_v8_CI_detect = 0xFFFF;
	value = 0xFF;

/* test */
	if (DBG_CONTROL_CONTINU) {
		value = FSK_ERROR;
		return(value);
	}

	/* 1996/08/07 */
	if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
		wai_tsk(1);				/* 1999/7/7 Y.Murata NAGANOより 1999/10/21 Y.Murata */
		value = FSK_ERROR;
		return(value);
	}

	/* 受信レベル測定 1997/01/28 */
	if (SYS_V34ProcedureExecuting() == 0) {
		if (MDM_FirstV21Ch2FlagReceive == 1) {
			MDM_V21MeasureStartGo = 1;
		}
	}
	MDM_FirstV21Ch2FlagReceive = 0;
	MDM_FskFcsTimeOutFlag = 0;		/* 1997/02/08 */

	if (DetectCI_Enable == 1) {
		/*--------------------------------------*/
		/* V8 Config                            */
		/* No TX of ANSam until CI detected ｾｯﾄ */
		/*--------------------------------------*/
		/* 1997/01/28 debug */
		MDM_SetIO(POS_CEQ, ON);

		StartUpData.Item = V34_MANUAL;
		StartUpData.Option.TransmitCI = 0;
		StartUpData.Direction = TX_COM_MODE;

	 	if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
		|| (SYB_DB_PollingDocumentStatus == 1)
		|| (SYB_SelectPollDocumentStatus == 1)
		|| (CheckPollingTxType() != 0) /* added by H.Kubo 1998/04/24 */
		|| (CHK_UNI_FcodeSecureDocPollTx())) {
			StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
		}
		else {
			StartUpData.Allowed = TX_COM_MODE;
		}
#if (0)	/* 2001/10/18 Y.Murata */
**		if ((SYB_PollingDocumentStatus == 1) || (SYB_DB_PollingDocumentStatus == 1)) {
**			StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
**		}
**		else {
**			StartUpData.Allowed = TX_COM_MODE;
**		}
#endif

		MDM_SetUpV8Mode();		/** Ｖ８モード設定 */
		FCM_MakeFrameCMandJM();		/** 試行可能ＣＭデータ作成 */
		for (i = 0; i < TxInformationCategoryByteCount; i++) {
			V34SavedAvailableJM_Data[i] = MDM_ModemBuffer[0][i];
		}
		MDM_SetTerminalInformation(StartUpData.Allowed);	/** モデムに端末情報を与える */
		MDM_SetV34DataRate();		/** モデムデータ速度設定 */

		/* 1997/01/20
		 * L8153-3 Release Note 1.8 Fine tune Selection of 33.6/31.2
		 * 手動の時のパスで抜けていたので追加
		*/
		/* Ｒ６７１３－２２Ｐでは、過去のＷｏｒｋａｒｏｕｎｄをすべて外すようにロックウェルから指示が
		** あったので、下記の条件を変更します。
		** By O.Kimoto 1997/07/02 
		*/
#if (0)
** 		if (SYS_ModemVersion != MDM_L6713_13P) [
#endif
 		if ((SYS_ModemVersion == MDM_L6713_14P) || (SYS_ModemVersion == MDM_L6713_20P)) {
			MDM_FinetuneSelection336or312();
		}

		MDM_StartGoV8Mode();		/** Ｖ８モード開始 */

		/*if (SYS_MemorySwitch[34] & 0x80) { 1996/11/05 */	/* 松下対策 1996/07/16 Y.M */
		if (CHK_V34DetectCIforMGCS()) {
			MDM_FilterSet(RX_V8_TONE_FILTER);
		}
		else {
			/* V21H Channel Flag検出用ﾌｨﾙﾀｰｾｯﾄ */
			/* Not Detect NSS by V21H Mode because Filter Set has Long Time 1996/10/23 Y.Murata */
			/*MDM_FilterSet(V8_TONE_FILTER);*/
			MDM_FilterSet(V8_MODE_FSK_TONE_FILTER);
		}

		/* CI検出task*/
		if (tskno_v8_CI_detect == 0xFFFF) {
			cre_tsk(&tskno_v8_CI_detect, TSK_V34_DETECTV8CITASK, 0);
		}

		/* V21H Channel Flag 検出 */
		if (tskno_v21flag_detect == 0xFFFF) {
			data.Item = mbxno.FCM_Task;		/* 送信メイルＢＯＸ */
			data.Message = V21_CH2_FLAG;	/* 送信メッセージ */
			cre_tsk(&tskno_v21flag_detect, TSK_MDM_DETECTV21CH2FLAGV8TASK, &data);/** Ｖ８モード中のＶ２１Ｃｈ２フラグ（ＤＩＳ）検出タスク起動 */
		}

		/* time up task */
		if (tskno_response_time == 0xFFFF) {
			FCM_TimeUp.Time = FCM_ReceiveResponseTime;
			FCM_TimeUp.SendMBX = mbxno.FCM_Task;
			FCM_TimeUp.ReturnValue = FCM_TIME_UP;	/* 0x00FE */
			cre_tsk(&tskno_response_time, TSK_CMN_MAN_TIMER10MSTASK, &FCM_TimeUp);/** タイムアップ・タスク起動 */
		}

		rcv_msg(mbxno.FCM_Task, &msg);		/** 受信メッセージ判別 */
		switch (msg->Item) {
			case FROM_V34_DETECT_V8CI:
				switch (msg->Message) {
					case V8_CI_DETECT:
						value = CALL_INDICATOR_RECEIVE;
						break;
					default:
						value = TIME_OVER;
						break;
				}
				break;
			default:
				switch (msg->Message) {
					case V21_CH2_FLAG:
						value = FSK_RECEIVE;
						break;
					case FCM_TIME_UP:
					default:
						value = TIME_OVER;
						break;
				}
				MDM_ManagementV8EndToT30();
				break;
		}
		if (tskno_v21flag_detect != 0xFFFF) {
			del_tsk(&tskno_v21flag_detect);
		}
		if (tskno_response_time != 0xFFFF) {
			del_tsk(&tskno_response_time);
		}
		if (tskno_v8_CI_detect != 0xFFFF) {
			del_tsk(&tskno_v8_CI_detect);
		}

		if (value == FSK_RECEIVE) {
			DetectCI_Enable = 0;
		}
		else {
			return(value);
		}

	}	/* end of DetectCI_Enable */

#if 0	/* 1996/04/25 */
//	return(MDM_ReceiveResponse(FCM_ReceiveResponseTime, DetectCI_Enable));
#endif

	value = MDM_ReceiveResponse(FCM_ReceiveResponseTime);

	/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
	if (SYS_V34ProcedureExecuting()) {
		if (value == FSK_ERROR) {
			if (CHK_V34ControlChannelRetrain()) {
				MDM_SetControlChannelRetrain();
			}
		}

		/* 1996/5/17 Y.Murata
		 * リトレーンを検出すれば、もう１回受信しなおす
		*/
		if (cc_try == CONTINUE_CCRETRAIN) {
			if (value == CC_RETRAIN) {
				value = MDM_ReceiveResponse(FCM_ReceiveResponseTime);

				/* Ｖ３４交信でＦＳＫエラーの時はリトレーンする */
				if (SYS_V34ProcedureExecuting()) {
					if (value == FSK_ERROR) {
						if (CHK_V34ControlChannelRetrain()) {
							MDM_SetControlChannelRetrain();
						}
					}
				}
			}
		}
	}
	else {	/* 1997/02/08 */
		if (MDM_FskFcsTimeOutFlag == 1) {
			if (cc_try == CONTINUE_CCRETRAIN) {
				value = MDM_ReceiveResponse(FCM_ReceiveResponseTime);
				if (value == FSK_ERROR) {
					dummy = 1;
				}
				else {
					dummy = 2;
				}
			}
		}
	}
	if (value == CC_RETRAIN) {
		value = FSK_ERROR;
	}

	return(value);
 #endif
}
#endif

/*************************************************************************
	module		:[ＴＣＦ受信]
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
	date		:[1995/10/30]
	author		:[村田]
*************************************************************************/
UBYTE far FCM_ReceiveTCF(UBYTE speed)	/* near->far 1996/03/12 */
{
	if (SYS_V34ProcedureExecuting() == 0) {
		return(MDM_ReceiveTCF(speed));
	}
	else {
		return(1);
	}

}


/*************************************************************************
	module		:[ 高低速ｔｕｒｎ－ｏｆｆ識別]
	function	:[
		1.第三引き数が０の時は高速オープンしてかえってくる。
		2.第三引き数が１の時は高速クローズしてかえってくる。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/10/30]
	author		:[村田]
*************************************************************************/
UBYTE FCM_FskHighSpeedCheck(UBYTE rate, UBYTE mode)
{
	UBYTE ret;
	ret = 0;

	if (SYS_V34ProcedureExecuting() == 0) {
		return(MDM_FskHighSpeedCheck(rate, mode,(UBYTE)(0x00)));
	}
	else {
/*		ret = MDM_ControlChanelDetectTurnOff(); */

		if (FCM_CheckModemAbort()) {	/* ﾓﾃﾞﾑがｱﾎﾞｰﾄした */
			wai_tsk(1);				/* 1999/7/7 Y.Murata NAGANOより 1999/10/21 Y.Murata */
			return(FSK_ERROR);			/* 1996/09/11 Y.M */
		}
		else {
			return(MDM_FskHighSpeedCheck(rate, mode,(UBYTE)(0x00)));
		}
	}
}

#endif /* (PRO_TX_SPEED == V34) */
