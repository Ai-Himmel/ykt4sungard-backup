/************************************************************************
*				BY:	S.Kawasaki, M.Kotani
*			  DATE:	Mar.29,1993, 1996/10/11
*		 Copy Date: 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 FILE NAME:	man_init.c
*	   DESCRIPTION:	PowerOn時に初期化するRAM
*	   MODULE NAME:	MAN_InitializeRAM()
*				  :	MAN_InitializeMailBox()
*				  :	InitializeMachineStatus()
*				  :	MAN_InitializeTaskValue()
*				  :	MAN_InitializeSemapho()
*				  :	MAN_InitializeDevice()
*				  :	MAN_InitializeTaskCreate()
*				  :	MAN_MultiLinePowerOnInitial()
*				  :	ClearOptionModemDataArea()
*		 REFERENCE:	void far MAN_Task(void)よりCallされる
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\mntsw_a.h"
#include	"\src\atlanta\define\mntsw_b.h"
#include	"\src\atlanta\define\mntsw_h.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sysmjnl.h"
#include	"\src\atlanta\sh7043\define\cpu_def.h"
#include	"\src\atlanta\sh7043\define\SH_PORT.h"
/*MON*/
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\def_semn.h"
/*CDC*/
#include	"\src\atlanta\define\cdc_def.h"
/*MDM*/
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#else
#endif
/*DMA*/
#include	"\src\atlanta\define\dma_def.h"	/* 1996/12/11 T.Nose */

/*参照ファイル*/
/*SYS*/
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\ext_v\man_data.h"
#include	"\src\atlanta\ext_v\cpu_tbl.h"
#include	"\src\atlanta\ext_v\mlt_data.h"
/*MON*/
#include	"\src\atlanta\sh7043\ext_v\extv_sem.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
/*CDC*/
#include	"\src\atlanta\ext_v\cdc_data.h"
/*MDM*/
/*PAT*/
#if (PRO_PAT_JOURNAL == ENABLE)
#include	"\src\atlanta\ext_v\pat_data.h"
#endif
/*FCM*/
#include	"\src\atlanta\ext_v\fcm_data.h"

#if defined (KEISATSU) /* 警察FAX 05/06/09 石橋正和 */
#include "\src\atlanta\define\s1_pro.h"
#endif

/*MDM*/
#if (PRO_MODEM == ORANGE3) /* #if condition is added by H.Kubo 1997/11/05 */
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/11/05 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif
/*LST*/
#include	"\src\atlanta\ext_v\lst_data.h"
/*NCU*/
#include	"\src\atlanta\ext_v\ncu_data.h"
/*SCN*/
#include	"\src\atlanta\ext_v\scn_data.h"
#include	"\src\atlanta\define\mntsw_c.h" /* ミラーキャリッジ待機位置切替え可能仕様デバッグ */
#if (PRO_FBS == ENABLE)
#include	"\src\atlanta\define\sysscan.h"
#endif
#if defined(SATSUKI2)
#include "\src\atlanta\satsuki2\ext_v\scn_tbl.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h" /* 先端読取り位置微調整を有効にする為 Add by Y.Kano 2004/01/09 */
#endif
#if defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_tbl.h"
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h" /* 先端読取り位置微調整を有効にする為 Add by Y.Kano 2004/01/09 */
#endif

/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\ext_v\prn_data.h"
#include	"\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#elif (PRO_PRINT_TYPE == THERMAL) /*Smuratec H.C.H 2003.07.11*/
 #if defined(STOCKHM2)			/* Modify by SMuratec K.W.Q 2004/05/18 */
#include	"\src\atlanta\prt\lv_therm\ext_v\prn_data.h"
#include	"\src\atlanta\prt\lv_therm\ext_v\prn_tbl.h"
 #else
#include	"\src\atlanta\prt\iu_therm\ext_v\prn_data.h"
#include	"\src\atlanta\prt\iu_therm\ext_v\prn_tbl.h"
 #endif
#else
#include	"\src\atlanta\prt\sp322\ext_v\prn_data.h"
#include	"\src\atlanta\prt\sp322\ext_v\prn_tbl.h"
#endif
/*DMA*/
#include	"\src\atlanta\ext_v\dma_data.h"	/* 1996/12/11 T.Nose */
#include	"\src\atlanta\ext_v\cmn_data.h"	/* 1996/11/19 T.Nose */
#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
#include	"\src\atlanta\ext_v\atd_data.h"
#endif

/*プロトタイプ宣言*/
/*#include	"\src\memsw\define\mems_pro.h"*/
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"

	/*#include	"\src\atlanta\define\scn_pro.h"*/
	void	SCN_SetBuzzer( UBYTE );
	void	SCN_Init( void );
	void	SCN_GeneratePrinter1KHz( void );


#if (PRO_PANEL == ANK)	/* 1996/10/25 by K.Watanabe */
	/*#include	"\src\atlanta\opr\ank\define\opr_pro.h"*/
	void	OPR_Initial(void);
	void	LCD_Initialize(void);
	void	DisplayWaitAMinutes(void);
#endif
#if (PRO_PANEL == KANJI)	/* Added by H.Kubo 1997/08/13 */
#include	"\src\atlanta\opr\kanji\define\opr_pro.h"
#endif
#if (PRO_DPRAM == ENABLE)
	void DPRD_InitializeInterface(void);
#endif
#if (PRO_MULTI_LINE == ENABLE)
#include "\src\atlanta\define\mlt_pro.h"
#endif
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\define\cl1_pro.h"
void	CL1_RSHardWareCheck( void );
#endif
#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\define\prn_pro.h"
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1998/06/13 H.Yoshikawa */
#include	"\src\atlanta\define\sysprint.h"
#include	"\src\atlanta\sakaki\define\gaio_pro.h"
#endif

#if (PRO_PRINT_TYPE == THERMAL)	/*  By O.Kimoto 1998/09/22 */
#include	"\src\atlanta\define\sysprint.h"
#endif

#if defined(SATSUKI2) || defined(STOCKHM2)	/* Add by Y.Kano ローカルに反映 2003/12/04 */
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif

#if (PRO_SCN_CODEC_TYPE == IDP301)	/* 1998/06/29 H.Yoshikwa */
void SCN_Initial(void);
#endif

/* MDM */
	void	CreateModemBufferSem(void);
	void	MemoryMove(register UBYTE	*src_adr,register UBYTE	*tgt_adr,UWORD	cnt);

#if (PRO_MODEM == R288F)	/* ROCKWELL製 28.8K */
#include "\src\atlanta\define\cmn_pro.h"
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h" /* added by H.Kubo 1997/11/05 */
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h" /* added by H.Kubo 1997/11/05 */
 #endif
extern UBYTE	Exist288Modem(void);
#endif

#if (PRO_RING_MASTER == ENABLE)	/* 1998/01/06 */
#include	"\src\atlanta\define\ncu_cnst.h"
#endif

#if defined(SATSUKI2) /* checker key scan O.Oshima 2003/10/24 */
#include "\src\atlanta\satsuki2\define\m_param.h"
#include "\src\atlanta\define\status.h"	/* Add by Y.Kano 2004/01/07 */
#endif

#if defined(STOCKHM2)
#include "\src\atlanta\stockhm2\define\m_param.h"
#include "\src\atlanta\define\status.h"	/* Add by Y.Kano 2004/01/07 */
#endif

#if defined(HINOKI2) || defined(HINOKI3) /* Add by 2004/01/14 */
#include "\src\atlanta\hinoki\define\m_param.h"
#include "\src\atlanta\define\status.h"
#endif

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
#include "\src\atlanta\define\sys_line.h"
#endif /* defined (KEISATSU) */

/* DTC */
void DMA_DTC_Initialize(void);	/* 1997/08/19  By T.Yamaguchi */

void SetJunkOwnDial(void);	/* 1997/10/23  By T.Yamaguchi */

/* メモリー送信原稿降誕縮む件 T.Nose 1997/11/03 */
extern UBYTE DEBUG_DocumentScanning;

/* E設 中西さんからの依頼 Busy Flag がこけない時LCDCをリセットする T.Nose 1997/12/01 */
#include "\src\atlanta\opr\ank\ext_v\opr_data.h"

#if (PRO_CIPHER == ENABLE) || (PRO_EXT_ROM == ENABLE)	/*	By Y.Suzuki 1997/12/09	*//* Add By O.Kimoto 1998/03/09 */
#include "\src\atlanta\scd\ext_v\cph_data.h"
#include "\src\atlanta\ext_v\rom_tbl.h"
#include "\src\atlanta\define\rom_def.h"	/* by K.Watanabe 1998/02/27 */
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
extern UBYTE DebugStripePattern1;
extern UBYTE DebugStripePattern2;
extern UBYTE DebugStripePattern3;
extern UBYTE DebugStripePattern4;
extern UBYTE DebugStripePattern5;
extern UBYTE DebugStripePattern6;
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
void	MailComDataPowerOnInitial(void);
void	INF_PowerOnInitial(void);		/*1998/04/20 Eguchi */
#endif

#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)	/* T.Nose 1998/12/21 */
#include "\src\atlanta\define\ncu_pro.h"
#endif

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\unisw_j.h"
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE) /*By Y.Suzuki 2002/06/07*/
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\std.h"
#endif

/*************************************************************************
	module		:[RAMを初期化する]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		PowerOn時に1回Callされる
	]
	comment		:[
		メインタスクからCallされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1994/3/29]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeRAM(void)
{
	UWORD	i;

#if defined(POPLAR_F)
#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/15 */
	SYS_T30Monitor = (struct SYS_T30MonitorData_t *)MEM_STOREAREA_START_ADDRESS;
 #endif
#endif

#if defined(ANZU_L)	/* 1997/12/09 debug Y.M */
	LST_DebugInit();
#endif

#if (0)	/* 下に移動 By M.Tachibana 1997/10/18 */
//	/*------------------------------*/
//	/* マシーン・ステータスのクリア */
//	/*------------------------------*/
//	InitializeMachineStatus();
#endif
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
	SYB_FlashROM_WriteStatus = NO_STATUS;
#endif

	/*****SYS*****/
#if defined(POPLAR_F)
	SYS_PADRH_PortStatus = IO__PADRH_DATA;		/* ＣＰＵポートＡＨ By M.Kotani 97/06/13 */
	SYS_PADRL_PortStatus = IO__PADRL_DATA;		/* ＣＰＵポートＡＬ By M.Kotani 97/06/13 */
	SYS_PDDRH_PortStatus = IO__PDDRH_DATA;		/* ＣＰＵポートＤＨ By M.Kotani 97/06/13 */
	SYS_Modem1PortStatus = 0;					/** MRD9201モデム・ポ－ト1／ビット・アサイメント */
	SYS_Modem2PortStatus = 0;					/** MRD9201モデム・ポ－ト2／ビット・アサイメント */
	SYS_ETC_PortStatus = 0xBF00;				/** その他・ポ－ト／ビット・アサイメント */
	SYS_ETC2_PortStatus = 0;					/** その他・ポ－ト／ビット・アサイメント */
	SYS_LED1_PortStatus = 0xFFFF;				/** ＬＥＤ・ポ－ト1／ビット・	アサイメント */
	SYS_LED2_PortStatus = 0xFFFF;				/** ＬＥＤ・ポ－ト２／ビット・アサイメント */
	SYS_COM_PortStatus |= 0x0010;				/** ＣＯＭ・ポ－ト／ビット・アサイメント */
