/************************************************************************
*	System		: LONDON/AMSTERDAM
*	File Name	: OPR_CHAR.C
*	Author		: 渡辺一章
*	Date		: 2001/03/27
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 文字入力オペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\font_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
/*************************************************************************
	module		:[文字入力]
	function	:[
		1.
	]
	return		:[
		TRUE	:入力完了
		FALSE	:入力中断
	]
	common		:[]
	condition	:[CharacterInputに必要なデータをセットしてからコールする事]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
UBYTE OPR_InputCharacterOperation(CONST UBYTE is_input_kanji_enable)
{
	UBYTE	key_code;
	UBYTE	key_type;
	UBYTE	is_loop_end;				/* ループ終了判断 */
	UBYTE	is_input_complete;
	UBYTE	before_ten_key_code;
	UBYTE	select_character_count;

	key_code = OPR_NO_KEY;
	before_ten_key_code = OPR_NO_KEY;
	is_input_complete = FALSE;
	select_character_count = 0xFF;

#if 0 /* SetCharacterInputMode()で初期化します。Modified by SMuratec L.Z.W 2003/11/28 */
**	/* 初期文字入力モードの設定 */
**#if defined(JPN)
**	CharacterInput.Mode = OPR_KATAKANA_MODE;	/* カタカナ入力モード	*/
**#else
**	CharacterInput.Mode = OPR_ALPHAMERIC_MODE;	/* 英数字入力モード		*/
**#endif
#endif

	is_loop_end = FALSE;
	while (!is_loop_end) {
		/* ＬＣＤ表示 */
		OPR_DisplayInputCharacterMode();
		OPR_DisplayInputCharacterData();

		/* １つ前に押されたキーを記憶する
		** 注）１キー　→　上矢印キー(無効なキー)　→　１キーと押されても、イが入力出来るようにテンキーだけを記憶します
		*/
		if ((key_type == NUMBER) || (key_type == SHARP) || (key_type == AST)) {
			before_ten_key_code = key_code;
		}

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key_code = GetInputKeyCode();
		key_type = GetInputKeyType();

		/* カーソル移動・文字クリアが行われた時に、文字候補選択中だった時の為に初期化します */
		if ((key_type == LEFT_ARROW) || (key_type == FUNCTION) || (key_type == CLEAR)) {
			select_character_count = 0xFF;
		}

		/* 取り込んだキーに対する処理実行 */
		switch (key_type) {
		case CHARACTER:		/* 文字キー */ /* (DIALMARK -> CHARACTER)Modify by SMuratec L.Z.W 2003/10/10 */
			OPR_ChangeInputCharacterMode(is_input_kanji_enable, &select_character_count);
			break;
		case FUNCTION:	/* 右矢印キー */
			/* カーソル移動 右 */
			if (!OPR_CheckInputCharacterCode()) {	/* コード入力中でない時 */
				OPR_InputCharacterRightKeyOpr(is_input_kanji_enable);
			}
			else {
				NackBuzzer();
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			/* カーソル移動 左 */
			if (!OPR_CheckInputCharacterCode()) {	/* コード入力中でない時 */
				OPR_InputCharacterLeftKeyOpr();
			}
			else {
				NackBuzzer();
			}
			break;
		case SPEED:	/* 電話帳キー */
			if (!OPR_CheckInputCharacterCode()) {	/* コード入力中でない時 */
				if (select_character_count != 0xFF) {	/* 入力文字が確定していない時 */
					if (CharacterInput.CursorPosition == CharacterInput.WritePosition) {	/* カーソル位置が、入力文字の最後の時 */
						/* 選択されていた文字で確定し（書き込み位置を進める）、カーソル位置を進める */
						CharacterInput.WritePosition++;
					}

					/* カーソル位置を進める */
					CharacterInput.CursorPosition++;

					/* 押されたキーの文字群の先頭文字を選択するように初期化 */
					select_character_count = 0xFF;
				}

				/* 電話帳オペレーション実行 */
				switch (TelephoneBookOperation2()) {
				case TELBOOK_SET:	/* 電話帳で相手先名が選択された時 */
					/* 選択された相手先名を文字入力用バッファにコピーする */
					OPR_InputCharacterTelBook(is_input_kanji_enable);
					break;
				case TELBOOK_END:	/* ストップキー押下・１分間キー入力無しの時 */
					/* 文字入力終了 */
					is_loop_end = TRUE;
					break;
				default:
					break;
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER			/* 数字キー */:
		case SHARP:			/* ＃キー */
		case AST:			/* ＊キー */
			/* テンキー入力オペレーション */
			OPR_InputCharacterTenKeyOpr(is_input_kanji_enable, key_code, before_ten_key_code, &select_character_count);
			break;
		case ENTER:			/* セットキー */
			if (!OPR_CheckInputCharacterCode()) {	/* コード入力中でない時 */
				is_input_complete = TRUE;
				is_loop_end = TRUE;
			}
			else {
				if (before_ten_key_code == TEN_2_KEY || before_ten_key_code == TEN_3_KEY) {
					OPR_CharacterSetEnd 	= TRUE;
					if (CharacterInput.InputKeyPosition == OPR_CODE_FIGURE_MAX) {	/* ４桁入力された時 */
						OPR_InputCharacterTenKeyOpr(is_input_kanji_enable, 
													before_ten_key_code, 
													before_ten_key_code, 
													&select_character_count);
					}
					else {
						select_character_count 	= 0xFF;
					}
				}
				else {
					NackBuzzer();
				}
			}
			break;
		case CLEAR:			/* クリアキー */
			OPR_InputCharacterDataClear();
			break;
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			is_loop_end = TRUE;
			break;
		case NO_EFFECT:		/* チャイルド終了等 */
			break;
		default:
			NackBuzzer();
			break;
		}
	}

	CursorOff();
	return (is_input_complete);
}

/*************************************************************************
	module		:[文字入力モード表示]
	function	:[
		1.上段に入力モードを表示します（右端から８文字）
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
void OPR_DisplayInputCharacterMode(void)
{
	switch (CharacterInput.Mode) {
#if defined(JPN)
	case OPR_KATAKANA_MODE:		/* カタカナ入力モード					*/
		DisplayStringHigh(11, D2W_Kana);		/* [;ｶﾀｶﾅ    ] */
		break;
 #if (PRO_JIS_CODE == ENABLE)
	case OPR_2_BYTE_CODE_MODE:	/* 全角文字コード入力モード(区点コード)	*/
		DisplayStringHigh(11, D2W_KanjiCode);	/* [;ｶﾝｼﾞｺｰﾄﾞ] */
		break;
 #endif
#endif
	case OPR_ALPHAMERIC_MODE:	/* 英数字入力モード						*/
		DisplayStringHigh(11, D2W_Alphameric);	/* [;ｴｲｽｳ    ] */
		break;
	case OPR_1_BYTE_CODE_MODE:	/* 半角文字コード入力モード(ASCII･ANK)	*/
		DisplayStringHigh(11, D2W_Code);		/* [;ｺｰﾄﾞ    ] */
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[入力文字データ表示]
	function	:[
		1.下段に入力したデータを表示します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
void OPR_DisplayInputCharacterData(void)
{
	UBYTE	cursor_disp_position;
	UBYTE	diff;
	UBYTE	over_count;
	UBYTE	disp_enable_count;

	cursor_disp_position = 0;
	diff = 0;
	over_count = 0;
	disp_enable_count = 0;

	disp_enable_count = (UBYTE)(OPR_DISPLAY_MAX - CharacterInput.LcdDisplayPosition);

	if (CheckChildErrorDisplayReq() == TRUE) {	/* エラー等でチャイルド表示要求がある場合 */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay()) {	/* チャイルド表示中 */
		return;
	}

	/* 下段表示用バッファをクリア */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	if (OPR_CheckInputCharacterCode()) {	/* コード入力中の時 */
		/* "[B_   ]            " と表示 */
		FunctionDisplayBufferLow[0] = '[';
		CMN_StringCopy(&FunctionDisplayBufferLow[1], CharacterInput.InputKeyBuffer);
		FunctionDisplayBufferLow[5] = ']';
		cursor_disp_position = (UBYTE)(CharacterInput.InputKeyPosition + 1);
	}
	else {											/* 通常入力中 */
		/* 表示開始位置を計算する */
		if (CharacterInput.DisplayStartPosition > CharacterInput.CursorPosition) {			/* 表示開始位置よりカーソルが前にある */
			/* カーソル位置を先頭に２０文字分(表示可能文字数分）表示するので表示位置をカーソル位置に持ってくる  */
			CharacterInput.DisplayStartPosition = CharacterInput.CursorPosition;
		}
		else if (CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition) {	/* 表示位置とカーソル位置が同じ */
			/* カーソル位置を先頭に２０文字分表示する */
			;
		}
		else {																				/* 表示開始位置よりカーソルが後ろにある */
			/* 表示開始位置とｶｰｿﾙ位置までの差が２０文字(表示可能文字数分）以内であれば表示位置から２０文字分表示する
			** 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）を越える場合は
			** カーソル位置がＬＣＤの右端にくるように表示位置を調整する
			*/
			diff = (CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition) + 1;
			if (diff > disp_enable_count) {	/* 表示可能文字数を越える */
				over_count = diff - disp_enable_count;	/* オーバーする文字数を求める */
				CharacterInput.DisplayStartPosition += over_count;	/* オーバーする文字数分表示位置をカーソル側へ移動 */
			}
		}
		/* カーソル位置と表示開始位置が同じでかつ先頭でない場合 */
		/* カーソル位置の一つ前から表示を開始する */
		if ((CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition)
		 && (CharacterInput.CursorPosition != 0)) {
			CharacterInput.DisplayStartPosition--;
		}
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition],
								 &CharacterInput.Buffer[CharacterInput.DisplayStartPosition],
								 disp_enable_count);
		/* カーソル位置を計算 */
		cursor_disp_position = CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition;
	}

	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor_disp_position + CharacterInput.LcdDisplayPosition));
}

