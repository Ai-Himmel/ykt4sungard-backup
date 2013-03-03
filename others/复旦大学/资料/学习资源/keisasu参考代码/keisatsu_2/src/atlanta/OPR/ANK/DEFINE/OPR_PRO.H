/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_PRO.H
*	Author		: ìnï”àÍèÕ
*	Date		: 1996/10/17
*	RealTimeOS	: ÇqÇhÇrÇbÅiÇrÇgÇVÇOÇSÇRÅjÉÇÉjÉ^Å[
*	Description	: ÉIÉyÉåÅ[ÉVÉáÉìä÷êîêÈåæ
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#ifndef OPR_PRO_H
	#define OPR_PRO_H	1

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif

#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysspeed.h"
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/12 by K.Okada */
#include "\src\atlanta\define\message.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/03/12 by K.Okada */
/*************************************
** \src\atlanta\opr\ank\src\opr_msnd.c
*************************************/
void SendMailCommandOperation(UBYTE, UBYTE);
void MailCommandInputInitial(void);
void SetInputDialInfoFlag(void);
void InputNumberRedialSet(void);
UBYTE CheckDestKindAtCursorPosition(void);
UBYTE CheckDirectAdrAtCursorPos(void);
UBYTE CheckSpeedDialAtCursorPosition(void);
UBYTE CheckGroupDialAtCursorPosition(void);
UBYTE CheckProgramAtCursorPosition(void);
UBYTE CheckOnetouchAtCursorPosition(void);
UBYTE InputNumberMailMarkSet(UBYTE);
void SwitchDialMarkExceptDirect(void);
void SwitchDialMark(UBYTE, UBYTE);
void InputNumberDataShiftAndSet(UBYTE);
void InputDialMarkSet(UBYTE);
UBYTE CheckDestKindInInputBuffer(void);
UBYTE CheckCorrectAllCommand(void);
UBYTE CheckDirectMarkInvalidPosition(void);
UBYTE CheckSpecialCommandType(void);
void ReleaseMailCommandArea(void);
void MailCommandSet(void);
void SetTxMailAddress(UBYTE, UBYTE);
void SetBitAssign(UBYTE *, UBYTE);
UBYTE SetMixedTxDialNumber(void);
void SetMixedCommandOption(UBYTE);
void SetMixedCommandOptionItem(struct SYS_CommandData_t *, UBYTE);
UBYTE CheckMailComExecute(void);
UBYTE CheckCodeNumber(void);
UBYTE NumberInputTx(UBYTE);
void UpperDisplayNumberInput(void);
UBYTE CheckCodeNumberUnderMinFigure(void);
UBYTE CheckCodeNumberTx(void);
UBYTE CheckAllUserDataStore(UBYTE, UBYTE);
void MailCommandMessageToMain(void);
void MixedCommandMessageToMain(void);
UBYTE CheckPreMailCommandSet(void);
UBYTE CheckSetUserData(void);
UBYTE CheckPreMixedCommandSet(void);
void MixedCommandSet(void);
void FaxCommandSet(void);
UBYTE CheckMailTxEnable(void);
void DisplayMailCommandInput(void);
void DisplayMailCommandAddress(void);
UBYTE CheckHexCodeInput(void);
UBYTE DirectAddressInput(UBYTE, UBYTE);
UBYTE CheckAddressMark(UBYTE *, UWORD, UWORD);
UBYTE CheckNumberOfDirectAddress(void);
void DirectAddressInputModeSet(UBYTE);
void ResetInputMode(void);
void AllClearInputHexCodeBuffer(void);
void DirectAddressAlphabetInput(UBYTE);
void DirectAddressHexCodeSet(UBYTE);
UBYTE OnetouchAddressInput(UBYTE);
UBYTE CountNumberOfOnetouchAddress(void);
UBYTE MailGroupAddressInput(UBYTE);
UBYTE CountNumberOfPOnetouchAddress(UBYTE);
UBYTE MailAddressHistorySet(void);
UBYTE CheckNoDirectMailAddress(void);
void MailBroadCastSet(void);
UBYTE DeleteDirectAddressMark(void);
UBYTE DeleteOnlyDirectAddressMark(void);
/*
**UBYTE CheckMailOnetouchStoreStatus(UBYTE);
*/
/*
**UBYTE CheckProgramStoreStatus(UBYTE);
*/
/************************************
** \src\atlanta\opr\ank\src\opr_mnet.c
************************************/
void SetUserData(void);
void SetMachineState(void);
void SetToneDetect(void);
void PrintUserDataList(void);
void EraseUserData(void);
void OperationClearMessageToMain(MESSAGE_t);
void ClearUpdateUserDataFlag(void);
UBYTE SelectNewEntryOrNot(void);
UBYTE SelectMailBoxChangeOrNot(void);
void DisplayChangeMailBox(UBYTE);
UBYTE CheckAndGetUserDataArea(void);
UBYTE EnterUserCodeNumber(UBYTE, UBYTE);
void SubstituteUserData(UBYTE *, UBYTE *, UWORD);
UBYTE EnterName(UBYTE *, UWORD, UBYTE *, UBYTE, UBYTE);
void GetUserData(UBYTE *, UBYTE *);
UBYTE CheckUserDataStore(UBYTE *);
UBYTE EnterAP_TelNumber(UBYTE, UBYTE);
UBYTE * BCD_StringCopy(UBYTE *, UBYTE *);
UBYTE EnterAP_PIN_Number(UBYTE, UBYTE);
UBYTE EnterLoginID(UBYTE *, UWORD, UBYTE *, UBYTE, UBYTE);
UBYTE EnterLoginPassword(UBYTE *, UWORD, UBYTE *, UBYTE, UBYTE);
UBYTE EnterMailAddress(UBYTE, UBYTE);
UBYTE EnterNameOrIPAddress(UBYTE *, UWORD, UBYTE *, UBYTE, UBYTE);
UBYTE CheckCorrectIP_AddressInput(void);
UBYTE EnterDNS_SpaceIPAddress(UBYTE, UBYTE);
UBYTE EnterDNS_ServerIPAddress(UBYTE, UBYTE);
UBYTE CheckIP_AddressInput(UBYTE *, UBYTE);
UBYTE EnterIPAddress(UBYTE *, UBYTE *, UBYTE, UBYTE, UBYTE);
UBYTE SpaceIP_AddressInput(void);
UBYTE CheckOneBlockAllSpace(void);
void InsertIP_AddressNumberSet(UBYTE);
UBYTE CheckOneBlockAllNumber(UBYTE);
void SpaceIP_AddressClear(void);
UBYTE SearchIP_AddressMoveCursor(void);
void ChangeIP_AddressToSpace(void);
UBYTE CheckCharacterInputAllSpace(void);
void CursorRightOneBlockRotation(void);
void CursorLeftOneBlockRotation(void);
UBYTE IP_AddressInput(void);
void DisplayIP_AddressInput(void);
UBYTE CheckSpaceIP_AddrBlockRange(UBYTE);
UBYTE CheckSpaceBetweenIP_Address(UBYTE *, UBYTE);
UBYTE CheckInsertIP_AddrBlockRange(UBYTE);
UBYTE CheckSpaceLeft(UBYTE *, UBYTE);
void ShiftOneStepLeft(UBYTE *, UBYTE);
void ShiftOneStepRight(UBYTE *, UBYTE, UBYTE);
void ShiftClearOneStepLeft(UBYTE *, UBYTE, UBYTE);
UBYTE CheckIP_AddressOneBlockRange(UBYTE);
void GetSpaceIP_Address(UBYTE *);
void GetIP_Address(UBYTE *);
UBYTE CheckIP_AddressStore(UBYTE *);
void SetSpaceIP_Address(UBYTE *);
void ShiftSpaceToLeft(UBYTE *,UBYTE);
void ShiftSpaceToRight(UBYTE *,UBYTE);
void ChangeSpaceToZero(UBYTE *,UBYTE);
void ChangeZeroToSpace(UBYTE *,UBYTE);
void SetIP_Address(UBYTE *);
UBYTE SelectPPP_Authentication(UBYTE, UBYTE);
UBYTE SetDeleteInvalidMailSetting(void);
UBYTE SetAutoReceiveSetting(void);
UBYTE SetAutoDownload(void);
UBYTE SetAutoPrintSetting(void);
UBYTE SetRxMailHoldTime(UBYTE);
UBYTE EnterToggleSetting(UBYTE *, UBYTE *, UBYTE, UBYTE *, UBYTE, UBYTE);
UBYTE SetTxWithRxSetting(UBYTE);
UBYTE CheckMailRxEnable(UBYTE);
UBYTE SetAutoReceiveTime(UBYTE);
UWORD MailAutoRcvStartTimeInput(UBYTE);
UWORD MailTimeInput(void);
UWORD MailAutoRcvEndTimeInput(UBYTE, UWORD);
UWORD MailAutoRcvIntervalTimeInput(UBYTE, UWORD);
UBYTE SetDetectTone(UBYTE *, UBYTE);
void MailListPrintOperation(MESSAGE_t);

/************************************
** \src\atlanta\opr\ank\src\opr_rcv.c
************************************/
void ManualReceiveMail(void);
void PrintReceiveMail(void);
UBYTE CheckAllUserStoredDocument(void);
void CreateManualRcvMailCommand(UBYTE, UBYTE);
void StartPrintRcvMailOperation(UBYTE);

/************************************
** \src\atlanta\opr\ank\src\opr_adr.c
************************************/
void SetMailAddress(void);
void EraseMailAddress(void);
void PrintMailAddressList(void);
void SetMailGroup(void);
void EraseMailGroup(void);
void PrintMailGroupList(void);
void EnterMailAddressInitial(void);
UBYTE MailAddressInput(void);
void DisplayAddressInputUpper(UBYTE *, UBYTE *);
void ClearMailAddressRecord(UBYTE);
void ClearOnetouchFromMailGroup(UBYTE);
UBYTE MailGroupInput(void);
void MailGroupSet(UBYTE);
void MailGroupClear(UBYTE);
void DisplayMailGroupInput(void);

/************************************
** \src\atlanta\opr\ank\src\opr_rev.c
************************************/
void PrintMailCommandList(void);
void PrintStoredMail(void);
UBYTE CheckAllMailCommand(void);
UBYTE CheckAllMailTxCommand(void);
UBYTE CheckUserMailCommand(UBYTE);
UBYTE CheckUserMailTxCommand(UBYTE user_no);
UBYTE CheckMailCommandStatus(UBYTE);
UBYTE EraseMailCommand(void);
UBYTE CheckUserMailCommandStatus(UBYTE, UBYTE);
UBYTE CheckUserTxMailCommandStatus(UBYTE,UBYTE);
void GetNameOrPOP_LoginID(UBYTE *, UBYTE);
void GetAddressInputBuffer(UBYTE);
void GetFaxNumberInputBuffer(UBYTE, struct SYS_CommandData_t *, UBYTE *);
UBYTE CheckOnetouchMailCommand(UBYTE);
UBYTE CheckDirectMailCommand(UBYTE);

/************************************
** \src\atlanta\opr\ank\src\opr_jrn.c
************************************/
void PrintMailJournal(void);

/*************************************
** \src\atlanta\opr\ank\src\opr_serv.c
*************************************/
void InitEmailEngineBoard(void);
void SetIP_EchoRequest(void);
void SF_DataModemTonalTest(void);
void OperationMessageToMainFunction(MESSAGE_t);
void DisplayDataModemTonalTest(UBYTE, UBYTE);
UBYTE SF_SelectVFC_OrV34Parameter(UBYTE);
UBYTE SF_SelectVFC_R_Parameter(void);
UBYTE SF_SelectV34_R_Parameter(void);
UBYTE SF_SelectVFC_OrV34_S_Parameter(UBYTE);
UBYTE SF_SelectVFC_C_Parameter(void);
UBYTE CarrierBiasInput(UBYTE *);
void DisplayCarrierBiasInput(UBYTE *);
UBYTE CheckCarrierBiasValue(UBYTE);
UBYTE SF_SelectVFC_OrV34_A_Parameter(UBYTE);
UBYTE SF_SelectVFC_P_Parameter(void);
UBYTE CheckCorrectVFC_BandEdge(void);
UBYTE SF_SelectV34_P_Parameter(void);
void ClearSYS_INF_PTT_Parameter(void);
UBYTE SF_SelectGuardToneLevel(UBYTE);
UBYTE SF_SelectMode(UBYTE);
UBYTE UpperBandEdgeInput(void);
void DisplayUpperBandEdgeInput(void);

#endif	/* PRO_DIALUP_INTERNET_FAX 1998/03/12 by K.Okada*/

/*---------------------------------------------*
	\src\atlanta\opr\ank\src\opr_btx.c
 *---------------------------------------------*/
void	SetBatchBox(void);
void	PrintBatchBoxList(void);
void	EraseBatchBox(void);
void	PrintBatchDocumentList(void);
void	PrintBatchTxDocument(void);
void	EraseBatchTxDocument(void);
UBYTE	SelectBatchBox(void);
void	DisplayBatchBoxSelect(void);
UBYTE	EnterBatchTxData(void);
UBYTE	EnterBatchTxDialNumber(void);
UBYTE	CheckValidKeyForBatchDial(UBYTE, UBYTE);
UBYTE	BatchDialEnter(UBYTE);
void	DisplayBatchTxDialNumberInput(void);
UBYTE	EnterBatchTxTime(void);
UBYTE	EnterBatchTxName(void);
void	SetBatchDialAndTime(void);
void	ClearBatchBoxData(void);
void	BatchBoxNumberForword(void);
void	BatchBoxNumberBack(void);
void	GetBatchTxDialNumber(UBYTE, UBYTE *, UWORD);
UBYTE	CheckBatchTxFileStatus(UBYTE);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_ciph.c
 *-------------------------------------------*/
#if (PRO_CIPHER == ENABLE)
void	SetCipherKeyBook(void);
void	PrintCipherKeyBookList(void);
void	PrintSettingCipherKeyBook(void);
void	EraseCipherKeyBook(void);
void	EraseCipherRxDocument(void);
void	SetCipherDefaultKey(void);
void	SetServiceLabelPosition(void);
void	SetCipherPassCode(void);
void	PrintDecipherDocument(void);
UBYTE	CheckCipherPassCode(void);
UBYTE	SelectCipherKeyBookNumber(void);
UBYTE	CheckCipherKeyBookPassCode(void);
UBYTE	SetCipherKeyBookName(void);
UBYTE	SetCipherKey(void);
UBYTE	SetCipherKeyClue(void);
UBYTE	SetCipherKeyBookPassCode(void);
void	SetCipherKeyBookComplete(void);
void	ClearOPR_CipherData(void);
void	DisplaySetCipherKeyBook(UBYTE);
void	DisplaySelectCipherKeyBook(void);
void	KeyBookNumberForwordOperation(void);
void	KeyBookNumberBackOperation(void);
void	GetKeyBookData(void);
UBYTE	CheckSetKeyBookData(void);
void	DisplayKeyBookNumberAndTitle(UBYTE *);
UBYTE	InputRxCipherDocNumber(UBYTE *);
void	SetDecipherData(void);
UBYTE	SelectCipherKeySet(UBYTE);
UBYTE	SetDecipherParameter(void);
UBYTE	CheckCipherExecEnable(UBYTE);
UBYTE	CheckCipherEnableMode(void);
UBYTE	ChangeCentiToInch(UBYTE);
UBYTE	ChangeInchToCenti(UBYTE);
UBYTE	CheckCipherExecuting(void);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_cl1.c
 *-------------------------------------------*/
void	SetRS232CPCFaxScsn(void);
void	SetRS232CParameter(void);
void	SetRS232CPCFaxInitial(void);

/*--------------------------------------------*
	\src\atlanta\opr\ank\src\opr_com.c
 *--------------------------------------------*/
void	CommandOperation(UBYTE,UBYTE);
void	CopyModeCommandOperation(UBYTE);
void	CommandInputInitial(void);
void	SetPinCheckStatus(void);
void	ComOptionInputInitial(void);
void	DisplayCommandOperation(void);
void	DisplayCommandNumber(void);
UBYTE	CheckNoCommandData(void);
UBYTE	CheckInputCommandDialNumber(void);
UBYTE	CheckInputSpecialCommand(void);
UBYTE	CheckInputBroadcast(void);
UBYTE	CheckInputOnetouchEnable(UBYTE);
UBYTE	CheckInputP_OnetouchEnable(UBYTE);
UBYTE	CheckPreDataSpeedMark(void);
UBYTE	CheckPreDataOnetouch(void);
UBYTE	CheckInputNumberCode(UBYTE);
UBYTE	CheckSpeedGroupAfterEnableKey(UBYTE);
UBYTE	CheckProgramAfterInput(UBYTE);
#if (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE	CheckRegistrationData(UBYTE);
UBYTE	CheckInputDialData(UBYTE);
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)
UBYTE	CheckInputDirectDial(UBYTE);
#endif
void	BroadcastCheck(void);
void	InputNumberTenKeySet(UBYTE);
void	InputNumberOnetouchSet(UBYTE);
void	InputNumberGroupSpeedMarkSet(UBYTE);
void	InputNumberProgramSet(UBYTE);
void	BroadcastMarkSet(void);
void	InputNumberDialMarkSet(UBYTE);
void	InputNumberCursorRight(void);
void	InputNumberCursorLeft(void);
void	InputNumberDataClear(void);
void	InputNumberDialCharacterSet(void);
void	InputNumberDataShift(UBYTE);
void	InputNumberDataSet(UBYTE);
void	InsertInputData(UBYTE *, UBYTE);
void	InputNumberClearBackSpace(void);
void	InputNumberClearDelete(void);
void	SetTelBookDataToInputBuffer(void);
UBYTE	ProgramOnetouchExecute(UBYTE);
UBYTE	FaxComTxReserveOperation(void);
UBYTE	DepartmentCodeOperation(void);
UBYTE	CheckInputDepartCode(void);
UBYTE	PinAccessOperation(void);
void	CalculateProgramExecTime(void);
UBYTE	CheckAndGetCommandArea(void);
void	ReleaseCommandArea(void);
void	ClearCommandFileData(struct SYS_CommandData_t *);
void	ClearDialNumber(struct SYS_DialData_t *);
void	ClearCommandPinNumber(struct SYS_CommandData_t *);
void	ClearDialPinNumber(struct SYS_DialData_t *);
UBYTE	CommandStartOperation(void);
void	SetCommandPinAccessMode(struct SYS_CommandData_t *);
void	SetCommandDialNumber(void);
void	SetDialNumber(struct SYS_DialData_t *, UBYTE);
void	SetCommandTime(void);
void	SetCommandOption(void);
void	SetCommandOptionItem(struct SYS_CommandData_t *);
void	SetCommandOptionNumber(struct SYS_CommandData_t *, UBYTE, UBYTE);
void	SetCommandConfirmReport(struct SYS_CommandData_t *);
void	SetCommandTitleMessage(void);
void	SetCommandPage(void);
#if (PRO_DEPARTMENT == ENABLE)
void	SetCommandDepartCode(void);
#endif

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/ /* By H.Fujimura 1999/01/07 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* By H.Fujimura 1999/01/07 */ /* Add by Y.Kano 2003/07/11 */

void	SetCommandAbility(void);
#endif
void	SetCommandPinNumber(void);
UBYTE	CheckMemoryTxEnable(void);
UBYTE	CheckScannerTxEnable(void);
UBYTE	CheckPollingCommandInput(void);
void	SetProgramDialToInputNumber(UBYTE);
UBYTE	DialCharacterCheck(UBYTE *, UWORD, UWORD);
#if (PRO_NEW_DIALMARK_OPR == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	DialCharacterCheck2(UBYTE *, UWORD, UWORD);
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
UBYTE	SetContPollingCommandTime(void);
void	ClearContPollingData(struct SYS_ContinuousPollingData_t *);
void	ClearCommandPinNumberCP(struct SYS_ContinuousPollingData_t *);
#endif
#if (PRO_FBS == ENABLE)
UBYTE	BookDocumentSizeSet(UBYTE, UBYTE);
void	BookNextDocumentSet(UBYTE, UBYTE);
void	DisplayBookDocumentData(UBYTE);
#endif
#if (PRO_BATCH_TX == ENABLE)
UBYTE	ProgramOnetouchBatch(UBYTE);
#endif
#if (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE	CheckRegistrationSpeedDial(UWORD, UWORD);
UBYTE	CheckRegistrationGroupDial(UWORD, UWORD);
#endif
#if (PRO_NEW_DIAL_OPR2 == ENABLE)
UBYTE	CheckDirectDialCount(void);				/* by K.Watanabe 1999/01/28 */
UBYTE	CheckDirectDialLength(UBYTE, UBYTE);
void	ChangeAsteriskKeyCode(UBYTE);
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE)
void	DisplayDialName(UBYTE, UWORD);
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
UBYTE	LifeMonitorPasscodeOperation(void);
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/16 Y.Matsukuma */
void	MinoltaOnetouchPrint(UBYTE);
UBYTE	MinoltaStandardPG(UBYTE, UBYTE);
#endif
#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
void SetSgpDialNumber(void);
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE) || (PRO_FCODE_RELAY == ENABLE) /* By H.Fujimura 1999/01/07 */
void	ClearDialNumber2(UBYTE *, UBYTE *, UBYTE *, UDWORD *);
void	SetDialNumber2(UBYTE *, UBYTE *, UBYTE *, UDWORD *);
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/09/30 By M.Kuwahara */
void SetRxDocTransferPageCount(void);
#endif

