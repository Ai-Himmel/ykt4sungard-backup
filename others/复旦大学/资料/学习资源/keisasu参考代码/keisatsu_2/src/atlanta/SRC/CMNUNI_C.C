/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_c.h	*/
/************************************************
 * CMNUNI_C.C
 * 機種固有スイッチCの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_c.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"

/*************************************************************************
	module		:[ECM受信ﾀｲﾑｰｵｰﾊﾞ回避無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_ECM_RxTM_OutEvade(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C0] & ECM_RX_TMOUT_EVADE));
}

/*************************************************************************
	module		:[メモリ受信中に受信済ページのプリントの有効／無効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1994/09/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_MemoryRxAndPrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C0] & MEMORY_RX_AND_PRINT));
}



/*************************************************************************
	module		:[Tel/Fax待機モード着信後疑似ベル鳴動開始時間の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/04/15]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_GenerateBellWait(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_C0] & GENERATE_BELL_08SEC_WAIT) >> 2));
}



/*************************************************************************
	module		:[TCFチェック時間の獲得]
	function	:[
		1.
	]
	return		:[0～160:0～1600m秒]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/10]
	author		:[吉川弘康]
*************************************************************************/
UWORD CHK_UNI_TCF_CheckTime(void)
{
	return ((UWORD)((SYB_MachineUniqSwitch[UNIQ_SW_C1] & TCF_CHECK_TIME)*100));
}

/*************************************************************************
	module		:[オンフック転送時にCEDを送出しない/するの獲得]
	function	:[
		1.
	]
	return		:[0	   :CED送出しない
				  0以外:CED送出する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/11]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_OnhookTransferCED_Tx(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C0] & ONHOOK_TRANSFER_CED_TX));
}

/*************************************************************************
	module		:[MMR蓄積無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/11]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_StoredMethodMMR(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C0] & STORED_METHOD_MMR));
}

/*#if (PRO_CODEC_TYPE == MN86063)*/
/*************************************************************************
	module		:[インチ/ミリ変換設定]
	function	:[
		1.インチ機からの受信時、インチ／ミリ変換処理を行うか行わないか設定します。
	]
	return		:[0	   :変換しない
				  0以外:インチ／ミリ変換する
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53,SH]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/15]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_InchMiriConvert(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C0] & INCH_MIRI_CONVERT));
}
/*#endif*/

/*************************************************************************
	module		:[Ｅ－ＦＩＮＥ受信能力獲得]
	function	:[
		1.受信時ＮＳＦ／ＮＳＣのEFINEﾋﾞｯﾄをONするかしないか設定します。
	]
	return		:[0	   :受信能力なし
				  0以外:能力あり
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53,SH]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/06/14]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_ExcellentFIne(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C0] & EFINE_RX));
}

/*************************************************************************
	module		:[転送受信後のT1タイマー値の獲得]
	function	:[
		1.
	]
	return		:[0～15:0～15秒]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_RemoteRxT1Timer(void)
{
	return ((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_C1] & RMT_RX_T1_TIMER) >> 4));
}

/*************************************************************************
	module		:[複数ページ受信時のメモりオーバー]
	function	:[
		1.次ページメモり受信できない場合
			0:通常のメモりオーバー時の処理
			1:会話予約をかける
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/01/10]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_MemoryOverRx(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C2] & MEMORY_OVER_PIP_TX));
}

#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  Apr.06.1995 */
/*************************************************************************
	module		:[配信機での不達通知プリント設定の取得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/04/06]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE CHK_RelayedReportPrint(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C2] & RELAYED_REPORT_PRINT));
}
#endif
/*************************************************************************
	module		:[ダイレクトメール防止モード２の時のＴＳＩが来ない場合]
	function	:[
		1.
	]
	return		:[0    :受信する
				  0以外:受信しない
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/18]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_JunkMode2_Rx_No_TSI(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C2] & JUNK_MODE2_NO_TSI));
}

/*************************************************************************
	module		:[JBIG受信]
	function	:[
		1.ＪＢＩＧ受信する／しない
	]
	return		:[0	   :受信する
				  0以外:受信しない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/15]
	author		:[曽根岡]
*************************************************************************/
UBYTE CHK_UNI_JBIG_RX_Enable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C2] & JBIG_RX_ENABLE));
}

/*************************************************************************
	module		:[受信後直ぐに回転起動]
	function	:[]
	return		:[0	   :印刷可能状態判断後回転起動
				  0以外:受信時直ぐ回転起動（記録紙チェック無し）
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/3/16]
	author		:[福井]
*************************************************************************/
UBYTE CHK_UNI_StartRotateAfterRX(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C2] & START_ROTATE_AFTER_RX));
}
/*************************************************************************
	module		:[G3受信蓄積符号化方式]
	function	:[
		1.ＭＲ蓄積：１  ＭＭＲ蓄積：０
	]
	return		:[0	   :ＭＭＲ
				  1    :ＭＲ
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/1/27]
	author		:[鈴木]
*************************************************************************/
UBYTE CHK_UNI_G3_RX_StoreMR(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & G3RX_MR_STORE));
}
/*************************************************************************
	module		:[受信原稿蓄積方式]
	function	:[
		1.Ｃ：２－５～７の値を返す。
	]
	return		:[
				０：SYS_IMAGE_DATA
				１：SYS_MH_CODE
				２：SYS_MR_CODE
				３：SYS_MMR_CODE
				４：SYS_MG3_CODE
				５：SYS_JBIG_CODE
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/04/30]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_NewRxStoredMethod(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_C2] & NEW_RX_STORED_METHOD)>>5));
}

/*************************************************************************
	module		:[縮小後の画像を中央寄せにする。]
	function	:[
		1.中央：１  左寄せ：０
	]
	return		:[0	   :左寄せ
				  1    :中央
				]
	common		:[Ａ３，Ｂ４－＞Ａ４の場合のみ]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/10/6]
	author		:[鈴木]
*************************************************************************/
UBYTE CHK_UNI_ReducedPixToMid(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & REDUCED_PIX_MID));
}