/*************************************************************************
	module		:[文字入力モードの変更]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
void OPR_ChangeInputCharacterMode(CONST UBYTE is_input_kanji_enable, UBYTE *select_character_count)
{
	/* コード入力中は文字入力モードの変更は出来ません */
	if (OPR_CheckInputCharacterCode()) {	/* コード入力中の時 */
		NackBuzzer();
		return;
	}

	/* 文字候補選択中に入力モードが変えられた時は、その時点で表示している文字を確定し、カーソルを進めます */
	if (((CharacterInput.Mode == OPR_KATAKANA_MODE) || (CharacterInput.Mode == OPR_ALPHAMERIC_MODE))
	 && (*select_character_count != 0xFF)) {
		OPR_InputCharacterRightKeyOpr(is_input_kanji_enable);
		/* 次のモードで、押されたキーの文字群の先頭文字を選択するように初期化 */
		*select_character_count = 0xFF;
	}

	switch (CharacterInput.Mode) {
#if defined(JPN)
	case OPR_KATAKANA_MODE:		/* カタカナ入力モード					*/
		CharacterInput.Mode = OPR_ALPHAMERIC_MODE;	/* 英数字入力モードに変更 */
		break;
#endif
	case OPR_ALPHAMERIC_MODE:	/* 英数字入力モード						*/
		CharacterInput.Mode = OPR_1_BYTE_CODE_MODE;	/* 半角文字コード入力モードに変更 */
		break;
	case OPR_1_BYTE_CODE_MODE:	/* 半角文字コード入力モード(ASCII･ANK)	*/
#if (PRO_JIS_CODE == ENABLE)
		if (is_input_kanji_enable) {
			CharacterInput.Mode = OPR_2_BYTE_CODE_MODE;	/* 全角文字コード入力モードに変更 */
		}
		else {
			CharacterInput.Mode = OPR_KATAKANA_MODE;	/* カタカナ入力モードに変更 */
		}
#else
 #if defined(JPN)
		CharacterInput.Mode = OPR_KATAKANA_MODE;	/* カタカナ入力モードに変更 */
 #else
		CharacterInput.Mode = OPR_ALPHAMERIC_MODE;	/* 英数字入力モードに変更 */
 #endif
#endif
		break;
#if (PRO_JIS_CODE == ENABLE)
	case OPR_2_BYTE_CODE_MODE:	/* 全角文字コード入力モード(区点コード)	*/
		CharacterInput.Mode = OPR_KATAKANA_MODE;	/* カタカナ入力モードに変更 */
		break;
#endif
	default:
		break;
	}
}

