/* ---------------------------------------------------------------------------------------- */
/*		ﾌﾟﾛｼﾞｪｸﾄ:ATLANTA																	*/
/*		ﾓｼﾞｭｰﾙ	:void	ATD_FilterOnOffDetectTask(UBYTE *)									*/
/*		作成者	:山口																		*/
/*		日付	:1996/10/31																	*/
/*		概要	:																			*/
/*				 \SRC\KOBE\ANZU\SRC\ATD_FREQ.Cを流用しました								*/
/*		修正履歴:																			*/
/*------------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\ctry_pro.h"	/* CTRY_?Tone() */
#include "\src\atlanta\define\mon_pro.h"	/* モニタコール */
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\atd_def.h"
#include "\src\atlanta\define\std.h"	/* 1997/06/05  By T.Yamaguchi */
#if (PRO_MODEM == R288F) /* Changed by H.Kubo 1997/07/19 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"	/* mdm_data.hのundefを避けるため */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h" /* モデムのレジスタを見るため */
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"	/* mdm_data.hのundefを避けるため */
#include "\src\atlanta\mdm\r288f\define\mdm_def.h" /* モデムのレジスタを見るため */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"	/* mdm_data.hのundefを避けるため */
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"	/* MDM_ZX_WriteRAM, MDM_LevelWriteRAM */
#include "\src\atlanta\mdm\orange\define\mdm_def.h" /* モデムのレジスタを見るため */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* MDM_FilterSet() */
#endif

#include "\src\atlanta\define\cmn_pro.h" /* By S.Kawasaki 1996/03/07 *//* inp() */

#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\uni_pro.h"

#include "\src\atlanta\ext_v\atd_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"

#include "\src\atlanta\sh7043\define\def_evtn.h" /* By S.Kawasaki 1996/03/07 */	/* イベント関係 */
#include "\src\atlanta\ext_v\BKUPRAM.H"			/* 1997/06/05  By T.Yamaguchi */
#include "\src\atlanta\define\mntsw_d.h"		/* 1997/06/05  By T.Yamaguchi */

