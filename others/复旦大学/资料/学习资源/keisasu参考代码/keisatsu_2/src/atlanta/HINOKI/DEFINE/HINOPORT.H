/*--------------------------------------------------------------------*/
/* プロジェクト : POPLAR_H											  */
/* ファイル名	: POPHport.h										  */
/* 作成者		: 野瀬敏弘											  */
/* 日  付		: 1996/10/15										  */
/* 概  要		: I/Oポート定義										  */
/* 修正履歴		: 機種別に移動  By M.Kotani 97/06/11				  */
/*                POPLAR_Bよりコピー  By O.kimoto 1997/06/13		  */
/*                POPLAR_Hよりコピーしただけです。  By O.kimoto 1998/09/07		  */
/*                Jason/Evaから、eva_io.h/lc82103.hをコピーしてきました。 by O.Kimoto 1998/09/19 */
/*--------------------------------------------------------------------*/
#ifndef HINOPORT_H
	#define	HINOPORT_H	1

#include "\src\atlanta\define\product.h"

/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/inc/lc82103.h
 *	Create:	Thu Nov 27 16:10:44 1997	by	ishiyama
 *	Description:
 *		三洋電機 画像処理 LSI 制御
 */

/*
 *	Image Processor Registers
 */
/* -------------------<ＬＣ８２１０３仕様>--------------------- */

/* reg[0] */
extern volatile UBYTE	Sreg0;
#define	SREG_0	&Sreg0
#define IP_FLG	(0x01 << 7)		/* 処理フラグ */
#define IP_IFLG	(0x01 << 6)		/* 内部処理フラグ */

#define IP_PM	(0x03 << 4)		/* 処理モード */
#define IP_PM_WHITE	(0x00 << 4)			/* 白補正データ作成 */
#define IP_PM_BLACK	(0x01 << 4)			/* 黒データ作成 */
#define IP_PM_2CHI	(0x02 << 4)			/* 補正処理、二値化処理 */
#define IP_PM_GAMMA	(0x03 << 4)			/* ガンマ直線補間 */

#define	IP_BM	(0x03 << 2)		/* 二値化処理モード */
#define IP_BM_2CHI	(0x00 << 2)	/* 単純二値化処理 */
#define IP_BM_GRAY	(0x01 << 2)	/* 誤差拡散 */
#define IP_BM_FILTER	(0x02 << 2)	/* 像域分離フィルタ制御 */
#define IP_BM_SELECTOR	(0x03 << 2)	/* 像域分離セレクタ制御 */

#define IP_ATB	(0x01 << 1)		/* 二値化処理方法選択 */
#define IP_WD	(0x01 << 0)		/* 内蔵メモリ初期化 */

/* reg[1] */
extern volatile UBYTE	Sreg1;
#define SREG_1	&Sreg1
#define IP_CDV	(0x07 << 5)		/* 入力クロック分周 */

#define IP_DC	(0x03 << 3)		/* ディジタルクランプ */
#define IP_DC_OFF	(0x00 << 3)			/* DC OFF */
#define IP_DC_ONE	(0x01 << 3)			/* 一点クランプモード */
#define IP_DC_EVENODD	(0x02 << 3)		/* Even/Odd クランプモード */

#define IP_SUBM	(0x03 << 1)		/* 副操作方向縮小率 */
#define IP_SUBM_NON	(0x00 << 1)	/* 無変換 */
#define IP_SUBM_1_2	(0x01 << 1)	/* 1/2 */
#define IP_SUBM_1_3	(0x02 << 1)	/* 1/3 */
#define IP_SUBM_1_4	(0x03 << 1)	/* 1/4 */

#define IP_SAMP	(0x01 << 0)		/* A/D サンプリング、LINE 信号選択 */

/* reg[2] */
extern volatile UBYTE	Sreg2;
#define SREG_2	&Sreg2

#define IP_BFMX	(0x03 << 6)		/* 単純二値化用 X 方向強調フィルタモード */
#define IP_BFMX_NON	(0x00 << 6)	/* 強調なし */
#define IP_BFMX_X1	(0x01 << 6)	/* 強調x1 */
#define IP_BFMX_X2	(0x02 << 6)	/* 強調x2 */
#define IP_BFMX_X4	(0x03 << 6)	/* 強調x4 */

#define IP_BFMY	(0x03 << 4)		/* 単純二値化用 Y 方向強調フィルタモード */
#define IP_BFMY_NON	(0x00 << 4)	/* 強調なし */
#define IP_BFMY_X1	(0x01 << 4)	/* 強調x1 */
#define IP_BFMY_X2	(0x02 << 4)	/* 強調x2 */
#define IP_BFMY_X4	(0x03 << 4)	/* 強調x4 */

#define IP_HFMX	(0x03 << 2)		/* 中間調処理用 X 方向強調フィルタモード */
#define IP_HFMX_NON	(0x00 << 2)	/* 強調なし */
#define IP_HFMX_X1	(0x01 << 2)	/* 強調x1 */
#define IP_HFMX_X2	(0x02 << 2)	/* 強調x2 */
#define IP_HFMX_X4	(0x03 << 2)	/* 強調x4 */

#define IP_HFMY	(0x03 << 0)		/* 中間調処理用 Y 方向強調フィルタモード */
#define IP_HFMY_NON	(0x00 << 0)	/* 強調なし */
#define IP_HFMY_X1	(0x01 << 0)	/* 強調x1 */
#define IP_HFMY_X2	(0x02 << 0)	/* 強調x2 */
#define IP_HFMY_X4	(0x03 << 0)	/* 強調x4 */

/* reg[3] */
extern volatile UBYTE	Sreg3;
#define SREG_3	&Sreg3
#define IP_OPN	(0x03 << 6)		/* ピン機能設定 */
#define IP_PDM	(0x01 << 5)		/* パラレル出力データ選択 */
#define IP_MSBF	(0x01 << 4)		/* パラレル出力順 */
#define IP_ERRM	(0x01 << 3)		/* 誤差拡散モード */
#define IP_HFMS	(0x01 << 2)		/* 中間調処理用フィルタ選択 */

#define IP_MFMX	(0x03 << 0)		/* 多値解像度用 X 方向強調フィルタモード */
#define IP_MFMX_NON	(0x00 << 0)			/* 強調無し */
#define IP_MFMX_X1	(0x01 << 0)			/* 強調x１ */
#define IP_MFMX_X2	(0x02 << 0)			/* 強調x２ */
#define IP_MFMX_X4	(0x03 << 0)			/* 強調x３ */

/* reg[4] */
extern volatile UBYTE	Sreg4;
#define	SREG_4	&Sreg4
#define IP_RES	(0x07 << 5)		/* 主走査方向多値解像度変換 */
#define IP_RES_NON	(0x00 << 5)			/* 強調無し */
#define IP_RES_1_2	(0x01 << 5)			/* 1/2 変換 */
#define IP_RES_2_3	(0x02 << 5)			/* 2/3 変換 */
#define IP_RES_3_2	(0x03 << 5)			/* 3/2 変換 */
#define IP_RES_2_1	(0x04 << 5)			/* 2/1 変換 */
#define IP_TRGEG	(0x01 << 4)	/* TRIG 信号判定基準 */
#define IP_TRGM	(0x01 << 3)		/* トリガタイミング */
#define IP_MST	(0x01 << 2)		/* マスタモード,スレーブモード*/
#define IP_SLVM	(0x01 << 1)		/* スレーブモード選択 */
#define IP_ADDIR	(0x01 << 0)	/* A/D 信号二値化 */

/* reg[5] */
extern volatile UBYTE	Sreg5;
#define SREG_5	&Sreg5
#define IP_SPE	(0x01 << 7)		/* センサ信号制御 */
#define IP_ST	(0x03 << 5)		/* センサタイプ */
#define IP_BID	(0x01 << 4)		/* 出力データ極性 */
#define IP_ALW	(0x01 << 3)		/* 出力全白判定 */
#define IP_ALB	(0x01 << 2)		/* 出力全黒判定 */
#define IP_DSTC	(0x03 << 0)		/* ゴミ判定 */

/* reg[6] */
extern volatile UBYTE	Sreg6;
#define SREG_6	&Sreg6
#define IP_CP	(0xff << 0)		/* クランプ位置 */

/* reg[7] */
extern volatile UBYTE	Sreg7;
#define SREG_7	&Sreg7
#define IP_MAXD	(0xff << 0)		/* 入力信号最大値 */

/* reg[8] */
extern volatile UBYTE	Sreg8;
#define SREG_8	&Sreg8
#define IP_MIND	(0xff << 0)		/* 入力信号最小値 */

/* reg[9] */
extern volatile UBYTE	Sreg9;
#define SREG_9	&Sreg9
#define IP_BCD	(0xff << 0)		/* 黒基準データ */

/* reg[0x0a] */
extern volatile UBYTE	SregA;
#define SREG_A	&SregA
#define IP_RSTB	(0x01 << 7)		/* ソフトウェアリセット */
#define IP_SDSEL	(0x01 << 6)	/* メモリ選択 */
#define IP_TH	(0x3f << 0)		/* 二値化域値 */

/* reg[0x0b] */
extern volatile UBYTE	SregB;
#define	SREG_B	&SregB
#define IP_WCHG	(0x01 << 7)		/* 白画素変換 */
#define IP_STHM	(0x01 << 6)		/* 副操作方向二値縮小モード変換 */
#define IP_NRC	(0x01 << 5)		/* 主走査方向二値縮小しない */
#define IP_RM	(0x03 << 3)		/* 主操作法二値縮小モード選択 */
#define IP_RM_KEEPBLACK	(0x00 << 3)	/* 黒細線保持 */
#define IP_RM_KEEPWHITE	(0x01 << 3)	/* 白細線保持 */
#define IP_RM_PURE	(0x02 << 3)	/* 単純間引き */
#define IP_SP	(0x07 << 0)		/* A/D サンプリングポイント調整 */

/* reg[0x0c] */
extern volatile UBYTE	SregC;
#define SREG_C	&SregC
#define IP_RC	(0xff << 0)		/* 縮小率 */

/* reg[0x0d] */
extern volatile UBYTE	SregD;
#define SREG_D	&SregD
#define IP_AON	(0x01 << 7)		/* 網点検出処理 */
#define IP_XSL	(0x3f << 0)		/* 像域分離パラメータ */

/* reg[0x0e] */
extern volatile UBYTE	SregE;
#define	SREG_E	&SregE
#define IP_SDW	(0x01 << 6)		/* 文字判定領域 */
#define IP_ET	(0x3f << 0)		/* 網点スライスレベル */

/* reg[0x0f] */
extern volatile UBYTE	SregF;
#define SREG_F	&SregF
#define IP_MTE	(0x01 << 7)		/* モータパルス制御 */
#define IP_MTT	(0x03 << 5)		/* モータパルスタイプ */
#define IP_EP	(0x1f << 0)		/* 網点エッジペア */

/* reg[0x10] */
extern volatile UBYTE	Sreg10;
#define	SREG_10	&Sreg10
#define IP_WVAL	(0x07 << 4)		/* 重みマトリックス */
#define IP_FF	(0x0f << 0)		/* "FF"値カウント */

/* reg[0x11] */
extern volatile UBYTE	Sreg11;
#define SREG_11	&Sreg11
#define IP_TMPR	(0x01 << 7)		/* D/A 設定値制御 */
#define IP_DALA	(0x3f << 0)		/* センサ信号期間 A/D ローレファレンス用 D/A 値 */
#define IP_DALA_MIN	0x0b		/* 最小値（初期設定） */

/* reg[0x12] */
extern volatile UBYTE	Sreg12;
#define SREG_12	&Sreg12
#define IP_DALT	(0x3f << 0)		/* 温度信号期間 A/D ローリファレンス用 D/A 値 */
#define IP_DALT_MIN	0x00		/* 最小値（初期設定） */

/* reg[0x13] */
extern volatile UBYTE	Sreg13;
#define SREG_13	&Sreg13
#define IP_DAHA	(0x3f << 0)		/* センサ信号期間 A/D ハイリファレンス用 D/A 値 */
#define IP_DAHA_MAX	0x35		/* 最大値（初期設定） */

/* reg[0x14] */
extern volatile UBYTE	Sreg14;
#define	SREG_14	&Sreg14
#define IP_DAHT	(0x3f << 0)		/* 温度信号期間 A/D ハイリファレンス用 D/A 値 */
#define IP_DAHT_MAX	0x3f		/* 最大値（初期設定） */

/* reg[0x15] */
extern volatile UBYTE	Sreg15;
#define	SREG_15	&Sreg15
#define IP_TPH	(0xff << 0)		/* ヘッド温度データ */

/* reg[0x16] */
extern volatile UBYTE	Sreg16;
#define	SREG_16	&Sreg16
#define IP_PPM	(0xff << 0)		/* 汎用 I/O ポート制御 */

/* reg[0x17] */
extern volatile UBYTE	Sreg17;
#define SREG_17	&Sreg17
#define IP_PPDR &Sreg17

#define IP_PPD	(0xff << 0)		/* 汎用 I/O ポート */

#if (0)
** /* ＬＡＭＰとクラッチは下の方にありますのでこれらは消します。 By O.Kimoto 1998/09/19 */
** #define IO_BIT_LAMP		(0x01 << 0)		/* Lamp出力 */
** #define IO_BIT_CLUTCH	(0x01 << 1)		/* クラッチ出力 */
#define IO_BIT_CONT24	(0x01 << 6)		/* NCU +24V制御信号 */
#define IO_BIT_STAMP	(0x01 << 5)		/* 済みスタンプ  1998/07/07 by T.Soneoka */
#endif

#if (0) /* 未使用です 1998/11/16 by T.Soneoka */
**	#define IO_BIT_CONTI	(0x01 << 2)		/* CIS電流制御 */
**	#define IO_BIT_RXMOTOR	(0x01 << 3)		/* Lotus Rx Motor 1:Enable 0:Disable(for Kurumi)*/
**	#define IO_BIT_BATT2	(0x01 << 4)		/* 電池残量検出開始信号 */
#endif

