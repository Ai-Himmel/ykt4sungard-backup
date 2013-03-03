/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA													 */
/*	ファイル名	 : CMN_ND.C													 */
/*	モジュール	 :															 */
/*				 : CMN_ND_Parse()											 */
/*				 : CMN_ND_AnalizeRxInformation()							 */
/*				 : CMN_ND_RxInfoToHistory()									 */
/*	作成者		 : 久保博													 */
/*	日	付		 :	1998/10/07												 */
/*	概	要		 : ナンバーディスプレイデータ解析							 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/

/* 仮のコードです。 by H.Kubo 1998/06/24 */


#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysnd.h"
#include "\src\atlanta\define\cmn_nd.h"
#include "\src\atlanta\define\cmn_ndhs.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\syscomf.h"



#if (PRO_DIALIN == ENABLE) || defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */
#include "\src\atlanta\define\ncu_ret.h"
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)

#define		ND_INFO_LANGTH	128

#define		DLE		(0x10)
#define		ETX		(0x03)
#define		STX		(0x02)
#define		SOH		(0x01)
#define		SI		(0x0f)
#define		SO		(0x0e)

#if 0
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル番号をキーにしてジャンクメール防止番号を検索する]
	function	:[

	]
	return		:[]
	common		:[
		NCU_ND_CarPattern
		SYB_ND_CarPattern[]
	]
	condition	:[]
	comment		:[
			登録されたダイヤル番号中の  「*」 はどの番号にも一致する「ワイルドカード」です。
			登録されたダイヤル番号中の  「-」 はないものとして読み飛ばされます。
			後方一致、登録番号全桁一致で検索します。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/11/22]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE *CMN_ND_FindJunkNoByPhoneNumber(CONST UBYTE *rx_dial, UBYTE length)
{
	UBYTE *junk;
	UBYTE i;
	WORD dial_pos;
	WORD rx_dial_pos;
	WORD rx_dial_pos_max;
	if (rx_dial[0] == '\0') {
		return NULL;
	}
	for (rx_dial_pos = 0; rx_dial_pos < length; rx_dial_pos++) {
		if (!CMN_isdigit(rx_dial[rx_dial_pos])) {
			rx_dial_pos--;
			break;
		}
	}
	if (rx_dial_pos == length) {
		rx_dial_pos--;
	}
	rx_dial_pos_max = rx_dial_pos;
	for (i = 0; i < SYS_JUNK_DIAL_MAX ; i++) {
		junk = SYB_JunkMailProtectDialBuffer[i];
		/* ND 登録されたダイヤルの末尾を探す */
		for (dial_pos = 1; dial_pos <= SYS_DIRECT_DIAL_MAX; dial_pos++) {
			if (junk[dial_pos] == '\0') {
				dial_pos--;
				break;
			}
		}
		while(!(CMN_isdigit(junk[dial_pos]) || ('*' == junk[dial_pos]))) { /* 数字でない文字は飛ばし読み。 */
			if (--dial_pos < 0) {
				break;
			}
		}
		if (dial_pos < 0) {
			continue;
		}
		/* ダイヤル番号マッチ */
		for (rx_dial_pos = rx_dial_pos_max; (rx_dial_pos >= 0) && (dial_pos >= 0); dial_pos--, rx_dial_pos--) {
			while(!(CMN_isdigit(junk[dial_pos]) || ('*' == junk[dial_pos]) ) ) { /* 数字でない文字は飛ばし読み。 */
				if (--dial_pos < 0) {
					break;
				}
			}
			if ((dial_pos < 0) 
			|| (('*' != junk[dial_pos]) && (rx_dial[rx_dial_pos] != junk[dial_pos]))) {
				break;
			}
		}
		if (dial_pos < 0) { /* もし、比較する番号が尽きたのなら、 */
			return junk; /* 発見 */
		}
	}
	return NULL;
}

#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル番号をキーにしてナンバーディスプレイ登録情報を検索する]
	function	:[

	]
	return		:[]
	common		:[
		NCU_ND_CarPattern
		SYB_ND_CarPattern[]
	]
	condition	:[]
	comment		:[
			登録されたダイヤル番号中の  「*」 はどの番号にも一致する「ワイルドカード」です。
			登録されたダイヤル番号中の  「-」 はないものとして読み飛ばされます。
			後方一致、登録番号全桁一致で検索します。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/12]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
