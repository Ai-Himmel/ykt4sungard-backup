/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_TBOK.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 電話帳オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\io_pro.h"
#endif

/* Prototype
void	GetTelephoneBookMode();
UWORD	SearchTelBookTopPosition(UBYTE);
UWORD	SetNextTelBookData(UBYTE);
UBYTE 	Shortcut_NUMBER(UBYTE,UBYTE);
void	SetTelephoneBook(UWORD);
UBYTE	GetTelBookKeyWord(UWORD);
UBYTE	GetTelBookSortPriority(UBYTE);
UWORD	SearchTelBookInsertPosition(UWORD, UBYTE);
UBYTE	CompareRemoteName(UWORD, UWORD);
void	ShiftTelBookData(UWORD, UBYTE);
void	InsertNewTelBookData(UWORD, UBYTE, UWORD);
void	DeleteTelBookData(UWORD);
UBYTE	TelephoneBookOperation(UBYTE);
void	TelBookUpSearch(void);
void	TelBookDownSearch(void);
void	TelBookLeftSearch(void);
void	TelBookRightSearch(void);
void	ResetTelBookDataExistPoint(void);
UBYTE	TelBookStartOperation(UBYTE, UBYTE);
void	DisplayTelBookOperation(void);
UWORD	GetTelBookDataPoint(void);
void	ResortTelephoneBookData(void);
*/

#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//static UBYTE	TelBookDataPointer = 0;	/* 電話帳検索時、参照位置 */
#endif
static UWORD	TelBookDataPointer = 0;	/* 電話帳検索時、参照位置 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０仕様と同じです) Added by SMuratec L.Z.W 2003/09/27 */
static	UBYTE	TOP_TelBookMode = 0;		/* 電話帳検索時、先頭モード */
static	UBYTE	BEF_TelBookMode = 0;		/* 電話帳検索時、参照前モード */

static	UBYTE	TelBookMode = 0;			/* 電話帳検索時、参照モード */
#define	TelBook_KANA			0			/* カナモード */
#define	TelBook_ALPHABET		1			/* 英字モード */
#define	TelBook_CODE			2			/* 記号モード */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０仕様と同じです)Added by SMuratec L.Z.W 2003/09/27 */
/*************************************************************************
	module		:[電話帳データのモード設定]
	function	:[電話帳表示の現在のモードを設定する]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/16]
	author		:[佐々木佳世]
*************************************************************************/
void	GetTelephoneBookMode()
{
	UBYTE	chk_order;
	UBYTE	set_order;

	chk_order = (UBYTE)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_SORTPRIORITY];

	set_order = GetTelBookSortPriority('0');
	if (set_order <= chk_order) {
		TelBookMode = TelBook_CODE;			/* 記号モード */
	}
	else {
		if (TOP_TelBookMode == TelBook_KANA) {
			set_order = GetTelBookSortPriority('A');	/* 入力テーブルの変更に伴い"AlphamericCharacterTable[1][0]"を "A"に変更	2001/07/27 K.Sasaki */
			if (set_order <= chk_order) {
				TelBookMode = TelBook_ALPHABET;			/* アルファベットモード */
			}
			else {
				TelBookMode = TelBook_KANA;				/* カナモード */
			}
		}
		else {
			TelBookMode = TelBook_ALPHABET;			/* アルファベットモード */
		}
		BEF_TelBookMode = TelBookMode;			/* 前モードの保管 */
	}

}

/*************************************************************************
	module		:[データ先頭位置の検索]
	function	:[]
	return		:[データ先頭位置]
	common		:[
					SYB_TelephoneBookData
					SYB_TelBookDataEnd
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/05/30]
	author		:[佐々木佳世]
*************************************************************************/
UWORD	SearchTelBookTopPosition(
			UBYTE	sort_priority
		)
{
	UWORD	loop_i;
	UBYTE	priority;

	for (loop_i = 0; loop_i < SYB_TelBookDataEnd; loop_i++) {
		priority = (UBYTE)SYB_TelephoneBookData[loop_i][OPR_TELBOOK_SORTPRIORITY];
		if (priority >= sort_priority) {
			break;
		}
	}

	return (loop_i);
}

/*************************************************************************
	module		:[電話帳データの次データ設定]
	function	:[電話帳の次データのポイントを設定します｡]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/17]
	author		:[佐々木佳世]
*************************************************************************/
UBYTE	SetNextTelBookData(
			UBYTE	chk_char
		)
{
	UBYTE	set_order;
	UWORD	chk_point;
	UBYTE	chk_order;

	set_order = GetTelBookSortPriority(chk_char);
	chk_point = SearchTelBookTopPosition(set_order);
	chk_order = (UBYTE)SYB_TelephoneBookData[chk_point][OPR_TELBOOK_SORTPRIORITY];
	if (TelBookSortPriorityTable[set_order] != TelBookSearchLineTable[chk_order]) {
		return (NG);
	}
	else {
		TelBookDataPointer = chk_point;
		return (OK);
	}
}

/*************************************************************************
	module		:[ショートカット処理]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/19]
	author		:[佐々木佳世]
*************************************************************************/
UBYTE Shortcut_NUMBER(
		UBYTE	mode,
		UBYTE	key
)
{
	UBYTE	set_char;
	UBYTE	set_order;
	UBYTE	loop_i;
	UBYTE	alpha_MAX;

	switch (mode) {
	case TelBook_KANA:				/* カナモード */
		set_char = KATAKANA_CharacterTable[OPR_GetCharacterTable1stArrange(key)][0];
		if (SetNextTelBookData(set_char) != OK) {
			NackBuzzer();
		}
		break;
	case TelBook_ALPHABET:			/* 英字モード */
		if ( (key == TEN_1_KEY)
		  || (key == TEN_0_KEY) ) {
			NackBuzzer();
		}
		else {
			switch (key) {
			case TEN_7_KEY:
			case TEN_9_KEY:
				alpha_MAX = 7;
				break;
			default:
				alpha_MAX = 5;
				break;
			}
			set_order = OPR_GetCharacterTable1stArrange(key);
			for (loop_i = 0; loop_i < alpha_MAX; loop_i++) {
				set_char = AlphamericCharacterTable[set_order][loop_i];
				if (SetNextTelBookData(set_char) == OK) {
					break;
				}
			}
			if (loop_i >= alpha_MAX) {
				NackBuzzer();
			}
		}
		break;
	default:
		NackBuzzer();
		break;
	}
}

/* (電話帳でテンキーの動作はV-650と同じくなります) Added start by SMuratec L.Z.W 2003/10/20 */
/*************************************************************************
	module		:[電話帳データ表示セット（アルファベット）]
	function	:[電話帳表示の先頭（アルファベット）をセットする]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/16]
	author		:[佐々木佳世]
*************************************************************************/
void	SetTelephoneBook_AlphabetTop()
{
	UBYTE	set_order;

	set_order = GetTelBookSortPriority('A');	/* 入力テーブルの変更に伴い"AlphamericCharacterTable[1][0]"を "A"に変更	2001/07/27 K.Sasaki */
	TelBookDataPointer = SearchTelBookTopPosition(set_order);
	if (TelBookDataPointer >= SYB_TelBookDataEnd) {			/* 該当データが無い */
		set_order = GetTelBookSortPriority('0');
		TelBookDataPointer = SearchTelBookTopPosition(set_order);
	}
}