/* reg[0x18] */
extern volatile UBYTE	Sreg18;
#define SREG_18	&Sreg18
#define IP_LT	(0xff << 0)		/* 蓄積時間 */

/* reg[0x19] */
extern volatile UBYTE	Sreg19;
#define SREG_19	&Sreg19
#define IP_SES	(0xff << 0)		/* 補正有効期間スタート */

/* reg[0x1a] */
extern volatile UBYTE	Sreg1A;
#define SREG_1A	&Sreg1A
#define IP_SEL	(0xff << 0)		/* 補正有効期間長 */

/* reg[0x1b] */
extern volatile UBYTE	Sreg1B;
#define SREG_1B	&Sreg1B
#define IP_WM	(0x1f << 3)		/* 白マスク幅 */
#define IP_PES_H	(0x03 << 0)	/* 処理有効期間スタート */

/* reg[0x1c] */
extern volatile UBYTE	Sreg1C;
#define SREG_1C	&Sreg1C
#define IP_PES_L	(0xff << 0)	/* 処理有効期間スタート */

/* reg[0x1d] */
extern volatile UBYTE	Sreg1D;
#define SREG_1D	&Sreg1D
#define IP_PEL	(0xff << 0)		/* 処理有効期間長 */


/* -------------------<ＬＣ８２１０３３仕様>--------------------- */
/* by Y,Kano 2003/11/27 */

#if defined(HINOKI2) || defined(HINOKI3) || defined(KEISATSU)	/* LC821033仕様対応 Y.Kano 2003/11/27 */
/* reg[0] */
#define IP_FLG_LC33			(0x01 << 7)		/* 処理フラグ 										*/
#define IP_IFLG_LC33		(0x01 << 6)		/* 内部処理フラグ 									*/

#define IP_PM_LC33			(0x03 << 4)		/* 処理モード 										*/
#define IP_PM_WHITE_LC33	(0x00 << 4)		/* 白補正データ作成 								*/
#define IP_PM_BLACK_LC33	(0x01 << 4)		/* 黒データ作成 									*/
#define IP_PM_2CHI_LC33		(0x02 << 4)		/* 補正処理、二値化処理 							*/
#define IP_PM_GAMMA_LC33	(0x03 << 4)		/* ガンマ直線補間 									*/

#define	IP_BM_LC33			(0x01 << 2)		/* 二値化処理モード 								*/
#define IP_BM_2CHI_LC33		(0x00 << 2)		/* 単純二値化処理 									*/
#define IP_BM_GRAY_LC33		(0x01 << 2)		/* 誤差拡散 										*/

#define IP_ATB_LC33			(0x01 << 1)		/* 二値化処理方法選択 								*/
#define IP_WD_LC33			 0x01			/* 内蔵メモリ初期化 								*/


/* reg[1] */
#define IP_CDV_LC33			(0x07 << 5)		/* 入力クロック分周 								*/

#define IP_DC_LC33			(0x03 << 3)		/* ディジタルクランプ 								*/
#define IP_DC_OFF_LC33		(0x00 << 3)		/* DC OFF 											*/
#define IP_DC_ONE_LC33		(0x01 << 3)		/* 一点クランプモード 								*/
#define IP_DC_EVENODD_LC33	(0x02 << 3)		/* Even/Odd クランプモード 							*/

#define IP_SUBM_LC33		(0x03 << 1)		/* 副操作方向縮小率 								*/
#define IP_SUBM_NON_LC33	(0x00 << 1)		/* 無変換 											*/
#define IP_SUBM_1_2_LC33	(0x01 << 1)		/* 1/2 												*/
#define IP_SUBM_1_3_LC33	(0x02 << 1)		/* 1/3 												*/
#define IP_SUBM_1_4_LC33	(0x03 << 1)		/* 1/4 												*/

#define IP_SAMP_LC33		0x01			/* A/D サンプリング、LINE 信号選択 					*/


/* reg[2] */
#define IP_DCM_LC33			(0x01 << 5)		/* ディジタルクランプ平均画素数 					*/
#define IP_DCM_2_LC33		(0x00 << 5)		/* レジスタＤＣＰより２画素平均 					*/
#define IP_DCM_4_LC33		(0x01 << 5)		/* レジスタＤＣＰより４画素平均 					*/

#define IP_FEG_LC33			(0x07 << 2)		/* 強調処理の強調度設定 							*/
#define IP_FEG_0_LC33		(0x00 << 2)		/* 強調フィルタ1、×0.5 							*/
#define IP_FEG_1_LC33		(0x01 << 2)		/* 強調フィルタ1or2、×1.0 							*/
#define IP_FEG_2_LC33		(0x02 << 2)		/* 強調フィルタ1or2、×2.0 							*/
#define IP_FEG_3_LC33		(0x03 << 2)		/* 強調フィルタ1、×3.0 							*/
#define IP_FEG_4_LC33		(0x04 << 2)		/* 強調フィルタ1、×4.0 							*/

#define	IP_FM_LC33			(0x03)			/* 2次元フィルタ選択 								*/
#define	IP_FM_0_LC33		(0x00)			/* スルー 											*/
#define	IP_FM_1_LC33		(0x01)			/* 強調フィルタ1(単純2値化処理) 					*/
#define	IP_FM_2_LC33		(0x02)			/* 強調フィルタ2(中間調処理) 						*/
#define	IP_FM_3_LC33		(0x03)			/* 平滑 											*/


/* reg[3] */
#define IP_OPN_LC33			(0x03 << 6)		/* ピン機能設定 									*/
#define IP_PDM_LC33			(0x01 << 5)		/* パラレル出力データ選択 							*/
#define IP_MSBF_LC33		(0x01 << 4)		/* パラレル出力順 									*/

#define IP_WRNG_LC33		0x0f			/* 重み付け範囲設定 								*/


/* reg[4] */
#define IP_ST_H_LC33		(0x01 << 7)		/* センサタイプ 最上位ビット 						*/
#define IP_TRGEG_LC33		(0x01 << 4)		/* TRIG 信号判定基準 								*/
#define IP_TRGM_LC33		(0x01 << 3)		/* トリガタイミング 								*/
#define IP_MST_LC33			(0x01 << 2)		/* マスタモード,スレーブモード						*/
#define IP_SLVM_LC33		(0x01 << 1)		/* スレーブモード選択 								*/
#define IP_ADDIR_LC33		0x01			/* A/D 信号二値化 									*/


/* reg[5] */
#define IP_SPE_LC33			(0x01 << 7)		/* センサ信号制御 									*/
#define IP_ST_L_LC33		(0x03 << 5)		/* センサタイプ 									*/
#define IP_BID_LC33			(0x01 << 4)		/* 出力データ極性 									*/
#define IP_ALW_LC33			(0x01 << 3)		/* 出力全白判定 									*/
#define IP_ALB_LC33			(0x01 << 2)		/* 出力全黒判定 									*/
#define IP_DSTC_LC33	 	0x03			/* ゴミ判定 										*/


/* reg[6] */
#define IP_CP_LC33			0xff			/* クランプ位置 									*/


/* reg[7] */
#define IP_MAXD_LC33		0xff			/* 入力信号最大値 									*/


/* reg[8] */
#define IP_MIND_LC33		0xff			/* 入力信号最小値 									*/


/* reg[9] */
#define IP_MCPS_LC33		(0x01 << 7)		/* 内部モニター選択 								*/


/* reg[0x0a] */
#define IP_RSTB_LC33		(0x01 << 7)		/* ソフトウェアリセット 							*/
#define IP_TH_LC33			0x3f			/* 二値化域値 										*/


/* reg[0x0b] */
#define IP_WCHG_LC33		(0x01 << 7)		/* 白画素変換 */
#define IP_STHM_LC33		(0x01 << 6)		/* 副操作方向二値縮小モード変換 					*/
#define IP_RC_H_LC33		(0x01 << 5)		/* 縮小率 最上位ビット 								*/
#define IP_SP_LC33			0x0f			/* A/D サンプリングポイント調整 					*/


/* reg[0x0c] */
#define IP_RC_LC33			0xff			/* 縮小率 											*/


/* reg[0x0d] */
#define IP_THLM_LC33		0x3f			/* 背景追従閾値 									*/


/* reg[0x0e] */
#define IP_SGAM_LC33		(0x01 << 7)		/* ガンマ補正位置 			    */
#define IP_SGAM_0_LC33		(0x00 << 7)		/* 二次元フィルタ処理後に、ガンマ補正を行う 		*/
#define IP_SGAM_1_LC33		(0x01 << 7)		/* 二次元フィルタ処理前に、ガンマ補正を行う 		*/

#define IP_THDV_LC33		(0x03 << 4)		/* 背景追従閾値　閾値選択 	      */
#define IP_THDV_1_2_LC33	(0x00 << 4)		/* 追従閾値＝輝度差×１／２＋ＭＩＮ値 				*/
#define IP_THDV_1_4_LC33	(0x01 << 4)		/* 追従閾値＝輝度差×１／４＋ＭＩＮ値 				*/
#define IP_THDV_1_8_LC33	(0x02 << 4)		/* 追従閾値＝輝度差×１／８＋ＭＩＮ値 				*/
#define IP_THDV_NON_LC33	(0x03 << 4)		/* 禁止				　　  */


/* reg[0x0f] */
#define IP_MTE_LC33			(0x01 << 7)		/* モータパルス制御 */
#define IP_MTT_LC33			(0x03 << 5)		/* モータパルスタイプ */

#define IP_MFLG_LC33		(0x01 << 3)		/* 歪み補正メモリ内部リフレッシュ処理フラグ 		*/
#define IP_MFLG_ACT_LC33	(0x00 << 3)		/* 実行					    						*/
#define IP_MFLG_STP_LC33	(0x01 << 3)		/* 停止					    						*/

#define IP_IMFLG_LC33		(0x01 << 2)		/* 歪み補正メモリ内部リフレッシュ内部処理フラグ 	*/
#define IP_IMFLG_ACT_LC33	(0x00 << 2)		/* 実行中（内部リフレッシュモード）             	*/
#define IP_IMFLG_STP_LC33	(0x01 << 2)		/* 停止中（外部リフレッシュモード）	        		*/

#define IP_MSEL_LC33		0x01			/* 歪み補正メモリ選択 								*/
#define IP_MSEL_WHITE_LC33	0x00			/* 白歪み補正メモリ   								*/
#define IP_MSEL_BLACK_LC33	0x01			/* 黒歪み補正メモリ   								*/


/* reg[0x10] */
#define IP_WVAL_LC33		(0x07 << 4)		/* 重みマトリックス 								*/
#define IP_FF_LC33			0x0f			/* "FF"値カウント 									*/


/* reg[0x11] */
#define IP_LIMW_LC33		0x3f			/* 白リミッタ設定 									*/


/* reg[0x12] */
#define IP_LIMB_LC33		0x3f			/* 黒リミッタ設定 									*/


/* reg[0x13] */
#define IP_TMPR_LC33		(0x01 << 7)		/* D/A 設定値制御 									*/
#define IP_DAHA_LC33		0x3f			/* センサ信号期間 A/D ハイリファレンス用 D/A 値 	*/
#define IP_DAHA_MAX_LC33	0x35			/* 最大値（初期設定） 								*/


/* reg[0x14] */
#define IP_DAHT_LC33		0x3f			/* 温度信号期間 A/D ハイリファレンス用 D/A 値 		*/
#define IP_DAHT_MAX_LC33	0x3f			/* 最大値（初期設定） 								*/


/* reg[0x15] */
#define IP_TPH_LC33			0xff			/* ヘッド温度データ 								*/


/* reg[0x16] */
#define IP_PPM_LC33			0xff			/* 汎用 I/O ポート制御 								*/


/* reg[0x17] */
#define IP_PPD_LC33			0xff			/* 汎用 I/O ポート 									*/


/* reg[0x18] */
#define IP_LT_LC33			0xff			/* 蓄積時間 										*/


/* reg[0x19] */
#define IP_SES_LC33			0xff			/* 補正有効期間スタート 							*/


/* reg[0x1a] */
#define IP_SEL_LC33			0xff			/* 補正有効期間長 									*/


/* reg[0x1b] */
#define IP_WM_LC33			(0x1f << 3)		/* 白マスク幅 										*/
#define IP_PES_H_LC33		0x03			/* 処理有効期間スタート 							*/


/* reg[0x1c] */
#define IP_PES_L_LC33		0xff			/* 処理有効期間スタート 							*/


/* reg[0x1d] */
#define IP_PEL_LC33			0xff			/* 処理有効期間長 									*/

#endif	/* End of defined(HINOKI2) */


#define	DAHRH	5						/* 5V */
#define DAHRL	0						/* 0V */
#define DALRH	5						/* 5V */
#define DALRL	0						/* 0V */


/*----------------------------------------------------------------*/
/*
**	@(#)$Id: HINOPORT.H,v 1.8 2005/09/16 10:57:40 xiax Exp $
**	File Name:	f:\prj\eva\src\inc\eva_io.h
**	Create:	1997/12/05	By Masahiro,IIDA
**	Description: GateArray I/O Address Map
**	Change: 19xx/xx/xx	
*/

/*
 *	割込みステータスレジスタ
 */
extern volatile UWORD	ga_int_sta;			/* 0x00c00000 */
#define	GA_INT_STA			&ga_int_sta			
#define IO_BIT_CI_INT	(0x0001 << 0)	/**  CI割込み */
#if defined (KEISATSU) /* 警察FAX 05/06/30 石橋正和 */
	#define IO_BIT_CI_EX_INT	(0x0001 << 1)	/* 拡張回線(警電回線)CI割込み  */
#else
	#define IO_BIT_CTS_INT		(0x0001 << 1)	/**  RS232C CTS状態変化割込み */
#endif
#define IO_BIT_PBRDY	(0x0001 << 2)	/* Printer Buffer Ready */
#define IO_BIT_XTOP		(0x0001 << 3)	/**  プリンタ･VSYNC割込み */
#define IO_BIT_XSTWR	(0x0001	<< 4)	/**  プリンタ･ステータス割込み */
#define IO_BIT_PGEND	(0x0001 << 5)	/**  プリンタ･データ１ページ転送終了割込み */
#define IO_BIT_PREND	(0x0001 << 6)	/**  プリント終了割込み */
#define	IO_BTT_SINT		(0x0001 << 8)	/* SP Int */

