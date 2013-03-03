/*---------------------------------------------------------------------------*/
/*  プロジェクト : ATLANTA/SAKAKI                                            */
/*  ファイル名   : mdm_nd.c                                                  */
/*  作成者       : 久保博                                                    */
/*  日  付       : 1997/10/08                                                */
/*  概  要       : ナンバーディスプレイ着信履歴                              */
/*  修正履歴     :                                                           */
/*	keyword      :[CMN]                                                      */
/*	machine      :[SH7043]                                                   */
/*	language     :[SHC]                                                      */
/*---------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysnd.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"

#include "\src\atlanta\define\cmn_ndhs.h"


#if (PRO_NUMBER_DISPLAY == ENABLE)

/* SYB_NumberDisplayJournal を着信履歴に使う場合のメソッドです。 */


/********************************************************
 	module [ナンバーディスプレイ着信履歴を全消去]
 	function	:[	]
	argument 	:[	]
	return 		:[	]
********************************************************/
void CMN_ND_EraseAllHistory(void)
{
	
	UBYTE i;
	struct SYS_NumberDisplayJournalTable *journal;
	journal = SYB_NumberDisplayJournal;
	for (i = 0; i < SYS_ND_JRNL_MAX; i++, journal++) {
		journal->Status = SYS_ND_EMPTY;
		journal->CalledTime = 0;
		CMN_MemorySet(journal->Dial, SYS_DIRECT_DIAL_MAX, 0x0);
		CMN_MemorySet(journal->Name, SYS_DIAL_NAME_MAX, 0x0);
		journal->Reason = 0x0;
		journal->Note = 0x0;
		journal->InformationRxError = 0x00;
		journal->Reserve1 = 0x0;
		journal->Reserve2 = 0x0;
		journal->Reserve3 = 0x0;
		journal->Reserve4 = 0x0;
	}
	SYB_NumberDisplayJournalPoint = 0;
}

/********************************************************
 	module [ナンバーディスプレイ着信履歴をオープン]
 	function	:[
		
	]
	argument 	:[
		1. UBYTE mode	オープンのモードを指定する
						ND_HISTORY_OPEN_EMPTY			空の履歴をオープンする。書き込み用。
						ND_HISTORY_OPEN_MODIFY			指定履歴をオープンする。書き込み用。
						ND_HISTORY_OPEN_NEWEST			最新の履歴をオープンする。読み出し用。
						ND_HISTORY_OPEN_OLDEST			最古の履歴をオープンする。読み出し用。
	]
	return 		:[
		履歴のハンドル
					SYS_ND_INVALID_HANDLE				オープンに失敗
					その他								オープンに成功
	]
********************************************************/
SYS_ND_HistoryHandle_t CMN_ND_HistoryOpen(UBYTE mode, SYS_ND_HistoryHandle_t handle)
{
	SYS_ND_HistoryHandle_t i;
	if (mode == ND_HISTORY_OPEN_EMPTY) {
		i = SYB_NumberDisplayJournalPoint;
		do { /* 空いている領域を探します。 */
			if (!(SYB_NumberDisplayJournal[i].Status &  (SYS_ND_WRITING | SYS_ND_MODIFYING))) {
				SYB_NumberDisplayJournal[i].Status |= SYS_ND_WRITING;
				
				return i;
			}
			if (++i >= SYS_ND_JRNL_MAX) {
				i = 0;
			}
		} while ( i != SYB_NumberDisplayJournalPoint);
	} else if (mode == ND_HISTORY_OPEN_MODIFY) {
		if (handle >= SYS_ND_JRNL_MAX) {
			SaveReturnAddressAndJumpBegin();
		}
		while (SYB_NumberDisplayJournal[handle].Status  &  (SYS_ND_WRITING | SYS_ND_MODIFYING)) {
			wai_tsk(10/10);
		}
		SYB_NumberDisplayJournal[handle].Status |= SYS_ND_MODIFYING;
		return handle;
	}
	return SYB_NumberDisplayJournalPoint;
}

