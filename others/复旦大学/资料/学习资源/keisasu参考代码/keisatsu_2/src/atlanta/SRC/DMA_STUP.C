/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.14,1994
*        FILE NAME:  dma_stup.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACを制御するための
*                    大機能間インターフェイス関数群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:  システムのDMAを使用する時,外部からはこのファイルの関数をCallする
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\std.h"
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
#include "\src\atlanta\define\mntsw_g.h"	/* added by H.Hirao 1999/01/23 */
#include "\src\atlanta\ext_v\bkupram.h"	/* added by H.Hirao 1999/01/23 */
#endif

/*************************************************************************
	module		:[引数のＤＭＡＵをセットアップします]
	function	:[
		1.アドレスレジスタを設定する
		2.カウントレジスタを設定する
		3.転送単位を設定する
		4.転送方向を設定する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/09]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void  DMA_SetupDMAUFlsRom(struct DMA_Data_t *dma)	/*DMAの設定データブロック*/
#else
void  DMA_SetupDMAU(struct DMA_Data_t *dma)	/*DMAの設定データブロック*/
#endif
{
	UWORD int_enable;

	DMA_RequestMask(dma->Channel);
	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	DMA_SetDMA_Direction(dma->Channel, dma->Direction);		/* 転送方向を設定する */
	DMA_SetDMA_Address(dma->Channel, dma->Direction, dma->SrcAddress);	/* アドレスレジスタを設定する*/
	DMA_SetDMA_Counter(dma->Channel, dma->Counter);		/* カウントレジスタを設定する*/
	DMA_SetDMA_Unit(dma->Channel, dma->Unit);			/* 転送単位を設定する*/
#else
	/* ＤＭＡを使うかＤＴＣを使うかチェックする */
	if (DMA_ChannelCheck(dma->Channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_SetDMA_Direction(dma->Channel, dma->Direction);		/* 転送方向を設定する */
		DMA_SetDMA_Address(dma->Channel, dma->Direction, dma->SrcAddress);	/* アドレスレジスタを設定する*/
		DMA_SetDMA_Counter(dma->Channel, dma->Counter);		/* カウントレジスタを設定する*/
		DMA_SetDMA_Unit(dma->Channel, dma->Unit);			/* 転送単位を設定する*/
	}
	else {	/* ＤＴＣを使用する場合 */
 #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		/*-----------------------------------------------------------------
		** ここでは、DTC用Channelの値には書き換えません。
		** DMAtoDTC_SetupDTC()の中でChannel/SrcAddress/DstAddressの値をDTC用に変換するようにします。
		*/
		DMAtoDTC_SetupDTC(dma);
 #else
		if (dma->Channel == DMA_MDM_MDMBUF_CH) {
			dma->Channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
			DMAtoDTC_SetupDTC(dma);
		}
		else if (dma->Channel == DMA_MPC_MPCBUF_CH) {
			dma->Channel = DTC_INTERRUPT_CH2;		/* CLASS1 */
			DMAtoDTC_SetupDTC(dma);
		}
 #endif
 	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/* 割り込み許可*/
	}
}


/*************************************************************************
	module		:[DMA転送を再スタートします]
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
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void DMA_RestartDMAUFlsRom(UBYTE channel,		/* DMAチャンネル */
					 	   UBYTE direction,	/* DMA転送方向 */
						   UWORD count,		/* DMA転送回数 */
					       UDWORD address)	/* DMAアドレス */
#else
void DMA_RestartDMAU(UBYTE channel,		/* DMAチャンネル */
					 UBYTE direction,	/* DMA転送方向 */
					 UWORD count,		/* DMA転送回数 */
					 UDWORD address)	/* DMAアドレス */
#endif
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_RestartInternalDMAU(channel,direction,(UDWORD)count,address);
	}
	else {
		DMA_RestartExternalDMAU(channel - DMA_INTERNAL_CH_MAX,count - 1,address);
	}
