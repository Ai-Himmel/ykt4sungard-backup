/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/CLOVER                                                */
/*  ファイル名   : FCM_V34.C                                                 */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1995/11/25                                                */
/*  概  要       : Ｖ３４モードモジュール                                    */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*               : 1996/10/03 ﾘﾄﾚｰﾝ等が起こるとSPEEDﾚｼﾞｽﾀとCONFﾚｼﾞｽﾀの値が   */
/*               :            合わなくなるためCONFを参照するように変更(送信) */
/*               : 1996/10/08 ﾚｰﾄｱｯﾌﾟ時のmax速度修正                         */
/*---------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"

#if (PRO_TX_SPEED == V34) /* Ported from clover by H.Kubo 1997/08/08 */
/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mon_pro.h"

#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\fcm_def.h"
/* #include "\src\atlanta\define\sys_spd.h"*/
#include "\src\atlanta\define\syst30.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
/* #include "\src\atlanta\ext_v\mdm_tbl.h" */

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/08/07 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\define\mdm_io.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif




/*************************************************************************
	module		:[Ｖ３４コントロールチャネルターンＯＦＦ]
	function	:[
		1.コントロールチャネルのｔｕｒｎ－ｏｆｆを行う
		2.フラグの終了（無音）を検出する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_ControlChanelTurnOff(void)
{
	if (SYS_V34ProcedureExecuting() == 0) {
		return(OK);
	}

	return(MDM_ControlChanelTurnOff());

}


/*************************************************************************
	module		:[Ｖ３４コントロールチャネルターンＯＦＦ検出]
	function	:[
		1.ｔｕｒｎ－ｏｆｆを検出する（連続４０個の「１」）
		2.ｔｕｒｎ－ｏｆｆを検出する前にＦＳＫを検出すればＦＳＫを受信する
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_ControlChanelDetectTurnOff(void)
{
	if (!SYS_V34ProcedureExecuting()) {
		return(OK);
	}

	/*return(MDM_FskHighSpeedCheck(RxBaudRate, RxECM_Mode,(UBYTE)(0x01)));1996/03/13*/
	return(MDM_FskHighSpeedCheck(TxBaudRate, TxECM_Mode,(UBYTE)(0x01)));
	/*return(MDM_ControlChanelDetectTurnOff()); 1996/02/14 */

}

/*************************************************************************
	module		:[受領証送信時、Ｖ８モードに入るためのコントロールチャネルの
				  ターンＯＦＦ]
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
	date		:[1995/12/05]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_ControlChTurnaroundTurnOff(void)
{
	if ( !SYS_V34ProcedureExecuting() ) {
		return(OK);
	}

	return(MDM_ControlChTurnaroundTurnOff());
	/*return(MDM_FskHighSpeedCheck(RxBaudRate, RxECM_Mode,(UBYTE)(0x01))); 1996/02/14 */

}


/*************************************************************************
	module		:[Ｖ３４コントロールチャネルＯＦＦ]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_ControlChanelOff(void)
{
	if ( !SYS_V34ProcedureExecuting() ) {
		return(OK);
	}
	return(MDM_ControlChanelOff());
}


/*************************************************************************
	module		:[Ｖ３４プライマリチャネルターンＯＦＦ]
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
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
void  FCM_PrimaryChanelTurnOff(void)
{
	if ( !SYS_V34ProcedureExecuting() ) {
		/* 何もしない */
	}
	else {

/** Advive by Mr.Palm Sh - PPh Trouble By O.Kimoto 1996/07/04 **/
/** Advive by Mr.Palm Sh - PPh Trouble By O.Kimoto 1996/07/17 **/
#if 0
//if (DATA_RATE_CHANGE) {
//	if (DATA_RATE_CHANGE == 1) {
//		MDM_FlipCcBit();
//	}
//	else if (DATA_RATE_CHANGE == 2) {
//		MDM_SetForcedPPh();
//	}
//}
#endif
#if 0	/* 1996/08/26 Y.Murata */
//		/* ﾒﾓﾘSWがたっている時か、相手がﾑﾗﾀ機ならPPh 1996/08/03 Y.M */
//		if ((CHK_V34ForcedPPh()) || (MakerCodeRxFlag == 1)) {	/* 1996/07/17 Y.M */
//			MDM_SetForcedPPh();
//		}
#endif

		if (FCM_DataRateChangExecute == 1) {	/* 1996/08/28 */
			FCM_DataRateChangExecute = 0;
		}
		else {
			/* ﾒﾓﾘSWがたっている時か、相手がﾑﾗﾀ機ならPPh 1996/08/28 Y.M */
			if ((CHK_V34ForcedPPh()) || (MakerCodeRxFlag == 1)) {
				MDM_SetForcedPPh();
			}
		}

		MDM_PrimaryChanelTurnOff();
	}
}

