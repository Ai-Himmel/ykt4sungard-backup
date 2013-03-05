/* by NOBUKO  Oct.03,95 */
/*--------------------------------------------------*/
/*	fcm_def.h										*/
/*		以下のファイルを合体	Jan.7'94	Bamboo	*/
/*		fcm_fcom.h	fcm_err.h						*/
/*		fcm_fcf.h	fcm_fif.h						*/
/*--------------------------------------------------*/
#ifndef fcm_def_h
	#define	fcm_def_h

#include "\src\atlanta\define\mem_def.h" /* Added by H.Kubo for MEM_IndexData_t 1997/06/27 */
#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
#include "\src\atlanta\define\status.h"
#endif

/************************************************************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Thu 25 Nov 1993
* VAR TO HOLD:	 UWORD FaxComRxType
* DESCRIPTION:	 受信種別 使わない　'94.2.12鈴木
************************************************************************************************************/
#define		MEMORY_RX		0		/*	メモリ受信	*/
#define		PRINTER_RX		1		/*	プリンタ受信	*/
/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Thu 25 Nov 1993
* VAR TO HOLD:	 struct	FaxComData	FaxComStatus.ECM;
* DESCRIPTION:	 ＥＣＭ実行状態
************************************************************************/
#define		ECM_OFF			0		/*	ＥＣＭオフ	*/
#define		ECM_ON			1		/*	ＥＣＭオン	*/
/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Thu 25 Nov 1993
* VAR TO HOLD:	 UWORD TxMSEMethod;
* DESCRIPTION:	 MSE MODE
************************************************************************/
#define		NOMSE			0
#define		MSE1			1
#define		MSE2			2
#define		SMSE			3
/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Thu 25 Nov 1993
* VAR TO HOLD:	 UWORD	TxBaudRate;
* DESCRIPTION:	 通信ボーレート
************************************************************************/
/*-----------
*  POPLAR_H で使う R288F モデムのために追加。 by H. Kubo 1997/06/19
* [NOTE]	以下の  #define のなかで、 1-10 までは EYEQ_SliceTable[][]のテーブルの
*			インデックスに使われるために値の変更は不可。
*			それより後の値の変更は可能。(久保)
*/
/** V.8 **/
#define		V8_SETUP		92
#define		V8_CLEARDOWN	91
/** V.34 **/
#define		BPS33600_V34	115
#define		BPS31200_V34	114
#define		BPS28800_V34	113
#define		BPS26400_V34	112
#define		BPS24000_V34	111
#define		BPS21600_V34	110
#define		BPS19200_V34	109
#define		BPS16800_V34	108
#define		BPS14400_V34	107
#define		BPS12000_V34	106
#define		BPS9600_V34		105
#define		BPS7200_V34		104
#define		BPS4800_V34		103
#define		BPS2400_V34		102
#define		CLEARDOWN_V34	101
/** V.33 **/
#define		BPS14400_V33	5	/* Old Data = 31 */
#define		BPS12000_V33	4	/* Old Data = 32 */
#define		BPS9600_V33		122	/* Old Data = 34 */
#define		BPS7200_V33		121	/* Old Data = 38 */
/** V.17 **/
#define		BPS14400_V17	9
#define		BPS12000_V17	8
#define		BPS9600_V17		7
#define		BPS7200_V17		6
/** V.29 **/
#define		BPS9600_V29		3
#define		BPS7200_V29		2
#define		BPS4800_V29		131
/** V.27 ter **/
#define		BPS4800_V27		1
#define		BPS2400_V27		0
/** V.21 **/
#define		BPS0_300_V21	141
#define		BPS300_V21		10	/** Channel 2 **/
/** Etc. **/
#define		TX_SINGLE_TONE	154
#define		TX_DUAL_TONE	153
#define		DIALING			152
#define		DTMF_RECEIVER	151
/** V.23 **/
#define		TX1200_V23		162	/* Tx:1200 Rx:75   */
#define		RX1200_V23		161	/* Tx:75   Rx:1200 */

#define		FAXCOM_STOP		255	/* 強制的に通信停止 2001/04/25 H.Yoshikawa */

/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Thu 25 Nov 1993
* VAR TO HOLD:	 UWORD	AvailableTxMinimumScanningTime;
* DESCRIPTION:	 最小走査線時間 DIS Table Comm 14.Mar'94 Y.Suzuki
************************************************************************/
#define		SCANNING_TIME40		0
#define		SCANNING_TIME20		1
#define		SCANNING_TIME10		2
#define		SCANNING_TIME5		3
#define		SCANNING_TIME40_2	4
#define		SCANNING_TIME20_2	5
#define		SCANNING_TIME10_2	6
#define		SCANNING_TIME0		7
/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Thu 25 Nov 1993
* VAR TO HOLD:	 unsigned char	FaxTxMaxLength;
* DESCRIPTION:	 最大原稿長 94.2.8 SYSDOC.H に移動しました。鈴木
************************************************************************/
/*#define		TX_A4_LENGTH			0*/
/*#define		TX_B4_LENGTH			1*/
/*#define		TX_UNLIMITED_LENGTH		2*/
/*************************** SYSDOC.H 内での記述は以下のとうり。 By S,Kawasaki 1996/06/13 */
/* #define SYS_NO_LIMIT		0  * 制限無し */
/* #define	SYS_A4_LENGTH		1  *追加'94/2/8***/
/* #define	SYS_B4_LENGTH		2  *鈴木**********/
/* #define	SYS_A3_LENGTH		3  ***************/
/* #define SYS_MAX_1M			4  * 最大長 1M */
/* #define SYS_MAX_TWICE_A4	5  * F網対応原稿長 */
/***************************************************************/

/***********************************************************************
*		   BY:	 鈴木郁二
*		 DATE:	 Wed 26 Jun 1994
* VAR TO HOLD:	 unsigned char	RelayedTxDocumentStatus[SYS_COM_FILE_MAX]
* DESCRIPTION:	 中継配信原稿の状態
************************************************************************/
#define		NO_RELAYED_DOC		0x00
#define		PRINT_IS_OVER		0x01
#define		RELAYED_IS_OVER		0x02
#define		RECEIVE_RELAYED_DOC 0x04
/***********************************************************************
*		   BY:	 村田
*		 DATE:	 1994/01/08
* VAR TO HOLD:	 unsigned char	FaxComTXorRX_Sign
* DESCRIPTION:	 送信受信判別
************************************************************************/
#define		TX_COM_MODE		 1
#define		RX_COM_MODE		 2
#define		DIAG_MODE		 3

/**********************************************************************
*		   BY:	 山口
*		 DATE:	 1996/05/08
* VAR TO HOLD:
* DESCRIPTION:コマンド通信の送受信判別
***********************************************************************/
#define		COMMAND_KIND_TX	 0
#define		COMMAND_KIND_RX	 1

/***********************************************************************
*		   BY:	 村田
*		 DATE:	 1994/01/09
* VAR TO HOLD:
* DESCRIPTION:	 リモート診断種別
************************************************************************/
#define		DIAG_DIS_ONLY_TX	 0x01		 /*	 DISのみ送出  */
#define		DIAG_REVISION_TX	 0x02		 /* ﾊﾞｰｼﾞｮﾝ読出し */
#define		DIAG_DATA_READ		 0x04		 /*	 ﾃﾞｰﾀ読出し	  */
#define		DIAG_DATA_WRITE		 0x08		 /*	 ﾃﾞｰﾀ書込み	  */
#define		DIAG_ERROR			 0x10		 /*	   ERROR	  */
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/03/31  By T.Yamaguchi */
#define		DIAG_ROM_WRITE_OK	 0x20		 /*	 ﾘﾓｰﾄﾌﾗｯｼｭ書換え OK	  */ /* PRO_RDS_FLASH_ROM_WRITE */
#define		DIAG_ROM_WRITE_ERROR 0x40		 /*	 ﾘﾓｰﾄﾌﾗｯｼｭ書換え ERROR	  */ /* PRO_RDS_FLASH_ROM_WRITE */

#define		NO_STATUS			0x00		/* SYB_FlashROM_WriteStatus */
#define		ROM_DATA_RXING		0x01
#define		ROM_DATA_RECEIVED	0x02
#define		ROM_WRITING			0x03
#define		ROM_WRITE_COMPLETE	0x04
#endif
#if defined(POPLAR_L) || defined(POPLAR_N) 
	#define	ROM_DATA_WRITE_ADDRESS			0x1000000L
