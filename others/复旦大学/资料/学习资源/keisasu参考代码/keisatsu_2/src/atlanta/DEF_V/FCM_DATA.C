
/*************************************************************************
	module		:[通信大域変数]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1)	松竹桜の<faxdata.c>と<g3_d.c>からコピーして，ＮＴＴ仕様の部分を削除
		2)	大機能間大域変数は"SYS_"をつけて"sys_data.c"へ移動
		3)	大域変数をサイズ別に確保
		4)	SATSUKI/LAVENDRでは内蔵RAM(512Byte)に実体があります
		修正履歴
		1.一括送信送信済み頁数追加 94/9/22 鈴木
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/15]
	author		:[竹内茂樹]
*************************************************************************/

/*########################################################*/
/* 警告！！												  */
/* １バイトデータとそうでないデータをちゃんと分けましょう */
/*--------------------------------------------------------*/

/*--------------------------*/
/*	インクルードファイル達	*/
/*--------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysmax.h"				/* 最大値 */
#include	"\src\atlanta\define\message.h"			/* メッセージ構造体 */
#include	"\src\atlanta\define\syscomf.h"			/* コマンド・ファイル構造体 */
#include	"\src\atlanta\define\sysbatch.h"			/* バッチ・ファイル構造体 */
#include	"\src\atlanta\define\sysjrnl.h"			/* ジャーナル構造体 */
#include	"\src\atlanta\define\mem_def.h"			/* メモリ・ファイル構造体 */
#include 	"\src\atlanta\define\fcm_def.h"
/*------------*/
/* デバッグ用 */
/*------------*/

/* unsigned char	FaxDebugDCSSW  = 0;			*/	/** もういらない **/
/* unsigned char	FaxTelDebugSW  = 0;			*/	/** もういらない **/
/* unsigned char	VoiceReceiveDebugFlag  = 0;	*/
/* unsigned int	FaxPhaseC_D_Time = 200;			*//** もういらない **/
UWORD	FaxComPhaseStatus = 0;
/* unsigned int	FaxDebugPIXStartTime = 0;		*/
/* unsigned int	FaxDebugPIXENDTime = 0;			*/
/* int				mpl_address = 0;			*/

/*==========================================*/
/*		  １バイトデータ達					*/
/*==========================================*/

UBYTE	OwnMakerCode = 0;					/*	自機メーカーコード	村田A2	ＦＸ45	*/

UBYTE	PollingTxType = 0;					/*	ポーリング送信原稿種別	皐月はセット不要	*/

UBYTE	FaxComRxType = 0;					/*	受信原稿種別				*/

UBYTE	FaxTxCommand = 0;					/*	確定送信コマンド	相手機中継同報機能あり-->YES	*/

UBYTE	FinalTxMode = 0;					/*	確定送信モード				*/
UBYTE	FinalRxMode = 0;					/*	確定受信モード				*/

UBYTE	TxSmType = 0;						/*	送信方法	スキャナ、メモリ、カバー、ＲＣＲ	*/
UBYTE	RxPmType = 0;						/*	受信方法	プリンタ、メモリ	*/

UBYTE	DisplayFirstMode = 0;				/*	送信モードを表示させるためのフラグ	YES/NO	*/

UBYTE	FirstTxMode = 0;					/*	送信モード（次ページ目のモード）	*/
UBYTE	TxMode = 0;							/*	送信モード（最後に送ったページのモード）	*/
UBYTE	RxMode = 0;							/*	受信モード（最後に受けたページのモード）	*/
UBYTE	TxModeMethod = 0;					/*	送信モード（インチ／ミリ）23.Mar'94 Y.Suzuki	*/
UBYTE	RxModeMethod = 0;					/*	受信モード（インチ／ミリ）23.Mar'94 Y.Suzuki	*/

UBYTE	TxWidth = 0;						/*	確定送信原稿幅	*/
UBYTE	RxWidth = 0;						/*	確定受信原稿幅	*/
UBYTE	DocWidth = 0;						/*	原稿幅			*/

UBYTE	FaxRxAvailableLength = 0;			/*	受信可能最大原稿長	*/
UBYTE	FaxTxMaxLength = 0;					/*	確定送信原稿長		*/
UBYTE	FaxRxMaxLength = 0;					/*	確定受信原稿長		*/

/*	unsigned char	VoiceCallModeRequest = 0;		**	会話予約指示	** 竹内 Jul.07.1994 */
/*	unsigned char	VoiceCallFormedFlag = 0;		**	会話予約成立	** 竹内 Jul.07.1994 */

UBYTE	TxRCR_Flag = 0;						/*	相手機からの「受領証要求」フラグ	YES/NO 受領証送信時--YES	*/
													/*	TxReceiptConfirmationReportFlag → TxRCR_Flagに変更	by Bamboo,Jan.6'94	*/
UBYTE	TxReceiptRequestFlag = 0;			/*	「受領証送信」フラグ(受信側から送信側の能力をチェック)	*/

UBYTE	FaxComPerformingFlag = 0;			/*	「通信中」フラグ	YES/NO	*/
UBYTE	FaxComTxPerformingFlag = 0;			/*	「送信中」フラグ	*/
UBYTE	FaxComRxPerformingFlag = 0;			/*	「受信中」フラグ	*/

UBYTE	TxECM_Mode = 0;						/*	確定ＥＣＭ送信指定	*/
UBYTE	RxECM_Mode = 0;						/*	確定ＥＣＭ受信指定	*/
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
UBYTE	TxECM_AbilitySram = 0;				/*	ＥＣＭ送信ＯＮ／ＯＦＦ指定	*/
UBYTE	RxECM_AbilitySram = 0;				/*	ＥＣＭ受信	*/
#else
UBYTE	TxECM_Ability = 0;					/*	ＥＣＭ送信ＯＮ／ＯＦＦ指定	*/
UBYTE	RxECM_Ability = 0;					/*	ＥＣＭ受信	*/
#endif

UBYTE	RxFirstTimeCompatibleCheckFlag = 0;	/*	受信コンパチブルチェック回数	フレーム取り込み要/不要に使用	*/

UBYTE	TxRetrainingFlag = 0;				/*	「再トレーニング」フラグ	*/

UBYTE	TxRetransmitFlag = 0;				/*	「再送信」フラグ	*/

UBYTE	TxModeChangedFlag = 0;				/*	「モード変更」フラグ	*/
UBYTE	RxModeChangeRequestedFlag = 0;		/*	「受信モード変更要求」フラグ	*/

UBYTE	TxPageDataSetFlag = 0;				/*	「ページオープン中（済み）」フラグ	*/

UBYTE	RxWholePageCompletedFlag = 0;		/*	「１物理ページ受信完了」フラグ	*/

UBYTE	RxEOM_ReceiveFlag = 0;				/*	「ＥＯＭ受信」フラグ	*/
UBYTE	RxEOP_ReceiveFlag = 0;				/*	「交信終了許可（ＥＯＰ受信）」フラグ	*/
UBYTE	RxEOR_ReceiveFlag = 0;				/*	ＥＯＲ受信済みフラグ	*/

UBYTE	TxCoverPageFlag = 0;				/*	カバーページ送信フラグ	*/

UBYTE	AttemptTxBaudRate = 0;				/*	試行送信ボーレイト	*/
UBYTE	AttemptRxBaudRate = 0;				/*	試行受信ボーレイト	*/

UBYTE	TxBaudRate = 0;						/*	確定送信ボーレイト	*/
UBYTE	RxBaudRate = 0;						/*	確定受信ボーレイト	*/

UBYTE	AvailableTxBaudRate = 0;			/*	機器の送信可能なボーレイト	*/
UBYTE	AvailableRxBaudRate = 0;			/*	機器の受信可能なボーレイト	*/

