/*----------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                   */
/*  ファイル名   : mdm_fltr.c                                                 */
/*  作成者       :                                                            */
/*  日  付       : 1999/10/16                                                 */
/*  概  要       : フィルタ関連処理                                           */
/*  修正履歴     :                                                            */
/*	keyword			:[MDM]                                                    */
/*	machine			:[SH7043,V53]                                             */
/*	language		:[MS-C(Ver.6.0)]                                          */
/*----------------------------------------------------------------------------*/
/********
** define
********/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\define\param.h"

#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mem_pro.h"	/* 1996/07/09 Y.M */
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */
#include "\src\atlanta\define\uni_pro.h" /* by H.Kubo 1997/07/08 */
#include "\src\atlanta\sh7043\define\io_pro.h" /* Added by H.Kubo 1998/01/06 */
#include "\src\atlanta\define\fcm_def.h"		/* thonda */

/*******
** ext_v
*******/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h" /* Added by H.Kubo 1997/07/04. Please delete this line. */

/*************************************************************************
	module		:[モデムフィルタ設定]
	function	:[
		1.モデム拡張プログラムをロードする
		2.ゼロクロスを５０ｍｓで書き変えます（第２ダイヤルトーンは２５ｍｓ）
		3.各トーン検出によって、フィルタのＯＮ／ＯＦＦを設定します
		, 		フィルタ			Ａ（４００Ｈｚ）	Ｂ（１３００Ｈｚ）	Ｃ（２１００Ｈｚ）
		,		BEFORE_DIAL_FILTER	○					×					×
		,		AFTER_DIAL_FILTER	○					×					○
		,		CNG_FILTER			×					○					×
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	date		:[1994/03/25]
	author		:[曽根岡拓]
*************************************************************************/
/*
** POPLAR_H では、小さなスタックのタスクから MDM_FilterSet を呼ぶと、スタックが溢れる可能性が高いので、
** 暫定的に auto 変数を static にします。ただし、これで安心ではないので、抜本的な対策が
** 必要です。
** 1997/12/16 H.Kubo
*/
static	struct FilterTable_t  *filter1_tbl = 0;
static	struct FilterTable_t  *filter2_tbl = 0;
static	struct FilterTable_t  *filter3_tbl = 0;
void	MDM_FilterSet(UBYTE type)
{
	UBYTE country_code;
	UBYTE filter_no;
	country_code = 0;

	/* 1999/11/09 Y.Murata
	 * カントリーコード獲得
	*/
	country_code = SYB_MachineParameter[COUNTRY_CODE];
	if (country_code >= 8) {
		country_code = 0;
	}

	filter1_tbl = 0;	/* Add by O.Kimoto 1998/02/16 */
	filter2_tbl = 0;	/* Add by O.Kimoto 1998/02/16 */
	filter3_tbl = 0;	/* Add by O.Kimoto 1998/02/16 */

	/*------------------------------*/
	/* モデムのRTSPをクリアーします */
	/*------------------------------*/
	MDM_SetIO(POS_RTS,OFF);

	/*------------------------------------*/
	/* フィルタ番号、テーブルを設定します */
	/*------------------------------------*/
	switch (type) {
	case	BEFORE_DIAL_FILTER:
		filter_no = (MDM_FILTER1 | MDM_FILTER2);
		/*
		** FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23.
		*/
		filter1_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* BT, CT */
		filter2_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[0];	/* DT */
		break;
	case	AFTER_DIAL_FILTER:
		filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);
		/*
		** FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23.
		*/
		filter1_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* BT, CT */
		filter2_tbl = (struct FilterTable_t  *)&DIS_Filter72Table;
		filter3_tbl = (struct FilterTable_t  *)&CED_Filter72Table; /* ATD_DetectAnswerToneV25Task で使っている。 1998/01/08 */
		break;
	case	DIALTONE_2ND_FILTER:
		filter_no = MDM_FILTER1;
		/*
		** FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23.
		*/
		filter1_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[1];	/* DT2nd */
		break;
	case	CNG_FILTER:
		/*
		** Changed by H.Kubo 997/10/06
		*/
		filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);
		/*
		** FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23.
		*/
		filter1_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
		filter2_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
		filter3_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
		break;
	case	FSK_FILTER:
		filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);
		/*
		** FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23.
		*/
		/*
		** Changed by H.Kubo 1998/01/08
		*/
		filter1_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* Busy Tone, CT */
		filter2_tbl = (struct FilterTable_t  *)&FSK_Filter72Table; 	/* DIS_Tone のフィルタ番号は 2 */
		filter3_tbl = (struct FilterTable_t  *)&CED_Filter72Table; /* CED, ANSam */
		break;
	case	FSK_PIX_FILTER:	/* Add 6 line 1995/07/28 */
		filter_no = MDM_FILTER2;
		/*
		** FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23.
		*/
		filter1_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
		filter2_tbl = (struct FilterTable_t  *)&DIS_Filter72Table;
		filter3_tbl = (struct FilterTable_t  *)&FSK_Filter72Table;
		break;
	case	F_NET_FILTER:
		/*
		** Changed by H.Kubo 1997/12/10
		*/
		filter_no = MDM_FILTER3;
		filter3_tbl = (struct FilterTable_t *) &FnetFilter96Table;	 /* 1997/08/04 Y.Murata */
		/*
		** TONEA, TONEB のデバッグ用に filter 1,2 も設定します。 by H.Kubo 1997/12/11
		*/
		filter_no |= (MDM_FILTER1 | MDM_FILTER2);
		filter1_tbl = (struct FilterTable_t *) &FnetFilter72Table; /* 1997/08/04 Y.Murata */ /* filter3 => filter2 by H.Kubo 1997/12/10 */
		filter2_tbl = (struct FilterTable_t *) &FnetFilter96Table; /* 1997/08/04 Y.Murata */ /* filter3 => filter2 by H.Kubo 1997/12/10 */
		break;
	case	CNG_BT_FILTER:
		filter_no = (MDM_FILTER1 | MDM_FILTER3);
		filter1_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* BT, CT */
		filter3_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
		break;
	case	SPECIAL_DIAL_FILTER:
		filter_no = 0;
		break;
	case	V8_TONE_FILTER:		/** Ｖ．８モード時のフィルター設定 **/
		filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);
		filter1_tbl = (struct FilterTable_t  *)&V21_LowFilter96Table;
		filter2_tbl = (struct FilterTable_t  *)&V21_HighFilter96Table;
		filter3_tbl = (struct FilterTable_t  *)&AnswerToneFilter96Table;
		break;
	case	TX_V8_TONE_FILTER:		/** Ｖ．８モード時のフィルター設定 **/
		/*filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);*/
		filter_no = 5;
		filter1_tbl = (struct FilterTable_t  *)&AnswerToneFilter96Table;
		filter2_tbl = (struct FilterTable_t  *)&V21_HighFilter96Table;
		break;
	case	RX_V8_TONE_FILTER:		/** Ｖ．８モード時のフィルター設定 **/
		/*filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);*/
		filter_no = 5;
		filter1_tbl = (struct FilterTable_t  *)&V21_LowFilter96Table;
		filter2_tbl = (struct FilterTable_t  *)&V21_HighFilter96Table;
		break;
	case	V8_MODE_FSK_TONE_FILTER:	/** Ｖ．８モード時のフィルター設定 Not detect NSS by V21H Mode  beacuse Filter set Long Time 1996/10/23 Y.Murata **/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
		filter_no = (MDM_FILTER1 | MDM_FILTER2);
		filter1_tbl = (struct FilterTable_t  *)&BusyToneFilter96Table;
		filter2_tbl = (struct FilterTable_t  *)&V21_HighFilter96Table;
