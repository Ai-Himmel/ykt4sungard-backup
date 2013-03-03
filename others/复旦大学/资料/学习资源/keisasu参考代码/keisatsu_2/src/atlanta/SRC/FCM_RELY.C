/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCM_RELY.C												 */
/*	モジュール	 :															 */
/*				 : FaxcomRelayControl()										 */
/*				 : FaxComRelaySetting()										 */
/*				 : FaxComUntilRecDISLineON()								 */
/*				 : FaxComUntilRecDISLineOFF()								 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 : ＦＡＸ通信終了時のリレー制御								 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\apl_msg.h"

#include "\src\atlanta\define\ncu_pro.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\stng_pro.h"	/*  Add by T.Soneoka 1997/11/20 */

#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\fcm_def.h"

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\sh7043\define\io_pro.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include 	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
 #endif

CONST unsigned char far SLT_DEBUG = 0;
#endif /* (PRO_MODEM == R288F) */

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if (PRO_DIALIN == ENABLE)
	#include "\src\atlanta\ext_v\bkupram.h"
#endif
#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
#include "\src\atlanta\ext_v\ncu_data.h"
#include "\src\atlanta\define\ncu_stat.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/29 */
#include	"\src\atlanta\define\sys_line.h"
#include	"\src\atlanta\sh7043\define\def_evtn.h"
#endif /* defined (KEISATSU) */

CONST UBYTE RELAY_WAIT_TIME = 10;	/* RDC200400326 -- 特ROMでは15以上にパッチを当てること By O.Kimoto 2004/09/27 */

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[通信開始時のモデム・リレー初期設定]
	function	:[
		1.モデム初期設定
		2.リレー初期設定
	]
	common		:[
		\src\rice\src\NCU_RLY.C から移動 1994/06/14
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立ﾏｲｺﾝ)]
	keyword		:[ATD/FCM/MDM]
	date		:[1993/12/]
	author		:[曽根岡拓／奥村明／村田]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void	FaxcomRelayControlFlsRom(void)
#else
void	FaxcomRelayControl(void)
#endif
{
/*	ﾓﾃﾞﾑ初期設定 */

#if (PRO_MODEM == ORANGE3)
	FilterRXA_Set();
	AnalogSwitchRXA_Set();
#endif
#if (PRO_MODEM == R288F)
	/* POPLAR_H 搭載の R288F のアナログ入力は、モデム基盤上の
	** 外部回路で TONE/RXA を切り替える。
	** H.Kubo 1997/11/12
	*/
	AnalogSwitchRXA_Set();
#endif

#if defined(GBR)
	/* 受信完了アラーム鳴動停止処理追加 1996/08/14 Eguchi */
	if (SYS_AudibleAlarmStatus & 0x02) { /** 受信完了アラーム鳴動中 */
		SYS_AudibleAlarmStatus &= ~0x01; /** 受信完了アラーム鳴動要求クリア */
	}
#endif

#if (PRO_NCU_TYPE == ANZU_GBR_TYPE )	/* 1996/07/08 By N.Sakamoto */
	DP_RelayOn();
	wai_tsk(1);
#endif

#if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
	S_RelayOn();
	wai_tsk(1);		/* 追加　M.H 98/05/06 */
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ラインにて送信時	*/
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/10 */
		SYS_RingCounter		 = 0;
#endif /* defined (KEISATSU) */
		ModemRelay_Off();	/**	モデムリレーOFF	*/
	}
	else {	/**	拡張ラインにて送信時	*/
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/10/10 */
		SYS_RingCounterExt		 = 0;
#endif /* defined (KEISATSU) */
		ModemRelay_On();	/**	モデムリレーON	*/
	}
#endif

#if defined(JPN)	/* RDC200400326 By O.Oshima 2004/09/27 */
	if (FaxComTXorRX_Sign != TX_COM_MODE) {
		if (!(CML_RelaySetting())) {
			S_RelayOn();
		}
	}
