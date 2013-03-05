/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_FCOD.C
*	Author		: 渡辺一章
*	Date		: 1997/04/14
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: Ｆコード　オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

/*
void	SetFcodeBox(void);
void	PrintFcodeBoxList(void);
void	PrintFcodeBoxDocList(void);
void	PrintFcodeBoxDocument(void);
void	EraseFcodeBox(void);
void	EraseFcodeBoxDocument(void);
void	StoreFcodeBoxDocument(void);
UBYTE	SelectFcodeBoxNumber(void);
UBYTE	CheckFcodePassCode(void);
UBYTE	SetFcodeBoxName(void);
UBYTE	SetFcodeSubAddress(void);
UBYTE	SetFcodePassword(void);
UBYTE	SelectFcodeBoxKind(void);
UBYTE	SetFcodeOption(void);
UBYTE	SetFcodeHoldTime(void);
UBYTE	SetFcodePassCode(void);
void	SetFcodeComplete(void);
void	ClearFcodeControlData(void);
void	DisplaySetFcodeBox(UBYTE);
void	DisplaySelectFcodeBox(void);
void	FcodeBoxNumberForwordOperation(void);
void	FcodeBoxNumberBackOperation(void);
void	GetSubAddressBoxData(void);
UBYTE	InputFcodePassword(void);
UBYTE	InputFcodeNumber(UBYTE);
UBYTE	InputFcodeStoreDocFile(UBYTE, UBYTE *, UWORD *);
void	DisplayFcodeBoxNumberAndTitle(UBYTE *);
UBYTE	GetEmptyFcodeNumberData(UBYTE);
*/

#if (PRO_F_CODE == ENABLE)
/*************************************************************************
	module		:[サブアドレスＢＯＸ登録]
	function	:[
		1.登録するＢＯＸ番号を選択します
		2.選択したＢＯＸの暗証番号（パスコード）を確認します
		3.ＢＯＸ名を登録します
		4.サブアドレス番号を登録します
		5.通信パスワード番号を登録します
		6.登録するＢＯＸの種類を選択します（掲示板ＢＯＸ・親展ＢＯＸ）
		7.選択したＢＯＸに対しての個別の設定を行います
		　・掲示板ＢＯＸを選択	→	オプションの設定
		　・親展ＢＯＸを選択	→	原稿保持期間の設定
		8.暗証番号を登録します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/03/25]
	author		:[渡辺一章]
*************************************************************************/
void SetFcodeBox(void)
{
	UBYTE	stage;	/* セット段階 */

	/* サブアドレスＢＯＸ登録作業用変数クリア */
	ClearFcodeControlData();

	stage = SELECT_FCODE_BOX_NO;	/* ＢＯＸ番号選択 */

	/* ＢＯＸ登録中止するまで処理を続けます */
	while ((stage != SELECT_FCODE_BOX_STOP) && (stage != SET_FCODE_STOP)) {

		/* 上段の表示 */
		DisplaySetFcodeBox(stage);

		stage = (SetFcodeBoxFunction[stage])();

		/* ＢＯＸ登録完了又は、ＢＯＸ登録中止（一度登録してあるＢＯＸに対して）の時、
		** 作業用変数をサブアドレスＢＯＸの変数にコピーします
		** 注）ＢＯＸ番号選択中の中止は除きます
		*/
		if ((stage == SET_FCODE_COMPLETE)
		 || ((stage == SET_FCODE_STOP)
		  && (SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].Status != SUB_ADDRESS_BOX_EMPTY))) {
			/* サブアドレスＢＯＸ登録処理 */
			SetFcodeComplete();

			if (stage == SET_FCODE_COMPLETE) {	/* ＢＯＸ登録完了時 */
				/* 次のＢＯＸ番号に進めます */
				FcodeBoxNumberForwordOperation();
				stage = SELECT_FCODE_BOX_NO;	/* ＢＯＸ番号選択 */
			}
		}
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸリスト]
	function	:[
		1.サブアドレスＢＯＸに登録されている内容の一覧をプリントします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/21]
	author		:[渡辺一章]