#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/07/25 */
void	SetCommandKeisatsu(void);
#endif		/* End of (defined (KEISATSU)) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_copy.c
 *-------------------------------------------*/
#if (PRO_COPY_FAX_MODE == DISABLE)
void	CopyKeyOperation(void);
UBYTE	InputMultiCopyReserveNumber(void);
void	DisplayCopyNumberInput(void);
void	MultiCopyOperation(void);
UBYTE	GetMultiCopyFile(void);
void	SetMultiCopyFile(void);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_cpym.c
 *-------------------------------------------*/
#if (PRO_COPY_FAX_MODE == ENABLE)
UBYTE	CopyOperation(UBYTE, UBYTE, UBYTE);
void	CopyFaxKeyOperation(void);
void	CopyMagnifiDecreaseOperation(void);
void	CopyMagnifiIncreaseOperation(void);
void	CopyModeSetKeyOperation(void);
void	CopyNumberClearOperation(void);
void	MagnificationKeyOperation(UBYTE);
void	SortKeyOperation(UBYTE);
void	PaperSelectKeyOperation(void);
void	CopyResetKeyOperation(void);
void	CopyStartOperation(void);
void	CopyNumberKeyOperation(UBYTE);
void	ChangeNumberKeyInputMode(void);
UBYTE	CheckCopyMagnifiLimit(UWORD);
void	ResetCopyMagnifi(void);
void	ClearCopyParameter(void);
UBYTE	ClearCopyCassette(void);
UBYTE	ClearCopyMagnifi(void);
void	ClearCopyNumber(void);
UBYTE	CheckCopyToFaxChangeEnable(void);
UBYTE	CheckFaxToCopyChangeEnable(void);
void	CopyMagnificationOperation(UBYTE);
void	CopyReductionOperation(UBYTE);
void	GetNextManualPaperSize(void);
UBYTE	CheckCopyFileStatus(void);
void	SetCopyParameter(void);
UBYTE	GetDocumentSize(struct OPR_MAGNIFI_PAPER_TABLE_t *, UBYTE);
UBYTE	GetBookCopyDocumentSize(void);
void	ModifyCopyMagnifi(UBYTE);
UBYTE	GetADF_CopyMaxMagnifi(void);
 #if (0)	/* by K.Watanabe 1997/12/25 */