/*************************************************************************
	module		:[文字入力中の右矢印キーの処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/29]
	author		:[渡辺一章]
*************************************************************************/
void OPR_InputCharacterRightKeyOpr(CONST UBYTE is_input_kanji_enable)
{
	if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* カーソルが入力文字の最後の位置にある時 */
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] != NULL) {	/* 文字候補選択中の時 */
			/* 選択中の文字で確定し、カーソルを右に移動させます */
			CharacterInput.WritePosition++;
			CharacterInput.CursorPosition++;
		}
		else {																/* 文字候補選択中でない時 */
			/* スペース追加可能チェック */
			if (!OPR_CheckSetNextDataEnable(is_input_kanji_enable, 1)) {	/* 入力可能最大桁数入力されている時 */
				NackBuzzer();
			}
			else {
				CharacterInput.Buffer[CharacterInput.CursorPosition] = ' ';	/* カーソル位置にスペースをセット */
				CharacterInput.WritePosition++;
				CharacterInput.CursorPosition++;
			}
		}
	}
#if (PRO_JIS_CODE == ENABLE)
	else if (CharacterInput.Buffer[CharacterInput.CursorPosition] == OPR_KANJI_CODE_MARK_LEFT) {	/* カーソル位置が漢字コードの時 */
		/* "(1234) "のような時、カーソルを右移動させると"(1234) "となる */
		/*  ~                                                  ~        */
		CharacterInput.CursorPosition += OPR_KANJI_CODE_LEN;
	}
#endif
	else {																	/* カーソルが入力文字の途中の位置にある時 */
		/* カーソルを右に移動させます */
		CharacterInput.CursorPosition++;
	}
}

