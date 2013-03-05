/*	By Y.Suzuki 1996/10/21	*/
/* Original File : jun\usr1:\src\ichou\ext_v\atd_tbl.h */
#include "\src\atlanta\define\atd_def.h"

extern struct DialParameters_t DialTable[];

extern struct ToneParameters_t DialTone[];
extern struct ToneParameters_t Dial2ndTone[];
extern struct ToneParameters_t BusyTone[];
extern struct ToneParameters_t CongestionTone[];
extern struct ToneParameters_t CNG_Tone;
extern struct ToneParameters_t CNG_Tone1;
/*#if defined(POPLAR_F)*//* 2000/02/22 Y.Murata */
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* ANS/FAX待機時の、CNG検出のﾚﾍﾞﾙを上げる */
extern struct ToneParameters_t CNG_Tone2;
#endif
extern struct ToneParameters_t CED_Tone;
extern struct ToneParameters_t DIS_Tone;
extern struct ToneParameters_t MercuryTone;
extern struct ToneParameters_t F_Net_Tone;
extern struct ToneParameters_t SPD_Tone[];
extern struct ToneParameters_t Mode_CNG_Tone;
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
extern struct ToneParameters_t PhaseB1_Busy;
extern struct ToneParameters_t VoiceCNG_Tone;
#endif
/* #if defined(POPLAR_F) *//* 2000/02/02 Y.Murata */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
extern struct ToneParameters_t PhaseA1_Busy;
 #endif
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
extern struct ToneParameters_t PhaseA1_Busy;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)
 #if (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23)
extern CONST struct ToneParameters_t V23_Tone;
 #endif
#endif

#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
extern CONST struct ToneParameters_t PBX_Tone;
#endif

extern UBYTE SpeedHandshakeValiableData;

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
extern CONST struct ATD_Prefix_t ATD_PrefixTable[];
#endif
