/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_d.h	*/
/************************************************
 * CMNUNI_D.C
 * 機種固有スイッチＤの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_d.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/11/05 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\ext_v\sys_data.h" 			/* Added by H.Kubo 1997/07/19 for SYS_V8DetectATV25Flag */
#endif

/* コンパイルを通すだけのダミー関数 */
UBYTE CHK_UNI_Dummy_D(void)
{
	return (0);
}

/*************************************************************************
	module		:[Ｖ３４通信時の使用可能シンボルレート]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
					Ｒ２８８Ｆは２７４３はサポートしていない
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34SymboleRate(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D0] & 0x3D));
}


/*************************************************************************
	module		:[Forced 2400 Symbol Rate when Probing SNR is AdverseのＳＮ比]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34Forced2400SymbolRateSNR(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D1]));
}


/*************************************************************************
	module		:[Ｖ３４通信時のＡＲＡアルゴリズム設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ARA_AlgorithmEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_ARA_ALGORITHM_ENABLE));
}


/*************************************************************************
	module		:[Ｖ３４コントロールチャンネルの希望速度]
	function	:[
		1.
	]
	return		:[
					0: 1200BPS
					1: 2400BPS
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ContorlChannelRate(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_CONTROL_CHANNEL_RATE_2400));
}


/*************************************************************************
	module		:[Ｖ８ＡＮＳａｍ送出時間]
	function	:[
		1.
	]
	return		:[
					0: 3sec
					1: 4sec
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V8TransmitANSamTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V8_TRANSMIT_ANSAM_TIME));
}


/*************************************************************************
	module		:[ＦＳＫエラー時にコントロールチャネルのリトレーンをするか否か]
	function	:[
		1.
	]
	return		:[
					0: リトレーンしない
					1: リトレーンする
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ControlChannelRetrain(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_CONTROL_CHANNEL_RETRAIN));
}


/*************************************************************************
	module		:[受信局からも通信速度を変更するか否か]
	function	:[
		1.
	]
	return		:[
					0: 変更しない
					1: 変更する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34RxDataRateChange(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_RX_DATA_RATE_CHANGE));
}


/*************************************************************************
	module		:[受信局から通信速度を変えるパターン]
	function	:[
		1.
	]
	return		:[
					0: 最初のﾌﾚｰﾑｶｳﾝﾀｰの10%
					1: ﾌﾚｰﾑｶｳﾝﾀｰの10%
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34RxDataRateChangeType(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_RX_DATA_RATE_CHANGE_TYPE));
}


/*************************************************************************
	module		:[受信側から通信速度を上げるか否か（D2:4が1の時有効）]
	function	:[
		1.
	]
	return		:[
		0以外: 上げる
			0: 上げない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34RxDataRateUp(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_RX_DATA_RATE_UP));
}

/*************************************************************************
	module		:[手動交信時Ｖ８を行うか否か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[UNI]
	date		:[1996/12/27]
	author		:[村田]
*************************************************************************/
UBYTE CHK_ManualFaxComV8Enable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D2] & V34_MANUAL_FAXCOM_V8_ENABLE));
}


/*************************************************************************
	module		:[Ｖ３４スタートアップ時にモデムのアボートコードを無視するか否か]
	function	:[
		1.
	]
	return		:[
					0: 無視する
					1: 無視しない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ModemAbcodeEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_MODEM_ABCODE_FOR_STRATUP));
}


/*************************************************************************
	module		:[ＣＩ検出松下対策]
	function	:[
		1.
	]
	return		:[
					0: 
					1: 
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34DetectCIforMGCS(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_DETECT_CI_FOR_MGCS));
}


/*************************************************************************
	module		:[ＣＩ送出中のＡＮＳａｍをフルターで検出する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34DetectANSam_DuringCI(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_DETECT_ANSAM_DURING_CI));
}


/*************************************************************************
	module		:[ﾛｯｸｳｴﾙﾓﾃﾞﾑ同期対策 PPH強制送出]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ForcedPPh(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_MODEM_FORCED_PPH));
}

/*************************************************************************
	module		:[ラインプロービング問題の対策をするか否か]
	function	:[
		1.
	]
	return		:[
						0:しない
					0以外:する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/11/06]
	author		:[村田]
*************************************************************************/
UBYTE CHK_RecoverLineProblingProblem(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_LINE_PLOBING_PROBLEM));
}


