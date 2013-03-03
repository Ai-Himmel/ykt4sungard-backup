/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_i.h	*/
/****************************************************************
 * CMNUNI_I.C
 * 機種固有スイッチIの設定状態を得る関数たち
 * 1996/03/06 Eguchi
 ****************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_i.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\cmn_pro.h"		/* S.Fukui Jun.19,1998 */
#if (0)	/* cmn_pro.h定義に変更  */
void  CMN_EnableInterrupt(void);
void  CMN_DisableInterrupt(void);
#endif

UBYTE	CHK_UNI_Dummy_I(void)
{
	/* ｺﾝﾊﾟｲﾙを通すだけのダミー関数 */
	return (0);
}

/*　各自追加していってください */

/*************************************************************************
	module		:[通信が終了した回線をユニークＳＷにセットする]
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
	date		:[1996/12/02]
	author		:[村田]
*************************************************************************/
void CHK_SetT30Sign(UBYTE line_no)
{
	UBYTE	data;

	data = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
/* 回線番号値をそのままスカラー値でセットし、内蔵回線の標準／拡張を最上位ビットにセットします */
	CMN_DisableInterrupt();	/* DI */
	SYB_MachineUniqSwitch[UNIQ_SW_I0] = 0;
	SYB_MachineUniqSwitch[UNIQ_SW_I0] = line_no;
	if ((SYB_MachineUniqSwitch[UNIQ_SW_I0] == 0)
	&& (SYS_InternalLineNumber == SYS_EXT_LINE_COM)) {	/**	拡張ライン通信中	*/
		SYB_MachineUniqSwitch[UNIQ_SW_I0] |= 0x80;
	}
	CMN_EnableInterrupt();	/* EI */
#else
	data = (UBYTE)(0x01 << line_no);
	CMN_DisableInterrupt();	/* DI */
	SYB_MachineUniqSwitch[UNIQ_SW_I0] = 0;
	SYB_MachineUniqSwitch[UNIQ_SW_I0] = data;
	CMN_EnableInterrupt();	/* EI */
#endif
}

/*************************************************************************
	module		:[通信が終了した回線の獲得]
	function	:[
		1.
	]
	return		:[
			0: 回線０
			1: 回線１
			2: 回線２
			3: 回線３
			4: 回線４
			5: 回線５
			6: 回線６
			7: 回線７
		 0xFF: 該当なし
	]
	common		:[]
	condition	:[]
	comment		:[

	## 警告 ##
		この関数をコールする前に割り込みを禁止にしておく事

	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/02]
	author		:[村田]
*************************************************************************/
UBYTE CHK_GetT30Sign(void)
{
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
	return (SYB_MachineUniqSwitch[UNIQ_SW_I0]);
#else
	UBYTE	data;
	UBYTE	msk_bit;
	UBYTE	i;

	msk_bit = 0x01;
	data = SYB_MachineUniqSwitch[UNIQ_SW_I0];

	for (i = 0; i < 8; i++) {
		if (data & msk_bit) {
			return((UBYTE)i);
		}
		msk_bit = (UBYTE)(msk_bit << 1);
	}
	return(0xFF);
#endif
}



/*************************************************************************
	module		:[Ｒ２８８Ｆ内部ステータスモニタープリント有効／無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[unsigned char far CHK_PrintR288FMonitorEnable(void){}]
	date		:[1996/12/20]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_PrintR288FMonitorEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I2] & R288F_MONITOR_PRINT));
}


/*************************************************************************
	module		:[マルチ表示有効／無効（オペレーション）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1997/01/23]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_UNI_MultiDisplayEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & MULTI_DISPLAY_OPR));
}

/*************************************************************************
	module		:[マルチ表示有効／無効（待機中表示切り替え）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1997/02/06]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_UNI_MultiDisplayLineNumber(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & MULTI_DISPLAY_LINE_NUMBER));
}


/*************************************************************************
	module		:[マルチ表示有効／無効（タイマー）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1997/02/05]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_UNI_MultiDisplayTime(void)
{
	return(SYB_MachineUniqSwitch[UNIQ_SW_I4]);
}

#if (PRO_LINENUMBER == TWICE_LINE)
/*************************************************************************
	module		:[標準／拡張回線状態表示]
	function	:[
		1.ＰＯＰＬＡＲ＿Ｈ専用です。
	]
	return		:[
		0:分けて表示しない
		1:分けて表示する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/03/06]
	author		:[木元]
*************************************************************************/
UBYTE CHK_UNI_MultiDisplayTwiceLine(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & MULTI_DISPLAY_TWICE_LINE));
}
#endif


