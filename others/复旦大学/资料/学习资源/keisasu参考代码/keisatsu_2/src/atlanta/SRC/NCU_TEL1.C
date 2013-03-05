/**********************************************************************
*	ANZU
*
*	File   Name:	NCU_TEL1.C
*	Coded	 by:	坂本直史
*	Module Name:	NCU_TelephoneExecuteTask()
*					NCU_TelephoneExecuteExit()
*					TransferReceive()
*					TelephoneDialing()
*					HoldOperation()
*					InternalComOperation()
*					InternalCalling()
*					InternalAndThreePartiesCom()
*
*	Note	   :	多機能電話実行(通常／保留／発信／転送／呼出／内線）
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
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\memsw\define\mems_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\std.h"

#include	"\src\atlanta\define\ncu_pro.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\ncu_msg.h"
#include	"\src\atlanta\define\ncu_ret.h"
#include	"\src\atlanta\define\ncu_cnst.h"
#include	"\src\atlanta\define\ncu_def.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"

#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
#endif /* (PRO_MODEM == ORANGE3)  */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
 #endif
#endif /* (PRO_MODEM == R288F)  */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif


#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"

#if (PRO_PANEL == ANK)
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#endif
#if (PRO_PANEL == KANJI)
#include	"\src\atlanta\opr\kanji\define\opr_def.h"
#endif

/*#if defined(GBR)|| defined(NLD)								@* Flash,Mercury */
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix */	/* Flash,Mercury  By Y.Suzuki 1998/09/18 *//* by K.Watanabe 2004/10/12 */
#include 	"\src\atlanta\define\param.h"
#include 	"\src\atlanta\ext_v\atd_data.h"
#endif
#if (PRO_CLASS1 == ENABLE)/* 96.04.08 */
#include "\src\atlanta\ext_v\cl1_data.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/29 */
#include	"\src\atlanta\define\sys_line.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"

extern UWORD tskno_RemoteRxSignalDetTask;	/* 1998/01/24  By T.Yamaguchi */
UBYTE	LineStatusBk = 0;
#endif /* defined (KEISATSU) */