#endif
#if defined(POPLAR_B) || defined(POPLR_BN) || defined(POPLAR_H) || defined(ANZU_L) || defined(ANZU_V) || defined(POPLAR_F)
	#define	ROM_DATA_WRITE_ADDRESS			0x1100000L
#endif

#if defined(SAKAKI)
	#define	ROM_DATA_WRITE_ADDRESS			0x1100000L
#endif

#if defined(HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined (SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/13 T.Takagi */
	/* HINOKI By O.Kimoto 1998/09/04 */
	#define	ROM_DATA_WRITE_ADDRESS			0x1100000L
#endif

/*----------------------------------------------------------*/
/*	原稿制御ブロックにセットする最大原稿長（送信／受信）	*/
/*		Jan.27'94	竹内									*/
/*----------------------------------------------------------*/
#if 0	/*	sysdoc.hへ移動	竹内 Jun.14.1994	*/
	#if defined(FRA)
		#define		TX_DOC_BLOCK_LENGTH		0x4a6	/*	フランス仕様(送信)	1190 line	*/
		#define		RX_DOC_BLOCK_LENGTH		0x4e2	/*	フランス仕様(受信)	1250 line	*/
	#else
		#define		TX_DOC_BLOCK_LENGTH		0xffff	/*	その他の仕様(送信)	無制限		*/
		#define		RX_DOC_BLOCK_LENGTH		0xffff	/*	その他の仕様(受信)	無制限		*/
	#endif
	#define		TX_FNET_DOC_BLOCK_LENGTH	0x8de	/*	日本仕様のＦ網設定	2270 line	*/
#endif

/* #if (PRO_CPU == V53)	 || (PRO_CPU == SH704X) || (PRO_CPU == SH7034) */
#if (PRO_CPU == SH7043)
#if (PRO_PRINT_TYPE == LASER)
	#define	MARGIN_5mm		40		/*	40step for 7.7line/mm	*/
	#define	UPPER_MARGIN	20		/*	上マージン5mm(3.85)	*/
	#define	LOWER_MARGIN	20		/*	下マージン5mm(3.85)	*/

#else
	#define	UPPER_MARGIN	8		/*	上マージン2mm(3.85)	*/
	#define	LOWER_MARGIN	8		/*	下マージン2mm(3.85)	*/
#endif
#endif
/**************************************************************************
*			  BY: Y.SUZUKI
*			DATE: Sat. 27 Nov. 1993
*	 Module Name: FCM_ERR.H	松竹桜のFAXERROR.Hと同じ
***************************************************************************/
#define		ECM_MODE_SET	0x8000		/*	ECM交信時	*/
#define		V34_MODE_SET	0x4000		/*	V34交信時	*/
#define		NO_ERROR		0x0000		/*	正常終了	*/
#define		TRANSMITERROR	0x0400		/*	T.X.X エラー	*/
#define		RECEIVEERROR	0x0800		/*	R.X.X エラー	*/
#define		DIALERROR		0x0c00		/*	D.X.X エラー	*/

/* #define		ND_NOT_RECEIVE	0x2000 *//*  ND着信で発ID受信しなかった *//* Test 1998/11/14 H.Yoshikawa */

/*---------------------------------------------------------------------*/
/*			   By : Y.SUZUKI	*/
/*			  DATE: '94.2.17	*/
/*	   VAR TO HOLD: UWORD FaxCompatibleErrorCode	*/
/*	   DESCRIPTION: コンパチエラーの際の詳しいエラー内容	*/
/*	   T30モニターに表示するため使用	*/
/*---------------------------------------------------------------------*/
#define		SECURITY_TX_ERROR				1	/*	パスワード送信不成立	*/
#define		SECURITY_TX_NO_ID_ERROR			2	/*	パスワード送信時 相手機のIDがこない	*/
#define		SECURITY_TX_ID_SPACE_ERROR		3	/*	パスワード送信時 相手機のIDがオールスペース	*/
#define		CLOSED_NETWORK_ERROR			4	/*	閉域通信時 相手機他社機	*/
#define		PASSCODE_ERROR_1				5	/*	閉域通信時 相手機パスコードフィールドなし	*/
#define		PASSCODE_ERROR_2				6	/*	閉域通信時 パスコード不一致	*/
#define		BLOCKJUNKFAX_ERROR				7	/*	DM防止成立	*/
#define		BLOCKJUNKFAX_NO_ID_ERROR		8	/*	DM防止設定時 相手機のIDがこない	*/
#define		BLOCKJUNKFAX_ID_SPACE_ERROR		9	/*	DM防止設定時 相手機のIDがオールスペース	*/
#define		SECURE_NOT_MURATA_ERROR			10	/*	親展送信時 相手機他社機	*/
#define		SECURE_FUNCTION_ERROR			11	/*	親展送信時 相手機親展受信機能なし	*/
#define		SECURE_MAILBOX_ERROR			12	/*	親展送信時 指定メイルボックス未登録	*/
#define		RELAYED_RX_FUNCTION_ERROR		13	/*	中継同報要求時 子機(中継)機能なし	*/
#define		RELAYED_RX_COMMAND_ERROR		14	/*	中継同報要求時 展開可能コマンドファイルなし	*/
#define		TX_NO_POLLING_DOC_ERROR			15	/*	自機ポーリング原稿なし	*/
#define		RX_NO_POLLING_DOC_ERROR			16	/*	相手機ポーリング原稿なし	*/
#define		DB_POLLING_NOT_MURATA_ERROR		17	/*	検索ポーリング受信時 相手機他社機	*/
#define		NO_DB_POLLING_FUNCTION_ERROR	18	/*	自機検索ポーリング機能なし	*/
#define		NO_DB_POLLING_DOC_ERROR			19	/*	相手機検索ポーリング指定原稿なし	*/
#define		POLLING_PASSCODE_ERROR			20	/*	ポーリングパスコード不一致	*/
#define		POLLING_NOT_MURATA_ERROR		21	/*	ポーリングパスコード登録時 相手機他社機	*/
#define		COMMUNICATE_BAUDRATE_ERROR		22	/*	通信ボーレート合せこみできず	*/
#define		COMMUNICATE_CODE_ERROR			23	/*	通信コード(MH、MR、MMR)合せこみできず	*/
#define		COMMUNICATE_MODE_ERROR			24	/*	通信モード(ノーマル、ファイン、Sファイン)合せこみできず	*/
#define		COMMUNICATE_ECM_ERROR			25	/*	通信ECMモード合せこみできず	*/
#define		COMMUNICATE_SIZE_ERROR			26	/*	通信原稿幅合せこみできず	*/
#define		COMMUNICATE_TIME_ERROR			27	/*	通信最小伝送時間合せこみできず	*/
#define		COMMUNICATE_LENGTH_ERROR		28	/*	通信原稿長合せこみできず	*/
#define		STANDARD_FRAME_ERROR			29	/*	標準フレーム受信できず	*/
#define		UNEXPECTED_ERROR				30	/*	予期せぬエラー	*/
#define		SUBSTITUTE_PRINTER_ERROR		31	/*	代行受信バッファフルエラー Y.SUZUKI '94.2.17	*/
#define		PRINTER_ERROR					32	/*	メモリなし機プリンター受信できずエラー　紙づまり､紙無し､トナー無し 25.Mar'94 Y.Suzuki	*/
#define		NO_RX_DOC_POLLING_DOC_ERROR		33	/*	受信原稿ポーリング送信　原稿なしエラー　 25.Mar'94 Y.Suzuki	*/
#define		MEMORY_CAPACITY_ERROR			34	/*	送信コンパチ時、メモリ容量不足(ﾌﾟﾘﾝﾀ機のみ) 受信コンパチ時、ﾘﾓｰﾄFAX受信代行受信用バッファ空きなしまたは，メモリフル	*/
#define		BUFFERING_BUF_FULL_ERROR		35	/*	受信コンパチ時、バッファリングバッファ空きなし	*/
#define		MEMORY_RX_REQUEST_ERROR			36	/*	メモリプリント中にメモリ受信できない機種にメモリ受信要求があった 13.Jly'94 Y.Suzuki	*/
#define		RELAYED_RX_TSI_ERROR			37	/*	中継指示受信、不達ON設定で TSI 不良 9.Feb'95 Y.Suzuki	*/
#define		COMMUNICATE_T4BIT_ERROR			38	/*	通信 DIS T4ﾋﾞｯﾄ ON せず 17.Oct'95 Y.Suzuki	*/
#define		SECURE_INDEX_CONFLICT_ERROR		39	/*	親展受信原稿index競合ｴﾗｰ（同時に同じ親展boxに受信しようとした）1997/01/13 Y.Murata */
#define		RECEIVE_INCRRECT_DIS			40	/*  FIFが00 00 00のDIS、DTCを受信。DTSで回線断を要求されている。DEU仕様 */

