/*	By Y.Suzuki 1996/10/21	*/
/*	Original File jun\usr2:\src\kobe\anzu\src\cmnuni_e.h	*/
/************************************************
 * CMNUNI_E.C
 * 機種固有スイッチEの設定状態を獲得する関数
 * 1996/04/11 Eguchi
 ************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\unisw_e.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\std.h"

/*************************************************************************
	module		:[超高画質がスーパーファイン(200×400dpi)かハイパーファイン(400×400dpi)かの獲得]
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
	date		:[1994/07/01]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_HyperFineON(void)
{
#if (PRO_HQ_MODE == ENABLE) /* 1997/11/05 Y.Matsukuma */
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E0] & HYPER_FINE_ON));
#else
	return(0);
#endif
}

/*************************************************************************
	module		:[中間調でエッジ強調するか、しないかの選択]
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
	date		:[1994/07/07]
	author		:[宮崎仁一]
*************************************************************************/
UBYTE CHK_UNI_HalfToneEdgeON(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E0] & HALFTONE_EDGE_ON));
}

/*************************************************************************
	module		:[中間調を４００ＤＰＩで蓄積する]
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
	date		:[1994/07/29]
	author		:[S.Kawasaki]
*************************************************************************/
UBYTE CHK_UNI_HalfTone400DPI_ON(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E0] & HALFTONE_400DPI));
}

/*************************************************************************
	module		:[６４階調をディザで蓄積するか]
	function	:[
		1.
	]
	return		:[
				０：誤差拡散を使用
				１：ディザを使用
				　]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1994/08/31]
	author		:[S.Kawasaki]
*************************************************************************/
UBYTE CHK_UNI_64ScaleDither(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E0] & HALFTONE64_DITHER));
}



/*************************************************************************
	module		:[ファインー＞ノーマル変更無効／有効の獲得]
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
UBYTE	CHK_UNI_FineNormalConvert(void)
{
#if (PRO_PRINT_TYPE == LASER)	/*F100だけ論理を逆にするAdd By M.Kotani 1998/02/02*/
	if (CMN_CheckF100Model()) {
		if ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_E0] & FINE_TO_NORMAL)) {
			return (FALSE);
		}
		else {
			return (TRUE);
		}
	}
	else {
		return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_E0] & FINE_TO_NORMAL));
	}
#else
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_E0] & FINE_TO_NORMAL));
#endif
}


/*************************************************************************
	module		:[中間調コピーを400dpiディザで読む]
	function	:[
		中間調コピーを400dpiディザで読むかどうかを指定
		(中間調縮小コピーでのプリントのデコード遅れ対策)
	]
	return		:[
		0以外	有効
		0		無効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/07/10]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CHK_UNI_ReduceGrayCopyDither400( void )
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E0] & REDUCE_GRAY_COPY_DITHER_400));
}


/*************************************************************************
	module		:[中間調コピーを200dpiディザで読む]
	function	:[
		中間調コピーを200dpiディザで読むかどうかを指定
		(中間調縮小コピーでのプリントのデコード遅れ対策)
	]
	return		:[
		0以外	有効
		0		無効
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1997/07/10]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CHK_UNI_ReduceGrayCopyDither200( void )
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E0] & REDUCE_GRAY_COPY_DITHER_200));
}


/*************************************************************************
	module		:[ＦＩＮＥコピーの場合、３００ｄｐｉで読み取る]
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
	date		:[1996/09/17]
	author		:[坂本直史]
*************************************************************************/
UBYTE	CHK_UNI_FineCopyEFineScan(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_E0] & FINE_COPY_EFINE));
}



/*************************************************************************
	module		:[中間調(EFINE)ｽｷｬﾅｰ送信のｽﾛｰUPで読み飛ばすﾗｲﾝ数]
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
	date		:[1996/07/28]
	author		:[坂本直史]
*************************************************************************/
UBYTE	CHK_UNI_EFineNonScanLineCount(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_E1]));
}