/*************************************************************************
	module		:[通常Ｔ３０プロトコルからＶ８手順に戻るか否か]
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
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckV8ProcedureRequest(void)
{
	if ((CMN_GetDataSignalingRate() & 0x0001) != 0x0001) {		/** Ｖ３４リソースが無い  */
		return(0);		/** Ｖ８に戻らない */
	}
	else {
		if ((V8ProcedureRequestFlag == 1) && 
			(FaxComPerformingFlag == 1) && 
			(SYS_V34ProcedureExecuting() == 0)) {	/** Ｖ８要求でＶ３４モードを実行してない */

			return(1);		/** Ｖ８に戻る */
		}
		else {
			return(0);		/** Ｖ８に戻らない */
		}
	}
}


/*************************************************************************
	module		:[相手機Ｖ８能力チェック]
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
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckPartnerV8Capable(void)
{
	GetMultiFrameLine();

	/* BIT6 チェック */
	if (MDM_ModemBuffer[StdFrmPos][2] == DIS_F) {	/* DISﾌﾚｰﾑなら 1998/02/17 Y.Murata */
		if (MDM_ModemBuffer[StdFrmPos][3] & 0x20) {	/* Recommendation V8 capabilities ON ? */

#if (0)
** 			PartnerV8Capable = 1;		/* 1996/08/03 Y.M */
** 			return(1);
#else
			/* 松下 Ｂ－５６がＣＩを検出しないため、Ｔ．１．１エラーが必ず発生する。
			** よって、その防御策として、ＣＩ送出回数を限定する。
			** By O.Kimoto 1999/03/11
			*/
			if (FCM_CI_TransmitCount < 2) {
				FCM_CI_TransmitCount ++;
				PartnerV8Capable = 1;		/* 1996/08/03 Y.M */
				return(1);
			}
			else {
				PartnerV8Capable = 0;		/* 1996/08/03 Y.M */
				return(0);
			}
#endif


		}
	}

#if 0
	if (RxStandardFrameByteCount > 13) {
		if (MDM_ModemBuffer[StdFrmPos][13] & 0x01) {	/* Recommendation V8 capabilities ON ? */
			return(1);
		}
	}
#endif
	PartnerV8Capable = 0;		/* 1996/08/03 Y.M */
	return(0);

}


/*************************************************************************
	module		:[応答受信時にＶ３４起呼表示信号「ＣＩ」を検出するか否か]
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
	date		:[1995/10/27]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckDetectCI(void)
{
#if (0) /* Changed by H.Kubo 997/10/07 */
	if ((CMN_GetDataSignalingRate() & 0x0001) != 0x0001) {	/** Ｖ３４リソースが無い */
		return(0);			/** Ｖ３４起呼表示信号の検出を行わない */
	}
#else 
	if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) != DATA_SIGNALING_RATE_V34_BIT) {	/** Ｖ３４リソースが無い */
		return(0);			/** Ｖ３４起呼表示信号の検出を行わない */
	}