/*UBYTE	CheckCopyEnablePaperCombi(UBYTE, UBYTE);*/
 #endif
UBYTE	CheckADF_CopyMagnifi(void);
UBYTE	CheckPossibleCopyReserve(void);
void	StopParamDispTask(void);
UBYTE	ConfirmCopyParam(void);
UBYTE	CheckChangeCassette(void);
UBYTE	CheckFixedMagnification(struct OPR_FIXED_MAGNIFI_TABLE_t *);
 #if (PRO_ADF_AUTO_CASSETTE == ENABLE) /* By S.Fukui Jan.23,1998 */
void ClearAutoCassetteAndMagnifi(void);
 #endif
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_dial.c
 *-------------------------------------------*/
UBYTE	OnetouchSpeedInput(void);
UBYTE	EnterOnetouchSpeedDialNumber(struct SYS_SpeedDialData_t *);
UBYTE	EnterOnetouchSpeedSubDial(struct SYS_SpeedDialData_t *);
#if defined (KEISATSU)		/* åxé@FAX Modify by SMuratec K.W.Q 2005/06/21 */
UBYTE	DialNumberInput(UBYTE *, UBYTE *);
#else
UBYTE	DialNumberInput(UBYTE *);
#endif
UBYTE	EnterOnetouchSpeedRemoteName(struct SYS_SpeedDialData_t *);
UBYTE	DialNameInput(UBYTE *init_name);
UBYTE	EnterOnetouchSpeedGroup(struct SYS_SpeedDialData_t *);
UBYTE	GroupNumberInput(UBYTE, UDWORD);
UBYTE	CheckGroupNumberInput(UBYTE);
UBYTE	EnterOnetouchSpeedAttribute(struct SYS_SpeedDialData_t *);
UBYTE	EnterOnetouchSpeedPIN(struct SYS_SpeedDialData_t *);
UBYTE	PinNumberInput(UBYTE *, UBYTE);
void	ClearOnetouchSpeedRecord(struct SYS_SpeedDialData_t *);
void	DisplayEnterOnetouchSpeed(UBYTE);
#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/06/21 */
UBYTE	SetKeisatsuBuf(UBYTE  *, const UBYTE);
UBYTE	SetToCheckKeisatsuBuffer(UBYTE);
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_ANK_TO_KANJI == DISABLE)	/* by K.Watanabe 1999/06/16 */
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_disp.c
 *-------------------------------------------*/
void	UpdateLCD(void);
void	DisplayMachineError(void);
void	DisplayMachineErrorHigh(void);
UBYTE	DisplayMachineErrorLow(UBYTE);

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

void	DisplayMachineError2(void);
UBYTE	DisplayMachineErrorLow2(UBYTE);
#endif
void	DisplayFaxCom(void);
void	DisplayTransmit(void);
void	DisplayReceive(void);
UBYTE	*GetCommunicationResolution(UBYTE);
UWORD	GetCommunicationSpeed(UBYTE baud_rate);
UBYTE	DisplayMultiLineFaxCom(void);
void	DisplayWaitAMinutes(void);
void	DisplayCalender(void);
void	DisplayFeedOut(void);
void	DisplayIdle(void);
void	DisplayRxMode(void);
void	DisplayCopy(UBYTE);
void	DisplayJamRecover(void);
void	DisplayPrinterWarmUp(void);
void	DisplayImagePrint(void);
void	DisplayListPrint(void);
UBYTE	DisplayDocumentStore(void);
void	DisplayDocumentStoreHigh(void);
void	DisplayStoreMemTxDocument(void);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/03 by K.Okada */
void	DisplayStoreMailMemTxDocument(void);
#endif
void	DisplayStoreBatcTxDocument(void);
/* void	DisplayDocumentSet(UBYTE doc_size); 1997/05/19 */
void	DisplayDocumentSet(void);
void	SetDocumentScanSizeWording(UBYTE *, UBYTE);
void	SetRegularDocumentSizeWording(UBYTE *);
void	DisplayComplete(void);
void	DisplayDocumentOnFeeder(void);
#if (PRO_CLASS1 == ENABLE)
void	DisplayClass1(void);
#endif
#if (PRO_PC_PRINT == ENABLE)
void	DisplayPcPrint(void);
#endif
#if (PRO_CIPHER == ENABLE)	/* by K.Watanabe 1997/12/04 */
void	DisplayCipherProcess(UBYTE *);
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
void	DisplayCopyMode(void);
void	DisplayCopyModeHigh(void);
void	DisplayCopyModeLow(void);
void	SetCopyModePaperDensity(void);
void	SetCassettePaperSize(UBYTE *);
UBYTE	*SetCassetteCharacter(UBYTE *, UBYTE);
void	SetCassetteWording(UBYTE *, UBYTE);
void	SetCopyModeMagnification(UBYTE *);
void	SetDocumentSize(void);
void	DisplayReplacePaperSize(UBYTE);
#endif
void	SetPaperSizeWording(UBYTE *, UBYTE, UBYTE);
#if (PRO_MULTI_LINE == ENABLE)
void	OverWriteDisplayData(UBYTE);
UBYTE	BaudRateCompatible(UBYTE);
void	UpdateCheckerDisplay(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
void	IdleCountDisplay(UDWORD);
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/14 Y.Matsukuma */
void	MinoltaPrinterErrorDisplay(void);
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/07 */
void	DisplayND_CallerID(void);
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/08/01 */
void	SetDocumentSetWording(UBYTE *);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif	/* (PRO_ANK_TO_KANJI == DISABLE) */
#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/06/24 */
void	DisplayKeisatsuSettings(UBYTE *);
void	DisplayFaxComKeisatsu(UBYTE *);
void	DisplayTelBell(UBYTE);
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_DEPARTMENT == ENABLE)
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_dpt.c
 *-------------------------------------------*/
void	SetDepartmentProtect(void);
void	SetDepartmentCode(void);
void	SetDepartmentOnOff(void);
#if (PRO_DEPART_NEW_LIST == ENABLE)
void	PrintDepartTimeList(void);  /* by thonda 1997/12/03 */
void	EraseDepartTimeList(void);  /* by thonda 1997/12/03 */
#endif
/*void	DepartmentCodeDisplay(UBYTE);*/
UBYTE	CheckDepartmentCode(void);

UBYTE	SetDeptCodeSelect(UBYTE);
UBYTE	SettingDeptCode(void);
void 	DepartmentSelectDisplay(void);
/*void	Del_DepartmentDuplication(void);*/
UBYTE	Del_DepartmentDuplication(UWORD, UBYTE);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_fcod.c
 *-------------------------------------------*/
void	SetFcodeBox(void);
void	PrintFcodeBoxList(void);
void	PrintFcodeBoxDocList(void);
void	PrintFcodeBoxDocument(void);
void	EraseFcodeBox(void);
void	EraseFcodeBoxDocument(void);
void	StoreFcodeBoxDocument(void);
UBYTE	SelectFcodeBoxNumber(void);
UBYTE	CheckFcodePassCode(void);
UBYTE	SetFcodeBoxName(void);
UBYTE	SetFcodeSubAddress(void);
UBYTE	SetFcodePassword(void);
UBYTE	SelectFcodeBoxKind(void);
UBYTE	SetFcodeOption(void);
UBYTE	SetFcodeHoldTime(void);
UBYTE	SetFcodePassCode(void);
void	SetFcodeComplete(void);
void	ClearFcodeControlData(void);
void	DisplaySetFcodeBox(UBYTE);
void	DisplaySelectFcodeBox(void);
void	FcodeBoxNumberForwordOperation(void);
void	FcodeBoxNumberBackOperation(void);
void	GetSubAddressBoxData(void);
UBYTE	InputFcodePassword(void);
UBYTE	InputFcodeNumber(UBYTE);
UBYTE	InputFcodeStoreDocFile(UBYTE, UBYTE *, UWORD *);
void	DisplayFcodeBoxNumberAndTitle(UBYTE *);
UBYTE	GetEmptyFcodeNumberData(UBYTE);
#if (PRO_FCODE_RELAY == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	SetFcodeRelayBox(void);
UBYTE	FcodeRelayNumberInput(UBYTE *Onetouch, UBYTE *Speed, UDWORD *Group);
#endif
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	SetStoreFcodeBoxDocument(UBYTE prg_no);
void	EnterStoreFcodeBoxDocument(UBYTE prg_no);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_flsh.c
 *-------------------------------------------*/
void	OPR_DisplayFlashTask(void);
void	FunctionFlashControl(void);
UBYTE	WaitFlashTime(void);
void	FlashDisplayStringHigh(UBYTE *);
void	FlashDisplayStringLow(UBYTE *);
void	SetFlashBuffer(UBYTE *, UBYTE *, UBYTE *);
void	StopFunctionFlash(void);
void	StopFunctionFlashHigh(void);
void	StopFunctionFlashLow(void);
UBYTE	CheckFunctionFlash(void);
void	StartChildDisplay(void);
void	StopChildDisplay(void);
UBYTE	CheckChildDisplay(void);
UBYTE	CheckChildErrorDisplayReq(void);
void	ChildDisplayStringLow(CONST UBYTE *);
void	ChildDisplaySetCompleted(CONST UBYTE *);

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

void	ParamChildDisplayStringLow(UBYTE *);
#endif

/*------------------------------------------*
	\src\atlanta\opr\ank\src\opr_fnc.c
 *------------------------------------------*/
void	FunctionOperation(void);
void	OPR_SaveTopBottomOPRPointer(struct FUNCTION_TABLE_t *);
void	DisplayFunctionOperation(void);
UBYTE	CheckSelectFunctionEnable(struct FUNCTION_TABLE_t *);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
UBYTE	CheckSelectMailFunction(struct FUNCTION_TABLE_t *);
#endif
void	ChangeWording(void);
void	ServiceFunctionOperation(void);
void	FunctionDummy(void);
#if (PRO_CPU == SH7043)
UWORD	DRAM_AddressChange(UWORD);
 #if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui Jun. 19,1998  */
UDWORD	DMA_AddressSet(UBYTE *);
 #endif
#endif

#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/06/10 */
/*	åxìdÉTÅ[ÉrÉXê›íË	*/
void	KeisatsuService(void);
#endif		/* End of (defined (KEISATSU)) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_fncs.c
 *-------------------------------------------*/
