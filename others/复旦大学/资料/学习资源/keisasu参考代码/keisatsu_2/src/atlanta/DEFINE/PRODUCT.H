#ifndef product_h
	#define product_h

/************************************************************************
 * プロジェクトパラメータ												*
 * "\src\atlanta\define\product.h"										*
 *																		*
 * 概要　　：共通ソースファイル内でプロジェクト固有の仕様を識別するため *
 *			 に使用する													*
 * 使用方法：ソースファイルの先頭にインクルードする						*
 *			 条件コンパイルの式として使用する							*
 *			 例) #if (PRO_FIP == ENABLE)								*
 *				 #endif													*
 * 定義方法：定義内容は仕様別とする										*
 *			 プロジェクト仕様が変更となった場合でも、本定義をかえるだけ *
 *			 の対応で済むようにする										*
 *			 例) KIRIで有効な｢一括送信｣をSATSUKIで有効にする場合、		*
 *				   #define PRO_BATCH_TX		ENABLE						*
 *				 とするだけで仕様変更できることになる。					*
 * 補足	   ：プロジェクト内の仕向先固有の仕様を識別する場合は、			*
 *			 国別パラメータ(CountryTable[])を使用する					*
 *																		*
 *																		*
 *		★★★	PRODUCT.HDRのほうもメンテナンスして下さい。★★★		*
 *																		*
 *																		*
 ************************************************************************/

/************************************************************************
 * 有効/無効															*
 ************************************************************************/
#define		DISABLE		0				/* 無効 */
#define		ENABLE		2				/* 有効 */
/************************************************************************
 * メーカ名				PRO_MAKER										*
 ************************************************************************/
#define		MML			0				/* 村田仕様 */
#define		FX			1				/* FX仕様 */
/************************************************************************
 * 操作パネル			PRO_PANEL										*
 ************************************************************************/
#define		ANK			0				/* ANK */
#define		KANJI		1				/* 漢字対応 */
/************************************************************************
 * CPU					PRO_CPU											*
 ************************************************************************/
#define		SH7043		0				/* HITACHI SH2 */
/************************************************************************
 * プリント方式			PRO_PRINT_TYPE				*
 ************************************************************************/
#define		THERMAL		0		/** 感熱記録方式 **/
#define		THERMAL_TRANS	1		/** 熱転写記録方式 **/
#define		LASER		2		/** レーザープリント記録方式 **/
#define		LED		3		/** ＬＥＤプリント記録方式 **/
/************************************************************************
 * プリントスピード		PRO_PRT_SPEED									*
 ************************************************************************/
#define		PRT_SPEED_5MS	0			/* プリントスピード5mS */
#define		PRT_SPEED_10MS	1			/* プリントスピード10mS */
/************************************************************************
 * 記録紙タイプ			PRO_PAPER_TYPE									*
 ************************************************************************/
#define		ROLL_PAPER	0
#define		CUT_PAPER	1
/************************************************************************
 * 通信管理記録			PRO_JOURNAL										*
 ************************************************************************/
#define		SEPARATE	0				/* 送受信分離型 */
#define		UNITED		1				/* 送受信一体型 */
/************************************************************************
 * モデム				PRO_MODEM										*
 ************************************************************************/
#define		ORANGE3		0				/* 村田製オレンジ3 */
#define		R288F		1				/* ROCKWELL製 28.8K */
#define		MN195006	2				/* 松下モデム */
/************************************************************************
 * コーデック			PRO_SCN_CODEC_TYPE
						PRO_PRN_CODEC_TYPE
						PRO_COM_CODEC_TYPE
 ************************************************************************/
#define		SOFTWARE	0				/* ソフトコーデック */
#define		MN86063		1				/* 松下製CODEC				MN86063	 */
#define		MN86064		2				/* 松下製CODEC				MN86064	 */
#define		IDP301		3				/* 日立製CODEC(DICEP)		IDP301	 */

/************************************************************************
 * コーデックの個数		PRO_CODEC_NUMBER								*
 ************************************************************************/
#define		CDC_SINGLE			1
#define		CDC_DOUBLE			2
#define		CDC_TRIPLE			3
/************************************************************************
 * 交信ボーレート		PRO_TX_SPEED									*
 ************************************************************************/
#define		V29			0				/* V27､V29 */
#define		V33			1				/* V17､V33 */
#define		V34			2				/* V8､V34 */ /* V17, V27, V29, V17ter, (V33) 能力もあるものとして使っている H.Kubo 1997/11/05 */
/************************************************************************
 * 最大読み取り幅		PRO_SCAN_WIDTH									*
 * 最大記録紙幅			PRO_PRINT_WIDTH									*
 ************************************************************************/
#define		A3WIDTH		0				/* Ａ３ */
#define		B4WIDTH		1				/* Ｂ４ */
#define		A4WIDTH		2				/* Ａ４ */
/************************************************************************
 * 中間調				PRO_HALFTONE									*
 ************************************************************************/
#define		HARMONY32	0				/*	 ３２階調 */
#define		HARMONY64	1				/*	 ６４階調 */
#define		HARMONY128	2				/* １２８階調 */
/************************************************************************
 * ＮＣＵ／カプラ	(Relay 動作による分類)								*
 *						PRO_NCU_TYPE									*
 ************************************************************************/
#define		ANZU_USA_TYPE		1	/* ANZU		USA		TYPE			*/
#define		ANZU_GBR_TYPE		2	/* ANZU		GBR		TYPE			*/
#define		POPLAR_TYPE			3
#define		SAKAKI_TYPE			4 	/* added by H.Kubo 1998/07/03 */
#define		HINOKI_TYPE			5 	/* Add By O.Kimoto 1998/08/28 */
/************************************************************************
 * キーパネルテーブル	PRO_KEYPANEL									*
 ************************************************************************/
#define		PANEL_POPLAR_B	1	/* ポプラ＿Ｂタイプ */
#define		PANEL_POPLAR_H	2	/* ポプラ＿Ｈタイプ */
#define		PANEL_POPLAR_L	3	/* ポプラ＿Ｌタイプ */
#define		PANEL_ANZU_L	4	/* あんず＿Ｌタイプ */
#define		PANEL_SAKAKI	5	/* さかき    タイプ */
#define		PANEL_HINOKI	6	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
#define		PANEL_SATSUKI2	7	/* SATSUKI2 タイプ *//* SMuratec H.C.H 2003.07.11 */
#define		PANEL_STOCKHM2	8	/* STOCKHM2 タイプ *//* SMuratec C.P 2004/05/28 */
/************************************************************************
 * 解像度				PRO_CCD, PRO_PRINTER							*
 ************************************************************************/
#define		DPI100		1	/* １００ ｄｐｉ */
#define		DPI200		2	/* ２００ ｄｐｉ */
#define		DPI300		3	/* ３００ ｄｐｉ */
#define		DPI400		4	/* ４００ ｄｐｉ */
#define		DPI500		5	/* ５００ ｄｐｉ */
#define		DPI600		6	/* ６００ ｄｐｉ */
#define		DPI700		7	/* ７００ ｄｐｉ */
#define		DPI800		8	/* ８００ ｄｐｉ */

/************************************************************************
 * トナー欠発生時のプリント												*
 ************************************************************************/
/* Low Toner発生時、100枚のみプリントし、以降はTonerが交換されるまでプリントしない仕様を区別するため
** By O.Kimoto 1996/12/26
*/
#define		PRINT_FREE				0	/** 従来仕様のままとします */
#define		PRINT_LIMIT				1	/** Low Toner発生後100枚のみプリントできます */

/************************************************************************
 * 内蔵回線数の定義 By O.Kimoto 1997/11/01
 * ＰＯＰＬＡＲ_Ｈでは標準で２回線収容となる。
 ************************************************************************/
#define		SINGLE_LINE		0	/* ＰＯＰＬＡＲ＿Ｈ以外 */
#define		TWICE_LINE		1	/* ＰＯＰＬＡＲ_Ｈ */

/************************************************************************
 * 標準ＤＲＡＭサイズ(PRO_DRAM_SIZE) By Y.Suzuki 1998/05/15
 ************************************************************************/
#define		DRAM_1M		0	/* ＰＯＰＬＡＲ＿Ｌ */
#define		DRAM_2M		1	/* ＰＯＰＬＡＲ_Ｌ以外 */

/************************************************************************
 * SH2 内蔵 DMA の使用方法 (PRO_SH2_INTERNAL_DMAC) By H.Kubo 1998/07/22
 ************************************************************************/
#define		MODEM_DMA				1
#define		SCN_PRN_CODEC_DMA		2
#define		COM_CODEC_DMA			3

/************************************************************************
 * ナンバーディスプレイ（Caller-ID）の通信方法 (PRO_CALLER_ID_PROTOCOL)  By H.Kubo 1998/08/12
 ************************************************************************/
#define		CALLER_ID_DISABLE		0
#define		CALLER_ID_V23			1
#define		CALLER_ID_DFTMF			2

/************************************************************************
 * 割り込み要因DTC(PRO_DTC_INT_SYSTEMをEnableにする）を汎用的に使用できるようにした時の割り込み要因割り当て
 * PRO_DTC_INT_TYPE
 * 1998/08/31 H.Yoshikawa
 ************************************************************************/
#define		DTC_INT_OTHER			0
#define 	DTC_INT_SAKAKI			1
#define		DTC_INT_HINOKI			2 /* HINOKI TYPE By H.Hirao 1998/09/21 */

/************************************************************************
 * 外部追加割り込み要因を識別する
 * PRO_EXT_INT_TYPE
 * 1998/08/31 H.Yoshikawa
 ************************************************************************/
#define		EXT_INT_OTHER			0
#define 	EXT_INT_SAKAKI			1
#define 	EXT_INT_NONE			2

/************************************************************************
 * ＣＰＵバージョン
 * PRO_CPU_VERSION
 * 1998/09/04 O.Kimoto
 ************************************************************************/
#define		SH7043_R			0
#define 	SH7043_A			1
/************************************************************************
 * モデムバージョン														*
 * PRO_MODEM_R288F_VERSION
 * バージョンが新しいほうが値が大きくなるように定義してください。
 * by H.Kubo 1998/09/07
 ************************************************************************/
#define		R288F_VERSION_INVALID		0				/* 村田製オレンジ3 */
#define		R288F_VERSION_20P			1				/* ROCKWELL製 28.8K */
#define		R288F_VERSION_22P			2				/* ROCKWELL製 28.8K */
#define		R288F_VERSION_24P			3				/* ROCKWELL製 28.8K */
#define		R288F_VERSION_26P			4				/* ROCKWELL製 28.8K */
#define		FM336_VERSION_12P			5				/* CONEXANT(旧Rockwell)製 33.6K *//* 1999/09/27 Y.Murata */

/************************************************************************
 * 第２水準漢字対応														*
 * PRO_KANJI2_TYPE														*
 * 1998/09/17 H.Yoshikawa												*
 ************************************************************************/
#define		KANJI2_26					0				/* POPLAR/ANZU_L */
#define		KANJI2_27					1				/* SAKAKI/HINOKI */
#define		KANJI2_28					2				/* */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#define		KANJI2_29					3			*/	/* SAKAKI2/POPLAR_H2 */
#define		KANJI2_29					3				/* SAKAKI2 */
#define		KANJI2_30					4				/* POPLAR_H2 */

/************************************************************************
 * 待機状態で、『停止』キーを押されたときに、							*
 * モード・濃度等の１次的に設定設定できる値が変更されている場合には、	*
 * オペレーション設定で設定された初期値に戻す。							*
 * PRO_STOP_MODE_CLEAR													*
 * 1998/09/17 H.Yoshikawa												*
 ************************************************************************/

/************************************************************************
 * Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定				*
 * PRO_MODEM_AREA_BUS_WIDTH												*
 * 1998/09/19 H.Hirao													*
 ************************************************************************/
#define		BUS_WIDTH_16BIT				0			/* POPLAR/ANZU_L/SAKAKI */
#define		BUS_WIDTH_8BIT				1			/* HINOKI */

/************************************************************************
 * 画処理ＬＳＩ															*
 * PRO_IMAGE_PROCESSOR													*
 * 1998/09/28 T.Soneoka													*
 ************************************************************************/
#define		IMAGE_PROCESSOR_OTHER			0
#define		IMAGE_PROCESSOR_LC82103			1			/* HINOKI */

/************************************************************************
 * 最少走査線時間														*
 * PRO_TX_MINIMUM_SCAN_LINE_TIME										*
 * PRO_RX_MINIMUM_SCAN_LINE_TIME										*
 * 1998/12/05 H.Hirao													*
 ************************************************************************/
#define		TIME0		7
#define		TIME5		4
#define		TIME10		2
#define		TIME10_2	3
#define		TIME40_2	5

/************************************************************************
 * TTI の形式 OKI 仕様対応のため。										*
 * PRO_TTI_TYPE															*
 * 1999/02175 H.Kubo													*
 ************************************************************************/
#define		TTI_MML_TYPE	0
#define		TTI_OKI_TYPE	1

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｂ												*
 ************************************************************************/
#if defined(POPLAR_B)

 #if defined(USAPIT)	/* Pitney Bowes HﾊﾟﾀｰﾝﾃｽﾄROM用 */
	#define USA
 #endif

 #if defined(USATST)
	#define USA
 #endif

 #if defined(JP1)
	#define JPN
 #endif
 #if defined(US1)	/* Pitney Bowes 仕様 By S.Fukui Aug.25,1998 */
	#define USA
 #endif
 #if defined(GBR_OKI)
	#define GBR
 #endif
/* #if defined(BEL) || defined(DNK) || defined(ESP) || defined(FIN) || defined(ITA) || defined(NLD) || defined(NOR) || defined(SWE) by K.Watanabe 1998/10/22 */
 #if defined(BEL) || defined(ESP) || defined(ITA) || defined(NLD) || defined(NOR) || defined(SWE)
	#define EC1
 #endif

 #if defined(AUS_OKI)/* 沖仕様追加 By Y.Suzuki 1999/02/18 */
	#define AUS
 #endif
 #if defined(EU1) || defined(EU2) || defined(EU3) || defined(EU4)
	#define EUR
 #endif

	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			ORANGE3				/* 村田製オレンジ３モデム */
	#define	PRO_PRINT_TYPE		LED					/* ＬＥＤプリント記録方式 */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_B		/* ポプラ＿Ｂタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_PRINTER			DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルイン */
 #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_DOUBLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86063				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86063				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	SOFTWARE			/* ソフトコーデック */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話	???*/
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 ??? */
 #if defined(JPN)
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
 #elif defined(USA)
	#define	PRO_NCU_TYPE		ANZU_USA_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
 #else
	#define	PRO_NCU_TYPE		ANZU_GBR_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
 #endif
	#define	PRO_TX_SPEED		V33					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			ENABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		A3WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅	*/
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信					*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
 #if defined(USA) || defined(AUS)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
 #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
 #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi ???*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
