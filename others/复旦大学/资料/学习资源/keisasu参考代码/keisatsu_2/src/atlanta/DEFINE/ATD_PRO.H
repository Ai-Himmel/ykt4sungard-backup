/*********************************************************************/
/*			 オートダイアラー(ATD) プロト・タイプ宣言				 */
/*																	 */
/*																	 */
/*							1996/11/06								 */
/*							 山口　哲治								 */
/*																	 */
/*********************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998 */
#include "\src\atlanta\define\cl1expro.h"
#endif
/*********************************************************************/
/* File : ATDFLTOF.C								   */
/*********************************************************************/
void	ATD_CheckFilterOffTask(struct	ToneDetectMailBoxData_t *);
/*********************************************************************/
/* File : ATDRELAY.C								   */
/*********************************************************************/
void	RelaySetting(void);
void	ATD_RelayOff(void);
/*********************************************************************/
/* File : ATD_MAIN.C								   */
/*********************************************************************/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UBYTE	AutoDial(UBYTE	*Buffer);
#endif
void	ToneDetectTaskInitial(void);
void 	ATD_BreakDTMF_Tx(void);		/* Ported from CLOVER by H.Kubo 1997/11/06 */
/*********************************************************************/
/* File : ATD_AFTN.C								   */
/*********************************************************************/
UBYTE	AfterDial_ToneDetect(void);
void	Del_AfterTone_Task(void);
/*********************************************************************/
/* File : ATD_D2T.C									  */
/*********************************************************************/
UBYTE	Dial2ndToneDetect(void);
void	Del_Dial2ndTone_Task(void);
/*********************************************************************/
/* File : ATD_DSE.C									  */
/*********************************************************************/
void	ATD_CheckDSETask(void);
/*********************************************************************/
/* File : ATD_DT.C									 */
/*********************************************************************/
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
UBYTE	DialToneDetect(UBYTE before_dial);
#else
UBYTE	DialToneDetect(void);
#endif
void	Del_DialTone_Task(void);
/*********************************************************************/
/* File : ATD_LC.C									 */
/*********************************************************************/
UBYTE	LoopCurrentCheck(UWORD	chk_time);
void	Del_LoopCurrentTask(void);
/*********************************************************************/
/* File : ATD_LCOF.C								   */
/*********************************************************************/
void	ATD_LC_OffCheckTask(void);
/*********************************************************************/
/* File : ATD_OUTD.C								   */
/*********************************************************************/
#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
void 	ATD_DialPulseTask(void);
void	ATD_StopDialPulse(void);
#endif
UBYTE	OutPutDial(UBYTE	Number);
UBYTE	AsciiToDialNumber(UBYTE Number);
/*********************************************************************/
/* File : ATD_STOP.C								   */
/*********************************************************************/
void	ATD_CheckStopTask(void);
/*********************************************************************/
/* File : ATD_TN.C									 */
/*********************************************************************/
void	ATD_ToneDetectPattern0Task(struct	ToneDetectMailBoxData_t	*);
void	ATD_ToneDetectPattern1Task(struct	ToneDetectMailBoxData_t	*);
void	ATD_ToneDetectPattern0Exit(void);
void	ATD_CheckToneTask(struct	ToneDetectMailBoxData_t	*);
void	ATD_WatchTimer10msEventTask(struct Timer10msEventData_t *);
void	Del_SPD_CheckFilterOffTask(UBYTE filter_type);
void	ATD_CheckToneExit(void);		/* 96/06/17 By T.Yamaguchi */

/* void		ATD_ToneDetectPattern1Exit(void);			*/
/*********************************************************************/
/* File : ATD_FREQ.C								   */
/*********************************************************************/
#if (PRO_MODEM == ORANGE3)
void	ATD_FilterOnOffDetectTask(UBYTE * ToneDetectType);
#endif

/*********************************************************************/
/* File : ATD_CNG.C									  */
/*********************************************************************/
UBYTE	CNG_ToneDetect(void);
void	CNG_ToneDetectTaskExit(void);
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
 UBYTE	Busy_ToneDetect(void);
#endif
/*********************************************************************/
/* File : ATDMCRYT.C												 */
/*********************************************************************/
void	MercuryToneDetect(void);
/* void		Del_Mercury_Tone_Task(void); 96/06/14 By T.Yamaguchi */
void	Del_Mercury_Tone_Task(void);
void	MercuryDial( UBYTE );
/* UBYTE			MercuryDial( UBYTE ); 96/06/14 By T.Yamaguchi */
void	Mercury_DialToneDetect(void);
void	Del_Mcry_DialTone_Task(void);

