/**********************************************************************
*	ANZU
*
*	File	Name:	NCU_OH.C
*	Coded	  by:	坂本直史
*	Module	Name:	OhPortStatusRead()
*					BranchDataInitialize()
*					OnToOffHookLevelCheck()
*					OffToOnHookLevelCheck()
*					CMLAndOffHookLevelCheck()
*					CiInputLevelCheck()
*					InitializeBRCOhBuffer()
*					SetStableTime()
*					BRCTelOhCounterSet()
*					BRCOhLevelCorrect()
*					DetectLineLevelState()
*					DetectBranchPortState()
*					LineVoltLevelPortBarrier()
*					NCU_TelephoneHookCheckTask()
*
*	Note		:	ＨＯＯＫ状態監視モジュール
*
***********************************************************************/
/*
 * ATLANTAに移植 1996/12/02 Eguchi
 * (1)インクルードファイルのパス変更
 * (2)不要なパスを削除
 *    内線通話、内蔵ＴＡＤ、ブランチ、Ｈ８、Ｖ５３・・・
 * (3)far/near削除
 * (4)unsigned char -> UBYTE
 * (5)構造体の定義->けつに"_t"を付ける
 */
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\sysdiali.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\atd_def.h"
#include	"\src\atlanta\define\buzzer.h"
#include	"\src\atlanta\define\cmn_def.h" /* 1996/02/22 Eguchi @SYS_SPK_OUT_FAKEBUZZER@ */

#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#include 	"\src\atlanta\define\uni_pro.h"

#include	"\src\atlanta\define\ncu_pro.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\ncu_msg.h"
#include	"\src\atlanta\define\ncu_ret.h"
#include	"\src\atlanta\define\ncu_cnst.h"
#include	"\src\atlanta\define\ncu_def.h"

#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#endif

#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\bkupram.h"

#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\ncu_tbl.h"

#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include	"\src\atlanta\sh7043\define\def_tib.h"

#include	"\src\atlanta\ext_v\atd_tbl.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\define\status.h"	/* 1998/01/24  By T.Yamaguchi */
#include	"\src\atlanta\sh7043\define\sh_sys.h"	/* 1998/01/24  By T.Yamaguchi */
#include	"\src\atlanta\define\unisw_g.h"	/* 1998/01/26  By T.Yamaguchi */

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
#include	"\src\atlanta\mdm\fm336\define\mdm_io.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\evttomsg.h"
#include	"\src\memsw\define\mem_sw_a.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/29 */
#include	"\src\atlanta\define\sys_line.h"
/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/05 */
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#include "\src\memsw\define\mem_sw_g.h"/* 1996/04/17 Eguchi */
/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
#include	"\src\atlanta\ext_v\man_data.h"
#endif /* defined (KEISATSU) */

#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
extern UWORD tskno_RemoteRxSignalDetTask;	/* 1998/01/24  By T.Yamaguchi */
extern UWORD	tskno_NCU_TelephoneOperation;
extern UBYTE	LineStatusBk;
extern UWORD	tskno_NCU_ND_Rx;

static UBYTE	HDSTOnCount 	= 40;
static UBYTE	HDSTOffCount 	= 40;
/* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/09 */
static UBYTE	STDTel2OnCount 	= 40;
static UBYTE	STDTel2OffCount	= 40;
static UBYTE	EXTTel2OnCount 	= 40;
static UBYTE	EXTTel2OffCount	= 40;
#endif /* defined (KEISATSU) */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ＯＨのＩ／Ｏポートを回線監視部内部変数に変換]
	function	:[
		1.ＯＨのＩ／ＯポートをＲｅａｄし回線監視モジュール内大域変数にセットする。
	]
	return		:[なし
	]
	common		:[
		OhPortStatus	:ＯＨのＩ／Ｏポートの状態を記憶
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void       OhPortStatusRead( void )
{
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
	/*---------------------*/
	/** 標準回線電話のＯＨ状態 */
	/*---------------------*/
	/* 転送受信の確認音仕様 警察FAX Modify by SMuratec 李 2005/10/12 */
	if (!ModemRelaySetting() && (TADStatus & REMOTE_RECEIVE)) {	/* 標準回線で転送受信 */
	}
	else {
		if( (OffHook1() && !HDST_RelaySetting()) /* ハンドセットは標準回線でOFFHOOK状態 */
		    || OffHook2() ){
			OhPortStatus |= TEL1_OFF_HOOK;	/* 標準回線電話（外付電話未だは付属電話）オフフック */
		}
		else {
			OhPortStatus &= ~TEL1_OFF_HOOK;	/* 標準回線電話（外付電話未だは付属電話）オンフック */
		}
	}
	
	/*---------------------*/
	/** 拡張回線電話のＯＨ状態 */
	/*---------------------*/
	/* 転送受信の確認音仕様 警察FAX Modify by SMuratec 李 2005/10/12 */
	if (ModemRelaySetting() && (TADStatus & REMOTE_RECEIVE)) {	/* 拡張回線で転送受信 */
	}
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
	else if ((!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM))
			&& ((CHK_LineSetting() && CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
			|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
			|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY))) { /* ナンバーディスプレイ起動している場合 */
		if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
			OhPortStatus &= ~TEL2_OFF_HOOK;
		}
		else if (CHK_LineSetting() && CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE)){
			if (!(SYS_LineTelStatus & EXT_TEL2_OFFHOOK)) {
				if (SYS_RingCounterExt) {
					SYS_RingCounterExt = 0;
				}
			}
		}
	}
	else {
		if( (OffHook1() && HDST_RelaySetting()) /* ハンドセットは拡張回線でOFFHOOK状態 */
		    || OffHook3() ){
			OhPortStatus |= TEL2_OFF_HOOK;	/* 拡張回線電話（外付電話未だは付属電話）オフフック */
		}
		else {
			OhPortStatus &= ~TEL2_OFF_HOOK;	/* 拡張回線電話（外付電話未だは付属電話）オンフック */
		}
	}
	
#else /* !defined (KEISATSU) */

#if (0) /* (PRO_NCU_TYPE == HINOKI_TYPE) comment by H.Hirao 1999/03/15 */
//	BOOL	is_enable_int;
#endif
	/*---------------------*/
	/** 付属電話のＯＨ状態 */
	/*---------------------*/
	if( OffHook1()){
		OhPortStatus |=  TEL1_OFF_HOOK;
#if (PRO_ECO_MODE == ENABLE) /* 2002/09/25 By M.Maeda */
		MAN_ChangeEcoMode(0);
#endif
	}
	else{
		OhPortStatus &= ~TEL1_OFF_HOOK;
#if (0) /* (PRO_NCU_TYPE == HINOKI_TYPE) comment by H.Hirao 1999/03/15 */
//		/* added by H.Hirao 1999/03/13 */
//		is_enable_int = CheckInterruptEnable();
//		CMN_DisableInterrupt();
//		Tel1OhTimer = SYS_GeneralTimer;
//		if (is_enable_int) {
//			CMN_EnableInterrupt();
//		}
#endif
	}
	/*---------------------*/
	/** 外付電話のＯＨ状態 */
	/*---------------------*/
	if( OffHook2()){
		OhPortStatus |=  TEL2_OFF_HOOK;
#if (PRO_ECO_MODE == ENABLE) /* 2002/09/25 By M.Maeda */
		MAN_ChangeEcoMode(0);
#endif
	}
	else{
		OhPortStatus &= ~TEL2_OFF_HOOK;
#if (0) /* (PRO_NCU_TYPE == HINOKI_TYPE) comment by H.Hirao 1999/03/15 */
//		/* added by H.Hirao 1999/03/13 */
//		is_enable_int = CheckInterruptEnable();
//		CMN_DisableInterrupt();
//		Tel2OhTimer = SYS_GeneralTimer;
//		if (is_enable_int) {
//			CMN_EnableInterrupt();
//		}
#endif
	}
#endif /* defined (KEISATSU) */
}