#if (0)	/* 現状、PIN機能は全ての国にあるので、無条件にENABLEにします（条件ｺﾝﾊﾟｲﾙの追加のし忘れが恐いので） by K.Watanabe 1998/09/18 */
///* #if defined(USA) || defined(JPN) || defined(GBR) || defined(DEU) || defined(FRA) */ /* POPLAR_B AUS bythonda1998/06/18 */
// #if defined(USA) || defined(JPN) || defined(GBR) || defined(DEU) || defined(FRA) || defined(AUS)
//	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
// #else
//	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
// #endif
#endif
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク（海外仕様のみ） 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		ENABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
/* #if defined(JPN) || defined(DEU) || defined(FRA) S.Fukui */
/* #if defined(DEU) || defined(FRA)By Y.Suzuki 1998/08/05 */
/*	#define	PRO_CLASS1			DISABLE				 クラス１　1996/01/22 Eguchi */
/* #else */
 #if defined(USAPIT) || defined(USATST)
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi */
 #else
	#define	PRO_CLASS1			ENABLE				/* クラス１　1996/01/22 Eguchi */
 #endif
/* #endif*/
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 2000/1/11 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/07/02 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
/* #if defined(JPN) || defined(USA) || defined(AUS) */
/* #if defined(JPN) || defined(AUS)*/	/* （ＵＳＡ）一時的にはずします bythonda1998/11/5 */
 #if defined(JPN)	/* （ＡＵＳ）ＲＯＭ容量超える為はずします bythonda1998/11/5 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
 #else
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
 #endif
	#define	PRO_EXT_DMAC		ENABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	ENABLE				/* コピー／ＦＡＸ切り替え */
 #if defined(JPN)										/* Modified by S.Fukui Sep.18,1997  */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
 #else
	#define	PRO_JIS_CODE		DISABLE				/* 漢字ＣＧＲＯＭ対応 */
 #endif
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				ENABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	ENABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 1997/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */

 #if (1)  /* 「白紙受信」対策がＲＯＭ容量を食う為、日本仕様以外はアリロ－削除 （輸出、ＣＳ確認済） S.Fukui Jan.17,2000 */
  #if defined(JPN)
	#define	PRO_CIPHER			ENABLE				/* アリロー  */
  #else
 	#define	PRO_CIPHER			DISABLE				/* アリロー  */
  #endif
 #else
//  #if defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)
// 	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
//  #else
//	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 */
//  #endif
 #endif
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

 #if defined(JPN)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #else
	#define PRO_DEPART_NEW_LIST	ENABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #endif
	#define PRO_JBIG			DISABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	ENABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			DISABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
 #if defined(JPN)
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
 #else
	#define PRO_ADF_AUTO_CASSETTE	ENABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
 #endif
	#define PRO_EXT_ROM			ENABLE				/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */

/*By Y.Suzuki 1998/08/05*/
/* #if defined(DEU) || defined(FRA)					@* 条件追加：S.Fukui Jun.19,1998 */
/*	#define	PRO_CLASS1_ECM		DISABLE				@* クラス１ECM 通信 by H.Kubo1998/03/06 */
/* #else*/
	#define	PRO_CLASS1_ECM		ENABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
/* #endif*/
	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
 #if defined(USAPIT)
	#define	PRO_MINOLTA_TEST_FUNC		ENABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)&Pitney Bowesﾃｽﾄﾓｰﾄﾞ 1998/10/06 M.Tachibana */
 #else
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)&Pitney Bowesﾃｽﾄﾓｰﾄﾞ 1998/10/06 M.Tachibana */
 #endif
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
 #if defined(USA)	/* By M.Tachibana 1998/05/21 */
	#define PRO_REVERSE_PRINT	ENABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
 #else
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
 #endif
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
 #if defined(JP1)
	#define PRO_SPEED_DIAL_ADDITION	ENABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
 #else
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
 #endif
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	ENABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata *//* DISABLE->ENABLE 1998/07/09 Y.Matsukuma */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
 #if defined(JPN)
	#define PRO_EX_CLASS1		ENABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	ENABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 #else
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 #endif
 #if defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)|| defined(AUS_OKI)
	#define PRO_OKI				ENABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
 #else
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
 #endif
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	MODEM_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
 #if defined(US1)
	#define PRO_PITNEYBOWES		ENABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
 #else
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
 #endif
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
 #if defined(USATST)
	#define PRO_QUICK_TX_TEST		ENABLE 			/* クイック送信テスト 1998/10/09 Y.Murata */
 #else
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
 #endif
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
 #if defined(USA)
	#define PRO_ALLRAMCLR_WO_MCP	ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
 #else
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
 #endif
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
 #if defined(JPN) || defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
 #else
	#define PRO_PREHEAT				DISABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
 #endif

 #if (1)	/* 相手機がＰＣ－ＦＡＸ等で起こる「白紙受信」対策 は イマドコサービス対策をベースに作られている！ S.Fukui Jan.17,2000 */
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 */
 #else
  #if defined(JPN) || defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
  #else
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
  #endif
 #endif
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
 #if defined(USA)
	#define	PRO_DIAL_LIST_GROUP		ENABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
 #else
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
 #endif
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa *//* By M.Tachibana 2002/11/18 */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/****************************************************************************
 * ＰＯＰＬＡＲ タイプ ＢＮ （Ｌ５００ ＮＴＴ仕様） 1999/05/13 by T.Soneoka	*
 ***************************************************************************/
#if defined(POPLR_BN)

 #if defined(USAPIT)	/* Pitney Bowes HﾊﾟﾀｰﾝﾃｽﾄROM用 */
	#define USA
 #endif

 #if defined(USATST)
	#define USA
 #endif

 #if defined(JP1)
	#define JPN
 #endif
 #if defined(US1)	/* Pitney Bowes 仕様 By S.Fukui Aug.25,1998 */
	#define USA
 #endif
 #if defined(GBR_OKI)
	#define GBR
 #endif
/* #if defined(BEL) || defined(DNK) || defined(ESP) || defined(FIN) || defined(ITA) || defined(NLD) || defined(NOR) || defined(SWE) by K.Watanabe 1998/10/22 */
 #if defined(BEL) || defined(ESP) || defined(ITA) || defined(NLD) || defined(NOR) || defined(SWE)
	#define EC1
 #endif

 #if defined(AUS_OKI)/* 沖仕様追加 By Y.Suzuki 1999/02/18 */
	#define AUS
 #endif

	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			ORANGE3				/* 村田製オレンジ３モデム */
	#define	PRO_PRINT_TYPE		LED					/* ＬＥＤプリント記録方式 */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_B		/* ポプラ＿Ｂタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_PRINTER			DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルイン */
 #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_DOUBLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86063				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86063				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	SOFTWARE			/* ソフトコーデック */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話	???*/
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 ??? */
 #if defined(JPN)
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
 #elif defined(USA)
	#define	PRO_NCU_TYPE		ANZU_USA_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
 #else
	#define	PRO_NCU_TYPE		ANZU_GBR_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
 #endif
	#define	PRO_TX_SPEED		V33					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			ENABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		A3WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅	*/
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信					*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
 #if defined(USA) || defined(AUS)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
 #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
 #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi ???*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
#if (0)	/* 現状、PIN機能は全ての国にあるので、無条件にENABLEにします（条件ｺﾝﾊﾟｲﾙの追加のし忘れが恐いので） by K.Watanabe 1998/09/18 */
///* #if defined(USA) || defined(JPN) || defined(GBR) || defined(DEU) || defined(FRA) */ /* POPLAR_B AUS bythonda1998/06/18 */
// #if defined(USA) || defined(JPN) || defined(GBR) || defined(DEU) || defined(FRA) || defined(AUS)
//	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
// #else
//	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
// #endif
#endif
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク（海外仕様のみ） 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		ENABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
/* #if defined(JPN) || defined(DEU) || defined(FRA) S.Fukui */
/* #if defined(DEU) || defined(FRA)By Y.Suzuki 1998/08/05 */
/*	#define	PRO_CLASS1			DISABLE				 クラス１　1996/01/22 Eguchi */
/* #else */
 #if defined(USAPIT) || defined(USATST)
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi */
 #else
	#define	PRO_CLASS1			DISABLE				/* クラス１　ENABLE->DISABLE 1999/06/07 by T.Soneoka */
 #endif
/* #endif*/
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/07/02 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
/* #if defined(JPN) || defined(USA) || defined(AUS) */
/* #if defined(JPN) || defined(AUS)*/	/* （ＵＳＡ）一時的にはずします bythonda1998/11/5 */
 #if defined(JPN)	/* （ＡＵＳ）ＲＯＭ容量超える為はずします bythonda1998/11/5 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
 #else
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
 #endif
	#define	PRO_EXT_DMAC		ENABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	ENABLE				/* コピー／ＦＡＸ切り替え */
 #if defined(JPN)										/* Modified by S.Fukui Sep.18,1997  */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
 #else
	#define	PRO_JIS_CODE		DISABLE				/* 漢字ＣＧＲＯＭ対応 */
 #endif
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				ENABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	ENABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 1997/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
/* #if defined(DEU) || defined(FRA)@*By Y.Suzuki 1998/08/05*/
 #if defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)/*By Y.Suzuki 1999/01/21*/
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
 #else
	#define	PRO_CIPHER			DISABLE				/* アリロー ENABLE->DISABLE  1999/06/07 by T.Soneoka */
 #endif
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

 #if defined(JPN)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #else
	#define PRO_DEPART_NEW_LIST	ENABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #endif
	#define PRO_JBIG			DISABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	ENABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		ENABLE			/* 音声応答 1999/06/08  By T.Sato */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			DISABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
 #if defined(JPN)
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
 #else
	#define PRO_ADF_AUTO_CASSETTE	ENABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
 #endif
	#define PRO_EXT_ROM			DISABLE				/* ポプラＢ 拡張ＲＯＭの使用あり ENABLE->DISABLE  1999/06/07 by T.Soneoka */

/*By Y.Suzuki 1998/08/05*/
/* #if defined(DEU) || defined(FRA)					@* 条件追加：S.Fukui Jun.19,1998 */
/*	#define	PRO_CLASS1_ECM		DISABLE				@* クラス１ECM 通信 by H.Kubo1998/03/06 */
/* #else*/
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 ENABLE->DISABLE  1999/06/07 by T.Soneoka */
/* #endif*/
	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
 #if defined(USAPIT)
	#define	PRO_MINOLTA_TEST_FUNC		ENABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)&Pitney Bowesﾃｽﾄﾓｰﾄﾞ 1998/10/06 M.Tachibana */
 #else
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)&Pitney Bowesﾃｽﾄﾓｰﾄﾞ 1998/10/06 M.Tachibana */
 #endif
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
 #if defined(USA)	/* By M.Tachibana 1998/05/21 */
	#define PRO_REVERSE_PRINT	ENABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
 #else
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
 #endif
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
 #if defined(JP1)
	#define PRO_SPEED_DIAL_ADDITION	ENABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
 #else
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
 #endif
	#define	PRO_NOT_AUTO_RX_DISP	ENABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	ENABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata *//* DISABLE->ENABLE 1998/07/09 Y.Matsukuma */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
 #if defined(JPN)
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 ENABLE->DISABLE  1999/06/07 by T.Soneoka */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 ENABLE->DISABLE  1999/06/07 by T.Soneoka */
 #else
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 #endif
 #if defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)|| defined(AUS_OKI)
	#define PRO_OKI				ENABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
 #else
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
 #endif
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	MODEM_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
 #if defined(US1)
	#define PRO_PITNEYBOWES		ENABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
 #else
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
 #endif
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
 #if defined(USATST)
	#define PRO_QUICK_TX_TEST		ENABLE 			/* クイック送信テスト 1998/10/09 Y.Murata */
 #else
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
 #endif
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
 #if defined(USA)
	#define PRO_ALLRAMCLR_WO_MCP	ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
 #else
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
 #endif
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
 #if defined(JPN) || defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
 #else
	#define PRO_PREHEAT				DISABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
 #endif
 #if defined(JPN) || defined(DEU) || defined(FRA) || defined(GBR_OKI) || defined(EC1)
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
 #else
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
 #endif
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	ENABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		ENABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		DISABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｌ												*
 ************************************************************************/
#if defined(POPLAR_L)
	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			ORANGE3				/* 村田製オレンジ３モデム */
	#define	PRO_PRINT_TYPE		LED					/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_L		/* ポプラ＿Ｌタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI200				/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER			DPI200				/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルインあり By N.S. '95,11,25 */
 #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_SINGLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	SOFTWARE			/* ソフトコーデック */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_TX_SPEED		V33					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			DISABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		B4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
 #if defined(USA)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
 #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
 #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ DISABLE → ENABLE 1998/02/10  By T.Yamaguchi */
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		ENABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi */
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_EXT_DMAC		DISABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	ENABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
 #if defined(JPN)
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
 #else
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 */
 #endif
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

 #if defined(USA)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #else
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #endif
	#define PRO_JBIG			DISABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			ENABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM				DISABLE				/* ポプラＢ 拡張ＲＯＭの使用 By Y.Suzuki 1998/03/02 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_1M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	SCN_PRN_CODEC_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
 #if defined(JPN)
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
 #else
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
 #endif
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		DISABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｈ												*
 ************************************************************************/
#if defined(POPLAR_H)

 #if defined(JPNTST) || defined(JP0)
	#define JPN
 #endif

 /* 55転送 By O.Kimoto 2003/02/05 */
 #if defined(JP1)
	#define JPN
	#define JP0
 #endif

 #if defined(JPNTST)	/* テスト用 */

	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			R288F				/* ROCKWELL製 28.8K */
	#define	PRO_PRINT_TYPE		LED					/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_H		/* ポプラ＿Ｈタイプ */
	#define	PRO_PANEL			KANJI				/* 漢字対応操作パネル */
	#define	PRO_CCD				DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_PRINTER			DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
  #if defined(JPN)
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
  #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
  #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		DISABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_TRIPLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_PRN_CODEC_TYPE	MN86063		 		/* 松下CODEC *//* ＰＯＰＬＡＲ＿Ｈはこれは６３です。 By O.Kimoto 1997/10/28 */
	#define	PRO_COM_CODEC_TYPE	MN86064				/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_TX_SPEED		V34					/* V8､V34 28.8K */
	#define	PRO_HQ_MODE			ENABLE				/* 高画質モード									*/
  #if defined(GBR)
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/ /* メモリ節約のため、削ります。 H.Kubo 1998/04/02 */
  #else
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
  #endif
	#define	PRO_SCAN_WIDTH		A3WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			DISABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
  #if defined(USA)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
  #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
  #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
  #if defined(USA) || defined(JPN)
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #elif defined(GBR)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #else
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #endif
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
  #if defined(USA)
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #elif defined(GBR)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */ /* Deleted by H.Kubo 1998/04/01 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #else	/* JPN */
	/* コードサイズを見るために By O.Kimoto 1997/09/11 */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #endif
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_EXT_DMAC		ENABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
  #if defined(GBR)
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
  #else
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	DISABLE			/* 連続ポーリング機能 */
  #endif
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
  #if defined(GBR)
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */ /* メモリ節約のため、削ります。 H.Kubo 1998/04/02 */
  #else
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
  #endif
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			DISABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		TWICE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

  #if defined(USA)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
  #else
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
  #endif
	#define PRO_JBIG			ENABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	ENABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			ENABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM				ENABLE			/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */

	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	DISABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