#if (PRO_KEYPANEL == PANEL_ANZU_L) || (PRO_KEYPANEL == PANEL_POPLAR_B)	/* アラムコ仕様、POPLAR_Bも追加 1998/06/30 Y.Matsukuma */
/*#if (PRO_KEYPANEL == PANEL_ANZU_L)		@ 1998/06/03 Y.Murata ｱﾗﾑｺ特殊対応 LT,LG,A4対応 ARM_A4*/
/*************************************************************************
	module		:[]
	function	:[
		1.ＡＮＺＵ＿Ｌ専用です。
		2.POPLAR_Bも追加 1998/06/30 Y.Matsukuma
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/06/03]
	author		:[村田]
*************************************************************************/
UBYTE CHK_UNI_AramcoSuportA4Paper(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & ARAMCO_SUPORT_A4_PAPER));
}
#endif

/*************************************************************************
	module		:[キャッチホン設定の有効／無効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/11/09]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_CatchPhoneON(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & MEMSW_CATCHPHONE_ON));
}


/* #if defined(POPLAR_F) */
#if (PRO_VOICE_ANSWER == ENABLE)
 #if (PRO_MODEM == R288F) || (PRO_MODEM == MN195006)	/* ORANGE以外のモデム Modified by J.Kishida 2002/09/09 */
/*************************************************************************
	module		:[TEL/FAX切り替えで音声応答するかどうかの獲得]
	function	:[
		1.
	]
	return		:[0    :音声応答しない（ムラタ仕様）
				  0以外:音声応答する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1999/10/21]
	author		:[村田]
*************************************************************************/
UBYTE CHK_UNI_VoiceAnswerEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & VOICE_ANSWER_ENABLE));
}
 #endif
#endif


#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)	/* 1998/06/15 Y.Murata */
/*************************************************************************
	module		:[ＣＩＬインサイド設定獲得]
	function	:[
		1.DATE_SET_RXDOC
		2.受信原稿に受信日時を付ける
	]
	return		:[
		０		:無効(アウトサイド)
		０以外	:有効(インサイド)
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/6/15]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_CIL_Inside(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I5] & CIL_INSIDE));
}

/*************************************************************************
	module		:[ＣＩＬ有効／無効設定獲得]
	function	:[
		1.DATE_SET_RXDOC
		2.受信原稿に受信日時を付ける
	]
	return		:[
		０		:無効
		０以外	:有効
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/15]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_CILPrintOn(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I5] & CIL_PRINT_ON));
}

/*************************************************************************
	module		:[ＣＩＬのＴＳＩ有効／無効設定獲得]
	function	:[
		1.DATE_SET_RXDOC
		2.受信原稿にＴＳＩを付ける
	]
	return		:[
		０		:無効
		０以外	:有効
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/15]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_CIL_TSIPrintOn(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I6] & CIL_TSI_PRINT_ON));
}
#endif	/* End of (PRO_DATE_SET_RXDOC_CHK == ENABLE) */




/*************************************************************************
	module		:[送信証ダイヤル番号印字範囲]
	function	:[
		1.送信証の電話番号が印字範囲を超えたら先頭に「・・」
		  を印字して下から２５桁分印字
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/10/26]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_UNI_DialWithin(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & TCR_WITHIN_PRINT));
}

/*************************************************************************
	module		:[通信管理記録・送信証に Year印字]
	function	:[
		1.
	]
	return		:[0		:Yearプリントしない
				  1		:Yearプリントする
	]			  
	common		:[]
	condition	:[]
	comment		:[ICHOUから移植]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1999/11/16]
	author		:[本多智幸]
*************************************************************************/
UBYTE CHK_JournalYearPrint(void)	/* 西暦４桁対応 addedbythonda1999/11/16	*/
									/* ICHOUから移植してきました			*/
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & JOURNAL_YEAR_PRINT));
}


