#ifndef wording_h
    #define wording_h

#include	"\src\atlanta\define\product.h"

/***********************************************************************
*          BY:   M.Kotani
*        DATE:   Tue 22 Mar 1994
*        TYPE:   DEFINE
* VAR TO HOLD:   
* DESCRIPTION:   国別Wording Type & Date Type
*	  UPDATED:	 By S.K 2/23/93
*	  UPDATED:	 By J.C.S(J.M) 6/24/93
*	  UPDATED:   95/03/13	By j.masuda
*					defined(US2)を追加。
*
*	Group No 1	JPN_ROM		JPN,AP								JAP/ENG
*	Group No.2	USA_ROM		USA(CAN)							ENG/FRE/SPA
*	Group No.3	DEU_ROM		DEU									GER/ENG/FRE
*	Group No.4	SWE_ROM		SWE									ENG/SWE/GER
*	Group No.5	ITA_ROM		ITA									ITA/ENG/GER
*	Group No.6	CHE_ROM		CHE									GER/ITA/FRE
*	Group No.7	ESP_ROM		ESP									SPA/ENG/FRE
*	Group No.8	FRA_ROM		FRA									FRE/GER/ENG
*	Group No.9	GBR_ROM		GBR,IRL,DNK,FIN,GRC,NLD,BEL,AUS		ENG/FRE/GER
*	Group No.10	TUR_ROM		TUR,ARE,ZAF,ISR,CYP,East			ENG/FRE/SPA
*	Group No.11	SEA_ROM		SAU,SGP,THA,HKG,IND,IDN,MYS			ENG/FRE/SPA
*	Group No.12	AUT_ROM		AUT,NOR								GER/ENG/FRE
*	Group No.13	CHN_ROM		CHN									CHN
*	Group No.14	AUS_ROM		AUS									ENG/FRE/SPA   1996/08/12 by H,Yagi 
*	Group No.15	TWN_ROM		TWN									ENG/FRE/SPA   1996/08/24 by H,Yagi 
*	Group No.16	SGP_ROM		SGP									ENG/FRE/SPA   1996/08/24 by H,Yagi 

************************************************************************/

/* Wording Type Number */
#define	JAPANESE		1
#define	ENGLISH			2
#define	FRENCH			3
#define	GERMAN			4
#define	SPANISH			5
#define	ITALIAN			6
#define	SWEDISH			7
#define	CHINESE			8
#define	DANISH			9
#define	DUTCH			10
#define	NORWEGIAN		11
#define PORTUGUESE		12
#define	DUMMY			13

/* Display Wording Type */
/* ２行ＬＣＤ用 */
#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
#define	D2W_JAPANESE	"\src\atlanta\opr\ank\wording\ntt_wjpn.c"	/* 日本語			*/
#define	D2W_ENGLISH		"\src\atlanta\opr\ank\wording\ntt_wusa.c"	/* 英語				*/
#else
#define	D2W_JAPANESE	"\src\atlanta\opr\ank\wording\opr_wjpn.c"	/* 日本語			*/
#define	D2W_ENGLISH		"\src\atlanta\opr\ank\wording\opr_wusa.c"	/* 英語				*/
#endif
#define	D2W_FRENCH		"\src\atlanta\opr\ank\wording\opr_wfra.c"	/* フランス語		*/
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/07/15 */
#define	D2W_GERMAN		"\src\atlanta\opr\ank\wording\oki_odeu.c"	/* ドイツ語			*/
#else
#define	D2W_GERMAN		"\src\atlanta\opr\ank\wording\opr_wdeu.c"	/* ドイツ語			*/
#endif
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	D2W_SPANISH		"\src\atlanta\opr\ank\wording\oki_oesp.c"	/* スペイン語		*/
#else
#define	D2W_SPANISH		"\src\atlanta\opr\ank\wording\opr_wesp.c"	/* スペイン語		*/
#endif
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	D2W_ITALIAN		"\src\atlanta\opr\ank\wording\oki_oita.c"	/* イタリア語		*/
#else
#define	D2W_ITALIAN		"\src\atlanta\opr\ank\wording\opr_wita.c"	/* イタリア語		*/
#endif
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	D2W_SWEDISH		"\src\atlanta\opr\ank\wording\oki_oswe.c"	/* スウェーデン語	*/
#else
#define	D2W_SWEDISH		"\src\atlanta\opr\ank\wording\opr_wswe.c"	/* スウェーデン語	*/
#endif
#define	D2W_CHINESE		"\src\atlanta\opr\ank\wording\opr_wchn.c"	/* 中国語			*/
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	D2W_DANISH		"\src\atlanta\opr\ank\wording\oki_odnk.c"	/* デンマーク語		*/
#define	D2W_DUTCH		"\src\atlanta\opr\ank\wording\oki_onld.c"	/* オランダ語		*/
#define	D2W_NORWEGIAN	"\src\atlanta\opr\ank\wording\oki_onor.c"	/* ノルウェー語		*/
#else
#define	D2W_DANISH		"\src\atlanta\opr\ank\wording\opr_wdnk.c"	/* デンマーク語		*/
#define	D2W_DUTCH		"\src\atlanta\opr\ank\wording\opr_wnld.c"	/* オランダ語		*/
#endif
#define	D2W_PORTUGUESE	"\src\atlanta\opr\ank\wording\opr_wprt.c"	/* ポルトガル語		*/

