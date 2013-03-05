/**********************************************************************************************************************
	@(#)$Id: fcm_srtx.c,v 1.17 2005/12/21 18:19:27 xiax Exp $
	Create        : 2005/07/04
	Author        : 石橋正和
	Description   : 一斉指令送信
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#if !defined (KEISATSU)
	UBYTE NoIsseiTx; 
#else
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\ncu_def.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\hinoki\define\hino_tib.h"
#include "\src\atlanta\hinoki\define\mpr_pro.h"
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"

 /* 警察FAX DVT_ID62 Added by SMuratec 夏 2005/12/08 */
#include "\src\atlanta\define\status.h"
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\ncu_stat.h"
#include "\src\atlanta\define\sys_line.h"

/**************************************************************************************************/
/**
	@brief		一斉指令送信
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはManualTransmit()
	@date		2005/07/10 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiTx(
			BOOL bshirei) /* 指令起動信号の有無 */
{
	FCM_ISSEI_TX = TRUE;	/* 警察FAX DVT_ID17 一斉モード送信中 by SMuratec 夏 2005/11/05 */
	
	FCM_S1_Scramble = FCM_ExecutingS1Info.Available;
	if (CMN_CheckScrambleSwOn() == FALSE) { /* 背面スイッチがOFFの場合 */
		FCM_S1_Scramble = FALSE;
	}
	
	if (FCM_ExecutingS1Info.Method == SYS_S1_SENYO) {
		FCM_S1_Senyo = TRUE;
	}
	else {
		FCM_S1_Senyo = FALSE;
	}
	
	SYS_FaxComType = SYS_MANUAL_TX;
	SYS_FaxComTxType = SYS_SCANNER_TRANSMIT; /* 送信タイプ */
	
	/* 送信原稿情報取得 */
	TxMemoryFilePage = 1;
	SYS_DocBlock.Src.Mode = (BYTE)SYB_ModeSw;
	SYS_DocBlock.Dst.Mode = SYS_DocBlock.Src.Mode;	/* 追加 O.Oshima 2005/10/20 */
	SYS_DocBlock.Src.Size = (BYTE)CMN_GetDocumentScanSize();
	FirstTxMode = (UBYTE)SYS_DocBlock.Src.Mode;
	TxMode = (UBYTE)SYS_DocBlock.Src.Mode;
	DocWidth = (UBYTE)SYS_DocBlock.Src.Size;
	
	CMN_EvacuateStampSetting(); /* 済スタンプ初期化 */
	
	SCN_MotorStopRequest = 1; /* 原稿読み取り終了時にモーター停止 */
	
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
	NoNextDocument = FALSE;
#endif
	
	if (bshirei == TRUE) {
		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
		SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_FAXCOM;
	}
	
	SYS_FaxCommStage = FCM_TRANSMIT;
	MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain); /* LCD更新 */
	rcv_msg(mbxno.FCM_Task, &FcomMsg);
	
	AvailableTxBaudRate = CHK_IsseiSpeed(); /* 送信可能ボーレイト */
	AttemptTxBaudRate = AvailableTxBaudRate; /* 試行送信ボーレイト */
	TxBaudRate = AvailableTxBaudRate;
	
	AvailableTxCodingMethod = CHK_IsseiCodingMethod(); /* 符号化方式 */
	TxCodingMethod = AvailableTxCodingMethod;
	
	SYS_DocBlock.Src.Code = TxCodingMethod;
	SYS_DocBlock.Dst.Code = TxCodingMethod;
	
	AvailableTxMinimumScanningTime = CHK_IsseiMinimumScanningTime(); /* 最小伝送時間 */
	
	TxECM_Mode == ECM_OFF;
	
	V8ProcedureRequestFlag = 0; /* V8手順移行要求クリア */
	
#if defined(POPLAR_F)	/* 1999/11/29 */
	SYS_BackUpConfirmationReport = SYB_ConfirmationReportSwitch;
#endif
	
	FaxComPerformingFlag = 1;
	
	/* メインで読み取り装置(ADF/FBS)を決定して、ミラーキャリッジを移動 */
	MsgFromFaxComToMain.Message = MSG_FAXCOM_SCANNER_DECIDE;
	snd_msg(mbxno.MAN_Task, &MsgFromFaxComToMain);
	rcv_msg(mbxno.FCM_Task, &FcomMsg);
	
	
	
	FaxcomRelayControl(); /* リレーセット */
#if defined(POPLAR_F)
	MDM_SetOriginateMode(); /* モデムモードセット */
#endif
	FaxComStartTime = SYB_CurrentTime; /* 交信開始時刻 */
	SYS_FCM_StartTime = SYS_1SecGeneralTimer;

	/*-----------------------*/
	/** ジャーナル通番セーブ */
	/*-----------------------*//* 1994/09/30 */
	JournalTxTotalCount				= SYB_TxTotalCount;			/* 通信開始時間と終了時間で日付が変わった場合は、 */
	JournalRxTotalCount				= SYB_RxTotalCount;			/* 通信開始時の日付に合わせるためにセーブしておく */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
	JournalTxTotalCountExt			= SYB_TxTotalCountExt;
	JournalRxTotalCountExt			= SYB_RxTotalCountExt;
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalWorkFile.Number = JournalTxTotalCount;
	PAT_JournalWorkFile.StartTime = FaxComStartTime;
	if (SYS_FaxComType == SYS_MANUAL_TX) {
		PAT_JournalWorkFile.Kind = SYS_MANUAL_TRANSMIT;
	}
	else if (SYS_FaxComType == SYS_REMOTE_FAX_TX) {
		PAT_JournalWorkFile.Kind = SYS_REMOTE_TX;
	}

	PAT_JournalDataToImage(NUMBER);
	PAT_JournalDataToImage(START);
	PAT_JournalDataToImage(NOTE);
