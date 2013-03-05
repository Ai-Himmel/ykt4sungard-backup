/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_NAME.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 名前入力
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

/* Prototype
UBYTE	NameInput(UBYTE);
void	NameInputTenKeyOperation(UBYTE, UBYTE);
void	AlphabetInputOperation(UBYTE, UBYTE);
void	ChangeUpperLowerSignal(UBYTE);
void	ChangeNameInputMode(UBYTE, UBYTE);
void	AllClearInputKeyBuffer(void);
void	NameInputHexCodeSet(UBYTE);
UBYTE	ChangeHexCodeToChar(void);
void	DisplayNameInputMode(void);
void	DisplayNameInputValue(void);
void	ChangeRomaToKana(UBYTE, UBYTE);
void	KANA_Data_Set(UBYTE *);
UBYTE	CheckInputCodeOrChangingKana(void);
void	ClearInputKeyBuffer(void);
void	SetCharacterInputMode(void);
#if (PRO_JIS_CODE == ENABLE)
void	NameInputKanjiCodeSet(UBYTE);
#endif
UBYTE	CheckNextDataWrite(UBYTE, UBYTE *);
UBYTE	GetWriteDataCount(void);
void	SetCharacterInputBuf(UBYTE *);
*/

/*************************************************************************
	module		:[文字入力]
	function	:[
		1.ローマ字入力等もあり(ただし日本のみ)
	]
	return		:[
		OK	:セット完了
		NG	:登録中断
	]
	common		:[CharacterInputに必要なデータをセットしてからコールする]
	condition	:[]
	comment		:[
		ポプラＢでＴＴＩ登録時、漢字コード入力か可能になったので、
		引数に漢字入力可能／不可能を追加
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE NameInput(UBYTE is_kanji_enable)
{
	UBYTE	key;
	UBYTE	keytype;

	/* ここで初期化してしまうと、エラー等で再入力時にモードが初期化されてしまうので、
	** この関数を呼ぶ前に初期化を行うように戻します
	*/
#if (0)	/* by K.Watanabe 1998/01/14 */
//	/* 文字入力モード初期化 */
//	SetCharacterInputMode();
#endif

	/*------------------------------*/
	/* 入力処理						*/
	/*------------------------------*/
	while (1) {
		/*------------------------*/
		/** 入力状態表示		  */
		/*------------------------*/
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/17 Y.Matsukuma */
		DisplaySetPrograming();
#else
		DisplayNameInputMode();		/* 上段の右から８文字分に入力モードを表示 [********* ;Upper    ]*/
#endif
		DisplayNameInputValue();	/* 下段に入力データを表示				  [ABCDEF_			   ]*/

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理実行 */
		switch (keytype) {
		case KEY_TIME_UP:	/** １分間キー入力なし */
		case STOP:			/** ストップキー */
			/* 終わり */
			CursorOff();
			return (NG);
		case FUNCTION:		/** 機能　ー＞キー */
			/** カーソル移動、右*/
			if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中・ローマ字カナ変換中でない時 */
				CharacterInputCursorRightMove();
			}
			else {
				NackBuzzer();
			}
			break;
		case LEFT_ARROW:	/** ＜ー キー	  */
			/** カーソル移動,左*/
			if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中・ローマ字カナ変換中でない時 */
				CharacterInputCursorLeftMove();
			}
			else {
				NackBuzzer();
			}
			break;
		case CLEAR:			/** クリアキー 	  */
			/** 入力中のデータを１文字クリア */
			if (CheckInputCodeOrChangingKana() == TRUE) {	/* コード入力中・ローマ字カナ変換中の時 */
				ClearInputKeyBuffer();		/* ローマ字カナ変換入力バッファ内の文字をクリア */
			}
			else {
				CharacterInputDataClear();	/* データ入力バッファをクリア　*/
			}
			break;
		case ENTER:			/** セットキー	   */
			if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中・ローマ字カナ変換中でない時 */
				CursorOff();
				return(OK);
			}
			NackBuzzer();
			break;
		case NUMBER:
		case SHARP:
		case AST:
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/26 by K.Okada */
			/****************************************************
			** メールで使用される記号（. , @ , _ , - ）の入力後の
			** 文字入力は自動でカーソル移動します
			****************************************************/
			if (CharacterInput.AddressMarkInputMode) {
				if (CheckAddressMark(&CharacterInput.Buffer[CharacterInput.CursorPosition],
									 (UWORD)CharacterInput.CursorPosition,
									 (UWORD)CharacterInput.WritePosition) == TRUE) {
					CharacterInput.CursorPosition++;
				}
			}
#endif
			/* テンキー入力オペレーション*/
			NameInputTenKeyOperation(is_kanji_enable, key);
			break;
		case ONETOUCH:
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/26 by K.Okada */
			/****************************************************
			** メールで使用される記号（. , @ , _ , - ）の入力後の
			** 文字入力は自動でカーソル移動します
			****************************************************/
			if (CharacterInput.AddressMarkInputMode) {
				if (CheckAddressMark(&CharacterInput.Buffer[CharacterInput.CursorPosition],
									 (UWORD)CharacterInput.CursorPosition,
									 (UWORD)CharacterInput.WritePosition) == TRUE) {
					CharacterInput.CursorPosition++;
				}
			}
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/23 Y.Matsukuma */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1998/10/06 Y.Matsukuma */
			if ((key >= ONETOUCH_A_KEY) && (key <= ONETOUCH_G_KEY)) {
			}
 #else
			if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_07_KEY)) {
			}
 #endif
			else {
				NackBuzzer();
				break;
			}
#endif
			AlphabetInputOperation(is_kanji_enable, key);
			break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		case PROGRAM:
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/26 by K.Okada */
			/****************************************************
			** メールで使用される記号（. , @ , _ , - ）の入力後の
			** 文字入力は自動でカーソル移動します
			****************************************************/
			if (CharacterInput.AddressMarkInputMode) {
				if (CheckAddressMark(&CharacterInput.Buffer[CharacterInput.CursorPosition],
									 (UWORD)CharacterInput.CursorPosition,
									 (UWORD)CharacterInput.WritePosition) == TRUE) {
					CharacterInput.CursorPosition++;
				}
			}
#endif
			if (key == ONETOUCH_80_KEY) {
				/* 入力モード変換 */
				ChangeNameInputMode(is_kanji_enable, key);
			}
			else {
				NackBuzzer();
			}
			break;
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
		case PROGRAM:
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/26 by K.Okada */
			/****************************************************
			** メールで使用される記号（. , @ , _ , - ）の入力後の
			** 文字入力は自動でカーソル移動します
			****************************************************/
			if (CharacterInput.AddressMarkInputMode) {
				if (CheckAddressMark(&CharacterInput.Buffer[CharacterInput.CursorPosition],
									 (UWORD)CharacterInput.CursorPosition,
									 (UWORD)CharacterInput.WritePosition) == TRUE) {
					CharacterInput.CursorPosition++;
				}
			}