/*************************************************************************
	module		:[電話帳データ表示セット（カナ）]
	function	:[電話帳表示の先頭（カナ）をセットする]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/16]
	author		:[佐々木佳世]
*************************************************************************/
void	SetTelephoneBook_KanaTop()
{
	UBYTE	set_order;

	set_order = GetTelBookSortPriority(KATAKANA_CharacterTable[0][0]);
	TelBookDataPointer = SearchTelBookTopPosition(set_order);
	if (TelBookDataPointer >= SYB_TelBookDataEnd) {			/* 該当データが無い */
		SetTelephoneBook_AlphabetTop();
	}
}
/* Added end by SMuratec L.Z.W 2003/10/20 */
/* 移植 by SMuratec L.Z.W 2003/11/06 */
/*************************************************************************
	module		:[文字列比較（電話帳）]
	function	:[
		1.2つの文字列を電話帳の順序で比較する
	]
	return		:[
		1.STRCMP_LOWER(-1):string1がstring2より小さい
		2.STRCMP_EQUAL( 0):string1とstring2は等しい
		3.STRCMP_UPPER( 1):string1がstring2より大きい
	]
	common		:[
		1."12"と"123"では"12"の方が小さい
		2.""と"1"では"1"の方が小さい
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/06/14]
	author		:[松隈]
*************************************************************************/
UBYTE	CMN_StringCompareTelBook(
UBYTE	*string1,		/* 比較する文字列 */
UBYTE	*string2,		/* 比較する文字列 */
UBYTE	size)			/* 比較する文字列長 */
{
	UBYTE	ret;				/* 比較結果 */
	UBYTE	i;					/* loop */
	UBYTE	j;
	UBYTE	k;
	UWORD	char1;				/* String1の１ﾊﾞｲﾄ */
	UWORD	char2;				/* String2の１ﾊﾞｲﾄ */

	/*------------------------------*/
	/**	文字列のアドレス変換		*/
	/*------------------------------*/
	string1 = CalculateStringAddress(string1);
	string2 = CalculateStringAddress(string2);

	/* 頭からスペースがはいっている場合は、文字がくるまでとばす
		でも、すべてスペースの場合は、記号としてあつかう		*/
	for (; string1 != NULL; string1++) {
		if (*string1 != ' ') {
			break;
		}
	}
	for (; string2 != NULL; string2++) {
		if (*string2 != ' ') {
			break;
		}
	}

	ret = STRCMP_EQUAL;
	for (i = 0; i < size; i++) {
		if (*string1 != *string2) {
			char1 = *string1;
			if (char1 == NULL) {
				ret = STRCMP_LOWER;
				break;
			}
			char2 = *string2;
			if (char2 == NULL) {
				ret = STRCMP_UPPER;
				break;
			}
#if (0)	/* for文の条件が間違っていた 2000/06/22 By M.Maeda */
//			for (j = 0; j < size; j++) {
//				if (TelBookSortPriorityTable[j] == char1) {
//					break;
//				}
//			}
//			for (k = 0; k < size; k++) {
//				if (TelBookSortPriorityTable[k] == char2) {
//					break;
//				}
//			}
#else
			for (j = 0; TelBookSortPriorityTable[j] != NULL; j++) {
				if (TelBookSortPriorityTable[j] == char1) {
					break;
				}
			}
			for (k = 0; TelBookSortPriorityTable[k] != NULL; k++) {
				if (TelBookSortPriorityTable[k] == char2) {
					break;
				}
			}
#endif
			if (j < k) {
				ret = STRCMP_LOWER;
			}
			else {
				ret = STRCMP_UPPER;
			}
			break;
		}
		if (*string1 == NULL && *string2 == NULL) {
			break;
		}
		string1++;
		string2++;
	}
	return (ret);
}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/*************************************************************************
	module		:[電話帳データセット]
	function	:[
		1.電話帳格納テーブルに新規データを登録する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		電話帳テーブルは音の順番にソートされている
		ワンタッチ＋短縮が２５５を越える場合、引数、その他を変更せなあかん

		data_number
			0 - SYS_ONETOUCH_MAX - 1									:ワンタッチダイアル
			SYS_ONETOUCH_MAX - SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX	:短縮ダイアル
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//void SetTelephoneBook(UBYTE new_data_number)	/* ワンタッチ・短縮番号 */
#endif
void SetTelephoneBook(UWORD new_data_number)	/* ワンタッチ・短縮番号 */
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	insert_position;	/* 電話帳データ新規登録位置 */
#endif
	UWORD	insert_position;	/* 電話帳データ新規登録位置 */
	UBYTE	sort_order;			/* ソート順 */
	UBYTE	key_word;			/* 頭文字 */

	/* 初期化 */
	insert_position = 0;
	key_word = 0;

	/** 古い電話帳データを削除する */
	DeleteTelBookData(new_data_number);

	/** 新たに電話帳に登録される相手先名の頭文字を求める */
	key_word = GetTelBookKeyWord(new_data_number);

	if (key_word == NULL) { /** 相手先名が登録されていない場合（このパスは恐らくないと思う（登録されない限りセットされないから)） */
		/**終了 */
		return;
	}

	/** 電話帳に格納し、データをソートするときの優先順位を頭文字から求める */
	sort_order = GetTelBookSortPriority(key_word);

	/* 頭文字が特殊文字（ウムラウト等）の場合、電話帳には登録しません */
	/* 取り敢えず。こうしておく。 1996/06/20 Eguchi */
	if (sort_order == 0xFF) { /* 頭文字が特殊文字の場合 */
		/* 電話帳には登録しません */
		return;
	}

	/** 電話帳に格納する際の挿入位置を求める */
	insert_position = SearchTelBookInsertPosition(new_data_number, sort_order);

	/** 電話帳に登録する */
	ShiftTelBookData(insert_position, SHIFT_BACKWORD);
	InsertNewTelBookData(new_data_number, sort_order, insert_position);
}

/*************************************************************************
	module		:[頭文字を取り出す]
	function	:[
		1.与えられた短縮・ワンタッチデータの相手先名の頭文字を取り出す
		2.濁音,拗音は無視します
	]
	return		:[頭文字]
	common		:[
				SYB_OnetouchDial
				SYB_SpeedDial
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//UBYTE GetTelBookKeyWord(UBYTE data_number)
#endif
UBYTE GetTelBookKeyWord(UWORD data_number)
{
	UBYTE	key_word;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 先頭スペース対応　Added by SMuratec L.Z.W 2003/11/06 */
	UBYTE	loop_i;
	
	for (loop_i = 0; loop_i < SYS_DIAL_NAME_MAX; loop_i++) {
		if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチダイアル */
			key_word = SYB_OnetouchDial[data_number].Name[loop_i];
		}
		else {									/* 短縮 (上限はみない) */
			key_word = SYB_SpeedDial[data_number - SYS_ONETOUCH_MAX].Name[loop_i];
		}
		if (key_word != ' ') {
			break;
		}
	}
	if (key_word == NULL) {
		key_word = ' ';
	}