static	UWORD		tskno_CMN_WatchTimer10msTask	= 0xFFFF;
static	UWORD		tskno_CMN_Watch2Timer10msTask	= 0xFFFF;


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[保留機能実行部位（ＮＣＵ＿ＨＯＬＤ）]
	function	:[
		1.保留状態遷移リレー制御
		2.保留状態リセット・タイマのセット
		3.同タイマＴｉｍｅＵｐの際の保留状態の脱出
		4.保留メロディー送出
		5.保留転送・内線通話（三者通話）の開始・終了処理
	]
	return		:[
		なし
	]
	common		:[
		NCUStatus					:回線監視モジュール動作状態を記憶
		SYS_HoldKeyInputFlag			:保留キー入力情報
		HoldKeyInputFlag				:保留キー入力検出同期フラグ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	HoldOperation( WORD	*tx_mail_box_no )
{
	MESSAGE_t   *RxTelephoneExecuteTaskMsg;
	UBYTE		hold_timer_counter;


	/*-------------------*/
	/** 使用変数の初期化 */
	/*-------------------*/
	TxTelephoneExecuteTaskMsg.Item	= FROM__NCU_TEL;
	NCUStatus				   |= HOLD_STATE;
	hold_timer_counter				= HOLD_TIME_MAX;
	/*-------------------------*/
	/** 保留状態遷移リレー制御 */
	/*-------------------------*/
	HoldKeyOnRelayControl();
	/*-------------*/
	/** 保留音送出 */
	/*-------------*/
	if (CHK_HoldMelodyON()) {
#if (PRO_MODEM == R288F)  /* Edited by H.Kubo 1997/07/23 */
		StartSendingMelodyToLine();
#endif /* (PRO_MODEM == R288F)  */
#if (PRO_MODEM == ORANGE3) /* Edited by H.Kubo 1997/07/23 */
		MDM_MelodyExe();
#endif /* (PRO_MODEM == ORANGE3) */
	}
	/*-------------------------*/
	/** 保留状態タイマーセット */
	/*-------------------------*/
	NCU10msTimer.Time				= 6000;
	NCU10msTimer.SendMBX			= mbxno.NCU_TelephoneExecuteTask;
	NCU10msTimer.ReturnValue		= NOTICE_HOLD_1_SEC_PASS;
	tskno_CMN_WatchTimer10msTask	= 0xFFFF;
	cre_tsk(&tskno_CMN_WatchTimer10msTask, TSK_CMN_MAN_TIMER10MSTASK, &NCU10msTimer);
	/*---------------------------------*/
	/** 保留キー入力同期フラグ・クリア */
	/*---------------------------------*/
	SYS_HoldKeyInputFlag			= 0;
	HoldKeyInputFlag				= 0;
					/*-------------------------------------*/
	while(1){		/** 保留状態が解除されるまで無限ループ */
					/*-------------------------------------*/					/*---------------------------------------------*/
		rcv_msg(mbxno.NCU_TelephoneExecuteTask, &RxTelephoneExecuteTaskMsg);	/** 保留状態における多機能電話の事象の待ち合せ */
																				/*---------------------------------------------*/
														/*-----------------------------------*/
		switch(RxTelephoneExecuteTaskMsg->Message){		/** 受信メッセージに対する処理を行う */
														/*-----------------------------------*/
													/*-------------------------------------*/
			case NOTICE_TEL1_OFF_HOOK		:		/** 付 属 電 話 がOFF HOOKに成った場合 */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/10/13 */
				StopSendingMelodyToLine();
#endif /* (PRO_MODEM == R288F) */
				HoldKeyOffRelayControl();
				return;

			case NOTICE_TEL2_OFF_HOOK		:		/** 外 付 電 話 がOFF HOOKに成った場合 */
													/*-------------------------------------*/
				/*-----------------------------*/
				/** OFF HOOK状態遷移リレー制御 */
				/*-----------------------------*/
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/10/13 */
	#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
					StopSendingMelodyToLine();
				}
				else {/* V851 tel1で保留中にtel2(拡張)ｵﾌﾌｯｸでtel1から保留音が聞こえる By Y.Suzuki 2002/07/25 */
					/*StopSendingMelodyToLine();By Y.Suzuki 2002/08/12 */
					break;/*なにもしない*/
				}
	#else
				StopSendingMelodyToLine();
	#endif
#endif /* (PRO_MODEM == R288F) */
				HoldKeyOffRelayControl();
				return;
													/*---------------------------------*/
			case NOTICE_TEL1_ON_HOOK		:		/** 付属電話が ON HOOKに成った場合 */
													/*---------------------------------*/
				NCUStatus &= ~TELEPHONE1_OFF_HOOK;

				break;

			/*-----------------------------------------------------------
			** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
			*/
													/*---------------------------------*/
			case NOTICE_TEL2_ON_HOOK		:		/** 付属電話が ON HOOKに成った場合 */
													/*---------------------------------*/
				if (CHK_UNI_TEL2_TEL1Action()) {
					NCUStatus &= ~TELEPHONE2_OFF_HOOK;
				}

				break;
												/*-------------------------------------------------------*/
			case NOTICE_HOLD_1_SEC_PASS		:	/** アラーム鳴動・保留状態解除の為のタイマのＴｉｍｅＵｐ */
												/*-------------------------------------------------------*/
				/*---------------------------------*/
				/** 保留自動解除の為の５分タイマー */
				/*---------------------------------*/
				hold_timer_counter--;
				/*-----------------------------*/
				/** 保留状態１分タイマーの停止 */
				/*-----------------------------*/
				if( tskno_CMN_WatchTimer10msTask != 0xFFFF ){
					del_tsk(&tskno_CMN_WatchTimer10msTask);
				}
											/*---------------------------------------------*/
				if( hold_timer_counter ){	/** 保留状態に入ってから５分経過していない場合 */
											/*---------------------------------------------*/
					/*-----------------------------*/
					/** 保留状態１分タイマーセット */
					/*-----------------------------*/
					NCU10msTimer.Time			 = 6000;
					NCU10msTimer.SendMBX		 = mbxno.NCU_TelephoneExecuteTask;
					NCU10msTimer.ReturnValue	 = NOTICE_HOLD_1_SEC_PASS;
					tskno_CMN_WatchTimer10msTask = 0xFFFF;
					cre_tsk(&tskno_CMN_WatchTimer10msTask, TSK_CMN_MAN_TIMER10MSTASK, &NCU10msTimer);
					/*---------------------------------------------------------------------*/
					/** 多機能電話制御タスクへ保留状態に入ってから１分毎のメッセージを送出 */
					/*---------------------------------------------------------------------*/
					TxTelephoneExecuteTaskMsg.Message = DETECT_HOLD_1_SEC_PASS;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					rcv_msg(mbxno.NCU_TelephoneExecuteTask, &RxTelephoneExecuteTaskMsg);
				}
				else{
					/*-------------------------------------------------------------*/
					/** 多機能電話制御タスクへ保留状態がＴｉｍｅＵｐしたことを通知 */
					/*-------------------------------------------------------------*/
					TxTelephoneExecuteTaskMsg.Message = DETECT_HOLD_TIMEUP;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);

					rcv_msg(mbxno.NCU_TelephoneExecuteTask, &RxTelephoneExecuteTaskMsg);

					if( OK_CONT == RxTelephoneExecuteTaskMsg->Message){
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/10/13 */
						StopSendingMelodyToLine();
#endif /* (PRO_MODEM == R288F) */
						HoldKeyOffRelayControl();
					}

					return;
				}

				break;
												/*-------------------------*/
			case NOTICE_INPUT_HOLD_KEY		:	/** 保留キーが押された場合 */
												/*---------------------------------------*/
				/*-----------------------------------------------------------
				** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
				*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
				if ((!CHK_Phone2ExtLineOn()) 	/**	PHONE2リレー設定が標準ラインの場合	*/
				&&  (CHK_UNI_TEL2_TEL1Action())) {
#else
				if (CHK_UNI_TEL2_TEL1Action()) {
#endif
					if( NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK) ){	/** 付属電話がOFF HOOK状態の場合 */
						/*-----------------------------*/	/*-------------------------------*/
						/** OFF HOOK状態遷移リレー制御 */
						/*-----------------------------*/
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/10/13 */
						StopSendingMelodyToLine();
#endif /* (PRO_MODEM == R288F) */
						HoldKeyOffRelayControl();
						SYS_HoldKeyInputFlag	= 0;
						HoldKeyInputFlag		= 0;

						return;
					}
				}
				else {
					if( NCUStatus & TELEPHONE1_OFF_HOOK ){	/** 付属電話がOFF HOOK状態の場合 */
						/*-----------------------------*/	/*-------------------------------*/
						/** OFF HOOK状態遷移リレー制御 */
						/*-----------------------------*/
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/10/13 */
						StopSendingMelodyToLine();
#endif /* (PRO_MODEM == R288F) */
						HoldKeyOffRelayControl();
						SYS_HoldKeyInputFlag	= 0;
						HoldKeyInputFlag		= 0;

						return;
					}
				}
				SYS_HoldKeyInputFlag	= 0;
				HoldKeyInputFlag		= 0;

				break;
			default:

				break;
		}
	}
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル機能実行部位（ＮＣＵ＿ＤＩＡＬ）]
	function	:[
		1.ＦＡＸテンキーよりのダイヤル動作を行なう。
	]
	return		:[
		なし
	]
	common		:[
		SYS_DialingNumber.Buffer[]			:ＦＡＸテンキーより入力されたダイヤル番号がオペレーションにてセットされている
		SYS_DialingNumber.ReadPointer		:ダイヤル・バッファの読み出し開始位置
		SYS_DialingNumber.WritePointer		:ダイヤル・バッファの書き込み済み位置
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	TelephoneDialing( void )
{
	UBYTE	dial_number;
	UBYTE	minus;
	UBYTE	minus_slash;
	UBYTE	dialbuf_wp;
	UBYTE	return_flash_status;
	UBYTE	mercury_param;
/*#if defined(GBR)|| defined(NLD) || defined(AUS) || defined(TWN) || defined(SGP)By Y.Suzuki 1998/09/18 */
#if defined(GBR) || defined(AUS) || defined(TWN) || defined(SGP)
	UWORD		flash_pause;
#endif

	/*-------------------*/
	/** 内部変数の初期化 */
	/*-------------------*/
	NCUStatus	|= DIALING_STATE;
	minus			 = OFF;
	minus_slash		 = OFF;
	PauseDetectFlag	 = 0;

#if defined(GBR)	/* 1996/07/10  by H.Yagi  */
	#if (PRO_MODEM == ORANGE3)
	FilterRXA_Set();
	#endif
#endif
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
 #if !defined (KEISATSU) /* Modified by SMuratec 李 2005/08/03 */
	SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン	*/
 #else
	if (!IsDailing) {
		LineStatusBk = 0;
	}
 #endif /* defined (KEISATSU) */
#endif
								/*-----------------------------------------*/
	if (!(CTRY_OffhookTel())){	/** ＦＡＸテンキーからダイヤルできない場合 */
								/*-----------------------------------------*/
		if ( HOOK_KEY_ON_STATE != ( NCUStatus & HOOK_KEY_ON_STATE )){
			if (SYS_DialingNumber.ReadPointer++ >= SYS_DIRECT_DIAL_MAX){
				SYS_DialingNumber.ReadPointer = 0;
			}
			NCUStatus &= ~DIALING_STATE;
			return;
		}
	}
	
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */
	if (!IsDailing) {
		LineStatusBk = NCU_LineStatus;
		if (HOOK_KEY_ON_STATE != ( NCUStatus & HOOK_KEY_ON_STATE )) {
			if (CHK_LineSetting()) { 			/* 回線設定は標準回線側接 */
				if ((NCU_LineStatus & STD_LINE_STATUS) != STD_IN_USE) {
					NCU_LineStatus &= ~STD_LINE_STATUS;
					NCU_LineStatus |= (STD_LINE_STATUS & STD_IN_USE);
					SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン	*/
				}
			}
			else { /* ハンドセットは拡張回線側接 */
				if ((NCU_LineStatus & EXT_LINE_STATUS) != EXT_IN_USE) {
					NCU_LineStatus &= ~EXT_LINE_STATUS;
					NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_IN_USE);
					SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	拡張ライン	*/
				}
			}
		}
		
		if( tskno_RemoteRxSignalDetTask != 0xFFFF ){
			del_tsk(&tskno_RemoteRxSignalDetTask);
		}
	}

	IsDailing = TRUE;
#endif /* defined (KEISATSU) */

/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18 */
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	if((CHK_PBX())==0 && SYS_DialingNumber.Buffer[0] != '!'){
		MercuryKeyEndFlag = 1;
	}
#endif
#if (PRO_CLASS1 == ENABLE)	/* Add By Y.Tanimoto 96.04.08 */
	CL1_ATD_DialType = 0x00;
#endif
	dialbuf_wp = SYS_DialingNumber.WritePointer;
																/*-------------------------------------------*/
	while ( SYS_DialingNumber.ReadPointer != dialbuf_wp ){		/** 入力されたダイヤル番号が送出し終わるまで */
																/*-------------------------------------------*/
#if defined (KEISATSU)  /* Added by SMuratec 李 2005/06/24 */
		if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
			/* 通信中断していない場合 */
			if (NCUStatus & HOOK_KEY_ON_STATE) {
				SYS_HookKeyInputFlag = TRUE;
			}
			SYS_DialingNumber.ReadPointer = SYS_DialingNumber.WritePointer;
			break;
		}
#endif /* defined (KEISATSU) */
		dial_number =  SYS_DialingNumber.Buffer[SYS_DialingNumber.ReadPointer];
								/*---------------------------------*/
		switch (dial_number){	/** 入力されたキー毎に処理を行なう */
								/*---------------------------------*/
						/*-----------*/
			case '!':	/** ！の場合 */
						/*-------------------------------------------*/
				if (minus){		/** －！の場合（ジグナル・チェンジ） */
								/*-----------------------------------*/
					SYS_DialChange = 1;
					SignalChangeRelayControl();
					PauseDetectFlag	 = 0;
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
					MercuryKeyEnableFlag = 0;
#endif
				}
				else {
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
					/*-----------------------*/
					/** マーキュリーキー動作 */
					/*-----------------------*/
					if((SYS_DialingNumber.ReadPointer == 0)
					&& (SYB_MachineParameter[COUNTRY_CODE] == 0)){
						if(NCUStatus & TELEPHONE1_OFF_HOOK){
							mercury_param = DIAL_STATUS_OFFHOOK1;
						}
						if(NCUStatus & TELEPHONE2_OFF_HOOK){
							mercury_param = DIAL_STATUS_OFFHOOK2;
						}
						if(NCUStatus & HOOK_KEY_ON_STATE){
							mercury_param = DIAL_STATUS_HOOK_KEY;
						}
						MercuryDial(mercury_param);
						MercuryKeyEnableFlag = 0;
						MercuryKeyEndFlag = 1;
					}else{					/* add by M.HARADA 95/10/05 */
						PauseControl();
					}
					PauseDetectFlag	 = 0;
#else				/*-------------*/
					/** ポーズ動作 */
					/*-------------*/
					PauseControl();
#endif
				}
				minus		= OFF;
				minus_slash	= OFF;

				break;
						/*-----------*/
			case '/':	/** ／の場合 */
						/*-----------------------------------*/
				if (minus){		/** －／の場合（ポーズ動作） */
								/*---------------------------*/
/*#if defined(NOR) || defined(DEU)				@* 1995/05/10  by M.HARADA */
#if defined(DEU)				/* By Y.Suzuki 1998/09/18 */
					if (CHK_UNI_GroundkeyCheck()){		/* TEL1がない場合の制御 */
						GroundKeyOn();	/** ｸﾞﾗﾝﾄﾞｷｰ･ﾘﾚｰを引く */
						wai_tsk(30);	/** 300ms 待つ */
						GroundKeyOff();	/** ｸﾞﾗﾝﾄﾞｷｰ･ﾘﾚｰを開放 */
						wai_tsk(10);	/* 連続入力されたときにｸﾞﾗﾝﾄﾞ動作がくっついてしまうのでｳｴｲﾄ100msを追加
											by M.Harada　1999/12/16 */
					}
#else
					PauseControl();
#endif
					minus_slash = ON;
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
					MercuryKeyEnableFlag = 0;
#endif
				}
				else {
					if(CHK_UNI_FlashkeyCheck()){ /* CHK_FlashKeyCheck->CHK_UNI_FlashKeyCheck 1996/04/16 Eguchi */
					/*--------------------*/
						/* フラッシュキー動作 */
						/*--------------------*/
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
/*#if defined(GBR) || defined(NLD) || defined(AUS) || defined(TWN) || defined(SGP)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(AUS) || defined(TWN) || defined(SGP)
						flash_pause = 30;		/* FulashKey動作後のポーズ時間 300ms */
						wai_tsk(flash_pause);
#endif
						MercuryKeyEnableFlag = 1;
						PauseDetectFlag	 = 0;
					}
					else{
						/** ポーズ動作 */
						/*-------------*/
						PauseControl();
					}
					minus_slash = OFF;
				}
				minus = OFF;

				break;
						/*-----------*/
			case '-':	/** －の場合 */
						/*-----------*/
				minus = ON;
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
				MercuryKeyEnableFlag = 0;
#endif
				break;
						/*-----------------------*/
			default:	/** ダイヤル・キーの場合 */
						/*-----------------------*/							/*-----------------------------------------*/
#if defined (KEISATSU) /* Added by SMuratec 李 2005/08/30 */
				if (!CHK_LineSetting()) { 			/* 回線設定は拡張回線側接 */
					if ((CHK_DialTypeExt() & LINE_TYPE_TONE_EXT) || SYS_DialChange){	/** トーン設定又はシグナル・チェンジの場合 */
																				/*-----------------------------------------*/
						DTMFDialStartRelayControl();
						if(('0' <= dial_number ) && ( dial_number <= '9')){
							OutPutDial((UBYTE)(dial_number & 0x0f));
						}
						if((dial_number == '*') || (dial_number == '#')){
							OutPutDial(dial_number);
						}
					}
					else{	/*-------------------*/
							/** パルス設定の場合 */
							/*-------------------*/
						if(('0' <= dial_number ) && ( dial_number <= '9')){
							DPDialStartRelayControl();
							OutPutDial((UBYTE)(dial_number & 0x0f));
						}
					}
				}
				else 
#endif /* defined (KEISATSU) */
				if ((CHK_DialType() & LINE_TYPE_TONE) || SYS_DialChange){	/** トーン設定又はシグナル・チェンジの場合 */
																			/*-----------------------------------------*/

					DTMFDialStartRelayControl();
					if(('0' <= dial_number ) && ( dial_number <= '9')){
						OutPutDial((UBYTE)(dial_number & 0x0f));
					}
					if((dial_number == '*') || (dial_number == '#')){
						OutPutDial(dial_number);
					}
#if defined(SATSUKI2) || defined(STOCKHM2) /* TELから本体テンキー発呼した時、一瞬本体からトーン以外の音が聞こえる件。従来機同様。O.Oshima 2003/10/30 */
					if(!(NCUStatus & HOOK_KEY_ON_STATE)){
						SpeakerMuteOn();
					}
#endif
				}
				else{	/*-------------------*/
						/** パルス設定の場合 */
						/*-------------------*/
					if(('0' <= dial_number ) && ( dial_number <= '9')){
						DPDialStartRelayControl();
						OutPutDial((UBYTE)(dial_number & 0x0f));
					}
				}
				minus		= OFF;
				minus_slash	= OFF;
				PauseDetectFlag	 = 0;
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
				MercuryKeyEnableFlag = 0;
#endif
		}
		/*---------------------*/
		/** ダイヤル桁間の処理 */
		/*---------------------*/
#if defined (KEISATSU) /* ID22 O.Oshima 2005/11/07 */
		if (++SYS_DialingNumber.ReadPointer >= DIALING_NUMBER_MAX ) {
#else
		if (SYS_DialingNumber.ReadPointer++ >= DIALING_NUMBER_MAX ) {
#endif
			SYS_DialingNumber.ReadPointer = 0;
		}
#if defined(EC1)	/* ITA仕様 */
		if((dial_number=='-' && SYS_DialingNumber.Buffer[SYS_DialingNumber.ReadPointer]=='!') && (SYB_MachineParameter[0]==2)){
			PassCopyToRedialBuffer = 1;
		}
		if ( SYB_RedialBufWritePointer < ( SYS_REDIAL_BUF_MAX - 1 ) && PassCopyToRedialBuffer == 0) {
#else
		if ( SYB_RedialBufWritePointer < ( SYS_REDIAL_BUF_MAX - 1 )) {
#endif

			/*-----------------*/
			/** PIN Operation  */
			/*-----------------*/
			if( dial_number == OPR_PIN_MARK ){
				PIN_NumberRedialProtectFlag = 1;
				SYB_RedialBuffer[SYB_RedialBufWritePointer] = 0x00;
			}
			else{
				if( PIN_NumberRedialProtectFlag == 0 ){
					SYB_RedialBuffer[SYB_RedialBufWritePointer] = dial_number;
					SYB_RedialBuffer[SYB_RedialBufWritePointer+1] = 0x00;
					SYB_RedialBufWritePointer++;
				}
			}
		}

		if( CTRY_OffhookTel() == 1 ){
			if(NCUStatus & HOOK_KEY_ON_STATE){
				dialbuf_wp = SYS_DialingNumber.WritePointer;
			}
		}
		else {
			dialbuf_wp = SYS_DialingNumber.WritePointer;
		}

		if (NCUStatus & HOOK_KEY_ON_STATE) {
			MonitorSpeakerOn();
		}
	}
	/*-------------------------------------------------------------*/
	/** ダイヤル送出後、回線に受話器を接続するまでのタイマをセット */
	/*-------------------------------------------------------------*/
	NCU10msTimer.Time			 = CHK_AfterDialCML_OFF_Time();
	NCU10msTimer.SendMBX		 = mbxno.NCU_TelephoneExecuteTask;
	NCU10msTimer.ReturnValue	 = NOTICE_TEL_CML_OFF_TIMEUP;
	tskno_CMN_Watch2Timer10msTask = 0xFFFF;
	cre_tsk(&tskno_CMN_Watch2Timer10msTask, TSK_CMN_MAN_TIMER10MSTASK, &NCU10msTimer);

	NCUStatus	  &= ~DIALING_STATE;
	NumberKeyInputFlag =  0;
	
}


#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[転送受信機能実行部位（ＮＣＵ＿ＴＲＮ）]
	function	:[
		1.検出したＯＮ　ＨＯＯＫが転送受信であるかどうか判定します。
	]
	return		:[
		TRUE:	転送受信可能
		FALSE:	転送受信不可
	]
	common		:[
		NCUStatus			:回線監視モジュール動作状態を記憶
		SYS_RingCounter			:呼出ベル鳴動回数をカウント
		TransferReceiveFlag		:転送受信許容時間以内であるかどうかを判断（０：無効　１：有効）
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1997/11/29]
	author		:[曽根岡拓]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE	TransferReceive(UBYTE(*mem_sw_read)(void))
{
	TxTelephoneExecuteTaskMsg.Item = FROM__NCU_TEL;

	if ((TransferReceiveFlag)
	&& ((*mem_sw_read)())) {
		if ((!CHK_Phone2ExtLineOn()) 	/**	PHONE2リレー設定が標準ラインの場合	*/
		&& (NCUStatus & TELEPHONE2_OFF_HOOK)		/* 修正 by T.Soneoka 1998/03/09 <-&& (!(NCUStatus & TELEPHONE2_OFF_HOOK)) */
		&& (SYS_ANS_FAX_READY == NCU_RxModeSwitch)
		&& (!(CHK_TAD_FaxReadyOnhookTransfer()))) {
			return(FALSE);
		}
		else{
			if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {
				return(FALSE);
			}
			else {
 #if (PRO_REMOTE_DIAL_TRANSFER == ENABLE )		/* REMOTE_RX_FUNC */
				if (((NCU_RemoteTransferDial()) && (TADStatus & REMOTE_RECEIVE))) {
					return(TRUE);
				} else {
					return(FALSE);
				}
 #else
				return(TRUE);
 #endif
			}
		}
	}
	else{
		return(FALSE);
	}
	return(FALSE);
}
#else
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[転送受信機能実行部位（ＮＣＵ＿ＴＲＮ）]
	function	:[
		1.検出したＯＮ　ＨＯＯＫが転送受信であるかどうか判定します。
	]
	return		:[
		なし
	]
	common		:[
		NCUStatus			:回線監視モジュール動作状態を記憶
		SYS_RingCounter			:呼出ベル鳴動回数をカウント
		TransferReceiveFlag		:転送受信許容時間以内であるかどうかを判断（０：無効　１：有効）
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1995/12/27]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	TransferReceive( WORD *tx_mail_box_no, UBYTE (  *mem_sw_read)( void ))
{
	TxTelephoneExecuteTaskMsg.Item = FROM__NCU_TEL;

	if(( SYS_RingCounter ) && ( TransferReceiveFlag ) && ((*mem_sw_read)())){
 #if !((PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2))		/* ANS待機での55転送 移植 by SMuratec 李 2004/08/27 */
  #if (PRO_NCU_TYPE == ANZU_USA_TYPE) || (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 1996/07/11 By N.Sakamoto */
		if(((   NCUStatus	 &	TELEPHONE1_OFF_HOOK )||(   NCUStatus	 &	TELEPHONE2_OFF_HOOK ))
		&& (   SYS_ANS_FAX_READY == NCU_RxModeSwitch	)
		&& (!( CHK_TAD_FaxReadyOnhookTransfer()			))){
			TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
		}
  #else	/* (PRO_NCU_TYPE == POPLAR_TYPE) *//* #ifの条件からPOPLARをはずた By M.Tachibana 1997/11/08 */
		if((   NCUStatus	 &	TELEPHONE2_OFF_HOOK )
		&& (   SYS_ANS_FAX_READY == NCU_RxModeSwitch	)
		&& (!( CHK_TAD_FaxReadyOnhookTransfer()			))){
			TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
		}
  #endif
		else{
 #endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
			/* Sep.7,1994 By S.K */
			if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {
				TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
			}
			else {
 #if (PRO_ONHOOK_RX_SWITCH == ENABLE) && (PRO_REMOTE_RX == ENABLE)
				/* ポプラＬのＮＴＴ仕様は、リモート受信かオンフック受信の設定が  */
				/* ＯＮでないと転送受信はできません 1998/03/16 Add By T.Fukumoto */
				if( ( ( CHK_RemoteRxON() ) && ( TADStatus & REMOTE_RECEIVE ) )
				 || ( CHK_OnHookRX_ON() ) ) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE;
				}
				else {
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
				}
 #elif (PRO_REMOTE_DIAL_TRANSFER == ENABLE )		/* REMOTE_RX_FUNC */
				/* リモート受信かオンフック受信の設定が  */
				/* ＯＮでないと転送受信はできません      */
  #if (0) /* 2002/02/03 Y.Murata オンフック転送のソースコードを削除 */
  //				if( ( ( NCU_RemoteTransferDial() ) && ( TADStatus & REMOTE_RECEIVE ) )
  //				 || ( NCU_RemoteTransferOnHook() ) ) {
  //					TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE;
  //				}
  //				else {
  //					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
  //				}
  #endif
				if( ( ( NCU_RemoteTransferDial() ) && ( TADStatus & REMOTE_RECEIVE ) ) ) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE;
				}
				else {
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
				}
 #else
				TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE;
 #endif
			}
 #if !((PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2))		/* ANS待機での55転送 移植 by SMuratec 李 2004/08/27 */
		}
 #endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
	}
	else{
		TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
	}

	snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
	wai_tsk(0xFFFF);
}
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[多機能電話機能実行タスク（ＮＣＵ＿ＴＥＬ１）]
	function	:[
		1.狭義の多機能電話の実際の動作の開始・終了部位
		2.狭義の多機能電話動作の内、保留状態・内線呼出状態・内線通話状態を除いた状態の実行部位
	]
	return		:[なし]
	common		:[
		NCUStatus					:回線監視モジュール動作状態を記憶
		SYS_RingCounter					:呼出ベル鳴動回数をカウント
		SYS_HookKeyInputFlag			:回線捕捉キー入力情報
		HookKeyInputFlag				:回線捕捉キー入力同期フラグ
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1993/12/20]
	author		:[坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		   NCU_TelephoneExecuteTask( WORD *tx_mail_box_no )
{
	MESSAGE_t	   *RxTelephoneExecuteTaskMsg;


	/*-------------------*/
	/** 内部変数の初期化 */
	/*-------------------*/
	TxTelephoneExecuteTaskMsg.Item	= FROM__NCU_TEL;
	/*SYS_HookKeyInputFlag			= 0;By Y.Suzuki 1998/03/31*/
	/* 待機状態からフックキーを2回連続入力されると2度目のフックキー入力が無効になる。By Y.Suzuki 1998/03/31*/
	/* NTTからの指摘事項です。*/
	if (SYS_HookKeyInputFlag != 1) {/* フックキー入力有り 以外なら */
		SYS_HookKeyInputFlag			= 0;
	}
	HookKeyInputFlag				= 0;
	tskno_CMN_WatchTimer10msTask	= 0xFFFF;
	tskno_CMN_Watch2Timer10msTask	= 0xFFFF;
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	tskno_mercury = 0xffff;
	tskno_mcry_timeup = 0xffff;
	tskno_mcry_dt = 0xffff;
	tskno_mcry_dt_timeup = 0xffff;
#endif
#if defined(EC1)	/* ITA仕様 */
	PassCopyToRedialBuffer = 0;
#endif
					/*-----------------------------------------*/
	while(1){		/** 回線捕捉状態が解除されるまで無限ループ */
					/*-----------------------------------------*/
		/*---------------------------------------------*/
		/** 通常状態における多機能電話の事象の待ち合せ */
		/*---------------------------------------------*/
		rcv_msg(mbxno.NCU_TelephoneExecuteTask, &RxTelephoneExecuteTaskMsg);
																					/*-----------------*/
		switch(RxTelephoneExecuteTaskMsg->Message){									/** 発生事象の処理 */
												/*-----------------------------*/	/*-----------------*/
			case NOTICE_TEL1_ON_HOOK		:	/** 付属電話ＯＮ　ＨＯＯＫ検出 */
												/*-----------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
 #if 0 /* 警察FAX DVT_ID10 Modified by SMuratec 李 2005/11/01 */
@@				if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
@@					/* 秘話機能起動した場合 */
@@					SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
@@					SYS_LineTelStatus |= STD_READY;
@@					H_RelayOff();
@@				}
 #else
				if ((SYS_LineTelStatus & SYS_STD_LINE_STATUS) != STD_READY) {
					/* 秘話機能起動した場合 */
					SYS_LineTelStatus &= ~SYS_STD_LINE_STATUS;
					SYS_LineTelStatus |= STD_READY;
				}
				H_RelayOff();
 #endif
				if (!(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK))) {
					NCU_HdstShift();
				}
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/25 */
				if (DEBUG_NumberDisplay) {
					if (SYS_LineNDStatus == ND_USED_IN_STD) {
						NCU_ND_InitializeStatus();
					}
				}
				/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
				SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
 #endif /* defined (KEISATSU) */
 #endif /* defined (KEISATSU) */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/06 */
				if ((SYS_RingCounter)
				&&  (TransferReceive(CHK_TEL1FaxTransferAvailable) == TRUE)) {
					SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
					TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE1;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
				SYS_RingCounter = 0;
 #else /* !defined (KEISATSU) */
				SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
				if ((SYS_RingCounter)
				&&  (TransferReceive(CHK_TEL1FaxTransferAvailable) == TRUE)) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE1;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
 #endif /* (PRO_KEYPANEL == PANEL_STOCKHM2) */
				if (!CHK_Phone2ExtLineOn()) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
				NCUStatus &= (~TELEPHONE1_OFF_HOOK);
				if ((!(NCUStatus & TELEPHONE2_OFF_HOOK))
				&&	(!(NCUStatus & HOOK_KEY_ON_STATE))) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
				SYS_RingCounter = 0;
#else
				TransferReceive( tx_mail_box_no, CHK_TEL1FaxTransferAvailable );
#endif

				break;
												/*-----------------------------*/
			case NOTICE_TEL2_ON_HOOK		:	/** 外付電話ＯＮ　ＨＯＯＫ検出 */
												/*-----------------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
				if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
					SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
					if ((SYS_RingCounter)
					&&  (TransferReceive(CHK_TEL2FaxTransferAvailable) == TRUE)) {
						TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE2;
						snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
						wai_tsk(0xFFFF);
					}
				}
				else {
 #if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/13 */
 #if 0 /* 警察FAX DVT_ID10 Modified by SMuratec 李 2005/11/01 */
@@					if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
@@						/* 秘話機能起動した場合 */
@@						SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
@@						SYS_LineTelStatus |= EXT_READY;
@@						L_RelayOff();
@@					}
 #else
					if ((SYS_LineTelStatus & SYS_EXT_LINE_STATUS) != EXT_READY) {
						/* 秘話機能起動した場合 */
						SYS_LineTelStatus &= ~SYS_EXT_LINE_STATUS;
						SYS_LineTelStatus |= EXT_READY;
					}
					L_RelayOff();
 #endif
					if (!(NCU_LineStatus & (STD_HDST_OFFHOOK | EXT_HDST_OFFHOOK))) {
						NCU_HdstShift();
					}
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/25 */
					if (DEBUG_NumberDisplay) {
						if (SYS_LineNDStatus == ND_USED_IN_EXT) {
							NCU_ND_InitializeStatus();
						}
					}
					/* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
					SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	拡張ライン通信中	*/
 #endif /* defined (KEISATSU) */
 #endif /* defined (KEISATSU) */
 #if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/07/06 */
					if ((SYS_RingCounterExt)
					&&  (TransferReceive(CHK_TEL2FaxTransferAvailable) == TRUE)) {
						SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	拡張ライン通信中	*/
						TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE2;
						snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
						wai_tsk(0xFFFF);
					}
					SYS_RingCounterExt = 0;
 #else /* !defined (KEISATSU) */
					SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	拡張ライン通信中	*/
					if ((SYS_RingCounterExt)
					&&  (TransferReceive(CHK_TEL2FaxTransferAvailable) == TRUE)) {
						TxTelephoneExecuteTaskMsg.Message = DETECT_TRANSFER_RECEIVE2;
						snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
						wai_tsk(0xFFFF);
					}
 #endif /* (PRO_KEYPANEL == PANEL_STOCKHM2) */
				}
				if (!CHK_Phone2ExtLineOn()) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
				NCUStatus &= (~TELEPHONE2_OFF_HOOK);
				if ((!(NCUStatus & TELEPHONE1_OFF_HOOK))
				&&	(!(NCUStatus & HOOK_KEY_ON_STATE))) {
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
				SYS_RingCounterExt = 0;
#else
				TransferReceive( tx_mail_box_no, CHK_TEL2FaxTransferAvailable );
#endif

				break;
												/*-----------------------*/
			case NOTICE_INPUT_HOOK_KEY		:	/** 回線捕捉キー入力検出 */
												/*-----------------------*/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/25 */
				if (!CHK_Phone2ExtLineOn()) {
					if (((CHK_UNI_TEL2_TEL1Action())
					&& (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)))
					|| ((!(CHK_UNI_TEL2_TEL1Action()))
					&& (NCUStatus & TELEPHONE1_OFF_HOOK))) {
						if ( CTRY_OffhookTel() ){
							HookingRelayControl();
						}
						SYS_HookKeyInputFlag = 0;
						HookKeyInputFlag	 = 0;
					}
					else{
						/*-----------------------------------*/
						/** 回線捕捉キーによる回線捕捉の解除 */
						/*-----------------------------------*/
						NCUStatus &= ~HOOK_KEY_ON_STATE;
						TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
						snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
						wai_tsk(0xFFFF);
					}
				}
				else {
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
					if ((NCUStatus & TELEPHONE1_OFF_HOOK) /* 標準回線電話オフフック */
						&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
						if ( !HDST_RelaySetting()						/* ハンドセットは標準回線側接 */
							||(NCUStatus & TELEPHONE2_OFF_HOOK) ) { 	/* 拡張回線電話オフフック */
							if ( CTRY_OffhookTel() ){
								HookingRelayControl();
							}
							SYS_HookKeyInputFlag = 0;
							HookKeyInputFlag	 = 0;
						}
						else {	/* ハンドセットは拡張回線側接及びは、
								   拡張回線電話オンフック */
							/*----------------------------------------------*/
							/** 回線補足キーによる回線補足の為のリレー制御 */
							/*---------------------------------------------*/
							if (NCUStatus & HOOK_KEY_ON_STATE) {
								if (!IsDailing) {	/* 本体ダイヤル中ではない */
									NCU_LineStatus &= ~EXT_LINE_STATUS;
									NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_NOT_USE);
								}
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/25 */
								if (DEBUG_NumberDisplay) {
									if (SYS_LineNDStatus == ND_USED_IN_EXT) {
										NCU_ND_InitializeStatus();
									}
								}
 #endif
								SYS_RingCounterExt = 0;
								NCUStatus &= ~HOOK_KEY_ON_STATE;
								HookKeyOffRelayControl();
							}
							else {
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/26 */
								if (DEBUG_NumberDisplay) {
									if (SYS_LineNDStatus == ND_USED_IN_STD) {
										NCU_ND_SetCallDetectedStatus();
									}
								}
 #endif /* defined (KEISATSU) */
								NCUStatus |= HOOK_KEY_ON_STATE;
								HookKeyOnRelayControl();
							}
							SYS_HookKeyInputFlag = 0;
							HookKeyInputFlag = 0;
						}
					}
					else if ((NCUStatus & TELEPHONE2_OFF_HOOK)	/* 拡張回線電話オフフック */
						&& !(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE)) {
						if ( HDST_RelaySetting()						/* ハンドセットは拡張回線側接 */
							|| (NCUStatus & TELEPHONE1_OFF_HOOK) ) {	/* 標準回線電話オフフック */
							if ( CTRY_OffhookTel() ){
								HookingRelayControl();
							}
							SYS_HookKeyInputFlag = 0;
							HookKeyInputFlag	 = 0;
						}
						else { 	/* ハンドセットは標準回線側接及びは、
								   標準回線電話オンフック */
							/*----------------------------------------------*/
							/** 回線補足キーによる回線補足の為のリレー制御 */
							/*---------------------------------------------*/
							if (NCUStatus & HOOK_KEY_ON_STATE) {
								if (!IsDailing) {	/* 本体ダイヤル中ではない */
									NCU_LineStatus &= ~STD_LINE_STATUS;
									NCU_LineStatus  |=  (STD_LINE_STATUS & STD_NOT_USE);
								}
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/25 */
								if (DEBUG_NumberDisplay) {
									if (SYS_LineNDStatus == ND_USED_IN_STD) {
										NCU_ND_InitializeStatus();
									}
								}
 #endif /* defined (KEISATSU) */
								SYS_RingCounter = 0;
								NCUStatus &= ~HOOK_KEY_ON_STATE;
								HookKeyOffRelayControl();
							}
							else {
 #if (PRO_NUMBER_DISPLAY == ENABLE) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/10/21 */
 								if (DEBUG_NumberDisplay) {
									if (SYS_LineNDStatus == ND_USED_IN_EXT) {
										NCU_ND_SetCallDetectedStatus();
									}
								}
 #endif /* defined (KEISATSU) */
								NCUStatus |= HOOK_KEY_ON_STATE;
								HookKeyOnRelayControl();
							}
							SYS_HookKeyInputFlag = 0;
							HookKeyInputFlag = 0;
						}
					}
#else /* !defined (KEISATSU) */
					if (NCUStatus & TELEPHONE1_OFF_HOOK) {
						if ( CTRY_OffhookTel() ){
							HookingRelayControl();
						}
						SYS_HookKeyInputFlag = 0;
						HookKeyInputFlag	 = 0;
					}
					else if (NCUStatus & TELEPHONE2_OFF_HOOK) {
						/*----------------------------------------------*/
						/** 回線補足キーによる回線補足の為のリレー制御 */
						/*---------------------------------------------*/
						if (NCUStatus & HOOK_KEY_ON_STATE) {
							NCUStatus &= ~HOOK_KEY_ON_STATE;
							HookKeyOffRelayControl();
						}
						else {
							NCUStatus |= HOOK_KEY_ON_STATE;
							HookKeyOnRelayControl();
						}
						SYS_HookKeyInputFlag = 0;
						HookKeyInputFlag = 0;
					}
#endif /* defined (KEISATSU) */

#if (0)
//					if (NCUStatus & (TELEPHONE1_OFF_HOOK | TELEPHONE2_OFF_HOOK)) {
//						if ( CTRY_OffhookTel() ){
//							HookingRelayControl();
//						}
//						SYS_HookKeyInputFlag = 0;
//						HookKeyInputFlag	 = 0;
//					}
#endif
					else{
						/*-----------------------------------*/
						/** 回線捕捉キーによる回線捕捉の解除 */
						/*-----------------------------------*/
 #if defined (KEISATSU) /* 警察FAX (ナンバーディスプレイ) Added by SMuratec 李 2005/11/29 */
 #if (PRO_NUMBER_DISPLAY == ENABLE)
						if (CHK_LineSetting()) { /* 加入回線 */
							SYS_InternalLineNumber = SYS_STD_LINE_COM;	/**	標準ライン通信中	*/
							SYS_RingCounter = 0;
						}
						else {
							SYS_InternalLineNumber = SYS_EXT_LINE_COM;	/**	拡張ライン通信中	*/
							SYS_RingCounterExt = 0;
						}
 #endif /* defined (KEISATSU) */
 #endif /* defined (KEISATSU) */
						NCUStatus &= ~HOOK_KEY_ON_STATE;
						TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
						snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
						wai_tsk(0xFFFF);
					}
				}
