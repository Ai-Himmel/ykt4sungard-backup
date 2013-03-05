/*----------------------------------------------------------------------*/
/* ƒvƒƒWƒFƒNƒg : POPLAR_F												*/
/* ƒtƒ@ƒCƒ‹–¼	: MDM_PRO.H												*/
/* ƒ‚ƒWƒ…-ƒ‹–¼	:														*/
/* ì¬ŽÒ–¼		: 														*/
/* “ú  •t		: 1999/10/06											*/
/* ŠT  —v		: ƒ‚ƒfƒ€ŠÖŒW ƒvƒƒgƒ^ƒCƒv								*/
/* C³—š—ð		:														*/
/*----------------------------------------------------------------------*/
#ifndef	MDM_PRO_H
	#define	MDM_PRO_H	1


/* For SH compiler, cancel near and far by H.Kubo 1997/07/07 */

#ifndef near
#define near 
#endif

#ifndef far
#define far
#endif

#ifndef _near
#define _near 
#endif

#ifndef _far
#define _far
#endif

#include "\src\atlanta\define\product.h"

#include "\src\atlanta\define\message.h"



/*************/
/* MDM_IO.C **/
/*************/
/*++++ Global function ++++*/
void	MDM_SetIO(UBYTE bit_position, UBYTE sw);
UBYTE	MDM_GetIO(UBYTE Bit);
void	MDM_FlipAnsOrg(void);	/* Polling By O.Kimoto 1996/06/26 */
void	MDM_SetIO_NewcAfterConf(UBYTE bit_position, UBYTE sw, UWORD time_count); /** Add By O.Kimoto 1997/02/07 */
void	MDM_InitializeModemCheck(void); /* Ported from CLOVER by H.Kubo 1997/11/05 */
/*++++ End of global function ++++*/

/*++++ Local function ++++*/
/* UBYTE *	MDM_GetPortStatusAddress(CONST struct MDM_I_O_Memory_t * io_port_ptr);*/ /* By H.Kubo 1997/07/14 */
/* conf = BPS****_V**, bps = MDM_R288F_CONF_BPS****_V** */
UBYTE 	MDM_BPS_ToR288F_MemBitCONF(UBYTE bps);	 /* by H. Kubo 1997/06/19 */
UBYTE 	MDM_R288F_MemBitCONF_ToBPS(UBYTE conf); 	/* by H. Kubo 1997/06/19 */
/*++++ End of local function ++++*/