/*
 *	割込み受領レジスタ
 */
extern volatile UWORD	ga_int_rec;			/* 0x00c00002 */
#define	GA_INT_REC			&ga_int_rec			

/*
 *	割込み有効／無効レジスタ
 */
extern volatile UWORD	ga_int_mask;		/* 0x00c00004 */
extern UWORD GA_IntMaskStatus;				/* 設定状態保存用 */
#define	GA_INT_MASK			&ga_int_mask		
#define	IMASK_XCI		(0x0001 << 0)
#if defined (KEISATSU) /* 警察FAX 05/06/30 石橋正和 */
	#define	IMASK_XCIEX		(0x0001 << 1)
#else
	#define	IMASK_XCTS		(0x0001 << 1)
#endif
#define	IMASK_PBRDY		(0x0001 << 2)
#define	IMASK_XTOP		(0x0001 << 3)
#define	IMASK_XSTWR		(0x0001 << 4)
#define	IMASK_PGEND		(0x0001 << 5)
#define	IMASK_PREND		(0x0001 << 6)
#define	IMASK_INTSP		(0x0001 << 8)

/*
 *	ソフトリセット
 */
extern volatile UWORD	ga_rst;				/* 0x00c00006 */
#define	GA_RST				&ga_rst				

/*
 *	DMA 許可／禁止, DMA 選択
 */
extern volatile UWORD	ga_dmar;			/* 0x00C00008 */
#define	GA_DMAR				&ga_dmar
#define GA_DMA_ENABLE	0x0001			/* DMA Enable */
#define GA_DMA_SCANNER	0x0002			/* Scanner DMA */
#define GA_DMA_PRINTER	0x0000			/* Printer DMA */

/*
 *	スキャナデータ読出し要求/プリントデータ書込み要求
 */
extern volatile UWORD	ga_sp_req;			/* 0x00C0000A */
#define	GA_SP_REQ			&ga_sp_req			

#define SREQ			0x0001			/* スキャナデータ読み出し要求 */
#define PREQ			0x0002			/* プリントデータ読み出し要求 */

/*
 *	トリガーイネーブル,イメージバッファイネーブル,イメージバッファ本数,
 *	イメージバッファ先頭アドレス
 */
extern volatile UWORD	ga_mwr;			/* 0x00C0000C */
extern UWORD GA_MWR_Status;				/* 設定状態保存用 */
#define	GA_MWR				&ga_mwr				
#define MWR_LINE_5MS	(0x0001 << 0) /* TRIG 周期 0:2.5ms 1:5ms */
#define MWR_INTCYC_5MS	(0x0001 << 1) /* SPINT 周期 0:2.5ms 1:5ms */
#define MWR_IBEN		(0x0001 << 2) /* Image Buffer Enable */
#define MWR_IBN			(0x000F << 3) /* Image Buffer 本数 */
#define MWR_IBADD		(0x007F << 7) /* Image Buffer Address(S-RAM の相対アドレス) */
#define MWR_IBB4		(0x0001 << 14) /* Image Buffer Size 0:A4 1:B4 */

#define MWR_IBN_VALUE	(0x000F << 3) 	/* 16本：Image Buffer本数設定値 */

/*
 *	スキャナスタート
 */
extern volatile UWORD	ga_sstart;			/* 0x00C0000E */
#define	GA_SSTART			&ga_sstart			

/*
 *	プリントスタート,スムージングイネーブル
 */
extern volatile UWORD	ga_pstart;			/* 0x00C00010 */
extern UWORD	GaPstartStatus;			/* 設定値保存用 RAM */
#define	GA_PSTART			&ga_pstart			

#define GA_PRINT_START	0x0001
#define GA_PRINT_SMTH	0x0002			/* bad do not use */
#define GA_PRINT_SMTH2	0x0004			/* new smoothing */

/*
 *	書込み中アドレス
 */
extern volatile UWORD	ga_mrd;				/* 0x00C00012 */
#define	GA_MRD				&ga_mrd				

/*
 *	スキャナデータ読出し
 */
extern volatile UWORD	ga_scand;			/* 0x00C00014 */
#define	GA_SCAND			&ga_scand			

/*
 *	プリントデータ書込み
 */
extern volatile UWORD	ga_prid;			/* 0x00C00016 */
#define	GA_PRID				&ga_prid

/*
 *	Test Mode
 */
extern volatile UWORD	ga_tstm;		/* 0x00C00018 */
#define GA_TSTM	&ga_tstm

/*
 *	Printer Mode
 */
extern volatile UWORD	ga_pmd;			/* 0x00C0001A */
#define GA_PMD	&ga_pmd

#define PMD_PAGE_PRINTER	0x0000		/* Page Printer */
#define PMD_THERMAL_PRINTER	0x0001		/* Thermal Head Printer */

/*
 *	送信モータ
 */
extern volatile UWORD	ga_tmr0;		/* 0x00C00100 */
extern UWORD	GaTmr0Status;			/* 設定値保存用 RAM */
#define	GA_TMR0				&ga_tmr0			

#define TMSPED200	0x0000				/* 1-2相:200PPS	2相:100PPS */
#define TMSPED400	0x0001				/* 1-2相:400PPS 2相:200PPS */
#define TMSPED800	0x0002				/* 1-2相 800PPS 2相:400PPS */
#define TMSPED1600	0x0003				/* 1-2相 1600PPS 2相:800PPS */
#define TMSPED3200	0x0004				/* 1-2相 3200PPS 2相:1600PPS */
#define TMSPED6400	0x0005				/* 1-2相 6400PPS 2相:3200PPS */

#define TMSTEP1		(0x0000 << 3)		/* 1-2相:1Step 2相:禁止 */
#define TMSTEP2		(0x0001 << 3)		/* 1-2相:2Step 2相:1Step */
#define TMSTEP4		(0x0002 << 3)		/* 1-2相:4Step 2相:2Step */
#define TMSTEP8		(0x0003 << 3)		/* 1-2相:8Step 2相:4Step */
#define TMSTEP16	(0x0004 << 3)		/* 1-2相:16Step 2相:8Step */
#define TMSTEP32	(0x0005 << 3)		/* 1-2相:32Step 2相:16Step */
#define TMSTEP64	(0x0006 << 3)		/* 1-2相:64Step 2相:32Step */

#define	TMPOUT	(0x0001 << 6)			/* 連続回転 0:ストップ 1:スタート*/
#define	TMSTART	(0x0001 << 7)			/* 回転スタート 1:スタート*/
#define TMASYNC	(0x0000 << 8)			/* 回転スタート(SP_INT同期) 0:非同期 1:同期 */
#define TMSYNC	(0x0001 << 8)			/* 回転スタート(SP_INT同期) 0:非同期 1:同期 */
#define TMCW	(0x0000 << 9)			/* 回転方向 0:正転 1:逆転 */
#define TMCCW	(0x0001 << 9)			/* 回転方向 0:正転 1:逆転 */
#define TMEXCT	(0x0001 << 10)			/* 励磁制御 0:非励磁 1:励磁 */
#define TMSEL_1_2	(0x0000 << 11)		/* 相選択 0:1-2相 1:2相 */
#define TMSEL_2	(0x0001 << 11)			/* 相選択 0:1-2相 1:2相 */
#define HC		(0x0001 << 12)			/* 自動電流断制御 0:未使用 1:使用 */


extern volatile UWORD	ga_tmr1;		/* 0x00C00102 */
extern UWORD	GaTmr1Status;			/* 設定値保存用 RAM */
#define	GA_TMR1				&ga_tmr1

#define MICRO		(0x0001 << 0)		/* マイクロステップ制御 0:未使用 1:使用 */
#define FLAT		(0x0001 << 1)		/* フラットトルク制御 0:未使用 1:使用 */
#define SSEX		(0x0001 << 2)		/* 特殊励磁制御 0:未使用 1:使用 */
#define SS			(0x0007 << 3)		/* 特殊励磁制御時間設定 */
#define IV_DAI		(0x0000 << 6)		/* 手動電流制御時の電流値 大 */
#define IV_CHU		(0x0001 << 6)		/* 手動電流制御時の電流値 中 */
#define IV_SHOU		(0x0002 << 6)		/* 手動電流制御時の電流値 小 */
#define IV_ZERO		(0x0003 << 6)		/* 手動電流制御時の電流値 ０ */
#define MKIND_UNI	(0x0000 << 8)		/* モータ 0:ユニポーラ 1:バイポーラ */
#define MKIND_BI	(0x0001 << 8)		/* モータ 0:ユニポーラ 1:バイポーラ */

/*
 *	受信モータ
 */
extern volatile UWORD	ga_rmr;			/* 0x00C00104 */
extern UWORD	GaRmrStatus;			/* 設定値保存用 RAM */
#define	GA_RMR				&ga_rmr
#define RMSPED200	0x0000				/* 1-2相:200PPS	2相:100PPS */
#define RMSPED400	0x0001				/* 1-2相:400PPS 2相:200PPS */
#define RMSPED800	0x0002				/* 1-2相 800PPS 2相:400PPS */
#define RMSPED1600	0x0003				/* 1-2相 1600PPS 2相:800PPS */

#define RMSTEP1		(0x0000 << 3)		/* 1-2相:1Step 2相:禁止 */
#define RMSTEP2		(0x0001 << 3)		/* 1-2相:2Step 2相:1Step */
#define RMSTEP4		(0x0002 << 3)		/* 1-2相:4Step 2相:2Step */
#define RMSTEP8		(0x0003 << 3)		/* 1-2相:8Step 2相:4Step */

#define	RMPOUT	(0x0001 << 6)			/* 連続回転 0:ストップ 1:スタート*/
#define	RMSTART	(0x0001 << 7)			/* 回転スタート 1:スタート*/
#define RMASYNC	(0x0000 << 8)			/* 回転スタート(SP_INT同期) 0:非同期 1:同期 */
#define RMSYNC	(0x0001 << 8)			/* 回転スタート(SP_INT同期) 0:非同期 1:同期 */
#define RMCW	(0x0000 << 9)			/* 回転方向 0:正転 1:逆転 */
#define RMCCW	(0x0001 << 9)			/* 回転方向 0:正転 1:逆転 */
#define RMEXCT	(0x0001 << 10)			/* 励磁制御 0:非励磁 1:励磁 */
#define RMSEL_1_2	(0x0000 << 11)		/* 相選択 0:1-2相 1:2相 */
#define RMSEL_2	(0x0001 << 11)			/* 相選択 0:1-2相 1:2相 */

/*
 *	TPH etc.
 */
extern volatile UWORD	ga_tph_reg;			/* 0x00C00106 */
extern UWORD	GaTphStatus;			/* 設定値保存用 RAM */
#define	GA_TPH_REG			&ga_tph_reg

#define TPH_EN			(0x0001 << 0)	/* TPH コントロール回路 0:PagePrinter 1:Thermal */
#define TPH_SIZE_A4		(0x0000 << 1)	/* TPH Size 0:A4 1:B4 */
#define TPH_SIZE_B4		(0x0001 << 1)
#define TPH_STRSEL_2	(0x0000 << 2)	/* ストローブ信号分割数 0:2分割 1:4分割 */
#define TPH_STRSEL_4	(0x0001 << 2)
#define TPH_STRPOL_NEG	(0x0000 << 3)	/* ストローブ極性 0:負論理 1:正論理 */
#define TPH_STRPOL_POS	(0x0001 << 3)
#define TPH_DPOL_BLACK1	(0x0000 << 4)	/* データ極性 0:0=白,1=黒 1:0=黒,1=白 */
#define TPH_DPOL_BLACK0	(0x0001 << 4)
#define TPH_CKSEL_3_5	(0x0000 << 5)	/* 転送クロック 0:3.5MHz, 1:1.75MHz */
#define TPH_CKSEL_1_75	(0x0001 << 5)
#define TPH_DSIZE_A4	(0x0000 << 6)	/* データサイズ 0:A4 1:B4 */
#define TPH_DSIZE_B4	(0x0001 << 6)
#define TPH_MAINRC_OFF	(0x0000 << 7)	/* 主走査縮小 0:OFF 1:ON */
#define TPH_MAINRC_ON	(0x0001 << 7)
#define TPH_RC_SIMPLE	(0x0000 << 8)	/* 縮小補正 0:単純間引き */
#define TPH_RC_OR		(0x0001 << 8)	/* 縮小補正 1:OR 処理 */
#define TPH_RC_KEEP		(0x0002 << 8)	/* 縮小補正 2:画素保存 */
#define TPH_WMSK_OFF	(0x0000 << 10)	/* 両端白マスク 0:OFF 1:ON */
#define TPH_WMSK_ON		(0x0001 << 10)
#define TPH_WMSKW		(0x0007 << 11)	/* 両端マスク幅 2-8(mm) 0,1設定不可 */
#define TPH_ASYNC		(0x0000 << 14)	/* 印可パルスSP_INT 同期 0:非同期 1:同期 */
#define TPH_SYNC		(0x0001 << 14)
#define TPH_LATPOL_POS	(0x0000 << 15)	/* Latch 極性 0:正論理,1:負論理 */
#define TPH_LATPOL_NEG	(0x0001 << 15)


/*
 *	レフトマージン(for Thermal Head)
 */
extern volatile UWORD	ga_tphlmrg;			/* 0x00C00108 */
#define	GA_TPHLMRG	&ga_tphlmrg

/*
 *	TPH ストローブ etc.
 */
extern volatile UWORD	ga_swr;				/* 0x00C0010A */
#define	GA_SWR				&ga_swr				
#define SWR_LATEN	0x0001				/* Latch Enable ハード的に０になる */
#define SWR_PRTEN	0x0002				/* Strobe Pulse 出力 ハード的に０になる */
#define SWR_STREN	0x0004				/* Strobe Enabel 0:出力禁止 1:出力許可 */
#define SWR_SW		(0x00ff << 3)		/* Strobe Pulse 幅 */

