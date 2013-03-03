/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ANZU																		*/
/*		ﾓｼﾞｭｰﾙ	:unsigned char OutPutDial(unsigned char)								*/
/*				:unsigned char AsciiToDialNumber(unsigned char)						*/
/*		作成者	:山口																		*/
/*		日付	:1995/09/22																	*/
/*		概要	:																			*/
/*				 \SRC\RICE\SRC\ATD_OUTD.Cを流用しました										*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\mon_pro.h"				/* モニタコール */
#include	"\src\atlanta\define\ctry_pro.h"			/* CTRY_DialTable() */
#include	"\src\atlanta\define\stng_pro.h"			/* CHK_DialType() */
#include	"\src\memsw\define\mems_pro.h"				/*1996/04/17 Eguchi */
#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1997/07/19 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* MDM_DTMF_Tx() */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"	/* DTMF_ASTA, DTMF_SHARP */
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"	/* MDM_DTMF_Tx() */
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"	/* DTMF_ASTA, DTMF_SHARP */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if  (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"	/* MDM_DTMF_Tx() */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"	/* DTMF_ASTA, DTMF_SHARP */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_DTMF_Tx() */
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* DTMF_ASTA, DTMF_SHARP */
#endif

#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"		/*	リレー関係	*/
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\std.h"					/* OK,NG */
#include	"\src\atlanta\define\status.h"				/*	LINE_TYPE_TONE,DIAL_SPEED_20PPS	*/
#include	"\src\memsw\define\mem_sw_a.h"				/*1996/04/17 Eguchi */
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mntsw_d.h"				/* 1997/06/05  By T.Yamaguchi */
#include	"\src\atlanta\define\cmn_pro.h"

#include	"\src\atlanta\ext_v\atd_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"				/* SYS_DialChange */
#include	"\src\atlanta\ext_v\BKUPRAM.H"				/* 1997/06/05  By T.Yamaguchi */

#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\define\cl1_def.h"
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* 1999/02/22 by T.Soneoka */
 #if defined(POPLAR_F)
	#include "\src\atlanta\sh7043\ext_v\extv_mon.h"
 #else
	#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
 #endif
#endif
#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"
#endif

/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/12 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
extern UBYTE UAE_PIN_FirstSharpCode;	/* UAE ARAMCO PIN By O.Kimoto 1997/04/16 */
extern UBYTE CHK_UNI_AramcoPinNotMasking(void);
#endif

#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
#include	"\src\atlanta\ext_v\ncu_data.h"
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
/*************************************************************************
	module		:[パルスダイヤル番号一桁を回線に送出するタスク]
	function	:[
	]
	common		:[
	]
	condition	:[]
	comment		:[
	・SAKAKIのSCN_Open()時にIDPの設定に時間がかかっている
	・naganoから移植した
	]
	return		:[
	]
	machine		:[]
	language	:[]
	keyword		:[ATD]
	date		:[2000/10/18]
	author		:[吉川弘康]
*************************************************************************/
struct ATD_DialPulse_t {
	UWORD MakeTime;
	UWORD BreakTime;
	UBYTE DialNumber;		/*回線に送出したい値*/
} ATD_DialPulseData;

