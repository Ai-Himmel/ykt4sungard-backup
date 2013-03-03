/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_TBL.H
*	Author		: 渡辺一章
*	Date		: 1996/10/17
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: オペレーションテーブル宣言
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef OPR_TBL_H
	#define OPR__TBL_H 1

#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\sysonet.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\ext_v\bkupram.h"

extern CONST UBYTE	MaxDayTable[][13];

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
/**************************************************************************************************
 * 文字テーブル
 *************************************************************************************************/
extern CONST UBYTE KATAKANA_CharacterTable[OPR_TEN_KEY_MAX][OPR_KATAKANA_CHARACTER_MAX];
extern CONST UBYTE AlphamericCharacterTable[OPR_TEN_KEY_MAX][OPR_ALPHAMERIC_CHARACTER_MAX];
extern CONST struct ANK_CharacterTable_t ANK_CharacterTable[];
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/***********************************************
 * ワンタッチ->記号変換テーブル
 ***********************************************/
extern CONST UBYTE	OnetouchSignalTable[];

/****************************************************:
 * 電話帳関係
 ******************************************************/
extern CONST UBYTE	TelBookSearchLineTable[];
extern CONST UBYTE	TelBookSortPriorityTable[];

/*---------------------------------------*/
/* コマンドの種別を変換するテーブル		 */
/* 同報、メモリ送信ON/OFFの設定によりITEM*/
/* を変換するためのテーブル				 */
/*---------------------------------------*/
extern CONST UBYTE	CommandOptionTable[][4];

/***************************************************************
 * ファンクションテーブル
 ***************************************************************/
extern CONST struct FUNCTION_TABLE_t OneTouchFunction[];
extern CONST struct FUNCTION_TABLE_t SpeedDialFunction[];
extern CONST struct FUNCTION_TABLE_t ProgramOnetouchFunction[];
extern CONST struct FUNCTION_TABLE_t PollingFunction[];
extern CONST struct FUNCTION_TABLE_t SecureMailFunction[];
extern CONST struct FUNCTION_TABLE_t DelayedCommandsFunction[];
extern CONST struct FUNCTION_TABLE_t SetReportFunction[];
extern CONST struct FUNCTION_TABLE_t UserSettingsFunction[];
extern CONST struct FUNCTION_TABLE_t UserSettingsFunction_Category2[];
extern CONST struct FUNCTION_TABLE_t MessageFunction[];
#if (PRO_DEPARTMENT == ENABLE)
extern CONST struct FUNCTION_TABLE_t DepartmentCodeFunction[];
#endif
#if (PRO_BATCH_TX == ENABLE)
extern CONST struct FUNCTION_TABLE_t BatchTxFunction[];
#endif
#if (PRO_SECURITY_RX == ENABLE)
extern CONST struct FUNCTION_TABLE_t SecurityRxFunction[];
#endif
#if (PRO_F_CODE == ENABLE)
extern CONST struct FUNCTION_TABLE_t FcodeFunction[];
#endif
#if (PRO_CIPHER == ENABLE)
extern CONST struct FUNCTION_TABLE_t CipherFunction[];
#endif
#if (PRO_CLASS1 == ENABLE)
extern CONST struct FUNCTION_TABLE_t Class1Function[];
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/03/12 by K.Okada */
extern CONST struct FUNCTION_TABLE_t EMailFunction[];
extern CONST struct FUNCTION_TABLE_t ReceiveMail[];
extern CONST struct FUNCTION_TABLE_t MailAddressFunction[];
extern CONST struct FUNCTION_TABLE_t ConfirmInternetFaxCommand[];
#endif
extern CONST struct FUNCTION_TABLE_t MainFunction[];
extern CONST struct FUNCTION_TABLE_t MainFunction_Category2[];	/* Ｆ－１０１専用 1997/12/26 Y.Matsukuma */

/* サービスファンクション */
extern CONST struct SERV_FUNCTION_t ServiceFunctionTable[];
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/10 */
extern CONST struct FUNCTION_TABLE_t KeisatsuServiceTable[];
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* 1997/06/25 Y.Matsukuma	*/
/* 親展ボックス登録オペレーション */
extern UBYTE (* (SetSMailFunction[]))(void);
#else	/* ANZU_L */
extern CONST UBYTE (*SetSMailFunction[])(void);
#endif

#if (PRO_F_CODE == ENABLE)
/* Ｆコードボックス登録オペレーション */
extern UBYTE (* (SetFcodeBoxFunction[]))(void);
#endif

#if (PRO_CIPHER == ENABLE)
/* 暗号化機能キーブック登録オペレーション */
extern UBYTE (* (SetCipherKeyBookFunction[]))(void);
#endif