/***************/
/** MDM_DSP.C **/
/***************/
void 			DspRamAccessWriteMethod1(UWORD, UBYTE, UBYTE);
UBYTE			DspRamAccessReadMethod1(UWORD );
void			DspRamAccessWriteMethod2(UWORD, UWORD, UWORD, UWORD);
UWORD			DspRamAccessReadMethod2(UWORD ,UWORD );
void			DspRamAccessWriteMethod3(UWORD, UWORD, UWORD);
UWORD			DspRamAccessReadMethod3(UWORD );
UWORD			DspRamAccessReadMethod4(UWORD );
void			MDM_SetDualTone1Frequency(UWORD );
void			MDM_SetDualTone2Frequency(UWORD );
void			MDM_SetDualTone1PowerLevel(UWORD );
void			MDM_SetDualTone2PowerLevel(UWORD );
void 			MDM_SetMaskingRegsiter01(UBYTE );
void 			MDM_SetMaskingRegsiter0A0B(UWORD );
void 			MDM_SetMaskingRegsiter0C0D(UWORD );
void 			MDM_SetMaskingRegsiter0E0F(UWORD );
void 			MDM_SetMaskingRegsiter12(UBYTE);
void 			MDM_SetMaskingRegsiter14(UBYTE );
void 			MDM_SetMaskingRegsiter16(UBYTE );
void 			MDM_SetMaskingRegsiter17(UBYTE );
void 			MDM_SetMaskingRegsiter1A1B(UWORD );
void 			MDM_SetMemAccMaskingRegsiter(UBYTE );
void			MDM_SetTone_A_Filter_B1_A3(UWORD );
void			MDM_SetTone_A_Filter_B1_A2(UWORD );
void			MDM_SetTone_A_Filter_B1_A1(UWORD );
void			MDM_SetTone_A_Filter_B1_B2(UWORD );
void			MDM_SetTone_A_Filter_B1_B1(UWORD data);
void			MDM_SetTone_A_Filter_B2_A3(UWORD );
void			MDM_SetTone_A_Filter_B2_A2(UWORD );
void			MDM_SetTone_A_Filter_B2_A1(UWORD );
void			MDM_SetTone_A_Filter_B2_B2(UWORD );
void			MDM_SetTone_A_Filter_B2_B1(UWORD );
void			MDM_SetTone_B_Filter_B1_A3(UWORD );
void			MDM_SetTone_B_Filter_B1_A2(UWORD );
void			MDM_SetTone_B_Filter_B1_A1(UWORD );
void			MDM_SetTone_B_Filter_B1_B2(UWORD );
void			MDM_SetTone_B_Filter_B1_B1(UWORD );
void			MDM_SetTone_B_Filter_B2_A3(UWORD );
void			MDM_SetTone_B_Filter_B2_A2(UWORD );
void			MDM_SetTone_B_Filter_B2_A1(UWORD );
void			MDM_SetTone_B_Filter_B2_B2(UWORD );
void			MDM_SetTone_B_Filter_B2_B1(UWORD );
void			MDM_SetTone_C_Filter_B1_A3(UWORD );
void			MDM_SetTone_C_Filter_B1_A2(UWORD );
void			MDM_SetTone_C_Filter_B1_A1(UWORD );
void			MDM_SetTone_C_Filter_B1_B2(UWORD );
void			MDM_SetTone_C_Filter_B1_B1(UWORD );
void			MDM_SetTone_C_Filter_B2_A3(UWORD );
void			MDM_SetTone_C_Filter_B2_A2(UWORD );
void			MDM_SetTone_C_Filter_B2_A1(UWORD );
void			MDM_SetTone_C_Filter_B2_B2(UWORD );
void			MDM_SetTone_C_Filter_B2_B1(UWORD );
void			MDM_SetTone_P_Filter_B1_A3(UWORD );
void			MDM_SetTone_P_Filter_B1_A2(UWORD );
void			MDM_SetTone_P_Filter_B1_A1(UWORD );
void			MDM_SetTone_P_Filter_B1_B2(UWORD );
void			MDM_SetTone_P_Filter_B1_B1(UWORD );
void			MDM_SetTone_P_Filter_B2_A3(UWORD );
void			MDM_SetTone_P_Filter_B2_A2(UWORD );
void			MDM_SetTone_P_Filter_B2_A1(UWORD );
void			MDM_SetTone_P_Filter_B2_B2(UWORD );
void			MDM_SetTone_P_Filter_B2_B1(UWORD );
void			MDM_setTone_A_LPFBK(UWORD);
void			MDM_SetTone_A_LPGAIN(UWORD);
void			MDM_SetTone_A_THRESHU(UWORD);
void			MDM_SetTone_A_THRESHL(UWORD);
void			MDM_setTone_B_LPFBK(UWORD);
void			MDM_SetTone_B_LPGAIN(UWORD);
void			MDM_SetTone_B_THRESHU(UWORD);
void			MDM_SetTone_B_THRESHL(UWORD);
void			MDM_setTone_C_LPFBK(UWORD);
void			MDM_SetTone_C_LPGAIN(UWORD);
void			MDM_SetTone_C_THRESHU(UWORD);
void			MDM_SetTone_C_THRESHL(UWORD);
void			MDM_SetFiterCoefficient(UWORD address, UWORD data, UWORD mask_data);	/* Add By O.Kimoto 1998/04/27 */
void			MDM_SetReceiverGain(UWORD );
UWORD			MDM_GetEyeQualityMonitor(void);
UWORD			MDM_GetPhaseJitterAmplitude(void);
void			MDM_SetV34SymbolRate(UBYTE );
UBYTE			MDM_GetV34Phase2PowerReduction(void);
UBYTE			MDM_GetV34RxSpeedIndication(void );	/** Add By O.K Feb.02,1996 **/
UBYTE			MDM_GetV8StatusRegister1(void);
UBYTE			MDM_GetV8StatusRegister2(void);
void			MDM_SetV8ControlRegister1(UBYTE );
void			MDM_SetV8ControlRegister2(UBYTE );
void			MDM_SetV8ControlRegister3(UBYTE );
void			MDM_SetV8ControlRegister4(UBYTE );
void			MDM_SetV8ControlRegister5(UBYTE );
void			MDM_SetV8ControlRegister6(UBYTE );
void			MDM_SetModulationModeV34HDX(UBYTE );
void			MDM_SetModulationModeV32BIS(UBYTE );
void			MDM_SetModulationModeV17(UBYTE );
void			MDM_SetModulationModeV29(UBYTE );
void			MDM_SetModulationModeV27(UBYTE );
void			MDM_SetV8MaxFrameByteCount(UBYTE );
void			MDM_SetV8CallFunction(UBYTE );
void			MDM_SetCmFrameSyncCm(void);
void			MDM_SetCmFrameDataCallFunc(UBYTE );
void			MDM_SetCmFrameModulation0(UBYTE );
void			MDM_SetCmFrameModulation1(UBYTE );
void			MDM_SetCmFrameModulation2(UBYTE );
void			MDM_SetCmFrameProtocol(UBYTE );
void			MDM_SetCmFrameGSTN(UBYTE );
void			MDM_SetCmFrameEnd(void);
void			MDM_SetCiFrameSyncCi(void);
void			MDM_SetCiFrameDataCallFunc(UBYTE );
void			MDM_SetCiFrameEOF(void);
UBYTE			MDM_SetJmFrameSyncJm(void);
UBYTE			MDM_GetJmFrameDataCallFunc(void);
UBYTE			MDM_GetJmFrameModulation0(void);
UBYTE			MDM_GetJmFrameModulation1(void);
UBYTE			MDM_GetJmFrameModulation2(void);
UBYTE			MDM_GetJmFrameProtocol(void);
UBYTE			MDM_GetJmFrameGSTN(void);
UBYTE			MDM_GetJmFrameEnd(void);
UBYTE			MDM_GetSelectedSymbolRate(void);
void			MDM_SetASYMControlChRatesEnable(UBYTE );
void			MDM_SetRxFIFOClear(void);
void			MDM_SetTxFIFOClear(void);
void			MDM_SetFlag2Tx(UBYTE count);
void			MDM_GetARAThreshold(void);
void			MDM_GetEQMAveraging(void);
void			MEM_GetARAThreshold(void);
void			MDM_GetEQMAveraging(void);
void			MDM_SetForced2400SymbolRateSNR(UBYTE );		/* 1996/02/23 Y.M */
void			MDM_SetARAinRAM_FunctionEnable(UBYTE );		/* 1996/02/23 Y.M */
void			MDM_SetARAThreshold(UBYTE symbol_rate);		/* 1996/03/03 Y.M */
void			MDM_FlipSrcRcp(void);	/* Polling  By O.Kimoto 1996/06/26 */
void			MDM_SetForcedPPh(void);	/** Advive by Mr.Palm Sh - PPh Trouble By O.Kimoto 1996/07/17 **/
void			MDM_Disable3429SymbolRateSNR(UBYTE); /* for 26P or above by H.Kubo 1999/03/01 */

