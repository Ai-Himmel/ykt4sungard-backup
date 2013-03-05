/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_data.c                                                */
/*  作成者       :                                                           */
/*  日  付       : 99/10/06                                                  */
/*  概  要       : モデム制御テーブル                                        */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\message.h"

/*---------------------------------------------------------
**		ＳＣＤから参照されている変数にセクション名をつける
**		By Y.Suzuki 1997/03/07
------------------------------------------------------------*/
#pragma section SCDREF /* ロケート時のセクション名 "DSCDREF" */
struct mdmcntl_t	ModemControl = {0};			/*	モデムバッファコントロール	*/
struct	MEM_ExecData_t	MemoryExecData = {0};	/*	蓄積中指定データ	*/
UDWORD	EncodeDataCount = 0;					/*	エンコードデータ総符号量	*/
UBYTE	CodecPageStatus = 0;					/*	コーデック状態	*/
UWORD	DecodeEcmFrameNum = 0;					/*	デコード済みＥＣＭフレーム番号	*/
UBYTE	TxStartFlag = 0;						/*	送出開始フラグ	*/
UWORD	MDM_RxTotalLine = 0;		/*	受信トータルライン	*/
UWORD	MDM_RxErrorTotalLine = 0;	/*	受信エラートータルラインBy Y.Suzuki 1998/10/07	*/
UWORD	SCDREF_Dummy[8] = {0};					/*	By Y.Suzuki 1998/10/07	*/
#pragma section

#pragma section MDMBUF /* ロケート時のセクション名 "DMDMBUF" */
UBYTE			MDM_ModemBuffer[MODEM_BUFFER_MAX][MODEM_BUFFER_LENGTH] = {0};	/* モデム・バッファ */
#pragma section
UBYTE			MDM_EcmStatus[ECM_STATUS_MAX] = {0};						/* ＥＣＭステータス (256bit) */
UWORD			MDM_RxSize[MODEM_BUFFER_MAX] = {0};							/* 受信フレームサイズ */
UBYTE			MDM_EcmFrameNumber = 0;										/* ＥＣＭフレームナンバー */
UBYTE			MDM_ZX_WriteRAM = 0;										/* ゼロクロス */
UBYTE			MDM_LevelWriteRAM = 0;										/* ゼロクロス */
UBYTE			MDM_PhaseC_Status = 0;										/* フェーズＣ・ステータス */
UBYTE		MDM_RxRTN_Flag = 0;											/* フェーズＣ・ステータス */
UBYTE			MDM_RTC_SeparateFlag = 0;									/* ＲＴＣフレーム間またがり検出フラグ */
UWORD			MDM_RxTotalLineSave[MDM_ERR_LINE_DATA_MAX] = {0};			/* 受信トータルラインセーブ */
UWORD			MDM_RxErrorTotalLineSave[MDM_ERR_LINE_DATA_MAX] = {0};		/* 受信エラートータルラインセーブ */
struct	EcmControl_t	EcmControl = {0};											/* ＥＣＭ・制御 */
UBYTE			MDM_TxLevelSaveValue = 0;										/* 送出レベルのセーブ値 */

/*-------------------------------------------------------------------------
** ソフトコーデックでもMemoryExecDataを使用しているので、
** 通信以外でソフトコーデックを使用している機種(SAKAKI)の場合には、
** PRNとFCMでMemoryExecDataを使用してしまいます。
** FCM/MDMで使用するメモリ管理用変数を別のものします。
** 1998/09/04 H.Yoshikawa
*/
struct	MEM_ExecData_t	MDM_MemoryExecData = {0};	/*	通信用蓄積中指定データ	*/


/************/
/* 通信種別 */
/************/
UBYTE			HighSpeedCheckFlag = 0;
UBYTE			EchoFrameRcvFlag = 0;