#endif

	FaxComTXorRX_Sign = TX_COM_MODE;			/** 送信コマンドセット */
	
	/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
	IsSHIREIKido = FALSE;
	
	if(CHK_MessageTxON() != 0) {				/** メッセージ送信要求 */
		TxCoverPageFlag = 1;					/** カバーページフラグ セット */
	}
	else {
		TxCoverPageFlag = 0;					/** カバーページフラグ クリア */
	}

	TxReceiptRequestFlag = 0;					/** 受領証送信フラグ クリア */


	SYS_BackUpConfirmationReport = SYB_ConfirmationReportSwitch;

	SYS_CurrentExecutingCommand = 0x00;		/* NULL */
	PollingTxFirstPageFlag = 0;
	
	FCM_IsseiTxBody(bshirei);
	/*************************/
	
	if (bshirei == TRUE) {
		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_FAXCOM;
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
			SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_SHIREI_IDLE;
		}
		else {
			SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_SHIREI_IDLE;
		}
	}
	FCM_ISSEI_TX = FALSE;	/* 警察FAX DVT_ID17 一斉モード送信中 by SMuratec 夏 2005/11/05 */
	
	CheckAllErrorPage(); /* T.4.2エラーを出すかどうかチェック */
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信本体
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはFaxTransmit()
	@date		2005/07/10 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiTxBody(
				BOOL bshirei) /* 指令起動信号の有無 */
{
	UBYTE ring_time; /* 一斉鳴動時間 */
	UWORD total_page;
	
	SYS_TxTotalPage		= 0;							/** 送信ページ数ゼロクリア */
	FaxComTxPerformingFlag = 1;						/** 送信中フラグセット */
	
	/* FaxComPhaseStatus = FAX_TX_PH_B1; */
	TxSpeedHandshakeFlag = 0;			/** 短縮ハンドシェイク送信フラグクリア クリアする場所を検討すること By T.Y */
	FSK_FirstReceivedFlag = 1;	/** 相手がＦＡＸであると確定した */
	/* FaxComUntilRecDISLineOFF(); */	/** ＤＩＳ受信で回線モニタをＯＦＦする */
	/* DIS_ReceivedFlag = 1; */	/*????*/						/** DIS受信フラグセット */
	FinalTxMode		= G3MODE;		/** 確定送信モード */
	
	total_page = 0;
	
	while ((FaxComPerformingFlag == 1) && (FaxComTxPerformingFlag ==1) && (SYS_FaxComStopSwitch() == 0)) {
		/* 通信中 & 送信中 & StopSwitch なし */
		DIS_ReceivedFlag = 0;	/*????*/	/** DIS受信フラグ ゼロクリア */
		
		if (total_page == 0){ /* 画データ未送信の場合 */
			MonitorSpeakerOn(); /* モニタースピーカON */
			
			FaxTimer(FCM_ISSEI_TX_A_B_TIME);
			
			if (!CHK_LineMonitor()) {
				MonitorSpeakerOff(); /* モニタースピーカOFF */
			}
			
			FCM_S1_Preamble3S = TRUE; /* 最初のDCSのプリアンブルを3秒にする */
		}
		else { /* 1ページ送信以降の場合 */
			FaxTimer(FCM_ISSEI_TX_D_B_TIME);
		}
		
		if ((FaxComPerformingFlag != 1) || (SYS_FaxComStopSwitch() != 0)) {
			FCM_S1_Preamble3S = FALSE; /* プリアンブルの長さを元に戻す */
			break;
		}
		
		TxInterMemoryFlag = NO;
		
		FaxComPhaseStatus = FAX_TX_PH_B2; /*	Phase B2  */
		
		SYS_DocBlock.Src.Mode = (BYTE)SYB_ModeSw;		/* 追加 O.Oshima 2005/10/20 */
		SYS_DocBlock.Dst.Mode = SYS_DocBlock.Src.Mode;	/* 追加 O.Oshima 2005/10/20 */
		TxMode = SYS_DocBlock.Src.Mode;
		DocWidth = SYS_DocBlock.Src.Size;
		
		FaxTxMaxLength = SYS_NO_LIMIT; /* とりあえず */
		TxMethodFlag = 1;							/** 送信方式確定フラグセット */
		TxWidth = DocWidth;
		SYS_DocBlock.Dst.Size = (BYTE)TxWidth;
		TxMinimumScanningTime = FCM_GetIsseiMinScanningTime(AvailableTxMinimumScanningTime, TxMode);
		PartnerV8Capable = 0;
		BaudrateFlag = 1;								/** ボーレイト確定フラグセット */
		
		FCM_SendIsseiDCS(); /* DCS送信 */
		FCM_S1_Preamble3S = FALSE; /* プリアンブルの長さを元に戻す */
		
		TxRetrainingFlag = 0;					/** リトレーニングなしフラグセット */
		if((FaxComPerformingFlag == 1) && (SYS_FaxComStopSwitch() == 0)){ /** 通信中 & StopSwitchなし */
			MsgFromFaxComToMain.Item = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_DISPLAY;
		}
		else{
			break;
		}
		
		FaxTimer(FCM_ISSEI_TX_B_C_TIME);
		
		FCM_IsseiTxPhaseC(); /* フェーズＣ */
		
		FaxTimer(FCM_ISSEI_TX_C_D_TIME);
		
		FCM_IsseiTxPhaseD(); /* フェーズＤ */
		
		/* 原稿排出＋次原稿繰り込み処理 */
#if (PRO_SCN_CLUTCH == ENABLE) /* スキャナクラッチ有りの場合 by H.Hirao 1998/11/19 */
		/* スキャナをクローズする時にtskno_SCN_STxStoreTaskを消しときたい(HINOKIだけの処理) */
		if (TxSmType == TX_SCAN) {	/**	スキャナ送信	*/
 #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
			if (!FaxComPerformingFlag
				|| ((TxPageFinishStatus != TX_PAGE_END) && (TxPageFinishStatus != TX_PAGE_END_MODE_CHANGE))) {
				if (tskno_SCN_STxStoreTask != 0xffff) {
					del_tsk(&tskno_SCN_STxStoreTask);
				}
				SCN_Close((UBYTE)FROM_FAXCOM);
			}
 #else
			SCN_Close((UBYTE)0);
 #endif
		}
#endif
		total_page++;
	}
	
	if(( 1 == FaxComPerformingFlag ) && ( 1 == SYS_FaxComStopSwitch() )) { /* 通信中 & StopSwitch あり */
		/*---------------*/
		/*	STOP DCN Tx	 */
		/*---------------*/
		FaxPhaseE(5);								/** フェーズＥ */
		TransmitError( 0x14,1 );
	}
	
#if (PRO_PANEL == KANJI)
	/* ＩＣＨＯＵからのフィードバック By O.Kimoto 1998/03/30 */
	/* 送信終了後に送信ページ+1のページ数が表示されるため  1997/10/10 s.takeuchi */
	SYS_FaxCommStage = FCM_TRANSMIT;
	SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );
