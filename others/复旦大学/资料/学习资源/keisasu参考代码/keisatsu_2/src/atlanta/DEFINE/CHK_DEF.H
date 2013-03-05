#ifndef chk_def_h
	#define	chk_def_h
/**********************************************************************
**	チェッカー用の定義ファイル
**	chk_anlg.cの中で定義していたやつを新たに定義します
*/

#include	"\src\atlanta\sh7043\define\sh_port.h"


/* ポート一覧 */
#define	COMMAND_PORT	KEY0_PORT				/*コマンドポート(ｷｰﾎﾟｰﾄ0) */
/*DMA Base Count Register / DMA Current Count Register (16Bit Reg.)*/
#define	DMAU_PORT		DMAU_DBC_DCC_WORD		/*ＤＭＡＵポート*/

#if defined(POPLAR_B) || defined(POPLR_BN) || defined(POPLAR_L) || defined(POPLAR_F)
/* コマンド一覧	ポプラ仕様 */
#define	CHECK_OUT_CPU_PA1		0x01		/* ポートＡデータレジスタＨ */
 #define OUT_CPU_PA1		0xA0
#define	CHECK_OUT_CPU_PA2		0x02		/* ポートＡデータレジスタＨ */
 #define OUT_CPU_PA2		0x51
#define	CHECK_OUT_CPU_PA_UB1	0x03		/* ポートＡデータレジスタＬ */
 #define OUT_CPU_PA_UB1		0xA8
#define	CHECK_OUT_CPU_PA_UB2	0x04		/* ポートＡデータレジスタＬ */
 #define OUT_CPU_PA_UB2		0x55
#define	CHECK_OUT_CPU_PE1		0x05		/* ポートＥデータレジスタ */
 #define OUT_CPU_PE1		0x80
#define	CHECK_OUT_CPU_PE2		0x06		/* ポートＥデータレジスタ */
 #define OUT_CPU_PE2		0x00
#define	CHECK_OUT_CPU_PE_UB1	0x07		/* ポートＥデータレジスタ */
 #define OUT_CPU_PE_UB1		0x4000
 #define RSLT_CPU_PE_UB1	0x40
#define	CHECK_OUT_CPU_PE_UB2	0x08		/* ポートＥデータレジスタ */
 #define OUT_CPU_PE_UB2		0x0000
 #define RSLT_CPU_PE_UB2	0x00
#define	CHECK_OUT_EXT1			0x09		/* 外部 */
 #define OUT_EXT1			0x2A
#define	CHECK_OUT_EXT2			0x0A		/* 外部 */
 #define OUT_EXT2			0x55
#define	CHECK_OUT_EXT_UB1		0x0B		/* 外部 ＵＢ */
 #define OUT_EXT_UB1		0x2A00
 #define RSLT_EXT_UB1		0x2A
#define	CHECK_OUT_EXT_UB2		0x0C		/* 外部 ＵＢ */
 #define OUT_EXT_UB2		0x5500
 #define RSLT_EXT_UB2		0x55
#define	CHECK_IN_CPU_PA			0x0D		/* ポートＡデータレジスタＨ */
 #define IN_CPU_PA			0x02
#define	CHECK_IN_CPU_PA_UB		0x0E		/* ポートＡデータレジスタＬ */
 #define IN_CPU_PA_UB		0x03
#define	CHECK_IN_CPU_PD			0x0F		/* ポートＤデータレジスタ */
 #define IN_CPU_PD			0xC0
#define	CHECK_IN_CPU_PE			0x10		/* ポートＥデータレジスタ */
/* #define IN_CPU_PE			0x3F BとLで異なる */
#define	CHECK_IN_CPU_PE_UB		0x11		/* ポートＥデータレジスタ */
 #define IN_CPU_PE_UB		0x3F
#define	CHECK_IN_CPU_PF			0x12		/* ポートＦデータレジスタ */
 #define IN_CPU_PF			0xFF
