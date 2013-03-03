/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																	*/
/*		ﾓｼﾞｭｰﾙ	:void	MercuryToneDetect(void)												*/
/*				 void	Del_Mercury_Tone_Task()												*/
/*				 void	MercuryDial(UBYTE  DialStatus)										*/
/*				 void  Mercury_DialToneDetect(void)											*/
/*				 void	Del_Mcry_DialTone_Task()											*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATDMCRYT.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\ctry_pro.h"	/* CTRY_?Tone() */
#include	"\src\atlanta\define\mon_pro.h"	/* モニタコール	 */
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
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet() */
#endif

#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */

#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\message.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h" /* By S.Kawasaki 1996/03/07 */

#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"

#include	"\src\atlanta\ext_v\atd_tbl.h"
#include	"\src\atlanta\ext_v\atd_data.h"

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
 #include	"\src\atlanta\define\std.h"
 #include	"\src\atlanta\define\status.h"
 #include	"\src\atlanta\define\ncu_stat.h"
 #include	"\src\atlanta\ext_v\bkupram.h"
 #include	"\src\atlanta\ext_v\ncu_data.h"
 #include	"\src\atlanta\ext_v\sys_data.h"
#endif

/*************************************************************************
	module		:[MercuryTone検出]
	function	:[
		1.MercuryTone検出
		2.検出,タイムアウトに対する値をリターン
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		TONE_DET_OK				:CNGトーンを検出した
		TONE_DET_TIMEUP			:トーン検出制限時間オーバー
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[原田　学]
*************************************************************************/
/*-----------------*/
/*MercuryToneを検出*/
/*-----------------*/
void   MercuryToneDetect(void)
{
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	MESSAGE_t		*ad_receive;				/*rcv_msg()で受信データをｾｯﾄする*/

	struct	Timer10msData_t	TimeUp;
	struct	ToneDetectMailBoxData_t	MercuryToneDetectMailBox;

#if (PRO_MODEM == ORANGE3)
	UBYTE	ToneDetectType = 0;

	ToneDetectType = MERCURY_DETECT;

	tskno_ATD_freq_check = 0xffff;
#endif
	tskno_mercury = 0xffff;			/* by M.HARADA	1994/12/24 */
	tskno_mcry_timeup = 0xff;		/* by M.HARADA	1994/12/24 */
/*	tskno_mcry_timeup = 0xffff;		/@ by M.HARADA	1994/12/24 */

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
	MDM_FilterSet(CNG_FILTER);				/* 1111Hz Continuous Tone */
	/*------------------*/
	/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
	/*------------------*/
	TimeUp.Time			= ((SYB_SettingStatus[MERCURY_PAUSE] * 100) + 1);	/* 0～11Sec	初期値5 */
/*	TimeUp.Time			= ((SYB_MercuryPauseTime * 100) + 1);		 0 ～ 11 Sec	初期値5 */
	TimeUp.SendMBX		= mbxno.FCM_Task;
	TimeUp.ReturnValue	= TIMEUP;
/*	cre_tsk(&tskno_mcry_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp); *//* ｺﾒﾝﾄの閉じるがなかった 1998/02/25 */
	CMN_MultiTimer10msStart(&tskno_mcry_timeup, &TimeUp);
	/*-------------------*/
	/*Mercuryﾄｰﾝ検出ﾀｽｸ生成*/
	/*-------------------*/
	if (tskno_mercury == 0xFFFF) {
		MercuryToneDetectMailBox.ToneType = MERCURY_TONE;	/*TONE_DET_OK;*/
		MercuryToneDetectMailBox.SendMBX = mbxno.FCM_Task;
		cre_tsk(&tskno_mercury, TSK_ATD_TONEDETECTPATTERN0TASK, &MercuryToneDetectMailBox);
	}
	/*-------------------------------------*/
	/*	Frequency check Only Orange3 Modem */
	/*-------------------------------------*/
#if (PRO_MODEM == ORANGE3)
	if (tskno_ATD_freq_check == 0xFFFF) {
		cre_tsk(&tskno_ATD_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &ToneDetectType);
	}
#endif
	/*----------*/
	/*ﾒｯｾｰｼﾞ受信*/
	/*----------*/
	rcv_msg(mbxno.FCM_Task, &ad_receive);
	/*------------------*/
	/*	　終了処理		*/
	/*--------------------------*/
	/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
	/*--------------------------*/
	Del_Mercury_Tone_Task();
#endif
}