#endif
	
	FCM_IsseiTxCloseScanner(); /* スキャナクローズ */
	
	if (bshirei == FALSE) {
		ring_time = SYB_MachineParameter[M_PARA_SW_I2]; /* 一斉鳴動時間 */
		if (ring_time > 0) {
			MonitorSpeakerOn(); /* モニタースピーカON */
			
			FCM_IsseiVoiceReq((UWORD)ring_time); /* 会話予約動作 */
			
			if (!CHK_LineMonitor()) {
				MonitorSpeakerOff(); /* モニタースピーカOFF */
			}
		}
	}
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信においてスキャナをクローズする
	
	@li			
	@param		
	@return		最小伝送時間
	@note		
	@date		2005/07/10 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiTxCloseScanner(void)
{
#if (PRO_SCN_CLUTCH == ENABLE) /* スキャナクラッチ有りの場合 */
	return;
#endif
	
	/*----------------------------------------------------------------------------------*/
	/*	桐のスキャナ送信で最終原稿を排出するために，送信の最後でスキャナクローズする	*/
	/*	但し，通信エラーがあった場合はクローズしない	Oct.18.1994						*/
	/*----------------------------------------------------------------------------------*/
	/* FBS 条件追加 1997/05/22 By T.Yamaguchi */
#if (PRO_FBS == ENABLE)
	if (SYS_ScannerExecMode != SCN_ADF) {
		return;
	}
#endif
	
	if ((TxPageFinishStatus == TX_DOC_ERR) || (TxPageFinishStatus == TX_STOPPED) || (TxPageFinishStatus == TX_1M_OVER)) {
		/**	スキャナオープン済	*/
		return;
	}
	
	if (((FaxComResult & 0x00ff) == NO_ERROR) || ((FaxComResult & 0x00ff) == 0x0014) || ((FaxComResult & 0x00ff) == 0x0041)) {
		/* 通信エラーなしor最終原稿でT.4.1 */
		if (!DS1()) {	/** ADF上に残り原稿なし */
			/* 正常終了でADFに残り原稿がない(DS1 OFF)場合のみ排出する(セット枚数＞指定枚数の時に残りをADF上に残すため) */
			/* スキャナクローズ (最終原稿を排出) */
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
			if (tskno_SCN_STxStoreTask != 0xffff) {
				del_tsk(&tskno_SCN_STxStoreTask);
			}
#endif
			if (SCN_Close(SCN_DOC_EXITING) != SCN_DOC_EXIT_OK) { /* 結果ＮＧ */
				/* 原稿排出ＮＧをメインタスクへ通知 */
				MsgFromFaxComToMain.Item	= FROM_FAXCOM;
				MsgFromFaxComToMain.Message = MSG_FAXCOM_CLOSE_ERROR;
				snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
				rcv_msg( mbxno.FCM_Task, &FcomMsg );
			}
		}
		else {
			LampOff(); /* ブロックエンド（PPS-NULL)中にT.4.1エラーになった場合、ランプが消えない不具合修正 1998/05/25 by T.Soneoka */
		}

#if (PRO_SCN_CODEC_TYPE != SOFTWARE)	/* 1998/11/17 by T.Soneoka */
		/* スキャナー送信 左端影が出る テスト T.Nose 1998/03/25 */
		if (SYB_MaintenanceSwitch[MNT_SW_C9] & CHECK_SHADING_RAM) { /* 薄読みデバッグ用 */
			UBYTE i; /* added by H.Kubo 1998/03/25 */
			DIPP_SetBitDIPPST(IDP_BIT_OFF);	/* Shading RAMを読むため */
			DIPP_ReadShadingRAM( &SCN_DebugShadingRAM[0] );	/* 1997/04/25 */
			for (i=0; i<SYS_SHADING_MAX; i++) {
				if (SYB_ShadingRAM[i] != SCN_DebugShadingRAM[i]) {
					/* 違ったらmnt swにセット */
					SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR1;
					break;
				}
			}
			/* 初期値RAMもコンペアする  1997/04/25 */
			DIPP_ReadInitialRAM( &SCN_DebugInitialRAM1[0] );
			for (i=0; i<SYS_INITIAL_MAX; i++) {
				if ((SYB_InitialRAM[i] != SCN_DebugInitialRAM0[i])
				||	(SYB_InitialRAM[i] != SCN_DebugInitialRAM1[i])) {
					/* 初期値RAMが違ったらmntB6-0にセット */
					SYB_MaintenanceSwitch[MNT_SW_C9] |= SHADING_RAM_ERROR0;
					break;
				}
			}
			DIPP_SetBitDIPPST(IDP_BIT_ON);	/* Shading RAMを読むため */
		}
#endif
	}
	else if ((FaxComResult & 0x00ff) == 0x0012) { /** 送信枚数＜指定枚数 */
		/* 枚数指定エラー(T.1.2)の時は排出ローラーに噛んだ最終原稿を排出する */
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
		if (tskno_SCN_STxStoreTask != 0xffff) {
			del_tsk(&tskno_SCN_STxStoreTask);
		}
#endif
		/**	スキャナクローズ (最終原稿を排出)	*/
		if (SCN_Close(SCN_DOC_EXITING) != SCN_DOC_EXIT_OK) {	/**	結果ＮＧ	*/
			/**	原稿排出ＮＧをメインタスクへ通知	*/
			MsgFromFaxComToMain.Item    = FROM_FAXCOM;
			MsgFromFaxComToMain.Message = MSG_FAXCOM_CLOSE_ERROR;
			snd_msg( mbxno.MAN_Task, &MsgFromFaxComToMain );
			rcv_msg( mbxno.FCM_Task, &FcomMsg );
		}
	}
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信の最小伝送時間を得る
	
	@li			
	@param		
	@return		最小伝送時間
	@note		
	@date		2005/07/06 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE FCM_GetIsseiMinScanningTime(
						UBYTE availability,	/* 最小伝送時間能力 */
						UBYTE resolution)	/* 解像度 */

{
	UBYTE time;
	
	switch (availability) {
	case SCAN_MINIMUM_TIME0:
	case SCAN_MINIMUM_TIME5:
	case SCAN_MINIMUM_TIME10:
	case SCAN_MINIMUM_TIME20:
	case SCAN_MINIMUM_TIME40:
		time = availability;
		break;
	case SCAN_MINIMUM_TIME10_2:
		if (resolution == SYS_NORMAL) {
			time = SCAN_MINIMUM_TIME10;
		}
		else {
			time = SCAN_MINIMUM_TIME5;
		}
		break;
	case SCAN_MINIMUM_TIME20_2:
		if (resolution == SYS_NORMAL) {
			time = SCAN_MINIMUM_TIME20;
		}
		else {
			time = SCAN_MINIMUM_TIME10;
		}
		break;
	case SCAN_MINIMUM_TIME40_2:
		if (resolution == SYS_NORMAL) {
			time = SCAN_MINIMUM_TIME40;
		}
		else {
			time = SCAN_MINIMUM_TIME20;
		}
		break;
	default:
		time = SCAN_MINIMUM_TIME20;
		break;
	}
	
	return time;
}

/**************************************************************************************************/
/**
	@brief		DCS送信
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/07 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_SendIsseiDCS(void)
{
	FCM_SetIsseiDCS_FIF(); /* DCS TSIのFIF作成 */
	TxNonStandardFrameByteCount = 0;
	
	MDM_TransmitCommand(); /* DCS送信 */
}