/* ４行ＬＣＤ用 */
#define	D4W_JAPANESE	"\src\atlanta\opr\kanji\wording\opr_wjpn.c"	/* 日本語			*/
#define	D4W_ENGLISH		"\src\atlanta\opr\kanji\wording\opr_wusa.c"	/* 英語				*/
#define	D4W_FRENCH		"\src\atlanta\opr\kanji\wording\opr_wfra.c"	/* フランス語		*/
#define	D4W_GERMAN		"\src\atlanta\opr\kanji\wording\opr_wdeu.c"	/* ドイツ語			*/
#define	D4W_SPANISH		"\src\atlanta\opr\kanji\wording\opr_wesp.c"	/* スペイン語		*/
#define	D4W_ITALIAN		"\src\atlanta\opr\kanji\wording\opr_wita.c"	/* イタリア語		*/
#define	D4W_SWEDISH		"\src\atlanta\opr\kanji\wording\opr_wswe.c"	/* スウェーデン語	*/
#define	D4W_DUMMY		"\src\atlanta\opr\kanji\wording\opr_wdmy.c"	/* ダミー（空）語	*/

/* List Print Wording Type */
#define	LST_JAPANESE	"\src\atlanta\wording\lst_wrdj.c"			/* 日本語 lst_wrdj.cでlst_wjpn.c(半角対応)とlst_wkan.c(全角対応)に分けている '94/4/1 toyoda*/
#define	LST_ENGLISH		"\src\atlanta\wording\lst_wusa.c"			/* 英語				*/
#define	LST_FRENCH		"\src\atlanta\wording\lst_wfra.c"			/* フランス語		*/
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/07/15 */
#define	LST_GERMAN		"\src\atlanta\wording\oki_ldeu.c"			/* ドイツ語			*/
#else
#define	LST_GERMAN		"\src\atlanta\wording\lst_wdeu.c"			/* ドイツ語			*/
#endif
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	LST_SPANISH		"\src\atlanta\wording\oki_lesp.c"			/* スペイン語		*/
#else
#define	LST_SPANISH		"\src\atlanta\wording\lst_wesp.c"			/* スペイン語		*/
#endif
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	LST_ITALIAN		"\src\atlanta\wording\oki_lita.c"			/* イタリア語		*/
#else
#define	LST_ITALIAN		"\src\atlanta\wording\lst_wita.c"			/* イタリア語		*/
#endif
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	LST_SWEDISH		"\src\atlanta\wording\oki_lswe.c"			/* スウェーデン語	*/
#else
#define	LST_SWEDISH		"\src\atlanta\wording\lst_wswe.c"			/* スウェーデン語	*/
#endif
#define	LST_CHINESE		"\src\atlanta\wording\lst_wchn.c"			/* 中国語			*/
#if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
#define	LST_DANISH		"\src\atlanta\wording\oki_ldnk.c"			/* デンマーク語		*/
#define	LST_DUTCH		"\src\atlanta\wording\oki_lnld.c"			/* オランダ語		*/
#define	LST_NORWEGIAN	"\src\atlanta\wording\oki_lnor.c"			/* ノルウェー語		*/
#else
#define	LST_DANISH		"\src\atlanta\wording\lst_wdnk.c"			/* デンマーク語		*/
#define	LST_DUTCH		"\src\atlanta\wording\lst_wnld.c"			/* オランダ語		*/
#endif
#define	LST_DUMMY		"\src\atlanta\wording\lst_wdmy.c"			/* ダミー語			*/
#define	LST_PORTUGUESE	"\src\atlanta\wording\lst_wprt.c"			/* ポルトガル語		*/

