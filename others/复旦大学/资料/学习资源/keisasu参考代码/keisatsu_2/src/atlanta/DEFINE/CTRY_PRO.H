#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\ncu_def.h"

/************************************************************************
 * 国別パラメータに関するプロトタイプ宣言								*
 * SYS_AvailableOfCountry[]												*
 * cmn_ctry.c															*
 ************************************************************************/
UBYTE  CTRY_RelayTx(void);
UBYTE  CTRY_RelayedTx(void);
UBYTE  CTRY_DB_PolingRx(void);
UBYTE  CTRY_DB_PolingTx(void);
UBYTE  CTRY_SecureTx(void);
UBYTE  CTRY_SecureRx(void);
UBYTE  CTRY_SecureDocHoldTime(void);
UBYTE  CTRY_PhoneType(void);
UBYTE  CTRY_Pause(void);
UBYTE  CTRY_BellCount(void);
UBYTE  CTRY_Connecting2Tel(void);
UBYTE  CTRY_RemoteDiag(void);
UBYTE  CTRY_RedialNumber(void);
UBYTE  CTRY_RedialInterval(void);
UBYTE  CTRY_HoldMelody(void);
UBYTE  CTRY_ClosedNetwork(void);
UBYTE  CTRY_TelFaxPrimary(void);
UBYTE  CTRY_SecurityTx(void);
UBYTE  CTRY_BlockJunkFax(void);
UBYTE  CTRY_Stamp(void);
UBYTE  CTRY_MessageTx(void);
UBYTE  CTRY_RS232C(void);
UBYTE  CTRY_Dialin(void);
UBYTE  CTRY_Department(void);
UBYTE  CTRY_Cost(void);
UBYTE  CTRY_BatchTx(void);
UBYTE  CTRY_RCR(void);
UBYTE  CTRY_NonePaperRx(void);
UBYTE  CTRY_RemoteRx(void);
UBYTE  CTRY_TelFaxReady(void);
UBYTE  CTRY_AnsFaxReady(void);
UBYTE  CTRY_HoldKey(void);
UBYTE  CTRY_RedialKey(void);
UBYTE  CTRY_HookKey(void);
UBYTE  CTRY_OffhookTel(void);
UBYTE  CTRY_PauseKey(void);
UBYTE  CTRY_SignalChange(void);
UBYTE  CTRY_1DT_Detect(void);
UBYTE  CTRY_2DT_Detect(void);
UBYTE  CTRY_Catchphone(void);
UBYTE  CTRY_RemoteTakeOut(void);
UBYTE  CTRY_BranchRx(void);
UBYTE  CTRY_PocketBell(void);
UBYTE  CTRY_MonitorOnToDIS(void);
UBYTE  CTRY_PauseCount(void);
UBYTE  CTRY_PauseTimeMin(void);
UBYTE  CTRY_PauseTimeMax(void);
UBYTE  CTRY_RingCountMin(void);
UBYTE  CTRY_RingCountMax(void);
UBYTE  CTRY_RedialNumberMin(void);
UBYTE  CTRY_RedialNumberMax(void);
UBYTE  CTRY_RedialIntervalMin(void);
UBYTE  CTRY_RedialIntervalMax(void);
UBYTE  CTRY_InitToneAttenation(void);
UBYTE  CTRY_InitSecureMailRxTime(void);
UBYTE  CTRY_InitPhoneType(void);
UBYTE  CTRY_InitWordingNumber(void);
UBYTE  CTRY_WordingNumberMax(void);
UBYTE  CTRY_CountryType(void);
UBYTE  CTRY_InitPauseTime(void);
UBYTE  CTRY_InitRingCount(void);
UBYTE  CTRY_InitRedialNumber(void);
UBYTE  CTRY_InitRedialInterval(void);
UBYTE  CTRY_RecordPaper(void);

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1996/06/24 H,Yagi *//* by K.Watanabe 2004/10/12 */
UBYTE  CTRY_MercuryPauseTimeMin(void);
UBYTE  CTRY_MercuryPauseTimeMax(void);
UBYTE  CTRY_InitMercuryPauseTime(void);
#endif

/************************************************************************
 * 国別ダイヤルパラメータに関するプロトタイプ宣言						*
 * cmn_ctry.c															*
 ************************************************************************/
struct  DialParameters_t *CTRY_DialTable(void);
struct  ToneParameters_t *CTRY_DialTone(void);
struct  ToneParameters_t *CTRY_Dial2ndTone(void);
struct  ToneParameters_t *CTRY_BusyTone(void);
struct  ToneParameters_t *CTRY_CongestionTone(void);
struct  RingData_t *CTRY_RingTable(void);
struct  RingMaster_t *CTRY_RingMasterTable(void);
struct  RingBackToneData_t *CTRY_RBTTable(void);