/* 	#define PRO_RDS_FLASH_ROM_WRITE		DISABLE	1998/06/02 by T.Soneoka */	/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */

  #if defined(USA)
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
  #else
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 *//* マルチＴＴＩ仮名ＩＤ対応 By H.Fujimura 1998/07/07 */
  #endif
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	MODEM_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_20P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 *//* DISABLE By H.Fujimura 1998/10/09 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		ENABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */

 #elif defined(JP0)/* V850ﾏｲﾅﾁｪﾝｼﾞBy Y.Suzuki 2002/05/13 */ || defined(JP1)	/* 55転送 By O.Kimoto 2003/02/05 */
 /* 変更点
 ** 省エネ対応
 ** PC-PRINT CIPHER CLASS1 OPTION 削除
 ** 停電時ﾀﾞｲﾔﾙｲﾝ不要(ﾄｰﾝ検出MODEMでおこなう),保留ﾒﾛﾃﾞｨ変更
 ** ﾌﾟﾘﾝﾀFAN制御(ROME,MELBOURNE方式)
 ** PIN ACCESS 削除(暫定)
 */	
	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			R288F				/* ROCKWELL製 28.8K */
	#define	PRO_PRINT_TYPE		LED					/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_H		/* ポプラ＿Ｈタイプ */
	#define	PRO_PANEL			KANJI				/* 漢字対応操作パネル */
	#define	PRO_CCD				DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_PRINTER			DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			ENABLE				/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
  #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルイン By N.S. '95,11,25 */
  #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
  #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_TRIPLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_PRN_CODEC_TYPE	MN86063		 		/* 松下CODEC *//* ＰＯＰＬＡＲ＿Ｈはこれは６３です。 By O.Kimoto 1997/10/28 */
	#define	PRO_COM_CODEC_TYPE	MN86064				/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_TX_SPEED		V34					/* V8､V34 28.8K */
	#define	PRO_HQ_MODE			ENABLE				/* 高画質モード									*/
  #if defined(GBR)
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/ /* メモリ節約のため、削ります。 H.Kubo 1998/04/02 */
  #else
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
  #endif
	#define	PRO_SCAN_WIDTH		A3WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
  #if defined(USA)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
  #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
  #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
  #if defined(USA) || defined(JPN)
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #elif defined(GBR)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #else
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #endif
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
  #if defined(USA)
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #elif defined(GBR)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */ /* Deleted by H.Kubo 1998/04/01 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #else	/* JPN */
	/* コードサイズを見るために By O.Kimoto 1997/09/11 */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #endif
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_EXT_DMAC		ENABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
  #if defined(GBR)
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
  #else
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
  #endif
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
  #if defined(GBR)
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */ /* メモリ節約のため、削ります。 H.Kubo 1998/04/02 */
  #else
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
  #endif
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		TWICE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

  #if defined(USA)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
  #else
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
  #endif
	#define PRO_JBIG			ENABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	ENABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			ENABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM				ENABLE			/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */

	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	DISABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
/* 	#define PRO_RDS_FLASH_ROM_WRITE		DISABLE	1998/06/02 by T.Soneoka */	/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */

  #if defined(USA)
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
  #else
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 *//* マルチＴＴＩ仮名ＩＤ対応 By H.Fujimura 1998/07/07 */
  #endif
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	MODEM_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		ENABLE				/* V851 NEW JATE 対応 By Y.Suzuki 2002/07/04 ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION FM336_VERSION_12P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*	#define PRO_KANJI2_TYPE		KANJI2_29		*/	/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa *//* <- KANJI2_26 By H.Fujimura 2002/09/27 *//* <- KANJI2_28 By M.Maeda 2002/10/11 */
	#define PRO_KANJI2_TYPE		KANJI2_30			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa *//* <- KANJI2_26 By H.Fujimura 2002/09/27 *//* <- KANJI2_28 By M.Maeda 2002/10/11 */

	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 *//* DISABLE By H.Fujimura 1998/10/09 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			ENABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				ENABLE			/* NEW JIG 2002/06/03 T.Takagi */
 	#define PRO_ENERGY_SAVE_PPF		ENABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	ENABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			DISABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	ENABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	ENABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		DISABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			ENABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			ENABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME ENABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		ENABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */

  #if defined(JP1)
 	#define PRO_REMOTE_DIAL_TRANSFER	ENABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
  #else
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
  #endif
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */

 #else	/*本物のポプラＨ */

	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			R288F				/* ROCKWELL製 28.8K */
	#define	PRO_PRINT_TYPE		LED					/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_H		/* ポプラ＿Ｈタイプ */
	#define	PRO_PANEL			KANJI				/* 漢字対応操作パネル */
	#define	PRO_CCD				DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_PRINTER			DPI400				/* 解像度４００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			ENABLE				/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
  #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルイン By N.S. '95,11,25 */
  #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
  #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_TRIPLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_PRN_CODEC_TYPE	MN86063		 		/* 松下CODEC *//* ＰＯＰＬＡＲ＿Ｈはこれは６３です。 By O.Kimoto 1997/10/28 */
	#define	PRO_COM_CODEC_TYPE	MN86064				/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_TX_SPEED		V34					/* V8､V34 28.8K */
	#define	PRO_HQ_MODE			ENABLE				/* 高画質モード									*/
  #if defined(GBR)
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/ /* メモリ節約のため、削ります。 H.Kubo 1998/04/02 */
  #else
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
  #endif
	#define	PRO_SCAN_WIDTH		A3WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
  #if defined(USA)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
  #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
  #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
  #if defined(USA) || defined(JPN)
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #elif defined(GBR)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #else
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
  #endif
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
  #if defined(USA)
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #elif defined(GBR)	/* for CIPHER Debug by O.Kimoto 1998/03/19 */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */ /* Deleted by H.Kubo 1998/04/01 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #else	/* JPN */
	/* コードサイズを見るために By O.Kimoto 1997/09/11 */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			ENABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER			ENABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
  #endif
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_EXT_DMAC		ENABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
  #if defined(GBR)
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
  #else
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
  #endif
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
  #if defined(GBR)
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */ /* メモリ節約のため、削ります。 H.Kubo 1998/04/02 */
  #else
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
  #endif
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		TWICE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

  #if defined(USA)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
  #else
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
  #endif
	#define PRO_JBIG			ENABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	ENABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			ENABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM				ENABLE			/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */

	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	DISABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
/* 	#define PRO_RDS_FLASH_ROM_WRITE		DISABLE	1998/06/02 by T.Soneoka */	/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */

  #if defined(USA)
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
  #else
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 *//* マルチＴＴＩ仮名ＩＤ対応 By H.Fujimura 1998/07/07 */
  #endif
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	MODEM_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_20P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 *//* DISABLE By H.Fujimura 1998/10/09 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			ENABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		DISABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 *//* DISABLE にします。By H.Fujimura 2002/09/12 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15  A355A0 からENABLE 2003/06/23 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
 #endif

	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/************************************************************************
 * ＡＮＺＵ タイプ Ｌ													*
 ************************************************************************/
#if defined(ANZU_L)

	/* ﾐﾉﾙﾀﾃｽﾄROM用 */
 #if defined(USAMLT)
	#define	PRO_MINOLTA_TEST_FUNC		ENABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
 #else
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
 #endif
 #if defined(USAMLT)
	#define USA
 #endif

 #if defined(USATST)							/* 1998/07/16 Y.Murata */
	#define	PRO_SGP_TEST_ROM			ENABLE
 #else
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
 #endif
 #if defined(USATST)
	#define USA
 #endif



 /*機種展開のため最初に国の定義を行います By M.Kotani 1998/01/30 ここから*/
 #if defined(USAOKI)
	#define USA
 #endif
 /*機種展開のため最初に国の定義を行います By M.Kotani 1998/01/30 ここまで*/
	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			ORANGE3				/* 村田製オレンジ３モデム */
	#define	PRO_PRINT_TYPE		LASER				/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_ANZU_L		/* あんず＿Ｌタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI300				/* 解像度３００ｄｐｉ */
	#define	PRO_PRINTER			DPI600				/* 解像度６００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルイン By N.S. '95,11,25 */
 #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	DISABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_SINGLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	SOFTWARE			/* ソフトコーデック */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
 #if defined(USA) || defined(TWN) || defined(JPN)	/** 1997/12/02 */
	#define	PRO_NCU_TYPE		ANZU_USA_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
 #else
	#define	PRO_NCU_TYPE		ANZU_GBR_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
 #endif
	#define	PRO_TX_SPEED		V33					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			DISABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		A4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		A4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
 #if defined(USA) || defined(AUS)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
 #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
 #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		ENABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_CLASS1		ENABLE				/* クラス１　1996/01/22 Eguchi */
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_EXT_DMAC		DISABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		DISABLE				/* 漢字ＣＧＲＯＭ対応 */
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	DISABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			DISABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* ＤＰＲＡＭを介したクラス１ */
	#define	PRO_AUTO_RX_SWITCH	ENABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
	#define PRO_LOW_TONER_PRINT		PRINT_LIMIT		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	ENABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	DISABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			ENABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	ENABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			DISABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

 #if defined(USA)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #else
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #endif
	#define PRO_JBIG			DISABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			DISABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM				DISABLE			/* ポプラＢ 拡張ＲＯＭの使用 By Y.Suzuki 1998/03/02 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	DISABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		ENABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		ENABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
 #if defined(USA)
	#define PRO_DATE_SET_RXDOC_CHK	ENABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
 #else
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
 #endif
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
/*	#define PRO_CL1_TELFAX_LAN	DISABLE	*/			/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
	#define PRO_CL1_TELFAX_LAN	ENABLE				/* for SALUTATION 1998/07/14 by Y.Tanimoto */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define PRO_SH2_INTERNAL_DMAC	SCN_PRN_CODEC_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				DISABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		DISABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/************************************************************************
 * ＡＮＺＵ タイプ Ｖ	インターネットＦＡＸモデル						*
 ************************************************************************/
#if defined(ANZU_V)
	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			ORANGE3				/* 村田製オレンジ３モデム */
	#define	PRO_PRINT_TYPE		LASER				/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_ANZU_L		/* あんず＿Ｌタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI300				/* 解像度３００ｄｐｉ */
	#define	PRO_PRINTER			DPI600				/* 解像度６００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN			ENABLE				/* ダイヤルイン By N.S. '95,11,25 */
 #else
	#define	PRO_DIALIN			DISABLE				/* ダイヤルイン By N.S. '95,11,25 */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	DISABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_SINGLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	SOFTWARE			/* ソフトコーデック */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
/*  #if defined(USA) || defined(TWN) || defined(JPN)	/@@ 1997/12/02 */
/*	#define	PRO_NCU_TYPE		ANZU_USA_TYPE		/@ NCU/ｶﾌﾟﾗｰTyep */
/*  #else */
	/*　InternetFAXモデルのカプラは28.8Kタイプのカプラです　*/
	#define	PRO_NCU_TYPE		ANZU_GBR_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
/* #endif*/
	#define	PRO_TX_SPEED		V33					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			DISABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		A4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		A4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
 #if defined(USA) || defined(AUS)
	#define	PRO_RING_MASTER		ENABLE				/* リングマスター設定 '95,11,25 By N.S.*/
 #else
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
 #endif
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		ENABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */

#if (0)
	#define	PRO_CLASS1			ENABLE				/* クラス１　1996/01/22 Eguchi */
#endif
	/* ｲﾝﾀｰﾈｯﾄFAXを組み込むのでClass1をDisableにします　*/
	#define	PRO_CLASS1			DISABLE				/* クラス１　1998/03/10 Y.Tanimoto */
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_PC_PRINT		ENABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_EXT_DMAC		DISABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		DISABLE				/* 漢字ＣＧＲＯＭ対応 */
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	DISABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			DISABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* ＤＰＲＡＭを介したクラス１ */
	#define	PRO_AUTO_RX_SWITCH	ENABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
	#define PRO_LOW_TONER_PRINT		PRINT_LIMIT		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	ENABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	DISABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			ENABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	ENABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			DISABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

 #if defined(USA)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #else
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
 #endif
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */

#if (0)
	#define PRO_JBIG				ENABLE			/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_VOICE_RECOGNITION	ENABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
#endif
	/* ｲﾝﾀｰﾈｯﾄFAXを組み込むのでDisableに変更します　*/
	#define PRO_JBIG				DISABLE			/* JBIG対応 1998/03/10  By Y.Tanimoto */
	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/03/10  By Y.Tanimoto */

	#define PRO_VOICE_ANSWER		DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			DISABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM				DISABLE			/* ポプラＢ 拡張ＲＯＭの使用 By Y.Suzuki 1998/03/02 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define PRO_DIALUP_INTERNET_FAX		ENABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	DISABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE		DISABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		ENABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		ENABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	SCN_PRN_CODEC_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				DISABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		DISABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/****************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｎ（ＮＴＴ仕様のポプラＬ）1998/01/17  By T.Yamaguchi	*
 ***************************************************************************/
