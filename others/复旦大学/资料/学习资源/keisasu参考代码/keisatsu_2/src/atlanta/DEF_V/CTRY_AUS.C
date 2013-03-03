/* By S.K Spe.21,1995 */
/****************************************************************/
/* Ｗａｒｎｉｎｇ ！！！										*/
/* ここのテーブルを変更するときは								*/
/* ＦＥＭや取説に修正をかける必要があるので						*/
/* 必ず、“小原”及び“関野”まで報告してください				*/
/****************************************************************/

const unsigned char far CountryTable[COUNTRY_MAX][COUNTRY_DATA_MAX] = {
	{
		/*----------------------------------*/
		/*				AUS					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		&	~CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		&	~HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/	/* |→&,~  BY M.HARADA '95.07.04 &->| 1996/11/13 By N.Sakamoto */
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		|	STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		&	~COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		&	~REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	10							/*	ポーズ時間最大値		*/
		,
/*9*/	2							/*	呼出ベル回数最小値		*//* PTTより,ﾍﾞﾙ1回着信は不可とのこと 1996/08/27 by H.Yagi */
		,
/*10*/	9							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		11							/*	トーンアッテネータの初期値 */ /* 1996/08/29 by H,Yagi */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
		/*----------------------------------*/
		/*				THA					*//* add by M.HARADA 96.09.30 */
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		&	~CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		&	~HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/	/* |→&,~  BY M.HARADA '95.07.04 &->| 1996/11/13 By N.Sakamoto */
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		|	STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		&	~COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		&	~REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	3							/*	ポーズ時間最小値		*/
		,
/*8*/	10							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*//* THA 2-----> 1 1996/11/01 By N.Sakamoto */ /* PTTより,ﾍﾞﾙ1回着信は不可とのこと 1996/08/27 by H.Yagi */
		,
/*10*/	9							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		11							/*	トーンアッテネータの初期値 */ /* 1996/08/29 by H,Yagi */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	3							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
		/*----------------------------------*/					/*  1996/10/21 By N.Sakamoto CTRY_SGP.Cより移動 */
		/*				SGP					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/* 	中継指示送信 			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/* 	中継配信送信 			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/* 	検索ポーリング受信 		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/* 	検索ポーリング送信 		*/
#endif
		|	SECURE_TX				/* 	親展送信 				*/
		|	SECURE_RX				/* 	親展受信 				*/
		|	SECURE_DOC_HOLD_TIME	/* 	親展受信保持時間 		*/
		|	PHONE_TYPE				/* 	電話回線セット 			*/
		,
/*1*/	0
		|	PAUSE					/* 	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		&	~CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		&	~HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/	/* |→&,~  BY M.HARADA '95.07.04 & -> | By 1996/11/13 By N.Sakamoto */
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX 			/*	ダイレクトメール防止	*/
		|	STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		&	~COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		&	~REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	3							/*	ポーズ時間最小値		*//* 5 -> 3  1996/09/04 by H.Yagi */
		,
/*8*/	10							/*	ポーズ時間最大値		*/	
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	9							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		12							/* 	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		8							/* 	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3 	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	3							/*	ポーズ時間の初期値		*//* 5 -> 3  1996/09/04 by H.Yagi */
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
/*============================================================== coment by M.HARADA 96.09.30 ======*/
#if (0)
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
/*	@endif		1996/10/21 By N.Sakamoto */
/*==============================================================================*/
		/*----------------------------------*/
		/*				?2?					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
#endif		/* 1996/10/21 By N.Sakamoto */
/*========================================================================================*/
		/*----------------------------------*/
		/*				?3?					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
		/*----------------------------------*/
		/*				?4?					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
		/*----------------------------------*/
		/*				?5?					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
		/*----------------------------------*/
		/*				?6?					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
		,
/*22*/	NOT_USED					/*	未使用					*/
		,
/*23*/	NOT_USED					/*	未使用					*/
		,
/*24*/	NOT_USED					/*	未使用					*/
	},
	{
		/*----------------------------------*/
		/*				?7?					*/
		/*----------------------------------*/
/*0*/	0
		|	RELAY_TX				/*	中継指示送信			*/
#if (PRO_RELAY_BROADCAST == ENABLE)								/* Add '95.04/26 By J.Miyazaki */
		|	RELAYED_TX				/*	中継配信送信			*/
#endif															/* Add '95.04/26 By J.Miyazaki */
#if (PRO_DB_POLLING_RX == ENABLE)
		|	DB_POLING_RX			/*	検索ポーリング受信		*/
#endif
#if (PRO_DB_POLLING_TX == ENABLE)
		|	DB_POLING_TX			/*	検索ポーリング送信		*/
#endif
		|	SECURE_TX				/*	親展送信				*/
		|	SECURE_RX				/*	親展受信				*/
		|	SECURE_DOC_HOLD_TIME	/*	親展受信保持時間		*/
		|	PHONE_TYPE				/*	電話回線セット			*/
		,
/*1*/	0
		|	PAUSE					/*	ポーズ時間セット		*/
		|	BELL_COUNT				/*	ベル回数セット			*/
		|	CONNECTING_2TEL			/*	子電話接続セット		*/
		|	REMOTE_DIAG				/*	リモート診断セット		*/
		|	REDIAL_NUMBER			/*	再ダイヤル回数セット	*/
		|	REDIALINTERVAL			/*	再ダイヤル間隔セット	*/
		|	HOLD_MELODY				/*	保留メロディーセット	*/
		|	CLOSED_NETWORK			/*	閉域通信セット			*/
		,
/*2*/	0
		|	TELFAX_PRIMARY			/*	電話／ファクス優先セット*/
		|	SECURITY_TX				/*	パスワード送信			*/
		|	BLOCK_JUNK_FAX			/*	ダイレクトメール防止	*/
		&	~STAMP					/*	済みスタンプセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	MESSAGE_TX				/*	メッセージセット		*/
		|	RS232C					/*	ＲＳ２３２Ｃセット		*/
		&	~DIALIN					/*	ダイヤルインセット		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	DEPARTMENT				/*	部門管理セット			*/
		,
/*3*/	0
		|	COST					/*	料金管理セット			*/
		|	BATCH_TX				/*	一括送信セット			*/
		|	RCR						/*	受領証					*/
		|	NONE_PAPER_RX			/*	代行受信				*/
		|	REMOTE_RX				/*	転送受信				*/
		|	TELFAX_READY			/*	電話/FAX待機			*/
#if (PRO_BUILTIN_TAD == DISABLE)
		|	ANSFAX_READY			/*	留守/FAX待機			*/
#endif
		|	HOLD_KEY_ENABLE			/*	保留キー				*/
		,
/*4*/	0
		|	REDIAL_KEY_ENABLE		/*	リダイヤルキー			*/
		|	HOOK_KEY_ENABLE			/*	モニタキー				*/
		|	OFFHOOK_TEL				/*	オフフック状態での電話	*/
		|	PAUSE_KEY_ENABLE		/*	ポーズキー				*/
		|	TONE_KEY_ENABLE			/*	シグナルチェンジキー	*/
		|	FIRST_DT_DETECT			/*	第1発信音検出			*/
		|	SECOND_DT_DETECT		/*	第2発信音検出			*/	/* ~ -> Non By J.Miyazaki '95.04/26 */
		&	~CATCH_PHONE			/*	キャッチホン対応		*/	/* | -> & By J.Miyazaki '95.04/26 */
		,
/*5*/	0
		|	REMOTE_TAKEOUT			/*	リモートＦＡＸ取出し	*/
		&	~BRANCH_RX				/*	ブランチ転送			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~POCKET_BELL			/*	ポケベル呼出			*/	/* | -> & By J.Miyazaki '95.04/26 */
		&	~MONITOR_ON_TO_DIS		/*	DIS受信までモニタON		*/	/* | -> & By J.Miyazaki '95.04/26 */
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*6*/	99							/*	最大ポーズ動作回数		*/
		,
/*7*/	5							/*	ポーズ時間最小値		*/
		,
/*8*/	99							/*	ポーズ時間最大値		*/
		,
/*9*/	1							/*	呼出ベル回数最小値		*/
		,
/*10*/	10							/*	呼出ベル回数最大値		*/
		,
/*11*/	2							/*	リダイヤル回数最小値	*/
		,
/*12*/	5							/*	リダイヤル回数最大値	*/
		,
/*13*/	3							/*	リダイヤル間隔最小値	*/
		,
/*14*/	5							/*	リダイヤル間隔最大値	*/
		,
/*15*/
#if (PRO_MODEM == ORANGE3)
		13							/*	トーンアッテネータの初期値 */
#endif
#if (PRO_MODEM == R288F)
		12							/*	トーンアッテネータの初期値 */
#endif
		,
/*16*/	3							/*	親展受信保持期間の初期値*/
		,
/*17*/	0
		|	INIT_PHONE_TYPE_TONE	/*	回線設定の初期値		*/
		|	INIT_WORDING_NUMBER_0	/*	ワーディングの初期値	*/
		|	WORDING_NUMBER_MAX_3	/*	マルチワーディング数	*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		|	NOT_USED				/*	未使用					*/
		,
/*18*/	5							/*	ポーズ時間の初期値		*/
		,
/*19*/	2							/*	呼出ベル回数の初期値	*/
		,
/*20*/	2							/*	リダイヤル回数の初期値	*/
		,
/*21*/	3							/*	リダイヤル間隔の初期値	*/
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
const unsigned char far CountryOptionTable[COUNTRY_MAX][COUNTRY_OPTION_DATA_MAX] = {
	{
		/*----------------------------------*/
		/*	0			AUS					*/
		/*----------------------------------*/
/*0*/	8							/* 送出レベル(0～15)		*//* 97.05.27 BY M.H. */
		,
/*1*/	10							/* ＤＴＭＦ送出レベル(0～15)*//* 97.05.27 BY M.H. */
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	1			THA					*/
		/*----------------------------------*/
/*0*/	11							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	2			SGP					*/
		/*----------------------------------*/
/*0*/	12							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	3			???					*/
		/*----------------------------------*/
/*0*/	13							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	4			???					*/
		/*----------------------------------*/
/*0*/	13							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	5			???					*/
		/*----------------------------------*/
/*0*/	13							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	6			???					*/
		/*----------------------------------*/
/*0*/	13							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	},
	{
		/*----------------------------------*/
		/*	7			???					*/
		/*----------------------------------*/
/*0*/	13							/* 送出レベル(0～15)		*/
		,
/*1*/	3							/* ＤＴＭＦ送出レベル(0～15)*/
		,
/*2*/	NOT_USED					/* 未使用					*/
		,
/*3*/	NOT_USED					/* 未使用					*/
		,
/*4*/	NOT_USED					/* 未使用					*/
	}
};