/**************************************************************************************************/
/**
	@brief		DCS+TSIフレーム作成
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/06 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_SetIsseiDCS_FIF(void)
{
	TxID_FrameByteCount = 0;
	TxStandardFrameByteCount = 0;
	
	/**	ＤＣＳのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
	MDM_ModemBuffer[InSTD][0] = ADDRESS_FIELD_DATA;
	MDM_ModemBuffer[InSTD][1] = LAST_FRAME_DATA;
	MDM_ModemBuffer[InSTD][2] = DCS_F;

	if (CheckSubscriberID_Buf() == YES) {		/**	自機ＮＯあり	*/
		/**	ＴＳＩのアドレスフィールド､制御フィールド､ＦＣＦをモデムバッファにセット	*/
		MDM_ModemBuffer[InID][0] = ADDRESS_FIELD_DATA;
		MDM_ModemBuffer[InID][1] = NON_LAST_FRAME_DATA;
		MDM_ModemBuffer[InID][2] = TSI_F;
		SetSubscriberID_Frame(); /* 自機ＮＯをモデムバッファにセット	*/
		TxID_FrameByteCount = 23; /* モデムバッファにセットしたバイト数を大域変数にセット	*/
	}
	
#if 0
//	/*	ＤＣＳＦＩＦビットセット	*/
//	if (DIS_ReceivedFlag == YES) {		/**	ＤＩＳを受信	*/
//		/**	Ｘビットをセット	*/
//		MDM_ModemBuffer[InNS][2] |= X_BIT;
//		MDM_ModemBuffer[InID][2] |= X_BIT;
//		MDM_ModemBuffer[InSTD][2] |= X_BIT;
//	}
#endif
	
	MDM_ModemBuffer[InSTD][3] = BIT_CLEAR; /**	ＤＣＳ ＦＩＦ１バイト目クリア	*/
	MDM_ModemBuffer[InSTD][4] = BIT_CLEAR; /**	Ｔ４ビットセット	*/
	MDM_ModemBuffer[InSTD][4] |= JT_T4_BIT;
	
	/*	試行送信ボーレートセット	*/
	switch (AttemptTxBaudRate) {		/**	試行送信ボーレート	*/
	case BPS2400_V27:	/**	2400BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V27_2400BPS_BIT;
		break;
	case BPS4800_V27:	/**	4800BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V27_4800BPS_BIT;
		break;
	case BPS7200_V29:	/**	V29-7200BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V29_7200BPS_BIT;
		break;
	case BPS9600_V29:	/**	V29-9600BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V29_9600BPS_BIT;
		break;
	case BPS7200_V17:	/**	V17-7200BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_7200BPS_BIT;
		break;
	case BPS9600_V17:	/**	V17-9600BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_9600BPS_BIT;
		break;
	case BPS12000_V17:	/**	V17-12000BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_12000BPS_BIT;
		break;
	case BPS14400_V17	:	/**	V17-14400BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V17_14400BPS_BIT;
		break;
	case  BPS12000_V33:	/**	V33-12000BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V33_12000BPS_BIT;
		break;
	case  BPS14400_V33:	/**	V33-14400BPS	*/
		MDM_ModemBuffer[InSTD][4] |= DATA_V33_14400BPS_BIT;
		break;
	}
	
	MDM_ModemBuffer[InSTD][8] = BIT_CLEAR; /**	DCS FIF ５バイト目クリア	*/
	
	switch (TxMode) {		/**	送信線密度	*/
	case SYS_NORMAL:	/**	ノーマル	*/
		break;
	case SYS_SFINE:	/**	Ｓファイン(R8*15.4mm)､	*/
		MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
		break;
	/* 300*400の送信／ＡＮＺＵ＿Ｌ */
	case SYS_E_HFINE: /** ANZUのE_H-FINEは(300*400)ミリ S-FINEビットON By t.yamaguchi */
		MDM_ModemBuffer[InSTD][8] |= SUPER_FINE_BIT;
		break;
	case SYS_HFINE:	/**	Ｓファイン３(400*400)	*/
		MDM_ModemBuffer[InSTD][8] |= HYPER_FINE_BIT;
		break;
	case SYS_GRAY16:		/**	中間調１６	*/
	case SYS_GRAY16_SEP:	/**	中間調１６_SEP	*/
	case SYS_GRAY32:		/**	中間調３２	*/
	case SYS_GRAY32_SEP:	/**	中間調３２_SEP	*/
	case SYS_GRAY64:		/**	中間調６４	*/
	case SYS_GRAY64_SEP:	/**	中間調６４_SEP	*/
	case SYS_GRAY128:
	case SYS_GRAY128_SEP:
	case SYS_FINE:			/**	ファイン	*/
	case SYS_EFINE: /** E-FINE(R12*11.55L/mm)は、FINEﾋﾞｯﾄＯＮ 96/06/14 By t.yamaguchi */
		MDM_ModemBuffer[InSTD][4] |= SET_FINE_BIT;
		break;
	default:
		break;
	}
	if (TxModeMethod == SYS_INCH) {	/**	インチベース	*/
		MDM_ModemBuffer[InSTD][8] |= INCH_BASE_BIT;
	}
	
	MDM_ModemBuffer[InSTD][6] = BIT_CLEAR; /**	DCS FIF 4 バイト目クリア	*/
	
	switch (TxCodingMethod) {		/**	送信符号化方式	*/
	case SYS_MH_CODE:	/**	ＭＨ	*/
		break;
	case SYS_MR_CODE:	/**	ＭＲ	*/
		MDM_ModemBuffer[InSTD][4] |= SET_MR_BIT;
		break;
	case SYS_MMR_CODE:	/**	ＭＭＲ	*/
		MDM_ModemBuffer[InSTD][6] |= SET_MMR_BIT;
		break;
	case SYS_JBIG_CODE:
		/** ＪＢＩＧビットは最後にセットする	*/
		break;
	}
	
	MDM_ModemBuffer[InSTD][5] = BIT_CLEAR; /**	DCS FIF 3 バイト目クリア	*/
	
	switch (TxWidth) {		/**	送信原稿幅	*/
	case SYS_DOCUMENT_A4_SIZE:	/**	Ａ４	*/
		MDM_ModemBuffer[InSTD][5] |= RX_A4_PAPER_BIT;
		break;
	case SYS_DOCUMENT_B4_SIZE:	/**	Ｂ４	*/
		MDM_ModemBuffer[InSTD][5] |= RX_B4_PAPER_BIT;
		break;
	case SYS_DOCUMENT_A3_SIZE:	/**	Ａ３	*/
		MDM_ModemBuffer[InSTD][5] |= RX_A3_PAPER_BIT;
		break;
	}
	
	switch (FaxTxMaxLength) {		/**	送信原稿長	*/
	case SYS_A4_LENGTH:	/**	Ａ４	*/
		MDM_ModemBuffer[InSTD][5] |= LENGTH_A4_BIT;
		break;
	case SYS_B4_LENGTH:	/**	Ｂ４	*/
		MDM_ModemBuffer[InSTD][5] |= LENGTH_B4_BIT;
		break;
	case SYS_NO_LIMIT:	/**	無限長	*/
		MDM_ModemBuffer[InSTD][5] |= LENGTH_UNLIMITED_BIT;
		break;
	}
	
	switch (TxMinimumScanningTime) {		/**	送信最少伝送時間	*/
	case SCAN_MINIMUM_TIME20:	/**	TIME20ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME20;
		break;
	case SCAN_MINIMUM_TIME40:	/**	TIME40ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME40;
		break;
	case SCAN_MINIMUM_TIME10:	/**	TIME10ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME10;
		break;
	case SCAN_MINIMUM_TIME5:	/**	TIME5ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME5;
		break;
	case SCAN_MINIMUM_TIME0:	/**	TIME0ms	*/
		MDM_ModemBuffer[InSTD][5] |= SCAN_MINIMUM_TIME0;
		break;
	}
	
	MDM_ModemBuffer[InSTD][5] |= EXPAND_FIELD_BIT; /**	拡張ビットON（２４ビット）	*/
	
	MDM_ModemBuffer[InSTD][6] &= ~EXPAND_FIELD_BIT; /**	拡張フィールドOFF（３２ビット）	*/
	
	MDM_ModemBuffer[InSTD][7] = BIT_CLEAR; /**	DCS FIF 5バイト目クリア	*/
	MDM_ModemBuffer[InSTD][7] |= EXPAND_FIELD_BIT; /**	拡張ビットON（４０ビット）	*/
	
	MDM_ModemBuffer[InSTD][8] = BIT_CLEAR; /**	DCS FIF 6 バイト目クリア	*/
	
	TxStandardFrameByteCount = 7; /**	DCSフレーム送信バイト数 7バイトセット	*/
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信のフェーズC
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはFaxTxPhaseC()
	@date		2005/06/16 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiTxPhaseC(void)
{
	FaxComPhaseStatus = FAX_TX_PH_C_BEFORE_PIX;
	TxPageDataSetFlag	= 0; /* ページオープンのフラグを初期化 */
	CodecPageStatus = CDC_READY; /* コーデックステータスを初期化 Aug.18.1994 */
	
	SetTxPageData(); /* 送信ページデータセット */
	SYS_FaxCommStage = FCM_TRANSMIT_SET;
	SendMsgFaxComToMain(MSG_FAXCOM_DISPLAY); /* 表示切替指示(画データ送信中) */
	
	SCN_DecideReductionPattern(); /* 縮小パターンを決定 */
	
	SaveT30TimingData(SYS_T30_START_TIME); /* Ｔ３０モニタ用データセット	*/
	SaveT30Data(SYS_T30_TX_PIX, &MDM_ModemBuffer[0][0], 0);
	FaxComPhaseStatus = FAX_TX_PH_C_PIX;
	
	
	MDM_TxPixOpen(TxBaudRate, ECM_OFF); /* モデムオープン */
	
	TxPageFinishStatus = MDM_TxPix(ECM_OFF, TxSmType);
	
	MDM_TxPixClose(ECM_OFF);
	
	FaxComPhaseStatus = FAX_TX_PH_C_AFTER_PIX;	/* Jun.29.1994 */

	/*--------------------------------------------------*/
	/*	画データ送信結果が「１ページ送信終了」の場合は	*/
	/*	次ページがある可能性があるので，再度セットする	*/
	/*--------------------------------------------------*/
	FCM_TxEndSet();	/* 送信データが残っているか判断する */

	FaxComPhaseStatus = FAX_TX_PH_D;

	if (MDM_PhaseC_Status == TX_DOC_ERR) { /* 原稿エラーの時、ランプ消灯 T.Nose 1997/09/20 */
		LampOff();
	}
}

