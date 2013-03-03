/* 仮のコードです。 by H.Kubo 1998/06/24 */


/* 着信履歴用構造体 */

#define 		SYS_ND_FAX
#define			SYS_ND_TEL1
#define			SYS_ND_TEL2



SYS_ND_HistoryHandle CMN_ND_HistoryWriteOpen()
{
	SYS_ND_HistoryHandle_t	handle = SYS_ND_INVALID_HANDLE;
	return handle;
}

struct SYS_NumberDisplayHistory_t {
	UDWORD		interval;	/* 通話秒数 */
	TIME_DATA_t	time;		/* 着信日時 */
	UBYTE		line;		/* 回線の種類 */
	UBYTE		service;	/* 通新前／通信中（キャッチホン）*/
	UBYTE		kind; 		/* FAX/TEL1/TEL2 & AGGREATED(複数の着信の集約情報) */
	union {
		struct	{
			UBYTE	number;		/* 通信管理記録の番号 */
			UBYTE	date[6];	/* BCD 表現の年月日 */
		} journal_id;			/* 通信管理記録の主キー */
		UWORD 	number_of_call;		/* 集約情報の場合のみ有効。集約された着信の回数。*/
	} option;
} SYB_ND_History[SYS_ND_HISTORY_MAX];

UBYTE	SYB_ND_HistoryCounter;


UBYTE SYB_ND_CallerInformationCount;


CMN_ND_ClearHistory()
{
	int i;
	SYS_NumberDisplayHistory_t *ptr_history;
	
	ptr SYB_ND_History

	for (i = 0, ptr_history = &SYB_ND_History; i < SYS_ND_HISTORY_MAX; i++, ptr_history++) {
		ptr_history->interval 	= 0;
		ptr_history->date		= 0;
		ptr_history->id			= 0;
		ptr_hisotry->line		= 0;
		ptr_history->service	= 0;
		ptr_history->kind		= 0;
	}
}

UBYTE CMN_ND_FindEmptyInfoRecord()
{
	UBYTE	i;

	for (i = 0; i < SYS_ND_CALLER_INFO_MAX; i++) {
		if (SYB_ND_CallerInformation[i].id >= SYS_ND_HISTORY_MAX) {
			return i;
		}
	}
	return i;
}


CMN_ND_RegisterNewHistory(UBYTE *rx_buffer)
{
	UBYTE	i;
	UBYTE	hist_index;
	for (i = 0; i < SYS_ND_HISTORY_MAX; i++) {
		if (SYB_ND_History[i].kind == NULL) {
			hist_index = i;
			break;
		}
	}

	/* ヘッダ読み出し */
	/* 情報読み出し */
}





UBYTE CMN_ND_PrepareEmptyRecordOfHistory()
{
	UBYTE history_index;
	UBYTE n_of_parameter;


	/* ND 情報の パラメータの個数を獲得 */
	n_of_parameter = CMN_ND_CountParameterOfRxInfo(EcmBuffer);

	/* ND 情報のパラメータを格納するだけの記憶場所はあるか ? */
	if (SYB_ND_HistoryCount >= SYS_ND_HISTORY_MAX) {
		/* 記憶場所を空ける。*/
	}

	if (SYB_ND_CallerInformationCount + n_of_parameter > SYS_ND_CALLER_INFO_MAX) {
		/* 記憶場所を空ける。*/
	}
	return history_index;
}

CMN_ND_WriteToHistory()
{
	UBYTE history_index;
	UBYTE n_of_parameter;
	UBYTE	info_record_index;
	UBYTE *parameter_field;
	struct SYS_ND_CallerInformation_t *info_record;

	/* semaphore 処理を入れるべし */

	history_index = CMN_ND_PrepareEmptyRecordOfHistory(EcmBuffer);
	SYB_ND_HistoryCount++;
	/* 履歴をきれいにする。*/

	/* 着信したことを記憶 */
	SYB_ND_History[history_index].kind = ND_HISTORY_ANSWERED;

	/* 回線を記憶 */

	/* 着信の日時を記憶 */
	
	/* ナンバーディスプレイの情報を記憶。*/
	n_of_parameter = CMN_ND_CountParameterOfRxInfo(EcmBuffer);
	
	parameter_field = CMN_ND_FindHeadOfRxParameter(EcmBuffer);

	info_record_index = CMN_ND_NextCallerInformationRecord(0);
	info_record = &SYB_ND_CallerInformation[info_record_index];
	for (i = 0; i < n_of_parameter; i++) {
		info_record->id = history_index;
		if ( CMN_ND_StoreCallerInformation(info_record, parameter_field) ) {
			info_record->kind = parameter_field[0];
			info_record_index = CMN_ND_NextCallerInformationRecord(info_record_index);
			if (info_record_index >= SYS_ND_CALLER_INFO_MAX) {
				SetAddressAndJumpBegin();
			}
			info_record = &SYB_ND_CallerInformation[info_record_index];
		}
		else {
		}
	}

}




