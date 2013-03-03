/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_f.h	*/
/************************************************
 * CMNUNI_F.C
 * 機種固有スイッチFの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_h.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\std.h"
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103) /* 1999/02/24 by T.Soneoka */
#include "\src\atlanta\ext_v\sys_data.h"
#endif
#if defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/* 2003/01/06 T.Takagi  */
#include "\src\atlanta\ext_v\ini_tbl.h"
#endif
CONST UBYTE IsOptionalSpdDialInvalid = TRUE;	/* 任意短縮機能を無効とする。 By S.Fukui Oct.5,1998 */


/*************************************************************************
	module		:[サンフラワサークル用ポーリングパスコード無効/有効の獲得]
	function	:[
		1.
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
	date		:[1994/01/11]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_SpecialPollingPasscode(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & SPECIAL_POLLING_PASSCODE));
}


/*************************************************************************
	module		:[メモリオーパー時のメッセージプリント無効/有効の獲得]
	function	:[
		1.
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
	date		:[1994/01/11]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_MemoryOverMessagePrint(void)
{
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	/*
	** 原稿蓄積にて、１ページ読み取り完了する前に、原稿排出完了する仕様変更
	**  1999/02/24 by T.Soneoka
	*/
	if (SYB_MachineUniqSwitch[UNIQ_SW_H0] & MEMORY_OVER_MESSAGE_PRINT) {
		if (SYS_ForcedMemoryOverMsg) {
			return (TRUE);
		} else {
			return (FALSE);
		}
	} else {
		return (FALSE);
	}
#else
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & MEMORY_OVER_MESSAGE_PRINT));
#endif
}

#if defined(HINOKI3)	/* 他に空きが無く未使用なのでここを使用します（もし他機種でも使用する時は条件をはずして下さい）by K.Watanabe 2004/12/09 */
/**********************************************************************************************************************/
/**
	@brief		通信管理レポート降順／昇順プリントの獲得
	
	@li			
	@param		なし
	@return		
	@note		なし
	@date		2004/12/09 作成
	@author		渡辺一章
*/
/**********************************************************************************************************************/
UBYTE CHK_UNI_JournalDescendingPrint(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & JOURNAL_DESCENDING_PRINT));
}
#else
/*************************************************************************
	module		:[通信管理記録にライフモニター印字有効／無効に獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ＣＨＮのみ有効なスイッチ？]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_UNI_JournalLifeMonitorPrint(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & LIFE_MONITOR_PRINT));
}
#endif

/*************************************************************************
	module		:[オートダイアル時相手が人間だった時に使用されたワンタッチ／短縮を消去する設定に獲得]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ＦＲＡのみ有効なスイッチ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/11]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_UNI_HumanAnswerClear(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & HUMAN_ANSWER_CLEAR));
}


/*************************************************************************
	module		:[ブザーボリューム値の獲得]
	function	:[
		1.
	]
	return		:[
				BUZZER_VOLUME_OFF
				BUZZER_VOLUME_MIN
				BUZZER_VOLUME_MID
				BUZZER_VOLUME_MAX
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/03/07]
	author		:[江口]
*************************************************************************/
UBYTE	CHK_UNI_BuzzerVolume(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & BUZZER_VOLUME_MAX));
}

/*************************************************************************
	module		:[通信エラー発生時、チェックメッセージ印字後にエラー表示
				を消去するか？]
	function	:[]
	return		:[
					０：消去しない
					１：消去する
				]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1996/04/27]
	author		:[川崎]
*************************************************************************/
UBYTE CHK_UNI_ClearCommunicationError(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & CLEAR_COMMUNICATION_ERROR));
}

/*************************************************************************
	module		:[リストのフォーマットを３×３にする]
	function	:[]
	return		:[
				0    ：しない
				0以外：する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/03/29]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_ListFormat3x3(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H0] & LIST_3X3_FORMAT));
}


/*************************************************************************
	module		:[送信時ＤＩＳ受信まで回線モニタをＯＮする]
	function	:[
		1.
	]
	return		:[
					0以外:有効
					0    :無効
	]
	common		:[]
	condition	:[]
	comment		:[ＳＥＡのみ有効になる]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/06/13]
	author		:[村田]
*************************************************************************/
UBYTE 	CHK_UNI_UntilReceiveDISLineON(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & TRAN_DIS_LINE_ON));
}