#if defined (KEISATSU) /* Modify by SMuratec 李 2005/08/01 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[２回線状態を更新]
	function	:[
	]
	return		:[なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/08/01 ]
	author		:[SMuratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void       LineStatusRead( void )
{
	/*---------------------*/
	/** 付属電話のＯＨ状態 */
	/*---------------------*/
	 /* ハンドセットは通信中の拡張回線に接続されたない場合 */
	/* 転送受信の確認音仕様 警察FAX Modify by SMuratec 李 2005/10/12 */
	if (!HDST_RelaySetting() && !ModemRelaySetting() && (TADStatus & REMOTE_RECEIVE)) {	/* 標準回線で転送受信 */
	}
	/* 転送受信の確認音仕様 警察FAX Modify by SMuratec 李 2005/10/12 */
	else if (HDST_RelaySetting() && ModemRelaySetting() && (TADStatus & REMOTE_RECEIVE)) {	/* 拡張回線で転送受信 */
	}
	else if( OffHook1()){
		if (HDSTOffCount != 40) {
			HDSTOffCount = 40;
		}
		/* 付属電話状態はオンフックの場合 */
		if (!HDST_RelaySetting()) {	/* ハンドセットは標準回線でOFFHOOK状態 */
			if (!(NCU_LineStatus & STD_HDST_OFFHOOK)) {
				if (!(--HDSTOnCount)) {
					HDSTOnCount = 40;
					NCU_LineStatus &= ~EXT_HDST_OFFHOOK;
					NCU_LineStatus |= STD_HDST_OFFHOOK;	/* 付属電話は標準回線でオフフック */
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_HDST_EXT_OFFHOOK;
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_HDST_STD_OFFHOOK;
				}
			}
			else if (((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_EXT)
					&& !OffHook2()) {
				if (!(--HDSTOnCount)) {
					HDSTOnCount = 40;
					SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
					SYS_LineTelStatus |= STD_READY;
					Tel1OhCounter = 1;
					NCU_LineStatus &= ~(EXT_HDST_OFFHOOK | STD_HDST_OFFHOOK);
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_HDST_EXT_OFFHOOK | SYS_HDST_STD_OFFHOOK);
					OhPortStatus &= ~TEL1_OFF_HOOK;
				}
			}
			else {
				SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_HDST_EXT_OFFHOOK;
				SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_HDST_STD_OFFHOOK;
				HDSTOnCount = 40;
			}
		}
		else {						/* ハンドセットは拡張回線でOFFHOOK状態 */
			if (!(NCU_LineStatus & EXT_HDST_OFFHOOK)) {
				if (!(--HDSTOnCount)) {
					HDSTOnCount = 40;
					NCU_LineStatus &= ~STD_HDST_OFFHOOK;
					NCU_LineStatus |= EXT_HDST_OFFHOOK;	/* 付属電話は拡張回線でオフフック */
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_HDST_STD_OFFHOOK;
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_HDST_EXT_OFFHOOK;
				}
			}
			else if (((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_EXT)
					&& !OffHook3()) {
				if (!(--HDSTOnCount)) {
					HDSTOnCount = 40;
					SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
					SYS_LineTelStatus |= EXT_READY;
					Tel2OhCounter = 1;
					NCU_LineStatus &= ~(EXT_HDST_OFFHOOK | STD_HDST_OFFHOOK);
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_HDST_EXT_OFFHOOK | SYS_HDST_STD_OFFHOOK);
					OhPortStatus &= ~TEL2_OFF_HOOK;
				}
			}
			else {
				SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_HDST_STD_OFFHOOK;
				SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_HDST_EXT_OFFHOOK;
				HDSTOnCount = 40;
			}
		}
	}
	else {
		if (HDSTOnCount != 40) {
			HDSTOnCount = 40;
		}
		/* 付属電話状態はオフフックの場合 */
		if (NCU_LineStatus & (EXT_HDST_OFFHOOK | STD_HDST_OFFHOOK)) {
#if 0 /* 警察FAX DVT_ID68 Modified By SMuratec 李 2005/12/15 */
@@			if (!IsDailing /* 本体ダイヤルではない場合 */
@@				&& !(!HDST_RelaySetting() && !ModemRelaySetting() && (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_CONT24_LINE_BUSY))
#else
			if (!(!HDST_RelaySetting() && !ModemRelaySetting() && (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_CONT24_LINE_BUSY))
#endif
				&& !(HDST_RelaySetting() && ModemRelaySetting() && (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_CONT24_LINE_BUSY))
				){
				if (!(--HDSTOffCount)) {
					HDSTOffCount = 40;
					NCU_LineStatus &= ~(EXT_HDST_OFFHOOK | STD_HDST_OFFHOOK);
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_HDST_EXT_OFFHOOK | SYS_HDST_STD_OFFHOOK);
				}
			}
		}
		else if (((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_USED_IN_HDST)
				&& (NCUStatus & TELEPHONE1_OFF_HOOK)) {
			/* 警察FAX DVT_ID68 Added By SMuratec 李 2005/12/15 */
			if (!IsDailing) { /* 本体ダイヤルではない */
				SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
				SYS_LineTelStatus |= STD_READY;
			}
			Tel1OhCounter = 1;
			OhPortStatus &= ~TEL1_OFF_HOOK;
		}
		else if (((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_USED_IN_HDST)
				&& (NCUStatus & TELEPHONE2_OFF_HOOK)) {
			/* 警察FAX DVT_ID68 Added By SMuratec 李 2005/12/15 */
			if (!IsDailing) { /* 本体ダイヤルではない */
				SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
				SYS_LineTelStatus |= EXT_READY;
			}
			Tel2OhCounter = 1;
			OhPortStatus &= ~TEL2_OFF_HOOK;
		}
		else {
			SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_HDST_EXT_OFFHOOK | SYS_HDST_STD_OFFHOOK);
			HDSTOffCount = 40;
		}
	}
	
	/* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/09 */
	if( OffHook2()){
		if (STDTel2OffCount != 40) {
			STDTel2OffCount = 40;
		}
		/* 外付電話状態はオンフックの場合 */
		if (!(SYS_LineTelStatus & STD_TEL2_OFFHOOK)) {
			if (!(--STDTel2OnCount)) {
				STDTel2OnCount = 40;
				SYS_LineTelStatus |= STD_TEL2_OFFHOOK;	/* 付属電話は標準回線でオフフック */
			}
		}
	}
	else {
		if (STDTel2OnCount != 40) {
			STDTel2OnCount = 40;
		}
		/* 付属電話状態はオフフックの場合 */
		if (SYS_LineTelStatus & STD_TEL2_OFFHOOK) {
			if (!(--STDTel2OffCount)) {
				STDTel2OffCount = 40;
				SYS_LineTelStatus &= ~STD_TEL2_OFFHOOK;
			}
		}
	}
	
	/* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/09 */
	if( OffHook3()){
		if (EXTTel2OffCount != 40) {
			EXTTel2OffCount = 40;
		}
		/* 外付電話状態はオンフックの場合 */
		if (!(SYS_LineTelStatus & EXT_TEL2_OFFHOOK)) {
			if (!(--EXTTel2OnCount)) {
				EXTTel2OnCount = 40;
				SYS_LineTelStatus |= EXT_TEL2_OFFHOOK;	/* 付属電話は標準回線でオフフック */
			}
		}
	}
	else {
		if (EXTTel2OnCount != 40) {
			EXTTel2OnCount = 40;
		}
		/* 付属電話状態はオフフックの場合 */
		if (SYS_LineTelStatus & EXT_TEL2_OFFHOOK) {
			if (!(--EXTTel2OffCount)) {
				EXTTel2OffCount = 40;
				SYS_LineTelStatus &= ~EXT_TEL2_OFFHOOK;
			}
		}
	}
	
	if ((OhPortStatus & TEL2_OFF_HOOK) && (Tel2OhCounter == 1)) {   /* 拡張回線電話オフフック */
		if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
			switch (NCU_LineStatus & EXT_LINE_STATUS) { /* 拡張回線状態 */
			case EXT_NOT_USE:	/* 待機状態 */
			case EXT_CI_IN:		/* 呼出中 */
				if (SYS_RingCounterExt) {
					NCU_LineStatus &= ~EXT_LINE_STATUS;
					NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
				}
				else {
					NCU_LineStatus &= ~EXT_LINE_STATUS;
					NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_TRANSMIT);
				}
				break;
			case EXT_IN_USE:		/* 拡張回線には本体使用中 */
				if (IsDailing) {	/* 本体ダイヤル中 */
					if (SYS_RingCounterExt) {
						LineStatusBk &= ~EXT_LINE_STATUS;
						LineStatusBk |= (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
					}
					else {
						LineStatusBk &= ~EXT_LINE_STATUS;
						LineStatusBk |= (EXT_LINE_STATUS & EXT_TEL_TRANSMIT);
					}
				}
				break;
			default:	/* 其の他 */
				break;
			}
		}
	}

	if (!(OhPortStatus & TEL2_OFF_HOOK) && (Tel2OhCounter == 1)) { /* 拡張回線電話オンフック */
		if (NCUStatus & TELEPHONE2_OFF_HOOK) {
			switch (NCU_LineStatus & EXT_LINE_STATUS) { /* 拡張回線状態 */
			case EXT_TEL_RECEIVE:	/* 受話中 */
			case EXT_TEL_TRANSMIT:	/* 送話中 */
				NCU_LineStatus &= ~EXT_LINE_STATUS;
				NCU_LineStatus |= (EXT_LINE_STATUS & EXT_NOT_USE);
				break;
			case EXT_IN_USE:		/* 拡張回線には本体使用中 */
				if (!(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
					LineStatusBk &= ~EXT_LINE_STATUS;
					LineStatusBk |= (EXT_LINE_STATUS & EXT_NOT_USE);
					/* 通信中断していない場合 */
					SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
				}
				Tel2OhCounter = 40;
				break;
			default:	/* 其の他 */
				break;
			}
		}
	}

	if ((OhPortStatus & TEL1_OFF_HOOK) && (Tel1OhCounter == 1)) { /* 標準回線電話オフフック */
		if (!(NCUStatus & TELEPHONE1_OFF_HOOK)) {
			switch (NCU_LineStatus & STD_LINE_STATUS) { /* 標準回線状態 */
			case STD_NOT_USE:	/* 待機状態 */
			case STD_CI_IN:	/* 呼出中 */
				if (SYS_RingCounter) {
					NCU_LineStatus &= ~STD_LINE_STATUS;
					NCU_LineStatus |= (STD_LINE_STATUS & STD_TEL_RECEIVE);
				}
				else {
					NCU_LineStatus &= ~STD_LINE_STATUS;
					NCU_LineStatus |= (STD_LINE_STATUS & STD_TEL_TRANSMIT);
				}
				break;
			case STD_IN_USE:		/* 標準回線には本体使用中 */
				if (IsDailing) { /* 本体ダイヤル中 */
					if (SYS_RingCounter) {
						LineStatusBk &= ~STD_LINE_STATUS;
						LineStatusBk |= (STD_LINE_STATUS & STD_TEL_RECEIVE);
					}
					else {
						LineStatusBk &= ~STD_LINE_STATUS;
						LineStatusBk |= (STD_LINE_STATUS & STD_TEL_TRANSMIT);
					}
				}
				break;
			default:
				break;
			}
		}
	}

	if (!(OhPortStatus & TEL1_OFF_HOOK) && (Tel1OhCounter == 1)) { /* 標準回線電話オンフック */
		if (NCUStatus & TELEPHONE1_OFF_HOOK) {
			switch (NCU_LineStatus & STD_LINE_STATUS) { /* 標準回線状態 */
			case STD_TEL_RECEIVE:	/* 受話中 */
			case STD_TEL_TRANSMIT:	/* 送話中 */
				NCU_LineStatus &= ~STD_LINE_STATUS;
				NCU_LineStatus |= (STD_LINE_STATUS & STD_NOT_USE);
				break;
			case STD_IN_USE:		/* 標準回線には本体使用中 */
				if (!(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
					LineStatusBk &= ~STD_LINE_STATUS;
					LineStatusBk |= (STD_LINE_STATUS & STD_NOT_USE);
					/* 通信中断していない場合 */
					SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
				}
				Tel1OhCounter = 40;
				break;
			default:	/* 其の他 */
				break;
			}
		}
	}

	if (!CHK_LineSetting()) { /* 回線設定 == 拡張回線 */
		if (((NCU_LineStatus & EXT_LINE_STATUS) != EXT_COM_IN_USE) 		/* 拡張回線は通信中ではない */
			&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ){	/* 拡張回線は本体使用中ではない */
			switch (NCU_LineStatus & STD_LINE_STATUS) { /* 標準回線状態 */
			case STD_COM_IN_USE:	/* 標準回線には通信中 */
			case STD_IN_USE:		/* 標準回線には本体使用中 */
				if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE){ /* 拡張回線には受話中 */
					if ( (CHK_KEIDENRxPriority())   /* 警電優先受信機能が有効されている場合 */
					&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
						/* 通信中断していない場合 */
						SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@						if (SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI) {
@@							if (RingStatus & CI_EXT_LINE) {
@@								RingStatus |= CI_DETECT_TIMEUP;
@@								det_evt(EVT_CI_CHECK);
@@							}
@@							else {
@@								RingStatus2nd |= CI_DETECT_TIMEUP;
@@								det_evt(EVT_2ND_CI_CHECK);
@@							}
#else
						if (RingStatus2nd & CI_EXT_LINE) {
							RingStatus2nd |= CI_DETECT_TIMEUP;
							det_evt(EVT_2ND_CI_CHECK);
#endif
						}
					}
				}
				break;
			default:
				/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
				if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
					|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
					|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
				}
				else
				if ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_NOT_USE) { /* 拡張回線は待機状態でわない */
					if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) ) {  /* 指令起動信号OFFの場合 */
						if (!ModemRelaySetting()) { /* モデムリレーを標準回線に接続している場合 */
							ModemRelay_On();        /** モデムリレーを拡張ライン側に倒します    */
						}
					}
				}
				else if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) 		/* 標準回線は受話中 */
						|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT) ){	/* 標準回線は送話中 */
					if (ModemRelaySetting()) {  /* モデムリレーを拡張回線に接続している場合 */
						ModemRelay_Off();       /** モデムリレーを標準ライン側に倒します    */
					}
				}
				if ((((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE)
						|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE))
						&& NCU_RemoteTransferDial()
						&& (tskno_NCU_TelephoneOperation != 0xFFFF)) {
					if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) && !ModemRelaySetting()) {
						if ((tskno_RemoteRxSignalDetTask == 0xFFFF) && !(TADStatus & REMOTE_RECEIVE)) {
							cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
						}
					}
					else if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) && ModemRelaySetting()) {
						if ((tskno_RemoteRxSignalDetTask == 0xFFFF) && !(TADStatus & REMOTE_RECEIVE)) {
							cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
						}
					}
				}
				break;
			}
		}
	}
	else {	/* 回線設定 == 標準回線 */
		if (((NCU_LineStatus & STD_LINE_STATUS) != STD_COM_IN_USE) 		/* 標準回線は通信中ではない */
			&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ){	/* 標準回線は本体使用中ではない */
			switch (NCU_LineStatus & EXT_LINE_STATUS) { /* 拡張回線状態 */
			case EXT_COM_IN_USE:	/* 拡張回線には通信中 */
			case EXT_IN_USE:		/* 拡張回線には本体使用中 */
				break;
			case EXT_TEL_RECEIVE:	/* 受話中 */
				/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
				if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
					|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
					|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
				}
				else
				if ( CHK_KEIDENRxPriority() ){   /* 警電優先受信機能が有効されている場合 */
					if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) ) {  /* 指令起動信号OFFの場合 */
						if (!ModemRelaySetting()) { /* モデムリレーを標準回線に接続している場合 */
							ModemRelay_On();        /** モデムリレーを拡張ライン側に倒します    */
						}
						if ((((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE)
								|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE))
								&& NCU_RemoteTransferDial()
								&& (tskno_NCU_TelephoneOperation != 0xFFFF)) {
							if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) && !ModemRelaySetting()) {
								if ((tskno_RemoteRxSignalDetTask == 0xFFFF) && !(TADStatus & REMOTE_RECEIVE)) {
									cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
								}
							}
							else if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) && ModemRelaySetting()) {
								if ((tskno_RemoteRxSignalDetTask == 0xFFFF) && !(TADStatus & REMOTE_RECEIVE)) {
									cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
								}
							}
						}
						break;
					}
				}
			default:
				/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
				if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
					|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
					|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
				}
				else 
				if ((NCU_LineStatus & STD_LINE_STATUS) != STD_NOT_USE) { /* 標準回線は待機状態でわない */
					if (ModemRelaySetting()) {  /* モデムリレーを拡張回線に接続している場合 */
						ModemRelay_Off();       /** モデムリレーを標準ライン側に倒します    */
					}
				}
				else if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) 		/* 拡張回線は受話中 */
						|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) ){	/* 拡張回線は送話中 */
					if ( !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) ) {  /* 指令起動信号OFFの場合 */
						if (!ModemRelaySetting()) { /* モデムリレーを標準回線に接続している場合 */
							ModemRelay_On();        /** モデムリレーを拡張ライン側に倒します    */
						}
					}
				}
				if ((((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE)
						|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE))
						&& NCU_RemoteTransferDial()
						&& (tskno_NCU_TelephoneOperation != 0xFFFF)) {
					if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) && !ModemRelaySetting()) {
						if ((tskno_RemoteRxSignalDetTask == 0xFFFF) && !(TADStatus & REMOTE_RECEIVE)) {
							cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
						}
					}
					else if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) && ModemRelaySetting()) {
						if ((tskno_RemoteRxSignalDetTask == 0xFFFF) && !(TADStatus & REMOTE_RECEIVE)) {
							cre_tsk(&tskno_RemoteRxSignalDetTask, TSK_NCU_REMOTERXSIGNALDETTASK, &(mbxno.NCU_TelephoneOperationTask));
						}
					}
				}
				break;
			}
		}
		else if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE){ /* 拡張回線には受話中 */
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
			if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
				|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
				|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
				if ((RingStatus2nd & CI_EXT_LINE) && !(RingStatus2nd & CI_DETECT_TIMEUP)) {
					RingStatus2nd |= CI_DETECT_TIMEUP;
					det_evt(EVT_2ND_CI_CHECK);
				}
			}
			else 
			if ( (CHK_KEIDENRxPriority())   /* 警電優先受信機能が有効されている場合 */
			&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
				/* 通信中断していない場合 */
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_COM_ON_FORCE;
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@				if (SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI) {
@@					if (RingStatus & CI_EXT_LINE) {
@@						RingStatus |= CI_DETECT_TIMEUP;
@@						det_evt(EVT_CI_CHECK);
@@					}
@@					else {
@@						RingStatus2nd |= CI_DETECT_TIMEUP;
@@						det_evt(EVT_2ND_CI_CHECK);
@@					}
#else
				if (RingStatus2nd & CI_EXT_LINE) {
					RingStatus2nd |= CI_DETECT_TIMEUP;
					det_evt(EVT_2ND_CI_CHECK);
#endif
				}
			}
		}
	}

	if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE ){ /* 拡張回線は本体で受話中 */
		/* 拡張回線によって受話中状態に変更していない場合 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE)) {
			/* 拡張回線によって受話中状態になる事 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_EXT_LINE_IN_RECEIVE; 
		}
	}
	else {
		/* 拡張回線によって受話中状態を保持されている場合 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE) {
			/* 拡張回線によって受話中状態を消去し */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_EXT_LINE_IN_RECEIVE; 
		}
	}
	
	if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE ){ /* 標準回線は本体で受話中 */
		/* 標準回線によって受話中状態に変更していない場合 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_STD_LINE_IN_RECEIVE)) {
			/* 標準回線によって受話中状態になる事 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_STD_LINE_IN_RECEIVE; 
		}
	}
	else {  /* 標準回線は受話中ではない */
		/* 標準回線によって受話中状態を保持されている場合 */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_STD_LINE_IN_RECEIVE) {
			/* 標準回線によって受話中状態を消去し */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_STD_LINE_IN_RECEIVE; 
		}
	}
	
	if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
		/* 強制終了要求された場合 */
		if (NCUStatus & HOOK_KEY_ON_STATE
		&& (!(NCUStatus & DIALING_STATE)) ) {
			if (!SYS_HookKeyInputFlag) {
				SYS_HookKeyInputFlag = TRUE;
			}
		}
	}
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[付属電話切替]
	function	:[
	]
	return		:[なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[2005/08/01 ]
	author		:[SMuratec 李]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_HdstShift(void)
{
	if ( CHK_LineSetting()		/* 回線設定 == 標準回線 */
	&& HDST_RelaySetting() ) {	/* ハンドセットは拡張回線側接 */
		switch (NCU_LineStatus & EXT_LINE_STATUS) {
		case EXT_CI_IN:
 #if 0 /* 警察FAX DVT_ID9 by SMuratec 李 2005/11/01 */
@@			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK)) {
@@				break;
@@			}
 #else
 			break;
 #endif
		default:
			if ((SYS_InternalLineNumber != SYS_EXT_LINE_COM) /**	拡張ライン通信中でわない	*/
				|| !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_CONT24_LINE_BUSY) ){ /* 擬似ﾍﾞﾙ鳴動していない場合 */
				HDST_RelayOff();        /* ハンドセットを標準回線に接続する */
			}
			break;
		}
	}
	else if ( !CHK_LineSetting()		/* 回線設定 == 拡張回線 */
	&& !HDST_RelaySetting() ) {			/* ハンドセットは標準回線側接 */
		switch (NCU_LineStatus & STD_LINE_STATUS) {
		case STD_CI_IN:
 #if 0 /* 警察FAX DVT_ID9 by SMuratec 李 2005/11/01 */
@@			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK)) {
@@				break;
@@			}
 #else
 			break;
 #endif
		default:
			if ((SYS_InternalLineNumber != SYS_STD_LINE_COM) /**	標準ライン通信中でわない	*/
				|| !(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_CONT24_LINE_BUSY) ){ /* 擬似ﾍﾞﾙ鳴動していない場合 */
				HDST_RelayOn();        /* ハンドセットを拡張回線に接続する */
			}
			break;
		}
	}
}

