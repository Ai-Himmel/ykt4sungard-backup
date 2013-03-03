/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_NUM.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 数字入力
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ポーズ追加特ＲＯＭ By H.Fujimura 1999/04/15 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/28 */
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif 		/* End of (defined (KEISATSU)) */

/* Prototype
UBYTE	NumberInput(UBYTE);
void	NumberInputInitial(UBYTE type);
UBYTE	NumberInputKeyGet(void);
void	DisplayNumberInput(void);
UWORD	FixedLengthNumberInput(UWORD, UWORD, UWORD, UBYTE, UBYTE *);
UBYTE	FixedLengthNumberInput2(UBYTE, UBYTE, UBYTE, UBYTE, UBYTE, UBYTE *);
UWORD	DecimalPointInput(UWORD, UWORD, UWORD, UBYTE, UBYTE *, UBYTE);
void	FixedNumberDataSet(UBYTE);
void	DisplayFixedNumberInput(void);
void	DisplayDecimalPointInput(void);
UWORD	EnterPassCode(UWORD, UBYTE, UBYTE *);
void	CharacterInputCursorRightMove(void);
void	CharacterInputCursorLeftMove(void);
void	CharacterInputDataClear(void);
void	CharacterInputDialCharSet(void);
void	DataShiftOneStep(void);
void	CharacterInputDataSet(UBYTE);
void	CharacterDataSet_FigureCheck(UBYTE);
void	CharacterInputDialMarkSet(UBYTE);
void	CursorRightRotation(void);
void	CursorLeftRotation(void);
void	ClearCharacterInput(void);
UWORD	CharacterInputToNumber(void);
void	StoreCharacterInputValue(UBYTE *, UBYTE);
UBYTE	StoreCharacterInputToSoftDip(void);
UDWORD	StoreCharacterInputToLongGroup(void);
void	StoreCharacterInputToDatabase(UWORD *);
void	StoreSoftDipToCharacterInput(UBYTE);
void	StoreGroupToCharacterInput(UDWORD);
void	SetLongTimeToCharacterInput(UDWORD, UBYTE);
void	SetSpecialTimeToCharacter(void);
UBYTE	CheckCharacterInputEmpty(void);
UBYTE	InputNumberRotation(UBYTE);
void	DisplayNumberRotation(UBYTE);
*/

/*************************************************************************
	module		:[可変長数字入力]
	function	:[
		1.数字のみで入力するもの
		2.桁数制限のみありで入力範囲は制限は特になし
		3.以下の入力に使用
		,	通信予約ファイル番号入力（予約原稿プリント）
		,	親展ボックス番号入力（親展送信）
		,	親展ボックス番号入力（親展ボックス登録・親展受信プリント）
		,	ポーリング　ファイル番号入力（ポーリング原稿蓄積）
		,	ポーリング　ファイル番号入力（ポーリング原稿消去・プリント）
		,	一括送信ボックス番号入力（一括送信原稿消去・プリント・送信）
		,	一括送信ファイル番号入力（一括送信原稿消去・プリント）
		,	一括送信ボックス番号入力（プログラムワンタッチ登録）
		,	Ｆコード　ファイル番号入力（Ｆコード蓄積原稿消去・プリント）
		,	暗号化受信原稿番号入力（暗号化受信原稿復号化）
		,	暗号化拡張キー番号入力（暗号化受信原稿復号化）
	]
	return		:[
		OK:入力完了
		NG:入力中断
	]
	common		:[CharacterInput]
	condition	:[
		未入力可能にする時（CharacterInput.IsNoInputEnable = TRUE）は、
		この関数の後、必ず CheckCharacterInputEmpty()で未入力かどうかを
		チェックしてから CharacterInputToNumber()を使用する事
		注）未条件に CharacterInputToNumber()を使用すると、未入力でも０が
		　　返ってくるため
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/20]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE NumberInput(UBYTE input_item)	/* 入力種別 */
{
	UBYTE	key;

	key = OPR_NO_KEY;	/* 前回キー入力値用に初期化します */

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
	if (input_item != OPR_NUMBER_INPUT_NO_INITIAL) {
		/* 初期値をセットする */
		NumberInputInitial(input_item);
	}
#else
	/* 初期値をセットする */
	NumberInputInitial(input_item);
#endif

	while (1) {
		/** 表示処理 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();

		/** 入力されたキーに対する処理 */
		switch (key) {
		case STOP_KEY:		/* ストップキー */
			CursorOff();
			return (NG);

		case SET_KEY:		/* セットキー */
			/*---------------------------*/
			/** 入力データをチェックする  */
			/*---------------------------*/
			/** 未入力チェック */
			if (CheckCharacterInputEmpty() == TRUE) {	/* データが未入力の時 */
				if (CharacterInput.IsNoInputEnable) {	/* 未入力可能な時 */
					CursorOff();
					return (OK);
				}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/13 by K.Okada */
				else if (input_item == OPR_USERCODE_NUMBER_INPUT) { /*ユーザコード番号の入力*/
					CursorOff();
					return (OK);
				}
#endif
				else {									/* 未入力不可能な時 */
					NackBuzzer();
					OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
				}
			}
			else {										/* データが入力済みの時 */
				/* 検査するデータをチェック用のバッファに展開する */
				SetToCheckBuffer(CharacterInput.Buffer, NULL);

				/* 数字のみの入力、桁数オーバー、入力範囲外の入力のチェックを行う */
				OPR_ChildErrorFlag = CheckNumberFigureRange(CharacterInput.MaxFigure,
															CharacterInput.MinValue,
															CharacterInput.MaxValue);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/23 by K.Okada */
#if (0)
//				if (OPR_ChildErrorFlag == OPR_NO_ERROR) {
//					if (input_item == SF_PTT_VFC_BAND_EDGE_INPUT) {
//						SetToCheckBuffer(CharacterInput.Buffer, NULL);
//						OPR_ChildErrorFlag = CheckCorrectVFC_BandEdge();
//					}
//				}
#endif
#endif
				if (OPR_ChildErrorFlag == OPR_NO_ERROR) {	/* エラーなし */
					CursorOff();
					return (OK);
				}
				else {										/* エラーあり */
					NackBuzzer();
				}
			}
			break;
		case MODE_KEY:		/* 画質キー */
		case CONTRAST_KEY:	/* 濃度キー */
			/* ポーリング蓄積の時だけは、画質・濃度を変更できる必要があります */
			if (input_item == OPR_STORE_POLLING_NUMBER_INPUT) {
				SingleKeyOperation(key);
			}
			else {
				NackBuzzer();
			}
			break;
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[数字入力初期値セット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ポーリング蓄積の時は、画質・濃度キーを有効にする必要があるが、
		ポプラでは、濃度変更がＬＣＤのために上段が書き換えられてしまうので
		CharacterInput.FixedWordingHighを追加し、上段を再表示できるように
		変更しました（ポーリング蓄積以外は、特に必要がないのでキーを受け付けません）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/31]
	author		:[江口,渡辺一章]
*************************************************************************/
void NumberInputInitial(UBYTE type)
{
	ClearCharacterInput();

	switch (type) {
	case OPR_COMMAND_NUMBER_INPUT:			/* 通信予約ファイル番号入力（予約原稿プリント） */
		CharacterInput.LcdDisplayPosition = 15;
		CharacterInput.MaxFigure = COM_DIGIT_MAX;
		CharacterInput.MaxValue = SYS_COM_FILE_MAX - 1;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputCommandNumber;		/* "ﾖﾔｸ ﾊﾞﾝｺﾞｳ:         " */
		break;
	case OPR_TX_MAIL_BOX_NUMBER_INPUT:		/* 親展ボックス番号入力（親展送信） */
	case OPR_MAIL_BOX_NUMBER_INPUT:			/* 親展ボックス番号入力（親展ボックス登録・親展受信プリント） */
		if ((type == OPR_TX_MAIL_BOX_NUMBER_INPUT)
		 && (SpecialCommandValue.CommandOption.Item == SYS_SCANNER_SECURE_TX)) {
			/* 親展送信時、既に親展ボックス番号がセットされている時は、前回登録内容をセットします */
			CMN_UnsignedIntToASC(CharacterInput.Buffer,
								 SpecialCommandValue.CommandOption.OptionNumber.SecureNumber,
								 1,
								 '0');
		}
		CharacterInput.LcdDisplayPosition = 18;
		CharacterInput.MaxFigure = 1;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputMailBoxNumber;		/* "ｼﾝﾃﾝ ﾊﾞﾝｺﾞｳ:        " */
		break;
	case OPR_STORE_POLLING_NUMBER_INPUT:	/* ポーリング　ファイル番号入力（ポーリング原稿蓄積） */
		CharacterInput.LcdDisplayPosition = 15;
		CharacterInput.MaxFigure = 2;
		CharacterInput.FixedWordingHigh = (UBYTE *)D2W_StorePollingDocument;	/* "ﾎﾟｰﾘﾝｸﾞ ｹﾞﾝｺｳ ﾁｸｾｷ  " */
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputFileNumber;			/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:        " */
		CharacterInput.IsNoInputEnable = TRUE;	/* データ未入力可能 */
		break;
	case OPR_POLLING_FILE_NUMBER_INPUT:		/* ポーリング　ファイル番号入力（ポーリング原稿消去・プリント） */
		CharacterInput.LcdDisplayPosition = 15;
		CharacterInput.MaxFigure = 2;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputFileNumber;			/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:        " */
		CharacterInput.IsNoInputEnable = TRUE;	/* データ未入力可能 */
		break;
	case OPR_BATCH_BOX_NUMBER_INPUT:		/* 一括送信ボックス番号入力（一括送信原稿消去・プリント・送信） */
	case OPR_PRG_BATCH_BOX_INPUT:			/* 一括送信ボックス番号入力（プログラムワンタッチ登録） */
		if ((type == OPR_PRG_BATCH_BOX_INPUT)
		 && (SpecialCommandValue.CommandOption.Item == SYS_BATCH_MEMORY_TX)) {
			/* 一括送信ボックス番号入力で、既に一括送信が登録されている時は、前回登録内容をセット */
			CMN_UnsignedIntToASC(CharacterInput.Buffer,
								 (UWORD)(SpecialCommandValue.CommandOption.OptionNumber.BatchNumber + 1),
								 1,
								 '0');
		}
		CharacterInput.LcdDisplayPosition = 18;
		CharacterInput.MaxFigure = 1;
		CharacterInput.MinValue = OPR_BATCH_FILE_MIN;
		CharacterInput.MaxValue = SYS_BATCH_FILE_MAX;	/* 中:0～4,外：1～5 */
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_BatchBoxNumber;			/* "ﾎﾞｯｸｽ ﾊﾞﾝｺﾞｳ     :  " */
		break;
	case OPR_BATCH_INDEX_NUMBER_INPUT:		/* 一括送信ファイル番号入力（一括送信原稿消去・プリント） */
		CharacterInput.LcdDisplayPosition = 17;
		CharacterInput.MaxFigure = 2;
		CharacterInput.MaxValue = SYS_BATCH_INDEX_MAX - 1;	/* 中:0～39,*/
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_BatchFileNumber;			/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ     :   " */
		break;
#if (PRO_F_CODE == ENABLE)
	case OPR_FCODE_BOX_DOC_NUMBER_INPUT:	/* Ｆコード　ファイル番号入力（Ｆコード蓄積原稿消去・プリント） */
		CharacterInput.LcdDisplayPosition = 17;
		CharacterInput.MaxFigure = 2;
		CharacterInput.MaxValue = SYS_SUBADDRESS_BOX_INDEX_MAX;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputFileNumber;			/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:        " */
		break;
#endif
#if (PRO_CIPHER == ENABLE)
	case OPR_CIPHER_RX_DOC_NUMBER_INPUT:	/* 暗号化受信原稿番号入力（暗号化受信原稿復号化） */
		CharacterInput.LcdDisplayPosition = 18;
		CharacterInput.MaxFigure = 1;
		CharacterInput.MaxValue = SYS_CIPHERBOX_MAX - 1;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputCipherRxDocNumber;	/* "ｼﾞｭｼﾝ ﾊﾞﾝｺﾞｳ     :  " */
		break;
	case OPR_CIPHER_EXTENSION_KEY_INPUT:	/* 暗号化拡張キー番号入力（暗号化受信原稿復号化） */
		CharacterInput.LcdDisplayPosition = 17;
		CharacterInput.MaxFigure = 2;
		CharacterInput.MaxValue = 99;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputCipherExtensionKey;	/* "ﾀﾞﾌﾞﾙｶﾞｰﾄﾞ      :   " */
		CharacterInput.IsNoInputEnable = TRUE;	/* データ未入力可能 */
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	/**************************
	** ユーザコード番号チェック
	**************************/
	case OPR_USERCODE_NUMBER_CHECK:
		CharacterInput.MaxFigure = OPR_CHARACTER_INPUT_MAX;
		break;
	/**************************
	** ユーザコード番号入力
	**************************/
	case OPR_USERCODE_NUMBER_INPUT:
		CharacterInput.MaxFigure = OPR_CHARACTER_INPUT_MAX;
		if (OPR_INF_UserData.TempCodeNumberInit[0] != NULL) {
			CMN_StringCopy(&CharacterInput.Buffer[0], &OPR_INF_UserData.TempCodeNumberInit[0]);
		}
		break;
	case OPR_MAIL_COMMAND_NUMBER_INPUT:
		CharacterInput.LcdDisplayPosition = 15;
		CharacterInput.MaxFigure = COM_DIGIT_MAX;
		CharacterInput.MaxValue = SYS_INF_MAIL_COM_MAX - 1;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputCommandNumber;		/* "ﾖﾔｸ ﾊﾞﾝｺﾞｳ:         " */
		break;
#if (0)
//	case SF_PTT_VFC_BAND_EDGE_INPUT:
//		CharacterInput.LcdDisplayPosition = 15;
//		CharacterInput.MaxFigure = UPPER_BAND_EDGE_FIGURE_MAX;
//		CharacterInput.MaxValue = UPPER_BAND_EDGE_MAX;
//		CharacterInput.MinValue = 0;
//		CharacterInput.FixedWordingLow = (UBYTE *)D2W_BandEdgeRange;			/* "[0-22(dB)]          " */
//		CMN_MemorySet(CharacterInput.Buffer, 2, '0');
//		break;
#endif
#endif
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
	case OPR_T30_MONITOR_NUMBER_INPUT:
		CharacterInput.MaxValue = SYS_JOURNAL_MAX - 1;
		CharacterInput.MaxFigure = FigureCalculation(CharacterInput.MaxValue);
		CharacterInput.LcdDisplayPosition = 19 - CharacterInput.MaxFigure;
		CharacterInput.FixedWordingLow = (UBYTE *)D2W_SF_T30MonitorNumber;		/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:        " */
		CharacterInput.IsNoInputEnable = TRUE;	/* データ未入力可能 */
		break;
#endif
	default:
		break;
	}
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
}

/*************************************************************************
	module		:[数字入力キー取り込み及び処理]
	function	:[
		1.各数字入力関数に共通する処理を実行する
		2.カーソル移動。（＜＞キー )
		3.数字データセット(0 - 9)
		4.データクリア(Clearキー)
		5.上記以外のキー入力については処理は行わず上位関数にキーコードをそのまま返す
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/08]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE NumberInputKeyGet(void)
{
	UBYTE	key;
	UBYTE	keytype;
	
	OPR_GetKey(KEY_WAIT_ONE_MINUTE);
	key = GetInputKeyCode();
	keytype = GetInputKeyType();

	switch (keytype) {
	case FUNCTION:		/* 機能／右矢印キー */
		key = OPR_NO_KEY;
		/** カーソル右移動を行う */
		CharacterInputCursorRightMove();
		break;
	case LEFT_ARROW:	/* 左矢印キー */
		key = OPR_NO_KEY;
		/** カーソル左移動を行う */
		CharacterInputCursorLeftMove();
		break;
	case CLEAR:			/* クリアキー */
		key = OPR_NO_KEY;
		/** バッファのデータを１文字消去する */
		CharacterInputDataClear();
		break;

#if defined (KEISATSU)		/* 警察FAX QAT Added by SMuratec K.W.Q 2005/12/20 */
	/* 属性入力の場合、桁数オーバーチェック */
	case PROGRAM:
		if (KeisatsuSet_OverCheck(key)) {
			NackBuzzer();
			OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
			key = OPR_NO_KEY;
		}
		break;
#endif
	case NUMBER:
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/16 */
		if (CharacterInput.CursorPosition < CharacterInput.KeisatsuPosition){
			key = OPR_NO_KEY;
/* 警察FAX DVT_ID3 Added start by SMuratec K.W.Q 2005/10/28 */
			NackBuzzer();
/* 警察FAX DVT_ID3 Added end by SMuratec K.W.Q 2005/10/28 */
			break;
		}
#endif		/* End of (defined (KEISATSU)) */

		/* ダイヤル記号入力後の数字入力の時は、ダイヤル記号後に数字をセットします */
#if defined(KEISATSU)	/* 警察FAX DVT_ID87 Modify by SMuratec 夏 2006/01/12 */
		if (DialCharacterCheck(&CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition],
							   CharacterInput.CursorPosition,
							   CharacterInput.WritePosition) == TRUE) {
			CharacterInput.CursorPosition++;
		}
#else
		if (DialCharacterCheck(&CharacterInput.Buffer[CharacterInput.CursorPosition],
							   CharacterInput.CursorPosition,
							   CharacterInput.WritePosition) == TRUE) {
			CharacterInput.CursorPosition++;
		}
#endif

#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
		/* ダイヤル記号（ポーズ・トーン）入力後の数字入力の時は、ダイヤル記号（ポーズ・トーン）後に数字をセットします */
 #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/06/21 */
 		if (DialCharacterCheck2(&CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition],
							   CharacterInput.CursorPosition,
							   CharacterInput.WritePosition) == TRUE) {
			CharacterInput.CursorPosition += 2;
 
 #else
 		if (DialCharacterCheck2(&CharacterInput.Buffer[CharacterInput.CursorPosition],
							   CharacterInput.CursorPosition,
							   CharacterInput.WritePosition) == TRUE) {
			CharacterInput.CursorPosition += 2;
 #endif		/* End of (defined (KEISATSU)) */
		}
#endif

		/** 数字の入力を行う  */
		CharacterDataSet_FigureCheck(key);
		key = OPR_NO_KEY;
		break;
	case STOP:			/* ストップキー */
	case KEY_TIME_UP:	/* １分間キー入力なし */
		key = STOP_KEY;
		break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
	case SINGLE:		/* 単一オペレーションキー */
		SingleKeyOperation(key);
		key = OPR_NO_KEY;
		break;
#endif
	case NO_EFFECT:
		key = OPR_NO_KEY;
		break;
	default:
		break;
	}
	return (key);
}