#if defined(POPLAR_N)
	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			ORANGE3				/* 村田製オレンジ３モデム */
	#define	PRO_PRINT_TYPE		LED					/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_L		/* ポプラ＿Ｌタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI200				/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER			DPI200				/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
	#define	PRO_DIALIN			ENABLE				/* ダイヤルインあり By N.S. '95,11,25 */
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_SINGLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	SOFTWARE			/* ソフトコーデック */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
	#define	PRO_NCU_TYPE		POPLAR_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_TX_SPEED		V33					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			DISABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		B4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		ENABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi */
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_EXT_DMAC		DISABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		DISABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	ENABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
	#define PRO_JBIG			DISABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		ENABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX			ENABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */

	#define PRO_UPPER_COVER			ENABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM			DISABLE				/* ポプラＢ 拡張ＲＯＭの使用 By Y.Suzuki 1998/03/02 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	DISABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		ENABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	ENABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		ENABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		ENABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		ENABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	DISABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_1M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	ENABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	ENABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	SCN_PRN_CODEC_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				DISABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				ENABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		DISABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/*************************************
 * ＳＡＫＡＫＩ1998/5/21 By K.Kawata *
 *************************************/
#if defined(SAKAKI)
 #if defined(JP0)	/* SAKAKI2 By M.Maeda 2002/08/07 */
	#define JPN
 #endif
	#define	PRO_MAKER		MML		/* 村田仕様 */
	#define	PRO_CPU			SH7043		/* SH2 */
	#define	PRO_MODEM		R288F		/* ROCKWELL製 28.8K */
	#define	PRO_PRINT_TYPE		THERMAL_TRANS	/* 熱転写記録方式 */
	#define	PRO_PAPER_TYPE		ROLL_PAPER	/* ロール紙 */
	#define	PRO_KEYPANEL		PANEL_SAKAKI	/* さかきタイプ */
	#define	PRO_PANEL		KANJI		/* 漢字対応操作パネル */
	#define	PRO_CCD			DPI200		/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER		DPI200		/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL		UNITED		/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE		/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST		ENABLE		/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 */
	#define	PRO_DEPARTMENT		ENABLE		/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE		/* 転送先ダイヤル */
	#define	PRO_DIALIN		ENABLE		/* ダイヤルイン */
	#define	PRO_BUILTIN_TAD		DISABLE		/* 内蔵TAD */
	#define	PRO_FIP			DISABLE		/* FIP */
	#define	PRO_DIRECTORY		ENABLE		/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE		/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE		/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_TRIPLE	/* コーデックの個数 */
	#define	PRO_SCN_CODEC_TYPE	IDP301		/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	SOFTWARE	/* 松下CODEC *//* ＰＯＰＬＡＲ＿Ｈはこれは６３です。 By O.Kimoto 1997/10/28 */
	#define	PRO_COM_CODEC_TYPE	MN86064		/* 松下CODEC *//* 環境が整うまでMN86063とする。 By O.Kimoto 1997/10/15 */
	#define	PRO_ADD_MEMORY		ENABLE		/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE		/* 内線通話 */
	#define	PRO_REMOTE_FAX		DISABLE		/* リモートFAX */
	#define	PRO_NCU_TYPE		SAKAKI_TYPE	/* NCU/ｶﾌﾟﾗｰTyep */ /* POPLAR_TYPE => SAKAKI_TYPE by H.Kubo 1998/07/03 */
	#define	PRO_TX_SPEED		V34		/* V8､V34 28.8K */
	#define	PRO_HQ_MODE		DISABLE		/* 高画質モード									*/
	#define	PRO_DIAG		ENABLE		/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		A3WIDTH		/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH		/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64	/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE		/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE		/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE		/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR			ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP		ENABLE		/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE		/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE		/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE		/** プリンタ受信		Bamboo	Apr.13.1994 */
	#define	PRO_RING_MASTER		DISABLE		/* リングマスター設定 */
	#define	PRO_DB_POLLING_TX	ENABLE		/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE		/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE		/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE		/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE		/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE		/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE		/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE		/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE		/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED	DISABLE		/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE		/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		DISABLE		/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE		/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE		/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE		DISABLE		/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_CLASS1		DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM		DISABLE	/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		DISABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE		DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER		DISABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	ENABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define PRO_G4			DISABLE	/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE	/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_EXT_DMAC		DISABLE	/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS			DISABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE		ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		ENABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM	DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	ENABLE		/** 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT	PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	DISABLE		/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN		ENABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE		/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR		ENABLE		/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE	/* 標準収容回線数 By O.Kimoto 1997/11/01 */
	#define PRO_DEPART_NEW_LIST	DISABLE		/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
	#define PRO_JBIG		ENABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE			/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER	DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX		DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */
	#define PRO_UPPER_COVER		DISABLE	/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM		DISABLE		/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */
	#define PRO_DIALUP_INTERNET_FAX	DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX	DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE		/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
	#define PRO_RDS_FLASH_ROM_WRITE	ENABLE	/** リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH	DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE		/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME	DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
	#define	PRO_MINOLTA_TEST_FUNC	DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	DISABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M		/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE		/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_NUMBER_DISPLAY	ENABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_V23 /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_NAME_RECALL		ENABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	ENABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS ENABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	ENABLE			/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	COM_CODEC_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	ENABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	ENABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_SAKAKI		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_SAKAKI		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	ENABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_A			/* 1998/10/09 H.Yoshikawa */
	#define PRO_NEW_JATE		ENABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
 #if defined(JP0)	/* SAKAKI2 By M.Maeda 2002/09/12 */
	#define	PRO_MODEM_R288F_VERSION FM336_VERSION_12P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_29			/* 第２水準漢字２９文字対応 By. M.Maeda 2002/10/11 */
 #else
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_26P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_27			/* 第２水準漢字２７文字対応 1998/09/17 H.Yoshikawa */
 #endif
	#define PRO_STOP_MODE_CLEAR	ENABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		ENABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY ENABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH ENABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		ENABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	ENABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
 #if defined(JP0)	/* SAKAKI2 By M.Maeda 2002/08/28 */
	#define PRO_ALLRAMCLR_WO_MCP	ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
 #else
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
 #endif
	#define PRO_GEAR_BACK_LASH	DISABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		ENABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			DISABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_OKI_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		ENABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	DISABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	ENABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF		ENABLE	/* 新送信証フォーマット By K.Kawata 2000/2/3 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	ENABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 *//* ENABLE化 2000/10/18 H.Yoshikawa */
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				ENABLE			/* NEW JIG 2002/06/03 T.Takagi  2002/09/25  By T.Yamaguchi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
 #if defined(JP0)	/* SAKAKI2 By M.Maeda 2002/08/28 */
	#define PRO_CLEAR_FIRST_LAST	ENABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			DISABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	ENABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			ENABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			ENABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			ENABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		ENABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	ENABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
 #else
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
 #endif
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/*************************************
 * ＨＩＮＯＫＩ用です。By O.Kimoto 1998/08/28
 *************************************/
#if defined(HINOKI)
 #if 0 /* 使われていない為削除します 2003/02/17 T.Takagi defined(JP1) */	/* クラス１搭載仕様 by H.Hirao 1999/04/14 */
	#define JPN
 #endif
	#define	PRO_MAKER		MML						/* 村田仕様 */
	#define	PRO_CPU			SH7043					/* SH2 */
	#define	PRO_MODEM		R288F					/* ROCKWELL製 28.8K */
	#define	PRO_PRINT_TYPE		THERMAL				/* THERMAL */				/* 熱転写記録方式 */
	#define	PRO_PAPER_TYPE		ROLL_PAPER			/* ROLL_PAPER */			/* ロール紙 */
	#define	PRO_KEYPANEL		PANEL_HINOKI		/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
	#define	PRO_PANEL		ANK						/* 漢字対応操作パネル */
	#define	PRO_CCD			DPI200					/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER		DPI200					/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL		UNITED					/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	ENABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST		DISABLE					/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 *//* DISABLE By H.Fujimura 1998/12/09 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN		ENABLE					/* ダイヤルイン */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_DIALIN		DISABLE					/* ダイヤルイン */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP			DISABLE					/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_TRIPLE			/* コーデックの個数 */
	#define	PRO_SCN_CODEC_TYPE	SOFTWARE			/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	SOFTWARE			/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX */
 #if defined(JPN)
	#define	PRO_NCU_TYPE		HINOKI_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
 #else /* TWN仕様 by H.Hirao 1999/01/29 */
	#define	PRO_NCU_TYPE		ANZU_GBR_TYPE
 #endif
	#define	PRO_TX_SPEED		V34					/* V8､V34 28.8K */
	#define	PRO_HQ_MODE		DISABLE					/* 高画質モード									*/
	#define	PRO_DIAG		ENABLE					/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		B4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR			ENABLE					/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP		ENABLE					/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		ENABLE				/** プリンタ受信		Bamboo	Apr.13.1994 */
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 */
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
 #if defined(JPN)
  #if 0 /* 使われていない為削除します 2003/02/17 T.Takagi defined(JP1) */	/* クラス１搭載仕様 by H.Hirao 1999/04/14 */
	#define	PRO_CLASS1			ENABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		ENABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
  #else
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
  #endif
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_CLASS1			ENABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		ENABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
 #endif
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM		DISABLE					/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		DISABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE		DISABLE					/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER		DISABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	ENABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */ /* enabled 1998/12/21 */
	#define PRO_G4			DISABLE					/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_EXT_DMAC		DISABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
 #if defined(JPN)
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
 #else	/* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_JIS_CODE		DISABLE /*ENABLE*/				/* 漢字ＣＧＲＯＭ対応 by H.Hirao 1999/02/02 */
 #endif
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	DISABLE			/* 連続ポーリング機能 *//* HINOKI無し By O.Kimoto 1998/12/02 */
	#define	PRO_FBS			DISABLE					/* フラットベッドスキャナ */
	#define	PRO_F_CODE		ENABLE					/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		ENABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao *//* ENABLE By H.Fujimura 1998/09/29 */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM	DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	ENABLE				/** 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT	PRINT_FREE			/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	DISABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN		ENABLE					/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
 #if defined(JPN)
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
 #else	/* ROMが溢れた by H.Hirao 1999/01/12 -> ENABLE by H.Hirao 1999/02/02*/
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
 #endif
	#define PRO_JAM_OPR		ENABLE					/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */
	#define PRO_DEPART_NEW_LIST	ENABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 *//* ENABLE By H.Fujimura 1998/11/17 */
	#define PRO_JBIG		ENABLE					/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER	DISABLE				/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX		DISABLE				/* リモート受信 1998/01/17  By T.Yamaguchi */
	#define PRO_UPPER_COVER		DISABLE				/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM		DISABLE					/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */
	#define PRO_DIALUP_INTERNET_FAX	DISABLE			/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX	DISABLE			/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 *//* ENABLE By H.Fujimura 1998/10/09 */
	#define PRO_RDS_FLASH_ROM_WRITE	ENABLE			/** リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH	DISABLE			/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME	DISABLE			/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 *//* ENABLE By H.Fujimura 1998/10/09 */
	#define	PRO_MINOLTA_TEST_FUNC	DISABLE			/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION	DISABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
 #if defined(JPN)
	#define PRO_NUMBER_DISPLAY	ENABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_NUMBER_DISPLAY_WARP	ENABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_V23	/* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE	/* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
 #endif
	#define PRO_NAME_RECALL		ENABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	ENABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS ENABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
 #if defined(JPN)
  #if 0 /* 使われていない為削除します 2003/02/17 T.Takagi defined(JP1) */	/* クラス１搭載仕様 by H.Hirao 1999/04/14 */
	#define PRO_CL1_TELFAX_LAN	ENABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
  #else
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
  #endif
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define PRO_CL1_TELFAX_LAN	ENABLE /*DISABLE*/				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 DISABLE -> ENABLE by H.Hirao 1999/02/10 */
 #endif
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	ENABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	COM_CODEC_DMA	/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	ENABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa *//* とりあえず By O.Kimoto 1998/09/07 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	ENABLE /*DISABLE*/				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_HINOKI /*DTC_INT_OTHER*/		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_NONE		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_A			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
  #if defined(JPN) || defined(JP1)	/* by H.Hirao 1999/05/08 */
	#define PRO_NEW_JATE		ENABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
  #else
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */ /* ＪＰＮ以外は必要ないのでDISABLEにしました by H.Hirao 1999/04/29 */
  #endif
	#define	PRO_MODEM_R288F_VERSION R288F_VERSION_26P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_27			/* Change KANJI2_26 to KANJI_27 by O.Kimoto 1999/01/13 *//* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	ENABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa *//* ENABLE By H.Fujimura 1998/11/16 */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_8BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	ENABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		ENABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		ENABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_LC82103	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY ENABLE	/* Change DISABLE to ENABLE by O.Kimoto 1999/01/11 */			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	ENABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa *//* ENABLE By H.Fujimura 1998/10/14 */
	#define PRO_ALLRAMCLR_WO_MCP	DISABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	DISABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		ENABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	ENABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10 /*TIME5*/	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 changed by H.Hirao 1999/02/16 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME10_2 /* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	ENABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			ENABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
 #if defined(JPN)
	#define	PRO_MESSAGE_KANJI_INPUT	ENABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
 #endif
	#define	PRO_DISPLAY_TEL_TO_IDLE	ENABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	ENABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				ENABLE /*DISABLE*/			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 DISABLE -> ENABLE by H.Hirao 1999/02/09 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			ENABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	ENABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			ENABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 *//* RDC200000302 By O.Kimoto 2000/08/01 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	ENABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa DISABLE->ENABLE 2000/11/24 by T.Soneoka*/
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif


/****************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｆ								1999/09/27 Y.Murata *
 * ＮＴＴ仕様のポプラＬ ＋ ＦＭ３３６モデム ＋ ＪＢＩＧ						*
 ***************************************************************************/
