/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\define\uni_pro.h	*/
/*********************************************
 * UNI_PRO.H
 * 機種固有スイッチ参照関数のプロトタイプ宣言
 * 1996/04/15 Eguchi
 *********************************************/
#ifndef	UNI_PRO_H
	#define	UNI_PRO_H	1
#include	"\src\atlanta\define\product.h"

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif

/* CMNUNI_A.C */
UBYTE  CHK_UNI_FlashkeyCheck(void);
UBYTE  CHK_UNI_GroundkeyCheck(void);
UBYTE  CHK_UNI_CurrentLoop(void);
UBYTE  CHK_UNI_DSE_Detect(void);
UBYTE  CHK_UNI_RingBackToneWaitTime(void);
UBYTE  CHK_UNI_ConToneDetect(void);
void   SET_UNI_Line0_TxRx(UBYTE);
UBYTE  CHK_UNI_Line0_TxRx(void);
void   SET_UNI_Line1_TxRx(UBYTE);
UBYTE  CHK_UNI_Line1_TxRx(void);
void   SET_UNI_Line2_TxRx(UBYTE);
UBYTE  CHK_UNI_Line2_TxRx(void);
void   SET_UNI_Line3_TxRx(UBYTE);
UBYTE  CHK_UNI_Line3_TxRx(void);
void   SET_UNI_Line4_TxRx(UBYTE);
UBYTE  CHK_UNI_Line4_TxRx(void);
void   SET_UNI_Line5_TxRx(UBYTE);
UBYTE  CHK_UNI_Line5_TxRx(void);
void   SET_UNI_Line6_TxRx(UBYTE);
UBYTE  CHK_UNI_Line6_TxRx(void);
void   SET_UNI_Line7_TxRx(UBYTE);
UBYTE  CHK_UNI_Line7_TxRx(void);
void   SET_UNI_Line8_TxRx(UBYTE);
UBYTE  CHK_UNI_Line8_TxRx(void);
UBYTE  CHK_UNI_PriorityDirection(void);
UBYTE  CHK_UNI_OptionStxAvailable(void);
UBYTE  CHK_UNI_SwitchV17Line(void);
UBYTE  CHK_UNI_AramcoPinNotMasking(void);	/* ARAMCO PIN By O.Kimoto 1997/05/21 */
UBYTE CHK_UNI_Line_EXT_TxRx(void);			/* Add By O.Kimoto 1997/11/04 */
void SET_UNI_Line_EXT_TxRx(UBYTE value);	/* Add By O.Kimoto 1997/11/04 */
#if (PRO_PREHEAT == ENABLE)
UBYTE CHK_UNI_PreHeatEnable(void);			/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
UBYTE CHK_UNI_PreHeatTime(void);			/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
UBYTE CHK_UNI_PreHeatEndHour(void);			/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
UBYTE CHK_UNI_PreHeatEndMinute(void);		/* 寒冷地 PreHeat  1998/12/26 s.takeuchi */
#endif
#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
UBYTE	CHK_UNI_FORVAL_LCR_Enable(void);	
#endif
UBYTE CHK_UNI_Transmit1300Hz(void);

#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
UBYTE	CHK_UNI_BeforeDialPbxToneDetect(void);
#endif