/*------------*/
/* タスクＩＤ */
/*------------*/
UWORD				tskno_MDM_ScanTx = 0;
UWORD				tskno_MDM_MemoryTx = 0;
UWORD				tskno_MDM_CharTx = 0;
UWORD				tskno_MDM_EcmRxPrint = 0;
UWORD				tskno_MDM_EcmRxMemory = 0;
UWORD				tskno_MDM_Print = 0;
UWORD				tskno_TxFskControl = 0;	/*	ＦＳＫ送出監視タスク制御用データ	*/
UWORD				tskno_ModemInterrupt = 0;	/*	モデム割り込み監視タスク制御用データ	*/
UWORD				tskno_ModemDMA_TC_Detect = 0;	/*	モデムＶ５３ＤＭＡ割り込み監視タスク制御用データ	*/
UWORD				tskno_RxFrameControl = 0;
UWORD				tskno_T3_Timer = 0;
UWORD				tskno_T1_Timer = 0;
UWORD				tskno_Bell = 0;
UWORD				tskno_ModemStatusCheck = 0;
UWORD				tskno_RxFlagDetect = 0;
UWORD				tskno_Timer1 = 0;
UWORD				tskno_Timer2 = 0;
UWORD				tskno_TimerEqz = 0;
UWORD				tskno_RxPixControl = 0;
UWORD				tskno_RxEcmControl = 0;
UWORD				tskno_DMA_TC_Detect = 0;
UWORD				tskno_FlagDetect = 0;
UWORD				tskno_FcsDetect = 0;
UWORD				tskno_RxDeviceWriteControl = 0;
UWORD				tskno_DecodeDMA_End = 0;
UWORD				tskno_DecodeTimer = 0;
UWORD				tskno_EyeQualityMonitor = 0;
UWORD				tskno_EncodeDMA_End = 0;
UWORD				tskno_CDC_MTxCodeConvertTask = 0;
UWORD				tskno_CDC_CTxCodeConvertTask = 0;
UWORD				tskno_MTxReadDMA_Task = 0;
UWORD				tskno_TimerTCF_End = 0;
UWORD				tskno_TimerEYE_Q = 0;
UWORD				tskno_TimerTCF = 0;
UWORD				tskno_TimerTCF_ReadTime = 0;
UWORD				tskno_TimerTrainingDetect = 0;
UWORD				tskno_TimerRLSD_Detect = 0;
UWORD				tskno_TimerBaudWait = 0;
WORD				tskno_v21_timeup = 0;		/* タイムアップタスク */
WORD				tskno_v21_off = 0;			/* Ｖ２１チャンネル２フラグＯＦＦ検出タスク */
UWORD				tskno_TxEcmControl = 0;
UWORD				tskno_FcsDetectTimer = 0;
UWORD				tskno_TxDMA_TC_Detect = 0;
UWORD				tskno_RxDMA_TC_Detect = 0;
UWORD				tskno_RxFcsDetect = 0;
UWORD				tskno_CcRetrainDetect = 0;	/* CC Retrain By O.Kimoto 1996/05/16 */
UWORD				tskno_MDM_BackupRamToEcmBufTask = 0; /* Ported from ORANGE by H.Kubo 1997/07/16 */
UWORD				tskno_MDM_ModemRecoverTask = 0;	/* Add By O.Kimoto 1998/02/03 */

/* Used with CMN_MultiTimer10msStart() and CMN_MultiTimer10msStop() */
UBYTE				timerID_DummyPixTimer = 0; /* Changed from tskno_DummyPixTimer by H.Kubo 1997/07/14 */
UBYTE				timerID_Timer30sec = 0; /* Changed from tskno_Timer30sec by H.Kubo 1997/07/15 */
UBYTE				timerID_TimerT2 = 0;
UBYTE				timerID_Timer3sec = 0;
UBYTE				timerID_EcmCloseTimer = 0;
UBYTE				timerID_FcsDetectTimer = 0; /* by H.Kubo 1997/12/15 */