/* Rom Type ※WORDING_1,2,3の重複登録は禁止(ﾗﾍﾞﾙ重複の為)*/
/* 国別ロム追加のときにはここに追加してください */
#if defined(JPN) || defined(AP)	/* Group No.1 */
	#define	WORDING_1	JAPANESE
	#define	WORDING_2	ENGLISH
 #if (PRO_PANEL == ANK)
	#define	WORDING_3	FRENCH		/* ダミー（領域確保用） */
 #endif
 #if (PRO_PANEL == KANJI)
	#define	WORDING_3	DUMMY
 #endif
#endif

#if defined(USA) || defined(US2)	/* Group No.2 */
 #if (PRO_PANEL == ANK)
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	SPANISH
 #else
	/* テストメイク用にワーディングをＪＰＮと同じにします。 By O.Kimoto 1998/05/25 */
	#define	WORDING_1	JAPANESE
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	DUMMY
 #endif
#endif

#if defined(EU1)
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	GERMAN
	#define	WORDING_3	FRENCH
#endif
#if defined(EU2)
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	ITALIAN
	#define	WORDING_3	SPANISH
#endif
#if defined(EU3)
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	DANISH
	#define	WORDING_3	PORTUGUESE
#endif
#if defined(EU4)
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	DUTCH
#endif

#if defined(DEU)	/* Group No.3 */
	#define	WORDING_1	GERMAN
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	FRENCH
#endif

#if defined(SWE)	/* Group No.4 */
 #if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
	#define	WORDING_1	SWEDISH
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	DANISH
 #else
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	SWEDISH
	#define	WORDING_3	GERMAN
 #endif
#endif

#if defined(ITA)	/* Group No.5 */
 #if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
	#define	WORDING_1	ITALIAN
	#define	WORDING_2	FRENCH
	#define	WORDING_3	GERMAN
 #else
	#define	WORDING_1	ITALIAN
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	GERMAN
 #endif
#endif

#if defined(CHE)	/* Group No.6 */
	#define	WORDING_1	GERMAN
	#define	WORDING_2	ITALIAN
	#define	WORDING_3	FRENCH
#endif

#if defined(ESP)	/* Group No.7 */
 #if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
	#define	WORDING_1	SPANISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	ENGLISH
 #else
	#define	WORDING_1	SPANISH
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	FRENCH
 #endif
#endif

#if defined(FRA)	/* Group No.8 */
	#define	WORDING_1	FRENCH
	#define	WORDING_2	GERMAN
	#define	WORDING_3	ENGLISH
#endif

#if defined(GBR)	/* Group No.9 */
 #if (PRO_PANEL == KANJI)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	WORDING_1	JAPANESE
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	DUMMY
 #else
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	GERMAN
 #endif
#endif

#if defined(TUR)	/* Group No.10 */
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	SPANISH		/* ドイツ語のワーディングが入りしだい変更　*/
#endif

#if defined(SEA)	/* Group No.11 */
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	SPANISH		/* ドイツ語のワーディングが入りしだい変更　*/
#endif

#if defined(NOR)	/* Group No.12 */
 #if (PRO_OKI == ENABLE)	/* 沖仕様 by K.Watanabe 1998/09/17 */
	#define	WORDING_1	NORWEGIAN
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	DANISH
 #else
	#define	WORDING_1	GERMAN
	#define	WORDING_2	ENGLISH
	#define	WORDING_3	FRENCH
 #endif