/* CMNUNI_B.C */
UBYTE  CHK_UNI_PPR_Count(void);
UBYTE  CHK_UNI_PostSpeedHandshake(void);
UBYTE  CHK_UNI_TTI_Inside(void);
UBYTE  CHK_UNI_FSK_TxOpenMethod(void);
UBYTE  CHK_UNI_TTI_Size(void);
UWORD  CHK_UNI_PostMsgPreambleTime(void);
UBYTE  CHK_UNI_OptionSpeedHandshake(void);
UBYTE  CHK_UNI_SpeedHandshakeEx(void);
UWORD  CHK_UNI_SPDToneWaitTime(void);
UWORD  CHK_UNI_SCFRWaitTime(void);
UBYTE  CHK_UNI_ArrivalSignalToneType(void);
UWORD  CHK_UNI_ArrivalSignalToneTxTime(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE  CHK_UNI_Inch_TRx(void);
#endif
UBYTE  CHK_UNI_HiSpeedModeChange(void);
UBYTE  CHK_UNI_SpeedModeChange(void);
UBYTE  CHK_UNI_SDCSModeChange(void);
UBYTE  CHK_UNI_OldFCodeBit(void);
UBYTE  CHK_UNI_FcodeSecureDocPollTx(void);
UBYTE  CHK_UNI_F_CODE_TTI_On(void);
UBYTE  CHK_UNI_SUB_Frame_Off(void);
UBYTE  CHK_UNI_Fcode_ID_Space_Check(void);
UBYTE CHK_UNI_Fcode_Space_Tx_Enable(void);
UBYTE CHK_UNI_FcodeSpaceInputEnable(void);
UBYTE CHK_RelayedTxReport(void);
UBYTE CHK_RelayedTxReportPaperLength(void); /* by H.Kubo 1998/01/19 */
UBYTE CHK_UNI_Error_NonCiperRx(void);	/* 1997/12/08  By T.Yamaguchi */
UBYTE CHK_UNI_JBIG_TX_Enable(void);		/* 1997/12/15  By T.Soneoka */
UBYTE CHK_UNI_JBIG_2lineTemplate(void);	/*  追加 by T.Soneoka 1998/03/16 */
UBYTE CHK_UNI_JBIG_TPB_Mode(void);	/*  追加 by T.Soneoka 1998/03/16 */
UBYTE CHK_UNI_JBIG_SDRST(void);	/*  追加 by T.Soneoka 1998/03/16 */
UBYTE CHK_UNI_CommunicationNeedNSF(void);	/* By M.Tachibana 1998/04/22 */
UBYTE CHK_UNI_ScannerTxMR(void);	/* 1998/11/22 H.Yoshikawa */
UBYTE CHK_UNI_TxLevelUpper0DB(void);	/* 1999/01/05 H.Yoshikawa */

#if (PRO_RESULT_REPORT_TX == ENABLE)	/* Add By O.Kimoto 1998/12/15 */
UBYTE CHK_UNI_ResultReportTxEnable(void);
#endif
#if (PRO_CSDR_ITEM == ENABLE)	/* Add By O.Kimoto 1998/12/15 */
UBYTE CHK_UNI_NoNeedNsfToManualTx(void);
#endif
UBYTE CHK_UNI_T5_Timer(void); /* T5 タイマー(RNR-RR のやり取りの時間制限)の長さ. added by H.Kubo 1999/03/09 */
UBYTE CHK_TxSpeedUpper4800bps(void);
UBYTE CHK_TxSpeedUpper7200bps(void);

#if defined(POPLAR_H) && defined(JP1)/* V851 関西電力専用線 By Y.Suzuki 2003/05/30*/
UBYTE CHK_TransmitBy1300Hz(void);
#endif

#if defined(STOCKHM2) || defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2004/10/26 */ /* Add by Y.Kano 2005/01/11 */
UBYTE CHK_CarBinGammaValue(void);
#endif

/* CMNUNI_C.C */
UBYTE  CHK_UNI_ECM_RxTM_OutEvade(void);
UBYTE  CHK_UNI_MemoryRxAndPrint(void);
UBYTE  CHK_UNI_GenerateBellWait(void);
UWORD  CHK_UNI_TCF_CheckTime(void);
UBYTE  CHK_UNI_OnhookTransferCED_Tx(void);
UBYTE  CHK_UNI_StoredMethodMMR(void);
UBYTE  CHK_UNI_InchMiriConvert(void);
UBYTE  CHK_UNI_ExcellentFIne(void);
UBYTE  CHK_UNI_RemoteRxT1Timer(void);
UBYTE  CHK_UNI_MemoryOverRx(void);
UBYTE  CHK_RelayedReportPrint(void);
UBYTE  CHK_UNI_JunkMode2_Rx_No_TSI(void);
UBYTE  CHK_UNI_JBIG_RX_Enable(void);
UBYTE  CHK_UNI_StartRotateAfterRX(void);
UBYTE  CHK_UNI_G3_RX_StoreMR(void);
UBYTE  CHK_UNI_NewRxStoredMethod(void);		/* プリント時デコード間に合わず対応 By O.Kimoto 1998/04/30 */
UBYTE CHK_UNI_ReducedPixToMid(void);/*By Y.Suzuki 1998/10/06*/
UBYTE  CHK_UNI_GenerateBellPeriod(void);
UBYTE CHK_UNI_R288fExtendedTxFIFO(void); /* by H.Kubo 1998/10/20 */
UBYTE CHK_UNI_R288fExtendedRxFIFO(void); /* by H.Kubo 1998/10/20 */
UBYTE CHK_UNI_R288fExtendedRxEcmFIFO(void); /* by H.Kubo 1998/10/20 */
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/24 */
UBYTE CHK_UNI_V17ReceiveType(void);
UBYTE CHK_UNI_V34ReceiveType(void);
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*/
UBYTE CHK_UNI_V17ReceiveType(void);
UBYTE CHK_UNI_V34ReceiveType(void);
#endif
UBYTE CHK_UNI_TakeCareImadokoMH(void);/*By Y.Suzuki 1998/11/24*/
UBYTE CHK_UNI_RcvResponseTime6sec(void);	/* By M.Tachibana 1999/02/16 */

#if defined(POPLAR_F)
UBYTE	CHK_UNI_FanOnTempThreshold(void);
UWORD	CHK_UNI_FanStopTimerLowTemp(void);
UWORD	CHK_UNI_FanStopTimer(void);
#endif

/*#if defined(POPLAR_H) && defined(JP0)@* V851 By Y.Suzuki 2002/08/23 */
#if (PRO_ROTATE == ENABLE)
UBYTE CHK_UNI_GetMemoryBlockForRotPrt(void);
#endif

/* CMNUNI_D.C */
UBYTE CHK_UNI_Dummy_D(void);
UBYTE CHK_V34SymboleRate(void);
UBYTE CHK_V34Forced2400SymbolRateSNR(void);
UBYTE CHK_V34ARA_AlgorithmEnable(void);
UBYTE CHK_V34ContorlChannelRate(void);
UBYTE CHK_V8TransmitANSamTime(void);
UBYTE CHK_V34ControlChannelRetrain(void);
UBYTE CHK_V34RxDataRateChange(void);
UBYTE CHK_V34RxDataRateChangeType(void);
UBYTE CHK_V34RxDataRateUp(void);
UBYTE CHK_ManualFaxComV8Enable(void);
UBYTE CHK_V34ModemAbcodeEnable(void);
UBYTE CHK_V34DetectCIforMGCS(void);
UBYTE CHK_V34DetectANSam_DuringCI(void);
UBYTE CHK_V34ForcedPPh(void);
UBYTE CHK_RecoverLineProblingProblem(void);
UBYTE CHK_TxLevelAttribute(void);
UBYTE CHK_V34SiganalRateV34Mask(void);
UBYTE CHK_V34ARA_ThresholdARAinROM(void);
UBYTE CHK_V34ManualProcedureEnable(void);
UBYTE CHK_V34SpikeNoiseEvasion(void);
UBYTE CHK_NoCarryOrErrorLineTime(void);
UBYTE CHK_V34_V29_7200Special(void);
UBYTE CHK_V34_AnsFaxSilentLevel(void);
UBYTE CHK_V34_AnsFaxCNGPriorty(void);
UBYTE CHK_V34_V21_R42EvasionEnable(void);
UBYTE CHK_V34_R288F_WayWorkFreqBug(void);
UBYTE CHK_V34_PostExpired(void); /* Added by H.Kubo 1998/02/03 */
UWORD CHK_V34_PreambleTime(void); /* Added by H.Kubo 1998/02/03 */
UBYTE CHK_R288fModemRthLevel(void); /* added by H.Kubo 1998/10/21 */
UBYTE CHK_V34Disable3429SymbolRateSNR(void); /* added by H.Kubo 1999/03/01 */
UBYTE CHK_V34SymbolRateTuningDisable(void);	/* Add By O.Kimoto 1999/10/18 */
UBYTE CHK_V34SymbolRateTuningValue(void);	/*  By O.Kimoto 1999/10/18 */

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
UBYTE CHK_TelFax_AnsFaxV34Mask(void);
 #endif
#endif

/*#if defined(POPLAR_F)*/
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* ANS/FAX待機時の、CNG検出のﾚﾍﾞﾙを上げる */
UBYTE CHK_AnsFaxCNG_DetLevelUp(void);
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
UBYTE	CHK_ReceiveDtmfLevelRange(void);
#endif

/* CMNUNI_E.C */
UBYTE  CHK_UNI_HyperFineON(void);
UBYTE  CHK_UNI_HalfToneEdgeON(void);
UBYTE  CHK_UNI_HalfTone400DPI_ON(void);
UBYTE  CHK_UNI_64ScaleDither(void);
UBYTE  CHK_UNI_FineNormalConvert(void);
UBYTE  CHK_UNI_ReduceGrayCopyDither400(void);
UBYTE  CHK_UNI_ReduceGrayCopyDither200(void);
UBYTE  CHK_UNI_FineCopyEFineScan(void);
UBYTE  CHK_UNI_EFineNonScanLineCount(void);
UBYTE  CHK_UNI_MirrorReadyModeVariable(void);
UBYTE  CHK_UNI_MirrorStaticPositionADF(void);
UBYTE  CHK_UNI_NormalScan4Sec(void);
UBYTE  CHK_UNI_MemTxDocGosaScan(void);
UBYTE  CHK_UNI_CopyDocTopSkipLine(void);
BYTE  CHK_UNI_FBS_AdjustStep(void);
BYTE  CHK_UNI_ADF_AdjustStep(void);
UWORD  CHK_UNI_FBS_LeftMargin(UWORD);
UWORD  CHK_UNI_FBS_RightMargin(UWORD);
UBYTE  CHK_UNI_FBS_TopMargin(void);
UBYTE  CHK_UNI_FBS_BottomMargin(void);
UBYTE  CHK_UNI_SwCopyTestMode(void);
UBYTE  CHK_UNI_ShadingTest(void);
UBYTE CHK_UNI_NormFineScan(void);
UBYTE CHK_UNI_PunchHoleScan(void);
UBYTE CHK_UNI_ReductionPrint(void);
UBYTE CHK_UNI_AdditionalDrumLifeCount(void);/*V851 By Y.Suzuki 2002/09/17*/

/* CMNUNI_F.C */
UBYTE  CHK_UNI_SmoothingCopy2(void);
UBYTE  CHK_UNI_SmoothingRx2(void);
UBYTE  CHK_UNI_SmoothingNormal(void);
UBYTE  CHK_UNI_SmoothingCopyFine(void);
UBYTE  CHK_UNI_SmoothingRxFine(void);
UBYTE  CHK_UNI_SmoothingS_Fine(void);
UBYTE  CHK_UNI_SmoothingH_Fine(void);
UBYTE  CHK_UNI_PowerON_InitialCut(void);
UBYTE  CHK_UNI_THERMAL_HEAD_RANK(void);
UBYTE  CHK_UNI_Reduced1PagePrint(void);
UBYTE  CHK_UNI_MultiRxDocumentPrint(void);
UBYTE  CHK_UNI_PrinterAutoShutTime(void);
UBYTE  CHK_UNI_LeterLegal(void);
UBYTE  CHK_UNI_LaserDensity(void);
UBYTE  CHK_UNI_TransCurrency(void);
UBYTE  CHK_UNI_PrinterCleaning(void);
UBYTE  CHK_UNI_ContinueToPrintForTonar(void);
UBYTE  CHK_UNI_SmoothingE_Fine(void);
UBYTE  CHK_UNI_PrintReductionAjust(void);
UBYTE  CHK_UNI_CopyPrimaryPrint(void);
UBYTE  CHK_UNI_TonerSaveMode(void);
UBYTE  CHK_UNI_LED_StrobeTime(void);
UBYTE  CHK_UNI_TransferVoltage(void);
UBYTE  CHK_UNI_ManualDocWaitTime(void);
UBYTE  CHK_UNI_PcManualDocWaitTime(void);
UBYTE  CHK_PrinterDuty50(void);
UBYTE  CHK_UNI_RestPrintPage(void);
UBYTE  CHK_UNI_PCNonCommunicationTime(void);
UBYTE  CHK_UNI_ResetDrumLife(void);
UBYTE  CHK_UNI_PC_PrintForceReceive(void);
UWORD  CHK_UNI_ReversePrintMemorySize(void);
UBYTE  CHK_UNI_RxDocReversePrint(void);
UBYTE  CHK_UNI_CorrectPartitionPrint(void);	/* By M.Tachibana 1998/06/17 */
UBYTE  CHK_UNI_AdjustPrintReduction(void);	/* By M.Tachibana 1998/06/18 */
UBYTE  CHK_UNI_NewDrumControl(void);	/* By M.Tachibana 1998/07/02 */
UBYTE  CHK_UNI_SizeErrorIgnore(void);	/* By M.Tachibana 1998/08/19 */


/* CMNUNI_G.C */
UBYTE  CHK_UNI_SilentDetectAvailable(void);
UBYTE  CHK_UNI_TEL2_AvailableStartKey(void);
UBYTE  CHK_UNI_TEL2_TEL1Action(void);
UBYTE  CHK_UNI_OnHook24V_Available(void);
/* #if (PRO_LINENUMBER == TWICE_LINE) 1998/06/09 H.Yoshikawa *//* 疑似２回線仕様 by T.Soneoka 1997/12/3 */
UBYTE CHK_UNI_TelOpeDialTx(void);
/* #endif */
UBYTE  CHK_UNI_SecretTelAnsFax(void);
UBYTE  CHK_UNI_FlashKeyOnOffTime(void);
UBYTE  CHK_UNI_NoRingTel2Detachable(void);
UBYTE  CHK_UNI_DetectDSE_Available(void);
UBYTE  CHK_UNI_GenerateRingStopCond(void);
UBYTE  CHK_UNI_DSE_DetectCycle(void);
UBYTE  CHK_UNI_DialInCMLOnAfterOffHook(void);
UBYTE  CHK_UNI_DialinPBX_RxSignalTime(void);
UBYTE  CHK_UNI_AnsFaxDTMFDetect(void);
UBYTE  CHK_UNI_DP_DetectMore(void);		/* 1998/01/26  By T.Yamaguchi */
UBYTE  CHK_UNI_DP_DetectNumber(void);
UBYTE  CHK_UNI_DTMF_ThirdNumber(void);
UBYTE  CHK_UNI_Between_DTMFandDTMF(void);

#if (PRO_CSDR_ITEM == ENABLE)	/* Add By O.Kimoto 1998/12/15 */
UBYTE CHK_UNI_ExtendedCallCount(void);
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 2001/10/03 M.Matsumoto *//* Add By O.Kimoto 2002/03/11 */
UBYTE CHK_UNI_DetectBusyTone(void);
UBYTE CHK_UNI_DetectBusySameTime(void);
#endif

#if (PRO_VOICE_ANSWER == ENABLE)/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2003/12/01 */
UBYTE CHK_UNI_IgnoreBusyTone(void);
#endif

#if (PRO_LINENUMBER == TWICE_LINE)/* V851 By Y.Suzuki 2002/09/19 */
UBYTE CHK_UNI_CHG_CI_DetectTime(void);
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE) || (PRO_VOICE_ANSWER == ENABLE)	/*  By O.Kimoto 2003/12/05 */
UBYTE CHK_UNI_ExtendBusyToneDetectTime(void);
#endif

