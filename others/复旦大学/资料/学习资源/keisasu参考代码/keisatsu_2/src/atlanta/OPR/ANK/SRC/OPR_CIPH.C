/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_CIPH.C
*	Author		: 渡辺一章
*	Date		: 1997/07/14
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 暗号化機能オペレーション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\ncu_stat.h"	/* by K.Watanabe 1998/05/11 */
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\atlanta\define\sysdoc.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ncu_data.h"		/* by K.Watanabe 1998/05/11 */
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\scn_data.h"		/* By T.Fukumoto 98/06/26 */
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\ext_v\cph_data.h"
#else
	#include	"\src\atlanta\scd\ext_v\cph_data.h"
#endif

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

/*
void	SetCipherKeyBook(void);
void	PrintCipherKeyBookList(void);
void	PrintSettingCipherKeyBook(void);
void	EraseCipherKeyBook(void);
void	EraseCipherRxDocument(void);
void	SetCipherDefaultKey(void);
void	SetServiceLabelPosition(void);
void	SetCipherPassCode(void);
void	PrintDecipherDocument(void);
UBYTE	CheckCipherPassCode(void);
UBYTE	SelectCipherKeyBookNumber(void);
UBYTE	CheckCipherKeyBookPassCode(void);
UBYTE	SetCipherKeyBookName(void);
UBYTE	SetCipherKey(void);
UBYTE	SetCipherKeyClue(void);
UBYTE	SetCipherKeyBookPassCode(void);
void	SetCipherKeyBookComplete(void);
void	ClearOPR_CipherData(void);
void	DisplaySetCipherKeyBook(UBYTE);
void	DisplaySelectCipherKeyBook(void);
void	KeyBookNumberForwordOperation(void);
void	KeyBookNumberBackOperation(void);
void	GetKeyBookData(void);
UBYTE	CheckSetKeyBookData(void);
void	DisplayKeyBookNumberAndTitle(UBYTE *);
UBYTE	InputRxCipherDocNumber(UBYTE *);
void	SetDecipherData(void);
UBYTE	SelectCipherKeySet(UBYTE);
UBYTE	SetDecipherParameter(void);
UBYTE	CheckCipherExecEnable(UBYTE);
UBYTE	CheckCipherEnableMode(void);
UBYTE	ChangeCentiToInch(UBYTE);
UBYTE	ChangeInchToCenti(UBYTE);
UBYTE	CheckCipherExecuting(void);
*/


#if defined(HINOKI) || defined(HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2)		/* Ｆｏｒ ＨＩＮＯＫＩ By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/13 T.Takagi */
extern UBYTE	IsBookDocSizeSet;			/* ブック原稿サイズの設定状態確認				*/
#endif

#if (PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[キーブック登録]
	function	:[
		1.登録するキーブック番号を選択します
		2.選択したキーブックの暗証番号を確認します
		3.キーブック名を登録します
		4.暗号化キーを登録します
		5.暗号化キーのヒントを登録します
		6.キーブック用の暗証番号を登録します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void SetCipherKeyBook(void)
{
	UBYTE	stage;	/* セット段階 */

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();
	OPR_CipherData.SelectKeyBookType = OPR_KEYBOOK_SET;	/* キーブック選択時の処理内容にキーブック登録をセット */

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_EnterCipherKeyBookMode[3]);	/* "   ｷｰﾊﾞﾝｸ ｾｯﾄ       " */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	stage = SELECT_CIPHER_KEY_BOOK_NO;	/* キーブック番号選択 */

	/* キーブック登録中止するまで処理を続けます */
	while ((stage != SELECT_CIPHER_KEY_BOOK_STOP) && (stage != SET_CIPHER_KEY_BOOK_STOP)) {

		/* 上段の表示 */
		DisplaySetCipherKeyBook(stage);

		stage = (SetCipherKeyBookFunction[stage])();

		/* キーブック登録完了又は、キーブック登録中止（一度登録してあるキーブックに対して）の時、
		** 作業用変数をキーブックの変数にコピーします
		** 注）キーブック番号選択中の中止は除きます
		*/
		if ((stage == SET_CIPHER_KEY_BOOK_COMPLETE)
		 || ((stage == SET_CIPHER_KEY_BOOK_STOP)
		  && (SYB_KeyBookData.SYB_KeyData[OPR_CipherData.KeyBookNumber].Key[0] != NULL))) {
			/* キーブック登録処理 */
			SetCipherKeyBookComplete();

			if (stage == SET_CIPHER_KEY_BOOK_COMPLETE) {	/* キーブック登録完了時 */
				/* 次のキーブック番号に進めます */
				KeyBookNumberForwordOperation();
				stage = SELECT_CIPHER_KEY_BOOK_NO;	/* キーブック番号選択に移行 */
			}
		}
	}
}

/*************************************************************************
	module		:[キーブックリスト　プリント]
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
	date		:[1997/07/18]
	author		:[渡辺一章]
*************************************************************************/
void PrintCipherKeyBookList(void)
{
	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_PrintCipherKeyBookListMode[3]);	/* "   ｷｰﾊﾞﾝｸ ﾘｽﾄ       " */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	/* キーブックにデータが登録されているかをチェックします */
	if (CheckSetKeyBookData() == TRUE) {	/* キーブックにキーが登録されている時 */
		FinalListPrintOperation(LST_SCRAMBLE_KEY_LIST);	/* メインにリスト起動メッセージを送信 */
	}
	else {									/* キーブックにキーが未登録の時 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
	}
}

/*************************************************************************
	module		:[キーブック登録内容プリント]
	function	:[
		1.選択されたキーブックの暗号化キー・暗号化キーのヒントをプリントします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void PrintSettingCipherKeyBook(void)
{
	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_PrintCipherKeyMode[3]);	/* "   ｷｰﾜｰﾄﾞ ﾌﾟﾘﾝﾄ     " */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	/* プリントしたいキーブック番号を選択します */
	if (SelectCipherKeyBookNumber() == SELECT_CIPHER_KEY_BOOK_STOP) {	/* 選択が中止された時 */
		return;
	}

	/* キーブック選択後の上段表示 */
	DisplayKeyBookNumberAndTitle(&D2W_PrintCipherKeyMode[1]);	/* "   ｷｰﾜｰﾄﾞ ﾌﾟﾘﾝﾄ     " */

	/* 選択したキーブックの暗証番号を入力します */
	if (CheckCipherKeyBookPassCode() == SET_CIPHER_KEY_BOOK_STOP) {
		/* 間違った暗証番号が入力されたか、入力が中止された時 */
		return;
	}

	/* メインにリスト起動メッセージを送信 */
	SYS_CipherKeyNo = OPR_CipherData.KeyBookNumber;	/* リストで、キーブック番号参照用にセット */
	FinalListPrintOperation(LST_SCRAMBLE_KEY);
}