#else

/*
** ＴＥＬ２がＴＥＬ１と同じ動作の場合、
** ＴＥＬ２をオフフックした状態でオフフックキーを押したとき、
** フッキング動作をせず、待機状態に戻る不具合
** ＨＩＮＯＫＩ ＱＡＴ 1999/02/09 by T.Soneoka
*/
#if (0)
**				if( TELEPHONE1_OFF_HOOK == ( NCUStatus & TELEPHONE1_OFF_HOOK )){		/** 付属電話ＯＦＦ　ＨＯＯＫの場合 */
#else
				if ((TELEPHONE1_OFF_HOOK == (NCUStatus & TELEPHONE1_OFF_HOOK))
				|| (((TELEPHONE2_OFF_HOOK == (NCUStatus & TELEPHONE2_OFF_HOOK)) && CHK_UNI_TEL2_TEL1Action()))) {
#endif

					/*-------------------------------------*/
					/** フッキング動作（ＮＣＵ＿ＨＫＮＧ） */
					/*-------------------------------------*/
					if ( CTRY_OffhookTel() ){
						HookingRelayControl();
					}

					SYS_HookKeyInputFlag = 0;
					HookKeyInputFlag	 = 0;
				}
				else{
					/*-----------------------------------*/
					/** 回線捕捉キーによる回線捕捉の解除 */
					/*-----------------------------------*/
					NCUStatus &= ~HOOK_KEY_ON_STATE;
					TxTelephoneExecuteTaskMsg.Message = DETECT_ON_HOOK_MANAGE_END;
					snd_msg( *tx_mail_box_no, &TxTelephoneExecuteTaskMsg);
					wai_tsk(0xFFFF);
				}
#endif
				break;
																/*-------------------*/
			case NOTICE_INPUT_HOLD_KEY		:					/** 保留キー入力検出 */
				/*---------------------------------------*/		/*-------------------*/
				/** 保留機能実行部位（ＮＣＵ＿ＨＯＬＤ） */
				/*---------------------------------------*/
				HoldOperation( tx_mail_box_no );
				NCUStatus &= ~HOLD_STATE;

				if( tskno_CMN_WatchTimer10msTask != 0xFFFF ){
					del_tsk(&tskno_CMN_WatchTimer10msTask);
				}

				break;
												/*-----------------------*/
			case NOTICE_INPUT_DIAL_KEY		:	/** ダイヤル番号入力検出 */
												/*-----------------------*/
				if(( tskno_CMN_Watch2Timer10msTask != 0xFFFF )
				&& (!( NCUStatus & HOLD_STATE ))){
					del_tsk(&tskno_CMN_Watch2Timer10msTask);
				}
				/*-------------------------------------------*/
				/** ダイヤリング実行部位（ＮＣＵ＿ＤＩＡＬ） */
				/*-------------------------------------------*/
				TelephoneDialing();

				break;
												/*-----------------------------------------------*/
			case NOTICE_TEL_CML_OFF_TIMEUP	:	/** ダイヤル後、受話器回線復帰タイマＴｉｍｅＵｐ */
												/*-----------------------------------------------*/
				if( tskno_CMN_Watch2Timer10msTask != 0xFFFF ){
					del_tsk(&tskno_CMN_Watch2Timer10msTask);
				}
#if !defined (KEISATSU) /* Added by SMuratec 李 2005/06/24 */

				DialEndRelayControl();
#else /* defined (KEISATSU) */
				DialEndRelayControl();
				if (CHK_LineSetting()) { 			/* 回線設定は標準回線側接 */
					if ((LineStatusBk & STD_LINE_STATUS) != (NCU_LineStatus & STD_LINE_STATUS)) {
						NCU_LineStatus &= ~STD_LINE_STATUS;
						NCU_LineStatus |= (LineStatusBk & STD_LINE_STATUS);
					}
				}
				else { /* ハンドセットは拡張回線側接 */
					if ((LineStatusBk & EXT_LINE_STATUS) != (NCU_LineStatus & EXT_LINE_STATUS)) {
						NCU_LineStatus &= ~EXT_LINE_STATUS;
						NCU_LineStatus |= (LineStatusBk & EXT_LINE_STATUS);
					}
				}
				IsDailing = FALSE;
				if ( SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE ) {
					if (!(NCUStatus & HOOK_KEY_ON_STATE)) {
						if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_SHIREI_SIGNEL_ON) {
						}
 #if 0 /* 警察FAX DVT_ID37 Modify by SMuratec 李 2005/11/12 */
@@						else if ((SYS_RingCounterExt >= CHK_ExtRingCount())
@@								&& !(NCUStatus & TELEPHONE2_OFF_HOOK)) {			/** 着信条件を満たした */
@@						}
 #else
						else if (CHK_KEIDENRxPriority()
								&& (SYS_RingCounterExt >= (UBYTE)GetRingCounter(1))
								&& !(NCUStatus & TELEPHONE2_OFF_HOOK)) {			/** 着信条件を満たした */
						}
 #endif
						else {
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_COM_ON_FORCE;
						}
					}
				}
