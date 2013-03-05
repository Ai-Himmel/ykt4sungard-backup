#ifndef cmn_pro_h
	#define cmn_pro_h
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\timer10.h"
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\time.h"
#include "\src\atlanta\define\sysmcopy.h"

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun. 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/09/02 By M.Kuwahara */
#include "\src\atlanta\define\syswarp.h"
#endif

/************************************************************************
 * 文字列操作に関するプロトタイプ宣言									*
 * cmn_str.c															*
 ************************************************************************/
UBYTE  *CMN_StringCopyNULL(UBYTE  *dst_ptr,CONST UBYTE  *src_ptr);
UBYTE  *CMN_StringCopyNumOrNULL(UBYTE  *dst_ptr,CONST UBYTE  *src_ptr,register WORD  str_cnt);
UBYTE  *CMN_StringCopy(UBYTE  *dst_ptr,CONST UBYTE  *src_ptr);
UBYTE  *CMN_StringCopyNum(UBYTE  *dst_ptr,CONST UBYTE  *src_ptr,register WORD  str_cnt);
UBYTE  *CMN_StringCopyNumUntilNull(UBYTE  *dst_ptr,CONST UBYTE  *src_ptr,register WORD  str_cnt);
UWORD  *CMN_IntDataCopyNum(UWORD  *dst_ptr,UWORD  *src_ptr,register WORD  str_cnt);
UBYTE  *CMN_MemorySetNULL(UBYTE  *dst_ptr,UWORD  size,UBYTE  data);
UBYTE  *CMN_MemorySet(UBYTE  *dst_ptr,UWORD  size,UBYTE  data);
UWORD  *CMN_WordMemorySet(UWORD  *dst_ptr,UWORD  size,UWORD  data);
UBYTE  CMN_MSB_LSB_Invert(UBYTE  data);
UBYTE  CMN_StringLength(CONST UBYTE  *string);
UBYTE  CMN_StringLengthCR(CONST UBYTE  *string);
UBYTE  CMN_StringLengthSP(UBYTE  *string);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE  CMN_StringCompare(UBYTE  *string1,UBYTE  *string2,UBYTE  size);
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
#if (PRO_JIS_CODE == ENABLE)
UBYTE	CMN_CheckJIS1Code(CONST UWORD);
UBYTE	CMN_CheckFontJIS2Code(CONST UWORD);
UBYTE	CMN_CheckShiftJISCode(CONST UBYTE, CONST UBYTE);
#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/  /* SANYO仕様の追加 2000/02/25 N.Kondo */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* SANYO仕様の追加 2000/02/25 N.Kondo */ /* Add by Y.Kano 2003/07/11 */

UBYTE  CMN_StringCompare2(UBYTE  *string1,UBYTE  *string2,UBYTE  size);
#endif
void  CMN_StringReverse(UBYTE  *string);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE  CMN_isdigit(UBYTE  data);
#endif
UBYTE  *CMN_StringCopyNumNotNULL(UBYTE  *DST_String,UBYTE  *SRC_String,UBYTE  CopyCount);
UBYTE  *CalculateStringAddress(UBYTE  *Address);
UBYTE  CMN_CheckBitAssign(UBYTE  *buf,UBYTE  pos);
void  CMN_SetBitAssign(UBYTE  *buf,UBYTE  pos);
void  CMN_ClearBitAssign(UBYTE  *buf,UBYTE  pos);
UBYTE CMN_CheckLongBitAssign(UDWORD buf, UBYTE pos);
void  CMN_SetLongBitAssign(UDWORD *buf, UBYTE pos);
void  CMN_ClearLongBitAssign(UDWORD *buf, UBYTE pos);
UBYTE CMN_GetRemoteTransferDialString(UBYTE * str);	/* REMOTE_RX_FUNC 設定表示 By M.Maeda 2003/02/07 */

/************************************************************************
 * データ変換に関するプロトタイプ宣言									*
 * cmn_cnv.c															*
 ************************************************************************/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