#define	CHECK_IN_MD9604			0x13		/* MD9604ｾﾝｻ1 */
#define	CHECK_IN_EXT2			0x14		/* 外部ｾﾝｻ2 */
#if defined(POPLAR_B) || defined(POPLR_BN)
 #define IN_CPU_PE			0x3F
 #define IN_MD9604			0x5B
 #define IN_EXT2			0xDF
#endif
#if defined(POPLAR_L) || defined(POPLAR_F)	/* 1998/01/12  By T.Yamaguchi */
 #define IN_CPU_PE			0x2F
 #define IN_MD9604			0xDB			/* DBHでマスク */
 #define IN_EXT2			0xC0			/* C0Hでマスク */
#endif
#define	CHECK_BUZZER_HIGH		0x15		/* ブザーチェック大 */
#define	CHECK_BUZZER_LOW		0x16		/* ブザーチェック小 */
#define	CHECK_DRAM_WR			0x17		/* ＤＲＡＭライトチェック) */
#define	CHECK_DRAM_RD			0x18		/* ＤＲＡＭリードチェック) */
#define	CHECK_SRAM_WR			0x19		/* ＳＲＡＭライトチェック) */
#define	CHECK_SRAM_RD			0x1A		/* ＳＲＡＭリードチェック) */
#define CHECK_MD9604			0x1B		/* ＭＤ９６０４ */
#define CHECK_MD9605			0x1C		/* ＭＤ９６０５（ＩＤＰ） */
#define	CHECK_EXTEND_RAM		0x1E		/* ＥＸＴＥＮＤ－ＲＡＭチェック */
#if defined(POPLAR_B) || defined(POPLR_BN)
 #define CHECK_MD9509			0x1D		/* ＭＤ９６０９ */
 #define CHECK_RS232C			0x1F		/* ＲＳ２３２Ｃ */
 #define CHECK_OPTION			0x20		/* オプション */
#endif
#if defined(POPLAR_L) || defined(POPLAR_F)	/* 1998/01/12  By T.Yamaguchi */
 #define CHECK_OPTION			0x1F		/* オプション */
 #define CHECK_SHADING			0x20		/* 白黒判定 */
 #define CHECK_RS232C			0x54		/* ＲＳ２３２Ｃ */
#endif
#define	CHECK_AD_PORT_F0		0x21		/* Ａ／Ｄ値上位８bit出力(CASET1) */
#define	CHECK_AD_PORT_F1		0x22		/* Ａ／Ｄ値上位８bit出力(CASET2) */
#define	CHECK_AD_PORT_F2		0x23		/* Ａ／Ｄ値上位８bit出力(CASET3) */
#define	CHECK_AD_PORT_F3		0x24		/* Ａ／Ｄ値上位８bit出力(TEMPR)  */
#define	CHECK_AD_PORT_F4		0x25		/* Ａ／Ｄ値上位８bit出力(BAT)    */
#define	CHECK_AD_PORT_F5		0x26		/* Ａ／Ｄ値上位８bit出力(HVR)    */
#define	CHECK_AD_PORT_F6		0x27		/* Ａ／Ｄ値上位８bit出力(THMST)  */
#define	CHECK_AD_PORT_F7		0x28		/* Ａ／Ｄ値上位８bit出力(TS)     */
#define	CHECK_MODEM_TX			0x29		/* モデム送信チェック */
#define	CHECK_MODEM_RX			0x2A		/* モデム受信チェック */
#define	CHECK_CODEC_SCN			0x2B		/* ＣＯＤＥＣスキャナーチェック */
#define	CHECK_CODEC_PRN			0x2C		/* ＣＯＤＥＣプリンターチェック */
#define	CHECK_CODEC_COM			0x2D		/* ＣＯＤＥＣ通信チェック */
#define	CHECK_DMAU				0x2E		/* ＤＭＡＵチェック */
#define CHECK_MOTOR				0x2F		/* モータ制御 */
#define	CHECK_MOTOR_STOP		0x30		/* モータ制御 */
#define	CHECK_FBS_MOTOR			0x31		/* ＦＢＳモータ制御 */
#define	CHECK_FBS_MOTOR_STOP	0x32		/* ＦＢＳモータ制御 */
#define	CHECK_APS_SENSOR		0x33		/* ＡＰＳセンサー入力チェック */
/* その他のコマンド */
#define	CHECK_RXA_RXOUT			0x50	/* ＲＸＡ－ＲＸＯＵＴチェック*/
#define	CHECK_1100_BPF			0x51	/* １１００ＢＰＦチェック*/
#define	CHECK_462_LPF			0x52	/* ４６２ＬＰＦチェック*/
#define	CHECK_IDP301			0x53	/* ＩＤＰ３０１チェック */
#if defined(POPLAR_B) || defined(POPLR_BN)
 #define	CHECK_SHADING			0x54	/* 白黒判定 */
