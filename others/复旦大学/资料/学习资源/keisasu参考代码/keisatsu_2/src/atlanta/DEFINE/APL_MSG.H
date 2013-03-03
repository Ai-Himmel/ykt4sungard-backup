#ifndef apl_msg_h
	#define apl_msg_h

	/*-------------------------------------------------------------------------
	**	FROM_TIM_INT
	*/
	#define		FROM_TIM_INT				1

	/*-------------------------------------------------------------------------
	**	FROM_MAIN
	*/
	#define		FROM_MAIN					2	/* NCU_MSG.Hの定義と被らないよう2で固定して下さい。By N.S. '94,01,08 */
		#define		MSG_EXIT					0
		#define		MSG_TEL_FROM_MAIN			1
		/* Add By O.Kimoto 1997/07/22 */
		#define		MSG_ELAPSE_BUZZER			2	/* 保留：1分経過ブザーリクエスト */
		#define		MSG_TIMEUP_BUZZER			3	/* 保留：5分経過ブザーリクエスト */
		#define		MSG_DEPARTMENT_OPERATION	4	/* 部門管理リストプリントオペレーション起動 */
		#define		MSG_UPDATE_DOC_SIZE			5	/* ＴＥＬ／ＯＰＥ時の原稿サイズ更新用 */
		#define		MSG_CHANGE_READY_MODE		6	/* 待機状態自動切替メッセージ */
		#define		MSG_BUZZER_DOC				7	/* 原稿挿入時のアック音 by T.Soneoka 1997/04/07 */
		#define		MSG_CL1_DIALIN_EXIT			8	/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/14 */
		#define		MSG_SHIREI_ON				9
#endif		/* End of (defined (KEISATSU)) */

		/**	FipTask起動ﾒｯｾｰｼﾞ	By Hisanori Tomita	**/
		#define	FIP_TEST_CMD			100		/* ｻｰﾋﾞｽﾌｧﾝｸｼｮﾝ RS232Cﾃｽﾄ要求	*/
		#define	FIP_RCV_REQ				101		/* FIP受信要求	*/
		#define	FIP_SECURE_RCV_REQ		102		/* FIP親展受信要求	*/
												/* MailBoxNo.はSubMessage1にｾｯﾄ	*/
		#define	FIP_STOREDOC_CONF		103		/* 原稿蓄積完了通知	*/
		#define	FIP_DOCPRINT_CONF		104		/* 蓄積原稿ﾌﾟﾘﾝﾄ完了通知	*/
		#define	FIP_SEND_CONF			105		/* 蓄積原稿送信完了通知	*/
		#define	FIP_POLLING_CONF		106		/* ﾎﾟｰﾘﾝｸﾞ受信完了通知	*//* Aug,26'93 Bamboo! ^^; */

		#define	MSG_FIP_STOREDOC_ACCEPT	200
		#define	MSG_FIP_STOREDOC_REJECT	201
		#define	MSG_FIP_DOCPRINT_ACCEPT	202
		#define	MSG_FIP_DOCPRINT_REJECT	203
		#define	MSG_FIP_SEND_ACCEPT		204
		#define	MSG_FIP_SEND_REJECT		205
		#define	MSG_FIP_POLLING_ACCEPT	206
		#define	MSG_FIP_POLLING_REJECT	207
		#define	MSG_FIP_RS232C_TEST_END	208		/* Add By M.T 1995/03/27 */

		/* CLASS 1起動ﾒｯｾｰｼﾞ	By Y.Tanimoto	*/
		#define	CL1_DETECT_RING				210	/* CIを1波検出した					*/
		#define	CL1_DETECT_RING_FNET		211	/* F網の着信要求あり				*/
		#define	CL1_DETECT_RING_DIALIN		212	/* ﾀﾞｲﾔﾙｲﾝの着信要求あり			*/
		#define	CL1_ONLINE_ACCEPT			213	/* CLASS1回線接続が受け入れられた	*/
		#define	CL1_ONLINE_REJECT			214	/* CLASS1回線接続が拒否された		*/
		#define	CL1_RCV_ACCEPT				215	/* CLASS1受信の実行が受け入れられた	*/
		#define	CL1_RCV_REJECT				216	/* CLASS1受信の実行が拒否された		*/
		#define	CL1_PRINT_ACCEPT			217	/* ﾛｰｶﾙﾌﾟﾘﾝﾄの実行が受け入れられた	*/
		#define	CL1_PRINT_REJECT			218	/* ﾛｰｶﾙﾌﾟﾘﾝﾄの実行が拒否された		*/
		#define	CL1_SCAN_REQ				219	/* ﾛｰｶﾙｽｷｬﾝの実行が要求された		*/
		#define	CL1_SCAN_MEM_REQ			220	/* ﾛｰｶﾙｽｷｬﾝ(ﾒﾓﾘ)の実行が要求された	*/
		#define	CL1_TEST_CMD				221	/* RS232Cのﾃｽﾄが要求された			*/
		#define CL1_CI_TIMEUP				222	/* 呼出しに応答する前にCIが消滅した	*/
		#define CL1_RS232C_TEST_END			223	/* RS232Cﾃｽﾄ終了(ｵﾍﾟﾚｰｼｮﾝに通知)	*/
		#define	CL1_INIT_REQ				224	/* Auto Initialize 起動要求			*/
		#define	CL1_INIT_END				225	/* Auto Initialize 終了 ｵﾍﾟﾚｰｼｮﾝに通知　*/
		#define	CL1_DETECT_OFF_HOOK			226	/* Class1呼び出し中にOFF HOOK		*/
		#define	CL1_DIALIN_DETECT_DSE		227	/* Class1ダイヤルイン呼び出し中に極反検出 PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
		#define	CL1_FNET_TIMEUP				228	/* Class1 1300Hz検出タイムアップ PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
		#define	CL1_SCAN_SCANNER		0
		#define	CL1_SCAN_MEMORY			1

		/* ＰＣプリント用	By J.Miyazaki 1996/09/21 */
		#define	DPR_PCR_TESTPRINT_OK		230
		#define	DPR_PCR_TESTPRINT_NG		231
		/* Class1着信条件の仕様変更 （ＡＮＺＵより移植 S.Fukui June.19,1998) */
		#define	CL1_MANUAL_RX_REQ			232	/* Class1手動受信起動 */
		#define	CL1_MANUAL_RX_RING			233	/* Class1手動受信	*/ /* 必要 ? */
		#define CL1_CNG_RX_REQ				234 /* Class1ＣＮＧ検出時自動受信起動 */
		#define CL1_NON_DIAL_IN_RX_REQ		235 /* Class1ダイヤルイン設定時の非ダイヤルイン呼に対するＰＣ受信 S.Fukui */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/30 */
		/*　InternetFAXﾒｲﾝﾀｽｸ起動用メッセージ　*/
		#define	INF_EXEC_MAILCOM			240	/*　メール通信実行要求		*/
		#define	INF_TEST_FUNCTION			241	/*　テスト実行要求			*/
		#define	INF_TEST_END				242	/*　テストファンクション終了(OPRへ通知)	*/
		#define	INF_ERASE_ONE_ACCOUNT_DATA	243	/*　特定のアカウント消去要求　*/
		#define	INF_ERASE_ALL_ACCOUNT_DATA	244	/*　全アカウント消去要求　*/
		#define	INF_INIT_ENGINE_BOARD		245	/*　ROM交換時のエンジンボードの初期化　*/
		#define	INF_TTL_TEST_MODE			246 /*TTL Serial基板ﾃｽﾄﾌｧﾝｸｼｮﾝ*/
#endif

		/* リストプリント用 */
		/* チェックメッセージ等は、ストップキーにて停止しては困るので、その判断をリストを追加する度に
		** プログラムを変更しなくて済むように、定義の順番を変更します
		** 注）新規にリストを追加する場合は、追加する場所に注意すること
		** by K.Watanabe 1997/09/25
		*/

		/* ストップキーにて停止可能なリスト（オペレーションから起動されるリスト） */
		/* 通常の機能メニューから起動されるリスト */
		#define	LST_ONETOUCHDIAL_LIST			 0	/* ワンタッチダイヤルリスト							*/
		#define	LST_SPEEDDIAL_LIST				 1	/* 短縮ダイヤルリスト								*/
		#define	LST_PROGRAM_LIST				 2	/* プログラムワンタッチリスト						*/
		#define	LST_MAILBOX_LIST				 3	/* 親展者リスト										*/
		#define	LST_RESERVECMD_LIST				 4	/* 通信予約リスト									*/
		#define	LST_JOURNAL_LIST				 5	/* 通信管理レポート									*/
		#define	LST_GROUP_LIST					 6	/* グループリスト									*/
		#define	LST_PARAMETER_LIST				 7	/* 機器設定リスト									*/
		#define	LST_BLOCK_JUNK_LIST				 8	/* ジャンクメール防止ダイヤルリスト					*/
		#define	LST_COVERPAGE_LIST				 9	/* カバーページプリント								*/
		#define	LST_BATCHTXBOX_LIST				10	/* 一括送信ＢＯＸリスト								*/
		#define	LST_BATCHTXDOC_LIST				11	/* 一括送信原稿リスト								*/
		#define	LST_F_CODE_BOX_LIST				12	/* Ｆコードボックスリスト							*/
		#define	LST_F_CODE_DOC_LIST				13	/* Ｆコード蓄積原稿リスト							*/
		#define	LST_SCRAMBLE_KEY				14	/* 暗号化キーリスト									*/
		#define	LST_SCRAMBLE_KEY_LIST			15	/* 暗号化キーブックリスト							*/
		#define	LST_TTI_LIST					16	/* 発信元リスト										*/
		#define	LST_MULTIPROGRAM_LIST			17	/* マルチプログラムリスト							*/
		#define	LST_COSTTABLE_LIST				18	/* 料金表 											*/
		#define	LST_DEPARTDATACODE_LIST			19	/* 部門管理リスト									*/
		#define	LST_DEPARTMANAGE_LIST			19	/* 管理料金管理リスト added by thonda 1997/11/27	*/
		/*　インターネットＦＡＸ用に以下を追加
		**  1998/03/10  by Y.Tanimoto
		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		#define	LST_INF_ADDRESS_LIST			20
		#define	LST_INF_GROUP_LIST				21
		#define	LST_INF_SETTING_LIST			22
		#define	LST_INF_JOURNAL_LIST			23
		#define	LST_INF_MAILCOM_LIST			24
		#define	LST_INF_SECURE_NOTICE			25
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)
		#define LST_ND_LIST						26	/* ナンバーディスプレイダイヤルリスト				*/	/* 1998/06/15 By M.Kuwahara */
		#define LST_INF_ND_LIST					27	/* ナンバーディスプレイ着信履歴						*/	/* 1998/06/29 By M.Kuwahara */
#endif
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/15 Add By M.Kuwahara */
		#define LST_KEYMACRO_LIST				28	/* キーマクロタイトルリスト							*/
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/15 Add By M.Kuwahara */
		#define LST_WARP_LIST					29	/* ワープ機能リスト									*/
#endif
#if (PRO_SGP_TEST_ROM == ENABLE) /* by S.Wang 98/07/24 */
		#define LST_SGP_REPORT_LIST				30	/* シンガポール市場調査レポート						*/
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/22 */
		#define	LST_AUTO_ALL_JOURNAL			31	/* 通信管理記録自動プリント							*/
		#define	LST_DAILY_REPORT				32	/* 通信管理記録日報プリント							*/