/*************************************************************************
	module		:[送出レベルを個別の属性にあわせるか否か]
	function	:[
		1.
	]
	return		:[
						0:あわせない（機器レベル）
					0以外:属性にあわせる
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/27]
	author		:[村田]
*************************************************************************/
UBYTE CHK_TxLevelAttribute(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_TX_LEVEL_ATTRIBUTE));
}

/*************************************************************************
	module		:[オプションボードでＶ３４をマスクするか否か]
	function	:[
		1.
	]
	return		:[
			0     :Ｖ３４で交信する（Ｖ３４のリソースを持つ）
			0以外 :Ｖ３４で交信しない（Ｖ１７以下で行う）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[UNI]
	date		:[1997/01/26]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34SiganalRateV34Mask(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_V34SIGNAL_RATE_MASK));
}

/*************************************************************************
	module		:[ＡＲＡテーブルを標準のＲＯＭを使用するか否か]
	function	:[
		1.
	]
	return		:[
						0:ＡＲＡｉｎＲＡＭを使用（自分らであわしたやつ）
					0以外:ＡＲＡｉｎＲＯＭを使用（ロックウエル標準）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/01/26]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ARA_ThresholdARAinROM(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D3] & V34_ARA_THRESHOLD_ARA_IN_ROM));
}


/*************************************************************************
	module		:[Ｖ３４手動の手順を実行するか否か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/01/29]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34ManualProcedureEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_MANUAL_PROCEDURE_ENABLE));
}

/*************************************************************************
	module		:[Ｒ２８８Ｆスパイクノイズ対策有効／無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/01/30]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34SpikeNoiseEvasion(void)
{
#if (PRO_MODEM == R288F) /* ===== Ported from CLOVER by H.Kubo 1997/11/05 ===== */
	/* Ｒ６７１３－２２Ｐ対応
	** －２２Ｐでは、このスパイクノイズ対策が入っていると
	** 誤動作するらしいので、モデムバージョンをチェックして、
	** －２２Ｐならば、メモリスイッチの設定に関わらず、無効とします。
	** By O.Kimoto 1997/07/03
	*/
	if ((SYS_ModemVersion == MDM_L6713_14P) || (SYS_ModemVersion == MDM_L6713_20P)) {
		return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_SPIKE_NOISE_EVASION));
	}
	else {
		return((UBYTE)0);
	}
#else  /* (PRO_MODEM == R288F) */
	/* return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_SPIKE_NOISE_EVASION)); */
#endif  /* (PRO_MODEM == R288F) */
}

/*************************************************************************
	module		:[連続ｴﾗｰﾗｲﾝによるｷｬﾘｱ断ﾀｲﾏ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/02/01]
	author		:[村田]
*************************************************************************/
UBYTE CHK_NoCarryOrErrorLineTime(void)
{
	switch (SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_NO_CARRY_OR_ERROR_TIME) {
	case 0x00:
		return(15);
		break;
	case 0x04:
		return(10);
		break;
	case 0x08:
		return(20);
		break;
	case 0x0C:
		return(30);
		break;
	default:	/* ありえない */
		return(5);
		break;
	}
}


UBYTE CHK_V34_V29_7200Special(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_V29_7200_SPECIAL) {
		return(1);
	}
	else {
		return(0);
	}
}


