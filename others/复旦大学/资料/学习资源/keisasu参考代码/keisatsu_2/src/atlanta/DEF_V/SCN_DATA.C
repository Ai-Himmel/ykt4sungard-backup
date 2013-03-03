/* アンズより移植 イチョウで追加された分追加必要 By Y.Suzuki 1996/10/14 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\scn_def.h"
/*--------------------------------------------------------------------*/
/* プロジェクト : ﾎﾟﾌﾟﾗ･ｱﾝｽﾞL	                                      */
/* ファイル名   : scn_data.c                                          */
/* 作成者       : S.Kawasaki Y.suzuki                                 */
/* 日  付       : 94.3.14/961014                                      */
/* 概  要       : V53                                                 */
/*              : スキャナー用定義					                  */
/* 参照			:									                  */
/* 修正履歴     :                                                     */
/*              :                                                     */
/*--------------------------------------------------------------------*/
UBYTE SCN_MotorTablePoint = 0;

UBYTE SCN_MTPC0_Status = 0;
UBYTE SCN_MTPC1_Status = 0;
UBYTE SCN_MTP0_Status = 0;
UBYTE SCN_MTP1_Status = 0;
UWORD SCN_SENSTP_Status = 0;
UWORD SCN_SSTSTP_Status = 0;
UBYTE SCN_SCNINT_Status = 0;
UBYTE SCN_DS2INTR_Status = 0;
UBYTE SCN_BUZZ_1K_Status = 0;
UBYTE SCN_MTCNT_Status = 0;
UBYTE SCN_SCCNT_Status = 0;
UBYTE SCN_INTLNCN_Status = 0;

/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  23,Mar,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿搬送路の原稿ステータス
*********************************************************************************************/
UBYTE SCN_DocumentStatus = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  31,Mar,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー・モーターのスピード制御
*********************************************************************************************/
UBYTE SCN_MotorSpeedControl = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  18,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー蓄積用データ（MEM_WriteOpen()への引き数）
*********************************************************************************************/
struct MEM_StoreData_t       SCN_StoreData = {0};
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  18,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー蓄積用データ（MEM_WriteOpen(),MEM_WriteClose()への引き数）
*********************************************************************************************/
struct MEM_ExecData_t        SCN_ExecData = {0};
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  18,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナーモーターテーブル用ポインター
*********************************************************************************************/
struct SCN_MOTOR_TABLE_t *SCN_MotorPointer = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  21,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー読み取り用モードの待避用
*********************************************************************************************/
UBYTE SCN_ModeSw = 0;
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
UBYTE SCN_VerticalMode = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  21,Apr,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー副走査のモード
*********************************************************************************************/
struct SCN_Control_def_t SCN_Control = {0};
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  May.11,1994
*        TYPE:
* DESCRIPTION:  スキャナー副走査のMAX Scanning Line
*********************************************************************************************/
UWORD			SCN_ScanMaxLine = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jun.4,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー蓄積用データ（MEM_ClearBreak()への引き数）
*********************************************************************************************/
struct MEM_IndexData_t SCN_IndexData = {0};
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jun.6,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用スピード制御用配列の番号
*********************************************************************************************/
UBYTE SCN_SpeedCheckPoint = 0;
UWORD		  SCN_FeedErrorCheckStep = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jun.28,1994
*        TYPE:  DEFINE
* DESCRIPTION:  読み取り左右白マスク
*********************************************************************************************/
UBYTE SCN_WhiteMaskFlag = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクＩＤ用
*********************************************************************************************/
UWORD tskno_SCN_DMA_WriteTask = 0;
UWORD tskno_CDC_EncodePageTask = 0;
UWORD tskno_SCN_WatchDocCoverTask = 0;
UWORD tskno_SCN_WatchDocFeedTask = 0;
UWORD tskno_SCN_WatchDocumentExitTask = 0;
UWORD tskno_SCN_WatchGearBackLashTask = 0;
UWORD tskno_SCN_MirrorMoveTask = 0;
UWORD tskno_SCN_WatchDocMirrorTask = 0;
UWORD tskno_SCN_DocumentPageCountTask = 0;
UWORD tskno_SCN_WatchPrinterCoverTask = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクのメッセージ受信用
*********************************************************************************************/
MESSAGE_t		*SCN_Msg = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクのメッセージ受信用（テンポラリ）
*********************************************************************************************/
UWORD SCN_Message = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Jul.11,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー用タスクのメッセージ送信用
*********************************************************************************************/
MESSAGE_t StoreTaskMsg = {0};
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.19,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿読み取り終了時にモーターを停止要求があるか
*********************************************************************************************/
UBYTE SCN_MotorStopRequest = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.20,1994
*        TYPE:  DEFINE
* DESCRIPTION:  原稿蓄積時の符号化ライン数
*********************************************************************************************/
UWORD SCN_TotalEncodeLine = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.22,1994
*        TYPE:  DEFINE
* DESCRIPTION:  ＩＤＰでの縮小ステータス待避
*                待避場所はIDP_Interruptで行う
*********************************************************************************************/
UBYTE SCN_RED_Status = 0;
/********************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  Aug.24,1994
*        TYPE:  DEFINE
* DESCRIPTION:  スキャナー送信時の縮小パターン
*               セットされる関数はSCN_DecideReductionPattern()
*               参照場所はSCN_Open()
*********************************************************************************************/
UBYTE SCN_ScannerTxReductionPattern = 0;