/*************************************************************************
	module		:[特番転送起動番号と、検出したDTMFを比較する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[2005/08/01 ]
	author		:[SMuratec 李]
*************************************************************************/
UBYTE NCU_CompareSpecialNumber(UBYTE cnt)
{
	UBYTE num_count;
	UBYTE remote_number[3];
	UBYTE sharp_aster;

	remote_number[0] = (unsigned char)((SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM1_ISSEI) >> 4);
	remote_number[1] = (unsigned char)(SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM2_ISSEI);

	/* MEMSW 68-4で＃か＊かを指定するようにします by J.Kishida 2003/08/12 */
	sharp_aster = CHK_RemoteTransNum3_SharpAster();
	if (sharp_aster == 0) {
		remote_number[2] = DTMF_SHARP;	/* '#'(0x0B) */
	}
	else {
		remote_number[2] = DTMF_ASTA;	/* '*'(0x0A) */
	}

	/* 変換は1,2桁目のみ行います */
	for (num_count = 0; num_count < 2; num_count++) {
		switch (remote_number[num_count]) {
		case DTMF_0:	/* '0' */
			remote_number[num_count] = DTMF_5;
			break;
		case 0x0C:		/* 'A' */
		case 0x0D:		/* 'B' */
		case 0x0E:		/* 'C' */
		case 0x0F:		/* 'D' */
			remote_number[num_count] = DTMF_0;
			break;
		default:
			break;
		}
	}

	/*
	// 今回検出した番号1桁だけを判定します．
	// 1桁検出する度にここを通るので，
	// 遡って全ての桁を判定することはしません．
	*/
	if (ModemRelaySetting()) {	/* モデムリレーを拡張回線に接続している場合 */
		if (DTMF_Detect_Buffer[cnt] == remote_number[cnt]) {
			return (TRUE);
		}
	}
	return (FALSE);

}

UBYTE NCU_CompareSpecialNumberDP(UBYTE pulse_count, UBYTE rcv_cnt)
{
	UBYTE i;
	UBYTE remote_num[2];
	UBYTE detect_pulse_more;

	remote_num[0] = 9;
	remote_num[1] = 9;
	detect_pulse_more = CHK_RemoteTransferDialNumMore();

	for (i = 0;i < 2;i++) {
		switch (remote_num[i]) {
		case 0:
			remote_num[i] = 5;		/* ダイアルの５ */
			break;
		case 0x0A:
		case 0x0B:
#if (0)
			/*
			// NTT仕様の場合，55転送の番号の初期値は"5*"なので
			// 以下の処理が入っているとDP設定時に55転送できません．
			// NAGANOからのNTT向け機種の作成予定はありませんが，
			// YAWARAからROME NTT作成時に入れた処理を移植しておきます．
			// by J.Kishida 2003/11/14
			*/
//			/* 以下の判断が入っているとDP設定時、転送番号に#/*が登録されていると
//			** まったく検出が出来ない。よって、以下の判断と同様に0に置き換えるよう修正
//			** By O.Kimoto 2003/10/01
//			*/
//			return FALSE;
//			break;
#endif
		case 0x0C:
		case 0x0D:
		case 0x0E:
		case 0x0F:
			remote_num[i] = 10;		/* ダイアルの０ */
			break;
		default:
			break;
		}
	}

	/* ダイヤルパルス方式対応 *//* 2003/02/07 */
	switch (CHK_DP_Method()) {
	case	DIAL_SWE_TYPE:
		if (remote_num[0] == 10) {		/* ダイアルの０ */
			remote_num[0] = 0;
		}
		if (remote_num[1] == 10) {		/* ダイアルの０ */
			remote_num[1] = 0;
		}
		remote_num[0] += 1;
		remote_num[1] += 1;
		break;
	case	DIAL_NZL_TYPE:
		if (remote_num[0] == 10) {		/* ダイアルの０ */
			remote_num[0] = 0;
		}
		if (remote_num[1] == 10) {		/* ダイアルの０ */
			remote_num[1] = 0;
		}
		remote_num[0] = (UBYTE)(10 - remote_num[0]);
		remote_num[1] = (UBYTE)(10 - remote_num[1]);
		break;
	default	:
		break;
	}


	if ( ModemRelaySetting()	/* モデムリレーを拡張回線に接続している場合 */
		&& (9 == (unsigned char)((SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM1_ISSEI) >> 4))
		&& (9 == (unsigned char)(SYS_MemorySwitch[MEMORY_SW_G9] & REMOTE_TRANSFER_DIAL_NUM2_ISSEI)) ){
		if (detect_pulse_more) {
			if (pulse_count >= remote_num[rcv_cnt]) {
				return (TRUE);
			}
			else {
				return (FALSE);
			}
		}
		else {
			if (pulse_count == remote_num[rcv_cnt]) {
				return (TRUE);
			}
			else {
				return (FALSE);
			}
		}
	}
	else {
		return (FALSE);
	}
}

#endif /* defined (KEISATSU) */

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ＨＯＯＫ状態変化監視タスク]
	function	:[
		1.付属電話（ＴＥＬ１）・外付電話（ＴＥＬ２）・ブランチ電話（ＢＲＣ）のＯＨの状態変化を監視します。
		2.回線捕捉キー（ＨＯＯＫ）・保留キー（ＨＯＬＤ）・停止キー（ＳＴＯＰ）・ＦＡＸテンキーの入力を監視します。
		3.転送受信許容時間を計測する１０ｍｓ単位のタイマ
		4.Ｈ，Ｌリレー動作直後のノイズによるベル鳴動防止タイマ
		5.内線通話中のＣＩによる着信検出を行います。
	]
	return		:[
		なし
	]
	common		:[
		NCUStatus	:回線監視モジュール動作状態を記憶
		OhPortStatus    :付属／外付／ブランチ電話のＯＨポート状態を記憶
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		NCU_TelephoneHookCheckTask( WORD *tx_mail_box_no )
{
	MESSAGE_t				*RxTelephoneHookCheckTaskMsg;

	/*------------------------------*/
	/**     内部変数の初期化        */
	/*------------------------------*/
#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
	/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */

	/* ダイアル１桁送出週中かどうかの変数のクリアです。
	 * この変数は、NCU_TelephoneExecuteTask()でセットされますが、もしこの変数がたちっぱなしになれば
	 * ＯＨの検出はできなくなってしまうので安全のためこのタスク内でクリアします。
	 * NCU_TelephoneExecuteTask()タスクとNCU_TelephoneHookCheckTask()は同時にクリエイトされるので問題ないはず。
	*/
	OneDigitDiallingExecute = 0;
#endif

	TxTelephoneHookCheckTaskMsg.Item	= FROM__NCU_SUB;
	OhPortStatus			=  0;
	if(!( Tel1OhCounter = Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
		Tel1OhCounter			= 40;
		Tel2OhCounter			= 40;
	}
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/21 */
	HDSTOffCount = HDSTOnCount = 40;
#endif /* defined (KEISATSU) */
				/*-------------------------------------------*/
#if defined (KEISATSU) /* 警察FAX DVT_ID45 Added by SMuratec 李 2005/11/14 */
	if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
		}
		else if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE) {
			SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_EXT_LINE_IN_RECEIVE) && !(NCUStatus & TELEPHONE2_OFF_HOOK)) {
				if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_NOT_USE) { /* 拡張回線は待機状態 */
					NCU_LineStatus &= ~EXT_LINE_STATUS;
					NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
				}
				TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_OFF_HOOK;
				snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
				rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
			}
		}
	}
#endif /* defined (KEISATSU) */

	while(1){	/** 親タスクから強制終了されるまで無限ループ */
				/*-------------------------------------------*/
						/*-------------------*/
		wai_tsk( 1 );	/** 監視間隔 10msec  */
						/*-------------------*/
#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
	/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
	if (OneDigitDiallingExecute == 0) {
#endif
		/*-----------------------------------*/
		/** 付属／外付電話のＯＨ情報の取込み */
		/*-----------------------------------*/
		OhPortStatusRead();
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/08/01 */
		LineStatusRead();
#endif /* defined (KEISATSU) */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/22 */
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
 		if (SYS_LineNDStatus == ND_USED_IN_STD) { /* ナンバーディスプレイ起動回線は標準回線 */
			/* HINOKI のように、 TEL1 を上げると先に CI が検出され、その後 OFF-Hook が検出される場合に対応します。
			** ND で CAR らしき最初の CI が来たら、しばらく OH 監視を休みます。
			** なおこの状態は、 NCU_DetectCalledTask で解除されることになっています。注意してください。
			** by H.Kubo 1998/11/16 */
			if (NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) {
				if ((TimeStatus != WITHIN_MIN_CYCLE)
				&&  (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED))
				{
					do {
						wai_tsk(10/10);
						CMN_DisableInterrupt();
						if ((TimeStatus > OK_CI_CYCLE) && 
							((NCU_LineStatus & STD_HDST_OFFHOOK) || (SYS_LineTelStatus & STD_TEL2_OFFHOOK))
						 && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED)) {
							NCU_ND_Status &= ~ ND_SUSPICIOUS_CI_DETECTED; /* added by H.Kubo 1998/11/23 */
							SYS_LineTelStatus &= ~STD_TEL2_OFFHOOK;
						}
						CMN_EnableInterrupt();
						OhPortStatusRead();
						LineStatusRead();
						if((  ( OhPortStatus & TEL2_OFF_HOOK )  && (!( NCUStatus & TELEPHONE2_OFF_HOOK )))
						|| ((!( OhPortStatus & TEL2_OFF_HOOK )) &&   ( NCUStatus & TELEPHONE2_OFF_HOOK ) )){
							if( OhPortStatus & TEL2_OFF_HOOK ){
								if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
									if(!(--Tel2OhCounter )){
										TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_OFF_HOOK;
										snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
										rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
									}
								}
							}
							else{
								if(!(--Tel2OhCounter )){
										TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
										snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
										rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
																										/* SAKAKI追加 By M.Maeda 2002/12/02 */
									if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
										Tel2OhCounter = 40;
									}
								}
							}
						}
						else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && (!(NCUStatus & TELEPHONE2_OFF_HOOK))) {
							if(!(--Tel2OhCounter )){
								/*-------------------------------*/
								/**		メイン・タスクへ通知	 */
								/*-------------------------------*/
								SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
								TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
								snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
								rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
								
								if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
									Tel2OhCounter = 40;
								}
							}
						}
						else{
							if (SYS_RingCounterExt && (NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_TEL2FaxTransferAvailable()) {
							/*	キャッチホン対応電話でオンフック転送してしまうため設定範囲を広げる */
							/*	if(!( Tel2OhCounter =  CHK_OnHookTransferRxPeriod() )){	下記処理に変更 By M.Tachibana 1998/10/25 */
								if(!( Tel2OhCounter =  (UWORD)CHK_OnHookTransferRxPeriod()+ (UWORD)CHK_OnHookTransferRxTime() * 2 )){
									Tel2OhCounter = 3;
								}
							}
							else{
								if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
									Tel2OhCounter = 40;
								}
							}
						}
					} while ((NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED));
				}
			}
			/* ND 外付け電話で処理する場合、 ND 処理中はここに捕まります。 */
			if (CHK_NumberDisplayByExtPhoneON()
			&& (OffHook2()) 
			&& (NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED))) {
				if (NCU_ND_CheckOH2(SYB_ND_CarPattern[SYS_ND_OH_TO_V23_RX_TIMER], SYB_ND_CarPattern[SYS_ND_OH_TO_V23_RX_TIMER])) {
					if (NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED)) {
						TxTelephoneHookCheckTaskMsg.Message = DETECT_ND_OH_1ST_RESPONSE;
						snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
						rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
						while (NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED)) {
							if (NCU_ND_Status & (ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) { /* 受信応答を返した後なら */
								break;
							}
							/*--------------------------------------------------------------*/
							/* Ｈ・Ｌリレーが回線側に倒れた直後のＣＩを無視する為のタイマー */
							/*--------------------------------------------------------------*/
							if( AfterCI_HL_RelayOn ){
								AfterCI_HL_RelayOn--;
							}
							wai_tsk(10/10);
							OhPortStatusRead();
							LineStatusRead();
							if((  ( OhPortStatus & TEL2_OFF_HOOK )  && (!( NCUStatus & TELEPHONE2_OFF_HOOK )))
							|| ((!( OhPortStatus & TEL2_OFF_HOOK )) &&   ( NCUStatus & TELEPHONE2_OFF_HOOK ) )){
								if( OhPortStatus & TEL2_OFF_HOOK ){
									if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
										if(!(--Tel2OhCounter )){
											TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_OFF_HOOK;
											snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
											rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
										}
									}
								}
								else{
									if(!(--Tel2OhCounter )){
											TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
											snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
											rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
																											/* SAKAKI追加 By M.Maeda 2002/12/02 */
										if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
											Tel2OhCounter = 40;
										}
									}
								}
							}
							else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && (!(NCUStatus & TELEPHONE2_OFF_HOOK))) {
								if(!(--Tel2OhCounter )){
									/*-------------------------------*/
									/**		メイン・タスクへ通知	 */
									/*-------------------------------*/
									SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
									TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
									snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
									rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
									
									if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
										Tel2OhCounter = 40;
									}
								}
							}
							else{
								if (SYS_RingCounterExt && (NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_TEL2FaxTransferAvailable()) {
								/*	キャッチホン対応電話でオンフック転送してしまうため設定範囲を広げる */
								/*	if(!( Tel2OhCounter =  CHK_OnHookTransferRxPeriod() )){	下記処理に変更 By M.Tachibana 1998/10/25 */
									if(!( Tel2OhCounter =  (UWORD)CHK_OnHookTransferRxPeriod()+ (UWORD)CHK_OnHookTransferRxTime() * 2 )){
										Tel2OhCounter = 3;
									}
								}
								else{
									if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
										Tel2OhCounter = 40;
									}
								}
							}
						}
					}
				}
				if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel1OhCounter			= 40;
				}
			}
			if (NCU_ND_Status & ND_SLEEP_AFTER_ACK_RESPONSE) { /* 受信完了信号直後の受話器上げを無視。added by H.Kubo 1998/11/25 */
				if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel1OhCounter			= 40;
				}
			}
		}
 #else /* !defined (KEISATSU) */
		/* HINOKI のように、 TEL1 を上げると先に CI が検出され、その後 OFF-Hook が検出される場合に対応します。
		** ND で CAR らしき最初の CI が来たら、しばらく OH 監視を休みます。
		** なおこの状態は、 NCU_DetectCalledTask で解除されることになっています。注意してください。
		** by H.Kubo 1998/11/16 */
		if (NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) {

#if defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/* For Debug by O.Kimoto 2002/02/18 */
			if ((TimeStatus != WITHIN_MIN_CYCLE)
			&&  (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED))
#else
			if (((TimeStatus == WITHIN_MIN_CYCLE) || (TimeStatus == OK_CI_CYCLE))
			&&  (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED))
#endif
			{
				do {
					wai_tsk(10/10);
					CMN_DisableInterrupt();
					if ((TimeStatus > OK_CI_CYCLE) && (OhPortStatus & (TEL1_OFF_HOOK | TEL2_OFF_HOOK))
					 && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED)) {
						NCU_ND_Status &= ~ ND_SUSPICIOUS_CI_DETECTED; /* added by H.Kubo 1998/11/23 */
					}
					CMN_EnableInterrupt();
				} while ((NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && !(NCU_ND_Status & ND_CI_SEQUENCE_DETECTED));
			}
		}
		/* ND 外付け電話で処理する場合、 ND 処理中はここに捕まります。 */
		if (CHK_NumberDisplayByExtPhoneON()
		&& (OhPortStatus & TEL2_OFF_HOOK) 
		&& (NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED))) {
			if (NCU_ND_CheckOH2(SYB_ND_CarPattern[SYS_ND_OH_TO_V23_RX_TIMER], SYB_ND_CarPattern[SYS_ND_OH_TO_V23_RX_TIMER])) {
				if (NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED)) {
					TxTelephoneHookCheckTaskMsg.Message = DETECT_ND_OH_1ST_RESPONSE;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
					rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
					while (NCU_ND_Status & (ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED)) {
						if (NCU_ND_Status & (ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) { /* 受信応答を返した後なら */
							break;
						}
						/*--------------------------------------------------------------*/
						/* Ｈ・Ｌリレーが回線側に倒れた直後のＣＩを無視する為のタイマー */
						/*--------------------------------------------------------------*/
						if( AfterCI_HL_RelayOn ){
							AfterCI_HL_RelayOn--;
						}
						wai_tsk(10/10);
					}
				}
			}
			if(!( Tel1OhCounter = Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
				Tel1OhCounter			= 40;
				Tel2OhCounter			= 40;
			}
		}
		if (NCU_ND_Status & ND_SLEEP_AFTER_ACK_RESPONSE) { /* 受信完了信号直後の受話器上げを無視。added by H.Kubo 1998/11/25 */
			if(!( Tel1OhCounter = Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
				Tel1OhCounter			= 40;
				Tel2OhCounter			= 40;
			}
		}
 #endif /* defined (KEISATSU) */
#endif
		/*--------------------------------------------*/
		/* 付属電話（ＴＥＬ１）のＨＯＯＫ状態監視部位 */
		/*--------------------------------------------*/
		if((  ( OhPortStatus & TEL1_OFF_HOOK )  && (!( NCUStatus & TELEPHONE1_OFF_HOOK )))
		|| ((!( OhPortStatus & TEL1_OFF_HOOK )) &&   ( NCUStatus & TELEPHONE1_OFF_HOOK ) )){
			if( OhPortStatus & TEL1_OFF_HOOK ){
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/28 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
					if((!( NCUStatus & TELEPHONE1_OFF_HOOK ))
					&& (!( NCUStatus & TELEPHONE2_OFF_HOOK ))){
						if(!(--Tel1OhCounter )){
							TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL1_OFF_HOOK;
							snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
							rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
						}
					}
				}
				else {
					if (!(NCUStatus & TELEPHONE1_OFF_HOOK)) {
						if(!(--Tel1OhCounter )){
							TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL1_OFF_HOOK;
							snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
							rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
						}
					}
				}
#else
				if((!( NCUStatus & TELEPHONE1_OFF_HOOK ))
				&& (!( NCUStatus & TELEPHONE2_OFF_HOOK ))){
					if(!(--Tel1OhCounter )){
						TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL1_OFF_HOOK;
						snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
						rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);

	#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	/* 2000/02/25 Y.Murata *//* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 */
																							/* SAKAKI追加 By M.Maeda 2002/12/02 */
						if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel1OhCounter = 40;
						}
	#endif
					}
				}
#endif
			}
			else{
				if(!(--Tel1OhCounter )){
					/* 1996/07/17 By N.Sakamot for debug 16lines insert */
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/08/01 */
					if (ModemRelaySetting() || !IsDailing) { /* 標準回線で本体ダイヤルしていない場合 */
						TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL1_ONHOOK;
						snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
						rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
					}
#else /* defined (KEISATSU) */
					TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL1_ONHOOK;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
					rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
#endif

	#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	/* 2000/02/25 Y.Murata *//* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 */
																							/* SAKAKI追加 By M.Maeda 2002/12/02 */
					if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
						Tel1OhCounter = 40;
					}
	#endif

				}
			}
		}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/21 */
		else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK) && (!(NCUStatus & TELEPHONE1_OFF_HOOK))) {
			if(!(--Tel1OhCounter )){
				/*-------------------------------*/
				/**		メイン・タスクへ通知	 */
				/*-------------------------------*/
				if (ModemRelaySetting() || !IsDailing) { /* 標準回線で本体ダイヤルしていない場合 */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
					TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL1_ONHOOK;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
					rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
				}
				
				if(!(Tel1OhCounter = (UWORD)(CHK_OnhookOffhookTime() * 10))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel1OhCounter = 40;
				}
			}
		}
