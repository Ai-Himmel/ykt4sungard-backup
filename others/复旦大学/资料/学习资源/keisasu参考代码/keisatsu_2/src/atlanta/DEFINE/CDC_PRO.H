/*
 *  \src\atlanta\define\cdc.pro   1996/10/14   By M.Kotani
 *  コーデックモジュール部
 *  プロトタイプ宣言
 */
#include	"\src\atlanta\define\product.h"
/************ \src\atlanta\src\cdc_mscr.c **********/
void WaitPBR_Ready(UBYTE codec_type);
UBYTE CheckPBR_Ready(UBYTE codec_type);
UBYTE CheckOutputDMA_Request(UBYTE codec_type);
UBYTE CheckPBR_Ready(UBYTE codec_type);
/************ \src\atlanta\src\cdc_cdcr.c **********/
void AbortDecode(UBYTE codec_type);
void CodecEncodeCDCR_Setup(UBYTE codec_type);
void CodecDecodeCDCR_Setup(UBYTE codec_type);
void CodecDecodeCheckCDCR_Setup(UBYTE codec_type);
void CodecCodeConvertCDCR_Setup(UBYTE codec_type);
void CodecDataTransferCDCR_Setup(UBYTE codec_type);
/************ \src\atlanta\src\cdc_cmd.c **********/
void EnterCodecCommand(UBYTE codec_type, UBYTE command_number);
void AbortCodecCommand(UBYTE codec_type);
void WaitCommandEnd(UBYTE codec_type);
/************ \src\atlanta\src\cdc_cntl.c **********/
UBYTE GetCodec(UBYTE codec_type, UBYTE get_id);
UBYTE ReleaseCodec(UBYTE codec_type, UBYTE get_id);
UBYTE CheckCodec(UBYTE codec_type);
/************ \src\atlanta\src\cdc_dmcr.c **********/
void CodecDMA_Enable(UBYTE codec_type, UBYTE channel);
void CodecDMA_Disable(UBYTE codec_type, UBYTE channel);
void AbortCodecDMA_Transfer(UBYTE codec_type, UBYTE channel);
void CodecINTR2_Mask(UBYTE codec_type, UBYTE channel);
void CodecINTR2_Enable(UBYTE codec_type, UBYTE channel);
UWORD CDC_CheckMN86064(UBYTE codec_type); /* 1998/04/29 by T.Soneoka */
/************ \src\atlanta\src\cdc_dtcr.c **********/
void CodecImageByteSwapEnable(UBYTE codec_type);
void CodecImageByteSwapDisable(UBYTE codec_type);
void CodecCodeByteSwapEnable(UBYTE codec_type);
void CodecCodeByteSwapDisable(UBYTE codec_type);
/************ \src\atlanta\src\cdc_init.c **********/
void InitializeCodec(UBYTE codec_type);
void ResetCodec(UBYTE codec_type);
void InitializeCodecValue(UBYTE codec_type);
void InitializeCodecParameterValue(UBYTE codec_type);
void CDC_InitializePrintImageMemory(UWORD initial_data);
#if (PRO_ENERGY_SAVE_PPF == ENABLE) /*By Y.Suzuki 2002/06/07*/
void CDC_InitializeCodec(void);
#endif
/************ \src\atlanta\src\cdc_main.c **********/
void CDC_EncodePageTask(void);
void CDC_DecodePageTask(struct PrintQueueData_t *);
void CDC_STxCodeConvertPageTask(void);
void CDC_CTxCodeConvertPageTask(void);
void CDC_MTxCodeConvertPageTask(void);
void CDC_MRxCodeConvertPageTask(void);
void CDC_DataTransferPageTask(void);
void CDC_DecodeJournalPageTask(void);
#if (PRO_PC_PRINT == ENABLE)
void CDC_PcPrintDataTransfer(struct PrintQueueData_t *);
#endif
UBYTE CDC_GetOBXR_Size(struct PrintQueueData_t *);
/************ \src\atlanta\src\cdc_parm.c **********/
void SetCodecParameterRegister(UBYTE codec_type, UWORD address, UWORD data);
UWORD ReadCodecParameterRegister(UBYTE codec_type, UWORD address);
void SetCodecAllParameterRegister(UBYTE codec_type);
void SetCodecPartParameterRegister(UBYTE codec_type, UWORD start_address, UWORD end_address);
void ReadCodecAllParameterRegister(UBYTE codec_type);
void CodecEncodeParameterSetup(struct CodecEncodeParameterBlk_t *encode_block);
void CodecDecodeParameterSetup(struct CodecDecodeParameterBlk_t *decode_block);
void CodecCodeConvertParameterSetup(struct CodecCodeConvertParameterBlk_t *code_convert_block);
void CodecDataTransferParameterSetup(struct CodecDataTransferParameterBlk_t *data_transfer_block);
void CodecDMA_TransferParameterSetup(struct CodecDMA_TransferParameterBlk_t *DMA_transfer_block);
/************ \src\atlanta\src\cdc_stup.c **********/
void CodecEncodeSetup(struct CodecEncodeParameterBlk_t *enc_blk);
void CodecDecodeSetup(struct CodecDecodeParameterBlk_t *dec_blk);
void CodecDecodeCheckSetup(struct CodecDecodeParameterBlk_t *dec_blk);
void CodecCodeConvertSetup(struct CodecCodeConvertParameterBlk_t *code_conv_blk);
void CodecDataTransferSetup(struct CodecDataTransferParameterBlk_t *data_trans_blk);
void CodecPcDataTransferSetup(struct CodecDataTransferParameterBlk_t *data_trans_blk);	/* By M.Tachibana 1998/03/30 */
void CodecDMA_TransferSetup(struct CodecDMA_TransferParameterBlk_t *dma_transfer_block);
/************ \src\atlanta\src\cdc_sub.c **********/
UWORD EncodeLine(UBYTE codec_type);
UWORD DecodeLine(UBYTE codec_type);
UWORD ErrorLine(UBYTE codec_type);
UWORD CodecDMA0_Address(UBYTE codec_type);
UWORD CodecDMA1_Address(UBYTE codec_type);
void StartEncode(UBYTE codec_type, UBYTE code_type);
void StartDecode(UBYTE codec_type, UBYTE code_type);
void StartCodeConvert(UBYTE codec_type, UBYTE src_code_type, UBYTE dest_code_type);
void SetRTC(UBYTE codec_type, UBYTE code_type);
#if (PRO_FBS == ENABLE)
UWORD CDC_GetDocumentScanLine(UBYTE mode);
#endif
UWORD CDC_GetDocumentMaxLine(UBYTE mode);
UBYTE CDC_GetTxTTI_Line(UBYTE mode);
UWORD CDC_CheckCodecLSI(UBYTE codec_type);
/************ \src\atlanta\src\cdc_ctx.c **********/
UDWORD CDC_SetTTI(void);
UDWORD CDC_SetCoverPage(void);
UDWORD CDC_SetRCR(void);
void CDC_CTxSetupCodec(UBYTE);  /* Modified by H.Kubo 1997/12/19 */
/* void CDC_CTxSetupCodec(void); */
void CDC_CTxSetupDMAU(void);
void CDC_SetDummyLine(UBYTE line);
void CDC_CTxStartEncodeAndJBIGIRQ(UBYTE codec_type, UBYTE code_type); /* Added by H.Kubo 1997/12/27 */
UDWORD CDC_DataTransferAndSetTTI(void);	/*  by T.Soneoka 1998/01/07 */
#if (PRO_RELAYED_REPORT == ENABLE) /* H.Kubo 1998/01/17 */
UDWORD CDC_SetRelayedTxReport(void);
#endif
void CDC_InitCodecEncodeStructJbig(struct CodecEncodeParameterBlk_t *cdc_cnv); /* added by H.Kubo 1998/07/08 */
void CDC_CtxCodecEncodeStructMagnify(struct CodecEncodeParameterBlk_t *cdc_cnv, UBYTE image_kind); /* added by H.Kubo 1998/07/08 */
UBYTE CDC_GetCtxCodecEncode_I_OBXR(void);/* added by H.Kubo 1998/07/08 */
UWORD CDC_GetCodecEncodeMCLR(void); /* added by H.Kubo 1998/07/08 */


