/**********************************************************************
*	ANZU
*
*	File	Name:	NCU_RBT.C
*	Coded	  by:	坂本直史
*	Module	Name:	TransferModulatedFrequencyRBT()
*					NCU_TransRBTAndDetCNGTask()
*					NCU_TransRBTAndDetCNGExit()
*					DialInCompareDTMF()
*					InterCallingCompareDTMF()
*					NCU_ReceiveDTMFTask()
*					NCU_ReceiveDTMFExit()
*
*	Note		:	回線監視各モジュール使用関数群
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
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\sysdiali.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\timer10.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\atd_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"

#include	"\src\atlanta\define\ncu_pro.h"
#include	"\src\atlanta\define\ncu_stat.h"
#include	"\src\atlanta\define\ncu_msg.h"
#include	"\src\atlanta\define\ncu_ret.h"
#include	"\src\atlanta\define\ncu_cnst.h"
#include	"\src\atlanta\define\ncu_def.h"

#if (PRO_MODEM == ORANGE3) /* added by H.Kubo 1997/07/23 */
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/07/23 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_io.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#endif

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\ncu_data.h"
#include	"\src\atlanta\ext_v\ncu_tbl.h"
#include	"\src\atlanta\ext_v\atd_data.h"

#include	"\src\atlanta\ext_v\sys_port.h"

#include	"\src\atlanta\define\cmn_pro.h"

#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\sh_sys.h"

#include	"\src\atlanta\define\uni_pro.h"

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/27  By T.Yamaguchi */
 #include	"\src\atlanta\ext_v\fcm_data.h"
 void	VoicePrompt(UBYTE);
#endif

#include	"\src\atlanta\sh7043\define\io_pro.h"	/* 拡張ＲＯＭ対応 S.Fukui June 19,1998 */

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"	/* 1999/11/06 M.Matsumoto */
 #endif
 #if (PRO_MODEM == MN195006)
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"	/* 1999/11/06 M.Matsumoto */
 #endif
#endif