struct SYS_NumberDisplayTable *CMN_ND_FindNdTableByPhoneNumber(CONST UBYTE *rx_dial, UBYTE length)
{
	struct SYS_NumberDisplayTable *table;
	UBYTE i;
	WORD dial_pos;
	WORD rx_dial_pos;
	WORD rx_dial_pos_max;
	if (rx_dial[0] == '\0') {
		return NULL;
	}
	for (rx_dial_pos = 0; rx_dial_pos < length; rx_dial_pos++) {
		if (!CMN_isdigit(rx_dial[rx_dial_pos])) {
			rx_dial_pos--;
			break;
		}
	}
	if (rx_dial_pos == length) {
		rx_dial_pos--;
	}
	rx_dial_pos_max = rx_dial_pos;
	for (i = ND_DataNextSearch(0); i < SYS_ND_MAX /* SYS_DIAL_NAME_MAX */; i = ND_DataNextSearch(i + 1)) { /* SYB_NumberDisplay[] の個数を正しく直す。Changed by H.Kubo 1998/11/11 */
		table = SYB_NumberDisplay + i; /* 作業用に ND 登録テーブルへのポインタを設定。 */
		/* ND 登録されたダイヤルの末尾を探す */
		for (dial_pos = 1; dial_pos <= SYS_DIRECT_DIAL_MAX; dial_pos++) {
			if (table->Dial[dial_pos] == '\0') {
				dial_pos--;
				break;
			}
		}
		while(!(CMN_isdigit(table->Dial[dial_pos]) || ('*' == table->Dial[dial_pos]))) { /* 数字でない文字は飛ばし読み。 */
			if (--dial_pos < 0) {
				break;
			}
		}
		if (dial_pos < 0) {
			continue;
		}
		/* ダイヤル番号マッチ */
		for (rx_dial_pos = rx_dial_pos_max; (rx_dial_pos >= 0) && (dial_pos >= 0); dial_pos--, rx_dial_pos--) {
			while(!(CMN_isdigit(table->Dial[dial_pos]) || ('*' == table->Dial[dial_pos]) ) ) { /* 数字でない文字は飛ばし読み。 */
				if (--dial_pos < 0) {
					break;
				}
			}
			if ((dial_pos < 0) 
			|| (('*' != table->Dial[dial_pos]) && (rx_dial[rx_dial_pos] != table->Dial[dial_pos]))) {
				break;
			}
		}
		if (dial_pos < 0) { /* もし、比較する番号が尽きたのなら、 */
			return table; /* 発見 */
		}
	}
	return NULL;
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ナンバーディスプレイ履歴に FAX 交信結果を記録]
	function	:[

	]
	return		:[]
	common		:[
	]
	condition	:[
		FAX 交信中であること
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/17]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void CMN_ND_SetFaxComReportOnNDJrnl(SYS_ND_HistoryHandle_t handle)
{
	if ((handle == SYS_ND_NO_JOURNAL) || (handle >= SYS_ND_JRNL_MAX)) {
		return;
	}
	if ((SYS_FaxComType == SYS_AUTO_CALLED) || (SYS_FaxComType == SYS_MANUAL_RX)) {	/** 自動着信 */ /* 手動送信も by H.Kubo 1998/12/09 */
		handle = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_MODIFY, handle);
		CMN_ND_SetNote(handle, SYS_ND_FAX);
		CMN_ND_HistoryClose(handle, ND_HISTORY_CLOSE_PRESERVE);
	}
}

#if 0
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ナンバーディスプレイの発信者番号とジャンクメール番号の照合]
	function	:[

	]
	return		:[
		TRUE	ジャンクメール番号と一致
		FALSE	ジャンクメール番号と不一致
	]
	common		:[]
	condition	:[
		
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/11/22]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE CMN_ND_CompareJunkMailAndCaller(SYS_ND_HistoryHandle_t handle)
{
	UBYTE buffer[SYS_DIRECT_DIAL_MAX];
	UBYTE rtn;
	if ((handle == SYS_ND_NO_JOURNAL) || (handle >= SYS_ND_JRNL_MAX)) {
		return FALSE;
	}
	handle = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_MODIFY, handle);
	CMN_ND_GetDialNumber(handle, buffer);
	rtn = CMN_ND_FindJunkNoByPhoneNumber(buffer, CMN_StringLength(buffer));
	CMN_ND_HistoryClose(handle, ND_HISTORY_CLOSE_PRESERVE);
	}
	if (rtn == NULL) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}