#endif /* (0) */
	else {
		if (( !SYS_V34ProcedureExecuting() ) && (SYS_RxTotalPage == 0) &&
												(SYS_TxTotalPage == 0)) {

			return(1);		/** Ｖ３４起呼表示信号の検出を行う */
		}
		else {
			return(0);		/** Ｖ３４起呼表示信号の検出を行わない */
		}
	}
}


/*************************************************************************
	module		:[送信フェーズＡでＶ８モードを実行するか否か]
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
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckV8ProcedurePhaseA(void)
{
	UBYTE ret;

	ret = 0;

	/* if ((CMN_GetDataSignalingRate() & 0x0001) == 0x0001) [ */
	if ((CMN_GetDataSignalingRate() & DATA_SIGNALING_RATE_V34_BIT) == DATA_SIGNALING_RATE_V34_BIT) {
#if (0) /* Changed by H.Kubo 1998/01/09 */
@@		if (CHK_SpeedHandshakeV8() == 0) {
@@			if ((CHK_SpeedHandshake144()) || (CHK_SpeedHandshake96())) {
@@				ret = 0;
@@			}
@@			else {
@@				ret = 1;
@@			}
@@		}
#else
		if (FCM_PtnrChkSpeedHandshakeV8() == 0) {
			if ((FCM_PtnrChkSpeedHandshake144()) || (FCM_PtnrChkSpeedHandshake96())) {
				ret = 0;
			}
			else {
				ret = 1;
			}
		}
#endif
		else {
			ret = 1;
		}
	}
	else {
		ret = 0;
	}

	if (ret == 1) {
		/* V34ｽﾀｰﾄｱｯﾌﾟｴﾗｰが出たときのﾘﾀﾞｲｱﾙはV17で交信 1996/09/04 Y.Murata */
		if (SYS_CurrentExecutingCommand->Option & SYS_V34_STUP_RECOVER) {
			return(0);
		}

		return(1);
	}
	else {
		return(0);
	}
}


/*************************************************************************
	module		:[送信データレイトリード]
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
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckTxDataRate(void)
{
#if (PRO_MODEM == MN195006)
	UBYTE	rate;
	UBYTE	value;

	value = MDM_TxDataRateRead();
	FCM_384_Value = value;
	rate = FCM_V34DataRateDefineChange( value );
	if ( V34FirstDataRate == 0xFF ) {
		V34FirstDataRate = rate;
	}
	V34CurrentDataRate = rate;
	FCM_CONF_Value = value;
	FCM_SPEED_Value = value;
	return(V34CurrentDataRate);

#else
	UBYTE	rate;
	UBYTE	value;

	value = MDM_TxDataRateRead();		/* SPEED */
	FCM_SPEED_Value = value;
	rate = FCM_V34DataRateDefineChange(value);
	if (V34FirstDataRate == 0xFF) {
		V34FirstDataRate = rate;
	}
	V34CurrentDataRate = rate;

	FCM_CONF_Value = MDM_GetIO(POS_CONF);
	FCM_384_Value = MDM_GetV34RxSpeedIndication();
 #if 0 /*ROM 節約のため、削除。by H.Kubo 1999/01/22  */
/* sample for debug */
@	if (FCM_SampleBufPoint < 16) {
@		FCM_SpeedBuf[FCM_SampleBufPoint] = value;
@		FCM_ConfBuf[FCM_SampleBufPoint] = MDM_TrueConfValue;	/** FCM_CONF_Value to MDM_TrueConfValue by O.Kimoto 1997/12/02 */
@		FCM_RateBuf[FCM_SampleBufPoint] = rate;
@		FCM_SampleBufPoint++;
@	}
 #endif
	/*return(V34CurrentDataRate); 1996/10/03 MURATTCH */
	return(FCM_CONF_Value);
#endif
}