#define		SUB_ABILITY_ERROR				41	/*	サブアドレス送信時、相手機能力なし（ボックスなし）*/
#define		SEP_ABILITY_ERROR				42	/*	相手機、選択ポーリング能力なし（蓄積原稿なし、ボックスなし）*/
#define		COMMUNICATE_FCODE_RX_ERROR		43	/*	受信時サブアドレスビットと送って来たＳＵＢデータの論理があっていない */
#define		NOT_SUB_ADDRESS_BOX_ERROR		44	/*	自機のBOXのサブアドレスと相手機のサブアドレスが一致するものがなかった */
#define		SUB_PROHIBIT_RX_ERROR			45	/*	サブアドレスオプション設定で受信禁止のＢＯＸに送って来た */
#define		SUB_RECEIVING_BOX_ERROR			46	/*	多回線仕様で受信中のＢＯＸに受信指定してきた	*/
#define		NO_SUB_POLLING_DOC_ERROR		47	/*	指定されたＢＯＸに原稿が蓄積されていない(ﾌﾟﾘﾝﾄ中、蓄積中の場合あり) */
#define		SUB_POLLING_SECURE_BOX_ERROR	48	/*	親展ＢＯＸをポーリング受信しようとした	*/
#define		SUBADDRESS_BOX_INDEX_MAX_ERROR	49	/*	ＦコードBOX原稿蓄積ＭＡＸまで蓄積されている */
#define		SUBADDRESS_BOX_STORING			50	/*	ＦコードBOX原稿蓄積中or消去中のため受信拒否 */
#define		SUBADDRESS_BOX_PRINTING_ERROR	51	/*	Ｆコード原稿プリント中のため受信できない */

#define		NO_EMPTY_CIPHERBOX_ERROR		52	/*	暗号化受信ＢＯＸが全て使用中 */
#define		CIPHER_ABILITY_ERROR			53	/*	暗号化送信時、相手機に暗号化能力なし */
#define		CIPHER_ECM_ERROR				54	/*	暗号化送信時、相手機にＥＣＭ能力なし */
#define		CIPHER_SIZE_ERROR				55	/*	暗号化送信時、通信原稿幅合せこみできず	*/
#define		CIPHER_MODE_ERROR				56	/*	暗号化送信時、通信原稿モード合わせこみできず */

#define		DIRECTION_ERROR					80	/*	V8ﾓｰﾄﾞにおいてﾌﾟﾗｲﾏﾘﾁｬﾈﾙ指示不一致 */
#define		ORIGINATE_DIRECTION_TX_ERROR	81	/*	起呼局V8ﾓｰﾄﾞにおいてﾌﾟﾗｲﾏﾘﾁｬﾈﾙ指示不一致(TX FAX) */
#define		ORIGINATE_DIRECTION_RX_ERROR	82	/*	起呼局V8ﾓｰﾄﾞにおいてﾌﾟﾗｲﾏﾘﾁｬﾈﾙ指示不一致(RX FAX) */
#define		ORIGINATE_MODURATION_ERROR		83	/*	起呼局V8ﾓｰﾄﾞにおいて変調ﾓｰﾄﾞ合わせ込みできず */
#define		ANSWER_DIRECTION_TX_ERROR		84	/*	応答局V8ﾓｰﾄﾞにおいてﾌﾟﾗｲﾏﾘﾁｬﾈﾙ指示不一致(TX_FAX) */
#define		ANSWER_DIRECTION_RX_ERROR		85	/*	応答局V8ﾓｰﾄﾞにおいてﾌﾟﾗｲﾏﾘﾁｬﾈﾙ指示不一致(RX_FAX) */
#define		ANSWER_MODURATION_ERROR			86	/*	応答局V8ﾓｰﾄﾞにおいて変調ﾓｰﾄﾞ合わせ込みできず */
#define		POLLING_TX_DIRECTION_ERROR		87	/*	受信局でV8ではRX_FAXなのにDTCを受信した */

/* Ported from clover\define\fcm_def.h for R288F by H.Kubo 1997/06/30 */
#define		MDM_CARRY_DOWN_DEU				94	/*	ＤＥＵ仕様キャリ１ライン送信時間オーバー */
#define		MDM_NON_ECM_MODE_CARRY_DOWN_1	95	/*	予期せぬｴﾗｰ Ｇ３モードキャリア断／連続エラー */ /* 1997/01/31 Y.Murata */
#define		MDM_NON_ECM_MODE_CARRY_DOWN_2	96	/*	予期せぬｴﾗｰ Ｇ３モードキャリア断／連続エラー */ /* 1997/01/31 Y.Murata */
#define		MDM_CARRIER_OFF1				97	/*	予期せぬｴﾗｰ(ｷｬﾘｱ断ｰﾓﾃﾞﾑがOFFを返してきた) */ /* 1996/09/20 Y.Murata */
#define		MDM_CARRIER_OFF2				98	/*	予期せぬｴﾗｰ(ｷｬﾘｱ断-FEDが５秒間OFF) */ /* 1996/09/20 Y.Murata */
#define		MDM_CTS_ABORT					99	/*	予期せぬｴﾗｰ(ﾓﾃﾞﾑのCTSがONしなかった) */ /* 1996/05/17 Y.Murata */

/*----------------------------------------------------------------------------------*/
/*	@(#) fcm_fcf.h 26/Nov/1993 ファックス通信用 定義 (ファクシミリ制御フィールド)	*/
/*	松竹桜 fcf.h より流用　鈴木														*/
/*----------------------------------------------------------------------------------*/
/*------------------+-----------+-------------------------------+-----------*/
/*					| LSB 1'st	|	機	能						| MSB 1'st	*/
/*------------------+-----------+-------------------------------+-----------*/

#define		CFR_F		0x84	/*	受信準備確認				| 0x21	*/
#define		CRP_F		0x1a	/*	命令再送					| 0x58	*/

#define		CIG_F		0x41	/*	発呼端末識別				| 0x82	*/
#define		CSI_F		0x40	/*	被呼端末識別				| 0x02	*/
#define		CTC_F		0x12	/*	訂正続行					| 0x48	*/
#define		CTR_F		0xc4	/*	訂正続行応答				| 0x23	*/
#define		DCN_F		0xfa	/*	切断命令					| 0x5f	*/
#define		DCS_F		0x82	/*	ディジタル命令信号			| 0x41	*/
#define		DIS_F		0x80	/*	ディジタル識別信号			| 0x01	*/
#define		DTC_F		0x81	/*	ディジタル送信命令			| 0x81	*/
#define		EOM_F		0x8e	/*	メッセージ終了				| 0x71	*/

/* FX 独自 EOM 追加 動作は、EOM と同じ 94/9/17 Y.Suzuki */
#define		EOMX_F		0xce	/*	メッセージ終了				| 0x73	*/

#define		EOP_F		0x2e	/*	手順終了					| 0x74	*/
#define		EOR_F		0xce	/*	再送終了					| 0x73	*/
#define		ERR_F		0x1c	/*	再送終了応答				| 0x38	*/

#define		MCF_F		0x8c	/*	メッセージ確認				| 0x31	*/
#define		MPS_F		0x4e	/*	マルチページ信号			| 0x72	*/

#define		NSC_F		0x21	/*	非標準機能命令				| 0x84	*/
#define		NSF_F		0x20	/*	非標準機能					| 0x04	*/
#define		NSS_F		0x22	/*	非標準機能設定				| 0x44	*/
#define		PIN_F		0x2c	/*	手順中断否定				| 0x34	*/
#define		PIP_F		0xac	/*	手順中断肯定				| 0x35	*/

#define		PPS_F		0xbe	/*	部分ページ信号				| 0x7d	*/
#define		PPR_F		0xbc	/*	部分ページ要求				| 0x3d	*/
#define		PRI_Q_F		0x10	/*	ポストメッセージ命令		| 0x08	*/
#define		PRI_EOM_F	0x9e	/*	手順中断 EOM				| 0x79	*/

/* FX 独自 PRI_Q 追加 動作は、PRI_EOM と同じ 94/9/17 Y.Suzuki */
#define		PRI_EOMX_F	0xde	/*	手順中断 EOMX				| 0x7b	*/