#endif
			AlphabetInputOperation(is_kanji_enable, key);
			break;
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			if (key == OPR_SHEET_CHANGE) {	/* シート切り替え */
				/* 入力モード変換 */
				ChangeNameInputMode(is_kanji_enable, key);
			}
			break;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/14 by K.Okada */
		case DIALMARK:
			if (CharacterInput.AddressMarkInputMode) {
				InputAddressMarkOperation(is_kanji_enable);
			}
			else {
				NackBuzzer();
			}
			break;
#endif
#if (PRO_NAME_RECALL == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
		case SPEED:			/* 短縮						*/
			/** 電話帳オペレーション実行 */
			if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中・ローマ字カナ変換中でない時 */
				CursorOff();
				if (TelephoneBookOperation2() == TELBOOK_SET) {
					NameInputTelephoneBookOperation(is_kanji_enable);
				}
			}
			else {
				NackBuzzer();
			}
			break;
#endif
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[メールアドレス中で頻繁に使用される文字をセット]
	function	:[
		1.
	]
	return		:[]
	common		:[CharacterInput:登録オペレーション用入力バッファ]
	condition	:[]
	comment		:[
			".", "@", "_", "-"が順番に切り替わる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/14]
	author		:[K.Okada]
*************************************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/14 by K.Okada */	
void InputAddressMarkOperation(UBYTE is_kanji_enable)
{
	switch (CharacterInput.Mode) {		/* 入力モードにより処理が変わる */
#if defined(JPN)
	case ROMAN_TO_KANA_MODE:	/* ローマ字カナ変換モード（日本のみ） */
 #if (PRO_JIS_CODE == ENABLE)
	case KANJI_CODE_MODE:		/* 漢字コードモード（日本のみ） */
 #endif
		if (CheckInputCodeOrChangingKana() == FALSE) {	/* ローマ字カナ変換中でない時 */
			CharacterInputAddressMarkSet(is_kanji_enable);
		}
		else {
			NackBuzzer();
		}
		break;
#endif
	case UPPER_MODE:			/* 英数大文字モード */
	case LOWER_MODE:			/* 英数小文字モード */
	case SIGNAL_MODE:			/* 記号モード       */
		CharacterInputAddressMarkSet(is_kanji_enable);
		break;
	case HEX_CODE_MODE:			/* ＨＥＸコードモード */
	case CODE_MODE:				/* 記号・ＨＥＸコードモード */
		if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中でない時 */
			CharacterInputAddressMarkSet(is_kanji_enable);
		}
		else {											/* コード入力中の時 */
			NackBuzzer();
		}
		break;
	default:
		break;
	}
}
#endif

/*************************************************************************
	module		:[文字入力で数字キーが押されたときの処理]
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
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
void NameInputTenKeyOperation(UBYTE is_kanji_enable, UBYTE key)
{
	UBYTE	write_data_count;	/* 入力データ桁数 */

	/*----------------------------*/
	/* 次の入力が可能かを調べます */
	/*----------------------------*/
	if (!CheckNextDataWrite(is_kanji_enable, &write_data_count)) {
		NackBuzzer();
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* 入力バッファ桁数オーバー */
		return;
	}

	switch (CharacterInput.Mode) {		/* 入力モードにより処理が変わる */
#if defined(JPN)
	case ROMAN_TO_KANA_MODE:	/* ローマ字カナ変換モード（日本のみ） */
		if (CheckInputCodeOrChangingKana() == FALSE) {	/* ローマ字カナ変換中でない時 */
			CharacterInputDataSet(key);
		}
		else {
			NackBuzzer();
		}
		break;
 #if (PRO_JIS_CODE == ENABLE)
	case KANJI_CODE_MODE:		/* 漢字コードモード（日本のみ） */
		/* ポプラはイチョウに合わせて、コード入力モードでの＊，＃キーを有効にします
		** （ただし、コード入力途中は無効です） by K.Watanabe 1997/11/05
		*/
		if ((key >= TEN_0_KEY) && (key <= TEN_9_KEY)) {	/* ０～９の時 */
			NameInputKanjiCodeSet(key);
		}
		else {											/* ＊，＃の時 */
			if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中でない時 */
				CharacterInputDataSet(key);
			}
			else {											/* コード入力中の時 */
				NackBuzzer();
			}
		}
		break;
  #endif
#endif
	case UPPER_MODE:			/* 英数大文字モード */
	case LOWER_MODE:			/* 英数小文字モード */
	case SIGNAL_MODE:			/* 記号モード       */
		CharacterInputDataSet(key);
		break;
	case HEX_CODE_MODE:			/* ＨＥＸコードモード */
	case CODE_MODE:				/* 記号・ＨＥＸコードモード */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
		/* ポプラはイチョウに合わせて、コード入力モードでの＊，＃キーを有効にします
		** （ただし、コード入力途中は無効です） by K.Watanabe 1997/11/05
		*/
		if ((key >= TEN_0_KEY) && (key <= TEN_9_KEY)) {	/* ０～９の時 */
			NameInputHexCodeSet(key);
		}
		else {											/* ＊，＃の時 */
			if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中でない時 */
				CharacterInputDataSet(key);
			}
			else {											/* コード入力中の時 */
				NackBuzzer();
			}
		}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		if ((key >= TEN_0_KEY) && (key <= TEN_9_KEY)) {	/* ０～９が使用可能 */
			NameInputHexCodeSet(key);
		}
		else {
			NackBuzzer();
		}
#endif
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[名前入力でアルファベットキーが押されたときの処理]
	function	:[
		1.
	]
	return		:[]
	common		:[CharacterInput]
	condition	:[]
	comment		:[シート切り替えに注意]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