#else
	if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチダイアル */
		key_word = SYB_OnetouchDial[data_number].Name[0];
	}
	else {									/* 短縮 (上限はみない) */
		data_number -= SYS_ONETOUCH_MAX;
		key_word = SYB_SpeedDial[data_number].Name[0];
	}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	return (key_word);
}

/*************************************************************************
	module		:[音順の取り出し]
	function	:[
		1.与えられた頭文字から、電話帳データのソート順（音順）を求める
	]
	return		:[
				0xFF: 電話帳に登録できない
				ソート順]
	common		:[TelBookSortPriorityTable]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
UBYTE GetTelBookSortPriority(UBYTE key_word)
{
	UBYTE	i;

	for (i = 0; TelBookSortPriorityTable[i] != NULL; i++) {
		if (TelBookSortPriorityTable[i] == key_word) {
			return (i);
		}
	}
	return (0xFF);
}

/*************************************************************************
	module		:[データ格納位置の検索]
	function	:[
		1.
	]
	return		:[データ格納位置]
	common		:[
				SYB_TelephoneBookData
				SYB_TelBookDataEnd
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//UBYTE SearchTelBookInsertPosition(UBYTE data_number, UBYTE sort_priority)
#endif
UWORD SearchTelBookInsertPosition(UWORD data_number, UBYTE sort_priority)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	loop;
#endif
	UWORD	loop;
	UBYTE	priority;

	for (loop = 0; loop < SYB_TelBookDataEnd; loop++) {
		priority = (UBYTE)SYB_TelephoneBookData[loop][OPR_TELBOOK_SORTPRIORITY];
		if (priority > sort_priority) {			/* 新しく登録される相手先名の頭文字　＜　登録されている相手先名の頭文字 */
			break;
		}
		else if (priority == sort_priority) {	/* 新しく登録される相手先名の頭文字　==　登録されている相手先名の頭文字 */
			/* 頭文字が同じデータがある場合 */
			/* ２文字目以降で比較して挿入位置を求める */
			if (CompareRemoteName(loop, data_number) == OK)
				break;
		}
	}
	return (loop);
}

/*************************************************************************
	module		:[相手先名の比較]
	function	:[
		1.
	]
	return		:[
				OK:新しく電話帳にセットするデータの方が前に来る(指定されて位置にセットできる)
				NG:新しく電話帳にセットするデータの方が後になる(指定された位置にセットでけへん)
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//UBYTE CompareRemoteName(UBYTE data_point, UBYTE new_number)
#endif
UBYTE CompareRemoteName(UWORD data_point, UWORD new_number)
{
	BYTE	cmp_result;
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_number;
#endif
	UWORD	data_number;
	UBYTE	*new_name;
	UBYTE	*remote_name;

	/** 新たに登録された相手先名を取り出す */

	if (new_number < SYS_ONETOUCH_MAX) {	/** ワンタッチダイアルの場合 */
		/** ワンタッチダイアルから相手先名を取り出す */
		new_name = &(SYB_OnetouchDial[new_number].Name[0]);
	}
	else {									/** 短縮ダイアルの場合 */
		/** 短縮ダイアルから相手先名を取り出す */
		new_name = &(SYB_SpeedDial[new_number - SYS_ONETOUCH_MAX].Name[0]);
	}

	data_number = (UWORD)SYB_TelephoneBookData[data_point][OPR_TELBOOK_DATANUMBER];

	/** 格納されている相手先名を取り出す */
	/* 相手先が登録されていないということは絶対ない */

	if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチの場合 */
		remote_name = &(SYB_OnetouchDial[data_number].Name[0]);
	}
	else {									/* 短縮ダイアルの場合 */
		remote_name = &SYB_SpeedDial[data_number - SYS_ONETOUCH_MAX].Name[0];
	}

	/** 文字列の比較 */
	/* 新しく登録される相手先名と、既に登録されている相手先名の比較 */
	/* 文字毎にASCII列で比較しているのでたとえば"ハヒフ"と”バヒフ”の場合、
	** ２文字目の'゛'と'ヒ’を比較してしまいます。不都合がでたら検討します
	*/
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/11/06 */
	cmp_result = CMN_StringCompareTelBook(new_name, remote_name, SYS_DIAL_NAME_MAX - 1);
#else
	cmp_result = CMN_StringCompare(new_name, remote_name, SYS_DIAL_NAME_MAX - 1);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	if (cmp_result == STRCMP_LOWER) { /* 新しい名前の方が前に来る */
		/** 終了 */
		return (OK);
	}
	else if (cmp_result == STRCMP_EQUAL) { /* 全く同じ名前 */
		/* ワンタッチ・短縮の順番でデータ挿入位置を決める */
		/* 順番：ワンタッチＡ < Ｂ <･･･< Ⅳ < 短縮001 < 002・・・・*/
		if (data_number < new_number) /* 後にくる */
			return (NG);
		else
			return (OK);
	}
	else { /* 新しい名前の方が大きくなる(後にくる) */
		return (NG);
	}
}

/*************************************************************************
	module		:[電話帳データのシフト]
	function	:[
		1.電話帳にデータを格納する際、格納位置以降のデータを後ろにずらす
		2.電話帳でーたの登録限界位置も更新します
	]
	return		:[]
	common		:[
					SYB_TelephoneBookData
					SYB_TelBookDataEnd
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//void ShiftTelBookData(UBYTE data_pointer, UBYTE shift_mode)
#endif
void ShiftTelBookData(UWORD data_pointer, UBYTE shift_mode)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	i;
#endif
	UWORD	i;

	if (shift_mode == SHIFT_BACKWORD) {	/* データを後ろにシフト */
		for (i = SYB_TelBookDataEnd; i > data_pointer; i--) {
			SYB_TelephoneBookData[i][OPR_TELBOOK_DATANUMBER]   = SYB_TelephoneBookData[i - 1][OPR_TELBOOK_DATANUMBER];
			SYB_TelephoneBookData[i][OPR_TELBOOK_SORTPRIORITY] = SYB_TelephoneBookData[i - 1][OPR_TELBOOK_SORTPRIORITY];
		}
		SYB_TelBookDataEnd++; /* 登録最終位置を進める */
	}
	else {								/* データを前にシフト（詰める） */
		for (i = data_pointer; i < SYB_TelBookDataEnd; i++) {
			SYB_TelephoneBookData[i][OPR_TELBOOK_DATANUMBER]   = SYB_TelephoneBookData[i + 1][OPR_TELBOOK_DATANUMBER];
			SYB_TelephoneBookData[i][OPR_TELBOOK_SORTPRIORITY] = SYB_TelephoneBookData[i + 1][OPR_TELBOOK_SORTPRIORITY];
		}
		/* 最後のデータは初期化しておく */
#if (PRO_SPEED_DIAL_ADDITION == ENABLE)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
		SYB_TelephoneBookData[SYS_TELBOOK_MAX][OPR_TELBOOK_DATANUMBER] = 0xFFFF;
#else
		SYB_TelephoneBookData[SYS_TELBOOK_MAX][OPR_TELBOOK_DATANUMBER] = 0xFF;
#endif
		SYB_TelBookDataEnd--;	/* 登録最終位置を戻す */
	}
}