/*************************************************************************
	module		:[代行受信原稿をポーリング原稿としない/するの獲得]
	function	:[
		1.
	]
	return		:[0    :ポーリング原稿としない
				  0以外:ポーリング原稿する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_RxDocToPollingDoc(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & RX_DOC_TO_POLLING_DOC));
}

/*************************************************************************
	module		:[親展受信原稿をポーリング原稿としない/するの獲得]
	function	:[
		1.
	]
	return		:[0    :ポーリング原稿としない
				  0以外:ポーリング原稿する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_SecureDocToPollingDoc(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & SECURE_RX_DOC_TO_POLLING_DOC));
}

#if defined(HINOKI3)	/* 他に空きが無く、条件コンパイル的に未使用なので、ここを使用します by K.Watanabe 2005/01/05 */
/**********************************************************************************************************************/
/**
	@brief		ジャーナル定形サイズカットする／しないの獲得
	
	@li			
	@param		なし
	@return		
	@note		メンテナンスSWにも同じ内容のLIST_PRINT_NO_CUTがありますが、サービスからの要望で自由に変更出来るように
				して欲しいとの事から、HINOKI3では新たにユニークSWに設けました
	@date		2005/01/05 作成
	@author		渡辺一章
*/
/**********************************************************************************************************************/
UBYTE CHK_UNI_JournalFixedFormSizeCut(void)
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & JOURNAL_FIXED_FORM_SIZE_CUT));
}
#else	/* (PRO_FIP == ENABLE) */
/*************************************************************************
	module		:[FIP受信原稿をポーリング原稿としない/するの獲得]
	function	:[
		1.
	]
	return		:[0    :ポーリング原稿としない
				  0以外:ポーリング原稿する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/03]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_FIP_DocToPollingDoc(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & FIP_DOC_TO_POLLING_DOC));
}
#endif

/*************************************************************************
	module		:[送信予約原稿をポーリング原稿としない/するの獲得]
	function	:[
		1.
	]
	return		:[0    :ポーリング原稿としない
				  0以外:ポーリング原稿する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/03/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_TxDocToPollingDoc(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & TX_DOC_TO_POLLING_DOC));
}


/*************************************************************************
	module		:[スクランブル原稿をポーリング原稿としない/するの獲得]
	function	:[
		1.
	]
	return		:[0    :ポーリング原稿としない
				  0以外:ポーリング原稿する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/07/01]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CHK_UNI_ScrambleDocToPollingDoc(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & SCRAMBLE_DOC_TO_POLLING_DOC));
}

/*************************************************************************
	module		:[DRAMﾊﾞｯｸｱｯﾌﾟ時間の獲得]
	function	:[
		1.
	]
	return		:[
		0の場合はバックアップしない
		1～127:1～127時間
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/05/20]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_DRAM_BackupTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H2] & DRAM_BACKUP_TIME));

}

/*************************************************************************
	module		:[強制DRAMﾊﾞｯｸｱｯﾌﾟ処理実施／未実施の獲得]
	function	:[
		1.
	]
	return		:[0    :未実施
				  0以外:実施
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/12/20]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_DRAM_BackupTest(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H2] & DRAM_BACKUP_TEST));
}


/*************************************************************************
	module		:[Ｔ３０モニタのフレーム間隔時間のプリントの有効／無効の獲得]
	function	:[
		1.
	]
	return		:[0		:有効
				  0以外	:無効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/05/23]
	author		:[平尾 英典]
*************************************************************************/
UBYTE CHK_UNI_T30_IntervalPrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & T30FRAME_PRINT_INTERVALTIME));
}

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/2/4 */
/*************************************************************************
	module		:[ジャーナル印字時に標準ライン／拡張ラインを分けてプリントする／しないの獲得]
	function	:[
		1.
	]
	return		:[0		:プリントしない
				  0以外	:プリントする
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1998/02/04]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CHK_UNI_JrnlInternalSeprate(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H1] & JOURNAL_INTNL_LINE_SEPARATE));
}
#endif

/*************************************************************************
	module		:[任意短縮]
	function	:[]
	return		:[
				0    ：無効
				0以外：有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/04/18]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_OptionalSpeedDial(void)
{
#if ((defined(HINOKI2) || defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3)) && defined(JPN))	/* 2003/12/02 Y.Kano */
	if (ROM_SW_OptionalSpeedDial) {	/* スギ薬局特ROM（任意短縮）*/
		return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & OPTIONAL_SPEED_DIAL));
	}
	else {
		/* 沖電気の特許公報(第2612376号)回避の為、追加。有効期間 2010年 迄。 By S.Fukui Oct.5,1998 */
		if (IsOptionalSpdDialInvalid == TRUE) {
			return(0);
		}
		return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & OPTIONAL_SPEED_DIAL));
	}