UBYTE	TxInterMemoryFlag = 0;				/*	メモリ間通信を示す	YES/NO	*/
UBYTE	RxPrinterDirectFlag = 0;			/*	ダイレクトプリンタ受信を示す	*/

/*	unsigned char	TxPageOpenedFlag  = 0;	*/	/*	送信ファイルオープン済みフラグ	*/
/*	unsigned char	RxPageOpenedFlag = 0;	*/	/*	受信ファイルオープン済みフラグ (0:Closed/1:Opened/2:DualOpened)	*/

UBYTE	TxCodingMethod = 0;					/*	確定送信符号化方式	*/
UBYTE	RxCodingMethod = 0;					/*	確定受信符号化方式	*/
UBYTE	AvailableTxCodingMethod = 0;		/*	機器の送信可能な符号化方式	*/
UBYTE	AvailableRxCodingMethod = 0;		/*	機器の受信可能な符号化方式	*/

UBYTE	JBIG_Ability = 0;					/* TEST JBIG符号化能力 1997/01/28	By T.Yamaguchi */

UBYTE	TxMSE_Method = 0;					/*	確定送信ＭＳＥ方式	*/
UBYTE	AvailableTxMSE_Method = 0;			/*	機器の送信可能なMSE方式	*/
UBYTE	AvailableRxMSE_Method = 0;			/*	機器の受信可能なＭＳＥ方式	*/

UBYTE	NextScanningMode = 0;				/*	送信原稿の指定線密度　int-->char 鈴木 94/1/19	*/

UBYTE	AttemptRxModeSwitch = 0;			/*	受信モード	*/

UBYTE	AvailableTxMinimumScanningTime = 0;	/*	機器の送信可能な1ライン最小電送時間	*/
UBYTE	AvailableRxMinimumScanningTime = 0;	/*	機器の受信可能な１ライン最小電送時間	*/
UBYTE	TxMinimumScanningTime = 0;			/*	確定１ライン最小電送時間（送信）	*/
UBYTE	RxMinimumScanningTime = 0;			/*	確定１ライン最小電送時間（受信）	*/

UBYTE	TxPageFinishStatus = 0;				/*	送信終了の状況	*/
UBYTE	RxPageFinishStatus = 0;				/*	受信終了の状況	*/

/* unsigned char	RxRTN_Flag;	 * 竹内 Feb.13'94 */	/*	現在受信ページの画質不良フラグ（画質不良のときセットする）	*/

UBYTE	ECM_PageCounter = 0;				/*	ＥＣＭポストメッセージのページカウンタ	*/
UBYTE	ECM_BlockCounter = 0;				/*	ＥＣＭポストメッセージのブロックカウンタ	*/
UBYTE	ECM_FrameCounter = 0;				/*	ＥＣＭポストメッセージのフレームカウンタ	*/
UBYTE	ECM_FirstFrameCounter = 0;			/*	受信した１部分ページのフレーム数　現在受信中の部分ページの全フレーム数 */
													/*	（１部分ページの初回のみＰＰＳのＦＣをコピー）	*/
UBYTE	FaxECM_ResponseTimeFlag = 0;		/*	ＥＣＭ応答受信の待ち時間切り替えフラグ	*/
UBYTE	RxECM_RetransmittedFlag = 0;		/*	ＥＣＭの１部分ページ１回目受信フラグ	*/
UBYTE	RxECM_PixTimeoutFlag = 0;			/*	ＥＣＭ受信でノイズによるタイムアウト対策(回線断しないで再送要求する)	*/

UBYTE	AvailableRxResolution = 0;			/*	機器の受信可能な受信線密度	*/

UBYTE	TxMemoryFileItem = 0;				/*	メモリ送信を行う原稿のファイルアイテム	*/
UBYTE	TxMemoryFileBoxNumber = 0;			/*	1997/02/24	By T.Yamaguchi	*/
UBYTE	FaxComFileItem = 0;					/*	通信ファイルアイテム	*/
UBYTE	FaxComFileNumber = 0;				/*	通信ファイルナンバー	*/
UBYTE	FaxComFilePage = 0;					/*	通信ファイルページ	*/

UBYTE	RelayedCommandNo = 0;				/*	中継配信指示受信（中継同報の子機）の時に */
													/*	展開したコマンドファイルナンバー	*/
UBYTE	NonStdFrmName = 0;					/*	MDM_Buffer[][]上へ受信した非標準各フレームの名前	*/
UBYTE	ID_FrmName = 0;						/*	MDM_Buffer[][]上へ受信したＩＤ各フレームの名前	*/
UBYTE	StdFrmName = 0;						/*	MDM_Buffer[][]上へ受信した標準各フレームの名前	*/


UBYTE	DIS_ReceivedFlag = 0;				/*	ＤＩＳ（ＤＣＳ）関係	*/

UBYTE	DiagByteCounter = 0;				/*	リモート診断関係	*/

UBYTE	TxMethodFlag = 0;					/*	送信方式確定	*/
UBYTE	BaudrateFlag = 0;					/*	ボーレイト確定	*/

/* unsigned char	CNG_DetectFlag = 0;			*/		/*	擬似リングバックトーン送出中のＣＮＧ検出済みフラグ	*/
UBYTE	FaxTelOffHook = 0;					/*	会話予約中にオフフック検出済みフラグ	*/
UBYTE	FaxTelOffHookTEL1Flag = 0;			/*	TEL1 オフフック検出フラグ */
UBYTE	FaxTelOffHookTEL2Flag = 0;			/*	TEL2 オフフック検出フラグ */
UBYTE	OffHookDetectStopFlag = 0;			/*	オフフック検出ストップフラグ 1994/01/19 Y.Murata */
/* unsigned char	GenerateRingSignalStopFlag = 0;	*/	/*	擬似ベル鳴動中のストップキー入力フラグ	*/

UBYTE	TxSpeedHandshakeFlag = 0;			/*	短縮ハンドシェーク用(短縮ハンドシェーク送信を実行する送信) YES/NO */
UBYTE	RxSpeedHandshakeFlag = 0;			/*	短縮ハンドシェーク用(短縮ハンドシェーク受信をおこなった) */
UBYTE	SDCS_TransmitFlag = 0;				/*	短縮ハンドシェーク用(モデムに短縮ハンドシェーク送信であることを示す) */
UBYTE	PartnerSpeedHandshakeAbility = 0;	/*	短縮ハンドシェーク用(相手機に短縮ハンドシェーク機能がある) */
#if (PRO_SPEED_EX == ENABLE)
UBYTE	PartnerSpeedHandshakeExAbility	= 0;/** 相手機が新短縮ハンドシェーク機能の有無を示すフラグ */
UBYTE	ArrivalSignalToneTransmitFlag = 0;	/** 着信トーン送出を示すフラグ */
#endif
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
UBYTE	EOM_received = 0;
UBYTE	PartnerSpeedModeChangeAbility = 0;	/*	相手機が短縮ハンドシェーク（モード変更）受信能力の有無を示す 96/06/01 By T.Yamaguchi */
#endif
UBYTE	Partner300dpiAbility = 0;			/** 相手機がR12*15.4L/mm受信能力の有無を示すフラグ */
UBYTE	PartnerEFineAbility = 0;			/** 相手機がR12*11.55L/mm受信能力の有無を示すフラグ */
UBYTE	PartnerCipherAbility = 0;			/** 相手機暗号化能力の有無を示すフラグ	1997/06/18  By T.Yamaguchi */
UBYTE	FaxComTXorRX_Sign = 0;				/*	送信／受信識別フラグ　送信、受信、リモート診断識別	*/