/** Global RAM for Modem Interface Memory Access **/
UBYTE			MDM_REG_00_PortStatus = 0;
UBYTE			MDM_REG_01_PortStatus = 0;
UBYTE			MDM_REG_02_PortStatus = 0;
UBYTE			MDM_REG_03_PortStatus = 0;
UBYTE			MDM_REG_04_PortStatus = 0;
UBYTE			MDM_REG_05_PortStatus = 0;
UBYTE			MDM_REG_06_PortStatus = 0;
UBYTE			MDM_REG_07_PortStatus = 0;
UBYTE			MDM_REG_08_PortStatus = 0;
UBYTE			MDM_REG_09_PortStatus = 0;
UBYTE			MDM_REG_0A_PortStatus = 0;
UBYTE			MDM_REG_0B_PortStatus = 0;
UBYTE			MDM_REG_0C_PortStatus = 0;
UBYTE			MDM_REG_0D_PortStatus = 0;
UBYTE			MDM_REG_0E_PortStatus = 0;
UBYTE			MDM_REG_0F_PortStatus = 0;
UBYTE			MDM_REG_10_PortStatus = 0;
UBYTE			MDM_REG_11_PortStatus = 0;
UBYTE			MDM_REG_12_PortStatus = 0;
UBYTE			MDM_REG_13_PortStatus = 0;
UBYTE			MDM_REG_14_PortStatus = 0;
UBYTE			MDM_REG_15_PortStatus = 0;
UBYTE			MDM_REG_16_PortStatus = 0;
UBYTE			MDM_REG_17_PortStatus = 0;
UBYTE			MDM_REG_18_PortStatus = 0;
UBYTE			MDM_REG_19_PortStatus = 0;
UBYTE			MDM_REG_1A_PortStatus = 0;
UBYTE			MDM_REG_1B_PortStatus = 0;
UBYTE			MDM_REG_1C_PortStatus = 0;
UBYTE			MDM_REG_1D_PortStatus = 0;
UBYTE			MDM_REG_1E_PortStatus = 0;
UBYTE			MDM_REG_1F_PortStatus = 0;

/** Global RAM for Modem DSP RAM Access **/
UBYTE			MDM_DSP_RAM_089_Status = 0;
UBYTE			MDM_DSP_RAM_0B3_Status = 0;
UBYTE			MDM_DSP_RAM_10D_Status = 0;
UBYTE			MDM_DSP_RAM_13F_Status = 0;
UBYTE			MDM_DSP_RAM_32A_Status = 0;
UBYTE			MDM_DSP_RAM_3A5_Status = 0;		/* 1996/02/23 Y.M */

UWORD					MDM_DSP_RAM_031_Status = 0;
UWORD					MDM_DSP_RAM_38F_Status = 0;
UWORD					MDM_DSP_RAM_3DF_Status = 0;
UWORD					MDM_DSP_RAM_C0E_Status = 0;
UBYTE			MDM_V8_StatusStatus[3] = {0};
UBYTE			MDM_V8_ControlStatus[7] = {0};
UBYTE			EQMAveragingBuffer[4] = {0};
UWORD 					MDM_SymbolRate = 0;
UWORD					ARAThresholdBuffer[16] = {0};
UBYTE			MDM_AbortCode = 0;

