/**********************************************************************
*	ANZU
*
*	File	Name:	NCU_RLY.C
*	Coded	  by:	坂本直史
*	Module	Name:	[リレー制御用関数]
*						AfterCI_TimerSet()
*						PauseControl()
*						InterRelayTimer()
*						CML_RelaySetting()	cmn_io.cに移動 By M.Tachibana 1997/02/13
*						H_RelaySetting()	cmn_io.cに移動 By M.Tachibana 1997/02/13
*						L_RelaySetting()	cmn_io.cに移動 By M.Tachibana 1997/02/13
*						DP_RelaySetting()	cmn_io.cに移動 By M.Tachibana 1997/02/13
*						S_RelaySetting()	cmn_io.cに移動 By M.Tachibana 1997/02/13
*					[一般リレー制御関数]
*						SilentReceiveRequest()
*						InitializeRelay()
*						CallingRelayControl()
*						ReverseRelayControl()
*						F_Net_DisconnectRelayControl()
*						TelIndependentRelayControl()
*						TelephoneToFaxcomRelayControl()
*					[回線捕捉キー関係リレー制御関数]
*						HookKeyOnRelayControl()
*						HookKeyOffRelayControl()
*						HookingRelayControl()
*					[保留関係リレー制御関数]
*						ModemOnRelayControl()
*						HoldKeyOnRelayControl()
*						HoldKeyOffRelayControl()
*					[ダイヤリング関係リレー制御関数]
*						SignalChangeRelayControl()
*						DTMFDialStartRelayControl()
*						DPDialStartRelayControl()
*						DialEndRelayControl()
*						Flash_Off_On()
*						MercuryDial()
*					[ダイヤル・イン関係リレー制御関数]
*						DialIn1stAnswerRealyControl()
*						DialIn2ndAnswerRelayControl()
*						DialinIndependentRelayControl()
*					[疑似ベル関係リレー制御関数]
*						GenerateRingStartRelayControl()
*						GenerateRingEndRelayControl()
*						GenerateRingKeyOn()
*						GenerateRingKeyOff()
*						GenerateRingPreventRelayControl()
*					[内線通話関係リレー制御関数]
*						InterCallStartRelayControl()
*						InterCallStopRelayControl()
*						InterComStartRelayControl()
*						TransferChangeRelayControl()
*						ThreePartComStartRelayControl()
*						ThreePartComStopRelayControl()
*						ThreePartComResetRelayControl()
*
*
*	Note	:	リレー制御(非機種依存）
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
#include    "\src\atlanta\define\product.h"
#include    "\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\status.h"
#include    "\src\atlanta\define\std.h"
#include    "\src\atlanta\define\cmn_pro.h"
#include    "\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
#include	"\src\atlanta\define\fcm_def.h"
#endif /* defined (KEISATSU) */

#include	"\src\memsw\define\mems_pro.h"

#include 	"\src\atlanta\define\uni_pro.h"
#include    "\src\atlanta\define\atd_def.h"

#include    "\src\atlanta\define\ncu_pro.h"
#include    "\src\atlanta\define\ncu_stat.h"
#include    "\src\atlanta\define\ncu_ret.h"
#include    "\src\atlanta\define\ncu_cnst.h"
#include    "\src\atlanta\define\ncu_def.h"

#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/23 */
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
#include	"\src\atlanta\ext_v\sys_port.h"
#include    "\src\atlanta\ext_v\ncu_data.h"

#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\sh_port.h"
#include    "\src\atlanta\sh7043\define\def_tib.h"
#include    "\src\atlanta\sh7043\ext_v\extv_mbx.h"

#include 	"\src\atlanta\define\cmn_pro.h"

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/13 */
#include    "\src\atlanta\ext_v\bkupram.h"
#include    "\src\atlanta\define\sysnd.h"
 #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* added by H.Hirao 1999/05/11 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
	#include    "\src\atlanta\define\cl1_def.h"
 #endif
#endif

#if defined(POPLAR_H) && defined(JP0)/*V851 By Y.Suzuki 2002/09/12*/
#include    "\src\atlanta\ext_v\sys_data.h"
#include    "\src\atlanta\define\sys_stat.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/14 */
/* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/05 */
#include "\src\atlanta\sh7043\define\sh_port.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"
#include    "\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sys_line.h"
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#endif /* defined (KEISATSU) */

/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[リレーが回線側に倒れた直後のノイズをＣＩと誤検出しない為のタイマ]
	function	:[
		1.メモリ・スイッチの設定時間ＣＩ割込を無視する為のタイマをセットする。
	]
	return		:[なし]
	common		:[
		AfterCI_HL_RelayOn		：ＣＩ無視時間（０でなけれはＣＩ割込を無視）
		CI_Counter　　　　　　　：ＣＩ割込発生回数
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		AfterCI_TimerSet(void)
{
	if(!( AfterCI_HL_RelayOn = (UBYTE)( CHK_TEL_RelayOffAfterCI_Ignore()))){;
		AfterCI_HL_RelayOn = 70;
	}
	CI_Counter = 0;
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ポーズ用タイマー]
	function	:[
		1.メモリ・スイッチの設定時間、多機能電話実行タスクをＷａｉｔさせ、ポーズとする。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[FRAは、連続ポーズ不可]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	    PauseControl( void  )
{
	UWORD    time;

#if defined(FRA)
	if(!PauseDetectFlag){
		time = ( UWORD )( CHK_PauseTime() * 100 - 60 );	/* close to 2.5sec */
		PauseDetectFlag = 1;
		if( time ){
    		wai_tsk(time);
    	}
	}
#else
	time = ( UWORD )( CHK_PauseTime() * 100 );
	if( time ){
    	wai_tsk(time);
    }
#endif
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[１００ｍｓウェイトタイマー]
	function	:[
		1.100msecウェイトする。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		InterRelayTimer(void)
{
	UWORD time;

	time = 10;
	wai_tsk(time);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無鳴動着信する条件]
	function	:[
		1.・サイレント・オペレーション設定
		  ・ダイヤルイン待機
		  ・TEL/FAX待機のFAX優先
		  なら1を返す
		2.それ以外なら0を返す
	]
	return		:[
		0	:無鳴動着信禁止
		1	:無鳴動着信許可
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	 SilentReceiveRequest(void)
{
	
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/13 */
 #if 0 /* changed by H.Kubo 1998/11/25 */
	if (CHK_NumberDisplayON() && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED)) {
		return 1;
	}
 #else
 	/* ナンバーディスプレイＯＮで通常回線に接続した時、最初の呼出音で無鳴動着信してしまうのを防ぎます。by H.Kubo 1998/11/25 */
	if (NCU_ND_Status & ND_COUNTING_2ND_RING) { /* added by H.Kubo 1998/11/26 */
	}
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/20 */
	else if (!DEBUG_NumberDisplay && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && (SYS_RingCounter == 0 ) ) {
		return 1;
	}
	else if ((SYS_LineNDStatus == ND_USED_IN_STD) && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && (SYS_RingCounter == 0 ) ) {
		return 1;
	}
	else if ((SYS_LineNDStatus == ND_USED_IN_EXT) && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && (SYS_RingCounterExt == 0 ) ) {
		return 1;
	}
 #else /* !defined (KEISATSU) */
	else if ((NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && (SYS_RingCounter == 0 ) ) {
		return 1;
	}
 #endif /* defined (KEISATSU) */
 #endif
#endif

	NCU_RxModeSwitch = CMN_PresentReceiveMode();

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/28 */
	if ( (NCU_ND_Status & (ND_DETECT_CI_AFTER_RX_RES | ND_WAIT_FOR_2ND_RING | ND_COUNTING_2ND_RING)) 
			&& !(NCU_ND_Status & ND_MODEM_DIALIN_DIAL)
			&& (NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY) && (!SYB_DialInNoNumberSignal)) {
		/* モデムダィヤルインで着番号が取れなかったときは TEL1, TEL2 を鳴らす 1998/10/28  */
			return 0;
	}
#endif

	if (( CHK_SilentOperation()                     )
	 || ( CHK_UNI_SilentOperation()                 )	/* By M.Tachibana 1997/12/03 */
	 || ( NCU_RxModeSwitch == SYS_DIAL_IN_READY     )
#if (PRO_NUMBER_DISPLAY == ENABLE) /* changed by H.Kubo 1998/10/15 */
	 || ( NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY     )
#endif
	 || ( NCU_RxModeSwitch == SYS_FAX_TEL_READY     )
/*	 || ( NCU_RxModeSwitch == SYS_FAX_TEL_READY     ))[*/
	 || ((NCU_RxModeSwitch == SYS_TEL_FAX_READY) && !CHK_RingCount())/* L400 着信ベル回数０回（無鳴動）あり By Y.Suzuki 1998/04/03 */
	 || ((NCU_RxModeSwitch == SYS_FAX_READY) && !CHK_RingCount())){/* L400 着信ベル回数０回（無鳴動）あり By Y.Suzuki 1998/03/16 */
		return (1);
	}
	return (0);
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[待機状態時のリレーの初期化]
	function	:[
		1.リレー・モデムの初期化を行なう。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void 	 InitializeRelay( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) ||(PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == ANZU_GBR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	/*-----------------*/
	/**	モデムの初期化 */
	/*-----------------*/
 #if (PRO_MODEM != R288F) /* Edited by H.Kubo 1997/07/23 */
	MDM_ConfigReset();
 #endif /* (PRO_MODEM != R288F) */
 #if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/10/13 */
	StopSendingMelodyToLine(); /* メロディ送出やめ、モデム Tx の線を回線側に接続。 */
 #endif /* (PRO_MODEM == R288F) */

	MDM_FilterStandbyMode();
	/*-----------------*/
	/** リレーの初期化 */
	/*-----------------*/
	AfterCI_TimerSet();
	MonitorSpeakerOff();
 #if defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* (PRO_NCU_TYPE == HINOKI_TYPE) ＴＷＮ仕様にもいれます by H.Hirao 1999/03/25 */ /* HINOKI2 2001/11/13 T.Takagi */
 	/*
 	** wait 100ms for broken buzzer by H.Hirao 
 	*/
 	wai_tsk(10);
 #endif
	CML_RelayOff();
	H_RelayOff();
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/10/20 */
	L_RelayOff();
 #endif /* defined (KEISATSU) */
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
	AnalogSwitchTONE_Set();
 #endif
 #if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
  #if defined (HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
  /* ＨＩＮＯＫＩＴＷＮはＡＮＺＵ＿ＧＢＲ＿ＴＹＰＥのパスを通す。ＴＯＮＥは結線されていないので、
  ** ここで、ＲＸＡにセットします by H.Hirao 1999/01/29
  */
	AnalogSwitchRXA_Set();
  #endif
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/23 */
	/* ND 着信処理を外付け電話で行う場合は、 TEL2 は回線につないでおく。 */
	if (CHK_NumberDisplayByExtPhoneON()) {
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Modify by SMuratec 李 2005/11/01 */
		if (DEBUG_NumberDisplay) {
			CONT_24V_Off();
			if (SYS_LineNDStatus == ND_USED_IN_STD) {
				RelayPortStatus &= ~IO_BIT_L; /* 外付電話を回線に接続し */
				OutputWORD(GA_PGADR, RelayPortStatus);
			}
			else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
				IO__PADRL &= ~IO_BIT_K_L; /* 外付電話を回線に接続し */
			}
		}
		else {
			CONT_24V_Off();
			L_RelayOff();
		}
	}
	else if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_STD) && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && (SYS_RingCounter == 0 ) ) {
		H_RelayOn();
	}
	else if (DEBUG_NumberDisplay && (SYS_LineNDStatus == ND_USED_IN_EXT) && (NCU_ND_Status & ND_SUSPICIOUS_CI_DETECTED) && (SYS_RingCounterExt == 0 ) ) {
		L_RelayOn();
 #else /* !defined (KEISATSU) */
		CONT_24V_Off();
		L_RelayOff();
 #endif /* defined (KEISATSU) */
	}
	else
 #endif
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 PHONE2リレーが標準の場合はLリレーはOFFにします by T.Soneoka 1997/11/21 */
	if ((CHK_UNI_NoRingTel2Detachable())
	&&  (!CHK_Phone2ExtLineOn())) {	/**	PHONE2リレー設定が標準ラインの場合	*/
 #else
	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,02,1995 *//* By M.Tachibana 1997/10/17 */
	if (CHK_UNI_NoRingTel2Detachable()) {
 #endif
		if (SilentReceiveRequest()) {

 #if defined(POPLAR_H) && defined(JP0)
 		/*--------------------------------------------------------------------
 		 * V851 ﾀﾞｲﾔﾙｲﾝ待機、拡張回線で交信中に標準回線に接続されたTEL2で通話
 		 * している場合、交信終了と同時に通話が切断されてしまう。
 		 * なぜかV851固有。By Y.Suzuki 2002/09/12
 		 */
 		if (!CHK_Phone2ExtLineOn() && (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_TEL2_OFF_HOOK)) {/*TEL2標準回線*/
			/*なにもしません。*/
		}
		else{
			L_RelayOn();
		}
 #else
			L_RelayOn();
 #endif
 
 #if (PRO_NORING_TEL1_DETACHABLE == ENABLE)
			H_RelayOn();	/* 無鳴動着信のＴＥＬ１切り離し(For L400) 98/04/01 Add By T.Fukumoto */
 #endif
			CONT_24V_Off(); /** 対策方法変更のため By O.K Jun,07,1995 **/
		}
 #if (0)	/* By M.Tachibana 1997/10/17 */
//		else if (CHK_UNI_RingTel2Detachable()) {
//			L_RelayOn();
//			CONT_24V_Off(); /** 対策方法変更のため By O.K Jun,07,1995 **/
//		}
 #endif
		else {
			L_RelayOff();
			CONT_24V_Off();
		}
	}
	else {
		L_RelayOff();
		CONT_24V_Off();
	}

 #if (PRO_LINENUMBER == TWICE_LINE)
 #if defined (KEISATSU) /* Added by SMuratec 李 2005/07/01 */
 	IsDailing = FALSE;
 	NCU_LineStatus = 0; /* 回線状態値の初期化 */
	if (CHK_LineSetting()) {  /* 回線設定 == 標準回線 */
		ModemRelay_Off();		/**	モデムリレーを標準ライン側に倒します	*/
	}
	else {					/* 回線設定 == 拡張回線 */
		ModemRelay_On();		/**	モデムリレーを拡張ライン側に倒します	*/
	}
	if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
		if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
			NCU_HdstShift();
		}
	}
	/* 警察FAX DVT_ID65 Added by SMuratec 李 2005/12/14 */
	else {
		if (SYS_CalledLineNumber & SYS_STD_LINE_IN_CI) {
			NCU_LineStatus &= ~STD_LINE_STATUS;
			NCU_LineStatus  |=  (STD_LINE_STATUS & STD_CI_IN);
		}
		else if (SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI) {
			NCU_LineStatus &= ~EXT_LINE_STATUS;
			NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_CI_IN);
		}
	}
	
	/* 警察FAX DVT Added by SMuratec 李 2005/12/19 */
	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) {
		NCU_LineStatus &= ~EXT_HDST_OFFHOOK;
		NCU_LineStatus |= STD_HDST_OFFHOOK;	/* 付属電話は標準回線でオフフック */
	}
	else if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK) {
		NCU_LineStatus &= ~STD_HDST_OFFHOOK;
		NCU_LineStatus |= EXT_HDST_OFFHOOK;	/* 付属電話は拡張回線でオフフック */
	}
 #else /* !defined (KEISATSU) */
	/*
	** 疑似２回線仕様
	** PHONE2接続設定にてPHONE2リレーを制御します
	** by T.Soneoka 1997/11/19
	*/
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		PHONE2_RelayOff();		/**	PHONE2リレーを標準ライン側に倒します	*/
	}
	else {	/**	PHONE2リレー設定が拡張ラインの場合	*/
		PHONE2_RelayOn();	/**	PHONE2リレーを拡張ライン側に倒します	*/
	}
	/*
	** 疑似２回線仕様
	** F網接続設定にてMODEMリレーを制御します
	** by T.Soneoka 1997/11/19
	*/
	if (!CHK_UNI_F_NET_ExtLineEnable()) {
		ModemRelay_Off();		/**	モデムリレーを標準ライン側に倒します	*/
	}
	else {
		ModemRelay_On();		/**	モデムリレーを拡張ライン側に倒します	*/
	}
 #endif
 #endif /* defined (KEISATSU) */

 #if (0)	/* By M.Tachibana 1997/10/17 */