/*************************************************************************
	module		:[Tel/Fax待機モード着信後疑似ベル鳴動時間の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/10/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_GenerateBellPeriod(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C3] & GENERATE_BELL_PERIOD_ALL));
}

#if  (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/20 */
/*************************************************************************
	module		:[R288F モデムで拡張FIFO を使う／使わない]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/10/20]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_UNI_R288fExtendedTxFIFO(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & R288F_EXTENDED_TX_FIFO));
}
/*************************************************************************
	module		:[R288F モデムで拡張FIFO を使う／使わない]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/10/20]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_UNI_R288fExtendedRxFIFO(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & R288F_EXTENDED_RX_FIFO));
}
/*************************************************************************
	module		:[R288F モデムで拡張FIFO を使う／使わない]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/10/20]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_UNI_R288fExtendedRxEcmFIFO(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & R288F_EXTENDED_RX_FIFO));
}
#endif

/*************************************************************************
	module		:[Ｖ１７以下の受信方式の獲得]
	function	:[
		1.
	]
	return		:[ V17_MRX_TO_PRX	メモリ受信優先 メモリ受信不可の場合、プリンタ受信
				   V17_MRX_TO_MRX	強制メモリ受信
				   V17_PRX_TO_MRX	プリンタ受信優先 プリンタ受信不可の場合、メモリ受信
				   V17_PRX_TO_PRX	強制プリンタ受信
				  ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/11/17]
	author		:[H.Hirao]
*************************************************************************/
#if (PRO_PRINTER_RX == ENABLE)
UBYTE CHK_UNI_V17ReceiveType(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C3] & 0x30));
}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*/
UBYTE CHK_UNI_V17ReceiveType(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C3] & 0x30));
}
#endif
/*************************************************************************
	module		:[Ｖ３４の受信方式の獲得]
	function	:[
		1.
	]
	return		:[ V34_MRX_TO_PRX	メモリ受信優先 メモリ受信不可の場合、プリンタ受信
				   V34_MRX_TO_MRX	強制メモリ受信
				   V34_PRX_TO_MRX	プリンタ受信優先 プリンタ受信不可の場合、メモリ受信
				   V34_PRX_TO_PRX	強制プリンタ受信
				 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/11/17]
	author		:[H.Hirao]
*************************************************************************/
#if (PRO_PRINTER_RX == ENABLE)
UBYTE CHK_UNI_V34ReceiveType(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C3] & 0xC0));
}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/16 K.Kawata*/
UBYTE CHK_UNI_V34ReceiveType(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C3] & 0xC0));
}
#endif


/*#if defined(POPLAR_H) && defined(JP0)@* V851 By Y.Suzuki 2002/08/23 */
#if (PRO_ROTATE == ENABLE)
/*************************************************************************
	module		:[回転受信をするﾒﾓﾘの閾値]
	function	:[
		1.
	]
	return		:[ 
						設定値（ﾌﾞﾛｯｸ）
				 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,SH]
	language	:[MS-C(Ver.6.0),SH(日立マイコン)]
	keyword		:[CMN]
	date		:[2002/08/23]
	author		:[By Y.Suzuki]
*************************************************************************/
UBYTE CHK_UNI_GetMemoryBlockForRotPrt()
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C4]));
}
#endif



/*************************************************************************
	module		:[NTTいまどこＦＡＸ対策ＭＨ符号化方式のみ]
	function	:[
		ＭＨ符号化方式：１  全符号化方式：０
	]
	return		:[1	   :ＭＨ
				  0    :全て
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/11/24]
	author		:[鈴木]
*************************************************************************/
UBYTE CHK_UNI_TakeCareImadokoMH(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & MH_ONLY_CARE_IMADOKO));
}

/*************************************************************************
	module		:[応答受信のタイムアウトを６秒にする]
	function	:[
	]
	return		:[0    :無効
				  0以外:有効
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/02/16]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_RcvResponseTime6sec(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C9] & RECEIVE_RESPONSE_TIME_6SEC));
}


#if defined(POPLAR_F)
/*
 *	新Ｌ４００用 FAN騒音対策の温度の敷居値
*/
UBYTE	CHK_UNI_FanOnTempThreshold(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_C6]));
}

/*
 *	新Ｌ４００用 FAN騒音対策の敷居値以下のFAN回転時間
*/
UWORD	CHK_UNI_FanStopTimerLowTemp(void)
{
	UWORD time;

	time = (UWORD)SYB_MachineUniqSwitch[UNIQ_SW_C7] * (UWORD)60;
	if (time) {
		return(time);
	}
	else {
		return(5);
	}
}

/*
 *	新Ｌ４００用 FAN騒音対策の敷居値以上のFAN回転時間
*/
UWORD	CHK_UNI_FanStopTimer(void)
{
	UWORD time;

	time = (UWORD)SYB_MachineUniqSwitch[UNIQ_SW_C8] * (UWORD)60;
	return(time);
}

#endif