/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[定期間単一周波数トーン送出]
	function	:[
		1.
	]
	return		:[
		必ず入力してください
	]
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
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	TransmitTone( UWORD    on_time, UBYTE	frequency)
{
    MDM_Tone( frequency );
    wai_tsk( on_time );
#if (PRO_MODEM == ORANGE3) /* Edited by H.Kubo 1997/07/23 */
	MDM_ConfigReset();
/*#endif @* (PRO_MODEM == ORANGE3) */
#else
	/*
	** 擬似リングバックトーンの音がおかしい。通常、30msON 30msOFFが 60msONになっている
	** on_time期間frequencyのトーンを送出した後、トーンの送出を止めます。by H.Hirao 1999/02/17
	*/
 #if defined (HINOKI) || defined (HINOKI3) || defined (HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
	/* MDM_SingleToneOff(); */
  #if (PRO_VOICE_ANSWER == ENABLE)
	/*-------------------------------------------------
	** （NTT TEL/FAXで擬似RBT鳴動したままとなる対策）
	** この関数をコールしているTransmitTone()で単一トーンを送出した後
	** wai_tskし、その後単一トーンをストップしている。
	** そのため、wai_tskしている間にスケジューリングがおこりTransmitTone()
	** をコールしているタスクが殺された場合、単一トーンを送出したままとなる
	** 単一トーン送出中を示すフラグを作成し、送出中であれば、TransmitTone()
	** をコールしているタスクが殺される時に、単一トーンを止める処理をいれる。
	** 2001/11/30 M.Matsumoto
	** Add by O.Kimoto 2002/11/14
	*/
	MDM_ToneOff();	/* モデム変更可能とするため　2001/05/11 K.Doukuni */
  #else
	MDM_SetIO(POS_RTS,OFF);		/* モデムのRTSPをクリアーします */
  #endif
 #endif
#endif

#if 0 /*defined(POPLAR_F)*/	/* 2000/2/17 Y.Murata 本来はRTSをOFFしとかなあかん。*/
**	MDM_SetIO(POS_RTS,OFF);
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[１６Ｈｚ変調４６２Ｈｚトーン送出]
	function	:[
		1.
	]
	return		:[
		必ず入力してください
	]
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
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	TransferModulatedFrequencyRBT( WORD   timecount )
{
    WORD     counter;

    counter = 0;

    while( counter < timecount ){
#if (0)/*By Y.Suzuki 1998/09/21*/
//#if defined(SWE)
//        TransmitTone( ( UWORD )3, TONE_415HZ_SWE );
#endif /* defined(SWE) */
#if defined(FRA)	/* by M.HARADA '96/11/18 */
	#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/07/23 */
		MDM_ConfigReset();
		MDM_DTMF(ROW_1); 	/* by M.HARADA '96/11/18 */
		wai_tsk(3);
		MDM_ConfigReset();
	#endif /* (PRO_MODEM == ORANGE3) */
	#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/23 */
        TransmitTone( ( UWORD )3, TONE_640HZ ); /* Since R288F can generate tone of any frequency, no longer use DTMF. */
	#endif /* (PRO_MODEM == R288F) */
#else /* !defined(SWE) && !defined(FRA) */
        TransmitTone( ( UWORD )3, TONE_462HZ );
#endif
	/*
	** 擬似リングバックトーンの音がおかしい。通常、30msON 30msOFFが 60msONになっている
	** on_time期間frequencyのトーンを送出した後、トーンの送出を止めます。by H.Hirao 1999/02/17
	*/
 #if defined (HINOKI) || defined (HINOKI3) || defined (HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
		/* トーンのコンフィグに10msかかってしまうので、ＯＦＦ期間を20msにウェイトします by H.Hirao 1999/02/18 */
		/* 機種固有だと思われるので、ＨＩＮＯＫＩだけにします。申し訳有りません。*/
		wai_tsk(2);
 #else
        wai_tsk( 3 );
 #endif
        counter++;
    }
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ＲＢＴ送出／（電話／ＦＡＸ自動切換のため、相手機のＣＮＧ信号検出）タスク]
	function	:[
		1.
	]
	return		:[
		必ず入力してください
	]
	common		:[
		必ず入力してください
	]
	condition	:[]
	comment		:[]
	machine		:[V53,RISC(SH),H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU/FCM]
	date		:[1995/12/27]
	author		:[坂本直史/原田学]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_TransRBTAndDetCNGTask( WORD *tx_mail_box_no )
{
	MESSAGE_t	*RxTransRBTAndDetCNGTaskMsg;
	UWORD		timer;
	UWORD		rbt_interval_time;
	UBYTE		rbt_dis_place_change_flag;
	UBYTE		dis_tx_count;
#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/03  By T.Yamaguchi */
	UBYTE		voice_message_stop_flag;
	UBYTE		cng_result;
	UWORD		voice_result;

	voice_message_stop_flag = 0;
	voice_result = 0;
	cng_result = 0;
#endif
#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
	UBYTE		cng_result;
	
	cng_result = 0;
	IsTelFaxRingSend = 0;		/* T/F待機で疑似ベル送出したら１になるフラグ O.Oshima 2002/03/05 M.Iida 2002/02/25 *//* Add By O.Kimoto 2002/03/11 */
#endif

	tskno_cng_detect = 0xffff;
	tskno_cng_timeup = 0xffff;

	TxTransRBTAndDetCNGTaskMsg.Item = FROM__NCU_SUB;

	/*---------------------------*/
	/**     ＣＮＧ検出開始       */
	/*---------------------------*/
   	rbt_dis_place_change_flag	= 0;
   	dis_tx_count				= 0;
	SYS_RingSignalStopFlag 		= 1;
	rbt_interval_time 			= SYS_GeneralTimer;

	while(1){
		SYS_RingSignalStopFlag = 1;

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/12/19 */

#if (0)
** /*
** ** ＣＮＧを異常に誤検出して、ＲＢＴ送出タイミングが狂う不具合
** ** ＲＸＡの経路に修正します
** ** 1999/02/16 by T.Soneoka
** */
**		AnalogSwitchTONE_Set();
#endif

		MDM_ToneModeConfig();	/* Added by H.Kubo 1998/01/06 */

#endif /* (PRO_MODEM == R288F) */


#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/27  By T.Yamaguchi */
 /* #if defined(POPLAR_F) */
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
		if (CMN_CheckAnswerEnable() == 0) {
#if (0)
** 			/* 擬似ベル鳴動中のBusyTone検出処理追加 By O.Kimoto 2002/11/01 */
** 		 	/*------------------------*/
** 			/**    ＣＮＧ検出期間     */
** 			/*------------------------*//*-------------------*/
** 			if( CNG_ToneDetect()){		/** ＣＮＧ検出の場合 */
** 										/*-------------------*/
** 				/*---------------------------------------------*/
** 				/**        通信タスクにＣＮＧ検出を通知        */
** 				/*---------------------------------------------*/
** 				TxTransRBTAndDetCNGTaskMsg.Message = DETECT_CNG;
** 				snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
** 				rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
** 				/*--------------------*/
** 				/**   自タスクの終了  */
** 				/*--------------------*/
** 				wai_tsk(0xFFFF);
** 			}
#else
			cng_result = CNG_ToneDetect();		/** ＣＮＧ検出の場合 */
			if(cng_result){
				/*---------------------------------------------*/
				/**        通信タスクに検出結果を通知         */
				/*---------------------------------------------*/
				if (cng_result == TONE_DET_OK) {
					TxTransRBTAndDetCNGTaskMsg.Message = DETECT_CNG;
				}
				if (cng_result == TONE_DET_BUSY) {
					TxTransRBTAndDetCNGTaskMsg.Message = DETECT_BUSY;
				}
				snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
				rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
				/*--------------------*/
				/**   自タスクの終了  */
				/*--------------------*/
				wai_tsk(0xFFFF);
			}
#endif
		}
		else {
			cng_result = CNG_ToneDetect();
			if (cng_result) {
				/*---------------------------------------------*/
				/**        通信タスクに検出結果を通知         */
				/*---------------------------------------------*/
				if (cng_result == TONE_DET_OK) {
					TxTransRBTAndDetCNGTaskMsg.Message = DETECT_CNG;
				}
				if (cng_result == TONE_DET_BUSY) {
					TxTransRBTAndDetCNGTaskMsg.Message = DETECT_BUSY;
				}
				snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
				rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
				/*--------------------*/
				/**   自タスクの終了  */
				/*--------------------*/
				wai_tsk(0xFFFF);
			}
        	if ( 0 == voice_message_stop_flag ) {
				voice_result = VoiceAnswer();	/* 音声応答 */
				if (voice_result) {	/* 音声応答の結果が０以外なら */
					TxTransRBTAndDetCNGTaskMsg.Message = voice_result;
					snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
					rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
					/*--------------------*/
					/**   自タスクの終了  */
					/*--------------------*/
					wai_tsk(0xFFFF);
				}
				voice_message_stop_flag = 1;	/* 音声応答しない */
			}
		}

 #else	/* ORANGEモデム */

		cng_result = CNG_ToneDetect();
		if (cng_result) {
			/*---------------------------------------------*/
			/**        通信タスクに検出結果を通知         */
			/*---------------------------------------------*/
			if (cng_result == TONE_DET_OK) {
				TxTransRBTAndDetCNGTaskMsg.Message = DETECT_CNG;
			}
			if (cng_result == TONE_DET_BUSY) {
				TxTransRBTAndDetCNGTaskMsg.Message = DETECT_BUSY;
			}
			snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
			rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
			/*--------------------*/
			/**   自タスクの終了  */
			/*--------------------*/
			wai_tsk(0xFFFF);
		}
		if ( 0 == voice_message_stop_flag ) {
			voice_result = VoiceAnswer();	/* 音声応答 */
			if (voice_result) {	/* 音声応答の結果が０以外なら */
				TxTransRBTAndDetCNGTaskMsg.Message = voice_result;
				snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
				rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
				/*--------------------*/
				/**   自タスクの終了  */
				/*--------------------*/
				wai_tsk(0xFFFF);
			}
			voice_message_stop_flag = 1;	/* 音声応答しない */
		}
 #endif
#endif
#if (PRO_VOICE_ANSWER == DISABLE)	/* 1998/01/27  By T.Yamaguchi */
	#if (PRO_BT_DET_WHILE_RBT == ENABLE)			/* 疑似ベル鳴動中のBusyTone検出 By O.Kimoto 2000/09/02 */
		/*------------------------*/
		/**    ＣＮＧ検出期間     */
		/*------------------------*//*-------------------*/
		cng_result = CNG_ToneDetect();		/** ＣＮＧ検出の場合 */
		if(cng_result){
			/*---------------------------------------------*/
			/**        通信タスクに検出結果を通知         */
			/*---------------------------------------------*/
			if (cng_result == TONE_DET_OK) {
				TxTransRBTAndDetCNGTaskMsg.Message = DETECT_CNG;
			}
			if (cng_result == TONE_DET_BUSY) {
				TxTransRBTAndDetCNGTaskMsg.Message = DETECT_BUSY;
			}
			snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
			rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
			/*--------------------*/
			/**   自タスクの終了  */
			/*--------------------*/
			wai_tsk(0xFFFF);
		}
	#else
		/*------------------------*/
		/**    ＣＮＧ検出期間     */
		/*------------------------*//*-------------------*/
		if( CNG_ToneDetect()){		/** ＣＮＧ検出の場合 */
									/*-------------------*/
			/*---------------------------------------------*/
			/**        通信タスクにＣＮＧ検出を通知        */
			/*---------------------------------------------*/
			TxTransRBTAndDetCNGTaskMsg.Message = DETECT_CNG;
			snd_msg( *tx_mail_box_no, &TxTransRBTAndDetCNGTaskMsg);
			rcv_msg(mbxno.NCU_TransRBTAndDetCNGTask, &RxTransRBTAndDetCNGTaskMsg );
			/*--------------------*/
			/**   自タスクの終了  */
			/*--------------------*/
			wai_tsk(0xFFFF);
		}
	#endif
#endif


		/*----------------------------------*/
		/**     擬似ＲＢＴ　ＯＮ　期間      */
		/*----------------------------------*/					/*-------------------------------------*/
		if( 1 == CTRY_RBTTable()->ModulatedFrequencyFlag ){		/** 擬似ＲＢＴに変調が掛かっている場合 */
																/*-------------------------------------*/
															/*-----------------------------------*/
			if( 1 == CTRY_RBTTable()->DoubleRingFlag ){		/** 擬似ＲＢＴがダブル・リングの場合 */
															/*-----------------------------------*/
				TransferModulatedFrequencyRBT( CTRY_RBTTable()->DoubleRingOnTimeCount );
				timer = ( WORD )( 60 * ( CTRY_RBTTable()->DoubleRingOffTimeCount ));
				wai_tsk( timer );
				TransferModulatedFrequencyRBT( CTRY_RBTTable()->DoubleRingOnTimeCount );
			}
			else{
#if (0)/*By Y.Suzuki 1998/09/21*/
//#if defined(SWE)				/* add by M.HARADA 95.07.07 */
//				TransferModulatedFrequencyRBT(( CTRY_RBTTable()->OnTime ) * 16 );	/* 擬似ベル鳴動時間　1sec */
//#else
//				TransferModulatedFrequencyRBT(( CTRY_RBTTable()->OnTime ) * 12 );
#endif
				TransferModulatedFrequencyRBT(( CTRY_RBTTable()->OnTime ) * 12 );
			}
		}
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[疑似ＲＢＴ送出／（電話／ＦＡＸ自動切換のため、相手機のＣＮＧ信号検出）タスク強制終了処理ルーチン]
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
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_TransRBTAndDetCNGExit( void )
{
    /*------------------*/
	/** ＣＮＧ検出打切  */
    /*------------------*/
    SYS_RingSignalStopFlag = 0;
	CNG_ToneDetectTaskExit();

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
	V8TaskDelete();
	StartUpTaskDelete();
	VoicePromptTaskDelete(); /* 1999/11/06 M.Matsumoto */
 #endif
#endif

    exi_tsk();
}


#if (PRO_DIALIN == ENABLE)
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・インＦＡＸ／ＴＥＬ切分実行部位]
	function	:[
		1.受信内線指定信号と登録内線番号の比較を行いＦＡＸ／付属電話／外付電話のいずれに着信させるかを判断する。
	]
	return		:[
		D_IN_UNMATCH	(0)		登録番号と受信番号の不一致または内線番号未登録
		D_IN_FAX		(1)		ＦＡＸに着信
		D_IN_TEL1		(2)		付属電話側呼出
		D_IN_TEL2		(3)		外付電話側呼出
		D_IN_TEL1_TEL2	(4)		付属／外付電話両方呼出
	]
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
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE    DialInCompareDTMF( void )
{
	UBYTE	tel1_ok_flag;
	UBYTE	i;


	tel1_ok_flag = OFF;

	for (i = 0; i < ( SYS_DIALIN_MAX - 1 ); i++) {
		if ((DTMF_ReceiverBuffer[i] & 0x0f) == 0x0a) {
			if (SYB_Dialin.FaxNumber[i] != '0') {
				break;
			}
		}
		else {
			if ((SYB_Dialin.FaxNumber[i] & 0x0f) != (DTMF_ReceiverBuffer[i] & 0x0f)) {
				break;
			}
		}
	}

	if (i == ( SYS_DIALIN_MAX - 1 )) {
		return (D_IN_FAX);
	}

	for (i = 0; i < ( SYS_DIALIN_MAX - 1 ); i++) {
		if ((DTMF_ReceiverBuffer[i] & 0x0f) == 0x0a) {
			if (SYB_Dialin.Tel1Number[i] != '0') {
				break;
			}
		}
		else {
			if ((SYB_Dialin.Tel1Number[i] & 0x0f) != (DTMF_ReceiverBuffer[i] & 0x0f)) {
				break;
			}
		}
	}

	if (i == ( SYS_DIALIN_MAX - 1 )) {
		tel1_ok_flag = ON;
	}

	for (i = 0; i < ( SYS_DIALIN_MAX - 1 ); i++) {
		if ((DTMF_ReceiverBuffer[i] & 0x0f) == 0x0a) {
			if (SYB_Dialin.Tel2Number[i] != '0') {
				break;
			}
		}
		else {
			if ((SYB_Dialin.Tel2Number[i] & 0x0f) != (DTMF_ReceiverBuffer[i] & 0x0f)) {
				break;
			}
		}
	}

	if (i == ( SYS_DIALIN_MAX - 1 )) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/20 */
		if (tel1_ok_flag == ON) {	/**	TEL1がすでにマッチしているとき	*/
			if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
				return (D_IN_TEL1_TEL2);	/**	TEL1とTEL2両方呼び出し	*/
			}
			else {	/**	PHONE2リレー設定が拡張ラインの場合	*/
				return (D_IN_TEL1);	/**	TEL1のみ呼び出し	*/
			}
		}
		if (!CHK_Phone2ExtLineOn()) {	/**	PHONE2リレー設定が標準ラインの場合	*/
			return(D_IN_TEL2);	/**	TEL2呼び出し	*/
		}
		else {	/**	PHONE2リレー設定が拡張ラインの場合	*/
			return (D_IN_UNMATCH);	/* 呼び出ししない */
		}
#else
		if (tel1_ok_flag == ON) {
			return (D_IN_TEL1_TEL2);
		}
		return(D_IN_TEL2);
#endif
	}
	else{
		if (tel1_ok_flag == ON) {
			return (D_IN_TEL1);
		}
	}
	return (D_IN_UNMATCH);
}

