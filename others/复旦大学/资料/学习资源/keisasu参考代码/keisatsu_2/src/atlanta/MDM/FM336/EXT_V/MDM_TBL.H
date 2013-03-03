/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_tbl.c                                                 */
/*  モジュール   : MDM_FskPreAnbleTbl                                        */
/*               : MDM_EcmPhasingTbl                                         */
/*               : MDM_PixDummyTbl                                           */
/*               : MDM_TcfReceiveSkipTbl                                     */
/*               : MDM_TcfTbl                                                */
/*               : MDM_EyeSliceTbl                                           */
/*               : MDM_FskFilterTbl                                          */
/*               : MDM_CngFilterTbl                                          */
/*               : MDM_CedFilterTbl                                          */
/*               : MDM_462HzFilterTbl                                        */
/*               : MDM_VoiceFilterTbl                                        */
/*               : MDM_RxSensitivityTbl                                      */
/*               : MDM_SingleFreqTbl                                         */
/*               : MDM_DtmfFreqTbl                                           */
/*               : MDM_DtmfLevelTbl                                          */
/*  作成者       :                                                           */
/*  日  付       : 99/10/06                                                  */
/*  概  要       : モデムＲＯＭテーブル                                      */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"



/***************************/
/* H8                      */
/***************************/

#if (0)
** /*---------------------------*/
** /* FSKプリアンブル・テーブル */
** /*---------------------------*/
** extern CONST	UWORD far FskPreAnbleTable;	/* 1秒 */
#endif

#if (0)
** /*---------------------*/
** /* ECM同期信号テーブル */
** /*---------------------*/
** extern CONST	UWORD far EcmPhasingTable;	/* 200ms */
#endif

#if (0)
** /*----------------------------*/
** /* 画データのダミー・テーブル */
** /*----------------------------*/
** /* 800msダミー信号するバイト数 */
** extern CONST	UWORD far PixDummyTable[MDM_DUMMY_MAX];
#endif

#if (0)
** /*---------------------------*/
** /* TCF受信スキップ・テーブル */
** /*---------------------------*/
** /* 50msTCF受信を無視するバイト数 */
** extern CONST	UWORD far TcfReceiveSkipTable[MDM_TCF_SKIP_MAX];
#endif

#if (0)
** /*-------------*/
** /* TCFテーブル */
** /*-------------*/
** /* 1.5秒TCF送出するバイト数 */
** extern CONST	UWORD far TcfTable[MDM_TCF_MAX];
#endif

#if (0)
** /*------------------------------*/
** /* G3 256Byte受信タイマテーブル */
** /*------------------------------*/
** /* 600byte単位で6秒間ループ */
** extern CONST	UWORD far G3BlockTimerTable[6][2];
#endif

/*-----------------------*/
/* EYEスライス・テーブル */
/*-----------------------*/
extern CONST	UWORD far EyeSliceTable[][MDM_EYE_SPEED_TYPE][MDM_EYE_SLICE];

#if (0)
** /*-------------------------*/
** /* フィル・テーブル (Byte) */
** /*-------------------------*/
** extern CONST	unsigned char far MDM_FillTable[6][5];
#endif

/* 以下はＲ２８８Ｆモデムのフィルター係数である。
** フィルター係数は大きく分けて２種類ある。
**       Ｖ．８／Ｖ．３４モード時：サンプリング周波数＝９６００ｂｐｓ
**       上記以外の時            ：サンプリング周波数＝７２００ｂｐｓ
**/

/*
** FSK信号検出フィルター
** 1650Hz
** Center Frequency   : 1650Hz
** Sampling Frequency : 7200Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far FSK_Filter72Table;

/*
** CNG信号検出フィルター
** 1100Hz±30Hz
** Center Frequency   : 1100Hz
** Sampling Frequency : 7200Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far CNG_Filter72Table;

/*
** DIS信号検出フィルター
** 1600Hz～1900Hz
** Center Frequency   : 1650Hz
** Sampling Frequency : 7200Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far DIS_Filter72Table;

/*
** CED信号検出フィルター
** 2050Hz～2125Hz
** Center Frequency   : 2100Hz
** Sampling Frequency : 7200Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far CED_Filter72Table;

/*
** CED/DIS信号検出フィルター
** 1625Hz～2125Hz
** Center Frequency   : 1800Hz
** Sampling Frequency : 7200Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far CED_DIS_Filter72Table;

/*
** Ｆ網着信検出フィルター
** Center Frequency   : 1300Hz
** Sampling Frequency : 7200Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far FnetFilter72Table;


/*
** V21 High Signal信号検出フィルター
** Tabel value is 1650Hz
** Center Frequency   : 1650Hz
** Sampling Frequency : 9600Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far V21_HighFilter96Table;

/*
** V21 Low Signal 信号検出フィルター
** Tabel value is 1080Hz
** Center Frequency   :  980Hz
** Sampling Frequency : 9600Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far V21_LowFilter96Table;

/*
** Answer Tone(ANSam or CED) Signal 信号検出フィルター
** Tabel value is 2100Hz
** Center Frequency   : 2100Hz
** Sampling Frequency : 9600Hz
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far AnswerToneFilter96Table;

/*
** Tone C Detecter sets transparent Mode
*/
/* FilterTable_def is renamed FilterTable_t by H. Kubo 1997/06/23 */
extern CONST struct FilterTable_t far TransparentFilterTable;