/*************************************************************************
	module		:[文字入力中の左矢印キーの処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/29]
	author		:[渡辺一章]
*************************************************************************/
void OPR_InputCharacterLeftKeyOpr(void)
{
	if (CharacterInput.CursorPosition == 0) {	/* カーソルが一番先頭にある時 */
		NackBuzzer();
	}
	else {
		if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* カーソルが入力文字の最後の位置にある時 */
			if (CharacterInput.Buffer[CharacterInput.CursorPosition] != NULL) {	/* 文字候補選択中の時 */
				/* カーソルが入力文字の最後の位置で文字候補選択中だった時は、選択中だった文字で確定させます */
				CharacterInput.WritePosition++;
				CharacterInput.CursorPosition--;
			}
			else {
				/* カーソルを左に移動させます */
				CharacterInput.CursorPosition--;

				/* 最後のデータがスペースだった時は、そのスペースも削除します */
				if (CharacterInput.Buffer[CharacterInput.CursorPosition] == ' ') {
					CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
					CharacterInput.WritePosition--;
				}
			}
		}
		else {
			/* カーソルだけ左に移動させます */
			CharacterInput.CursorPosition--;
		}

#if (PRO_JIS_CODE == ENABLE)
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] == OPR_KANJI_CODE_MARK_RIGHT) {
			/* "(1234) "のような時、カーソルを左移動させると"(1234) "となる */
			/*        ~                                      ~              */
			CharacterInput.CursorPosition -= (OPR_KANJI_CODE_LEN - 1);
		}
#endif
	}
}

/*************************************************************************
	module		:[文字入力テンキーオペレーション]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
void OPR_InputCharacterTenKeyOpr(CONST UBYTE is_input_kanji_enable,
								 CONST UBYTE key_code,
								 CONST UBYTE before_ten_key_code,
								 UBYTE *select_character_count)
{
	UBYTE	add_data_count;			/* 入力文字桁数 */
	UBYTE	*character_table_ptr;	/* 文字テーブルのポインター */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/08/14 */
	UBYTE	select_char_count = *select_character_count;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/* 同じキーでの文字候補選択中は、桁数チェックを行いません */
	if (!((select_char_count != 0xFF) && (key_code == before_ten_key_code))) {
		/* 入力する文字の桁数の取得 */
		add_data_count = 1;		/* 半角文字は１バイト使用します */
#if (PRO_JIS_CODE == ENABLE)
		if (CharacterInput.Mode == OPR_2_BYTE_CODE_MODE) {	/* 全角文字コード入力モードの時 */
			add_data_count = 2;	/* 全角文字は２バイト使用します */
		}
#endif
		/* 入力文字桁数チェック */
		if (!OPR_CheckSetNextDataEnable(is_input_kanji_enable, add_data_count)) {	/* 次の文字を入力すると、入力可能桁数をオーバーする時 */
			/* 桁数オーバーした時はカーソルを進めてないので、最大入力文字位置の文字がキーが押されると
			** いつでも違う文字に変わってしまうので、初期化処理を追加します by K.Watanabe 2001/09/21
			*/
			select_char_count = 0xFF;

			NackBuzzer();
			ChildDisplayStringLow(D2W_TooManyDigitsin);	/* 入力バッファ桁数オーバー */
			return;
		}
	}

	switch (CharacterInput.Mode) {
	case OPR_KATAKANA_MODE:		/* カタカナ入力モード					*/
	case OPR_ALPHAMERIC_MODE:	/* 英数字入力モード						*/
		if (select_char_count == 0xFF) {	/* 文字入力開始直後のキー入力か、カーソル移動後のキー入力の時 */
			if (CharacterInput.CursorPosition != CharacterInput.WritePosition) {	/* カーソル位置が、入力文字の途中の時 */
				/* カーソル位置以降のデータを１つずらす */
				DataShiftOneStep();
			}
			else {																	/* カーソル位置が、入力文字の最後の時 */
				if (CharacterInput.Buffer[CharacterInput.CursorPosition] != NULL) {
					/* カーソル位置以降のデータを１つずらす */
					DataShiftOneStep();
				}
			}
		}
		else {									/* 文字入力が連続して行われている時 */
			if (key_code != before_ten_key_code) {	/* 違うキーの文字を入力する時 */
				if (CharacterInput.CursorPosition != CharacterInput.WritePosition) {	/* カーソル位置が、入力文字の途中の時 */
					/* カーソル位置以降のデータを１つずらす */
					DataShiftOneStep();
					/* カーソル位置を進める */
					CharacterInput.CursorPosition++;
				}
				else {																	/* カーソル位置が、入力文字の最後の時 */
					/* 選択されていた文字で確定し（書き込み位置を進める）、カーソル位置を進める */
					CharacterInput.WritePosition++;
					CharacterInput.CursorPosition++;
				}

				/* 押されたキーの文字群の先頭文字を選択するように初期化 */
				select_char_count = 0xFF;
			}
		}

		/* 押されたキーの押された回数に該当する文字をセットします */
		if (CharacterInput.Mode == OPR_KATAKANA_MODE) {	/* カタカナ入力モード	*/
			character_table_ptr = &KATAKANA_CharacterTable[OPR_GetCharacterTable1stArrange(key_code)][0];
		}
		else {											/* 英数字入力モード		*/
			character_table_ptr = &AlphamericCharacterTable[OPR_GetCharacterTable1stArrange(key_code)][0];
		}
		OPR_SetCharacterTableData(character_table_ptr, &select_char_count);
		break;
	case OPR_1_BYTE_CODE_MODE:	/* 半角文字コード入力モード(ASCII･ANK)	*/
#if (PRO_JIS_CODE == ENABLE)
	case OPR_2_BYTE_CODE_MODE:	/* 全角文字コード入力モード(区点コード)	*/
#endif
		if ((key_code >= TEN_0_KEY) && (key_code <= TEN_9_KEY)) {	/* ０～９の時 */
			OPR_InputCharacterCode(key_code);
		}
		else {														/* ＊，＃の時 */
			NackBuzzer();
		}
		break;
	default:
		break;
	}
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/08/14 */
	*select_character_count = select_char_count;	/* 文字テーブルのポインター */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[文字入力クリアーオペレーション]
	function	:[
		1.カーソル位置が入力最後尾の場合、カーソル前を１文字クリア
		2.カーソル位置が入力バッファの途中の場合、カーソル上の文字を１文字クリア
		3.クリアはＮＵＬＬをセットすることで実現する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/03]
	author		:[渡辺一章]
