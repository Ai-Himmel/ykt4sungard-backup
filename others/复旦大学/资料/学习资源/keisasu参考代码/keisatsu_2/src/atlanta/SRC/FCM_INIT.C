/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA	ANZUを移植										 */
/*	ファイル名	 : FCM_INIT.C												 */
/*	モジュール	 : InitializeBaudrate()										 */
/*				 : InitializeFaxCom()										 */
/*	作成者		 : 山口														 */
/*	日	付		 : 1996/11/19												 */
/*	概	要		 : ＦＡＸ通信初期化モジュール								 */
/*				 :															 */
/*	修正履歴	 :															 */
/*---------------------------------------------------------------------------*/

/*------------------------------------------------------------------*/
/* 警告！！															*/
/*		   条件コンパイルには注意しましょう！！						*/
/*		   機能の無い機種については共通関数でリターン値が機能無しで */
/*		   かえってくると言う前提で組んでいます						*/
/*------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysrxsw.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\memsw\define\mem_sw_b.h" /*1996/04/17 Eguchi */
#include "\src\memsw\define\mem_sw_c.h" /* 1996/04/17 Eguchi */
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\message.h"
#include "\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include "\src\atlanta\define\uni_pro.h"

#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/08/04 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/04 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* 1996/07/19 By N.Sakamoto */
#endif



#if (PRO_PAT_JOURNAL == ENABLE)			/* 1995/01/27 */
 #include "\src\atlanta\define\pat_def.h"	/* Add by T.Nose 1995/12/15 */
 #include "\src\atlanta\define\pat_pro.h"
#endif

#include "\src\atlanta\define\MNTSW_C.h"	/* 1998/02/09  By T.Yamaguchi */

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\fcm_data.h"

#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
#include "\src\atlanta\define\mntsw_b.h"
#endif
#if (PRO_FORCE_FINE_RX_SWITCH == ENABLE) /* メモリスイッチで強制的にファインにする機能を試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
#include "\src\atlanta\define\mntsw_e.h"
#endif
#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
 #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_data.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"	/* Add by T.Soneoka 1999/03/12 */
 #elif defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_data.h"
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h"	/* Add by T.Soneoka 1999/03/12 */
 #else
#include "\src\atlanta\hinoki\ext_v\scn_data.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
 #endif
#include "\src\atlanta\ext_v\cdc_data.h"
#endif

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
  #include "\src\atlanta\ext_v\cdc_data.h"
  #include "\src\atlanta\ext_v\lst_data.h"
 #endif
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/23 K.Kawata*/
#include "\src\atlanta\define\unisw_c.h" /* 1999/2/22 K.Kawata */
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL)
#include "\src\atlanta\define\unisw_c.h" /* added by H.Hirao 1999/02/26 */
#endif
/*************************************************************************
	module		:[ ＦＡＸ通信で使用する Baudrate の初期化を行う。]
	function	:[]
	commom		:[
		AvailableTxBaudRate		: 機器の送信可能なボーレイト
		AvailableRxBaudRate		: 機器の受信可能なボーレイト
		AttemptTxBaudRate		: 試行送信ボーレイト
		AttemptRxBaudRate		: 試行受信ボーレイト
		PartnerAbility0			: メモリスイッチＢ０のコピー
	]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[1994/01/17]
	author		:[山口]
*************************************************************************/
void	InitializeBaudrate(void)
{
	UBYTE	 partner_baudrate;
	UBYTE	type;	/*	Add By O.Kimoto 1997/10/07	*/

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/11 */
	UWORD			signaling_rate;
#endif /* (PRO_TX_SPEED == V34) */

	/*--------------------*/
	/*	Codec & BaudRate  */
	/*--------------------*/

#if (PRO_MODEM == ORANGE3)
	AvailableTxBaudRate				= BPS14400_V17;			/** 送信可能ボーレイト */
	AvailableRxBaudRate				= BPS14400_V17;			/** 受信可能ボーレイト */
	AttemptTxBaudRate				= BPS14400_V17;			/** 試行送信ボーレイト */
	AttemptRxBaudRate				= BPS14400_V17;			/** 試行受信ボーレイト */
#endif

#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/08/11 */
	/*---------------------*/
	/*  DataSignalingRate  */
	/*---------------------*/
	/** ホスト側の要求しているデータ信号速度獲得 */

	SYS_DataSignalingRate = 0x00;
	CMN_SetDataSignalingRate(DATA_SIGNALING_RATE_ALL_BIT);
	if (CHK_V34SiganalRateV34Mask()) {	/* UNISW D3:6 V17固定 1997/01/26 */
		CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V34_BIT);
	}
#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
	if (SYB_MaintenanceSwitch[MNT_SW_B8] & DISABLE_V29_SIGNALING_RATE) {
		CMN_ResetDataSignalingRate(DATA_SIGNALING_RATE_V29_BIT);
	}
#endif

	signaling_rate = CMN_GetDataSignalingRate();

	if (signaling_rate & 0x0001) {	/* Ｖ３４の時のボーレイトはモデムがオートで行う */
		AvailableTxBaudRate	= BPS14400_V17;			/** 送信可能ボーレイト */
		AvailableRxBaudRate	= BPS14400_V17;			/** 受信可能ボーレイト */
		AttemptTxBaudRate	= BPS14400_V17;			/** 試行送信ボーレイト */
		AttemptRxBaudRate	= BPS14400_V17;			/** 試行受信ボーレイト */
		V8ProcedureRequestFlag = 1;					/** Ｖ８手順移行要求セット */
	}
	else if (signaling_rate & 0x0002) {	/** Ｖ１７ */
		AvailableTxBaudRate	= BPS14400_V17;			/** 送信可能ボーレイト */
		AvailableRxBaudRate	= BPS14400_V17;			/** 受信可能ボーレイト */
		AttemptTxBaudRate	= BPS14400_V17;			/** 試行送信ボーレイト */
		AttemptRxBaudRate	= BPS14400_V17;			/** 試行受信ボーレイト */
		V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求クリア */
	}
	else if (signaling_rate & 0x0004) {	/** Ｖ２９ */
		AvailableTxBaudRate	= BPS9600_V29;			/** 送信可能ボーレイト */
		AvailableRxBaudRate	= BPS9600_V29;			/** 受信可能ボーレイト */
		AttemptTxBaudRate	= BPS9600_V29;			/** 試行送信ボーレイト */
		AttemptRxBaudRate	= BPS9600_V29;			/** 試行受信ボーレイト */
		V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求クリア */
	}
	else if (signaling_rate & 0x0008) {	/** Ｖ２７ */
		AvailableTxBaudRate	= BPS4800_V27;			/** 送信可能ボーレイト */
		AvailableRxBaudRate	= BPS4800_V27;			/** 受信可能ボーレイト */
		AttemptTxBaudRate	= BPS4800_V27;			/** 試行送信ボーレイト */
		AttemptRxBaudRate	= BPS4800_V27;			/** 試行受信ボーレイト */
		V8ProcedureRequestFlag = 0;					/** Ｖ８手順移行要求クリア */
	}
	else {	/* This Path is Nothing. */
		AvailableTxBaudRate	= BPS14400_V17;			/** 送信可能ボーレイト */
		AvailableRxBaudRate	= BPS14400_V17;			/** 受信可能ボーレイト */
		AttemptTxBaudRate	= BPS14400_V17;			/** 試行送信ボーレイト */
		AttemptRxBaudRate	= BPS14400_V17;			/** 試行受信ボーレイト */
		V8ProcedureRequestFlag = 1;					/** Ｖ８手順移行要求セット */
	}

	/*--------------------*/
	/* 送信データ信号速度 */
	/*--------------------*/
	partner_baudrate = FCM_PtnrChkTxBPS();	/** 送信速度 */

	if (partner_baudrate > 5) {
		partner_baudrate = 5;
	}

	switch ( AvailableTxBaudRate ){		/** 送信可能ボーレイト判定 */
		case BPS14400_V17:				/** 14400_V17 */
		case BPS14400_V33:				/** 14400_V33 */
			break;

		case BPS12000_V17:				/** 12000_V17 */
		case BPS12000_V33:				/** 12000_V33 */
			if( partner_baudrate == 5 ){		/** 14400BPS */
				partner_baudrate = 4;					/** 12000BPS SET */
			}
			 break;

		case BPS9600_V17:				/** 9600_V17 */
		case BPS9600_V29:				/** 9600_V29 */
			if(( partner_baudrate == 5 )
			|| ( partner_baudrate == 4 )){	/** 14400BPS または 12000BPS */

				partner_baudrate = 3;					/** 9600BPS SET */
			}
			break;

		case BPS7200_V17:				/** 7200_V17 */
		case BPS7200_V29:				/** 7200_V29 */
			if(( partner_baudrate == 5)
			|| ( partner_baudrate == 4 )
			|| ( partner_baudrate == 3 )){	/** 14400BPS または 12000BPS または 9600BPS */

				partner_baudrate = 2;		/** 7200BPS SET */
			}
			break;
		case BPS4800_V27:				/** 4800BPS */
			if(( partner_baudrate == 5 )
			|| ( partner_baudrate == 4 )
			|| ( partner_baudrate == 3 )
			|| ( partner_baudrate == 2 )){	/** 7200BPS以上 */

				partner_baudrate = 1;						/** 4800BPS SET */
			}
			break;

		case BPS2400_V27:				/** 2400BPS */
			if(( partner_baudrate == 5 )
			|| ( partner_baudrate == 4 )
			|| ( partner_baudrate == 3 )
			|| ( partner_baudrate == 2 )
			|| ( partner_baudrate == 1 )){		/** 4800BPS以上 */

				partner_baudrate = 0;							/** 2400BPS SET */
			}
			break;
	}

	switch (partner_baudrate) {		/** 送信速度判定 */
	case MEM_TX_BPS144:
		if( FCM_PtnrChk_DCS_V33AllHold() ) {
			AvailableTxBaudRate = BPS14400_V33;
		}
		else{
			AvailableTxBaudRate = BPS14400_V17;
		}
		break;
	case MEM_TX_BPS120:
		if( FCM_PtnrChk_DCS_V33AllHold() ) {
			AvailableTxBaudRate = BPS12000_V33;
		}
		else{
			AvailableTxBaudRate = BPS12000_V17;
		}
		break;
	case MEM_TX_BPS096:
		AvailableTxBaudRate = BPS9600_V29;
#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
		if (SYB_MaintenanceSwitch[MNT_SW_B8] & DISABLE_V29_SIGNALING_RATE) {
			AvailableTxBaudRate = BPS9600_V17;
		}
#endif
		break;
	case MEM_TX_BPS072:
		AvailableTxBaudRate = BPS7200_V29;
#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
		if (SYB_MaintenanceSwitch[MNT_SW_B8] & DISABLE_V29_SIGNALING_RATE) {
			AvailableTxBaudRate = BPS7200_V17;
		}
#endif
		break;
	case MEM_TX_BPS048:
		AvailableTxBaudRate = BPS4800_V27;
		break;
	case MEM_TX_BPS024:
		AvailableTxBaudRate = BPS2400_V27;
		break;

	/* add 1997/01/27 for TEST */
	case MEM_TX_BPS168:			/* 28.8kが入ってきたら要変更 */
	case MEM_TX_BPS192:
	case MEM_TX_BPS216:
	case MEM_TX_BPS240:
	case MEM_TX_BPS264:
	case MEM_TX_BPS288:
	case MEM_TX_BPS312:
	case MEM_TX_BPS336:
	default		  :
		if( FCM_PtnrChk_DCS_V33AllHold() ) {
			AvailableTxBaudRate = BPS14400_V33;
		}
		else{
			AvailableTxBaudRate = BPS14400_V17;
		}
		break;
	 }

