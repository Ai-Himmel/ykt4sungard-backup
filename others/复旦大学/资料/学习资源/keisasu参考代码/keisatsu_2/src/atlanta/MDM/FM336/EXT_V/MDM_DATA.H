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
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mem_def.h"

extern UBYTE					MDM_ModemBuffer[MODEM_BUFFER_MAX][MODEM_BUFFER_LENGTH];	/* モデム・バッファ */
extern UBYTE					MDM_EcmStatus[ECM_STATUS_MAX];							/* ＥＣＭステータス (256bit) */
extern UWORD					MDM_RxTotalLine ;										/* 受信トータルライン */
extern UWORD					MDM_RxErrorTotalLine ;									/* 受信エラートータルライン */
extern UWORD					MDM_RxSize[MODEM_BUFFER_MAX];							/* 受信フレームサイズ */
extern UBYTE					MDM_EcmFrameNumber;										/* ＥＣＭフレームナンバー */
extern UBYTE					MDM_ZX_WriteRAM;										/* ゼロクロス */
extern UBYTE					MDM_LevelWriteRAM;										/* ゼロクロス */
extern UBYTE					MDM_PhaseC_Status;										/* フェーズＣ・ステータス */
extern UBYTE					MDM_RxRTN_Flag;											/* フェーズＣ・ステータス */
extern UBYTE					MDM_RTC_SeparateFlag;									/* ＲＴＣフレーム間またがり検出フラグ */
extern UWORD					MDM_RxTotalLineSave[MDM_ERR_LINE_DATA_MAX];				/* 受信トータルラインセーブ */
extern UWORD					MDM_RxErrorTotalLineSave[MDM_ERR_LINE_DATA_MAX];		/* 受信エラートータルラインセーブ */
extern struct	EcmControl_t	EcmControl;												/* ＥＣＭ・制御 */
extern UBYTE					MDM_TxLevelSaveValue;									/* 送出レベルのセーブ値 */

/*-------------------------------------------------------------------------
** ソフトコーデックでもMemoryExecDataを使用しているので、
** 通信以外でソフトコーデックを使用している機種(SAKAKI)の場合には、
** PRNとFCMでMemoryExecDataを使用してしまいます。
** FCM/MDMで使用するメモリ管理用変数を別のものします。
** 1998/09/04 H.Yoshikawa
*/
extern struct	MEM_ExecData_t	MDM_MemoryExecData;	/*	通信用蓄積中指定データ	*/

/************/
/* 通信種別 */
/************/
extern UBYTE			HighSpeedCheckFlag;
extern UBYTE			EchoFrameRcvFlag;