#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
UBYTE	FaxComTXorRX_Flag = 0;				/*	送信／受信識別フラグ　送信、受信、リモート診断識別	*/
#endif /* defined (KEISATSU) */

UBYTE	PartnerAbility0	 = 0;				/*	メモリスイッチＢ０(SYS_MemorySwitch[10])のコピー	*/
UBYTE	PartnerAbility1	 = 0;				/*	メモリスイッチＢ１(SYS_MemorySwitch[11])のコピー	*/
UBYTE	PartnerAbility2	 = 0;				/*	メモリスイッチＢ２(SYS_MemorySwitch[12])のコピー	*/
UBYTE	PartnerAbility3	 = 0;				/*	メモリスイッチＢ２(SYS_MemorySwitch[12])のコピー	*/

UBYTE	AD_Result	   = 0;					/*	オートダイアラー戻り値	*/
UBYTE	AD_Result_Flag = 0;					/*	???		*/

UBYTE	RxJunkMailFlag = 0;					/*	ジャンクメイル受信フラグ　YES/NO　ジャンクメイルエラー時--YES	*/

UBYTE	HurryUpFaxComFlag = 0;				/*	通信の優先順位を強制的に高くするフラグ	*/

UBYTE	GrayModeFlag = 0;					/*	ファイン、中間調の場合--YES	*/

UBYTE	ScanTxGrayMode = 0;					/* KIRI スキャナ送信 でかつ相手の能力 400DPI ｲﾝﾁ なら H_FINE 94/10/19 Y.S */

UBYTE	UpdateTxPageMode = 0;				/*	ページ数更新時の更新項目			*/
UBYTE	FaxCompatibleErrorCode = 0;			/*	詳しいコンパチエラーコード			*/

UBYTE	TxOptionFCF = 0;					/*	ポストメッセージ送信拡張ＦＣＦフレーム	*/
UBYTE	TxFCF = 0;							/*	ポストメッセージ送信ＦＣＦフレーム		*/
UBYTE	RxOptionFCF = 0;					/*	ポストメッセージ受信拡張ＦＣＦフレーム	*/
UBYTE	RxFCF = 0;							/*	ポストメッセージ受信ＦＣＦフレーム		*/

UBYTE	RxFrameMessage1 = 0;				/*	受信フレーム種別	*/
UBYTE	PRI_Q_RxFlag = 0;					/*	ＰＲＩ＿Ｑ受信フラグ	*/
UBYTE	PRI_Q_RxCount = 0;					/*	ＰＲＩ＿Ｑ受信カウンタ	*/

UBYTE	ReceiveResponseFlag = 0;			/*	応答受信ありなしフラグ		*/
UBYTE	ReceiveCommandFlag = 0;				/*	命令受信ありなしフラグ		*/

UBYTE	UpdatePageInformationFlag = 0;		/*	送信ページ情報を更新する／しないフラグ	*/
UBYTE	FSK_FirstReceivedFlag = 0;			/* 相手機がＦＡＸであると確定した 96/05/17 By T.Yamaguchi */

UBYTE	TimerFlag = 0;						/*	タイマー	*/
UBYTE	ReceiveCommandFlagDetectFlag = 0;	/*	HDLC関係	*/
UBYTE	TransmitCommandFlag			 = 0;	/*	HDLC関係	*/
UBYTE	ReceiveCommandTimerStartFlag = 0;	/*	HDLC関係	*/

UBYTE	ForwardReceiveFlag = 0;				/* 転送受信 */
UBYTE	BackUpForwardReceiveFlag = 0;		/* 転送受信バックアップ */
UBYTE	FaxNetReceiveFlag  = 0;				/* Ｆネット着信 */

UBYTE	DelWaitFlag = 0;					/* FaxTel 1994年6月8日 */
UBYTE	FaxTelDelCheckFlag = 0;				/* FaxTel 1994年6月8日 */

UBYTE	DCS_TxCount = 0;					/*	unsigned short -> UBYTEに変更		*/

/*--------------------------------------------------------------------*/
/*	 ｺﾏﾝﾄﾞﾌｧｲﾙ,ﾊﾞｯﾁﾌｧｲﾙの内容をｾｰﾌﾞしとくためのもの					  */
/*		通信起動時(FCM_Main())にセットされる						  */
/*						   1994/01/19  Y.Murata						  */
/*--------------------------------------------------------------------*/
UBYTE	CommandFileStatus = 0;				/*	使用状況	*/
UBYTE	CommandFileOptionItem = 0;			/*	通信種別	*/
UBYTE	CommandFileConfirmationReport = 0;	/*	通信証	*/
UBYTE	CommandFileTitleMessage = 0;		/*	タイトルメッセージ	*/
UBYTE	*CommandFileDirectDial = 0;			/*	直接ダイヤル番号	*/
#if (PRO_PIN_ACCESS == ENABLE)
UBYTE	*CommandFilePinNumber = 0;			/*	ｺﾏﾝﾄﾞﾌｧｲﾙのＰＩＮ番号 '95.12.22 t.yamaguchi */
UBYTE	CommandFilePinAccessMode = 0;		/* ＰＩＮアクセスモード 1996.01.09 T.yamaguchi */
#endif
/* UBYTE	CommandFilePage = 0;			/@ 送信ページ 1997/05/09  By T.Yamaguchi */
UWORD	CommandFilePage = 0;				/* 送信ページ */
UWORD	CommandFileDepartmentCode = 0;		/* 部門管理コード */
UBYTE	CommandFileAbility = 0;				/* 通信予約の付加情報(FX) 1994/11/01 Y.Murata */
/*#if (PRO_F_CODE == ENABLE)*/	/* 1997/01/10  By T.Yamaguchi */
UBYTE	CommandFileFcodePosition = 0;		/* ｺﾏﾝﾄﾞﾌｧｲﾙのＦコードﾃﾞｰﾀの格納されているﾎﾟｼﾞｼｮﾝを格納 */
/*#endif*/
/* unsigned char	T30PrintStopFlag = 0;			*/	/*	Ｔ３０モニタ印字禁止フラグ	(松竹桜のバグの対応) */

/*---------------------------------------------------------------------*/
/*	 リモートＦＡＸ設定状態フラグ									   */
/*		通信起動時 FCM_initializeFaxCom()で CHK_RemoteFaxON()の値を	   */
/*		セーブする。												   */
/*	 1994/01/19	 Y.Murata											   */
/*---------------------------------------------------------------------*/
UBYTE	RemoteFaxON_Flag = 0;				/*	リモートＦＡＸ設定状態 */

/*---------------------------------------------------------------------*/
/*	 リモートＦＡＸ自動プリント設定状態フラグ						   */
/*		通信起動時 FCM_initializeFaxCom()で CHK_RemoteFaxPRN()の値を   */
/*		セーブする。												   */
/*	 1994/02/04	 Y.Murata											   */
/*---------------------------------------------------------------------*/
UBYTE	RemoteFaxPRN_Flag = 0;				/*	リモートＦＡＸ自動プリント設定状態 */

/*---------------------------------------------------------------------*/
/*	 リモートＦＡＸ自動メモリ消去設定状態フラグ						   */
/*		通信起動時 FCM_initializeFaxCom()で CHK_RemoteFaxDEL()の値	  */
/*		セーブする。												   */
/*	 1994/02/04	 Y.Murata											   */
/*---------------------------------------------------------------------*/
UBYTE	RemoteFaxDEL_Flag = 0;				/*	リモート自動メモリ消去ＦＡＸ設定状態 */


