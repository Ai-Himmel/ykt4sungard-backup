/*	イベント定義ファイル
 *	EVENT_MAX は
 *	\src\atlanta\sh7043\define\def_mon.h に有ります。
 *	２５６個確保して有ります。T.Nose 1997/08/25
 */

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"
#else

/* システムDMA関連イベント */
#define	EVT_DMA_MDM_MDMBUF				0	/* モデム ←→ モデムバッファ ＤＭＡ終了 */
#define	EVT_DMA_MPC_MPCBUF				1	/* ＭＰＣ ←→ バッファ	      ＤＭＡ終了 */
#define	EVT_DMA_SCNCDC_DRAM				2	/* スキャナコーデック → ＤＲＡＭ ＤＭＡ終了 */
#define	EVT_DMA_DRAM_PRNCDC				3	/* ＤＲＡＭ → プリンタコーデック ＤＭＡ終了 */
#define	EVT_DMA_COMCDC_DRAM				4	/* 通信コーデック → ＤＲＡＭ ＤＭＡ終了 */
#define	EVT_DMA_DRAM_COMCDC				5	/* ＤＲＡＭ → 通信コーデック ＤＭＡ終了 */

/* コーデック関連イベント */
#define	EVT_CDC0_COMMAND_END			6	/*コマンド終了		For KIRI スキャナ CODEC*/
#define	EVT_CDC0_DMA0_END				7	/*DMAチャンネル0終了 For KIRI スキャナ CODEC*/
#define	EVT_CDC0_DMA1_END				8	/*DMAチャンネル0終了 For KIRI スキャナ CODEC*/
#define	EVT_CDC1_COMMAND_END			9	/*コマンド終了		For KIRI プリンタ CODEC*/
#define	EVT_CDC1_DMA0_END				10	/*DMAチャンネル0終了 For KIRI プリンタ CODEC*/
#define	EVT_CDC1_DMA1_END				11	/*DMAチャンネル0終了 For KIRI プリンタ CODEC*/
#define	EVT_CDC2_COMMAND_END			12	/*コマンド終了		For KIRI 通信 CODEC*/
#define	EVT_CDC2_DMA0_END				13	/*DMAチャンネル0終了 For KIRI 通信 CODEC*/
#define	EVT_CDC2_DMA1_END				14	/*DMAチャンネル0終了 For KIRI 通信 CODEC*/
#define	EVT_TX_START					15	/*1ページ符号化終了 For KIRI スキャナ CODEC*/

/* FIPイベント */
#define	EVT_FIPWAKEUP					16
#define	EVT_RSISR						17

/* NCUイベント */
#define	EVT_CI_CHECK					18	/*CI・F網着信検出*/

/* ATDイベント */
#define	EVT_TONE_FILTER1_ON				19
#define	EVT_TONE_FILTER2_ON				20
#define	EVT_TONE_FILTER3_ON				21
#define	EVT_TONE_FILTER1_OFF			22
#define	EVT_TONE_FILTER2_OFF			23
#define	EVT_TONE_FILTER3_OFF			24

/* SCNイベント */
#define	EVT_SCN_SCAN_START				25	/** Mar.29,1994 By S.K */
#define	EVT_SCN_FEED_ERROR				26	/** Mar.29,1994 By S.K */
#define	EVT_SCN_SCAN_END				27	/** Mar.29,1994 By S.K */
#define EVT_SCN_DOCUMENT_SET_OK			28
#define	EVT_SCN_NO_DOC					29
#define	EVT_SCN_COVER_OPEN				30
#define	EVT_SCN_DOC_OUT_OK				31
#define	EVT_SCN_GEAR_BACK_LASH_END		32
#define	EVT_MIRROR_MOVE_END				33		/* FBS追加  T.Nose 1996/12/09 */
#define	EVT_TX_MOTOR_BACKLASH_END		34		/* FBS追加  T.Nose 1996/12/09 */
#define	EVT_FCOT_PRINT_START			35		/* FCOT追加 T.Nose 1996/12/09 */