/*-------------------------------*/
/*ﾀﾞｲｱﾙﾄｰﾝ検出で生成したﾀｽｸを削除*/
/*-------------------------------*/
void	Del_Mercury_Tone_Task()
{
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	if (tskno_mercury != 0xFFFF) {
		del_tsk(&tskno_mercury);
	}
/*	if (tskno_mcry_timeup != 0xFFFF) {	1996/12/12	By T.Yamaguchi	*/
	if (tskno_mcry_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_mcry_timeup);
/*		del_tsk(&tskno_mcry_timeup);	*/
	}
#if (PRO_MODEM == ORANGE3)
	if (tskno_ATD_freq_check != 0xFFFF) {
		del_tsk(&tskno_ATD_freq_check);
	}
#endif
#endif
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[マーキュリー・キー実行]
	function	:[
		1.マーキュリー・キー動作（ＡＵＴ内線番号発呼に類似）を実現させる。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[H8/300]
	language	:[H8/300(日立マイコン)]
	keyword		:[NCU/ATD/FCM]
	date		:[1994/03/07]
	author		:[原田学]
	変更履歴	:[	1. 1994/11/16  NCU_RLY.Cより移動	（原田）
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	MercuryDial(UBYTE  DialStatus)
{

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	UBYTE  count = 0;
	UBYTE  MercuryDialNumber = 0;
	UBYTE  DialToneDetectFlag = 0;
	UBYTE  ReturnMercury = 0;
	UBYTE  return_flash_status = 0;

/*	FCM_GetDialData(SubDialBuffer,SYB_MercuryDialBuffer);	既にアスキーで入力されている　*/
 #if 0  /* Deleted by S.Fukui Sep.13,1997 */
// #if (PRO_NCU_TYPE == LAVENDER_USA_TYPE)
//	SpeakerOutSelectTELorKEY();
//  #endif
 #endif
 
 #if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* DVT : mod by SMuratec C.P 2004/09/06 *//* by K.Watanabe 2004/10/12 */
	UBYTE pre_dial_num = 0;			/*Buffer[cnt-1]に登録されているﾀﾞｲｱﾙ番号*/
 #else	
	MonitorSpeakerOff();			/** モニター・スピーカーＯＦＦ */
 #endif
 
	if((DialStatus == DIAL_STATUS_OFFHOOK1) || (DialStatus == DIAL_STATUS_OFFHOOK2)){	/* 94.12.07 M.H. */
		DP_RelayOn();		/*	1996/07/10 by H.Yagi  */
		wai_tsk(1);			/*	1996/07/10 by H.Yagi  */
		CML_RelayOn();
		InterRelayTimer();
 #if defined(STOCKHM2) || defined (HINOKI3)/* QAT : mod by SMuratec C.P 2004/11/04 */
		CONT_24V_Off();
		InterRelayTimer();
		L_RelayOn();
		InterRelayTimer();
 #else
		CONT_24V_On();
		InterRelayTimer();
 #endif
		H_RelayOn();
		InterRelayTimer();
	}
	while ( (MercuryDialNumber = SYB_MercuryDialBuffer[ count++ ]) != NULL ){
		switch( MercuryDialNumber ){
			case	'-':
				break;
			case	'!':	/* DialTone検出 */
			/* DVT : Added start by SMuratec 夏 2004/9/8 */
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* by K.Watanabe 2004/10/12 */
				if (pre_dial_num == '-') {
					SYS_DialChange = 1;
					ATD_RelayOff();		/**	ダイヤルトーン送出の為にリレーを戻す	*/
				}
				else
#endif
			/*	Added end by SMuratec 夏 2004/9/8*/
				if(DialToneDetectFlag == 0){		/* ２回目以降をはじくための処理 */
			
					ATD_BreakDTMF_Tx();	 /* H.Kubo 1997/11/06 */
					ATD_RelayOff();	/**	トーン検出の為にリレーを戻す	*/
					DialToneDetectFlag = 1;
					Mercury_DialToneDetect();			/* add by M.HARADA 1994/12/24 */
/*					if ((ReturnMercury = DialToneDetect()) != AD_OK) {
						if (!CHK_DialToneOrTimeupAvailable()) {	@** ﾀﾞｲｱﾙﾄｰﾝを検出しないと発呼しない設定になっている時 *@
							return(ReturnMercury);
						}
					}		*/							/* del by M.HARADA 1994/12/24 */
				}
				break;
			case	'/':
				if(SYB_MercuryDialBuffer[count-2]=='-'){	/* ポーズ */
					wai_tsk(CHK_PauseTime()*100 + 1);
				}
				else{								/* フラッシュキー */
					if(NCUStatus & TELEPHONE1_OFF_HOOK){
						return_flash_status = DIAL_STATUS_OFFHOOK1;
					}
					if(NCUStatus & TELEPHONE2_OFF_HOOK){
						return_flash_status = DIAL_STATUS_OFFHOOK2;
					}
					if(NCUStatus & HOOK_KEY_ON_STATE){
						return_flash_status = DIAL_STATUS_HOOK_KEY;
					}
					Flash_Off_On(return_flash_status);
					wai_tsk(30);		/* フラッシュキー動作後のウエイト：３００ｍｓ  1994/12/28 M.HARADA */
					DP_RelayOn();		/* 1996/07/12 by H.Yagi */
					CML_RelayOn();
					if(NCUStatus & TELEPHONE1_OFF_HOOK){
						H_RelayOn();
					}
					if(NCUStatus & TELEPHONE2_OFF_HOOK){
						L_RelayOn();
					}
 #if defined(STOCKHM2) || defined(HINOKI3) /* QAT : mod by SMuratec C.P 2004/11/04 */
					CONT_24V_Off();
 #else
					CONT_24V_On();
 #endif
					#if(0)
					/*****	add by M.HARADA	 '95/04/10	*****/
					CML_RelayOn();
					H_RelayOn();
					/****************************************/
					#endif
				}
				break;
			case	'M':
				S_RelayOff();
				MercuryToneDetect();
				SYS_DialChange = 1;
				break;
			case	'*':
			case	'#':							/*回線ﾀｲﾌﾟがDTMFの時だけ送出*/
				if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
					DP_RelayOn();		/* 1996/07/12 by H.Yagi */
					CML_RelayOn();
 #if defined(STOCKHM2) || defined(HINOKI3) /* QAT : Add by SMuratec C.P 2004/11/04	*/
					if(NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK )){
						MonitorSpeakerOn();
					}
 #endif
					OutPutDial(MercuryDialNumber);
				}
				break;
			default:								/* 数字 */
				if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
					if(!( CML_RelaySetting())){
						DP_RelayOn();		/* 1996/07/12 by H.Yagi */
						CML_RelayOn();
						InterRelayTimer();
					}
 #if defined(STOCKHM2) || defined(HINOKI3) /* QAT : Add by SMuratec C.P 2004/11/04	*/
					if(NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK )){
						MonitorSpeakerOn();
					}
 #endif
				} else {
					if(!( DP_RelaySetting())){
						DP_RelayOn();
						InterRelayTimer();
					}
					if(!( CML_RelaySetting())){
						CML_RelayOn();
						InterRelayTimer();
					}
					if(!( S_RelaySetting())){
						S_RelayOn();
					}
				}
				OutPutDial( MercuryDialNumber );
		}