#endif /* defined (KEISATSU) */

				break;
												/*-------------------------------*/
			case NOTICE_TEL1_OFF_HOOK		:	/** 付属電話ＯＦＦ　ＨＯＯＫ検出 */
												/*-------------------------------*/
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
				if (!ModemRelaySetting()) {	/* モデムリレーを標準回線に接続している場合 */
					if (!IsDailing) {	/* 本体ダイヤル中ではない */
						if (SYS_RingCounter) {
							NCU_LineStatus &= ~STD_LINE_STATUS;
							NCU_LineStatus  |=  (STD_LINE_STATUS & STD_TEL_RECEIVE);
						}
						else {
							NCU_LineStatus &= ~STD_LINE_STATUS;
							NCU_LineStatus  |=  (STD_LINE_STATUS & STD_TEL_TRANSMIT);
						}
					}
					NCUStatus &= ~HOOK_KEY_ON_STATE;
					HookKeyOffRelayControl();
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
					UpdateLED();
				}
				else {
					TelIndependentRelayControl();
				}
#else /* !defined (KEISATSU) */
				NCUStatus &= ~HOOK_KEY_ON_STATE;
				HookKeyOffRelayControl();
#endif /* defined (KEISATSU) */
				break;

			/*-----------------------------------------------------------
			** ＴＥＬ２もＴＥＬ１の処理に統一  By M.Tachibana 1997/09/25
			*/
												/*-------------------------------*/
			case NOTICE_TEL2_OFF_HOOK		:	/** 付属電話ＯＦＦ　ＨＯＯＫ検出 */
												/*-------------------------------*/
				if (CHK_UNI_TEL2_TEL1Action()) {
#if defined (KEISATSU) /* Modify by SMuratec 李 2005/06/24 */
					if (ModemRelaySetting()	/* モデムリレーを拡張回線に接続している場合 */
						) {
						if (!IsDailing) {	/* 本体ダイヤル中ではない */
							if (SYS_RingCounterExt) {
								NCU_LineStatus &= ~EXT_LINE_STATUS;
								NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_TEL_RECEIVE);
							}
							else {
								NCU_LineStatus &= ~EXT_LINE_STATUS;
								NCU_LineStatus  |=  (EXT_LINE_STATUS & EXT_TEL_TRANSMIT);
							}
						}
						NCUStatus &= ~HOOK_KEY_ON_STATE;
						HookKeyOffRelayControl();
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_HOOK_KEY_OFF_HOOK;
						UpdateLED();
					}
					else {
						TelIndependentRelayControl();
					}