#else /* (PRO_TX_SPEED == V34) */

	switch (FCM_PtnrChkTxBPS()) { /** 送信速度判定 V8手順の処理を入れる事 */
	case MEM_TX_BPS144:
		if( FCM_PtnrChk_DCS_V33AllHold() ) {
			AvailableTxBaudRate = BPS14400_V33;
		}
		else{
			AvailableTxBaudRate = BPS14400_V17;
		}
		break;
	case MEM_TX_BPS120:
		if( FCM_PtnrChk_DCS_V33AllHold() ) {
			AvailableTxBaudRate = BPS12000_V33;
		}
		else{
			AvailableTxBaudRate = BPS12000_V17;
		}
		break;
	case MEM_TX_BPS096:
		AvailableTxBaudRate = BPS9600_V29;
#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
		if (SYB_MaintenanceSwitch[MNT_SW_B8] & DISABLE_V29_SIGNALING_RATE) {
			AvailableTxBaudRate = BPS9600_V17;
		}
#endif
		break;
	case MEM_TX_BPS072:
		AvailableTxBaudRate = BPS7200_V29;
#if (PRO_PROHIBIT_V29_TX_SWITCH == ENABLE) /* 試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
		if (SYB_MaintenanceSwitch[MNT_SW_B8] & DISABLE_V29_SIGNALING_RATE) {
			AvailableTxBaudRate = BPS7200_V17;
		}
#endif
		break;
	case MEM_TX_BPS048:
		AvailableTxBaudRate = BPS4800_V27;
		break;
	case MEM_TX_BPS024:
		AvailableTxBaudRate = BPS2400_V27;
		break;
	case MEM_TX_BPS168:			/* 28.8kが入ってきたら要変更 */
	case MEM_TX_BPS192:
	case MEM_TX_BPS216:
	case MEM_TX_BPS240:
	case MEM_TX_BPS264:
	case MEM_TX_BPS288:
	case MEM_TX_BPS312:
	case MEM_TX_BPS336:
	default		  :
		if( FCM_PtnrChk_DCS_V33AllHold() ) {
			AvailableTxBaudRate = BPS14400_V33;
		}
		else{
			AvailableTxBaudRate = BPS14400_V17;
		}
		break;
	}
#endif /* (PRO_TX_SPEED == V34) */

	/*----------------*/
	/* 受信ボーレイト */
	/*----------------*/
	partner_baudrate = CHK_RxBPS();				/** 受信速度取得(受信メモリスイッチの内容) */

	/* V8手順の処理を追加する事 */

#if (PRO_TX_SPEED == V34 ) /* Added by H.Kubo 1997/08/11 */
/* Also refer to SYS_DataSignalingRate to decide AvailableRxBaudRate.*/

	if (partner_baudrate > 5) {
		partner_baudrate = 5;
	}

	switch ( AvailableRxBaudRate ){			/** 受信可能ボーレイト判定 */
		case BPS14400_V17:					/** 14400_V17 */
		case BPS14400_V33:					/** 14400_V33 */
			 break;

		case BPS12000_V17:					/** 12000_V17 */
		case BPS12000_V33:					/** 12000_V33 */
		case BPS9600_V17:					/** 9600_V17 */
		case BPS9600_V29:					/** 9600_V29 */
			if(( partner_baudrate == 5 )
			|| ( partner_baudrate == 4 )){	/** メモリスイッチ 14400_V33 or 14400_V17 */

				partner_baudrate = 3;		/** 9600BPS SET */
			}
			break;

		case BPS7200_V17:					/** 7200_V17 */
		case BPS7200_V29:					/** 7200_V29 */
		case BPS4800_V27:					/** 4800BPS */
			if(( partner_baudrate == 5 )
			|| ( partner_baudrate == 4 )
			|| ( partner_baudrate == 3 )
			|| ( partner_baudrate == 2 )){	/** メモリスイッチ 7200BPS以上 */

				partner_baudrate = 1;			/** 4800BPS SET */
			}
			break;

		case BPS2400_V27:					/** 2400BPS */
			if(( partner_baudrate == 5 )
			|| ( partner_baudrate == 4 )
			|| ( partner_baudrate == 3 )
			|| ( partner_baudrate == 2 )
			|| ( partner_baudrate == 1 )){		/** メモリスイッチ 4800BPS以上 */

				partner_baudrate = 0;				/** 2400BPS SET */
			}
			break;
	}
#endif /* (PRO_TX_SPEED == V34 ) */

	switch (partner_baudrate) {		/** 受信速度判定 */
	case MEM_RX_BPS144:
	case MEM_RX_BPS120:	/* -------- V34 の能力がある場合は要変更  -------------------- */
		/* 受信可能ボーレイトはV17のみとする V33のパスは無くした '96.04.17	BY T.Y */
		AvailableRxBaudRate = BPS14400_V17;		/** 受信可能ボーレイト 14400_V17 */
		break;
	case MEM_RX_BPS096:
	case MEM_RX_BPS072:	/* -------- V34 の能力がある場合は要変更  -------------------- */
		AvailableRxBaudRate = BPS9600_V29;		/** 受信可能ボーレイト 9600_V29 */
		break;
	case MEM_RX_BPS048:
		AvailableRxBaudRate = BPS4800_V27;		/** 受信可能ボーレイト 4800_V27 */
		break;
	case MEM_RX_BPS024:
		AvailableRxBaudRate = BPS2400_V27;		/** 受信可能ボーレイト 2400_V27フォールバックモード */
		break;
	case MEM_RX_BPS168:			/* 28.8kが入ってきたら要変更 */
	case MEM_RX_BPS192:
	case MEM_RX_BPS216:
	case MEM_RX_BPS240:
	case MEM_RX_BPS264:
	case MEM_RX_BPS288:
	case MEM_RX_BPS312:
	case MEM_RX_BPS336:
	default		  :
		AvailableRxBaudRate = BPS14400_V17;		/** 受信可能ボーレイト 14400_V17 */
		break;
	}
}


/*************************************************************************
	module		:[ ＦＡＸ通信で使用する変数の初期化を行う。]
	function	:[]
	commom		:[]
	condition	:[]
	comment		:[]
	return		:[なし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void	InitializeFaxComFlsRom(void)
#else
void	InitializeFaxCom(void)
#endif
{
	UBYTE	  count;

	OwnMakerCode = MURATA_CODE;						/** 自機メーカーコード */

	SYS_FaxCommStage = 0;							/* 通信遷移状態 *//* 1997/11/29 */

