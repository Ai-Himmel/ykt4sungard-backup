/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SPE.C
*	Author		: 渡辺一章
*	Date		: 1996/10/23
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 応用機能入力
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysbatch.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\stng_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#else
	#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

/* Prototype
UBYTE	SpecialCommandOperation(UBYTE);
UBYTE	SelectSpecialCommand(UBYTE);
void	DisplaySelectSpecialCommand(UBYTE, UBYTE);
UBYTE	DelayedTransmissionOperation(UBYTE);
UBYTE	DelayedTransmissionTimeInput(void);
UBYTE	CheckAndCalculateCommandTime(void);
UDWORD	TotalMinutesFromMonthHead(UBYTE, UBYTE, UBYTE);
UBYTE	ProgramTimeInput(void);
UBYTE	CheckAndSetProgramTime(void);
void	DisplayTimeInput(UBYTE);
UBYTE	SecureTransmissionOperation(void);
UBYTE	RelayTransmissionOperation(void);
UBYTE	PollingCommunicationOperation(void);
void	DataBaseInputInitial(void);
UBYTE	CheckDataBasePollingInput(void);
UBYTE	CheckDataBaseFileNumber(void);
void	PollingOptionSet(void);
#if (PRO_BATCH_TX == ENABLE)
UBYTE	BatchTransmissionOperation(void);
UBYTE	FinalBatchTxOperation(UBYTE, UBYTE);
void	DisplayFinalBatchTx(UBYTE, UBYTE);
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
UBYTE	ContPollingOperation(void);
UWORD	ContPollingTimeInput(void);
#endif
#if (PRO_F_CODE == ENABLE)
UBYTE	FcodeTransmissionOperation(void);
UBYTE	FcodePollingOperation(void);
UBYTE	ComOptionFcodeNumberInput(void);
#endif
#if (PRO_CIPHER == ENABLE)
UBYTE	CipherTransmissionOperation(void);
UBYTE	ComOptionCipherTxParaInput(void);
#endif
UBYTE	ExistPinNumberAtSelectedBox(UBYTE);  1997/11/07 Y.Matsukuma
*/

/*************************************************************************
	module		:[応用通信セット]
	function	:[
		1.応用通信機能の設定を行う
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		SpecialCommandValue
	]
	condition	:[]
	comment		:[
		 一括送信のパスを追加 1995/05/19 Eguchi
		引数 mode:OPR_COM_OPE/OPR_PRG_OPE
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/20]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE SpecialCommandOperation(UBYTE mode) /*プログラムワンタッチ／応用通信 */
{
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
	UBYTE spe_com_type;

	/******************************************
	** メールアドレス含むときは時刻指定のみ
	******************************************/
	spe_com_type = SelectSpecialCommand(mode);
	if ((CheckDestKindInInputBuffer() == IS_MAIL_ADDRESS)		/** 入力バッファにメールアドレスのみ */
		|| (CheckDestKindInInputBuffer() == IS_MAIL_FAX_DESTINATION)) {	/** 入力バッファにメールアドレスも含まれる */
		if ((spe_com_type != (UBYTE)1)
		&&	(spe_com_type != (UBYTE)0)) {							/** 応用機能の決定 */
			NackBuzzer();
			return(NG);
		}
	}
	switch (spe_com_type) {		/** 応用機能の種類 */
#else
	switch (SelectSpecialCommand(mode)) {	/** 応用機能の決定 */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/05 */
	case 0:	/** ストップ */
		return( NG );

	case 1:	/** 時刻指定 */
		return (DelayedTransmissionOperation(mode));

	case 2:	/** ポーリング */
		return (PollingCommunicationOperation());

#if (PRO_F_CODE == ENABLE)
	case 3:	/** サブアドレス送信 */
		return (FcodeTransmissionOperation());

	case 4:	/** サブアドレス　ポーリング受信 */
		return (FcodePollingOperation());
#endif
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	case 0:	/** ストップ */
		return( NG );

	case 1:	/** 時刻指定 */
		return (DelayedTransmissionOperation(mode));

	case 2:	/** 親展送信 */
		return (SecureTransmissionOperation());

	case 3:	/** 中継指示 */
		return (RelayTransmissionOperation());

	case 4:	/** ポーリング */
		return (PollingCommunicationOperation());

#if (PRO_BATCH_TX == ENABLE)
	case 5:	/** 一括送信 */
		return (BatchTransmissionOperation());
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE)
	case 6:	/** 連続ポーリング */
		return (ContPollingOperation());
#endif

#if (PRO_F_CODE == ENABLE)
	case 7:	/** サブアドレス送信 */
		return (FcodeTransmissionOperation());

	case 8:	/** サブアドレス　ポーリング受信 */
		return (FcodePollingOperation());
#endif

#if (PRO_CIPHER == ENABLE)
	case 9:	/** 暗号化送信 */
		return (CipherTransmissionOperation());
#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	default:
		break;
	}
	return (NG);
}

/*************************************************************************
	module		:[応用機能セット]
	function	:[
		1.応用機能の選択・決定を行う
	]
	return		:[
		０：終了
		１：時刻指定
		２：親展送信
		３：中継指示
		４：ポーリング
		５：一括送信
		６：連続ポーリング
		７：サブアドレス送信
		８：サブアドレス　ポーリング受信
		９：暗号化送信
	]
	common		:[]
	condition	:[]
	comment		:[
		POPLAR_B				POPLAR_L				ANZU_L
		1.時刻指定				1.時刻指定				1.時刻指定
		2.親展送信				2.親展送信				2.親展送信
		3.中継指示				3.中継指示				3.中継指示
		4.ポーリング			4.ポーリング			4.ポーリング
		5.一括送信				5.一括送信				5.一括送信
		6.連続ポーリング		6.連続ポーリング		(6.連続ポーリング)
		7.サブアドレス送信		7.サブアドレス送信
		8.ｻﾌﾞｱﾄﾞﾚｽ ﾎﾟｰﾘﾝｸﾞ受信	8.ｻﾌﾞｱﾄﾞﾚｽ ﾎﾟｰﾘﾝｸﾞ受信
		(9.暗号化送信)

		５番目以降の機能については、機種により不定であるため注意が必要
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/25]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE SelectSpecialCommand(UBYTE mode)
{
	UBYTE	menu_number;	/* 応用通信表示用機能番号（機能に対する番号は不定です） */
	UBYTE	select_item;	/* 応用通信選択中機能番号（機能に対する番号は固定です） */
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ */
	UBYTE	keytype;		/* キー種別 */
	UBYTE	max_count;

	/*------------*/
	/* 初期化処理 */
	/*------------*/
	menu_number = 1;
	select_item = 1;

	/* 最大選択数の計算 */
	max_count = 4;
#if (PRO_BATCH_TX == ENABLE)
	max_count++;
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	max_count++;
#endif
#if (PRO_F_CODE == ENABLE)
	max_count += 2;
#endif
#if (PRO_CIPHER == ENABLE)
	max_count++;
