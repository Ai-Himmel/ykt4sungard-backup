/* アンズより移植 イチョウで追加された分追加必要 By Y.Suzuki 1996/10/14 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\scn_def.h"
/*--------------------------------------------------------------------*/
/* プロジェクト : ﾎﾟﾌﾟﾗ･ｱﾝｽﾞL	                                      */
/* ファイル名   : scn_data.h                                          */
/* 作成者       : S.Kawasaki Y.suzuki                                 */
/* 日  付       : 94.3.14/961014                                      */
/* 概  要       : SHC                                                 */
/*              : スキャナー用定義					                  */
/* 参照			:									                  */
/* 修正履歴     :                                                     */
/*              :                                                     */
/*--------------------------------------------------------------------*/
extern UBYTE SCN_MotorTablePoint;

extern UBYTE SCN_MTPC0_Status;
extern UBYTE SCN_MTPC1_Status;
extern UBYTE SCN_MTP0_Status;
extern UBYTE SCN_MTP1_Status;
extern UWORD SCN_SENSTP_Status;
extern UWORD SCN_SSTSTP_Status;
extern UBYTE SCN_SCNINT_Status;
extern UBYTE SCN_DS2INTR_Status;
extern UBYTE SCN_BUZZ_1K_Status;
extern UBYTE SCN_MTCNT_Status;
extern UBYTE SCN_SCCNT_Status;
extern UBYTE SCN_INTLNCN_Status;

/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  23,Mar,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿搬送路の原稿ステータス
*********************************************************************************************/
extern UBYTE SCN_DocumentStatus;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  31,Mar,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー・モーターのスピード制御
*********************************************************************************************/
extern UBYTE SCN_MotorSpeedControl;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  18,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー蓄積用データ（MEM_WriteOpen()への引き数）
*********************************************************************************************/
extern struct MEM_StoreData_t       SCN_StoreData;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  18,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー蓄積用データ（MEM_WriteOpen(),MEM_WriteClose()への引き数）
*********************************************************************************************/
extern struct MEM_ExecData_t        SCN_ExecData;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  18,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナーモーターテーブル用ポインター
*********************************************************************************************/
extern struct SCN_MOTOR_TABLE_t *SCN_MotorPointer;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  21,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー読み取り用モードの待避用
*********************************************************************************************/
extern UBYTE SCN_ModeSw;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  21,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー副走査のモード
*			 :  0:SCN_NORMAL
*			 :  1:SCN_FINE
*			 :  2:SCN_SFINE
*			 :  3:SCN_DOC_IN
*			 :  4:SCN_DOC_OUT
*********************************************************************************************/
extern UBYTE SCN_VerticalMode;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  21,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー副走査のモード
*********************************************************************************************/
extern struct SCN_Control_def_t SCN_Control;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  May.11,1994
*        TYPE:
* DESCRIPTION:  スキャナー副走査のMAX Scanning Line
*********************************************************************************************/
extern UWORD			SCN_ScanMaxLine;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jun.4,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー蓄積用データ（MEM_ClearBreak()への引き数）
*********************************************************************************************/
extern struct MEM_IndexData_t SCN_IndexData;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jun.6,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用スピード制御用配列の番号
*********************************************************************************************/
extern UBYTE SCN_SpeedCheckPoint;
extern UWORD		  SCN_FeedErrorCheckStep;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jun.28,1994
*        TYPE:  DEFINE
* DESCRIPTION:  読み取り左右白マスク
*********************************************************************************************/
extern UBYTE SCN_WhiteMaskFlag;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクＩＤ用
*********************************************************************************************/
extern UWORD tskno_SCN_DMA_WriteTask;
extern UWORD tskno_CDC_EncodePageTask;
extern UWORD tskno_SCN_WatchDocCoverTask;
extern UWORD tskno_SCN_WatchDocFeedTask;
extern UWORD tskno_SCN_WatchDocumentExitTask;
extern UWORD tskno_SCN_WatchGearBackLashTask;
extern UWORD tskno_SCN_MirrorMoveTask;
extern UWORD tskno_SCN_WatchDocMirrorTask;
extern UWORD tskno_SCN_DocumentPageCountTask;
extern UWORD tskno_SCN_WatchPrinterCoverTask;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクのメッセージ受信用
*********************************************************************************************/
extern MESSAGE_t		*SCN_Msg;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクのメッセージ受信用（テンポラリ）
*********************************************************************************************/
extern UWORD SCN_Message;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクのメッセージ送信用
*********************************************************************************************/
extern MESSAGE_t StoreTaskMsg;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.19,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿読み取り終了時にモーターを停止要求があるか
*********************************************************************************************/
extern UBYTE SCN_MotorStopRequest;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.20,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿蓄積時の符号化ライン数
*********************************************************************************************/
extern UWORD SCN_TotalEncodeLine;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.22,1994
*        TYPE:  DEFINE
* DESCRIPTION:  ＩＤＰでの縮小ステータス待避
*                待避場所はIDP_Interruptで行う
*********************************************************************************************/
extern UBYTE SCN_RED_Status;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.24,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー送信時の縮小パターン
*               セットされる関数はSCN_DecideReductionPattern()
*               参照場所はSCN_Open()
*********************************************************************************************/
extern UBYTE SCN_ScannerTxReductionPattern;

