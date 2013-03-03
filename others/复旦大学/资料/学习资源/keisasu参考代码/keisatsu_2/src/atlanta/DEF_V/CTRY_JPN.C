/* By Y.Suzuki 1996/10/16 */
/* Original File : jun\usr2:\src\atlanta\def_v\ctry_jpn.c */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\country.h"

CONST UBYTE CountryTable[COUNTRY_MAX][COUNTRY_DATA_MAX] = {
	{
		/*----------------------------------*/
		/*				JPN					*/
		/*----------------------------------*/
/*0*/	0
		|	 RELAY_TX				/* 	中継指示送信 			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* '95.04/26 By J.Miyazaki */
		|	 RELAYED_TX				/* 	中継配信送信 			*/
#endif															/* '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	 DB_POLING_RX			/* 	検索ポーリング受信 		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	 DB_POLING_TX			/* 	検索ポーリング送信 		*/
#endif
		|	 SECURE_TX				/* 	親展送信 				*/
		|	 SECURE_RX				/* 	親展受信 				*/
		|	 SECURE_DOC_HOLD_TIME	/* 	親展受信保持時間 		*/
		|	 PHONE_TYPE				/* 	電話回線セット 			*/
		,
/*1*/	0
		|	 PAUSE					/* 	ポーズ時間セット		*/
		|	 BELL_COUNT				/*	ベル回数セット			*/
		|	 CONNECTING_2TEL		/*	子電話接続セット		*/
		|	 REMOTE_DIAG			/*	リモート診断セット		*/
		|	 REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	 REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	 HOLD_MELODY			/*	保留メロディーセット	*/
		|	 CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	 TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	 SECURITY_TX			/*	パスワード送信			*/
		|	 BLOCK_JUNK_FAX 		/*	ダイレクトメール防止	*/
		|	 STAMP					/*	済みスタンプセット		*/
		|	 MESSAGE_TX				/*	メッセージセット		*/
		|	 RS232C					/*	ＲＳ２３２Ｃセット		*/
		|	 DIALIN					/*	ダイヤルインセット		*/
		|	 DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	 COST					/*	料金管理セット			*/
		|	 BATCH_TX				/*	一括送信セット			*/
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* (受領証機能を削除する) Modify by SMuratec L.Z.W 2003/10/30 */
		|	 RCR					/*	受領証					*/
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		|	 NONE_PAPER_RX			/*	代行受信				*/
		|	 REMOTE_RX				/*	転送受信				*/
		|	 TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	 ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	 HOLD_KEY_ENABLE		/*	保留キー				*/
		,
/*4*/	0
		|	 REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	 HOOK_KEY_ENABLE		/*	モニタキー				*/
		|	 OFFHOOK_TEL			/*	オフフック状態での電話	*/
		|	 PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	 TONE_KEY_ENABLE		/*	シグナルチェンジキー	*/
		|	 FIRST_DT_DETECT		/*	第1発信音検出			*/
		|	 SECOND_DT_DETECT		/*	第2発信音検出			*/
		|	 CATCH_PHONE			/*	キャッチホン対応		*/
		,
/*5*/	0
		&	 ~REMOTE_TAKEOUT		/*	リモートＦＡＸ取出し	*/
		&	 ~BRANCH_RX				/*	ブランチ転送			*/
		&	 ~POCKET_BELL			/*	ポケベル呼出			*/
		&	 ~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
#if (PRO_MAKER == FX)
/*7*/	4							/*	ポーズ時間最小値		*/
#endif
#if (PRO_MAKER == MML)
/*7*/	5							/*	ポーズ時間最小値		*/
#endif
		,
/*8*/	10							/*	ポーズ時間最大値		*/
		,
#if defined(POPLAR_F)
 #if defined(JP1)	/* V740 */
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
 #else				/* L400(A) */
/*9*/	0							/*	呼出ベル回数最小値		*/
		,
 #endif
#elif defined(POPLAR_N)	/* ポプラＬ（ＮＴＴ仕様） by K.Watanabe 1998/03/16 */
/*9*/	0							/*	呼出ベル回数最小値		*/
		,
#elif defined(HINOKI2) || defined (HINOKI3) || defined (SATSUKI2) || defined (STOCKHM2)
 #if defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 *//* (PRO_NORING_TEL1_DETACHABLE == ENABLE) */
/*9*/	0							/*	呼出ベル回数最小値		*//* Add By O.Kimoto 2002/09/27 */
		,
 #else
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
 #endif
#else
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
#endif

#if (PRO_RING_10_COUNT == ENABLE)	/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
/*10*/	10							/*	呼出ベル回数最大値		*/
#else
/*10*/	9							/*	呼出ベル回数最大値		*/
#endif
		,
#if (PRO_NEW_JATE == ENABLE)	/*  By O.Kimoto 1998/09/04 *//* defined(SAKAKI)	1998/08/21 By M.Kuwahara */
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	15							/*	リダイヤル回数最大値	*/
		,
/*13*/	0							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
#else
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	10							/*	リダイヤル回数最大値	*/
		,
/*13*/	1							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
#endif
/*15*/
#if (PRO_MODEM == ORANGE3)
 #if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* ポプラＬ／ポプラＮ送出レベル変更(JPNのみ) */
		14							/* 	送出レベルの初期値		*//* 1998/03/12 Ｅ設(福間氏)からの依頼 By T.Yamaguchi */
 #else
		13							/* 	送出レベルの初期値		*//* 1994/11/11 電子(曽根氏)からの依頼 By H.Y */
 #endif
#endif
#if (PRO_MODEM == R288F)
  #if (PRO_NEW_JATE == ENABLE)	/*  1998/10/06 H.Yoshikawa */
		TX_LEVEL_INITIAL			/* 	送出レベルの初期値（-8.9dBm) *//* 1998/10/23 H.Yoshikawa */
  #else
		14							/* 	送出レベルの初期値		*/
  #endif
#endif
#if (PRO_MODEM == MN195006)
  #if (PRO_NEW_JATE == ENABLE)	/*  1998/10/06 H.Yoshikawa */
		TX_LEVEL_INITIAL			/* 	送出レベルの初期値（-8.9dBm) *//* 1998/10/23 H.Yoshikawa */
  #else
		14							/* 	送出レベルの初期値		*/
  #endif
#endif
		,
/*16*/	1							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	 INIT_PHONE_TYPE_20PPS	/*	回線設定の初期値		*/
		|	 INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	 WORDING_NUMBER_MAX_2 	/*	マルチワーディング数	*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		,
#if (PRO_MAKER == FX)
/*18*/	4							/*	ポーズ時間の初期値		*/
#endif
#if (PRO_MAKER == MML)
/*18*/	5							/*	ポーズ時間の初期値		*/
#endif
		,
#if defined (KEISATSU) /* 警察FAX 05/09/30 石橋正和 */
/*19*/	1							/*	呼出ベル回数の初期値	*/
#else
/*19*/	2							/*	呼出ベル回数の初期値	*/
#endif
		,
#if (PRO_MAKER == FX)
/*20*/	5							/*	リダイヤル回数の初期値	*/
#endif
#if (PRO_MAKER == MML)
 /* NTT仕様はF-351以降の機種ではリダイヤル回数初期値を3回とします */
 #if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/10 */
/*20*/	3
 #else
  #if (PRO_NEW_JATE == ENABLE)	/* 1998/10/02 H.Yoshikawa */
   /* Modify start by SMuratec 夏 2004/7/9 */
   #if defined(STOCKHM2) || defined(HINOKI3)	/* by K.Watanabe 2004/10/12 */
	#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
/*20*/   3
	#else
/*20*/   5
	#endif
   #else
/*20*/	15
   #endif
  #else
/*20*/	10							/*	リダイヤル回数の初期値	*/
  #endif
 #endif
#endif
		,
/*21*/	1							/*	リダイヤル間隔の初期値	*/
		,
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/12 */
/*22*/	5							/*	prefixポーズ時間最小値 *//* Add by SMuratec 夏 2004/7/12 */
#else
/*22*/	NOT_USED					/*	未使用					*/
#endif
		,
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/12 */
/*23*/	10							/*	prefixポーズ時間最大値 *//* Add by SMuratec 夏 2004/7/12 */
#else
/*23*/	NOT_USED					/*	未使用					*/
#endif
		,
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/12 */
/*24*/	5							/*	prefixポーズ時間初期値 *//* Add by SMuratec 夏 2004/7/12 */
#else		
/*24*/	NOT_USED					/*	未使用					*/
#endif
	},
	{
		/*----------------------------------*/
		/*				JPN					*/
		/*----------------------------------*/
/*0*/	0
		|	 RELAY_TX				/* 	中継指示送信 			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* '95.04/26 By J.Miyazaki */
		|	 RELAYED_TX				/* 	中継配信送信 			*/
#endif															/* '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	 DB_POLING_RX			/* 	検索ポーリング受信 		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	 DB_POLING_TX			/* 	検索ポーリング送信 		*/
#endif
		|	 SECURE_TX				/* 	親展送信 				*/
		|	 SECURE_RX				/* 	親展受信 				*/
		|	 SECURE_DOC_HOLD_TIME	/* 	親展受信保持時間 		*/
		|	 PHONE_TYPE				/* 	電話回線セット 			*/
		,
/*1*/	0
		|	 PAUSE					/* 	ポーズ時間セット		*/
		|	 BELL_COUNT				/*	ベル回数セット			*/
		|	 CONNECTING_2TEL		/*	子電話接続セット		*/
		|	 REMOTE_DIAG			/*	リモート診断セット		*/
		|	 REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	 REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	 HOLD_MELODY			/*	保留メロディーセット	*/
		|	 CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	 TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	 SECURITY_TX			/*	パスワード送信			*/
		|	 BLOCK_JUNK_FAX 		/*	ダイレクトメール防止	*/
		|	 STAMP					/*	済みスタンプセット		*/
		|	 MESSAGE_TX				/*	メッセージセット		*/
		|	 RS232C					/*	ＲＳ２３２Ｃセット		*/
		|	 DIALIN					/*	ダイヤルインセット		*/
		|	 DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	 COST					/*	料金管理セット			*/
		|	 BATCH_TX				/*	一括送信セット			*/
#if (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) /* (受領証機能を削除する) Modify by SMuratec L.Z.W 2003/10/30 */
		|	 RCR					/*	受領証					*/
#endif /* End of (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
		|	 NONE_PAPER_RX			/*	代行受信				*/
		|	 REMOTE_RX				/*	転送受信				*/
		|	 TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	 ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		&	 HOLD_KEY_ENABLE		/*	保留キー				*/
		,
/*4*/	0
		|	 REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	 HOOK_KEY_ENABLE		/*	モニタキー				*/
		|	 OFFHOOK_TEL			/*	オフフック状態での電話	*/
		|	 PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	 TONE_KEY_ENABLE		/*	シグナルチェンジキー	*/
		|	 FIRST_DT_DETECT		/*	第1発信音検出			*/
		|	 SECOND_DT_DETECT		/*	第2発信音検出			*/
		|	 CATCH_PHONE			/*	キャッチホン対応		*/
		,
/*5*/	0
		&	 ~REMOTE_TAKEOUT		/*	リモートＦＡＸ取出し	*/
		&	 ~BRANCH_RX				/*	ブランチ転送			*/
		&	 ~POCKET_BELL			/*	ポケベル呼出			*/
		&	 ~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	10							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	9							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	10							/*	リダイヤル回数最大値	*/
		,
/*13*/	1							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		14							/* 	送出レベルの初期値		*/
#endif
#if (PRO_MODEM == R288F)
		14							/* 	送出レベルの初期値		*/
#endif
#if (PRO_MODEM == MN195006)
		14							/* 	送出レベルの初期値		*/
#endif
		,
/*16*/	1							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	 INIT_PHONE_TYPE_20PPS	/*	回線設定の初期値		*/
		|	 INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	 WORDING_NUMBER_MAX_2 	/*	マルチワーディング数	*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		|	 NOT_USED				/*	未使用					*/
		,
#if (PRO_MAKER == FX)
/*18*/	4							/*	ポーズ時間の初期値		*/
#endif
#if (PRO_MAKER == MML)
/*18*/	5							/*	ポーズ時間の初期値		*/
#endif
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
#if (PRO_MAKER == FX)
/*20*/	5							/*	リダイヤル回数の初期値	*/
#endif
#if (PRO_MAKER == MML)
/*20*/	10							/*	リダイヤル回数の初期値	*/
#endif
		,
/*21*/	1							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	}
};


/*--------------------------------------*/
/* オプションモデムボード用国別テーブル */
/*--------------------------------------*/
CONST UBYTE CountryOptionTable[COUNTRY_MAX][COUNTRY_OPTION_DATA_MAX] = {
	{
		/*----------------------------------*/
		/*	0			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/	/* <- 13 M.Tachibana 1998/10/27 */
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/	/* <- 3  M.Tachibana 1998/10/27 */
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	1			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	2			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	3			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	4			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	5			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	6			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	7			JPN					*/
		/*----------------------------------*/
#if defined(POPLAR_H) && defined(JP0)/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/05*/
/*0*/	8							/* 送出レベル(0～15)		*/
#else
/*0*/	15							/* 送出レベル(0～15)		*/
#endif
		,
/*1*/	11							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	}
};