#if (PRO_FIP == ENABLE)
	SYS_FaxComFIP_RxActiveFlag = 0;						/** ＦＩＰ 受信 */
	SYS_FaxComFIP_RxCode = 0;							/** ＦＩＰ 受信可能符合化能力 25.Jly'94 Y.Suzuki */
	SYS_FaxComFIP_RxSize = 0;							/** ＦＩＰ 受信可能記録巾能力 25.Jly'94 Y.Suzuki */
	SYS_FaxComFIP_RxMode = 0;							/** ＦＩＰ 受信可能線密度能力 25.Jly'94 Y.Suzuki */
	SYS_FaxComFIP_RxMilliInch = 0;						/** ＦＩＰ 受信可能線密度インチ／ミリ能力 25.Jly'94 Y.Suzuki */
#endif

	/*--------------/
	/** 交信タイプ */
	/*-------------*/
#if (PRO_PRINTER_RX == DISABLE)
	FaxComRxType					= MEMORY_RX;					/** 受信原稿種別 */
#else
	FaxComRxType					= PRINTER_RX;					/** 受信原稿種別 */
#endif

	SYS_FaxComTxType				= 0;							/** 送信原稿種別 */
	SYS_FaxComType					= 0;							/** 交信種別 */

	/*------------*/
	/* 確定モード */
	/*------------*/
	FinalTxMode						= 0;							/**	確定送信モード	*/
	FinalRxMode						= 0;							/**	確定受信モード	*/

	/*------------------------------------------*/
	/* 中継指示送信時のみ参照					*/
	/* 中継指示可能   = 1						*/
	/* 中継指示不可能 = 0	杏では使ってない	*/
	/*------------------------------------------*/
	FaxTxCommand					= 0;			/** 確定送信コマンド *//* 中継同報指示とは限らないので	 0 ｲﾆｼｬﾗｲｽﾞ */

	TxSmType						= 0;			/** 送信方法	スキャナ、メモリ、カバー、ＲＣＲ */
	RxPmType						= 0;			/** 受信方法	プリンタ、メモリ */
	PollingTxType					= 0;			/** ポーリング送信原稿種別	皐月はセット不要 */

	/*-----------*/
	/** 会話予約 */
	/*-----------*/
	if (SYB_MaintenanceSwitch[14] & 0x80) {
		SYS_VoiceSwitch	 = 1;	/* テスト用に強制的に会話予約する 1997/09/10 */
	}
	else {
		SYS_VoiceSwitch					= 0;			/**	「会話予約」キー入力フラグ	*/	/* 竹内 Jul.07.1994 */
	}
	SYS_VoiceCallAccepted			= 0;			/** 「会話予約」受付フラグ */

	/*-----------*/
	/** 交信制御 */
	/*-----------*/
	FaxComTxPerformingFlag			= 0;			/** 「送信中」フラグ */
	FaxComRxPerformingFlag			= 0;			/** 「受信」フラグ */
	FaxComPerformingFlag			= 1;			/** 「通信中」フラグ */

#if defined(DEU)
		FaxTelOffHookFlag			= 0;
		RTN_ReceiveCounter			= 0;			/** ＲＴＮ受信回数 */
#endif

	/*------------*/
	/** 交信 MODE */
	/*------------*/
	FirstTxMode						= SYS_FINE;		/** 送信モード	（次ページ目） */
	TxMode							= SYS_NORMAL;	/** 送信モード	（最後に送ったページの、モード ノーマルにしておく 15.Mar'94 Y.Suzuki） */
	RxMode							= SYS_NORMAL;	/** 受信モード	（最後に送ったページの、モード ノーマルにしておく 15.Mar'94 Y.Suzuki） */
	TxModeMethod					= 0;			/*	送信モード（インチ／ミリ）23.Mar'94 Y.Suzuki	*/
	RxModeMethod					= 0;			/*	受信モード（インチ／ミリ）23.Mar'94 Y.Suzuki	*/

	/*--------*/
	/* 原稿幅 */
	/*--------*/
	TxWidth							= 0;			/**	確定送信原稿幅	*/
	RxWidth							= 0;			/**	確定受信原稿幅	*/
	DocWidth						= 0;			/**	原稿幅			*/

	/*---------------*/
	/** FAX/TEL MODE */
	/*---------------*/
	FaxTelOffHook					= 0;			/*	会話予約中にオフフック検出済みフラグ	*/
	FaxTelOffHookTEL1Flag			= 0;			/** TEL1 オフフック検出フラグ */
	FaxTelOffHookTEL2Flag			= 0;			/** TEL2 オフフック検出フラグ */
	OffHookDetectStopFlag			= 0;			/** オフフック検出ストップフラグ */
/*	GenerateRingSignalStopFlag		= 0;		*/	/** 擬似ベル鳴動中のストップキー入力フラグ */
	FaxTelResult					= 0;			/** ＴＥＬ／ＦＡＸ戻り値 */

#if (PRO_BT_DET_WHILE_RBT == ENABLE) /* 疑似ベル鳴動中のBusyTone検出 2001/10/03 M.Matsumoto *//* Add By O.Kimoto 2002/03/11 */
	IsDetectBusyTone = CHK_UNI_DetectBusyTone();
#endif

	/*------------*/
	/** Tx Memory */
	/*------------*/
	TxMemoryFileItem				= 0;			/** メモリ送信を行う原稿のファイルアイテム */
	TxMemoryFileNo[0]				= 0xFFFF;		/** メモリ送信を行う原稿のファイルナンバー */
	TxMemoryFileCurrentExecutingNo	= 0;			/** 現在実行中のメモリ送信原稿のファイルナンバー */
	TxMemoryFileNextExecutingNo		= 0;			/** 次回送信予定のメモリ送信原稿のファイルナンバー */
	TxMemoryFilePage				= 0;			/** メモリ送信を行う原稿のファイルページ */
	UpdateTxPageMode				= 0;			/** ページ数更新時の更新項目 */
	TxInterMemoryFlag				= 0;			/** メモリ間通信を示すフラグ */
	PollingTxFilePage[0]			= 0xFFFF;		/** ポーリング送信の際の総送信ページ数 */
	GrayModeFlag					= 0;			/**	中間調の場合--YES	*/
	ScanTxGrayMode					= 0;			/*	ANZU 相手の能力、300DPI/ｲﾝﾁ なら 300DPI その他は、FINE 19.Oct'94 */
	TxMemoryFileBoxNumber			= MEM_IGNORE_BOX_NUMBER;/* 1997/03/20  By T.Yamaguchi */
	TxFinalPageNumber				= 0;			/* ICHOU変更 送信最適化処理 by T.Soneoka 1996/10/01 */

	/*----------------------*/
	/* 画質不良ページクリア */
	/*----------------------*/
	for(count = 0; count < SYS_ERROR_PAGE; count ++){
		TxResponsedRTN_PageSign[ count ] = 0;				/** ＲＴＮ／ＰＩＮ を応答された送信ページ（ビット指定） */
	}
	/* RelayedTxDocumentStatus[0]= NULL; 95/02/22*/	/**	中継配信原稿の状態を表す'94/1/26鈴木	  */
													/*	 ↑↑↑↑ には、使ってない。			  */
													/*	 ので不達通知用コマンドファイルNO記憶用に */
													/*	 使うことにする。	   95/02/21 Y.Suzuki  */

	TxOptionFCF						= 0;			/**	ポストメッセージ送信拡張ＦＣＦフレーム	*/
	TxFCF							= 0;			/**	ポストメッセージ送信ＦＣＦフレーム		*/
	RxOptionFCF						= 0;			/**	ポストメッセージ受信拡張ＦＣＦフレーム	*/
	RxFCF							= 0;			/**	ポストメッセージ受信ＦＣＦフレーム		*/

	/*------------*/
	/** Rx Memory */
	/*------------*/
#if (PRO_PRINTER_RX == DISABLE)		/*	defined(KIRI) ソースで機種名はアカンよー	竹内 Jun.08.1994	*/
  #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/25 K.Kawata*/
	if ((CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) || (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX)) {
		SYS_RxMemoryFileItem = NULL;
	}
	else {
		SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;	/** メモリ受信を行う原稿のファイルアイテム */
	}
  #else
	SYS_RxMemoryFileItem			= SYS_MEM_RX_FILE;	/** メモリ受信を行う原稿のファイルアイテム */
  #endif
#else
	SYS_RxMemoryFileItem			= 0;			/** メモリ受信を行う原稿のファイルアイテム */
#endif
	/* 95/03/31 Y.Suzuki 親展受信ﾎﾞｯｸｽなしｺﾝﾊﾟﾁｴﾗｰ時ﾎﾞｯｸｽ1が未登録の場合､FCM_LASTでﾎﾞｯｸｽ1が登録されてしまう。	*/
	/* SYS_RxMemoryFileNo を FF ｸﾘｱし親展受信でｺﾝﾊﾟﾁｴﾗｰとなった場合、FCM_LASTの処理を回避する。					*/
	SYS_RxMemoryFileNo				= 0xFF;			/** メモリ受信を行う原稿のファイルナンバー */

	SYS_RxMemoryFilePage			= 0;			/** メモリ受信を行う原稿のファイルページ */
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/13  By T.Yamaguchi */
	SYS_RxMemoryFileBoxNumber		= 0;			/** メモリ受信を行なう原稿のＢＯＸ番号 */