/* DVT : Added start by SMuratec 夏 2004/9/8 */
#if defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)
		pre_dial_num = MercuryDialNumber;
#endif
/* Added end by SMuratec 夏 2004/9/8 */
	}
/*************			del by M.harada '95/04/10					**********************/
/*	if((DialStatus == DIAL_STATUS_OFFHOOK1) || (DIAL_STATUS_OFFHOOK2)){	@* 94.12.07 M.H. */
/*		H_RelayOff();																	 */
/*		InterRelayTimer();																 */
/*		CONT_24V_Off();																	 */
/*		InterRelayTimer();																 */
/*		CML_RelayOff();																	 */
/*		InterRelayTimer();																 */
/*	}																					 */
/*****************************************************************************************/
	if(((DialStatus == DIAL_STATUS_AUTODIAL) && (CHK_LineMonitor()))
											 || DialStatus == DIAL_STATUS_HOOK_KEY){
 #if 0	/* Deleted by S.Fukui Sep.13,1997 */
//	#if (PRO_NCU_TYPE == LAVENDER_USA_TYPE)
//		SpeakerOutSelectMonitor();
//	#endif
 #endif
		MonitorSpeakerOn();
	}

	ATD_BreakDTMF_Tx();	 /* ここが大事 */
	
 #if !defined(STOCKHM2) && (PRO_PREFIX_KEY == DISABLE)	/* DVT : mod by SMuratec C.P 2004/09/07 *//* by K.Watanabe 2004/10/12 */
	SYS_DialChange = 1;
 #endif
 
#endif
}