#endif

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_SpecialCommunicationEnter);	/* "       ｵｳﾖｳﾂｳｼﾝ/ｾｯﾄ " */

	/* キーの取り込み処理 */
	while (1) {

		/** 上段表示更新 */
		DisplaySelectSpecialCommand(menu_number, select_item);

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理 */
		switch (keytype) {	/* キータイプで分岐 */
		case KEY_TIME_UP:	/** キー待ちタイムオーバー */
		case STOP:			/** ストップキー */
			/** 終了 */
			select_item = 0;
			return (select_item);
		case SPECIAL:		/** 応用通信キー */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/13 by K.Okada */
			if ((CheckDestKindInInputBuffer() == IS_MAIL_ADDRESS)
			||	(CheckDestKindInInputBuffer() == IS_MAIL_FAX_DESTINATION)) {
				NackBuzzer();
				break;
			}
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/05 */
			/** 応用機能スクロール */
			menu_number++;
			select_item++;

			/* 応用通信キーが押された場面により、有効でない機能を飛ばします */
			if (select_item == 2) {	/* ポーリング受信の場合 */
				if (SpecialCommandValue.Page != 0) {	/* 枚数指定してから応用通信を選択した時 */
					menu_number++;
					select_item++;	/* 枚数指定のポーリングは出来ません */
				}
			}
			if (select_item == 3) {	/* サブアドレス送信の場合 */
#if (PRO_F_CODE == DISABLE)
				select_item++;
#endif
			}
			if (select_item == 4) {	/* サブアドレス　ポーリング受信の場合 */
#if (PRO_F_CODE == ENABLE)
				if (SpecialCommandValue.Page != 0) {	/* 枚数指定してから応用通信を選択した時 */
					menu_number++;
					select_item++;	/* 枚数指定のポーリングは出来ません */
				}
#else
				select_item++;
#endif
			}

			if (menu_number > 4) {	/* 最後まで来たら時刻指定に戻します */
				menu_number = 1;
				select_item = 1;
			}
			break;

#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
			/** 応用機能スクロール */
			menu_number++;
			select_item++;

			/* 応用通信キーが押された場面により、有効でない機能を飛ばします */
			if (select_item == 2) {	/* 親展送信の場合 */
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1997/12/27 Y.Matsukuma */
				if ((CTRY_SecureTx() == 0) || (CMN_CheckCategory2() != 0)) {
					menu_number++;
					select_item++;
				}
#else
				if (CTRY_SecureTx() == 0) {
					menu_number++;
					select_item++;
				}
#endif
			}
			if (select_item == 3) {	/* 中継指示送信の場合 */
				if (CTRY_RelayTx() == 0) {
					menu_number++;
					select_item++;
				}
			}
			if (select_item == 4) {	/* ポーリング受信の場合 */
				if (SpecialCommandValue.Page != 0) {	/* 枚数指定してから応用通信を選択した時 */
					menu_number++;
					select_item++;	/* 枚数指定のポーリングは出来ません */
				}
			}
			if (select_item == 5) {	/* 一括送信の場合 */
#if (PRO_BATCH_TX == ENABLE)
				if (!OPR_BatchTxEnableFlag) {	/* 一括送信不可能（プログラムワンタッチの場合) */
					menu_number++;
					select_item++;
				}
				/* 一括送信では通常のコマンドファイルを使用していない為に、枚数指定をしても無効なので
				** ポーリングと同様に選択できなくします by K.Watanabe 1998/04/15
				*/
				else if (SpecialCommandValue.Page != 0) {	/* 枚数指定してから応用通信を選択した時 */
					menu_number++;
					select_item++;	/* 枚数指定の一括送信は出来ません */
				}
#else
				select_item++;
#endif
			}
			if (select_item == 6) {	/* 連続ポーリングの場合 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
				if (mode == OPR_PRG_OPE) {	/* 連続ポーリング不可能（プログラムワンタッチの場合) */
					menu_number++;
					select_item++;
				}
				else if (SpecialCommandValue.Page != 0) {	/* 枚数指定してから応用通信を選択した時 */
					menu_number++;
					select_item++;	/* 枚数指定のポーリングは出来ません */
				}
#else
				select_item++;
#endif
			}
			if (select_item == 7) {	/* サブアドレス送信の場合 */
#if (PRO_F_CODE == DISABLE)
				select_item++;
#endif
			}
			if (select_item == 8) {	/* サブアドレス　ポーリング受信の場合 */
#if (PRO_F_CODE == ENABLE)
				if (SpecialCommandValue.Page != 0) {	/* 枚数指定してから応用通信を選択した時 */
					menu_number++;
					select_item++;	/* 枚数指定のポーリングは出来ません */
				}
#else
				select_item++;
#endif
			}
			if (select_item == 9) {	/* 暗号化送信の場合 */
#if (PRO_CIPHER == ENABLE)
				if (!ScrambleOn) {	/* ＲＯＭスイッチがＯＦＦの時 */
					menu_number++;
					select_item++;
				}
#else
				select_item++;
#endif
			}

			if (menu_number > max_count) {	/* 最後まで来たら時刻指定に戻します */
				menu_number = 1;
				select_item = 1;
			}
			break;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case ENTER:			/** セットキー (応用通信決定) */
			switch (select_item) {	/* 選択した種類を判断します */
			case 1:	/* 時刻指定を選択した時 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
				if (SpecialCommandValue.CommandOption.Item == SYS_CONTINUOUS_POLLING) {
					/* 時刻指定の前に、連続ポーリングが設定されている時は、選択を禁止します by K.Watanabe 1997/11/29 */
					NackBuzzer();
				}
				else {
					return (select_item);
				}
#else
				return (select_item);
#endif
				break;
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* by K.Watanabe 1997/10/24 */
			case 6:	/* 連続ポーリングを選択した時 */
				if ((mode == OPR_COM_OPE) && (SYB_ContinuousPolling.Status != SYS_CMD_EMPTY)) {
					/* 送信時に連続ポーリングを選択したが、連続ポーリングが予約・実行中の時は、選択を禁止します */
					NackBuzzer();
				}
				else {
					return (select_item);
				}
				break;
#endif
			default:
				return (select_item);
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
	module		:[応用機能選択中の表示]
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
	date		:[1995/07/07]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplaySelectSpecialCommand(UBYTE menu_number, UBYTE select_item)
{
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/05 */
	switch (menu_number) {
		case 1:	/** 時刻指定 */
			CMN_StringCopyNULL(FunctionDisplayBufferHigh,
							   D2W_SetDelayedTransmission + (OPR_WORDING_LEN * (select_item - 1)));	/*"  ｼﾞｺｸｼﾃｲ ｿｳｼﾝ	  "*/
			break;
		case 2:	/** ポーリング */
			CMN_StringCopyNULL(FunctionDisplayBufferHigh, D2W_SetPolling);	/*"  ﾎﾟｰﾘﾝｸﾞ           "*/
			break;
	#if (PRO_F_CODE == ENABLE)
		case 3:	/** サブアドレス送信 */
			CMN_StringCopyNULL(FunctionDisplayBufferHigh, D2W_SetFcodeTransmission);	/*"  Fｺｰﾄﾞ ｿｳｼﾝ        "*/
			break;
		case 4:	/** サブアドレス　ポーリング受信 */
			CMN_StringCopyNULL(FunctionDisplayBufferHigh, D2W_SetFcodePolling);	/*"  Fｺｰﾄﾞ ﾎﾟｰﾘﾝｸﾞ     "*/
			break;
		default:
			break;
	#endif
	}
	FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(menu_number);
	FunctionDisplayBufferHigh[1] = '.';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	CMN_StringCopyNULL(FunctionDisplayBufferHigh,
					   D2W_SetDelayedTransmission + (OPR_WORDING_LEN * (select_item - 1)));	/*"  ｼﾞｺｸｼﾃｲ ｿｳｼﾝ	  "*/
	FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(menu_number);
	FunctionDisplayBufferHigh[1] = '.';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[時刻指定送信の登録]
	function	:[
		1.応用通信機能の時刻指定送信の登録を行う
		2.指定時刻の入力を行う
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		SpecialCommandValue
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/20]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE DelayedTransmissionOperation(UBYTE mode)	/*プログラムワンタッチ／原稿送信ダイヤル*/
{
	UBYTE	ret;

	DisplayStringHigh(0, D2W_DelayedTransmission);	/* "ｼﾞｺｸｼﾃｲ ｿｳｼﾝ        " */

	if (mode == OPR_COM_OPE) {		/* 応用通信/予約 */
		ret = DelayedTransmissionTimeInput();
	}
	else {/*mode == OPR_PRG_OPE*/	/* プログラムワンタッチ登録中に応用通信キーが押された */
		ret = ProgramTimeInput();
	}

	if ((ret == OK) && (SpecialCommandValue.CommandOption.Item == SYS_CHAR_TX)) {
		/** 時刻が入力され（ExecTimeが０でない）、今まで応用機能がセットされていない */
		SpecialCommandValue.CommandOption.Item = SYS_DELAYED_SCANNER_TX;
	}

	return(ret);
}

/*************************************************************************
	module		:[送信時刻セット]
	function	:[
		1.時刻指定送信を行う際の送信時刻の入力を行う
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
UBYTE DelayedTransmissionTimeInput(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UDWORD	time;

	time = 0;

	/*----------------------*/
	/** 	初期化処理 		*/
	/*----------------------*/
	ClearCharacterInput();
	if (BackUpCurrentTimeSet == 0) {
		/*------------------------------------------------------*/
		/* 指定時刻のセットを開始した時の現在時刻を退避しておく */
		/* 以下、入力チェック等はこの時刻を基準におこなう		*/
		/* 時間入力中にCurrentTimeが更新されても即時発呼を可能にするための処理 */
		/*---------------------------------------------------------------------*/
		BackUpCurrentTime = SYB_CurrentTime;
		BackUpCurrentTimeSet = 1;
	}
	if (SpecialCommandValue.CommandTime == 0) { /* 前回登録値がない場合 */
		time = BackUpCurrentTime;
	}
	else {
		time = SpecialCommandValue.CommandTime*60;
	}
	/** ロング型時間を編集形式に直す */
	SetLongTimeToCharacterInput(time , COMMAND_TIME_TYPE);

	CharacterInput.WritePosition = 5;
	CharacterInput.LcdDisplayPosition = 11;
	CharacterInput.FixedWordingLow = (UBYTE *)D2W_EnterDelayedTxTime;

	/* 編集　*/
	while (1) {
		/* 表示処理 */
		DisplayTimeInput(COMMAND_TIME_TYPE);

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:	/* 数字（0 - 9) */
			FixedNumberDataSet(key);
			break;
		case STOP:				/* ストップキー　	  */
		case KEY_TIME_UP:			/* １分間キー入力なし */
			CursorOff();
			return (NG);
		case FUNCTION:	/* カーソルー＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 		/* カーソル＜ー　キー */
			CursorLeftRotation();
			break;
		case ENTER:		/* セットキー */
			/* 入力データのチェック及びセットを行う */
			if (CheckAndCalculateCommandTime() == OK) {
				CursorOff();
				return (OK);
			}
			CharacterInput.CursorPosition = 0;
			NackBuzzer();
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[積算分計算]
	function	:[
		　1.時刻指定送信で指定された時刻の基準（1992年1月1日0時0分)からの
		　　積算"分"数を計算する。
	return		:[]
	common		:[
		SYB_CurrentTime:
	]
	condition	:[]
	comment		:[コマンドファイルにセットする時間の計算を行う]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
UBYTE CheckAndCalculateCommandTime(void)
{
	/*----------------------------------------------------------*/
	/* 送信指定時刻が現在時刻よりも前かどうかをチェックする		*/
	/* 送信時刻のほうが前であれば翌月の送信時刻に送信することに */
	/* なるので、翌月に指定日が存在するかをチェックする。		*/
	/* 指定日がない場合ＮＧとする.								*/
	/* 送信時刻が現在時刻よりも後の場合は、その月に指定された日 */
	/* があるかチェックする。なければＮＧとする					*/
	/* 原稿送信のための時刻指定の場合に限る。プログラムワンタッチ*/
	/* の時刻指定の場合は関係ない(プログラムワンタッチが使用	*/
	/* された時点での時間が問題になってくる	)					*/
	/*---------------------------------------------------------*/

	/************************************************************************************************
	 * 仕様																							*
	 *    1.送信時刻が現在時刻よりも前の場合、翌月の指定時刻に送信する。							*
	 *    2.送信時刻が現在時刻以降の場合で、指定日が現在の月に存在しない場合、翌月の指定時刻に		*
	 *      送信を行う。																			*
	 *    3.上記以外の場合、指定された時刻に送信を行う												*
     ************************************************************************************************/
	UBYTE	max_day;
	UBYTE	next_max_day;
	UBYTE	next_month;
	UBYTE	input_day;
	UBYTE	input_hour;
	UBYTE	input_minute;
	UBYTE	current_year;
	UBYTE	current_month;
	UBYTE	current_day;
	UBYTE	current_hour;
	UBYTE	current_minute;
	UBYTE	next;
	UDWORD	add_minute;		/* 現在時刻から。送信時刻までの差分"分"数 */

	next = 0;

	input_day    = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 2);
	input_hour   = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[2], 2);
	input_minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2);

	if ((input_day    < 1  )   /* 0日という指定はできない */
	||	(input_day 	  > 31 )
	||	(input_hour   > 23 )
	||	(input_minute > 59 )) { /* 最大最小値の間に収まっていない */
		return (NG);
	}

	/* 現在時刻の取り出し */
	CMN_LongTimeToBCD((TIME_DATA_t *)&OperationTime.BCD_StructTime.Year , BackUpCurrentTime);
	current_year   = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Year);
	current_month  = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Month);
	current_day    = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Date);
	current_hour   = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Hour);
	current_minute = CMN_BCD_ToDecimal(OperationTime.BCD_StructTime.Minute);

	/** 翌月の日数を計算 */
	next_month = (UBYTE)(current_month + 1);
	if (next_month > 12) {
		next_month = 1;
	}
	/* 翌月が次の年の１月で、かつ翌年が閏年の場合でも１月の日数は変わらない */
	/* のでＹｅａｒの値は変えなくても差し支えない */
	next_max_day = GetDayFromMonth(current_year , next_month);

	/** その月の最大日数を計算 */
	max_day = GetDayFromMonth(current_year , current_month);

	if ((input_day > current_day)&&(input_day > max_day)) { /**その月に存在しない月をセットされた場合*/
		return (NG);/*この場合送信できない */
	}
	if (( input_day <  current_day)
	||  ((input_day == current_day)&&(input_hour <  current_hour))
	||  ((input_day == current_day)&&(input_hour == current_hour)&&(input_minute < current_minute))) {
		/* 入力された指定日が現在時刻よりも前 */
		/* 入力された指定日に該当する日がない */
		/* -> 翌月に送信 */
		if (input_day > next_max_day) { /** 指定された日が翌月に存在しない場合 */
			return (NG); /* この場合送信できない */
		}
		else {
			next = 1;
		}
	}
	/** 送信時刻と現在時刻の差分を求める */
	/* 翌月に送信する場合の加算分数 */
	add_minute = (UDWORD)max_day * next;
	add_minute *= 1440;
	/* 月始めから入力された時間までの積算分数 */
	add_minute += TotalMinutesFromMonthHead((UBYTE)(input_day - 1), input_hour, input_minute);
	/* 月始めから現在時刻までの積算分数 */
	add_minute -= TotalMinutesFromMonthHead((UBYTE)(current_day - 1), current_hour, current_minute);

	/** 基準から指定時刻までの積算"分”を計算 */
	SpecialCommandValue.CommandTime = 0x00000000UL;
	SpecialCommandValue.CommandTime = add_minute + BackUpCurrentTime/60  ; /* add_minute:現在時刻から送信時刻までの積算分 */
	return (OK);
}