/*************************************************************************
	module		:[受信データレイトリード]
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
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckRxDataRate(void)
{
	UBYTE	rate;
	UBYTE	value;

	value = MDM_RxDataRateRead();	/* $384 */
	FCM_384_Value = value;
	rate = FCM_V34DataRateDefineChange(value);
	if (V34FirstDataRate == 0xFF) {
		V34FirstDataRate = rate;
	}
	V34CurrentDataRate = rate;
	FCM_CONF_Value = MDM_GetIO(POS_CONF);
	FCM_SPEED_Value = MDM_GetIO(POS_SPEED);

#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* PhaseJitter。by H.Kubo 1998/10/06  */
	FCM_PhaseJitterFrequency = MDM_GetPhaseJitterFrequency();
	FCM_PhaseJitterAmplitude = MDM_GetPhaseJitterAmplitude();
#endif

 #if 0 /*ROM 節約のため、削除。by H.Kubo 1999/01/22  */
/* sample for debug */
	if (FCM_SampleBufPoint < 16) {
@		FCM_SpeedBuf[FCM_SampleBufPoint] = value;
@		FCM_ConfBuf[FCM_SampleBufPoint] =  MDM_TrueConfValue;	/** FCM_CONF_Value to MDM_TrueConfValue by O.Kimoto 1997/12/02 */
@		FCM_RateBuf[FCM_SampleBufPoint] = rate;
@		FCM_SampleBufPoint++;
@	}
 #endif
	return(V34CurrentDataRate);
}

/*************************************************************************
	module		:[Ｖ３４データレイトを下げる]
	function	:[
		1.
	]
	return		:[
					1: 速度変更した
					0: 速度変更していない

	]
	common		:[]
	condition	:[]
	comment		:[
		1996/02/14 データ速度のとりうる範囲の判断追加
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/11/16]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_ChangeDataRate(UBYTE src_data_rate)	/* void -> UBYTE 1996/09/10 */
{
	UBYTE	rate;
	UBYTE	max;
	UBYTE	min;
	UBYTE	ret;

	rate = 0;
	max = 0;
	min = 0;
	ret = 0;

	/* 通信速度を下げる */
	switch (src_data_rate) {
		case BPS33600_V34:
			rate = BPS31200_V34;
			break;
		case BPS31200_V34:
			rate = BPS28800_V34;
			break;
		case BPS28800_V34:
			rate = BPS26400_V34;
			break;
		case BPS26400_V34:
			rate = BPS24000_V34;
			break;
		case BPS24000_V34:
			rate = BPS21600_V34;
			break;
		case BPS21600_V34:
			rate = BPS19200_V34;
			break;
		case BPS19200_V34:
			rate = BPS16800_V34;
			break;
		case BPS16800_V34:
			rate = BPS14400_V34;
			break;
		case BPS14400_V34:
			rate = BPS12000_V34;
			break;
		case BPS12000_V34:
			rate = BPS9600_V34;
			break;
		case BPS9600_V34:
			rate = BPS7200_V34;
			break;
		case BPS7200_V34:
			rate = BPS4800_V34;
			break;
		case BPS4800_V34:
			rate = BPS2400_V34;
			break;
		case BPS2400_V34:
		default:
			rate = BPS2400_V34;
			break;
	}

	/* シンボルレートよりｍｉｎ、ｍａｘ求める */
	switch (V34BaudDataRate) {
		case SYMBOL_2400:
			min = BPS2400_V34;
			max = BPS21600_V34;
			break;
		case SYMBOL_2800:
			min = BPS4800_V34;
			max = BPS26400_V34;
			break;
		case SYMBOL_3000:
			min = BPS4800_V34;
			max = BPS28800_V34;
			break;
		case SYMBOL_3200:
			min = BPS4800_V34;
			max = BPS31200_V34;
			break;
		case SYMBOL_3429:
			min = BPS4800_V34;
			max = BPS33600_V34;
			break;
		default:
			break;
	}

	/* 正常な速度かどうかチェック */
	if ((rate >= min) && (rate <= max)) {
		/* 正常な速度 */
	}
	else {
		if (rate == BPS2400_V34) {	/* 2400BPSでこのパスにくると言うことはｍｉｎを下回ったからで、レートを下げずに１つ戻す */
			rate = BPS4800_V34;
		}
		else {
		/* このパスはありえないけど、もしここを通れば、とりあえず強制的に１４．４のしておきます */
			rate = BPS14400_V34;
		}
	}

	if (src_data_rate != rate) {	/* add if 1996/09/10 */
		/* 希望データレイト書き込み */
		MDM_V34DataRateChange(rate);
		ret = 1;
	}
	else {
		ret = 0;
	}

	return(ret);

}