UWORD	SCN_StopScanLine = 0;
UWORD	SCN_EndScanLine = 0;

UBYTE 	SCN_MotorCurrentStopCounter = 0;
UWORD	SCN_Debug53Lines = 0; /* Nov.9,1994 By S.K */
UWORD	DebugLineInt = 0;
UWORD	DebugPreLineInt = 0;

/********************************************************************************************
*          BY:  N.Sakamoto
*        DATE:  Dec.21,1995
*        TYPE:  DEFINE
* DESCRIPTION:  モータ反転制御の際の複数頁繰込時の繰込結果
*               セットされる関数はMAN_DocumentInTask()
*               参照場所はSCN_Task()
*********************************************************************************************/
UBYTE	IsScanTxScanningStop = 0;			/* 1996/06/27 By N.Sakamoto */

UBYTE	IsScanDocFeedOutAfterStampTest = 0;	/* 1996/07/03 By N.Sakamoto */

UBYTE	DocFeedOutAfterStampTestCount  = 0;	/* 1996/07/03 By N.Sakamoto */

UBYTE	SCN_AppointPage = 0;				/* 1996/07/23 By N.Sakamoto */

UBYTE	SCN_StopDS1OffDetect = 0;			/* 1996/08/14 By N.Sakamoto */

/*--------------------for debug,check -----------------------------------*/
UWORD	SCN_GA_Check_Flag = 0;

/* unsigned char	DebugLampOffAddressCheck = 0;	@* 1996/08/02 By N.Sakamoto */
/*-----------------------------------------------------------------------*/

/* ICHOU用に追加  s.takeuchi */
struct SYS_MultiCopyData_t	*SCN_CopyFile = 0;	/* (マルチ|手差し)コピーファイルのポインタ */
MESSAGE_t		SCN_MirrorTxMessage = {0};		/* ミラータスクからのsnd_msg用 */
MESSAGE_t		*SCN_MirrorRxMessage = 0;		/* ミラータスクへのrcv_msg用 */
UWORD			SCN_MirrorMotorPulseCount = 0;	/* ミラーキャリッジ移動時のモーターの移動量 */
UWORD			SCN_MotorIntStep = 0;			/* モーター速度変更割り込み設定ステップ */
UWORD			SCN_StepFromES_Off = 0;			/* エンドセンサOffから所定位置への移動量 */
UWORD			SCN_StepFromHS_Off = 0;			/* ホームセンサOffから所定位置への移動量 */
UWORD			SCN_PageCount = 0;				/* テスト用の排出ページ数カウンタ */
UWORD			SCN_MirrorStopTimeoutCount = 0;	/* ミラー停止待ちタイムアウト用  1997/02/18 */
UWORD			SCN_DS2_BouncePoint = 0;		/* DS2バウンス対策用(発生ポイント)  1997/04/05 */
UWORD			SCN_DS2_BounceMaxStep = 0;		/* DS2バウンス対策用(収束ステップ)  1997/04/05 */
UWORD			SCN_DocExitTopSpeedCount = 0;	/* 原稿排出時にモーターを最高速でまわす回数 */
UBYTE	SCN_FullWidthScan = 0;			/* 全画素読取り状態 */
UBYTE	SCN_MotorDriveMode = 0;			/* モーター駆動経路(sysscan.h参照) */
UBYTE	SCN_IsMotorClockwise = 0;		/* モーター回転方向(正転:TRUE) */
UBYTE	SCN_MirrorTaskControl = 0;		/* ミラーキャリッジ移動タスクへの動作指定 */
UBYTE	SCN_MirrorCarriageStatus = 0;	/* ミラーキャリッジの状態 */
UBYTE	SCN_MirrorMoveStatus = 0;		/* ミラーキャリッジ移動結果 */
UBYTE	SCN_IsMirrorMoveEnd = 0;		/* ミラーキャリッジ移動終了状態 */
UBYTE	SCN_WatchEndSensorStatus = 0;	/* 10ms割込みでのエンドセンサ監視の状態 */
UBYTE	SCN_IsLampCheckFinish = 0;		/* FBS読み取り前のランプチェック実行状況 */
UBYTE	SCN_RegularDocumentSize = 0;	/* 1996/10/3 by T.Soneoka */
UBYTE	SCN_FBS_VerticalSize = 0;		/* FBS長手センサ(BSS)検出結果 */
UBYTE	SCN_ADF_MotorStopRequest = 0;	/* ADFモーター停止要求用  1996/10/28 */
UBYTE	SCN_StorePageCountError = 0;	/* 枚数指定チェック  1997/02/18 */
UBYTE	SCN_MirrorReadyPosition = 0;	/* ミラーキャリッジの待機位置 */

