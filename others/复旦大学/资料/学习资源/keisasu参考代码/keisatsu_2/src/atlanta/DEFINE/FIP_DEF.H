/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\fip_def.h */
/*----------------------------------------------------------------------*/
/*	FIP 関係 define														*/
/*----------------------------------------------------------------------*/
#ifndef fip_def_h
	#define fip_def_h

#define		FIP_DEBUG			1		/*	ＦＩＰモニタ（デバッグ用）		*/

#if 0
//#define		FIP_FRAME_MAX		136		/* FIPｺﾏﾝﾄﾞﾌﾚｰﾑ最大ｻｲｽﾞ								*/
//#define		FIP_MAIL_BOX_MAX	10		/* FIPﾒｲﾙﾎﾞｯｸｽ個数									*/
//#define		FIP_CHK_MES_MAX		11		/* FIPﾁｪｯｸﾒｯｾｰｼﾞｻｲｽﾞ								*/
//#define		FIP_RS_BUF_MAX		160		/* RS-232C中間ﾊﾞｯﾌｧ(FipRsBuffer[])ｻｲｽﾞ(RSBUFSIZE*5)	*/
//#define		FIP_TIME_STR_SIZE	7		/* 通信時間ｷｬﾗｸﾀのｻｲｽﾞ(mmm'ss")						*/
//#define		FIP_MEM_STR_SIZE	4		/* ﾚｽﾎﾟﾝｽにｾｯﾄするﾒﾓﾘｻｲｽﾞの桁数						*/
//#define		FIP_PASSCODE_MAX	5		/* FIPﾊﾟｽｺｰﾄﾞﾊﾞｯﾌｧ(FipPasscode[])ｻｲｽﾞ				*/
//#define		FIP_PAGE_STR_SIZE	3		/* FIPﾍﾟｰｼﾞ文字数(ﾁｪｯｸﾒｯｾｰｼﾞ,ｾﾝﾄﾞｺﾏﾝﾄﾞ等)			*/
//#define		FIP_COM_STR_SIZE	3		/* FIPｺﾏﾝﾄﾞ文字列("CC"など)のｻｲｽﾞ(含むnull)			*/
//#define		FIP_REMOTEID_SIZE	21		/* ﾌｧｯｸｽ受信の相手機ID(FipComRemoteID[])のｻｲｽﾞ		*/
//#define		CHAR_SIZE			80		/* ASCII Characters In Line							*/
//#define		FIP_DIAL_BUF_MAX	128		/* ﾀﾞｲﾔﾙ桁最大数	*/	/*	 @要確認@				*/
//#define		FIP_PAGE_CHAR		3		/* FIP ﾛｰｶﾙﾌﾟﾘﾝﾄでのﾍﾟｰｼﾞ指定文字数 				*/
//#define		FIP_COM_VER			'6'		/* FIP ｺﾏﾝﾄﾞﾊﾞｰｼﾞｮﾝ 								*/
#endif


/*-------------------------------------*/
/*        ＭＡＸサイズ                 */
/*-------------------------------------*/
#define		RSBUFSIZE	32			/*	DMA転送するためのﾊﾞｯﾌｧのｻｲｽﾞ=32ﾊﾞｲﾄ	*/
#define		RSNBUFFS	4			/*	送信／受信のﾃﾞｰﾀをDMA転送するためのﾊﾞｯﾌｧの本数	*/

