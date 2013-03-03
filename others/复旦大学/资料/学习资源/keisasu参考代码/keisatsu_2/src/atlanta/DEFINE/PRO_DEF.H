/*---------------------------------------------------------------------------*/
/*  プロジェクト : ATLANTA                                                   */
/*  ファイル名   : PRO_DEF.H                                                 */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1996/11/12                                                */
/*  概  要       : オプションボード機能スペック定義ファイル                  */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef	pro_def_h
	#define pro_def_h

/*---------------------------*/
/* ホスト機器の性能 20バイト */
/*---------------------------*/
struct SYS_MachinePerformanceData_t {
	UBYTE AvailableRxResolution;	/* 受信可能線密度	*/
	UBYTE AvailableRxResolutionSub;	/* 受信可能線密度SUB*/
	UBYTE PaperSizeMAX;				/* 最大記録紙サイズ	*/
	UBYTE TxMinimumScanningTime;	/* 最小伝送時間		*/
	UBYTE TxMinimumScanningTimeSub;	/* 最小伝送時間SUB	*/
	UBYTE RxMinimumScanningTime;	/* 最小伝送時間		*/
	UBYTE RxMinimumScanningTimeSub;	/* 最小伝送時間SUB	*/
	UBYTE AvailableTxCodingMethod;	/* 通信符号化方式	*/
	UBYTE AvailableRxCodingMethod;	/* 通信符号化方式	*/
	UBYTE TxModeMethod;				/* インチ／ミリ		*/
	UBYTE RxModeMethod;				/* インチ／ミリ		*/
	UBYTE TxMSE_Method;				/* ＳＭＳＥモード	*/
	UBYTE RxMSE_Method;				/* ＳＭＳＥモード	*/
	UBYTE Reserve14;
	UBYTE Reserve15;
	UBYTE Reserve16;
	UBYTE Reserve17;
	UBYTE Reserve18;
	UBYTE Reserve19;
	UBYTE Reserve20;
};

	/* 受信可能線密度主走査	*/
	#define	PRO_SPEC_200_200_MODE		0
	#define	PRO_SPEC_200_400_MODE		1
	#define	PRO_SPEC_300_300_MODE		2
	#define	PRO_SPEC_300_400_MODE		3
	#define	PRO_SPEC_400_400_MODE		4
	#define	PRO_SPEC_600_600_MODE		5

	/* 受信可能線密度	*/
	/* 予約 */

	/* 最大記録紙サイズ	*/
	#define	PRO_SPEC_MAX_PAPER_SIZE_A4		0
	#define	PRO_SPEC_MAX_PAPER_SIZE_B4		1
	#define	PRO_SPEC_MAX_PAPER_SIZE_A3		2

	/* 最小伝送時間		*/
	#define	PRO_SPEC_SCANNING_TIME40		0
	#define	PRO_SPEC_SCANNING_TIME20		1
	#define	PRO_SPEC_SCANNING_TIME10		2
	#define	PRO_SPEC_SCANNING_TIME5			3
	#define	PRO_SPEC_SCANNING_TIME40_2		4
	#define	PRO_SPEC_SCANNING_TIME20_2		5
	#define	PRO_SPEC_SCANNING_TIME10_2		6
	#define	PRO_SPEC_SCANNING_TIME0			7

	/* 最小伝送時間SUB	*/
	#define	PRO_SPEC_SCAN_HIGHER_RESOLUTION		0x01	/* DIS/DTC ﾋﾞｯﾄ46をｾｯﾄする */

	/* 通信符号化方式		*/
	#define	PRO_SPEC_IMAGE_DATA		0
	#define	PRO_SPEC_MH_CODE		1
	#define	PRO_SPEC_MR_CODE		2
	#define	PRO_SPEC_MMR_CODE		3

	#define PRO_SPEC_MG3_CODE		4	/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */


	/* インチ／ミリ		*/
	#define	PRO_SPEC_METRIC			0	/* ミリ */
	#define	PRO_SPEC_INCH			1	/* インチ */


	/* ＳＭＳＥモード	*/
	#define	PRO_SPEC_NOMSE		0
	#define	PRO_SPEC_MSE1		1
	#define	PRO_SPEC_MSE2		2
	#define	PRO_SPEC_SMSE		3


/*-------------------------------------------------*/
/* グレープに動作させたい機能（マスター／スレーブ）*/
/*-------------------------------------------------*/
/*UWORD	SYS_OptionBoaudFunctionTable[8][5];*/	/* ８回線分 80バイト */
												/* グレープでは１つだけもつ */