#if (PRO_COM_CODEC_TYPE == MN86064)
 #if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1999/10/19 Y.Murata */
void	CDC_SetReceiveCIL(void);
void	CDC_CRxSetupCodec(void);
 #endif
#endif

/************ \src\atlanta\src\cdc_stir.c **********/
UWORD CDC_CheckDecodeError(UBYTE codec_type);
UWORD CDC_CheckDetectRTC(UBYTE codec_type);
UWORD CDC_CheckAccept(UBYTE codec_type);
/************ \src\atlanta\src\cdc_modr.c **********/
void CodecEncodeCodeByteSwapEnable(UBYTE codec_type);
void CodecEncodeCodeByteSwapDisable(UBYTE codec_type);
void CodecDecodeCodeByteSwapEnable(UBYTE codec_type);
void CodecDecodeCodeByteSwapDisable(UBYTE codec_type);
void CodecMODR_Enable(UBYTE codec_type);
void CodecMODR_Disable(UBYTE codec_type);
void CodecEXA_Enable(UBYTE codec_type);
void CodecEXA_Disable(UBYTE codec_type);
/************ \src\atlanta\src\cdc_hdmr.c **********/
void CodecHDMR_Enable(UBYTE codec_type);
void CodecHDMR_Disable(UBYTE codec_type);
void CodecINTR0_Mask(UBYTE codec_type);
void CodecINTR0_Enable(UBYTE codec_type);
void CodecINTR1_Mask(UBYTE codec_type);
void CodecINTR1_Enable(UBYTE codec_type);
void CodecREQC0_Mask(UBYTE codec_type);
void CodecREQC0_Enable(UBYTE codec_type);
void CodecREQC1_Mask(UBYTE codec_type);
void CodecREQC1_Enable(UBYTE codec_type);
void CodecREQD0_Mask(UBYTE codec_type);
void CodecREQD0_Enable(UBYTE codec_type);
void CodecREQD1_Mask(UBYTE codec_type);
void CodecREQD1_Enable(UBYTE codec_type);
void CodecREQOR_Disable(UBYTE codec_type);
void CodecREQOR_Enable(UBYTE codec_type);

void CDC_GetTTI_SkipLine(void);	/* SAKAKI用　1998/11/28 H.Yoshikawa */