#endif

	CML_RelayOn();
	if (CHK_LineMonitor() || CHK_UNI_UntilReceiveDISLineON()) {
		MonitorSpeakerOn();				/* モニタスピーカーＯＮ ＣＭＬと同時にＯＮする様に変更	95.12.07 t.yamaguchi */
	}

#if defined(JPN)	/* RDC200400326 By O.Oshima 2004/09/27 */
	if (FaxComTXorRX_Sign != TX_COM_MODE) {
		if (S_RelaySetting()) {
			wai_tsk(CHK_S_RelayOffTime()/10);
		}
	}
#endif

#if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
#else
	wai_tsk(10);	/* 100ms */
#endif

#if (PRO_NCU_TYPE == ANZU_USA_TYPE ) || (PRO_NCU_TYPE == ANZU_GBR_TYPE )
	H_RelayOn();
	L_RelayOn();			/* ＡＮＺＵのカプラにはＬリレーはない 95.12.07 t.yamaguchi */
 #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
	wai_tsk(1);
 #endif
	S_RelayOff();				/* Add by TH92115 1994/08/29 */
#endif

#if (PRO_NCU_TYPE == POPLAR_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE) || (PRO_NCU_TYPE == HINOKI_TYPE)
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {	/**	標準ラインにて送信時	*/
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			H_RelayOn();	/**	HリレーON	*/
			L_RelayOn();	/**	LリレーON	*/
		}
		else {
			H_RelayOn();	/**	HリレーON	*/
							/**	Lﾘﾚｰ触りません	*/
		}
	}
	else {	/**	拡張ラインにて交信時	*/
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			/**	H、Lﾘﾚｰ触りません	*/
		}
		else {
			/**	Hﾘﾚｰ触りません	*/
			L_RelayOn();	/**	LﾘﾚｰON	*/
		}
	}
 #else
	H_RelayOn();
	L_RelayOn();
 #endif
	S_RelayOff();
	T_RelayOff();
	/* ICHOU変更 送信時、ＴＥＬから聞こえるスキャナモータ音を消すため by T.Soneoka 1997/05/07 */
 #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/05/18 */
	CONT_24V_Off();
 #else
	CONT_24V_On();/*CONT_24V_Off();疑似回線電圧０V By Y.Suzuki 1998/05/14*/
 #endif
 #if defined (HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3)
	/*
	** HINOKI2でメモリ送信時、スキャン終了24VOff→ここで24VOn→メインで24VOff
	** となり、リレーを引く音が３回聞こえてしまう。
	** HINOKI2ではNCUに常時24V供給されているので、ここで24VOnする必要はない
	** 2002/02/05 T.Takagi
	*/
 #else
	PC_24V_On();
 #endif /* end of (defined HINOKI2) */
#endif /* end of (PRO_LINENUMBER == TWICE_LINE) */


#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
	/* test */
if (SLT_DEBUG) {
	UWORD	cnt;
	UWORD	timer;

	cnt = 0;
	timer = SYS_GeneralTimer;
	MDM_SetIO(POS_DTR, OFF);
	MDM_SetIO(POS_DATA, OFF);
	MDM_SetIO(POS_RTH, RTH_LOWEST);
	MDM_SetIO(POS_NEWC, ON);


	while (1) {
		wai_tsk(1);

		if ((UWORD)(SYS_GeneralTimer - timer) > 500) {	/*cast by M.Kotani 97/10/08*/
			break;
		}
		if (MDM_GetIO(POS_FED)) {
			cnt++;
			if (cnt > 10) {
				timer = SYS_GeneralTimer;
				cnt = 0;
			}
		}
		else {
			cnt = 0;
		}
	}
}
/* end test */
#endif /* (PRO_MODEM == R288F) */
}