/*************************************************************************
	module		:[数字入力中の表示]
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
	date		:[1995/07/05]
	author		:[江口]
*************************************************************************/
void DisplayNumberInput(void)
{
	UBYTE	diff;
	UBYTE	over_count;
	UBYTE	disp_enable_count;
	UBYTE	cursor_disp_position;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	UBYTE	length;
#endif
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/12 for prefix *//* by K.Watanabe 2004/10/12 */
	UWORD	pos;
	UWORD	len;	/* SYB_MercuryDialBuffer の length+1*/
#endif


	diff = 0;
	over_count = 0;
	disp_enable_count = 0;
	cursor_disp_position = 0;

	if (CheckChildErrorDisplayReq() == TRUE) {	/** チャイルド表示すべきエラーが発生した */
		CursorOff();
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {	/** チャイルド表示中 */
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Mod by SMuratec C.P 2004/07/12 for prefix *//* by K.Watanabe 2004/10/12 */
	pos = 0;
	len = CMN_StringLength(SYB_MercuryDialBuffer) + 1;
	CMN_MemorySet(CharacterInput_Mercury.Buffer,OPR_CHARACTER_INPUT_MAX + 1, NULL);
	CharacterInput_Mercury.FixedWordingLow 		= CharacterInput.FixedWordingLow;
	CharacterInput_Mercury.FixedWordingHigh 	= CharacterInput.FixedWordingHigh;
	CharacterInput_Mercury.LcdDisplayPosition 	= CharacterInput.LcdDisplayPosition;
	CharacterInput_Mercury.CursorPosition 		= 0;
	CharacterInput_Mercury.DisplayStartPosition = 0;

	ChangeInputBuffer(CharacterInput_Mercury.Buffer,CharacterInput.Buffer);

	while(CharacterInput_Mercury.Buffer[pos] != NULL) {
		CharacterInput_Mercury.CursorPosition++;
		pos++;
	}
	pos = CharacterInput.WritePosition - CharacterInput.CursorPosition;
	while(pos) {
		CharacterInput_Mercury.CursorPosition--;
		if(CharacterInput_Mercury.Buffer[CharacterInput_Mercury.CursorPosition] == ']') {
			CharacterInput_Mercury.CursorPosition -= len;
		}
		pos--;
	}
	pos = 0;
	while(CharacterInput_Mercury.Buffer[pos] != NULL) {
		if (CharacterInput_Mercury.CursorPosition <= CharacterInput_Mercury.DisplayStartPosition) {
			CharacterInput_Mercury.DisplayStartPosition = CharacterInput_Mercury.CursorPosition;
			if (CharacterInput_Mercury.CursorPosition != 0) {/* カーソル位置がバッファの先頭でない */
				CharacterInput_Mercury.DisplayStartPosition--;
			}
		}
		/* カーソル位置が現在の表示開始位置よりも後ろの時　*/
		else {
			/* ２1桁以上離れている時 */
			if (CharacterInput_Mercury.CursorPosition - CharacterInput_Mercury.DisplayStartPosition >= OPR_DISPLAY_MAX) {
				CharacterInput_Mercury.DisplayStartPosition = CharacterInput_Mercury.CursorPosition - 19;
			}
		}
		pos++;
	}

	/*-------------------------------*/
	/** 下段表示文字列を作成		 */
	/*-------------------------------*/
	/** 表示できる文字数を計算する */
	disp_enable_count = (UBYTE)(OPR_DISPLAY_MAX - CharacterInput_Mercury.LcdDisplayPosition);

	/* 固定文字列があればコピー */
	if (CharacterInput_Mercury.FixedWordingLow != NULL) {
		CMN_StringCopyNumNotNULL(FunctionDisplayBufferLow,
								 CharacterInput_Mercury.FixedWordingLow,
								 CharacterInput_Mercury.LcdDisplayPosition);
	}
		/** 入力データのどの位置から表示するかを求める */
	if (CharacterInput_Mercury.DisplayStartPosition > CharacterInput_Mercury.CursorPosition) { /* 表示開始位置よりカーソル位置が前にある */
		/* カーソル位置の１つ前を先頭に２０文字分(表示可能文字数分）表示するので表示位置をカーソル位置の一つ前に持ってくる  */
		CharacterInput_Mercury.DisplayStartPosition = CharacterInput_Mercury.CursorPosition;
	}
	else if (CharacterInput_Mercury.DisplayStartPosition == CharacterInput_Mercury.CursorPosition) { /* 表示位置とカーソル位置が同じ */
		/* カーソル位置を先頭に２０文字分表示する *//* この場合カーソルはバッファの先頭にある筈 */
		;
	}
	else { /* 表示開始位置よりカーソルが後ろにある */
	/* 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）以内であれば表示位置から２０文字分表示する */
			/* 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）を越える場合はカーソル位置がＬＣＤの右端にくるように
		　 表示位置を調整する */
		diff = (UBYTE)((CharacterInput_Mercury.CursorPosition - CharacterInput_Mercury.DisplayStartPosition) + 1);
		if (diff > disp_enable_count) { /* 表示可能文字数を越える */
			over_count = diff - disp_enable_count; /* オーバーする文字数を求める */
			CharacterInput_Mercury.DisplayStartPosition += over_count; /* オーバーする文字数分表示位置をカーソル側へ移動 */
		}
	}
		/* カーソル位置と表示開始位置が同じでかつ先頭でない場合 */
	/* カーソル位置の一つ前から表示を開始する */
	if ((CharacterInput_Mercury.DisplayStartPosition == CharacterInput_Mercury.CursorPosition)
	&&	(CharacterInput_Mercury.CursorPosition != 0)) {
		CharacterInput_Mercury.DisplayStartPosition--;
	}

	/* カーソル位置を計算 */
	cursor_disp_position = CharacterInput_Mercury.CursorPosition - CharacterInput_Mercury.DisplayStartPosition;

	if((cursor_disp_position == 19) && (CharacterInput_Mercury.Buffer[CharacterInput_Mercury.CursorPosition] == '-')
		&&(CharacterInput_Mercury.Buffer[CharacterInput_Mercury.CursorPosition + 1] == '!')) {
		CharacterInput_Mercury.DisplayStartPosition++;
		cursor_disp_position = CharacterInput_Mercury.CursorPosition - CharacterInput_Mercury.DisplayStartPosition;
	}

 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/13 by K.Okada */
	if (OPR_DisplayMaskingFlag == 1) {/* 下段表示マスク要求あり */
		length = CMN_StringLength(&CharacterInput_Mercury.Buffer[CharacterInput_Mercury.DisplayStartPosition]);
		if (length > disp_enable_count) {
			length = disp_enable_count;
		}
		CMN_MemorySet(&FunctionDisplayBufferLow[CharacterInput_Mercury.LcdDisplayPosition], (UWORD)length , '*');
	}
	else {
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput_Mercury.LcdDisplayPosition],
				   	    		 &CharacterInput_Mercury.Buffer[CharacterInput_Mercury.DisplayStartPosition],
					   	     	 disp_enable_count);
	}
 #else
	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput_Mercury.LcdDisplayPosition],
							 &CharacterInput_Mercury.Buffer[CharacterInput_Mercury.DisplayStartPosition],
							 disp_enable_count);
 #endif

	/*---------------------------*/
	/** LCD表示更新				 */
	/*---------------------------*/
	if (CharacterInput_Mercury.FixedWordingHigh != NULL) {
		DisplayStringHigh(0, CharacterInput_Mercury.FixedWordingHigh);
	}
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor_disp_position + CharacterInput_Mercury.LcdDisplayPosition));

	/*-------------------------------*/
	/** 下段表示文字列を作成		 */
	/*-------------------------------*/
	/** 表示できる文字数を計算する */
	disp_enable_count = (UBYTE)(OPR_DISPLAY_MAX - CharacterInput.LcdDisplayPosition);
		/** 入力データのどの位置から表示するかを求める */
	if (CharacterInput.DisplayStartPosition > CharacterInput.CursorPosition) { /* 表示開始位置よりカーソル位置が前にある */
		/* カーソル位置の１つ前を先頭に２０文字分(表示可能文字数分）表示するので表示位置をカーソル位置の一つ前に持ってくる  */
		CharacterInput.DisplayStartPosition = CharacterInput.CursorPosition;
	}
	else if (CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition) { /* 表示位置とカーソル位置が同じ */
		/* カーソル位置を先頭に２０文字分表示する *//* この場合カーソルはバッファの先頭にある筈 */
		;
	}
	else { /* 表示開始位置よりカーソルが後ろにある */
		/* 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）以内であれば表示位置から２０文字分表示する */
		/* 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）を越える場合はカーソル位置がＬＣＤの右端にくるように
		　 表示位置を調整する */
		diff = (UBYTE)((CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition) + 1);
		if (diff > disp_enable_count) { /* 表示可能文字数を越える */
			over_count = diff - disp_enable_count; /* オーバーする文字数を求める */
			CharacterInput.DisplayStartPosition += over_count; /* オーバーする文字数分表示位置をカーソル側へ移動 */
		}
	}
		/* カーソル位置と表示開始位置が同じでかつ先頭でない場合 */
	/* カーソル位置の一つ前から表示を開始する */
	if ((CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition)
	&&	(CharacterInput.CursorPosition != 0)) {
		CharacterInput.DisplayStartPosition--;
	}