/* #endif */
	RxPrinterDirectFlag				= 0;			/** ダイレクトプリンタ受信を示すフラグ */
	TxPageTotalLineCount			= 0;			/**	送信トータルライン数（スキャナ送信用）	*/
	RxPageIndexNo					= 0;			/** メモリ受信時のファイルインデックス番号 */
	RxWholePageCompletedFlag		= 0;			/** 「１物理ページ受信完了」フラグ */
	TxPageDataSetFlag				= 0;			/**	「ページオープン中（済み）」フラグ	*/
/*	RxRTN_Flag						= 0; */			/** 現在受信ページの画質不良フラグ（画質不良のときセットする） */
/*	ecm_rtc_flag					= 0; */			/** RTC符号64K股裂き制御 */
	HurryUpFaxComFlag				= 0;			/** 通信中の蓄積を強制的に止める(通信の優先順位を強制的に高くするフラグ) */
	RxEOP_ReceiveFlag				= 0;			/**	「交信終了許可（ＥＯＰ受信）」フラグ	*/
	RxEOR_ReceiveFlag				= 0;			/** ＥＯＲ受信済みフラグ */
	/*	Y.SUZUKI 17.Feb'94 メモリデュアルオープンのため追加	*/
	SYS_RxPrintFilePage				= 0;			/** 中継指示受信プリントとリモートＦＡＸ同時プリントで使用 */
	SYS_RxPrintFileNo				= 0;			/** 中継指示受信プリントとリモートＦＡＸ同時プリントで使用 */
	SYS_RxPrintFileItem				= 0;			/** 中継指示受信プリントとリモートＦＡＸ同時プリントで使用 */
	SYS_RxPrintFileBoxNumber		= 0;			/* 1997/01/30  By T.Yamaguchi */

#if (PRO_PRINTER_RX == ENABLE)
	PrinterRxPreOpenFlag			= 0;			/**	プリンタ受信用フラグ初期化	Apr.22.1994	*/
#endif

	PollingTxFirstPageFlag			= 0;			/**	ポーリング送信先頭ページフラグ	*/
	PRI_Q_Count						= 0;			/**	ＰＲＩ－Ｑカウント	*/

	/*------------------*/
	/** Compatible/HDLC */
	/*------------------*/
	StandardID[0]					= NULL;					/** 交信相手機の標準ＩＤ */
	NonStandardID[0]				= NULL;					/** 交信相手機の村田（／ＯＥＭ）ＩＤ */
#if 0	/* 1996/06/07 T.Yamaguchi */
	BackUpStandardID[0]				= NULL;					/**	交信相手機の標準ＩＤ（バックアップ）	*/
#endif
/* #if (PRO_F_CODE == ENABLE) */
	PasswordFrameID[0]              = NULL;
	SelectivePollingFrameID[0]      = NULL;
	SubaddressFrameID[0]            = NULL;
/* #endif */
/*	LastFCF							= 0;		*/			/** 最後に受信したＦＣＦ */
	DIS_ReceivedFlag				= 0;					/** DIS DCS 受信フラグ	*/
	MakerCodeRxFlag					= 0;					/** 「村田メーカコード受信」フラグ */
	FX_CodeRxFlag					= 0;					/**	「ＦＸメーカコード受信」フラグ	YES/NO	*/
	RxFirstTimeCompatibleCheckFlag	= 1;					/** 受信コンパチブルチェック回数 */
	ReceiveCommandFlagDetectFlag	= 0;					/** HDLC関係 */
	ReceiveCommandTimerStartFlag	= 0;					/** HDLC関係 */
	TransmitCommandFlag				= 0;					/** HDLC関係 */
	AD_Result						= 0;					/**	オートダイアラー戻り値	*/

	RxFrameMessage1					= 0;					/**	受信フレーム種別	*/
	PRI_Q_RxFlag					= 0;					/**	ＰＲＩ＿Ｑ受信フラグ	*/

	ReceiveResponseFlag				= 0;					/**	応答受信ありなしフラグ		*/
	ReceiveCommandFlag				= 0;					/**	命令受信ありなしフラグ		*/
	UpdatePageInformationFlag		= 0;					/**	送信ページ情報を更新する／しないフラグ	*/
	FSK_FirstReceivedFlag			= 0;					/** 相手機がＦＡＸであると確定した 96/05/17 By T.Yamaguchi */
	/*----------------*/
	/** Memory Switch */
	/*----------------*/
	PartnerAbility0					= SYS_MemorySwitch[10];								/** メモリスイッチＢ０ 送信 */
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/24 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
		PartnerAbility1				= SYS_MemorySwitch[11];								/** メモリスイッチＢ１ 送信 */
	}
	else {
		PartnerAbility1				= SYS_MemorySwitch[14];								/** メモリスイッチＢ４ 送信 */
	}
#else
	PartnerAbility1					= SYS_MemorySwitch[11];								/** メモリスイッチＢ１ 送信 */
#endif		/* End of (defined (KEISATSU)) */
	PartnerAbility2					= SYS_MemorySwitch[12];								/** メモリスイッチＢ２ 送信 */
	PartnerAbility3					= (UBYTE)(SYS_MemorySwitch[13] & 0xf8);				/** メモリスイッチＢ３ 送信 */

	TxRetrainingFlag				= 0;					/**	「再トレーニング」フラグ	*/
	TxRetransmitFlag				= 0;					/**	「再送信」フラグ	*/
	TxModeChangedFlag				= 0;					/**	「モード変更」フラグ	*/
	RxModeChangeRequestedFlag		= 0;					/**	「受信モード変更要求」フラグ	*/

	DiagByteCounter					= 0;					/**	リモート診断関係	*/
	TxMethodFlag					= 0;					/**	送信方式確定	*/
	BaudrateFlag					= 0;					/**	ボーレイト確定	*/

	/*---------------------*/
	/** 短縮ハンドシェーク */
	/*---------------------*/
	SDCS_TransmitFlag				= 0;			/** 短縮ハンドシェーク送信フラグ */
	TxSpeedHandshakeFlag			= 0;			/** 短縮ハンドシェーク送信機能フラグ */
	RxSpeedHandshakeFlag			= 0;			/** 短縮ハンドシェーク受信フラグ */
	PartnerSpeedHandshakeAbility	= 0;			/** 相手機が短縮ハンドシェーク機能の有無を示すフラグ */
#if (PRO_SPEED_EX == ENABLE)
	PartnerSpeedHandshakeExAbility	= 0;			/** 相手機が新短縮ハンドシェーク機能の有無を示すフラグ */
	ArrivalSignalToneTransmitFlag	= 0;			/** 着信トーン送出の有無を示すフラグ  By T.Y */
#endif
#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
	PartnerSpeedModeChangeAbility	= 0;			/*	相手機が短縮ハンドシェーク（モード変更）受信能力の有無を示す 96/06/01 By T.Yamaguchi */
#endif
	PostSpeedHandshakeFlag			= 0;			/** 後手順短縮ハンドシェーク送信機能フラグ	*/	/* 竹内 Jun.15.1994 */
	ShorteningPreambleFlag			= 0;			/**	プリアンブル短縮フラグ			*/	/* 竹内 Sep.07.1994 */

	/*------------------*/
	/** 相手機受信能力	*/
	/*------------------*/
	Partner300dpiAbility			= 0;			/** 相手機がR12*15.4L/mmの受信能力の有無を示すフラグ By T.Y 96.01.29 */
	PartnerEFineAbility				= 0;			/** 相手機がR12*11.55L/mmの受信能力の有無を示すフラグ By T.Y 96.06.14 */
	PartnerCipherAbility			= 0;			/** 相手機暗号化能力の有無を示すフラグ 1997/06/18  By T.Yamaguchi	 */

	/*-----------------------*/
	/** ジャンク・メイル防止 */
	/*-----------------------*/
	RxJunkMailFlag					= 0;			/** ジャンクメイル受信フラグ */

	/*---------------------*/
	/** Cover Page/TCR/RCR */
	/*---------------------*/
	TxCoverPageFlag					= 0;			/** カバーページ送信フラグ */
	SYS_RxReceiptRequestFlag		= 0;			/** 「受領証要求」フラグ */
	TxReceiptRequestFlag			= 0;			/** 「受領証送信」フラグ */
	TxRCR_Flag						= 0;			/** 相手機からの「受領証要求」フラグ */

	/*--------------------------*/
	/** 確定中継配信コマンドNo. */
	/*--------------------------*/
	RelayedCommandNo				= 0xFF;			/** 中継配信指示受信（中継同報の子機）の時展開したコマンドファイルナンバー */

	NonStdFrmName					= 0;			/*	MDM_Buffer[][]上へ受信した非標準各フレームの名前	*/
	ID_FrmName						= 0;			/*	MDM_Buffer[][]上へ受信したＩＤ各フレームの名前	*/
	StdFrmName						= 0;			/*	MDM_Buffer[][]上へ受信した標準各フレームの名前	*/
	PWD_FrmName                     = NO;
	SEP_FrmName                     = NO;
	SUB_FrmName						= NO;
	/*--------------------*/
	/** T30 モニタ & List */
	/*--------------------*/
	FaxComResult					= NO_ERROR;		/** 交信結果 */