/*************************************************************************
	module		:[キーブック消去]
	function	:[
		1.選択したキーブックを消去します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void EraseCipherKeyBook(void)
{
	UBYTE	i;				/* ループ変数 */
	UBYTE	is_loop_end;	/* ループ終了で使用 */

	is_loop_end = FALSE;

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_EraseCipherKeyBookMode[3]);	/* "   ｷｰﾜｰﾄﾞ ｸﾘｱ       " */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	/** データ入力 */
	while (is_loop_end != TRUE) {

		/* 消去したいキーブック番号を選択します */
		if (SelectCipherKeyBookNumber() == SELECT_CIPHER_KEY_BOOK_STOP) {	/* 選択が中止された時 */
			is_loop_end = TRUE;
			continue;
		}

		/* デフォルトキーの登録内容チェック */
		if (OPR_CipherData.KeyBookNumber == SYB_KeyBookData.DefaultKeyNo) {
			/* 選択されたキーが、デフォルトキーとして設定されていた場合は、消去できません */
			NackBuzzer();
			OPR_ChildErrorFlag = USE_DEFAULT_CIPHER_KEY_ERROR;	/* "ﾃﾞﾌｫﾙﾄ ﾃﾞ ｼﾖｳ ｻﾚﾃｲﾏｽ" */
			is_loop_end = TRUE;
			continue;
		}

		/* プログラムワンタッチの登録内容チェック */
		for (i = 0; i < SYS_PROGRAM_MAX; i++) {
			if (CheckProgramStoreStatus(i) == OPR_PRG_CIPHER_TX) {	/* 暗号化送信が登録されている時 */
				if ((SYB_CipherPData[i].SetKeyMode == SYS_CIPHER_KEY_BOOK)
				 && (SYB_CipherPData[i].KeyNumber == OPR_CipherData.KeyBookNumber)) {
					/* 選択されたキーが、プログラムワンタッチで登録されていた場合は、消去できません */
					NackBuzzer();
					OPR_ChildErrorFlag = USE_PROGRAM_ONETOUCH_ERROR;	/* "ﾌﾟﾛｸﾞﾗﾑ ﾃﾞ ｼﾖｳｻﾚﾃｲﾏｽ" */
					is_loop_end = TRUE;
					break;
				}
			}
		}
		if (is_loop_end) {
			continue;
		}

		/* キーブック選択後の上段表示 */
		DisplayKeyBookNumberAndTitle(&D2W_EraseCipherKeyBookMode[1]);	/* "   ｷｰﾜｰﾄﾞ ｸﾘｱ       " */

		/* 選択したキーブックの暗証番号を入力します */
		if (CheckCipherKeyBookPassCode() == SET_CIPHER_KEY_BOOK_STOP) {
			/* 間違った暗証番号が入力されたか、入力が中止された時 */
			is_loop_end = TRUE;
			continue;
		}

		/* 消去前にもう一度、確認を行います */
		switch (ConfirmKeyInputOperation(FunctionDisplayBufferHigh, D2W_CheckProgramEnter, ENTER, FUNCTION)) {
		case CONFIRM_EXEC:	/* セットキーが押された時 */
			/* 指定されたキーブックを消去します */
			CMN_ClearCipherKey((UWORD)OPR_CipherData.KeyBookNumber);

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_EraseCipherKeyBookMode[3]);	/* "   ｷｰﾜｰﾄﾞ ｸﾘｱ       " */
			if (ClearCompleteDisplayOperation(FunctionDisplayBufferHigh) == OPR_CONTINUE) {
				/* ストップキー以外のキーが押されたか、チャイルド表示終了の時 */
				KeyBookNumberForwordOperation();
			}
			else {
				/* ストップキーが押された時 */
				is_loop_end = TRUE;
			}
			break;
		case CONFIRM_ABORT:	/* 機能キーが押された時 */
			break;
		case OPR_END:		/* ストップキーが押されたか１分間入力無しの時 */
		default:
			is_loop_end = TRUE;
			break;
		}
	}
}

