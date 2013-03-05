/* Copied by T.Nose 1996/11/09 */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.11,1994
*        FILE NAME:  dma_dch.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DCHレジスタを制御する関数群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:  UBYTE CheckDMAU_DCH(UBYTE DMAUtype)
*                    void  SetDMAU_DCH(UBYTE DMAUtype, UBYTE data)
*                    UBYTE CheckDMA_Channel(UBYTE DMAUtype)
*                    UBYTE CheckDMA_AccessMethod(UBYTE DMAUtype)
*                    void  SetDMA_Channel(UBYTE DMAUtype, UBYTE channel)
*                    void  SetDMA_AccessMethod(UBYTE DMAUtype, UBYTE method)
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\cmn_pro.h"

#if (PRO_EXT_DMAC == ENABLE) /* ファイル内の関数全部 */

/*************************************************************************
	module		:[uPD71071のDCHレジスタを読み出します]
	function	:[
		1.uPD71071のDCHレジスタポートのアドレスをリードする
	]
	return		:[
		n:DCHの値
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
UBYTE CheckDMAU_DCH(void)
{
	return(inp(DMAU_DCH));
}


/*************************************************************************
	module		:[uPD71071のDCHレジスタに引数のデータを書き込みます]
	function	:[
		1.uPD71071のDCHレジスタポートのアドレスにアウトする
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
void SetDMAU_DCH(UBYTE data)		/*DCHの値*/
{
	outp(DMAU_DCH, data);
}


/*************************************************************************
	module		:[uPD71071のチャンネルをリターンします]
	function	:[
		1.uPD71071のDCHレジスタポートのアドレスをリードする
		2.ビットマスクして選択されているチャンネルを調べる
	]
	return		:[
		n<4:選択されているDMAのチャンネル
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
UBYTE CheckDMA_Channel(void)
{
	UBYTE dch;

	dch = CheckDMAU_DCH(); /*DMAUの種類*/
	if (dch & 0x01) {
		return(0);	/**チャンネル0が選択されている*/
	}
	if (dch & 0x02) {
		return(1);	/**チャンネル1が選択されている*/
	}
	if (dch & 0x04) {
		return(2);	/**チャンネル2が選択されている*/
	}
	if (dch & 0x08) {
		return(3);	/**チャンネル3が選択されている*/
	}
	return(4);/**エラー*/
}


/*************************************************************************
	module		:[uPD71071のアクセス条件をリターンします]
	function	:[
		1.uPD71071のDCHレジスタポートのアドレスをリードする
		2.ビットマスクして選択されているアクセス条件を調べる
	]
	return		:[
		0(READ_CURRENT_WRITE_BASE_CURRENT)
		:リード時：カレントのみ，ライト時：ベースとカレント
		1(READ_BASE_WRITE_BASE)
		:リード／ライトともベースのみ
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
UBYTE CheckDMA_AccessMethod(void)
{
	UBYTE dch;

	dch = CheckDMAU_DCH(); /*DMAUの種類*/
	if (dch & 0x10) {
		return(READ_BASE_WRITE_BASE);	/**リード／ライトともベースのみ*/
	}
	else {
		return(READ_CURRENT_WRITE_BASE_CURRENT);	/**リード時：カレントのみ，ライト時：ベースとカレント*/
	}
}


/*************************************************************************
	module		:[uPD71071のチャンネルをセットします]
	function	:[
		1.変数にチャンネルをセット
		2.変数に現状のアクセス条件をセット
		3.DCHのポートアドレスを選択して、アウトする
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
void SetDMA_Channel(UBYTE channel)		/*使用するDMAのチャンネル*/
{
	UBYTE dch;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	dch = channel;	/**使用チャンネルで初期化*/
	if (CheckDMA_AccessMethod()) {
		dch |= 0x04;	/**現状のアクセス条件をセット*/
	}
	SetDMAU_DCH(dch);
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}


/*************************************************************************
	module		:[uPD71071のアクセス条件をセットします]
	function	:[
		1.変数に現状のチャンネルをセット
		2.変数にアクセス条件をセット
		3.DCHのポートアドレスを選択して、アウトする
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
void SetDMA_AccessMethod(UBYTE method)		/*使用するDMAのアクセス条件*/
{
	UBYTE dch;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	dch = CheckDMA_Channel();	/**現状の使用チャンネルで初期化*/
	if (method == READ_BASE_WRITE_BASE) {
		dch |= 0x04;	/**アクセス条件をセット*/
	}
	SetDMAU_DCH(dch);
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}

#endif /* PRO_EXT_DMAC == ENABLE */