UBYTE CMN_ND_CheckJunkMail(SYS_ND_HistoryHandle_t handle)
{
	UBYTE junk_mode;

	junk_mode = CHK_BlockJunkFaxMode();
	if ((junk_mode == BLOCK_JUNK_FAX_MODE2) || junk_mode == BLOCK_JUNK_FAX_MODE3)) {
		return CMN_ND_CompareJunkMailAndCaller();
	}
	else {
		return TRUE;
	}
}
#endif

UWORD CMN_ND_FindTailOfRxInfo(UBYTE *info, UWORD length)
{
	UWORD i;
	for (i = 0; i < (length - 1);) {
		if (info[i] == DLE) {
			i++;
			if (info[i] == ETX) {
				return i;
			}
			else if (info[i] == DLE) {
				continue;
			}
		}
		i++;
	}
	return i;
}

UBYTE CMN_ND_FindHeadOfRxParameter(UBYTE *info, UWORD length)
{
	/* <DLE><STX> の並びを探索 */

	UWORD i;

	for (i = 0; i < length - 4; i++) {
		if (info[i] == DLE && info[i+1] == STX) {
			return i;
		}
	}
	return 0;
}

UBYTE CMN_ND_GetMessageLengthIndex(UBYTE *info, UWORD length)
{
	UWORD	i = 0;
	for (i = 0; i < length; i++) {
		if ((info[i] == DLE) && (info[i+1] == STX) && (info[i+2] == 0x40)) {
			if (info[i+3] == DLE) {
				return i+4;
			}
			else {
				return i+3;
			}
		}
	}
	return 0;
}

UWORD CMN_ND_7bitJisCharTo8bitJisChar(UBYTE *dst, UBYTE *src, UWORD length)
{
	UWORD i;
	UWORD dst_length = 0;
	UBYTE is_kana = FALSE;
	UBYTE is_escape = FALSE;

	for (i = 0, dst_length= 0; i < length; i++, src++) {
		switch (*src) {
		case SI:
			is_kana = TRUE;
			is_escape = FALSE;
			break;
		case SO:
			is_kana = FALSE;
			is_escape = FALSE;
			break;
		default:
			if ( (*src == DLE) && (!is_escape)) {
				is_escape = TRUE;
			}
			else {
				is_escape = FALSE;
				if (is_kana) {
					*dst++ = 0x80 | *src;
				}
				else {
					*dst++ = *src;
				}
				dst_length++;
			}
			break;
		}
	}
	return dst_length;
}




UBYTE CMN_ND_GetNextInfoIndex(UBYTE *info, UBYTE index)
{
	UBYTE i;
	if ((i = info[index + 1]) == DLE) {
		i = info[index + 2];
		i += 3; /* 4 to 3 changed by H.Kubo 1998/10/14 */
	}
	else {
		i += 2; /* 3 to 2 changed by H.Kubo 1998/10/14 */
	}
	
	return (index + i);
}

UBYTE CMN_ND_CheckDialinNumber(UBYTE *in)
{
#if defined (KEISATSU) /* 警察FAX make通すため 05/05/07 石橋正和 */
	return D_IN_UNMATCH;
#else
	if (in[0] ==  ND_INFO_DIALIN_NUMBER) {
		return NCU_ND_CheckDialinNumber(in + 2, in[1]);
	}
	else {
		return D_IN_UNMATCH;
	}
#endif
}


void CMN_ND_RxInfoToHistory(SYS_ND_HistoryHandle_t handle, UBYTE *in)
{
	struct SYS_NumberDisplayTable *table;
	switch (in[0]) {
	case ND_INFO_CALLER_NUMBER:
		CMN_ND_SetDialNumber(handle, in + 2, in[1]);
		table = CMN_ND_FindNdTableByPhoneNumber(in + 2,in[1]);
		if (table != NULL) {
			CMN_ND_SetCallerName(handle, table->Name, CMN_StringLength(table->Name) + 1);
		}
		break;
	case ND_INFO_CALLER_NUMBER_REASON:
		CMN_ND_SetReason(handle, in[2]);
		break;
	}
}