/* CMNUNI_H.C */
UBYTE  CHK_UNI_SpecialPollingPasscode(void);
UBYTE  CHK_UNI_MemoryOverMessagePrint(void);
#if defined(HINOKI3)	/* 他に空きが無く未使用なのでここを使用します（もし他機種でも使用する時は条件をはずして下さい）by K.Watanabe 2004/12/09 */
UBYTE  CHK_UNI_JournalDescendingPrint(void);
#else
UBYTE  CHK_UNI_JournalLifeMonitorPrint(void);
#endif
UBYTE  CHK_UNI_HumanAnswerClear(void);
UBYTE  CHK_UNI_BuzzerVolume(void);
UBYTE  CHK_UNI_ClearCommunicationError(void);
UBYTE  CHK_UNI_ListFormat3x3(void);
UBYTE  CHK_UNI_UntilReceiveDISLineON(void);
UBYTE  CHK_UNI_RxDocToPollingDoc(void);
UBYTE  CHK_UNI_SecureDocToPollingDoc(void);
#if defined(HINOKI3)	/* 他に空きが無く、条件コンパイル的に未使用なので、ここを使用します by K.Watanabe 2005/01/05 */
UBYTE  CHK_UNI_JournalFixedFormSizeCut(void);
#else
UBYTE  CHK_UNI_FIP_DocToPollingDoc(void);
#endif
UBYTE  CHK_UNI_TxDocToPollingDoc(void);
UBYTE  CHK_UNI_ScrambleDocToPollingDoc(void);
UBYTE  CHK_UNI_DRAM_BackupTime(void);
UBYTE  CHK_UNI_DRAM_BackupTest(void);
UBYTE  CHK_UNI_T30_IntervalPrint(void);
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
UBYTE  CHK_UNI_JrnlInternalSeprate(void);
#endif
UBYTE  CHK_UNI_OptionalSpeedDial(void);
UBYTE  CHK_UNI_JunkMailProtectDial(void);
UBYTE  CHK_UNI_Fcode_RxMessageOff(void);
UBYTE  CHK_UNI_ContPollingDaily(void);
UBYTE  CHK_UNI_PcMemoryOverMsgPrint(void);
UBYTE  CHK_UNI_OrderListPrint(void);
UBYTE  CHK_UNI_TCR_NoneTxTime(void);
UBYTE  CHK_UNI_PriorOrderListPrint(void);
UBYTE  CHK_UNI_MaskingDram(void);
UBYTE  CHK_UNI_ManualTxTimeManage(void);
UBYTE  CHK_UNI_KeyMacroActionTime(void);	/* 1998/06/19 Add By M.Kuwahara */
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/15*/ /* || (PRO_ENERGY_SAVE == ENABLE) 見送る */ /* 2002/11/29 T.Takagi */
UBYTE  CHK_UNI_EcoModeStartTime(void);
#endif
UBYTE  CHK_UNI_ManualRxTimeManage(void);
UBYTE  CHK_UNI_StampKeyEnable(void);
UBYTE  CHK_UNI_SilentOperation(void);
UBYTE  CHK_UNI_F_NET_ExtLineEnable(void);	/**	疑似２回線F網接続設定   by T.Soneoka 1997/11/21	*/
UBYTE  CHK_DaytimeStartTime(void);
UBYTE  CHK_NightStartTime(void);
UBYTE  CHK_MidnightStartTime(void);
UBYTE  CHK_BaseCostInCostTable(void);
UBYTE CHK_UNI_ND_JournalErrorReport(void); /* by H.Kubo 1998/10/23 */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*/	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */

UBYTE CHK_UNI_CSDR_ConfirmOprEnable(void);
UBYTE CHK_UNI_CSDR_TtiTxOprEnable(void);
UBYTE CHK_UNI_CSDR_DialMarkExchange(void);
#endif

UBYTE CHK_TcrWithDocument(void); /* Atlanta TCR画像つける・つけないSW追加 1999/08/26 M.Maeda */
UBYTE CHK_UNI_NoTripleRestrict(void);	/* 1999/02/18 by T.Soneoka */
UBYTE CHK_UNI_ExtSecurityRxOperation(void);	/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */

/* CMNUNI_I.C */
UBYTE	CHK_UNI_Dummy_I(void);
void	CHK_SetT30Sign(UBYTE line_no);
UBYTE	CHK_GetT30Sign(void);
UBYTE	CHK_PrintR288FMonitorEnable(void);
UBYTE	CHK_UNI_MultiDisplayEnable(void);
UBYTE	CHK_UNI_MultiDisplayLineNumber(void);
UBYTE	CHK_UNI_MultiDisplayTime(void);
UBYTE	CHK_UNI_MultiDisplayTwiceLine(void);	/* Add By O.Kimoto 1998/03/06 */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
/*#if (PRO_KEYPANEL == PANEL_ANZU_L)		@ 1998/06/03 Y.Murata ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4*/
UBYTE	CHK_UNI_AramcoSuportA4Paper(void);
#endif
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1998/06/15 Y.Murata */
UBYTE	CHK_UNI_CIL_Inside(void);
UBYTE	CHK_UNI_CILPrintOn(void);
UBYTE	CHK_UNI_CIL_TSIPrintOn(void);
#endif
UBYTE 	CHK_UNI_DialWithin(void);	/* 1998/10/26 Y.Matsukuma */
UBYTE	CHK_JournalYearPrint(void);	/* 西暦４桁対応 addedbythonda1999/11/16	*/
									/* ICHOUから移植してきました			*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/23 Eguchi*/