#if (PRO_MODEM == ORANGE3)
/*************************************************************************
	module		:[トーン周波数監視タスク]
	function	:[
		1.５０ｍｓ毎にフィルターを通過したトーンの周波数(MDM_ZX_WriteRAM)を指定周波数と比較し、イベント発生
	]
	return		:[]
	common		:[]
	condition	:[
		全てのトーン検出タスクから生成される
	]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[ATD]
	date		:[1994/10/17]
	author		:[奥村明/山口]
*************************************************************************/
void	ATD_FilterOnOffDetectTask(UBYTE *ToneDetectType)
{
	UBYTE table_cnt = 0;
	UBYTE table_max	= 0;
	UBYTE loop	= 0;
	UBYTE is_cng_detect_on_ansfax = 0;		/* Add By t.yamaguchi 95.12.02 */
	UBYTE filter_status = 0;
#if defined(FRA)
	UBYTE zx_modify_flag = 0;	/* add by M.HARADA '96/12/18 */
#endif
	UBYTE minmun_level = 0;		/* 1997/06/05  By T.Yamaguchi */
	UBYTE is_cmpare_uni_sw_level = FALSE;

#if (PRO_SPEED_EX == ENABLE)
	UBYTE spd_tone_type = 0;

	struct	ToneParameters_t	*ToneTable[5]; /* SPD 95.10.24 By.T.Y */
#else
	struct	ToneParameters_t	*ToneTable[4];
#endif

	/* デバッグ用 */
	FCM_Is_ToneDetecting = YES;	/* 1997/09/11  By T.Yamaguchi */

	table_max = 0;
	is_cmpare_uni_sw_level = FALSE;
	
	switch (*ToneDetectType) {
	case	BEFORE_DIAL_DETECT:		/*	DIALTONE, BUSYTONE, CON_TONE	*/
		ToneTable[table_max] = (struct ToneParameters_t *)CTRY_DialTone();	/* ダイヤルトーン */
#if defined(FRA)	/* FRA仕様 */
#else
		if(FCM_PtnrChkBusyToneDetect()) {
			table_max++;
			ToneTable[table_max] = (struct ToneParameters_t *)CTRY_BusyTone(); /* ビジートーン */
		}
		if(CHK_UNI_ConToneDetect()) {
			table_max++;
			ToneTable[table_max] = (struct ToneParameters_t *)CTRY_CongestionTone(); /* ｺﾝｼﾞｪｼｮﾝﾄｰﾝ */
		}
#endif
		table_max++;
		/* 検出レベルの設定をﾒﾝﾃﾅﾝｽｽｲｯﾁで調整できる様にする 1997/06/05  By T.Yamaguchi */
		if (SYB_MaintenanceSwitch[MNT_SW_D4]) {
			minmun_level = SYB_MaintenanceSwitch[MNT_SW_D4];
			is_cmpare_uni_sw_level = TRUE;
		}
		break;
	case	AFTER_DIAL_DETECT:		/*	BUSYTONE, CON_TONE, DIS_TONE, CED_TONE	(SPD_TONE) */
		ToneTable[table_max] = &DIS_Tone;	/* DIS */
#if (PRO_CED_DETECT == ENABLE)	/* 日立特許回避 By M.Tachibana 1998/04/14 */
		if (CHK_CED_Detect()) {
			table_max++;
			ToneTable[table_max] = &CED_Tone;	/* CED */
		}
#endif
		if (FCM_PtnrChkBusyToneDetect()) {
			table_max++;
			ToneTable[table_max] = (struct ToneParameters_t *)CTRY_BusyTone();	/* BUSY */
		}
		if(CHK_UNI_ConToneDetect()) {
			table_max++;
			ToneTable[table_max] = (struct ToneParameters_t *)CTRY_CongestionTone(); /* CONGESTION */
		}
#if (PRO_SPEED_EX == ENABLE)
		if ((SpeedHandshakeRomCheck()) &&
			 (CHK_UNI_SpeedHandshakeEx())) {
			table_max++;
			spd_tone_type = CHK_UNI_ArrivalSignalToneType();
			ToneTable[table_max] = &SPD_Tone[spd_tone_type];		/* 0:2100Hz,1:697Hz,2:770Hz,3:852Hz */
		}
#endif
		table_max++;
		/* 検出レベルの設定をﾒﾝﾃﾅﾝｽｽｲｯﾁで調整できる様にする 1997/06/05  By T.Yamaguchi */
		if (SYB_MaintenanceSwitch[MNT_SW_D5]) {
			minmun_level = SYB_MaintenanceSwitch[MNT_SW_D5];
			is_cmpare_uni_sw_level = TRUE;
		}
		break;
	case	CNG_DETECT:
		table_max = 1;			/*	CNG_TONE	*/
		ToneTable[0] = &CNG_Tone;
		break;
	case	DIAL2TONE_DETECT:
		table_max = 1;			/*	DIAL2TONE	*/
		ToneTable[0] = (struct ToneParameters_t *)CTRY_Dial2ndTone();
		/* 検出レベルの設定をﾒﾝﾃﾅﾝｽｽｲｯﾁで調整できる様にする 1997/06/05  By T.Yamaguchi */
		if (SYB_MaintenanceSwitch[MNT_SW_D6]) {
			minmun_level = SYB_MaintenanceSwitch[MNT_SW_D6];
			is_cmpare_uni_sw_level = TRUE;
		}
		break;
	case	F_NET_TONE_DETECT:
		table_max = 1;
		ToneTable[0] = &F_Net_Tone;
		break;
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	case	MERCURY_DETECT:			/*	1994/12/2	追加by A.O	GBRのみ	*/
		table_max = 1;
		ToneTable[0] = &MercuryTone;
		break;
#endif
	case	ANS_FAX_CNG_DETECT:					/* Add By t.yamaguchi 95.12.02 */
		table_max = 1;			/*	CNG_TONE	*/
		ToneTable[0] = &CNG_Tone;
		is_cng_detect_on_ansfax = 1;
		break;
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
	case	MODE_CHANGE_CNG_DETECT:
		table_max = 1;
		ToneTable[0] = &Mode_CNG_Tone;
		break;
#endif
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/11  By T.Yamaguchi */
	case	CNG_BUSY_DETECT:
		table_max = 2;			/*	CNG_TONE	*/
		ToneTable[0] = &VoiceCNG_Tone;
		ToneTable[1] = &PhaseB1_Busy; /* ビジートーン */
		break;
	case	FSK_OR_BUSY_DETECT:
		table_max = 2;			/*	CNG_TONE	*/
		ToneTable[0] = &DIS_Tone;
		ToneTable[1] = &PhaseB1_Busy; /* ビジートーン */
		break;
#endif
	default:
		/* ここに来たらバグ */
		break;
	}
#if defined(FRA)	/* add by M.HARADA '96/11/22 */
	zx_modify_flag = 0;		/* add by M.HARADA '96/12/18 */
#endif


	for(;;) {
		for(;;) {
			for (loop = 0; loop < table_max; loop++) {
				if (ToneTable[table_cnt]->DetectCycle == 0) {	/*	タスクが生成されていない時	*/
					table_cnt++;								/*	比較するトーンテーブルを１つ進める	*/
				}
				else {											/*	タスクが生成されている時	*/
					break;										/*	周波数比較の為抜ける	*/
				}
				if (table_cnt == table_max) {		/*	すべてのトーン検出タスクが生成されていない時	*/
					wai_tsk(0xFFFF);				/*	無限スリープ	*/
				}
			}
			if (is_cng_detect_on_ansfax == 1) {				/* Add By t.yamaguchi 95.12.02 */
				/** ポートのＯＮは、一定幅連続した時ＣＮＧと見なします	Add by t.yamaguchi 95.12.02 */
				if ( inp(ModemBasicControl) & MDMSTS0_D1080_BIT ) {
					filter_status = 1;
				}
				else {
					filter_status = 0;
				}
			}
			else {
#if defined(FRA)	/* add by M.HARADA '96/11/22 */
				if(*ToneDetectType == BEFORE_DIAL_DETECT || *ToneDetectType == DIAL2TONE_DETECT){
					if((MDM_PrevDataZX <= ToneTable[table_cnt]->MaxFrequency)
					 &&(MDM_PrevDataZX >= ToneTable[table_cnt]->MinFrequency)
					 &&(MDM_ZX_WriteRAM < ToneTable[table_cnt]->MinFrequency)
					 &&(MDM_ZX_WriteRAM >= 11)	/* 15 -> 11 by M.H 98/03/20 */
					 &&(zx_modify_flag <= 1) ){		
						MDM_ZX_WriteRAM = 44;		/* 有効周波数帯域のセンター値 */
						MDM_LevelWriteRAM = 25;		/* 有効レベル帯域のセンター値 */
						zx_modify_flag ++;			/* add by M.HARADA '96/12/18 */
					}
				}
#endif

				if (is_cmpare_uni_sw_level == FALSE) {
					if (((ToneTable[table_cnt]->MinFrequency <= MDM_ZX_WriteRAM) && (MDM_ZX_WriteRAM <= ToneTable[table_cnt]->MaxFrequency))
					 && (((ToneTable[table_cnt]->MaxLevel <= MDM_LevelWriteRAM) && (MDM_LevelWriteRAM <= ToneTable[table_cnt]->MinLevel))
					  || (ToneTable[table_cnt]->MinLevel == 0)) )	 {	/*	指定範囲の周波数の時	*/
						filter_status = 1;
					}
					else {
						filter_status = 0;
					}
				}
				else {	/* ﾒﾝﾃﾅﾝｽｽｲｯﾁの値のレベルを比較する場合 申請時に使用 */
					if (((ToneTable[table_cnt]->MinFrequency <= MDM_ZX_WriteRAM) && (MDM_ZX_WriteRAM <= ToneTable[table_cnt]->MaxFrequency))
					 && (MDM_LevelWriteRAM <= minmun_level) )	 {	/*	指定範囲の周波数の時	*/
						filter_status = 1;
					}
					else {
						filter_status = 0;
					}
				}
			}
			if (filter_status){
				switch (ToneTable[table_cnt]->FilterType) {
				case	1:
					det_evt(EVT_TONE_FILTER1_ON);
					break;
				case	2:
					det_evt(EVT_TONE_FILTER2_ON);
					break;
				case	3:
					det_evt(EVT_TONE_FILTER3_ON);
					break;
				}
			}
			else {		/*	指定範囲外の周波数の時	*/
				switch (ToneTable[table_cnt]->FilterType) {
				case	1:
					det_evt(EVT_TONE_FILTER1_OFF);
					break;
				case	2:
					det_evt(EVT_TONE_FILTER2_OFF);
					break;
				case	3:
					det_evt(EVT_TONE_FILTER3_OFF);
					break;
				}
#if defined(FRA)
				zx_modify_flag = 0;
#endif
			}
			if ((UBYTE)(table_cnt + 1) == table_max) {
				break;
			}
			table_cnt++;
		}
		table_cnt = 0;
#if defined(FRA)
		if(*ToneDetectType == BEFORE_DIAL_DETECT || *ToneDetectType == DIAL2TONE_DETECT){
			wai_tsk(1);
		} else {
			wai_tsk(5);
		}
#else
		wai_tsk(5);		/* 50ms wait	*/
#endif
	}
}
#else /* (PRO_MODEM == ORANGE3) */
void	ATD_FilterOnOffDetectTask(UBYTE *ToneDetectType) {}
#endif /* (PRO_MODEM == ORANGE3) */