#if defined(POPLAR_F)

 #if defined(JP1)	/* ムラタ仕様 */
	#define JPN
 #endif

	#define	PRO_MAKER			MML					/* 村田仕様 */
	#define	PRO_CPU				SH7043				/* SH2 */
	#define	PRO_MODEM			R288F				/* スーパーＧ３対応モデム */
	#define	PRO_PRINT_TYPE		LED					/* レーザーショット */
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
	#define	PRO_KEYPANEL		PANEL_POPLAR_L		/* ポプラ＿Ｌタイプ */
	#define	PRO_PANEL			ANK					/* ANK対応操作パネル */
	#define	PRO_CCD				DPI200				/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER			DPI200				/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL			UNITED				/* 送受信分離型通信管理記録 */
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
	#define	PRO_COST			DISABLE				/* 料金管理 */
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
	#define	PRO_DIALIN			ENABLE				/* ダイヤルインあり By N.S. '95,11,25 */
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP				DISABLE				/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
	#define	PRO_CODEC_NUMBER	CDC_SINGLE			/* コーデックの個数 **/
	#define	PRO_SCN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話		 By N.S. '93,12,21 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX	 By N.S. '93,12,21 */
	#define	PRO_NCU_TYPE		HINOKI_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_TX_SPEED		V34					/* V17､V33対応	以下項目追加鈴木			*****/
	#define	PRO_HQ_MODE			DISABLE				/* 高画質モード									*/
	#define	PRO_DIAG			ENABLE				/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		B4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR				ENABLE				/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define	PRO_STAMP			ENABLE				/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		DISABLE				/* プリンタ受信		Bamboo	Apr.13.1994 */
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 '95,11,25 By N.S. */
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_RELAYED_REPORT	DISABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki */
	#define	PRO_LIST_TX_WITH_IMG	DISABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		ENABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi */
	#define	PRO_CLASS1_EXT_FUNC	DISABLE				/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM			ENABLE				/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		ENABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE			DISABLE				/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_EXT_DMAC		ENABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	ENABLE			/* 連続ポーリング機能 */
	#define	PRO_FBS				DISABLE				/* フラットベッドスキャナ */
	#define	PRO_F_CODE			ENABLE				/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		ENABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	ENABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	DISABLE				/* 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define	PRO_CIPHER			DISABLE				/* アリロー By Y.Suzuki 1997/05/21 */
	#define PRO_LOW_TONER_PRINT		PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	ENABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_G4				DISABLE				/* G4 By O.Kimoto 1997/07/22 */
	#define PRO_DOC_IN			DISABLE				/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_JAM_OPR			ENABLE				/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 */
	#define PRO_JBIG			ENABLE				/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_VOICE_ANSWER		ENABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
 #if defined(JP1)
	#define PRO_REMOTE_RX			DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */
 #else
	#define PRO_REMOTE_RX			ENABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */
 #endif

	#define PRO_UPPER_COVER			ENABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM			DISABLE				/* ポプラＢ 拡張ＲＯＭの使用 By Y.Suzuki 1998/03/02 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define PRO_DIALUP_INTERNET_FAX		DISABLE		/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE		/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */

 #if defined(JP1)
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
 #else
	#define	PRO_NEW_DIAL_OPR	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 */
 #endif
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE		/* リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
 #if defined(JP1)
	#define PRO_ONHOOK_RX_SWITCH		DISABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
 #else
	#define PRO_ONHOOK_RX_SWITCH		ENABLE		/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
 #endif
 #if defined(JP1)
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
 #else
	#define PRO_NORING_TEL1_DETACHABLE	ENABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
 #endif
 #if defined(JP1)
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
 #else
	#define PRO_SCAN_1000mm		ENABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
 #endif
 #if defined(JP1)
	#define PRO_JOURNAL_PRINT_TIME		DISABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
 #else
	#define PRO_JOURNAL_PRINT_TIME		ENABLE		/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
 #endif

	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */

 #if defined(JP1)
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
 #else
	#define	PRO_NEW_DIAL_OPR2	DISABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 */
 #endif
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE		/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */

 #if defined(JP1)
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
 #else
	#define	PRO_FIXED_REDUCTION	DISABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
 #endif
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_1M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */

 #if defined(JP1)
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
 #else
	#define	PRO_NOT_AUTO_RX_DISP	ENABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
 #endif

	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE /* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */

	#define PRO_NAME_RECALL		DISABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	DISABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	ENABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS DISABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */

 #if defined(JP1)
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
 #else
	#define PRO_DRUM_PRT_CNT	ENABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
 #endif
	#define PRO_RTC_IO_LOW_READ	DISABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	MODEM_DMA		/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	DISABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	DISABLE				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_OTHER		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_OTHER		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_R			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_NEW_JATE		ENABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MODEM_R288F_VERSION FM336_VERSION_12P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_26			/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	DISABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_16BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	DISABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		DISABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		DISABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_OTHER	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY DISABLE			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	DISABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa */
	#define PRO_ALLRAMCLR_WO_MCP	ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
	#define PRO_GEAR_BACK_LASH	ENABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		DISABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	DISABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME0	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	DISABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			ENABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
	#define	PRO_DISPLAY_TEL_TO_IDLE	DISABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT				DISABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			DISABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	ENABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_SPECIAL_REPLAY_TRANS	DISABLE	/*1999.4.21 K.Kawata */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
 #if defined(JP1)
	#define PRO_NEW_TX_CONF			ENABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
 #else
        #define PRO_NEW_TX_CONF			DISABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 */
 #endif
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_DIAL_PULSE_TASK		DISABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa */
	#define PRO_ENERGY_SAVE			DISABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			DISABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				DISABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 内線トーン検出不可 by Y.Kano 2004/10/27 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif

/*************************************
 * ＨＩＮＯＫＩ２用です。By O.Kimoto 2001/11/07
 *************************************/
/********************/
/* ＳＡＴＳＵＫＩ２ */
/********************/
/********************/
/*   ＬＶＮＤＲ２   */
/********************/

#if defined(HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)
 #if defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/09 */
	#define JPN
 #endif
 #if defined(JP1)		/* 55転送 (PRO_REMOTE_DIAL_TRANSFER == ENABLE) by T.Takagi 2003/02/04 */
	#define JPN
 #endif
	#define	PRO_MAKER		MML						/* 村田仕様 */
	#define	PRO_CPU			SH7043					/* SH2 */
	#define	PRO_MODEM		R288F					/* ROCKWELL製 28.8K */
 #if defined(STOCKHM2)
	#define	PRO_PAPER_TYPE		CUT_PAPER			/* カット紙 */
 #else
	#define	PRO_PAPER_TYPE		ROLL_PAPER			/* ROLL_PAPER */			/* ロール紙 */
 #endif
 	#define	PRO_PRINT_TYPE		THERMAL				/* THERMAL */
 
/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*	#define	PRO_KEYPANEL		PANEL_HINOKI	*/	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */

 #if defined (SATSUKI2) 
	#define	PRO_KEYPANEL		PANEL_SATSUKI2		/* ＳＡＴＳＵＫＩ２タイプ *//* Add By Y.Kano 2003/07/10 */
 #elif 	defined (STOCKHM2)
	#define	PRO_KEYPANEL		PANEL_STOCKHM2		/* ＳＴＯＣＫＨＯＬＭ２タイプ *//* Add By SMuratec 夏 2004/5/26 */
 #else
	#define	PRO_KEYPANEL		PANEL_HINOKI		/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
 #endif

	#define	PRO_PANEL		ANK						/* 漢字対応操作パネル */
	#define	PRO_CCD			DPI200					/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER		DPI200					/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL		UNITED					/* 送受信分離型通信管理記録 */
 #if defined (SATSUKI2) || defined(STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/12 */
	#define	PRO_BATCH_TX		DISABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
 #else
	#define	PRO_BATCH_TX		ENABLE				/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	ENABLE		/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
 #endif
	#define	PRO_COST		DISABLE					/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 *//* DISABLE By H.Fujimura 1998/12/09 */

 /* DVT: Modify by SMuratec K.W.Q 2004/09/07 */
 #if 	defined (STOCKHM2)
	#define	PRO_DEPARTMENT		DISABLE				/* 部門管理 */
 #else
	#define	PRO_DEPARTMENT		ENABLE				/* 部門管理 */
 #endif
 
	#define	PRO_SUB_DIAL		ENABLE				/* 転送先ダイヤル */
 #if defined(JPN)
	#define	PRO_DIALIN		ENABLE					/* ダイヤルイン */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_DIALIN		DISABLE					/* ダイヤルイン */
 #endif
	#define	PRO_BUILTIN_TAD		DISABLE				/* 内蔵TAD */
	#define	PRO_FIP			DISABLE					/* FIP */
	#define	PRO_DIRECTORY		ENABLE				/* 電話帳 */
	#define	PRO_BRANCH_RX		DISABLE				/* ブランチ転送 */

 /* Modify by SMuratec 夏 2004/6/8 */
 #if defined (SATSUKI2) || defined(HINOKI2)
	#define	PRO_PRINT_FACE_UP	ENABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
 #elif 	defined (STOCKHM2)
	#define	PRO_PRINT_FACE_UP	DISABLE				/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
 #endif
 
	#define	PRO_CODEC_NUMBER	CDC_TRIPLE			/* コーデックの個数 */
	#define	PRO_SCN_CODEC_TYPE	SOFTWARE			/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE	SOFTWARE			/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE	MN86064				/* 松下CODEC */
	#define	PRO_ADD_MEMORY		ENABLE				/* 増設メモリ */
	#define	PRO_INTER_COM		DISABLE				/* 内線通話 */
	#define	PRO_REMOTE_FAX		DISABLE				/* リモートFAX */
 #if defined(JPN)
	#define	PRO_NCU_TYPE		HINOKI_TYPE			/* NCU/ｶﾌﾟﾗｰTyep */
 #else /* TWN仕様 by H.Hirao 1999/01/29 */
	#define	PRO_NCU_TYPE		ANZU_GBR_TYPE
 #endif
	#define	PRO_TX_SPEED		V34					/* V8､V34 28.8K */
	#define	PRO_HQ_MODE		DISABLE					/* 高画質モード									*/
	#define	PRO_DIAG		ENABLE					/* リモート診断									*/
	#define	PRO_SCAN_WIDTH		B4WIDTH				/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH		B4WIDTH				/* 最大記録紙幅 */
	#define	PRO_HALFTONE		HARMONY64			/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST	ENABLE				/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX		ENABLE				/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE		DISABLE				/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR			ENABLE					/* ＭＭＲ符号化							   1994/02/08 Y.M */
 #if defined (SATSUKI2) || defined(STOCKHM2)
	#define	PRO_STAMP		DISABLE					/* 済みスタンプ */ /* 変更 by Y.Kano 2003/10/02 */
 #else
	#define	PRO_STAMP		ENABLE					/* 済みスタンプ		Bamboo	Jan.12'94	*/
 #endif
 #if defined (SATSUKI2)
	#define	PRO_SEPERATE_INTER_LOCK	DISABLE			/* インター・ロックがスキャナー。プリンター別々 */
 #else
	#define	PRO_SEPERATE_INTER_LOCK	ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
 #endif
	#define	PRO_SMOOTHING		ENABLE				/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX		ENABLE				/** プリンタ受信		Bamboo	Apr.13.1994 */
	#define	PRO_RING_MASTER		DISABLE				/* リングマスター設定 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/12 */
	#define	PRO_DB_POLLING_TX	DISABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	DISABLE				/* 検索ポーリング受信 */
#else
	#define	PRO_DB_POLLING_TX	ENABLE				/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX	ENABLE				/* 検索ポーリング受信 */
#endif
	#define	PRO_DUAL_PRINT		ENABLE				/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT		DISABLE				/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT	ENABLE				/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL		DISABLE				/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT	DISABLE				/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL		DISABLE				/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP		ENABLE				/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED	DISABLE				/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE	DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM	DISABLE				/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS		DISABLE				/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX		DISABLE				/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
	#define	PRO_CLOSED_NETWORK	ENABLE				/* 閉域通信 1995/12/03 Eguchi */
	#define	PRO_SOFT_CODEC		DISABLE				/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE		DISABLE				/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
 #if defined(JPN)
	#define	PRO_CLASS1			DISABLE				/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE				/* クラス１ECM 通信 by H.Kubo1998/03/06 */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */	/* HINOKI2 TWN はクラス１なし */
	#define	PRO_CLASS1			DISABLE	/*ENABLE*/	/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM		DISABLE	/*ENABLE*/	/* クラス１ECM 通信 by H.Kubo1998/03/06 */
 #endif
	#define	PRO_CLASS1_EXT_FUNC	DISABLE	/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_PC_PRINT		DISABLE				/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM		DISABLE					/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE		DISABLE				/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE		DISABLE					/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER		DISABLE				/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT	ENABLE				/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG	ENABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */ /* enabled 1998/12/21 */
	#define PRO_G4			DISABLE					/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX	DISABLE				/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_EXT_DMAC		DISABLE				/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE	DISABLE				/* コピー／ＦＡＸ切り替え */
 #if defined(JPN)
	#define	PRO_JIS_CODE		ENABLE				/* 漢字ＣＧＲＯＭ対応 */
 #else	/* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_JIS_CODE		DISABLE /*ENABLE*/				/* 漢字ＣＧＲＯＭ対応 by H.Hirao 1999/02/02 */
 #endif
	#define	PRO_SECURITY_RX		ENABLE				/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT	ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING	DISABLE			/* 連続ポーリング機能 *//* HINOKI無し By O.Kimoto 1998/12/02 */
	#define	PRO_FBS			DISABLE					/* フラットベッドスキャナ */
	#define	PRO_F_CODE		ENABLE					/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY		ENABLE				/* Ｆコード中継配信機能 1998/08/21 By H.Hirao *//* ENABLE By H.Fujimura 1998/09/29 */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE		/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY	DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT	DISABLE				/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM	DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM	DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH	ENABLE				/** 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT	PRINT_FREE			/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE	DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE	DISABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN		ENABLE					/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V	DISABLE				/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
 #if defined(JPN)
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
 #else	/* ROMが溢れた by H.Hirao 1999/01/12 -> ENABLE by H.Hirao 1999/02/02*/
	#define PRO_SERVICE_FUNC	ENABLE				/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
 #endif
	#define PRO_JAM_OPR		ENABLE					/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
	#define PRO_LINENUMBER		SINGLE_LINE			/* 標準収容回線数 By O.Kimoto 1997/11/01 */

 /* DVT: Modify by SMuratec K.W.Q 2004/09/07 */
 #if 	defined (STOCKHM2)
	#define PRO_DEPART_NEW_LIST	DISABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 *//* ENABLE By H.Fujimura 1998/11/17 */
 #else
	#define PRO_DEPART_NEW_LIST	ENABLE				/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 *//* ENABLE By H.Fujimura 1998/11/17 */
 #endif

	#define PRO_JBIG		ENABLE					/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE	DISABLE				/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
	#define PRO_VOICE_RECOGNITION	DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
 #if defined(JPNNTT)
	#define PRO_VOICE_ANSWER	ENABLE				/* 音声応答 1998/01/17  By T.Yamaguchi */
 #else
	#define PRO_VOICE_ANSWER	DISABLE				/* 音声応答 1998/01/17  By T.Yamaguchi */
 #endif
	#define PRO_REMOTE_RX		DISABLE				/* リモート受信 1998/01/17  By T.Yamaguchi */
	#define PRO_UPPER_COVER		DISABLE				/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE	DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM		DISABLE					/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */
	#define PRO_DIALUP_INTERNET_FAX	DISABLE			/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX	DISABLE			/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP	ENABLE				/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION		DISABLE				/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 *//* ENABLE By H.Fujimura 1998/10/09 */
	#define PRO_RDS_FLASH_ROM_WRITE	ENABLE			/** リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH	DISABLE			/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
 #if defined(JPNNTT)
	#define PRO_NORING_TEL1_DETACHABLE	ENABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto *//* Add By O.Kimoto 2002/09/27 */
 #else
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE		/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
 #endif
	#define PRO_SCAN_1000mm		DISABLE				/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME	DISABLE			/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT		DISABLE				/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2	ENABLE				/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 *//* ENABLE By H.Fujimura 1998/10/09 */
	#define	PRO_MINOLTA_TEST_FUNC	DISABLE			/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