/**************************************************************************************************/
/**
	@brief		一斉指令送信のフェーズD
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはFaxTxPhaseD()
	@date		2005/06/16 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiTxPhaseD(void)
{
	UpdatePageInformationFlag = 1;
	UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;

	/**	ＥＣＭ送信フレームカウンタにドライバのＥＣＭフレーム数をセット	*/
	/* ECM_FrameCounter = MDM_EcmFrameNumber; */

	/**	送信ＦＣＦをクリア	*/
	TxOptionFCF = 0;
	TxFCF = 0;

	/* メモリ送信最適化処理を実行する為、今送信したページを覚えておきます 1997/06/02  By T.Yamaguchi */
	EraseIndexData.Item = SYS_DocBlock.Index.Item;
	EraseIndexData.No   = SYS_DocBlock.Index.No;
	EraseIndexData.Page = SYS_DocBlock.Index.Page;
	EraseIndexData.BoxNumber = SYS_DocBlock.Index.BoxNumber;

	TxPageFinishStatus = FCM_ResetIsseiTxPageStatus(); /* フェーズＣの結果をフェーズＤ用に変換 */

	switch (TxPageFinishStatus) { /* 画データ送信結果 */
	case	TX_SEPARATE:		/**	原稿長制限オーバー	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage と TxMemoryFilePage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
			TxFCF |= MPS_F;				/**	ＦＣＦにＭＰＳを(orで)セット	*/
		}
		/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		
		MakeHDLC_Frame(TxFCF, TxOptionFCF); /* 指定フレーム作成 */
		MDM_TransmitCommand(); /* 命令送信 */
		
		/* ECM_PageCounter++; */			/**	ＥＣＭページカウンタを＋１	*/
		/* ECM_BlockCounter = 0; */		/**	ＥＣＭブロックカウンタを０クリア	*/
		break;
	case	TX_PAGE_END_MODE_CHANGE:	/**	１ページ終了，モード変更あり	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
			TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Apr.29.1995 */
		}
		else {
			/**	SYS_TxTotalPage と TxMemoryFilePage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOM_F;				/**	ＦＣＦにＥＯＭを(orで)セット	*/
			TxModeChangedFlag = 1;		/**	送信モード変更フラグをセット	*/
			TxRetrainingFlag = 1;		/**	再トレーニングフラグをセット	*/
		}
		/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		
		MakeHDLC_Frame(TxFCF, TxOptionFCF); /* 指定フレーム作成 */
		MDM_TransmitCommand(); /* 命令送信 */
		
		/* ECM_PageCounter++; */			/**	ＥＣＭページカウンタを＋１	*/
		/* ECM_BlockCounter = 0; */		/**	ＥＣＭブロックカウンタを０クリア	*/
		
		UpdateTxPageInformation();			/**	送信ページ番号を更新	*/
		break;
	case	TX_END:		/**	全ページ送信終了	*/
		if (SYS_FaxComStopSwitch() == 1) {	/**	ストップキー入力あり	*/
			TxFCF = EOP_F;				/**	ＦＣＦにＥＯＰをセット	*/
			FaxComPerformingFlag = 0;	/**	通信中フラグをクリア	*/
		}
		else {
			/**	SYS_TxTotalPage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		ｲﾝｸﾘﾒﾝﾄするように変更 By T.Yamaguchi Apr.27'96 */
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOP_F;				/**	ＦＣＦにＥＯＰを(orで)セット	*/
			TxRetrainingFlag = 1;		/**	再トレーニングフラグをセット	*/
		}
		/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
		
		MakeHDLC_Frame(TxFCF, TxOptionFCF); /* 指定フレーム作成 */
		MDM_TransmitCommand(); /* 命令送信 */
		
		FaxTimer(FCM_ISSEI_TX_D_E_TIME);
		
		TxCoverPageFlag = 0; /* カバーページ送信フラグをクリア */
		FaxPhaseE(5); /* 通信終了（ＤＣＮあり） */
		
		/* ECM_PageCounter++; */			/**	ＥＣＭページカウンタを＋１	*/
		/* ECM_BlockCounter = 0; */		/**	ＥＣＭブロックカウンタを０クリア	*/
		/*
		** ディスプレイはTxMemoryFilePage、SYS_TxTotalPageをそのまま表示しているので
		** ページ数 2/1のようになってしまう
		** そこで、ここの処理以降はページ数を表示しないようにSYS_FaxCommStageを変更します
		** by T.Soneoka 1998/01/09
		*/
		SYS_FaxCommStage = FCM_TRANSMIT;
		
		UpdateTxPageInformation();				/**	送信ページ番号を更新	*/
		break;
	case	TX_STOPPED:		/**	ストップキーで停止	*/
		/*----------------------------------------------------------------------*/
		/*	画データ送信中にストップキーが押された場合の処理を変更	Sep.13.1994	*/
		/*		1)	強制終了設定の場合は，即ＤＣＮを送出する					*/
		/*		2)	通常終了の場合は，ＥＯＰを送出し，応答受信する				*/
		/*			(全ページ終了の場合と同じ処理．)							*/
		/*			ページ数はカウントしない						Nov.28.1994	*/
		/*		3)	Ｔ．１．４で終了する  (Oct.18.1994)							*/
		/*----------------------------------------------------------------------*/
		if (CHK_TxForceStop() != 0) {	/**	強制終了する場合 (RTCなし)	*/
			FaxPhaseE( 5 );					/**	ＤＣＮ送出し，通信中フラグをクリア (応答受信しない)	*/
		}
		else {							/**	強制終了しない (RTC付けて正常終了)	*/
			/**	SYS_TxTotalPage を更新するにセット	*/
			UpdateTxPageMode = UPDATE_TOTAL_PAGE | UPDATE_MEMORY_PAGE;			/*		ｲﾝｸﾘﾒﾝﾄするように変更 By T.Yamaguchi Apr.27'96 */
			TxPageDataSetFlag = 0;		/**	送信ページデータセット済みフラグをクリア	*/
			TxFCF |= EOP_F;				/**	ＦＣＦにＥＯＰを(orで)セット	*/
			/* ECM_FrameCounter = MDM_EcmFrameNumber; */	/**	ＥＣＭフレームカウンタにドライバのフレーム数をセット	*/
			
			MakeHDLC_Frame(TxFCF, TxOptionFCF); /* 指定フレーム作成 */
			MDM_TransmitCommand(); /* 命令送信 */
			
			/* ECM_PageCounter++; */			/**	ＥＣＭページカウンタを＋１	*/
			/* ECM_BlockCounter = 0; */		/**	ＥＣＭブロックカウンタを０クリア	*/
		}
		TransmitError( 0x14, 1 );	/**	Ｔ．１．４をセット	*/	/* Oct.18.1994 */
		break;
	case	TX_1M_OVER:		/**	１ｍオーバー	*/
	default:		/**	その他のエラー	*/
		TimerCutStatus = 1;
		FaxPhaseE( 5 );					/**	ＤＣＮ送出し，通信中フラグをクリア	*/
		TransmitError( 0x31, 1 );		/**	Ｔ．３．１をセット	*/
		break;
	}
}