#define		FIP_COM_VER			'6'				/* ＦＩＰコマンドバージョン							*/
#define		FIP_MAIL_BOX_MAX	 10				/* ＦＩＰメイルＢＯＸ個数							*/
#define		FIP_FRAME_MAX		133				/* ＦＩＰフレームのパラメータ部最大サイズ			*/
#define		FIP_DIAL_STR_MAX	128				/* ＦＩＰダイヤル情報最大サイズ						*/
#define		FIP_CHK_MES_SIZE	 10				/* ＦＩＰチェックメッセージサイズ(X.9._9.999)		*/
#define		FIP_PASSCODE_SIZE	  4				/* ＦＩＰパスコード情報サイズ(9999)					*/
#define		FIP_TIME_STR_SIZE	  7				/* ＦＩＰ通信時間　情報サイズ(mmm'ss")				*/
#define		FIP_MEM_STR_SIZE	  4				/* ＦＩＰ使用メモリ情報サイズ(9999)					*/
#define		FIP_PAGE_STR_SIZE	  3				/* ＦＩＰ開始ページ情報サイズ(999)					*/
#define		FIP_REMOTEID_SIZE	 21				/* ＦＩＰ受信の相手機ＩＤのサイズ					*/
#define		FIP_CHAR_SIZE		124				/* フィルインＡＳＣＩＩ文字数／ライン（Ａ３対応）	*/
#define		FIP_RS_BUF_SIZE		RSBUFSIZE*1		/* ＲＳ２３２Ｃ受信中間バッファサイズ(32*1)			*/
#define		FIP_BLOCK_SIZE		0x2000			/* ＦＩＰメモリブロック容量サイズ単位(8192Byte単位)	*/

/*-------------------------------------*/
/*        ＦＩＰステータス             */
/*-------------------------------------*/
#define		FIP_IDLE			0x0000		/* ｱｲﾄﾞﾙ						*/
#define		FIP_GENERAL			0x0001		/* 待機中						*/
#define		FIP_CHECK_CMD		0x0002		/* ﾁｪｯｸ･ｺﾏﾝﾄﾞ実行中				*/
#define		FIP_FILLIN_CMD		0x0004		/* ﾌｨﾙｲﾝｺﾏﾝﾄﾞ実行中				*/
#define		FIP_LOCALSCAN_CMD	0x0008		/* ﾛｰｶﾙｽｷｬﾝｺﾏﾝﾄﾞ実行中			*/
#define		FIP_LOCALPRINT_CMD	0x0010		/* ﾛｰｶﾙﾌﾟﾘﾝﾄｺﾏﾝﾄﾞ実行中			*/
#define		FIP_SEND_CMD		0x0020		/* 送信ｺﾏﾝﾄﾞ実行中				*/
#define		FIP_POLLING_CMD		0x0040		/* ﾎﾟｰﾘﾝｸﾞｺﾏﾝﾄﾞ実行中			*/
#define		FIP_RECEIVE_CMD		0x0080		/* 受信ｺﾏﾝﾄﾞ実行中(含むﾌﾟﾘﾝﾄ)	*/
#define		FIP_SECURERX_CMD	0x0100		/* SecureMail受信ｺﾏﾝﾄﾞ実行中	*/
#define		FIP_MEMPRINT_CMD	0x0200		/* ﾛｰｶﾙﾌﾟﾘﾝﾄの原稿ﾌﾟﾘﾝﾄ中		*/
#define		FIP_RETRIEVE_CMD	0x0400		/* 原稿取り出し中(ｽｷｬﾝ/受信)	*/
#define		FIP_CONTROL			0x0800		/* ﾎﾟｰﾄﾃｽﾄ実行中				*/
#define		FIP_DURING_RX		0x1000		/* 受信中						*/
#define		FIP_WAIT_ANSWER		0x2000		/* ｱﾝｻｰﾌﾚｰﾑ待ち(未使用)			*/

/*-------------------------------------*/
/*        制御コード                   */
/*-------------------------------------*/
#define		FIP_INIT_SET_NUM	5			/* ﾌﾚｰﾑ送出時の識別子の個数		*/
#define		FIP_INIT_DET_NUM	2			/* ﾌﾚｰﾑ検出時の識別子の個数		*/
#define		CTRL_F				0x06		/* ﾌﾚｰﾑ識別子 (Ctrl-F ｺｰﾄﾞ)		*/
#ifndef		CR	/* std.hでも定義されている */
#define		CR					0x0D		/* CR ｺｰﾄﾞ (ﾌﾚｰﾑﾃﾞﾘﾐﾀ1)			*/
#endif
#define		LF					0x0A		/* LF ｺｰﾄﾞ (ﾌﾚｰﾑﾃﾞﾘﾐﾀ2)			*/
#define		ESC					0x1B
#define		SI					0x0F
#define		TAB					0x09
#define		XON					0x11
#define		XOFF				0x13