#if defined(STOCKHM2)		/*	Modify by SMuratec K.W.Q 2004/05/25	*/
	#define	PRO_FIXED_REDUCTION	ENABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
#else
	#define	PRO_FIXED_REDUCTION	DISABLE				/* 固定縮小率 by K.Watanabe 1998/05/13 */
#endif
	#define PRO_REVERSE_PRINT	DISABLE				/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
	#define	PRO_DRAM_SIZE		DRAM_2M				/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI		DISABLE				/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION	DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
 #if defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/09 *//* Add By O.Kimoto 2002/09/27 */
	#define	PRO_NOT_AUTO_RX_DISP	ENABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
 #else
	#define	PRO_NOT_AUTO_RX_DISP	DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
 #endif
 #if defined(JPN)
	#define PRO_NUMBER_DISPLAY	ENABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_NUMBER_DISPLAY_WARP	ENABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_V23	/* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define PRO_NUMBER_DISPLAY	DISABLE				/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_NUMBER_DISPLAY_WARP	DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL	CALLER_ID_DISABLE	/* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
 #endif
	#define PRO_NAME_RECALL		ENABLE				/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO		DISABLE				/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER	ENABLE				/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK	DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS ENABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1		DISABLE				/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
 #if defined(JPN)
	#define PRO_CL1_TELFAX_LAN	DISABLE				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */	/* HINOKI2 TWN はクラス１なし */
	#define PRO_CL1_TELFAX_LAN	DISABLE /*ENABLE*/				/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 DISABLE -> ENABLE by H.Hirao 1999/02/10 */
 #endif
 	#define PRO_OKI				DISABLE				/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT	DISABLE				/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ	ENABLE				/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE		/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC	COM_CODEC_DMA	/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH	ENABLE				/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa *//* とりあえず By O.Kimoto 1998/09/07 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_PITNEYBOWES		DISABLE				/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM	ENABLE /*DISABLE*/				/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE	DTC_INT_HINOKI /*DTC_INT_OTHER*/		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE	EXT_INT_NONE		/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK	DISABLE				/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION		SH7043_A			/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
  #if defined(JPN)
	#define PRO_NEW_JATE		ENABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
  #else
	#define PRO_NEW_JATE		DISABLE				/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */ /* ＪＰＮ以外は必要ないのでDISABLEにしました by H.Hirao 1999/04/29 */
  #endif
	#define	PRO_MODEM_R288F_VERSION FM336_VERSION_12P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_KANJI2_TYPE		KANJI2_27			/* Change KANJI2_26 to KANJI_27 by O.Kimoto 1999/01/13 *//* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_STOP_MODE_CLEAR	ENABLE				/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa *//* ENABLE By H.Fujimura 1998/11/16 */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_8BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO	ENABLE				/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME		ENABLE				/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL		ENABLE				/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR	IMAGE_PROCESSOR_LC82103	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY ENABLE	/* Change DISABLE to ENABLE by O.Kimoto 1999/01/11 */			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE		/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH		DISABLE /* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST		DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT	ENABLE				/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa *//* ENABLE By H.Fujimura 1998/10/14 */
	#define PRO_ALLRAMCLR_WO_MCP	ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 *//* RDC200200635 By O.Kimoto 2003/02/14 */
	#define PRO_GEAR_BACK_LASH	DISABLE				/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH		ENABLE				/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR	ENABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10 /*TIME5*/	/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 changed by H.Hirao 1999/02/16 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME10_2 /* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX	ENABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM			ENABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
 #if defined(JPN)
	#define	PRO_MESSAGE_KANJI_INPUT	ENABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
 #else /* TWN仕様 by H.Hirao 1999/01/12 */
	#define	PRO_MESSAGE_KANJI_INPUT	DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
 #endif
	#define	PRO_DISPLAY_TEL_TO_IDLE	ENABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Modify by SMuratec 李 2004/07/07 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	DISABLE		/* ストップキー押下時の表示を待機画面にする */
	#define	PRO_DISPLAY_PRN_INITIALIZE	ENABLE		/* プリンターの初期化時の表示を使用する */
#else /* (PRO_PAPER_TYPE != CUT_PAPER) || !defined(STOCKHM2) */
	#define	PRO_DISPLAY_STOP_KEY_OPR	ENABLE		/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
	#define PRO_PREHEAT				ENABLE /*DISABLE*/			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 DISABLE -> ENABLE by H.Hirao 1999/02/09 */
	#define	PRO_IMADOKO				DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER			ENABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE			TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY		DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR	ENABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_PRINTER_GA_MD9803	DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP		DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI		DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX			DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF			ENABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 *//* RDC200000302 By O.Kimoto 2000/08/01 */
	#define	PRO_FAN_TEST			DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
 #if defined(JPNNTT)
	#define PRO_BT_DET_WHILE_RBT	DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
 #else
	#define PRO_BT_DET_WHILE_RBT	ENABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
 #endif
	#define PRO_DIAL_PULSE_TASK		ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa DISABLE->ENABLE 2000/11/24 by T.Soneoka*/
	#define PRO_ENERGY_SAVE			ENABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN			ENABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG				ENABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF		DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST	DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
	#define PRO_DIALIN_SW			ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_DRUM_TONER	DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK	DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING		ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1			DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
#if defined(STOCKHM2) /* Mod by SMuatec C.P 2004/06/08 */
	#define PRO_COM_RESULT			ENABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
#else 
	#define PRO_COM_RESULT			DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
#endif
#if defined(STOCKHM2) /* Add by SMuatec C.P 2004/08/20 */
	#define PRO_DISASTER_PREVENTION_FAX		DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
#endif
#if defined(HINOKI2) || defined (SATSUKI2)
	#define PRO_DISASTER_PREVENTION_FAX		DISABLE		/* 防災FAX対応 by Y.Kano 2004/08/19 */
#endif
	#define PRO_ECO_MODE			DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
 #if defined(JPNNTT) || defined(STOCKHM2) /* Mod by SMuatec C.P 2004/06/08 for test */
	#define PRO_COMM_RESULT_REVIEW	ENABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
 #else
	#define PRO_COMM_RESULT_REVIEW	DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
 #endif
	#define PRO_FANLOCK_DETECT_TIME DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE		/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
 #if defined(JPNNTT)
	#define PRO_MEMORY_SW_EDIT_GUARD	ENABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 #else
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE		/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2		DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
 #endif
  #if defined (SATSUKI2) || defined(STOCKHM2)
 #if defined(JPN)
	#define PRO_REMOTE_DIAL_TRANSFER	ENABLE		/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
 #else
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE		/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
 #endif
  #else	/* HINOKI2 */
 #if defined(JP1)
	#define PRO_REMOTE_DIAL_TRANSFER	ENABLE		/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
 #else
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE		/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
 #endif
  #endif
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
 #if defined(STOCKHM2)	/* 内線トーン検出 by Y.Kano 2004/10/27 */
	#define PRO_PBX_TONE_DETECT				ENABLE			/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/05/14 By Y.Tanaka */
 #else
	#define PRO_PBX_TONE_DETECT				DISABLE
 #endif
#endif

/************************************************
 * ＨＩＮＯＫＩ３用です。By Y.Tanaka 2004/10/06 *
 ************************************************/

#if defined(KEISATSU) /* 警察FAX */
	#define HINOKI3
#endif

#if defined(HINOKI3)
	#define HINOKI2

 #if defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/09 */
	#define JPN
 #endif
 #if defined(JP1)		/* 55転送 (PRO_REMOTE_DIAL_TRANSFER == ENABLE) by T.Takagi 2003/02/04 */
	#define JPN
 #endif

 #if (0)
  #if defined(JPN)		/* 松下モデムとＦＭ３３６の切り分けに用いる */
	#define	PRO_MODEM					MN195006		/* 松下モデム */
	#define	PRO_MODEM_R288F_VERSION 	R288F_VERSION_INVALID /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_RTC_RX5C338A			ENABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
  #else
	#define JPN
	#define	PRO_MODEM					R288F			/* ROCKWELL製 28.8K */
	#define	PRO_MODEM_R288F_VERSION 	FM336_VERSION_12P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
  #endif
 #else
	#define	PRO_MODEM					R288F			/* ROCKWELL製 28.8K */
	#define	PRO_MODEM_R288F_VERSION 	FM336_VERSION_12P /* R288F モデムのバージョン by H.Kubo 1998/09/07 */
	#define PRO_RTC_RX5C338A			DISABLE			/* RTCをRx5C338Aに変更 by Y.Tanaka 2004/10/27*/
 #endif

	#define	PRO_MAKER					MML				/* 村田仕様 */
	#define	PRO_CPU						SH7043			/* SH2 */
	#define	PRO_PAPER_TYPE				ROLL_PAPER		/* ROLL_PAPER */			/* ロール紙 */
	#define	PRO_PRINT_TYPE				THERMAL			/* THERMAL */

	#define	PRO_KEYPANEL				PANEL_HINOKI	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */

	#define	PRO_PANEL					ANK				/* 漢字対応操作パネル */
	#define	PRO_CCD						DPI200			/* 解像度２００ｄｐｉ */
	#define	PRO_PRINTER					DPI200			/* 解像度２００ｄｐｉ */
	#define	PRO_JOURNAL					UNITED			/* 送受信分離型通信管理記録 */
#if defined (KEISATSU) /* 警察FAX 05/05/12 石橋正和 */
	#define	PRO_BATCH_TX				DISABLE			/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	DISABLE			/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
#else
	#define	PRO_BATCH_TX				ENABLE			/* 一括送信 */
	#define	PRO_BATCH_TX_RESERVE_LIST	ENABLE			/* 一括送信予約リスト By H.Fujimura 1998/12/01 */
#endif
	#define	PRO_COST					DISABLE			/* 料金管理 *//* 仕様変更となりました By O.Kimoto 1997/11/13 *//* DISABLE By H.Fujimura 1998/12/09 */

 /* DVT: Modify by SMuratec K.W.Q 2004/09/07 */
	#define	PRO_DEPARTMENT				ENABLE			/* 部門管理 */
 
	#define	PRO_SUB_DIAL				ENABLE			/* 転送先ダイヤル */
	#define	PRO_BUILTIN_TAD				DISABLE			/* 内蔵TAD */
	#define	PRO_FIP						DISABLE			/* FIP */
	#define	PRO_DIRECTORY				ENABLE			/* 電話帳 */
	#define	PRO_BRANCH_RX				DISABLE			/* ブランチ転送 */

 /* Modify by SMuratec 夏 2004/6/8 */
	#define	PRO_PRINT_FACE_UP			ENABLE			/* 印字原稿がﾌｪｲｽ･ｱｯﾌﾟで出て来るか? */
 
	#define	PRO_CODEC_NUMBER			CDC_TRIPLE		/* コーデックの個数 */
	#define	PRO_SCN_CODEC_TYPE			SOFTWARE		/* 松下CODEC */
	#define	PRO_PRN_CODEC_TYPE			SOFTWARE		/* 松下CODEC */
	#define	PRO_COM_CODEC_TYPE			MN86064			/* 松下CODEC */
	#define	PRO_ADD_MEMORY				ENABLE			/* 増設メモリ */
	#define	PRO_INTER_COM				DISABLE			/* 内線通話 */
	#define	PRO_REMOTE_FAX				DISABLE			/* リモートFAX */
	#define	PRO_TX_SPEED				V34				/* V8､V34 28.8K */
	#define	PRO_HQ_MODE					DISABLE			/* 高画質モード									*/
	#define	PRO_DIAG					ENABLE			/* リモート診断									*/
	#define	PRO_SCAN_WIDTH				B4WIDTH			/* 最大原稿読み取り幅 1996/03/23 Eguchi*/
	#define	PRO_PRINT_WIDTH				B4WIDTH			/* 最大記録紙幅 */
	#define	PRO_HALFTONE				HARMONY64		/* 中間調６４階調								*/
	#define	PRO_RELAY_BROADCAST			ENABLE			/* 中継同報指示あり								*/
	#define	PRO_MEMORY_RX				ENABLE			/* メモリプリント中のメモリ受信 13.Jly'94		*/
	#define	PRO_PRN_RX_SMSE				DISABLE			/* プリンタ受信ＳＭＳＥあり				*********/
	#define	PRO_MMR						ENABLE			/* ＭＭＲ符号化							   1994/02/08 Y.M */
	#define PRO_STAMP					ENABLE			/* 済みスタンプ		Bamboo	Jan.12'94	*/
	#define	PRO_SEPERATE_INTER_LOCK		ENABLE			/* インター・ロックがスキャナー。プリンター別々 */
	#define	PRO_SMOOTHING				ENABLE			/* スムージング機能の有無 Add By O.K Feb,28th,1994 **/
	#define	PRO_PRINTER_RX				ENABLE			/** プリンタ受信		Bamboo	Apr.13.1994 */
	#define	PRO_RING_MASTER				DISABLE			/* リングマスター設定 */
	#define	PRO_DB_POLLING_TX			ENABLE			/* 検索ポーリング送信 */
	#define	PRO_DB_POLLING_RX			ENABLE			/* 検索ポーリング受信 */
	#define	PRO_DUAL_PRINT				ENABLE			/* 通信中にコピー等のプリント動作が出来るか否か 1994/05/20 Y.M */
	#define	PRO_TCR_PRINT				DISABLE			/* 送信証の印字機能 */
	#define	PRO_MONITOR_REPORT			ENABLE			/* モニター・レポート機能 By S.K 7/7/1994 */
	#define	PRO_PAT_JOURNAL				DISABLE			/* ジャーナルイメージ展開 1994/07/30 Y.Murata */
	#define	PRO_MEM_RX_REJECT			DISABLE			/* メモリ受信拒絶機能 '94,09,06 By N.S. */
	#define	PRO_POCKET_BELL				DISABLE			/* ポケベル呼び出し機能 1994/09/30 Eguchi*/
	#define	PRO_DRAM_BACKUP				ENABLE			/* ＤＲＡＭバックアップ 1994/10/04 Y.Murata*/
	#define	PRO_OPTIONAL_SPEED			DISABLE			/* 任意短縮番号オペレーション 1995/02/13 T.Nose */
	#define	PRO_OP_SPPED_4_FIGURE		DISABLE			/* 任意短縮番号４桁化 2002/02/12 By M.Maeda */
	#define	PRO_TSI_RELAY_COM			DISABLE			/* FAXﾎﾞｰﾄﾞのTSIにより中々継受信をうける 1995/02/14 Y.Suzuki */
	#define	PRO_PIN_ACCESS				DISABLE			/* ＰＩＮ機能 1995/06/22 M.Tachibana */
	#define	PRO_SPEED_EX				DISABLE			/* 新短縮ハンドシェーク 1996/01/23 By t.yamaguchi */