/*------------*/
/* タスクＩＤ */
/*------------*/
extern UWORD				tskno_MDM_ScanTx;
extern UWORD				tskno_MDM_MemoryTx;
extern UWORD				tskno_MDM_CharTx;
extern UWORD				tskno_MDM_EcmRxPrint;
extern UWORD				tskno_MDM_EcmRxMemory;
extern UWORD				tskno_MDM_Print;
extern UWORD				tskno_TxFskControl;	/*	ＦＳＫ送出監視タスク制御用データ	*/
extern UWORD				tskno_ModemInterrupt;	/*	モデム割り込み監視タスク制御用データ	*/
extern UWORD				tskno_ModemDMA_TC_Detect;	/*	モデムＶ５３ＤＭＡ割り込み監視タスク制御用データ	*/
extern UWORD				tskno_RxFrameControl;
extern UWORD				tskno_T3_Timer;
extern UWORD				tskno_T1_Timer;
extern UWORD				tskno_Bell;
extern UWORD				tskno_ModemStatusCheck;
extern UWORD				tskno_RxFlagDetect;
extern UWORD				tskno_Timer1;
extern UWORD				tskno_Timer2;
extern UWORD				tskno_TimerEqz;
extern UWORD				tskno_RxPixControl;
extern UWORD				tskno_RxEcmControl;
extern UWORD				tskno_DMA_TC_Detect;
extern UWORD				tskno_FlagDetect;
extern UWORD				tskno_FcsDetect;
extern UWORD				tskno_RxDeviceWriteControl;
extern UWORD				tskno_DecodeDMA_End;
extern UWORD				tskno_DecodeTimer;
extern UWORD				tskno_EyeQualityMonitor;
extern UWORD				tskno_EncodeDMA_End;
extern UWORD				tskno_CDC_MTxCodeConvertTask;
extern UWORD				tskno_CDC_CTxCodeConvertTask;
extern UWORD				tskno_MTxReadDMA_Task;
extern UWORD				tskno_TimerTCF_End;
extern UWORD				tskno_TimerEYE_Q;
extern UWORD				tskno_TimerTCF;
extern UWORD				tskno_TimerTCF_ReadTime;
extern UWORD				tskno_TimerTrainingDetect;
extern UWORD				tskno_TimerRLSD_Detect;
extern UWORD				tskno_TimerBaudWait;
extern UWORD				tskno_v21_timeup;		/* タイムアップタスク */
extern UWORD				tskno_v21_off;			/* Ｖ２１チャンネル２フラグＯＦＦ検出タスク */
extern UWORD				tskno_TxEcmControl;
extern UWORD				tskno_TxDMA_TC_Detect;
extern UWORD				tskno_RxDMA_TC_Detect;
extern UWORD				tskno_RxFcsDetect;
extern UWORD				tskno_CcRetrainDetect;	/* CC Retrain By O.Kimoto 1996/05/16 */
extern	UWORD				tskno_MDM_BackupRamToEcmBufTask; /* Ported from ORANGE modem by H.Kubo 1997/07/16 */
extern UWORD				tskno_MDM_ModemRecoverTask;	/* Add By O.Kimoto 1998/02/03 */

extern UBYTE				timerID_DummyPixTimer; /* Changed from tskno_DummyPixTimer by H.Kubo 1997/07/14 */
extern UBYTE				timerID_Timer30sec; /* Changed from tskno_Timer30sec by H.Kubo 1997/07/15 */
extern UBYTE				timerID_TimerT2; /* by H.Kubo 1997/07/15 */
extern UBYTE				timerID_Timer3sec; /* by H.Kubo 1997/07/15 */
extern UBYTE				timerID_EcmCloseTimer; /* by H.Kubo 1997/12/15 */
extern UBYTE				timerID_FcsDetectTimer; /* by H.Kubo 1997/12/15 */

/** Global RAM for Modem Interface Memory Access **/
extern UBYTE			MDM_REG_00_PortStatus;
extern UBYTE			MDM_REG_01_PortStatus;
extern UBYTE			MDM_REG_02_PortStatus;
extern UBYTE			MDM_REG_03_PortStatus;
extern UBYTE			MDM_REG_04_PortStatus;
extern UBYTE			MDM_REG_05_PortStatus;
extern UBYTE			MDM_REG_06_PortStatus;
extern UBYTE			MDM_REG_07_PortStatus;
extern UBYTE			MDM_REG_08_PortStatus;
extern UBYTE			MDM_REG_09_PortStatus;
extern UBYTE			MDM_REG_0A_PortStatus;
extern UBYTE			MDM_REG_0B_PortStatus;
extern UBYTE			MDM_REG_0C_PortStatus;
extern UBYTE			MDM_REG_0D_PortStatus;
extern UBYTE			MDM_REG_0E_PortStatus;
extern UBYTE			MDM_REG_0F_PortStatus;
extern UBYTE			MDM_REG_10_PortStatus;
extern UBYTE			MDM_REG_11_PortStatus;
extern UBYTE			MDM_REG_12_PortStatus;
extern UBYTE			MDM_REG_13_PortStatus;
extern UBYTE			MDM_REG_14_PortStatus;
extern UBYTE			MDM_REG_15_PortStatus;
extern UBYTE			MDM_REG_16_PortStatus;
extern UBYTE			MDM_REG_17_PortStatus;
extern UBYTE			MDM_REG_18_PortStatus;
extern UBYTE			MDM_REG_19_PortStatus;
extern UBYTE			MDM_REG_1A_PortStatus;
extern UBYTE			MDM_REG_1B_PortStatus;
extern UBYTE			MDM_REG_1C_PortStatus;
extern UBYTE			MDM_REG_1D_PortStatus;
extern UBYTE			MDM_REG_1E_PortStatus;
extern UBYTE			MDM_REG_1F_PortStatus;