#if 0	/* 1996/06/07 T.Yamaguchi */
//	BackUpFaxComResult				= 0;			/**	交信結果（バックアップ）	*/
#endif
	SYB_T30Monitor.WritePointer		= 0;			/** T30モニタ・データ用ライトポインタ */
	FaxComStartTime					= 0;			/** 交信開始時刻 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/28 Y.Murata */
	SYB_T30Monitor.ReadPointer = 0;
	SYB_T30Monitor.A_Pointer = 0;
	SYB_T30Monitor.B_Pointer = 0;
	SYB_T30Monitor.Flag = 0;
	SYB_T30Monitor.BK_Pointer1 = 0;
	SYB_T30Monitor.BK_Pointer2 = 0;
	SYB_T30Monitor.BK_Pointer3 = 0;
	SYB_T30Monitor.BK_Pointer4 = 0;
#endif

	/*
	** ＱＡＴ中に通信記録の通信時間が実際の時間と異なる不具合対策用
	** By S.Kawasaki 1996/09/02
	*/
	SYS_FCM_StartTime				= 0;

	FaxComPeriod					= 0;			/**	交信時間	*/
	FaxComTXorRX_Sign				= 0;			/** 送信／受信識別フラグ */
	SYS_TxTotalPage					= 0;			/** 全送信ページ数 */
	SYS_RxTotalPage					= 0;			/** 全受信ページ数 */
	FaxCompatibleErrorCode			= NO_ERROR;		/** 詳しいコンパチエラーコード */
	SYS_EyeQ_Level					= 0;			/** EYE_Q 値 パラメータ 22.Jun'94 Y.Suzuki*/
	SYB_T30_TxFrame300dpiFlag		= 0;			/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用 注．通信の頭でしか初期化しない */
	SYB_T30_RxFrame300dpiFlag		= 0;			/** T30モニタにHｰFine(R12*15.4l/mm)表示に使用			 1996/04/10 By T.Y	 */

	/*-------------*/
	/** 最大原稿長 */
	/*-------------*/
	FaxRxAvailableLength			= SYS_NO_LIMIT;		/** 受信可能最大原稿長 */
	FaxTxMaxLength					= SYS_NO_LIMIT;		/** 確定送信原稿長	基本は無制限 */
	FaxRxMaxLength					= SYS_NO_LIMIT;		/** 確定受信原稿長	基本は無制限 */

	/*-------------------*/
	/** ボーレイト初期化 */
	/*-------------------*/
	InitializeBaudrate();									/* ボーレイト初期化 */

	/*-----------------*/
	/** リモートＦＡＸ */
	/*-----------------*/

	RemoteFaxON_Flag				= 0;
	RemoteFaxPRN_Flag				= 0;
	RemoteFaxDEL_Flag				= 0;

#if (PRO_REMOTE_FAX == ENABLE)
	if (CHK_RemoteFaxON()) {
		RemoteFaxON_Flag			= 1;				/** リモートＦＡＸ設定 ON/OFF) */
	}
	if (CHK_RemoteFaxPRN()) {
		RemoteFaxPRN_Flag			= 1;				/** リモートＦＡＸ自動プリント設定 (ON/OFF) */
	}
	if (CHK_RemoteFaxDEL()) {
		RemoteFaxDEL_Flag			= 1;				/** リモートＦＡＸ自動メモリ消去設定 (ON/OFF) */
	}
 #if defined(GBR)
	if(CHK_GBR_SecurityRx()) {
		RemoteFaxPRN_Flag			= 0;		/* SecurityRx:On時、自動プリント強制OFF 95.01.26 M.HARADA */
	}
 #endif
	TxRemoteFaxCheckMsgFlag = 0;	/**	リモートＦＡＸチェックメッセージ送信フラグ	*/	/* 竹内 Jun.24.1994 */
#endif
	/*----------*/
	/** Rx Mode */
	/*----------*/
#if defined(KEISATSU) /* 警察FAX Modify by SMuratec 夏 2005/09/21 */
	if (SYS_InternalLineNumber == SYS_STD_LINE_COM ){
		AttemptRxModeSwitch = (UBYTE)(SYB_RxModeSwitch & SYS_AUTO_CALLED_SW);
	}
	else{
		AttemptRxModeSwitch = (UBYTE)(SYB_RxModeSwitchExt & SYS_AUTO_CALLED_SW);
	}
#else
	AttemptRxModeSwitch = CMN_PresentReceiveMode();			/** 受信モードセット */
#endif /* Modify end */	

	if ( (AttemptRxModeSwitch == SYS_TAD_READY)
	  || (AttemptRxModeSwitch == SYS_DIALIN_TAD_READY) ) {
		AttemptRxModeSwitch = SYS_ANS_FAX_READY;
	}
#if (PRO_REMOTE_FAX == ENABLE)
 #if (PRO_BUILTIN_TAD == DISABLE)
	else if (AttemptRxModeSwitch != SYS_FAX_READY) {
		RemoteFaxON_Flag	= 0;	/** 外付けＴＡＤのリモートＦＡＸはＦＡＸ待機以外無効 */
		RemoteFaxPRN_Flag	= 0;
		RemoteFaxDEL_Flag	= 0;
	}
 #endif
 #if (PRO_BUILTIN_TAD == ENABLE)
	else {			/* 内蔵ＴＡＤに "ANS/FAX待機"は無い */
		RemoteFaxON_Flag	= 0;	/** 内蔵ＴＡＤのリモートＦＡＸはＴＡＤ待機以外無効 */
		RemoteFaxPRN_Flag	= 0;
		RemoteFaxDEL_Flag	= 0;
	}
 #endif
#endif

	ForwardReceiveFlag				= 0;		/** 転送受信 */
	BackUpForwardReceiveFlag		= 0;		/** 転送受信バックアップ */
	FaxNetReceiveFlag				= 0;		/** Ｆネット着信 */

	/*----------------------*/
	/** MinimumScaninngTime */
	/*----------------------*/
	/* 送信はスキャナ送信時の伝送時間をセットする */
	/* Jumbo Soneoka の依頼によりスキャナ送信時 0ms-->10ms に変更　14.Sep'94 Y.Suzuki */
	
	/* プロダクトの定義でセットする値を決める
	** by H.Hirao 1998/12/05
	*/
#if (PRO_TX_MINIMUM_SCAN_LINE_TIME == TIME10)
	AvailableTxMinimumScanningTime	= SCAN_MINIMUM_TIME10;			/** 機器の送信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
#elif (PRO_TX_MINIMUM_SCAN_LINE_TIME == TIME5)
	AvailableTxMinimumScanningTime	= SCAN_MINIMUM_TIME5;			/** 機器の送信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
#endif
#if (PRO_RX_MINIMUM_SCAN_LINE_TIME == TIME0)
	AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME0;			/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
 #if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/19 K.Kawata*/
	if ((CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX) || (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX)) {
		AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME20_2;		/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
	}
	else {
		AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME0;			/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
	}
 #endif
#elif (PRO_RX_MINIMUM_SCAN_LINE_TIME == TIME40_2)
	AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME40_2;		/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
#elif (PRO_RX_MINIMUM_SCAN_LINE_TIME == TIME10_2)
	AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME10_2;		/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
 #if (PRO_PRINT_TYPE == THERMAL)	/* by H.Hirao 1999/02/22 */
	/*
	** ＨＩＮＯＫＩは基本的にSCAN_MINIMUM_TIME10_2で印字できるのですが
	** ５ｍｓで間欠送りをすると印字が乱れるので１ライン２０ｍｓで印字するようにします
	** 1999/03/24 by T.Soneoka
	*/
	AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME40_2;		/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
	if (CHK_UNI_V17ReceiveType() == V17_MRX_TO_MRX) {	/* メモリ受信のみの場合 */
		AvailableRxMinimumScanningTime	= SCAN_MINIMUM_TIME0;			/** 機器の受信可能な１ライン最小電送時間 DIS Table Comm 14.Mar'94 Y.Suzuki */
	}
 #endif
#endif
	TxMinimumScanningTime			= 0;							/**	確定１ライン最小電送時間（送信）	*/
	RxMinimumScanningTime			= 0;							/**	確定１ライン最小電送時間（受信）	*/
	NextScanningMode				= 0;							/**	送信原稿の指定線密度　int-->char 鈴木 94/1/19	*/

	/*--------------*/
	/**	 MSE Method */
	/*--------------*/
	/* ポプラ、あんずの送信はＭＳＥ１（ＳＭＳＥ送信なし）山口 Dec.22.1995 */
	AvailableTxMSE_Method			= MSE1;						/** 機器の送信可能なＭＳＥ方式 26.Apr'94 Y.Suzuki*/
/*	AvailableTxMSE_Method			= SMSE;						ｿﾌﾄｺｰﾃﾞｯｸはSMSE可能？ */
#if (PRO_PRN_RX_SMSE == ENABLE)
	AvailableRxMSE_Method			= SMSE;						/** 機器の受信可能なＭＳＥ方式 26.Apr'94 Y.Suzuki*/
#else
/* 移植 by SMuratec L.Z.W 2003/07/24 */
 #if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
  #if (PRO_POST_OFFICE == ENABLE)	/* 郵政局特ROM by O.Kimoto 2001/01/21 */
	AvailableRxMSE_Method			= NOMSE;					/** 機器の受信可能なMSE1方式 28.Jun'94 Y.Suzuki*/
  #else
	AvailableRxMSE_Method			= MSE1;						/** 機器の受信可能なMSE1方式 28.Jun'94 Y.Suzuki*/
  #endif
 #endif
