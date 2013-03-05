/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_/ANZU_L                                           */
/*  ファイル名   : dma_sh.c                                                 */
/*  作成者       : 野瀬                                                     */
/*  日  付       : 1996/11/13                                               */
/*  概  要       : SH7043内蔵DMACの各種設定を行う為の関数群                 */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include "\src\atlanta\ext_v\dma_data.h"
#include "\src\atlanta\define\cdc_pro.h"	/*デバッグ用 By M.Kotani 1997/11/1*/
#include "\src\atlanta\define\cdc_def.h"	/*デバッグ用 By M.Kotani 1997/11/1*/

#if (PRO_MODEM == R288F)
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\mon_pro.h"
#endif
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\mon_pro.h"
#endif

void SaveReturnAddressAndJumpBegin(void);

/*************************************************************************
	module		:[SH7043内蔵DMAC全チャネルの動作許可]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/13]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SH_StartDMAU(void)
{
	DMA__DMAOPR |= DMAOPR_DME;
}


/*************************************************************************
	module		:[SH7043内蔵DMAC全チャネルの動作禁止]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/13]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SH_StopDMAU(void)
{
	DMA__DMAOPR &= ~DMAOPR_DME;
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送アドレスを読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD DMA_CheckSH_Address(UBYTE channel,		/* チャンネル */
							UBYTE direction)	/* 転送方向 */
{
	UDWORD address;

	switch (direction) {
	case DMA_MEMORY_TO_IO:
		address = CheckDMAU_SH_SAR(channel);
		break;
	case DMA_IO_TO_MEMORY:
		address = CheckDMAU_SH_DAR(channel);
		break;
#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/29 */
	case DMA_MEMORY_TO_MEMORY:
		address = CheckDMAU_SH_SAR(channel);
		break;
#endif /* 0 */
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(address);
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送アドレスを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
		I/O 側のアドレスレジスタにはダミーアドレスをセットする
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_Address(UBYTE channel,		/* チャンネル */
						UBYTE direction,	/* 転送方向 */
						UDWORD address)		/* 転送アドレス */
{
#if (PRO_MODEM == R288F)
 #if (PRO_SH2_INTERNAL_DMAC == MODEM_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/0722 */
	/* Ｒ２８８Ｆは、Ｉ／Ｏ側のアドレスを正しく指定する必要あり。 By O.Kimoto 1997/10/09 */

	UDWORD io_address;

	if (channel == DMA_MDM_MDMBUF_CH) {		/* モデム ←→ モデムバッファ	  */
		if (direction == DMA_IO_TO_MEMORY) {	/* データ受信 */
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					io_address = S1_HDLC_DATA_ADDRESS;
				}
				else {
					io_address = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				io_address = MDM_RX_ADDRESS;
			}
#else
			io_address = MDM_RX_ADDRESS;
#endif
		}
		else if (direction == DMA_MEMORY_TO_IO){	/* データ送信*/
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					io_address = S1_HDLC_DATA_ADDRESS;
				}
				else {
					io_address = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				io_address = MDM_TX_ADDRESS;
			}
#else
			io_address = MDM_TX_ADDRESS;
#endif
		}
		else {	/* ここへ来てはダメ!! */
			SaveReturnAddressAndJumpBegin();
		}
	}
	else {
		io_address = DMA_DUMMY_ADDRESS;
	}

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = io_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = io_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		break;
#if 0 /* (PRO_MODEM == R288F) */
	case DMA_MEMORY_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = io_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		break;
#endif /* 0 */

	default:
		SaveReturnAddressAndJumpBegin();
	}
 #elif (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA)
  #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
	UDWORD io_address;
	/*
	** レシーブデータレジスタ（ＲＤＲ１）、トランスミットデータレジスタ（ＴＤＲ１）を設定 by H.Hirao 1999/01/14
	*/
	if (channel == DMA_MPC_MPCBUF_CH) {	/* ＲＤＲ１→ＭＥＭＯＲＹ、ＭＥＭＯＲＹ→ＴＤＲ１ */
		if (direction == DMA_IO_TO_MEMORY) {	/* データ受信 */
			io_address = (UDWORD)SCI_RDR1;
		}
		else if (direction == DMA_MEMORY_TO_IO){	/* データ送信 */
			io_address = (UDWORD)SCI_TDR1;
		}
		else {	/* ここへ来てはダメ!! */
			SaveReturnAddressAndJumpBegin();
		}
	}
	else {
		io_address = DMA_DUMMY_ADDRESS;
	}

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = io_address;
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = io_address;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
  #else
	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = DMA_DUMMY_ADDRESS;
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = DMA_DUMMY_ADDRESS;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
  #endif
 #endif
#else
	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = DMA_DUMMY_ADDRESS;
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = DMA_DUMMY_ADDRESS;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
#endif