#if defined (KEISATSU) /* 警察FAX 05/05/12 石橋正和 */
	#define	PRO_CLOSED_NETWORK			DISABLE			/* 閉域通信 1995/12/03 Eguchi */
#else
	#define	PRO_CLOSED_NETWORK			ENABLE			/* 閉域通信 1995/12/03 Eguchi */
#endif
	#define	PRO_SOFT_CODEC				DISABLE			/* ﾒﾓﾘ送信ｿﾌﾄｺｰﾃﾞｯｸ使用 96/1/11 Y.S */
	#define	PRO_SPD_MODE				DISABLE			/* モード変更時の短縮ハンドシェーク 1996/06/17 By t.yamaguchi */
	#define	PRO_CLASS1_EXT_FUNC			DISABLE			/* クラス１拡張機能 1999/06/10 K.Kawata */
	#define	PRO_PC_PRINT				DISABLE			/* ＤＰＲＡＭ経由のＰＣプリント機能 1996/07/02 */
	#define	PRO_DPRAM					DISABLE			/* ＤＰＲＡＭインタフェース By J.Miyazaki 1996/07/26 */
	#define	PRO_MULTI_LINE				DISABLE			/* ＤＰＲＡＭ経由の２回線仕様 */
	#define	PRO_ROTATE					DISABLE			/* ＤＰＲＡＭ経由の回転受信 */
	#define	PRO_CIPHER					DISABLE			/* アリロー By Y.Suzuki 1997/05/21 *//* ３ By O.Kimoto 1997/09/11 *//* 有効にします By O.Kimoto 1998/04/08 */
	#define	PRO_RELAYED_REPORT			ENABLE			/* 中継配信不達通知機能 1995/02/13 Y.Suzuki *//* ２ By O.Kimoto 1997/09/11 */
	#define	PRO_LIST_TX_WITH_IMG		ENABLE			/* 画像付きリスト送信機能（不達通知用） by H.Kubo 1998/12/16 */ /* enabled 1998/12/21 */
	#define PRO_G4						DISABLE			/* G4 By O.Kimoto 1997/07/22 */
	#define	PRO_INTERNET_FAX			DISABLE			/* インターネットＦＡＸ By S.Kawasaki 1996/0702 */
	#define	PRO_EXT_DMAC				DISABLE			/* 外付けＤＭＡＣ */
	#define	PRO_COPY_FAX_MODE			DISABLE			/* コピー／ＦＡＸ切り替え */
	#define	PRO_SECURITY_RX				ENABLE			/* セキュリティ受信 */
	#define	PRO_OPERATION_PROTECT		ENABLE			/* オペレーションプロテクト */
	#define	PRO_CONTINUOUS_POLLING		DISABLE			/* 連続ポーリング機能 *//* HINOKI無し By O.Kimoto 1998/12/02 */
	#define	PRO_FBS						DISABLE			/* フラットベッドスキャナ */
	#define	PRO_F_CODE					ENABLE			/* Ｆコード通信 1996/12/20	By T.Yamaguchi */
	#define PRO_FCODE_RELAY				ENABLE			/* Ｆコード中継配信機能 1998/08/21 By H.Hirao *//* ENABLE By H.Fujimura 1998/09/29 */
	#define PRO_FCODE_RELAYED_REPORT	DISABLE			/* Ｆコード中継配信不達通知 1998/08/21 By H.Hirao */
	#define PRO_FCODE_DELAYED_RELAY		DISABLE			/* Ｆコード時刻指定中継配信機能 1998/10/31 By S.Wang */
	#define	PRO_CONT_KEY_INPUT			DISABLE			/* 連続キー入力（コピーモード時の倍率変更）by K.Watanabe 97/02/25 */
	#define	PRO_COMMANDFILE_SRAM		DISABLE			/* コマンドファイルをＳＲＡＭに置く */
	#define PRO_CLASS1_VIA_DPRAM		DISABLE			/* 1997/03/13  By T.Yamaguchi */
	#define	PRO_AUTO_RX_SWITCH			ENABLE			/** 自動受信キーのあり／なし by K.Watanabe 1997/03/22 */
	#define PRO_LOW_TONER_PRINT			PRINT_FREE		/* Low Toner発生後、100枚だけプリントする仕様 By O.Kimoto 1996/12/26 */
	#define	PRO_PRIORITY_CASSETTE		DISABLE			/* 記録紙選択でカセット優先 by O.Kimoto 1996/12/26 *//*  By O.Kimoto 1997/04/14 */
	#define	PRO_TX_MOTOR_REVERSE		DISABLE			/* 読み取りモータ回転方向の論理 by M.Kotani 1997/06/27 */
	#define PRO_DOC_IN					ENABLE			/* ＡＤＦに原稿がセットされた時の原稿繰り込み T.Nose 1997/08/21 */
	#define PRO_SEPERATE_24V			DISABLE			/* スキャナー・プリンターの２４Ｖ制御が別々 T.Nose 1997/08/21 */
	#define PRO_JAM_OPR					ENABLE			/* ジャムリカバーオペレーション有無 T.Nose 1997/10/21 */
#if defined (KEISATSU) /* 警察FAX 05/04/28 石橋正和 */
	#define PRO_LINENUMBER				TWICE_LINE		/* 標準収容回線数 By O.Kimoto 1997/11/01 */
#else
	#define PRO_LINENUMBER				SINGLE_LINE		/* 標準収容回線数 By O.Kimoto 1997/11/01 */
#endif

	#define PRO_DEPART_NEW_LIST			ENABLE			/* 部門管理リスト用（簡易料金管理リスト） By O.Kimoto 1997/11/29 *//* ENABLE By H.Fujimura 1998/11/17 */

	#define PRO_JBIG					ENABLE			/* JBIG対応 by T.Soneoka 1997/12/09 */
	#define PRO_MANUAL_CASSETTE			DISABLE			/* 手差しプリント機能 by O.Kimoto 1998/01/05 */
	#define PRO_VOICE_RECOGNITION		DISABLE			/* 音声認識 1998/01/17  By T.Yamaguchi */
	#define PRO_REMOTE_RX				DISABLE			/* リモート受信 1998/01/17  By T.Yamaguchi */
	#define PRO_UPPER_COVER				DISABLE			/* ＰＯＰＬＡＲ＿Ｌ／ＨのＡＤＦガイド付きカバーのことです。 By O.Kimoto 1998/01/17 */
	#define PRO_ADF_AUTO_CASSETTE		DISABLE			/* ポプラＢ ＡＤＦコピー時の自動カセット選択 By S.Fukui 1998/01/23 */
	#define PRO_EXT_ROM					DISABLE			/* ポプラＢ 拡張ＲＯＭの使用あり By Y.Suzuki 1998/03/02 */
	#define PRO_DIALUP_INTERNET_FAX		DISABLE			/* ﾀﾞｲｱﾙｱｯﾌﾟ型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define PRO_LAN_INTERNET_FAX		DISABLE			/* LAN型ｲﾝﾀｰﾈｯﾄFAX　by Y.Tanimoto 1998/03/10 */
	#define	PRO_DIAL_NAME_DISP			ENABLE			/* ワンタッチ・短縮番号入力時の相手先名表示 by K.Watanabe 1998/03/11 */
	#define PRO_SALUTATION				DISABLE			/* ＳｔａｎｄＡｌｏｎｅ型サリュテーション用 By O.Kimoto 1998/03/20 */
	#define	PRO_NEW_DIAL_OPR			ENABLE			/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/03/27 *//* ENABLE By H.Fujimura 1998/10/09 */
	#define PRO_RDS_FLASH_ROM_WRITE		ENABLE			/** リモート診断でのフラッシュＲＯＭ書込み 1998/03/31  By T.Yamaguchi */
	#define PRO_ONHOOK_RX_SWITCH		DISABLE			/* オンフック受信ON/OFF切替えの有無(For L400)  98/04/01  Add By T.Fukumoto */
	#define PRO_SCAN_1000mm				DISABLE			/* 読み取り可能原稿長を１ｍにする By Y.Suzuki 1998/04/01 */
	#define PRO_JOURNAL_PRINT_TIME		DISABLE			/* 通信管理記録にプリント時間をのせる By M.Tachibana 1998/04/14 */
	#define PRO_CED_DETECT				DISABLE			/* ＣＥＤ検出 By M.Tachibana 1998/04/14 */
	#define	PRO_NEW_DIAL_OPR2			ENABLE			/* ダイヤル番号入力の新オペレーション by K.Watanabe 1998/04/23 *//* ENABLE By H.Fujimura 1998/10/09 */
	#define	PRO_MINOLTA_TEST_FUNC		DISABLE			/* ﾐﾉﾙﾀﾌﾟﾘﾝﾀ(8PPM)ﾃｽﾄﾓｰﾄﾞ 1998/05/09 Y.Murata */
	#define	PRO_FIXED_REDUCTION			DISABLE			/* 固定縮小率 by K.Watanabe 1998/05/13 */
	#define	PRO_DRAM_SIZE				DRAM_2M			/* 標準DRAM By Y.Suzuki 1998/05/15 */
	#define PRO_MULTI_TTI				DISABLE			/* マルチ発信元（特ＲＯＭ） By O.Kimoto 1998/05/25 */
	#define PRO_SPEED_DIAL_ADDITION		DISABLE			/* 短縮200件対応(特ROM) By M.Tachibana 1998/06/02 */
	#define PRO_NAME_RECALL				ENABLE			/* 文字入力時に登録済み名前を呼び出す H.Yoshikawa 1998/06/09 */
	#define PRO_KEY_MACRO				DISABLE			/* キーマクロ H.Yoshikawa 1998/06/09 */
	#define PRO_RX_DOC_TRANSFER			ENABLE			/* 受信原稿の転送 H.Yoshikawa 1998/06/09 */
	#define PRO_DATE_SET_RXDOC_CHK		DISABLE			/* 受信原稿に日時を付ける 1998/06/11 Y.Murata */
	#define PRO_EXT_SETTING_STATTUS 	ENABLE			/* SYS_SettingStatusの配列を増やす 1998/06/15 H.Yoshikawa */
	#define PRO_EX_CLASS1				DISABLE			/* 拡張ＲＯＭ対応CLASS1 S.Fukui Jun 19,1998 */
	#define PRO_OKI						DISABLE			/* ＯＫＩ仕様 By T.Fukumoto 98/07/03 */
	#define PRO_DRUM_PRT_CNT			DISABLE			/* ドラム11000枚でプリントをやめる By Y.Suzuki 1998/07/06 */
	#define PRO_RTC_IO_LOW_READ			ENABLE			/* RTCへのWrite時にIO_BIT_RTC_IOをLowにする H.Yoshikawa 1998/07/10 */
	#define	PRO_SGP_TEST_ROM			DISABLE			/* シンガポール市場調査ＲＯＭ 1998/07/16 Y.Murata */
	#define PRO_SH2_INTERNAL_DMAC		COM_CODEC_DMA	/* SH2 内蔵DMA by H.Kubo 1998/07/22 */
	#define PRO_EXT_P_ONETOUCH			ENABLE			/* SAKAKI/HINOKI用拡張版プログラムワンタッチ 1998/08/04 H.Yoshikawa *//* とりあえず By O.Kimoto 1998/09/07 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_PITNEYBOWES				DISABLE			/* Pitney Bowes仕様（読取原稿幅表現の変更、解像度表現の変更、サービスモードの初期値ON等) By S.Fukui Aug.25,1998 */
	#define PRO_DTC_INT_SYSTEM			ENABLE			/* 割り込み要因DTCを汎用的に使用できる PRO_EXT_DMACがDISABLEのみ有効 1998/08/31 H.Yoshikawa */
	#define PRO_DTC_INT_TYPE			DTC_INT_HINOKI	/*DTC_INT_OTHER*/		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	#define PRO_EXT_INT_TYPE			EXT_INT_NONE	/* 外部割り込み要因を識別する 1998/08/31 H.Yoshikawa */
	#define PRO_SH_PA15MD_CK			DISABLE			/* PA15/CK端子をクロック出力(CK)にする 1998/08/31 H.Yoshikawa */
	#define PRO_CPU_VERSION				SH7043_A		/* ＰＯＰＬＡＲシリーズとＳＡＫＡＫＩ／ＨＩＮＯＫＩを区別する By O.Kimoto 1998/09/04 */
	#define PRO_STOP_MODE_CLEAR			ENABLE			/*『停止』キー押下でモード等を初期値にする 1998/09/17 H.Yoshikawa *//* ENABLE By H.Fujimura 1998/11/16 */
	#define PRO_MODEM_AREA_BUS_WIDTH	BUS_WIDTH_8BIT	/* Ｒ２８８Ｆモデムのレジスタ領域の空間のＣＰＵバス幅の設定 By H.Hirao 1998/09/19 */
	#define PRO_RTC_INTERNAL_IO			ENABLE			/* RTCのI/OがCPU内蔵ﾎﾟｰﾄか外部IOか By O.Kimoto 1998/09/22 */
	#define PRO_MEKA_VOLUME				ENABLE			/* SAKAKI/HINOKIはロータリーボリュームです。By O.Kimoto 1998/09/22 */
	#define PRO_RS_INTERNAL				ENABLE			/* SH704X内蔵のシリアル有効／無効 By O.Kimoto 1998/09/25 */
	#define PRO_IMAGE_PROCESSOR			IMAGE_PROCESSOR_LC82103	/* 画処理ＩＣの設定  1998/09/28 by T.Soneoka */
	#define PRO_FCODE_KIND_DISPLAY 		ENABLE			/* Change DISABLE to ENABLE by O.Kimoto 1999/01/11 */			/* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
	#define PRO_CLEAR_SRAM_AND_DRAM		DISABLE			/* ＳＲＡＭ、ＤＲＡＭクリア（特ＲＯＭ）By H.Fujimura 1998/10/08 */
	#define PRO_FORCE_FINE_RX_SWITCH 	DISABLE  		/* 強制FINE受信スイッチ by H.Kubo 1998/10/08 */
	#define PRO_PROHIBIT_V29_TX_SWITCH	DISABLE			/* V29 送信禁止スイッチ by H.Kubo 1998/10/08 */
	#define PRO_QUICK_TX_TEST			DISABLE 		/* クイック送信テスト 1998/10/09 Y.Murata */
	#define PRO_RING_10_COUNT			ENABLE			/* JPN着信ベル回数の最大値を１０回にする 1998/10/12 H.Yoshikawa *//* ENABLE By H.Fujimura 1998/10/14 */
	#define PRO_ALLRAMCLR_WO_MCP		ENABLE			/* ＡｌｌＲＡＭＣｌｅａｒ([機能]+[＊]+[３]）の際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 *//* RDC200200635 By O.Kimoto 2003/02/14 */
	#define PRO_GEAR_BACK_LASH			DISABLE			/* ＡＤＦにピックアップローラーがある場合はENABLE 1998/11/02 H.Yoshikawa */
	#define PRO_SCN_CLUTCH				ENABLE			/* スキャナクラッチ有り by H.Hirao 1998/11/19 */
	#define	PRO_NEW_DIALMARK_OPR		ENABLE			/* ダイヤル記号入力の新オペレーション By H.Fujimura 1998/12/04 */
	#define PRO_TX_MINIMUM_SCAN_LINE_TIME	TIME10		/* 機器の送信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 changed by H.Hirao 1999/02/16 */
	#define PRO_RX_MINIMUM_SCAN_LINE_TIME	TIME10_2	/* 機器の受信可能な１ライン最小電送時間 by H.Hirao 1998/12/05 */
	#define PRO_RESULT_REPORT_TX		ENABLE			/* 結果通知配信機能 By O.Kimoto 1998/12/10 */
	#define PRO_CSDR_ITEM				ENABLE			/* ＣＳＤＲの各項目について対応／非対応 By O.Kimoto 1998/12/15 */
	#define	PRO_DISPLAY_TEL_TO_IDLE		ENABLE			/* 【CSDR-No.9/11】電話機使用中でも待機画面を表示する By H.Fujimura 1998/12/17 */
	#define	PRO_DISPLAY_STOP_KEY_OPR	ENABLE			/* ストップキー押下時の表示を待機画面にする By H.Fujimura 1999/01/18 */
	#define PRO_PREHEAT					ENABLE			/* 寒冷地対策 プリヒート T.Nose 1999/01/21 DISABLE -> ENABLE by H.Hirao 1999/02/09 */
	#define	PRO_IMADOKO					DISABLE			/* NTTﾄﾞｺﾓ ｲﾏﾄﾞｺｻｰﾋﾞｽ対策 By Y.Suzuki 1999/01/21*/
	#define	PRO_RX_3M_OVER				ENABLE			/* 受信３ｍオーバチェック  1999/02/02 by T.Soneoka */
	#define	PRO_TTI_TYPE				TTI_MML_TYPE	/* OKI 仕様 TTI 対応。 by H.Kubo 1119/02/17 */
	#define PRO_FAX_AND_1COPY			DISABLE			/* メモリ送信時に１枚コピーする　(簡易版Copy&Fax　SAKAKIで対応) 1999/02/17 H.Yoshikawa */
	#define PRO_MULTI_T30_MONITOR		ENABLE			/* マルチＴ３０モニタ By H.Fujimura 1999/04/07 */
	#define PRO_PRINTER_GA_MD9803		DISABLE			/* プリンタＧ／Ａ ＭＤ９８０３を使用する 1999/05/21 by T.Soneoka */
	#define	PRO_DIAL_LIST_GROUP			DISABLE			/* ワンタッチ・短縮リストにグループ番号を追加 by K.Watanabe 1999/05/24 */
	#define	PRO_ANK_TO_KANJI			DISABLE			/* ２行ＬＣＤ漢字化対応(L500 NTT仕様用) by K.Watanabe 1999/06/15 */
	#define	PRO_EXT_SEC_RX				DISABLE			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
	#define PRO_NEW_TX_CONF				ENABLE			/* 新送信証フォーマット By K.Kawata 2000/2/3 *//* RDC200000302 By O.Kimoto 2000/08/01 */
	#define	PRO_FAN_TEST				DISABLE			/* FAN騒音対策用特ROM　By M.Tachibana 2000/02/14 */
	#define PRO_DIAL_PULSE_TASK			ENABLE			/* パルスダイヤルを優先順位の高いタスクにする。naganoからの移植 SAKAKI誤ダイヤル 2000/10/17 H.Yoshikawa DISABLE->ENABLE 2000/11/24 by T.Soneoka*/
	#define PRO_ENERGY_SAVE				ENABLE			/* 省エネ 待機中PC_24V_OFF, 通信CODEC画処理LSIへのCLOCK停止 2001/11/22 T.Takagi */
	#define PRO_RED_SCAN				ENABLE			/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	#define PRO_NEW_JIG					ENABLE			/* NEW JIG 2002/06/03 T.Takagi */
	#define PRO_ENERGY_SAVE_PPF			DISABLE			/* 省エネ 待機中PC_24V_OFF, CODECへのCLOCK停止、YAWARA PPFから移植 By Y.Suzuki 2002/06/07 */
	#define PRO_CLEAR_FIRST_LAST		DISABLE			/* ファーストクリアとラストクリア By H.Fujimura 2002/07/11 */