/*-------------------------------------*/
/*        戻り値                       */
/*-------------------------------------*/
#define		FIP_OK				 0			/*									*/
#define		FIP_NG		 		-1			/* 									*/
#define		FIP_ERR		 		-2			/* 									*/

#define		FIP_NO_PAPER		-1			/* 記録紙なし FipGetPaperSize() */
#define		FIP_CASSETTE_OPEN	-2			/* ｶｾｯﾄｵｰﾌﾟﾝ  FipGetPaperSize() */

#if 0
//#define		FIP_OK			1
//#define		FIP_NG			0
#endif
#define		FRM_OK				1			/* ｺﾏﾝﾄﾞﾌﾚｰﾑ正常 */
#define		FRM_ERR				0			/* ﾌﾚｰﾑｴﾗｰ(ｺﾏﾝﾄﾞの末尾に'\0'<CR,LF>なし) */
#define		COM_ERR				-1			/* ｺﾏﾝﾄﾞｴﾗｰ(ｺﾏﾝﾄﾞｵﾌﾟｼｮﾝ形式が不正) */
#define		PRT_ERR				-2			/* Printerｴﾗｰ(Unuse Printer) */

/*-------------------------------------*/
/*        フレーム種別                 */
/*-------------------------------------*/
/* 0-3bit: 任意												*/
/* 4Bit  : 要求／応答	0= ｺﾏﾝﾄﾞ     1= ﾚｽﾎﾟﾝｽ  			*/
/* 5Bit  : 受信／送信	0= ﾎｽﾄ→FIP  1= FIP→ﾎｽﾄ			*/
/* 6Bit  : 双方向ﾌﾚｰﾑ	0= 5Bit参照  1= FIP←→ﾎｽﾄ			*/
/* 7Bit  : 正常／異常	0= OK        1= NG      			*/
#define		FIP_FRM_RES_BIT		0x10		/* ﾚｽﾎﾟﾝｽ  Bit						*/
#define		FIP_FRM_SND_BIT		0x20		/* FIP→ﾎｽﾄBit						*/
#define		FIP_FRM_ERR_BIT		0x80		/* 異  常  Bit						*/
											/*	ｺﾏﾝﾄﾞﾌﾚｰﾑ						*/
#define		FIP_FRM_CC 			0x01		/* ﾎｽﾄ → FIP : ﾁ ｪ ｯ ｸ   ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_FI 			0x02		/*            : ﾌ ｨ ﾙ ｲ ﾝ ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_LS 			0x03		/*            : ﾛｰｶﾙｽｷｬﾝ  ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_LP 			0x04		/*            : ﾛｰｶﾙﾌﾟﾘﾝﾄ ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_SC 			0x05		/*            : ｾ ﾝ ﾄﾞ    ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_PC 			0x06		/*            : ﾎﾟｰﾘﾝｸﾞ   ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_UND			0x80		/*            : 未 定 義  ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_ABN			0x81		/*            : ﾃﾞｰﾀ異常  ｺﾏﾝﾄﾞ		*/
#define		FIP_FRM_ILG			0x82		/*            : ﾌﾚｰﾑ異常  ｺﾏﾝﾄﾞ		*/
											/*	ｱﾝｻｰﾌﾚｰﾑ						*/
#define		FIP_FRM_AY 			0x11		/* ﾎｽﾄ → FIP :(受信可能) ｱﾝｻｰ		*/
#define		FIP_FRM_AN 			0x12		/*            :(受信不可) ｱﾝｻｰ		*/
											/*	ﾘｸｴｽﾄﾌﾚｰﾑ						*/
#define		FIP_FRM_RR 			0x21		/* FIP → ﾎｽﾄ : 受  信    要  求	*/
											/*	ﾚｽﾎﾟﾝｽﾌﾚｰﾑ						*/
