/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : sys_pro.h                                                 */
/*  作成者       : 橘正樹                                                    */
/*  日  付       : 1997/05/17                                                */
/*  概  要       : フラッシュ書き換えシステム                                */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef SYS_PRO_H
 #define SYS_PRO_H	1

/* ini_cpu.c */
void InitializeCPU(void);
void InitializeInternalDevice(void);
void INI_Start10msTimer(void);
void INI_Stop10msTimer(void);
void InitializeSystem(void);

/* int_tim.c */
void INT_Timer10ms(void);

/* cmn_iorw.src */
void outp(UDWORD, UBYTE);
void outpw(UDWORD, UWORD);
void outpdw(UDWORD, UDWORD);
UBYTE inp(UDWORD);
UWORD inpw(UDWORD);
UDWORD inpdw(UDWORD);

/* cmn_io.c */
void IO_Port_Initialize(void);
void SpeakerMuteOn(void);
void SpeakerMuteOff(void);
void BuzzerVolumeControl(void);
void SpeakerOutBuzzer(void);

/* cmn_buzz.c */
void AckBuzzerSound(void);
void NackBuzzerSound(void);
void EndBuzzerSound(void);
void HoldAlarmSound(void);
void ErrorAlarmSound(void);
void ErrorEndlessAlarmSound(void);
void HungUpErrorAramSound(void);
void HoldEndBuzzerSound(void);
void BuzzerOnSetting(UWORD);
void BuzzerOffSetting(UWORD);
void wait_timer(UWORD);
void wait10ms_timer(void);
void  wait_timer2(UWORD wait_time);

/* scn_sub.c */
void SCN_Init(void);
void SCN_SetBuzzerFrequency(UBYTE);
void SCN_SetBuzzer(UBYTE);

/* opr_lcda.c */
void LCD_SoftWearTimer(UWORD);
void LCD_WriteInstruction(UBYTE);
void LCD_BusyFlagWait(UWORD);
void LCD_WriteData(UBYTE);
void WriteCGRAM(UBYTE *);
void LCD_Initialize(void);
void DisplayStringHigh(UBYTE, UBYTE *);
void DisplayStringLow(UBYTE, UBYTE *);
void CursorOn(UBYTE);
void CursorOff(void);
void DisplayChar(UBYTE, UBYTE);
void ClearDisplayHigh(void);
void ClearDisplayLow(void);

/* cmn_str.c */
UBYTE *CMN_MemorySetNULL(UBYTE *, UWORD, UBYTE);
UBYTE *CMN_StringCopy(UBYTE *,CONST UBYTE *);
UBYTE  CMN_StringLength(CONST UBYTE *);
void  CMN_StringReverse(UBYTE *);
void  CMN_HexToASC(UBYTE *, UDWORD, UBYTE);
void  CMN_UnsignedLongToASC_NULL(UBYTE *, UDWORD, UBYTE ,UBYTE);
void  CMN_UnsignedLongToASC(UBYTE *,UDWORD, UBYTE, UBYTE);

/* opr_lcdk.c */
void  LCD_Initialize(void);
void  DisplayString0(unsigned char  *string);
void  DisplayString1(unsigned char  *string);
void  DisplayStringAttribute(unsigned char  dsp_pos,unsigned char  *string,unsigned short  attr);
void  GetByteCharacterDotPattern(unsigned char  xc,unsigned char  yc,unsigned char  ascii,unsigned short  attr);
void  ClearDisplay(void);
void  LCD_RegisterSet(unsigned long  address,unsigned char  data);

#endif