void	PrintCommandList(void);
void	PrintStoredDocument(void);
#if (0)	/* Ç±ÇÃä÷êîÇÕïKóvÇ»Ç¢ÇÃÇ≈ÅAçÌèúÇµÇ‹Ç∑ by K.Watanabe 1998/05/27 */
//UBYTE	CheckPollingCommand(UBYTE);
#endif
#if (PRO_CIPHER == ENABLE)
UBYTE	SetCipherTxDocDecipherPara(UBYTE *);
#endif
void	SetJournalOnOff(void);
void	PrintJournalList(void);
void	SetCommunicationResult(void);
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/07 */
void	Print_ND_JournalList(void);
#endif
void	PrintGroupList(void);
void	SetMessageOnOff(void);
void	SetMessageDataMode(void);
UBYTE	CoverPageMessageInput(void);
void	PrintMessageList(void);
void	SetNumberOfPages(void);
#if (PRO_PC_PRINT == ENABLE)
void	ResetPrinterBoard(void);
#endif
#if !defined(STOCKHM2)
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/10/15 */
void	ManualCutter(void);
 #endif
#endif
#if defined(STOCKHM2) || (PRO_JOURNAL_VER_UP == ENABLE)	/* Added by SMuratec C.P 2004/06/07 *//* by K.Watanabe 2004/10/15 */
void	DisplayJournalSelect(void);
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/22 */
void	PrintDailyReport(void);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_inst.c
 *-------------------------------------------*/
void	UserInstallOperation(void);
UBYTE	SetDateAndTime(void);
UBYTE	CheckCalenderInput(void);
void	SetClockData(UBYTE);
#if defined(USA)
UBYTE	SetDayLightSaving(void);
#endif
UBYTE	EnterYourTTI(void);
UBYTE	TTI_FaxNumberInput(void);
UBYTE	TTI_NameInput(void);
UBYTE	TTI_ID_NameInput(void);
UBYTE	SetPhoneType(void);

/* É_ÉCÉÑÉãÉgÅ[ÉìåüèoëŒâû by SMuratec âƒ 2004/7/13 */
#if defined(STOCKHM2) || defined(HINOKI3)
UBYTE	SetDialTone(void);
#endif