#endif

#if defined(CHN) /* Group No.13 */
	#define	WORDING_1	CHINESE
	#define	WORDING_2	FRENCH		/* ダミー（領域確保用） */
	#define	WORDING_3	SPANISH		/* ダミー（領域確保用） */
#endif

#if defined(AUS)	/* Group No.14 *//* 1996.08.12 by H.Yagi */
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	GERMAN		/* 1998/03/12 Y.Murata SPANISH->GERMAN */
#endif

#if defined(TWN)	/* Group No.15 *//* 1996.08.24 by H.Yagi */
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	GERMAN		/* 1998/02/23 Y.Murata SPANISH->GERMAN(技連MCH-GTIZX-009) */
#endif

#if defined(SGP)	/* Group No.16 *//* 1996.08.24 by H.Yagi */
	#define	WORDING_1	ENGLISH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	SPANISH
#endif

#if (0)	/* 今後、ｺﾝﾊﾟｲﾙ時に、EC1を指定する事は無い（ｿｰｽ中では、逆にEC1しか使いません）ので、削除します by K.Watanabe 1998/09/18 */
// #if defined(EC1)	/* Group No.17 *//* BY M.Harada 98/04/09 */
//	#define	WORDING_1	ENGLISH
//	#define	WORDING_2	FRENCH
//	#define	WORDING_3	GERMAN
// #endif
#endif

#if defined(BEL)	/* by K.Watanabe 1998/09/17 */
	#define	WORDING_1	DUTCH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	GERMAN
#endif

#if (0)	/* ROM管理の都合で、同じﾜｰﾃﾞｨﾝｸﾞの組み合わせ(DNK → NOR)を1つにします（順番はﾃﾞｨｯﾌﾟSWにて対応） by K.Watanabe 1998/10/22 */
//#if defined(DNK)	/* by K.Watanabe 1998/09/17 */
//	#define	WORDING_1	DANISH
//	#define	WORDING_2	ENGLISH
//	#define	WORDING_3	NORWEGIAN
//#endif
#endif

#if (0)	/* ROM管理の都合で、同じﾜｰﾃﾞｨﾝｸﾞの組み合わせ(FIN → SWE)を1つにします（順番はﾃﾞｨｯﾌﾟSWにて対応） by K.Watanabe 1998/10/22 */
//#if defined(FIN)	/* by K.Watanabe 1998/09/17 */
//	#define	WORDING_1	ENGLISH
//	#define	WORDING_2	SWEDISH
//	#define	WORDING_3	DANISH
//#endif
#endif

#if defined(NLD)	/* by K.Watanabe 1998/09/17 */
	#define	WORDING_1	DUTCH
	#define	WORDING_2	FRENCH
	#define	WORDING_3	ENGLISH
#endif


/* ワーディングの詳細設定 */
/* 日本語の時 */
#if (WORDING_1 == JAPANESE)
	#define	D2W_WORDING_1	D2W_JAPANESE
	#define	D4W_WORDING_1	D4W_JAPANESE
	#define	LST_WORDING_1	LST_JAPANESE
	#define	DATE_WORDING_1	JPN_CLOCK_TYPE
#endif
#if (WORDING_2 == JAPANESE)
	#define	D2W_WORDING_2	D2W_JAPANESE
	#define	D4W_WORDING_2	D4W_JAPANESE
	#define	LST_WORDING_2	LST_JAPANESE
	#define	DATE_WORDING_2	JPN_CLOCK_TYPE
#endif
#if (WORDING_3 == JAPANESE)
	#define	D2W_WORDING_3	D2W_JAPANESE
	#define	D4W_WORDING_3	D4W_JAPANESE
	#define	LST_WORDING_3	LST_JAPANESE
	#define	DATE_WORDING_3	JPN_CLOCK_TYPE
#endif

/* 英語の時 */
#if (WORDING_1 == ENGLISH)
	#define	D2W_WORDING_1	D2W_ENGLISH
	#define	D4W_WORDING_1	D4W_ENGLISH
	#define	LST_WORDING_1	LST_ENGLISH
 #if defined(USA) || defined(US2) || defined(AUS) || defined(TWN) || defined(SGP)	/* 95/03/13 By j.masuda */
	#define	DATE_WORDING_1	USA_CLOCK_TYPE
 #else				/* add by M.H '94/10/15 for GBR.SEA */
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
 #endif