#else
	SYS_PADRH_PortStatus = IO__PADRH_DATA;		/* ＣＰＵポートＡＨ By M.Kotani 97/06/13 */
	SYS_PADRL_PortStatus = IO__PADRL_DATA;		/* ＣＰＵポートＡＬ By M.Kotani 97/06/13 */
	SYS_PDDRH_PortStatus = IO__PDDRH_DATA;		/* ＣＰＵポートＤＨ By M.Kotani 97/06/13 */
	SYS_Modem1PortStatus = 0;		/** MRD9201モデム・ポ－ト1／ビット・アサイメント */
	SYS_Modem2PortStatus = 0;		/** MRD9201モデム・ポ－ト2／ビット・アサイメント */
	SYS_ETC_PortStatus = 0;			/** その他・ポ－ト／ビット・アサイメント */
	SYS_ETC2_PortStatus = 0;		/** その他・ポ－ト／ビット・アサイメント */
	SYS_LED1_PortStatus = 0xFF;		/** ＬＥＤ・ポ－ト1／ビット・	アサイメント */
	SYS_LED2_PortStatus = 0xFF;		/** ＬＥＤ・ポ－ト２／ビット・アサイメント */
#endif

#if (PRO_PANEL == ANK)
/* 移植 by SMuratec L.Z.W 2003/07/24 */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */
 #else
	SYS_LCDC_PortStatus = LCDC_PORT_DATA;	/** ＬＣＤポ－ト／ビット・アサイメント */
 #endif
#endif

	SYS_LCD_DataPortStatus = 0;		/** ＬＣＤデータポート／ビット・アサイメント */
	SYS_RTC_PortStatus = 0;			/** ＲＴＣ・ポ－ト／ビット・アサイメント */
	SYS_SpeakerOutputStatus = 0;	/** スピーカー出力状態初期化 ANZU 1996/02/22 Eguchi */

	SYS_SecondCassetteFlag = 1;		/** 下段カセットは有りで初期化する。 */

	SYS_VariableTimer = 5;
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		SYS_MltVariableTimer[i] = 5;
	}

	SYS_NextQueueVariableTimer = 1;	/* Add By O.Kimoto 1997/01/22 */

	SYS_AudibleAlarmStatus = 0;		/** 受信完了アラーム鳴動状態クリア *//*1996/08/13 Eguchi*/

#if (PRO_PRINT_TYPE == LASER)
	SYS_PRN_SirialInhibit = 0;
#endif
#if (PRO_PRINT_TYPE == LED)
	SYB_PrinterLifeMonitor.ErrorStatus = 0;	/* By M.Tachibana 1997/12/04 */
	SYS_DrumUnitStatus = 0;
	SYS_MotorLockCheckStart = 0;
	SYS_FanLockEnableTimer = 0;
	SYS_FanLockDetectTimer = 0;
	SYS_PsFanLockEnableTimer = 0;
	SYS_PsFanLockDetectTimer = 0;
#endif
	SYS_FaxCommStage = 0;			/*ＦＣＭタスクの通信遷移状態(表示用) */
	SYS_HookKeyInputFlag  = 0;		/** フックキー入力フラグ初期化 */
	SYS_HoldKeyInputFlag  = 0;		/** 保留キー入力フラグ初期化   */
#if (PRO_RING_MASTER == ENABLE)
	SYS_TeachingModeFlag = 0;
 #if defined(AUS)	/* 1997/05/21 Y.Murata DUET */
	/*----------------------------------------------*/
	/* リングマスターパターン自動検出データのクリア */
	/*----------------------------------------------*/
	for (i = 0; i < BUFF_MAX; i++) {
		SYB_TeachingPattern[0].RingMinCycle[i] = 0;
		SYB_TeachingPattern[0].RingMaxCycle[i] = 0;
		SYB_TeachingPattern[1].RingMinCycle[i] = 0;
		SYB_TeachingPattern[1].RingMaxCycle[i] = 0;
	}
	SYB_RingG_SetNumber = 0;
	SYB_RingH_SetNumber = 0;
 #endif
#endif
	SYS_RingCounter	 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	SYS_RingCounterExt = 0;
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1998/03/12 */
	DebugStripePattern1 = 0;
	DebugStripePattern2 = 0;
	DebugStripePattern3 = 0;
	DebugStripePattern4 = 0;
	DebugStripePattern5 = 0;
	DebugStripePattern6 = 0;
#endif

	SYS_RxDetectFlag = 0;
#if defined(JPN)
	SYS_F_Net_AutoCalledDisableFlag = 0;	/* '95,11,17 By N.S. for ANZU */
#endif

	SYS_DialingNumber.ReadPointer = 0;		/* ↓ M.Tachibana 1997/02/20 */
	SYS_DialingNumber.WritePointer = 0;
	SYS_FaxTelTimeUpTimeFlag = 0;
	SYS_TxDetectFlag = 0;					/* ↑ M.Tachibana 1997/02/20 */

	/*************************************************************
	 * ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
	 * 原因：通信記録の開始時刻が正常に印字されているため、通信終了
	 *		 時に読み込んだＲＴＣのデータが化けていた可能性がある。
	 *		 ＲＴＣが化ける可能性としては、リード中にＣＥがローレベル
	 *		 になる等があるが、実際の原因は不明。
	 * 対策：通信時間の算出用に次のデータを追加
	 *		 UWORD SYS_1SecBaseCounter（０～１００）
	 *		 UWORD SYS_1SecGeneralTimer（０～６５５３５）
	 *		 UWORD SYS_FCM_StartTime
	 * 1996/09/02 S.Kawasaki
	 *************************************************************/
	SYS_1SecBaseCounter = 0;
	SYS_1SecGeneralTimer = 0;
	SYS_FCM_StartTime = 0;
	SYS_VoiceSwitch = 0;			/* 会話予約のリセット Add By M.Kotani 1998/04/01 */

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
	/* 待機モードの初期化 */
	switch (CHK_UNI_PrimaryReadyMode()) {
	case PRIMARY_COPY_READY:
		/* コピー禁止中かミラーキャリッジ輸送モードの時は、コピーモードに出来ません */
		if ((!CHK_CopyProtectON()) && (SYB_ScannerTransportMode == FALSE)) {
			SYB_SettingStatus[SETTING_STATUS_26] |= READY_MODE_COPY;
		}
		break;
	case PRIMARY_FAX_READY:
		SYB_SettingStatus[SETTING_STATUS_26] &= ~READY_MODE_COPY;
		break;
	default:
		break;
	}
#endif

	/*------------------------------*/
	/* ２回線仕様電源ＯＮ時の初期化 */
	/*------------------------------*/
	MAN_MultiLinePowerOnInitial();

#if (PRO_FBS == ENABLE)
	SYS_NextBookDocument = FALSE;	/* ＢＯＯＫ次原稿のあり／なし確認  by K.Watanabe 1997/04/25 */
#endif

/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	SYS_InternalLineNumber = 0;
	/* 警察FAX DVT_ID2 Added by SMuratec 李 2005/11/10 */
 #if defined (KEISATSU) /* Added by SMuratec 李 2005/08/02 */
	FaxComTXorRX_Flag 		= 0;			/*	送信／受信識別フラグ　送信、受信、リモート診断識別	*/
	SYS_LineTelStatus 		= 0;
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
	DEBUG_NumberDisplay		= FALSE;
	SYS_LineNDStatus 		= 0;
	SYS_CalledLineNumber 	= 0;
 #endif /* defined (KEISATSU) */
#endif

	/* 省エネ関連 */
#if (PRO_ENERGY_SAVE == ENABLE) 		/* 2001/11/30 T.Takagi */
	SYS_MakingShadingData = FALSE;	/* 2001/12/3 T.Takagi */
	SYS_ShadingDataSet = FALSE;
/*	SYS_HaltClock = FALSE;	*/
/* 	SYS_24V_OffTimer = (UWORD)CHK_UNI_EcoModeStartTime() * 60; */	/* 2002/11/29 T.Takagi */
#endif

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	SYS_IsRedShading = 0;
#endif


	/*****MAN*****/
	MAN_StartPageCounter = 0;
	MAN_EndPageCounter = 0;
	BackUpStatusPrinter1 = 0;
	BackUpStatusPrinter2 = 0;
	BackUpStatusPrinter3 = 0;
	BackUpStatusScanner = 0;
	BackUpStatusError = 0;
	BackUpStatusCover = 0;			/* 追加 94.11.11 野瀬 */
	BackUpStatusWarning = 0;		/* 追加　1996/06/20　Eguchi */
	HoldBuzzerRequest = 0;			/* 1995/12/04 Eguchi 保留警告ブザー鳴動要求クリア */
	HoldEndBuzzerRequest = 0;		/* 1995/12/04 Eguchi 保留終了ブザー鳴動要求クリア */
	SYS_SCN_MotorReverseControal = 0;	/* '95,12,21 By N.S. 1line insert for ﾓｰﾀｰ反転 0:正転 1:反転*/
	/* ＣＰＵバージョンのコピー		By M.Tachibana 1997/05/28 */
	for (i = 0; i < ROM_REVISION_MAX; i++) {
		SYB_CPU_Revision[i] = CPU_Revision[i];
	}

#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
	/** パワーＯＮ時に、SGPダイアルバッファをクリアする。*/
	CMN_MemorySet(SYS_SgpDialBuffer, SYS_DIRECT_DIAL_MAX, 0xFF);
#endif

	/*****CDC*****/
	for (i = 0; i < CODEC_MAX; i++) {
		CodecGetID[i] = CODEC_NOT_USE;	/** コーデックの使用状況格納用変数のクリア (コーデックを使用しているID = 0)*/
	}
	FontImageBufferAddress = NULL;

	/*****PRN*****/
#if (PRO_PRINT_TYPE == LED) || (PRO_PRINT_TYPE == LASER)	/* 1998/06/10 H.Yoshikawa */
	PRN_1stPagePrintFlag = 0;		/* 電源ＯＮ直後の黒ライン対策 By S.Kawasaki 1996/08/22 */
	for (i = 0; i < PRN_STATUS_MAX; i++) {
		PrinterStatus[i] = 0x00;	/** Initialize Printer Status By S.K Apr.28,1994 */
	}
#endif

	/*****LST*****/
	LST_JAM_DetectCounter = 0;

	/*****FCM*****/
	MDM_ResetCounter = 0;			/* 96.2.13 by T.Yamaguchi for ＥＣＭ受信ループ対策 */
	FaxComPerformingFlag = 0;		/**	通信中フラグをクリア	*/	/* 竹内 Aug.24.1994 */
