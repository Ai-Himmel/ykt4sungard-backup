/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																		*/
/*		ﾓｼﾞｭｰﾙ	:UBYTE Dial2ndToneDetect(void)									*/
/*				:void Del_Dial2ndTone_Task(void)											*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_D2T.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\ctry_pro.h"	/* CTRY_Dial2ndTone() */
#include	"\src\atlanta\define\mon_pro.h"	/* モニタコール */
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1997/07/19 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* MDM_FilterSet(),MDM_FilterSet2ndDial() */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"	/* MDM_FilterSet(),MDM_FilterSet2ndDial() */
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"	/* MDM_FilterSet(),MDM_FilterSet2ndDial() */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet(),MDM_FilterSet2ndDial() */
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#endif

#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\SH7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */


static UWORD tskno_d2t = 0;
/* static UWORD tskno_ad_timeup = 0;	*/
static UWORD tskno_ad_stop = 0;
static UBYTE tskno_ad_timeup = 0;

#if (PRO_MODEM == ORANGE3)
static UWORD tskno_freq_check = 0;
#endif

/*************************************************************************
	module		:[第二ダイアルトーン検出]
	function	:[
		第二ダイアルトーン検出
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		AD_OK			:第二ダイアルトーンを検出した
		AD_STOPPED		:停止ボタンが押された
		AD_NO_DIAL_TONE	:トーン検出制限時間オーバー
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/
UBYTE Dial2ndToneDetect(void)
{
	MESSAGE_t		*ad_receive;			/*rcv_msg()で受信データをｾｯﾄする*/

	struct	Timer10msData_t	TimeUp;
	struct	ToneDetectMailBoxData_t	Dial2ndToneDetectMailBox;

	UBYTE	return_value = 0;
#if (PRO_MODEM == ORANGE3)
	UBYTE	ToneDetectType;

	ToneDetectType = DIAL2TONE_DETECT;

	tskno_freq_check = 0xffff;
#endif
	tskno_d2t = 0xffff;
	tskno_ad_timeup = 0xff;
/*	tskno_ad_timeup = 0xffff;	*/
	tskno_ad_stop = 0xffff;

	/*------------------------------*/
	/*ﾌｨﾙﾀｰのﾄｰﾝ周波数検出範囲を設定*/
	/*------------------------------*/
	MDM_FilterSet(DIALTONE_2ND_FILTER);

	/*------------------*/
	/*ｽﾄｯﾌﾟｷｰ検出ﾀｽｸ	*/
	/*------------------*/
	if (tskno_ad_stop == 0xFFFF) {
		cre_tsk(&tskno_ad_stop, TSK_ATD_CHECKSTOPTASK, 0);
	}
	/*------------------*/
	/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
	/*------------------*/
	TimeUp.Time			= ((struct ToneParameters_t *)CTRY_Dial2ndTone())->MaxDetectTime;/*第２ダイアルトーン検出時間*/
	TimeUp.SendMBX		= mbxno.FCM_Task;
	TimeUp.ReturnValue	= TIMEUP;
	CMN_MultiTimer10msStart(&tskno_ad_timeup, &TimeUp);
/*	cre_tsk(&tskno_ad_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);	*/
	/*-----------------------*/
	/*第２ﾀﾞｲｱﾙﾄｰﾝ検出ﾀｽｸ生成*/
	/*-----------------------*/
	Dial2ndToneDetectMailBox.ToneType = DIAL2TONE;
	Dial2ndToneDetectMailBox.SendMBX = mbxno.FCM_Task;
	switch (((struct ToneParameters_t *)CTRY_Dial2ndTone())->TonePattern) {
	case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
		cre_tsk(&tskno_d2t, TSK_ATD_TONEDETECTPATTERN0TASK, &Dial2ndToneDetectMailBox);
		break;
	case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
	case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
	case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
		cre_tsk(&tskno_d2t, TSK_ATD_TONEDETECTPATTERN1TASK, &Dial2ndToneDetectMailBox);
		break;
	}
	/*-------------------------------------*/
	/*	Frequency check Only Orange3 Modem */
	/*-------------------------------------*/
#if (PRO_MODEM == ORANGE3)
	cre_tsk(&tskno_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &ToneDetectType);
#endif

	/*----------*/
	/*ﾒｯｾｰｼﾞ受信*/
	/*----------*/
	rcv_msg(mbxno.FCM_Task, &ad_receive);
	/*------------------*/
	/*ﾒｯｾｰｼﾞに対する処理*/
	/*------------------*/
	switch (ad_receive->Message) {
	case	DIAL2TONE:
		return_value = AD_OK;
		break;
	case	MSG_DETECT_STOP:
		return_value = AD_STOPPED;
		break;
	default:	/*TIMEUP*/
		return_value = AD_NO_DIAL_TONE;
	}
	/*-----------------------------------*/
	/*第２ﾀﾞｲｱﾙﾄｰﾝ検出で使用したﾀｽｸを削除*/
	/*-----------------------------------*/
	Del_Dial2ndTone_Task();

	return(return_value);
}

/*-------------------------------*/
/*第２ﾀﾞｲｱﾙﾄｰﾝ検出で生成したﾀｽｸを削除*/
/*-------------------------------*/
void	Del_Dial2ndTone_Task()
{
	if (tskno_d2t != 0xFFFF) {
		del_tsk(&tskno_d2t);
	}
/*	if (tskno_ad_timeup != 0xFFFF) {	*/
	if (tskno_ad_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_ad_timeup);
/*		del_tsk(&tskno_ad_timeup);	*/
	}
	if (tskno_ad_stop != 0xFFFF) {
		del_tsk(&tskno_ad_stop);
	}
#if (PRO_MODEM == ORANGE3)
	if (tskno_freq_check != 0xFFFF) {
		del_tsk(&tskno_freq_check);
	}
#endif /* (PRO_MODEM == ORANGE3) */
}