#else /* define(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
	/*-------------------------------*/
	/** 下段表示文字列を作成		 */
	/*-------------------------------*/
	/** 表示できる文字数を計算する */
	disp_enable_count = (UBYTE)(OPR_DISPLAY_MAX - CharacterInput.LcdDisplayPosition);

	/* 固定文字列があればコピー */
	if (CharacterInput.FixedWordingLow != NULL) {
		CMN_StringCopyNumNotNULL(FunctionDisplayBufferLow,
								 CharacterInput.FixedWordingLow,
								 CharacterInput.LcdDisplayPosition);
	}

	/** 入力データのどの位置から表示するかを求める */
	if (CharacterInput.DisplayStartPosition > CharacterInput.CursorPosition) { /* 表示開始位置よりカーソル位置が前にある */
		/* カーソル位置の１つ前を先頭に２０文字分(表示可能文字数分）表示するので表示位置をカーソル位置の一つ前に持ってくる  */
		CharacterInput.DisplayStartPosition = CharacterInput.CursorPosition;
	}
	else if (CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition) { /* 表示位置とカーソル位置が同じ */
		/* カーソル位置を先頭に２０文字分表示する *//* この場合カーソルはバッファの先頭にある筈 */
		;
	}
	else { /* 表示開始位置よりカーソルが後ろにある */
		/* 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）以内であれば表示位置から２０文字分表示する */
		/* 表示開始位置とカーソル位置までの差が２０文字(表示可能文字数分）を越える場合はカーソル位置がＬＣＤの右端にくるように
		　 表示位置を調整する */
		diff = (UBYTE)((CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition) + 1);
		if (diff > disp_enable_count) { /* 表示可能文字数を越える */
			over_count = diff - disp_enable_count; /* オーバーする文字数を求める */
			CharacterInput.DisplayStartPosition += over_count; /* オーバーする文字数分表示位置をカーソル側へ移動 */
		}
	}

	/* カーソル位置と表示開始位置が同じでかつ先頭でない場合 */
	/* カーソル位置の一つ前から表示を開始する */
	if ((CharacterInput.DisplayStartPosition == CharacterInput.CursorPosition)
	&&	(CharacterInput.CursorPosition != 0)) {
		CharacterInput.DisplayStartPosition--;
	}
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/13 by K.Okada */
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
 
  #if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/06/21 */
     if (CharacterInput.DisplayStartPosition >= CharacterInput.KeisatsuPosition){
	  	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition],
								 &CharacterInput.Buffer[CharacterInput.DisplayStartPosition - CharacterInput.KeisatsuPosition],
								 disp_enable_count);
	}
	else{
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition],
								 &CharacterInput.KeisatsuBuf[CharacterInput.DisplayStartPosition],
								 CharacterInput.KeisatsuPosition - CharacterInput.DisplayStartPosition);
	  	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition + (CharacterInput.KeisatsuPosition  - CharacterInput.DisplayStartPosition)],
								 &CharacterInput.Buffer[0],
								 disp_enable_count - (CharacterInput.KeisatsuPosition - CharacterInput.DisplayStartPosition));
	}
  #else
  	CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition],
							 &CharacterInput.Buffer[CharacterInput.DisplayStartPosition],
							 disp_enable_count);
  #endif
 #endif

	/* カーソル位置を計算 */
	cursor_disp_position = CharacterInput.CursorPosition - CharacterInput.DisplayStartPosition;

	/*---------------------------*/
	/** LCD表示更新				 */
	/*---------------------------*/
	if (CharacterInput.FixedWordingHigh != NULL) {
		DisplayStringHigh(0, CharacterInput.FixedWordingHigh);
	}
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor_disp_position + CharacterInput.LcdDisplayPosition));
#endif /* defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE) */
}

/*************************************************************************
	module		:[固定長数字入力（未入力不可能）]
	function	:[
		1.入力桁数が固定である数字の入力を行う。
		，以下のようなもの
		, 桁数オーバーはない。全て上書き入力。（パスワードなど)
		2.引数の説明
		, 第１引数：UWORD store_data		:既に登録されているデータ
		, 第２引数：UWORD min_value 		:入力可能最小値.チェックする必要が無い場合０をセット
		, 第３引数：UWORD max_value 		:入力可能最大値,チェックする必要が無い場合０をセット
		, 第４引数：UBYTE display_position	:入力データ表示開始位置(LCD下段のどの位置から入力データを表示するか)
		, 第５引数：UBYTE *item_wording		:下段表示用固定文字列,無い場合はＮＵＬＬをセット
	]
	return		:[
		入力数値
			FFFF:は登録中止とする。
	]
	common		:[
		CharacterInput
	]
	condition	:[
		入力範囲の最大値が0xFFFFにならないことを前提にしている
		入力範囲が０～９９９９に収まるものの、入力にしかこの関数は使用できない
	]
	comment		:[
		(注意)第３引数:max_value に０をセットすると１桁のみの入力になります。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/18]
	author		:[江口,渡辺一章]
*************************************************************************/
UWORD FixedLengthNumberInput(UWORD stored_data,
							 UWORD min_value,
							 UWORD max_value,
							 UBYTE display_position,
							 UBYTE *item_wording)
{
	UBYTE	key;			/* キー入力		  */
	UBYTE	keytype;		/* キー入力		  */
	UBYTE	length; 		/* 桁数 		  */
	UBYTE	no_check;		/* 1:入力チェック不要 0:入力チェック必要 */
	UWORD	input_value;	/* 入力された数値 */

	no_check = FALSE;

	/* ワークエリア初期化 */
	ClearCharacterInput();
	length = FigureCalculation(max_value);
	CharacterInput.WritePosition = (UBYTE)(length - 1); /* 1234の4の所 */
	CharacterInput.LcdDisplayPosition = display_position;
	CharacterInput.FixedWordingLow = item_wording;

	if (stored_data != 0xFFFF) {
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], stored_data, length, '0');
	}
	else {
		CMN_MemorySet(&CharacterInput.Buffer[0], length , '*');
	}

	if (max_value == 0 && min_value == 0) {	/* 入力チェックは必要ない場合 */
		no_check = TRUE;
	}

	/* 入力処理 */
	while (1) {

		/** 下段表示 */
		DisplayFixedNumberInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理 */
		switch (keytype) {
		case STOP:			/** ストップキー */
		case KEY_TIME_UP:	/** １分間キー入力なし */
			/** 終了 */
			CursorOff();
			return (0xFFFF);
		case ENTER:			/** セットキー */
			/* 入力された文字列形式のデータをINT型に変換 */
			input_value = CharacterInputToNumber();
			if (no_check == TRUE) {	/* 入力チェックがいらん場合 */
				CursorOff();
				return (input_value);
			}
			else if ((input_value >= min_value) && (input_value <= max_value)) {	/* 入力範囲内に収まっている */
				CursorOff();
				return (input_value);
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:		/** 数字キー */
			FixedNumberDataSet(key);
			break;
		case FUNCTION:		/** ＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 	/** ＜キー */
			CursorLeftRotation();
			break;
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
	module		:[固定長数字入力（未入力可能）]
	function	:[
		1.入力桁数が固定である数字の入力を行う。
		  以下のようなもの
		  ,桁数オーバーはない。全て上書き。
		  ,クリアーキーでクリアーできる。
		  ,未入力可能。
		2.引数の説明
		, 第１引数：UBYTE store_data		:既に登録されているデータ,未登録の場合は0xFFをセット
		, 第２引数：UBYTE max_figure 		:入力可能最大桁数(1～2桁)
		, 第３引数：UBYTE min_value 		:入力可能最小値,チェックする必要が無い場合 0をセット
		, 第４引数：UBYTE max_value 		:入力可能最大値,チェックする必要が無い場合 0をセット
		, 第５引数：UBYTE display_position	:入力データ表示開始位置(LCD下段のどの位置から入力データを表示するか)
		, 第６引数：UBYTE *item_wording		:下段表示用固定文字列,無い場合はＮＵＬＬをセット
	]
	return		:[
		入力数値(0～99)
		OPR_NUMBER_INPUT_STOP :登録中止
		OPR_NUMBER_NO_STORED  :未登録
	]
	common		:[
		CharacterInput
	]
	condition	:[
		入力範囲の最大値が0xFFにならないことを前提にしている
		入力範囲が０～９９に収まるものの、入力にしかこの関数は使用できない
	]
	comment		:[
		FixedLengthNumberInput()との違いは、
		・クリアーキーが有効であること。
		・桁数に関係なく未入力が可能であること。(FixedLengthNumberInput()は1桁のときのみ未入力が可能)
		・入力範囲が０～９９であること。(FixedLengthNumberInput()は０～９９９９)

		注）第一引数をUWORDにすると、UBYTEで定義されている未登録のデータ(0xFF)を引数にするときの処理が
		　　ややこしいので、この関数ではUBYTEのデータのみ扱います。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/12/17]
	author		:[福本貴吉]
*************************************************************************/
UBYTE FixedLengthNumberInput2(UBYTE stored_data,
							  UBYTE max_figure,
							  UBYTE min_value,
							  UBYTE max_value,
							  UBYTE display_position,
							  UBYTE *item_wording)
{
	UBYTE	key;				/* キー入力		  */
	UBYTE	keytype;			/* キー入力		  */
	UBYTE	length;				/* 桁 */
	UBYTE	is_need_inp_chk;	/* FALSE:入力チェック不要 TRUE:入力チェック必要 */
	UBYTE	input_value;		/* 入力された数値 */

	is_need_inp_chk = TRUE;
	if (max_value == 0 && min_value == 0) {	/* 入力チェックは必要ない場合 */
		is_need_inp_chk = FALSE;
	}

	ClearCharacterInput();								/* ワークエリア初期化       */
	CharacterInput.MaxFigure = max_figure;					/* 入力可能最大桁       */
	CharacterInput.MinValue = (UWORD)min_value;				/* 入力可能最小値       */
	CharacterInput.MaxValue = (UWORD)max_value;				/* 入力可能最大値       */
	CharacterInput.LcdDisplayPosition = display_position;	/* ＬＣＤ上表示開始位置 */
	CharacterInput.FixedWordingLow = item_wording;			/* 下段表示固定文字列   */
	CharacterInput.IsNoInputEnable = TRUE;					/* 未入力可能か         */

	/* 入力データ・入力最後尾のセット*/
	if (stored_data != 0xFF) {
		length = FigureCalculation((UWORD)stored_data);
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], (UWORD)stored_data, length, '0');
		if (length >= CharacterInput.MaxFigure) {
			CharacterInput.WritePosition = (UBYTE)(length - 1);	/* 12の2の位置 */
		}
		else {
			CharacterInput.WritePosition = (UBYTE)length;		/* 1_の_の位置 */
		}
	}
	else {
		CharacterInput.WritePosition = 0;						/* _の_の位置 */
	}
	CharacterInput.CursorPosition = CharacterInput.WritePosition;	/* 入力位置のセット */

	/* 入力処理 */
	while (1) {

		/** 下段表示 */
		DisplayFixedNumberInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理 */
		switch (keytype) {
		case STOP:			/** ストップキー */
		case KEY_TIME_UP:	/** １分間キー入力なし */
			/** 終了 */
			CursorOff();
			return (OPR_NUMBER_INPUT_STOP);
		case CLEAR:
			if (CheckCharacterInputEmpty() == TRUE) {
				NackBuzzer();
			}
			else {
				/* バッファをすべてクリアーする */
				CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
				CharacterInput.WritePosition  = 0;
				CharacterInput.CursorPosition = 0;
			}
			break;
		case ENTER:			/** セットキー */
			if (CheckCharacterInputEmpty() == TRUE) {	/* 未登録 */
				CursorOff();
				return (OPR_NUMBER_NO_STORED);
			}
			input_value = (UBYTE)CharacterInputToNumber();	/* 入力された文字列形式のデータをINT型に変換 */
			if (is_need_inp_chk) {	/* 入力範囲のチェックを行う */
				if ((input_value >= min_value) && (input_value <= max_value)) {
					CursorOff();
					return (input_value);
				}
				else {
					NackBuzzer();
				}
			}
			else {					/* 入力範囲のチェックを行わない */
				CursorOff();
				return (input_value);
			}
			break;
		case NUMBER:		/** 数字キー */
			CharacterInput.Buffer[CharacterInput.CursorPosition] = key;
			/* 入力最後尾の更新 */
			if ((CharacterInput.WritePosition == CharacterInput.CursorPosition)
			 && (CharacterInput.WritePosition < (UBYTE)(CharacterInput.MaxFigure - 1))) {
				CharacterInput.WritePosition++;
			}
			/* カーソル位置の更新 */
			if (CharacterInput.CursorPosition == (UBYTE)(CharacterInput.MaxFigure -1)) {
				CharacterInput.CursorPosition = 0;	/* カーソル位置を頭に戻す */
			}
			else {
				CharacterInput.CursorPosition++;	/* １つ進める */
			}
			break;
		case FUNCTION:		/** ＞キー */
			if (CharacterInput.MaxFigure <= 1) {	/* １桁のときは移動できない */
				NackBuzzer();
			}
			else {
				CursorRightRotation();
			}
			break;
		case LEFT_ARROW: 	/** ＜キー */
			if (CharacterInput.MaxFigure <= 1) {	/* １桁のときは移動できない */
				NackBuzzer();
			}
			else {
				CursorLeftRotation();
			}
			break;
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
	module		:[小数点数型固定長数字の入力]
	function	:[
		1.入力桁数が固定であり小数点を含む数字の入力を行う。(整数2桁、小数1桁に固定 "XX.X")
		  小数点は CharacterInput.Buffer にはセットしないため、
		  入力されたデータは CharacterInput.Buffer に×１０した値でセットします。
		  小数点は表示用の関数DisplyaDecimalPoint()で扱います。
		  以下のようなもの
		, 桁数オーバーはない。全て上書き入力。
		2.引数の説明
		, 第１引数：UWORD store_data			:既に登録されているデータ
		, 第２引数：UWORD min_value 			:入力可能最小値×１０,チェックする必要が無い場合０をセット
		, 第３引数：UWORD max_value 			:入力可能最大値×１０,チェックする必要が無い場合０をセット
		, 第４引数：UBYTE display_position		:入力データ表示開始位置(LCD下段のどの位置から入力データを表示するか)
		, 第５引数：UBYTE *item_wording			:下段表示用固定文字列,無い場合はＮＵＬＬをセット
		, 第６引数：UBYTE is_under_half_only	:TRUE ;小数点以降の入力は０と５のみ有効
												 FALSE;小数点以降の入力は０～９まで有効
	]
	return		:[
		入力数値×１０
			FFFF:は登録中止とする。
	]
	common		:[
		CharacterInput
	]
	condition	:[
		入力範囲の最大値が0xFFFFにならないことを前提にしている
		入力範囲が０～９９.９に収まるものの、入力にしかこの関数は使用できない
	]
	comment		:[
		この関数はスクランブルのサービスラベル位置入力のインチ入力(ＵＳＡ仕様)用に作成しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/12/12]
	author		:[福本貴吉]
*************************************************************************/
UWORD DecimalPointInput(UWORD stored_data,
						UWORD min_value,
						UWORD max_value,
						UBYTE display_position,
						UBYTE *item_wording,
						UBYTE is_under_half_only)
{
	UBYTE	key;				/* キー入力		  */
	UBYTE	keytype;			/* キー入力		  */
	UBYTE	length; 			/* 桁数 		  */
	UBYTE	is_need_inp_chk;	/* FALSE:入力チェック不要 TRUE:入力チェック必要 */
	UWORD	input_value;		/* 入力された数値 */

	is_need_inp_chk = TRUE;
	if (max_value == 0 && min_value == 0) {	/* 入力チェックは必要ない場合 */
		is_need_inp_chk = FALSE;
	}
	if (max_value == 0) {
		if (is_under_half_only) {
			max_value = 995;
		}
		else {
			max_value = 999;
		}
	}

	/* ワークエリア初期化 */
	ClearCharacterInput();
	length = 3;	/* 固定 */
	CharacterInput.WritePosition = (UBYTE)(length - 1); /* 12.3の3の所 */
	CharacterInput.LcdDisplayPosition = display_position;
	CharacterInput.FixedWordingLow = item_wording;

	if (stored_data != 0xFFFF) {
		CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], stored_data, length, '0');
	}
	else {
		CMN_MemorySet(&CharacterInput.Buffer[0], length , '*');
	}

	/* 入力処理 */
	while (1) {
		/* 下段表示
		** 小数点は固定された位置に表示する。
		** 整数2桁、小数1桁(XX.X)
		*/
		DisplayDecimalPointInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理 */
		switch (keytype) {
		case STOP:			/** ストップキー */
		case KEY_TIME_UP:	/** １分間キー入力なし */
			/** 終了 */
			CursorOff();
			return (0xFFFF);
		case ENTER:			/** セットキー */
			input_value = CharacterInputToNumber();	/* 入力された文字列形式のデータをINT型に変換 */
			if (is_need_inp_chk) {	/* 入力範囲のチェックを行う */
				if ((input_value >= min_value) && (input_value <= max_value)) {
					CursorOff();
					return (input_value);
				}
				else {
					NackBuzzer();
				}
			}
			else {					/* 入力範囲のチェックを行わない */
				CursorOff();
				return (input_value);
			}
			break;
		case AST:		/** ＊キー(現在の入力値を指定値分減算させた値をセット) */
			/* 入力された文字列形式のデータをINT型に変換 */
			input_value = CharacterInputToNumber();
			if ((input_value <= min_value)		/* 現在の値が最小値以下のとき最大値をセットする */
			 || (input_value > max_value)) {	/* 現在の値が最大値より大きいとき最大値をセットする */
				input_value = max_value;
			}
			else if (is_under_half_only) {	/* ５減算 */
				input_value -= 5;
			}
			else {									/* １減算 */
				input_value -= 1;
			}
			/* 更新データをバッファにセット */
			CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], input_value, length, '0');
			break;
		case SHARP:		/** ＃キー(現在の入力値を指定値分加算させた値をセット) */
			/* 入力された文字列形式のデータをINT型に変換 */
			input_value = CharacterInputToNumber();
			if ((input_value >= max_value)		/* 現在の値が最大値以上のとき最小値をセットする */
			 || (input_value < min_value)) {	/* 現在の値が最小値より小さいとき最小値をセットする */
				input_value = min_value;
			}
			else if (is_under_half_only) {	/* ５加算 */
				input_value += 5;
			}
			else {									/* １加算 */
				input_value += 1;
			}
			/* 更新データをバッファにセット */
			CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], input_value, length, '0');
			break;
		case NUMBER:		/** 数字キー */
			/* 小数点以降の入力が０か５しか受け付けない場合 */
			if ((is_under_half_only) && (CharacterInput.WritePosition == CharacterInput.CursorPosition)) {
				if ((key != TEN_0_KEY) && (key != TEN_5_KEY)) {
					NackBuzzer();
					break;
				}
			}
			/* 小数点は CharacterInput.Buffer にはセットしないため
			** 入力されたデータは CharacterInput.Buffer には×１０した値でセットされます。
			*/
			FixedNumberDataSet(key);
			break;
		case FUNCTION:		/** ＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 	/** ＜キー */
			CursorLeftRotation();
			break;
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
	module		:[固定長数字入力表示]
	function	:[
		1.ＬＣＤ下段に入力状況を表示する
	]
	return		:[]
	common		:[FunctionDisplayBufferLow]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口]