#else
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_RestartInternalDMAU(channel,direction,(UDWORD)count,address);
	}
	else {
 #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		/*-----------------------------------------------------------------
		** ここでは、DTC用Channelの値には書き換えません。
		** DMAtoDTC_SetupDTC()の中でChannel/SrcAddress/DstAddressの値をDTC用に変換するようにします。
		*/
		DMAtoDTC_Restart(channel,direction, count,address);	/* DMA再起動のパスでDTCを起動 */
 #else
		if (channel == DMA_MDM_MDMBUF_CH) {
			channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
		}
		else if (channel == DMA_MPC_MPCBUF_CH) {
			channel = DTC_INTERRUPT_CH2;	/* CLASS1 */
		}
		DMAtoDTC_Restart(channel,direction, count,address);	/* DMA再起動のパスでDTCを起動 */
  #endif
	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


#if (PRO_EXT_DMAC == ENABLE)
/*************************************************************************
	module		:[uPD71071を再スタートします]
	function	:[
		1.ベース＆カレントアドレスレジスタを設定する
		2.ベース＆カレントカウントレジスタを設定する
		3.マスクを解除する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_RestartExternalDMAU(UBYTE channel,		/* DMAチャンネル */
					 		 UWORD count,		/* DMA転送回数 */
					 		 UDWORD address)	/* DMAアドレス */
{
	UBYTE dmk;

	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	SetDMAU_DBA_DCA(address);	/**DBA_DCAレジスタのセット*/
	SetDMAU_DBC_DCC(count);	/**DBC_DCCレジスタのセット*/
	dmk = CheckDMAU_DMK();	/**現状のDMKで初期化*/
	switch (channel) {
	case 0:
		dmk &= ~0x01;
		break;
	case 1:
		dmk &= ~0x02;
		break;
	case 2:
		dmk &= ~0x04;
		break;
	case 3:
		dmk &= ~0x08;
		break;
	default:
		break;
	}
	SetDMAU_DMK(dmk);
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}
#endif /* PRO_EXT_DMAC == ENABLE */

#if (PRO_EXT_DMAC == DISABLE)
  #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
/*************************************************************************
	module		:[ＤＭＡを使うかＤＴＣを使うかチェックする]
	function	:[
		1.チャンネルを見てＤＭＡｏｒＤＴＣを判断する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/16]
	author		:[山口]
*************************************************************************/
UBYTE	DMA_ChannelCheck(UBYTE channel)
{

    /* #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) || (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) @* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */ /* Add HINOKI 1998/09/29 H.Hirao */
    #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)	/* by H.Hirao 1999/01/13 */

	switch (channel) {
	case	DMA_COMCDC_DRAM_CH:
	case	DMA_DRAM_COMCDC_CH:
	case	DMA_MEMORY_TO_MEMORY_CH: /* added by H.Kubo 1998/10/20 */
		return(YES);
		break;
	case	DMA_SCNCDC_DRAM_CH:
	case	DMA_DRAM_PRNCDC_CH:
	case	DMA_MDM_MDMBUF_CH:
	case	DMA_MPC_MPCBUF_CH:	/* CLASS1 */
	case	DMA_MDMBUF_MDM_CH:	/* Add 1998/09/29 By H.Hirao */
		return (NO);
		break;
	default:	/* ここに来たらバグ */
		break;
	}

	#elif (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)	/* by H.Hirao 1999/01/13 */

	switch (channel) {
	case	DMA_COMCDC_DRAM_CH:
	case	DMA_DRAM_COMCDC_CH:
	case	DMA_MEMORY_TO_MEMORY_CH: /* added by H.Kubo 1998/10/20 */
		return(YES);
		break;
	case	DMA_MPC_MPCBUF_CH:	/* CLASS1 added by H.Hirao 1999/01/13 */
   #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */

		if (SYB_MaintenanceSwitch[MNT_SW_G2] & 0x02) {	/* ＤＭＡ／ＤＴＣをスイッチで切り替える by H.Hirao 1999/01/23 */
			return (NO);
		}
		else {
			return(YES);
		}
   #else
		return (YES);
   #endif
		break;
	case	DMA_SCNCDC_DRAM_CH:
	case	DMA_DRAM_PRNCDC_CH:
	case	DMA_MDM_MDMBUF_CH:
	case	DMA_MDMBUF_MDM_CH:	/* Add 1998/09/29 By H.Hirao */
	case	DMA_GATEARRAYWRITE_CH:	/* プリンタイメージバッファ → Ｇ／Ａ 1998/10/26 by T.Soneoka */
		return (NO);
		break;
	default:	/* ここに来たらバグ */
		break;
	}
	
    #endif

}
  #else	/* 1998/10/15 H.Yoshikawa */
/*************************************************************************
	module		:[ＤＭＡを使うかＤＴＣを使うかチェックする]
	function	:[
		1.チャンネルを見てＤＭＡｏｒＤＴＣを判断する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/16]
	author		:[山口]
*************************************************************************/
UBYTE	DMA_ChannelCheck(UBYTE channel)
{

	switch (channel) {
	case	DMA_SCNCDC_DRAM_CH:
	case	DMA_DRAM_PRNCDC_CH:
	case	DMA_COMCDC_DRAM_CH:
	case	DMA_DRAM_COMCDC_CH:
		return(YES);
		break;
	case	DMA_MDM_MDMBUF_CH:
	case	DMA_MPC_MPCBUF_CH:	/* CLASS1 */
		return (NO);
		break;
	default:	/* ここに来たらバグ */
		break;
	}

}
  #endif
#endif
