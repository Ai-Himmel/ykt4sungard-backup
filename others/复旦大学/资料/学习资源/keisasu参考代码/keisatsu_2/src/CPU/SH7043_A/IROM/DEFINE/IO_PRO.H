/************************************************************************
*	System		: POPLAR/ANZU-L
*	File Name	: IO_PRO.H
*	Author		: ãkê≥é˜
*	Date		: 1996/11/02
*	RealTimeOS	: ÇqÇhÇrÇbÅiÇrÇgÇVÇOÇSÇRÅjÉÇÉjÉ^
*	Description	: ÇhÅ^ÇnÉTÉuÉãÅ[É`Éì
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#ifndef	IO_PRO2_H
	#define	IO_PRO2_H	1

#include "\src\atlanta\define\product.h"

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif

/* CPUå≈óL & ã@éÌã§í  */
UWORD	CMN_CheckSH_WCR1_CS3(void);
void	CMN_SetSH_WCR1_CS3(UWORD wait);
void	AnalogSwitchTONE_Set2(void);	/* added by H.Hirao 1999/05/25 */

/* ã@éÌå≈óL */
UBYTE	OffHook1(void);
UBYTE	OffHook2(void);
UBYTE	LCV_Status(void);
UBYTE	DSE1(void);
UBYTE	DSE2(void);
UBYTE	CCD_MakerTOSHIBA(void);
UBYTE	CCD_SizeB4(void);
UBYTE	RTC_DataRead(void);
UBYTE	DTMF_Decision(void);
UBYTE	DTMF_Code(void);
UBYTE	DS1(void);
UBYTE	DS2(void);
UBYTE	Exist288KModem(void);
UBYTE	DA3(void);
UBYTE	DB4(void);
UBYTE	TwoLine(void);
UBYTE	PrinterOption(void);
UBYTE	TXIL(void);
UBYTE	DSW(void);
/*UBYTE	PREQ(void);	*/
UBYTE	DialIn(void);
UBYTE	CML_RelaySetting(void);
UBYTE	H_RelaySetting(void);
UBYTE	L_RelaySetting(void);
UBYTE	DP_RelaySetting(void);
UBYTE	S_RelaySetting(void);
UBYTE 	CONT24_Setting(void);
void	Reset288ModemOn(void);
void	Reset288ModemOff(void);
void	RTC_ChipEnable(void);
void	RTC_ChipDisable(void);
void	RTC_DataWriteSet(void);
void	RTC_DataReadSet(void);
void	RTC_ClockUp(void);
void	RTC_ClockDown(void);
void	RTC_DataWrite_1(void);
void	RTC_DataWrite_0(void);
void	SpeakerMuteOn(void);
void	SpeakerMuteOff(void);
void	MonitorSpeakerVolumeControl(void);
void	BuzzerVolumeControl(void);
#if defined(SATSUKI2) || defined(STOCKHM2)	/* í«â¡ by Y.Kano 2003/08/06 */
void	SpeakerVolumeOut(void);
void	BuzzerVolumeOut(UWORD, UWORD);
/* à⁄êA by SMuratec K.W.Q 2003/07/24 */
void	CheckTxDialType(void);
void	RingerControlSet(void);
void	RingerControlReset(void);
void	BatteryChargeOn(void);	/* Add by Y.Kano 2003/09/30 */
void	BatteryChargeOff(void);	/* Add by Y.Kano 2003/09/30 */
#endif
void	SetScannerCodecToDramDACK(void);	/*  by T.Soneoka 1998/01/14 */
void	SetScannerDramToCodecDACK(void);	/*  by T.Soneoka 1998/01/14 */
void	AnalogSwitchRXA_Set(void);
void	AnalogSwitchTONE_Set(void);
void	SpeakerOutRXA(void);
void	SpeakerOutBuzzer(void);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui Jun. 19,1998 */
void	MonitorSpeakerOn(void);
void	MonitorSpeakerOff(void);
void	SELDMA_On(void);
void	SELDMA_Off(void);
#endif
void	RI_On(void);
void	RI_Off(void);
void	PHONE2_RelayOn(void);	/*  by T.Soneoka 1997/11/11 */
void	PHONE2_RelayOff(void);	/*  by T.Soneoka 1997/11/11 */
void	PC_24V_On(void);
void	PC_24V_Off(void);
void	LampOn(void);
void	LampOff(void);
void	CMN_EvacuateStampSetting(void);
void	CMN_PushStamp(void);
void	ConnectPrinterToFax(void);
void	DisconnectPrinterToFax(void);
void	FilterRXA_Set(void);
void	FilterTONE_Set(void);
void	FilterCNG_Set(void);
void	NoRingRelayOn(void);
void	CML_RelayOn(void);
void	CML_RelayOff(void);
void	S_RelayOn(void);
void	S_RelayOff(void);
void	H_RelayOn(void);
void	H_RelayOff(void);
void	L_RelayOn(void);
void	L_RelayOff(void);
void	T_RelayOn(void);
void	T_RelayOff(void);
void	DP_RelayOn(void);
void	DP_RelayOff(void);
void	CONT_24V_On(void);
void	CONT_24V_Off(void);
void	TonerSave(UBYTE);
void	PACK_High(void);
void	PACK_Low(void);