//	L_RelayOff();
//	CONT_24V_Off();
 #endif
	S_RelayOff();
 #if (PRO_NCU_TYPE == ANZU_GBR_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE) /* add HINOKI H.Hirao */
	DP_RelayOff();
 #endif
 #if	defined(JPN)
	GenerateRingKeyOff();	/**  By O.K Jun,07,1995 **/
 #else
  #if	defined(SEA) || defined(TUR)
	GenerateRingKeyOff();
  #endif
 #endif

 #if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/02 Eguchi */
	/* ANZU_L InternetFAX仕様。*/

	/*LineをFAX側に接続する */
	SwitchLineToFAX();

	/* TONE検出LOW */
	OnMML_Low();
 #endif

#endif
}

/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[無鳴動着信リレー制御]
	function	:[
		1.Ｈ・Ｌリレーを回線から引き上げ付属・外付電話が鳴動しないようにする。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1993/12/06]
	author		:[坂本直史, 平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	CallingRelayControl( void )
{
/*	RI_On();				'94,07,12			*/
/*	H_RelayOn();								*/

#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/12/07 */
	if (CHK_NumberDisplayByExtPhoneON()) { 						/* 外付け電話による ND 制御か？ */
		if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
			HDST_Disable();	/* ハンドセットを使用禁止にします */
		}
	}
	else {
		H_RelayOn();
	}
	wai_tsk(10);
	CONT_24V_Off();
#else /* !defined (KEISATSU) */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/23 */
	/* ND 着信処理を外付け電話で行う場合は、 TEL2 は回線につないでおく。 */
	if (CHK_NumberDisplayByExtPhoneON() && (NCU_ND_Status & (ND_BEFORE_INFO_RECEIVED))) {
		if( L_RelaySetting()) {
			CONT_24V_Off();
			wai_tsk(10);
			L_RelayOff();
		}
	}
	else
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,01,1995 *//* By M.Tachibana 1997/10/17 */
		if(!( L_RelaySetting())){
			L_RelayOn();
			wai_tsk(10);
			CONT_24V_Off();
		}
	}
#else
 #if (PRO_NORING_TEL1_DETACHABLE == ENABLE)
	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,01,1995 *//* By M.Tachibana 1997/10/17 */
	/* 無鳴動着信のＴＥＬ１切り離し(For L400) 98/04/01 Add By T.Fukumoto */
	if (!(L_RelaySetting()) || !(H_RelaySetting())) {
		if (!(L_RelaySetting())) {
			L_RelayOn();
		}
		if (!(H_RelaySetting())) {
			H_RelayOn();
		}
		wai_tsk(10);
		CONT_24V_Off();
	}
 #else
	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,01,1995 *//* By M.Tachibana 1997/10/17 */
	if(!( L_RelaySetting())){
		L_RelayOn();
		wai_tsk(10);
		CONT_24V_Off();
	}
 #endif
#endif
#endif /* defined (KEISATSU) */
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[鳴動着信リレー制御]
	function	:[
		1.Ｈ・Ｌリレーを回線へ戻し、付属・外付電話が鳴動するようにする。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		CallingRelayControlの反対
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/06/15]
	author		:[平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	ReverseRelayControl(void)
{
/*	RI_Off();						'94,07,12	*/
/*	H_RelayOff();								*/

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,01,1995 *//* By M.Tachibana 1997/10/17 */
		if( L_RelaySetting()){
			CONT_24V_Off();
			wai_tsk(10);
			L_RelayOff();
		}
	}
 #if defined(KEISATSU)
	/* (PRO_CR_RINGING==ENABLE) CR対応 O.Oshima2005/07/20 */
	if (CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (CR_Ringing == OFF)) {
	}
	else {
		if (H_RelaySetting()) {
			CONT_24V_Off();
			wai_tsk(10);
			H_RelayOff();
		}
		if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続 */
			if (Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
				HDST_Enable();
			}
		}
	}

 #endif

#else
 #if (PRO_NORING_TEL1_DETACHABLE == ENABLE)
	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,01,1995 *//* By M.Tachibana 1997/10/17 */
	/* 無鳴動着信のＴＥＬ１切り離し(For L400) 98/04/01 Add By T.Fukumoto */
	if (L_RelaySetting() || H_RelaySetting()) {
		CONT_24V_Off();
		wai_tsk(10);
		if (L_RelaySetting()) {
			L_RelayOff();
		}
		if (H_RelaySetting()) {
			H_RelayOff();
		}
	}
 #else
	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,01,1995 *//* By M.Tachibana 1997/10/17 */
	if( L_RelaySetting()){
		CONT_24V_Off();
		wai_tsk(10);
		L_RelayOff();
	}
 #endif
#endif
}