/*************************************************************************
	module		:[月始めから指定された時刻までの積算分を計算]
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
UDWORD TotalMinutesFromMonthHead(UBYTE day, UBYTE hour, UBYTE minute)
{
	UWORD	temp;
	UDWORD	total_minute;

	total_minute = 0x00000000UL;
	temp = 0;

	temp = (UWORD)day;

	total_minute = (UDWORD)(day * 24 + hour);
	total_minute *= 60;
	total_minute += (UDWORD)minute;

	return (total_minute);
}

/************************************************************************
	module		:[プログラム指定時刻のセット]
	function	:[
		1.プログラムワンタッチ登録、一括送信ボックス登録の際の指定時刻の入力を行う
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
************************************************************************/
UBYTE ProgramTimeInput(void)
{
	UBYTE	key;
	UBYTE	keytype;

	/*------------------------*/
	/**   初期化処理 		  */
	/*------------------------*/
	ClearCharacterInput();

	if (SpecialCommandValue.CommandTime == 0) { /* 前回登録値がない場合 */
		/** 現在時刻を編集形式に直す */
		SetLongTimeToCharacterInput(SYB_CurrentTime, COMMAND_TIME_TYPE);
	}
	else {
		if (SpecialCommandValue.CommandTime & 0x80000000UL) {
			SpecialCommandValue.CommandTime &= ~0x80000000UL;
		}
		SetSpecialTimeToCharacter();
	}
	CharacterInput.WritePosition = 5;
	CharacterInput.LcdDisplayPosition = 11;
	CharacterInput.FixedWordingLow = (UBYTE *)D2W_EnterDelayedTxTime;

	/* 編集　*/
	while (1) {
		/* 表示処理 */
		DisplayTimeInput(COMMAND_TIME_TYPE);

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:		/* 数字（0 - 9) */
			FixedNumberDataSet(key);
			break;
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			CursorOff();
			return (NG);
		case FUNCTION:		/* カーソルー＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 	/* カーソル＜ー　キー */
			CursorLeftRotation();
			break;
		case ENTER:			/* セットキー */
			/* 入力データのチェックを行う */
			if (CheckAndSetProgramTime() == OK) {
				CursorOff();
				return (OK);
			}
			CharacterInput.CursorPosition = 0;
			NackBuzzer();
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[プログラム時刻の正誤のチェック]
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
UBYTE CheckAndSetProgramTime(void)
{
	UBYTE	trans_day;
	UBYTE	trans_hour;
	UBYTE	trans_minute;

	trans_day    = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 2);
	trans_hour   = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[2], 2);
	trans_minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2);

	if ((trans_day    > 31)	/* 0日という指定はできる */
	||	(trans_hour   > 23)
	||	(trans_minute > 59)) { /* 最大最小値の間に収まっていない */
		return (NG);
	}
	SpecialCommandValue.CommandTime = TotalMinutesFromMonthHead(trans_day , trans_hour , trans_minute);
	if (trans_day == 0) { /* ０日が指定された場合 */
		SpecialCommandValue.CommandTime |= 0x80000000UL; /* ０日０時０分と未登録の０を区別するため */
	}
	return (OK);
}