#if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
	#define	EVT_PRN_XTOP					36		/*プリンタからのVREQ検出.両エッジの検知なので状態変化によって割り込みが発生する MD9803*/
	#define	EVT_PRN_BDEND					37		/*白マスクの開始(WMイネーブル) MD9803*/
	#define	EVT_PRN_BDCEND					38		/*白マスクの終了 MD9803*/
	#define	EVT_PRN_SCD						39		/*コマンド送出中 MD9803*/
	#define	EVT_PRN_SST						40		/*ステータス受信中 MD9803*/
	#define	EVT_PRN_ENDCD					41		/*コマンド送出終了 MD9803*/
	#define	EVT_PRN_ENDST					42		/*ステータス受信終了 MD9803*/
	#define	EVT_PRN_PGEND					43		/*ページエンド検知 MD9803*/
	#define	EVT_PRN_PSSP					44		/*PSS起動検知.論理によってどちらかを選択する(LED Only) MD9803*/
	#define	EVT_PRN_PSSN					45		/*PSS終了検知.論理によってどちらかを選択する(LED Only) MD9803*/
	#define	EVT_PRN_FSCLR					46		/*8K×12FIFOのクリア終了 MD9803*/
	#define	EVT_PRN_DPCLR					47		/*DPRAMクリア終了 MD9803*/
	#define	EVT_PRN_FLCLR					48		/*8K×1,16K×1FIFOのクリア終了 MD9803*/
	#define	EVT_PRN_RP1						49		/*RPO1の状態変化あり.両エッジ検知なので状態変化によって割り込みが発生する MD9803*//* KAKIは使用しません */
	#define	EVT_PRN_RP2						50		/*RPO2の状態変化あり.両エッジ検知なので状態変化によって割り込みが発生する MD9803*//* KAKIは使用しません */
	#define	EVT_PRN_RP3						51		/*RPO3の状態変化あり.両エッジ検知なので状態変化によって割り込みが発生する MD9803*//* KAKIは使用しません */
	#define	EVT_PRN_COUNT_UP				52		/*カウントアップのイベント */
#else
	/* PRNイベント */
	#define	EVT_PAPER_JAM					36	/* PAPER JAM 発生時のイベント	*/
	#define	EVT_PRN_XTOP					37	/* 垂直同期信号			*/
	#define	EVT_PRN_XBD						38	/* 水平同期信号			*/
	#define	EVT_PRN_XSBSY					39	/* ステータス・ビジー	*/
	#define	EVT_PRN_PGEND					40	/* ページ終了			*/
	#define	EVT_PRN_XPPRDY_ON				41	/* プリンタ・パワー・レディ信号	*/
	#define	EVT_PRN_XPPRDY_OFF				42	/* プリンタ・パワー・レディ信号	*/
	#define	EVT_PRN_XRDY_ON					43	/* レディ信号			*/
	#define	EVT_PRN_XRDY_OFF				44	/* レディ信号			*/
	#define	EVT_PRN_BDEND					45	/* BDCounterの割込み	*/
	#define	EVT_PRN_RESTART					46
	#define	EVT_PRN_PSS_ON					47	/* LED 給紙センサ	*/
	#define	EVT_PRN_PSS_OFF					48	/* LED 給紙センサ	*/
	#define	EVT_PRN_PDS_ON					49	/* LED 排紙センサ	*/
	#define	EVT_PRN_PDS_OFF					50	/* LED 排紙センサ	*/
	#define	EVT_PRN_PRINTER_ERROR			51	/* LED プリンタエラー	*/
	#define	EVT_PRN_PAPER_SENSOR			52	/* LED ペーパーセンサ	*/
#endif




/* モデムイベント */
#define	EVT_DECODE_BLOCK_END			53	/*	１ブロックデコード終了	*/
#define	EVT_RXFSK_DMA_STOP				54	/*	ＦＳＫ受信	*/
#define	EVT_G3_TX_COMPLETE				55	/*	画データ送出終了	*/
#define	EVT_TXFRAME_END					56	/*	ＦＣＳ送出完了 */
#define	EVT_RX_FLG_DETECT				57	/*	受信フラグ検出	*/
#define	EVT_MODEM_STATUS				58	/*	該当モデムステータス検出	*/
#define	EVT_DTMF_DETECT					59	/*	DTMF検出	*/
#define	EVT_MODEM_INT					60
#define	EVT_TX_FCS_COMPLETE				61
#define	EVT_TX_COMPLETE					62

/* OPRキースキャンイベント */
#define	EVT_KEY_DECIDE					63	/*	入力キーの確定	*/