/*
 *	ストローブ信号モニタ
 */
extern volatile UWORD	ga_strm;			/* 0x00C0010C */
#define	GA_STRM				&ga_strm
#define	STRM_STRMON	0x0001				/* ストローブモニタ 1:出力中 */
#define STRM_DTMON	0x0002				/* データ転送モニタ 1:転送中 */

/*
 *	記録紙幅設定,トナーセーブモード,データ極性,縮小制御,白マスク
 */
extern UWORD	GaPrtcStatus;			/* 設定値保存用 RAM */
extern volatile UWORD	ga_prtc;		/* 0x00C00200 */
#define	GA_PRTC				&ga_prtc

#define PRTC_TSAVE	(0x0001 << 0)		/* トナーセーブ 1:黒データの幅を TSSEL の設定値にする */
#define PRTC_TSSEL	(0x0001 << 1)		/* トナーセーブモード選択 0:3/4 1:1/2 */
#define PRTC_DPOLE	(0x0001 << 2)		/* データ極性 0:白=0,黒=1 1:白=1,黒=0*/
#define PRTC_WMASK	(0x0001 << 3)		/* 白マスク 1:WM3-0 の設定値で両端をマスク */
#define PRTC_WM		(0x000f << 4)		/* 両端マスク幅 0,1:禁止 2mm-15mm */
#define PRTC_SYNTH	(0x0001 << 8)		/* 仮想垂直同期信号割込み発生 */
#define PRTC_RSPC	(0x0001 << 9)		/* 記録紙幅 0:210mm 1:216mm */
#define PRTC_SUBRC	(0x0001 << 10)		/* 副走査縮小 0:Off 1:On */
#define PRTC_MAINRC	(0x0001 << 11)		/* 主走査縮小 0:Off 1:On */
#define PRTC_MODE	(0x0003 << 12)		/* プリントモード */
#define PRTC_MODE_X6	(0x0000 << 12)	/* 副走査6倍 */
#define PRTC_MODE_X3	(0x0001 << 12)	/* 副走査3倍 */
#define PRTC_MODE_X1_5	(0x0002 << 12)	/* 副走査1.5倍 */


/*
 *	プリンタリセット,コントローラ待機中,プリント動作開始,プリントモード
 */
extern volatile UWORD	ga_cmdr1;			/* 0x00C00202 */
#define	GA_CMDR1			&ga_cmdr1			

#define CMDR1_RESET	(0x0001 << 0)		/* エンジンのハードウェアリセット */
#define CMDR1_CPRDY	(0x0001 << 1)		/* コントローラが Ready になったことをエンジンに示す */
#define CMDR1_PRINT	(0x0001 << 2)		/* エンジンにプリント動作の開始または継続を指示 */

/*
 *	プリンタコマンドレジスタ
 *		1の補数をとってからライトすること
 */
extern volatile UWORD	ga_cmdr2;			/* 0x00C00204 */
#define	GA_CMDR2			&ga_cmdr2			

/* ステータス要求コマンド(SR) */
#define CMDR2_SR0	0x01				/* 基本ステータスを要求 */
#define CMDR2_SR1	0x02				/* オペレーターコール情報を要求 */
#define CMDR2_SR2	0x04				/* サービスマンコール情報を要求 */
#define CMDR2_SR3	0x07				/* ジャム箇所情報を要求 */
#define CMDR2_SR4	0x08				/* 再送枚数情報を要求 */
#define CMDR2_SR5	0x0b				/* 下給紙カセットの用紙サイズコードを要求 */
#define CMDR2_SR6	0x0d				/* MP トレイの用紙サイズコードを要求 */
#define CMDR2_SR7	0x0e				/* MP トレイの用紙長を要求 */
#define CMDR2_SR9	0x13				/* 排紙枚数情報を要求 */
#define CMDR2_SR10	0x15				/* 給紙部選択情報を要求 */
#define CMDR2_SR15	0x1f				/* トナー情報を要求 */
#define CMDR2_SR18	0x25				/* 給紙ユニット装着情報を要求 */
#define CMDR2_SR21	0x2a				/* 給紙ユニット内用紙情報を要求 */
#define CMDR2_SR30	0x3d				/* M/C F/W バージョン情報を要求 */
#define CMDR2_SR31	0x3e				/* バイアス調整情報を要求 */

/* 実行コマンド(EC) */
#define CMDR2_EC2	0x45				/* エンジンをポーズ状態（休止中）にする */
#define CMDR2_EC3	0x46				/* エンジンをポーズ状態から解除する */
#define CMDR2_EC6	0x4c				/* 下給紙カセットからの給紙を選択 */
#define CMDR2_EC7	0x4f				/* MP トレイからの給紙を選択 */
#define CMDR2_EC8	0x51				/* Reserved */
#define CMDR2_EC14	0x5d				/* ミスプリント・給紙ミス・サイズエラー解除およびクリーニング指示 */
#define CMDR2_EC17	0x62				/* クリーニング指示なしのミスプリント・給紙ミス・サイズエラー解除 */
#define CMDR2_EC21	0x6b				/* ファンモータ強制回転指示 */
#define CMDR2_EC22	0x6d				/* ファンモータ強制回転指示解除 */

/* 拡張実行コマンド(EEC) */
#define CMDR2_EEC12	0x98				/* 転写電流指示 */
#define CMDR2_EEC13	0x9b				/* 用紙長指示 */
#define CMDR2_EEC15	0x9e				/* バイアス調整指示 */
#define CMDR2_EEC16	0xa1				/* 解像度指示 */

/* 拡張通信コマンド(ECC) */
#define CMDR2_ECC31	0xfe				/* イニシャライズ・コマンド */


/*
 *	エンジン待機中、プリンタ動作可能、ステータス受信中
 */
extern volatile UWORD	ga_stsr1;			/* 0x00C00206 */
#define	GA_STSR1			&ga_stsr1			
#define STSR1_MASK	0x0007				/* 下位3ビットのみ有効,上位は不定 */

#define STSR1_EPRDY	(0x0001 << 0)		/* エンジンがコントローラと通信可能になったことを示す */
#define STSR1_PRRDY	(0x0001 << 1)		/* エンジンがプリント動作可能な状態にあることを示す */
#define STSR1_ETBSY	(0x0001 << 2)		/* エンジンが/STS 信号を用いてステータスをコントローラへ送っていることを示す */

/*
 *	プリンタステータスレジスタ
 *		1の補数を取り,上位8ビットは無視すること
 *		ステータスは、prt_drv.h 参照
 */
extern volatile UWORD	ga_stsr2;			/* 0x00C00208 */
#define	GA_STSR2			&ga_stsr2			
#define STSR2_MASK	0x00ff				/* 下位8ビットのみ有効,上位は不定 */

#define STSR2_ERROR	0x0080				/* コマンドエラー */
#define STSR2_ERROR_PARI	0x00c1		/* コマンドパリティエラー */
#define STSR2_ERROR_DEFINE	0x0080		/* コマンド未定義 */


/*
 *	先端余白設定(for Lazer Printer)
 */
extern volatile UWORD	ga_prs;				/* 0x00C0020A */
#define	GA_PRS				&ga_prs				

/*
 *	プリントライン数設定
 */
extern volatile UWORD	ga_print_end;		/* 0x00C0020C */
#define	GA_PRINT_END		&ga_print_end		

/*
 *	記録紙サイズ設定
 */
extern volatile UWORD	ga_page_end;		/* 0x00C0020E */
#define	GA_PAGE_END			&ga_page_end		

/*
 *	副操作縮小パターン
 */
extern volatile UWORD	ga_sub_rdc1;		/* 0x00C00210 */
extern volatile UWORD	ga_sub_rdc2;		/* 0x00C00212 */
#define	GA_SUB_RDC1			&ga_sub_rdc1		
#define	GA_SUB_RDC2			&ga_sub_rdc2		

/*
 *	主走査縮小パターン
 */
extern volatile UWORD	ga_line_rdc1;		/* 0x00C00214 */
extern volatile UWORD	ga_line_rdc2;		/* 0x00C00216 */
extern volatile UWORD	ga_line_rdc3;		/* 0x00C00218 */
extern volatile UWORD	ga_line_rdc4;		/* 0x00C0021A */
extern volatile UWORD	ga_line_rdc5;		/* 0x00C0021C */
extern volatile UWORD	ga_line_rdc6;		/* 0x00C0021E */
#define	GA_LINE_RDC1		&ga_line_rdc1		
#define	GA_LINE_RDC2		&ga_line_rdc2		
#define	GA_LINE_RDC3		&ga_line_rdc3		
#define	GA_LINE_RDC4		&ga_line_rdc4		
#define	GA_LINE_RDC5		&ga_line_rdc5		
#define	GA_LINE_RDC6		&ga_line_rdc6		

/*
 *	縮小時のレフトマージン
 */
extern volatile UWORD	ga_left_mrg;		/* 0x00C00220 */
#define	GA_LEFT_MRG			&ga_left_mrg		


/*
** GateArray出力ポート
*/
extern UWORD RelayPortStatus; /* maindata.cで定義 */

extern volatile UWORD	ga_pgadr;			/* 0x00C00302 */
#define	GA_PGADR			&ga_pgadr			
	#define IO_BIT_CML		0x0001		/**  ＣＭＬリレー		*/
	#define IO_BIT_S		0x0002		/**  Ｓリレー			*/
	#define IO_BIT_H		0x0004		/**  Ｈリレー			*/
	#define IO_BIT_L		0x0008		/**  Ｌリレー			*/
	#define IO_BIT_RI_GK	0x0010		/**  Groud Key			*/
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/28 */
	#define IO_BIT_HDST_OFF	0x0020		/**  ＡＴＴＡＣＨＴＥＬリレー	*/
#else /* !defined (KEISATSU) */
	#define IO_BIT_DP		0x0020		/**  ＤＰリレー			*/
#endif /* defined (KEISATSU) */
/* もしSOHが必要になった場合は復活させてください T.Nose         */
/*	#define IO_BIT_SOH_TCK	0x0040		@** ショートオンフック		*/
	#define	IO_BIT_ND_DATA	0x0040		/* 停電時ダイヤルインDATA	*//* T.Nose 1998/11/19 */
	#define IO_BIT_RXA_TONE	0x0080		/* AFE切り替え				*/
	#define IO_BIT_RXA_BZ	0x0100		/* スピーカ出力				*/
	#define IO_BIT_LAMP		0x0200		/* ランプ					*/
	#define IO_BIT_CLUTCH	0x0400		/* クラッチ					*/
	#define IO_BIT_CONT24	0x0800		/**  ＣＯＮＴ２４		*/
	#define IO_BIT_PC		0x1000		/**  ２４Ｖ				*/
	#define	IO_BIT_STAMP	0x2000		/* スタンプ					*/
	#define IO_BIT_SUBRESET 0x4000		/* サブリセット			 */ /* 2001/11/19 T.Takagi */
	#define	IO_BIT_SELMEL	0x8000		/* 保留メロディー切り替え	*/

/*
** GateArray入力ポート
*/
extern volatile UWORD	ga_pgbdr;			/* 0x00C00300 */
#define	GA_PGBDR			&ga_pgbdr			
 #if defined(HINOKI3) || defined(KEISATSU)
  #if defined(KEISATSU) /* 警察FAX 05/06/08 石橋正和 */
	#define IO_BIT_XOH_EX	0x0001		/* 拡張回線(警電回線)ＯＨ１検出 */
	#define IO_BIT_XDS2		0x0002		/**  Document Sensor2	*/
	#define IO_BIT_SHIREI	0x0004		/* 指令起動信号 */
  #endif
 #else
	#define IO_BIT_XPS1		0x0001		/**  記録紙検出センサー	*/
	#define IO_BIT_XPS2		0x0002		/**  記録紙ジャムセンサー */
	#define IO_BIT_XPB4		0x0004		/**  記録紙Ｂ４センサー */
 #endif
	#define IO_BIT_RY_BY	0x0008		/**  フラッシュステート */
#if (0)	/* 1998/10/18 ＴＸ／ＲＸを逆にします */
**	#define	IO_BIT_TXIL		0x0010		/* ＴＸインターロック		*/
**	#define	IO_BIT_TOPOP	0x0020		/* ＲＸインターロック		*/
#else
	#define	IO_BIT_TOPOP	0x0010		/* ＲＸインターロック		*/
	#define	IO_BIT_TXIL		0x0020		/* ＴＸインターロック		*/
#endif
	#define IO_BIT_XDS1		0x0040		/**  Document Sensor1	*/
#if defined (KEISATSU) /* 警察FAX 05/06/29 石橋正和 */
	#define IO_BIT_XCI_EX	0x0080		/* 拡張回線(警電回線)CI信号 */
#else
	#define IO_BIT_XDS2		0x0080		/**  Document Sensor2	*/
#endif
	#define	IO_BIT_XDB4		0x0100		/* Ｂ４センサ				*/
	#define IO_BIT_PGB9		0x0200		/* 画処理選択 1:LC821033 0:LC82103	*/
	#define	IO_BIT_XDA3		0x0200		/* Ａ３センサ				*/
	#define	IO_BIT_XCI		0x0400		/* CI信号				*/
	#define	IO_BIT_XDSE1_VC	0x0800		/**  極反検出１				*/
	#define	IO_BIT_XDSE2_LC	0x1000		/**  極反検出２				*/
	#define	IO_BIT_XOH1		0x2000		/**  ＯＨ１検出				*/
	#define	IO_BIT_XOH2		0x4000		/**  ＯＨ２検出				*/