#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[優先リストプリント記録紙サイズのの獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1999/10/06]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_PrimaryListSize(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I8] & PRIMARY_LIST_SIZE));
}
/*************************************************************************
	module		:[優先リストプリント記録紙サイズのの獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1999/10/06]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_PrimaryTestSize(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_I8] & PRIMARY_TEST_SIZE)>>4));
}
#endif


#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/23 Eguchi*/

/*************************************************************************
	module		:[InternetFAX TTLのボーレートの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INF]
	date		:[1998/05/23]
	author		:[M.Eguchi]
*************************************************************************/
UBYTE	CHK_UNI_INF_Baudrate(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I9] & 0x03));
}



/*************************************************************************
	module		:[InternetFAX TIFFのminimumSet有効/無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INF]
	date		:[1998/05/23]
	author		:[M.Eguchi]
*************************************************************************/
UBYTE	CHK_UNI_INF_MinimumSetAvail(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I9] & INF_MINIMUM_SET_ENABLE));
}

#endif /* End of (PRO_DIALUP_INTERNET_FAX == ENABLE) */


#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/07 */
/*************************************************************************
	module		:[マルチＴ３０モニタ（０：無効／１：有効）の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[INF]
	date		:[1999/04/07]
	author		:[H.Fujimura]
*************************************************************************/
UBYTE	CHK_UNI_MultiT30Monitor(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I5] & MULTI_T30_MONITOR));
}
#endif

/*************************************************************************
	module		:[ジャーナルの相手先欄に載せる内容の優先順位を変更するスイッチ]
	function	:[
		1.
	]
	return		:[０：（従来）オートダイアル：自機内情報(Name, No)、手動：相手情報
				  １：オートダイアル、手動：相手情報（カナＩＤ→ＣＳＩ／ＴＳＩ→自機内情報（Name, No））]
	common		:[ＣＨＮ，ＤＥＵ，ＥＵＲ以外のパスに入っています]
	condition	:[]
	comment		:[ (RDC200000497 郵政向け特ＲＯＭ作成依頼)]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2000/12/05]
	author		:[H.Hirao]
*************************************************************************/
UBYTE	CHK_UNI_JournalPriority(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & JOURNAL_PRIORITY));
}

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/07 By M.Maeda */
/*************************************************************************
	module		:[通信結果表示]
	function	:[
		1.
	]
	return		:[0:無効 1:有効]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/08/07]
	author		:[前田雅也]
*************************************************************************/
UBYTE	CHK_UNI_CommandResult(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & COMM_RESULT_VIEW));
}

#endif

#if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り */
/*************************************************************************
	module		:[あるキーを朱色原稿読取のON/OFFキーとして流用するかしないか]
	function	:[
		1.
	]
	return		:[
		０    ：しない（本来のオペレーション起動のこと）
		その他：する
	]
	common		:[]
	condition	:[]
	comment		:[
			I:3-7	#define  RED_SCAN					0x80
	]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	ProtoType	:[]
	date		:[2002/03/04]
	author		:[T.Takagi]
*************************************************************************/
UBYTE	CHK_UNI_RedScanModeEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I3] & RED_SCAN));
}
#endif

#if defined(JPN) /* 2002/08/29 By M.Maeda */
/*************************************************************************
	module		:[ワーディング切り替えを有効／無効にするSW]
	function	:[
		1.メニュー、＃で簡単にワーディングが切り替わってしまう
		ため、フィールドにて無意識にワーディングが切り替わることがある
		メニュー、＃の切り替えを有効／無効のSWを追加
	]
	return		:[0(FALSE)	:無効
				  1(TRUE)	:有効
	]
	common		:[]
	condition	:[]
	comment		:[2000/08/18 白樺から移植 M.IIDA]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2000/06/14]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_WordingChangeEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & WORDING_CHANGE_ENABLE));
}
#endif

#if (PRO_ENERGY_SAVE == ENABLE)
/**********************************************************************************************************************
 * Module: PC_24Vのリレー寿命テストモード切換スイッチ
 * Author: 高木 智史
 * Create: 2002/12/03
 * Function: 
 * Argument: 
 * Return: 0:無効（通常）1:有効（テストモード）
 * Global: 
 * Condition: 
 * Note: 
 *********************************************************************************************************************/