/*************************************************************************
	module		:[受信暗号化原稿の消去]
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
	date		:[1997/07/18]
	author		:[渡辺一章]
*************************************************************************/
void EraseCipherRxDocument(void)
{
	UBYTE	rx_number;	/* 受信番号*/

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_EraseCipherRxDocMode[3]);	/* "   ｽｸﾗﾝﾌﾞﾙｹﾞﾝｺｳ ｸﾘｱ " */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	/* 消去する暗号化受信原稿の受信番号を指定します */
	if (InputRxCipherDocNumber(&rx_number) == FALSE) {
		return;
	}

	/* 消去前にもう一度、確認を行います */
	if (ConfirmKeyInputOperation(OPR_CipherData.TitleWording,	/* "ｽｸﾗﾝﾌﾞﾙｹﾞﾝｺｳ ｸﾘｱ    " */
								 D2W_CheckProgramEnter,			/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {

		/* 消去しようとした原稿がスクランブル解除中の時は、消去できません
		** 注）デスクランブルが完了してからでないと、プリントを開始しない仕様なので、プリント中に消去されても
		** 　　問題はありません（デスクランブル後は、データが別になるため）
		*/
		if ((SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC) && ((UWORD)rx_number == CipherReadIndex.No)) {
			NackBuzzer();
			OPR_ChildErrorFlag = DECIPHERING_ERROR;		/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳﾃﾞｽ" */
			return;
		}

		/* 受信中の原稿を消去してしまうと、スクランブル受信通知プリント中にリセットがかかってしまうので、
		** チェックして弾くようにします by K.Watanabe 1998/06/16
		*/
		if (SYB_CipherBox[rx_number].Status == SYS_CIPHERBOX_RECEIVING) {
			NackBuzzer();
			OPR_ChildErrorFlag = LINE_BUSY_ERROR;		/* "ﾂｳｼﾝﾁｭｳ ﾃﾞｽ         " */
			return;
		}

		/* スクランブル受信通知プリント前の原稿を消去すると、スクランブル受信通知プリント中にリセットが
		** かかってしまうので、チェックして弾くようにします by K.Watanabe 1998/06/16
		*/
		if (SYB_CipherBox[rx_number].MessageStatus == SYS_CIPHERBOX_RCV_MSG) {
			NackBuzzer();
			OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;	/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
			return;
		}

		/* 指定された受信番号の原稿を消去します */
		SYB_CipherBox[rx_number].Status = SYS_CIPHERBOX_NO;									/* ステータスの消去 */
		MEM_ClearDoc(SYS_MEM_CIPHER_RX_FILE,rx_number,0);
				/*ボックスno. は、常時０をセット By Y.Suzuki 1998/04/20 */
				/*	 (UBYTE)(OPR_CipherData.KeyBookNumber + OPR_CIPHER_KEY_BOOK_MIN));	/* 原稿の消去 */

		/* 完了表示 */
		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[デフォルトキーの登録]
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
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
void SetCipherDefaultKey(void)
{
	UBYTE	i;				/* ループ変数 */
	UBYTE	default_key;	/* デフォルトキー登録用ワーク変数 */

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_EnterDefaultCipherKeyMode[3]);	/* "   ﾃﾞﾌｫﾙﾄ ｷｰﾜｰﾄﾞ ｾｯﾄ" */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	/* デフォルトキー番号の登録 97/12/17 T.Fukumoto */
	default_key = FixedLengthNumberInput2(SYB_KeyBookData.DefaultKeyNo,
										  1,								/* 入力可能最大桁         */
										  0,								/* 入力可能最小値         */
										  9,								/* 入力可能最大値         */
										  18,								/* ＬＣＤ上表示開始位置   */
										  D2W_InputCipherDefaultKeyNo);		/* "ｷｰﾜｰﾄﾞﾊﾞﾝｺﾞｳ(0-9):  " */

	if (default_key != OPR_NUMBER_INPUT_STOP) {	/* デフォルトキーが設定された時 */
		if (default_key != OPR_NUMBER_NO_STORED) {	/* キーブックの任意のキーが、指定された時 */
			/* デフォルトとして指定されたキーが、実際に登録されていない時はエラーです */
			if (SYB_KeyBookData.SYB_KeyData[default_key].Key[0] != NULL) {	/* 登録済みのキーが指定された時 */
				SYB_KeyBookData.DefaultKeyNo = default_key;
				ChildDisplayStringLow(D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
			}
			else {															/* 未登録のキーが指定された時 */
				NackBuzzer();
				OPR_ChildErrorFlag = NOT_ENTRY_ERROR;		/* "ﾄｳﾛｸ ｻﾚﾃｲﾏｾﾝ        " */
			}
		}
		else {										/* デフォルトキーがクリアされた時 */
			/* プログラムワンタッチの登録内容チェック */
			for (i = 0; i < SYS_PROGRAM_MAX; i++) {
				if (CheckProgramStoreStatus(i) == OPR_PRG_CIPHER_TX) {	/* 暗号化送信が登録されている時 */
					if (SYB_CipherPData[i].SetKeyMode == SYS_CIPHER_KEY_DEFAULT) {
						/* プログラムワンタッチで登録されている場合は、クリアできません */
						NackBuzzer();
						OPR_ChildErrorFlag = USE_PROGRAM_ONETOUCH_ERROR;	/* "ﾌﾟﾛｸﾞﾗﾑ ﾃﾞ ｼﾖｳｻﾚﾃｲﾏｽ" */
						break;
					}
				}
			}

			if (i >= SYS_PROGRAM_MAX) {	/* プログラムワンタッチで使用されていなかった時 */
				SYB_KeyBookData.DefaultKeyNo = 0xFF;
				ChildDisplayStringLow(D2W_SetComplete);			/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
			}
		}
	}
}

/*************************************************************************
	module		:[サービスラベル位置の設定]
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
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
void SetServiceLabelPosition(void)
{
	UWORD	label_position;
#if defined(USA)
	UBYTE	centi_data;
	UBYTE	inch_data;
#endif

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_EnterCipherServiceLabelMode[3]);	/* "   ﾋﾝﾄ ﾋｮｳｼﾞｲﾁ      " */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

#if defined(USA)	/* USA仕様はインチで入力する 97/12/15 T.Fukumoto */
	/* センチからインチ×１０に変換 */
	inch_data = ChangeCentiToInch(SYB_KeyBookData.OffsetServiceLabel);
	label_position = DecimalPointInput((UWORD)inch_data,
									   10,								/* 最小値×１０ */
									   145,								/* 最大値×１０ */
									   16,
									   D2W_InputServiceLabelPosition,	/* "Offset (1-14.5"):   " */
									   TRUE);
	if (label_position != 0xffff) {
		/* インチ×１０からセンチに変換 */
		centi_data = ChangeInchToCenti((UBYTE)label_position);
		SYB_KeyBookData.OffsetServiceLabel = centi_data;
		ChildDisplayStringLow(D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
	}
#else
	label_position = FixedLengthNumberInput(SYB_KeyBookData.OffsetServiceLabel,
											2,
											36,
											17,
											D2W_InputServiceLabelPosition);	/* "ｵﾌｾｯﾄ   (2-36cm):   " */
	if (label_position != 0xffff) {
		SYB_KeyBookData.OffsetServiceLabel = (UBYTE)label_position;
		ChildDisplayStringLow(D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
	}
#endif
}

/*************************************************************************
	module		:[暗号化原稿復号化プリント]
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
	date		:[1997/07/18]
	author		:[渡辺一章]
*************************************************************************/
void PrintDecipherDocument(void)
{
	UBYTE	rx_number;	/* 受信番号*/

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* タイトルワーディングの作成 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_PrintDecipherDocMode[2]);	/* "  ｽｸﾗﾝﾌﾞﾙｶｲｼﾞｮ ﾌﾟﾘﾝﾄ" */

	/* 暗号化機能用暗証番号のチェックを行います */
	if (CheckCipherPassCode() == FALSE) {
		return;
	}

	/* プリントする暗号化受信原稿の受信番号を指定します */
	if (InputRxCipherDocNumber(&rx_number) == FALSE) {
		return;
	}

	/* 暗号化キー・キーのヒント・拡張キー・エラー修正の設定 */
	if (SetDecipherParameter() == FALSE) {
		return;
	}

	/* プリント部数の入力 */
	DisplayStringHigh(0, OPR_CipherData.TitleWording);
	OPR_CipherData.PrintPageNo = FixedLengthNumberInput(1, 1, 99, 17, D2W_InputPrintPageNumber);
																	/* "ﾌﾞｽｳ      (1-99):   " */
	if (OPR_CipherData.PrintPageNo == 0xffff) {
		return;
	}

	/* 暗号化受信原稿復号化用データのセット */
	SetDecipherData();

	/* プリントできる状態かをチェックします */
	if (CheckPrintOperationEnable() == FALSE) {
		return;
	}

	/* 復号化可能かチェックします */
	if (CheckCipherExecEnable(OPR_DECIPHER_RX_DOC) == FALSE) {
		NackBuzzer();	/* by K.Watanabe 1998/05/11 */
		return;
	}

	/* 暗号化原稿復号化メッセージの送信 */
	OperationMessageToMain.Message = MSG_DECIPHER_START;
	OperationMessageToMain.SubMessage1 = SYS_MEM_CIPHER_RX_FILE;
	OperationMessageToMain.SubMessage2 = rx_number;
	snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
	MainTaskExecWait();
}

/*************************************************************************
	module		:[暗号化機能用暗証番号の登録]
	function	:[
		1.２回目以降の登録で、”００００”以外が登録されている時は、
		　暗証番号のチェックを行います
		2.チェックがＮＧでなければ、暗証番号の登録を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
void SetCipherPassCode(void)
{
	UBYTE	inp_passcode_mode;
	UWORD	cipher_passcode;

	/* 暗号化機能用変数クリア */
	ClearOPR_CipherData();

	/* 上段の表示 */
	CMN_StringCopy(OPR_CipherData.TitleWording, &D2W_EnterCipherPassCodeMode[3]);	/* "   ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ ｾｯﾄ " */
	DisplayStringHigh(0, OPR_CipherData.TitleWording);

	/* 暗証番号が初期登録又は、”００００”が登録されている時は、チェックは行いません */
	if ((SYB_KeyBookData.CipherPassCode != 0xffff) && (SYB_KeyBookData.CipherPassCode != 0)) {
		/* 暗証番号チェック */
		cipher_passcode = EnterPassCode(SYB_KeyBookData.CipherPassCode, CHK_PASS_CODE_ENTER, D2W_OldCipherPassCode);
																						/* "ｹﾞﾝｻﾞｲ ﾉ ﾊﾞﾝｺﾞｳ:****" */
		if (cipher_passcode == 0xFFFF) {	/* 入力中止の時 */
			return;
		}
		if (cipher_passcode != SYB_KeyBookData.CipherPassCode) {	/* 暗証番号が違った時 */
			NackBuzzer();
			OPR_ChildErrorFlag = INVALID_ID_CODE_ERROR;	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    " */
			return;
		}
	}

	/* 暗証番号初期登録の時は、暗証番号が表示出来ない（初期値が0xffffのため）ので、"****"を表示します
	** （登録済みデータの時は、前回登録内容を表示します）
	*/
	if (SYB_KeyBookData.CipherPassCode == 0xffff) {	/* 暗証番号初期登録の時 */
		inp_passcode_mode = CHK_PASS_CODE_ENTER;
	}
	else {											/* 暗証番号変更時 */
		inp_passcode_mode = PASS_CODE_ENTER_ZERO_OK;
	}

	/* 暗証番号登録 */
	cipher_passcode = EnterPassCode(SYB_KeyBookData.CipherPassCode, inp_passcode_mode, D2W_NewCipherPassCode);
																					/* "ｱﾀﾗｼｲ ﾊﾞﾝｺﾞｳ   :9999" */
	if (cipher_passcode != 0xFFFF) {	/* 登録された時 */
		SYB_KeyBookData.CipherPassCode = cipher_passcode;
		ChildDisplayStringLow(D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
	}
}

/*************************************************************************
	module		:[暗号化機能用暗証番号のチェック]
	function	:[
		1.
	]
	return		:[
		TRUE	:チェックＯＫ
		FALSE	:チェックＮＧ
	]
	common		:[]
	condition	:[
		この関数を呼ぶ前に、必ず上段表示内容を OPR_CipherData.TitleWordingに
		セットしておくこと
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCipherPassCode(void)
{
	UWORD	cipher_passcode;
	UBYTE	ret;

	ret = FALSE;

	/* 上段の表示 */
	DisplayStringHigh(0, OPR_CipherData.TitleWording);

	/* 暗証番号が”００００”の時は、チェックは行いません */
	if (SYB_KeyBookData.CipherPassCode == 0) {
		ret = TRUE;
	}
	else {
		/* 暗証番号チェック */
		cipher_passcode = EnterPassCode(SYB_KeyBookData.CipherPassCode, CHK_PASS_CODE_ENTER, D2W_CipherPassCode);
																					/* "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :****" */
		if (cipher_passcode != 0xFFFF) {	/* 入力された時 */
			if (cipher_passcode == SYB_KeyBookData.CipherPassCode) {	/* 暗証番号が一致した時 */
				ret = TRUE;
			}
			else {														/* 暗証番号が違った時 */
				NackBuzzer();
				OPR_ChildErrorFlag = INVALID_ID_CODE_ERROR;	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    " */
			}
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[キーブック番号選択]
	function	:[
		1.キーブック番号を選択します
	]
	return		:[
		TRUE	:キーが選択された
		FALSE	:選択が中止された
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SelectCipherKeyBookNumber(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	key_number;		/* キーブック番号 */
	UBYTE	is_loop_end;
	UBYTE	stage;

	stage = SELECT_CIPHER_KEY_BOOK_STOP;	/* キーブック番号選択中止 */
	is_loop_end = FALSE;

	/* 上段の表示 */
	DisplayStringHigh(0, D2W_CipherSelectNumber);	/* "ﾊﾞﾝｺﾞｳ ｦ ｴﾗﾝﾃﾞｸﾀﾞｻｲ  " */

	while (is_loop_end != TRUE) {

		/* 下段の表示 */
		DisplaySelectCipherKeyBook();

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case KEY_TIME_UP:
		case STOP:
			is_loop_end = TRUE;
			break;
		case ENTER:
			if (OPR_CipherData.KeyBookNumberInpPos > 0) {	/* キーブック番号入力途中の時 */
				NackBuzzer();
			}
			else {
				if ((OPR_CipherData.SelectKeyBookType == OPR_EXCEPT_KEYBOOK_SET)
				 && (SYB_KeyBookData.SYB_KeyData[OPR_CipherData.KeyBookNumber].Key[0] == NULL)) {
					/* キーブック登録時以外の時で、選択されたキーが未登録の時は無効です */
					NackBuzzer();
				}
				else {
					/* 選択された番号のキーブックデータを、作業用変数にコピーします */
					GetKeyBookData();
					stage = CHECK_CIPHER_KEY_PASSCODE;	/* 暗証番号チェックに移行 */
					is_loop_end = TRUE;
				}
			}
			break;
		case FUNCTION:
			if (OPR_CipherData.KeyBookNumberInpPos > 0) {	/* キーブック番号入力途中の時 */
				NackBuzzer();
			}
			else {
				/* 次のキーブック番号に進めます */
				KeyBookNumberForwordOperation();
			}
			break;
		case LEFT_ARROW:
			if (OPR_CipherData.KeyBookNumberInpPos > 0) {	/* キーブック番号入力途中の時 */
				NackBuzzer();
			}
			else {
				/* 前のキーブック番号に戻します */
				KeyBookNumberBackOperation();
			}
			break;
		case CLEAR:
			if (OPR_CipherData.KeyBookNumberInpPos > 0) {	/* キーブック番号入力途中の時 */
				/* キーブック番号入力バッファのデータを１文字クリア */
				OPR_CipherData.KeyBookNumberInpPos--;
				OPR_CipherData.KeyBookNumberInpBuf[OPR_CipherData.KeyBookNumberInpPos] = NULL;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:
			OPR_CipherData.KeyBookNumberInpBuf[OPR_CipherData.KeyBookNumberInpPos++] = key;
			if (OPR_CipherData.KeyBookNumberInpPos >= OPR_KEY_BOOK_FIGURE_MAX) {
				/* 入力値を数値に変換します */
				key_number = (UBYTE)CMN_ASC_ToUnsignedInt(OPR_CipherData.KeyBookNumberInpBuf,
														  OPR_CipherData.KeyBookNumberInpPos);

				/* 入力値が適正値かどうかを調べます
				** （最大値の判断を、０・１どちらから始まっていても対応できるようにしておきます
				** 　SYS_KEY_BOOK_MAX -> SYS_KEY_BOOK_MAX - 1 + OPR_CIPHER_KEY_BOOK_MIN）
				*/
				if ((key_number >= OPR_CIPHER_KEY_BOOK_MIN)
				 && (key_number <= SYS_KEY_BOOK_MAX - 1 + OPR_CIPHER_KEY_BOOK_MIN)) {
					OPR_CipherData.KeyBookNumber = (UBYTE)(key_number - OPR_CIPHER_KEY_BOOK_MIN);
				}
				else {
					NackBuzzer();
				}
				CMN_MemorySet(OPR_CipherData.KeyBookNumberInpBuf, OPR_KEY_BOOK_FIGURE_MAX + 1, NULL);
				OPR_CipherData.KeyBookNumberInpPos = 0;
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
	module		:[キーブック暗証番号検査]
	function	:[
		1.指定のキーブックの暗証番号を入力し、登録されている暗証番号と
		　一致するかを調べます
	]
	return		:[
		ENTER_CIPHER_KEY_BOOK_NAME	:1.ＢＯＸ初期登録の時
									 2.暗証番号が一致した時
		SET_CIPHER_KEY_BOOK_STOP	:1.入力が中止された時
									 2.間違った暗証番号が入力された時
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
************************************************************************/
UBYTE CheckCipherKeyBookPassCode(void)
{
	UWORD	key_passcode;
	UBYTE	stage;

	stage = SET_CIPHER_KEY_BOOK_STOP;	/* キーブック登録中止 */

	/* 暗証番号が登録されていない時は、チェックは行いません（初期登録・登録済みに関わらず） */
	if (OPR_CipherData.KeyPassCode == 0) {
		stage = ENTER_CIPHER_KEY_BOOK_NAME;	/* キーブック名登録に移行 */
	}
	else {
		key_passcode = EnterPassCode(OPR_CipherData.KeyPassCode, CHK_PASS_CODE_ENTER, D2W_CipherPassCode);
																			/* "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :****" */

		if (key_passcode != 0xFFFF) {	/* 入力された時 */
			if (key_passcode == OPR_CipherData.KeyPassCode) {	/* 暗証番号が一致した時 */
				stage = ENTER_CIPHER_KEY_BOOK_NAME;	/* キーブック名登録に移行 */
			}
			else {												/* 暗証番号が違う時 */
				NackBuzzer();
				OPR_ChildErrorFlag = INVALID_ID_CODE_ERROR;	/* "ﾊﾞﾝｺﾞｳ ｶﾞ ﾁｶﾞｲﾏｽ    " */
			}
		}
	}

	return(stage);
}

/*************************************************************************
	module		:[キーブック名登録]
	function	:[
		1.指定のキーブックの名前を登録します
	]
	return		:[
		ENTER_CIPHER_KEY			:キーブック名登録完了
		SET_CIPHER_KEY_BOOK_STOP	:キーブック名登録中止
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetCipherKeyBookName(void)
{
	UBYTE	stage;

	stage = SET_CIPHER_KEY_BOOK_STOP;	/* キーブック登録中止 */

	/* 名前入力初期処理 */
	ClearCharacterInput();
	SetCharacterInputMode();	/* 文字入力モード初期化 */
	CMN_StringCopy(CharacterInput.Buffer, OPR_CipherData.KeyName);
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_BOX_NAME_MAX - 1;

	/* キーブック名登録 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
#else
	if (NameInput(OPR_KANJI_DISABLE) == OK) {	/* 登録完了 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		/* キーブック名は登録されていなくても構わない */
		StoreCharacterInputValue(OPR_CipherData.KeyName, ASC_DATA_TYPE);
		stage = ENTER_CIPHER_KEY;	/* 暗号化キーの登録に移行 */
	}
	return(stage);
}

/*************************************************************************
	module		:[暗号化キー入力]
	function	:[
		1.
	]
	return		:[
		ENTER_CIPHER_KEY_CLUE		:暗号化キー登録完了
		SET_CIPHER_KEY_BOOK_STOP	:暗号化キー登録中止
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
UBYTE SetCipherKey(void)
{
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	stage;

	stage = SET_CIPHER_KEY_BOOK_STOP;	/* キーブック登録中止 */

	/* 名前入力用バッファ初期化 */
	ClearCharacterInput();
	SetCharacterInputMode();					/* 文字入力モード初期化 */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
	OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, OPR_CipherData.Key, 0);	/* 前回登録データをセット */
 #else
	SetCharacterInputBuf(OPR_CipherData.Key);	/* 前回入力値を名前入力用バッファに展開する */
 #endif
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_KEY_MAX - 1;

	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {
		/* 暗号化キー入力 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
		if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
#else 
		if (NameInput(OPR_KANJI_ENABLE) == OK) {	/* 登録完了の時 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
			if (CharacterInput.Buffer[0] != NULL) {	/* 暗号化キーが入力された時 */
				if (GetWriteDataCount() >= 4) {	/* ４桁以上入力されている時 */
#if (PRO_JIS_CODE == ENABLE)
					StoreCharacterInputValue(OPR_CipherData.Key, ASC_JIS_DATA_TYPE);
#else
					StoreCharacterInputValue(OPR_CipherData.Key, ASC_DATA_TYPE);
#endif
					stage = ENTER_CIPHER_KEY_CLUE;	/* 暗号化キーのヒントの登録に移行 */
					is_loop_end = TRUE;
				}
				else {							/* ３桁以下の入力の場合は、再入力します */
					NackBuzzer();
					OPR_ChildErrorFlag = SHORT_FIGURE_ERROR;	/* "4ｹﾀ ｲｼﾞｮｳ ﾋﾂﾖｳ      " Added by S.Fukui Dec.15,1997 */
				}
			}
			else {									/* 暗号化キーが未入力の時 */
				/* 暗号化キーは必ず登録される必要があります */
				NackBuzzer();
				ChildDisplayStringLow(D2W_NoNumberStored);	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
			}
		}
		else {				/* 登録中止の時 */
			is_loop_end = TRUE;
		}
	}

	return(stage);
}

/*************************************************************************
	module		:[暗号化キーのヒント入力]
	function	:[
		1.
	]
	return		:[
		ENTER_CIPHER_KEY_PASSCODE	:暗号化キーのヒント登録完了
		SET_CIPHER_KEY_BOOK_STOP	:暗号化キーのヒント登録中止
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
UBYTE SetCipherKeyClue(void)
{
	UBYTE	stage;

	stage = SET_CIPHER_KEY_BOOK_STOP;	/* キーブック登録中止 */

	/* 名前入力用バッファ初期化 */
	ClearCharacterInput();
	SetCharacterInputMode();						/* 文字入力モード初期化 */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/09/27 */
	OPR_SetRegisteredDataToBuf(CharacterInput.Buffer, OPR_CipherData.KeyClue, 0);	/* 前回登録データをセット */
 #else
	SetCharacterInputBuf(OPR_CipherData.KeyClue);	/* 前回入力値を名前入力用バッファに展開する */
 #endif
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;
	CharacterInput.MaxFigure = SYS_KEY_CLUE_MAX - 1;

	/* 暗号化キーのヒント入力 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (SATSUKI2でＶ６５０と同じです) Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
#else
	if (NameInput(OPR_KANJI_ENABLE) == OK) {	/* 登録完了の時 */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		/* 暗号化キーのヒントは未登録でも可能です */
#if (PRO_JIS_CODE == ENABLE)
		StoreCharacterInputValue(OPR_CipherData.KeyClue, ASC_JIS_DATA_TYPE);
#else
		StoreCharacterInputValue(OPR_CipherData.KeyClue, ASC_DATA_TYPE);
#endif
		stage = ENTER_CIPHER_KEY_PASSCODE;	/* 暗証番号登録に移行 */
	}

	return(stage);
}

/*************************************************************************
	module		:[暗号化キーブック用暗証番号登録]
	function	:[
		1.指定のキーブックの暗証番号を登録します
	]
	return		:[
		ENTER_CIPHER_KEY			:暗証番号登録完了
		SET_CIPHER_KEY_BOOK_STOP	:暗証番号登録中止
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetCipherKeyBookPassCode(void)
{
	UWORD	key_passcode;
	UBYTE	stage;

	stage = SET_CIPHER_KEY_BOOK_STOP;	/* キーブック登録中止 */

	/* 暗証番号登録 */
	key_passcode = EnterPassCode(OPR_CipherData.KeyPassCode, PASS_CODE_ENTER_ZERO_OK, D2W_CipherPassCode);
																			/* "ｱﾝｼｮｳ ﾊﾞﾝｺﾞｳ   :9999" */
	if (key_passcode != 0xFFFF) {	/* 登録された時 */
		OPR_CipherData.KeyPassCode = key_passcode;
		stage = SET_CIPHER_KEY_BOOK_COMPLETE;	/* キーブック登録完了 */
	}

	return(stage);
}

/*************************************************************************
	module		:[キーブック登録処理]
	function	:[
		1.編集用バッファの内容をキーブック用バッファにコピーします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void SetCipherKeyBookComplete(void)
{
	UBYTE	key_number;		/* キーブック番号 */

	key_number = OPR_CipherData.KeyBookNumber;

	/** 暗号化キー */
	CMN_StringCopyNULL(SYB_KeyBookData.SYB_KeyData[key_number].Key, OPR_CipherData.Key);

	/** 暗号化キーのヒント */
	CMN_StringCopyNULL(SYB_KeyBookData.SYB_KeyData[key_number].KeyClue, OPR_CipherData.KeyClue);

	/** キーブック名 */
	CMN_StringCopyNULL(SYB_KeyBookData.SYB_KeyData[key_number].KeyName, OPR_CipherData.KeyName);

	/** 暗証番号 */
	SYB_KeyBookData.SYB_KeyData[key_number].KeyPassCode = OPR_CipherData.KeyPassCode;
}

/*************************************************************************
	module		:[暗号化機能用変数クリア]
	function	:[
		1.暗号化機能用変数を初期化します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void ClearOPR_CipherData(void)
{
	/* 拡張キー設定 */
	OPR_CipherData.KeyExtensionOn = TRUE;

	/* 暗号化キー */
	OPR_CipherData.Key[0] = NULL;

	/* 暗号化キーのヒント */
	OPR_CipherData.KeyClue[0] = NULL;

	/* キーセット種別 */
	OPR_CipherData.SetKeyMode = SYS_CIPHER_KEY_DEFAULT;

	/* タイトルワーディング */
	CMN_MemorySetNULL(OPR_CipherData.TitleWording, OPR_DISPLAY_MAX, ' ');

	/* ボックス番号 */
	OPR_CipherData.KeyBookNumber = 0;

	/* ボックス番号入力位置 */
	OPR_CipherData.KeyBookNumberInpPos = 0;

	/* ボックス番号入力バッファ */
	CMN_MemorySet(OPR_CipherData.KeyBookNumberInpBuf, OPR_KEY_BOOK_FIGURE_MAX + 1, NULL);

	/* キーブック選択時の処理内容 */
	OPR_CipherData.SelectKeyBookType = OPR_EXCEPT_KEYBOOK_SET;
}

