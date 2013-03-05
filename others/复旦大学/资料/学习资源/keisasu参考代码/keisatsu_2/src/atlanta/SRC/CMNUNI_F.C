/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\unisw_f.h	*/
/************************************************
 * CMNUNI_F.C
 * 機種固有スイッチFの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_f.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"


/*************************************************************************
	module		:[２値コピー時のスムージング有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_SmoothingCopy2(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_COPY_2));
}



/*************************************************************************
	module		:[２値受信時のスムージング有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_SmoothingRx2(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_RX_2));
}



/*************************************************************************
	module		:[ノーマルモード時のスムージング有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_SmoothingNormal(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_NORMAL));
}




/*************************************************************************
	module		:[ファインモードコピー時のスムージング有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_SmoothingCopyFine(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_COPY_FINE));
}




/*************************************************************************
	module		:[ファイン受信時のスムージング有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_SmoothingRxFine(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_RX_FINE));
}



/*************************************************************************
	module		:[スーパーファイン時のスムージングの有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_SmoothingS_Fine(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_SFINE));
}


/*************************************************************************
	module		:[ハイパーファイン（３００ｘ４００）（２値）時のスムージングの有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/06/28]
	author		:[川崎]
*************************************************************************/
UBYTE CHK_UNI_SmoothingH_Fine(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F0] & SMOOTHING_HFINE));
}

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)
/*************************************************************************
	module		:[電源ON時にイニシャルカットするしないの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/08/19]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_PowerON_InitialCut(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F0] & POWER_ON_INITIAL_CUT));
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
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/10/2]
	author		:[K.Kawata]
*************************************************************************/
UBYTE CHK_UNI_THERMAL_HEAD_RANK(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F3]));
}
#endif

/*************************************************************************
	module		:[記録紙A4,B5Rで､B4原稿受信した場合のカセット選択の獲得]
	function	:[
		1.
	]
	return		:[0    :B5R
				　0以外:A4
	]
	common		:[]
	condition	:[]
	comment		:[
		1.戻り値が０の時　　：100%で1ﾍﾟｰｼﾞ>100%で複数ﾍﾟｰｼﾞ>幅による縮小で1ﾍﾟｰｼﾞ>幅による縮小で複数ﾍﾟｰｼﾞ
		2.戻り値が０以外の時：100%で1ﾍﾟｰｼﾞ>幅による縮小で1ﾍﾟｰｼﾞ>100%で複数ﾍﾟｰｼﾞ>幅による縮小で複数ﾍﾟｰｼﾞ
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/04/07]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_Reduced1PagePrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] & REDUCED_1PAGE_PRINT));
}

/*************************************************************************
	module		:[受信プリント枚数設定実施／未実施の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				　0以外:有効（オペレーションで設定できる）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/06/26]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_MultiRxDocumentPrint(void)
{
	return((UBYTE)SYB_MachineUniqSwitch[UNIQ_SW_F1] & MULTI_RX_DOCUMENT_PRINT);
}


/*************************************************************************
	module		:[プリンタオートシャットオフ時間]
	function	:[
		1.
	]
	return		:[1～255:1～255分]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_PrinterAutoShutTime(void)
{
	return(SYB_MachineUniqSwitch[UNIQ_SW_F2]);
}

/*************************************************************************
	module		:[記録紙でＡ４／Ｆ４かレター／リーガルのどちらを使用するか]
	function	:[
		1.
	]
	return		:[
		0:Ａ４／Ｆ４
		1:レター／リーガル
	]
	common		:[]
	condition	:[東南アジア使用のみ有効]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1995/03/08]
	author		:[宮崎]
*************************************************************************/
UBYTE CHK_UNI_LeterLegal(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] & PAPER_LETER_LEGAL));
}




/*************************************************************************
	module		:[印字濃度]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_LaserDensity(void)
{
	return ((UBYTE)SYB_MachineUniqSwitch[UNIQ_SW_F3]);
}



/*************************************************************************
	module		:[転写電流設定値の獲得　]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/12]
	author		:[江口]
*************************************************************************/
UBYTE CHK_UNI_TransCurrency(void)
{
	return ((UBYTE)SYB_MachineUniqSwitch[UNIQ_SW_F4]);
}