*************************************************************************/
void DisplayFixedNumberInput(void)
{
	if (CheckChildErrorDisplayReq() == TRUE) {	/** チャイルド表示すべきエラーが発生した */
		CursorOff();
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {	/** チャイルド表示中 */
		return;
	}
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(&FunctionDisplayBufferLow[0], CharacterInput.FixedWordingLow);
	CMN_StringCopy(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition], CharacterInput.Buffer);

	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));
}

/*************************************************************************
	module		:[小数点数型固定長数字の入力表示]
	function	:[
		1.ＬＣＤ下段に入力状況を表示する
		2.小数点の表示を行う。
	]
	return		:[]
	common		:[FunctionDisplayBufferLow]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/12]
	author		:[福本貴吉]
*************************************************************************/
void DisplayDecimalPointInput(void)
{
	if (CheckChildErrorDisplayReq() == TRUE) {	/** チャイルド表示すべきエラーが発生した */
		CursorOff();
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {	/** チャイルド表示中 */
		return;
	}

	/* 整数2桁、小数1桁に固定します。(XX.X)
	** 入力されたデータは CharacterInput.Buffer に×１０した値でセットされているため
	** 表示用バッファには以下のように展開します。
	*/
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(&FunctionDisplayBufferLow[0], CharacterInput.FixedWordingLow);
	FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition]     = CharacterInput.Buffer[0];
	FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition + 1] = CharacterInput.Buffer[1];
	FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition + 2] = '.';
	FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition + 3] = CharacterInput.Buffer[2];
	DisplayStringLow(0, FunctionDisplayBufferLow);

	/* カーソルの位置が小数点にこないように調整 */
	if (FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition] == '.' ) {
		CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + 1 + OPR_LCD_LOWER_ADD));
	}
	else {
		CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));
	}
}

/*************************************************************************
	module		:[パスコードの入力]
	function	:[
		1.親展ボックスパスコード/プロテクトパスコードの入力を行う.
		2.パスコードチェック時のパスコード入力の場合、初期表示は「****」とし
		　４桁数字が入力されない限りおわらない。
		3.新しいパスコードの入力の場合、初期表示として前回登録値を表示する.(新規の場合0000 )
	]
	return		:[
		入力されたパスコード。
		FFFFは登録中止を表す。
	]
	common		:[]
	condition	:[パスコードは４桁を前提
				  モードキーなどの単一キーは無効]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/29]
	author		:[江口､渡辺一章]
*************************************************************************/
UWORD EnterPassCode(UWORD passcode,		/* 登録済みデータ */
					UBYTE mode,			/* 登録モード :新規／確認 */
					UBYTE *wording)		/* 下段固定ワーディング  */
{
	UBYTE	i;
	UBYTE	key;
	UBYTE	keytype;
	UWORD	input_passcode;

	input_passcode = 0;

	ClearCharacterInput();
	CharacterInput.WritePosition = SYS_PASSCODE_MAX - 1;
	CharacterInput.LcdDisplayPosition = 16;

	/* 下段初期表示データセット */
	switch (mode) {
	case CHK_PASS_CODE_ENTER:		/* 暗証番号の確認用入力			*/
		/* 初期表示データは＊＊＊＊とする [Old Passcode:  ****] */
		CMN_MemorySet(CharacterInput.Buffer, SYS_PASSCODE_MAX, '*');
		break;
	case PASS_CODE_ENTER_ZERO_OK:	/* 新規登録（"0000"登録可能）	*/
	case PASS_CODE_ENTER_ZERO_NG:	/* 新規登録（"0000"登録不可能）	*/
		/* 既に登録されているデータを編集 [New Passcode:   1234] */
		CMN_UnsignedIntToASC(CharacterInput.Buffer, passcode, SYS_PASSCODE_MAX, '0');
		break;
	default:
		break;
	}
	CharacterInput.FixedWordingLow = wording;

	while (1) {
		/** 下段表示処理 */
		DisplayFixedNumberInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:		/* 数字キー */
			FixedNumberDataSet(key);
			break;
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			CursorOff();
			return (0xFFFF);
		case FUNCTION:		/* カーソル→キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 	/* カーソル←キー */
			CursorLeftRotation();
			break;
		case ENTER:			/* セットキー */
			for (i = 0; i < SYS_PASSCODE_MAX; i++) {	/* '*'がのこっていないかチェック */
				if (CharacterInput.Buffer[i] == '*') {
					break;
				}
			}
			if (i == SYS_PASSCODE_MAX) {
				input_passcode = CMN_ASC_ToUnsignedInt(CharacterInput.Buffer, SYS_PASSCODE_MAX);

				/* "0000"入力された場合は、許可されているかのチェックをします
				** 注）暗証番号の確認用入力時は無条件で許可します → 元のデータと比較するので無意味なため
				*/
				if ((input_passcode == 0) && (mode == PASS_CODE_ENTER_ZERO_NG)) {
					NackBuzzer();
				}
				else {
					CursorOff();
					return(input_passcode);
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[パスコードの入力（プロテクトパスコード用）]
	function	:[
		1.プロテクトパスコードの入力を行う.
		2.パスコードチェック時のパスコード入力の場合、初期表示は「****」とし
		　４桁数字が入力されない限りおわらない。
		3.新しいパスコードの入力の場合、初期表示として前回登録値を表示する.(新規の場合0000 )
		4.４桁数字が入力されたら、セットキーを押さずに終了。
	]
	return		:[
		入力されたパスコード。
		FFFFは登録中止を表す。
	]
	common		:[]
	condition	:[パスコードは４桁を前提
				  モードキーなどの単一キーは無効]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/05]
	author		:[桑原]
*************************************************************************/
UWORD EnterPassCodeProtect(
					UBYTE *wording)		/* 下段固定ワーディング  */
{
	UBYTE	i;
	UBYTE	key;
	UBYTE	keytype;
	UWORD	input_passcode;

	input_passcode = 0;

	ClearCharacterInput();
	CharacterInput.WritePosition = SYS_PASSCODE_MAX - 1;
	CharacterInput.LcdDisplayPosition = 16;

	/* 下段初期表示データセット */
	CMN_MemorySet(CharacterInput.Buffer, SYS_PASSCODE_MAX, '*');
	CharacterInput.FixedWordingLow = wording;

	while (1) {
		/** 下段表示処理 */
		DisplayFixedNumberInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:		/* 数字キー */
			FixedNumberDataSet(key);
			for (i = 0; i < SYS_PASSCODE_MAX; i++) {	/* '*'がのこっていないかチェック */
				if (CharacterInput.Buffer[i] == '*') {
					break;
				}
			}
			if (i == SYS_PASSCODE_MAX) {
				input_passcode = CMN_ASC_ToUnsignedInt(CharacterInput.Buffer, SYS_PASSCODE_MAX);
				CursorOff();
				return(input_passcode);
			}
			break;
		case CLEAR:			/** クリアキー */
			CMN_MemorySet(CharacterInput.Buffer, 4 , '*');
			CharacterInput.CursorPosition = 0;
			break;
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			CursorOff();
			return (0xFFFF);
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/* CharacterInput.Bufferに関する汎用操作 */
/*************************************************************************
	module		:[カーソル右移動]
	function	:[
		1.カーソルを１文字分右にシフトする。
		2.右端まできたらそれ以上進まない.
	]
	return		:[]
	common		:[
				CharacterInput.CursorPosition
				]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/21]
	author		:[江口,渡辺一章]
*************************************************************************/
#if defined(KEISATSU)	/* 警察FAX DVT_ID87 Modify by SMuratec 夏 2006/01/12 */
void CharacterInputCursorRightMove(void)
{
	if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* カーソルが入力後端位置にある */
		NackBuzzer();
	}
	else {
		if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '/')) {	/* ダイヤル記号（ポーズ） */
			/* "-/ "のような時、カーソルを右移動させると"-/ "となる */
			/*  ~                                          ~        */
			CharacterInput.CursorPosition++;
		}
		if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '!')) {	/* ダイヤル記号（トーン） */
			/* "-! "のような時、カーソルを右移動させると"-! "となる */
			/*  ~                                          ~        */
			CharacterInput.CursorPosition++;
		}
		CharacterInput.CursorPosition++;
	}
}

#else

void CharacterInputCursorRightMove(void)
{
	if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/* カーソルが入力後端位置にある */
		NackBuzzer();
	}
	else {
#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
		if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '/')) {	/* ダイヤル記号（ポーズ） */
			/* "-/ "のような時、カーソルを右移動させると"-/ "となる */
			/*  ~                                          ~        */
			CharacterInput.CursorPosition++;
		}
		if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!')) {	/* ダイヤル記号（トーン） */
			/* "-! "のような時、カーソルを右移動させると"-! "となる */
			/*  ~                                          ~        */
			CharacterInput.CursorPosition++;
		}
#endif
#if (PRO_JIS_CODE == ENABLE)
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] == OPR_KANJI_CODE_MARK_LEFT) {
			/* "(1234) "のような時、カーソルを右移動させると"(1234) "となる */
			/*  ~                                                  ~        */
			CharacterInput.CursorPosition += OPR_KANJI_CODE_LEN;
		}
		else {
			CharacterInput.CursorPosition++;
		}
#else
		CharacterInput.CursorPosition++;
