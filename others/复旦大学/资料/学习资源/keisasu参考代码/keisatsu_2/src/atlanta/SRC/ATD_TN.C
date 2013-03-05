/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANT																		*/
/*		ﾓｼﾞｭｰﾙ	:void	ATD_ToneDetectPattern0Task(struct *)							*/
/*				:void	ATD_ToneDetectPattern1Task(struct *)							*/
/*				:void	ATD_ToneDetectPattern0Exit(void)								*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_TN.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mon_pro.h"	/*	モニタコール */
#include	"\src\atlanta\define\man_pro.h"	/*	SYS_FaxComStopSwitch()	*/
#include	"\src\atlanta\define\ctry_pro.h"	/* CTRY_?Tone() */
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"

#if (PRO_SPEED_EX == ENABLE)
 #include	"\src\atlanta\define\uni_pro.h"
#endif

#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\ext_v\atd_tbl.h"
#include	"\src\atlanta\ext_v\atd_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"	/* SYS_GeneralTimer	,SYS_RingToneStopFlag */

#include	"\src\atlanta\sh7043\define\def_evtn.h" /* By S.Kawasaki 1996/03/07 */
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include	"\src\atlanta\sh7043\define\def_tib.h"

#if defined(GBR)
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#endif

MESSAGE_t		ToneDetectMessage = {0};		/*	ｽﾀｯｸを減らすために内部変数から大域に変更 1994/10/25 by A.O	*/

/* ファネット指摘項目(No.10)
** TEL/FAX待機にしておき、受信させる（送信側は自動送信）
** ８回線交換機を使うとCNG検出がNGとなり、電話呼び出しが始まる。。。
** L-410でも同様な不具合で対策をしているのでそれをフィードバックする。
** by O.Kimoto 2002/11/01
*/
#define RBT_STOP_CNG_DETECT		0x01
#define RBT_STOP_PHA1_BUSY		0x02
#define RBT_STOP_PHB1_BUSY		0x04

/*--------------------------------------------------------------------------------------------------------------------------*/
/* < ToneType >																												*/
/* DIALTONE:0, DIAL2TONE:1, CED_TONE:2, DIS_TONE:3, F_NET_TONE:4, BUSYTONE:5, CONTONE:6, CNG_TONE:7, PBXTONE:12				*/
/* この値をCNG_StopFlagにｾｯﾄして区別する																					*/
/*																															*/
/* 理由：ON(連続)ﾊﾟﾀｰﾝのﾄｰﾝ検出ﾀｽｸで検出するﾄｰﾝは																			*/
/*		 <DIALTONE,DIAL2TONE,CED_TONE,DIS_TONE,F_NET_TONE>の5種類しか無いため												*/
/*		 tskno_filter?_off[]の配列領域が無駄になるから																		*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/*************************************************************************
	module		:[連続（ＯＮ）パターンのトーン検出（タスク）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[ATD]
	date		:[1994/03/04]
	author		:[奥村明]
*************************************************************************/
void	ATD_ToneDetectPattern0Task(struct ToneDetectMailBoxData_t	*MessageP)
{
	MESSAGE_t		*tone_receive;				/*	受信メッセージを格納する変数	*/

	UWORD StartOffTime = 0;	/*	指定周波数のトーンが（ＯＮ－＞ＯＦＦ）に変わった時点のタイマー値をセット	*/
	UWORD OffTime = 0;		/*	指定周波数のトーンが（ＯＮ－＞ＯＦＦ）に変わってから（ＯＦＦ－＞ＯＮ）に戻るまでの時間	*/
	UBYTE	i = 0;			/*	ループ変数	*/

	struct	ToneParameters_t	*ToneTable;	/*	トーンテーブル	*/
	struct	Timer10msData_t	TimeUpTone;
	struct	ToneDetectMailBoxData_t	SendMessageValue;

	WORD tone_type = 0;

	SendMessageValue.ToneType = MessageP->ToneType;				/*	検出するトーンの種類を指定	*/
	SendMessageValue.SendMBX  = mbxno.Tone[MessageP->ToneType];	/*	メッセージを送るメイルボックスを指定	*/

	/*	指定周波数のﾄｰﾝが無いことを監視するﾀｽｸのIDを格納する変数 */
	tskno_filter1_off[MessageP->ToneType] = 0xFFFF;
	tskno_filter2_off[MessageP->ToneType] = 0xFFFF;
	tskno_filter3_off[MessageP->ToneType] = 0xFFFF;
	tskno_tone_timeup[MessageP->ToneType] = 0xFFFF;

	AtdToneDetectDebagRam = 0;	/* for Debag 96.02.07 By t.y */

	/*----------------------------*/
	/**ﾄｰﾝﾃｰﾌﾞﾙをｾｯﾄ、ﾒｲﾙﾎﾞｯｸｽ生成*/
	/*----------------------------*/
	switch(MessageP->ToneType) {
	case DIALTONE:
		ToneTable = (struct ToneParameters_t *)CTRY_DialTone();
		break;
	case DIAL2TONE:
		ToneTable = (struct ToneParameters_t *)CTRY_Dial2ndTone();
		break;
	case CED_TONE:
		ToneTable = &CED_Tone;
		break;
	case DIS_TONE:
		ToneTable = &DIS_Tone;
		break;
	case F_NET_TONE:
		ToneTable = &F_Net_Tone;
		break;
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	case MERCURY_TONE:					/* 1994.12.2 by M.H. */
		ToneTable = &MercuryTone;
		break;
#endif
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* added by H.Kubo 1998/01/05 for a test*/
	case CNG_TONE: /* CNG 検出レベル調整のために追加。*/
		ToneTable = &CNG_Tone;
		break;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/12 */
 #if (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23) 
	case V23_TONE: 
		ToneTable = &V23_Tone;
		break;
 #endif
#endif
	default:
		/*ここに来たらバグ*/
		break;
	}

	/*-------*/
	/*ﾄｰﾝ検出*/
	/*-------*/
	for(;;) {
		/*------------------------------------------*/
		/**	指定範囲のトーン周波数が来るまで待つ	*/
		/*------------------------------------------*/
		switch (ToneTable->FilterType) {
		case 1:
			wai_evt(EVT_TONE_FILTER1_ON);
			cre_tsk(&tskno_filter1_off[MessageP->ToneType], TSK_ATD_CHECKFILTER1OFFTASK, &SendMessageValue);
			break;
		case 2:
			wai_evt(EVT_TONE_FILTER2_ON);
			cre_tsk(&tskno_filter2_off[MessageP->ToneType], TSK_ATD_CHECKFILTER2OFFTASK, &SendMessageValue);
			break;
		case 3:
			wai_evt(EVT_TONE_FILTER3_ON);
			cre_tsk(&tskno_filter3_off[MessageP->ToneType], TSK_ATD_CHECKFILTER3OFFTASK, &SendMessageValue);
			break;
		default:
			break;		/* ここに来たらバグ 96/06/17 */
		}

		/*----------------------------------*/
		/*ﾄｰﾝが入って来たのでCNG送出を止める*/
		/*----------------------------------*/
		/*CNG_StopFlag |= (0x01 << MessageP->ToneType);*/
		CNG_StopFlag |= 0x00;	/* '96.03.06 By T.Y for Debag */

		/*------------------------*/
		/*ﾄｰﾝがOFF～ONに変わった時*/
		/*------------------------*/
		if (StartOffTime != 0) {
			AtdToneDetectDebagRam++ ;
			OffTime = (UWORD)(SYS_GeneralTimer - StartOffTime);
			if (OffTime > ToneTable->MaxCutTime) {	/*瞬断でない時*/
				StartOffTime = 0;
				/*-----------------*/
				/*CNG送出を止めない*/
				/*-----------------*/
				/*CNG_StopFlag &= ~(0x01 << MessageP->ToneType);*/
				/*---------------------------*/
				/*自タスクで生成したﾀｽｸを削除*/
				/*---------------------------*/
				switch (ToneTable->FilterType) {
				case 1:
					if (tskno_filter1_off[MessageP->ToneType] != 0xFFFF) {
						del_tsk(&tskno_filter1_off[MessageP->ToneType]);
					}
					break;
				case 2:
					if (tskno_filter2_off[MessageP->ToneType] != 0xFFFF) {
						del_tsk(&tskno_filter2_off[MessageP->ToneType]);
					}
					break;
				case 3:
					if (tskno_filter3_off[MessageP->ToneType] != 0xFFFF) {
						del_tsk(&tskno_filter3_off[MessageP->ToneType]);
					}
					break;
				}
				if (tskno_tone_timeup[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_tone_timeup[MessageP->ToneType]);
				}
				/*------------*/
				/*検出やり直し*/
				/*------------*/
				continue;
			}
		}
		else {
			/*----------------------------------------------------*/
			/**指定周波数のトーンがＯＮになった時点でﾀｲﾏｰﾀｽｸを生成*/
			/*----------------------------------------------------*/
			TimeUpTone.Time = ToneTable->MinOnTime[0];
			TimeUpTone.ReturnValue = TIMEUP;
			TimeUpTone.SendMBX = mbxno.Tone[MessageP->ToneType];
			cre_tsk(&tskno_tone_timeup[MessageP->ToneType], TSK_CMN_MAN_TIMER10MSTASK, &TimeUpTone);
		}
		/*-------------------------------*/
		/*ﾄｰﾝ検出用ﾒｲﾙﾎﾞｯｸｽからﾒｯｾｰｼﾞ受信*/
		/*-------------------------------*/
		rcv_msg(mbxno.Tone[MessageP->ToneType], &tone_receive);
		/*------------------*/
		/*ﾒｯｾｰｼﾞに対する処理*/
		/*------------------*/
		if (tone_receive->Message == TIMEUP) {
			/*------------------------------*/
			/*	自タスクで生成したﾀｽｸを削除	*/
			/*------------------------------*/
			switch (ToneTable->FilterType) {
			case 1:
				if (tskno_filter1_off[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_filter1_off[MessageP->ToneType]);
				}
				break;
			case 2:
				if (tskno_filter2_off[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_filter2_off[MessageP->ToneType]);
				}
				break;
			case 3:
				if (tskno_filter3_off[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_filter3_off[MessageP->ToneType]);
				}
				break;
			}
			if (tskno_tone_timeup[MessageP->ToneType] != 0xFFFF) {
				del_tsk(&tskno_tone_timeup[MessageP->ToneType]);
			}
			/*----------*/
			/*ﾒｯｾｰｼﾞ送信*/
			/*----------*/
			ToneDetectMessage.Item = FROM_AUTODIAL;
			ToneDetectMessage.Message = MessageP->ToneType;
			snd_msg(MessageP->SendMBX, &ToneDetectMessage);
			wai_tsk(0xFFFF);
		}
		else if (tone_receive->Message == MSG_DETECT_FILTER_OFF) {
			StartOffTime = SYS_GeneralTimer;
			/*------------------------------------*/
			/*２重生成しないように一旦削除しておく*/
			/*------------------------------------*/
			switch (ToneTable->FilterType) {
			case 1:
				if (tskno_filter1_off[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_filter1_off[MessageP->ToneType]);
				}
				break;
			case 2:
				if (tskno_filter2_off[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_filter2_off[MessageP->ToneType]);
				}
				break;
			case 3:
				if (tskno_filter3_off[MessageP->ToneType] != 0xFFFF) {
					del_tsk(&tskno_filter3_off[MessageP->ToneType]);
				}
				break;
			}
		}
		else {
			/* ここに来たらバグ */
			tone_type = (WORD)MessageP->ToneType;
		}
	}
}


