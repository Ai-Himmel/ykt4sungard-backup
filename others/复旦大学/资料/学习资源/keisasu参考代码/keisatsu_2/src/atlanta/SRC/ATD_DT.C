/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANT																		*/
/*		ﾓｼﾞｭｰﾙ	:UBYTE DialToneDetect(void)									*/
/*				:void Del_DialTone_Task(void)											*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_DT.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\ctry_pro.h"	/* CTRY_?Tone() */
#include	"\src\atlanta\define\mon_pro.h"		/* モニタコール	 */
#include	"\src\memsw\define\mems_pro.h"		/*1996/04/17 Eguchi */

#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1997/07/19 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* MDM_FilterSet() */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"	/* MDM_FilterSet() */
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"	/* MDM_FilterSet() */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet() */
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#endif

#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"

#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\ext_v\fcm_data.h"
#if defined(FRA)	/* 95/03/29 by M.HARADA */
 #include	"\src\atlanta\ext_v\atd_data.h"
#endif
#if defined(GBR)	/* add by M.HARADA 95.09.09 for NLD */
 extern UBYTE SYB_MachineParameter[SYS_MACHINE_PARAMETER_MAX];
 #include	"\src\atlanta\define\param.h"
#endif

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include	"\src\atlanta\sh7043\define\def_tib.h"

#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* モデムに依存するのではないが、仕方なく。 by H.Kubo*/
static UWORD tskno_dt = 0xffff;
static UWORD tskno_bt = 0xffff;
static UWORD tskno_ct = 0xffff;
/* static UWORD tskno_ad_timeup = 0xffff;	*/
static UBYTE tskno_ad_timeup = 0xff;
static UWORD tskno_ad_stop = 0xffff;
static UWORD tskno_loop_current_chk = 0xffff;
 #if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
static UWORD tskno_pbx = 0xffff;
 #endif
#else
static UWORD tskno_dt = 0;
static UWORD tskno_bt = 0;
static UWORD tskno_ct = 0;
/* static UWORD tskno_ad_timeup = 0;	*/
static UBYTE tskno_ad_timeup = 0;
static UWORD tskno_ad_stop = 0;
/* static UWORD tskno_loop_current_chk = 0; */
#endif

#if (PRO_MODEM == ORANGE3)
static UWORD tskno_freq_check = 0;
#endif