/*------------------------------*/
/*	Ｖ５３で使用している変数	*/
/*------------------------------*/
UBYTE			CommunicateType = 0;	/*	送受信・スキャナ／メモリ種別	*/
UWORD					CarryDownBlock = 0;	/*	キャリアダウンとみなすブロック数 		*/
struct mdmblk_t			ModemBlock = {0};	/*	モデムＩ／Ｆブロック	*/
UBYTE			ModemZeroBuffer[256] = {0};	/*	ゼロ送出用ワークバッファ	*/
UBYTE			ModemRxStatus = 0;	/*	モデムバッファ受信状態	*/
UBYTE			EchoFCF = 0;	/*	エコーフレーム	*/
UBYTE			FaxComTxFrame[MODEM_BUFFER_LENGTH] = {0};	/*	ＥＣＭ受信フレーム一時待避用バッファ	*/
UWORD					ModemWaitStatus = 0;	/* モデムステータス待ちビットパターン	*/
UWORD					RxFrameLength = 0;	/*	受信フレームデータ数	*/
MESSAGE_t					ModemMessage = {0};	/*	モデム汎用メッセージデータ	*/
MESSAGE_t					DecodeMessage = {0};	/*	１ブロックデコード終了メッセージ用	*/
MESSAGE_t					CodecMessage = {0};		/*	１ページ受信完了メッセージ用	*/
MESSAGE_t					MemWriteMessage = {0};	/*	メモリ受信メモリオーバメッセージ用	*/
MESSAGE_t					FlagDetectMessage = {0};	/*	フラグ検出メッセージ用	*/
MESSAGE_t					FcsDetectMessage = {0};	/*	フレーム検出メッセージ用	*/
MESSAGE_t					FrameDetectMessage = {0};	/*	フレーム検出完了メッセージ用	*/
MESSAGE_t					TxFrameEndMessage = {0};	/*	送信フレーム送出完了メッセージ用	*/
UBYTE			BreakEcmTaskFlag = 0;	/*	ＥＣＭ受信コントロールタスク有無フラグ	*/
UWORD					Pix_H_Reduction = 0;	/*	主走査縮小率	*/
UWORD					Pix_V_Reduction = 0;	/*	副走査縮小率	*/
UBYTE			ModemDMA_TC_Flag = 0;	/*	モデムＤＭＡ終了割り込み有無フラグ	*/
UBYTE			ModemInterruptFlag = 0;	/*	モデム割り込み有無フラグ	*/
UWORD					RxFskTimer = 0;	/*	ＦＳＫ受信タイムアウト	*/
UDWORD			RemainEncodeData = 0;	/*	残りエンコードデータ数	*/
struct MEM_StoreData_t	RxMemoryStoreData = {0};	/* 蓄積時に指定するデータ */
UDWORD			EcmBufferBaseWritePoint = 0;	/*	ＥＣＭバッファ開始アドレス	*/
UBYTE			ServiceFuncTx = 0;	/*	サービスファンクション用高速／低速信号切り替えＳｗ	*/
UBYTE			MDM_TxStopSwFlag = 0;	/*	送信ストップ制御用フラグ	*/
UBYTE			BreakRxTaskCompleteFlag = 0;	/*	ＥＣＭ受信コントロールタスク終了完了フラグ	*/
UBYTE			GetCodecFlag = 0;	/*	コーデック獲得有無フラグ	*/
UBYTE			LastEcmFrameNumber = 0;	/*	ＥＣＭ送出最終フレーム番号	*/
UWORD					LastEcmFrameLength = 0;	/*	ＥＣＭ送出最終フレームデータ数*/
UWORD					EncInpStatus = 0;	/*	縮小率設定用入力画素数（ワード）	*/
UWORD					EncOtpStatus = 0;	/*	縮小率設定用出力画素数（ワード）	*/
UWORD					MDM_EncodeLine = 0;	/*	エンコードライン設定	*/
UWORD					MDM_Yd_Line = 0;	/*	ＪＢＩＧ Ｙｄライン設定	*/
UBYTE			TxCompleteEventFlag = 0;	/*	画データ送出完了割り込み有無フラグ	*/
UWORD					DebugDMA_EncodeStopCounter = 0;	/*	位相ずれ用スキャナモータ停止用カウンタ	*/
UBYTE			PixRxSpeed = 0;	/*	短縮ハンドシェーク用受信スピード	*/
UBYTE			DMA_TailStart = 0;	/*	ＥＣＭ受信分割ＤＭＡ制御用フラグ	*/
UBYTE			ModemStatusFlag = 0;	/*	１０ｍｓ割り込みモデムステータス有効フラグ	*/
UWORD					MDM_TxEncodeLine = 0;	/*	送出済み符号化データライン数	*//* No Use */
UWORD					MDM_Tx1BlockEncodeLine = 0;	/*	１ブロック符号化データライン数	*//* No Use */
UBYTE			CodecRestartFlag = 0;