/*************************************************************************
	module		:[電話帳データ格納]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//void InsertNewTelBookData(UBYTE data_number, UBYTE sort_priority, UBYTE insert_point)
#endif
void InsertNewTelBookData(UWORD data_number, UBYTE sort_priority, UWORD insert_point)
{
#if (PRO_SPEED_DIAL_ADDITION == ENABLE)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
	SYB_TelephoneBookData[insert_point][OPR_TELBOOK_DATANUMBER]   = data_number;
	SYB_TelephoneBookData[insert_point][OPR_TELBOOK_SORTPRIORITY] = (UWORD)sort_priority;
#else
	SYB_TelephoneBookData[insert_point][OPR_TELBOOK_DATANUMBER]   = (UBYTE)data_number;
	SYB_TelephoneBookData[insert_point][OPR_TELBOOK_SORTPRIORITY] = sort_priority;
#endif
}

/*************************************************************************
	module		:[電話帳データ削除]
	function	:[
		1.前回登録されたデータを削除
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/23]
	author		:[江口]
*************************************************************************/
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//void DeleteTelBookData(UBYTE data_number)	/* ワンタッチ・短縮番号 */
#endif
void DeleteTelBookData(UWORD data_number)	/* ワンタッチ・短縮番号 */
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	i;
#endif
	UWORD	i;

	for (i = 0; i < SYB_TelBookDataEnd; i++) {	/* 電話帳の登録最終位置まで検索 */
		if ((UWORD)SYB_TelephoneBookData[i][OPR_TELBOOK_DATANUMBER] == data_number) {	/* 同一データがある */
			break;
		}
	}

	if (i == SYB_TelBookDataEnd) {	/* 消去するデータがない */
		return;
	}
	else {							/* 消去するデータ以降のデータを前に詰める */
		ShiftTelBookData(i, SHIFT_FORWORD);
	}
}

/*************************************************************************
	module		:[電話帳検索オペレーションメイン]
	function	:[
		1.電話帳を使って発呼する際の相手先の検索を行う.
		2.スタートキーを押された時の状態で電話を掛けるのか、通信を行うのか、終了するのか決定する
		3.電話帳オペレーションに入ってくるのは、短縮が２回連続で押された時で、状態は以下のものがある。
		, 1.電話オペレーションから、電話帳オペレーションにくる場合。
		, 2.コマンドオペレーションから電話帳オペレーションにくる場合。
		, 3.電話オペレーションからコマンドオペレーションを通って電話帳オペレーションにくる場合.
	]
	return		:[
			TELBOOK_END	(2)
			TELBOOK_FAXCOM(3)
			TELBOOK_TEL(4)
			TELBOOK_TEL_ON_HOOK(5)
			TELBOOK_BROADCAST(6)
			TELBOOK_SPEED_KEY(7)
			TELBOOK_SET(8)
				]
	common		:[]
	condition	:[
				mode:OPR_COM_OPE:コマンドオペレーションからコール
					 OPR_TEL_OPE:電話オペレーションからコール]
	comment		:[スタートキー押下時の条件を詰める必要あり 1995/09/04]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/24]
	author		:[江口]
*************************************************************************/
UBYTE TelephoneBookOperation(UBYTE mode)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	status;
	UBYTE	line;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/11/06 */
	UBYTE	chk_point;
	UBYTE	set_order;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/* 電話帳テーブルにデータが存在するか調べる */
	if (SYB_TelBookDataEnd == 0) { /* 登録最終位置が電話帳テーブルの先頭にある */
		/* データなし */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		return (TELBOOK_END);
	}


	/**初期設定 */
	TelBookDataPointer = 0; /*電話帳テーブル参照位置 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (電話帳でテンキーの動作はV-650と同じくなります)　Added by SMuratec L.Z.W 2003/10/20 */
	TOP_TelBookMode = TelBook_KANA;		/* 先頭モードの初期化 */
#if defined(JPN)						/* 先頭モード設定 */
	SetTelephoneBook_KanaTop();
#else
	SetTelephoneBook_AlphabetTop();
#endif
	GetTelephoneBookMode();
	TOP_TelBookMode = TelBookMode;		/* 先頭モードの保管 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	while (1) {
		/** 電話帳オペレーション表示 (相手先表示)*/
		DisplayTelBookOperation();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key 	= GetInputKeyCode();
		keytype = GetInputKeyType();
		line 	= CheckLineStatus();

		switch (keytype) { /** 取り込んだキーに対する処理  */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０仕様と同じです)Modify by SMuratec L.Z.W 2003/09/27 */
		case LEFT_ARROW:
			/* 左方向検索 */
			TelBookLeftSearch();
			break;
		case FUNCTION:
			/* 右方向検索 */
			TelBookRightSearch();
			break;
		case NUMBER:					/* 数字キー */
			if (SYB_TelBookDataEnd  == 1) {	/* データ１件のみ */
				NackBuzzer();
			}
			else {
				switch (TelBookMode) {
				case TelBook_KANA:				/* カナモード */
				case TelBook_ALPHABET:			/* 英字モード */
					Shortcut_NUMBER(TelBookMode, key);
					break;
				default:
					Shortcut_NUMBER(BEF_TelBookMode, key);
					GetTelephoneBookMode();
					break;
				}
			}
			break;
		/* 記号で検索追加　Added by SMuratec L.Z.W 2003/11/06 */
		case SHARP:						/* ＃キー */
		case AST:						/* ＊キー */
			if (SYB_TelBookDataEnd  == 1) {	/* データ１件のみ */
				NackBuzzer();
			}
			else {
				set_order = GetTelBookSortPriority('0');
				chk_point = SearchTelBookTopPosition(set_order);
				if (chk_point >= SYB_TelBookDataEnd) {
					NackBuzzer();
				}
				else {
					TelBookMode = TelBook_CODE;
					TelBookDataPointer = chk_point;
				}
			}
			break;
		/* (カナモードと英字モードで交替追加) Added by SMuratec L.Z.W 2003/11/11 */
		case CHARACTER:					/* 文字キー */
			if (SYB_TelBookDataEnd  == 1) {	/* データ１件のみ */
				NackBuzzer();
			}
			else {
				switch (TelBookMode) {
				case TelBook_KANA:				/* カナモード */
					chk_point = TelBookDataPointer;
					set_order = GetTelBookSortPriority('A');	/* 入力テーブルの変更に伴い"AlphamericCharacterTable[1][0]"を "A"に変更	2001/07/27 K.Sasaki */
					TelBookDataPointer = SearchTelBookTopPosition(set_order);
					if (TelBookDataPointer >= SYB_TelBookDataEnd) {
						TelBookDataPointer = chk_point;
						NackBuzzer();
					}
					else {
						GetTelephoneBookMode();
						if (TelBookMode != TelBook_ALPHABET) {
							TelBookMode = TelBook_KANA;
							TelBookDataPointer = chk_point;
							NackBuzzer();
						}
					}
					break;
				case TelBook_ALPHABET:			/* 英字モード */
					if (TOP_TelBookMode == TelBook_ALPHABET) {
						NackBuzzer();
					}
					else {
						chk_point = TelBookDataPointer;
						set_order = GetTelBookSortPriority(0xB1);	/* ｱ */
						TelBookDataPointer = SearchTelBookTopPosition(set_order);
						if (TelBookDataPointer >= SYB_TelBookDataEnd) {
							TelBookDataPointer = chk_point;
							NackBuzzer();
						}
						else {
							GetTelephoneBookMode();
							if (TelBookMode != TelBook_KANA) {
								TelBookMode = TelBook_ALPHABET;
								TelBookDataPointer = chk_point;
								NackBuzzer();
							} /* if (TelBookMode != TelBook_KANA) */
						} /* if (TelBookDataPointer >= SYB_TelBookDataEnd) */
					} /* if (TOP_TelBookMode == TelBook_ALPHABET) */
					break;
				default:
					if (TOP_TelBookMode != TelBook_KANA) {	/* アルファベット・記号のみ */
						NackBuzzer();
					}
					else {									/* カナ有り */
						if (BEF_TelBookMode == TelBook_ALPHABET) {	/* カナ・アルファベット・記号 */
							SetTelephoneBook_KanaTop();
							GetTelephoneBookMode();
						}
						else {
							chk_point = TelBookDataPointer;
							SetTelephoneBook_AlphabetTop();
							GetTelephoneBookMode();
							if (TelBookMode != TelBook_ALPHABET) {	/* カナ・記号 */
								TelBookMode = TelBook_CODE;
								TelBookDataPointer = chk_point;
								NackBuzzer();
							}
						}
					}
					break;
				}	/* switch (TelBookMode)*/
			}	/* if (SYB_TelBookDataEnd  == 1) */
			break;