/*************************************************************************
	module		:[data rate modem's define -> sys_spd define]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		1996/02/13 スピードを示す定義変更（\src\atlanta\doc\letter\mail\R288FQ&A.ANSより)
	
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/01/11]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_V34DataRateDefineChange(UBYTE data_rate)
{
	UBYTE value;
	value = 0;

	switch (data_rate) {
		case 0x03:		/* 2400 */
			value = BPS2400_V34;
			break;
		case 0x04:		/* 4800 */
			value = BPS4800_V34;
			break;
		case 0x08:		/* 7200 */		/* 0x05 -> 0x08  1996/02/13 */
			value = BPS7200_V34;
			break;
		case 0x05:		/* 9600 */		/* 0x06 -> 0x05  1996/02/13 */
			value = BPS9600_V34;
			break;
		case 0x06:		/* 12000 */		/* 0x07 -> 0x06  1996/02/13 */
			value = BPS12000_V34;
			break;
		case 0x07:		/* 14400 */		/* 0x08 -> 0x07  1996/02/13 */
			value = BPS14400_V34;
			break;
		case 0x09:		/* 16800 */
			value = BPS16800_V34;
			break;
		case 0x0A:		/* 19200 */
			value = BPS19200_V34;
			break;
		case 0x0B:		/* 21600 */
			value = BPS21600_V34;
			break;
		case 0x0C:		/* 24000 */
			value = BPS24000_V34;
			break;
		case 0x0D:		/* 26400 */
			value = BPS26400_V34;
			break;
		case 0x0E:		/* 28800 */
			value = BPS28800_V34;
			break;
		case 0x0F:		/* 31200 */
			value = BPS31200_V34;
			break;
		case 0x10:		/* 33600 */
			value = BPS33600_V34;
			break;
		default:
			break;
	}
	return(value);
}


/*************************************************************************
	module		:[]
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
	date		:[1996/02/13]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckMinimumDataRate(void)
{
	UBYTE	value;

	if (V34BaudDataRate == SYMBOL_2400) {
		value = BPS2400_V34;
	}
	else {
		value = BPS4800_V34;
	}

	/*--------------------------------------------------------------
	** 低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
	** それならば、一旦回線断してリダイヤルして再送したほうが通信料金削減になります。
	** 2001/04/25 H.Yoshikawa
	*/
	/* ここから追加	 2001/04/25 H.Yoshikawa */
	switch (TxBaudRate) {
	case BPS7200_V34:
		if (CHK_TxSpeedUpper7200bps()) {
			value = TxBaudRate;
		}
		break;
	case BPS4800_V34:
	case BPS2400_V34:
		if (CHK_TxSpeedUpper7200bps() || CHK_TxSpeedUpper4800bps()) {
			value = TxBaudRate;
		}
		break;
	default:
		break;
	}
	/* ここまで追加	 2001/04/25 H.Yoshikawa */

	if (TxBaudRate == value) {
		return(1);
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＰＯＰＬＡＲ＿Ｈでは、スピードに関する定義がオレンジ用とＲ２８８Ｆ用で
		異なるので、TxBaudRate値がモデムのCONF Register値と異なるため、1バイト追加 by O.Kimoto 1997/12/03
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/02/14]
	author		:[村田]