UBYTE			MDM_LastData = 0;	/** ＨＤＬＣモード時の最終データ処理用変数 **/
UBYTE			MDM_DmaStart = 0;	/** For Debug By O.K Jan.25,1996 **/

UBYTE 			dbg_old_cts_status = 0;	/** for Debug **/
UBYTE 			dbg_new_cts_status = 0;	/** for Debug **/
UBYTE 			dbg_old_rlsd_status = 0;	/** for Debug **/
UBYTE 			dbg_new_rlsd_status = 0;	/** for Debug **/

UBYTE			MDM_CtsTurnOffFlag = 0;	/**  By O.K Feb.05,1996 **/
UBYTE			MDM_CtsTurnOnFlag = 0;		/**  By O.K Feb.05,1996 **/
UBYTE			MDM_CtsTurnOffCheckFlag = 0;	/**  By O.K Feb.05,1996 **/
UBYTE			MDM_RlsdTurnOffFlag = 0;	/**  By O.K Feb.05,1996 **/
UBYTE			MDM_RlsdTurnOnFlag = 0;		/**  By O.K Feb.05,1996 **/
UBYTE			MDM_RlsdTurnOffCheckFlag = 0;	/**  By O.K Feb.05,1996 **/
UBYTE			MDM_RlsdTurnOnCheckFlag = 0;	/**  By O.K Feb.05,1996 **/

UWORD					MDM_EQM_Value = 0;	/* Add for EQM By O.K Feb.22,1996 */

UBYTE			MDM_OldSecTxb = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewSecTxb = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_OldSecRxb = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewSecRxb = 0x00;	/*  By O.Kimoto 1996/02/28 */

UBYTE			MDM_OldDtrStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewDtrStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_OldRlsdStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewRlsdStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_OldCtsStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewCtsStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_OldRtsStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewRtsStatus = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_OldT30Status = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			MDM_NewT30Status = 0x00;	/*  By O.Kimoto 1996/02/28 */

UDWORD			MDM_ModemInternalStatusTimer = 0x00; 	/*  by O.Kimoto 1996/04/11 */
UWORD					MDM_ModemInternalStatusCounter = 0x00;	/*  By O.Kimoto 1996/02/28 */
UBYTE			ControlChannelRetrainFlag = 0;	/* CC Retrain By O.Kimoto 1996/05/16 */
UBYTE			MDM_ClearToSendAbort = 0;			/* CTSがONしなかった 1996/05/17 Y.Murata */
UBYTE			MDM_RetrainFirstCCTrainFlag = 0;	/* １ｓｔＣＣでリトレインが発生したかどうかのフラグ By O.Kimoto 1996/08/14 */
UWORD					MDM_CarrierDropoutTimer = 0;	/* キャリアがなくなった事を計測するタイマー By O.Kimoto 1996/09/10 */
UBYTE			MDM_CarrierDropoutFlag = 0;	/* キャリアがなくなった事を示すフラグ By O.Kimoto 1996/09/10 */
UBYTE			MDM_FedOffFlag = 0;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */

UWORD					MDM_RxTcfEyeAverage = 0;	/* T30 TCF EQM Average 1996/10/23 Y.Murata */
UWORD					BackUpEYE_Slice = 0;		/* T30 比較したﾃｰﾌﾞﾙ値 1996/10/25 Y.M */
UBYTE			MDM_DropOutRecovryV17V29 = 0;	/* 1996/10/31 Y.Murata */
UBYTE			MDM_PixStartFlag = 0;	/* For Control RTDIS By O.Kimoto 1996/12/09 */
UBYTE			MDM_AlreadyRtdisSetFlag = 0;	/* For Control RTDIS By O.Kimoto 1996/12/09 */

/* 工場ファンクションタスクＩＤ追加 1996/12/11 Y.M */
UWORD					tskno_MDM_FskTest = 0;
UWORD					tskno_MDM_PixTest = 0;
UBYTE			MDM_FactoryFskMenu = 0;
struct ServiceFuncPixData_t 	FactoryPixData = {0};

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
UWORD					tskno_MDM_VoiceTest = 0;
 #endif