/*************************************************************************
	module		:[マーキュリーダイヤル時ダイアルトーン検出]
	function	:[
		1.ダイヤルトーン検出
		2.検出したトーン、事象に対する値をリターン
	]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		AD_OK			:ダイアルトーンを検出した
		AD_NO_DIAL_TONE	:トーン検出制限時間オーバー
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[原田　学]
*************************************************************************/
void  Mercury_DialToneDetect(void)
{
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */

	MESSAGE_t		*ad_receive;				/*rcv_msg()で受信データをｾｯﾄする*/
	UBYTE	return_value = 0;

	struct	Timer10msData_t	TimeUp;
	struct	ToneDetectMailBoxData_t	Mcry_DialToneDetectMailBox;

#if (PRO_MODEM == ORANGE3)
	UBYTE	ToneDetectType = 0;

	ToneDetectType = BEFORE_DIAL_DETECT;

	tskno_ATD_freq_check = 0xffff;
#endif
	tskno_mcry_dt = 0xffff;
	tskno_mcry_dt_timeup = 0xff;
/*	tskno_mcry_dt_timeup = 0xffff;	1996/12/12	By T.Yamaguchi */

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
	MDM_FilterSet(BEFORE_DIAL_FILTER);
	/*------------------*/
	/*ﾀｲﾑｱｯﾌﾟ検出ﾀｽｸ生成*/
	/*------------------*/
	TimeUp.Time			= CTRY_DialTone()->MaxDetectTime;	/*ダイアルトーン検出時間*/
	TimeUp.SendMBX		= mbxno.FCM_Task;
	TimeUp.ReturnValue	= TIMEUP;
/*	cre_tsk(&tskno_mcry_dt_timeup, TSK_CMN_MAN_TIMER10MSTASK, &TimeUp);	*/
	CMN_MultiTimer10msStart(&tskno_mcry_dt_timeup, &TimeUp);
	/*-------------------*/
	/*ﾀﾞｲｱﾙﾄｰﾝ検出ﾀｽｸ生成*/
	/*-------------------*/
	if (CTRY_DialTone()->DetectCycle) {
		Mcry_DialToneDetectMailBox.ToneType = DIALTONE;
		Mcry_DialToneDetectMailBox.SendMBX = mbxno.FCM_Task;
		switch (CTRY_DialTone()->TonePattern) {
		case	0:		/*ﾄｰﾝのﾊﾟﾀｰﾝが連続の時*/
			cre_tsk(&tskno_mcry_dt, TSK_ATD_TONEDETECTPATTERN0TASK, &Mcry_DialToneDetectMailBox);
			break;
		case	1:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF の時*/
		case	2:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF の時*/
		case	3:		/*ﾄｰﾝのﾊﾟﾀｰﾝが ON-OFF-ON-OFF-ON-OFF の時*/
			cre_tsk(&tskno_mcry_dt, TSK_ATD_TONEDETECTPATTERN1TASK, &Mcry_DialToneDetectMailBox);
			break;
		}
	}
	/*-------------------------------------*/
	/*	Frequency check Only Orange3 Modem */
	/*-------------------------------------*/
#if (PRO_MODEM == ORANGE3)
	cre_tsk(&tskno_ATD_freq_check, TSK_ATD_FILTERONOFFDETECTTASK, &ToneDetectType);
#endif
	/*----------*/
	/*ﾒｯｾｰｼﾞ受信*/
	/*----------*/
	rcv_msg(mbxno.FCM_Task, &ad_receive);
	/*--------------------------*/
	/*ﾄｰﾝ検出で使用したﾀｽｸを削除*/
	/*--------------------------*/
	Del_Mcry_DialTone_Task();

#endif
}

/*-------------------------------*/
/*マーキュリーダイヤル時ダイヤルトーン検出で生成したﾀｽｸを削除*/
/*-------------------------------*/
void	Del_Mcry_DialTone_Task()
{
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	if (tskno_mcry_dt != 0xFFFF) {
		del_tsk(&tskno_mcry_dt);
	}
/*	if (tskno_mcry_dt_timeup != 0xFFFF) {	1996/12/12	By T.Yamaguchi
**		del_tsk(&tskno_mcry_dt_timeup);
**	}
*/
	if (tskno_mcry_dt_timeup != 0xFF) {
		CMN_MultiTimer10msStop(&tskno_mcry_dt_timeup);
	}
#if (PRO_MODEM == ORANGE3)
	if (tskno_ATD_freq_check != 0xFFFF) {
		del_tsk(&tskno_ATD_freq_check);
	}
#endif
#endif
}