#define		FIP_FRM_CR1			0x31		/* FIP → ﾎｽﾄ : ﾁ ｪ ｯ ｸ   ﾚｽﾎﾟﾝｽ	*/
#define		FIP_FRM_SR1			0x32		/*            : ｾ ﾝ ﾄﾞ    ﾚｽﾎﾟﾝｽ	*/
#define		FIP_FRM_LR1			0x33		/*            : ﾛ ｰ ｶ ﾙ   ﾚｽﾎﾟﾝｽ1	*/
#define		FIP_FRM_LR2			0x34		/*            : ﾛ ｰ ｶ ﾙ   ﾚｽﾎﾟﾝｽ2	*/
											/*	ﾌﾚｰﾑﾍｯﾀﾞｰ/ｴﾝﾄﾞ					*/
#define		FIP_FRM_FTH			0x41		/* ﾎｽﾄ←→FIP : ﾃｷｽﾄ ﾌﾚｰﾑ ﾍｯﾀﾞ-		*/
#define		FIP_FRM_FIH			0x42		/*            : ｲﾒｰｼﾞﾌﾚｰﾑ ﾍｯﾀﾞ-		*/
#define		FIP_FRM_FIE			0x43		/*            : ｲﾒｰｼﾞﾌﾚｰﾑ ｴﾝﾄﾞ		*/
#define		FIP_FRM_FPE			0x44		/*            : ﾃｷｽﾄﾍﾟｰｼﾞ ｴﾝﾄﾞ		*/
#define		FIP_FRM_FTE			0x45		/*            : ﾃｷｽﾄ ﾌﾚｰﾑ ｴﾝﾄﾞ		*/

/*-------------------------------------*/
/*        原稿情報                     */
/*-------------------------------------*/
/*	ﾌｨﾙｲﾝ ｺｰﾃﾞｨﾝｸﾞ方式 (FipCordingMethod)	*/
#define		FIP_RL			0
#define		FIP_MH			1

/*	ﾌｫﾝﾄﾀｲﾌﾟ								*/
#define		FONT_0			0
#define		FONT_1			1
#define		FONT_2			2
#define		FONT_3			3

/*-------------------------------------*/
/*        チェックメッセージ種別       */
/*-------------------------------------*/
#define		NO_ERR			' '			/*	OK : " . .  .nnn"	*/
#define		LOCAL_ERR		'L'
#define		DIAL_ERR		'D'
#define		TX_ERR			'T'
#define		RX_ERR			'R'
#define		FRAME_ERR		'F'
#define		MEMORY_ERR		'M'

#if 0
//#define	IMAGE			1			/* Image Data */
//#define	ASCII			2			/* ASCII Data */
//#define	FIP_WHITE		0x00		/*	*/
//#define	FIP_BLACK		0xFF		/*	*/
//#define	MRY_BLKSZ		256			/* Document_Memory Block Size (product.h の MEM_BLOCK_SIZE を使用) */
//#define	RW_BLKSZ		32			/* Port Buffer Memory Size    (fiprsque.h の RSBUFSIZE を使用)*/
#endif

/* FIP送信ﾎﾞｰﾚｲﾄ (ｾﾝﾄﾞﾚｽﾎﾟﾝｽでの送信ﾎﾞｰﾚｲﾄ) */
#define		FIP2400BPS			'1'
#define		FIP4800BPS			'2'
#define		FIP7200BPS			'3'
#define		FIP9600BPS			'4'
#define		FIP12000BPS			'5'
#define		FIP14400BPS			'6'

/*-------------------------------------*/
/*        ＦＩＰモニタ関係             */
/*-------------------------------------*/
#define		FIP_MON_BUF_MAX		16		/*	モニタ情報１６件(x32Byte)	*/
#define		FIP_MON_FRM_SIZE	 5		/*	フレーム識別コードサイズ	*/
#define		FIP_MON_PRM_SIZE	26		/*	フレームパラメータサイズ	*/
#define		FIP_MON_RXF			0x01	/*	受信フレーム				*/
#define		FIP_MON_TXF			0x02	/*	送信フレーム				*/
#define		FIP_MON_PRM			0x03	/*	フレームパラメータ			*/

/*-------------------------------------*/
/*   ドライバの状態 (RsDriver.status)  */
/*-------------------------------------*/
/* ﾎﾟｰﾄﾃｽﾄ時	*/
#define		SLEEP				0
#define		TEST				1