/* デバッグ用 */
UBYTE	SCN_DebugShadingRAM[224] = {0};	/* 薄読みデバッグ用  1997/02/25 */
UBYTE	SCN_DebugInitialRAM0[192] = {0};	/* 薄読みデバッグ用  1997/04/25 */
UBYTE	SCN_DebugInitialRAM1[192] = {0};	/* 薄読みデバッグ用  1997/04/25 */
UBYTE	SCN_DebugTest = 0;					/* 汎用 T.Nose */

UWORD	SCN_N_StepRemain = 0;	/* 輸送モード停止位置までの残りステップ  1997/06/05 */

/********************************************************************************************
*          BY:  T.Nose
*        DATE:  1997/11/25
*        TYPE:  DEFINE
* DESCRIPTION:  マルチコピー蓄積でA3原稿をスキャナーコーデックで縮小する時の縮小率を保存する
*********************************************************************************************/
UWORD SCN_DocumentReduction = 0;

/*-------------------------------------------------------------------------
** ライン割り込みカウンター
** メモリ蓄積時は、一定速で読み取りを行っているので、このカウンターも一定周期でインクリメントされている。
** 読み取り中なのになぜかモータが停止している不具合対策
** 一定周期でカウントアップされるべきこのカウンターがインクリメントされていない場合には、
** 不具合発生として、ＳＣＮタスクを終了し、原稿ＪＡＭ状態にするようにする。
** 1997/05/10 H.Yoshikawa
*/
UWORD 			SCN_INT_Counter = 0;
UWORD 			SCN_PreINT_Counter = 0;
UWORD			SCN_WatchDocTimer = 0;

/********************************************************************************************
*          BY:  T.Nose
*        DATE:  1997/12/05
*        TYPE:  DEFINE
* DESCRIPTION:  ソフトコーデックなど他の処理が重くなった時、SCN_Task()でSCN_DocumentStatus
*               の更新が間に合わなかったフラグ
*********************************************************************************************/
UBYTE SCN_PageChangeTimeOut = 0;

/* メモリー送信原稿後端が縮む件 T.Nose 1997/10/17 */
UWORD	DEBUG_SaveLineInt = 0;
UWORD	DEBUG_SCNCount = 0;
UBYTE	DEBUG_DocumentScanning = 0;	/* 10/31 */

/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件 T.Nose 1997/12/17 */
BYTE  DEBUG_MirrorMoveTimeCounter = 0;
UBYTE DEBUG_MirrorMoveCountStart = 0;
UBYTE DEBUG_MirrorNeedInitial = 0;
UBYTE DEBUG_OperationExitFlag = 0;		/* シェーディングオペレーション終了フラグ */

#if (PRO_FBS == ENABLE)
/* RXIL瞬断対策 RXILをチャタリング監視なしで直接見てセットする T.Nose 1998/03/03 */
UBYTE SCN_IsTopCoverOpen = 0;
#endif

/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
UBYTE SCN_STxLineIntDisableFlag = 0;
#endif