/*************************************************************************
	module		:[プリンタ起動前のクリーニング指示をする しないの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/05/17]
	author		:[平尾 英典]
*************************************************************************/
UBYTE CHK_UNI_PrinterCleaning(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] & PRINTER_CLEANING_PREPRINT));
}
/*************************************************************************
	module		:[トナー無し状況での印字を継続するかを判断する]
	function	:[
		1.
	]
	return		:[  ０：印字中止
					１：継続印字
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/06/20]
	author		:[川崎真史]
*************************************************************************/
UBYTE CHK_UNI_ContinueToPrintForTonar(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] & CONTINUE_TO_PRINT_FOR_TONAR));
}
/*************************************************************************
	module		:[Ｅファイン（３００ｘ３００）（２値）時のスムージングの有効／無効の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/09/18]
	author		:[川崎]
*************************************************************************/
UBYTE CHK_UNI_SmoothingE_Fine(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_F1] & SMOOTHING_EFINE));
}

/*************************************************************************
	module		:[Normal/SuperFine/HyperFineプリンタ縮小率]
	function	:[
		1.
	]
	return		:[  ０：設定率通り
					１：設定率に１を加える
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/08/27]
	author		:[坂本直史]
*************************************************************************/
UBYTE CHK_UNI_PrintReductionAjust(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] & PRINTER_REDUCTION_ADJUST));
}

/*************************************************************************
	module		:[コピー原稿を優先的にプリントするか否かを獲得]
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
	date		:[1996/10/23]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_CopyPrimaryPrint(void)
{
#if (PRO_PRINT_TYPE == LED)
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F5] & COPY_PRIMARY_PRINT));
#else
	return(0);
#endif

}

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[トナーセーブモード状態を獲得]
	function	:[
		1.
	]
	return		:[
		TONER_SAVE_NONE(0x00)                   ：なし
		TONER_SAVE_QUARTER(0x02)                ：２５％間引き
		TONER_SAVE_HALF(0x04)                   ：５０％間引き
		TONER_SAVE_QUARTER+TONER_SAVE_HALF(0x06)：７５％間引き
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[PRN]
	date		:[1996/07/17]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_TonerSaveMode(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F5] & (TONER_SAVE_QUARTER |
														 TONER_SAVE_HALF)));
}

/*************************************************************************
	module		:[サイズエラーを無視するか否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1.ＦＡＬＳＥ：サイズエラーを無視しない。ＪＡＭとして扱う。
		2.ＴＲＵＥ	：サイズエラーを無視する。正常プリントしたとして扱う。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/08/19]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_SizeErrorIgnore(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F5] & SIZE_ERROR_IGNORE));

}

/*************************************************************************
	module		:[ＬＥＤヘッド露光時間の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ポプラのみ使用]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/05/12]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_LED_StrobeTime(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F6] & LED_STROBE_TIME));
}

/*************************************************************************
	module		:[ページ分割の画像欠落を修正するか否かの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ポプラのみ使用]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/17]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_CorrectPartitionPrint(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F6] & CORRECT_PARTITION_PRINT));
}

/*************************************************************************
	module		:[ページ分割の画像欠落を修正するか否かの獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ポプラのみ使用]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/06/18]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_AdjustPrintReduction(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F6] & ADJUST_PRINT_REDUCTION));
}

/*************************************************************************
	module		:[ドラムメーカーの獲得]
	function	:[
		1.
	]
	return		:[
		0:キャノン製ドラム
		1:富士電機製ドラム
	]
	common		:[]
	condition	:[]
	comment		:[ポプラのみ使用]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/07/02]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_NewDrumControl(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F6] & NEW_DRUM_CONTROL));
}


/*************************************************************************
	module		:[転写電圧調整値の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/03]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_TransferVoltage(void)
{
	return ((UBYTE)SYB_MachineUniqSwitch[UNIQ_SW_F7]);
}

/*************************************************************************
	module		:[手差し給紙タイムアウト時間の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ポプラのみ使用]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/01/22]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_ManualDocWaitTime(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F4] & MANUAL_DOC_WAIT_TIME));
}

/*************************************************************************
	module		:[ＰＣ手差し給紙タイムアウト時間の獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ポプラのみ使用]
	machine		:[SH]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/01/22]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_PcManualDocWaitTime(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F4] & PC_MANUAL_DOC_WAIT_TIME));
}

#endif	/* #if (PRO_PRINT_TYPE == LED) */