/*************************************************************************
	module		:[時間入力中の表示]
	function	:[
		1.入力用バッファの内容を表示用になおして表示する
	 	,	A.カレンダー入力の場合
	 	,		「年月日時分」の形で入力されているのもを「'年　月／日　時：分」の形に
	 	,	 	なおして表示。
	 	,		1995年6月30日16時10分の場合
	 	,									   012345678901234
	 	,			CharacterInput.Buffer	= "9506301610"
	 	,			FunctionDisplayBuffer	= "'95 06/30 16:10"
		,									   |
	 	,									   disp_start_position
	 	,		「年月日」のみの形で入力されているのもを「'年　月／日」の形に
	 	,	 	なおして表示。
	 	,		1995年6月30日16時10分の場合
	 	,									   012345678901234
	 	,			CharacterInput.Buffer	= "950630"
	 	,			FunctionDisplayBuffer	= "'95 06/30"
		,									   |
	 	,									   disp_start_position
 	  	,	B.送信指定時刻入力の場合
	  	,		「日時分」の形で入力されているのもを「日／時：分」の形に
	    ,		なおして表示。
	 	,		30日16時10分の場合
	 	,									   012345678901234
	 	,			CharacterInput.Buffer	= "301610"
	 	,			FunctionDisplayBuffer	= " 30/16:10"
	 	,									   |
	 	,									   disp_start_position
		,
		,
		,	C.セキュリティ受信モード開始時刻入力の場合
		,		「時分」の形で入力されているものを「時：分」の形になおして
		,		表示
		,		19時10分の場合
		,									   01234567890123456789
		,			CharacterInput.Buffer	= "1910"
		,			FunctionDisplayBuffer	= " 19:10"
		,									   |
		,									   disp_start_position

	]
	return		:[]
	common		:[
					CharacterInput
					FunctionDisplayBuffer
				]
	condition	:[]
	comment		:[
				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/03]
	author		:[江口]
*************************************************************************/
void DisplayTimeInput(UBYTE type)
{
	UBYTE	i;
	UBYTE	disp_position;
	UBYTE	cursor;

	disp_position = CharacterInput.LcdDisplayPosition;

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	if (CharacterInput.FixedWordingLow != NULL) {/*下段固定文字列がある */
		CMN_StringCopy(FunctionDisplayBufferLow, CharacterInput.FixedWordingLow);
	}
	/* 入力バッファの内容を表示形式に変換 */
	for (i = 0; (CharacterInput.Buffer[i] != NULL)&&(CharacterInput.Buffer[i] != ' '); i++) { /* 入力バッファの最後まで */
		if (i % 2 == 0) { /* 偶数位置の場合 */
			FunctionDisplayBufferLow[disp_position + ((i / 2) * 3 + 1)] = CharacterInput.Buffer[i];
		}
		else { /*奇数位置の場合 */
			FunctionDisplayBufferLow[disp_position + ((i / 2) * 3 + 2)] = CharacterInput.Buffer[i];
		}
	}

	/* カーソル位置の計算 */
	if (CharacterInput.CursorPosition % 2) { /* 奇数位置の場合 */
		cursor = (UBYTE)((CharacterInput.CursorPosition / 2) * 3 + 2);
	}
	else {	/* 偶数位置の場合 */
		cursor = (UBYTE)((CharacterInput.CursorPosition / 2) * 3 + 1);
	}

	/* 数字と数字の間の区切り文字をセット */
	switch (type) {
	case CALENDER_TYPE:
		FunctionDisplayBufferLow[disp_position + 0]  = '\'';
		FunctionDisplayBufferLow[disp_position + 3]  = ' ';
		FunctionDisplayBufferLow[disp_position + 6]  = '/';
		FunctionDisplayBufferLow[disp_position + 9]  = ' ';
		FunctionDisplayBufferLow[disp_position + 12] = ':';
		break;
	case CALENDER_DATE_TYPE:
		FunctionDisplayBufferLow[disp_position + 0]  = '\'';
		FunctionDisplayBufferLow[disp_position + 3]  = ' ';
		FunctionDisplayBufferLow[disp_position + 6]  = '/';
		break;
	case COMMAND_TIME_TYPE:
		FunctionDisplayBufferLow[disp_position + 0] = ' ';
		FunctionDisplayBufferLow[disp_position + 3] = '/';
		FunctionDisplayBufferLow[disp_position + 6] = ':';
		break;
	case SECURITY_RX_TIME_TYPE:
	case CONT_POLLING_RX_TIME_TYPE:
		FunctionDisplayBufferLow[disp_position + 0] = ' ';
		FunctionDisplayBufferLow[disp_position + 3] = ':';
		break;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/13 by K.Okada */
	case AUTO_MAIL_RX_TIME_TYPE: /* 自動メール受信開始／終了時刻 */
		FunctionDisplayBufferLow[disp_position + 0] = ' ';
		FunctionDisplayBufferLow[disp_position + 3] = ':';
		CMN_StringCopyNULL((UBYTE *)&FunctionDisplayBufferLow[0] , 
						   (UBYTE *)&FunctionDisplayBufferLow[1]);
		cursor--;
		break;
#endif
	}
	DisplayStringLow(0, FunctionDisplayBufferLow);
	CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + cursor + disp_position));
}