#endif
	}
}
#endif
/*************************************************************************
	module		:[カーソル左移動]
	function	:[
		1.カーソルを１文字分左にシフトする。
		2.先頭まできたらそれ以上すすまない.
	]
	return		:[]
	common		:[CharacterInput.CursorPosition]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/21]
	author		:[江口,渡辺一章]
*************************************************************************/
#if defined(KEISATSU)	/* 警察FAX DVT_ID87 Modify by SMuratec 夏 2006/01/12 */
void CharacterInputCursorLeftMove(void)
{
	if (CharacterInput.CursorPosition == 0) {	/* カーソルが先頭にある */
		NackBuzzer();
	}
	else {
		CharacterInput.CursorPosition--;
		if ((CharacterInput.CursorPosition > 0)
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition - 1] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '/')) {	/* ダイヤル記号（ポーズ） */
			/* "-/ "のような時、カーソルを左移動させると"-/ "となる */
			/*    ~                                      ~          */
			CharacterInput.CursorPosition--;
		}
		if ((CharacterInput.CursorPosition > 0)
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition - 1] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '!')) {	/* ダイヤル記号（トーン） */
			/* "-! "のような時、カーソルを左移動させると"-! "となる */
			/*    ~                                      ~          */
			CharacterInput.CursorPosition--;
		}
	}
}
#else

void CharacterInputCursorLeftMove(void)
{
	if (CharacterInput.CursorPosition == 0) {	/* カーソルが先頭にある */
		NackBuzzer();
	}
	else {
#if (PRO_JIS_CODE == ENABLE)
		if (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == OPR_KANJI_CODE_MARK_RIGHT) {
			/* "(1234) "のような時、カーソルを左移動させると"(1234) "となる */
			/*        ~                                      ~              */
			CharacterInput.CursorPosition -= OPR_KANJI_CODE_LEN;
		}
		else {
			CharacterInput.CursorPosition--;
		}
#else
		CharacterInput.CursorPosition--;
#endif
#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
		if ((CharacterInput.CursorPosition > 0)
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition] == '/')) {	/* ダイヤル記号（ポーズ） */
			/* "-/ "のような時、カーソルを左移動させると"-/ "となる */
			/*    ~                                      ~          */
			CharacterInput.CursorPosition--;
		}
		if ((CharacterInput.CursorPosition > 0)
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition] == '!')) {	/* ダイヤル記号（トーン） */
			/* "-! "のような時、カーソルを左移動させると"-! "となる */
			/*    ~                                      ~          */
			CharacterInput.CursorPosition--;
		}
#endif
	}
}
#endif

/************************************************************************
	module		:[数字入力中のクリアオペレーション]
	function	:[
		1.カーソル位置が入力最後尾の場合、カーソル前を１文字クリア
		2.カーソル位置が入力バッファの途中の場合、カーソル上の文字を１文字クリア
		3.クリアはＮＵＬＬをセットすることで実現する
	]
	return		:[]
	common		:[CharacterInput]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/21]
	author		:[江口]
************************************************************************/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/06/21 */
void CharacterInputDataClear(void)
{
	UBYTE	kei_pos;
	UBYTE	i;
	
	kei_pos	= 0;
	i		= 0;
	
	if (CheckCharacterInputEmpty() == TRUE) {	/* バッファが空 */
		NackBuzzer();
	}
	else {
		
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/22 */
		if (CharacterInput.CursorPosition == CharacterInput.WritePosition
			&& CharacterInput.CursorPosition == CharacterInput.KeisatsuPosition){
			
			kei_pos++;

			while (1){
				switch (i){
				case 0:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
					
							UpdateKeisatsuBuf();
							return;
						}

						kei_pos++;
					}
					break;
				case 1:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
							
							UpdateKeisatsuBuf();
							
							return;
						}
						
						kei_pos++;
					}
					
					break;
				case 2:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
							
							UpdateKeisatsuBuf();
							
							return;
						}
						
						kei_pos++;
					}
					
					break;
				case 3:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
							
							UpdateKeisatsuBuf();
							
							return;
						}
						
						kei_pos++;
					}
					
					break;
				}
			
				i++;
			}			
		}
		else if (CharacterInput.CursorPosition < CharacterInput.KeisatsuPosition){
			while (1){
				switch (i){
				case 0:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
					
							UpdateKeisatsuBuf();
							return;
						}

						kei_pos++;
					}
					break;
				case 1:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
							
							UpdateKeisatsuBuf();
							
							return;
						}
						
						kei_pos++;
					}
					
					break;
				case 2:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
							
							UpdateKeisatsuBuf();
							
							return;
						}
						
						kei_pos++;
					}
					
					break;
				case 3:
					if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO))){
						if (kei_pos == CharacterInput.CursorPosition){
							CharacterInput.Keisatsu &= ~(SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO);

							if (CharacterInput.CursorPosition >= CharacterInput.WritePosition){
								CharacterInput.CursorPosition--;
							}
							CharacterInput.WritePosition--;
							
							UpdateKeisatsuBuf();
							
							return;
						}
						
						kei_pos++;
					}
					
					break;
				}
			
				i++;
			}
		}

#endif		/* End of (defined (KEISATSU)) */

#if 0	/* 警察FAX DVT_ID87 Modify by SMuratec 夏 2006/01/12 */
		if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) { /* この場合カーソル位置が入力最後尾にある */
			/*---------------------------*/
			/** カーソル前の１文字を消去 */
			/*---------------------------*/
#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
			if ((CharacterInput.CursorPosition > 1)
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 2] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == '/')) {	/* ダイヤル記号（ポーズ） */
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = NULL;
			}
			if ((CharacterInput.CursorPosition > 1)
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 2] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == '!')) {	/* ダイヤル記号（トーン） */
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = NULL;
			}
#endif
#if (PRO_JIS_CODE == ENABLE)
			if (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == OPR_KANJI_CODE_MARK_RIGHT) {
				CharacterInput.WritePosition -= OPR_KANJI_CODE_LEN;
				CharacterInput.CursorPosition -= OPR_KANJI_CODE_LEN;
				CMN_MemorySet(&CharacterInput.Buffer[CharacterInput.WritePosition], OPR_KANJI_CODE_LEN, NULL);
			}
			else {
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
			}
#else
			CharacterInput.WritePosition--;
			CharacterInput.CursorPosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
#endif
		}
		else {
			/*---------------------------*/
			/** カーソル上の１文字を消去 */
			/*---------------------------*/
#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '/')) {		/* ダイヤル記号（ポーズ） */
				/* "-/ "のような時、クリアキーを押すと" "となる */
				/*  ~                                  ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
			}
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!')) {		/* ダイヤル記号（トーン） */
				/* "-! "のような時、クリアキーを押すと" "となる */
				/*  ~                                  ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
			}
#endif
#if (PRO_JIS_CODE == ENABLE)
			if (CharacterInput.Buffer[CharacterInput.CursorPosition] == OPR_KANJI_CODE_MARK_LEFT) {
				/* "(1234) "のような時、クリアキーを押すと" "となる */
				/*  ~                                      ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + OPR_KANJI_CODE_LEN],
								  OPR_CHARACTER_INPUT_MAX - OPR_KANJI_CODE_LEN - CharacterInput.CursorPosition);
				CharacterInput.WritePosition -= OPR_KANJI_CODE_LEN;
				CMN_MemorySet(&CharacterInput.Buffer[CharacterInput.WritePosition], OPR_KANJI_CODE_LEN, NULL);
			}
			else {
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition- CharacterInput.KeisatsuPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition + CharacterInput.KeisatsuPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
			}
#else
			CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition- CharacterInput.KeisatsuPosition],
							  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
							  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition + CharacterInput.KeisatsuPosition);
			CharacterInput.WritePosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
#endif
		}

#else	/* 警察FAX DVT_ID87 */

		if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) { /* この場合カーソル位置が入力最後尾にある */
			/*---------------------------*/
			/** カーソル前の１文字を消去 */
			/*---------------------------*/
			if ((CharacterInput.CursorPosition > 1)
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition - 2] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition - 1] == '/')) {	/* ダイヤル記号（ポーズ） */
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = NULL;
			}
			if ((CharacterInput.CursorPosition > 1)
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition - 2] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition - 1] == '!')) {	/* ダイヤル記号（トーン） */
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = NULL;
			}
			CharacterInput.WritePosition--;
			CharacterInput.CursorPosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
		}
		else {
			/*---------------------------*/
			/** カーソル上の１文字を消去 */
			/*---------------------------*/
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '/')) {		/* ダイヤル記号（ポーズ） */
				/* "-/ "のような時、クリアキーを押すと" "となる */
				/*  ~                                  ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition + CharacterInput.KeisatsuPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
			}
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '!')) {		/* ダイヤル記号（トーン） */
				/* "-! "のような時、クリアキーを押すと" "となる */
				/*  ~                                  ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
			}
			CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition- CharacterInput.KeisatsuPosition],
							  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
							  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition + CharacterInput.KeisatsuPosition);
			CharacterInput.WritePosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition - CharacterInput.KeisatsuPosition] = NULL;
		}
#endif	/* 警察FAX DVT_ID87 */ 
	}
}
#else
void CharacterInputDataClear(void)
{
	if (CheckCharacterInputEmpty() == TRUE) {	/* バッファが空 */
		NackBuzzer();
	}
	else {
		if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) { /* この場合カーソル位置が入力最後尾にある */
			/*---------------------------*/
			/** カーソル前の１文字を消去 */
			/*---------------------------*/
#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
			if ((CharacterInput.CursorPosition > 1)
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 2] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == '/')) {	/* ダイヤル記号（ポーズ） */
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
			}
			if ((CharacterInput.CursorPosition > 1)
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 2] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == '!')) {	/* ダイヤル記号（トーン） */
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = NULL;
			}
#endif
#if (PRO_JIS_CODE == ENABLE)
			if (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] == OPR_KANJI_CODE_MARK_RIGHT) {
				CharacterInput.WritePosition -= OPR_KANJI_CODE_LEN;
				CharacterInput.CursorPosition -= OPR_KANJI_CODE_LEN;
				CMN_MemorySet(&CharacterInput.Buffer[CharacterInput.WritePosition], OPR_KANJI_CODE_LEN, NULL);
			}
			else {
				CharacterInput.WritePosition--;
				CharacterInput.CursorPosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
			}
#else
			CharacterInput.WritePosition--;
			CharacterInput.CursorPosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
#endif
		}
		else {
			/*---------------------------*/
			/** カーソル上の１文字を消去 */
			/*---------------------------*/
#if (PRO_NEW_DIALMARK_OPR == ENABLE)	/* Add By H.Fujimura 1999/01/06 */
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '/')) {		/* ダイヤル記号（ポーズ） */
				/* "-/ "のような時、クリアキーを押すと" "となる */
				/*  ~                                  ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
			}
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!')) {		/* ダイヤル記号（トーン） */
				/* "-! "のような時、クリアキーを押すと" "となる */
				/*  ~                                  ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
			}
#endif
#if (PRO_JIS_CODE == ENABLE)
			if (CharacterInput.Buffer[CharacterInput.CursorPosition] == OPR_KANJI_CODE_MARK_LEFT) {
				/* "(1234) "のような時、クリアキーを押すと" "となる */
				/*  ~                                      ~        */
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + OPR_KANJI_CODE_LEN],
								  OPR_CHARACTER_INPUT_MAX - OPR_KANJI_CODE_LEN - CharacterInput.CursorPosition);
				CharacterInput.WritePosition -= OPR_KANJI_CODE_LEN;
				CMN_MemorySet(&CharacterInput.Buffer[CharacterInput.WritePosition], OPR_KANJI_CODE_LEN, NULL);
			}
			else {
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
			}
#else
			CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
							  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
							  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
			CharacterInput.WritePosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
#endif
		}
	}
}
#endif		/* End of (defined (KEISATSU)) */

/*************************************************************************
	module		:[数字入力中、ダイアル記号キーが押されたときの処理]
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
	date		:[1995/04/21]
	author		:[江口]
*************************************************************************/
/* 警察FAX DVT_ID87 Modify by SMuratec 夏 2006/01/12 */
#if defined(KEISATSU)
void CharacterInputDialCharSet(void)
{
	UBYTE flag; /* バッファの途中にデータをセットする時で、			 */
				/* 入力位置のデータがダイアル記号以外の場合１にセット*/
	
	flag = 0;

	if (CharacterInput.CursorPosition < CharacterInput.KeisatsuPosition){
		NackBuzzer();
		return;
	}

	if (CharacterInput.CursorPosition < CharacterInput.WritePosition) { /** 入力位置が入力の途中 */
		if (ROM_SW_SpecialPauseInput == 1) {
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] != '!')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] != '/')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '/';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '/')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '!';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '!')) {		/* ダイアル記号 */
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '-';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
				  && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] = '/';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
				  && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '/')) {	/* ダイアル記号(ポーズ)*/
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition + CharacterInput.KeisatsuPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '-';
			}
			else {
				flag = 1;
			}
		}
		else {
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] != '!')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '/';
			}
   			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '/')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '!';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '!')) {		/* ダイアル記号 */
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '-';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] == '-')
				  && (CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition + CharacterInput.KeisatsuPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '-';
			}
			else {
				flag = 1;
			}
		}
	}

	if ((CharacterInput.CursorPosition >= CharacterInput.WritePosition)
	||	(flag == 1)) {
		/** 桁数オーバーのチェック */
		if (CharacterInput.WritePosition >= CharacterInput.MaxFigure) {
			NackBuzzer();
			OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
			return;
		}

		/* カーソル位置にデータをセット。カーソルは動かさない */
		if (ROM_SW_SpecialPauseInput == 1) {
			DataShiftOneStep();
			/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
			if (CHK_UNI_CSDR_DialMarkExchange()) {
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '!';
			}
			else {
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '/';
			}
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '-';
		}
		else {
			/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
			if (CHK_UNI_CSDR_DialMarkExchange()) {
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '!';
			}
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = '-';
		}
	}
}
#else
void CharacterInputDialCharSet(void)
{
	UBYTE flag; /* バッファの途中にデータをセットする時で、			 */
				/* 入力位置のデータがダイアル記号以外の場合１にセット*/

	flag = 0;


	if (CharacterInput.CursorPosition < CharacterInput.WritePosition) { /** 入力位置が入力の途中 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
 #if (PRO_SPECIAL_PAUSE_INPUT == ENABLE)	/* ポーズ追加特ＲＯＭ【RDC-1436】By J.Kishida 1999/04/14 */
		if (ROM_SW_SpecialPauseInput == 1) {
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] != '!')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] != '/')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '/';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '/')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '!')) {		/* ダイアル記号 */
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
				  && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
				CharacterInput.Buffer[CharacterInput.CursorPosition + 1] = '/';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
				  && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '/')) {	/* ダイアル記号(ポーズ)*/
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			}
			else {
				flag = 1;
			}
		}
		else {
			if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] != '!')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '/';
			}
   #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Mod by SMuratec C.P 2004/07/20 for prefix *//* by K.Watanabe 2004/12/16 */
			else if((CharacterInput.Buffer[CharacterInput.CursorPosition] == '/')) {		/* ダイアル記号 */
				if(CharacterInput.CursorPosition == 0){
					CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
					DataShiftOneStep();
					CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
				}
				else {
					CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
				}
			}
   #else
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '/')) {		/* ダイアル記号 */
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
			}
   #endif
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '!')) {		/* ダイアル記号 */
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			}
			else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
				  && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
				CharacterInput.WritePosition--;
				CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			}
			else {
				flag = 1;
			}
		}
 #else
		if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
		 && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] != '!')) {		/* ダイアル記号 */
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '/';
		}
		else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '/')) {		/* ダイアル記号 */
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
		}
		else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '!')) {		/* ダイアル記号 */
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
		}
		else if ((CharacterInput.Buffer[CharacterInput.CursorPosition] == '-')
			  && (CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!')) {	/* ダイアル記号（トーン）*/
			CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
							  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
							  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
			CharacterInput.WritePosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition] = NULL;
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
		}
		else {
			flag = 1;
		}
 #endif
