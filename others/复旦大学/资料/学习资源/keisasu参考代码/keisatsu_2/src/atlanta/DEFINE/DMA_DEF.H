/*
 *	dma_def.h  1994/01/11  DMAU 状態定義  By M.Kotani
 *	For V53 & uPD71071
 */
/*
** 履歴：
**		1996/05/20 S.Kawasaki モデル別のDMA MAX値の削除
**
*/

#ifndef	dma_def_h
	#define	dma_def_h

#if (PRO_CPU == SH7043)
	#include "\src\atlanta\sh7043\define\sh_port.h"
#endif

/***********************************************************************
*		   BY:	 T.Nose
*		 DATE:	 1996/11/09
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 N/A
* DESCRIPTION:	 DMA種類 内蔵/外付け
************************************************************************/
#define		DMA_INTERNAL_CH_MAX		(UBYTE)4

/***********************************************************************
*		   BY:	 T.Nose
*		 DATE:	 1996/11/09
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 N/A
* DESCRIPTION:	 DMAチャンネル
************************************************************************/
#if defined (SAKAKI)	/* 1998/06/11 H.Yoshikawa */
#define DMA_COMCDC_DRAM_CH		0	/* 通信コーデック → ＤＲＡＭ	  */
#define DMA_DRAM_COMCDC_CH		1	/* ＤＲＡＭ → 通信コーデック	  */

/*-------------------------------------------------------------------------
** SAKAKIでは使用していないが、ATLANTA共通のソースコードを使用するために、
** undefにならないように定義しておきます。
** 1998/06/11 H.Yoshikawa
*/
#define DMA_MDM_MDMBUF_CH		2	/* モデム → モデムバッファ		  */
#define DMA_MPC_MPCBUF_CH		3	/* ＭＰＣ ←→ バッファ			  */
#define DMA_SCNCDC_DRAM_CH		4	/* スキャナコーデック → ＤＲＡＭ */
#define DMA_DRAM_PRNCDC_CH		5	/* ＤＲＡＭ → プリンタコーデック */
#define DMA_MEMORY_TO_MEMORY_CH	6	/* ＤＲＡＭ → ＤＲＡＭ           */ /* added by H.Kubo 1998/01/29 */
#define	RS_DMA_CH				7	/* ＣＬＡＳＳ１用ＤＴＣ起動チャンネル */

#define DMA_MDMBUF_MDM_CH		8	/* モデム ← モデムバッファ		  */

#elif defined (HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined (SATSUKI2) || defined(STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
#define DMA_DRAM_COMCDC_CH		0	/* ＤＲＡＭ → 通信コーデック	  */
#define DMA_COMCDC_DRAM_CH		1	/* 通信コーデック → ＤＲＡＭ	  */
#define DMA_MPC_MPCBUF_CH		2	/* ＭＰＣ ←→ バッファ			  */ /* changed by H.Hirao 1999/01/14 */
#define DMA_MEMORY_TO_MEMORY_CH	3	/* ＤＲＡＭ → ＤＲＡＭ           */ /* changed by H.Hirao 1999/01/14 */

/*-------------------------------------------------------------------------
** SAKAKIでは使用していないが、ATLANTA共通のソースコードを使用するために、
** undefにならないように定義しておきます。
** 1998/06/11 H.Yoshikawa
*/
 #if (0)	/* changed by H.Hirao 1999/01/14 */
/*	#define DMA_MDM_MDMBUF_CH		2	@* モデム → モデムバッファ		  */
/*	#define DMA_MPC_MPCBUF_CH		3	@* ＭＰＣ ←→ バッファ			  */
/*	#define DMA_SCNCDC_DRAM_CH		4	@* スキャナコーデック → ＤＲＡＭ */
/*	#define DMA_DRAM_PRNCDC_CH		5	@* ＤＲＡＭ → プリンタコーデック */
/*	#define DMA_MEMORY_TO_MEMORY_CH	6	@* ＤＲＡＭ → ＤＲＡＭ           */ /* added by H.Kubo 1998/01/29 */
/*	#define	RS_DMA_CH				7	@* ＣＬＡＳＳ１用ＤＴＣ起動チャンネル */
/*	#define DMA_MDMBUF_MDM_CH		8	@* モデム ← モデムバッファ		  */
/*	#define DMA_GATEARRAYWRITE_CH	9	@* プリンタイメージバッファ → Ｇ／Ａ 1998/10/26 by T.Soneoka */
 #else
