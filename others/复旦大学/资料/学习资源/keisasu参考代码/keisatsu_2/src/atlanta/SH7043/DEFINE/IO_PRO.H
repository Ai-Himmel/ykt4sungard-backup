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
#include "\src\atlanta\define\product.h"

/* ÇrÇ`ÇjÇ`ÇjÇhÅ^ÇgÇhÇmÇnÇjÇhà»ç~ÇÃã@éÌÇÕÅAÉ}ÉXÉNÉvÉçÉOÉâÉÄïœçX
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#else

#ifndef	IO_PRO_H
	#define	IO_PRO_H	1

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif

/* CPUå≈óL & ã@éÌã§í  */
UWORD	CMN_CheckSH_WCR1_CS3(void);
void	CMN_SetSH_WCR1_CS3(UWORD wait);

/* ã@éÌå≈óL */
/* SATSUKI2ópí«â¡ start by Y.Kano 2003/06/24 */
#if defined(SATSUKI2) || defined(STOCKHM2)
UWORD   CutterSensor1(void);
UWORD   CutterSensor2(void);

UWORD	AD_PS1(void);	/* ÇoÇrÇP Ç`Å^Çcïœä∑ëŒâû By Y.Kano 2003/06/23 */
UWORD	AD_PB4(void);	/* ÇoÇaÇS Ç`Å^Çcïœä∑ëŒâû By Y.Kano 2003/06/23 */

UWORD	AD_PS2(void);	/* Added by SMuratec K.W.Q 2003/07/24 */

/*void	CutterOn(void);*/
#endif

#if defined(STOCKHM2)
UWORD	AD_DFD(void);
UBYTE	RIBON(void);
#endif

/* SATSUKI2ópí«â¡ end   by Y.Kano 2003/06/24 */
UBYTE	OffHook1(void);
UBYTE	OffHook2(void);
#if defined (KEISATSU) /* Modify by SMuratec óõ 2005/06/24 */
UBYTE	OffHook3(void);
UBYTE	CheckShireiOn(void); /* Added by SMuratec óõ 2005/06/28 */
UBYTE 	HDST_RelaySetting(void);
void	HDST_RelayOn(void);
void	HDST_RelayOff(void);
UBYTE 	ModemRelaySetting(void);
UBYTE 	Is_HDST_Disable(void);
#endif /* defined (KEISATSU) */
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
UBYTE	PREQ(void);
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
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/13 */
void	NoRingRelayOnTel1(void);
#endif
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
#if defined (KEISATSU) /* åxé@FAX Modify by SMuratec óõ 2005/07/28 */
void HDST_Disable(void);
void HDST_Enable(void);
#endif /* defined (KEISATSU) */
#if defined (KEISATSU)		/* åxé@FAX Added DVT_ID15 by SMuratec K.W.Q 2005/11/05 */
void	Keisatsu_L_RelayOn(void);
void	Keisatsu_L_RelayOff(void);
#endif		/* End of (defined (KEISATSU)) */
void	DP_RelayOn(void);
void	DP_RelayOff(void);
void	CONT_24V_On(void);
void	CONT_24V_Off(void);
void	TonerSave(UBYTE);
void	PACK_High(void);
void	PACK_Low(void);
#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)
void	SetDICPU_Disable(void);
void	SetDICPU_Enable(void);
#endif

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
void 	CMN_ND_SetReset(void);

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

#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* by H.Kubo 1998/10/27 */
void DMA_DTC_MaskEnable(UBYTE channel);
void DMA_DTC_MaskDisable(UBYTE channel);
#endif


#if defined(POPLAR_F)
void	SelectDreqDirection(UBYTE direction);
void	SetModemDMA_DirectionTx(void);
void	SetModemDMA_DirectionRx(void);
void	SetDICPU_Disable(void);
void	SetDICPU_Enable(void);
UBYTE	NAR(void);
void	CMN_SetFraseAnswerLSI(UWORD frase);
void	CMN_AnswerLSIOn(void);
void	CMN_AnswerLSIOff(void);
void	CMN_ResetOnAnswerLSI(void);
void	CMN_ResetOffAnswerLSI(void);
void	SelectVOL(void);
void	SelectMELorTX(void);
void	SelectTHMOn(void);
void	SelectTHMOff(void);
void	SelectMELOn(void);
void	SelectMELOff(void);
void	StartSendingMelodyToLine(void);
void	StopSendingMelodyToLine(void);
UWORD	AD_MachineTemp(void);

#endif

/*-----------------------------------------------------------
** V851 è»ÉGÉlä÷òAí«â¡ By Y.Suzuki 2002/06/07
*/
#if (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/07 */
void PSRESET(UWORD is_enable);
void CLKCON(UWORD is_enable);
void PCON(UWORD is_enable);
/*-----------------------------------------------------------
** V851 DRAMÅ@BACKUPä÷òAí«â¡ By Y.Suzuki 2002/06/11
*/
void BatteryChargeOn(void);
void BatteryChargeOff(void);
/*-----------------------------------------------------------
** V851 FANêßå‰ä÷òAí«â¡ By Y.Suzuki 2002/06/13
*/
UWORD	AD_MachineTemp(void);
/**void	SelectMachineTempOn(void);
**void	SelectEnvironmentTempOn(void);**/
void	SelectTHMOn(void);
void	SelectTHMOff(void);

void	ChkFanMotorLock(void);		/*V851 ã@ì‡FAN¥◊∞í≤ç∏By Y.Suzuki 2002/09/11*/
void	ChkFanMotorLockClear(void);	/*V851 ã@ì‡FAN¥◊∞í≤ç∏By Y.Suzuki 2002/09/21*/
UBYTE	CMN_ForcedStackCopyKey(void);/* ÉãÅ[Éví≤ç∏ By Y.Suzuki 2003/06/19*/
#endif


#endif	/* End of File */

#endif