#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0))/* YAWARA‚æ‚èˆÚA 2002/01/17 T.Takagi *//*POPLAR_H By Y.Suzuki 2002/06/11*/ || (defined(SAKAKI) && defined(JP0)) || defined (SATSUKI2) || defined(STOCKHM2)
UBYTE MDM_CheckBitMEACC(void);
void  MDM_SetMaskingRegsiter0A(UBYTE mask_data);
void  MDM_SetMaskingRegsiter0B(UBYTE mask_data);
void  MDM_SetMaskingRegsiter0C(UBYTE mask_data);
void  MDM_SetMaskingRegsiter0D(UBYTE mask_data);
void  MDM_SetMaskingRegsiter0E(UBYTE mask_data);
void  MDM_SetMaskingRegsiter0F(UBYTE mask_data);
void  MDM_SetMaskingRegsiter1A(UBYTE mask_data);
void  MDM_SetMaskingRegsiter1B(UBYTE mask_data);
#endif

/***************/
/* MDM_V8.C    */
/***************/
void			MDM_SetCmFrame(void);
void			MDM_GetCmFrame(void);
void			MDM_SetCiFrame(void);
void			MDM_SetJmFrame(void);
void			MDM_GetJmFrame(void);
void			MDM_SetUpTurnaroundModeORG(void);
void			MDM_SetUpV8Mode(void);
void			MDM_SetUpTurnaroundModeANS(void);
void			MDM_SetTerminalInformation(UBYTE);
void			MDM_SetV34DataRate(void);
void			MDM_StartGoTurnaroundModeORG(void);
void			MDM_StartGoV8Mode(void);
void			MDM_V8TransmitCI(void);
void			MDM_V8StopCI(void);
UBYTE		 	MDM_V8DetectANSam(void);
UBYTE		 	MDM_V8DetectANS(void);
UBYTE		 	MDM_V8DetectCI(void);
void			MDM_V8TransmitANSam(void);
void			MDM_V8StopANSam(void);
UBYTE		 	MDM_V8CheckTransmittingANSam(void);		/* 1996/02/19 Y.M */
void			MDM_DetectV21Ch2FlagV8Task(MESSAGE_t *);
void			MDM_DetectV21Ch2FlagV8TaskExit(void);	/* 1996/03/01 Y.M */
void			MDM_V21Ch2FlagV8TaskDelete(void);		/* 1996/03/01 Y.M */
void			MDM_V21Ch2FlagV8TaskInitial(void);		/* 1996/03/01 Y.M */
UBYTE		 	MDM_V8OctetMonitoring(void);
void			MDM_SetAnswerMode(void);
void			MDM_SetOriginateMode(void);
UBYTE		 	MDM_V8StatusCallFunctionData(void);
void			MDM_V34ManagementAfterProbing(void);
void			MDM_ABCODE_Task(UWORD *);
void			MDM_ManagementV8EndToT30(void);
void			MDM_ManagementV34StartUpEnd(void);
UBYTE		 	MDM_ControlChanelTurnOff(void);
UBYTE		 	MDM_ControlChTurnaroundTurnOff(void);
UBYTE		 	MDM_ControlChanelOff(void);
void			MDM_PrimaryChanelTurnOff(void);
void			MDM_V34DataRateChange(UBYTE);
UBYTE		 	MDM_TxDataRateRead(void);
UBYTE			MDM_RxDataRateRead(void);
void			MDM_SetModemIdle(void);			/* 1996/02/24 Y.M */
void			MDM_SetVolumeAttenuationLevel(UBYTE);	/* 1996/03/07 Y.M */
void 			MDM_SetControlChannelRetrain(void);				/* 1996/04/25 Y.M */
void 			MDM_SetARA_HighSpeedRate(void);					/* 1996/08/27 Y.M */
void 			MDM_SetARA_PhaseJitterRate(void);				/* 1996/08/27 Y.M */
void 			MDM_FinetuneSelection336or312(void);			/* 1996/10/11 Y.M */