#endif

		/* サービスファンクション等から起動されるリスト */
		#define	LST_T30MONITOR					50	/* Ｔ３０モニタ										*/
		#define	LST_FUNCTION_LIST				51	/* 機能リスト										*/
		#define	LST_PATTERN_PRINT				52	/* パターンプリント									*/
		#define	LST_MEM_SW						53	/* メモリスイッチ									*/
		#define	LST_FACT_MENU					54	/* 工場ファンクションリスト							*/
		#define	LST_SERVICE_LIST				55	/* サービスレポート									*/
		#define	LST_MEMORY_DUMP					56	/* メモリダンプリスト								*/
		#define	LST_CL1_ONLINE_MONITOR			57	/* クラス１オンラインモニタ－						*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/22 Eguchi */
		#define	LST_INF_MONITOR					58
#endif
#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
		#define LST_COM_RESULT_LIST				59	/* 通信結果プリント */
#endif
 #if defined(SAKAKI) && defined(JP0)/* 2002/08/26 By M.Maeda */
		#define LST_JOURNAL_TX_LIST				60	/* 通信結果プリント */
		#define LST_JOURNAL_RX_LIST				61	/* 通信結果プリント */
#endif

		/* 注）これより前に追加したリストはストップキーにて停止可能です（起動される場所で分けてあります） */
		#define	LST_STOP_ENABLE_LINE			99	/* ストップキーにて停止可能かの判断で使用			*/

		/* ストップキーにて停止不可能なリスト（チェックメッセージ，受信・消去通知等） */
		#define	LST_TXCONF_REPORT				100	/* 送信証											*/
		#define	LST_MONITOR_REPORT				101	/* モニターレポート（ＯＮの原稿無し時）				*/
		#define	LST_MANUAL_TXCONF_REPORT		102	/* 手動送信送信証									*/
		#define	LST_TXJOURNAL_LIST				103	/* 通信管理レポート（送信）							*/
		#define	LST_RXJOURNAL_LIST				104	/* 通信管理レポート（受信）							*/
		#define	LST_DOC_CHECKMSG				105	/* チェックメッセージＡ（原稿添付）					*/
		#define	LST_COMMERR_CHECKMSG			106	/* チェックメッセージＢ（交信エラー）				*/
		#define	LST_MRYOVER_CHECKMSG			107	/* チェックメッセージＣ（メモリオーバー）			*/
		#define	LST_MRYINIT_CHECKMSG			108	/* チェックメッセージＤ（メモリイニシャル）			*/
		#define	LST_MNLERR_CHECKMSG				109	/* チェックメッセージＥ（手動送信エラー）			*/
		#define	LST_RXMRYOVER_CHECKMSG			110	/* チェックメッセージＦ（受信メモリオーバー）		*/
		#define	LST_CATCHPHONE_CHKMSG			111	/* チェックメッセージＧ（キャッチホン）				*/
		#define	LST_LOSTPAGE_CHKMSG				112	/* チェックメッセージＩ（受信ページ紛失）			*/
		#define	LST_COMMERR_BATCH_CHECKMSG		113	/* 一括送信チェックメッセージＢ（交信エラー）		*/
		#define	LST_SEC_RX_MEMOVER_CHKMSG		114	/* セキュリティ受信モード中の受信メモリーオーバー	*/
		#define	LST_POWEROFF_NOTICE				115	/* 停電検出通知										*/
		#define	LST_DELRESERVECMD_NOTICE		116	/* 通信予約消去通知									*/
		#define	LST_DELMEMORYRCV_NOTICE			117	/* 代行受信消去通知									*/
		#define	LST_DELCONTPOLLCMD_NOTICE		118	/* 連続ポーリングコマンド消去通知					*/
		#define	LST_SECURERCV_NOTICE			119	/* 親展受信通知										*/
		#define	LST_DELSECURE_NOTICE			120	/* 親展受信消去通知									*/
		#define	LST_DELPOLLING_NOTICE			121	/* ポーリング原稿消去通知							*/
		#define	LST_DELBATCHTXDOC_NOTICE		122	/* 一括送信原稿消去通知								*/
		#define	LST_FCODE_BOXRCV_NOTICE			123	/* Ｆコード受信通知									*/
		#define	LST_DEL_FCODE_BOX_DOC_NOTICE	124	/* Ｆコード原稿消去通知								*/
		#define	LST_SCRAMBLE_RCV_NOTICE			125	/* 暗号化受信通知									*/
		#define	LST_DEL_SCRAMBLE_RX_NOTICE		126	/* 暗号化受信原稿消去通知							*/
		#define	LST_DEL_SCRAMBLEING_DOC_NOTICE	127	/* 暗号化中原稿消去通知								*/
		#define	LST_DEL_DESCRAMBLE_DOC_NOTICE	128	/* 暗号化復元原稿消去通知							*/
		#define LST_PCMRYOVER_CHECKMSG			129	/* ＰＣプリンタメモリオーバー						*/
		#define	LST_CONSUMERORDER_SHEET			130	/* 消耗品発注票										*/
		/*　インターネットＦＡＸ用に以下を追加
		**  1998/03/10  by Y.Tanimoto
		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		#define	LST_INF_TEXT_MAIL				131	/* ｲﾝﾀｰﾈｯﾄFAX　受信したTEXTﾒｰﾙ　Y.Tanimoto　*/
		#define	LST_INF_ERROR_NOTICE			132
		#define	LST_INF_JUNK_NOTICE				134
		#define	LST_INF_MAILBOX_NOTICE			135
		#define	LST_INF_ERASED_MAIL_NOTICE		136
		#define	LST_INF_ERASED_COMMAND_NOTICE	137
#endif

#if defined(KEISATSU)/* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
		#define	LST_FORCE_STOP_COMM_CHKMSG		131	/* 通信強制中断のメッセージ印字 					*/
#endif

		/* 注）これより前に追加したリストはストップキーにて停止不可能です */

		#define	LST_PATTERN1				 1	 /* Pattern Print 1			*/
		#define	LST_PATTERN2				 2	 /* Pattern Print 2			*/
		#define	LST_PATTERN3				 3	 /* Pattern Print 3			*/
		#define	LST_PATTERN4				 4	 /* Pattern Print 4			*/
		#define	LST_PATTERN5				 5	 /* Pattern Print 5			*/
		#define	LST_PATTERN6				 6	 /* Pattern Print 6			*/
		#define	LST_PATTERN7				 7	 /* Pattern Print 7			*/
		#define	LST_PATTERN8				 8	 /* Pattern Print 8			*/
		#define	LST_CLEANING_PAPER			 9	 /* クリーニングペーパー(追加 石橋正和 94/09/13) */
		#define	LST_PATTERN10				10	 /* ＰＣからの格子パターンプリント（Pattern Print 1と内容は同じです）*/
		#define	LST_PATTERN11				11	 /* ＰＣからの升目パターンプリント（Pattern Print 2と内容は同じです）*/
		#define	LST_PATTERN12				12	 /* V851 チェッカー By H.Fujimura 2002/07/15 */
		/*----- CHAR MAKE -------------------------------------------------- */

		/*----- LIST_OUT RESULT--------------------------------------------- */
		#define	LIST_OK						  0	  /*						 */
		#define	LIST_PAPER_ERR				  1	  /*						 */
		#define	LIST_STOP					  2	  /*						 */

		#define	MSG_SVC_TEST_PATTERN_PRINT	5

		#define	MSG_SVC_IO_OBSERVE			6
			#define	MSG_OBSERVE_CI				0
			#define	MSG_OBSETVE_OH				1

		#define	MSG_SVC_INTERNAL_SETTING	7

		#define	MSG_VOICE_REQ_ACCEPT		9	/* By Sakamoto 8 -> 9 '92,10, 9*/

		/** From MainTask To NCU_Task,NCU_TelephoneOperationTask,NCU_DailInAutoSwitch '93,12,13 By N.S. **/
		#define MSG_TELEPHONE_OPERATION			 1	 /*		 多機能電話として起動		 TBD OPR */
		#define MSG_TAD_OPERATION				 2	 /* ＴＡＤオペレーションとして起動	 TBD TAD */
		#define MSG_AFTER_RECEIVE				 3	 /*	 　　　　　内蔵ＴＡＤ着信			   　*/
		#define MSG_AFTER_FAXCOM				 4	 /*	 　　　　　 遠隔留守切替				 */
		#define MSG_ON_HOLD_KEY					 5	 /*			  HOLD KEY ON			 TBD OPR */
		#define MSG_TEL1_INTER_CALLING_START	 6	 /* TEL1より内線呼出START 　　　　　 TBD OPR */
		#define MSG_TEL1_HOLD_TRANSFER_START	 7	 /* TEL1より保留転送START 　　　　　 TBD OPR */
		#define	MSG_OPR_TADRECORD_REQ			 8	 /* 内蔵TAD録音								 */
		#define MSG_OPR_TADPLAY_REQ				 9	 /* 内蔵TAD再生								 */
		#define MSG_OPR_TADSKIP_REQ				10
		#define MSG_OPR_TADREPEAT_REQ			11
		#define	MSG_OPR_TADDELETE_REQ			12

#if defined (KEISATSU) /* 警察FAX 05/09/20 石橋正和 */
		#define MSG_ISSEI_TX					0 /* 一斉指令送信へ移行 */
		#define MSG_SHIREI_OFF					1 /* 指令起動信号OFF */
#endif

	/*-------------------------------------------------------------------------
	**	FROM_COPY
	*/
	#define FROM_COPY				3
		#define MSG_CPY_END					0
		#define MSG_CPY_PAGE_END			1
		#define	MSG_CPY_NO_DOCUMENT			2
		#define MSG_CPY_DOC_ERROR			3
		#define	MSG_CPY_NO_PAPER			4
		#define MSG_CPY_PAPER_ERROR			5
		#define MSG_CPY_LAMP_ERROR			6
		#define MSG_CPY_STOPSW_ON			7
		#define MSG_CPY_PAPER_END			8	/* ﾌﾟﾘﾝﾄ終了時次のﾌﾟﾘﾝﾄが出来ない状態 */
												/* １枚正常に書いて紙が無くなった */
		#define	MSG_CPY_NO_INK				9
		#define	MSG_CPY_CUTTER_ERROR		10
		#define MSG_CPY_THERMAL_TEMP_ERROR	11
		#define MSG_COPY_READY_DOWN			14	/* MATSU Printer Error */

	/*-------------------------------------------------------------------------
	**	FROM_DOCUMENT_IN
	*/
	#define FROM_DOCUMENT_IN		4		/* Modify J.Miyazaki '93.12/28 */
		#define	MSG_DOCUMENT_IN_SETUP		1
		#define	MSG_DOCUMENT_IN_ERROR		2
		#define MSG_DOCUMENT_IN_NOTHING		3	/* 原稿引き抜き */
		#define	MSG_DOCUMENT_IN_LAMP_ERROR	4

	/*-------------------------------------------------------------------------
	**	FROM_DOCSTORE
	*/
	#define FROM_DOCSTORE			5
		#define MSG_SCN_DOCSTORE_OK				0
		#define	MSG_SCN_DOCSTORE_MEM_OVER		1
		#define	MSG_SCN_DOCSTORE_STOPSW_ON		2
		#define	MSG_SCN_DOCSTORE_MAXLINE_OVER	3
		#define	MSG_SCN_DOCSTORE_NO_DOCUMENT	4
		#define	MSG_SCN_DOCSTORE_DOC_ERROR		5
		#define	MSG_SCN_DOCSTORE_LAMP_ERROR		6
		#define	MSG_SCN_DOCSTORE_STR_PAGE_ERROR	7	/* 原稿枚数指定ｴﾗｰ */
		#define	MSG_SCN_DOCSTORE_1PAGE_FINISH	8	/* 原稿蓄積一ページ蓄積正常終了 */
		#define	MSG_SCN_DOCSTORE_1PAGE_START	9	/* 原稿蓄積一ページ蓄積開始 */
		#define	MSG_SCN_DOCSTORE_MIRROR_ERROR	10	/* ミラーキャリッジエラー */
		#define MSG_SCN_DOCSTORE_TOP_COVER_OPEN 11	/* 読み取り中プリンタカバー開 */
		#define MSG_SCN_DOCSTORE_RXIL_ABORT		12	/* RXIL瞬断対策 T.Nose */

