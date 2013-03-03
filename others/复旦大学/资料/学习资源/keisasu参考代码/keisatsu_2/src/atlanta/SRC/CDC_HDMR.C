/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/09/18
*        FILE NAME:  cdc_hdmr.c
*      DESCRIPTION:  松下製コーデックNM86063のHDMR(ハードマスクレジスタ)を
*                    設定する為のファイル群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:  void CodecHDMR_Enable(UBYTE codec_type);
*                    void CodecHDMR_Disable(UBYTE codec_type);
*                    void CodecINTR0_Mask(UBYTE codec_type);
*                    void CodecINTR0_Enable(UBYTE codec_type);
*                    void CodecINTR1_Mask(UBYTE codec_type);
*                    void CodecINTR1_Enable(UBYTE codec_type);
*                    void CodecREQC0_Mask(UBYTE codec_type);
*                    void CodecREQC0_Enable(UBYTE codec_type);
*                    void CodecREQC1_Mask(UBYTE codec_type);
*                    void CodecREQC1_Enable(UBYTE codec_type);
*                    void CodecREQD0_Mask(UBYTE codec_type);
*                    void CodecREQD0_Enable(UBYTE codec_type);
*                    void CodecREQD1_Mask(UBYTE codec_type);
*                    void CodecREQD1_Enable(UBYTE codec_type);
*                    void CodecREQOR_Disable(UBYTE codec_type);
*                    void CodecREQOR_Enable(UBYTE codec_type);
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"

/*************************************************************************
	module		:[
		システムバス側の出力信号をマスクする為の
		ハードマスク機能を有効にするようにHDMRを設定する
	]
	function	:[
		1.大域変数にハードマスク有効ビットをセットする
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
void CodecHDMR_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= HDENB_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		システムバス側の出力信号をマスクする為の
		ハードマスク機能を無効にするようにHDMRを設定する
	]
	function	:[
		1.大域変数にハードマスク有効ビットをクリアする
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
void CodecHDMR_Disable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~HDENB_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		INTR0をマスクするようにHDMRを設定する
	]
	function	:[
		1.大域変数にINTR0マスクビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecINTR0_Mask(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MINTR0_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		INTR0をマスク解除するようにHDMRを設定する
	]
	function	:[
		1.大域変数にINTR0マスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecINTR0_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MINTR0_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		INTR1をマスクするようにHDMRを設定する
	]
	function	:[
		1.大域変数にINTR1マスクビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecINTR1_Mask(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MINTR1_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		INTR1をマスク解除するようにHDMRを設定する
	]
	function	:[
		1.大域変数にINTR1マスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecINTR1_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MINTR1_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQC0をマスクするようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQC0マスクビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQC0_Mask(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MREQC0_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQC0をマスク解除するようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQC0マスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQC0_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MREQC0_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQC1をマスクするようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQC1マスクビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQC1_Mask(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MREQC1_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQC1をマスク解除するようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQC1マスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQC1_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MREQC1_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQD0をマスクするようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQD0マスクビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQD0_Mask(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MREQD0_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQD0をマスク解除するようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQD0マスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQD0_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MREQD0_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQD1をマスクするようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQD1マスクビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQD1_Mask(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~MREQD1_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQD1をマスク解除するようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQD1マスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQD1_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= MREQD1_BIT;	/**ハードマスク有効(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQORが有効になるようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQORビットをセットする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQOR_Enable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] |= REQOR_BIT;	/**OR処理(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}


/*************************************************************************
	module		:[
		REQORが無効になるようにHDMRを設定する
	]
	function	:[
		1.大域変数にREQORマスクビットをクリアする
		2.設定値をポートに出力する
	]
	return		:[なし]
	common		:[
		CodecHDMR_MODR_Status
		CodecRegisterAddressTable
	]
	condition	:[
		ハードマスク機能が有効になっていること
	]
	comment		:[
		MN86064のみで有効である
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/09/18]
	author		:[小谷正樹]
*************************************************************************/
void CodecREQOR_Disable(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
	/**HDMR(ハードマスクレジスタ)を設定する*/
	CodecHDMR_MODR_Status[codec_type] &= ~REQOR_BIT;	/**OR処理(0:無効, 1:有効)*/
	outpw(CodecRegisterAddressTable[codec_type][CODEC_HDMR_MODR], CodecHDMR_MODR_Status[codec_type]);
}