#endif /* defined (KEISATSU) */
		else{
			/*  '96,04,15 新ON HOOK転送に対応 NEWMEM By N.S. USA仕様TEL2無し */
			if (SYS_RingCounter && (NCUStatus & TELEPHONE1_OFF_HOOK) && CHK_TEL1FaxTransferAvailable()) {
			/*	 キャッチホン対応電話でオンフック転送してしまうため設定範囲を広げる */
			/*	if(!( Tel1OhCounter = CHK_OnHookTransferRxPeriod())){	下記処理に変更 By M.Tachibana 1998/10/25 */
				if(!( Tel1OhCounter = (UWORD)CHK_OnHookTransferRxPeriod() + (UWORD)CHK_OnHookTransferRxTime() * 2 )){
					Tel1OhCounter = 3;
				}
			}
			else{
				if(!( Tel1OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S. *//* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
					Tel1OhCounter = 40;
				}
			}
		}
		/*--------------------------------*/
		/* 外付電話のＨＯＯＫ状態監視部位 */
		/*--------------------------------*/
		/*-----------------------------------------------------------
		** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
		*/
#if (0)	/* 1997/09/25 */
//		if(!( NCUStatus & HOOK_KEY_ON_STATE )){
#endif
		if(!( NCUStatus & HOOK_KEY_ON_STATE ) || CHK_UNI_TEL2_TEL1Action()){
			if((  ( OhPortStatus & TEL2_OFF_HOOK )  && (!( NCUStatus & TELEPHONE2_OFF_HOOK )))
			|| ((!( OhPortStatus & TEL2_OFF_HOOK )) &&   ( NCUStatus & TELEPHONE2_OFF_HOOK ) )){
				if( OhPortStatus & TEL2_OFF_HOOK ){
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/28 */
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
						if((!( NCUStatus & TELEPHONE2_OFF_HOOK ))
						&& (!( NCUStatus & TELEPHONE1_OFF_HOOK ))){
							if(!(--Tel2OhCounter )){
								TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_OFF_HOOK;
								snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
								rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
							}
						}
					}
					else {
						if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
							if(!(--Tel2OhCounter )){
								TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_OFF_HOOK;
								snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
								rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
							}
						}
					}
#else
					if((!( NCUStatus & TELEPHONE2_OFF_HOOK ))
					&& (!( NCUStatus & TELEPHONE1_OFF_HOOK ))){
						if(!(--Tel2OhCounter )){
							TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_OFF_HOOK;
							snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
							rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);

	#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	/* 2000/02/25 Y.Murata *//* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 */
																							/* SAKAKI追加 By M.Maeda 2002/12/02 */
							if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
								Tel2OhCounter = 40;
							}
	#endif
						}
					}
#endif
				}
				else{
					if(!(--Tel2OhCounter )){
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/08/01 */
						if (!ModemRelaySetting() || !IsDailing) { /* 拡張回線で本体ダイヤルしていない場合 */
							TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
							snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
							rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
						}
#else /* defined (KEISATSU) */
						TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
						snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
						rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
#endif

	#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	/* 2000/02/25 Y.Murata *//* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 */
																							/* SAKAKI追加 By M.Maeda 2002/12/02 */
						if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel2OhCounter = 40;
						}
	#endif

					}
				}
			}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
			else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && (!(NCUStatus & TELEPHONE2_OFF_HOOK))) {
				if(!(--Tel2OhCounter )){
					/*-------------------------------*/
					/**		メイン・タスクへ通知	 */
					/*-------------------------------*/
					if (!ModemRelaySetting() || !IsDailing) { /* 拡張回線で本体ダイヤルしていない場合 */
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
						TxTelephoneHookCheckTaskMsg.Message = DETECT_TEL2_ONHOOK;
						snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
						rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
					}
					
					if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
						Tel2OhCounter = 40;
					}
				}
			}
#endif /* defined (KEISATSU) */
			else{
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/28 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
					if (SYS_RingCounter && (NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_TEL2FaxTransferAvailable()) {
					/*	キャッチホン対応電話でオンフック転送してしまうため設定範囲を広げる */
					/*	if(!( Tel2OhCounter =  CHK_OnHookTransferRxPeriod() )){	下記処理に変更 By M.Tachibana 1998/10/25 */
						if(!( Tel2OhCounter =  (UWORD)CHK_OnHookTransferRxPeriod() + (UWORD)CHK_OnHookTransferRxTime() * 2 )){
							Tel2OhCounter = 3;
						}
					}
					else{
						if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel2OhCounter = 40;
						}
					}
				}
				else {
					if (SYS_RingCounterExt && (NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_TEL2FaxTransferAvailable()) {
					/*	キャッチホン対応電話でオンフック転送してしまうため設定範囲を広げる */
					/*	if(!( Tel2OhCounter =  CHK_OnHookTransferRxPeriod() )){	下記処理に変更 By M.Tachibana 1998/10/25 */
						if(!( Tel2OhCounter =  (UWORD)CHK_OnHookTransferRxPeriod()+ (UWORD)CHK_OnHookTransferRxTime() * 2 )){
							Tel2OhCounter = 3;
						}
					}
					else{
						if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel2OhCounter = 40;
						}
					}
				}
#else
				/*  '96,04,15 新ON HOOK転送に対応 NEWMEM By N.S. USA仕様TEL2無し */
				if (SYS_RingCounter && (NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_TEL2FaxTransferAvailable()) {
				/*	キャッチホン対応電話でオンフック転送してしまうため設定範囲を広げる */
				/*	if(!( Tel2OhCounter =  CHK_OnHookTransferRxPeriod() )){	下記処理に変更 By M.Tachibana 1998/10/25 */
					if(!( Tel2OhCounter =  (UWORD)CHK_OnHookTransferRxPeriod() + (UWORD)CHK_OnHookTransferRxTime() * 2 )){
						Tel2OhCounter = 3;
					}
				}
				else{
					if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
						Tel2OhCounter = 40;
					}
				}
#endif
			}
		}
#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 *//* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
	}	/*if (OneDigitDiallingExecute == 0) {*/
#endif


		/*--------------------------*/
		/* 回線補足キー状態監視部位 */
		/*--------------------------*/
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/11/25 */
		if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) { /* 受信完了信号直後の受話器上げを無視。added by H.Kubo 1998/11/25 */
		}
		else
#endif
		if(( SYS_HookKeyInputFlag == 1 ) && ( HookKeyInputFlag == 0 )){
			AfterCI_HL_RelayOn = 100;		/* 1000ms WAIT	Add by TH92115 1995/02/14 */
			TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_HOOK_KEY;
			snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
			rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
		}
		/*-----------------------*/
		/*  保留キー状態監視部位 */
		/*-----------------------*/
		if(( SYS_HoldKeyInputFlag == 1 ) && ( HoldKeyInputFlag == 0 )){
			/*-----------------------------------------------------------
			** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
			*/
			if (CHK_UNI_TEL2_TEL1Action()) {
				if( NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK) ){
					TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_HOLD_KEY;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
					rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
				}
				else{
					SYS_HoldKeyInputFlag = 0;
				}
			}
			else {
				if( NCUStatus & TELEPHONE1_OFF_HOOK ){
					TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_HOLD_KEY;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
					rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
				}
				else{
					SYS_HoldKeyInputFlag = 0;
				}
			}
		}
		/*------------------------------------------------------*/
		/* ダイヤル・回線補足・三者通話中のＳＴＯＰキー検出部位 */
		/*------------------------------------------------------*/
		if(( NCUStatus & DIALING_STATE     )
		|| ( NCUStatus & HOOK_KEY_ON_STATE )){
			if( SYS_TelephoneStopSwitch()){
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_TELEPHONE;
				if(( NCUStatus & DIALING_STATE     )
				|| ( NCUStatus & HOOK_KEY_ON_STATE )){
					TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_STOP_KEY;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
				}
				rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
			}
		}
#if defined(EC1)	/* '98/04/9 M.H. HookKey timer for BEL */
		/*-----------------------------------------*/
		/* HOOK KEY ON状態で放置した場合80secでOFF */
		/*-----------------------------------------*/
		if (SYB_MachineParameter[0] == 0) {		/* BEL */
			if((( NCUStatus & HOOK_KEY_ON_STATE  ) == HOOK_KEY_ON_STATE  )
			&& (( NCUStatus & DIALING_STATE      ) != DIALING_STATE      )
			&& (  HookKeyTimer                                           )){
				HookKeyTimer--;
				if( HookKeyTimer == 0 ){
					AfterCI_HL_RelayOn = 100;
					TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_HOOK_KEY;
					snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
					wai_tsk(0xFFFF);
				}
			}
			if(( NCUStatus & HOOK_KEY_ON_STATE  ) != HOOK_KEY_ON_STATE  ){
				HookKeyTimer = 0;
			}
		}
		else{
			HookKeyTimer = 0;
		}
#endif
		/*-----------------------------*/
		/*  多機能電話番号入力監視部位 */
		/*-----------------------------*/
		/*-----------------------------------------------------------
		** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
		*/
		if (CHK_UNI_TEL2_TEL1Action()) {
			if(( NCUStatus    &   ( TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK | HOOK_KEY_ON_STATE ))
			&& ( SYS_DialingNumber.ReadPointer != SYS_DialingNumber.WritePointer )
			&& ( !AfterCI_HL_RelayOn)		/* Add by TH92115 1995/01/10 */
			&& ( NumberKeyInputFlag            == 0                              )){
#if defined(EC1)	/* '98/04/8 M.H. HookKey timer for BEL */
				if (SYB_MachineParameter[0] == 0) {		/* BEL */
					HookKeyTimer		 = 8000;		/* 80sec */
				}
#endif
				TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_TEL_NO;
				snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
				rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
			}
		}
		else {
			if(( NCUStatus    &   ( TELEPHONE1_OFF_HOOK | HOOK_KEY_ON_STATE ))
			&& ( SYS_DialingNumber.ReadPointer != SYS_DialingNumber.WritePointer )
			&& ( !AfterCI_HL_RelayOn)		/* Add by TH92115 1995/01/10 */
			&& ( NumberKeyInputFlag            == 0                              )){
				TxTelephoneHookCheckTaskMsg.Message = DETECT_INPUT_TEL_NO;
				snd_msg( *tx_mail_box_no, &TxTelephoneHookCheckTaskMsg );
				rcv_msg(mbxno.NCU_TelephoneHookCheckTask, &RxTelephoneHookCheckTaskMsg);
			}
		}
		/*--------------------------------------------------------------*/
		/* Ｈ・Ｌリレーが回線側に倒れた直後のＣＩを無視する為のタイマー */
		/*--------------------------------------------------------------*/
		if( AfterCI_HL_RelayOn ){
			AfterCI_HL_RelayOn--;
		}