#define DMA_MDM_MDMBUF_CH		4	/* モデム → モデムバッファ		  */
#define DMA_SCNCDC_DRAM_CH		5	/* スキャナコーデック → ＤＲＡＭ */
#define DMA_DRAM_PRNCDC_CH		6	/* ＤＲＡＭ → プリンタコーデック */
#define	RS_DMA_CH				7	/* ＣＬＡＳＳ１用ＤＴＣ起動チャンネル */
#define DMA_MDMBUF_MDM_CH		8	/* モデム ← モデムバッファ		  */
#define DMA_GATEARRAYWRITE_CH	9	/* プリンタイメージバッファ → Ｇ／Ａ 1998/10/26 by T.Soneoka */
 #endif
#else

#if (PRO_EXT_DMAC == ENABLE)
#define DMA_MDM_MDMBUF_CH		0	/* モデム ←→ モデムバッファ	  */
#define DMA_MDMBUF_MDM_CH		0	/* モデム ←→ モデムバッファ	  */ /* R288F ドライバを SAKAKI に流用するため。added by H.Kubo 1998/07/15 */
#define DMA_MPC_MPCBUF_CH		1	/* ＭＰＣ ←→ バッファ			  */
#define DMA_SCNCDC_DRAM_CH		4	/* スキャナコーデック → ＤＲＡＭ */
#define DMA_DRAM_PRNCDC_CH		5	/* ＤＲＡＭ → プリンタコーデック */
#define DMA_COMCDC_DRAM_CH		6	/* 通信コーデック → ＤＲＡＭ	  */
#define DMA_DRAM_COMCDC_CH		7	/* ＤＲＡＭ → 通信コーデック	  */
#define DMA_MEMORY_TO_MEMORY_CH	2	/* ＤＲＡＭ → ＤＲＡＭ           */ /* added by H.Kubo 1998/01/29 */
#else
#define DMA_SCNCDC_DRAM_CH		0	/* スキャナコーデック → ＤＲＡＭ */
#define DMA_DRAM_PRNCDC_CH		1	/* ＤＲＡＭ → プリンタコーデック */
/* とりあえず 1997/06/26 */
#define DMA_MDM_MDMBUF_CH		4	/* モデム ←→ モデムバッファ	  */
#define DMA_MPC_MPCBUF_CH		5	/* ＭＰＣ ←→ バッファ			  */
#define DMA_COMCDC_DRAM_CH		6	/* 通信コーデック → ＤＲＡＭ	  */
#define DMA_DRAM_COMCDC_CH		7	/* ＤＲＡＭ → 通信コーデック	  */
/* ANZU_L CLASS 1 Debug -- WC97303 1997/09/22 13:15 */
/* #define	RS_DMA_CH			9	*/	/* ＣＬＡＳＳ１用ＤＴＣ起動チャンネル */
#define	RS_DMA_CH				DMA_MPC_MPCBUF_CH	/* MPCBUFを使用する */
									/* ＣＬＡＳＳ１用ＤＴＣ起動チャンネル */
/* ANZU_L CLASS 1 Debug -- WC97303 1997/09/22 13:15 */
#endif

#endif	/* 1998/06/11 H.Yoshikawa */

