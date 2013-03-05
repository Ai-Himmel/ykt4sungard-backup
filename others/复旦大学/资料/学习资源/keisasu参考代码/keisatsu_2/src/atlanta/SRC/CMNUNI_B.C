/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\define\cmnuni_b.h	*/
/************************************************
 * CMNUNI_B.C
 * 機種固有スイッチBの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_b.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_RELAYED_REPORT == ENABLE)
#include "\src\atlanta\define\sysdoc.h"
#endif


/*************************************************************************
	module		:[ECMエラー再送時のPPR送出回数]
	function	:[
		1.
	]
	return		:[1～4:1～4回]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/01/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_PPR_Count(void)
{
	return ((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_B0] & (PPR_COUNT1 | PPR_COUNT2)) + 1));
}


/*************************************************************************
	module		:[後手順短縮ハンドシェイク無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/06/15]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE CHK_UNI_PostSpeedHandshake(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & POST_SPEED_HANDSHAKE));
}

/*************************************************************************
	module		:[TTIインサイド無効/有効の獲得]
	function	:[
		1.	USAはTTIのインサイドは無効
	]
	return		:[0	   :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/01/08]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_TTI_Inside(void)
{
#if (0)		/* 1996/10/17 By N.Sakamoto */
	#if defined(USA) || defined(AUS)	/* USA */
	return (0);
	#else
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & TTI_INSIDE));
	#endif
#endif

#if defined(USA)			/* 1996/10/17 By N.Sakamoto */
	return (0);
#else
	#if defined(AUS)
	if (SYB_MachineParameter[0] == 0 ) {	/* AUS */
		return (0);
	}
	else{									/* THA,SGP */
		return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & TTI_INSIDE));
	}
	#else
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & TTI_INSIDE));
	#endif
#endif
}

/*************************************************************************
	module		:[ＦＳＫ送信オープンのモデムの設定方法]
	function	:[
		1.この設定切り替えで、ＦＳＫのプリアンブル前のゴミデータの量がかわります。
		　量産段階での変更により、メモリＳｗにより個別対応扱いにします。
　　　　　現在のところ、ＦＸ・海外専用線交信のみ不具合がでています。
		  ポプラでは初期値１：２７ｍｓとします。保守スイッチに移動
	]
	return		:[0	   :173msのゴミ　従来どうり（松・竹・桜と同じ方法）
				  0以外:27msのゴミ
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1995/05/16]
	author		:[曽根岡]
*************************************************************************/
UBYTE CHK_UNI_FSK_TxOpenMethod(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & FSK_TX_OPEN_METHOD));
}

/*************************************************************************
	module		:[ＴＴＩサイズ縮小]
	function	:[
		1.ファイン･Ｓファイン時副走査方向を１／２にする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/07/02]
	author		:[鈴木郁ニ]
*************************************************************************/
UBYTE CHK_UNI_TTI_Size(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & TTI_SIZE_REDUCE));
}

/*************************************************************************
	module		:[ＮＳＦが取れない場合、もう一度取りに行く]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/04/22]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_CommunicationNeedNSF(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & NEED_NSF));
}

/*************************************************************************
	module		:[後手順短縮時のプリアンブル送出時間]
	function	:[
		1.
	]
	return		:[
		10～2550 (ms)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	date		:[1994/12/15]
	author		:[竹内 茂樹]
*************************************************************************/
UWORD CHK_UNI_PostMsgPreambleTime( void )
{
	if (SYB_MachineUniqSwitch[UNIQ_SW_B1] == 0) {
		return (500);
	}
	else {
		return (SYB_MachineUniqSwitch[UNIQ_SW_B1] * 10);
	}
}

/*************************************************************************
	module		:[応用通信の時短縮ハンドシェイク無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/23]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_OptionSpeedHandshake(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B2] & SPEED_HANDSHAKE_OPTION));
}


/*************************************************************************
	module		:[新短縮ハンドシェイク無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/01/23]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_SpeedHandshakeEx(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B2] & SPEED_HANDSHAKE_EX));
}

/*************************************************************************
	module		:[新短縮ＨＳ 着信から着信トーン送出までのｳｪｲﾄ時間獲得]
	function	:[
		1.
	]
	return		:[0 ～ 1500](ms)
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/01/23]
	author		:[t.yamaguchi]
*************************************************************************/
UWORD CHK_UNI_SPDToneWaitTime(void)
{
	return(((SYB_MachineUniqSwitch[UNIQ_SW_B3] & 0xF0) >> 4)*100);
}