extern UWORD	SCN_StopScanLine;
extern UWORD	SCN_EndScanLine;

extern UBYTE 	SCN_MotorCurrentStopCounter;
extern UWORD	SCN_Debug53Lines;
extern UWORD	DebugLineInt;
extern UWORD	DebugPreLineInt;

/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  Dec.21,1995
*        TYPE:  DEFINE
* DESCRIPTION:  モータ反転制御の際の複数頁繰込時の繰込結果
*               セットされる関数はMAN_DocumentInTask()
*               参照場所はSCN_Task()
*********************************************************************************************/
extern UBYTE	IsScanTxScanningStop;			/* 1996/06/27 By N.Sakamoto */

extern UBYTE	IsScanDocFeedOutAfterStampTest;	/* 1996/07/03 By N.Sakamoto */

extern UBYTE	DocFeedOutAfterStampTestCount;	/* 1996/07/03 By N.Sakamoto */

extern UBYTE	SCN_AppointPage;				/* 1996/07/23 By N.Sakamoto */

extern UBYTE	SCN_StopDS1OffDetect;			/* 1996/08/14 By N.Sakamoto */

/*--------------------for debug,check -----------------------------------*/
extern UWORD	SCN_GA_Check_Flag;

/* extern unsigned char	DebugLampOffAddressCheck;	@* 1996/08/02 By N.Sakamoto */
/*-----------------------------------------------------------------------*/

/* ICHOU用に追加  s.takeuchi */
extern struct SYS_MultiCopyData_t	*SCN_CopyFile;	/* (マルチ|手差し)コピーファイルのポインタ */
extern MESSAGE_t	SCN_MirrorTxMessage;	/* ミラータスクからのsnd_msg用 */
extern MESSAGE_t	*SCN_MirrorRxMessage;	/* ミラータスクへのrcv_msg用 */
extern UWORD	SCN_MirrorMotorPulseCount;	/* ミラーキャリッジ移動時のモーターの移動量 */
extern UWORD	SCN_MotorIntStep;			/* モーター速度変更割り込み設定ステップ */
extern UWORD	SCN_StepFromES_Off;			/* エンドセンサOffから所定位置への移動量 */
extern UWORD	SCN_StepFromHS_Off;			/* ホームセンサOffから所定位置への移動量 */
extern UWORD	SCN_PageCount;				/* テスト用の排出ページ数カウンタ */
extern UWORD	SCN_MirrorStopTimeoutCount;	/* ミラー停止待ちタイムアウト用  1997/02/18 */
extern UWORD	SCN_DS2_BouncePoint;		/* DS2バウンス対策用(発生ポイント)  1997/04/05 */
extern UWORD	SCN_DS2_BounceMaxStep;		/* DS2バウンス対策用(収束ステップ)  1997/04/05 */
extern UWORD	SCN_DocExitTopSpeedCount;	/* 原稿排出時にモーターを最高速でまわす回数 */
extern UBYTE	SCN_FullWidthScan;			/* 全画素読取り状態 */
extern UBYTE	SCN_MotorDriveMode;			/* モーター駆動経路(sysscan.h参照) */
extern UBYTE	SCN_IsMotorClockwise;		/* モーター回転方向(正転:TRUE) */
extern UBYTE	SCN_MirrorTaskControl;		/* ミラーキャリッジ移動タスクへの動作指定 */
extern UBYTE	SCN_MirrorCarriageStatus;	/* ミラーキャリッジの状態 */
extern UBYTE	SCN_MirrorMoveStatus;		/* ミラーキャリッジ移動結果 */
extern UBYTE	SCN_IsMirrorMoveEnd;		/* ミラーキャリッジ移動終了状態 */
extern UBYTE	SCN_WatchEndSensorStatus;	/* 10ms割込みでのエンドセンサ監視の状態 */
extern UBYTE	SCN_IsLampCheckFinish;		/* FBS読み取り前のランプチェック実行状況 */
extern UBYTE	SCN_RegularDocumentSize;	/* 1996/10/3 by T.Soneoka */
extern UBYTE	SCN_FBS_VerticalSize;		/* FBS長手センサ(BSS)検出結果 */
extern UBYTE	SCN_ADF_MotorStopRequest;	/* ADFモーター停止要求用  1996/10/28 */
extern UBYTE	SCN_StorePageCountError;	/* 枚数指定チェック  1997/02/18 */
extern UBYTE	SCN_MirrorReadyPosition;	/* ミラーキャリッジの待機位置 */