/*************************************************************************
	module		:[ダイアルトーン検出]
	function	:[
		1.発呼前トーン検出
		2.検出したトーン、事象に対する値をリターン
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		AD_OK			:ダイアルトーンを検出した
		AD_NO_DIAL_TONE	:トーン検出制限時間オーバー
		AD_REMOTE_BUSY	:ダイアルトーン以外のトーンを検出した
		AD_STOPPED		:停止ボタンが押された
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/
/*-----------------------------------------------------*/
/*ﾄｰﾝを検出，ﾄｰﾝの種類をAutoDial()にﾘﾀｰﾝ, DT|BT|CT|STOP*/
/*-----------------------------------------------------*/
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
UBYTE	DialToneDetect(UBYTE before_dial)
#else
UBYTE	DialToneDetect(void)
#endif
{

	MESSAGE_t		*ad_receive;				/*rcv_msg()で受信データをｾｯﾄする*/
	UBYTE	return_value = 0;

	struct	Timer10msData_t	TimeUp;
	struct	ToneDetectMailBoxData_t	DialToneDetectMailBox;
#if defined(FRA)	/* add by M.HARADA '97/12/9 */
	/* FRAではﾀﾞｲﾔﾙ前にBT、CTを検出してはいけない */
#else
	struct	ToneDetectMailBoxData_t	BusyToneDetectMailBox;
	struct	ToneDetectMailBoxData_t	ConToneDetectMailBox;
 #if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
	struct	ToneDetectMailBoxData_t	PbxToneDetectMailBox;
 #endif
#endif

#if (PRO_MODEM == ORANGE3)
	UBYTE	tone_detect_type;

	tone_detect_type = BEFORE_DIAL_DETECT;		/* ダイヤル前のトーン検出をセット */

	tskno_freq_check = 0xffff;
#endif
	tskno_dt = 0xffff;
	tskno_bt = 0xffff;
	tskno_ct = 0xffff;
/*	tskno_ad_timeup = 0xffff;	*/
	tskno_ad_timeup = 0xff;
	tskno_ad_stop = 0xffff;

#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
	tskno_pbx = 0xffff;
#endif

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* モデムに依存するのではないが、仕方なく。 by H.Kubo*/
	tskno_loop_current_chk = 0xFFFF;
#endif
#if defined(FRA)		/* 95/03/29 M.HARADA */
	tskno_after_rbt_timeup = 0xff;
/*	tskno_after_rbt_timeup = 0xffff;	*/
#endif

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Added by H.Kubo 1997/07/19 */
	/* ダイヤルトーン検出用フィルターをセットする前に
	** ＣＯＮＦの値をＶ．８からＶ．２１に戻しておきます。
	** 1997/05/27 Y.Murata
	*/
	/*---------------------------------------*/
	/* re config tone mode for ATV25detector */
	/*---------------------------------------*/
	MDM_ToneModeConfig();
#endif /* (PRO_MODEM == R288F) */

	/*------------------------------*/
	/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
	/*------------------------------*/
#if defined(GBR)		/* add by M.HARADA 95.09.09 for NLD */
	if(SYB_MachineParameter[COUNTRY_CODE] == 5){		/* NLD */
		NLD_DT_Detecting_Flag = 1;
		MDM_FilterSet(BEFORE_NLD_DIAL_FILTER);
	}else{
		MDM_FilterSet(BEFORE_DIAL_FILTER);
	}
#else
	MDM_FilterSet(BEFORE_DIAL_FILTER);
#endif
	/*------------------*/
	/*ｽﾄｯﾌﾟｷｰ検出ﾀｽｸ	*/
	/*------------------*/
	if (tskno_ad_stop == 0xFFFF) {
		cre_tsk(&tskno_ad_stop, TSK_ATD_CHECKSTOPTASK, 0);
	}
	/*------------------*/
	/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
	/*------------------*/
	TimeUp.Time			= ((struct ToneParameters_t *)CTRY_DialTone())->MaxDetectTime;	/*ダイアルトーン検出時間*/
	TimeUp.SendMBX		= mbxno.FCM_Task;
	TimeUp.ReturnValue	= TIMEUP;
/*	cre_tsk(&tskno_ad_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);	*/
	CMN_MultiTimer10msStart(&tskno_ad_timeup, &TimeUp);
	/*-------------------*/
	/*ﾀﾞｲｱﾙﾄｰﾝ検出ﾀｽｸ生成*/
	/*-------------------*/
	if (((struct ToneParameters_t *)CTRY_DialTone())->DetectCycle) {
		DialToneDetectMailBox.ToneType = DIALTONE;
		DialToneDetectMailBox.SendMBX = mbxno.FCM_Task;
		switch (((struct ToneParameters_t *)CTRY_DialTone())->TonePattern) {
		case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
			cre_tsk(&tskno_dt, TSK_ATD_TONEDETECTPATTERN0TASK, &DialToneDetectMailBox);
			break;
		case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
		case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
		case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
			cre_tsk(&tskno_dt, TSK_ATD_TONEDETECTPATTERN1TASK, &DialToneDetectMailBox);
			break;
		}
	}
#if defined(FRA)	/* add by M.HARADA '97/12/9 */
	/* FRAではﾀﾞｲﾔﾙ前にBT、CTの検出をしてはいけない */
#else
	/*-------------------*/
	/*ﾋﾞｼﾞ-ﾄｰﾝ検出ﾀｽｸ生成*/
	/*-------------------*/
	if(FCM_PtnrChkBusyToneDetect()) {
		if (((struct ToneParameters_t *)CTRY_BusyTone())->DetectCycle) {
			BusyToneDetectMailBox.ToneType = BUSYTONE;
			BusyToneDetectMailBox.SendMBX = mbxno.FCM_Task;
			switch (((struct ToneParameters_t *)CTRY_BusyTone())->TonePattern) {
			case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
				cre_tsk(&tskno_bt, TSK_ATD_TONEDETECTPATTERN0TASK, &BusyToneDetectMailBox);
				break;
			case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
			case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
			case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
				cre_tsk(&tskno_bt, TSK_ATD_TONEDETECTPATTERN1TASK, &BusyToneDetectMailBox);
				break;
			}
		}
	}
	/*-----------------------*/
	/*ｺﾝｼﾞｪｽｼｮﾝﾄｰﾝ検出ﾀｽｸ生成*/
	/*-----------------------*/
#if (PRO_CLASS1 == ENABLE)
	if(CHK_UNI_ConToneDetect() || CL1_ContoneDet == 1) {
#else
	if(CHK_UNI_ConToneDetect()) {
#endif
		if (((struct ToneParameters_t *)CTRY_CongestionTone())->DetectCycle) {
			ConToneDetectMailBox.ToneType = CONTONE;
			ConToneDetectMailBox.SendMBX = mbxno.FCM_Task;
			switch (((struct ToneParameters_t *)CTRY_CongestionTone())->TonePattern) {
			case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
				cre_tsk(&tskno_ct, TSK_ATD_TONEDETECTPATTERN0TASK, &ConToneDetectMailBox);
				break;
			case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
			case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
			case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
				cre_tsk(&tskno_ct, TSK_ATD_TONEDETECTPATTERN1TASK, &ConToneDetectMailBox);
				break;
			}
		}
	}
#endif
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
	/*-----------------------*/
	/*内線ダイヤルトーン検出タスク生成*/
	/*-----------------------*/
	if (!CHK_PBX()){				/* 外線設定である。*/
		if(CHK_UNI_BeforeDialPbxToneDetect() && (before_dial == BEFORE_DIAL)) {		/* PBXトーン検出設定になっていて、かつダイヤル前のトーン検出である。*/
			PbxToneDetectMailBox.ToneType = PBXTONE;
			PbxToneDetectMailBox.SendMBX = mbxno.FCM_Task;
			cre_tsk(&tskno_pbx, TSK_ATD_TONEDETECTPATTERN1TASK, &PbxToneDetectMailBox);
		}
	}
#endif
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* 復活させてみる。1998/01/19 */
/* #if 0 */	/* defined(FRA) */
	/*----------------------------------*/
	/*	カレントループ検出タスク生成	*/
	/*----------------------------------*/
	if(CHK_UNI_CurrentLoop()) {
		cre_tsk(&tskno_loop_current_chk, TSK_ATD_LC_OFFCHECKTASK, 0);
	}
#endif
	/*-------------------------------------*/
	/*	Frequency check Only Orange3 Modem */
	/*-------------------------------------*/
#if (PRO_MODEM == ORANGE3)
	cre_tsk(&tskno_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &tone_detect_type);
#endif
	/*----------*/
	/*ﾒｯｾｰｼﾞ受信*/
	/*----------*/
	rcv_msg(mbxno.FCM_Task, &ad_receive);
	/*------------------*/
	/*ﾒｯｾｰｼﾞに対する処理*/
	/*------------------*/
	switch (ad_receive->Message) {
	case	DIALTONE:
		return_value = AD_OK;
		break;
	case	TIMEUP:
		return_value = AD_NO_DIAL_TONE;
		break;
	case	MSG_DETECT_STOP:
		return_value = AD_STOPPED;
		break;
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* 復活させてみる。1998/01/19 */
/* #if 0	/* defined(FRA) */
	case	MSG_DETECT_LC_OFF:	/* カレントループ無しを検出　*/
		return_value = AD_NO_CURRENT_LOOP;
		break;
#endif
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
	case	PBXTONE:
		return_value = AD_OK;
		break;
#endif
	default:		/* ﾋﾞｼﾞｰﾄｰﾝ、ｺﾝｼﾞｪｽｼｮﾝﾄｰﾝ */
		return_value = AD_REMOTE_BUSY;
	}
	/*--------------------------*/
	/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
	/*--------------------------*/
	Del_DialTone_Task();
#if defined(GBR)	/* add by M.HARADA 95.09.09 for NLD */
	if(SYB_MachineParameter[COUNTRY_CODE] == 5){
		NLD_DT_Detecting_Flag = 0;
	}
#endif

	return(return_value);
}

/*-------------------------------*/
/*ﾀﾞｲｱﾙﾄｰﾝ検出で生成したﾀｽｸを削除*/
/*-------------------------------*/
void	Del_DialTone_Task()
{
	if (tskno_dt != 0xFFFF) {
		del_tsk(&tskno_dt);
	}
	if (tskno_bt != 0xFFFF) {
		del_tsk(&tskno_bt);
	}
	if (tskno_ct != 0xFFFF) {
		del_tsk(&tskno_ct);
	}
	if (tskno_ad_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_ad_timeup);
	}
#if 0	/* 1996/12/12  By T.Yamaguchi */
	if (tskno_ad_timeup != 0xFFFF) {
		del_tsk(&tskno_ad_timeup);
	}
#endif
	if (tskno_ad_stop != 0xFFFF) {
		del_tsk(&tskno_ad_stop);
	}
#if (PRO_MODEM == ORANGE3)
	if (tskno_freq_check != 0xFFFF) {
		del_tsk(&tskno_freq_check);
	}
#endif
#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* 復活させてみる。1998/01/19 */
	if (tskno_loop_current_chk != 0xFFFF) {
		del_tsk(&tskno_loop_current_chk);
	}
#endif
#if 0	/* defined(FRA) */
/*	if (tskno_after_rbt_timeup !=0xFFFF) {		/@ 95/03/29 M.HARADA */
	if (tskno_after_rbt_timeup !=0xFF) {		/* 1996/12/12  By T.Yamaguchi */
		CMN_MultiTimer10msStop(&tskno_after_rbt_timeup);
/*		del_tsk(&tskno_after_rbt_timeup);	*/
	}
#endif
#if (PRO_PBX_TONE_DETECT == ENABLE)	/* 発着衝突防止のため、ダイヤル発呼前に内線トーンを見る 2004/10/27 by Y.Kano */
	if (tskno_pbx != 0xFFFF) {
		del_tsk(&tskno_pbx);
	}
#endif
}