void  CMN_UnsignedIntToASC_NULL(UBYTE  *dst_string,UWORD  data,UBYTE  size,UBYTE  pad_data);
#endif
void  CMN_UnsignedIntToASC(UBYTE  *dst_string,UWORD  data,UBYTE  size,UBYTE  pad_data);
void  CMN_UnsignedLongToASC_NULL(UBYTE  *dst_string,UDWORD  data,UBYTE  size,UBYTE  pad_data);
void  CMN_UnsignedLongToASC(UBYTE  *dst_string,UDWORD  data,UBYTE  size,UBYTE  pad_data);
void  CMN_UnsignedLongToHexASC_NULL(UBYTE  *dst_string,UDWORD  data,UBYTE  size,UBYTE  pad_data);
UWORD  CMN_ASC_ToUnsignedInt(UBYTE  *src_ptr,UBYTE  size);
UWORD  CMN_ASC_ToUnsignedIntHex(UBYTE  *src_ptr,UBYTE  size);
void  CMN_BCD_ToASC_String(UBYTE  *ASC_ptr,UBYTE  *BCD_ptr);
UBYTE  CMN_BCD_ToASC(UBYTE  BCD);
void	CMN_FCODE_BCD_ToASC_String(UBYTE  *ASC_ptr,UBYTE  *BCD_ptr);
void	CMN_BCD_Number_ToASC_String(UBYTE  *ASC_ptr,UBYTE  *BCD_ptr);
void	CMN_NoSpaceBCD_ToASC_String(UBYTE  *ASC_ptr,UBYTE  *BCD_ptr);
UBYTE	CMN_FCODE_BCD_ToASC(UBYTE BCD);
UBYTE  CMN_FXBCD_ToASC(UBYTE  BCD);
void  CMN_ASC_ToBCD_String(UBYTE  *BCD_ptr,UBYTE  *ASC_ptr);
void	CMN_ASC_ToBCD_StringNumber(UBYTE  *BCD_ptr,UBYTE  *ASC_ptr, UBYTE	figure); /* 桁数指定 1997/10/23  By T.Yamaguchi */
UBYTE  CMN_ASC_ToBCD(UBYTE  ASC);
UBYTE  CMN_ASC_ToFXBCD(UBYTE  ASC);
UDWORD  CMN_BCD_TimeToLong(TIME_DATA_t *BCD_time);
UBYTE  CMN_BCD_ToDecimal(UBYTE  BCD);
void  CMN_LongTimeToBCD(TIME_DATA_t *BCD_time,UDWORD  long_time);
UBYTE  CMN_DecimalToBCD(UBYTE  decimal);
void  CMN_BCD_To2ASC_String(UBYTE  *ASC_ptr,UBYTE  BCD,UBYTE  pad_data);
UBYTE  CMN_DecimalToHex(UBYTE  decimal);
UBYTE  CMN_OffsetToOnetouchCode(UBYTE  one_pos);
UBYTE  CMN_OnetouchCodeToOffset(UBYTE  onetouch);
void  CMN_BCD_ToASC_StringNum(UBYTE  *ASC_String,UBYTE  *BCD_String,UBYTE  ASC_Count);
void  CMN_ASC_ToBCD_StringNum(UBYTE  *BCD_String,UBYTE  *ASC_String,UBYTE  ASC_Count);
void  CMN_HexToASC(UBYTE  *DST_String,UDWORD  HexCode,UBYTE  Count);
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* 移植 by SMuratec L.Z.W 2003/08/13 */
#if (PRO_JIS_CODE == ENABLE)
UWORD	CMN_JIS_ToShiftJIS(CONST UWORD);
void	CMN_ShiftJIS_ToJIS(UWORD *, UWORD *);
void	CMN_ShiftJIS_ToASC_KUTEN_Code(UWORD *, UWORD *, UBYTE *);
UWORD	CMN_ASC_KUTEN_CodeToJIS(CONST UBYTE *);
#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */


/************************************************************************
 * 機器状態の確認に関するプロトタイプ宣言								*
 * cmn_chk.c															*
 ************************************************************************/