#endif
	TxMSE_Method					= NOMSE;					/** 確定送信ＭＳＥ方式 */

	/*------------------------------------------*/
	/* 交信に使用している原稿情報の変数を初期化 */
	/*					27.Aug'94 Y.Suzuki		*/
	/*------------------------------------------*/
	SYS_DocBlock.Index.No = 0;
	SYS_DocBlock.Index.Page = 0;
	SYS_DocBlock.Index.Item = 0;
	SYS_DocBlock.Index.BoxNumber = 0;
	SYS_DocBlock.Src.Code = 0;
	SYS_DocBlock.Src.Mode = 0;
	SYS_DocBlock.Src.Size = 0;
	SYS_DocBlock.Dst.Code = 0;
	SYS_DocBlock.Dst.Mode = 0;
	SYS_DocBlock.Dst.Size = 0;
	SYS_DocBlock.MinimumLineSize = 0;
	SYS_DocBlock.DocLength = 0;
	SYS_DocBlock.ModeMethod = 0;
	SYS_DocBlock.MSE_Method = 0;

	/*---------------*/
	/** RxResolution */
	/*---------------*/
#if (PRO_PRINTER == DPI400)
	AvailableRxResolution			= SYS_HFINE;				/** 機器の受信可能な受信線密度 */
#endif
#if (PRO_PRINTER == DPI200)
	AvailableRxResolution			= SYS_SFINE;				/** 機器の受信可能な受信線密度 */
#endif
#if (PRO_PRINTER == DPI600)		/* ANZU_L 300*400受信ありのとき */
	AvailableRxResolution			= SYS_E_HFINE;
#endif

#if (PRO_FORCE_FINE_RX_SWITCH == ENABLE) /* メモリスイッチで強制的にファインにする機能を試験的にサカキで入れます。 by H.Kubo 1998/10/06 */
	if (SYB_MaintenanceSwitch[MNT_SW_E1] & FORCE_RX_FINE_RESOLUTION) {
		AvailableRxResolution			= SYS_FINE;				/** 機器の受信可能な受信線密度 */
	}
#endif
	/*------------------*/
	/** ECM & MH/MR/MMR */			  /* Set CodingMethod ECM Modeに依存 */
	/*------------------*/
	if ( CHK_ECM_ON() != 0 ) {	/** ＥＣＭモード */
		TxECM_Ability				= ECM_ON;					/** ＥＣＭ送信ＯＮ／ＯＦＦ指定 */
		RxECM_Ability				= ECM_ON;					/** ＥＣＭ受信ＯＮ／ＯＦＦ指定 */

#if (PRO_TX_SPEED == V34) /* Changed by H.Kubo 1998/01/27 */
		SetAvailableCodingMethodEcmOn();
#else
		if (CHK_UNI_StoredMethodMMR()) {
			AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
			AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
		}
		else {
			AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
			AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
		}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */
		if (CHK_UNI_JBIG_TX_Enable()) {
			AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
		}
		if (CHK_UNI_JBIG_RX_Enable()) {
			AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
		}
#endif
#endif
	}
	else {
		TxECM_Ability				= ECM_OFF;					/** ＥＣＭ送信ＯＮ／ＯＦＦ指定 */
		RxECM_Ability				= ECM_OFF;					/** ＥＣＭ受信ＯＮ／ＯＦＦ指定 */
		AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
		AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
	}
#if (0)
//	JBIG_Ability					= 0;						/** TEST JBIG符号化能力 1997/01/28	By T.Yamaguchi */
#endif
	TxCodingMethod					= 0;						/**	確定送信符号化方式	*/
	RxCodingMethod					= 0;						/**	確定受信符号化方式	*/

	ECM_PageCounter					= 0;						/** ＥＣＭポストメッセージのページカウンタ */
	ECM_BlockCounter				= 0;						/** ＥＣＭポストメッセージのブロックカウンタ */
	ECM_FrameCounter				= 0;						/** ＥＣＭポストメッセージのフレームカウンタ */
	ECM_FirstFrameCounter			= 0;						/** 受信した１部分ページのフレーム数　現在受信中の部分ページの全フレーム数 */
	RxEOM_ReceiveFlag				= 0;						/** 「ＥＯＭ受信」フラグ */
	RxECM_RetransmittedFlag			= 0;						/** ＥＣＭの１部分ページ１回目受信フラグ */
/*	FaxECM_ResponseTimeFlag			= 0;						/@@ ＥＣＭ応答受信の待ち時間切り替えフラグ 未使用のため削除 by T.Y */
	RxECM_PixTimeoutFlag			= 0;						/** ＥＣＭ受信でノイズによるタイムアウト対策 */

	TxECM_Mode						= ECM_OFF;					/** 確定ＥＣＭ送信指定 */
	RxECM_Mode						= ECM_OFF;					/** 確定ＥＣＭ受信指定 */
	FcomEcmSize						= ECM_64_OCT;				/** ＥＣＭフレームサイズ（６４／２５６oct）種別 *//* Change by NOBUKO	 Mar/26/93 */

	TxPageFinishStatus				= TX_PAGE_END;				/**	送信終了の状況	*/
	RxPageFinishStatus				= RX_PAGE_END;				/**	受信終了の状況 (１ページ終了)	*/
	RxPrinterErrorFlag				= 0;						/**	プリンタエラーフラグ	*/

	TxNonStandardFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信非標準フレームのバイト数		*/
	TxID_FrameByteCount				= 0;						/*	MDM_Buffer[][]上へセットした送信ＩＤフレームのバイト数		*/
	TxStandardFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信標準フレームのバイト数		*/
	RxNonStandardFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットされた受信非標準フレームのバイト数	*/
	RxID_FrameByteCount				= 0;						/*	MDM_Buffer[][]上へセットされた受信ＩＤフレームのバイト数		*/
	RxStandardFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットされた受信標準フレームのバイト数		*/

/* #if (PRO_F_CODE == ENABLE) */
	/**	送信バイト数変数初期化	*/
	TxPasswordFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信ＰＷＤフレームのバイト数	*/
	TxSelectiveFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信ＳＥＰフレームのバイト数	*/
	TxSubaddressFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットした送信ＳＵＢフレームのバイト数	*/
	RxPasswordFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットされた受信ＰＷＤフレームのバイト数	*/
	RxSelectiveFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットされた受信ＳＥＰフレームのバイト数	*/
	RxSubaddressFrameByteCount		= 0;						/*	MDM_Buffer[][]上へセットされた受信ＳＵＢフレームのバイト数	*/
/* #endif */

	NonStdFrmPos					= 0;						/*	MDM_Buffer[][]上へ受信した非標準フレームの位置	*/
	ID_FrmPos						= 0;						/*	MDM_Buffer[][]上へ受信したＩＤフレームの位置		*/
	StdFrmPos						= 0;						/*	MDM_Buffer[][]上へ受信した標準フレームの位置		*/
	FaxTM							= 0;						/*	タイマー	*/

	DCS_TxCount						= 0;						/*		*/
	FCF_Point						= 0;						/*	HDLC関係　HDLCフレーム受信時モデムバッファ内のＦＣＦの位置	*/
	DiagPoint						= 0;						/*	リモート診断関係　サービスユーティリティフィールドポイント	*/
	DiagReadAddress					= 0;						/*	リモート診断関係	*/
	DiagReadSegment					= 0;						/*	リモート診断関係	*/
	ErrorMessageSet					= 0;						/*	エラーメッセージ内容	*/

	Offset_2ndDial					= 0;						/* 第２ワンタッチ／短縮ダイアルの配列オフセット */


	/*------------------------------*/
	/**	受信原稿ﾎﾟｰﾘﾝｸﾞ送信タイプ	*/
	/*	25.Mar'94 Y.Suzuki			*/
	/*------------------------------*/
	RxDocumentPollingTxFlag = 0;

#if(PRO_BATCH_TX == ENABLE)
	/*--------------------------------------------------*/
	/**	一括送信１頁以上送信後、エラー終了した場合		*/
	/*	のリダイヤル送信頁セットの際に使用 Y.Suzuki		*/
	/*										94/9/28		*/
	/*--------------------------------------------------*/
	BatchRedialFirstPage = 0;
#endif

	/*------------------------------*/
	/** コマンドファイル関係変数	*/
	/*------------------------------*/
	CommandFileStatus = 0;				/*	使用状況	*/
	CommandFileOptionItem = 0;			/*	通信種別	*/
	CommandFileConfirmationReport = 0;	/*	通信証	*/
	CommandFileTitleMessage = 0;		/*	タイトルメッセージ	*/
/*	*CommandFileDirectDial = 0;			/@	直接ダイヤル番号	*/
#if (PRO_PIN_ACCESS == ENABLE)
/*	*CommandFilePinNumber = 0;			/@	ｺﾏﾝﾄﾞﾌｧｲﾙのＰＩＮ番号 '95.12.22 t.yamaguchi */
	CommandFilePinAccessMode = 0;		/* ＰＩＮアクセスモード 1996.01.09 T.yamaguchi */
#endif
	CommandFilePage = 0;				/* 送信ページ */
	CommandFileDepartmentCode = 0xffff;		/* 部門管理コード */
	CommandFileAbility = 0;				/* 通信予約の付加情報(FX) 1994/11/01 Y.Murata */