/*************************************************************************
	module		:[留守/ＦＡＸ 無音検出レベル敷居値の獲得]
	function	:[
		1.
	]
	return		:[ソフト設定値
				  ON		OFF
			0:	 -43dBm		-48dBm
			1:	 -33dBm		-38dBm
			2:	 -26dBm		-31dBm
			3:	 -16dBm		-21dBm
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/02/21]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34_AnsFaxSilentLevel(void)
{
	switch (SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_ANS_FAX_SILENT_LEVEL) {
	case 0x00:
		return(0);
	case 0x20:
		return(1);
	case 0x40:
		return(2);
	case 0x60:
		return(3);
	default:
		return(1);
	}
}


/*************************************************************************
	module		:[留守/ＦＡＸ ＣＮＧ検出方法の獲得]
	function	:[
		1.	０に設定されている時は、ソフトで無音検出をします、
			この時ＣＮＧ検出はハードのみで行います。
			１に設定されている時は、ソフトで、ＣＮＧも無音も検出します
		2.	この切り替えＳＷを設けた理由は、ＣＮＧと無音を同時に検出しようと
			すると、アンズではプリンタが動作するとノイズのため無音が検出できないためです。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/02/21]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34_AnsFaxCNGPriorty(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_D6] & V34_ANS_FAX_CNG_PRI) {
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
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/04/25]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34_V21_R42EvasionEnable(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_D7] & V34_V21_R42_EVASION) {
		return(1);
	}
	else {
		return(0);
	}

}

/*************************************************************************
	module		:[モデム動作周波数不具合対策の有効/無効の獲得]
	function	:[
		1.「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７で
		   受信できないことがある」
	]
	return		:[
		###	注意！注意！注意！###
					０：有効
					１：無効
		既にアンズがでているため、標準でこの対策を入れたいし、
		０：で有効と言う形にします。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/08/28]
	author		:[村田]
				:[久保] (1997/10/27)
*************************************************************************/
UBYTE CHK_V34_R288F_WayWorkFreqBug(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_D7] & V34_R288F_WAY_WORK_FREQ_BUG) {
		return(1);
	}
	else {
		return(0);
	}

}

#if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006) /* Ported from Clover by H.Kubo 1998/02/03 */
/*************************************************************************
	module		:[Ｖ３４ポストメッセージリトレーン対策]
	function	:[
		1.受信ﾚﾍﾞﾙが-39dBmで遅延がない時にﾘﾄﾚｰﾝが発生する
		  ２発目のﾎﾟｽﾄﾒｯｾｰｼﾞとﾘﾄﾚｰﾝがかぶってしまう時がある。
		  その後、ﾌﾗｸﾞ誤検出して３秒の遅延時間がはたらいて、結果ﾎﾟｽﾄﾒｯｾｰｼﾞが
		  ６秒後にでてしまう。この３秒の遅延を行うかをどうかのＳＷです。
	]
	return		:[
		###	注意！注意！注意！###
					０：有効
					１：無効
		既にアンズがでているため、標準でこの対策を入れたいし、
		０：で有効と言う形にします。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/10/07]
	author		:[村田]
*************************************************************************/
UBYTE CHK_V34_PostExpired(void)
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_D7] & V34_POST_EXPIRED) {
		return(1);
	}
	else {
		return(0);
	}
}


/*************************************************************************
	module		:[Ｖ３４ポストメッセージリトレーン対策]
	function	:[
		1.受信ﾚﾍﾞﾙが-39dBmで遅延がない時にﾘﾄﾚｰﾝが発生する
		  ２発目のﾎﾟｽﾄﾒｯｾｰｼﾞとﾘﾄﾚｰﾝがかぶってしまう時がある。
		  かぶらないようにFSKの頭にﾌﾟﾘｱﾝﾌﾞﾙをつけてずらす対策です。
	]
	return		:[
		###	注意！注意！注意！###
					０：有効
					１：無効
		既にアンズがでているため、標準でこの対策を入れたいし、
		０：で有効と言う形にします。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/10/07]
	author		:[村田]
*************************************************************************/
UWORD CHK_V34_PreambleTime(void)
{
	UBYTE data;

	data = (UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_D7] & 0x18) >> 3);

	switch (data) {
	case 0:
		return(0);		/* 0ms */
	case 1:
		return(10);		/* 100ms */
	case 2:
		return(20);		/* 200ms */
	case 3:
		return(30);		/* 300ms */
	default:
		return(0);
	}

}