/*************************************************************************
	module		:[断続 パターンのトーン検出（タスク）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[ATD]
	date		:[1994/03/04]
	author		:[奥村明]
*************************************************************************/
#if (0)
** #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/05 */
** static UBYTE ATD_DEBUG_Pattern1Count = 0;
** static UBYTE ATD_DEBUG_Pattern1Noise = 0;
** static UBYTE ATD_DEBUG_Pattern1NoiseTime[10];
** static UBYTE ATD_DEBUG_Pattern1SpikeTime[10];
** static UWORD ATD_DEBUG_Pattern1OnTime[10];
** static UWORD ATD_DEBUG_Pattern1OffTime[10];
** #endif
#endif

void ATD_ToneDetectPattern1Task(struct	ToneDetectMailBoxData_t	*MessageP)
{
	struct	ToneParameters_t	*ToneTable;

	UWORD	StartOnTime		= 0;
	UWORD	StartOffTime	= 0;
	UWORD	OnTime			= 0;
	UWORD	OffTime			= 0;
	UWORD	DetOnTime		= 0;
	UWORD	DetOffTime		= 0;

	UBYTE	OnSubTime		= 0;		/*	int -> char 1994/10/25	MaxCutTimeより小さい値が入るから	*/
	UBYTE	OffSubTime		= 0;		/*	int -> char 1994/10/25	MaxNoiseTimeより小さい値が入るから	*/

	UBYTE	DetectCount		= 0;		/*	int -> char 1994/10/25変更 by A.O	*/
	UBYTE	i				= 0;
	UBYTE	pattern			= 1;		/*	テーブル上のどのＯＮ－ＯＦＦパターンと比較するかを示す変数	*/
	UBYTE	detect_pattern	= 0;		/*	比較結果が等しい時のテーブル番号	*/

#if (0)
** #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/05 */
** 	ATD_DEBUG_Pattern1Count = 0;
** 	ATD_DEBUG_Pattern1Noise = 0;
** #endif
#endif

#if defined(FRA)			/* 95.02.07 by M.HARADA */
	struct	Timer10msData_t	AFTER_RBT_TimeUp;
	tskno_after_rbt_timeup = 0xff;
/*	tskno_after_rbt_timeup = 0xffff;	*/
#endif

	switch(MessageP->ToneType) {
	case DIALTONE:
		ToneTable = (struct ToneParameters_t *)CTRY_DialTone();
		break;
	case BUSYTONE:
		ToneTable = (struct ToneParameters_t *)CTRY_BusyTone();
		break;
	case CONTONE:
		ToneTable = (struct ToneParameters_t *)CTRY_CongestionTone();
		break;
	case DIAL2TONE:
		ToneTable = (struct ToneParameters_t *)CTRY_Dial2ndTone();
		break;
	case CNG_TONE:
		ToneTable = &CNG_Tone;
		break;
	case CNG_TONE1:				/* Add By t.yamaguchi 95.12.01 留守ＦＡＸ待機時のＣＮＧ検出の場合 */
/*#if defined(POPLAR_F)*//* 2000/02/22 Y.Murata */
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* ANS/FAX待機時の、CNG検出のﾚﾍﾞﾙを上げる */
		if (CHK_AnsFaxCNG_DetLevelUp()) {
			ToneTable = &CNG_Tone2;
		}
		else {
			ToneTable = &CNG_Tone1;
		}
#else
		ToneTable = &CNG_Tone1; /* Add By Y.Tanimoto 96'1.31 留守FAX待機時のＣＮＧ検出用のﾃｰﾌﾞﾙを作成 */
#endif
		break;
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
	case PHB1_BUSY:
		ToneTable = &PhaseB1_Busy;

		/* TEL/FAX,FAX/TELモード、BusyTone検出周期の拡張処理 By O.Kimoto 2003/12/05 */
		if (CHK_UNI_ExtendBusyToneDetectTime()) {
			ToneTable->DetectCycle += CHK_UNI_ExtendBusyToneDetectTime();
		}

		break;
 /* #if defined(POPLAR_F) *//* 2000/02/02 Y.Murata */
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/05 */
	case PHA1_BUSY:
		ToneTable = &PhaseA1_Busy;

		/* TEL/FAX,FAX/TELモード、BusyTone検出周期の拡張処理 By O.Kimoto 2003/12/05 */
		if (CHK_UNI_ExtendBusyToneDetectTime()) {
			ToneTable->DetectCycle += CHK_UNI_ExtendBusyToneDetectTime();
		}

		break;
 #endif
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	case PHA1_BUSY:
		ToneTable = &PhaseA1_Busy;

		/* TEL/FAX,FAX/TELモード、BusyTone検出周期の拡張処理 By O.Kimoto 2003/12/05 */
		if (CHK_UNI_ExtendBusyToneDetectTime()) {
			ToneTable->DetectCycle += CHK_UNI_ExtendBusyToneDetectTime();
		}

		break;
#endif
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
	case PBXTONE:
		ToneTable = &PBX_Tone;

		/* TEL/FAX,FAX/TELモード、BusyTone検出周期の拡張処理 By O.Kimoto 2003/12/05 */
		if (CHK_UNI_ExtendBusyToneDetectTime()) {
			ToneTable->DetectCycle += CHK_UNI_ExtendBusyToneDetectTime();
		}

		break;
#endif
	default:
		break;
	}

	/**	指定範囲の周波数が来るまで待つ	*/
	switch (ToneTable->FilterType) {
	case 1:
		wai_evt(EVT_TONE_FILTER1_ON);
		break;
	case 2:
		wai_evt(EVT_TONE_FILTER2_ON);
		break;
	case 3:
		wai_evt(EVT_TONE_FILTER3_ON);
		break;
	}

#if defined(FRA)
	if (MessageP->ToneType == CONTONE) {
/*		if (tskno_after_rbt_timeup !=0xFFFF) {		/@ del after_RBT_timeupタスク */
		if (tskno_after_rbt_timeup !=0xFF) {		/* del after_RBT_timeupタスク */
			CMN_MultiTimer10msStop(&tskno_after_rbt_timeup);
/*			del_tsk(&tskno_after_rbt_timeup);	*/
		}
	}
#endif

/* ファネット指摘項目(No.10)
** TEL/FAX待機にしておき、受信させる（送信側は自動送信）
** ８回線交換機を使うとCNG検出がNGとなり、電話呼び出しが始まる。。。
** L-410でも同様な不具合で対策をしているのでそれをフィードバックする。
** by O.Kimoto 2002/11/01
*/
#if (0)
**  #if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
**   /* #if defined(POPLAR_F) *//* 2000/02/02 Y.Murata */
**   #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/05 */
**  	if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  	if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY))  { /* 1998/03/11  By T.Yamaguchi */
**   #endif
**  #else
**   #if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
**  	if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  	if (MessageP->ToneType == CNG_TONE) {
**   #endif
**  #endif
**  		SYS_RingToneStopFlag = 1;				/*	リングバックトーンを止める	追加 1994/12/1 by A.O	Tel/Fax待機対策	*/
**  	}
#else

	switch(MessageP->ToneType) {
	case CNG_TONE:
		SYS_RingToneStopFlag |= RBT_STOP_CNG_DETECT;
		break;
 #if (PRO_VOICE_ANSWER == ENABLE)
	case PHB1_BUSY:
		SYS_RingToneStopFlag |= RBT_STOP_PHB1_BUSY;
		break;
  #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
	case PHA1_BUSY:
		SYS_RingToneStopFlag |= RBT_STOP_PHA1_BUSY;
		break;
  #endif
 #endif
 #if (PRO_BT_DET_WHILE_RBT == ENABLE)
	case PHA1_BUSY:
		SYS_RingToneStopFlag |= RBT_STOP_PHA1_BUSY;
		break;
 #endif
	}
#endif


#if(PRO_BUILTIN_TAD == ENABLE)||(PRO_REMOTE_FAX == ENABLE)
	SYS_ToneOnFlag = 1;
#endif
	StartOnTime = SYS_GeneralTimer;	/*タイマー*/

	for(;;) {
		/**	指定範囲の周波数が来なくなるまで待つ	*/
		switch (ToneTable->FilterType) {
		case 1:
			wai_evt(EVT_TONE_FILTER1_OFF);
			break;
		case 2:
			wai_evt(EVT_TONE_FILTER2_OFF);
			break;
		case 3:
			wai_evt(EVT_TONE_FILTER3_OFF);
			break;
		}

#if defined(FRA)
		/*--------------------------------*/
		/*AFTER RBT 10秒ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
		/*--------------------------------*/
		if (MessageP->ToneType == CONTONE) {
			AFTER_RBT_TimeUp.Time	= 1500;		/*	10秒 →	15秒  95/05/16	by M.HARADA */
			AFTER_RBT_TimeUp.SendMBX		= mbxno.FCM_Task;
			AFTER_RBT_TimeUp.ReturnValue	= MSG_TIMEUP_AFTER_RBT;
			CMN_MultiTimer10msStart(&tskno_after_rbt_timeup, &AFTER_RBT_TimeUp);
/*			cre_tsk(&tskno_after_rbt_timeup, TSK_CMN_MAN_TIMER10MSTASK, &AFTER_RBT_TimeUp);	*/
		}
#endif

#if(PRO_BUILTIN_TAD == ENABLE)||(PRO_REMOTE_FAX == ENABLE)
		SYS_ToneOnFlag = 0;
#endif
		StartOffTime = SYS_GeneralTimer;	/*タイマー*/
		OnTime += StartOffTime - StartOnTime + (UWORD)OnSubTime;
		OnSubTime = 0;

		if(OnTime <= ToneTable->MaxNoiseTime) { /**ﾉｲｽﾞの時*/
			OffSubTime = (UBYTE)OnTime;
			OnTime = 0;

#if (0)
** #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/05 */
** 				if (ATD_DEBUG_Pattern1Noise < 10) {
** 					ATD_DEBUG_Pattern1NoiseTime[ATD_DEBUG_Pattern1Noise++] = OffSubTime;
** 				}
** #endif
#endif

/* ファネット指摘項目(No.10)
** TEL/FAX待機にしておき、受信させる（送信側は自動送信）
** ８回線交換機を使うとCNG検出がNGとなり、電話呼び出しが始まる。。。
** L-410でも同様な不具合で対策をしているのでそれをフィードバックする。
** by O.Kimoto 2002/11/01
*/
#if (0)
**  #if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
**   /* #if defined(POPLAR_F) */
**   #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/05 */
**  			if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  			if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY))  { /* 1998/03/11  By T.Yamaguchi */
**   #endif
**  #else
**   #if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
**  			if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  			if (MessageP->ToneType == CNG_TONE) {
**   #endif
**  #endif
**  				SYS_RingToneStopFlag = 0;				/*	リングバックトーンを送出する	追加 1994/12/1 by A.O	Tel/Fax待機対策	*/
**  			}
#else
			switch(MessageP->ToneType) {
			case CNG_TONE:
				SYS_RingToneStopFlag &= ~RBT_STOP_CNG_DETECT;
				break;
 #if (PRO_VOICE_ANSWER == ENABLE)
			case PHB1_BUSY:
				SYS_RingToneStopFlag &= ~RBT_STOP_PHB1_BUSY;
				break;
  #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
			case PHA1_BUSY:
				SYS_RingToneStopFlag &= ~RBT_STOP_PHA1_BUSY;
				break;
  #endif
 #endif
 #if (PRO_BT_DET_WHILE_RBT == ENABLE)
			case PHA1_BUSY:
				SYS_RingToneStopFlag &= ~RBT_STOP_PHA1_BUSY;
				break;
 #endif
			}
#endif
		}
		else {

/* ファネット指摘項目(No.10)
** TEL/FAX待機にしておき、受信させる（送信側は自動送信）
** ８回線交換機を使うとCNG検出がNGとなり、電話呼び出しが始まる。。。
** L-410でも同様な不具合で対策をしているのでそれをフィードバックする。
** by O.Kimoto 2002/11/01
*/
#if (0)
**  #if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
**   /* #if defined(POPLAR_F) *//* 2000/02/02 Y.Murata */
**   #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/05 */
**  			if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  			if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY))  { /* 1998/03/11  By T.Yamaguchi */
**   #endif
**  #else
**   #if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
**  			if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  			if (MessageP->ToneType == CNG_TONE) {
**   #endif
**  #endif
**  				if (ToneTable->MinOnTime[0] <= OnTime && OnTime <= ToneTable->MaxOnTime[0]) {	/*	ＯＮタイムを検出した時	*/
**  					SYS_RingToneStopFlag = 1;				/*	リングバックトーンを止める	*/
**  				}
**  			}
#else

			switch(MessageP->ToneType) {
			case CNG_TONE:
				if (ToneTable->MinOnTime[0] <= OnTime && OnTime <= ToneTable->MaxOnTime[0]) {	/*	ＯＮタイムを検出した時	*/
					SYS_RingToneStopFlag |= RBT_STOP_CNG_DETECT;	/*	リングバックトーンを止める	*/
				}
				break;
 #if (PRO_VOICE_ANSWER == ENABLE)
			case PHB1_BUSY:
				if (ToneTable->MinOnTime[0] <= OnTime && OnTime <= ToneTable->MaxOnTime[0]) {	/*	ＯＮタイムを検出した時	*/
					SYS_RingToneStopFlag |= RBT_STOP_PHB1_BUSY;	/*	リングバックトーンを止める	*/
				}
				break;
  #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
			case PHA1_BUSY:
				if (ToneTable->MinOnTime[0] <= OnTime && OnTime <= ToneTable->MaxOnTime[0]) {	/*	ＯＮタイムを検出した時	*/
					SYS_RingToneStopFlag |= RBT_STOP_PHA1_BUSY;	/*	リングバックトーンを止める	*/
				}
				break;
  #endif
 #endif
 #if (PRO_BT_DET_WHILE_RBT == ENABLE)
			case PHA1_BUSY:
				if (ToneTable->MinOnTime[0] <= OnTime && OnTime <= ToneTable->MaxOnTime[0]) {	/*	ＯＮタイムを検出した時	*/
					SYS_RingToneStopFlag |= RBT_STOP_PHA1_BUSY;	/*	リングバックトーンを止める	*/
				}
				break;
 #endif
			}
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*//* フィールドトラブル By O.Kimoto 1999/02/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* フィールドトラブル By O.Kimoto 1999/02/24 */
			if(DetOnTime == 0) {
				DetOnTime = OnTime;		/*ＯＮ　ＴＩＭＥ 確定*/
			}
			OnTime = 0;
#else
			if(DetOffTime == 0) {
				DetOffTime = OffTime;		/**ＯＦＦ ＴＩＭＥ確定*/

#if (0)
** #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/05 */
** 				if (ATD_DEBUG_Pattern1Count < 10) {
** 					ATD_DEBUG_Pattern1OffTime[ATD_DEBUG_Pattern1Count++] = DetOffTime;
** 				}
** #endif
#endif

			}
			OffTime = 0;
#endif

			if(DetOnTime > 0) {					/**	ＯＮ ＴＩＭＥが確定している時	*/
				for (i = 0; i < ToneTable->TonePattern; i++) {		/**	検出した（ＯＮ－ＯＦＦ）パターンをトーンテーブル上のすべてのパターンと比較（最初のみ）	*/
#if defined(CHE)
					/*			③ ●			*/
					/*			 ●	 ● ④		*/
					/*	↑	   ●	   ●		*/
					/*		   ●		 ●		*/
					/*	Ｏ	② ●		   ●	*/
					/*	Ｆ	   ●		  ●	*/
					/*	Ｆ	   ●		 ●		*/
					/*		   ●		●		*/
					/*			 ●	   ● ⑤	*/
					/*			① ● ●		*/
					/*				 ●			*/
					/*		   ＯＮ →			*/
					/*							*/
					if ((DetOnTime + DetOffTime > ToneTable->MaxOnTime[0]) &&					/*	①		ON + OFF > 250ms	*/
						(DetOnTime > ToneTable->MaxOnTime[1]) &&								/*	②		ON > 80ms			*/
						(DetOffTime < DetOnTime + ToneTable->MaxOnTime[2]) &&					/*	③		OFF < ON + 600ms	*/
						(DetOnTime + DetOffTime < ToneTable->MinOnTime[0]) &&					/*	④		ON + OFF < 1300ms	*/
						(DetOffTime * ToneTable->MinOnTime[1] > DetOnTime * ToneTable->MinOnTime[2])) {	/*	⑤		OFF × 8 > ON × 5	*/
#else
					if ((ToneTable->MinOnTime[pattern - 1]	<= DetOnTime) &&
					   (ToneTable->MaxOnTime[pattern - 1]  >= DetOnTime) &&
					   (ToneTable->MinOffTime[pattern - 1] <= DetOffTime) &&
					   (ToneTable->MaxOffTime[pattern - 1] >= DetOffTime)) {	/**	１パターン検出できた時	*/
#endif
						if (detect_pattern == 0) {				/**	１パターンも検出していない or 最初から検出やり直しの時	*/
							detect_pattern = pattern;		/**	どのパターンで検出したかを記憶	*/
						}
						if (pattern++ == ToneTable->TonePattern) {	/**	比較するパターンテーブルを１つ進める	*/
							pattern = 1;
						}
						if (pattern == detect_pattern) {	/**	１周期検出できた	*/
#if defined(FRA)
							if (MessageP->ToneType != CONTONE) {
								DetectCount ++;		/**続けて検出*/
							}
#else
							DetectCount ++;		/**続けて検出*/
#endif
						}
						break;
					}
					if (pattern++ == ToneTable->TonePattern) {	/**	比較するパターンテーブルを１つ進める	*/
						pattern = 1;
					}
					if (detect_pattern) {	/**	既に１パターン以上検出していた時	*/
						detect_pattern = 0;
						DetectCount = 0;	/**最初から検出やり直し*/
						/**CNG送出を止めない*/
#if defined(GBR)
						if (SYB_MachineParameter[COUNTRY_CODE] == 0) { /* 1994/10/18 by A.O For GBR */
							if (!(CNG_StopFlag & (0x01 << BUSYTONE))) {
								CNG_StopFlag &= ~(0x01 << MessageP->ToneType);
							}
						}
						else {
							CNG_StopFlag &= ~(0x01 << MessageP->ToneType);
						}
#else
						CNG_StopFlag &= ~(0x01 << MessageP->ToneType);
#endif

/* ファネット指摘項目(No.10)
** TEL/FAX待機にしておき、受信させる（送信側は自動送信）
** ８回線交換機を使うとCNG検出がNGとなり、電話呼び出しが始まる。。。
** L-410でも同様な不具合で対策をしているのでそれをフィードバックする。
** by O.Kimoto 2002/11/01
*/
#if (0)
**  #if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
**   /* #if defined(POPLAR_F) *//* 2000/02/02 Y.Murata */
**   #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/05 */
**  						if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  						if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY))  { /* 1998/03/11  By T.Yamaguchi */
**   #endif
**  #else
**   #if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
**  						if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  						if (MessageP->ToneType == CNG_TONE) {
**   #endif
**  #endif
**  							SYS_RingToneStopFlag = 0;		/*	リングバックトーンを送出可能	*/
**  						}
#else
						switch(MessageP->ToneType) {
						case CNG_TONE:
							SYS_RingToneStopFlag &= ~RBT_STOP_CNG_DETECT;
							break;
 #if (PRO_VOICE_ANSWER == ENABLE)
						case PHB1_BUSY:
							SYS_RingToneStopFlag &= ~RBT_STOP_PHB1_BUSY;
							break;
  #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
						case PHA1_BUSY:
							SYS_RingToneStopFlag &= ~RBT_STOP_PHA1_BUSY;
							break;
  #endif
 #endif
 #if (PRO_BT_DET_WHILE_RBT == ENABLE)
						case PHA1_BUSY:
							SYS_RingToneStopFlag &= ~RBT_STOP_PHA1_BUSY;
							break;
 #endif
						}
#endif

						break;
					}
				}
				if (DetectCount == ToneTable->DetectCycle) {	/**	トーン検出成功	*/
					break;										/**	 while文から抜ける	*/
				}
				/*------------------------------------*/
				/**１パターン以上検出したらCNGを止める*/
				/*------------------------------------*/
				if (detect_pattern) {
					CNG_StopFlag |= (0x01 << MessageP->ToneType);
				}
				DetOnTime  = 0;
				DetOffTime = 0;
			}
			/* ＴＥＬ／ＦＡＸ擬似ベル不具合修正 by T.Soneoka 1997/04/06
			** ＣＮＧノイズが発生した場合、ここでＯＮ・ＯＦＦタイムをクリアしておかないと次検出で
			** このＮＧのタイムをみてしまう
			*/
			else {
				DetOnTime  = 0;
				DetOffTime = 0;
			}
		}

		/**	指定範囲の周波数が来るまで待つ	*/
		switch (ToneTable->FilterType) {
		case 1:
			wai_evt(EVT_TONE_FILTER1_ON);
			break;
		case 2:
			wai_evt(EVT_TONE_FILTER2_ON);
			break;
		case 3:
			wai_evt(EVT_TONE_FILTER3_ON);
			break;
		}