/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/07
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD	SYS_LED1_PortStatus;
* DESCRIPTION:	 ＬＥＤ・ポ－ト1／ビット・アサイメント(WRITE)
************************************************************************/
#define MODE_NORMAL_LED		0x0001		/* 標準					*/
#define	MODE_FINE_LED		0x0002		/* 高画質				*/
#define DST_NORMAL_LED		0x0004		/* 普通					*/
#define DST_LIGHT_LED		0x0008		/* 薄く					*/
#define	MODE_SFINE_LED		0x0010		/* 超高画質				*/
#define	MODE_GRAY_LED		0x0020		/* 写真					*/
#define DST_DARK_LED		0x0040		/* 濃く					*/
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/09/15 */
#define RESERVATION_LED		0x0080		/* 会話予約				*/
#else
#define	STAMP_LED			0x0080		/* 済みスタンプ			*/
#endif		/* End of (defined (KEISATSU)) */
/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/07
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD	SYS_LED2_PortStatus;
* DESCRIPTION:	 ＬＥＤ・ポ－ト2／ビット・アサイメント(WRITE)
************************************************************************/
#define	MEMORY_TX_LED		0x0001		/* メモリ送信			*/
#if defined(HINOKI3) || defined(KEISATSU)
#define	ON_HOOK_LED			0x0002		/* フック／会話予約		*/
#endif
#define	MEMORY_RX_LED		0x0010		/* 代行受信				*/
#define	FAX_COM_LED			0x0020		/* 通信中				*/
#define	ALARM_LED			0x0040		/* アラーム				*/
#define	AUTO_RX_LED			0x0080		/* 自動受信				*/

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/07
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD	SYS_LED2_PortStatus;
* DESCRIPTION:	 ＬＥＤ・ポ－ト2／ビット・アサイメント(WRITE)
************************************************************************/
#if defined(HINOKI3) || defined(KEISATSU)
		/* HINOKI3ではフックキーのポートが変わりました。名前は一緒	*/
#else
#define	ON_HOOK_LED			0x0001		/* フック／会話予約		*/
#endif



/*
** 暫定 ＨＩＮＯＫＩのプリンタ部等環境が揃うまで定義しておきます
**  1998/09/30 by T.Soneoka
*/


/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/07
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD	SYS_InterruptPortStatus
* DESCRIPTION:	 割込みマスク・ポ－ト／ビット・アサイメント(WRITE)
************************************************************************/
#define	INT_MASK_PORT		0x00C203E0	/* アドレス					*/
#define IO_BIT_MASK70		0x0001		/* ＩＲＱ７０割込のマスク          　*/
#define IO_BIT_MASK71		0x0002		/* ＩＲＱ７１割込のマスク          　*/
#define IO_BIT_MASK72		0x0004		/* ＩＲＱ７２割込のマスク          　*/
#define IO_BIT_MASK73		0x0008		/* ＩＲＱ７３割込のマスク          　*/
#define IO_BIT_MASK74		0x0010		/* ＩＲＱ７４割込のマスク          　*/
#define IO_BIT_MASK75		0x0020		/* ＩＲＱ７５割込のマスク          　*/
#define IO_BIT_INTCLR70		(~0x0040)	/* ＩＲＱ７０割込要因フラグをクリア　*/
#define IO_BIT_INTCLR71		(~0x0080)	/* ＩＲＱ７１割込要因フラグをクリア　*/
#define IO_BIT_INTCLR72		(~0x0100)	/* ＩＲＱ７２割込要因フラグをクリア　*/
#define IO_BIT_INTCLR73		(~0x0200)	/* ＩＲＱ７３割込要因フラグをクリア　*/
#define IO_BIT_INTCLR74		(~0x0400)	/* ＩＲＱ７４割込要因フラグをクリア　*/
#define IO_BIT_INTCLR75		(~0x0800)	/* ＩＲＱ７５割込要因フラグをクリア　*/

#define IO_BIT_MASK76		0x0000		/* ＩＲＱ７６割込のマスク          　*/
#define IO_BIT_MASK77		0x0020		/* ＩＲＱ７７割込のマスク          　*/
#define IO_BIT_INTCLR76		0x0000		/* ＩＲＱ７６割込要因フラグをクリア　*/
#define IO_BIT_INTCLR77		(~0x0800)	/* ＩＲＱ７７割込要因フラグをクリア　*/

/*--------------------------------------------------------------------------*/
/*	ＭＤ９６０４	Ｉ／Ｏ		ＰＨＯＮＩＸ３用　プリンタコントロール部	*/
/*--------------------------------------------------------------------------*/

#define	PRN_MD9509_BASE_PORT	0x00C20701

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/05
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD PRN_Printer1PortData
* DESCRIPTION:	 プリンタ・ポート１(READ/WRITE)
************************************************************************/
#define	PRINTER1_PORT		0x00C20300	/* アドレス					*/
#define	PRN_P1_HS1			0x0001		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS2			0x0002		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS3			0x0004		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS4			0x0008		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS5			0x0010		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS6			0x0020		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS7			0x0040		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS8			0x0080		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS9			0x0100		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS10			0x0200		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS11			0x0400		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS12			0x0800		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS13			0x1000		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS14			0x2000		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS15			0x4000		/* HSYNC周期カウンタ設定値	*/
#define	PRN_P1_HS16			0x8000		/* HSYNC周期カウンタ設定値	*/

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/05
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD PRN_Printer2PortData
* DESCRIPTION:	 プリンタ・ポート２(READ/WRITE)
************************************************************************/
#define	PRINTER2_PORT		0x00C20310	/* アドレス					*/
#define	PRN_P2_HSDWR		0x0001		/* HSYNCディレイ中は"H"を出力	*/
#define	PRN_P2_HSDWRCLR		0x0002		/* D0をクリアするビット			*/
#define	PRN_P2_HSEN			0x0004		/* HSYNC有効					*/
#define	PRN_P2_HSDEN		0x0008		/* HSYNCディレイ機能有効		*/
#define	PRN_P2_PRCLKSEL		0x0010		/* HDCLK選択					*/
#define	PRN_P2_TSPWR		0x0020		/* トナーセーブパターンの書込み	*/
#define	PRN_P2_VOCKSEL		0x0040		/* LED HEAD解像度設定			*/
#define	PRN_P2_HDCKACT		0x0080		/* LED HEAD転送クロック論理設定	*/
#define	PRN_P2_TSP1			0x0100		/* トナーセーブパターンビット１	*/
#define	PRN_P2_TSP2			0x0200		/* トナーセーブパターンビット２	*/
#define	PRN_P2_TSP3			0x0400		/* トナーセーブパターンビット３	*/
#define	PRN_P2_TSP4			0x0800		/* トナーセーブパターンビット４	*/
#define	PRN_P2_TSP5			0x1000		/* トナーセーブパターンビット５	*/
#define	PRN_P2_TSP6			0x2000		/* トナーセーブパターンビット６	*/
#define	PRN_P2_TSP7			0x4000		/* トナーセーブパターンビット７	*/
#define	PRN_P2_TSP8			0x8000		/* トナーセーブパターンビット８	*/

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/05
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD PRN_Printer3PortData
* DESCRIPTION:	 プリンタ・ポート３(READ/WRITE)
************************************************************************/
#define	PRINTER3_PORT		0x00C20320	/* アドレス					*/
#define	PRN_P3_STBS1		0x0001		/* 正規ストローブ設定値			*/
#define	PRN_P3_STBS2		0x0002		/* 正規ストローブ設定値			*/
#define	PRN_P3_STBS3		0x0004		/* 正規ストローブ設定値			*/
#define	PRN_P3_STBS4		0x0008		/* 正規ストローブ設定値			*/
#define	PRN_P3_CLKSEL1		0x0010		/* ストローブカウンタ用クロック設定	*/
#define	PRN_P3_CLKSEL2		0x0020		/* ストローブカウンタ用クロック設定	*/
#define	PRN_P3_SELACT		0x0040		/* ストローブ論理の設定			*/
#define	PRN_P3_STBEN		0x0080		/* 露光状態のイネーブル			*/
#define	PRN_P3_INTACK		0x0100		/* PSS割込みのINTACK			*/
#define	PRN_P3_INTEN		0x0200		/* PSS割込みのイネーブル		*/
#define	PRN_P3_MDIR			0x0400		/* モーターの回転方向の設定		*/
#define	PRN_P3_MLD			0x0800		/* モーターパルスの保持停止選択	*/
#define	PRN_P3_MSET			0x1000		/* 励磁相の設定					*/
#define	PRN_P3_MTEN			0x2000		/* モーターイネーブル			*/
#define	PRN_P3_MTCK1		0x4000		/* MTCLKの選択					*/
#define	PRN_P3_MTCK2		0x8000		/* MTCLKの選択					*/

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/05
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:
* DESCRIPTION:	 プリンタ・ポート４(READ)
************************************************************************/
#define	PRINTER4_PORT		0x00C20330	/* アドレス					*/
#define	PRN_P4_PSSIRQ		0x0001		/* PSS割込みモニタ			*/
#define	PRN_P4_PSS			0x0002		/* PSSモニタ				*/
#define	PRN_P4_VSYNC		0x0004		/* VSYNCモニタ				*/
#define	PRN_P4_HSDRD		0x0008		/* HSYNCディレイ状態モニタ	*/
#define	PRN_P4_TEST1		0x0010		/* テストモードモニタ		*/
#define	PRN_P4_TS1			0x0100		/* トナーセンサ出力モニタ１	*/
#define	PRN_P4_TS2			0x0200		/* トナーセンサ出力モニタ２	*/
#define	PRN_P4_TS3			0x0400		/* トナーセンサ出力モニタ３	*/
#define	PRN_P4_TS4			0x0800		/* トナーセンサ出力モニタ４	*/
#define	PRN_P4_TS5			0x1000		/* トナーセンサ出力モニタ５	*/
#define	PRN_P4_TS6			0x2000		/* トナーセンサ出力モニタ６	*/
#define	PRN_P4_TS7			0x4000		/* トナーセンサ出力モニタ７	*/
#define	PRN_P4_TS8			0x8000		/* トナーセンサ出力モニタ８	*/

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/05
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD PRN_Printer6PortData
* DESCRIPTION:	 プリンタ・ポート６(READ/WRITE)
************************************************************************/
#define	PRINTER6_PORT		0x00C20350	/* アドレス					*/
#define	PRN_P6_XHRST		0x0001		/* HSYNC強制リセット				*/
#define	PRN_P6_XVRST		0x0002		/* VSYNC強制リセット				*/
#define	PRN_P6_XLEDRST		0x0004		/* LEDHEADI/F強制リセット			*/
#define	PRN_P6_X400RST		0x0008		/* 400I/F強制リセット				*/
#define	PRN_P6_XMTRST		0x0010		/* MTCNT強制リセット				*/
#define	PRN_P6_XTNRST		0x0020		/* TN強制リセット					*/
#define	PRN_P6_XCKRST		0x0040		/* CLKGEN強制リセット				*/
#define	PRN_P6_XPRRST		0x0080		/* PRCLK強制リセット				*/
#define	PRN_P6_ALLREST		0x00FF		/* 全リセット						*/
#define	PRN_P6_TCLK1		0x0100		/* HSYNC用クロックをSYSCLKに変更	*/
#define	PRN_P6_PTEST4		0x0200		/* モータークロックバイパス			*/
#define	PRN_P6_PTEST3		0x0400		/* XBDEN外部直接入力				*/
#define	PRN_P6_TCLK4		0x0800		/* LEDHEADストローブ用クロックをSYSCLKに変更*/
#define	PRN_P6_TCLK5		0x1000		/* トナー残量検出用クロックをSYSCLKに変更	*/
#define	PRN_P6_TCLK6		0x2000		/* VSYNC用クロックをSYSCLKに変更	*/
#define	PRN_P6_PTEST2		0x4000		/* CLKGEN部テストモード				*/
#define	PRN_P6_PTEST1		0x8000		/* CLKGEN部テストモード				*/

/***********************************************************************
*		   BY:	 M.Tachibana
*		 DATE:	 1997/02/05
*		 TYPE:	 DEFINE
*		  CPU:	 SH704X
* VAR TO HOLD:	 UWORD PRN_Printer7PortData
* DESCRIPTION:	 プリンタ・ポート７(READ/WRITE)
************************************************************************/
#define	PRINTER7_PORT		0x00C20360	/* アドレス					*/
#define	PRN_P7_HSD1			0x0001		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD2			0x0002		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD3			0x0004		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD4			0x0008		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD5			0x0010		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD6			0x0020		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD7			0x0040		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSD8			0x0080		/* HSYNCディレイ設定値		*/
#define	PRN_P7_HSTEST1		0x0100		/* HSYNCカウント用イネーブル信号(4-7)	*/
#define	PRN_P7_HSTEST2		0x0200		/* HSYNCカウント用イネーブル信号(8-11)	*/
#define	PRN_P7_HSTEST3		0x0400		/* HSYNCカウント用イネーブル信号(12-15)	*/
#define	PRN_P7_HSTEST4		0x0800		/* HSYNCカウント用ワンショットパルス幅設定*/
#define	PRN_P7_DCTEST1		0x1000		/* DCテスト用出力ピン切り替え設定	*/
#define	PRN_P7_DCTEST2		0x2000		/* DCテスト用出力ピン切り替え設定	*/

/*-----------------------------------------------------------------------*
 * 以下にＭＤ９５０９用のＩ／Ｏマップを記述します。Nov.13,1995 By S.K	 *
 * 並びは次のようになっています。										 *
 *	(1)スムージング部Ｉ／Ｏ												 *
 *	(2)プリンター部Ｉ／Ｏ												 *
 *	(3)スキャナー部Ｉ／Ｏ												 *
 *-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------------------------------------*/