#else
		case NUMBER:	/* 数字キー */
			switch (key) {
			case TEN_2_KEY:
				/* 上方向検索 */
				TelBookUpSearch();
				break;
			case TEN_8_KEY:
				/* 下方向検索 */
				TelBookDownSearch();
				break;
			case TEN_4_KEY:
				/* 左方向検索 */
				TelBookLeftSearch();
				break;
			case TEN_6_KEY:
				/* 右方向検索 */
				TelBookRightSearch();
				break;
			default:
				NackBuzzer();
				break;
			}
			break;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case START:		/* スタートキー */
			if ((status = TelBookStartOperation(mode, line)) != OPR_CONTINUE) {
				return (status);
			}
			break;
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:		/* １分間キー入力なし */
			/** 終了 */
			return (TELBOOK_END);
		case HOOK:			/* フックキー */
			/* フックキーオフフック時にしか有効でない */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
			if (line & OPR_HOOKKEY_OFFHOOK) {
				HookKeySet();
			}
			else {
				NackBuzzer();
			}
 #else
			if (line == OPR_HOOKKEY_OFFHOOK)
				HookKeySet();
			else
				NackBuzzer();
 #endif /* defined (KEISATSU) */
			break;
		case BROADCAST:		/* 同報キー   */
			/* コマンドオペレーションからきても、既に同報入力されていても、ＴＥＬ１が
			   があがっていたら同報入力はできない ラベンダー、椛で確認*/
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
			if ((line & OPR_TEL1_OFFHOOK) || (line & OPR_HOOKKEY_OFFHOOK)) {
 #else
			if ((line == OPR_TEL1_OFFHOOK) || (line == OPR_HOOKKEY_OFFHOOK)) {
 #endif /* defined (KEISATSU) */
				NackBuzzer();
			}
			else { /* 受話器下がり又はTEL2オフフック */
				return (TELBOOK_BROADCAST);
			}
			break;
		case SPEED:
			/* 電話帳オペレーションを終了して短縮入力モードに戻る */
			return (TELBOOK_SPEED_KEY);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			if ((key  == OPR_TEL_OPERATION) && (mode == OPR_TEL_OPE) && (line == OPR_NCU_IDLE)) {
				/** 電話帳オペレーション終了 */
#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/01 */
				HookLedOff();
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
				return (TELBOOK_END);
			}
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[上方向検索]
	function	:[
		1.検索行を上方向に移動.行単位の検索
		2.ア←カ←・・・←Ａ←！←０
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/05]
	author		:[江口]
*************************************************************************/
void TelBookUpSearch(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_pointer;
#endif
	UWORD	data_pointer;
	UBYTE	search_line;
	UBYTE	old_search_line;

	/* 現在の検索行の退避 */
	old_search_line = TelBookSearchLineTable[SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_SORTPRIORITY]];
	data_pointer = TelBookDataPointer;

	if (data_pointer == 0) { /*先頭*/
		data_pointer = SYB_TelBookDataEnd;
	}
	data_pointer--;

	/* 検索行が変わるまでループ */
	while (data_pointer != TelBookDataPointer) {	/* 電話長テーブルを１周するまで */
		search_line = TelBookSearchLineTable[SYB_TelephoneBookData[data_pointer][OPR_TELBOOK_SORTPRIORITY]];
		if (search_line != old_search_line) { /* 行が変わった */
			old_search_line = search_line;	  /* 次に移る行を退避 */
			break;							  /* ループを抜ける   */
		}
		if (data_pointer == 0) { /* 先頭まで来た */
			data_pointer = SYB_TelBookDataEnd;
		}
		data_pointer--;
	}

	if (data_pointer == TelBookDataPointer) {
		/* 異なる行が存在しない場合.ex)登録されているものが全てア行から始まる*/
		/* 先頭に移しておく */
		TelBookDataPointer = 0;
		return;
	}
	else { /* 異なる行が存在する場合 ex)ア行から始まるものとカ行から始まるものが登録されている場合など */
		/* その行の先頭の位置を求める */
		for (data_pointer = 0; data_pointer < SYB_TelBookDataEnd; data_pointer++) {
			search_line = TelBookSearchLineTable[SYB_TelephoneBookData[data_pointer][OPR_TELBOOK_SORTPRIORITY]];
			if (search_line == old_search_line) { /* 先頭発見 */
				TelBookDataPointer = data_pointer;/* 参照位置を更新 */
				return;							  /* 終了 */
			}
		}
		/* ここにきたらバグ */
	}
}

