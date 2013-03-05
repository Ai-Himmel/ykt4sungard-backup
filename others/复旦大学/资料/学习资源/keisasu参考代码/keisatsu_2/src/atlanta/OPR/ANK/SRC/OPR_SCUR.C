/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SCUR.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 親展モード
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

/* Prototype
void	SetSecureMailBox(void);
UBYTE	SecureBoxInput(void);
UBYTE	SecurePasscodeCheck(void);
UBYTE	SecureNameInput(void);
UBYTE	SecurePasscodeInput(void);
void	SetSecureMailComplete(void);
void	DisplaySetSecureMailBox(UBYTE);
void	PrintSecureMailList(void);
void	PrintSecureMailDocument(void);
void	ClearMailBox(UBYTE);
void	SetSecureMailHoldTime(void);
*/

/*************************************************************************
	module		:[親展者名登録機能]
	function	:[
		1.親展者名登録の機能を実行する。
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[PRG + E1]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/26]
	author		:[江口]
*************************************************************************/
void SetSecureMailBox(void)
{
	UBYTE	stage;	/* セット段階 */

	stage = ENTER_SECURE_BOXNO;

	while (1) {
		DisplaySetSecureMailBox(stage);
		stage = (SetSMailFunction[stage])();

		if (stage == SET_SECURE_END) {
			return;
		}
		if (stage == SET_SECURE_COMPLETE) {
			SetSecureMailComplete();
			return;
		}
	}
}

/*************************************************************************
	module		:[親展ボックス番号の入力]
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
	date		:[1995/12/15]
	author		:[江口]
*************************************************************************/
UBYTE SecureBoxInput(void)
{
	UBYTE	stage;

	stage = SET_SECURE_END;

	if (NumberInput(OPR_MAIL_BOX_NUMBER_INPUT) == OK) {
		OPR_Buf.ScurMailCtrl.BoxNumber = (UBYTE)CharacterInputToNumber();
		if (SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].Status == SYS_MAILBOX_NO_SET) {
			/* 未登録状態の場合 データが残っている可能性があるので消去*/
			ClearMailBox(OPR_Buf.ScurMailCtrl.BoxNumber);
		}
		stage = CHECK_SECURE_PASSCODE;
	}
	return (stage);
}

/************************************************************************
	module		:[親展パスコードチェック]
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
	date		:[1995/12/15]
	author		:[江口]
************************************************************************/
UBYTE SecurePasscodeCheck(void)
{
	UBYTE	stage;
	UWORD	passcode;

	stage = SET_SECURE_END;

	passcode = EnterPassCode(SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].PassCode, CHK_PASS_CODE_ENTER, D2W_EnterIDCode);

	if (passcode == 0xFFFF) { /* 登録中止 */
		return (stage);
	}
	if (passcode == SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].PassCode) { /* 一致する*/
		stage = ENTER_SECURE_BOXNAME;	/* ボックス名の入力に移行 */
	}
	else { /* 古いパスコードと異なる場合、登録はできないので終了する */
		NackBuzzer();
		OPR_ChildErrorFlag = INVALID_ID_CODE_ERROR;	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    " */
	}
	return (stage);
}

/*************************************************************************
	module		:[親展ボックス名入力]
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
	date		:[1995/12/15]
	author		:[江口]
*************************************************************************/
UBYTE SecureNameInput(void)
{
	UBYTE	stage;

	stage = SET_SECURE_END;
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	CMN_StringCopy(CharacterInput.Buffer, SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].BoxName);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_BOX_NAME_MAX - 1;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
#else 
	if (NameInput(OPR_KANJI_DISABLE) == OK) {	/* 登録完了 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

		if (CheckCharacterInputEmpty() == FALSE) { /* 登録された場合 */
			StoreCharacterInputValue(OPR_Buf.ScurMailCtrl.BoxName, ASC_DATA_TYPE);
			stage = ENTER_SECURE_NEW_PASSCODE;
		}
		else { /* 名前が未入力の場合は親展ボックスの消去を行う */
			if ((SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].Status == SYS_MAILBOX_RECEIVE)
			||	(SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].Status == SYS_MAILBOX_RECEIVING)
			||	(SYB_MailBox[OPR_Buf.ScurMailCtrl.BoxNumber].Status == SYS_MAILBOX_RCV_TO_RECEVING)) {	/* 1line add 1997/10/18  By T.Yamaguchi */
				/* 消去しようとした親展ボックスに原稿があるか、或いは受信中の場合
				   消去はせずにもう一度名前入力に戻る*/
				NackBuzzer();
				OPR_ChildErrorFlag = SECURE_DOC_EXIST_ERROR; /*いらんか*/
				stage = ENTER_SECURE_BOXNAME;
			}
			else {
				ClearMailBox(OPR_Buf.ScurMailCtrl.BoxNumber);
			}
		}
	}
	return (stage);
}