/*									ＭＤ９５０９	  Ｉ／Ｏ													   */
/*--< スムージング部 >---------------------------------------------------------------------------------------------*/
/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHControlPortData
*		  R/W:	Write
* DESCRIPTION:	スムージング部制御コマンド
*********************************************************************************************/
#define	PRN_IO_CONTROL_ADDRESS			PRN_MD9509_BASE_PORT+0x0020
#define	PRN_CONTROL_ONDMA		0x01		/* イメージＤＭＡ転送			   0:DISABLE		1:ENABLE		   */
#define	PRN_CONTROL_ONSUM		0x02		/* スムージング					   0:DISABLE		1:ENABLE		   */
#define	PRN_CONTROL_RUT1		0x04
#define	PRN_CONTROL_RUT2		0x08
#define	PRN_CONTROL_RUT3		0x10
#define	PRN_CONTROL_RUT4		0x20
#define	PRN_CONTROL_RUT5		0x40
#define	PRN_CONTROL_INV			0x80		/* ビデオデータ論理				   0:そのまま		1:反転			   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode1PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 1 設定レジスタ
*********************************************************************************************/
#define PRN_IO_CODE1_ADDRESS			PRN_MD9509_BASE_PORT+0x0022
#define PRN_CODE1_C00			0x01		/* 検出コード 16H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C01			0x02		/* 検出コード D0H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C02			0x04		/* 検出コード 68H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C03			0x08		/* 検出コード 0BH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C04			0x10		/* 検出コード 97H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C05			0x20		/* 検出コード F4H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C06			0x40		/* 検出コード E9H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE1_C07			0x80		/* 検出コード 2FH				   0:ENABLE			1:DISABLE		   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode2PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 2 設定レジスタ（ノッチ除去）
*********************************************************************************************/
#define PRN_IO_CODE2_ADDRESS			PRN_MD9509_BASE_PORT+0x0024
#define PRN_CODE2_C08			0x01		/* 検出コード 1FH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C09			0x02		/* 検出コード D6H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C10			0x04		/* 検出コード F8H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C11			0x08		/* 検出コード 6BH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C12			0x10		/* 検出コード 07H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C13			0x20		/* 検出コード 94H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C14			0x40		/* 検出コード E0H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE2_C15			0x80		/* 検出コード 29H				   0:ENABLE			1:DISABLE		   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode3PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 3 設定レジスタ（ノッチ除去）
*********************************************************************************************/
#define PRN_IO_CODE3_ADDRESS			PRN_MD9509_BASE_PORT+0x0026
#define PRN_CODE3_C16			0x01		/* 検出コード 1DH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C17			0x02		/* 検出コード C6H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C18			0x04		/* 検出コード B8H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C19			0x08		/* 検出コード 63H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C20			0x10		/* 検出コード 47H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C21			0x20		/* 検出コード 9CH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C22			0x40		/* 検出コード E2H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE3_C23			0x80		/* 検出コード 39H				   0:ENABLE			1:DISABLE		   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode4PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 4 設定レジスタ（ノッチ除去）
*********************************************************************************************/
#define PRN_IO_CODE4_ADDRESS			PRN_MD9509_BASE_PORT+0x0028
#define PRN_CODE4_C24			0x01		/* 検出コード FDH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C25			0x02		/* 検出コード EFH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C26			0x04		/* 検出コード BFH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C27			0x08		/* 検出コード F7H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C28			0x10		/* 検出コード 02H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C29			0x20		/* 検出コード 10H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C30			0x40		/* 検出コード 40H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE4_C31			0x80		/* 検出コード 08H				   0:ENABLE			1:DISABLE		   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode5PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 5 設定レジスタ（ノッチ除去）
*********************************************************************************************/
#define PRN_IO_CODE5_ADDRESS			PRN_MD9509_BASE_PORT+0x002A
#define PRN_CODE5_C32			0x01		/* 検出コード 17H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C33			0x02		/* 検出コード D4H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C34			0x04		/* 検出コード E8H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C35			0x08		/* 検出コード 2BH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C36			0x10		/* 検出コード 0FH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C37			0x20		/* 検出コード 96H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C38			0x40		/* 検出コード F0H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE5_C39			0x80		/* 検出コード 69H				   0:ENABLE			1:DISABLE		   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode6PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 6 設定レジスタ（ノッチ除去）
*********************************************************************************************/
#define PRN_IO_CODE6_ADDRESS			PRN_MD9509_BASE_PORT+0x002C
#define PRN_CODE6_C40			0x01		/* 検出コード 90H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C41			0x02		/* 検出コード 28H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C42			0x04		/* 検出コード 60H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C43			0x08		/* 検出コード 03H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C44			0x10		/* 検出コード 14H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C45			0x20		/* 検出コード 09H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C46			0x40		/* 検出コード C0H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C47			0x80		/* 検出コード 06H				   0:ENABLE			1:DISABLE		   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHCode7PortData
*		  R/W:	Write
* DESCRIPTION:	パターン検出コード 7 設定レジスタ（孤立点除去）
*********************************************************************************************/
#define PRN_IO_CODE7_ADDRESS			PRN_MD9509_BASE_PORT+0x002E
#define PRN_CODE6_C48			0x01		/* 検出コード FFH				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_C49			0x02		/* 検出コード 00H				   0:ENABLE			1:DISABLE		   */
#define PRN_CODE6_BIT2			0x04		/* 未使用															   */
#define PRN_CODE6_BIT3			0x08		/* 未使用															   */
#define PRN_CODE6_BIT4			0x10		/* 未使用															   */
#define PRN_CODE6_BIT5			0x20		/* 未使用															   */
#define PRN_CODE6_EN3X1			0x40		/* 後段スムージング黒補間		   0:有効			1:無効			   */
#define PRN_CODE6_EN3X2			0x80		/* 後段スムージング白補間		   0:有効			1:無効			   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHExpand1PortData
*		  R/W:	Write
* DESCRIPTION:	拡張処理１設定レジスタ
*********************************************************************************************/
#define PRN_IO_EXPAND1_ADDRESS			PRN_MD9509_BASE_PORT+0x0030
#define	PRN_EXPAND1_RENSUM		0x01		/* 連続スムージング検出			   0:有効			1:無効			   */
#define	PRN_EXPAND1_RENNOC		0x02		/* 連続凸ノッチ除去				   0:有効			1:無効			   */
#define	PRN_EXPAND1_KEN1		0x04		/* 文字／斜め線の検出１			   0:有効			1:無効			   */
#define	PRN_EXPAND1_KEN2		0x08		/* 文字／斜め線の検出１			   0:有効			1:無効			   */
#define	PRN_EXPAND1_BIT4		0x10		/* 未使用															   */
#define	PRN_EXPAND1_BIT5		0x20		/* 未使用															   */
#define	PRN_EXPAND1_BIT6		0x40		/* 未使用															   */
#define	PRN_EXPAND1_BIT7		0x80		/* 未使用															   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHExpand2PortData
*		  R/W:	Write
* DESCRIPTION:	拡張処理２設定レジスタ
*********************************************************************************************/
#define PRN_IO_EXPAND2_ADDRESS			PRN_MD9509_BASE_PORT+0x0032
#define	PRN_EXPAND2_TNOCH1		0x01		/* ２×２凸ノッチ検出１			   0:有効			1:無効			   */
#define	PRN_EXPAND2_TNOCH2		0x02		/* ２×２凸ノッチ検出２			   0:有効			1:無効			   */
#define	PRN_EXPAND2_TNOCH3		0x04		/* ２×２凸ノッチ検出３			   0:有効			1:無効			   */
#define	PRN_EXPAND2_TNOCH4		0x08		/* ２×２凸ノッチ検出４			   0:有効			1:無効			   */
#define	PRN_EXPAND2_TNOCH5		0x10		/* 凸ノッチ検出１・２・３・４	   0:検出１・２有効 1:検出３・４有効   */
#define	PRN_EXPAND2_TNOCH6		0x20		/* 凸ノッチ検出５・６・７・８	   0:検出５・６有効 1:検出７・８有効   */
#define	PRN_EXPAND2_ONOCH1		0x40		/* 凹ノッチ検出１・２・３・４	   0:検出１・２有効 1:検出３・４有効   */
#define	PRN_EXPAND2_ONOCH2		0x80		/* 凹ノッチ検出５・６・７・８	   0:検出５・６有効 1:検出７・８有効   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHEnlargePortData
*		  R/W:	Write
* DESCRIPTION:	拡大率設定レジスタ
*********************************************************************************************/
#define PRN_IO_ENLARGE_ADDRESS		PRN_MD9509_BASE_PORT+0x0034
#define	PRN_ENLARGE_FENC		0x01		/* 副走査拡大率					   0:無効			1:有効			   */
#define	PRN_ENLARGE_FCON0		0x02
#define	PRN_ENLARGE_FCON1		0x04
#define	PRN_ENLARGE_FCON2		0x08
#define	PRN_ENLARGE_SENC		0x10		/* 主走査拡大率					   0:無効			1:有効			   */
#define	PRN_ENLARGE_SCON0		0x20
#define	PRN_ENLARGE_SCON1		0x40
#define	PRN_ENLARGE_CHP0		0x80		/* PRDY端子からのPVSVD出力		   0:無効			1:有効			   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.24,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_SMTHOtherPortData
*		  R/W:	Write
* DESCRIPTION:	その他の設定レジスタ
*********************************************************************************************/
#define PRN_IO_OTHER_ADDRESS		PRN_MD9509_BASE_PORT+0x0036
#define	PRN_OTHER_ENO16			0x01		/* ENO16 = 0固定													   */
#define	PRN_OTHER_NOTCK			0x02		/* NOTCK = 0固定													   */
#define	PRN_OTHER_3D			0x04		/* 3D = 0固定														   */
#define	PRN_OTHER_SHEN			0x08		/* 左右白付け					   0:無効			1:有効			   */
#define	PRN_OTHER_RES1			0x10		/* RES1 = 0固定														   */
#define	PRN_OTHER_RES2			0x20		/* RES2 = 0固定														   */
#define	PRN_OTHER_CLEAR			0x40		/* CLR =1 RAM CLEAR CLR=0 プリント可 1996/04/04 */
#define	PRN_OTHER_BIT7			0x80		/* 先頭マスク論理				   0:？				1:論理が白		   */