#else
	/* 沖電気の特許公報(第2612376号)回避の為、追加。有効期間 2010年 迄。 By S.Fukui Oct.5,1998 */
	if (IsOptionalSpdDialInvalid == TRUE) {
		return(0);
	}
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & OPTIONAL_SPEED_DIAL));
#endif
}

/*************************************************************************
	module		:[ジャンクメール専用ダイヤル登録]
	function	:[]
	return		:[
				0    ：無効
				0以外：有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/05/17]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_JunkMailProtectDial(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & JUNK_MAIL_PROTECT_DIAL));
}

/*************************************************************************
	module		:[Ｆコード受信通知メッセージプリント]
	function	:[]
	return		:[
				0    ：プリントする
				0以外：プリントしない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/05/17]
	author		:[山口]
*************************************************************************/
UBYTE CHK_UNI_Fcode_RxMessageOff(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & FCODE_RX_MSG_OFF));
}

/*************************************************************************
	module		:[連続ポーリングを毎日実行する]
	function	:[]
	return		:[
				0    ：無効
				0以外：有効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/09/03]
	author		:[橘正樹]
*************************************************************************/
UBYTE CHK_UNI_ContPollingDaily(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & CONTINUOUS_POLLING_DAILY));
}

#if (PRO_PC_PRINT == ENABLE)
/*************************************************************************
	module		:[ＰＣメモリオーパー時のメッセージプリント無効/有効の獲得]
	function	:[
		1.
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
	date		:[1997/10/02]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CHK_UNI_PcMemoryOverMsgPrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & PC_MEMORY_OVER_MESSAGE_PRINT));
}
#endif

/*************************************************************************
	module		:[消耗品発注用紙プリント無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0x20 :トナー発注
				  0x40 :ドラム発注
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/10/02]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CHK_UNI_OrderListPrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & (TONER_ORDER_LIST_PRINT|DRUM_ORDER_LIST_PRINT)));
}

/*************************************************************************
	module		:[済みスタンプキー有効にする（他のキーと兼用割付）無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[ポプラＢのみ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/12]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CHK_UNI_StampKeyEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H3] & STAMP_KEY_ENABLE));
}

/*************************************************************************
	module		:[サイレントオペレーションの無効/有効の獲得]
	function	:[
		1.
	]
	return		:[0    :無効
				  0以外:有効
	]
	common		:[]
	condition	:[]
	comment		:[機器設定とＯＲでみる
				  機器設定にサイレントオペレーションがない場合でも
				  このビットを立てると動作する
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/03]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CHK_UNI_SilentOperation(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & SILENT_OPERATION_MODE));
}

/*************************************************************************
	module		:[疑似２回線仕様におけるF網着信回線設定]
	function	:[
		1.F網着信は標準ライン、拡張ラインどちらか一方しかできないので、
		  このスイッチによってMODEMリレーを制御して、どちらに着信させるかを設定します
	]
	return		:[0    :標準ライン側有効
				  0以外:拡張ライン側有効
	]
	common		:[]
	condition	:[ポプラHのみ]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/21]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE	CHK_UNI_F_NET_ExtLineEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & F_NET_EXT_LINE));
}

/*************************************************************************
	module		:[送信証に印字されている送信時間を空欄にするかどうかの獲得]
	function	:[
		1.
	]
	return		:[0    :送信時間を印字する
				  0以外:送信時間を印字せずに、空欄とする
	]
	common		:[]
	condition	:[]
	comment		:[
			【CSDR-No.70】モニターレポート上の送信時間印字する／しないの切り替え
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	date		:[1998/10/05]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_TCR_NoneTxTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & TCR_NONE_TX_TIME));
}

/*************************************************************************
	module		:[消耗品発注用紙プリント起動の優先度の獲得]
	function	:[
		1.消耗品発注用紙要求 から プリント動作停止(トナー欠等）までの間に
          発注用紙プリントが実施されないケースを回避するため、現プリント
          ジョブに割込んで印字させる。
	]
	return		:[0    :現プリントジョブ終了後印刷
				  0以外:プリント処理最優先
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/11/27]
	author		:[福井知史]
*************************************************************************/
UBYTE  CHK_UNI_PriorOrderListPrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & PRIOR_ORDER_LIST));
}