/* 22P ˆÈ~ */
void MDM_EnableFastTrainingDetection(void);
void MDM_EnableExtendedFIFO(void);
void MDM_DisableExtendedFIFO(void); /* added by H.Kubo 1998/10/19 */
void MDM_EnableExtendedTxFIFO(void);
void MDM_DisableExtendedTxFIFO(void);
void MDM_EnableExtendedRxFIFO(void);
void MDM_SetCapacityOfExtendedRxFIFO(UBYTE capacity);


/***************/
/* MDM_TEST.C **/
/***************/
void			MDM_TestANSamTx(void);
void			MDM_TestANSamTx2(void);
void			MDM_TestSoftReset(void);


/*----------------------*/
/*	File:	mdm.c		*/
/*----------------------*/
void			MDM_ModemHardwareReset(void);
void			MDM_ModemInitialize(void);
void			ModemConfig(UBYTE);
void			MDM_InitialConfig( void );
void			CTS_Check( void );
void			EqualizerHoldOn( void );
void			ModemTypeSet( UBYTE );
void			MDM_TransmitLevelSet(UBYTE );
void			MDM_ModemSoftReset(void);				/* 1996/02/24 Y.M */
void			MDM_ClearTskNoBuffer(void);	/** Add By O.Kimoto 1996/07/27 **/
void 		 	MDM_SetReceiveLevelExtension(UBYTE);
void 		 	MDM_ReSetReceiveLevelExtension(void);
void 		 	MDM_SetReceiveLevelExtendRLSD(void);
UWORD 		 	MDM_GetSpikeNoiseWaitTime(void);
void 		 	MDM_FskConfig(UBYTE tx_mode);
void 			MDM_HighSpeedConfig(UBYTE tx_mode, UBYTE hdlc_mode);
UWORD 			MDM_GetConfigTimeCount(UBYTE mode);
UWORD 			MDM_InitialConfig2(UBYTE type);
void			MDM_V23Config(UBYTE tx_mode);

