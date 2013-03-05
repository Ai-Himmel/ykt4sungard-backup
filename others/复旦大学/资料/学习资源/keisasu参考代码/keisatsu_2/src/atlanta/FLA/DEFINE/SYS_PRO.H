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

/* Fla_icpu.c */
void FLA_InitializeCPU(void);
void FLA_InitializeInternalDevice(void);
void FLA_INI_Start10msTimer(void);
void FLA_INI_Stop10msTimer(void);
void FLA_InitializeSystem(void);

/* Fla_itim.c */
void FLA_INT_Timer10ms(void);

/* cmn_iorw.src */
void FLA_outp(UDWORD, UBYTE);
void FLA_outpw(UDWORD, UWORD);
void FLA_outpdw(UDWORD, UDWORD);
UBYTE FLA_inp(UDWORD);
UWORD FLA_inpw(UDWORD);
UDWORD FLA_inpdw(UDWORD);

/* cmn_io.c */
void FLA_IO_Port_Initialize(void);
void FLA_SpeakerMuteOn(void);
void FLA_SpeakerMuteOff(void);
void FLA_BuzzerVolumeControl(void);
void FLA_SpeakerOutBuzzer(void);

/* cmn_buzz.c */
void FLA_AckBuzzerSound(void);
void FLA_NackBuzzerSound(void);
void FLA_EndBuzzerSound(void);
void FLA_HoldAlarmSound(void);
void FLA_ErrorAlarmSound(void);
void FLA_ErrorEndlessAlarmSound(void);
void FLA_HungUpErrorAramSound(void);
void FLA_HoldEndBuzzerSound(void);
void FLA_BuzzerOnSetting(UWORD);
void FLA_BuzzerOffSetting(UWORD);
void FLA_wait_timer(UWORD);
void FLA_wait10ms_timer(void);

/* scn_sub.c */
void FLA_SCN_Init(void);
void FLA_SCN_SetBuzzerFrequency(UBYTE);
void FLA_SCN_SetBuzzer(UBYTE);

/* opr_lcda.c */
void FLA_LCD_SoftWearTimer(UWORD);
void FLA_LCD_WriteInstruction(UBYTE);
void FLA_LCD_BusyFlagWait(UWORD);
void FLA_LCD_WriteData(UBYTE);
void FLA_WriteCGRAM(UBYTE *);
void FLA_LCD_Initialize(void);
void FLA_DisplayStringHigh(UBYTE, UBYTE *);
void FLA_DisplayStringLow(UBYTE, UBYTE *);
void FLA_CursorOn(UBYTE);
void FLA_CursorOff(void);
void FLA_DisplayChar(UBYTE, UBYTE);
void FLA_ClearDisplayHigh(void);
void FLA_ClearDisplayLow(void);

/* cmn_str.c */
UBYTE *FLA_CMN_MemorySetNULL(UBYTE *, UWORD, UBYTE);
UBYTE *FLA_CMN_StringCopy(UBYTE *,CONST UBYTE *);
UBYTE  FLA_CMN_StringLength(CONST UBYTE *);
void  FLA_CMN_StringReverse(UBYTE *);
void  FLA_CMN_HexToASC(UBYTE *, UDWORD, UBYTE);
void  FLA_CMN_UnsignedLongToASC_NULL(UBYTE *, UDWORD, UBYTE ,UBYTE);
void  FLA_CMN_UnsignedLongToASC(UBYTE *,UDWORD, UBYTE, UBYTE);

/* opr_lcdk.c */
void  FLA_LCD_Initialize(void);
void  FLA_DisplayString0(unsigned char  *string);
void  FLA_DisplayString1(unsigned char  *string);
void  FLA_DisplayStringAttribute(unsigned char  dsp_pos,unsigned char  *string,unsigned short  attr);
void  FLA_GetByteCharacterDotPattern(unsigned char  xc,unsigned char  yc,unsigned char  ascii,unsigned short  attr);
void  FLA_ClearDisplay(void);
void  FLA_LCD_RegisterSet(unsigned long  address,unsigned char  data);

#endif