void ATD_DialPulseTask(void)
{
	struct ATD_DialPulse_t *dialpulse_ptr = &ATD_DialPulseData;
	UWORD MakeTime;
	UWORD BreakTime;
	UBYTE DialNumber;

	MakeTime = dialpulse_ptr->MakeTime;
	BreakTime = dialpulse_ptr->BreakTime;
	DialNumber = dialpulse_ptr->DialNumber;		/*回線に送出したい値*/

	wai_sem(semno.ATD_PulseDialer);
	/*-------------*/
	/*ﾀﾞｲｱﾙﾊﾟﾙｽ送出*/
	/*-------------*/
	while (DialNumber--) {
  #if (PRO_NCU_TYPE == SAKAKI_TYPE) /* Changed by H.Kubo 1998/07/03 */
		CML_RelayOff();
		wai_oneshot(BreakTime);
		CML_RelayOn();
		wai_oneshot(MakeTime);
  #else
    #if (PRO_NCU_TYPE == HINOKI_TYPE)
  /*
  ** HINOKIはJPNでCMLリレーをON/OFFする changed by H.Hirao 1998/11/16
  */
      #if defined(JPN)
		CML_RelayOff();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(BreakTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(BreakTime);
		}
		else {
			wai_tsk((UWORD)((BreakTime / 10) + 1));
		}
        #endif
		CML_RelayOn();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(MakeTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(MakeTime);
		}
		else {
			wai_tsk((UWORD)((MakeTime / 10) + 1));
		}
        #endif
      #else /* JPN */
		DP_RelayOff();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(BreakTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(BreakTime);
		}
		else {
			wai_tsk((UWORD)((BreakTime / 10) + 1));
		}
        #endif
		DP_RelayOn();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(MakeTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(MakeTime);
		}
		else {
			wai_tsk((UWORD)((MakeTime / 10) + 1));
		}
        #endif
      #endif
    #else
		DP_RelayOff();
		wai_oneshot(BreakTime);
		DP_RelayOn();
		wai_oneshot(MakeTime);
    #endif
  #endif

/* 以下はnaganoのソースです。参考のため、おいてます。2000/10/18 H.Yoshikawa */
#if (0)
//#if (PRO_NCU_TYPE == USA_TYPE) || (PRO_NCU_TYPE == JPN_TYPE)
//		CML_RelayOff();
//		wai_oneshot(BreakTime);
//		CML_RelayOn();
//		wai_oneshot(MakeTime);
//#else	/* GBR_TYPE */
//		DP_RelayOff();
//		wai_oneshot(BreakTime);
//		DP_RelayOn();
//		wai_oneshot(MakeTime);
//#endif
#endif
	}
	sig_sem(semno.ATD_PulseDialer);
	wai_tsk(0xffff); /* changed by H.Kubo 1999/12/27 */
}

void ATD_StopDialPulse(void)
{
	if (tskno_ATD_DialPulseTask != 0xffff) { /* added by H.Kubo 1999/12/27 */
		del_tsk(&tskno_ATD_DialPulseTask);
	}
}

#endif