/** Global RAM for Modem DSP RAM Access **/
extern UBYTE			MDM_DSP_RAM_089_Status;
extern UBYTE			MDM_DSP_RAM_0B3_Status;
extern UBYTE			MDM_DSP_RAM_10D_Status;
extern UBYTE			MDM_DSP_RAM_13F_Status;
extern UBYTE			MDM_DSP_RAM_32A_Status;
extern UBYTE			MDM_DSP_RAM_3A5_Status;		/* 1996/02/23 Y.M */

extern UWORD					MDM_DSP_RAM_031_Status;
extern UWORD					MDM_DSP_RAM_38F_Status;
extern UWORD					MDM_DSP_RAM_3DF_Status;
extern UWORD					MDM_DSP_RAM_C0E_Status;
extern UBYTE			MDM_V8_StatusStatus[3];
extern UBYTE			MDM_V8_ControlStatus[7];
extern UBYTE			EQMAveragingBuffer[4];
extern UWORD 					MDM_SymbolRate;
extern UWORD					ARAThresholdBuffer[16];
extern UBYTE			MDM_AbortCode;



/*------------------------------*/
/*	Ｖ５３で使用している変数	*/
/*------------------------------*/
extern UBYTE			CommunicateType;					/*	送受信・スキャナ／メモリ種別	*/
extern UWORD					CarryDownBlock;						/*	キャリアダウンとみなすブロック数 		*/
extern struct mdmblk_t			ModemBlock;							/*	モデムＩ／Ｆブロック	*/
extern struct mdmcntl_t			ModemControl;						/*	モデムバッファコントロール	*/
extern struct MEM_ExecData_t 		MemoryExecData;						/*	蓄積中指定データ	*/
extern struct MEM_StoreData_t		RxMemoryStoreData;						/* 蓄積時に指定するデータ */
extern UBYTE			ModemZeroBuffer[256];				/*	ゼロ送出用ワークバッファ	*/
extern UBYTE			ModemRxStatus;						/*	モデムバッファ受信状態	*/
extern UBYTE			EchoFCF;							/*	エコーフレーム	*/
extern UBYTE			FaxComTxFrame[MODEM_BUFFER_LENGTH];	/*	ＥＣＭ受信フレーム一時待避用バッファ	*/
extern UWORD					ModemWaitStatus;					/* モデムステータス待ちビットパターン	*/
extern UWORD					RxFrameLength;						/*	受信フレームデータ数	*/
extern UDWORD			EncodeDataCount;					/*	エンコードデータ総符号量	*/
extern MESSAGE_t					ModemMessage;						/*	モデム汎用メッセージデータ	*/
extern MESSAGE_t					DecodeMessage;						/*	１ブロックデコード終了メッセージ用	*/
extern MESSAGE_t					CodecMessage;						/*	１ページ受信完了メッセージ用	*/
extern MESSAGE_t					MemWriteMessage;					/*	メモリ受信メモリオーバメッセージ用	*/
extern MESSAGE_t					FlagDetectMessage;					/*	フラグ検出メッセージ用	*/
extern MESSAGE_t					FcsDetectMessage;					/*	フレーム検出メッセージ用	*/
extern MESSAGE_t					FrameDetectMessage;					/*	フレーム検出完了メッセージ用	*/
extern MESSAGE_t					TxFrameEndMessage;					/*	送信フレーム送出完了メッセージ用	*/
extern UBYTE			BreakEcmTaskFlag;					/*	ＥＣＭ受信コントロールタスク有無フラグ	*/
extern UWORD					Pix_H_Reduction;					/*	主走査縮小率	*/
extern UWORD					Pix_V_Reduction;					/*	副走査縮小率	*/
extern UBYTE			CodecPageStatus;					/*	コーデック状態	*/
extern UBYTE			ModemDMA_TC_Flag;					/*	モデムＤＭＡ終了割り込み有無フラグ	*/
extern UBYTE			ModemInterruptFlag;					/*	モデム割り込み有無フラグ	*/
extern UWORD					RxFskTimer;							/*	ＦＳＫ受信タイムアウト	*/
extern UDWORD			RemainEncodeData;					/*	残りエンコードデータ数	*/
extern UBYTE			TxStartFlag;						/*	送出開始フラグ	*/
extern UDWORD			EcmBufferBaseWritePoint;			/*	ＥＣＭバッファ開始アドレス	*/
extern UWORD					DecodeEcmFrameNum;					/*	デコード済みＥＣＭフレーム番号	*/
extern UBYTE			ServiceFuncTx;						/*	サービスファンクション用高速／低速信号切り替えＳｗ	*/
extern UBYTE			MDM_TxStopSwFlag;					/*	送信ストップ制御用フラグ	*/
extern UBYTE			BreakRxTaskCompleteFlag;			/*	ＥＣＭ受信コントロールタスク終了完了フラグ	*/
extern UBYTE			GetCodecFlag;						/*	コーデック獲得有無フラグ	*/
extern UBYTE			LastEcmFrameNumber;					/*	ＥＣＭ送出最終フレーム番号	*/
extern UWORD					LastEcmFrameLength;					/*	ＥＣＭ送出最終フレームデータ数*/
extern UWORD					EncInpStatus;						/*	縮小率設定用入力画素数（ワード）	*/
extern UWORD					EncOtpStatus;						/*	縮小率設定用出力画素数（ワード）	*/
extern UWORD					MDM_EncodeLine;						/*	エンコードライン設定	*/
extern UWORD					MDM_Yd_Line;						/*	ＪＢＩＧ Ｙｄライン設定	*/
extern UBYTE			TxCompleteEventFlag;				/*	画データ送出完了割り込み有無フラグ	*/
extern UWORD					DebugDMA_EncodeStopCounter;			/*	位相ずれ用スキャナモータ停止用カウンタ	*/
extern UBYTE			PixRxSpeed;							/*	短縮ハンドシェーク用受信スピード	*/
extern UBYTE			DMA_TailStart;						/*	ＥＣＭ受信分割ＤＭＡ制御用フラグ	*/
extern UBYTE			ModemStatusFlag;					/*	１０ｍｓ割り込みモデムステータス有効フラグ	*/
extern UWORD					MDM_TxEncodeLine;					/*	送出済み符号化データライン数	*/
extern UWORD					MDM_Tx1BlockEncodeLine;				/*	１ブロック符号化データライン数	*/
extern UBYTE			CodecRestartFlag;
extern UBYTE			MDM_LastData;						/** ＨＤＬＣモード時の最終データ処理用変数 **/