/*	受信時	*/
/* #define		SLEEP			0		@:	停止中	*/
#define		WAKEUP				1		/*	受信起動	*/
#define		RUN					2		/*	受信中	*/
#define		SEND_XOFF			3		/*	Xoff送出	*/
#define		OVER_RUN			4		/*	受信ﾊﾞｯﾌｧ･ﾌﾙ	*/
#define		SEND_XON			5		/*	Xon送出要求	*/
#define		RX_UNDER_RUN		6		/*	受信完了ﾃﾞｰﾀﾊﾞｯﾌｧ待ち	*/

/*	送信時	*/
/* #define		SLEEP			0		@*	停止中	*/
/* #define		WAKEUP			1		@*	送信起動	*/
/* #define		RUN				2		@*	送信中	*/
#define		UNDER_RUN			3		/*	送信ﾊﾞｯﾌｧなし	*/
#define		RCV_XOFF			4		/*	Xoff受信で停止中(送信待ちﾊﾞｯﾌｧはある)	*/
#define		RCV_XON				5		/*	Xon受信	*/
#define		TX_OVER_RUN			6		/*	送信ﾃﾞｰﾀを格納する空きﾊﾞｯﾌｧ待ち	*/

/*---------------------------------------------------*/
/*   ＲＳデバイスのオープン・モード (RsDevice.mode)  */
/*---------------------------------------------------*/
#define		RSIDLE				0		/*	未使用の状態	*/
#define		RSTEST				't'		/*	RS232C ﾎﾟｰﾄﾃｽﾄ･ﾓｰﾄﾞ	*/
#define		RSWRITE				'w'		/*	送信ﾓｰﾄﾞ	*/
#define		RSREAD				'r'		/*	受信ﾓｰﾄﾞ	*/

/*-----------------------------------------*/
/*   ＲＳデバイスの状態 (RsDevice.status)  */
/*-----------------------------------------*/
#define		RS_STOP				0		/*	停止中	*/
#define		RS_WAIT				1		/*	送／受信起動後	*/
#define		RS_TRX 				2		/*	送信中／受信中	*/
#define		RS_EOF				3		/*	ﾃﾞｰﾀの終端受付／受付	*/
#define		RS_CLOSE			4		/*	ｸﾛｰｽﾞ処理完了	*/
#define		RS_ERR				-1		/*	ﾀｲﾑｱｳﾄ･ｴﾗｰ発生	*/
#define		RS_ABORT			-2		/*	受信強制停止	*/

/*-------------------------------------*/
/*        ＣＴＳ制御                   */
/*-------------------------------------*/
#define		CTS_ON				1		/* "Low" :1 -> "High":0	（送信停止）*/
#define		CTS_OFF				0		/* "High":0 -> "Low" :1	（送信開始）*/

/*-------------------------------------*/
/*        ＦＩＰタイムオーバー         */
/*-------------------------------------*/
#define		RS_TIME_OUT			60		/* RsOpen()のﾀｲﾑｱｳﾄ */
#define		RS_AF_RX_TIMEOUT	15		/* RR送信からAY/AN受信までの時間 */

/*-------------------------------------*/
/*        ポートテスト                 */
/*-------------------------------------*/
#define		RS_TEST_TIMES		100		/* エコーバックテストの回数 */

/*-------------------------------------*/
/*        ＲＳ２３２Ｃ受信エラー       */
/*-------------------------------------*/
#define		RS_PARITY_ERROR		1		/* パリティ・エラー */
#define		RS_OVERRUN_ERROR	2		/* オーバーラン・エラー */
#define		RS_FRAMING_ERROR	3		/* フレーミング・エラー */