#if (PRO_RELAYED_REPORT == ENABLE)	/* 95/03/17 Y.Suzuki */
	TxRelayReport = 0;				/* 不達通知送信時、会話予約キーを入力しない  初期化 */
#endif
	FCM_Is_ToneDetecting = YES;		/* ゼロクロス検出する */

#if defined(POPLAR_F) || defined(HINOKI2) || defined(HINOKI3) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || (defined(POPLAR_H) && defined(JP1)) || defined(SATSUKI2) || defined(STOCKHM2)
#else
	MDM_DebugSw = 0;
#endif

	/*****PAT*****/
#if (PRO_PAT_JOURNAL == ENABLE)
	PAT_JournalMaking = 0;			/** ジャーナル自動印字で何も書かない件対策 By O.K Mar,20,1995 **/
	PAT_JournalCDC = 0;				/* 1995/03/25 Y.Murata */
#endif

#if defined(POPLAR_F)
#else
	/*****SCN*****/
	/* SCN_StopDS1OffDetect = 0;	@* 1996/08/14 By N.Sakamoto */
	CCD_Maker = CCD_MakerTOSHIBA();	/* NEC:0 TOSHIBA:1 *//*MODEM__PORTをリードして決定する*/
	if (CCD_SizeB4()){	/*MODEM__PORTをリードして決定する*/
		CCD_Size = 2;	/** CCD_Size = B4 '96,01,30 By N.S.**/
	}
	else{
		CCD_Size = 1;	/** CCD_Size = A4 '96,01,30 BY N.S.**/
	}
#endif

#if (PRO_SCN_CODEC_TYPE == IDP301)	/* 1998/06/29 H.Yoshikawa */
	SCN_Initial();
#endif

	/*****OPR*****/
	OPR_Initial();					/** オペレーション大域変数の初期化 */
	LCD_Initialize();				/** ＬＣＤコントローラーの初期設定 By S.K */

#if (PRO_PANEL == ANK)	/* 1996/10/25 by K.Watanabe */
	/* E設 中西さんからの依頼 Busy Flag がこけない時LCDCをリセットする T.Nose 1997/12/01 */
	DEBUG_LCD_ResetFlag = 0;
#endif

	/*****DTC*****/
	DMA_DTC_Initialize();


#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1997/04/20 Eguchi */
	/*****INF******/
	/* TCP/IP EngineBoardの初期化 */
	SYS_INF_ExecuteIFAX = FALSE;
	SYS_INF_PSTN_AccessReq = FALSE;
#endif

#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/15 */
	/***** チェッカー!!! *****/
	SYS_CheckerMode = CMN_StartCheckerModeKey();	/* CHECKER */
#endif

	/************************************/
	/*以下バックアップラムに関する初期化*/
	/************************************/
	/*****SYB*****/
	/*----------------------------------------------------------------------*
	 * 電源立ち上げ時にバックアップRAMをクリアするかどうかをチェックする処理
	 *----------------------------------------------------------------------*/
	SYS_AutoBackUpRAM_Clear = 0;

	if (CMN_CheckBackUpRAM() == TRUE) {	/** SRAM異常無し */
		if (CMN_CheckOptionChange() == TRUE) {	/**異なるモデル（オプション）のＲＯＭに交換された */
			CMN_InitializeOptionData((UBYTE)0);			/** オプション専用バックアップデータ初期化 */
			/* SYB_ScannerTransportMode = FALSE; @** 輸送モード解除 1997/03/05 s.takeuchi *//* コメント化 T.Nose 1998/01/08 */
		}

#if (1) /* 電源立ち上げ時に初期化されない。By H.Fujimura 2002/09/10 */
		CMN_ResetMemoyFeederTx();
		CMN_ResetStamp();
		CMN_ResetPrimaryMode();
		CMN_ResetPrimaryContrast();
		CMN_ResetConfirmationReport();
 #if (PRO_RED_SCAN == ENABLE)
		CMN_ResetRedScan();
 #endif
 #if defined(SATSUKI2) || defined(HINOKI2) || defined(HINOKI3)	/* Add by Y.kano 2004/01/14 */
		CMN_CheckNewFunction();
 #endif
#endif
	}
	else {								/** SRAM異常有り */
		CMN_InitializeAllBackUpRAM(0);			/** バックアップ領域全てを初期化 */
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
	/* ＲＡＭの初期状態によっては登録時、無限長コピーとなってしまい、ループするので、
	** ここで、シリアルデータ・メンバーの最後にＮＵＬＬをセットしておく。
	** By O.Kimoto 1999/02/12
	*/
	SYB_ConsumerOrder.SerialNumber[SYS_ORDER_SERIAL_MAX]     = NULL;	/* シリアル番号			*/
#endif

		SYS_AutoBackUpRAM_Clear = 1;
	}

	/* 拡張ＲＯＭバージョンの初期化 by K.Watanabe 1998/02/27 */
	for (i = 0; i < SYS_EXT_ROM_MAX; i++) {
		SYB_ExtRomRevision[i][0] = NULL;
	}

	/* 1997/12/03
	 * この変数使ってないやんけ～！
	*/
	SYS_BackUpRamListRequest = 0;			/* ＲＡＭ領域初期化通知のプリント要求（「しない」にプリセット） */

	SYS_OptionLineT30PrintRequest = 0;		/* ここでもやる 1997/12/03 */
	SYS_BackUpOptionLineT30PrintReq = 0;
	SYS_BackupFaxComType = 0xFF;			/* 1997/12/05 Y.Murata */
	SYS_DualPrinterWaiting = 0;
	SYS_DualPrinterWaitReq = 0;
	SYS_DualPrinerWakeUpStatus = 0;
	SYS_DualPrinterWaitStatus = 0;

	/* 追加  自動起動に使用してるＳＹＳはここでクリアじゃ～ 1997/12/24 */
	SYS_ManualFaxCommErrRequest = 0;		/* 手動通信チェックメッセージのプリント要求 */
	SYS_BackUpManualFaxCommErrReq = 0;
	SYS_ProtocolMonitorPrintRequest = 0;	/* プロトコルモニタのプリント要求 */
	SYS_BackUpProtocolMonitorReq = 0;
	SYS_MemoryOverListRequest = 0;			/* 画像メモリあふれ通知のプリント要求 */
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
	SYS_MemoryOverListPage = 0;
#endif
#if (PRO_PC_PRINT == ENABLE)
	SYS_PcMemoryOverListRequest = 0;		/* ＰＣプリント用画像メモリあふれ通知のプリント要求 */
	SYS_PcMemoryOverDispRequest = 0;		/* ＰＣ画像メモリあふれ表示要求 */
#endif
#if (PRO_DEPARTMENT == ENABLE)
  #if (PRO_COST == ENABLE)
	SYS_DepartmentListRequest = 0;			/* 部門リストのプリント要求 */
	SYS_DepartmentClearRequest = 0;
  #endif
  #if (PRO_DEPART_NEW_LIST == ENABLE)	/* 部門管理リスト（簡易料金管理リスト）*/
	SYS_DepartManageListRequest = 0;		/* 部門リストのプリント要求 */
	SYS_DepartManageClearRequest = 0;
  #endif
#endif


#if (PRO_EXT_ROM == ENABLE)		/*	By Y.Suzuki 1997/12/09	*/
 #if (PRO_CIPHER == ENABLE) /*By Y.Suzuki 1998/03/09*/
	/* ＤＲＡＭクリアの前で行なう */
/* #if (defined JPN)By Y.Suzuki 1998/03/03 */
	/* 拡張ＲＯＭがあれば スクランブルありとする */
	if ((EXT_ROM_Revision[ROM_EXT_SCRAMBLE][0] == 'D') &&
		(EXT_ROM_Revision[ROM_EXT_SCRAMBLE][1] == 'S') &&
		(EXT_ROM_Revision[ROM_EXT_SCRAMBLE][2] == '-') &&
		(EXT_ROM_Revision[ROM_EXT_SCRAMBLE][3] == '1') &&
		(EXT_ROM_Revision[ROM_EXT_SCRAMBLE][4] == '0') &&
		(EXT_ROM_Revision[ROM_EXT_SCRAMBLE][5] == '0')) {
		ScrambleOn = 1;
		/* 拡張ＲＯＭリビジョン表示のため By Y.Suzuki 1998/02/26 */
		CMN_StringCopyNum(SYB_ExtRomRevision[0], EXT_ROM_Revision[ROM_EXT_SCRAMBLE], ROM_REVISION_MAX);
	}
	else {
		ScrambleOn = 0;
	}
/* #endif */
	SYS_CipherComExec = 0;
	SYS_CipherInterruptionOn = 0;/*By Y.Suzuki 1998/05/27*/
	SYS_CipherRestartEnable = 0;/*By Y.Suzuki 1998/06/10*/
	SYS_CipherFnetOrDialInReceive = 0;/*By Y.Suzuki 1998/06/15*/
	SYS_BackupCipherStatus = 0;/*By Y.Suzuki 1998/08/12*/
 #endif /* (PRO_CIPHER == ENABLE) By Y.Suzuki 1998/03/09*/

 #if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
	/* 拡張ＲＯＭがあれば(識別文字が一致すれば）クラス１ありとする */
	if ((EXT_ROM_Revision[ROM_EXT_CLASS1][0] == 'C') &&
		(EXT_ROM_Revision[ROM_EXT_CLASS1][1] == 'L') &&
		(EXT_ROM_Revision[ROM_EXT_CLASS1][2] == 'A') &&
		(EXT_ROM_Revision[ROM_EXT_CLASS1][3] == 'S') &&
		(EXT_ROM_Revision[ROM_EXT_CLASS1][4] == 'S') &&
		(EXT_ROM_Revision[ROM_EXT_CLASS1][5] == '1')) {
		 CL1_IsExClass1ROM = TRUE;
		/* 拡張ＲＯＭリビジョン表示のため */
		CMN_StringCopyNum(SYB_ExtRomRevision[ROM_EXT_CLASS1], EXT_ROM_Revision[ROM_EXT_CLASS1], ROM_REVISION_MAX);
	}
	else {
		 CL1_IsExClass1ROM = FALSE;
	}

 #endif /* (PRO_EX_CLASS1 == ENABLE)  */

#endif
	/*---------------------------------------------------------------------*/
	/* ＤＲＡＭクリアに関係するＲＡＭの初期化							   */
	/* CMN_CheckBackUpRAM()がFALSEの時の処理前にこの処理を行うとループする */
	/*---------------------------------------------------------------------*/
	MAN_CheckDRAM_BackUp();

	SYS_AutoShutOFF_Timer = CHK_UNI_PrinterAutoShutTime();
#if (PRO_PRINT_TYPE == LED)
 #if defined(POPLAR_F)	/* FAN騒音対策 */
	SYS_AutoFanOffTimer = (UWORD)CMN_GetFanStopTimer();
 #elif (defined(POPLAR_H) && defined(JP0)) /* V851 ＦＡＮ制御 By H.Fujimura 2002/07/11 */
	SYS_AutoFanOffTimer = (UWORD)CHK_UNI_FanTime();								/* 単位：分 *//* FAN停止用最長タイマー */
	SYS_AutoFanOffTimer2 = (UWORD)CHK_UNI_InternalTempIntervalTimer();		/* 単位：分 *//* FAN停止用監視タイマー */
 #else
	SYS_AutoFanOffTimer = SYB_MaintenanceSwitch[MNT_SW_H8];
 #endif
	SYS_PrinterWakeupTimer = 0;