#define		PRI_EOP_F	0x3e	/*	手順中断 EOP				| 0x7c	*/
#define		PRI_MPS_F	0x5e	/*	手順中断 MPS				| 0x7a	*/
#define		RCP_F		0x86	/*	部分ページ制御復帰			| 0x61	*/

#define		RNR_F		0xec	/*	受信不可					| 0x37	*/
#define		RR_F		0x6e	/*	受信可						| 0x76	*/
#define		RTN_F		0x4c	/*	リトレーニング否定			| 0x32	*/
#define		RTP_F		0xcc	/*	リトレーニング肯定			| 0x33	*/
#define		TSI_F		0x42	/*	送信端末識別				| 0x42	*/
#define		FCD_F		0x06	/*	ファクシミリ符号化データ	| 0x60	*/
#define		FTT_F		0x44	/*	トレーニング失敗			| 0x22	*/

#define		NULL_FF		0x00
#define		X_BIT		0x01	/*	X bit						| 0x80	*/

#define		CM_F		0xE0
#define		JM_F		0xE1

#define		P_PWD_F		0xC1	/*	Password (for Polling)		| 0x83	*/	/** New Negotiation Procedure By O.K Feb.07,1996 **/
#define		T_PWD_F		0xA2	/*	Password (for Transmission)	| 0x25	*/	/** New Negotiation Procedure By O.K Feb.07,1996 **/
#define		SEP_F		0xA1	/*	Selective Polling			| 0x85	*/	/** New Negotiation Procedure By O.K Feb.07,1996 **/
#define		SUB_F		0xC2	/*	SubAddress					| 0x43	*/	/** New Negotiation Procedure By O.K Feb.07,1996 **/

/*----------------------------------------------------------------------*/
/*				 BY: 鈴木郁二											*/
/*			   DATE: Thu 25 Nov	 1993									*/
/*		  FILE NAME: FIF_DATA.H											*/
/*		DESCRIPTION: DIS, DTC, DCS, NSF, NSC, NSS FRAME の DATA			*/
/*----------------------------------------------------------------------*/
#define		ADDRESS_FIELD_DATA		0xFF	/*	アドレスフィールドデータ		*/
#define		NON_LAST_FRAME_DATA		0x03	/*	非最終フレーム			| 0xC0	*/
#define		LAST_FRAME_DATA			0x13	/*	最終フレーム			| 0xC8	*/

/*	各DATAの入るFrameの初期化	*/
#define		BIT_CLEAR				0x00	/*	フレームの初期化	*/

/*	拡張 Field BIT	*/
#define		EXPAND_FIELD_BIT		0x80	/*	拡張フィールド		*/

/*----< DIS, DTC, DCS >------------------------------------------------*/
/*	1byteめ	*/
/* #define		DIS_FIF_1ST_BYTE		0x00	/@	DIS, DTC 1byteめ DATA	*/
/* #define		DCS_FIF_1ST_BYTE		0x00	/@	DCS 1byteめ DATA		*/
#define		TX_G2_MODE_BIT			0x08	/*	送信機 G2 MODE			*/
#define		RX_G2_MODE_BIT			0x10	/*	受信機 G2 MODE			*/

/*	2byteめ	*/
/* #define		DIS_FIF_2ND_BYTE		0xC2	/@	DIS, DTC 2byteめ DATA			*/
#define		DCS_FIF_2ND_BYTE		0x02	/*	DCS 2byteめ DATA				*/
#define		SET_POLLING_DOC_BIT		0x01	/*	ポーリング原稿有				*/
#define		JT_T4_BIT				0x02	/*	MH, MR 機能有					*/
#define		CCITT_V27F_BIT			0x00	/*	V.27ter + フォールバックモード	*/
#define		CCITT_V27_BIT			0x08	/*	V.27ter							*/
#define		CCITT_V29ONLY_BIT		0x04	/*	V.29							*/
#define		CCITT_V29_BIT			0x0C	/*	V.27ter + V.29					*/
#define		CCITT_V33_BIT			0x1C	/*	V.27ter + V.29 + V.33			*/
#define		CCITT_V17_BIT			0x2C	/*	V.27ter + V.29 + V.33 + V.17	*/
#define		DATA_V27_2400BPS_BIT	0x00	/*	V.27ter 2400bps					*/
#define		DATA_V27_4800BPS_BIT	0x08	/*	V.27ter 4800bps					*/
#define		DATA_V29_7200BPS_BIT	0x0C	/*	V.29 7200bps					*/
#define		DATA_V29_9600BPS_BIT	0x04	/*	V.29 9600bps					*/
#define		DATA_V33_12000BPS_BIT	0x18	/*	0x14 V.33 12000bps By S.K 93/03/16	*/
#define		DATA_V33_14400BPS_BIT	0x10	/*	V.33 14400bps					*/
#define		DATA_V17_14400BPS_BIT	0x20	/*	V.17 14400bps					*/
#define		DATA_V17_12000BPS_BIT	0x28	/*	V.17 12000bps					*/
#define		DATA_V17_9600BPS_BIT	0x24	/*	V.17 9600bps					*/
#define		DATA_V17_7200BPS_BIT	0x2C	/*	V.17 7200bps					*/
#define		SET_FINE_BIT			0x40	/*	垂直解像度 7.7l/mm				*/
#define		SET_MR_BIT				0x80	/*	二次元符号化 (MR)				*/

/*	3byteめ	*/
/* #define		DIS_FIF_3RD_BYTE		0x80	/@	DIS, DTC 3byteめ DATA		*/
/* #define		DCS_FIF_3RD_BYTE		0x80	/@	DCS 3byteめ DATA			*/
#define		RX_A4_PAPER_BIT			0x00	/*	記録紙幅 A4					*/
#define		RX_B4_PAPER_BIT			0x01	/*	記録紙幅 B4					*/
#define		RX_A3_PAPER_BIT			0x02	/*	記録紙幅 A3					*/
#define		RX_ALL_PAPER_BIT		0x03	/*	本当は無効のBit 記録紙幅 A3	*/
#define		LENGTH_A4_BIT			0x00	/*	最大記録長 A4				*/
#define		LENGTH_B4_BIT			0x04	/*	最大記録長 B4				*/
#define		LENGTH_UNLIMITED_BIT	0x08	/*	最大記録長 無制限			*/
#define		SCAN_MINIMUM_TIME20		0x00	/*	最少走査線時間 20ms			*/
#define		SCAN_MINIMUM_TIME40		0x40	/*	最少走査線時間 40ms			*/
#define		SCAN_MINIMUM_TIME10		0x20	/*	最少走査線時間 10ms			*/
#define		SCAN_MINIMUM_TIME5		0x10	/*	最少走査線時間	5ms			*/
#define		SCAN_MINIMUM_TIME10_2	0x60	/*	最少走査線時間 10ms/T2		*/
#define		SCAN_MINIMUM_TIME20_2	0x30	/*	最少走査線時間 20ms/T2		*/
#define		SCAN_MINIMUM_TIME40_2	0x50	/*	最少走査線時間 40ms/T2		*/
#define		SCAN_MINIMUM_TIME0		0x70	/*	最少走査線時間	0ms			*/

/*	4byteめ	*/
/* #define		DIS_FIF_4TH_BYTE		0xC0	/@	DIS, DTC 4byteめ DATA		*/
/* #define		DCS_FIF_4TH_BYTE		0x00	/@	DCS 4byteめ DATA			*/
#define		HANDSHAKE_2400BPS_BIT	0x01	/*	2400bps ハンドシェーク		*/
#define		NON_COMPRESS_BIT		0x02	/*	非圧縮モード				*/
#define		ECM_MODE_BIT			0x04	/*	ECM機能有　					*/
#define		ECM_FRAMESIZE_64_BIT	0x08	/*	ECM送信時のフレームサイズ 64oct.	*/
#define		ERROR_LIMITING_BIT		0x10	/*	エラーリミティングモード	*/
#define		SET_MMR_BIT				0x40	/*	T.6 符号化能力 (MMR)		*/

/*	5byteめ	*/
/* #define		DIS_FIF_5TH_BYTE		0x80	/@	DIS, DTC 5byteめ DATA		*/
/* #define		DCS_FIF_5TH_BYTE		0x00	/@	DCS 5byteめ DATA			*/
#define		AVAILABLE_17_18_BIT		0x01	/*	Bit17,18 の有効性			*/
#define		TX_A4_RX_A5_BIT			0x08	/*	記録紙幅 A5 (A4原稿を縮小受信機能有り)	*/
#define		TX_A4_RX_A6_BIT			0x10	/*	記録紙幅 A6 (A4原稿を縮小受信機能有り)	*/