UBYTE	CHK_UNI_INF_MinimumSetAvail(void);
UBYTE	CHK_UNI_INF_Baudrate(void);
#endif
UBYTE	CHK_UNI_CatchPhoneON(void);	/* Add By M.Tachibana 1998/11/09 */

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
UBYTE CHK_UNI_VoiceAnswerEnable(void);
 #endif
#endif

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/07 */
UBYTE	CHK_UNI_MultiT30Monitor(void);
#endif
#if (PRO_PRINT_TYPE == LED)	/* By M.Tachibana 1999/10/06 */
UBYTE	CHK_UNI_PrimaryListSize(void);
UBYTE	CHK_UNI_PrimaryTestSize(void);
#endif
UBYTE	CHK_UNI_JournalPriority(void);	/* added by H.Hirao 2000/12/05 */

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/07 By M.Maeda */
UBYTE	CHK_UNI_CommandResult(void);
#endif

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り */
UBYTE	CHK_UNI_RedScanModeEnable(void);	/* 2002/03/04 T.Takagi */
#endif

#if defined(JPN)
UBYTE CHK_UNI_WordingChangeEnable(void);	/* 2002/08/29 By M.Maeda */
#endif

#if (PRO_ENERGY_SAVE == ENABLE)
UBYTE CHK_UNI_PC24V_RelayTestEnable(void);	/* 2002/12/03 T.Takagi */
#endif
#if defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)
UBYTE CHK_UNI_IgnoreNEWC_Reset(void);		/* 2002/12/11 T.Takagi */
#endif