/*************************************************************************
	module		:[電話番号一桁を回線に送出]
	function	:[
	]
	common		:[
		SYS_DialChange	:パルス－＞トーンに回線タイプ変更
	]
	condition	:[]
	comment		:[]
	return		:[
		1	:OK
		0	:NG(ループ電流チェックでＮＧ)
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/
UBYTE	OutPutDial(	UBYTE	Number)		/*Number : ASCii文字*/
{
	UBYTE DialNumber = 0;		/*回線に送出したい値*/

	UWORD MakeTime = 0;
	UWORD BreakTime = 0;
	UWORD MiniPause = 0;

	DialNumber = AsciiToDialNumber(Number);
	/*------------------------*/
	/*回線ﾀｲﾌﾟがDTMFの時の処理*/
	/*------------------------*/
#if (PRO_CLASS1 == ENABLE)		/* Add By M.Tachibana 1995/12/25 */
	if (((CL1_ATD_DialType == 0x00) && (CHK_DialType() & LINE_TYPE_TONE))
	 || (CL1_ATD_DialType == 'T')
	 || SYS_DialChange) {
#else
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (((SYS_InternalLineNumber == SYS_STD_LINE_COM)	/**	標準ライン通信中	*/
	&&  ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange))
	||  ((SYS_InternalLineNumber == SYS_EXT_LINE_COM)	/**	拡張ライン通信中	*/
	&&  ((CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) || SYS_DialChange))) {
#else
	if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {
#endif
#endif

/* ＵＡＥ ＡＲＡＭＣＯ社 ＰＩＮ対応 1998/03/11 Y.Matsukuma */
#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
		if (CMN_CheckAramcoModel() == 1) {
			/* ユニークスイッチＡ：１－０が０（＝ＯＮ）ならば、ＰＩＮコードのマスクをする。
			** その際、最初に見つけた＃は発呼しない
			** by O.Kimoto 1997/05/21
			*/
			if (CHK_UNI_AramcoPinNotMasking() == 0) {	/* ARAMCO PIN By O.Kimoto 1997/05/21 */
				if (DialNumber == 0x0B) { /* 0x0B is a "#" of a murata BCD Code. */
					if (UAE_PIN_FirstSharpCode == 0) {
						UAE_PIN_FirstSharpCode = 1;	/** 最初の”＃”検出 */
						return(OK);
					}
					else {
						UAE_PIN_FirstSharpCode = 2;	/** ＰＩＮの終了をあらわす”＃”検出 */
					}
				}
			}
		}
#endif

		MakeTime = (UWORD)(((struct DialParameters_t *)CTRY_DialTable())->MakeDTMF);	 /*DTMF送出*/ /* For RISC T.Nose 1995/12/14 */
		BreakTime = (UWORD)(((struct DialParameters_t *)CTRY_DialTable())->BreakDTMF);

		/* 申請用にMake時間とBreak時間を設定できる様に、変更 1997/06/20  By T.Yamaguchi */
		if (SYB_MaintenanceSwitch[MNT_SW_D1]) {	/* ﾒｰｸ時間が設定されていたら */
			MakeTime = (UWORD)(SYB_MaintenanceSwitch[MNT_SW_D1]);	/* 1～9の場合は10ms単位 */
		}
		if (SYB_MaintenanceSwitch[MNT_SW_D2]) {	/* ﾌﾞﾚｰｸ時間が設定されていたら */
			BreakTime = (UWORD)(SYB_MaintenanceSwitch[MNT_SW_D2]); /* 1ms単位 */
		}
#if(PRO_MODEM == ORANGE3)
		/*
		** DTMF送出時にノイズがのるため送出時にMuteOFFの処理を追加したため10msｳｪｲﾄおくので
		** BreakTimeを10ms引いてセットする MDM_DTMF(UBYTE)の中でｳｪｲﾄしている 1997/06/20  By T.Yamaguchi
		*/
		if (BreakTime > 10) {
			BreakTime = BreakTime - 10;
		}
#endif

		MDM_DTMF_Tx(DialNumber, MakeTime);	 /*DTMF送出*/ /* For RISC T.Nose 1995/12/14 */

/*
** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
** 確認して使用することにする
** 1999/02/22 by T.Soneoka
*/
#if (PRO_NCU_TYPE == HINOKI_TYPE)
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(BreakTime);
		}
		else {
			wai_tsk((UWORD)((BreakTime / 10) + 1));
		}
#else
		wai_oneshot(BreakTime);
#endif
		return(OK);	  /*OK*/
	}
	/*--------------------------*/
	/*回線ﾀｲﾌﾟがPULSEで20PPSの時*/
	/*--------------------------*/
#if (PRO_CLASS1 == ENABLE)		/* Add By M.Tachibana 1995/12/25 */
	if (((CL1_ATD_DialType == 0x00) && (CHK_DialType() & DIAL_SPEED_20PPS))
	 || ((CL1_ATD_DialType == 'P') && (CL1DialPulseSpeed == DIAL_SPEED_20PPS))) {
#else
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (((SYS_InternalLineNumber == SYS_STD_LINE_COM)	/**	標準ライン通信中	*/
	&&  (CHK_DialType() & DIAL_SPEED_20PPS))
	||  ((SYS_InternalLineNumber == SYS_EXT_LINE_COM)	/**	拡張ライン通信中	*/
	&&  (CHK_DialTypeExt() & DIAL_SPEED_20PPS_EXT))) {
#else
	if (CHK_DialType() & DIAL_SPEED_20PPS) {
#endif
#endif
		MakeTime = ((struct DialParameters_t *)CTRY_DialTable())->Make20;
		BreakTime = 50 - MakeTime;		/*（注）松竹桜では48*/
		MiniPause = ((struct DialParameters_t *)CTRY_DialTable())->MiniPause20;
	}
	/*--------------------------*/
	/*回線ﾀｲﾌﾟがPULSEで10PPSの時*/
	/*--------------------------*/
	else {
		if ((SYB_MaintenanceSwitch[MNT_SW_D3] != 0)		/* １～１００までの値が入っていたら */
		 && (SYB_MaintenanceSwitch[MNT_SW_D3] < 100)) {	/* 1997/05/29  By T.Yamaguchi */
			MakeTime = (UWORD)(SYB_MaintenanceSwitch[MNT_SW_D3]);
		}
		else {
			MakeTime = ((struct DialParameters_t *)CTRY_DialTable())->Make10;
		}
#if defined(FRA) 	/* 95/04/24 by M.HARADA */
		BreakTime = 99 - MakeTime;		 /*（注）松竹桜では98*/
#else

	#if (PRO_NCU_TYPE == ANZU_USA_TYPE)
		BreakTime = 100 - MakeTime;		 /* ANZU_L */
	#else
		BreakTime = 101 - MakeTime;		 /* POPLAR変更 97/06/24 By T.Yamaguchi */
	#endif

#endif
		MiniPause = ((struct DialParameters_t *)CTRY_DialTable())->MiniPause10;
	}

	/*----------------------------------------*/
	/*ﾀﾞｲｱﾙ番号とPULSE送出回数の違いを補う処理*/
	/*----------------------------------------*/
	switch (CHK_DP_Method()) {
	case	DIAL_SWE_TYPE:
		DialNumber += 1;
		break;
	case	DIAL_NZL_TYPE:
		DialNumber = (UBYTE)(10 - DialNumber);
		break;
	default	:
		if (DialNumber == 0) {
			DialNumber = 10;
		}
	}
	/*-----------------------*/
	/**PULSE送出用のﾘﾚｰを引く*/
	/*-----------------------*/
	if (IsDialFirstNum) {	/**１番最初のダイヤル番号を送出する時(ダイアル中のトーン検出の後も該当)	*/
		DP_RelayOn();
		wai_tsk(1);									/**	リレーが安定するまで１０ｍｓ待つ	*/
		S_RelayOn();
		wai_tsk(((struct DialParameters_t *)CTRY_DialTable())->PrePause / 10);	/*	プレポーズ	*/
		IsDialFirstNum = 0;
	}
	else {
		/*--------------------------------------------------------------------------*/
		/* 注意!! ﾃｰﾌﾞﾙにｾｯﾄするﾐﾆﾏﾑﾎﾟｰｽﾞの値は（実値 - (S_RelayOnTime+S_RelayOffTime))*/
		/*--------------------------------------------------------------------------*/
		if (((struct DialParameters_t *)CTRY_DialTable())->S_RelayOnTime != 0) {	/**	S_Relayを引くか？	*/
			S_RelayOn();
			wai_tsk(((struct DialParameters_t *)CTRY_DialTable())->S_RelayOnTime / 10);	/*	Ｓリレーが安定するまでのポーズ	*/
		}
	}
	/*-------------*/
	/*ﾀﾞｲｱﾙﾊﾟﾙｽ送出*/
	/*-------------*/
#if 0 /* (PRO_NCU_TYPE == MOMIJI_TYPE) */
	CML_RelayOff();
#endif

#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
	OneDigitDiallingExecute = 1;
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
	if (tskno_ATD_DialPulseTask != 0xffff) { /* added by H.Kubo 1999/12/27 */
		del_tsk(&tskno_ATD_DialPulseTask);
	}
	ATD_DialPulseData.MakeTime = MakeTime;
	ATD_DialPulseData.BreakTime = BreakTime;
	ATD_DialPulseData.DialNumber = DialNumber;
	cre_tsk(&tskno_ATD_DialPulseTask, TSK_ATD_DIALPULSETASK, 0);
	wai_sem(semno.ATD_PulseDialer);	 /* セマフォでダイヤルパルス送出終了までの同期を取る */
	sig_sem(semno.ATD_PulseDialer);
	ATD_StopDialPulse();
#else	/* (PRO_DIAL_PULSE_TASK == ENABLE) */
	while (DialNumber--) {
  #if (PRO_NCU_TYPE == SAKAKI_TYPE) /* Changed by H.Kubo 1998/07/03 */
		CML_RelayOff();
		wai_oneshot(BreakTime);
		CML_RelayOn();
		wai_oneshot(MakeTime);
  #else
    #if (PRO_NCU_TYPE == HINOKI_TYPE)
  /*
  ** HINOKIはJPNでCMLリレーをON/OFFする changed by H.Hirao 1998/11/16
  */
      #if defined(JPN)
		CML_RelayOff();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(BreakTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(BreakTime);
		}
		else {
			wai_tsk((UWORD)((BreakTime / 10) + 1));
		}
        #endif
		CML_RelayOn();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(MakeTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(MakeTime);
		}
		else {
			wai_tsk((UWORD)((MakeTime / 10) + 1));
		}
        #endif
      #else /* JPN */
		DP_RelayOff();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(BreakTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(BreakTime);
		}
		else {
			wai_tsk((UWORD)((BreakTime / 10) + 1));
		}
        #endif
		DP_RelayOn();
		/*
		** ＨＩＮＯＫＩにて、発着衝突でwai_oneshot()が同時に呼ばれてしまうパスが存在し、リセットに飛ぶ
		** 現在のところ原因は分かっていないが、最悪リセットに飛ぶのを防ぐため、wai_oneshotが使用されていないかどうか
		** 確認して使用することにする
		** 1999/02/22 by T.Soneoka
		*/
        #if (0)
		**		wai_oneshot(MakeTime);
        #else
		if (wai_1shot_tid == 0xFF) {
			wai_oneshot(MakeTime);
		}
		else {
			wai_tsk((UWORD)((MakeTime / 10) + 1));
		}
        #endif
      #endif
    #else
		DP_RelayOff();
		wai_oneshot(BreakTime);
		DP_RelayOn();
		wai_oneshot(MakeTime);
    #endif
  #endif
	}
#endif	/* (PRO_DIAL_PULSE_TASK == ENABLE) */

#if 0 /* (PRO_NCU_TYPE == MOMIJI_TYPE) */
	CML_RelayOn();
#endif
	if (((struct DialParameters_t *)CTRY_DialTable())->S_RelayOffTime != 0) {	/**	S_Relayを戻すか？	*/
		S_RelayOff();
		wai_tsk(((struct DialParameters_t *)CTRY_DialTable())->S_RelayOffTime / 10);	/*	Ｓリレーが安定するまでのポーズ	*/
	}

#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
	/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
	OneDigitDiallingExecute = 0;
#endif

	/*----------------------------------------*/
	/*ミニマムポーズ  &	 ﾀﾞｲｱﾙ中のﾙｰﾌﾟ電流ﾁｪｯｸ*/
	/*----------------------------------------*/
	if (!LoopCurrentCheck(MiniPause)) {
		return(NG);	  /*ﾙｰﾌﾟ電流が無い = NG*/
	}
	return(OK);
}
/*************************************************************************
	module		:[アスキー文字をダイアル番号に変換]
	function	:[
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	return		:[
		ダイアル番号
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD]
	date		:[1993/12/6]
	author		:[奥村明]
*************************************************************************/

/*---------------------------*/
/*ｱｽｷｰ文字をﾀﾞｲｱﾙ番号に変える*/
/*---------------------------*/
UBYTE AsciiToDialNumber(UBYTE Number)
{
	switch(Number) {
	case '*':
		return(DTMF_ASTA);
	case '#':
		return(DTMF_SHARP);
	default:
		return(Number & (UBYTE)0x0f);
	}
}