*************************************************************************/
void  FCM_SetTxDataRate(void)
{
	UBYTE		buffer[6];
	
	if (SYS_V34ProcedureExecuting() == 1) {

		buffer[0] = 0;
		buffer[1] = 0;
		buffer[2] = 0;
		buffer[3] = 0;
		buffer[4] = 0;
		buffer[5] = 0;

		/*TxBaudRate = FCM_CheckTxDataRate(); CTC ON の時にﾘｰﾄﾞ 1996/03/04 */
		buffer[0] = V34BaudDataRate;
		buffer[1] = MDM_TrueConfValue; /* Change TxbaudRate to MDM_TrueConfValue by O.Kimoto 1997/12/02 */

		buffer[2] = MDM_TrueConfValue; /* Change FCM_CONF_Value to MDM_TrueConfValue by O.Kimoto 1997/12/02 */
		buffer[3] = FCM_SPEED_Value;
		buffer[4] = FCM_384_Value;
		buffer[5] = TxBaudRate;

		SaveT30Data( SYS_T30_V34_TX_RATE, &buffer[0], 6 );
	}
}

/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ＰＯＰＬＡＲ＿Ｈでは、スピードに関する定義がオレンジ用とＲ２８８Ｆ用で
		異なるので、TxBaudRate値がモデムのCONF Register値と異なるため、1バイト追加 by O.Kimoto 1997/12/03
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/02/14]
	author		:[村田]
*************************************************************************/
void  FCM_SetRxDataRate(void)
{
#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* PhaseJitter。by H.Kubo 1998/10/06  */
	UBYTE		buffer[10 + 4];
#else
	UBYTE		buffer[11];
#endif	
	if (SYS_V34ProcedureExecuting() == 1) {
		buffer[0] = 0;
		buffer[1] = 0;
		buffer[2] = 0;
		buffer[3] = 0;
		buffer[4] = 0;
		buffer[5] = 0;
		buffer[6] = 0;
		buffer[7] = 0;
		buffer[8] = 0;
		buffer[9] = 0;
		buffer[10] = 0;

#if (PRO_MODEM == R288F) && (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* PhaseJitter。by H.Kubo 1998/10/07 */
		buffer[0] = V34BaudDataRate;
		buffer[1] = MDM_TrueConfValue; /* Change RxbaudRate to MDM_TrueConfValue by O.Kimoto 1997/12/02 */
		buffer[2] = FCM_SPEED_Value;
		buffer[3] = FCM_384_Value;
		buffer[4] = (UBYTE)FCM_SignalToNoiseRatio;
		buffer[5] = (UBYTE)FCM_LowBandEdgeFrequency;
		buffer[6] = (UBYTE)FCM_HighBandEdgeFrequency;
		buffer[7] = (UBYTE)FCM_PreEmphasisFilter;		/* Add By O.Kimoto 1996/07/25 */
		buffer[8] = (UBYTE)FCM_TxLevelReduction;		/* Add By O.Kimoto 1996/07/25 */
		buffer[9] = RxBaudRate;
		buffer[10] = (FCM_PhaseJitterFrequency & 0xff00) >> 8;
		buffer[11] = (FCM_PhaseJitterFrequency & 0x00ff);
		buffer[12] = (FCM_PhaseJitterAmplitude & 0xff00) >> 8;
		buffer[13] = (FCM_PhaseJitterAmplitude & 0x00ff);
		SaveT30Data( SYS_T30_V34_RX_RATE, &buffer[0], 10 + 4 );
#else
		/*RxBaudRate = FCM_CheckRxDataRate(); CTC ON の時にﾘｰﾄﾞ 1996/03/04 */
		buffer[0] = V34BaudDataRate;
		buffer[1] = MDM_TrueConfValue; /* Change RxbaudRate to MDM_TrueConfValue by O.Kimoto 1997/12/02 */

		buffer[2] = MDM_TrueConfValue; /* Change FCM_CONF_Value to MDM_TrueConfValue by O.Kimoto 1997/12/02 */
		buffer[3] = FCM_SPEED_Value;
		buffer[4] = FCM_384_Value;

		buffer[5] = (UBYTE)FCM_SignalToNoiseRatio;
		buffer[6] = (UBYTE)FCM_LowBandEdgeFrequency;
		buffer[7] = (UBYTE)FCM_HighBandEdgeFrequency;
		buffer[8] = (UBYTE)FCM_PreEmphasisFilter;		/* Add By O.Kimoto 1996/07/25 */
		buffer[9] = (UBYTE)FCM_TxLevelReduction;		/* Add By O.Kimoto 1996/07/25 */
		buffer[10] = RxBaudRate;

		SaveT30Data( SYS_T30_V34_RX_RATE, &buffer[0], 11 );
#endif
	}
}