/*----------------------*/
/*	File:	mdm_sub.c	*/
/*----------------------*/
void  InitializeModemWork(void);
void  ModemBufferWaiSem(unsigned char  buf_num);
void  ModemBufferSigSem(unsigned char  buf_num);
void  CreateModemBufferSem(void);
void  ResetModemBufferSem(void);
unsigned short  GetCount(unsigned long  src_cnt,unsigned short  cnt);
void  SetClear(unsigned char  *buf,unsigned short  cnt,unsigned char  set_num);
unsigned short  SetTransmitCount(unsigned short  time);
void  NextMdmBufWritePointSetExtRom(void);
void  NextMdmBufReadPointSetExtRom(void);
void  MemoryMove(unsigned char  *tgt_adr,unsigned char  *src_adr,unsigned short  cnt);

/* ˆÚA by SMuratec K.W.Q 2003/07/23 */
#if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* FM336ˆÈŠO‚Ìƒ\[ƒX‚ðÈ‚­‚ÆˆÈ‰º‚ªéŒ¾‚³‚ê‚È‚¢‚½‚ß’Ç‰Á O.Oshima 2003/07/16 */
	#define		NextModemBufferWritePointSet	(*next_mdmbuf_wp_set_ext_tbl)
	#define 	NextModemBufferReadPointSet	(*next_mdmbuf_rp_set_ext_tbl)
	#define		CheckEcmStatus	(*check_ecm_status_ext_tbl)
#endif

unsigned char  CheckEcmStatusExtRom(unsigned short  frm_num);
void  EnableEcmStatus(unsigned char  num);
void  GetRxSize(unsigned char  pnt);
unsigned char  ModemBufferFormatControl(unsigned char  point);
unsigned char  TxPixReductionSet(unsigned char  src_size,unsigned char  src_mode,unsigned char  dst_size,unsigned char  dst_mode,unsigned char  mode_method);
unsigned short  GetCodecSize(unsigned char  size,unsigned char  mode);
unsigned char  GetK_Parameter(unsigned char  mode);
unsigned short  GetMaxTxLine(unsigned short  length);
unsigned long  EncodeDataCountSet(void);
unsigned short  Set64K_PixTime(void);
unsigned char  GrayScannerTX_ReductionSet(void);
void					MDM_JBG_ReadBIH(void);
UBYTE MDM_TxForceStop(void);
void IncModemControlUsedCount(void);
void DecModemControlUsedCount(void);
void MDM_EcmTxFillFlags(void); /* added by H.Kubo 1999/01/25 */

/*----------------------*/
/*	File:	mdm_fsk.c	*/
/*----------------------*/
void				TxFskOpen(void);
void				TxFskWrite(UBYTE  *, UWORD);
void				TxFskStart(void);
void				TxFskOpen(void);
void				TxFskClose(void);
void				MDM_TxFskFrameControlTask(void);
void				MDM_TxFskFrameControlExit(void);
void				RxFskOpen(void);
void				RxFskClose(void);
void				MDM_RxFskFrameControlTask(UWORD *);
void				MDM_RxFskFrameControlExit(void);
UBYTE		RxFskFlagDetect(void);
void			 	MDM_FlagDetectTask(UWORD *);
UBYTE		RxFskFrameDetect(void);
void				MDM_FcsDetectTask(UWORD *);
UWORD				SetFskTime(UWORD);
void				MDM_CcRetrainDetectTask(UWORD *);	/* CC Retrain By O.Kimoto 1996/05/16 */
void				MDM_CheckCcRetrain(void);	/* Check CC Retrain By O.Kimoto 1996/09/20 */