#if defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */
	#define PRO_DIALIN_SW				DISABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
#else
	#define PRO_DIALIN_SW				ENABLE			/* ダイヤルインＳＷ By H.Fujimura 2002/07/11 */
#endif
	#define PRO_DISPLAY_DRUM_TONER		DISABLE			/* ドラムとトナーの組み合わせエラー表示 By H.Fujimura 2002/07/11 */
	#define PRO_DISPLAY_SUM_CHECK		DISABLE			/* サムチェック表示 By H.Fujimura 2002/07/11 */
	#define PRO_DUMMY_WORDING			ENABLE			/* ダミーワーディング使用 By H.Fujimura 2002/07/11 */
	#define PRO_FORVAL_LCR1				DISABLE			/* 00500サービス対応 By H.Fujimura 2002/07/11 */
	#define PRO_COM_RESULT				DISABLE			/* 通信結果表示対応 By M.Maeda 2002/08/07 */
	#define PRO_DISASTER_PREVENTION_FAX	DISABLE			/* 防災FAX対応 by Y.Kano 2004/08/19 */
	#define PRO_ECO_MODE				DISABLE			/* 省エネモード By M.Maeda 2002/09/06 */
	#define PRO_FANLOCK_DETECT_TIME 	DISABLE			/* 機内FANｴﾗｰ対策　200ms-->400msBy Y.Suzuki 2002/09/26 */

#if (1)		/* 紙センサーオペレーションを無くします。by Y.Kano 2004/12/25 */
	#define PRO_PAPER_AD_SENSOR_INIT	DISABLE			/* 紙センサーの初期化 */
#else
	#define PRO_PAPER_AD_SENSOR_INIT	ENABLE			/* 紙センサーの初期化 Y.Tanaka 2004/10/07 */
#endif

 #if defined(JPN)
  #if defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */
	#define	PRO_DIALIN					DISABLE			/* ダイヤルイン */
  #else
	#define	PRO_DIALIN					ENABLE			/* ダイヤルイン */
  #endif
	#define	PRO_NCU_TYPE				HINOKI_TYPE		/* NCU/ｶﾌﾟﾗｰTyep */
	#define	PRO_CLASS1					DISABLE			/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM				DISABLE			/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_JIS_CODE				ENABLE			/* 漢字ＣＧＲＯＭ対応 */
	#define PRO_SERVICE_FUNC			ENABLE			/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_NUMBER_DISPLAY			ENABLE			/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_NUMBER_DISPLAY_WARP		ENABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL		CALLER_ID_V23	/* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_CL1_TELFAX_LAN			DISABLE			/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 */
	#define PRO_NEW_JATE				ENABLE			/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */
	#define	PRO_MESSAGE_KANJI_INPUT		ENABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
 #else
	#define	PRO_DIALIN					DISABLE			/* ダイヤルイン */
	#define	PRO_NCU_TYPE				ANZU_GBR_TYPE
	#define	PRO_CLASS1					DISABLE			/* クラス１　1996/01/22 Eguchi *//* ＲＯＭ溢れのため、一時的に無効にする。 By O.Kimoto 1997/09/08 */
	#define	PRO_CLASS1_ECM				DISABLE			/* クラス１ECM 通信 by H.Kubo1998/03/06 */
	#define	PRO_JIS_CODE				DISABLE 		/* 漢字ＣＧＲＯＭ対応 by H.Hirao 1999/02/02 */
	#define PRO_SERVICE_FUNC			ENABLE			/* サービスファンクション有無 By O.Kimoto 1997/10/11 */
	#define PRO_NUMBER_DISPLAY			DISABLE			/* ナンバーディスプレイ H.Yoshikawa 1998/06/09 *//* ENABLE By H.Fujimura 1998/09/30 */
	#define PRO_NUMBER_DISPLAY_WARP		DISABLE			/* ＮＤワープＯＮ／ＯＦＦ By H.Fujimura 1999/01/07 */
	#define PRO_CALLER_ID_PROTOCOL		CALLER_ID_DISABLE	/* ナンバーディスプレイ(Caller-ID) の通信方法 by H.Kubo 1998/08/12 */
	#define PRO_CL1_TELFAX_LAN			DISABLE 		/* TEL/FAX,ANS/FAX,ダイヤルイン,F網,SALUTATION 対応 CLASS1新仕様 By S.Fukui June 19,1998 DISABLE -> ENABLE by H.Hirao 1999/02/10 */
	#define PRO_NEW_JATE				DISABLE			/* ＪＡＴＥ新規格対応 By O.Kimoto 1998/09/04 */ /* ＪＰＮ以外は必要ないのでDISABLEにしました by H.Hirao 1999/04/29 */
	#define	PRO_MESSAGE_KANJI_INPUT		DISABLE			/* カバーページメッセージ漢字入力 By H.Fujimura 1998/12/16 */
 #endif

 #if defined(JPNNTT)
	#define PRO_VOICE_ANSWER			ENABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_NORING_TEL1_DETACHABLE	ENABLE			/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto *//* Add By O.Kimoto 2002/09/27 */
	#define	PRO_NOT_AUTO_RX_DISP		ENABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_BT_DET_WHILE_RBT		DISABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_COMM_RESULT_REVIEW		ENABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_MEMORY_SW_EDIT_GUARD	ENABLE			/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2			DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
	#define PRO_KANJI2_TYPE				KANJI2_27		/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
	#define	PRO_KEY_SOUND_OPR			DISABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			DISABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			DISABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				DISABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_PBX_TONE_DETECT			DISABLE			/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/05/14 By Y.Tanaka */
	#define PRO_REVERSE_PRINT			DISABLE			/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
 #else
	#define PRO_VOICE_ANSWER			DISABLE			/* 音声応答 1998/01/17  By T.Yamaguchi */
	#define PRO_NORING_TEL1_DETACHABLE	DISABLE			/* 無鳴動着信のＴＥＬ１切り離し(For L400)  98/04/01 Add By T.Fukumoto */
	#define	PRO_NOT_AUTO_RX_DISP		DISABLE			/* 自動受信不可能表示 by K.Watanabe 1998/06/08 */
	#define PRO_BT_DET_WHILE_RBT		ENABLE			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	#define PRO_COMM_RESULT_REVIEW		DISABLE			/* 通信結果表示(印刷機能無し仕様) by J.Kishida 2002/09/12 */
	#define PRO_MEMORY_SW_EDIT_GUARD	DISABLE			/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	#define PRO_COMMON_SAKAKI2			DISABLE			/* サカキ２の変更に合わせる By M.Maeda 2002/10/15 */
	#define PRO_KANJI2_TYPE				KANJI2_30		/* 第２水準漢字２６文字対応 1998/09/17 H.Yoshikawa */ /* 第２水準漢字３０文字対応 by Y.Kano 2005/01/13 */
  #if defined(JPN)
	#define PRO_REMOTE_DIAL_TRANSFER	ENABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
  #else
	#define PRO_REMOTE_DIAL_TRANSFER	DISABLE			/* リモート受信５５版 2003/01/29 T.Takagi REMOTE_RX_FUNC */
  #endif
  #if defined (KEISATSU) /* 警察FAX 05/05/07 石橋正和 */
	#define	PRO_PREFIX_KEY				DISABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
  #else
	#define	PRO_PREFIX_KEY				ENABLE			/* プレフィックスキー by K.Watanabe 2004/10/12 */
  #endif
	#define	PRO_KEY_SOUND_OPR			ENABLE			/* キー音(音色/音量)設定オペレーション by K.Watanabe 2004/10/12 */
	#define	PRO_JOURNAL_VER_UP			ENABLE			/* ジャーナル仕様追加(A4分割、送受信別印刷、降順プリント) by K.Watanabe 2004/10/12 */
	#define	PRO_DAILY_REPORT			ENABLE			/* ジャーナル日報対応 by K.Watanabe 2004/10/12 */
	#define	PRO_UI_WORDING				ENABLE			/* UIワーディング変更 by K.Watanabe 2004/10/12 */
	#define PRO_PBX_TONE_DETECT			ENABLE			/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/05/14 By Y.Tanaka */
	#define PRO_REVERSE_PRINT			ENABLE			/* 受信原稿逆順プリント By M.Tachibana 1998/05/15 */
 #endif

	#define	PRO_DISPLAY_PRN_INITIALIZE	DISABLE		/* プリンターの初期化時の表示を使用する */
#endif



#if (PRO_CPU == SH7043)
	#define	BYTE			char
	#define	UBYTE			unsigned char
	#define	WORD			short
	#define	UWORD			unsigned short
	#define	DWORD			long
	#define	UDWORD			unsigned long
	#define CONST			const

 #if defined (HINOKI) || defined (SAKAKI) || defined (HINOKI2) || defined (SATSUKI2)  || defined(STOCKHM2) /* SAKAKI is added by H.Kubo 1999/01/25 */ /* HINOKI2 2001/11/13 T.Takagi */
	#define EXTERN			extern
	#define	BOOL			char			/* 1Byte:TRUE or FALSE */
		#define	WORD_MAX	(WORD)32767
		#define	WORD_MIN	(WORD)(-32768)
 #endif

 #if defined (HINOKI) || defined (HINOKI2) || defined (SATSUKI2)  || defined(STOCKHM2) /* HINOKI2 2001/11/13 T.Takagi */
#include "\src\atlanta\define\product2.h"	/* ＨＩＮＯＫＩ特ＲＯＭ専用 By O.Kimoto 1999/04/01 */
 #endif

#endif

/*	\src\memsw\define\mems_pro.hにfarの記述あり By Y.Suzuki 1996/10/18	*/

#define far

#endif