/*#if (PRO_F_CODE == ENABLE)*/	/* 1997/01/10  By T.Yamaguchi */
	CommandFileFcodePosition = 0;		/* ｺﾏﾝﾄﾞﾌｧｲﾙのＦコードﾃﾞｰﾀの格納されているﾎﾟｼﾞｼｮﾝを格納 */
/*#endif*/

	/*----------*/
	/*	その他	*/
	/*----------*/
#if defined(FRA)
	GenerateRingSignalHLRelayFlag	= 0;						/* フランスのみ */
	VoiceTxFlag						= 0;						/* フランスのみ */
	FaxRingingPeriodFlag			= 0;						/** 無制限 :0　一定期間 :1 **/
	GenerateRingSignalFlag			= 0;
	GenerateRingSignalMessage		= 0;
	VoiceFlag						= 0;
#endif
#if defined(GBR)	/* add by M.HARADA 95.09.09 for NLD */
	NLD_DT_Detecting_Flag = 0;
#endif

#if (PRO_PIN_ACCESS == ENABLE) /* PINダイヤルバッファ初期化 '95.12.26 By T.Y */
	for(count = 0; count < PIN_DIALING_NUMBER_MAX; count ++){
		SYS_PinBuffer[count] = NULL;
	}
#endif

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
	ServiceFunctionMode = NO;	/* 96/07/23 By T.Yamaguchi */
#endif /* (PRO_MODEM == ORANGE3) */

	/* コンパチの途中で記録紙サイズが変更されるとエラーにならないためバックアップ変数 */
	/* FCM_BuckUpPaperSize = SYS_NO_PAPER;	/@ 1997/12/16  By T.Yamaguchi */
	if (SYB_MaintenanceSwitch[MNT_SW_C9] & BUCKUP_PAPER_SIZE_FCM_RCMP) {
		FCM_BuckUpPaperSize = CheckDocPaperSize(); /* 1998/02/09  By T.Yamaguchi */
	}
	else {
		FCM_BuckUpPaperSize = SYS_NO_PAPER;
	}
	/*--------------------------*/
	/*	応答受信用タイマ初期化	*/
	/*--------------------------*/
	FCM_ReceiveResponseTime			= TIME_OVER_3SEC;			/* 応答受信用ﾀｲﾏｰ 3SEC '95.12.19 T.Y */

	FaxComPhaseStatus				= FAX_PH_A;					/** デバッグ用 */
/*	FaxDebugPIXStartTime			= 0;		*/				/** デバッグ用 */
/*	FaxDebugPIXENDTime				= 0;		*/				/** デバッグ用 */
/*	FaxDebugDCSSW					= 0;		*/				/** デバッグ用 */

	/*----------------------------------------------------------*/
	/** 手動送受信チェックメッセージリクエストクリア			*/
	/*	手動送受信時のﾁｪｯｸﾒｯｾｰｼﾞは次通信開始まで有効 1994/09/12 */
	/*----------------------------------------------------------*/
#if 0	/* 1996/06/07 T.Yamaguchi */
//	SYS_ManualFaxCommErrRequest		= 0;
#endif
	/*------------------------------------------------------------*/
	/** マシーンステータス(SYS_MachineStatus)の通信停止情報クリア */
	/*------------------------------------------------------------*/
	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;

	/*------------------------------*/
	/*	 SYS_TensouJushinFlag clear */
	/*------------------------------*/
	SYS_TensouJushinFlag = 0;

	EcmWaitPhase = 0;	/*	ＥＣＭ受信時のデコード待ち／カット待ち状態を初期化	*/	/* 竹内 Oct.13.1994 */

#if (PRO_REMOTE_FAX == ENABLE)
 #if (PRO_DRAM_BACKUP == ENABLE)
	SYS_RemoteFaxTxPerformingFlag = 0;		/* 1994/12/19 */
 #endif
#endif

#if (PRO_PAT_JOURNAL == ENABLE)
	/** ジャーナルのイメージ展開バッファをクリア */
	PAT_JournalImageBufferClear();
 #if (PRO_DEPARTMENT == ENABLE)
	PAT_JournalWorkFile.DepartmentCode = 0xffff;/** 初期値変更　ジャーナルの部門を「００００」でイメージバッファに展開(初期化) */
/*	PAT_JournalWorkFile.DepartmentCode = 0;		/@@ ジャーナルの部門を「００００」でイメージバッファに展開(初期化) */

	PAT_JournalDataToImage(DCODE);
 #endif
#endif

#if (PRO_RELAYED_REPORT == ENABLE)	/* 不達通知のため  竹内 Apr.28.1995 */
	TxRelayReport = 0;		/** 不達通知の識別フラグをクリア */
#endif
#if defined(FRA)
	FRA_PIP_PIN_Rx_Flag = 0;				/* 1995/95/06 by M.HARADA */
	CRPReceiveFlag = 0;						/* 1995/95/06 by M.HARADA */
#endif
#if defined(DEU) || defined(EUR)		/* add by M.HARADA 95.09.13 for PTT Test */
	DEU_Return_Flag = 0;
#endif

	TimerCutStatus = 0;	/* 1997/06/02  By T.Yamaguchi DEUの条件削除 */
	PIP_TX_Flag = 0;	/* 1997/06/02  By T.Yamaguchi DEUの条件削除 */
/*----------------------------------------------------------*/
/*	TSI による中々継時に中継指示ｸﾞﾙｰﾌﾟNO.とは、				*/
/*	別に中継指示配信送信宛先用ｸﾞﾙｰﾌﾟNO.をTSIにｾｯﾄさせる。	*/
/*	受信したTSI:000-2-3-4--10 の場合						*/
/*						  ↑を示す。						*/
/*	FCM_INIT.C で初期化される。								*/
/*											Y.Suzuki 950929 */
/*----------------------------------------------------------*/
#if(PRO_TSI_RELAY_COM == ENABLE)
	TSI_Ptr = 0;
#endif

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
	MDM_tskno_FcsDetectTimer = 0xffff;		/* 1996/07/19 By N.Sakamoto */
	/* デバッグ用変数 1997/09/11  By T.Yamaguchi */
	FCM_Is_ToneDetecting = NO;
#endif /* (PRO_MODEM == ORANGE3) */
	SYS_RingSignalStopFlag	 = 0;			/* 1996/08/21 By N.Sakamoto 会話予約で擬似ベルが鳴動しない不具合対策 */

/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/10 Y.Murata */
	SYS_FaxComIndexConflictStatus = 0;
	PartnerV8Capable = 0xFF;	/* 相手機Ｖ８能力有り */ /* 1997/01/13 */
/* #endif  */

#if (PRO_VOICE_ANSWER == ENABLE)	/* 1998/01/27  By T.Yamaguchi */
    /*-----------------------------*/
    /* Voice 送出中,FhaseB1を示すFlagのｸﾘｱ */
    /*-----------------------------*/
    SYS_VoiceTxFlag = NO;
    SYS_PhaseB1Flag = NO;
	SYS_FaxMelodyFlag = NO;
	SYS_PhaseB1StopWaitFlag = NO;
	SYS_Busy_detecting	= NO;
#endif


#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/08/11 */
	/*------------------*/
	/* Ｖ８／Ｖ３４関係 */
	/*------------------*/
	V8ProcedureRequestFlag = 0;				/** Ｖ８モード移行要求 */
	SYS_V34ProcedureExecutingFlag = 0;			/** Ｖ３４モード実行中フラグ */
	ExecDialNumber = 0;						/** ワンタッチ／短縮オフセット */

	/* 初期値はＦＦにしておく 1996/08/03 Y.M */
	/*PartnerV8Capable = 0;*/				/** 相手機Ｖ８能力有り */
	PartnerV8Capable = 0xFF;				/** 相手機Ｖ８能力有り */

	V34PrimaryChannelDirection = 0;			/** プライマリチャネル指示 */

	SYS_V8DetectATV25Flag = 0;				/** V25 Answer Tone Flag */
	SYS_DetectABCODE_Flag = 0;				/** ABCODE Flag */

	V34FirstDataRate = 0xFF;
	V34CurrentDataRate = 0xFF;				/* For Debug */
	V34BaudDataRate = 0xFF;					/* For Debug */
	FaxComPhaseStatus = V34_INITIAL;		/* For Debug */
	V8ConfigMode = 0;
	V34ErrorCode = 0;
	TxInformationCategoryByteCount = 0;		/* 送信情報カテゴリバイト数 */
	RxInformationCategoryByteCount = 0;		/* 受信情報カテゴリバイト数 */

	V8FrmPos = 0;
	V8CallFunctionPos = 0;


	FCM_V8MonitorFlag = 0; /* Added by H.Kubo 1997/10/07 */
	/*----------------------------------*/
	/* スタートアップの引き数達の初期化 */
	/*----------------------------------*/
	StartUpData.Item = 0;
	StartUpData.Direction = 0;
	StartUpData.Allowed = 0;
	StartUpData.Option.TransmitCI = 0;
	StartUpData.Option.SubOption1 = 0;
	StartUpData.Option.SubOption2 = 0;

	/*--------------------------------*/
	/* メモリ消去用インデックス初期化 */
	/*--------------------------------*/
	FCM_MemoryClearIndex.Status = 0;
	FCM_MemoryClearIndex.Index.Item = 0;
	FCM_MemoryClearIndex.Index.No   = 0;
	FCM_MemoryClearIndex.Index.Page = 0;

	/*------------------------------------*/
	/* 情報カテゴリセーブ用バッファクリア */
	/*------------------------------------*/
	for (count = 0; count < SAVE_CATEGORY_BUF_MAX; count++) {
		V34SavedCM_Data[count] = 0x00;
		V34SavedJM_Data[count] = 0x00;
		V34SavedAvailableJM_Data[count] = 0x00;
	}

	/*-------------------*/
	/** ボーレイト初期化 */
	/*-------------------*/
	InitializeBaudrate();									/* ボーレイト初期化 */

	/* for (count = 0; count < 50; count++) [ */
	for (count = 0; count <( sizeof FCM_MonitorData); count++) {
		FCM_MonitorData[count] = 0x00;
	}
 #if 0 /*ROM 節約のため、削除。by H.Kubo 1999/01/22  */