void AlphabetInputOperation(UBYTE is_kanji_enable, UBYTE key)
{
	UBYTE	write_data_count;	/* 入力データ桁数 */

	/*--------------------------------------------------------------------------------*/
	/* 入力モードの変更は、登録されているデータの桁数とは関係ないので、先に処理します */
	/*--------------------------------------------------------------------------------*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	if ((key >= ONETOUCH_38_KEY) && (key <= ONETOUCH_40_KEY)) {
		ChangeNameInputMode(is_kanji_enable, key);	/* 入力モード変換 */
		return;
	}
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) 	/* Add By H.Fujimura 1999/01/06 */
	if ((key >= ONETOUCH_27_KEY) && (key <= ONETOUCH_30_KEY)) {
		ChangeNameInputMode(is_kanji_enable, key);	/* 入力モード変換 */
		return;
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if ((key >= ONETOUCH_U1_KEY) && (key <= ONETOUCH_U8_KEY)) {
		ChangeNameInputMode(is_kanji_enable, key);	/* 入力モード変換 */
		return;
	}
#endif

	/*----------------------------*/
	/* 次の入力が可能かを調べます */
	/*----------------------------*/
	if (!CheckNextDataWrite(is_kanji_enable, &write_data_count)) {
		NackBuzzer();
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* 入力バッファ桁数オーバー */
		return;
	}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	/* 記号が割り当てられているワンタッチは、モードに関係なく入力可能です */
	if (OnetouchSignalTable[CMN_OnetouchCodeToOffset(key)] != NULL) {	/* 記号が割り当てられている時 */
		if (CheckInputCodeOrChangingKana() == FALSE) {	/* コード入力中・ローマ字カナ変換中でない時 */
			CharacterInputDataSet(OnetouchSignalTable[CMN_OnetouchCodeToOffset(key)]);
		}
		else {
			NackBuzzer();
		}
	}
	else {																/* 記号が割り当てられていない時 */
		/* 記号もアルファベットも割り当てられていないワンタッチは無効です */
		if (key > ONETOUCH_26_KEY) {	/* Ａ～Ｚ以外の時 */
			NackBuzzer();
		}
		else {							/* Ａ～Ｚの時 */
			switch (CharacterInput.Mode) {
 #if defined(JPN)
			case ROMAN_TO_KANA_MODE:	/* ローマ字カナ変換モード（日本のみ） */
				ChangeRomaToKana(key, write_data_count);
				break;
  #if (PRO_JIS_CODE == ENABLE)
			case KANJI_CODE_MODE:		/* 漢字コードモード（日本のみ） */
				if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_06_KEY)) {	/* Ａ～Ｆの時 */
					NameInputKanjiCodeSet(key);
				}
				else {														/* Ｇ～Ｚの時 */
					NackBuzzer();
				}
				break;
  #endif
 #endif
			case UPPER_MODE:			/* 英数大文字モード */
			case LOWER_MODE:			/* 英数小文字モード */
				ChangeUpperLowerSignal(key);
				break;
			case CODE_MODE:				/* 記号・ＨＥＸコードモード */
				if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_06_KEY)) {	/* Ａ～Ｆの時 */
					NameInputHexCodeSet(key);
				}
				else {														/* Ｇ～Ｚの時 */
					NackBuzzer();
				}
				break;
			default:
				break;
			}
		}
	}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
	switch (CharacterInput.Mode) {
 #if defined(JPN)
	case ROMAN_TO_KANA_MODE:	/* ローマ字カナ変換モード（日本のみ） */
		ChangeRomaToKana(key, write_data_count);
		break;
  #if (PRO_JIS_CODE == ENABLE)
	case KANJI_CODE_MODE:		/* 漢字コードモード（日本のみ） */
		if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_06_KEY)) {	/* Ａ～Ｆの時 */
			NameInputKanjiCodeSet(key);
		}
		else {
			NackBuzzer();
		}
		break;
  #endif
 #endif
	case UPPER_MODE:			/* 英数大文字モード */
	case LOWER_MODE:			/* 英数小文字モード */
	case SIGNAL_MODE:			/* 記号モード */
		ChangeUpperLowerSignal(key);
		break;
	case HEX_CODE_MODE:			/* ＨＥＸコードモード */
		if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_06_KEY)) {	/* Ａ～Ｆの時 */
			NameInputHexCodeSet(key);
		}
		else {
			NackBuzzer();
		}
		break;
	default:
		break;
	}
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	switch (CharacterInput.Mode) {
 #if defined(JPN)
	case ROMAN_TO_KANA_MODE:	/* ローマ字カナ変換モード（日本のみ） */
		ChangeRomaToKana(key, write_data_count);
		break;
 #endif
	case UPPER_MODE:			/* 英数大文字モード */
	case LOWER_MODE:			/* 英数小文字モード */
	case SIGNAL_MODE:			/* 記号モード */
		ChangeUpperLowerSignal(key);
		break;
	case HEX_CODE_MODE:			/* ＨＥＸコードモード */
		if (((key >= ONETOUCH_A_KEY) && (key <= ONETOUCH_F_KEY))
		 || ((key >= ONETOUCH_a_KEY) && (key <= ONETOUCH_f_KEY))) {	/* Ａ～Ｆ或いはａ～ｆの時 */
			NameInputHexCodeSet(key);
		}
		else {
			NackBuzzer();
		}
		break;
	default:
		break;
	}
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
}

/*************************************************************************
	module		:[大文字／小文字／記号変換]
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
	date		:[1995/11/28]
	author		:[江口,渡辺一章]
*************************************************************************/
void ChangeUpperLowerSignal(UBYTE key)
{
	UBYTE	set_code;

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	switch (CharacterInput.Mode) {
	case UPPER_MODE:	/* 英数大文字モード */
		set_code = key;
		break;
	case LOWER_MODE:	/* 英数小文字モード */
		set_code = (UBYTE)(key + 0x20);
		break;
	case CODE_MODE:		/* 記号・ＨＥＸコードモード */
		/* 記号の文字コードに変換 */
		set_code = OnetouchSignalTable[CMN_OnetouchCodeToOffset(key)];
		break;
	default:
		break;
	}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
	switch (CharacterInput.Mode) {
	case UPPER_MODE:	/* 英数大文字モード */
		set_code = key;
		break;
	case LOWER_MODE:	/* 英数小文字モード */
		set_code = (UBYTE)(key + 0x20);
		break;
	case SIGNAL_MODE:	/* 記号モード */
		/* 記号の文字コードに変換 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* Dial-UpｲﾝﾀｰﾈｯﾄFAX用の処理追加 1998/03/12 by K.Okada */
		if ((CharacterInput.Only7bitAsciiEnable == 1)
		&&	(key == ONETOUCH_Y_KEY)) {
			/* ・は8bitコードなので入力禁止 */
			NackBuzzer();
			return;
		}
#endif
		set_code = OnetouchSignalTable[(UBYTE)(key - ONETOUCH_01_KEY)];
		break;
	default:
		break;
	}
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (ONETOUCH_A_KEY <= key && key <= ONETOUCH_Z_KEY) {	/* Ａ～Ｚ */
		switch (CharacterInput.Mode) {
		case UPPER_MODE:	/* 英数大文字モード */
			set_code = key;
			break;
		case LOWER_MODE:	/* 英数小文字モード */
			set_code = (UBYTE)(key + 0x20);
			break;
		case SIGNAL_MODE:	/* 記号モード */
			/* 記号の文字コードに変換 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* Dial-UpｲﾝﾀｰﾈｯﾄFAX用の処理追加 1998/03/12 by K.Okada */
			if ((CharacterInput.Only7bitAsciiEnable == 1)
			&&	(key == ONETOUCH_Y_KEY)) {
				/* ・は8bitコードなので入力禁止 */
				NackBuzzer();
				return;
			}
#endif
			set_code = OnetouchSignalTable[CMN_OnetouchCodeToOffset(key)];
			break;
		default:
			break;
		}
	}
	else {													/* ａ～ｚ */
		switch (CharacterInput.Mode) {
		case UPPER_MODE:	/* 英数大文字モード */
			set_code = (UBYTE)(key - 0x20);
			break;
		case LOWER_MODE:	/* 英数小文字モード */
			set_code = key;
			break;
		case SIGNAL_MODE:	/* 記号モード */
			/* 記号の文字コードに変換 */
			key -= 0x20;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* Dial-UpｲﾝﾀｰﾈｯﾄFAX用の処理追加 1998/03/12 by K.Okada */
			if ((CharacterInput.Only7bitAsciiEnable == 1)
			&&	(key == ONETOUCH_Y_KEY)) {
				/* ・は8bitコードなので入力禁止 */
				NackBuzzer();
				return;
			}
#endif
			set_code = OnetouchSignalTable[CMN_OnetouchCodeToOffset(key)];
			break;
		default:
			break;
		}
	}
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

	/* バッファにセット */
	CharacterInputDataSet(set_code);
}