/*---------------------------------------------------*/
/*	ＦＸ 村田独自機能有無の判断に使用				 */
/*---------------------------------------------------*/
UBYTE	MakerCodeRxFlag = 0;				/*	「村田メーカコード受信」フラグ	YES/NO	*/
UBYTE	FX_CodeRxFlag = 0;					/*	「ＦＸメーカコード受信」フラグ	YES/NO	*/

UBYTE	NonStandardID[SYS_TTI_ID_MAX]			  = {0};	/*	交信相手機の村田（／ＯＥＭ）ＩＤ		*/
UBYTE	StandardID[SYS_ID_MAX]					  = {0};	/*	交信相手機の標準ＩＤ					*/
UBYTE	BackUpStandardID[SYS_ID_MAX]			  = {0};	/*	交信相手機の標準ＩＤ（バックアップ）	*/
UBYTE	TxResponsedRTN_PageSign[SYS_ERROR_PAGE]	  = {0};	/*	RTN/PIN を応答された送信ページ（ビット指定）	*/
UBYTE	RelayedTxDocumentStatus[SYS_COM_FILE_MAX] = {0};	/*	中継配信原稿の状態を表す'94/1/26鈴木	*/
UBYTE	RelayedReportPrintStatus[SYS_COM_FILE_MAX]= {0};	/*	不達通知のプリント状況	竹内 Apr.07.1995	*/

/*----------------------------------------------------------*/
/*	受信原稿ポーリング送信種別								*/
/*	受信原稿ﾎﾟｰﾘﾝｸﾞではない		0							*/
/*	RX_DOC_POLLING_TX			1							*/
/*	SECURE_DOC_POLLING_TX		2							*/
/*	FIP_DOC_POLLING_TX			3							*/
/*----------------------------------------------------------*/
UBYTE	RxDocumentPollingTxFlag = 0;

/*------------------------------------------*/
/*	PRN_PreOpen()済かどうかの識別フラグ		*/
/*		竹内	Apr.22.1994					*/
/*------------------------------------------*/
#if (PRO_PRINTER_RX == ENABLE)
	UBYTE	PrinterRxPreOpenFlag = 0;		/*	プリンタ受信でのＰｒｅオープン済フラグ	*/
#endif

/*----------------------------------------------------------------------*/
/*	後手順短縮ハンドシェークフラグ	(Jun.14.1994)						*/
/*		自機と相手機の間で「後手順の短縮ハンドシェーク」を行うことが	*/
/*		決まった時に，セットする										*/
/*	プリアンブル短縮フラグ			(Aug.31.1994)						*/
/*		ポストメッセージの命令送信，応答送信時に「後手順短縮フラグ」	*/
/*		の状態によってセット／クリアする (ＭＤＭはこのフラグを見る)		*/
/*			竹内														*/
/*----------------------------------------------------------------------*/
UBYTE	PostSpeedHandshakeFlag = 0;			/*	後手順短縮ハンドシェークフラグ	*/
UBYTE	ShorteningPreambleFlag = 0;			/*	プリアンブル短縮フラグ			*/

/*----------------------------------------------------------------------*/
/*	リモートＦＡＸチェックメッセージ送信フラグ							*/
/*		リモートＦＡＸ送信での最終ページで，次ページにメモリオーバーの	*/
/*		チェックメッセージを送信する時にセットする						*/
/*			竹内	Jun.24.1994											*/
/*----------------------------------------------------------------------*/
UBYTE	TxRemoteFaxCheckMsgFlag = 0;		/*	リモートＦＡＸチェックメッセージ送信フラグ	*/

/*----------------------------------------------------------------------*/
/*	プリンタ受信時のプリンタエラーフラグ								*/
/*		プリンタエラーが発生した時にセットする							*/
/*		これを見て，次ページからプリンタ受信をメモリ受信に切り替える	*/
/*			竹内	Jul.21.1994											*/
/*----------------------------------------------------------------------*/
UBYTE	RxPrinterErrorFlag = 0;				/*	プリンタ受信時のプリンタエラーフラグ	*/

/*------------------------------------------*/
/*	料金管理フラグ							*/
/* ==1　なら料金計算する 25.Aug'94 Y.Suzuki */
/*------------------------------------------*/
#if(PRO_COST == ENABLE)
UBYTE	CheckCostFlag = 0;
#endif

#if(PRO_BATCH_TX == ENABLE)
/*--------------------------------------------------*/
/**	一括送信１頁以上送信後、エラー終了した場合		*/
/*	のリダイヤル送信頁セットの際に使用 Y.Suzuki		*/
/*										94/9/28		*/
/*--------------------------------------------------*/
UBYTE	BatchRedialFirstPage = 0;
#endif

/*#if defined(DEU) || defined(AUT) || defined(NOR)By Y.Suzuki 1998/09/21*/
#if defined(DEU) || defined(AUT)
	UBYTE	FaxTelOffHookFlag = 0;			/*	???		*/
#endif

#if defined(DEU)	/*----	★ドイツ仕様★	----*/
	UBYTE	RTN_ReceiveCounter = 0;			/*	ＲＴＮ受信回数	(ReceiveRTN_Count)	*/
#endif

#if defined(FRA)	/*----	★フランス仕様★	----*/
	UBYTE	FaxRingingPeriodFlag = 0;			/*	無制限:0／一定期間:1	*/
	UBYTE	VoiceFlag = 0;						/*	「会話予約受付」フラグ	*/
	UBYTE	GenerateRingSignalHLRelayFlag = 0;	/*	???	（フランスのみ）	*/
	UBYTE	VoiceTxFlag = 0;					/*	???	（フランスのみ）	*/
	UBYTE	GenerateRingSignalFlag = 0;			/*	???						*/
	UBYTE	GenerateRingSignalMessage = 0;		/*	???						*/
	UBYTE	FRA_PIP_PIN_Rx_Flag = 0;			/*	1995/05/06	by M.HARADA */
	UBYTE	CRPReceiveFlag = 0;					/*	1995/05/07	by M.HARADA */
#endif

/*------------------------------------------------------*/
/*	ＥＣＭ受信時のＲＮＲ処理，ロール紙カット待ちの状態	*/
/*		2=デコード待ち → 1=カット待ち → 0=終了		*/
/*								竹内	Jun.24.1994		*/
/*------------------------------------------------------*/
UBYTE	EcmWaitPhase = 0;						/*	ＥＣＭ受信時のデコード待ち／カット待ち状態	*/


/* By S.K unsigned char	SYS_FaxComType = 0;				*/	/*	交信種別 */
/* By S.K unsigned char	SYS_FaxComTxType = 0;			*/	/*	送信原稿種別 */
/* By S.K unsigned char	SYS_VoiceCallAccepted = 0;		*/	/*	「会話予約受付」フラグ	*/
/* By S.K unsigned char	SYS_RxReceiptRequestFlag = 0;	*/	/*	「受領証要求」フラグ(送信側から受信側の能力をチェック)	*/
/* By S.K unsigned char	SYS_FaxComFIP_RxActiveFlag = 0; */	/*	通信で使用するＦＩＰ受信中フラグ */

/* 未使用 unsigned char	RxPostMessageEORRxContinueFlag = 0;	*/
/* 未使用 unsigned char	CountUpTo100 = 0;				*/
/* 未使用 unsigned char	SetTransmitterID = 0;			*/	/* 「発信元送出」のＯＮ／ＯＦＦを示す */
/* 未使用 unsigned char	DCSReceivedFlag = 0;			*/	/* ＤＣＳ関係	*/
/* 未使用 unsigned char	LastFCF = 0;					*/	/*	最後に受信したＦＣＦ	*/
/* 未使用 unsigned char	GI2AvailableFlag = 0;			*/	/*	???		*/
/* 未使用 unsigned char	OverSeaDial1stDISFlag = 0;		*/	/*	???		*/
/* 未使用 unsigned char	GCAvailableFlag = 0;			*/	/*	???		*/
/* 未使用 unsigned char	FarBssData = 0;					*/	/*	???		*/
/*----	★松ＡＰ　ＵＳＡ仕様★	----------------------------------------*/
/*	unsigned char	FaxComTemporaryCalledFlag = 0;	%*	仮着信	*%		*/
/*----------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  ダイヤル種別、ダイヤルナンバー配列のオフセット用データ	Nov.21.1996	 By T.Yamaguchi
  ------------------------------------------------------------------------------------ */