/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[Ｆ網着信－受信不可の際の回線断リレー制御]
	function	:[
		1.ＣＭＬリレーにて回線を一定時間捕捉後、開放する。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[5sec回線を捕捉 ＯＨ検出等は、この間、働きません。]
	machine		:[V53,RISC]
	language	:[MS-C(Ver.6.0)]
	keyword		:[NCU]
	date		:[1995/11/17]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if defined(JPN)
void					F_Net_DisconnectRelayControl(void)
{
	if(CHK_F_NetSubscriber()){
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		ModemRelay_Off();	/**	モデムリレーOff	*/
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchRXA_Set();
 #endif
		CML_RelayOn();
   		wai_tsk(500);
		CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchTONE_Set();
 #endif
	}
}
#endif


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[秘話機能リレー制御]
	function	:[
		1.付属・外付・ブランチのいずれかがＯＦＦ　ＨＯＯＫされた場合、他の電話機を回線から切り離す。
	]
	return		:[なし]
	common		:[
		NCUStatus　：回線監視モジュールの状態
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void                    TelIndependentRelayControl( void )
{
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
	if (((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_RECEIVE)
		|| ((NCU_LineStatus & STD_LINE_STATUS) == STD_TEL_TRANSMIT)) {
		if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_READY) {
			/* 秘話機能起動しない場合 */
			SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) {
				/* ハンドセット使用中 */
				SYS_LineTelStatus |= STD_USED_IN_HDST;
			}
			else { /* 外付電話使用中 */
				SYS_LineTelStatus |= STD_USED_IN_EXT;
			}
		}
		H_RelayOff();
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@		if (SYS_CalledLineNumber & SYS_STD_LINE_IN_CI) {
@@			if (RingStatus & CI_STD_LINE) {
@@				RingStatus |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_CI_CHECK);
@@			}
@@			else {
@@				RingStatus2nd |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_2ND_CI_CHECK);
@@			}
#else
		if (RingStatus & CI_STD_LINE) {
			RingStatus |= CI_DETECT_TIMEUP;
			det_evt(EVT_CI_CHECK);
#endif
 		}
		else {
			if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
				NCU_HdstShift();
			}
			/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
			if (tskno_DetectCalledTask != 0xFFFF) {
				del_tsk(&tskno_DetectCalledTask);
			}
		}
	}
	/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/30 */
	else if ((CHK_NumberDisplayON() && (SYS_RingCounter == 0) && (RingStatus & CI_STD_LINE))
		|| (NCU_ND_Status &~(ND_WAIT_FOR_CAR_AND_IR))
		|| (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_ND_DISPLAY)) { /* ナンバーディスプレイ起動している場合 */
	}
	else if (((NCU_LineStatus & STD_LINE_STATUS) != STD_COM_IN_USE) 		/* 標準回線は通信中ではない */
			&& ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) ){	/* 標準回線は本体使用中ではない */
		H_RelayOff();
	}
	
	if (((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_RECEIVE)
		|| ((NCU_LineStatus & EXT_LINE_STATUS) == EXT_TEL_TRANSMIT)) {
		if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_READY) {
			/* 秘話機能起動しない場合 */
			SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK) {
				/* ハンドセット使用中 */
				SYS_LineTelStatus |= EXT_USED_IN_HDST;
			}
			else { /* 外付電話使用中 */
				SYS_LineTelStatus |= EXT_USED_IN_EXT;
			}
		}
		L_RelayOff();
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@		if (SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI) {
@@			if (RingStatus & CI_EXT_LINE) {
@@				RingStatus |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_CI_CHECK);
@@			}
@@			else {
@@				RingStatus2nd |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_2ND_CI_CHECK);
@@			}
#else
		if (RingStatus2nd & CI_EXT_LINE) {
			RingStatus2nd |= CI_DETECT_TIMEUP;
			det_evt(EVT_2ND_CI_CHECK);
#endif
		}
		else {
			if ( !(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK)) ) {	/* 付属電話はフフックではない */
				NCU_HdstShift();
			}
			/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
			if (tskno_Detect2ndCalledTask != 0xFFFF) {
				del_tsk(&tskno_Detect2ndCalledTask);
			}
		}
	}
	else if (((NCU_LineStatus & EXT_LINE_STATUS) != EXT_COM_IN_USE) 		/* 標準回線は通信中ではない */
			&& ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) ){	/* 標準回線は本体使用中ではない */
		L_RelayOff();
	}
	
	/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
	if (tskno_DetectCalledTask == 0xFFFF) {
		cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
	}
	if (tskno_Detect2ndCalledTask == 0xFFFF) {
		cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
	}
	if (!(NCUStatus & HOOK_KEY_ON_STATE)) {
		if (!(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK))) {
			NCU_HdstShift();
		}
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) 	/*	通信中ではありません	*/
			&& !IsDailing) {
			CONT_24V_Off();
			wai_tsk(1);
			CML_RelayOff();
		}
	}
	InterRelayTimer();
#else /* !defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
 #if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC  2003/02/13 by T.Soneoka */
		ModemRelay_Off();	/**	モデムリレーOFF	*/
 #endif
		if (NCUStatus & TELEPHONE1_OFF_HOOK) {
			L_RelayOn();
			H_RelayOff();
		}
		if (NCUStatus & TELEPHONE2_OFF_HOOK) {
			if ((0 == SYS_RingCounter)
			|| (CHK_UNI_SecretTelAnsFax())	/* 1998/03/31  By T.Yamaguchi */
			|| (SYS_ANS_FAX_READY != NCU_RxModeSwitch)) {
				H_RelayOn();
			}
			L_RelayOff();
		}
	}
	else {	/**	PHONE2リレー設定が拡張ラインの場合は、PHONE2リレーにて既に秘話になっているため他のTELを切り離すことはしません	*/
 #if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC  2003/02/13 by T.Soneoka */
		ModemRelay_On();	/**	モデムリレーON	*/
 #endif
		if (NCUStatus & TELEPHONE1_OFF_HOOK) {
			H_RelayOff();
		}
		if (NCUStatus & TELEPHONE2_OFF_HOOK) {
			L_RelayOff();
		}
	}
#else
	if( NCUStatus & TELEPHONE1_OFF_HOOK ){
		L_RelayOn();
		H_RelayOff();
	}
	if( NCUStatus & TELEPHONE2_OFF_HOOK ){
		if (( 0 == SYS_RingCounter)
		|| (CHK_UNI_SecretTelAnsFax())	/* 1998/03/31  By T.Yamaguchi */
		|| (SYS_ANS_FAX_READY != NCU_RxModeSwitch)) {
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
			H_RelayOff();
 #else
			H_RelayOn();
 #endif
		}
		L_RelayOff();
	}
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		CONT_24V_Off();
		wai_tsk(1);
		CML_RelayOff();
	}
	else {	/**	PHONE2リレー設定が拡張ラインの場合	*/
		if (!(NCUStatus & HOOK_KEY_ON_STATE)) {
			CONT_24V_Off();
			wai_tsk(1);
			CML_RelayOff();
		}
	}
#else
	CONT_24V_Off();
	wai_tsk(1);
	CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
	AnalogSwitchTONE_Set();
 #endif
#endif
 #if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
	DP_RelayOff();
 #endif
	InterRelayTimer();
#endif /* defined (KEISATSU) */
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[通信状態遷移リレー制御]
	function	:[
		1.多機能電話使用状態から通信状態へ遷移する場合のリレー制御を行う。
		2.キャッチホン対策を行なう。
	]
	return		:[なし]
	common		:[
		0	：再びＯＦＦ　ＨＯＯＫを検出した為、転送受信しない。
		1	：転送受信を行なう。
	]
	condition	:[]
	comment		:[200 + 30 * 50 = 1700 ms  　ＯＨ監視期間（但しＢＲＣは監視せず hook_check_count）
						 2 * 50 =  100 ms    ＯＦＦ　ＨＯＯＫ判定時間(off_hook_count)
				 ]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	TelephoneToFaxcomRelayControl( UBYTE mode, UBYTE (  *mem_sw_read)( void ))
{
	UBYTE	hook_check_count;
	UBYTE	off_hook_count;


	hook_check_count     = 30;
	off_hook_count       =  0;
 #if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
	DP_RelayOn();
	wai_tsk(1);
 #endif

 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 *//* ﾄﾗﾝｼﾞｼｮﾝ対策  EC1の条件を追加 980601 M.H */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
 #else
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
   #if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/04 */
	ModemRelay_Off();		/**	モデムリレーを標準ライン側に倒します	*/
   #else /* 警察FAX DVT_ID44 Modify by SMuratec 李 2005/11/16 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
		ModemRelay_Off();
	}
	else {
		ModemRelay_On();
	}
   #endif /* !defined (KEISATSU) */
  #endif
  #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
	AnalogSwitchRXA_Set();
  #endif
	CML_RelayOn();
	AfterCI_TimerSet();
	MonitorSpeakerOff();
  #if (PRO_MODEM != R288F) /* Edited by H.Kubo 1997/07/23 */
	MDM_ConfigReset();
  #endif /* (PRO_MODEM != R288F) */
 #endif
								/*-------------------------------------*/
	if ( mode == TRNS_RX  ){	/** 転送受信／キャッチ・ホン対応の場合 */
								/*-------------------------------------*/
 #if defined(FRA) || defined(DEU) || defined(EC1) ||defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
		CML_RelayOn();
		AfterCI_TimerSet();
		MonitorSpeakerOff();
  #if (PRO_MODEM != R288F) /* Edited by H.Kubo 1997/07/23 */
		MDM_ConfigReset();
  #endif /* (PRO_MODEM != R288F) */
 #endif
		InterRelayTimer();

		/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Aug,17,1995 *//* By M.Tachibana 1997/10/17 */
		if (CHK_UNI_NoRingTel2Detachable()) {
			CONT_24V_Off();/* 疑似回線電圧０V By Y.Suzuki 1998/05/14 */
		}
		else {
			CONT_24V_On();
		}
#if (0)	/* By M.Tachibana 1997/10/17 */
//		CONT_24V_On();
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			H_RelayOn();
			L_RelayOn();
		}
#else
		H_RelayOn();
		L_RelayOn();
#endif
		wai_tsk(20);
		OhPortStatusRead();

#if (PRO_REMOTE_RX == ENABLE)	/* 1998/01/24  By T.Yamaguchi */
		if ( (( OhPortStatus & TEL2_OFF_HOOK ) && ( NCUStatus & TELEPHONE2_OFF_HOOK ))
		  && (CHK_RemoteRxON()) ) {
			SYS_RingCounter = 0;
						/*---------------*/
			return(1);	/** 転送受信開始 */
						/*---------------*/
		}
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/10 */
		else if ( (( OhPortStatus & TEL1_OFF_HOOK ) && ( NCUStatus & TELEPHONE1_OFF_HOOK ))
		  && (CHK_RemoteRxON()) ) {
			SYS_RingCounterExt = 0;
						/*---------------*/
			return(1);	/** 転送受信開始 */
						/*---------------*/
		}
 #endif /* defined (KEISATSU) */
#elif (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
		if ( (( OhPortStatus & TEL2_OFF_HOOK ) && ( NCUStatus & TELEPHONE2_OFF_HOOK ))
		  && (NCU_RemoteTransferDial()) ) {
			SYS_RingCounter = 0;
			/*---------------
			** 転送受信開始 
			*/
			return(1);
		}
