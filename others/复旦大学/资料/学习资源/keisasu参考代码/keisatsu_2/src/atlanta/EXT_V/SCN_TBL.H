/* Original File : jun\usr1:\src\rice\v53\kiri\ext_v\scn_tbl.hkr */
/*--------------------------------------------------------------------*/
/* プロジェクト : KIRI/MILAN	                                      */
/* ファイル名   : scn_tbl.h                                           */
/* 作成者       : S.Kawasaki                                          */
/* 日  付       : 94.3.14                                             */
/* 概  要       : V53                                                 */
/*              : スキャナー用定義					                  */
/* 参照			:									                  */
/* 修正履歴     :                                                     */
/*              :                                                     */
/*--------------------------------------------------------------------*/
/*******************************************************************************************
*          BY:  S.Kawasaki
*        DATE:  10,Mar,1994
*        TYPE:  DEFINE
* VAR TO HOLD:	struct MOTOR_TABLE SCN_ThroughUpTable：スルーアップ用
*				struct MOTOR_TABLE SCN_ThroughDownTable ：スルーダウン用
* DESCRIPTION:  モーター・スルーアップ／ダウン用構造体
*********************************************************************************************/
#include "\src\atlanta\define\scn_def.h"

extern CONST struct SCN_MOTOR_TABLE_t SCN_MotorTable[];

/* 繰り込み不良検出ステップ */
extern CONST UWORD	SCN_DS1_TO_READY_ERROR_STEPS;
extern CONST UWORD	SCN_DS1_TO_DS2_ERROR_STEPS;
extern CONST UWORD	SCN_READ_TO_DS3_ERROR_STEPS;
extern CONST UWORD	SCN_DS3_TO_EXIT_ERROR_STEPS;
extern CONST UWORD	SCN_DS2_TO_READ_ERROR_STEPS;

extern CONST UWORD	SCN_FEED_OUT_ERROR_STEPS;
extern CONST UWORD	SCN_DS2_ON_TO_OFF_ERROR_STEPS;

extern CONST UBYTE	SCN_SpeedCheckLine[];	/* ライン割り込み設定値 */

/*ICHOU削除	extern UBYTE DebugFineToNormal; */

/* ADF用の済みスタンプ位置用のステップ (define値から大域変数に変更  1996/11/14) */
extern CONST UWORD	ADF_READ_POINT_TO_STAMP;
extern CONST UWORD	ADF_DOC_EDGE_TO_STAMP;

/* ミラーキャリッジ移動用のステップ (define値から大域変数に変更  1996/11/13) */
extern CONST UWORD	FBS_STEP_HS_TO_READY;
/* extern UWORD	FBS_STEP_HS_TO_FBS_TOP; */
extern CONST UWORD	FBS_STEP_HS_TO_FBS_END;
extern CONST UWORD	FBS_STEP_ES_ON_TO_LAMP_CHECK;
extern CONST UWORD	FBS_STEP_HS_TO_LAMP_CHK;
/* extern UWORD	FBS_STEP_ES_TO_ADF; */
extern CONST UWORD	FBS_STEP_MAXIMUM;
extern CONST UWORD	FBS_STEP_HS_ON_PERIOD;
extern CONST UWORD	FBS_STEP_HS_TO_ES;
extern CONST UWORD	FBS_STEP_ES_ON_PERIOD;

extern CONST struct ScanDocSizeTable_t	SYS_ScanDocSizeTable[];	/* 読取り原稿サイズ設定値 */
extern CONST UBYTE	SCN_DocSizeDetectTable[2][3][2];	/* FBS原稿サイズ自動検出 */

extern CONST UWORD	SCN_MotorChangeInterval;	/*	モータの回転方向を変えるための待ち時間 */

extern CONST UWORD SCN_DOC_EXIT_STEP;
extern CONST UBYTE SCN_CopyReduction;		/* コピー縮小率 1997/08/27 T.Nose */

/* デバッグ用 */
extern CONST UBYTE	SCN_Debug2motor;	/* Twin Motor  1996/10/27 */