/*************************************************************************
	module		:[名前入力のモード変更]
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
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
void ChangeNameInputMode(UBYTE is_kanji_enable, UBYTE key)
{
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	UBYTE	old_mode;	/* 変更前の入力モード */

	/* 変更前のモードを退避します */
	old_mode = CharacterInput.Mode;

	switch (key) {
 #if defined(JPN)
	case ONETOUCH_38_KEY:
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
  		if (CharacterInput.Only7bitAsciiEnable == 1) {
			NackBuzzer();
		}
		else {
   #if (PRO_JIS_CODE == ENABLE)
			if (is_kanji_enable) {	/* 漢字入力が可能な時 */
				if (CharacterInput.Mode == ROMAN_TO_KANA_MODE) {
					CharacterInput.Mode = KANJI_CODE_MODE;		/* 漢字コードモード（日本のみ） */
				}
				else {
					CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
				}
			}
			else {					/* 漢字入力が不可能な時 */
				CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
			}
   #else
			CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
   #endif
  		}
  #else
   #if (PRO_JIS_CODE == ENABLE)
		if (is_kanji_enable) {	/* 漢字入力が可能な時 */
			if (CharacterInput.Mode == ROMAN_TO_KANA_MODE) {
				CharacterInput.Mode = KANJI_CODE_MODE;		/* 漢字コードモード（日本のみ） */
			}
			else {
				CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
			}
		}
		else {					/* 漢字入力が不可能な時 */
			CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
		}
   #else
		CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
   #endif
  #endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */
		break;
 #endif
	case ONETOUCH_39_KEY:
		if (CharacterInput.Mode == UPPER_MODE) {
			CharacterInput.Mode = LOWER_MODE;	/* 英数小文字モード */
		}
		else {
			CharacterInput.Mode = UPPER_MODE;	/* 英数大文字モード */
		}
		break;
	case ONETOUCH_40_KEY:
	case ONETOUCH_80_KEY:
		CharacterInput.Mode = CODE_MODE;	/* 記号・ＨＥＸコードモード */
		break;
	case OPR_SHEET_CHANGE:
		/* ポプラはイチョウに合わせて、シートを変更されてもモードは変更しません
		** 注）ただし、シート１からシート２にされた場合、直接モードは変更しませんが、
		** 　　処理的にはモードなしの扱いにします by K.Watanabe 1997/11/06
		*/
		break;
	default:
		break;
	}

	/* コード入力中・ローマ字カナ変換中にモードが変更された場合は、変換途中の内容をクリアします */
	if (CheckInputCodeOrChangingKana() == TRUE) {	/* コード入力中・ローマ字カナ変換中の時 */
		if (key != OPR_SHEET_CHANGE) {	/* モード切り換えキーが押された時 */
			if (CharacterInput.Mode != old_mode) {	/* モードが変更された時 */
				AllClearInputKeyBuffer();	/* 変換途中の内容をクリア */
			}
		}
		else {							/* シート切り換えがされた時 */
			if ((GetOnetouchSheetStatus() == ONETOUCH_SHEET2)	/* シート１からシート２に切り換えられた時 */
			 && (CharacterInput.Mode != CODE_MODE)) {			/* 記号・ＨＥＸコードモードでない時 */
				AllClearInputKeyBuffer();	/* 変換途中の内容をクリア */
			}
		}
	}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */

#if (PRO_KEYPANEL == PANEL_HINOKI) 	/* Add By H.Fujimura 1999/01/06 */
	UBYTE	old_mode;	/* 変更前の入力モード */

	/* 変更前のモードを退避します */
	old_mode = CharacterInput.Mode;

	switch (key) {
 #if defined(JPN)
	case ONETOUCH_27_KEY:
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (CharacterInput.Only7bitAsciiEnable == 1) {
			NackBuzzer();
		}
		else {
   #if (PRO_JIS_CODE == ENABLE)
			if (is_kanji_enable) {	/* 漢字入力が可能な時 */
				if (CharacterInput.Mode == ROMAN_TO_KANA_MODE) {
					CharacterInput.Mode = KANJI_CODE_MODE;		/* 漢字コードモード（日本のみ） */
				}
				else {
					CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
				}
			}
			else {					/* 漢字入力が不可能な時 */
				CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
			}
   #else
			CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
   #endif
  		}
  #else
   #if (PRO_JIS_CODE == ENABLE)
		if (is_kanji_enable) {	/* 漢字入力が可能な時 */
			if (CharacterInput.Mode == ROMAN_TO_KANA_MODE) {
				CharacterInput.Mode = KANJI_CODE_MODE;		/* 漢字コードモード（日本のみ） */
			}
			else {
				CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
			}
		}
		else {					/* 漢字入力が不可能な時 */
			CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
		}
   #else
		CharacterInput.Mode = ROMAN_TO_KANA_MODE;		/* ローマ字カナ変換モード（日本のみ） */
   #endif
  #endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */
		break;
 #endif
	case ONETOUCH_28_KEY:
		if (CharacterInput.Mode == UPPER_MODE) {
			CharacterInput.Mode = LOWER_MODE;	/* 英数小文字モード */
		}
		else {
			CharacterInput.Mode = UPPER_MODE;	/* 英数大文字モード */
		}
		break;
	case ONETOUCH_29_KEY:
#if (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/12 */
		if (CharacterInput.Mode == SIGNAL_MODE) {	/* 記号モードの時 */
			CharacterInput.Mode = HEX_CODE_MODE;	/* ＨＥＸコードモード */
		}
		else {
			CharacterInput.Mode = SIGNAL_MODE;		/* 記号モード */
		}
#else
		CharacterInput.Mode = SIGNAL_MODE;		/* 記号モード */
#endif
		break;
	case ONETOUCH_30_KEY:
		CharacterInput.Mode = HEX_CODE_MODE;	/* ＨＥＸコードモード */
		break;
	default:
		break;
	}

	/* コード入力中・ローマ字カナ変換中にモードが変更された場合は、変換途中の内容をクリアします */
	if (CheckInputCodeOrChangingKana() == TRUE) {	/* コード入力中・ローマ字カナ変換中の時 */
		if (CharacterInput.Mode != old_mode) {	/* モードが変更された時 */
			AllClearInputKeyBuffer();	/* 変換途中の内容をクリア */
		}
	}
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (CheckInputCodeOrChangingKana() == TRUE) {	/* コード入力中・ローマ字カナ変換中の時 */
		NackBuzzer();
	}
	else {
		switch (key) {
 #if defined(JPN)
		case ONETOUCH_U1_KEY:
		case ONETOUCH_U5_KEY:
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			if (CharacterInput.Only7bitAsciiEnable == 1) {
				NackBuzzer();
			}
			else {
				CharacterInput.Mode = ROMAN_TO_KANA_MODE;
			}
  #else
			CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
  #endif
			break;
		case ONETOUCH_U2_KEY:
		case ONETOUCH_U6_KEY:
			if (CharacterInput.Mode == UPPER_MODE) {
				CharacterInput.Mode = LOWER_MODE;	/* 英数小文字モード */
			}
			else {
				CharacterInput.Mode = UPPER_MODE;	/* 英数大文字モード */
			}
			break;
 #else
		case ONETOUCH_U1_KEY:
		case ONETOUCH_U5_KEY:
			CharacterInput.Mode = UPPER_MODE;	/* 英数大文字モード */
			break;
		case ONETOUCH_U2_KEY:
		case ONETOUCH_U6_KEY:
			CharacterInput.Mode = LOWER_MODE;	/* 英数小文字モード */
			break;
 #endif
		case ONETOUCH_U3_KEY:
		case ONETOUCH_U7_KEY:
			CharacterInput.Mode = SIGNAL_MODE;		/* 記号モード */
			break;
		case ONETOUCH_U4_KEY:
		case ONETOUCH_U8_KEY:
			CharacterInput.Mode = HEX_CODE_MODE;	/* ＨＥＸコードモード */
			break;
		case OPR_SHEET_CHANGE:
			SetCharacterInputMode();
			break;
		default:
			break;
		}
	}
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
}