/*************************************************************************
	module		:[キーブック登録中　上段表示]
	function	:[
		1.キーブック登録中の上段表示を行います
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void DisplaySetCipherKeyBook(UBYTE stage)
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
	case CHECK_CIPHER_KEY_PASSCODE:		/** 暗証番号チェック */
	case ENTER_CIPHER_KEY_PASSCODE:		/** 暗証番号登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_EnterCipherKeyBookMode[1]);	/* "   ｷｰﾊﾞﾝｸ ｾｯﾄ       " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_CipherData.KeyBookNumber + OPR_CIPHER_KEY_BOOK_MIN,
							 OPR_KEY_BOOK_FIGURE_MAX,
							 '0');
		FunctionDisplayBufferHigh[OPR_KEY_BOOK_FIGURE_MAX] = ':';
		break;
	case ENTER_CIPHER_KEY_BOOK_NAME:	/** キーブック名登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterCipherKeyName);			/* " :ｷｰﾜｰﾄﾞ ﾒｲ         " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_CipherData.KeyBookNumber + OPR_CIPHER_KEY_BOOK_MIN,
							 OPR_KEY_BOOK_FIGURE_MAX,
							 '0');
		break;
	case ENTER_CIPHER_KEY:				/** 暗号化キー登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterCipherKey);				/* " :ｷｰﾜｰﾄﾞ            " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_CipherData.KeyBookNumber + OPR_CIPHER_KEY_BOOK_MIN,
							 OPR_KEY_BOOK_FIGURE_MAX,
							 '0');
		break;
	case ENTER_CIPHER_KEY_CLUE:			/** 暗号化キーのヒント登録 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_EnterCipherKeyClue);			/* " :ｷｰﾜｰﾄﾞﾋﾝﾄ         " */
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
							 OPR_CipherData.KeyBookNumber + OPR_CIPHER_KEY_BOOK_MIN,
							 OPR_KEY_BOOK_FIGURE_MAX,
							 '0');
		break;
	case SELECT_CIPHER_KEY_BOOK_NO:		/** キーブック番号選択 */
	case SET_CIPHER_KEY_BOOK_STOP:		/** キーブック登録中止 */
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
	module		:[キーブック番号選択　下段表示]
	function	:[
		1.キーブック番号が選択されている時、登録内容を表示します
		2.キーブック番号がテンキーにて選択中の時、入力内容を表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void DisplaySelectCipherKeyBook(void)
{
	UBYTE	key_number;		/* キーブック番号 */

	if (CheckChildErrorDisplayReq() == TRUE) {	/* チャイルド表示すべきエラーが発生した */
		DisplayChildError();
		return;
	}

	if (CheckChildDisplay() == TRUE) {	/* チャイルド表示中 */
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	key_number = OPR_CipherData.KeyBookNumber;

	if (OPR_CipherData.KeyBookNumberInpPos == 0) {	/* キーブック番号入力途中でない時 */
		/* 現在選択されているキーブック番号を表示用バッファにセットします */
		CMN_UnsignedIntToASC(FunctionDisplayBufferLow,
							 key_number + OPR_CIPHER_KEY_BOOK_MIN,
							 OPR_KEY_BOOK_FIGURE_MAX,
							 '0');
		FunctionDisplayBufferLow[OPR_KEY_BOOK_FIGURE_MAX] = ':';

		/* キーブックの設定状況を調べます */
		if (SYB_KeyBookData.SYB_KeyData[key_number].Key[0] != NULL) {	/* 登録済みの時 */
			/* キーブック名を表示用バッファにコピーします */
			CMN_StringCopy(&FunctionDisplayBufferLow[OPR_KEY_BOOK_FIGURE_MAX + 1],
						   SYB_KeyBookData.SYB_KeyData[key_number].KeyName);
		}
		else {															/* 未登録の時 */
			CMN_StringCopyNum(&FunctionDisplayBufferLow[OPR_KEY_BOOK_FIGURE_MAX + 1],
							  D2W_NoNumberStored,										/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
							  OPR_DISPLAY_MAX - (OPR_KEY_BOOK_FIGURE_MAX + 1));
		}
	}
	else {
		CMN_StringCopy(FunctionDisplayBufferLow, OPR_CipherData.KeyBookNumberInpBuf);
	}

	/* 下段の表示 */
	DisplayStringLow(0, FunctionDisplayBufferLow);
}

/*************************************************************************
	module		:[キーブック番号前進処理]
	function	:[
		1.キーブック番号を次に進めます
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void KeyBookNumberForwordOperation(void)
{
	/* キーブック番号の最後までいったら先頭に戻します */
	if (OPR_CipherData.KeyBookNumber >= SYS_KEY_BOOK_MAX - 1) {
		OPR_CipherData.KeyBookNumber = 0;
	}
	else {
		/* キーブック番号を進めます */
		OPR_CipherData.KeyBookNumber++;
	}
}

/*************************************************************************
	module		:[キーブック番号後退処理]
	function	:[
		1.キーブック番号を前に戻します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void KeyBookNumberBackOperation(void)
{
	/* キーブック番号が先頭の時は、最後の値にします */
	if (OPR_CipherData.KeyBookNumber == 0) {
		OPR_CipherData.KeyBookNumber = SYS_KEY_BOOK_MAX - 1;
	}
	else {
		/* キーブック番号を戻します */
		OPR_CipherData.KeyBookNumber--;
	}
}