/**************************************************************************************************/
/**
	@brief		フェーズCの結果を再セット
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはResetTxPageFinishStatus()
	@date		2005/07/07 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE FCM_ResetIsseiTxPageStatus(void)
{
	UBYTE ret;
	
	TxModeChangedFlag = 0; /* 送信モード変更フラグをクリア */
	
	if ((TxPageFinishStatus == TX_PAGE_END) || (TxPageFinishStatus == TX_NEXT_FILE)) { 
		/* １ページ終了/１ファイル送信終了、次ファイルあり */
		FCM_CompareIsseiTxMode(); /* 送信モードの変更をチェック */
		ret = TX_PAGE_END_MODE_CHANGE;
		/* ret = TX_PAGE_END; */
	}
	else {
		ret = TxPageFinishStatus;
	}
	
	return ret;
}

/**************************************************************************************************/
/**
	@brief		送信モードの変更をチェック
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはCompareTxMode()
	@date		2005/07/07 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_CompareIsseiTxMode(void)
{
	UWORD file_page;			/**	次ページのファイルナンバー	*/
	UBYTE next_mode, next_size;	/**	次ページのモード，幅	*/
	UBYTE gray_flag_on;
	
	gray_flag_on = 0;
	
	/**	原稿制御ブロックを次ページの情報に更新	*/
	if (TxSmType == TX_CVR) {
		file_page = TxMemoryFilePage;
	}
	else {
		file_page = TxMemoryFilePage + 1;
	}
	
	if (TxPageFinishStatus == TX_NEXT_FILE) {
		file_page = 1;
	}
	GetNextTxPageData(file_page);

	/**	次ページのモードを取り込む (GRAY??はFINEにする)	*/
	next_mode = SYS_DocBlock.Src.Mode;
	gray_flag_on = next_mode;
	switch (next_mode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		/* スキャナ送信 でかつ相手の能力 400DPI ｲﾝﾁ なら H_FINE */
		next_mode = ScanTxGrayMode;
		break;
	default:
		break;
	}

	/**	現ページのモードの SYS_GRAY?? を SYS_FINE にする	*/
	switch (FirstTxMode) {
	case	SYS_GRAY16:
	case	SYS_GRAY16_SEP:
	case	SYS_GRAY32:
	case	SYS_GRAY32_SEP:
	case	SYS_GRAY64:
	case	SYS_GRAY64_SEP:
	case	SYS_GRAY128:
	case	SYS_GRAY128_SEP:
		FirstTxMode = ScanTxGrayMode;
		break;
	default:
		break;
	}

	if ((FirstTxMode != next_mode) && (TxMode != next_mode)) { /* (今送信したモード≠次ページのモード)&&(送信モード≠次ページのモード) */
		TxModeChangedFlag = 1; /* モード変更フラグをセットする */
	}

	/**	次ページのサイズを取り込む	*/
	next_size= SYS_DocBlock.Src.Size;

	if (DocWidth != next_size) {	/**	送信した原稿サイズ≠次ページのサイズ	*/
		/**	モード変更フラグをセットする	*/
		TxModeChangedFlag = 1;
	}

	/**	次ページの原稿モードをセットする	*/
	FirstTxMode = gray_flag_on;/* 中間調表示 Set Gray Too! */
	/**	次ページの原稿サイズをセットする	*/
	DocWidth = next_size;
}