/*************************************************************************
	module		:[下方向検索]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/05]
	author		:[江口]
*************************************************************************/
void TelBookDownSearch(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_pointer;
#endif
	UWORD	data_pointer;
	UBYTE	search_line;
	UBYTE	old_search_line;

	old_search_line = TelBookSearchLineTable[SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_SORTPRIORITY]];
	data_pointer = TelBookDataPointer;

	data_pointer++;
	if (data_pointer >= SYB_TelBookDataEnd) {
		data_pointer = 0;
	}

	/* 検索行が変わるまでループ */
	while (data_pointer != TelBookDataPointer) {
		search_line = TelBookSearchLineTable[SYB_TelephoneBookData[data_pointer][OPR_TELBOOK_SORTPRIORITY]];
		if (search_line != old_search_line) { /* 行が変わった */
			TelBookDataPointer = data_pointer;
			return;
		}
		data_pointer++;
		if (data_pointer >= SYB_TelBookDataEnd) {
			data_pointer = 0;
		}
	}

	if (data_pointer == TelBookDataPointer) {
		/* 異なる行が存在しない場合.ex)登録されているものが全てア行から始まる*/
		/* 先頭に移しておく */
		TelBookDataPointer = 0;
		return;
	}
}

/*************************************************************************
	module		:[左方向検索]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/05]
	author		:[江口]
*************************************************************************/
void TelBookLeftSearch(void)
{
	/* 電話帳テーブル上を降順に移動 */
	if (TelBookDataPointer == 0) {/*先頭の場合*/
		TelBookDataPointer = SYB_TelBookDataEnd;
	}
	TelBookDataPointer--;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (電話帳でテンキーの動作はV-650と同じくなります) Added by SMuratec L.Z.W 2003/10/21 */
	GetTelephoneBookMode();			/* モード設定 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[右方向検索]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/05]
	author		:[江口]
*************************************************************************/
void TelBookRightSearch(void)
{
	/* 電話帳テーブル上を昇順に移動 */
	TelBookDataPointer++;
	if (TelBookDataPointer >= SYB_TelBookDataEnd) {
		TelBookDataPointer = 0;
	}
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (電話帳でテンキーの動作はV-650と同じくなります) Added by SMuratec L.Z.W 2003/10/21 */
	GetTelephoneBookMode();			/* モード設定 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[電話帳スタートオペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/01/05]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE TelBookStartOperation(UBYTE mode, UBYTE line)
{
	UBYTE	ret;

	ret = OPR_CONTINUE;

	/*------------------------------------------------------------------------*/
	/* スタートキー押下時の機器状態により、電話。ＦＡＸ通信。終了を切り分ける */
	/*------------------------------------------------------------------------*/

#if (PRO_FBS == ENABLE)
	/* ポプラＢでは、ブックに原稿があるかを検出できないために、ＡＤＦに原稿がないという
	** 条件で電話発呼するとまずいので、自動電話発呼は行わない仕様にします
	*/
	if (mode == OPR_TEL_OPE) {	/* 電話中の電話帳操作 */
		/* 絶対にＴＥＬ１オフフックかフックキーオフフック */
		ret = TELBOOK_TEL;
	}
	else {	/* OPR_COM_OPE */	/* コマンド登録時の電話帳操作 */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
		if ((line & OPR_TEL1_OFFHOOK) || (line & OPR_HOOKKEY_OFFHOOK)) {	/* TEL1オフフック又はフックキーオフフック */
 #else
		if (line == OPR_TEL1_OFFHOOK || line == OPR_HOOKKEY_OFFHOOK) {	/* TEL1オフフック又はフックキーオフフック */
 #endif /* defined (KEISATSU) */
			if ((CheckInputBroadcast() == FALSE)
			 && (CheckInputSpecialCommand() == FALSE)
			 && (SpecialCommandValue.Page == 0)) {	/* 枚数指定されていない 97/12/02 T.Fukumoto */
				/* 同報も応用通信もセットされていない */
				ret = TELBOOK_TEL;
			}
			else {
				/* 同報または応用機能がセットされている */
				ret = TELBOOK_SET;
			}
		}
		else {															/* TEL2オフフックまたは電話はあがっていない */
			if (CheckInputBroadcast() == TRUE) {	/* 同報入力中である */
				ret = TELBOOK_SET;
			}
			else {									/* 同報入力でない */
				ret = TELBOOK_FAXCOM;
			}
		}
	}
	return (ret);
#else
	if (mode == OPR_TEL_OPE) {	/* 電話中の電話帳操作 */
		/* 絶対にＴＥＬ１オフフックかフックキーオフフック */
		ret = TELBOOK_TEL;
	}
	else {	/* OPR_COM_OPE */	/* コマンド登録時の電話帳操作 */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
		if ((line & OPR_TEL1_OFFHOOK) || (line & OPR_HOOKKEY_OFFHOOK)) {	/* TEL1オフフック又はフックキーオフフック */
 #else
		if (line == OPR_TEL1_OFFHOOK || line == OPR_HOOKKEY_OFFHOOK) {	/* TEL1オフフック又はフックキーオフフック */
 #endif /* defined (KEISATSU) */
			if ((CheckInputBroadcast() == FALSE)
			 && (CheckInputSpecialCommand() == FALSE)
			 && (SpecialCommandValue.Page == 0)) {	/* 枚数指定されていない 97/12/02 T.Fukumoto */
				/* 同報も応用通信もセットされていない */
				ret = TELBOOK_TEL;
			}
			else {
				/* 同報または応用機能がセットされている */
				ret = TELBOOK_SET;
			}
		}
		else {															/* TEL2オフフックまたは電話はあがっていない */
			if ((CheckInputBroadcast() == FALSE)		/* 同報入力中でない */
			 && (CheckInputSpecialCommand() == FALSE)	/* 応用機能はセットされていない */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
			 && !(line & OPR_TEL2_OFFHOOK)				/* 電話はあがっていない */
 #else
			 && (line != OPR_TEL2_OFFHOOK)				/* 電話はあがっていない */
 #endif /* defined (KEISATSU) */
			 && (SpecialCommandValue.Page == 0)			/* 枚数指定されていない 97/12/02 T.Fukumoto */

#if (0)
** 			 && (CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE)) [	/* スキャン不可能(原稿がないetc) */
#else
			 && ((CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) != OPR_SCAN_ENABLE)	/* スキャン不可能(原稿がないetc) */
			 	|| (CheckScanDisableCondition() == TRUE))) {						/* ｼﾞｬﾑﾘｶﾊﾞｰｵﾍﾟﾚｰｼｮﾝ等が起こっている *//* Add By O.Kimoto 1999/07/19 */
#endif

				/*------------------------------------------------------------*
				 * 同報入力中でなく、かつ応用機能はセットされていなくて、かつ *
				 * 電話はオンフック状態で、かつ原稿読み取りが不可能な場合     *
				 *------------------------------------------------------------*/
				if (CheckFaxComExecute() == FALSE) {	/* 通信中でない (回線があいている) */
					OPR_ChildErrorFlag = OPR_NO_ERROR;
					ret = TELBOOK_TEL;	/* 電話発呼を行う */
				}
				else {									/* 通信中の場合*/
					NackBuzzer(); /* NG */
				}
			}
			else {
				/*------------------------------------------------------------*
				 * 同報入力中である。または応用機能がセットされている。または *
				 * TEL2がオフフックされている。または原稿読み取りが可能な場合 *
				 *------------------------------------------------------------*/
				if (CheckInputBroadcast() == TRUE) {	/* 同報入力中である */
					ret = TELBOOK_SET;
				}
				else {									/* 同報入力でない */
					ret = TELBOOK_FAXCOM;
				}
			}
		}
	}
	return (ret);
#endif	/* (PRO_FBS == ENABLE) */
}

/*************************************************************************
	module		:[電話帳オペレーション表示]
	function	:[
		1.電話帳データ表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/24]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayTelBookOperation(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_number;
#endif
	UWORD	data_number;
	UBYTE	order;
	UWORD	option_number;		/* 任意短縮番号 */

	/* チャイルド表示処理 */
	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 上段表示はV650と同じくなります。Added by SMuratec L.Z.W 2003/11/06 */
	/* 上段表示文字列：「ﾃﾞﾝﾜﾁｮｳ         [A]」[]の中は検索ラインの先頭文字 */
	order = (UBYTE)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_SORTPRIORITY];
	data_number = (UWORD)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_DATANUMBER];

	CMN_StringCopyNULL(FunctionDisplayBufferHigh, D2W_TelephoneBookMode);
	if (TelBookMode != TelBook_ALPHABET) {
		if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチ */
			FunctionDisplayBufferHigh[18] = SYB_OnetouchDial[data_number].Name[0];
		}
		else {									/* 短縮 */
			FunctionDisplayBufferHigh[18] = SYB_SpeedDial[(data_number - SYS_ONETOUCH_MAX)].Name[0];
		}
	}
	else {
		FunctionDisplayBufferHigh[18] = TelBookSearchLineTable[order];
	}

	/* 下段表示文字列作成 : 「ABCDEF         :B  ] 相手先名とダイアルデータ */
	if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチ */
		CMN_StringCopyNumUntilNull(FunctionDisplayBufferLow, SYB_OnetouchDial[data_number].Name, 15);
		FunctionDisplayBufferLow[15] = ':';
		/* ワンタッチ記号を表示 */
		SetOnetouchCode(&FunctionDisplayBufferLow[16],
						CMN_OffsetToOnetouchCode((UBYTE)data_number), OPR_SET_ONETOUCH_CODE);
	}
	else {									/* 短縮 */
		data_number -= SYS_ONETOUCH_MAX;
		CMN_StringCopyNumUntilNull(FunctionDisplayBufferLow, SYB_SpeedDial[data_number].Name, 15);
		FunctionDisplayBufferLow[15] = ':';
		/* 短縮番号表示 */
		FunctionDisplayBufferLow[16] = OPR_SPEED_MARK;
		if (!CHK_UNI_OptionalSpeedDial()) {	/* 通常の短縮の時 */
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[17],
								 (UWORD)(data_number + OPR_SPEED_DIAL_MIN),
								 (UBYTE)SPEED_FIGURE_MAX,
								 '0');
		}
		else {								/* 任意短縮の時 */
			option_number = GetRecordFromNumber(data_number);
			if (option_number != 0xFFFF) {
				CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[17], option_number, (UBYTE)SPEED_FIGURE_MAX, '0');
			}
			else {
				CMN_MemorySet(&FunctionDisplayBufferLow[17], (UWORD)SPEED_FIGURE_MAX, (UBYTE)0x2A);
			}
		}
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);
#else
	/* 上段表示文字列：「ﾃﾞﾝﾜﾁｮｳ         [A]」[]の中は検索ラインの先頭文字 */
	CMN_StringCopyNULL(FunctionDisplayBufferHigh, D2W_TelephoneBookMode);
	order = (UBYTE)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_SORTPRIORITY];
	FunctionDisplayBufferHigh[18] = TelBookSearchLineTable[order];

	/* 下段表示文字列作成 : 「ABCDEF         :B  ] 相手先名とダイアルデータ */
	data_number = (UWORD)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_DATANUMBER];

	if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチ */
		/* 相手先名取り出し */
		CMN_StringCopy(FunctionDisplayBufferLow, SYB_OnetouchDial[data_number].Name);
		FunctionDisplayBufferLow[15] = ':';
		/* ワンタッチ記号を表示 */
		SetOnetouchCode(&FunctionDisplayBufferLow[16],
						CMN_OffsetToOnetouchCode((UBYTE)data_number), OPR_SET_ONETOUCH_CODE);
	}
	else {									/* 短縮 */
		data_number -= SYS_ONETOUCH_MAX;
		/* 相手先名取り出し */
		CMN_StringCopy(FunctionDisplayBufferLow, SYB_SpeedDial[data_number].Name);
		FunctionDisplayBufferLow[15] = ':';
		/* 短縮番号表示 */
		FunctionDisplayBufferLow[16] = OPR_SPEED_MARK;
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[17],
								 (UWORD)(data_number + OPR_SPEED_DIAL_MIN),
								 (UBYTE)SPEED_FIGURE_MAX,
								 '0');
		}
		else{		/* 任意短縮の時 */
			option_number = GetRecordFromNumber(data_number);
			if( option_number != 0xFFFF ){
				CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[17], option_number, (UBYTE)SPEED_FIGURE_MAX, '0');
			}
			else{
				CMN_MemorySet(&FunctionDisplayBufferLow[17], (UWORD)SPEED_FIGURE_MAX, (UBYTE)0x2A);
			}
		}
	}

	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	DisplayStringLow(0, FunctionDisplayBufferLow);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//UBYTE GetTelBookDataPoint(void)
