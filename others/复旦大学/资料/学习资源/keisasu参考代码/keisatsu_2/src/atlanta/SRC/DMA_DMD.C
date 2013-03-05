/* Copied by T.Nose 1996/11/09 */
/************************************************************************
*               BY:  M.Kotani
*             DATE:  Jan.13,1994
*        FILE NAME:  dma_dmd.c
*       Task ID No:
*      DESCRIPTION:  V53内蔵および、外付けuPD71071のDMACの
*                    DMDレジスタを制御する関数群
*  PUBLIC ROUTINES:  void DMA_SetV53DMA_Unit(UBYTE channel,UBYTE unit)
*                    void DMA_AutoInitializeEnable(unsigned char DMAUtype, unsigned char channel)
*                    void DMA_AutoInitializeDisable(unsigned char DMAUtype, unsigned char channel)
*                    void DMA_SetV53DMA_Direction(UBYTE channel, UBYTE dir)
*                    void DMA_SetV53DMA_Mode(UBYTE channel, UBYTE mode)
* PRIVATE ROUTINES:  UBYTE CheckDMAU_DMD(void)
*                    void SetDMAU_DMD(UBYTE data)
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
	module		:[uPD71071のDMDレジスタを読み出します]
	function	:[
		1.DMDレジスタポートのアドレスをリードする
	]
	return		:[
		n:DMDの値
	]
	common		:[なし]
	condition	:[
		チャンネルが設定されていること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/09]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CheckDMAU_DMD(void)
{
	return(inp(DMAU_DMD));
}


/*************************************************************************
	module		:[uPD71071のDMDレジスタをセットします]
	function	:[
		1.DMDレジスタポートのアドレスにアウトする
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		チャンネルが設定されていること
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/09]
	author		:[野瀬敏弘]
*************************************************************************/
void SetDMAU_DMD(UBYTE data)		/*DMDの値*/
{
	outp(DMAU_DMD, data);
}


/*************************************************************************
	module		:[uPD71071の転送単位をセットします]
	function	:[
		1.DMAチャンネルを設定します
		2.引数のDMDレジスタのポートへ書き込む
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
void DMA_SetV53DMA_Unit(UBYTE channel,	/*DMAチャンネル*/
						UBYTE unit)		/*DMAの転送単位*/
{
	UBYTE dmd;

	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	dmd = CheckDMAU_DMD();	/**現状のDMDで初期化*/
	if (unit == DMA_WORD_TRANSFER) {	/**ワード転送の場合*/
		dmd |= DMD_W_B;
	}
	else {
		dmd &= ~DMD_W_B;	/**バイト転送の場合*/
	}
	SetDMAU_DMD(dmd);
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}

/*************************************************************************
	module		:[引数のDMAUのオートイニシャライズを許可します]
	function	:[
		1.DMAチャンネルを設定します
		2.引数のDMDレジスタのポートへ書き込む
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[DMA]
	date		:[1994/01/13]
	author		:[小谷正樹]
*************************************************************************/
void DMA_V53_AutoInitializeEnable(UBYTE channel)	/*DMAチャンネル*/
{
	UBYTE dmd;

	DMA_STOP_MASTER_DMAU();		/*DMAUのSTOP*/

	SetDMAU_DCH(channel);		/**チャンネルとアクセス条件をセット*/
	dmd = CheckDMAU_DMD();		/**現状のDMCで初期化*/
	dmd |= DMD_AUTI;			/**オートイニシャライズビットをセットする*/
	SetDMAU_DMD(dmd);

	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}


/*************************************************************************
	module		:[引数のDMAUのオートイニシャライズを禁止します]
	function	:[
		1.DMAチャンネルを設定します
		2.引数のDMDレジスタのポートへ書き込む
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[DMA]
	date		:[1994/01/13]
	author		:[小谷正樹]
*************************************************************************/
void DMA_V53_AutoInitializeDisable(UBYTE channel)	/*DMAチャンネル*/
{
	UBYTE dmd;

	DMA_STOP_MASTER_DMAU();		/*DMAUのSTOP*/

	SetDMAU_DCH(channel);		/**チャンネルとアクセス条件をセット*/
	dmd = CheckDMAU_DMD();		/**現状のDMCで初期化*/
	dmd &= ~DMD_AUTI;			/**オートイニシャライズビットをクリアする*/
	SetDMAU_DMD(dmd);

	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}


/*************************************************************************
	module		:[uPD71071の転送方向をセットします]
	function	:[
		1.DMAチャンネルを設定します
		2.引数のDMDレジスタのポートへ書き込む
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
void DMA_SetV53DMA_Direction(UBYTE channel,		/*DMAチャンネル*/
							UBYTE dir)			/*DMAの転送方向*/
{
	UBYTE dmd;

	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	dmd = CheckDMAU_DMD();	/**現状のDMDで初期化*/
	if (dir == DMA_VERIFY) {	/**ベリファイ(アドレス出力のみ)の場合*/
		dmd &= ~(DMD_TDIR_LOWER | DMD_TDIR_UPPER);	/**00=Verify*/
	}
	if (dir == DMA_IO_TO_MEMORY) {	/**I/O -> メモリ*/
		dmd |= DMD_TDIR_LOWER;	/**01=I/O->Memory*/
		dmd &= ~DMD_TDIR_UPPER;
	}
	if (dir == DMA_MEMORY_TO_IO) {	/**メモリ -> I/O*/
		dmd &= ~DMD_TDIR_LOWER;	/**10=Memory->I/O*/
		dmd |= DMD_TDIR_UPPER;
	}
	SetDMAU_DMD(dmd);
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
}


/*************************************************************************
	module		:[uPD71071のDMAUの転送モードをセットします]
	function	:[
		1.引数のDMDレジスタのポートへ書き込む
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
void DMA_SetV53DMA_Mode(UBYTE channel,	/*DMAチャンネル*/
						UBYTE mode)		/*DMA Mode*/
{
	UBYTE dmd;
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/**割り込み禁止*/
	DMA_STOP_MASTER_DMAU();	/*DMAUのSTOP*/
	SetDMAU_DCH(channel);	/**チャンネルとアクセス条件をセット*/
	dmd = CheckDMAU_DMD();	/**現状のDMDで初期化*/
	if (mode == DMA_DEMAND_MODE) {	/**ベリファイ(アドレス出力のみ)の場合*/
		dmd &= ~(DMD_TMODE_LOWER | DMD_TMODE_UPPER);	/**00=Demand Mode*/
	}
	if (mode == DMA_SINGLE_MODE) {	/**Single Mode*/
		dmd |= DMD_TMODE_LOWER;	/**01=Single Mode*/
		dmd &= ~DMD_TMODE_UPPER;
	}
	if (mode == DMA_BLOCK_MODE) {	/**Block Mode*/
		dmd &= ~DMD_TMODE_LOWER;	/**10=Block Mode*/
		dmd |= DMD_TMODE_UPPER;
	}
	if (mode == DMA_CASCADE_MODE) {	/**Cascade Mode*/
		dmd |= (DMD_TMODE_LOWER | DMD_TMODE_UPPER);	/**11=Cascade Mode*/
	}
	SetDMAU_DMD(dmd);
	DMA_START_MASTER_DMAU();	/*DMAUのSTART*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/**割り込み許可*/
	}
}

#endif /* PRO_EXT_DMAC == ENABLE */
