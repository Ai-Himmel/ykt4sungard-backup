/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.11,1994
*        FILE NAME:  dma_dbcc.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DBC/DCCレジスタを制御する関数群
*  PUBLIC ROUTINES:  unsigned int  far  DMA_CheckDMA_BaseCounter(unsigned char DMAUtype)
*                    unsigned int  far  DMA_CheckDMA_CurrentCounter(unsigned char DMAUtype)
*                    void          far  DMA_SetDMA_BaseCounter(unsigned char DMAUtype, unsigned int count)
*                    void          far  DMA_SetDMA_BaseCurrentCounter(unsigned char DMAUtype, unsigned int count)
* PRIVATE ROUTINES:  unsigned int  near CheckDMAU_DBC_DCC(unsigned char DMAUtype)
*                    void          near SetDMAU_DBC_DCC(unsigned char DMAUtype, unsigned int data)
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\cmn_pro.h"

#if (PRO_EXT_DMAC == ENABLE) /* ファイル内の関数全部 */

/*************************************************************************
	module		:[uPD71071のDBC/DCCレジスタを読み出します]
	function	:[
		1.引数のDBC/DCCレジスタポートのアドレスをリードする
	]
	return		:[
		n:DBC/DCCの値
	]
	common		:[なし]
	condition	:[
		チャンネル、アクセス条件が設定されていること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
UWORD CheckDMAU_DBC_DCC(void)
{
	UWORD data;

	data = (UWORD)inp(DMAU_DBC_DCC_WORD - 1);
	data <<= 8;
	data += (UWORD)inp(DMAU_DBC_DCC_WORD);
	return(data);
}


/*************************************************************************
	module		:[uPD71071のDBC/DCCレジスタをセットします]
	function	:[
		1.引数のDBC/DCCレジスタポートのアドレスにアウトする
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		チャンネル、アクセス条件が設定されていること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void SetDMAU_DBC_DCC(UWORD data)		/*DMA転送回数*/
{
	outp((DMAU_DBC_DCC_WORD - 1), (UBYTE)(data >> 8));
	outp(DMAU_DBC_DCC_WORD, (UBYTE)data);
}


/*************************************************************************
	module		:[uPD71071のDBCレジスタを読み出します]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をベースレジスタ読みだしに設定する
		3.DBC/DCCレジスタのポートを読みだす
	]
	return		:[
		n>=0:設定されているDMA転送回数
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
UWORD DMA_CheckDMA_BaseCounter(UBYTE channel)	/*DMAチャンネル*/
{
	UWORD result;
	UBYTE dch;
	UWORD  int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	dch = channel;
	dch |= 0x04;	/**アクセス条件をセット*/
	SetDMAU_DCH(dch);
	result = CheckDMAU_DBC_DCC();
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
	return(result);
}


/*************************************************************************
	module		:[uPD71071のDMAUのDCCレジスタを読み出します]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をカレントレジスタ読みだしに設定する
		3.DBC/DCCレジスタのポートを読みだす
	]
	return		:[
		n>=0:残りのDMA転送回数
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
UWORD DMA_CheckDMA_CurrentCounter(UBYTE channel)		/*DMAチャンネル*/
{
	UWORD result;

	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	result = CheckDMAU_DBC_DCC();
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	return(result);
}
/*************************************************************************
	module		:[uPD71071のDMAUのDBCレジスタをセットします]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をベースレジスタのみ書き込みに設定する
		3.DBC/DCCレジスタのポートへ書き込む
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
void DMA_SetDMA_BaseCounter(UBYTE channel,	/*DMAチャンネル*/
							UWORD count)		/*DMA転送回数*/
{
	UBYTE dch;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	dch = channel;
	dch |= 0x04;	/**アクセス条件をセット*/
	SetDMAU_DCH(dch);
	SetDMAU_DBC_DCC(count);	/**DBC_DCCレジスタのセット*/
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}


/*************************************************************************
	module		:[uPD71071のDMAUのDBC&DCCレジスタをセットします]
	function	:[
		1.使用するDMAチャンネルを設定する
		2.使用するDMAレジスタのアクセス条件をベース&カレントレジスタ書き込みに設定する
		3.DBC/DCCレジスタのポートへ書き込む
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
void DMA_SetDMA_BaseCurrentCounter(UBYTE channel,	/*DMAチャンネル*/
									UWORD  count)		/*DMA転送回数*/
{
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	SetDMAU_DBC_DCC(count);	/**DBC_DCCレジスタのセット*/
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}

#endif /* PRO_EXT_DMAC == ENABLE */