/*************************************************************************
	module		:[新短縮ＨＳ SDCS～SCFR(FTT)送出までのｳｪｲﾄ時間獲得]
	function	:[
		1.
	]
	return		:[0 ～ 1500](ms)
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/01/23]
	author		:[t.yamaguchi]
*************************************************************************/
UWORD CHK_UNI_SCFRWaitTime(void)
{
	return((SYB_MachineUniqSwitch[UNIQ_SW_B4] & 0x0F)*100);
}

/*************************************************************************
	module		:[新短縮ＨＳ 着信トーン周波数獲得]
	function	:[
		1.
	]
	return		:[0: 2100Hz
				  1:  697Hz
				  2:  770Hz
				  3:  852Hz
				 ]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/01/23]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_ArrivalSignalToneType(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B2] & AS_TONE_TYPE));
}

/*************************************************************************
	module		:[新短縮ＨＳ 着信トーン送出時間獲得]
	function	:[
		1.
	]
	return		:[0 ～ 1500](ms)
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/01/23]
	author		:[t.yamaguchi]
*************************************************************************/
UWORD CHK_UNI_ArrivalSignalToneTxTime(void)
{
	return((SYB_MachineUniqSwitch[UNIQ_SW_B3] & AS_TONE_TIME)*100);
}

/* #if 0 クラス１で使用 1997/07/16 Y.Matsukuma */
/*************************************************************************
	module		:[インチ系送受信能力獲得]
	function	:[
		1.
	]
	return		:[0	   :能力なし
				  0以外:能力有り
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/02/15]
	author		:[t.yamaguchi]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE CHK_UNI_Inch_TRxFlsRom(void)
#else
UBYTE CHK_UNI_Inch_TRx(void)
#endif
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B5] & INCH_TRX));
}
/* #endif */

#if (PRO_SPD_MODE == ENABLE)	/* 96/06/17 */
/*************************************************************************
	module		:[モードチェンジの時の短縮ﾊﾝﾄﾞｼｪｰｸ]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/22]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_HiSpeedModeChange(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B5] & MODE_CHANGE_HISPEED_HANDSHAKE));
}

/*************************************************************************
	module		:[モードチェンジの時のCNG方式のみの短縮ﾊﾝﾄﾞｼｪｰｸ]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/22]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_SpeedModeChange(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B5] & CNG_ONLY_SPEED_HANDSHAKE));
}

/*************************************************************************
	module		:[モードチェンジの時のＳＤＣＳ方式のみの短縮ﾊﾝﾄﾞｼｪｰｸ]
	function	:[
		1.
	]
	return		:[0	   :無効
				  0以外:有効
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/22]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_SDCSModeChange(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B5] & SDCS_ONLY_SPEED_HANDSHAKE));
}
#endif

/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.ＤＴＣのＦｺｰﾄﾞﾋﾞｯﾄをたててこない機種に対応する
		2.ＤＣＳのＦコードビットを立ててこない機種に対応する
	]
	return		:[0	   :無効
				  0以外:有効
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/22]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_OldFCodeBit(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & IGNORE_F_CODE_BIT));
}

/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.親展ポーリングを有効にする
	]
	return		:[0	   :無効
				  0以外:有効
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53/SH]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/22]
	author		:[t.yamaguchi]
*************************************************************************/
UBYTE CHK_UNI_FcodeSecureDocPollTx(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & SECURE_POLLING_ENABLE));
}

/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.Ｆコードポーリング送信時にＴＴＩにＢＯＸ名とＳＵＢを付ける
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
	date		:[1997/05/09]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_F_CODE_TTI_On(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & F_CODE_DOC_TTI_ON));
}

/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.モード変更後にＳＵＢ／ＰＷＤを付けない
	]
	return		:[0	   :付ける
				  0以外:付けない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/05/09]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_SUB_Frame_Off(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & F_CODE_SUB_FRAME_OFF));
}
/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.ＳＵＢ／ＰＷＤ／ＳＥＰのスペースを無視しない
	]
	return		:[0	   :無視する
				  0以外:無視しない（スペースまでチェックする）
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/05/09]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_Fcode_ID_Space_Check(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & F_CODE_SUB_ID_SPACE_CHECK));
}

/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.ＳＵＢ／ＰＷＤ／ＳＥＰにスペース、＊、＃を途中に入れる
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
	date		:[1997/06/06]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_Fcode_Space_Tx_Enable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & F_CODE_SUB_SPACE_ENABLE));
}