/*************************************************************************
	module		:[エラーフレーム獲得]
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
	date		:[1996/05/16]
	author		:[村田]
*************************************************************************/
void  FCM_GetRxErrorFrame(void)
{
	WORD			fc;
	WORD			partial_fc;
	UBYTE	mask;
	UBYTE	*ecm_status;

	fc = (WORD)ECM_FirstFrameCounter;
	FCM_SavedRxTotalFrameLine = (UWORD)(fc + 1);
	FCM_SavedRxErrorFrameLine = 0;
	partial_fc = (WORD)ECM_FrameCounter;
	FCM_SavedRxPartialFrameLine = (UWORD)(partial_fc + 1);

	ecm_status = &MDM_EcmStatus[0];
	mask = 0x01;

	while (fc >= 0) {	/**	ＰＰＳでのフレームカウンタ分繰り返す	*/
		if ((*ecm_status & mask) != 0) {	/**	エラーフレームあり	*/
			FCM_SavedRxErrorFrameLine++;	/**	エラーフレーム加算	*/
		}
		mask <<= 1;
		fc--;
		if (mask == 0x00) {
			mask = 0x01;
			ecm_status++;
		}
	}

	if (FCM_SavedRxErrorFrameLine == 0) {
		if (FCM_CheckDataRateUp()) {
			FCM_SavedRxNonErrContinuePage++;
		}
		else {
			FCM_SavedRxNonErrContinuePage = 0;
		}
	}
	else {
		FCM_SavedRxNonErrContinuePage = 0;
	}

}