#endif
		if((!(( OhPortStatus & TEL1_OFF_HOOK ) && ( NCUStatus & TELEPHONE1_OFF_HOOK )))
		&& (!(( OhPortStatus & TEL2_OFF_HOOK ) && ( NCUStatus & TELEPHONE2_OFF_HOOK )))){
			while( hook_check_count ){
				if( off_hook_count >= 2 ){
   					CML_RelayOff();
#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
					AnalogSwitchTONE_Set();
#endif
												/*-------------------*/
					if( CHK_CatchPhoneON() ){	/** キャッチホン対応 */
												/*-------------------*/
						HookingRelayControl();
					}
					else{
						SYS_RingCounter = 0;
						wai_tsk(50);
					}
					CONT_24V_Off();
					return(0);
				}
				wai_tsk(5);
				hook_check_count--;
				OhPortStatusRead();
   				if((( OhPortStatus & TEL1_OFF_HOOK ) && ( NCUStatus & TELEPHONE1_OFF_HOOK ))
   				|| (( OhPortStatus & TEL2_OFF_HOOK ) && ( NCUStatus & TELEPHONE2_OFF_HOOK ))){
					off_hook_count++;
				}
			}
			SYS_RingCounter = 0;
										/*---------------*/
			if((*mem_sw_read)()){		/** 転送受信開始 */
										/*---------------*/
				return(1);
			}
			else{
				CONT_24V_Off();
				return(0);
			}
		}
   		else{
			CML_RelayOff();
#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
#endif
										/*-----------------*/
			if( CHK_CatchPhoneON() ){	/** キャチホン対応 */
										/*-----------------*/
				HookingRelayControl();
			}
			else{
				SYS_RingCounter = 0;
				wai_tsk(50);
			}
			CONT_24V_Off();
			return(0);
		}
	}
	else{
		/*-----------------------*/
		/** 手動送受信リレー制御 */
		/*-----------------------*/
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '98/10/01 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
		MonitorSpeakerOff();
 #endif
		InterRelayTimer();
		SYS_RingCounter = 0;
		return(1);
	}
}

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[通信状態遷移リレー制御（疑似２回線でPHONE2リレーが拡張側の場合）]
	function	:[
		1.多機能電話使用状態から通信状態へ遷移する場合のリレー制御を行う。
		2.キャッチホン対策を行なう。
	]
	return		:[なし]
	common		:[
		0	：再びＯＦＦ　ＨＯＯＫを検出した為、転送受信しない。
		1	：転送受信を行なう。
	]
	condition	:[]
	comment		:[200 + 30 * 50 = 1700 ms  　ＯＨ監視期間（但しＢＲＣは監視せず hook_check_count）
						 2 * 50 =  100 ms    ＯＦＦ　ＨＯＯＫ判定時間(off_hook_count)
				 ]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1997/11/29]
	author		:[曽根岡拓]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	TelToFaxRelayControlTel2Ext(UBYTE tel_line)
{
	UBYTE	hook_check_count;
	UBYTE	off_hook_count;
	UBYTE	is_tel_on_hook;

	hook_check_count     = 30;
	off_hook_count       =  0;

	if (tel_line == 1) {
		ModemRelay_Off();		/**	モデムリレーを標準ライン側に倒します	*/
	}
	else {
		ModemRelay_On();		/**	モデムリレーを拡張ライン側に倒します	*/
	}
	CML_RelayOn();
	AfterCI_TimerSet();
	MonitorSpeakerOff();
	InterRelayTimer();

	if (tel_line == 1) {
		if (CHK_UNI_NoRingTel2Detachable()) {
			CONT_24V_Off();
		}
		else {
			CONT_24V_On();
		}
		H_RelayOn();
	}
	else {
		CONT_24V_On();
		L_RelayOn();
	}
	wai_tsk(20);

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 2003/02/14 by T.Soneoka */
	if (((OhPortStatus & TEL2_OFF_HOOK ) && ( NCUStatus & TELEPHONE2_OFF_HOOK ))
	  && (NCU_RemoteTransferDial())) {
		if (tel_line == 1) {
			SYS_RingCounter = 0;
		} else {
			SYS_RingCounterExt = 0;
		}
		/*---------------
		** 転送受信開始 
		*/
		return(1);
	}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/16 */
	else if (((OhPortStatus & TEL1_OFF_HOOK ) && ( NCUStatus & TELEPHONE1_OFF_HOOK ))
	  && (NCU_RemoteTransferDial())) {
		if (tel_line == 1) {
			SYS_RingCounter = 0;
		} else {
			SYS_RingCounterExt = 0;
		}
		/*---------------
		** 転送受信開始 
		*/
		return(1);
	}
#endif /* defined (KEISATSU) */
#endif

	OhPortStatusRead();
	is_tel_on_hook = FALSE;
	if (tel_line == 1) {
		if (!((OhPortStatus & TEL1_OFF_HOOK) && (NCUStatus & TELEPHONE1_OFF_HOOK))) {
			is_tel_on_hook = TRUE;
		}
	}
	else {
		if (!((OhPortStatus & TEL2_OFF_HOOK) && (NCUStatus & TELEPHONE2_OFF_HOOK))) {
			is_tel_on_hook = TRUE;
		}
	}
	if (is_tel_on_hook) {
		while (hook_check_count) {
			if (off_hook_count >= 2) {
   				CML_RelayOff();
				if (CHK_CatchPhoneON()) {
					HookingRelayControlTel2Ext(tel_line);
				}
				else{
					if (tel_line == 1) {
						SYS_RingCounter = 0;
					}
					else {
						SYS_RingCounterExt = 0;
					}
					wai_tsk(50);
				}
				CONT_24V_Off();
				return(0);
			}
			wai_tsk(5);
			hook_check_count--;
			OhPortStatusRead();
			is_tel_on_hook = FALSE;
			if (tel_line == 1) {
				if (!((OhPortStatus & TEL1_OFF_HOOK) && (NCUStatus & TELEPHONE1_OFF_HOOK))) {
					is_tel_on_hook = TRUE;
				}
			}
			else {
				if (!((OhPortStatus & TEL2_OFF_HOOK) && (NCUStatus & TELEPHONE2_OFF_HOOK))) {
					is_tel_on_hook = TRUE;
				}
			}
			if (!is_tel_on_hook) {
				off_hook_count++;
			}
		}
		if (tel_line == 1) {
			SYS_RingCounter = 0;
		}
		else {
			SYS_RingCounter = 0;
		}
		return(1);
	}
	else{
		CML_RelayOff();
		if( CHK_CatchPhoneON() ){
			HookingRelayControlTel2Ext(tel_line);
		}
		else{
			SYS_RingCounter = 0;
			wai_tsk(50);
		}
		CONT_24V_Off();
		return(0);
	}
}
#endif


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[回線捕捉キーＯＮリレー制御]
	function	:[
		1.回線捕捉キーによる回線捕捉状態を実現させる。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	    HookKeyOnRelayControl( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
	if (CHK_LineSetting()) { 			/* 回線設定は標準回線側接 */
		NCU_LineStatus &= ~STD_LINE_STATUS;
		NCU_LineStatus  |=  (STD_LINE_STATUS & STD_IN_USE);
		SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン	*/
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@		if (SYS_CalledLineNumber & SYS_STD_LINE_IN_CI) {
@@			if (RingStatus & CI_STD_LINE) {
@@				RingStatus |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_CI_CHECK);
@@			}
@@			else {
@@				RingStatus2nd |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_2ND_CI_CHECK);
@@			}
#else
		if (RingStatus & CI_STD_LINE) {
			RingStatus |= CI_DETECT_TIMEUP;
			det_evt(EVT_CI_CHECK);
#endif
		}
		/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
		else if (tskno_DetectCalledTask != 0xFFFF) {
			del_tsk(&tskno_DetectCalledTask);
		}
		ModemRelay_Off();		/**	モデムリレーを標準ライン側に倒します	*/
	}
	else { /* ハンドセットは拡張回線側接 */
		NCU_LineStatus &= ~EXT_LINE_STATUS;
		NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_IN_USE);
		SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	拡張ライン	*/
#if 0 /* 警察FAX DVT_ID18&25&26 Modify by SMuratec 李 2005/11/12 */
@@		if (SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI) {
@@			if (RingStatus & CI_EXT_LINE) {
@@				RingStatus |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_CI_CHECK);
@@			}
@@			else {
@@				RingStatus2nd |= CI_DETECT_TIMEUP;
@@				det_evt(EVT_2ND_CI_CHECK);
@@			}
#else
		if (RingStatus2nd & CI_EXT_LINE) {
			RingStatus2nd |= CI_DETECT_TIMEUP;
			det_evt(EVT_2ND_CI_CHECK);
#endif
		}
		else if (tskno_Detect2ndCalledTask != 0xFFFF) {
			del_tsk(&tskno_Detect2ndCalledTask);
		}
		ModemRelay_On();		/**	モデムリレーを拡張ライン側に倒します	*/
	}
	/* 警察FAX DVT_ID18&ID25&ID26 Added by SMuratec 李 2005/11/07 */
	if (tskno_DetectCalledTask == 0xFFFF) {
		cre_tsk(&tskno_DetectCalledTask, TSK_NCU_DETECTCALLEDTASK, &(mbxno.NCU_Task));
	}
	if (tskno_Detect2ndCalledTask == 0xFFFF) {
		cre_tsk(&tskno_Detect2ndCalledTask, TSK_NCU_DETECT_2ND_CALLEDTASK, &(mbxno.NCU_Task));
	}