/*************************************************************************
	module		:[カナ変換入力バッファをオールクリアする]
	function	:[]
	return		:[]
	common		:[
				CharacterInput
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/11]
	author		:[江口]
*************************************************************************/
void AllClearInputKeyBuffer(void)
{
	/* HEXコードで入力された場合、InputKeyBufferを使用するので クリアしておきます*/
	CMN_MemorySetNULL(CharacterInput.InputKeyBuffer, 4, NULL);
	CharacterInput.InputKeyPosition = 0;
}

/*************************************************************************
	module		:[ＨＥＸモードで入力されたコードをバッファにセット]
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
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
void NameInputHexCodeSet(UBYTE key)
{
	UBYTE	data;

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if ((key >= ONETOUCH_a_KEY) && (key <= ONETOUCH_f_KEY)) {	/* 小文字の場合 */
		key -= 0x20;	/* 大文字に変換 */
	}
#endif

	if (CharacterInput.InputKeyPosition >= 2) {	/* すでに２文字入力されている時 */
		NackBuzzer();
		AllClearInputKeyBuffer();
	}
	else {										/* １文字目か２文字目の入力の時 */
		CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = key;
		CharacterInput.InputKeyPosition++;
		if (CharacterInput.InputKeyPosition == 2) {	/* ２文字分入力(ASCIIコードの上位、下位ともに入力された) */
			data = ChangeHexCodeToChar();		/* ASCIIコードに変換 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			if (CharacterInput.Only7bitAsciiEnable == 1) {
				if (0x20 <= data && data <= 0x7F) {
					CharacterInputDataSet(data);
				}
				else {
					NackBuzzer();
				}
			}
			else {
 #if (PRO_JIS_CODE == ENABLE)
				/* 0x20未満	：制御コード
				** 80～9F	：未使用領域
				** E0～FF	：漢字コード（ｼﾌﾄJIS第２水準ｴﾘｱ）と重なるので除く
				*/
				if ((0x20 <= data && data <= 0x7F) || (0xA0 <= data && data <= 0xDF)) {
					CharacterInputDataSet(data);
				}
				else {
					NackBuzzer();
				}
 #else
				/* 0x20未満	：制御コード
				** 80～9F	：未使用領域
				*/
				if ((0x20 <= data && data <= 0x7F) || (0xA0 <= data && data <= 0xFF)) {
					CharacterInputDataSet(data);
				}
				else {
					NackBuzzer();
				}
			}
 #endif
#else
 #if (PRO_JIS_CODE == ENABLE)
			/* 0x20未満	：制御コード
			** 80～9F	：未使用領域
			** E0～FF	：漢字コード（ｼﾌﾄJIS第２水準ｴﾘｱ）と重なるので除く
			*/
			if ((0x20 <= data && data <= 0x7F) || (0xA0 <= data && data <= 0xDF)) {
				CharacterInputDataSet(data);
			}
			else {
				NackBuzzer();
			}
 #else
  #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
   #if defined(JPN)
			/* 0x20未満	：制御コード
			** 80～9F	：未使用領域
			*/
			if ((0x20 <= data && data <= 0x7F) || (0xA0 <= data && data <= 0xFF)) {
				CharacterInputDataSet(data);
			}
			else {
				NackBuzzer();
			}
   #else	/* 現状はＴＷＮのみ */
			/* 0x20未満	：制御コード
			** 20～7F	：標準ＡＳＣＩＩ領域
			** 80～9F	：ヨーロッパ特殊コード領域
			** E0～FF	：ヨーロッパ特殊コード領域＋曜日用半角漢字領域
			*/
			if (   (0x20 <= data && data <= 0x7F)
				|| (0x80 <= data && data <= 0x9F)
				|| (0xE0 <= data && data <= 0xFF)) {
				CharacterInputDataSet(data);
			}
			else {
				NackBuzzer();
			}
   #endif
  #else
			/* 0x20未満	：制御コード
			** 80～9F	：未使用領域
			*/
			if ((0x20 <= data && data <= 0x7F) || (0xA0 <= data && data <= 0xFF)) {
				CharacterInputDataSet(data);
			}
			else {
				NackBuzzer();
			}
   #endif
 #endif
#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */
			AllClearInputKeyBuffer();
		}
	}
}

/*************************************************************************
	module		:[ＨＥＸコードで入力されたものを文字コードに変換]
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
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE ChangeHexCodeToChar(void)
{
	UBYTE	code1;
	UBYTE	code2;
	UBYTE	ascii_code;

	ascii_code = 0;
	code1 = CharacterInput.InputKeyBuffer[0];
	code2 = CharacterInput.InputKeyBuffer[1];

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	if (ONETOUCH_01_KEY <= code1 && code1 <= ONETOUCH_06_KEY) {
		code1 -= 0x37;
	}
	else if (TEN_0_KEY <= code1 && code1 <= TEN_9_KEY) {
		code1 = ChangeASC_CodeToNumber(code1);
	}
	if (ONETOUCH_01_KEY <= code2 && code2 <= ONETOUCH_06_KEY) {
		code2 -= 0x37;
	}
	else if (TEN_0_KEY <= code2 && code2 <= TEN_9_KEY) {
		code2 = ChangeASC_CodeToNumber(code2);
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (ONETOUCH_A_KEY <= code1 && code1 <= ONETOUCH_F_KEY) {
		code1 -= 0x37;
	}
	else if (TEN_0_KEY <= code1 && code1 <= TEN_9_KEY) {
		code1 = ChangeASC_CodeToNumber(code1);
	}
	if (ONETOUCH_A_KEY <= code2 && code2 <= ONETOUCH_F_KEY) {
		code2 -= 0x37;
	}
	else if (TEN_0_KEY <= code2 && code2 <= TEN_9_KEY) {
		code2 = ChangeASC_CodeToNumber(code2);
	}
#endif

	ascii_code = (UBYTE)(((code1 << 4) & 0xF0) + (code2 & 0x0F));	/* ビットのマスクは別に必要じゃない */

	return (ascii_code);
}