/*************************************************************************
	module		:[親展送信の登録]
	function	:[
		1.応用通信機能の親展送信の登録を行う
		2.親展番号の入力を行う
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/20]
	author		:[江口]
*************************************************************************/
UBYTE SecureTransmissionOperation(void)
{
	DisplayStringHigh(0, D2W_SecureTransmission);	/* "ｼﾝﾃﾝ ｿｳｼﾝ           " */
	if (NumberInput(OPR_TX_MAIL_BOX_NUMBER_INPUT) == OK) {
		SpecialCommandValue.CommandOption.Item = SYS_SCANNER_SECURE_TX;
		SpecialCommandValue.CommandOption.OptionNumber.SecureNumber = CharacterInputToNumber();
		return( OK );
	}
	return (NG);
}

/*************************************************************************
	module		:[応用通信、中継指示送信オペレーション]
	function	:[
		1.応用通信の中継指示送信のオペレーションを行う。
		2.中継同報の宛先（グループ番号）の入力までを行う
	]
	return		:[実行結果		０：登録中断	１：登録完了]
	common		:[]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
UBYTE RelayTransmissionOperation(void)
{
	UDWORD	group_number;

	group_number = 0;

	if (SpecialCommandValue.CommandOption.Item == SYS_SCANNER_RELAY_BROADCAST) {
		/* 既に一回中継指示送信がセットされている場合 */
		group_number = SpecialCommandValue.CommandOption.OptionNumber.RelayGroupNumber;
	}

	DisplayStringHigh(0, D2W_RelayTransmission);	/* "ﾁｭｳｹｲｼｼﾞ ｿｳｼﾝ      " */

	if (GroupNumberInput(OPR_RELAYGROUP_NUMBER_INPUT, group_number) == OK) {
		SpecialCommandValue.CommandOption.Item = SYS_SCANNER_RELAY_BROADCAST;
		SpecialCommandValue.CommandOption.OptionNumber.RelayGroupNumber = 0x00000000UL;
		SpecialCommandValue.CommandOption.OptionNumber.RelayGroupNumber = StoreCharacterInputToLongGroup();
		return(OK);
	}
	return (NG);
}