#if (0)
** 	switch (direction) {
** 	case DMA_IO_TO_MEMORY:
** 		DMA_SetSH_SAR(channel,DMA_DUMMY_ADDRESS);
** 		DMA_SetSH_DAR(channel,address);
** 		break;
** 	case DMA_MEMORY_TO_IO:
** 		DMA_SetSH_SAR(channel,address);
** 		DMA_SetSH_DAR(channel,DMA_DUMMY_ADDRESS);
** 		break;
** 	default:
** 		SaveReturnAddressAndJumpBegin();
** 	}
#endif
}

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)/* added by H.Kubo 1998/01/29 */
/*************************************************************************
	module		:[SH7043内蔵DMACの転送アドレスを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_MEMORY_TO_MEMORY のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/01/28]
	author		:[久保博]
*************************************************************************/
void DMA_SetSH_DstSrcAddress(UBYTE channel,		/* チャンネル */
						UBYTE direction,	/* 転送方向 */
						UDWORD dst_address,		/* 転送先アドレス */
						UDWORD src_address)	/* 転送元アドレス */
{
#if (PRO_MODEM == R288F)
	switch (direction) {
	case DMA_MEMORY_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = src_address;
		DMA_SH_Cntrl[channel].DstAddress = dst_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
#endif
}

/*************************************************************************
	module		:[SH7043内蔵DMAC CH2 割り込み処理関数]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_MEMORY_TO_MEMORY のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/01/28]
	author		:[久保博]
*************************************************************************/
void DMA_MemoryToMemory_TC_Interrupt(void)
{
#if (PRO_MODEM == R288F)
	DMA__CHCR2 &= ~CHCR_IE;
	DMA_MemoryToMemory_TC_Flag = TRUE;
	idet_evt(EVT_DMA_MEMORY_TO_MEMORY);
#endif
}
#endif /* 0 */

/*************************************************************************
	module		:[SH7043内蔵DMACの転送元アドレス(SAR)を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_SAR(UBYTE channel,
                   UDWORD address)
{
	switch (channel) {
	case 0:
		DMA__SAR0 = address;
		break;
	case 1:
		DMA__SAR1 = address;
		break;
	case 2:
		DMA__SAR2 = address;
		break;
	case 3:
		DMA__SAR3 = address;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送元アドレス(SAR)を読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD CheckDMAU_SH_SAR(UBYTE channel)
{
	UDWORD address;

	switch (channel) {
	case 0:
		address = DMA__SAR0;
		break;
	case 1:
		address = DMA__SAR1;
		break;
	case 2:
		address = DMA__SAR2;
		break;
	case 3:
		address = DMA__SAR3;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
	return(address);
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送先アドレス(DAR)を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_DAR(UBYTE channel,
                   UDWORD address)
{
	switch (channel) {
	case 0:
		DMA__DAR0 = address;
		break;
	case 1:
		DMA__DAR1 = address;
		break;
	case 2:
		DMA__DAR2 = address;
		break;
	case 3:
		DMA__DAR3 = address;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送元アドレス(DAR)を読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD CheckDMAU_SH_DAR(UBYTE channel)
{
	UDWORD address;

	switch (channel) {
	case 0:
		address = DMA__DAR0;
		break;
	case 1:
		address = DMA__DAR1;
		break;
	case 2:
		address = DMA__DAR2;
		break;
	case 3:
		address = DMA__DAR3;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(address);
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送回数を読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD DMA_CheckSH_Counter(UBYTE channel)
{
	UDWORD count;

	switch (channel) {
	case 0:
		count = DMA__TCR0;
		break;
	case 1:
		count = DMA__TCR1;
		break;
	case 2:
		count = DMA__TCR2;
		break;
	case 3:
		count = DMA__TCR3;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(count);
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送回数を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_Counter(UBYTE channel,
                       UDWORD counter)
{
	if ((counter & 0xFF000000) != 0) { /* 設定値が24ビット(16777216回)以上の場合 */
		SaveReturnAddressAndJumpBegin();
	}

	DMA_SH_Cntrl[channel].Counter = counter;
}


/*************************************************************************
	module		:[SH7043内蔵DMACのトランスファカウントレジスタを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/10]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_TCR(UBYTE channel,
				   UDWORD counter)
{
	switch (channel) {
	case 0:
		DMA__TCR0 = counter;
		break;
	case 1:
		DMA__TCR1 = counter;
		break;
	case 2:
		DMA__TCR2 = counter;
		break;
	case 3:
		DMA__TCR3 = counter;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送サイズを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_Unit(UBYTE channel,	/* チャンネル */
					UBYTE unit)		/* 転送単位 */
{
	DMA_SH_Cntrl[channel].Unit = unit;
}


