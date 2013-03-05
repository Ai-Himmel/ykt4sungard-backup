/* Copied by T.Nose 1996/11/09 */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.13,1994
*        FILE NAME:  dma_dmk.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DMKレジスタを制御する関数群
*  PUBLIC ROUTINES:  void  DMA_ExternalRequestMask(UBYTE channel)
*                    void  DMA_RequestEnable(UBYTE channel)
* PRIVATE ROUTINES:  UBYTE CheckDMAU_DMK(void)
*                    void  SetDMAU_DMK(UBYTE data)
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\cmn_pro.h"

#if (PRO_EXT_DMAC == ENABLE) /* ファイル内の関数全部 */

/*************************************************************************
	module		:[uPD71071のDMKレジスタを読み出します]
	function	:[
		1.DMKレジスタポートのアドレスをリードする
	]
	return		:[
		n:DMKの値
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/09]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CheckDMAU_DMK(void)
{
	return(inp(DMAU_DMK));
}


/*************************************************************************
	module		:[uPD71071のDMKレジスタをセットします]
	function	:[
		1.DMKレジスタポートのアドレスにアウトする
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
void SetDMAU_DMK(UBYTE data)		/*DMKの値*/
{
	outp(DMAU_DMK, data);
}


/*************************************************************************
	module		:[uPD71071の引数のチャンネルのDMARQをマスクします]
	function	:[
		1.引数のDMKレジスタのポートへ書き込む
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
void DMA_RequestMaskExternalDMAU(UBYTE channel)		/*マスクするチャンネル*/
{
	UBYTE dmk;

	DMA_V53DMAU_Disable();	/*DMAUのSTOP*/
	dmk = CheckDMAU_DMK();	/**現状のDMKで初期化*/
	switch (channel) {
	case 0:
		dmk |= 0x01;
		break;
	case 1:
		dmk |= 0x02;
		break;
	case 2:
		dmk |= 0x04;
		break;
	case 3:
		dmk |= 0x08;
		break;
	default:
		break;
	}
	SetDMAU_DMK(dmk);
	DMA_V53DMAU_Enable();	/*DMAUのSTART*/
}


/*************************************************************************
	module		:[uPD71071の引数のチャンネルのDMARQを有効にします]
	function	:[
		1.DMKレジスタのポートへ書き込む
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
void DMA_RequestEnableExternalDMAU(UBYTE channel)	/*有効にするチャンネル*/
{
	UBYTE dmk;

	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
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