/*************************************************************************
	module		:[親展パスコード入力]
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
	date		:[1995/12/15]
	author		:[江口]
*************************************************************************/
UBYTE SecurePasscodeInput(void)
{
	UBYTE	stage;
	UBYTE	box_no;
	UWORD	passcode;

	box_no = OPR_Buf.ScurMailCtrl.BoxNumber;

	stage = SET_SECURE_END;

	/* パスコード登録 */
	passcode = EnterPassCode(SYB_MailBox[box_no].PassCode, PASS_CODE_ENTER_ZERO_OK, D2W_EnterIDCode);
	if (passcode == 0xFFFF) {	/* 登録中断 */
		return (stage);
	}
	if (passcode == 0) {	/* ０がセットされた */
		/* 消去 */
		if ((SYB_MailBox[box_no].Status == SYS_MAILBOX_RECEIVE)
		||	(SYB_MailBox[box_no].Status == SYS_MAILBOX_RECEIVING)
		||	(SYB_MailBox[box_no].Status == SYS_MAILBOX_RCV_TO_RECEVING)) {	/* 1line add 1997/10/18  By T.Yamaguchi */
			/* 消去しようとした親展ボックスに原稿があるか、或いは受信中の場合
			   消去はせずにもう一度パスコード入力に戻る*/
			NackBuzzer();
			OPR_ChildErrorFlag = SECURE_DOC_EXIST_ERROR; /*いらんか*/
			stage = ENTER_SECURE_NEW_PASSCODE;
		}
		else {
			ClearMailBox(box_no);
		}
	}
	else {
		OPR_Buf.ScurMailCtrl.Passcode = passcode;
		stage = SET_SECURE_COMPLETE;
	}
	return (stage);
}

/*************************************************************************
	module		:[親展ボックス登録最終処理]
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
	date		:[1995/12/15]
	author		:[江口]
*************************************************************************/
void SetSecureMailComplete(void)
{
	UBYTE	box_no;

	box_no = OPR_Buf.ScurMailCtrl.BoxNumber;

	/* 名前を入力 */
	CMN_StringCopyNULL(SYB_MailBox[box_no].BoxName, OPR_Buf.ScurMailCtrl.BoxName);

	/** 入力されたパスコードを登録する */
	SYB_MailBox[box_no].PassCode = OPR_Buf.ScurMailCtrl.Passcode;
	if (SYB_MailBox[box_no].Status == SYS_MAILBOX_NO_SET) {
		SYB_MailBox[box_no].Status = SYS_MAILBOX_SET;
	}
	ChildDisplaySetCompleted(D2W_SetSecureMailBox);
}