#if (PRO_REMOTE_FAX == ENABLE) /* L400 ポプラＬ ＮＴＴ 特許関係なしに入れる By Y.Suzuki 1998/03/16 */
		/*--------------------------*/
		/* 転送受信許容時間タイマー */
		/*--------------------------*/
		if( TransferReceiveAvailableTime != 0 ){
			TransferReceiveAvailableTime--;
			if( TransferReceiveAvailableTime == 0 ){
				TransferReceiveFlag = 0;
			}
		}
#endif
		/*------------------------------------------------------------*/
		/** 待機モードの監視（無鳴動受信の準備とブランチデータの反映）*/
		/*------------------------------------------------------------*/
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/14 */
		if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING | ND_MODEM_DIALIN_DIAL)) {
			/* 無鳴動着信の準備はしない。 */
		}
		else
#endif
		if (!(NCUStatus & ~DETECT_CI_STATE)) {				/* QAT1 1994/08/24 by TH92115 */
			/*-----------------------------*/
			/** 無鳴動受信の準備を行います */
			/*-----------------------------*/
			/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K May,10,1995 *//* By M.Tachibana 1997/10/17 */
			if (CHK_UNI_NoRingTel2Detachable()) {
#if (1) /* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
				if ((SilentReceiveRequest()) && (CR_Ringing == OFF)){
#else
				if (SilentReceiveRequest()) {
#endif
					CallingRelayControl();
				}
				else {
					ReverseRelayControl();
				}
			}
			NCU_RxModeSwitch = CMN_PresentReceiveMode();
		}
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/14 */
		/*-------------------------------*/
		/* 10ms 毎に ND の設定を見直す。 */
		/*-------------------------------*/
		CMN_DisableInterrupt();
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/08 */
		if (DEBUG_NumberDisplay) {
			if (!(NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))) { /* ND 情報受信手順が CAR 待ち状態ならば */
				if (NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) {
					if (!CHK_NumberDisplayON()) {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							H_RelayOff();
						}
						else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							L_RelayOff();
						}
					}
				}
				if (SYS_LineNDStatus == ND_USED_IN_STD) {
					NCU_ND_InitializeStatus(); /* 初期状態に戻す */
					if (SYS_LineNDStatus == ND_USED_IN_EXT) {
						H_RelayOff();
					}
				}
				else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
					NCU_ND_InitializeStatus(); /* 初期状態に戻す */
					if (SYS_LineNDStatus == ND_USED_IN_STD) {
						L_RelayOff();
					}
				}
				else {
					NCU_ND_InitializeStatus(); /* 初期状態に戻す */
				}
				if (CHK_NumberDisplayON()) {
					if (NCU_IsCarWaitedFor()) {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							if (!(NCUStatus & TELEPHONE1_OFF_HOOK)) {
								if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
									if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
										HDST_Disable();	/* ハンドセットを使用禁止にします */
									}
									RelayPortStatus &= ~IO_BIT_L; /* 外付電話を回線に接続し */
									OutputWORD(GA_PGADR, RelayPortStatus);
								}
								else {
									H_RelayOn();
								}
							}
						}
						else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
								if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
									if (HDST_RelaySetting()) { /* ハンドセットを拡張回線に接続 */
										HDST_Disable();	/* ハンドセットを使用禁止にします */
									}
									IO__PADRL &= ~IO_BIT_K_L; /* 外付電話を回線に接続し */
					 			}
								else {
									L_RelayOn();
								}
							}
						}
					}
					else {
						if (SYS_LineNDStatus == ND_USED_IN_STD) {
							if ((NCU_LineStatus & STD_LINE_STATUS) == STD_CI_IN ) {
								H_RelayOff();
							}
						}
						else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_CI_IN ) {
								L_RelayOff();
							}
						}
					}
				}
			}
		}
		else {
			if (!(NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))) { /* ND 情報受信手順が CAR 待ち状態ならば */
				NCU_ND_InitializeStatus(); /* 初期状態に戻す */
			}
		}
#else /* !defined (KEISATSU) */
		if (!(NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))) { /* ND 情報受信手順が CAR 待ち状態ならば */
			NCU_ND_InitializeStatus(); /* 初期状態に戻す */
		}
		CMN_EnableInterrupt();
#endif /* defined (KEISATSU) */
#endif
	}
}



#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 PHONE2リレーが標準の場合はLリレーはOFFにします by T.Soneoka 1997/11/21 */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[通信中のＨＯＯＫ状態変化監視タスク]
	function	:[
		1.疑似２回線仕様で、通信中における他方の回線の電話制御を行います
	]
	return		:[
		なし
	]
	common		:[
		NCUStatus	:回線監視モジュール動作状態を記憶
		OhPortStatus:付属／外付電話のＯＨポート状態を記憶
	]
	condition	:[通信状態のときに起動されるのが前提です
	]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1997/11/25]
	author		:[曽根岡拓]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_FaxComTelHookChkTask(void)
{
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/15 */
	UWORD					comp_min_on_time;	/* 1999/12/06 by K.Okada */
#endif /* defined (KEISATSU) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/23 */
	MESSAGE_t				*RxTelephoneOperationTaskMsg;
	
	/*-------------------*/
	/** 使用変数の初期化 */
	/*-------------------*/
	TxTelephoneOperationTaskMsg.Item			 = FROM_NCU_TELEPHONEOPERATIONTASK;
#endif /* defined (KEISATSU) */
	/*------------------------------*/
	/**     内部変数の初期化        */
	/*------------------------------*/
	OhPortStatus = 0;
	if(!( Tel1OhCounter = Tel2OhCounter = (UWORD)(CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
		Tel1OhCounter = 40;
		Tel2OhCounter = 40;
	}
				/*-------------------------------------------*/
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/09 */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/01 */
 	if (DEBUG_NumberDisplay) {
		if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
			del_tsk(&tskno_NCU_ND_Rx);
		}
		if ((NCU_ND_Status & ND_CALL_ACCEPTED) || !(NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))) {
			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ラインにて送信時	*/
				if (SYS_LineNDStatus == ND_USED_IN_EXT) {
					L_RelayOff();
				}
			}
			else {
				if (SYS_LineNDStatus == ND_USED_IN_STD) {
					H_RelayOff();
				}
			}
			NCU_ND_InitializeStatus(); /* 初期状態に戻す */
		}
	}
#endif
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ラインにて送信時	*/
		NCU_LineStatus &= ~STD_LINE_STATUS;
		NCU_LineStatus  |=  (STD_LINE_STATUS & STD_COM_IN_USE);
		if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
			/* 秘話機能起動した場合 */
			SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
			SYS_LineTelStatus |= STD_READY;
		}
		SYS_CalledLineNumber &= ~SYS_STD_LINE_IN_CI;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/01 */
		/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
#if 0 		/* 警察FAX DVT_ID72 Modified by SMuratec 李 2005/12/16 */
@@		if (DEBUG_NumberDisplay) {
#else
		if (!DEBUG_NumberDisplay) {
#endif
			if (tskno_DetectCalledTask != 0xFFFF) {
				del_tsk(&tskno_DetectCalledTask);
			}
			cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
		}
#endif
		/* 警察FAX DVT Added by SMuratec 李 2005/11/15 */
		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON)
			&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
			L_RelayOff();
			/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
			if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
				del_tsk(&tskno_NCU_ND_Rx);
			}
			NCU_ND_InitializeStatus(); /* 初期状態に戻す */
		}
	}
	else {
		NCU_LineStatus &= ~EXT_LINE_STATUS;
		NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_COM_IN_USE);
		if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
			/* 秘話機能起動した場合 */
			SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
			SYS_LineTelStatus |= EXT_READY;
		}
		SYS_CalledLineNumber &= ~SYS_EXT_LINE_IN_CI;
#if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/01 */
		/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/24 */
#if 0 		/* 警察FAX DVT_ID72 Modified by SMuratec 李 2005/12/16 */
@@		if (DEBUG_NumberDisplay) {
#else
		if (!DEBUG_NumberDisplay) {
#endif
			if (tskno_Detect2ndCalledTask != 0xFFFF) {
				del_tsk(&tskno_Detect2ndCalledTask);
			}
			cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
		}
		/* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/13 */
		if (tskno_NCU_ND_Rx != 0xFFFF) { /* 2nd 呼出音検出待ち終了 */
			del_tsk(&tskno_NCU_ND_Rx);
		}
		NCU_ND_InitializeStatus(); /* 初期状態に戻す */
#endif
	}

	HDSTOffCount = HDSTOnCount = 40;
	if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
		NCU_HdstShift();
	}
#endif /* defined (KEISATSU) */

	while(1){	/** 親タスクから強制終了されるまで無限ループ */
				/*-------------------------------------------*/
						/*-------------------*/
		wai_tsk( 1 );	/** 監視間隔 10msec  */
						/*-------------------*/
		/*-----------------------------------*/
		/** 付属／外付電話のＯＨ情報の取込み */
		/*-----------------------------------*/
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/09/09 */
		if (!FaxComTXorRX_Sign) { /* 通信準備している場合 */
			continue;
		}
#endif /* defined (KEISATSU) */
		OhPortStatusRead();
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/08/01 */
		LineStatusRead();
#endif /* defined (KEISATSU) */
		/*--------------------------------------------*/
		/* 付属電話（ＴＥＬ１）のＨＯＯＫ状態監視部位 */
		/*--------------------------------------------*/
		if ((OhPortStatus & TEL1_OFF_HOOK)  && (!(NCUStatus & TELEPHONE1_OFF_HOOK))) {
			if(!(--Tel1OhCounter )) {
				if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準回線で通信中か？	*/
					/*	標準回線での通信中の場合 */
					/*	何もしません	*/
				}
				else {
					/*	拡張回線での通信中	*/
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が拡張ライン側か？	*/
						/* 標準ライン側の場合 */
						if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
							NCUStatus |= TELEPHONE1_OFF_HOOK;
							L_RelayOn();	/**	秘話機能のため LリレーON */
							H_RelayOff();	/* 1998/05/11 by T.Soneoka */
						}
					}
					else {
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/15 */
						comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
						if ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) {
							if(!SYS_RingCounter){
								if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_STD)
									&& (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE))) {
								}
								else if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
								}
								else {
									if (RingStatus & CI_STD_LINE) { /**	CI検出状態が拡張ラインの場合	*/
										if(( RingingOnTime   >= comp_min_on_time )
										|| ( SamplingBuff[0] >= comp_min_on_time )){
											SYS_RingCounter++;
											if ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT) {
												NCU_LineStatus &= ~STD_LINE_STATUS;
												NCU_LineStatus |= (STD_LINE_STATUS & STD_TEL_RECEIVE);
												SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_STD_LINE_IN_RECEIVE; 
											}
										}
									}
								}
							}
						}
#endif
						/* 拡張ライン側の場合 */
						NCUStatus |= TELEPHONE1_OFF_HOOK;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |=  SYS_TEL1_OFF_HOOK;
						TelIndependentRelayControl();
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL1_OFF_HOOK;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
						
						if(!(Tel1OhCounter = (UWORD)(CHK_OnhookOffhookTime() * 10))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel1OhCounter = 40;
						}
#else /* defined (KEISATSU) */
						H_RelayOff();	/* 1998/05/11 by T.Soneoka */
#endif /* defined (KEISATSU) */
					}
				}
			}
		}
		else if ((!(OhPortStatus & TEL1_OFF_HOOK)) && (NCUStatus & TELEPHONE1_OFF_HOOK)) {
			if(!(--Tel1OhCounter )){
				if ( SYS_InternalLineNumber == SYS_STD_LINE_COM ) {	/**	標準回線で通信中か？	*/
					/* 標準回線での通信中の場合 */
					/* 何もしません	*/
				}
				else {
#if (0) /* 1998/05/11 by T.Soneoka */
**					/*	拡張回線での通信中	*/
**					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定は？	*/
**						/* 標準ライン側の場合 */
**						if (!(NCUStatus & TELEPHONE2_OFF_HOOK)) {
**							NCUStatus &= (~TELEPHONE1_OFF_HOOK);
**							L_RelayOff();	/**	LリレーOff */
**						}
**					}
**					else {
**						/* 拡張ライン側の場合 */
**						NCUStatus &= (~TELEPHONE1_OFF_HOOK);
**					}
#else
#if !defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定は？	*/
						if (CHK_UNI_NoRingTel2Detachable()) {
							if (SilentReceiveRequest()) {
								L_RelayOn();
							}
							else {
								L_RelayOff();
							}
						}
						else {
							L_RelayOff();
						}
					}
					else {
						L_RelayOn();
					}
#endif /* defined (KEISATSU) */
					NCUStatus &= (~TELEPHONE1_OFF_HOOK);
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
					if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
						/* 秘話機能起動した場合 */
						SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
						SYS_LineTelStatus |= STD_READY;
					}
					H_RelayOff();
					SYS_RingCounter = 0;
					/*-------------------------------*/
					/**		メイン・タスクへ通知	 */
					/*-------------------------------*/
					TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
					snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
					
					if(!(Tel1OhCounter = (UWORD)(CHK_OnhookOffhookTime() * 10))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
						Tel1OhCounter = 40;
					}
#endif /* defined (KEISATSU) */
#endif
				}
			}
		}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
		else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL1_OFF_HOOK) && (!(NCUStatus & TELEPHONE1_OFF_HOOK))) {
			if(!(--Tel1OhCounter )){
				if ( SYS_InternalLineNumber == SYS_STD_LINE_COM ) {	/**	標準回線で通信中か？	*/
					/* 標準回線での通信中の場合 */
					/* 何もしません	*/
				}
				else {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL1_OFF_HOOK;
					if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
						/* 秘話機能起動した場合 */
						SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
						SYS_LineTelStatus |= STD_READY;
					}
					H_RelayOff();
					SYS_RingCounter = 0;
					/*-------------------------------*/
					/**		メイン・タスクへ通知	 */
					/*-------------------------------*/
					TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT;
					snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);
					
					if(!(Tel1OhCounter = (UWORD)(CHK_OnhookOffhookTime() * 10))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
						Tel1OhCounter = 40;
					}
				}
			}
		}