#else
		switch (CharacterInput.Buffer[CharacterInput.CursorPosition]) {
		case '-':
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '/';
			break;
		case '/':
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
			break;
		case '!':
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			break;
		default: /*ダイアル記号以外 */
			flag = 1;
			break;
		}
#endif
	}

	if ((CharacterInput.CursorPosition >= CharacterInput.WritePosition)
	||	(flag == 1)) {
		/** 桁数オーバーのチェック */
		if (CharacterInput.WritePosition >= CharacterInput.MaxFigure) {
			NackBuzzer();
			OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
			return;
		}

		/* カーソル位置にデータをセット。カーソルは動かさない */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/06 */
 #if (PRO_SPECIAL_PAUSE_INPUT == ENABLE)	/* ポーズ追加特ＲＯＭ【RDC-1436】By J.Kishida 1999/04/14 */
		if (ROM_SW_SpecialPauseInput == 1) {
			DataShiftOneStep();
			/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
			if (CHK_UNI_CSDR_DialMarkExchange()) {
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
			}
			else {
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '/';
			}
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
		}
		else {
			/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
			if (CHK_UNI_CSDR_DialMarkExchange()) {
				DataShiftOneStep();
				CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
			}
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
		}
 #else
		/*【CSDR-No.58】ダイヤル記号の順番入れ替え */
		if (CHK_UNI_CSDR_DialMarkExchange()) {
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '!';
		}
		DataShiftOneStep();
		CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
 #endif
#else
		if (CharacterInput.CursorPosition == CharacterInput.WritePosition) { /* 入力位置がバッファの最後尾の時 */
			/** バッファの最後尾に値をセットする場合 */
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
			CharacterInput.WritePosition++;
		}
		else {	/* 入力位置(書き込み位置）がバッファの途中の時 */
			/** バッファの途中に値をセットする場合 */
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
		}
#endif
	}
}
#endif

/*************************************************************************
	module		:[数字入力中、１文字挿入オペレーション]
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
	date		:[1995/04/21]
	author		:[江口]
*************************************************************************/
void DataShiftOneStep(void)
{
	UBYTE	counter;

	/** カーソル以降のデータを１文字ずつずらす*/
	/* カーソル位置は動かさない　*/
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/23 */
	for (counter = OPR_CHARACTER_INPUT_MAX - 1; counter > CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition; counter--) {
		CharacterInput.Buffer[counter] = CharacterInput.Buffer[(UBYTE)(counter - 1)];
	}
#else
	for (counter = OPR_CHARACTER_INPUT_MAX - 1; counter > CharacterInput.CursorPosition; counter--) {
		CharacterInput.Buffer[counter] = CharacterInput.Buffer[(UBYTE)(counter - 1)];
	}
#endif		/* End of (defined (KEISATSU)) */

	CharacterInput.WritePosition++;
}

/*************************************************************************
	module		:[文字入力データセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		もともとは、この関数の中で桁数オーバーのチェックも行っていたが、
		ポプラＢの名前入力で漢字コード入力が追加になったため、登録内容に
		漢字コードが含まれていると、CharacterInput.WritePositionでは、
		入力文字数が判断できなくなったために桁数チェックを含まない部分を
		別関数にしました
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/21]
	author		:[江口,渡辺一章]
*************************************************************************/
void CharacterInputDataSet(UBYTE data)
{
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/06/21 */
	/** バッファの最後尾に値をセットする場合 */
	if (CharacterInput.CursorPosition == CharacterInput.WritePosition) {	/* 入力位置がバッファの最後尾の時 */
		CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = data;
		CharacterInput.CursorPosition++;
		CharacterInput.WritePosition++;
	}
	/** バッファの途中に値をセットする場合 */
	else {																/* 入力位置(書き込み位置）がバッファの途中の時 */
		/* カーソル位置以降のデータを後方にシフトし、カーソル位置にデータを書きこみ、カーソル位置を進める */
		DataShiftOneStep();
		CharacterInput.Buffer[CharacterInput.CursorPosition - CharacterInput.KeisatsuPosition] = data;
		CharacterInput.CursorPosition++;
	}
#else
	/** バッファの最後尾に値をセットする場合 */
	if (CharacterInput.CursorPosition == CharacterInput.WritePosition) {	/* 入力位置がバッファの最後尾の時 */
		CharacterInput.Buffer[CharacterInput.CursorPosition] = data;
		CharacterInput.CursorPosition++;
		CharacterInput.WritePosition++;
	}
	/** バッファの途中に値をセットする場合 */
	else {																/* 入力位置(書き込み位置）がバッファの途中の時 */
		/* カーソル位置以降のデータを後方にシフトし、カーソル位置にデータを書きこみ、カーソル位置を進める */
		DataShiftOneStep();
		CharacterInput.Buffer[CharacterInput.CursorPosition] = data;
		CharacterInput.CursorPosition++;
	}
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[文字入力データセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		もともとは、この関数の中で桁数オーバーのチェックも行っていたが、
		ポプラＢの名前入力で漢字コード入力が追加になったため、登録内容に
		漢字コードが含まれていると、CharacterInput.WritePositionでは、
		入力文字数が判断できなくなったために桁数チェックを含まない部分を
		別関数にしました
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/21]
	author		:[江口,渡辺一章]
*************************************************************************/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
void CharacterInputAddressMarkSet(UBYTE is_kanji_enable)
{
	UBYTE write_data_count;	/* 入力データ桁数 */
	
	switch (CharacterInput.Buffer[CharacterInput.CursorPosition]) {	/* カーソル上の入力データにより分岐 */
	case '.':	/* ピリオド */
		CharacterInput.Buffer[CharacterInput.CursorPosition] = '@';
		break;
	case '@':	/* アットマーク */
		CharacterInput.Buffer[CharacterInput.CursorPosition] = '_';
		break;
	case '_':	/* アンダーバー */
		CharacterInput.Buffer[CharacterInput.CursorPosition] = '-';
		break;
	case '-':	/* ハイフン */
		CharacterInput.Buffer[CharacterInput.CursorPosition] = '.';
		break;
	default:
		/*----------------------------*/
		/* 次の入力が可能かを調べます */
		/*----------------------------*/
		if (!CheckNextDataWrite(is_kanji_enable, &write_data_count)) {
			NackBuzzer();
			OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;	/* 入力バッファ桁数オーバー */
			return;
		}
		/** バッファの最後尾に値をセットする場合 */
		if (CharacterInput.CursorPosition == CharacterInput.WritePosition) {/* 入力位置がバッファの最後尾の時 */
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '.';
			CharacterInput.WritePosition++;
		}
		/** バッファの途中に値をセットする場合 */
		else {												/* 入力位置(書き込み位置）がバッファの途中の時 */
			/* カーソル位置以降のデータを後方にシフトし、カーソル位置にデータを書きこみ、カーソル位置を進める */
			DataShiftOneStep();
			CharacterInput.Buffer[CharacterInput.CursorPosition] = '.';
		}
		break;
	}
}
#endif

/*************************************************************************
	module		:[文字入力データセット ＆ 桁数オーバーチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		この関数は、名前入力以外の場所からのみ呼び出されます
		（名前入力では、先に桁数チェックを行っています）
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/04/21]
	author		:[江口,渡辺一章]
*************************************************************************/
void CharacterDataSet_FigureCheck(UBYTE data)
{
	/** 桁数オーバーのチェック */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/16 Y.Matsukuma */
	if (CharacterInput.WritePosition >= 4) {
#else
	if (CharacterInput.WritePosition >= CharacterInput.MaxFigure) {
#endif
		NackBuzzer();
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
		return;
	}

	CharacterInputDataSet(data);
}

/*************************************************************************
	module		:[ダイアル記号キー]
	function	:[
		1.数字入力、特殊記号キー処理
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/09/13]
	author		:[江口]
*************************************************************************/
void CharacterInputDialMarkSet(UBYTE mark)	/*ダイヤル記号*/
{
	UBYTE	i;
	UBYTE	len;		/*文字列長*/
	UBYTE	key[2];

#if defined(KEISATSU)	/* 警察FAX DVT_ID87 Added by SMuratec 夏 2006/01/13 */
	if (CharacterInput.CursorPosition < CharacterInput.KeisatsuPosition){
		NackBuzzer();
		return;
	}
#endif

	switch (mark) {
	case PAUSE_MARK:
		len = 2;
		key[0] = '-';
		key[1] = '/';
		break;
	case TONE_MARK:
		len = 2;
		key[0] = '-';
		key[1] = '!';
		break;
#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
	case FLASH_MARK:
		len = 1;
		key[0] = '/';
		break;
#endif
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix */	/* 1996/06/25  H,Yagi *//* by K.Watanabe 2004/10/12 */
	case MERCURY_MARK:
		len = 1;
		key[0] = '!';
		break;
	case MERCURY_TONE_MARK:
		len = 1;
		key[0] = 'M';
		break;
#endif
	default:
		break;
	}
	if ((UBYTE)(CharacterInput.WritePosition + len) > CharacterInput.MaxFigure) {
		/* 桁数オーバー */
		NackBuzzer();
		OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
	}
	else {
		for (i = 0; i < len; i++) {
			CharacterDataSet_FigureCheck(key[i]);		
		}
	}
}

/*************************************************************************
	module		:[カーソル右回り]
	function	:[
		1.カーソルを右方向に移動させる。
		2.最後まで来た場合、先頭に戻す
	]
	return		:[]
	common		:[CharacterInput:CursorPosition,WritePosition]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口]
*************************************************************************/
void CursorRightRotation(void)
{
	if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) { /* 最後まできたら最初に戻る (桁数オーバーはない) */
		CharacterInput.CursorPosition = 0;
	}
	else {
		CharacterInput.CursorPosition++;
	}
}

/*************************************************************************
	module		:[カーソル左回り]
	function	:[
		1.カーソルを左方向に移動させる
		2.先頭に来た場合、最後に移動させる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[CharacterInput]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口]
*************************************************************************/
void CursorLeftRotation(void)
{
	if (CharacterInput.CursorPosition == 0) { /* 先頭まで戻ったら最後にカーソルを持ってくる(Ring)*/
		CharacterInput.CursorPosition = CharacterInput.WritePosition;
	}
	else {
		CharacterInput.CursorPosition--;
	}
}

/*************************************************************************
	module		:[固定長数字入力データセット]
	function	:[
		1.入力された数字データをバッファにセットする。
		2｡上書きで入力する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口]
*************************************************************************/
void FixedNumberDataSet(UBYTE key)
{
	CharacterInput.Buffer[CharacterInput.CursorPosition] = key;
	CursorRightRotation();
}

/*************************************************************************
	module		:[数字入力作業用バッファクリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[このバッファはいろんなところで使ってる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口,渡辺一章]
*************************************************************************/
void ClearCharacterInput(void)
{
	CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
	CharacterInput.CursorPosition = 0;
	CharacterInput.WritePosition = 0;
	CharacterInput.DisplayStartPosition = 0;
	CharacterInput.LcdDisplayPosition = 0;
	CharacterInput.MaxFigure = 0;
	CharacterInput.MaxValue = 0;
	CharacterInput.MinValue = 0;
	CMN_MemorySet(CharacterInput.InputKeyBuffer, 5, NULL);
	CharacterInput.InputKeyPosition = 0;
	CharacterInput.Mode = 0;
	CharacterInput.FixedWordingHigh = NULL;
	CharacterInput.FixedWordingLow = NULL;
	CharacterInput.IsNoInputEnable = FALSE;	/* データ未入力不可能 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/13 by K.Okada */
	CharacterInput.Only7bitAsciiEnable = 0;
	CharacterInput.AddressMarkInputMode = 0;
#endif
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
	CharacterInput.Keisatsu = 0x00;
	CMN_MemorySet(CharacterInput.KeisatsuBuf, 4, NULL);
	CharacterInput.KeisatsuPosition = 0;
#endif		/* End of (defined (KEISATSU)) */
}

/*************************************************************************
	module		:[文字入力で登録されたデータを文字列形式から数字に変換]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[
		変換された結果、９９９９を越えるようなデータ（CharacterInput.Buffer[]の
		入力桁数が４桁をこえるもの）は入力できない

		必ずデータがセットされている時のみ、この関数を呼ぶ事
		（データがセットされていない時と、０が入力されている時が同じになる為）
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UWORD CharacterInputToNumber(void)
{
	UBYTE	length;
	UWORD	number;

	length = CMN_StringLength(CharacterInput.Buffer);
	number = CMN_ASC_ToUnsignedInt(CharacterInput.Buffer, length);
	return (number);
}

/*************************************************************************
	module		:[文字入力で登録されたデータを格納]
	function	:[
		1.文字入力で入力されたデータを引数で指定されたバッファにコピーする。
		2.コピーするデータ形式は引数で指定。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		コピー元のデータ（CharacterInput.buffer）のデータ長が
		コピー先のサイズを越えないことをチェックしてからこの関数をコールすること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口,渡辺一章]
*************************************************************************/
void StoreCharacterInputValue(UBYTE *DST_String,	/* 格納先の先頭アドレス */
							  UBYTE data_type)		/* 格納先のデータタイプ */
{
#if (PRO_JIS_CODE == ENABLE)	/* 1997/06/24 Y.Matsukuma */
	UBYTE	i;
	UWORD	code;
#endif
	UBYTE	cnt;

	switch (data_type) {
	case ASC_DATA_TYPE:
		CMN_StringCopyNULL(DST_String, CharacterInput.Buffer);
		break;
	case BCD_DATA_TYPE:
		/* 変換後のBCDのサイズが、SYS_TEL_2DIGIT_MAXを超える様な場合は、CMN_ASC_ToBCD_StringNum()を使用して下さい */
		CMN_ASC_ToBCD_String(DST_String, CharacterInput.Buffer);
		break;
	case BCD_PIN_DATA_TYPE:		/* PIN番号には終端文字が付かないので下の処理に変更します。 97/12/04 T.Fukumoto */
		cnt = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
		CMN_ASC_ToBCD_StringNum(DST_String, CharacterInput.Buffer, cnt);
		break;
#if (PRO_JIS_CODE == ENABLE)
	case ASC_JIS_DATA_TYPE:
		i = 0;
		while (CharacterInput.Buffer[i] != NULL) {	/* NULLで終了します */
			if (CharacterInput.Buffer[i] == OPR_KANJI_CODE_MARK_LEFT) {	/* 漢字コードの時 */

				/* 漢字コードの時は、入力値はJISコードなので、シフトJISコードに変換後格納します
				** 注）格納先のバッファがバイトデータのため、JISコードで格納すると漢字コードとそれ以外の
				** 　　文字との区別がつかないので、入力値と格納値でコードの種類が違います
				*/
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2で漢字コードの入力は　Ｖ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
				code = CMN_ASC_KUTEN_CodeToJIS(&CharacterInput.Buffer[i + 1]);	/* 入力された区点コードをJISコードに変換 */
				code = CMN_JIS_ToShiftJIS(code);										/* JISコードをシフトJISコードへ変換 */
 #else
				code = CMN_ASC_ToUnsignedIntHex(&CharacterInput.Buffer[i + 1], 4);	/* 入力された値を１６進数に変換 */
				code = JIS_ToShiftJIS(code);										/* シフトJISコードへ変換 */
 #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
				*DST_String++ = (UBYTE)(code >> 8);
				*DST_String++ = (UBYTE)(code & 0x00FF);
				i += 6;
			}
			else {														/* 英数字・片仮名・記号の時 */
				*DST_String++ = CharacterInput.Buffer[i];
				i++;
			}
		}
		*DST_String = NULL;
		break;
#endif
	default:
		break;
	}
}

/*************************************************************************
	module		:[ソフトディップ、ビット変換セット]
	function	:[
		1.文字入力で入力されたソフトディプ（文字列形式）を
		  ソフトディプ（ビット形式）に変換する。
	]
	return		:[変換後のソフトディップ]
	common		:[]
	condition	:[]
	comment		:[H8から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
UBYTE StoreCharacterInputToSoftDip(void)
{
	UBYTE	number;
	UBYTE	test_bit;
	UBYTE	count;

	number = 0;
	test_bit = 0x80;

	for ( count = 0; count < 8; count++ ) {
		if (CharacterInput.Buffer[count] == '1' ) {
			number |= (test_bit >> count);
		}
	}
	return (number);
}

/*************************************************************************
	module		:[文字入力で入力されたデータをグループ番号に変換]
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
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UDWORD StoreCharacterInputToLongGroup(void)
{
	UBYTE	number;
	UBYTE	length;
	UDWORD	group_number;
	UDWORD	bit = 0x00000001;	 /*00000000000000000000000000000001*/

	length = 0;
	number = 0;
	group_number = (UDWORD)0;
	bit 		 = (UDWORD)0x00000001;
	CharacterInput.CursorPosition = 0;
	CMN_MemorySet(OPR_CharacterCheckBuffer, OPR_CHECK_BUFFER_MAX, NULL);

	if (CheckCharacterInputEmpty() == TRUE) { /* 未入力 */
		group_number = (UDWORD)0;
	}
	else { /* 入力データ有り */
		while (CharacterInput.Buffer[CharacterInput.CursorPosition] != NULL) {
			length = SetToCheckBuffer(&CharacterInput.Buffer[CharacterInput.CursorPosition],',');
			if (length > 0) {
				number = (UBYTE)CMN_ASC_ToUnsignedInt(OPR_CharacterCheckBuffer, length);
				if (number == 0) {
					group_number = (UDWORD)0xFFFFFFFF;
					break;
				}
				else {
					group_number |= (bit << (number - 1));
				}
			}
			else { /* length == 0 これ以上データがない */
				break;
			}
			CharacterInput.CursorPosition += length;
			if (CharacterInput.Buffer[CharacterInput.CursorPosition] == ',') { /*区切り文字上にカーソル有り*/
				CharacterInput.CursorPosition++;
			}
		}
	}
	CMN_MemorySet(OPR_CharacterCheckBuffer, OPR_CHECK_BUFFER_MAX, NULL);
	return (group_number);
}