#endif

	/*------------------------------*/
	/* マシーン・ステータスのクリア */
	/*------------------------------*/
	/* DRAMバックアップ処理の中でマシンステータスを参照しているため
	** ここより上にはもっていってはいけない By M.Tachibana 1997/10/18
	*/
	InitializeMachineStatus();

#if (0)	/* 未使用なので削除します by K.Watanabe 1998/07/10 */
//	/** ワーディングの実体までのオフセットの計算 1996/03/11 Eguchi*/
//	SetWording(SYB_WordingNumber);
//	CalculateWordingOffset();
#endif

	/* マルチタイマーキューの初期化 T.Nose 1996/11/19 */
	for (i = 0; i < TIMER_MULTI10MS_MAX; i++) {
		Timer10msQueue[i].Time = 0xFFFF;
		Timer10msQueue[i].SendMBX = 0xFFFF;
		Timer10msQueue[i].ReturnValue = 0xFFFF;
		Timer10msQueue[i].Link = 0xFF;
		Timer10msQueue[i].TimerID = (UBYTE *)0xFFFFFFFF;
	}
	CMN_TopTimerQueue = 0xFF;

	/* SH内蔵DMAC設定ブロックの初期化（オートイニシャライズ設定のみ） T.Nose */
	for (i = 0; i < 4; i++) {
		DMA_SH_Cntrl[i].AutoInit = AUTO_INITIALIZE_OFF;
	}

#if (PRO_ROTATE == ENABLE)
	MAN_RotateIsBusy = 0;
#endif


#if (PRO_PC_PRINT == ENABLE)
	PCR_OptMessagRead = 0;
	PCR_OptMessagWrite = 0;
	for (i = 0; i < SYS_PCR_OPTION_MESSAGE_MAX; i ++) {
		SYS_PCR_OptionMessage[i].Status = 0;
		SYS_PCR_OptionMessage[i].Item = 0xFFFF;
		SYS_PCR_OptionMessage[i].Message = 0xFFFF;
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
	MailComDataPowerOnInitial();
#endif

	/* ワンタッチＡの設定を前ワンタッチ短縮にコピーする 1997/08/07  By T.Yamaguchi */
	if (SYB_MaintenanceSwitch[MNT_SW_B4] & ONETOUCH_DIAL_COPY) {
		for (i = 3; i < SYS_ONETOUCH_MAX; i ++) {
			MemoryMove(&SYB_OnetouchDial[i].Dial[0], &SYB_OnetouchDial[0].Dial[0], 64);
			i++;
			if (i < SYS_ONETOUCH_MAX) {
				MemoryMove(&SYB_OnetouchDial[i].Dial[0], &SYB_OnetouchDial[1].Dial[0], 64);
			}
			i++;
			if (i < SYS_ONETOUCH_MAX) {
				MemoryMove(&SYB_OnetouchDial[i].Dial[0], &SYB_OnetouchDial[2].Dial[0], 64);
			}
		}
		/*------------------*
		 * 標準短縮ダイヤル *
		 *------------------*/
		for (i = 0; i < SYS_SPEED_DIAL_MAX; i ++) {
			MemoryMove(&SYB_SpeedDial[i].Dial[0], &SYB_OnetouchDial[0].Dial[0], 64);
			i++;
			if (i < SYS_SPEED_DIAL_MAX) {
				MemoryMove(&SYB_SpeedDial[i].Dial[0], &SYB_OnetouchDial[1].Dial[0], 64);
			}
			i++;
			if (i < SYS_SPEED_DIAL_MAX) {
				MemoryMove(&SYB_SpeedDial[i].Dial[0], &SYB_OnetouchDial[2].Dial[0], 64);
			}
		}
		SetJunkOwnDial();
	}
	if (SYB_MaintenanceSwitch[MNT_SW_B4] & FCODE_BOX_COPY) {
		/*------------------*
		 * ＦコードＢＯＸ   *
		 *------------------*/
		for (i = 1; i < SUB_ADDRESS_BOX_MAX; i ++) {
			MemoryMove(&SYB_SubAddressBoxTable[i].Status, &SYB_SubAddressBoxTable[0].Status, 64);
		}
	}

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/07.02 */
	NCU_ND_Status = 0;
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
	SYS_LineNDStatus = 0;
#endif /* defined (KEISATSU) */
	NCU_ND_FirstResponseTime = 0; /* added by H.Kubo 1998/10/06 */
	SYS_ND_CurrentJournalPoint = SYS_ND_NO_JOURNAL;
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS /*THERMAL*/)	/*  By H.Kubo  1998/10/26 */
	SYS_PRN_StopRequestFromModem = FALSE;
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/06 Y.Murata */
	if (CMN_CheckMinoltaFlashEnable()) {
		CMN_MinoltaDataInitFla();
	}

	/* 1998/08/27 Y.Murata */
	OPR_MinoltaPatternCheck = 0xFF;						/* ミノルタテストプリント用バッファ初期化 */
	OPR_MinoltaPagesCheck	= 0;
	OPR_MinoltaOnetouch		= 0;
	OPR_MinoltaPatternItem 	= 0xFF;	/* 1998/08/31 Y.Matsukuma */
	OPR_MinoltaDisplayCheck = 0xFF;

 #if (PRO_PRINT_TYPE == LASER)
	PRN_TimerTaskSerial = 0;	/* 1998/08/31 Y.Murata */
 #endif
#endif


#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/16 Y.Murata for KAKI */
	SYS_QucikTxStopQueueNo = 0xFFFF;
	SYS_QucikTxStopStatus = 0;
#endif

#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
 #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	SYS_DualRestrictionStatus = 0;
	SYS_CalledRequestForDocStore = 0; /* added by H.Hirao 1998/12/28 */
 #endif
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	CL1_DualRestrictionStatus = 0;	/* added by H.Hirao 1999/03/04 */
	CL1_RestrictionStatusResetTimer = 0;	/* added by H.Hirao 1999/05/26 */
#endif
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/18 K.Kawata */
	CL1_ExtFunctionEnableFlag = 0;
	CL1_ExtLocalPrtRejectCnt = 0;
	CL1_ExtTransmitErrorFlag = 0;
#endif

#if defined(POPLAR_F)
	SYS_ContPollingValiableTimer = 0;
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
	SYS_AutoPowerSW = TRUE;
	SYS_EcoModeStatus = ECO_MODE_OFF;
	SYS_NewEcoModeStatus = ECO_MODE_OFF;
	SYS_OldEcoModeStatus = ECO_MODE_OFF;
	SYS_EcoModeTimer = (UWORD)CHK_UNI_EcoModeStartTime() * 60;
	SYS_SensorDetectInhibit = 0;
	SYS_EcoResetKeyInput = 0;
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
	SYS_EcoModeStatus = ECO_MODE_OFF;
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.kano 2003/09/01 */
	SYS_KeyTouchFrequencySetting = 0;	/* キータッチ音色設定オペレーション中判別フラグ */
	SYS_AckBuzzerFlag = 0;				/* AckBuzzerをONに */
	CheckTxDialType();					/* SATSUKI2は外付けSWで決定 by Y.Kano 2003/09/17 */
	CheckRingerControl();				/* リンガー制御チェック by Y.Kano 2003/09/18 */
	OPR_PS2_Adjust_Flg = 0;				/* PS2調整中フラグをOFF ローカルに反映 by Y.Kano 2003/12/04 */
	DocSetReadySteps = Ds2ToScanSteps;	/* 先端読取り位置微調整を有効にする為 Add by Y.Kano 2004/01/09 */
#endif

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)
	OPR_PaperSensor_Adjust_Flg = 0;
#endif	/* End of (PRO_PAPER_AD_SENSOR_INIT == ENABLE) */


#if (PRO_RTC_RX5C338A == ENABLE)
	ManInitRTC();
#endif

#if defined(STOCKHM2) /* 通信結果フラグの初期化 by Y.kano  2004/11/04 */
	SYS_ConfirmTxRxFlag = 0;
#endif

#if defined (KEISATSU) /* 警察FAX 05/09/21 石橋正和 */
	FCM_ShireiKidoWaitFor1stDCS = FALSE;
#endif


}


