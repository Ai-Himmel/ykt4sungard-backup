/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_ONE.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: ワンタッチオペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\define\sysspeed.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"

#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ini_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

/* Prototype
void	EnterOneTouch(void);
void	EraseOneTouch(void);
void	PrintOneTouchList(void);
void	OnetouchForwordOperation(void);
void	OnetouchBackOperation(void);
void	EnterOnetouchInitial(void);
UBYTE	SelectOnetouchNumber(void);
void	DisplaySelectOnetouch(void);
UBYTE	CheckOnetouchStoreStatus(UBYTE);
*/

/*************************************************************************
	module		:[ワンタッチ登録オペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-A1]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void EnterOneTouch(void)
{
	/* 初期化 */
	EnterOnetouchInitial();

	while (1) {
		/** 登録するワンタッチキーを選択 */
		/* 選択されたワンタッチ番号は変数：OPR_Buf.OntchSpdCtrl.SelectNumberにセットされている */
		if (SelectOnetouchNumber() == OPR_END) { /* 途中でストップキーが押された */
			return;
		}
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (SYB_INF_OnetouchStatus[OPR_Buf.OntchSpdCtrl.SelectNumber] == SYS_INF_ONETOUCH_MAILADDRESS) {
			/*ワンタッチダイアル選択中で選択したワンタッチにメールアドレスが登録されている */
			NackBuzzer();
		}
		else { /* ＦＡＸ番号が登録されているか未登録 */
			if (OnetouchSpeedInput() == OPR_END) { /* 登録中止(STOP) */
				return;
			}

			/** ワンタッチを進める */
			OnetouchForwordOperation();
		}
#else		
		if (OnetouchSpeedInput() == OPR_END) { /* 登録中止(STOP) */
			return;
		}

		/** ワンタッチを進める */
		OnetouchForwordOperation();
#endif
	}
}