/*************************************************************************
	module		:[文字入力で入力されたデータをデータベース番号として格納]
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
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
void StoreCharacterInputToDatabase(UWORD *data_base)
{
	UBYTE	length;
	UBYTE	file_count;

	length = 0;
	file_count = 0;

	CharacterInput.CursorPosition = 0;
	CMN_MemorySet(OPR_CharacterCheckBuffer, OPR_CHECK_BUFFER_MAX, NULL);

	while (1) {
		length = SetToCheckBuffer(&CharacterInput.Buffer[CharacterInput.CursorPosition] , ',');
		if (length > 0) { /* 入力データ有り */
			*data_base = CMN_ASC_ToUnsignedInt(OPR_CharacterCheckBuffer, length);
			data_base++;
			file_count++;
			CharacterInput.CursorPosition += length;
			if (CharacterInput.Buffer[CharacterInput.CursorPosition] == ',') { /*区切り文字上にカーソル有り*/
				CharacterInput.CursorPosition++;
			}
		}
		else {
			CMN_MemorySet(OPR_CharacterCheckBuffer, OPR_CHECK_BUFFER_MAX, NULL);
			return;
		}
	}
}

/*************************************************************************
	module		:[ソフトディプ文字列変換]
	function	:[
		1.ソフトディプ（ビット形式）を編集用のバッファに文字列形式で格納
	]
	return		:[ない]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
void StoreSoftDipToCharacterInput(UBYTE soft_dip)	/*ｿﾌﾄﾃﾞｨﾌﾟ（ﾋﾞｯﾄ形式）*/
{
	UBYTE	bit;	/*ﾃｽﾄﾋﾞｯﾄ*/
	WORD	count;	/*loop*/

	bit = 0x80;

	for (count = 0; count < 8; count++) {
		if (soft_dip & (bit >> count)) {
			CharacterInput.Buffer[count] = '1';
		}
		else {
			CharacterInput.Buffer[count] = '0';
		}
	}
	CharacterInput.Buffer[count] = NULL;
}

/*************************************************************************
	module		:[ロング型のグループ番号を編集できるように文字列に変換]
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
	date		:[1995/07/25]
	author		:[江口]
*************************************************************************/
void StoreGroupToCharacterInput(UDWORD group_number)	/*グループ番号データ*//*ビット列*/
{
	UBYTE	shift;			/*ｼﾌﾄﾙｰﾌﾟ*/
	UBYTE	data_length;
	UBYTE	position;

	data_length = 0;
	position = 0;

	if (group_number == 0x00000000UL) { /* 未登録->なにもしない(セットするバッファのクリアもしない)*/
		return;
	}
	if (group_number == 0xffffffffUL) { /* グループ番号に０を指定するとこうなる */
		CharacterInput.Buffer[position] = '0';
		return;
	}

	for (shift = 0; shift < SYS_GROUP_NUMBER_MAX; shift++) {
		if (group_number & (0x00000001UL << shift) ) {
			if ((shift + 1) < 10) { /*１桁 */
				data_length = 1;
			}
			else {	/* ２桁 */
				data_length = 2;
			}
			CMN_UnsignedIntToASC(&CharacterInput.Buffer[position], (UWORD)(shift + 1), data_length, '0');
			position += data_length;
			CharacterInput.Buffer[position++] = ','; /* 区切り挿入 */
		}
	}
	CharacterInput.Buffer[position - 1] = NULL; /* 最後のコンマをＮＵＬＬに変換 */
}

/*************************************************************************
	module		:[ロング型時間を入力形式に変換]
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
	date		:[1995/12/27]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetLongTimeToCharacterInput(UDWORD long_time, UBYTE type)
{
	UBYTE	position;
	union	OperationTimeData_t bcd_time;

	/** 現在時刻を計算 */
	CMN_LongTimeToBCD(&(bcd_time.BCD_StructTime) ,long_time);

	/* 年月日時分のみしかいらないので、残りの秒、曜日をへつる */
	/* このタイミングでこの処理をしないと暴走する */
	bcd_time.BCD_StructTime.Second = 0xFF;
	bcd_time.BCD_StructTime.Week   = 0xFF;

	/* ASCIIに直す */
	switch (type) {
	case CALENDER_TYPE:				/* カレンダーセット */
		position = 0;	/* 年月日時分 */
		break;
	case COMMAND_TIME_TYPE:			/* 送信指定時刻入力 */
		position = 2;	/* 日時分 */
		break;
	case SECURITY_RX_TIME_TYPE:		/* セキュリティ受信開始時刻 */
	case CONT_POLLING_RX_TIME_TYPE:	/* 連続ポーリング時刻入力 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/17 by K.Okada */
	case AUTO_MAIL_RX_TIME_TYPE:
#endif
		position = 3;	/* 時分 */
		break;
	}
	CMN_BCD_ToASC_String(&CharacterInput.Buffer[0], &bcd_time.BCD_StringTime[position]);
}

/*************************************************************************
	module		:[コマンド送信時刻を編集形式に変換]
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
	date		:[1995/12/27]
	author		:[江口]
*************************************************************************/
void SetSpecialTimeToCharacter(void)
{
	/* 日時分を編集用バッファにセットする*/
	/* 日 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], (UWORD)(SpecialCommandValue.CommandTime / 1440), 2, '0');
	/* 時 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[2], (UWORD)((SpecialCommandValue.CommandTime % 1440) / 60), 2, '0');
	/* 分 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[4], (UWORD)((SpecialCommandValue.CommandTime % 1440) % 60), 2, '0');
}

/*************************************************************************
	module		:[文字入力で入力があったかどうか調べる]
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
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckCharacterInputEmpty(void)
{
	if ((CharacterInput.Buffer[0] == NULL) && (CharacterInput.WritePosition == 0)) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[番号の入力（文字数が最大値まで入力されると０に戻る）]
	function	:[
			1. 以下の物の入力に対応
				a)部門コード入力
				b)ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ入力
				]
	return		:[なし]
	common		:[
		OPR_Buf:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/05/26]
	author		:[桑原美紀]
*************************************************************************/
UBYTE	 		InputNumberRotation( 
						UBYTE	Type )
{
	UBYTE	key;
	UBYTE	keytype;
/*	UBYTE	check;*/	/* いつでも表示処理を通るようにした為、必要無し 97/11/07 By M.Kuwahara */

/*	check	= 0;*/

	NumberRotationInitial(Type);
/*	CharacterInput.CursorPosition	= 0;*/

	while(1) {
/*		if( check == 0 ){*/		/* 97/11/07 By M.Kuwahara */
			/** 表示処理 */
			DisplayNumberRotation( Type );
/*		}*/

/*		CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));*/
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);						/* キー取り込み */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch(keytype) {										/* 取り込んだキーに対する処理 */
		case FUNCTION:		/* ＞キー */
			if( CharacterInput.WritePosition >= CharacterInput.MaxFigure ){			/* 最大桁入力されている時 */
				if ((CharacterInput.CursorPosition + (UBYTE)1) >= CharacterInput.WritePosition) {		/* ｶｰｿﾙ位置が最大の時 *//* add (UBYTE) 1997/06/24 Y.Matsukuma */
					CharacterInput.CursorPosition	= 0;
				}
				else{
					CharacterInput.CursorPosition++;
				}
			}
			else{
				if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {		/* ｶｰｿﾙ位置が最大の時 */
					NackBuzzer();
				}
				else{
					CharacterInput.CursorPosition++;
				}
			}
			break;
		case LEFT_ARROW:	/* ＜キー */
			if (CharacterInput.WritePosition == CharacterInput.MaxFigure) {		/* 表示最終位置が最大の時 */
				if( CharacterInput.CursorPosition == 0 ){			/* カーソル位置が最小の時 */
					CharacterInput.CursorPosition	= CharacterInput.MaxFigure - (UBYTE)1;	/* add (UBYTE) 1997/06/24 Y.Matsukuma */
				}
				else{
					CharacterInput.CursorPosition--;
				}
			}
			else{
				if( CharacterInput.CursorPosition == 0 ){			/* カーソル位置が最小の時 */
					NackBuzzer();
				}
				else{
					CharacterInput.CursorPosition--;
				}
			}
			break;
		case NUMBER:		/* 数字キー */
		case DIALMARK:		/* ダイアル記号キー */
			if( keytype == DIALMARK ){
				if( Type == OPR_TX_DEPART_CODE_INPUT ){		/* 部門コード */
					NackBuzzer();
					break;
				}
				else{
					key	= '-';
				}
			}
			

			CharacterInput.Buffer[CharacterInput.CursorPosition] = key;
			/* 表示最終位置のセット */
			if (CharacterInput.WritePosition < CharacterInput.MaxFigure) {		/* 表示桁数が最大桁以下の時 */
				if (CharacterInput.CursorPosition >= CharacterInput.WritePosition) {	/*入力位置がﾊﾞｯﾌｧの最後尾の時*/
					CharacterInput.WritePosition++;
				}
			}
			/* カーソル位置の移動 */
			if (CharacterInput.WritePosition >= CharacterInput.MaxFigure) {		/* 表示桁数が最大桁以上の時 */
			   if((CharacterInput.CursorPosition + (UBYTE)1) >= CharacterInput.WritePosition){	/* add (UBYTE) 1997/06/24 Y.Matsukuma */
					CharacterInput.CursorPosition	= 0;
				}
				else{
					CharacterInput.CursorPosition++;
				}
			}
			else{
				CharacterInput.CursorPosition++;
			}
			CMN_StringCopy(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition], CharacterInput.Buffer);
			DisplayStringLow(0, FunctionDisplayBufferLow);
/*			check	= 1;*/
			break;
		case ENTER:		/* セットキー */
			CursorOff();	/* 終了する */
			return (OK);
		case CLEAR:		/* クリアキー */
			if( CharacterInput.Buffer[CharacterInput.CursorPosition] == 0x00 ){		/* 文字入力無しの時 */
				if (CharacterInput.CursorPosition == 0) {
					NackBuzzer();
					break;
				}
				CharacterInput.CursorPosition--;
			}
			else{
				CMN_StringCopyNum(&CharacterInput.Buffer[CharacterInput.CursorPosition],
								  &CharacterInput.Buffer[CharacterInput.CursorPosition + 1],
								  OPR_CHARACTER_INPUT_MAX - 1 - CharacterInput.CursorPosition);
			}
			CharacterInput.WritePosition--;
			CharacterInput.Buffer[CharacterInput.WritePosition]	= NULL;
			CMN_StringCopy(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition], CharacterInput.Buffer);
			FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition + CharacterInput.WritePosition]	= ' ';
			DisplayStringLow(0, FunctionDisplayBufferLow);