UBYTE	SetAutoReceiveMode(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1997/12/10 */
UBYTE	ConfirmPrintSettingList(void);
#endif
#if (PRO_MULTI_LINE == ENABLE)
UBYTE	EnterMultiLineYourTTI(UBYTE);
UBYTE	SetMultiLinePhoneType(UBYTE);
UBYTE	SetMultiLineTxRx(void);
UBYTE	SetMultiLineLineType(void);
UBYTE	SetPstnAccessNumber(void);
#endif
#if (PRO_MULTI_TTI == ENABLE) /* By H.Fujimura 1999/03/25 */
UBYTE	EnterMultiYourTTI(UBYTE i);
UBYTE	Multi_TTI_FaxNumberInput(UBYTE i);
UBYTE	Multi_TTI_NameInput(UBYTE i);
#if (PRO_JIS_CODE == ENABLE)
UBYTE	Multi_TTI_ID_NameInput(UBYTE i);
#endif
#endif

#if defined (KEISATSU) /* åxé@FAX Added by SMuratec K.W.Q 2005/06/02 */
UBYTE	SetDefaultLine(void);
UBYTE	SetDefaultCOMMethod(void);
UBYTE	SetKeidenScramleOn(void);
UBYTE	SetKanyuScramleOn(void);
#endif		/* End of (defined (KEISATSU)) */


/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_int.c
 *-------------------------------------------*/
void	OPR_KeyScan(void);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_key.c
 *-------------------------------------------*/
void	OPR_GetKey(UWORD);
UBYTE	GetInputKeyCode(void);
UBYTE	GetInputKeyType(void);
void	OPR_KeyTask(void);
UBYTE	GetKeyPortBit(void);
void	OPR_CheckOnetouchSheetTask(void);
UBYTE	GetOnetouchSheetStatus(void);
void	AckBuzzer(void);
void	NackBuzzer(void);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_lcd.c
 *-------------------------------------------*/

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*/	/* ÇgÇhÇmÇnÇjÇh É^ÉCÉv *//* Add By O.Kimoto 1998/08/28 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ÇgÇhÇmÇnÇjÇh É^ÉCÉv *//* Add By O.Kimoto 1998/08/28 */ /* Add by Y.Kano 2003/07/11 */

	void  WaitSoftWareTimer(unsigned short  time);
	void  LCD_WriteInstruction(unsigned char  instruction);
	void  LCD_Initialize(void);
	void  DisplayLCD(void);
	void  DisplayStringHigh(unsigned char  pos,unsigned const char  *string);
	void  DisplayStringLow(unsigned char  pos,unsigned const char  *string);
	void  ClearDisplayHigh(void);
	void  ClearDisplayLow(void);
	void  CursorCtrlInit(unsigned char  type,unsigned char  start_col,unsigned char  end_col);
	void  CursorOn(unsigned char  pos);
	void  CursorOff(void);
	void  SetCursorPos(unsigned char  pos);
	void  CursorRightMove(void);
	void  CursorLeftMove(void);
	void  DisplayAllBlack(void);
	unsigned char  CheckSpecialCharacter(unsigned char  character);
	void  DisplayChar(unsigned char  pos,unsigned char  dsp_char);
	void  CheckChangeCGRAM(unsigned char  *string);
	void  DisplayFlashStringHigh(unsigned char  pos,unsigned char  *string);
	void  DisplayFlashStringLow(unsigned char  pos,unsigned char  *string);
#else
 #if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/15 */
void	LCD_RegisterSet(UDWORD, UBYTE);
void	LCD_Initialize(void);
void	ClearByteCharacterDotPattern(UBYTE, UBYTE);
void	DisplayString(UBYTE, UBYTE *);
void	DisplayString0(UBYTE *);
void	DisplayString1(UBYTE *);
void	DisplayString2(UBYTE *);
void	DisplayString3(UBYTE *);
void	DisplayStringWithRightSpace0(UBYTE *);
void	DisplayStringWithRightSpace1(UBYTE *);
void	DisplayStringWithoutLeftSpace(UBYTE, UBYTE *);
void	DisplayBlinkString(UBYTE, UBYTE *);
void	NormalString(UBYTE, UBYTE);
void	BlinkString(UBYTE, UBYTE);
void	ClearString(UBYTE, UBYTE);
void	ClearString0(void);
void	ClearString1(void);
void	ClearString2(void);
void	ClearString3(void);
void	ClearDisplay(void);
void	ContinuouslyClearString(UBYTE, UBYTE);
void	ReverseChar(UBYTE);
void	NormalChar(UBYTE);
void	ClearChar(UBYTE);
void	DisplayShiftJIS(UBYTE, UWORD);
void	PagingON_ForInputJapanese(void);
void	PagingOFF(void);
UBYTE	CheckFontJIS2(UWORD, UWORD);
void	GetByteCharacterDotPattern(UBYTE, UBYTE, UBYTE, UWORD);
void	GetWordCharacterDotPattern(UBYTE, UBYTE, UBYTE, UBYTE, UWORD);
void	GetPictureFontDotPattern(UBYTE, UBYTE, UBYTE, UWORD);
void	Get2ndWordCharacterDotPattern(UBYTE, UBYTE, UBYTE, UBYTE, UWORD);
void	DisplayStringAttribute(UBYTE, UBYTE *, UWORD);
void	DisplayStringToProperPosition(UBYTE, UBYTE, UBYTE *);
void	ChangeCharacterAttribute(UBYTE, UWORD);
void	DisplayStringWithRightSpace(UBYTE, UBYTE *);
void	ChangeStringAttribute(UBYTE, UBYTE, UWORD);
void	DisplayCursorON(UBYTE);
void	DisplayCursorOFF(void);
 #else	/* (PRO_ANK_TO_KANJI == DISABLE) */
	void	LCD_SoftWearTimer(UWORD);
	void	LCD_WriteInstruction(UBYTE);
	void	LCD_BusyFlagWait(UWORD);
	void	LCD_WriteData(UBYTE);
	void	WriteCGRAM(UBYTE *);
	void	LCD_Initialize(void);
	void	InitializeCGRAM_Data(void);
	UBYTE	CheckSpecialCharacter(UBYTE);
	void	CheckChangeCGRAM(UBYTE *);
 #endif	/* (PRO_ANK_TO_KANJI == ENABLE) */
	void	DisplayStringHigh(UBYTE, UBYTE *);
	void	DisplayStringLow(UBYTE, UBYTE *);
	void	CursorOn(UBYTE);
	void	CursorOff(void);
	void	DisplayChar(UBYTE, UBYTE);
	void	ClearDisplayHigh(void);
	void	ClearDisplayLow(void);
	void	DisplayFlashStringHigh(UBYTE, UBYTE *);
	void	DisplayFlashStringLow(UBYTE, UBYTE *);
	void	DisplayAllBlack(void);
#endif
#if (PRO_JIS_CODE == ENABLE)
	UWORD	JIS_ToShiftJIS(UWORD);
	void	ShiftJIS_ToJIS(UWORD *, UWORD *);
	UBYTE	GetFontAddress(UDWORD *, UWORD, UWORD);
	UBYTE	CheckJIS1Code(UWORD);
	UBYTE	CheckFontJIS2Code(UWORD);
	UBYTE	CheckShiftJISCode(UBYTE, UBYTE);
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*---------------------------------------------*
	\src\atlanta\opr\ank\src\opr_mer.c
 *---------------------------------------------*/
UBYTE	SetMercuryNumber(void);
UBYTE	SetMercuryPause(void);
UBYTE	MercuryNumberInput(void);
void	SetMercury(void);
/* Add by SMuratec C.P 2004/07/12 */
UBYTE   *ChangeDisplayBuffer(UBYTE *string);
UBYTE	*ChangeInputBuffer(UBYTE *dst_str,UBYTE *src_str);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_name.c
 *-------------------------------------------*/
UBYTE	NameInput(UBYTE);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/14 by K.Okada */
void InputAddressMarkOperation(UBYTE);
#endif
void	NameInputTenKeyOperation(UBYTE, UBYTE);
void	AlphabetInputOperation(UBYTE, UBYTE);
void	ChangeUpperLowerSignal(UBYTE);
void	ChangeNameInputMode(UBYTE, UBYTE);
void	AllClearInputKeyBuffer(void);
void	NameInputHexCodeSet(UBYTE);
UBYTE	ChangeHexCodeToChar(void);
void	DisplayNameInputMode(void);
void	DisplayNameInputValue(void);
void	ChangeRomaToKana(UBYTE, UBYTE);
void	KANA_Data_Set(UBYTE *);
UBYTE	CheckInputCodeOrChangingKana(void);
void	ClearInputKeyBuffer(void);
void	SetCharacterInputMode(void);
#if (PRO_JIS_CODE == ENABLE)
void	NameInputKanjiCodeSet(UBYTE);
#endif
UBYTE	CheckNextDataWrite(UBYTE, UBYTE *);
UBYTE	GetWriteDataCount(void);
void	SetCharacterInputBuf(UBYTE *);
#if (PRO_NAME_RECALL == ENABLE) /* By H.Fujimura 1999/01/07 */
void	NameInputTelephoneBookOperation(UBYTE);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_num.c
 *-------------------------------------------*/
UBYTE	NumberInput(UBYTE);
void	NumberInputInitial(UBYTE type);
UBYTE	NumberInputKeyGet(void);
void	DisplayNumberInput(void);
UWORD	FixedLengthNumberInput(UWORD, UWORD, UWORD, UBYTE, UBYTE *);
UBYTE	FixedLengthNumberInput2(UBYTE, UBYTE, UBYTE, UBYTE, UBYTE, UBYTE *);
UWORD	DecimalPointInput(UWORD, UWORD, UWORD, UBYTE, UBYTE *, UBYTE);
void	FixedNumberDataSet(UBYTE);
void	DisplayFixedNumberInput(void);
void	DisplayDecimalPointInput(void);
UWORD	EnterPassCode(UWORD, UBYTE, UBYTE *);
UWORD	EnterPassCodeProtect(UBYTE *);
void	CharacterInputCursorRightMove(void);
void	CharacterInputCursorLeftMove(void);
void	CharacterInputDataClear(void);
void	CharacterInputDialCharSet(void);
void	DataShiftOneStep(void);
void	CharacterInputDataSet(UBYTE);
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* 1998/04/14 By K.Okada */
void	CharacterInputAddressMarkSet(UBYTE);
#endif
void	CharacterDataSet_FigureCheck(UBYTE);
void	CharacterInputDialMarkSet(UBYTE);
void	CursorRightRotation(void);
void	CursorLeftRotation(void);
void	ClearCharacterInput(void);
UWORD	CharacterInputToNumber(void);
void	StoreCharacterInputValue(UBYTE *, UBYTE);
UBYTE	StoreCharacterInputToSoftDip(void);
UDWORD	StoreCharacterInputToLongGroup(void);
void	StoreCharacterInputToDatabase(UWORD *);
void	StoreSoftDipToCharacterInput(UBYTE);
void	StoreGroupToCharacterInput(UDWORD);
void	SetLongTimeToCharacterInput(UDWORD, UBYTE);
void	SetSpecialTimeToCharacter(void);
UBYTE	CheckCharacterInputEmpty(void);
UBYTE	InputNumberRotation(UBYTE);
void	DisplayNumberRotation(UBYTE);
void	NumberRotationInitial(UBYTE);
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* à⁄êA by SMuratec L.Z.W 2003/09/18 */
void	InputNumberAsteriskSharpKey(CONST UBYTE, CONST UBYTE, UBYTE *, unsigned char *, unsigned char, UBYTE *);	/* 2001/05/01 K.Sasaki */
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/06/21 */
UBYTE	UpdateKeisatsuBuf(void);
UBYTE	KeisatsuSet_OverCheck(UBYTE key);	/* åxé@FAX QAT Added by SMuratec K.W.Q 2005/12/20 */
#endif		/* End of (defined (KEISATSU)) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_okey.c
 *-------------------------------------------*/
void	SingleKeyOperation(UBYTE);
#if (PRO_AUTO_RX_SWITCH == ENABLE)
void	ChangeRxMode(void);
#endif
#if defined(KEISATSU)	/* åxé@FAX Added by SMuratec âƒ 2005/08/05 */
void	UpdateRxModeDisplay(void);
#endif
void	ChangeMode(void);
void	ChangeModeSuperFine(UBYTE *);
void	ChangeModeHalfTone(UBYTE *);
void	ChangeDensity(void);

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

void	SetDensityDispBuffer(UBYTE);
void	ChangeDensityLightToDark(UBYTE *);
void	ChangeDensityDarkToLight(UBYTE *);
void	ChangeDensityRotation(UBYTE *);
#endif
void	ChangeMemoryTx(void);
#if (PRO_STAMP == ENABLE)
void	ChangeTxStamp(void);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_one.c
 *-------------------------------------------*/
void	EnterOneTouch(void);
void	EraseOneTouch(void);
void	PrintOneTouchList(void);
void	OnetouchForwordOperation(void);
void	OnetouchBackOperation(void);
void	EnterOnetouchInitial(void);
UBYTE	SelectOnetouchNumber(void);
void	DisplaySelectOnetouch(void);
UBYTE	CheckOnetouchStoreStatus(UBYTE);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_pol.c
 *-------------------------------------------*/
void	StorePollingDocument(void);
void	ErasePollingDocument(void);
void	PrintPollingDocument(void);
void	PollingOperation(UBYTE);
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	SetStorePollingDocument(UBYTE prg_no);
void	EnterStorePollingDocument(UBYTE prg_no);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_prg.c
 *-------------------------------------------*/
void	EnterProgramOneTouch(void);
void	PRG_OnetouchInitial(void);
UBYTE	SetPrograming(void);
void	DisplaySetPrograming(void);
void	GetProgramOnetouchDial(UBYTE);
void	GetProgramOnetouchOption(UBYTE);
void	GetProgramTime(UDWORD);
UBYTE	ProgramEnter(UBYTE);
void	SetProgramingDialNumber(UBYTE);
void	SetProgramingTime(UBYTE);
void	SetProgramingOption(UBYTE, UBYTE);
void	EraseProgramOneTouch(void);
void	PrintProgramOneTouchList(void);
void	ClearProgramOnetouchRecord(UBYTE);
UBYTE	SelectProgramOnetouch(void);
void	DisplayProgramSelect(void);
void	ProgramForwordOperation(void);
void	ProgramBackOperation(void);
UBYTE	CheckProgramStoreStatus(UBYTE);
void	SetProgramBatchBox(UBYTE);
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/07 */
void	SetSingleKeyToProgram(UBYTE prg_no);
UBYTE	GetPrimaryMode(UBYTE TxMode);
UBYTE	GetTxMode(UBYTE PrimaryMode);
void	SetProgramToSingleKey(UBYTE prg_no);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_prm.c
 *-------------------------------------------*/
void	SetScanParameters(void);
UBYTE	CheckGrayModeSetting(void);
void	SetRxPrintParameters(void);
#if (PRO_COPY_FAX_MODE == DISABLE)	/* by K.Watanabe 1998/08/18 */
void	SetCopyParameters(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
void	SetPaperSize(void);
#if (PRO_PC_PRINT == ENABLE)
void 	Set_PCR_PaperSize(void);
#endif
#endif
void	SetCopyProtect(void);
void	SetDialingPause(void);
void	SetNumberOfRings(void);
void	SetRedial(void);
void	SetECMMode(void);
void	SetPasscode(void);
void	SetClosedNetwork(void);
void	SetSecurityTx(void);
void	SetBlockJunkFax(void);
void	SetRemoteDiagnostic(void);
void	SetMemoryTransmission(void);
void	SetSilentOperation(void);
void	SetProtectPasscode(void);

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/	/* 97/10/17 T.Fukumoto */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 97/10/17 T.Fukumoto */

void	SaveProtectPasscode(void);
#endif
void	AllProtectClear(void);
UBYTE	EraseProtectPasscodeEnable(void);
void	SetOperationProtect(void);
void	SetPINAccessMode(void);
void	SetRingMaster(void);
void	SetStamp(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* by K.Watanabe 1998/08/18 */
void	ResetDrumLife(void);
#endif
#if defined(GBR)
void	SetRxAlarm(void);
#endif
void	FixedNumberInputRangeSet(UWORD, UWORD, UBYTE, UBYTE *);
#if (PRO_DIALIN == ENABLE)
void	SetDialIn(void);
UBYTE	InputDialInNumber(UBYTE *, UBYTE *);
#endif
/*UBYTE	BlockJunkCommandOperation(void);*/
UBYTE	SetJunkMailDial(void);
UBYTE	SetJunkMailCodeSelect(UBYTE);
UBYTE	SettingJunkMailDial(void);
void	JunkMailSelectDisplay(void);
UBYTE	GetJunkMailDialCount(void);
/*void	Del_BlockJunkDuplication(void);*/
UBYTE	Del_BlockJunkDuplication(UBYTE *, UBYTE);
UBYTE	PrintBlockJunkList(void);
#if (PRO_EXT_P_ONETOUCH == ENABLE) /* By H.Fujimura 1999/01/07 */
void	PrintBlockJunkList2(void);
#endif

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

void	SetHoldMelody(void);
#endif
#if (PRO_REMOTE_RX == ENABLE)
void	SetRemoteReceive(void);
#endif
#if (PRO_ONHOOK_RX_SWITCH == ENABLE)
void	SetOnHookReceive(void);
#endif

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

void	PrintSettingList(void);
#endif

#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/06/16 */
void	SetRemoteRxParameters(void);
UBYTE	SetRemoteRxDialMumIssei(void);
UBYTE	SetRemoteRxDialMumKobetsu(void);
#endif		/* End of (defined (KEISATSU)) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_prn.c
 *-------------------------------------------*/
#if (PRO_SECURITY_RX == ENABLE)
void	SetSecurityReceive(void);
void	PrintMemoryReceiveDoc(void);
UBYTE	SecurityRxTimeInput(void);
UBYTE	CheckProtectedDocStored(void);
UBYTE	CheckProtectedDocStoring(void);
void	CalculateSecurityRxStartTime(UDWORD);
void	AllClearPrintProtect(void);
void	SetSecurityRxMode(void);
void	SetSecurityRxChkMsgPrint(void);
void	ClearSecurityRxChkMsgPrint(void);
UBYTE	CheckSecurityRxChkMsgPrint(void);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_ram.c
 *-------------------------------------------*/
void	SF_SRAM_Check(void);
UBYTE	SRAM_Check(UBYTE, UBYTE **, UBYTE *);
/*UBYTE	SRAM_Check(UBYTE, UBYTE *, UBYTE *);*/
UBYTE	SF_SelectStopOrContinue(void);
void	SF_DRAM_Check(void);
/*UBYTE	DRAM_Check(UBYTE, UBYTE);*/
UBYTE	DRAM_Check(UBYTE);
UBYTE	DRAM_CheckFull(UBYTE);
UBYTE	DramAreaInput(UBYTE *);
void	DisplayDramInput(UBYTE);
void 	DisplayDRAM_Check(UBYTE *);
void	ClearDRAM(void);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_rsv.c
 *-------------------------------------------*/
void	ReviewCommandOperation(void);
UBYTE	SelectReviewOperationType(void);
UBYTE	ConfirmClearCommandOperation(void);
void	ClearReviewControlData(void);
UBYTE	SetCommandPointer(UBYTE);
UBYTE	CheckCommandReviewMode(void);
UBYTE	SearchExecQueue(UBYTE, UBYTE);
UBYTE	CheckExecQueueBeforeStart(UBYTE);
UBYTE	CheckExecuteExecQueue(UBYTE);
UBYTE	CheckExecKindNumber(UBYTE, UBYTE, UBYTE);
UBYTE	CheckExecuteCommand(UBYTE, UBYTE);
UBYTE	ClearReviewCommandData(void);
UBYTE	CheckCommandPrinting(UBYTE, UBYTE);
UBYTE	CheckAllClearExecQueue(UBYTE, UBYTE);
UBYTE	CheckAllClearCommandDial(UBYTE);
void	ClearAllExecQueueData(UBYTE, UBYTE);
void	ResetAllScannerParameter(void);
void	ClearCommandBatchFile(UBYTE, UBYTE);
UBYTE	CheckBroadCastCommand(void);
void	ResetExecPointer(void);
UBYTE	SetExecPointer(UBYTE);
void	ChangeCommandReviewMode(void);
UBYTE	CheckCommandBatchStatus(UBYTE, UBYTE);
void	DisplayReviewCommand(void);
UBYTE	SetCheckConfirmReport(void);
#if (PRO_MULTI_LINE == ENABLE)
UBYTE	MultiDisplaySelect(void);
void	MultiOverWriteDisplayData(UBYTE);
#endif
void	DisplaySpeedDialSet(UBYTE, UWORD);
UBYTE	SearchDialData(struct SYS_DialData_t *, UBYTE *, UBYTE *);
#if (PRO_COMM_RESULT_REVIEW == ENABLE)	/* í êMåãâ ï\é¶ */
UBYTE	SelectReviewCommandOperation(void);
UBYTE	SelectCommandResult(void);
void	DisplaySelectCommandResult(void);
UBYTE	CommandResult(void);
void	DisplayResult(UBYTE index, UBYTE data_max, UBYTE count);
void	OPR_CommunicationResult(UWORD Result, UBYTE *ResultName);
void	ConfirmClearResultCommand(void); /* Add by SMuratec C.P 2004/06/10 */ 
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* (ÉRÉ}ÉìÉhÉtÉ@ÉCÉãÇÃéQè∆à íuÇÃÉZÉbÉg) Added by SMuratec L.Z.W 2003/10/24 */
UBYTE SetBackCommand(UBYTE mode);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_scur.c
 *-------------------------------------------*/
void	SetSecureMailBox(void);
UBYTE	SecureBoxInput(void);
UBYTE	SecurePasscodeCheck(void);
UBYTE	SecureNameInput(void);
UBYTE	SecurePasscodeInput(void);
void	SetSecureMailComplete(void);
void	DisplaySetSecureMailBox(UBYTE);
void	PrintSecureMailList(void);
void	PrintSecureMailDocument(void);
void	ClearMailBox(UBYTE);
void	SetSecureMailHoldTime(void);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_serv.c
 *-------------------------------------------*/
void	MachineParameterMode(void);
void	MemorySwitchMode(void);
UBYTE	SelectSetClearMode(void);
void	SetSoftSwitch(void);
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)
UBYTE	SelectSoftSwitch(UBYTE);
#else
UBYTE	SelectSoftSwitch(void);
#endif
void	DisplaySoftSwitchSelect(void);
void	ClearSoftSwitch(UBYTE);
UBYTE	SoftDipInput(void);
void	SoftDipInputInitial(void);
void	ClearBackUpFile(void);
void	ClearAllBackUpFile(void);
void	UniqSwitchMode(void);
void	T30MonitorPrintOperation(void);
#if (PRO_PRINT_TYPE == LED)	/* 1997/07/10 Y.Matsukuma */
void	PrintMaintenance(void);
void	ReplaceCountSetOperation(void);
void	ServiceCallOperation(void);
void	SearchServiceCallRight(UBYTE *);
void	SearchServiceCallLeft(UBYTE *);
#endif
void	FunctionListPrintOperation(void);
void	ServiceFunctionSetting(void);
void	SF_InnerStatusOperation(void);
void	SF_LifeMonitorClear(void);
void	SF_TestPatternOperation(void);
void	DisplayPatternPrint(UBYTE, UBYTE);
void	SF_StampTest(void);
void	SF_DocumentFeedOutTest(void);
void	SF_ShadingOperation(void);
void	PrintMemorySwList(void);
void	FactoryFunctionMode(void);
void	PrintFactoryFunctionList(void);
void	SF_All_LED_Test(void);
void	SF_LED_Test(void);
void	SF_LCD_Test(void);
void	SF_PanelKeyTest(void);
void	SF_RTCTestFunction(void);
void	SF_RS232CTestFunction(void);
#if (0)	/* É`ÉFÉbÉJÅ[ÇÃÇ› 97/09/10 By M.Kuwahara */
void	SF_CassetteCheck(void);
void	DisplayCassetteCheck(UBYTE);
#endif
#if defined (KEISATSU) /* åxé@FAX 05/12/13 êŒã¥ê≥òa */
void SF_CopyOnetouchA_ToAll(void);
void SF_TonalTestWithVariableAtt(UWORD, UWORD, UBYTE*);
#endif
void	LineFunctionMode(void);
void	SF_RelayTest(void);
void	DisplayRelayTest(void);
void	SF_TonalTest(void);
UBYTE	TxSignalType(UBYTE);
UBYTE	TxSignalFreq(UBYTE, UBYTE);
void	FskPixStop(void);
void	DisplayTonalTest(UBYTE, UBYTE, UBYTE);
void	SF_DTMF_Test(void);
void	DisplayTxDTMF(UBYTE);
UBYTE	DTMF_TypeGet(UBYTE);
void	ConnectLine(void);
void	DisconnectLine(void);
void	InvalidServiceFunction(void);
void	TeachingRingPattern(void);
#if (PRO_RING_MASTER == ENABLE)
void	DisplayTeachingPattern(UBYTE);
#endif
void	SetMirrorCarrigeTransMode(void);
void	ConsumptionArticleOrderFunc(void);
UBYTE	EnterConsumerOrder(void);
UBYTE	ToCustomerCodeInput(void);
UBYTE	ToCompanyNameInput(void);
UBYTE	FromCustomerCodeInput(void);
UBYTE	FromCompanyNameInput(void);
UBYTE	FromSectionNameInput(void);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
UBYTE	FromSectionName2Input(void);  /* orderbythonda1998/05/18 */
#endif
UBYTE	FromCustomerTelNumberInput(void);
#if defined(US1)
UBYTE	ToCompanyFaxNumberInput(void);	/* orderbythonda1998/11/11 */
UBYTE	ToCompanyTelNumberInput(void);	/* orderbythonda1998/11/11 */
#endif
UBYTE	SerialNumberInput(void);
#if(0)	/* ÇqÇnÇlóeó çÌå∏ÇÃà◊ by K.Watanabe 1998/04/24 */
//UBYTE	SetDateInput(void);
#endif
UBYTE	PrintConsumerOrderForm(void);
void	ServicePrintSettingList(void);
#if (PRO_MULTI_LINE == ENABLE)
void	MultiLineFunctionMode(void);
void	SF_MultiRelayTest(void);
void	SF_MultiTonalTest(void);
void	SF_MultiDTMF_Test(void);
UWORD	MultiPixPattern(UWORD);
void	DisplayMultiTonalTest(UBYTE, UBYTE );
void 	DisplayMultiTxDTMF(UBYTE);
#endif
void	SF_OptionDataInitial(void);
void	ClearOrderData(void);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
void	SetLifeMonitorPasscode(void);
#endif

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI) *//* By H.Fujimura 1999/01/07 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* By H.Fujimura 1999/01/07 */ /* Add by Y.Kano 2003/07/11 */