/* ファネット指摘項目(No.10)
** TEL/FAX待機にしておき、受信させる（送信側は自動送信）
** ８回線交換機を使うとCNG検出がNGとなり、電話呼び出しが始まる。。。
** L-410でも同様な不具合で対策をしているのでそれをフィードバックする。
** by O.Kimoto 2002/11/01
*/
#if (0)
**  #if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
**   /* #if defined(POPLAR_F) */
**   #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/05 */
**  		if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  		if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHB1_BUSY))  { /* 1998/03/11  By T.Yamaguchi */
**   #endif
**  #else
**   #if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
**  		if ((MessageP->ToneType == CNG_TONE) || (MessageP->ToneType == PHA1_BUSY))  {
**   #else
**  		if (MessageP->ToneType == CNG_TONE) {
**   #endif
**  #endif
**  			if (OffTime > ToneTable->MaxOffTime[0]) {
**  				SYS_RingToneStopFlag = 0;				/*	リングバックトーンを送出する	追加 1994/12/1 by A.O	Tel/Fax待機対策	*/
**  			}
**  		}
#else

		switch(MessageP->ToneType) {
		case CNG_TONE:
			if (OffTime > ToneTable->MaxOffTime[0]) {
				SYS_RingToneStopFlag &= ~RBT_STOP_CNG_DETECT;
			}
			break;
 #if (PRO_VOICE_ANSWER == ENABLE)
		case PHB1_BUSY:
			if (OffTime > ToneTable->MaxOffTime[0]) {
				SYS_RingToneStopFlag &= ~RBT_STOP_PHB1_BUSY;
			}
			break;
  #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)
		case PHA1_BUSY:
			if (OffTime > ToneTable->MaxOffTime[0]) {
				SYS_RingToneStopFlag &= ~RBT_STOP_PHA1_BUSY;
			}
			break;
  #endif
 #endif
 #if (PRO_BT_DET_WHILE_RBT == ENABLE)
		case PHA1_BUSY:
			if (OffTime > ToneTable->MaxOffTime[0]) {
				SYS_RingToneStopFlag &= ~RBT_STOP_PHA1_BUSY;
			}
			break;
 #endif
		}
#endif

#if defined(FRA)
		if (MessageP->ToneType == CONTONE) {
/*			if (tskno_after_rbt_timeup !=0xFFFF) {		/@ del after_RBT_timeupタスク */
			if (tskno_after_rbt_timeup !=0xFF) {		/* del after_RBT_timeupタスク */
				CMN_MultiTimer10msStop(&tskno_after_rbt_timeup);
/*				del_tsk(&tskno_after_rbt_timeup);	*/
			}
		}
#endif
#if(PRO_BUILTIN_TAD == ENABLE)||(PRO_REMOTE_FAX == ENABLE)
		SYS_ToneOnFlag = 1;
#endif
		StartOnTime = SYS_GeneralTimer;	/*タイマー*/
		OffTime += StartOnTime - StartOffTime + (UWORD)OffSubTime;
		OffSubTime = 0;

		if(OffTime <= ToneTable->MaxCutTime) { /*瞬断の時*/
			OnSubTime = (UBYTE)OffTime;
			OffTime = 0;

#if (0)
** #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/05 */
** 			if (ATD_DEBUG_Pattern1Noise < 10) {
** 				ATD_DEBUG_Pattern1SpikeTime[ATD_DEBUG_Pattern1Noise] = OnSubTime;
** 			}
** #endif
#endif

		}
		else {
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)	*//* フィールドトラブル By O.Kimoto 1999/02/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* フィールドトラブル By O.Kimoto 1999/02/24 */
			if(DetOffTime == 0) {
				DetOffTime = OffTime;		/**ＯＦＦ ＴＩＭＥ確定*/
			}
			OffTime = 0;
#else
			if(DetOnTime == 0) {
				DetOnTime = OnTime;		/*ＯＮ　ＴＩＭＥ 確定*/

#if (0)
** #if (PRO_MODEM == R288F) /* added by H.Kubo 1998/01/05 */
** 				if (ATD_DEBUG_Pattern1Count < 10) {
** 					ATD_DEBUG_Pattern1OnTime[ATD_DEBUG_Pattern1Count] = DetOnTime;
** 				}
** #endif
#endif

			}
			OnTime = 0;
#endif

		}
	}	/* ① */

	ToneDetectMessage.Item = FROM_AUTODIAL;
	ToneDetectMessage.Message = MessageP->ToneType;
	snd_msg(MessageP->SendMBX, &ToneDetectMessage);
	wai_tsk(0xFFFF);
}