/*************************************************************************
	module		:[応用通信ポーリングオペレーション]
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
	date		:[1996/01/06]
	author		:[江口]
*************************************************************************/
UBYTE PollingCommunicationOperation(void)
{
	UBYTE	key;	/* ｷｰ取り込みﾃﾞｰﾀ */

	if (CTRY_DB_PolingRx() == 0) {/* 検索ポーリングなし */
		CMN_MemorySet(CharacterInput.Buffer, OPR_CHARACTER_INPUT_MAX + 1, NULL);
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/05 */
		CharacterInput.WritePosition = 0; /* add by SMuratec H.C.H 2003/10/11 初期化*/
		PollingOptionSet();
		CursorOff();
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		return (OK);
	}
	else {
		DisplayStringHigh(0 , D2W_PollingCommunication);	/*"ﾎﾟｰﾘﾝｸﾞ			 "*/
		DataBaseInputInitial();
		/*******************/
		/**  キー取り込み **/
		/*******************/
		while (1) {
			/** 表示処理 */
			DisplayNumberInput();

			/** キー取り込み */
			key = NumberInputKeyGet();
			switch (key) {
			case STOP_KEY:			/* ストップキー */
				/** 終了 */
				CursorOff();
				return (NG);
			case SET_KEY:			/* セットキー	*/
				if (CheckDataBasePollingInput() == OK) {
					PollingOptionSet();
					CursorOff();
					return (OK);
				}
				else {
					NackBuzzer();
				}
				break;
			case SPECIAL_KEY:		/* 応用通信キー */
				if ((CharacterInput.Buffer[CharacterInput.CursorPosition	] != ',')
				 && (CharacterInput.Buffer[CharacterInput.CursorPosition - 1] != ',')
				 && (CheckCharacterInputEmpty() == FALSE)) {
					CharacterDataSet_FigureCheck(',');
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
}

/*************************************************************************
	module		:[ポーリングデータ初期値取り出し]
	function	:[
		1.検索ポーリングのファイある番号を編集できる形式に直す
	]
	return		:[]
	common		:[
		SpecialCommandValue
		CharacterInput
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/08/09]
	author		:[江口]
*************************************************************************/
void DataBaseInputInitial(void)
{
	UBYTE	i;
	UBYTE	position;

	position = 0;

	ClearCharacterInput();
	CharacterInput.LcdDisplayPosition = 12;
	CharacterInput.MaxFigure = OPR_CHARACTER_INPUT_MAX;
	CharacterInput.FixedWordingLow = (UBYTE *)D2W_InputFileNumber;	/* "ﾌｧｲﾙ ﾊﾞﾝｺﾞｳ:        " */

	if (SpecialCommandValue.CommandOption.Item == SYS_DB_POLLING_RX) { /** 既にポーリングファイル番号がセットされている */
		for ( i = 0; i < SYS_DATA_BASE_MAX; i++ ) {
			if (SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber[i] != 0xffff) {
				if (position != 0) {
					CharacterInput.Buffer[position] = ',';
					position++;
				}
				CMN_UnsignedIntToASC(&CharacterInput.Buffer[position],
				 					 SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber[i],
				  					 DB_FILE_DIGIT_MAX,
				  					 '0');
				position += DB_FILE_DIGIT_MAX;
			}
			else {
				break;
			}
		}
	}
	CharacterInput.WritePosition = CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
}

/*************************************************************************
	module		:[ポーリングデータ入力値チェック]
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
	date		:[1995/04/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckDataBasePollingInput(void)
{
	UBYTE	location_count;
	UBYTE	length;

	length = 0;
	location_count = 0;

	/* 未入力状態チェック */
	if (CheckCharacterInputEmpty() == TRUE) {
		return (OK);
	}
	CharacterInput.CursorPosition = 0;
	while (1) {
		if (CharacterInput.Buffer[CharacterInput.CursorPosition] == NULL) {
			return (OK);
		}
		else {
			if (location_count >= (UBYTE)(SYS_DATA_BASE_MAX - 1)) { /* 既に１０箇所入力されている */
				OPR_ChildErrorFlag = TOO_MANY_LOCATION_ERROR;
				return (NG);
			}
			length = SetToCheckBuffer(&CharacterInput.Buffer[CharacterInput.CursorPosition], ',');
			if (length == 0) { /* ,と,の間にデータがない */
				/* エラーコードのセット */
				OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
				return (NG);
			}
			else {
				if (CheckDataBaseFileNumber() == OPR_NO_ERROR) {	/* エラーなし */
					CharacterInput.CursorPosition += length;
					if (CharacterInput.Buffer[CharacterInput.CursorPosition] == ',') { /* カーソル上にコンマあり */
						CharacterInput.CursorPosition++;
					}
					location_count++;
				}
				else {												/* エラーあり */
					/* エラーコードのセット */
					OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;
					CharacterInput.CursorPosition += ErrorPositionSet();
					return (NG);
				}
			}
		}
	}
}

/*************************************************************************
	module		:[データベース番号のチェック]
	function	:[
		1.入力されたデータベースポーリングのファイル番号をチェックする
	]
	return		:[]
	common		:[OPR_CharacterCheckBuffer:チェック用バッファ]
	condition	:[チェックする対象となるデータをあらかじめチェック用のバッファにいれておくこと]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/24]
	author		:[江口]
*************************************************************************/
UBYTE CheckDataBaseFileNumber(void)
{
	OPR_CharacterCheckPoint = 0;
	return (CheckNumberFigureRange(DB_FILE_DIGIT_MAX, 0, DATABASE_NUMBER_MAX));
}

/*************************************************************************
	module		:[ポーリングデータセット]
	function	:[
		1.検索ポーリングかただのポーリングか判断する
		2.検索ポーリング場合、ファイル番号を計算する
	]
	return		:[なし]
	common		:[
		SpecialCommandValue:
	]
	condition	:[]
	comment		:[
		元となるデータは検査済みであることが大前提である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
void PollingOptionSet(void)
{
	/* データーベース番号をクリアしておく */
	CMN_WordMemorySet(SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber,
					  (UWORD)SYS_DATA_BASE_MAX,
					  (UWORD)0xFFFF);
	/* ただのポーリング */
	if (CheckCharacterInputEmpty() == TRUE) {
		SpecialCommandValue.CommandOption.Item = SYS_POLLING_RX;
	}

	/* 検索ポーリング */
	else {
		SpecialCommandValue.CommandOption.Item = SYS_DB_POLLING_RX;
		/*-----------------------------*/
		/* ファイル番号をセットする　　*/
		/*-----------------------------*/
		StoreCharacterInputToDatabase(SpecialCommandValue.CommandOption.OptionNumber.DatabaseNumber);
	}
}

#if (PRO_BATCH_TX == ENABLE)
/*************************************************************************
	module		:[応用通信一括送信登録]
	function	:[
		1.一括送信オペレーション実行
		2.一括送信の場合はコマンドファイルを掴むことはないし
		　相手先番号の登録も必要ないので、注意する事.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[原稿登録の時は、たとえＰＩＮアクセスがＯｎであってもＰＩＮ番号の
				　有無のチェックは行わない。]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/20]
	author		:[江口]
*************************************************************************/
UBYTE BatchTransmissionOperation(void)
{
	UBYTE	box_no;
	UBYTE	index_no;
	UBYTE	box_status;

	DisplayStringHigh(0, D2W_BatchTransmission);

	if( InputNumber.InputDialType == PROGRAM_DIAL_TYPE ){	/* プログラムワンタッチ登録時 */
		while (1) {
			if (NumberInput(OPR_PRG_BATCH_BOX_INPUT) == NG) { /*STOP */
				return (NG);
			}
			box_no = (UBYTE)CharacterInputToNumber();
			box_no -= OPR_BATCH_FILE_MIN;
	 		if (CheckBatchTxFileStatus(box_no) == BATCH_BOX_NOT_ENTRY) {
				NackBuzzer();
				OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
			}
			else {
				SpecialCommandValue.CommandOption.OptionNumber.BatchNumber = box_no;
				SpecialCommandValue.CommandOption.Item = SYS_BATCH_MEMORY_TX;
				return (OK);
			}
		}
	}
	else {
		/*--------------------------*/
		/**	   ボックス番号入力 	*/
		/*--------------------------*/
		if (NumberInput(OPR_BATCH_BOX_NUMBER_INPUT) == NG) { /* 登録中止 STOP */
			return (NG);
		}
		/* ボックス番号の計算 */
		box_no = (UBYTE)CharacterInputToNumber();
		box_no -= OPR_BATCH_FILE_MIN;
	}

	box_status = CheckBatchTxFileStatus(box_no);
	/*-----------------------------------------*/
	/** 一括送信原稿が登録できるかどうか調べる */
	/*-----------------------------------------*/
	switch (box_status) {
	case BATCH_BOX_NOT_ENTRY:/** 未登録 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
		return (NG);

	case BATCH_BOX_STORING: /** 蓄積中 */
	case BATCH_BOX_EXECUTE: /** 実行中 */
	case BATCH_BOX_ERASED:  /** 消去中 */
	case BATCH_BOX_POWER_OFF:/** 電源断検出 */
		NackBuzzer();
		return (NG);

	case BATCH_BOX_EMPTY:	/** 未使用 */
	case BATCH_BOX_WAITING: /** 予約中 */
		if (box_status == BATCH_BOX_EMPTY) {/** 未使用の場合 */
#if (0)	/* この文を下の処理にさしかえます 1997/11/08 Y.Matsukuma */
			/** インデックスを初期化する */
			CMN_WordMemorySet(SYB_BatchTxFile[box_no].IndexNo, SYS_BATCH_INDEX_MAX, SYS_BAT_DOC_EMPTY);
			index_no = 0;
#endif
			if (ExistPinNumberAtSelectedBox(box_no) == TRUE) {
				/** インデックスを初期化する */
				CMN_WordMemorySet(SYB_BatchTxFile[box_no].IndexNo , SYS_BATCH_INDEX_MAX , SYS_BAT_DOC_EMPTY);
				index_no = 0;
			}
			else {
				NackBuzzer();
				OPR_ChildErrorFlag = NO_PIN_NUMBER_ERROR;
				return (NG);
			}
		}
		else { /** 原稿蓄積すみの場合　*/
			for (index_no = 0; index_no < SYS_BATCH_INDEX_MAX; index_no++) {
				/** インデックスの空きを検索する */
				if (SYB_BatchTxFile[box_no].IndexNo[index_no] == SYS_BAT_DOC_EMPTY) { /* STORINGはここではないと思う */
					break;
				}
			}
			if (index_no == SYS_BATCH_INDEX_MAX) { /** すべて蓄積されている */
				/** 終了　*/
				NackBuzzer();
				/*OPR_ChildErrorFlag = BATCH_DOCUMENT_FULL_ERROR;*/
				return (NG);
			}
		}
		/** ボックス番号と受け付け番号をユーザーに確認させ、
			スタートキーを押させるオペレーションを行う 		*/
		return (FinalBatchTxOperation(box_no, index_no));
	}
}

/*************************************************************************
	module		:[一括送信最終処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		一括送信は部門管理の対象からはずす
		一括送信時に使用するＰＩＮ番号はＰＩＮアクセスモードに関係なく、
		一括送信時の相手先固有に登録されているＰＩＮ番号とする. TBD
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/10/12]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE FinalBatchTxOperation(UBYTE box_no, UBYTE index_no)
{
	UBYTE	key;
	UBYTE	keytype;
#if (PRO_FBS == ENABLE)
	UBYTE	last_key;		/* 前回キー入力値 */
#endif
	UBYTE	box_status;
	UBYTE	is_loop_end;
	UBYTE	ret;

	/* オペレーション中に実行中にならないようにステータスを書き換えておく */
	box_status = SYB_BatchTxFile[box_no].Status;
	SYB_BatchTxFile[box_no].Status = SYS_CMD_SETTING;

#if (PRO_FBS == ENABLE)
	last_key = OPR_NO_KEY;
#endif
	is_loop_end = FALSE;
	ret = NG;

	while (is_loop_end != TRUE) {
		DisplayFinalBatchTx(box_no ,index_no);

		/** キーを取り込む */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:	/** １分間キー入力なし */
		case STOP:			/** ストップキー */
			is_loop_end = TRUE;
			break;
		case START:			/** スタートキー */
			/* 蓄積できる状態かを調べます */
			if (CheckScanStartEnable(OPR_DOC_SET_CHK_ONLY) == OPR_SCAN_ENABLE) {	/* 原稿読み取り可能な時 */
				/* 原稿読み取り不可能な時（ブック原稿サイズ未設定も含む）は、一度このループに戻ります */

#if (0)	/* Add By O.Kimoto 1999/07/19 */
** 				if (CheckMemoryOver() == FALSE) [
#else
				if ((CheckMemoryOver() == FALSE) && (CheckScanDisableCondition() == FALSE)) {
#endif

					if (box_status == SYS_CMD_EMPTY) {	/**初めて原稿を登録する場合 */
						/** 送信指定時刻をセット */
						SpecialCommandValue.CommandTime = 0x00000000UL;
						GetProgramTime(SYB_BatchTxFile[box_no].ProgramTime);
						CalculateProgramExecTime();
						SYB_BatchTxFile[box_no].ExecTime = SpecialCommandValue.CommandTime * 60;
					}
					/** ボックスの使用状況を蓄積中にセットする */
					SYB_BatchTxFile[box_no].Status = SYS_CMD_SETTING; /* 蓄積中をセット */
					SpecialCommandValue.CommandOption.Item = SYS_BATCH_MEMORY_TX;

					/** メインタスクに原稿蓄積起動のメッセージを送信 */
					OperationMessageToMain.Message = MSG_STORE_MEMORY_BATCH_TX_DOC;
					OperationMessageToMain.SubMessage1 = box_no;
					OperationMessageToMain.SubMessage2 = index_no;
					snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
					MainTaskExecWait();
					ret = OK;
#if (PRO_FBS == ENABLE)	/* by K.Watanabe 1998/01/28 */
					if (InputNumber.InputDialType == COMMAND_DIAL_TYPE) {	/* コマンド入力の時 */
						IsTxOrScanStart = TRUE;	/* 送信・原稿読み取り開始 */
					}
#endif
				}
				else {
					NackBuzzer();
				}
				is_loop_end = TRUE;
			}
			else {
				NackBuzzer();
			}
			break;
#if (PRO_FBS == ENABLE)
		case BOOK_DOC_SIZE:	/* ブック原稿サイズキー		*/
			BookDocumentSizeSet(OPR_COM_OPTION_OPE, last_key);
			break;
#endif
		case SINGLE:
			SingleKeyOperation(key);
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}

#if (PRO_FBS == ENABLE)
		last_key = key;	/* 前回キー入力値の退避 */
#endif
	}

	if (ret == NG) {
		/** ボックスの使用状況を元に戻して終了 */
		SYB_BatchTxFile[box_no].Status = box_status;
	}
	return(ret);
}

/*************************************************************************
	module		:[]
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
	date		:[]
	author		:[]
*************************************************************************/
void DisplayFinalBatchTx(UBYTE box_no, UBYTE index_no)
{
	if (CheckChildErrorDisplayReq() == TRUE) {/** チャイルド表示すべきエラーが発生した */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) { /** チャイルド表示中*/
		return;
	}
													/*  01234567890123456789  */
	DisplayStringHigh(0, D2W_PressStart);			/* [ｽﾀｰﾄｷｰ ｦ ﾄﾞｳｿﾞ      ] */
	DisplayStringLow(0, D2W_BatchBoxIndexNumber);	/* [ﾎﾞｯｸｽ: 9  ﾌｧｲﾙ:  99 ] */
	DisplayChar((UBYTE)27, ChangeNumberToASC_Code((UBYTE)(box_no + OPR_BATCH_FILE_MIN)));
	DisplayChar((UBYTE)37, ChangeNumberToASC_Code((UBYTE)(index_no / (UBYTE)10)));
	DisplayChar((UBYTE)38, ChangeNumberToASC_Code((UBYTE)(index_no % (UBYTE)10)));
}
#endif	/* (PRO_BATCH_TX == ENABLE) */

#if (PRO_CONTINUOUS_POLLING == ENABLE)
/*************************************************************************
	module		:[連続ポーリング機能]
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
	date		:[1996/10/11]
	author		:[松隈,渡辺一章]
*************************************************************************/
UBYTE ContPollingOperation(void)
{
	UWORD	start_time;
	UWORD	end_time;
	UWORD	now_time;
	UDWORD	add_time;
	UDWORD	current_time;
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	TIME_DATA_t bcd_time;

	/* 初期化 */
	now_time = 0;
	add_time = 0x00000000UL;
	current_time = SYB_CurrentTime;	/* 設定時間がずれるため待避する */
	is_loop_end = FALSE;

	/* 時間入力用バッファの初期化 */
	ClearCharacterInput();
	CharacterInput.WritePosition = 3;
	CharacterInput.LcdDisplayPosition = 14;
	/* 現在時刻（ロング型時間）を編集形式に直す */
	SetLongTimeToCharacterInput(current_time, CONT_POLLING_RX_TIME_TYPE);

	/* 開始時間の入力 */
	CharacterInput.FixedWordingLow = (UBYTE *)D2W_EnterContPollStartTime;	/* "ｶｲｼ ｼﾞｶﾝ:           " */
	if ((start_time = ContPollingTimeInput()) == 0xFFFF) {
		return(NG);
	}

	/* 終了時間の入力 */
	CharacterInput.FixedWordingLow = (UBYTE *)D2W_EnterContPollEndTime;		/* "ｼｭｳﾘｮｳ ｼﾞｶﾝ:        " */
	while (is_loop_end != TRUE) {
		if ((end_time = ContPollingTimeInput()) == 0xFFFF) {
			return(NG);
		}
		else {
			/* 終了時間に、開始時間と同じ時間を設定された時は無効です by K.Watanabe 1997/11/08 */
			if (end_time == start_time) {
				NackBuzzer();
			}
			else {
				is_loop_end = TRUE;
			}
		}
	}

	/* 時刻の計算 */
	CMN_LongTimeToBCD(&bcd_time, current_time);
	now_time = (UWORD)CMN_BCD_ToDecimal(bcd_time.Hour);		/* ０時から今の時の積算分 */
	now_time *= 60;
	now_time += (UWORD)CMN_BCD_ToDecimal(bcd_time.Minute);	/* ０分から今の分の積算分 */

	if (now_time > start_time) { /* 開始時刻が現在時刻より前に設定されたら、１日加える */
		start_time += 1440;
		end_time   += 1440;
	}
	if (start_time > end_time) { /* 終了時刻が開始時刻より前に設定されたら、１日加える */
		end_time += 1440;
	}

    /* 開始時刻の計算 */
	add_time = (UDWORD)(start_time - now_time) + (current_time / 60);
	SpecialCommandValue.ContPollingStartTime = add_time * 60;

	/* 終了時刻の計算 */
	add_time = 0x00000000UL;
	add_time = (UDWORD)(end_time - now_time) + (current_time / 60);
	SpecialCommandValue.ContPollingEndTime = add_time * 60;

	/* この先、連続ポーリングが登録されているか判断させるため、アイテムに代入 */
	SpecialCommandValue.CommandOption.Item = SYS_CONTINUOUS_POLLING;
	return(OK);
}

/*************************************************************************
	module		:[連続ポーリング時刻入力]
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
	date		:[1996/11/09]
	author		:[松隈]
*************************************************************************/
UWORD ContPollingTimeInput(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	hour;
	UBYTE	minute;
	UWORD	time;

	time =0;

	/** 上段表示 */
	DisplayStringHigh(0, D2W_ContinuousPolling);

	while (1) {
		DisplayTimeInput(CONT_POLLING_RX_TIME_TYPE);

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			FixedNumberDataSet(key);
			break;
		case FUNCTION:
			CursorRightRotation();
			break;
		case LEFT_ARROW:
			CursorLeftRotation();
			break;
		case ENTER:
			hour = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 2);
			minute = (UBYTE)CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[2], 2);
			if (hour <= 23 && minute <= 59) {
				/* 正しい値 */
				time = (UWORD)hour * 60; 	/* ０時から入力された時の積算分 */
				time += (UWORD)minute;		/* ０分から入力された分の積算分 */
				CharacterInput.CursorPosition = 0;
				return(time);
			}
			else {
				CharacterInput.CursorPosition = 0;
				NackBuzzer();
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return (0xFFFF);
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
#endif	/* (PRO_CONTINUOUS_POLLING == ENABLE) */

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[サブアドレス送信オペレーション]
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
	date		:[1997/04/23]
	author		:[渡辺一章]
*************************************************************************/
UBYTE FcodeTransmissionOperation(void)
{
	UBYTE	ret;	/* リターン値 */

	/* 初めてのＦコード送信の時は、編集用バッファを初期化します */
	if (SpecialCommandValue.CommandOption.Item != SYS_SCANNER_SUB_ADDRESS_TX) {
		CMN_MemorySet(OPR_FcodeData.SubAddress, SYS_ID_MAX, NULL);
		CMN_MemorySet(OPR_FcodeData.Password, SYS_ID_MAX, NULL);
	}

	if ((ret = ComOptionFcodeNumberInput()) == OK) {
		SpecialCommandValue.CommandOption.Item = SYS_SCANNER_SUB_ADDRESS_TX;	/* Ｆコードスキャナ送信 */
	}

	return(ret);
}

/*************************************************************************
	module		:[サブアドレス　ポーリング受信オペレーション]
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
	date		:[1997/04/23]
	author		:[渡辺一章]
*************************************************************************/
UBYTE FcodePollingOperation(void)
{
	UBYTE	ret;	/* リターン値 */

	/* 初めてのＦコード送信の時は、編集用バッファを初期化します */
	if (SpecialCommandValue.CommandOption.Item != SYS_SELECT_POLLING_RX) {
		CMN_MemorySet(OPR_FcodeData.SubAddress, SYS_ID_MAX, NULL);
		CMN_MemorySet(OPR_FcodeData.Password, SYS_ID_MAX, NULL);
	}

	if ((ret = ComOptionFcodeNumberInput()) == OK) {
		SpecialCommandValue.CommandOption.Item = SYS_SELECT_POLLING_RX;		/* 選択ポーリング受信 */
	}

	return(ret);
}

/*************************************************************************
	module		:[応用通信　サブアドレス関係番号入力]
	function	:[
		1.サブアドレス番号の入力を行います
		2.通信パスワード番号の入力を行います
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/24]
	author		:[渡辺一章]
*************************************************************************/
UBYTE ComOptionFcodeNumberInput(void)
{
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	ret;			/* リターン値 */

	/*--------*/
	/* 初期化 */
	/*--------*/
	is_loop_end = FALSE;
	ret = NG;

	/* 番号登録用の初期化 */
	ClearCharacterInput();
	CMN_StringCopy(CharacterInput.Buffer, OPR_FcodeData.SubAddress);
	CharacterInput.MaxFigure = SYS_ID_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/*--------------------*/
	/* サブアドレスの入力 */
	/*--------------------*/
	DisplayStringHigh(0, D2W_InputSubAddressNumber);	/* "ｻﾌﾞｱﾄﾞﾚｽ ｦ ﾄﾞｳｿﾞ    " */

	while (is_loop_end != TRUE) {
		if (InputFcodeNumber(OPR_FCODE_SET_SUB_ADDRESS) == OK) {	/* サブアドレス番号が登録された時 */
			if (CharacterInput.Buffer[0] != NULL) {	/* サブアドレスが登録された時 */
				/* 入力された番号を編集用変数にセットします */
				StoreCharacterInputValue(OPR_FcodeData.SubAddress, ASC_DATA_TYPE);

				/*----------------------*/
				/* 通信パスワードの入力 */
				/*----------------------*/
				DisplayStringHigh(0, D2W_InputPasswordNumber);	/* "ﾊﾟｽﾜｰﾄﾞ ｦ ﾄﾞｳｿﾞ     " */
				if (InputFcodePassword() == OK) {	/* 通信パスワード番号が登録された時 */
					ret = OK;
				}

				is_loop_end = TRUE;
			}
			else {									/* サブアドレスが未登録の時 */
				/* サブアドレスは必ず登録される必要があります */
				NackBuzzer();
				ChildDisplayStringLow(D2W_InvalidNumber);	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
			}
		}
		else {														/* サブアドレス番号入力が中止・タイムアップした時 */
			is_loop_end = TRUE;
		}
	}

	return(ret);
}
#endif	/* (PRO_F_CODE == ENABLE) */

#if (PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[暗号化送信オペレーション]
	function	:[
		1.
	]
	return		:[
		OK	:設定完了
		NG	:設定中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/15]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CipherTransmissionOperation(void)
{
	UBYTE	ret;	/* リターン値 */

	/* 初めての暗号化送信の時は、編集用バッファを初期化します */
	if (SpecialCommandValue.CommandOption.Item != SYS_CIPHER_TX) {
		ClearOPR_CipherData();
	}

	if ((ret = ComOptionCipherTxParaInput()) == OK) {
		SpecialCommandValue.CommandOption.Item = SYS_CIPHER_TX;	/* 暗号化送信 */
	}

	return(ret);
}

/*************************************************************************
	module		:[暗号化送信用パラメータ入力]
	function	:[
		1.キー・キーのヒントを設定します
		2.拡張キーのＯＮ／ＯＦＦを設定します
	]
	return		:[
		OK	:設定完了
		NG	:設定中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/15]
	author		:[渡辺一章]
*************************************************************************/
UBYTE ComOptionCipherTxParaInput(void)
{
	/* キー・キーのヒントの設定をします */
	if (SelectCipherKeySet(OPR_COM_OPTION) == FALSE) {
		return(NG);
	}

	/* 拡張キーのＯＮ／ＯＦＦを設定します */
	if (SelectData(D2W_SelectCipherExtensionKey,		/* "ﾀﾞﾌﾞﾙｶﾞｰﾄﾞ     :    " */
				   D2W_Off2,							/* "                OFF " */
				   2,
				   &OPR_CipherData.KeyExtensionOn,
				   TRUE,
				   NO_KEYTYPE) == OPR_CANCELED) {			/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(NG);
	}

	return(OK);
}
#endif	/* (PRO_CIPHER == ENABLE) */

/* 1997/11/07 Y.Matsukuma */
/************************************************************************
	module		:[一括送信ボックスにＰＩＮ番号がセットされているか]
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
	date		:[1997/11/05]
	author		:[M.Eguchi]
************************************************************************/
UBYTE	ExistPinNumberAtSelectedBox(UBYTE box_no)
{
#if (PRO_PIN_ACCESS == ENABLE)

/*	struct	SYS_DialData_t *dial_ptr;*/
	struct	SYS_BatchTxDialData_t *dial_ptr;
	UBYTE	is_pin_str;


	dial_ptr = &SYB_BatchTxFile[box_no].DialNumber[0];

	if (CHK_PIN_AccessMode() == PIN_ACCESS_OFF) {/*PINｱｸｾｽOFF*/
		/*PIN番号は不要なので無条件にTRUEをかえす*/
		return (TRUE);
	}
	else { /* Mode1 or Mode2 */
		/*選択したボックスのPIN番号の有無を調べる*/
		is_pin_str = FALSE;
		switch (dial_ptr->Item) {
		case SYS_ONETOUCH_DIAL:
			if (((SYB_OnetouchDial[dial_ptr->FaxNumber.Onetouch].Dial[0] & 0xF0) != 0xF0)
			&&	((SYB_OnetouchDial[dial_ptr->FaxNumber.Onetouch].PIN_Number[0] & 0xF0) != 0xF0)) {
				is_pin_str = TRUE;
			}
			break;
		case SYS_SPEED_DIAL:
			if (((SYB_SpeedDial[dial_ptr->FaxNumber.Speed].Dial[0] & 0xF0) != 0xF0)
			&&	((SYB_SpeedDial[dial_ptr->FaxNumber.Speed].PIN_Number[0] & 0xF0) != 0xF0)) {
				is_pin_str = TRUE;
			}
			break;
		case SYS_DIRECT_DIAL:
			if ((dial_ptr->PIN_Number[0] & 0xF0) != 0xF0) {
				is_pin_str = TRUE;
			}
			break;
		default:/*有り得ないはず*/
			break;
		}
		return (is_pin_str);
	}
#else
	return (TRUE);
#endif

}