#if (PRO_PRINT_TYPE == LASER)
/*************************************************************************
	module		:[プリンタデューティを５０％にするか否かを獲得する]
	function	:[
		1.
	]
	return		:[
		1.ＦＡＬＳＥ：１００％
		2.ＴＲＵＥ	：５０％
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/08/13 -> 1997/11/14]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_PrinterDuty50(void)
{
	return ((unsigned char)(SYB_MachineUniqSwitch[UNIQ_SW_F7] & PRINTER_DUTY_50));

}
#endif

/*#if (PRO_PRINT_TYPE == LASER) LEDでも使用 By M.Tachibana 1997/11/03 */
/*************************************************************************
	module		:[トナー無し後にプリントする枚数]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[PRN]
	ProtoType	:[unsigned char far CHK_UNI_RestPrintPage(void){}]
	date		:[1997/02/13]
	author		:[木元修]
*************************************************************************/
UBYTE CHK_UNI_RestPrintPage(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F8]));
}
/*#endif	@* #if (PRO_PRINT_TYPE == LASER) */

/*************************************************************************
	module		:[ＰＣプリントケーブル抜け判断時間]
	function	:[
		1.
	]
	return		:[
					0 ～ 255 (x10)秒
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/02/03]
	author		:[宮崎仁一]
*************************************************************************/
UBYTE CHK_UNI_PCNonCommunicationTime(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F9]));
}



/*************************************************************************
	module		:[ドラム寿命カウンタークリア判断]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[H8/300]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1997/12/02]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_UNI_ResetDrumLife(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F1] & RESET_DRUM_LIFE));

}

#if (PRO_PC_PRINT == ENABLE)
/*************************************************************************
	module      :[ＰＣプリントで、サイズの異なったデータでも受信するか否かを獲得する]
	function    :[
		1.
	]
	return      :[]
	common      :[]
	condition   :[]
	comment     :[]
	machine     :[V53]
	language    :[MS-C(Ver.6.0)]
	keyword     :[CMN]
	date        :[1998/02/24]
	author      :[橘正樹]
*************************************************************************/
UBYTE	CHK_UNI_PC_PrintForceReceive(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F5] & PC_PRINT_FORCE_RECEIVE));

}
#endif

#if (PRO_REVERSE_PRINT == ENABLE)
/*************************************************************************
	module		:[受信原稿の逆順プリント設定時に、メモリ容量の規定値を獲得する]
	function	:[
		1.受信原稿の逆順プリント設定時に、受信中にメモリ容量が規定値以下となった場合には、
		  正順プリントを開始する。その時の規定値を定義する
	]
	return		:[
		1.ブロック数＝メモリ容量／４（ＫＢ）
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1999/05/19]
	author		:[橘正樹]
*************************************************************************/
UWORD	CHK_UNI_ReversePrintMemorySize(void)
{
	switch (SYB_MachineUniqSwitch[UNIQ_SW_F5] & REVERSE_PRINT_MEMORY_SIZE) {
	case REVERSE_PRINT_MEMORY_SIZE0:
		return(128/4);
	case REVERSE_PRINT_MEMORY_SIZE1:
		return(512/4);
	case REVERSE_PRINT_MEMORY_SIZE2:
		return(1024/4);
	case REVERSE_PRINT_MEMORY_SIZE3:
		return(2048/4);
	default:
		return(1024/4);
	}
}
#endif

#if (PRO_REVERSE_PRINT == ENABLE)
/*************************************************************************
	module		:[受信原稿を逆順プリントする機能を有効にするか否かを獲得する]
	function	:[
		1.ＦＡＬＳＥ：受信原稿を逆順プリントする機能を無効にする
		2.ＴＲＵＥ	：受信原稿を逆順プリントする機能を有効にする
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/05/19]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CHK_UNI_RxDocReversePrint(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_F5] & RX_DOC_REVERSE_PRINT));

}
#endif