#if (0) /* 桐用スムージング部 */
** /* バス I/F 設定レジスタ */
** #define PRN_IO_BASS_IF_ADDRESS			0x00420
** #define PRN_BASS_ENWT			0x01		/* READY出力ウェイト挿入		   0:DISABLE		1:ENABLE		   */
** #define PRN_BASS_11WAIT			0x02		/* 1:1 ウエイト														   */
** #define PRN_BASS_21WAIT			0x04		/* 2:1 ウエイト														   */
** #define PRN_BASS_31WAIT			0x08		/* 3:1 ウエイト														   */
** #define PRN_BASS_41WAIT			0x10		/* 4:1 ウエイト														   */
** #define PRN_BASS_ONDMA			0x20		/* DMA転送(DMARQ出力)			   0:DISABLE		1:ENABLE		   */
** #define PRN_BASS_DO				0x40		/* スルー出力					   0:しない			1:する			   */
** #define PRN_BASS_CKS			0x80		/* HSYNサンプリング・クロック	   0:16MHz			1:1MHz			   */
** /* RAM I/F 設定レジスタ */
** #define PRN_IO_RAM_IF_ADDRESS			0x00422
** #define PRN_RAM_16MON			0x01		/* 内部クロック					   0:通常			1:倍速			   */
** #define PRN_RAM_ONWH			0x02		/* 外部RAM出力データ			   0:LOW			1:HIGH			   */
** #define PRN_RAM_ONSUM			0x04		/* スムージング					   0:DISABLE		1:ENABLE		   */
** #define PRN_RAM_DOS				0x08		/* スムージング出力				   0:DISABLE		1:ENABLE		   */
** #define PRN_RAM_SPCK32			0x00		/* SPCKクロック32M													   */
** #define PRN_RAM_SPCK16			0x20		/* SPCKクロック16M													   */
** #define PRN_RAM_SPCK8			0x10		/* SPCKクロック 8M													   */
** #define PRN_RAM_SPCK4			0x30		/* SPCKクロック 4M													   */
** #define PRN_RAM_NOTCK			0x40		/* 0 固定データ														   */
** #define PRN_RAM_BIT7			0x80		/* 未使用															   */
** /* 検出コード 1 設定レジスタ */
** #define PRN_IO_CODE1_ADDRESS			0x00424
** #define PRN_CODE1_C00			0x01		/* 検出コード 16H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C01			0x02		/* 検出コード D0H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C02			0x04		/* 検出コード 68H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C03			0x08		/* 検出コード 0BH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C04			0x10		/* 検出コード 97H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C05			0x20		/* 検出コード F4H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C06			0x40		/* 検出コード E9H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE1_C07			0x80		/* 検出コード 2FH				   0:ENABLE			1:DISABLE		   */
** /* 検出コード 2 設定レジスタ */
** #define PRN_IO_CODE2_ADDRESS			0x00426
** #define PRN_CODE2_C08			0x01		/* 検出コード 1FH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C09			0x02		/* 検出コード D6H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C10			0x04		/* 検出コード F8H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C11			0x08		/* 検出コード 6BH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C12			0x10		/* 検出コード 07H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C13			0x20		/* 検出コード 94H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C14			0x40		/* 検出コード E0H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE2_C15			0x80		/* 検出コード 29H				   0:ENABLE			1:DISABLE		   */
** /* 検出コード 3 設定レジスタ */
** #define PRN_IO_CODE3_ADDRESS			0x00428
** #define PRN_CODE3_C16			0x01		/* 検出コード 1DH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C17			0x02		/* 検出コード C6H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C18			0x04		/* 検出コード B8H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C19			0x08		/* 検出コード 63H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C20			0x10		/* 検出コード 47H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C21			0x20		/* 検出コード 9CH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C22			0x40		/* 検出コード E2H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE3_C23			0x80		/* 検出コード 39H				   0:ENABLE			1:DISABLE		   */
** /* 検出コード 4 設定レジスタ */
** #define PRN_IO_CODE4_ADDRESS			0x0042A
** #define PRN_CODE4_C24			0x01		/* 検出コード FDH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C25			0x02		/* 検出コード EFH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C26			0x04		/* 検出コード BFH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C27			0x08		/* 検出コード F7H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C28			0x10		/* 検出コード 02H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C29			0x20		/* 検出コード 10H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C30			0x40		/* 検出コード 40H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE4_C31			0x80		/* 検出コード 08H				   0:ENABLE			1:DISABLE		   */
** /* 検出コード 5 設定レジスタ */
** #define PRN_IO_CODE5_ADDRESS			0x0042C
** #define PRN_CODE5_C32			0x01		/* 検出コード 42H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C33			0x02		/* 検出コード 18H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C34			0x04		/* 検出コード BDH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C35			0x08		/* 検出コード E7H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C36			0x10		/* 検出コード 17H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C37			0x20		/* 検出コード D4H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C38			0x40		/* 検出コード E8H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE5_C39			0x80		/* 検出コード 2BH				   0:ENABLE			1:DISABLE		   */
** /* 検出コード 6 設定レジスタ */
** #define PRN_IO_CODE6_ADDRESS			0x0042E
** #define PRN_CODE6_C40			0x01		/* 検出コード 0FH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE6_C41			0x02		/* 検出コード 96H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE6_C42			0x04		/* 検出コード F0H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE6_C43			0x08		/* 検出コード 69H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE6_C44			0x10		/* 検出コード FFH				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE6_C45			0x20		/* 検出コード 00H				   0:ENABLE			1:DISABLE		   */
** #define PRN_CODE6_BIT6			0x40		/* 未使用															   */
** #define PRN_CODE6_BIT7			0x80		/* 未使用															   */
** /* スムージング/ノッチ 設定レジスタ */
** #define PRN_IO_SUNO_ADDRESS				0x00430
** #define PRN_SUNO_SSU			0x01		/* 連続スムージング				   0:DISABLE		1:ENABLE		   */
** #define PRN_SUNO_SUNO			0x02		/* スムージング/ノッチ区別		   0:DISABLE		1:ENABLE		   */
** #define PRN_SUNO_NO1			0x04		/* 連続ノッチ					   0:DISABLE		1:ENABLE		   */
** #define PRN_SUNO_CHW			0x08		/* 横ノッチ白変換				   0:DISABLE		1:ENABLE		   */
** #define PRN_SUNO_CHB			0x10		/* 横ノッチ黒変換				   0:DISABLE		1:ENABLE		   */
** #define PRN_SUNO_SEL			0x20		/* 連続ノッチ除去				   0:ENABLE			1:DISABLE		   */
** #define PRN_SUNO_BIT6			0x40		/* 未使用															   */
** #define PRN_SUNO_BIT7			0x80		/* 未使用															   */
** /* 縦ノッチ 設定レジスタ */
** #define PRN_IO_VNO_ADDRESS				0x00432
** #define PRN_VNO1				0x01		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO2				0x02		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO3				0x04		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO4				0x08		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO5				0x10		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO6				0x20		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO7				0x40		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_VNO8				0x80		/* 縦ノッチ						   0:DISABLE		1:ENABLE		   */
** /* 横ノッチ 設定レジスタ */
** #define PRN_IO_HNO_ADDRESS				0x00434
** #define PRN_HNO_HNO1			0x01		/* 横ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_HNO_HNO2			0x02		/* 横ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_HNO_HNO3			0x04		/* 横ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_HNO_HNO4			0x08		/* 横ノッチ						   0:DISABLE		1:ENABLE		   */
** #define PRN_HNO_BIT5			0x10		/* 未使用															   */
** #define PRN_HNO_BIT6			0x20		/* 未使用															   */
** #define PRN_HNO_BIT7			0x40		/* 未使用															   */
** #define PRN_HNO_BIT8			0x80		/* 未使用															   */
** /* 孤立点白変換 設定レジスタ */
** #define PRN_IO_KORITSUW_ADDRESS			0x00436
** #define PRN_HNO_KBW2			0x01		/* 孤立点白変換 設定主走査幅										   */
** #define PRN_HNO_KBW3			0x02		/* 孤立点白変換 設定主走査幅										   */
** #define PRN_HNO_KBW4			0x04		/* 孤立点白変換 設定主走査幅										   */
** #define PRN_HNO_KLW2			0x08		/* 孤立点白変換 設定副走査幅										   */
** #define PRN_HNO_KLW3			0x10		/* 孤立点白変換 設定副走査幅										   */
** #define PRN_HNO_KLW4			0x20		/* 孤立点白変換 設定副走査幅										   */
** #define PRN_HNO_BIT7			0x40		/* 未使用															   */
** #define PRN_HNO_BIT8			0x80		/* 未使用															   */
** /* 孤立点黒変換 設定レジスタ */
** #define PRN_IO_KORITSUB_ADDRESS			0x00438
** #define PRN_HNO_KBB2			0x01		/* 孤立点黒変換 設定主走査幅										   */
** #define PRN_HNO_KBB3			0x02		/* 孤立点黒変換 設定主走査幅										   */
** #define PRN_HNO_KBB4			0x04		/* 孤立点黒変換 設定主走査幅										   */
** #define PRN_HNO_KLB2			0x08		/* 孤立点黒変換 設定副走査幅										   */
** #define PRN_HNO_KLB3			0x10		/* 孤立点黒変換 設定副走査幅										   */
** #define PRN_HNO_KLB4			0x20		/* 孤立点黒変換 設定副走査幅										   */
** #define PRN_HNO_BIT7			0x40		/* 未使用															   */
** #define PRN_HNO_BIT8			0x80		/* 未使用															   */
** /* 直交検出 設定レジスタ */
** #define PRN_IO_CROSS_ADDRESS			0x0043A
** #define PRN_CROSS_CRS1			0x01		/* 白エッジ						   0:検出しない		1:検出する		   */
** #define PRN_CROSS_BIT2			0x02		/* 未使用															   */
** #define PRN_CROSS_BIT3			0x04		/* 未使用															   */
** #define PRN_CROSS_BIT4			0x08		/* 未使用															   */
** #define PRN_CROSS_BIT5			0x10		/* 未使用															   */
** #define PRN_CROSS_BIT6			0x20		/* 未使用															   */
** #define PRN_CROSS_BIT7			0x40		/* 未使用															   */
** #define PRN_CROSS_BIT8			0x80		/* 未使用															   */
** /* スルー 設定レジスタ */
** #define PRN_IO_THROUGH_ADDRESS			0x0043C
** #define PRN_TRU0				0x01		/* 連続スムージング・イネーブル	   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU1				0x02		/* スムージング/ノッチ区別		   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU2				0x04		/* 連続ノッチ・イネーブル		   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU3				0x08		/* 横ノッチ黒変換・イネーブル	   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU4				0x10		/* 横ノッチ白変換・イネーブル	   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU5				0x20		/* 孤立点黒変換・イネーブル		   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU6				0x40		/* 孤立点白変換・イネーブル		   0:強制変換しない 1:強制変換する	   */
** #define PRN_TRU7				0x80		/* 直交検出・イネーブル			   0:強制変換しない 1:強制変換する	   */
** /* 拡大率 設定レジスタ */
** #define PRN_IO_ENLARGE_ADDRESS			0x0043E
** #define PRN_ENLARGE_ENC			0x01		/* 副走査拡大					   0:DISABLE		1:ENABLE		   */
** #define PRN_ENLARGE_MAG1		0x02		/* 副走査拡大倍率  1倍												   */
** #define PRN_ENLARGE_MAG2		0x04		/* 副走査拡大倍率  2倍												   */
** #define PRN_ENLARGE_MAG3		0x06		/* 副走査拡大倍率  3倍												   */
** #define PRN_ENLARGE_MAG4		0x08		/* 副走査拡大倍率  4倍												   */
** #define PRN_ENLARGE_MAG5		0x0A		/* 副走査拡大倍率  5倍												   */
** #define PRN_ENLARGE_MAG6		0x0C		/* 副走査拡大倍率  6倍												   */
** #define PRN_ENLARGE_MAG7		0x0E		/* 副走査拡大倍率  7倍												   */
** #define PRN_ENLARGE_SHEN		0x10		/* 両端白マスク					   0:DISABLE		1:ENABLE		   */
** #define PRN_ENLARGE_RES1		0x20		/* BK1リセット					   0:通常			1:リセット		   */
** #define PRN_ENLARGE_RES2		0x40		/* BK2リセット					   0:通常			1:リセット		   */
** #define PRN_ENLARGE_BIT8		0x80		/* 未使用															   */
#endif /* 桐用スムージング部 */