/*************************************************************************
	module		:[SH7043内蔵DMACのチャンネルコントロールレジスタの
				  転送サイズを設定する
	]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/10]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CHCR_Unit(UBYTE channel,
						 UBYTE unit)
{
	switch (channel) {
	case 0:
		DMA_SetSH_CH0_Unit(unit);
		break;
	case 1:
		DMA_SetSH_CH1_Unit(unit);
		break;
	case 2:
		DMA_SetSH_CH2_Unit(unit);
		break;
	case 3:
		DMA_SetSH_CH3_Unit(unit);
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル０の転送サイズを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH0_Unit(UBYTE unit)
{
	DMA__CHCR0 &= ~CHCR_TS_MASK;	/* 転送サイズのリセット */

	switch (unit) {
	case DMA_BYTE_TRANSFER:
		DMA__CHCR0 |= CHCR_TS_BYTE;
		break;
	case DMA_WORD_TRANSFER:
		DMA__CHCR0 |= CHCR_TS_WORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル１の転送サイズを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH1_Unit(UBYTE unit)
{
	DMA__CHCR1 &= ~CHCR_TS_MASK;	/* 転送サイズのリセット */

	switch (unit) {
	case DMA_BYTE_TRANSFER:
		DMA__CHCR1 |= CHCR_TS_BYTE;
		break;
	case DMA_WORD_TRANSFER:
		DMA__CHCR1 |= CHCR_TS_WORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル２の転送サイズを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH2_Unit(UBYTE unit)
{
	DMA__CHCR2 &= ~CHCR_TS_MASK;	/* 転送サイズのリセット */

	switch (unit) {
	case DMA_BYTE_TRANSFER:
		DMA__CHCR2 |= CHCR_TS_BYTE;
		break;
	case DMA_WORD_TRANSFER:
		DMA__CHCR2 |= CHCR_TS_WORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル３の転送サイズを設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH3_Unit(UBYTE unit)
{
	DMA__CHCR3 &= ~CHCR_TS_MASK;	/* 転送サイズのリセット */

	switch (unit) {
	case DMA_BYTE_TRANSFER:
		DMA__CHCR3 |= CHCR_TS_BYTE;
		break;
	case DMA_WORD_TRANSFER:
		DMA__CHCR3 |= CHCR_TS_WORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACの転送方向を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_Direction(UBYTE channel,
						 UBYTE direction)
{
	DMA_SH_Cntrl[channel].Direction = direction;
}


/*************************************************************************
	module		:[SH7043内蔵DMACのチャンネルコントロールレジスタの
				  転送方向を設定する
	]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/09/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CHCR_Direction(UBYTE channel,
							  UBYTE direction)
{
	switch (channel) {
	case 0:
		DMA_SetSH_CH0_Direction(direction);
		break;
	case 1:
		DMA_SetSH_CH1_Direction(direction);
		break;
	case 2:
		DMA_SetSH_CH2_Direction(direction);
		break;
	case 3:
		DMA_SetSH_CH3_Direction(direction);
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル０の転送方向を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH0_Direction(UBYTE direction)
{
	UDWORD chcr_status;

	chcr_status = DMA__CHCR0;

	/* リソースリセット
	** デスティネーションアドレスモードリセット
	** ソースアドレスモードリセット
	*/
	chcr_status &= 0xFFFF00FF;

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス固定
		** デスティネーションアドレス増加
		** アクノリッジリードサイクル出力
		*/
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/07/22 */
 #if 0
 		chcr_status |= (CHCR_DM_INC | CHCR_RS_IO_MEM); /* 外部I/O => メモリ*/
 #else
		chcr_status |= (CHCR_DM_INC | CHCR_AL); /* changed by H.Kubo 1998/08/05 */
		chcr_status &= ~CHCR_AM;
 #endif
#else
		chcr_status |= CHCR_DM_INC;
		chcr_status &= ~CHCR_AM;
#endif
		break;
	case DMA_MEMORY_TO_IO:
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス増加
		** デスティネーションアドレス固定
		** アクノリッジライトサイクル出力
		*/
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/07/22 */
 #if defined(HINOKI) || defined (HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 *//* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 		chcr_status |= (CHCR_SM_INC | CHCR_AM | CHCR_AL);	/* デスティネーションアドレスは増加、書き込みサイクルでDACKを出力、ローアクティブで出力 */
 		chcr_status &= ~CHCR_RS_MASK; /* 外部リクエスト、デュアルアドレスモード */
 #else
  #if 0
		/* chcr_status |= (CHCR_SM_INC | CHCR_RS_MEM_IO); */ /*  メモリ => 外部I/O*/
  #else
		chcr_status |= (CHCR_SM_INC | CHCR_AM | CHCR_AL); /* デュアルアクセスモード */ /* changed by H.Kubo 1998/08/05 */
  #endif
 #endif
#else
		chcr_status |= (CHCR_SM_INC + CHCR_AM);
#endif
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	DMA__CHCR0 = chcr_status;

}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル１の転送方向を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH1_Direction(UBYTE direction)
{
	UDWORD chcr_status;

	chcr_status = DMA__CHCR1;

	/* リソースリセット
	** デスティネーションアドレスモードリセット
	** ソースアドレスモードリセット
	*/
	chcr_status &= 0xFFFF00FF;

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス固定
		** デスティネーションアドレス増加
		** アクノリッジリードサイクル出力
		*/
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/07/22 */
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 */ /* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 		chcr_status |= (CHCR_DM_INC | CHCR_AL);	/* デスティネーションアドレスは増加、ローアクティブで出力 */
 		chcr_status &= ~CHCR_AM; /* 読み出しサイクルでDACKを出力 */
 		chcr_status &= ~CHCR_RS_MASK; /* 外部リクエスト、デュアルアドレスモード */
 #else
  #if 0
		/* chcr_status |= (CHCR_RS_IO_MEM | CHCR_DS); */ /* 外部I/O => メモリ 立ち下がりエッジ検出  シングルアドレスモード*/
  #else
		chcr_status |= (CHCR_DM_INC | CHCR_AL); /* changed by H.Kubo 1998/08/05 */
		chcr_status &= ~CHCR_AM; /* デュアルアクセスモード */
  #endif
 #endif
#else
		chcr_status |= CHCR_DM_INC;
		chcr_status &= ~CHCR_AM;
#endif
		break;
	case DMA_MEMORY_TO_IO:
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス増加
		** デスティネーションアドレス固定
		** アクノリッジライトサイクル出力
		*/
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* added by H.Kubo 1998/07/22 */
 #if 0
 		/* chcr_status |= (CHCR_SM_INC | CHCR_RS_MEM_IO | CHCR_DS); */ /*  メモリ => 外部I/O シングルアドレスモード */
 #else
		chcr_status |= (CHCR_SM_INC | CHCR_AM | CHCR_AL); /* デュアルアクセスモード */ /* changed by H.Kubo 1998/08/05 */
 #endif
#else
		chcr_status |= (CHCR_SM_INC + CHCR_AM);
#endif
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	DMA__CHCR1 = chcr_status;

}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル２の転送方向を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH2_Direction(UBYTE direction)
{
	UDWORD chcr_status;

	chcr_status = DMA__CHCR2;

	/* リソースリセット
	** デスティネーションアドレスモードリセット
	** ソースアドレスモードリセット
	*/
	chcr_status &= 0xFFFF00FF;

	switch (direction) {
	case DMA_IO_TO_MEMORY:
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
		/* デスティネーションアドレス増加、内部リクエスト、ＲＸＩ１ by H.Hirao 1999/01/14 */
		chcr_status &= ~CHCR_RO;
		chcr_status |= CHCR_DM_INC;
		chcr_status |= CHCR_SM_RGD;
		chcr_status |= CHCR_RS_RXI1;
#else
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス固定
		** デスティネーションアドレス増加
		** アクノリッジリードサイクル出力
		*/
		chcr_status |= CHCR_DM_INC;
		chcr_status &= ~CHCR_AM;
#endif
		break;
	case DMA_MEMORY_TO_IO:
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
		/* ソースアドレス増加、内部リクエスト、ＴＸＩ１ by H.Hirao 1999/01/14 */
		chcr_status &= ~CHCR_RO;
		chcr_status |= CHCR_DM_RGD;
		chcr_status |= CHCR_SM_INC;
		chcr_status |= CHCR_RS_TXI1;
#else
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス増加
		** デスティネーションアドレス固定
		** アクノリッジライトサイクル出力
		*/
		chcr_status |= (CHCR_SM_INC + CHCR_AM);
#endif
		break;
#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/29 */
	case DMA_MEMORY_TO_MEMORY:
		/* 
		** ソースアドレス増加
		** デスティネーションアドレス増加
		*/
		chcr_status |= (CHCR_SM_INC | CHCR_DM_INC);
		break;
#endif /* 0 */
	default:
		SaveReturnAddressAndJumpBegin();
	}

	DMA__CHCR2 = chcr_status;

}


/*************************************************************************
	module		:[SH7043内蔵DMACチャンネル３の転送方向を設定する]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetSH_CH3_Direction(UBYTE direction)
{
	UDWORD chcr_status;

	chcr_status = DMA__CHCR3;

	/* リソースリセット
	** デスティネーションアドレスモードリセット
	** ソースアドレスモードリセット
	*/
	chcr_status &= 0xFFFF00FF;

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス固定
		** デスティネーションアドレス増加
		** アクノリッジリードサイクル出力
		*/
		chcr_status |= CHCR_DM_INC;
		chcr_status &= ~CHCR_AM;
		break;
	case DMA_MEMORY_TO_IO:
		/* 外部リクエスト、デュアルアドレスモード
		** ソースアドレス増加
		** デスティネーションアドレス固定
		** アクノリッジライトサイクル出力
		*/
		chcr_status |= (CHCR_SM_INC + CHCR_AM);
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	DMA__CHCR3 = chcr_status;

}


/*************************************************************************
	module		:[SH7043内蔵DMACの引数のチャンネルをマスクする]
	function	:[
		1.チャンネルコントロールレジスタのＤＥビットをクリアする
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_RequestMaskInternalDMAU(UBYTE channel)
{
	switch (channel) {
	case 0:
		DMA__CHCR0 &= ~CHCR_DE;
		break;
	case 1:
		DMA__CHCR1 &= ~CHCR_DE;
		break;
	case 2:
		DMA__CHCR2 &= ~CHCR_DE;
		break;
	case 3:
		DMA__CHCR3 &= ~CHCR_DE;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DMACの引数のチャンネルをイネーブルにする]
	function	:[
		1.チャンネルコントロールレジスタのＤＥビットをセットする
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_RequestEnableInternalDMAU(UBYTE channel)
{
	/* 転送元アドレスの設定 */
	DMA_SetSH_SAR(channel,DMA_SH_Cntrl[channel].SrcAddress);
	/* 転送先アドレスの設定 */
	DMA_SetSH_DAR(channel,DMA_SH_Cntrl[channel].DstAddress);
	/* カウンタの設定 */
	DMA_SetSH_TCR(channel,DMA_SH_Cntrl[channel].Counter);
	/* 転送方向の設定 */
	DMA_SetSH_CHCR_Direction(channel,DMA_SH_Cntrl[channel].Direction);
	/* 転送単位の設定 */
	DMA_SetSH_CHCR_Unit(channel,DMA_SH_Cntrl[channel].Unit);

	/* 引数の内蔵ＤＭＡチャネルのＴＥフラグをクリアした後、動作許可する */
	switch (channel) {
	case 0:
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR0 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
				DMA__CHCR0 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2)  || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 */ /* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR0 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR0 &= ~CHCR_TE;
		DMA__CHCR0 |= CHCR_DE;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
		CodecREQC0_Enable(SCANNER_CODEC);	/*デバッグ用 By M.Kotani 1997/11/1*/
#endif
		break;
	case 1:
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR1 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2)  || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 */ /* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR1 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
				DMA__CHCR1 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR1 &= ~CHCR_TE;
		DMA__CHCR1 |= CHCR_DE;
		break;
	case 2:
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
		if (DMA__CHCR2 & CHCR_TE) {
			DMA__CHCR2 &= ~CHCR_TE;
		}
		DMA__CHCR2 |= CHCR_IE;
#else
		DMA__CHCR2 &= ~CHCR_TE;
 #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/0129 */
		/* メモリメモリ転送 のときは立てとかないつ終わったか分からん。*/
		DMA__CHCR2 |= ( CHCR_RS_AUTO | CHCR_IE); /* オートリクエスト、終了割り込み許可*/
		SH__IPRC |= DMAC2_LEVEL; /* こんなところで割り込み順位を変えてごめんなさい。*/
 #endif
#endif
		DMA__CHCR2 |= CHCR_DE;
		break;
	case 3:
		DMA__CHCR3 &= ~CHCR_TE;
		DMA__CHCR3 |= CHCR_DE;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH内蔵DMACによるDMA転送を再スタートします]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_RestartInternalDMAU(UBYTE channel,		/* DMAチャンネル */
					 		 UBYTE direction,	/* DMA転送方向 */
					 		 UDWORD count,		/* DMA転送回数 */
					 		 UDWORD address)	/* DMAアドレス */
{

#if (0)	/* 処理速度を上げるためべたで書く By M.Tachibana 1998/02/26 */
	DMA_SetSH_Address(channel,direction,address);	/* 転送アドレスの設定 */
	DMA_SetSH_Counter(channel,count);				/* 転送回数の設定 */
	DMA_SetSH_Direction(channel,direction);			/* 転送方向の設定 */
	DMA_RequestEnableInternalDMAU(channel);			/* DMAイネーブル */
#endif

/*	DMA_SetSH_Address(channel,direction,address);	下記処理に変更 By M.Tachibana 1998/02/03 *//* 転送アドレスの設定 */
#if (PRO_MODEM == R288F)
 #if (PRO_SH2_INTERNAL_DMAC == MODEM_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/0722 */
	/* Ｒ２８８Ｆは、Ｉ／Ｏ側のアドレスを正しく指定する必要あり。 By O.Kimoto 1997/10/09 */

	UDWORD io_address;

	if (channel == DMA_MDM_MDMBUF_CH) {		/* モデム ←→ モデムバッファ	  */
		if (direction == DMA_IO_TO_MEMORY) {	/* データ受信 */
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					io_address = S1_HDLC_DATA_ADDRESS;
				}
				else {
					io_address = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				io_address = MDM_RX_ADDRESS;
			}
#else
			io_address = MDM_RX_ADDRESS;
#endif
		}
		else if (direction == DMA_MEMORY_TO_IO){	/* データ送信*/
#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					io_address = S1_HDLC_DATA_ADDRESS;
				}
				else {
					io_address = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				io_address = MDM_TX_ADDRESS;
			}
#else
			io_address = MDM_TX_ADDRESS;
#endif
		}
		else {	/* ここへ来てはダメ!! */
			SaveReturnAddressAndJumpBegin();
		}
	}
	else {
		io_address = DMA_DUMMY_ADDRESS;
	}

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = io_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = io_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		break;
#if 0 /* (PRO_MODEM == R288F) */
	case DMA_MEMORY_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = io_address;	/** Change DMA_DUMMY_ADDRESS to io_address by O.Kimoto 1997/10/9 */
		break;
#endif /* 0 */

	default:
		SaveReturnAddressAndJumpBegin();
	}
 #else
  #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
	UDWORD io_address;
	/*
	** レシーブデータレジスタ（ＲＤＲ１）、トランスミットデータレジスタ（ＴＤＲ１）を設定 by H.Hirao 1999/01/14
	*/
	if (channel == DMA_MPC_MPCBUF_CH) {	/* ＲＤＲ１→ＭＥＭＯＲＹ、ＭＥＭＯＲＹ→ＴＤＲ１ */
		if (direction == DMA_IO_TO_MEMORY) {	/* データ受信 */
			io_address = (UDWORD)SCI_RDR1;
		}
		else if (direction == DMA_MEMORY_TO_IO){	/* データ送信 */
			io_address = (UDWORD)SCI_TDR1;
		}
		else {	/* ここへ来てはダメ!! */
			SaveReturnAddressAndJumpBegin();
		}
	}
	else {
		io_address = DMA_DUMMY_ADDRESS;
	}

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = io_address;
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = io_address;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
  #else
	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = DMA_DUMMY_ADDRESS;
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = DMA_DUMMY_ADDRESS;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
  #endif
 #endif
#else
	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_SH_Cntrl[channel].SrcAddress = DMA_DUMMY_ADDRESS;
		DMA_SH_Cntrl[channel].DstAddress = address;
		break;
	case DMA_MEMORY_TO_IO:
		DMA_SH_Cntrl[channel].SrcAddress = address;
		DMA_SH_Cntrl[channel].DstAddress = DMA_DUMMY_ADDRESS;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
#endif

/*	DMA_SetSH_Counter(channel,count);	下記処理に変更 By M.Tachibana 1998/02/03 *//* 転送回数の設定 */
	if ((count & 0xFF000000) != 0) { /* 設定値が24ビット(16777216回)以上の場合 */
		SaveReturnAddressAndJumpBegin();
	}
	DMA_SH_Cntrl[channel].Counter = count;

/*	DMA_SetSH_Direction(channel,direction);	下記処理に変更 By M.Tachibana 1998/02/03 *//* 転送方向の設定 */
	DMA_SH_Cntrl[channel].Direction = direction;

/*	DMA_RequestEnableInternalDMAU(channel);	下記処理に変更 By M.Tachibana 1998/02/03 *//* DMAイネーブル */
	/* 引数の内蔵ＤＭＡチャネルのＴＥフラグをクリアした後、動作許可する */
	switch (channel) {
	case 0:
		/* 転送元アドレスの設定 */
		DMA__SAR0 = DMA_SH_Cntrl[channel].SrcAddress;
		/* 転送先アドレスの設定 */
		DMA__DAR0 = DMA_SH_Cntrl[channel].DstAddress;
		/* カウンタの設定 */
		DMA__TCR0 = DMA_SH_Cntrl[channel].Counter;
		/* 転送方向の設定 */
		DMA_SetSH_CH0_Direction(DMA_SH_Cntrl[channel].Direction);
		/* 転送単位の設定 */
		DMA_SetSH_CH0_Unit(DMA_SH_Cntrl[channel].Unit);

#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR0 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
				DMA__CHCR0 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2)  || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 *//* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR0 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR0 &= ~CHCR_TE;
		DMA__CHCR0 |= CHCR_DE;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
		CodecREQC0_Enable(SCANNER_CODEC);	/*デバッグ用 By M.Kotani 1997/11/1*/
#endif
		break;
	case 1:
		/* 転送元アドレスの設定 */
		DMA__SAR1 = DMA_SH_Cntrl[channel].SrcAddress;
		/* 転送先アドレスの設定 */
		DMA__DAR1 = DMA_SH_Cntrl[channel].DstAddress;
		/* カウンタの設定 */
		DMA__TCR1 = DMA_SH_Cntrl[channel].Counter;
		/* 転送方向の設定 */
		DMA_SetSH_CH1_Direction(DMA_SH_Cntrl[channel].Direction);
		/* 転送単位の設定 */
		DMA_SetSH_CH1_Unit(DMA_SH_Cntrl[channel].Unit);

#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR1 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 *//* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR1 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
				DMA__CHCR1 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR1 &= ~CHCR_TE;
		DMA__CHCR1 |= CHCR_DE;
		break;
	case 2:
		/* 転送元アドレスの設定 */
		DMA__SAR2 = DMA_SH_Cntrl[channel].SrcAddress;
		/* 転送先アドレスの設定 */
		DMA__DAR2 = DMA_SH_Cntrl[channel].DstAddress;
		/* カウンタの設定 */
		DMA__TCR2 = DMA_SH_Cntrl[channel].Counter;
		/* 転送方向の設定 */
		DMA_SetSH_CH2_Direction(DMA_SH_Cntrl[channel].Direction);
		/* 転送単位の設定 */
		DMA_SetSH_CH2_Unit(DMA_SH_Cntrl[channel].Unit);
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
		if (DMA__CHCR2 & CHCR_TE) {
			DMA__CHCR2 &= ~CHCR_TE;
		}
		DMA__CHCR2 |= CHCR_IE;
#else
		DMA__CHCR2 &= ~CHCR_TE;
 #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/0129 */
		/* メモリメモリ転送 のときは立てとかないつ終わったか分からん。*/
		DMA__CHCR2 |= ( CHCR_RS_AUTO | CHCR_IE); /* オートリクエスト、終了割り込み許可*/
		SH__IPRC |= DMAC2_LEVEL; /* こんなところで割り込み順位を変えてごめんなさい。*/
 #endif
#endif
		DMA__CHCR2 |= CHCR_DE;
		break;
	case 3:
		/* 転送元アドレスの設定 */
		DMA__SAR3 = DMA_SH_Cntrl[channel].SrcAddress;
		/* 転送先アドレスの設定 */
		DMA__DAR3 = DMA_SH_Cntrl[channel].DstAddress;
		/* カウンタの設定 */
		DMA__TCR3 = DMA_SH_Cntrl[channel].Counter;
		/* 転送方向の設定 */
		DMA_SetSH_CH3_Direction(DMA_SH_Cntrl[channel].Direction);
		/* 転送単位の設定 */
		DMA_SetSH_CH3_Unit(DMA_SH_Cntrl[channel].Unit);

		DMA__CHCR3 &= ~CHCR_TE;
		DMA__CHCR3 |= CHCR_DE;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

}