extern char	far				EcmBuffer[ECM_BUFFER_MAX][ECM_BUFFER_LENGTH]; /* T.Soneoka '94.5.18 */
extern char	far				EcmBuffer2[ECM_BUFFER_MAX][ECM_BUFFER_LENGTH]; /* ECM_BUFFER_OVER */

extern UBYTE			MDM_DmaStart;	/** For Debug By O.K Jan.25,1996 **/

extern UBYTE 			dbg_old_cts_status;	/** for Debug **/
extern UBYTE 			dbg_new_cts_status;	/** for Debug **/
extern UBYTE 			dbg_old_rlsd_status;	/** for Debug **/
extern UBYTE 			dbg_new_rlsd_status;	/** for Debug **/

extern UBYTE			MDM_CtsTurnOffFlag;			/**  By O.K Feb.05,1996 **/
extern UBYTE			MDM_CtsTurnOnFlag;			/**  By O.K Feb.05,1996 **/
extern UBYTE			MDM_CtsTurnOffCheckFlag;	/**  By O.K Feb.05,1996 **/
extern UBYTE			MDM_RlsdTurnOffFlag;		/**  By O.K Feb.05,1996 **/
extern UBYTE			MDM_RlsdTurnOnFlag;			/**  By O.K Feb.05,1996 **/
extern UBYTE			MDM_RlsdTurnOffCheckFlag;	/**  By O.K Feb.05,1996 **/
extern UBYTE			MDM_RlsdTurnOnCheckFlag;	/**  By O.K Feb.05,1996 **/
extern UWORD					MDM_EQM_Value;				/* Add for EQM By O.K Feb.22,1996 */