/*--< プリンタ部 >-------------------------------------------------------------------------------------------------*/
/* MD9309から追加になったレジスタ */
/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_BDCNTCount
*		  R/W:	Write
* DESCRIPTION:	記録ラインカウンタ設定レジスタ下位
*				１６ビット中の下位８ビットBDCT0 - BDCT7をセット
*********************************************************************************************/
#define PRN_IO_BDCTLR_ADDRESS		PRN_MD9509_BASE_PORT+0x0038

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_BDCNTCount
*		  R/W:	Write
* DESCRIPTION:	記録ラインカウンタ設定レジスタ上位
*				１６ビット中の下位８ビットBDCT8 - BDCT15をセット
*********************************************************************************************/
#define PRN_IO_BDCTHR_ADDRESS		PRN_MD9509_BASE_PORT+0x003A

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_MCR3PortData
*		  R/W:	Write
* DESCRIPTION:	動作モード・コマンド・レジスタ３
*********************************************************************************************/
#define PRN_IO_MCR3_ADDRESS		PRN_MD9509_BASE_PORT+0x003C
#define PRN_MCR3_GFD_DIV2		0x00		/* OVCLK選択／外部クロックの分周比２					 */
#define PRN_MCR3_GFD_DIV4		0x01		/* OVCLK選択／外部クロックの分周比４					 */
#define PRN_MCR3_GFD_DIV8		0x02		/* OVCLK選択／外部クロックの分周比８					 */
#define PRN_MCR3_GFD_DIV16		0x03		/* OVCLK選択／外部クロックの分周比１６					 */
#define PRN_MCR3_GFD_G32		0x05		/* ----------------------------------					 */
#define PRN_MCR3_GFD_G41		0x06		/* ----------------------------------					 */
#define PRN_MCR3_CORP			0x08		/* CCLK&PCLK(1)/CCLK Only(0)							 */
#define PRN_MCR3_CNTLD			0x40		/* ラインカウンタ ロード設定	   0:ロード終了	   1:ロード			   */
#define PRN_MCR3_CNTCLR			0x80		/* ラインカウンタ クリア		   0:通常		   1:クリア			   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_MCR4PortData
*		  R/W:	Write
* DESCRIPTION:	動作モード・コマンド・レジスタ４
*********************************************************************************************/
#define PRN_IO_MCR4_ADDRESS		PRN_MD9509_BASE_PORT+0x003E
/* Ｄ０～Ｄ３は白付けラインカウンタ 0 - F */
#define PRN_MCR4_BWEN				0x10		/* 白ラインカウンタ許可				0:待機			1:白付き			*/
#define PRN_MCR4_WORN				0x20		/* ＢＤの幅(ANZUは３０μ)			0:5μｓ以上		1:5μ～1μ			*/
#define PRN_MCR4_HORL				0x40		/* データ転送クロック				0:システムクロック 1:外部			*/
#define PRN_MCR4_SXRESET			0x80		/* ソフトリセット All Clear												*/

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_MCR1PortData
*		  R/W:	Write
* DESCRIPTION:	動作モード・コマンド・レジスタ1設定データ
*********************************************************************************************/
#define PRN_IO_MCR1_ADDRESS		PRN_MD9509_BASE_PORT+0x0040
#define PRN_MCR1_VIDEO_ENABLE	0x01		/* ビデオ関連信号出力			   0:禁止			1:許可			   */
#define PRN_MCR1_THERMAL		0x02		/* プリンタ・タイプ選択１		   0:ページプリンタ 1:サーマルプリンタ */
#define PRN_MCR1_FXHSYN			0x04		/* データ開始信号２				   0:通常			1:転送開始		   */
#define PRN_MCR1_OUT_MEM		0x08		/* 外部トグルライン・バッファ	   0:なし			1:あり			   */
#define PRN_MCR1_CBSYEN			0x10		/* コマンド・ビジー				   0:LOW			1:HIGH			   */
#define PRN_MCR1_XCPRDY			0x20		/* コントローラ・パワーレディ信号  0:HIGH			1:LOW			   */
#define PRN_MCR1_XSTART			0x40		/* プリント動作起動信号			   0:HIGH			1:LOW			   */
#define PRN_MCR1_XPRFD			0x80		/* プレ・フィード信号			   0:HIGH			1:LOW			   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_MCR2PortData
*		  R/W:	Write
* DESCRIPTION:	動作モード・コマンド・レジスタ2設定データ
*********************************************************************************************/
#define PRN_IO_MCR2_ADDRESS		PRN_MD9509_BASE_PORT+0x0042
#define PRN_MCR2_VSYNC_OPEN		0x01		/* 垂直同期信号					   0:停止			1:送出			   */
#define PRN_MCR2_THERMAL		0x02		/* プリンタ・タイプ選択２		   0:ページプリンタ 1:サーマルプリンタ */
#define PRN_MCR2_FXVSYN			0x04		/* データ開始信号１				   0:通常			1:転送開始		   */
#define PRN_MCR2_VSYNC			0x08		/* 垂直同期信号/VALID選択		   0:VALID信号		1:垂直同期信号	   */
#define PRN_MCR2_VALID_CLEAR	0x10		/* TYPD信号クリア				   0:通常			1:クリア		   */
#define PRN_MCR2_LFD_CLK_0		0x00		/* 水平同期信号からデータ送出までの時間設定用周波数			 0Hz	   */
#define PRN_MCR2_LFD_CLK_8M		0x20		/* 水平同期信号からデータ送出までの時間設定用周波数			 8MHz	   */
#define PRN_MCR2_LFD_CLK_12M	0x40		/* 水平同期信号からデータ送出までの時間設定用周波数			12MHz	   */
#define PRN_MCR2_LFD_CLK_16M	0x60		/* 水平同期信号からデータ送出までの時間設定用周波数			16MHz	   */
#define PRN_MCR2_LFD_CLK_32M	0x80		/* 水平同期信号からデータ送出までの時間設定用周波数			32MHz	   */
#define PRN_MCR2_LFD_CLK_HFEXT	0xA0		/* 水平同期信号からデータ送出までの時間設定用周波数			HF外部	   */
#define PRN_MCR2_LFD_CLK_EXT	0xC0		/* 水平同期信号からデータ送出までの時間設定用周波数			外部	   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	無し
*		  R/W:	Write
* DESCRIPTION:	割込 解除レジスタ
*********************************************************************************************/
#define PRN_IO_PCINTR_ADDRESS		PRN_MD9509_BASE_PORT+0x0044
#define PRN_PCINTR_CXTOP			0x01		/* 垂直同期信号					   0:通常		   1:割込解除		   */
#define PRN_PCINTR_CXBD			0x02		/* 水平同期信号					   0:通常		   1:割込解除		   */
#define PRN_PCINTR_CXSBSY		0x04		/* ステータス・ビジー			   0:通常		   1:割込解除		   */
#define PRN_PCINTR_CPGEND		0x08		/* ページ終了					   0:通常		   1:割込解除		   */
#define PRN_PCINTR_CCNTINT		0x10		/* 設定ライン終了				   0:通常		   1:割込解除		   */
#define PRN_PCINTR_BIT5			0x20		/* 未使用															   */
#define PRN_PCINTR_BIT6			0x40		/* 未使用															   */
#define PRN_PCINTR_BIT7			0x80		/* 未使用															   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_PMINTRPortData
*		  R/W:	Write
* DESCRIPTION:	割込 マスク・レジスタ
*********************************************************************************************/
#define PRN_IO_PMINTR_ADDRESS		PRN_MD9509_BASE_PORT+0x0046
#define PRN_MASK_MXTOP			0x01		/* 垂直同期信号要求割込			   0:割込許可		1:割込禁止		   */
#define PRN_MASK_MXBD			0x02		/* 水平同期信号要求割込			   0:割込許可		1:割込禁止		   */
#define PRN_MASK_MXSBSY			0x04		/* ステータス・ビジー要求割込	   0:割込許可		1:割込禁止		   */
#define PRN_MASK_MPGEND			0x08		/* ページ終了要求割込			   0:割込許可		1:割込禁止		   */
#define PRN_MASK_MCNTINT		0x10		/* 設定ライン終了				   0:割込許可		1:割込禁止		   */
#define PRN_MASK_BIT5			0x20		/* 未使用															   */
#define PRN_MASK_BIT6			0x40		/* 未使用															   */
#define PRN_MASK_BIT7			0x80		/* 未使用															   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_LeftMargine
*		  R/W:	Byte Write
* DESCRIPTION:	下位レフト・マージン (1 ～ 2047dot)
*********************************************************************************************/
#define PRN_IO_LFMLR_ADDRESS		PRN_MD9509_BASE_PORT+0x0048

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_LeftMargine
*		  R/W:	Byte Write
* DESCRIPTION:	上位レフト・マージン (1 ～ 2047dot) Ｄ３～Ｄ７まで未使用
*********************************************************************************************/
#define PRN_IO_LFMHR_ADDRESS		PRN_MD9509_BASE_PORT+0x004A

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_RightMargine
*		  R/W:	Byte Write
* DESCRIPTION:	下位ライト・マージン (1 ～ 8191dot)
*********************************************************************************************/
#define PRN_IO_RTMLR_ADDRESS		PRN_MD9509_BASE_PORT+0x004C

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_RightMargine
*		  R/W:	Byte Write
* DESCRIPTION:	上位ライト・マージン (1 ～ 8191dot) Ｄ５～Ｄ７まで未使用
*********************************************************************************************/
#define PRN_IO_RTMHR_ADDRESS		PRN_MD9509_BASE_PORT+0x004E

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_VideoData
*		  R/W:	Byte Write
* DESCRIPTION:	下位 ビデオ・データ・サイズ(1 ～ 8191dot)
*********************************************************************************************/
#define PRN_IO_VZLR_ADDRESS		PRN_MD9509_BASE_PORT+0x0050

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_VideoData
*		  R/W:	Byte Write
* DESCRIPTION:	上位 ビデオ・データ・サイズ(1 ～ 8191dot) Ｄ５～Ｄ７は未使用
*********************************************************************************************/
#define PRN_IO_VZHR_ADDRESS		PRN_MD9509_BASE_PORT+0x0052

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_MemoryDataSize
*		  R/W:	Byte Write
* DESCRIPTION:	下位 外部メモリ・ビデオ・サイズ(1 ～ 8191dot)
*********************************************************************************************/
#define PRN_IO_OVZLR_ADDRESS		PRN_MD9509_BASE_PORT+0x0054

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_MemoryDataSize
*		  R/W:	Byte Write
* DESCRIPTION:	上位 外部メモリ・ビデオ・サイズ(1 ～ 8191dot)Ｄ５～Ｄ７は未使用
*********************************************************************************************/
#define PRN_IO_OVZHR_ADDRESS		PRN_MD9509_BASE_PORT+0x0056

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_VideoDataClock
*		  R/W:	Byte Write
* DESCRIPTION:	周波数選択設定レジスタ
*********************************************************************************************/
#define PRN_IO_FDEVR_ADDRESS		PRN_MD9509_BASE_PORT+0x0058
#define PRN_FDEVR_FD_8MHZ		0x01		/* IVCK設定 8MHz													   */
#define PRN_FDEVR_FD_4MHZ		0x02		/* IVCK設定 4MHz													   */
#define PRN_FDEVR_FD_2MHZ		0x03		/* IVCK設定 2MHz													   */
#define PRN_FDEVR_FD_1MHZ		0x04		/* IVCK設定 1MHz													   */
#define PRN_FDEVR_FD_HF_EXCLK	0x05		/* IVCK設定 HF外部													   */
#define PRN_FDEVR_FD_EXCLK		0x06		/* IVCK設定 外部													   */
#define PRN_FDEVR_OFD_8MHZ		0x10		/* OVCK設定 8MHz													   */
#define PRN_FDEVR_OFD_4MHZ		0x20		/* OVCK設定 4MHz													   */
#define PRN_FDEVR_OFD_2MHZ		0x30		/* OVCK設定 2MHz													   */
#define PRN_FDEVR_OFD_1MHZ		0x40		/* OVCK設定 1MHz													   */
#define PRN_FDEVR_OFD_HF_EXCLK	0x50		/* OVCK設定 HF外部													   */
#define PRN_FDEVR_OFD_EXCLK		0x60		/* OVCK設定 外部													   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_SettingT2Time
*		  R/W:	Byte Write
* DESCRIPTION:	下位 データ転送開始タイミング設定レジスタ １
*********************************************************************************************/
#define PRN_IO_VDLLR_ADDRESS		PRN_MD9509_BASE_PORT+0x005A

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_SettingT2Time
*		  R/W:	Byte Write
* DESCRIPTION:	上位 データ転送開始タイミング設定レジスタ １ Ｄ４～Ｄ７は未使用
*********************************************************************************************/
#define PRN_IO_VDLHR_ADDRESS		PRN_MD9509_BASE_PORT+0x005C

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_SettingT3Time
*		  R/W:	Byte Write
* DESCRIPTION:	下位 データ転送開始タイミング設定レジスタ ２
*********************************************************************************************/
#define PRN_IO_HDLLR_ADDRESS		PRN_MD9509_BASE_PORT+0x005E

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_SettingT3Time
*		  R/W:	Byte Write
* DESCRIPTION:	上位 データ転送開始タイミング設定レジスタ ２
*********************************************************************************************/
#define PRN_IO_HDLHR_ADDRESS		PRN_MD9509_BASE_PORT+0x0060

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_LineCount
*		  R/W:	Byte Write
* DESCRIPTION:	下位ライン数設定レジスタ １(1 - 65535line)
*********************************************************************************************/
#define PRN_IO_LCTLR_ADDRESS		PRN_MD9509_BASE_PORT+0x0062

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	UWORD  PRN_LineCount
*		  R/W:	Byte Write
* DESCRIPTION:	上位ライン数設定レジスタ １(1 - 65535line)
*********************************************************************************************/
#define PRN_IO_LCTHR_ADDRESS		PRN_MD9509_BASE_PORT+0x0064

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	無し
*		  R/W:	Byte Read
* DESCRIPTION:	割込 ステータス・レジスタ
*********************************************************************************************/
#define PRN_IO_PSINTR_ADDRESS		PRN_MD9509_BASE_PORT+0x0044
#define PRN_PSINTR_XTOP			0x01		/* 垂直同期信号要求割込			   0:なし		  1:あり			   */
#define PRN_PSINTR_XBD			0x02		/* 水平同期信号要求割込			   0:なし		  1:あり			   */
#define PRN_PSINTR_XSBSY		0x04		/* ステータス・ビジー要求割込	   0:なし		  1:あり			   */
#define PRN_PSINTR_PGEND		0x08		/* ページ終了要求割込			   0:なし		  1:あり			   */
#define PRN_PSINTR_XPPRDY		0x10		/* プリンタ・パワーレディ信号	   0:なし		  1:あり			   */
#define PRN_PSINTR_XRDY			0x20		/* レディ信号					   0:なし		  1:あり			   */
#define PRN_PSINTR_CNTINT		0x40		/* 設定ライン終了割込			   0:なし		  1:あり			   */
#define PRN_PSINTR_BIT7			0x80		/* 未使用															   */

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Nov.15,1995
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char PRN_CommandPortData
*		  R/W:	Byte Read/Write
* DESCRIPTION:	プリンタ コマンド／ステータス・レジスタ
*				８ビット・シリアルデータ ＭＳＢ First
*********************************************************************************************/
#define PRN_IO_PSDR_ADDRESS		PRN_MD9509_BASE_PORT+0x0066

/********************************************************************************************
*		   BY:	T.Nose
*		 DATE:	Aug.07,1996
*		 TYPE:	DEFINE
* VAR TO HOLD:	unsigned char SCN_BUZZ_1K_Status
*		  R/W:	Write
* DESCRIPTION:
*				Ｄ０からＤ３　ブザー周波数＝ 23.4325KHz/(2*(設定値+1))
*					ex)23.4325/(2*(0x0A+1))=1.065KHz
*				Ｄ４からＤ７　１ＫＨｚ発生＝ 23.4325KHz/(2*(設定値+1))
*					ex)23.4325/(2*(0x0A+1))=1.065KHz
*********************************************************************************************/
#define	PRN_1K_PORT		PRN_MD9509_BASE_PORT+0x0014

/********************************************************************************************
*		   BY:	S.Kawasaki
*		 DATE:	Mar.5,1996
*		 TYPE:	DEFINE
* VAR TO HOLD:
*		  R/W:	Byte Read/Write
* DESCRIPTION:	ＤＭＡＣ Ｉ／Ｏ
*********************************************************************************************/
/*DMAU Address*/
/* 16bitバス設定でuPD71071の奇数アドレスレジスタにバイトアクセスした場合、有効なデータバスは
** D8-D15だが SH CPU はD0-D7に有効データを出力するため、奇数アドレスにデータをかけなかった。
** そこで、A0、A1を逆につなぎ、全てのレジスタをバイトアクセスすることとした。
** よって以下のアドレスデファインはマニュアル上のアドレスとは異なっている。また、全てのレジスタは
** バイトサイズとしている。
** T.Nose 1996/04/24
*/
#define		DMAU_DCH					0x0C00000		/*DMA Channel Register*/
#define		DMAU_DICM					0x0C00001		/*DMA Initial Cmmand Register*/
#define		DMAU_DBC_DCC_WORD			0x0C00003		/*DMA Base Count Register / DMA Current Count Register (16Bit Reg.)*/
#define		DMAU_DBA_DCA_WORD_LOWER		0x0C00005		/*DMA Base Address Register / DMA Current Address Register (A0~A15)*/
#define		DMAU_DBA_DCA_UPPER			0x0C00007		/*DMA Base Address Register / DMA Current Address Register (A16~A23)*/
#define		DMAU_DDC_WORD				0x0C00009		/*DMA Device Control Register (16Bit Reg.) ini_nmi.srcもメンテして下さい 野瀬 */
#define		DMAU_DST					0x0C0000A		/*DMA Status Register*/
#define		DMAU_DMD					0x0C0000B		/*DMA Mode Control Register*/
#define		DMAU_DMK					0x0C0000E		/*DMA Mask Register*/

/* DMAU DICM Bit Define */
#define DMAC_DICM_RES		0x01					/**	 リセット							*/
#define DMAC_DICM_16WIDTH	0x02					/**	 データバス幅１６ビット				*/

/*DMAU DDC Initial Data*/
#define		DMAU_DDC_WORD_DATA					0x002B0		/*DMA Enable,Rotate Priority,Extra Write Timing,Bus Rel Mode,Verify Wait Enable,DMAAK Active High*/
#define		SLAVE_DMAU_DDC_WORD_DATA			0x002B0		/*DMA Enable,Rotate Priority,Extra Write Timing,Bus Rel Mode,Verify Wait Enable,DMAAK Active High*/
/*DMAU DDC Bit Define*/
#define		DDC_DDMA	0x0004		/*DMA Disable Bit*/
#define		DDC_ROT		0x0010		/*Channel Priority Rotation Bit*/
#define		DDC_EXW		0x0020		/*Extra Write Timing Bit*/
#define		DDC_BHLD	0x0100		/*Bus Hold Mode Bit*/
#define		DDC_WEV		0x0200		/*Verify Wait Enable*/
/*DMAU DMD Bit Define*/
#define		DMD_W_B			0x01	/*Word Transfer Bit*/
#define		DMD_TDIR_LOWER	0x04	/*┌Transfer Direction*/
#define		DMD_TDIR_UPPER	0x08	/*└00=Verify,01=I/O->Memory,10=Memory->I/O*/
#define		DMD_AUTI		0x10	/*Auto Initialize Bit*/
#define		DMD_ADIR		0x20	/*Address Decrememt Bit*/
#define		DMD_TMODE_LOWER	0x40	/*┌Transfer Mode*/
#define		DMD_TMODE_UPPER	0x80	/*└00=Demand Mode,01=Single Mode,10=Block Mode,11=Cascade Mode*/
/*DMAU DST Bit Define*/
#define		DST_TC0			0x01	/*DMA TC Channel 0*/
#define		DST_TC1			0x02	/*DMA TC Channel 1*/
#define		DST_TC2			0x04	/*DMA TC Channel 2*/
#define		DST_TC3			0x08	/*DMA TC Channel 3*/

#endif