/*************************************************************************
	module		:[SH内蔵DMACのオートイニシャライズを有効設定にします]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		DMA_SH_Cntrl.AutoInit
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SH_AutoInitializeEnable(UBYTE channel)
{
	DMA_SH_Cntrl[channel].AutoInit = AUTO_INITIALIZE_ON;
}


/*************************************************************************
	module		:[SH内蔵DMACのオートイニシャライズを無効設定にします]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		DMA_SH_Cntrl.AutoInit
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SH_AutoInitializeDisable(UBYTE channel)
{
	DMA_SH_Cntrl[channel].AutoInit = AUTO_INITIALIZE_OFF;
}


#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/0722 */
/*************************************************************************
	module		:[SH7043内蔵RAM 領域かどうかの判定]
	function	:[
		引数のアドレスが SH7043内蔵RAM 領域かどうかの判定
	]
	return		:[
			TRUE		内蔵 RAM 領域である
			FALSE		内蔵 RAM 領域でない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/08/10]
	author		:[久保博]
*************************************************************************/
UBYTE DMA_IsTheAddressInInternalRAM(UDWORD address)
{
	if (CAC_ADDRESS_ARRAY <= address) { /* とりあえず、内蔵RAM の先頭アドレスより大きければ真を返すことにします。*/
		return TRUE;
	}
	return FALSE;
}
#endif