/*----------------------*/
/*	File:	mdm_int.c	*/
/*----------------------*/
void					MDM_ModemInterrupt(void); /* UWORD => void by H.Kubo 1997/12/16 */
void					MDM_ModemInterruptTask(void);
void					MDM_ModemDMA_TC_Interrupt(void);
void					MDM_TxDMA_TC_Interrupt(void);
void					MDM_RxDMA_TC_Interrupt(void);
void					MDM_TxDMA_TC_DetectTask(void);
void					MDM_RxDMA_TC_DetectTask(void);
void					MDM_EncodeDMA_TC_DetectTask(void);
void					MDM_DecodeDMA_TC_DetectTask(void);
UWORD					MDM_ModemStatusCheck(void);
void 					MDM_ModemStatusCheckTask(UWORD *);
void				 	MDM_ToneCheck(void);
void					MDM_CheckInternalStatus(void);
void					MDM_ModemRecoverTask(void);
void					GetRxEcmSize(UBYTE	pnt, UWORD dma_counter);
UBYTE					MDM_IsModemRequestingInterrupt(void); /* added by H.Kubo 1998/11/11 */
void					MDM_ModemInterruptComplement(void); /* added by H.Kubo 1998/11/11 */
void					MDM_ReadModemStatus(void);  /* added by H.Kubo 1998/11/11 */
UBYTE					MDM_IsNewModemInterruptRaised(void);  /* added by H.Kubo 1998/11/11 */
UBYTE					MDM_IsModemInterruptActive(void);  /* added by H.Kubo 1998/11/11 */
void					MDM_ModemInterruptSub(void);  /* added by H.Kubo 1998/11/11 */
void					MDM_ReInterruptSYNCD(void); /* 2‰ñ–Ú‚ÌPPS.MPS‚ð‚Æ‚è‚±‚Ú‚µ‘Îô 1999/08/09 by K.Okada */
void					MDM_EncodeDMA_TC_Detect(void);	/* ECM_BUFFER_OVER */
void					MDM_CheckInternalStatusTask(void);
UBYTE					MDM_CHK_InternalStatus(void);

/*----------------------*/
/*	File:	mdm_ecm.c	*/
/*----------------------*/
void					TxEcmOpen(void); /* argument is deleted by H.Kubo 1997/08/18 */
void					TxEcmWrite(UBYTE  *, UWORD);
void					TxEcmStart(void);
#if defined (KEISATSU) /* ŒxŽ@FAX 05/08/24 Î‹´³˜a */
void TxEcmStartWithRTS_Sent(void);
#endif
void					TxEcmClose(void);
void					MDM_TxEcmFrameControlTask(void);
void					RxEcmOpen(void); /* argument is deleted by H.Kubo 1997/08/18 */
UBYTE			RxEcmRead(void);
void					RxEcmClose(void);
UWORD					SetEcmTime(UWORD);

/*----------------------*/
/*	File:	mdm_g3.c	*/
/*----------------------*/
void					TxG3_Open(void);
void					TxG3_Write(UBYTE  *, UWORD);/*Š„‚èž‚Ý‚ÅŽg—p*/
void					TxG3_Start(void);
#if defined (KEISATSU) /* ŒxŽ@FAX 05/08/20 Î‹´³˜a */
void TxG3_WriteWithRTS_Sent(UBYTE*, UWORD, BOOL);
void TxG3_StartWithRTS_Sent(BOOL);
#endif
void					TxG3_Close(void);
void					RxG3_Open(void);
#define RxG3_Read	(*rx_g3_read_ext_tbl)
void					RxG3_Start(void);
void					RxG3_Close(void);
void					MDM_ModemTxCloseWait(void);

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 2002/09/18 By M.Maeda */
UWORD MDM_G3Rx_EcmBufToCdcDmaCount(void); /* private routine added by H.Kubo 1999/03/20 */
UBYTE MDM_G3Rx_bufferToEcmBuffer(UBYTE *src_addr, UWORD count); /* private routine added by H.Kubo 1999/03/20 */
UBYTE MDM_G3RxNextDmaFromEcmBuffer(void); /* public routine added by H.Kubo 1999/03/20 */
UBYTE MDM_G3RxModemBufferToEcmBuffer(void); /* public routine added by H.Kubo 1999/03/20 */
#endif
/*----------------------*/
/*	File:	mdm_tcf.c	*/
/*----------------------*/
void					MDM_TransmitTCF(UBYTE );
void					TxTcfStart(void);
UBYTE			MDM_ReceiveTCF(UBYTE );
UBYTE			CheckTraining(UWORD);
UBYTE			CheckRLSD(UWORD);
UBYTE			CheckSlice(UBYTE);
UBYTE			CheckEYEQ(void);
void 					MDM_ReadEqmValueTask(void);	/* Add for EQM By O.K Feb.22,1996 */
/*----------------------*/
/*	File:	mdmtxpix.c	*/
/*----------------------*/
void					MDM_TxPixOpen(UBYTE ,UBYTE );
UBYTE			MDM_TxPix(UBYTE ,UBYTE );
 UBYTE			G3_Tx(void);
