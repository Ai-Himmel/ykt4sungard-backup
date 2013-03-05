/*---------------------------------------------------------------------------*/
/*	プロジェクト : SAKAKI													 */
/*	ファイル名	 : CMN_NDHS.C												 */
/*	モジュール	 :															 */
/*	作成者		 : 久保博													 */
/*	日	付		 :															 */
/*	概	要		 : ナンバーディスプレイ着信履歴DB							 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

#ifndef __CMN_NDHS_H
 #define __CMN_NDHS_H

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"

typedef UBYTE SYS_ND_HistoryHandle_t; /* SYB_NumberDisplayJournal を使うので、 UBYTE にします。 by H.Kubo 1998/10/08 */

/* ナンバーディスプレイ着信履歴をオープンのモード */
#define 	ND_HISTORY_OPEN_EMPTY 	1
#define		ND_HISTORY_OPEN_NEWEST 	2
#define		ND_HISTORY_OPEN_OLDEST 	3
#define		ND_HISTORY_OPEN_MODIFY	4

#define 	ND_HISTORY_CLOSE_PRESERVE	10
#define		ND_HISTORY_CLOSE_DESTROY	11

/********************************************************
 	module [ナンバーディスプレイ着信履歴を全消去]
 	function	:[	]
	argument 	:[	]
	return 		:[	]
********************************************************/
void CMN_ND_EraseAllHistory(void);

/********************************************************
 	module [ナンバーディスプレイ着信履歴をオープン]
 	function	:[
		
	]
	argument 	:[
		1. UBYTE mode	オープンのモードを指定する
						ND_HISTORY_OPEN_EMPTY			空の履歴をオープンする。書き込み用。
						ND_HISTORY_OPEN_NEWEST			最新の履歴をオープンする。読み出し用。
						ND_HISTORY_OPEN_OLDEST			最古の履歴をオープンする。読み出し用。
	]
	return 		:[
		履歴のハンドル
					SYS_ND_INVALID_HANDLE				オープンに失敗
					その他								オープンに成功
	]
********************************************************/
SYS_ND_HistoryHandle_t CMN_ND_HistoryOpen(UBYTE mode, SYS_ND_HistoryHandle_t );

void CMN_ND_HistoryClear(SYS_ND_HistoryHandle_t handle);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴の次の記録に移動する]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
		2. UBYTE mode	オープンのモードを指定する
						ND_HISTORY_GET_NEWER_HANDLE		一つ新しい履歴
						ND_HISTORY_GET_OLDER_HANDLE		一つ古い履歴
	]
	return 		:[
		履歴のハンドル
					SYS_ND_INVALID_HANDLE				次の記録がない
					その他								次の記録がある
	]
********************************************************/
UBYTE CMN_ND_GetNextHistory(SYS_ND_HistoryHandle_t handle, UBYTE mode);



/********************************************************
 function 		:[ナンバーディスプレイ着信履歴に指定した種類のデータがあるか問い合わせる]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
		2. UBYTE kind	データの種類
				ND_INFO_CALLER_NUMBER			発信元番号
				ND_INFO_CALLER_EXTRA			発信元付加情報
				ND_INFO_CALLER_NUMBER_REASON	発信元非通知理由
				ND_INFO_DIALIN_NUMBER			ダイヤルイン番号
				ND_INFO_DIALIN_EXTRA			ダイヤルイン番号付加情報
				ND_INFO_TRANSFERER_NUMBER		転送元番号
				ND_INFO_TRANSFERER_EXTRA		転送元番号付加情報
				ND_INFO_MESSAGE					メッセージ情報
				ND_INFO_TIME					着信時刻
				ND_INFO_CALLER_NAME				発信元企業名
				ND_INFO_CALLER_NAME_REASON		発信元企業名非通知理由
				ND_INFO_PUBLIC_PHONE			公衆電話情報
	]
	return 		:[
				TRUE 	ある
				FALSE 	ない
	]
********************************************************/
UBYTE CMN_ND_HistoryCheckKind(SYS_ND_HistoryHandle_t, UBYTE kind);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報取得]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
		2. UBYTE kind	データの種類
				ND_INFO_CALLER_NUMBER			発信元番号
				ND_INFO_CALLER_EXTRA			発信元付加情報
				ND_INFO_CALLER_NUMBER_REASON	発信元非通知理由
				ND_INFO_DIALIN_NUMBER			ダイヤルイン番号
				ND_INFO_DIALIN_EXTRA			ダイヤルイン番号付加情報
				ND_INFO_TRANSFERER_NUMBER		転送元番号
				ND_INFO_TRANSFERER_EXTRA		転送元番号付加情報
				ND_INFO_MESSAGE					メッセージ情報
				ND_INFO_TIME					着信時刻
				ND_INFO_CALLER_NAME				発信元企業名
				ND_INFO_CALLER_NAME_REASON		発信元企業名非通知理由
				ND_INFO_PUBLIC_PHONE			公衆電話情報
	]
	return 		:[
		ナンバーディスプレイ情報の共用体へのポインタ
	]
********************************************************/
union SYS_ND_InformationContent_t *CMN_ND_HistoryGetRecord(SYS_ND_HistoryHandle_t, UBYTE kind);



/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報取得（発信元電話番号）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
CONST UBYTE *	CMN_ND_GetDialNumber(SYS_ND_HistoryHandle_t);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（発信元電話番号）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetDialNumber(SYS_ND_HistoryHandle_t handle, UBYTE *in_buffer, UWORD length);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報取得（着信時刻）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		着信時刻
	]
********************************************************/
UDWORD 			CMN_ND_GetCalledTime(SYS_ND_HistoryHandle_t);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報取得（着信時刻）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		着信時刻
	]
********************************************************/
UDWORD 			CMN_ND_GetCalledTime(SYS_ND_HistoryHandle_t);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（操作パネルから入力された発信元の名前）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		名前格納したバッファへのポインタ
	]
********************************************************/
CONST UBYTE *	CMN_ND_SetName(SYS_ND_HistoryHandle_t handle, UBYTE *name);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報取得（番号非通知理由）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		理由を表す値
	]
********************************************************/
UBYTE 			CMN_ND_GetReason(SYS_ND_HistoryHandle_t);


/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（番号非通知理由）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		理由を表す値
	]
********************************************************/
void CMN_ND_SetReason(SYS_ND_HistoryHandle_t handle, UBYTE reason);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（着信時刻）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
	]
********************************************************/
void CMN_ND_SetCalledTime(SYS_ND_HistoryHandle_t handle, UDWORD time);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（発信元名前）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetCallerName(SYS_ND_HistoryHandle_t handle, UBYTE *in_buffer, UWORD length);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（備考）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetNote(SYS_ND_HistoryHandle_t handle, UBYTE note);

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（情報受信エラー状態）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetInfoRxError(SYS_ND_HistoryHandle_t handle, UBYTE c);


/********************************************************
 	module [ナンバーディスプレイ着信履歴をクローズ]
 	function	:[
		
	]
	argument 	:[
		1. SYS_ND_HistoryHandle_t handle	現在オープンしているハンドル
		2. UBYTE mode	クローズのモードを指定する
				ND_HISTORY_CLOSE_PRESERVE			保存して終了
				ND_HISTORY_CLOSE_DESTROY			削除して終了
		]
	return 		:[
		
	]
********************************************************/
void CMN_ND_HistoryClose(SYS_ND_HistoryHandle_t handle, UBYTE mode);


#endif /*  __CMN_NDHS_H */