UBYTE	DialKind = 0;							/* ダイヤル種別 */
UBYTE	DirectNumberPosition = 0;				/* 直接ﾀﾞｲﾔﾙのﾎﾟｼﾞｼｮﾝ */
UBYTE	OnetouchDialPosition = 0;				/* ワンタッチﾀﾞｲﾔﾙのﾎﾟｼﾞｼｮﾝ */
UWORD	SpeedDialPosition = 0;					/* 短縮ﾀﾞｲﾔﾙのﾎﾟｼﾞｼｮﾝ */


/*==============================================*/
/*		 ２バイト・４バイトデータ達				*/
/*==============================================*/

UWORD	FaxComResult = 0;					/*	交信結果					*/
UWORD	BackUpFaxComResult = 0;				/*	交信結果（バックアップ）	*/

UDWORD	FaxComStartTime = 0;				/*	交信開始時刻	*/
UWORD	FaxComPeriod = 0;					/*	交信時間	*/

/*以下２ライン　SYS_DATA.C に移動 OPR ﾀｽｸが参照するため　19.Apr'94 Y.Suzuki*/
/*unsigned int	SYS_TxTotalPage			 = 0;			*//*	全送信ページ数	*/
/*unsigned int	SYS_RxTotalPage = 0;					*//*	全受信ページ数	*/

UDWORD	TxPageTotalLineCount = 0;			/*	送信トータルライン数（スキャナ送信用）	*/

WORD				RxPageIndexNo	   = 0;				/*	メモリ受信時のファイルインデックス番号	*/

UWORD	PollingTxFirstPageFlag = 0;			/*	ポーリング送信先頭ページフラグ	*/

UWORD	PRI_Q_Count = 0;					/*	ＰＲＩ－Ｑカウント	*/

UWORD	TxMemoryFileCurrentExecutingNo = 0;	/*	現在実行中のメモリ送信原稿のファイルナンバー　通常送信--１ */
											/*	  マルチファイルＤＢポーリング--送信中のファイルNO	*/
UWORD	TxMemoryFileNextExecutingNo = 0;	/*	次送信予定ののメモリ送信原稿のファイルナンバー　通常送信--１ */

UWORD	TxMemoryFilePage = 0;				/*	メモリ送信を行う原稿のファイルページ	*/

UWORD	FCM_ReceiveResponseTime = 0;		/* 応答受信時のタイマ add by t.yamaguchi 95.12.18 */

/*---------------------------------------------------*/
/*	デュアルオープンメモリ受信されるプリント用原稿	 */
/*	のためのパラメータ								 */
/*	By Y.SUZUKI	17.Feb'94	SYS_DATA.Cに移動		 */
/*---------------------------------------------------*/
/*unsigned int	SYS_RxPrintFilePage = 0;				*	デュアルオープンメモリ受信されるプリント用原稿(中継配信指示受信、リモートＦＡＸ同時プリント)のファイルページ	*/
/*unsigned int	SYS_RxPrintFileNo = 0;					*	デュアルオープンメモリ受信されるプリント用原稿(中継配信指示受信、リモートＦＡＸ同時プリント)のファイルＮＯ．	*/
/*unsigned char	SYS_RxPrintFileItem = 0;				*	デュアルオープンメモリ受信されるプリント用原稿(中継配信指示受信、リモートＦＡＸ同時プリント)のファイルアイテム	*/


WORD				TxNonStandardFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットした送信非標準フレームのバイト数		*/
WORD				TxID_FrameByteCount = 0;			/*	MDM_Buffer[][]上へセットした送信ＩＤフレームのバイト数		*/
WORD				TxStandardFrameByteCount = 0;		/*	MDM_Buffer[][]上へセットした送信標準フレームのバイト数		*/
WORD				RxNonStandardFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットされた受信非標準フレームのバイト数	*/
WORD				RxID_FrameByteCount = 0;			/*	MDM_Buffer[][]上へセットされた受信ＩＤフレームのバイト数		*/
WORD				RxStandardFrameByteCount = 0;		/*	MDM_Buffer[][]上へセットされた受信標準フレームのバイト数		*/

WORD				NonStdFrmPos = 0;					/*	MDM_Buffer[][]上へ受信した非標準フレームの位置	*/
WORD				ID_FrmPos = 0;						/*	MDM_Buffer[][]上へ受信したＩＤフレームの位置		*/
WORD				StdFrmPos = 0;						/*	MDM_Buffer[][]上へ受信した標準フレームの位置		*/
UDWORD				FaxTM = 0;							/*	タイマー	*/




UWORD	FCF_Point		= 0;				/*	HDLC関係　HDLCフレーム受信時モデムバッファ内のＦＣＦの位置	*/

UWORD	DiagPoint		= 0;				/*	リモート診断関係　サービスユーティリティフィールドポイント	*/
UWORD	DiagReadAddress = 0;				/*	リモート診断関係	*/
UWORD	DiagReadSegment = 0;				/*	リモート診断関係	*/
#if defined(POPLAR_F)
UWORD	DiagTxBackUpPointer = 0;			/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
UDWORD	DiagTxLength = 0;					/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
UWORD	DiagTxBackUpSize = 0;				/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
UWORD	DiagRxBackUpPointer = 0;			/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
UDWORD	DiagRxLength = 0;					/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
UWORD	DiagRxBackUpSize = 0;				/*	リモート診断 64KB以上データ対応 1999/04/29 by K.Okada */
#endif
UWORD	RelayedDocumentReceiveNo = 0;		/*	中継指示時プリントするファイルナンバー	*/
UWORD	ErrorMessageSet = 0;				/*	エラーメッセージ内容	*/

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
UWORD	FcomEcmSizeSram = 256;				/*	ＥＣＭフレームサイズ（６４／２５６oct）種別	*/
#else
UWORD	FcomEcmSize = 256;					/*	ＥＣＭフレームサイズ（６４／２５６oct）種別	*/
#endif

WORD	FaxTelResult = 0;					/* FaxTel戻り値 */

#if (0)/*By Y.Suzuki 1998/09/11*/
//#if(PRO_BATCH_TX == DISABLE)
//UWORD	TxMemoryFileNo[SYS_TX_MEMORY_FILE_NO_MAX]	 = {0};	/*	メモリ送信を行う原稿のファイルナンバー	*/
//UWORD	PollingTxFilePage[SYS_TX_MEMORY_FILE_NO_MAX] = {0};	/*	ポーリング送信の際の総送信ページ数	*/
//#else
//UWORD	TxMemoryFileNo[SYS_BATCH_INDEX_MAX+1]	 = {0};			/*	バッチ,メモリ送信を行う原稿のファイルナンバー 20.Aug'94 Y.Suzuki	*/
//UWORD	PollingTxFilePage[SYS_BATCH_INDEX_MAX+1]   = {0};			/*	バッチ,ポーリング送信の際の総送信ページ数 20.Aug'94 Y.Suzuki	*/
//#endif
#endif /*if(0) By Y.Suzuki 1998/09/11 */
/*受信原稿ポーリング取り出しに対応するため 最大代行受信数にあわせる By Y.Suzuki 1998/09/11 */
UWORD	TxMemoryFileNo[SYS_MEMORY_RX_MAX+1]	 = {0};	/*	メモリ送信を行う原稿のファイルナンバー	*/
UWORD	PollingTxFilePage[SYS_MEMORY_RX_MAX+1] = {0};	/*	ポーリング送信の際の総送信ページ数	*/

