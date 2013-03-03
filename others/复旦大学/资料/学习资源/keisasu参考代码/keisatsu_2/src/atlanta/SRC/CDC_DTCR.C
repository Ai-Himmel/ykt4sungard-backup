/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/15
*        FILE NAME:  cdc_dtcr.c
*      DESCRIPTION:  松下製コーデックNM86063のDTCR(データコントロールレジスタ)を
*                    設定する為のファイル群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:  void CodecImageByteSwapEnable(UBYTE codec_type);
*                    void CodecImageByteSwapDisable(UBYTE codec_type);
*                    void CodecCodeByteSwapEnable(UBYTE codec_type);
*                    void CodecCodeByteSwapDisable(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"

/*************************************************************************
	module		:[
		画像データにおいて（符号ではない）ワードデータの
		上位バイト、下位バイトを入れ替えするようにDTCRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		符号データには無効である
		キャラクタプリントのときに使用される
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecImageByteSwapEnable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**DTCR(データコントロールレジスタ)を設定する*/
	CodecMSCR_DTCR_Status[codec_type] |= BESWP0_BIT;	/**画像データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		画像データにおいて（符号ではない）ワードデータの
		上位バイト、下位バイトを入れ替えしないようにDTCRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		符号データには無効である
		通常のときに使用される
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecImageByteSwapDisable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**DTCR(データコントロールレジスタ)を設定する*/
	CodecMSCR_DTCR_Status[codec_type] &= ~BESWP0_BIT;	/**画像データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		符号データにおいて（画像ではない）ワードデータの
		上位バイト、下位バイトを入れ替えするようにDTCRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		画像データには無効である
		通常プリントのときに使用される
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecCodeByteSwapEnable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**DTCR(データコントロールレジスタ)を設定する*/
	CodecMSCR_DTCR_Status[codec_type] |= BCSWAP_BIT;	/**画像データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		符号データにおいて（画像ではない）ワードデータの
		上位バイト、下位バイトを入れ替えしないようにDTCRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecMSCR_DTCR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		画像データには無効である
		ＧＤＩのときに使用される
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/15]
	author		:[小谷正樹]
*************************************************************************/
void CodecCodeByteSwapDisable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**DTCR(データコントロールレジスタ)を設定する*/
	CodecMSCR_DTCR_Status[codec_type] &= ~BCSWAP_BIT;	/**画像データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR], CodecMSCR_DTCR_Status[codec_type]);
}