/* ÉhÉCÉcédólÅ@*/
void	GroundKeyOn(void);
void	GroundKeyOff(void);

#if (PRO_PRINT_TYPE == LASER)
void	CMN_PrinterDuty50(void);
void	CMN_PrinterDuty100(void);
#endif
#if (PRO_PRINT_TYPE == LED)

UBYTE	RXIL(void);
UBYTE	APS(void);
UBYTE	HV24V(void);
UBYTE	PDS(void);
UBYTE	HPES(void);
UBYTE	PSS(void);
UBYTE	DrumStatus(void);
UBYTE	CheckFanMotorLockEnable(void);
UBYTE	CheckPsFanMotorLockEnable(void);
UBYTE	FanMotorLock(void);
UBYTE	PsFanMotorLock(void);
UBYTE	MotorLock(void);
UBYTE	JamCover1Open(void);
UBYTE	HS(void);
UBYTE	ES(void);
void	HeatOn(void);
void	HeatOff(void);
void	FanControl(UBYTE);
void	PsFanControl(UBYTE);
void	HVC_On(void);
void	HVC_Off(void);
void	HVB_Plus_On(void);
void	HVB_Plus_Off(void);
void	HVB_Minus_On(void);
void	HVB_Minus_Off(void);
void	HVT_Plus_On(void);
void	HVT_Plus_Off(void);
void	HVT_Minus_On(void);
void	HVT_Minus_Off(void);
void	ERSB_On(void);
void	ERSB_Off(void);
void	FuseCutOn(void);
void	FuseCutOff(void);
void	MotorEnable(void);
void	MotorDisable(void);
void	FeedClutchOn(UBYTE);
void	FeedClutchOff(UBYTE);

#if (PRO_MODEM == R288F)	/* Add By O.Kimoto 1997/10/08 */
void	SelectDreqDirection(UBYTE direction);
/* Control relay for Melody */
void	StartSendingMelodyToLine(void); /* added by H.Kubo 1997/10/13 */
void	StopSendingMelodyToLine(void); /* added by H.Kubo 1997/10/13 */
#endif

void	WDT_Enable(void);
void	WDT_Disable(void);
void	WDT_Clear(void);
void	ModemRelay_On(void);
void	ModemRelay_Off(void);
UWORD	AD_Cassette(UBYTE);
UWORD	AD_EnvironmentTemp(void);
UWORD	AD_Battery(void);
UWORD	AD_RollerResist(void);
UWORD	AD_Thermistor(void);
UWORD	AD_Toner(void);

#endif

#if (PRO_FBS == ENABLE)
void CMN_SetTxMotorADF( void );
void CMN_SetTxMotorFBS( void );
#endif
UBYTE	ExistOrangeModem(void);
UBYTE CMN_KinkOfModem(void);	/* Add By O.Kimoto 1997/06/14 */
UBYTE CMN_ForcedDRAM_InitialKey(void);
UBYTE CMN_ForcedDRAM_BackUpKey(void);	/* 1998/02/12  By T.Yamaguchi */