#endif

UBYTE			MDM_OldFedStatus = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_NewFedStatus = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_OldPndetStatus = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_NewPndetStatus = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_OldPnsucStatus = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_NewPnsucStatus = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_OldDmy4Status = 0x00;	/*  By O.Kimoto 1996/12/20 */
UBYTE			MDM_NewDmy4Status = 0x00;	/*  By O.Kimoto 1996/12/20 */

UBYTE			MDM_OldFeStatus = 0x00;		/*  By H.Kubo  1997/08/28 */
UBYTE			MDM_NewFeStatus = 0x00;		/*  By H.Kubo  1996/08/28 */


UBYTE			MDM_FirstV21Ch2FlagReceive = 0;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
UBYTE			MDM_ReceiveLevelExtension = 0;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
UWORD			MDM_V21MeasureReceiveLevel = 0;
UWORD			MDM_V21MeasureStartGo = 0;
UWORD			MDM_NoCarryOrErrorCount = 0;	/* EOL又はｴﾗｰがあったﾌﾞﾛｯｸ(G3) 1997/01/31 Y.Murata */
UWORD			MDM_CurrentTotalErrorLine = 0;	/* 1997/01/31 Y.Murata */
UWORD			MDM_CurrentDecodeLine = 0;		/* 1997/02/01 Y.Murata */
UWORD			MDM_CurrentDecodeErrorLine = 0;	/* 1997/02/01 Y.Murata */
UBYTE			MDM_FskModeFlag = 0;			/* 1997/02/06 Y.Murata */
UBYTE			MDM_FskFcsTimeOutFlag = 0;		/* 1997/02/08 Y.Murata */

UDWORD 			MDM_OptionTTiSize = 0x00000000;	/* Add By O.Kimoto 1997/02/25 */

UDWORD			BackUpDataLength = 0;	/* 高速ＲＤＳデータライト時のバックアップデータ長 */


/* Flags to indicate that DMA transfer is finished. Written by H.Kubo 1997/07/18 */
/*+++++ This part should be modified according to the configuration of DMA channel allocation. ++++++*/
/* [Note for POPLAR ]
** Though scanner CODEC to memory transfer is done by external DMAC and its virtual DMA channel is
** allocated to 4, interrupt handler to catch end of tranfer sets DMA0_TC0_Flag. :-<
** The reason for nasty naming of DMA0_TC2Flag is the same.
** So I decided to use new flags.
*/
/* refer to mdm_int.c */
int 			IsModemToMemoryXferDone = 0;
int				IsMemoryToModemXferDone = 0;

/* Ported from ORANGE by H.Kubo 1997/09/08 */
/* ECM 受信ループ対策 */
UWORD			MDM_ResetCounter = 0; /* 96.2.13 for ＥＣＭ受信中ループ */

UBYTE			MDM_TrueConfValue = 0;	/** Add By O.Kimoto 1997/12/02 */

/* Ported from CLOVER by H.Kubo 1997/12/24 */
UBYTE			MDM_RTH_ControlStatus = 0;	/* 1997/12/22 RTH_CONTROL */

UBYTE			MDM_G3DummyDataDetecting = 0;	/* 1997/12/25 */

UWORD			MDM_RecoverStatus = 0;			/* Add By O.Kimoto 1998/02/03 */
UWORD			MDM_BackupRecoverStatus = 0;	/* Add By O.Kimoto 1998/02/03 */

UBYTE			MDM_V34_CC_RetrainTimeCutFlag = 0;	/* 1997/10/07 Y.Murata */ /* Ported from Clover by H.Kubo 1998/02/03 */
UBYTE			MDM_ForcedDecodeStart = 0;	/*  追加 by T.Soneoka 1998/03/02 */
UBYTE			IsDetLastFrameEndMaker = 0;	/*  追加 by T.Soneoka 1998/03/02 */
UBYTE			IsDetEndMaker = 0;	/*  追加 by T.Soneoka 1998/03/02 */