UBYTE CHK_UNI_PC24V_RelayTestEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I5] & PC_24V_TEST));
}
#endif

#if defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)
/**********************************************************************************************************************
 * Module: 一定時間待ってもMODEMのNEWCビットが落ちなかった場合、リセットするかしないかのSW
 * Author: 高木 智史
 * Create: 2002/12/11
 * Function: 
 * Argument: 
 * Return: 0:リセットする（通常） 1:リセットしない
 * Global: 
 * Condition: 
 * Note: 
 *********************************************************************************************************************/
UBYTE CHK_UNI_IgnoreNEWC_Reset(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I5] & MDM_NEWC_RESET_DISABLE));
}
#endif

#if defined(SATSUKI2) || defined(STOCKHM2)	/* Y.Kano 2003/10/01 */
/*************************************************************************
	module		:[CI割込み救済措置2の有功/無効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				　0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[2003/11/26]
	author		:[大島]
*************************************************************************/
UBYTE CHK_UNI_CiRescueEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I5] & CI_RESCUE_ENABLE));
}


/*************************************************************************
	module		:[壁掛設定の無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				　0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1994/6/20]
	author		:[大西]
*************************************************************************/
UBYTE CHK_WallHangSetting(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & WALL_HANG_SETTING));
}

/*************************************************************************
	module		:[読み取り中の点滅機能の無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				　0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2003/10/23]
	author		:[SMuratec H.C.H]
*************************************************************************/
UBYTE CHK_StoringFlashEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & STORING_FLASH_ENABLE));
}
/*************************************************************************
	module		:[経年変化対応の無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				　0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2003/10/23]
	author		:[SMuratec H.C.H]
*************************************************************************/
UBYTE CHK_YearChangeEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I7] & YEAR_CHANGE_ENABLE));
}
#endif

#if defined(STOCKHM2)	/* Add by Y.Kano 2004/07/09 */
/*************************************************************************
	module		:[ＳＴＯＣＫＨＭ２用ヒートパルステーブルの無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  1    :有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/07/09]
	author		:[加納]
*************************************************************************/
UBYTE CHK_HeatTableEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I6] & HEAT_PULSE_TABLE_ENABLE));
}

/*************************************************************************
	module		:[ＳＴＯＣＫＨＭ２用ヒートパルステーブルの無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  1    :有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/07/09]
	author		:[加納]
*************************************************************************/
UBYTE CHK_PreHeatTableEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I6] & PRE_HEAT_PULSE_TABLE_ENABLE));
}

/*************************************************************************
	module		:[ＳＴＯＣＫＨＭ２用会話予約の無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  1    :有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/11/03]
	author		:[SMuratec 夏]
*************************************************************************/
UBYTE CHK_VoiceCallEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I6] & VOICE_CALL_ENABLE));
}

/*************************************************************************
	module		:[ＳＴＯＣＫＨＭ２用防災ＦＡＸの無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  1    :有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/08/19]
	author		:[加納]
*************************************************************************/
UBYTE CHK_DisasterPreventionFaxEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I9] & DISASTER_PREVENTION_FAX_ENABLE));
}
#endif	/* End of defined(STOCKHM2) */
/*************************************************************************
	module		:[松下モデムＶ２３送受信時のBellcore設定]
	function	:[
		1.
	]
	return		:[0    :無効
				  1    :有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/10/19]
	author		:[田中]
*************************************************************************/
UBYTE CHK_V23_BellcoreEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_I9] & V23_BELLCORE_ENABLE));
}
/*************************************************************************
	module		:[松下モデムＶ２３送信時のパリティ設定]
	function	:[
		1.
	]
	return		:[		bit9-7 bit9-6 bit9-5
							0      0      0			８ビットパリティ無し 
						    1      0      0			７ビットパリティ無し 
						    1      1      0			７ビット偶数パリティ 
						    1      1      1			７ビット奇数パリティ 
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[2004/10/19]
	author		:[加納]
*************************************************************************/
UBYTE CHK_V23_TxParitySetting(void)
{
	return((UBYTE)((SYB_MachineUniqSwitch[UNIQ_SW_I9] & V23_TX_PARITY_METHOD) >> 5));
}