#endif
#define	CHECK_OUT_RTC_PORT1		0x55		/* ＲＴＣ・ポ－ト */
#define	CHECK_OUT_RTC_PORT2		0x56		/* ＲＴＣ・ポ－ト */
#define	CHECK_TX_OUT_1080HZ		0x57		/* １０８０Ｈｚ送出レベル */
#define	CHECK_TX_OUT_5000HZ		0x58		/* ５０００Ｈｚ送出レベル */

#endif /* POPLAR_B */

#if defined(ANZU_L)
/* コマンド一覧	ＡＮＺＵ＿Ｌ仕様 */
#define	CHECK_OUT_CPU_PA1		0x01		/* ポートＡデータレジスタＨ */
 #define OUT_CPU_PA1		0xA0
#define	CHECK_OUT_CPU_PA2		0x02		/* ポートＡデータレジスタＨ */
 #define OUT_CPU_PA2		0x51
#define	CHECK_OUT_CPU_PA_UB1	0x03		/* ポートＡデータレジスタＬ */
 #define OUT_CPU_PA_UB1		0xAA
#define	CHECK_OUT_CPU_PA_UB2	0x04		/* ポートＡデータレジスタＬ */
 #define OUT_CPU_PA_UB2		0x55
#define	CHECK_OUT_CPU_PA_UB1H	0x05		/* ポートＡデータレジスタＬ上位 */
 #define OUT_CPU_PA_UB1H	0x0200
 #define RSLT_CPU_PA_UB1H	0x02
#define	CHECK_OUT_CPU_PA_UB2H	0x06		/* ポートＡデータレジスタＬ上位 */
 #define OUT_CPU_PA_UB2H	0x0100
 #define RSLT_CPU_PA_UB2H	0x01
#define	CHECK_OUT_CPU_PD1H		0x07		/* ポートＤデータレジスタＬ上位 */
 #define OUT_CPU_PD1H		0x4000
 #define RSLT_CPU_PD1H		0x40
#define	CHECK_OUT_CPU_PD2H		0x08		/* ポートＤデータレジスタＬ上位 */
 #define OUT_CPU_PD2H		0x8000
 #define RSLT_CPU_PD2H		0x80
#define	CHECK_OUT_COM_PORT1			0x09		/* ＣＯＭ・ポ－ト */
 #define OUT_COM_PORT1		0x28
#define	CHECK_OUT_COM_PORT2			0x0A		/* ＣＯＭ・ポ－ト */
 #define OUT_COM_PORT2		0x10
#define	CHECK_OUT_RTC_PORT1			0x0B		/* ＲＴＣ・ポ－ト */
 #define OUT_RTC_PORT1		0x0A
#define	CHECK_OUT_RTC_PORT2			0x0C		/* ＲＴＣ・ポ－ト */
 #define OUT_RTC_PORT2		0x05
