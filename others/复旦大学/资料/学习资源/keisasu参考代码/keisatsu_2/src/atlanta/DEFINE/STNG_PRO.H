/************************************************************************
 * 機器設定に関するプロトタイプ宣言										*
 * SYB_SettingStatus[]													*
 * cmn_stng.c															*
 ************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif

UBYTE	CHK_DialType(void);
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
UBYTE	CHK_DialTypeExt(void);
#endif
UBYTE	CHK_ScanningWidth(void);
UBYTE	CHK_PrimaryMode(void);
UBYTE	CHK_PrimaryDensity(void);
UBYTE	CHK_Halftone64ON(void);
UBYTE	CHK_Halftone2ON(void);			/* 写真1/2の獲得 */
UBYTE	CHK_MultiPassLibbonON(void);
UBYTE	CHK_HeatTransferON(void);
UBYTE	CHK_NonSortCopy(void);	/*1996/04/18 Eguchi */
UBYTE	CHK_JournalAutoPrintON(void);	/* 1995/12/12 Eguchi */
UBYTE	CHK_BlockJunkFaxMode(void);	/* 1997/05/12  By T.Yamaguchi */
UBYTE	CHK_Connecting2TelON(void);
UBYTE	CHK_AnsMachinePhone1(void);
UBYTE	CHK_HoldMelodyON(void);
#if (PRO_BRANCH_RX == ENABLE)
UBYTE	CHK_BranchON(void);				/* '95.07/20 K.Watanabe */
#endif
UBYTE	CHK_DialinModeON(void);
#if (PRO_NUMBER_DISPLAY == ENABLE)
UBYTE	CHK_NumberDisplayON(void);		/* 1998/06/16 By M.Kuwahara */
UBYTE	CHK_DialinON(void);				/* 1998/06/16 By M.Kuwahara */
UBYTE	CHK_ModemDialinON(void);		/* 1998/10/14 H.Yoshikawa */
UBYTE	CHK_NumberDisplayByExtPhoneON(void); /* by H.Kubo 1998/10/22 */
#endif
#if (0)	/* TEL待機を追加のためこのﾋﾞｯﾄを削除します（待機ﾓｰﾄﾞに吸収されているので問題はなし）by K.Watanabe 1997/03/22 */
**UBYTE 	CHK_PrimaryFax(void);
#endif
UBYTE	CHK_AutoRxMode(void);
UBYTE	CHK_ClosedNetworkON(void);
UBYTE	CHK_SecurityTxON(void);
UBYTE	CHK_BlockJunkFaxON(void);
UBYTE	CHK_MessageTxON(void);
UBYTE	CHK_PageCompoundON(void);
UBYTE	CHK_RxFixedReduction(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE	CHK_RS232C_Speed(void);
#endif
UBYTE	CHK_RS232C_DataLength8(void);
UBYTE	CHK_RS232C_Parity(void);
UBYTE	CHK_RS232C_StopLength2(void);
UBYTE	CHK_StampON(void);
UBYTE	CHK_MemoryTxON(void);
UBYTE	CHK_DepartmentON(void);
UBYTE	CHK_ConfirmationReportON(void);
UBYTE	CHK_RCR_ON(void);
UBYTE	CHK_ECM_ON(void);
UBYTE	CHK_CopyProtectON(void);
UBYTE	CHK_RemoteDiagON(void);
UBYTE	CHK_RxMargin(void);
UBYTE	CHK_RedialCount(void);
UBYTE	CHK_RedialInterval(void);
UBYTE	CHK_PauseTime(void);
UBYTE	CHK_RingNumber(void);
UBYTE	CHK_RingCount(void);
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/12 */
UBYTE	CHK_ExtRingCount(void);
#endif /* defined (KEISATSU) */
UBYTE	CHK_SecureMailHoldTime(void);
UBYTE	CHK_PrinterTime(void);
UBYTE	CHK_FreeReduction(void);
UBYTE	CHK_RemoteFaxON(void);
UBYTE	CHK_RemoteFaxDEL(void);
UBYTE	CHK_RemoteFaxPRN(void);
UBYTE	CHK_TAD_PocketBellON(void);
UBYTE	CHK_TAD_OGM_UserMessage(void);
UBYTE	CHK_RelayedRelayTxON(void);
UBYTE	CHK_CatchPhoneON(void);
UBYTE	CHK_RingMasterON(void);
UBYTE	CHK_RingMasterPattern(void);
UBYTE	CHK_CopyFixedReduction(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE	CHK_PrinterRxON(void);
#endif
/*UBYTE	CHK_AllModeToAnsMode(void);  Delete By Eguchi '94/06/20*/
UBYTE	CHK_CopyMargin(void);
UBYTE	CHK_TollSaverBellCount(void);
UBYTE	CHK_UpperManualCassete(void);
#if (PRO_PC_PRINT == ENABLE)	/* 1996/10/09 by K.Watanabe */
UBYTE	CHK_PCR_UpperManualCassete(void);
UBYTE	CHK_PCR_ManualCassetteSize(void);
#endif
UBYTE	CHK_LowerManualCassete(void);
#if defined(GBR)
UBYTE	CHK_GBR_RxAlarm(void);			/* '95.07/21 K.Watanabe */
#endif
#if defined(GBR) || defined(STOCKHM2) /* Added by SMuratec C.P 2004/07/08 for prefix */
 UBYTE	CHK_GBR_SecurityRx(void);		/* 95.01.26 M.HARADA */
#endif
UBYTE	CHK_NumberOfPrintingRxDocuments(void);	/* 1995/06/26 */
UBYTE	CHK_RotateMargin(void);
/* 1995/12/21 Eguchi */
UBYTE	CHK_DayLightSavingAuto(void);
UBYTE	CHK_SecurityReceiveON(void);
UBYTE	CHK_OperationProtect(void);
UBYTE	CHK_SectionCheckProtect(void);
UBYTE	CHK_PIN_AccessMode(void);
UBYTE	CHK_SilentOperation(void);
UBYTE	CHK_AudibleAlarmON(void);
UBYTE	CHK_RemoteRxON(void);	/* 1998/01/24  By T.Yamaguchi */
UBYTE	CHK_VoiceMessageON(void);	/* 1998/02/03  By T.Yamaguchi */
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
UBYTE	CHK_OnHookRX_ON(void);	/* 1998/03/13  Add By T.Fukumoto */
#endif
UBYTE	CHK_ReadyModeCopy(void);
UBYTE	CHK_AutoRxSwitch(void);
UBYTE	CHK_MultiPhoneType(UBYTE Board);
UBYTE	CHK_MultiLineType(UBYTE Board);
UBYTE	CHK_MultiTxRxType(UBYTE Board);
#if (PRO_LINENUMBER == TWICE_LINE)
UBYTE	CHK_Phone2ExtLineOn(void);	/*  by T.Soneoka 1997/11/11 */
#endif
#if defined (KEISATSU)
UBYTE	CHK_LineSetting(void);	/* Added by SMuratec 李 2005/06/24 */
UBYTE CHK_KEIDENRxPriority(void); /* Added by SMuratec 李 2005/06/28 */
#endif /* defined (KEISATSU) */
#if defined(FRA) || defined(TWN)
UBYTE CHK_HardDipProtection(void);	/* by M.H.  8 Dec  97 */
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)
UBYTE CHK_WarpFunctionON(void);	/* 1998/06/26 Add By M.Kuwahara */
#endif
#if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
UBYTE CHK_ND_WarpON(void);
#endif
#if defined(STOCKHM2)		/* 呼出ベル対応テスト by Y.Kano 2004/09/24 */
UBYTE	CHK_CallingBuzzerMode(void);
#endif	/* End of defined(STOCKHM2) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/24 */
void CMN_CheckKeidenSettings(UBYTE *Keisatsu);
void CMN_CheckKanyuSettings(UBYTE *Keisatsu);

void CMN_SetKeisatsuSettings(UBYTE Keisatsu);
UBYTE CMN_CheckHDSTOnSTD(void); /* Added by SMuratec 李 2005/06/27 */
UBYTE CMN_CheckHDSTOnEXT(void); /* Added by SMuratec 李 2005/06/27 */

BOOL CHK_SenyoOn(void);

#endif 		/* End of (defined (KEISATSU)) */