/*----------------------------------------------------------*/
/*  割り込みルーチン → 割り込み監視タスクに対するイベント  */
/*----------------------------------------------------------*/
#define		RS_TIMEOUTEVT		0x01		/* ｲﾍﾞﾝﾄ無し時間が制限時間を越えた	*/
#define		XON_RCV				0x02		/* XOFFを受信した後にXONを受信した (送信時)	*/
#define		FIRST_RCV			0x04		/* １番最初のデータを受信した (受信時)	*/
#define		MPSC_ERR			0x08		/* MPSCでｴﾗｰ発生 (受信時)	*/
#define		DMA_FIPWAKEUP		0x10		/* FIP_TASKをwakeup  ADD  Aug.23 '94  */
#define		CTS_RCV				0x20		/* CTS端子がONした	*/

/*-------------------------------------*/
/*        ＤＭＡ方向                   */
/*-------------------------------------*/
#define		FIP_DMA_IO_TO_MEM	0
#define		FIP_DMA_MEM_TO_IO	1

/*-------------------------------------*/
/*        ソフトコーデック関係         */
/*-------------------------------------*/
#define	FIP_DRAM_ACS_ADR		0x7c000000

#define		RL_EOL				'/'			/*	タグＲＬのＥＯＬ値（0x2F）	*/
#define		MH_EOL				(2560+64)	/*	ＭＨテーブル上のＥＯＬ値(64x41)	*/
#define		SCD_TAG_RL			0xc0
#define		SCD_TAG_MKUP		0xc0
#define		SCD_TAG_TERM		0x80
#define		SCD_TAG_MH			0x80
#define		SCD_RTC_DET_NUM		3			/* 2 -> 3 By M.T 1995/06/07 */
#define		SCD_RTC_SET_NUM		6
#define		SCD_MH_MKUP_MAX		2560		/*	64 x 40	*/
#define		SCD_MH_TERM_MAX		63
#define		SCD_RL_MKUP_MAX		4032		/*	64 x 63	*/
#define		SCD_RL_TERM_MAX		63

#define		SCD_OK				 0		/*	正常					*/
#define		SCD_NG				-1		/*	異常					*/
#define		SCD_RD_ERR			-2		/*	リードエラー発生		*/
#define		SCD_WR_ERR			-3		/*	ライトエラー発生		*/
#define		SCD_DT_END			-4		/*	リードデータ終了		*/

							/*	ScdOpen(),ScdExe(),ScdClose()の引数	*/
#define		SCD_MH_TO_TAGRL		1		/*	リトリーブ：タグＲＬ	*/
#define		SCD_MH_TO_TAGMH		2		/*	リトリーブ：タグＭＨ	*/
#define		SCD_TAGMH_TO_MH		3		/*	フィルイン：タグＭＨ	*/
#define		SCD_TAGRL_TO_MH		4		/*	フィルイン：タグＲＬ	*/
#define		SCD_ASCII_TO_MH		5		/*	フィルイン：ＡＳＣＩＩ	*/

							/*	文字書き出し位置（標準モード基準）	*/
#define		SCD_LEFT_MARGIN		224		/*	左マージン画素数		*/

							/*	ScdATRBuffer[],ScdATRDataの設定値	*/
/*#define	SCD_ANK				0x00	@*	文字修飾　：通常		*/
/*#define	SCD_KANJI			0x01	@*	文字修飾　：漢字		*/
#define		SCD_TWICE			0x02	/*	文字修飾　：倍角		*/
/*#define	SCD_MESH			0x04	@*	文字修飾　：網掛け		*/
#define		SCD_INVERT			0x08	/*	文字修飾　：反転		*/

#if 0
//#if (KIRI)
//#define		FIP_BLOCK_NUMBER	4		/*	16/4 = 4	*/
//#endif
//#if (MOMIJI)
//#define		FIP_BLOCK_NUMBER	64		/*	16/0.25 = 64	*/
//#endif
#endif

/*---------------------------------------------------------------------------*/
/*        構　造　体　定　義　（ＲＡＭ領域）       fip_data.c                */
/*---------------------------------------------------------------------------*/
/*----------------------------------*/
/*	ＦＩＰモニタバッファ(fip_chk.c)	*/
/*----------------------------------*/
struct	fipmonbuf_s_t {
	UBYTE		id;
	UBYTE		frm[FIP_MON_FRM_SIZE];
	UBYTE		prm[FIP_MON_PRM_SIZE];
};
typedef	struct fipmonbuf_s_t		FIPMONDATA_t;