#define	CHECK_IN_CPU_PE			0x0D		/* ポートＥデータレジスタ */
 #define IN_CPU_PE			0x5F
#define	CHECK_IN_CPU_PE_UB		0x0E		/* ポートＥデータレジスタ */
 #define IN_CPU_PE_UB		0x3F
#define	CHECK_IN_CPU_PF			0x0F		/* ポートＦデータレジスタ */
 #define IN_CPU_PF			0x0F
#define	CHECK_IN_MD9604			0x11		/* MD9604ｾﾝｻ1 */
 #define IN_MD9604			0x4B
#define	CHECK_IN_MD9604H		0x12		/* MD9604ｾﾝｻ1上位 */
 #define IN_MD9604H			0x01
#define	CHECK_BUZZER_HIGH		0x13		/* ブザーチェック大 */
#define	CHECK_BUZZER_LOW		0x14		/* ブザーチェック小 */
#define	CHECK_DRAM_WR			0x15		/* ＤＲＡＭライトチェック) */
#define	CHECK_DRAM_RD			0x16		/* ＤＲＡＭリードチェック) */
#define	CHECK_SRAM_WR			0x17		/* ＳＲＡＭライトチェック) */
#define	CHECK_SRAM_RD			0x18		/* ＳＲＡＭリードチェック) */
#define CHECK_MD9604			0x19		/* ＭＤ９６０４ */
#define CHECK_MD9605			0x1A		/* ＭＤ９６０５（ＩＤＰ） */
#define	CHECK_EXTEND_RAM		0x1C		/* ＥＸＴＥＮＤ－ＲＡＭチェック */
#define	CHECK_RS232C			0x1D		/* ＲＳ２３２Ｃ */
#define	CHECK_OPTION			0x1E		/* オプション */
#define	CHECK_MODEM_TX			0x1F		/* モデム送信チェック */
#define	CHECK_MODEM_RX			0x20		/* モデム受信チェック */
#define	CHECK_CODEC_PRN			0x21		/* ＣＯＤＥＣプリンターチェック */
#define	CHECK_SHADING			0x22		/* 白黒判定 */
#define	CHECK_MOTOR				0x23		/* モータ制御 */
#define	CHECK_MOTOR_STOP		0x24		/* モータ制御 */
#define	CHECK_TX_OUT_1080HZ		0x25		/* １０８０Ｈｚ送出レベル */
#define	CHECK_TX_OUT_5000HZ		0x26		/* ５０００Ｈｚ送出レベル */
#define	CHECK_AD_PORT_F4		0x27		/* Ａ／Ｄ値上位８bit出力(BAT)    */

/* その他のコマンド */
#define	CHECK_CODEC_SCN			0x30		/* ＣＯＤＥＣスキャナーチェック */
#define	CHECK_CODEC_COM			0x31		/* ＣＯＤＥＣ通信チェック */
#define	CHECK_DMAU				0x32		/* ＤＭＡＵチェック */
#define	CHECK_RXA_RXOUT			0x33		/* ＲＸＡ－ＲＸＯＵＴチェック*/
#define	CHECK_1100_BPF			0x34		/* １１００ＢＰＦチェック*/
#define	CHECK_462_LPF			0x35		/* ４６２ＬＰＦチェック*/
#define	CHECK_IDP301			0x36		/* ＩＤＰ３０１チェック */

#define PRINTER1_PORT		0x00C20300	/* MD9604 */
#endif /* ANZU_L_ */