/*************************************************************************
	module		:[親展ボックス登録中上段表示]
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
	date		:[1995/12/15]
	author		:[江口]
*************************************************************************/
void DisplaySetSecureMailBox(UBYTE stage)
{
	if (CheckChildErrorDisplayReq() == TRUE) {	/* チャイルド表示すべきエラーが発生した */
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) { /* チャイルド表示中*/
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	switch (stage) {
	case ENTER_SECURE_BOXNO: 		/** 親展ボックス番号入力 */
		/* [ｼﾝﾃﾝ ｾｯﾄ            ] */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SetSecureMailBox);
		break;
	case CHECK_SECURE_PASSCODE:		/** パスコードチェック */
	case ENTER_SECURE_NEW_PASSCODE:	/** 新規パスコード入力 */
		/* [ｼﾝﾃﾝ ﾊﾞﾝｺﾞｳ:      1 ] */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_InputMailBoxNumber);
		FunctionDisplayBufferHigh[18] = ChangeNumberToASC_Code(OPR_Buf.ScurMailCtrl.BoxNumber);
		break;
	case ENTER_SECURE_BOXNAME:		/** 名前入力 */
		/* [1:ｼﾝﾃﾝｼｬﾒｲ          ] */
#if (0)	/* 無駄な処理を止めて、ワーディングで対応します by K.Watanabe 1998/08/19 */
//		FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(OPR_Buf.ScurMailCtrl.BoxNumber);
//		FunctionDisplayBufferHigh[1] = ':';
//		CMN_StringCopy(&FunctionDisplayBufferHigh[2], D2W_SecureMailName);	/* "ｼﾝﾃﾝｼｬﾒｲ\0           " */
#endif
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SecureMailName);	/* " :ｼﾝﾃﾝｼｬﾒｲ          " */
		FunctionDisplayBufferHigh[0] = ChangeNumberToASC_Code(OPR_Buf.ScurMailCtrl.BoxNumber);
		break;
	case SET_SECURE_END:			/** 終了 */
		return;
	default:
		break;
	}
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

/*************************************************************************
	module		:[親展者リスト]
	function	:[
		1.親展者リストの印字の起動をかける
		2.親展ＢＯＸが登録されている必要がある
	]
	return		:[]
	common		:[SYB_MailBox]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/05/19]
	author		:[江口]
*************************************************************************/
void PrintSecureMailList(void)
{
	UWORD	secure_number;	/*親展番号*/

	/* 親展ＢＯＸが登録されているかチェック */
	for (secure_number = 0; secure_number < SYS_MAILBOX_MAX; secure_number++) {
		if (SYB_MailBox[secure_number].Status != SYS_MAILBOX_NO_SET) {
			FinalListPrintOperation(LST_MAILBOX_LIST); /* メインにリスト起動メッセージ送信 1995/04/04 Egu*/
			return;
		}
	}
	NackBuzzer();
	OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;
}