#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/20 */
/*************************************************************************
	module		:[]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/10/21]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_R288fModemRthLevel(void)
{
	return (UBYTE) ((SYB_MachineUniqSwitch[UNIQ_SW_D7] & R288F_MODEM_RTH_LEVEL) >> 6);
}
#endif /* (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) */

#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_26P) /* added by H.Kubo 1999/03/01 */
/*************************************************************************
	module		:[]
	function	:[
	]
	return		:[
				0 	: 	モデムの初期値を使用する印
				0-3F:	モデムの設定値
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/03/01]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_V34Disable3429SymbolRateSNR(void)
{
	return (UBYTE) (SYB_MachineUniqSwitch[UNIQ_SW_D9] & V34_3429_SYMBOL_RATE_THRESHOLD);
}
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC */
/*************************************************************************
	module		:[]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/11/28]
	author		:[松本正幸]
*************************************************************************/
UBYTE CHK_ReceiveDtmfLevelRange(void)
{
	return (UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_D5] & 0x70) >> 4);
}
#endif

/*************************************************************************
	module		:[リンク特性に対する選択するシンボルレート調整（ON/OFF)]
	function	:[
		1.
	]
	return		:[
		0: ENABLE
		1: DISABLE
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_V34SymbolRateTuningDisable(void){}]
	date		:[1999/10/18]
	author		:[木元 修]
*************************************************************************/
UBYTE CHK_V34SymbolRateTuningDisable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D4] & V34_SYMBOL_RATE_TUNING_DISABLE));
}

/*************************************************************************
	module		:[リンク特性に対する選択するシンボルレート調整]
	function	:[
		1.機種固有スイッチＤ：４－４～６の値にしたがって、Ｒ２８８Ｆの
		  ＤＳＰ－ＲＡＭアドレス＝＄０６Ａ１，＄０６Ａ２の値を変更する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_V34SymbolRateTuningValue(void){}]
	date		:[1999/10/18]
	author		:[木元 修]
*************************************************************************/
UBYTE CHK_V34SymbolRateTuningValue(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_D4] & (V34_SYMBOL_RATE_TUNEALL)) >> 3));
}

/*************************************************************************
	module		:[TEL/FAX ANS/FAX切り替え時 V34をマスクする]
	function	:[
		1.ＮＴＴのみです。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_V34SymbolRateTuningValue(void){}]
	date		:[1999/11/05]
	author		:[村田]
*************************************************************************/
/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
UBYTE CHK_TelFax_AnsFaxV34Mask(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D7] & TEL_FAX_V34_MASK));
}
 #endif
#endif

/*************************************************************************
	module		:[ANS/FAX待機時の、CNG検出のﾚﾍﾞﾙを上げる]
	function	:[
		1.CNG検出のﾚﾍﾞﾙを上げると、留守電の応答ﾒｯｾｰｼﾞをCNGと誤検出する可能性があります。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2000/02/22]
	author		:[村田]
*************************************************************************/
/*#if defined(POPLAR_F)*/
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))	/* ANS/FAX待機時の、CNG検出のﾚﾍﾞﾙを上げる */
UBYTE CHK_AnsFaxCNG_DetLevelUp(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_D5] & ANS_FAX_CNG_DET_LEVEL_UP));
}
#endif


#endif /* (PRO_MODEM == R288F) Ported from Clover by H.Kubo 1998/02/03 */