/*	6byteめ	*/
/* #define		DIS_FIF_6TH_BYTE		0x80	/@	DIS, DTC 6byteめ DATA				*/
#define		SUPER_FINE_BIT			0x01	/*	標準 S_FINE MODE					*/
#define		OTHER_FINE_BIT			0x02	/*	300×300							*/
#define		HYPER_FINE_BIT			0x04	/*	標準 H_FINE MODE					*/
#define		INCH_BASE_BIT			0x08	/*	Inch based resolution preferred		*/
#define		METRIC_BASE_BIT			0x10	/*	Metric based resolution preferred	*/
#define		HIGH_SCAN_TIME_BIT		0x20	/*	高画質(15.4l/mm)最少伝送時間	*/
#define		SELECTIVE_POLLING_BIT	0x40	/*	選択ポーリング能力	*/

/*	7byteめ	*/
/* #define		DIS_FIF_7TH_BYTE		0x80	/@	DIS, DTC 7byteめ DATA	*/
#define		SUBADDRESSING_BIT		0x01	/*	サブアドレス能力／送信	*/
#define		PASSWORD_BIT			0x02	/*	パスワード能力／送信	*/

/*	8byteめ	*/
/* #define		DIS_FIF_8TH_BYTE		0x00	/@	DIS, DTC 8byteめ DATA	*/

/*	9byteめ */

/*	10byteめ */
#define		JBIG_BIT				0x20	/* JBIG用のビット	*/

/*----< NSF, NSC, NSS >------------------------------------------------*/
/*	1byteめ */	/*	0x00に固定	*/
/*	2byteめ */	/*	0x00に固定	*/

/*	3byteめ *//*	MAKER CODE	*/
#define		MURATA_CODE				0x45	/*	村田コード				| 0xA2	*/
#define		FUJI_XEROX_CODE			0x19	/*	富士ゼロックスコード	| 0x98	*/

/*	4byteめ	*/
/* #define		NSF_FIF_4TH_BYTE		0x1E	/@	4byteめ DATA			*/
#define		TTI_ON_BIT				0x01	/*	局名表示有				*/
#define		RCR_ON_BIT				0x02	/*	受領証発行機能有		*/
#define		MSE1_MODE_BIT			0x04	/*	MSE1					*/
#define		MSE2_MODE_BIT			0x08	/*	MSE2					*/
#define		SFINE_MODE_BIT			0x10	/*	スーパーファイン		*/
#define		SCFR_MODE_BIT			0x20	/*	短縮ハンドシェーク有	*/
#define		SMSE_MODE_BIT			0x40	/*	SMSE					*/
#define		MSE1_SMSE_MODE_BIT		0x44	/*	SMSE + MSE1				*/

/*	機能拡張フィールド (1)	*/
#define		MEMORY_OK_BIT			0x01	/*	メモリ残量有			*/
#define		MMR_USE_BIT				0x02	/*	MMR						*/
#define		DATABASE_POLLING_BIT	0x04	/*	検索ポーリング			*/
#define		SECUREMAIL_BIT			0x08	/*	親展					*/
#define		RELAYED_BROADCAST_BIT	0x10	/*	中継同報				*/
#define		CHARACTER_MAIL_BIT		0x20	/*	キャラクタメール機能	*/
#define		PASSCODE_SET_BIT		0x40	/*	パスコード有			*/

/*	機能拡張フィールド (2)	*/
#define		NO_IN_MEMORY_BIT		0x00	/*	蓄積機能無							*/
#define		MH_IN_MEMORY_BIT		0x01	/*	MH 蓄積								*/
#define		MR_IN_MEMORY_BIT		0x02	/*	MR 蓄積								*/
#define		MMR_IN_MEMORY_BIT		0x03	/*	MMR蓄積								*/
#define		POST_MSG_SPEED_BIT		0x04	/*	後手順短縮ハンドシェーク機能あり 15.Jun'94 Y.Suzuki	*/
#define		SPEED_EX_BIT			0x08	/*	着信トーン検出方式短縮ハンドシェーク有効ビット */
#define		TX300DPI_BIT			0x10	/*	副走査３００ｄｐｉ×４００ｄｐｉ '96.01.29 By t.yamaguchi */
#define		SERVICE_UTIL_ON_BIT		0x20	/*	サービスユーティリティフィールド ON	*/
#define		SERVICE_UTIL_BIT		0x40	/*	サービスユーティリティ機能(1)有		*/

/*	機能拡張フィールド (3)	*/
#define		SPEED_MODE_CHANGE_BIT	0x01	/* モード変更時の短縮ハンドシェーク機能あり 1.Jun'96 T.Yamaguchi */
#define		EFINE_MODE_BIT			0x02	/* E-FINE（Ｒ１２×11.55L/mm）交信機能あり 96/06/14 T.Yamaguchi */
#define		NSF_SERVICE_UTIL_ON_BIT 0x04	/* 高速ＲＤＳ ＮＳＦ用サービスユーティリティ */
#define		CIPHER_COM_BIT			0x08	/* 暗号化受信機能あり 1997/06/18  By T.Yamaguchi */
#define		FLASH_ROM_WRITE_BIT		0x10	/* フラッシュＲＯＭ書換え PRO_RDS_FLASH_ROM_WRITE */

/*----< MASK DATA in COMPATIBLE CHEKKING >-----------------------------*/
#define		MASK_FCF_NAME				0xFE	/*	Frame Name				*/
#define		MASK_BAUDRATE				0x3C	/*	BaudRate				*/
#define		MASK_MINIMUM_SCANNING_TIME	0x70	/*	最小走査線時間			*/
#define		MASK_MSE_MODE				0x4C	/*	MSE Mode				*/
#define		MASK_RX_LENGTH_BIT			0x0C	/*	最大原稿長				*/
#define		MASK_MEMORY_MODE			0x03	/*	拡張機能フィールド(2)の蓄積方式	*/

/*----< GENERAL BIT DATA >---------------------------------------------*/
#define BitNo1					  0x01
#define BitNo2					  0x02
#define BitNo3					  0x04
#define BitNo4					  0x08
#define BitNo5					  0x10
#define BitNo6					  0x20
#define BitNo7					  0x40
#define BitNo8					  0x80
#define RevBitNo1				  0x80
#define RevBitNo2				  0x40
#define RevBitNo3				  0x20
#define RevBitNo4				  0x10
#define RevBitNo5				  0x08
#define RevBitNo6				  0x04
#define RevBitNo7				  0x20
#define RevBitNo8				  0x01

/*----< POSITION in MODEM BUFFER >-------------------------------------*/
/* Max 8 Line (BufPos) */
#define InNS						  0 /*							   */
#define InID						  1 /*							   */
#define InSTD						  2 /*							   */
#define InPWD						  3 /*							   */
#define InSEP						  4 /*							   */
#define InSUB						  5 /*							   */

/* Max 260 Count (Pos) */
#define ADDRESS_FIELD_POS			  0 /*							   */
#define LAST_FRAME_POS				  1 /*							   */
#define FCF_POS						  2 /*							   */
#define START_HDLC_FIF_POS			  3 /*							   */
#define MAKERCODE_POS				  5 /*							   */
#define PASSCODE_POS				  7 /*							   */

/* ECM Frame size */
#define ECM_64_OCT					 64 /* ECM Frame size == 64oct	   */
#define ECM_256_OCT					256 /* ECM Frame size == 256oct	   */

/* SettingStatus[6]を読むために設定 */
#define SETTINGSTATUS_ECM_ON	  0x20	/* ECM ON					   */
#define SETTINGSTATUS_RCR_ON	  0x18	/* 受領証 ON				   */
#define SETTINGSTATUS_TCR_ON	  0x08	/* 送信証 (通信証) ON		   */

/*--------------------------------------------------*/
/*	通信フェーズの状況								*/
/*	UWORD	FaxComPhaseStatus;				*/
/*		Jan.8'94	竹内茂樹						*/
/*--------------------------------------------------*/
#define		FAX_PH_A				0x00a0

#define		FAX_TX_PH_B				(0x00b0 | TRANSMITERROR)
#define		FAX_TX_PH_B1			(0x00b1 | TRANSMITERROR)
#define		FAX_TX_PH_B2			(0x00b2 | TRANSMITERROR)
#define		FAX_TX_PH_C_BEFORE_PIX	(0x00c0 | TRANSMITERROR)
#define		FAX_TX_PH_C_PIX			(0x00c1 | TRANSMITERROR)
#define		FAX_TX_PH_C_AFTER_PIX	(0x00c2 | TRANSMITERROR)
#define		FAX_TX_PH_D				(0x00d0 | TRANSMITERROR)
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/04 */
#define		FAX_TX_PH_C_RPIX		(0x00c4 | TRANSMITERROR)
#define		FAX_TX_PH_C_AFTER_RPIX	(0x00c5 | TRANSMITERROR)
#endif /* (PRO_TX_SPEED == V34) */