/*************************************************************************
	module		:[通信終了時のリレー制御]
	function	:[
		1. TEL/FAX待機のOFF_HOOK検出時のリレー制御
		2. 内線通話中のリレー制御
		3. ＴＡＤ遠隔操作設定時のリレー制御
	]
	return		:[]
	common		:[
		AttemptRxModeSwitch		: 待機モード
		FaxComResult			: 通信結果
		SYS_FaxComType			: 通信種別
		ForwardReceiveFlag		: 転送受信
		FaxTelOffHookTEL1Flag	: TEL1 オフフック検出
		FaxTelOffHookTEL2Flag	: TEL2 オフフック検出
		MsgFromFaxComToMain		: メッセージ送信バッファ
		SYS_MACHINE_STATUS_NCU[SYS_MACHINE_STATUS_NCU]	: 内線通話中ステータス
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/03/04]
	author		:[村田]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void	FaxComRelaySettingFlsRom(void)
#else
void	FaxComRelaySetting(void)
#endif
{

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/06 */
	/* パラ接続やめる 保険 */
	MDM_SetModemIdle();		/* モデムをアイドル状態にする */
	/* モデム内部ステータスＬＯＧの取り込みを終了する By O.Kimoto 1996/04/24 */
 #if defined(POPLAR_F)
	wai_tsk(2);		/* 最後のステータスｌｏｇをとるため */
 #endif
	MDM_ModemInternalStatusCounter = MODEM_STATUS_TABLE_MAX;
#endif /* (PRO_MODEM == R288F) */


	/*-------------------*/
	/** リレー関係初期化 */
	/*-------------------*/

	AfterCI_TimerSet();				/* ＣＩ検出用 */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* changed by H.Kubo 1998/10/15 */
	if( (( AttemptRxModeSwitch == SYS_TEL_FAX_READY) 
	    || (AttemptRxModeSwitch == SYS_DIAL_IN_READY )
	    || (AttemptRxModeSwitch == SYS_MODEM_DIALIN_READY )
	)	&& (( FaxTelOffHookTEL1Flag == 1 ) || ( FaxTelOffHookTEL2Flag == 1 ))){		/** OFF_HOOK 検出 */
#else
	if((( AttemptRxModeSwitch == SYS_TEL_FAX_READY) || (AttemptRxModeSwitch == SYS_DIAL_IN_READY ))
	&& (( FaxTelOffHookTEL1Flag == 1 ) || ( FaxTelOffHookTEL2Flag == 1 ))){		/** OFF_HOOK 検出 */
#endif
	/*------------------------------------*/
	/* ＯＦＦ＿ＨＯＯＫ検出時のリレ～制御 */
	/*------------------------------------*/

		if( FaxTelOffHookTEL1Flag == 1 ){	/** ＴＥＬ１ OFF_HOOK */
			H_RelayOff();					/** Ｈリレー OFF */
		}
		if( FaxTelOffHookTEL2Flag == 1 ){	/** ＴＥＬ２ OFF_HOOK */
			L_RelayOff();					/** Ｌリレー OFF */
		}
#if (PRO_NCU_TYPE == ANZU_USA_TYPE ) || (PRO_NCU_TYPE == ANZU_GBR_TYPE )
		wai_tsk(10);						/** add by t.yamaguchi 95.12.07 */
#endif
#if defined(POPLAR_H) && defined(JP0)/*(PRO_MODEM == R288F)/* 通信終了時ｵﾌﾌｯｸで電話が切れるのでCMLﾘﾚｰOFFの前に移動 by O.Kimoto 1999/03/08 */
		/*tel/fax待機時送信後の会話予約に応答するとﾓﾆﾀｽﾋﾟｰｶｰやﾊﾝﾄﾞｾｯﾄからﾉｲｽﾞが出る。By Y.Suzuki 2002/07/20*/
		/*原因わかってない。*/
		MDM_ModemSoftReset();
#endif /* (PRO_MODEM == R288F) */
#if defined(SATSUKI2) || defined(STOCKHM2) /* SATSUKI2も対応します。念のため会話予約の制限を追加します。O.Oshima 2003/10/31 */
		/* tel/fax待機時送信後の会話予約に応答するとﾓﾆﾀｽﾋﾟｰｶｰやﾊﾝﾄﾞｾｯﾄからﾉｲｽﾞが出る。By Y.Suzuki 2002/07/20*/
		/* 原因わかってない。*/
		if (SYS_VoiceCallAccepted) { /* 会話予約に限定するなら==2にするべきかもしれない。*/
			MDM_ModemSoftReset();
		}
#endif
		CML_RelayOff();						/** ＣＭＬリレー OFF */
#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0)) /* SAKAKI2 2002/09/20 By M.Maeda */
		AnalogSwitchTONE_Set();
#endif
		S_RelayOff();					/** Ｓリレー OFF */

#if (PRO_NCU_TYPE == ANZU_USA_TYPE ) || (PRO_NCU_TYPE == ANZU_GBR_TYPE )
		DP_RelayOff();					/** ＤＰリレー OFF */
#endif
		GenerateRingKeyOff();			/** 疑似ベル用 OFF */

#if defined(DEU)
		GroundKeyOff();
#endif

	}
	else if (SYS_VoiceCallAccepted) {	/** 会話予約成立 */
	/*------------------------------------*/
	/* ＯＦＦ＿ＨＯＯＫ検出時のリレ～制御 */
	/*					   1994/09/05	  */
	/*------------------------------------*/

		if( SYS_VoiceCallAccepted == TEL1_OH_DETECT ){	/** ＴＥＬ１ OFF_HOOK */
			H_RelayOff();					/** Ｈリレー OFF */
		}
		if( SYS_VoiceCallAccepted == TEL2_OH_DETECT ){	/** ＴＥＬ２ OFF_HOOK */
#if ( PRO_NCU_TYPE == ANZU_USA_TYPE )	|| ( PRO_NCU_TYPE == ANZU_GBR_TYPE ) /* アンズＵＳＡにはＬリレーが無いのでＨリレーをｏｆｆ */
			H_RelayOff();	/* for SEA & GBR  add by harada '94/10/3  '95.10.31 T.yamaguchi */
			wai_tsk(10);						/* add by t.yamaguchi 95.12.07 */
#else
			L_RelayOff();	/* for SATUKI & KIRI & MOMIJI */
#endif
		}

#if (PRO_MODEM == R288F)	/* 通信終了時ｵﾌﾌｯｸで電話が切れるのでCMLﾘﾚｰOFFの前に移動 by O.Kimoto 1999/03/08 */
		MDM_ModemSoftReset();
#endif /* (PRO_MODEM == R288F) */

		CML_RelayOff();						/** ＣＭＬリレー OFF */

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0)) /* SAKAKI2 2002/09/20 By M.Maeda */
		AnalogSwitchTONE_Set();
