/************************************************************************
*               BY:  M.Kotani
*             DATE:  1996/10/16
*        FILE NAME:  cdc_stup.c
*      DESCRIPTION:  松下製コーデックNM86063のコンフィギュレーション関数群
*                    コーデックを使用目的別にセットアップする時、
*                    外部(cdc_main.c)からは基本的にこのファイルの関数をCallする
*  PUBLIC ROUTINES:  void CodecEncodeSetup(struct CodecEncodeParameterBlk_t *encode_block);
*                    void CodecDecodeSetup(struct CodecDecodeParameterBlk_t *decode_block);
*                    void CodecDecodeCheckSetup(struct CodecDecodeParameterBlk_t *dec_blk);
*                    void CodecCodeConvertSetup(struct CodecCodeConvertParameterBlk_t *code_convert_block);
*                    void CodecDataTransferSetup(struct CodecDataTransferParameterBlk_t *data_transfer_block);
*                    void CodecDMA_TransferSetup(struct CodecDMA_TransferParameterBlk_t *dma_transfer_block);
* PRIVATE ROUTINES:
*        REFERENCE:  SH7043 for POPLAR/ANZU_L
*************************************************************************/
#include  "\src\atlanta\define\cdc_pro.h"
#include  "\src\atlanta\define\cdc_def.h"
#include  "\src\atlanta\define\cdc_blk.h"
#include  "\src\atlanta\ext_v\cdc_data.h"
#include  "\src\atlanta\ext_v\cdc_tbl.h"

#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\mem_def.h"
#include  "\src\atlanta\ext_v\sys_data.h"

/*************************************************************************
	module		:[符号化用にコーデックをセットアップする]
	function	:[
		1.コーデック初期化
		2.CDCR設定
		3.パラメータレジスタ設定
		4.符号化初期化
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		事前に使用するコーデック資源を獲得しておく事
	]
	comment		:[
		初期化＆初期設定を行います
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecEncodeSetup(struct CodecEncodeParameterBlk_t *enc_blk)	/*符号化設定ブロックの先頭アドレス*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
#else	/**コーデック１個の時はＤＴＣＲは固定*/
	CodecImageByteSwapDisable(enc_blk->CodecType);	/**DTCR設定(バイトSwap無効)*/
#endif
	CodecEncodeCDCR_Setup(enc_blk->CodecType);	/**CDCR設定*/
	CodecEncodeParameterSetup(enc_blk);			/**パラメータレジスタセット*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (enc_blk->CodeType == SYS_JBIG_CODE) {
		EnterCodecCommand(enc_blk->CodecType, CODEC_CMD_JBIG_ENCODE_INIT);	/**初期化(符号化)*/
	}
	else {
		EnterCodecCommand(enc_blk->CodecType, CODEC_CMD_ENCODE_INIT);	/**初期化(符号化)*/
	}
#else
	EnterCodecCommand(enc_blk->CodecType, CODEC_CMD_ENCODE_INIT);	/**初期化(符号化)*/
#endif
}


/*************************************************************************
	module		:[復号化用にコーデックをセットアップする]
	function	:[
		1.コーデック初期化
		2.CDCR設定
		3.パラメータレジスタ設定
		4.復号化初期化
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		事前に使用するコーデック資源を獲得しておく事
	]
	comment		:[
		初期化＆初期設定を行います
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDecodeSetup(struct CodecDecodeParameterBlk_t *dec_blk)	/*復号化設定ブロックの先頭アドレス*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
 #if (PRO_PC_PRINT == ENABLE)	/* By M.Tachibana 1997/07/08 */
	if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
		CodecDecodeCodeByteSwapDisable(dec_blk->CodecType);	/**復号化符号データバイト交換:入れ替えない*/
	}
	else {
		CodecDecodeCodeByteSwapEnable(dec_blk->CodecType);	/**復号化符号データバイト交換:入れ替えない*/
	}
 #endif