#define		FAX_RX_PH_B				(0x00b0 | RECEIVEERROR)
#define		FAX_RX_PH_B1			(0x00b1 | RECEIVEERROR)
#define		FAX_RX_PH_B2			(0x00b2 | RECEIVEERROR)
#define		FAX_RX_PH_C_BEFORE_PIX	(0x00c0 | RECEIVEERROR)
#define		FAX_RX_PH_C_PIX			(0x00c1 | RECEIVEERROR)
#define		FAX_RX_PH_C_AFTER_PIX	(0x00c2 | RECEIVEERROR)
#define		FAX_RX_PH_D				(0x00d0 | RECEIVEERROR)
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/07/26 */
#define		FAX_RX_PH_C_BEFORE_RPIX	(0x00c3 | RECEIVEERROR)
#define		FAX_RX_PH_C_RPIX		(0x00c4 | RECEIVEERROR)
#define		FAX_RX_PH_C_AFTER_RPIX	(0x00c5 | RECEIVEERROR)
#endif /* (PRO_TX_SPEED == V34) */

#define		FAX_PH_E				0x00e0

/*----------------------------------------------*/
/*	(\src\galaxy\define\g3_d.hよりコピー)		*/
/*		Jan.10.'94	竹内茂樹					*/
/*----------------------------------------------*/
/* #define		T1_TIMER		35000/10		/@	Ｔ１タイマ（３５秒）	*/
#define		T3_TIMER		10000/10		/*	Ｔ３タイマ（１０秒）	*/
#define		T5_TIMER		58000/10		/*	Ｔ５タイマ（５８秒）	*/
/*	#define		NULL_F			0x00 */	/*	NULL_FFを使う				*/
/*	#define		ADDRESS_F		0xFF */	/*	ADDRESS_FIELD_DATAを使う	*/
/*	#define		LAST_F			0x13 */	/*	LAST_FRAME_DATAを使う		*/
#define		STANDARD_F				2
#define		RX_STANDARD_F			0
#define		POST_MESSAGE_F			0x0e
#define		PAGE_COUNT_MASK_BIT		0x01
/*	AnalyzeRxPostMessageFrame()でRxFrameMessage1にセット	*/
#define		INITIAL_IDENTIFICATION			1
#define		COMMAND_TO_SEND					2
#define		COMMAND_TO_RECEIVE				3
#define		PRE_MESSAGE_RESPONSE_SIGNALS	4
#define		POST_MESSAGE_COMMANDS			5
#define		POST_MESSAGE_RESPONSES			6
#define		OTHER_LINE_CONTROL_SIGNALS		7

/*	命令受信／応答受信のフラグ検出タイマ値引き数　単位は１０ｍｓ	*/
#define	TIME_OVER_3SEC			300		/* ３．０秒 　CNG送出しまがらの命令受信及び通常の応答受信 */
#define	TIME_OVER_45SEC			450		/* ４．５秒　手動受信時の１発目のＤＣＳ受信まで */
#define	TIME_OVER_48SEC			480		/* ４．８秒　ECM応答４．８秒設定時 */
#define	TIME_OVER_6SEC			600		/* ６．０秒　通常命令受信及びﾘﾓｰﾄ診断時 */

/*------------------*/
/** FinalTx/RxMode **/
/* 確定受信モード	*
/* 1994/1/13 Murata */
/*------------------*/
#define	  G2MODE			   0			/* Ｇ２モード */
#define	  G3MODE			   1			/* Ｇ３モード */
#define	  DIAGMODE			   2			/* リモート診断 */
/*------------------*/
/* FAX/TEL RETURN	*/
/* 1994/1/14 Murata */
/*------------------*/
#define		FCS_ERROR				   -1			/* FCSエラー	検出	*/
#define		DETECT_COMMAND				1			/* コマンド		検出	*/
#define		DETECT_DCS					2			/* DCS		 検出		*/
#define		DETECT_CNG					3			/* CNG		 検出		*/
#define		DETECT_BUSY					4			/* Busy Tone 検出		*/
#define		FCOM_STOP_KEY				5			/* Stop Key	 検出		*/
#define		RECEIVE						6			/* コマンド		検出	*/
#define		FCOM_TEL1_OFF_HOOK			7			/* TEL1 OFF HOOK  検出	*/
#define		FCOM_TEL2_OFF_HOOK			8			/* TEL2 OFF HOOK  検出	*/
#define		FCOM_HOOK_KEY				9			/* HOOK Key 入力　検出	*/
#define		RING_TMOUT				   10			/* Ring Time Out		*/
#define		DETECT_TMOUT			   11			/* CNG検出部Time Out	*/
#define		DETECT_STOP				   12			/* CNG検出部STOP検出	*/
#define		TX_COMMAND				   13			/* PhaeB1TxCom中		*/
#define		DETECT_MEMORY_FULL		   14			/* MemoryFull検出		*/
#define		OK_SLEEP				   15			/* 子タスク 終了同期	*/
#define		OK_RESET				   16			/* T2タイマーReset		*/
#define		FLAG_RECEIVE			   17			/* Flag Receive			*/
#define		CL1_DETECT_CNG			   18			/* Class1対応 CNG検出   */	/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
#define		CL1_IGNORE_CNG			   19			/* Class1対応 CNG検出後、代行受信不可 */	/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
#define		TMOUT_RESP				  265			/* Time Out				*/
/*--------------------------------------*/
/*	送信ページ情報を更新する時の項目	*/
/*		変数	UpdateTxPageMode		*/
/*		竹内茂樹	Jan.17'94			*/
/*--------------------------------------*/
#define		UPDATE_TOTAL_PAGE	0x01		/*	トータルページ番号を更新	*/
#define		UPDATE_MEMORY_PAGE	0x02		/*	送信ファイル番号を更新		*/
/*----------------------------------------------------------------------*/
/*	通信証ｽｲｯﾁ															*/
/*	unsigned char SYB_ConfirmationReportSwitch (この行のコメント追加 石橋 94/06/29) */
/* 1994/01/28	Y.Murata												*/
/*----------------------------------------------------------------------*/
#define		NO_CONFIRMATION_REPORT	0x00		/* なし	  */
#define		TCR_REQUEST				0x01		/* 送信証 */
#define		RCR_REQUEST				0x02		/* 受領証 */
/*--------------------------------------------------------------------------*/
/*	受信原稿ポーリング送信タイプ											*/
/*	unsigned char SetPollingTxType(void) の戻り値							*/
/*	unsigned char RxDocumentPollingTxFlag									*/
/*	25.Mar'94 Y.Suzuki														*/
/*--------------------------------------------------------------------------*/
#define		RX_DOC_POLLING_TX				1	/* 受信原稿ポーリング送信		*/
#define		SECURE_DOC_POLLING_TX			2	/* 親展原稿ポーリング送信		*/
#define		FIP_DOC_POLLING_TX				3	/* FIP原稿ポーリング送信		*/
#define		TX_DOC_POLLING_TX				4	/* 送信ｺﾏﾝﾄﾞ原稿ポーリング送信	*/
#define		SCRAMBLE_DOC_POLLING_TX			5	/* ｽｸﾗﾝﾌﾞﾙ受信原稿ポーリング送信	*/
/*----------------------------------------------------------------------*/
/*	通信の遷移状態　　　　　　　　　									*/
/*	unsigned char SYS_FaxCommStageの設定値　　　						*/
/*	27.May'94 S.Tanaka													*/
/*----------------------------------------------------------------------*/
#define		FCM_TRANSMIT					1
#define		FCM_TRANSMIT_SET				2
#define		FCM_CALLED						3
#define		FCM_RECEIVE						4
#define		FCM_RECEIVE_SET					5
#define		FCM_TERMINATE					6
#define		FCM_VOICE_CALLED				7
#define		FCM_POLLING						8
#define		FCM_ERROR_LINE					9
#define		FCM_REMOTE_FAX_TRANSMIT			10		/* 1994/09/06 Y.Murata */
#define		FCM_FLASH_ROM_WRITING			11		/* PRO_RDS_FLASH_ROM_WRITE 1998/04/07  By T.Yamaguchi */
/*--------------------------------------------------------------*/
/*	SetupRelayBroadCastRX() の戻り値追加 1995/02/09 Y.Suzuki	*/
/*--------------------------------------------------------------*/
#define		TSI_NG							2

