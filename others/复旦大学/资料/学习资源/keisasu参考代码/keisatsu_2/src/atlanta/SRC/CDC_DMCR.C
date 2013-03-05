/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/15
*        FILE NAME:  cdc_dmcr.c
*      DESCRIPTION:  松下製コーデックNM86063のDMCR(DMA転送コントロールレジスタ)を
*                    設定する為のファイル群
*  PUBLIC ROUTINES:  void AbortCodecDMA_Transfer(UBYTE codec_type, UBYTE channel);
*                    void CodecINTR2_Mask(UBYTE codec_type, UBYTE channel);
*                    void CodecINTR2_Enable(UBYTE codec_type, UBYTE channel);
* PRIVATE ROUTINES:  void CodecDMA_Enable(UBYTE codec_type, UBYTE channel);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"

/*************************************************************************
	module		:[指定されたコーデックのDMAを有効にする]
	function	:[
		1.指定されたコーデックのチャンネルのDMENBのビットをセットする
	]
	return		:[なし]
	common		:[
		CodecDMCR_DMIR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_main.c, cdc_stup.cからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecDMA_Enable(UBYTE codec_type,	/*使用するコーデック*/
					 UBYTE channel)		/*セットするチャンネル*/
{
	UWORD  int_enable;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	switch (channel) {
	case 0:
		CodecDMCR_DMIR_Status[codec_type] |= DMENB0_BIT;	/**0x0008 DMA0転送イネーブル*/
		break;
	case 1:
		CodecDMCR_DMIR_Status[codec_type] |= DMENB1_BIT;	/**0x0080 DMA1転送イネーブル*/
		break;
	default:
		break;
	}
	outp(CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1, (UBYTE)CodecDMCR_DMIR_Status[codec_type]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** 1997/08/28 割り込み許可*/
	}
}


/*************************************************************************
	module		:[指定されたコーデックのDMAを無効にする]
	function	:[
		1.指定されたコーデックのチャンネルのDMENBのビットをリセットする
	]
	return		:[なし]
	common		:[
		CodecDMCR_DMIR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		cdc_main.c, cdc_stup.cからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecDMA_Disable(UBYTE codec_type,	/*使用するコーデック*/
					  UBYTE channel)		/*セットするチャンネル*/
{
	UWORD  int_enable;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	switch (channel) {
	case 0:
		CodecDMCR_DMIR_Status[codec_type] &= ~DMENB0_BIT;	/**0x0008 DMA0転送ディスエーブル*/
		break;
	case 1:
		CodecDMCR_DMIR_Status[codec_type] &= ~DMENB1_BIT;	/**0x0080 DMA1転送ディスエーブル*/
		break;
	default:
		break;
	}
	outp(CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1, (UBYTE)CodecDMCR_DMIR_Status[codec_type]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** 1997/08/28 割り込み許可*/
	}
}


/*************************************************************************
	module		:[DMA転送を異常終了する]
	function	:[
		1.指定されたコーデックのチャンネルのDMABTのビットをセットする
	]
	return		:[なし]
	common		:[
		CodecDMCR_DMIR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void AbortCodecDMA_Transfer(UBYTE codec_type,	/*使用するコーデック*/
							UBYTE channel)	 	/*セットするチャンネル*/
{
	UWORD  int_enable;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	switch (channel) {
	case 0:
		CodecDMCR_DMIR_Status[codec_type] |= DMABT0_BIT;	/**0x0004 DMA0転送アボート(0:通常, 1:アボート)*/
		break;
	case 1:
		CodecDMCR_DMIR_Status[codec_type] |= DMABT1_BIT;	/**0x0040 DMA1転送アボート(0:通常, 1:アボート)*/
		break;
	default:
		break;
	}
	outp(CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1, (UBYTE)CodecDMCR_DMIR_Status[codec_type]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}
}


/*************************************************************************
	module		:[DMAブロック転送終了時の割り込みINTR2をマスクする]
	function	:[
		1.指定されたコーデックのチャンネルのMBENDのビットをクリアする
	]
	return		:[なし]
	common		:[
		CodecDMCR_DMIR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[参考関数(未使用)]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecINTR2_Mask(UBYTE codec_type,	/*使用するコーデック*/
					 UBYTE channel)	  	/*セットするチャンネル*/
{
	UWORD  int_enable;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	switch (channel) {
	case 0:
		CodecDMCR_DMIR_Status[codec_type] &= ~MBEND0_BIT;	/**0x0002 DBEND0マスク(0:割り込みマスク, 1:割り込み許可)*/
		break;
	case 1:
		CodecDMCR_DMIR_Status[codec_type] &= ~MBEND1_BIT;	/**0x0020 DBEND1マスク(0:割り込みマスク, 1:割り込み許可)*/
		break;
	default:
		break;
	}
	outp(CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1, (UBYTE)CodecDMCR_DMIR_Status[codec_type]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}
}


/*************************************************************************
	module		:[DMAブロック転送終了時の割り込みINTR2を許可する]
	function	:[
		1.指定されたコーデックのチャンネルのMBENDのビットをセットする
	]
	return		:[なし]
	common		:[
		CodecDMCR_DMIR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecINTR2_Enable(UBYTE codec_type,	/*使用するコーデック*/
					   UBYTE channel)		/*セットするチャンネル*/
{
	UWORD  int_enable;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	switch (channel) {
	case 0:
		CodecDMCR_DMIR_Status[codec_type] |= MBEND0_BIT;	/**0x0002 DBEND0マスク(0:割り込みマスク, 1:割り込み許可)*/
		break;
	case 1:
		CodecDMCR_DMIR_Status[codec_type] |= MBEND1_BIT;	/**0x0020 DBEND1マスク(0:割り込みマスク, 1:割り込み許可)*/
		break;
	default:
		break;
	}
	outp(CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1, (UBYTE)CodecDMCR_DMIR_Status[codec_type]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}
}


/*************************************************************************
	module		:[コーデックのチップがMN86064かどうかを判断する]
	function	:[
		1.指定されたコーデックのDMCRのBit0をチェックする
	]
	return		:[なし]
	common		:[
		CodecDMCR_DMIR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
UWORD CDC_CheckMN86064(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD  int_enable;
	UWORD  result;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	result = 0;
	int_enable = CheckInterruptEnable();	/**現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態*/
	CMN_DisableInterrupt();	/** 1997/08/28 割り込み禁止*/
	CodecDMCR_DMIR_Status[codec_type] &= 0xFF00;	/**下位クリア*/
	CodecDMCR_DMIR_Status[codec_type] |= inp((CodecRegisterAddressTable[codec_type][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
	if (CodecDMCR_DMIR_Status[codec_type] & 0x0001) {
		result = 1;
	}
	if (int_enable) {	/**割り込み禁しに変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/** Sep.23,1994 割り込み許可*/
	}
	return (result);
}