#endif
#if (WORDING_2 == ENGLISH)
	#define	D2W_WORDING_2	D2W_ENGLISH
	#define	D4W_WORDING_2	D4W_ENGLISH
	#define	LST_WORDING_2	LST_ENGLISH
#if (0)	/* 無条件にＵＳＡタイプだったのを、ヨーロッパタイプとに分けます by K.Watanabe 1998/12/21 */
//	#define	DATE_WORDING_2	USA_CLOCK_TYPE
#endif
 #if defined(USA) || defined(US2) || defined(AUS) || defined(TWN) || defined(SGP) || defined(JPN)
	#define	DATE_WORDING_2	USA_CLOCK_TYPE
 #else
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
 #endif
#endif
#if (WORDING_3 == ENGLISH)
	#define	D2W_WORDING_3	D2W_ENGLISH
	#define	D4W_WORDING_3	D4W_ENGLISH
	#define	LST_WORDING_3	LST_ENGLISH
#if (0)	/* 無条件にＵＳＡタイプだったのを、ヨーロッパタイプとに分けます by K.Watanabe 1998/12/21 */
//	#define	DATE_WORDING_3	USA_CLOCK_TYPE
#endif
 #if defined(USA) || defined(US2) || defined(AUS) || defined(TWN) || defined(SGP) || defined(JPN)
	#define	DATE_WORDING_3	USA_CLOCK_TYPE
 #else
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
 #endif
#endif

/* フランス語の時 */
#if (WORDING_1 == FRENCH)
	#define	D2W_WORDING_1	D2W_FRENCH
	#define	D4W_WORDING_1	D4W_FRENCH
	#define	LST_WORDING_1	LST_FRENCH
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == FRENCH)
	#define	D2W_WORDING_2	D2W_FRENCH
	#define	D4W_WORDING_2	D4W_FRENCH
	#define	LST_WORDING_2	LST_FRENCH
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == FRENCH)
	#define	D2W_WORDING_3	D2W_FRENCH
	#define	D4W_WORDING_3	D4W_FRENCH
	#define	LST_WORDING_3	LST_FRENCH
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* ドイツ語の時 */
#if (WORDING_1 == GERMAN)
	#define	D2W_WORDING_1	D2W_GERMAN
	#define	D4W_WORDING_1	D4W_GERMAN
	#define	LST_WORDING_1	LST_GERMAN
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == GERMAN)
	#define	D2W_WORDING_2	D2W_GERMAN
	#define	D4W_WORDING_2	D4W_GERMAN
	#define	LST_WORDING_2	LST_GERMAN
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == GERMAN)
	#define	D2W_WORDING_3	D2W_GERMAN
	#define	D4W_WORDING_3	D4W_GERMAN
	#define	LST_WORDING_3	LST_GERMAN
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* スペイン語の時 */
#if (WORDING_1 == SPANISH)
	#define	D2W_WORDING_1	D2W_SPANISH
	#define	D4W_WORDING_1	D4W_SPANISH
	#define	LST_WORDING_1	LST_SPANISH
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == SPANISH)
	#define	D2W_WORDING_2	D2W_SPANISH
	#define	D4W_WORDING_2	D4W_SPANISH
	#define	LST_WORDING_2	LST_SPANISH
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == SPANISH)
	#define	D2W_WORDING_3	D2W_SPANISH
	#define	D4W_WORDING_3	D4W_SPANISH
	#define	LST_WORDING_3	LST_SPANISH
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* イタリア語の時 */
#if (WORDING_1 == ITALIAN)
	#define	D2W_WORDING_1	D2W_ITALIAN
	#define	D4W_WORDING_1	D4W_ITALIAN
	#define	LST_WORDING_1	LST_ITALIAN
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == ITALIAN)
	#define	D2W_WORDING_2	D2W_ITALIAN
	#define	D4W_WORDING_2	D4W_ITALIAN
	#define	LST_WORDING_2	LST_ITALIAN
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == ITALIAN)
	#define	D2W_WORDING_3	D2W_ITALIAN
	#define	D4W_WORDING_3	D4W_ITALIAN
	#define	LST_WORDING_3	LST_ITALIAN
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* スウェーデン語の時 */
#if (WORDING_1 == SWEDISH)
	#define	D2W_WORDING_1	D2W_SWEDISH
	#define	D4W_WORDING_1	D4W_SWEDISH
	#define	LST_WORDING_1	LST_SWEDISH
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == SWEDISH)
	#define	D2W_WORDING_2	D2W_SWEDISH
	#define	D4W_WORDING_2	D4W_SWEDISH
	#define	LST_WORDING_2	LST_SWEDISH
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == SWEDISH)
	#define	D2W_WORDING_3	D2W_SWEDISH
	#define	D4W_WORDING_3	D4W_SWEDISH
	#define	LST_WORDING_3	LST_SWEDISH
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* 中国語の時 */
#if (WORDING_1 == CHINESE)
	#define	D2W_WORDING_1	D2W_CHINESE
	#define	D4W_WORDING_1	D4W_SWEDISH
	#define	LST_WORDING_1	LST_CHINESE
	#define	DATE_WORDING_1	USA_CLOCK_TYPE