#if (0)	/* たぶん使ってないよ By M.Tachibana 1996/11/06 */
	/*-------------------------------------------------------------------------
	**	FROM_OPERATE
	*/
	#define FROM_OPERATE			X
		#define MSG_COPY_COM				1
		#define MSG_PRINT_COM				2
		#define MSG_STR_COM					3
		#define FAX_COM						4
		#define TEST_PRINT_COM				5
		#define TEST_FAXCOM					6	/* By S.Kawasaki */

	/*-------------------------------------------------------------------------
	**	FROM_TX_TSK
	*/
	#define FROM_TX_TSK				X
		#define MSG_TX_OK					0

	/*-------------------------------------------------------------------------
	**	FROM_RX_TSK
	*/
	#define FROM_RX_TSK				X
		#define MSG_RX_OK					0
		#define MSG_RX_ERROR				1

	/*-------------------------------------------------------------------------
	**	FROM_ECMPRT_TSK
	*/
	#define FROM_ECMPRT_TSK			X
		#define ECM_PRT_OK					0
		#define ECM_PRT_ERROR				1

	/*-------------------------------------------------------------------------
	**	FROM_KEYINPUT
	*/
	#define	FROM_KEYINPUT			X		/* Dummy By Kawasaki 4/15/92	*/
		#define FEED_OUT_DOC		0		/* Add By Yoshida 6/1/92		*/

#endif	/* たぶん使ってないよ By M.Tachibana 1996/11/06 */


	/*-------------------------------------------------------------------------
	**	FROM_PRN_IMAGE_PRINT_TASK
	*/
	#define FROM_PRN_IMAGE_PRINT_TASK	6
		#define MSG_PRN_IMAGE_END				0	/* 実際のﾌﾟﾘﾝﾄ正常終了 */
		#define	MSG_PRN_IMAGE_WAIT				1
		#define	MSG_PRN_IMAGE_WAIT_END			2
		#define	MSG_PRN_IMAGE_PAPER_END			3	/* １枚正常に書いて紙が無くなった */
		#define	MSG_PRN_IMAGE_STOPSW_ON			4
		#define MSG_PRN_IMAGE_NO_ID				5
		#define	MSG_PRN_IMAGE_NO_PAPER			6
		#define MSG_PRN_IMAGE_PAPER_ERROR		7
		#define	MSG_PRN_IMAGE_NO_INK			8
		#define	MSG_PRN_IMAGE_CUTTER_ERROR		9
		#define MSG_PRN_IMAGE_PAGE_END			10	/* 連続プリント実行時に１ページ正常にプリントできた. 未使用のため、機会があれば消去したい */
		#define	MSG_PRN_IMAGE_THERMAL_TMP_ERROR	11
		#define MSG_PRN_IMAGE_COVER_OPEN_ERROR	12	/* プリント中にプリンタカバーオープン */
		#define MSG_PRN_IMAGE_PRINT_DEC_ERROR	13	/** 蓄積原稿プリント中のデコードエラー（椛のみ） By O.K Jan,22,1995 **/
		#define	MSG_PRN_IMAGE_PRT_END			14	/* For POPLAR M.Tachibana 1997/04/17 */

	/*-------------------------------------------------------------------------
	**	FROM_SENSOR
	*/
	#define	FROM_SENSOR				7
		#define	MSG_TEL1_OFF_HOOK			1
		#define	MSG_TEL1_ON_HOOK			2
		#define	MSG_TEL2_OFF_HOOK			3
		#define	MSG_TEL2_ON_HOOK			4
		#define	MSG_P_READY					5
		#define	MSG_P_NOT_READY				6
		#define	MSG_P_STATUS_CHANGED		7
		#define	MSG_P_STATUS_NORMAL			8
		#define	MSG_PAPER_EXIT				9
		#define	MSG_PAPER_NOT_EXIT			10
		#define	MSG_SCANNER_COVER_OPEN		11
		#define	MSG_SCANNER_COVER_CLOSE		12
		#define MSG_DS1_ON					13
		#define	MSG_DS1_OFF					14
		#define	MSG_DS2_ON					15
		#define	MSG_DS2_OFF					16
		#define	MSG_PRINTER_COVER_OPEN		17
		#define	MSG_PRINTER_COVER_CLOSE		18
		#define	MSG_JAM_COVER1_OPEN			19
		#define	MSG_JAM_COVER1_CLOSE		20
		#define	MSG_JAM_COVER2_OPEN			21
		#define	MSG_JAM_COVER2_CLOSE		22
		#define	MSG_PAPER_SIZE_CHANGE		23
		#define	MSG_DIAL_IN_ON				24
		#define	MSG_DIAL_IN_OFF				25
		#define	MSG_PAPER_EXIST				26
		#define	MSG_PAPER_NOT_EXIST			27
		#define	MSG_LOW_PAPER1				28
		#define	MSG_HIGH_PAPER1				29
		#define	MSG_LOW_PAPER2				30
		#define	MSG_HIGH_PAPER2				31
		#define	MSG_PAPER1_EXIST			32
		#define	MSG_PAPER1_NOT_EXIST		33
		#define	MSG_PAPER2_EXIST			34
		#define	MSG_PAPER2_NOT_EXIST		35
		#define	MSG_RIBON_EXIST				36		/* Sep.2,1994 For MOMIJI By S.K */
		#define	MSG_RIBON_NOT_EXIST			37		/* Sep.2,1994 For MOMIJI By S.K */
		#define	MSG_RESET_PRINTER_COVER_CLOSE	38	/* By S.Kawasaki 1996/07/16 */
		#define	MSG_HPES_ON					39	/* For POPLAR By M.Tachibana 1997/01/18 */
		#define	MSG_HPES_OFF				40	/* For POPLAR By M.Tachibana 1997/01/18 */
		#define	MSG_SENSOR_UPDATE			41	/* For POPLAR By M.Tachibana 1997/01/22 */
		#define	MSG_JAM_COVER_OPEN			42
		#define	MSG_JAM_COVER_CLOSE			43
		#define MSG_FBS_PRESS_BOAD_OPEN		44
		#define MSG_FBS_PRESS_BOAD_CLOSE	45
		#define MSG_CASSETTE_OPEN			46	/* For POPLAR By M.Tachibana 1997/07/05 */
		#define MSG_CASSETTE_CLOSE			47	/* For POPLAR By M.Tachibana 1997/07/05 */
#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
		#define MSG_SCRAMBLE_ON				48	/* スクランブルSW ON */
		#define MSG_SCRAMBLE_OFF			49	/* スクランブルSW OFF */
		#define MSG_S1_ERROR_ON				50	/* S1エラーON */
		#define MSG_S1_ERROR_OFF			51	/* S1エラーOFF */
#endif

	/*-------------------------------------------------------------------------
	**	FROM_TIMER
	*/
	#define	FROM_TIMER				8
		#define	MSG_TIME_UP_1MIN			0
		#define	MSG_TIME_UP_VAR				1
		#define	MSG_DATE_CHANGED			2
		#define	MSG_PRINTER_ERROR			3
		#define	MSG_PRINTER_ERROR_CLEAR		4
		#define MSG_SUMMER_TIME_EXECUTE		5	/* 1996.01.23 Eguchi サマータイム実行メッセージ */
		#define MSG_SCAN_CONT_TIMEUP		6
		#define MSG_MULTI_DISPLAY_TIME		7	/* 1997/02/04 Y.Matsukama マルチ表示実行メッセージ */
		/* #define	MSG_CITIME_UP_VAR			2 */ /* By S.K May.21,1993 */
		/* #define	MSG_HUNG_UP_VAR				3 */ /* By M.H May.29,1993 */
		#define MSG_PRINTER_WAKEUP			8	/* By M.Tachibana 1997/12/03 */
		/*　インターネットＦＡＸ用に以下を追加
		**  1998/03/12  by Y.Tanimoto
		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		#define MSG_INF_COMPLETE			9
		#define	MSG_INF_TERMINATE			10
		#define	MSG_INF_NO_NEW_MAIL			11
#endif
#if (PRO_PREHEAT == ENABLE)
		#define MSG_PREHEAT_START_TIME		12	/* 寒冷地 PreHeat 開始  1998/12/26 s.takeuchi */
		#define MSG_PREHEAT_END_TIME		13	/* 寒冷地 PreHeat 終了  1998/12/26 s.takeuchi */
#endif
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/19*/
		#define MSG_ECO_MODE_CHANGE			14
#endif
#if 0 /* (PRO_ENERGY_SAVE == ENABLE) 見送る */		/* 2002/11/29 T.Takagi */
		#define MSG_24V_OFF					15