/*************************************************************************
	module		:[標準ＤＲＡＭ２Ｍをマスクするかの設定]
	function	:[
		1.標準DRAM 2MB：蓄積枚数MAX or 78枚制限の設定
	]
	return		:[]
	common		:[]
	condition	:[ANZU_Lのみ]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/04]
	author		:[松隈]
*************************************************************************/
UBYTE CHK_UNI_MaskingDram(void)
{
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)
	return((UBYTE)1);	/* 必ずマスクさせるようにリターンを返す　*/
 #endif
 #if (PRO_DIALUP_INTERNET_FAX == DISABLE)
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & MAX_STORE_78));
 #endif
}
/*************************************************************************
	module		:[簡易時間管理 手動送信積算設定]
	function	:[]
	return		:[
		０		：手動送信時、時間／ページ数の積算しない
		０以外  ：手動送信時、時間／ページ数の積算する
 	]
	common		:[]
	condition	:[
		PRO_DEPART_NEW_LIST	== ENABLE の時のみ有効（海外仕様)
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/04]
	author		:[福井知史]
*************************************************************************/
UBYTE CHK_UNI_ManualTxTimeManage(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & MANUAL_TX_TIME_MANAGE));
}
/*************************************************************************
	module		:[簡易時間管理 手動受信積算設定]
	function	:[]
	return		:[
		０		：手動受信時、時間／ページ数の積算しない
		０以外  ：手動受信時、時間／ページ数の積算する
 	]
	common		:[]
	condition	:[
		PRO_DEPART_NEW_LIST	== ENABLE の時のみ有効（海外仕様)
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/04]
	author		:[福井知史]
*************************************************************************/
UBYTE CHK_UNI_ManualRxTimeManage(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & MANUAL_RX_TIME_MANAGE));
}

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/23 */
/*************************************************************************
	module		:[ナンバーディスプレイ着信履歴のエラー表示]
	function	:[]
	return		:[
		０		：ナンバーディスプレイ着信履歴のエラー表示しない
		０以外  ：ナンバーディスプレイ着信履歴のエラー表示する
 	]
	common		:[]
	condition	:[
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/04]
	author		:[福井知史]
*************************************************************************/
UBYTE CHK_UNI_ND_JournalErrorReport(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H4] & NUMBER_DISPLAY_ERROR_REPORT));
}
#endif

#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/19 By M.Kuwahara */
/*************************************************************************
	module		:[キーマクロ実行時間の獲得]
	function	:[
		1.
	]
	return		:[実行時間]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1998/06/19]
	author		:[桑原美紀]
*************************************************************************/
UBYTE CHK_UNI_KeyMacroActionTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H5] & (KEYMACRO_PREVIEW_TIME_1 |
														KEYMACRO_PREVIEW_TIME_2 |
														KEYMACRO_PREVIEW_TIME_3 |
														KEYMACRO_PREVIEW_TIME_4 |
														KEYMACRO_ACTION_TIME_1  |
														KEYMACRO_ACTION_TIME_2  |
														KEYMACRO_ACTION_TIME_3  |
														KEYMACRO_ACTION_TIME_4)));
}
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネ By Y.Suzuki 2002/06/15*/ /* || (PRO_ENERGY_SAVE == ENABLE) 見送る */ /* 2002/11/29 T.Takagi */
/*************************************************************************
	module		:[省エネ開始時間の獲得]
	function	:[
		1.
	]
	return		:[分]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[2002/06/15]
	author		:[Y.Suzuki]
*************************************************************************/
UBYTE CHK_UNI_EcoModeStartTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H5]));
}
#endif


/*************************************************************************
	module		:[料金管理時の昼間開始時間の獲得]
	function	:[
		1.
	]
	return		:[0～23:0～23時]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_DaytimeStartTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H6] & (DAYTIME_START_TIME_1 |
														DAYTIME_START_TIME_2 |
														DAYTIME_START_TIME_3 |
														DAYTIME_START_TIME_4 |
														DAYTIME_START_TIME_5)));
}


/*************************************************************************
	module		:[料金管理時の夜間開始時間の獲得]
	function	:[
		1.
	]
	return		:[0～23:0～23時]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_NightStartTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H7] & (NIGHT_START_TIME_1 |
														NIGHT_START_TIME_2 |
														NIGHT_START_TIME_3 |
														NIGHT_START_TIME_4 |
														NIGHT_START_TIME_5)));
}

/*************************************************************************
	module		:[料金管理時の深夜開始時間の獲得]
	function	:[
		1.
	]
	return		:[0～23:0～23時]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_MidnightStartTime(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H8] & (MIDNIGHT_START_TIME_1 |
														MIDNIGHT_START_TIME_2 |
														MIDNIGHT_START_TIME_3 |
														MIDNIGHT_START_TIME_4 |
														MIDNIGHT_START_TIME_5)));
}

/*************************************************************************
	module		:[料金テーブルでの単位料金の獲得]
	function	:[
		1.
	]
	return		:[1～255:1～255円]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[1996/05/13]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_BaseCostInCostTable(void)
{
	return(SYB_MachineUniqSwitch[UNIQ_SW_H9]);
}


/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* ＨＩＮＯＫＩ タイプ *//* Add By O.Kimoto 1998/08/28 */
/*************************************************************************
	module		:[あるキーを送信証ON/OFFのキーとして流用するかしないか]
	function	:[
		1.
	]
	return		:[
		０    ：通信証ON/OFFオペレーション無効（本来のオペレーション起動のこと）
		その他：通信証ON/OFFオペレーション有効
	]
	common		:[]
	condition	:[]
	comment		:[
		H:6-5 【SCDR-No.111】通信証設定の改善 このスイッチを１にすると、スタンプキーを通信証ON/FFのキー
							（通信確認キーでのオペレーションと同一）にする。
		#define SCDR_COMFIRM_OPR			0x20
	]
	machine		:[V53,H8/300]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_CSDR_ConfirmOprEnable(void){}]
	date		:[1998/12/03]
	author		:[木元  修]
*************************************************************************/
UBYTE CHK_UNI_CSDR_ConfirmOprEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H6] & SCDR_COMFIRM_OPR));
}