/*----------------------------------*/
/*	ＦＩＰメイルＢＯＸ(fip_chk.c)	*/
/*----------------------------------*/
struct	fipmailbox_t {
	UWORD		page;
	UWORD		block;
};

/*----------------------------------*/
/*	バイト／ワードデータ(fip_scdc.c)*/
/*----------------------------------*/
union ByteWordData_u {
	struct{
#if (0)
//#if (PRO_CPU == V53)
//		UBYTE	L;
//		UBYTE	H;
//#else
#endif
		UBYTE	H;
		UBYTE	L;
/* #endif */
	} Byte;
	UWORD		Word;
};
typedef union ByteWordData_u_t	SCDBWDT_t;

/*-------------------------------------------*/
/*	RS232C上で　送信／受信するﾃﾞｰﾀ･ﾊﾞｯﾌｧの	 */
/*	ｷｭｰ、ｷｭｰ･ｺﾝﾄﾛｰﾙ･ﾌﾞﾛｯｸの定義				 */
/*-------------------------------------------*/
/* mpsc_int.asm中で　ﾃﾞﾀｰのﾎﾟｲﾝﾀを進める時に　ﾏｯｼﾞｯｸ･ﾅﾝﾊﾞｰを使用している	*/
/*	ので "RSBUFSIZE" を変更する時は注意する事									*/
/* dma3_int.asm中で　ﾊﾞｯﾌｧのｲﾝﾃﾞｯｸｽを進める時に　ﾏｯｼﾞｯｸ･ﾅﾝﾊﾞｰを使用している	*/
/*	ので "RSNBUFFS" を変更する時は注意する事									*/

struct rsbuf_t {
	UWORD		benqp;			/*	どのrsbufに書き込むのかのｲﾝﾃﾞｯｸｽ	*/
	UWORD		bdeqp;			/*	どのrsbufから読み出すかのｲﾝﾃﾞｯｸｽ	*/
	UWORD		currentp;		/*	割込みで送／受信する(Xon/Xoff)ﾎﾟｲﾝﾀ	*/
	struct bufblk_t{
		UBYTE		*bufp;		/*	送信／受信ﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ	*/
		UWORD		bufsize;	/*                   ｻｲｽﾞ	*/
		UWORD		datasize;	/*	ﾊﾞｯﾌｧ中に入っているﾃﾞｰﾀのｻｲｽﾞ	*/
	} rsbuf[RSNBUFFS];
};

/*------------------------------------------*/
/*	RS232C 下位ﾊｰﾄﾞｳｪｱ(ﾄﾞﾗｲﾊﾞ)(MPSC,DMA)	*/
/*	のﾊｰﾄﾞｳｪｱ･ｺﾝﾄﾛｰﾙ･ﾌﾞﾛｯｸの定義			*/
/*------------------------------------------*/
struct rsdrv_t {
	BYTE		status;			/*	送信中、受信ｵｰﾊﾞﾌﾛｰ等の状態	*/
	BYTE		xflow;			/*	Xon / Xoff の送受信状況		*/
	BYTE		cts;			/*	CTSの状況					*/
	UBYTE		mpsc_trx;		/*	MPSCの送受信動作ｽﾃｰﾀｽ(SR0)	*/
	UBYTE		mpsc_es;		/*	E/Sｽﾃｰﾀｽ(SR1)				*/
	UBYTE		mpsc_cr1;		/*	Save: MPSC CR1				*/
	UBYTE		mpsc_cr3;		/*	Save: MPSC CR3				*/
	UBYTE		mpsc_cr5;		/*	Save: MPSC CR5				*/
	UBYTE		*dma_address;	/*	Save: Current DMA ｱﾄﾞﾚｽ		*/
	UWORD		dma_count;		/*	Save: Current DMA ｶｳﾝﾀ		*/
	UWORD		dma_count_save;	/*	Save: Current DMA ｶｳﾝﾀｾｰﾌﾞ	*/	/* Add By M.T 1995/03/25 */
	UWORD		mpsc_isr_event;	/*	MPSCからのｲﾍﾞﾝﾄNo			*/
	UWORD		dma_isr_event;	/*	DMAからのｲﾍﾞﾝﾄNo			*/
};