/*************************************************************************
	module		:[Ｖ３４データレイトをあげる]
	function	:[
		1.最初にネゴした通信速度よりは上げない
	]
	return		:[
					1: 速度変更した
					0: 速度変更していない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1996/05/20]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_ChangeDataRateUp(UBYTE src_data_rate)	/* void -> UBYTE 1996/09/10 Y.M */
{
	UBYTE	rate;
	UBYTE	max;
	UBYTE	min;
	UBYTE	ret;	/* 1996/09/10 */

	rate = 0;
	max = 0;
	min = 0;
	ret = 0;

	/* シンボルレートよりｍｉｎ、ｍａｘ求める */
	switch (V34BaudDataRate) {
		case SYMBOL_2400:
			min = BPS2400_V34;
			max = BPS21600_V34;
			break;
		case SYMBOL_2800:
			min = BPS4800_V34;
			max = BPS26400_V34;
			break;
		case SYMBOL_3000:
			min = BPS4800_V34;
			max = BPS28800_V34;
			break;
		case SYMBOL_3200:
			min = BPS4800_V34;
			max = BPS31200_V34;
			break;
		case SYMBOL_3429:
			min = BPS4800_V34;
			max = BPS33600_V34;
			break;
		default:
			min = BPS2400_V34;	/* ありえないけどとりあえず */
			max = BPS21600_V34;
			break;
	}

	if (max > src_data_rate) {
		/* 通信速度をあげる */
		switch (src_data_rate) {
		case BPS33600_V34:
			rate = BPS33600_V34;
			break;
		case BPS31200_V34:
			rate = BPS33600_V34;
			break;
		case BPS28800_V34:
			rate = BPS31200_V34;
			break;
		case BPS26400_V34:
			rate = BPS28800_V34;
			break;
		case BPS24000_V34:
			rate = BPS26400_V34;
			break;
		case BPS21600_V34:
			rate = BPS24000_V34;
			break;
		case BPS19200_V34:
			rate = BPS21600_V34;
			break;
		case BPS16800_V34:
			rate = BPS19200_V34;
			break;
		case BPS14400_V34:
			rate = BPS16800_V34;
			break;
		case BPS12000_V34:
			rate = BPS14400_V34;
			break;
		case BPS9600_V34:
			rate = BPS12000_V34;
			break;
		case BPS7200_V34:
			rate = BPS9600_V34;
			break;
		case BPS4800_V34:
			rate = BPS7200_V34;
			break;
		case BPS2400_V34:
		default:
			rate = BPS4800_V34;
			break;
		}
	}
	else {
		rate = src_data_rate;
	}

#if 0	/* move 1996/10/08 Y.M          MURATTCH */
//	/* シンボルレートよりｍｉｎ、ｍａｘ求める */
//	switch (V34BaudDataRate) {
//		case SYMBOL_2400:
//			min = BPS2400_V34;
//			max = BPS21600_V34;
//			break;
//		case SYMBOL_2800:
//			min = BPS4800_V34;
//			max = BPS26400_V34;
//			break;
//		case SYMBOL_3000:
//			min = BPS4800_V34;
//			max = BPS28800_V34;
//			break;
//		case SYMBOL_3200:
//			min = BPS4800_V34;
//			max = BPS31200_V34;
//			break;
//		case SYMBOL_3429:
//			min = BPS4800_V34;
//			max = BPS33600_V34;
//			break;
//		default:
//			break;
//	}
#endif

	/* 正常な速度かどうかチェック */
	if ((rate >= min) && (rate <= max)) {
		/* 正常な速度 */
	}
	else {
	/* このパスはありえないけど、もしここを通れば、とりあえず強制的に１４．４のしておきます */
		rate = BPS14400_V34;
	}


	if (V34FirstDataRate >= rate) {
		if (src_data_rate != rate) {
			/* 希望データレイト書き込み */
			MDM_V34DataRateChange(rate);
			ret = 1;
		}
		else {
			ret = 0;
		}
	}
	else {
		ret = 0;
	}

	return(ret);
}


/*************************************************************************
	module		:[]
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
	date		:[1996/05/20]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckDataRateUp(void)
{
	UBYTE value;

	value = 0;

	if (ECM_PageCounterBackUp == 0xFFFF) {
		value = 0;
	}
	else {
		if (((UBYTE)ECM_PageCounterBackUp) !=  ECM_PageCounter) {
			value = 1;
		}
		else {
			if (((UBYTE)ECM_BlockCounterBackUp) != ECM_BlockCounter) {
				value = 1;
			}
			else {
				value = 0;
			}
		}
	}
	
	ECM_PageCounterBackUp = (UWORD)ECM_PageCounter;
	ECM_BlockCounterBackUp = (UWORD)ECM_BlockCounter;

	return(value);
}


/*************************************************************************
	module		:[モデムがアボートしたか]
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
	date		:[1996/06/20]
	author		:[村田]
*************************************************************************/
UBYTE  FCM_CheckModemAbort(void)
{
	if (SYS_V34ProcedureExecuting()) {
		if (MDM_ClearToSendAbort == FALSE) {
			return(0);	/* ｱﾎﾞｰﾄしてない */
		}
		else {
			return(1);	/* ｱﾎﾞｰﾄした */
		}
	}
	else {
		return(0);	/* ｱﾎﾞｰﾄしてない */
	}

}

#endif /* (PRO_TX_SPEED == V34) */