#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
UWORD			MDM_ModemDmaSize = 0; /* 受信時データを DMA でモデムバッファに一度に転送するバイト数。モデムをオープンした後はクローズするまで変更しないこと。 */
UBYTE 			MDM_ModemBufferFirstPoint = 0; /* モデムバッファの先頭のインデックス。 モデムをオープンした後はクローズするまで変更しないこと。 */
#endif

UBYTE			IsMemoryOpen = 0;	/* 1998/05/15 by T.Soneoka */

UBYTE	MDM_ND_WaitFirstDataEvent = 0;
UWORD tskno_V23RlsdTimer = 0; /* added by H.Kubo 1998/11/11 */
UWORD MDM_V23_ModemRecoverRunning = 0; /* added by H.Kubo 1998/11/11 */

/* 
** R288F VERSION 22P以上
** Condition changd by H.Kubo 1998/10/17
*/
/* モデム割り込みでＥＣＭ受信のとき、*/
UBYTE	IsRlsdAndRdbfOn = 0;	/* 1998/10/09 By H.Hirao */

/*
** R288F VERSION 24P以上
** by H.Kubo 1998/10/30
*/
UBYTE 	MDM_PreviousPCOFF_Status = 0;	/* H.Kubo 1998/10/30 */

UBYTE	MDM_MemReadStatus = 0;

/*
** R288F VERSION 22P以上
** added by H.Kubo 1998/11/10
*/
struct MDM_ModemStatusRegister_t  MDM_CurrentModemRegister = {0};
struct MDM_ModemStatusRegister_t  MDM_PreviousModemRegister = {0};
struct MDM_ModemStatusRegister_t  MDM_ReviewRegister = {0};

/*
** フレーム間フラグが短くてモデムがフラグを取り逃がしたときの救済用。
** H.Kubo 1999/01/22
*/
UBYTE	MDM_EcmRxFcsCheckRequest = 0; /* 8bit 幅の変数。各ビットがモデムバッファ一本に対応する。 */

UWORD	MDM_LineDecodeStartTimer = 0;	/* １ラインの受信時間を測定するためのタイマー ＤＥＵ仕様 */

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* added by H.Kubo 1999/06/25  */
/* V29 9600bps 受信対策用。 by H.Kubo 1999/06/25 */
UBYTE MDM_CurrentFilterType = 0;
#endif

UWORD	Rx3mErrorLine = 0; /* 3m over Rx by H.Kubo 1999/09/14 */


#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
UBYTE	MDM_EcmBufferOverEncodeStop = 0;	/* ＥＣＭﾊﾞｯﾌｧ超えたでフラグ 1997/11/20 */
UBYTE	MDM_2ndEcmBufferReamin = 0;			/* 1997/11/21 */
UDWORD	MDM_EcmRemainCount = 0;				/* 1997/11/21 */
UBYTE	MDM_RTC_DetectStatusStopReq = 0;	/* 1997/11/29 */
UWORD	MDM_R33Timer1 = 0;					/* 1997/12/10 debug */
UWORD	MDM_R33Timer2 = 0;					/* 1997/12/10 debug */
UDWORD	MDM_DebugRxCount = 0;				/* 1997/12/13 debug */
#endif	

/* #if defined(POPLAR_F) *//* 1999/10/21 m.matsumoto */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
UWORD	   tskid_VoiceTimeUpTask = 0;
UWORD	   tskid_NAR_DetectTask = 0;
UBYTE	   BackUpCodecPageStatus = 0;		/*	コーデック状態を保存 for debug	*/
UWORD	   MDM_StxLoopCounter = 0;			/* 2000/02/04 Y.Murata */

UBYTE	MDM_IsSingleToneON = 0;		/* WAYARAより移植 by O.Kimoto 2002/11/14 */

 #endif
#endif

#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) /* By M.Maeda 2002/09/18 */  || (defined(POPLAR_H) && defined(JP1))	/* 55転送 By O.Kimoto 2003/02/05 */
UWORD	BackupReceiveLevel = 0; /* 2000/12/12 by K.Okada */
#endif