#else
		filter_no = MDM_FILTER2;
		filter2_tbl = (struct FilterTable_t  *)&V21_HighFilter96Table;
#endif
		break;
	case	RX_V23_TONE_FILTER:		/** Ｖ	２３モード時のフィルター設定 **/
		filter_no = (MDM_FILTER1 | MDM_FILTER2 | MDM_FILTER3);
		filter1_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* BT, CT */
		filter2_tbl = (struct FilterTable_t  *)& FnetFilter72Table; /* 1300Hz V23 '1' sequence */
		filter3_tbl = (struct FilterTable_t  *)&CED_Filter72Table; /* 2100Hz */
		break;
/* #if defined (POPLAR_F) || defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || defined (SATSUKI2) */
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || ((PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)) || (defined(SAKAKI) && defined(JP0)) || defined (SATSUKI2) || defined(STOCKHM2)
/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */	/* HINOKI2 2002/02/12 T.Takagi *//*POPLAR_H By Y.Suzuki 2002/06/11*//* NTT音声応答 && ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	case CNG_BUSY_FILTER:	/* 2000/02/02 Y.Murata */
 #if 0	/* 2000/03/21 Y.Murata CNGをﾌｨﾙﾀｰ３で見ます */
 //		filter_no = (MDM_FILTER1 | MDM_FILTER2);
 //		filter1_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
 //		filter2_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* BT, CT */
 #endif
		filter_no = (MDM_FILTER2 | MDM_FILTER3);
		filter2_tbl = (struct FilterTable_t  *)&MDM_CountryFilterTable[country_code].filter[2];	/* BT, CT */
		filter3_tbl = (struct FilterTable_t  *)&CNG_Filter72Table;
		break;