#endif /* defined (KEISATSU) */

	if(!( CML_RelaySetting())){
 #if (PRO_NCU_TYPE == HINOKI_TYPE)
 	/*
 	** wait 100ms for broken buzzer by H.Hirao 
 	*/
 	wai_tsk(10);
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* || (PRO_NCU_TYPE == SAKAKI_TYPE)*/ /* added by H.Hirao 1998/10/26 & H.Kubo 1998/10/29 */ /* SAKAKI is deleted by H.Kubo 1998/11/11 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchRXA_Set();
 #endif

 #if defined(JPN)	/* RDC200400326 By O.Oshima 2004/09/27 */
	if (!(CML_RelaySetting())) {
		S_RelayOn();
	}
	if (!(CML_RelaySetting())){
		CML_RelayOn();
	}
	if (S_RelaySetting()) {
		wai_tsk(CHK_S_RelayOffTime()/10);
		S_RelayOff();
	}
 #else
		CML_RelayOn();
 #endif

 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
 #if defined (KEISATSU)
 #else /* !defined (KEISATSU) */
		ModemRelay_Off();	/**	モデムリレーOff	*/
 #endif /* defined (KEISATSU) */
 #endif
		InterRelayTimer();
	}

 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		if ((!H_RelaySetting())
		||  (!L_RelaySetting())) {
			H_RelayOn();
			L_RelayOn();
			InterRelayTimer();
		}
	}
	else {	/**	PHONE2リレー設定が拡張ラインの場合、Lリレーは触りません	*/
 #if defined (KEISATSU)
  #if 0 /* 警察FAX DVT_ID21&ID22 Added by SMuratec 李 2005/11/07 */
@@ 		if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
@@			if (!H_RelaySetting()) {	/**	HリレーがOFFの場合	*/
@@				H_RelayOn();	/**	HリレーON	*/
@@				InterRelayTimer();
@@			}
@@ 		}
@@ 		else {						/* モデムリレーを拡張回線に接続している場合 */
@@			if (!L_RelaySetting()) {	/**	LリレーがOFFの場合	*/
@@				L_RelayOn();	/**	LリレーON	*/
@@				InterRelayTimer();
@@			}
@@		}
  #else
 		if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
			if (!H_RelaySetting()) {	/**	標準回線電話リレーがOFFの場合	*/
				H_RelayOn();	/**	標準回線電話リレーON	*/
				InterRelayTimer();
			}
			else if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続している場合 */
				if (!Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
					HDST_Disable();
					InterRelayTimer();
				}
			}
 		}
 		else {						/* モデムリレーを拡張回線に接続している場合 */
			if (!L_RelaySetting()) {	/**	拡張回線電話リレーがOFFの場合	*/
				L_RelayOn();	/**	拡張回線電話リレーON	*/
				InterRelayTimer();
			}
			else if (HDST_RelaySetting()) { /* ハンドセットを拡張回線に接続している場合 */
				if (!Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
					HDST_Disable();
					InterRelayTimer();
				}
			}
		}
  #endif
 #else /* !defined (KEISATSU) */
	if (!H_RelaySetting()) {	/**	HリレーがOFFの場合	*/
		H_RelayOn();	/**	HリレーON	*/
		InterRelayTimer();
	}
 #endif /* defined (KEISATSU) */
	}
 #else
	if((!( H_RelaySetting()))
	|| (!( L_RelaySetting()))){
		H_RelayOn();
		L_RelayOn();
		InterRelayTimer();
	}
 #endif

	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,08,1995 *//* By M.Tachibana 1997/10/17 */
	if (CHK_UNI_NoRingTel2Detachable()) {
		CONT_24V_Off();/*疑似回線電圧０V By Y.Suzuki 1998/05/14*/
	}
	else {
		CONT_24V_On();
	}
 #if (0)	/* By M.Tachibana 1997/10/17 */
//	CONT_24V_On();
 #endif
	MonitorSpeakerOn();
#endif

#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)		/* 1996/07/04-08 By N.Sakamoto */
 #if defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
 	/*
 	** wait 100ms for broken buzzer by H.Hirao 1999/03/25
 	*/
 	wai_tsk(10);
 #endif
	if(!(DP_RelaySetting())){
		DP_RelayOn();
		wai_tsk(1);
	}
  #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/13 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
	S_RelayOn();
	wai_tsk(1);	/* 10ms */
  #endif
	if(!( CML_RelaySetting())){
		CML_RelayOn();
	}
  #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/13 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
	wai_tsk(1);
	S_RelayOff();
  #endif
	if( CHK_UNI_OnHook24V_Available()){
		if((!( H_RelaySetting()))
		|| (!( L_RelaySetting()))){
			wai_tsk(10);
			H_RelayOn();
			L_RelayOn();
			wai_tsk(10);
		}
		CONT_24V_On();
		MonitorSpeakerOn();
	}
	else{
		MonitorSpeakerOn();
		wai_tsk(100);
	}
#endif
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[回線捕捉キーＯＦＦリレー制御]
	function	:[
		1.付属電話のＯＦＦ　ＨＯＯＫにより回線捕捉キーによる回線捕捉から受話器による
		回線捕捉状態へ状態を切り替える。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	HookKeyOffRelayControl( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/25 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		CONT_24V_Off();
		MonitorSpeakerOff();
	}
	else {	/**	PHONE2リレー設定が拡張ラインの場合	*/
		if (!(NCUStatus & HOOK_KEY_ON_STATE)) {
			CONT_24V_Off();
			MonitorSpeakerOff();
		}
	}
 #else
	CONT_24V_Off();
	MonitorSpeakerOff();
 #endif

	TelIndependentRelayControl();

#endif
#if	(PRO_NCU_TYPE == ANZU_GBR_TYPE)
	CONT_24V_Off();
	MonitorSpeakerOff();
	if( NCUStatus & TELEPHONE1_OFF_HOOK ){
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			L_RelayOn();
		}
 #else
		L_RelayOn();
 #endif
		H_RelayOff();
	}
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		if( NCUStatus & TELEPHONE2_OFF_HOOK ){
			if(( 0 == SYS_RingCounter )
			|| ( SYS_ANS_FAX_READY != NCU_RxModeSwitch )){
				H_RelayOn();
			}
			L_RelayOff();
		}
	}
 #else
	if( NCUStatus & TELEPHONE2_OFF_HOOK ){
		if(( 0 == SYS_RingCounter )
		|| ( SYS_ANS_FAX_READY != NCU_RxModeSwitch )){
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
			H_RelayOff();
 #else
			H_RelayOn();
 #endif
		}
		L_RelayOff();
	}
 #endif
	wai_tsk(10);
	CML_RelayOff();
	wai_tsk(1);
	DP_RelayOff();
	wai_tsk(10);
	S_RelayOff();
	
#endif
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[フッキング・リレー制御]
	function	:[
		1.付属電話ＯＦＦ　ＨＯＯＫ状態時、回線捕捉キーによるフッキングを実現させる。
	]
	return		:[なし]
	common		:[
		NCUStatus　：回線監視モジュールの状態
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	HookingRelayControl( void )
{
	UWORD    time;

#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
	UBYTE	LineStatusBk;
	if (!HDST_RelaySetting()) { 			/* ハンドセットは標準回線側接 */
		ModemRelay_Off();		/**	モデムリレーを標準ライン側に倒します	*/
		LineStatusBk = NCU_LineStatus;
		NCU_LineStatus &= ~STD_LINE_STATUS;
		NCU_LineStatus  |=  (STD_LINE_STATUS & STD_IN_USE);
	}
	else { /* ハンドセットは拡張回線側接 */
		ModemRelay_On();		/**	モデムリレーを拡張ライン側に倒します	*/
		LineStatusBk = NCU_LineStatus;
		NCU_LineStatus &= ~EXT_LINE_STATUS;
		NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_IN_USE);
	}
#endif /* defined (KEISATSU) */

	NCUStatus |=  HOOKING_STATE;
	CONT_24V_Off();
	H_RelayOn();
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		L_RelayOn();
	}
#else
	L_RelayOn();
#endif
	time = (UWORD)(CHK_OffhookHookingTime() * 10 );	/* '96,04,15 10ms単位--->100ms単位 NEWMEM By N.S.*/
	if (time) {
		wai_tsk(time);
	}
	if (NCUStatus & TELEPHONE1_OFF_HOOK) {
		H_RelayOff();
	}
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
		if (NCUStatus & TELEPHONE2_OFF_HOOK) {
			L_RelayOff();
		}
	}
#else
	if (NCUStatus & TELEPHONE2_OFF_HOOK) {
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
		H_RelayOff();
 #else
		L_RelayOff();
 #endif
	}
#endif
	InterRelayTimer();
	CML_RelayOff();
#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
	AnalogSwitchTONE_Set();
#endif
	CONT_24V_Off();
	InterRelayTimer();
	NCUStatus &=  ~HOOKING_STATE;
	
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
	NCU_LineStatus = LineStatusBk;
#endif /* defined (KEISATSU) */

}

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/26 */
/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[フッキング・リレー制御]
	function	:[
		1.付属電話ＯＦＦ　ＨＯＯＫ状態時、回線捕捉キーによるフッキングを実現させる。
	]
	return		:[なし]
	common		:[
		NCUStatus　：回線監視モジュールの状態
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	HookingRelayControlTel2Ext(UBYTE tel_line)
{
	UWORD    time;


	NCUStatus |=  HOOKING_STATE;
	CONT_24V_Off();
	if (tel_line == 1) {
		H_RelayOn();
	}
	else {
		L_RelayOn();
	}
	time = (UWORD)(CHK_OffhookHookingTime() * 10 );
	if (time) {
		wai_tsk(time);
	}
	if (tel_line == 1) {
		H_RelayOff();
	}
	else {
		L_RelayOff();
	}
	InterRelayTimer();
	CML_RelayOff();
	CONT_24V_Off();
	InterRelayTimer();
	NCUStatus &=  ~HOOKING_STATE;
}
#endif

/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ＯＮリレー制御]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	ModemOnRelayControl( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
  #if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/04 */
	ModemRelay_Off();	/**	モデムリレーOff	*/
  #endif /* !defined (KEISATSU) */
 #endif
	/*	CONT_24V_On();	*/
	if(!( CML_RelaySetting())){
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchRXA_Set();
 #endif
		CML_RelayOn();
		wai_tsk(1);
	}
#if defined (KEISATSU) /* 警察FAX DVT_ID21&ID22 Modify by SMuratec 李 2005/11/07 */
	if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
		if (!H_RelaySetting()) {	/**	標準回線電話リレーがOFFの場合	*/
			H_RelayOn();	/**	標準回線電話リレーON	*/
			InterRelayTimer();
		}
		else if (!HDST_RelaySetting()) { /* ハンドセットを標準回線に接続している場合 */
			if (!Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
				HDST_Disable();
				InterRelayTimer();
			}
		}
	}
	else {						/* モデムリレーを拡張回線に接続している場合 */
		if (!L_RelaySetting()) {	/**	拡張回線電話リレーがOFFの場合	*/
			L_RelayOn();	/**	拡張回線電話リレーON	*/
			InterRelayTimer();
		}
		else if (HDST_RelaySetting()) { /* ハンドセットを拡張回線に接続している場合 */
			if (!Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
				HDST_Disable();
				InterRelayTimer();
			}
		}
	}
#else /* !define (KEISATSU) */
	if((!( H_RelaySetting()))
	|| (!( L_RelaySetting()))){
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/04 */
		if (!ModemRelaySetting()){/* モデムリレーを標準側接ならば */
			H_RelayOn();
		}
		else { /**	モデムリレーを標準ライン側に倒します	*/
			L_RelayOn();
		}
 #else /* defined (KEISATSU) */
		H_RelayOn();
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
		if (!CHK_Phone2ExtLineOn()) {
			L_RelayOn();
		}
 #else
		L_RelayOn();
 #endif
 #endif /* defined (KEISATSU) */
		InterRelayTimer();
	}
#endif /* defined (KEISATSU) */
 #if (PRO_NCU_TYPE == ANZU_USA_TYPE)	/* By M.Tachibana 1997/12/17 */
	/* POPLAR(JPN)ではCONT24をＯＮしなくてもＯＨを見ることができる
	** ここでＯＮすると、電話を上げてテンキーからダイヤルするとき
	** モーターのノイズが回り込んで受話器から聞こえる
	*/
	CONT_24V_On();
 #endif
#endif
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)		/* 1996/07/15 by H.Yagi */
	if(!( DP_RelaySetting())){
		DP_RelayOn();
		wai_tsk(1);
	}
	if(!( CML_RelaySetting())){
		CML_RelayOn();
		wai_tsk(1);
	}
	if((!( H_RelaySetting()))
	|| (!( L_RelaySetting()))){
		H_RelayOn();
		L_RelayOn();
		InterRelayTimer();
	}
	CONT_24V_On();