/***********************************************************************
*		   BY:	 M.Kotani
*		 DATE:	 Jan.11,1994
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 DMAU_Blk.DCH_Status
* DESCRIPTION:	 DMAレジスタアクセス条件
************************************************************************/
#define		READ_CURRENT_WRITE_BASE_CURRENT		(UBYTE)0
#define		READ_BASE_WRITE_BASE				(UBYTE)1
/***********************************************************************
*		   BY:	 M.Kotani
*		 DATE:	 Jan.13,1994
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 DMAU_Blk.DMD_Status
* DESCRIPTION:	 DMA転送単位
************************************************************************/
#define		DMA_BYTE_TRANSFER	(UBYTE)0
#define		DMA_WORD_TRANSFER	(UBYTE)1
#define		DMA_DWORD_TRANSFER	(UBYTE)2	/* SH内蔵DMACのみ */
/***********************************************************************
*		   BY:	 M.Kotani
*		 DATE:	 Jan.13,1994
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 DMAU_Blk.DMD_Status
* DESCRIPTION:	 DMA転送方向
************************************************************************/
#define		DMA_VERIFY				(UBYTE)0
#define		DMA_IO_TO_MEMORY		(UBYTE)1
#define		DMA_MEMORY_TO_IO		(UBYTE)2
#define		DMA_MEMORY_TO_MEMORY	(UBYTE)3
/***********************************************************************
*		   BY:	 M.Kotani
*		 DATE:	 Jan.14,1994
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 DMAU_Blk.DMD_Status
* DESCRIPTION:	 DMA転送モード
************************************************************************/
#define		DMA_DEMAND_MODE		(UBYTE)0
#define		DMA_SINGLE_MODE		(UBYTE)1
#define		DMA_BLOCK_MODE		(UBYTE)2
#define		DMA_CASCADE_MODE	(UBYTE)3
/***********************************************************************
*		   BY:	 T.Nose
*		 DATE:	 1996/12/11
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 DMA_SH_Cntrl.AutoInit
* DESCRIPTION:	 SH内蔵DMAオートイニシャライズON/OFF
************************************************************************/
#define		AUTO_INITIALIZE_OFF	(UBYTE)0
#define		AUTO_INITIALIZE_ON	(UBYTE)1
/***********************************************************************
*		   BY:	 M.Kotani
*		 DATE:	 Oct.30,1994
*		 TYPE:	 DEFINE
* VAR TO HOLD:
* DESCRIPTION:	 DMA Control Macro Program
************************************************************************/
#if (PRO_EXT_DMAC == ENABLE)
#define	DMA_STOP_MASTER_DMAU()	outp(DMAU_DDC_WORD, 0x04|inp(DMAU_DDC_WORD))
#define	DMA_START_MASTER_DMAU() outp(DMAU_DDC_WORD, 0xfb&inp(DMAU_DDC_WORD))
#endif

/*--------------------------------------------------------------*/
/*	モデムＤＭＡの指定 (ＭＤＭのソースではこの#defineを使う)	*/
/*		Ｍｏｄｅｍ ←→ Ｓ－ＲＡＭ(ModemBuffer)					*/
/*											Jul.08.1994 竹内	*/
/*--------------------------------------------------------------*/
#if (PRO_SCN_CODEC_TYPE == MN86064)
	/*	きり …… ＤＭＡＲＱ４	*/
	#define		MDM_DMA_UNIT	(UBYTE)SLAVE1_DMAU
	#define		MDM_DMA_CH		(UBYTE)1
#endif

/*----------------------------------------------------------------------*/
/*	ＣＬＡＳＳ １ＤＭＡの指定 (CLASS 1のｿｰｽ中ではこの#defineを使用)		*/
/*		SLAVE1,ch2					96.02.06 Y.Tanimoto					*/
/*----------------------------------------------------------------------*/
#if 0	/* (PRO_CLASS1 == ENABLE) 上のdefineに追加 1997/08/18  By T.Yamaguchi	*/
	#define		RS_DMA_UNIT		(UBYTE)SLAVE1_DMAU
	#define		RS_DMA_CH		(UBYTE)2
#endif
#if (PRO_INTERNET_FAX == ENABLE)	/* 1996/10/17 by Y.Tanimoto */
	#define		RS_DMA_UNIT		(UBYTE)SLAVE1_DMAU
	#define		RS_DMA_CH		(UBYTE)2
#endif

#endif

