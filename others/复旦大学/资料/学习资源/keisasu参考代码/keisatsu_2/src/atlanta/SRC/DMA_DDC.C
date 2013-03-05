/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.13,1994
*        FILE NAME:  dma_ddc.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DDCレジスタを制御する関数群
*  PUBLIC ROUTINES:  void         far  DMA_V53DMAU_Enable(unsigned char DMAUtype)
*                    void         far  DMA_V53DMAU_Disable(unsigned char DMAUtype)
* PRIVATE ROUTINES:  unsigned int near CheckDMAU_DDC(unsigned char DMAUtype)
*                    void         near SetDMAU_DDC(unsigned char DMAUtype, unsigned int data)
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\sh7043\define\sh_port.h"

#if (PRO_EXT_DMAC == ENABLE) /* ファイル内の関数全部 */
/*************************************************************************
	module		:[uPD71071のDDCレジスタを読み出します]
	function	:[
		1.引数のDDCレジスタポートのアドレスをリードする
	]
	return		:[
		n:DDCの値
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
UWORD CheckDMAU_DDC(void)
{
	UWORD ddc;

	ddc = (UWORD)inp(DMAU_DDC_WORD - 1);
	ddc <<= 8;
	ddc += (UWORD)inp(DMAU_DDC_WORD);
	return(ddc);
}


/*************************************************************************
	module		:[uPD71071のDDCレジスタをセットします]
	function	:[
		1.引数のDDCレジスタポートのアドレスにアウトする
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
void SetDMAU_DDC(UWORD data)		/*DDCの値*/
{
	outp((DMAU_DDC_WORD - 1),(unsigned char)(data >> 8));
	outp(DMAU_DDC_WORD,(unsigned char)data);
}


/*************************************************************************
	module		:[uPD71071のDMA転送を許可します]
	function	:[
		1.引数のDDCレジスタのポートへ書き込む
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		全チャンネルに影響するため注意すること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_V53DMAU_Enable(void)
{
	UWORD ddc;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	ddc = CheckDMAU_DDC();	/**現状のDDCで初期化*/
	ddc &= ~DDC_DDMA;	/**DMA動作禁止ビットを0にする*/
	SetDMAU_DDC(ddc);
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}


/*************************************************************************
	module		:[uPD71071のDMA転送を禁止します]
	function	:[
		1.引数のDDCレジスタのポートへ書き込む
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		全チャンネルに影響するため注意すること
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_V53DMAU_Disable(void)
{
	UWORD ddc;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	ddc = CheckDMAU_DDC();	/**現状のDDCで初期化*/
	ddc |= DDC_DDMA;	/**DMA動作禁止ビットを1にする*/
	SetDMAU_DDC(ddc);
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}

#endif /* PRO_EXT_DMAC == ENABLE */
