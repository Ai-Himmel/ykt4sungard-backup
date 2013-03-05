/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/14
*        FILE NAME:  cdc_mscr.c
*      DESCRIPTION:  松下製コーデックNM86063のMSCR(マスタコントロールレジスタ)を
*                    読みだし, 状態を確認する為のファイル群
*  PUBLIC ROUTINES:  void WaitPBR_Ready(UBYTE codec_type);
*                    UBYTE CheckPBR_Ready(UBYTE codec_type);
*                    UBYTE CheckOutputDMA_Request(UBYTE codec_type);
*                    UBYTE CheckInputDMA_Request(UBYTE codec_type);
* PRIVATE ROUTINES:
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#if defined(ANZU_L)		/** ＡＮＺＵ＿Ｌタイプは機種別ディレクトリに移動しました */
	#include "\src\atlanta\anzu_l\define\anzu_sys.h"	/* By M.Kotani 97/06/10 */
#endif

/*************************************************************************
	module		:[PBRレディ(パラメータレジスタアクセス可能)になるまで待つ]
	function	:[
		1.タイムアップ用のループカウンタを１００００回とする
		2.PBRレディになるまで１００００回デッドループでチェックする（正常時最悪１３サイクル）
		3.異常時（PBRレディにならない）はなるまで１０ｍＳごとにチェックする
	]
	return		:[
		なし
	]
	common		:[]
	condition	:[]
	comment		:[
		パラメータレジスタを使用したい時Callされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/14]
	author		:[小谷正樹]
*************************************************************************/
void WaitPBR_Ready(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD loop;

	loop = 10000; /**タイムアップ用のループカウンタを１００００回とする*/
	while (loop) {	/**PBRレディになるまで１００００回デッドループでチェックする（正常時最悪１３サイクル）*/
		if (CheckPBR_Ready(codec_type)) {
			break;
		}
		loop--;
	}
	if (!loop) {	/**異常時（PBRレディにならない）はなるまで１０ｍＳごとにチェックする*/
		while (!CheckPBR_Ready(codec_type)) {
			wai_tsk(1);
		}
	}
}


/*************************************************************************
	module		:[PBRレディ(パラメータレジスタアクセス可能)をチェックする]
	function	:[
		1.指定されたコーデックのCODEC_MSCR_DTCRレジスタを読み込む
		2.PBRRビットをチェックする
	]
	return		:[
		1:使用可能
		0:Busy
	]
	common		:[]
	condition	:[]
	comment		:[
		パラメータレジスタを使用したい時、WaitPBR_Ready()からCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/14]
	author		:[小谷正樹]
*************************************************************************/
UBYTE CheckPBR_Ready(UBYTE codec_type)	/*使用するコーデック*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
#endif
    CodecMSCR_DTCR_Status[codec_type] = inpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR]);
    if (CodecMSCR_DTCR_Status[codec_type] & PBRR_BIT) {
        return(1); /**パラメータレジスタアクセス可能　PBRレディ*/
    }
    return(0); /** パラメータレジスタアクセス不可 */
}


/*************************************************************************
	module		:[データ出力DMAリクエストが出ているかチェックする]
	function	:[
		1.指定されたコーデックのCODEC_MSCR_DTCRレジスタを読み込む
		2.DREQC0ビットをチェックする
	]
	return		:[
		1:転送要求あり
		0:転送要求なし
	]
	common		:[]
	condition	:[]
	comment		:[
		デバック用関数
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/14]
	author		:[小谷正樹]
*************************************************************************/
UBYTE CheckOutputDMA_Request(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD bit;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	if (codec_type == SCANNER_CODEC) {
		bit = DREQC0_BIT;
	}
	else {
		bit = DREQC1_BIT;
		codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
	}
#else	/** 通常はそれぞれのコーデックのチャンネル０を使用する */
	bit = DREQC0_BIT;
#endif
    CodecMSCR_DTCR_Status[codec_type] = inpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR]);
    if (CodecMSCR_DTCR_Status[codec_type] & bit) {
        return(1);	/**転送要求あり*/
    }
    return(0);	/**転送要求なし*/
}


/*************************************************************************
	module		:[データ入力DMAリクエストが出ているかチェックする]
	function	:[
		1.指定されたコーデックのCODEC_MSCR_DTCRレジスタを読み込む
		2.DREQD0ビットをチェックする
	]
	return		:[
		1:転送要求あり
		0:転送要求なし
	]
	common		:[]
	condition	:[]
	comment		:[
		デバック用関数
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/14]
	author		:[小谷正樹]
*************************************************************************/
UBYTE CheckInputDMA_Request(UBYTE codec_type)	/*使用するコーデック*/
{
	UWORD bit;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用の場合はチャンネルを分ける*/
	if (codec_type == SCANNER_CODEC) {
		bit = DREQD0_BIT;
	}
	else {
		bit = DREQD1_BIT;
		codec_type = SCANNER_CODEC;	/** ハードコーデックをスキャナーコーデックで固定する */
	}
#else	/** 通常はそれぞれのコーデックのチャンネル０を使用する */
	bit = DREQC0_BIT;
#endif
    CodecMSCR_DTCR_Status[codec_type] = inpw(CodecRegisterAddressTable[codec_type][CODEC_MSCR_DTCR]);
    if (CodecMSCR_DTCR_Status[codec_type] & bit) {
        return(1);	/**転送要求あり*/
    }
    return(0);	/**転送要求なし*/
}