#endif
	/*-------------------------------------------------------------------------
	**	FROM_NCU_TASK
	**	FROM_NCU_TELEPHONEOPERATIONTASK
	**	FROM_NCU_DIALINAUTOSWITCHTASK
	*/
	#define	FROM_NCU_TASK						9
	#define	FROM_NCU_TELEPHONEOPERATIONTASK		10
	#define	FROM_NCU_DIALINAUTOSWITCHTASK		11
		#define	   MSG_FROM_NCU_OK_RECEIVE			1
		#define	   MSG_DETECT_CI					2	  /*  CI割込検出／着信検出中  */
		#define	   MSG_DETECT_CI_TIMEUP				3	  /*	CI割込検出 Time Up	  */
		#define	   MSG_DETECT_CALL_TO_FAX			4	  /*   FAXCOMダイレクト着信	  */
		#define	   MSG_DETECT_CALL_TO_TEL			5	  /*	多機能電話経由着信	  */
		#define	   MSG_DETECT_F_NET					6	  /* F網着信（1300Hz検出）	  */
		#define	   MSG_DETECT_CALL_D_IN				7	  /*  ダイヤル・イン経由着信  */
		#define	   MSG_DETECT_TRANSFER_TEL_EXIT		8	  /* 転送受信／仮着信後の着信 NCU_TEL終了 */
		#define	   MSG_DETECT_TRANSFER_TEL_CONT		9	  /* 転送受信／仮着信後の着信 NCU_TEL継続 */
		#define	   MSG_DETECT_TRANSFER_D_IN		   10	  /* ダイヤル・インよりFAX着信 */
		#define	   MSG_D_IN_TIMEUP				   11	  /* 疑似ベル鳴動TimeUp		   */
		#define	   MSG_HOLD_ELAPSE_1MIN			   12	  /* 保留状態1分経過 叉は前回同ﾒｯｾｰｼﾞより1分経過 */
		#define	   MSG_HOLD_TIMEUP				   13	  /* 保留状態5分経過 Time UP 　*/
		#define	   MSG_DETECT_TEL1_OFF_HOOK		   14	  /*	TEL1  OFF HOOK 検出 　*/
		#define	   MSG_DETECT_TEL2_OFF_HOOK		   15	  /*	TEL2  OFF HOOK 検出	  */
		#define	   MSG_DETECT_INPUT_HOOK_KEY	   16	  /* HOOK KEY 入力検出 */
		#define	   MSG_DETECT_INPUT_HOLD_KEY	   17	  /* HOLD KEY 入力検出 */
		#define	   MSG_DETECT_ON_HOOK_EXIT		   18	  /* TEL1/TEL2/HOOK KEY ON	HOOK 検出NCU_TEL終了 */
		#define	   MSG_DETECT_ON_HOOK_CONT		   19	  /* TEL1/TEL2/HOOK KEY ON	HOOK 検出NCU_TEL終了 */
		#define	   MSG_DETECT_BRN_OFF_HOOK		   20	  /*  BRN TEL OFF  HOOK 検出  */
		#define	   MSG_DETECT_BRN_ON_HOOK_EXIT	   21	  /*  BRN TEL  ON  HOOK 検出 NCU_TEL終了 */
		#define	   MSG_DETECT_BRN_ON_HOOK_CONT	   22	  /*  BRN TEL  ON  HOOK 検出 NCU_TEL継続 */
		#define	   MSG_DETECT_REMOTE_FAX_EXIT	   23	  /*  Remote FAX 検出 NCU_TEL終了 */
		#define	   MSG_DETECT_REMOTE_FAX_CONT	   24	  /*  Remote FAX 検出 NCU_TEL継続 */
		#define	   MSG_NOT_DET_REMOTE_FAX_EXIT	   25	  /*  Remote FAX 検出 NCU_TEL終了 */
		#define	   MSG_NOT_DET_REMOTE_FAX_CONT	   26	  /*  Remote FAX 検出 NCU_TEL継続 */
		#define	   MSG_TEL2_INTER_CALLING_START	   27	  /*  TEL2 より内線呼出START */
		#define	   MSG_TEL2_HOLD_TRANSFER_START	   28	  /*  TEL2 より保留転送START */
		#define	   MSG_INTER_CALLING_STOP_EXIT	   29	  /*  内線呼出／保留転送中止 NCU_TEL終了 */
		#define	   MSG_INTER_CALLING_STOP_CONT	   30	  /*  内線呼出／保留転送中止 NCU_TEL継続 */
		#define	   MSG_INTER_CALLING_STOP_OFF_HOOK 31	  /*  内線呼出／保留転送中止 NCU_TEL継続 */
		#define	   MSG_INTER_COM_START			   32	  /*  内線通話／三者通話中 　*/
		#define	   MSG_INTER_COM_END_TEL_EXIT	   33	  /*  内線通話／三者通話終了 NCU_TEL終了 */
		#define	   MSG_INTER_COM_END_TEL_CONT	   34	  /*  内線通話／三者通話終了 NCU_TEL(TAD)継続 */
		#define	   MSG_INTER_COM_END_OFF_HOOK1	   35	  /*  内線通話／三者通話終了 NCU_TEL(TEL1)継続 */
		#define	   MSG_INTER_COM_END_OFF_HOOK2	   36	  /*  内線通話／三者通話終了 NCU_TEL(TEL2)継続 */
		#define	   MSG_INTER_THREE_PARTIES_COM_END 37	  /*  三者通話終了／二者通話継続 */
		#define	   MSG_BUILTIN_TAD_COM_END_EXIT	   38	  /*  内蔵TAD通信終了		 NCU_TEL終了	  */
		#define	   MSG_BUILTIN_TAD_COM_END_CONT	   39	  /*  内蔵TAD通信終了		 NCU_TEL継続	  */
		#define	   MSG_BUILTIN_TAD_OPR_END_EXIT	   40	  /*  内蔵TADｵﾍﾟﾚｰｼｮﾝ終了	 NCU_TEL終了	  */
		#define	   MSG_BUILTIN_TAD_OPR_END_CONT	   41	  /*  内蔵TADｵﾍﾟﾚｰｼｮﾝ終了	 NCU_TEL継続	  */
		#define	   MSG_REMOTE_FAX_FAILED_EXIT	   42	  /*  ﾘﾓｰﾄFAX　ｱｸｾｽｺｰﾄﾞNG　　NCU_TEL終了 '94/07/07 By eguchi */
		#define	   MSG_REMOTE_FAX_FAILED_CONT	   43	  /*  ﾘﾓｰﾄFAX　ｱｸｾｽｺｰﾄﾞNG　　NCU_TEL継続 '94/07/07 By eguchi */
		#define	   MSG_END_OF_FAXCOM			   44	  /*  通信終了時に内線通話実行中なら、NCU_TelTaskへ送信 7/21/1994 SATSUKI QAT */
		#define	   MSG_BRC_LINE_VOLT_CHK_START	   45	  /* ブランチ電話の為の回線電圧測定開始 */
		#define	   MSG_BRC_LINE_VOLT_CHK_END	   46	  /* ブランチ電話の為の回線電圧測定終了 */
		#define	   MSG_NO_LINE_CHK_START		   47	  /* ブランチ電話の為の回線電圧測定中に回線抜けを検出 */
		#define	   MSG_DETECT_RING				   48	  /* CLASS1 CIを1波検出 by Y.Tanimoto		*/
		#define	   MSG_DETECT_ON_HOOK_CONT_TEL1	   49	  /* TEL1/TEL2/HOOK KEY ON	HOOK 検出NCU_TEL終了 By M.Tachibana 1997/09/25 */
		#define	   MSG_DETECT_ON_HOOK_CONT_TEL2	   50	  /* TEL1/TEL2/HOOK KEY ON	HOOK 検出NCU_TEL終了 By M.Tachibana 1997/09/25 */
		#define	   MSG_DETECT_CALL_TO_FAX_EXT      51	  /* 拡張ライン着信 */
		#define	   MSG_DETECT_F_NET_EXT            52	  /* 拡張ラインF網着信（1300Hz検出）	  */
		#define    MSG_DETECT_ON_HOOK_CONT_HKEY    53     /* フックキーオンフック検出でNCU_TEL継続   by T.Soneoka 1998/01/20 */
		#define	   MSG_DETECT_CL1_D_IN			   54	  /* PRO_CLASS1 ダイヤルイン着信  	  PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
		#define	   MSG_DETECT_CL1_D_IN_DSE		   55	  /* PRO_CLASS1 ダイヤルイン極反検出  PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
		#define	   MSG_DETECT_F_NET_TIMEOUT		   56	  /* PRO_CLASS1 F網対応  			  PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
		#define	   MSG_DETECT_CL1_TRANSFER_TEL	   57	  /* PRO_CLASS1 ANS/FAX時、CNG／無音着信 PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
		#define	   MSG_DETECT_CL1_NON_D_IN		   58	  /* PRO_CLASS1 PRO_CL1_TELFAX_LAN ダイヤルイン設定時の非ダイヤルイン呼に対するＰＣ着信 S.Fukui June 19,1998 */
		#define	   MSG_DETECT_ND_CAR			   59	  /* ナンバーディスプレイの CAR 検出 by H.Kubo 1998/08/04 */
		#define    MSG_DETECT_ND_NUMBER			   60	  /* ナンバーディスプレイの発信者番号検出 H.Yoshikawa 1998/09/19 */
		#define	   MSG_NCU_RESTART				   61	  /* NDの処理を行った後は、必ず、NCU_Taskを再起動します。 */
		#define	   MSG_DETECT_TRANSFER_MODEM_D_IN  62	  /* モデムダィヤルイン着信検出 by H.Kubo 1999/02/25 */
		#define	   MSG_DETECT_CALLED_REQUEST_ND    63	  /* ナンバーディスプレイで着信検出 by H.Kubo 1999/02/26 */
		#define	   MSG_DETECT_RING_DUMMY		   64	  /* ナンバーディスプレイが１波検出した場合のダミーメッセージ by H.Hirao 1999/05/12 */
		#define	   MSG_NCU_TASK_RE_CREATE		   65	  /* ＮＣＵタスクを再起動する by H.Hiroa 1999/05/12 */
	/*-------------------------------------------------------------------------
	**	FROM_BUILTIN_TAD
	*/
	#define	FROM_BUILTIN_TAD		12

	/*-------------------------------------------------------------------------
	**	FROM_OPERATION
	*/
	#define	FROM_OPERATION			13
		#define	MSG_COPY					0
		#define	MSG_STORE_MEMORY_TX_DOC		1
		#define	MSG_STORE_MEMORY_BATCH_TX_DOC	2
		#define	MSG_STORE_POLLING_DOC		3
		#define	MSG_STORE_DBPOLLING_DOC		4
		#define	MSG_STORE_MULTI_COPY_DOC	5
		#define	MSG_PRINT_MEMORY_DOC		6
		#define	MSG_PRINT_POLLING_DOC		7
		#define	MSG_PRINT_DBPOLLING_DOC		8
		#define	MSG_PRINT_MULTI_COPY_DOC	9
		#define	MSG_PRINT_SECURE_RX_DOC		10
		#define	MSG_ONETOUCH_DIAL_LIST		11
		#define	MSG_CIPHERKEY_LIST			12
		#define	MSG_SPEED_DIAL_LIST			12
		#define	MSG_PROGRAM_ONETOUCH_LIST	13
		#define	MSG_SETTING_LIST			14
		#define	MSG_COVER_PAGE_LIST			15
		#define	MSG_GROUP_LIST				16
		#define	MSG_MAILBOX_LIST			17
		#define	MSG_COMMAND_LIST			18
		#define	MSG_TX_JOURNAL				19
		#define	MSG_TTI_PRINT				20
		#define	MSG_TCR_LIST				21
		#define	MSG_PROGRAM_LIST			22
		#define	MSG_T30MONITOR_LIST			23
		#define	MSG_ENTER_COMMAND			24
		#define	MSG_ERASE_COMMAND			25
		#define	MSG_ERASE_EXECQUEUE			26
		#define	MSG_ON_HOOK_TEL_START		27
		#define	MSG_ON_HOOK_TEL_STOP		28
		#define	MSG_HOOKING					29
		#define	MSG_HOLD_START				30
		#define	MSG_HOLD_STOP				31
		#define	MSG_MANUAL_TX				32
		#define	MSG_MANUAL_RX				33
		#define	MSG_SVC_TEST_PATTERN		34
		#define MSG_SVC_FACTORY_MENU		35
		#define	MSG_MEMORY_OVER_ENTER		36
		#define	MSG_MEMORY_OVER_CANCEL		37
		#define	MSG_MEMORY_OVER_TIME_UP		38
		#define	MSG_VOICE_SWITCH_ON			39
		#define	MSG_FEED_OUT_DOC			40
		#define	MSG_DIAL_IN_NUMBER_STORE	41
		#define	MSG_SERV_FEED_OUT_DOC		42
		#define	MSG_SERV_FEED_OUT_DOC2		43
		#define	MSG_MEM_SW_LIST				44
		#define	MSG_SERV_RS232C_TEST		45	/* RS232C折り返しﾃｽﾄ By H.T	*/
												/* Mar.11.1993	*/
		#define	MSG_FNET_ACCESS_TX			46
		#define	MSG_FNET_ACCESS_RX			47
		#define MSG_STORE_FNET_TX_DOC		48
		#define	MSG_LIST_PRINT				49	/* Jan.11,1994 S.K */
		#define MSG_MEMORY_PRINT			50	/* Jan.12,1994 S.K */
		#define OPR_TADRECORD_REQ			51	/* Mar.02.1994 M.E */
		#define OPR_TADPLAY_REQ				52	/* Mar.02.1994 M.E */
		#define OPR_TADSKIP_REQ				53	/* Mar.02.1994 M.E */
		#define OPR_TADREPEAT_REQ			54	/* Mar.02.1994 M.E */
		#define OPR_TADDELETE_REQ			55	/* Mar.02.1994 M.E */
		#define OPR_TADSTOP_REQ				56	/* Mar.02.1994 M.E */
												/* SubMessage1*/
			#define		OGM			1			/* Mar.02.1994 M.E */
			#define		CONV		2			/* Mar.02.1994 M.E */
			#define		MEMO		3			/* Mar.02.1994 M.E */
			#define		OGM1		4			/* Mar.02.1994 M.E */
			#define		OGM2		5			/* Mar.02.1994 M.E */
			#define		OGM3		6			/* Mar.02.1994 M.E */
			#define		OGM4		7			/* Mar.02.1994 M.E */
			#define		OGMU		8			/* Mar.02.1994 M.E */
			#define		ICM			9			/* Mar.02.1994 M.E */
		#define MSG_DISPLAY_IDLE			57	/* Masuda 94/03/09 */
				/* ﾒｲﾝにDisplayIdle()を実行してもらう為のﾒｯｾｰｼﾞ。但しﾒｲﾝは
				何かﾒｯｾｰｼﾞが来れば無条件でDisplayIdle()を実行するので、これは
				空ﾒｯｾｰｼﾞとなる。masuda*/
		#define MSG_INTER_CALL_START		58	/* TEL1からの内線呼出要求  by TH92115 1994/06/02 */
		#define MSG_HOLD_TRANS_START		59	/* TEL1からの保留転送要求  by TH92115 1994/06/02 */
		#define MSG_SERV_START				60	/* サービスファンクション開始通知(メインにNCUタスクを殺してもらう為)	*/
		#define MSG_SERV_END				61	/* サービスファンクション終了通知(メインにNCUタスクを生成してもらう為)	*/
		#define MSG_UPDATE_DISPLAY			62	/* By S.K 7/12/1994	*/
		#define MSG_MANUAL_POLLING			63	/* 手動ポーリング By T.Nose */
		#define MSG_STORE_MULTI_PROGRAM_DOC 64	/* 桐マルチ・プログラム・コマンド By S.K 7/21/1994 */
		#define	MSG_PRINT_DEMO_DOC			65	/* ラベンダ:デモ用ﾄﾞｷｭﾒﾝﾄﾌﾟﾘﾝﾄ '94.0823 S.Tan */
		#define	MSG_SERV_STAMP_TEST			66	/* スタンプ・テスト Aug.23,1994 */
		#define	MSG_PRINT_PROTECT_OFF		67	/* 受信原稿プリントプロテクト解除 1995.12.22 Eguchi 受信原稿プリントプロテクト機能用に追加 */
		#define MSG_STORE_CLASS1_TX_DOC		68	/* CLASS1ﾛｰｶﾙｽｷｬﾝ用送信原稿	 by Y.Tanimoto 1996/06/26  */
		#define MSG_SERV_AUTO_INIT			69	/* CLASS1 Auto Initialize	  */
		#define	MSG_ERASE_CONTINUOUS_POLLING	70	/* 連続ポーリングコマンド消去1996/10/18 Eguchi */
		#define MSG_SERV_SHADING_START		71	/* シェーディング取り込み開始 T.Nose 1997/01/28 */
		#define MSG_SERV_SHADING_END		72	/* シェーディング取り込み終了 T.Nose 1997/01/28 */
		#define MSG_STORE_MANUAL_COPY_DOC	73	/* 手差しコピー起動 by M.Tachibana 1997/01/29 */
		#define MSG_STORE_FCODE_BOX_DOC		74	/* FコードBOX原稿蓄積 1997/03/11  By T.Yamaguchi */
		#define MSG_SCAN_CONT_START			75	/* 次原稿あり→読み取り開始				*/
		#define MSG_SCAN_CONT_END			76	/* 次原稿あり→送信開始（読み取り終了）	*/
		#define MSG_SCAN_CONT_ABORT			77	/* 蓄積原稿キャンセル					*/
		#define MSG_STORE_CIPHER_DOC		78	/* 暗号化前原稿蓄積	By Y.Suzuki 1997/06/02 */
		#define MSG_DECIPHER_START			79	/* 暗号化解除開始	By Y.Suzuki 1997/06/02 */
		#define MSG_FBS_TRANSPORT_SET		80	/** FBS輸送モード設定 */
		#define MSG_FBS_TRANSPORT_RESET		81	/** FBS輸送モード解除 */
												/*  1998.3.11 by K.Okada */
		/*　インターネットＦＡＸ用に以下を追加
		**  1998/03/10  by Y.Tanimoto
		*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		#define MSG_STORE_MAIL_TX_DOC		82	/*　ｲﾝﾀｰﾈｯﾄFAX用　送信原稿蓄積要求						*/
		#define MSG_STORE_MIXED_TX_DOC		83	/*　ｲﾝﾀｰﾈｯﾄFAX用　ﾒｰﾙ&FAX混在同報用の原稿蓄積要求		*/
		#define MSG_MAIL_MANUAL_RX			84	/*　ｲﾝﾀｰﾈｯﾄFAX用　手動受信起動要求						*/
		#define MSG_MAILCOM_LIST_PRINT		85	/*　ｲﾝﾀｰﾈｯﾄFAX用　ﾒｰﾙ用各種ﾘｽﾄﾌﾟﾘﾝﾄ起動要求				*/
		#define MSG_MAIL_STORED_DOC_PRINT	86	/*　ｲﾝﾀｰﾈｯﾄFAX用　送信予約原稿ﾌﾟﾘﾝﾄ起動要求				*/
		#define MSG_MAIL_MANUAL_PRINT		87	/*　ｲﾝﾀｰﾈｯﾄFAX用　手動受信ﾒｰﾙﾌﾟﾘﾝﾄ起動要求(使用されないかもしれない) */
		#define MSG_INF_TEST_FUNCTION		88	/*　ｲﾝﾀｰﾈｯﾄFAX用　テストファンクション実行要求			*/
		#define	MSG_INF_INIT_ENGINE_BOARD	89	/*　ｲﾝﾀｰﾈｯﾄFAX用　設置オペレーション実行要求　*/