/*-----------------------------------------------------*/
/* ワンタッチ／短縮ダイアル属性セット／リセット define */
/*-----------------------------------------------------*/
#define SET_V8_ATTRIBUTE	1		/* Ｖ８能力 */
#define SET_144_ATTRIBUTE	2		/* 短縮ハンドシェーク１４．４Ｋ */
#define SET_96_ATTRIBUTE	3		/* 短縮ハンドシェーク９．６Ｋ */
#define RESET_V8_ATTRIBUTE	4
#define RESET_144_ATTRIBUTE	5
#define RESET_96_ATTRIBUTE	6

  #if defined(FRA)
/*----------------------------------------------*/
/*	送信側会話予約のFCM_TxPhaseB1()への戻り値	*/
/*		'95/02/22	by M.HARADA					*/
/*----------------------------------------------*/
	#define		B1_OH_DETECT		1
	#define		B1_DIS_DETECT		2
	#define		B1_ETC_DETECT		3
  #endif

/*-------------------------------------------------
	モード変更時の短縮手順 By T.Yamaguchi 96/06/01
--------------------------------------------------*/
#define		USUALLY_MODE			0
#define		CNG_MODE				1
#define		HIGH_SPEED_MODE			2

/*-------------------------------------------------
	サブアドレスＢＯＸのＳＵＢ、ＰＷＤの登録状態チェック
 -------------------------------------------------*/
#define		SUB_SET				0x01	/* SUBが登録されている */
#define		PWD_SET				0x02	/* PWDが登録されている */

/*-----------------------------------------------*/
/*                 Ｖ８／Ｖ３４関係             */
/*-----------------------------------------------*/
/* Ported from Clover by H.Kubo 1997/06/27 for V8&V34 property of POPLAR_H */

	/*-----------------------------------------------------*/
	/* ＣＭ／ＪＭフレームコード T30ﾓﾆﾀ用のため仮のﾌﾚｰﾑｺｰﾄﾞ */
	/*-----------------------------------------------------*/
	/* #define CM_F				0xE0 */			/* 多分T30のﾌﾚｰﾑｺｰﾄﾞとかぶらないと思う */
	/* #define JM_F				0xE1 */
	#define V8_INFIRMATION_POS		0				/* V8ﾌﾚｰﾑ同期符号ﾎﾟｼﾞｼｮﾝ */
	#define V8_SYNCHRONIZATION_POS	1				/* V8ﾌﾚｰﾑ同期符号ﾎﾟｼﾞｼｮﾝ */

	/*------------------------*/
	/* ＣＭ／ＪＭ情報カテゴリ */
	/*------------------------*/
	/* 起呼機能 */
	#define CALL_FUNC_TAG		0x01
	#define TRANSMIT_CALL		0x81
	#define RECEIVE_CALL		0xA1
	#define TRANS_AND_REC		0xC1
	#define CALL_EXTENSION		0xE1
	/* 変調モード */
	#define MODURATION_TAG		0x05
	#define EXTENSION_OCTET		0x10
	#define V34_DUPLEX			0x40
	#define V34_HALF_DUPLEX		0x80
	#define V32_AVAILABLE		0x01
	#define V22_AVAILABLE		0x02
	#define V17_AVAILABLE		0x04
	#define V29_AVAILABLE		0x40
	#define V27_AVAILABLE		0x80
	#define V26TER_AVAILABLE	0x01
	#define V26BIS_AVAILABLE	0x02
	#define V23_DUPLEX			0x04
	#define V23_HALF_DUPLEX		0x40
	#define V21_AVAILABLE		0x80
	/* プロトコル */
	#define PROTOCOL_TAG		0x0A
	#define RECOMMENDATION_V24	0x2A
	#define PROTOCOL_EXTENSION	0xEA
	/* ＧＳＴＮ */
	#define GSTN_TAG			0x0D
	#define CALL_SELLULAR		0x20
	#define ANSWER_SELLULAR		0x40


	/*---------------------------------*/
	/* V34 StartUpProcedure 引き数の型 */
	/*---------------------------------*/
	/* struct StartUpOption ---->  struct StartUpOption_t by H.Kubo 1997/06/27 */
	struct StartUpOption_t {
		UBYTE		TransmitCI;	/* 1:CI送信 2:CNG送信 0:無音送信 */
		UBYTE		SubOption1;	/* 未使用 */
		UBYTE		SubOption2;	/* 未使用 */
	};
	/* struct StartUpDataFile ---> struct StartUpDataFile_t by H.Kubo 1997/06/27 */
	struct StartUpDataFile_t {
		UBYTE	Item;		/* スタートアップ種別 */
		UBYTE	Direction;	/* プライマリチャネル指示 1:TX_COM_MODE, 2:RX_COM_MODE */
		UBYTE	Allowed;	/* CallFunctionAllowed 1:TX_COM_MODE, 2:RX_COM_MODE 3:送受信可能 */
		struct	StartUpOption_t	Option;		/* オプション */
	};
	/* スタートアップ種別 */
	#define V34_STANDARD	0
	#define V34_MANUAL		1
	#define V34_TURNAROUND	2
	/* 起呼信号送信 TransmitCI */
	#define TRANSMIT_CI_IN_V8	1
	#define TRANSMIT_CNG_IN_V8	2

	/*-----------------------------*/
	/* V34 StartUpProcedure 戻り値 */
	/*-----------------------------*/
	/*#define NG            0 */
	#define T30_PROCEDURE	1
	#define V34_PROCEDURE	2
	#define TONE_CHECK_TIME_OUT	3	/* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/15 */

	/*----------------------------------*/
	/* Ｖ８コントロールタスク引き数の型 */
	/*----------------------------------*/
	/* struct FCM_V8ControlData ---> struct FCM_V8ControlData_t by H.Kubo 1997/06/27 */
	struct FCM_V8ControlData_t {
		UBYTE	Direction;		/* 起呼局:1(TX_COM_MODE)  応答局:2(RX_COM_MODE) */
		UBYTE	ControlStatus;
		WORD	ReturnMbxno;
	};

	/* Ｖ８コントロールステータス */
	#define CALL_CM_TX			1
	#define CALL_JM_RX			2
	#define CALL_CJ_TX			3
	#define CALL_SILENCE_TX		4
	#define ANS_CM_RX			5
	#define ANS_JM_TX			6
	#define ANS_CJ_RX			7
	#define ANS_SILENCE_TX		8

	/*------------------*/
	/* タスクメッセージ */
	/*------------------*/
	#define V21_CH2_FLAG		0xAA
	#define V21_CH2_FLAG_OFF	0xBB

	#define FCM_CNG_OFF_TIME_UP	0xFD		/* 日立特許回避（ＣＥＤ検出） By O.Kimoto 1998/04/15 */

	#define FCM_TIME_UP			0xFE


	/*--------------------------------*/
	/* Ｖ３４スタートアップステータス */
	/*--------------------------------*/
	#define V34_LINE_PROBING		1
	#define V34_EQUALIZER_TRAINING	2

	/*----------------------*/
	/* 情報カテゴリセーブ用 */
	/*----------------------*/
	#define SAVE_CATEGORY_BUF_MAX	10

	/*------------------------------------------*/
	/* スタートアップフェーズステータス DEBUG用 */
	/*------------------------------------------*/
	#define V34_INITIAL		0x0000		/* 初期化 */
	#define CALL_PHASE1_1	0x1101		/* V8ﾓｰﾄﾞに入った */
	#define CALL_PHASE1_2	0x1102		/* ﾌｪｰｽﾞ1に入った */
	#define CALL_PHASE1_3	0x1103		/* ANSam検出 */
	#define CALL_PHASE1_4	0x1104		/* CM送信開始 */
	#define CALL_PHASE1_5	0x1105		/* JM受信 */
	#define CALL_PHASE1_6	0x1106		/* CJ送信開始 */
	#define CALL_PHASE1_7	0x1107		/* 無音開始 */
	#define CALL_PHASE2_1	0x1201		/* ﾌｪｰｽﾞ2に入った */
	#define CALL_PHASE2_2	0x1202		/* ﾌｪｰｽﾞ2終了 */
	#define CALL_PHASE3		0x1300		/* ﾌｪｰｽﾞ3に入った */
	#define CALL_PHASE4		0x1400		/* ﾌｪｰｽﾞ4に入った */

	#define ANS_PHASE1_1	0x2101		/* V8ﾓｰﾄﾞに入った */
	#define ANS_PHASE1_2	0x2102		/* ﾌｪｰｽﾞ1に入った */
	#define ANS_PHASE1_3	0x2103		/* CM受信 */
	#define ANS_PHASE1_4	0x2104		/* JM送信開始 */
	#define ANS_PHASE1_5	0x2105		/* CJ受信 */
	#define ANS_PHASE1_6	0x2106		/* 無音送信中 */
	#define ANS_PHASE2_1	0x2201		/* ﾌｪｰｽﾞ2に入った */
	#define ANS_PHASE2_2	0x2202		/* ﾌｪｰｽﾞ2終了 */
	#define ANS_PHASE3		0x2300		/* ﾌｪｰｽﾞ3に入った */
	#define ANS_PHASE4		0x2400		/* ﾌｪｰｽﾞ4に入った */

	#define V34_PHASE_1		0x0100		/* ﾌｪｰｽﾞ 1 */
	#define V34_PHASE_2		0x0200		/* ﾌｪｰｽﾞ 2 */
	#define V34_PHASE_3		0x0300		/* ﾌｪｰｽﾞ 3 */
	#define V34_PHASE_4		0x0400		/* ﾌｪｰｽﾞ 4 */