/*************************************************************************
	module		:[キーブック登録内容コピー]
	function	:[
		1.指定のキーブック番号に対する、キー内容を作業用バッファにコピーします
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/17]
	author		:[渡辺一章]
*************************************************************************/
void GetKeyBookData(void)
{
	UBYTE	key_number;		/* キーブック番号 */

	key_number = OPR_CipherData.KeyBookNumber;

	/** 暗号化キー */
	CMN_StringCopyNULL(OPR_CipherData.Key, SYB_KeyBookData.SYB_KeyData[key_number].Key);

	/** 暗号化キーのヒント */
	CMN_StringCopyNULL(OPR_CipherData.KeyClue, SYB_KeyBookData.SYB_KeyData[key_number].KeyClue);

	/** キーブック名 */
	CMN_StringCopyNULL(OPR_CipherData.KeyName, SYB_KeyBookData.SYB_KeyData[key_number].KeyName);

	/** 暗証番号 */
	OPR_CipherData.KeyPassCode = SYB_KeyBookData.SYB_KeyData[key_number].KeyPassCode;
}

/*************************************************************************
	module		:[キーブックデータ登録チェック]
	function	:[
		1.キーブックにキーが登録されているかをチェックします
	]
	return		:[
		TRUE	:キーブック登録済み
		FALSE	:キーブック未登録
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckSetKeyBookData(void)
{
	UBYTE	i;
	UBYTE	ret;

	ret = FALSE;

	/* キーが登録されているキーブックがあるかをチェックします */
	for (i = 0; i < SYS_KEY_BOOK_MAX; i++) {
		if (SYB_KeyBookData.SYB_KeyData[i].Key[0] != NULL) {	/* キーが登録されている時 */
			ret = TRUE;
			break;
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[キーブック選択後の上段表示]
	function	:[
		1.選択されたキーブック番号と、キーブックに対する処理を表示します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
void DisplayKeyBookNumberAndTitle(UBYTE *title_wording)
{
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, title_wording);
	CMN_UnsignedIntToASC(FunctionDisplayBufferHigh,
						 OPR_CipherData.KeyBookNumber + OPR_CIPHER_KEY_BOOK_MIN,
						 OPR_KEY_BOOK_FIGURE_MAX,
						 '0');
	FunctionDisplayBufferHigh[OPR_KEY_BOOK_FIGURE_MAX] = ':';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

/*************************************************************************
	module		:[暗号化受信原稿　受信番号入力]
	function	:[
		1.
	]
	return		:[
		TRUE	:入力された番号の暗号化受信原稿が存在する
		FALSE	:入力された番号の暗号化受信原稿が存在しない・入力中止
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/18]
	author		:[渡辺一章]
*************************************************************************/
UBYTE InputRxCipherDocNumber(UBYTE *rx_number)
{
	/* 上段の表示 */
	DisplayStringHigh(0, OPR_CipherData.TitleWording);

	/* 復号化したい暗号化原稿の受信番号を指定します */
	if (NumberInput(OPR_CIPHER_RX_DOC_NUMBER_INPUT) == NG) {	/* 入力が中止された時 */
		return(FALSE);
	}
	*rx_number = (UBYTE)CharacterInputToNumber();

	if (SYB_CipherBox[*rx_number].Status == SYS_CIPHERBOX_NO) {	/* 指定された受信番号の原稿が存在しない時 */
		NackBuzzer();
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;	/* "ｹﾞﾝｺｳ ｶﾞ ｱﾘﾏｾﾝ      " */
		return(FALSE);
	}

	return(TRUE);
}

/*************************************************************************
	module		:[暗号化原稿復号化用データ　セット]
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
	date		:[1997/07/19]
	author		:[渡辺一章]
*************************************************************************/
void SetDecipherData(void)
{
	UBYTE	key_number;		/* キーブック番号 */

	key_number = OPR_CipherData.KeyBookNumber;

	/* プリント部数 */
	/* 注）暗号化受信原稿の復号化時しか、プリント部数はセットされませんが、
	** 　　暗号化送信予約原稿の復号化時は、特に参照されないので無条件に値をセットします
	** 　　不都合があれば、判断する必要があります
	*/
	CipherData.PrintPageNo = OPR_CipherData.PrintPageNo;

	/* 暗号化キー */
	CMN_StringCopyNULL(CipherData.Key, OPR_CipherData.Key);

	/* 暗号化キーのヒント */
	CMN_StringCopyNULL(CipherData.KeyClue, OPR_CipherData.KeyClue);

	/* 拡張キー */
	CipherData.ExtensionKey = OPR_CipherData.ExtensionKey;

	/* ノイズ除去設定 */
/*	CipherData.NoiseRemovalOn = OPR_CipherData.NoiseRemovalOn;By Y.Suzuki 1997/11/01 */
	SYB_KeyBookData.NoiseRemovalOn = OPR_CipherData.NoiseRemovalOn;

}

/*************************************************************************
	module		:[暗号化キー・キーのヒントの設定]
	function	:[
		1.キーのセット方法を選択します
		　・デフォルトキーが選択された時は、暗号化機能設定で設定されている
		　　デフォルトキーを使用します
		　・キーブックが選択された時は、キーブックの中から登録されているキーを
		　　選択します
		　・直接が選択された時は、キー・キーのヒントを直接入力します
	]
	return		:[
		TRUE	:キー・キーのヒント　セット完了
		FALSE	:キー・キーのヒント　セット中止
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/18]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SelectCipherKeySet(UBYTE call_place)
{
	UBYTE	set_key_mode_last;	/* 前回選択キーセット種別 */

	if (call_place == OPR_COM_OPTION) {	/* 応用通信から呼ばれた時 */
		set_key_mode_last = OPR_CipherData.SetKeyMode;
	}

	/* キーのセット方法を選択します */
	if (SelectData(D2W_SelectCipherKeySetKind,	/* "ｷｰﾜｰﾄﾞ ｾｯﾄ  :       " */
				   D2W_CipherKeySetDefault,		/* "             ﾃﾞﾌｫﾙﾄ " */
				   3,
				   &OPR_CipherData.SetKeyMode,
				   SYS_CIPHER_KEY_DEFAULT | SYS_CIPHER_KEY_BOOK | SYS_CIPHER_KEY_DIRECT,
				   NO_KEYTYPE) == OPR_CANCELED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		return(FALSE);
	}

	/* 選択したセット方法に基づき、キー・キーのヒントをセットします */
	switch (OPR_CipherData.SetKeyMode) {
	case SYS_CIPHER_KEY_DEFAULT:	/* デフォルトキーを使用	*/
		/* デフォルトキーが未登録又は、デフォルトキーのキーが未登録の時は、無効です */
		if ((SYB_KeyBookData.DefaultKeyNo == 0xff)
		 || (SYB_KeyBookData.SYB_KeyData[SYB_KeyBookData.DefaultKeyNo].Key[0] == NULL)) {
			NackBuzzer();
			OPR_ChildErrorFlag = NO_STORED_NUMBER_ERROR;	/* "ｾｯﾄ ｻﾚﾃｲﾏｾﾝ         " */
			return(FALSE);
		}

		/* デフォルトキーのキー・キーのヒントを作業用バッファにコピーする */
		CMN_StringCopyNULL(OPR_CipherData.Key,
						   SYB_KeyBookData.SYB_KeyData[SYB_KeyBookData.DefaultKeyNo].Key);
		CMN_StringCopyNULL(OPR_CipherData.KeyClue,
						   SYB_KeyBookData.SYB_KeyData[SYB_KeyBookData.DefaultKeyNo].KeyClue);
		break;
	case SYS_CIPHER_KEY_BOOK:		/* キーブックから選択	*/
		/* 応用通信の再登録時に、キーブック→直接→キーブック等の選択がされた時、
		** １回目のキーブックで選択されたキーを、再表示しないようにクリアしておきます
		*/
		if ((call_place == OPR_COM_OPTION)					/* 応用通信から呼ばれた時 */
		 && (set_key_mode_last != SYS_CIPHER_KEY_BOOK)) {	/* かつ、前回の登録がキーブック以外の時 */
			OPR_CipherData.KeyBookNumber = 0;
		}

		if (SelectCipherKeyBookNumber() == SELECT_CIPHER_KEY_BOOK_STOP) {	/* 選択が中止された時 */
			return(FALSE);
		}
		break;
	case SYS_CIPHER_KEY_DIRECT:		/* 直接入力				*/
		/* 送信するまでに暗号化送信のメニューに２回以上入った時、前の選択が直接入力でなかった時は、
		** 編集用バッファを初期化します（前回選択された直接入力以外の内容を、そのまま表示してしまうため）
		*/
		if ((call_place == OPR_COM_OPTION)					/* 応用通信から呼ばれた時 */
		 && (set_key_mode_last != SYS_CIPHER_KEY_DIRECT)) {	/* かつ、前回が直接入力以外の時 */
			OPR_CipherData.Key[0] = NULL;
			OPR_CipherData.KeyClue[0] = NULL;
		}

		/* 暗号化キー入力時の上段表示 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_EnterCipherKey[2]);	/* " :ｷｰﾜｰﾄﾞ   \0        " */
		DisplayStringHigh(0, FunctionDisplayBufferHigh);

		/* 暗号化キーの入力 */
		if (SetCipherKey() == SET_CIPHER_KEY_BOOK_STOP) {
			return(FALSE);
		}

		/* 暗号化原稿の復元時は、キーのヒントは必要ありません */
		if (call_place == OPR_COM_OPTION) {	/* 応用通信から呼ばれた時 */
			/* 暗号化キーのヒント入力時の上段表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_EnterCipherKeyClue[2]);	/* " :ｷｰﾜｰﾄﾞﾋﾝﾄ\0        " */
			DisplayStringHigh(0, FunctionDisplayBufferHigh);

			/* 暗号化キーのヒント入力 */
			if (SetCipherKeyClue() == SET_CIPHER_KEY_BOOK_STOP) {
				return(FALSE);
			}
		}
		break;
	default:
		break;
	}

	return(TRUE);
}

/*************************************************************************
	module		:[暗号化原稿復号化用パラメータ設定]
	function	:[
		1.暗号化キー・キーのヒントを設定します
		2.拡張キーを入力します
		3.エラー修正のＯＮ／ＯＦＦを設定します
	]
	return		:[
		TRUE	:セット完了
		FALSE	:セット中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/22]
	author		:[渡辺一章]
*************************************************************************/
UBYTE SetDecipherParameter(void)
{
	/* 暗号化キー・キーのヒントの設定 */
	if (SelectCipherKeySet(OPR_DECIPHER_DOC) == FALSE) {
		return(FALSE);
	}

	/* 拡張キーの入力 */
	DisplayStringHigh(0, OPR_CipherData.TitleWording);
	if (NumberInput(OPR_CIPHER_EXTENSION_KEY_INPUT) == NG) {
		return(FALSE);
	}
	/* 無条件にCharacterInputToNumber()を呼ぶと、データ未入力時でも０が返ってくるので
	** ０を入力した時との区別がつかないので、事前に判断します
	*/
	if (CheckCharacterInputEmpty() == TRUE) {	/* 拡張キーが未入力の時 */
		OPR_CipherData.ExtensionKey = 0xff;
	}
	else {										/* 拡張キーが入力された時 */
		OPR_CipherData.ExtensionKey = (UBYTE)CharacterInputToNumber();
	}

	/* エラー修正の設定 */
	OPR_CipherData.NoiseRemovalOn = FALSE;	/* エラー修正の初期値ＯＦＦをセット */
#if (0)	/* メモリ蓄積された原稿には、エラー修正は無効なので、無くします by K.Watanabe 1998/01/08 */
//		/* 但し、スキャナー読み取り原稿を復号化する様になれば必要なので、コメントにしておきます */
//	if (SelectData(D2W_SelectCipherDocErrRemoval,	/* "ｴﾗｰ ｼｭｳｾｲ      :    " */
//				   D2W_Off2,						/* "                OFF " */
//				   2,
//				   &OPR_CipherData.NoiseRemovalOn,
//				   TRUE,
//				   NO_KEYTYPE) == OPR_CANCELED) { /* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
//		return(FALSE);
//	}
#endif

	return(TRUE);
}

/*************************************************************************
	module		:[暗号化・復号化可能検査]
	function	:[
		1.応用通信で、暗号化送信が指定されている時、暗号化可能か調べます
		2.暗号化受信原稿を復号化する時、復号化可能か調べます
		3.暗号化送信予約原稿を復号化する時、復号化可能か調べます
	]
	return		:[
		TRUE	:暗号化・復号化可能
		FALSE	:暗号化・復号化不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/12]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCipherExecEnable(UBYTE call_place)
{

	/* 送信前の検査時に、応用通信で未設定の場合は、詳細検査は行いません */
	if ((call_place == OPR_CIPHER_TX) && (SpecialCommandValue.CommandOption.Item == SYS_CIPHER_TX)
	 || (call_place != OPR_CIPHER_TX)) {
		/* 拡張ＲＯＭが抜かれた後に、スクランブルが登録されているプログラムワンタッチで送信すると
		** 正しく動作しないのでオペレーションで弾きます by K.Watanabe 1998/04/16
		*/
		if (!ScrambleOn) {
			return(FALSE);
		}

		/* 着信（ＣＩ）検出中は、禁止します by K.Watanabe 1998/05/11 */
		if (NCUStatus & DETECT_CI_STATE) {
			return(FALSE);
		}

		/* 通信中は、禁止します */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
			OPR_ChildErrorFlag = LINE_BUSY_ERROR;	/* "ﾂｳｼﾝﾁｭｳ ﾃﾞｽ         " */
			return(FALSE);
		}

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
		/****************************
		** メール送受信中も禁止？
		****************************/
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_DIALUP_INTERNET_FAX) {
			OPR_ChildErrorFlag = LINE_BUSY_ERROR;	/* "ﾂｳｼﾝﾁｭｳ ﾃﾞｽ         " */
			return(FALSE);
		}
#endif

		/* スクランブル中・デスクランブル中は、禁止します */
		if (CheckCipherExecuting() == TRUE) {
			return(FALSE);
		}

		/* スクランブル・デスクランブルが、受信優先設定で中断されている時は、禁止します by K.Watanabe 1998/05/27 */
		if (SYS_CipherInterruptionOn == SYS_CIPHER_EXEC) {					/* ｽｸﾗﾝﾌﾞﾙ中に受信した時 */
			OPR_ChildErrorFlag = CIPHERING_ERROR;	/* "ｽｸﾗﾝﾌﾞﾙ ﾁｭｳﾃﾞｽ      " */
			return(FALSE);
		}
		else if (SYS_CipherInterruptionOn == SYS_DECIPHER_EXEC) {			/* 受信原稿ﾃﾞｽｸﾗﾝﾌﾞﾙ中に受信した時 */
			OPR_ChildErrorFlag = DECIPHERING_ERROR;	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳﾃﾞｽ" */
			return(FALSE);
		}
		else if (SYS_CipherInterruptionOn == SYS_TX_DOC_DECIPHER_EXEC) {	/* 送信予約原稿ﾃﾞｽｸﾗﾝﾌﾞﾙ中に受信した時 */
			OPR_ChildErrorFlag = DECIPHERING_ERROR;	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳﾃﾞｽ" */
			return(FALSE);
		}

		if ((call_place == OPR_DECIPHER_TX_DOC)		/* 暗号化予約原稿を復号化する時 98/03/11 Add By T.Fukumoto */
		 || (call_place == OPR_DECIPHER_RX_DOC)) {	/* 暗号化受信原稿を復号化する時 */
			/* デスクランブルした原稿が残っている時は、復号化できません（復号化用のバッファが固定の為） */
			if (SYB_CPH_RxPrint[0].Status != SYS_MCOPY_EMPTY) {
				OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;		/* "ﾌﾟﾘﾝﾄﾁｭｳ ﾃﾞｽ        " */
				return(FALSE);
			}
		}
		else {										/* 読み取った原稿に対して、暗号化・復号化する時 */
			/* 200x200より上の画質は、暗号化できません */
			if (CheckCipherEnableMode() == FALSE) {
				OPR_ChildErrorFlag = NO_SCAN_CIPHER_MODE_ERROR;	/* "ﾁｮｳｺｳｶﾞｼﾂ ﾊ ﾑｺｳ ﾃﾞｽ " */
				return(FALSE);
			}

#if (0)	/* ＦＢＳからの復号化可能検査の条件を追加するため、下記のように変更します。98/06/26 By T.Fukumoto */
//			/* ＡＤＦからの送信で、原稿がＡ３の時は暗号化出来ません（Ｂ４より大きい原稿は対応していません） */
//			if ((CMN_CheckScanDocOnFeeder() == TRUE) && (CMN_GetDocumentScanSize() == SYS_DOCUMENT_A3_SIZE)) {
//				OPR_ChildErrorFlag = NOT_SCAN_DOC_SIZE_ERROR;	/* "ｹﾞﾝｺｳ ｻｲｽﾞ ｶｸﾆﾝ     " */
//				return(FALSE);
//			}
#endif
			/* ＡＤＦからの送信で、原稿がＡ３の時は暗号化出来ません（Ｂ４より大きい原稿は対応していません） */
			if (CMN_CheckScanDocOnFeeder() == TRUE) {
				if (CMN_GetDocumentScanSize() == SYS_DOCUMENT_A3_SIZE) {
					OPR_ChildErrorFlag = NOT_SCAN_DOC_SIZE_ERROR;	/* "ｹﾞﾝｺｳ ｻｲｽﾞ ｶｸﾆﾝ     " */
					return(FALSE);
				}
			}
			/* ＦＢＳからの送信で、原稿幅がＡ４で原稿長がＡ４より長い時は暗号化出来ません 98/06/26 By T.Fukumoto */
			else {
				if ((IsBookDocSizeSet)
				 && ((SCN_RegularDocumentSize == SYS_REGULAR_SIZE_LEGAL) || (SCN_RegularDocumentSize == SYS_REGULAR_SIZE_F4))) {
					OPR_ChildErrorFlag = NOT_SCAN_DOC_SIZE_ERROR;	/* "ｹﾞﾝｺｳ ｻｲｽﾞ ｶｸﾆﾝ     " */
					return(FALSE);
				}
			}
		}
	}

	return(TRUE);
}

