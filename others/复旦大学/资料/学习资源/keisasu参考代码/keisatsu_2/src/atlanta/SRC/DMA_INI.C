/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : dma_ini.c                                                 */
/*  モジュ-ル    :                                                           */
/*  作成者       : 野瀬敏弘                                                  */
/*  日  付       : 96.11.09                                                  */
/*  概  要       : 外付けuPD71071のDMACを初期化する関数群                    */
/*  修正履歴     : ini_dmau.c,iniexdma.c から流用                            */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\sh7043\define\sh_port.h"

/* #if (PRO_KEYPANEL == PANEL_POPLAR_B) */
/* 外付けＤＭＡＣリセットハードウェアデバッグ T.Nose 1997/11/04 */
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_a.h"
#include "\src\atlanta\define\mntsw_h.h"

/* 参照していない。T.Nose 1998/06/03 */
/* #include "\src\atlanta\poplar_b\define\popb_sys.h" */

#include "\src\atlanta\ext_v\sys_port.h"
/* #endif */

#if (PRO_EXT_DMAC == ENABLE)
/************************************************************************
	module		:[外付けＤＭＡＣ初期化処理]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INI]
	date		:[1996/02/17]
	author		:[野瀬敏弘]
************************************************************************/
void INI_ExternalDMAC(void)
{
	UBYTE channel;

/*#if (PRO_KEYPANEL == PANEL_POPLAR_B)*//* POPLAR_Hも行う必要あり By M.Tachibana 1998/05/11 */
	UBYTE debug = 0;

	/* 外付けＤＭＡＣリセットハードウェアデバッグ T.Nose 1997/11/04 */
	SYS_ETC_PortStatus = (UWORD)0x0010; /* メインの初期化が走る前なので初期化する */
	outpw(ETC_PORT,SYS_ETC_PortStatus);
	while (debug < 10) { /* 10usec 以上wait */
		debug++;
	}
	SYS_ETC_PortStatus = (UWORD)0x0000;
	outpw(ETC_PORT,SYS_ETC_PortStatus);
/*#endif*/

	/*------------------------------------------------------------------*/
	/* 外部ＤＭＡＣ０イニシャルコマンドレジスタの設定                   */
	/* ・リセットビットセット                                           */
	/* ・データバス幅１６ビット                                         */
	/*------------------------------------------------------------------*/
	outp(DMAU_DICM,(DMAC_DICM_RES + DMAC_DICM_16WIDTH));
	/*------------------------------------------------------------------*/
	/* 外部ＤＭＡＣ０デバイスコントロールレジスタの設定                 */
	/* ・回転優先順位                                                   */
	/* ・拡張書き込み                                                   */
	/* ・バスリリースモード                                             */
	/* ・ベリファイ時でのウェイト許可                                   */
	/*------------------------------------------------------------------*/
	outp((DMAU_DDC_WORD - 1),(unsigned char)(DMAU_DDC_WORD_DATA >> 8));
	outp(DMAU_DDC_WORD,(unsigned char)DMAU_DDC_WORD_DATA);

	for (channel = 0; channel < 4; channel++) {
		DMA_SetV53DMA_Mode(channel, DMA_SINGLE_MODE);
	}

}
#endif