/* ÇkÇdÇcä÷òA */
void	AutoRxLedOn(void);
void	AutoRxLedOff(void);
void	MemoryTxLedOn(void);
void	MemoryTxLedOff(void);
void	MemoryRxLedOn(void);
void	MemoryRxLedOff(void);
void	HookLedOn(void);
void	HookLedOff(void);
void	AlarmLedOn(void);
void	AlarmLedOff(void);
void	FaxComLedOn(void);
void	FaxComLedOff(void);
void	ModeLedOn(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/*â∫ãLïœçX By M.Kotani 1998/03/18*/
/*#if defined(ANZU_L)*/
void	DensityLedOn(void);
#endif
#if (PRO_PANEL == KANJI)
void  DensityLedOn(void);
#endif
void	ReplacePaperLedOn(void);
void	ReplacePaperLedOff(void);
void	PaperJamLedOn(void);
void	PaperJamLedOff(void);
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/*â∫ãLïœçX By M.Kotani 1998/03/18*/
/*#if defined(ANZU_L)*/
void	PrinterAlarmLedOn(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/*â∫ãLïœçX By M.Kotani 1998/03/18*/
/*#if defined(ANZU_L)*/
void	PrinterAlarmLedOff(void);
#endif
void	StampLedOn(void);
void	StampLedOff(void);
#if (PRO_PANEL == ANK)
void	LED_Initial(void);
void	MemoryTxLedSet(void);
void	StampLedSet(void);
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
void	CopyModeLedOn(void);
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)
void	FaxModeLedOn(void);
#endif
void	AllLedOn(void);
void	AllLedOff(void);
void	OrderLedOn(UBYTE,UWORD);

#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1998/07/01 By M.Kuwahara */
void	ContrastLCD_Set(void);
UWORD	AD_XPS1(void);
UWORD	AD_XPS2(void);
UWORD	AD_XPB4(void);
UWORD	AD_DFD(void);
UWORD	AD_DFA4_B4(void);

#endif

#if (PRO_EXT_DMAC == DISABLE)
void DMA_DTC_RequestReqDisable(void);	/* 1997/12/16 Y.M */
void DMA_DTC_RequestReqEnable(void);	/* 1997/12/16 Y.M */
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/04/14 Eguchi */
void	SwitchLineToEngineBoard(void);
void	SwitchLineToFAX(void);
void	OnMML_Low(void);
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI)  || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
unsigned char  CutterPosition(void);
unsigned char  ThermalHeadMaker(void);
unsigned char  ThermalHeadRank(void);
unsigned char  Check_DTR(void);
unsigned char  PS1(void);
unsigned char  PS2(void);
unsigned char  PB4(void);
unsigned char  RY_BY(void);
unsigned char  RXIL(void);
unsigned char  CI(void);
void  Cutter1On(void);
void  Cutter1Off(void);
void  Cutter2On(void);
void  Cutter2Off(void);
void  DCD_On(void);
void  DCD_Off(void);
void  ClearModemRequestOn(void);
void  ClearModemRequestOff(void);
void  BuzzerOn(void);
void  BuzzerOff(void);
void  LcdDriverRegisterData(void);
void  LcdDriverRegisterIR(void);
void  LedPortSelect1On(void);
void  LedPortSelect1Off(void);
void  LedPortSelect2On(void);
void  LedPortSelect2Off(void);
void  PanelDataLoadOn(void);
void  PanelDataLoadOff(void);
void  LedPortSelect3On(void);
void  LedPortSelect3Off(void);
void  LcdDriverClockOn(void);
void  LcdDriverClockOff(void);
void  DSR_On(void);
void  DSR_Off(void);
void  SOH_RelayOn(void);
void  SOH_RelayOff(void);
void  CluchOn(void);
BOOL  CluchSetting(void);
void  CluchOff(void);
void  StartSendingMelodyToLine(void);
void  StopSendingMelodyToLine(void);
void  DensityLedOn(void);
unsigned short  AD_Battery(void);
unsigned short  AD_Thermistor(void);
unsigned short  AD_PS2(void);	/* ÇoÇrÇQ Ç`Å^Çcïœä∑ëŒâû By O.Kimoto 1999/03/29 */

#if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3)
UWORD	AD_PS1(void);	/* ÇoÇrÇP Ç`Å^Çcïœä∑ëŒâû By Y.Kano 2003/06/23 */
UWORD	AD_PB4(void);	/* ÇoÇaÇS Ç`Å^Çcïœä∑ëŒâû By Y.Kano 2003/06/23 */
#endif

