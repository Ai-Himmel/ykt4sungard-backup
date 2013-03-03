/**********************************************************************
*	ANZU
*
*	File	Name:	NCU_GRS.C
*	Coded	  by:	坂本直史
*	Module	Name:	GRS_DetectStopKeyInput()
*					GRB_RingAndBellOn()
*					NCU_GenerateRingSignalTask()
*					NCU_GenerateRingSignalExit()
*
*	Note		:	疑似ベル鳴動／ＨＯＯＫ状態変化監視モジュール
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
#include	"\src\atlanta\define\buzzer.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\cmn_def.h" /* 1996/02/22 Eguchi @SYS_SPK_OUT_FAKEBUZZER@ */

#include	"\src\atlanta\define\scn_pro.h" 
#include	"\src\atlanta\define\man_pro.h" 
#include	"\src\atlanta\define\mon_pro.h" 
#include	"\src\memsw\define\mems_pro.h"
#include	"\src\atlanta\define\cmn_pro.h" 
#include	"\src\atlanta\define\uni_pro.h" 
#include	"\src\atlanta\define\ctry_pro.h" 
#include	"\src\atlanta\define\atd_pro.h" 
#include	"\src\atlanta\define\stng_pro.h" 

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

#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\ncu_tbl.h"

#include	"\src\atlanta\sh7043\define\sh_port.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"