/* ステータス（チェック結果） */
#define	CHECK_RAM_WRITE		0x20	/* ＲＡＭライト完了 */
#define	BUZZER_HIGH_OK		0x10	/* ブザー大、送出中 */
#define	BUZZER_LOW_OK		0x11	/* ブザー小、送出中 */
#define	CHECK_DRAM_OK		0x30	/* ＤＲＡＭチェック(RD) ＯＫ */
#define	CHECK_SRAM_OK		0x40	/* ＳＲＡＭチェック(RD 55H) ＯＫ */
#define	CHECK_MD9604_OK		0x50	/* MD9604 */
#define	CHECK_MD9605_OK		0x60	/* MD9605 */
#define	CHECK_MD9509_OK		0x70	/* MD9509 */
#define	CHECK_EXT_DRAM_OK	0x80	/* ＥＸＴＥＮＤ－ＲＡＭチェック(A) ＯＫ*/
#define CHECK_DRAM_EX12_NG  0x01	/* ＥＸ-ＲＡＭチェック(1200000) NG */
#define CHECK_DRAM_EX14_NG  0x02	/* ＥＸ-ＲＡＭチェック(1400000) NG */
#define CHECK_DRAM_EX16_NG  0x04	/* ＥＸ-ＲＡＭチェック(1600000) NG */
#define CHECK_DRAM_EX18_NG  0x08	/* ＥＸ-ＲＡＭチェック(1800000) NG */
#define	CHECK_RS232C_OK		0x90	/* ＲＳ２３２Ｃ */
#define	CHECK_OPTION_OK		0xA0	/* オプション */
#define	CHECK_ERROR			0xE0	/* チェックエラー */
#define	CHECK_MDM_TX		0x20	/* モデム出力ポート出力中*/
#define	CHECK_MDM_TRAINING_NG	0x31	/* モデムトレーニングエラー*/
#define	CHECK_MDM_RX_OK		0x30	/* モデム受信データＯＫ*/
#define	CHECK_MDM_RX_NG		0x32	/* モデム受信データＮＧ*/
#define	CHECK_DRAM_IC36_NG	0x36	/* 拡張DRAM ＮＧ */
#define	CHECK_DMAU_OK		0xC0	/* ＤＭＡＵチェック ＯＫ*/
#define	CHECK_DMAU_NG		0xE0	/* ＤＭＡＵチェック ＮＧ*/
#define	CHECK_IDP301_OK		0x60	/* ＩＤＰ３０１　ＯＫ */
#define	CHECK_IDP301_NG		0xE0	/* ＩＤＰ３０１　ＮＧ */
#define	CHECK_CODEC_SCN_OK	0xB1	/* ＣＯＤＥＣスキャナーＯＫ */
#define	CHECK_CODEC_SCN_NG	0xE0	/* ＣＯＤＥＣスキャナーＮＧ */
#define	CHECK_CODEC_PRN_OK	0xB2	/* ＣＯＤＥＣプリンターＯＫ */
#define	CHECK_CODEC_PRN_NG	0xE0	/* ＣＯＤＥＣプリンターＮＧ */
#define	CHECK_CODEC_COM_OK	0xB3	/* ＣＯＤＥＣ通信ＯＫ */
#define	CHECK_CODEC_COM_NG	0xE0	/* ＣＯＤＥＣ通信ＮＧ */

/* レベルチェック */
#define	CHECK_RXA_RXOUT_BIT	0x00	/* ＲＸＡ＿ＲＸＯＵＴビット */
#define	CHECK_1100_BPF_BIT	0x01	/* １１００ＢＰＦビット */
#define	CHECK_462_LPF_BIT	0x02	/* ４６２ＬＰＦビット */

/* モデムチェックデータ */
#define	CHECK_MDM_DATA0		0xDB	/* チェックデータ０ */
#define	CHECK_MDM_DATA1		0xB6	/* チェックデータ１ */
#define	CHECK_MDM_DATA2		0x6D	/* チェックデータ２ */
/* 結果出力ＯＮ／ＯＦＦ */
#define	OUT_ON				1		/* 結果出力ＯＮ*/
#define	OUT_OFF				0		/* 結果出力ＯＦＦ*/
/* READ/WRITE */
#define	CHK_READ	0				/* Read */
#define	CHK_WRITE	1				/* Write */
	
#endif