UBYTE			EcmTx(void);
void					MDM_MTxReadDMA_Task(void);
UBYTE			MDM_TxEcmPartialPage(void);
void					WriteFCD(UWORD, UBYTE  *, UBYTE  *, UWORD);
void					WriteRCP(UBYTE  *);
void					MDM_TxPixClose(UBYTE );
void					MDM_BreakTxTask(void);
UBYTE			CheckTxSystemError(void);
#if (0) /* SCN_SetScannerTxParam()‚Æ‚µ‚Ä‹@Ží–ˆ‚ÌSCN‚Å‘Î‰žBS.Fukui May.19,1999 */
void					SetScannerTxParam(void);
#endif
void					CopyBackUpRAM_ToEcmBuffer(void); /* ICHOU’Ç‰Á by T.Soneoka 1996/09/12 */ /* Added by H.Kubo 1997/07/25 */
void	SetScannerTxParam( void );
UBYTE	G3_TxSub(void);		/* ECM_BUFFER_OVER */
UBYTE	EcmTxSub(void);		/* ECM_BUFFER_OVER */

/*----------------------*/
/*	File:	mdmrxpix.c	*/
/*----------------------*/
UBYTE			MDM_FskHighSpeedCheck(UBYTE ,UBYTE ,UBYTE);
UBYTE			RxPixFlagAndHighSpeedDetect(void);
UBYTE			RxPixFrameAndHighSpeedDetect(void);
UBYTE			MDM_RxPix(UBYTE ,UBYTE );
UBYTE			G3_Rx(void);
UBYTE 			EcmRx(void);
void					MDM_RxEcmControlTask(void);
#if defined (SIRAKABA)	/* ECMƒoƒbƒtƒ@ -> CDC -> DRAMƒpƒXƒ`ƒFƒbƒN—p 1999/05/18 by K.Okada */
void			RxDMA_TransferTest(void);
#endif
UBYTE			MDM_RxEcmPartialPage(void);
void					RxDeviceControlTask(void);
void					MDM_RxPixClose(UBYTE );
UBYTE			CRC_Check(UBYTE *,UWORD, UWORD *);
void					MDM_BreakRxTask(void);
UWORD 				 	MDM_CarryDownErrorOrTotalLine(void);
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 2002/09/18 By M.Maeda */
void MDM_G3Rx_CreateDecodeTimer(struct Timer10msData_t * timer_ptr); /* added by H.Kubo 1999/03/31 */
#endif
/*----------------------*/
/*	File:	mdm_dtmf.c	*/
/*----------------------*/
void					MDM_DTMF_Tx(UBYTE ,UWORD );
void					MDM_DetectDtmfTask(UWORD *);
void					MDM_DTMF_Open(void);
void					MDM_DTMF_Set(UBYTE );
void					MDM_DTMF_Close(void);
void					MDM_BreakDTMF_Tx(void);
void					MDM_DTMF_SingleSet(UBYTE dtmf_type);
#if defined (KEISATSU)		/* ŒxŽ@FAX Added by SMuratec K.W.Q 2005/10/25 */
/* ŒxŽ@FAX Added DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
void					MDM_KEIDEN_DTMF_SingleSet(UBYTE dtmf_type);
#endif		/* End of (defined (KEISATSU)) */
void					MDM_DTMF(UBYTE dial_no); /* added for factory functions by H.Kubo 1997/12/05 */
/*----------------------*/
/*	File:	mdm_fltr.c	*/
/*----------------------*/
void					MDM_FilterSet(UBYTE );
void					MDM_FilterSetCNG(void);
void					MDM_FilterStandbyMode(void);
void					MDM_DetectFilter1Task(struct FilterData_t * );
void					MDM_DetectFilter2Task(struct FilterData_t * );
void					MDM_DetectFilter3Task(struct FilterData_t * );
void					MDM_ReceiveLevelSet(void);
void 				 	MDM_SetUpAnsFaxSilent(UBYTE mode);
UBYTE 	 		MDM_GetAnsFaxSilentLevel(void);