static	UBYTE	DetectStopKeyInputFlag = 0;
static	UBYTE	GRS_Tel1OhCounter      = 0;
static	UBYTE	GRS_Tel2OhCounter      = 0;

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
#include	"\src\atlanta\define\sys_line.h"
#endif /* defined (KEISATSU) */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ベル鳴動中の停止キー入力の検出]
	function	:[
		1.疑似ベルを鳴動しオペレーターを呼び出している際に停止キーが押された場合、これを検出する。
	]
	return		:[
		STOP    (0)		: 停止キー入力を検出
		NOT_STOP(1)		: 停止キー入力を検出せず
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	GRS_DetectStopKeyInput( void )
{
	if ((SYS_HookKeyInputFlag   == 1)
	||  (DetectStopKeyInputFlag == 1)) {
		return (STOP);
	}
	else {
		if (NCUStatus & DIALIN_RECEIVE_STATE) {
			if (SYS_TelephoneStopSwitch() == 1) {
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_TELEPHONE;
				DetectStopKeyInputFlag = 1;
				return (STOP);
			}
		}
		else {
			if (SYS_FaxComStopSwitch() == 1) {
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;
				DetectStopKeyInputFlag    = 1;
				return (STOP);
			}
		}
	}
	return (NOT_STOP);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ベル／呼出ブザーＯＮ]
	function	:[
		1.疑似ベル／呼出ブザーのＯＮ期間をつくる
	]
	return		:[
		なし
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void    GRB_RingAndBellOn(void)
{
	/*-------------------------------------------------*/
	/** 疑似ベルＯＦＦ・呼出ブザーＯＮ（１６Ｈｚ変調） */
	/*-------------------------------------------------*/
	/* ICHOUの仕様に合わせる ＪＰＮ仕様のカプラはＦＡＸ側のブザーならさない 1997/09/08  By T.Yamaguchi */
#if (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == ANZU_GBR_TYPE)
	BuzzerOnSetting(SYS_SPK_OUT_FAKERINGER);
 #if defined (HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
	bell_on(); /* by H.Hirao 1999/01/30 */
 #else
	SCN_SetBuzzer(SCN_ENABLE);
 #endif
#endif
	GenerateRingKeyOff();
	wai_tsk(3);

	/*-------------------------------------------------*/
	/** 疑似ベルＯＮ・呼出ブザーＯＦＦ（１６Ｈｚ変調） */
	/*-------------------------------------------------*/
	/*--------------------------*/
	/** 呼出ブザー周波数の設定  */
	/*--------------------------*/
	/* ICHOUの仕様に合わせる ＪＰＮ仕様のカプラはＦＡＸ側のブザーならさない 1997/09/08  By T.Yamaguchi */
#if (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == ANZU_GBR_TYPE)
	SCN_SetBuzzerFrequency(VOICE_ALARM_FREQ);
	BuzzerOffSetting(SYS_SPK_OUT_FAKERINGER);
 #if defined (HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
	bell_off(); /* by H.Hirao 1999/01/30 */
 #else
	SCN_SetBuzzer(SCN_DISABLE);
 #endif
#endif
	GenerateRingKeyOn();
	wai_tsk(3);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似呼出ベル鳴動／ＯＨ状態変化検出タスク]
	function	:[
		1.ダイヤル・イン着信時のオペレータ呼出の為に疑似ベル鳴動及びＯＦＦ　ＨＯＯＫ検出を行なう。
		2.ＴＥＬ／ＦＡＸ着信時のオペレータ呼出の為に疑似ベル鳴動及びＯＦＦ　ＨＯＯＫ検出を行なう。
		3.会話予約時のオペレータ呼出の為に疑似ベル鳴動及びＯＦＦ　ＨＯＯＫ検出を行なう。
		4.内線呼出・保留転送呼出の為に疑似ベル鳴動及び呼出側のＯＮ　ＨＯＯＫ／被呼出側のＯＦＦ　ＨＯＯＫ検出を行なう。
		（回線捕捉キーによる内線呼出の場合、外付電話のＯＦＦ　ＨＯＯＫが検出されても、付属電話がＯＦＦ　ＨＯＯＫされる
		まで本タスクは、存在します。（内線呼出仮成立状態。＊回線捕捉キーによる保留転送は有り得ない。））
		5.1～4の際に上記の動作と共に停止キー入力・回線捕捉キー入力検出を行なう。
	]
	return		:[
		なし
	]
	common		:[
		NCUStatus					:回線監視モジュール動作状態を記憶
		SYS_HookKeyInputFlag		:回線捕捉キー入力情報
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU/FCM]
	date		:[1995/12/27]
	author		:[坂本直史／原田学]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_GenerateRingSignalTask(struct GenerateRingData_t *ring_data )
{
	WORD	tx_mail_box_no;
	WORD	time;
	WORD	counter;
	UWORD	ringing_tel;
	UBYTE 	det_cng_ring_flag;
	UBYTE   delay_ring_flag;


#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/15 */
	UBYTE	Is_HDST_Offhook;
	
	Is_HDST_Offhook = FALSE;

	SYS_MachineStatus[SYS_OTHER_STATUS] |=	SYS_CONT24_LINE_BUSY; /* 擬似鳴動状態になります */
	if ( !ModemRelaySetting() ){	/**	標準ラインに接続された場合	*/
		SYS_CalledLineNumber |= SYS_STD_LINE_IN_CI;
		if ( !(NCU_LineStatus & EXT_HDST_OFFHOOK) && !(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {	/* 付属電話は拡張回線でオフフックではない */
			HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
			/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
			/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
			UpdateLCD();
		}
	}
	else { /**	拡張ラインに接続された場合	*/
		SYS_CalledLineNumber |= SYS_EXT_LINE_IN_CI;
		if ( !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
			HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
			/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
			/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
			UpdateLCD();
		}
	}
#endif /* defined (KEISATSU) */

	TxGenerateRingSignalTaskMsg.Item =	FROM__NCU_SUB;
	tx_mail_box_no					 =	ring_data->SendMBX;
	time							 =	ring_data->StartTime;
	ringing_tel						 =	ring_data->RingingTel;
	RingingType						 =	ringing_tel;
	GRS_Tel1OhCounter				 =	0;
	GRS_Tel2OhCounter				 =	0;
	det_cng_ring_flag				 =	0;
	if (time) {
		delay_ring_flag				 =	1;
	}
	else {
		delay_ring_flag				 =	0;
	}
    DetectStopKeyInputFlag			 =	0;

	/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K Jun,03,1995 *//* By M.Tachibana 1997/10/17 */
	if (!CHK_UNI_NoRingTel2Detachable()) {
		GenerateRingKeyOn();
		wai_tsk( 3 );
	}
#if (0)	/* By M.Tachibana 1997/10/17 */
//	GenerateRingKeyOn();
//	wai_tsk(3);
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/24 By M.Maeda */
	MAN_ChangeEcoMode(0);
#endif

	while ((GRS_Tel1OhCounter          <   GENERAL_RING_OFF_HOOK_MAX)
	&&     (GRS_Tel2OhCounter          <   GENERAL_RING_OFF_HOOK_MAX)
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
	&&  	(SYS_HookKeyInputFlag      == 0							)
#endif /* defined (KEISATSU) */
	&&     (GRS_DetectStopKeyInput()   !=  STOP                     )) {
		/*-----------------------------------*/
		/** 疑似ベル・呼出ブザー ＯＦＦ期間  */
		/*-----------------------------------*/
		counter = 0;
		while ((counter                  <  (15 * time)              )
		&&     (GRS_DetectStopKeyInput() != STOP                     )
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
		&&  	(SYS_HookKeyInputFlag      == 0						)
#endif /* defined (KEISATSU) */
		&&     (GRS_Tel1OhCounter        <  GENERAL_RING_OFF_HOOK_MAX)
		&&     (GRS_Tel2OhCounter        <  GENERAL_RING_OFF_HOOK_MAX)) {
			/*-----------------------------------*/
			/** 付属／外付電話のＯＨ情報の取込み */
			/*-----------------------------------*/
			OhPortStatusRead();
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
			if (!ModemRelaySetting()) {	/**	標準ラインに接続された場合	*/
				if (OffHook1() && !HDST_RelaySetting()){ /* ハンドセットは標準回線でOFFHOOK状態 */
					Is_HDST_Offhook = TRUE;
				}
				else {
					Is_HDST_Offhook = FALSE;
				}
				if ( !(NCU_LineStatus & EXT_HDST_OFFHOOK) && !(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {	/* 付属電話は拡張回線でオフフックではない */
					HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
					/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
					/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
					UpdateLCD();
				}
			}
			else {
				if (OffHook1() && HDST_RelaySetting()){ /* ハンドセットは拡張回線でOFFHOOK状態 */
					Is_HDST_Offhook = TRUE;
				}
				else {
					Is_HDST_Offhook = FALSE;
				}
				if ( !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
					HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
					/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
					/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
					UpdateLCD();
				}
			}
#endif /* defined (KEISATSU) */
											/*--------------------------*/
			if (CHK_600PhoneAvailable()) {	/** 600型 OFF HOOK 検出(1)  */
											/*--------------------------*/
				if ((delay_ring_flag == 1) && (counter >= ((16 * time) / 2))) {
					if (OhPortStatus  & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/19 */
						if ((OhPortStatus & TEL1_OFF_HOOK) && !ModemRelaySetting()) {
#else /* !defined (KEISATSU) */
						if (OhPortStatus & TEL1_OFF_HOOK) {
#endif /* defined (KEISATSU) */
							GRS_Tel1OhCounter = GENERAL_RING_OFF_HOOK_MAX;
							break;												/* '94,08,12 By N.S. */
						}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
						if (OhPortStatus & TEL2_OFF_HOOK && ModemRelaySetting()) {
							GRS_Tel2OhCounter = GENERAL_RING_OFF_HOOK_MAX;
							break;												/* '94,08,12 By N.S. */
						}
#endif /* defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
						if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
							if (OhPortStatus & TEL2_OFF_HOOK) {
								GRS_Tel2OhCounter = GENERAL_RING_OFF_HOOK_MAX;
								break;												/* '94,08,12 By N.S. */
							}
						}
#else
						if (OhPortStatus & TEL2_OFF_HOOK) {
							GRS_Tel2OhCounter = GENERAL_RING_OFF_HOOK_MAX;
							break;												/* '94,08,12 By N.S. */
						}
#endif
					}
				}
			}
			else {
				if (OhPortStatus  & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/19 */
					if ((OhPortStatus & TEL1_OFF_HOOK) && !ModemRelaySetting()) {
#else /* !defined (KEISATSU) */
					if (OhPortStatus & TEL1_OFF_HOOK) {
#endif /* defined (KEISATSU) */
						GRS_Tel1OhCounter++;
					}
					else {
						GRS_Tel1OhCounter = 0;
					}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
					if ((OhPortStatus & TEL2_OFF_HOOK) && ModemRelaySetting()) {
						GRS_Tel2OhCounter++;
					}
					else {
						GRS_Tel2OhCounter = 0;
					}
#endif /* defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
						if (OhPortStatus & TEL2_OFF_HOOK) {
							GRS_Tel2OhCounter++;
						}
						else {
							GRS_Tel2OhCounter = 0;
						}
					}
#else
					if (OhPortStatus & TEL2_OFF_HOOK) {
						GRS_Tel2OhCounter++;
					}
					else {
						GRS_Tel2OhCounter = 0;
					}
#endif
				}
			}
			wai_tsk( 6 );
			counter++;
		}

		if ((CHK_600PhoneAvailable()         )
		&&  (GRS_DetectStopKeyInput() != STOP)		/*--------------------------*/
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
		&&  	(SYS_HookKeyInputFlag      == 0						)
#endif /* defined (KEISATSU) */
		&&  (delay_ring_flag          == 0   )) {	/** 600型 OFF HOOK 検出(2)  */
			/*-----------------------------------*//*--------------------------*/
			/** 付属／外付電話のＯＨ情報の取込み */
			/*-----------------------------------*/
			OhPortStatusRead();
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
			if (!ModemRelaySetting()) {	/**	標準ラインに接続された場合	*/
				if (OffHook1() && !HDST_RelaySetting()){ /* ハンドセットは標準回線でOFFHOOK状態 */
					Is_HDST_Offhook = TRUE;
				}
				else {
					Is_HDST_Offhook = FALSE;
				}
				if ( !(NCU_LineStatus & EXT_HDST_OFFHOOK) && !(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {	/* 付属電話は拡張回線でオフフックではない */
					HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
					/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
					/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
					UpdateLCD();
				}
			}
			else {
				if (OffHook1() && HDST_RelaySetting()){ /* ハンドセットは拡張回線でOFFHOOK状態 */
					Is_HDST_Offhook = TRUE;
				}
				else {
					Is_HDST_Offhook = FALSE;
				}
				if ( !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
					HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
					/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
					/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
					UpdateLCD();
				}
			}
#endif /* defined (KEISATSU) */
			if (OhPortStatus  & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/19 */
				if ((OhPortStatus & TEL1_OFF_HOOK) && !ModemRelaySetting()) {
#else /* !defined (KEISATSU) */
				if (OhPortStatus &  TEL1_OFF_HOOK) {
#endif /* defined (KEISATSU) */
					GRS_Tel1OhCounter = GENERAL_RING_OFF_HOOK_MAX;
					break;												/* '94,08,12 By N.S. */
				}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
				if ((OhPortStatus &  TEL2_OFF_HOOK) && ModemRelaySetting()) {
					GRS_Tel2OhCounter = GENERAL_RING_OFF_HOOK_MAX;
					break;												/* '94,08,12 By N.S. */
				}
#endif /* defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
					if (OhPortStatus &  TEL2_OFF_HOOK) {
						GRS_Tel2OhCounter = GENERAL_RING_OFF_HOOK_MAX;
						break;												/* '94,08,12 By N.S. */
					}
				}
#else
				if (OhPortStatus &  TEL2_OFF_HOOK) {
					GRS_Tel2OhCounter = GENERAL_RING_OFF_HOOK_MAX;
					break;												/* '94,08,12 By N.S. */
				}
#endif
			}
		}
#if defined(FRA)		/* 95/02/20 by M.HARADA */
		time     		= 4;
#else
		time     		= 2;
#endif
		delay_ring_flag	= 0;
		/*------------------------------------*/
		/** ＣＮＧ検出中の疑似ベル鳴動の防止  */
		/*------------------------------------*/
#if ( PRO_DIALIN == ENABLE )
		if (!(NCUStatus &  DIALIN_RECEIVE_STATE)) {
#endif
			while ((GRS_DetectStopKeyInput()  != STOP                     )
			&&     (SYS_RingSignalStopFlag    == 1                        )
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
			&&  	(SYS_HookKeyInputFlag      == 0						)
#endif /* defined (KEISATSU) */
			&&     (GRS_Tel1OhCounter         <  GENERAL_RING_OFF_HOOK_MAX)
			&&     (GRS_Tel2OhCounter         <  GENERAL_RING_OFF_HOOK_MAX)
			&&     (det_cng_ring_flag         == 0                        )) {

				wai_tsk(6);
				if (CHK_600PhoneAvailable()) {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/19 */
					if ((OhPortStatus & TEL1_OFF_HOOK) && !ModemRelaySetting()) {
#else /* !defined (KEISATSU) */
					if (OhPortStatus &  TEL1_OFF_HOOK) {
#endif /* defined (KEISATSU) */
						GRS_Tel1OhCounter++;
					}
					else {
						GRS_Tel1OhCounter = 0;
					}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
					if ((OhPortStatus & TEL2_OFF_HOOK) && ModemRelaySetting()){
						GRS_Tel2OhCounter++;
					}
					else {
						GRS_Tel2OhCounter = 0;
					}
#endif /* defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
						if (OhPortStatus & TEL2_OFF_HOOK){
							GRS_Tel2OhCounter++;
						}
						else {
							GRS_Tel2OhCounter = 0;
						}
					}
#else
					if (OhPortStatus & TEL2_OFF_HOOK){
						GRS_Tel2OhCounter++;
					}
					else {
						GRS_Tel2OhCounter = 0;
					}
#endif
				}
			}
#if ( PRO_DIALIN == ENABLE )
		}
#endif

		/* 無鳴動着信モード時、ＴＥＬ２を回線から切り離す特ＲＯＭ By O.K May,10,1995 *//* By M.Tachibana 1997/10/17 */
		if (det_cng_ring_flag == 0) {
			if (CHK_UNI_NoRingTel2Detachable()) {
				CONT_24V_On();
			}
		}

		det_cng_ring_flag = 1;
		/*--------------------------------*/
		/** 疑似ベル・呼出ブザーＯＮ期間  */
		/*--------------------------------*/
		counter = 0;
		/*----------------------------------------------------*/
		/** 留守番電話誤着信・回線断防止対策（田村TA-60対策） */
		/*----------------------------------------------------*/
		GenerateRingPreventRelayControl(ringing_tel);
		while ((counter                    <  12                       )
		&&     (GRS_DetectStopKeyInput()   != STOP                     )
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
		&&  	(SYS_HookKeyInputFlag      == 0						)
#endif /* defined (KEISATSU) */
		&&     (GRS_Tel1OhCounter          <  GENERAL_RING_OFF_HOOK_MAX)
		&&     (GRS_Tel2OhCounter          <  GENERAL_RING_OFF_HOOK_MAX)) {
			/*-----------------------------------*/
			/** 付属／外付電話のＯＨ情報の取込み */
			/*-----------------------------------*/
			OhPortStatusRead();
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
			if (!ModemRelaySetting()) {	/**	標準ラインに接続された場合	*/
				if (OffHook1() && !HDST_RelaySetting()){ /* ハンドセットは標準回線でOFFHOOK状態 */
					Is_HDST_Offhook = TRUE;
				}
				else {
					Is_HDST_Offhook = FALSE;
				}
				if ( !(NCU_LineStatus & EXT_HDST_OFFHOOK) && !(SYS_CalledLineNumber & SYS_EXT_LINE_IN_CI)) {	/* 付属電話は拡張回線でオフフックではない */
					HDST_RelayOff(); 		/* ハンドセットを標準回線に接続する */
					/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
					/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
					UpdateLCD();
				}
			}
			else {
				if (OffHook1() && HDST_RelaySetting()){ /* ハンドセットは拡張回線でOFFHOOK状態 */
					Is_HDST_Offhook = TRUE;
				}
				else {
					Is_HDST_Offhook = FALSE;
				}
				if ( !(NCU_LineStatus & STD_HDST_OFFHOOK) ) {	/* 付属電話は標準回線でオフフックではない */
					HDST_RelayOn(); 		/* ハンドセットを拡張回線に接続する */
					/* 警察FAX DVT_ID36 Added by SMuratec 夏 2005/11/11 */
					/* 付属電話を呼び出し回線に切換の場合、ＬＣＤで更新します。*/
					UpdateLCD();
				}
			}
#endif /* defined (KEISATSU) */
			if (!(CHK_600PhoneAvailable())) {
				if (OhPortStatus  & (TEL1_OFF_HOOK | TEL2_OFF_HOOK)) {
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/09/19 */
					if ((OhPortStatus & TEL1_OFF_HOOK) && !ModemRelaySetting()) {
#else /* !defined (KEISATSU) */
					if (OhPortStatus & TEL1_OFF_HOOK) {
#endif /* defined (KEISATSU) */
						GRS_Tel1OhCounter++;
					}
					else {
						GRS_Tel1OhCounter = 0;
					}
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
					if ((OhPortStatus & TEL2_OFF_HOOK) && ModemRelaySetting()) {
						GRS_Tel2OhCounter++;
					}
					else {
						GRS_Tel2OhCounter = 0;
					}
#endif /* defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
						if (OhPortStatus &  TEL2_OFF_HOOK) {
							GRS_Tel2OhCounter++;
						}
						else {
							GRS_Tel2OhCounter = 0;
						}
					}
#else
					if (OhPortStatus &  TEL2_OFF_HOOK) {
						GRS_Tel2OhCounter++;
					}
					else {
						GRS_Tel2OhCounter = 0;
					}
#endif
					GRB_RingAndBellOn();
				}
				else {
					/*-----------------------------*/
					/**  疑似ベル・呼出ブザーＯＮ  */
					/*-----------------------------*/
					GRS_Tel1OhCounter   = 0;
					GRS_Tel2OhCounter   = 0;
					GRB_RingAndBellOn();
				}
			}
			else {
				/*-----------------------------*/
				/**  疑似ベル・呼出ブザーＯＮ  */
				/*-----------------------------*/
				GRS_Tel1OhCounter   = 0;
				GRS_Tel2OhCounter   = 0;
				GRB_RingAndBellOn();
			}
#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 *//* Add By O.Kimoto 2002/03/11 */
			IsTelFaxRingSend = 1;		/* 2002/03/05 O.Oshima */
#endif	/* endof (PRO_BT_DET_WHILE_RBT == ENABLE) 2002/02/25 M.Iida */
			counter++;
		}
		/*-----------------------------------------------------*/
		/** 留守番電話誤着信・回線断防止対策（田村TA-60対策）  */
		/*-----------------------------------------------------*/
		GenerateRingPreventRelayControl(ringing_tel);
	}
	/*--------------------*/
	/** 呼出ブザーＯＦＦ  */
	/*--------------------*/
	BuzzerOffSetting(SYS_SPK_OUT_FAKERINGER);
	SCN_SetBuzzer(SCN_DISABLE);
	/*---------------*/
	/** 疑似ベル OFF */
	/*---------------*/
	GenerateRingKeyOff();
	if ((DetectStopKeyInputFlag    == 0)
	&&  (SYS_HookKeyInputFlag      == 0)) {
		if (GRS_Tel1OhCounter >= GENERAL_RING_OFF_HOOK_MAX) {
#if ( PRO_DIALIN == ENABLE )
			if (NCUStatus & DIALIN_RECEIVE_STATE) {
				TxGenerateRingSignalTaskMsg.Message = DETECT_TEL1_OFF_HOOK;
				snd_msg(tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
			}
			else{
#endif
				NCUStatus							&= ~TELEPHONE2_OFF_HOOK;
				NCUStatus						    |= TELEPHONE1_OFF_HOOK;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
				if (Is_HDST_Offhook) {
					NCU_LineStatus &= ~EXT_HDST_OFFHOOK;
					NCU_LineStatus |= STD_HDST_OFFHOOK;	/* 付属電話は標準回線でオフフック */
					SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_HDST_EXT_OFFHOOK;
					SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_HDST_STD_OFFHOOK;
					SYS_LineTelStatus |= STD_USED_IN_HDST;
				}
				else {
					SYS_LineTelStatus |= STD_USED_IN_EXT;
				}
 #if 0 /* 会話予約によって特番機能消去 Deleted By SMuratec 李 2005/10/14 */
**				SYS_RingCounter = 1;
**				if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
**					RingStatus		= RING_STATUS_INITIAL;
**				}
 #endif
#endif /* defined (KEISATSU) */
				TxGenerateRingSignalTaskMsg.Message  = FCOM_TEL1_OFF_HOOK;
				snd_msg(tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
#if ( PRO_DIALIN == ENABLE )
			}
#endif
		}
		else {
			if (GRS_Tel2OhCounter >= GENERAL_RING_OFF_HOOK_MAX) {
#if ( PRO_DIALIN == ENABLE )
				if( NCUStatus & DIALIN_RECEIVE_STATE ){
					TxGenerateRingSignalTaskMsg.Message  = DETECT_TEL2_OFF_HOOK;
					snd_msg( tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
				}
				else {
#endif
					NCUStatus						    &= ~TELEPHONE1_OFF_HOOK;
					NCUStatus							|= TELEPHONE2_OFF_HOOK;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
					if (Is_HDST_Offhook) {
						NCU_LineStatus &= ~STD_HDST_OFFHOOK;
						NCU_LineStatus |= EXT_HDST_OFFHOOK;	/* 付属電話は標準回線でオフフック */
						SYS_MachineStatus[SYS_OTHER_STATUS] &= ~SYS_HDST_STD_OFFHOOK;
						SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_HDST_EXT_OFFHOOK;
						SYS_LineTelStatus |= EXT_USED_IN_HDST;
					}
					else {
						SYS_LineTelStatus |= EXT_USED_IN_EXT;
					}
 #if 0 /* 会話予約によって特番機能消去 Deleted By SMuratec 李 2005/10/14 */
**					SYS_RingCounterExt = 1;
**					if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
**						RingStatus		= RING_STATUS_INITIAL;
**					}
 #endif
#endif /* defined (KEISATSU) */
					TxGenerateRingSignalTaskMsg.Message  = FCOM_TEL2_OFF_HOOK;
					snd_msg( tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
#if ( PRO_DIALIN == ENABLE )
				}
#endif
			}
		}
	}
	else {
		if (!SYS_HookKeyInputFlag) {
#if ( PRO_DIALIN == ENABLE )
			if (NCUStatus & DIALIN_RECEIVE_STATE) {
				TxGenerateRingSignalTaskMsg.Message  = DETECT_INPUT_STOP_KEY;
				snd_msg( tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
			}
			else {
#endif
				TxGenerateRingSignalTaskMsg.Message  = FCOM_STOP_KEY;
				snd_msg( tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
#if ( PRO_DIALIN == ENABLE )
			}
#endif
		}
		else {
#if ( PRO_DIALIN == ENABLE )
			if (NCUStatus & DIALIN_RECEIVE_STATE) {
				TxGenerateRingSignalTaskMsg.Message  = DETECT_INPUT_HOOK_KEY;
				snd_msg( tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
			}
			else {
#endif
				NCUStatus							|= HOOK_KEY_ON_STATE;
				SYS_HookKeyInputFlag	             = 0;
				HookKeyInputFlag	                 = 0;
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/17 */
 #if 0 /* 会話予約によって特番機能消去 Deleted By SMuratec 李 2005/10/14 */
**				if (!ModemRelaySetting()) {	/**	標準ラインに接続された場合	*/
**					SYS_RingCounter = 1;
**				}
**				else {
**					SYS_RingCounterExt = 1;
**				}
**				if (!(SYS_CalledLineNumber & SYS_TWICE_LINE_IN_CI)) {
**					RingStatus		= RING_STATUS_INITIAL;
**				}
 #endif
#endif /* defined (KEISATSU) */
				TxGenerateRingSignalTaskMsg.Message  = FCOM_HOOK_KEY;
				snd_msg( tx_mail_box_no, &TxGenerateRingSignalTaskMsg);
#if ( PRO_DIALIN == ENABLE )
			}
#endif
		}
	}
	wai_tsk(0xFFFF);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似呼出信号鳴動／OFF　HOOK検出タスク強制終了処理ルーチン]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU/FCM]
	date		:[1995/12/27]
	author		:[坂本直史／原田学]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void     NCU_GenerateRingSignalExit(void)
{
	SYS_HookKeyInputFlag = 0;
	HookKeyInputFlag     = 0;
    /*--------------------*/
    /** 呼出ブザーＯＦＦ  */
    /*--------------------*/
	BuzzerOffSetting(SYS_SPK_OUT_FAKERINGER);
	SCN_SetBuzzer(SCN_DISABLE);

	/*---------------*/
	/** 疑似ベル OFF */
	/*---------------*/
	GenerateRingKeyOff();
    exi_tsk();
}