void	EditLifeMonitor(void);
UBYTE	LifeMonitorNumberInput(UBYTE *, UBYTE);
#endif
void	SetMonitorSpeakerOnOff(void);
void	MemoryDump(void);
#if defined (KEISATSU) /* åxé@FAX 05/12/12 êŒã¥ê≥òa */
void DisplayCommunicationSpeed(void);
#endif
UBYTE	InputAddressOrLength(UBYTE *, UBYTE, UBYTE, UBYTE *);
void	MaintenanceOperationMode(void);
void	MachineStatusMonitor(void);
void	Class1MonitorPrintOperation(void);
void	PrinterStatusMonitor(void);
#if defined(POPLAR_F) || defined(SATSUKI2) || defined(STOCKHM2)	/* Add by Y.Kano 2003/10/02 */
void	EmptyAndMemoryAreaDisplay(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ŒﬂÃﬂ◊ÇÃROMóeó çÌå∏ÇÃà◊ÅAèåè∫› ﬂ≤Ÿí«â¡ by K.Watanabe 1998/04/24 */
void	EmptyAndMemoryAreaDisplay(void);
#endif
void	ServiceReportPrintOperation(void);
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/* by K.Watanabe 1998/09/24 */
void	PrintErrorList(void);
#endif
void	MaintenanceSwitchMode(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L) /* 1998/01/29 Y.Matsukuma */
void 	ChangeRxSecondLine(void);
#endif
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/13 Y.Matsukuma */
void 	MinoltaTestOperation(UBYTE);
void	ClearMinoltaTestPrintArea(void);
void	MinoltaTestPatternPrint(UBYTE);
void	MinoltaTestPatternPrintCheck(void);
void	MinoltaTestPatternPrintPG(void);
void	MinoltaTestPatternDisplay(void);
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/22 Eguchi */
void	IfaxMonitorPrint(void);
#endif
#if (PRO_MODEM == R288F) /* By H.Fujimura 1999/01/07 */
void	R288F_LineFunctionMode(void);
void	SF_R288F_RelayTest(void);
void	SF_R288F_TonalTest(void);
void	SF_R288F_DTMF_Test(void);
UWORD	R288F_PixPattern(UWORD);
void	Display_R288F_TonalTest(UBYTE, UBYTE);
void	Display_R288F_TxDTMF(UBYTE);
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/07 */
void	OPR_NumberDisplayCarPatternMode(void);
#endif

/* à⁄êA by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI) *//* By H.Fujimura 1999/01/07 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* By H.Fujimura 1999/01/07 */ /* Add by Y.Kano 2003/07/11 */

void	AllOnetouchSpeedInput(void);
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L)			/* Ãß∞Ωƒ/◊Ωƒ∏ÿ± 2002/04/04 By M.Maeda */
void	FirstOrLastClear(UBYTE);				/* Ãß∞Ωƒ/◊Ωƒ∏ÿ± 2002/04/04 By M.Maeda */
#endif											/* Ãß∞Ωƒ/◊Ωƒ∏ÿ± 2002/04/04 By M.Maeda */