/*************************************************************************
	module		:[名前入力、入力モード表示]
	function	:[
		1.上段に入力モードをひょうじします
		2.表示を更新するのは上段の右から８文字分だけです
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/11]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayNameInputMode(void)
{
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	/* ポプラはイチョウに合わせて、シート１からシート２にされた場合は、モードなしにします by K.Watanabe 1997/11/06 */
	if ((GetOnetouchSheetStatus() == ONETOUCH_SHEET2)	/* 現在のシートがシート２の時 */
	 && (CharacterInput.Mode != CODE_MODE)) {			/* 記号・ＨＥＸコードモードでない時 */
		DisplayStringHigh(11, D2W_ModeNone);	/* [:        ] */
		return;
	}
#endif

	switch (CharacterInput.Mode) {
#if defined(JPN)	/* 1997/06/16 Y.Matsukuma */
 #if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/17 */
	case ROMAN_TO_KANA_MODE:	/* ローマ字カナ変換モード（日本のみ） */
		DisplayStringHigh(11, D2W_Kana);		/* [:ｶﾀｶﾅ    ] */
		break;
  #if (PRO_JIS_CODE == ENABLE)
	case KANJI_CODE_MODE:		/* 漢字コードモード（日本のみ） */
		DisplayStringHigh(11, D2W_KanjiCode);	/* [:ｶﾝｼﾞｺｰﾄﾞ] */
		break;
  #endif
 #endif
#endif
	case UPPER_MODE:			/* 英数大文字モード */
		DisplayStringHigh(11, D2W_Upper);		/* [:ｴｲｽｳ ﾀﾞｲ] */
		break;
	case LOWER_MODE:			/* 英数小文字モード */
		DisplayStringHigh(11, D2W_Lower);		/* [:ｴｲｽｳ ｼｮｳ] */
		break;
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	case SIGNAL_MODE:			/* 記号モード */
		DisplayStringHigh(11, D2W_Symbol);		/* [:ｷｺﾞｳ    ] */
		break;
	case HEX_CODE_MODE:			/* ＨＥＸコードモード */
		DisplayStringHigh(11, D2W_Code);		/* [:ｺｰﾄﾞ    ] */
		break;
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	case CODE_MODE:				/* 記号・ＨＥＸコードモード */
		DisplayStringHigh(11, D2W_Code);		/* [:ｺｰﾄﾞ    ] */
		break;
#endif
	default:
		break;
	}
}

/*************************************************************************
	module		:[名前入力データ表示]
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
	date		:[1995/04/11]
	author		:[江口]
*************************************************************************/
void DisplayNameInputValue(void)
{
	UBYTE	cursor_disp_position;
	UBYTE	diff;
	UBYTE	over_count;
	UBYTE	disp_enable_count;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/16 by K.Okada */
	UBYTE	length;
#endif

	cursor_disp_position = 0;
	diff = 0;
	over_count = 0;
	disp_enable_count = 0;

	disp_enable_count = (UBYTE)(OPR_DISPLAY_MAX - CharacterInput.LcdDisplayPosition);

	if (CheckChildErrorDisplayReq() == TRUE) {	/* エラー等でチャイルド表示要求がある場合 */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {	/* チャイルド表示中 */
		return;
	}

	/* 下段表示用バッファをクリア */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	if (CheckInputCodeOrChangingKana() == TRUE) {	/* コード入力中・ローマ字カナ変換中の時 */
		/* "[B_   ]            " と表示 */
		FunctionDisplayBufferLow[0] = '[';
		CMN_StringCopy(&FunctionDisplayBufferLow[1], CharacterInput.InputKeyBuffer);
		FunctionDisplayBufferLow[5] = ']';
		cursor_disp_position = (UBYTE)(CharacterInput.InputKeyPosition + 1);
	}
	else {											/* 通常入力中 */
		/* CharacterInput.Bufferの内容を表示 */
		/* 表示文字数はカーソルを含んで２０桁 */

		/* 表示開始位置を計算する */
		if (CharacterInput.DisplayStartPosition > CharacterInput.CursorPosition) { /* 表示開始位置よりｶｰｿﾙが前にある */
			/* カーソル位置を先頭に２０文字分(表示可能文字数分）表示するので表示位置をカーソル位置に持ってくる  */
			CharacterInput.DisplayStartPosition = CharacterInput.CursorPosition;
		}
		else if (CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition) { /* 表示位置とｶｰｿﾙ位置が同じ */
			/* カーソル位置を先頭に２０文字分表示する */
			;
		}
		else {	/* 表示開始位置よりカーソルが後ろにある */
			/* 表示開始位置とｶｰｿﾙ位置までの差が２０文字(表示可能文字数分）以内であれば表示位置から２０文字分表示する
			** 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）を越える場合は
			** カーソル位置がＬＣＤの右端にくるように表示位置を調整する
			*/
			diff = (UBYTE)((CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition) + 1);
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
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/16 K.Okada */
		if (OPR_DisplayMaskingFlag == 1) {/* 下段表示マスク要求あり */
			length = CMN_StringLength(&CharacterInput.Buffer[CharacterInput.DisplayStartPosition]);
			if (length > disp_enable_count) {
				length = disp_enable_count;
			}
			CMN_MemorySet(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition], (UWORD)length , '*');
		}
		else {
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition],
					   	    		 &CharacterInput.Buffer[CharacterInput.DisplayStartPosition],
						   	     	 disp_enable_count);
		}
#else 
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition],
								 &CharacterInput.Buffer[CharacterInput.DisplayStartPosition],
								 disp_enable_count);
#endif
		/* カーソル位置を計算 */
		cursor_disp_position = CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition;
	}

	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor_disp_position + CharacterInput.LcdDisplayPosition));
}