/*---------------------------------------------------------------------*/
/*	 第２ワンタッチ／短縮ダイアルの配列オフセット					   */
/*	   FCM_SetPartnerAbility() でセットされる						   */
/*																	   */
/* if ( SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed < SYS_SPEED_DIAL_MAX )
 *		Offset_2ndDial = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Speed - SYS_SPEED_DIAL_MAX
 *																	   *
 * if ( SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch < SYS_2ND_ONETOUCH_MAX )
 *		Offset_2ndDial = SYS_CurrentExecutingCommand->ExecDial.ExecNumber.Onetouch - SYS_2ND_ONETOUCH_MAX
 *																	   */
/* 1994/02/17 Y.Murata												   */
/*---------------------------------------------------------------------*/
UWORD	Offset_2ndDial = 0;					/* 第２ワンタッチ／短縮ダイアルの配列オフセット */

/*------------------------------------------------------------------------*/
/* ジャーナル通番									  1994/06/07 Y.Murata */
/*			 通信開始時にジャーナルカウント(SYB_TxTotalCount)をセーブする */
/*------------------------------------------------------------------------*/
UWORD	JournalTxTotalCount = 0;
UWORD	JournalRxTotalCount = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/03/11 */
UWORD	JournalTxTotalCountExt = 0;
UWORD	JournalRxTotalCountExt = 0;
#endif

UWORD	EcmOneFrameTime = 0;	/*	ＥＣＭ受信タイムアウト回避用の１フレーム分の時間(msec)	*/

/*--------------------------------------------------------------------------*/
/*	一括送信送信済み頁数	94/9/22 Y.Suzuki								*/
/*--------------------------------------------------------------------------*/
UWORD	BatchTxFinishPage = 0;

/* const unsigned int	FaxComAvailableModeMaster = G2_ABILITY|G3_ABILITY; */	/*	受信モード （有効受信モード）ロムテーブル	*/
/* By S.K unsigned int	SYS_RxMemoryFileItem = 0;		*/	/*	メモリ受信を行う原稿のファイルアイテム	*/
/* By S.K unsigned int	SYS_RxMemoryFileNo = 0;			*/	/*	メモリ受信を行う原稿のファイルナンバー	*/
/* By Y.S unsigned int	SYS_RxMemoryFilePage = 0;				*	メモリ受信を行う原稿のファイルページ	*/
/* 未使用 unsigned int	FaxComAvailableMode = 0;		*/	/*	受信モード（有効受信モード）int-->char 鈴木94/1/19	*/
/* 未使用 unsigned int	FaxComStartTimeInSecond = 0;	*/	/*	交信時間	交信開始時のタイマー値をセーブしておき交信時間を求める	*/
/* 未使用 unsigned int	FaxComTotalLine = 0;			*/	/*	受信トータルライン　画データ受信側でセット	*/
/* 未使用 unsigned int	FaxComErrorTotalLine = 0;		*/	/*	受信エラートータルライン　画データ受信側デセット	*/
/* 未使用 unsigned int	PhaseDTxPageFinishStatus = 0;	*/	/*	フェーズＤで再セットした送信結果	*/
/* 未使用 unsigned int	MDM_RxTotalLine = 0;			*/	/* by T.S '94.1.14 受信トータルライン　画データ受信側でセット	*/
/* 未使用 unsigned int	MDM_RxErrorTotalLine = 0;		*/	/* by T.S '94.1.14 受信エラートータルライン　画データ受信側デセット	*/



/*--------------------------------------------------------------------*/
/* メッセージ用ポインター											  */
/*--------------------------------------------------------------------*/
MESSAGE_t			FaxTelTxMessage		 = {0};				/*	ＴＥＬ／ＦＡＸ用	*/
MESSAGE_t			*FaxTelRxMessage	 = {0};				/*	ＴＥＬ／ＦＡＸ用	*/
/* MESSAGE_t			*DetCNG_Message		 = {0};		*/	/*	ＴＥＬ／ＦＡＸ用	*/
/* MESSAGE_t			*DetRcvComMessage	 = {0};		*/	/*	ＴＥＬ／ＦＡＸ用	*/
/* MESSAGE_t			*TxComMessage		 = {0};		*/	/*	ＴＥＬ／ＦＡＸ用	*/
/* MESSAGE_t			*OffHookMessage		 = {0};		*/	/*	ＴＥＬ／ＦＡＸ用	*/
MESSAGE_t			MsgFromFaxComToMain	 = {0};			/*	通信～＞メイン用	*/
MESSAGE_t			*FcomMsg			 = {0};			/** メイン～＞通信用メッセージ */


/*---------------------------------------------------------------------*/
/* コマンドファイル用ポインター										   */
/* 94/01/06	   Y.Murata												   */
/*---------------------------------------------------------------------*/
struct	SYS_CommandData_t		*CommandP = {0};		/*	コマンドファイル用ポインター	*/

/*---------------------------------------------------------------------*/
/* 一括送信用ポインター												   */
/* 94/01/06	   Y.Murata												   */
/*---------------------------------------------------------------------*/
struct	SYS_BatchTxData_t		*BatchP	  = {0};		/*	一括送信用ポインター	*/

#if (PRO_CONTINUOUS_POLLING == ENABLE)
/*---------------------------------------------------------------------*/
/* 連続ポーリング用ポインター										   */
/* Oct.18.1996	By T.Yamaguchi										   */
/*---------------------------------------------------------------------*/
struct	SYS_ContinuousPollingData_t *ContPollingP	= {0};
#endif

/*---------------------------------------------------------------------*/
/* ジャーナル用ポインタ												   */
/* 94/01/17	   Y.Murata												   */
/*---------------------------------------------------------------------*/
struct	SYS_JournalData_t		*Journal	 = {0};		/* ジャーナル用ポインタ		*/

/*----------------------------------------------------------------------*/
/*	メモリファイルのオープン実行用データ								*/
/*		MEM_WriteOpen()/MEM_DualOpen()の実行時使用						*/
/*		竹内茂樹	Jan.21'94											*/
/*		Mar.02.1994		struct MEM_ExecData_t FaxMemoryExecData やめ！	*/
/*		May.12.1994		struct MEM_StoreData_t FaxMemoryStoreData 削除！	*/
/*----------------------------------------------------------------------*/
/*	struct	MEM_StoreData_t	FaxMemoryStoreData = {0};	*/	/*	メモリへの蓄積実行用データ	*/

/*---------------------------------------------------------------------*/
/*	デュアルオーブン時インデックス指定データ						   */
/*		MEM_DualWriteOpen()の実行時使用								   */
/*		中継配信指示受信、リモートＦＡＸ受信(同時プリント有り)の場合に */
/*		使用														   */
/*		Y.SUZUKI	Feb.17'94										   */
/*---------------------------------------------------------------------*/
struct	MEM_IndexData_t	FaxMemoryIndexData = {0};	/*	デュアルオーブン時インデックス指定データ	*/
/* この変数は何処で使っているのでしょうか？ 97/01/09 BY T.Yamaguchi 要確認	*/

#if defined(FRA)				/* 95/02/21 by M.HARADA */
unsigned	char	FRA_GRS_StartFlag = 0;			/*	DIS 3回TX後擬似ベルタスクの起動時に参照　*/
UWORD		tskno_B1_Bell = 0xFFFF;
#endif