#else	/**コーデック１個の時はＤＴＣＲは固定*/
 #if (PRO_PC_PRINT == ENABLE)	/* By M.Tachibana 1997/07/08 */
	if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) {
		CodecCodeByteSwapDisable(dec_blk->CodecType);	/**DTCR設定(バイトSwap無効)*/
	}
	else {
		CodecCodeByteSwapEnable(dec_blk->CodecType);	/**DTCR設定(バイトSwap有効)*/
	}
 #endif
	CodecImageByteSwapDisable(dec_blk->CodecType);	/**DTCR設定(バイトSwap無効)*/
#endif
	CodecDecodeCDCR_Setup(dec_blk->CodecType);				/**CDCR設定*/
	CodecDecodeParameterSetup(dec_blk);			/**パラメータレジスタセット*/
	/* 
	** プリンタ受信の場合、ＪＢＩＧ符号をデコードできるようにします。
	** by H.Hirao 1998/10/28
	*/
#if (PRO_JBIG == ENABLE) && (PRO_PRINTER_RX == ENABLE)
	if (dec_blk->CodeType == SYS_JBIG_CODE) {
		EnterCodecCommand(dec_blk->CodecType, CODEC_CMD_JBIG_DECODE_INIT);	/**初期化(JBIG復号化)*/
	}
	else {
		EnterCodecCommand(dec_blk->CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
	}
#else
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/17 K.Kawata */
	if (dec_blk->CodeType == SYS_JBIG_CODE) {
		EnterCodecCommand(dec_blk->CodecType, CODEC_CMD_JBIG_DECODE_INIT);	/**初期化(JBIG復号化)*/
	}
	else {
		EnterCodecCommand(dec_blk->CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
	}
#else
	EnterCodecCommand(dec_blk->CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
#endif
#endif
}


/*************************************************************************
	module		:[復号エラーチェック用にコーデックをセットアップする]
	function	:[
		1.コーデック初期化
		2.CDCR設定
		3.パラメータレジスタ設定
		4.復号化初期化
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		事前に使用するコーデック資源を獲得しておく事
	]
	comment		:[
		初期化＆初期設定を行います
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDecodeCheckSetup(struct CodecDecodeParameterBlk_t *dec_blk)
{
	CodecDecodeCheckCDCR_Setup(dec_blk->CodecType);			/**CDCR設定*/
	CodecDecodeParameterSetup(dec_blk);			/**パラメータレジスタセット*/
	EnterCodecCommand(dec_blk->CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
}


/*************************************************************************
	module		:[符号変換用にコーデックをセットアップする]
	function	:[
		1.コーデック初期化
		2.CDCR設定
		3.パラメータレジスタ設定
		4.符号化初期化
		5.復号化初期化
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		事前に使用するコーデック資源を獲得しておく事
	]
	comment		:[
		初期化＆初期設定を行います
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecCodeConvertSetup(struct CodecCodeConvertParameterBlk_t *code_conv_blk)	/*符号変換設定ブロックの先頭アドレス*/
{
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
#else	/**コーデック１個の時はＤＴＣＲは固定*/
	CodecImageByteSwapDisable(code_conv_blk->CodecType);	/**DTCR設定(バイトSwap無効)*/
#endif
	CodecCodeConvertCDCR_Setup(code_conv_blk->CodecType);	/**CDCR設定*/
	CodecCodeConvertParameterSetup(code_conv_blk);	/**パラメータレジスタセット*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (code_conv_blk->DestCodeType == SYS_JBIG_CODE) {
		EnterCodecCommand(code_conv_blk->CodecType, CODEC_CMD_JBIG_ENCODE_INIT);	/**初期化(JBIG符号化)*/
	}
	else {
		EnterCodecCommand(code_conv_blk->CodecType, CODEC_CMD_ENCODE_INIT);	/**初期化(符号化)*/
	}
	if (code_conv_blk->SrcCodeType == SYS_JBIG_CODE) {
		EnterCodecCommand(code_conv_blk->CodecType, CODEC_CMD_JBIG_DECODE_INIT);	/**初期化(JBIG復号化)*/
	}
	else {
		EnterCodecCommand(code_conv_blk->CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
	}
#else
	EnterCodecCommand(code_conv_blk->CodecType, CODEC_CMD_ENCODE_INIT);	/**初期化(符号化)*/
	EnterCodecCommand(code_conv_blk->CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
#endif
}


/*************************************************************************
	module		:[データ転送用にコーデックをセットアップする]
	function	:[
		1.コーデック初期化
		2.CDCR設定
		3.パラメータレジスタ設定
		4.データ転送初期化
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		事前に使用するコーデック資源を獲得しておく事
	]
	comment		:[
		初期化＆初期設定を行います
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDataTransferSetup(struct CodecDataTransferParameterBlk_t *data_trans_blk)	/*データ転送設定ブロックの先頭アドレス*/
{
#if (PRO_CPU == SH7043)	/**モトローラ系のエンディアンタイプ*/
	CodecImageByteSwapDisable(data_trans_blk->CodecType);	/**DTCR設定(バイトSwap無効)*/
#else	/**インテル系のエンディアンタイプ*/
	CodecImageByteSwapEnable(data_trans_blk->CodecType);	/**DTCR設定(バイトSwap有効)*/
#endif
	CodecDataTransferCDCR_Setup(data_trans_blk->CodecType);		/**CDCR設定*/
	CodecDataTransferParameterSetup(data_trans_blk);	/**パラメータレジスタセット*/
	EnterCodecCommand(data_trans_blk->CodecType, CODEC_CMD_TRANSFER_INIT);	/**初期化(データ転送)*/
}

#if (PRO_PC_PRINT == ENABLE)
/*************************************************************************
	module		:[ＰＣのイメージデータ転送用にコーデックをセットアップする]
	function	:[
		1.コーデック初期化
		2.CDCR設定
		3.パラメータレジスタ設定
		4.データ転送初期化
	]
	return		:[なし]
	common		:[なし]
	condition	:[
		事前に使用するコーデック資源を獲得しておく事
	]
	comment		:[
		初期化＆初期設定を行います
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1998/03/30]
	author		:[橘正樹]
*************************************************************************/
void CodecPcDataTransferSetup(struct CodecDataTransferParameterBlk_t *data_trans_blk)	/*データ転送設定ブロックの先頭アドレス*/
{
#if (PRO_CPU == SH7043)	/**モトローラ系のエンディアンタイプ*/
/*	CodecImageByteSwapDisable(data_trans_blk->CodecType);	@**DTCR設定(バイトSwap無効)*/
	CodecImageByteSwapEnable(data_trans_blk->CodecType);	/**DTCR設定(バイトSwap無効)*/
#else	/**インテル系のエンディアンタイプ*/
	CodecImageByteSwapEnable(data_trans_blk->CodecType);	/**DTCR設定(バイトSwap有効)*/
#endif
	CodecDataTransferCDCR_Setup(data_trans_blk->CodecType);		/**CDCR設定*/
	CodecDataTransferParameterSetup(data_trans_blk);	/**パラメータレジスタセット*/
	EnterCodecCommand(data_trans_blk->CodecType, CODEC_CMD_TRANSFER_INIT);	/**初期化(データ転送)*/
}
#endif

/*************************************************************************
	module		:[DMA転送用にコーデックをセットアップする]
	function	:[
		1.パラメータレジスタ設定
		2.DMAイネーブル
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/10/16]
	author		:[小谷正樹]
*************************************************************************/
void CodecDMA_TransferSetup(struct CodecDMA_TransferParameterBlk_t *dma_transfer_block)	/*DMA転送設定ブロックの先頭アドレス*/
{
#if (0)	/*原稿付きチェックメッセージのときにページの途中でDMAを止めないようにする 1998/01/29 By M.Kotani*/
//	CodecDMA_Disable(dma_transfer_block->CodecType, dma_transfer_block->Channel);	/**上下のラインと入れ替え1997/11/11 By M.Kotani*/
#endif
	CodecDMA_TransferParameterSetup(dma_transfer_block);	/**パラメータレジスタセット*/
	CodecDMA_Enable(dma_transfer_block->CodecType, dma_transfer_block->Channel);
	CodecINTR2_Enable(dma_transfer_block->CodecType, dma_transfer_block->Channel);
}