#endif
		S_RelayOff();					/** Ｓリレー OFF */

#if ( PRO_NCU_TYPE == ANZU_USA_TYPE )	|| ( PRO_NCU_TYPE == ANZU_GBR_TYPE ) /* アンズＵＳＡにはＬリレーが無いのでＨリレーをｏｆｆ */
		DP_RelayOff();					/** ＤＰリレー OFF */
#endif
		GenerateRingKeyOff();			/** 疑似ベル用 OFF */
#if defined(DEU)
		GroundKeyOff();
#endif

	}
	else{		/** OFF_HOOK なし */
	/*------------------------------------*/
	/* ＯＦＦ＿ＨＯＯＫなし時のリレ～制御 */
	/*------------------------------------*/
	/* 会話予約成立時のＨ、ＬリレーはフェーズＤでやっている */

#if ( PRO_NCU_TYPE == ANZU_GBR_TYPE )
 #if !defined(GBR)		/* 切り替え時の回線瞬断対応 既にGBRは認可通っているためGBR以降の国から対応	1996/09/03 by H.Yagi */
   #if (PRO_DIALUP_INTERNET_FAX == DISABLE)	/* 1998/04/29 by Y.Tanimoto */
		H_RelayOff();					/** Ｈリレー OFF */
		L_RelayOff();					/** Ｌリレー OFF */
   #endif
  #if defined(FRA) || defined(DEU) || defined(EC1) || defined(EUR)	/* by M.HARADA '96/11/14 for transition */
																	/* 欧州仕様追加 by M.H 1999/09/15 */
  #else
		wai_tsk(1);
  #endif
 #endif
#endif
#if ( PRO_NCU_TYPE == ANZU_USA_TYPE )
 #if !defined(USA)		/* 切り替え時の回線瞬断対応 既にUSAは認可通っているためUSA以降の国から対応	1996/09/04 by H.Yagi */
		H_RelayOff();					/** Ｈリレー OFF */
		L_RelayOff();					/** Ｌリレー OFF */
		wai_tsk(1);
 #endif
#endif

#if (0)
** /* アナログスイッチはＣＭＬリレーをＯＦＦしてからトーン側に切りかえること。
** ** by O.Kimoto 1999/03/08
** */
** #if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by H.Hirao 1998/12/25 */
** 		AnalogSwitchTONE_Set();
** #endif
#endif

#if (PRO_MODEM == R288F)	/* 通信終了時ｵﾌﾌｯｸで電話が切れるのでCMLﾘﾚｰOFFの前に移動 1999.1.29 K.Kawata*/
		MDM_ModemSoftReset();		/* モデムリセット 1996/02/24 */
#endif /* (PRO_MODEM == R288F) */


#if defined(JPN)
		/* 花キューピット仕様（交信終了時の受話器上がり検出せず）で、回線とＦＡＸの間にTEL/FAX切り替えアダプターをはさんでいるユーザー先があり
		** CMLを話してからハンドセットを回線に戻すまでに時間がかかってしまい、TEL/FAX切り替えアダプターが回線を話してしまうという不具合（？）が
		** 発生した。。ユーザーさん所では、F340からのリプレースで、F340はOKなのに、F350はNGだといわれていて、調べてみると、リレーの制御がF340とF350
		** とでは違うことがわかった。また、上の方には、CMLリレーを放す前にH/Lリレーを放している場合もあるので、それに見習うようにする。
		** ただし、このあたりは各国PTTに関係するので、とりあえず、JPNという条件を入れておきます。
		** (RDC20010095)
		** By O.Kimoto 2001/02/22
		*/
		if (!CHK_HANGUP_ALARM_AVAILABLE()) {
			H_RelayOff();
			L_RelayOff();
			wai_tsk(10);
		}
#endif

		CML_RelayOff();					/** ＣＭＬリレー OFF */

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
	/*---------------------------------------------------------
	** ﾘﾓｰﾄ受信起動後にTEL2をｵﾌﾌｯｸしておくと通信終了に瞬断して
	** しまうことがある。ﾀｽｸの構成上 NCU_TSK()\InitializeRelay()\H_RelayOff()
	** の処理がおこなわれるまでの時間にばらつきがあるためである。
	** そこで、ここではやくもTEL2を回線に接続する
	*/
		if ((NCUStatus & TRANSFER_RECIVE) 
		&&  (NCUStatus & TELEPHONE2_OFF_HOOK)
		&&  (TADStatus & REMOTE_RECEIVE)){
			L_RelayOff();
		}
#endif

#if (PRO_NCU_TYPE == HINOKI_TYPE) /* added by O.Kimoto 1999/03/08 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/26 */ || (defined(SAKAKI) && defined(JP0)) /* SAKAKI2 2002/09/20 By M.Maeda */
		AnalogSwitchTONE_Set();
#endif

		S_RelayOff();					/** Ｓリレー OFF */
#if ( PRO_NCU_TYPE == ANZU_USA_TYPE )	|| ( PRO_NCU_TYPE == ANZU_GBR_TYPE ) /* アンズＵＳＡにはＬリレーが無いのでＨリレーをｏｆｆ */
		DP_RelayOff();					/** ＤＰリレー OFF */
#endif
		GenerateRingKeyOff();			/** 疑似ベル用 OFF */

#if defined(DEU)
		GroundKeyOff();
#endif
	}
	CONT_24V_Off();		/* add by m.harada 95.06.23 */