/*------------------------------------*/
/*連続ﾄｰﾝ検出タスクで生成したﾀｽｸを削除*/
/*(異常終了処理ルーチン) dev_tib.asm  */
/*------------------------------------*/
void	ATD_ToneDetectPattern0Exit(void)
{
	UBYTE i = 0;

	for (i = 0; i < CONTINUE_TONE_MAX; i++) {
		if (tskno_filter1_off[i] != 0xFFFF) {
			del_tsk(&tskno_filter1_off[i]);
		}
		if (tskno_filter2_off[i] != 0xFFFF) {
			del_tsk(&tskno_filter2_off[i]);
		}
		if (tskno_filter3_off[i] != 0xFFFF) {
			del_tsk(&tskno_filter3_off[i]);
		}
		if (tskno_tone_timeup[i] != 0xFFFF) {
			del_tsk(&tskno_tone_timeup[i]);
		}
	}
	exi_tsk();
}

#if (PRO_SPEED_EX == ENABLE)
/********************************************************************************
	module		:[着信トーン（短縮用）検出（タスク）]
	function	:[
		1.トーンがＯＮになるのを待つ
		2.ＯＮ－＞ＯＦＦに変った時点でＯＮ時間を調べノイズかどうか判断
		  ノイズの時  ：  1.へ
		  ノイズでない：  タイマタスク生成
		3.再びＯＮになる（瞬断であった）場合は 2.に戻る
		4.タイムアップ（瞬断でない場合）の場合はメッセージを返す
		5.タスクが殺されるのを待つ
	==========================================================================
				ノイズ								   瞬断			   トーン終了
	ON
				1￣1		   1￣￣￣￣￣￣￣￣￣￣1  1￣￣￣￣￣1
	OFF		 ___1  1_______＿＿1					1＿1		  1__________＿＿

	TimerTask										<-->		   <------->
		  OnTimeが短い時は							 ToneON				TimeUp
		  ﾀｲﾏｰﾀｽｸセットしない
	==========================================================================

	連続トーンがとぎれるまで検出し続けるタスク
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[ATD]
	date		:[1995/10/23]
	author		:[山口]
*********************************************************************************/
void ATD_CheckToneTask(struct ToneDetectMailBoxData_t	*MessageP)
{
	MESSAGE_t		*tone_receive;			/*	受信メッセージを格納する変数	*/

	UWORD start_on_time = 0;		/*	指定周波数のトーンが（ＯＦＦ－＞ＯＮ）に変わった時点のタイマー値をセット */
	UWORD on_time = 0;				/*	指定周波数のトーンが（ＯＦＦ－＞ＯＮ）に変わってから（ＯＮ－＞ＯＦＦ）に戻るまでの時間 */

	struct	ToneParameters_t	*ToneTable;	/*	トーンテーブル	*/
	struct	ToneDetectMailBoxData_t	SendMessageValue;

	struct Timer10msEventData_t	TimeUp;
	struct	Timer10msData_t	TimeUpTone;
	UBYTE SpeedFilterType = 0;
	UBYTE spd_tone_type = 0;

	/* for Debag */
	SpeedToneOnTime = 0;
	SpeedStartOFFTime = 0;
	SpeedOFFTime = 0;

	/*	指定周波数のﾄｰﾝが無いことを監視するﾀｽｸのIDを格納する変数 */
	tskno_spd_filter1_off = 0xFFFF;
	tskno_spd_filter2_off = 0xFFFF;
	tskno_spd_filter3_off = 0xFFFF;
	tskno_spd_tone_on_timeup = 0xFF;
	tskno_spd_tone_timeup = 0xFF;
/*	tskno_spd_tone_on_timeup = 0xFFFF;	*/
/*	tskno_spd_tone_timeup = 0xFFFF;	*/


	SendMessageValue.ToneType = MessageP->ToneType;				/*	検出するトーンの種類を指定	*/
	SendMessageValue.SendMBX  = mbxno.ATD_SPD_Tone;			/*	メッセージを送るメイルボックスを指定	*/

	SpeedToneOrTimeUpFlag = SPD_NOT_DETECT;

	/*----------------------------*/
	/* ﾄｰﾝﾃｰﾌﾞﾙをｾｯﾄ、ﾒｲﾙﾎﾞｯｸｽ生成*/
	/*----------------------------*/
	switch(MessageP->ToneType) {
		case SPD_TONE:
			spd_tone_type = CHK_UNI_ArrivalSignalToneType();

			ToneTable = &SPD_Tone[spd_tone_type];
			break;
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
		case MODE_CNG_TONE:
			ToneTable = &Mode_CNG_Tone;
			break;
#endif
		default:
			/*ここに来たらバグ*/
			break;
	}

	SpeedFilterType = ToneTable->FilterType;

	/*-------*/
	/*ﾄｰﾝ検出*/
	/*-------*/
	/*------------------------------------------*/
	/**	指定範囲のトーン周波数が来るまで待つ	*/
	/*------------------------------------------*/
	switch (SpeedFilterType) {
		case 1:
			wai_evt(EVT_TONE_FILTER1_ON);
			if (tskno_spd_filter1_off == 0xFFFF) {
				cre_tsk(&tskno_spd_filter1_off, TSK_ATD_CHECKFILTER1OFFTASK, &SendMessageValue);
			}
			break;
		case 2:
			wai_evt(EVT_TONE_FILTER2_ON);
			if (tskno_spd_filter2_off == 0xFFFF) {
				cre_tsk(&tskno_spd_filter2_off, TSK_ATD_CHECKFILTER2OFFTASK, &SendMessageValue);
			}
			break;
		case 3:
			wai_evt(EVT_TONE_FILTER3_ON);
			if (tskno_spd_filter3_off == 0xFFFF) {
				cre_tsk(&tskno_spd_filter3_off, TSK_ATD_CHECKFILTER3OFFTASK, &SendMessageValue);
			}
			break;
	}

	/*----------------------------------*/
	/*ﾄｰﾝが入って来たのでCNG送出を止める*/
	/*----------------------------------*/
	CNG_StopFlag |= (0x01 << 2);	 /* 新短縮の時はＣＮＧを止める必要あり */

	/*------------------------*/
	/*ﾄｰﾝがOFF～ONに変わった時*/
	/*------------------------*/
	start_on_time = SYS_GeneralTimer;	/* ＯＮになった時の時間を記憶 */

	/*-----------------------------------*/
	/* ONになってからの時間検出ﾀｲﾏﾀｽｸ生成*/
	/*-----------------------------------*/
	TimeUpTone.Time = ToneTable->MaxOnTime[0];
	TimeUpTone.ReturnValue = TIMEUP;
	TimeUpTone.SendMBX = mbxno.ATD_SPD_Tone;
	/* if (tskno_spd_tone_on_timeup == 0xFFFF) { */
	if (tskno_spd_tone_on_timeup == 0xFF) {
		CMN_MultiTimer10msStart(&tskno_spd_tone_on_timeup, &TimeUpTone);
/*		cre_tsk(&tskno_spd_tone_on_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUpTone);	*/
	}
	/*-------------------------------*/
	/*ﾄｰﾝ検出用ﾒｲﾙﾎﾞｯｸｽからﾒｯｾｰｼﾞ受信*/
	/*-------------------------------*/
	for(;;) {
		rcv_msg(mbxno.ATD_SPD_Tone, &tone_receive);	/* OFFになるかON時間ﾀｲﾑｱｯﾌﾟになるのを待つ */

		if (tone_receive->Message == TIMEUP) {
			/* 自タスクで生成したタスクを削除 */
			Del_SPD_CheckFilterOffTask(SpeedFilterType);
			/* if (tskno_spd_tone_on_timeup != 0xFFFF) { */
			if (tskno_spd_tone_on_timeup != 0xFF) {
				CMN_MultiTimer10msStop(&tskno_spd_tone_on_timeup);
				/* del_tsk(&tskno_spd_tone_on_timeup); */
			}
			wai_tsk(0xFFFF);	/* 最大ＯＮ時間以上検出した時、他の信号と判断する 殺されるのを待つ */
		}
		else if (tone_receive->Message == MSG_DETECT_FILTER_OFF) {
			/* 自タスクで生成したタスクを削除 */
			Del_SPD_CheckFilterOffTask(SpeedFilterType);

			on_time = (UWORD)(SYS_GeneralTimer - start_on_time);
			/* for Debag By t.yanaguchi add 2line */
			SpeedStartOFFTime = SYS_GeneralTimer;
			SpeedToneOnTime = on_time;

			if (on_time >= ToneTable->MaxNoiseTime) {	  /* ノイズでない時 */
				/*------------------------------------------------------*/
				/**指定周波数のトーンがＯＦＦになった時点でﾀｲﾏｰﾀｽｸを生成*/
				/*------------------------------------------------------*/
				TimeUp.Time = ToneTable->MaxCutTime;			/*	瞬断時間 20*10 = 200ms	*/
				switch (ToneTable->FilterType) {
				case 1:
					TimeUp.Event = EVT_TONE_FILTER1_ON;					/* タイムアップ後に発生するイベント */
					break;
				case 2:
					TimeUp.Event = EVT_TONE_FILTER2_ON;					/* タイムアップ後に発生するイベント */
					break;
				case 3:
					TimeUp.Event = EVT_TONE_FILTER3_ON;					/* タイムアップ後に発生するイベント */
					break;
				}
				/* if (tskno_spd_tone_timeup == 0xFFFF) { */
				if (tskno_spd_tone_timeup == 0xFF) {
					CMN_MultiTimer10msStart(&tskno_spd_tone_timeup, &TimeUp);
					/* cre_tsk(&tskno_spd_tone_timeup, TSK_ATD_WATCHTIMER10MSEVENTTASK, &TimeUp); */
				}
			}
			else {
				start_on_time = 0;
				/* if (tskno_spd_tone_on_timeup != 0xffff) { */
				if (tskno_spd_tone_on_timeup != 0xff) {
					CMN_MultiTimer10msStop(&tskno_spd_tone_on_timeup);
					/* del_tsk(&tskno_spd_tone_on_timeup); */
				}
			}

			switch (ToneTable->FilterType) {
			case 1:
				wai_evt(EVT_TONE_FILTER1_ON);/* OFF～ONになるのを待つ、またはタイムアップを待つ */
				break;
			case 2:
				wai_evt(EVT_TONE_FILTER2_ON);/* OFF～ONになるのを待つ、またはタイムアップを待つ */
				break;
			case 3:
				wai_evt(EVT_TONE_FILTER3_ON);/* OFF～ONになるのを待つ、またはタイムアップを待つ */
				break;
			}

			/* for Debag */
			SpeedOFFTime = (UWORD)(SYS_GeneralTimer - SpeedStartOFFTime);

			if (SpeedToneOrTimeUpFlag != SPD_DETECT_OK) {
				 /* ＯＮになった時（瞬断、或はノイズの時） SPD_NOT_DETECT */
				/* if (tskno_spd_tone_timeup != 0xFFFF) { */
				if (tskno_spd_tone_timeup != 0xFF) {
					CMN_MultiTimer10msStop(&tskno_spd_tone_timeup);
					/* del_tsk(&tskno_spd_tone_timeup); */
				}
				if (start_on_time == 0) {	/* ノイズの時 */
					start_on_time = SYS_GeneralTimer;	/* ＯＮになった時の時間を記憶 */
					/*-----------------------------------*/
					/* ONになってからの時間検出ﾀｲﾏﾀｽｸ生成*/
					/*-----------------------------------*/
					/* if (tskno_spd_tone_on_timeup == 0xFFFF) { */
					if (tskno_spd_tone_on_timeup == 0xFF) {
						CMN_MultiTimer10msStart(&tskno_spd_tone_on_timeup, &TimeUpTone);
						/* cre_tsk(&tskno_spd_tone_on_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUpTone); */
					}
				}
				switch (ToneTable->FilterType) {
				case 1:
					if (tskno_spd_filter1_off == 0xFFFF) {
						cre_tsk(&tskno_spd_filter1_off, TSK_ATD_CHECKFILTER1OFFTASK, &SendMessageValue);
					}
					break;
				case 2:
					if (tskno_spd_filter2_off == 0xFFFF) {
						cre_tsk(&tskno_spd_filter2_off, TSK_ATD_CHECKFILTER2OFFTASK, &SendMessageValue);
					}
					break;
				case 3:
					if (tskno_spd_filter3_off == 0xFFFF) {
						cre_tsk(&tskno_spd_filter3_off, TSK_ATD_CHECKFILTER3OFFTASK, &SendMessageValue);
					}
					break;
				}
			}
			else {	/* タイムアップの時 ( 瞬断、或はノイズでない場合) DETECT_OK */
				/*------------------------------*/
				/*	自タスクで生成したﾀｽｸを削除	*/
				/*------------------------------*/
				/* if (tskno_spd_tone_on_timeup == 0xFFFF) { */
				if (tskno_spd_tone_on_timeup == 0xFF) {
					CMN_MultiTimer10msStop(&tskno_spd_tone_on_timeup);
					/* del_tsk(&tskno_spd_tone_on_timeup); */
				}
				/* if (tskno_spd_tone_timeup == 0xFFFF) { */
				if (tskno_spd_tone_timeup == 0xFF) {
					CMN_MultiTimer10msStop(&tskno_spd_tone_timeup);
					/* del_tsk(&tskno_spd_tone_timeup); */
				}
				/*----------*/
				/*ﾒｯｾｰｼﾞ送信*/
				/*----------*/
				ToneDetectMessage.Item = FROM_AUTODIAL;
				ToneDetectMessage.Message = MessageP->ToneType;
				snd_msg(MessageP->SendMBX, &ToneDetectMessage);
				wai_tsk(0xFFFF);
			}
		}
		else {		/* 96/06/17 */
			/* ここに来たらバグ */
			/* 自タスクで生成したタスクを削除 */
			Del_SPD_CheckFilterOffTask(SpeedFilterType);
			/* if (tskno_spd_tone_on_timeup == 0xFFFF) { */
			if (tskno_spd_tone_on_timeup == 0xFF) {
				CMN_MultiTimer10msStop(&tskno_spd_tone_on_timeup);
				/* del_tsk(&tskno_spd_tone_on_timeup); */
			}
			wai_tsk(0xFFFF);	/* 殺されるのを待つ */
		}
	}
}