/* 0 */
	#define PRO_FUNC_TEL_FAX_MODE		0x0001	/* ＴＥＬ／ＦＡＸ	*/
	#define PRO_FUNC_ANS_FAX_MODE		0x0002	/* ＡＮＳ／ＦＡＸ	*/
	#define	PRO_FUNC_TEL_MODE			0x0004	/* ＴＥＬ			*/
	#define	PRO_FUNC_REMOTE_DIAG		0x0008	/* リモート診断		*/
	#define	PRO_FUNC_PIN				0x0010	/* ＰＩＮアクセス	*/
	#define	PRO_FUNC_RING_MASTER		0x0020	/* リングマスター	*/
	#define	PRO_FUNC_CLASS1				0x0040	/* クラス１			*/
	#define	PRO_FUNC_CLASS2				0x0080	/* クラス２			*/
	#define	PRO_FUNC_POLLING_TX			0x0100	/* ポーリング送信	*/
	#define	PRO_FUNC_DB_POLLING_TX		0x0200	/* 検索ポーリング送信 */
	#define	PRO_FUNC_SECURE_RX			0x0400	/* 親展受信			*/
	#define	PRO_FUNC_RELAYED_TX			0x0800	/* 中継配信			*/
	#define	PRO_FUNC_RELAYED_RELAY_TX	0x1000	/* 中中継			*/
	#define	PRO_FUNC_RELAYED_REPORT		0x2000	/* 不達通知			*/
	#define	PRO_FUNC_DIALIN				0x4000	/* ダイアルイン		*/
	#define	PRO_FUNC_ERASE_TX_MEM_PAGE	0x8000	/* 送信済みメモリの消去 */

/* 1 */
	#define	PRO_FUNC_JUNK_FAX_MODE_TYPE	0x0001	/* ﾀﾞｲﾚｸﾄﾒｰﾙﾓｰﾄﾞ別編 */
	#define	PRO_FUNC_COST				0x0002	/* 料金管理			 */
	#define	PRO_FUNC_F_CODE				0x0004	/* Ｆコード			 */
	#define	PRO_FUNC_CIPHER				0x0008	/* アリロー			 */
	#define	PRO_FUNC_ERROR_MONITOR		0x0010	/* 通信エラーモニタ	 */
	#define	PRO_FUNC_MAIL_COMP_CHK		0x0020	/* 親展競合ｺﾝﾊﾟﾁ編	 */ /*1997/10/20 SYS_MAILBOX_RCV_TO_RECEVING*/
	#define	PRO_FUNC_DATE_SET_RXDOC_CHK	0x0040	/* 受信原稿日時付加  */ /*1998/06/15 Y.Murata */
	#define PRO_FUNC_TX_CLOSED_NET		0x8000	/* 国税庁仕様（送信版閉域通信） By O.Kimoto 2002/06/07 */

	/* 予備 */
/* 2 */
	/* 予備 */
/* 3 */
	/* 予備 */
/* 4 */
	/* 予備 */


/*----------------------------------*/
/* オプションモデムボード用国コード */
/*----------------------------------*/
	#define JPN_CODE	0x00
	#define USA_CODE	0x01
	#define GBR_CODE	0x02
	#define DEU_CODE	0x03
	#define FRA_CODE	0x04
	#define AUS_CODE	0x05
	#define SGP_CODE	0x06
	#define TWN_CODE	0x07
	#define THA_CODE	0x08
	#define DNK_CODE	0x09
	#define AUT_CODE	0x0A
	#define CHE_CODE	0x0B	/* add by M.H 98/04/10 */
	#define BEL_CODE	0x0C	/* add by M.H 98/04/10 */
	#define NLD_CODE	0x0D	/* add by M.H 98/04/10 */
	#define ITA_CODE	0x0E	/* add by M.H 98/04/10 */
	#define POL_CODE	0x0F	/* add by M.H 98/04/10 */
	#define GRC_CODE	0x10	/* add by M.H 98/04/10 */
	#define ZAF_CODE	0x11	/* add by M.H 98/04/10 */
	#define NOR_CODE	0x12	/* add by M.H 98/04/10 */
	#define SWE_CODE	0x13	/* add by M.H 98/04/10 */
	#define FIN_CODE	0x14	/* add by M.H 98/04/10 */
	#define ESP_CODE	0x15	/* add by M.H 98/04/10 */
	#define PRT_CODE	0x16	/* add by M.H 98/04/10 */
	#define TUR_CODE	0x17	/* add by M.H 98/04/10 */
	#define CSK_CODE	0x18	/* add by M.H 98/04/10 */
	#define TBR_CODE	0x19	/* For ICHOU Add By M.Tachibana 1998/09/21 */
	#define DEU_CTR_CODE	0x1A	/* DEU(CTR)仕様 For kaki Add By harada 1999/08/28 */
	#define EUR_CTR_33_CODE	0x1B	/* EUR(CTR):DP=33仕様 For kaki Add By harada 1999/09/13 */
	#define EUR_CTR_40_CODE	0x1C	/* EUR(CTR):DP=40仕様 For kaki Add By harada 1999/09/13 */



#endif	/* End of File */