/********************************************************
 	module [ナンバーディスプレイ着信履歴を消す]
 	function	:[
		
	]
	argument 	:[
	]
	return 		:[
		履歴のハンドル
	]
********************************************************/
void CMN_ND_HistoryClear(SYS_ND_HistoryHandle_t handle)
{
	UBYTE null = '\0';
	if ((handle >= 0) && (handle < SYS_ND_JRNL_MAX)) {
		CMN_ND_SetDialNumber(handle, &null, 1);
		CMN_ND_SetReason(handle, SYS_ND_NONE);
		CMN_ND_SetCalledTime(handle, 0);
		CMN_ND_SetCallerName(handle, &null, 1);
		CMN_ND_SetNote(handle, 0);
		CMN_ND_SetInfoRxError(handle, 0);
	}
	return;
}

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
 function 		:[ナンバーディスプレイ着信履歴情報格納（発信元電話番号）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetDialNumber(SYS_ND_HistoryHandle_t handle, UBYTE *in_buffer, UWORD length)
{
	/* SYS_DIRECT_DIAL_MAX より length が短ければ、length 分だけ履歴に格納する。 */
	CMN_StringCopyNumOrNULL(&SYB_NumberDisplayJournal[handle].Dial[0], in_buffer, 
							((length > SYS_DIRECT_DIAL_MAX) ? SYS_DIRECT_DIAL_MAX : length));
	return;
}

#if 0
/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報取得（発信元電話番号）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_GetDialNumber(SYS_ND_HistoryHandle_t handle, UBYTE *in_buffer)
{
	/* SYS_DIRECT_DIAL_MAX より length が短ければ、length 分だけ履歴に格納する。 */
	CMN_StringCopyNumOrNULL(&SYB_NumberDisplayJournal[handle].Dial[0], in_buffer, SYS_DIRECT_DIAL_MAX);
	return;
}
#endif

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（番号非通知理由）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		理由を表す値
	]
********************************************************/
void CMN_ND_SetReason(SYS_ND_HistoryHandle_t handle, UBYTE reason)
{
	SYB_NumberDisplayJournal[handle].Reason = reason;
}


/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（着信時刻）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
	]
********************************************************/
void CMN_ND_SetCalledTime(SYS_ND_HistoryHandle_t handle, UDWORD time)
{
	SYB_NumberDisplayJournal[handle].CalledTime = time;
}


/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（発信元名前）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetCallerName(SYS_ND_HistoryHandle_t handle, UBYTE *in_buffer, UWORD length)
{
	/* SYS_DIRECT_DIAL_MAX より length が短ければ、length 分だけ履歴に格納する。 */
	CMN_StringCopyNumOrNULL(&SYB_NumberDisplayJournal[handle].Name[0], in_buffer, 
							((length > SYS_DIAL_NAME_MAX) ? SYS_DIAL_NAME_MAX : length));
	return;
}


/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（備考）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetNote(SYS_ND_HistoryHandle_t handle, UBYTE note)
{
	SYB_NumberDisplayJournal[handle].Note = note;
	return;
}

/********************************************************
 function 		:[ナンバーディスプレイ着信履歴情報格納（情報受信エラー状態）]
	argument 	:[
		1  SYS_ND_HistoryHandle_t handle	現在のハンドル
	]
	return 		:[
		ダイヤル番号を格納したバッファへのポインタ
	]
********************************************************/
void CMN_ND_SetInfoRxError(SYS_ND_HistoryHandle_t handle, UBYTE c)
{
	SYB_NumberDisplayJournal[handle].InformationRxError = c;
	return;
}



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
void CMN_ND_HistoryClose(SYS_ND_HistoryHandle_t handle, UBYTE mode)
{

	CMN_DisableInterrupt();
	if (SYB_NumberDisplayJournal[handle].Status & SYS_ND_WRITING) { /* 書き込みオープンされていたら、*/
		if (++SYB_NumberDisplayJournalPoint >= SYS_ND_JRNL_MAX) { /* 書き込みポイントを一つ進める */
			SYB_NumberDisplayJournalPoint = 0;
		}
		SYB_NumberDisplayJournal[handle].Status &= ~SYS_ND_WRITING;
		SYB_NumberDisplayJournal[handle].Status |= SYS_ND_SET;
	}
	if (SYB_NumberDisplayJournal[handle].Status & SYS_ND_MODIFYING) { /* 修正オープンされていたら、*/
		SYB_NumberDisplayJournal[handle].Status &= ~SYS_ND_MODIFYING;
	}
	CMN_EnableInterrupt();

}



#endif /* (PRO_NUMBER_DISPLAY == ENABLE) */