/*************************************************************************
	module		:[標準10msタイマーイベント発生タスク(短縮用着信トーン検出用）
	function	:[
		1.SpeedToneOrTimeUpFlag = SPD_DETECT_OK
		タイムアップ時、フラグにトーン検出ＯＫをセットする
	]
	return		:[]
	common		:[]
	condition	:[
		1.timer10ms_ptr->Time = ウエイトするタイマー値
		3.timer10ms_ptr->Event = タイムアップ後に発生するイベント
	]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/10/23]
	author		:[山口]
*************************************************************************/
void  ATD_WatchTimer10msEventTask(struct Timer10msEventData_t *timer10ms_ptr)
{
	wai_tsk(timer10ms_ptr->Time);
	SpeedToneOrTimeUpFlag = SPD_DETECT_OK;
	det_evt(timer10ms_ptr->Event);
	wai_tsk(0xFFFF);
}

/*************************************************************************
	module		:[短縮用のトーンオフ検出タスク削除	関数]
	function	:[
		1.トーンオフ検出タスクを削除する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[ATD]
	date		:[1995/11/01]
	author		:[山口]
*************************************************************************/

void	Del_SPD_CheckFilterOffTask(UBYTE filter_type)
{
	switch (filter_type) {
		case 1:
			if (tskno_spd_filter1_off != 0xFFFF) {
				del_tsk(&tskno_spd_filter1_off);
			}
			break;
		case 2:
			if (tskno_spd_filter2_off != 0xFFFF) {
				del_tsk(&tskno_spd_filter2_off);
			}
			break;
		case 3:
			if (tskno_spd_filter3_off != 0xFFFF) {
				del_tsk(&tskno_spd_filter3_off);
			}
			break;
		default:
			break;	/* ここに来たらバグ */
	}
}