/**********************************************************
 * セッティングデータの内、選択肢が３個以上あるものに関して
 * 選択肢の有効／無効を定義するテーブル.
 **********************************************************/
extern CONST UBYTE	ValidSelectBitPatternTable[];

/***********************************************************************************************
 * セッティングデータの内、選択肢が９個以上あるものに関して選択肢の有効／無効を定義するテーブル
 * ValidSelectBitPatternTable[]では、ＰＣプリント用の上段紙サイズが対応できないために作成
 ***********************************************************************************************/
#if (PRO_PC_PRINT == ENABLE)	/* DPRAM経由のPCﾌﾟﾘﾝﾄ機能 1996/09/17 by K.Watanabe */
extern CONST UDWORD	ValidSelectBitPatternTableLong[];
#endif

/******************************************
 * 各種ロムディップ
 ******************************************/

/* リングマスターパターン自動検出フラグ有効無効のスイッチ */
/* 1996/03/22 Eguchi */
extern CONST UBYTE	TeachingOperationEnable;

/* ワンタッチ・プログラムワンタッチ自動スタート有効無効のスイッチ */
/* １：自動スタート（ワンタッチ）　０：スタートキー入力が必要(ツータッチ）*/
extern CONST UBYTE	IsOnetouchAutoStart;

/* 通信中の通信予約でスタートキーを２かい押す／押さないのスイッチ */
/* 1996/07/18 Eguchi */
extern CONST UBYTE	PushStartTwiceFaxCom;

#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/15 */
 #if defined(JPN)
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/11/20
*             TYPE:  struct
*      VAR TO HOLD:
*      DESCRIPTION:  ローマ字カナ変換テーブル
************************************************************************/
/* SHCのコンパイラーではカタカナのキャラクター定義がコンパイルできないため、文字列の定義に変更します */
/* extern CONST UBYTE	ROMA_KATAKANA_Table[270][6]; */
extern CONST struct ROMAJI_KATAKANA_TABLE_t RomajiToKatakanaTable[OPR_ROMAJI_KANA_TABLE_MAX];

/************************************************************************
*               BY:
*             DATE:
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（ファクス待機日付表示用）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
   #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様（ボリュームＣＧの追加） by Y.Kano 2003/08/18 */
extern UBYTE CG_RamTableFaxReadyKanji[LCD_SPECIAL_CHARACTER_MAX][11];
   #else
extern UBYTE CG_RamTableFaxReadyKanji[LCD_SPECIAL_CHARACTER_MAX][LCD_CGRAM_TABLE_MAX];
   #endif
 #endif	/* JPN */

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/12/05
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（コピーモード原稿濃度・縦原稿表示用）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
extern CONST UBYTE CG_RamTableCopyModeDensity[LCD_SPECIAL_CHARACTER_MAX][LCD_CGRAM_TABLE_MAX];

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  96/12/05
*             TYPE:  CONST
*      VAR TO HOLD:
*      DESCRIPTION:  ＣＧ　ＲＡＭテーブル（濃度・ボリューム設定用）
*          COMMENT:  有効範囲は右上基準の７(縦)ｘ５(横)です
************************************************************************/
extern CONST UBYTE CG_RamTableDensityVolumeSet[LCD_SPECIAL_CHARACTER_MAX][LCD_CGRAM_TABLE_MAX];
#endif	/* (PRO_ANK_TO_KANJI == DISABLE) */

#if (PRO_COPY_FAX_MODE == ENABLE)
/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/03/07
*             TYPE:  CONST UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  手差し記録紙サイズ選択用テーブル
************************************************************************/
extern CONST struct OPR_MANUAL_PAPER_TABLE_t OPR_SelectManualPaperTable[];

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/03/10
*             TYPE:  CONST UBYTE
*      VAR TO HOLD:
*      DESCRIPTION:  コピー固定倍率テーブル
************************************************************************/
 #if defined(USA)
/* ５０％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_50[];

/* ６４％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_64[];

/* ７８％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_78[];

/* １２９％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_129[];

/* ２００％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_200[];

 #else		/* これ以下ＵＳＡ仕様以外（日本仕様、欧州仕様など）*/

/* ５０％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_50[];

/* ７０％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_70[];

/* ８１％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_81[];

/* ８６％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_86[];

/* １１５％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_115[];

/* １２２％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_122[];

/* １４１％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_141[];

/* １７２％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_172[];

/* ２００％用テーブル */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_FixedMagnification_200[];
 #endif /* defined(USA) */

/* 固定倍率　拡大用 */
extern CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedMagnificationTable[];