@	/* for (count = 0; count < 16; count++) [ */
@	for (count = 0; count < (sizeof FCM_SpeedBuf); count++) {
@		FCM_SpeedBuf[count] = 0xFF;
@		FCM_ConfBuf[count] = 0xFF;
@		FCM_RateBuf[count] = 0xFF;
@	}
@	FCM_SampleBufPoint = 0;
 #endif
	/*-------------------*/
	/** プロービング情報 */
	/*-------------------*/
	FCM_SignalToNoiseRatio = 0xFF;
	FCM_LowBandEdgeFrequency = 0xFF;
	FCM_HighBandEdgeFrequency = 0xFF;
	FCM_PreEmphasisFilter = 0xFF;		/* Add By O.Kimoto 1996/07/25 */
	FCM_TxLevelReduction = 0xFF;		/* Add By O.Kimoto 1996/07/25 */

	FCM_CONF_Value = 0xFF;					/* conf data for debug 1996/02/19 */
	FCM_SPEED_Value = 0xFF;					/* tx speed for debug 1996/02/19 */
	FCM_384_Value = 0xFF;					/* rx speed for debug 1996/02/19 */

	FCM_EQM_MonitorPoint = 0;				/* Test 1996/02/23 */
	for (count = 0; count < 100; count++) {
		FCM_EQM_MonitorBuf[count] = 0xFFFF;
	}
/* mod by SMuratec H.C.H 2003.07.11 */
#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* PhaseJitter。by H.Kubo 1998/10/06  */
	FCM_PhaseJitterFrequency = 0;
	FCM_PhaseJitterAmplitude = 0;
#endif

	/* フレーム情報 1996/05/16 */
	FCM_SavedRxTotalFrameLine = 0;
	FCM_SavedRxErrorFrameLine = 0;
	FCM_SavedRxPartialFrameLine = 0;
	FCM_SavedRxNonErrContinuePage = 0;
	ECM_PageCounterBackUp = 0xFFFF;
	ECM_BlockCounterBackUp = 0xFFFF;

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/11 */
	/* CTSがONせず通信が継続できないことをしめす変数 */
	MDM_ClearToSendAbort = FALSE;		/* 1996/05/17 */
#endif /* (PRO_MODEM == R288F) */

	DammyDataforMurata1 = 0;
	DammyDataforMurata2 = 0;
	DammyDataforMurata3 = 0;
	DammyDataforMurata4 = 0;
	DammyDataforMurata5 = 0;

	V8_ANSamDetectFlag = 0;		/* 1996/08/07 */

	FCM_PhaseJitterFrequencyValue = 0xFFFF;	/* 位相ジッタリード値 */
	FCM_PhaseJitterAmplitudeValue = 0xFFFF;	/* 位相ジッタリード値 */

	FCM_DataRateChangExecute = 0;		/* 通信速度変更中 1996/08/28 */

	FCM_ToneAfterDetectDCE = AD_NOT_YET_DETECTED;

#endif /* (PRO_TX_SPEED == V34) */

#if (PRO_RELAYED_REPORT == ENABLE) /* added by H.Kubo 1998/01/19 */
	tskno_LST_RelayedTxReportImage = 0xffff;
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	LST_TxPageFinishStatus = TX_PAGE_END;
	CDC_ReadPageCount = 0;
 #endif
#endif

#if (PRO_MODEM == R288F)
	/* by T.Soneoka 1998/01/22 */
	tskno_RxEcmControl = 0xffff;
#endif
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
	SYB_FlashROM_WriteStatus = NO_STATUS;
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */
	FCM_QuickMemoryTxExecute = 0;
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE)	/* 1998/11/17 by T.Soneoka */
	tskno_SCN_STxStoreTask = 0xffff;
#if (0) /* 1999/1/5 by T.Soneoka */
**	tskno_SCN_WatchDocFeedTask = 0xffff;
**	tskno_SCN_ScanPage = 0xffff;
#endif
	tskno_CDC_STxDMA_Task = 0xffff;
#endif

/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Mod. by J.Kishida 2002/09/06 */
	FCM_DetectFSK = 0;
	StartUpTaskInitial();
	V8TaskInitial();
	FCM_DetectCIbyVoiceAnswer = 0;
	FCM_BusyToneDetectStatus = 0;
 #endif
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/16 石橋正和 */
	FCM_S1_Bypass = CHK_BypassS1();
	S1_InitializeFaxCom(CHK_ScrambleAvailabe(), FCM_S1_Bypass); /* S1初期化 */
	
	FCM_S1_Scramble = FALSE;
	FCM_S1_Senyo = FALSE;
	
	FCM_S1_Preamble3S = FALSE;
	
	FCM_ShireiKidoWaitFor1stDCS = FALSE;
	
	FCM_ISSEI_TX = FALSE;	/* 警察FAX DVT_ID17 一斉モード送信中 by SMuratec 夏 2005/11/05 */
	
	FCM_ShireiOff = FALSE;
	
#endif
}



#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1998/01/27 */
void SetAvailableCodingMethodEcmOn(void)
{
	if (CHK_UNI_StoredMethodMMR()) {
		AvailableTxCodingMethod		= SYS_MMR_CODE;				/** 機器の送信可能な符号化方式 */
		AvailableRxCodingMethod		= SYS_MMR_CODE;				/** 機器の受信可能な符号化方式 */
	}
	else {
		AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
		AvailableRxCodingMethod		= SYS_MR_CODE;				/** 機器の受信可能な符号化方式 */
	}
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/17 */

 #if defined(POPLAR_F)
	if (SYS_FaxComTxType != SYS_SCANNER_TRANSMIT) {
		if (CHK_UNI_JBIG_TX_Enable()) {
			AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
		}
	}
	
 #else
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* SAKAKIではJBIGスキャナ送信なし 1998/09/30 H.Kubo */
	if (SYS_FaxComTxType != SYS_SCANNER_TRANSMIT) {
		if (CHK_UNI_JBIG_TX_Enable()) {
			AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
		}
	}
	/*---------------------------------------------------------------------
	** SAKAKIで６４ＫＢを超えるデータをスキャナ送信しようとすると、
	** ６４ＫＢの間で、データかけが発生することがあり、この時T.4.1/R.3.3が発生する。
	** 原因究明・対策が終了するまで、MRで送信するようにしておきます。
	** MR送信すると、受信側でデコードエラーにはなりませんが、エラーラインが発生します。
	** 1998/11/22 H.Yoshikawa
	*/
	else {
		if (CHK_UNI_ScannerTxMR()) {
			AvailableTxCodingMethod		= SYS_MR_CODE;				/** 機器の送信可能な符号化方式 */
		}
	}
  #else
	if (CHK_UNI_JBIG_TX_Enable()) {
		AvailableTxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
	}
  #endif
 #endif
	if (CHK_UNI_JBIG_RX_Enable()) {
		AvailableRxCodingMethod		= SYS_JBIG_CODE;				/** 機器の送信可能な符号化方式 */
	}
#endif
}
#endif

/*----------------------------------------------------------------------------------------------
 |	  きしゅ			|		じゅしん			|	 みかけ		|	  ＤＩＳのせんげん	   |
 |						|							|				| (さしょうでんそうじかん) |
 -----------------------------------------------------------------------------------------------
 |	さつき				|	ぷりんた～				|	ぷりんた～	|	ぷりんた～ののうりょく |
 -----------------------------------------------------------------------------------------------
 |	さつき び～			|	ぷりんた～				|	ぷりんた～	|	ぷりんた～ののうりょく |
 -----------------------------------------------------------------------------------------------
 |	らべんだ～ えいち	|	ばっふぁりんぐじゅしん	|	ぷりんた～	|	ぷりんた～ののうりょく |
 -----------------------------------------------------------------------------------------------
 |	らべんだ～ える		|	ばっふぁりんぐじゅしん	|	ぷりんた～	|	ぷりんた～ののうりょく |
 -----------------------------------------------------------------------------------------------
 |	もみじ				|	ぷりんた～				|	ぷりんた～	|	ぷりんた～ののうりょく |
 -----------------------------------------------------------------------------------------------
 |	きり				|	めもり					|	めもり		|	０ｍｓｅｃ			   |
 -----------------------------------------------------------------------------------------------
 |	みらん				|	めもり					|	めもり		|	０ｍｓｅｃ			   |
 ----------------------------------------------------------------------------------------------*/