SYS_ND_HistoryHandle_t CMN_ND_Parse(UBYTE *buffer, UWORD length, UBYTE *dialin_status)
{
	SYS_ND_HistoryHandle_t history;
	UBYTE	tail;
	UBYTE	work_index;
	UBYTE 	info_head;
	UBYTE	n_of_info;
	UBYTE	info_length;
	UBYTE 	i;
#if (PRO_DIALIN == ENABLE) /* added by H.Kubo 1998/10/14 */
	if (dialin_status != NULL) {
		*dialin_status = D_IN_UNMATCH;
	}
#endif

	/* 情報の先頭を見つける */
	work_index = CMN_ND_FindHeadOfRxParameter(buffer, length);
	if (work_index == 0 ) {
		/* 失敗。 */
	}
	tail = work_index + CMN_ND_FindTailOfRxInfo(buffer + work_index, length - work_index);
	/* 情報のメッセージ内容長を獲得 */
	info_head = work_index + CMN_ND_GetMessageLengthIndex(buffer + work_index, length - work_index);

	/* パラメータ種別、情報内容を次々に獲得 */
	info_length = buffer[info_head];
	history = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_EMPTY, NULL);
	CMN_ND_HistoryClear(history); /* 1998/10/20 */
	work_index = info_head + 1;
	while (work_index < tail) {
#if 0 /* Changed by H.Kubo 1998/09/29 */
@		CMN_ND_StoreToHistory(buffer + work_index);
#endif
		CMN_ND_RxInfoToHistory(history, buffer + work_index);
#if (PRO_DIALIN == ENABLE) /* added by H.Kubo 1998/10/14 */
		if ((dialin_status != NULL) && (*dialin_status == D_IN_UNMATCH)) {
			*dialin_status = CMN_ND_CheckDialinNumber(buffer + work_index);
		}
#endif
		work_index = CMN_ND_GetNextInfoIndex(buffer, work_index);
		if (work_index >= length) {
			break; /* 受信データ数を超えたら、処理を強制終了 */
		}
	}
	CMN_ND_SetCalledTime(history, SYB_CurrentTime);
	CMN_ND_SetInfoRxError(history, ND_V23_DATA_RECEIVED);

	CMN_ND_HistoryClose(history, ND_HISTORY_CLOSE_PRESERVE);
	return history;
}

UBYTE CMN_ND_AnalizeRxInformation(UBYTE *in_buffer, UWORD length, UBYTE *dialin_status)
{
	return (UBYTE) CMN_ND_Parse(in_buffer, length, dialin_status);

}


UBYTE CMN_ND_SetEmptyHistory(void)
{
	SYS_ND_HistoryHandle_t history;
	history = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_EMPTY, NULL);
	CMN_ND_HistoryClear(history); /* 1998/10/27 */
	CMN_ND_SetReason(history, SYS_ND_V23_RX_ERROR);
	CMN_ND_SetCalledTime(history, SYB_CurrentTime); /* 1998/10/26 */
	CMN_ND_HistoryClose(history, ND_HISTORY_CLOSE_PRESERVE);
	return (UBYTE) history;
}

UBYTE CMN_ND_SetV23ErrorHistory(UBYTE error)
{
	SYS_ND_HistoryHandle_t history;
	history = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_EMPTY, NULL);
	CMN_ND_HistoryClear(history); /* 1998/10/27 */
	CMN_ND_SetReason(history, SYS_ND_V23_RX_ERROR);
	CMN_ND_SetInfoRxError(history, error);
	CMN_ND_SetCalledTime(history, SYB_CurrentTime); /* 1998/10/26 */
	CMN_ND_HistoryClose(history, ND_HISTORY_CLOSE_PRESERVE);
	return (UBYTE) history;
}

UBYTE CMN_ND_SetFnetHistory(void)
{
	SYS_ND_HistoryHandle_t history;
	history = CMN_ND_HistoryOpen(ND_HISTORY_OPEN_EMPTY, NULL);
	CMN_ND_HistoryClear(history); /* 1998/10/27 */
	CMN_ND_SetReason(history, SYS_ND_F_NET);
	CMN_ND_SetCalledTime(history, SYB_CurrentTime); /* 1998/10/26 */
	CMN_ND_HistoryClose(history, ND_HISTORY_CLOSE_PRESERVE);
	return (UBYTE) history;
}
#endif /* (PRO_NUMBER_DISPLAY == ENABLE) */