#endif

/* デンマーク語の時 by K.Watanabe 1998/09/17 */
#if (WORDING_1 == DANISH)
	#define	D2W_WORDING_1	D2W_DANISH
	#define	LST_WORDING_1	LST_DANISH
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == DANISH)
	#define	D2W_WORDING_2	D2W_DANISH
	#define	LST_WORDING_2	LST_DANISH
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == DANISH)
	#define	D2W_WORDING_3	D2W_DANISH
	#define	LST_WORDING_3	LST_DANISH
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* オランダ語の時 by K.Watanabe 1998/09/17 */
#if (WORDING_1 == DUTCH)
	#define	D2W_WORDING_1	D2W_DUTCH
	#define	LST_WORDING_1	LST_DUTCH
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == DUTCH)
	#define	D2W_WORDING_2	D2W_DUTCH
	#define	LST_WORDING_2	LST_DUTCH
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == DUTCH)
	#define	D2W_WORDING_3	D2W_DUTCH
	#define	LST_WORDING_3	LST_DUTCH
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* ノルウェー語の時 by K.Watanabe 1998/09/17 */
#if (WORDING_1 == NORWEGIAN)
	#define	D2W_WORDING_1	D2W_NORWEGIAN
	#define	LST_WORDING_1	LST_NORWEGIAN
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == NORWEGIAN)
	#define	D2W_WORDING_2	D2W_NORWEGIAN
	#define	LST_WORDING_2	LST_NORWEGIAN
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == NORWEGIAN)
	#define	D2W_WORDING_3	D2W_NORWEGIAN
	#define	LST_WORDING_3	LST_NORWEGIAN
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* ポルトガル語の時 bythonda1999/12/21 */
#if (WORDING_1 == PORTUGUESE)
	#define	D2W_WORDING_1	D2W_PORTUGUESE
	#define	LST_WORDING_1	LST_PORTUGUESE
	#define	DATE_WORDING_1	EUR_CLOCK_TYPE
#endif
#if (WORDING_2 == PORTUGUESE)
	#define	D2W_WORDING_2	D2W_PORTUGUESE
	#define	LST_WORDING_2	LST_PORTUGUESE
	#define	DATE_WORDING_2	EUR_CLOCK_TYPE
#endif
#if (WORDING_3 == PORTUGUESE)
	#define	D2W_WORDING_3	D2W_PORTUGUESE
	#define	LST_WORDING_3	LST_PORTUGUESE
	#define	DATE_WORDING_3	EUR_CLOCK_TYPE
#endif

/* ダミーの時 */
#if (WORDING_3 == DUMMY)
	#define	D2W_WORDING_3	D2W_CHINESE
	#define	D4W_WORDING_3	D4W_DUMMY
	#define	LST_WORDING_3	LST_DUMMY
	#define	DATE_WORDING_3	JPN_CLOCK_TYPE
#endif

#endif	/* wording_h */
