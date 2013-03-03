/*	By Y.Suzuki 1996/10/16	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\atd_def.h */
#ifndef atd_def_h
	#define atd_def_h
/**********************************************************************
*				BY:	 A.Okumura
*			  DATE:	 Wed 17 Nov 1993
*		 FILE NAME:	 dialer.h
*	   DESCRIPTION:	 ﾀﾞｲｱﾗｰ用定義ファイル
**********************************************************************@H*/

/***********************************************************************
*		   BY:	 A.Okumura
*		 DATE:	 Wed 17 Nov 1993
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 ｵｰﾄﾀﾞｲｱﾗｰのﾘﾀｰﾝ値
************************************************************************/
#define		AD_OK				0
#define		AD_LOCAL_BUSY		1		/*発着衝突があった*/
#define		AD_REMOTE_BUSY		2		/*ﾋﾞｼﾞｰﾄｰﾝ､ｺﾝｼﾞｪｽｼｮﾝﾄｰﾝを検出した*/
#define		AD_STOPPED			3		/*ｽﾄｯﾌﾟ･ｷｰが押された*/
#define		AD_DESTROYED		4		/*ﾊﾞｯﾌｧのﾀﾞｲｱﾙﾃﾞｰﾀが壊れている*/
#define		AD_OK_DSE			5		/*極反検出した*/
#define		AD_DIAL_EMPTY		6		/*ﾊﾞｯﾌｧにﾀﾞｲｱﾙﾃﾞｰﾀが登録されていない*/
#define		AD_TIME_OVER		7		/*制限時間内にﾄｰﾝが検出できなかった*/
#define		AD_NO_DIAL_TONE		8		/*ﾀﾞｲｱﾙﾄｰﾝを検出できない*/
#define		AD_NO_CURRENT_LOOP	9		/*ﾙｰﾌﾟ電流が無い*/
#define		AD_DETECT_RINGBACKTONE	10
#define		AD_OK_CED			11		/* CED検出 for FRA	95/03/17 by M.HARADA */
#if (PRO_SPEED_EX == ENABLE)
	#define	AD_OK_SPD_TONE		12		/* 短縮ﾊﾝﾄﾞｼｪｰｸ（海外用）着信ﾄｰﾝ検出した */
#endif
#define		AD_OK_DIS			13
#if (PRO_TX_SPEED == V34) /* Ported from \src\clover\src\atd_def.h and modified by H.Kubo 1997/07/22 */
#define		AD_OK_ANSWER_TONE		14		/* V25ｱﾝｻｰﾄｰﾝ検出 */
#define		AD_NOT_YET_DETECTED		0xff 	/* 未検出状態 */
#endif /* (PRO_TX_SPEED == V34) */
/***********************************************************************
*		   BY:	 A.Okumura
*		 DATE:	 Wed 17 Nov 1993
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 ｵｰﾄﾀﾞｲｱﾗｰのﾒｯｾｰｼﾞ
************************************************************************/
#define		DIALTONE			0
#define		DIAL2TONE			1
#define		CED_TONE			2
#define		DIS_TONE			3
#define		F_NET_TONE			4
#define		MERCURY_TONE		5		/* 1996/12/12  By T.Yamaguchi 18 -> 5 */
#define		BUSYTONE			5
#define		CONTONE				6
#define		CNG_TONE			7
#define		CNG_TONE1			8
#define		V23_TONE			9		/* For (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23). added by H.Kubo 1998/08/12 */

#define		MSG_DETECT_DSE			9		/*極性反転を検出した*/
#define		MSG_DETECT_STOP			10		/*ｽﾄｯﾌﾟ･ｷｰが押された*/
#define		MSG_DETECT_LC_OFF		11		/*ﾙｰﾌﾟ電流が無い*/

#define		MSG_DETECT_FILTER_ON	12		/*指定周波数のﾄｰﾝが来た*/
#define		MSG_DETECT_FILTER_OFF	13		/*指定周波数のﾄｰﾝが来ない*/

#define		TIMEUP				14		/*制限時間を超過した*/
#define		TIMEUP_CNGOFF		15		/*CNGを停止する制限時間を超過した*/
#define		TIMEUP_TONE0		16		/*ﾄｰﾝ検出を続行する制限時間を超過した*/

#define		SOMETHING			17		/**/
/* #define		MERCURY_TONE		18		/@ 1994.12.2 by M.H.  GBRのみの為、特殊使用します　by A.O*/
#define		MSG_TIMEUP_AFTER_RBT	19		/* 1995.01.20 by M.HARASA FRAのみの使用　*/

#if (PRO_SPEED_EX == ENABLE)
 #define	SPD_TONE			20		/* 短縮ﾊﾝﾄﾞｼｪｰｸ（海外用）着信ﾄｰﾝ */
#endif
#define		DET_TIMEUP			21		/* CNG検出中のﾀｲﾑｱｯﾌﾟ */
#define		EOM_TONE			22		/* 96/05/22 By T.Yamaguchi */
#define		MODE_CNG_TONE		23		/* 96/05/22 By T.Yamaguchi */
#define		MODE_CHANGE_CNG_DETECT	24	/* 96/05/29 */

#define 	MSG_DETECT_V25_ANSWER_TONE 25 /* 97/07/22 by H.Kubo for V8/V34*/

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
 #define	PHB1_BUSY			26		/* for NTT */
 #define 	CNG_BUSY_DETECT		27		/* for NTT */
 #define	FSK_OR_BUSY_DETECT	28		/* for NTT */
 #define	BUSY_DETECT_STOP	29		/* for NTT */
 /* #if defined(POPLAR_F) */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/05 */
 #define	PHA1_BUSY			30		/* for NTT *//* 2000/02/02 Y.Murata */
 #endif
