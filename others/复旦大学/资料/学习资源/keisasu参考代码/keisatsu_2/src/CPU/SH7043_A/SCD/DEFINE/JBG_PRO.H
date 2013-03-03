/*
 *  \src\data\jbig\define\jbg_pro.h   1997/01/22   By M.Kotani
 *  ÇiÇaÇhÇfÉÇÉWÉÖÅ[Éãïî
 *  ÉvÉçÉgÉ^ÉCÉvêÈåæ
 */
#include "\src\atlanta\define\product.h"

/************ \src\data\jbig\src\jbg_main.c **********/
void JBG_EncodePageTask(void);
void JBG_DecodePageTask(void);
/************ \src\data\jbig\src\jbg_init.c **********/
void JBG_InitializeGlobalValue(void);
void JBG_SetEncodeIO_Address(void);
void JBG_SetDecodeIO_Address(void);
/************ \src\data\jbig\src\jbg_bih.c **********/
void JBG_MakeBIH(void);
void JBG_ResetBIH(void);
void JBG_SetBIH_LRLTWO(UBYTE lrltwo);
void JBG_SetBIH_VLENGTH(UBYTE vlength);
void JBG_SetBIH_TPBON(UBYTE tpbon);
void JBG_EncodeBIH(void);
void JBG_DecodeBIH(void);
/************ \src\data\jbig\src\jbg_fms.c **********/
void JBG_MakeFMS(void);
void JBG_WriteSDRST(void);
void JBG_WriteSDNORM(void);
void JBG_WriteATMOVE(void);
void JBG_WriteNEWLEN(void);
void JBG_WriteCOMMENT(void);
void JBG_ResetATMOVE(void);
void JBG_ResetCOMMENT(void);
void JBG_ResetNEWLEN(void);
/************ \src\data\jbig\src\jbg_tpb.c **********/
void JBG_EncodeTPB(void);
void JBG_MakeLNTP(void);
void JBG_MakeSLNTP(void);
void JBG_GetLNTP(void);
void JBG_DecodeTPB(void);
/************ \src\data\jbig\src\jbg_mt.c **********/
void JBG_MT(void);
void JBG_MakePixCxTpValueDpValue(void);
void JBG_Get2LinesCx(void);
void JBG_Get3LinesCx(void);
void JBG_GetSlntpCx(void);
void JBG_ResetCx(void);
/************ \src\data\jbig\src\jbg_at.c **********/
void JBG_AT(void);
/************ \src\data\jbig\src\jbg_aae.c **********/
void JBG_AAE(void);
void JBG_EncodeReferenceLine(void);
void AAE_Encode(void);
void AAE_CodeLps(void);
void AAE_CodeMps(void);
void AAE_Renorme(void);
void AAE_ByteOut(void);
void AAE_InitEnc(void);
void AAE_Flush(void);
void AAE_ClearBits(void);
void AAE_FinalWrite(void);
/************ \src\data\jbig\src\jbg_aad.c **********/
void JBG_AAD(void);
void JBG_DecodeReferenceLine(void);
void AAD_Decode(void);
void AAD_LpsExchange(void);
void AAD_MpsExchange(void);
void AAD_Renormd(void);
void AAD_ByteIn(void);
void AAD_InitDec(void);
/************ \src\data\jbig\src\jbg_io.c **********/
void JBG_ReadImageLine(void);
void JBG_CopyReferenceLine(void);
void JBG_WritePscd(UBYTE data);
void JBG_WriteBid(UBYTE data);
void JBG_IncrementReferenceLineY(void);
UBYTE JBG_ReadPix(void);
UBYTE JBG_ReadBID(void);
UBYTE JBG_ReadSCD(void);
/************ \src\data\jbig\src\jbg_test.c **********/
void main(void);
UBYTE ReadPix(void);
UWORD ReadCx(void);
UBYTE ReadTpValue(void);
UBYTE ReadDpValue(void);
void InitTestData(void);
void Write(UWORD data);
void WritePix(void);
UBYTE CheckStripeEnd(void);
UBYTE CheckEndSCD(void);
void WriteBID(UWORD data);
UWORD ReadSCR(void);
void DumpTrace(void);
void printbih(void);
void check(void);
void check1(void);
void check2(void);
void check3(void);
void check4(void);
void DumpRL(void);
void DumpEOL(void);
void DumpByte(UBYTE *src);