/*************************************************************************
	module		:[メイル・ボックス作成]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1994/08/25]
	author		:[村田]
*************************************************************************/
void MAN_InitializeMailBox(void)
{
	/****************************************************************/
	/* メイル・ボックス作成											*/
	/****************************************************************/
	cre_mbx(&mbxno.MAN_Task);
	cre_mbx(&mbxno.MAN_TimerTask);
	cre_mbx(&mbxno.MAN_SensorTask);
	cre_mbx(&mbxno.NCU_Task);
	cre_mbx(&mbxno.NCU_TaskSub);
	cre_mbx(&mbxno.NCU_DetectCalledTask);
	cre_mbx(&mbxno.NCU_TelephoneHookCheckTask);
	cre_mbx(&mbxno.NCU_DetectFnetTask);
	cre_mbx(&mbxno.NCU_DialInAutoSwitchTask);
	cre_mbx(&mbxno.FIP);
	cre_mbx(&mbxno.OPR_Task);
	cre_mbx(&mbxno.FCM_Task);
	cre_mbx(&mbxno.Tone[0]);
	cre_mbx(&mbxno.Tone[1]);
	cre_mbx(&mbxno.Tone[2]);
	cre_mbx(&mbxno.Tone[3]);
	cre_mbx(&mbxno.Tone[4]);	/* By H.Y 1994/12/03 */
	cre_mbx(&mbxno.Tone[5]);	/* 1996/12/12  By T.Yamaguchi */
	cre_mbx(&mbxno.NCU_TelephoneOperationTask);
	cre_mbx(&mbxno.NCU_TelephoneOperationTaskSub);
	cre_mbx(&mbxno.NCU_FaxTadAutoSwitchTask);
	cre_mbx(&mbxno.NCU_TelephoneExecuteTask);
	cre_mbx(&mbxno.NCU_ReceiveDTMFTask);
	cre_mbx(&mbxno.NCU_DailInAutoSwitchTask);
	cre_mbx(&mbxno.NCU_TransRBTAndDetCNGTask);
	cre_mbx(&mbxno.NCU_GenerateRingSignalTask);
	cre_mbx(&mbxno.NCU_DetectDSETask);
	cre_mbx(&mbxno.NCU_DetectSilentTask);
	cre_mbx(&mbxno.MDM_Task);
	cre_mbx(&mbxno.SCN_Task);
	cre_mbx(&mbxno.SCN_ControlTask);
	cre_mbx(&mbxno.PRN_Task);
	cre_mbx(&mbxno.PRN_ControlTask);
	cre_mbx(&mbxno.LST_Task);
#if (PRO_DOC_IN == ENABLE) /* メモリ節約のため。#if is added by H.Kubo 1998/07/08 */
	cre_mbx(&mbxno.MAN_DocumentInTask);
#endif
	cre_mbx(&mbxno.MDM_TaskSub);
	cre_mbx(&mbxno.CPY_Task);
	cre_mbx(&mbxno.CMN_BuzzerTask);
	cre_mbx(&mbxno.MDM_EncodeDMA_TC_DetectTask);
	cre_mbx(&mbxno.MDM_MTxReadDMA_Task);
	cre_mbx(&mbxno.MDM_RxEcmControlTask);
	cre_mbx(&mbxno.MDM_PixDummy);
	cre_mbx(&mbxno.PRN_Serial);
	cre_mbx(&mbxno.PRN_SerialInTimer);
	cre_mbx(&mbxno.SCN_Sub); /* By S.K Nov.2,1994 */
	cre_mbx(&mbxno.SCN_GearBackLashTask); /* By S.K Jan.24,1995 */
	cre_mbx(&mbxno.OPR_SubMessageTask);	/* Jan.11,1995 By S.K -> 桐にも適用 Jan.18,1995 By T.Nose */
	cre_mbx(&mbxno.OPR_Sub_MANTask);	/* Jan.11,1995 By S.K -> 桐にも適用 Jan.18,1995 By T.Nose */
	cre_mbx(&mbxno.OPR_MAN_MessageTask);/* Jan.13,1995 By T.Nose -> 桐にも適用 Jan.18,1995 By T.Nose */
#if (PRO_SPEED_EX == ENABLE)
	cre_mbx(&mbxno.ATD_SPD_Tone);		/* Jan.29,1996 By t.yamaguchi */
#endif
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if (PRO_SOFT_CODEC == ENABLE) */
	cre_mbx(&mbxno.SCDC_MTxCodeConvertTask);/* By Y.Suzuki 1996/07/11 */
	cre_mbx(&mbxno.SCDC_RxEcmControlTask);	/* By Y.Suzuki 1996/07/19 */
/*	cre_mbx(&mbxno.SCD_G3_MemRxTask);		@* By Y.Suzuki 1996/07/19 */
#endif
#if (PRO_PRINT_TYPE == LED)
	cre_mbx(&mbxno.PRN_HighVoltageTask);
	cre_mbx(&mbxno.PRN_DocumentOutTask[0]);
	cre_mbx(&mbxno.PRN_DocumentOutTask[1]);
	cre_mbx(&mbxno.PRN_DocumentOutTask[2]);
	cre_mbx(&mbxno.PRN_ListDocumentOutTask);
#endif
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	cre_mbx(&mbxno.CDC_Task);
#endif
#if (PRO_FBS == ENABLE)		/* T.Nose 1997/01/20 */
	cre_mbx(&mbxno.SCN_MirrorMoveTask);
#endif
	cre_mbx(&mbxno.FCM_Option);		/* 1996/11/09 Y.Murata */

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)/* Added by H.Kubo 1997/10/06 */
	cre_mbx(&mbxno.FCM_V8Task);
	cre_mbx(&mbxno.MDM_V21DetectTask);
	cre_mbx(&mbxno.MDM_TxEcmControlTask);
	cre_mbx(&mbxno.FCM_Dummy);
#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_CIPHER == ENABLE)/*	By Y.Suzuki 1997/12/22	*/
	cre_mbx(&mbxno.SCD_CipherResult);
#endif

#if (PRO_RELAYED_REPORT == ENABLE)/*	H.Kubo 1998/01/17 */
	cre_mbx(&mbxno.CDC_CTx);
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	cre_mbx(&mbxno.INF_Task);
	cre_mbx(&mbxno.INF_RsWriteTask);
	cre_mbx(&mbxno.INF_RsReadTask);

#endif

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/03/15  By T.Yamaguchi */
	cre_mbx(&mbxno.FCM_BusyToneDetect);		/* By T.Yamaguchi 1998/03/15 NTT BusyTone検出 */
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/21 */
	cre_mbx(&mbxno.NCU_ND);		/* added by H.Kubo 1998/08/21 */
#endif

#if	(PRO_PRINT_TYPE == THERMAL)
	cre_mbx(&mbxno.PRN_PrinterTask);
	cre_mbx(&mbxno.PRN_AddIndexQueueTask);
	cre_mbx(&mbxno.PRN_MakeImageTask);
	cre_mbx(&mbxno.PRN_PrintImageTask);
	cre_mbx(&mbxno.PRN_WatchPrinterTask);
#endif
/* #if defined(POPLAR_F) *//* added by m.matsumoto 1999/10/22 */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	cre_mbx(&mbxno.MDM_VoiceTask);
	cre_mbx(&mbxno.FCM_V34Task);
 #endif
#endif


	/****************************************************************/
	/* 完了表示用タイマーデータの設定(mbxnoの代入)					*/
	/****************************************************************/
	FaxcomCompleteMessage.Time = 200;							/** ２秒 */
	FaxcomCompleteMessage.SendMBX = mbxno.MAN_Task;				/** タイムアップ時に送るメッセージ送出先メイルボックス */
	FaxcomCompleteMessage.ReturnValue = MSG_FAXCOM_COMPLETE;	/** タイムアップ時に送るメッセージ内容 */

	timer_store_fax_complete = 0xFF;							/* メモリー送信原稿蓄積完了 */
	timer_store_copy_complete = 0xFF;							/* コピー蓄積完了 */

	timer_store_fax_complete = 0xFF;		/* メモリー送信原稿蓄積完了表示用 */

#if (PRO_PANEL == KANJI)				/* 漢字対応操作パネル */
	timer_faxcom_complete = 0xFF;		/* 通信終了表示用 */
	timer_print_complete = 0xFF;		/* プリント完了時 */
 #if (PRO_PC_PRINT == ENABLE)
	timer_print_pc_complete = 0xFF;	/* ＰＣプリント追加 by T.Soneoka 1997/07/17 */
 #endif
#endif

	StoreCompleteMessage.Time = 200;							/** ２秒 */
	StoreCompleteMessage.SendMBX = mbxno.MAN_Task;				/** タイムアップ時に送るメッセージ送出先メイルボックス */
	StoreCompleteMessage.ReturnValue = MSG_STORE_COMPLETE;		/** タイムアップ時に送るメッセージ内容 */

	PrintCompleteMessage.Time = 200;							/** ２秒 */
	PrintCompleteMessage.SendMBX = mbxno.MAN_Task;				/** タイムアップ時に送るメッセージ送出先メイルボックス */
	PrintCompleteMessage.ReturnValue = MSG_PRINT_COMPLETE;		/** タイムアップ時に送るメッセージ内容 */

#if (PRO_CLASS1 == ENABLE) /* 1996/09/13 Eguchi */
	PC_FAX_CompleteMessage.Time = 200;							/** ２秒 */
	PC_FAX_CompleteMessage.SendMBX = mbxno.MAN_Task;			/** タイムアップ時に送るメッセージ送出先メイルボックス */
	PC_FAX_CompleteMessage.ReturnValue = MSG_PC_FAX_COMPLETE;	/** タイムアップ時に送るメッセージ内容 */
#endif

	/* ICHOU追加 次原稿蓄積開始オペレーション入力タイマ設定 by T.Soneoka 1996/07/18 *//* T.Nose 1997/01/17 */
	timer_next_scan_complete = 0xff;
	NextScanStartOperation.Time = 6000;							/** １分 */
	NextScanStartOperation.SendMBX = mbxno.MAN_Task;			/** タイムアップ時に送るメッセージ送出先メイルボックス */
	NextScanStartOperation.ReturnValue = MSG_SCAN_CONT_TIMEUP;	/** タイムアップ時に送るメッセージ内容 */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	INF_CompleteMessage.Time = 200;							/** ２秒 */
	INF_CompleteMessage.SendMBX = mbxno.MAN_Task;			/** タイムアップ時に送るメッセージ送出先メイルボックス */
	INF_CompleteMessage.ReturnValue = MSG_INF_COMPLETE;		/** タイムアップ時に送るメッセージ内容 */

	INF_TerminateMessage.Time = 200;							/** ２秒 */
	INF_TerminateMessage.SendMBX = mbxno.MAN_Task;				/** タイムアップ時に送るメッセージ送出先メイルボックス */
	INF_TerminateMessage.ReturnValue = MSG_INF_TERMINATE;		/** タイムアップ時に送るメッセージ内容 */

	INF_NoNewMailMessage.Time = 200;							/** ２秒 */
	INF_NoNewMailMessage.SendMBX = mbxno.MAN_Task;				/** タイムアップ時に送るメッセージ送出先メイルボックス */
	INF_NoNewMailMessage.ReturnValue = MSG_INF_NO_NEW_MAIL;		/** タイムアップ時に送るメッセージ内容 */
#endif

}

/*************************************************************************
	module		:[マシーンステータスのクリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1994/09/22]
	author		:[吉川弘康]
*************************************************************************/
void InitializeMachineStatus(void)
{
	/*------------------------------*/
	/* マシーン・ステータスのクリア */
	/*------------------------------*/
	SYS_MachineStatus[SYS_RESOURCE_STATUS] = 0;
	SYS_MachineStatus[SYS_MACHINE_STATUS] = 0;
	SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] = 0;
	SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] = 0;
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] = 0;
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS_RESERVE] = 0;
	SYS_MachineStatus[SYS_PRINTER_STATUS1] = 0;
	SYS_MachineStatus[SYS_PRINTER_STATUS2] = 0;
	SYS_MachineStatus[SYS_PRINTER_STATUS3] = 0;
	SYS_MachineStatus[SYS_SCANNER_STATUS] = 0;
	SYS_MachineStatus[SYS_COVER_STATUS] = 0;
	SYS_MachineStatus[SYS_SENSOR_STATUS] = 0;
	SYS_MachineStatus[SYS_ERROR_STATUS] = 0;
	SYS_MachineStatus[SYS_WARNING_STATUS] = 0;
/*	SYS_MachineStatus[SYS_OTHER_STATUS] = 0;	ここで初期化してはいけません */

#if (PRO_MULTI_LINE == DISABLE)
 #if defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
	SYS_MachineStatus[SYS_OTHER_STATUS] = 0;
 #endif
#endif

	SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS] = 0;
	SYS_MachineStatus[SYS_CIPHER_STATUS] = 0;/*	By Y.Suzuki 1997/11/12	*/


#if (PRO_PRINT_TYPE == LASER)
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/31 Y.Murata */
	/* Nothing */
 #else
	/* ドラム寿命状態の初期化 1996/06/20 Eguchi */
	if (SYB_LifeMonitor.DrumLifeCount >= (UDWORD)PRN_DrumPrintMax) { /** ドラムの寿命 *//* UDWORDキャスト By M.Tachibana 1997/12/09 */
		SYS_MachineStatus[SYS_WARNING_STATUS] |= SYS_WARNING_DRUM_REPLACE;	/** ドラム交換表示／印字継続可能 */
	}
 #endif