#endif

#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
 #define	PHA1_BUSY			30		/* for NTT */
#endif

#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
#define		PBXTONE				31
#endif

/* #define		CONTINUE_TONE_MAX	5		/@DT,D2T,CED,DIS,FNET(合計5)*/
#define		CONTINUE_TONE_MAX	6		/*DT,D2T,CED,DIS,FNET,MERCURY(合計6) 1996/12/12	 By T.Yamaguchi */
#define		MAX_TONETYPE		8		/*DT,BT,CT,D2T,DIS,CED,CNG,FNET(合計7)*/
/***********************************************************************
*		   BY:	 A.Okumura
*		 DATE:	 Wed 7 Dec 1993
*		 TYPE:	 STRUCT DEFINE
* VAR TO HOLD:	 ﾊﾟﾗﾒｰﾀｰ
************************************************************************/
struct	ToneDetectMailBoxData_t	{
	WORD			SendMBX;
	WORD			ToneType;
};
/***********************************************************************
*		   BY:	 A.Okumura
*		 DATE:	 Wed 7 Dec 1993
*		 TYPE:	 DEFINE ( ONLY ORANGE3 MODEM )
* VAR TO HOLD:	 ATD_FilterOnOffDetectTask に渡すﾊﾟﾗﾒｰﾀ
************************************************************************/
/* #if (PRO_MODEM == ORANGE3) */ /* Not only for ORANGE3, also for R288F. by H.Kubo 1997/07/23 */
#define	BEFORE_DIAL_DETECT	0
#define	AFTER_DIAL_DETECT	1
#define	CNG_DETECT			2
#define	DIAL2TONE_DETECT	3
#define	F_NET_TONE_DETECT	4
#define	MERCURY_DETECT		5
#define ANS_FAX_CNG_DETECT	6
/* #endif */
/***********************************************************************
*		   BY:	 T.Yamaguchi
*		 DATE:	 The 25 Jan 1996
*		 TYPE:	 DEFINE ( ONLY SPEED_EX )
* VAR TO HOLD:	 ATD_CheckToneTask に渡すﾊﾟﾗﾒｰﾀ
************************************************************************/
#if (PRO_SPEED_EX == ENABLE)
#define SPD_NOT_DETECT	0
#define SPD_DETECT_OK	1
#endif
/***********************************************************************
*		   BY:	 A.Okumura
*		 DATE:	 Wed 17 Nov 1993
*		 TYPE:	 STRUCT DEFINE
* VAR TO HOLD:	 ﾀﾞｲｱﾙ送出時のﾊﾟﾗﾒｰﾀｰ
************************************************************************/
struct	DialParameters_t	{
	UWORD		PrePause;
	UWORD		Make10;
	UWORD		Make20;
	UWORD		MakeDTMF;
	UWORD		BreakDTMF;
	UBYTE		LevelDTMF;
	UWORD		S_RelayOffTime;
	UWORD		S_RelayOnTime;
	UWORD		MiniPause10;
	UWORD		MiniPause20;
	UBYTE		DialType;
	UBYTE		FlashTime;		/* 1996/07/08 By N.Sakamoto */
};
/***********************************************************************
*		   BY:	 A.Okumura
*		 DATE:	 Wed 17 Nov 1993
*		 TYPE:	 STRUCT DEFINE
* VAR TO HOLD:	 ﾄｰﾝ検出時のﾊﾟﾗﾒｰﾀｰ
************************************************************************/
struct ToneParameters_t {
	UBYTE		FilterType;
	UBYTE		MaxFrequency;
	UBYTE		MinFrequency;
	UBYTE		MaxLevel;
	UBYTE		MinLevel;
	UBYTE		DetectCycle;
	UWORD		MaxDetectTime;
	UWORD		MaxOnTime[3];
	UWORD		MinOnTime[3];
	UWORD		MaxOffTime[3];
	UWORD		MinOffTime[3];
	UWORD		MaxNoiseTime;
	UWORD		MaxCutTime;
	UBYTE		TonePattern;
};

/***********************************************************************
*		   BY:	 harada
*		 DATE:	 '94.3.15
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 FaxTelAutoSwitchのﾘﾀｰﾝ値
************************************************************************/
#define	TONE_DET_TIMEUP		0
#define	TONE_DET_OK			1
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
#define	TONE_DET_BUSY		2
#endif
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
#define	TONE_DET_BUSY		2

/***********************************************************************
*		   BY:	 T.Yamaguchi
*		 DATE:	 1998/03/11
*		 TYPE:	 DEFINE
* VAR TO HOLD:	 Busy_ToneDetectのﾘﾀｰﾝ値
************************************************************************/
#define	DETECT_TIMEUP		0
#define	BUSY_TONE_DET_OK	1
#define TONE_FLAG_DETECT	2
#endif

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/*----------------------------------*/
/*	MercuryTone検出時間の初期値		*/
/*	94/11/17   by M.HARADA			*/
/*----------------------------------*/
 #define MCRY_PAUSE_1ST_DATA	5
#endif

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
struct	ATD_Prefix_t {
	UBYTE	SrcDial[10];
	UBYTE	DelCount;
	UBYTE	AddDial[10];
	UBYTE	IsAreaCode;
};
#endif

#if defined(STOCKHM2) || defined(HINOKI3) || defined(KEISATSU)	/* 内線トーン検出 by Y.kano 2004/10/27 */ /* Add by Y.kano 2004/11/25 */
 #if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
#define NOT_BEFORE_DIAL			0	/* 今から行うダイヤルトーンの検出はダイヤル前のトーン検出じゃない */
#define BEFORE_DIAL				1	/* 今から行うダイヤルトーンの検出はダイヤル前のトーン検出だ */
 #endif
#endif

#endif