#endif
		#define	MSG_CLASS1_MANUAL_RX		90	/* Class1手動受信起動 PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */

		#define MSG_CHANGE_PRINT_TYPE		91	/* 記録タイプ変更後のイニシャルカット起動メッセージ 1998/08/19 H.Yoshikawa */

#if (PRO_PRINT_TYPE == THERMAL)
		#define MSG_REALTIME_COPY			92	/* 1998/10/07 by T.Soneoka */
#endif

	/*-------------------------------------------------------------------------
	**	FROM_LIST_PRINT
	*/
	#define	FROM_LIST_PRINT			14			   /* By Tanaka 92/09/01 *//* Discript LIST_MSG.H */

	/*-------------------------------------------------------------------------
	**	FROM_FAXCOM
	*/
	#define	FROM_FAXCOM				15			   /* By S.K 7/24/1992 */
		#define	MSG_FAXCOM_END				0
		#define MSG_FAXCOM_ANS_CHANGE_KAMO	1	/* 1994/03/02 Y.Murata */
		#define MSG_FAXCOM_END_OFF_HOOK		2	/* 1994/06/20 Y.Murata 会話予約成立 or TEL/FAX待機 OFF_HOOK検出で通信終了 */

			/* SubMassage1		   */
			#define FAXCOM_OK					1	/* 1994/02/08 Y.Murata */
			#define FAXCOM_REDIAL				2	/* 1994/02/08 Y.Murata */
			#define FAXCOM_ERROR				3	/* 1994/02/08 Y.Murata */
			/* SubMassage2		   */
			#define MSG_FCOM_TEL1_OH			1	/* 1994/06/22 Y.Murata */
			#define MSG_FCOM_TEL2_OH			2	/* 1994/06/22 Y.Murata */
			#define MSG_FCOM_HOOK_KEY_OH		3	/* 1994/06/22 Y.Murata */

		#define	MSG_VOICE_REQ_START			3
		#define	MSG_VOICE_REQ_END			4
		#define DETECT						5	 /* '92,09,22  By Sakamoto */
		#define MSG_OK_EXIT					6	 /* '92,09,22  By Sakamoto */
		#define	MSG_RX_PRINT_PAGE			7
		#define	MSG_TEL_FAX_START			8
		#define	MSG_TEL_FAX_END				9
		#define MSG_FAXCOM_DISPLAY			10	/* 1994/02/08 Y.Murata */
		#define MSG_FAXCOM_RX_START			11	/* 1994/04/06 Y.Suzuki fcm_rcmp.c の最後で送信 */
		#define MSG_BUFFERING_PRINT_START	12	/* 1994/04/23 M.Tachibana */
		#define	MSG_FAXCOM_CLOSE_ERROR		13	/* 7/13/1994 Phase Scanner Close Error By S.K */
		#define	MSG_FAXCOM_PRINTER_ERROR	14	/* Jul.20.1994	竹内 */
		#define MSG_FAXCOM_TX_START			15
			/*	SubMessage1		*/
			#define	MSG_FAXCOM_NO_PAPER			1	/*	記録紙切れ (黒エンドマークも)	*/
			#define	MSG_FAXCOM_CUTTER_ERROR		2	/*	カッターエラー		*/
			#define	MSG_FAXCOM_PAPER_JAM		3	/*	ジャム				*/
			#define	MSG_FAXCOM_COVER_OPEN		4	/*	カバーオープン		*/
			#define	MSG_FAXCOM_NO_INK			5	/*	ドナー切れ			*/
			#define	MSG_FAXCOM_TH_HI_TEMP		6	/*	Ｔ／Ｈハイテンプ	*/
			#define MSG_FAXCOM_3M_OVER			7	/*  ３ｍ原稿長オーバ	*/	/* added by H.Hirao 1998/12/16 */

		#define MSG_FAXCOM_SCANNER_DECIDE	16	/* スキャナ送信起動(ICHOU用)  1996/07/09 s.takeuchi */
		#define	MSG_FAXCOM_END_TIME				17	/* 通信終了時間ﾀｲﾐﾝｸﾞ 1996/02/05 Y.M */
		#define	MSG_FAXCOM_T30_CONTINUE			18	/* GRAPE -> ORANGE Change 1996/03/11 Y.M */
		#define	MSG_FAXCOM_T30_CONTINUE_ANSAM	19	/* GRAPE -> ORANGE Change ANSam Detect 1996/08/07 Y.M */
		#define	MSG_FAXCOM_OPTION_RECEIVE_REQ	20	/* ｵﾌﾟｼｮﾝ受信要求 */
		#define	MSG_FAXCOM_DETECT_CI			21	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ CI検出 1996/11/12 Y.Murata */
		#define	MSG_FAXCOM_DETECT_CI_TIMEUP		22	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ CIﾀｲﾑｵｰﾊﾞｰ 1996/11/12 Y.Murata */
		#define	MSG_FAXCOM_SET_JOURNAL			23	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ ｼﾞｬｰﾅﾙｾｯﾄ要求 1996/12/02 Y.Murata */
		#define	MSG_FAXCOM_START_TIME			24	/* 通信開始時間ﾀｲﾐﾝｸﾞ 1996/12/18 Y.M */
		#define MSG_FAXCOM_TEL1_OFF_HOOK		25	/* TEL1  OFF HOOK 検出 1997/01/06 By N.Sakamoto */
		#define	MSG_FAXCOM_ON_HOOK_EXIT			26  /* TEL1/TEL2/HOOK KEY ON HOOK 検出NCU_TEL終了 1997/01/06 By N.Sakamoto */
		#define	MSG_FAXCOM_ON_HOOK_CONT			27  /* TEL1/TEL2/HOOK KEY ON HOOK 検出NCU_TEL終了 1997/01/06 By N.Sakamoto */
		#define	MSG_FAXCOM_INPUT_HOOK_KEY	    28	/* HOOK KEY 入力検出  1997/01/06 By N.Sakamoto */
		#define	MSG_FAXCOM_INPUT_HOLD_KEY	    29	/* HOLD KEY 入力検出  1997/01/06 By N.Sakamoto */
		#define	MSG_FAXCOM_DET_TRANS_EXIT		30	/* 転送受信／仮着信後の着信 NCU_TEL終了 1997/01/20 By N.Sakamoto */
		#define	MSG_FAXCOM_CREATE_GRS_TASK		31  /*  FAX側の擬似ベル鳴動タスク起動指示 1997/01/28 BY N.Sakamoto */
		#define	MSG_FAXCOM_DELETE_GRS_TASK		32  /*  FAX側の擬似ベル鳴動タスク削除指示 1997/01/28 BY N.Sakamoto */
		#define	MSG_FAXCOM_START_GRS_BELL		33  /*  FAX側の呼出ブザー鳴動開始指示 	1997/01/28 BY N.Sakamoto */
		#define	MSG_FAXCOM_STOP_GRS_BELL		34  /*  FAX側の呼出ブザー鳴動停止指示 	1997/01/28 By N.Sakamoto */
		#define MSG_CL1_CNG_DETECT				35	/*  CLASS1対応 CNG検出 S.Fukui June 19,1998  */

	/*-------------------------------------------------------------------------
	**	FROM_FIP
	*/
	#define FROM_FIP				16			/* By H.Tomita	Jul.12 '93	*/
		#define	FIP_STOREDOC_REQ			1	/* FIP原稿蓄積要求	*/
		#define	FIP_DOCPRINT_REQ			2	/* FIP蓄積原稿ﾌﾟﾘﾝﾄ要求	*/
		#define	FIP_SEND_REQ				3	/* FIP蓄積原稿送信要求	*/
		#define	FIP_POLLING_REQ				4	/* FIPﾎﾟｰﾘﾝｸﾞ要求	*/
		#define	FIP_TEST_END				5	/* 追加 By A.O Feb.7.1994	（DISP_FROM_FIPから変更）*/
		#define	FIP_FILLIN_START			6	/* FillIn開始 By M.T 1995/02/24 */
		#define	FIP_FILLIN_END				7	/* FillIn終了 By M.T 1995/02/24 */
		#define	FIP_RETRIEVE_START			8	/* ﾘﾄﾘｰﾌﾞ開始 By M.T 1995/02/24 */
		#define	FIP_RETRIEVE_END			9	/* ﾘﾄﾘｰﾌﾞ終了 By M.T 1995/02/24 */
		#define	FIP_DISPLAY					10	/* FIP表示 By M.T 1995/02/24 */
		#define	FIP_DISPLAY_CHANGE			11	/* FIP表示 By M.T 1995/02/24 */

	/*-------------------------------------------------------------------------
	**	FROM_RSISR
	*/
	#define	FROM_RSISR				17
		/* ↓のメッセージは、ＣＬＡＳＳ1で使っている */
		#define	RS_RX_TIMEOUT				1	/* 一番最初のｷｬﾗｸﾀを受信する前にﾀｲﾑｵｰﾊﾞｰ	*/
		#define	RS_FIRST_RCV				2	/* RS232Cから一番最初のｷｬﾗｸﾀを受信	*/
		/* ↑のメッセージは、ＣＬＡＳＳ1で使っている */

	/*-------------------------------------------------------------------------
	**	FROM_POCKET_BELL
	*/
	#define	FROM_POCKET_BELL		18			/* By Y.Murata	1994/02/08	*/
		#define	MSG_TAD_POCKET_END			 1	/* ポケベルタスク 通常終了 */
		#define	MSG_TAD_POCKET_END_REMOTEFAX 2	/* ポケベルタスク リモートＦＡＸ送信リクエスト */
		#define	MSG_TAD_POCKET_AGAIN		 3	/* 多分使わない */

	/*-------------------------------------------------------------------------
	**	FROM_PRN_LST_PRINT_TASK
	*/
	#define	FROM_PRN_LST_PRINT_TASK		19
		#define	MSG_PRN_LST_END				1
		#define	MSG_PRN_LST_PAPER_END		2
		#define	MSG_PRN_LST_STOPSW_ON		3	/*ﾘｽﾄﾌﾟﾘﾝﾄ中のｽﾄｯﾌﾟｷｰ*/
		#define	MSG_PRN_LST_NO_LIST			4
		#define	MSG_PRN_LST_NO_ID			5
		#define	MSG_PRN_LST_NO_PAPER		6
		#define	MSG_PRN_LST_PAPER_ERROR		7
		#define	MSG_PRN_LST_NO_INK			8
		#define	MSG_PRN_LST_CUTTER_ERROR	9
		#define	MSG_PRN_LST_THERMAL_TEMP_ERROR	10	/* '94.6/6 By T.O */
		#define	MSG_PRN_LST_PRINTER_END		11	/* For POPLAR M.Tachibana 1997/04/17 */

	/*-------------------------------------------------------------------------
	**	FROM_10MS_TIMER
	*/
	#define FROM_10MS_TIMER				20			/* 10msTimer   By N.S. '94,03,01 */
		#define MSG_FAXCOM_COMPLETE			1
		#define MSG_STORE_COMPLETE			2
		#define MSG_PRINT_COMPLETE			3
		#define MSG_PC_FAX_COMPLETE			4	/* 1996/09/12 Eguchi */

	/*-------------------------------------------------------------------------
	**	FROM_KEYSCAN
	*/
	#define	FROM_KEYSCAN				21
		#define	MSG_KEYGET				1

	/*-------------------------------------------------------------------------
	**	FROM_MAN_DOCUMENT_WATCH_TASK
	*/
	#define	FROM_MAN_DOCUMENT_WATCH_TASK	22		/* By S.K Apr.8,1994 */
		#define	MSG_DOCUMENT_SET_OK			0
		#define	MSG_DOCUMENT_OUT			1
		#define	MSG_DOCUMENT_FEED_ERROR		2
		#define	MSG_DOCUMENT_COVER_OPEN		3

	/*-------------------------------------------------------------------------
	**	FROM_AUTODIAL
	*/
	#define	FROM_AUTODIAL				23			/* By M.T 94.04.26 */

	/*-------------------------------------------------------------------------
	**	FROM_CNG_DETECT
	*/
	#define FROM_CNG_DETECT				24			/* By T.O 94.5.23 */

	/*-------------------------------------------------------------------------
	**	FROM_DOCUMENT_OUT
	*/
	#define FROM_DOCUMENT_OUT			25
		#define	MSG_DOCUMENT_OUT_OK					1
		#define	MSG_DOCUMENT_OUT_ERROR				2
		#define	MSG_DOCUMENT_OUT_NEXTPAGE_OK		3
		#define	MSG_DOCUMENT_OUT_NEXTPAGE_ERROR		4

	/*-------------------------------------------------------------------------
	**	FROM_PRN_BUFFERING_PRINT_TASK
	*/
	#define	FROM_PRN_BUFFERING_PRINT_TASK	26			/* By M.T 94.06.17 */
		#define MSG_PRN_BUF_END					0	/* 実際のﾌﾟﾘﾝﾄ正常終了 */
		#define	MSG_PRN_BUF_PAPER_END			1	/* １枚正常に書いて紙が無くなった */
		#define	MSG_PRN_BUF_STOPSW_ON			2
		#define MSG_PRN_BUF_NO_ID				3
		#define	MSG_PRN_BUF_NO_PAPER			4
		#define MSG_PRN_BUF_PAPER_ERROR			5
		#define	MSG_PRN_BUF_NO_INK				6
		#define	MSG_PRN_BUF_THERMAL_TMP_ERROR	7
		#define MSG_PRN_BUF_COVER_OPEN_ERROR	8	/* プリント中にプリンタカバーオープン */
		#define MSG_PRN_BUF_MEM_OVER_WRITE		9

	/*-------------------------------------------------------------------------
	**	FROM_PRN_ALLPAGE_PRINT_TASK
	*/
	#define FROM_PRN_ALLPAGE_PRINT_TASK		27		/* By H.Y 1994/06/29 */
		#define MSG_PRN_IMAGE_ALLPAGE_END		0	/* 連続プリント実行時に全ページ正常にプリントできた */
		#define MSG_PRN_IMAGE_1PAGE_END			1	/* 連続プリント実行時に１ページ正常にプリントできた */
		#define MSG_PRN_ILLEGAL_ERROR			2	/* シリアル通信エラー */
		#define MSG_PRN_IMAGE_STOP				3	/* ストップスイッチが押された */
		#define	MSG_PRN_IMAGE_PRINTER_END		4	/* For POPLAR M.Tachibana 1997/04/17 */
		#define	MSG_PRN_IMAGE_INITIAL_END		5	/* For SAKAKI イニシャルカット終了 1998/08/19 H.Yoshikwa */

	/*-------------------------------------------------------------------------
	**	FROM_SCN_GEAR_BACK_LASH_TASK
	*/
	#define FROM_SCN_GEAR_BACK_LASH_TASK	28
		#define MSG_SCN_GEAR_BACK_LASH_END		0

	/*-------------------------------------------------------------------------
	**	FROM_SCN_STAMP_TEST_TASK
	*/
	#define	FROM_SCN_STAMP_TEST_TASK		29