/*************************************************************************
	module		:[親展受信プリント機能]
	function	:[
		1.親展受信プリントの機能を実行する。
	]
	return		:[なし]
	common		:[
		DisplayBuffer0:
		SYB_MailBox:
		OperationMessageToMain:
	]
	condition	:[]
	comment		:[PRG - E3]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/2/17]
	author		:[S.Kawasaki]
*************************************************************************/
void PrintSecureMailDocument(void)
{
	UWORD	passcode;	/*ﾊﾟｽｺｰﾄﾞ*/
	UWORD	box_no;		/*親展番号*/

	passcode = box_no = 0;

	/* （特許対応） 97'09/03 by K.Watanabe
	** メモリ送信原稿蓄積中に、受信済みの蓄積原稿プリントの起動は禁止します
	*/
	if (CMN_CheckMemoryTxDocStoring()) {
		NackBuzzer();
		return;
	}

	/** 親展ボックス番号の入力 */
	DisplayStringHigh(0, D2W_PrintSecureMail);	/* "ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ     " */
	if (NumberInput(OPR_MAIL_BOX_NUMBER_INPUT) == NG) { /* 登録が中止された場合 */
		return;
	}
	box_no = (UBYTE)CharacterInputToNumber();

#if (0)
** 	/* 同一ボックスにすでに親展受信原稿がある状態で、さらに受信を行っているとき、
** 	** 既存の受信原稿をプリントしようとすると、「原稿が有りません」となってしまう。
** 	** by O.Kimoto 1999/03/18
** 	*/
** 	/*
** 	** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
** 	** 原稿無し：MEM_NO_INDEX(0xFFFF)
** 	** 原稿有り：０以外のページ数
** 	** By S.Kawasaki 1996/08/10
** 	*/
** 	/** 原稿の有無のチェック */
** 	if ((SYB_MailBox[box_no].Status != SYS_MAILBOX_RECEIVE)
**    	/* ||  (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,box_no, MEM_IGNORE_BOX_NUMBER) == 0)) { @** 原稿がない By S.Kawasaki 1996/08/10 */
**    	||  (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,box_no, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX)) { /** 原稿がない By S.Kawasaki 1996/08/10 */
** 		NackBuzzer();
** 		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
** 		return;
** 	}
#else
	if ((SYB_MailBox[box_no].Status == SYS_MAILBOX_RECEIVING)					/* 親展受信原稿有り */
		|| (SYB_MailBox[box_no].Status == SYS_MAILBOX_RCV_TO_RECEVING)) {		/* 親展受信原稿ありのＢＯＸに受信中の原稿有り */
		NackBuzzer();
		OPR_ChildErrorFlag = BOX_IN_USE_ERROR;	/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
		return;
	}
	if ((SYB_MailBox[box_no].Status != SYS_MAILBOX_RECEIVE)
		|| (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,box_no, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX)) { /** 原稿がない By S.Kawasaki 1996/08/10 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		return;
	}
#endif

	/** パスコードチェック */
	DisplayStringHigh(0, D2W_PrintSecureMail);	/* "ｼﾝﾃﾝｼﾞｭｼﾝ ﾌﾟﾘﾝﾄ     " */
	passcode = EnterPassCode(SYB_MailBox[box_no].PassCode, CHK_PASS_CODE_ENTER, D2W_EnterIDCode);
	/* パスコードチェック */
	if (passcode != 0xFFFF) { /* 登録された (0xFFFF :登録中止)*/
		if (passcode == SYB_MailBox[box_no].PassCode) {	/* 古いパスコードと一致する */
			/* プリント起動メッセージの送信 */
			FinalMemoryPrintOperation(SYS_MEM_SECURE_RX_FILE, box_no, NULL);
		}
		else {											/* パスコードチェックＮＧ */
			NackBuzzer();
			OPR_ChildErrorFlag = INVALID_ID_CODE_ERROR;	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    " */
			return;
		}
	}
}

/*************************************************************************
	module		:[親展ボックスのクリア]
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
	date		:[1995/07/13]
	author		:[江口]
*************************************************************************/
void ClearMailBox(UBYTE box_no)
{
	/*	念のため消去できる状態かチェックする */
	if ((SYB_MailBox[box_no].Status == SYS_MAILBOX_RECEIVE)
	 || (SYB_MailBox[box_no].Status == SYS_MAILBOX_RECEIVING)
	 ||	(SYB_MailBox[box_no].Status == SYS_MAILBOX_RCV_TO_RECEVING)) {	/* 1line add 1997/10/18  By T.Yamaguchi */
		/* 消去できない */
		return;
	}

	SYB_MailBox[box_no].Status = SYS_MAILBOX_NO_SET;
	SYB_MailBox[box_no].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
	SYB_MailBox[box_no].PassCode = 0;
	SYB_MailBox[box_no].ErasedTime = 0;
	CMN_MemorySet(&SYB_MailBox[box_no].RemoteName[0], SYS_REMOTE_NAME_MAX, NULL);
	CMN_MemorySet(&SYB_MailBox[box_no].BoxName[0], SYS_BOX_NAME_MAX, NULL);
}

/*************************************************************************
	module		:[親展受信メモリ期間セット機能]
	function	:[
		1.親展受信メモリ期間セットの機能を実行する。
	]
	return		:[なし]
	common		:[
		SYB_SettingStatus:
	]
	condition	:[]
	comment		:[H8から移植
				  PRG - E4]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/2/17]
	author		:[S.Kawasaki]
*************************************************************************/
void SetSecureMailHoldTime(void)
{
	UWORD	hold_time;

	hold_time = 0;

	DisplayStringHigh(0, D2W_SecureMailHoldTime );
	hold_time = FixedLengthNumberInput((UWORD)SYB_SettingStatus[SECURE_MAIL_HOLD_TIME], 1, 31,(UBYTE)18, D2W_HoldTime1_31);
	if (hold_time != 0xFFFF) { /* 登録完了(0xFFFF:登録中止)*/
		SYB_SettingStatus[SECURE_MAIL_HOLD_TIME] = (UBYTE)hold_time;
		ChildDisplaySetCompleted(D2W_SecureMailHoldTime);
	}
}