extern UBYTE			MDM_OldSecTxb;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewSecTxb;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_OldSecRxb;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewSecRxb;	/*  By O.Kimoto 1996/02/28 */
extern UWORD					MDM_ModemInternalStatusCounter;	/*  By O.Kimoto 1996/02/28 */

extern UBYTE			MDM_OldDtrStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewDtrStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_OldRlsdStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewRlsdStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_OldCtsStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewCtsStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_OldRtsStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewRtsStatus;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_OldT30Status;	/*  By O.Kimoto 1996/02/28 */
extern UBYTE			MDM_NewT30Status;	/*  By O.Kimoto 1996/02/28 */
 
extern UDWORD			MDM_ModemInternalStatusTimer; 	/*  by O.Kimoto 1996/04/11 */

extern struct	ModemInternalStatusTable_t far MDM_InternalStatus[MODEM_STATUS_TABLE_MAX];	/** モデム内部遷移ステータス用テーブル **/
extern UBYTE			ControlChannelRetrainFlag;	/* CC Retrain By O.Kimoto 1996/05/16 */
extern UBYTE			MDM_ClearToSendAbort;			/* CTSがONしなかった 1996/05/17 Y.Murata */
extern UBYTE			MDM_RetrainFirstCCTrainFlag;	/* １ｓｔＣＣでリトレインが発生したかどうかのフラグ By O.Kimoto 1996/08/14 */
extern UWORD					MDM_CarrierDropoutTimer;	/* キャリアがなくなった事を計測するタイマー By O.Kimoto 1996/09/10 */
extern UBYTE			MDM_CarrierDropoutFlag;	/* キャリアがなくなった事を示すフラグ By O.Kimoto 1996/09/10 */
extern UBYTE			MDM_FedOffFlag;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */

extern UWORD					MDM_RxTcfEyeAverage;	/* T30 TCF EQM Average 1996/10/23 Y.Murata */
extern UWORD					BackUpEYE_Slice;		/* T30 比較したﾃｰﾌﾞﾙ値 1996/10/25 Y.M */
extern UBYTE			MDM_DropOutRecovryV17V29;	/* 1996/10/31 Y.Murata */
extern UBYTE			MDM_PixStartFlag;			/* For Control RTDIS By O.Kimoto 1996/12/09 */
extern UBYTE			MDM_AlreadyRtdisSetFlag;	/* For Control RTDIS By O.Kimoto 1996/12/09 */

/* 工場ファンクションタスクＩＤ追加 1996/12/11 Y.M */
extern UWORD					tskno_MDM_FskTest;
extern UWORD					tskno_MDM_PixTest;
extern UBYTE			MDM_FactoryFskMenu;
extern struct ServiceFuncPixData_t 	FactoryPixData;

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
extern UWORD					tskno_MDM_VoiceTest;
 #endif
#endif