#if defined(SATSUKI2) || defined(STOCKHM2)	/* 旧SATSUKIから持ってきました。by Y.Kano 2003/10/01 */
UBYTE CHK_UNI_CiRescueEnable(void); /* CI割込み救済2 O.Oshima 2003/11/26 */
UBYTE CHK_WallHangSetting(void);
UBYTE CHK_StoringFlashEnable(void); /* SMuratec H.C.H 2003/10/30 */
UBYTE CHK_YearChangeEnable(void);	/* 経年変化対応チェック by Y.Kano 2003/10/31 */
#endif

#if defined(STOCKHM2)	/* Add by Y.Kano 2004/07/09 */
UBYTE CHK_HeatTableEnable(void);	/* ＳＴＯＣＫＨＭ２用ヒートテーブル有効／無効の獲得 */
UBYTE CHK_PreHeatTableEnable(void);	/* ＳＴＯＣＫＨＭ２用プレヒートテーブル有効／無効の獲得 */
UBYTE CHK_DisasterPreventionFaxEnable(void);	/* ＳＴＯＣＫＨＭ２用防災ＦＡＸの無効/有効の獲得 by Y.Kano 2004/08/19 */
UBYTE CHK_VoiceCallEnable(void);	/* QAT:会話予約有効/無効の獲得 by SMuratec 夏 2004/11/03 */
#endif