/*************************************************************************
	module		:[ワンタッチ消去オペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-A2]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/07]
	author		:[江口]
*************************************************************************/
void EraseOneTouch(void)
{
	UBYTE	onetouch_code;
	UBYTE	erase_step;

	erase_step = ERASE_ITEM_SELECT_STEP;

	EnterOnetouchInitial();

	while (1) {
		switch (erase_step) {
		case ERASE_ITEM_SELECT_STEP:	/** ワンタッチ選択状態 */
			/* 選択されたワンタッチ番号は変数：OPR_Buf.OntchSpdCtrl.SelectNumberにセットされている */
			if (SelectOnetouchNumber() == OPR_END) { /* 途中でストップキーが押された */
				return;
			}
			onetouch_code = CMN_OffsetToOnetouchCode((UBYTE)OPR_Buf.OntchSpdCtrl.SelectNumber);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
			if (CheckOnetouchStoreStatus(onetouch_code) == SYS_INF_ONETOUCH_FAXNUMBER) {
				/* 登録されている場合、次のステップに移行 */
				erase_step = ERASE_CONFIRM_STEP;
			}
#else
			if (CheckOnetouchStoreStatus(onetouch_code) == OK) {
				/* 登録されている場合、次のステップに移行 */
				erase_step = ERASE_CONFIRM_STEP;
			}
#endif
			else {
				NackBuzzer();
			}
			break;

		case ERASE_CONFIRM_STEP:	/** クリア確認状態 */
			switch (ConfirmKeyInputOperation(D2W_EraseOnetouch, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
			case CONFIRM_EXEC:	/* 実行 */
				/* ワンタッチ消去実行 */
				ClearOnetouchSpeedRecord(&SYB_OnetouchDial[OPR_Buf.OntchSpdCtrl.SelectNumber]);
				DeleteTelBookData(OPR_Buf.OntchSpdCtrl.SelectNumber);	/* 電話帳からも削除 */
				/* ダイレクトメール防止機能用処理（登録したダイヤルの下４桁のみ別バッファに格納） by K.Watanabe 1997/10/22 */
				SYB_OnetouchJunkDial[OPR_Buf.OntchSpdCtrl.SelectNumber]
				 = PickOutLastFourFigure(SYB_OnetouchDial[OPR_Buf.OntchSpdCtrl.SelectNumber].Dial, 40);
				erase_step = ERASE_COMPLETE_STEP;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
				SYB_INF_OnetouchStatus[OPR_Buf.OntchSpdCtrl.SelectNumber] = SYS_INF_ONETOUCH_NO_ENTRY;
#endif
				break;
			case CONFIRM_ABORT:	/* 取り消し */
				erase_step = ERASE_ITEM_SELECT_STEP;
				break;
			case OPR_END:		/* 中止・タイムアップ */
				return;	
			default:
				break;
			}
			break;

		case ERASE_COMPLETE_STEP:	/* 消去完了表示 */
			if (ClearCompleteDisplayOperation(D2W_EraseOnetouch) == OPR_CONTINUE) {
				erase_step = ERASE_ITEM_SELECT_STEP;
				OnetouchForwordOperation();
			}
			else {
				return;
			}
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
	module		:[ワンタッチダイアルリスト]
	function	:[
		1.ワンタッチダイアルリストのプリントの起動を掛ける
		2.ワンタッチが登録されている必要がある
	]
	return		:[]
	common		:[
					SYB_OnetouchDial
				]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintOneTouchList(void)
{
	UBYTE	onetouch_sw;	/*ﾜﾝﾀｯﾁ番号*/
	UBYTE	onetouch_code;

	/* ワンタッチテーブルをサーチ */
	for (onetouch_sw = 0; onetouch_sw < SYS_ONETOUCH_MAX; onetouch_sw++) {
		onetouch_code = CMN_OffsetToOnetouchCode(onetouch_sw);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		if (CheckOnetouchStoreStatus(onetouch_code) == SYS_INF_ONETOUCH_FAXNUMBER) {
			FinalListPrintOperation(LST_ONETOUCHDIAL_LIST);	/* メインにリスト起動メッセージ送信 */
			return;
		}
#else
		if (CheckOnetouchStoreStatus(onetouch_code) == OK) {
			FinalListPrintOperation(LST_ONETOUCHDIAL_LIST);	/* メインにリスト起動メッセージ送信 */
			return;
		}
#endif
	}
	/*ﾜﾝﾀｯﾁ登録ﾃﾞｰﾀなし*/
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}

/*************************************************************************
	module		:[ワンタッチを進める]
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
	date		:[1995/04/14]
	author		:[江口]
*************************************************************************/
void OnetouchForwordOperation(void)
{
	if (OPR_Buf.OntchSpdCtrl.SelectNumber == (SYS_ONETOUCH_MAX - 1)) {	/* ワンタッチの最大値を越える */
		OPR_Buf.OntchSpdCtrl.SelectNumber = 0;	/* 戻す */
	}
	else {
		OPR_Buf.OntchSpdCtrl.SelectNumber++;
	}
}

/*************************************************************************
	module		:[ワンタッチを戻す]
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
	date		:[1995/04/14]
	author		:[江口]
*************************************************************************/
void OnetouchBackOperation(void)
{
	if (OPR_Buf.OntchSpdCtrl.SelectNumber == 0) {
		OPR_Buf.OntchSpdCtrl.SelectNumber = SYS_ONETOUCH_MAX - 1;
	}
	else {
		OPR_Buf.OntchSpdCtrl.SelectNumber--;
	}
}

/*************************************************************************
	module		:[ワンタッチオペレーション初期化処理]
	function	:[
		1.ワンタッチ登録、クリアのオペレーションに使用するバッファを初期化します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void EnterOnetouchInitial(void)
{
	OPR_Buf.OntchSpdCtrl.SelectNumber = 0; /* ワンタッチＡのオフセット */
	CMN_MemorySet(OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer, 5, NULL);
	/* U1～U2は２文字で表示する必要あり 1995/12/06 Eguchi */
	OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[0] = 'A';
	OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[1] = ' ';
	OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[2] = ':';
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	OPR_Buf.OntchSpdCtrl.MailAddressSetting = 0;
#endif

}

/*************************************************************************
	module		:[セット／消去するワンタッチを選択]
	function	:[
		1.
	]
	return		:[0～SYS_ONETOUCH_MAX：ワンタッチ番号
				  SYS_ONETOUCH_MAX	 :登録終了]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/19]
	author		:[江口]
*************************************************************************/
UBYTE SelectOnetouchNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	onetouch_code;

	onetouch_code = 0;

	DisplayStringHigh(0 , D2W_SelectOnetouch); /* 上段表示[Select One-Touch No. ] */

	while (1) {
		DisplaySelectOnetouch(); /* 下段表示[A:No Number Stored   ]ワンタッチ記号と登録状態 を表示 */

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
	
		switch (keytype) {
		case FUNCTION:		/* 機能キー */
			/* ワンタッチを進める A -> B -> C.....*/
			OnetouchForwordOperation();
			break;
		case LEFT_ARROW:	/*＜　キー */
			/* ワンタッチを戻す C -> B -> A.....*/
			OnetouchBackOperation();
			break;
		case KEY_TIME_UP:
		case STOP:
			/*終了*/
			return (OPR_END);
		case ENTER:
			/* ワンタッチ決定 */
			return (OPR_CONTINUE);
		case ONETOUCH:
			OPR_Buf.OntchSpdCtrl.SelectNumber = (UWORD)CMN_OnetouchCodeToOffset(key);
			break;
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* アンズＬだけは、アンズと動作を合わせます by K.Watanabe 1997/11/28 */
		case SINGLE:		/* 単一オペレーションキー */
			SingleKeyOperation(key);
			break;
#endif
		case NO_EFFECT:
			/*ナックをならさへんため */
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ワンタッチ選択状態表示]
	function	:[
		1.ＬＣＤの下段にワンタッチ記号と登録状態を表示
	]
	return		:[]
	common		:[
		OPR_Buf:OntchSpdCtrl
		FunctionDisplayBufferLow
	]
	condition	:[]
	comment		:[
		ワンタッチとプログラムを兼用することが無くなったので
		プログラム関係の表示は行わないように変更
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/19]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplaySelectOnetouch(void)
{
	UBYTE	onetouch_code;	/* ワンタッチ記号 */
	UBYTE	position;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	UBYTE	status;
#endif
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/17 */
	UBYTE	kei_pos;
#endif		/* End of (defined (KEISATSU)) */

	/* SelectNumberは必ずSYS_ONETOUCH_MAX以下の筈 */
	position = (UBYTE)OPR_Buf.OntchSpdCtrl.SelectNumber;
	onetouch_code = CMN_OffsetToOnetouchCode(position);

	/* 表示バッファクリア */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	/* ワンタッチ記号をセットする部分を関数化したために、
	** アルファベット１文字の場合は、２文字目の部分をクリアしておく必要がある
	*/
	CMN_MemorySet(&OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[0], 2, ' ');
#endif

	/* 選択中のワンタッチ記号をセット */
	SetOnetouchCode(&OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer[0], onetouch_code, OPR_SET_ONETOUCH_NUMBER);

	CMN_StringCopy(FunctionDisplayBufferLow, OPR_Buf.OntchSpdCtrl.SelectNumberDisplayBuffer);

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	status = CheckOnetouchStoreStatus(onetouch_code);
	if (status == SYS_INF_ONETOUCH_FAXNUMBER) {	/* ワンタッチ登録 */
		if (OPR_Buf.OntchSpdCtrl.MailAddressSetting == 1) {
			/*[A :Onetouch In Use  ]*/
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[3], D2W_AlreadyUsedError , 17);
		}
		else {
			/* 下段、ワンタッチ記号と電話番号表示 */
			/* |A :1234567          | */
			CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[3], &SYB_OnetouchDial[position].Dial[0], 17);
		}
	}
	else if (status == SYS_INF_ONETOUCH_MAILADDRESS) {	/* メールアドレス登録 */
		if (OPR_Buf.OntchSpdCtrl.MailAddressSetting == 1) {
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[3], &SYB_INF_Onetouch[CMN_OnetouchCodeToOffset(onetouch_code)].MailAddress[0], 17);
		}
		else {
			/*[A :Onetouch In Use  ]*/
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[3], D2W_AlreadyUsedError, 17);
		}
	}
	else {														/* 未登録 */
		/* |A :No Number Stored | */
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[3], D2W_NoNumberStored, 17);
	}