*************************************************************************/
void OPR_InputCharacterDataClear(void)
{
	if (OPR_CheckInputCharacterCode()) {	/* 文字コード入力中の時 */
		OPR_ClearCodeBuffer1Character();	/* コード入力中の文字をクリア */
		return;
	}

	if (CheckCharacterInputEmpty()) {	/* データ未入力の時 */
		NackBuzzer();
		return;
	}

	if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* カーソル位置が、入力文字の最後の時 */
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] != NULL) {	/* カーソル位置が、文字候補選択中の時 */
			CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;	/* 選択中の文字を消去 */
		}
#if (PRO_JIS_CODE == ENABLE)
		else if (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == OPR_KANJI_CODE_MARK_RIGHT) {	/* 最後の文字が漢字コードの時 */
			/* 括弧を含めた漢字コードを消去 */
			CharacterInput.WritePosition -= OPR_KANJI_CODE_LEN;
			CharacterInput.CursorPosition -= OPR_KANJI_CODE_LEN;
			CMN_MemorySet(&CharacterInput.Buffer[CharacterInput.WritePosition], OPR_KANJI_CODE_LEN, NULL);
		}
#endif
		else {
			/* カーソル位置を１つ戻します */
			CharacterInput.WritePosition--;
			CharacterInput.CursorPosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
		}
	}
	else {																	/* カーソル位置が、入力文字の途中の時 */
#if (PRO_JIS_CODE == ENABLE)
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] == OPR_KANJI_CODE_MARK_LEFT) {	/* カーソル位置が、漢字コードの時 */
			/* "(1234) "のような時、クリアキーを押すと" "となる */
			/*  ~                                      ~        */
			CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
							  &CharacterInput.Buffer[CharacterInput.CursorPosition + OPR_KANJI_CODE_LEN],
							  OPR_CHARACTER_INPUT_MAX - OPR_KANJI_CODE_LEN - CharacterInput.CursorPosition);
			CharacterInput.WritePosition -= OPR_KANJI_CODE_LEN;
			CMN_MemorySet(&CharacterInput.Buffer[CharacterInput.WritePosition], OPR_KANJI_CODE_LEN, NULL);
		}
		else {																					/* カーソル位置が、カタカナ・英数字・記号の時 */
			/* カーソル位置の文字を消します */
			CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
							  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
							  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
			CharacterInput.WritePosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
		}
#else
		/* カーソル位置の文字を消します */
		CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
						  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
						  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
		CharacterInput.WritePosition--;
		CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
#endif
	}
}

/*************************************************************************
	module		:[文字テーブル第一配列番号取得]
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
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
UBYTE OPR_GetCharacterTable1stArrange(CONST UBYTE key_code)
{
	UBYTE	first_arrange_number;	/* 文字テーブルの第一配列番号 */

	/* 押されたキーを配列番号に変換します */
	switch (key_code) {
	case TEN_1_KEY:		/* テンキー１キー */
	case TEN_2_KEY:		/* テンキー２キー */
	case TEN_3_KEY:		/* テンキー３キー */
	case TEN_4_KEY:		/* テンキー４キー */
	case TEN_5_KEY:		/* テンキー５キー */
	case TEN_6_KEY:		/* テンキー６キー */
	case TEN_7_KEY:		/* テンキー７キー */
	case TEN_8_KEY:		/* テンキー８キー */
	case TEN_9_KEY:		/* テンキー９キー */
		first_arrange_number = key_code - TEN_1_KEY;	/* 0～8 */
		break;
	case TEN_0_KEY:		/* テンキー０キー */
		first_arrange_number = 9;
		break;
	case TEN_AST_KEY:	/* テンキー＊キー */
		first_arrange_number = 10;
		break;
	case TEN_SHARP_KEY:	/* テンキー＃キー */
		first_arrange_number = 11;
		break;
	default:
		/* テンキーは１２３４５６７８９＊０＃固定なのでありえません */
		break;
	}

	return (first_arrange_number);
}