/* デバッグ用 */
extern UBYTE	SCN_DebugShadingRAM[224];	/* 薄読みデバッグ用  1997/02/25 */
extern UBYTE	SCN_DebugInitialRAM0[192];	/* 薄読みデバッグ用  1997/04/25 */
extern UBYTE	SCN_DebugInitialRAM1[192];	/* 薄読みデバッグ用  1997/04/25 */
extern UBYTE	SCN_DebugTest;				/* 汎用 T.Nose */

extern UWORD	SCN_N_StepRemain;	/* 輸送モード停止位置までの残りステップ  1997/06/05 */

/********************************************************************************************
*          BY:  T.Nose
*        DATE:  1997/11/25
*        TYPE:  DEFINE
* DESCRIPTION:  マルチコピー蓄積でA3原稿をスキャナーコーデックで縮小する時の縮小率を保存する
*********************************************************************************************/
extern UWORD SCN_DocumentReduction;

/*-------------------------------------------------------------------------
** ライン割り込みカウンター
** メモリ蓄積時は、一定速で読み取りを行っているので、このカウンターも一定周期でインクリメントされている。
** 読み取り中なのになぜかモータが停止している不具合対策
** 一定周期でカウントアップされるべきこのカウンターがインクリメントされていない場合には、
** 不具合発生として、ＳＣＮタスクを終了し、原稿ＪＡＭ状態にするようにする。
** 1997/05/10 H.Yoshikawa
*/
extern UWORD 	SCN_INT_Counter;
extern UWORD 	SCN_PreINT_Counter;
extern UWORD	SCN_WatchDocTimer;

/********************************************************************************************
*          BY:  T.Nose
*        DATE:  1997/12/05
*        TYPE:  DEFINE
* DESCRIPTION:  ソフトコーデックなど他の処理が重くなった時、SCN_Task()でSCN_DocumentStatus
*               の更新が間に合わなかったフラグ
*********************************************************************************************/
extern UBYTE SCN_PageChangeTimeOut;

/* メモリー送信原稿後端が縮む件 T.Nose 1997/10/17 */
extern UWORD	DEBUG_SaveLineInt;
extern UWORD	DEBUG_SCNCount;
extern UBYTE	DEBUG_DocumentScanning;	/* 10/31 */

/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件 T.Nose 1997/12/17 */
extern BYTE  DEBUG_MirrorMoveTimeCounter;
extern UBYTE DEBUG_MirrorMoveCountStart;
extern UBYTE DEBUG_MirrorNeedInitial;
extern UBYTE DEBUG_OperationExitFlag;		/* シェーディングオペレーション終了フラグ */

#if (PRO_FBS == ENABLE)
/* RXIL瞬断対策 RXILをチャタリング監視なしで直接見てセットする T.Nose 1998/03/03 */
extern UBYTE SCN_IsTopCoverOpen;
#endif

/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
extern UBYTE SCN_STxLineIntDisableFlag;
#endif