/*************************************************************************
	module		:[Ｆコード通信]
	function	:[
		1.ＳＵＢ／ＰＷＤ／ＳＥＰにスペース、＊、＃を登録できる
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
	date		:[1997/06/06]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_FcodeSpaceInputEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B6] & F_CODE_INPUT_SPACE_ENABLE));
}


#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  Apr.06.1995 */
/*************************************************************************
	module		:[中継配信不達通知　あり／なし]
	function	:[
		1.
	]
	return		:[0    :なし
				  0以外:あり
]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1995/02/08]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CHK_RelayedTxReport(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B5] & RELAYED_TX_REPORT));
}

/*************************************************************************
	module		:[中継配信不達通知　原稿長]
	function	:[
		1.
	]
	return		:[
		SYS_A4_LENGTH
		SYS_B4_LENGTH
		SYS_NO_LIMIT
]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/01/19]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_RelayedTxReportPaperLength(void)
{
#if 0 /* changed by H.Kubo 1998/01/21 */
** 	UBYTE paper_length;
** 	paper_length = SYB_MachineUniqSwitch[UNIQ_SW_B5] 
** 	& ( RELAYED_TX_REPORT_PAPER_LENGTH0 | RELAYED_TX_REPORT_PAPER_LENGTH1);
** 	if (paper_length & RELAYED_TX_REPORT_PAPER_LENGTH0) {
** 		return SYS_NO_LIMIT;
** 	}
** 	else {
** 		if (paper_length & RELAYED_TX_REPORT_PAPER_LENGTH1) {
** 			return SYS_B4_LENGTH;
** 		}
** 		else {
** 			return SYS_A4_LENGTH;
** 		}
** 	}
#else
	if (SYB_MachineUniqSwitch[UNIQ_SW_B5] & RELAYED_TX_REPORT_PAPER_LENGTH) {
		return SYS_NO_LIMIT;
	}
	else {
		return SYS_A4_LENGTH;
	}
#endif

}
#endif

/*************************************************************************
	module		:[暗号化送信]
	function	:[
		1.暗号化受信能力がない相手機に対して、送信しない
	]
	return		:[0	   :送信する
				  0以外:送信しない
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/06/06]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_Error_NonCiperRx(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & ERROR_NON_CIPHER_RX_ABILITY));
}
/*************************************************************************
	module		:[JBIG送信]
	function	:[
		1.ＪＢＩＧ送信する／しない
	]
	return		:[0	   :送信する
				  0以外:送信しない
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
UBYTE CHK_UNI_JBIG_TX_Enable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & JBIG_TX_ENABLE));
}

/*************************************************************************
	module		:[JBIG ２ラインテンプレート選択する]
	function	:[
		1.JBIG ２ラインテンプレート選択する／しない
	]
	return		:[0	   :３ラインテンプレート
				  0以外:２ラインテンプレート
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/03/16]
	author		:[曽根岡]
*************************************************************************/
UBYTE CHK_UNI_JBIG_2lineTemplate(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & JBIG_2LINE_TEMPLATE));
}

/*************************************************************************
	module		:[JBIG ＴＰモード]
	function	:[
		1.JBIG ＴＰモード有効／無効
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
	date		:[1998/03/16]
	author		:[曽根岡]
*************************************************************************/
UBYTE CHK_UNI_JBIG_TPB_Mode(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & JBIG_TPB_MODE));
}

/*************************************************************************
	module		:[JBIG終端マーカＳＤＲＳＴ選択する]
	function	:[
		1.JBIG終端マーカＳＤＲＳＴ選択する／しない
	]
	return		:[0	   :SDNORM選択
				  0以外:SDRST選択
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/03/16]
	author		:[曽根岡]
*************************************************************************/
UBYTE CHK_UNI_JBIG_SDRST(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & JBIG_SDRST));
}

