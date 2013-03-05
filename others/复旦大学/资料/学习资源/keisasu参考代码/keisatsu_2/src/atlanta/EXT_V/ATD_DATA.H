/*	By Y.Suzuki 1996/10/12	*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\atd_def.h"
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include	"\src\atlanta\define\cl1expro.h"
#endif


#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui Jun.19,1998  */
extern UBYTE	CNG_StopFlag;
#endif
extern UBYTE	IsDialFirstNum;			/*	ダイヤル送出時に１桁目を送出する事を判断するフラグ(ダイヤルパルスのみ)	*/
extern UBYTE	ATD_DSE1_Status;				/*	ダイヤル送出前に現在の極性を記憶しておく変数	*/
extern UBYTE	ATD_DSE2_Status;


/*(連続ﾄｰﾝ検出ﾀｽｸのみで使用)*/
extern UWORD	tskno_tone_timeup[CONTINUE_TONE_MAX];	/*DT,D2T,CED,DIS,FNET,(MCRY)*/
extern UWORD	tskno_filter1_off[CONTINUE_TONE_MAX];	/*DT,D2T,CED,DIS,FNET,(MCRY)*/
extern UWORD	tskno_filter2_off[CONTINUE_TONE_MAX];	/*DT,D2T,CED,DIS,FNET,(MCRY)*/
extern UWORD	tskno_filter3_off[CONTINUE_TONE_MAX];	/*DT,D2T,CED,DIS,FNET,(MCRY)*/

extern UWORD	tskno_ad_lc_timeup;
extern UWORD	tskno_ad_loop_current;

#if defined(FRA)
 extern UBYTE	tskno_after_rbt_timeup;
/* extern UWORD	tskno_after_rbt_timeup;	*/
#endif

extern UWORD	tskno_cng_detect;		/*Tel/Fax待機で使用*/
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
extern UWORD	tskno_busy_detect;		/* NTT Tel/Fax待機で使用 */
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
extern UWORD	tskno_busy_detect;
#endif
/* extern UWORD	tskno_cng_timeup;		/@Tel/Fax待機で使用*/
/* extern UWORD	tskno_cng_det_timeup;	/@Tel/Fax待機で使用*/
extern UBYTE	tskno_cng_timeup;		/*Tel/Fax待機で使用*/
extern UBYTE	tskno_cng_det_timeup;	/*Tel/Fax待機で使用*/

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1994/12/24 by M.HARADA *//* by K.Watanabe 2004/10/12 */
	extern UWORD	tskno_ATD_freq_check;
	extern UWORD	tskno_mercury;			/*MercuryToneDetect*/
/*	extern UWORD	tskno_mcry_timeup;		/@MercuryToneDetect*/
	extern UWORD	tskno_mcry_dt;			/*MercuryToneDetect*/
/*	extern UWORD	tskno_mcry_dt_timeup;	/@MercuryToneDetect*/
	extern UBYTE	tskno_mcry_dt_timeup;	/*MercuryToneDetect*/
	extern UBYTE	tskno_mcry_timeup;		/*MercuryToneDetect*/
#endif
#if (PRO_MODEM == ORANGE3)
extern UWORD	tskno_cng_freq_check;	/*Tel/Fax待機で使用*/
#endif

#if (PRO_SPEED_EX == ENABLE)
 extern UBYTE SpeedToneOrTimeUpFlag;
#endif

/* For Debag '95.12.28 By T.Y */
extern UBYTE CNGPortStatus;
extern UWORD SpeedToneOnTime;
extern UWORD SpeedStartOFFTime;
extern UWORD SpeedOFFTime;
extern UBYTE Spd_Debag_WriteRAM;
extern UBYTE Spd_Debag_WriteRAM1;
extern UBYTE AtdToneDetectDebagRam;

#if (PRO_SPEED_EX == ENABLE)
/*	指定周波数のﾄｰﾝが無いことを監視するﾀｽｸのIDを格納する変数 */
extern	UWORD tskno_spd_filter1_off;
extern	UWORD tskno_spd_filter2_off;
extern	UWORD tskno_spd_filter3_off;
extern	UBYTE tskno_spd_tone_on_timeup;
extern	UBYTE tskno_spd_tone_timeup;
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE)	/* 2000/10/18 H.Yoshikawa */
extern UWORD tskno_ATD_DialPulseTask;
#endif