WORD			DammyDataforMurata1 = 0;				/* 内蔵ＲＡＭに移動のための保健体育 */
WORD			DammyDataforMurata2 = 0;
WORD			DammyDataforMurata3 = 0;
WORD			DammyDataforMurata4 = 0;
WORD			DammyDataforMurata5 = 0;

#if(PRO_RELAYED_REPORT == ENABLE)
/* 椛不達通知用 不達通知送信時は、会話予約キーの入力を拒否する。95/03/17 Y.Suzuki */
UBYTE TxRelayReport = 0;
#endif
#if defined(GBR)	/* add by M.HARADA 95.09.09 for NLD */
UBYTE NLD_DT_Detecting_Flag = 0;
#endif
/* 1997/06/02  By T.Yamaguchi DEU条件削除 */
UBYTE DEU_Return_Flag = 0;
/* #if defined(FRA) || defined(DEU) 1997/06/02  By T.Yamaguchi */
UBYTE TimerCutStatus = 0;
UBYTE PIP_TX_Flag = 0;	/* 1997/06/02  By T.Yamaguchi DEU条件削除 */ /* 97/04/26 by M.H. */
/* #endif */

/*----------------------------------------------------------*/
/*	TSI による中々継時に中継指示ｸﾞﾙｰﾌﾟNO.とは、				*/
/*	別に中継指示配信送信宛先用ｸﾞﾙｰﾌﾟNO.をTSIにｾｯﾄさせる。	*/
/*	受信したTSI:000-2-3-4--10 の場合						*/
/*						  ↑を示す。						*/
/*											Y.Suzuki 950929 */
/*----------------------------------------------------------*/
#if(PRO_TSI_RELAY_COM == ENABLE)
UBYTE TSI_Ptr = 0;
#endif

MESSAGE_t			BackupFcomMsg = {0};		/** メイン～＞通信用メッセージ保存 1996/03/04 */

/* ICHOU からもってきた 1997/06/02  By T.Yamaguchi */
/* UBYTE	AddPBX_DialingNumber[DIALING_NUMBER_MAX+(SYS_PBX_NUMBER_MAX-1)] = {0};	未使用 */
struct	MEM_IndexData_t		EraseIndexData = {0};				/*	ファイルインデックス	*/
UWORD	TxFinalPageNumber = 0;	/* ICHOU変更 送信最適化処理 by T.Soneoka 1996/10/01 */

/* コンパチの途中で記録紙サイズが変更されるとエラーにならないためバックアップ変数 */
UBYTE	FCM_BuckUpPaperSize = 0;	/* 1997/12/16  By T.Yamaguchi */


/*---------------------------------*/
/* Ｆコードのためのもの 1996/06/14 */
/*---------------------------------*/
WORD			TxPasswordFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットした送信ＰＷＤフレームのバイト数	*/
WORD			TxSelectiveFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットした送信ＳＥＰフレームのバイト数	*/
WORD			TxSubaddressFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットした送信ＳＵＢフレームのバイト数	*/
WORD			RxPasswordFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットされた受信ＰＷＤフレームのバイト数	*/
WORD			RxSelectiveFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットされた受信ＳＥＰフレームのバイト数	*/
WORD			RxSubaddressFrameByteCount = 0;	/*	MDM_Buffer[][]上へセットされた受信ＳＵＢフレームのバイト数	*/
UBYTE			PasswordFrameID[SYS_ID_MAX] = {0};			/* PWDﾊﾞｯﾌｧ */
UBYTE			SelectivePollingFrameID[SYS_ID_MAX] = {0};	/* SEPﾊﾞｯﾌｧ */
UBYTE			SubaddressFrameID[SYS_ID_MAX] = {0};		/* SUBﾊﾞｯﾌｧ */

UBYTE			OwnPasswordFrameID[SYS_ID_MAX] = {0};			/* PWDﾊﾞｯﾌｧ */
UBYTE			OwnSelectivePollingFrameID[SYS_ID_MAX] = {0};	/* SEPﾊﾞｯﾌｧ */
UBYTE			OwnSubaddressFrameID[SYS_ID_MAX] = {0};		/* SUBﾊﾞｯﾌｧ */

UBYTE			PartnerPasswordFrameID[SYS_ID_MAX] = {0};			/* PWDﾊﾞｯﾌｧ */
UBYTE			PartnerSelectivePollingFrameID[SYS_ID_MAX] = {0};	/* SEPﾊﾞｯﾌｧ */
UBYTE			PartnerSubaddressFrameID[SYS_ID_MAX] = {0};		/* SUBﾊﾞｯﾌｧ */

UBYTE			PWD_FrmName = 0;
UBYTE			SEP_FrmName = 0;
UBYTE			SUB_FrmName = 0;
WORD			PWD_FrmPos	= 0;
WORD			SEP_FrmPos	= 0;
WORD			SUB_FrmPos	= 0;

UBYTE			PartnerT_PWD_Ability = 0;
UBYTE			PartnerP_PWD_Ability = 0;
UBYTE			PartnerSEP_Ability = 0;
UBYTE			PartnerSUB_Ability = 0;

UBYTE			PWDT_BitEnable	= 0;
UBYTE			PWDP_BitEnable	= 0;
UBYTE			SUB_BitEnable	= 0;
UBYTE			SEP_BitEnable	= 0;