/*************************************************************************
	module		:[指定文字セット]
	function	:[
		1.押されたキーの押された回数に該当する文字をセットします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/28]
	author		:[渡辺一章]
*************************************************************************/
void OPR_SetCharacterTableData(CONST UBYTE *character_table_ptr, UBYTE *select_character_count)
{
	if (*select_character_count != 0xFF) {	/* 同じキーを２回以上押した時 */
		if (*(character_table_ptr + *select_character_count + 1) == '\0') {	/* そのキーで入力出来る文字が一周した時 */
			*select_character_count = 0;	/* そのキーに割り当てられた先頭の文字を指定します */
		}
		else {
			(*select_character_count)++;	/* そのキーに割り当てられた、次の文字を指定します */
		}
	}
	else {									/* 初めてそのキーが押された時 */
		*select_character_count = 0;	/* そのキーに割り当てられた先頭の文字を指定します */
	}

	/* 現在の文字入力モードの、押されたキーの押された回数に該当する文字をセットします */
	CharacterInput.Buffer[CharacterInput.CursorPosition] = *(character_table_ptr + *select_character_count);
}

/*************************************************************************
	module		:[文字コード入力]
	function	:[
		1.入力された数字を区点コード用バッファにセット
		2.区点コードが４桁入力されたら、JISコードに変換し該当する文字が
		　あるかをチェックする
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/30]
	author		:[渡辺一章]
*************************************************************************/
void OPR_InputCharacterCode(CONST UBYTE key_code)
{
	UWORD	input_code;				/* 入力されたコード */
	UBYTE	character_table_number;	/* 半角テーブル配列番号 */
	UBYTE	loop_i;					/* ループ変数 */
	UBYTE	is_loop_end;			/* ループ終了判断用 */
	UBYTE	is_valid_code;			/* 入力コードの正誤判断用 */

	/* 入力された数字を区点コード用バッファにセット */
	CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = key_code;
	CharacterInput.InputKeyPosition++;

	if (CharacterInput.InputKeyPosition == OPR_CODE_FIGURE_MAX) {	/* ４桁入力された時 */
		/* 入力コードの正誤判断用変数の初期化 */
		is_valid_code = FALSE;

		if (CharacterInput.Mode == OPR_1_BYTE_CODE_MODE) {	/* 半角文字コード入力モード(ASCII･ANK) */
			input_code = CMN_ASC_ToUnsignedInt(&CharacterInput.InputKeyBuffer[0], 4);
			character_table_number = 0;
			is_loop_end = FALSE;
			while (!is_loop_end) {
				if (ANK_CharacterTable[character_table_number].KUTEN_Code == 0) {	/* 入力コードに該当する文字がなかった時 */
					NackBuzzer();
					is_loop_end = TRUE;
				}
				else {
					if (ANK_CharacterTable[character_table_number].KUTEN_Code == input_code) {	/* 入力コードに該当する文字があった時 */
						CharacterInputDataSet(ANK_CharacterTable[character_table_number].Character);
						is_valid_code = TRUE;	/* 入力されたコードに該当する文字があった */
						is_loop_end = TRUE;
					}
					else {
						character_table_number++;
					}
				}
			}
		}
#if (PRO_JIS_CODE == ENABLE)
		else {												/* 全角文字コード入力モード(区点コード) */
			/* 入力された区点コードをJISコードに変換 */
			input_code = CMN_ASC_KUTEN_CodeToJIS(&CharacterInput.InputKeyBuffer[0]);

			/* 変換したJISコード(第１水準・定義されている第２水準)に該当する文字があるかを調べます */
			if (CMN_CheckJIS1Code(input_code) || (CMN_CheckFontJIS2Code(input_code) != KANJI2_NONE)) {	/* 入力コードに該当する文字があった時 */

				/* 入力文字用バッファに、漢字コードを表すかっこと共に入力された区点コードをセットする */
				CharacterInputDataSet(OPR_KANJI_CODE_MARK_LEFT);	/* 漢字コードを表す左かっこ */
				for (loop_i = 0; loop_i < OPR_CODE_FIGURE_MAX; loop_i++) {	/* 入力文字用バッファに、入力された区点コードをセット */
					CharacterInputDataSet(CharacterInput.InputKeyBuffer[loop_i]);
				}
				CharacterInputDataSet(OPR_KANJI_CODE_MARK_RIGHT);	/* 漢字コードを表す右かっこ */
				is_valid_code = TRUE;	/* 入力されたコードに該当する文字があった */
			}
			else {																						/* 入力コードに該当する文字が無かった時 */
				NackBuzzer();
			}
		}
#endif

		if (is_valid_code) {	/* 入力されたコードに該当する文字があった時 */
			/* 文字が確定したので、コード入力用バッファを初期化します */
			OPR_AllClearInputKeyBuffer();
		}
		else {					/* 入力されたコードが間違いの時 */
			/* 最後に入力された数字はキャンセルします */
			CharacterInput.InputKeyPosition--;
			CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = NULL;
			OPR_CharacterSetEnd = TRUE;
		}
	}
}