/* CLASS1イベント */
#define	EVT_CL1MAN						64
#define	EVT_RSCONTROL					65
#define	EVT_CL1WAKEUP					66
#define	EVT_CL1RX_DATA					67
#define	EVT_ABORT_CHAR					68
#define	EVT_CL1TX_START					69
#define	EVT_CL1_BUF_SET					70
#define	EVT_CL1_BUF_FREE				71

/* DPRイベント */
#define	EVT_DPR_UPLOAD_INTERRUPT		72

/* ROTイベント */
#define	EVT_ROT_ROTATE_END				73

/* 工場ファンクション 原稿排出テスト */
#define EVT_DOC_PAGE_COUNT				74 /* 排出原稿ページ数のカウント */

/* Ported from clover\define\def\evtn.h for R288F by H.Kubo 1997/06/30 */
#define R288F_BASE					74	/** R288F Only **/
#define EVT_MDM_SYNCD				(R288F_BASE +  1)
#define EVT_MDM_FLAGS				(R288F_BASE +  2)
#define EVT_MDM_OE					(R288F_BASE +  3)
#define EVT_MDM_FE					(R288F_BASE +  4)
#define EVT_MDM_PE					(R288F_BASE +  5)
#define EVT_MDM_PNSUC				(R288F_BASE +  6)
#define EVT_MDM_EQMAT				(R288F_BASE +  7)
#define EVT_MDM_DISDET				(R288F_BASE +  8)
#define EVT_MDM_ATV25				(R288F_BASE +  9)
#define EVT_MDM_RREDT				(R288F_BASE + 10)
#define EVT_MDM_BRKD				(R288F_BASE + 11)
#define EVT_MDM_RTDET				(R288F_BASE + 12)
#define EVT_MDM_CTS					(R288F_BASE + 13)
#define EVT_MDM_FED					(R288F_BASE + 14)
#define EVT_MDM_RLSD				(R288F_BASE + 15)
#define EVT_MDM_ABCODE				(R288F_BASE + 16)
#define EVT_MDM_DTMFD				(R288F_BASE + 17)
#define EVT_MDM_TURNON				(R288F_BASE + 18)	/**  By O.K Feb.03,1996 **/
#define EVT_MDM_TURNOFF				(R288F_BASE + 19)	/**  By O.K Feb.03,1996 **/
#define EVT_MDM_CC_RETRAIN			(R288F_BASE + 20)	/*  By O.Kimoto 1996/05/16 */

/* SCNイベント */
#define EVT_SCN_TOP_COVER_OPEN		95	/* プリンタカバー開 T.Nose 1997/08/25 */
/* 音声応答用ＤＭＡ転送終了 */
#define EVT_DMA_MDM_VOICE_ROM		96	/* 1998/01/29  By T.Yamaguchi */

/* for R288F */
#define EVT_DMA_MEMORY_TO_MEMORY	97 /* added by H.Kubo 1998/01/29 */
#define EVT_MDM_MODEM_RECOVER		98	/* Add By O.Kimoto 1998/02/03 */

/* For ANZU_L Internet FAX  1998/4/3 Eguchi */
#define	EVT_INF_RSCONTROL	99
#define	EVT_INF_WAKEUP		100 /*Add by Eguchi 1998/04/21 */

/* IDP関係 (SAKAKI)*/
#define EVT_DICEP_DMA_END				101
#define EVT_COMMAND_OR_DMA_BLOCK_END	102
#define EVT_SCAN_ONE_BLOCK_END			103
#define EVT_ENCODE_ONE_BLOCK_END		104
#define EVT_DICEP_COMMAND_END			105
#define EVT_PRINT_HEAT_1LINE_END	110
/* For R288F V23 Rx by H.Kubo 1998/08/04 */
#define EVT_MDM_RX_NEW_DATA			111

#if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
	#define	EVT_PRN_PSS_ON					112	/* LED 給紙センサ	*/
	#define	EVT_PRN_PSS_OFF					113	/* LED 給紙センサ	*/
	#define	EVT_PRN_PDS_ON					114	/* LED 排紙センサ	*/
	#define	EVT_PRN_PDS_OFF					115	/* LED 排紙センサ	*/
	#define	EVT_PRN_PRINTER_ERROR			116	/* LED プリンタエラー	*/
	#define	EVT_PRN_PAPER_SENSOR			117	/* LED ペーパーセンサ	*/
	#define	EVT_PRN_RESTART					118
#endif
#define EVT_NAR		119		/* For NTT AnswerLSI(MSM9805) */
#endif