/**************************************************************************************************/
/**
	@brief		一斉指令通信後の会話予約処理
	
	@li			
	@param		
	@return		なし
	@note		オリジナルはMDM_RxVoiceReq()
	@date		2005/07/23 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FCM_IsseiVoiceReq(
				UWORD time) /* ベル鳴動時間(秒) */
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
	t3timer.Time = (time * 100);
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

/* 警察FAX DVT_ID62 Added start by SMuratec 夏 2005/12/08 */ 
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
/* 警察FAX DVT_ID62 Added end by SMuratec 夏 2005/12/08 */ 

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
	/* return (rtn); */
	
	
	
	/* 以下は、RxRequestedVoiceMode()の一部から移植 */
	/* 境界を分かりやすくするため、冗長になっています */
	switch (rtn) {		/**	会話予約結果	*/
	case	TEL1_OH_DETECT:		/**	ＴＥＬ１オフフック検出	*/
	case	TEL2_OH_DETECT:		/**	ＴＥＬ２オフフック検出	*/
	case	HOOK_KEY_OH_DETECT:	/**	オフフックキー検出	*/
		SYS_VoiceCallAccepted = rtn;	/**	会話予約成立(ＯＨ識別)	*/
		/* Sep.16.1994 */
		if (rtn == TEL1_OH_DETECT) {
			FaxTelOffHookTEL1Flag = 1;
		}
		else if (rtn == TEL2_OH_DETECT) {
			FaxTelOffHookTEL2Flag = 1;
		}
		
		/*------------------------------------------*/
		/**	３００msウェイト後，Ｈ／ＬリレーＯＦＦ	*/
		/*------------------------------------------*/
		FaxTimer( 300 );
		FaxTelAutoSWAfterTransaction();
		break;
	default:
		break;
	}
}

#endif /* KEISATSU */