/*------------------------------------*/
/*着信ﾄｰﾝ検出タスクで生成したﾀｽｸを削除*/
/*(異常終了処理ルーチン) dev_tib.asm  */
/*------------------------------------*/
void	ATD_CheckToneExit(void)
{

	if (tskno_spd_filter1_off != 0xFFFF) {
		del_tsk(&tskno_spd_filter1_off);
	}
	if (tskno_spd_filter2_off != 0xFFFF) {
		del_tsk(&tskno_spd_filter2_off);
	}
	if (tskno_spd_filter3_off != 0xFFFF) {
		del_tsk(&tskno_spd_filter3_off);
	}
	/* if (tskno_spd_tone_on_timeup != 0xffff) { */
	if (tskno_spd_tone_on_timeup != 0xff) {
		CMN_MultiTimer10msStop(&tskno_spd_tone_on_timeup);
		/* del_tsk(&tskno_spd_tone_on_timeup); */
	}
	/* if (tskno_spd_tone_timeup != 0xffff) { */
	if (tskno_spd_tone_timeup != 0xff) {
		CMN_MultiTimer10msStop(&tskno_spd_tone_timeup);
		/* del_tsk(&tskno_spd_tone_timeup); */
	}
	exi_tsk();
}

#endif	/* ここまで新短縮ハンドシェーク用 */