#endif /* defined (KEISATSU) */
		else {
			if(!(Tel1OhCounter = (UWORD)(CHK_OnhookOffhookTime() * 10))) {	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
				Tel1OhCounter = 40;
			}
		}
		/*--------------------------------*/
		/* 外付電話のＨＯＯＫ状態監視部位 */
		/*--------------------------------*/
		if ((OhPortStatus & TEL2_OFF_HOOK) && (!(NCUStatus & TELEPHONE2_OFF_HOOK))) {
			if(!(--Tel2OhCounter )){
				if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準回線で通信中か？	*/
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定は？	*/
						/* 標準ライン側の場合 */
						/* 何もしません	*/
					}
					else {
#if defined (KEISATSU) /* 警察FAX DVT_ID18&25&26 Added by SMuratec 李 2005/11/15 */
						comp_min_on_time = NCU_CI_MinOnTime(); /* 最小ON期間を獲得 */
						if ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) {
							if(!SYS_RingCounterExt){
								if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_EXT)
									&& (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE))) {
								}
								else if (NCU_ND_Status & (ND_SUSPICIOUS_CI_DETECTED | ND_CI_SEQUENCE_DETECTED | ND_CAR_DETECTED | ND_SLEEP_AFTER_ACK_RESPONSE)) {
								}
								else{
									if (RingStatus2nd & CI_EXT_LINE) {	/**	CI検出状態が標準ラインの場合	*/
					  					if(( RingingOnTime2nd   >= comp_min_on_time )
										|| ( SamplingBuff2nd[0] >= comp_min_on_time )){
											SYS_RingCounterExt++;
											if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT) {
												NCU_LineStatus &= ~EXT_LINE_STATUS;
												NCU_LineStatus |= (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
												SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_EXT_LINE_IN_RECEIVE; 
											}
										}
									}
								}
							}
						}
#endif
						/* 拡張ライン側の場合 */
						NCUStatus |= TELEPHONE2_OFF_HOOK;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TEL2_OFF_HOOK;
						TelIndependentRelayControl();
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
						while (IsSHIREIKido){
							wai_tsk(1);
						}
						IsSHIREIKido = TRUE;
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_TEL2_OFF_HOOK;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);

						if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel2OhCounter = 40;
						}
#else /* defined (KEISATSU) */
						L_RelayOff();	/* 1998/05/11 by T.Soneoka */
#endif /* defined (KEISATSU) */
					}
				}
				else {
					/*	拡張回線での通信中	*/
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が拡張ライン側か？	*/
						/* 標準ライン側の場合 */
						if (!(NCUStatus & TELEPHONE1_OFF_HOOK)) {
							NCUStatus |= TELEPHONE2_OFF_HOOK;
							H_RelayOn();	/**	秘話機能のため HリレーOn */
							L_RelayOff();	/* 1998/05/11 by T.Soneoka */
						}
					}
					else {
						/* 拡張ライン側の場合 */
						/* 何もしません	*/
					}
				}
			}
		}
		else if ((!(OhPortStatus & TEL2_OFF_HOOK)) && (NCUStatus & TELEPHONE2_OFF_HOOK)) {
			if(!(--Tel2OhCounter )){
				if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準回線で通信中か？	*/
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定は？	*/
						/* 標準ライン側の場合 */
						/* オフフックのとき何もしていないので、ここでも何もしません	*/
					}
					else {
						/* 拡張ライン側の場合 */
						NCUStatus &= ~TELEPHONE2_OFF_HOOK;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
						if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
							/* 秘話機能起動した場合 */
							SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
							SYS_LineTelStatus |= EXT_READY;
						}
						L_RelayOff();
						SYS_RingCounterExt = 0;
						/*-------------------------------*/
						/**		メイン・タスクへ通知	 */
						/*-------------------------------*/
						/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
						while (IsSHIREIKido){
							wai_tsk(1);
						}
						IsSHIREIKido = TRUE;
						TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;
						snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
						rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);

						if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
							Tel2OhCounter = 40;
						}
#endif /* defined (KEISATSU) */
					}
				}
				else {
					/* 拡張回線での通信中の場合 */
					/* 何もしません	*/
				}
			}
		}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
		else if ((SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK) && (!(NCUStatus & TELEPHONE2_OFF_HOOK))) {
			if(!(--Tel2OhCounter )){
				if ( SYS_InternalLineNumber == SYS_EXT_LINE_COM ) {	/**	拡張回線で通信中か？	*/
					/* 拡張回線での通信中の場合 */
					/* 何もしません	*/
				}
				else {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_TEL2_OFF_HOOK;
					if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
						/* 秘話機能起動した場合 */
						SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
						SYS_LineTelStatus |= EXT_READY;
					}
					L_RelayOff();
					SYS_RingCounterExt = 0;
					/*-------------------------------*/
					/**		メイン・タスクへ通知	 */
					/*-------------------------------*/
					/* 警察FAX DVT_ID81 Added By SMuratec 李 2005/12/21 */
					while (IsSHIREIKido){
						wai_tsk(1);
					}
					IsSHIREIKido = TRUE;
					TxTelephoneOperationTaskMsg.Message = MSG_DETECT_ON_HOOK_CONT_TEL2;
					snd_msg(mbxno.MAN_Task, &TxTelephoneOperationTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneOperationTaskSub, &RxTelephoneOperationTaskMsg);

					if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
						Tel2OhCounter = 40;
					}
				}
			}
		}
#endif /* defined (KEISATSU) */
		else {
			if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){	/* UBYTE -> UWORD By M.Tachibana 1998/10/25 */
				Tel2OhCounter = 40;
			}
		}
	}
}
#endif


#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* 村田５５転送 REMOTE_RX_FUNC */

/* リモートダイアル転送か */
UBYTE NCU_RemoteTransferDial(void)
{
	if (CHK_RemoteTransferDial()) {
		return TRUE;
	}
	return FALSE;
}

 #if (0) /* 2002/02/03 Y.Murata オンフック転送のソースコードを削除 */
 ///* オンフック転送か */
 //UBYTE NCU_RemoteTransferOnHook(void)
 //{
 //	if (!EnableRemoteTransferOnHook) {	/* ROMスイッチチェック */
 //		return FALSE;
 //	}
 //	if (CHK_RemoteTransferOnHook()) {
 //		return TRUE;
 //	}
 //	return FALSE;
 //}
 #endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リモート受信（ＴＥＬ２のダイヤル信号）検出タスク]
	function	:[
		1.回線タイプがＤＰの場合、外付電話（ＴＥＬ２）のＤＰのＯＨの状態変化を監視します。
		2.回線タイプがプッシュの場合、ＤＴＭＦレシーバーの状態変化を監視します｡
		3.１０ｍｓ毎に状態を見ています。
		4.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、30ms～50msONされています。
		5.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、60ms～100msONされています。
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[19978/01/24]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		NCU_RemoteRxSignalDetTask( WORD *tx_mail_box_no )
{
	MESSAGE_t	msg;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 2003/02/19 */
	UBYTE	dial_type;
#endif
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
	UBYTE	ret;
	
	ret = FALSE;
#endif /* defined (KEISATSU) */

	msg.Item = FROM__NCU_SUB;

	/* ＣＩを検出している且つ、増設電話がＯＦＦフック、且つ機種固有ｽｲｯﾁ有効 */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 2003/02/14 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		if (!(SYS_RingCounter && (NCUStatus & TELEPHONE2_OFF_HOOK) && NCU_RemoteTransferDial())) {
			wai_tsk(0xFFFF);
		}
	} else {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/25 */
#else /* !defined (KEISATSU) */
		if (!(SYS_RingCounterExt && (NCUStatus & TELEPHONE2_OFF_HOOK) && NCU_RemoteTransferDial())) {
			wai_tsk(0xFFFF);
		}
#endif /* defined (KEISATSU) */
	}
#else
	if (!(SYS_RingCounter && (NCUStatus & TELEPHONE2_OFF_HOOK) && NCU_RemoteTransferDial())) {
		wai_tsk(0xFFFF);
	}
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
	while (ret == FALSE) {
		if (!ModemRelaySetting()) { /* モデムリレーは標準回線に接続の場合 */
			if ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE) {
				tskno_RemoteRxSignalDetTask = 0xFFFF;
				exi_tsk();
			}
			dial_type = CHK_DialType();
		} else {	 /* モデムリレーは拡張回線に接続の場合 */
			if ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE) {
				tskno_RemoteRxSignalDetTask = 0xFFFF;
				exi_tsk();
			}
			dial_type = (CHK_DialTypeExt() >> 6);
		}
		switch (dial_type) {
		case LINE_TYPE_TONE:
			/*----------------
			** DTMF検出モード 
			*/
			MDM_ToneModeConfig();
			MDM_ConfigDTMF_ReceiverMode();

			ret = NCU_RemoteRxDTMFDetect();
			break;

		case DIAL_SPEED_20PPS:		/* ダイヤル時、３０ｍｓ～５０ｍｓ連続ＯＮしている */

			if (CHK_RemoteTransferForcedDTMF()) {
				MDM_ToneModeConfig();
				MDM_ConfigDTMF_ReceiverMode();
				ret = NCU_RemoteRxDTMFDetect();
			}
			else {
				ret = NCU_RemoteRxDialPulseDetect(1);
			}
			break;

		case DIAL_SPEED_10PPS:		/* ダイヤル時、６０ｍｓ～１００ｍｓ連続ＯＮしている */

			if (CHK_RemoteTransferForcedDTMF()) {
				MDM_ToneModeConfig();
				MDM_ConfigDTMF_ReceiverMode();
				ret = NCU_RemoteRxDTMFDetect();
			}
			else {
				ret = NCU_RemoteRxDialPulseDetect(2);
			}
			break;
		default:
			break;
		}
		wai_tsk(1);
	}
#else /* !defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 2003/02/19 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		dial_type = CHK_DialType();
	} else {
		dial_type = (CHK_DialTypeExt() >> 6);
	}
	switch (dial_type) {
#else
	switch (CHK_DialType()) {
#endif
	case LINE_TYPE_TONE:
		/*----------------
		** DTMF検出モード 
		*/
		MDM_ToneModeConfig();
		MDM_ConfigDTMF_ReceiverMode();

		NCU_RemoteRxDTMFDetect();
		break;

	case DIAL_SPEED_20PPS:		/* ダイヤル時、３０ｍｓ～５０ｍｓ連続ＯＮしている */

		if (CHK_RemoteTransferForcedDTMF()) {
			MDM_ToneModeConfig();
			MDM_ConfigDTMF_ReceiverMode();
			NCU_RemoteRxDTMFDetect();
		}
		else {
			NCU_RemoteRxDialPulseDetect(1);
		}
		break;

	case DIAL_SPEED_10PPS:		/* ダイヤル時、６０ｍｓ～１００ｍｓ連続ＯＮしている */

		if (CHK_RemoteTransferForcedDTMF()) {
			MDM_ToneModeConfig();
			MDM_ConfigDTMF_ReceiverMode();
			NCU_RemoteRxDTMFDetect();
		}
		else {
			NCU_RemoteRxDialPulseDetect(2);
		}
		break;
	default:
		break;
	}
#endif /* defined (KEISATSU) */
	/*---------------------------------------------------------------*/
	/** 多機能電話制御監視メインタスク）へ結果を通知                 */
	/*---------------------------------------------------------------*/
	msg.Message = DETECT_REMOTE_RX_SIGNAL;
	snd_msg( *tx_mail_box_no, &msg);
	/*-----------*/
	/** 終了待ち */
	/*-----------*/
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リモート受信（ＴＥＬ２のダイヤル信号）検出タスク]
	function	:[
		1.回線タイプがプッシュの場合、ＤＴＭＦレシーバーの状態変化を監視します｡
		2.１０ｍｓ毎に状態を見ています。
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[19978/01/24]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	NCU_RemoteRxDTMFDetect( void )
{
 #if (PRO_MODEM == R288F)
	UBYTE i;
	UBYTE det_cnt;		/* 検出するべきDTMF桁数 */
	UBYTE rcv_cnt;		/* 検出したDTMF桁数 */
	UWORD off_time;		/* 桁間の時間 */
	UWORD max_off_time;	/* 桁間の最大有効時間 */
	UBYTE pre_det;
	UBYTE check_bit;
	UBYTE comp_bit;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
	UBYTE spec_rcv_cnt;	/* 検出したDTMF桁数(特番用) */
	UBYTE line_number; 	/* 監視回線番号 */
#endif /* defined (KEISATSU) */
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)		/* (ANS待機での55転送) 移植 by SMuratec 李 2004/08/27 */
	UBYTE	dtmf_receiver_counter;
	UBYTE	number;
	UBYTE	cng_detect_stop;
	MESSAGE_t	msg;
	dtmf_receiver_counter = 0;
	cng_detect_stop = 0;
	number = CHK_UNI_AnsFaxDTMFDetect();
	msg.Item = FROM__NCU_TAD;
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
/* 特番受信フラグ */
	NCU_SpecialReceiveFlag = FALSE;
	line_number = (UBYTE)ModemRelaySetting();
#endif /* defined (KEISATSU) */

	check_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS | IO_BIT_DTMFD);
	comp_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS);
	pre_det = 0;

/* 警察FAX Modify by SMuratec 夏 2005/08/19 */
#if defined(KEISATSU)
	if( CHK_RemoteTransferDialOne() ){
		det_cnt = 1;
	}
	else{
		det_cnt = 2;
	}
#else
	if (CHK_RemoteTransfer3ThNumber()) {
		det_cnt = 3;
	}
	else {
		det_cnt = 2;
	}
#endif
/* 警察FAX Modify End */

	rcv_cnt = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
	spec_rcv_cnt = 0;
#endif /* defined (KEISATSU) */
	off_time = 0;
	max_off_time = (UWORD)(CHK_RemoteTransferDialTimer() * 100);
	if (!max_off_time) {		/* REMOTE_RX_FUNC_REMOTE_RX_FUNC */
		max_off_time = 300;
	}

	for (i = 0;i < 3;i++) {
		DTMF_Detect_Buffer[i] = 0x0f;
	}

	DEBUG_RemoteTransferDialBufPoint = 0;
	for (i = 0; i < 20; i++) {
		DEBUG_RemoteTransferDialBuf[i] = 0xFF;
	}

  #if (0)	/* REMOTE_RX_FUNC_REMOTE_RX_FUNC */
	/* 検出する桁数の獲得 */
	if (CHK_UNI_DTMF_ThirdNumber()) {
		det_cnt++;
	}
  #endif

	MDM_SetIO(POS_DTMFD, 0);

	while (1) {
		
		if (!pre_det) {
			if ((inp(MDM_REG_1B_PORT) & comp_bit) == comp_bit) {
				pre_det = 1;
			}
		}
		if (rcv_cnt == det_cnt) {
			return (TRUE);
		}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
		else if (spec_rcv_cnt == det_cnt) {
			NCU_SpecialReceiveFlag = TRUE;
			return (TRUE);
		}
		else if (line_number != (UBYTE)ModemRelaySetting()) {
			return (FALSE);
		}
		else if (!ModemRelaySetting() /* モデムリレーは標準回線に接続の場合 */
				&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE)) {
			return (FALSE);
		}
		else if (ModemRelaySetting()	 /* モデムリレーは拡張回線に接続の場合 */
				&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE)) {
			return (FALSE);
		}