/*************************************************************************
	module		:[文字コード入力用バッファ１文字クリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/29]
	author		:[渡辺一章]
*************************************************************************/
void OPR_ClearCodeBuffer1Character(void)
{
	CharacterInput.InputKeyPosition--;
	CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = NULL;
}

/*************************************************************************
	module		:[文字コード入力用バッファ　オールクリア]
	function	:[]
	return		:[]
	common		:[CharacterInput]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/11]
	author		:[江口]
*************************************************************************/
void OPR_AllClearInputKeyBuffer(void)
{
	CMN_MemorySetNULL(CharacterInput.InputKeyBuffer, OPR_CODE_FIGURE_MAX, NULL);
	CharacterInput.InputKeyPosition = 0;
}

/*************************************************************************
	module		:[文字コード入力中チェック]
	function	:[
		1.コード（半角・全角文字）入力中かを、調べます
	]
	return		:[
		TRUE	:コード入力中
		FALSE	:コード未入力状態
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/03/29]
	author		:[渡辺一章]
*************************************************************************/
UBYTE OPR_CheckInputCharacterCode(void)
{
	if (CharacterInput.InputKeyPosition > 0) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[次入力可能検査]
	function	:[
		1.入力モード毎の最低入力文字数から、次入力が可能かどうかを調べます
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/05]
	author		:[渡辺一章]
*************************************************************************/
UBYTE OPR_CheckSetNextDataEnable(CONST UBYTE is_input_kanji_enable, CONST UBYTE add_data_count)
{
	UWORD	write_data_count;	/* 入力データ桁数	*/
	UBYTE	ret;				/* リターン値 */

	ret = TRUE;

	/* 入力されているデータの桁数を調べます */
#if (PRO_JIS_CODE == ENABLE)
	if (is_input_kanji_enable) {	/* 漢字入力が可能な時 */
		/* 漢字コードは、表示上の文字数と実際にセットする時の文字数が違うために
		** CharacterInput.WritePositionを使っての最大入力桁数の検査は行えません
		*/
		write_data_count = OPR_GetWriteDataCount();
	}
	else {							/* 漢字入力が不可能な時 */
		write_data_count = CharacterInput.WritePosition;

		if (CharacterInput.Buffer[CharacterInput.WritePosition] != NULL) {	/* 文字候補選択中の時 */
			write_data_count++;
		}
	}
#else
	write_data_count = CharacterInput.WritePosition;

	if (CharacterInput.Buffer[CharacterInput.WritePosition] != NULL) {	/* 文字候補選択中の時 */
		write_data_count++;
	}
#endif

	/* 次の入力が可能かを調べます */
	if ((write_data_count + add_data_count) > CharacterInput.MaxFigure) {
		ret = FALSE;
	}

	return (ret);
}

/*************************************************************************
	module		:[登録文字数検査]
	function	:[
		1.
	]
	return		:[登録文字数（漢字コードは２文字です）]
	common		:[]
	condition	:[]
	comment		:[
		漢字コードが入力されていると入力文字数が、CharacterInput.WritePosition
		ではわからないので、カバーするために、この関数を作成しました

		漢字コードは、表示上は６文字"（１２３４）"使用していますが、
		実際は全角文字なので２文字しか使用しません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/18]
	author		:[渡辺一章]
*************************************************************************/
UWORD OPR_GetWriteDataCount(void)
{
	UWORD	count;	/* バッファ位置 */
	UWORD	ret;	/* リターン値 */

	count = 0;
	ret = 0;

	while (CharacterInput.Buffer[count] != NULL) {	/* 登録文字を全てカウントするまで */
		if (CharacterInput.Buffer[count] == OPR_KANJI_CODE_MARK_LEFT) {	/* 漢字コードの時 */
			count += OPR_KANJI_CODE_LEN;	/* バッファの位置を漢字コードの次にセットします */
			ret += 2;						/* 漢字コードは２文字として扱います */
		}
		else {
			count++;						/* バッファの位置を次の文字にセットします */
			ret++;							/* 登録文字数を加算します */
		}
	}

	return (ret);
}

/*************************************************************************
	module		:[登録済みデータ　バッファセット]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		引数の説明
			*set_buf_ptr	:コピー先バッファの先頭アドレス
			*set_data_ptr	:コピー元データ（登録済みデータ）の先頭アドレス
			set_cnt			:コピー長（バイト数）
							 注）長さ不定でNULLまでコピーする時は、0を指定します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/16]
	author		:[渡辺一章]
*************************************************************************/
void OPR_SetRegisteredDataToBuf(UBYTE *set_buf_ptr, UBYTE *set_data_ptr, UBYTE set_cnt)
{
#if (PRO_JIS_CODE == ENABLE)
	UWORD	data_cnt;	/* コピー元データの先頭アドレスからのバイト位置		*/
	UWORD	buf_cnt;	/* コピー先バッファの先頭アドレスからのバイト位置	*/
	UBYTE	copy_cnt;	/* コピーするバイト数								*/
	UBYTE	wrk_buf[7];	/* コピー先バッファのワーク用						*/
	UWORD	jis_code;	/* コピーデータJISコード変換用ワーク変数			*/
	UWORD	code1;		/* コピーデータの偶数バイトのデータ					*/
	UWORD	code2;		/* コピーデータの奇数バイトのデータ					*/

	data_cnt = 0;
	buf_cnt = 0;
	CMN_MemorySet(wrk_buf, 7, NULL);

	/* 前回入力値を名前入力用バッファに展開する */
	while (*(set_data_ptr + data_cnt) != NULL) {	/* NULLで終了します */
		code1 = (UWORD)(*(set_data_ptr + data_cnt));
		code2 = (UWORD)(*(set_data_ptr + data_cnt + 1));
		if (CMN_CheckShiftJISCode((UBYTE)code1, (UBYTE)code2)) {	/* 漢字（シフトJISコード）の時 */
			/* 漢字コードは、格納値はシフトJISコードですが、入力値は区点コードなので変換して格納します
			** 注）格納先のバッファがバイトデータのため、シフトJISコードで格納してしまうと漢字コードと
			** 　　それ以外の文字との区別がつかないので、入力値と格納値でコードの種類が違います
			*/
			wrk_buf[0] = OPR_KANJI_CODE_MARK_LEFT;	/* 漢字コードを表す左かっこ */
			/* シフトJISコードをアスキーの区点コードに変換し、表示用バッファにセットします */
			CMN_ShiftJIS_ToASC_KUTEN_Code(&code1, &code2, &wrk_buf[1]);
			wrk_buf[5] = OPR_KANJI_CODE_MARK_RIGHT;	/* 漢字コードを表す右かっこ */

			copy_cnt = 6;
			if (set_cnt == 0) {	/* NULLまでコピーする時 */
				CMN_StringCopy(set_buf_ptr + buf_cnt, wrk_buf);
			}
			else {				/* コピーするデータ数に制限がある時 */
				if (set_cnt - (buf_cnt + copy_cnt) < 0) {	/* 漢字コードが全部コピー出来ない時 */
					copy_cnt = set_cnt - buf_cnt;	/* コピーできるバイト数を計算します */
				}
				CMN_StringCopyNumUntilNull(set_buf_ptr + buf_cnt, wrk_buf, copy_cnt);
			}
			buf_cnt += copy_cnt;
			data_cnt += 2;
		}
		else {														/* カタカナ・英数字・記号の時 */
			*(set_buf_ptr + buf_cnt) = *(set_data_ptr + data_cnt);
			buf_cnt++;
			data_cnt++;
		}

		if ((set_cnt != 0) && (set_cnt - buf_cnt <= 0)) {	/* コピーできるデータが一杯になった時 */
			break;
		}
	}
#else
	/* 前回入力値を名前入力用バッファにコピーする */
	if (set_cnt == 0) {
		CMN_StringCopy(set_buf_ptr, set_data_ptr);
	}
	else {
		CMN_StringCopyNumUntilNull(set_buf_ptr, set_data_ptr, set_cnt);
	}
#endif
}

/*************************************************************************
	module		:[文字入力で短縮/電話帳キーが押されたときの処理]
	function	:[
		1.
	]
	return		:[]
	common		:[CharacterInput:登録オペレーション用入力バッファ]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村]
*************************************************************************/
void OPR_InputCharacterTelBook(UBYTE is_kanji_enable)
{
	UWORD	add_data_count;		/* 入力最小文字数 */
	UWORD	write_data_count;	/* 入力データ桁数 */
	UWORD	i;					/* ループ変数 */

	/*--------------------------------------------*/
	/* すでに入力されているデータの桁数を調べます */
	/*--------------------------------------------*/
	add_data_count = CMN_StringLength(CharacterInput.Name);
#if (PRO_JIS_CODE == ENABLE)
	if (is_kanji_enable) {	/* 漢字入力が可能な時 */
		/* 漢字コードは、表示上の文字数と実際にセットする時の文字数が違うために
		** CharacterInput.WritePositionを使っての最大入力桁数の検査は行えないため、
		** OPR_GetWriteDataCount()を追加しました
		*/
		write_data_count = OPR_GetWriteDataCount();
	}
	else {					/* 漢字入力が不可能な時 */
		write_data_count = CharacterInput.WritePosition;
	}
#else
	write_data_count = CharacterInput.WritePosition;
#endif

	/*----------------------------*/
	/* 次の入力が可能かを調べます */
	/*----------------------------*/
	if ((write_data_count + add_data_count) > CharacterInput.MaxFigure) {
		NackBuzzer();
		ChildDisplayStringLow(D2W_TooManyDigitsin);	/* 入力バッファ桁数オーバー */
		return;
	}

	/*--------------------------*/
	/* 入力バッファにセットする */
	/*--------------------------*/
	for (i = 0; i < add_data_count; i++) {
		CharacterInputDataSet(CharacterInput.Name[i]);
	}
}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
