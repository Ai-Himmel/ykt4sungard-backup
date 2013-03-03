/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/09/18
*        FILE NAME:  cdc_modr.c
*      DESCRIPTION:  松下製コーデックNM86064のMODR(モードレジスタ)を
*                    設定する為のファイル群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:  void CodecEncodeCodeByteSwapEnable(UBYTE codec_type);
*                    void CodecEncodeCodeByteSwapDisable(UBYTE codec_type);
*                    void CodecDecodeCodeByteSwapEnable(UBYTE codec_type);
*                    void CodecDecodeCodeByteSwapDisable(UBYTE codec_type);
*                    void CodecMODR_Enable(UBYTE codec_type);
*                    void CodecMODR_Disable(UBYTE codec_type);
*                    void CodecEXA_Enable(UBYTE codec_type);
*                    void CodecEXA_Disable(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"

/*************************************************************************
	module		:[
		符号化処理時の符号データにおいて（画像ではない）ワードデータの
		上位バイト、下位バイトを入れ替えするようにMODRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
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
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecEncodeCodeByteSwapEnable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= ENCSWAP_BIT;	/**符号化時符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		符号化処理時の符号データにおいて（画像ではない）ワードデータの
		上位バイト、下位バイトを入れ替えしないようにMODRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
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
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecEncodeCodeByteSwapDisable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~ENCSWAP_BIT;	/**符号化時符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		復号化処理時の符号データにおいて（画像ではない）ワードデータの
		上位バイト、下位バイトを入れ替えするようにMODRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
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
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecDecodeCodeByteSwapEnable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= DECSWAP_BIT;	/**復号化時符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		復号化処理時の符号データにおいて（画像ではない）ワードデータの
		上位バイト、下位バイトを入れ替えしないようにMODRを設定する
	]
	function	:[
		1.大域変数に上位下位をスワップするビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
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
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecDecodeCodeByteSwapDisable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~DECSWAP_BIT;	/**復号化時符号データバイト交換(0:入れ替えない, 1:入れ替える)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}



/*************************************************************************
	module		:[
		DTCRを無効としMODRを有効とするようにMODRを設定する
	]
	function	:[
		1.大域変数にMODRを有効にするビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecMODR_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MODRENB_BIT;	/**MODRの復号化時符号データバイト交換機能(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		DTCRを有効としMODRを無効とするようにMODRを設定する
	]
	function	:[
		1.大域変数にMODRを有効にするビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecMODR_Disable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MODRENB_BIT;	/**MODRの復号化時符号データバイト交換機能(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		外部アドレス拡張を有効とするようにMODRを設定する
	]
	function	:[
		1.大域変数にEXA0,1を有効にするビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecEXA_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= EXAENB_BIT;	/**外部アドレス拡張機能(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		外部アドレス拡張を無効とするようにMODRを設定する
	]
	function	:[
		1.大域変数にEXA1,0を有効にするビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecEXA_Disable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**MODR(モードレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~EXAENB_BIT;	/**外部アドレス拡張機能(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}