#if  (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)  /* added by H.Kubo 1998/11/19 */
/*************************************************************************
	module		:[引数のチャンネルのDMA転送を継続]
	function	:[
		1.チャンネルコントロールレジスタのＤＥビットをセットする
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/14]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_ContinueInternalDMAU(UBYTE channel)
{
	/* 引数の内蔵ＤＭＡチャネルのＴＥフラグをクリアした後、動作許可する */
	switch (channel) {
	case 0:
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR0 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
				DMA__CHCR0 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 *//* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR0 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR0 &= ~CHCR_TE;
		DMA__CHCR0 |= CHCR_DE;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
		CodecREQC0_Enable(SCANNER_CODEC);	/*デバッグ用 By M.Kotani 1997/11/1*/
#endif
		break;
	case 1:
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR1 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 */ /* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR1 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
				DMA__CHCR1 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR1 &= ~CHCR_TE;
		DMA__CHCR1 |= CHCR_DE;
		break;
	case 2:
		DMA__CHCR2 &= ~CHCR_TE;
#if (PRO_MODEM == R288F) /* added by H.Kubo 1998/0129 */
		/* メモリメモリ転送 のときは立てとかないつ終わったか分からん。*/
		DMA__CHCR2 |= ( CHCR_RS_AUTO | CHCR_IE); /* オートリクエスト、終了割り込み許可*/
		SH__IPRC |= DMAC2_LEVEL; /* こんなところで割り込み順位を変えてごめんなさい。*/
#endif
		DMA__CHCR2 |= CHCR_DE;
		break;
	case 3:
		DMA__CHCR3 &= ~CHCR_TE;
		DMA__CHCR3 |= CHCR_DE;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}