/*************************************************************************
	module		:[ナンバーディスプレイ情報を格納]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/09/03]
	author		:[久保博]
*************************************************************************/
CMN_ND_StoreToHistory()
{
	UBYTE empty_record;
	/* 空きエリアを獲得*/
	empty_record = CMN_ND_NextCallerInformationRecord(0);
	/* 空きエリアがなければ、 */
	if (empty_record >= SYS_ND_CALLER_INFO_MAX) {
		/* 古い履歴を消去して */
		DeleteOldestHistory();
		/* 空きエリアを獲得*/
		empty_record = CMN_ND_NextCallerInformationRecord(0);
		if (empty_record >= SYS_ND_CALLER_INFO_MAX) {
			/* こうなったらバグ。 */
		}
	}
	/* 格納 */
}

















UBYTE CMN_ND_StoreCallerInformation(struct SYS_ND_CallerInformation_t *call_info, UBYTE *parameter_field)
{
	UWORD length;
	UBYTE	kind = parameter_field[0];
	if (parameter_field[1] == DLE) { /* 情報長が 0x10 (DLE)  のときは、情報フィールドが一つずれる。*/
		parameter_field++;
	}
	switch (kind) {
	case	ND_INFO_CALLER_NUMBER:
	case	ND_INFO_DIALIN_NUMBER:
	case	ND_INFO_TRANSFERER_NUMBER:
		caller_info->number.length = (parameter_field[1] > SYS_ND_INFO_NUMBER_LENGTH_MAX) ? SYS_ND_INFO_NUMBER_LENGTH_MAX : parameter_field[1];
		CMN_StringCopyNum(caller_info->number.number, parameter_field + 2, caller_info->number.length);
		break;
	case	ND_INFO_CALLER_EXTRA:
	case	ND_INFO_DIALIN_EXTRA:
	case	ND_INFO_TRANSFERER_EXTRA:
		caller_info->extra_number.type_of_number = parameter_field[2];
		caller_info->extra_number.number_plan_identifier[0] = parameter_field[3];
		caller_info->extra_number.number_plan_identifier[1] = parameter_field[4];
		break;
	case	ND_INFO_CALLER_NUMBER_REASON:
	case	ND_INFO_CALLER_NAME_REASON:
		caller_info->reason = parameter_field[2];
		break;
	case	ND_INFO_CALLER_NAME:
	case	ND_INFO_PUBLIC_PHONE:
		length = (parameter_field[1] > SYS_ND_INFO_TEXT_LENGTH_MAX) ? SYS_ND_INFO_TEXT_LENGTH_MAX : parameter_field[1];
		caller_info->name.length = CMN_ND_7bitJisCharTo8bitJisChar(caller_info->name.text, parameter_field + 2, length);
		break;
	case	ND_INFO_MESSAGE:
		length = (parameter_field[1] > SYS_ND_INFO_TEXT_LENGTH_MAX + 5) ? SYS_ND_INFO_TEXT_LENGTH_MAX + 5 : parameter_field[1];
		if (length < 5) {
			CMN_StringCopyNum(caller_info->message_info.message_status, parameter_field + 2, length);
			CMN_MemorySet(caller_info->message_info.message_status + length, '\0', 5 - length);
			caller_info->message_info.length = 0;
		}
		else {
			CMN_StringCopyNum(caller_info->message_info.number, parameter_field + 2, 5);
			caller_info->message_info.length = CMN_ND_7bitJisCharTo8bitJisChar(caller_info->message_info.text, parameter_field + 2 + 5, length - 5);
		}
		break;
	case	ND_INFO_TIME:
			if (parameter_field[1] == 0x08) {
				caller_info->time.month[0] = parameter_field[2 + 0];
				caller_info->time.month[1] = parameter_field[2 + 1];
				caller_info->time.day[0] = parameter_field[2 + 2];
				caller_info->time.day[1] = parameter_field[2 + 3];
				caller_info->time.hour[0] = parameter_field[2 + 4];
				caller_info->time.hour[1] = parameter_field[2 + 5];
				caller_info->time.minute[0] = parameter_field[2 + 6];
				caller_info->time.minute[1] = parameter_field[2 + 7];
			}
			else {
				CMN_MemorySet(caller_info->time.month, '\0',8);
				return FALSE;
			}
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;
}


UBYTE CMN_ND_NextCallerInformationRecord(UBYTE i)
{
	for (; i < SYS_ND_CALLER_INFO_MAX; i++) {
		if (SYB_ND_CallerInformation[i].id >=  SYS_ND_HISTORY_MAX) {
			break;
		}
	}
	return i;
}


UBYTE CMN_ND_FindOldestHistoryRecord()
{
	UBYTE i;
	UBYTE oldest;
	UDWORD oldest_time;
	UDWORD long_time;
	

	for (i = 0; i <SYS_ND_HISTORY_MAX; i++) {
		if ( SYB_ND_History[i].kind & ND_HISTORY_ANSWERED) {
			break;
		}
	}

	oldest_time = CMN_BCD_TimeToLong( &(SYB_ND_History[i].time) );
	for (oldest = i; i < SYS_ND_HISTORY_MAX; i++) {
		if ( SYB_ND_History[i].kind & ND_HISTORY_ANSWERED) {
			long_time = CMN_BCD_TimeToLong( &(SYB_ND_History[i].time) );
			if ( long_time < oldest_time ) {
				oldest_time = long_time;
				oldest = i;
			}
		}
	}
	return oldest;
}

UBYTE CMN_ND_DeleteRxInfoRecords(UBYTE id)
{
	UBYTE	i;
	UBYTE	counter;

	for (i = 0, counter = 0; i < SYS_ND_CALLER_INFO_MAX; i++) {
		if (SYB_ND_CallerInformation[i].id == i) {
			SYB_ND_CallerInformation[i].id = SYS_ND_HISTORY_MAX;
			counter++;
		}
	}
	return counter;
}


UBYTE CMN_ND_DeleteOldestHistoryRecord(void)
{
	UBYTE i;
	UBYTe ret;
	
	/* 一番古い履歴の番号を獲得。*/
	i = CMN_ND_FindOldestHistoryRecord();
	/* 先にナンバーディスプレイ情報を削除 */
	ret = CMN_ND_DeleteRxInfoRecords(i);
	/* 最後に着信履歴情報を削除 */
	SYB_ND_History[i].kind = 0;
	return ret;
}


SYS_ND_InformationContent_t *CMN_ND_FindCallerInfoOfHistoryRecord(UBYTE id, UBYTE info_kind)
{
	UBYTE i;
	for (i = 0; i < SYS_ND_CALLER_INFO_MAX; i++) {
		if ((SYB_ND_CallerInformation[i].id == id) 
		&&  (SYB_ND_CallerInformation[i].kind == info_kind) ) {
			return &( SYB_ND_CallerInformation[i].info_field);
		}
	}
	return NULL;
}


CMN_ND_FindPairOfHistoryOfSameCaller(UBYTE *one, UBYTE *another)
{
	UBYTE one_index;
	UBYTE another_index;
	SYS_ND_InformationContent_t	*one_content;
	SYS_ND_InformationContent_t *another_content;

	/* 番号非通知理由による検索 */
	for (one_index = 0; one_index < SYS_ND_HISTORY_MAX; one_index++) {
		one_content = CMN_ND_FindCallerInfoOfHistoryRecord(one_index, ND_INFO_CALLER_NUMBER_REASON);
		for (another_index = one_index + 1; another_index < SYS_ND_HISTORY_MAX; another_index++) {
			another_content == CMN_ND_FindCallerInfoOfHistoryRecord(another_index, ND_INFO_CALLER_NUMBER_REASON))
			if ((one_content->reason.reason == another_content->reason.reason ) {
				*one = one_index;
				*another = another_index;
				return ND_INFO_CALLER_NUMBER_REASON;
			}
		}
	}

	/* 企業名による検索 */
	
		/* 未実装 */
	
	/* 公衆電話情報による検索 */

		/* 未実装 */

	/* 番号一致による検索 */
	for (one_index = 0; one_index < SYS_ND_HISTORY_MAX; one_index++) {
		one_content = CMN_ND_FindCallerInfoOfHistoryRecord(one_index, ND_INFO_CALLER_NUMBER);
		for (another_index = one_index + 1; another_index < SYS_ND_HISTORY_MAX; another_index++) {
			another_content == CMN_ND_FindCallerInfoOfHistoryRecord(another_index, ND_INFO_CALLER_NUMBER))
			if ((one_content->number.length == another_content->number.length ) 
			&&  (CMN_StringCompare(one_content->number.number, another_content->number.number, one_content->number.length) == STRCMP_EQUAL) {
				*one = one_index;
				*another = another_index;
				return ND_INFO_CALLER_NUMBER;
			}
		}
	}
	return FALSE;
}





#if 0 /* DOS 用動作確認プログラム*/

SYS_ND_CallerInformation_t caller_info[] = {
	{	0,
		ND_INFO_CALLER_NUMBER,
		{
}

main()
{
	SYS_ND_HistoryHandle_t hs_handle;
	
	if ((hs_handle = CMN_ND_HistoryOpen(ND_HISTORY_WRITE_MODE)) == SYS_ND_INVALID_HANDLE) {
		/* エラー */
	}
	CMN_ND_HistoryWrite(hs_handle, );
	CMN_ND_HistoryClose();
	
	if ((hs_handle = CMN_ND_HistoryOpen(ND_HISTORY_READ_MODE)) == SYS_ND_INVALID_HANDLE) {
		/* エラー */
	}
	for (;hs_handle != SYS_ND_INVALID_HANDLE; hs_handle = CMN_ND_HistoryNext(hs_handle)) {
		CMN_ND_HistoryRead(hs_handle, kind);
	}
}

#endif