#else /* !defined (KEISATSU) */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/25 */
					if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
						NCUStatus &= ~HOOK_KEY_ON_STATE;
					}
#else
					NCUStatus &= ~HOOK_KEY_ON_STATE;
#endif
					HookKeyOffRelayControl();
#endif /* defined (KEISATSU) */
				}
				break;
			default	   :

				break;
		}
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[TelephoneExecuteTask強制終了処理ルーチン]
	function	:[
		1.子タスク（疑似ベル鳴動／ＯＨ監視・疑似ＲＢＴ送出／ＣＮＧ検出・汎用タイマ）の強制終了
		2.自タスク（多機能電話実行タスク）の終了
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
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void		   NCU_TelephoneExecuteExit( void )
{
	/*---------------------*/
	/** 子タスクの強制終了 */
	/*---------------------*/
	if( tskno_CMN_WatchTimer10msTask != 0xFFFF ){
		del_tsk( &tskno_CMN_WatchTimer10msTask );
	}
	if( tskno_CMN_Watch2Timer10msTask != 0xFFFF ){
		del_tsk( &tskno_CMN_Watch2Timer10msTask );
	}
	Del_LoopCurrentTask();
/*#if defined(GBR)|| defined(NLD)By Y.Suzuki 1998/09/18*/
#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
	Del_Mercury_Tone_Task();
	Del_Mcry_DialTone_Task();
#endif

#if (PRO_DIAL_PULSE_TASK == ENABLE)	/* 誤ダイヤル 2000/10/17 H.Yoshikawa */
	ATD_StopDialPulse(); /* ダイヤルパルス送出タスクを止める */
#endif

#if defined(POPLAR_F) || (PRO_NCU_TYPE == HINOKI_TYPE) || (PRO_NCU_TYPE == SAKAKI_TYPE)	|| (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 2000/01/14 Y.Murata HOOKKEY_TEL1_OFFHOOK_DIAL_BUG */
/* T-340ベテランテスト指摘項目 By O.Kimoto 2002/10/24 */ /* SAKAKI追加 By M.Maeda 2002/12/02 */ /* TWN用にANZU_GBR追加 2002/12/05 T.Takagi */
	OneDigitDiallingExecute = 0;
#endif

	/*-----------------*/
	/** 自タスクの終了 */
	/*-----------------*/
	exi_tsk();
}