#endif
UWORD GetTelBookDataPoint(void)
{
	return(TelBookDataPointer);
}

/*************************************************************************
	module		:[リモート診断後の電話帳データの並び替え]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/04]
	author		:[江口]
*************************************************************************/
void ResortTelephoneBookData(void)
{
	UWORD	i;
	struct	SYS_SpeedDialData_t *dp;

	/** 電話帳テーブルを初期化する */ /*SYB_TelephoneBookData[SYS_TELBOOK_MAX + 1] */
	for (i = 0 ;i <= SYS_TELBOOK_MAX; i++) {
#if (PRO_SPEED_DIAL_ADDITION == ENABLE)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
		SYB_TelephoneBookData[i][OPR_TELBOOK_DATANUMBER] = 0xFFFF;
#else
		SYB_TelephoneBookData[i][OPR_TELBOOK_DATANUMBER] = 0xFF;
#endif
	}
	SYB_TelBookDataEnd = 0;

	/** ワンタッチ・短縮データを電話帳テーブルにセットしていく */
	for (i = 0; i < SYS_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX; i++) {
		if (i < SYS_ONETOUCH_MAX) { /** ワンタッチダイアルの場合 */
			dp = &SYB_OnetouchDial[i];
		}
		else { /** 短縮の場合 */
			dp = &SYB_SpeedDial[i - SYS_ONETOUCH_MAX];
		}

		if (((dp->Dial[0] & 0xF0) != 0xF0) && (dp->Name[0] != NULL)) { /** ダイアル番号、名前ともに登録されている */
			/** 電話帳にセット */
			SetTelephoneBook(i);
		}
	}
}

