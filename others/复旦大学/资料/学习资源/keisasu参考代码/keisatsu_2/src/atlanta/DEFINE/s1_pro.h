/**********************************************************************************************************************
	@(#)$Id: s1_pro.h,v 1.14 2005/11/17 23:19:34 mi93007 Exp $
	Create        : 2005/06/08
	Author        : 石橋正和
	Description   : S1関係プロトタイプ
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"

/*********************************************************************
	s1_reg.c
*********************************************************************/
void S1_Initialize(void);
void S1_InitializeFaxCom(BOOL, BOOL);
void S1_OpenG3Rx(BOOL);
void S1_CloseG3Rx(void);
void S1_OpenG3Tx(BOOL);
void S1_CloseG3Tx(void);
void S1_OpenECM_Rx(BOOL);
void S1_CloseECM_Rx(void);
void S1_OpenECM_Tx(BOOL);
void S1_CloseECM_Tx(void);
void S1_GetFPGA_VersionString(UBYTE*);

void S1_SoftwareReset(void);
void S1_HardwareReset(void);
UBYTE S1_GetInterruptKind(void);
void S1_EnableInterrupt(void);
void S1_DisableInterrupt(void);
void S1_ClearInterrupt(void);
void S1_EnableDTC_Request(UBYTE);
void S1_ClearDTC_Request(void);
void S1_SetMode(BOOL);
void S1_SetRTS(UBYTE);
/* void S1_EnableRTS_RLSD(BOOL); */
void S1_EnableRTS(BOOL);
void S1_EnableRLSD(BOOL);
UBYTE S1_GetRTS(void);
UBYTE S1_GetCTS(void);
UBYTE S1_GetRLSD(void);
void S1_TCF_Clear(void);
void S1_TCF_Detect(UBYTE*, UBYTE*);
void S1_SetScrambleAvailable(BOOL);
BOOL S1_GetScrambleAvailable(void);
void S1_SetScrambleMode(BOOL);
void S1_BypassS1(BOOL);
UBYTE S1_GetFPGA_Version(void);
void S1_SCI_EnableRx(BOOL);
void S1_SCI_ClearRxFIFO(void);
void S1_SCI_ClearRxStatus(void);
/* void S1_SCI_ClearRxOE(void); */
UBYTE S1_SCI_GetRxStatus(void);
/* BOOL S1_SCI_CheckRxData(void); */
/* BOOL S1_SCI_CheckRxOE(void); */
void S1_SCI_EnableTx(BOOL);
void S1_SCI_SetTxUNE(void);
void S1_SCI_ClearTxStatus(void);
UBYTE S1_SCI_GetTxStatus(void);
/* BOOL S1_SCI_CheckTxData(void); */
/* BOOL S1_SCI_CheckTxUNE(void) */
/* BOOL S1_SCI_CheckTxDataReady(void); */
void S1_SCI_SetIntDTC_Enabled(UBYTE);
UBYTE S1_SCI_GetIntFactor(void);
void S1_HDLC_InitializeCRC(void);
void S1_HDLC_InitializeTransMode(void);
UBYTE S1_HDLC_GetRxStatus(void);
UBYTE S1_HDLC_GetRxRemainedBitNum(void);
void S1_HDLC_EnableRx(BOOL);
void S1_HDLC_ClearRxStatus(void);
void S1_HDLC_SetRxIntDTC_Enabled(UBYTE);
UBYTE S1_HDLC_GetTxStatus(void);
void S1_HDLC_ClearTxStatus(UBYTE);
void S1_HDLC_EnableTx(BOOL);
void S1_HDLC_TxSendHighLevel(BOOL);
void S1_HDLC_TxSendBreak(BOOL);
void S1_HDLC_TxSelectIdle(BOOL);
void S1_HDLC_RestTx(void);
void S1_HDLC_TxSendAbort(void);
void S1_HDLC_TxLast(UBYTE);
void S1_HDLC_SetTxIntDTC_Enabled(UBYTE);
void S1_HDLC_InitializeTxMode(void);
UBYTE S1_HDLC_GetRequestStatus(void);
void S1_HDLC_EnableRxInterrupt(BOOL);
void S1_HDLC_EnableRxDMA_Request(BOOL);
void S1_HDLC_EnableTxInterrupt(BOOL);
void S1_HDLC_EnableTxDMA_Request(BOOL);

/*********************************************************************
	s1_int.c
*********************************************************************/
void S1_Interrupt(void);

/*********************************************************************
	s1_tcf.c
*********************************************************************/
BOOL S1_CheckScramblePossibility(UBYTE);
UBYTE S1_ReceiveTCF(UBYTE, BOOL, BOOL*);
void S1_ReceiveTCF_DataTask(void);