#if (0)	/* By M.Tachibana 1997/06/07 */
**	/*-------------------------------------------------------------------------
**	**	FROM_PRN_HIGH_TEMP
**	*/
**	#define	FROM_PRN_HIGH_TEMP				X
**		#define	MSG_PRN_IMAGE					0
**		#define	MSG_PRN_LIST					1
**		#define MSG_PRN_COPY					2
#endif

	/*-------------------------------------------------------------------------
	**	FROM_CHILD_TIMEOUT
	*/
	#define	FROM_CHILD_TIMEOUT				30
		#define	MSG_CHILD_TIMEOUT				2

	/*-------------------------------------------------------------------------
	**	FROM_CLASS1
	*/
	#define FROM_CLASS1					31
		#define	MSG_CL1_CALLED				1	/* CLASS1が着信した					*/
		#define	MSG_CL1_AUTO_CALLED			2	/* CLASS1が自動着信した				*/
		#define	MSG_CL1_RING_TIMEOUT		3	/* CLASS1がF網着信した				*/
		#define	MSG_CL1_AUTO_CALLED_FNET	4	/* CLASS1がF網自動着信した			*/
		#define	MSG_CL1_CALLED_DIALIN		5	/* CLASS1がﾀﾞｲﾔﾙｲﾝ着信した			*/
		#define	MSG_CL1_AUTO_CALLED_DIALIN	6	/* CLASS1がﾀﾞｲﾔﾙｲﾝ自動着信した		*/
		#define	MSG_CL1_ONLINE_REQ			7	/* CLASS1の回線接続(OffHook)が要求された			*/
		#define	MSG_CL1_ONLINE_EXIT			8	/* CLASS1の回線接続が終了した(OnHook)			*/
		#define	MSG_CL1_RCV_END				9	/* CLASS1の受信が終了した			*/
		#define	MSG_CL1_PRINT_REQ			10	/* ﾛｰｶﾙﾌﾟﾘﾝﾄの実行が要求された		*/
		#define	MSG_CL1_PRINT_END			11	/* ﾛｰｶﾙﾌﾟﾘﾝﾄが終了した				*/
		#define	MSG_CL1_SCAN_ACCEPT			12	/* ﾛｰｶﾙｽｷｬﾝの実行が受け入れられた	*/
		#define	MSG_CL1_SCAN_REJECT			13	/* ﾛｰｶﾙｽｷｬﾝの実行が拒否された		*/
		#define	MSG_CL1_SCAN_END			14	/* ﾛｰｶﾙｽｷｬﾝが終了した				*/
		#define	MSG_CL1_TEST_END			15	/* RS232Cﾃｽﾄが終了した				*/
		#define	MSG_CL1_INIT_END			16	/* Auto Initialize 終了				*/
 	/* Added by H.Kubo 1997/08/28, for +FRH command */
 		#define	MSG_CL1_FRH_ECM_READ_REQ		17 	/* +FRH コマンドからの高速読込要求 */
 		#define	MSG_CL1_FRH_ECM_ABORT_REQ		18 	/* +FRH コマンドからの高速読込中断 */
 		#define	MSG_CL1_FRH_ECM_OPEN_HIGH	19 	/* +FRH の高速オープン成功 */
 		#define	MSG_CL1_FRH_ECM_OPEN_FSK	20 	/* +FRH の高速オープン成功 */
 		#define	MSG_CL1_FRH_ECM_OPEN_FAIL		21 	/* +FRH の高速オープン失敗 */
		#define	MSG_CL1_FNET_RING				22	/* 1300Hz検出での呼び出し中 PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
		#define	MSG_CL1_FNET_TIMEOUT			23	/* 1300Hz検出タイムアウト PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
	/*-------------------------------------------------------------------------
	**	FROM_RS_CONTROL
	*/
	#define	FROM_RS_CONTROL				32
	/*	#define	RS_RX_TIMEOUT				1	*/	/* 一番最初のｷｬﾗｸﾀを受信する前にﾀｲﾑｵｰﾊﾞｰ	*/
	/*	#define	RS_FIRST_RCV				2	*/	/* RS232Cから一番最初のｷｬﾗｸﾀを受信	*/
		#define	RS_FIRST_ERR				3	/* RS232Cが最初のｷｬﾗｸﾀを受信するまでにRSｴﾗｰが発生した */
		#define	RS_CMD_RCV					4	/* ｺﾏﾝﾄﾞ受信が完了した					*/
		#define	RS_CMD_ERR					5	/* ｺﾏﾝﾄﾞ受信中にRSｴﾗｰ､ﾀｲﾑｱｳﾄが発生した	*/
		#define	RS_TIMEOUT					6	/* ﾓﾃﾞﾑからのﾃﾞｰﾀ受信ﾀｲﾑｵｰﾊﾞｰ	*/
		#define	RS_ABORT_CHAR				7	/* ｱﾎﾞｰﾄ･ｷｬﾗｸﾀを受信した	*/

	/*-------------------------------------------------------------------------
	**	FROM_CL1_FAXCOM
	*/
	#define	FROM_CL1_FAXCOM				33
		#define	MSG_CL1_FCOM_OK				1	/*	*/
		#define	MSG_CL1_FCOM_ERR			2	/*	*/

	/*-------------------------------------------------------------------------
	**	FROM_PRN_RESET_TASK
	*/
	#define FROM_PRN_RESET_TASK			34		/** プリンターリセット終了 By S.Kawasaki 1996/07/16 */
		#define MSG_PRN_RESET_END			1

	/*-------------------------------------------------------------------------
	**	FROM_PRN_WARMUP_TASK
	*/
	#define FROM_PRN_WARMUP_TASK		35
		#define MSG_PRN_WARMUP_END			1
		#define MSG_PRN_WAKEUP_END			2