extern UBYTE			MDM_OldFedStatus;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_NewFedStatus;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_OldPndetStatus;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_NewPndetStatus;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_OldPnsucStatus;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_NewPnsucStatus;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_OldDmy4Status;	/*  By O.Kimoto 1996/12/20 */
extern UBYTE			MDM_NewDmy4Status;	/*  By O.Kimoto 1996/12/20 */

extern UBYTE			MDM_OldFeStatus;	/*  By H.Kubo  1997/08/28 */
extern UBYTE			MDM_NewFeStatus;	/*  By H.Kubo  1996/08/28 */


extern UBYTE			MDM_FirstV21Ch2FlagReceive;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
extern UBYTE			MDM_ReceiveLevelExtension;	/* Ｖ２１の最初の受信か 1997/01/28 Y.Murata */
extern UWORD					MDM_V21MeasureReceiveLevel;
extern UWORD					MDM_V21MeasureStartGo;
extern UWORD					MDM_NoCarryOrErrorCount;	/* EOL又はｴﾗｰがあったﾌﾞﾛｯｸ(G3) 1997/01/31 Y.Murata */
extern UWORD					MDM_CurrentTotalErrorLine;	/* 1997/01/31 Y.Murata */
extern UWORD					MDM_CurrentDecodeLine;		/* 1997/02/01 Y.Murata */
extern UWORD					MDM_CurrentDecodeErrorLine;	/* 1997/02/01 Y.Murata */
extern UBYTE			MDM_FskModeFlag;			/* 1997/02/06 Y.Murata */
extern UBYTE			MDM_FskFcsTimeOutFlag;		/* 1997/02/08 Y.Murata */

extern UDWORD 			MDM_OptionTTiSize;	/* Add By O.Kimoto 1997/02/25 */

extern	struct HighRdsTable_t HighRDS_Table[];	/* 1997/02/05  By T.Yamaguchi */
extern	UBYTE *WriteDisableBackUpData[];	/* 1999/04/29 by K.Okada */

extern	UDWORD	BackUpDataLength;	/* 高速ＲＤＳデータライト時のバックアップデータ長 */

/* Flags to indicate that DMA transfer is finished. Written by H.Kubo 1997/07/18 */
/*+++++ This part should be modified according to the configuration of DMA channel allocation. ++++++*/
extern int 	IsModemToMemoryXferDone;
extern int	IsMemoryToModemXferDone;


extern UBYTE CL1_PNSUC_TurnOff;	/*  By O.Kimoto 1997/05/16 */
extern UBYTE CL1_RLSD_TurnOff;	/*  By O.Kimoto 1997/05/16 */
extern UBYTE CL1_FLAGDT_Found;	/*  By O.Kimoto 1997/05/16 */
extern UBYTE CL1_HDLC_AbortSequence; /* by H.Kubo 1997/08/28 */

/* Ported from ORANGE by H.Kubo 1997/09/08 */
/* ECM 受信ループ対策 */
extern	UWORD			MDM_ResetCounter; /* 96.2.13 for ＥＣＭ受信中ループ */

extern UBYTE			MDM_TrueConfValue;	/** Add By O.Kimoto 1997/12/02 */

/* Ported from CLOVER by H.Kubo 1997/12/24 */
extern UBYTE			MDM_RTH_ControlStatus;	/* 1997/12/22 RTH_CONTROL */

extern UBYTE			MDM_G3DummyDataDetecting;	/* 1997/12/25 */

extern UWORD			MDM_RecoverStatus;			/* Add By O.Kimoto 1998/02/03 */
extern UWORD			MDM_BackupRecoverStatus;	/* Add By O.Kimoto 1998/02/03 */

extern UBYTE			MDM_V34_CC_RetrainTimeCutFlag;	/* 1997/10/07 Y.Murata */ /* Ported from Clover by H.Kubo 1998/02/03 */
extern UBYTE			MDM_ForcedDecodeStart;	/*  追加 by T.Soneoka 1998/03/02 */