#endif /* (PRO_DIALIN == ENABLE) */


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ＤＴＭＦ検出タスクのメッセージ取得]
	function	:[
		1.状態によりメッセージを取得する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/04/27]
	author		:[平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	TakeInResultMessage(UBYTE	data)
{
	switch (data) {
#if (PRO_DIALIN == ENABLE)
	case D_IN_UNMATCH:		/** 登録番号と不一致 */
		TxReceiveDTMFTaskMsg.Message = DETECT_D_IN_UNMATCH;
		break;
	case D_IN_FAX:			/** FAX番号要求 */
		TxReceiveDTMFTaskMsg.Message = DETECT_D_IN_FAX;
		break;
	case D_IN_TEL1:			/** TEL1番号要求 */
		TxReceiveDTMFTaskMsg.Message = DETECT_D_IN_TEL1;
		break;
	case D_IN_TEL2:			/** TEL2番号要求 */
		TxReceiveDTMFTaskMsg.Message = DETECT_D_IN_TEL2;
		break;
	case D_IN_TEL1_TEL2:	/** TEL1,TEL2番号要求 */
		TxReceiveDTMFTaskMsg.Message = DETECT_D_IN_TEL1_TEL2;
		break;
#endif
	default:
		break;
	}
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ダイヤル・イン／外付電話からの内線呼出／保留転送の為のＤＴＭＦ検出]
	function	:[
		1.検出桁数のDTMFをバッファに取込む
		2.比較処理後、登録内容と一致していればメッセージを送信する
	]
	return		:[なし]
	common		:[
		UWORD NCUStatus
		UBYTE SYS_RingCounter
		UBYTE SYS_TxDetectFlag  電話器からの発呼状況
		UBYTE SYS_RxDetectFlag  電話器からの着呼状況
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/01/20]
	author		:[平岡徹,　坂本直史]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_ReceiveDTMFTask( WORD *tx_mail_box_no )
{
	UBYTE	 	ret_dtmf_data;
	MESSAGE_t 	*RxReceiveDTMFTaskMsg;

#if (PRO_DIALIN == ENABLE)
	UWORD	modem_port_read;

	UBYTE	dtmf_receive_debug = 0;			/* for debug */

 #if defined (HINOKI2) || defined (HINOKI3) /* FOR DTMF 2000/09/12 by K.Okada */ /* NAGANOより移植 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2) /* By M.Maeda 2002/09/18 */
	UBYTE pre_det;
	UBYTE check_bit;
	UBYTE comp_bit;
	
	pre_det = 0;
	check_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS | IO_BIT_DTMFD);
	comp_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS);
 #endif

	TxReceiveDTMFTaskMsg.Item = FROM__NCU_SUB;

				/*-----------------------------------------------------*/
	while(1){	/** ダイヤル・インＤＴＭＦを４桁検出し終わるまでループ */
				/*-----------------------------------------------------*/
		/*--------------------------------*/
		/**       Ｉ／Ｏ　Ｒｅａｄ        */
		/*--------------------------------*/

  #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0))/* By M.Maeda 2002/09/18 */
		/* modem_port_read = IO__PADRL; */
		/* ここでＩＯをリードするのは、汎用性に欠ける by H.Hirao 1998/12/04 */
  #else
		modem_port_read = IO__PEDR;
  #endif

		if( dtmf_receive_debug ){
			DTMF_OutPutTest = modem_port_read;
		}
		else{

 #if defined (HINOKI2) || defined (HINOKI3) /* FOR DTMF 2000/09/12 by K.Okada */ /* NAGANOより移植 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2)  || defined(STOCKHM2) /* By M.Maeda 2002/09/18 */
			if (!pre_det) {
				if ((inp(MDM_REG_1B_PORT) & comp_bit) == comp_bit) {
					pre_det = 1;
				}
			}
 #endif
												/*---------------------------------*/
			if(	DTMF_ReceiverCounter == 4 ){ 	/** ＤＴＭＦを既に４桁検出した場合 */
												/*---------------------------------*/
  #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0))/* By M.Maeda 2002/09/18 */
				if (!DTMF_Decision()) {
  #else
														/*---------------------------*/
				if(!( modem_port_read & IO_BIT_DV )){	/** ＤＴＭＦ検出　無効の場合 */
														/*---------------------------*/
  #endif
															/*---------------------------------*/
					ret_dtmf_data = DialInCompareDTMF();	/** 登録番号と検出ＤＴＭＦとの比較 */
															/*---------------------------------*/
					/*---------------------------------------------------------------*/
						/** ダイヤル・インＭＡＩＮタスク（ＮＣＵ＿Ｄ＿ＩＮ）へ結果を通知 */
					/*---------------------------------------------------------------*/
					TxReceiveDTMFTaskMsg.Message = DETECT_D_IN_DTMF_RCV;
					snd_msg( *tx_mail_box_no, &TxReceiveDTMFTaskMsg);
					rcv_msg(mbxno.NCU_ReceiveDTMFTask, &RxReceiveDTMFTaskMsg);
					/*---------------------------------------------------------------*/
					/** ダイヤル・インＭＡＩＮタスク（ＮＣＵ＿Ｄ＿ＩＮ）へ結果を通知 */
					/*---------------------------------------------------------------*/
					TakeInResultMessage(ret_dtmf_data);
					snd_msg( *tx_mail_box_no, &TxReceiveDTMFTaskMsg);
					rcv_msg(mbxno.NCU_ReceiveDTMFTask, &RxReceiveDTMFTaskMsg);
					/*-----------*/
					/** 終了待ち */
					/*-----------*/
					wai_tsk(0xFFFF);
				}
			}
			else{
 #if defined (HINOKI2) || defined (HINOKI3) /* FOR DTMF 2000/09/12 by K.Okada */ /* NAGANOより移植 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
		 		if (((inp(MDM_REG_1B_PORT) & check_bit) == IO_BIT_DTMFD) && pre_det) {
					DTMF_ReceiverBuffer[DTMF_ReceiverCounter] = MDM_GetIO(POS_DTMFW);
					DTMF_ReceiverCounter++;
					wai_tsk(1);
					MDM_SetIO(POS_DTMFD, 0);
					pre_det = 0;
				}
				else {
					wai_tsk(1);
				}
 #else
  #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */
				if (DTMF_Decision() && (DTMF_ReceiverDV_OnOff == OFF)) {
  #else
				                                                                            /*-------------------------------------------*/
				if(( modem_port_read & IO_BIT_DV ) && ( DTMF_ReceiverDV_OnOff == OFF )){	/** ＤＴＭＦ検出　有効で且つ前回が無効の場合 */
																							/*-------------------------------------------*/
  #endif
					/*-----------------------------------*/
					/** 検出ＤＴＭＦをバッファに格納する */
					/*-----------------------------------*/
  #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */ /* by H.Hirao 1998/12/03 */
					DTMF_ReceiverBuffer[DTMF_ReceiverCounter] = DTMF_Code();
  #else
					DTMF_ReceiverBuffer[DTMF_ReceiverCounter] = (UBYTE)(( modem_port_read & ( IO_BIT_DTMF1 | IO_BIT_DTMF2 | IO_BIT_DTMF3 | IO_BIT_DTMF4 )) >> 8 );
  #endif
					DTMF_ReceiverCounter++;
					DTMF_ReceiverDV_OnOff  = ON;
				}
				else{
  #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */
					if (!DTMF_Decision()) {
  #else
					if(!( modem_port_read & IO_BIT_DV )){
  #endif
						DTMF_ReceiverDV_OnOff  = OFF;
					}
				}
 #endif
			}
		}
 #if !defined (HINOKI2) && !defined(HINOKI3)	/* 2002/01/10 T.Takagi */ && !(defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || !(defined(SAKAKI) && defined(JP0)) || !defined(SATSUKI2)  && !defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
		/*---------------------------------*/
		/** １０ｍｓ自タスクをＷａｉｔする */
		/*---------------------------------*/
		wai_tsk(1);
 #endif
	}
#endif
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[ＤＴＭＦ検出タスク強制終了ルーチン]
	function	:[
		1.子タスクを強制終了後、自タスクを終了する
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[NCU]
	date		:[1994/02/04]
	author		:[平岡徹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
void	NCU_ReceiveDTMFExit(void)
{
	exi_tsk();
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[留守／ＦＡＸ待機時のリモートからのＤＴＭＦ検出タスク]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU]
	date		:[1997/11/16]
	author		:[橘正樹]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if ((PRO_NCU_TYPE == POPLAR_TYPE) && (PRO_DIALIN == ENABLE)) || ((PRO_NCU_TYPE == HINOKI_TYPE) && (PRO_DIALIN == ENABLE)) /* added by H.Kubo 1997/12/11 */
 #if (0)	/* 拡張ＲＯＭCLASS1 対応のため "\src\atlanta\sh7043\define\io_pro.h" で定義 */
void MonitorSpeakerOn(void);
void MonitorSpeakerOff(void);
 #endif
static UBYTE debug_dialin = 0;
#endif
void	NCU_DetectRemoteDTMFTask(void)
{
	UBYTE	number;
	UBYTE	dtmf_rcv_dv_on_off;
	UBYTE	dtmf_receiver_counter;
	UWORD	modem_port_read;
	MESSAGE_t	msg;

#if defined (HINOKI2) || defined (HINOKI3) /* FOR DTMF 2000/09/12 by K.Okada */ /* NAGANOより移植 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2)  || defined(STOCKHM2) /* By M.Maeda 2002/09/18 */
	UBYTE pre_det;
	UBYTE check_bit;
	UBYTE comp_bit;
	
	pre_det = 0;
	check_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS | IO_BIT_DTMFD);
	comp_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS);
#endif

	number = 0;
	dtmf_rcv_dv_on_off = OFF;
	dtmf_receiver_counter = 0;
	modem_port_read = 0;

	msg.Item = FROM__NCU_TAD;
	number = CHK_UNI_AnsFaxDTMFDetect();

#if ((PRO_NCU_TYPE == POPLAR_TYPE) && (PRO_DIALIN == ENABLE)) /* added by H.Kubo 1997/12/11 */
	if (debug_dialin == 1) {
		MonitorSpeakerOn();
	}
#endif

	/* 留守ＦＡＸ待機時のＤＴＭＦ検出  */
				/*-----------------------------------------------------*/
	while(1){	/** ＤＴＭＦを検出し終わるまでループ */
				/*-----------------------------------------------------*/
		/*--------------------------------*/
		/**       Ｉ／Ｏ　Ｒｅａｄ        */
		/*--------------------------------*/
#if defined (HINOKI2) || defined (HINOKI3) /* FOR DTMF 2000/09/12 by K.Okada */ /* NAGANOより移植 2002/01/10 T.Takagi */ || (defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2)  || defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
		if (!pre_det) {
			if ((inp(MDM_REG_1B_PORT) & comp_bit) == comp_bit) {
				pre_det = 1;
			}
		}
		if (((inp(MDM_REG_1B_PORT) & check_bit) == IO_BIT_DTMFD) && pre_det) {
			wai_tsk(1);
			MDM_SetIO(POS_DTMFD, 0);
			pre_det = 0;
			if (++dtmf_receiver_counter >= number) {
				msg.Message = DETECT_REMOTE_DTMF;
				snd_msg( mbxno.NCU_FaxTadAutoSwitchTask, &msg);
				wai_tsk(0xFFFF);
			}
		}
		else {
			wai_tsk(1);
		}
#else /* HINOKI2以外ならこっち */
 #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */
		/* ここでＩＯをリードするのは、汎用性に欠ける by H.Hirao 1998/12/04 */
 #else
		modem_port_read = IO__PEDR;
 #endif
												/*---------------------------------*/
		if(	dtmf_receiver_counter == number ){ 	/** ＤＴＭＦを既に４桁検出した場合 */
												/*---------------------------------*/
 #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */
			if (!DTMF_Decision()) {
 #else
													/*---------------------------*/
			if(!( modem_port_read & IO_BIT_DV )){	/** ＤＴＭＦ検出　無効の場合 */
													/*---------------------------*/
 #endif
				/*---------------------------------------------------------------*/
				/** 外付留守番電話着信後処理タスクへ結果を通知 */
				/*---------------------------------------------------------------*/
				msg.Message = DETECT_REMOTE_DTMF;
				snd_msg( mbxno.NCU_FaxTadAutoSwitchTask, &msg);
				/*-----------*/
				/** 終了待ち */
				/*-----------*/
 #if ((PRO_NCU_TYPE == POPLAR_TYPE) && (PRO_DIALIN == ENABLE)) /* added by H.Kubo 1997/12/11 */
				if (debug_dialin == 1) {
					MonitorSpeakerOff();
				}
 #endif
				wai_tsk(0xFFFF);
			}
		}
		else{
 #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */
			if (DTMF_Decision() && (dtmf_rcv_dv_on_off == OFF)) {
 #else
			                                                                        /*-------------------------------------------*/
			if(( modem_port_read & IO_BIT_DV ) && ( dtmf_rcv_dv_on_off == OFF )){	/** ＤＴＭＦ検出　有効で且つ前回が無効の場合 */
																					/*-------------------------------------------*/
 #endif
				/*-----------------------------------*/
				/** 検出ＤＴＭＦをバッファに格納する */
				/*-----------------------------------*/
				/* DTMF_ReceiverBuffer[dtmf_receiver_counter] = (UBYTE)(( modem_port_read & ( IO_BIT_DTMF1 | IO_BIT_DTMF2 | IO_BIT_DTMF3 | IO_BIT_DTMF4 )) >> 8 ); */
				dtmf_receiver_counter++;
				dtmf_rcv_dv_on_off  = ON;
			}
			else{
 #if (PRO_NCU_TYPE == HINOKI_TYPE)			/* NCU/ｶﾌﾟﾗｰTyep */  /* by H.Hirao 1998/12/04 */
				if (!DTMF_Decision()) {
 #else
				if(!( modem_port_read & IO_BIT_DV )){
 #endif
					dtmf_rcv_dv_on_off  = OFF;
				}
			}
		}
#endif /* defined (HINOKI2) */

#if !defined (HINOKI2) && !defined (HINOKI3) /* FOR DTMF 2000/09/08 by K.Okada */ /* 2002/01/10 T.Takagi */ && !(defined(POPLAR_H) && defined(JP0))/* By Y.Suzuki 1902/06/06 */ || !(defined(SAKAKI) && defined(JP0)) || !defined(SATSUKI2) && !defined(STOCKHM2)/* By M.Maeda 2002/09/18 */
		/*---------------------------------*/
		/** １０ｍｓ自タスクをＷａｉｔする */
		/*---------------------------------*/
		wai_tsk(1);
#endif
	}
}

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/02/04  By T.Yamaguchi */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[音声応答送出]
	function	:[
		1.音声応答をします。
	]
	return		:[
		RECEIVE/RECEIVE/TMOUT_RESP
	]
	common		:[

	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[NCU/FCM]
	date		:[1998/02/04]
	author		:[山口]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
 /* #if defined(POPLAR_F) */	/* 新Ｌ４００ */
 #if ((PRO_MODEM == R288F) || (PRO_MODEM == MN195006))	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
UWORD	VoiceAnswer(void)
{
	UWORD	timer;
	UBYTE	ret_value;

	/**********************/
	/* ＦＡＸ／ＴＥＬ待機 */
	/**********************/
	if ( AttemptRxModeSwitch == SYS_FAX_TEL_READY ) {
		/********************************************************/
		/** -------音声ﾒｯｾｰｼﾞ①  11.3 sec -------------        **/
		/* この電話はﾌｧｸｼﾐﾘに接続されています｡ﾋﾟｰという音の後に	*/
		/* 送信して下さい｡電話をご利用の方は,そのまましばらくお	*/
		/* 待ち下さい｡											*/
		/*------------------------------------------------------*/
		VoicePrompt(VOICE_A);
		/*************************************/
		/** 音声ﾒｯｾｰｼﾞ① - CED Wait 2.5 sec **/
		/*************************************/
		timer = (UWORD)2500;
		FaxTimer( timer );
		if( !CMN_CheckMemoryReceiveEnable() ){			/** 自動受信不可（メモリなし）*/
			/*---------------------------------------------*/
			/* メモリがない場合は､通信タスクの方で､擬似ベルを鳴らしオペレータを呼び出します */
			/*        通信タスクにＦＳＫ受信を通知         */
			/*---------------------------------------------*/
			return (RECEIVE);
		}
		else if (CMN_CheckMemoryReceiveEnable()) {	/* 受信可能 */

			if (FCM_CheckV8ProcedureRequest()) {	/** Ｖ８実行可能 */

				MDM_FilterSet(V8_MODE_FSK_TONE_FILTER);

				StartUpData.Item = V34_STANDARD;
				StartUpData.Option.TransmitCI = 0;
				StartUpData.Direction = TX_COM_MODE;

				if ((UWORD)CMN_CheckPollingDocRights((UWORD)SYS_SEND_INTERNAL_LINE)
				|| (SYB_DB_PollingDocumentStatus == 1)
				|| (SYB_SelectPollDocumentStatus == 1)
				|| (CheckPollingTxType() != 0)
				|| (CHK_UNI_FcodeSecureDocPollTx())) {
					StartUpData.Allowed = (TX_COM_MODE | RX_COM_MODE);
				}
				else {
					StartUpData.Allowed = TX_COM_MODE;
				}
				ret_value = FCM_AnswerStartUpProcedure();	/** スタートアップ応答処理 */
				V8ProcedureRequestFlag = 0;
				switch (ret_value) {
				case V34_PROCEDURE:
					/* Ｖ３４はＥＣＭ必須 */
					TxECM_Ability = ECM_ON;						/** ＥＣＭ送信ＯＮ指定 */
					RxECM_Ability = ECM_ON;						/** ＥＣＭ受信ＯＮ指定 */
					AvailableTxCodingMethod = SYS_MR_CODE;		/** 機器の送信可能な符号化方式 */
					AvailableRxCodingMethod = SYS_MR_CODE;		/** 機器の受信可能な符号化方式 */
					if (CHK_UNI_StoredMethodMMR()) {
						AvailableTxCodingMethod = SYS_MMR_CODE;	/** 機器の送信可能な符号化方式 */
						AvailableRxCodingMethod = SYS_MMR_CODE;	/** 機器の受信可能な符号化方式 */
					}
					SetAvailableCodingMethodEcmOn();
					SYS_V34ProcedureExecutingFlag = 1;
					break;
				case T30_PROCEDURE:
					SYS_V34ProcedureExecutingFlag = 0;
					FCM_CommunicationV8toT30();
					break;
				default:
					CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
					FaxComPerformingFlag = 0;
					break;
				}
			}
			else {
				CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
				SYS_FaxMelodyFlag = YES;
				FaxTransmitCED();				/** ＣＥＤ送出 */
				SYS_FaxMelodyFlag = NO;
			}
			if (FaxComPerformingFlag == 1) {
				if (SYS_V34ProcedureExecuting() == 0) {
					/*----------------------------------------------------*/
					/*	CED - NSF Wait 75±20ms[CCITT/FTZ18TR53 Fig11-1]  */
					/*----------------------------------------------------*/
					timer = CHK_WaitAfterDIS();		/** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
					TimerCutStatus = 1;
					FaxTimer( timer );
				}
				else {
					MDM_InitialConfig2(2);
				}
				/*------------*/
				/*	Phase B1  */
				/*------------*/
				SYS_PhaseB1Flag = YES;
				FaxRxPhaseB1();					/** 受信フェーズＢ１ */
				SYS_PhaseB1Flag = NO;
				if (V8ProcedureRequestFlag) {
					FCM_DetectCIbyVoiceAnswer = 1;
				}
			}

			if (FaxComPerformingFlag == 0) {
				/*---------------------------------------------*/
				/**        通信タスクにＦＳＫ受信を通知        */
				/*---------------------------------------------*/
				if (SYS_PhaseB1StopWaitFlag == 1) {	/* OH検出 */
					return (OK_SLEEP);
				}
				else if (SYS_PhaseB1StopWaitFlag == 2) {	/* BUSY検出 */
					return (DETECT_BUSY);
				}
			}
			if ( FaxComPerformingFlag != 0) {	/* 相手機がＦＡＸ */
				/*---------------------------------------------*/
				/**        通信タスクにＦＳＫ受信を通知        */
				/*---------------------------------------------*/
				return (RECEIVE);
			}
			/***************************/
			/** 音声ﾒｯｾｰｼﾞ②  8.6 sec **/
			/***************************/
			/*------------------------------------------------------*/
			/* ただいま,呼び出しております｡そのまましばらくお待ちく	*/
			/* ださい｡												*/
			/*------------------------------------------------------*/
			VoicePrompt(VOICE_B);
			/*****************************************/
			/** 音声ﾒｯｾｰｼﾞ② - 保留音 Wait 75±20ms **/
			/*****************************************/
			timer = ( UWORD )75;
			FaxTimer( timer );
			/************************/
			/** 保留音送出  24 sec **/
			/************************/
			SYS_FaxMelodyFlag = YES;
			StartSendingMelodyToLine();
			timer = ( UWORD )22000;	/* ２４秒 */
			FaxTimer( timer );
			StopSendingMelodyToLine();	/* 保留ﾒﾛﾃﾞｨ解除 */
			SYS_FaxMelodyFlag = NO;
			/*---------------------------------------------*/
			/**        通信タスクにタイムアウトを通知      */
			/*---------------------------------------------*/
			return (TMOUT_RESP);
		}
	}
	/**********************/
	/* ＴＥＬ／ＦＡＸ待機 */
	/**********************/
	else if( AttemptRxModeSwitch == SYS_TEL_FAX_READY ){
		/************************/
		/** Tel/Fax 待機	   **/
		/************************/
		if (CHK_VoiceMessageON()) { /* 音声応答メッセージ送出ＯＮなら */
			/****************************/
			/** 音声ﾒｯｾｰｼﾞ①  7.3 sec **/
			/****************************/
			/*--------------------------------------------------*/
			/* ただいま,電話を呼び出しております｡ﾌｧｸｼﾐﾘをご利用	*/
			/* の方は,そのまましばらくお待ちください｡			*/
			/*--------------------------------------------------*/
			VoicePrompt(VOICE_D);
			/******************************************************************/
			/** 音声ﾒｯｾｰｼﾞ①- 疑似RBT送出 Wait 1 sec + CNG 検出期間( 2 sec ) **/
			/******************************************************************/
			timer = ( UWORD )1000;
			FaxTimer( timer );
		}
	}
	return(0);
}

#else	/* Ｌ４００ *//* っていうかORANGEモデムの機種 */

UWORD	VoiceAnswer(void)
{
	UWORD timer;

	/**********************/
	/* ＦＡＸ／ＴＥＬ待機 */
	/**********************/
	if ( AttemptRxModeSwitch == SYS_FAX_TEL_READY ) {
		/********************************************************/
		/** -------音声ﾒｯｾｰｼﾞ①  11.3 sec -------------        **/
		/* この電話はﾌｧｸｼﾐﾘに接続されています｡ﾋﾟｰという音の後に	*/
		/* 送信して下さい｡電話をご利用の方は,そのまましばらくお	*/
		/* 待ち下さい｡											*/
		/*------------------------------------------------------*/
		VoicePrompt(VOICE_A);
		/*************************************/
		/** 音声ﾒｯｾｰｼﾞ① - CED Wait 2.5 sec **/
		/*************************************/
		timer = (UWORD)2500;
		FaxTimer( timer );
		if( !CMN_CheckMemoryReceiveEnable() ){			/** 自動受信不可（メモリなし）*/
			/*---------------------------------------------*/
			/* メモリがない場合は､通信タスクの方で､擬似ベルを鳴らしオペレータを呼び出します */
			/*        通信タスクにＦＳＫ受信を通知         */
			/*---------------------------------------------*/
			return (RECEIVE);
		}
		else if (CMN_CheckMemoryReceiveEnable()) {	/* 受信可能 */
			SYS_FaxMelodyFlag = YES;
			FaxTransmitCED();				/** ＣＥＤ送出 */
			SYS_FaxMelodyFlag = NO;
			/*----------------------------------------------------*/
			/*	CED - NSF Wait 75±20ms[CCITT/FTZ18TR53 Fig11-1]  */
			/*----------------------------------------------------*/
			timer = (UWORD)(CHK_WaitAfterDIS());		/** CED送出後NSF送出までの時間75m秒/1000m秒の獲得 */
			TimerCutStatus = 1;
			FaxTimer( timer );
			/*------------*/
			/*	Phase B1  */
			/*------------*/
			SYS_PhaseB1Flag = YES;
			FaxRxPhaseB1();						/** 受信フェーズＢ１ */
			SYS_PhaseB1Flag = NO;
			if (FaxComPerformingFlag == 0) {
				/*---------------------------------------------*/
				/**        通信タスクにＦＳＫ受信を通知        */
				/*---------------------------------------------*/
				if (SYS_PhaseB1StopWaitFlag == 1) {	/* OH検出 */
					return (OK_SLEEP);
				}
				else if (SYS_PhaseB1StopWaitFlag == 2) {	/* BUSY検出 */
					return (DETECT_BUSY);
				}
			}
			if ( FaxComPerformingFlag != 0) {	/* 相手機がＦＡＸ */
				/*---------------------------------------------*/
				/**        通信タスクにＦＳＫ受信を通知        */
				/*---------------------------------------------*/
				return (RECEIVE);
			}
			/***************************/
			/** 音声ﾒｯｾｰｼﾞ②  8.6 sec **/
			/***************************/
			/*------------------------------------------------------*/
			/* ただいま,呼び出しております｡そのまましばらくお待ちく	*/
			/* ださい｡												*/
			/*------------------------------------------------------*/
			VoicePrompt(VOICE_B);
			/*****************************************/
			/** 音声ﾒｯｾｰｼﾞ② - 保留音 Wait 75±20ms **/
			/*****************************************/
			timer = ( UWORD )75;
			FaxTimer( timer );
			/************************/
			/** 保留音送出  24 sec **/
			/************************/
			SYS_FaxMelodyFlag = YES;
			MDM_MelodyExe();
			timer = ( UWORD )22000;	/* ２４秒 */
			FaxTimer( timer );
			MDM_ConfigReset();	/* 保留ﾒﾛﾃﾞｨ解除 */
			SYS_FaxMelodyFlag = NO;
			/*---------------------------------------------*/
			/**        通信タスクにタイムアウトを通知      */
			/*---------------------------------------------*/
			return (TMOUT_RESP);
		}
	}
	/**********************/
	/* ＴＥＬ／ＦＡＸ待機 */
	/**********************/
	else if( AttemptRxModeSwitch == SYS_TEL_FAX_READY ){
		/************************/
		/** Tel/Fax 待機	   **/
		/************************/
		if (CHK_VoiceMessageON()) { /* 音声応答メッセージ送出ＯＮなら */
			/****************************/
			/** 音声ﾒｯｾｰｼﾞ①  7.3 sec **/
			/****************************/
			/*--------------------------------------------------*/
			/* ただいま,電話を呼び出しております｡ﾌｧｸｼﾐﾘをご利用	*/
			/* の方は,そのまましばらくお待ちください｡			*/
			/*--------------------------------------------------*/
			VoicePrompt(VOICE_D);
			/******************************************************************/
			/** 音声ﾒｯｾｰｼﾞ①- 疑似RBT送出 Wait 1 sec + CNG 検出期間( 2 sec ) **/
			/******************************************************************/
			timer = ( UWORD )1000;
			FaxTimer( timer );
		}
		return(0);
	}
}
 #endif	/* End of (PRO_MODEM == R288F) */
#endif