/*************************************************************************
	module		:[暗号化可能画質検査]
	function	:[
		1.現在の画質が、暗号化可能（200x200以下）か調べます
	]
	return		:[
		TRUE	:暗号化可能
		FALSE	:暗号化不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/11]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCipherEnableMode(void)
{
	UBYTE	ret;	/* リターン値 */

	switch (SYB_ModeSw) {
	case SYS_NORMAL:
	case SYS_FINE:
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		ret = TRUE;
		break;
	default:
		ret = FALSE;
		break;
	}

	return(ret);
}

/*************************************************************************
	module		:[センチをインチに変換]
	function	:[
		1.センチ(インチ×２.５４を四捨五入した値)をインチ×１０に変換します。
	]
	return		:[
		インチ×１０に変換したデータ。
		テーブルに該当するデータがない場合はテーブルの頭のデータを返します｡
	]
	common		:[OPR_ChangeInchCentiTable]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/15]
	author		:[福本貴吉]
*************************************************************************/
UBYTE ChangeCentiToInch(UBYTE centidata)
{
	UBYTE	loop;
	UBYTE	inch_data;	/* 戻り値 */

	/* テーブルから変換データを検索する
	** 該当するデータがない場合はテーブルの頭のデータを返します
	*/
	loop = 0;
	inch_data = OPR_ChangeInchCentiTable[0].Inch;
	while (OPR_ChangeInchCentiTable[loop].Centi != NULL) {
		if (centidata == OPR_ChangeInchCentiTable[loop].Centi) {
			inch_data = OPR_ChangeInchCentiTable[loop].Inch;
			break;
		}
		loop++;
	}
	return (inch_data);
}