extern CONST struct FilterTable_t far FnetFilter96Table;	/*  by T.Soneoka 1997/12/09 */

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/11 */
extern CONST struct FilterTable_t far BusyToneFilter96Table;
 #endif
#endif


/* フィルタ－　レベル検出部　テーブル */
/* FilterLevelTable_def is renamed FilterLevelTable_t by H. Kubo 1997/06/23. */
/*	extern CONST struct FilterLevelTable_def far FilterLevelCountryTable[][3]; */
	extern CONST struct FilterLevelTable_t far FilterLevelCountryTable[][3];

/*---------------------------*/
/* 送信検出レベル(All Modes) */
/*---------------------------*/
/** 変更済み By O.K Nov.16,1995 **/
extern CONST UWORD far TxOutputLevelAll[MDM_TX_OUTPUT_LEVEL_ALL_MAX];

/*-----------------------*/
/* 送出レベル(All Modes) */
/*-----------------------*/
/** 変更済み By O.K Nov.16,1995 **/
extern CONST UWORD far TxOutputLevelFSK[2/** CEQ **/][2/** Answer/originate **/][MDM_TX_OUTPUT_LEVEL_FSK_MAX];

/*------------------*/
/* 単一トーン周波数 */
/*------------------*/
/** 変更済み By O.K Nov.16,1995 **/
extern CONST UWORD far SingleFrequencyTable[MDM_SINGLE_MAX];

/*------------*/
/* DTMF周波数 */
/*------------*/
/** 変更済み By O.K Nov.16,1995 **/
/* Struct name is modified by H. Kubo, 1997/06/17 */
/* extern CONST struct DTMF_FrequencyTable_def far DTMF_FrequencyTable[MDM_DTMF_FREQ_MAX]; */
extern CONST struct DTMF_FrequencyTable_t far DTMF_FrequencyTable[MDM_DTMF_FREQ_MAX]; 

/*---------------------------------*/
/* 送出レベル(Ps)                  */
/* Ps = 18426*(10^((dBm+5)/20))    */
/*    デフォルト:7FFF=0dBm         */
/*---------------------------------*/
/*------------*/
/* DTMFレベル */
/*------------*/
/** 変更済み By O.K Nov.16,1995 **/
/* 高群、低群レベル差 -2dBm */
	/* 国別対応 1997/03/28 Y.Murata */
	/* Struct name is modified by H. Kubo, 1997/06/17 */
	/* extern CONST struct DTMF_LevelTable_def far DTMF_LevelCountryTable[][MDM_DTMF_LVL_MAX]; */
	extern CONST struct DTMF_LevelTable_t far DTMF_LevelCountryTable[][MDM_DTMF_LVL_MAX];

/*--------------------------------------*/
/* ＡＲＡ  Ｔｈｒｅｓｈｏｌｄ  テーブル */
/*--------------------------------------*/
extern CONST UWORD far ARAThresholdTable[6][DATA_RATE_MAX];

/*--------------------------------------*/
/* ＡＲＡ  Ｔｈｒｅｓｈｏｌｄ  テーブル */
/*--------------------------------------*/
/* // extern CONST unsigned char far EQMAveragingTable[EQM_AVERAGE_MAX]; */

/*-------------------------------------------------------------*/
/* モデムＩｎｔｅｒＦａｃｅ Ｍｅｍｏｒｙ Ａｃｃｅｓｓ用テーブル*/
/*-------------------------------------------------------------*/
extern CONST struct MDM_I_O_Memory_t far MDM_I_O_MemoryMap[POS_NSIA+1];

/************************/
/* 国別フィルタテーブル */
/************************/
/* CountryFilterTbl_def is renamed CountryFilterTbl_t by H. Kubo 1997/06/23. */
extern CONST struct CountryFilterTbl_t far MDM_CountryFilterTable[];

/******************/
/* V53            */
/******************/
#if (0)
** extern CONST unsigned char	far	EYEQ_SliceTable[10][4];
** extern CONST char far DTMF_TxDialTable[ DIAL_MAX ];
** extern CONST unsigned char far DTMF_RxDialTable[ DIAL_MAX ];
#endif