/*************************************************************************
	module		:[ドラム寿命枚数11000枚に＋αする。]
	function	:[
		1.10000枚で予告、11000枚で印字停止している。
		ﾋﾞｯﾄ０から6までを使用して最大12700枚まで＋αする。
		V851で追加
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[2002/09/17]
	author		:[Y.Suzuki]
*************************************************************************/
UBYTE	CHK_UNI_AdditionalDrumLifeCount(void)
{
	return ((UBYTE )(SYB_MachineUniqSwitch[UNIQ_SW_E1] & 0x7F));
}


/*************************************************************************
	module		:[ミラーキャリッジの待機モード]
	function	:[
		1.
	]
	return		:[
		0:    固定モード
		0以外:可変モード
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/06/03]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CHK_UNI_MirrorReadyModeVariable(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & MIRROR_READY_VARIABLE));
}


/*************************************************************************
	module		:[ミラーキャリッジ固定待機モードの時の待機位置]
	function	:[
		1.
	]
	return		:[
		0:    FBS
		0以外:ADF
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/06/03]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CHK_UNI_MirrorStaticPositionADF(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & MIRROR_READY_STATIC_ADF));
}


/*************************************************************************
	module		:[ノーマルモードを４秒で読取るかどうか]
	function	:[
	]
	return		:[
		０    ：４秒読取りでない（２秒）
		０以外：４秒読取り
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1997/12/08]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CHK_UNI_NormalScan4Sec(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & NORMAL_MODE_4SEC));
}


/*************************************************************************
	module		:[メモリ送信原稿の中間調蓄積を誤差拡散で蓄積する]
	function	:[
	]
	return		:[
		０    ：ディザ
		０以外：誤差拡散
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/07/14]
	author		:[野瀬敏弘]
*************************************************************************/
UBYTE CHK_UNI_MemTxDocGosaScan(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & MEMTXDOC_GOSA_SCAN));
}


/*************************************************************************
	module		:[コピー原稿の先端読み飛ばしライン]
	function	:[
		コピー原稿の先端読み飛ばしライン
	]
	return		:[
		SFINEでのステップ数 (1/10step)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/10/23]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CHK_UNI_CopyDocTopSkipLine( void )
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E4] & COPY_DOC_TOP_SKIP_LINE));
}


/*************************************************************************
	module		:[FBS読取り開始位置の補正ステップ数]
	function	:[
		FBS読取り開始位置の補正ステップ数を返す
	]
	return		:[
		SFINEでの補正ステップ数
		-7 ～ +7 (単位:10ステップ)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/13]
	author		:[竹内茂樹]
*************************************************************************/
BYTE	CHK_UNI_FBS_AdjustStep( void )
{
	BYTE	step;	/* ステップ */

	step = (BYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E5] & HS_TO_FBS_ADJUST_STEP);
	if (SYB_MachineUniqSwitch[UNIQ_SW_E5] & HS_TO_FBS_ADJUST_SIGN) {
		step *= -1;
	}

	return (step);
}


/*************************************************************************
	module		:[ADF読取り位置の補正ステップ数]
	function	:[
		ADF読み取り位置のミラーキャリッジの補正ステップ数を返す
	]
	return		:[
		SFINEでの補正ステップ数
		-7 ～ +7 (単位:10ステップ)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/13]
	author		:[竹内茂樹]
*************************************************************************/
BYTE	CHK_UNI_ADF_AdjustStep( void )
{
	BYTE	step;	/* ステップ */

	step = (BYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E5] & ES_TO_ADF_ADJUST_STEP);
	step >>= 4;
	if (SYB_MachineUniqSwitch[UNIQ_SW_E5] & ES_TO_ADF_ADJUST_SIGN) {
		step *= -1;
	}

	return (step);
}