/*************************************************************************
	module		:[インチをセンチに変換]
	function	:[
		1.インチ×１０を、センチ(インチ×２.５４を四捨五入した値)に変換する。
	]
	return		:[
		センチ(インチ×２.５４を四捨五入した値)に変換したデータ。
		テーブルに該当するデータがない場合はテーブルの頭のデータを返します。
	]
	common		:[OPR_ChangeInchCentiTable]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/15]
	author		:[福本貴吉]
*************************************************************************/
UBYTE ChangeInchToCenti(UBYTE inchdata)
{
	UBYTE	loop;
	UBYTE	centi_data;

	/* テーブルから変換データを検索する
	** 該当するデータがない場合はテーブルの頭のデータを返します
	*/
	loop = 0;
	centi_data = OPR_ChangeInchCentiTable[0].Centi;
	while (OPR_ChangeInchCentiTable[loop].Inch != NULL) {
		if (inchdata == OPR_ChangeInchCentiTable[loop].Inch) {
			centi_data = OPR_ChangeInchCentiTable[loop].Centi;
			break;
		}
		loop++;
	}
	return (centi_data);
}

/*************************************************************************
	module		:[暗号化・復号化実行中検査]
	function	:[
		1.暗号化・復号化が実行中かを調べます
	]
	return		:[
		TRUE	:暗号化・復号化　実行中
		FALSE	:暗号化・復号化　未実行
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/04/17]
	author		:[渡辺一章]
*************************************************************************/
UBYTE CheckCipherExecuting(void)
{
	if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_SCRAMBLE_EXEC) {		/* スクランブル中の時 */
		OPR_ChildErrorFlag = CIPHERING_ERROR;	/* "ｽｸﾗﾝﾌﾞﾙ ﾁｭｳﾃﾞｽ      " */
		return(TRUE);
	}

	if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_DESCRAMBLE_EXEC) {	/* デスクランブル中の時 */
		OPR_ChildErrorFlag = DECIPHERING_ERROR;	/* "ｽｸﾗﾝﾌﾞﾙ ｶｲｼﾞｮ ﾁｭｳﾃﾞｽ" */
		return(TRUE);
	}

	return(FALSE);
}

#endif	/* (PRO_CIPHER == ENABLE) */