#if (0)	/* 通信終了時ｵﾌﾌｯｸで電話が切れるのでCMLﾘﾚｰOFFの前に移動 1999.1.29 K.Kawata*/
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/06 */
	MDM_ModemSoftReset();		/* モデムリセット 1996/02/24 */
#endif /* (PRO_MODEM == R288F) */
#endif

	MDM_FilterStandbyMode();			/** モデム・フィルター初期化 */

	MonitorSpeakerOff();				/** モニター・スピーカーＯＦＦ */

#if defined(POPLAR_H) && defined(JP0)/* V851 ﾓﾆﾀｽﾋﾟｰｶｰから異音 By Y.Suzuki 2002/08/12 */
	AnalogSwitchTONE_Set();
#endif

#if 0 /* 警察FAX DVT_ID2 Deleted by SMuratec 李 2005/11/19 */
@@#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
@@	if ( (NCU_LineStatus & EXT_LINE_STATUS) == EXT_COM_IN_USE ){ 		/* 拡張回線に通信した場合 */
@@		NCU_LineStatus &= ~EXT_LINE_STATUS;
@@		NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
@@	}
@@	else if ( (NCU_LineStatus & STD_LINE_STATUS) == STD_COM_IN_USE ) {	/* 標準回線に通信した場合 */
@@		NCU_LineStatus &= ~STD_LINE_STATUS;
@@		NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
@@	}
@@#endif /* defined (KEISATSU) */
#endif
}