#endif

	/* 1997/06/12 Y.Murata
	 * アトランタには内臓モデムが標準にあるので、有り無しは関係ないが
	 * ＫＯＢＥより移植してるし、直すのめんどうなので、ここで有り固定にします。
	*/
	SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_INTERNAL_MODEM;

}


/*************************************************************************
	module		:[タスク変数の初期化]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/11]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeTaskValue(void)
{
	/****************************************************************/
	/* タスク変数の初期化											*/
	/****************************************************************/
	tskno_DocumentOutTask				= 0xffff;
	tskno_SCN_StampTestTask				= 0xffff;
	tskno_SCN_DocumentStoreTask			= 0xffff;
	tskno_PRN_ImagePrintTask			= 0xffff;
	tskno_CPY_Task						= 0xffff;
	tskno_LST_PrintTask					= 0xffff;
	tskno_FCM_Task						= 0xffff;
	tskno_MAN_SensorTask				= 0xffff;
	tskno_MAN_TimerTask					= 0xffff;
	tskno_NCU_TelephoneOperation		= 0xffff;
	tskno_NCU_Task						= 0xffff;
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/11 */
	tskno_DetectCalledTask 				= 0xFFFF;
	/* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
	IsCiSndMsg	 						= FALSE;
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/01 */
	IsNDSndMsg	 						= FALSE;
	tskno_Detect2ndCalledTask			= 0xFFFF;
 #endif /* defined (KEISATSU) */
	tskno_OPR_Task						= 0xffff;
	tskno_PRN_PrinterResetTask			= 0xffff;	/* By S.Kawasaki 1996/07/16 */
	tskno_PRN_PrinterWarmUpTask			= 0xffff;
	tskno_SCN_GearBackLashTask			= 0xffff;
	tskno_faxcom_complete				= 0xffff;
	tskno_store_complete				= 0xffff;
	tskno_print_complete				= 0xffff;
	tskno_cmn_watchtimer10msevent		= 0xffff;	/** Add By Hirao 1996/08/24 */
	/* 以下の変数はUpdateDisplay()で使用します By H.Y 1994/08/11 */
	tskno_end_buzzer					= 0xffff;
	tskno_error_alarm					= 0xffff;
	tskno_error_alarm					= 0xffff;
	tskno_hunguperror					= 0xffff;
	tskno_hold_end						= 0xffff;	/* 1995/12/05 Eguchi */
	tskno_OPR_SubMessageReceiveTask		= 0xffff;	/* Jan.11,1995 By S.K -> 桐にも適用 Jan.18,1995 By T.Nose */
	tskno_CMN_MultiTimer10msTask		= 0xffff;	/* 1996/12/13 T.Nose */
#if (PRO_DOC_IN == ENABLE)
	tskno_DocumentInTask				= 0xffff;
#endif
#if (PRO_PAT_JOURNAL == ENABLE)
	tskno_JournalPrintTask				= 0xffff;	/*	1994/9/26 by okumura	*/
#endif
#if (PRO_DIALIN == ENABLE)
	tskno_NCU_DialInAutoSwitchTask		= 0xffff;
#endif
#if (PRO_PRINT_TYPE == LED)
	tskno_PRN_FuserTempTask				= 0xffff;
	tskno_PRN_ManualDocInTask			= 0xffff;
#endif
#if (PRO_CLASS1 == ENABLE)
	tskno_CL1_Task						= 0xffff;
	tskno_CL1_FaxComTask				= 0xffff;
	tskno_pc_fax_complete				= 0xffff; /* 1996/09/13 Eguchi */
#endif
#if defined(GBR)
	tskno_audible_alarm					= 0xFFFF; /* 1996/07/08 Eguchi */
#endif
#if (PRO_FBS == ENABLE)
	tskno_SCN_MirrorMoveTask			= 0xffff; /* T.Nose 1997/01/17 */
#endif
#if (PRO_ROTATE == ENABLE)
	tskno_ROT_Task						= 0xffff; /* By M.Kotani 97/03/27 */
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
	tskno_NCU_FaxComTelHookChkTask		= 0xffff;
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	tskno_INF_Task						= 0xffff;
	tskno_inf_terminate					= 0xffff;
	tskno_inf_nomail					= 0xffff;
	tskno_inf_complete					= 0xffff;
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/08/26 */
	tskno_V23ToneTask					= 0xffff;
	tskno_BusyToneTask 					= 0xffff;
	tskno_DetectDseTask 				= 0xffff;
	tskno_V23RxTask 					= 0xffff;
	timerID_v23_arrival 				= 0xff;
	tskno_CarOffTimer					= 0xffff;
#endif
#if defined(POPLAR_F)
	tskno_MDM_InternalStatus 			= 0xffff;
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
	tskno_ATD_DialPulseTask 			= 0xffff;
#endif
#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/19*/
	tskno_MAN_WakeUpSystemTask			= 0xffff;
	tskno_MAN_SleepSystemTask			= 0xffff;
#endif
#if defined(STOCKHM2) /* 本体鳴動のテスト : by SMuratec C.P 2004/09/24 */
	tskno_callingbuzzer 				= 0xffff;	/* 呼出ブザー鳴動用 */
#endif
}


/*************************************************************************
	module		:[セマフォ作成]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/11]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeSemapho(void)
{
	/****************************************************************/
	/* セマフォの作成												*/
	/****************************************************************/
	cre_sem(&semno.rtc);
	cre_sem(&semno.lcd);		/* add By T.Nose 94.10.17 */
	cre_sem(&semno.prn_serial);	/** プリンタのシリアル通信で使用  Add by NOBUKO	 Apr.13,94 */
	cre_sem(&semno.MEM_WriteOpenSem);	/** メモリライトオープンのセマフォ WRITE_OPEN_SEM by Y.Murata 1997/12/16 */
	cre_sem(&semno.MEM_ReadOpenSem);	/** メモリリードオープンのセマフォ WRITE_OPEN_SEM by Y.Murata 1997/12/16 */
	cre_sem(&semno.MEM_CheckSem);	/** メモリリードオープンのセマフォ WRITE_OPEN_SEM by Y.Murata 1997/12/16 */
	CreateModemBufferSem();
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)/*1998/05/22 Eguchi *//* if defined(ANZU_V)のほうがいいかな*/
	cre_sem(&semno.INF_MailJournal);
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) && (PRO_PRN_CODEC_TYPE == SOFTWARE)
	/* 基本的にここへ入ってくるのは、ＨＩＮＯＫＩだけのはずです。
	** ソフトコーデックの内蔵ＲＯＭ側でメモリ管理用変数を１個でRead/Writeしている
	** 箇所があり、最悪画像がバラバラになってしまう。
	** よって、セマフォで切り替えてソフトコーデックを使用する。
	** By O.Kimoto 1998/10/05
	*/
	cre_sem(&semno.SCDC_DRAM_Access);
#endif
#if (PRO_PANEL == ANK)
	cre_sem(&semno.OPR_UpDateDisp);		/** 表示ＵＰＤＡＴＥのセマフォ 1999/10/19 Y.Murata */
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE) /* 誤ダイヤル 2000/10/18 H.Yoshikawa */
	cre_sem(&semno.ATD_PulseDialer);
#endif

}


/*************************************************************************
	module		:[周辺デバイスの初期化]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/11/18]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeDevice(void)
{
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/10/29 H.Yoshikawa */
	UWORD	t30_wr_ptr;
#endif

#if (PRO_DTC_INT_SYSTEM == ENABLE)	/* DTC を使う周辺デバイスが初期化される前に DTC のカウンタをリセットします。 1998/11/19 H.Kubo */
	DMA_DTC_InitializeCounter();
#endif

#if (PRO_ENERGY_SAVE == ENABLE)			/* 2001/11/21 T.Takagi */
	/* ここでクロック供給 */
	if (SYS_HaltClock == FALSE) {	/* 現在クロックが停止していて *//* add 2002/02/22 T.Takagi */
		HaltClockOn();
		wai_tsk(1);		/* クロックが出始めてから最低0.6us待ってサブリセット解除 */
		SubResetOff();
		SYS_HaltClock = TRUE;			/* クロックが供給されていることを示すフラグ */
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1997/04/28 Eguchi */
	/*****INF*******/
	/* TCP/IP EngineBoardの初期化 */
	DisplayWaitAMinutes(); /** ウォームアップ中の表示を出す */
	INF_PowerOnInitial();  /**初期化ｴﾗｰの時の処理はどうする?*/
#endif

	/*****SCN*****/
	SCN_SetBuzzer(SCN_DISABLE); /** ブザー禁止 */
#if (PRO_IMAGE_PROCESSOR !=	IMAGE_PROCESSOR_LC82103)	/* 1998/10/02 by T.Soneoka */
	SCN_Init();					/** スキャナー用ゲートアレイの初期設定 */
#endif
	/*****DPR*****/
#if (PRO_DPRAM == ENABLE)		/* By J.Miyazaki 1996/08/12 */	/**プリンタ初期化の前に移動 97/06/26 M.Kotani*/
	DPRD_InitializeInterface();	/**DPRAM通信を開始するための一連の初期化*/
 #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/06/14 */
	MAN_InitilizeOptionBoard();	/* Add By O.Kimoto 1996/11/18 */
 #endif
#endif

	/*****PRN*****/
	cre_tsk(&tskno_CMN_MultiTimer10msTask,TSK_CMN_MULTITIMER10MSTASK,0); /*プリンターデバイスの初期化でイベント待ちするためイベントを発行するこのタスクを移動する By M.Kotani 1998/01/27*/
	/****************************************************************/
	/* プリンターの初期化（リセット）を実行							*/
	/****************************************************************/
#if (PRO_PRINT_TYPE == LASER)
	SCN_GeneratePrinter1KHz();	/** プリンタ用1KHzのセット */
	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP; /** プリンターリセット中のウォームアップヲセット Feb.23,1996 */
	DisplayWaitAMinutes(); /** ウォームアップ中の表示を出す */
	if (PRN_InitPrinter()) { /** プリンタまわりの初期設定 */	/**この前にＤＰＲの初期化がされていること*/
		/** プリンター初期化正常終了 */
	}
	else { /** プリンター異常 */
		/** プリンター初期化異常のステータスをセット */
		SYS_MachineStatus[SYS_PRINTER_STATUS3] |= SYS_PRINTER_RESET_ERROR;	/* ﾐﾉﾙﾀ ﾌﾟﾘﾝﾀｰ初期化エラー By S.K Jan.29,1996 */
	}
	SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_PRINT_WARMUP); /** プリンターリセット中のウォームアップヲセット Feb.23,1996 */
	UpdateDisplay(); /** プリンターウォームアップの表示を更新 Feb.23,1996 */
	PRN_1stPagePrintFlag = 1;		/* 電源ＯＮ直後の黒ライン対策 By S.Kawasaki 1996/08/22 */
