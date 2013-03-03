/************************************************************************
*               BY:  M.Kotani
*             DATE:  1997/01/24
*        FILE NAME:  jbg_enc.c
*       Task ID No:
*      DESCRIPTION:  T.82(JBIG)による１ページ符号化復号化するためのタスク群
*  PUBLIC ROUTINES:
* PRIVATE ROUTINES:
*        REFERENCE:  ＪＢＩＧのエントリタスク
*************************************************************************/
#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\jbg_def.h"
#include "\src\cpu\sh7043_a\scd\define\jbg_pro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\jbg_tbl.h"
#else
#include "\src\atlanta\scd\define\jbg_def.h"
#include "\src\atlanta\scd\define\jbg_pro.h"
#include "\src\atlanta\scd\ext_v\jbg_data.h"
#include "\src\atlanta\scd\ext_v\jbg_tbl.h"
#endif

/*************************************************************************
	module		:[
		T.85(JBIG)による１ページ符号化処理をするタスク
	]
	function	:[
		1.大域変数の初期化
		2.入出力アドレスの設定
		3.ＢＩＨの作成
		4.ＢＩＤの作成
		5.フローティングマーカーセグメントの作成
		6.ＳＤＥの作成(ＡＡＥ(Adaptive Arithmetic Encoder)アダプティブ算術符号器の呼び出し)
		7.符号化するラインが残っている間はループする
	]
	return		:[なし]
	common		:[]
	condition	:[
		イメージデータのスタートアドレスが確定していること
		符号データのスタートアドレスが確定していること
	]
	comment		:[
		１論理ページのＢＩＥを作成することを目的とする
	]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_EncodePageTask(void)
{
	JBG_InitializeGlobalValue();		/** 大域変数の初期化 */
	JBG_SetEncodeIO_Address();			/** 入出力アドレスの設定 */
	JBG_MakeBIH();						/** ＢＩＨの作成 */
	do {								/** ＢＩＤの作成 */
		JBG_MakeFMS();					/** フローティングマーカーセグメントの作成 */
		JBG_AAE();						/** ＳＤＥの作成(ＡＡＥ(Adaptive Arithmetic Encoder)アダプティブ算術符号器の呼び出し) */
		JBG_RequestSDNORM = 1;			/** ＳＤＮＯＲＭの作成要求 */
		if ((1125 - JBG_EncodeLineCount) <= JBG_BIH.L0) {	/** ＮＥＷＬＥＮ後出し */
			JBG_BIH.YD = 1125;
			JBG_RequestNEWLWN++;	/** ＮＥＷＬＥＮフローティングマーカーセグメントの作成要求 */
		}
	} while (JBG_EncodeLineCount < JBG_BIH.YD);	/** 符号化するラインが残っている間はループする */
	JBG_RequestSDNORM = 0;			/** ＳＤＮＯＲＭの作成要求とりやめ */
	JBG_RequestSDRST = 1;			/** ＳＤＲＳＴの作成要求 */
	JBG_RequestNEWLWN = 0;			/** ＮＥＷＬＥＮフローティングマーカーセグメントの作成要求 */
	JBG_MakeFMS();					/** フローティングマーカーセグメントの作成 */
}


/*************************************************************************
	module		:[
		T.85(JBIG)による１ページ複合化処理をするタスク
	]
	function	:[
		1.
	]
	return		:[なし]
	common		:[
		BIH
	]
	condition	:[
	]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[JBG]
	date		:[1997/01/24]
	author		:[小谷正樹]
*************************************************************************/
void JBG_DecodePageTask(void)
{
	JBG_InitializeGlobalValue();		/** 大域変数の初期化 */
	JBG_SetDecodeIO_Address();			/** 入出力アドレスの設定 */
	JBG_DecodeBIH();					/** ＢＩＨの読み込み */
#if (JBG_DEBUG)
printbih();
#endif
	do {								/** ＢＩＤの読み込み */
		JBG_AAD();						/** ＳＤＥの読み込み(ＡＡＤ(Adaptive Arithmetic Decoder)アダプティブ算術復号器の呼び出し) */
		/** ＳＤＥ終了時のステータスチェック？ */
		if (JBG_DecodeEndStatus & JBG_BIT_ERROR) {
			break;
		}
		if (JBG_DecodeEndStatus & JBG_BIT_ABORT) {
			break;
		}
	} while (JBG_DecodeLineCount < JBG_BIH.YD);	/** 復号化するラインが残っている間はループする */
#if (JBG_DEBUG)
check();
#endif
}