#endif /* defined (KEISATSU) */
		else {
		 	if (((inp(MDM_REG_1B_PORT) & check_bit) == IO_BIT_DTMFD) && pre_det) {

				/*----------------------------
				** 3秒以上の桁間があった場合は
				** それまで受信したDTMFを無効
				** とします。
				*/
#if !defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/22 */
				if (off_time >= max_off_time) {
					rcv_cnt = 0;
				}
#endif /* defined (KEISATSU) */
				off_time = 0;

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2)		/* (ANS待機での55転送) 移植 by SMuratec 李 2004/08/27 */
				if ((TADStatus & FAX_TAD_STATE)			/* 外付留守番電話着信中の場合 */
				 && (CHK_TAD_FaxReadyOnhookTransfer())	/* ANS待機オンフック転送 */
				 && (CHK_UNI_AnsFaxDTMFDetect())		/* CNG検出停止の為のDTMF検出 */
				 && ((SYS_ANS_FAX_READY == NCU_RxModeSwitch) && SYS_RingCounter)	/* 保険 */
				 && (!cng_detect_stop)) {				/* CNG検出停止フラグ */
					if (++dtmf_receiver_counter >= number) {
						cng_detect_stop = TRUE;
						msg.Message = DETECT_REMOTE_DTMF;
						snd_msg( mbxno.NCU_FaxTadAutoSwitchTask, &msg);
					}
				}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

				/*----------
				** DTMF獲得
				*/
				DTMF_Detect_Buffer[rcv_cnt] = MDM_GetIO(POS_DTMFW);
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
				if (spec_rcv_cnt != rcv_cnt) {
					DTMF_Detect_Buffer[spec_rcv_cnt] = DTMF_Detect_Buffer[rcv_cnt];
				}
#endif /* defined (KEISATSU) */
				MDM_SetIO(POS_DTMFD, 0);
				pre_det = 0;


				if (DEBUG_RemoteTransferDialBufPoint < 20) {
					DEBUG_RemoteTransferDialBuf[DEBUG_RemoteTransferDialBufPoint] = DTMF_Detect_Buffer[rcv_cnt];
					DEBUG_RemoteTransferDialBufPoint++;
				}

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
				if (NCU_CompareSpecialNumber(spec_rcv_cnt)) {
					spec_rcv_cnt++;
				}
				else if (NCU_CompareRemoteNumber(rcv_cnt)) {
					rcv_cnt++;
				}
#else /* defined (KEISATSU) */
				if (NCU_CompareRemoteNumber(rcv_cnt)) {
					rcv_cnt++;
				}
#endif /* defined (KEISATSU) */
				else {
					rcv_cnt = 0;
				}
			}
			else {
				if (off_time == 0xffff) {
					off_time = max_off_time;
				}
				else {
					off_time++;
				}
			}
		}
		wai_tsk(1);
	}
 #else
	return FALSE;
 #endif
}
/*************************************************************************
	module		:[リモート起動番号と、検出したDTMFを比較する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[2001/10/11]
	author		:[松本正幸]
*************************************************************************/
UBYTE NCU_CompareRemoteNumber(UBYTE cnt)
{
#if (0)	/* 55転送の3桁目を*でも検出できるようにする by J.Kishida 2003/11/14 */
//	UBYTE i;
//	UBYTE remote_num[3];
//
//	remote_num[0] = CHK_RemoteTransferDialNumber1();
//	remote_num[1] = CHK_RemoteTransferDialNumber2();
//	remote_num[2] = 0x0B;	/* '#' */ /* '#'の方が '*'より検出しやすかったから */
//
//	for (i = 0;i < 2;i++) {
//		switch (remote_num[i]) {
//		case 0:
//			remote_num[i] = DTMF_5;
//			break;
//		case 0x0C:
//		case 0x0D:
//		case 0x0E:
//		case 0x0F:
//			remote_num[i] = DTMF_0;
//			break;
//		default:
//			break;
//		}
//	}
//
//	if (DTMF_Detect_Buffer[cnt] == remote_num[cnt]) {
//		return (TRUE);
//	}
//	else {
//		for (i = 0;i < 3;i++) {
//			DTMF_Detect_Buffer[i] = 0x0f;
//		}
//		return (FALSE);
//	}
#else
	UBYTE num_count;
	UBYTE remote_number[3];
	UBYTE sharp_aster;

	remote_number[0] = CHK_RemoteTransferDialNumber1();
	remote_number[1] = CHK_RemoteTransferDialNumber2();

	/* MEMSW 68-4で＃か＊かを指定するようにします by J.Kishida 2003/08/12 */
	sharp_aster = CHK_RemoteTransNum3_SharpAster();
	if (sharp_aster == 0) {
		remote_number[2] = DTMF_SHARP;	/* '#'(0x0B) */
	}
	else {
		remote_number[2] = DTMF_ASTA;	/* '*'(0x0A) */
	}

	/* 変換は1,2桁目のみ行います */
	for (num_count = 0; num_count < 2; num_count++) {
		switch (remote_number[num_count]) {
		case DTMF_0:	/* '0' */
			remote_number[num_count] = DTMF_5;
			break;
		case 0x0C:		/* 'A' */
		case 0x0D:		/* 'B' */
		case 0x0E:		/* 'C' */
		case 0x0F:		/* 'D' */
			remote_number[num_count] = DTMF_0;
			break;
		default:
			break;
		}
	}

	/*
	// 今回検出した番号1桁だけを判定します．
	// 1桁検出する度にここを通るので，
	// 遡って全ての桁を判定することはしません．
	*/
 #if (0)
	/*
	// MEMSW 68-4で＃か＊かを指定するようにするので
	// 「3桁目は＃/＊のどちらでも可とする」のは止めにします．
	// by J.Kishida 2003/08/12
	*/
//	if (cnt == 2) {
//		switch (DTMF_Detect_Buffer[cnt]) {
//		case DTMF_ASTA:		/* '*'(0x0A) */
//		case DTMF_SHARP:	/* '#'(0x0B) */
//			return (TRUE);
//		default:
//			break;
//		}
//	}
//	else {
//		if (DTMF_Detect_Buffer[cnt] == remote_number[cnt]) {
//			return (TRUE);
//		}
//	}
 #else
	if (DTMF_Detect_Buffer[cnt] == remote_number[cnt]) {
		return (TRUE);
	}
 #endif

	/*
	// TRUEで抜けない場合はDTMF_Detect_Buffer[]をクリアして
	// FALSEを返します．
	*/
	for (num_count = 0; num_count < 3; num_count++) {
		DTMF_Detect_Buffer[num_count] = 0x0F;
	}
	return (FALSE);

#endif	/* #if (0) */
}
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リモート受信（ＴＥＬ２のダイヤル信号）検出タスク]
	function	:[
		1.回線タイプがＤＰの場合、外付電話（ＴＥＬ２）のＤＰのＯＨの状態変化を監視します。
		3.１０ｍｓ毎に状態を見ています。
		4.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、30ms～50msONされています。
		5.DP10の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、60ms～100msONされています。
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[19978/01/24]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	NCU_RemoteRxDialPulseDetect( UBYTE dial_type )
{
	UWORD off_count;						/* WORDに変更 2003/02/13 Y.Murata */
	UWORD on_count;							/* WORDに変更 2003/02/13 Y.Murata */
	UBYTE pulse_count;				/* 検出したダイヤルパルス数 */
	UBYTE pre_ohport_status;		/* 10ms前のＯＨの状態 */
	UBYTE current_ohport_status;	/* 現在のＯＨの状態 */
	UWORD min_on_time;						/* WORDに変更 2003/02/13 Y.Murata */
	UWORD max_on_time;						/* WORDに変更 2003/02/13 Y.Murata */
	UWORD max_off_time;						/* WORDに変更 2003/02/13 Y.Murata */
	UBYTE det_cnt;
	UBYTE rcv_cnt;
	UBYTE is_pulse_detecting;
	UBYTE i;
	UWORD timeout;
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/14 */
	UBYTE detect_object;
	UBYTE spec_rcv_cnt;	/* 検出したDTMF桁数(特番用) */
	
	detect_object = 0;
#endif /* defined (KEISATSU) */

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
/* 特番受信フラグ */
	NCU_SpecialReceiveFlag = FALSE;
#endif /* defined (KEISATSU) */

	/*------------------------------*/
	/**     内部変数の初期化        */
	/*------------------------------*/
	if (CHK_RemoteTransferDialOne()) {		/* 検出は１桁だけでＯＫとする */
		det_cnt = 1;
	}
	else {
		det_cnt = 2;
	}
	rcv_cnt = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
	spec_rcv_cnt = 0;
#endif /* defined (KEISATSU) */

	off_count = 0;
	on_count = 0;
	pulse_count = 0;			/* 検出したダイヤルパルス */
	current_ohport_status = 0;	/* 現在のＯＨの状態 */

	if (dial_type == 1) {	/* 20pps */
		min_on_time = 2;
		max_on_time = 6;
		max_off_time = 10;
	}
	else {	/* 10pps */
		min_on_time = 5;
		max_on_time = 12;
		max_off_time = 20;
	}


	timeout = (UWORD)(CHK_RemoteTransferDialTimer() * 100);
	if (!timeout) {
		timeout = 300;
	}
	is_pulse_detecting = FALSE;

#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/14 */
	if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
		if ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE) {
			if (NCU_LineStatus & STD_HDST_OFFHOOK) {
				detect_object = 1; /* 標準回線側付属電話を監視し */
				pre_ohport_status = OffHook1();	/* 最初にＯＨの状態を取り込んでおく */
			}
			else {
				detect_object = 2;	/* 標準回線側外付電話を監視し */
				pre_ohport_status = OffHook2();	/* 最初にＯＨの状態を取り込んでおく */
			}
		}
	}
	else {	/* モデムリレーを拡張回線に接続している場合 */
		if ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE) {
			if (NCU_LineStatus & EXT_HDST_OFFHOOK) {
				detect_object = 3; /* 拡張回線側付属電話を監視し */
				pre_ohport_status = OffHook1();	/* 最初にＯＨの状態を取り込んでおく */
			}
			else {
				detect_object = 4;	/* 拡張回線側外付電話を監視し */
				pre_ohport_status = OffHook3();	/* 最初にＯＨの状態を取り込んでおく */
			}
		}
	}
#else /* !defined (KEISATSU) */
	pre_ohport_status = OffHook2();	/* 最初にＯＨの状態を取り込んでおく */
#endif /* defined (KEISATSU) */
	/*DBG_PulseCount = 0;*/

	DEBUG_RemoteTransferDialBufPoint = 0;
	for (i = 0; i < 20; i++) {
		DEBUG_RemoteTransferDialBuf[i] = 0xFF;
	}


				/*-------------------------------------------*/
	while(1){	/** 親タスクから強制終了されるまで無限ループ */
				/*-------------------------------------------*/

						/*-------------------*/
		wai_tsk( 1 );	/** 監視間隔 10msec  */
						/*-------------------*/

		/*
		 * ダイアルパルス１桁
		*/
		CMN_DisableInterrupt();
		if ((off_count > 50) || (on_count > 50)) {
			OneDigitDiallingExecute = 0;
		}
		else {
			if (on_count) {
				OneDigitDiallingExecute = 1;
				if(!( Tel2OhCounter = (UWORD)( CHK_OnhookOffhookTime() * 10 ))){
					Tel2OhCounter = 40;
				}
			}
			else {
				OneDigitDiallingExecute = 0;
			}
		}
		CMN_EnableInterrupt();

		/*-----------------------------------*/
		/** 付属／外付電話のＯＨ情報の取込み */
		/*-----------------------------------*/
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/14 */
		switch (detect_object) {
		case 1:
			current_ohport_status = OffHook1();	/* 0:ON_HOOK  1:OFF_HOOK  */
			if (ModemRelaySetting()) {	/* モデムリレーを拡張回線に接続している場合 */
				return FALSE;
			}
			break;
		case 2:
			current_ohport_status = OffHook2();	/* 0:ON_HOOK  1:OFF_HOOK  */
			if (ModemRelaySetting()) {	/* モデムリレーを拡張回線に接続している場合 */
				return FALSE;
			}
			break;
		case 3:
			current_ohport_status = OffHook1();	/* 0:ON_HOOK  1:OFF_HOOK  */
			if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
				return FALSE;
			}
			break;
		case 4:
			current_ohport_status = OffHook3();	/* 0:ON_HOOK  1:OFF_HOOK  */
			if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
				return FALSE;
			}
			break;
		}
		if (!ModemRelaySetting()) { /* モデムリレーは標準回線に接続の場合 */
			if ((NCU_LineStatus & STD_LINE_STATUS) != STD_TEL_RECEIVE) {
				return (FALSE);
			}
		} else {	 /* モデムリレーは拡張回線に接続の場合 */
			if ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_TEL_RECEIVE) {
				return (FALSE);
			}
		}
#else /* !defined (KEISATSU) */
		current_ohport_status = OffHook2();	/* 0:ON_HOOK  1:OFF_HOOK  */
#endif /* defined (KEISATSU) */

		if (current_ohport_status) {
			DEBUG_Triger = 1;
		}
		else {
			DEBUG_Triger = 0;
		}


		/*--------------------------------*/
		/* 外付電話のＨＯＯＫ状態監視部位 */
		/*--------------------------------*/
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/15 */
		if( 1 ){
#else /* !defined (KEISATSU) */
		if( NCUStatus & TELEPHONE2_OFF_HOOK ){			/* 増設電話が受話器を上げている状態 */
#endif /* defined (KEISATSU) */
			if( current_ohport_status ) {		/* TEL2 OFF_HOOK */
				off_count++;

#if !defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/22 */
				if (off_count > timeout) {	/* 規定時間パルスがこない */
					rcv_cnt = 0;			/* もう一度最初から */
					is_pulse_detecting = FALSE;
				}
#endif /* defined (KEISATSU) */

				if (is_pulse_detecting) {
					if (off_count >= max_off_time) {	/* OFFの状態が続く*/

						if (DEBUG_RemoteTransferDialBufPoint < 20) {
							DEBUG_RemoteTransferDialBuf[DEBUG_RemoteTransferDialBufPoint] = pulse_count;
							DEBUG_RemoteTransferDialBufPoint++;
						}

						if (NCU_CompareRemoteNumberDP(pulse_count, rcv_cnt)) {		/* ダイアルコンペア */
							rcv_cnt++;
						}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
						else if (NCU_CompareSpecialNumberDP(pulse_count, spec_rcv_cnt)) {		/* ダイアルコンペア */
							spec_rcv_cnt++;
						}
#endif /* defined (KEISATSU) */
						else {
							rcv_cnt = 0;
						}
						if (rcv_cnt >= det_cnt) {
							OneDigitDiallingExecute = 0;
							return TRUE;
						}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
						else if (spec_rcv_cnt >= det_cnt) {
							OneDigitDiallingExecute = 0;
							NCU_SpecialReceiveFlag = TRUE;
							return TRUE;
						}
#endif /* defined (KEISATSU) */
						is_pulse_detecting = FALSE;
					}
				}
			}
			else{								/* TEL2 ON HOOK */
				on_count++;
			}
		}

		if (pre_ohport_status != current_ohport_status) {	/* 状態変化があった */
			if( current_ohport_status ) {		/* TEL2 OFF_HOOK */
				if (on_count >= min_on_time) {
					if (on_count <= max_on_time) {
						/* ダイヤルパルス検出した */
						pulse_count++;
						/*DBG_PulseCount++;*/
						is_pulse_detecting = TRUE;
					}
					else if (on_count <= (max_on_time * 2)) {
						pulse_count += 2;	/* OFFﾌｯｸが検出できない（2個分のﾀﾞｲﾔﾙﾊﾟﾙｽ）検出 */
						is_pulse_detecting = TRUE;
					}
				}
				on_count = 0;
			}
			else {		/* ON_HOOK */
				if ((off_count >= 1) && (off_count <= max_off_time)) {
					/* off期間 10ms～20ms	*/
				}
				else {
					/* 次の桁もしくは、通話状態 */
					pulse_count = 0;
				}
				off_count = 0;
			}
		}
		pre_ohport_status = current_ohport_status;
	}
}



