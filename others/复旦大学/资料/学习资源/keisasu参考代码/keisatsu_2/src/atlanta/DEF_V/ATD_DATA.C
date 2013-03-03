/* ANZU より移植 By Y.Suzuki 1996/10/11 */
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\atd_def.h"	/*	By Y.Suzuki 1996/10/16	*/

#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
UBYTE	CNG_StopFlagSram = 0;
#else
UBYTE	CNG_StopFlag = 0;
#endif

UBYTE	IsDialFirstNum = 0;			/*	ダイヤル送出時に１桁目を送出する事を判断するフラグ(ダイヤルパルスのみ)	*/

UBYTE	ATD_DSE1_Status = 0;				/*	ダイヤル送出前に現在の極性を記憶しておく変数	*/
UBYTE	ATD_DSE2_Status = 0;

/*(連続ﾄｰﾝ検出ﾀｽｸのみで使用)*/
UWORD	tskno_tone_timeup[CONTINUE_TONE_MAX] = {0xFFFF};	/*DT,D2T,CED,DIS,FNET*/
UWORD	tskno_filter1_off[CONTINUE_TONE_MAX] = {0xFFFF};	/*DT,D2T,CED,DIS,FNET*/
UWORD	tskno_filter2_off[CONTINUE_TONE_MAX] = {0xFFFF};	/*DT,D2T,CED,DIS,FNET*/
UWORD	tskno_filter3_off[CONTINUE_TONE_MAX] = {0xFFFF};	/*DT,D2T,CED,DIS,FNET*/

UWORD	tskno_ad_lc_timeup = 0xFFFF;
UWORD	tskno_ad_loop_current = 0xFFFF;

#if defined(FRA)
/* UWORD	tskno_after_rbt_timeup = 0xffff;*/
 UBYTE	tskno_after_rbt_timeup = 0xff;
#endif

UWORD	tskno_cng_detect = 0xFFFF;		/*Tel/Fax待機で使用*/
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
UWORD	tskno_busy_detect = 0xFFFF;		/* NTT Tel/Fax待機で使用 */
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
UWORD	tskno_busy_detect = 0xFFFF;
#endif
/* UWORD	tskno_cng_timeup = 0xFFFF;		/@Tel/Fax待機で使用*/
/* UWORD	tskno_cng_det_timeup = 0xFFFF;	/@Tel/Fax待機で使用*/
UBYTE	tskno_cng_timeup = 0xFF;		/*Tel/Fax待機で使用*/
UBYTE	tskno_cng_det_timeup = 0xFF;	/*Tel/Fax待機で使用*/

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* 1994/12/24 by M.HARADA *//* by K.Watanabe 2004/10/12 */
	UWORD	tskno_ATD_freq_check = 0xffff;
	UWORD	tskno_mercury		 = 0xffff;	/*MercuryToneDetect*/
/*	UWORD	tskno_mcry_timeup	 = 0xffff;	/@MercuryToneDetect*/
	UWORD	tskno_mcry_dt		 = 0xffff;	/*MercuryToneDetect*/
/*	UWORD	tskno_mcry_dt_timeup = 0xffff;	/@MercuryToneDetect*/
	UBYTE	tskno_mcry_dt_timeup = 0xff;	/*MercuryToneDetect*/
	UBYTE	tskno_mcry_timeup	 = 0xff;	/*MercuryToneDetect*/
#endif
#if (PRO_MODEM == ORANGE3)
UWORD	tskno_cng_freq_check = 0xFFFF;	/*Tel/Fax待機で使用*/
#endif

#if (PRO_SPEED_EX == ENABLE)
 UBYTE SpeedToneOrTimeUpFlag = 0;
#endif

/* For Debag '95.12.28 By T.Y */
UBYTE CNGPortStatus =0;
UWORD SpeedToneOnTime = 0;
UWORD SpeedStartOFFTime = 0;
UWORD SpeedOFFTime = 0;
UBYTE Spd_Debag_WriteRAM = 0;
UBYTE Spd_Debag_WriteRAM1 = 0;
UBYTE AtdToneDetectDebagRam = 0;

#if (PRO_SPEED_EX == ENABLE)
/*	指定周波数のﾄｰﾝが無いことを監視するﾀｽｸのIDを格納する変数 */
UWORD tskno_spd_filter1_off = 0;
UWORD tskno_spd_filter2_off = 0;
UWORD tskno_spd_filter3_off = 0;
UBYTE tskno_spd_tone_on_timeup = 0;
UBYTE tskno_spd_tone_timeup = 0;
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE)	/* 2000/10/18 H.Yoshikawa */
UWORD tskno_ATD_DialPulseTask = 0x0;
#endif
