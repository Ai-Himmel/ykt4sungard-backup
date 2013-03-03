/******************************************************
 * ÇQÇWÅDÇWä÷åWÇÃä÷êîÉvÉçÉgÉ^ÉCÉvêÈåæ
 * By O.Kimot 1996/11/15
 ******************************************************/

/*
** mlt_main.C
*/
void   MAN_InitilizeOptionBoard(void);
void   MAN_ConfirmOptionBoard(void);
UBYTE   CHK_UnusedOptionLine(void);
UBYTE   CHK_SelectedLineEnable(UBYTE  board_number);
UWORD   CHK_OptionLineExist(UBYTE  board_number);
UWORD   CHK_OptionLine288(UBYTE  board_number);
UWORD   CHK_OptionPreLineBusy(UBYTE  board_number);
UWORD   CHK_OptionLineBusy(UBYTE  board_number);
UWORD   CHK_OptionLineError(UBYTE  board_number);
UWORD   CHK_OptionLineValid(UBYTE  board_number);
UWORD   CHK_OptionTelephoneUse( UBYTE board_number );
void   SYS_SetOptionPreLineBusy(UBYTE  board_number);
void   SYS_SetOptionLineBusy(UBYTE  board_number);
void   SYS_OptionLineStop(UBYTE  board_number);
void   SYS_ClearOptionLineBusy(UBYTE  board_number);
void   SYS_ClearOptionLineStop(UBYTE  board_number);
UBYTE   OPT_CheckPstnAccess(void);
UBYTE   OPT_GetQueueAndCommand(void);
UBYTE   OPT_GetAttribute(void);
UBYTE   OPT_GetDialNumber(void);
UBYTE   OPT_CheckExclusiveTxRx(void);
void   OPT_CheckLineType(void);
UBYTE   OPT_CheckV34ModemExist(void);
UBYTE   OPT_JudgeSelectLine(void);
UBYTE  OPT_DecideLineNumber(UBYTE ,UBYTE ,UBYTE ,UBYTE *,UBYTE *);

UBYTE MAN_JudgeSelectLine(void);
UWORD GetNextExecNoScannerTx(void);
UWORD GetNextExecNoPollingRx(UWORD point);
UWORD GetNextExecQueueNoCommandBatch(UWORD, UWORD);
UWORD GetNextExecNoContPolling(UWORD point);
UBYTE MAN_CheckSingleCodecScanTx(void);


/*
** mlt_sub.c
*/
UBYTE   OPT_CHK_UNI_LineTxRx(UBYTE  number);
UBYTE   OPT_CHK_Pbx(UBYTE  number);
UBYTE   OPT_GetMultiLinrNumber(UBYTE stack_number);
UBYTE   OPT_CHK_SelecetedLineEnable(UBYTE);
UBYTE   OPT_CHK_ScannerTxExecute(void);
UBYTE   OPT_CHK_FaxComExecute(void);
UWORD   OPT_CHK_FaxComSecureRxExecute(void);
UBYTE   OPT_CountModems(void);
UBYTE	OPT_CheckMultiLine(void);
UBYTE   OPT_CHK_ScannerTTI_TxAvailable(void);
UBYTE   OPT_CHK_CalendarTypeChange(UBYTE line_number);
UBYTE   OPT_CheckScannerCommandFromQue(UBYTE que_num);
UBYTE 	OPT_CheckRlyTxRptCommandFromQue(UBYTE que_num); /* Added by H.Kubo 1998/03/12 for relayed Tx report */
/*
** mlt_poll.c
*/
UBYTE   CMN_GetPollingDocRight(UWORD  LineNumber);
void   CMN_ReleasePollingDocRight(UWORD  LineNumber);
void   CMN_ErasePollingDoc(UWORD  LineNumber);
#if 0
// void   CMN_EraseFcodePollingDoc(UWORD LineNumber,UBYTE BoxNumber);
#endif
void   CMN_SetErrorComPollingDoc(UWORD  LineNumber);
UWORD  CMN_CheckPollingDocRights(UWORD line_number);