/*---------------------------------------*/
/*	RS232C ﾘｰﾄﾞ/ﾗｲﾄ　上位i/fﾙｰﾁﾝの為の   */
/*	ﾃﾞﾊﾞｲｽ･ｺﾝﾄﾛｰﾙ･ﾌﾞﾛｯｸの定義            */
/*---------------------------------------*/
struct rsdev_t {
	BYTE		mode;			/*	ｵｰﾌﾟﾝのﾓｰﾄﾞ										*/
	BYTE		cdphase;		/*	Command.Response / ImageData => LF検出しない	*/
	BYTE		status;			/*	ﾃﾞﾊﾞｲｽの状態									*/
	BYTE		dummy;			/*	ﾀﾞﾐｰ											*/
	UWORD		qindex;			/*	現在ｱｸｾｽ中のRS232C-DMAﾊﾞｯﾌｧのｲﾝﾃﾞｯｸｽ			*/
	UBYTE 		*dp;			/*	RS232C-DMAﾊﾞｯﾌｧ中のｱｸｾｽ･ﾎﾟｲﾝﾀ					*/
	UWORD		dsize;			/*	上記ﾊﾞｯﾌｧにﾘｰﾄﾞ/ﾗｲﾄ可能な残りﾃﾞｰﾀ長				*/
	UBYTE		*bufp;			/*	上位ﾙｰﾁﾝが渡してくるﾃﾞｰﾀ･ﾊﾞｯﾌｧのｱｸｾｽ･ﾎﾟｲﾝﾀ		*/
	UWORD		bufsize;		/*	上記ﾊﾞｯﾌｧにﾘｰﾄﾞ/ﾗｲﾄしたﾃﾞｰﾀ長					*/
	WORD		timeout;		/*	ﾃﾞｰﾀを送受信していない時間のﾀｲﾑｱｳﾄ値(秒)の最大値*/
	WORD		timecount;		/*	ﾀｲﾏｰｲﾍﾞﾝﾄ(100mS)の発生した回数					*/
};

/*---------------------------------------------------------------------------*/
/*        構　造　体　定　義　（ＲＯＭ領域）       fipmhtbl.c / fip_tbl.c    */
/*---------------------------------------------------------------------------*/
/*----------------------------------*/
/*	コマンド実行関数登録テーブル	*/
/*----------------------------------*/
struct fipcomexetbl_s_t {
	UBYTE		CmdCode;
	WORD		(*Function)(UBYTE *);		/*	注）FARアクセス NEARコール	*/
};
typedef	CONST struct fipcomexetbl_s_t		FIPEXETBL_t;

/*----------------------------------*/
/*	フレーム名称登録テーブル		*/
/*----------------------------------*/
struct	fipfrmtable_s_t{
	UBYTE		FrmName[4];
	UBYTE		FrmCode;
};
typedef	CONST struct fipfrmtable_s_t 		FIPFRMTBL_t;

/*----------------------------------*/
/*	ＭＨデコード１次テーブル		*/
/*----------------------------------*/
struct MH_DC_Table1_t {
	UWORD		RunLength;			/*	ランレングス				*/
};
typedef	CONST struct MH_DC_Table1_t		MH_DC_TABLE1_t;

/*----------------------------------*/
/*	ＭＨデコード２次テーブル		*/
/*----------------------------------*/
struct MH_DC_Table2_t {
	MH_DC_TABLE1	*Adr;				/*								*/
	UBYTE			MaskBit;			/*	マスクビット(01～1F)		*/
};
typedef	CONST struct MH_DC_Table2_t		MH_DC_TABLE2_t;

/*----------------------------------*/
/*	ＭＨエンコードテーブル			*/
/*----------------------------------*/
struct MH_EC_Table_t {
	UBYTE		BitLength;			/*	ビット長					*/
	UBYTE		MHData;				/*	ＭＨデータ（下位８ビット）	*/
};
typedef	CONST struct MH_EC_Table_t 	MH_EC_TABLE_t;

#endif