#if defined(SATSUKI2) || defined(STOCKHM2)
UWORD   CutterSensor1(void);
UWORD   CutterSensor2(void);
UBYTE	EndMarkPS2Cehck(void);	/* ÉGÉìÉhÉ}Å[ÉNëŒâûÇoÇrÇQÉ`ÉFÉbÉN by Y.Kano 2003/10/23 */
/*void	CutterOn(void);*/
#endif

#if defined(STOCKHM2)
UWORD	AD_DFD(void);
UBYTE	RIBON(void);
UBYTE	CassettePaper(void);
void PrinterFPGA_Enable(void);
void PrinterFPGA_Disable(void);
#endif

unsigned char  CMN_ForcedDRAM_InitialKey(void);
 #if (PRO_CLASS1 == ENABLE)
	void RTS_Enable(void);
	void RTS_Disable(void);
	void CTS_IntEnable(void);
	void CTS_IntDisable(void);
 #endif
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By O.Kimoto 1998/08/28 */ /* Add by Y.Kano 2003/07/14 */
/************************************************************************
 * ÇhÅ^ÇnÇ…ä÷Ç∑ÇÈÉvÉçÉgÉ^ÉCÉv											*
 ************************************************************************/
/* I/OÇ©ÇÁÇÃì¸óÕ -------------------------------------------------------------------------------
extern UBYTE Input(*(volatile UBYTE *)addr);
extern UWORD InputWORD(*(volatile UWORD *)addr);
extern UDWORD InputDWORD(*(volatile UDWORD *)addr);
	Sample1: UBYTE a,*ap;	a = Input(addr);
	Sample2: UWORD b;	 	b = InputWORD(*(volatile UDWORD *)0x1234);
--------------------------------------------------------------------------------------------- */
/* ATTENTION ********
 *  if you want to use dummy read, you must set return value to a tempolary valiable.
 *  Input(IOPointer);               // It's BAD code
 *  UBYTE DummyStackValiable; DummyStackValiable = Input(IOPointer);  // Good
 */
#define	Input(Address)	((UBYTE)(*(Address)))
#define	InputWORD(Address)	((UWORD)(*(Address)))
#define	InputDWORD(Address)	((UDWORD)(*(Address)))
/* I/OÇ÷ÇÃèoóÕ -------------------------------------------------------------------------------
** extern void Output(*(volatile UBYTE *)addr, UBYTE Data);
** extern void OutputWORD(*(volatile UWORD *)addr, UWORD Data);
** extern void OutputDWORD(*(volatile UDWORD *)addr, UDWORD Data);
** 	Sample: UDWORD c;   OutputDWORD(0x100, c);
--------------------------------------------------------------------------------------------- */
#define	Output(Address, Data)	{*(Address) = (UBYTE)(Data);}
#define	OutputWORD(Address, Data)	{*(Address) = (UWORD)(Data);}
#define	OutputDWORD(Address, Data)	{*(Address) = (UDWORD)(Data);}
#endif


#if (PRO_ENERGY_SAVE == ENABLE) /* 2001/11/19 T.Takagi */
void 	HaltClockOn(void);
void 	HaltClockOff(void);
void	SubResetOff(void);
void	SubResetOn(void);
UBYTE	CheckCutting(void);
UBYTE	CheckLamp(void);
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
UBYTE	EcoModeOn(void);
 #if (1) /* ÉJÉoÅ[ÉIÅ[ÉvÉìÇ≈ÇQÇSÇuÇÇnÇmÇµÇ»Ç¢ÇÊÇ§Ç…Ç∑ÇÈ By M.Maeda 2003/01/22 */
UBYTE	EcoModeOff(UBYTE eco_off_mode);
 #else
//UBYTE	EcoModeOff(void);
 #endif
#endif

#if defined (KEISATSU) /* åxé@FAX 05/05/07 êŒã¥ê≥òa */
	BOOL CheckShireiInput(void);
	BOOL CheckScrambleSwOn(void);
	void SetDTC_IntFromModem(void);
	void SetDTC_IntFromS1(void);
	BOOL CheckS1Error(void);
#endif

#endif	/* End of File */