extern CONST	unsigned char far ToneTable[];
/*-------------------*/
/* ﾎﾞｰﾚｰﾄ 設定ﾃｰﾌﾞﾙ  */
/*-------------------*/
#if (0)
** extern CONST	unsigned char	far ModemLow[];
** extern CONST	unsigned char	far ModemHigh[];
#endif

#if (0)
//extern CONST	UWORD	far TxReductionA4_DocTable[12][8];
//extern CONST	UWORD	far TxReductionB4_DocTable[12][8];
//extern CONST	UWORD	far TxReductionA3_DocTable[12][8];
#endif

/**********************************************************
** 送信原稿A4サイズのインチ-インチ、ミリ-ミリ変換テーブル
***********************************************************/
extern CONST	UWORD	TxReductionInchA4_DocTable[15][10];
#if (0) /* 600dpi×600dpi対応 1999/06/02 by K.Okada */
/*--------------------------------------------------------------------------------------*/
/*	送信　モード／サイズ／インチ～ミリ変換テーブル　送信原稿がＡ４サイズ（インチ系）	*/
/*--------------------------------------------------------------------------------------*/
//extern CONST	UWORD	far TxReductionInchA4_DocTable[12][8];
#endif

#if (0)
/*----------------------------------------------------------------------------------*/
/*	送信　モード／サイズ／インチ～ミリ変換テーブル　送信原稿がＡ４サイズ（ミリ系）	*/
/*----------------------------------------------------------------------------------*/
//extern CONST	UWORD	far TxReductionMetricA4_DocTable[12][8];
#endif

/**********************************************************
** 送信原稿B4サイズのインチ-インチ、ミリ-ミリ変換テーブル
***********************************************************/
extern CONST	UWORD	TxReductionInchB4_DocTable[15][10];
#if (0) /* 600dpi×600dpi対応 1999/06/02 by K.Okada */
/*--------------------------------------------------------------------------------------*/
/*	送信　モード／サイズ／インチ～ミリ変換テーブル　送信原稿がＢ４サイズ（インチ系）	*/
/*--------------------------------------------------------------------------------------*/
//extern CONST	UWORD	far TxReductionInchB4_DocTable[12][8];
#endif

#if (0)
/*----------------------------------------------------------------------------------*/
/*	送信　モード／サイズ／インチ～ミリ変換テーブル　送信原稿がＢ４サイズ（ミリ系）	*/
/*----------------------------------------------------------------------------------*/
//extern CONST	UWORD	far TxReductionMetricB4_DocTable[12][8];
#endif

/**********************************************************
** 送信原稿A3サイズのインチ-インチ、ミリ-ミリ変換テーブル
***********************************************************/
extern CONST	UWORD	far TxReductionInchA3_DocTable[15][10];
#if (0) /* 600dpi×600dpi対応 1999/06/02 by K.Okada */
/*--------------------------------------------------------------------------------------*/
/*	送信　モード／サイズ／インチ～ミリ変換テーブル　送信原稿がＡ３サイズ（インチ系）	*/
/*--------------------------------------------------------------------------------------*/
//extern CONST	UWORD	far TxReductionInchA3_DocTable[12][8];
#endif

#if (0)
/*----------------------------------------------------------------------------------*/
/*	送信　モード／サイズ／インチ～ミリ変換テーブル　送信原稿がＡ３サイズ（ミリ系）	*/
/*----------------------------------------------------------------------------------*/
//extern CONST	UWORD	far TxReductionMetricA3_DocTable[12][8];
#endif

/**********************/
/* テスト送信パターン */
/**********************/
extern CONST	unsigned char	far	PixTestPatternTable[5][5];

#if (0)
** extern CONST unsigned char far DBG_DmaStart;	/** For Debug By O.K Jan.25,1996 **/
** extern CONST unsigned char far DATA_RATE_CHANGE;	/** Advive by Mr.Palm Sh - PPh Trouble By O.Kimoto 1996/07/17 **/
#endif

extern CONST UWORD far AdjustTxOutputLevel[MDM_TX_OUTPUT_LEVEL_ADJUST_MAX];	/* Add For Debug by O.Kimoto 1996/03/12 */

extern CONST	UWORD CRCTab[];	/* ORANGEからコピーしてきました。By O.Kimoto 1997/06/12 */

extern UWORD MDM_EcmTxFillFlagsTable[];/* Ecm Tx のフレーム間フラグ送出時の待ち時間(100us 単位の時間) by H.Kubo 1999/01/25 */

/*
** ECMバッファ -> CDC -> DRAMパスチェック用
** 1999/05/18 by K.Okada
*/
#if defined (SIRAKABA)
extern CONST UWORD EcmBufferData[];
#endif