#endif
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[保留キーＯＮリレー制御]
	function	:[
		1.オフフック状態から保留状態へ遷移する場合のリレー制御を行う。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	HoldKeyOnRelayControl( void )
{
	MonitorSpeakerOff();
#if defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
 	/* 
 	** オフフック状態で保留キーを入力すると、ＡＣＫブザーが壊れます
 	** リレー制御をＡＣＫブザー鳴動終了後にするためウェイトをいれます by H.Hirao 1999/03/24
 	*/
 	wai_tsk(10);
#endif
	ModemOnRelayControl();
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[保留キーＯＦＦリレー制御]
	function	:[
		1.保留状態から保留キー入力または電話機をＯＮ　ＨＯＯＫからＯＦＦ　ＨＯＯＫに
		することにより多機能電話通常状態へ状態を切り替える。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	HoldKeyOffRelayControl( void )
{
#if (PRO_MODEM != R288F) /* Edited by H.Kubo 1997/07/23 */
	MDM_ConfigReset();
#endif /* (PRO_MODEM != R288F) */
#if defined(HINOKI) || defined(HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)  /* HINOKI2 2001/11/13 T.Takagi */
 	/* 
 	** 保留状態から保留キー入力すると、ＡＣＫブザーが壊れます
 	** リレー制御をＡＣＫブザー鳴動終了後にするためウェイトをいれます by H.Hirao 1999/03/24
 	*/
 	if (SYS_HoldKeyInputFlag && HoldKeyInputFlag) {
	 	wai_tsk(10);
	}
#endif
	TelIndependentRelayControl();
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[シグナル・チェンジ・リレー制御]
	function	:[
		1.シグナル・チェンジを実現させる。
	]
	return		:[なし]
	common		:[
		NCUStatus　：回線監視モジュールの状態
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	SignalChangeRelayControl( void )
{
	if (HOOK_KEY_ON_STATE == ( NCUStatus & HOOK_KEY_ON_STATE )) {
		S_RelayOff();
	}
	else {
		if( TELEPHONE1_OFF_HOOK == ( NCUStatus & TELEPHONE1_OFF_HOOK )){
			H_RelayOff();
		}
		if( TELEPHONE2_OFF_HOOK == ( NCUStatus & TELEPHONE2_OFF_HOOK )){
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
			H_RelayOff();
 #else
			L_RelayOff();
 #endif
		}
		wai_tsk(1);
		CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchTONE_Set();
 #endif
		InterRelayTimer();
		S_RelayOff();
	}
	InterRelayTimer();
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[トーン・ダイヤル開始リレー制御]
	function	:[
		1.トーンにてダイヤルする為の準備を行なう。
	]
	return		:[なし]
	common		:[
		NCUStatus　：回線監視モジュールの状態
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	DTMFDialStartRelayControl( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	if (CHK_TEL_PushToneAvailable()) { 		/** 電話時電話機からPTを聞かせない--->聞かせる設定の場合 1996/05/22 By N.Sakamoto */
		if(!( CML_RelaySetting())){
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
  #if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/04 */
			ModemRelay_Off();	/**	モデムリレーOff	*/
  #endif /* !defined (KEISATSU) */
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchRXA_Set();
 #endif
			CML_RelayOn();
			InterRelayTimer();
		}
	}
	else {
		ModemOnRelayControl();					/** モデムと回線を接続し受話器を回線から切り離すリレー制御（保留と同じ） */
		if(!(NCUStatus & HOOK_KEY_ON_STATE)){
			MonitorSpeakerOn();
		}
	}
#endif
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)							/* 1996/07/04-08 By N.Sakamoto */
	if (CHK_TEL_PushToneAvailable()) { 		/** 電話時電話機からPTを聞かせる設定の場合 1996/05/22 By N.Sakamoto */
		if(!(DP_RelaySetting())){
			DP_RelayOn();
			wai_tsk(1);
		}
		if(!( CML_RelaySetting())){
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
			S_RelayOn();
 #endif
			CML_RelayOn();
			wai_tsk(10);			/* 1996/07/17 by H,Yagi */
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
		S_RelayOff();
 #endif
		}
	}
	else {
		if(!(DP_RelaySetting())){
			DP_RelayOn();
			wai_tsk(1);
		}
		if(!( CML_RelaySetting())){
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
			S_RelayOn();
 #endif
			CML_RelayOn();
			wai_tsk(5);
		}
		if(!(NCUStatus & HOOK_KEY_ON_STATE)){
			MonitorSpeakerOn();
		}
		if((!( H_RelaySetting()))
		|| (!( L_RelaySetting()))){
			H_RelayOn();
			L_RelayOn();
			CONT_24V_On();
			wai_tsk(5);			/* 1996/07/17 by H,Yagi */
		}
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
		S_RelayOff();
 #endif
	}
#endif
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[パルス・ダイヤル開始リレー制御]
	function	:[
		1.パルスにてダイヤルする為の準備を行なう。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史, 平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	DPDialStartRelayControl( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE)
	DP_RelayOn();
	S_RelayOn();
	ModemOnRelayControl();						/** 回線から受話器を切り離すリレー制御 */
#endif
#if (PRO_NCU_TYPE == HINOKI_TYPE)
	DP_RelayOn();
	S_RelayOn();
	ModemOnRelayControl();						/** 回線から受話器を切り離すリレー制御 */
#endif
#if (PRO_NCU_TYPE == SAKAKI_TYPE) /* SAKAKI には DP リレーがありません。 by H.Kubo 1998/07/03 */
	S_RelayOn();
	ModemOnRelayControl();						/** 回線から受話器を切り離すリレー制御 */
#endif
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)			/* 1996/07/11 By H.Yagi */
	if(NCUStatus & HOOK_KEY_ON_STATE){
		if((!( H_RelaySetting()))
		|| (!( L_RelaySetting()))){
			H_RelayOn();
			L_RelayOn();
		}
		CONT_24V_On();
		wai_tsk(1);
		S_RelayOn();
		MonitorSpeakerOff();
	}
	else{
		S_RelayOn();
		DP_RelayOn();
		wai_tsk(1);
		if(!( CML_RelaySetting())){
			CML_RelayOn();
			wai_tsk(1);
		}
		if((!( H_RelaySetting()))
		|| (!( L_RelaySetting()))){
			H_RelayOn();
			L_RelayOn();
		}
		CONT_24V_On();
	}
#endif
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル送出終了処理リレー制御]
	function	:[
		1.ダイヤル送出後、リレーを元の状態に復帰させる。
	]
	return		:[なし]
	common		:[
		NCUStatus　：回線監視モジュールの状態
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	DialEndRelayControl( void )
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	if(NCUStatus & HOOK_KEY_ON_STATE ){
		S_RelayOff();
	}
	else{

 #if defined(POPLAR_F)  || (PRO_NCU_TYPE == HINOKI_TYPE)	/* 2000/03/01 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG *//* NTTファネット(No.102)指摘項目 by O.Kimoto 2002/10/29 */
		MonitorSpeakerOff();
 #else
		if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {		/*ＤＴＭＦ*/
			MonitorSpeakerOff();
		}
 #endif
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/04 */
		if (!ModemRelaySetting()){/* モデムリレーを標準側接ならば */
#if 0 /* 警察FAX DVT_ID68 Modified By SMuratec 李 2005/12/15 */
@@			if( NCUStatus & TELEPHONE1_OFF_HOOK ){
@@				SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
@@				if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) {
@@					/* ハンドセット使用中 */
@@					SYS_LineTelStatus |= STD_USED_IN_HDST;
@@				}
@@				else { /* 外付電話使用中 */
@@					SYS_LineTelStatus |= STD_USED_IN_EXT;
@@				}
@@				H_RelayOff();
@@			}
#else
			if( NCUStatus & TELEPHONE1_OFF_HOOK ){
				if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) == STD_READY) {
					SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
					if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_STD_OFFHOOK) {
						/* ハンドセット使用中 */
						SYS_LineTelStatus |= STD_USED_IN_HDST;
					}
					else { /* 外付電話使用中 */
						SYS_LineTelStatus |= STD_USED_IN_EXT;
					}
				}
				H_RelayOff();
			}
#endif
		}
		else { /**	モデムリレーを標準ライン側に倒します	*/
#if 0 /* 警察FAX DVT_ID68 Modified By SMuratec 李 2005/12/15 */
@@			if( NCUStatus & TELEPHONE2_OFF_HOOK ){
@@				SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
@@				if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK) {
@@					/* ハンドセット使用中 */
@@					SYS_LineTelStatus |= EXT_USED_IN_HDST;
@@				}
@@				else { /* 外付電話使用中 */
@@					SYS_LineTelStatus |= EXT_USED_IN_EXT;
@@				}
@@				L_RelayOff();
@@			}
#else
			if( NCUStatus & TELEPHONE2_OFF_HOOK ){
				if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) == EXT_READY) {
					SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
					if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_HDST_EXT_OFFHOOK) {
						/* ハンドセット使用中 */
						SYS_LineTelStatus |= EXT_USED_IN_HDST;
					}
					else { /* 外付電話使用中 */
						SYS_LineTelStatus |= EXT_USED_IN_EXT;
					}
				}
				L_RelayOff();
			}
#endif
		}
 #else /* defined (KEISATSU) */
		if( NCUStatus & TELEPHONE1_OFF_HOOK ){
			H_RelayOff();
		}
		if( NCUStatus & TELEPHONE2_OFF_HOOK ){
			L_RelayOff();
		}
 #endif /* defined (KEISATSU) */
		wai_tsk(1);
		CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchTONE_Set();
 #endif
		InterRelayTimer();
		S_RelayOff();
 #if (PRO_NCU_TYPE == ANZU_USA_TYPE)
		DP_RelayOff();	/* POPLAR */
 #endif
	}
	InterRelayTimer();