*************************************************************************/
void PrintFcodeBoxList(void)
{
	if (CheckSubaddressBox()) {	/* サブアドレスＢＯＸが登録されている時 */
		FinalListPrintOperation(LST_F_CODE_BOX_LIST);	/* メインにリスト起動メッセージを送信 */
	}
	else {						/* サブアドレスＢＯＸが未登録の時 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿リスト]
	function	:[
		1.サブアドレスＢＯＸで蓄積原稿又は、受信原稿があるＢＯＸがあれば
		　一覧をプリントします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/21]
	author		:[渡辺一章]
*************************************************************************/
void PrintFcodeBoxDocList(void)
{
	UBYTE	i;
	UBYTE	is_print_enable;

	if (CheckSubaddressBox()) {	/* サブアドレスＢＯＸが登録されている時 */
		/* 蓄積原稿又は、受信原稿があるＢＯＸがあるかを調べます */
		is_print_enable = FALSE;
		for (i = 0; i < SUB_ADDRESS_BOX_MAX; i++) {
#if (0)	/* Fｺｰﾄﾞ原稿ﾌﾟﾘﾝﾄ中、Fｺｰﾄﾞ原稿ﾘｽﾄﾌﾟﾘﾝﾄすると"ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ"が表示される不具合対策。By H.Fujimura 1999/03/04 */
//			if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
//			 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE)) {/* 蓄積原稿ありor受信原稿あり */
//				is_print_enable = TRUE;
//				break;
//			}
#else
			if (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRINTING) {/* 蓄積原稿プリント中 */
				NackBuzzer();
				OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;	/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
				return;
			}
			if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
			 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE)) {/* 蓄積原稿ありor受信原稿あり */
				is_print_enable = TRUE;
			}
#endif
		}

		if (is_print_enable) {	/* 蓄積原稿・受信原稿があった時 */
			FinalListPrintOperation(LST_F_CODE_DOC_LIST);	/* メインにリスト起動メッセージを送信 */
		}
		else {					/* 蓄積原稿・受信原稿がない時 */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      " */
		}
	}
	else {						/* サブアドレスＢＯＸが未登録の時 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿プリント]
	function	:[
		1.サブアドレスＢＯＸに蓄積されている原稿のプリントを行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		注）掲示板ＢＯＸのみ、プリントするファイルを指定できます
			親展ＢＯＸは、無条件に全ファイルをプリントします
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/22]
	author		:[渡辺一章]
*************************************************************************/
void PrintFcodeBoxDocument(void)
{
	UWORD	doc_number;	/* ファイル番号*/
	UBYTE	file_item;	/* プリントファイル種別 */

	/* （特許対応） 97'09/03 by K.Watanabe
	** メモリ送信原稿蓄積中に、受信済みの蓄積原稿プリントの起動は禁止します
	*/
	if (CMN_CheckMemoryTxDocStoring()) {
		NackBuzzer();
		return;
	}

	/* プリントするＢＯＸ・ファイルを指定します */
	if (InputFcodeStoreDocFile(OPR_FCODE_STORE_DOC_PRINT, &file_item, &doc_number) == OK) {
		/* プリント起動メッセージの送信 */
		FinalMemoryPrintOperation(file_item, doc_number, (UBYTE)(OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN));
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ消去]
	function	:[
		1.選択したサブアドレスＢＯＸを消去します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/22]
	author		:[渡辺一章]
*************************************************************************/
void EraseFcodeBox(void)
{
	UBYTE	is_loop_end;	/* ループ終了で使用 */
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
	UBYTE	prg_no;
#endif

	is_loop_end = FALSE;

	/* サブアドレスＢＯＸ登録作業用変数クリア */
	ClearFcodeControlData();

	/** データ入力 */
	while (is_loop_end != TRUE) {

		/* 消去したいＢＯＸ番号を選択します */
		if (SelectFcodeBoxNumber() == SELECT_FCODE_BOX_STOP) {	/* 選択が中止された時 */
			is_loop_end = TRUE;
			continue;
		}

		/* 選択されたＢＯＸのチェック */
		if (OPR_FcodeData.Status == SUB_ADDRESS_BOX_EMPTY) {
			/* 未登録のＢＯＸが選択された時 */
			NackBuzzer();
			continue;
		}
		else if (SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_NO_SET) {
			/* 選択されたＢＯＸが未蓄積以外（蓄積原稿がある等）の時 */
			NackBuzzer();
			OPR_ChildErrorFlag = BOX_IN_USE_ERROR;	/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
			continue;
		}

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
		/* プログラムワンタッチの登録内容チェック */
		for (prg_no = 0; prg_no < SYS_PROGRAM_MAX; prg_no++) {
			if ((CheckProgramStoreStatus(prg_no) == OPR_PRG_STORE)
			 && (SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item == MSG_STORE_FCODE_BOX_DOC)
			 && (OPR_FcodeData.BoxNumber == (UBYTE)SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point)) {
				NackBuzzer();
				OPR_ChildErrorFlag = USE_PROGRAM_ONETOUCH_ERROR;	/* "ﾌﾟﾛｸﾞﾗﾑ ﾃﾞ ｼﾖｳｻﾚﾃｲﾏｽ" */
				break;
			}
		}
		if (prg_no < SYS_PROGRAM_MAX) {
			continue;
		}
#endif

		/* ＢＯＸ選択後の上段表示 */
		DisplayFcodeBoxNumberAndTitle(D2W_EraseFcodeBoxMode);	/* "   ﾎﾞｯｸｽ ｸﾘｱ        " */

		/* 選択したＢＯＸの暗証番号を入力します */
		if (CheckFcodePassCode() == SET_FCODE_STOP) {	/* 間違った暗証番号が入力されたか、入力が中止された時 */
			is_loop_end = TRUE;
			continue;
		}

		/* 消去前にもう一度、確認を行います */
		switch (ConfirmKeyInputOperation(FunctionDisplayBufferHigh, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
		case CONFIRM_EXEC:	/* セットキーが押された時 */

			/* 1999/08/05 Y.Murata  NAGANOより 1999/10/21 Y.Murata
			 * 消去前にもう一度、ＢＯＸの状態のチェックをします。
			*/
			if (SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_NO_SET) {
				/* 選択されたＢＯＸが未蓄積以外（蓄積原稿がある等）の時 */
				NackBuzzer();
				OPR_ChildErrorFlag = BOX_IN_USE_ERROR;	/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
				is_loop_end = TRUE;
				break;
			}


			/* 指定されたＢＯＸのサブアドレスを消去します */
			CMN_ClearFcodeBox((UWORD)OPR_FcodeData.BoxNumber);

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_EraseFcodeBoxMode[3]);	/* "   ﾎﾞｯｸｽ ｸﾘｱ        " */
			if (ClearCompleteDisplayOperation(FunctionDisplayBufferHigh) == OPR_CONTINUE) {
				/* ストップキー以外のキーが押されたか、チャイルド表示終了の時 */
				FcodeBoxNumberForwordOperation();
			}
			else {
				/* ストップキーが押された時 */
				is_loop_end = TRUE;
			}
			break;
		case CONFIRM_ABORT:	/* 機能キーが押された時 */
#if (0)	/* ｸﾘｱがｷｬﾝｾﾙされた時は、一括送信BOX等と同様に、選択されたBOXのままにします by K.Watanabe 1998/01/27 */
//			/* 次のＢＯＸ番号に進めます */
//			FcodeBoxNumberForwordOperation();
#endif
			break;
		case OPR_END:		/* ストップキーが押されたか１分間入力無しの時 */
		default:
			is_loop_end = TRUE;
			break;
		}
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ蓄積原稿消去]
	function	:[
		1.蓄積原稿を消去するＢＯＸを選択します
		2.消去したいファイル番号を入力します（掲示板ＢＯＸのみ）
		3.蓄積原稿を消去します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		注）掲示板ＢＯＸのみ、消去するファイルを指定できます
			親展ＢＯＸは、無条件に全ファイルを消去します
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/22]
	author		:[渡辺一章]
*************************************************************************/
void EraseFcodeBoxDocument(void)
{
	UBYTE	file_item;		/* プリントファイル種別 */
	UWORD	doc_number;		/* ファイル番号*/
	struct	SYS_SubAddressBoxData_t	*sub_ptr;

	/* 消去するＢＯＸ・ファイルを指定します */
	if (InputFcodeStoreDocFile(OPR_FCODE_STORE_DOC_ERASE, &file_item, &doc_number) == NG) {
		return;
	}
	sub_ptr = &SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber];

	/* 消去前にもう一度、確認を行います */
	if (ConfirmKeyInputOperation(FunctionDisplayBufferHigh,
								 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {	/* 実行が選択された時 */

		/* 消去前にもう一度、ＢＯＸのチェックを行います */
		if (sub_ptr->DataStatus == SYS_SUB_ADDRESS_BOX_NO_SET) {
			/* 選択されたＢＯＸに蓄積原稿がない時 */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      " */
			return;
		}
		else if ((sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_STORED)
			  && (sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVE)) {
			/* 選択されたＢＯＸが受信中・送信中・蓄積中・消去中・プリント中の時 */
			NackBuzzer();
			OPR_ChildErrorFlag = BOX_IN_USE_ERROR;			/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
			return;
		}

		/* 指定されたＢＯＸの蓄積原稿を消去します */
		MEM_ClearDoc(file_item, doc_number, (UBYTE)(OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN));

		/* 消去した原稿を表すビットをＯＦＦします */
		if (doc_number == MEM_ALL_NO) {
			sub_ptr->StoredDocBit = 0;
		}
		else {
			CMN_ClearLongBitAssign(&sub_ptr->StoredDocBit, (UBYTE)(doc_number - 1));
		}

		/* 蓄積されている原稿がなくなった時は、蓄積・受信原稿の状態を未登録にしておく */
		if (sub_ptr->StoredDocBit == 0) {
			sub_ptr->DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;	/* 原稿未蓄積をセット */

			if (MEM_CountItemTotalPage(SYS_MEM_SUB_BULLETIN_FILE) == MEM_NO_INDEX) {
				SYB_SelectPollDocumentStatus = 0; /** 選択ポーリング無しセット */
			}
		}

		/* 完了表示 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_EraseFcodeDocMode[3]);	/* "   ﾁｸｾｷ ｹﾞﾝｺｳ ｸﾘｱ   " */
		DisplayStringHigh(0, FunctionDisplayBufferHigh);	/* "ﾁｸｾｷ ｹﾞﾝｺｳ ｸﾘｱ      " */
		ChildDisplayStringLow(D2W_ClearComplete);			/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ原稿蓄積]
	function	:[
		1.原稿を蓄積するＢＯＸ番号を選択します（掲示板ＢＯＸのみ）
		2.原稿を追加で蓄積するか、上書きで蓄積するかを選択します
		3.原稿を蓄積します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		注）掲示板ＢＯＸ以外は蓄積できません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/22]
	author		:[渡辺一章]
*************************************************************************/
void StoreFcodeBoxDocument(void)
{
	UBYTE	file_number;	/* 空きファイル番号 */
	UBYTE	is_doc_add;		/* 原稿追加するか上書きするか */
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	struct	SYS_SubAddressBoxData_t	*sub_ptr;

	is_loop_end = FALSE;

	/* サブアドレスＢＯＸ登録作業用変数クリア */
	ClearFcodeControlData();

	/** データ入力 */
	while (is_loop_end != TRUE) {

		/* 原稿を蓄積したいＢＯＸ番号を選択します */
		if (SelectFcodeBoxNumber() == SELECT_FCODE_BOX_STOP) {	/* 選択が中止された時 */
			return;
		}
		sub_ptr = &SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber];

		/* 選択されたＢＯＸのチェック */
		if (OPR_FcodeData.Status == SUB_ADDRESS_BOX_EMPTY) {
			/* 未登録のＢＯＸが選択された時 */
			NackBuzzer();
		}
		else if (OPR_FcodeData.Status == SUB_ADDRESS_SECURE_BOX) {
			/* 親展ＢＯＸは蓄積できません */
			NackBuzzer();
			OPR_ChildErrorFlag = SETTING_SECURE_BOX_ERROR;	/* "ｼﾝﾃﾝﾎﾞｯｸｽ ﾃﾞｽ       " */
		}
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
		else if (OPR_FcodeData.Status == SUB_ADDRESS_RELAY_BOX) {
			/* 中継ＢＯＸは蓄積できません */
			NackBuzzer();
			OPR_ChildErrorFlag = SETTING_RELAY_BOX_ERROR;	/* "ﾁｭｳｹｲﾎﾞｯｸｽ ﾃﾞｽ      " */
		}
#endif
		else if ((sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_NO_SET)
			  && (sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_STORED)
			  && (sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVE)) {
			/* 受信中・送信中・蓄積中・消去中・プリント中の時は蓄積できません 1997/05/06  By T.Yamaguchi */
			NackBuzzer();
		/*	OPR_ChildErrorFlag = NOT_STORED_DOCUMENT_ERROR;	*/ /* "ﾁｸｾｷ ﾃﾞｷﾏｾﾝ         " */
			OPR_ChildErrorFlag = BOX_IN_USE_ERROR;			   /* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */ /* Modified by S.Fukui Oct.13,1997 */
		}
		else {
			/* 蓄積可能なＢＯＸが選択された時 */
			is_loop_end = TRUE;
		}
	}

	/* ＢＯＸ選択後の上段表示 */
	DisplayFcodeBoxNumberAndTitle(D2W_StoreFcodeDocMode);	/* "   ｹﾞﾝｺｳ ﾁｸｾｷ       " */

	/* 選択したＢＯＸの暗証番号を入力します */
	if (CheckFcodePassCode() == SET_FCODE_STOP) {	/* 間違った暗証番号が入力されたか、入力が中止された時 */
		return;
	}

	/* 原稿追加／上書き設定 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/21 */
	is_doc_add = 0;	/* 初期値は原稿追加ＯＮです */
	if (SelectData(D2W_SelectFcodeRxDocUpperWrite,	/* "ｹﾞﾝｺｳ ｳﾜｶﾞｷ    :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &is_doc_add,
				   SUB_ADDRESS_OPTION_DOC_ADD,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return;
	}
#else
	is_doc_add = TRUE;	/* 初期値は原稿追加ＯＮです */
	if (SelectData(D2W_SelectFcodeStoreDocAdd,	/* "ｹﾞﾝｺｳ ﾂｲｶ      :    " */
				   D2W_Off2,					/* "                OFF " */
				   2,
				   &is_doc_add,
				   TRUE,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* 登録中止又は、タイムアップの時 */ /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return;
	}
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add By H.Fujimura 1999/01/21 */
	if (is_doc_add != SUB_ADDRESS_OPTION_DOC_ADD) {	/* 原稿追加が選択された時 */
#else
	if (is_doc_add) {	/* 原稿追加が選択された時 */
#endif
		/* 空いている最初のファイル番号を探します */
		file_number = SubaddressBoxDetectEmptyNo(sub_ptr->StoredDocBit);
		if (file_number == FULL_STORED) {	/* 空いているファイルがなかった時 */
			NackBuzzer();
			OPR_ChildErrorFlag = NOT_STORED_DOCUMENT_ERROR;	/* "ﾁｸｾｷ ﾃﾞｷﾏｾﾝ         " */
			return;
		}
	}
	else {				/* 原稿上書きが選択された時 */
		file_number = 0;	/* 上書き蓄積の時は先にメインで原稿を消去してから蓄積するため０としておく 1997/04/30  By T.Yamaguchi */
/*		file_number = 1;	/@ ファイル番号は、１固定です */
	}

	/* 蓄積する直前にもう一度ＦコードＢＯＸに蓄積できる状態か調べます 1997/05/14  By T.Yamaguchi */
	if ((sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_NO_SET)
	 && (sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_STORED)
	 && (sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVE)) {
		/* 受信中・送信中・蓄積中・消去中・プリント中の時は蓄積できません 1997/05/06  By T.Yamaguchi */
		NackBuzzer();
/*		OPR_ChildErrorFlag = NOT_STORED_DOCUMENT_ERROR;	*//* "ﾁｸｾｷ ﾃﾞｷﾏｾﾝ         " */
		OPR_ChildErrorFlag = BOX_IN_USE_ERROR;			  /* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */ /* Modified by S.Fukui Oct.13,1997 */
		return;
	}

	/* 蓄積できる状態かを調べます */
	switch (CheckScanStartEnable(OPR_DOC_SET_CHK_INP_SET)) {
	case OPR_SCAN_ENABLE:	/* 原稿読み取り可能な時 */

#if (0)	/* Add By O.Kimoto 1999/07/19 */
** 		if (CheckMemoryOver() == FALSE) [
#else
		if ((CheckMemoryOver() == FALSE) && (CheckScanDisableCondition() == FALSE)) {
#endif

			/* メインに蓄積開始のメッセージを送ります */
			OperationMessageToMain.Message = MSG_STORE_FCODE_BOX_DOC;
			OperationMessageToMain.SubMessage1 = file_number;
			OperationMessageToMain.SubMessage2 = (UWORD)(OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN);
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
		}
		else {
			NackBuzzer();
		}
		break;
	case OPR_SCAN_DISABLE:	/* 原稿読み取り不可能な時 */
		NackBuzzer();
		break;
	case OPR_SCAN_STOP:		/* ブック原稿サイズ入力中に停止又は、タイムアップした時 */
		/* ナックは鳴らしません */
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ番号選択]
	function	:[
		1.サブアドレスＢＯＸ番号を選択します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SelectFcodeBoxNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	box_number;		/* ＢＯＸ番号 */
	UBYTE	is_loop_end;
	UBYTE	stage;

	stage = SELECT_FCODE_BOX_STOP;	/* ＢＯＸ番号選択中止 */
	is_loop_end = FALSE;

	/* 上段の表示 */
	DisplayStringHigh(0, D2W_SelectFcodeBoxNumber);	/* "ﾎﾞｯｸｽ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ  " */

	while (is_loop_end != TRUE) {

		/* 下段の表示 */
		DisplaySelectFcodeBox();

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			is_loop_end = TRUE;
			break;
		case ENTER:
			if (OPR_FcodeData.BoxNumberInpPos > 0) {	/* ＢＯＸ番号入力途中の時 */
				NackBuzzer();
			}
			else {
				/* 選択された番号のサブアドレスＢＯＸデータを、作業用変数にコピーします */
				GetSubAddressBoxData();
				stage = CHECK_FCODE_PASS_CODE;	/* パスコード（暗証番号）チェックに移行 */
				is_loop_end = TRUE;
			}
			break;
		case FUNCTION:
			if (OPR_FcodeData.BoxNumberInpPos > 0) {	/* ＢＯＸ番号入力途中の時 */
				NackBuzzer();
			}
			else {
				/* ＢＯＸ番号を進めます */
				FcodeBoxNumberForwordOperation();
			}
			break;
		case LEFT_ARROW:
			if (OPR_FcodeData.BoxNumberInpPos > 0) {	/* ＢＯＸ番号入力途中の時 */
				NackBuzzer();
			}
			else {
				/* ＢＯＸ番号を戻します */
				FcodeBoxNumberBackOperation();
			}
			break;
		case CLEAR:
			if (OPR_FcodeData.BoxNumberInpPos > 0) {	/* ＢＯＸ番号を入力途中の時 */
				/* ＢＯＸ番号入力バッファのデータを１文字クリア */
				OPR_FcodeData.BoxNumberInpPos--;
				OPR_FcodeData.BoxNumberInpBuf[OPR_FcodeData.BoxNumberInpPos] = NULL;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:
			OPR_FcodeData.BoxNumberInpBuf[OPR_FcodeData.BoxNumberInpPos++] = key;
			if (OPR_FcodeData.BoxNumberInpPos >= OPR_FCODE_BOX_FIGURE_MAX) {
				/* 入力値を数値に変換します */
				box_number = (UBYTE)CMN_ASC_ToUnsignedInt(OPR_FcodeData.BoxNumberInpBuf,
														  OPR_FcodeData.BoxNumberInpPos);

				/* 入力値が適正値かどうかを調べます
				** （最大値の判断を、０・１どちらから始まっていても対応できるようにしておきます
				** 　SUB_ADDRESS_BOX_MAX -> SUB_ADDRESS_BOX_MAX - 1 + OPR_FCODE_BOX_MIN）
				*/
				if ((box_number >= OPR_FCODE_BOX_MIN) && (box_number <= SUB_ADDRESS_BOX_MAX - 1 + OPR_FCODE_BOX_MIN)) {
					OPR_FcodeData.BoxNumber = (UBYTE)(box_number - OPR_FCODE_BOX_MIN);
				}
				else {
					NackBuzzer();
				}
				CMN_MemorySet(OPR_FcodeData.BoxNumberInpBuf, OPR_FCODE_BOX_FIGURE_MAX + 1, NULL);
				OPR_FcodeData.BoxNumberInpPos = 0;
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}

	return(stage);
}

/************************************************************************
	module		:[サブアドレスＢＯＸ　暗証番号（パスコード）検査]
	function	:[
		1.指定のＢＯＸの暗証番号を入力し、登録されている暗証番号と
		　一致するかを調べます
	]
	return		:[
		ENTER_FCODE_BOX_NAME	:1.ＢＯＸ初期登録の時
								 2.ＢＯＸが掲示板で登録されていて、暗証番号が未登録の時
								 3.暗証番号が一致した時
		SET_FCODE_STOP			:1.入力が中止された時
								 2.間違った暗証番号が入力された時
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
************************************************************************/
UBYTE CheckFcodePassCode(void)
{
	UWORD	passcode;
	UBYTE	stage;

	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	/* 1.ＢＯＸ初期登録の時は、暗証番号は登録されていないのでチェックは行いません
	** 2.ＢＯＸが掲示板で登録されていて、暗証番号が未登録の時はチェックは行いません
	*/
	if ((OPR_FcodeData.Status == SUB_ADDRESS_BOX_EMPTY)
	 || ((OPR_FcodeData.Status == SUB_ADDRESS_BULLETIN_BOX) && (OPR_FcodeData.PassCode == 0))) {
		stage = ENTER_FCODE_BOX_NAME;	/* ＢＯＸ名登録に移行 */
	}
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
	/* ＢＯＸが中継で登録されていて、暗証番号が未登録の時はチェックは行いません */
	else if ((OPR_FcodeData.Status == SUB_ADDRESS_RELAY_BOX) && (OPR_FcodeData.PassCode == 0)) {
		stage = ENTER_FCODE_BOX_NAME;	/* ＢＯＸ名登録に移行 */
	}
#endif
	else {
		passcode = EnterPassCode(OPR_FcodeData.PassCode, CHK_PASS_CODE_ENTER, D2W_EnterFcodePasscode);
																		/* "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :****" */

		if (passcode != 0xFFFF) {	/* 登録中止でない時 */
			if (passcode == OPR_FcodeData.PassCode) {	/* 暗証番号が一致した時 */
				stage = ENTER_FCODE_BOX_NAME;	/* ＢＯＸ名登録に移行 */
			}
			else {										/* 暗証番号が違う時 */
				/* 間違った暗証番号を入力された場合、登録はできないので終了する */
				NackBuzzer();
				OPR_ChildErrorFlag = INVALID_ID_CODE_ERROR;	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    " */
			}
		}
	}

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ名登録]
	function	:[
		1.指定のＢＯＸのＢＯＸ名を登録します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetFcodeBoxName(void)
{
	UBYTE	stage;

	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	/* 名前入力初期処理 */
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	CMN_StringCopy(CharacterInput.Buffer, OPR_FcodeData.BoxName);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_BOX_NAME_MAX - 1;

	/* ボックス名登録 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
#else
	if (NameInput(OPR_KANJI_DISABLE) == OK) {	/* 登録完了 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		/* ボックス名は登録されていなくても構わない */
		StoreCharacterInputValue(OPR_FcodeData.BoxName, ASC_DATA_TYPE);
		stage = ENTER_FCODE_SUB;	/* サブアドレス番号登録に移行 */
	}

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　サブアドレス番号登録]
	function	:[
		1.指定のＢＯＸのサブアドレス番号を登録します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetFcodeSubAddress(void)
{
	UBYTE	i;				/* ループ変数 */
	UBYTE	is_set_ok;
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	stage;

	/* 初期化 */
	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */
	ClearCharacterInput();
	CMN_StringCopy(CharacterInput.Buffer, OPR_FcodeData.SubAddress);
	CharacterInput.MaxFigure = SYS_ID_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {
		if (InputFcodeNumber(OPR_FCODE_SET_SUB_ADDRESS) == OK) {	/* サブアドレス番号が登録された時 */

			/* サブアドレスは、必ず登録される必要があります */
			if (CharacterInput.Buffer[0] == NULL) {
				NackBuzzer();
				ChildDisplayStringLow(D2W_InvalidNumber);	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
				continue;
			}

			/* 登録するサブアドレスが、すでに他のＢＯＸで登録されている場合は登録を禁止します */
			is_set_ok = TRUE;
			for (i = 0; i < SUB_ADDRESS_BOX_MAX; i++) {
				/* 現在登録中のＢＯＸは比較しない */
				if (i != OPR_FcodeData.BoxNumber) {
					/* 登録するサブアドレスと、他のＢＯＸのサブアドレスを比較します */
					if (CMN_StringCompare(CharacterInput.Buffer, SYB_SubAddressBoxTable[i].SubAddress, SYS_ID_MAX)
						== STRCMP_EQUAL) {
						is_set_ok = FALSE;
						break;
					}
				}
			}

			if (is_set_ok) {	/* 登録するサブアドレスが重複していなかった時 */
				/* 入力された番号を編集用変数にセットします */
				StoreCharacterInputValue(OPR_FcodeData.SubAddress, ASC_DATA_TYPE);
				stage = ENTER_FCODE_PWD;	/* 通信パスワード番号登録に移行 */
				is_loop_end = TRUE;
			}
			else {
				NackBuzzer();
				ChildDisplayStringLow(D2W_SameNumber);	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾄｳﾛｸｻﾚﾃｲﾏｽ" */
			}
		}
		else {	/* サブアドレス番号入力が中止・タイムアップした時 */
			is_loop_end = TRUE;
		}
	}

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　通信パスワード番号登録]
	function	:[
		1.指定のＢＯＸの通信パスワード番号を登録します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetFcodePassword(void)
{
	UBYTE	stage;

	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	if (InputFcodePassword() == OK) {	/* 通信パスワード番号が登録された時 */
		/* ＢＯＸ初期登録の時は、掲示板ＢＯＸで使用するか、親展ＢＯＸで使用するかの選択を行います */
		switch (OPR_FcodeData.Status) {
		case SUB_ADDRESS_BOX_EMPTY:		/* ボックス未使用 */
			stage = SELECT_FCODE_KIND;		/* ＢＯＸ種類選択に移行 */
			break;
		case SUB_ADDRESS_BULLETIN_BOX:	/* 掲示板登録 */
			stage = ENTER_FCODE_OPTION;		/* オプション設定に移行 */
			break;
		case SUB_ADDRESS_SECURE_BOX:	/* 親展登録 */
			stage = ENTER_FCODE_HOLDTIME;	/* 原稿保持期間設定に移行 */
			break;
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
		case SUB_ADDRESS_RELAY_BOX:		/* 中継登録 */
			stage = ENTER_FCODE_RELAY_BOX;	/* 中継ＢＯＸ設定に移行 */
			break;
#endif
		default:
			break;
		}
	}

	return(stage);
}

/************************************************************************
	module		:[サブアドレスＢＯＸ　ＢＯＸ種類選択]
	function	:[
		1.登録するＢＯＸの種類を選択します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
************************************************************************/
UBYTE SelectFcodeBoxKind(void)
{
	UBYTE	box_kind;
	UBYTE	stage;

	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */
	box_kind = 0;

#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
	if (SelectData(D2W_SelectFcodeBoxKind,		/* "ﾎﾞｯｸｽ ｼｭﾍﾞﾂ :       " */
				   D2W_FcodeBulletinBoardBox,	/* "             ｹｲｼﾞﾊﾞﾝ" */
				   3,
				   &box_kind,
				   0xFF,
				   NO_KEYTYPE) == OPR_ENTERED) {	/* 登録された時 */	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		if (box_kind == 0) {		/* 掲示板ＢＯＸが選択された時 */
			OPR_FcodeData.Status = SUB_ADDRESS_BULLETIN_BOX;	/* 掲示板登録 */
			stage = ENTER_FCODE_OPTION;		/* オプション設定に移行 */
		}
		else if (box_kind == 1) {	/* 親展ＢＯＸが選択された時 */
			OPR_FcodeData.Status = SUB_ADDRESS_SECURE_BOX;		/* 親展登録 */
			stage = ENTER_FCODE_HOLDTIME;	/* 原稿保持期間設定に移行 */
		}
		else {						/* 中継ＢＯＸが選択された時 */
			OPR_FcodeData.Status = SUB_ADDRESS_RELAY_BOX;		/* 中継登録 */
			ClearDialNumber2(NULL, OPR_FcodeData.Onetouch, OPR_FcodeData.Speed, &OPR_FcodeData.Group);
			stage = ENTER_FCODE_RELAY_BOX;	/* 中継ＢＯＸ設定に移行 */
		}
	}
#else
	if (SelectData(D2W_SelectFcodeBoxKind,		/* "ﾎﾞｯｸｽ ｼｭﾍﾞﾂ :       " */
				   D2W_FcodeBulletinBoardBox,	/* "             ｹｲｼﾞﾊﾞﾝ" */
				   2,
				   &box_kind,
				   0x01,
				   NO_KEYTYPE) == OPR_ENTERED) {	/* 登録された時 */	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		if (box_kind == 0) {	/* 掲示板ＢＯＸが選択された時 */
			OPR_FcodeData.Status = SUB_ADDRESS_BULLETIN_BOX;	/* 掲示板登録 */
			stage = ENTER_FCODE_OPTION;		/* オプション設定に移行 */
		}
		else {					/* 親展ＢＯＸが選択された時 */
			OPR_FcodeData.Status = SUB_ADDRESS_SECURE_BOX;		/* 親展登録 */
			stage = ENTER_FCODE_HOLDTIME;	/* 原稿保持期間設定に移行 */
		}
	}
#endif

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　オプション設定]
	function	:[
		1.掲示板ＢＯＸに対するオプション設定を行います
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/21]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetFcodeOption(void)
{
	UBYTE	option;
	UBYTE	stage;

	option = OPR_FcodeData.Option;
	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	/* 受信禁止設定 */
	if (SelectData(D2W_SelectFcodeRxProhibition,	/* "ｼﾞｭｼﾝ ｷﾝｼ      :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &option,
				   SUB_ADDRESS_OPTION_RECEIVE,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */ /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(stage);
	}

	/* 受信原稿プリント許可 */
	if (SelectData(D2W_SelectFcodeRxDocPrint,		/* "ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ    :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &option,
				   SUB_ADDRESS_OPTION_PRINT,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(stage);
	}

	/* 受信原稿上書き許可 */
	if (SelectData(D2W_SelectFcodeRxDocUpperWrite,	/* "ｹﾞﾝｺｳ ｳﾜｶﾞｷ    :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &option,
				   SUB_ADDRESS_OPTION_DOC_ADD,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(stage);
	}

	/* 送信原稿消去許可 */
	if (SelectData(D2W_SelectFcodeTxDocClear,		/* "ｿｳｼﾝ ｹﾞﾝｺｳ ｸﾘｱ :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &option,
				   SUB_ADDRESS_OPTION_ERASE,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(stage);
	}

	OPR_FcodeData.Option = option;
	stage = ENTER_FCODE_PASS_CODE;	/* パスコード（暗証番号）登録に移行 */

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　原稿保持期間設定]
	function	:[
		1.親展ＢＯＸに対する原稿保持期間を設定します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/21]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetFcodeHoldTime(void)
{
	UWORD	hold_time;
	UBYTE	stage;

	hold_time = 0;
	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	DisplayStringHigh(0, D2W_FcodeDocumentHoldTime);		/* "ｹﾞﾝｺｳ ﾒﾓﾘｷｶﾝ        " */
	/* 保持期間を設定する関数を作る事 */
	hold_time = FixedLengthNumberInput((UWORD)OPR_FcodeData.HoldTime, 0, 31, (UBYTE)18, D2W_HoldTime0_31);
																			/* "ﾒﾓﾘｷｶﾝ   (0-31):    " */
	if (hold_time != 0xFFFF) {	/* 登録された時 */
		OPR_FcodeData.HoldTime = (UBYTE)hold_time;
		stage = ENTER_FCODE_PASS_CODE;	/* パスコード（暗証番号）登録に移行 */
	}
	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　暗証番号（パスコード）登録]
	function	:[
		1.指定のＢＯＸの暗証番号を登録します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/18]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetFcodePassCode(void)
{
	UBYTE	zero_inp_mode;
	UWORD	passcode;
	UBYTE	stage;

	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	/* パスコード登録 */
	if (OPR_FcodeData.Status == SUB_ADDRESS_BULLETIN_BOX) {	/* 掲示板登録 */
		/* "0000"の入力を受け付けます */
		zero_inp_mode = PASS_CODE_ENTER_ZERO_OK;
	}
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
	else if (OPR_FcodeData.Status == SUB_ADDRESS_RELAY_BOX) {	/* 中継登録 */
		/* "0000"の入力を受け付けます */
		zero_inp_mode = PASS_CODE_ENTER_ZERO_OK;
	}
#endif
	else {													/* 親展登録 */
		/* "0000"の入力を受け付けません */
		zero_inp_mode = PASS_CODE_ENTER_ZERO_NG;
	}

	passcode = EnterPassCode(OPR_FcodeData.PassCode, zero_inp_mode, D2W_EnterFcodePasscode);
																/* "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :9999" */
	if (passcode != 0xFFFF) {	/* 登録中止でない時 */
		OPR_FcodeData.PassCode = passcode;
		stage = SET_FCODE_COMPLETE;	/* ＢＯＸ登録完了 */
	}

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ登録処理]
	function	:[
		1.編集用バッファの内容をサブアドレスＢＯＸ管理テーブルにコピーします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/21]
	author		:[渡辺一章]
*************************************************************************/
void SetFcodeComplete(void)
{
	struct	SYS_SubAddressBoxData_t	*sub_ptr;

	sub_ptr = &SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber];

	/** サブアドレスＢＯＸ管理テーブルの登録状態（種類） */
	sub_ptr->Status = OPR_FcodeData.Status;

	/** ボックス名 */
	CMN_StringCopyNULL(sub_ptr->BoxName, OPR_FcodeData.BoxName);

	/** サブアドレス番号 */
	CMN_StringCopyNULL(sub_ptr->SubAddress, OPR_FcodeData.SubAddress);

	/** 通信パスワード */
	CMN_StringCopyNULL(sub_ptr->PassWord, OPR_FcodeData.Password);

	if (OPR_FcodeData.Status == SUB_ADDRESS_SECURE_BOX) {	/* 親展登録 */
		/** 原稿保持期間 */
		sub_ptr->HoldTime = OPR_FcodeData.HoldTime;
	}
	else {													/* 掲示板登録 */
		/** オプション設定 */
		sub_ptr->Option = OPR_FcodeData.Option;
	}

	/** パスコード */
	sub_ptr->PassCode = OPR_FcodeData.PassCode;

#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
	/* 中継配信先（ワンタッチ）*/
	CMN_StringCopyNum(sub_ptr->Onetouch, OPR_FcodeData.Onetouch, SYS_ONETOUCH_BIT_FIELD_MAX);

	/* 中継配信先（短縮）*/
	CMN_StringCopyNum(sub_ptr->Speed, OPR_FcodeData.Speed, SYS_SPEED_BIT_FIELD_MAX);

	/* 中継配信先（グループ）*/
	sub_ptr->Group = OPR_FcodeData.Group;
#endif
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ登録作業用変数クリア]
	function	:[
		1.サブアドレスＢＯＸ登録時の作業用変数を初期化します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/18]
	author		:[渡辺一章]
*************************************************************************/
void ClearFcodeControlData(void)
{
	/* ボックス番号 */
	OPR_FcodeData.BoxNumber = 0;

	/* ボックス番号入力位置 */
	OPR_FcodeData.BoxNumberInpPos = 0;

	/* ボックス番号入力バッファ */
	CMN_MemorySet(OPR_FcodeData.BoxNumberInpBuf, OPR_FCODE_BOX_FIGURE_MAX + 1, NULL);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ登録中　上段表示]
	function	:[
		1.サブアドレスＢＯＸ登録中の上段表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/16]
	author		:[渡辺一章]
*************************************************************************/
void DisplaySetFcodeBox(UBYTE stage)
{
	UBYTE	is_display_high;	/* 上段表示を行うか */

	if (CheckChildErrorDisplayReq() == TRUE) {	/* チャイルド表示すべきエラーが発生した */
		DisplayChildError();
		return;
	}

	if (CheckChildDisplay() == TRUE) {	/* チャイルド表示中 */
		return;
	}

	is_display_high = TRUE;
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	switch (stage) {
	case CHECK_FCODE_PASS_CODE:	/** パスコード（暗証番号）チェック */
	case ENTER_FCODE_PASS_CODE:	/** パスコード（暗証番号）登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterFcodeBoxMode);		/* "   ﾎﾞｯｸｽ ｾｯﾄ        " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN,
							 OPR_FCODE_BOX_FIGURE_MAX,
							 '0');
		FunctionDisplayBufferHigh[OPR_FCODE_BOX_FIGURE_MAX] = ':';
		break;
	case ENTER_FCODE_BOX_NAME:	/** ＢＯＸ名登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterFcodeBoxName);		/* "  :ﾎﾞｯｸｽﾒｲ          " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN,
							 OPR_FCODE_BOX_FIGURE_MAX,
							 '0');
		break;
	case ENTER_FCODE_SUB:		/** サブアドレス番号登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterFcodeSubAddress);	/* "  :ｻﾌﾞｱﾄﾞﾚｽ ﾊﾞﾝｺﾞｳ  " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN,
							 OPR_FCODE_BOX_FIGURE_MAX,
							 '0');
		break;
	case ENTER_FCODE_PWD:		/** 通信パスワード番号登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterFcodePassword);		/* "  :ﾊﾟｽﾜｰﾄﾞ ﾊﾞﾝｺﾞｳ   " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN,
							 OPR_FCODE_BOX_FIGURE_MAX,
							 '0');
		break;
	case ENTER_FCODE_HOLDTIME:	/** 原稿保持期間設定 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_FcodeDocumentHoldTime);	/* "ｹﾞﾝｺｳ ﾒﾓﾘｷｶﾝ        " */
		break;
	case SELECT_FCODE_BOX_NO:	/** ＢＯＸ番号選択 */
	case SELECT_FCODE_KIND:		/** ＢＯＸ種類選択 */
	case ENTER_FCODE_OPTION:	/** オプション設定 */
	case SET_FCODE_STOP:		/** ＢＯＸ登録中止 */
	default:
		/* それぞれの関数の中で表示を行います */
		is_display_high = FALSE;
		break;
	}

	if (is_display_high) {
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ選択　下段表示]
	function	:[
		1.サブアドレスＢＯＸ番号が選択されている時、登録内容を表示します
		2.サブアドレスＢＯＸ番号がテンキーにて選択中の時、入力内容を表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
void DisplaySelectFcodeBox(void)
{
	struct	SYS_SubAddressBoxData_t	*sub_ptr;

	if (CheckChildErrorDisplayReq() == TRUE) {	/* チャイルド表示すべきエラーが発生した */
		DisplayChildError();
		return;
	}

	if (CheckChildDisplay() == TRUE) {	/* チャイルド表示中 */
		return;
	}

	sub_ptr = &SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber];
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	if (OPR_FcodeData.BoxNumberInpPos == 0) {	/* ＢＯＸ番号入力途中でない時 */
		/* 現在選択されているＢＯＸ番号を表示用バッファにセットします */
		CMN_UnsignedIntToASC(FunctionDisplayBufferLow,
							 OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN,
							 OPR_FCODE_BOX_FIGURE_MAX,
							 '0');
		FunctionDisplayBufferLow[OPR_FCODE_BOX_FIGURE_MAX] = ':';

		/* ＢＯＸの設定状況を調べます */
		if (sub_ptr->Status != SUB_ADDRESS_BOX_EMPTY) {	/* 登録済みの時 */
			/* ＢＯＸ名を表示用バッファにコピーします */
			CMN_StringCopy(&FunctionDisplayBufferLow[OPR_FCODE_BOX_FIGURE_MAX + 1], sub_ptr->BoxName);
		}
		else {											/* 未登録の時 */
			CMN_StringCopyNum(&FunctionDisplayBufferLow[OPR_FCODE_BOX_FIGURE_MAX + 1],
							  D2W_NoNumberStored,									/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
							  OPR_DISPLAY_MAX - (OPR_FCODE_BOX_FIGURE_MAX + 1));
		}
	}
	else {
		CMN_StringCopy(FunctionDisplayBufferLow, OPR_FcodeData.BoxNumberInpBuf);
	}

	/* 下段の表示 */
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ番号前進処理]
	function	:[
		1.ＢＯＸ番号を次に進めます
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
void FcodeBoxNumberForwordOperation(void)
{
	/* ＢＯＸ番号の最後までいったら先頭に戻します */
	if (OPR_FcodeData.BoxNumber >= SUB_ADDRESS_BOX_MAX - 1) {
		OPR_FcodeData.BoxNumber = 0;
	}
	else {
		/* ＢＯＸ番号を進めます */
		OPR_FcodeData.BoxNumber++;
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ番号後退処理]
	function	:[
		1.ＢＯＸ番号を前に戻します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
void FcodeBoxNumberBackOperation(void)
{
	/* ＢＯＸ番号が先頭の時は、最後の値にします */
	if (OPR_FcodeData.BoxNumber == 0) {
		OPR_FcodeData.BoxNumber = SUB_ADDRESS_BOX_MAX - 1;
	}
	else {
		/* ＢＯＸ番号を戻します */
		OPR_FcodeData.BoxNumber--;
	}
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ登録内容コピー]
	function	:[
		1.指定のＢＯＸ番号に対する、サブアドレスＢＯＸ内容を
		　作業用バッファにコピーします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/18]
	author		:[渡辺一章]
*************************************************************************/
void GetSubAddressBoxData(void)
{
	struct	SYS_SubAddressBoxData_t	*sub_ptr;

	sub_ptr = &SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber];

	/* サブアドレスＢＯＸ管理テーブルの登録状態（種類） */
	OPR_FcodeData.Status = sub_ptr->Status;

	/* ボックス名 */
	CMN_StringCopyNULL(OPR_FcodeData.BoxName, sub_ptr->BoxName);

	/* サブアドレス番号 */
	CMN_StringCopyNULL(OPR_FcodeData.SubAddress, sub_ptr->SubAddress);

	/* 通信パスワード */
	CMN_StringCopyNULL(OPR_FcodeData.Password, sub_ptr->PassWord);

	/* 原稿保持期間 */
	OPR_FcodeData.HoldTime = sub_ptr->HoldTime;

	/* オプション設定 */
	OPR_FcodeData.Option = sub_ptr->Option;

	/* パスコード */
	OPR_FcodeData.PassCode = sub_ptr->PassCode;

#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
	/* 中継配信先（ワンタッチ）*/
	CMN_StringCopyNum(OPR_FcodeData.Onetouch, sub_ptr->Onetouch, SYS_ONETOUCH_BIT_FIELD_MAX);

	/* 中継配信先（短縮）*/
	CMN_StringCopyNum(OPR_FcodeData.Speed, sub_ptr->Speed, SYS_SPEED_BIT_FIELD_MAX);

	/* 中継配信先（グループ）*/
	OPR_FcodeData.Group = sub_ptr->Group;
#endif
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ通信パスワード番号入力]
	function	:[
		1.通信パスワード番号の入力を行います
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
UBYTE InputFcodePassword(void)
{
	UBYTE	ret;

	/* 初期化 */
	ret = NG;
	ClearCharacterInput();
	CMN_StringCopy(CharacterInput.Buffer, OPR_FcodeData.Password);
	CharacterInput.MaxFigure = SYS_ID_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	if (InputFcodeNumber(OPR_FCODE_SET_PASSWORD) == OK) {	/* 通信パスワード番号が登録された時 */
		/* 入力された番号を編集用変数にセットします */
		StoreCharacterInputValue(OPR_FcodeData.Password, ASC_DATA_TYPE);
		ret = OK;
	}

	return(ret);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　番号入力処理]
	function	:[
		1.サブアドレス番号・通信パスワード等の入力を行います
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE InputFcodeNumber(UBYTE set_kind)
{
	UBYTE	key;			/* キー取り込みデータ */
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	ret;			/* リターン値 */

	is_loop_end = FALSE;
	ret = NG;

	/** データ入力 */
	while (is_loop_end != TRUE) {
		/** 下段に登録内容を表示 */
		DisplayNumberInput();

		/** キー取り込みと共通処理を実行 */
		key = NumberInputKeyGet();
		switch (key) {
		case STOP_KEY:			/* ストップキー		*/
			is_loop_end = TRUE;
			break;
		case SET_KEY:			/* セットキー		*/
			ret = OK;
			is_loop_end = TRUE;
			break;
		case TEN_SHARP_KEY:		/* テンキー＃キー	*/
		case TEN_AST_KEY:		/* テンキー＊キー	*/

#if (0) /* 新しい仕様でとりあえず#if 0にする S.Wang 98/08/31 */
** 		/* POPLAR_Bでサブアドレス番号、通信パスワード登録の時 ＃,＊,SPACEキー有効 */
** #if (PRO_KEYPANEL == PANEL_POPLAR_B)
** 			CharacterDataSet_FigureCheck(key);
** 			break;
** 		case ONETOUCH_32_KEY:	/* SPACEキー		*/
** 			CharacterDataSet_FigureCheck(OnetouchSignalTable[CMN_OnetouchCodeToOffset(key)]);
** 			break;
** #endif
#endif
			if (set_kind == OPR_FCODE_SET_PASSWORD) {	/* 通信パスワード番号登録の時 */
				CharacterDataSet_FigureCheck(key);
			}
			else {										/* サブアドレス番号登録の時 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 		/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
				if (CHK_UNI_FcodeSpaceInputEnable()) {
					CharacterDataSet_FigureCheck(key);
				}
				else {
					NackBuzzer();
				}

#else
				NackBuzzer();
#endif
			}
			break;
		case OPR_NO_KEY:		/* 処理実行済み		*/
			break;
		default:
			NackBuzzer();
			break;
		}
	}

	CursorOff();
	return(ret);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　蓄積原稿ＢＯＸ番号選択＆ファイル番号入力]
	function	:[
		1.原稿が蓄積されているＢＯＸ番号を選択します
		2.選択したＢＯＸの暗証番号を確認します
		3.掲示板ＢＯＸを選択した時のみ、ファイルを指定します
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		注）掲示板ＢＯＸを選択した時は、必ずファイルを指定する必要があります
			親展ＢＯＸを選択した時は、無条件に全ファイルが選択されます
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/22]
	author		:[渡辺一章]
*************************************************************************/
UBYTE InputFcodeStoreDocFile(UBYTE mode, UBYTE *file_item, UWORD *doc_number)
{
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	struct	SYS_SubAddressBoxData_t	*sub_ptr;

	/* サブアドレスＢＯＸ登録作業用変数クリア */
	ClearFcodeControlData();

	/** データ入力 */
	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {

		/* 原稿が蓄積されているＢＯＸ番号を選択します */
		if (SelectFcodeBoxNumber() == SELECT_FCODE_BOX_STOP) {	/* 選択が中止された時 */
			return(NG);
		}
		sub_ptr = &SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber];

		/*----------------------------*/
		/* 選択されたＢＯＸのチェック */
		/*----------------------------*/
		if (OPR_FcodeData.Status == SUB_ADDRESS_BOX_EMPTY) {
			/* 未登録のＢＯＸが選択された時 */
			NackBuzzer();
		}
		else if ((mode == OPR_FCODE_STORE_DOC_ERASE) && (OPR_FcodeData.Status == SUB_ADDRESS_SECURE_BOX)) {
			/* 原稿消去モードで親展ＢＯＸが選択された時 1997/05/14  By T.Yamaguchi */
			NackBuzzer();
			OPR_ChildErrorFlag = SETTING_SECURE_BOX_ERROR;	/* "ｼﾝﾃﾝﾎﾞｯｸｽ ﾃﾞｽ       " */
		}
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
		else if (OPR_FcodeData.Status == SUB_ADDRESS_RELAY_BOX) {
			/* 中継ＢＯＸが選択された時 */
			NackBuzzer();
			OPR_ChildErrorFlag = SETTING_RELAY_BOX_ERROR;	/* "ﾁｭｳｹｲﾎﾞｯｸｽ ﾃﾞｽ      " */
		}
#endif
		else if (sub_ptr->DataStatus == SYS_SUB_ADDRESS_BOX_NO_SET) {
			/* 選択されたＢＯＸに蓄積原稿がない時 */
			NackBuzzer();
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      " */
		}
		else if ((sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_STORED)
			  && (sub_ptr->DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVE)) {
			/* 選択されたＢＯＸが受信中・送信中・蓄積中・消去中・プリント中の時 */
			NackBuzzer();
			OPR_ChildErrorFlag = BOX_IN_USE_ERROR;			/* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */
		}
		else {
			is_loop_end = TRUE;
		}
	}

	/* ＢＯＸ選択後の上段表示 */
	if (mode == OPR_FCODE_STORE_DOC_PRINT) {
		DisplayFcodeBoxNumberAndTitle(D2W_PrintFcodeStoreDocMode);	/* "   ﾁｸｾｷ ｹﾞﾝｺｳ ﾌﾟﾘﾝﾄ " */
	}
	else {
		DisplayFcodeBoxNumberAndTitle(D2W_EraseFcodeDocMode);		/* "   ﾁｸｾｷ ｹﾞﾝｺｳ ｸﾘｱ   " */
	}

	/* 選択したＢＯＸの暗証番号を入力します */
	if (CheckFcodePassCode() == SET_FCODE_STOP) {	/* 間違った暗証番号が入力されたか、入力が中止された時 */
		return(NG);
	}

	/* 掲示板ＢＯＸが選択された時は、ファイルを指定する必要があります
	** （親展ＢＯＸの時は、無条件に全ファイル指定になります）
	*/
	if (OPR_FcodeData.Status == SUB_ADDRESS_BULLETIN_BOX) {	/* 掲示板登録 */
		/* 暗証番号が一致したらファイル番号を指定します */
		if (NumberInput(OPR_FCODE_BOX_DOC_NUMBER_INPUT) == NG) {	/* 登録が中止された時 */
			return(NG);
		}
		*doc_number = CharacterInputToNumber();

		if (*doc_number) {	/* ファイル番号が指定されている時 */
			/* 指定されたファイル番号の原稿が存在するかをチェックします */
			if (!CMN_CheckLongBitAssign(sub_ptr->StoredDocBit, (UBYTE)(*doc_number - 1))) {
				NackBuzzer();
				OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      " */
				return(NG);
			}
		}
		else {				/* ファイル番号指定なし（０が入力された）の時 */
			*doc_number = MEM_ALL_NO;
		}
		*file_item = SYS_MEM_SUB_BULLETIN_FILE;
	}
	else {													/* 親展登録 */
		*doc_number = MEM_ALL_NO;
		*file_item = SYS_MEM_SUB_SECURE_FILE;
	}

	return(OK);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ選択後の上段表示]
	function	:[
		1.選択されたＢＯＸ番号と、ＢＯＸに対する処理を表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/05]
	author		:[渡辺一章]
*************************************************************************/
void DisplayFcodeBoxNumberAndTitle(UBYTE *title_wording)
{
	CMN_StringCopy(FunctionDisplayBufferHigh, title_wording);
	CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
						 OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN,
						 OPR_FCODE_BOX_FIGURE_MAX,
						 '0');
	FunctionDisplayBufferHigh[OPR_FCODE_BOX_FIGURE_MAX] = ':';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

/*************************************************************************
	module		:[Ｆコードデータ格納バッファ空き領域獲得]
	function	:[
		1.Ｆコードデータ格納バッファの空き領域を探します
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
UBYTE GetEmptyFcodeNumberData(UBYTE mode)
{
	UBYTE	i;
	UBYTE	ret;

	ret = 0xFF;

	if (mode == OPR_COM_OPE) {	/* コマンド入力から呼ばれた時 */
		/* Ｆコードデータ格納バッファ（コマンドファイル登録用）の空き領域を探します */
		for (i = 0; i < SYS_COM_FILE_MAX; i++) {
			if (SYB_FcodeNumberCDataBuffer[i].SYS_SubAddressNumber[0] == 0xFF) {
				ret = i;
				break;
			}
		}
	}
	else {						/* プログラムワンタッチ登録から呼ばれた時 */
		/* Ｆコードデータ格納バッファ（プログラムワンタッチ登録用）の空き領域を探します */
		for (i = 0; i < SYS_PROGRAM_MAX; i++) {
			if (SYB_FcodeNumberPDataBuffer[i].SYS_SubAddressNumber[0] == 0xFF) {
				ret = i;
				break;
			}
		}
	}

	return(ret);
}

#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
/*************************************************************************
	module		:[サブアドレスＢＯＸ　中継ＢＯＸ設定]
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
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	SetFcodeRelayBox(void)
{
	UBYTE	Onetouch[SYS_ONETOUCH_BIT_FIELD_MAX];	/* 中継配信先（ワンタッチ）*/
	UBYTE	Speed[SYS_SPEED_BIT_FIELD_MAX];			/* 中継配信先（短縮）*/
	UDWORD	Group;									/* 中継配信先（グループ）*/
	UBYTE	option;
	UBYTE	stage;

	CMN_StringCopyNum(Onetouch, OPR_FcodeData.Onetouch, SYS_ONETOUCH_BIT_FIELD_MAX);
	CMN_StringCopyNum(Speed, OPR_FcodeData.Speed, SYS_SPEED_BIT_FIELD_MAX);
	Group = OPR_FcodeData.Group;
	option = OPR_FcodeData.Option;
	stage = SET_FCODE_STOP;	/* ＢＯＸ登録中止 */

	/*--------*/
	/* 配信先 */
	/*--------*/
	DisplayStringHigh(0, D2W_InputRelayNumber);		/* "ﾊｲｼﾝｻｷ ｦ ﾄﾞｳｿﾞ      " */
	if (FcodeRelayNumberInput(Onetouch, Speed, &Group) == NG) {
		return(stage);
	}

	/*--------------*/
	/* 配信時発信元 */
	/*--------------*/
	if (option & SUB_ADDRESS_OPTION_TTI_INSIDE) {
		option &= ~SUB_ADDRESS_OPTION_TTI_AVAIL;
	}
	if (SelectData(D2W_SetRelayTTI[0],				/* "ﾊｲｼﾝｼﾞ ﾊｯｼﾝﾓﾄ:\0     " */
				   D2W_SetRelayTTI[1],				/* "              ﾂｹﾅｲ  " */
				   3,
				   &option,
				   SUB_ADDRESS_OPTION_TTI_AVAIL | SUB_ADDRESS_OPTION_TTI_INSIDE,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		if (option & SUB_ADDRESS_OPTION_TTI_INSIDE) {
			option |= SUB_ADDRESS_OPTION_TTI_AVAIL;
		}
		return(stage);
	}
	if (option & SUB_ADDRESS_OPTION_TTI_INSIDE) {
		option |= SUB_ADDRESS_OPTION_TTI_AVAIL;
	}

	/*--------------*/
	/* 同時プリント */
	/*--------------*/
	if (SelectData(D2W_SelectFcodeRxDocPrint,		/* "ﾄﾞｳｼﾞ ﾌﾟﾘﾝﾄ    :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &option,
				   SUB_ADDRESS_OPTION_PRINT,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(stage);
	}

	CMN_StringCopyNum(OPR_FcodeData.Onetouch, Onetouch, SYS_ONETOUCH_BIT_FIELD_MAX);
	CMN_StringCopyNum(OPR_FcodeData.Speed, Speed, SYS_SPEED_BIT_FIELD_MAX);
	OPR_FcodeData.Group = Group;
	OPR_FcodeData.Option = option;
	stage = ENTER_FCODE_PASS_CODE;	/* パスコード（暗証番号）登録に移行 */

	return(stage);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ　中継ＢＯＸ（配信先）設定]
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
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	FcodeRelayNumberInput(UBYTE *Onetouch, UBYTE *Speed, UDWORD *Group)
{
	UBYTE	key;
	UBYTE	keytype;
	UWORD	buf_count;		/* ダイヤルデータ位置					*/
	UBYTE	direct_count;	/* 直接ダイヤル件数						*/

	/** 初期化 */
	CommandInputInitial();		/* コマンド登録用バッファを初期化 */
	InputNumber.InputDialType = PROGRAM_DIAL_TYPE;
	SetPinCheckStatus();
	SetDialDataToDispBuffer2(OPR_PROGRAM_DISPLAY,
							 NULL,
							 Onetouch,
							 Speed,
							 *Group,
							 InputNumber.Buffer);

	while (1) {
		/* 下段表示[123456789_         ] */
		if (CheckChildErrorDisplayReq() == TRUE) {	/* チャイルド表示要求有り */
			DisplayChildError();
		}
		else if (CheckChildDisplay() == FALSE) {	/* チャイルド表示中でない */
			DisplayCommandNumber();
		}

		/* キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/* 短縮・グループキーの直後のデータ入力チェック */
		if (CheckSpeedGroupAfterEnableKey(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

#if (PRO_NEW_DIAL_OPR == ENABLE)
		/* 入力データ（短縮・グループ）の登録チェック by K.Watanabe 1998/04/02 */
		if (CheckRegistrationData(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}

		/* ダイヤルデータ入力チェック by K.Watanabe 1998/03/24 */
		if (CheckInputDialData(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}
#endif

#if (PRO_NEW_DIAL_OPR2 == ENABLE)
		/* 直接ダイヤル入力桁数・件数チェック by K.Watanabe 1998/04/17 */
		if (CheckInputDirectDial(keytype) == FALSE) {
			NackBuzzer();
			continue;
		}
#endif

		switch (keytype) {	/* 取り込んだキーのキー種別毎の処理 */
		case AST:			/*   *   */
		case NUMBER:		/* 0 - 9 */
		case SHARP:			/*   #   */
			InputNumberTenKeySet(key);
			break;

		case ONETOUCH:		/* ワンタッチキー入力 */
			if (CheckInputOnetouchEnable(key) == TRUE) {
				InputNumberOnetouchSet(key);
			}
			break;

		case SPEED:			/* 短縮 */
		case GROUP:			/* グループキー */
			InputNumberGroupSpeedMarkSet(key);
			break;

		case BROADCAST:		/* 同報キー */
			BroadcastMarkSet();
			break;

		case REDIAL:		/* リダイアル/ポーズキー */
			InputNumberDialMarkSet(PAUSE_MARK);
			break;

#if !defined(JPN) || (PRO_KEYPANEL == PANEL_ANZU_L)
		case FLASH:			/* フラッシュキー */
			InputNumberDialMarkSet(FLASH_MARK);
			break;
#endif

		case FUNCTION:		/* 機能キー */
			/* カーソル移動　ー＞ */
			InputNumberCursorRight();
			break;

		case LEFT_ARROW:
			/* カーソル移動　＜ー */
			InputNumberCursorLeft();
			break;

		case CLEAR:			/* クリアキー */
			/* データクリア実行 */
			InputNumberDataClear();
			break;

		case DIALMARK:		/* ダイアル記号キー */
			InputNumberDialCharacterSet();
			break;

#if (PRO_KEYPANEL == PANEL_POPLAR_L || PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/07/25 */
		case TONE:			/* トーンキー 		*/	/* 追加 97/11/13 T.Fukumoto */
			InputNumberDialMarkSet(TONE_MARK);
			break;
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
		case MERCURY:		/* マーキュリーキー *//*1996/09/18 Eguchi */
			InputNumberDialMarkSet(MERCURY_MARK);
			break;
#endif
#if defined(DEU)	/* for GroundKey '98/03/11 M.HARADA */
		case GROUND:
			if(CHK_UNI_GroundkeyCheck()){
				InputNumberDialMarkSet(PAUSE_MARK);
			}else{
				NackBuzzer();
			}
			break;
#endif

#if (PRO_MULTI_LINE == ENABLE)
 #if (PRO_KEYPANEL == PANEL_POPLAR_B)	/* by K.Watanabe 1998/01/16 */
		case COPY_RESET:	/* コピーリセットキー */
 #else
		case HOLD:			/* 保留キー */
 #endif
			/* 内線番号を示す「！」を保留キーにて入力 */
			InputNumberDialMarkSet(MULTI_TEL_MARK);
			break;
#endif

		case KEY_TIME_UP:	/* キー入力なしで１分間経過 */
		case STOP:			/* ストップキー */
			CursorOff();
			return (NG);

		case ENTER:			/* セットキー */
			/* 登録する番号が正しいかを調べる */
			if (CheckCommandNumber() == OK) { /* 正しい */
				ClearDialNumber2(NULL, Onetouch, Speed, Group);
				SetDialNumber2(NULL, Onetouch, Speed, Group);
				CursorOff();
				return (OK);
			}
			else {	/* 入力値が正しくない */
				NackBuzzer();
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

		/* 現在入力されている直接ダイヤルの件数を取得します */
		buf_count = 0;
		direct_count = 0;
		while (buf_count < InputNumber.WritePosition) {	/* 入力されているデータを全てチェックするまで */
			if (CheckInputNumberCode(InputNumber.Buffer[buf_count]) == FALSE) {	/* 直接ダイヤルの時 */
				direct_count++;
			}
			/* 次のダイヤルデータまで進めます */
			buf_count += GetStringGapPoint(&InputNumber.Buffer[buf_count], ',');
			buf_count++;
		}
		if (direct_count >= 1) {	/* 直接ダイヤルが既に、最大登録数入力されている時 */
			/* データクリア実行 */
			InputNumberDataClear();
			OPR_ChildErrorFlag = INVALID_NUMBER_ERROR;	/* "ﾀﾀﾞｼｲ ﾊﾞﾝｺﾞｳ ｦ ﾄﾞｳｿﾞ" */
			NackBuzzer();
		}
	}
}
#endif	/* (PRO_FCODE_RELAY == ENABLE) */

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
/*************************************************************************
	module		:[サブアドレスＢＯＸ原稿蓄積登録]
	function	:[
		1.原稿を蓄積するＢＯＸ番号を選択します（掲示板ＢＯＸのみ）
		2.原稿を追加で蓄積するか、上書きで蓄積するかを選択します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		注）掲示板ＢＯＸ以外は蓄積できません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
UBYTE	SetStoreFcodeBoxDocument(UBYTE prg_no)
{
	UBYTE	is_loop_end;	/* ループ終了で使用 */

	is_loop_end = FALSE;

	/* サブアドレスＢＯＸ登録作業用変数クリア */
	ClearFcodeControlData();

	/* ボックス番号 */
	if (SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item == MSG_STORE_FCODE_BOX_DOC) {
		OPR_FcodeData.BoxNumber = (UBYTE)SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point;
	}

	/** データ入力 */
	while (is_loop_end != TRUE) {

		/* 原稿を蓄積したいＢＯＸ番号を選択します */
		if (SelectFcodeBoxNumber() == SELECT_FCODE_BOX_STOP) {	/* 選択が中止された時 */
			return (NG);
		}

		/* 選択されたＢＯＸのチェック */
		if (OPR_FcodeData.Status == SUB_ADDRESS_BOX_EMPTY) {
			/* 未登録のＢＯＸが選択された時 */
			NackBuzzer();
		}
		else if (OPR_FcodeData.Status == SUB_ADDRESS_SECURE_BOX) {
			/* 親展ＢＯＸは蓄積できません */
			NackBuzzer();
			OPR_ChildErrorFlag = SETTING_SECURE_BOX_ERROR;	/* "ｼﾝﾃﾝﾎﾞｯｸｽ ﾃﾞｽ       " */
		}
#if (PRO_FCODE_RELAY == ENABLE)	/* Add By H.Fujimura 1999/01/21 */
		else if (OPR_FcodeData.Status == SUB_ADDRESS_RELAY_BOX) {
			/* 中継ＢＯＸは蓄積できません */
			NackBuzzer();
			OPR_ChildErrorFlag = SETTING_RELAY_BOX_ERROR;	/* "ﾁｭｳｹｲﾎﾞｯｸｽ ﾃﾞｽ      " */
		}
#endif
		else {
			/* 蓄積可能なＢＯＸが選択された時 */
			is_loop_end = TRUE;
		}
	}

	/* 原稿追加／上書き設定 */
	if (SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item != MSG_STORE_FCODE_BOX_DOC) {
		SYB_ProgramOnetouch[prg_no].EntryData.StoreData.AddType = 0;	/* 初期値は原稿追加ＯＮです */
	}
	if (SelectData(D2W_SelectFcodeRxDocUpperWrite,	/* "ｹﾞﾝｺｳ ｳﾜｶﾞｷ    :    " */
				   D2W_Off2,						/* "                OFF " */
				   2,
				   &SYB_ProgramOnetouch[prg_no].EntryData.StoreData.AddType,
				   SUB_ADDRESS_OPTION_DOC_ADD,
				   NO_KEYTYPE) == OPR_CANCELED) {		/* 登録中止又は、タイムアップの時 */  /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return (NG);
	}

	SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Item = MSG_STORE_FCODE_BOX_DOC;
	SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point = (UWORD)OPR_FcodeData.BoxNumber;

	return (OK);
}

/*************************************************************************
	module		:[サブアドレスＢＯＸ原稿蓄積実行]
	function	:[
		3.原稿を蓄積します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		注）掲示板ＢＯＸ以外は蓄積できません
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/21]
	author		:[藤村春夫]
*************************************************************************/
void	EnterStoreFcodeBoxDocument(UBYTE prg_no)
{
	UBYTE	file_number;	/* 空きファイル番号 */

	/* ボックス番号 */
	OPR_FcodeData.BoxNumber = (UBYTE)SYB_ProgramOnetouch[prg_no].EntryData.StoreData.Point;

	/* サブアドレスＢＯＸデータを、作業用変数にコピーします */
	GetSubAddressBoxData();

	/* ＢＯＸ選択後の上段表示 */
	DisplayFcodeBoxNumberAndTitle(D2W_StoreFcodeDocMode);	/* "   ｹﾞﾝｺｳ ﾁｸｾｷ       " */

	/* 選択したＢＯＸの暗証番号を入力します */
	if (CheckFcodePassCode() == SET_FCODE_STOP) {	/* 間違った暗証番号が入力されたか、入力が中止された時 */
		return;
	}

	if (SYB_ProgramOnetouch[prg_no].EntryData.StoreData.AddType != SUB_ADDRESS_OPTION_DOC_ADD) {	/* 原稿追加が選択された時 */
		/* 空いている最初のファイル番号を探します */
		file_number = SubaddressBoxDetectEmptyNo(SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].StoredDocBit);
		if (file_number == FULL_STORED) {	/* 空いているファイルがなかった時 */
			NackBuzzer();
			OPR_ChildErrorFlag = NOT_STORED_DOCUMENT_ERROR;	/* "ﾁｸｾｷ ﾃﾞｷﾏｾﾝ         " */
			return;
		}
	}
	else {				/* 原稿上書きが選択された時 */
		file_number = 0;	/* 上書き蓄積の時は先にメインで原稿を消去してから蓄積するため０としておく 1997/04/30  By T.Yamaguchi */
/*		file_number = 1;	/@ ファイル番号は、１固定です */
	}

	/* 蓄積する直前にもう一度ＦコードＢＯＸに蓄積できる状態か調べます 1997/05/14  By T.Yamaguchi */
	if ((SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_NO_SET)
	 && (SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_STORED)
	 && (SYB_SubAddressBoxTable[OPR_FcodeData.BoxNumber].DataStatus != SYS_SUB_ADDRESS_BOX_RECEIVE)) {
		/* 受信中・送信中・蓄積中・消去中・プリント中の時は蓄積できません 1997/05/06  By T.Yamaguchi */
		NackBuzzer();
/*		OPR_ChildErrorFlag = NOT_STORED_DOCUMENT_ERROR;	*//* "ﾁｸｾｷ ﾃﾞｷﾏｾﾝ         " */
		OPR_ChildErrorFlag = BOX_IN_USE_ERROR;			  /* "ﾎﾞｯｸｽ ｼﾖｳﾁｭｳ        " */ /* Modified by S.Fukui Oct.13,1997 */
		return;
	}

	/* 蓄積できる状態かを調べます */
	switch (CheckScanStartEnable(OPR_DOC_SET_CHK_INP_SET)) {
	case OPR_SCAN_ENABLE:	/* 原稿読み取り可能な時 */
#if (0)	/* Add By O.Kimoto 1999/07/19 */
** 		if (CheckMemoryOver() == FALSE) [
#else
		if ((CheckMemoryOver() == FALSE) && (CheckScanDisableCondition() == FALSE)) {
#endif

			/* シングルキーにプログラムワンタッチの値をセット */
			SetProgramToSingleKey(prg_no);
			/* メインに蓄積開始のメッセージを送ります */
			OperationMessageToMain.Message = MSG_STORE_FCODE_BOX_DOC;
			OperationMessageToMain.SubMessage1 = file_number;
			OperationMessageToMain.SubMessage2 = (UWORD)(OPR_FcodeData.BoxNumber + OPR_FCODE_BOX_MIN);
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
		}
		else {
			NackBuzzer();
		}
		break;
	case OPR_SCAN_DISABLE:	/* 原稿読み取り不可能な時 */
		NackBuzzer();
		break;
	case OPR_SCAN_STOP:		/* ブック原稿サイズ入力中に停止又は、タイムアップした時 */
		/* ナックは鳴らしません */
		break;
	default:
		break;
	}
}
#endif	/* (PRO_EXT_P_ONETOUCH == ENABLE) */

#endif	/* (PRO_F_CODE == ENABLE) */