extern UBYTE			IsDetLastFrameEndMaker;	/*  追加 by T.Soneoka 1998/03/02 */
extern UBYTE			IsDetEndMaker;	/*  追加 by T.Soneoka 1998/03/02 */

#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
extern  UWORD			MDM_ModemDmaSize;
extern  UBYTE 			MDM_ModemBufferFirstPoint;
#endif

extern UBYTE			IsMemoryOpen;	/* 1998/05/15 by T.Soneoka */

extern UBYTE			MDM_ND_WaitFirstDataEvent;
extern UWORD tskno_V23RlsdTimer; /* added by H.Kubo 1998/11/11 */
extern UWORD MDM_V23_ModemRecoverRunning; /* added by H.Kubo 1998/11/11 */

/*
** R288F VERSION 22P以上
** Condition changd by H.Kubo 1998/10/17
*/
extern UBYTE			IsRlsdAndRdbfOn;	/* 1998/10/09 By H.Hirao */

/*
** R288F VERSION 24P以上
** by H.Kubo 1998/10/30
*/
extern UBYTE MDM_PreviousPCOFF_Status; /* H.Kubo 1998/10/30 */

extern UBYTE	MDM_MemReadStatus;


/*
** R288F VERSION 22P
** added by H.Kubo 1998/11/10
*/
extern struct MDM_ModemStatusRegister_t  MDM_CurrentModemRegister;
extern struct MDM_ModemStatusRegister_t  MDM_PreviousModemRegister;
extern struct MDM_ModemStatusRegister_t  MDM_ReviewRegister;

/*
** フレーム間フラグが短くてモデムがフラグを取り逃がしたときの救済用。
** H.Kubo 1999/01/22
*/
extern UBYTE MDM_EcmRxFcsCheckRequest; /* 8bit 幅の変数。各ビットがモデムバッファ一本に対応する。 */

extern UWORD	MDM_LineDecodeStartTimer;	/* １ラインの受信時間を測定するためのタイマー ＤＥＵ仕様 */

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* added by H.Kubo 1999/06/25  */
/* V29 9600bps 受信対策用。 by H.Kubo 1999/06/25 */
extern UBYTE MDM_CurrentFilterType;
#endif

extern UWORD	Rx3mErrorLine; /* 3m over Rx by H.Kubo 1999/09/14 */

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
extern UBYTE	MDM_EcmBufferOverEncodeStop;	/* ＥＣＭﾊﾞｯﾌｧ超えたでフラグ 1997/11/20 */
extern UBYTE	MDM_2ndEcmBufferReamin;			/* 1997/11/21 */
extern UDWORD	MDM_EcmRemainCount;				/* 1997/11/21 */
extern UBYTE	MDM_RTC_DetectStatusStopReq;	/* 1997/11/29 */
extern UWORD	MDM_R33Timer1;					/* 1997/12/10 debug */
extern UWORD	MDM_R33Timer2;					/* 1997/12/10 debug */
extern UDWORD	MDM_DebugRxCount;				/* 1997/12/13 debug */
#endif

/* #if defined(POPLAR_F) *//* 1999/10/21 m.matsumoto */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
extern UWORD	tskid_VoiceTimeUpTask;
extern UWORD	tskid_NAR_DetectTask;
extern UBYTE	BackUpCodecPageStatus;		/*	コーデック状態を保存 for debug	*/
extern UWORD	MDM_StxLoopCounter;			/* 2000/02/04 Y.Murata */

extern UBYTE	MDM_IsSingleToneON;		/* WAYARAより移植 by O.Kimoto 2002/11/14 */

 #endif
#endif

#if defined (HINOKI2)	/* 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined (SATSUKI2) || defined(STOCKHM2)/* By M.Maeda 2002/09/18 */ || (defined(POPLAR_H) && defined(JP1))	/* 55転送 By O.Kimoto 2003/02/05 */
extern UWORD BackupReceiveLevel; /* 2000/12/12 by K.Okada */
#endif