#if defined (KEISATSU) /* åxé@FAX 05/11/18 êŒã¥ê≥òa */
void FactoryFirstClear(void);
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)
void	DisplayRemoteTransferSetting(void);		/* REMOTE_RX_FUNC ê›íËï\é¶ 2003/02/13 H.Tokuno */
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || (defined(HINOKI2) && defined(JPNNTT)) || defined(HINOKI3)	/* Add by Y.Kano 2003/10/17 */ /* by Y.kano 2005/02/14 */
void	SF_PS2AdjustFunction(void);
UBYTE	PS2VolumueAdjustStanby(void);
UBYTE	PS2VolumueAdjust(void);
void 	DisplayPS2Volumue(void);
void	SF_PS1_PB4_CheckFunction(void);			/* Add by Y.Kano 2003/12/18 */
UBYTE	PS1_PB4_Paper_Set_CheckStanby(void);	/* Add by Y.Kano 2003/12/18 */
UBYTE 	PS1_PB4_PaperSet_Check(void);			/* Add by Y.Kano 2003/12/18 */
void 	DisplayPS1_PB4_Set(UBYTE, UBYTE);		/* Add by Y.Kano 2003/12/18 */
UBYTE 	PS1_PB4_Paper_Non_CheckStanby(void);	/* Add by Y.Kano 2003/12/18 */
UBYTE 	PS1_PB4_PaperNon_Check(void);			/* Add by Y.Kano 2003/12/18 */
void	SF_PS1_PB4_ThresholdSet(void);			/* Add by Y.kano 2003/12/26 */
void	PS1_PB4_ThresholdSet(void);				/* Add by Y.kano 2003/12/26 */
UWORD	WordTypeCheckSum(UWORD *, UDWORD);		/* O.Oshima 2004/11/04 */
void	DisplayCheckSum(void);					/* O.Oshima 2004/11/04 */
#endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || (defined(HINOKI2) && defined(JPNNTT)) || defined(HINOKI3) */

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* ÇoÇrÇPÅAÇoÇrÇQÅAÇoÇaÇSËáílê›íËÉÇÅ[Éh by Y.Kano 2004/10/06 */
void SF_PS1_PS2_PB4_AdjustFunction(void);
void PS1_PS2_PB4_Paper_Non_Stanby(void);
void PS1_PS2_PB4_SensorThresholdSet(void);
void PS1_PS2_PB4_Paper_Set_Stanby(void);
void PS1_PS2_PB4_SensorTest(void);
void DisplayPS1_PS2_PB4_Result(UBYTE, UBYTE, UBYTE);
#endif	/* End of (PRO_PAPER_AD_SENSOR_INIT == ENABLE) */

#if (PRO_RTC_RX5C338A == ENABLE)
void	SF_RTC_Initialize(void);
#endif

#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)	/* ñhç–FAXëŒâû by Y.Kano 2005/03/04 	*/
void	DisasterPreventionFaxOperation(void);
void	DisasterPreventionFaxSetting(void);
void	DisasterPreventionSet(void);
void	DisasterPreventionClr(void);
#endif

#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/06/10 */

/*	åxìdÉTÅ[ÉrÉXê›íË	*/
UBYTE SetS1Bypass(void);
UBYTE	SetScrambleAvailable(void);
UBYTE	SetKeyLockOn(void);
UBYTE	SetSendLevel(void);
UBYTE	SetDTMFSendLevel(void);
#if (1)
UBYTE	SetIsseiRingTimeout(void);
#else
UBYTE	SetIsseiRingCount(void);
#endif
UBYTE	SetIsseiAbility(void);
UBYTE	SetIsseiTimeOut(void);
UBYTE	SetRemoteRxDialOne(void);
UBYTE	SetKeidenRxPriority(void);
void	GetFPGAVersion(void);
UBYTE	SetKeidenDialTone(void);

UBYTE	SetKeyLock(int);
UBYTE	SetIsseiSpeed(void);
UBYTE	SetIsseiCode(void);
UBYTE	SetIsseiMinScanLineTime(void);
#endif		/* End of (defined (KEISATSU)) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_sett.c
 *-------------------------------------------*/
UBYTE	EnterSettingStatus(UBYTE *, UBYTE *, UBYTE, UBYTE, UBYTE, UBYTE);
void	DisplayEnterSetting(void);
void	SettingForwordOperation(void);
void	SettingBackOperation(void);
void	CheckSelectItemEnable(UBYTE);
#if (PRO_PC_PRINT == ENABLE)
UBYTE	EnterSettingStatusToLong(UBYTE *, UBYTE *, UBYTE, UBYTE, UBYTE, UBYTE);
void	DisplayEnterSettingToLong(void);
void	SettingForwordOperationToLong(void);
void	SettingBackOperationToLong(void);
void	CheckSelectItemEnableToLong(UBYTE);
#endif
UBYTE	SelectData(UBYTE *, UBYTE *, UBYTE, UBYTE *, UBYTE, UBYTE); /* Modified by S.Fukui Oct.1,1997 */
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_spd.c
 *-------------------------------------------*/
void	EnterSpeedDial(void);
void	EraseSpeedDial(void);
void	PrintSpeedDialList(void);
UBYTE	SelectSpeedNumber(void);
UBYTE	InputSpeedOptionalNumber(void);
void	SpeedForwordOperation(void);
void	SpeedBackOperation(void);
void	SpeedOperationInitial(void);
void	SpeedSelectDisplay(void);
void	SpeedSelectOptionalDisplay(void);
UWORD	GetRecordFromNumber(UWORD);
UBYTE	SetOptionalSpeedStatus(UWORD);
UBYTE	GetSpeedEntryCount(void);
UBYTE	GetSpeedDialRecord(void);
void	SetSpeedControlTable(void);
void	DeleteSpeedControlTable(void);
UBYTE	CheckSpeedStoreStatus(UBYTE);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_spe.c
 *-------------------------------------------*/
UBYTE	SpecialCommandOperation(UBYTE);
UBYTE	SelectSpecialCommand(UBYTE);
void	DisplaySelectSpecialCommand(UBYTE, UBYTE);
UBYTE	DelayedTransmissionOperation(UBYTE);
UBYTE	DelayedTransmissionTimeInput(void);
UBYTE	CheckAndCalculateCommandTime(void);
UDWORD	TotalMinutesFromMonthHead(UBYTE, UBYTE, UBYTE);
UBYTE	ProgramTimeInput(void);
UBYTE	CheckAndSetProgramTime(void);
void	DisplayTimeInput(UBYTE);
UBYTE	SecureTransmissionOperation(void);
UBYTE	RelayTransmissionOperation(void);
UBYTE	PollingCommunicationOperation(void);
void	DataBaseInputInitial(void);
UBYTE	CheckDataBasePollingInput(void);
UBYTE	CheckDataBaseFileNumber(void);
void	PollingOptionSet(void);
#if (PRO_BATCH_TX == ENABLE)
UBYTE	BatchTransmissionOperation(void);
UBYTE	FinalBatchTxOperation(UBYTE, UBYTE);
void	DisplayFinalBatchTx(UBYTE, UBYTE);
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
UBYTE	ContPollingOperation(void);
UWORD	ContPollingTimeInput(void);
#endif
#if (PRO_F_CODE == ENABLE)
UBYTE	FcodeTransmissionOperation(void);
UBYTE	FcodePollingOperation(void);
UBYTE	ComOptionFcodeNumberInput(void);
#endif
#if (PRO_CIPHER == ENABLE)
UBYTE	CipherTransmissionOperation(void);
UBYTE	ComOptionCipherTxParaInput(void);
#endif
UBYTE	ExistPinNumberAtSelectedBox(UBYTE);

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_sub.c
 *-------------------------------------------*/
void	OPR_Initial(void);
UBYTE   CheckReservedCommandExist(void);
UBYTE	CheckExecuteCommandExist(void);
UBYTE	CheckRedialQueueExist(void);
UBYTE	CheckReservedBatchExist(void);
#if (PRO_BATCH_TX_RESERVE_LIST == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	CheckExecuteBatchExist(void);
#endif
UBYTE	FigureCalculation(UWORD);
void	MainTaskExecWait(void);
void	OPR_SubMessageReceiveTask(void);
void	FinalMemoryPrintOperation(UBYTE, UWORD, UBYTE);
UBYTE	CheckMemDocPrinting(UBYTE, UWORD);
UBYTE	CheckMemDocStoring(UBYTE, UWORD);
void	FinalListPrintOperation(UBYTE);
UWORD	GetStringGapPoint(UBYTE *, UBYTE);
UBYTE	GetBCD_StringLength(UBYTE *);
UBYTE	CheckAndGetSubDialEmptyArea(void);
UBYTE	SetToCheckBuffer(UBYTE *, UBYTE);
UBYTE	CheckMaxFigureOver(UBYTE);
UBYTE	CheckInputRangeOver(UWORD, UWORD);
UBYTE	CheckNumberOnlyInput(void);
UBYTE	CheckNumberFigureRange(UBYTE, UWORD, UWORD);
UBYTE	CheckDirectDialNumberInput(void);
UBYTE	CheckInputDialMarkOnly(void);
UBYTE	CheckCountryDialNumber(void);
UBYTE	CheckGroupDialStoreStatus(UBYTE);
UBYTE	ErrorPositionSet(void);
UBYTE	CheckCommandNumber(void);
void	ConvertAstToPinMark(void);
UBYTE	CheckOnetouchPinNumberStore(UBYTE);
UBYTE	CheckSpeedPinNumberStore(UBYTE);
UBYTE	CheckGroupPinNumberStore(UBYTE);
UBYTE	CheckProgramPinNumberStore(UBYTE);
UBYTE	FinalBroadcastCheck(UBYTE);
UBYTE	CheckScanStartEnable(UBYTE);
#if (PRO_FBS == ENABLE)
UBYTE	BookDocSizeSetOperation(UBYTE);
#endif
UBYTE	CheckPrintOperationEnable(void);
UBYTE	ClearCompleteDisplayOperation(UBYTE *);
UBYTE	ChildCompleteOperation(void);
UBYTE	CheckProtectPasscodeSet(void);
UBYTE	ChangeNumberToASC_Code(UBYTE);
#if defined(ANZU_L)
UBYTE	GetOnetouchSideCode(UBYTE);
#endif
UBYTE	ChangeNumberToOnetouch(UBYTE *, UBYTE);
UBYTE	ChangeASC_CodeToNumber(UBYTE);
UBYTE	CheckFaxComExecute(void);
UBYTE	CheckLeapYear(UBYTE);
UBYTE	GetDayFromMonth(UBYTE, UBYTE);
UBYTE	CheckMemoryOver(void);
#if (PRO_MULTI_LINE == ENABLE)		/* 1997/06/23 Y.Matsukuma */
UBYTE	InputPbxCheck(UBYTE);
UBYTE	MultiLineBusy(void);
UBYTE	MultiOptAllLineBusy(void);
#endif
UBYTE	CheckReservedContPollingExist(void);
void	SetDialDataToDispBuffer(UBYTE, struct SYS_CommandData_t *, UBYTE *);
UBYTE	CheckSettingDataLength(UBYTE, UWORD);
UBYTE	CheckOnetouchData(UBYTE);
UBYTE	SetOnetouchCode(UBYTE *, UBYTE, UBYTE);
UBYTE	CheckProgramOnetouchData(UBYTE);
UBYTE	CheckTelephoneUsing(void);
UBYTE	GetPaperSize(UBYTE);
void	CheckOperationValid(UBYTE *);
UBYTE	Check_BCD_StringCompare(UBYTE *, UBYTE *, UBYTE);
#if (PRO_KEYPANEL == PANEL_ANZU_L)
UBYTE	ChangeOnetouchCode(UWORD);
#endif
UBYTE	CheckCopyDocStore(void);
UBYTE	CheckExceptCopyDocStore(void);
UBYTE	ConfirmKeyInputOperation(UBYTE *, UBYTE *, UBYTE, UBYTE);
#if defined(FRA)
UBYTE	CheckSameNumber(void);
UBYTE	CheckBCDCompare(UBYTE *, UBYTE *, UBYTE);
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE) || (PRO_NEW_DIAL_OPR == ENABLE)
UBYTE	GetCursorPositionDataKind(UBYTE, UWORD *, UWORD *);
#endif
#if (PRO_DIAL_NAME_DISP == ENABLE)
UBYTE	SetOnetouchSpeedDialName(UBYTE *, UBYTE, UWORD);
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE) || (PRO_FCODE_RELAY == ENABLE) /* By H.Fujimura 1999/01/07 */
void	SetDialDataToDispBuffer2(UBYTE, UBYTE *, UBYTE *, UBYTE *, UDWORD, UBYTE *);
#endif

UBYTE CheckScanDisableCondition(void);	/* Add By O.Kimoto 1999/07/19 */
#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/08/18 */
UBYTE	CheckIsKanyuLine(void);
UBYTE	CheckIsKobetsuMode(void);
UBYTE	CheckIsScrambleOFF(void);
UBYTE	CheckIsSenyou(void);
#endif		/* End of (defined (KEISATSU)) */

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_tbok.c
 *-------------------------------------------*/