#if (0)	/* By M.Tachibana 1997/06/07 */
**	/*-------------------------------------------------------------------------
**	**	FROM_SMPCOPY_TASK
**	*/
**	#define	FROM_SMPCOPY_TASK	X		/* By Y.Murata 1994/07/13 */
**		#define MSG_SMPCOPY_OK		0
**		#define MSG_SMPCOPY_NG		1
**		#define MSG_SMPCOPY_END		2
#endif

	/*-------------------------------------------------------------------------
	**	FROM_TEST_TEST
	*/
	#define	FROM_TEST_TEST				36			/* By S.K Apr.28,1994 */

	/*-------------------------------------------------------------------------
	**	FROM_UPDATE_DISPLAY
	*/
	#define	FROM_UPDATE_DISPLAY			37			/* By H.Y 1994/11/26 */

	/*-------------------------------------------------------------------------
	**	FROM_ONETOUCH_SHEET_CHECK
	*/
	#define	FROM_ONETOUCH_SHEET_CHECK	38		/* 1995/12/12 Eguchi */

	/*-------------------------------------------------------------------------
	**	FROM_DPR_UPLOAD_RX_TASK
	**	FROM_DPR_REMOTEFUNCEXECTASK
	*/
	#define	FROM_DPR_UPLOAD_RX_TASK		39			/* By J.Miyazaki 1996/08/08 */
	#define FROM_DPR_REMOTEFUNCEXECTASK	40			/* By J.Miyazaki 1996/08/10 */
		#define MSG_DPR_PCPRINTPAGETRANSEND	1		/* By J.Miyazaki 1996/08/10 */
		#define MSG_DPR_PCPRINTJOBTRANSEND	2		/* By J.Miyazaki 1996/08/10 */
		#define	MSG_DPR_PCPRINTPAGETRANSABORT	3	/* By J.Miyazaki 1996/08/24 */
		#define	MSG_DPR_PCPRINTJOBTRANSSTART	4	/* By J.Miyazaki 1996/09/14 */
		#define	MSG_DPR_PCRPRINTTESTSTART		5	/* By J.Miyazaki 1996/09/21 */
		#define	MSG_DPR_PCRTIMEOUT				6	/* By J.Miyazaki 1997/01/10 */

	/*-------------------------------------------------------------------------
	**	FROM_DPR_UPLOAD_TX_TASK
	*/
	#define	FROM_DPR_UPLOAD_TX_TASK		41			/* By J.Miyazaki 1996/08/13 */

	/*-------------------------------------------------------------------------
	**	FROM_SCN_MIRROR_MOVE_TASK
	*/
	#define	FROM_SCN_MIRROR_MOVE_TASK	42		/* ICHOU用  1996/06/28 s.takeuchi */
		#define	MSG_MIRROR_MOVE_OK			0		/* 正常終了 */
		#define	MSG_MIRROR_MOVE_ERROR		1		/* エラー終了 */

	/*-------------------------------------------------------------------------
	**	FROM_MULTI_TIMER
	*/
	#define	FROM_MULTI_TIMER			43		/* 1997/01/23 T.Nose */
		#define	   MSG_ND_WATCH_OH						1 /* added by H.Kubo 1998/11/21 */
		#define	   MSG_ND_SUSPEND_RESPONSE_TIMEUP		2 /* added by H.Kubo 1998/11/21 */
		#define	   MSG_ND_ACK_RESPONSE_TIMEUP			3 /* added by H.Kubo 1998/11/25 */

	/*-------------------------------------------------------------------------
	**	FROM_ROT_TASK
	*/
	#define FROM_ROT_TASK					44		/* By M.Kotani 97/03/27 */
		#define MSG_ROT_ERROR				0	/* 回転を実行する前に気づいたエラー(たとえば、搭載メモリ以上の原稿だったとか) */
		#define MSG_ROT_COMPLETE			1	/* 連続回転実行時に全ページ正常に回転できた */
		#define MSG_ROT_NO_DOCUMENT			2	/* 回転原稿なし終了 */
		#define MSG_ROT_CANCEL				3	/* 回転不要原稿 */
		#define MSG_ROT_MEMORY_OVER			4	/* 回転中にメモリオーバー */
		#define MSG_ROT_STOP				5	/* 何らかの要因で強制中断した */
		#define MSG_ROT_BUSY				6	/* 回転処理中のため回転できず */
		#define MSG_ROT_COMPOUND			7	/* ページ合成するため、回転せず */

	/*-------------------------------------------------------------------------
	**	FROM_DOC_OUT_TEST_TASK		原稿排出テストタスク
	*/
	#define FROM_DOC_OUT_TEST_TASK			45		/* T.Nose 1997/05/22 */
		#define MSG_DOC_OUT_COMPLETE		0		/* 正常終了 */
		#define MSG_DOC_OUT_FEED_ERROR		1		/* 原稿繰り込みエラー */
		#define MSG_DOC_OUT_COVER_ERROR		2		/* 原稿カバーオープンエラー */

	#define FROM_FAXCOM_OPTION			46
		#define	MSG_OPT_FAXCOM_END				0
		#define MSG_OPT_FAXCOM_ANS_CHANGE_KAMO	1	/* 1994/03/02 Y.Murata */
		#define MSG_OPT_FAXCOM_END_OFF_HOOK		2	/* 1994/06/20 Y.Murata 会話予約成立 or TEL/FAX待機 OFF_HOOK検出で通信終了 */

			/* SubMassage1		   */
			#define OPT_FAXCOM_OK					1	/* 1994/02/08 Y.Murata */
			#define OPT_FAXCOM_REDIAL				2	/* 1994/02/08 Y.Murata */
			#define OPT_FAXCOM_ERROR				3	/* 1994/02/08 Y.Murata */
			/* SubMassage2		   */
			#define MSG_OPT_FCOM_TEL1_OH			1	/* 1994/06/22 Y.Murata */
			#define MSG_OPT_FCOM_TEL2_OH			2	/* 1994/06/22 Y.Murata */
			#define MSG_OPT_FCOM_HOOK_KEY_OH		3	/* 1994/06/22 Y.Murata */
			/* SubMassage3		   */
			#define MSG_OPT_FCOM_HAVE_QUE				1	/* 未実行ｷｭｰ有り（発着時）1996/12/20 Y.Murata */

		#define	MSG_OPT_VOICE_REQ_START			3
		#define	MSG_OPT_VOICE_REQ_END			4
		#define OPT_DETECT						5	 /* '92,09,22  By Sakamoto */
		#define MSG_OPT_OK_EXIT					6	 /* '92,09,22  By Sakamoto */
		#define	MSG_OPT_RX_PRINT_PAGE			7
		#define	MSG_OPT_TEL_FAX_START			8
		#define	MSG_OPT_TEL_FAX_END				9
		#define MSG_OPT_FAXCOM_DISPLAY			10	/* 1994/02/08 Y.Murata */
		#define MSG_OPT_FAXCOM_RX_START			11	/* 1994/04/06 Y.Suzuki fcm_rcmp.c の最後で送信 */
		#define MSG_OPT_BUFFERING_PRINT_START	12	/* 1994/04/23 M.Tachibana */
		#define	MSG_OPT_FAXCOM_CLOSE_ERROR		13	/* 7/13/1994 Phase Scanner Close Error By S.K */
		#define	MSG_OPT_FAXCOM_PRINTER_ERROR	14	/* Jul.20.1994	竹内 */
		#define MSG_OPT_FAXCOM_TX_START			15
					/*	SubMessage1		*/
			#define	MSG_OPT_FAXCOM_NO_PAPER			1	/*	記録紙切れ (黒エンドマークも)	*/
			#define	MSG_OPT_FAXCOM_CUTTER_ERROR		2	/*	カッターエラー		*/
			#define	MSG_OPT_FAXCOM_PAPER_JAM		3	/*	ジャム				*/
			#define	MSG_OPT_FAXCOM_COVER_OPEN		4	/*	カバーオープン		*/
			#define	MSG_OPT_FAXCOM_NO_INK			5	/*	ドナー切れ			*/
			#define	MSG_OPT_FAXCOM_TH_HI_TEMP		6	/*	Ｔ／Ｈハイテンプ	*/

		#define	MSG_OPT_FAXCOM_END_TIME			16	/* 通信終了時間ﾀｲﾐﾝｸﾞ 1996/02/05 Y.M */
		#define	MSG_OPT_FAXCOM_T30_CONTINUE		17	/* GRAPE -> ORANGE Change 1996/03/11 Y.M */
		#define	MSG_OPT_FAXCOM_T30_CONT_ANSAM	18	/* GRAPE -> ORANGE Change ANSam Detect 1996/08/07 Y.M */
		#define	MSG_OPT_FAXCOM_OPTION_REC_REQ	19	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ受信要求 */
		#define	MSG_OPT_DETECT_CI				20	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ CI検出 1996/11/12 Y.Murata */
		#define	MSG_OPT_DETECT_CI_TIMEUP		21	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ CIﾀｲﾑｵｰﾊﾞｰ 1996/11/12 Y.Murata */
		#define	MSG_OPT_FAXCOM_SET_JOURNAL		22	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ ｼﾞｬｰﾅﾙｾｯﾄ要求 1996/12/02 Y.Murata */
		#define MSG_OPT_FAXCOM_START_TIME		23	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ通信開始 1996/12/18 */
		#define MSG_OPT_FAXCOM_TEL1_OFF_HOOK	24	/* TEL1  OFF HOOK 検出 1997/01/06 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_ON_HOOK_EXIT		25  /* TEL1/TEL2/HOOK KEY ON HOOK 検出NCU_TEL終了 1997/01/06 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_ON_HOOK_CONT		26  /* TEL1/TEL2/HOOK KEY ON HOOK 検出NCU_TEL終了 1997/01/06 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_INPUT_HOOK_KEY   27	/* HOOK KEY 入力検出  1997/01/06 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_INPUT_HOLD_KEY   28	/* HOLD KEY 入力検出  1997/01/06 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_DET_TRANS_EXIT	29	/* 転送受信／仮着信後の着信 NCU_TEL終了 1997/01/20 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_CREATE_GRS_TASK	30  /*  FAX側の擬似ベル鳴動タスク起動指示 1997/01/28 BY N.Sakamoto */
		#define	MSG_OPT_FAXCOM_DELETE_GRS_TASK	31  /*  FAX側の擬似ベル鳴動タスク削除指示 1997/01/28 BY N.Sakamoto */
		#define	MSG_OPT_FAXCOM_START_GRS_BELL	32  /*  FAX側の呼出ブザー鳴動開始指示 	1997/01/28 BY N.Sakamoto */
		#define	MSG_OPT_FAXCOM_STOP_GRS_BELL	33  /*  FAX側の呼出ブザー鳴動停止指示 	1997/01/28 By N.Sakamoto */
		#define	MSG_OPT_FAXCOM_DETECT_RING		34	/*  Class1 Ring検出 1997/02/14 BY N.Sakamoto  */
		#define MSG_OPT_FAXCOM_AUTO_DIAL_END	35	/*  Class1 AutoDial処理終了 1997/02/17 By N.Sakamoto */
		#define MSG_OPT_FAXCOM_GO_ONHOOK_END	36	/*  Class1  1997/02/18 By N.Sakamoto */
		#define MSG_OPT_FAXCOM_ANSWERCALLSTART	37	/*  Class1  1997/02/18 By N.Sakamoto */
		#define MSG_OPT_FAXCOM_CED_TX_END		38	/*  Class1  1997/02/18 By N.Sakamoto */
		#define MSG_OPT_FAXCOM_DETECT_NOISE		39	/*  Class1  1997/02/25 By N.Sakamoto */

		#define MSG_OPT_EXEC_ERROR				60	/** ｷｭｰ,ｺﾏﾝﾄﾞﾌｧｲﾙ獲得異常 */


					/*	SubMessage1		ATD_DEF.H */
		/*-------------------------------------------------------------------------------------------
			#define		AD_OK					0
			#define		AD_LOCAL_BUSY			1		/@ 発着衝突があった @/
			#define		AD_REMOTE_BUSY			2		/@ ﾋﾞｼﾞｰﾄｰﾝ､ｺﾝｼﾞｪｽｼｮﾝﾄｰﾝを検出した @/
			#define		AD_STOPPED				3		/@ ｽﾄｯﾌﾟ･ｷｰが押された @/
			#define		AD_DESTROYED			4		/@ ﾊﾞｯﾌｧのﾀﾞｲｱﾙﾃﾞｰﾀが壊れている @/
			#define		AD_OK_DSE				5		/@ 極反検出した @/
			#define		AD_DIAL_EMPTY			6		/@ ﾊﾞｯﾌｧにﾀﾞｲｱﾙﾃﾞｰﾀが登録されていない @/
			#define		AD_TIME_OVER			7		/@ 制限時間内にﾄｰﾝが検出できなかった @/
			#define		AD_NO_DIAL_TONE			8		/@ ﾀﾞｲｱﾙﾄｰﾝを検出できない @/
			#define		AD_NO_CURRENT_LOOP		9		/@ ﾙｰﾌﾟ電流が無い @/
			#define		AD_DETECT_RINGBACKTONE	10
			#define		AD_OK_CED				11		/@ CED検出 for FRA  95/03/17 by M.HARADA @/
			#define		AD_OK_ANSWER_TONE		12		/@ V25ｱﾝｻｰﾄｰﾝ検出 @/
			#define		AD_OK_DIS				13
		----------------------------------------------------------------------------------------------*/

	/* For V8/V34 abort code. Added by H.Kubo 1997/06/30 */
	#define FROM_ABCODE						47

	/* For R288F modem chip. Added by H.Kubo 1997/06/30 */
	#define FROM_MDM_DETECT_V21FLAG			48

	/* For R288F modem chip. Added by H.Kubo 1997/07/08 */
	#define FROM_FAXCOM_DUMMY				49			/* 1997/02/24 Y.Murata */

	#define	FROM_V34_DETECT_V25TONE			50			/* このへんから追加 1995/12/08 Y.Murata */
		#define	V25_ANSAM_TONE					1
		#define	V25_ANS_TONE					2

	#define	FROM_V34_V8CONTROL				51
		#define	V8_COMPLETE						1
		#define	V8_NG							2

	#define FROM_V34_TX_HANDSHAKE_MONITOR	52
	#define FROM_V34_RX_HANDSHAKE_MONITOR	53

	#define FROM_V34_DETECT_V8CI			54			/* 1996/03/15 Y.M */
		#define V8_CI_DETECT					1

	#define FROM_FCM_WWDETECTTASK			55			/* 1996/08/21 Y.Murata */
		#define WWDETECT_EXIT					1

	/*-------------------------------------------------------------------------
	**	FROM_CIPHER_TASK
	*/
	#define FROM_CIPHER_TASK				56		/* By Y.Suzuki 1997/07/23 */
		#define MSG_OPT_CIPHER_MEM_ERROR	0	/* 暗号化メモリオーバーエラー */
		#define MSG_OPT_CIPHER_COMPLETE		1	/* 暗号化正常終了 */
		#define MSG_OPT_DECIPHER_COMPLETE	2	/* 復号化正常終了 */
		#define MSG_OPT_DECIPHER_MEM_ERROR	3	/* 復号化メモリオーバーエラー */
		#define MSG_OPT_CIPHER_ERROR		4	/* 暗号化エラー */
		#define MSG_OPT_DECIPHER_ERROR		5	/* 復号化エラー */
		#define MSG_OPT_ALIROO_ERROR		6	/* ALIROOエラー */
		#define MSG_OPT_CIPHER_DECODE_ERROR	7	/* 暗号化デコードエラー */
		#define MSG_OPT_DECIPHER_DECODE_ERROR	8	/* 復号化デコードエラー */
		#define MSG_OPT_DECIPHER_KEY_ERROR	9	/* 復号化キーエラー */
		#define MSG_OPT_DECIPHER_FROM_OPR	10	/* 復号化継続／中止 */
		#define MSG_OPT_CIPHER_STOPON		11	/* 処理中ＳＴＯＰキーＯＮ */
		#define MSG_OPT_CIPHER_PRT_RESTART  12	/* 復元化プリントリスタート */
		#define MSG_OPT_CIPHER_DOC_CLEAR	13	/* 1ページ復元時、スクランブル原稿消去ＯＰＲ用 */

	/*-------------------------------------------------------------------------
	**	FROM_PRN_MANUAL_DOCIN_TASK
	*/
	#define FROM_PRN_MANUAL_DOC_IN_TASK		57	/* By M.Tachibaba 1997/11/17 */
		#define MSG_PRN_MANUAL_DOC_IN_OK		1
		#define MSG_PRN_MANUAL_DOC_IN_ERROR		2


	#define FROM_CODEC_CTX					58
		#define	MSG_CDC_REQUEST_NEW_LINE		0x0001
		#define	MSG_CDC_REQUEST_PAGE_END		0x0004
		#define	MSG_LST_ACK_NEW_LINE			0x0010
		#define	MSG_LST_EMPTY_NEW_LINE			0x0020
		#define	MSG_LST_ACK_PAGE_END			0x0040

	/*-------------------------------------------------------------------------
	**	FROM_INF_TASK
	**	InternetFAXﾒｲﾝﾀｽｸからのﾒｯｾｰｼﾞ
	**	1998/03/10  by Y.Tanimoto
	*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	#define	FROM_INF_TASK						59
		#define	MSG_INF_EXIT					0	/*  1998/04/03 Eguchi */
		#define	MSG_INF_COMMAND_COMPLETE		1	/*	メール通信終了						*/
		#define	MSG_INF_RX_ONE_PAGE_END			2	/*	1ページ受信完了						*/
		#define	MSG_INF_RX_ONE_FILE_END			3	/*	1メール受信完了						*/
		#define	MSG_INF_TEST_END				4	/*	テストファンクション終了			*/
		#define	MSG_INF_DISPLAY					5	/*	表示切り替え要求					*/
		#define	MSG_INF_ERASE_ACCOUNT_DATA_END	6	/*	ボード内のユーザーデータ消去完了	*/
		#define	MSG_INF_INITIALIZE_COMPLETE		7	/*	設置オペレーション終了				*/
		#define	MSG_INF_INITIALIZE_ERROR		8	/*	設置オペレーション終了				*/

	#define	FROM_INF_RSWRITE_TASK	60		/*  1998/04/03 Eguchi */
	#define	FROM_INF_RSREAD_TASK	61		/*  1998/04/03 Eguchi */
		#define	MSG_INF_RS_EXIT_OK		0		/* 1998/04/03 Eguchi */
		#define	MSG_INF_RS_OPEN_OK		1		/* 1998/04/03 Eguchi */
		#define	MSG_INF_RS_OPEN_ERROR	2		/* 1998/04/03 Eguchi */
		#define	MSG_INF_RS_EXIT_DETECTRXERR	3	/* 1998/08/10 Eguchi */