#endif
#if (PRO_PRINT_TYPE == LED)
	SCN_GeneratePrinter1KHz();	/** プリンタ用1KHzのセット */
	PRN_InitHighVoltage();
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/19 */
	if (SYS_CheckerMode != CHECKER_ADF_ASSY) {
		PRN_InitPrinter();
	}
 #else
	PRN_InitPrinter();
 #endif
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)		/* For HINOKI By O.Kimoto 1998/09/07 */

	InitializeGateArray();	/* 1998/06/13 H.Yoshikawa */
#if (PRO_PRINT_TYPE == THERMAL)
	PRN_InitPrinter();
#endif
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)	/* 1998/10/02 by T.Soneoka */
	SCN_Init();
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) || defined(HINOKI3)	/* キー取込みが成功しないのでMAN_InitializeRAM()から移動 O.Oshima 2003/10/24 */ /* Add by Y.Kano 2004/12/21 */
	/***** チェッカー!!! *****/
	/* wai_tsk(1+SYB_MachineParameter[M_PARA_SW_B0]);	*//* O.Oshima 2003/10/24 */
	SYS_CheckerMode = CMN_StartCheckerModeKey();	/* CHECKER */
#endif

#if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/07 */
	if ((!CHK_WallHangSetting()) && !SYS_CheckerMode) { /** 壁掛け設定用 *//* Add by Y.kano 2003/10/07 *//* チェッカー対応 O.Oshima 2003/10/23 */
#endif
	/*---------------------------------------------------------------------
	** 電源ＯＮ時にイニシャルカットを行う。
	** 機種固有ＳＷの再定義し、共通関数を使用するようにする
	** 1998/08/19 H.Yoshikawa
	*/
	/* 【CSDR-No.152】 By O.Kimoto 1998/12/03 */
		if (CHK_UNI_PowerON_InitialCut()) {
			if ( !RXIL() /* && (PS1() || PS2()) */ ) {	/** パワーオン時にプリンターカバーが閉まっている場合 */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;		/* プリンター使用中をセット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT;		/* イメージ・プリント中セット */
				SYS_DocumentPrintClass = SYS_PRINT_CLASS_INITIAL;				/* プリンター初期化 */
#if (0)
** 				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);	/* メモリ・プリント・タスク起動 */
#else
/* すいません、暫定的に下記のように変更させてください。
** HINOKIの方が完成すれば元に戻しますので。 By O.Kimoto 1998/10/27 */
#if (PRO_PRINT_TYPE == THERMAL_TRANS)
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0);	/* メモリ・プリント・タスク起動 */
#else
				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_COPYPRINTTASK, 0); /* HINOKI 暫定 By O.Kimoto 1998/10/27 */
#endif
#endif

			}
		}
		else {
			PRN_InitPrinter();
		}
#if defined(SATSUKI2)	/* 壁掛け設定用に追加 by Y.Kano 2003/10/07 */
	}
	else
	{
		PRN_InitPrinter();
	}
#endif	/* End of defined(SATSUKI2) */
#endif

	/*****SCN*****/
	/* 電源ON時のスキャナの初期化処理 T.Nose 1997/01/17
	** 電源ON直後は、SYS_MachineStatusを初期化中にして
	** ミラーキャリッジを待機位置へ移動する
	*/

#if (PRO_FBS == ENABLE)
	SCN_RegularDocumentSize = SYS_REGULAR_SIZE_UNKNOWN;
#endif

	MAN_InitializeScanner(); /* man_oprm.c でも同じ処理を行うため関数化 */

#if defined (KEISATSU) /* 警察FAX 05/06/09 石橋正和 */
	S1_Initialize(); /* S1初期化 */
#endif

#if (PRO_MODEM == R288F)	/* ROCKWELL製 28.8K */
#if (PRO_PANEL == KANJI)	/* Added by H.Kubo 1997/08/13 */
	/* 谷＠電子設計氏からこのポートの初期状態をＯＦＦにしておいてほしいとの依頼があった為
	** By O.Kimoto 1998/03/14
	*/
	RI_Off();
#endif
#if  defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || (defined(POPLAR_H) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)	/* 1998.6.12 K.Kawata */ /* HINOKI 1998/09/21 H.Hirao */ /* Changed by H.Kubo 1998/11/18 */ /* HINOKI2 2001/11/13 T.Takagi */	/* POPLAR_H For FM336P By Y.Suzuki 2002/06/11*/
	Reset288ModemOn();
	Reset288ModemOff();
#endif
#if defined(SAKAKI) || defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2) || (defined(POPLAR_H) && defined(JP0)) /* 1998.6.12 K.Kawata */ /* HINOKI 1998/09/21 H.Hirao */ /* Modem Reset code is deleted by H.Kubo 1998/11/18 */ /* HINOKI2 2001/11/13 T.Takagi */ /* POPLAR_H For FM336P By Y.Suzuki 2002/06/11*/
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/19 */
	if (SYS_CheckerMode != CHECKER_ADF_ASSY) {
		MDM_ModemInitialize(); /* モデムドライバの変数の初期化もします。 by H.Kubo 1998/09/03 */
		/* SYS_ModemVersion に R288F のバージョンを設定します。 */
		MDM_InitializeModemCheck(); /* Ported from CLOVER by H.Kubo 1997/11/05 */
	}
 #else
	MDM_ModemInitialize(); /* モデムドライバの変数の初期化もします。 by H.Kubo 1998/09/03 */
	/* SYS_ModemVersion に R288F のバージョンを設定します。 */
	MDM_InitializeModemCheck(); /* Ported from CLOVER by H.Kubo 1997/11/05 */
 #endif
	
	/*---------------------------------------------------------------------
	** InitializeFaxCom()の中で、SYB_T30Monitor.WritePointer = 0;され、
	** そのために、T30モニターがプリントできなくなる
	** SYB_T30Monitor.WritePointerに0を代入された後、すぐに電源OFFされると、
	** T30モニターがプリントできなくなります。
	** 1998/10/29 H.Yoshikawa 
	*/
  #if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/10/29 H.Yoshikawa */
	t30_wr_ptr = SYB_T30Monitor.WritePointer;	/** T30モニタ・データ用ライトポインタ */
	InitializeFaxCom();
	SYB_T30Monitor.WritePointer = t30_wr_ptr;	/** T30モニタ・データ用ライトポインタ */
  #endif

#else

 #if defined(POPLAR_F)
	/**** MDM ****/
	if (Exist288Modem()) {
		/* Ｒ２８８Ｆのハードリセット実行 */
		Reset288ModemOn();
		wai_tsk(10/10); /* RESET 端子の 0 を少なくとも 3us 保つ。 */
		Reset288ModemOff();

		MDM_ModemInitialize(); /* モデムドライバの変数の初期化もします。 1999/12/01 Y.M */

		/* SYS_ModemVersion に R288F のバージョンを設定します。 */
		MDM_InitializeModemCheck(); /* Ported from CLOVER by H.Kubo 1997/11/05 */
	}
	else {
		SaveReturnAddressAndJumpBegin();
	}
  #else
	/**** MDM ****/
	if (Exist288Modem()) {
		/* Ｒ２８８Ｆのハードリセット実行 */
		SYS_COM_PortStatus &= ~IO_BIT_MRESM;
		outpw(COM_PORT, SYS_COM_PortStatus);
		SYS_COM_PortStatus |= IO_BIT_MRESM;
		outpw(COM_PORT, SYS_COM_PortStatus);
		/* SYS_ModemVersion に R288F のバージョンを設定します。 */
		MDM_InitializeModemCheck(); /* Ported from CLOVER by H.Kubo 1997/11/05 */
	}
	else {
		/* ＰＯＰＬＡＲ＿Ｈはここに来てはいけない */
		SaveReturnAddressAndJumpBegin();
	}
 #endif
#endif
#endif

#if (PRO_EXT_DMAC == DISABLE)	/* 1997/12/16 Y.M */
	DMA_DTC_RequestReqEnable();
#endif

#if (PRO_DIALIN == ENABLE) && (PRO_NCU_TYPE == HINOKI_TYPE)	/* T.Nose 1998/12/21 */
	NCU_DICPU_Initialize();
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/10 */
	/* 1999/10/22 M.Matsumoto
	 * 音声ＬＳＩ(MSM9805)の初期化を行う
	*/
	MDM_AnswerLSI_Initialize();

  #if defined(HINOKI2) && defined(JPNNTT)	/* Add by J.Kishida 2002/09/12 */
	SetTestLand13_On();
  #endif
 #endif
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*By Y.Suzuki 2002/06/07*/
	/*----------------------------------
	**電源ON時にｺｰﾃﾞｯｸ初期化する。
	*/
	CDC_InitializeCodec();
#endif

}

/*************************************************************************
	module		:[待機状態で動作しているタスク生成]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void MAN_InitializeTaskCreate(void)
{
	/****************************************************************/
	/* 待機状態で動作しているタスク生成								*/
	/****************************************************************/
	cre_tsk(&tskno_MAN_SensorTask, TSK_MAN_SENSORTASK, 0);
	cre_tsk(&tskno_MAN_TimerTask, TSK_MAN_TIMERTASK, 0);
	cre_tsk(&tskno_OPR_Task, TSK_OPR_TASK, 0);
	cre_tsk(&tskno_OPR_SubMessageReceiveTask, TSK_OPR_SUBMESSAGERECEIVETASK, 0);
	cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/11 */
	cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
	/* 2回線呼出監視仕様変更 Modified by SMuratec 李 2005/10/19 */
	cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
 #endif /* defined (KEISATSU) */
	/*cre_tsk(&tskno_CMN_MultiTimer10msTask,TSK_CMN_MULTITIMER10MSTASK,0); プリンターデバイスの初期化でイベント待ちするためイベントを発行するこのタスクを移動する By M.Kotani 1998/01/27*/

#if (PRO_CLASS1 == ENABLE) /* 1996/02/21 Eguchi */

	SYS_CL1_Status = 0;		/* とりあえずクリアしておく */

	CL1_RSHardWareCheck();
	if (SYS_RS232C_Exist) {
		cre_tsk(&tskno_CL1_Task, TSK_CL1_TASK, 0 );
	}
#endif

#if (PRO_PRINT_TYPE == LED)
	/*
	** センサータスクのイニシャルが走らずSYS_DrumUnitStatusが０のまま
	** ウォームアップタスクが走るため”ドラムガアリマセン”エラーがでる
	*/
 #if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/08/08 */
	if ((SYS_CheckerMode != CHECKER_ADF_ASSY) && (SYS_CheckerMode != CHECKER_MAIN_TEST)) {
		DisplayWaitAMinutes(); /** ウォームアップ中の表示を出す */
	}
 #else
	DisplayWaitAMinutes(); /** ウォームアップ中の表示を出す */
 #endif
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;
	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_PRINT_WARMUP;
	SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PRINTER_POWER_ON;

	wai_tsk(100);

	cre_tsk(&tskno_PRN_FuserTempTask, TSK_PRN_FUSERTEMPTASK, 0);
	cre_tsk(&tskno_PRN_PrinterWarmUpTask, TSK_PRN_PRINTERWARMUPTASK, 0);
#endif

#if defined(POPLAR_F)
	cre_tsk(&tskno_MDM_InternalStatus, TSK_MDM_CHECKINTERNALSTATUSTASK, 0);