/*************************************************************************
	module		:[ローマ字／カナ変換実行]
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
	date		:[1995/04/12]
	author		:[渡辺一章]
*************************************************************************/
void ChangeRomaToKana(UBYTE key, UBYTE write_data_count)
{
#if defined(JPN) && (PRO_ANK_TO_KANJI == DISABLE)	/* PRO_ANK_TO_KANJIの条件追加 by K.Watanabe 1999/06/15 */
	UBYTE	count;
	UBYTE	small_tsu;			/* 小さいツをいれるかどうかのフラグ */
	UBYTE	pos;
	UBYTE	compare;
	UBYTE	romaji_start;
	UBYTE	is_compare_NG;	/* ローマ字比較を行ったかどうか */
	UBYTE	kana[5];
	UBYTE	romaji_buf[4];		/* ローマ字カナ変換テーブル直接比較用バッファ */
	UWORD	i;					/* ループ変数 */

	small_tsu = 0;
	pos = 0;
	compare = 0xFF;
	romaji_start = 0;
	is_compare_NG = FALSE;
	CMN_MemorySet(kana, 5, NULL);
	CMN_MemorySetNULL(romaji_buf, 3, ' ');

	if (CharacterInput.InputKeyPosition >= 4) {	/* 変換前のローマ字が４文字を越えた場合 */
		NackBuzzer();
	}
	else {										/* 変換実行 */
		CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = key;
		CharacterInput.InputKeyPosition++;

		/** 小さいツをつけるのかチェックする */
		if ((CharacterInput.InputKeyBuffer[0] == CharacterInput.InputKeyBuffer[1])
		 && (CharacterInput.InputKeyBuffer[0] != 'N')) {	/* 小さいツが最初に入る */
			small_tsu = 1;
			romaji_start = 1;
		}

		/* ローマ字カナ変換用テーブルのローマ字部分と入力されたローマ字部分を直接比較できるように、
		** テーブルより変換するローマ字部分だけを、比較用バッファにコピーする
		*/
		CMN_StringCopy(&romaji_buf[0], &CharacterInput.InputKeyBuffer[romaji_start]);

		/** 入力したローマ字がカナ変換できるかをチェックします */
		for (i = 0; i < OPR_ROMAJI_KANA_TABLE_MAX; i++) {
			/* 比較時間短縮のために、先頭のアルファベットが同じになってからローマ字全部を比較します
			** 注）変換テーブルのローマ字部分の並び順はアルファバット順です（Ａ→Ｚ）
			*/
			if (romaji_buf[0] == RomajiToKatakanaTable[i].Romaji[0]) {
				compare = CMN_StringCompare(&romaji_buf[0], (UBYTE *)&RomajiToKatakanaTable[i].Romaji[0], 3);
				/* ローマ字カナ変換できたら、ループを抜けます */
				if (compare == STRCMP_EQUAL) {
					break;
				}
				if (!is_compare_NG) {
					is_compare_NG = TRUE;
				}
			}
			else {
				if (is_compare_NG) {	/* 入力したローマ字が変換できなかった時 */
					break;
				}
			}
		}

		if (compare == STRCMP_EQUAL) {	/* ローマ字カナ変換ができる時 */
			if (small_tsu == 1) {	/* 小さいツを挿入する時 */
				kana[pos] = 0xAF;	/* 'ｯ' */
				pos++;
			}
			CMN_StringCopyNULL(&kana[pos], &RomajiToKatakanaTable[i].Katakana[0]);
			count = CMN_StringLength(kana);
			if (write_data_count + count > CharacterInput.MaxFigure) {	/* 変換後のカナを格納するだけの空きがない */
				NackBuzzer();
				OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* "ｹﾀｽｳ ｵｰﾊﾞｰ ﾃﾞｽ      " */
			}
			else {
				/* 変換したカナデータをバッファにセット */
				KANA_Data_Set(&kana[0]);
				/* ﾛｰﾏ字からｶﾀｶﾅに変換後のﾃﾞｰﾀをｾｯﾄする */
			}
		}
		else {							/* 一致するデータがない場合 */
			/* 念のためクリアしておく */
			*kana = NULL;
		}
	}
#else
	return;
#endif
}

/*************************************************************************
	module		:[変換後のカナをバッファにセット]
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
	date		:[1995/07/20]
	author		:[江口]
*************************************************************************/
void KANA_Data_Set(UBYTE *kana)
{
	UBYTE	i;
	UBYTE	count;

	count = CMN_StringLength(kana);
	for (i = 0; i < count; i++) {
		CharacterInputDataSet(kana[i]);
	}
	AllClearInputKeyBuffer();
}

/*************************************************************************
	module		:[コード入力中・ローマ字カナ変換中検査]
	function	:[
		1.漢字コード入力中，ローマ字カナ変換中，ＨＥＸコード入力中
		　かどうかをチェックします。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/21]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE CheckInputCodeOrChangingKana(void)
{
	if (CharacterInput.InputKeyPosition > 0) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[ローマ字カナ変換バッファのデータを１文字クリア]
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
	date		:[1995/07/21]
	author		:[江口]
*************************************************************************/
void ClearInputKeyBuffer(void)
{
	CharacterInput.InputKeyPosition--;
	CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = NULL;
}

/*************************************************************************
	module		:[入力モードの初期値セット]
	function	:[
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)
		1.現在のシートがシート１の時、日本　　 → ローマ字カナ変換モード
		                              日本以外 → 英数大文字モード
		2.現在のシートがシート２の時、記号・ＨＥＸコードモード
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		1.日本		：ローマ字カナ変換モード
		2.日本以外	：シート１→英大文字
		,			：シート２→英小文字
#endif
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/11/27]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetCharacterInputMode(void)
{
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)
	/* ポプラはイチョウに合わせて、シートを変更されてもモードは変更しないので、初期値はシート１のモードになります
	** 注）シート２の状態の時は、モードだけで判断せずにシートの状態と合わせて判断しています by K.Watanabe 1997/11/06
	*/
 #if defined(JPN)
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
 	if (CharacterInput.Only7bitAsciiEnable == 1) {
		CharacterInput.Mode = UPPER_MODE;
	}
	else {
		CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
	}
  #else
	CharacterInput.Mode = ROMAN_TO_KANA_MODE;	/* ローマ字カナ変換モード（日本のみ） */
  #endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada */ 
 #else
	CharacterInput.Mode = UPPER_MODE;			/* 英数大文字モードにする */
 #endif
#elif (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/11/28 */
 /* 初期文字入力モードの設定 */
 #if defined(JPN)
	CharacterInput.Mode = OPR_KATAKANA_MODE;    /* カタカナ入力モード   */
 #else
	CharacterInput.Mode = OPR_ALPHAMERIC_MODE;  /* 英数字入力モード     */
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (GetOnetouchSheetStatus() == ONETOUCH_SHEET1) {	/* 現在のシートがシート１の時 */
		CharacterInput.Mode = UPPER_MODE;	/* 英数大文字モードにする */
	}
	else {												/* 現在のシートがシート２の時 */
		CharacterInput.Mode = LOWER_MODE;	/* 英数小文字モードにする */
	}
#endif
}

/*************************************************************************
	module		:[漢字コード入力処理]
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
	date		:[1997/03/12]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_JIS_CODE == ENABLE)
void NameInputKanjiCodeSet(UBYTE key)
{
	UBYTE	i;			/* ループ変数 */
	UWORD	input_code;	/* 入力コード */

	if (CharacterInput.InputKeyPosition >= 4) {	/* 入力された漢字コードが間違いの時 */
		NackBuzzer();
	}
	else {										/* 変換実行 */
		CharacterInput.InputKeyBuffer[CharacterInput.InputKeyPosition] = key;
		CharacterInput.InputKeyPosition++;

		if (CharacterInput.InputKeyPosition == 4) {	/* ４桁入力された時 */
			/* 入力された値を１６進数に変換 */
			input_code = CMN_ASC_ToUnsignedIntHex(&CharacterInput.InputKeyBuffer[0], 4);

			/* 入力されたコードがJISコード（第１水準・定義されている第２水準）かどうかを調べます */
			if (CheckJIS1Code(input_code) || (CheckFontJIS2Code(input_code) != KANJI2_NONE)) {
				/* 入力バッファに漢字コードを表すかっこと共にセットする */
				CharacterInputDataSet(OPR_KANJI_CODE_MARK_LEFT);	/* 漢字コードを表す左かっこ */
				for (i = 0; i < (UBYTE)(OPR_KANJI_CODE_LEN - 2); i++) {
					CharacterInputDataSet(CharacterInput.InputKeyBuffer[i]);
				}
				CharacterInputDataSet(OPR_KANJI_CODE_MARK_RIGHT);	/* 漢字コードを表す右かっこ */
				AllClearInputKeyBuffer();
			}
			else {										/* 不当なコードの場合 */
				NackBuzzer();
			}
		}
	}
}
#endif	/* (PRO_JIS_CODE == ENABLE) */