/* 固定倍率　縮小用 */
extern CONST struct OPR_FIXED_MAGNIFI_TABLE_t OPR_FixedReductionTable[];

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/04/04
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  ブックコピー原稿サイズ設定用テーブル
************************************************************************/
/* 記録紙　Ａ５用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_A5[];

/* 記録紙　レター用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_Letter[];

/* 記録紙　Ａ４用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_A4[];

/* 記録紙　リーガル用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_Legal[];

/* 記録紙　Ｂ５横用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_B5R[];

/* 記録紙　Ｂ４用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_B4[];

/* 記録紙　レター横用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_LetterR[];

/* 記録紙　Ａ５横用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_A5R[];

/* 記録紙　はがき用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_Post[];

/* 記録紙　Ｂ５用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_B5[];

/* 記録紙　ハーフレター横用テーブル */
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_HalfLetterR[];  /* added by honda 1997/10/04 */

/* 記録紙　Ｆ４用テーブル
extern CONST struct OPR_PRINT_PAPER_TABLE_t OPR_PrintPaperSize_F4[];  /* POPLAR_B AUS by thonda1998/05/12 */

/* ブックコピー原稿サイズ設定用テーブル */
extern CONST struct OPR_BOOK_COPY_DOC_TABLE_t OPR_BookCopyDocumentSizeTable[];

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/07/03
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  コピー不可能な原稿サイズ・記録紙サイズのテーブル
*          COMMENT:  テーブルの最後のデータをNULLで定義すると、紙サイズ
*                    の先頭のdefine値と同じになるので、テーブルの最後の
*                    データは0xFF(SYS_NO_PAPER)で定義します
************************************************************************/
/* Ａ４→ハガキもコピー禁止になり（実際は５０％以下なので）、結局ＡＤＦからハガキには
** コピーできなくなった為に、テーブルを使用してのチェックは必要ないので、削除します
*/
 #if (0)	/* by K.Watanabe 1997/12/26 */
extern CONST struct OPR_MAGNIFI_PAPER_TABLE_t OPR_CopyImposPaperCombiTable[];
 #endif

#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */

/************************************************************************
*               BY:  M.Kuwahara
*             DATE:  97/06/05
*             TYPE:  CONST UWORD
*      VAR TO HOLD:
*      DESCRIPTION:  工場ファンクション
************************************************************************/
/* ＬＥＤテスト用 点灯順序設定用テーブル */
extern CONST struct LED_AREA_t	LedArea[];

/* ＬＣＤテスト用 キー入力順序設定用テーブル */
extern CONST UBYTE	KeyArea[];

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  97/12/12
*             TYPE:  CONST struct
*      VAR TO HOLD:
*      DESCRIPTION:  インチ・センチ変換テーブル
*          COMMENT:  インチ入力された値をセンチに変換するだけなら、直接
*                    計算するだけで問題ないが、再表示でセンチからインチ
*                    に戻す時に、途中で四捨五入されているために計算では
*                    戻せないので、テーブルを作成しました
************************************************************************/
#if (PRO_CIPHER == ENABLE)
extern CONST struct OPR_INCH_CENTI_TABLE_t OPR_ChangeInchCentiTable[];
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* Add By H.Fujimura 1998/12/28 */
/* 拡張プログラムワンタッチ（リスト）*/
extern CONST struct OPR_ProgramList_t OPR_ProgramList[];
/* 拡張プログラムワンタッチ（蓄積）*/
extern CONST struct OPR_ProgramStore_t OPR_ProgramStore[];
/* 拡張プログラムワンタッチ（画質）*/
extern CONST UBYTE	OPR_ProgramTxModeSW[];
/* 拡張プログラムワンタッチ（濃度）*/
extern CONST UBYTE	OPR_ProgramContrastSW[];
/* 拡張プログラムワンタッチ（済スタンプ）*/
extern CONST UBYTE	OPR_ProgramStampSW[];
/* 拡張プログラムワンタッチ（メモリ送信）*/
extern CONST UBYTE	OPR_ProgramMemoryTxSW[];
/* 拡張プログラムワンタッチ（通信証）*/
extern CONST UBYTE	OPR_ProgramConfirmSW[];
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) 	/* For HINOKI By O.Kimoto 1998/10/07 */
extern CONST UBYTE CG_RamTableNumericSymbol[4][8];
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* SATSUKI2仕様 by Y.Kano2003/08/11 */
extern CONST UBYTE CG_RamTableNumericSymbol[8][8];
#endif

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
/************************************************************************
*          BY:	清水政貴
*        DATE:	1996/06/10
* DESCRIPTION:  絵文字のフォントパターン
************************************************************************/
extern CONST UBYTE	LCD_PictureFontPattern[][32];
#endif

#endif	/* OPR_TBL_H */