/*			check	= 1;*/
			break;
		case NO_EFFECT:
			break;
		case KEY_TIME_UP:	/* 一分間入力なし */
		case STOP:			/* ストップキー */
			CursorOff();
			return( NG );
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[入力中の表示]
	function	:[
			1. 以下の物の入力に対応
				a)部門コード入力
				b)ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ入力
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[番号は01から表示する]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/05/27]
	author		:[桑原美紀]
*************************************************************************/
void			DisplayNumberRotation(
							UBYTE	Type )
{
	if (CheckChildErrorDisplayReq() == TRUE) {	/** チャイルド表示すべきエラーが発生した */
		CursorOff();
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {	/** チャイルド表示中 */
		return;
	}

	/* 表示バッファにメモリをセット */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	switch( Type ){
	case	OPR_TX_DEPART_CODE_INPUT:		/* 部門コード */
		/* 上段「Enter Dept. Code   」*/
		CMN_StringCopy( FunctionDisplayBufferHigh, D2W_EnterDepartmentCode );
		/* 固定文字表示 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[0], 
							 OPR_Buf.DepartmentSelectNumber + 1,
							 3, '0');
		FunctionDisplayBufferLow[3] = ':';
#else
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[0], 
							 OPR_Buf.DepartmentSelectNumber + 1,
							 2, '0');
		FunctionDisplayBufferLow[2] = ':';
#endif
#if (0)
		/* 部門コード表示 */
		if ( CharacterInput.Buffer[0] != NULL ) {	/* すでにﾃﾞｰﾀがｾｯﾄされている時 97/11/07 By M.Kuwahara */
			break;
		}
		if (SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] == 0xFFFF) { 		/* 部門コードが登録してあるか */
			CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
		}
		else{
			/** 部門コード番号を取り出し、ASCIIになおして表示バッファにコピー */
			CMN_UnsignedIntToASC(CharacterInput.Buffer, 
								 SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber], 
								 DPTCODE_MAX, '0');
		}
#endif
		break;
	case	OPR_JUNK_MAIL_NUMBER_INPUT:		/* ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ */
		/* [Fax Number          」*/
		CMN_StringCopy( FunctionDisplayBufferHigh, D2W_EnterDialNumber );
		/* 固定文字表示 */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[0], 
							 OPR_Buf.JunkMailSelectNumber + 1,
							 2, '0');
		FunctionDisplayBufferLow[2] = ':';
#if (0)
		/* ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ表示 */
		if ( CharacterInput.Buffer[0] != NULL ) {	/* すでにﾃﾞｰﾀがｾｯﾄされている時 97/11/07 By M.Kuwahara */
			break;
		}
		if (SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0] == 0xFF) { 	/* ﾀﾞｲﾔﾙが登録してあるか */	
			CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
		}
		else{
			/** ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙを取り出し、ASCIIになおして表示バッファにコピー */
			CMN_BCD_ToASC_String(CharacterInput.Buffer, 
								 SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber]);
		}
#endif
		break;
	}
	CharacterInput.WritePosition = CMN_StringLength( CharacterInput.Buffer );	/* 入力最後尾をセット */
	CMN_StringCopy(&FunctionDisplayBufferLow[CharacterInput.LcdDisplayPosition], CharacterInput.Buffer);
	ClearDisplayHigh();								/* 上段表示クリア */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);/* 上段表示 */
	ClearDisplayLow();								/* 下段表示クリア */
	DisplayStringLow(0, FunctionDisplayBufferLow);	/* 下段表示 */
	CursorOn((UBYTE)(CharacterInput.LcdDisplayPosition + CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));

}

/*************************************************************************
	module		:[数字入力初期値セット]
	function	:[
			1. 以下の物の入力に対応
				a)部門コード入力
				b)ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ入力
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/18]
	author		:[桑原美紀]
*************************************************************************/
void NumberRotationInitial(UBYTE type)
{
	if ( CharacterInput.Buffer[0] != NULL ) {	/* 既にデータがセットされている時 */
		CharacterInput.CursorPosition	= 0;
	}
	else{
		ClearCharacterInput();
		switch( type ) {
		case	OPR_TX_DEPART_CODE_INPUT:		/* 部門コード */
			CharacterInput.WritePosition = 0;
			CharacterInput.MaxFigure = DPTCODE_MAX;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			CharacterInput.LcdDisplayPosition = 4;
#else
			CharacterInput.LcdDisplayPosition = 3;
#endif
			if (SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber] == 0xFFFF) { 		/* 部門コードが登録してあるか */
				CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
			}
			else{
				/** 部門コード番号を取り出し、ASCIIになおして表示バッファにコピー */
				CMN_UnsignedIntToASC(CharacterInput.Buffer, 
									 SYB_DepartmentCode[OPR_Buf.DepartmentSelectNumber], 
									 DPTCODE_MAX, '0');
			}
			break;
		case	OPR_JUNK_MAIL_NUMBER_INPUT:		/* ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙ */
			CharacterInput.WritePosition = 0;
			CharacterInput.MaxFigure = JUNK_CODE_MAX;
			CharacterInput.LcdDisplayPosition = 3;
			if (SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber][0] == 0xFF) { 	/* ﾀﾞｲﾔﾙが登録してあるか */	
				CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
			}
			else{
				/** ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙを取り出し、ASCIIになおして表示バッファにコピー */
				CMN_BCD_ToASC_String(CharacterInput.Buffer, 
									 SYB_JunkMailProtectDialBuffer[OPR_Buf.JunkMailSelectNumber]);
			}
			break;
		}
	}
}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* （SATSUKI2で　数字入力　＊・＃キーオペレーションはＶ６５０と同じです）移植 by SMuratec L.Z.W 2003/09/18 */
/*************************************************************************
	module		:[数字入力　＊・＃キーオペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
					・2001/05/01 K.Sasaki	汎用にパラメータ追加
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/04/13]
	author		:[渡辺一章]
*************************************************************************/
void	 		InputNumberAsteriskSharpKey( 
						CONST UBYTE		mode,
						CONST UBYTE		key_code,
						UBYTE			*buffer,
						unsigned char	*cursor_position,
						unsigned char	write_position,
						UBYTE			*bef_chk
						 )
{
	UBYTE	is_key_data_set;
	UBYTE	set_data[2];
	UWORD	CursorPosition;
	
/*	CursorPosition	= *cursor_position;*/ /* (意味がありません) Delete by SMuratec L.Z.W 2003/10/23 */

	is_key_data_set = FALSE;

	if (/*CursorPosition*/*cursor_position < write_position) {	/* カーソル位置が入力数字の途中の時 */
		if (key_code == TEN_AST_KEY) {	/* ＊キーの時 */
			if ((*bef_chk == 1) && (*buffer == '*')) {					/* カーソル位置が'*'の時 */
				/* カーソル位置のデータをトーン記号に置き換える */
				if (mode == 0) {
					if (CharacterInput.WritePosition > (CharacterInput.MaxFigure - 1)) {
						NackBuzzer();
						OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
					}
					else {
						CharacterInput.MaxFigure --;
						*buffer = 0x09;
					}
				}
				else{
					if (CheckInputDirectDial(AST) == FALSE) {
						/* 桁数チェックなのですが CheckInputDirectDial()にて OPR_PAUSE以外時に１桁の指定をしているので
						** あえて ASTを使用しました */
						NackBuzzer();
					}
					else {
						*buffer = 0x09;
					}
				}
			}
			else if ((*bef_chk == 1) && (*buffer == 0x09)) {	/* カーソル位置がトーン記号の時 */
				/* カーソル位置のデータを'*'に置き換える */
				if (mode == 0) {
					CharacterInput.MaxFigure ++;
				}
				*buffer = '*';
			}
			else {
				/* カーソル位置に'*'を挿入する */
				is_key_data_set = TRUE;
			}
		}
		else {							/* ＃キーの時 */
			if ((*bef_chk == 1) && (*buffer == '#')) {		/* カーソル位置が'#'の時 */
				/* カーソル位置のデータを'-'に置き換える */
				*buffer = '-';
			}
			else if ((*bef_chk == 1) && (*buffer == '-')) {	/* カーソル位置が'-'の時 */
				/* カーソル位置のデータを'#'に置き換える */
				*buffer = '#';
			}
			else {
				/* カーソル位置に'#'を挿入する */
				is_key_data_set = TRUE;
			}
		}
	}

	if ((/*CursorPosition*/*cursor_position >= write_position) || (is_key_data_set)) {
		if (is_key_data_set) {	/* そのキーでの初めてのキー入力の時 */
			/* ＊キー・＃キーを続けて押されていないかを調べます */
			if (DialCharacterCheck(buffer,
								   /*CursorPosition*/*cursor_position,
								   write_position) == TRUE) {
				(/*CursorPosition*/*cursor_position)++;
			}
			else if (CharacterInput.Buffer[CharacterInput.CursorPosition] == '-' /* （トンキーを続けて押されていないかを調べます）Added by SMuratec L.Z.W 2003/10/23 */
				&& CharacterInput.Buffer[CharacterInput.CursorPosition + 1] == '!') {
				if (*cursor_position + 2 == write_position) {
					(*cursor_position) += 2;
				}
			}
		}
		/* カーソル位置が入力数字の最後か、カーソル位置にデータを挿入する時 */
		if (mode == 1) {			/* InputNumber使用 */
			if (CheckInputDirectDial(AST) == FALSE) {
				/* 桁数チェックなのですが CheckInputDirectDial()にて OPR_PAUSE以外時に１桁の指定をしているので
				** あえて ASTを使用しました */
				NackBuzzer();
			}
			else {
				set_data[0] = key_code;
				set_data[1] = NULL;
				InsertInputData(&set_data[0], 2);
				if (OPR_ChildErrorFlag != TOO_MANY_DIGITS_ERROR){
					InputNumber.CursorPosition--;
					*bef_chk = 1;
				}
			}
		}
		else {						/* CharacterInput使用 */
			CharacterDataSet_FigureCheck(key_code);
			if (OPR_ChildErrorFlag != TOO_MANY_DIGITS_ERROR) {
				CharacterInput.CursorPosition--;
				*bef_chk = 1;
			}
		}
	}

/*	*cursor_position = CursorPosition;	*/ /* (意味がありません) Delete by SMuratec L.Z.W 2003/10/23 */
}
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/21 */
UBYTE UpdateKeisatsuBuf(void)
{
	UBYTE	kei_pos;
	kei_pos = 0;
	
	if (CharacterInput.Keisatsu & SYS_KEISATSU_KEIDEN){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "ｹ", 1);
		kei_pos++;
	}
	else if (CharacterInput.Keisatsu & SYS_KEISATSU_KANYU){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "ｶ", 1);
		kei_pos++;
	}

	if (CharacterInput.Keisatsu & SYS_KEISATSU_ISSEI){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "ｲ", 1);
		kei_pos++;
	}
	else if (CharacterInput.Keisatsu & SYS_KEISATSU_KOBETSU){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "ｺ", 1);
		kei_pos++;
	}

	if (CharacterInput.Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "S", 1);
		kei_pos++;
	}
	else if (CharacterInput.Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "N", 1);
		kei_pos++;
	}

	if (CharacterInput.Keisatsu & SYS_KEISATSU_KYOTSU){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "ｷ", 1);
		kei_pos++;
	}
	else if (CharacterInput.Keisatsu & SYS_KEISATSU_SENYO){
		CMN_StringCopyNumNotNULL(&CharacterInput.KeisatsuBuf[kei_pos], "ｾ", 1);
		kei_pos++;
	}
	
	CharacterInput.KeisatsuPosition = kei_pos;

	DisplayNumberInput();
	
	return (kei_pos);
}

UBYTE	KeisatsuSet_OverCheck(UBYTE key)
{
	UBYTE keycode = key;
	switch (keycode) {
	case ONETOUCH_27_KEY:			/* 警電/加入 */	/* ワンタッチ２７キー		*/
		if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KEIDEN | SYS_KEISATSU_KANYU)) != 0x00) {
			return FALSE;
		}
		break;
	case ONETOUCH_28_KEY:			/* 一斉/個別 */	/* ワンタッチ２８キー		*/
		if ((CharacterInput.Keisatsu & (SYS_KEISATSU_ISSEI | SYS_KEISATSU_KOBETSU)) != 0x00) {
			return FALSE;
		}
		break;
	case ONETOUCH_29_KEY:			/* スクランブル */	/* ワンタッチ２９キー	*/
		if ((CharacterInput.Keisatsu & (SYS_KEISATSU_SCRAMBLE_ON | SYS_KEISATSU_SCRAMBLE_OFF)) != 0x00) {
			return FALSE;
		}
		break;
	case ONETOUCH_30_KEY:			/* 共通/専用 */	/* ワンタッチ３０キー		*/
		if ((CharacterInput.Keisatsu & (SYS_KEISATSU_KYOTSU | SYS_KEISATSU_SENYO)) != 0x00) {
			return FALSE;
		}
		break;
	}
	
	if (CharacterInput.WritePosition >= CharacterInput.MaxFigure) {
		return TRUE;
	}
	
	return FALSE;
}
#endif 		/* End of (defined (KEISATSU)) */