#if (PRO_NAME_RECALL == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[電話帳検索オペレーションメイン]
	function	:[
		1.電話帳を使って発呼する際の相手先の検索を行う.
		2.スタートキーを押された時の状態で電話を掛けるのか、通信を行うのか、終了するのか決定する
		3.電話帳オペレーションに入ってくるのは、短縮が２回連続で押された時で、状態は以下のものがある。
		, 1.電話オペレーションから、電話帳オペレーションにくる場合。
		, 2.コマンドオペレーションから電話帳オペレーションにくる場合。
		, 3.電話オペレーションからコマンドオペレーションを通って電話帳オペレーションにくる場合.
	]
	return		:[
			TELBOOK_END	(2)
			TELBOOK_FAXCOM(3)
			TELBOOK_TEL(4)
			TELBOOK_TEL_ON_HOOK(5)
			TELBOOK_BROADCAST(6)
			TELBOOK_SPEED_KEY(7)
			TELBOOK_SET(8)
				]
	common		:[]
	condition	:[
				mode:OPR_COM_OPE:コマンドオペレーションからコール
					 OPR_TEL_OPE:電話オペレーションからコール]
	comment		:[スタートキー押下時の条件を詰める必要あり 1995/09/04]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
UBYTE TelephoneBookOperation2(void)
{
	UBYTE	key;
	UBYTE	keytype;

	/* 電話帳テーブルにデータが存在するか調べる */
	if (SYB_TelBookDataEnd == 0) { /* 登録最終位置が電話帳テーブルの先頭にある */
		/* データなし */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		return (TELBOOK_END);
	}


	/**初期設定 */
	TelBookDataPointer = 0; /*電話帳テーブル参照位置 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (電話帳でテンキーの動作はV-650と同じくなります)　Added by SMuratec L.Z.W 2003/10/20 */
	TOP_TelBookMode = TelBook_KANA;		/* 先頭モードの初期化 */
#if defined(JPN)						/* 先頭モード設定 */
	SetTelephoneBook_KanaTop();
#else
	SetTelephoneBook_AlphabetTop();
#endif
	GetTelephoneBookMode();
	TOP_TelBookMode = TelBookMode;		/* 先頭モードの保管 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	while (1) {
		/** 電話帳オペレーション表示 (相手先表示)*/
		DisplayTelBookOperation2();

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key 	= GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) { /** 取り込んだキーに対する処理  */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０仕様と同じです)Modify by SMuratec L.Z.W 2003/09/27 */
		case LEFT_ARROW:
			/* 左方向検索 */
			TelBookLeftSearch();
			break;
		case FUNCTION:
			/* 右方向検索 */
			TelBookRightSearch();
			break;
		case NUMBER:					/* 数字キー */
			if (SYB_TelBookDataEnd  == 1) {	/* データ１件のみ */
				NackBuzzer();
			}
			else {
				switch (TelBookMode) {
				case TelBook_KANA:				/* カナモード */
				case TelBook_ALPHABET:			/* 英字モード */
					Shortcut_NUMBER(TelBookMode, key);
					break;
				default:
					Shortcut_NUMBER(BEF_TelBookMode, key);
					GetTelephoneBookMode();
					break;
				}
			}
			break;
#else
		case NUMBER:	/* 数字キー */
			switch (key) {
			case TEN_2_KEY:
				/* 上方向検索 */
				TelBookUpSearch();
				break;
			case TEN_8_KEY:
				/* 下方向検索 */
				TelBookDownSearch();
				break;
			case TEN_4_KEY:
				/* 左方向検索 */
				TelBookLeftSearch();
				break;
			case TEN_6_KEY:
				/* 右方向検索 */
				TelBookRightSearch();
				break;
			default:
				NackBuzzer();
				break;
			}
			break;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case ENTER:		/* セットキー */
			return (TELBOOK_SET);
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:		/* １分間キー入力なし */
			/** 終了 */
			return (TELBOOK_END);
		case SPEED:
			/** 終了 */
			return (TELBOOK_END);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[電話帳オペレーション表示]
	function	:[
		1.電話帳データ表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void DisplayTelBookOperation2(void)
{
#if (0)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
//	UBYTE	data_number;
#endif
	UWORD	data_number;
	UBYTE	order;
	UWORD	option_number;		/* 任意短縮番号 */

	/* チャイルド表示処理 */
	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');

	/* 上段表示文字列：「ﾃﾞﾝﾜﾁｮｳ         [A]」[]の中は検索ラインの先頭文字 */
	order = (UBYTE)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_SORTPRIORITY];
	FunctionDisplayBufferHigh[11] = ':';
	FunctionDisplayBufferHigh[12] = '[';
	FunctionDisplayBufferHigh[13] = TelBookSearchLineTable[order];
	FunctionDisplayBufferHigh[14] = ']';

	/* 下段表示文字列作成 : 「ABCDEF         :B  ] 相手先名とダイアルデータ */
	data_number = (UWORD)SYB_TelephoneBookData[TelBookDataPointer][OPR_TELBOOK_DATANUMBER];

	if (data_number < SYS_ONETOUCH_MAX) {	/* ワンタッチ */
		/* 相手先名取り出し */
		CharacterInput.Name = SYB_OnetouchDial[data_number].Name;
		CMN_StringCopy(FunctionDisplayBufferLow, SYB_OnetouchDial[data_number].Name);
		FunctionDisplayBufferLow[15] = ':';
		/* ワンタッチ記号を表示 */
		SetOnetouchCode(&FunctionDisplayBufferLow[16],
						CMN_OffsetToOnetouchCode((UBYTE)data_number), OPR_SET_ONETOUCH_CODE);
	}
	else {									/* 短縮 */
		data_number -= SYS_ONETOUCH_MAX;
		/* 相手先名取り出し */
		CharacterInput.Name = SYB_SpeedDial[data_number].Name;
		CMN_StringCopy(FunctionDisplayBufferLow, SYB_SpeedDial[data_number].Name);
		FunctionDisplayBufferLow[15] = ':';
		/* 短縮番号表示 */
		FunctionDisplayBufferLow[16] = OPR_SPEED_MARK;
		if( CHK_UNI_OptionalSpeedDial() == 0 ){	/* 通常の短縮の時 */
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[17],
								 (UWORD)(data_number + OPR_SPEED_DIAL_MIN),
								 (UBYTE)SPEED_FIGURE_MAX,
								 '0');
		}
		else{		/* 任意短縮の時 */
			option_number = GetRecordFromNumber(data_number);
			if( option_number != 0xFFFF ){
				CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[17], option_number, (UBYTE)SPEED_FIGURE_MAX, '0');
			}
			else{
				CMN_MemorySet(&FunctionDisplayBufferLow[17], (UWORD)SPEED_FIGURE_MAX, (UBYTE)0x2A);
			}
		}
	}

	DisplayStringHigh(11, &FunctionDisplayBufferHigh[11]);
	DisplayStringLow(0, FunctionDisplayBufferLow);
}
#endif