UBYTE  CMN_CheckPrinting(void);
UBYTE  CMN_CheckPrintEnable(UWORD request_machine_status);
UBYTE  CMN_CheckPaperExist(void);
UBYTE  CMN_CheckNoPrinterError(void);
UBYTE  CMN_CheckPrinterCoverClose(void);
UBYTE  CMN_CheckBothCassetteClose(void);
UBYTE  CMN_CheckMemRxPrintEnable(void);
UBYTE  CMN_CheckScanEnable(void);
UBYTE  CMN_CheckMemoryReceiveEnable(void);
UBYTE  CMN_CheckAutoCalledEnable(void);
UBYTE  CMN_CheckAutoDialEnable(void);
/* UWORD  CMN_CheckMultiLineReceiveNumber(UBYTE StackNo, UBYTE ReceiveMode); */
UBYTE  CMN_CheckMultiLineReceiveEnable(void);	/* 1997/03/19  By T.Yamaguchi */
UBYTE  CMN_CheckLineEnable(void);
UBYTE  CMN_CheckTwiceLineEnable(UBYTE line);
UBYTE  CMN_CheckMulicopyEnable(void);
UBYTE  CMN_CheckFeederCommandEmpty(void);
UBYTE  CMN_CheckMemoryTxCommand(UBYTE com_no, UBYTE status_chk);
UBYTE  CMN_CheckScannerTxCommand(UBYTE com_no);
UBYTE  CMN_CheckDocumentOnFeeder(void);
UBYTE  CMN_CheckScanDocOnFeeder(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE  CMN_CheckFaxComPrinterEnable(void);
UBYTE  CMN_CheckFaxComPrinterError(void);
#endif
UBYTE  CMN_CheckScannerCoverClose(void);
UBYTE  CMN_CheckPollingReceiveEnable(void);
UBYTE  CMN_CheckMultiCopyPrintEnable(void);
UBYTE  CMN_CheckManualCopyPrintEnable(void);
UBYTE  CMN_CheckPrinterError(void);
UBYTE  CMN_CheckCassettePaper(UBYTE  cassette);
UBYTE  CMN_CheckPrinterStop(void);
UBYTE  CMN_WaitingPrintDocument(struct SYS_MultiCopyData_t *mcopy_ptr);
UBYTE  CMN_CheckInitializeKeyON(void);
UBYTE  CMN_CheckDS1Status(void);
UBYTE  CMN_CheckScanFilePrinting(void);
UBYTE  CMN_CheckCassetteUnit(void);
#if (PRO_PC_PRINT == ENABLE)
UBYTE	CMN_CheckSuportPaperExist(UBYTE cassette);
UBYTE	CMN_CheckPcCassettePaper(UBYTE cassette);
#endif
#if 0	/* 削除 */
UWORD  CMN_GetMemoryRxPrintNumber(void);
UBYTE  CMN_CheckMemRxPrintStatus(UWORD No);
UWORD  CMN_GetMultiLineReceiveNumber(UBYTE StackNo);
#endif
UBYTE  CMN_CheckFCOT_Enable(void);
UBYTE  CMN_CheckEncodeMG3_Enable(UBYTE item);
UBYTE  CMN_CheckFcodeCommand(UBYTE item);
UBYTE  CMN_CheckMemoryTxSetting(void);
UBYTE  CMN_CheckFcodeEnable(void);	/* Ｆコード対応 By O.Kimoto 1996/06/14 */ /* Added by H.Kubo 1997/07/08 */
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE  CMN_CL1CheckMemoryReceiveEnable(void); /* クラス１ 1997/07/16 Y.Matsukuma */
#endif
UBYTE  CMN_CheckActiveClass1(void); /* Ported from Clover by H.Kubo 1997/07/22 */

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
UBYTE CMN_CheckMultiCasseteUnit(void);	/* Add By O.Kimoto 1997/07/22 */
#endif
UBYTE CMN_CheckMemoryTxDocStoring(void);
UBYTE CMN_CheckPanelBusy(void); /*	By Y.Suzuki 1997/10/08	*/
#if (PRO_DIALIN == ENABLE)
UBYTE CMN_CheckInputDialInNumber(void);
#endif
UBYTE	CMN_CheckBroadcastCommand(UWORD);
UBYTE	CMN_CheckF100Model(void);
UBYTE	CMN_NormalScan4Sec(void);
#if (PRO_CIPHER == ENABLE)
UBYTE CMN_CheckScrambleBusy(void);
#endif
UBYTE CMN_CheckTelFaxSuport(void);	/* 1997/12/19 */
UBYTE CMN_CheckCategory2(void);	/*1997/12/25 M.Kotani*/
UBYTE CMN_CheckOptionBoardExecuting(void);	/* By M.Tachibana 1997/12/21 */
UBYTE CMN_CheckCipherPrintEnable(void);
UBYTE CMN_CheckCpuVersion(void);/* By Y.Suzuki 1998/01/26 */
UBYTE CMN_CheckAramcoModel(void); /* 1998/03/12 Y.Matsukuma */
UBYTE CMN_TCR_PrintRequestCheck(UWORD cmmand);	/* 1998/04/21  By T.Yamaguchi */

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
	UBYTE CMN_CheckMinoltaTestFuncEnable(void);
	UWORD CMN_SetMinoltaTestFuncData(UWORD No, UWORD Page, UWORD Time);
	UWORD CMN_CheckMinoltaTestPrintEnable(void);
	UWORD CMN_CheckMinoltaTestDataStore(UWORD No);
	void CMN_MinoltaDataInitFla(void);
	UBYTE CMN_CheckMinoltaFlashEnable(void);
#endif

#if (PRO_REVERSE_PRINT == ENABLE)	/* By M.Tachibana 1998/05/19 */
UBYTE CMN_CheckFastPrintStart(void);
UBYTE CMN_CheckOptionFastPrintStart(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
/*#if (PRO_KEYPANEL == PANEL_ANZU_L)		@ 1998/06/03 Y.Murata ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4*/
UBYTE CMN_CheckAramcoSuportA4Paper(void);
#endif
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1998/06/15 Y.Murata */
UBYTE CMN_CheckCILEnable(void);
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */
	UBYTE CMN_CheckMemoryForMemTx(void);
	UBYTE CMN_CheckMemoryForMemRx(void);
	UBYTE CMN_CheckMemoryQucikTxCont(void);
	UBYTE CMN_CheckMemoryQucikTxStart(void);
#endif

/*#if defined(POPLAR_H) && defined(JP0)@* V851 By Y.Suzuki 2002/08/23 */
#if (PRO_ROTATE == ENABLE)
UBYTE CMN_CheckMemoryForRotPrt(void);
#endif


#if defined(POPLAR_F)
	UBYTE CMN_CheckAnswerEnable(void);
	UWORD	CMN_GetFanStopTimer(void);	/* FAN騒音対策 */
#endif

#if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/19 T.Takagi */
UBYTE	CMN_Check24V_OffEnable(void);
UBYTE	CMN_CheckClockOffEnable(void);
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/15*/
UBYTE CMN_CheckAvailableEcoMode(void);
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
UBYTE CMN_ShiftEcoModeEnable(void);
#endif

#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
BOOL CMN_CheckScrambleSwOn(void);
#endif

/************************************************************************
 * 機器状態をリセットすることに関するプロトタイプ宣言					*
 * cmn_rst.c															*
 ************************************************************************/
void  CMN_ResetPrimaryMode(void);
void  CMN_ResetPrimaryContrast(void);
#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/21 */
void  CMN_ResetPrimaryCopyMode(void);
void  CMN_ResetPrimaryCopyContrast(void);
#endif
void  CMN_ResetMemoyFeederTx(void);
void  CMN_ResetStamp(void);
void  CMN_ResetPrimaryDocumentSize(void);
void  CMN_ResetConfirmationReport(void);
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り */
void  CMN_ResetRedScan(void);	/* 2002/03/05 T.Takagi */
#endif
#if defined(SATSUKI2)	/* F250用A/Dセンサー調整機能 by Y.Kano 2004/01/14 */
void  CMN_CheckNewFunction(void);
#endif

#if defined(HINOKI2) || defined (HINOKI3)	/* F351用新機能チェック追加 by Y.Kano 2004/04/01 */
void  CMN_CheckNewFunction(void);
#endif

/************************************************************************
 * 機器状態の設定に関するプロトタイプ宣言								*
 * cmn_com.c															*
 ************************************************************************/
UBYTE  CMN_GetMulticopyArea(void);
UBYTE  CMN_GetDocumentScanSize(void);
UBYTE  CMN_GetFBS_DocumentScanSize(void);
UBYTE  CMN_GetCommandArea(void);
void  CMN_ClearCommandArea(UBYTE  com_type,UBYTE  com_no);
UBYTE  CMN_PresentReceiveMode(void);
UBYTE  CMN_ChangeVoiceSwitch(void);

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/24 */
/* return value ex.: DATA_SIGNALING_RATE_V34_BIT. See fcm_def.h */
UWORD CMN_GetDataSignalingRate(void);	/* 1996/01/18 Y.M */
UWORD CMN_SetDataSignalingRate(UWORD); /* 1997/07/24 H.Kubo */
UWORD CMN_ResetDataSignalingRate(UWORD);	/* 1997/07/24 H.Kubo*/
UBYTE CMN_GetVoiceSwitch(void); /* by H.Kubo 1998/01/08 */
#endif /* (PRO_TX_SPEED == V34) */

/************************************************************************
 * 10msタイマに関するプロトタイプ宣言									*
 * cmn_tup.c															*
 ************************************************************************/
void  CMN_WatchTimer10msTask(struct  Timer10msData_t *timer10ms_ptr);
void  CMN_WatchTimer10msEventTask(struct  Timer10msEventData_t *timer10ms_ptr);
void  CMN_MAN_Timer10msTask(struct  Timer10msData_t *timer10ms_ptr);
void  CMN_EventToMessageTask(struct  EventToMessageData_t *data_ptr);
void  CMN_MultiTimer10msTask(void);
void  CMN_MultiTimer10msStart(UBYTE  *timer_id,struct  Timer10msData_t *timer10ms_ptr);
void  CMN_MultiTimer10msStop(UBYTE  *timer_id);

/************************************************************************
 * 機器状態,ＲＡＭ，ユーザデータの初期化に関するプロトタイプ宣言		*
 * cmn_ini.c															*
 ************************************************************************/
UBYTE  CMN_CheckBackUpRAM(void);
void  CMN_InitializeMachineParameter(void);
void  CMN_InitializeMemorySwitch(void);
void  CMN_ClearMailBox(UWORD  i);
void  CMN_ClearSpeedDial(UWORD  i);
void  CMN_ClearOnetouchDial(UWORD  i);
void  CMN_ClearProgramOnetouch(UWORD  i);
void  CMN_ClearJunkDial(UWORD i);
void  CMN_ClearSubDial(UWORD  i);
#if (PRO_F_CODE == ENABLE)
void  CMN_ClearFcodeBox(UWORD i);	/* 1997/03/11  By T.Yamaguchi */
#endif
void  CMN_AllClearDepartFile(void);
void  CMN_ClearDepartFile(UWORD);
void  CMN_AllClearDepartManageFile(void);  /* added by thonda 1997/11/27 */
void  CMN_ClearDepartManageFile(UWORD);    /* added by thonda 1997/11/27 */
void  CMN_ClearCostData(void);
void  CMN_ClearCostTable(UWORD i);
void  CMN_ClearNTT_AccessFile(UWORD);
void  CMN_ClearBatchTxFile(UWORD  i);
void  CMN_ClearCoverPageMessage(void);
void  CMN_ClearID_Buffer(void);
void  CMN_ClearTTI_Buffer(void);
void  CMN_ClearTTI_ID_Buffer(void);
void  CMN_ClearDialin(void);
void  CMN_ClearLifeMonitorData(void);
void  CMN_ClearPrinterLifeMonitorData(void);
void  CMN_ClearFaxComErrorMonitorData(void);
void  CMN_ClearJournalData(void);
void  CMN_ClearCipherKey(UWORD);
void  CMN_ClearCipherBox(UWORD);
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
void  CMN_MercuryDial(UWORD i);
#endif
void  CMN_ClearConsumerOrderData(void);
#if (PRO_CIPHER == ENABLE)
void  CMN_ClearCipherPData(UBYTE prg_no);
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/08/31 Add By M.Kuwahara */
void CMN_ClearWarpData(UBYTE i);
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/08/31 Add By M.Kuwahara */
void CMN_Clear_ND_Data(UBYTE i);
#endif
void  CountryCodeSet(void);
void  CMN_InitializeUniqSwitch(void);
void  CMN_InitMaintenanceSwitch(void);
void  CMN_InitializeAllBackUpRAM(UBYTE  mode);
void  CMN_InitializeOptionData(UBYTE mode);
UBYTE  CMN_CheckOptionChange(void);
void  SetWording(UBYTE);
#if (0)	/* 未使用なので削除します by K.Watanabe 1998/07/10 */
//void  CalculateWordingOffset(void);
#endif
void CMN_InitializeMultiLineData(UBYTE mode);
void CMN_InitializeModelChangeRAM(void);
void CMN_UpdateMultiBackupRAM(UBYTE mode);
UBYTE  CMN_CheckDRAM_BackupTestArea(void);
void CMN_InitDRAM_BackupTestArea(void);

/********************************************************
 * ブザー鳴動に関するプロトタイプ
 * 1996/02/21 Eguchi
 * CMN_BUZZ.C
 ********************************************************/
void  CMN_BuzzerTask(void);
void  AckBuzzerSound(void);
void  NackBuzzerSound(void);
void  CMN_EndBuzzerTask(void);
void  CMN_EndBuzzerExit(void);
void  CMN_HoldAlarmTask(void);
void  CMN_ErrorAlarmTask(void);
void  CMN_ErrorAlarmExit(void);
void  CMN_ErrorEndlessAlarmTask(void);
void  CMN_ErrorEndlessAlarmExit(void);
void  CMN_HungUpErrorAramTask(void);
void  CMN_HungUpErrorAramExit(void);
void  CMN_HoldEndBuzzerTask(void);
void  BuzzerOnSetting(UWORD  buzzer_type);
void  BuzzerOffSetting(UWORD  buzzer_type);
UBYTE  CheckOtherBuzzerSound(UWORD  buzzer_type);
UWORD  CheckBuzzerSound(void);
void  CMN_PaperSupplyBuzzer(void);

/*******************************************************
 * ＭＴＵに関するプロトタイプ
 * 1997/02/19 M.Tachibana
 * CMN_TMR.C
 *******************************************************/
void  CMN_SetupPrintOneshotTimer(void);
void  CMN_StartPrintOneshotTimer(void);
void  CMN_StopPrintOneshotTimer(void);
void CMN_ModemWait100microSec(UWORD time); /* added by H.Kubo 1999/01/25 */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/************************************************************************
 * プロトタイプ宣言
 * 1998/03/31 Y.Tanimoto
 * CMN_INF.C
 ************************************************************************/
UBYTE	CMN_CheckUpdateUserData(UBYTE);
UBYTE	CMN_CheckEraseUserData(UBYTE);
void	CMN_EraseUserData(UBYTE);
void	CMN_ClearUserData(UBYTE);
void	CMN_ClearAllUserData(void);
void	CMN_ClearAutoRcvData(UBYTE);
void	CMN_ClearAllAutoRcvData(void);
UBYTE	CMN_CheckAndReserveMailCommand(void);
void	CMN_ClearMailCommand(UBYTE);
void	CMN_ClearAllMailCommand(void);
void	CMN_RecoverMailCommand(void);
UBYTE	CMN_CheckFreeMemoryArea(void);
UBYTE	CMN_CheckMailBox(void);
UBYTE	CMN_CheckMailRcvEnable(void);
UBYTE	CMN_ReserveMailBox(UBYTE ,UBYTE);
UBYTE	CMN_CheckAndReserveMailBox(UBYTE);
void	CMN_SetRxMailBox(UBYTE);
void	CMN_ReleaseTopMailBox(UBYTE);
void	CMN_ReleaseMailBox(UBYTE);
void	CMN_RecoverMailBox(void);
void	CMN_ClearRxMailBox(UBYTE);
void	CMN_ClearAllMailBox(void);
void	CMN_ClearReservedMailBox(void);
void	CMN_ClearPrintPosition(UBYTE);
void	CMN_ClearAllPrintPosition(void);
UWORD	CMN_GetRxMailPrintStartPage(UBYTE , UWORD, UBYTE);
void	CMN_SetOnetouchStatus(void);
void	CMN_SetProgramOnetouchStatus(void);
void	CMN_ClearOnetouchMailData(UBYTE);
void	CMN_ClearAllOnetouchMailData(void);
void	CMN_ClearGroupMailData(UBYTE);
void	CMN_ClearAllGroupMailData(void);
void	CMN_ClearOneHistoryBox(UBYTE,UBYTE);
void	CMN_ClearHistoryBox(UBYTE);
void	CMN_ClearAllHistoryBox(void);
UBYTE	CMN_CheckEmptyHistoryBox(UBYTE);
void	CMN_ReleaseHistoryBox(UBYTE, UBYTE);
UBYTE	CMN_CompareHistoryData(UBYTE *, UBYTE, UBYTE);
void	CMN_SetHistoryBox(UBYTE, UBYTE);
void	CMN_RecoverHistoryBox(void);
void	CMN_ClearCommandCounter(UBYTE);
void	CMN_ClearAllCommandCounter(void);
void	CMN_ClearRxMailCounter(UBYTE);
void	CMN_ClearAllRxMailCounter(void);
void	CMN_ClearPrintRequest(UBYTE,UBYTE);
void	CMN_ChangeAutoRcvComStatus( UBYTE );
void	CMN_ClearSecureNoticeRequest( UBYTE );
void	CMN_ClearMailJournalData( UBYTE );
void	CMN_ClearAllMailJournalData( void );
void	CMN_ClearAllStoreDocParameter( void );
void	CMN_ClearUserDataStatus( UBYTE );
void	CMN_ClearAllUserDataStatus( void );
void	CMN_ReleaseHoldTimeoutMailBox( UBYTE );
UBYTE	CMN_CheckMailBoxPrintStatus( UBYTE );
void	CMN_ClearPrintJournalData(void);/*1998/05/22 Eguchi */

#endif	/* end of PRO_DIALUP_INTERNET_FAX */

/********************************************************
 * Ｉ／Ｏに関するプロトタイプ
 * 1996/10/24 M.Kotani
 ********************************************************/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
void  outp(UDWORD, UBYTE);
void  outpw(UDWORD, UWORD);
UBYTE inp(UDWORD);
UWORD  inpw(UDWORD);
void  CMN_EnableInterrupt(void);
void  CMN_DisableInterrupt(void);
#endif
void  outpdw(UDWORD, UDWORD);
UDWORD  inpdw(UDWORD);
UWORD  CheckInterruptEnable(void);

/********************************************************
 * ワープ機能に関するプロトタイプ
 * 1998/09/02 M.Kuwahara
 ********************************************************/
#if (PRO_RX_DOC_TRANSFER == ENABLE)
UBYTE	CMN_CheckWarpRange(struct SYS_SubDialData_t *, UDWORD);
/*void	CMN_SetDialData(struct	SYS_DialData_t *, UBYTE	*, UBYTE *, UDWORD);*/	/* 1998/10/06 By M.Kuwahara */
void	CMN_SetDialData(struct	SYS_DialData_t *, UBYTE	*, UBYTE *, UBYTE *, UDWORD);
UBYTE	CMN_CheckWarpPrint(UBYTE);
#endif

#endif
