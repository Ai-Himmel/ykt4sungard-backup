#ifndef product2_h
	#define product2_h

/************************************************************************
 * プロジェクトパラメータ												*
 * "\src\atlanta\define\product2.h"										*
 *																		*
 * 概要　　：特ＲＯＭ要求が発生する毎にPRODUCT.Hを編集するのは			*
 *			 他への影響が大きいので、特ＲＯＭ専用ファイルを新たに		*
 *			 設けることにする。											*
 * 使用方法：ソースファイルの先頭にインクルードする						*
 *			 条件コンパイルの式として使用する							*
 *			 例) #if (PRO_FIP == ENABLE)								*
 *				 #endif													*
 * 定義方法：定義内容は仕様別とする										*
 *			 プロジェクト仕様が変更となった場合でも、本定義をかえるだけ *
 *			 の対応で済むようにする										*
 *			 例) KIRIで有効な｢一括送信｣をSATSUKIで有効にする場合、		*
 *				   #define PRO_BATCH_TX		ENABLE						*
 *				 とするだけで仕様変更できることになる。					*
 * 補足	   ：プロジェクト内の仕向先固有の仕様を識別する場合は、			*
 *			 国別パラメータ(CountryTable[])を使用する					*
 *																		*
 *																		*
 *		★★★	PRODUCT.HDRのほうもメンテナンスして下さい。★★★		*
 *																		*
 *																		*
 ************************************************************************/

/************************************************************************
 * 有効/無効															*
 ************************************************************************/
#define		DISABLE		0				/* 無効 */
#define		ENABLE		2				/* 有効 */

#if defined(JPN)	/* by H.Hirao 1999/04/02 */
 #if 0 /* 使われていない為削除します 2003/02/17 T.Takagi defined(JP1) */	/* クラス１搭載仕様 by H.Hirao 1999/04/14 */
//	#define PRO_SPECIAL_DOCTOR_REPORT		DISABLE/
//	#define PRO_SPECIAL_REPLAY_TRANS		DISABLE
//	#define PRO_SPECIAL_PAUSE_INPUT			DISABLE
//	#define PRO_POST_OFFICE					DISABLE
//	#define PRO_DAILY_POLLING				DISABLE
 #else
	#define PRO_SPECIAL_DOCTOR_REPORT		ENABLE
	#define PRO_SPECIAL_REPLAY_TRANS		ENABLE
	#define PRO_SPECIAL_PAUSE_INPUT			ENABLE
	#define PRO_POST_OFFICE					DISABLE
	#define PRO_DAILY_POLLING				ENABLE
 #endif
#else	/* TWN */
	#define PRO_SPECIAL_DOCTOR_REPORT		DISABLE
	#define PRO_SPECIAL_REPLAY_TRANS		DISABLE
	#define PRO_SPECIAL_PAUSE_INPUT			DISABLE
	#define PRO_POST_OFFICE					DISABLE
	#define PRO_DAILY_POLLING				DISABLE
#endif

#endif