/*************************************************************************
	module		:[次入力可能検査]
	function	:[
		1.入力モード毎の最低入力文字数から、次入力が可能かどうかを調べます
		  ただしローマ字入力はこの時点では正確な判断はできません
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/22]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckNextDataWrite(UBYTE is_kanji_enable, UBYTE *write_data_count)
{
	UBYTE	add_data_count;		/* 入力最小文字数 */
	UBYTE	ret;				/* リターン値 */

	ret = TRUE;

	/*--------------------------------------------*/
	/* すでに入力されているデータの桁数を調べます */
	/*--------------------------------------------*/
	add_data_count = 1;	/* 漢字以外の文字は半角文字なので最低１バイト使用します */
#if (PRO_JIS_CODE == ENABLE)
	if (is_kanji_enable) {	/* 漢字入力が可能な時 */
		/* 漢字コードは、表示上の文字数と実際にセットする時の文字数が違うために
		** CharacterInput.WritePositionを使っての最大入力桁数の検査は行えないため、
		** GetWriteDataCount()を追加しました
		*/
		if (CharacterInput.Mode == KANJI_CODE_MODE) {	/* 漢字コードモードの時 */
			*write_data_count = GetWriteDataCount();
			add_data_count = 2;	/* 漢字は全角文字なので２バイト使用します */
		}
		else {											/* 片仮名・英数字・コード入力の時 */
			*write_data_count = GetWriteDataCount();
		}
	}
	else {					/* 漢字入力が不可能な時 */
		*write_data_count = CharacterInput.WritePosition;
	}
#else
	*write_data_count = CharacterInput.WritePosition;
#endif

	/*----------------------------*/
	/* 次の入力が可能かを調べます */
	/*----------------------------*/
	if ((UBYTE)(*write_data_count + add_data_count) > CharacterInput.MaxFigure) {
		ret = FALSE;
	}

	return(ret);
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

		漢字コードは、表示上は６文字［（１２３４）］使用していますが、
		実際は全角文字なので２文字しか使用しません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/18]
	author		:[渡辺一章]
*************************************************************************/
UBYTE GetWriteDataCount(void)
{
	UBYTE	count;	/* バッファ位置 */
	UBYTE	ret;	/* リターン値 */

	count = 0;
	ret = 0;

	while (CharacterInput.Buffer[count] != NULL) {	/* NULLで終了します */
		if (CharacterInput.Buffer[count] == OPR_KANJI_CODE_MARK_LEFT) {	/* 漢字コードの時 */
			count += OPR_KANJI_CODE_LEN;	/* バッファの位置を漢字コードの次にセットします */
			ret += 2;						/* 漢字コードは２文字としてあつかいます */
		}
		else {
			count++;						/* バッファの位置を次の文字にセットします */
			ret++;							/* 登録文字数を加算します */
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[名前入力用バッファ　セット]
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
	date		:[1997/07/16]
	author		:[渡辺一章]
*************************************************************************/
void SetCharacterInputBuf(UBYTE *set_data)
{
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
	OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, set_data, 0);	/* 前回登録データをセット */
#else 
	#if (PRO_JIS_CODE == ENABLE)
		UBYTE	tti_count;
		UBYTE	buffer_count;
		UWORD	code;
		UWORD	code1;
		UWORD	code2;
	#endif

	#if (PRO_JIS_CODE == ENABLE)
		/* 前回入力値を名前入力用バッファに展開する */
		tti_count = 0;
		buffer_count = 0;
		while (set_data[tti_count] != NULL) {	/* NULLで終了します */
			code1 = (UWORD)set_data[tti_count];
			code2 = (UWORD)set_data[tti_count + 1];
			if (CheckShiftJISCode((UBYTE)code1, (UBYTE)code2)) {	/* シフトJISコードの時 */

				/* 漢字コードの時は、格納値はシフトJISコードですが、入力値はJISコードなので変換して格納します
				** 注）格納先のバッファがバイトデータのため、JISコードで格納すると漢字コードとそれ以外の
				** 　　文字との区別がつかないので、入力値と格納値でコードの種類が違います
				*/
				CharacterInput.Buffer[buffer_count++] = OPR_KANJI_CODE_MARK_LEFT;	/* 漢字コードを表す左かっこ */

				/* 格納値をJISコードへ変換します */
				ShiftJIS_ToJIS(&code1, &code2);
				code = (code1 << 8) | code2;

				/* JISコードをアスキーコードに変換し、表示用バッファにセットします */
				CMN_HexToASC(&CharacterInput.Buffer[buffer_count], (UDWORD)code, 4);
				tti_count += 2;
				buffer_count += 4;
				CharacterInput.Buffer[buffer_count++] = OPR_KANJI_CODE_MARK_RIGHT;	/* 漢字コードを表す右かっこ */
			}
			else {													/* 英数字・片仮名・記号の時 */
				CharacterInput.Buffer[buffer_count++] = set_data[tti_count++];
			}
		}
	#else
		/* 前回入力値を名前入力用バッファにコピーする */
		CMN_StringCopy(CharacterInput.Buffer, set_data);
	#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

#if (PRO_NAME_RECALL == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
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
	author		:[藤村春夫]
*************************************************************************/
void NameInputTelephoneBookOperation(UBYTE is_kanji_enable)
{
	UBYTE	add_data_count;		/* 入力最小文字数 */
	UBYTE	write_data_count;	/* 入力データ桁数 */
	UBYTE	i;					/* ループ変数 */

	/*--------------------------------------------*/
	/* すでに入力されているデータの桁数を調べます */
	/*--------------------------------------------*/
	add_data_count = CMN_StringLength(CharacterInput.Name);
#if (PRO_JIS_CODE == ENABLE)
	if (is_kanji_enable) {	/* 漢字入力が可能な時 */
		/* 漢字コードは、表示上の文字数と実際にセットする時の文字数が違うために
		** CharacterInput.WritePositionを使っての最大入力桁数の検査は行えないため、
		** GetWriteDataCount()を追加しました
		*/
		write_data_count = GetWriteDataCount();
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
	if ((UBYTE)(write_data_count + add_data_count) > CharacterInput.MaxFigure) {
		NackBuzzer();
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* 入力バッファ桁数オーバー */
		return;
	}

	/*--------------------------*/
	/* 入力バッファにセットする */
	/*--------------------------*/
	for (i = 0; i < add_data_count; i++) {
		CharacterInputDataSet(CharacterInput.Name[i]);
	}
}
#endif