void	SetTelephoneBook(UWORD);
UBYTE	GetTelBookKeyWord(UWORD);
UBYTE	GetTelBookSortPriority(UBYTE);
UWORD	SearchTelBookInsertPosition(UWORD, UBYTE);
UBYTE	CompareRemoteName(UWORD, UWORD);
void	ShiftTelBookData(UWORD, UBYTE);
void	InsertNewTelBookData(UWORD, UBYTE, UWORD);
void	DeleteTelBookData(UWORD);
UBYTE	TelephoneBookOperation(UBYTE);
void	TelBookUpSearch(void);
void	TelBookDownSearch(void);
void	TelBookLeftSearch(void);
void	TelBookRightSearch(void);
void	ResetTelBookDataExistPoint(void);
UBYTE	TelBookStartOperation(UBYTE, UBYTE);
void	DisplayTelBookOperation(void);
UWORD	GetTelBookDataPoint(void);
void	ResortTelephoneBookData(void);
#if (PRO_NAME_RECALL == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	TelephoneBookOperation2(void);
void	DisplayTelBookOperation2(void);
#endif

/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_tel.c
 *-------------------------------------------*/
void	TelOperation(UBYTE, UBYTE);
void	TelOperationInitial(void);
UBYTE	CheckTelephoneStatus(void);
UBYTE	CheckLineStatus(void);
void	HookKeySet(void);
void	HoldKeySet(void);
void	SpeedTelOperation(void);
UBYTE	SpeedOperationSelect(void);
void	ManualTRxOperation(void);
void	OnetouchDialStart(UBYTE);
void	SpeedDialStart(UBYTE);
void	RedialStart(void);
void	DialMarkStart(UBYTE);
void	DirectDialStart(UBYTE);
UBYTE	TelPinNumberInput(UBYTE *);
void	SetDialingBuffer(void);
UBYTE	CheckDialingEnable(UBYTE);
void	DisplayNCUStatus(void);
void	DisplayTelNumber(void);
void	SpeakerVolumeAdjust(void);
void	DisplayMonitorSpeakerVolume(void);
void	ChangePanelBusy(void);
#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/08/09 */
UBYTE	CheckRemoteTransfer(UBYTE);
UBYTE	CheckKeidenRxPriorityON(void);
void	ResetKeisatsuAttribute();
#endif		/* End of (defined (KEISATSU)) */


/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_top.c
 *-------------------------------------------*/
void	OPR_Task(void);
void	OperationStart(void);
void	OperationEnd(void);
void	HookKeyOperation(void);
void	StopKeyOperation(void);
#if (PRO_CIPHER == ENABLE)
void	ConfirmStopCipherExecuting(void);
#endif
void	MemoryOverOperation(void);
void	JamRecoverOperation(UBYTE);
#if (PRO_FBS == ENABLE)
void	NextDocStoreOperation(void);
#endif
#if (PRO_CIPHER == ENABLE)
void	DifferentKeyOperation(void);
void	EraseRxCipherDocOperation(void);
#endif
void	DisplayChildError(void);
UBYTE	OperationProtectReset(UBYTE);
#if (PRO_STOP_MODE_CLEAR == ENABLE) /* By H.Fujimura 1999/01/07 */
UBYTE	CheckLocalKeyChange(void);
#endif
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)
UBYTE	ScanReservingOperation(void); /* QATèCê≥ Added by SMuratec óõ 2004/11/09 */
void	DensitySettingOperation(void); /* QATèCê≥ Added by SMuratec óõ 2004/11/10 */
void	ModeSettingOperation(void); /* QATèCê≥ Added by SMuratec óõ 2004/11/10 */
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
#if defined (KEISATSU)		/* åxé@FAX Added by SMuratec K.W.Q 2005/07/15 */
void	SetKeisatsuSettings(void);
void	KeidenKeyOperation(void);
void	IsseiKeyOpration(void);
void	ScramblerKeyOpration(void);
void	KyotsuKeyOpration(void);
void	IsseiTxOperation(void);
#endif		/* End of (defined (KEISATSU)) */

#if (PRO_RX_DOC_TRANSFER == ENABLE) /* By H.Fujimura 1999/01/07 */
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_warp.c
 *-------------------------------------------*/
void	EnterFaxWarp(void);
UBYTE	WarpSelectNumber(UBYTE set_cnt);	/* ÇeÇ`ÇwÉèÅ[Évìoò^êî */
UBYTE	DisplayWarpSelectNumber(void);
UBYTE	WarpInput(struct SYS_SubDialData_t *WarpFile, UBYTE *DisplayBuffer);
UBYTE	WarpAltNumberInput(struct SYS_SubDialData_t *WarpFile);
UBYTE	WarpTimeInput(struct SYS_SubDialData_t *WarpFile);
void	DisplayWarpTimeInput(void);
UBYTE	EnterWarpTimeInput(struct SYS_SubDialData_t *WarpFile);
UBYTE	GetWarpCount(void);
void	ShiftWarpData(void);
void	ClearWarpData(struct SYS_SubDialData_t *WarpFile);
void	PrintFaxWarpList(void);
void	SetFaxWarp(void);
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/07 */
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_nd.c
 *-------------------------------------------*/
void	EnterNumberDisplay(void);
UBYTE	ND_SelectNumber(UBYTE set_cnt);	/* ÉiÉìÉoÅ[ÉfÉBÉXÉvÉåÉCìoò^êî */
UBYTE	Display_ND_SelectNumber(void);
UBYTE	ND_Input(struct SYS_NumberDisplayTable *NumberDisplay, UBYTE *DisplayBuffer);
UBYTE	ND_DialNumberInput(UBYTE *stored_data);	/* ìoò^çœÇ›ÉfÅ[É^ */
UBYTE	Get_ND_Count(void);
void	Shift_ND_Data(void);
void	Clear_ND_Data(struct SYS_NumberDisplayTable *NumberDisplay);
void	PrintNumberDisplayList(void);
void	SetNumberDisplay(void);
#endif

#if (PRO_ANK_TO_KANJI == ENABLE)	/* by K.Watanabe 1999/06/16 */
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\ntt_disp.c
 *-------------------------------------------*/
void	UpdateLCD(void);
void	DisplayMachineError(void);
UBYTE	DisplayMachineErrorLow(UBYTE);
void	DisplayMachineError2(void);
UBYTE	DisplayMachineErrorLow2(UBYTE);
void	DisplayFaxCom(void);
void	DisplayTransmit(void);
void	DisplayReceive(void);
UBYTE	*GetCommunicationResolution(UBYTE);
UWORD	GetCommunicationSpeed(UBYTE baud_rate);
UBYTE	DisplayMultiLineFaxCom(void);
void	DisplayWaitAMinutes(void);
void	DisplayCalender(void);
void	DisplayFeedOut(void);
void	DisplayIdle(void);
void	DisplayRxMode(void);
void	DisplayCopy(UBYTE);
void	DisplayJamRecover(void);
void	DisplayPrinterWarmUp(void);
void	DisplayImagePrint(void);
void	DisplayListPrint(void);
UBYTE	DisplayDocumentStore(void);
void	DisplayDocumentStoreHigh(void);
void	DisplayStoreMemTxDocument(void);
void	DisplayStoreBatcTxDocument(void);
void	DisplayDocumentSet(void);
void	SetDocumentScanSizeWording(UBYTE *, UBYTE);
void	SetRegularDocumentSizeWording(UBYTE *);
void	DisplayComplete(void);
void	DisplayDocumentOnFeeder(void);
#if (PRO_PC_PRINT == ENABLE)
void	DisplayPcPrint(void);
#endif
void	DisplayCopyMode(void);
void	DisplayCopyMode0(void);
void	DisplayCopyMode1(void);
void	DisplayCopyMode2(void);
void	DisplayCopyMode3(void);
void	SetCopyModePaperDensity(void);
void	SetCassettePaperSize(UBYTE *);
UBYTE	*SetCassetteCharacter(UBYTE *, UBYTE);
void	SetCopyModeMagnification(UBYTE *);
void	SetDocumentSize(void);
void	DisplayReplacePaperSize(UBYTE);
void	SetPaperSizeWording(UBYTE *, UBYTE, UBYTE);
#if (PRO_MULTI_LINE == ENABLE)
void	OverWriteDisplayData(UBYTE);
UBYTE	BaudRateCompatible(UBYTE);
#endif
void	DisplayDensity(void);
#endif	/* (PRO_ANK_TO_KANJI == DISABLE) */

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* âπó í≤êÆèàóùÇÃí«â¡ by Y.Kano 2003/08/27 */
/*------------------------------------------*
	\src\atlanta\opr\ank\src\opr_vol.c
 *------------------------------------------*/
void 	VolumeKeyOperation(void);
UBYTE 	ChangeBuzzerVolume(void);
UBYTE 	ChangeMonitorVolume(void);
void 	DisplayHighMonitorVolume(void);
void	DisplayHighBuzzerVolume(void);
UBYTE 	SetRingerControl(void);
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) || defined(HINOKI3) /* à⁄êA by SMuratec L.Z.W 2003/08/13 */ /* Add by Y.Kano 2004/12/21 */
/*-------------------------------------------*
	\src\yawara\src\opr_char.c
 *-------------------------------------------*/
UBYTE	OPR_InputCharacterOperation(CONST UBYTE);
void	OPR_DisplayInputCharacterMode(void);
void	OPR_DisplayInputCharacterData(void);
void	OPR_ChangeInputCharacterMode(CONST UBYTE, UBYTE *);
void	OPR_InputCharacterRightKeyOpr(CONST UBYTE);
void	OPR_InputCharacterLeftKeyOpr(void);
void	OPR_InputCharacterTenKeyOpr(CONST UBYTE, CONST UBYTE, CONST UBYTE, UBYTE *);
void	OPR_InputCharacterDataClear(void);
UBYTE	OPR_GetCharacterTable1stArrange(CONST UBYTE);
void	OPR_SetCharacterTableData(CONST UBYTE *, UBYTE *);
void	OPR_InputCharacterCode(CONST UBYTE);
void	OPR_ClearCodeBuffer1Character(void);
void	OPR_AllClearInputKeyBuffer(void);
UBYTE	OPR_CheckInputCharacterCode(void);
UBYTE	OPR_CheckSetNextDataEnable(CONST UBYTE, CONST UBYTE);
UWORD	OPR_GetWriteDataCount(void);
void	OPR_SetRegisteredDataToBuf(UBYTE *, UBYTE *, UBYTE);
void	OPR_InputCharacterTelBook(UBYTE);

/* Added by SMuratec K.W.Q 2003/08/26 */
/*-------------------------------------------*
	\src\atlanta\opr\ank\src\opr_chkr.c
 *-------------------------------------------*/
void	MainCheckerFunctionMode(void);
void	PanelCheckerFunctionMode(void);
UBYTE	MainCheckerFunctionTest(void);

UBYTE	GenerateRingTest(void);
UBYTE	HoldMelody_Test(void);
UBYTE	AllClear_Test(void);
UBYTE 	DRAMCheck_Test(void);
UBYTE	DRAMCheck(void);
UBYTE	SRAMCheck_Test(void);
UBYTE	SRAMCheck(UBYTE Code, UBYTE *(*StartAddress), UBYTE *LimitAddress);

UBYTE	ListPrint_Test(void);
UBYTE	TestPatternOperation_Test(void);
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#endif