#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/*------------------------------------------------------------------------------------------------
	ソフトコーデック使用時のＧ３メモリ送信 Ａ３，ＨＦＩＮＥ －－＞ (Ｂ４以下）&&（ＳＦＩＮＥ以下）
	が発生するとき 最小伝送時間 ０ｍｓから１０ｍｓにする				 By Y.Suzuki 1997/05/09
	初期値 :0
	縮小あり、		インクリメント
	ﾓｰﾄﾞ変更あり	インクリメント
	2以上なら ０ｍｓ－－＞１０ｍｓとする。
--------------------------------------------------------------------------------------------------*/
UBYTE	AddMinLineTime = 0;
#endif

/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/13 Y.Murata */
UBYTE	PartnerV8Capable = 0;				/* 相手機Ｖ８能力有り */
/* #endif */


/***********************************************************************/
/* Ｖ８／Ｖ３４仕様にともない新規追加                                  */
/***********************************************************************/
/* Ported from Clover by H. Kubo 1997/06/27 */
/* 新たに必要になったインクルードファイル */
#include 	"\src\atlanta\define\fcm_def.h"
#include 	"\src\atlanta\define\ncu_data.h"

/*------------------*/
/* １バイトデータ達 */
/*------------------*/
UBYTE	V8ProcedureRequestFlag = 0;			/* Ｖ８モード移行要求 */
UBYTE	V34FirstDataRate = 0;				/* Ｖ３４データレイト(最初) */
UBYTE	V34CurrentDataRate = 0;				/* Ｖ３４データレイト(現在) */
UBYTE	V34BaudDataRate = 0;				/* Ｖ３４ボーレイト */
/* UBYTE	PartnerV8Capable = 0;	*/			/* 相手機Ｖ８能力有り */

UBYTE	V34PrimaryChannelDirection = 0;		/* プライマリチャネル指示 */
#if (0) /* Deleted by H.Kubo 1997/10/07 使われていない */
UBYTE	V8FrmName = 0;
#endif /* 0 */
UBYTE	FCM_CallFunctionData = 0;
UBYTE	V34ErrorCode = 0;					/* ＡＢＣＯＤＥ */
UBYTE	V8ConfigMode = 0;					/* Ｖ８終了時のCONF の値 */
UBYTE	FCM_V8MonitorFlag = 0;				/* V8 Octet Monitor Flag */
UBYTE	FCM_SampleBufPoint = 0;				/* data rate sample for debug */
UBYTE	FCM_CONF_Value = 0;					/* conf data for debug 1996/02/19 */
UBYTE	FCM_SPEED_Value = 0;				/* tx speed for debug 1996/02/19 */
UBYTE	FCM_384_Value = 0;					/* rx speed for debug 1996/02/19 */
UBYTE	FCM_DataRateChangExecute = 0;		/* 通信速度変更中 1996/08/28 */

UBYTE	V8_ANSamDetectFlag = 0;		/* 1996/08/07 */

/*----------------------*/
/* ２、４バイトデータ達 */
/*----------------------*/
UWORD			V34PhaseStatus = 0;					/* Ｖ３４スタートアップフェーズステータス */
WORD			TxInformationCategoryByteCount = 0;	/* 送信情報カテゴリバイト数 */
WORD			RxInformationCategoryByteCount = 0;	/* 受信情報カテゴリバイト数 */
UWORD			ExecDialNumber = 0;					/* ワンタッチ／短縮番号 */
WORD			V8FrmPos = 0;						/* Ｖ８フレームがモデムバッファの何番目か */
WORD			V8CallFunctionPos = 0;				/* 起呼機能の位置 */
/* UWORD			FCM_ReceiveResponseTime = 0;		*/ /* 応答受信ﾀｲﾏｰ */
UWORD			FCM_SignalToNoiseRatio = 0;			/* Signal to Noise Ratio */
UWORD			FCM_LowBandEdgeFrequency = 0;		/* Low Band Edge Frequency */
UWORD			FCM_HighBandEdgeFrequency = 0;		/* High Band Edge Frequency */
UWORD 			FCM_PreEmphasisFilter	= 0;	/* Add By O.Kimoto 1996/04/18 */
UWORD 			FCM_TxLevelReduction = 0;		/* Add By O.Kimoto 1996/07/25 */
#if (0) /* Deleted by H.Kubo 1997/10/07 */
UWORD			FCM_MemoryBlockSize = 0;			/* １ブロックのサイズ 1996/03/07 */
#endif /* (0) */
UWORD			FCM_SavedRxTotalFrameLine = 0;		/* トータルフレーム数記憶 1996/05/16 */
UWORD			FCM_SavedRxErrorFrameLine = 0;		/* エラーフレーム数記憶 1996/05/16 */
UWORD			FCM_SavedRxPartialFrameLine = 0;	/* 部分ページフレーム数記憶 1996/05/20 */
UWORD			FCM_SavedRxNonErrContinuePage = 0;	/* 連続エラーなしページ数記憶 1996/05/20 */
UWORD			ECM_PageCounterBackUp = 0;			/*	ＥＣＭポストメッセージのページカウンタ	*/
UWORD			ECM_BlockCounterBackUp = 0;			/*	ＥＣＭポストメッセージのブロックカウンタ	*/
UWORD			FCM_PhaseJitterFrequencyValue = 0;	/* 位相ジッタリード値 */
UWORD			FCM_PhaseJitterAmplitudeValue = 0;	/* 位相ジッタリード値 */

UBYTE			FCM_ToneAfterDetectDCE = 0; /* 1997/11/29 by H.Kubo */

/*----------------*/
/* 配列、構造体達 */
/*----------------*/
struct	StartUpDataFile_t				StartUpData = {0};			/* スタートアップデータ */
struct	FCM_MemoryClearIndexData_t		FCM_MemoryClearIndex = {0};		/* 原稿消去指示用インデックス */
UBYTE									V34SavedCM_Data[SAVE_CATEGORY_BUF_MAX] = {0};
UBYTE									V34SavedJM_Data[SAVE_CATEGORY_BUF_MAX] = {0};
UBYTE									V34SavedAvailableJM_Data[SAVE_CATEGORY_BUF_MAX] = {0};
struct	FCM_V8ControlData_t				FCM_V8Control = {0};
struct	Timer10msData_t					FCM_TimeUp = {0};
UBYTE									FCM_MonitorData[50] = {0};

#if 0 /*ROM 節約のため、削除。by H.Kubo 1999/01/22  */
@ UBYTE	FCM_SpeedBuf[16] = {0};
@ UBYTE	FCM_ConfBuf[16] = {0};
@ UBYTE	FCM_RateBuf[16] = {0};
#endif

UWORD			FCM_EQM_MonitorBuf[100] = {0};	/* TEST 1996/02/23 */
UBYTE			FCM_EQM_MonitorPoint = 0;		/* TEST 1996/02/23 */

/* MESSAGE			BackupFcomMsg = {0};		*/ /** メイン～＞通信用メッセージ保存 1996/03/04 */

UBYTE FCM_Is_ToneDetecting = 0;	/* 1997/09/11  By T.Yamaguchi */

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
UWORD				tskno_LST_RelayedTxReportImage = 0xffff;
#endif

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
UBYTE DiagErrorDetails = 0;
UWORD FCM_ROMDataSum = 0;
#endif

#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* PhaseJitter。by H.Kubo 1998/10/07  */
UWORD	FCM_PhaseJitterFrequency = 0;
UWORD	FCM_PhaseJitterAmplitude = 0;
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
UBYTE	FCM_QuickMemoryTxExecute = 0;
#endif

#if (PRO_TX_SPEED == V34)
/* 松下 Ｂ－５６がＣＩを検出しないため、Ｔ．１．１エラーが必ず発生する。
** よって、その防御策として、ＣＩ送出回数を限定する。
** By O.Kimoto 1999/03/11
*/
UBYTE	FCM_CI_TransmitCount = 0;
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
UBYTE	FCM_DetectFSK = 0;
UBYTE	FCM_DetectCIbyVoiceAnswer = 0;
UBYTE	FCM_BusyToneDetectStatus = 0;
 #endif
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 2001/10/03 M.Matsumoto *//* Add By O.Kimoto 2002/03/11 */
UBYTE	IsDetectBusyTone = 0;
#endif



/*********************************************************************
	警察FAX関連
										05/06/16 石橋正和
*********************************************************************/
#if defined (KEISATSU)

BOOL FCM_S1_Scramble; /* S1によるスクランブル通信か否か */
BOOL FCM_S1_Senyo; /* TRUE:専用 FALSE:共通 */

BOOL FCM_S1_Bypass; /* S1をバイパスするか否か */

struct FCM_ExecutingS1Info_t FCM_ExecutingS1Info; /* 実行中のスクランブル通信の状態 */

BOOL FCM_S1_Preamble3S; /* 最初のDCSのプリアンブルを3秒にする */

BOOL FCM_ShireiKidoWaitFor1stDCS; /* 一斉指令起動で最初のDCSを待っている */

/* const UWORD DBG_DelayAfterS1Open = 100; */		/* S1オープン送出後のウェイト[ms] */
const UWORD DBG_DelayAfterS1Open = 0;		/* S1オープン送出後のウェイト[ms] */
const UWORD DBG_DelayAfterRTC = 150;		/* RTC送出後のウェイト[ms] */
const UBYTE DBG_G3_TCF_OriginalPosition = 0;	/* G3、TCF送信におけるRTCを本来のタイミングで送出する */
const UBYTE DBG_ECM_OriginalPosition = 0;	/* ECM送信におけるRTCを本来のタイミングで送出する */

BOOL FCM_ISSEI_TX;		/* 警察FAX DVT_ID17 一斉モード送信中 by SMuratec 夏 2005/11/05 */

BOOL FCM_ShireiOff;	/* 指令信号がオフされた */

#endif /* defined (KEISATSU) */