/* CMNUNI_J.C */
UBYTE	CHK_UNI_WaitTempAdjust(void);
UBYTE	CHK_UNI_MotorStartTempAdjust(void);
UBYTE	CHK_UNI_FanLockDetectTime(void);		/*V851  機内FANﾛｯｸ対策 By Y.Suzuki 2002/09/26 */
UBYTE	CHK_UNI_PrintTempAdjust(void);
UBYTE	CHK_UNI_CassetteSizeAdjust(void);
UBYTE	CHK_UNI_RotateAdjustDistortion(void);
UBYTE	CHK_UNI_SelectableCopyMode(void);/* By Y.Suzuki 1999/11/29 */
UBYTE	CHK_UNI_RotatePageCompound(void);
UBYTE	CHK_UNI_RotateHorizontalMargin(void);
UBYTE	CHK_UNI_RxRemoteFaxOnClass1Busy(void);	/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
#if (PRO_EX_CLASS1 == DISABLE)
UBYTE	CHK_Class1CiTimeupRingCount(void);		/* PRO_CL1_TELFAX_LAN S.Fukui June 19,1998  */
#endif
UBYTE	CHK_UNI_PcPrintInchMmConvert(void);		/* By M.Tachibana 1998/11/11 */
UBYTE	CHK_UNI_PostCardFeedback(void);			/* By M.Tachibana 1998/12/07 */
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
UBYTE	CHK_UNI_PrimaryReadyMode(void);			/* by K.Watanabe 1999/01/20 */
#endif	/* Add By O.Kimoto 1999/08/06 */
UBYTE	CHK_UNI_CopyPrimaryMode(void);			/* by K.Watanabe 1999/01/20 */
/* #endif *//* Delete By O.Kimoto 1999/08/06 */
UBYTE CHK_UNI_SortCopyOn(void);					/* By Y.Suzuki 1999/02/15 */
UBYTE CHK_UNI_FaxAnd1Copy(void);				/* By H.Yoshikawa 1999/02/17 */
UBYTE CHK_UNI_TSI_RelayTrans(void);				/* by H.Hirao 1999/04/14 */
UBYTE CHK_UNI_TSI_MurataRelayTrans(void);		/* by H.Hirao 1999/04/14 */
UBYTE CHK_UNI_Class1_EXT_Function(void);	/* 1999.6.14 K.Kawata */
UBYTE CHK_UNI_TSI_RelayTxCenterPrint(void);	/* 折り返し特ＲＯＭセンターでも印字（RDC200100059) by O.Kimoto 2001/02/22 */
#if defined(POPLAR_H) && defined(JP0)/*By Y.Suzuki 2003/04/07*/
UBYTE CHK_UNI_PrimaryPaperForB5R_Doc(void);
#endif
UBYTE CHK_UNI_OCA_ForSAKAKI2(void);	/* 2003/09/20 H.Yoshikawa */
#if defined(STOCKHM2) /* 本体鳴動のテスト :by SMuratec C.P 2004/09/27 */
UBYTE	CHK_CallingBuzzerMode(void);
#endif
UBYTE CHK_V23_BellcoreEnable(void);
UBYTE CHK_V23_TxParitySetting(void);