/*--------------------------------------------------------------*/
/* メモリマップドＩ／Ｏ
/*	モデムＤＭＡの指定 (ＭＤＭのソースではこの#defineを使う)	*/
/*		Ｍｏｄｅｍ ←→ Ｓ－ＲＡＭ(ModemBuffer)					*/
/*--------------------------------------------------------------*/

#if defined (SAKAKI)	/* 1998/06/16 H.Yoshikawa */
	/*---------------------------------------------------------------------
	** DTCのメモリマップドＩ／Ｏを定義する
	** BYTE転送のときはI/O側アドレスを奇数にすること
	** WORD転送のときはI/O側アドレスを偶数にすること
	** 1998/06/16 H.Yoshikawa
	*/
 #if 0 /* Changed by H.Kubo 1998/07/15 */
@@	#define MDM_TX_ADDRESS			0xC30201		/* ＭＯＤＥＭバッファ -> ＭＯＤＥＭ（Ｉ／Ｏ） */
@@	#define MDM_RX_ADDRESS			0xC40001		/* ＭＯＤＥＭ（Ｉ／Ｏ） -> ＭＯＤＥＭバッファ */
 #else
	#define MDM_TX_ADDRESS			0xC40121		/* ＭＯＤＥＭバッファ -> ＭＯＤＥＭ（Ｉ／Ｏ） */
	#define MDM_RX_ADDRESS			0xC40101		/* ＭＯＤＥＭ（Ｉ／Ｏ） -> ＭＯＤＥＭバッファ */
 #endif
	#define DMA_DUMMY_ADDRESS		0xC40300		/* 未使用領域 */

	#define SCN_TO_DRAM_ADDRESS		0xC30001		/* ＩＤＰ３０１（Ｉ／Ｏ） -> ＤＲＡＭ */
	#define PRN_TO_DRAM_ADDRESS		0xC30100		/* ＤＲＡＭ -> ＭＤ９４０１（Ｉ／Ｏ）*/

	#define RS_ADDRESS				0xC40300		/* 未使用領域 */

#elif defined (HINOKI) || defined (HINOKI2) || defined (HINOKI3) || defined (KEISATSU) || defined (SATSUKI2) || defined(STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */ /* HINOKI2 2001/11/12 T.Takagi */
	/*---------------------------------------------------------------------
	** DTCのメモリマップドＩ／Ｏを定義する
	** 1998/09/28 H.Hirao
	** DTC用のモデム空間にします 1998/10/20
	*/
	#define MDM_TX_ADDRESS			0x80C010 /*0xC40121*/		/* ＭＯＤＥＭバッファ -> ＭＯＤＥＭ（Ｉ／Ｏ） */
	#define MDM_RX_ADDRESS			0x80C000 /*0xC40101*/		/* ＭＯＤＥＭ（Ｉ／Ｏ） -> ＭＯＤＥＭバッファ */
	#define DMA_DUMMY_ADDRESS		0xF00000 /*0xC40300*/		/* 未使用領域 */

#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
	#define S1_SCI_DATA_ADDRESS		0xA0C010					/* S1(SCI) <-> モデムバッファ */
	#define S1_HDLC_DATA_ADDRESS	0xA0C02A					/* S1(HDLC) <-> モデムバッファ */
#endif

	#define SCN_TO_DRAM_ADDRESS		0xC30001		/* ＩＤＰ３０１（Ｉ／Ｏ） -> ＤＲＡＭ */
	#define PRN_TO_DRAM_ADDRESS		0xC30100		/* ＤＲＡＭ -> ＭＤ９４０１（Ｉ／Ｏ）*/

	#define RS_ADDRESS				0xC40300		/* 未使用領域 */

	#define PRN_TO_GA_ADDRESS		0xC00016	/* プリンタイメージバッファ → Ｇ／Ａ 1998/10/26 by T.Soneoka */