/*************************************************************************
	module		:[スキャナ送信時にMRで送信する]
	function	:[
		1.スキャナ送信時にMRで送信する
	]
	return		:[0	   :初期値で送信する（SAKAKIではMMR）
				  0以外:MRで送信する
				]
	common		:[
		1.SAKAKIでMMRでデコードエラー発生するための暫定対策Bitです
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/11/22]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_ScannerTxMR(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & SCANNER_TX_MR));
}

/*************************************************************************
	module		:[新JATE基準９８で、送出レベル調整を０ｄＢまで可能にする]
	function	:[
		1.
	]
	return		:[0	   :送出レベルの調整範囲は最大－８ｄｍ以下となるように制限する
				  0以外:送出レベルの調整範囲を０ｄＢまで可能にする
				]
	common		:[
		1.新JATE基準９８では、送出レベルの調整範囲は最大－８ｄｍ以下でなければならない。
		2.しかし、フィールドにおいては、より送出レベルを上げる必要があるかもしれない。
		3．FEMには記述しない。
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/01/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_TxLevelUpper0DB(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B7] & TX_LEVEL_UPPER_0DB));
}


#if (PRO_RESULT_REPORT_TX == ENABLE)
/*************************************************************************
	module		:[中継配信／Ｆコード中継配信時、結果通知を返すかどうか]
	function	:[
		1.中継配信／Ｆコード中継配信時に指示局に対して結果通知を返信するかどうか
	]
	return		:[0	   :結果通知は返さない
				  0以外:結果通知を返す。
				]
	common		:[
		1.不達通知との組み合わせが発生するので注意が必要。
		  基本的な優先順位としては
		  	１．不達通知
		  	２．結果通知
		  とします。
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/10]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_ResultReportTxEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B5] & RELEYED_RESULT_REPORT_TX));
}
#endif


#if (PRO_CSDR_ITEM == ENABLE)
/*************************************************************************
	module		:[手動送信時、ＮＳＦが必要かどうか？]
	function	:[]
	return		:[0	   :必要
				  0以外:不要
				]
	common		:[]
	condition	:[]
	comment		:[
				CSDR-No.83】手動送信時、1回目のNSFが検出されなくても非自社機モードで通信する。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/12/14]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_NoNeedNsfToManualTx(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B8] & MANUAL_TX_WITHOUT_NSF_ENABLE));
}
#endif


/*************************************************************************
	module		:[T5 タイマー(RNR-RR のやり取りの時間制限)の長さ]
	function	:[
		1.
	]
	return		:[1, 3, 5, 7 (分)]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1999/03/09]
	author		:[久保博]
*************************************************************************/
UBYTE CHK_UNI_T5_Timer(void)
{
	switch (SYB_MachineUniqSwitch[UNIQ_SW_B8] & T5_TIMER_SELECTION) {
	case T5_TIMER_3_MINUTE:
		return 3;
	case T5_TIMER_5_MINUTE:
		return 5;
	case T5_TIMER_7_MINUTE:
		return 7;
	default:
		return 1;
	}
}

/*************************************************************************
	module		:[2400bpsへのフォールバックを禁止するか否かを獲得する。]
	function	:[
		1.
	]
	return		:[0	   :4800bpsから2400bpsへのフォールバックを認める
				  0以外:4800bpsから2400bpsへのフォールバックを認めない。回線断
				]
	common		:[]
	condition	:[]
	comment		:[
		低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
		それならば、一旦回線断した後に、リダイヤルして再送したほうが通信料金削減になる
	]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/03/06]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_TxSpeedUpper4800bps(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B8] & TX_SPEED_UPPER_4800BPS));
}

/*************************************************************************
	module		:[4800bpsへのフォールバックを禁止するか否かを獲得する。]
	function	:[
		1.
	]
	return		:[0	   :7200bpsから4800bpsへのフォールバックを認める
				  0以外:7200bpsから4800bpsへのフォールバックを認めない。回線断
				]
	common		:[]
	condition	:[]
	comment		:[
		低速な交信速度で大量の送信を行うと、通信時間が大幅に増加してしまう。
		それならば、一旦回線断した後に、リダイヤルして再送したほうが通信料金削減になる
	]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2001/03/06]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_TxSpeedUpper7200bps(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B8] & TX_SPEED_UPPER_7200BPS));
}

#if defined(POPLAR_H) && defined(JP1)/* V851 関西電力専用線 By Y.Suzuki 2003/05/30*/
/*************************************************************************
	module		:[送信時、CNGのかわりに1300Hzを送出する]
	function	:[
		1.ダイヤルなしで原稿セット＋スタートキー押下で送信開始する。
	]
	return		:[0	   :CNGのかわりに1300Hzを送出
				  0以外:CNGを送出する通常の送信
				]
	common		:[]
	condition	:[]
	comment		:[
			関西電力専用線仕様
	]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2003/05/30]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CHK_TransmitBy1300Hz(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B0] & TRANSMIT_1300HZ));
}
#endif

#if defined(STOCKHM2) || defined(HINOKI3)	/* ２値ガンマ補正テーブルの車検証モードの新設 Y.Kano 2004/10/26 */ /* Add by Y.Kano 2005/01/11 */
/*************************************************************************
	module		:[２値ガンマ補正テーブルの車検証モードの有効、無効の獲得]
	function	:[

	]
	return		:[0	   	:無効
				  0以外 :有効
				]
	common		:[]
	condition	:[]
	comment		:[

	]
	machine		:[SH704x]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2004/10/26]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CHK_CarBinGammaValue(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_B9] & CAR_BIN_GAMMAVALUE));
}
#endif