#endif
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)			/* 1996/07/04-08 By N.Sakamoto */
	if(NCUStatus & HOOK_KEY_ON_STATE ){
		S_RelayOff();
		MonitorSpeakerOn();
	}
	else{
		if( NCUStatus & TELEPHONE1_OFF_HOOK ){
			H_RelayOff();
		}
		if( NCUStatus & TELEPHONE2_OFF_HOOK ){
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
			H_RelayOff();
 #else
			L_RelayOff();
 #endif
		}
		CONT_24V_Off();
		wai_tsk(10);
		if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange) {		/*ＤＴＭＦ*/
			MonitorSpeakerOff();
		}
		CML_RelayOff();
		wai_tsk(1);
		DP_RelayOff();
		wai_tsk(10);
		S_RelayOff();
	}
	InterRelayTimer();
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[フラッシュ・キー動作リレー制御]
	function	:[
		1.フラッシュ・キー動作（フッキング）を実現させる。
	]
	return		:[なし]
	common		:[
		FlashStatus
	]
	condition	:[]
	comment		:[]
	machine		:[H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU/ATD/FCM]
	date		:[1994/02/28]
	author		:[原田学]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	Flash_Off_On( UBYTE	 FlashStatus )		/* FlashStatusはコールされた先を見分けるための引数 */
{
#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
	if ( FlashStatus == DIAL_STATUS_AUTODIAL || FlashStatus == DIAL_STATUS_HOOK_KEY ){		/** AUTODIAL時に起動 or FOOKDIAL時に起動 */
		CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchTONE_Set();
 #endif
		if (CHK_UNI_FlashKeyOnOffTime()) {
			wai_tsk((UWORD)CHK_UNI_FlashKeyOnOffTime());
		}
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
  #if !defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/04 */
		ModemRelay_Off();	/**	モデムリレーOff	*/
  #endif /* !defined (KEISATSU) */
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchRXA_Set();
 #endif
		CML_RelayOn();
	}
	else{	/* 1996/07/16 By N.Sakamoto FlashStatus == DIAL_STATUS_OFFHOOK1, FlashStatus == DIAL_STATUS_OFFHOOK2 */
		CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
		AnalogSwitchTONE_Set();
 #endif
		CONT_24V_Off();
		H_RelayOn();
		L_RelayOn();
		if (CHK_UNI_FlashKeyOnOffTime()) {
			wai_tsk((UWORD)CHK_UNI_FlashKeyOnOffTime());
		}
		if (NCUStatus & TELEPHONE1_OFF_HOOK) {
			H_RelayOff();
		}
		if (NCUStatus & TELEPHONE2_OFF_HOOK) {
			L_RelayOff();
		}
		if(((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange)
		&& ( NCUStatus & DIALING_STATE                         )){
			DTMFDialStartRelayControl();
		}
        else{
			InterRelayTimer();
			CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
 #endif
			CONT_24V_Off();
			InterRelayTimer();
		}
	}
#endif

#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)		/* 1996/07/12 by H.Yagi */
	if ( FlashStatus == DIAL_STATUS_AUTODIAL || FlashStatus == DIAL_STATUS_HOOK_KEY ){		/** AUTODIAL時に起動 or FOOKDIAL時に起動 */
		DP_RelayOff();
		if (CHK_UNI_FlashKeyOnOffTime()) {
			wai_tsk((UWORD)CHK_UNI_FlashKeyOnOffTime());
		}
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
		S_RelayOn();
 #endif
		DP_RelayOn();
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
		wai_tsk(1);
		S_RelayOff();
 #endif
	}else if( FlashStatus == DIAL_STATUS_OFFHOOK1 ){	/** TEL1がOFFFOOK時に起動 */
		S_RelayOn();
		DP_RelayOn();
		wai_tsk(1);
		CML_RelayOn();
		wai_tsk(10);
		H_RelayOn();
		CONT_24V_On();
		DP_RelayOff();
		if (CHK_UNI_FlashKeyOnOffTime()) {
			wai_tsk((UWORD)CHK_UNI_FlashKeyOnOffTime());
		}
		DP_RelayOn();
		H_RelayOff();
		CONT_24V_Off();
		wai_tsk(10);
		CML_RelayOff();
		wai_tsk(1);
		DP_RelayOff();
		S_RelayOff();
	}else if( FlashStatus == DIAL_STATUS_OFFHOOK2 ){	/** TEL2がOFFFOOK時に起動 */
		S_RelayOn();
		DP_RelayOn();
		wai_tsk(1);
		CML_RelayOn();
		wai_tsk(10);
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
		H_RelayOn();
 #else
		L_RelayOn();
 #endif
		CONT_24V_On();
		DP_RelayOff();
		if (CHK_UNI_FlashKeyOnOffTime()) {
			wai_tsk((UWORD)CHK_UNI_FlashKeyOnOffTime());
		}
		DP_RelayOn();
 #if (defined(HINOKI2) && defined(TWN)) /* F76 ANS待機必ず着信対策 二次不具合対応 O.Oshima 2004/07/12 */
		H_RelayOff();
 #else
		L_RelayOff();
 #endif
		CONT_24V_Off();
		wai_tsk(10);
		CML_RelayOff();
		wai_tsk(1);
		DP_RelayOff();
		S_RelayOff();
	}
#endif
	InterRelayTimer();
}


#if defined(JPN)
	#if (PRO_DIALIN == ENABLE)
/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン一次応答リレー制御]
	function	:[
		1.ダイヤル・イン待機モードにて着信検出した場合、一次応答（回線閉結）を行なう。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		DialIn1stAnswerRealyControl( void )
{
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	ModemRelay_Off();	/**	モデムリレーOff	*/
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */|| (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 2002/06/25 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
	AnalogSwitchRXA_Set();
 #endif
	CML_RelayOn();
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン内線指定受信完了信号形成／二次応答信号リレー制御]
	function	:[
		1.ダイヤル・イン待機モードにて内線指定信号を受信完了した場合、内線指定完了信号を形成する。
		2.二次応答信号の為のリレー制御を行なう。
	]
	return		:[なし]
	common		:[
		なし
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		DialIn2ndAnswerRelayControl( UBYTE	mode )
{
	UWORD	timer;

	switch( mode ){
		case	DIAL_IN_UNMATCH		:
			timer = 7000/10;
			wai_tsk(timer);
			AfterCI_TimerSet();
			H_RelayOff();
			L_RelayOff();
			CONT_24V_Off();
			timer = 100/10;
			wai_tsk(timer);
			CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
 #endif
			break;

		case	DIAL_IN_STOP		:
			H_RelayOff();
			L_RelayOff();
			CONT_24V_Off();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchRXA_Set();
 #endif
			CML_RelayOn();
			timer = 500/10;
			wai_tsk(timer);
			CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
 #endif
			break;

		case	DIAL_IN_FAX			:
			timer = 400/10;
			wai_tsk(timer);
			CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
 #endif
			timer = 1000/10;
			wai_tsk(timer);
			CONT_24V_Off();
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			ModemRelay_Off();	/**	モデムリレーOff	*/
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchRXA_Set();
 #endif
			CML_RelayOn();
			break;

		case	DIAL_IN_TEL1		:
		case	DIAL_IN_TEL2		:
		case	DIAL_IN_TEL1_TEL2	:
			CONT_24V_On();
			/*-----------------------------------*/
			/** 付属／外付電話排他処理リレー制御 */
			/*-----------------------------------*/
			DialinIndependentRelayControl(mode);
			/*---------------------------------------------------*/
			/** 内線番号信号受信～内線指定受信完了信号の間隔設定 */
			/*---------------------------------------------------*/
			timer = (UWORD)CHK_UNI_DialinPBX_RxSignalTime();
			wai_tsk(timer);
			AfterCI_HL_RelayOn = 1;	/* 1997/06/04 H.Yoshikawa */
			CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
 #endif
			InterRelayTimer();
			S_RelayOn();
			timer = 1000/10;
			wai_tsk(timer);
			AfterCI_HL_RelayOn = 0;	/* 1997/06/04 H.Yoshikawa */
			break;

		case	DIAL_IN_OFF_HOOK		:
			if(!( CHK_UNI_DialInCMLOnAfterOffHook())){
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
				ModemRelay_Off();	/**	モデムリレーOff	*/
 #endif
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
				AnalogSwitchRXA_Set();
 #endif
				CML_RelayOn();
				timer = 500/10;
				wai_tsk(timer);
			}
			break;
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 (ICHOUより) */
		case	DIAL_IN_CLASS1_CALL:
			CML_RelayOff();
			/* TEL1/TEL2とも切り離す *//* H/L Relay On 追加 1998/05/21 s.takeuchi */
			CONT_24V_Off();
			H_RelayOn();
			L_RelayOn();

			/* Dialinでの極反検出に必要 *//* 1998/06/03 s.takeuchi */
			InterRelayTimer();	/* 100ms wait */
			S_RelayOn();

			/* TEL1/TEL2つなぐと極反を誤検知するので追加 *//* 1998/05/22 s.takeuchi */
			timer = 1000/10;
			wai_tsk(timer);
			break;
#endif /* (PRO_CL1_TELFAX_LAN ==ENABLE) */
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/*
		** 原稿蓄積中は、呼び出し中で待たせるので、２次応答はしません added by H.Hirao 1998/12/28 */
		case	DIAL_IN_FAX_FOR_DOC_STORE:
			timer = 400/10;
			wai_tsk(timer);
			CML_RelayOff();
 #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0))/* 2002/09/24 By M.Maeda */
			AnalogSwitchTONE_Set();
 #endif
			timer = 1000/10;
			wai_tsk(timer);
			CONT_24V_Off();
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
			ModemRelay_Off();	/**	モデムリレーOff	*/
 #endif
 			break;
#endif
	}
}


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤルイン独立ベル鳴動リレー制御]
	function	:[

	]
	return		:[なし]
	common		:[なし]
	condition	:[なし]
	comment		:[
		TEL1とTEL2を独立してベル鳴動させます
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/03/25]
	author		:[平岡 徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			DialinIndependentRelayControl(UBYTE	 mode)
{
	if (mode == DIAL_IN_TEL1) {
		CONT_24V_On();
		H_RelayOn();
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			L_RelayOff();	/**	LリレーOFF	*/
		}
#else
		L_RelayOff();
#endif
	}
	else {
		if (mode == DIAL_IN_TEL2) {
			CONT_24V_On();
			H_RelayOff();
			if( CHK_DialInGRSOffLRelayOff()){			/* '94,08,12 By N.S. */
				L_RelayOn();
			}
			else{
				L_RelayOff();							/* '94,08,12 By N.S. */
			}
		}
		else{
			GenerateRingStartRelayControl();
		}
	}												/* '94,07,27 By N.S. */
}
	#endif
#endif


/**+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン，ＴＥＬ／ＦＡＸ，会話予約にて疑似ベル鳴動する場合リレー制御]
	function	:[
		1.ダイヤル・イン（桐・椛の場合（皐の場合は、内線呼出開始リレー制御を用いること））疑似ベル鳴動
		の際のリレー制御を行なう。
		2.ＴＥＬ／ＦＡＸ，会話予約の疑似ベル鳴動のリレー制御を行なう。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			GenerateRingStartRelayControl( void )
{
	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K May,10,1995 *//* By M.Tachibana 1997/10/17 */
	if (CHK_UNI_NoRingTel2Detachable()) {
		CONT_24V_Off();/*疑似回線電圧０V By Y.Suzuki 1998/05/14*/
	}
	else {
		CONT_24V_On();
	}
#if (0)	/* By M.Tachibana 1997/10/17 */
//	CONT_24V_On();
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/21 */
	if ( !ModemRelaySetting() ){	/**	標準ラインに接続された場合	*/
		H_RelayOn();
	}
	else {
		L_RelayOn();
	}
#else /* defined (KEISATSU) */
	H_RelayOn();

#if (PRO_LINENUMBER == TWICE_LINE)
	/*
	** 疑似２回線仕様
	** PHONE2接続設定にてLリレーを制御します
	** PHONE2が拡張ラインの場合はLリレーは設定しません
	** by T.Soneoka 1997/11/19
	*/
	if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2接続設定が標準ラインの場合	*/
		if (CHK_DialInGRSOffLRelayOff()) {
			L_RelayOn();
		}
		else{
			L_RelayOff();
		}
	}
#else
	if( CHK_DialInGRSOffLRelayOff()){
		L_RelayOn();
	}
	else{
		L_RelayOff();
	}
#endif
#endif /* defined (KEISATSU) */
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン，ＴＥＬ／ＦＡＸ，会話予約にて疑似ベル鳴動した場合の後処理のリレー制御]
	function	:[
		1.疑似ベル鳴動後、ＯＦＦ　ＨＯＯＫ／ＣＮＧ検出またはＴｉｍｅＵｐの場合のリレーの後処理を行なう。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			GenerateRingEndRelayControl( void )
{
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/05/18 */
	CONT_24V_Off();
#else
	CONT_24V_On();/*CONT_24V_Off();疑似回線電圧０V By Y.Suzuki 1998/05/14*/
#endif
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ベル鳴動用リンガ・スイッチＯＮ]
	function	:[
		1.リンガに電圧を掛ける。
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			GenerateRingKeyOn( void )
{
#if defined(JPN)
	RI_On();
#endif
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ベル鳴動用リンガ・スイッチＯＦＦ]
	function	:[
		1.リンガから電圧を落とす。
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			GenerateRingKeyOff( void )
{
#if defined(JPN)
    RI_Off();
#endif
}


/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ベル鳴動状態中のベルＯＦＦ期間Ｌリレーを回線側へ戻す]
	function	:[
		1.田村製留守番電話（TA-60）をダイヤル・イン待機モードにて接続した場合、疑似ベル鳴動中に、この疑似ベル
		鳴動をＣＩと誤認識し着信、更に回線側へＬリレーが戻される電圧変動を極性反転と誤認識し回線断する不具合の
		対策の為のリレー制御。
		2.疑似ベル鳴動状態中のＯＦＦ期間に着信する為、この期間、回線に接続し電圧変動をなくす。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void			GenerateRingPreventRelayControl( UWORD mode )
{
	if ((!(CHK_DialInGRSOffLRelayOff()))
	&& (mode != TEL1_RINGING)
#if (PRO_LINENUMBER == TWICE_LINE)
	/*
	** 疑似２回線仕様
	** PHONE2接続設定にてLリレーを制御します
	** by T.Soneoka 1997/11/19
	*/
	&& (!CHK_Phone2ExtLineOn())	/**	PHONE2リレー設定が標準ラインの場合	*/
#endif
	){
		if( L_RelaySetting()){
			L_RelayOff();
		}
		else{
			L_RelayOn();
		}
	}
}

#if (PRO_NUMBER_DISPLAY == ENABLE) /* by H.Kubo 1998/10/13 */
/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CAR のみ待ち状態用にリレーを設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/13]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_ND_CarWaitingRelaySetting(void)
{
	AfterCI_HL_RelayOn = 10; /* CI 見るのを止めさせる */
	if ((NCU_ND_Status & ND_WAIT_FOR_CAR_AND_IR) == ND_WAIT_FOR_CAR) { /* CAR のみ検出 */
		H_RelayOn();
		if (CHK_NumberDisplayByExtPhoneON()) {
			L_RelayOff();
		}
		else {
			L_RelayOn();
		}
	}
	else { /* CAR と IR の両面待ち */
		H_RelayOff();
		L_RelayOff();
	}
}

/**++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ナンバーディスプレイ情報受信後用にリレーを設定]
	function	:[
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1998/10/13]
	author		:[久保博]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void NCU_ND_AfterNdRxRelaySetting(void)
{
	UBYTE h_relay_on;
	UBYTE l_relay_on;
	
	h_relay_on = FALSE;
	l_relay_on = FALSE;




	/* モデムダィヤルイン設定で、着番号が正しくなかった場合。 1998/10/27 */
	NCU_RxModeSwitch = CMN_PresentReceiveMode();
	if ((NCU_RxModeSwitch == SYS_MODEM_DIALIN_READY) && (NCU_ND_Status & ND_COUNTING_2ND_RING)
		 	&& !(NCU_ND_Status & ND_MODEM_DIALIN_DIAL) && (SYB_DialInNoNumberSignal == 0)) {
		h_relay_on = FALSE;
		l_relay_on = FALSE;
		/* H_RelayOff(); */
		/* L_RelayOff(); */
		/* return; */
	}
	else if ((NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) && (NCU_ND_Status & ND_COUNTING_2ND_RING)) {
		/* モデムダィヤルインでメモリーオーバーで着信不可のときの処理 by H.Kubo 1999/02/26 */
 #if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/05/12 added (PRO_CLASS1 == ENABLE) 1999/05/28 */
		if ((CL1_CheckReceiveByFaxOrPC() != NO_RECEIVING_SCANNER_IN_USE)
		 && (CL1_CheckReceiveByFaxOrPC() != NO_RECEIVING_PRINTER_IN_USE)) {
			h_relay_on = FALSE;
			l_relay_on = FALSE;
		}
		else {
			h_relay_on = TRUE;
			l_relay_on = TRUE;
		}
 #else
		h_relay_on = FALSE;
		l_relay_on = FALSE;
 #endif
	}
#if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/23 */
	else if (SYS_LineNDStatus == ND_USED_IN_STD) {
		/* TEL1 の設定 */
		if (SilentReceiveRequest()) {
			h_relay_on = TRUE;
		}
		else {
			h_relay_on = FALSE;
		}
	}
	else if (SYS_LineNDStatus == ND_USED_IN_EXT) {
		/* TEL2 の設定 */
		if (!CHK_NumberDisplayByExtPhoneON() && SilentReceiveRequest()) {
			l_relay_on = TRUE;
		}
		else {
			l_relay_on = FALSE;
		}
	}
#else /* !defined (KEISATSU) */
	else {
		/* TEL1 の設定 */
		if (NCU_ND_Status & ND_MODEM_DIALIN_DIAL) { /* added by H.Kubo 1998/10/26 */
			if (NCU_ND_Status & ND_MODEM_DIALIN_TEL1_DIAL) {
				h_relay_on = FALSE;
				/* H_RelayOff(); */
			}
			else {
			/* if ((NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) || (NCU_ND_Status & ND_MODEM_DIALIN_TEL2_DIAL)) { */
				h_relay_on = TRUE;
				/* H_RelayOn(); */
			}
		}
		else { 	/* モデムダイヤルインでない場合 */
			if (SilentReceiveRequest()) {
				h_relay_on = TRUE;
				/* H_RelayOn(); */
			}
			else {
				h_relay_on = FALSE;
				/* H_RelayOff(); */
			}
		}
	
		/* TEL2 の設定 */
		/* モデムダイヤルイン */
		if (NCU_ND_Status & ND_MODEM_DIALIN_DIAL) { /* added by H.Kubo 1998/10/26 */
			if (NCU_ND_Status & ND_MODEM_DIALIN_TEL2_DIAL) {
				l_relay_on = FALSE;
				/* L_RelayOff(); */
			}
			else {
			/* if ((NCU_ND_Status & ND_MODEM_DIALIN_FAX_DIAL) || (NCU_ND_Status & ND_MODEM_DIALIN_TEL1_DIAL)) { */
				l_relay_on = TRUE;
				/* L_RelayOn(); */
			}
		}
		/* モデムダイヤルインでない場合 */
		else {
			if (!CHK_NumberDisplayByExtPhoneON() && SilentReceiveRequest()) {
				l_relay_on = TRUE;
				/* L_RelayOn(); */
			}
			else {
				l_relay_on = FALSE;
				/* L_RelayOff(); */
			}
		}
	}
#endif /* defined (KEISATSU) */

	/* 実際のリレー制御です。 */
	if ((!l_relay_on  && L_RelaySetting()) || (!h_relay_on && H_RelaySetting())) {
		if (CONT24_Setting()) {
			CONT_24V_Off();
			wai_tsk(10);
		}
		if( !h_relay_on && H_RelaySetting()) {
			H_RelayOff();
		}
		if( !l_relay_on && L_RelaySetting()) {
			L_RelayOff();
		}
		AfterCI_HL_RelayOn = 10; /* CI 見るのを止めさせる */
	}
	if ((l_relay_on  && !L_RelaySetting()) || (h_relay_on && !H_RelaySetting())) {
		if(l_relay_on && !( L_RelaySetting())){
			L_RelayOn();
		}
		if(h_relay_on && !( H_RelaySetting())){
			H_RelayOn();
		}
		AfterCI_HL_RelayOn = 10; /* CI 見るのを 100ms の間やめさせる */
	}
#if defined (KEISATSU) /* 警察FAX DVT_ID21&ID22 Added by SMuratec 李 2005/11/07 */
	if (!HDST_RelaySetting()) { /* ハンドセットを標準回線側接続 */
		if (h_relay_on && !Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
			HDST_Disable();
		}
		if (!h_relay_on && Is_HDST_Disable()) { /* ハンドセットリレーがONの場合 */
			HDST_Enable();
		}
	}
	else { /* ハンドセットを拡張回線側接続 */
		if (l_relay_on && !Is_HDST_Disable()) { /* ハンドセットリレーがOFFの場合 */
			HDST_Disable();
		}
		if (!l_relay_on && Is_HDST_Disable()) { /* ハンドセットリレーがONの場合 */
			HDST_Enable();
		}
	}
#endif /* defined (KEISATSU) */
	if (CHK_NumberDisplayByExtPhoneON() 
		&& (	(NCU_ND_Status & ND_MODEM_DIALIN_TEL1_DIAL) && !(NCU_ND_Status & ND_MODEM_DIALIN_TEL2_DIAL)
			|| !(NCU_ND_Status & ND_MODEM_DIALIN_TEL1_DIAL) && (NCU_ND_Status & ND_MODEM_DIALIN_TEL2_DIAL)
		)) { /* モデムダィヤルインで、TEL1 のみ、もしくは TEL2 のみベル鳴動のときは、*/
#if (PRO_NCU_TYPE == SAKAKI_TYPE) /* changed by H.Kubo 1998/10/29 */
		/* 本来、 CONT_24 をONにしてOH の検出をしますが、 SAKAKI では RI ポート操作の
		** 論理が逆になっているせいで、 CONT_24 を ON にしても電圧がかからず、
		** OH の検出ができません。逆に、 CONT_24 OFF の時は、24V がかかるため、
		** OH の検出はできるようになっています。以上の理由から、不本意ながら、
		** ここでは CONT_24 をOFFにしてOH の検出を待ちます。
		** by H.Kubo 1998/10/29
		*/ 
		if (!NCU_ModemDialinHandsetBehavior()) { /* TEL1 鳴動中に TEL2 で回線をつかめるならば */
			wai_tsk(10);
			CONT_24V_Off();
		}
#else
		if (!NCU_ModemDialinHandsetBehavior()) { /* TEL1 鳴動中に TEL2 で回線をつかめるならば */
			wai_tsk(10);
			CONT_24V_On();
		}
#endif
	}
}
#endif