#else	/* 1998/06/16 H.Yoshikawa */

 #if (PRO_CPU == SH7043)
  #if (PRO_EXT_DMAC == ENABLE)
	#define DMA_DUMMY_ADDRESS	0xC40501			/* IO R/W をアドレス出力(CS)で */
													/* 代用する為のダミーアドレス  */
   #if (PRO_MODEM == ORANGE3)
	#define MDM_ADDRESS			0x000000			/* ポプラＢはない */
   #endif
   #if (PRO_MODEM == R288F)
	#define MDM_TX_ADDRESS			0xC40121		/* Ｒ２８８Ｆ ＴＢＵＦＦＥＲ */
	#define MDM_RX_ADDRESS			0xC40101		/* Ｒ２８８Ｆ ＲＢＵＦＦＥＲ */
   #endif
	#define RS_ADDRESS			0x000000			/* ポプラＢはない */
   #if (PRO_VOICE_ANSWER == ENABLE)	/* 1999/06/8  By T.Sato ポプラＢＮ */
	#define VOICE_ADDRESS			0xC40011		/* VOICEROMを書き込むモデムのアドレス */
   #endif
  #else												/* <- 0xC40500 1997/05/07      */
   #if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA)
	#define DMA_DUMMY_ADDRESS	0xC402FE			/* <- Communication Codec Channel */
   #else
	#define DMA_DUMMY_ADDRESS	0xC40500			/* <- L Type SH_DMAC Codec Channel */
   #endif
	#define MDM_ADDRESS			0xC40101			/* モデムデータＴｘＲｘアドレス */
	/* modem ModemTxData1_Control 0x0C4000D */		/* 6: パラレル送信データ設定１	*/
	#define RS_ADDRESS			0xC40309			/* RS232C ADDRESS */
	/* UPD72002_DOUT		0x00C40300	 データ・ライト／リード   */
   #if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/29  By T.Yamaguchi */
	#define VOICE_ADDRESS			0xC40011		/* VOICEROMを書き込むモデムのアドレス */
   #endif

  #endif
 #endif

#endif	/* 1998/06/16 H.Yoshikawa */

/***********************************************************************
*		   BY:	 T.Nose
*		 DATE:	 1997/07/09
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 
* DESCRIPTION:	 DTC転送チャンネル
************************************************************************/
#define DTC_MDM_MDMBUF_CH		23	/* モデム ←→ モデムバッファ 起動要因ＩＲＱ５ */

/***********************************************************************
*		   BY:	 T.Yamaguchi
*		 DATE:	 1997/07/16
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 
* DESCRIPTION:	 DTC転送モードチャンネル
************************************************************************/
#define DTC_INTERRUPT_CH		0	/* 割り込みからのＤＴＣ起動チャンネル */
#define DTC_BLOCK_MODE			1	/* ソフト起動でブロック転送モードチャンネル */
#define DTC_NORMAL_MODE			2	/* ソフト起動でノーマル転送モードチャンネル */
#define DTC_REPEAT_MODE			3	/* ソフト起動でリピート転送モードチャンネル */
#define DTC_INTERRUPT_CH2		5	/* 割り込み起動ＩＲＱ６ */

/***********************************************************************
*		   BY:	 H.Yoshikawa
*		 DATE:	 1998/06/16
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 SAKAKI用に定義する。
*				 値は、ALTANTAで使用しているものと重複しないようにしておきます。
*				 SAKAKIでは、IRQ3/IRQ4/IRQ5/IRQ6を使用します
* DESCRIPTION:	 DTC転送モードチャンネル
************************************************************************/
#define DTC_INTERRUPT_IRQ0		6	/* ＩＲＱ０割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ1		7	/* ＩＲＱ１割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ2		8	/* ＩＲＱ２割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ3		9	/* ＩＲＱ３割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ4		10	/* ＩＲＱ４割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ5		11	/* ＩＲＱ５割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ6		12	/* ＩＲＱ６割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_IRQ7		13	/* ＩＲＱ７割り込みからのＤＴＣ起動チャンネル */
#define DTC_INTERRUPT_RXI1		14	/* ＲＸＩ割り込みからのＤＴＣ起動チャネル */
#define DTC_INTERRUPT_TXI1		15	/* ＴＸＩ割り込みからのＤＴＣ起動チャネル */