#endif


#if defined(POPLAR_F)
/*************************************************************************
	module		:[SH7043内蔵DMACの引数のチャンネルをイネーブルにする]
	function	:[
		1.チャンネルコントロールレジスタのＤＥビットをセットする
		モデム専用
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1999/12/06]
	author		:[村田]
*************************************************************************/
void DMA_RequestEnableInternalDMAUSb(UBYTE channel)
{
	/* 転送元アドレスの設定 */
	DMA_SetSH_SAR(channel,DMA_SH_Cntrl[channel].SrcAddress);
	/* 転送先アドレスの設定 */
	DMA_SetSH_DAR(channel,DMA_SH_Cntrl[channel].DstAddress);
	/* カウンタの設定 */
	DMA_SetSH_TCR(channel,DMA_SH_Cntrl[channel].Counter);
	/* 転送方向の設定 */
	DMA_SetSH_CHCR_Direction(channel,DMA_SH_Cntrl[channel].Direction);
	/* 転送単位の設定 */
	DMA_SetSH_CHCR_Unit(channel,DMA_SH_Cntrl[channel].Unit);
}

void DMA_RequestEnableInternalDMAUGo(UBYTE channel)
{
	/* 引数の内蔵ＤＭＡチャネルのＴＥフラグをクリアした後、動作許可する */
	switch (channel) {
	case 0:
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR0 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
				DMA__CHCR0 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 */ /* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR0 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR0 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR0 &= ~CHCR_TE;
		DMA__CHCR0 |= CHCR_DE;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
		CodecREQC0_Enable(SCANNER_CODEC);	/*デバッグ用 By M.Kotani 1997/11/1*/
#endif
		break;
	case 1:
#if (PRO_SH2_INTERNAL_DMAC == COM_CODEC_DMA) /* 通信コーデックの DMA に SH 内蔵の DMAC を使う。Changed by H.Kubo 1998/08/10 */
		DMA__CHCR1 &= ~CHCR_RS_MASK;
		switch (DMA_SH_Cntrl[channel].Direction) {
		case DMA_IO_TO_MEMORY:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].DstAddress)) {
 #if defined(HINOKI) || defined(HINOKI2) || defined (SATSUKI2) || defined (STOCKHM2) || defined (HINOKI3) /* Debug by SMuratec 夏 2004/5/7 */  /* HINOKIはデュアルアドレスモード 1998/10/06 By H.Hirao */ /* HINOKI2 2001/11/13 T.Takagi */
 				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
 #else
				DMA__CHCR1 |= CHCR_RS_IO_MEM; /* シングルアドレスモードを選択 */
 #endif
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */ 
			}
			break;
		case DMA_MEMORY_TO_IO:
			if (!DMA_IsTheAddressInInternalRAM(DMA_SH_Cntrl[channel].SrcAddress)) {
				DMA__CHCR1 |= CHCR_RS_MEM_IO; /* シングルアドレスモードを選択 */
			}
			else {
				/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			}
			break;
		default:
			/* DMA__CHCR1 |= CHCR_RS_DUAL;*/ /* デュアルアドレスモードを選択 */
			break;
		}
#endif
		DMA__CHCR1 &= ~CHCR_TE;
		DMA__CHCR1 |= CHCR_DE;
		break;
	case 2:
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* クラス１とSH7043内蔵のシリアル有効 */
		if (DMA__CHCR2 & CHCR_TE) {
			DMA__CHCR2 &= ~CHCR_TE;
		}
		DMA__CHCR2 |= CHCR_IE;
#else
		DMA__CHCR2 &= ~CHCR_TE;
 #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/0129 */
		/* メモリメモリ転送 のときは立てとかないつ終わったか分からん。*/
		DMA__CHCR2 |= ( CHCR_RS_AUTO | CHCR_IE); /* オートリクエスト、終了割り込み許可*/
		SH__IPRC |= DMAC2_LEVEL; /* こんなところで割り込み順位を変えてごめんなさい。*/
 #endif
#endif
		DMA__CHCR2 |= CHCR_DE;
		break;
	case 3:
		DMA__CHCR3 &= ~CHCR_TE;
		DMA__CHCR3 |= CHCR_DE;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}

#endif