#endif
	default:
		filter_no = 0;
		break;
	}

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* added by H.Kubo 1999/06/25  */
	/* V29 9600bps 受信対策。今までと同じフィルタ設定なら、係数はそのままにしておく。 by H.Kubo 1999/06/25 */
	CMN_DisableInterrupt();
	if (MDM_CurrentFilterType == type) {
		filter_no = 0;
	}
	else {
		MDM_CurrentFilterType = type;
	}
	CMN_EnableInterrupt();
#endif

	/*------------------------------*/
	/* トーン検出係数をセットします */
	/*------------------------------*/

	/*
	** フィルター1のトーン検出係数をセットします
	*/
	if (filter_no & MDM_FILTER1) {

		/* フィルター係数 Biquad B1 A3 */
		MDM_SetFiterCoefficient((UWORD)0xAA1, (UWORD)filter1_tbl->b1_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A2 */
		MDM_SetFiterCoefficient((UWORD)0xAA2, (UWORD)filter1_tbl->b1_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A1 */
		MDM_SetFiterCoefficient((UWORD)0xAA3, (UWORD)filter1_tbl->b1_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B2 */
		MDM_SetFiterCoefficient((UWORD)0xAA4, (UWORD)filter1_tbl->b1_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B1 */
		MDM_SetFiterCoefficient((UWORD)0xAA5, (UWORD)filter1_tbl->b1_b1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A3 */
		MDM_SetFiterCoefficient((UWORD)0xBA1, (UWORD)filter1_tbl->b2_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A2 */
		MDM_SetFiterCoefficient((UWORD)0xBA2, (UWORD)filter1_tbl->b2_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A1 */
		MDM_SetFiterCoefficient((UWORD)0xBA3, (UWORD)filter1_tbl->b2_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B2 */
		MDM_SetFiterCoefficient((UWORD)0xBA4, (UWORD)filter1_tbl->b2_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B1 */
		MDM_SetFiterCoefficient((UWORD)0xBA5, (UWORD)filter1_tbl->b2_b1, (UWORD)0x0000);

		MDM_SetFiterCoefficient((UWORD)0xBA0, (UWORD)FilterLevelCountryTable[country_code][0].lpfbk, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xAA0, (UWORD)FilterLevelCountryTable[country_code][0].lpgain, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xAB8, (UWORD)FilterLevelCountryTable[country_code][0].threshu, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xBB8, (UWORD)FilterLevelCountryTable[country_code][0].threshl, (UWORD)0x0000);
	}

	/*
	** フィルター2のトーン検出係数をセットします
	*/
	if (filter_no & MDM_FILTER2) {
		/* フィルター係数 Biquad B1 A3 */
		MDM_SetFiterCoefficient((UWORD)0xAA7, (UWORD)filter2_tbl->b1_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A2 */
		MDM_SetFiterCoefficient((UWORD)0xAA8, (UWORD)filter2_tbl->b1_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A1 */
		MDM_SetFiterCoefficient((UWORD)0xAA9, (UWORD)filter2_tbl->b1_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B2 */
		MDM_SetFiterCoefficient((UWORD)0xAAA, (UWORD)filter2_tbl->b1_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B1 */
		MDM_SetFiterCoefficient((UWORD)0xAAB, (UWORD)filter2_tbl->b1_b1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A3 */
		MDM_SetFiterCoefficient((UWORD)0xBA7, (UWORD)filter2_tbl->b2_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A2 */
		MDM_SetFiterCoefficient((UWORD)0xBA8, (UWORD)filter2_tbl->b2_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A1 */
		MDM_SetFiterCoefficient((UWORD)0xBA9, (UWORD)filter2_tbl->b2_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B2 */
		MDM_SetFiterCoefficient((UWORD)0xBAA, (UWORD)filter2_tbl->b2_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B1 */
		MDM_SetFiterCoefficient((UWORD)0xBAB, (UWORD)filter2_tbl->b2_b1, (UWORD)0x0000);

		MDM_SetFiterCoefficient((UWORD)0xBA6, (UWORD)FilterLevelCountryTable[country_code][1].lpfbk, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xAA6, (UWORD)FilterLevelCountryTable[country_code][1].lpgain, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xAB9, (UWORD)FilterLevelCountryTable[country_code][1].threshu, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xBB9, (UWORD)FilterLevelCountryTable[country_code][1].threshl, (UWORD)0x0000);
	}

	/*
	** フィルター3のトーン検出係数をセットします
	*/
	if (filter_no & MDM_FILTER3) {
		MDM_SetIO(POS_SQDIS,ON);	/** Prefilterをスルーにセットします。 **/
		/* フィルター係数 Biquad B1 A3 */
		MDM_SetFiterCoefficient((UWORD)0xAB2, (UWORD)TransparentFilterTable.b1_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A2 */
		MDM_SetFiterCoefficient((UWORD)0xAB3, (UWORD)TransparentFilterTable.b1_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A1 */
		MDM_SetFiterCoefficient((UWORD)0xAB4, (UWORD)TransparentFilterTable.b1_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B2 */
		MDM_SetFiterCoefficient((UWORD)0xAB5, (UWORD)TransparentFilterTable.b1_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B1 */
		MDM_SetFiterCoefficient((UWORD)0xAB6, (UWORD)TransparentFilterTable.b1_b1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A3 */
		MDM_SetFiterCoefficient((UWORD)0xBB2, (UWORD)TransparentFilterTable.b2_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A2 */
		MDM_SetFiterCoefficient((UWORD)0xBB3, (UWORD)TransparentFilterTable.b2_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A1 */
		MDM_SetFiterCoefficient((UWORD)0xBB4, (UWORD)TransparentFilterTable.b2_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B2 */
		MDM_SetFiterCoefficient((UWORD)0xBB5, (UWORD)TransparentFilterTable.b2_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B1 */
		MDM_SetFiterCoefficient((UWORD)0xBB6, (UWORD)TransparentFilterTable.b2_b1, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A3 */
		MDM_SetFiterCoefficient((UWORD)0xAAD, (UWORD)filter3_tbl->b1_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A2 */
		MDM_SetFiterCoefficient((UWORD)0xAAE, (UWORD)filter3_tbl->b1_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 A1 */
		MDM_SetFiterCoefficient((UWORD)0xAAF, (UWORD)filter3_tbl->b1_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B2 */
		MDM_SetFiterCoefficient((UWORD)0xAB0, (UWORD)filter3_tbl->b1_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B1 B1 */
		MDM_SetFiterCoefficient((UWORD)0xAB1, (UWORD)filter3_tbl->b1_b1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A3 */
		MDM_SetFiterCoefficient((UWORD)0xBAD, (UWORD)filter3_tbl->b2_a3, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A2 */
		MDM_SetFiterCoefficient((UWORD)0xBAE, (UWORD)filter3_tbl->b2_a2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 A1 */
		MDM_SetFiterCoefficient((UWORD)0xBAF, (UWORD)filter3_tbl->b2_a1, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B2 */
		MDM_SetFiterCoefficient((UWORD)0xBB0, (UWORD)filter3_tbl->b2_b2, (UWORD)0x0000);

		/* フィルター係数 Biquad B2 B1 */
		MDM_SetFiterCoefficient((UWORD)0xBB1, (UWORD)filter3_tbl->b2_b1, (UWORD)0x0000);

		MDM_SetFiterCoefficient((UWORD)0xBAC, (UWORD)FilterLevelCountryTable[country_code][2].lpfbk, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xAAC, (UWORD)FilterLevelCountryTable[country_code][2].lpgain, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xABA, (UWORD)FilterLevelCountryTable[country_code][2].threshu, (UWORD)0x0000);
		MDM_SetFiterCoefficient((UWORD)0xBBA, (UWORD)FilterLevelCountryTable[country_code][2].threshl, (UWORD)0x0000);
	}

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* added by H.Kubo 1999/07/02  */
	if (SYS_ModemVersion >= MDM_L6719_12P_ES) {
		switch (ModemBlock.Type) { /* added by H.Kubo 1999/07/02 */
		case TYPE_V27:
		case TYPE_V29:
		case TYPE_V17:
		case TYPE_V33:
			/*------------------------------------------------------------------*/
			/* 高速にコンフィグしているときは、受信レベルは触らずに抜けます。   */
			/* FM336 V29 9600 bps の R3.3 対策ですが、他の場合もモデムが内部で  */
			/* パラメータを調節しているときに受信ゲインを触るのも気持ち悪いので */
			/* V27ter, V29, V17 でも受信ゲインは触らないようにします。          */
			/*------------------------------------------------------------------*/
			return;
		default:
			break;
		}
	}
#endif

	/*------------------------------------------*/
	/* 受信レベルとモデムのBYPASSをセットします */
	/*------------------------------------------*/
	switch (type) {
	case	FSK_FILTER:
	case	FSK_PIX_FILTER:	/* Add 1995/07/28 */
	case	CNG_FILTER:
	case	F_NET_FILTER:
	case	CNG_BT_FILTER:
	case	V8_TONE_FILTER:		/** Ｖ．８モード時のフィルター設定 **/
			/*--------------------------------------*/
			/* 受信レベルとBYPASS=OFFをセットします */
			/*--------------------------------------*/
			MDM_ReceiveLevelSet();
			break;
	case	VOICE_FILTER:
			/*--------------------------*/
			/* 受信レベルをセットします */
			/*--------------------------*/
			MDM_ReceiveLevelSet();
			break;
	case	BEFORE_DIAL_FILTER:
			/*--------------------------*/
			/* 受信レベルをセットします */
			/*--------------------------*/
			MDM_ReceiveLevelSet();
			break;
	case	DIALTONE_2ND_FILTER:
			/*--------------------------*/
			/* 受信レベルをセットします */
			/*--------------------------*/
			MDM_ReceiveLevelSet();
			break;
	case	AFTER_DIAL_FILTER:
			/*--------------------------*/
			/* 受信レベルをセットします */
			/*--------------------------*/
			MDM_ReceiveLevelSet();
			break;
	case	SPECIAL_DIAL_FILTER:
			break;
	default:
			break;
	}
}


/*************************************************************************
	module		:[ＴＡＤ用ＣＮＧ検出モデムフィルタ設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/25]
	author		:[曽根岡拓]
*************************************************************************/
void			MDM_FilterSetCNG(void)
{
	MDM_ToneModeConfig();	/* add 1997/02/13 Y.Murata */
	MDM_FilterSet(CNG_FILTER);
}


/*************************************************************************
	module		:[ＦＳＫ受信モデムモードに設定]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/03/25]
	author		:[曽根岡拓]
*************************************************************************/
void			MDM_FilterStandbyMode(void)
{
	/* 1997/05/29 Y.Murata
	 * 電話でＤＴＭＦでダイアル中に、強制ダイアルストップが行われると
	 * 次に電話した時に、ＤＴＭＦトーンをだしっぱなしになる時がある
	 * とりあえず、ここで信号送出をとめるためにＲＴＳを落とす
	*/
	MDM_SetIO(POS_RTS, OFF);

/*#if defined (HINOKI2)	 いらないかもしれないので、大きくくくっておく（暫定） */
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || defined (SATSUKI2) || defined(STOCKHM2)	/* V851 hook key offのときにﾓﾆﾀｽﾋﾟｰｶｰから異音がでる。By Y.Suzuki 2002/09/03 */ || (defined(SAKAKI) && defined(JP0))
#else
	AnalogSwitchTONE_Set(); /* made valid by H.Kubo 1997/12/18 */
#endif
	/*
	** TEL 待機で受話器を上げると ANSam が聞こえる対策
	** by H.Kubo 1998/12/22
	*/
	MDM_SetIO(POS_DTR, OFF);

	/*
	** 留守／ＦＡＸ待機でＦ網の 1300Hz トーンが取れない不具合対策。
	** added by H.Kubo 1998/12/14
	*/
	MDM_SetIO(POS_CONF,V8_SETUP); 
	MDM_SetIO_NewcAfterConf(POS_NEWC, ON, 0x4000); /* NEWC をしばく。 タイマーはSH2 の場合。 */

}


/******************************************************************************
	module		:[フィルター１検出タスク]
	function	:[
		1. イベント待ちします.
		2. メッセージを送信します.
		3. 無限ループします.
	]
	return		:[なし]
	common		:[
		mbxno     	メールボックス番号
	]
	condition	:[]
	comment		:[
		Ｈ８のコードをそのまま流用します。
	]
	ProtoType	:[void far MDM_DetectFilter1Task(struct FilterData *){}]
	date		:[1993/12/23]
	update		:[1995/11/27]
	update		:[1997/06/17]
	author		:[橘正樹,木元修]
******************************************************************************/
void  MDM_DetectFilter1Task(struct FilterData_t *filter )
{
	MESSAGE_t msg;

	msg.Message = filter->ReturnValue;
	wai_evt(EVT_TONE_FILTER1_ON);
	snd_msg(filter->SendMBX, &msg);
	wai_tsk(0xffff);
}


/******************************************************************************
	module		:[フィルター２検出タスク]
	function	:[
		1. イベント待ちします.
		2. メッセージを送信します.
		3. 無限ループします.
	]
	return		:[なし]
	common		:[
		mbxno     	メールボックス番号
	]
	condition	:[]
	comment		:[
		Ｈ８のコードをそのまま流用します。
	]
	ProtoType	:[void far MDM_DetectFilter2Task(struct FilterData * ){}]
	date		:[1993/12/23]
	update		:[1995/11/27]
	update		:[1997/06/17]
	author		:[橘正樹,木元修]
******************************************************************************/
void  MDM_DetectFilter2Task(struct FilterData_t *filter )
{
	MESSAGE_t msg;

	msg.Message = filter->ReturnValue;
	wai_evt(EVT_TONE_FILTER2_ON);
	snd_msg(filter->SendMBX, &msg);
	wai_tsk(0xffff);
}


/******************************************************************************
	module		:[フィルター３検出タスク]
	function	:[
		1. イベント待ちします.
		2. メッセージを送信します.
		3. 無限ループします.
	]
	return		:[なし]
	common		:[
		mbxno     	メールボックス番号
	]
	condition	:[]
	comment		:[
		Ｈ８のコードをそのまま流用します。
	]
	ProtoType	:[void far MDM_DetectFilter3Task(struct FilterData * ){}]
	date		:[1993/12/23]
	update		:[1995/11/27]
	update		:[1997/06/17]
	author		:[橘正樹,木元修]
******************************************************************************/
void  MDM_DetectFilter3Task(struct FilterData_t *filter )
{
	MESSAGE_t msg;

	msg.Message = filter->ReturnValue;
	wai_evt(EVT_TONE_FILTER3_ON);
	snd_msg(filter->SendMBX, &msg);
	wai_tsk(0xffff);
}

/******************************************************************************
	module		:[モデムの受信レベルの設定]
	function	:[
		1. 受信検出レベルのMAXGに-43dBm or -47dBmをセットします
	]
	return		:[なし]
	common		:[
		SYS_MemorySwitch  (C3:SW1)
	]
	condition	:[
		通信手順の先頭で設定します
		オートダイアラー処理終了後で再設定します
	]
	date		:[1993/11/29]
	author		:[橘正樹]
******************************************************************************/
void  MDM_ReceiveLevelSet(void)
{
	
	/*
	** Changd by H.Kubo according to CLOVER. 1997/12/25
	*/
	/* 1997/12/22 RTH_CONTROL
	** 受信レベルより受信器スレッショルドをコントロールします。
	*/
	if (SYS_V34ProcedureExecuting() == 0) {	/** 従来のプロトコルならば **/
		if (MDM_RTH_ControlStatus == 0xFF) {
			MDM_SetIO(POS_RTH,RTH_LOWEST);	/** ON=-43dBm / OFF=-48dBm **/
		}
		else {
			if ((MDM_RTH_ControlStatus == RTH_LOWEST) || (MDM_RTH_ControlStatus == RTH_LOWER) ||
				(MDM_RTH_ControlStatus == RTH_HIGHER) || (MDM_RTH_ControlStatus == RTH_HIGHEST)) {

				MDM_SetIO(POS_RTH, MDM_RTH_ControlStatus);
			}
			else {
				MDM_SetIO(POS_RTH,RTH_LOWEST);	/** ON=-43dBm / OFF=-48dBm **/
			}
		}
	}
	else {
		MDM_SetIO(POS_RTH,RTH_LOWEST);	/** ON=-43dBm / OFF=-48dBm **/
	}

#if 0	/* 削除 1999/12/28 Y.Murata SET_RTH_LEVEL */
	/*
	** RTS OFF の前から後ろに移動。
	** by H.Kubo 1998/10/20
	*/
	/*
	** R288Fバージョン24P以上のとき
	** by H.Kubo 1998/08/20
	*/
	if ((SYS_ModemVersion == MDM_L6713_24P)
 #if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
	|| (SYS_ModemVersion == MDM_L6719_12P_ES)
	|| (SYS_ModemVersion == MDM_L6719_12P_CS)
 #endif
	|| (SYS_ModemVersion == MDM_L6713_26P)) {
		MDM_SetIO(POS_RTH, (CHK_R288fModemRthLevel() << 2));
	}
#endif

	/*****************************************************
	** メモリ・スイッチに従って,受信検出レベルを設定します
	*****************************************************/
	if (CHK_CarrierDetectAvailable()) {
		MDM_SetReceiverGain(0xF54D);	/* とりあえず、直値とします By O.Kimoto 1996/05/20 */

	/*
	** 1996/12/13 Y,Murata
	** 桐＋の時テストで入れていたが、どうもＮＥＷＣをしばくと、Ｖ８でＣＭ送出が詰まってしまう。
	** 桐＋では初期値が違うから通常通らないがアンズでは通常通る。
	** テストでいれていただけだから消去！
	**	MDM_SetRTH0_Offset(0x00);		* test 1996/07/15 Y.Murata *
	**	MDM_SetIO(POS_NEWC, ON);		* test 1996/07/15 Y.Murata *
	*/

	}

}


/******************************************************************************
	module		:[留守/ＦＡＸ待機時の無音検出セットアップ]
	function	:[
		1. 
	]
	return		:[なし]
	common		:[]
	condition	:[]
	date		:[1997/02/20]
	author		:[]
******************************************************************************/
void  MDM_SetUpAnsFaxSilent(UBYTE mode)
{
	UBYTE	level;
	UBYTE	value;

	level = CHK_V34_AnsFaxSilentLevel();
	switch (level) {
	case 0:
		value = RTH_LOWEST;
		break;
	case 1:
		value = RTH_LOWER;
		break;
	case 2:
		value = RTH_HIGHER;
		break;
	case 3:
		value = RTH_HIGHEST;
		break;
	default:
		value = RTH_LOWER;
		break;
	}

	MDM_SetIO(POS_DTR, OFF);
	MDM_SetIO(POS_DATA, OFF);
	MDM_SetIO(POS_RTH, value);
	MDM_SetIO(POS_NEWC, ON);

	if (mode == 1) {	/* 無音検出優先設定なら */
		/* 受信レベルゲインをぐぅ～とさげて、無音を検出しやすいようにする */
		DspRamAccessWriteMethod3(0x0B3C, 0x0B00, 0x0000);
	}
}

/******************************************************************************
	module		:[留守/ＦＡＸ待機時の無音検出レベルか否か]
	function	:[
		1. 
	]
	return		:[
			０：無音レベル
			１：何かはいってる
	]
	common		:[]
	condition	:[]
	date		:[1997/02/20]
	author		:[]
******************************************************************************/
UBYTE  MDM_GetAnsFaxSilentLevel(void)
{
	if (MDM_GetIO(POS_FED)) {
		return(1);
	}
	else {
		return(0);
	}
}