#else
	if (CheckOnetouchStoreStatus(onetouch_code) == OK) {	/* ワンタッチ登録 */
		/* 下段、ワンタッチ記号と電話番号表示 */
 #if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/17 */
 /* 警察設定表示 */
	 	kei_pos = 3;
		if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_KEIDEN){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｹ", 1);
			kei_pos++;
		}
		else if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_KANYU){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｶ", 1);
			kei_pos++;
		}

		if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_ISSEI){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｲ", 1);
			kei_pos++;
		}
		else if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_KOBETSU){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｺ", 1);
			kei_pos++;
		}

		if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_SCRAMBLE_ON){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "S", 1);
			kei_pos++;
		}
		else if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_SCRAMBLE_OFF){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "N", 1);
			kei_pos++;
		}

		if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_KYOTSU){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｷ", 1);
			kei_pos++;
		}
		else if (SYB_OnetouchDial[position].Keisatsu & SYS_KEISATSU_SENYO){
			CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[kei_pos], "ｾ", 1);
			kei_pos++;
		}

		/* |A :1234567          | */
		CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[kei_pos], &SYB_OnetouchDial[position].Dial[0], 20 - kei_pos);
 #else
		/* |A :1234567          | */
		CMN_BCD_ToASC_StringNum(&FunctionDisplayBufferLow[3], &SYB_OnetouchDial[position].Dial[0], 17);
 #endif		/* End of (defined (KEISATSU)) */
	}
	else {														/* 未登録 */
		/* |A :No Number Stored | */
		CMN_StringCopyNumNotNULL(&FunctionDisplayBufferLow[3], D2W_NoNumberStored, 17);
	}
#endif

#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Add by SMuratec C.P 2004/07/14 for prefix *//* by K.Watanabe 2004/11/12 */
	ChangeDisplayBuffer(FunctionDisplayBufferLow);
#endif

	/** 下段表示更新 */
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[ワンタッチダイアル登録状態チェック]
	function	:[
		1.指定されたワンタッチコードの登録状態を得る
		2.引数でワンタッチ記号を指定
	]
	return		:[
		NG:未登録
		OK:登録済み
	]
	common		:[SYB_OnetouchDial]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
UBYTE CheckOnetouchStoreStatus(UBYTE onetouch)
{
	UBYTE   position;

	position = CMN_OnetouchCodeToOffset(onetouch);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
	/*　リターン値の種類
	**　SYS_INF_ONETOUCH_FAXNUMBER		電話番号登録済み
	**　SYS_INF_ONETOUCH_MAILADDRESS	メールアドレス登録済み
	**　SYS_INF_ONETOUCH_NO_ENTRY		未登録
	*/
	return (SYB_INF_OnetouchStatus[position]);
#else
	if ((SYB_OnetouchDial[position].Dial[0] & 0xF0) == 0xF0) {
		return (NG);
	}
	return (OK);
#endif
}