/*************************************************************************
	module		:[あるキーを発信元ON/OFFのキーとして流用するかしないか]
	function	:[
		1.
	]
	return		:[
		０    ：発信元ON/OFFオペレーション無効（本来のオペレーション起動のこと）
		その他：発信元ON/OFFオペレーション有効
	]
	common		:[]
	condition	:[]
	comment		:[
		H:6-6 【SCDR-No.102】このスイッチを１にするとスタンプキーを「発信元印字する／しない」キーに割り当てる
		#define SCDR_TTI_ENABLE_OPR			0x40
	]
	machine		:[V53,H8/300]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_CSDR_TtiTxOprEnable(void){}]
	date		:[1998/12/03]
	author		:[木元  修]
*************************************************************************/
UBYTE CHK_UNI_CSDR_TtiTxOprEnable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H6] & SCDR_TTI_ENABLE_OPR));
}


/*************************************************************************
	module		:[ダイヤル記号の順番入れ替え]
	function	:[
		1.
	]
	return		:[
		０    ：”  －”-> ”／”->”！”->”－！”
		０以外：”－！”-> ”－”->”／”->”  ！”
	]
	common		:[]
	condition	:[]
	comment		:[
		H:6-7 【CSDR-No.58】ダイヤルリバースキーのワンタッチ化
        	      このスイッチを１にすると、ダイヤル記号キーの順番を変更する。
		#define CSDR_DIANL_MARK_EXCHANGE	0x80
	]
	machine		:[V53,H8/300]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_CSDR_DialMarkExchange(void){}]
	date		:[1998/12/03]
	author		:[木元  修]
*************************************************************************/
UBYTE CHK_UNI_CSDR_DialMarkExchange(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H6] & CSDR_DIANL_MARK_EXCHANGE));
}

#endif

/* Atlanta TCR画像つける・つけないSW追加 1999/08/26 M.Maeda */
/*************************************************************************
	module		:[送信原稿付き送信証プリント無効/有効の獲得]
	function	:[]
	return		:[	0    :画像あり
			  		0以外:なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[CMN]
	date		:[1999/06/23]
	author		:[K.Okada]
*************************************************************************/
UBYTE CHK_TcrWithDocument(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H7] & TCR_WITH_DOCUMENT));
}

/*************************************************************************
	module		:[トリプル動作制限]
	function	:[
		1.
	]
	return		:[
		０    ：トリプル制限あり
		０以外：トリプル制限なし
	]
	common		:[]
	condition	:[]
	comment		:[
	]
	machine		:[V53,H8/300]
	language	:[CH38(V.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_NoTripleRestrict(void){}]
	date		:[1999/02/18]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CHK_UNI_NoTripleRestrict(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H7] & NO_TRIPLE_RESTRICT));
}


#if (PRO_EXT_SEC_RX == ENABLE)			/* セキュリティ受信（単一キー対応）By H.Fujimura 1999/11/18 */
/*************************************************************************
	module		:[セキュリティー受信操作（拡張版）有効／無効]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[UBYTE CHK_UNI_ExtSecurityRxOperation(void){}]
	date		:[1999/11/26]
	author		:[木元 修]
*************************************************************************/
UBYTE CHK_UNI_ExtSecurityRxOperation(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_H7] & EXT_SEC_RX_OPERATION));
}
#endif