UBYTE NCU_CompareRemoteNumberDP(UBYTE pulse_count, UBYTE rcv_cnt)
{
	UBYTE i;
	UBYTE remote_num[2];
	UBYTE detect_pulse_more;

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/22 */
	remote_num[0] = 3;
	remote_num[1] = 3;
#else /* !defined (KEISATSU) */
	remote_num[0] = CHK_RemoteTransferDialNumber1();
	remote_num[1] = CHK_RemoteTransferDialNumber2();
#endif /* defined (KEISATSU) */
	detect_pulse_more = CHK_RemoteTransferDialNumMore();

	for (i = 0;i < 2;i++) {
		switch (remote_num[i]) {
		case 0:
			remote_num[i] = 5;		/* ダイアルの５ */
			break;
		case 0x0A:
		case 0x0B:
#if (0)
			/*
			// NTT仕様の場合，55転送の番号の初期値は"5*"なので
			// 以下の処理が入っているとDP設定時に55転送できません．
			// NAGANOからのNTT向け機種の作成予定はありませんが，
			// YAWARAからROME NTT作成時に入れた処理を移植しておきます．
			// by J.Kishida 2003/11/14
			*/
//			/* 以下の判断が入っているとDP設定時、転送番号に#/*が登録されていると
//			** まったく検出が出来ない。よって、以下の判断と同様に0に置き換えるよう修正
//			** By O.Kimoto 2003/10/01
//			*/
//			return FALSE;
//			break;
#endif
		case 0x0C:
		case 0x0D:
		case 0x0E:
		case 0x0F:
			remote_num[i] = 10;		/* ダイアルの０ */
			break;
		default:
			break;
		}
	}

	/* ダイヤルパルス方式対応 *//* 2003/02/07 */
	switch (CHK_DP_Method()) {
	case	DIAL_SWE_TYPE:
		if (remote_num[0] == 10) {		/* ダイアルの０ */
			remote_num[0] = 0;
		}
		if (remote_num[1] == 10) {		/* ダイアルの０ */
			remote_num[1] = 0;
		}
		remote_num[0] += 1;
		remote_num[1] += 1;
		break;
	case	DIAL_NZL_TYPE:
		if (remote_num[0] == 10) {		/* ダイアルの０ */
			remote_num[0] = 0;
		}
		if (remote_num[1] == 10) {		/* ダイアルの０ */
			remote_num[1] = 0;
		}
		remote_num[0] = (UBYTE)(10 - remote_num[0]);
		remote_num[1] = (UBYTE)(10 - remote_num[1]);
		break;
	default	:
		break;
	}


#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/22 */
	if ( 3 == CHK_RemoteTransferDialNumber1() 
		&& 3 == CHK_RemoteTransferDialNumber2() ){
		if (detect_pulse_more) {
			if (pulse_count >= remote_num[rcv_cnt]) {
				return (TRUE);
			}
			else {
				return (FALSE);
			}
		}
		else {
			if (pulse_count == remote_num[rcv_cnt]) {
				return (TRUE);
			}
			else {
				return (FALSE);
			}
		}
	}
	else {
		return (FALSE);
	}
#else /* !defined (KEISATSU) */
	if (detect_pulse_more) {
		if (pulse_count >= remote_num[rcv_cnt]) {
			return (TRUE);
		}
		else {
			return (FALSE);
		}
	}
	else {
		if (pulse_count == remote_num[rcv_cnt]) {
			return (TRUE);
		}
		else {
			return (FALSE);
		}
	}
#endif /* defined (KEISATSU) */
}


#elif (PRO_REMOTE_RX == ENABLE)	/* NTTのリモート受信 1998/01/24  By T.Yamaguchi */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リモート受信（ＴＥＬ２のダイヤル信号）検出タスク]
	function	:[
		1.回線タイプがＤＰの場合、外付電話（ＴＥＬ２）のＤＰのＯＨの状態変化を監視します。
		2.回線タイプがプッシュの場合、ＤＴＭＦレシーバーの状態変化を監視します｡
		3.１０ｍｓ毎に状態を見ています。
		4.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、30ms～50msONされています。
		5.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、60ms～100msONされています。
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[19978/01/24]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		NCU_RemoteRxSignalDetTask( WORD *tx_mail_box_no )
{
	MESSAGE_t	msg;

	msg.Item = FROM__NCU_SUB;

	/* ＣＩを検出している且つ、増設電話がＯＦＦフック、且つ機種固有ｽｲｯﾁ有効 */
	if (!(SYS_RingCounter && (NCUStatus & TELEPHONE2_OFF_HOOK) && CHK_RemoteRxON())) {
		wai_tsk(0xFFFF);
	}

	switch (CHK_DialType()) {	/* DIAL_SPEED_20PPS,DIAL_SPEED_10PPS,LINE_TYPE_TONE */
	case LINE_TYPE_TONE:
		NCU_RemoteRxDTMFDetect();
		break;
	case DIAL_SPEED_20PPS:		/* ダイヤル時、３０ｍｓ～５０ｍｓ連続ＯＮしている */
		NCU_RemoteRxDialPulseDetect(1);
		break;
	case DIAL_SPEED_10PPS:		/* ダイヤル時、６０ｍｓ～１００ｍｓ連続ＯＮしている */
		NCU_RemoteRxDialPulseDetect(2);
		break;
	}
	/*---------------------------------------------------------------*/
	/** 多機能電話制御監視メインタスク）へ結果を通知                 */
	/*---------------------------------------------------------------*/
	msg.Message = DETECT_REMOTE_RX_SIGNAL;
	snd_msg( *tx_mail_box_no, &msg);
	/*-----------*/
	/** 終了待ち */
	/*-----------*/
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リモート受信（ＴＥＬ２のダイヤル信号）検出タスク]
	function	:[
		1.回線タイプがプッシュの場合、ＤＴＭＦレシーバーの状態変化を監視します｡
		2.１０ｍｓ毎に状態を見ています。
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[19978/01/24]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	NCU_RemoteRxDTMFDetect( void )
{
	UBYTE	i;
	UBYTE	number;
	UBYTE	dtmf_rcv_dv_on_off;
	UBYTE	dtmf_receiver_counter;
	UBYTE	DTMF_received_buffer[3];
	UBYTE	check_number_buffer[3];
	UWORD	off_time;			/* 桁間の時間 */
	UWORD	max_between_time;	/* 桁間の最大有効時間 */
	UWORD	modem_port_read;

	dtmf_rcv_dv_on_off = OFF;
	dtmf_receiver_counter = 0;
	modem_port_read = 0;
	max_between_time = (UWORD)(CHK_UNI_Between_DTMFandDTMF() * 100);	/* 10ms単位 */
	/* check_number_buffer[0] = CHK_UNI_DTMF_FirstNumber(); */
	/* check_number_buffer[1] = CHK_UNI_DTMF_SecondNumber(); */
	check_number_buffer[0] = 5;		/* '5' */
	check_number_buffer[1] = 0xb;	/* '*' */
	check_number_buffer[2] = CHK_UNI_DTMF_ThirdNumber();	/* '*or#' */
	DTMF_received_buffer[0] = 0xF;
	DTMF_received_buffer[1] = 0xF;
	DTMF_received_buffer[2] = 0xF;

	number = 2;

	/* 検出する桁数の獲得 */
	if (check_number_buffer[2]) {
		number++;
	}

				/*-----------------------------------*/
	while(1){	/** ＤＴＭＦを検出し終わるまでループ */
				/*-----------------------------------*/
		/*--------------------------------*/
		/**       Ｉ／Ｏ　Ｒｅａｄ        */
		/*--------------------------------*/
		modem_port_read = IO__PEDR;
												/*---------------------------------*/
		if(	dtmf_receiver_counter == number ){ 	/** ＤＴＭＦを既に４桁検出した場合 */
												/*---------------------------------*/
													/*---------------------------*/
			if(!( modem_port_read & IO_BIT_DV )){	/** ＤＴＭＦ検出　無効の場合 */
													/*---------------------------*/
				return(1);	/* 検出ＯＫ */
			}
		}
		else{                                                                       /*-------------------------------------------*/
			if(( modem_port_read & IO_BIT_DV ) && ( dtmf_rcv_dv_on_off == OFF )){	/** ＤＴＭＦ検出　有効で且つ前回が無効の場合 */
																					/*-------------------------------------------*/
				if (off_time >= max_between_time) { /* ３秒以上の桁間があった */
					dtmf_receiver_counter = 0;
				}
				off_time = 0;
				/*-----------------------------------*/
				/** 検出ＤＴＭＦをバッファに格納する */
				/*-----------------------------------*/
				DTMF_received_buffer[dtmf_receiver_counter] = (UBYTE)(( modem_port_read & ( IO_BIT_DTMF1 | IO_BIT_DTMF2 | IO_BIT_DTMF3 | IO_BIT_DTMF4 )) >> 8 );

				/*---------------------------------*/
				/** 登録番号と検出ＤＴＭＦとの比較 */
				/*---------------------------------*/
				if (DTMF_received_buffer[dtmf_receiver_counter] == check_number_buffer[dtmf_receiver_counter]) {
					dtmf_receiver_counter++;
				}
				else {
					for (i = 0;i < 3;i++) {	/* クリアする */
						DTMF_received_buffer[i];
					}
					dtmf_receiver_counter = 0;
				}
				dtmf_rcv_dv_on_off  = ON;
			}
			else{
				if(!( modem_port_read & IO_BIT_DV )){
					dtmf_rcv_dv_on_off  = OFF;
					off_time++;
				}
			}
		}
		/*---------------------------------*/
		/** １０ｍｓ自タスクをＷａｉｔする */
		/*---------------------------------*/
		wai_tsk(1);
	}
}




/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リモート受信（ＴＥＬ２のダイヤル信号）検出タスク]
	function	:[
		1.回線タイプがＤＰの場合、外付電話（ＴＥＬ２）のＤＰのＯＨの状態変化を監視します。
		3.１０ｍｓ毎に状態を見ています。
		4.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、30ms～50msONされています。
		5.DP20の場合、ﾀﾞｲﾔﾙﾎﾞﾀﾝを押された時、TE2のＯＨが、60ms～100msONされています。
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[19978/01/24]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	NCU_RemoteRxDialPulseDetect( UBYTE dial_type )
{
	UBYTE off_count;
	UBYTE on_count;
	UBYTE pulse_count;				/* 検出したダイヤルパルス数 */
	UBYTE pre_ohport_status;		/* 10ms前のＯＨの状態 */
	UBYTE current_ohport_status;	/* 現在のＯＨの状態 */
	UBYTE min_on_time;
	UBYTE max_on_time;
	UBYTE max_off_time;
	UBYTE pulse_number;				/* 検出する番号 */
	UBYTE detect_pulse_more;		/* 指定した検出番号以上検出を有効とする */

	/*------------------------------*/
	/**     内部変数の初期化        */
	/*------------------------------*/
	off_count = 0;
	on_count = 0;
	pulse_count = 0;			/* 検出したダイヤルパルス */
	current_ohport_status = 0;	/* 現在のＯＨの状態 */
	min_on_time = (UBYTE)(3 * dial_type);
	max_on_time = (UBYTE)(6 * dial_type);
	max_off_time = (UBYTE)(3 * dial_type);
	pulse_number = CHK_UNI_DP_DetectNumber();
	detect_pulse_more = CHK_UNI_DP_DetectMore();
	pre_ohport_status = OffHook2();	/* 最初にＯＨの状態を取り込んでおく */

	if (pulse_number >= 0xd) {	/* 設定番号がＡからＤのときは検出しない */
		wai_tsk(0xFFFF);
	}
	if (pulse_number == 0) {	/* 0が設定されていたら１０をセットする */
		pulse_number = 10;
	}

				/*-------------------------------------------*/
	while(1){	/** 親タスクから強制終了されるまで無限ループ */
				/*-------------------------------------------*/
						/*-------------------*/
		wai_tsk( 1 );	/** 監視間隔 10msec  */
						/*-------------------*/
		/*-----------------------------------*/
		/** 付属／外付電話のＯＨ情報の取込み */
		/*-----------------------------------*/
		current_ohport_status = OffHook2();	/* 0:ON_HOOK  1:OFF_HOOK  */

		/*--------------------------------*/
		/* 外付電話のＨＯＯＫ状態監視部位 */
		/*--------------------------------*/
		if( NCUStatus & TELEPHONE2_OFF_HOOK ){			/* 増設電話が受話器を上げている状態 */
			if( current_ohport_status ) {		/* TEL2 OFF_HOOK */
				off_count++;
				if (pulse_count == pulse_number) {	/* 指定桁数のＤＰを検出している */
					if (off_count >= max_off_time) {	/* OFFの状態が続く*/
						return(1);	/* 検出ＯＫ */
					}
				}
			}
			else{								/* TEL2 ON HOOK */
				on_count++;
			}
		}

		if (pre_ohport_status != current_ohport_status) {	/* 状態変化があった */
			if( current_ohport_status ) {		/* TEL2 OFF_HOOK */
				if (on_count >= min_on_time) {
					if (on_count <= max_on_time) {
						/* ダイヤルパルス検出した */
						pulse_count++;
						if ((pulse_count >= pulse_number) && (detect_pulse_more)) {
							return(1);	/* 指定信号以上検出ＯＫ */
						}
					}
					else if (on_count <= (max_on_time * 2)) {
						pulse_count += 2;	/* OFFﾌｯｸが検出できない（2個分のﾀﾞｲﾔﾙﾊﾟﾙｽ）検出 */
					}
				}
				on_count = 0;
			}
			else {		/* ON_HOOK */
				if ((off_count >= 1) && (off_count <= max_off_time)) {
					/* off期間 10ms～20ms	*/
				}
				else {
					/* 次の桁もしくは、通話状態 */
					pulse_count = 0;
				}
				off_count = 0;
			}
		}
		pre_ohport_status = current_ohport_status;
	}
}
#else	/* 従来のオンフック転送 */
void NCU_RemoteRxSignalDetTask( WORD *tx_mail_box_no ) {}
#endif	/* (PRO_REMOTE_RX == ENABLE) */