/*----------------------*/
/*	File:	mdm_tone.c	*/
/*----------------------*/
void					MDM_Tone(UBYTE );
void					MDM_ToneTx(UBYTE ,UWORD );
void					MDM_SingleToneOn(UBYTE );
void					MDM_SingleToneOff(void);
void					MDM_TxLossSet(UBYTE );
void					MDM_ToneTxConfigSet(UBYTE );
void					MDM_ToneModeConfig(void);
UBYTE			MDM_GetToneBaseLevel(void);
UBYTE 					MDM_DetectAnswerToneV25(void); /* by H.Kubo 1997/07/22 */
#if defined (HINOKI2)	/* 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0))/* By M.Maeda 2002/09/18 */  || defined (SATSUKI2) || defined(STOCKHM2)
void					MDM_ConfigDTMF_ReceiverMode(void);
#endif

/*----------------------*/
/*	File:	mdm_cmd.c	*/
/*----------------------*/
void					MDM_TransmitCommand(void);
UBYTE			MDM_ReceiveCommand(WORD);
UBYTE			MDM_ReceiveResponse(WORD); /* Changed by H.Kubo 1997/08/12 */
#if defined (KEISATSU) /* ŒxŽ@FAX 05/09/16 */
UBYTE MDM_ReceiveResponseOrCNG(WORD);
#endif
UBYTE			MDM_TxVoiceReqRcvCmd(UBYTE );
UBYTE			MDM_RxVoiceReqFromTxRcvCmd(void);
UBYTE			MDM_RxVoiceReq(void);
UBYTE			MDM_RxSpeedHandshake(void);

/*--------------------------*/
/*	File:	mdm_func.c		*/
/*--------------------------*/
UWORD					DetectEOL(UBYTE *);
void					MDM_ModemConfigTask(void); /* by H.Kubo 1997/12/17 */
void					MDM_GetInternalStatus(void); /* Added by H.Kubo 1998/01/06 */
/*----------------------*/
/*	File:	mdm_crc.c	*/
/*----------------------*/
UWORD					crc(UWORD, UBYTE *);


/*----------------------*/
/*	File:	mdm_fact.c	*/
/*----------------------*/
unsigned char  MDM_TxV34ServiceFunction(unsigned char  baud_menu,unsigned char  data_menu);
void  MDM_FactoryFunctionTask(void);
void  MDM_FactoryFunctionExit(void);
void  MDM_TonalTest(void);
void  MDM_RealyTest(void);
void  MDM_DTMF_Test(void);
void  MDM_FactoryFuncRelaySet(void);
void  MDM_FactoryFuncRelayReSet(void);
void  MDM_FactoryStopCheck(void);
void  MDM_FskTxTask(UBYTE *);
void  MDM_PixTxTask(struct ServiceFuncPixData_t *);

/*----------------------*/
/*	File:	MDM_MLDY.c	*/
/*----------------------*/
/* #if defined(POPLAR_F) *//* 1999/10/25 m.matsumoto */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGEˆÈŠO‚Ìƒ‚ƒfƒ€ Modified by J.Kishida 2002/09/11 */
void  MDM_AnswerLSI_Initialize(void);
void  VoicePrompt(UBYTE phase);
void  MDM_WaitST(void);
void  MDM_WaitNAR(UWORD timer);
void  VoiceReset(void);
void  VoicePromptTaskDelete(void);
 #endif
#endif

#endif