#endif

}

/*************************************************************************
	module		:[電源ＯＮ時のマルチ回線の初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/12/09]
	author		:[村田]
*************************************************************************/
void MAN_MultiLinePowerOnInitial(void)
{
	UWORD	i;

	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		SYS_OptionLineStatus[i] = 0x00;
	}

	OptMessageRead = 0;
	OptMessageWrite = 0;
	for (i = 0; i < SYS_OPTION_MESSAGE_MAX; i ++) {
		SYS_OptionMessage[i].Status = 0;
		SYS_OptionMessage[i].Item = 0xFFFF;
		SYS_OptionMessage[i].Message = 0xFFFF;
		SYS_OptionMessage[i].SubMessage1 = 0xFFFF;
		SYS_OptionMessage[i].SubMessage2 = 0xFFFF;
		SYS_OptionMessage[i].SubMessage3 = 0xFFFF;
		SYS_OptionMessage[i].SubMessage4 = 0xFFFF;
	}

	SYS_OptionFaxComUpDataDisplay = 0;
	OptSendMessageCounter = 0;

	SYS_ChangedSRAM_Status = 0;

	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i++) {	/* 1997/01/30 Y.Murata */
		SYS_PreLineBusyCheckStatus[i] = 0;
	}

/* #if (PRO_MULTI_LINE == ENABLE) @* ＡＮＺＵ＿ＣのＭＡＫＥを通す為 BY H.H 1997/03/06 */
	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i++) {	/* 1997/02/18 Y.Murata */
		SYB_OptionROM_Revision[i][0] = 0;
	}
/* #endif */

	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		SYS_JournalRequest[i] = SYS_JOURNAL_REQ_NOTHING;
	}

	/* オプションモデムデータ転送用バッファクリア */
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		ClearOptionModemDataArea((unsigned char)i);
	}

	FaxComCompleteDisplaySign = 0;

#if defined (KEISATSU)				
	FaxComCompleted = TRUE;			/* 警察FAX DVT_ID43 Added by SMuratec K.W.Q 2005/11/15 */
	NCUSndMsg		= FALSE;			/* 警察FAX DVT Added by SMuratec 李 2005/11/30 */
	Hangup_Line	= 0;				/* 警察FAX DVT by SMuratec 夏 2005/11/19 */
	IsJournalCompleted = TRUE;		/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 */
#endif		/* End of (defined (KEISATSU)) */


	/***********************************************************************/
	/* コマンドスキャナ送信時の属性 1997/01/27 Y.Murata                    */
	/***********************************************************************/
	SYS_ScannerTxAbility0 = 0;
	SYS_ScannerTxAbility1 = 0;
	SYS_ScannerTxAbility2 = 0;
	SYS_ScannerTxAbility3 = 0;

}


void ClearOptionModemDataArea(UBYTE number)
{
	UWORD	j;

	SYS_Opt[number].SYS_FaxCommStage = 0;
	SYS_Opt[number].SYS_CurrentExecQueueNo = 0;
	SYS_Opt[number].SYS_DocBlock_Src_Size = 0;
	SYS_Opt[number].SYS_DocBlock_Src_Mode = 0;
	SYS_Opt[number].SYS_DocBlock_Dst_Size = 0;
	SYS_Opt[number].SYS_DocBlock_Dst_Mode = 0;
	SYS_Opt[number].GrayModeFlag = 0;
	SYS_Opt[number].FaxComTXorRX_Sign = 0;
	SYS_Opt[number].SYS_FaxComType = 0;
	SYS_Opt[number].SYS_FaxComTxType = 0;
	SYS_Opt[number].TxBaudRate = 0;
	SYS_Opt[number].RxBaudRate = 0;
	SYS_Opt[number].TxECM_Mode = 0;
	SYS_Opt[number].RxECM_Mode = 0;
	SYS_Opt[number].FinalRxMode = 0;
	SYS_Opt[number].SYS_RxMemoryFileItem = 0;
	SYS_Opt[number].TxMemoryFileItem = 0;
	SYS_Opt[number].RxMode = 0;
	SYS_Opt[number].TxMode = 0;
	SYS_Opt[number].FaxCompatibleErrorCode = 0;
	SYS_Opt[number].SYS_ManualFaxCommErrRequest = 0;
	SYS_Opt[number].SYS_VoiceCallAccepted = 0;
	SYS_Opt[number].SYS_TensouJushinFlag = 0;
	SYS_Opt[number].FirstTxMode = 0;
	SYS_Opt[number].SYS_V34ProcedureExecutingFlag = 0;
	SYS_Opt[number].CommandFileOptionItem = 0;
	SYS_Opt[number].CommandFilePage = 0;
	SYS_Opt[number].FCM_DataBasePollingNumber = 0;

	SYS_Opt[number].SYS_TxTotalPage = 0;
	SYS_Opt[number].SYS_RxTotalPage = 0;
	SYS_Opt[number].TxMemoryFilePage = 0;
	SYS_Opt[number].MDM_RxTotalLine = 0;
	SYS_Opt[number].MDM_RxErrorTotalLine = 0;
	SYS_Opt[number].BatchTxFinishPage = 0;
	SYS_Opt[number].FaxComResult = 0;
	SYS_Opt[number].BackUpFaxComResult = 0;
	SYS_Opt[number].JournalTxTotalCount = 0;
	SYS_Opt[number].JournalRxTotalCount = 0;
	SYS_Opt[number].SYS_RxMemoryFileNo = 0;
	SYS_Opt[number].TxMemoryFileBoxNumber = 0;
	SYS_Opt[number].NonStandardID[0] = 0;
	SYS_Opt[number].StandardID[0] = 0;
	SYS_Opt[number].BackUpStandardID[0] = 0;

	for (j = 0; j < SYS_ERROR_PAGE; j++) {
		SYS_Opt[number].TxResponsedRTN_PageSign[j] = 0;
	}
	for (j = 0; j < OPT_ERR_LINE_DATA_MAX; j++) {
		SYS_Opt[number].MDM_RxTotalLineSave[j] = 0;
		SYS_Opt[number].MDM_RxErrorTotalLineSave[j] = 0;
	}


	/* 1998/02/03 Y.Murata	CHAR_JOURNAL
	 * キャラクタジャーナル記載用データ初期化
	*/
	SYS_Opt2[number].QueueKind = 0;
	SYS_Opt2[number].QueueDialItem = 0;
	SYS_Opt2[number].QueueDialOffset = 0;
	SYS_Opt2[number].CommandDepartmentCode = 0;
	for (j = 0; j < SYS_DIRECT_DIAL_MAX; j++) {
		SYS_Opt2[number].CommandDirectDial[j] = 0xFF;
	}

}


/*************************************************************************
	module		:[電源ON時のスキャナの初期化処理]
	function	:[
		電源ON直後は、SYS_MachineStatusを初期化中にして
		ミラーキャリッジを待機位置へ移動する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		コンパイル時の"out of heap space"解消のために抜き出しました。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/08/10]
	author		:[竹内茂樹]
*************************************************************************/
void MAN_InitializeScanner( void )
{
#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/26 */
	if (SYS_CheckerMode == CHECKER_ADF_ASSY) {
		GearBackLashRequest = FALSE;	/* ギアバックラッシュ予約しない */
	}
	else {
		GearBackLashRequest = TRUE;		/* ギアバックラッシュ予約する */
	}
#else
	GearBackLashRequest = TRUE;		/* ギアバックラッシュ予約する */
#endif
	SCN_IsMotorClockwise = TRUE;	/* モーターの回転方向の状態は正転にしておく */
#if (PRO_FBS == ENABLE)
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
	SYS_MachineStatus[SYS_SCANNER_STATUS] |= (SYS_SCANNER_MIRROR_INIT | SYS_SCANNER_MIRROR_BUSY);
	SCN_IsLampCheckFinish = TRUE;	/* ランプチェック状態を初期化(あとで使う変数) 使われていない T.Nose */
	SCN_MotorDriveMode = SCN_ADF;	/* 現在のモーター駆動経路の状態を、一旦ADF側にする */
	SCN_MirrorCarriageStatus = MIRROR_POWER_ON;
	MirrorTaskInstruction = MIRROR_TASK_INITIALIZE;	/* ミラーの動作を指定する */
	/* 輸送モード変数のゴミ対策  1997/03/17 */
	if (!SYB_ScannerTransportMode 	/** 輸送モードじゃない時 */
	 && !RXIL()) { /* プリンタカバーが閉じている時 */
		MirrorTaskRequest = TRUE;		/* ミラータスク起動要求をセットする */
	}
	else {
		/* FBS輸送モード中はスキャナ(ミラーキャリッジ)を初期化しない  1997/03/05 */
		MirrorTaskRequest = FALSE;		/*  */
	}

	DocumentResetOperation = FALSE;		/* 原稿セットやり直し操作要求フラグ T.Nose 1997/08/21 */

	/* ミラーキャリッジの待機位置の初期化 *//* 本モジュール内に移動 T.Nose 1997/10/27 */
	if (CHK_UNI_MirrorReadyModeVariable()) { /* 待機位置可動モード */
		SCN_MirrorReadyPosition = READY_POSITION_ADF;
	}
	else { /* 待機位置固定モード */
		if (CHK_UNI_MirrorStaticPositionADF()) {
			SCN_MirrorReadyPosition = READY_POSITION_ADF;
		}
		else {
			SCN_MirrorReadyPosition = READY_POSITION_FBS;
		}
	}

	/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件
	** T.Nose 1997/12/20
	*/
	DEBUG_MirrorMoveCountStart = 0;	/* カウント開始フラグリセット */
	DEBUG_MirrorNeedInitial = 0;	/* ミラーキャリッジ初期化要求リセット */
	DEBUG_OperationExitFlag = 0;	/* シェーディングオペレーション終了フラグ */
#endif
	SCN_MirrorStopTimeoutCount = 0;	/* 1997/03/07 */

	/* バックラッシュのタイムアウト処理の初期化  1997/05/09 */
	GearBackLashRetryCount = 0;
	GearBackLashTimer = 0;
	GearBackLashTimeout = FALSE;

	/* メモリー送信原稿降誕縮む件 T.Nose 1997/11/03 */
	DEBUG_DocumentScanning = 0;

}


#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/15*/
/************************************************************************
	module		:[省エネモードへ移行処理]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INI]
	date		:[2002/06/15]
	author		:[Y.Suzuki]
************************************************************************/
void INI_SleepSystem(void)
{
	PSRESET(FALSE);
	PCON(FALSE);
	wai_tsk(1);
	CLKCON(FALSE);
}


/************************************************************************
	module		:[省エネモードからの復帰処理]
	function	:[]
	return		:[なし]
	common		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INI]
	date		:[2002/06/15]
	author		:[Y.Suzuki]
************************************************************************/
void INI_WakeUpSystem(void)
{
	CLKCON(TRUE);
	wai_tsk(1);
	PSRESET(TRUE);
	/*コーデック初期化*/
	CDC_InitializeCodec();
	PCON(TRUE);
}
#endif
