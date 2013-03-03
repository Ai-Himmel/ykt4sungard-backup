/*--------------------------------------------------------------------------*/
/*  プロジェクト : HINOKI                                                   */
/*  ファイル名   : HINO_INT.C                                               */
/*  作成者       : K.Kawata                                                 */
/*  日  付       : 97.06.04                                                 */
/*  概  要       : 機種別割り込み処理関数                                   */
/*               : 先頭アドレステーブル                                     */
/*  修正履歴     : SAKAKIよりコピーしただけです。	By O.Kimoto 1998/09/07  */
/*                 HINOKI用にメンテしました。	By H.Hirao 1998/09/19       */
/*--------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"

extern void GA_Interrupt1(void);
extern void GA_Interrupt2(void);
extern void DTC_MDMBUF_MDM_Interrupt(void);
extern void DTC_MDM_MDMBUF_Interrupt(void);
extern void MDM_ModemInterrupt(void);
extern void CommunicationCodecInterrupt(void);
extern void NCU_CI_Interrupt(void);
extern void DMA_TC_ComCodecToRam_Interrupt(void);
extern void DMA_TC_RamToComCodec_Interrupt(void);
extern void DMA_MemoryToMemory_TC_Interrupt(void);
extern void DTC_GateArrayWriteInterrupt(void);

#if (PRO_VOICE_ANSWER == ENABLE)	/* Add by O.Kimoto 2002/10/15 */
extern void MDM_AnswerLSIInterrupt(void);
#endif

#if defined (KEISATSU) /* 警察FAX 05/07/01 石橋正和 */
extern void S1_Interrupt(void);
#endif

/*------- cl1\sci_irpt.c --------------------------------------------------------------*/
extern void	SciTxInt(void);
extern void	SciRxInt(void);
extern void	SciErInt(void);
extern void	SciTeInt(void);
extern void	IntSciCTS(void);
extern void	INT_DMA_RsTxRx(void);
extern void CmtCtsInt(void);	/* added by H.Hirao 1999/03/16 */


#pragma section INT_ENTRY_IRQL /* ロケート時のセクション名 "CINT_ENTRY_IRQL" */
CONST UDWORD INT0_FUNCTION = (UDWORD)(&GA_Interrupt2);	/** G/A Interrupt2 */
CONST UDWORD INT1_FUNCTION = (UDWORD)(&GA_Interrupt1);	/** G/A Interrupt1 */
CONST UDWORD INT2_FUNCTION = (UDWORD)(&DTC_MDMBUF_MDM_Interrupt);	/** SRAMからMODEMへのDTC転送終了割り込み */
CONST UDWORD INT3_FUNCTION = (UDWORD)(&DTC_MDM_MDMBUF_Interrupt);	/** MODEMからSRAMへのDTC転送終了割り込み */
#pragma section

#pragma section INT_ENTRY_IRQH /* ロケート時のセクション名 "CINT_ENTRY_IRQH" */
CONST UDWORD INT4_FUNCTION = (UDWORD)(&MDM_ModemInterrupt);	/** Modem Status Interrupt */
CONST UDWORD INT5_FUNCTION = (UDWORD)(&CommunicationCodecInterrupt);	/** コーデック割り込み */
#if (0) /* 1998/10/26 by T.Soneoka */
**CONST UDWORD INT6_FUNCTION = (UDWORD)(&NCU_CI_Interrupt);	/** ＣＩ割り込み */
#else
CONST UDWORD INT6_FUNCTION = (UDWORD)(&DTC_GateArrayWriteInterrupt);
#endif
#if defined (KEISATSU) /* 警察FAX 05/07/01 石橋正和 */
	CONST UDWORD INT7_FUNCTION = (UDWORD)(&S1_Interrupt); /* S1割込み */
#else
	#if (PRO_VOICE_ANSWER == ENABLE)	/* Add by O.Kimoto 2002/10/15 */
		CONST UDWORD INT7_FUNCTION = (UDWORD)(&MDM_AnswerLSIInterrupt);	/** 音声応答ＩＣ割り込み */
	#else
		CONST UDWORD INT7_FUNCTION = (UDWORD)(&IntSciCTS);	/** ＣＴＳ割り込み */
	#endif
#endif
#pragma section

#pragma section INT_ENTRY_IRQD /* ロケート時のセクション名 "CINT_ENTRY_IRQD" */
CONST UDWORD INT_DMAC0_CH0_FUNCTION = (UDWORD)(&DMA_TC_RamToComCodec_Interrupt);	/** DRAMから通信コーデックへのDMA転送終了 */
CONST UDWORD INT_DMAC0_CH1_FUNCTION = (UDWORD)(&DMA_TC_ComCodecToRam_Interrupt);	/** 通信コーデックからDRAMへのDMA転送終了 */
CONST UDWORD INT_DMAC0_CH2_FUNCTION = (UDWORD)(&INT_DMA_RsTxRx);					/** クラス１ＤＭＡ終了割り込み */
CONST UDWORD INT_DMAC0_CH3_FUNCTION = (UDWORD)(&DMA_MemoryToMemory_TC_Interrupt);	/** メモリ－メモリの DMA 転送割り込み */
CONST UDWORD INT_UNDEFINE_FUNCTION = (UDWORD)(0xFFFFFFFF);	/** ダミーアドレス */
#pragma section

#pragma section INT_ENTRY_SCI /* ロケート時のセクション名 "CINT_ENTRY_SCI" */
CONST UDWORD INT_ERI1_FUNCTION = (UDWORD)(&SciErInt);	/* RS232C割込み		*/
CONST UDWORD INT_RXI1_FUNCTION = (UDWORD)(&SciRxInt);	/* RS232C割込み		*/
CONST UDWORD INT_TXI1_FUNCTION = (UDWORD)(&SciTxInt);	/* RS232C割込み		*/
CONST UDWORD INT_TEI1_FUNCTION = (UDWORD)(&SciTeInt);	/* RS232C割込み		*/
CONST UDWORD INT_CMI0_FUNCTION = (UDWORD)(&CmtCtsInt);	/* CMI0割り込み added by H.Hirao 1999/03/16 */
#pragma section

/* 割り込み専用スタック領域
**
** INT_InterruptStack		スタック領域
** INT_TaskStackPointer		割り込みがかかった時点で実行していたタスクのスタックポインタを待避する変数
*/
/* added by H.Kubo 1998/07/15 */
#pragma section INT_STACK 
/* 注意!! INT_InterruptStack と INT_TaskStackPointer の間には何も書かないこと。ロケータで重要です。 */
UBYTE INT_InterruptStack[192] = {0};
UDWORD INT_TaskStackPointer = 0;
#pragma section