#if 0
/*************************************************************************
	module		:[ＤＩＳ受信まで回線モニタをＯＮする]
	function	:[
		1. 東南アジアのみ
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/06/13]
	author		:[村田]
*************************************************************************/
void	FaxComUntilRecDISLineON(void)
{
	if (CHK_UNI_UntilReceiveDISLineON()) {
		MonitorSpeakerOn();				/** 回線モニタＯＮ */
	}
}
#endif

/*************************************************************************
	module		:[ＤＩＳ受信で回線モニタをＯＦＦする]
	function	:[
		1. 東南アジアのみ
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/06/13]
	author		:[村田]
*************************************************************************/
void	FaxComUntilRecDISLineOFF(void)
{
	if (CHK_UNI_UntilReceiveDISLineON() != 0) {
		if (CHK_LineMonitor() == 0) {
			MonitorSpeakerOff();			/** 回線モニタＯＦＦ */
		}
	}
}



#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
void FaxComQuickTxLineON(void)
{
	/* さらにソフトＳＷでクイック時のモニタＯＮ／ＯＦＦのＳＷ設ける必要有り */
	if (FCM_QuickMemoryTxExecute) {
		MonitorSpeakerOn();				/** 回線モニタＯＮ */
	}
}

void FaxComQuickTxLineOFF(void)
{
	/* さらにソフトＳＷでクイック時のモニタＯＮ／ＯＦＦのＳＷ設ける必要有り */
	if (FCM_QuickMemoryTxExecute) {
		if (CHK_LineMonitor() == 0) {
			MonitorSpeakerOff();			/** 回線モニタＯＦＦ */
		}
	}
}



#endif	/* End of (PRO_QUICK_TX_TEST == ENABLE) */


/*------------------------------------------------------------------------------------*/
/* 通信開始時																		  */
/*				  回線モニタ設定 | ＤＩＳ受信回線モニタ設定 || 回線モニタＯＮ／ＯＦＦ */
/*					   ＯＮ		 |		   ＯＮ				||			ＯＮ		  */
/*					   ＯＮ		 |		   ＯＦＦ			||			ＯＮ		  */
/*					   ＯＦＦ	 |		   ＯＮ				||			ＯＮ		  */
/*					   ＯＦＦ	 |		   ＯＦＦ			||			ＯＦＦ		  */
/*																					  */
/* ＤＩＳ受信時																		  */
/*				  回線モニタ設定 | ＤＩＳ受信回線モニタ設定 || 回線モニタＯＮ／ＯＦＦ */
/*					   ＯＮ		 |		   ＯＮ				||			そのまま	  */
/*					   ＯＮ		 |		   ＯＦＦ			||			そのまま	  */
/*					   ＯＦＦ	 |		   ＯＮ				||			ＯＦＦ		  */
/*					   ＯＦＦ	 |		   ＯＦＦ			||			そのまま	  */
/*------------------------------------------------------------------------------------*/