/*************************************************************************
	module		:[FBS原稿:左端余白量の取得]
	function	:[
		1.
	]
	return		:[
		余白量(dot)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/13]
	author		:[竹内茂樹]
*************************************************************************/
UWORD	CHK_UNI_FBS_LeftMargin(UWORD resolution)
{
	UBYTE dots;

	switch (resolution) {
	case 400:
		dots = 16;
		break;
	case 300:
		dots = 12;
		break;
	case 200:
		dots = 8;
		break;
	default:
		/* ありえない */
		break;
	}

	return ((UWORD)((SYB_MachineUniqSwitch[UNIQ_SW_E6] & FBS_LEFT_MARGIN) * dots));
}


/*************************************************************************
	module		:[FBS原稿:右端余白量の取得]
	function	:[
		1.
	]
	return		:[
		余白量(mm)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/13]
	author		:[竹内茂樹]
*************************************************************************/
UWORD	CHK_UNI_FBS_RightMargin(UWORD resolution)
{
	UBYTE dots;

	switch (resolution) {
	case 400:
		dots = 16;
		break;
	case 300:
		dots = 12;
		break;
	case 200:
		dots = 8;
		break;
	default:
		/* ありえない */
		break;
	}

	return ((UWORD)((SYB_MachineUniqSwitch[UNIQ_SW_E7] & FBS_RIGHT_MARGIN) * dots));
}


/*************************************************************************
	module		:[FBS原稿:先端余白量の取得]
	function	:[
		1.
	]
	return		:[
		余白量(mm)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/13]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CHK_UNI_FBS_TopMargin( void )
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E8] & FBS_TOP_MARGIN));
}


/*************************************************************************
	module		:[FBS原稿:後端余白量の取得]
	function	:[
		1.
	]
	return		:[
		余白量(mm)
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/06/13]
	author		:[竹内茂樹]
*************************************************************************/
UBYTE	CHK_UNI_FBS_BottomMargin( void )
{
	return ((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E9] & FBS_BOTTOM_MARGIN));
}

/*************************************************************************
	module		:[コピー時の画質をテストモードにする／しないの獲得]
	function	:[
		1.
	]
	return		:[0    :通常モード
				  0以外:テストモード
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[CMN]
	date		:[Sep.21.1996]
	author		:[曽根岡拓/吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_SwCopyTestMode(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & MODE_SW_TEST));
}


/*************************************************************************
	module		:[シェーディング実施するときに無限にランプ点灯する／しないの獲得]
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
	date		:[1998/09/09]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_ShadingTest(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & SHADING_TEST));
}


/*************************************************************************
	module		:[ノーマルをファインで読んで副操作１／２縮小]
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
	date		:[1998/09/30]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CHK_UNI_NormFineScan(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & NORM_FINE_SCAN));
}
/*************************************************************************
	module		:[読み取り時にパンチ穴で原稿の後端と誤判断しない対策]
	function	:[
		1.パンチ穴サイズの原稿なし状態は、チャタリングと判断して、ページの終了とは判断しません。
	]
	return		:[
		０    ：パンチ穴対策なし
		０以外：パンチ穴対策あり
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	date		:[1999/02/15]
	author		:[吉川弘康]
*************************************************************************/
UBYTE CHK_UNI_PunchHoleScan(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E2] & PUNCH_HOLE_SCAN));
}
/*************************************************************************
	module		:[マルチコピー時の縮小処理]
	function	:[
		1.マルチコピー時、Ｂ４原稿で、記録紙Ａ４の場合、
		  蓄積で縮小するか、プリントで縮小するかを選択する
	]
	return		:[
		０    ：蓄積時に縮小する
		０以外：プリント時に縮小する
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	date		:[1999/02/17]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE CHK_UNI_ReductionPrint(void)
{
	return((UBYTE)(SYB_MachineUniqSwitch[UNIQ_SW_E3] & REDUCTION_SCAN_PRINT));
}