/*----------------------------*/
/* オプションとして必要なもの */
/*----------------------------*/

	/*--------------------------*/
	/* メモリ消去用インデックス	*/
	/*--------------------------*/

	/* struct FCM_MemoryClearIndexData --> struct FCM_MemoryClearIndexData_t by H.Kubo 1997/06/27 */
	struct	FCM_MemoryClearIndexData_t {
		unsigned char			Status;				/* 0:消去要求無し 1:消去要求有り */
		struct	MEM_IndexData_t	Index;	/* by H.Kubo 1997/0627 */ /*	ファイル・インデックス	*/
		/* struct	MEM_IndexData		Index;	*/			/*	ファイル・インデックス	*/
	};

	/* 命令受信、応答受信引数で使用 */ /* 1996/05/17 */
	#define NON_CCRETRAIN			0	/* CC Retrain 検出したらすぐ抜ける */
	#define CONTINUE_CCRETRAIN		1	/* CC Retrain 検出したら再度入り直す */


/*-------------------------------------------------------*/
/* 主に FCM の中で使われる。 V8/V34 が使えるかどうかを判断するための値。*/
/*-------------------------------------------------------*/
/* Used in FCM_GetDataSignalingRate(), AutoCalled(), ManualReceive(). */
/* by H.Kubo 1997/07/24 */
#define 	DATA_SIGNALING_RATE_V34_BIT		0x0001  /* V34 利用可能 :1   V34 利用不可能 :0 */
#define 	DATA_SIGNALING_RATE_V17_BIT		0x0002
#define 	DATA_SIGNALING_RATE_V29_BIT		0x0004
#define 	DATA_SIGNALING_RATE_V27TER_BIT	0x0008
#define 	DATA_SIGNALING_RATE_ALL_BIT		(DATA_SIGNALING_RATE_V34_BIT |DATA_SIGNALING_RATE_V17_BIT \
											| DATA_SIGNALING_RATE_V29_BIT | DATA_SIGNALING_RATE_V27TER_BIT )


/*-----------------------------------------------*/
/*             Ｖ８／Ｖ３４関係終わり            */
/*-----------------------------------------------*/

#define DIAG_TRUE	1
#define DIAG_FALSE	0
#define DIAG_ERR	0xFF


#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
/*--------------------------------------------------------------------------*/
/* POPLAR_H 疑似２回線仕様にて通信状態が標準回線か拡張回線かを切り分ける	*/
/* UBYTE SYS_InternalLineNumber のデファイン値                              */
/* by T.Soneoka 1997/11/22                                                  */
/*--------------------------------------------------------------------------*/
#define SYS_STD_LINE_COM	0
#define SYS_EXT_LINE_COM	1
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
/************************************************************************
 * 警察FAXにおいて、どちらの回線で呼出を行っているかを			*
 * 記憶しておく変数														*
 * 2005/07/14															*
 * SMuratec 李 															*
 ************************************************************************/
#define SYS_STD_LINE_IN_CI	0x01
#define SYS_EXT_LINE_IN_CI	0x02
#define SYS_TWICE_LINE_IN_CI	(SYS_STD_LINE_IN_CI | SYS_EXT_LINE_IN_CI)
#endif /* defined (KEISATSU) */
#endif

#if defined (KEISATSU) /* 警察FAX 05/07/05 石橋正和 */

/************************************************************************
	実行中のスクランブル通信の状態(主にOPRでの状態表示で使用)
											2005/07/15 石橋正和
************************************************************************/
struct FCM_ExecutingS1Info_t {
	UBYTE Protocol;	/* 個別/一斉(SYS_PROTOCOL_KOBETSU/SYS_PROTOCOL_ISSEI) */
	BOOL Available;	/* TRUE:"S:ON" FALSE:"S:OFF" */
	UBYTE Method;	/* 共通/専用(SYS_S1_KYOTSU/SYS_S1_SENYO) */
};

/************************************************************************
	回線種別
											2005/06/22 石橋正和
************************************************************************/
#define SYS_LINE_KANYU			SYS_STD_LINE_COM	/* 加入回線 */
#define SYS_LINE_KEIDEN			SYS_EXT_LINE_COM	/* 警電回線 */

/************************************************************************
	警察FAXプロトコル
											2005/07/15 石橋正和
************************************************************************/
#define SYS_PROTOCOL_KOBETSU			0	/* 個別 */
#define SYS_PROTOCOL_ISSEI				1	/* 一斉 */

/************************************************************************
	S1 共通/専用
											2005/07/15 石橋正和
************************************************************************/
#define SYS_S1_KYOTSU					0	/* 共通 */
#define SYS_S1_SENYO					1	/* 専用 */

/*********************************************************************
	一斉指令送信時の各フェーズ間の時間[ms]
*********************************************************************/
#define FCM_ISSEI_TX_A_B_TIME				8000 /* フェーズA-B */
#define FCM_ISSEI_TX_B_C_TIME				1000 /* フェーズB-C */
#define FCM_ISSEI_TX_C_D_TIME				  80 /* フェーズC-D */
#define FCM_ISSEI_TX_D_B_TIME				3000 /* フェーズD-B */
#define FCM_ISSEI_TX_D_E_TIME				  80 /* フェーズD-E */

/*********************************************************************
	一斉指令受信時の各フェーズ間の待ち時間[ms]
*********************************************************************/
#define FCM_ISSEI_RX_D_B_TIME				9000 /* フェーズD-B */

/*********************************************************************
	FCM_IsseiRxPhaseB1()の引数
*********************************************************************/
#define FCM_ISSEI_RX_WAIT_NORMAL			0	/* FSKのみ待つ */
#define FCM_ISSEI_RX_WAIT_CNG				1	/* CNGも待つ */
#define FCM_ISSEI_RX_WAIT_OPR				2	/* スタートキー押下、指令起動信号OFFも待つ */

/*********************************************************************
	FCM_IsseiRxPhaseB1()の戻り値
*********************************************************************/
#define FCM_ISSEI_RX_CONTINUE				0	/* 一斉受信継続 */
#define FCM_ISSEI_RX_DETECT_CNG				1	/* CNG検出 */
#define FCM_ISSEI_RX_START_TX				2	/* スタートキー押下 */

/*********************************************************************
	回線種別の初期値
		(警察FAXではCountryTable[][]を使用しない)
*********************************************************************/
#define KEISATSU_LINE_TYPE_STD			DIAL_SPEED_20PPS 	/* 標準回線(加入) */
#define KEISATSU_LINE_TYPE_EXT			LINE_TYPE_TONE		/* 拡張回線(警電) */

#endif

#if defined (KEISATSU) /* 警察FAX DVT Added by SMuratec 夏 2005/11/24 */
/************************************************************************
 * 警察FAXにおいて、どちらの回線で通信完了時に、電話を上げる			*
 * 記憶しておく変数														*
 * 2005/11/24															*
 * SMuratec 夏 															*
 ************************************************************************/
#define SYS_LINE_KANYU_HANGUP	0x01
#define SYS_LINE_KEIDEN_HANGUP	0x02
#define SYS_TWICE_LINE_HANGUP	(SYS_LINE_KANYU_HANGUP | SYS_LINE_KEIDEN_HANGUP)
#endif /* defined (KEISATSU) */

#endif /* !fcm_def_h */