#endif

#if defined(CHN)			  /* By S.Wang 1995/08/22 */
/**********************************************************************

		95/1/18	 by BU
	for Print_PowerOff_Notice

**********************************************************************/
	#define Secure_Left								1
	#define Secure_Right							2
#endif
	#define	FROM_NCU_ND						62 /* ナンバーディスプレイ受信処理用 added by H.Kubo 1998/08/26 */
		#define	MSG_NCU_ND_RX_V23_SUCCESS	1
		#define	MSG_NCU_ND_RX_V23_FAIL		2
		#define	MSG_NCU_ND_RX_V23_TIMEOUT	3
		#define	MSG_NCU_ND_RX_V23_NO_DATA	5
		#define	MSG_NCU_ND_DETECT_DSE		4
		#define	MSG_NCU_ND_RX_V23_NO_DATA	5

	#define FROM_SCN_GETSHADE				63
		#define MSG_SCN_SHADE_OK			1		/* 正常終了 */
		#define MSG_SCN_SHADE_STOPSW_ON		2		/* 蓄積停止処理 */
		#define MSG_SCN_SHADE_MAXLINE_OVER	3		/* 最大読取り長を越えた */
		#define MSG_SCN_SHADE_DOC_ERROR		4		/* 原稿セットエラー */
		#define MSG_SCN_SHADE_NO_DOCUMENT	5		/* 原稿無し */
		#define MSG_SCN_SHADE_COVER_OPEN	6		/* スキャナー・カバー・オープン */
		#define MSG_SCN_SHADE_LAMP_ERROR	7		/* ランプ・エラー */

	#define FROM_PRN_REALTIMECOPY_TASK		64
		#define MSG_PRN_REALTIMECOPY_END					1
		#define MSG_PRN_REALTIMECOPY_CONTI					2	/* 表示更新用 */
		#define MSG_PRN_REALTIMECOPY_ERROR					3

	#define FROM_SCN_REALTIMECOPY_TASK		65
		/* メッセージ詳細はFROM_DOCSTOREと同じものを使用します */

#if defined (KEISATSU) /* 警察FAX 05/09/16 石橋正和 */
	#define FROM_MDM_RXFSKFRAMECONTROLTASK	66
#endif

#endif
