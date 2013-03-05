/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_SERV.C
*	Author		: 渡辺一章
*	Date		: 1996/10/21
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: サービスファンクション
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\keycode.h"
#include	"\src\atlanta\define\mntsw_a.h"
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syslifem.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\define\sysrxsw.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"
#include	"\src\memsw\define\mem_sw_b.h"
#include	"\src\memsw\define\mem_sw_h.h"

#include	"\src\atlanta\define\cmn_pro.h"
/*#include	"\src\atlanta\define\idp_pro.h"	/* 移植まだ */
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\man_pro.h"		/* by K.Watanabe 1998/08/21 */
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\stng_pro.h"
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
#include	"\src\atlanta\define\uni_pro.h"
#endif
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\cpu_tbl.h"

#if (PRO_MODEM == ORANGE3) /* By H.Fujimura 1999/01/06 */
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#endif
#if (PRO_MODEM == R288F) /* By H.Fujimura 1999/01/06 */
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#if !defined (KEISATSU) /* 警察FAX 05/06/24 石橋正和 */
		#include "\src\atlanta\mdm\fm336\define\mdm_bps.h"
#endif
		#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
		#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
		#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
		#include "\src\atlanta\mdm\r288f\define\mdm_bps.h"
		#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
		#include "\src\atlanta\mdm\r288f\define\mdm_io.h"
		#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
	#endif
#endif
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"
#include	"\src\atlanta\mdm\pana\define\mdm_bps.h"
#include	"\src\atlanta\mdm\pana\define\mdm_pro.h"
#include	"\src\atlanta\mdm\pana\define\mdm_io.h"
#include	"\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif
#include	"\src\atlanta\ext_v\fcm_data.h"
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
#include	"\src\atlanta\ext_v\lst_data.h"
#endif
#include	"\src\atlanta\ext_v\man_data.h"		/* by K.Watanabe 1998/08/21 */
#include	"\src\atlanta\ext_v\mem_data.h"
#include	"\src\atlanta\ext_v\rom_tbl.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\sys_port.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_tbl.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"
#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\satsuki2\define\scn_pro.h"
 #elif defined(STOCKHM2)
#include	"\src\atlanta\stockhm2\define\scn_pro.h"
 #else
#include	"\src\atlanta\hinoki\define\scn_pro.h"
 #endif
#include	"\src\atlanta\define\mntsw_c.h"
#endif
#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\define\io_pro.h"
#include	"\src\atlanta\sh7043\define\sh_sys.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\define\cl1_def.h"
#include	"\src\atlanta\define\scn_def.h"
#include	"\src\atlanta\define\scn_pro.h"
#endif

#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\define\prn_pro.h"
#include	"\src\atlanta\prt\ph3\ext_v\prn_data.h"
#else
 #if (PRO_PRINT_TYPE != THERMAL) /* By H.Fujimura 1999/01/06 */
#include	"\src\atlanta\prt\sp322\ext_v\prn_data.h"
/*#include	"\src\atlanta\prt\sp322\ext_v\prn_tbl.h"*/
 #endif
#endif

#if (PRO_MULTI_LINE == ENABLE)
#include	"\src\atlanta\define\sys_opt.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\atlanta\define\mlt_pro.h"
#include	"\src\atlanta\define\uni_pro.h"
#include 	"\src\atlanta\define\unisw_a.h"
#include	"\src\atlanta\ext_v\mlt_data.h"
#endif
#include	"\src\atlanta\ext_v\cmn_data.h"

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/08/20 */
#include "\src\atlanta\define\inf_def.h"
#include "\src\atlanta\ext_v\inf_data.h"
#endif

#if (PRO_NEW_JATE == ENABLE)	/* 1998/10/06 H.Yoshikawa *//* Add By O.Kimoto 1999/03/01 */
#include "\src\atlanta\ext_v\cmn_tbl.h"
#endif

#if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 */
/*	Added by SMuratec K.W.Q	2003/09/26	*/

#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\satsuki2\define\scn_pro.h"
#include "\src\atlanta\satsuki2\ext_v\scn_data.h"
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
#include	"\src\atlanta\satsuki2\define\scn_def.h"
#include	"\src\atlanta\satsuki2\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"

#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"

#endif

#if (0) /* 変更 by SMuratec K.W.Q 2003/10/22 */
#define SAMPLE_LINE_COUNT	10
#endif

#if defined(STOCKHM2)
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\stockhm2\define\scn_pro.h"
#include "\src\atlanta\stockhm2\ext_v\scn_data.h"
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h"
#include "\src\atlanta\stockhm2\define\scn_def.h"
#include "\src\atlanta\stockhm2\ext_v\scn_tbl.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\define\def_evtn.h"

#endif

#if (PRO_RTC_RX5C338A == ENABLE)
#include	"\src\atlanta\define\rtc_def.h"
#endif

#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)				/* 防災FAX対応 by Y.Kano 2005/03/04 	*/
#include 	"\src\atlanta\ext_v\fcm_tbl.h"
#include 	"\src\atlanta\define\unisw_i.h"
#include 	"\src\atlanta\define\unisw_a.h"
#include 	"\src\atlanta\define\unisw_b.h"
#include 	"\src\atlanta\define\unisw_c.h"
#include 	"\src\atlanta\define\unisw_d.h"
#include	"\src\memsw\define\mem_sw_d.h"
#include 	"\src\atlanta\ext_v\ini_tbl.h"
#endif

/* Prototype
void	MachineParameterMode(void);			/ *0 /
void	MemorySwitchMode(void);				/ *1 /
UBYTE	SelectSetClearMode(void);
void	SetSoftSwitch(void);
UBYTE	SelectSoftSwitch(void);
void	DisplaySoftSwitchSelect(void);
void	ClearSoftSwitch(UBYTE);
UBYTE	SoftDipInput(void);
void	SoftDipInputInitial(void);
void	ClearBackUpFile(void);				/ *2 /
void	ClearAllBackUpFile(void);			/ *3 /
void	UniqSwitchMode(void);				/ *4 /
void	T30MonitorPrintOperation(void);		/ *5 /
#if (PRO_PRINT_TYPE == LED)	@@ 1997/07/10 Y.Matsukuma @@
void	PrintMaintenance(void);				/ *6(ﾎﾟﾌﾟﾗ) /
void	ReplaceCountSetOperation(void);
void	ServiceCallOperation(void);
void	SearchServiceCallRight(UBYTE *);
void	SearchServiceCallLeft(UBYTE *);
#endif
void	FunctionListPrintOperation(void);	/ *8 /
void	ServiceFunctionSetting(void);		/ *9 /
void	SF_InnerStatusOperation(void);		/ *9-1 /
void	SF_LifeMonitorClear(void);			/ *9-2, *H /
void	SF_TestPatternOperation(void);		/ *9-3 /
void	DisplayPatternPrint(UBYTE, UBYTE);
void	SF_StampTest(void);					/ *9-4 /
void	SF_DocumentFeedOutTest(void);		/ *9-5 /
void	SF_ShadingOperation(void);			/ *9-6 /
void	PrintMemorySwList(void);			/ *A /
void	FactoryFunctionMode(void);			/ *B /
void	PrintFactoryFunctionList(void);		/ *B-1 /
void	SF_All_LED_Test(void);				/ *B-2 /
void	SF_LED_Test(void);					/ *B-2 /
void	SF_LCD_Test(void);					/ *B-3 /
void	SF_PanelKeyTest(void);				/ *B-4 /
void	SF_RTCTestFunction(void);			/ *B-7 /
void	SF_RS232CTestFunction(void);		/ *B-8 /
#if (0)	@@ チェッカーのみ 97/09/10 By M.Kuwahara @@
void	SF_CassetteCheck(void);				/ *B-9 /
void	DisplayCassetteCheck(UBYTE);
#endif
void	LineFunctionMode(void);				/ *C /
void	SF_RelayTest(void);					/ *C-1 /
void	DisplayRelayTest(void);
void	SF_TonalTest(void);					/ *C-2 /
UBYTE	TxSignalType(UBYTE);
UBYTE	TxSignalFreq(UBYTE, UBYTE);
void	FskPixStop(void);
void	DisplayTonalTest(UBYTE, UBYTE, UBYTE);
void	SF_DTMF_Test(void);					/ *C-3 /
void	DisplayTxDTMF(UBYTE);
UBYTE	DTMF_TypeGet(UBYTE);
void	ConnectLine(void);
void	DisconnectLine(void);
void	InvalidServiceFunction(void);
void	TeachingRingPattern(void);			/ *D(USA) /
#if (PRO_RING_MASTER == ENABLE)
void	DisplayTeachingPattern(UBYTE);
#endif
void	SetMirrorCarrigeTransMode(void);	/ *E(ﾎﾟﾌﾟﾗB) /
void	ConsumptionArticleOrderFunc(void);	/ *F(ﾎﾟﾌﾟﾗ) /
UBYTE	EnterConsumerOrder(void);
UBYTE	ToCustomerCodeInput(void);
UBYTE	ToCompanyNameInput(void);
UBYTE	FromCustomerCodeInput(void);
UBYTE	FromCompanyNameInput(void);
UBYTE	FromSectionNameInput(void);
UBYTE	FromSectionName2Input(void);    addedbythonda1998/05/22
UBYTE	FromCustomerTelNumberInput(void);
UBYTE	SerialNumberInput(void);
#if(0)	/@ ＲＯＭ容量削減の為 by K.Watanabe 1998/04/24 @/
UBYTE	SetDateInput(void);
#endif
UBYTE	PrintConsumerOrderForm(void);
void	ServicePrintSettingList(void);		/ *G /
#if (PRO_MULTI_LINE == ENABLE)
void	MultiLineFunctionMode(void);		/ *J(ﾎﾟﾌﾟﾗ), *E(ｱﾝｽﾞ) /
void	SF_MultiRelayTest(void);
void	SF_MultiTonalTest(void);
void	SF_MultiDTMF_Test(void);
UWORD	MultiPixPattern(UWORD);
void	DisplayMultiTonalTest(UBYTE, UBYTE );
void 	DisplayMultiTxDTMF(UBYTE);
#endif
void	SF_OptionDataInitial(void);			/ *K /
void	ClearOrderData(void);				/ *L(ﾎﾟﾌﾟﾗ) /
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  / lifemonitorbythonda1998/06/01 /
void	SetLifeMonitorPasscode(void);		/ *P(ﾎﾟﾌﾟﾗ) /
#endif
#if (0) @@ ROM容量の関係でコメントにします T.Fukumoto @@
void	EditLifeMonitor(void);				/ *Z(ﾎﾟﾌﾟﾗ) /
UBYTE	LifeMonitorNumberInput(UBYTE *, UBYTE);
#endif
void	SetMonitorSpeakerOnOff(void);		/ *[33](ﾎﾟﾌﾟﾗ), *L(ｱﾝｽﾞ) /
void	MemoryDump(void);					/ *[34](ﾎﾟﾌﾟﾗ), *M(ｱﾝｽﾞ) /
UBYTE	InputAddressOrLength(UBYTE *, UBYTE, UBYTE, UBYTE *);

void	MaintenanceOperationMode(void);		/ ** /
void	MachineStatusMonitor(void);			/ **1 /
void	Class1MonitorPrintOperation(void);	/ **2 /
void	PrinterStatusMonitor(void);			/ **3 /
#if (PRO_KEYPANEL == PANEL_ANZU_L)	/@ ﾎﾟﾌﾟﾗのROM容量削減の為、条件ｺﾝﾊﾟｲﾙ追加 by K.Watanabe 1998/04/24 @/
void	EmptyAndMemoryAreaDisplay(void);	/ **4(ｱﾝｽﾞ) /
#endif
#if defined(POPLAR_F)
void	EmptyAndMemoryAreaDisplay(void);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
void 	ChangeRxSecondLine(void);			/ **5(ｱﾝｽﾞ) /
#endif
void	ServiceReportPrintOperation(void);	/ **A /
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/ by K.Watanabe 1998/09/24 /
void	PrintErrorList(void);				/ **B(ﾎﾟﾌﾟﾗB) /
#endif
void	MaintenanceSwitchMode(void);		/ **[40](ﾎﾟﾌﾟﾗ), **P6(ｱﾝｽﾞ) /
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
void 	MinoltaTestOperation(UBYTE);
void	ClearMinoltaTestPrintArea(void);
void	MinoltaTestPatternPrint(UBYTE);
void	MinoltaTestPatternPrintCheck(void);
void	MinoltaTestPatternPrintPG(void);
void	MinoltaTestPatternDisplay(void);
#endif
*/

static UWORD	tskno_txtask = 0xFFFF;	/* トーナルテスト：ＦＳＫ／ＰＩＸ送出タスクＴＩＤ */

#include	"\src\atlanta\ext_v\ncu_data.h"

#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
 #if defined(SATSUKI2) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\satsuki2\define\m_param.h"
 #elif defined(STOCKHM2)
#include	"\src\atlanta\stockhm2\define\m_param.h"
 #else
#include	"\src\atlanta\hinoki\define\m_param.h"
 #endif
#include	"\src\atlanta\define\mntsw_h.h"
 #if defined(SATSUKI2) || defined(STOCKHM2)
#include "\src\atlanta\sh7043\define\sh_port.h"
 #else
#include "\src\atlanta\hinoki\define\hinoport.h"
 #endif
 #if defined(STOCKHM2)		/* Modify by SMuratec K.W.Q 2004/05/18 */
#include	"\src\atlanta\prt\lv_therm\define\prt_pro.h"
 #else
#include	"\src\atlanta\prt\iu_therm\define\prt_pro.h"
 #endif
#endif

#if defined(POPLAR_F)
#include	"\src\atlanta\sh7043\define\sh_port.h"
#endif

/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件
** T.Nose 1997/12/20
*/
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\define\mntsw_c.h"

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/14 */
#include	"\src\memsw\define\mem_sw_a.h"
#include	"\src\memsw\define\mem_sw_g.h"
#include	"\src\atlanta\hinoki\define\m_param.h"
#endif		/* End of (defined (KEISATSU)) */

extern UWORD			RsRxIntCount;	/* test debugcl1 */

#if defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2)	/* for debug */
 #if defined (JPN)
#include	"\src\atlanta\define\ncu_pro.h"
void TestDialinDetectDTMF(void);	/* 2002/01/24 T.Takagi */
 #endif
void PC24V_TestMode(void);			/* 2002/12/03 T.Takagi */
#endif


/*************************************************************************
 * ［ポプラＢ・Ｌ］
 * ****サービスファンクション一覧（機能　＋　＊で始まる）*****
 *		0.マシンパラメータセット・クリア
 *		1.メモリスイッチセット・クリア
 *		2.ユーザー設定クリア
 *		3.オールラムクリア
 *		4.機種固有スイッチセット・クリア
 *		5.Ｔ３０モニタープリント
 *		6.プリンタメンテナンス
 *			1.交換カウンタセット
 *			2.サービスコール
 *		7.未使用
 *		8.ファンクションリスト
 *		9.テストファンクション
 *			1.ライフモニター
 *				A:ＲＯＭバージョン
 *				B:読みとり枚数
 *				C:印字枚数
 *				D:送信枚数
 *				E:ドラム交換回数
 *				F:ドラム寿命
 *			2.ライフモニタークリア
 *			3.テストパターンプリント
 *			4.スタンプテスト
 *			5.シェーディングデータ取り込み
 *		A.パラメーターリストプリント
 *		B.工場ファンクション
 *			1.工場ファンクションリスト
 *			2.ＬＥＤテスト
 *			3.ＬＣＤテスト
 *			4.パネルキーテスト
 *			5.ＳＲＡＭチェック
 *			6.ＤＲＡＭチェック
 *			7.ＲＴＣテスト
 *			8.ＲＳ２３２３Ｃテスト
 *		C.回線テスト
 *			1.リレーテスト
 *			2.トーナルテスト
 *			3.ＤＴＭＦテスト
 *		D.リングマスターパターン自動検出 (USAのみ)
 *		E.ミラーキャリッジ輸送モードセット
 *		F.消耗品発注機能
 *		G.機器設定リストプリント
 *		H.ライフモニタークリア
 *		I.ＤＲＡＭクリア
 *		J.回線テスト（２回仕様）
 *		K.オプションデータ初期化
 *		L.消耗品発注データクリア
 *		P.ライフモニタパスコード（JPN以外）
 *		[33].モニタースピーカーＯＮ／ＯＦＦ
 *		[34].メモリダンプ表示
 * ****テストオペレーション一覧（機能　＋　＊　＋　＊で始まる）*****
 *		1.マシンステータス表示
 *		2.クラス１オンラインモニタープリント
 *		3.プリンターステータス表示
 *		A.サービスレポートプリント
 *		[40].保守用スイッチセット・クリア
 *
 *
 * ［アンズＬ］
 * ****サービスファンクション一覧（機能　＋　＊で始まる）*****
 *		0.マシンパラメータセット・クリア
 *		1.メモリスイッチセット・クリア
 *		2.ユーザー設定クリア
 *		3.オールラムクリア
 *		4.機種固有スイッチセット・クリア
 *		5.Ｔ３０モニタープリント
 *		6.未使用
 *		7.未使用
 *		8.ファンクションリスト
 *		9.テストファンクション
 *			1.ライフモニター
 *				A:ＲＯＭバージョン
 *				B:読みとり枚数
 *				C:印字枚数
 *				D:送信枚数
 *				E:ドラム交換回数
 *				F:ドラム寿命
 *			2.ライフモニタークリア
 *			3.テストパターンプリント
 *			4.スタンプテスト
 *			5.シェーディングデータ取り込み
 *		A.パラメーターリストプリント
 *		B.工場ファンクション
 *			1.工場ファンクションリスト
 *			2.ＬＥＤテスト
 *			3.ＬＣＤテスト
 *			4.パネルキーテスト
 *			5.ＳＲＡＭチェック
 *			6.ＤＲＡＭチェック
 *			7.ＲＴＣテスト
 *			8.ＲＳ２３２３Ｃテスト
 *		C.回線テスト
 *			1.リレーテスト
 *			2.トーナルテスト
 *			3.ＤＴＭＦテスト
 *		D.リングマスターパターン自動検出 (USAのみ)
 *		E.回線テスト（２回仕様）
 *		F.サービスレポートプリント
 *		G.機器設定リストプリント
 *		H.ライフモニタークリア
 *		I.ＤＲＡＭクリア
 *		K.オプションデータ初期化
 *		L.モニタースピーカーＯＮ／ＯＦＦ
 *		M.メモリダンプ表示
 * ****テストオペレーション一覧（機能　＋　＊　＋　＊で始まる）*****
 *		1.マシンステータス表示
 *		2.クラス１オンラインモニタープリント
 *		3.プリンターステータス表示
 *		4.メモリ残量・EMPTYファイル数表示
 *		A.サービスレポートプリント
 *		P06.保守用スイッチセット・クリア
*************************************************************************/

/*************************************************************************
	module		:[マシーンパラメーターオペレーション]
	function	:[
		1.機能+＊+0
		2.マシーンパラメーターのセット／クリアを実行
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
void MachineParameterMode(void)
{
	UBYTE	mode;

	/* データのセット */
	OPR_Buf.SoftSwCtrl.ItemWording  = D2W_SF_ParameterSet;			/* [Set Parameters      ] */
	OPR_Buf.SoftSwCtrl.SetParameter = &SYB_MachineParameter[0];		/* ﾏｼｰﾝﾊﾟﾗﾒｰﾀ */
	OPR_Buf.SoftSwCtrl.SwitchMax    = SYS_MACHINE_PARAMETER_MAX;	/* 最大１００個 */
	OPR_Buf.SoftSwCtrl.SelectSwitch = 0;							/* 初期値０（Ａ０）SATSUKI2では（００）*/

	/* 編集するかクリアするか選択させる */
	mode = SelectSetClearMode();

	if (mode == PARAMETER_SET) {		/* 編集の場合 */
		SetSoftSwitch();
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_MACHINE_PARA);
#endif
	}
	else if (mode == PARAMETER_CLEAR) {	/* クリアの場合 */
		ClearSoftSwitch(MACHINE_PARAMETER_MODE);
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_MACHINE_PARA);
#endif
	}
	else { /* 終了OPR_END */
		return;
	}
}

/*************************************************************************
	module		:[メモリースイッチオペレーション]
	function	:[
		1.機能+＊+１
		2.メモリースイッチのセット／クリアを実行
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
void MemorySwitchMode(void)
{
	UBYTE	mode;

	/* データのセット */
	OPR_Buf.SoftSwCtrl.ItemWording  = D2W_SF_MemorySwitchSet;	/* [Set Memory Switch   ]*/
	OPR_Buf.SoftSwCtrl.SetParameter = &SYS_MemorySwitch[0];		/* ﾒﾓﾘｰｽｲｯﾁ */
	OPR_Buf.SoftSwCtrl.SwitchMax    = SYS_MEMORY_SWITCH_MAX;	/* 最大１００個 */
	OPR_Buf.SoftSwCtrl.SelectSwitch = 0;						/* 初期値０（Ａ０）SATSUKI2では（００）*/

	/** セットするかクリアするか選択させる */
	mode = SelectSetClearMode();

	if (mode == PARAMETER_SET) {		/* 編集する場合 */
		SetSoftSwitch();
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_MEMORY_SWITCH);
#endif
	}
	else if (mode == PARAMETER_CLEAR) {	/* クリアの場合 */
		ClearSoftSwitch(MEMORY_SWITCH_MODE);
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_MEMORY_SWITCH);
#endif
	}
	else {/*OPR_END*/
		return;
	}
}

/*************************************************************************
	module		:[編集するかクリアするかの選択]
	function	:[
		1.
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
UBYTE SelectSetClearMode(void)
{
	UBYTE	status;		/* 0:set　1:clear */
	UBYTE	key;
	UBYTE	keytype;

	status = 0;

	/** 初期表示 [Set MemorySwitch    ][Set Parameters      ]*/
	/*			 [      Program/Enter ][      Program/Enter ]*/
	DisplayStringHigh(0, OPR_Buf.SoftSwCtrl.ItemWording); /* ****Set */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while (1) {
		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		switch (keytype) {
		case FUNCTION:		/* 機能キー */
		case LEFT_ARROW:	/* 左矢印  */
			/** 編集／クリアを切り替え */

			status ^= (UBYTE)0x01;
			DisplayStringHigh(0, OPR_Buf.SoftSwCtrl.ItemWording + status * OPR_WORDING_LEN);
			/* Set / Clearのワーディングは並べて登録すること */
			break;

		case ENTER: /* セット */
			/** 決定 */
			if (status == 0) /* 編集 */
				return (PARAMETER_SET);
			else /* クリア */
				return (PARAMETER_CLEAR);

		case STOP:
		case KEY_TIME_UP:
			/** 終了 */
			return (OPR_END);

		case NO_EFFECT:
			break; /* ナックをならさんため */
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[パラメータの編集]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口,渡辺一章]
*************************************************************************/
void SetSoftSwitch(void)
{
	UWORD	i;
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	UWORD DBG_Status;
#endif
#if (PRO_NEW_JATE == ENABLE)	/* 1998/10/06 H.Yoshikawa */
	UBYTE attenation;
#endif
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/12 */
	UBYTE	temp;
#endif
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	UBYTE	memory_sw_edit_mode;	/* メモリSWの編集が可能になった */
#endif

#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)
	memory_sw_edit_mode = FALSE;
#endif
#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
	UBYTE att;
#endif

	while (1) {
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* スイッチの位置を選択したので編集ガードを解除 */
		/** 編集するパラメータを選択 */
		if (SelectSoftSwitch(memory_sw_edit_mode) == OPR_END) {/** 選択中にストップキー*/
			return; /* 終了 */
		}
		memory_sw_edit_mode = TRUE;
#else
		/** 編集するパラメータを選択 */
		if (SelectSoftSwitch() == OPR_END) {/** 選択中にストップキー*/
			return; /* 終了 */
		}
#endif

		/** パラメータの編集 */
		DisplayStringHigh(0, OPR_Buf.SoftSwCtrl.ItemWording);
		SoftDipInputInitial();  /* 初期値セット :OPR_Buf.SoftSwCtrl ->> CharacterInput */
		if (SoftDipInput() == NG) {	/* 編集中にストップキー */
			return;
		}

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/12 */
		temp = CHK_UNI_MultiT30Monitor();
#endif

		/** 編集終了した場合,新しいデータを格納 */
		OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] = StoreCharacterInputToSoftDip();

#if defined(POPLAR_F)
#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/12 */
		if (CHK_UNI_MultiT30Monitor() != temp) {
			InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
			InitializeMachineStatus();									/** マシーンステータスのクリア	*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
			SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
			Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
  #if defined(KEISATSU) /* スクランブルBITが落ちてしまう件 O.Oshima 2005/12/06 */
			InitializeSensor();											/** センサーを初期化			*/
  #endif
		}
 #endif
#endif

		/*-------------------------------------------------------------
		** 新JATE基準（98/04以降）では、送出レベルは-8dBm以下となりましたので、
		** 初期値を-8.5dBmとなるようにします。CountryTable[][COUNTRY_SW_15])に定義すみ
		** ソフト調整範囲は、初期値（-8.5dBm）より小さい値でなければなりません。
		** 初期値より小さい値がセットされた場合には、強制的に初期値にします。
		** この時、初期値より小さい値を設定できないようにする方法もありますが、
		** 初期値の値がわからなくなったために、設定できなくなるのを防ぎます。
		** テスト用に、０ｄＢまで調整できるようにしておきます。
		** 1998/10/08 H.Yoshikawa
		** 機種固有ＳＷのＢ７－６に移動しました 1999/01/05
		*/
#if (PRO_NEW_JATE == ENABLE)	/* 1998/10/06 H.Yoshikawa *//* Add By O.Kimoto 1999/03/01 */
		if (!CHK_UNI_TxLevelUpper0DB()) {	/* 1999/01/05 H.Yoshikawa */
			if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == (&SYB_MachineParameter[MACHINE_PARA_1])) {
 				attenation = (UBYTE)(SYB_MachineParameter[MACHINE_PARA_1] & ATTENATION_MACHINE_PARA);
 				if (attenation) {
	 				if (attenation < CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]) {
		 				SYB_MachineParameter[MACHINE_PARA_1] &= ~ATTENATION_MACHINE_PARA;
		 				SYB_MachineParameter[MACHINE_PARA_1] |= (ATTENATION_MACHINE_PARA & (CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]));
					}
				}
			}
			if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == (&SYS_MemorySwitch[MEMORY_SW_B1])) {
				attenation = (UBYTE)(SYS_MemorySwitch[MEMORY_SW_B1] & ATTENATION);
				if (attenation < CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]) {
					SYS_MemorySwitch[MEMORY_SW_B1] &= ~ATTENATION;
					SYS_MemorySwitch[MEMORY_SW_B1] |= (ATTENATION & (CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15]));
				}
			}
		}
#endif

#if defined (KEISATSU) /* 警察FAX 05/04/27 石橋正和 */
		att = OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] & ATTENATION;
		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYB_MachineParameter[MACHINE_PARA_1]) {
			SYS_MemorySwitch[MEMORY_SW_B1] &= ~ATTENATION;
			SYS_MemorySwitch[MEMORY_SW_B1] |= att;
		}
		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYB_MachineParameter[M_PARA_SW_B3]) {
			SYS_MemorySwitch[MEMORY_SW_B4] &= ~ATTENATION;
			SYS_MemorySwitch[MEMORY_SW_B4] |= att;
		}
		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYS_MemorySwitch[MEMORY_SW_B1]) {
			SYB_MachineParameter[MACHINE_PARA_1] &= ~ATTENATION;
			SYB_MachineParameter[MACHINE_PARA_1] |= att;
		}
		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYS_MemorySwitch[MEMORY_SW_B4]) {
			SYB_MachineParameter[M_PARA_SW_B3] &= ~ATTENATION;
			SYB_MachineParameter[M_PARA_SW_B3] |= att;
		}
#else
		/* 機器パラメータ編集でスイッチＡ１の送出レベル設定に０以外がセットされた場合、
		** 全オートダイヤラの送出レベルを変更します
		*/
		if ((&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYB_MachineParameter[MACHINE_PARA_1])
		 && (OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] & ATTENATION_MACHINE_PARA)) {
			/* 全ワンタッチダイアル属性アッテネータ変更 */
			for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
				if ((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0) {
					SYB_OnetouchDial[i].Attribute2 &= ~ATTENATION;
					SYB_OnetouchDial[i].Attribute2 |= (SYB_MachineParameter[MACHINE_PARA_1] & ATTENATION_MACHINE_PARA);
				}
			}
			/* 全短縮ダイアル属性アッテネータ変更 */
			for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
				if (CheckSpeedStoreStatus(i) == OK) {
					SYB_SpeedDial[i].Attribute2 &= ~ATTENATION;
					SYB_SpeedDial[i].Attribute2 |= (SYB_MachineParameter[MACHINE_PARA_1] & ATTENATION_MACHINE_PARA);
				}
			}
			/* 機種共通スイッチアッテネータ変更 */
			SYS_MemorySwitch[MEMORY_SW_B1] &= ~ATTENATION;
			SYS_MemorySwitch[MEMORY_SW_B1] |= (SYB_MachineParameter[MACHINE_PARA_1] & ATTENATION_MACHINE_PARA);
		}
#endif

#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
		/* 濃度調整のパラメータ処理追加
		** 濃度普通のパラメータを調整した場合、濃い、薄いが０のとき、連動してセットするようにします
		** また、濃いと薄いのパラメータを調整した場合は、他のパラメータに連動しないようにします
		**
		** 注意：一度普通のパラメータ調整（０以外）を行い、濃い、薄いが連動してセットされた後、
		**       もう一度、普通のパラメータ調整を行なった場合、濃い、薄いには０以外の値がセットされているので
		**       連動されません
		*/
		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYB_MachineParameter[M_PARA_SW_H1]) {
#if (0) /* 並川の依頼 常に連動するように変更します 1999/1/22 by T.Soneoka */
**			if (!SYB_MachineParameter[M_PARA_SW_H0]) {
**				SYB_MachineParameter[M_PARA_SW_H0] = SYB_MachineParameter[M_PARA_SW_H1];
**			}
**			if (!SYB_MachineParameter[M_PARA_SW_H2]) {
**				SYB_MachineParameter[M_PARA_SW_H2] = SYB_MachineParameter[M_PARA_SW_H1];
**			}
#else
			SYB_MachineParameter[M_PARA_SW_H0] = SYB_MachineParameter[M_PARA_SW_H1];
			SYB_MachineParameter[M_PARA_SW_H2] = SYB_MachineParameter[M_PARA_SW_H1];
#endif
		}
		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYB_MachineParameter[M_PARA_SW_H4]) {
#if (0) /* 並川の依頼 常に連動するように変更します 1999/1/22 by T.Soneoka */
**			if (!SYB_MachineParameter[M_PARA_SW_H3]) {
**				SYB_MachineParameter[M_PARA_SW_H3] = SYB_MachineParameter[M_PARA_SW_H4];
**			}
**			if (!SYB_MachineParameter[M_PARA_SW_H5]) {
**				SYB_MachineParameter[M_PARA_SW_H5] = SYB_MachineParameter[M_PARA_SW_H4];
**			}
#else
			SYB_MachineParameter[M_PARA_SW_H3] = SYB_MachineParameter[M_PARA_SW_H4];
			SYB_MachineParameter[M_PARA_SW_H5] = SYB_MachineParameter[M_PARA_SW_H4];
#endif
		}

#if (0) /* 調査終了デバッグ終了 */
** 		/* プリントループ調査用 1999/1/27 by T.Soneoka */
** 		if (&OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch] == &SYB_MaintenanceSwitch[MNT_SW_H5]) {
** 			if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x10) {
** 				GA_IntMaskStatus |= (IMASK_PBRDY | IMASK_XCI);
** 				OutputWORD(GA_INT_MASK, GA_IntMaskStatus);
** 			}
** 			if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x04) {
** 				DBG_Status = InputWORD(GA_INT_STA);		/* G/A割込みステータス・ポート */
** 				OutputWORD(GA_INT_REC, DBG_Status);	/* 割込み受領 */
** 				PrinterPbreadyInt();
** 				DtcPermission = TRUE;
** 			}
** 		}
#endif
#endif

		/* スイッチを進める */
		OPR_Buf.SoftSwCtrl.SelectSwitch++;
		if (OPR_Buf.SoftSwCtrl.SelectSwitch >= OPR_Buf.SoftSwCtrl.SwitchMax) {
			OPR_Buf.SoftSwCtrl.SelectSwitch = 0;
		}
	}
}

/*************************************************************************
	module		:[編集するスイッチを選択]
	function	:[
		1.編集するスイッチ（A0からJ9）を選択
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口,渡辺一章]
*************************************************************************/
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)
UBYTE SelectSoftSwitch(UBYTE memory_sw_guard_release)
#else
UBYTE SelectSoftSwitch(void)
#endif
{
	UBYTE	key;			/*入力ｷｰﾃﾞｰﾀ*/
	UBYTE	keytype;
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* 編集するメモリSWをテンキー/カーソルで選択するまで編集をガードする by J.Kishida 2002/10/01 */
	UBYTE	onetouch_select;	/* ワンタッチで編集するSW(十の位)を選択した */
	UBYTE	ten_key_select;		/* テンキーで編集するSW(一の位)を選択した */
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/22 */
	UBYTE	key_ck;

	key_ck = 0;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* 2個目以降のSWの編集はガードを解除 */
	if (memory_sw_guard_release == TRUE) {	/* メモリSWの編集のガードが解除されている */
		onetouch_select = TRUE;
		ten_key_select  = TRUE;
	}
	else {	/* 1個目のメモリSWの編集 */
		onetouch_select = FALSE;
		ten_key_select  = FALSE;
	}
#endif

	/* 初期表示 */
	DisplaySoftSwitchSelect();
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while (1) {
		/* 表示処理 */
		DisplaySoftSwitchSelect();
		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:
			/* スイッチを進める */
			OPR_Buf.SoftSwCtrl.SelectSwitch++;
			if (OPR_Buf.SoftSwCtrl.SelectSwitch >= OPR_Buf.SoftSwCtrl.SwitchMax) {
				OPR_Buf.SoftSwCtrl.SelectSwitch = 0;
			}
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* 左右カーソルキーでSWの位置を選択したので編集ガードを解除 */
			onetouch_select = TRUE;
			ten_key_select  = TRUE;
#endif
			break;
		case LEFT_ARROW:
			/* スイッチを戻す */
			if (OPR_Buf.SoftSwCtrl.SelectSwitch == 0) {
				OPR_Buf.SoftSwCtrl.SelectSwitch = OPR_Buf.SoftSwCtrl.SwitchMax;
			}
			OPR_Buf.SoftSwCtrl.SelectSwitch--;
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* 左右カーソルキーでSWの位置を選択したので編集ガードを解除 */
			onetouch_select = TRUE;
			ten_key_select  = TRUE;
#endif
			break;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/22 */
		case NUMBER:	/* 0 - 9 */
			/* ｱﾙﾌｧﾍﾞｯﾄ表示部分を全て数字に変更 */
			if (key_ck == 0) {
				OPR_Buf.SoftSwCtrl.SelectSwitch = (UBYTE)((key - '0') * 10);
				key_ck = 1;
			}
			else {
				/* A7 -> A5 のような動き */
				OPR_Buf.SoftSwCtrl.SelectSwitch
				 = (UBYTE)((OPR_Buf.SoftSwCtrl.SelectSwitch / 10) * 10 + (UBYTE)(key - '0'));
				key_ck = 0;
			}
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* テンキーのガードを解除します */
			ten_key_select  = TRUE;
#endif
			break;
#else
		case ONETOUCH: /* 0 - 90 */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			if (key <= ONETOUCH_10_KEY) {	/* 01 - 10 */
				/* A9 -> C0の様な選択を行う */
				OPR_Buf.SoftSwCtrl.SelectSwitch = (UBYTE)((key - 'A') * 10);
 #if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* ワンタッチのガードを解除します */
				onetouch_select = TRUE;
 #endif
			}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if (key <= ONETOUCH_J_KEY) {	/* A - J */
				/* A9 -> C0の様な選択を行う */
				OPR_Buf.SoftSwCtrl.SelectSwitch = (UBYTE)((key - 'A') * 10);
 #if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* ワンタッチのガードを解除します */
				onetouch_select = TRUE;
 #endif
			}
#endif
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:	/* 0 - 9 */
			/* A7 -> A5 のような動き */
			OPR_Buf.SoftSwCtrl.SelectSwitch
			 = (UBYTE)((OPR_Buf.SoftSwCtrl.SelectSwitch / 10) * 10 + (UBYTE)(key - '0'));
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* テンキーのガードを解除します */
			ten_key_select  = TRUE;
#endif
			break;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case ENTER:
#if (PRO_MEMORY_SW_EDIT_GUARD == ENABLE)	/* ワンタッチ/テンキーの両方で選択していないと編集できません */
			if ((onetouch_select == FALSE)
			||  (ten_key_select  == FALSE)) {
				NackBuzzer();
				break;
			}
#endif
			/** 決定 */
			return (OPR_CONTINUE);
		case STOP:
		case KEY_TIME_UP:
			/** 終了 */
			return (OPR_END);
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[スイッチ選択状態の表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
void DisplaySoftSwitchSelect(void)
{
	UBYTE	count;	/*loop*/
	UBYTE	value;

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/22 */
	FunctionDisplayBufferHigh[0] = (UBYTE)(OPR_Buf.SoftSwCtrl.SelectSwitch / 10 + '0');
#else
	FunctionDisplayBufferHigh[0] = (UBYTE)(OPR_Buf.SoftSwCtrl.SelectSwitch / 10 + 'A');
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	FunctionDisplayBufferHigh[1] = (UBYTE)(OPR_Buf.SoftSwCtrl.SelectSwitch % 10 + '0');
	FunctionDisplayBufferHigh[2] = ':';
	value = *(OPR_Buf.SoftSwCtrl.SetParameter + OPR_Buf.SoftSwCtrl.SelectSwitch);
	for (count = 0; count < 8; count++) {
		if (value & (0x80 >> count)) {
			FunctionDisplayBufferHigh[count + 10] = '1';
		}
		else {
			FunctionDisplayBufferHigh[count + 10] = '0';
		}
	}
	ClearDisplayHigh();
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

/*************************************************************************
	module		:[パラメータのクリア（初期化）を行う]
	function	:[
		1.マシーンパラメータ・メモリースイッチのクリアを行う
	]
	return		:[]
	common		:[OPR_Buf.SoftSwCtrl]
	condition	:[]
	comment		:[

		<<修正履歴>>
			1:消去確認時のワーディングを「Check Program/Clear」から
			　「Check  Program/Enter」に変更。　1996/08/30
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
void ClearSoftSwitch(UBYTE mode)
{
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/12 */
	UBYTE	temp;
#endif

	/* 上段表示文字列->「Clear Memory Switch      」*/
	/* これは「Set Memory Switch    」の次に定義されているﾜｰﾃﾞｨﾝｸﾞである */

	if (ConfirmKeyInputOperation(OPR_Buf.SoftSwCtrl.ItemWording + OPR_WORDING_LEN,
								 D2W_CheckProgramEnter,								/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {
		switch (mode) {
		case MACHINE_PARAMETER_MODE:
			CMN_InitializeMachineParameter();	/* 機器ﾊﾟﾗﾒｰﾀの初期化 */
			break;
		case MEMORY_SWITCH_MODE:
			CMN_InitializeMemorySwitch();		/* ﾒﾓﾘｽｲｯﾁの初期化 */
			break;
		case UNIQ_SWITCH_MODE:			/* 機種固有スイッチの初期化 1996/03/06 */

#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/12 */
			temp = CHK_UNI_MultiT30Monitor();
#endif

			CMN_InitializeUniqSwitch();

#if defined(POPLAR_F)
#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/12 */
			if (CHK_UNI_MultiT30Monitor() != temp) {
				InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
				InitializeMachineStatus();									/** マシーンステータスのクリア	*/
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
				SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
				Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
  #if defined(KEISATSU) /* スクランブルBITが落ちてしまう件 O.Oshima 2005/12/06 */
				InitializeSensor();											/** センサーを初期化			*/
  #endif
			}
 #endif
#endif
			break;
		case MAINTENANCE_SWITCH_MODE:	/* 保守用スイッチの初期化 1996/03/06 */
			CMN_InitMaintenanceSwitch();
		}
		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[ソフトディツプ入力]
	function	:[
		1.メモリースイッチ、マシンパラメーターの編集を行う
	]
	return		:[入力結果	NG=入力中止	OK=入力ＯＫ]
	common		:[
		SoftSwCtrl:
	]
	condition	:[]
	comment		:[Ｈ８から移植]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口]
*************************************************************************/
UBYTE SoftDipInput(void)
{
	UBYTE	key;		/* 入力キーデータ*/
	UBYTE	keytype;

	while (1) {
		DisplayFixedNumberInput();

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			if (key <= TEN_1_KEY)
				FixedNumberDataSet(key);
			else
				NackBuzzer();
			break;
		case STOP:			/* ストップキー　	  */
		case KEY_TIME_UP:/* １分間キー入力なし */
			CursorOff();
			return (NG);
		case ENTER:	/* セットキー */
			CursorOff();
			return (OK);
		case FUNCTION:	/* カーソルー＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: /* カーソル＜ー　キー */
			CursorLeftRotation();
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ソフトディップ入力の初期データセット]
	function	:[
		1.メモリスイッチ・マシンパラメーターの編集用の初期データをセット。
		2.OPR_Buf.SoftSwCtrlに入力されたデータを文字入力用のバッファ、
		　に編集できる形にしてセットする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/25]
	author		:[江口]
*************************************************************************/
void SoftDipInputInitial(void)
{
	/* OPR_Buf.SoftSwCtrlのデータを文字入力用のバッファにセットする */
	ClearCharacterInput();					/* 作業用バッファをクリア */
	CharacterInput.LcdDisplayPosition = 12;	/* 表示開始位置をセット */
	CharacterInput.WritePosition 	  = 7; 	/* 編集後端位置をセット */
	/* 初期値を編集用に文字列形式に変換 */
	StoreSoftDipToCharacterInput(OPR_Buf.SoftSwCtrl.SetParameter[OPR_Buf.SoftSwCtrl.SelectSwitch]);

	/* 表示文字列を作成*/
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/09/22 */
	SubTitleDisplayBuffer[0] = (UBYTE)(OPR_Buf.SoftSwCtrl.SelectSwitch / 10 + '0');
#else
	SubTitleDisplayBuffer[0] = (UBYTE)(OPR_Buf.SoftSwCtrl.SelectSwitch / 10 + 'A');
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	SubTitleDisplayBuffer[1] = (UBYTE)(OPR_Buf.SoftSwCtrl.SelectSwitch % 10 + '0');
	CharacterInput.FixedWordingLow = &SubTitleDisplayBuffer[0];
}

/*************************************************************************
	module		:[バックアップ・ファイルクリアー機能]
	function	:[
		1.ユーザー設定データのクリア
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[PRG -*2

				<<修正履歴>>
					1:消去確認時のワーディングを「Check Program/Clear」から
					　「Check  Program/Enter」に変更。　1996/08/30

				]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
void ClearBackUpFile(void)
{
	UDWORD	long_time;		/* サマータイム用 */
	TIME_DATA_t bcd_time;		/* サマータイム用 */

	CMN_LongTimeToBCD(&bcd_time, SYB_CurrentTime);

	if (ConfirmKeyInputOperation(D2W_SF_BackUpFileClear, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
		/* CMN_InitializeBackUpValue();	@* バックアップＲＡＭの初期化 */
		/* ↑ Comment by Eguchi 1996/10/08  */

		CMN_InitializeAllBackUpRAM(1);	/** バックアップ領域の内ユーザ登録データのみを初期化 1996/10/08 Eguchi */
										/*メモリースイッチ、固有スイッチ、保守スイッチ、機器パラメータはクリアしない */

		/* サマータイムのための処理 1995/12/21 Eguchi */
		if (bcd_time.Year == CurrentTimeInBCD.Year) {
			long_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
			SetSummerTimeStatus(long_time);
		}

#if (PRO_MULTI_LINE == ENABLE)
		/* 下記の関数はDPRAMの初期化が全て完了していることが大前提の関数です。
		** by O.Kimoto 1997/03/05
		*/
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS   |
								  OPT_CHANGED_MEMORY_SWITCH     |
								  OPT_CHANGED_UNI_SWITCH        |
								  OPT_CHANGED_MENTE_SWITCH      |
								  OPT_CHANGED_DRD_TEADCHING_BUF |
								  OPT_CHANGED_MACHINE_PARA);
#endif
#if defined (KEISATSU)		/* 警察FAX DVT_ID7 Added by SMuratec K.W.Q 2005/10/31 */
		SetKeisatsuSettings();
		AttributeTimeoutCheck = 0;
		NCU_HdstShift();
#endif
		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[バックアップ・ファイル・オールクリアー機能]
	function	:[
		1.ユーザー設定データクリア
		　メモリースイッチ初期化
		　機種固有スイッチ初期化
		　マシーンパラメーター初期化
		　マシーンステータス、センサーステータスの初期化
	]
	return		:[なし]
	common		:[
		SYS_MachineStatus:
	]
	condition	:[]
	comment		:[PRG-*3
				  桐・椛にあわせてマシーンステータスのクリア・センサーのクリアを実行。
				　またどんな状態でもラムクリアできるように変更 1995/12/05

				<<修正履歴>>
					1:消去確認時のワーディングを「Check Program/Clear」から
					　「Check  Program/Enter」に変更。　1996/08/30
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
void ClearAllBackUpFile(void)
{
	UDWORD	long_time;		/* サマータイム用 */
	TIME_DATA_t bcd_time;	/* サマータイム用 */

#if defined(POPLAR_F)	/* 2000/03/01 Y.Murata */
	/* パワーＯＮ時のウォームアップ中は、キー操作禁止 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON) {
		NackBuzzer();
		return;
	}
#endif

#if (PRO_FBS == ENABLE)
	if ((SYB_ScannerTransportMode == TRUE)
	 && (SYS_MachineStatus[SYS_RESOURCE_STATUS] | SYS_SCANNER_BUSY)) { /* 輸送モードの時はＲＡＭオールクリアはじく */
		NackBuzzer();
		return;
	}
#endif

	CMN_LongTimeToBCD(&bcd_time, SYB_CurrentTime); /* サマータイム用 1995/12/21 Eguchi */

	if (ConfirmKeyInputOperation(D2W_SF_AllClear, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {

#if (0)	/* ANKもKANJIに合わせます by K.Watanabe 1998/12/04 */
//#if (PRO_KEYPANEL == PANEL_HINOKI)
#endif
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & ~SYS_PANEL_BUSY) {	/** 機器動作中 */
			NackBuzzer();
			return;
		}
#if (0)
//#endif
#endif

 #if (PRO_ALLRAMCLR_WO_MCP == ENABLE) /* ALL RAM Clearの際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
		CMN_InitializeAllBackUpRAM(2);	/** 機器パラメータ初期化を除くバックアップ領域全てを初期化 */
 #else
		CMN_InitializeAllBackUpRAM(0);	/** バックアップ領域全てを初期化 */
 #endif
		InitializeMachineStatus();		/** マシーンステータスクリア */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;	/** オペレーション中セット */
		InitializeSensor();				/** センサー初期化 */

		/* サマータイムのための処理 1995/12/21 Eguchi */
		if (bcd_time.Year == CurrentTimeInBCD.Year) {
			long_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
			SetSummerTimeStatus(long_time);
		}
		/* WriteCurrentTime();	@** 登録されたＢＣＤ時刻をＲＴＣに書き込む ->不要なはず */

#if (PRO_MULTI_LINE == ENABLE)
		/* 下記の関数はDPRAMの初期化が全て完了していることが大前提の関数です。
		** by O.Kimoto 1997/03/05
		*/
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS   |
								  OPT_CHANGED_MEMORY_SWITCH     |
								  OPT_CHANGED_UNI_SWITCH        |
								  OPT_CHANGED_MENTE_SWITCH      |
								  OPT_CHANGED_DRD_TEADCHING_BUF |
								  OPT_CHANGED_MACHINE_PARA);
#endif
#if defined (KEISATSU)		/* 警察FAX DVT_ID7 Added by SMuratec K.W.Q 2005/10/31 */
		SetKeisatsuSettings();
		AttributeTimeoutCheck = 0;
		NCU_HdstShift();
#endif

		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[機種固有スイッチモード]
	function	:[
		1.機能+＊+４
		2.機種固有スイッチのセット／クリアを実行
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
void UniqSwitchMode(void)
{
	UBYTE	mode;

	/* データのセット */
	OPR_Buf.SoftSwCtrl.ItemWording  = D2W_SF_UniqSwitchSet;			/* [Set Uniq Switc      ] */
	OPR_Buf.SoftSwCtrl.SetParameter = &SYB_MachineUniqSwitch[0];	/* ﾏｼｰﾝﾊﾟﾗﾒｰﾀ */
	OPR_Buf.SoftSwCtrl.SwitchMax    = SYS_MEMORY_SWITCH_MAX;		/* 最大１００個 */
	OPR_Buf.SoftSwCtrl.SelectSwitch = 0;							/* 初期値０（Ａ０）SATSUKI2では（００）*/

	/* 編集するかクリアするか選択させる */
	mode = SelectSetClearMode();

	if (mode == PARAMETER_SET) {		/* 編集の場合 */
		SetSoftSwitch();
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_UNI_SWITCH);

		/* 表示を１にするため追加（マルチ表示用） */
		if (CHK_UNI_MultiDisplayTime() == 0) {
			OPR_MultiDisplayFlag = 0;
		}
#endif
	}
	else if (mode == PARAMETER_CLEAR) {	/* クリアの場合 */
		ClearSoftSwitch(UNIQ_SWITCH_MODE);
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_UNI_SWITCH);

		/* 表示を１にするため追加（マルチ表示用） */
		if (CHK_UNI_MultiDisplayTime() == 0) {
			OPR_MultiDisplayFlag = 0;
		}
#endif
	}
	else {								/* 終了OPR_END */
		return;
	}
}

/*************************************************************************
	module		:[T30モニター・プリント機能]
	function	:[
		1.T30モニター・プリントの機能を実行する。
	]
	return		:[なし]
	common		:[
		FaxComPerformingFlag
		SYB_T30Monitor
	]
	condition	:[]
	comment		:[PRG-*5]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
void T30MonitorPrintOperation(void)
{
	UBYTE	print_ok;	/* 1:T30モニタープリントする。0:T30モニタープリントしない*/

	print_ok = FALSE;

	if (CheckPrintOperationEnable() == FALSE) {	/* プリント不可能 */
		return;
	}

#if defined(POPLAR_F)
	DisplayStringHigh(0, D2W_SF_T30MonitorPrint);

	/* Ｔ３０モニター番号入力 */
	if (CHK_UNI_MultiT30Monitor()) {
		if (NumberInput(OPR_T30_MONITOR_NUMBER_INPUT) == OK) {
			if (CheckCharacterInputEmpty() == TRUE) { /** 未入力 */
				LST_T30ConfNumber = 0xFF;
			}
			else {
				LST_T30ConfNumber = (UBYTE)CharacterInputToNumber();
				if (SYB_T30MonitorDRAM_Status[LST_T30ConfNumber] != 1) {
					NackBuzzer();
					return;
				}
			}
		}
		else {
			return;
		}
	}
	else {
		LST_T30ConfNumber = 0xFF;
	}

#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
	if (CHK_UNI_MultiT30Monitor()) {
		DisplayStringHigh(0, D2W_SF_T30MonitorPrint);

		/* Ｔ３０モニター番号入力 */
		if (NumberInput(OPR_T30_MONITOR_NUMBER_INPUT) == OK) {
			if (CheckCharacterInputEmpty() == TRUE) { /** 未入力 */
				LST_T30ConfNumber = 0xFF;
			}
			else {
				LST_T30ConfNumber = (UBYTE)CharacterInputToNumber();
			}
		}
		else {
			return;
		}
	}
 #endif
#endif

	/*----------------------------------------*/
	/* Ｔ３０モニタがプリント可能かのチェック */
	/*----------------------------------------*/
#if (PRO_MULTI_LINE == DISABLE)
 #if (0) /* 1996/07/04 Eguchi */
 //		/* SYB_T30Monitor.ReadPointerを更新している所はどこにもないため、条件変更 */
 //	if ((FaxComPerformingFlag == YES || SYB_T30Monitor.JournalType != SYS_T30_EMPTY)
 //	&&	(SYB_T30Monitor.ReadPointer != SYB_T30Monitor.WritePointer)) {
 //		/* 通信中またはT30データが存在し、かつ書き込み位置と読み出し位置が異なる。（書いていないデータがある） */
 //		print_ok = TRUE;
 //	}
 #endif
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/09 */
	if (CHK_UNI_MultiT30Monitor() && LST_T30ConfNumber != 0xFF) {
		if (((SYS_T30Monitor + LST_T30ConfNumber)->JournalType != SYS_T30_EMPTY)
		 && ((SYS_T30Monitor + LST_T30ConfNumber)->WritePointer != 0)) {
			/* 通信中またはT30データが存在し、かつ書き込み位置と読み出し位置が異なる。（書いていないデータがある） */
			print_ok = TRUE;
		}
	}
	else {
		if ((FaxComPerformingFlag == YES || SYB_T30Monitor.JournalType != SYS_T30_EMPTY)
		 && (SYB_T30Monitor.WritePointer != 0)) {
			/* 通信中またはT30データが存在し、かつ書き込み位置と読み出し位置が異なる。（書いていないデータがある） */
			print_ok = TRUE;
		}
	}
 #else
	if ((FaxComPerformingFlag == YES || SYB_T30Monitor.JournalType != SYS_T30_EMPTY)
	 && (SYB_T30Monitor.WritePointer != 0)) {
		/* 通信中またはT30データが存在し、かつ書き込み位置と読み出し位置が異なる。（書いていないデータがある） */
		print_ok = TRUE;
	}
 #endif
#else
	/* 手でプリントする時のOPRの起動では割り込み禁止いらない */
	if (CHK_GetT30Sign() != 0xFF) {
		print_ok = TRUE;
	}
#endif	/* (PRO_MULTI_LINE == DISABLE) */

	/*----------------------------*/
	/* メモリダンプ要求のチェック */
	/*----------------------------*/
	if (!print_ok) {	/* Ｔ３０モニタをプリントしない時 */
		if ((SYB_MaintenanceSwitch[MNT_SW_A7] & MEM_INDEX_FAT_DUMP)
		 || (SYB_MaintenanceSwitch[MNT_SW_A7] & ITORON_MEMORY_DUMP)) {
			/* メモリーダンプ要求がある。或いはモニター情報（スタックのダンプ）プリント要求がある */
			print_ok = TRUE;
		}
	}

	if (print_ok) {	/* Ｔ３０モニタか、メモリダンプをプリントする時 */
		FinalListPrintOperation(LST_T30MONITOR);
	}
	else {
		NackBuzzer();
#if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/20 */
		if (CHK_UNI_MultiT30Monitor()) {
			OPR_ChildErrorFlag = NO_COMMAND_RESULT_ERROR;	/* "ﾂｳｼﾝｹｯｶ ｱﾘﾏｾﾝ       " */
		}
#endif
	}
}

#if (PRO_PRINT_TYPE == LED)	/* 1997/07/10 Y.Matsukuma */
/*************************************************************************
	module		:[プリンタメンテナンスオペレーション]
	function	:[
		1.交換カウンタセットオペレーションとサービスコールオペレーションの選択を行う
		2.機能キーで交換カウンタセットオペレーションとサービスコールオペレーションを切り替え。
		3.セットキーでオペレーションの種類を選択して各オペレーションに分岐
		4.ストップキー又はキー待ちタイムオーバーで終了
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/09]
	author		:[桑原美紀]
*************************************************************************/
void PrintMaintenance(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	type;		/* 0:交換ｶｳﾝﾀｾｯﾄ 1:ｻｰﾋﾞｽｺｰﾙ */
	UBYTE	ret;

	type = 0;
	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);				/* "            ｷﾉｳ/ｾｯﾄ " */

	while (1) {
		/* 上段表示 */
		/* "ｺｳｶﾝ ｶｳﾝﾀ ｾｯﾄ        " */
		/* "ｻｰﾋﾞｽｺｰﾙ             " */
		CMN_StringCopy(FunctionDisplayBufferHigh, (D2W_SF_ReplaceCountSet + (OPR_WORDING_LEN * type)));
		DisplayStringHigh(0, FunctionDisplayBufferHigh);

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			type ^= 0x01;
			break;
		case STOP:			/* 停止キー */
		case KEY_TIME_UP:
			return;
		case ENTER:			/* セットキー */
			/* 処理実行 */
			if (type == 0) {
				ReplaceCountSetOperation();		/* 交換カウンタセット */
			}
			else {
				ServiceCallOperation();			/* サービスコール */
			}
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[交換カウンタセットオペレーション]
	function	:[
		1.定着機交換オペレーションと転写ローラー交換オペレーションの選択を行う
		2.機能キーで定着機交換オペレーションと転写ローラー交換オペレーションを切り替え。
		3.セットキーでオペレーションの種類を選択して各オペレーションに分岐
		4.ストップキー又はキー待ちタイムオーバーで終了
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/09]
	author		:[桑原美紀]
*************************************************************************/
void ReplaceCountSetOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	type;		/* 0:ﾃｲﾁｬｸｷ ｺｳｶﾝ 1:ﾃﾝｼｬﾛｰﾗｰ ｺｳｶﾝ */

	type = 0;

	while (1) {
		/* 上段表示 */
		/* "ﾃｲﾁｬｸｷ ｺｳｶﾝ          " */
		/* "ﾃﾝｼｬﾛｰﾗｰ ｺｳｶﾝ        " */
		CMN_StringCopy(FunctionDisplayBufferHigh, (D2W_SF_FuserReplace + (OPR_WORDING_LEN * type)));
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		/* 下段点滅表示 */
		FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			type ^= 0x01;
			break;
		case STOP:			/* 停止キー */
		case KEY_TIME_UP:
			return;
		case ENTER:			/* セットキー */
			/* 処理実行 */
			if (type == 0) {	/* 定着機交換 */
				if (ConfirmKeyInputOperation(D2W_SF_FuserReplace,		/* "ﾃｲﾁｬｸｷ ｺｳｶﾝ         " */
											 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
											 ENTER,
											 FUNCTION) == CONFIRM_EXEC) {
					SYB_PrinterLifeMonitor.FuserReplaceCount++;
					SYB_PrinterLifeMonitor.FuserLifeCount = 0;
					ChildDisplaySetCompleted(D2W_SF_FuserReplace);		/* "ﾃｲﾁｬｸｷ ｺｳｶﾝ         " */
				}
			}
			else {				/* 転写ローラー交換 */
				if (ConfirmKeyInputOperation(D2W_SF_TransferReplace,	/* "ﾃﾝｼｬﾛｰﾗｰ ｺｳｶﾝ       " */
											 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
											 ENTER,
											 FUNCTION) == CONFIRM_EXEC) {
					SYB_PrinterLifeMonitor.TransferReplaceCount++;
					SYB_PrinterLifeMonitor.TransferLifeCount = 0;
					ChildDisplaySetCompleted(D2W_SF_TransferReplace);	/* "ﾃﾝｼｬﾛｰﾗｰ ｺｳｶﾝ       " */
				}
			}
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[サービスコールオペレーション]
	function	:[
		1.エラー数を取得し表示
		2.機能キーで以下のエラー表示が行われる。
			"ﾋｰﾀｰ ｴﾗｰ            "	0x0001
			"ｻｰﾐｽﾀ ﾀﾞﾝｾﾝ         "	0x0002
			"ｻｰﾐｽﾀ ﾀﾝﾗｸ          "	0x0004
			"ｷﾅｲ ﾌｧﾝ ｴﾗｰ         "	0x0008
			"Rxﾓｰﾀｰ ｴﾗｰ          "	0x0010
			"ﾄﾞﾗﾑﾋｭｰｽﾞ ｴﾗｰ       "	0x0020
			"ﾃﾞﾝｹﾞﾝ ﾌｧﾝ ｴﾗｰ      "	0x0040
			"ｺｳｱﾂ ﾋｭｰｽﾞ ﾀﾞﾝｾﾝ    "	0x0080
		3.ストップキー又はキー待ちタイムオーバーで終了
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/09]
	author		:[桑原美紀]
*************************************************************************/
void ServiceCallOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	count;		/* エラー数 */
	UBYTE	pos;		/* 参照場所 */
	UBYTE	i;			/* ﾙｰﾌﾟ */

	pos		= 0;
	SearchServiceCallRight( &pos );
	while (1) {
	count	= 0;
		/* エラー件数取得 */
		for( i = 0; i < OPR_LIFE_ERROR_MAX; i++ ){
			if(((SYB_PrinterLifeMonitor.ErrorStatus >> i) & 0x0001) != 0x0000 ){
				count++;
			}
		}
		/* 上段表示 */
		CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_ServiceCallCount);
		FunctionDisplayBufferHigh[18] = ChangeNumberToASC_Code((UBYTE)count);
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		if( count != 0 ){
			CMN_StringCopy(FunctionDisplayBufferLow, (D2W_SF_HeatTrouble + (OPR_WORDING_LEN * pos)));
		}
		DisplayStringLow(0, FunctionDisplayBufferLow);

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
			SearchServiceCallRight( &pos );
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			SearchServiceCallLeft( &pos );
			break;
		case STOP:			/* 停止キー */
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[サービスコール検索（右矢印）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/09]
	author		:[桑原美紀]
*************************************************************************/
void 	SearchServiceCallRight(
				UBYTE	*Pos)
{
	UBYTE	i;
	UBYTE	position;

	position	= *Pos;
	for( i = 0; i < OPR_LIFE_ERROR_MAX; i++ ){
		if( position+1 >= OPR_LIFE_ERROR_MAX ){
			position	= 0;
		}
		else{
			position++;
		}
		if(((SYB_PrinterLifeMonitor.ErrorStatus >> position) & 0x0001) != 0x0000){
			break;
		}
	}
	*Pos	= position;
}

/*************************************************************************
	module		:[サービスコール検索（左矢印）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/09]
	author		:[桑原美紀]
*************************************************************************/
void 	SearchServiceCallLeft(
				UBYTE	*Pos)
{
	UBYTE	i;
	UBYTE	position;

	position	= *Pos;
	for( i = 0; i < OPR_LIFE_ERROR_MAX; i++ ){
		if( position == 0 ){
			position	= OPR_LIFE_ERROR_MAX - 1;
		}
		else{
			position--;
		}
		if(((SYB_PrinterLifeMonitor.ErrorStatus >> position) & 0x0001) != 0x0000){
			break;
		}
	}
	*Pos	= position;
}
#endif /* (PRO_PRINT_TYPE == LED) END */

/*************************************************************************
	module		:[ファンクションリスト・コール]
	function	:[
		1.機能リストの印字を行う
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[PRG-*8]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
void FunctionListPrintOperation(void)
{
	FinalListPrintOperation(LST_FUNCTION_LIST);
}

/*************************************************************************
	module		:[サービス・ファンクション（テストファンクション）]
	function	:[
		1.サービス・ファンクションの中のテストファンクションの項目の機能を実行する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-*9]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
void ServiceFunctionSetting(void)
{
	BYTE	fnc_number;
	UBYTE	keytype;

	/* 初期表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */
	fnc_number = 0;

	while (keytype != ENTER) {
		/** 表示処理 */
		DisplayStringHigh(0, D2W_SF_LifeMonitor + (OPR_WORDING_LEN * fnc_number));

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();

		switch (keytype) { /**取り込んだキーに対する処理 */

		case STOP:
			/** 終了 */
			return;

		case FUNCTION: /* ＞　キー*/
			/** 項目を進める */
			fnc_number++;
#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
			if (fnc_number == 2) { /* 済スタンプはない */
				fnc_number = 3;
			}
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI)
			/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
			if (fnc_number > 3) { /*進めすぎた場合もとに戻す*/
				fnc_number = 0;
			}
#elif (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			/* (F250には済みスタンプと原稿排出テストはありません。) by SMuratec L.Z.W 2003/11/11 */
  #if (1)	/* ファンクションＮｏの変更 by Y.Kano 2003/12/26 */
			if (fnc_number > 3) { /*進めすぎた場合もとに戻す*/
  #else
**			if (fnc_number > 2) { /*進めすぎた場合もとに戻す*/
  #endif
				fnc_number = 0;
			}
#else
			if (fnc_number > 4) { /*進めすぎた場合もとに戻す*/
				fnc_number = 0;
			}
#endif

			break;
		case LEFT_ARROW:/* ＜　キー */
			/** 項目を戻す */
			fnc_number--;
#if defined (KEISATSU) /* 警察FAX 05/10/05 石橋正和 */
			if (fnc_number == 2) { /* 済スタンプはない */
				fnc_number = 1;
			}
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)
			/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
			if (fnc_number < 0) {
				fnc_number = 3;
			}
#elif (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			/* (F250には済みスタンプと原稿排出テストはありません。) by SMuratec L.Z.W 2003/11/11 */
			if (fnc_number < 0) {
  #if (1)			/* ファンクションＮｏの変更 by Y.Kano 2003/12/26 */
				fnc_number = 3;
  #else
**				fnc_number = 2;
  #endif
			}
#else
			if (fnc_number < 0) {
				fnc_number = 4;
			}
#endif
			break;
		case ENTER:
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}

#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) /* || (PRO_KEYPANEL == PANEL_HINOKI) ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
	switch (fnc_number) {
	case 0:		/* ライフモニター */
		SF_InnerStatusOperation();
		break;
	case 1:		/* テストパターンプリント */
		SF_TestPatternOperation();
		break;
	case 2:		/* スタンプテスト */
		SF_StampTest();
		break;
	case 3:		/* 原稿排出テスト */
		SF_DocumentFeedOutTest();
		break;
	case 4:		/* シェーディング取り込み */
		SF_ShadingOperation();
		break;
	default:
		NackBuzzer();
		break;
	}
#elif (PRO_KEYPANEL == PANEL_HINOKI) 
	/* ＨＩＮＯＫＩは原稿排出テストは有りません by O.Kimoto 1999/02/09 */
	switch (fnc_number) {
	case 0:		/* ライフモニター */
		SF_InnerStatusOperation();
		break;
	case 1:		/* テストパターンプリント */
		SF_TestPatternOperation();
		break;
	case 2:		/* スタンプテスト */
		SF_StampTest();
		break;
	case 3:		/* シェーディング取り込み */
		SF_ShadingOperation();
		break;
	default:
		NackBuzzer();
		break;
	}
#elif (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	/* (F250には済みスタンプと原稿排出テストはありません。) by SMuratec L.Z.W 2003/11/11 */
	switch (fnc_number) {
	case 0:		/* ライフモニター */
		SF_InnerStatusOperation();
		break;
	case 1:		/* テストパターンプリント */
		SF_TestPatternOperation();
		break;
	case 2:		/* PS1,PB4スレッショルド設定  by Y.kano 2003/12/26 */
		SF_PS1_PB4_ThresholdSet();
		break;
	case 3:		/* シェーディング取り込み */
		SF_ShadingOperation();
		break;
	default:
		NackBuzzer();
		break;
	}
#else
	switch (fnc_number) {
	case 0: /* ライフモニター */
		SF_InnerStatusOperation();
		break;
	case 1: /* ライフモニタークリア */
		SF_LifeMonitorClear();
		break;
	case 2: /* テストパターンプリント */
		SF_TestPatternOperation();
		break;
	case 3: /* スタンプテスト */
		SF_StampTest();
		break;
	case 4: /* シェーディング取り込み */
		SF_ShadingOperation();
		break;
	default:
		NackBuzzer();
		break;
	}
#endif
}

/*************************************************************************
	module		:[テストファンクション。ライフモニター]
	function	:[
		1.機器内部状態の表示を行う。
		,　Ａ：ＲＯＭバージョン
		,　Ｂ：読みとり枚数
		,　Ｃ：印字枚数
		,　Ｄ：送信枚数
		,　Ｅ：ドラム交換回数			←　杏より追加　1996/06/25　Eguchi
		,　Ｆ：ドラム寿命カウンタ		←　杏より追加　1996/06/25　Eguchi
		,　Ｇ：トナー交換回数			←　ポプラより追加　1997/05/28　by K.Watanabe
		,　Ｈ：トナー寿命カウンタ		←　ポプラより追加　1997/05/28　by K.Watanabe
		,　Ｉ：定着機交換回数			←　ポプラより追加　1997/05/28　by K.Watanabe
		,　Ｊ：定着機寿命カウンタ		←　ポプラより追加　1997/05/28　by K.Watanabe
		,　Ｋ：転写ローラー交換回数		←　ポプラより追加　1997/05/28　by K.Watanabe
		,　Ｌ：転写ローラー寿命カウンタ	←　ポプラより追加　1997/05/28　by K.Watanabe
	]
	return		:[]
	common		:[SYB_LifeMonitor]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/07]
	author		:[松隈,江口,渡辺一章]
*************************************************************************/
void SF_InnerStatusOperation(void)
{
	UBYTE	i;
	UBYTE	key;
	UBYTE	keytype;
	UDWORD	data;	/* UWORD -> UDWORD By M.Tachibana 1997/12/09 */
#if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/01/06 */
	TIME_DATA_t	install_time;
#endif

	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

	DisplayStringHigh(0, D2W_SF_LifeMonitor);
	ClearDisplayLow(); /* 1996/02/28 Eguchi */

	while( 1 ) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
		case AST:	/** ＣＰＵバージョン */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_CPU_Revision);
			CMN_StringCopy(FunctionDisplayBufferLow, CPU_Revision);
			DisplayStringHigh(0, FunctionDisplayBufferHigh);
			DisplayStringLow(0, FunctionDisplayBufferLow);
			break;
		case NUMBER:
			if (key == TEN_0_KEY) {		/** ＲＯＭバージョン */
				CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
				CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
				CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_ROM_Revision);
				CMN_StringCopy(FunctionDisplayBufferLow, ROM_Revision);
				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				DisplayStringLow(0, FunctionDisplayBufferLow);
			}
			else {
				NackBuzzer();
			}
			break;
#endif
		case ONETOUCH:
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			if (key == ONETOUCH_01_KEY) {	/** ロムバージョン表示 */
				DisplayStringHigh(0, D2W_SF_BoardNumber);
				ClearDisplayLow();

				while (1) {
					OPR_GetKey(KEY_WAIT_ONE_MINUTE);
					key = GetInputKeyCode();
					CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
					FunctionDisplayBufferLow[0] = key;
					FunctionDisplayBufferLow[1] = ':';
					if (key == STOP_KEY) {
						DisplayStringHigh(0, D2W_SF_LifeMonitor);
						ClearDisplayLow();
						break;
					}
					else if (key == TEN_AST_KEY) {
						CMN_StringCopy(&FunctionDisplayBufferLow[2], CPU_Revision);
						DisplayStringLow(0, FunctionDisplayBufferLow);
					}
					else if (key == TEN_0_KEY) {
						CMN_StringCopy(&FunctionDisplayBufferLow[2], ROM_Revision);
						DisplayStringLow(0, FunctionDisplayBufferLow);
					}
					else if ((key >= TEN_1_KEY) && (key <= TEN_8_KEY)) {
						if (SYB_OptionROM_Revision[(UBYTE)(key - TEN_0_KEY)][0] != NULL) {
							/* SYB_OptionROM_RevisionがWORDの変数のために、CMN_StringCopy()が使用出来ないので、
							** わざとforループでコピーします
							** 注）WORDの変数のポインターをBYTEのポインターにキャストする時に、WORDの変数が
							** 　　奇数番地に割り当てられていると、リセットがかかってしまうので、キャストは出来ません
							*/
							/*CMN_StringCopy(&FunctionDisplayBufferLow[2], &SYB_OptionROM_Revision[(UBYTE)(key - 0x30)]);*/
							for (i = 0; i < OPTION_ROM_REVISION_WORD_MAX; i++) {
#if (0)	/* By M.Tachibana 1997/07/07 */
								FunctionDisplayBufferLow[i + 2] = (UBYTE)SYB_OptionROM_Revision[(UBYTE)(key - 0x30)][i];
#endif
								FunctionDisplayBufferLow[i * 2 + 2] = (UBYTE)(SYB_OptionROM_Revision[(UBYTE)(key - 0x30)][i] >> 8);
								FunctionDisplayBufferLow[i * 2 + 3] = (UBYTE)SYB_OptionROM_Revision[(UBYTE)(key - 0x30)][i];
							}
							DisplayStringLow(0, FunctionDisplayBufferLow);
						}
						else {
							NackBuzzer();
						}
					}
					/* 拡張ＲＯＭバージョン表示追加 by K.Watanabe 1998/02/27 */
					else if ((key >= ONETOUCH_01_KEY) && (key <= (ONETOUCH_01_KEY + (SYS_EXT_ROM_MAX - 1)))) {
						if (SYB_ExtRomRevision[(UBYTE)(key - ONETOUCH_01_KEY)][0] != NULL) {
							CMN_StringCopy(&FunctionDisplayBufferLow[2],
										   SYB_ExtRomRevision[(UBYTE)(key - ONETOUCH_01_KEY)]);
							DisplayStringLow(0, FunctionDisplayBufferLow);
						}
						else {
							NackBuzzer();
						}
					}
					else {
						NackBuzzer();
					}
				}
			}
			else if (ONETOUCH_02_KEY <= key && key <= ONETOUCH_12_KEY) {
				switch (key) {
				case ONETOUCH_02_KEY:	/** 読み取り枚数 */
					data = SYB_LifeMonitor.ScanCount;
					break;
				case ONETOUCH_03_KEY:	/** トータル印字枚数 */
					data = SYB_LifeMonitor.PrintCount;
					break;
				case ONETOUCH_04_KEY:	/** 送信枚数 */
					data = SYB_LifeMonitor.TransmitCount;
					break;
				case ONETOUCH_05_KEY:	/** ドラム交換回数 */
					data = (UDWORD)SYB_PrinterLifeMonitor.DrumReplaceCount;
					break;
				case ONETOUCH_06_KEY:	/** ドラム寿命カウンター */
					data = SYB_PrinterLifeMonitor.DrumLifeCount;
					break;
				case ONETOUCH_07_KEY:	/** トナー交換回数 */
					data = (UDWORD)SYB_PrinterLifeMonitor.TonerReplaceCount;
					break;
				case ONETOUCH_08_KEY:	/** トナー寿命カウンター */
					data = (UDWORD)SYB_PrinterLifeMonitor.TonerLifeCount;
					break;
				case ONETOUCH_09_KEY:	/** 定着機交換回数 */
					data = (UDWORD)SYB_PrinterLifeMonitor.FuserReplaceCount;
					break;
				case ONETOUCH_10_KEY:	/** 定着機寿命カウンター */
					data = SYB_PrinterLifeMonitor.FuserLifeCount;
					break;
				case ONETOUCH_11_KEY:	/** 転写ローラー交換回数 */
					data = (UDWORD)SYB_PrinterLifeMonitor.TransferReplaceCount;
					break;
				case ONETOUCH_12_KEY:	/** 転写ローラー寿命カウンター */
					data = SYB_PrinterLifeMonitor.TransferLifeCount;
					break;
				default:
					break;
				}
				CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
				CMN_UnsignedLongToASC(FunctionDisplayBufferLow, data, 6, '0');	/* Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */

				DisplayStringHigh(0, D2W_SF_LifeReadingPage + OPR_WORDING_LEN * (UBYTE)(key - ONETOUCH_02_KEY));
				DisplayStringLow(0, FunctionDisplayBufferLow);
			}
			else {
				NackBuzzer();
			}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
			if (ONETOUCH_01_KEY <= key && key <= ONETOUCH_06_KEY) {
				CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
				CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
				switch (key) {
				case ONETOUCH_01_KEY:	/** ＲＯＭバージョン */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_ROM_Revision);
					CMN_StringCopy(FunctionDisplayBufferLow, ROM_Revision);
					break;
 #if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/01/06 */
				case ONETOUCH_02_KEY:	/** シリアル番号 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_SerialNumber);
					CMN_StringCopy(FunctionDisplayBufferLow, SYB_ConsumerOrder.SerialNumber);
					break;
				case ONETOUCH_03_KEY:	/** 設置日 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_Date);
					CMN_LongTimeToBCD((TIME_DATA_t *)&install_time, SYB_ConsumerOrder.InstallDate);
					FunctionDisplayBufferLow[0] = '\'';
					FunctionDisplayBufferLow[1] = (UBYTE)(((install_time.Year & 0xF0) >> 4) + 0x30);
					FunctionDisplayBufferLow[2] = (UBYTE)((install_time.Year & 0x0F) + 0x30);
					FunctionDisplayBufferLow[3] = ' ';
					FunctionDisplayBufferLow[4] = (UBYTE)(((install_time.Month & 0xF0) >> 4) + 0x30);
					FunctionDisplayBufferLow[5] = (UBYTE)((install_time.Month & 0x0F) + 0x30);
					FunctionDisplayBufferLow[6] = '/';
					FunctionDisplayBufferLow[7] = (UBYTE)(((install_time.Date & 0xF0) >> 4) + 0x30);
					FunctionDisplayBufferLow[8] = (UBYTE)((install_time.Date & 0x0F) + 0x30);
					break;
				case ONETOUCH_04_KEY:	/** 読み取り枚数 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_LifeReadingPage);	/* "ﾖﾐﾄﾘ ﾏｲｽｳ           " */
					CMN_UnsignedLongToASC(FunctionDisplayBufferLow, SYB_LifeMonitor.ScanCount, 6, '0');
					break;
				case ONETOUCH_05_KEY:	/** トータル印字枚数 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_LifePrintingPage);	/* "ｲﾝｼﾞ ﾏｲｽｳ           " */
					CMN_UnsignedLongToASC(FunctionDisplayBufferLow, SYB_LifeMonitor.PrintCount, 6, '0');
					break;
				case ONETOUCH_06_KEY:	/** 送信枚数 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_LifeTxPage);		/* "ｿｳｼﾝ ﾏｲｽｳ           " */
					CMN_UnsignedLongToASC(FunctionDisplayBufferLow, SYB_LifeMonitor.TransmitCount, 6, '0');
					break;
 #else
				case ONETOUCH_02_KEY:	/** 読み取り枚数 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_LifeReadingPage);	/* "ﾖﾐﾄﾘ ﾏｲｽｳ           " */
					CMN_UnsignedLongToASC(FunctionDisplayBufferLow, SYB_LifeMonitor.ScanCount, 6, '0');
					break;
				case ONETOUCH_03_KEY:	/** トータル印字枚数 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_LifePrintingPage);	/* "ｲﾝｼﾞ ﾏｲｽｳ           " */
					CMN_UnsignedLongToASC(FunctionDisplayBufferLow, SYB_LifeMonitor.PrintCount, 6, '0');
					break;
				case ONETOUCH_04_KEY:	/** 送信枚数 */
					CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_LifeTxPage);		/* "ｿｳｼﾝ ﾏｲｽｳ           " */
					CMN_UnsignedLongToASC(FunctionDisplayBufferLow, SYB_LifeMonitor.TransmitCount, 6, '0');
					break;
 #endif
				}
				DisplayStringHigh(0, FunctionDisplayBufferHigh);
				DisplayStringLow(0, FunctionDisplayBufferLow);
			}
			else {
				NackBuzzer();
			}
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if (key == ONETOUCH_A_KEY) {	/** ロムバージョン表示 */
 #if (PRO_MULTI_LINE == ENABLE) || (PRO_PC_PRINT == ENABLE)
				DisplayStringHigh(0, D2W_SF_BoardNumber);
				ClearDisplayLow();

				while (1) {
					OPR_GetKey(KEY_WAIT_ONE_MINUTE);
					key = GetInputKeyCode();
					CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
					FunctionDisplayBufferLow[0] = key;
					FunctionDisplayBufferLow[1] = ':';
					if (key == STOP_KEY) {
						DisplayStringHigh(0, D2W_SF_LifeMonitor);
						ClearDisplayLow();
						break;
					}
					switch (key) {
					case TEN_AST_KEY:
						CMN_StringCopy(&FunctionDisplayBufferLow[2], CPU_Revision);
						DisplayStringLow(0, FunctionDisplayBufferLow);
						break;
					case TEN_0_KEY:
						CMN_StringCopy(&FunctionDisplayBufferLow[2], ROM_Revision);
						DisplayStringLow(0, FunctionDisplayBufferLow);
						break;
					case TEN_1_KEY:
					case TEN_2_KEY:
					case TEN_3_KEY:
					case TEN_4_KEY:
					case TEN_5_KEY:
					case TEN_6_KEY:
					case TEN_7_KEY:
					case TEN_8_KEY:
						if (SYB_OptionROM_Revision[(UBYTE)(key - 0x30)][0] != 0) {
							DisplayStringLow(0, FunctionDisplayBufferLow);
							DisplayStringLow(2, SYB_OptionROM_Revision[(UBYTE)(key - 0x30)]);
						}
						else {
							NackBuzzer();
						}
						break;
	#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/08/20 Eguchi */
					case TEN_9_KEY: /*ｲﾝﾀｰﾈｯﾄFAX。ｴﾝｼﾞﾝﾎﾞｰﾄﾞﾌｧｰﾑｳｪｱﾊﾞｰｼﾞｮﾝ表示*/
						if (SYB_INF_DeviceExist == TRUE) {
							DisplayChar(20 , 'S');
							DisplayChar(21 , ':');
							DisplayChar(29 , 'H');
							DisplayChar(30 , ':');
							DisplayStringLow(2 , INF_EngineSystemParam.SW_Rev);
							DisplayStringLow(11 , INF_EngineSystemParam.HW_Rev);
							/* SW_Rev の文字列が7文字を超えたら作り替える*/
							/* HW_Rev の文字列が9文字を超えたら作り替える*/
						}
						else {
							NackBuzzer();
						}
						break;
	#endif
					default:
						NackBuzzer();
						break;
					}
				}
 #else
				DisplayStringHigh(0, ROM_Revision);
				ClearDisplayLow();
 #endif	/* (PRO_MULTI_LINE == ENABLE) || (PRO_PC_PRINT == ENABLE) */
			}
			else if (ONETOUCH_B_KEY <= key && key <= ONETOUCH_F_KEY) {
				switch (key) {
				case ONETOUCH_B_KEY:	/** 読み取り枚数 */
					data = SYB_LifeMonitor.ScanCount;
					break;
				case ONETOUCH_C_KEY:	/** トータル印字枚数 */
					data = SYB_LifeMonitor.PrintCount;
					break;
				case ONETOUCH_D_KEY:	/** 送信枚数 */
					data = SYB_LifeMonitor.TransmitCount;
					break;
				case ONETOUCH_E_KEY:	/** ドラム交換回数 *//* 杏より追加1996/06/25 Eguchi */
					data = SYB_LifeMonitor.DrumReplaceCount;
					break;
				case ONETOUCH_F_KEY:	/** ドラム寿命カウンター *//* 杏より追加1996/06/25 Eguchi */
					data = SYB_LifeMonitor.DrumLifeCount;
					break;
				default:
					break;
				}
				CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
				CMN_UnsignedLongToASC(FunctionDisplayBufferLow, data, 6, '0');	/* Int -> Long : 5 -> 6 By M.Tachibana 1997/12/09 */

				DisplayStringHigh(0, D2W_SF_LifeReadingPage + OPR_WORDING_LEN * (UBYTE)(key - ONETOUCH_B_KEY));
				DisplayStringLow(0, FunctionDisplayBufferLow);
			}
			else {
				NackBuzzer();
			}
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
			break;
		case STOP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[(工場ファンクション)ライフモニタークリア]
	function	:[
		1.ライフモニターデータのクリア
		2.ジャーナル関係のデータのクリア
	]
	return		:[ない]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[96/03/05 ]
	author		:[松隈]
*************************************************************************/
void SF_LifeMonitorClear(void)
{
	ClearDisplayLow();

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
	if (SYB_LifeMonitorPasscode != 0x0000) {
		if (LifeMonitorPasscodeOperation() == NG) {
			NackBuzzer();
			return;
		}
	}
#endif

	/* クリア確認オペレーション */
	if (ConfirmKeyInputOperation(D2W_SF_LifeMonitorClear, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
		CMN_ClearLifeMonitorData();			/** ライフモニタークリア */
#if (PRO_PRINT_TYPE == LED)	/* By M.Tachibana 1997/04/24 */
		CMN_ClearPrinterLifeMonitorData();	/** プリンタライフモニタークリア */
#endif
		CMN_ClearFaxComErrorMonitorData();	/** 通信エラーモニタークリア By M.Tachibana 1997/06/23 */
		CMN_ClearJournalData();				/** ジャーナルデータクリア */
#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/02/10 */
		CMN_ND_EraseAllHistory();	/* ナンバーディスプレイ着信履歴消去 */
#endif
		ChildDisplayStringLow(D2W_ClearComplete);		/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[テストファンクション：パターンプリント]
	function	:[
		1.テストパターンのプリントを実行
		2.キー入力とプリントされるパターンの対応関係
		,	ONETOUCH_A_KEY	-> 格子パターン（チェッカーフラッグ)
		,	ONETOUCH_B_KEY	-> 升目パターン
		,	ONETOUCH_C_KEY	-> ラインパターン	** 97/07/18 Add by M.Kuwahara **
		3.ストップキーが押されるまでプリントし続ける.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口,渡辺一章]
*************************************************************************/
void SF_TestPatternOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	status;
	UBYTE	pattern;
	UBYTE	test_enable_key_max;

	status = 0;
	pattern = ' ';
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	test_enable_key_max = ONETOUCH_03_KEY;	/* 01 - 03 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	test_enable_key_max = ONETOUCH_B_KEY;	/* A - B */
#endif

	if (CheckPrintOperationEnable() == FALSE) {
		return;
	}
	while(1) {
		DisplayPatternPrint(pattern, status);

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2005/03/02/ */
		OPR_GetKey(KEY_WAIT_ONE_SECOND);
#else
		OPR_GetKey(KEY_WAIT_FOREVER);
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ONETOUCH:
			if (key <= test_enable_key_max) {
				if (CheckPrintOperationEnable()) {
					SYS_DocumentPrintItem = LST_PATTERN_PRINT;
					SYS_DocumentPrintNo   = LST_PATTERN1 + CMN_OnetouchCodeToOffset(key);
					OperationMessageToMain.Message = MSG_LIST_PRINT;
					snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
					MainTaskExecWait();
					status = 1;
					pattern = key;
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case STOP:
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) {	/** ﾌﾟﾘﾝﾄ中の時は、印刷停止要求をだす */
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_LIST_PRINT;
				status = 0;
				pattern = ' ';
			}
			else {	/** ﾌﾟﾘﾝﾄ中でない時は、ﾃｽﾄを終える */
				return;
			}
			break;
		case NO_EFFECT:
			break;
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2005/03/02/ */
		case KEY_TIME_UP:
			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT)) {
				status = 0;
				pattern = ' ';
			}
			break;
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[テストパターンプリント中表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口]
*************************************************************************/
void DisplayPatternPrint(UBYTE pattern, UBYTE status)
{
	if (CheckChildErrorDisplayReq() == TRUE) {
		DisplayChildError();
		return;
	}
	if (CheckChildDisplay() == TRUE) {
		return;
	}

	/* 上段表示 [Pattern           A ]*/
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_Pattern);
	FunctionDisplayBufferHigh[18] = pattern;
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* 下段表示 */
	if (status == 0) { /* プリント中でない */
		ClearDisplayLow();
	}
	else { /* プリント中 */
		DisplayStringLow(0 , D2W_Printing);
	}
}

#if (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2)	/* Add by Y.Kano 2003/12/26 */
/*************************************************************************
	module		:[テストファンクション：スタンプテスト]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口]
*************************************************************************/
void SF_StampTest(void)
{
	UBYTE	keytype;

	DisplayStringHigh(0, D2W_SF_StampTest);
	ClearDisplayLow();

	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		keytype = GetInputKeyType();

		switch (keytype) {
		case START:
			if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)	/* 排出中 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			/* 原稿なし状態でスタートキーを押すとループする対策 カバーオープン、原稿なしの時は
			** オペレーションではじきます。2002/11/28 T.Takagi
			 */
			|| (!QueryCloseInterLock4Scan())					/* カバーオープン */
			|| (!QueryDs1On())									/* 原稿なし */
			|| (!QueryDs2On())
#endif
			){
				NackBuzzer();
			}
			else {
				/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 Eguchi */
				OperationMessageToMain.Message = MSG_SERV_STAMP_TEST;
				snd_msg(mbxno.MAN_Task , &OperationMessageToMain);
				MainTaskExecWait();
			}
			break;
		case STOP:
			if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT) {/* 排出中 */
				NackBuzzer();
			}
			else {
				return;
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif

/*************************************************************************
	module		:[テストファンクション：原稿排出テスト]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/27]
	author		:[渡辺一章]
*************************************************************************/
void SF_DocumentFeedOutTest(void)
{
	UBYTE	is_loop_end;

	ClearDisplayLow();

	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		switch (GetInputKeyType()) {
		case START:
			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)	/* 排出中でない時 */
			 && CMN_CheckDocumentOnFeeder()) {	/* ＡＤＦに原稿がセットされている */
				OperationMessageToMain.Message = MSG_SERV_FEED_OUT_DOC;
				snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
				MainTaskExecWait();
			}
			else {															/* 排出中の時 */
				NackBuzzer();
			}
			break;
		case STOP:
			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FEED_OUT)) {	/* 排出中でない時 */
				is_loop_end = TRUE;
			}
			else {															/* 排出中の時 */
				NackBuzzer();
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[(テストファンクション)シェーディングデータ取り込み]
	function	:[
		シェーディングデータの取り込みを行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		POPLAR_B FBS仕様を追加 T.Nose 1997/01/28
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[96/03/13]
	author		:[松隈]
*************************************************************************/
void SF_ShadingOperation(void)
{
/* Added by SMuratec K.W.Q 2003/09/27 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	UBYTE	keytype;
	WORD	SamplePosition;				/* Shading Data をサンプルするライン数 */
	BOOL	PaperFlag;
#endif

	UBYTE is_scanner_error = FALSE;
	UBYTE is_mirror_fix = FALSE;

#if (PRO_FBS == ENABLE)
	if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_BUSY) {	/** ミラーが使用中 */
		NackBuzzer();	/** Nackブザーで終了 */
		return;
	}
#endif

	DisplayStringHigh(0, D2W_SF_Shading);
	ClearDisplayLow();

/* Added by SMuratec K.W.Q 2003/09/27 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	PaperFlag = TRUE;

	if (QueryCloseInterLock4Scan()) {
		if (DOC_POS_SCANNING == QueryDocPosition()) {
			NackBuzzer();	/** Nackブザーで終了 */
			return;
		}
	}
	
/*	DVT: Modify by SMuratec K.W.Q 2004/10/26 */
#if defined(STOCKHM2)
	while(!QueryDs2On()) {
		/** 表示処理 */
		DisplayStringLow(0,D2W_ShadingWord );
		
		OPR_GetKey(20);
		keytype = GetInputKeyType();
		
		if (keytype == STOP){
			PaperFlag = FALSE;
			return;
		}
		else if (keytype == ENTER){
			PaperFlag = FALSE;
			break;
		}
		else{
			PaperFlag = TRUE;
		}
	}
#else
	/* Modify by SMuratec K.W.Q 2003/10/27 */
	if (SYS_CheckerMode == CHECKER_MAIN_TEST){
		if (QueryDs2On()){
			PaperFlag = TRUE;
		}
		else{
			PaperFlag = FALSE;
		}
	}
	else{
		while(!QueryDs2On()) {
			/** 表示処理 */
			DisplayStringLow(0,D2W_ShadingWord );
			
			OPR_GetKey(20);
			keytype = GetInputKeyType();
			
			if (keytype == STOP){
				PaperFlag = FALSE;
				return;
			}
			else if (keytype == ENTER){
				PaperFlag = FALSE;
				break;
			}
			else{
				PaperFlag = TRUE;
			}
		}
	}
#endif
	
	if (PaperFlag){	
		wai_tsk(300); /* 200->300変更 SMuratec K.W.Q 2003/10/22 */
		
		SamplePosition = 0;

		SetupTxMotor(FEEDER_DOC_OUT);
		StartTxMotor();
		
#if (1) /* 変更 by SMuratec K.W.Q 2003/10/22 */
		wai_tsk(120); /* 1cmmくらい進む*/
		StopTxMotor();
#else
		while (1){
			if (QueryCloseInterLock4Scan()) {
				
				if (DOC_POS_SCANNING == QueryDocPosition()) {
					if (++SamplePosition > SAMPLE_LINE_COUNT) {
						StopTxMotor();
						break;
					}
				}
			}			
		}
#endif
	}
	
	DisplayStringHigh(0, D2W_SF_Shading);
	ClearDisplayLow();
#endif

#if (PRO_IMAGE_PROCESSOR ==	IMAGE_PROCESSOR_LC82103)
	if (SYB_MaintenanceSwitch[MNT_SW_C1] & SCN_SHADING_METHOD_SCANDOC) {
		OperationMessageToMain.Item = FROM_OPERATION;
		OperationMessageToMain.Message = MSG_SERV_SHADING_START;
		OperationMessageToMain.SubMessage1 = 0;
		OperationMessageToMain.SubMessage2 = 0;
		snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
		MainTaskExecWait();
	} else {
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/11 T.Takagi */
  #if defined(HINOKI3)		/* 朱色シェーディングデータ取込み後、通常のシェーディング取込みも行っていたので切り分けます。by Y.Kano 2005/01/24 */
		if (CHK_UNI_RedScanModeEnable()) {
			MakeShadingDataForRedScan();
			LampOff();
		}
		else {
			MakeShadingData();
			LampOff();
		}
  #else
		if (CHK_UNI_RedScanModeEnable()) {
			MakeShadingDataForRedScan();
			LampOff();
		}
  #endif
 #endif		
 #if !defined(HINOKI3)
		MakeShadingData();
		LampOff();
 #endif
		ChildDisplaySetCompleted(D2W_SF_Shading);
	}
	
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)		/* Added by SMuratec K.W.Q 2003/09/27 */
	/*	Added by SMuratec K.W.Q	2003/09/26	*/
	if (PaperFlag){
		SetupTxMotor(FEEDER_DOC_OUT);
		StartTxMotor();

		while (1){
		
		/*シェーディング修正*//* Modify by SMuratec K.W.Q 2003/11/10 */
		/* シェーディングで、紙の排出中にカバーを開けて紙を取り出すと、カバーを閉め
			てもモーターが回ったままになり、ループします。*/
		/*	if (QueryCloseInterLock4Scan()) {	*/

			if (DOC_POS_NO_DOCUMENT == QueryDocPosition()
				|| (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
				|| (SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_SCANNER_OPEN)) {
				wai_tsk(10);
				
				StopTxMotor();
				break;
			}
			
		/*	}*/
		}
	}
 #endif


#else
 #if (PRO_FBS == ENABLE)	/* ICHOU用に追加  1996/10/11 s.takeuchi */
	if (SYB_MaintenanceSwitch[MNT_SW_A8] & CURRENT_POSITION_SHADING) {
		is_mirror_fix = TRUE;
	}

	/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件 T.Nose 1997/12/17 */
	DEBUG_OperationExitFlag = 0;		/* シェーディングオペレーション終了フラグリセット */

	while (1) {
		/** MAN_Task()を介して、ミラーキャリッジをADF読み取り位置へ移動させる */
		if (!is_mirror_fix) {
			OperationMessageToMain.Item = FROM_OPERATION;
			OperationMessageToMain.Message = MSG_SERV_SHADING_START;
			OperationMessageToMain.SubMessage1 = 0;
			OperationMessageToMain.SubMessage2 = 0;
			snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
			MainTaskExecWait();

			/** ミラーキャリッジの移動終了を待つ */
			while (!SYS_IsMirrorScanReady) {
				wai_tsk( 10 );		/* 100ms待つ */
				if (SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR) {
					is_scanner_error = TRUE;
					break;
				}

				/* ＡＤＦに原稿をセットした時、ＡＤＦ側でミラーが止まらなくなる件
				** T.Nose 1997/12/20
				*/
				if ((SYB_MaintenanceSwitch[MNT_SW_C0] & MIRROR_MOVE_FORCE_END)
				 && (DEBUG_OperationExitFlag == 1)) {
					is_scanner_error = TRUE;
					break;
				}
			}
		}
 #else
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;	/** ランプチェックエラー対策 **/
 #endif
		if (!is_scanner_error) {
			if (CMN_ShadingExecute()) {		/** シェーディング取り込処理がＯＫの時 */
				LampOff();
				ChildDisplaySetCompleted(D2W_SF_Shading);
			}
			else {		/**	ＮＧの時	*/
				SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_LAMP_ERROR;
				LampOff();
			}
		}

 #if (PRO_FBS == ENABLE)	/* ICHOU用に追加  1996/10/11 s.takeuchi */
		/*	ミラーキャリッジを待機位置へ戻すメッセージをセットする
		**	但し、ミラーエラーの時は戻さない
		*/
		if (!is_mirror_fix) {
			if (!(SYS_MachineStatus[SYS_SCANNER_STATUS] & SYS_SCANNER_MIRROR_ERROR)) {
				OperationMessageToMain.Item = FROM_OPERATION;
				OperationMessageToMain.Message = MSG_SERV_SHADING_END;
				OperationMessageToMain.SubMessage1 = 0;
				OperationMessageToMain.SubMessage2 = 0;
				snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
				MainTaskExecWait();
			}
		}
 #else
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;	/** ランプチェックエラー対策 **/
 #endif
 #if (PRO_FBS == ENABLE)	/* 追加 1997/06/16 Y.Matsukuma */
		return;
	}
 #endif

#endif
}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* Add by Y.kano 2003/12/26 */
/*************************************************************************
	module		:[(テストファンクション)PS1、PB4スレッショルド設定]
	function	:[
		PS1,PB4の閾値の設定
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/26]
	author		:[加納]
*************************************************************************/
void SF_PS1_PB4_ThresholdSet(void)
{
	UBYTE	key;
	UBYTE	keytype;

	OPR_PS2_Adjust_Flg = TRUE;		/* PS2調整中フラグON by Y.Kano 2003/12/04 */

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_PleaseNonPaper);	/* "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ " */

	/* 下段表示 */
	FlashDisplayStringLow(D2W_EnterStop);		/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			PS1_PB4_ThresholdSet();	/* PS1,PB4（記録紙無し）閾値設定 */
			OPR_PS2_Adjust_Flg = FALSE;							/* PS2調整中フラグOFF */
			return;
		case STOP:
		case KEY_TIME_UP:
			OPR_PS2_Adjust_Flg = FALSE;							/* PS2調整中フラグOFF */
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１、ＰＢ４（記録紙無し）閾値設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void PS1_PB4_ThresholdSet(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	result;

	result = OK;

	SYB_MachineParameter[M_PARA_SW_J3] = (UBYTE)AD_PS1();		/* ＰＳ１（記録紙無し）のＡＤ値取込み。by Y.Kano 2003/12/18 */
	SYB_MachineParameter[M_PARA_SW_J5] = (UBYTE)AD_PB4();		/* ＰＢ４（記録紙無し）のＡＤ値取込み。by Y.Kano 2003/12/18 */

	if (SYB_MachineParameter[M_PARA_SW_J3] < 0x33) {
		if (SYB_MachineParameter[M_PARA_SW_J5] < 0x33) {
			/* 上段表示 */
			DisplayStringHigh(0,D2W_SF_PS1_PB4_Error);			/* "PS1,PB4 ｶｸﾆﾝｼﾃｸﾀﾞｻｲ " */
			NackBuzzer();	/* ナック音鳴動 */
			result = NG;
		}
		else {
			DisplayStringHigh(0,D2W_SF_PS1_Error);				/* "PS1 ｶｸﾆﾝｼﾃｸﾀﾞｻｲ     " */
			NackBuzzer();	/* ナック音鳴動 */
			result = NG;
		}
	}
	else if (SYB_MachineParameter[M_PARA_SW_J5] < 0x33) {
		DisplayStringHigh(0,D2W_SF_PB4_Error);				/* "PB4 ｶｸﾆﾝｼﾃｸﾀﾞｻｲ     " */
		NackBuzzer();		/* ナック音鳴動 */
		result = NG;
	}

	if (result) {
		/* ＰＳ１の閾値セット */
		SYB_MachineParameter[M_PARA_SW_J6] = (SYB_MachineParameter[M_PARA_SW_J3] - 0x19);

		/* ＰＢ４の閾値セット */
		SYB_MachineParameter[M_PARA_SW_J7] = (SYB_MachineParameter[M_PARA_SW_J5] - 0x19);

		/*-----------*/
		/** 画面表示 */
		/*-----------*/
		/* 上段表示 */
		DisplayStringHigh(0,D2W_SF_PS1_PB4_Threshold);	/* "PS1,PB4 ｼｷｲﾁ ｾｯﾃｲ   " */
		/* 下段表示 */
		ChildDisplayStringLow(D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */

		EndBuzzer();	/* 終了音鳴動 */
		return;
	}
	else {
		/* 下段表示 */
		FlashDisplayStringLow(D2W_Stop);				/* "              ｽﾄｯﾌﾟ " */

		while(1) {

			/** キー取り込み */
			OPR_GetKey(KEY_WAIT_ONE_MINUTE);
			key = GetInputKeyCode();
			keytype = GetInputKeyType();

			/** 取り込んだキーに対する処理を実行 */
			switch (keytype) {
			case STOP:
			case KEY_TIME_UP:
				return;

			case NO_EFFECT:
				break;

			default:
				NackBuzzer();
				break;
			}
		}
	}
}
#endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */


/*************************************************************************
	module		:[メモリー(DIP)スイッチリスト・コール]
	function	:[
		1.メモリスイッチ・マシンパラメーターのリストをプリントする
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[PRG*A]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/22]
	author		:[江口]
*************************************************************************/
void PrintMemorySwList(void)
{
	FinalListPrintOperation(LST_MEM_SW);
}

/*************************************************************************
	module		:[工場ファンクション]
	function	:[
		1.	工場チェック用のオペレーションを行う
		,	Ａ：工場ファンクションリスト
		,	Ｂ：ＬＥＤテスト
		,	Ｃ：ＬＣＤテスト
		,	Ｄ：パネルキーテスト
		,	Ｅ：ＳＲＡＭチェック
		,	Ｆ：ＤＲＡＭチェック -> OPR_RAM.Cに移動させた 1996/07/22 Eguchi
		,	Ｇ：ＲＴＣテスト	 -> OPR_RAM.Cに移動させた 1996/07/22 Eguchi
		,	Ｈ：ＲＳ２３２Ｃテスト

	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B
				  べたべたにかえた]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/06/13]
	author		:[江口,渡辺一章]
*************************************************************************/
void FactoryFunctionMode(void)
{
	UBYTE	key;		/* ｷｰ入力ﾃﾞｰﾀ */
	UBYTE	keytype;

	while (1) {
		DisplayStringHigh(0, D2W_SF_FactoryFunction);
		ClearDisplayLow();

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key     = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
		case KEY_TIME_UP:
			return;
		case ONETOUCH:
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			switch (key) {
			case ONETOUCH_01_KEY:
				PrintFactoryFunctionList();	/* 工場ファンクションリスト */
				return;
			case ONETOUCH_02_KEY:
				SF_All_LED_Test();			/* ＬＥＤテスト				*/
				break;
			case ONETOUCH_03_KEY:
				SF_LCD_Test();				/* ＬＣＤテスト				*/
				break;
			case ONETOUCH_04_KEY:
				SF_PanelKeyTest();			/* パネルキーテスト			*/
				break;
			case ONETOUCH_05_KEY:
				SF_SRAM_Check();			/* ＳＲＡＭテスト			*/
				return;
			case ONETOUCH_06_KEY:
				SF_DRAM_Check();			/* ＤＲＡＭテスト			*/
				return;
			case ONETOUCH_07_KEY:
				SF_RTCTestFunction();		/* ＲＴＣテストモード		*/
				return;
			case ONETOUCH_08_KEY:
				SF_RS232CTestFunction();	/* ＲＳ２３２Ｃテスト		*/
				return;
#if (0)		/* チェッカーのみ 97/09/10 By M.Kuwahara */
//			case ONETOUCH_09_KEY:
//				SF_CassetteCheck();			/* カセットテスト			*/
//				break;
#endif
			default:
				NackBuzzer();
				break;
			}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)/* By H.Fujimura 1999/01/06 */
			switch (key) {
			case ONETOUCH_01_KEY:
				PrintFactoryFunctionList();	/* 工場ファンクションリスト */
				return;
			case ONETOUCH_02_KEY:
				SF_All_LED_Test();			/* ＬＥＤテスト				*/
				break;
			case ONETOUCH_03_KEY:
				SF_LCD_Test();				/* ＬＣＤテスト				*/
				break;
			case ONETOUCH_04_KEY:
				IsSingleKeyOperation = FALSE;	/* 単一オペレーション無効 */
				SF_PanelKeyTest();			/* パネルキーテスト			*/
				IsSingleKeyOperation = TRUE;	/* 単一オペレーション有効 */
				break;
			case ONETOUCH_05_KEY:
				SF_SRAM_Check();			/* ＳＲＡＭテスト			*/
				return;
			case ONETOUCH_06_KEY:
				SF_DRAM_Check();			/* ＤＲＡＭテスト			*/
				return;
			case ONETOUCH_07_KEY:
				SF_RTCTestFunction();		/* ＲＴＣテストモード		*/
				return;
 #if (PRO_CLASS1 == ENABLE) /* added by H.Hirao 1999/02/09 */
			case ONETOUCH_08_KEY:
				SF_RS232CTestFunction();	/* ＲＳ２３２Ｃテスト		*/
				return;
 #endif
 #if (PRO_KEYPANEL == PANEL_SATSUKI2)		/* ＰＳ２調整モード by Y.Kano 2003/10/17 */
 			case ONETOUCH_09_KEY:
				SF_PS2AdjustFunction();		/* ＰＳ２調整モード			*/
				return;
 			case ONETOUCH_10_KEY:				/* ＰＳ１、ＰＢ４確認モード by Y.kano 2003/12/18 */
				SF_PS1_PB4_CheckFunction();		/* ＰＳ１、ＰＢ４確認モード	*/
				return;
 #elif (PRO_PAPER_AD_SENSOR_INIT == ENABLE)		/* ＰＳ１、ＰＳ２、ＰＢ４閾値設定モード by Y.Kano 2004/10/06 */
 			case ONETOUCH_09_KEY:
				SF_PS1_PS2_PB4_AdjustFunction();		/* ＰＳ１、ＰＳ２、ＰＢ４閾値設定モード	*/
				return;
 #endif
 #if defined (KEISATSU) /* 警察FAX 05/12/13 石橋正和 */
 			case ONETOUCH_09_KEY:
 				SF_CopyOnetouchA_ToAll(); /* ワンタッチAの内容をすべてのワンタッチ、短縮にコピーする */
 				return;
 			case ONETOUCH_10_KEY:
				SF_TonalTestWithVariableAtt(OPT_MDM_TONAL_1080HZ, 0xFF, D2W_SF_Transmit1100HzTone); /* 1100Hzトーナルテスト */
				return;
 			case ONETOUCH_11_KEY:
				SF_TonalTestWithVariableAtt(OPT_MDM_TONAL_V29_2400_9600, OPT_MDM_PIX_W1_B0, D2W_SF_TransmitV29Data); /* V29トーナルテスト */
				return;
 #endif
			default:
				NackBuzzer();
				break;
			}
#endif	/* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) */
#if (PRO_KEYPANEL == PANEL_STOCKHM2)  /* DVT : Modify end by SMuratec 夏 2004/11/08 */
			switch (key) {
			case ONETOUCH_01_KEY:
				PrintFactoryFunctionList();	/* 工場ファンクションリスト */
				return;
			case ONETOUCH_02_KEY:
				SF_LED_Test();				/* ＬＥＤテスト				*/
				break;
			case ONETOUCH_03_KEY:
				SF_LCD_Test();				/* ＬＣＤテスト				*/
				break;
			case ONETOUCH_04_KEY:
				IsSingleKeyOperation = FALSE;	/* 単一オペレーション無効 */
				SF_PanelKeyTest();			/* パネルキーテスト			*/
				IsSingleKeyOperation = TRUE;	/* 単一オペレーション有効 */
				break;
			case ONETOUCH_05_KEY:
				SF_SRAM_Check();			/* ＳＲＡＭテスト			*/
				return;
			case ONETOUCH_06_KEY:
				SF_DRAM_Check();			/* ＤＲＡＭテスト			*/
				return;
			case ONETOUCH_07_KEY:
				SF_RTCTestFunction();		/* ＲＴＣテストモード		*/
				return;
			default:
				NackBuzzer();
				break;
			}
#endif	/* (PRO_KEYPANEL == PANEL_STOCKHM2)  */
/* DVT : Modify end by SMuratec 夏 2004/11/08 */

#if (PRO_KEYPANEL == PANEL_ANZU_L)
			switch (key) {
			case ONETOUCH_A_KEY:
				PrintFactoryFunctionList();	/* 工場ファンクションリスト */
				return;
			case ONETOUCH_B_KEY:
				SF_All_LED_Test();			/* ＬＥＤテスト				*/
				return;
			case ONETOUCH_C_KEY:
				SF_LCD_Test();				/* ＬＣＤテスト				*/
				return;
			case ONETOUCH_D_KEY:
				SF_PanelKeyTest();			/* パネルキーテスト			*/
				return;
			case ONETOUCH_E_KEY:
				SF_SRAM_Check();			/* ＳＲＡＭテスト			*/
				return;
			case ONETOUCH_F_KEY:
				SF_DRAM_Check();			/* ＤＲＡＭテスト			*/
				return;
			case ONETOUCH_G_KEY:
				SF_RTCTestFunction();		/* ＲＴＣテストモード		*/
				return;
			case ONETOUCH_H_KEY:
				SF_RS232CTestFunction();	/* ＲＳ２３２Ｃテスト		*/
				return;

			default:
				NackBuzzer();
				break;
			}
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[工場ファンクションリストプリント]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-A]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/06/13]
	author		:[江口]
*************************************************************************/
void PrintFactoryFunctionList(void)
{
	FinalListPrintOperation(LST_FACT_MENU);
}

/*************************************************************************
	module		:[ＬＥＤテスト（全点灯、全消灯のみ）]
	function	:[
		1.全ＬＥＤの点灯／消灯を切り替える
		2.ＳＴＡＲＴキーを押すごとに全ＬＥＤが点灯、消灯する
		3.ストップキーで終了する。
		4.テストに入る前にＬＥＤの点灯状態を退避する
		5.テスト終了時はＬＥＤの点灯状態をテスト前の状態に戻る
		6.キー待ちは永久まちにする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-B]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/08]
	author		:[松隈,桑原]
*************************************************************************/
void SF_All_LED_Test(void)
{
	UBYTE	keytype;
	UBYTE	port1;
	UBYTE	port2;
	UBYTE	port3;
	UBYTE	type;

	SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE]	|= SYS_LED_TEST;	/* ﾒｲﾝを通ってもLEDが変わらないようにｽﾃｰﾀｽON */

	ClearDisplayHigh();						/* 上段表示クリア */
	DisplayStringHigh(0 ,D2W_SF_LEDTest );	/* 上段表示 */

	port1 = SYS_LED1_PortStatus;
	port2 = SYS_LED2_PortStatus;
	port3 = SYS_LCDC_PortStatus;

	type	= 1;
	AllLedOn();		/**	全ＬＥＤ点灯	*/
	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);	/* キー取り込み */
		keytype = GetInputKeyType();
		switch (keytype) {
		case START:
 #if defined(HINOKI3) /* ＬＥＤ制御変更 by Y.Kano 2004/12/27 */
			if( type == 0x01 ){
				AllLedOn();		/** 緑全ＬＥＤ点灯	*/
				AlarmLedOff();
			}
			else if ( type == 0x02 ) {
				AllLedOff();	/**	全ＬＥＤ消灯	*/
				AlarmLedOn();		/** アラームＬＥＤ点灯	*/
			}
			else if ( type == 0x03 ){
				AllLedOn();		/** 全ＬＥＤ点灯	*/
			}
			else {
				AllLedOff();	/**	全ＬＥＤ消灯	*/
			}
			type++;
			if ( type == 0x05) {
				type = 0x01;
			}

 #else
			type ^= 0x01;
			if( type == 0x00 ){
				AllLedOff();	/**	全ＬＥＤ消灯	*/
			}else{
				AllLedOn();		/** 全ＬＥＤ点灯	*/
			}
 #endif
			break;
		case LEFT_ARROW:
			break;
		case STOP:
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE]	&= ~SYS_LED_TEST;	/* ＬＥＤ変更用ステータスＯＦＦ */
			UpdateLED();
#else
 #if (PRO_CPU == SH7043)
			outpw(LED1_PORT,(UWORD)port1);	/**	ＬＥＤを元に戻す	*/
			outpw(LED2_PORT,(UWORD)port2);
			outpw(LCDC_PORT,(UWORD)port3);
 #endif
			SYS_LED1_PortStatus	= port1;	/** ＬＥＤポートを元に戻す */
			SYS_LED2_PortStatus	= port2;
			SYS_LCDC_PortStatus	= port3;
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE]	&= ~SYS_LED_TEST;	/* ＬＥＤ変更用ステータスＯＦＦ */
#endif
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
/*************************************************************************
	module		:[ＬＥＤテスト]
	function	:[
		1.全ＬＥＤの点灯／消灯を切り替える
		2.機能キーで全ＬＥＤが点灯する
		3.左カーソルキーで全ＬＥＤを消灯する。
		4.ストップキーで終了する。
		5.テストに入る前にＬＥＤの点灯状態を退避する
		6.テスト終了時はＬＥＤの点灯状態をテスト前の状態に戻る
		7.キー待ちは永久まちにする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-B]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/08]
	author		:[松隈,桑原]
*************************************************************************/
void SF_LED_Test(void)
{
	UBYTE	keytype;
	UWORD	port1;
	UWORD	port2;
	UWORD	port3;
	UBYTE	is_LED;			/* LED ON/Offﾌﾗｸﾞ */
	UBYTE	loop;			/* 点灯配列番号 */
#if (PRO_KEYPANEL == PANEL_STOCKHM2)	/* DVT:Added by SMuratec 夏 2004/10/11 */	
	int i;
#endif

	SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE]	|= SYS_LED_TEST;	/* ﾒｲﾝを通ってもLEDが変わらないようにｽﾃｰﾀｽON */

	ClearDisplayHigh();						/* 上段表示クリア */
	DisplayStringHigh(0 ,D2W_SF_LEDTest );	/* 上段表示 */

	port1 = SYS_LED1_PortStatus;
	port2 = SYS_LED2_PortStatus;
	port3 = SYS_LCDC_PortStatus;

	AllLedOff();	/**	全ＬＥＤ消灯	*/
	keytype	= (UBYTE)NO_EFFECT;
	is_LED	= 0;
	loop	= 0;

	while ( keytype != STOP ) {
		OPR_GetKey(KEY_WAIT_ONE_SECOND);
		keytype = GetInputKeyType();
		switch (keytype) {
		case START:
#if (PRO_KEYPANEL == PANEL_STOCKHM2)	/* DVT:Modify by SMuratec 夏 2004/10/11 */	
			is_LED++;
			if( is_LED>4 )
			is_LED = 1;
#else			
			if( loop != 0 ){			/* 点灯が開始されている時 */
				NackBuzzer();
			}
			else{	
				is_LED	= 1;
			}
#endif	/* (PRO_KEYPANEL == PANEL_STOCKHM2) */
			break;
		case STOP:
#if (PRO_CPU == SH7043)
 #if (PRO_CPU_VERSION == SH7043_R)	/*  By O.Kimoto 1998/09/08 */
			outpw(LED1_PORT,(UWORD)port1);	/**	ＬＥＤを元に戻す	*/
			outpw(LED2_PORT,(UWORD)port2);
			outpw(LCDC_PORT,(UWORD)port3);
 #else
 			/* ここには、ＨＩＮＯＫＩ用を記述してください。 */
 #endif
#endif
			SYS_LED1_PortStatus	= port1;	/** ＬＥＤポートを元に戻す */
			SYS_LED2_PortStatus	= port2;
			SYS_LCDC_PortStatus	= port3;
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE]	&= ~SYS_LED_TEST;	/* ＬＥＤ変更用ステータスＯＦＦ */
			return;
	 	case KEY_TIME_UP:
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		if( is_LED != 0 ){			/* 点灯の時 */
			OrderLedOn( LedArea[loop].Port, LedArea[loop].LedType );
			if( loop < 14 ){		/* 点灯途中 */
				loop++;
			}
		}
#elif (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) /* For HINOKI By O.Kimoto 1998/09/08 */
		if( is_LED != 0 ){			/* 点灯の時 */
			OrderLedOn( LedArea[loop].Port, LedArea[loop].LedType );
			if( loop < 14 ){		/* 点灯途中 */
				loop++;
			}
		}
#elif (PRO_KEYPANEL == PANEL_STOCKHM2)	/* DVT:Modify by SMuratec 夏 2004/10/8 */
		if( is_LED == 1 ){	/* 緑灯点灯 */
			CMN_DisableInterrupt();
			SYS_LED1_PortStatus = 0xff;
			SYS_LED1_PortStatus &= ~ALARM_LED;
			SYS_LED3_PortStatus = 0x01;
			IO__PEDR &= ~IO_BIT_LEWR3;
			CMN_EnableInterrupt();
		}
		if( is_LED == 2 ){	/* 赤灯点灯 */
			OrderLedOn( LedArea[0].Port, LedArea[0].LedType );
		}
		if( is_LED == 3 ){ /* 赤緑点灯*/
			AllLedOn();
		}
		if( is_LED == 4 ){
			AllLedOff();
		}
#else	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
		if( is_LED != 0 ){			/* 点灯の時 */
			OrderLedOn( LedArea[loop].Port, LedArea[loop].LedType );
			if( loop < 17 ){		/* 点灯途中 */
				loop++;
			}
		}
#endif
	}
}

/*************************************************************************
	module		:[ＬＣＤテスト（工場ファンクション)]
	function	:[
		1.一回目のスタートキーで全黒表示
		2.二回目のスタートキーで全白表示
		3.三回目のスタートキーでキャラクタ表示
		4.ストップで終了する。
		5.キー待ちは永久まちにする
		6.三回目以降のスタートキーは効かない
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-C]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/08]
	author		:[松隈,江口,桑原]
*************************************************************************/
void SF_LCD_Test(void)
{
	UBYTE	keytype;		/* 入力ｷｰﾃﾞｰﾀ */
	UBYTE	set_no;			/* 処理番号 */
	UBYTE	loop;			/* ﾙｰﾌﾟ */
	UBYTE	i;

	/* 初期画面 */
	CMN_StringCopy(FunctionDisplayBufferHigh,D2W_SF_LCDTest);
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	set_no	= 0;
	while (1) {
		/* 表示 */
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		DisplayStringLow(0,  FunctionDisplayBufferLow);

		OPR_GetKey(KEY_WAIT_FOREVER);	/* キー取り込み */
		keytype = GetInputKeyType();

#if (PRO_KEYPANEL == PANEL_ANZU_L)
		switch ( keytype ) {
		case START:
			if( set_no == 0 ){
				CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, 0xFF);
				CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, 0xFF);
				set_no++;
			}
			else{
				CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
				CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
				set_no--;
			}
			break;
		case STOP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
#else
		switch ( keytype ) {
		case START:
			if( set_no	< 3 ){
				set_no++;
			}
			else{
				NackBuzzer();
			}
			break;
		case STOP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
		switch( set_no ){
		case	1:
			/* 全黒表示用のバッファをセット */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, 0xFF);
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, 0xFF);
			break;
		case	2:
			/* 全白表示用のバッファをセット */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
			break;
		case	3:
#if defined(STOCKHM2) || defined(HINOKI3)	/* DVT : mod by SMuratec C.P 2004/10/11 */ /* Add by Y.Kano 2004/12/22 */
			for( loop = 0; loop < 7; loop++ ){
				FunctionDisplayBufferHigh[loop]	= 'A' + loop;
			}
			for( loop = 0; loop < 8; loop++ ){
				FunctionDisplayBufferLow[loop]	= '1' + loop;
			}
#else
			/* 上段に 'A ～ T',下段に 'U ～ Z,a ～ n'をセット */
			for( loop = 0; loop < OPR_DISPLAY_MAX; loop++ ){
				FunctionDisplayBufferHigh[loop]	= 'A' + loop;
			}
			i	= 0;
			for( loop = 0; loop < OPR_DISPLAY_MAX; loop++ ){
				if( loop == (26 - OPR_DISPLAY_MAX )){ 	/* 小文字の開始ｺｰﾄﾞをｾｯﾄ */
					i	+= 6;
				}
				FunctionDisplayBufferLow[loop]	= 'A' + OPR_DISPLAY_MAX + i;
				i++;
			}
#endif
			break;
		default:
			break;
		}
#endif
	}
}

/*************************************************************************
	module		:[大分用パネルチェッカー]
	function	:[
		1.正しい順番でキーを押して行くテスト。
		2.順番通りにキーを押さないとナックブザーではじかれる。
		  正しく'a'まで押されたら終了。
		3.押されたキーは誤っていても表示する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/12]
	author		:[松隈,渡辺一章,桑原]
*************************************************************************/
void SF_PanelKeyTest(void)
{
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/10 */
	UBYTE	prog;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
	UBYTE	i;
	UBYTE   stop;
	UBYTE	key;
	UBYTE	keytype;

	DisplayStringHigh(0, D2W_SF_PanelTest);
	i = 0;
	stop = 0;

	while(1) {
		OPR_GetKey(KEY_WAIT_FOREVER);		/* キー取り込み */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		switch (keytype) {
		case	SINGLE:
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/10/23 */
			if (key == MEMORY_TX_KEY) { /* メモリ送信キー押下で、表示はメモリソウシンにする */
				/** 表示処理 */
				ClearDisplayLow();
				DisplayStringLow(0 , D2W_SF_MemoryTx);
				break;
			}
			else if (key == AUTO_RX_KEY) { /* 自動受信キー押下で、表示はジュシンにする */
				/** 表示処理 */
				ClearDisplayLow();
				DisplayStringLow(0 , D2W_SF_Receive);
				break;
			}
#endif /* (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case	HOOK:
		case	HOLD:
		case 	FUNCTION:
		case	LEFT_ARROW:
		case	ENTER:
		case	REVIEW:
		case	CLEAR:
		case	DIALMARK:
		case	BROADCAST:
		case	SPECIAL:
		case	GROUP:
		case	SPEED:
		case	STOP:
		case	START:
		case	COPY:
		case	COPY_FAX:
		case	REDIAL:
		case	REDUCTION:
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
		case	MAGNIFICATION:
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
		case	TONE:			/* 追加 97/11/29 T.Fukumoto */
#endif
		case	BOOK_DOC_SIZE:
		case	COPY_RESET:
#if (PRO_KEYPANEL != PANEL_POPLAR_B)
		case	FLASH:
#endif
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
		case MERCURY:
#endif
			DisplayStringLow(0 , D2W_SF_Receive + (OPR_WORDING_LEN * (key - 1)));
			break;
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/10 */
		case	COMM_REPORT:
			DisplayStringLow(0 , D2W_SetCommunicationResult);
			break;
		case	CMD_LIST:
#if 1 /* (通信管理キー押下で、"ツウシンカカンリ"を表示する) Modified by SMuratec L.Z.W 2003/10/23 */
		  	for ( prog = 0;prog < OPR_WORDING_LEN; prog++ )
		  	{
				if (D2W_SetReportMode[prog] != ' ') break;
			}
			CMN_StringCopy(FunctionDisplayBufferLow, &D2W_SetReportMode[prog]);
			DisplayStringLow(0 , FunctionDisplayBufferLow);
			break;
#else
			DisplayStringLow(0 , D2W_PrintCommands);
			break;
#endif
		case	TCH_LIST:
			DisplayStringLow(0 , D2W_PrintOneTouch);
			break;
		case	SPD_LIST:
			DisplayStringLow(0 , D2W_PrintSpeedDial);
			break;
		case	VOLUME:
#if 1 /* (音量調整キー押下で、"オンリョウ"を表示する) Modified by SMuratec L.Z.W 2003/10/23 */
			CMN_StringCopy(FunctionDisplayBufferLow, &D2W_BuzzerVolume[15]);
			DisplayStringLow(0 , FunctionDisplayBufferLow);
			break;
#else
			DisplayStringLow(0 , D2W_BuzzerVolume);
			break;
#endif
#if 0 /* (文字キー押下で、"ﾓｼﾞ"を表示する) Modified by SMuratec L.Z.W 2003/10/23 */
		case	TONE:
		  	for ( prog = 0;prog < OPR_WORDING_LEN; prog++ )
		  	{
				if (D2W_Tone[prog] != ' ') break;
			}
			CMN_StringCopy(FunctionDisplayBufferLow, &D2W_Tone[prog]);
			DisplayStringLow(0 , FunctionDisplayBufferLow);
			break;
#else
		case	CHARACTER:
			DisplayStringLow(0 , D2W_Character);
			break;
#endif
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		case	SHARP:
		case	AST:
		case	NUMBER:
			FunctionDisplayBufferLow[0] = key;
			break;
		case	ONETOUCH:
			SetOnetouchCode(&FunctionDisplayBufferLow[0], key, OPR_SET_ONETOUCH_CODE);
			break;
		case	PROGRAM:
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			FunctionDisplayBufferLow[0] = OPR_PROGRAM_MARK_LEFT;
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[1], (UBYTE)(key - ONETOUCH_73_KEY + OPR_PRG_NUMBER_MIN), 2, '0');
			FunctionDisplayBufferLow[3] = OPR_PROGRAM_MARK_RIGHT;
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) /* By H.Fujimura 1999/01/06 */
 #if defined(HINOKI3)	/* by K.Watanabe 2004/10/18 */
  #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
			switch (key) {
			case ONETOUCH_27_KEY:
				DisplayStringLow(0, D2W_SF_KeidenKanyu);
				break;
			case ONETOUCH_28_KEY:
				DisplayStringLow(0, D2W_SF_IsseiKobetsu);
				break;
			case ONETOUCH_29_KEY:
				DisplayStringLow(0, D2W_SF_S_OnOff);
				break;
			case ONETOUCH_30_KEY:
				DisplayStringLow(0, D2W_SF_KyotsuSenyo);
				break;
			default:
				FunctionDisplayBufferLow[0] = OPR_PROGRAM_MARK;
				CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[1], (UBYTE)(key - ONETOUCH_25_KEY + OPR_PRG_NUMBER_MIN), 1, '0');
				break;
			}
  #else
			FunctionDisplayBufferLow[0] = OPR_PROGRAM_MARK;
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[1], (UBYTE)(key - ONETOUCH_25_KEY + OPR_PRG_NUMBER_MIN), 1, '0');
  #endif
 #else
			FunctionDisplayBufferLow[0] = OPR_PROGRAM_MARK_LEFT;
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[1], (UBYTE)(key - ONETOUCH_25_KEY + OPR_PRG_NUMBER_MIN), 2, '0');
			FunctionDisplayBufferLow[3] = OPR_PROGRAM_MARK_RIGHT;
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			FunctionDisplayBufferLow[0] = OPR_PROGRAM_MARK;
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[1], (UBYTE)(key - PROGRAM_P01 + OPR_PRG_NUMBER_MIN), 2, '0');
#endif
			break;
		}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		if ((key >= TEN_SHARP_KEY) && (key <= ONETOUCH_80_KEY)) {
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) /* By H.Fujimura 1999/01/06 */
 #if defined (KEISATSU) /* 警察FAX 05/11/26 石橋正和 */
		if ((key >= TEN_SHARP_KEY) && (key <= ONETOUCH_26_KEY)) {
 #else
		if ((key >= TEN_SHARP_KEY) && (key <= ONETOUCH_30_KEY)) {
 #endif
#endif
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/16 */
		if ((key >= TEN_SHARP_KEY) && (key <= ONETOUCH_20_KEY)) {
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		if ((key >= TEN_SHARP_KEY) && (key <= PROGRAM_P12)) {
#endif
			/** 表示処理 */
			ClearDisplayLow();
			DisplayStringLow(0, FunctionDisplayBufferLow);
		}

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 変更しました 1997/10/01 Y.Matsukuma */
	/* アンズは順番関係なし */
		if (key == STOP_KEY) {
			if (stop != 0) {
				return;
			}
			else {
				stop++;
			}
		}
		else {
			stop = 0;
		}
#else	/* ポプラはこれ */
		if (key == KeyArea[i]) {			/* 入力ＯＫの時 */
#if (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2004/10/08 */
			if (key == ONETOUCH_20_KEY) {			/* 全キー終了 */
#elif defined(HINOKI3)		/* Add by Y.Kano 2004/12/25 */
 #if (PRO_PREFIX_KEY == ENABLE) /* 警察FAX 05/11/26 石橋正和 */
			if (key == MERCURY_KEY) {			/* 全キー終了 */
 #else
			if (key == ONETOUCH_30_KEY) {			/* 全キー終了 */
 #endif
#else
			if (key == START_KEY) {			/* 全キー終了 */
#endif
				wai_tsk( 200 );
				AckBuzzer();
				wai_tsk( 20 );
				AckBuzzer();
				wai_tsk( 20 );
				AckBuzzer();
				ClearDisplayLow();
				DisplayStringLow(0 , D2W_SF_OK);
				OPR_GetKey(KEY_WAIT_2_SECOND);		/* キー取り込み */
				key = GetInputKeyCode();
				keytype = GetInputKeyType();
				switch (keytype) {
					case STOP:
						break;
					default:
						return;
				}
				i = 0;
				stop = 1;
			}
			else {
			/*	AckBuzzer();	By M.Tachibana 1997/06/17 */
				i++;
				stop = 0;
           	}
		}
		else{
			if (key == STOP_KEY) {
				if (stop != 0) {
					return;
				}
				else {
					stop++;
				}
			}
			else {
				stop = 0;
			}
			NackBuzzer();
		}
#endif
	}
}

/*************************************************************************
	module		:[工場ファンクション：ＲＴＣ評価テストモード]
	function	:[
		1.ＲＴＣの調整を行う
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-G]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[95/05/20]
	author		:[江口,渡辺一章]
*************************************************************************/
void SF_RTCTestFunction(void)
{
	UBYTE keytype;

	DisplayStringHigh(0, D2W_SF_RTCTest);
	ClearDisplayLow();

	if (!CheckRTC_TestEnable()) {	/* RTCテストが不可能な時 */
		NackBuzzer();
		DisplayStringLow(0, D2W_SF_NG);	/* "NG                  " */

		while (keytype != STOP) {	/* ストップキーが押されるまで結果表示をします */
			OPR_GetKey(KEY_WAIT_FOREVER);
			keytype = GetInputKeyType();
			if ((keytype != STOP) && (keytype != NO_EFFECT)) {
				NackBuzzer();
			}
		}

		/* 特に問題は無いと思いますが、一応終了時の形を合わせておきます */
		RTCTestEnd();
		return;
	}
	else {							/* RTCテストが可能な時 */
		DisplayStringLow(0, D2W_SF_OK);	/* "OK                  " */
	}

	/* RTCテストスタート */
	RTCTestStart();

	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
			/* TEST 終了 */
			RTCTestEnd();
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[工場ファンクション：ＲＳ２３２Ｃテスト]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/11]
	author		:[松隈,渡辺一章]
*************************************************************************/
void SF_RS232CTestFunction(void)
{
#if (PRO_CLASS1 == ENABLE)
	UBYTE	hex_code;			/* RS232Cﾃｽﾄﾃﾞｰﾀ */
	UBYTE	key;
	UBYTE	keytype;
	MESSAGE_t *WaitData;			/* ﾒｯｾｰｼﾞ */
	MESSAGE_t *wait_sub;			/* ﾒｯｾｰｼﾞ待避変数 */


	if (SYS_RS232C_Exist == 0) { /* RS232C基盤がない 1996/03/12 Eguchi */
		NackBuzzer();
		return;
	}

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	DisplayStringHigh(0, D2W_SF_RS232CTest);	/* "RS232C Test         " */
	ClearDisplayLow();

	while (1) {

		hex_code = 0;

		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
			return;
		case ONETOUCH:
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			switch (key) {
			case ONETOUCH_01_KEY:	/* 折り返し */
				hex_code = 'A';
				break;
			case ONETOUCH_02_KEY:	/* 送信 */
				hex_code = 0x01;
				break;
			case ONETOUCH_03_KEY:	/* 受信 */
				hex_code = 0x02;
				break;
			default:
				NackBuzzer();
				break;
			}
 #endif
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			switch (key) {
			case ONETOUCH_A_KEY:	/* 折り返し */
				hex_code = 'A';
				break;
			case ONETOUCH_B_KEY:	/* 送信 */
				hex_code = 0x01;
				break;
			case ONETOUCH_C_KEY:	/* 受信 */
				hex_code = 0x02;
				break;
			default:
				NackBuzzer();
				break;
			}
 #endif
			ClearDisplayLow();
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}

		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		if (hex_code != 0) {
			/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 Eguchi */
			OperationMessageToMain.Message = MSG_SERV_RS232C_TEST;
			OperationMessageToMain.SubMessage1 = hex_code;
			snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
			MainTaskExecWait();
			for (;;) {
				rcv_msg( mbxno.OPR_Task, &WaitData );
				wait_sub = WaitData;
				if ( wait_sub->Item == FROM_MAIN && wait_sub->Message == CL1_RS232C_TEST_END ) {
					break;
				}
			}

			if ( wait_sub->SubMessage1 != CHECK_OK ) {
				DisplayStringLow(0, D2W_SF_NG);
			}
			else {
				DisplayStringLow(0, D2W_SF_OK);
			}
		}
	}
#else
	NackBuzzer();
#endif
}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)		/* ＰＳ２調整モード by Y.Kano 2003/10/17 */
/*************************************************************************
	module		:[工場ファンクション：ＰＳ２調整モード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/17]
	author		:[加納]
*************************************************************************/
void SF_PS2AdjustFunction(void)
{
	UBYTE	result;
	UBYTE	key;
	UBYTE	keytype;

	result = FALSE;

#if defined(SATSUKI2) || defined(STOCKHM2)	/* Add by Y.Kano 2003/12/04 */
	OPR_PS2_Adjust_Flg = TRUE;		/* PS2調整中フラグON by Y.Kano 2003/12/04 */
#endif

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0,D2W_SF_PS2AdjustMode);	/* "PS2 ﾁｮｳｾｲ ﾓｰﾄﾞ      " */

	/* 下段表示 */
	FlashDisplayStringLow(D2W_EnterStop);		/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			result = PS2VolumueAdjustStanby();		/* PS2ボリューム調整準備 */
			break;
		case STOP:
		case KEY_TIME_UP:
			OPR_PS2_Adjust_Flg = FALSE;			/* PS2調整中フラグOFFが抜けてる。O.Oshima 2003/12/14 */
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (result == TRUE) {
			return;
		}
	}
}
/*************************************************************************
	module		:[ＰＳ２調整準備]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/17]
	author		:[加納]
*************************************************************************/
UBYTE PS2VolumueAdjustStanby(void)
{
	UBYTE	result;
	UBYTE	key;
	UBYTE	keytype;

	result = FALSE;

#if(1) /* 戻します。センサー調整前なのにセンサーの値を参照するのは変。O.Oshima 2003/12/14 */
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_ReplaceRxPaper);	/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */

#else
/*------------< 追加 by Y.kano 2003/12/04 >-------------*/

	if ((!QueryPs1On()) && (!QueryPs2On())) {
		/*-----------*/
		/** 画面表示 */
		/*-----------*/
		/* 上段表示 */
		DisplayStringHigh(0, D2W_ReplaceRxPaper);	/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */
	}

	while(1) {
		if ((QueryPs1On()) && (QueryPs2On())) {
			/*-----------*/
			/** 画面表示 */
			/*-----------*/
			/* 上段表示 */
			DisplayStringHigh(0,D2W_SF_PS2AdjustMode);	/* "PS2 ﾁｮｳｾｲ ﾓｰﾄﾞ      " */
			break;
		}
	}
	result = FALSE;
/*------------------------------------------------------*/
#endif

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			result = PS2VolumueAdjust();		/* PS2ボリューム調整 */
			break;
		case STOP:
		case KEY_TIME_UP:
			result = TRUE;
			break;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (result == TRUE) {
			OPR_PS2_Adjust_Flg = FALSE;		/* PS2調整中フラグOFF by Y.Kano 2003/12/04 */
			return(OK);
		}
	}
}

/*************************************************************************
	module		:[ＰＳ２調整]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/17]
	author		:[加納]
*************************************************************************/
UBYTE PS2VolumueAdjust(void)
{
	UBYTE	key;
	UBYTE	keytype;

	PS2Volumue = 0;

#if (0)		/* PS1,PB4確認モードでＡ／Ｄ値の取込みを行います。by Y.kano 2003/12/18 */
 #if defined(SATSUKI2)	/* ＰＢ４センサーテスト用 by Y.Kano 2003/12/12 */
	SYB_MachineParameter[M_PARA_SW_J5] = AD_PB4();		/* ＰＢ４のＡＤ値取込み。by Y.Kano 2003/10/31 */
	SYB_MachineParameter[M_PARA_SW_J4] = AD_PS1();		/* ＰＳ１のＡＤ値取込み。by Y.Kano 2003/10/31 */
 #endif
#endif
	while(1) {

		if ((UWORD)AD_PS2() >= ((UWORD)SYB_PS2LimitValue)) {
			/* 上段表示 */
			DisplayStringHigh(0, D2W_PS2VolumueFullLight_1);	/* "PS2 ｦ ﾐｷﾞ ﾍ ｻｲﾀﾞｲｹﾞﾝ" */
			DisplayStringLow(0, D2W_PS2VolumueFullLight_2);		/* "ﾏﾜｼﾃｸﾀﾞｻｲ           " */
		}
		else {
			if (((UWORD)AD_PS2() >= 0x0000) && ((UWORD)AD_PS2() <= 0x000e)) {	/* 00h～0Eh(0.0～0.3V) */
				PS2Volumue = VOLUMUE_0;		/* 左矢印１ケ表示 		*/
			}
			else if (((UWORD)AD_PS2() >= 0x000f) && ((UWORD)AD_PS2() <= 0x0017)) {	/* 0Fh～17h */
				PS2Volumue = VOLUMUE_OK;		/* セットカンリョウ表示 */
			}
			else if (((UWORD)AD_PS2() >= 0x0018) && ((UWORD)AD_PS2() <= 0x0027)) {	/* 18h～27h(0.46～0.8V) */
				PS2Volumue = VOLUMUE_1;		/* 右矢印１ケ表示 		*/
			}
			else if (((UWORD)AD_PS2() >= 0x0028) && ((UWORD)AD_PS2() <= 0x0037)) {	/* 28h～37h(0.8～1.12V) */
				PS2Volumue = VOLUMUE_2;		/* 右矢印２ケ表示 		*/
			}
			else {		/* 38h～FFH */
				PS2Volumue = VOLUMUE_3;		/* 右矢印３ケ表示 		*/				/* 38h～ffh(1.12～5.0V) */
			}
			DisplayPS2Volumue();
		}
		
		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_SECOND);	/* キー待ち１秒 */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			ChildDisplayStringLow(D2W_PS2_Complete);	/* " **   Complete   ** " */
			return(OK);

		case STOP:
			return(OK);

		case KEY_TIME_UP:
			break;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＰＳ２ボリューム量表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/17]
	author		:[加納]
*************************************************************************/
void DisplayPS2Volumue(void)
{
	/* 上段表示 */
	DisplayStringHigh(0, D2W_PS2VolumueTitle);		/* "     PS2 ﾎﾞﾘｭｰﾑ     " */
	CMN_MemorySet(&FunctionDisplayBufferLow[0], 20, ' ');
	FunctionDisplayBufferLow[10]  = 0x2B;		/* + */

	switch (PS2Volumue) {
	case VOLUMUE_0:					/* 左矢印１ケ表示	*/
		FunctionDisplayBufferLow[9]  = 0x7F;		/* ← */
		/* 下段表示 */
		DisplayStringLow(0, FunctionDisplayBufferLow);
		break;										
	case VOLUMUE_1:					/* 右矢印１ケ表示	*/
		FunctionDisplayBufferLow[11]  = 0x7E;		/* → */
		/* 下段表示 */
		DisplayStringLow(0, FunctionDisplayBufferLow);
		break;
	case VOLUMUE_2:					/* 右矢印２ケ表示	*/
		FunctionDisplayBufferLow[11]  = 0x7E;		/* → */
		FunctionDisplayBufferLow[12]  = 0x7E;		/* → */
		/* 下段表示 */
		DisplayStringLow(0, FunctionDisplayBufferLow);
		break;
	case VOLUMUE_3:					/* 右矢印３ケ表示	*/
		FunctionDisplayBufferLow[11]  = 0x7E;		/* → */
		FunctionDisplayBufferLow[12]  = 0x7E;		/* → */
		FunctionDisplayBufferLow[13]  = 0x7E;		/* → */
		/* 下段表示 */
		DisplayStringLow(0, FunctionDisplayBufferLow);
		break;
	case VOLUMUE_OK:				/* ＯＫ表示		*/
		/* 下段表示 */
		DisplayStringLow(0, D2W_PS2_OK);
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[工場ファンクション：ＰＳ１、ＰＢ４確認モード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void SF_PS1_PB4_CheckFunction(void)
{
	UBYTE	result;
	UBYTE	key;
	UBYTE	keytype;

	result = FALSE;

#if defined(SATSUKI2) || defined(STOCKHM2)	/* Add by Y.Kano 2003/12/04 */
	OPR_PS2_Adjust_Flg = TRUE;		/* PS2調整中フラグON by Y.Kano 2003/12/04 */
#endif

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0,D2W_SF_PS1_PB4_CheckMode);	/* "PS1,PB4 ｶｸﾆﾝﾓｰﾄﾞ    " */

	/* 下段表示 */
	FlashDisplayStringLow(D2W_EnterStop);		/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			result = PS1_PB4_Paper_Set_CheckStanby();	/* PS1,PB4（記録紙有り）確認準備 */
			break;
		case STOP:
		case KEY_TIME_UP:
			OPR_PS2_Adjust_Flg = FALSE;			/* PS2調整中フラグOFFが抜けてる。O.Oshima 2003/12/14 */
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (result == TRUE) {
			return;
		}
	}
}
/*************************************************************************
	module		:[ＰＳ１、ＰＢ４（記録紙有り）確認準備]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
UBYTE PS1_PB4_Paper_Set_CheckStanby(void)
{
	UBYTE	result;
	UBYTE	key;
	UBYTE	keytype;

	result = FALSE;

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_ReplaceRxPaper);	/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			result = PS1_PB4_PaperSet_Check();		/* PS1,PB4（記録紙有り）確認 */
			break;
		case STOP:
		case KEY_TIME_UP:
			result = TRUE;
			break;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (result == TRUE) {
			OPR_PS2_Adjust_Flg = FALSE;		/* PS2調整中フラグOFF by Y.Kano 2003/12/04 */
			return(OK);
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１、ＰＢ４（記録紙有り）確認]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
UBYTE PS1_PB4_PaperSet_Check(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	result;
	UBYTE	PS1_result;
	UBYTE	PB4_result;

	result = FALSE;

	SYB_MachineParameter[M_PARA_SW_J2] = AD_PS1();		/* ＰＳ１（記録紙有り）のＡＤ値取込み。by Y.Kano 2003/12/18 */
	SYB_MachineParameter[M_PARA_SW_J4] = AD_PB4();		/* ＰＢ４（記録紙有り）のＡＤ値取込み。by Y.Kano 2003/12/18 */

	/* ＰＳ１の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J2] < 0x38) {
		PS1_result = TRUE;		/* ＰＳ１判定ＯＫ */
	}
	else {
		PS1_result = FALSE;		/* ＰＳ１判定ＮＧ */
	}

	/* ＰＢ４の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J4] < 0x38) {
		PB4_result = TRUE;		/* ＰＢ４判定ＯＫ */
	}
	else {
		PB4_result = FALSE;		/* ＰＢ４判定ＮＧ */
	}
	FlashDisplayStringLow(D2W_EnterStop);			/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	DisplayPS1_PB4_Set(PS1_result, PB4_result);		/* PS1,PB4の判定結果表示 */

	if ((PS1_result == TRUE) && (PB4_result == TRUE)) {
		EndBuzzer();	/* 終了音鳴動 */
	}
	else {
		NackBuzzer();	/* ナック音鳴動 */
	}

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			result = PS1_PB4_Paper_Non_CheckStanby();		/* PS1,PB4（記録紙無し）確認準備 */
			break;
		case STOP:
		case KEY_TIME_UP:
			OPR_PS2_Adjust_Flg = FALSE;			/* PS2調整中フラグOFFが抜けてる。O.Oshima 2003/12/14 */
			return(OK);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (result == TRUE) {
			return(OK);
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１，ＰＢ４の判定結果表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void DisplayPS1_PB4_Set(UBYTE PS1_result, UBYTE PB4_result)
{
	CMN_MemorySet(&FunctionDisplayBufferHigh[0], 20, ' ');

	/* 上段表示 */
	FunctionDisplayBufferHigh[0]  = 'P';		/* PS1表示 */
	FunctionDisplayBufferHigh[1]  = 'S';
	FunctionDisplayBufferHigh[2]  = '1';
	FunctionDisplayBufferHigh[3]  = ':';

	FunctionDisplayBufferHigh[8]  = 'P';		/* PB4表示 */
	FunctionDisplayBufferHigh[9]  = 'B';
	FunctionDisplayBufferHigh[10]  = '4';
	FunctionDisplayBufferHigh[11]  = ':';

	switch (PS1_result) {
	case TRUE:					/* ＯＫ表示	*/
		FunctionDisplayBufferHigh[4]  = 'O';		/* OK表示 */
		FunctionDisplayBufferHigh[5]  = 'K';
		break;										
	case FALSE:					/* ＮＧ表示	*/
		FunctionDisplayBufferHigh[4]  = 'N';		/* NG表示 */
		FunctionDisplayBufferHigh[5]  = 'G';
		break;
	default:
		break;
	}
	switch (PB4_result) {
	case TRUE:					/* ＯＫ表示	*/
		FunctionDisplayBufferHigh[12]  = 	'O';		/* OK表示 */
		FunctionDisplayBufferHigh[13]  = 	'K';
		break;										
	case FALSE:					/* ＮＧ表示	*/
		FunctionDisplayBufferHigh[12]  =	 'N';		/* NG表示 */
		FunctionDisplayBufferHigh[13]  =	 'G';
		break;
	default:
		break;
	}
	/* 上段表示 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}

/*************************************************************************
	module		:[ＰＳ１、ＰＢ４（記録紙無し）確認準備]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
UBYTE PS1_PB4_Paper_Non_CheckStanby(void)
{
	UBYTE	result;
	UBYTE	key;
	UBYTE	keytype;

	result = FALSE;

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_PleaseNonPaper);	/* "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			result = PS1_PB4_PaperNon_Check();		/* PS1,PB4（記録紙無し）確認 */
			break;
		case STOP:
		case KEY_TIME_UP:
			result = TRUE;
			break;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
		if (result == TRUE) {
			OPR_PS2_Adjust_Flg = FALSE;		/* PS2調整中フラグOFF by Y.Kano 2003/12/04 */
			return(OK);
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１、ＰＢ４（記録紙無し）確認]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
UBYTE PS1_PB4_PaperNon_Check(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	PS1_result;
	UBYTE	PB4_result;

	SYB_MachineParameter[M_PARA_SW_J3] = AD_PS1();		/* ＰＳ１（記録紙無し）のＡＤ値取込み。by Y.Kano 2003/12/18 */
	SYB_MachineParameter[M_PARA_SW_J5] = AD_PB4();		/* ＰＢ４（記録紙無し）のＡＤ値取込み。by Y.Kano 2003/12/18 */

	/* ＰＳ１の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J3] > 0xa8) {
		PS1_result = TRUE;		/* ＰＳ１判定ＯＫ */
	}
	else {
		PS1_result = FALSE;		/* ＰＳ１判定ＮＧ */
	}

	/* ＰＢ４の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J5] > 0xa8) {
		PB4_result = TRUE;		/* ＰＢ４判定ＯＫ */
	}
	else {
		PB4_result = FALSE;		/* ＰＢ４判定ＮＧ */
	}
	FlashDisplayStringLow(D2W_Stop);				/* "              ｽﾄｯﾌﾟ " */

	DisplayPS1_PB4_Set(PS1_result, PB4_result);		/* PS1,PB4の判定結果表示 */

	if ((PS1_result == TRUE) && (PB4_result == TRUE)) {
		EndBuzzer();	/* 終了音鳴動 */
	}
	else {
		NackBuzzer();	/* ナック音鳴動 */
	}

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case STOP:
		case KEY_TIME_UP:
			OPR_PS2_Adjust_Flg = FALSE;			/* PS2調整中フラグOFFが抜けてる。O.Oshima 2003/12/14 */
			return(OK);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

#endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

#if (PRO_PAPER_AD_SENSOR_INIT == ENABLE)	/* ＰＳ１、ＰＳ２、ＰＢ４閾値設定モード by Y.Kano 2004/10/06 */
/*************************************************************************
	module		:[工場ファンクション：ＰＳ１、ＰＳ２、ＰＢ４閾値設定モード]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2004/10/06]
	author		:[加納]
*************************************************************************/
void SF_PS1_PS2_PB4_AdjustFunction(void)
{
	UBYTE	key;
	UBYTE	keytype;

	OPR_PaperSensor_Adjust_Flg = TRUE;		/* PS1,PS2,PB4設定中フラグON */

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0,D2W_SF_PS1_PS2_PB4_AdjustMode);	/* "PS1,PS2,PB4 ｼｷｲﾁｾｯﾃｲ" */

	/* 下段表示 */
	FlashDisplayStringLow(D2W_EnterStop);		/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			PS1_PS2_PB4_Paper_Non_Stanby();	/* PS1,PS2,PB4（記録紙無し）準備 */
			OPR_PaperSensor_Adjust_Flg = FALSE;			/* PS1,PS2,PB4設定中フラグOFF */
			return;
			break;
		case STOP:
		case KEY_TIME_UP:
			OPR_PaperSensor_Adjust_Flg = FALSE;			/* PS1,PS2,PB4設定中フラグOFF */
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}
/*************************************************************************
	module		:[ＰＳ１、ＰＳ２、ＰＢ４（記録紙無し）準備]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void PS1_PS2_PB4_Paper_Non_Stanby(void)
{
	UBYTE	key;
	UBYTE	keytype;

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_PleaseNonPaper);	/* "ｷﾛｸｼ ｦ ﾄﾘﾉｿﾞｲﾃｸﾀﾞｻｲ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			PS1_PS2_PB4_SensorThresholdSet();		/* PS1,PS2,PB4閾値設定 */
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１、ＰＳ２、ＰＢ４閾値設定]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void PS1_PS2_PB4_SensorThresholdSet(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	result;

	result = OK;

	SYB_MachineParameter[M_PARA_SW_J4] = (UBYTE)AD_PS1();		/* ＰＳ１（記録紙無し）のＡＤ値取込み。 */
	SYB_MachineParameter[M_PARA_SW_J5] = (UBYTE)AD_PS2();		/* ＰＳ２（記録紙無し）のＡＤ値取込み。 */
	SYB_MachineParameter[M_PARA_SW_J6] = (UBYTE)AD_PB4();		/* ＰＢ４（記録紙無し）のＡＤ値取込み。 */

	if (SYB_MachineParameter[M_PARA_SW_J4] < 0x33) {
		if (SYB_MachineParameter[M_PARA_SW_J5] < 0x33) {
			if (SYB_MachineParameter[M_PARA_SW_J6] < 0x33) {
				/* 上段表示 */
				DisplayStringHigh(0,D2W_SF_PS1_PS2_PB4_Error);			/* "PS1,PS2,PB4 ﾄﾘｺﾐﾁｴﾗｰ" */
			}
			else {
				/* 上段表示 */
				DisplayStringHigh(0,D2W_SF_PS1_PS2_Error);				/* "PS1,PS2 ﾄﾘｺﾐﾁｴﾗｰ    " */
			}
		}
		else {
			if (SYB_MachineParameter[M_PARA_SW_J6] < 0x33) {
				DisplayStringHigh(0,D2W_SF_PS1_PB4_Error);				/* "PS1,PB4 ﾄﾘｺﾐﾁｴﾗｰ    " */
			}
			else {
				DisplayStringHigh(0,D2W_SF_PS1_Error);					/* "PS1 ﾄﾘｺﾐﾁｴﾗｰ        " */
			}
		}
		NackBuzzer();	/* ナック音鳴動 */
		result = NG;
	}
	else if (SYB_MachineParameter[M_PARA_SW_J5] < 0x33) {
		if (SYB_MachineParameter[M_PARA_SW_J6] < 0x33) {
			DisplayStringHigh(0,D2W_SF_PS2_PB4_Error);				/* "PS2,PB4 ﾄﾘｺﾐﾁｴﾗｰ    " */
		}
		else {
			DisplayStringHigh(0,D2W_SF_PS2_Error);					/* "PS2 ﾄﾘｺﾐﾁｴﾗｰ        " */
		}
		NackBuzzer();	/* ナック音鳴動 */
		result = NG;
	}
	else if (SYB_MachineParameter[M_PARA_SW_J6] < 0x33) {
		DisplayStringHigh(0,D2W_SF_PB4_Error);						/* "PB4 ﾄﾘｺﾐﾁｴﾗｰ        " */
		NackBuzzer();	/* ナック音鳴動 */
		result = NG;
	}

	if (result) {
		/* ＰＳ１の閾値セット */
		SYB_MachineParameter[M_PARA_SW_J1] = (SYB_MachineParameter[M_PARA_SW_J4] - 0x19);

		/* ＰＳ２の閾値セット */
		SYB_MachineParameter[M_PARA_SW_J2] = (SYB_MachineParameter[M_PARA_SW_J5] - 0x19);

		/* ＰＢ４の閾値セット */
		SYB_MachineParameter[M_PARA_SW_J3] = (SYB_MachineParameter[M_PARA_SW_J6] - 0x19);

		/*-----------*/
		/** 画面表示 */
		/*-----------*/
		/* 上段表示 */
		DisplayStringHigh(0,D2W_SF_PS1_PS2_PB4_AdjustMode);	/* "PS1,PS2,PB4 ｼｷｲﾁｾｯﾃｲ" */
		/* 下段表示 */
		DisplayStringLow(0,D2W_SetComplete);		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */
/*		ChildDisplayStringLow(D2W_SetComplete);*/		/* " **  ｾｯﾄ  ｶﾝﾘｮｳ  ** " */

		EndBuzzer();	/* 終了音鳴動 */
		wai_tsk(100);
	}
	else {
		NackBuzzer();	/* ナック音鳴動 */

		/* 下段表示 */
		FlashDisplayStringLow(D2W_Stop);				/* "              ｽﾄｯﾌﾟ " */

		while(1) {

			/** キー取り込み */
			OPR_GetKey(KEY_WAIT_ONE_MINUTE);
			key = GetInputKeyCode();
			keytype = GetInputKeyType();

			/** 取り込んだキーに対する処理を実行 */
			switch (keytype) {
			case STOP:
			case KEY_TIME_UP:
				return;

			case NO_EFFECT:
				break;

			default:
				NackBuzzer();
				break;
			}
		}
	}
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_SensorTest);		/* "ｾﾝｻｰﾃｽﾄ             " */
	/* 下段表示 */
	FlashDisplayStringLow(D2W_EnterStop);		/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {
		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			PS1_PS2_PB4_Paper_Set_Stanby();		/* PS1,PS2,PB4（記録紙有り）準備 */
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}


/*************************************************************************
	module		:[ＰＳ１、ＰＳ２、ＰＢ４（記録紙有り）準備]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void PS1_PS2_PB4_Paper_Set_Stanby(void)
{
	UBYTE	key;
	UBYTE	keytype;

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_ReplaceRxPaper);	/* "ｷﾛｸｼ ｦ ﾎｷｭｳ ｼﾃｸﾀﾞｻｲ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			PS1_PS2_PB4_SensorTest();		/* PS1,PS2,PB4（記録紙有り）センサーテスト */
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１、ＰＢ４（記録紙有り）確認]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void PS1_PS2_PB4_SensorTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	PS1_result;
	UBYTE	PS2_result;
	UBYTE	PB4_result;

	SYB_MachineParameter[M_PARA_SW_J4] = (UBYTE)AD_PS1();		/* ＰＳ１（記録紙有り）のＡＤ値取込み。 */
	SYB_MachineParameter[M_PARA_SW_J5] = (UBYTE)AD_PS2();		/* ＰＳ２（記録紙有り）のＡＤ値取込み。 */
	SYB_MachineParameter[M_PARA_SW_J6] = (UBYTE)AD_PB4();		/* ＰＢ４（記録紙有り）のＡＤ値取込み。 */

	/* ＰＳ１の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J4] < SYB_MachineParameter[M_PARA_SW_J1]) {
		PS1_result = TRUE;		/* ＰＳ１判定ＯＫ */
	}
	else {
		PS1_result = FALSE;		/* ＰＳ１判定ＮＧ */
		/* ＰＳ１の閾値にデフォルト値をセット */
		SYB_MachineParameter[M_PARA_SW_J1] = 0xCD;
	}

	/* ＰＳ２の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J5] < SYB_MachineParameter[M_PARA_SW_J2]) {
		PS2_result = TRUE;		/* ＰＳ２判定ＯＫ */
	}
	else {
		PS2_result = FALSE;		/* ＰＳ２判定ＮＧ */
		/* ＰＳ２の閾値にデフォルト値をセット */
		SYB_MachineParameter[M_PARA_SW_J2] = 0xAD;
	}

	/* ＰＢ４の判定 */
	if (SYB_MachineParameter[M_PARA_SW_J6] < SYB_MachineParameter[M_PARA_SW_J3]) {
		PB4_result = TRUE;		/* ＰＢ４判定ＯＫ */
	}
	else {
		PB4_result = FALSE;		/* ＰＢ４判定ＮＧ */
		/* ＰＳ３の閾値にデフォルト値をセット */
		SYB_MachineParameter[M_PARA_SW_J3] = 0xC9;
	}

	FlashDisplayStringLow(D2W_EnterStop);			/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	DisplayPS1_PS2_PB4_Result(PS1_result, PS2_result, PB4_result);		/* PS1,PS2,PB4の判定結果表示 */

	if ((PS1_result == TRUE) && (PS2_result == TRUE) && (PB4_result == TRUE)) {
		EndBuzzer();	/* 終了音鳴動 */
	}
	else {
		NackBuzzer();	/* ナック音鳴動 */
	}

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＰＳ１，ＰＳ２、ＰＢ４の判定結果表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/12/18]
	author		:[加納]
*************************************************************************/
void DisplayPS1_PS2_PB4_Result(UBYTE PS1_result,  UBYTE PS2_result, UBYTE PB4_result)
{
	CMN_MemorySet(&FunctionDisplayBufferHigh[0], 20, ' ');

	/* 上段表示 */
	FunctionDisplayBufferHigh[0]  = 'P';		/* PS1表示 */
	FunctionDisplayBufferHigh[1]  = 'S';
	FunctionDisplayBufferHigh[2]  = '1';
	FunctionDisplayBufferHigh[3]  = ':';

	FunctionDisplayBufferHigh[7]  = 'P';		/* PS2表示 */
	FunctionDisplayBufferHigh[8]  = 'S';
	FunctionDisplayBufferHigh[9]  = '2';
	FunctionDisplayBufferHigh[10]  = ':';

	FunctionDisplayBufferHigh[14]  = 'P';		/* PB4表示 */
	FunctionDisplayBufferHigh[15]  = 'B';
	FunctionDisplayBufferHigh[16]  = '4';
	FunctionDisplayBufferHigh[17]  = ':';

	switch (PS1_result) {
	case TRUE:					/* ＯＫ表示	*/
		FunctionDisplayBufferHigh[4]  = 'O';		/* OK表示 */
		FunctionDisplayBufferHigh[5]  = 'K';
		break;										
	case FALSE:					/* ＮＧ表示	*/
		FunctionDisplayBufferHigh[4]  = 'N';		/* NG表示 */
		FunctionDisplayBufferHigh[5]  = 'G';
		break;
	default:
		break;
	}
	switch (PS2_result) {
	case TRUE:					/* ＯＫ表示	*/
		FunctionDisplayBufferHigh[11]  = 'O';		/* OK表示 */
		FunctionDisplayBufferHigh[12]  = 'K';
		break;										
	case FALSE:					/* ＮＧ表示	*/
		FunctionDisplayBufferHigh[11]  = 'N';		/* NG表示 */
		FunctionDisplayBufferHigh[12]  = 'G';
		break;
	default:
		break;
	}
	switch (PB4_result) {
	case TRUE:					/* ＯＫ表示	*/
		FunctionDisplayBufferHigh[18]  = 	'O';		/* OK表示 */
		FunctionDisplayBufferHigh[19]  = 	'K';
		break;										
	case FALSE:					/* ＮＧ表示	*/
		FunctionDisplayBufferHigh[18]  =	 'N';		/* NG表示 */
		FunctionDisplayBufferHigh[19]  =	 'G';
		break;
	default:
		break;
	}
	/* 上段表示 */
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
}
#endif

/*************************************************************************
	module		:[大分用ＲＳ２３２Ｃチェッカー]
	function	:[
		1.折り返しテストのみを実行
		2.ＯＫの時、ピッ、ピッ、ピッ・・・・・と電源を切るまで鳴り続ける。
		  ＮＧの時、ピーーーーーーー・・・・・と電源を切るまで鳴り続ける。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*B-H]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/07/15]
	author		:[松隈]
*************************************************************************/
#if (0)
//void SF_RS232CTestFunction(void)
//{
//#if (PRO_CLASS1 == ENABLE)
//	UBYTE	hex_code;	/* RS232Cﾃｽﾄﾃﾞｰﾀ */
//	MESSAGE_t *WaitData;	/* ﾒｯｾｰｼﾞ */
//	MESSAGE_t *wait_sub;	/* ﾒｯｾｰｼﾞ待避変数 */
//
//	if (SYS_RS232C_Exist == 0) { /* RS232C基盤がない 1996/03/12 Eguchi */
//		NackBuzzer();
//		return;
//	}
//
//		hex_code = 'A';
//
//		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
//
//		if (hex_code != 0) {
//			/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 Eguchi */
//			OperationMessageToMain.Message = MSG_SERV_RS232C_TEST;
//			OperationMessageToMain.SubMessage1 = hex_code;
//			snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
//			MainTaskExecWait();
//			for (;;) {
//				rcv_msg( mbxno.OPR_Task, &WaitData );
//				wait_sub = WaitData;
//				if ( wait_sub->Item == FROM_MAIN && wait_sub->Message == CL1_RS232C_TEST_END ) {
//					break;
//				}
//			}
//
//			if ( wait_sub->SubMessage1 != CHECK_OK ) {
//				while (1) {
//					SpeakerOutBuzzer();							/** スピーカー出力をブザー側に切り替える　*/
//					BuzzerVolumeControl();						/** ボリュームセット */
//					SpeakerMuteOff();							/** スピーカーのミュート状態を解除する */
//					SCN_SetBuzzerFrequency(SCN_BUZZER_1950HZ);
//					SCN_SetBuzzer(SCN_ENABLE);
//				}
//			}
//			else {
//				while(1) {
//					AckBuzzer();
//					wai_tsk( 20 );
//				}
//			}
//		}
//#else
//	NackBuzzer();
//#endif
//}
#endif

#if (0)			/* チェッカーのみ 97/09/10 By M.Kuwahara */
/*************************************************************************
	module		:[カセット１／２テスト]
	function	:[
		1.カセット１／２を選択
		2.カセットの状態を取得
		3.ストップキーが押されたら終了
		4.カセット２の時、温度も表示
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*C]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/23]
	author		:[桑原美紀]
*************************************************************************/
//void SF_CassetteCheck(void)
//{
//#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)
//	UBYTE key;
//	UBYTE keytype;
//	UBYTE cassette;
//
//	/* "ｶｾｯﾄﾃｽﾄ             " */
//	DisplayStringHigh(0,D2W_SF_CassetteCheck);
//	ClearDisplayLow();
//	cassette	= PRN_NO_CASSETTE;
//	while(1) {
//		OPR_GetKey(KEY_WAIT_FOREVER);
//		key = GetInputKeyCode();
//		keytype = GetInputKeyType();
//		switch (keytype) {
//		case ONETOUCH:
//#if (PRO_KEYPANEL == PANEL_ANZU_L)
//			if ((key >= ONETOUCH_A_KEY) && (key <= ONETOUCH_B_KEY)) {
//				switch (key) {
//				case ONETOUCH_A_KEY:	/* カセット１ */
//					cassette	= PRN_1ST_CASSETTE;
//					break;
//				case ONETOUCH_B_KEY:	/* カセット２ */
//					cassette	= PRN_2ND_CASSETTE;
//					break;
//				}
//			}
//#else
//			if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_02_KEY)) {
//				switch (key) {
//				case ONETOUCH_01_KEY:	/* カセット１ */
//					cassette	= PRN_1ST_CASSETTE;
//					break;
//				case ONETOUCH_02_KEY:	/* カセット２ */
//					cassette	= PRN_2ND_CASSETTE;
//					break;
//				}
//			}
//#endif
//			else {
//				NackBuzzer();
//				break;
//			}
//			break;
//		case STOP:
//			return;
//		case NO_EFFECT:
//			break;
//		default:
//			NackBuzzer();
//			break;
//		}
//		if( cassette != PRN_NO_CASSETTE ){		/* カセットを選択したら抜ける */
//			break;
//		}
//	}
//
//	while( 1 ){									/* カセットの状態表示 */
//		DisplayCassetteCheck( cassette );
//		OPR_GetKey(KEY_WAIT_ONE_SECOND);
//		key = GetInputKeyCode();
//		keytype = GetInputKeyType();
//		switch (keytype) {
//		case STOP:
//			return;
//		case NO_EFFECT:
//		case KEY_TIME_UP:
//			break;
//		default:
//			NackBuzzer();
//			break;
//		}
//	}
//#endif
//}
*************************************************************************
	module		:[カセットテストの表示]
		1.カセット状態を表示
			SYS_NO_CASSETTE
			SYS_NO_PAPER
			SYS_NO_UNIT
			SYS_SIDE_COVER_OPEN
			SYS_B4_PAPER
			SYS_A4_PAPER
			SYS_B5R_PAPER
			SYS_A5R_PAPER
			SYS_LT_PAPER
			SYS_LG_PAPER
			SYS_F4_PAPER
		2.カセット２の時、温度も表示
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*C]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/06/23]
	author		:[桑原美紀]
*************************************************************************/
//void	DisplayCassetteCheck(
//				UBYTE cassette )
//{
//#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI)
//	WORD	temp;		/* 温度 */
//
//	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
//	/* "                20ﾟC" */
//	if( cassette == PRN_1ST_CASSETTE ){
//		temp = PRN_CalculateDispEnvTemp();
//		if (temp >= 0) {
//			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[16], temp, 2, '0');
//		}
//		else {
//			FunctionDisplayBufferHigh[15] = '-';
//			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[16], (UWORD)(0 - temp), 2, '0');
//		}
//#if defined(JPN)
//		FunctionDisplayBufferHigh[18]	= 0xDF;		/* 'ﾟ' */
//#else
//		FunctionDisplayBufferHigh[18]	= 0xCF;		/* 'ﾟ' */
//#endif
//		FunctionDisplayBufferHigh[19]	= 'C';
//	}
//
//	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
//	switch(PRN_CheckPaperSize(cassette)){			/* カセットの状態を取得 */
//	case	SYS_NO_CASSETTE:
//		CMN_StringCopy(FunctionDisplayBufferLow,D2W_SF_CassetteOpen);
//		break;
//    case	SYS_NO_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_SF_NoPaper);
//		break;
//    case	SYS_NO_UNIT:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_SF_NoUnit);
//		break;
//    case	SYS_SIDE_COVER_OPEN:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_SF_SideCoverOpen);
//		break;
//    case	SYS_B4_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_B4);
//		break;
//    case	SYS_A4_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_A4);
//		break;
//    case	SYS_B5R_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_B5R);
//		break;
//    case	SYS_A5R_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_A5R);
//		break;
//    case	SYS_LT_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_Letter);
//		break;
//    case	SYS_LG_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_Legal);
//		break;
//    case	SYS_F4_PAPER:
//		CMN_StringCopy(FunctionDisplayBufferLow, D2W_PaperSize_F4);
//		break;
//	}
//	ClearDisplayHigh();
//	DisplayStringHigh(0,FunctionDisplayBufferHigh);
//	ClearDisplayLow();
//	DisplayStringLow(0,FunctionDisplayBufferLow);
//#endif
//}
#endif	/* if(0) */

#if defined (KEISATSU) /* 警察FAX 05/12/13 石橋正和 */
/**************************************************************************************************/
/**
	@brief		ワンタッチAの内容をすべてのワンタッチ、短縮にコピーする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/12/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void SF_CopyOnetouchA_ToAll(void)
{
	UBYTE key;
	UBYTE keytype;
	UWORD i;
	
	DisplayStringHigh(0, D2W_SF_CopyOnetouchA_ToAll);	/* "ﾜﾝﾀｯﾁﾃﾞｰﾀ ﾌｨﾙ       " */
	FlashDisplayStringLow(D2W_EnterStop);				/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */
	
	while(1) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE); /** キー取り込み */
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		
		switch (keytype) {
		case ENTER:
			for (i = 1; i < SYS_ONETOUCH_MAX; i++) {
				MemoryMove(&SYB_OnetouchDial[i], &SYB_OnetouchDial[0], sizeof(struct SYS_SpeedDialData_t));
			}
			for (i = 0; i < SYS_SPEED_DIAL_MAX; i++) {
				MemoryMove(&SYB_SpeedDial[i], &SYB_OnetouchDial[0], sizeof(struct SYS_SpeedDialData_t));
			}
			ChildDisplayStringLow(D2W_SetComplete);
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/**************************************************************************************************/
/**
	@brief		減衰量可変トーナルテスト
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/12/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void SF_TonalTestWithVariableAtt(
							UWORD kind,		/* テスト項目 */
							UWORD pattern,	/* PIXの場合のパターン */
							UBYTE* ptitle)	/* 表示ワーディング */
{
	UBYTE line;
	UBYTE key;
	UBYTE keytype;
	UBYTE attenuation;
	UBYTE val[3];
	
	line = 0;
	
	DisplayStringHigh(0, ptitle);
	DisplayStringHigh(15, D2W_Keiden);
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */
	
	while(1) {
		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (line == 0) {
				DisplayStringHigh(15, D2W_Kanyu);
				line = 1;
			}
			else {
				DisplayStringHigh(15, D2W_Keiden);
				line = 0;
			}
			break;
		case ENTER:
			goto NEXT;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
	
NEXT:
	if (line == 0) {
		DisplayStringHigh(0, D2W_Keiden);
	}
	else {
		DisplayStringHigh(0, D2W_Kanyu);
	}
	
	attenuation = 8;
	CMN_UnsignedIntToASC_NULL(val, (UWORD)attenuation, 2, ' ');
	
	ClearDisplayLow();
	DisplayStringLow(18, "dB");
	DisplayStringLow(16, val);
	
	tskno_MDM_FactoryTask == 0xFFFF;
	SYS_FactoryFuncReq = 0;
	SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_START;
	SYS_FactoryModem.Kind = 0xFF;
	SYS_FactoryModem.BaudRate = 0xFF;
	SYS_FactoryModem.DataRate = 0xFF;
	SYS_FactoryModem.PIX_Pattern = 0xFF;
	if (tskno_NCU_Task != 0xFFFF) {
		del_tsk(&tskno_NCU_Task);/* Add J.M 1994/05/12 */
	}
	cre_tsk(&tskno_MDM_FactoryTask, TSK_MDM_FACTORYFUNCTIONTASK, 0);
	LineFuncTxMsg.Item = FROM_OPERATION;
	LineFuncTxMsg.Message = FIP_TEST_CMD;
	snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
	
	if (line == 0) {
		SYS_FactoryModem.Item = SYS_OPT_MDM_KEIDEN_TONAL_TEST;
	}
	else {
		SYS_FactoryModem.Item = SYS_OPT_MDM_TONAL_TEST;
	}
	SYS_FactoryModem.Kind = kind;
	SYS_FactoryModem.PIX_Pattern = pattern;
	
	snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
	do {
		rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
	} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
	
	MDM_TransmitLevelSet(attenuation);
	
	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		
		switch (keytype) {
		case PROGRAM:
			if ((key != OPR_TOP_PROGRAM_KEY) && (key != (OPR_TOP_PROGRAM_KEY + 1))) {
				NackBuzzer();
				continue;
			}
			
			if (key == OPR_TOP_PROGRAM_KEY) { /* プログラムワンタッチ1 */
				if (attenuation < 15) {
					attenuation++;
				}
				else {
					NackBuzzer();
				}
			}
			else { /* プログラムワンタッチ2 */
				if (attenuation == 8) {
					attenuation = 15;
				}
				else {
					attenuation = 8;
				}
			}
			MDM_TransmitLevelSet(attenuation);
			
			CMN_UnsignedIntToASC_NULL(val, (UWORD)attenuation, 2, ' ');
			DisplayStringLow(16, val);
			break;
		case STOP:
			goto END;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
	
END:
	SYS_FactoryModem.Kind = OPT_MDM_TONAL_STOP;
	snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
	do {
		rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
	} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
	
	SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_END;
	MDM_TxStopSwFlag = 0;
	if (tskno_MDM_FactoryTask != 0xFFFF) {
		del_tsk(&tskno_MDM_FactoryTask);
	}
	cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
}
#endif

#if (PRO_MODEM == ORANGE3) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[回線テスト]
	function	:[
		1.回線まわりのテストを行う
		2.リレーテスト
		3.トーナルテスト
		4.ＤＴＭＦテスト
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG*C]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口,渡辺一章]
*************************************************************************/
void LineFunctionMode(void)
{
	UBYTE	keytype;
	UBYTE	func_number;

	func_number = 0;

	while (1) {

		DisplayStringHigh(0, D2W_SF_PhoneTest + (OPR_WORDING_LEN * func_number));
		ClearDisplayLow();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:
			func_number++;
			if (func_number > 2) {
				func_number = 0;
			}
			break;
		case ENTER:
			/* メインにＮＣＵタスクを殺してもらう（日本仕様で、ﾄｰﾅﾙﾃｽﾄの1300Hzを送出すると着信してしまうため） */
			OperationMessageToMain.Message = MSG_SERV_START;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();

			if (CHK_LineMonitor()) {
				MonitorSpeakerOn();
			}

			if (func_number == 0) {
				SF_RelayTest();	/* リレーテスト */
			}
			if (func_number == 1) {
				SF_TonalTest();	/* トーナルテスト */
			}
			if (func_number == 2) {
				SF_DTMF_Test();	/* ＤＴＭＦテスト */
			}

			MonitorSpeakerOff();

			/* メインにＮＣＵタスクを生成してもらう */
			OperationMessageToMain.Message = MSG_SERV_END;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[リレーテスト]
	function	:[
		1.指定されたリレーのＯＮ／ＯＦＦを行う。
		2.キー入力とリレーの対応関係は以下のようになる。
		,	ONETOUCH_A_KEY -> CML
		,	ONETOUCH_B_KEY -> H
		,	ONETOUCH_C_KEY -> L
		,	ONETOUCH_D_KEY -> S
		,	ONETOUCH_E_KEY -> DP
		,	ONETOUCH_F_KEY -> C24

		3.国別によるリレー
		,	USA: CML ○
		,		 H	 ○	(HリレーをON/OFFするとLリレーもON/OFFされる)
		,		 L	 × (Lリレーはない)
		,		 S	 ○
		,		 DP	 × (DPリレーはない。パルス送出時はCMLリレーがON/OFFされる)
		,		 C24 ○
		,
		,	GBR: CML ○
		,		 H	 ○	(HリレーをON/OFFするとLリレーもON/OFFされる)
		,		 L	 × (Lリレーはない)
		,		 S	 ○
		,		 DP	 ○
		,		 C24 ○
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口,渡辺一章]
************************************************************************/
void SF_RelayTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	init_status;

	init_status = SYS_Modem1PortStatus;

	while (1) {
		DisplayRelayTest();
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ONETOUCH:
			/* 指定されたリレーのＯＮ／ＯＦＦを行う */
			switch (key) {
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			case ONETOUCH_01_KEY:	/* CML */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			case ONETOUCH_A_KEY:	/* CML */
#endif
				if (CML_RelaySetting()) {
					CML_RelayOff();
				}
				else {
					CML_RelayOn();
				}
				break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			case ONETOUCH_02_KEY:	/*  H  */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			case ONETOUCH_B_KEY:	/*  H  */
#endif
				if (H_RelaySetting()) {
					H_RelayOff();
				}
				else {
					H_RelayOn();
				}
				break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			case ONETOUCH_03_KEY:	/*  L  */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			case ONETOUCH_C_KEY:	/*  L  */
#endif
/*#if defined(USA) || defined(TWN) 1998/01/21 */
/*#if (PRO_NCU_TYPE == ANZU_USA_TYPE)*/
#if (PRO_NCU_TYPE == ANZU_USA_TYPE)	/* 1998/01/21 */
				NackBuzzer();
#else
				if (L_RelaySetting()) {
					L_RelayOff();
				}
				else {
					L_RelayOn();
				}
#endif
				break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			case ONETOUCH_04_KEY:	/*  S  */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			case ONETOUCH_D_KEY:	/*  S  */
#endif
				if (S_RelaySetting()) {
					S_RelayOff();
				}
				else {
					S_RelayOn();
				}
				break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			case ONETOUCH_05_KEY:	/*  DP */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			case ONETOUCH_E_KEY:	/*  DP */
#endif
/*#if defined(USA) || defined(TWN) 1998/01/21 */
/*#if (PRO_NCU_TYPE == ANZU_USA_TYPE)*/
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)	/* 1998/01/21 */
				if (DP_RelaySetting()) {
					DP_RelayOff();
				}
				else {
					DP_RelayOn();
				}
#else
				NackBuzzer();
#endif
				break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
			case ONETOUCH_06_KEY:	/* C24 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			case ONETOUCH_F_KEY:	/* C24 */
#endif
				if (CONT24_Setting()) {
					CONT_24V_Off();
				}
				else {
					CONT_24V_On();
				}
				break;
			}
			break;
		case STOP:
			/* リレーをもとの状態に戻して終了する */
			SYS_Modem1PortStatus = init_status;
			outp(MODEM1_PORT, SYS_Modem1PortStatus); /*まずいかも*/
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[リレーテスト中の表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/23]
	author		:[江口,渡辺一章]
*************************************************************************/
void DisplayRelayTest(void)
{
	DisplayStringHigh(0, D2W_SF_RelayTest1);	/* [ CML  H  L  S  DP   ] */
	DisplayStringLow(0, D2W_SF_RelayTest2);		/* [ C24                ] */

	if (CML_RelaySetting()) {
		DisplayChar(0, '*');
	}
	if (H_RelaySetting()) {
		DisplayChar(5, '*');
	}
	if (L_RelaySetting()) {
		DisplayChar(8, '*');
	}
	if (S_RelaySetting()) {
		DisplayChar(11, '*');
	}
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE) /* ＤＰリレー関数でなぜかＣＭＬをみているため 1997/10/15 Y.Matsukuma */
	if (DP_RelaySetting()) {
		DisplayChar(14, '*');
	}
#endif
	if (CONT24_Setting()) {
		DisplayChar(20, '*');
	}
}

/*************************************************************************
	module		:[トーナルテスト]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口]
*************************************************************************/
void SF_TonalTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	type;
	UBYTE	tx_signal;	/* 0:無信号 1:トーン 2:ＦＳＫ 3:画信号 */
	UBYTE	tx_freq;	/* トーン：周波数 , ＦＳＫ：黒or白、画信号：交信スピード */
	UBYTE	w_b_rate;	/* 画信号送出時、白黒比率 */
	struct ServiceFuncPixData_t PixData;

	tx_signal = tx_freq = w_b_rate = 0;
	tskno_txtask = 0xFFFF; /* TID Initial */

	/* リレーをひく */
	ConnectLine();

	while (1) {
		DisplayTonalTest(tx_signal , tx_freq , w_b_rate);
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ONETOUCH:
			if ((type = TxSignalType(key)) != 0xFF) {
				if (tx_signal == 2 || tx_signal == 3) { /* PIX/FSK信号送出中 */
					FskPixStop();
				}
				tx_freq = TxSignalFreq(type , key);
				MDM_ConfigReset();

				if (type == 1) { /* トーン */
					MDM_Tone(tx_freq);
				}
				if (type == 2) {
					cre_tsk(&tskno_txtask, TSK_MDM_FSKTXTASK, &tx_freq);
				}
				if (type == 3) {
					w_b_rate = W1_B0;
					PixData.baud_rate = tx_freq;
					PixData.pix_retio = w_b_rate;
					cre_tsk(&tskno_txtask, TSK_MDM_PIXTXTASK, &PixData);
				}
				tx_signal = type;
			}
			else {
				NackBuzzer();
			}
			break;
		case FUNCTION:
			if (tx_signal == 3) { /* PIX送出中 */
				FskPixStop();
				MDM_ConfigReset();
				tx_signal = 3;
				w_b_rate++;
				if (w_b_rate > W4_B1) {
					w_b_rate = W1_B0;
				}
				PixData.pix_retio = w_b_rate;
				cre_tsk(&tskno_txtask, TSK_MDM_PIXTXTASK, &PixData);
			}
			else {
				NackBuzzer();
			}
			break;
		case STOP:
			if (tx_signal == 2 || tx_signal == 3) { /* FSK送出中 或いは ＰＩＸ送出中 */
				FskPixStop();
				tx_signal = 0;
			}
			else if (tx_signal == 1) {	/* トーン送出中 */
				MDM_ConfigReset();
				tx_signal = 0;
			}
			else {	/* 無信号状態 */
				MDM_ConfigReset();
				DisconnectLine();
				return;
			}
			break;

		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[トーナルテスト：信号タイプ判別]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/29]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE TxSignalType(UBYTE key)
{
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	if (key == ONETOUCH_01_KEY) {		/* ONETOUCH_01_KEY                   */
		return (0);	/* 無信号状態 */
	}
	else if (key <= ONETOUCH_09_KEY) {	/* ONETOUCH_02_KEY - ONETOUCH_09_KEY */
		return (1);
	}
	else if (key <= ONETOUCH_11_KEY) {	/* ONETOUCH_10_KEY - ONETOUCH_11_KEY */
		return (2);
	}
	else if (key <= ONETOUCH_19_KEY) {	/* ONETOUCH_12_KEY - ONETOUCH_19_KEY */
		return (3);
	}
	return (0xFF);
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	if (key == ONETOUCH_A_KEY) {		/* ONETOUCH_A_KEY                  */
		return (0);	/* 無信号状態 */
	}
	else if (key <= ONETOUCH_I_KEY) {	/* ONETOUCH_B_KEY - ONETOUCH_I_KEY */
		return (1);
	}
	else if (key <= ONETOUCH_K_KEY) {	/* ONETOUCH_J_KEY - ONETOUCH_K_KEY */
		return (2);
	}
	else if (key <= ONETOUCH_S_KEY) {	/* ONETOUCH_L_KEY - ONETOUCH_S_KEY */
		return (3);
	}
	return (0xFF);
#endif
}

/*************************************************************************
	module		:[トーナルテスト：信号周波数判別]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/29]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE  TxSignalFreq(UBYTE type, UBYTE key)
{
	UBYTE	freq;

	freq = 0xFF;

	switch (type) {
	case 0:	/* 無信号 */
		break;
	case 1:	/* トーナル */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		freq = (UBYTE)(TONE_462HZ + (UBYTE)(key - ONETOUCH_02_KEY));
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		freq = (UBYTE)(TONE_462HZ + (UBYTE)(key - ONETOUCH_B_KEY));
#endif
		break;
	case 2:	/* ＦＳＫ */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		freq = (UBYTE)(FSK_WHITE + (UBYTE)(key - ONETOUCH_10_KEY));
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		freq = (UBYTE)(FSK_WHITE + (UBYTE)(key - ONETOUCH_J_KEY));
#endif
		break;
	case 3:	/* ＰＩＸ */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		freq = (UBYTE)(PIX_2400BPS + (UBYTE)(key - ONETOUCH_12_KEY));
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
		freq = (UBYTE)(PIX_2400BPS + (UBYTE)(key - ONETOUCH_L_KEY));
#endif
		break;
	}
	return (freq);
}

/*************************************************************************
	module		:[ＦＳＫ／画信号送出停止]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/28]
	author		:[江口]
*************************************************************************/
void FskPixStop(void)
{
	MESSAGE_t *rx_message;

	SYS_PixStopFlag = 1;
	rcv_msg(mbxno.OPR_Task , &rx_message);
	if (tskno_txtask != 0xFFFF) {
		del_tsk(&tskno_txtask);
	}
	SYS_PixStopFlag = 0;
}

/*************************************************************************
	module		:[トーナルテスト中の表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[ワーディング容量節約のため、固定ワーディングをできるだけはずし実行時に表示文字列を作成
				　するようにする。　1996/06/12　Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/28]
	author		:[江口]
*************************************************************************/
void DisplayTonalTest(UBYTE tx_signal, UBYTE freq, UBYTE w_b_rate)
{
	UWORD	data;
	UBYTE	pix_rate[4];
	UBYTE	disp_buf[7];

	data = 0;
	CMN_MemorySet(disp_buf, 7, NULL);

	/* 上段表示 */
	switch (tx_signal) {

	/*-------------*/
	/* 無信号状態　*/
	/*-------------*/
	case 0:	/* 無信号 */
		ClearDisplayHigh(); /* 空白 */
		break;

	/*--------------------*/
	/* トーナル信号送出中 */
	/*--------------------*/
	case 1:	/* トーン */
		switch (freq) {
		case TONE_462HZ:
			data = 462;
			break;
		case TONE_1080HZ:
			data = 1080;
			break;
		case TONE_1300HZ:
			data = 1300;
			break;
		case TONE_1650HZ:
			data = 1650;
			break;
		case TONE_1700HZ:
			data = 1700;
			break;
		case TONE_1800HZ:
			data = 1800;
			break;
		case TONE_1850HZ:
			data = 1850;
			break;
		case TONE_2100HZ:
			data = 2100;
			break;
		}
		CMN_UnsignedIntToASC(disp_buf, data, 4, ' ');
		disp_buf[4] = 'H';
		disp_buf[5] = 'z';
		ClearDisplayHigh();
		DisplayStringHigh(0, disp_buf);
		break;

	/*----------------------*/
	/* ＦＳＫ信号送出中		*/
	/*----------------------*/
	case 2:	/* FSK	  */
		ClearDisplayHigh();
		DisplayStringHigh(0 , D2W_SF_FSK);
		if (freq == FSK_WHITE) {
			DisplayStringHigh(4 , D2W_SF_White);
		}
		if (freq == FSK_BLACK) {
			DisplayStringHigh(4 , D2W_SF_Black);
		}
		break;

	/*---------------------*/
	/* 画信号送出中		   */
	/*---------------------*/
	case 3:	/* PIX	  */
		switch (freq) {
		case PIX_2400BPS:
			data = 2400;
			break;
		case PIX_4800BPS:
			data = 4800;
			break;
		case PIX_7200BPS_V29:
		case PIX_7200BPS_V17:
			data = 7200;
			break;
		case PIX_9600BPS_V29:
		case PIX_9600BPS_V17:
			data = 9600;
			break;
		case PIX_12000BPS_V17:
			data = 12000;
			break;
		case PIX_14400BPS_V17:
			data = 14400;
			break;
		}
		CMN_UnsignedIntToASC(disp_buf, data, 5, ' ');

		pix_rate[0] = '1';
		pix_rate[1] = ':';
		pix_rate[2] = '1';
		pix_rate[3] = '\0';

		switch (w_b_rate) {
		case W1_B0: /* [1:0] */
			pix_rate[2] = '0';
			break;
		case W1_B1: /* [1:1] */
			break;
		case W1_B4: /* [1:4] */
			pix_rate[2] = '4';
			break;
		case W0_B1: /* [0:1] */
			pix_rate[0] = '0';
			break;
		case W4_B1: /* [4:1] */
			pix_rate[0] = '4';
			break;
		}
		DisplayStringHigh(0, D2W_SF_Pix);
		DisplayStringHigh(0, disp_buf);
		DisplayStringHigh(17, pix_rate);
	}

	/* 下段クリア */
	ClearDisplayLow();
}

/*************************************************************************
	module		:[ＤＴＭＦテスト]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口]
*************************************************************************/
void SF_DTMF_Test(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	dtmf;

	dtmf = 0xFF;

	/* リレーをひく */
	ConnectLine();

	while (1) {

		/* 表示 */
		DisplayTxDTMF(dtmf);

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
		case AST:
		case SHARP:
		case ONETOUCH:
			dtmf = DTMF_TypeGet(key);
			if (dtmf != 0xFF) {
				MDM_ConfigReset();
				MDM_DTMF(dtmf);
			}
			else {
				NackBuzzer();
			}

			break;
		case STOP:
			if (dtmf != 0xFF) { /* ＤＴＭＦ送出中 */
				MDM_ConfigReset();
				dtmf = 0xFF;
			}
			else {
				DisconnectLine();
				return;
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[ＤＴＭＦテスト中の表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/27]
	author		:[江口]
*************************************************************************/
void DisplayTxDTMF(UBYTE dtmf)
{
	ClearDisplayHigh();
	ClearDisplayLow();

	if (dtmf == 0xFF) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
	}
	if (DTMF_0 <= dtmf && dtmf <= DTMF_9) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , dtmf | 0x30);
	}
	if (dtmf == DTMF_SHARP) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , '#');
	}
	if (dtmf == DTMF_ASTA) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , '*');
	}

	if (ROW_1 <= dtmf && dtmf <= ROW_4) {
		DisplayStringHigh(0, D2W_SF_DTMFRow);
		DisplayChar(5, (UBYTE)((dtmf - ROW_1) + 1) | 0x30);
	}
	if (COL_1 <= dtmf && dtmf <= COL_4) {
		DisplayStringHigh(0, D2W_SF_DTMFColum);
		DisplayChar(5, (UBYTE)((dtmf - COL_1) + 1) | 0x30);
	}
}

/*************************************************************************
	module		:[ＤＴＭＦテスト：送出ＤＴＭＦ選択]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/29]
	author		:[江口,渡辺一章]
*************************************************************************/
UBYTE DTMF_TypeGet(UBYTE key)
{
	UBYTE dtmf;

	dtmf = 0xFF;

	if (TEN_0_KEY <= key && key <= TEN_9_KEY) {
		dtmf = (UBYTE)(key - 0x30);
	}
	else if (key == TEN_SHARP_KEY) {
		dtmf = DTMF_SHARP;
	}
	else if (key == TEN_AST_KEY) {
		dtmf = DTMF_ASTA;
	}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	else if (ONETOUCH_01_KEY <= key && key <= ONETOUCH_08_KEY) {
		dtmf = (UBYTE)(ROW_1 + (UBYTE)(key - ONETOUCH_01_KEY));
	}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	else if (ONETOUCH_A_KEY <= key && key <= ONETOUCH_H_KEY) {
		dtmf = (UBYTE)(ROW_1 + (UBYTE)(key - ONETOUCH_A_KEY));
	}
#endif
	return (dtmf);
}

/*************************************************************************
	module		:[リレーをつなぐ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/29]
	author		:[江口]
*************************************************************************/
void ConnectLine(void)
{
/*#if defined(GBR) 1998/01/21 */
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
	DP_RelayOn();
	wai_tsk(1);
#endif
	CML_RelayOn();
	wai_tsk(100);
	H_RelayOn();
	L_RelayOn();

}

/*************************************************************************
	module		:[リレーをはなす]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/02/29]
	author		:[江口]
*************************************************************************/
void DisconnectLine(void)
{
	CML_RelayOff();
/*#if defined(GBR) 1998/01/21 */
#if (PRO_NCU_TYPE == ANZU_GBR_TYPE)
	wai_tsk(1);
	DP_RelayOff();
#endif
	H_RelayOff();
	L_RelayOff();
}
#endif	/* (PRO_MODEM != R288F) */

void InvalidServiceFunction(void)
{
	NackBuzzer();
}

/*************************************************************************
	module		:[リングマスターパターン自動検出機能]
	function	:[
		1.リングマスターパターンの自動検出を行う
		2.ＴＥＬ待機でかつパターンとしてＧ／Ｈが選択されている時に限る
		3.ＲＯＭパッチでリングマスターパターン自動検出有効がセットされている時に限る
		4.基本的に検出パターンは表示しない
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/03/21]
	author		:[江口]
*************************************************************************/
void TeachingRingPattern(void)
{
#if (PRO_RING_MASTER == ENABLE)
	UBYTE	ring_pattern;
	UBYTE	pattern_display;
	UBYTE	keytype;
	UBYTE	during_teaching;

	#if defined(AUS)	/* DUET 1997/05/21 Y.Murata */
		NackBuzzer();
		return;
	#endif

	pattern_display = 0;
	ring_pattern = CHK_RingMasterPattern();

	if (TeachingOperationEnable == 0) { /* 自動検出オペレーション無効 */
		NackBuzzer();
		return;
	}

	if ((CMN_PresentReceiveMode() != SYS_TEL_READY) /* 電話待機でない */
	||	(ring_pattern != RING_MASTER_PATTERN_7 && ring_pattern != RING_MASTER_PATTERN_8)) {/* パターンがＧ／Ｈ以外である */
		NackBuzzer();
		return;
	}

	/* 上の条件に更に、メモリースイッチ設定状態による判断が入るかも 1996/03/21 Eguchi まだ!!*/


	/*　自動検出要求フラグセット */
	SYS_TeachingModeFlag = 1;
	ring_pattern -= RING_MASTER_PATTERN_7;


	/* 画面表示 */
	if (pattern_display == 0) {/* パターン表示しない */
		/* [                    ] */
		/* [Please Wait         ] */
		ClearDisplayHigh();
		DisplayStringLow(0 , D2W_PleaseWaitAMinute);
	}
	else {/* パターン表示する */
		/* 前回の表示パターンの表示 */
		/* [000 000 000 000 000 ] */
		/* [                    ] */
		DisplayTeachingPattern(ring_pattern);
	}

	during_teaching = 1;
	while (during_teaching) {
		OPR_GetKey(KEY_WAIT_ONE_SECOND);
		keytype = GetInputKeyType();
		switch (keytype) {
		case STOP:	/* ストップキー */
			SYS_TeachingModeFlag = 0; /* 自動検出終了 */
			during_teaching = 0;
			break;
		case KEY_TIME_UP:
			if (SYS_TeachingModeFlag == 0) {/* 自動検出終了 */
				during_teaching = 0;
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}

	if (keytype == KEY_TIME_UP) { /* 自動検出終了 */
		if (pattern_display == 0) { /* 結果表示をしない */
			ChildDisplayStringLow(D2W_SetComplete);
		}
		else { /* 結果表示を行う */
			/* ストップキーが押されるまで結果表示を行う */
			/* [000 000 000 000 000 ] */
			/* [                    ] */
			DisplayTeachingPattern(ring_pattern);
			while (keytype != STOP) {
				OPR_GetKey(KEY_WAIT_FOREVER);
				keytype = GetInputKeyType();
				if ((keytype != STOP)
				&&	(keytype != NO_EFFECT)) {
					NackBuzzer();
				}
			}
		}
	}

	SYS_RingCounter = 0;
#else
	NackBuzzer();
#endif
}

#if (PRO_RING_MASTER == ENABLE)
void DisplayTeachingPattern(UBYTE pattern)
{
	UBYTE	i;

	for (i = 0; i < 5; i++) { /* 前半５つのみ */
		CMN_HexToASC(&FunctionDisplayBufferHigh[i * 4], (UDWORD)SYB_TeachingPattern[pattern].RingMinCycle[i], 3);
	}
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	ClearDisplayLow();
}
#endif

/*************************************************************************
	module		:[ミラーキャリッジ輸送モードセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/01]
	author		:[渡辺一章]
*************************************************************************/
void SetMirrorCarrigeTransMode(void)
{
	UBYTE	trans_mode;

	trans_mode = SYB_ScannerTransportMode;

	if (SelectData(D2W_SF_MirrorCarrigeModeSet,	/* "ﾐﾗｰｷｬﾘｯｼﾞﾕｿｳﾓｰﾄﾞ:   " */
				   D2W_Off3,					/* "                 OFF" */
				   2,
				   &trans_mode,
				   TRUE,
				   NO_KEYTYPE) == OPR_ENTERED) {	/* SelectData() 引数追加 By S.Fukui Oct.1,1997 */
		/* スキャナ使用中は、設定を禁止します（但し輸送ﾓｰﾄﾞがONの時は、ｽｷｬﾅ使用中はONです） by K.Watanabe 1997/12/26 */
		if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)	/* スキャナ使用中の時 */
		 && (SYB_ScannerTransportMode == FALSE)) {						/* ミラーキャリッジ輸送モードがＯＦＦの時 */
			NackBuzzer();
		}
		else {															/* スキャナ未使用か、輸送モードがＯＮの時 */
			/* 注）SYB_ScannerTransportModeのON/OFFは、メインで行います */
			if (trans_mode == TRUE) {	/* ONにセットされた時 */
				OperationMessageToMain.Message = MSG_FBS_TRANSPORT_SET;
			}
			else {						/* OFFにセットされた時 */
				OperationMessageToMain.Message = MSG_FBS_TRANSPORT_RESET;
			}
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
		}
	}
}

/*************************************************************************
	module		:[消耗品発注機能]
	function	:[
		1.消耗品発注データの登録・印字を行う。
		2.消耗品発注用紙の印字を行う。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
void ConsumptionArticleOrderFunc(void)
{
#if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/01/06 */
	/** シリアルＮｏ．入力 */
	DisplayStringHigh(0, D2W_SF_SerialNumber);	/* "ｼﾘｱﾙNo.             " */
	if (SerialNumberInput() == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(SYB_ConsumerOrder.SerialNumber, ASC_DATA_TYPE);
	}
#else
	/*----------------------*/
	/** 発注データの登録	*/
	/*----------------------*/
	if (EnterConsumerOrder() == NG) {
		return;	/* 編集中にスットプキーが押された */
	}

	/*----------------------*/
	/** 発注用紙のプリント 	*/
	/*----------------------*/
	if (PrintConsumerOrderForm() == NG) {
		return;	/* 編集中にスットプキーが押された */
	}
#endif
}

/*************************************************************************
	module		:[消耗品発注データ登録機能]
	function	:[
		1.以下の項目を登録する。
		,発注先 得意先コード
		,発注先 社名
		,発注元 得意先コード
		,発注元 社名
		,発注元 部課名
		,発注元 電話番号
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		SYB_ConsumerOrder:
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE EnterConsumerOrder(void)
{

#if defined(JPN)	/* 海外仕様では使用されません By S.Fukui Oct.21,1997 */
	/** 発注先得意先コード入力 */
	DisplayStringHigh(0, D2W_SF_ReceiverCustomerCode);	/* "ｵｸﾘｻｷ ｺｰﾄﾞ          " */
	if (ToCustomerCodeInput() == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(SYB_ConsumerOrder.ToCustomerCode, ASC_DATA_TYPE);
	}
	else {
		return (NG);
	}
#endif

	/** 発注先社名入力 */
	DisplayStringHigh(0, D2W_SF_ReceiverCompany);		/* "ｵｸﾘｻｷ ｼｬﾒｲ          " */
	if (ToCompanyNameInput() == OK) {
		/* 入力データをセット */
#if (PRO_JIS_CODE == ENABLE)
		StoreCharacterInputValue(SYB_ConsumerOrder.ToCompany, ASC_JIS_DATA_TYPE);
#else
		StoreCharacterInputValue(SYB_ConsumerOrder.ToCompany, ASC_DATA_TYPE);
#endif
	}
	else {
		return (NG);
	}

#if !defined(US1)	/* orderbythonda1998/11/11 */
	/** 発注元得意先コード入力 */
	DisplayStringHigh(0, D2W_SF_SenderCustomerCode);	/* "ｵｸﾘﾓﾄ ｺｰﾄﾞ          " */
	if (FromCustomerCodeInput() == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(SYB_ConsumerOrder.FromCustomerCode, ASC_DATA_TYPE);
	}
	else {
		return (NG);
	}
#endif

	/** 発注元社名入力 */
	DisplayStringHigh(0, D2W_SF_SenderCompany);			/* "ｵｸﾘﾓﾄ ｼｬﾒｲ          " */
	if (FromCompanyNameInput() == OK) {
		/* 入力データをセット */
#if (PRO_JIS_CODE == ENABLE)
		StoreCharacterInputValue(SYB_ConsumerOrder.FromCompany, ASC_JIS_DATA_TYPE);
#else
		StoreCharacterInputValue(SYB_ConsumerOrder.FromCompany, ASC_DATA_TYPE);
#endif
	}
	else {
		return (NG);
	}

	/** 発注元部課名入力 */
	DisplayStringHigh(0, D2W_SF_SenderSection);			/* "ｵｸﾘﾓﾄ ﾌﾞｶﾒｲ         " */
	if (FromSectionNameInput() == OK) {
		/* 入力データをセット */
#if (PRO_JIS_CODE == ENABLE)
		StoreCharacterInputValue(SYB_ConsumerOrder.FromSection, ASC_JIS_DATA_TYPE);
#else
		StoreCharacterInputValue(SYB_ConsumerOrder.FromSection, ASC_DATA_TYPE);
#endif
	}
	else {
		return (NG);
	}
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
	/** 発注元部課名２入力 *//* orderbythonda1998/05/18 */
	DisplayStringHigh(0, D2W_SF_SenderSection2);		/* "ｵｸﾘﾓﾄ ﾌﾞｶﾒｲ2        " */
	if (FromSectionName2Input() == OK) {
		/* 入力データをセット */
 #if (PRO_JIS_CODE == ENABLE)
		StoreCharacterInputValue(SYB_ConsumerOrderFromSection2, ASC_JIS_DATA_TYPE);
 #else
		StoreCharacterInputValue(SYB_ConsumerOrderFromSection2, ASC_DATA_TYPE);
 #endif
	}
	else {
		return (NG);
	}
#endif

	/** 発注元電話番号入力 */
	DisplayStringHigh(0, D2W_SF_SenderTelNumber);		/* "ｵｸﾘﾓﾄ ﾃﾞﾝﾜﾊﾞﾝｺﾞｳ    " */
	if (FromCustomerTelNumberInput() == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(SYB_ConsumerOrder.FromTelNumber, ASC_DATA_TYPE);
	}
	else {
		return (NG);
	}

	/** シリアルＮｏ．入力 */
	DisplayStringHigh(0, D2W_SF_SerialNumber);	/* "ｼﾘｱﾙNo.             " */
	if (SerialNumberInput() == OK) {
		/* 入力データをセット */
		StoreCharacterInputValue(SYB_ConsumerOrder.SerialNumber, ASC_DATA_TYPE);
	}
	else {
		return (NG);
	}

#if defined(US1)	/* orderbythonda1998/11/11 */
	/** 発注先Ｆａｘ  Ｎｏ．入力 */
	DisplayStringHigh( 0, D2W_SF_ToCompanyFaxNumber );	/* "Dist. Fax No.             " */
	if ( ToCompanyFaxNumberInput() == OK ) {
		/* 入力データをセット */
		StoreCharacterInputValue( SYB_ToCompanyFaxNumber, ASC_DATA_TYPE );
	}
	else {
		return ( NG );
	}

	/** 発注先Ｔｅｌ  Ｎｏ．入力 */
	DisplayStringHigh( 0, D2W_SF_ToCompanyTelNumber );	/* "Dist. Tel No.             " */
	if ( ToCompanyTelNumberInput() == OK ) {
		/* 入力データをセット */
		StoreCharacterInputValue( SYB_ToCompanyTelNumber, ASC_DATA_TYPE );
	}
	else {
		return ( NG );
	}
#endif	/* if defined(US1) */

#if (0)		/* 設置日はここで登録しない 98/02/27 By M.Kuwahara */
	/** 設置日 */
//	DisplayStringHigh(0, D2W_SF_Date);			/* "ｾｯﾁﾋﾞ               " */
//	if (SetDateInput() == NG) {	/* STOP */
//		return(NG);
//	}
#endif
	return (OK); /* 終了 */
}

/*************************************************************************
	module		:[発注先得意先コード入力]
	function	:[
		1.発注先得意先コードの登録を行う。
		2.発注先得意先コードは１０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.ToCustomerCode
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE ToCustomerCodeInput(void)
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();

	/* 前回入力値を名前入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrder.ToCustomerCode);
	CharacterInput.MaxFigure = SYS_ORDER_CODE_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_DISABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[発注先社名入力]
	function	:[
		1.発注先社名登録を行う。
		2.発注先社名は３０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.ToCompany
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE ToCompanyNameInput(void)
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();

	/* 前回入力値を名前入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrder.ToCompany);
	CharacterInput.MaxFigure = SYS_ORDER_NAME_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_ENABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[発注元得意先コード入力]
	function	:[
		1.発注元得意先コードの登録を行う。
		2.発注元得意先コードは１０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.FromCustomerCode
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE FromCustomerCodeInput(void)
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();

	/* 前回入力値を名前入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrder.FromCustomerCode);
	CharacterInput.MaxFigure = SYS_ORDER_CODE_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_DISABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[発注元社名入力]
	function	:[
		1.発注元社名登録を行う。
		2.発注元社名は３０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.FromCompany
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE FromCompanyNameInput(void)
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();

	/* 前回入力値を名前入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrder.FromCompany);
	CharacterInput.MaxFigure = SYS_ORDER_NAME_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_ENABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[発注元部課名入力]
	function	:[
		1.発注元部課名登録を行う。
		2.発注元部課名は３０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.FromSection
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE FromSectionNameInput(void)
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();

	/* 前回入力値を名前入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrder.FromSection);
	CharacterInput.MaxFigure = SYS_ORDER_NAME_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_ENABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[発注元部課名入力２]
	function	:[
		1.発注元部課名登録を行う。
		2.発注元部課名は３０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrderFromSection2
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/05/18]
	author		:[本多智幸]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
UBYTE FromSectionName2Input(void)  /* orderbythonda1998/05/18 */
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();

	/* 前回入力値を名前入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrderFromSection2);
	CharacterInput.MaxFigure = SYS_ORDER_NAME_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_ENABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_ENABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}
#endif

/*************************************************************************
	module		:[発注元電話番号の入力]
	function	:[
		1.発注元電話番号の登録を行う
		2.発注元電話番号は２０桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.FromTelNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE FromCustomerTelNumberInput(void)
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */

	/* 入力作業用バッファのクリア */
	ClearCharacterInput();
	
	/* 前回入力値を数値入力用バッファに展開する */
	CMN_StringCopy(CharacterInput.Buffer, SYB_ConsumerOrder.FromTelNumber);
	CharacterInput.MaxFigure = SYS_ORDER_DIAL_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/** データ入力 */
	while (1) {

		/** 下段に登録状況を表示 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/* 終了 */
			CursorOff();
			return (NG);
		case SET_KEY:			/* セットキー	*/
			/* 終了 */
			CursorOff();
			return (OK);
		case DIAL_MARK_KEY:		/* ダイアル記号キー */
			/* バッファの先頭なら＋、それ以外の場合ーをセットする */
			if ((CharacterInput.Buffer[0] == NULL) || (CharacterInput.CursorPosition == 0)) {
				if (CharacterInput.Buffer[0] == '+') {
					NackBuzzer();
					break;
				}
				else {
					key = '+';
				}
			}
			else {
				key = '-';
			}
			CharacterDataSet_FigureCheck(key);
			break;
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

#if defined(US1)
/*************************************************************************
	module		:[発注先Ｆａｘ番号の入力]
	function	:[
		1.発注先Ｆａｘ番号の登録を行う
		2.発注先Ｆａｘ番号は１４桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ToCompanyFaxNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/11/11]
	author		:[本多智幸]
*************************************************************************/
UBYTE ToCompanyFaxNumberInput(void)		/* orderbythonda1998/11/11 */
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */

	/* 入力作業用バッファのクリア */
	ClearCharacterInput();
	
	/* 前回入力値を数値入力用バッファに展開する */
	CMN_StringCopy(CharacterInput.Buffer, SYB_ToCompanyFaxNumber);
	CharacterInput.MaxFigure = SYS_ORDER_DIAL2_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/** データ入力 */
	while (1) {

		/** 下段に登録状況を表示 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/* 終了 */
			CursorOff();
			return (NG);
		case SET_KEY:			/* セットキー	*/
			/* 終了 */
			CursorOff();
			return (OK);
		case DIAL_MARK_KEY:		/* ダイアル記号キー */
			/* バッファの先頭なら＋、それ以外の場合ーをセットする */
			if ((CharacterInput.Buffer[0] == NULL) || (CharacterInput.CursorPosition == 0)) {
				if (CharacterInput.Buffer[0] == '+') {
					NackBuzzer();
					break;
				}
				else {
					key = '+';
				}
			}
			else {
				key = '-';
			}
			CharacterDataSet_FigureCheck(key);
			break;
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[発注先Ｔｅｌ番号の入力]
	function	:[
		1.発注先Ｔｅｌ番号の登録を行う
		2.発注先Ｔｅｌ番号は１４桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ToCompanyTelNumber
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/11/11]
	author		:[本多智幸]
*************************************************************************/
UBYTE ToCompanyTelNumberInput(void)		/* orderbythonda1998/11/11 */
{
	UBYTE	key;			/* ｷｰ取り込みﾃﾞｰﾀ     */

	/* 入力作業用バッファのクリア */
	ClearCharacterInput();
	
	/* 前回入力値を数値入力用バッファに展開する */
	CMN_StringCopy(CharacterInput.Buffer, SYB_ToCompanyTelNumber);
	CharacterInput.MaxFigure = SYS_ORDER_DIAL2_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

	/** データ入力 */
	while (1) {

		/** 下段に登録状況を表示 */
		DisplayNumberInput();

		/** キー取り込み */
		key = NumberInputKeyGet();

		switch (key) {
		case STOP_KEY:			/* ストップキー */
			/* 終了 */
			CursorOff();
			return (NG);
		case SET_KEY:			/* セットキー	*/
			/* 終了 */
			CursorOff();
			return (OK);
		case DIAL_MARK_KEY:		/* ダイアル記号キー */
			/* バッファの先頭なら＋、それ以外の場合ーをセットする */
			if ((CharacterInput.Buffer[0] == NULL) || (CharacterInput.CursorPosition == 0)) {
				if (CharacterInput.Buffer[0] == '+') {
					NackBuzzer();
					break;
				}
				else {
					key = '+';
				}
			}
			else {
				key = '-';
			}
			CharacterDataSet_FigureCheck(key);
			break;
		case OPR_NO_KEY:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif	/* defined(US1) */

/*************************************************************************
	module		:[シリアル番号入力]
	function	:[
		1.シリアル番号の登録を行う。
		2.シリアル番号は１８桁以内
	]
	return		:[
		OK:登録完了
		NG:登録中止
	]
	common		:[
		CharacterInput
		SYB_ConsumerOrder.SerialNumber　　　　　　　　　
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/08]
	author		:[桑原美紀]
*************************************************************************/
UBYTE SerialNumberInput(void)
{
	/* 入力作業用バッファのクリア */
	ClearCharacterInput();

	/* 文字入力モード初期化 */
	SetCharacterInputMode();
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* シリアルNo登録画面での文字モードは初期値をエイスウにします。Added by SMuratec L.Z.W 2003/11/28 */
	CharacterInput.Mode = OPR_ALPHAMERIC_MODE;
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

	/* 前回入力値をシリアル番号入力用バッファに展開する */
	SetCharacterInputBuf(SYB_ConsumerOrder.SerialNumber);
	CharacterInput.MaxFigure = SYS_ORDER_SERIAL_MAX - 1;
	CharacterInput.WritePosition = (UBYTE)CMN_StringLength(CharacterInput.Buffer);
	CharacterInput.CursorPosition = CharacterInput.WritePosition;

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Modify by SMuratec L.Z.W 2003/08/13 */
	if (OPR_InputCharacterOperation(OPR_KANJI_DISABLE)) {
		return(OK);
	}
	else {
		return(NG);
	}
#else /* (PRO_KEYPANEL != PANEL_SATSUKI2) && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	return (NameInput(OPR_KANJI_DISABLE));
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
}

/*************************************************************************
	module		:[設置日セット]
	function	:[
		1.設置日のセットを行う
	]
	return		:[なし]
	common		:[
		SYB_ConsumerOrder.InstallDate
		CharacterInput
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[97/10/08]
	author		:[桑原美紀]
*************************************************************************/
#if(0)	/* ＲＯＭ容量削減の為 by K.Watanabe 1998/04/24 */
//UBYTE SetDateInput(void)
//{
//	UBYTE	key;
//	UBYTE	keytype;
//	UBYTE	old_current[10];
//	TIME_DATA_t current;
//
//	/*-------------------*/
//	/**  初期化処理		 */
//	/*-------------------*/
//	if ( SYB_ConsumerOrder.InstallDate == NULL ) {		/* 何もｾｯﾄされていない時は現在時間をｾｯﾄしておく */
//		SYB_ConsumerOrder.InstallDate	= SYB_CurrentTime;
//	}
//	ClearCharacterInput();
//	SetLongTimeToCharacterInput(SYB_ConsumerOrder.InstallDate, CALENDER_TYPE);
//	CharacterInput.WritePosition = 5;
//	CharacterInput.LcdDisplayPosition = 11;
//	CharacterInput.Buffer[6] = NULL;		/* 年月日しか表示しない為 */
//
//	/* 設定前のカレンダーを待避 */
//	CMN_StringCopyNum(old_current, CharacterInput.Buffer, 6);
//	old_current[6]	= NULL;
//
//	/* 編集　*/
//	while (1) {
//		/** 表示処理 */
//		DisplayTimeInput(CALENDER_DATE_TYPE);
//
//		/** キーの取り込み */
//		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
//		key = GetInputKeyCode();
//		keytype = GetInputKeyType();
//
//		switch (keytype) { /** 入力されたキーに対する処理 */
//		case NUMBER:	/** 数字（0 - 9) */
//			FixedNumberDataSet(key);
//			break;
//
//		case STOP:			/** ストップキー */
//		case KEY_TIME_UP:	/** １分間キー入力なし */
//			/** 終了 */
//			CursorOff();
//			return (NG);
//
//		case FUNCTION:	/**機能キー */
//			/** カーソル右移動 */
//			CursorRightRotation();
//			break;
//
//		case LEFT_ARROW:/** 左カーソルキー */
//			/** カーソル左キー*/
//			CursorLeftRotation();
//			break;
//
//		case ENTER:		/** セットキー */
//			/** 入力データのチェックを行う */
//			/* カレンダーが変更されているかチェック  追加 1997/08/05 Y.Matsukuma */
//			if (CMN_StringCompare(old_current, CharacterInput.Buffer, 6) == STRCMP_EQUAL) {
//				return(OK);	/* 更新されていなければ、RTCにセットしない */
//			}
//			CharacterInput.Buffer[6] = 0x30;	/* ＮＵＬＬをセットしたままだとカレンダーチェックでエラーになる為 */
//			if (CheckCalenderInput() == OK) {
//				StoreCharacterInputValue(OperationTime.BCD_StringTime, BCD_DATA_TYPE);
//				current.Year   = OperationTime.BCD_StructTime.Year;		/* 年 */
//				current.Month  = OperationTime.BCD_StructTime.Month;	/* 月 */
//				current.Date   = OperationTime.BCD_StructTime.Date;		/* 日 */
//				current.Hour   = OperationTime.BCD_StructTime.Hour;		/* 時 */
//				current.Minute = OperationTime.BCD_StructTime.Minute;	/* 分 */
//				current.Second = 0;										/* 秒 */
//				SYB_ConsumerOrder.InstallDate = CMN_BCD_TimeToLong(&current);
//				CursorOff();
//				return (OK);
//			}
//			CharacterInput.Buffer[6] = NULL;
//			CharacterInput.CursorPosition = 0;
//			NackBuzzer();
//			break;
//
//		case NO_EFFECT:
//		case OPR_NO_KEY:
//			break;
//
//		default:
//			NackBuzzer();
//			break;
//		}
//	}
//}
#endif

/*************************************************************************
	module		:[発注用紙リスト]
	function	:[
		1.発注用紙リストの印字
	]
	return		:[
		OK:印字実行
		NG:印字中止
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/09/30]
	author		:[福本貴吉]
*************************************************************************/
UBYTE PrintConsumerOrderForm(void)
{
	if (ConfirmKeyInputOperation(D2W_SF_PrintOrderForm, D2W_EnterStop, ENTER, STOP) == CONFIRM_EXEC) {
		/* メインにリスト起動メッセージ送信 */
		FinalListPrintOperation(LST_CONSUMERORDER_SHEET);
		return (OK);
	}
	return (NG);
}

/*************************************************************************
	module		:[機器設定リスト]
	function	:[
		1.機器設定リストの印字の起動をかける
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/09]
	author		:[桑原美紀]
*************************************************************************/
void ServicePrintSettingList(void)
{
	FinalListPrintOperation(LST_PARAMETER_LIST); /* メインにリスト起動メッセージ送信 */
}

#if (PRO_MULTI_LINE == ENABLE)
/*************************************************************************
	module		:[回線テスト（２回仕様）]
	function	:[
		1.リレーテスト
		2.トーナルテスト
		3.ＤＴＭＦテスト
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/10]
	author		:[松隈]
*************************************************************************/
void MultiLineFunctionMode(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	func_number;
	UBYTE	loop;

	/* データ初期化 */
	SYS_FactoryOptModem.Item = OPT_MDM_FACTORY_TEST_START;
	SYS_FactoryOptModem.Kind = 0xff;
	SYS_FactoryOptModem.BaudRate = 0xff;
	SYS_FactoryOptModem.DataRate = 0xff;
	SYS_FactoryOptModem.PIX_Pattern	= 0xff;
	SYS_FactoryOptModem.StackNumber = 0;

	/* 表示 1997/01/07  Y.Matsukuma */
	DisplayStringLow(0, D2W_SF_BoardNumber);
	ClearDisplayHigh();

	loop = 1;
	while (loop) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			if ((key >= TEN_1_KEY) && (key <= TEN_8_KEY)) {	/* ｵﾌﾟｼｮﾝ１～ｵﾌﾟｼｮﾝ８が選択された時 */
				if (CHK_OptionLineExist((UBYTE)(key - TEN_1_KEY + 1))) {
					SYS_FactoryOptModem.StackNumber = (UBYTE)(key - TEN_1_KEY);
					loop = 0;
				}
				else {
					NackBuzzer();
				}
			}
			else {
				NackBuzzer();
			}
			break;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}

/* 追加終了 */

	func_number = 0;

	while (1) {
		DisplayStringHigh(0, D2W_SF_PhoneTest + (OPR_WORDING_LEN * func_number));
		ClearDisplayLow();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:
			func_number++;
			if (func_number > 2) {
				func_number = 0;
			}
			break;
		case ENTER:
			MAN_OptFactoryFunctionCommand(&SYS_FactoryOptModem);
			MAN_OptionModemStart((UBYTE)(SYS_FactoryOptModem.StackNumber + 1));
			if (func_number == 0) {
				SYS_FactoryOptModem.Item = SYS_OPT_MDM_RELAY_TEST;
				SF_MultiRelayTest();/* リレーテスト */
			}
			if (func_number == 1) {
				SYS_FactoryOptModem.Item = SYS_OPT_MDM_TONAL_TEST;
				SF_MultiTonalTest();/* トーナルテスト */
			}
			if (func_number == 2) {
				SYS_FactoryOptModem.Item = SYS_OPT_MDM_DTMF_TEST;
				SF_MultiDTMF_Test();/* ＤＴＭＦテスト */
			}
			MAN_OptionModemLast((UBYTE)(SYS_FactoryOptModem.StackNumber + 1));
			MAN_OptFactoryFunctionCommand(&SYS_FactoryOptModem);
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[リレーテスト（２回線仕様）]
	function	:[
		1.指定されたリレーのＯＮ／ＯＦＦを行う。
		2.キー入力とリレーの対応関係は以下のようになる。
		,	ONETOUCH_A_KEY -> CML	ON
		,	ONETOUCH_B_KEY -> CML	OFF
		,	ONETOUCH_C_KEY -> H		ON
		,	ONETOUCH_D_KEY -> H		OFF
		,	ONETOUCH_E_KEY -> L		ON
		,	ONETOUCH_F_KEY -> L		OFF
		,	ONETOUCH_G_KEY -> S		ON
		,	ONETOUCH_H_KEY -> S		OFF
		,	ONETOUCH_I_KEY -> DP	ON
		,	ONETOUCH_J_KEY -> DP	OFF
		,	ONETOUCH_K_KEY -> C24	ON
		,	ONETOUCH_L_KEY -> C24	OFF
		,	ONETOUCH_M_KEY -> RI	ON
		,	ONETOUCH_N_KEY -> RI	OFF
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/02/14]
	author		:[松隈]
*************************************************************************/
void SF_MultiRelayTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	kind;

	kind = 0xFF;

	/* 表示 */
	DisplayStringHigh(0, D2W_SF_RelayTest1);	/* [ CML  H  L  S  DP   ] */
	DisplayStringLow(0, D2W_SF_RelayTest2);		/* [ C24                ] */
	DisplayChar(26, 'R');
	DisplayChar(27, 'I');

	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ONETOUCH:
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			/* 指定されたリレーのＯＮ／ＯＦＦを行う */
			switch (key) {
			case ONETOUCH_01_KEY:	/* CML */
				kind = OPT_MDM_RELAY_CML_ON;
				DisplayChar(0, '*');
				break;
			case ONETOUCH_02_KEY:	/* CML */
				kind = OPT_MDM_RELAY_CML_OFF;
				DisplayChar(0, ' ');
				break;
			case ONETOUCH_03_KEY:	/*  H  */
				kind = OPT_MDM_RELAY_H_ON;
				DisplayChar(5, '*');
				break;
			case ONETOUCH_04_KEY:	/*  H  */
				kind = OPT_MDM_RELAY_H_OFF;
				DisplayChar(5, ' ');
				break;
			case ONETOUCH_05_KEY:	/*  L  */
				kind = OPT_MDM_RELAY_L_ON;
				DisplayChar(8, '*');
				break;
			case ONETOUCH_06_KEY:	/*  L  */
				kind = OPT_MDM_RELAY_L_OFF;
				DisplayChar(8, ' ');
				break;
			case ONETOUCH_07_KEY:	/*  S  */
				kind = OPT_MDM_RELAY_S_ON;
				DisplayChar(11, '*');
				break;
			case ONETOUCH_08_KEY:	/*  S  */
				kind = OPT_MDM_RELAY_S_OFF;
				DisplayChar(11, ' ');
				break;
			case ONETOUCH_09_KEY:	/*  DP */
				kind = OPT_MDM_RELAY_DP_ON;
				DisplayChar(14, '*');
				break;
			case ONETOUCH_10_KEY:	/*  DP */
				kind = OPT_MDM_RELAY_DP_OFF;
				DisplayChar(14, ' ');
				break;
			case ONETOUCH_11_KEY:	/* C24 */
				kind = OPT_MDM_RELAY_CONT24_ON;
				DisplayChar(20, '*');
				break;
			case ONETOUCH_12_KEY:	/* C24 */
				kind = OPT_MDM_RELAY_CONT24_OFF;
				DisplayChar(20, ' ');
				break;
			case ONETOUCH_13_KEY:	/* RI */
				kind = OPT_MDM_RELAY_RI_ON;
				DisplayChar(25, '*');
				break;
			case ONETOUCH_14_KEY:	/* RI */
				kind = OPT_MDM_RELAY_RI_OFF;
				DisplayChar(25, ' ');
				break;
			default:
				NackBuzzer();
				break;
			}
 #endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			/* 指定されたリレーのＯＮ／ＯＦＦを行う */
			switch (key) {
			case ONETOUCH_A_KEY:	/* CML */
				kind = OPT_MDM_RELAY_CML_ON;
				DisplayChar(0, '*');
				break;
			case ONETOUCH_B_KEY:	/* CML */
				kind = OPT_MDM_RELAY_CML_OFF;
				DisplayChar(0, ' ');
				break;
			case ONETOUCH_C_KEY:	/*  H  */
				kind = OPT_MDM_RELAY_H_ON;
				DisplayChar(5, '*');
				break;
			case ONETOUCH_D_KEY:	/*  H  */
				kind = OPT_MDM_RELAY_H_OFF;
				DisplayChar(5, ' ');
				break;
			case ONETOUCH_E_KEY:	/*  L  */
				kind = OPT_MDM_RELAY_L_ON;
				DisplayChar(8, '*');
				break;
			case ONETOUCH_F_KEY:	/*  L  */
				kind = OPT_MDM_RELAY_L_OFF;
				DisplayChar(8, ' ');
				break;
			case ONETOUCH_G_KEY:	/*  S  */
				kind = OPT_MDM_RELAY_S_ON;
				DisplayChar(11, '*');
				break;
			case ONETOUCH_H_KEY:	/*  S  */
				kind = OPT_MDM_RELAY_S_OFF;
				DisplayChar(11, ' ');
				break;
			case ONETOUCH_I_KEY:	/*  DP */
				kind = OPT_MDM_RELAY_DP_ON;
				DisplayChar(14, '*');
				break;
			case ONETOUCH_J_KEY:	/*  DP */
				kind = OPT_MDM_RELAY_DP_OFF;
				DisplayChar(14, ' ');
				break;
			case ONETOUCH_K_KEY:	/* C24 */
				kind = OPT_MDM_RELAY_CONT24_ON;
				DisplayChar(20, '*');
				break;
			case ONETOUCH_L_KEY:	/* C24 */
				kind = OPT_MDM_RELAY_CONT24_OFF;
				DisplayChar(20, ' ');
				break;
			case ONETOUCH_M_KEY:	/* RI */
				kind = OPT_MDM_RELAY_RI_ON;
				DisplayChar(25, '*');
				break;
			case ONETOUCH_N_KEY:	/* RI */
				kind = OPT_MDM_RELAY_RI_OFF;
				DisplayChar(25, ' ');
				break;
			default:
				NackBuzzer();
				break;
			}
 #endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */
			SYS_FactoryOptModem.Kind = kind;
			MAN_OptFactoryFunctionCommand(&SYS_FactoryOptModem);
			break;
		case STOP:
			SYS_FactoryOptModem.Item = OPT_MDM_FACTORY_TEST_END;
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[トーナルテスト（２回線仕様）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/10]
	author		:[松隈]
*************************************************************************/
void SF_MultiTonalTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;
	UBYTE	tx_signal;
	UWORD	freq;

	tx_signal = 0;
	freq = (UWORD)OPT_MDM_TONAL_STOP;

	while (1) {
		DisplayMultiTonalTest(tx_signal, (UBYTE)freq );
		is_check_enable = TRUE;
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			if (key == TEN_0_KEY) {
#if defined(POPLAR_F)	/* FSK_W1_B1 1999/12/27 Y.Murata */
				freq = (UWORD)(OPT_MDM_TONAL_FSK_W1_B1);
				tx_signal = 2;
				break;
#else
				is_check_enable = FALSE;
				NackBuzzer();
				break;
#endif
			}
			freq = (UWORD)(OPT_MDM_TONAL_NONE + (UWORD)(key - TEN_1_KEY));
			tx_signal = 1;
			break;
		case AST:
			freq = (UWORD)OPT_MDM_TONAL_FSK_WHITE;
			tx_signal = 2;
			break;
		case SHARP:
			freq = (UWORD)OPT_MDM_TONAL_FSK_BLACK;
			tx_signal = 2;
			break;
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
		case ONETOUCH:
			if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_64_KEY)) {
				freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY));
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_08_KEY)) {
					freq = MultiPixPattern(freq);	/* ストップ押されたときこの処理からぬける */
					tx_signal = 0;
				}
				else if (key == ONETOUCH_64_KEY) {
					tx_signal = 4;	/* Voice */
				}
				else {
					tx_signal = 3;
				}
			}
			else {
				is_check_enable = FALSE;
				NackBuzzer();
			}
			break;
 #endif
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
		case ONETOUCH:
			if ((ONETOUCH_A_KEY <= key) && (key <= ONETOUCH_Z_KEY)) {
				freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_A_KEY));
				if ((ONETOUCH_A_KEY <= key) && (key <= ONETOUCH_H_KEY)) {
					freq = MultiPixPattern(freq);	/* ストップ押されたときこの処理からぬける */
					tx_signal = 0;
					break;
				}
			}
			else if ((ONETOUCH_a_KEY <= key) && (key <= ONETOUCH_z_KEY)) {
				freq = (UWORD)(OPT_MDM_TONAL_V34_2800_26400 + (UWORD)(key - ONETOUCH_a_KEY));
			}
			else if ((ONETOUCH_U1_KEY <= key) && (key <= ONETOUCH_U8_KEY)) {
				freq = (UWORD)(OPT_MDM_TONAL_V34_3429_9600 + (UWORD)(key - ONETOUCH_U1_KEY));
			}
			else {
				is_check_enable = FALSE;
				NackBuzzer();
			}
			tx_signal = 3;
			break;
		case PROGRAM:
			if ((PROGRAM_P01 <= key) && (key <= PROGRAM_P04)) {
				freq = (UWORD)(OPT_MDM_TONAL_V34_3429_28800 + (UWORD)(key - PROGRAM_P01));
				if (key == PROGRAM_P04) {
					tx_signal = 4;	/* Voice */
				}
				else {
					tx_signal = 3;
				}
			}
			else {
				is_check_enable = FALSE;
				NackBuzzer();
			}
			break;
 #endif
		case STOP:
			if (freq != (UWORD)OPT_MDM_TONAL_STOP) { /* トーン送出中 */
				freq = (UWORD)OPT_MDM_TONAL_STOP;
				tx_signal = 0;
				break;
			}
			else {
				SYS_FactoryOptModem.Item = OPT_MDM_FACTORY_TEST_END;
				return;
			}
			break;
		case NO_EFFECT:
			is_check_enable = FALSE;
			break;
		default:
			is_check_enable = FALSE;
			NackBuzzer();
			break;
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			SYS_FactoryOptModem.Kind = freq;
			MAN_OptFactoryFunctionCommand(&SYS_FactoryOptModem);
		}
	}
}

/*************************************************************************
	module		:[ＤＴＭＦテスト]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/10]
	author		:[松隈]
*************************************************************************/
void SF_MultiDTMF_Test(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;
	UWORD	dtmf;

	dtmf = (UWORD)OPT_MDM_DTMF_STOP;

	while (1) {
		is_check_enable = TRUE;

		/* 表示 */
		DisplayMultiTxDTMF((UBYTE) dtmf);

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
		case AST:
		case SHARP:
		case ONETOUCH:
			if (TEN_0_KEY <= key && key <= TEN_9_KEY) {
				dtmf = (UWORD)(key - 0x30);
			}
			else if (key == TEN_SHARP_KEY) {
				dtmf = (UWORD)OPT_MDM_DTMF_SHARP;
			}
			else if (key == TEN_AST_KEY) {
				dtmf = (UWORD)OPT_MDM_DTMF_AST;
			}
 #if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			else if (ONETOUCH_01_KEY <= key && key <= ONETOUCH_08_KEY) {
				dtmf = (UWORD)(OPT_MDM_DTMF_ROW1 + (UWORD)(key - ONETOUCH_01_KEY));
			}
 #endif
 #if (PRO_KEYPANEL == PANEL_ANZU_L)
			else if (ONETOUCH_A_KEY <= key && key <= ONETOUCH_H_KEY) {
				dtmf = (UWORD)(OPT_MDM_DTMF_ROW1 + (UWORD)(key - ONETOUCH_A_KEY));
			}
 #endif
			else {
				is_check_enable = FALSE;
				NackBuzzer();
			}
			break;
		case STOP:
			if (dtmf != (UWORD)OPT_MDM_DTMF_STOP) {	/* ＤＴＭＦ送出中 */
				dtmf = (UWORD)OPT_MDM_DTMF_STOP;
				break;
			}
			else {
				SYS_FactoryOptModem.Item = OPT_MDM_FACTORY_TEST_END;
				return;
			}
			break;
		case NO_EFFECT:
			is_check_enable = FALSE;
			break;
		default:
			is_check_enable = FALSE;
			NackBuzzer();
			break;
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			SYS_FactoryOptModem.Kind = dtmf;
			MAN_OptFactoryFunctionCommand(&SYS_FactoryOptModem);
		}
	}
}

/*************************************************************************
	module		:[回線テスト・ＰＩＸ送出パターン選択]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/12/11]
	author		:[松隈]
*************************************************************************/
UWORD MultiPixPattern(UWORD Freq)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;

	/* 表示  */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferLow[0] = 'W';
	FunctionDisplayBufferLow[1] = ':';
	FunctionDisplayBufferLow[2] = 'B';
	FunctionDisplayBufferLow[3] = '?';
	DisplayStringLow(0, FunctionDisplayBufferLow);

	while (1) {
		DisplayMultiTonalTest( 3, (UBYTE)Freq );
		is_check_enable = TRUE;

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		if (TEN_1_KEY <= key && key <= TEN_5_KEY) {
			SYS_FactoryOptModem.PIX_Pattern = (UWORD)(OPT_MDM_PIX_W1_B0 + (UWORD)(key - TEN_1_KEY));
			SYS_FactoryOptModem.Kind = Freq;
		}
		else if (key == STOP_KEY) {
			if (SYS_FactoryOptModem.Kind != OPT_MDM_TONAL_STOP) {
				SYS_FactoryOptModem.Kind = OPT_MDM_TONAL_STOP;
			}
			/*
			 * ストップ２回押すとこの処理からぬける
			*/
			else {
				ClearDisplayLow();
				return(OPT_MDM_TONAL_STOP);
			}
		}
		else {
			is_check_enable = FALSE;
			NackBuzzer();
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			MAN_OptFactoryFunctionCommand(&SYS_FactoryOptModem);
		}
	}
}

/*************************************************************************
	module		:[トーナル信号表示（２回線用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/13]
	author		:[松隈]
*************************************************************************/
void	DisplayMultiTonalTest(UBYTE tx_signal, UBYTE freq )
{
	UWORD	data;
	UBYTE	pix_rate[4];
	UBYTE	disp_buf[7];

	data = 0;
	CMN_MemorySet(disp_buf, 7, NULL);
	CMN_MemorySet(pix_rate, 4, NULL);

	/* 上段表示 */
	switch (tx_signal) {

	/*-------------*/
	/* 無信号状態　*/
	/*-------------*/
	case 0:	/* 無信号 */
		ClearDisplayHigh(); /* 空白 */
		break;

	/*--------------------*/
	/* トーナル信号送出中 */
	/*--------------------*/
	case 1:	/* トーン */
		switch (freq) {
		case OPT_MDM_TONAL_462HZ:
			data = 462;
			break;
		case OPT_MDM_TONAL_1080HZ:
			data = 1080;
			break;
		case OPT_MDM_TONAL_1300HZ:
			data = 1300;
			break;
		case OPT_MDM_TONAL_1650HZ:
			data = 1650;
			break;
		case OPT_MDM_TONAL_1700HZ:
			data = 1700;
			break;
		case OPT_MDM_TONAL_1800HZ:
			data = 1800;
			break;
		case OPT_MDM_TONAL_1850HZ:
			data = 1850;
			break;
		case OPT_MDM_TONAL_2100HZ:
			data = 2100;
			break;
		}
		CMN_UnsignedIntToASC(disp_buf, data, 4, ' ');
		disp_buf[4] = 'H';
		disp_buf[5] = 'z';
		ClearDisplayHigh();
		DisplayStringHigh(0, disp_buf);
		break;

	/*----------------------*/
	/* ＦＳＫ信号送出中		*/
	/*----------------------*/
	case 2:	/* FSK	  */
		ClearDisplayHigh();
		DisplayStringHigh(0 , D2W_SF_FSK);
		if (freq == OPT_MDM_TONAL_FSK_WHITE) {
			DisplayStringHigh(4 , D2W_SF_White);
		}
		if (freq == OPT_MDM_TONAL_FSK_BLACK) {
			DisplayStringHigh(4 , D2W_SF_Black);
		}
#if defined(POPLAR_F)	/* FSK_W1_B1 1999/12/27 Y.Murata */
		if (freq == OPT_MDM_TONAL_FSK_W1_B1) {
			disp_buf[0] = 'W';
			disp_buf[1] = '1';
			disp_buf[2] = ':';
			disp_buf[3] = 'B';
			disp_buf[4] = '1';
			disp_buf[5] = NULL;
			DisplayStringHigh(4 , disp_buf);
		}
#endif
		break;

	/*---------------------*/
	/* 画信号送出中		   */
	/*---------------------*/
	case 3:	/* PIX	  */
		switch (freq) {
		case OPT_MDM_TONAL_V27_1200_2400:
		case OPT_MDM_TONAL_V34_2400_2400:
			data = 2400;
			break;
		case OPT_MDM_TONAL_V27_1600_4800:
		case OPT_MDM_TONAL_V34_2400_4800:
		case OPT_MDM_TONAL_V34_2800_4800:
		case OPT_MDM_TONAL_V34_3000_4800:
		case OPT_MDM_TONAL_V34_3200_4800:
		case OPT_MDM_TONAL_V34_3429_4800:
			data = 4800;
			break;
		case OPT_MDM_TONAL_V29_2400_7200:
		case OPT_MDM_TONAL_V17_2400_7200:
		case OPT_MDM_TONAL_V34_2400_7200:
		case OPT_MDM_TONAL_V34_2800_7200:
		case OPT_MDM_TONAL_V34_3000_7200:
		case OPT_MDM_TONAL_V34_3200_7200:
		case OPT_MDM_TONAL_V34_3429_7200:
			data = 7200;
			break;
		case OPT_MDM_TONAL_V29_2400_9600:
		case OPT_MDM_TONAL_V17_2400_9600:
		case OPT_MDM_TONAL_V34_2400_9600:
		case OPT_MDM_TONAL_V34_2800_9600:
		case OPT_MDM_TONAL_V34_3000_9600:
		case OPT_MDM_TONAL_V34_3200_9600:
		case OPT_MDM_TONAL_V34_3429_9600:
			data = 9600;
			break;
		case OPT_MDM_TONAL_V17_2400_12000:
		case OPT_MDM_TONAL_V34_2400_12000:
		case OPT_MDM_TONAL_V34_2800_12000:
		case OPT_MDM_TONAL_V34_3000_12000:
		case OPT_MDM_TONAL_V34_3200_12000:
		case OPT_MDM_TONAL_V34_3429_12000:
			data = 12000;
			break;
		case OPT_MDM_TONAL_V17_2400_14400:
		case OPT_MDM_TONAL_V34_2400_14400:
		case OPT_MDM_TONAL_V34_2800_14400:
		case OPT_MDM_TONAL_V34_3000_14400:
		case OPT_MDM_TONAL_V34_3200_14400:
		case OPT_MDM_TONAL_V34_3429_14400:
			data = 14400;
			break;
		case OPT_MDM_TONAL_V34_2400_16800:
		case OPT_MDM_TONAL_V34_2800_16800:
		case OPT_MDM_TONAL_V34_3000_16800:
		case OPT_MDM_TONAL_V34_3200_16800:
		case OPT_MDM_TONAL_V34_3429_16800:
			data = 16800;
			break;
		case OPT_MDM_TONAL_V34_2400_19200:
		case OPT_MDM_TONAL_V34_2800_19200:
		case OPT_MDM_TONAL_V34_3000_19200:
		case OPT_MDM_TONAL_V34_3200_19200:
		case OPT_MDM_TONAL_V34_3429_19200:
			data = 19200;
			break;
		case OPT_MDM_TONAL_V34_2400_21600:
		case OPT_MDM_TONAL_V34_2800_21600:
		case OPT_MDM_TONAL_V34_3000_21600:
		case OPT_MDM_TONAL_V34_3200_21600:
		case OPT_MDM_TONAL_V34_3429_21600:
			data = 21600;
			break;
		case OPT_MDM_TONAL_V34_2800_24000:
		case OPT_MDM_TONAL_V34_3000_24000:
		case OPT_MDM_TONAL_V34_3200_24000:
		case OPT_MDM_TONAL_V34_3429_24000:
			data = 24000;
			break;
		case OPT_MDM_TONAL_V34_2800_26400:
		case OPT_MDM_TONAL_V34_3000_26400:
		case OPT_MDM_TONAL_V34_3200_26400:
		case OPT_MDM_TONAL_V34_3429_26400:
			data = 26400;
			break;
        case OPT_MDM_TONAL_V34_3000_28800:
		case OPT_MDM_TONAL_V34_3200_28800:
		case OPT_MDM_TONAL_V34_3429_28800:
			data = 28800;
			break;
		case OPT_MDM_TONAL_V34_3200_31200:
		case OPT_MDM_TONAL_V34_3429_31200:
			data = 31200;
			break;
		case OPT_MDM_TONAL_V34_3429_33600:
			data = 33600;
			break;
		}
		CMN_UnsignedIntToASC(disp_buf, data, 5, ' ');

		if (freq >= OPT_MDM_TONAL_V27_1200_2400 && freq <= OPT_MDM_TONAL_V17_2400_14400) {
			pix_rate[0] = '1';
			pix_rate[1] = ':';
			pix_rate[2] = '1';
			pix_rate[3] = '\0';

			switch (SYS_FactoryOptModem.PIX_Pattern) {
			case OPT_MDM_PIX_W1_B0: /* [1:0] */
				pix_rate[2] = '0';
				break;
			case OPT_MDM_PIX_W1_B1: /* [1:1] */
				break;
			case OPT_MDM_PIX_W1_B4: /* [1:4] */
				pix_rate[2] = '4';
				break;
			case OPT_MDM_PIX_W0_B1: /* [0:1] */
				pix_rate[0] = '0';
				break;
			case OPT_MDM_PIX_W4_B1: /* [4:1] */
				pix_rate[0] = '4';
				break;
			}
			DisplayStringHigh(0, D2W_SF_Pix);
			DisplayStringHigh(0, disp_buf);
			DisplayStringHigh(17, pix_rate);
		}
		else {
			pix_rate[0] = 'B';
			pix_rate[1] = 'P';
			pix_rate[2] = 'S';
			pix_rate[3] = '\0';
			ClearDisplayHigh();
			DisplayStringHigh(0, disp_buf);
			DisplayStringHigh(5, pix_rate);
		}
		break;
	/*-------*/
	/* Voice */
	/*-------*/
	case 4:
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferHigh[0] = 'V';
		FunctionDisplayBufferHigh[1] = 'o';
		FunctionDisplayBufferHigh[2] = 'i';
		FunctionDisplayBufferHigh[3] = 'c';
		FunctionDisplayBufferHigh[4] = 'e';
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		break;
	}

	/* 下段クリア */
/*	ClearDisplayLow();*/

}

/*************************************************************************
	module		:[ＤＴＭＦテスト中の表示（２回線用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/14]
	author		:[松隈]
*************************************************************************/
void DisplayMultiTxDTMF(UBYTE dtmf)
{
	ClearDisplayHigh();
	ClearDisplayLow();

	if (dtmf == OPT_MDM_DTMF_STOP) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
	}
	if (OPT_MDM_DTMF_0 <= dtmf && dtmf <= OPT_MDM_DTMF_9) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , dtmf | 0x30);
	}
	if (dtmf == OPT_MDM_DTMF_SHARP) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , '#');
	}
	if (dtmf == OPT_MDM_DTMF_AST) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , '*');
	}

	if (OPT_MDM_DTMF_ROW1 <= dtmf && dtmf <= OPT_MDM_DTMF_ROW4) {
		DisplayStringHigh(0, D2W_SF_DTMFRow);
		DisplayChar(5, (UBYTE)((dtmf - OPT_MDM_DTMF_ROW1) + 1) | 0x30);
	}
	if (OPT_MDM_DTMF_COL1 <= dtmf && dtmf <= OPT_MDM_DTMF_COL4) {
		DisplayStringHigh(0, D2W_SF_DTMFColum);
		DisplayChar(5, (UBYTE)((dtmf - OPT_MDM_DTMF_COL1) + 1) | 0x30);
	}
}
#endif	/* (PRO_MULTI_LINE == ENABLE) */

/*************************************************************************
	module		:[オプションデータ初期化]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/11/12]
	author		:[松隈]
*************************************************************************/
void	SF_OptionDataInitial(void)
{
	ClearDisplayLow();

	/* クリア確認オペレーション */
	if (ConfirmKeyInputOperation(D2W_SF_OptionDataInitial, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
		CMN_InitializeOptionData((UBYTE)1);			/** オプション専用バックアップデータの初期化 */
		CMN_ClearJournalData();				/** ジャーナルデータクリア */
		ChildDisplayStringLow(D2W_ClearComplete);		/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

/*************************************************************************
	module		:[消耗品発注データクリア]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/12/22]
	author		:[渡辺一章]
*************************************************************************/
void ClearOrderData(void)
{

#if (PRO_PRINT_TYPE == THERMAL) /* By H.Fujimura 1999/01/06 */
	if (ConfirmKeyInputOperation(D2W_SF_MntDataClear,		/* "ｷｶｲ ﾊﾞﾝｺﾞｳ ｸﾘｱ      " */
								 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {
		/* 消耗品発注データの初期化 */
		CMN_ClearConsumerOrderData();
		ChildDisplayStringLow(D2W_ClearComplete);			/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
#else
	if (ConfirmKeyInputOperation(D2W_SF_OrderDataClear,		/* "ﾊｯﾁｭｳﾃﾞｰﾀ ｸﾘｱ       " */
								 D2W_CheckProgramEnter,		/* "ｶｸﾆﾝ        ｷﾉｳ/ｾｯﾄ " */
								 ENTER,
								 FUNCTION) == CONFIRM_EXEC) {
		/* 消耗品発注データの初期化 */
		CMN_ClearConsumerOrderData();
		ChildDisplayStringLow(D2W_ClearComplete);			/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
#endif


}


#if (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 	/* ﾌｧｰｽﾄ/ﾗｽﾄｸﾘｱ 2002/04/03 By M.Maeda */	/* RDC200200635 By O.Kimoto 2003/02/14 */
/*************************************************************************
	module		:[オールクリアー機能]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2000/06/06]
	author		:[前田雅也]
*************************************************************************/
void FirstOrLastClear(UBYTE mode)
{
	TIME_DATA_t		bcd_time;		/* サマータイム用 */
	UDWORD			long_time;		/* サマータイム用 */

#if defined(POPLAR_F)
	/* パワーＯＮ時のウォームアップ中は、キー操作禁止 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON) {
		NackBuzzer();
		return;
	}
#endif

#if (PRO_FBS == ENABLE)
	if (SYB_ScannerTransportMode) {
		NackBuzzer();
		return;
	}

	if (mode == TEN_2_KEY) {	/* 最後のクリア ＋ 輸送ＯＮ */
		if ((SYB_ScannerTransportMode == TRUE) && (SYS_MachineStatus[SYS_RESOURCE_STATUS] | SYS_SCANNER_BUSY)) {
			NackBuzzer();
			return;
		}
	}
#endif

	if (mode == TEN_1_KEY) {	/* 初期のクリア */
		CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"First Clear         ");	/* "First Clear         " */
	}
	else {						/* 最後のクリア ＋ 輸送ＯＮ */
		CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"Last Clear          ");	/* "Last Clear          " */
	}

	CMN_LongTimeToBCD(&bcd_time, SYB_CurrentTime); /* サマータイム用 */

	if (ConfirmKeyInputOperation(FunctionDisplayBufferHigh, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & ~SYS_PANEL_BUSY) {	/** 機器動作中 */
			NackBuzzer();
			return;
		}

		if (mode == TEN_1_KEY) {	/* ファーストクリア */
			CMN_InitializeAllBackUpRAM(0);		/** 機器パラメータ、オールラム		*/
			CMN_ClearConsumerOrderData();		/** 消耗品発注データのクリア		*/
			CMN_ClearLifeMonitorData();			/** ライフモニタークリア			*/
#if (PRO_PRINT_TYPE == LED)
			CMN_ClearPrinterLifeMonitorData();	/** プリンタライフモニタークリア	*/
#endif
			CMN_ClearFaxComErrorMonitorData();	/** 通信エラーモニタークリア		*/
			CMN_ClearJournalData();				/** ジャーナルデータクリア			*/
		}
		else {						/* ラストクリア */
#if (PRO_ALLRAMCLR_WO_MCP == ENABLE) /* ALL RAM Clearの際、機器パラメータの初期化をしない By S.Fukui Oct.27,1998 */
			CMN_InitializeAllBackUpRAM(2);		/** ユーザー設定データのクリア		*/
#else 
			CMN_InitializeAllBackUpRAM(1);		/** ユーザー設定データのクリア		*/
#endif
			CMN_ClearConsumerOrderData();		/** 消耗品発注データのクリア		*/
			CMN_ClearLifeMonitorData();			/** ライフモニタークリア			*/
#if (PRO_PRINT_TYPE == LED)
			CMN_ClearPrinterLifeMonitorData();	/** プリンタライフモニタークリア	*/
#endif
			CMN_ClearFaxComErrorMonitorData();	/** 通信エラーモニタークリア		*/
			CMN_ClearJournalData();				/** ジャーナルデータクリア			*/
		}

		UpdateLCD();

		if (mode == TEN_1_KEY) {
			InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
			InitializeMachineStatus();									/** マシーンステータスのクリア	*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
			SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
			Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
			InitializeSensor();											/** センサーを初期化			*/
		}
		else {
			InitializeMachineStatus();									/** マシーンステータスクリア */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;	/** オペレーション中セット */
			InitializeSensor();											/** センサー初期化 */
		}

		/* サマータイムのための処理 */
		if (bcd_time.Year == CurrentTimeInBCD.Year) {
			long_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
			SetSummerTimeStatus(long_time);
		}

#if defined (KEISATSU) /* 警察FAX 05/11/18 石橋正和 */
		if (mode == TEN_2_KEY) {
			SYB_MachineParameter[M_PARA_SW_I1] &= ~BYPASS_S1; /* S1バイパスOFF */
		}
#endif

#if (PRO_FBS == ENABLE)
		if (mode == TEN_2_KEY) {	/* 最後のクリア ＋ 輸送ＯＮ */
			/* ミラーキャリッジ輸送モードON */
			OperationMessageToMain.Message = MSG_FBS_TRANSPORT_SET;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
		}
#endif

#if (PRO_MULTI_LINE == ENABLE)
		/* 下記の関数はDPRAMの初期化が全て完了していることが大前提の関数です。 */
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS   |
								  OPT_CHANGED_MEMORY_SWITCH     |
								  OPT_CHANGED_UNI_SWITCH        |
								  OPT_CHANGED_MENTE_SWITCH      |
								  OPT_CHANGED_DRD_TEADCHING_BUF |
								  OPT_CHANGED_MACHINE_PARA);
#endif

#if defined (KEISATSU) /* 警察FAX 05/11/24 石橋正和 */
		SetKeisatsuSettings();
		AttributeTimeoutCheck = 0;
		NCU_HdstShift();
#endif
		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}
#endif

#if defined (KEISATSU) /* 警察FAX 05/11/18 石橋正和 */
/**************************************************************************************************/
/**
	@brief		工場検査用ファーストクリア
	
	@li			
	@param		
	@return		なし
	@note		通常のファーストクリアにS1バイパスON、回線モニタON、通信速度表示を加える
	@date		2005/11/18 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void FactoryFirstClear(void)
{
	TIME_DATA_t		bcd_time;		/* サマータイム用 */
	UDWORD			long_time;		/* サマータイム用 */

#if defined(POPLAR_F)
	/* パワーＯＮ時のウォームアップ中は、キー操作禁止 */
	if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_PRINTER_POWER_ON) {
		NackBuzzer();
		return;
	}
#endif

#if (PRO_FBS == ENABLE)
	if (SYB_ScannerTransportMode) {
		NackBuzzer();
		return;
	}
#endif

	CMN_StringCopy(FunctionDisplayBufferHigh, (UBYTE *)"ﾌｧｰｽﾄ ｸﾘｱ (ｹﾝｻﾖｳ)   ");

	CMN_LongTimeToBCD(&bcd_time, SYB_CurrentTime); /* サマータイム用 */

	if (ConfirmKeyInputOperation(FunctionDisplayBufferHigh, D2W_CheckProgramEnter, ENTER, FUNCTION) == CONFIRM_EXEC) {
		if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & ~SYS_PANEL_BUSY) {	/** 機器動作中 */
			NackBuzzer();
			return;
		}

		CMN_InitializeAllBackUpRAM(0);		/** 機器パラメータ、オールラム		*/
		CMN_ClearConsumerOrderData();		/** 消耗品発注データのクリア		*/
		CMN_ClearLifeMonitorData();			/** ライフモニタークリア			*/
#if (PRO_PRINT_TYPE == LED)
		CMN_ClearPrinterLifeMonitorData();	/** プリンタライフモニタークリア	*/
#endif
		CMN_ClearFaxComErrorMonitorData();	/** 通信エラーモニタークリア		*/
		CMN_ClearJournalData();				/** ジャーナルデータクリア			*/

		UpdateLCD();

		InitializeDRAM_Parameter();									/** ＤＲＡＭ領域を初期化		*/
		InitializeMachineStatus();									/** マシーンステータスのクリア	*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PANEL_BUSY;
		SYS_ErasePixMemoryListRequest = 0;							/** 停電発生初期化				*/
		Init_AnyList(LST_POWEROFF_NOTICE);							/** 停電ステータスのクリア		*/
		InitializeSensor();											/** センサーを初期化			*/

		/* サマータイムのための処理 */
		if (bcd_time.Year == CurrentTimeInBCD.Year) {
			long_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD);
			SetSummerTimeStatus(long_time);
		}
		
		SYB_MachineParameter[M_PARA_SW_I1] |= BYPASS_S1; /* S1バイパスON */
		SYS_MemorySwitch[MEMORY_SW_H0] |= LINE_MONITOR; /* 回線モニタON */
		SYS_MemorySwitch[MEMORY_SW_H1] |= COMMUNICATION_SPEED_DISPLAY; /* 通信速度表示ON */
		
#if (PRO_MULTI_LINE == ENABLE)
		/* 下記の関数はDPRAMの初期化が全て完了していることが大前提の関数です。 */
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_SETTEING_STATUS   |
								  OPT_CHANGED_MEMORY_SWITCH     |
								  OPT_CHANGED_UNI_SWITCH        |
								  OPT_CHANGED_MENTE_SWITCH      |
								  OPT_CHANGED_DRD_TEADCHING_BUF |
								  OPT_CHANGED_MACHINE_PARA);
#endif

#if defined (KEISATSU) /* 警察FAX 05/11/24 石橋正和 */
		SetKeisatsuSettings();
		AttributeTimeoutCheck = 0;
		NCU_HdstShift();
#endif
		ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
	}
}

#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
/*************************************************************************
	module		:[ライフモニタクリアパスコードセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/06/01]
	author		:[本多]
*************************************************************************/
void SetLifeMonitorPasscode(void)  /* lifemonitorbythonda1998/06/01 */
{
	UWORD	passcode;
	passcode = 0;

	/** 古いパスコードを入力させる */
	DisplayStringHigh(0, D2W_SF_ServiceCode);  /* "ﾗｲﾌﾓﾆﾀ ﾊﾟｽｺｰﾄﾞ      " */
	if ((passcode = EnterPassCode(SYB_LifeMonitorPasscode, CHK_PASS_CODE_ENTER, D2W_OldProtectPasscode)) == 0xFFFF) {
		/* 入力終了 */
		return;
	}

	/** パスコードチェックを行う */
	if (passcode != SYB_LifeMonitorPasscode) { /** パスコード不一致 */
		OPR_ChildErrorFlag = INVALID_PROTECT_PASSCODE_ERROR;	/* "ﾌﾟﾛﾃｸﾄｺｰﾄﾞ ｶﾞ ﾁｶﾞｲﾏｽ" */
		NackBuzzer();
		return;
	}

	/**新しいパスコードの入力を行う */
	if ((passcode = EnterPassCode(SYB_LifeMonitorPasscode, PASS_CODE_ENTER_ZERO_OK, D2W_NewProtectPasscode)) == 0xFFFF) {
		/* 入力終了 */
		return;
	}

	SYB_LifeMonitorPasscode = passcode;
	ChildDisplaySetCompleted(D2W_SF_ServiceCode);  /* "ﾗｲﾌﾓﾆﾀ ﾊﾟｽｺｰﾄﾞ      " */
}
#endif

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[ライフモニタを編集する]
	function	:[
		1.以下の項目を順番に編集する
		,読みとり枚数
		,印字枚数
		,送信枚数
		,ドラム交換回数
		,ドラム寿命カウンタ
		,トナー交換回数
		,トナー寿命カウンタ
		,定着機交換回数
		,定着機寿命カウンタ
		,転写ローラー交換回数
		,転写ローラー寿命カウンタ
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/02/27]
	author		:[福本貴吉]
*************************************************************************/
void EditLifeMonitor(void)
{

	/** 読み取り枚数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedLongToASC(&CharacterInput.Buffer[0], SYB_LifeMonitor.ScanCount, 6, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeReadingPage, 6) == OPR_END) {
		return;
	}
	SYB_LifeMonitor.ScanCount = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 100L +
										 CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2));

	/** 印字枚数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedLongToASC(&CharacterInput.Buffer[0], SYB_LifeMonitor.PrintCount, 6, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifePrintingPage, 6) == OPR_END) {
		return;
	}
	SYB_LifeMonitor.PrintCount = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 100L +
										  CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2));

	/** 送信枚数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedLongToASC(&CharacterInput.Buffer[0], SYB_LifeMonitor.TransmitCount, 6, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeTxPage, 6) == OPR_END) {
		return;
	}
	SYB_LifeMonitor.TransmitCount = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 100L +
											 CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2));

#if (PRO_PRINT_TYPE != THERMAL) /* By H.Fujimura 1999/01/06 */
	/** ドラム交換回数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.DrumReplaceCount, 5, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeDrumReplaceCount, 5) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.DrumReplaceCount = (UWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 10 +
													  CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 1));

	/** ドラム寿命カウンター */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedLongToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.DrumLifeCount, 6, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeDrumLifeCount, 6) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.DrumLifeCount = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 100L +
													CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2));

	/** トナー交換回数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.TonerReplaceCount, 5, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeTonerReplaceCount, 5) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.TonerReplaceCount = (UWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 10 +
													   CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 1));

	/** トナー寿命カウンター */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.TonerLifeCount, 5, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeTonerLifeCount, 5) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.TonerLifeCount = (UWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 10 +
													CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 1));

	/** 定着機交換回数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.FuserReplaceCount, 5, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeFuserReplaceCount, 5) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.FuserReplaceCount = (UWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 10 +
													   CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 1));

	/** 定着機寿命カウンター */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedLongToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.FuserLifeCount, 6, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeFuserLifeCount, 6) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.FuserLifeCount = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 100L +
													 CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2));

	/** 転写ローラー交換回数 */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedIntToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.TransferReplaceCount, 5, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeTransferReplaceCount, 5) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.TransferReplaceCount = (UWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 10 +
														  CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 1));

	/** 転写ローラー寿命カウンター */
	ClearCharacterInput();	/* ワークエリア初期化 */
	CMN_UnsignedLongToASC(&CharacterInput.Buffer[0], SYB_PrinterLifeMonitor.TransferLifeCount, 6, '0');
	if (LifeMonitorNumberInput(D2W_SF_LifeTransferLifeCount, 6) == OPR_END) {
		return;
	}
	SYB_PrinterLifeMonitor.TransferLifeCount = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 100L +
														CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 2));
#endif	/* (PRO_PRINT_TYPE != THERMAL) */
	ChildDisplayStringLow(D2W_SetComplete);	/* " **  ｾｯﾄ ｶﾝﾘｮｳ  **  " */
}

/*************************************************************************
	module		:[ライフモニタデータ数値入力]
	function	:[
		1.
	]
	return		:[
		OPR_END      → 入力中止
		OPR_CONTINUE → 入力続行
	]
	common		:[]
	condition	:[]
	comment		:[
		入力範囲
			６桁のとき０～９９９９９９(入力値のチェックは不必要)
			５桁のとき０～  ６５５３５(入力値のチェックが必要)
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/02/27]
	author		:[福本貴吉]
*************************************************************************/
UBYTE LifeMonitorNumberInput(UBYTE *title_wording,	/* 上段表示用ワーディング */
							 UBYTE figure)			/* 桁数 */
{

	UBYTE	key;			/* キー入力		  */
	UBYTE	keytype;		/* キー入力		  */
	UDWORD	input_value;	/* 入力値		  */

	CharacterInput.WritePosition      = figure - 1;
	CharacterInput.CursorPosition     = 0;
	CharacterInput.LcdDisplayPosition = 0;

	/* 上段表示 */
	DisplayStringHigh(0, title_wording);

	/* 入力処理 */
	while (1) {

		/** 下段表示 */
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		CMN_StringCopy(&FunctionDisplayBufferLow[0], CharacterInput.Buffer);
		DisplayStringLow(0, FunctionDisplayBufferLow);
		CursorOn((UBYTE)(CharacterInput.CursorPosition + OPR_LCD_LOWER_ADD));

		/** キーの取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理 */
		switch (keytype) {
		case STOP:			/** ストップキー */
		case KEY_TIME_UP:	/** １分間キー入力なし */
			/** 終了 */
			CursorOff();
			return (OPR_END);
		case ENTER:			/** セットキー */
			/* 入力値が５桁の場合は入力範囲(０～６５５３５)のチェック */
			if (figure == 5) {
	 			input_value = (UDWORD)(CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[0], 4) * 10 +
									   CMN_ASC_ToUnsignedInt(&CharacterInput.Buffer[4], 1));
				if ((input_value < 0) || (input_value > 0xFFFF)) {
					NackBuzzer();
					break;
				}
			}
			CursorOff();
			return (OPR_CONTINUE);
		case NUMBER:		/** 数字キー */
			FixedNumberDataSet(key);
			break;
		case FUNCTION:		/** ＞キー */
			CursorRightRotation();
			break;
		case LEFT_ARROW: 	/** ＜キー */
			CursorLeftRotation();
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif /* (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  */

/*************************************************************************
	module		:[モニタースピーカーＯＮ／ＯＦＦ]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/07/24]
	author		:[山口]
*************************************************************************/
void SetMonitorSpeakerOnOff(void)
{
	if (SYS_MemorySwitch[MEMORY_SW_H0] & LINE_MONITOR) {
		SYS_MemorySwitch[MEMORY_SW_H0] &= ~LINE_MONITOR;
		MonitorSpeakerOff();
	}
	else {
		SYS_MemorySwitch[MEMORY_SW_H0] |= LINE_MONITOR;
		MonitorSpeakerOn();
	}
}

/*************************************************************************
	module		:[メモリダンプ表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/07]
	author		:[渡辺一章]
*************************************************************************/
void MemoryDump(void)
{
	UBYTE	i;
	UBYTE	byte;
	UBYTE	word;
	UBYTE	keytype;
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	num_buf[8 + 1];
	UBYTE	*dump_adr;
	UDWORD	wrk_adr;
	UDWORD	add_pos;
	UDWORD	add_end_pos;
	UDWORD	disp_add_pos;

	is_loop_end = FALSE;

	/* 表示 */
	DisplayStringHigh(0, D2W_SF_MemoryDump);		/* "ﾒﾓﾘﾀﾞﾝﾌﾟ            " */

	/* アドレスの入力 */
	CMN_MemorySetNULL(num_buf, 8, '0');
	if (InputAddressOrLength(D2W_SF_MemoryDumpAddress, 12, 8, num_buf) == FALSE) {
		return;
	}

	wrk_adr = 0;
	for (i = 0; i < 2; i++) {
		wrk_adr |= (UDWORD)(CMN_ASC_ToUnsignedIntHex(&num_buf[i * 4], 4) << (16 - (i * 16)));
	}
	OPR_MemoryDumpAddress = (UBYTE *)wrk_adr;

	/* ダンプを開始するアドレスを上段に表示します */
	ClearDisplayHigh();	/* 追加 1998/01/27 Y.Matsukma */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_UnsignedLongToHexASC_NULL(FunctionDisplayBufferHigh, wrk_adr, 8, '0');
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	/* データ長の入力 */
	CMN_MemorySetNULL(num_buf, 4, '0');
	if (InputAddressOrLength(D2W_SF_MemoryDumpLength, 12, 4, num_buf) == FALSE) {
		return;
	}
	OPR_MemoryDumpLength = (UDWORD)CMN_ASC_ToUnsignedIntHex(num_buf, 4);

	add_pos = (UDWORD)OPR_MemoryDumpAddress;
	add_end_pos = (UDWORD)(OPR_MemoryDumpAddress + OPR_MemoryDumpLength);

	while (is_loop_end != TRUE) {
		disp_add_pos = add_pos;

		/* ダンプアドレスを表示用にセット */
		CMN_UnsignedLongToHexASC_NULL(FunctionDisplayBufferHigh, disp_add_pos, 8, '0');

		/* ダンプ内容のセット */
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
		for (word = 0; word < 4; word++) {
			for (byte = 0; byte < 2; byte++) {
				if (disp_add_pos <= add_end_pos) {
					dump_adr = (UBYTE *)disp_add_pos;
					CMN_HexToASC(&FunctionDisplayBufferLow[(word * 5) + (byte * 2)], (UDWORD)(*dump_adr), 2);
					disp_add_pos++;
				}
			}
		}

		/* 上下段の表示 */
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		DisplayStringLow(0, FunctionDisplayBufferLow);

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			is_loop_end = TRUE;
			break;
		case START:			/* スタートキー */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
			/* 入力がＵＷＯＲＤの為、最大が６４Ｋ－１バイトとなる。
			**（リストは１６バイトバウンダリーでプリントしており、そのとき、１６バイト以下の残はプリント
			** されないような構造になっている。
			** その為、ここで、１６バイトバウンダリーになるように微調整します。
			**  By O.Kimoto 1998/02/20
			*/
			if ((OPR_MemoryDumpLength % 16) != 0) {
				OPR_MemoryDumpLength += 16;
				OPR_MemoryDumpLength &= (UDWORD)(0x0001ffff);
			}
#endif
			FinalListPrintOperation(LST_MEMORY_DUMP);
			is_loop_end = TRUE;
			break;
		case FUNCTION:		/* 機能／＞キー */
			if (add_pos + 8 < add_end_pos) {
				add_pos += (UDWORD)8;
			}
			else {
				NackBuzzer();
			}
			break;
		case LEFT_ARROW:	/* 次原稿／＜キー */
			if (add_pos > (UDWORD)OPR_MemoryDumpAddress) {
				add_pos -= (UDWORD)8;
			}
			else {
				NackBuzzer();
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
		}
	}
}

#if defined (KEISATSU) /* 警察FAX 05/12/12 石橋正和 */
/**************************************************************************************************/
/**
	@brief		通信速度表示ON/OFF
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/12/12 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void DisplayCommunicationSpeed(void)
{
	if (SYS_MemorySwitch[MEMORY_SW_H1] & COMMUNICATION_SPEED_DISPLAY) {
		SYS_MemorySwitch[MEMORY_SW_H1] &= ~COMMUNICATION_SPEED_DISPLAY;
	}
	else {
		SYS_MemorySwitch[MEMORY_SW_H1] |= COMMUNICATION_SPEED_DISPLAY;
	}
}
#endif

/*************************************************************************
	module		:[アドレスorデータ長入力処理]
	function	:[
		1.
	]
	return		:[
		TRUE	:入力完了
		FALSE	:入力中止・タイムアップ
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/08/07]
	author		:[渡辺一章]
*************************************************************************/
UBYTE InputAddressOrLength(UBYTE *title_wording, UBYTE dsp_pos, UBYTE num_len, UBYTE *num_buf)
{
	UBYTE	inp_pos;
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_loop_end;	/* ループ終了で使用 */
	UBYTE	ret;			/* リターン値 */

	inp_pos = 0;
	is_loop_end = FALSE;
	ret = TRUE;

	CMN_StringCopy(FunctionDisplayBufferLow, title_wording);

	while (is_loop_end != TRUE) {
		CMN_StringCopy(&FunctionDisplayBufferLow[dsp_pos], num_buf);
		DisplayStringLow(0, FunctionDisplayBufferLow);
		CursorOn((UBYTE)(OPR_LCD_LOWER_ADD + dsp_pos + inp_pos));

		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ENTER:			/* セットキー */
			is_loop_end = TRUE;
			break;
		case STOP:			/* ストップキー */
		case KEY_TIME_UP:	/* １分間キー入力なし */
			ret = FALSE;
			is_loop_end = TRUE;
			break;
		case FUNCTION:		/* 機能／＞キー */
			if (inp_pos < num_len - 1) {
				inp_pos++;
			}
			else {
				NackBuzzer();
			}
			break;
		case LEFT_ARROW:	/* 次原稿／＜キー */
			if (inp_pos != 0) {
				inp_pos--;
			}
			else {
				NackBuzzer();
			}
			break;
		case NUMBER:		/* 数字キー */
			num_buf[inp_pos] = key;
			if (inp_pos < num_len - 1) {
				inp_pos++;
			}
			break;
		case ONETOUCH:		/* ワンタッチキー */
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
			if ((key >= ONETOUCH_01_KEY) && (key <= ONETOUCH_06_KEY)) {	/* Ａ～Ｆの時 */
				num_buf[inp_pos] = key;
				if (inp_pos < num_len - 1) {
					inp_pos++;
				}
			}
			else {
				NackBuzzer();
			}
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
			if ((key >= ONETOUCH_A_KEY) && (key <= ONETOUCH_F_KEY)) {	/* Ａ～Ｆの時 */
				num_buf[inp_pos] = key;
				if (inp_pos < num_len - 1) {
					inp_pos++;
				}
			}
			else {
				NackBuzzer();
			}
#endif
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
		}
	}

	return(ret);
}

/*************************************************************************
	module		:[テスト用オペレーション]
	function	:[
		1.ＰＲＧ＊＊・・で呼び出されるオペレーション
		2.開発時のテストオペレーション
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		fnc_numberをなくしてkeycodeで見るようにしました 1997/09/18 Y.Matsukuma
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/09/03]
	author		:[江口]
*************************************************************************/
void MaintenanceOperationMode(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	loop;

	loop = 1;

	while (loop) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();
		keycode = GetInputKeyCode();
		switch (keytype) {
		case NUMBER:
		case ONETOUCH:
		case PROGRAM:
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
		case MERCURY:
#endif
			loop = 0;
			break;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
#if defined(POPLAR_F)	/* for debug 1999/11/16 Y.M */
		case SHARP:
			loop = 0;
			break;
#endif
		default:
			NackBuzzer();
			return;
		}
	}

	/* 関数実行 */
	switch (keycode) {
	/* ＩＣＨＯで、「機能＋＊＋０」と間違える可能性があるために変更されたので合わせておきます */
#if (0)
//	case TEN_0_KEY:
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	case ONETOUCH_40_KEY:
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)  /* By H.Fujimura 1999/01/06 */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)
	case ONETOUCH_20_KEY: 
 #else
  #if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
   #if (PRO_PREFIX_KEY == ENABLE)	/* 警察FAX Modify by SMuratec K.W.Q 2005/10/13 */
	case MERCURY_KEY:		/* プレフィックスキー		*/
   #else
	case ONETOUCH_30_KEY:	/* ワンタッチ３０キー		*/
   #endif
  #else
	case ONETOUCH_30_KEY:
  #endif
 #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	case PROGRAM_P06:
#endif
		MaintenanceSwitchMode();		/* 保守用スイッチモード */
		break;
	case TEN_1_KEY:
		MachineStatusMonitor();			/* マシーンステータスモニター */
		break;
	case TEN_2_KEY:
		Class1MonitorPrintOperation();	/* クラス１オンラインモニター */
		break;
	case TEN_3_KEY:
		PrinterStatusMonitor();			/* プリンターステータスモニター */
		break;
#if defined(POPLAR_F) || defined(SATSUKI2) || defined(STOCKHM2)	/* Add by Y.kano 2003/10/02 */
	case TEN_4_KEY:						/* インデックスの総残ページ数/代交のEMPTYファイル数/メモリ残量表示 */
		EmptyAndMemoryAreaDisplay();
		break;
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	case TEN_4_KEY:						/* インデックスの総残ページ数/代交のEMPTYファイル数/メモリ残量表示 */
		EmptyAndMemoryAreaDisplay();	/* 1997/10/30 Y.Matsukuma */
		break;
	case TEN_5_KEY:						/* １回線から送信テストｵﾍﾟﾚｰｼｮﾝ */
		ChangeRxSecondLine();			/* 1998/01/29 Y.Matsukuma */
		break;
#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/22 Eguchi */
	case TEN_6_KEY:						/*InternetFAXﾓﾆﾀｰプリント*/
		IfaxMonitorPrint();
		break;
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
	case ONETOUCH_01_KEY:
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	case ONETOUCH_A_KEY:
#endif
		ServiceReportPrintOperation();	/* サービスレポートプリント */
		break;
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)	/* by K.Watanabe 1998/09/25 */
	case ONETOUCH_02_KEY:
		PrintErrorList();				/* エラーリスト　プリント */
		break;
#endif
#if defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2)
 #if (PRO_DIALIN == ENABLE)		/* 条件追加 2002/07/18 T.Takagi */
	case ONETOUCH_09_KEY:		/** ダイヤルインDTMF検出テスト */
		TestDialinDetectDTMF();
		break;
 #endif
#endif

#if defined(STOCKHM2) || (defined(HINOKI2) && defined(JPNNTT)) || defined(HINOKI3)	/* O.Oshima 2004/11/04 */	/* Y.kano 2005/02/14 */
	case ONETOUCH_13_KEY:	/** ナンバーディスプレイ CAR 検出パラメータモード */
		DisplayCheckSum();
		break;
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/06 */
 #if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)
	case ONETOUCH_19_KEY:	/** ナンバーディスプレイ CAR 検出パラメータモード */
 #else
	case ONETOUCH_29_KEY:	/** ナンバーディスプレイ CAR 検出パラメータモード */
 #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
		OPR_NumberDisplayCarPatternMode();
		break;
#endif
#if defined(POPLAR_F)	/* for debug 1999/11/16 Y.M */
	case TEN_SHARP_KEY:
		NackBuzzer();
		/*SaveReturnAddressAndJumpBegin(); 2000/1/24 Y.M */
		break;
#endif
	default:
		NackBuzzer();
		break;
	}
}

/*************************************************************************
	module		:[マシンステータス表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[とりあえず<PRG * Ｅ>で呼び出す->QATがすんだらもっとわかりにくいところに動かすこと
				  <PRG * * 1>で呼び出すように変更 1996/09/03 Eguchi
				  0～15までのステータス全てを表示するように変更 1997/05/16 M.Kuwahara ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/05/21]
	author		:[松隈]
*************************************************************************/
void MachineStatusMonitor(void)
{
	UBYTE keytype;
	UBYTE page;

	page	 = 1;
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	do {
		if( page == 1 ){
			CMN_HexToASC(&FunctionDisplayBufferHigh[0],  SYS_MachineStatus[SYS_RESOURCE_STATUS],    4);
			CMN_HexToASC(&FunctionDisplayBufferHigh[5],  SYS_MachineStatus[SYS_MACHINE_STATUS],     4);
			CMN_HexToASC(&FunctionDisplayBufferHigh[10], SYS_MachineStatus[SYS_MACHINE_STATUS_NCU], 4);
			CMN_HexToASC(&FunctionDisplayBufferHigh[15], SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE], 4);
			CMN_HexToASC(&FunctionDisplayBufferLow[0],   SYS_MachineStatus[SYS_STOP_SWITCH_STATUS], 4);
			CMN_HexToASC(&FunctionDisplayBufferLow[5],   SYS_MachineStatus[SYS_STOP_SWITCH_STATUS_RESERVE], 4);
			CMN_HexToASC(&FunctionDisplayBufferLow[10], SYS_MachineStatus[SYS_PRINTER_STATUS1],    4);
			CMN_HexToASC(&FunctionDisplayBufferLow[15], SYS_MachineStatus[SYS_PRINTER_STATUS2],    4);
			FunctionDisplayBufferLow[19] = 0x7E;	/* -> */
		}
		else{
			CMN_HexToASC(&FunctionDisplayBufferHigh[0], SYS_MachineStatus[SYS_PRINTER_STATUS3],    4);
			CMN_HexToASC(&FunctionDisplayBufferHigh[5],  SYS_MachineStatus[SYS_SCANNER_STATUS],     4);
			CMN_HexToASC(&FunctionDisplayBufferHigh[10], SYS_MachineStatus[SYS_COVER_STATUS], 		4);
			CMN_HexToASC(&FunctionDisplayBufferHigh[15], SYS_MachineStatus[SYS_SENSOR_STATUS], 		4);
			CMN_HexToASC(&FunctionDisplayBufferLow[0],   SYS_MachineStatus[SYS_ERROR_STATUS],     4);
			CMN_HexToASC(&FunctionDisplayBufferLow[5],   SYS_MachineStatus[SYS_WARNING_STATUS],       4);
			CMN_HexToASC(&FunctionDisplayBufferLow[10],  SYS_MachineStatus[SYS_OTHER_STATUS],      4);
			CMN_HexToASC(&FunctionDisplayBufferLow[15],  SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS], 4);
			FunctionDisplayBufferLow[19] = 0x7F;	/* <- */
		}
		DisplayStringHigh(0, FunctionDisplayBufferHigh);	/* "0000 0000 0000 0000 " */
		DisplayStringLow(0, FunctionDisplayBufferLow);		/* "0000 0000 0000 0000 " */

		OPR_GetKey(KEY_WAIT_ONE_SECOND);
		keytype = GetInputKeyType();
		switch( keytype ){
		case	FUNCTION:
			if( page == 1 ){
				page++;
			}
			break;
		case	LEFT_ARROW:
			if( page != 1 ){
				page--;
			}
			break;
		}
	} while (keytype != STOP);
}

/*************************************************************************
	module		:[クラス１オンラインモニタープリント・コール]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[CLASS1有りの機種のみ有効]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1996/08/21]
	author		:[江口]
*************************************************************************/
void Class1MonitorPrintOperation(void)
{
#if (PRO_CLASS1 == ENABLE)
	FinalListPrintOperation(LST_CL1_ONLINE_MONITOR);
#else
	NackBuzzer();
#endif
}

/*************************************************************************
	module		:[プリンターステータス表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/04/21]
	author		:[渡辺一章]
*************************************************************************/
void PrinterStatusMonitor(void)
{
#if (PRO_PRINT_TYPE == LED)	/* ANZU_Lはとりあえず空にする 1997/06/16 Y.Matsukuma */
	UBYTE	keytype;
	WORD	work;

	do {
		/* 表示用バッファの初期化 */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');

		/* 上段表示内容のセット */
		CMN_HexToASC(&FunctionDisplayBufferHigh[0],  PRN_Paper1SizeData, 3);
		CMN_HexToASC(&FunctionDisplayBufferHigh[4],  PRN_Paper2SizeData, 3);
		CMN_HexToASC(&FunctionDisplayBufferHigh[8],  PRN_Paper3SizeData, 3);
		CMN_HexToASC(&FunctionDisplayBufferHigh[12], PRN_HeaterTemp,     3);
		CMN_HexToASC(&FunctionDisplayBufferHigh[16], AD_Battery(),       3);

		/* 下段表示内容のセット */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[0], PRN_TonerHighCount, 3, '0');
		work = PRN_CalculateDispEnvTemp();
		if (work >= 0) {
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[5], work, 2, '0');
		}
		else {
			FunctionDisplayBufferLow[4] = '-';
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[5], (UWORD)(0 - work), 2, '0');
		}
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[8], PRN_PWM_Duty, 3, '0');
		if (PRN_OutputVoltage >= 0) {
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[12], PRN_OutputVoltage/10, 3, '0');
		}
		else {
			FunctionDisplayBufferLow[11] = '-';
			CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[12], (UWORD)(0 - PRN_OutputVoltage)/10, 3, '0');
		}
/*		CMN_HexToASC(&FunctionDisplayBufferLow[16], PRN_AverageHVT_Ampere, 3);	下記に変更 By M.Tachibana 1997/12/28 */
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[16], PRN_AverageHVT_Ampere, 3, '0');

		/* 上下段の表示 */
		DisplayStringHigh(0, FunctionDisplayBufferHigh);	/* "FFF FFF FFF FFF FFF " */
		DisplayStringLow(0,  FunctionDisplayBufferLow);		/* "999 -99 999-999 FFF " */

		/* キー待ち（１秒毎に表示を更新） */
		OPR_GetKey(KEY_WAIT_ONE_SECOND);
		keytype = GetInputKeyType();
	} while (keytype != STOP);
#endif

#if defined(HINOKI2) || defined(HINOKI3)	/* コピー時のサーマルヘッドの温度とプレヒート印加パルス幅をモニターする 2004/02/04 Y.Kano */
	UBYTE	keytype;
	UBYTE	themistor;

	if (SYB_LC821033_Flg) {		/* LC821033対応フラグが立っている時にのみ */
		do {
			/* 表示用バッファの初期化 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_MemorySetNULL(FunctionDisplayBufferLow,  OPR_DISPLAY_MAX, ' ');

			/* サーマルヘッド温度の読出し */
			themistor = (UBYTE)AD_Thermistor();

			/* 上段表示内容のセット */
			CMN_StringCopy(&FunctionDisplayBufferHigh[0], (UBYTE *)"ｻｰﾏﾙﾍｯﾄﾞｵﾝﾄﾞ :");
			CMN_HexToASC(&FunctionDisplayBufferHigh[15], themistor, 3);

			/* 下段表示内容のセット */
			CMN_StringCopy(&FunctionDisplayBufferLow[0],  (UBYTE *)"ﾌﾟﾚﾋｰﾄﾊﾟﾙｽﾊﾊﾞ:");
			CMN_HexToASC(&FunctionDisplayBufferLow[15], CalcPreHeatStrobeTime(), 3);

			/* 上下段の表示 */
			DisplayStringHigh(0, FunctionDisplayBufferHigh);	/* "ｻｰﾏﾙﾍｯﾄﾞｵﾝﾄﾞ :  FF  " */
			DisplayStringLow(0,  FunctionDisplayBufferLow);		/* "ﾌﾟﾚﾋｰﾄｲﾝｼﾞﾊﾊﾞ:  FF  " */

			/* キー待ち（１秒毎に表示を更新） */
			OPR_GetKey(KEY_WAIT_ONE_SECOND);
			keytype = GetInputKeyType();
		} while (keytype != STOP);
	}
#endif
}

/*************************************************************************
	module		:[インデックスの総残ページ数/代交のEMPTYファイル数/メモリ残量表示]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[容量しだいで変更します]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/10/30]
	author		:[松隈]
*************************************************************************/
#if defined(POPLAR_F) || defined(SATSUKI2) || defined(STOCKHM2)	/* Add by Y.Kano 2003/10/02 */
void	EmptyAndMemoryAreaDisplay(void)
{

 	UWORD	mem_area;
	UWORD	downmem;
	UWORD	index;
	UWORD	block_total;
	UWORD	block_emp;
	UBYTE	keytype;
	UBYTE	cnt;

	do {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		downmem = 0;
		for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {
			if ( SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_EMPTY ) {
				downmem++;		/** ある */
			}
		}

		FunctionDisplayBufferHigh[0] = 'D';
		FunctionDisplayBufferHigh[1] = '.';
		FunctionDisplayBufferHigh[2] = 'E';
		FunctionDisplayBufferHigh[3] = 'M';
		FunctionDisplayBufferHigh[4] = 'P';
		FunctionDisplayBufferHigh[5] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[6], downmem, 3, ' ');

		index = MEM_CountTotalEmptyPage ();

		FunctionDisplayBufferHigh[10] = 'I';
		FunctionDisplayBufferHigh[11] = '.';
		FunctionDisplayBufferHigh[12] = 'E';
		FunctionDisplayBufferHigh[13] = 'M';
		FunctionDisplayBufferHigh[14] = 'P';
		FunctionDisplayBufferHigh[15] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[16], index, 4, ' ');

		CMN_StringCopy(FunctionDisplayBufferLow, D2W_MemoryAreaLong);	/* "             ﾒﾓﾘ   %" */
		block_total = (UWORD)MEM_CountTotalStoreBlock();
		block_emp = (UWORD)MEM_CountTotalEmptyBlock();
		mem_area = (UWORD)MEM_CountEmptyBlockRate();
		FunctionDisplayBufferLow[4] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[0], block_total, 4, ' ');
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[5], block_emp, 4, ' ');
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[16], mem_area, 3, ' ');

		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		DisplayStringLow(0, FunctionDisplayBufferLow);

		/* キー待ち（１秒毎に表示を更新） */
		OPR_GetKey(KEY_WAIT_ONE_SECOND);
		keytype = GetInputKeyType();
	} while (keytype != STOP);
}
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* ﾎﾟﾌﾟﾗのROM容量削減の為、条件ｺﾝﾊﾟｲﾙ追加 by K.Watanabe 1998/04/24 */
void	EmptyAndMemoryAreaDisplay(void)
{

 	UWORD	mem_area;
	UWORD	downmem;
	UWORD	index;
	UBYTE	keytype;
	UBYTE	cnt;

	do {
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');

		downmem = 0;
		for (cnt = 0; cnt < SYS_MEMORY_RX_MAX; cnt++) {
			if ( SYB_MemoryRxPrint[cnt].Status == SYS_MEMORY_RX_EMPTY ) {
				downmem++;		/** ある */
			}
		}

		FunctionDisplayBufferHigh[0] = 'D';
		FunctionDisplayBufferHigh[1] = '.';
		FunctionDisplayBufferHigh[2] = 'E';
		FunctionDisplayBufferHigh[3] = 'M';
		FunctionDisplayBufferHigh[4] = 'P';
		FunctionDisplayBufferHigh[5] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[6], downmem, 3, ' ');

		index = MEM_CountTotalEmptyPage ();

		FunctionDisplayBufferHigh[10] = 'I';
		FunctionDisplayBufferHigh[11] = '.';
		FunctionDisplayBufferHigh[12] = 'E';
		FunctionDisplayBufferHigh[13] = 'M';
		FunctionDisplayBufferHigh[14] = 'P';
		FunctionDisplayBufferHigh[15] = ':';
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[16], index, 4, ' ');

		CMN_StringCopy(FunctionDisplayBufferLow, D2W_MemoryAreaLong);	/* "             ﾒﾓﾘ   %" */
		mem_area = (UWORD)MEM_CountEmptyBlockRate();
		CMN_UnsignedIntToASC(&FunctionDisplayBufferLow[16], mem_area, 3, ' ');

		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		DisplayStringLow(0, FunctionDisplayBufferLow);

		/* キー待ち（１秒毎に表示を更新） */
		OPR_GetKey(KEY_WAIT_ONE_SECOND);
		keytype = GetInputKeyType();
	} while (keytype != STOP);
}
#endif	/* (PRO_KEYPANEL == PANEL_ANZU_L) */

/*************************************************************************
	module		:[サービスレポート・コール]
	function	:[
		1.サービスレポートの印字を行う
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1997/05/20]
	author		:[桑原]
*************************************************************************/
void ServiceReportPrintOperation(void)
{
	FinalListPrintOperation(LST_SERVICE_LIST);
}

/*************************************************************************
	module		:[エラーリスト　プリント]
	function	:[
		1.ワーディングチェック用にリストを起動します
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[
		沖仕様のワーディングチェック用にこの関数を作成しました
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/09/24]
	author		:[渡辺一章]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE)
void PrintErrorList(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_loop_end;

	ClearDisplayHigh();
	ClearDisplayLow();

	is_loop_end = FALSE;
	while (is_loop_end != TRUE) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
			is_loop_end = TRUE;
			break;
		case ONETOUCH:		/* ワンタッチキー */
			switch (key) {
			case ONETOUCH_01_KEY:	/* 手動送信送信証 */
				FinalListPrintOperation(LST_MANUAL_TXCONF_REPORT);
				break;
			case ONETOUCH_02_KEY:	/* チェックメッセージＢ（交信エラー） */
				FinalListPrintOperation(LST_COMMERR_CHECKMSG);
				break;
			case ONETOUCH_03_KEY:	/* チェックメッセージＥ（手動送信エラー） */
				FinalListPrintOperation(LST_MNLERR_CHECKMSG);
				break;
 #if (PRO_SECURITY_RX == ENABLE)
			case ONETOUCH_04_KEY:	/* セキュリティ受信メモリーオーバー */
				FinalListPrintOperation(LST_SEC_RX_MEMOVER_CHKMSG);
				break;
 #endif
			case ONETOUCH_05_KEY:	/* 親展受信通知 */
				FinalListPrintOperation(LST_SECURERCV_NOTICE);
				break;
 #if (PRO_F_CODE == ENABLE)
			case ONETOUCH_06_KEY:	/* Ｆコード受信通知 */
				FinalListPrintOperation(LST_FCODE_BOXRCV_NOTICE);
				break;
 #endif
			default:
				NackBuzzer();
				break;
			}
			break;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif	/* (PRO_KEYPANEL == PANEL_POPLAR_B) && (PRO_OKI == ENABLE) */

/*************************************************************************
	module		:[保守用スイッチモード]
	function	:[
		1.保守用スイッチのセット／クリアを実行
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[PRG**0 ←　PRG*6から変更。1996/09/03　Eguchi]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1995/07/18]
	author		:[江口]
*************************************************************************/
void MaintenanceSwitchMode(void)
{
	UBYTE	mode;

	/* データのセット */
	OPR_Buf.SoftSwCtrl.ItemWording  = D2W_SF_MaintenanceSet;		/* [Set Maintenance ] */
	OPR_Buf.SoftSwCtrl.SetParameter = &SYB_MaintenanceSwitch[0];	/* ﾏｼｰﾝﾊﾟﾗﾒｰﾀ */
	OPR_Buf.SoftSwCtrl.SwitchMax    = SYS_MEMORY_SWITCH_MAX;		/* 最大１００個 */
	OPR_Buf.SoftSwCtrl.SelectSwitch = 0;							/* 初期値０（Ａ０）SATSUKI2では（００）*/

	/* 編集するかクリアするか選択させる */
	mode = SelectSetClearMode();

	if (mode == PARAMETER_SET) { /* 編集の場合 */
		SetSoftSwitch();
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_MENTE_SWITCH);
#endif
	}
	else if (mode == PARAMETER_CLEAR) {/* クリアの場合 */
		ClearSoftSwitch(MAINTENANCE_SWITCH_MODE);
#if (PRO_MULTI_LINE == ENABLE)
		MAN_ChangedSRAM_Parameter(OPT_CHANGED_MENTE_SWITCH);
#endif
	}
	else { /* 終了OPR_END */
		return;
	}
}

/*************************************************************************
	module		:[１回線から送信テストｵﾍﾟﾚｰｼｮﾝ（２回線用）]
	function	:[
		1.２回線目を受信専用、又は送受信にする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1998/01/29]
	author		:[松隈]
*************************************************************************/
#if (PRO_KEYPANEL == PANEL_ANZU_L)
void ChangeRxSecondLine(void)
{
	if (OPT_CountModems() <= 1) {
		NackBuzzer();
		return;
	}

	if (CHK_UNI_Line1_TxRx() == (UBYTE)EXCLUSIVE_RX) {
		SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~((UBYTE)(LINE1_TX_ONLY | LINE1_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UBYTE)(EXCLUSIVE_TRX << 2);
	}
	else {
		SYB_MachineUniqSwitch[UNIQ_SW_A7] &= ~((UBYTE)(LINE1_TX_ONLY | LINE1_RX_ONLY));
		SYB_MachineUniqSwitch[UNIQ_SW_A7] |= (UBYTE)(EXCLUSIVE_RX << 2);
	}
}
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/13 Y.Matsukuma */
/*************************************************************************
	module		:[ミノルタ用テストプリントオペレーション]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SHC]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/05/12]
	author		:[松隈]
*************************************************************************/
void MinoltaTestOperation(UBYTE key)
{
	UWORD	pattern;
	UWORD	pages;
	UWORD	time;
	UWORD	repeat;
	UDWORD	page_ck;

	pattern = 0;
	pages	= 0;
	time	= 0;
	repeat	= 0;
	page_ck = 0;

	if (CMN_CheckPrinting()	== TRUE || OPR_MinoltaPatternCheck != 0xFF) {	/* テストプリント中 */
		OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
		NackBuzzer();
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferHigh[0]  = 'B';
	FunctionDisplayBufferHigh[1]  = 'o';
	FunctionDisplayBufferHigh[2]  = 'x';
	FunctionDisplayBufferHigh[3]  = ' ';
	FunctionDisplayBufferHigh[4]  = 'N';
	FunctionDisplayBufferHigh[5]  = 'o';
	FunctionDisplayBufferHigh[6]  = '.';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	pattern = FixedLengthNumberInput(1, 1, SYS_MINOLTA_TEST_FUNC_MAX-1, (UBYTE)18, NULL);
	if (pattern == 0xFFFF) {
		return;
	}
	if ((SYS_MinoltaTestFuncData[pattern].Status != SYS_FUNC_TEST_DATA_STORE) 
		&& (SYS_MinoltaTestFuncData[pattern].Status != SYS_FUNC_TEST_DATA_PRINT)) {	/* ﾃｽﾄﾌﾟﾘﾝﾄ管理ﾃｰﾌﾞﾙにﾃﾞｰﾀが登録されてない */
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		NackBuzzer();
		return;
	}

	DisplayStringHigh(0, D2W_InputPageCount);
	pages = FixedLengthNumberInput(1, 1, 9999, (UBYTE)16, NULL);
	if (pages == 0xFFFF) {
		return;
	}

	if (key == HOLD) {

 #if (PRO_KEYPANEL == PANEL_ANZU_L)
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferHigh[0]  = 'I';
		FunctionDisplayBufferHigh[1]  = 'n';
		FunctionDisplayBufferHigh[2]  = 't';
		FunctionDisplayBufferHigh[3]  = 'e';
		FunctionDisplayBufferHigh[4]  = 'r';
		FunctionDisplayBufferHigh[5]  = 'v';
		FunctionDisplayBufferHigh[6]  = 'a';
		FunctionDisplayBufferHigh[7]  = 'l';
		FunctionDisplayBufferHigh[9]  = 't';
		FunctionDisplayBufferHigh[10] = 'i';
		FunctionDisplayBufferHigh[11] = 'm';
		FunctionDisplayBufferHigh[12] = 'e';
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		time = FixedLengthNumberInput(0, 0, 9999, (UBYTE)16, NULL);
		if (time == 0xFFFF) {
			return;
		}

		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferHigh[0]  = 'R';
		FunctionDisplayBufferHigh[1]  = 'e';
		FunctionDisplayBufferHigh[2]  = 'p';
		FunctionDisplayBufferHigh[3]  = 'e';
		FunctionDisplayBufferHigh[4]  = 'a';
		FunctionDisplayBufferHigh[5]  = 't';
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		repeat = FixedLengthNumberInput(1, 1, 9999, (UBYTE)16, NULL);
		if (repeat == 0xFFFF) {
			return;
		}

		if (repeat > 0) {
			page_ck = (UDWORD)((UDWORD)repeat * (UDWORD)pages);
			if (page_ck > 65535) {
				SYS_MinoltaFuncPagesData = 0;
				OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
				NackBuzzer();
				return;
			}
			SYS_MinoltaFuncPagesData = pages;
			pages = (UWORD)page_ck;
		}

 #else	/* (PRO_KEYPANEL == PANEL_POPLAR_B) */

		if (pages == 9999) {
			SYS_MinoltaFuncPagesData = 65535;
			pages = 65535;	/* 無限設定 */
		}
		else {
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			FunctionDisplayBufferHigh[0]  = 'I';
			FunctionDisplayBufferHigh[1]  = 'n';
			FunctionDisplayBufferHigh[2]  = 't';
			FunctionDisplayBufferHigh[3]  = 'e';
			FunctionDisplayBufferHigh[4]  = 'r';
			FunctionDisplayBufferHigh[5]  = 'v';
			FunctionDisplayBufferHigh[6]  = 'a';
			FunctionDisplayBufferHigh[7]  = 'l';
			FunctionDisplayBufferHigh[9]  = 't';
			FunctionDisplayBufferHigh[10] = 'i';
			FunctionDisplayBufferHigh[11] = 'm';
			FunctionDisplayBufferHigh[12] = 'e';
			DisplayStringHigh(0, FunctionDisplayBufferHigh);
			time = FixedLengthNumberInput(0, 0, 9999, (UBYTE)16, NULL);
			if (time == 0xFFFF) {
				return;
			}
			if (time != 0) {
				time += 5;	/* 後回転の時間を考慮する */
			}

			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			FunctionDisplayBufferHigh[0]  = 'R';
			FunctionDisplayBufferHigh[1]  = 'e';
			FunctionDisplayBufferHigh[2]  = 'p';
			FunctionDisplayBufferHigh[3]  = 'e';
			FunctionDisplayBufferHigh[4]  = 'a';
			FunctionDisplayBufferHigh[5]  = 't';
			DisplayStringHigh(0, FunctionDisplayBufferHigh);
			repeat = FixedLengthNumberInput(1, 1, 9999, (UBYTE)16, NULL);
			if (repeat == 0xFFFF) {
				return;
			}

			if (repeat == 9999) {
				SYS_MinoltaFuncPagesData = pages;
				pages = 65535;	/* 無限設定 */
			}
			else {
				page_ck = (UDWORD)((UDWORD)repeat * (UDWORD)pages);
				if (page_ck > 65535) {
					SYS_MinoltaFuncPagesData = 0;
					OPR_ChildErrorFlag = TOO_MANY_DIGITS_ERROR;
					NackBuzzer();
					return;
				}
				SYS_MinoltaFuncPagesData = pages;
				pages = (UWORD)page_ck;
			}
		}

 #endif

	}

	/* このアイテムは、表示用に使用するため、FLASH・HOLDどちらでも同じ 1998/08/31 Y.Matsukuma */
	OPR_MinoltaPatternItem 	= OPR_MINOLTA_FLASH;
	OPR_MinoltaDisplayCheck = (UBYTE)pattern;
	if (OPR_MinoltaDisplayCheck < 0x0A) {
		OPR_MinoltaDisplayCheck = OPR_MinoltaDisplayCheck + 0x30;
	}
	CMN_SetMinoltaTestFuncData(pattern, pages, time);

}


/*************************************************************************
	module		:[ミノルタテストプリントデータクリア]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SHC]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1998/05/15]
	author		:[松隈]
*************************************************************************/
void	ClearMinoltaTestPrintArea(void)
{
	UWORD	pattern;

	pattern = 0;

	if (CMN_CheckPrinting()	== TRUE || OPR_MinoltaPatternCheck != 0xFF) {	/* プリント中 */
		OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
		NackBuzzer();
		return;
	}

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferHigh[0] = 'E';
	FunctionDisplayBufferHigh[1] = 'r';
	FunctionDisplayBufferHigh[2] = 'a';
	FunctionDisplayBufferHigh[3] = 's';
	FunctionDisplayBufferHigh[4] = 'e';
	FunctionDisplayBufferHigh[6] = 'B';
	FunctionDisplayBufferHigh[7] = 'o';
	FunctionDisplayBufferHigh[8] = 'x';
	FunctionDisplayBufferHigh[10] = 'N';
	FunctionDisplayBufferHigh[11] = 'o';
	FunctionDisplayBufferHigh[12] = '.';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);
	pattern = FixedLengthNumberInput(1, 1, SYS_MINOLTA_TEST_FUNC_MAX-1, (UBYTE)18, NULL);
	if (pattern == 0xFFFF) {
		return;
	}

	/*-----------------------------------------*
	 *　インデックス・エリアの初期化           *
	 *-----------------------------------------*/
	MEM_ClearDoc(SYS_MEM_PC_RX_FILE, pattern, 0);

	/*-----------------------------------------*
	 *　ＰＣプリント原稿管理テーブル初期化     *
	 *-----------------------------------------*/
	SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
	SYB_PcRxPrint.ExecutiveNumber = 0;
	SYB_PcRxPrint.RemainMultiPrintCount = 0;
	SYB_PcRxPrint.StorePage = 0;
	SYB_PcRxPrint.PrintPage = 1;
	SYB_PcRxPrint.ErasePage = 1;
	SYB_PcRxPrint.PrintEndPage = 0;

	SYS_MinoltaTestFuncData[pattern].Status = SYS_FUNC_TEST_DATA_EMPTY;
	SYS_MinoltaTestFuncData[pattern].IntervalTimer = 0;
	SYS_MinoltaTestFuncData[0].Status = SYS_FUNC_TEST_DATA_OFF;	/* ０番目は未使用 */
	SYS_MinoltaFuncIntervalTimer = 0;

	ChildDisplayStringLow(D2W_ClearComplete);	/* " **  ｸﾘｱ ｶﾝﾘｮｳ  **  " */
}


/*************************************************************************
	module		:[ミノルタ用画像パターン]
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
	date		:[1998/06/29]
	author		:[松隈]
*************************************************************************/
void	MinoltaTestPatternPrint(UBYTE key)
{
	UWORD	ptn;
	UWORD	pages;

	ptn = 0;
	pages = 0;

	if (CMN_CheckPrinting()	== TRUE || OPR_MinoltaPatternCheck != 0xFF) {	/* テストプリント中 */
		OPR_ChildErrorFlag = PRINTER_IN_USE_ERROR;
		NackBuzzer();
		return;
	}

#if (PRO_KEYPANEL == PANEL_ANZU_L)	/* 1998/10/06 Y.Matsukuma */
	switch (key) {
	case ONETOUCH_A_KEY:
		ptn = 1;
		pages = 1;
		break;
	case ONETOUCH_B_KEY:
		ptn = 1;
		pages = 2;
		break;
	case ONETOUCH_C_KEY:
		ptn = 1;
		pages = 3;
		break;
	case ONETOUCH_D_KEY:
		ptn = 2;
		pages = 1;
		break;
	case ONETOUCH_E_KEY:
		ptn = 2;
		pages = 2;
		break;
	case ONETOUCH_F_KEY:
		ptn = 4;
		pages = 1;
		break;
	case ONETOUCH_G_KEY:
		ptn = 5;
		pages = 1;
		break;
	case ONETOUCH_H_KEY:
		OPR_MinoltaPatternCheck = 1;
		ptn = 4;
		pages = 1;
		break;
	case ONETOUCH_I_KEY:
		OPR_MinoltaPatternCheck = 1;
		ptn = 2;
		pages = 1;
		break;
	case ONETOUCH_J_KEY:
		OPR_MinoltaPatternCheck = 4;
		ptn = 1;
		pages = 5;
		break;
	case ONETOUCH_K_KEY:
		ptn = 6;
		pages = 1;
		break;
	case ONETOUCH_L_KEY:
		ptn = 6;
		pages = 8;
		break;
	case ONETOUCH_M_KEY:
		ptn = 6;
		pages = 41;
		break;
	case ONETOUCH_N_KEY:
		ptn = 6;
		pages = 968;
		break;
	case ONETOUCH_O_KEY:
		if (CMN_CheckMinoltaTestDataStore(6) == 1) {
			SYS_MinoltaFuncPagesData = 1;
			OPR_MinoltaPatternItem = OPR_MINOLTA_ONETOUCH;
			OPR_MinoltaDisplayCheck = key;
			CMN_SetMinoltaTestFuncData(6, 468, 25);
		}
		else {
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
			NackBuzzer();
		}
		return;
	case ONETOUCH_P_KEY:
		OPR_MinoltaPatternCheck = 2;
		ptn = 2;
		pages = 1;
		break;
	case ONETOUCH_Q_KEY:
		OPR_MinoltaPatternCheck = 1;
		ptn = 2;
		pages = 2;
		break;
	case ONETOUCH_R_KEY:
		ptn = 1;
		pages = 5;
		break;
	default:
		NackBuzzer();
		return;
	}

#else	/* ポプラ */

	switch (key) {
	case ONETOUCH_01_KEY:
		ptn = 1;
		pages = 1;
		break;
	case ONETOUCH_02_KEY:
		ptn = 1;
		pages = 2;
		break;
	case ONETOUCH_03_KEY:
		ptn = 1;
		pages = 3;
		break;
	case ONETOUCH_04_KEY:
		ptn = 2;
		pages = 1;
		break;
	case ONETOUCH_05_KEY:
		ptn = 2;
		pages = 2;
		break;
	case ONETOUCH_06_KEY:
		ptn = 4;
		pages = 1;
		break;
	case ONETOUCH_07_KEY:
		ptn = 5;
		pages = 1;
		break;
	case ONETOUCH_08_KEY:
		OPR_MinoltaPatternCheck = 1;
		ptn = 4;
		pages = 1;
		break;
	case ONETOUCH_09_KEY:
		OPR_MinoltaPatternCheck = 1;
		ptn = 2;
		pages = 1;
		break;
	case ONETOUCH_10_KEY:
		OPR_MinoltaPatternCheck = 4;
		ptn = 1;
		pages = 5;
		break;
	case ONETOUCH_11_KEY:
		ptn = 6;
		pages = 1;
		break;
	case ONETOUCH_12_KEY:
		ptn = 6;
		pages = 8;
		break;
	case ONETOUCH_13_KEY:
		ptn = 6;
		pages = 41;
		break;
	case ONETOUCH_14_KEY:
		ptn = 6;
		pages = 968;
		break;
	case ONETOUCH_15_KEY:
		if (CMN_CheckMinoltaTestDataStore(6) == 1) {
			SYS_MinoltaFuncPagesData = 1;
			OPR_MinoltaPatternItem = OPR_MINOLTA_ONETOUCH;
			OPR_MinoltaDisplayCheck = key;
			CMN_SetMinoltaTestFuncData(6, 468, 25);
		}
		else {
			OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
			NackBuzzer();
		}
		return;
	case ONETOUCH_16_KEY:
		OPR_MinoltaPatternCheck = 2;
		ptn = 2;
		pages = 1;
		break;
	case ONETOUCH_17_KEY:
		OPR_MinoltaPatternCheck = 1;
		ptn = 2;
		pages = 2;
		break;
	case ONETOUCH_18_KEY:
		ptn = 1;
		pages = 5;
		break;
	default:
		NackBuzzer();
		return;
	}
#endif
	if (CMN_CheckMinoltaTestDataStore(ptn) == 1) {
		if (OPR_MinoltaPatternItem != OPR_MINOLTA_PROGRAM) {
			OPR_MinoltaPatternItem = OPR_MINOLTA_ONETOUCH;
			OPR_MinoltaDisplayCheck = key;
		}
		CMN_SetMinoltaTestFuncData(ptn, pages, 0);
	}
	else {
		OPR_ChildErrorFlag = NO_STORED_DOCUMENT_ERROR;
		NackBuzzer();
	}

}


/*************************************************************************
	module		:[次の画像パターン]
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
	date		:[1998/07/07]
	author		:[松隈]
*************************************************************************/
void	MinoltaTestPatternPrintCheck(void)
{
	if (OPR_MinoltaPatternCheck == 1) {
		CMN_SetMinoltaTestFuncData(5, 1, 0);
		OPR_MinoltaPatternCheck = 0xFF;
		OPR_MinoltaPagesCheck	= 0;	/* 1998/08/27 Y.Murata */
		OPR_MinoltaOnetouch		= 0;
	}
	else if (OPR_MinoltaPatternCheck == 2) {
		CMN_SetMinoltaTestFuncData(5, 1, 0);
		OPR_MinoltaPatternCheck = 3;
	}
	else if (OPR_MinoltaPatternCheck == 3) {
		CMN_SetMinoltaTestFuncData(1, 2, 0);
		OPR_MinoltaPatternCheck = 0xFF;
		OPR_MinoltaPagesCheck	= 0;	/* 1998/08/27 Y.Murata */
		OPR_MinoltaOnetouch		= 0;
	}
	else if (OPR_MinoltaPatternCheck == 4) {
		CMN_SetMinoltaTestFuncData(2, 2, 0);
		OPR_MinoltaPatternCheck = 5;
	}
	else if (OPR_MinoltaPatternCheck == 5) {
		CMN_SetMinoltaTestFuncData(4, 1, 0);
		OPR_MinoltaPatternCheck = 6;
	}
	else if (OPR_MinoltaPatternCheck == 6) {
		CMN_SetMinoltaTestFuncData(5, 1, 0);
		OPR_MinoltaPatternCheck = 7;
	}
	else if (OPR_MinoltaPatternCheck == 7) {
		CMN_SetMinoltaTestFuncData(7, 1, 0);
		OPR_MinoltaPatternCheck = 0xFF;
		OPR_MinoltaPagesCheck	= 0;	/* 1998/08/27 Y.Murata */
		OPR_MinoltaOnetouch		= 0;
	}
	else if (OPR_MinoltaPatternCheck == 8) {
		MinoltaTestPatternPrintPG();
	}
	else {	/* 1998/08/27 Y.Murata */
		OPR_MinoltaPatternCheck = 0xFF;
		OPR_MinoltaPagesCheck	= 0;
		OPR_MinoltaOnetouch		= 0;
	}
}


/*************************************************************************
	module		:[ミノルタ用画像パターン(PG)]
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
	date		:[1998/07/20]
	author		:[松隈]
*************************************************************************/
void	MinoltaTestPatternPrintPG(void)
{
	UWORD ptn;
	UWORD pages;
	UWORD time;
	UBYTE i;
	UBYTE j;

	ptn = 0;
	pages = 0;
	time = 0;
	i = 0;
	j = 0;

	if (SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[OPR_MinoltaPagesCheck] > 0x40) {
		ptn = (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[OPR_MinoltaPagesCheck] - 0x40);
		OPR_MinoltaPagesCheck++;
	}
	else {
		ptn = (UWORD)1;
	}

	for (; SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[OPR_MinoltaPagesCheck] < 0x40; OPR_MinoltaPagesCheck++) {
		if (SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[OPR_MinoltaPagesCheck] == NULL) {
			OPR_MinoltaPatternCheck = 0xFF;
			break;
		}
		i++;
	}
	j = OPR_MinoltaPagesCheck;
	if (i == 4) {
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)1;
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)10;
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)100;
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)1000;
	}
	else if (i == 3) {
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)1;
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)10;
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)100;
	}
	else if (i == 2) {
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)1;
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)10;
	}
	else if (i == 1) {
		pages += (UWORD)(SYB_OnetouchDial[OPR_MinoltaOnetouch].Name[--j] - 0x30) * (UWORD)1;
	}
	else if (i == 0 || i > 4) {
		pages = (UWORD)1;
	}

	CMN_SetMinoltaTestFuncData(ptn, pages, time);

}


/*************************************************************************
	module		:[ミノルタパターンプリント表示]
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
	date		:[1998/08/31]
	author		:[松隈]
*************************************************************************/
void	MinoltaTestPatternDisplay(void)
{
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');

	switch (OPR_MinoltaPatternItem) {
	case OPR_MINOLTA_FLASH:
	case OPR_MINOLTA_HOLD:
		/* フラッシュorホールド */
		FunctionDisplayBufferHigh[0] = 'B';
		FunctionDisplayBufferHigh[1] = 'o';
		FunctionDisplayBufferHigh[2] = 'x';
		if(OPR_MinoltaDisplayCheck < 0x30) {
			CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[3], (UWORD)OPR_MinoltaDisplayCheck, 2, '0');
		}
		else {
			FunctionDisplayBufferHigh[3] = OPR_MinoltaDisplayCheck;
		}
		break;
	case OPR_MINOLTA_ONETOUCH:
		/* ワンタッチプリント */
		FunctionDisplayBufferHigh[0] = OPR_MinoltaDisplayCheck;
		break;
	case OPR_MINOLTA_PROGRAM:
		/* プログラムワンタッチプリント */
		FunctionDisplayBufferHigh[0] = OPR_PROGRAM_MARK;
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[1], OPR_MinoltaDisplayCheck, 2, '0');
		break;
	case 0xFF:	/* ストップ */
		/*CMN_StringCopy(FunctionDisplayBufferHigh, D2W_SF_Stop);*/
		break;
	default:
		break;
	}

	ClearDisplayHigh();
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

}
#endif



#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* 1998/05/22 Eguchi */
/*************************************************************************
	module		:[インターネットFAXモニター印字起動]
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
	date		:[1998/05/22]
	author		:[M.Eguchi]
*************************************************************************/
void	IfaxMonitorPrint(void)
{
	FinalListPrintOperation(LST_INF_MONITOR);
}
#endif



#if (PRO_MODEM == R288F) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[回線テスト（Ｒ２８８Ｆ用）]
	function	:[
		1.リレーテスト
		2.トーナルテスト
		3.ＤＴＭＦテスト
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void R288F_LineFunctionMode(void)
{
	UBYTE	keytype;
	UBYTE	func_number;

	func_number = 0;
	tskno_MDM_FactoryTask == 0xffff;
	SYS_FactoryFuncReq = 0;

	while (1) {
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/25 */
		DisplayStringHigh(0, D2W_SF_KEIDEN_RelayTest + (OPR_WORDING_LEN * func_number));
#else
		DisplayStringHigh(0, D2W_SF_PhoneTest + (OPR_WORDING_LEN * func_number));
#endif		/* End of (defined (KEISATSU)) */
		ClearDisplayLow();
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();

		switch (keytype) {
		case FUNCTION:
			func_number++;
#if defined (KEISATSU)		/* 警察FAX Modify by SMuratec K.W.Q 2005/10/25 */
			if (func_number > 5) {			/* 警察FAX DVT_ID 15 Modify by SMuratec K.W.Q 2005/11/05 */
				func_number = 0;
			}
#else
			if (func_number > 2) {
				func_number = 0;
			}
#endif		/* End of (defined (KEISATSU)) */
			break;
		case ENTER:
			/* データ初期化 */
			SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_START;
			SYS_FactoryModem.Kind = 0xff;
			SYS_FactoryModem.BaudRate = 0xff;
			SYS_FactoryModem.DataRate = 0xff;
			SYS_FactoryModem.PIX_Pattern	= 0xff;
			if (tskno_NCU_Task != 0xffff) {
				del_tsk(&tskno_NCU_Task);/* Add J.M 1994/05/12 */
			}
			cre_tsk(&tskno_MDM_FactoryTask, TSK_MDM_FACTORYFUNCTIONTASK, 0);
			LineFuncTxMsg.Item = FROM_OPERATION;
			LineFuncTxMsg.Message = FIP_TEST_CMD;
#if (0)
** 			/* メールボックス変更 By O.Kimoto 1998/05/22 */
**			snd_msg(mbxno.MDM_Task,&LineFuncTxMsg);
#else
			snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
#endif
#if defined (KEISATSU)		/* 警察FAX DVT_ID 15 Added by SMuratec K.W.Q 2005/11/05 */
			if (func_number == 0) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_KEIDEN_RELAY_TEST;
				SF_R288F_RelayTest();	/* 警電　リレーテスト */
			}
			if (func_number == 1) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_KEIDEN_TONAL_TEST;
				SF_R288F_TonalTest();	/* 警電　トーナルテスト */
			}
			if (func_number == 2) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_KEIDEN_DTMF_TEST;
				SF_R288F_DTMF_Test();	/* 警電　ＤＴＭＦテスト */
			}
			if (func_number == 3) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_RELAY_TEST;
				SF_R288F_RelayTest();	/* リレーテスト */
			}
			if (func_number == 4) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_TONAL_TEST;
				SF_R288F_TonalTest();	/* トーナルテスト */
			}
			if (func_number == 5) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_DTMF_TEST;
				SF_R288F_DTMF_Test();	/* ＤＴＭＦテスト */
			}
#else
			if (func_number == 0) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_RELAY_TEST;
				SF_R288F_RelayTest();	/* リレーテスト */
			}
			if (func_number == 1) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_TONAL_TEST;
				SF_R288F_TonalTest();	/* トーナルテスト */
			}
			if (func_number == 2) {
				SYS_FactoryModem.Item = SYS_OPT_MDM_DTMF_TEST;
				SF_R288F_DTMF_Test();	/* ＤＴＭＦテスト */
			}
#endif		/* End of (defined (KEISATSU)) */
			SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_END;
			MDM_TxStopSwFlag = 0;	/* 1997/03/17 Y.Murata */
			if (tskno_MDM_FactoryTask != 0xFFFF) {
				del_tsk(&tskno_MDM_FactoryTask);
			}
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0 );
			return;
		case STOP:
		case KEY_TIME_UP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[リレーテスト（Ｒ２８８Ｆ用）]
	function	:[
		1.指定されたリレーのＯＮ／ＯＦＦを行う。
		2.キー入力とリレーの対応関係は以下のようになる。
		,	ONETOUCH_01_KEY -> CML
		,	ONETOUCH_02_KEY -> H
		,	ONETOUCH_03_KEY -> L
		,	ONETOUCH_04_KEY -> S
		,	ONETOUCH_05_KEY -> C24
		,	ONETOUCH_06_KEY -> TONE
		,	ONETOUCH_07_KEY -> BZ
		,	ONETOUCH_08_KEY -> RI
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void SF_R288F_RelayTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	kind;
	UBYTE	FunctionFlag;	/* リレーがセットされているか否かをビットで示す */

	kind = 0xFF;
	FunctionFlag = 0;

	/* 表示 */
#if defined (KEISATSU)		/* 警察FAX DVT_ID15 Modify by SMuratec K.W.Q 2005/11/05 */
	if (SYS_FactoryModem.Item == SYS_OPT_MDM_RELAY_TEST) {
		DisplayStringHigh(0, D2W_SF_R288F_RelayTest1);
	}
	else if (SYS_FactoryModem.Item == SYS_OPT_MDM_KEIDEN_RELAY_TEST) {
		DisplayStringHigh(0, D2W_SF_R288F_Keiden_RelayTest1);
	}
#else
	DisplayStringHigh(0, D2W_SF_R288F_RelayTest1);	/* [ CML  H     L   S   ] */
#endif		/* End of (defined (KEISATSU)) */
	DisplayStringLow(0, D2W_SF_R288F_RelayTest2);	/* [ C24  TONE  BZ  RI  ] */

	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case ONETOUCH:
			/* 指定されたリレーのＯＮ／ＯＦＦを行う */
			switch (key) {
			case ONETOUCH_01_KEY:	/* CML */
				if (FunctionFlag & 0x01) {
					kind = MDM_RELAY_CML_OFF;
					DisplayChar(0, ' ');
					FunctionFlag &= ~0x01;
				}
				else {
					kind = MDM_RELAY_CML_ON;
					DisplayChar(0, '*');
					FunctionFlag |= 0x01;
				}
				break;
			case ONETOUCH_02_KEY:	/*  H  */
				if (FunctionFlag & 0x02) {
					kind = MDM_RELAY_H_OFF;
					DisplayChar(5, ' ');
					FunctionFlag &= ~0x02;
				}
				else {
					kind = MDM_RELAY_H_ON;
					DisplayChar(5, '*');
					FunctionFlag |= 0x02;
				}
				break;
			case ONETOUCH_03_KEY:	/*  L  */
#if defined (JPN)
				if (FunctionFlag & 0x04) {
					kind = MDM_RELAY_L_OFF;
					DisplayChar(11, ' ');
					FunctionFlag &= ~0x04;
				}
				else {
					kind = MDM_RELAY_L_ON;
					DisplayChar(11, '*');
					FunctionFlag |= 0x04;
				}
				break;
#else	/* ＴＷＮにはＤＰリレー by H.Hirao 1999/02/02 */
				if (FunctionFlag & 0x04) {
					kind = MDM_RELAY_DP_OFF;
					DisplayChar(11, ' ');
					FunctionFlag &= ~0x04;
				}
				else {
					kind = MDM_RELAY_DP_ON;
					DisplayChar(11, '*');
					FunctionFlag |= 0x04;
				}
				break;
#endif
			case ONETOUCH_04_KEY:	/*  S  */
				if (FunctionFlag & 0x08) {
					kind = MDM_RELAY_S_OFF;
					DisplayChar(15, ' ');
					FunctionFlag &= ~0x08;
				}
				else {
					kind = MDM_RELAY_S_ON;
					DisplayChar(15, '*');
					FunctionFlag |= 0x08;
				}
				break;
			case ONETOUCH_05_KEY:	/* C24 */
				if (FunctionFlag & 0x10) {
					kind = MDM_RELAY_CONT24_OFF;
					DisplayChar(20, ' ');
					FunctionFlag &= ~0x10;
				}
				else {
					kind = MDM_RELAY_CONT24_ON;
					DisplayChar(20, '*');
					FunctionFlag |= 0x10;
				}
				break;
			case ONETOUCH_06_KEY:	/* TONE */
#if defined (JPN)	/* by H.Hirao 1999/02/02 */
				if (FunctionFlag & 0x20) {
					kind = MDM_RELAY_TONE_OFF;
					DisplayChar(25, ' ');
					FunctionFlag &= ~0x20;
				}
				else {
					kind = MDM_RELAY_TONE_ON;
					DisplayChar(25, '*');
					FunctionFlag |= 0x20;
				}
				break;
#endif
			case ONETOUCH_07_KEY:	/* BZ */
				if (FunctionFlag & 0x40) {
					kind = MDM_RELAY_BZ_OFF;
					DisplayChar(31, ' ');
					FunctionFlag &= ~0x40;
				}
				else {
					kind = MDM_RELAY_BZ_ON;
					DisplayChar(31, '*');
					FunctionFlag |= 0x40;
				}
				break;
			case ONETOUCH_08_KEY:	/* RI */
#if defined (JPN)	/* by H.Hirao 1999/02/02 */
				if (FunctionFlag & 0x80) {
					kind = MDM_RELAY_RI_OFF;
					DisplayChar(35, ' ');
					FunctionFlag &= ~0x80;
				}
				else {
					kind = MDM_RELAY_RI_ON;
					DisplayChar(35, '*');
					FunctionFlag |= 0x80;
				}
				break;
#endif
			default:
				NackBuzzer();
				break;
			}
			SYS_FactoryModem.Kind = kind;
			LineFuncTxMsg.Item = FROM_OPERATION;
			LineFuncTxMsg.Message = FIP_TEST_CMD;
#if (0)
** 			/* メールボックス変更 By O.Kimoto 1998/05/22 */
** 			snd_msg(mbxno.MDM_Task,&LineFuncTxMsg);
#else
			snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
#endif
			do {
				rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
			} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
			break;
		case STOP:
			SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_END;
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}

#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* SATSUKI2仕様 by Y.Kano 2003/10/20 */
/*************************************************************************
	module		:[トーナルテスト（Ｒ２８８Ｆ用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2003/10/20]
	author		:[加納義彦]
*************************************************************************/
void SF_R288F_TonalTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;
	UBYTE	tx_signal;
	UWORD	freq;

	tx_signal = 0;
	freq = (UWORD)OPT_MDM_TONAL_STOP;

	SYB_ModeSw = SYS_NORMAL;

	while (1) {
		Display_R288F_TonalTest(tx_signal, (UBYTE)freq );
		is_check_enable = TRUE;
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			if (key == TEN_0_KEY) {
				freq = (UWORD)(OPT_MDM_TONAL_FSK_W1_B1);
				tx_signal = 2;
				break;
			}
			freq = (UWORD)(OPT_MDM_TONAL_NONE + (UWORD)(key - TEN_1_KEY));
			tx_signal = 1;
			break;
		case AST:
			freq = (UWORD)OPT_MDM_TONAL_FSK_WHITE;
			tx_signal = 2;
			break;
		case SHARP:
			freq = (UWORD)OPT_MDM_TONAL_FSK_BLACK;
			tx_signal = 2;
			break;
		case ONETOUCH:
		case PROGRAM:
			/** 濃度選択を使って、３面分の種類をあらわす */
			switch (SYB_ModeSw) {	
			case SYS_NORMAL:			/** 普通 */
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_20_KEY)) {
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY));
					if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_08_KEY)) {
						freq = R288F_PixPattern(freq);	/* ストップ押されたときこの処理からぬける */
						tx_signal = 0;
					}
					else {
						tx_signal = 3;
					}
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			case SYS_FINE:				/** 高画質 */
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_20_KEY)) {
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY + 20));
					tx_signal = 3;
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			case SYS_SFINE:				/** 超高画質 */
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_20_KEY)) {
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY + 40));
					tx_signal = 3;
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			case SYS_GRAY16:	/** １６階調					*/
			case SYS_GRAY16_SEP:/** １６階調：像域分離			*/
			case SYS_GRAY64:	/** ６４階調					*/
			case SYS_GRAY64_SEP:/** ６４階調：像域分離			*/
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_04_KEY)) {
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY + 60));
						tx_signal = 3;
					if (key == ONETOUCH_04_KEY) {
						tx_signal = 4;	/* Voice */
					}
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			default:
				is_check_enable = FALSE;
				NackBuzzer();
				break;
			}
			break;
		case STOP:
			if (freq != (UWORD)OPT_MDM_TONAL_STOP) { /* トーン送出中 */
				freq = (UWORD)OPT_MDM_TONAL_STOP;
				tx_signal = 0;
				break;
			}
			else {
				SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_END;
				return;
			}
			break;
		case CLEAR:	/* 画質キー */
			if (key == CLEAR_KEY) {
				key = MODE_KEY;
				SingleKeyOperation(key);
			}
			else {
				NackBuzzer();
			}
			break;
		case NO_EFFECT:
			is_check_enable = FALSE;
			break;
		default:
			is_check_enable = FALSE;
			NackBuzzer();
			break;
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			SYS_FactoryModem.Kind = freq;
			LineFuncTxMsg.Item = FROM_OPERATION;
			LineFuncTxMsg.Message = FIP_TEST_CMD;
			snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
			do {
				rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
			} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
		}
	}
}

#else	/* SATSUKI2以外 */
/*************************************************************************
	module		:[トーナルテスト（Ｒ２８８Ｆ用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void SF_R288F_TonalTest(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;
	UBYTE	tx_signal;
	UWORD	freq;

	tx_signal = 0;
	freq = (UWORD)OPT_MDM_TONAL_STOP;

	while (1) {
		Display_R288F_TonalTest(tx_signal, (UBYTE)freq );
		is_check_enable = TRUE;
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
			if (key == TEN_0_KEY) {
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))
				/* FSK_W1_B1 1999/12/27 Y.Murata *//* HINOKI2追加 by J.Kishida 2002/10/03 */
				freq = (UWORD)(OPT_MDM_TONAL_FSK_W1_B1);
				tx_signal = 2;
#else
				is_check_enable = FALSE;
				NackBuzzer();
#endif
				break;
			}
			freq = (UWORD)(OPT_MDM_TONAL_NONE + (UWORD)(key - TEN_1_KEY));
			tx_signal = 1;
			break;
		case AST:
			freq = (UWORD)OPT_MDM_TONAL_FSK_WHITE;
			tx_signal = 2;
			break;
		case SHARP:
			freq = (UWORD)OPT_MDM_TONAL_FSK_BLACK;
			tx_signal = 2;
			break;
		case ONETOUCH:
		case PROGRAM:
#if defined(HINOKI3)	/* ONETOUCH_30_KEYがプレフィックスキーに変わったので by K.Watanabe 2004/10/26 */
		case MERCURY:
			if (key == MERCURY_KEY) {
				key = ONETOUCH_30_KEY;
			}
#endif
#if defined(POPLAR_F)
			if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_63_KEY)) {
				freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY));
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_08_KEY)) {
					freq = R288F_PixPattern(freq);	/* ストップ押されたときこの処理からぬける */
					tx_signal = 0;
				}
				else {
					tx_signal = 3;
				}
			}
			else {
				if (key == ONETOUCH_64_KEY) {
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY));
					tx_signal = 4;	/* Voice */
				}
				else if (key == ONETOUCH_65_KEY) {
					freq = (UWORD)OPT_MDM_TONAL_VOICE2;
					tx_signal = 5;	/* Melody */
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
			}
#else
			/** 濃度選択を使って、３面分の種類をあらわす */
			switch (SYB_DensitySw) {	
			case SYS_LIGHT_DENSITY:			/** 薄く */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/16 */
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_20_KEY)) {
#else
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_30_KEY)) {
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY));
					if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_08_KEY)) {
						freq = R288F_PixPattern(freq);	/* ストップ押されたときこの処理からぬける */
						tx_signal = 0;
					}
					else {
						tx_signal = 3;
					}
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			case SYS_NORMAL_DENSITY:		/** 普通 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Added by SMuratec L.Z.W 2003/09/16 */
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_20_KEY)) {
#else
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_30_KEY)) {
#endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY + 30));
					tx_signal = 3;
				}
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			case SYS_DARK_DENSITY:			/** 濃く */
 #if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* HINOKI2 NTT仕様に対応(POPLAR_Fはこっちに来ない) by J.Kishida 2002/10/09 */
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_05_KEY)) {
 #else
				if ((ONETOUCH_01_KEY <= key) && (key <= ONETOUCH_04_KEY)) {
 #endif
					freq = (UWORD)(OPT_MDM_TONAL_V27_1200_2400 + (UWORD)(key - ONETOUCH_01_KEY + 60));
					if (key == ONETOUCH_04_KEY) {

#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) 
/* ＨＩＮＯＫＩのＴＷＮ仕様は、保留メロディーが有りません。
** よって、回線テストからも保留メロディー送出は削除します。
** by O.Kimoto 1999/02/02
*/
 #if defined(JPN)
						tx_signal = 4;	/* Voice */
 #else
						is_check_enable = FALSE;
						NackBuzzer();
 #endif
#else
						tx_signal = 4;	/* Voice */
#endif

					}
 #if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* HINOKI2 NTT仕様に対応(POPLAR_Fはこっちに来ない) by J.Kishida 2002/10/09 */
					/* OPT_MDM_TONAL_VOICE2のテストを入れます */
					else if (key == ONETOUCH_05_KEY) {
						tx_signal = 5;	/* Melody */
					}
 #endif
					else {
						tx_signal = 3;
					}
 #if (PRO_VOICE_ANSWER == ENABLE) && (PRO_MODEM == R288F)	/* HINOKI2 NTT仕様に対応(POPLAR_Fはこっちに来ない) by J.Kishida 2002/10/09 */
				}	/* 右括弧と左括弧を対応させるため */
 #else
				}
 #endif
				else {
					is_check_enable = FALSE;
					NackBuzzer();
				}
				break;
			default:
				is_check_enable = FALSE;
				NackBuzzer();
				break;
			}
#endif	/* defined(POPLAR_F) */
			break;
		case STOP:
			if (freq != (UWORD)OPT_MDM_TONAL_STOP) { /* トーン送出中 */
				freq = (UWORD)OPT_MDM_TONAL_STOP;
				tx_signal = 0;
				break;
			}
			else {
				SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_END;
				return;
			}
			break;
#if defined(POPLAR_F)
		case SINGLE:	/* 濃度キー */
			if (key == CONTRAST_KEY) {
				SingleKeyOperation(key);
			}
			else {
				NackBuzzer();
			}
			break;
#endif
		case NO_EFFECT:
			is_check_enable = FALSE;
			break;
		default:
			is_check_enable = FALSE;
			NackBuzzer();
			break;
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			SYS_FactoryModem.Kind = freq;
			LineFuncTxMsg.Item = FROM_OPERATION;
			LineFuncTxMsg.Message = FIP_TEST_CMD;
#if (0)
//			/* メールボックス変更 By O.Kimoto 1998/05/22 */
//			snd_msg(mbxno.MDM_Task,&LineFuncTxMsg);
#else
			snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
#endif
			do {
				rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
			} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
		}
	}
}
#endif	/* End of (PRO_KEYPANEL == PANEL_SATSUKI2) || (PRO_KEYPANEL == PANEL_STOCKHM2) */

/*************************************************************************
	module		:[回線テスト・ＰＩＸ送出パターン選択（Ｒ２８８Ｆ用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
UWORD R288F_PixPattern(UWORD Freq)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;

	/* 表示  */
	CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferLow[0] = 'W';
	FunctionDisplayBufferLow[1] = ':';
	FunctionDisplayBufferLow[2] = 'B';
	FunctionDisplayBufferLow[3] = '?';
	DisplayStringLow(0, FunctionDisplayBufferLow);

	while (1) {
		Display_R288F_TonalTest( 3, (UBYTE)Freq );
		is_check_enable = TRUE;

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		if (TEN_1_KEY <= key && key <= TEN_5_KEY) {
			SYS_FactoryModem.PIX_Pattern = (UWORD)(OPT_MDM_PIX_W1_B0 + (UWORD)(key - TEN_1_KEY));
			SYS_FactoryModem.Kind = Freq;
		}
		else if (key == STOP_KEY) {
			if (SYS_FactoryModem.Kind != OPT_MDM_TONAL_STOP) {
				SYS_FactoryModem.Kind = OPT_MDM_TONAL_STOP;
			}
			/*
			 * ストップ２回押すとこの処理からぬける
			*/
			else {
				ClearDisplayLow();
				return(OPT_MDM_TONAL_STOP);
			}
		}
		else {
			is_check_enable = FALSE;
			NackBuzzer();
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			LineFuncTxMsg.Item = FROM_OPERATION;
			LineFuncTxMsg.Message = FIP_TEST_CMD;
#if (0)
//			/* メールボックス変更 By O.Kimoto 1998/05/22 */
//			snd_msg(mbxno.MDM_Task,&LineFuncTxMsg);
#else
			snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
#endif
			do {
				rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
			} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
		}
	}
}

/*************************************************************************
	module		:[トーナル信号表示（Ｒ２８８Ｆ用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void Display_R288F_TonalTest(UBYTE tx_signal, UBYTE freq )
{
	UWORD	data;
/* FSK_W1_B1 1999/12/27 Y.Murata *//* HINOKI2追加 by J.Kishida 2002/10/03 */
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))
	UBYTE	disp_buf[7];
#endif

	data = 0;

/* FSK_W1_B1 1999/12/27 Y.Murata *//* HINOKI2追加 by J.Kishida 2002/10/03 */
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))
	CMN_MemorySet(disp_buf, 7, NULL);
#endif

	/* 上段表示 */
	switch (tx_signal) {

	/*-------------*/
	/* 無信号状態　*/
	/*-------------*/
	case 0:	/* 無信号 */
		ClearDisplayHigh(); /* 空白 */
		break;

	/*--------------------*/
	/* トーナル信号送出中 */
	/*--------------------*/
	case 1:	/* トーン */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		switch (freq) {
		case OPT_MDM_TONAL_462HZ:
			data = 462;
			break;
		case OPT_MDM_TONAL_1080HZ:
#if defined (KEISATSU) /* 警察FAX 05/11/18 石橋正和 */
			data = 1100;
#else
			data = 1080;
#endif
			break;
		case OPT_MDM_TONAL_1300HZ:
			data = 1300;
			break;
		case OPT_MDM_TONAL_1650HZ:
			data = 1650;
			break;
		case OPT_MDM_TONAL_1700HZ:
			data = 1700;
			break;
		case OPT_MDM_TONAL_1800HZ:
			data = 1800;
			break;
		case OPT_MDM_TONAL_1850HZ:
			data = 1850;
			break;
		case OPT_MDM_TONAL_2100HZ:
			data = 2100;
			break;
		}
		CMN_UnsignedIntToASC(FunctionDisplayBufferHigh, data, 4, ' ');
		FunctionDisplayBufferHigh[4] = 'H';
		FunctionDisplayBufferHigh[5] = 'z';
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		break;

	/*----------------------*/
	/* ＦＳＫ信号送出中		*/
	/*----------------------*/
	case 2:	/* FSK	  */
		ClearDisplayHigh();
		DisplayStringHigh(0 , D2W_SF_FSK);
		if (freq == OPT_MDM_TONAL_FSK_WHITE) {
			DisplayStringHigh(4 , D2W_SF_White);
		}
		if (freq == OPT_MDM_TONAL_FSK_BLACK) {
			DisplayStringHigh(4 , D2W_SF_Black);
		}
/* FSK_W1_B1 1999/12/27 Y.Murata *//* HINOKI2追加 by J.Kishida 2002/10/03 */
#if defined(POPLAR_F) || (defined(HINOKI2) && defined(JPNNTT))
		if (freq == OPT_MDM_TONAL_FSK_W1_B1) {
			disp_buf[0] = 'W';
			disp_buf[1] = '1';
			disp_buf[2] = ':';
			disp_buf[3] = 'B';
			disp_buf[4] = '1';
			disp_buf[5] = NULL;
			DisplayStringHigh(4 , disp_buf);
		}
#endif
		break;

	/*---------------------*/
	/* 画信号送出中		   */
	/*---------------------*/
	case 3:	/* PIX	  */
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		switch (freq) {
		case OPT_MDM_TONAL_V27_1200_2400:
			data = 1200;
			break;
		case OPT_MDM_TONAL_V27_1600_4800:
			data = 1600;
			break;
		case OPT_MDM_TONAL_V34_2400_12000:
		case OPT_MDM_TONAL_V17_2400_12000:
		case OPT_MDM_TONAL_V34_2400_14400:
		case OPT_MDM_TONAL_V17_2400_14400:
		case OPT_MDM_TONAL_V34_2400_16800:
		case OPT_MDM_TONAL_V34_2400_19200:
		case OPT_MDM_TONAL_V34_2400_21600:
		case OPT_MDM_TONAL_V34_2400_2400:
		case OPT_MDM_TONAL_V34_2400_4800:
		case OPT_MDM_TONAL_V34_2400_7200:
		case OPT_MDM_TONAL_V17_2400_7200:
		case OPT_MDM_TONAL_V29_2400_7200:
		case OPT_MDM_TONAL_V34_2400_9600:
		case OPT_MDM_TONAL_V29_2400_9600:
		case OPT_MDM_TONAL_V17_2400_9600:
			data = 2400;
			break;
		case OPT_MDM_TONAL_V34_2800_12000:
		case OPT_MDM_TONAL_V34_2800_14400:
		case OPT_MDM_TONAL_V34_2800_16800:
		case OPT_MDM_TONAL_V34_2800_19200:
		case OPT_MDM_TONAL_V34_2800_21600:
		case OPT_MDM_TONAL_V34_2800_24000:
		case OPT_MDM_TONAL_V34_2800_26400:
		case OPT_MDM_TONAL_V34_2800_4800:
		case OPT_MDM_TONAL_V34_2800_7200:
		case OPT_MDM_TONAL_V34_2800_9600:
			data = 2800;
			break;
		case OPT_MDM_TONAL_V34_3000_12000:
		case OPT_MDM_TONAL_V34_3000_14400:
		case OPT_MDM_TONAL_V34_3000_16800:
		case OPT_MDM_TONAL_V34_3000_19200:
		case OPT_MDM_TONAL_V34_3000_21600:
		case OPT_MDM_TONAL_V34_3000_24000:
		case OPT_MDM_TONAL_V34_3000_26400:
		case OPT_MDM_TONAL_V34_3000_28800:
		case OPT_MDM_TONAL_V34_3000_4800:
		case OPT_MDM_TONAL_V34_3000_7200:
		case OPT_MDM_TONAL_V34_3000_9600:
			data = 3000;
			break;
		case OPT_MDM_TONAL_V34_3200_12000:
		case OPT_MDM_TONAL_V34_3200_14400:
		case OPT_MDM_TONAL_V34_3200_16800:
		case OPT_MDM_TONAL_V34_3200_19200:
		case OPT_MDM_TONAL_V34_3200_21600:
		case OPT_MDM_TONAL_V34_3200_24000:
		case OPT_MDM_TONAL_V34_3200_26400:
		case OPT_MDM_TONAL_V34_3200_28800:
		case OPT_MDM_TONAL_V34_3200_31200:
		case OPT_MDM_TONAL_V34_3200_4800:
		case OPT_MDM_TONAL_V34_3200_7200:
		case OPT_MDM_TONAL_V34_3200_9600:
			data = 3200;
			break;
		case OPT_MDM_TONAL_V34_3429_12000:
		case OPT_MDM_TONAL_V34_3429_14400:
		case OPT_MDM_TONAL_V34_3429_16800:
		case OPT_MDM_TONAL_V34_3429_19200:
		case OPT_MDM_TONAL_V34_3429_21600:
		case OPT_MDM_TONAL_V34_3429_24000:
		case OPT_MDM_TONAL_V34_3429_26400:
		case OPT_MDM_TONAL_V34_3429_28800:
		case OPT_MDM_TONAL_V34_3429_31200:
		case OPT_MDM_TONAL_V34_3429_33600:
		case OPT_MDM_TONAL_V34_3429_4800:
		case OPT_MDM_TONAL_V34_3429_7200:
		case OPT_MDM_TONAL_V34_3429_9600:
			data = 3429;
			break;
		}
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[0], data, 4, ' ');
		FunctionDisplayBufferHigh[4] = '/';

		switch (freq) {
		case OPT_MDM_TONAL_V27_1200_2400:
		case OPT_MDM_TONAL_V34_2400_2400:
			data = 2400;
			break;
		case OPT_MDM_TONAL_V27_1600_4800:
		case OPT_MDM_TONAL_V34_2400_4800:
		case OPT_MDM_TONAL_V34_2800_4800:
		case OPT_MDM_TONAL_V34_3000_4800:
		case OPT_MDM_TONAL_V34_3200_4800:
		case OPT_MDM_TONAL_V34_3429_4800:
			data = 4800;
			break;
		case OPT_MDM_TONAL_V29_2400_7200:
		case OPT_MDM_TONAL_V17_2400_7200:
		case OPT_MDM_TONAL_V34_2400_7200:
		case OPT_MDM_TONAL_V34_2800_7200:
		case OPT_MDM_TONAL_V34_3000_7200:
		case OPT_MDM_TONAL_V34_3200_7200:
		case OPT_MDM_TONAL_V34_3429_7200:
			data = 7200;
			break;
		case OPT_MDM_TONAL_V29_2400_9600:
		case OPT_MDM_TONAL_V17_2400_9600:
		case OPT_MDM_TONAL_V34_2400_9600:
		case OPT_MDM_TONAL_V34_2800_9600:
		case OPT_MDM_TONAL_V34_3000_9600:
		case OPT_MDM_TONAL_V34_3200_9600:
		case OPT_MDM_TONAL_V34_3429_9600:
			data = 9600;
			break;
		case OPT_MDM_TONAL_V17_2400_12000:
		case OPT_MDM_TONAL_V34_2400_12000:
		case OPT_MDM_TONAL_V34_2800_12000:
		case OPT_MDM_TONAL_V34_3000_12000:
		case OPT_MDM_TONAL_V34_3200_12000:
		case OPT_MDM_TONAL_V34_3429_12000:
			data = 12000;
			break;
		case OPT_MDM_TONAL_V17_2400_14400:
		case OPT_MDM_TONAL_V34_2400_14400:
		case OPT_MDM_TONAL_V34_2800_14400:
		case OPT_MDM_TONAL_V34_3000_14400:
		case OPT_MDM_TONAL_V34_3200_14400:
		case OPT_MDM_TONAL_V34_3429_14400:
			data = 14400;
			break;
		case OPT_MDM_TONAL_V34_2400_16800:
		case OPT_MDM_TONAL_V34_2800_16800:
		case OPT_MDM_TONAL_V34_3000_16800:
		case OPT_MDM_TONAL_V34_3200_16800:
		case OPT_MDM_TONAL_V34_3429_16800:
			data = 16800;
			break;
		case OPT_MDM_TONAL_V34_2400_19200:
		case OPT_MDM_TONAL_V34_2800_19200:
		case OPT_MDM_TONAL_V34_3000_19200:
		case OPT_MDM_TONAL_V34_3200_19200:
		case OPT_MDM_TONAL_V34_3429_19200:
			data = 19200;
			break;
		case OPT_MDM_TONAL_V34_2400_21600:
		case OPT_MDM_TONAL_V34_2800_21600:
		case OPT_MDM_TONAL_V34_3000_21600:
		case OPT_MDM_TONAL_V34_3200_21600:
		case OPT_MDM_TONAL_V34_3429_21600:
			data = 21600;
			break;
		case OPT_MDM_TONAL_V34_2800_24000:
		case OPT_MDM_TONAL_V34_3000_24000:
		case OPT_MDM_TONAL_V34_3200_24000:
		case OPT_MDM_TONAL_V34_3429_24000:
			data = 24000;
			break;
		case OPT_MDM_TONAL_V34_2800_26400:
		case OPT_MDM_TONAL_V34_3000_26400:
		case OPT_MDM_TONAL_V34_3200_26400:
		case OPT_MDM_TONAL_V34_3429_26400:
			data = 26400;
			break;
        case OPT_MDM_TONAL_V34_3000_28800:
		case OPT_MDM_TONAL_V34_3200_28800:
		case OPT_MDM_TONAL_V34_3429_28800:
			data = 28800;
			break;
		case OPT_MDM_TONAL_V34_3200_31200:
		case OPT_MDM_TONAL_V34_3429_31200:
			data = 31200;
			break;
		case OPT_MDM_TONAL_V34_3429_33600:
			data = 33600;
			break;
		}
		CMN_UnsignedIntToASC(&FunctionDisplayBufferHigh[5], data, 5, ' ');

		if (freq >= OPT_MDM_TONAL_V27_1200_2400 && freq <= OPT_MDM_TONAL_V17_2400_14400) {
			FunctionDisplayBufferHigh[11] = 'W';
			FunctionDisplayBufferHigh[12] = ':';
			FunctionDisplayBufferHigh[13] = 'B';
			FunctionDisplayBufferHigh[15] = '=';
			FunctionDisplayBufferHigh[17] = '1';
			FunctionDisplayBufferHigh[18] = ':';
			FunctionDisplayBufferHigh[19] = '1';

			switch (SYS_FactoryModem.PIX_Pattern) {
			case OPT_MDM_PIX_W1_B0: /* [1:0] */
				FunctionDisplayBufferHigh[19] = '0';
				break;
			case OPT_MDM_PIX_W1_B1: /* [1:1] */
				break;
			case OPT_MDM_PIX_W1_B4: /* [1:4] */
				FunctionDisplayBufferHigh[19] = '4';
				break;
			case OPT_MDM_PIX_W0_B1: /* [0:1] */
				FunctionDisplayBufferHigh[17] = '0';
				break;
			case OPT_MDM_PIX_W4_B1: /* [4:1] */
				FunctionDisplayBufferHigh[17] = '4';
				break;
			}
		}
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		break;
	/*-------*/
	/* Voice */
	/*-------*/
	case 4:
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferHigh[0] = 'V';
		FunctionDisplayBufferHigh[1] = 'o';
		FunctionDisplayBufferHigh[2] = 'i';
		FunctionDisplayBufferHigh[3] = 'c';
		FunctionDisplayBufferHigh[4] = 'e';
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		break;
	/*--------*/
	/* Melody */
	/*--------*/
	case 5:
		CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
		FunctionDisplayBufferHigh[0] = 'M';
		FunctionDisplayBufferHigh[1] = 'e';
		FunctionDisplayBufferHigh[2] = 'l';
		FunctionDisplayBufferHigh[3] = 'o';
		FunctionDisplayBufferHigh[4] = 'd';
		FunctionDisplayBufferHigh[5] = 'y';
		DisplayStringHigh(0, FunctionDisplayBufferHigh);
		break;
	}

	/* 下段クリア */
/*	ClearDisplayLow();*/

}

/*************************************************************************
	module		:[ＤＴＭＦテスト（Ｒ２８８Ｆ用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void SF_R288F_DTMF_Test(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_check_enable;
	UWORD	dtmf;

	dtmf = (UWORD)OPT_MDM_DTMF_STOP;

	while (1) {
		is_check_enable = TRUE;

		/* 表示 */
		Display_R288F_TxDTMF((UBYTE) dtmf);

		/* キー取り込み */
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case NUMBER:
		case AST:
		case SHARP:
		case ONETOUCH:
			if (TEN_0_KEY <= key && key <= TEN_9_KEY) {
				dtmf = (UWORD)(key - 0x30);
			}
			else if (key == TEN_SHARP_KEY) {
				dtmf = (UWORD)OPT_MDM_DTMF_SHARP;
			}
			else if (key == TEN_AST_KEY) {
				dtmf = (UWORD)OPT_MDM_DTMF_AST;
			}
			else if (ONETOUCH_01_KEY <= key && key <= ONETOUCH_08_KEY) {
				dtmf = (UWORD)(OPT_MDM_DTMF_ROW1 + (UWORD)(key - ONETOUCH_01_KEY));
			}
			else {
				is_check_enable = FALSE;
				NackBuzzer();
			}
			break;
		case STOP:
			if (dtmf != (UWORD)OPT_MDM_DTMF_STOP) {	/* ＤＴＭＦ送出中 */
				dtmf = (UWORD)OPT_MDM_DTMF_STOP;
				break;
			}
			else {
				SYS_FactoryModem.Item = OPT_MDM_FACTORY_TEST_END;
				return;
			}
			break;
		case NO_EFFECT:
			is_check_enable = FALSE;
			break;
		default:
			is_check_enable = FALSE;
			NackBuzzer();
			break;
		}

		if (is_check_enable) {	/* 正当なキーが押された時のみ下の処理有効 */
			SYS_FactoryModem.Kind = dtmf;
			LineFuncTxMsg.Item = FROM_OPERATION;
			LineFuncTxMsg.Message = FIP_TEST_CMD;
#if (0)
** 			/* メールボックス変更 By O.Kimoto 1998/05/22 */
** 			snd_msg(mbxno.MDM_Task,&LineFuncTxMsg);
#else
			snd_msg(mbxno.CPY_Task,&LineFuncTxMsg);
#endif
			do {
				rcv_msg(mbxno.OPR_Task,&LineFuncRxMsg);
			} while(LineFuncRxMsg->Message != MSG_FIP_RS232C_TEST_END);
		}
	}
}

/*************************************************************************
	module		:[ＤＴＭＦテスト中の表示（Ｒ２８８Ｆ用）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void Display_R288F_TxDTMF(UBYTE dtmf)
{
	ClearDisplayHigh();
	ClearDisplayLow();

	if (dtmf == OPT_MDM_DTMF_STOP) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
	}
	if (OPT_MDM_DTMF_0 <= dtmf && dtmf <= OPT_MDM_DTMF_9) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , dtmf | 0x30);
	}
	if (dtmf == OPT_MDM_DTMF_SHARP) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , '#');
	}
	if (dtmf == OPT_MDM_DTMF_AST) {
		DisplayStringHigh(0 , D2W_SF_DTMF);
		DisplayChar(5 , '*');
	}

	if (OPT_MDM_DTMF_ROW1 <= dtmf && dtmf <= OPT_MDM_DTMF_ROW4) {
		DisplayStringHigh(0, D2W_SF_DTMFRow);
		DisplayChar(5, (UBYTE)((dtmf - OPT_MDM_DTMF_ROW1) + 1) | 0x30);
	}
	if (OPT_MDM_DTMF_COL1 <= dtmf && dtmf <= OPT_MDM_DTMF_COL4) {
		DisplayStringHigh(0, D2W_SF_DTMFColum);
		DisplayChar(5, (UBYTE)((dtmf - OPT_MDM_DTMF_COL1) + 1) | 0x30);
	}
}
#endif	/* (PRO_MODEM == R288F) */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* By H.Fujimura 1999/01/06 */
/*************************************************************************
	module		:[ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲのCARﾊﾟﾀｰﾝ検出ﾊﾟﾗﾒｰﾀの設定、閲覧]
	function	:[
		1.機能+＊＊+２９(SATSUKI2では 機能+＊＊+１９です)
	]
	return		:[]
	common		:[SoftSwCtrl]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[1999/01/06]
	author		:[藤村春夫]
*************************************************************************/
void OPR_NumberDisplayCarPatternMode(void)
{
	UBYTE	mode;

	/* データのセット */
	OPR_Buf.SoftSwCtrl.ItemWording  = D2W_ND_Parameter;				/* [ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾊﾟﾗﾒｰﾀ] */
	OPR_Buf.SoftSwCtrl.SetParameter = &SYB_ND_CarPattern[0];		/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ ﾊﾟﾗﾒｰﾀ */
	OPR_Buf.SoftSwCtrl.SwitchMax    = SYS_ND_CAR_PATTERN_MAX;		/* 最大３０個 */
	OPR_Buf.SoftSwCtrl.SelectSwitch = 0;							/* 初期値０（Ａ０）SATSUKI2では（００）*/

	/* 編集するかクリアするか選択させる */
	mode = SelectSetClearMode();

	if (mode == PARAMETER_SET) {		/* 編集の場合 */
		SetSoftSwitch();
	}
	else if (mode == PARAMETER_CLEAR) {	/* クリアの場合 */
		ClearSoftSwitch(UNIQ_SWITCH_MODE);
	}
	else {								/* 終了OPR_END */
		return;
	}
}
#endif
#if defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2)	/* for debug 2002/01/24 T.Takagi */
 #if (PRO_DIALIN == ENABLE)		/* 条件追加 2002/07/18 T.Takagi */
/*************************************************************************
	module		:[ダイヤルインDTMF検出レベルテスト]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[PARISにあったのをHINOKI2用にカスタマイズ]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2002/01/24]
	author		:[T.Takagi]
*************************************************************************/
void TestDialinDetectDTMF(void)
{
	UWORD key;
	UWORD keytype;
	UBYTE dtmf_value;
	UBYTE string[2];
	UBYTE x,y;
	UBYTE pre_det;
	UBYTE check_bit;
	UBYTE comp_bit;
	UBYTE debug;
	UBYTE bk_dtmf_value;
	UBYTE reg_value;

	debug = 0;
	reg_value = 0;
	
	ClearDisplayHigh();
	ClearDisplayLow();

	MDM_ConfigDTMF_ReceiverMode();
	DialIn1stAnswerRealyControl();

	x = y = 0;
	pre_det = 0;
	check_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS | IO_BIT_DTMFD);
	comp_bit = (IO_BIT_EDET | IO_BIT_DTDET | IO_BIT_OTS);
	dtmf_value = bk_dtmf_value = 0x0F;
	while (1) {
		if (!pre_det) {
			if (((reg_value = inp(MDM_REG_1B_PORT)) & comp_bit) == comp_bit) {
				pre_det = 1;
			}
		}
		if ((((reg_value = inp(MDM_REG_1B_PORT)) & check_bit) == IO_BIT_DTMFD) && pre_det) {
			dtmf_value = MDM_GetIO(POS_DTMFW);
			if (dtmf_value == bk_dtmf_value) {
				if (debug) {
					outp(0,0);
				}
			}
			bk_dtmf_value = dtmf_value;
			wai_tsk(1);
			MDM_SetIO(POS_DTMFD, 0);
			pre_det = 0;
			if ((x == 0) && (y == 0)) {
				ClearDisplayHigh();
				ClearDisplayLow();
			}
			if ((dtmf_value >= 0) && (dtmf_value <= 9)) {
				CMN_UnsignedIntToASC_NULL(string, (UWORD)dtmf_value, 1, 0);
			}
			else {
				if (dtmf_value == 0x0A) {
					string[0] = '*';
					string[1] = 0x00;
				}
				else {
					string[0] = '#';
					string[1] = 0x00;
				}
			}
			if (x < 20) {
				DisplayStringHigh(x, string);
				x++;
			}
			else {
				y = x-20;
				DisplayStringLow(y, string);
				x++;
			}
			if (x > 39) {
				x = 0;
				y = 0;
			}
		}
		else {
			OPR_GetKey(1);
			key = GetInputKeyCode();
			keytype = GetInputKeyType();
			switch (keytype) {
			case STOP:
				S_RelayOff();
  #if defined(HINOKI3)
  #else
				DspRamAccessWriteMethod3(0x0B3C, BackupReceiveLevel, 0x0000); /* 2000/12/12 by K.Okada */
  #endif
				InitializeRelay();
				return;
			case KEY_TIME_UP:
				break;
			default:
				NackBuzzer();
				break;
			}
		}
	}
}
 #endif
#endif

#if (PRO_ENERGY_SAVE == ENABLE)
/**********************************************************************************************************************
 * Module: PC24V リレー寿命テスト
 * Author: 高木 智史
 * Create: 2002/12/03
 * Function: 
 * Argument: 
 * Return: 
 * Global: 
 * Condition: 
 * Note: 
 *********************************************************************************************************************/
void	PC24V_TestMode(void)
{
	UWORD key;
	UWORD keytype;
	UBYTE now_on;
	UDWORD count;
	now_on = 0;
	count = 0;

	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;

	ClearDisplayHigh();
	ClearDisplayLow();

	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	FunctionDisplayBufferHigh[0] = 'P';
	FunctionDisplayBufferHigh[1] = 'C';
	FunctionDisplayBufferHigh[2] = ' ';
	FunctionDisplayBufferHigh[3] = 'R';
	FunctionDisplayBufferHigh[4] = 'e';
	FunctionDisplayBufferHigh[5] = 'l';
	FunctionDisplayBufferHigh[6] = 'a';
	FunctionDisplayBufferHigh[7] = 'y';
	FunctionDisplayBufferHigh[8] = ' ';
	FunctionDisplayBufferHigh[9] = 'T';
	FunctionDisplayBufferHigh[10] = 'e';
	FunctionDisplayBufferHigh[11] = 's';
	FunctionDisplayBufferHigh[12] = 't';
	DisplayStringHigh(0, FunctionDisplayBufferHigh);

	while (1) {
		OPR_GetKey(300);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		if (keytype == STOP || count >= 999999) {
			break;
		}

		if (now_on == 0) {
			PC_24V_On();
			now_on = 1;
			count++;
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
			CMN_UnsignedLongToASC(FunctionDisplayBufferLow, count, 6, '0');
			DisplayStringLow(0, FunctionDisplayBufferLow);
		}
		else {
			PC_24V_Off();
			now_on = 0;
			count++;
			CMN_MemorySetNULL(FunctionDisplayBufferLow, OPR_DISPLAY_MAX, ' ');
			CMN_UnsignedLongToASC(FunctionDisplayBufferLow, count, 6, '0');
			DisplayStringLow(0, FunctionDisplayBufferLow);
		}
	}

	while (1) {
		OPR_GetKey(KEY_WAIT_FOREVER);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		switch (keytype) {
		case STOP:			/* ストップキー */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_SCANNER_BUSY;
			return;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif

#if (PRO_REMOTE_DIAL_TRANSFER == ENABLE)	/* REMOTE_RX_FUNC 設定表示 */
/*************************************************************************
	module		:[リモートダイヤル転送設定表示 REMOTE_RX_FUNC]
	function	:[
		3秒間表示して戻る
	]
	return		:[]
	date		:[2003/02/05]
	author		:[]
*************************************************************************/
void	DisplayRemoteTransferSetting(void)
{
	UWORD	loop = TRUE;
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	dial_str[4];
	UBYTE	length;

	length = CMN_GetRemoteTransferDialString(dial_str);

	ClearDisplayHigh();
	ClearDisplayLow();

	if (length > 0) {
		DisplayStringHigh(0, (CONST UBYTE *)dial_str);
		DisplayStringHigh(length + 1, D2W_RemoteTxSetting);
	}
	else {
		length = CMN_StringLength(D2W_RemoteTxSettingOff);
		DisplayStringHigh(0, D2W_RemoteTxSettingOff);
		DisplayStringHigh(length + 1, D2W_RemoteTxSetting);
	}

	while (loop) {
		OPR_GetKey(KEY_WAIT_FEW_TIME);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		switch (keytype) {
		case CLEAR:
		case STOP:
		case KEY_TIME_UP:
			loop = FALSE;
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif


#if defined(STOCKHM2) || (defined(HINOKI2) && defined(JPNNTT)) || defined(HINOKI3)	/* O.Oshima 2004/11/04 */	/* Y.kano 2005/02/14 */
/*************************************************************************
	module		:[サムチェック]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[2001/02/20]
	author		:[]
*************************************************************************/
UWORD WordTypeCheckSum(UWORD *address, UDWORD word_size)
{
	UWORD sum;

	sum = 0;
	while (word_size--) {
		sum += *(address++);
	}

	return (sum);	/* Wordのサムチェックを返す */
}


/*************************************************************************
	module		:[サムチェック表示]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[]
	date		:[]
	author		:[]
*************************************************************************/
CONST UBYTE Sum_Msg1[]		= " ROM0:     ROM1:    ";
void DisplayCheckSum(void)
{
	UBYTE keycode;
	UBYTE keytype;
	UBYTE buffer[OPR_DISPLAY_MAX+1];
	UWORD sum[4];

	ClearDisplayHigh();
	ClearDisplayLow();

	DisplayStringHigh(0, (CONST UBYTE *)"CheckSum");
	
	sum[0] = WordTypeCheckSum((UWORD *)0x200000, (0x80000L/2));
	sum[1] = WordTypeCheckSum((UWORD *)0x280000, (0x80000L/2));
	
	CMN_StringCopyNULL(buffer, Sum_Msg1);		/* " ROM0:XXXX ROM1:XXXX" */
	CMN_HexToASC(&buffer[6], (UDWORD)sum[0], 4);
	CMN_HexToASC(&buffer[16], (UDWORD)sum[1], 4);
	DisplayStringHigh(0, (UBYTE *)buffer);

	while (1) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keytype = GetInputKeyType();
		keycode = GetInputKeyCode();
		switch (keytype) {
		case KEY_TIME_UP:
			NackBuzzer();
			break;
		case STOP:
			return;
			break;
		default:
			NackBuzzer();
			break;
		}
	}
}
#endif

#if (PRO_RTC_RX5C338A == ENABLE)
/*************************************************************************
	module		:[ＲＴＣの初期設定]
	function	:[
	]
	return		:[]
	date		:[2004/10/25]
	author		:[Y.Tanaka]
*************************************************************************/
void	SF_RTC_Initialize(void)
{
	UWORD	i;
	UBYTE	data[7];
	UBYTE	reg;
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	is_break = 0;
	UDWORD	value = 0;

	UBYTE	mask[8] = {
		0x80, 0x40, 0x20, 0x10,
		0x08, 0x04, 0x02, 0x01
	};

	for (i = 0; i < 7; i++){
		data[i] = 0;
	}

	DisplayStringHigh(0, D2W_RTC_Init);	/* RTCｼｮｷｶ */
	while (1) {
				/* キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();
		DisplayStringLow(0, data);

		switch (keytype) {
		case NUMBER:	/* 0 - 9 */
			for (i = 4; i >= 1; i--){
				data[i] = data[i - 1];
			}
			data[0] = key;
			break;
		case ENTER:
			/** 決定 */
			is_break = 1;
			break;
		case STOP:
		case KEY_TIME_UP:
			/** 終了 */
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
		if (is_break){
			break;
		}
	}

	for (i = 0; i < 7; i++){
		value *= 10;
		value += (UBYTE)(data[i] - TEN_0_KEY);
	}

	value = value - 3276805;
	if (value >= 3276805){
		value = value - 3276805;
		value /= 10;
		if (value > 128){
			return;
		}
	}
	else {
		value = 3276805 - value;
		value /= 10;
		if (value > 128){
			return;
		}
		value = 128 - value;
	}
	reg = (UBYTE)value;
	
	RTC_IO_Enable(RTC_RW_PERMIT);								/**  書き込み許可		*/
	WriteClockBit(reg, ADJUST_REGISTER);						/**  書き込み			*/
	RTC_IO_Enable(RTC_RW_FORBIT);								/**  書き込み禁止		*/

	return;
}
#endif

#if (PRO_DISASTER_PREVENTION_FAX == ENABLE)				/* 防災FAX対応 by Y.Kano 2005/03/04 	*/
/*************************************************************************
	module		:[防災ＦＡＸモード設定オペレーション]
	function	:[
	]
	return		:[]
	date		:[2005/03/04]
	author		:[Y.Kano]
*************************************************************************/
void	DisasterPreventionFaxOperation(void)
{
	UBYTE	key;
	UBYTE	keytype;

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_DisasterPreventionFax);

	/* 下段表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);				/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case ENTER:
			DisasterPreventionFaxSetting();	/* 防災ＦＡＸ設定 */
			return;
		case FUNCTION:		/* 機能キー */
		case LEFT_ARROW:	/* 左矢印  */
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}


/*************************************************************************
	module		:[防災ＦＡＸモード設定]
	function	:[
	]
	return		:[]
	date		:[2005/03/04]
	author		:[Y.Kano]
*************************************************************************/
void	DisasterPreventionFaxSetting(void)
{
	UBYTE	status;		/* 1:set  0:clear */
	UBYTE	key;
	UBYTE	keytype;

	if (CHK_DisasterPreventionFaxEnable()) {
		status = 1;
	}
	else {
		status = 0;
	}

	/* 下段表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);				/* "          ｾｯﾄ/ｽﾄｯﾌﾟ " */

	while(1) {

		/* 上段表示 */
		if (status) {
			DisplayStringHigh(0, D2W_DisasterPreventionFaxOn);	/* "ﾎﾞｳｻｲ         : ON  " */
		}
		else {
			DisplayStringHigh(0, D2W_DisasterPreventionFaxOff);	/* "ﾎﾞｳｻｲ         : OFF " */
		}

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー */
		case LEFT_ARROW:	/* 左矢印  */
			status ^= (UBYTE)0x01;
			break;
		case ENTER:
			/** 決定 */
			if (status) {	/* 編集 */
				DisasterPreventionSet();	/* 防災ＦＡＸ設定 */
			}
			else {
				DisasterPreventionClr();	/* 防災ＦＡＸ設定 */
			}
			/* 完了 */
			ChildDisplaySetCompleted(D2W_DisasterPreventionFax);
			return;
		case STOP:
		case KEY_TIME_UP:
			return;

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
}

/*************************************************************************
	module		:[防災ＦＡＸ関連スイッチ設定]
	function	:[
	]
	return		:[]
	date		:[2005/03/04]
	author		:[Y.Kano]
*************************************************************************/
void	DisasterPreventionSet(void)
{
	/* 防災ＦＡＸを有効にする。 */
	SYB_MachineUniqSwitch[UNIQ_SW_I9] |= DISASTER_PREVENTION_FAX_ENABLE;
	/* Ｇ３モードにする。 */
	SYB_MachineUniqSwitch[UNIQ_SW_D3] |= V34_V34SIGNAL_RATE_MASK;
	/* １フレーム受信終了後のタイムアウト時間（６秒）。 */
	SYB_MachineUniqSwitch[UNIQ_SW_B8] |= DISASTER_PREVENTION_FAX_TIME_OUT;
	/* トレーニング検出時間（１．５ｓ～３．０ｓ）*/
	SYB_MachineUniqSwitch[UNIQ_SW_A5]	 = DisasterPreventionTCF_Time;
	/* ＲＬＳＤ時のトレーニング検出時間（１．５ｓ～３．０ｓ）*/
	SYB_MachineUniqSwitch[UNIQ_SW_A6] 	= DisasterPreventionRLSD_TCF_Time;
	/* ＤＣＳ－ＴＣＦ送信間隔が、１００ｍｓ */
	SYB_MachineUniqSwitch[UNIQ_SW_C5] 	= DisasterPreventionDCS_TCF_TX_Time;
	/* ＴＣＦ受信からＣＦＲ送出までの待ち時間が、２００ｍｓ */
	SYB_MachineUniqSwitch[UNIQ_SW_C6] 	= DisasterPreventionTCF_RX_CFR_TX_WaitTime;
	/* ＤＩＳ受信終了から－ＤＣＳ送出開始までの時間が、９９０ｍｓ */
	SYS_MemorySwitch[MEMORY_SW_D7] 		= DisasterPreventionDIS_RX_DCS_TX_WaitTime;
	/* ＣＦＲ－ＰＩＸ間隔 ６５０ｍｓ */
	SYS_MemorySwitch[MEMORY_SW_B8]		= DisasterPreventionCFR_RX_PIX_TX_Time;
	/* ＥＣＭモードをＯＦＦ */
	SYB_SettingStatus[SETTING_STATUS_6] &= ~ECM_SETTING;
	/* 機器パラメータ０１をセットする。*/
	SYB_MachineParameter[MACHINE_PARA_1] |= DisasterPreventionMachineParaData;
}

/*************************************************************************
	module		:[防災ＦＡＸ関連スイッチ初期化]
	function	:[
	]
	return		:[]
	date		:[2005/03/04]
	author		:[Y.Kano]
*************************************************************************/
void	DisasterPreventionClr(void)
{
	/* 防災ＦＡＸを無効にする。 */
	SYB_MachineUniqSwitch[UNIQ_SW_I9] &= ~DISASTER_PREVENTION_FAX_ENABLE;
	/* Ｖ３４モードにする。 */
	SYB_MachineUniqSwitch[UNIQ_SW_D3] = UniqSwitchInitialTable[UNIQ_SW_D3];
	/* １フレーム受信終了後のタイムアウト時間のクリア。 */
	SYB_MachineUniqSwitch[UNIQ_SW_B8] = UniqSwitchInitialTable[UNIQ_SW_B8];
	/* トレーニング検出時間のクリア */
	SYB_MachineUniqSwitch[UNIQ_SW_A5] 	= UniqSwitchInitialTable[UNIQ_SW_A5];
	/* ＲＬＳＤ時のトレーニング検出時間のクリア */
	SYB_MachineUniqSwitch[UNIQ_SW_A6] 	= UniqSwitchInitialTable[UNIQ_SW_A6];
	/* ＤＣＳ－ＴＣＦ送信間隔のクリア */
	SYB_MachineUniqSwitch[UNIQ_SW_C5] 	= UniqSwitchInitialTable[UNIQ_SW_C5];
	/* ＴＣＦ受信からＣＦＲ送出までの待ち時間は、メモリＳＷ（Ｃ１）で見る。 */
	SYB_MachineUniqSwitch[UNIQ_SW_C6] 	= UniqSwitchInitialTable[UNIQ_SW_C6];
	/* ＤＩＳ受信終了から－ＤＣＳ送出開始までの時間は、メモリＳＷ（Ｂ２）で見る。 */
	SYS_MemorySwitch[MEMORY_SW_D7]    	= MemorySwitchInitialTable[MEMORY_SW_D7];
	/* ＣＦＲ－ＰＩＸ間隔は、メモリＳＷ（Ｂ１）で見る。 */
	SYS_MemorySwitch[MEMORY_SW_B8]		= MemorySwitchInitialTable[MEMORY_SW_B8];
	/* 機器設定の初期値のＥＣＭモードを反映する。 */
	if (SettingStatusInitialTable[SETTING_STATUS_6] & ECM_SETTING) {
		SYB_SettingStatus[SETTING_STATUS_6] |= ECM_SETTING;
	}
	else {
		SYB_SettingStatus[SETTING_STATUS_6] &= ~ECM_SETTING;
	}
	/* 機器パラメータ０１を初期化する。*/
	SYB_MachineParameter[MACHINE_PARA_1] &= ~ATTENATION_MACHINE_PARA;
	SYB_MachineParameter[MACHINE_PARA_1] |= CountryTable[SYB_MachineParameter[COUNTRY_CODE]][COUNTRY_SW_15];
}
#endif	/* End of (PRO_DISASTER_PREVENTION_FAX == ENABLE) */

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/06/09 */
UBYTE SetS1Bypass(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();
	
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_S1Bypass); /* "S1 ﾊﾞｲﾊﾟｽ           " */
	DisplayStringHigh(15, ":");
	
	if (SYB_MachineParameter[M_PARA_SW_I1] & BYPASS_S1) {
		DisplayStringHigh(16, D2W_On);
		parasw = TRUE;
	}
	else {
		DisplayStringHigh(16, D2W_Off);
		parasw = FALSE; 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter); /* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(16, D2W_Off);
				parasw = FALSE;
			}
			else {
				DisplayStringHigh(16, D2W_On);
				parasw = TRUE;
			}
			break;
		case ENTER:
			if(parasw){
				SYB_MachineParameter[M_PARA_SW_I1] |= BYPASS_S1;
			}
			else{
				SYB_MachineParameter[M_PARA_SW_I1] &= ~BYPASS_S1;
			}

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_SetS1Bypass[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

UBYTE	SetScrambleAvailable(void)
{
	UBYTE	key;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();
	
	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_Scramble);				/* ｽｸﾗﾝﾌﾞﾙ       " */
	DisplayStringHigh(15, ":");
	
	if (SYB_MachineParameter[M_PARA_SW_I0] & SCRAMBLER_AVAILABLE) {
		DisplayStringHigh(16, D2W_On);  
		parasw = TRUE;					 
	}
	else {
		DisplayStringHigh(16, D2W_Off);   
		parasw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(16, D2W_Off);
				parasw = FALSE;
			}
			else {
				DisplayStringHigh(16, D2W_On);
				parasw = TRUE;
			}
			break;
		case ENTER:
			if(parasw){
				SYB_MachineParameter[M_PARA_SW_I0] |= SCRAMBLER_AVAILABLE;
			}
			else{
				SYB_MachineParameter[M_PARA_SW_I0] &= ~SCRAMBLER_AVAILABLE;
			}

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_ScrambleAvailable[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

UBYTE	SetKeyLockOn(void)
{
	UBYTE i = 0;

	for( i = 1; i < 6; i++){
		if (SetKeyLock(i) == NG){
			return (NG);
		}
	}

	/* 完了表示 */
	CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_KeyLockOn[3]);
	ChildDisplaySetCompleted(FunctionDisplayBufferHigh);
	
	return (OK);
}

UBYTE	SetKeyLock(int Index)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	parasw;
	UBYTE	Key;
	
	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	switch(Index){
	case 1:											/* 警電/加入キーロック */
		DisplayStringHigh(0, D2W_KeidenKanyu);
		Key = KEY_LOCK_KEIDEN_KANYU;
		break;
	case 2:											/* 一斉/個別キーロック */
		DisplayStringHigh(0, D2W_IsseiKobetsu);
		Key = KEY_LOCK_ISSEI_KOBETSU;
		break;
	case 3:											/* S:ON/OFFキーロック */
		DisplayStringHigh(0, D2W_S_OnOFF);
		Key = KEY_LOCK_S_ON_OFF;
		break;
	case 4:											/* 共通/専用キーロック */
		DisplayStringHigh(0, D2W_KyotsuSenyo);
		Key = KEY_LOCK_KYOTSU_SENYO;
		break;
	case 5:											/* 自動受信キーロック */
		DisplayStringHigh(0, D2W_AutoRx);
		Key = KEY_LOCK_AUTO_RX;
		break;
	default:
		return (NG);
	}

	DisplayStringHigh(15, ":");

	if (SYB_MachineParameter[M_PARA_SW_I1] & Key) {
		DisplayStringHigh(16, D2W_On);  
		parasw = TRUE;					 
	}
	else {
		DisplayStringHigh(16, D2W_Off);   
		parasw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(16, D2W_Off);
				parasw = FALSE;
			}
			else {
				DisplayStringHigh(16, D2W_On);
				parasw = TRUE;
			}
			break;
		case ENTER:
			if(parasw){
				SYB_MachineParameter[M_PARA_SW_I1] |= Key;
			}
			else{
				SYB_MachineParameter[M_PARA_SW_I1] &= ~Key;
			}
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

/*************************************************************************
	module		:[設定]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[PRG-J07]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPR]
	date		:[]
	author		:[]
*************************************************************************/
UBYTE SetSendLevel(void)
{
	UBYTE	disp_position;
	UWORD	level_min;
	UWORD	level_max;
	UWORD	send_level;
	UWORD	temp_level;

	int		i;
	
	ClearDisplayHigh();
	ClearDisplayLow();

	/*----------------------*/
	/*  送出レベル セット   */
	/*----------------------*/
	level_min = 0;
	level_max = 15;
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, "dB");
	FixedNumberInputRangeSet(level_min, level_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(level_max));

#if (0)		/* 警察FAX DVT_ID27 Modify by SMuratec K.W.Q 2005/10/28 */
	for (i = 0; i <= 2; i++){
#else
	for (i = 0; i < 2; i++){
#endif
		send_level = 0xFFFF;
		temp_level = 0xFFFF;
		switch(i){
		case 0:
#if (0)		/* 警察FAX DVT_ID27 Modify by SMuratec K.W.Q 2005/10/28 */
			DisplayStringHigh(0, D2W_KeidenIssei);
#else
			DisplayStringHigh(0, D2W_Keiden);
#endif
			/* 送出レベル入力 */
			send_level = FixedLengthNumberInput((UBYTE)(SYS_MemorySwitch[MEMORY_SW_B4] & ATTENATION),
												  level_min,
												  level_max,
												  disp_position,
												  SubTitleDisplayBuffer);
			if (0xFFFF == send_level){
				return (NG);
			}

			/* 入力された値をセット */
			temp_level = SYS_MemorySwitch[MEMORY_SW_B4] & ~ATTENATION;
			
			SYS_MemorySwitch[MEMORY_SW_B4] = temp_level | (UBYTE)send_level;
			SYB_MachineParameter[M_PARA_SW_B3] = temp_level | (UBYTE)send_level;

			break;
#if (0)		/* 警察FAX DVT_ID27 Delete by SMuratec K.W.Q 2005/10/28 */
		case 1:
			DisplayStringHigh(0, D2W_KeidenKobetsu);
	
			/* 送出レベル入力 */
/* 警察FAX DVT_ID3 Added start by SMuratec K.W.Q 2005/10/28 */
 #if (0)
			send_level = FixedLengthNumberInput((UBYTE)(SYS_MemorySwitch[MEMORY_SW_B4] & ~ATTENATION),
												  level_min,
												  level_max,
												  disp_position,
												  SubTitleDisplayBuffer);
 #else
			send_level = FixedLengthNumberInput((UBYTE)(SYS_MemorySwitch[MEMORY_SW_B4] >> 4),
												  level_min,
												  level_max,
												  disp_position,
												  SubTitleDisplayBuffer);
 #endif
/* 警察FAX DVT_ID3 Added end by SMuratec K.W.Q 2005/10/28 */
			if (0xFFFF == send_level){
				return (NG);
			}

			/* 入力された値をセット */
			temp_level = SYS_MemorySwitch[MEMORY_SW_B4] & ATTENATION;
			
			SYS_MemorySwitch[MEMORY_SW_B4] = temp_level | (UBYTE)(send_level << 4);
			SYB_MachineParameter[M_PARA_SW_B3] = temp_level | (UBYTE)(send_level << 4);

			break;

		case 2:
#else
		case 1:
#endif
			DisplayStringHigh(0, D2W_Kanyu);

			/* 送出レベル入力 */
			send_level = FixedLengthNumberInput((UBYTE)(SYS_MemorySwitch[MEMORY_SW_B1] & ATTENATION),
												  level_min,
												  level_max,
												  disp_position,
												  SubTitleDisplayBuffer);
			if (0xFFFF == send_level){
				return (NG);
			}

			/* 入力された値をセット */
			temp_level = SYS_MemorySwitch[MEMORY_SW_B4] & ~ATTENATION;
			
			SYS_MemorySwitch[MEMORY_SW_B1] = temp_level | (UBYTE)send_level;
			SYB_MachineParameter[MACHINE_PARA_1] = temp_level | (UBYTE)send_level;

			break;
		}
		

	}
	/* 完了表示 */
	ChildDisplaySetCompleted(&D2W_SendLevel[3]);
	
	return (OK);
}

UBYTE	SetDTMFSendLevel(void)
{
	UBYTE	disp_position;
	UWORD	level_min;
	UWORD	level_max;
	UWORD	DTMF_level;
	UWORD	temp_level;

	int		i;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*----------------------*/
	/*  送出レベル セット   */
	/*----------------------*/
	level_min = 0;
	level_max = 15;
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, "dB");
	FixedNumberInputRangeSet(level_min, level_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(level_max));

	for (i = 0; i < 2; i++){
		DTMF_level = 0xFFFF;
		
		switch(i){
		case 0:
			DisplayStringHigh(0, D2W_Keiden);

			/* 送出レベル入力 */
			DTMF_level = FixedLengthNumberInput((UWORD)(SYB_MachineParameter[M_PARA_SW_B4] & ATTENATION),
												  level_min,
												  level_max,
												  disp_position,
												  SubTitleDisplayBuffer);
			if (0xFFFF == DTMF_level){
				return (NG);
			}

			/* 入力された値をセット */
			temp_level = SYB_MachineParameter[M_PARA_SW_B4] & ~ATTENATION;
			SYB_MachineParameter[M_PARA_SW_B4] = temp_level | (UBYTE)DTMF_level;

			break;
		case 1:
			DisplayStringHigh(0, D2W_Kanyu);
			/* 送出レベル入力 */
			DTMF_level = FixedLengthNumberInput((UWORD)(SYB_MachineParameter[MACHINE_PARA_2] & ATTENATION),
												  level_min,
												  level_max,
												  disp_position,
												  SubTitleDisplayBuffer);
			if (0xFFFF == DTMF_level){
				return (NG);
			}

			/* 入力された値をセット */
			temp_level = SYB_MachineParameter[MACHINE_PARA_2] & ~ATTENATION;
			SYB_MachineParameter[MACHINE_PARA_2] = temp_level | (UBYTE)DTMF_level;

			break;
		}
	}

	/* 完了表示 */
	ChildDisplaySetCompleted(&D2W_DTMFSendLevel[3]);
	
	return (OK);
}

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/10/10 */
UBYTE SetIsseiRingTimeout(void)
{
	UBYTE	disp_position;
	UWORD	level_min;
	UWORD	level_max;
	UWORD	DTMF_level;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*----------------------*/
	/*  送出レベル セット   */
	/*----------------------*/
	level_min = 0;
	level_max = 30;
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, D2W_RingTimeout);
	FixedNumberInputRangeSet(level_min, level_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(level_max));

	DTMF_level = 0xFFFF;

	DisplayStringHigh(0, &D2W_IsseiRingTimeout[3]);

	/* 送出レベル入力 */
	DTMF_level = FixedLengthNumberInput((UWORD)SYB_MachineParameter[M_PARA_SW_I2],
										  level_min,
										  level_max,
										  disp_position,
										  SubTitleDisplayBuffer);
	if (0xFFFF == DTMF_level){
		return (NG);
	}

	/* 入力された値をセット */
	SYB_MachineParameter[M_PARA_SW_I2] = (UBYTE)DTMF_level;

	/* 完了表示 */
	ClearDisplayHigh();
	ChildDisplaySetCompleted(&D2W_IsseiRingTimeout[3]);
	
	return (OK);
}
#endif		/* End of (defined (KEISATSU)) */

#if (0)		/* 警察FAX Delete by SMuratec K.W.Q 2005/10/10 */
UBYTE SetIsseiRingCount(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_RingCount);				/* "ﾒｲﾄﾞｳ ｶｲｽｳ      " */
	DisplayStringHigh(15, ":");
	
	switch (SYB_MachineParameter[M_PARA_SW_I2] & 0x0F) {
	case 0:
		DisplayStringHigh(16, "0 ");  
		parasw = 0;
		break;
	case 2:
		DisplayStringHigh(16, "2 ");  
		parasw = 2;
		break;
	case 8:
		DisplayStringHigh(16, "8 ");  
		parasw = 8;
		break;
	case 15:
		DisplayStringHigh(16, "15");  
		parasw = 15;
		break;
	default:
		DisplayStringHigh(16, "0 ");  
		parasw = 0;
		break;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case LEFT_ARROW:	/* 左矢印キー */
			switch (parasw) {
			case 0:
				DisplayStringHigh(16, "2 ");  
				parasw = 0x02;
				break;
			case 2:
				DisplayStringHigh(16, "8 ");  
				parasw = 0x08;
				break;
			case 8:
				DisplayStringHigh(16, "15");  
				parasw = 0x0F;
				break;
			case 15:
				DisplayStringHigh(16, "0 ");  
				parasw = 0x00;
				break;
			default:
				DisplayStringHigh(16, "0 ");  
				parasw = 0x00;
				break;
			}
			break;
		case FUNCTION:		/* 機能キー／右矢印キー*/
			switch (parasw) {
			case 0:
				DisplayStringHigh(16, "15");  
				parasw = 0x0F;
				break;
			case 2:
				DisplayStringHigh(16, "0 ");  
				parasw = 0x00;
				break;
			case 8:
				DisplayStringHigh(16, "2 ");  
				parasw = 0x02;
				break;
			case 15:
				DisplayStringHigh(16, "8 ");  
				parasw = 0x08;
				break;
			default:
				DisplayStringHigh(16, "0 ");  
				parasw = 0x00;
				break;
			}
			break;
		case ENTER:
			SYB_MachineParameter[M_PARA_SW_I2] = (SYB_MachineParameter[M_PARA_SW_I2] & 0xF0) | parasw;

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_IsseiRingCount[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);
	
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}
#endif

UBYTE SetIsseiAbility(void)
{
	if (SetIsseiSpeed() == NG){
		return (NG);
	}
	
	if (SetIsseiCode() == NG){
		return (NG);
	}
	
	if (SetIsseiMinScanLineTime() == NG){
		return (NG);
	}
	
	return (OK);
}

UBYTE	SetIsseiSpeed(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	parasw;
	UBYTE	save_parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_IsseiSpeed);				/* "ｼﾝｺﾞｳ ｿｸﾄﾞ      " */
	DisplayStringHigh(12, ":");

	save_parasw = SYB_MachineParameter[M_PARA_SW_I3] & ISSEI_SPEED_MASK;
	
	parasw = save_parasw;
	
	switch (parasw) {
	case 0:
		DisplayStringHigh(13, "2400bps");  
		break;
	case 1:
		DisplayStringHigh(13, "4800bps");  
		break;
	case 2:
		DisplayStringHigh(13, "7200bps");  
		break;
	case 3:
		DisplayStringHigh(13, "9600bps");  
		break;
	default:
		DisplayStringHigh(13, "2400bps");  
		break;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
			switch (parasw) {
			case 0:
				DisplayStringHigh(13, "4800bps");  
				parasw = 0x01;
				break;
			case 1:
				DisplayStringHigh(13, "7200bps");  
				parasw = 0x02;
				break;
			case 2:
				DisplayStringHigh(13, "9600bps");  
				parasw = 0x03;
				break;
			case 3:
				DisplayStringHigh(13, "2400bps");  
				parasw = 0x00;
				break;
			default:
				DisplayStringHigh(13, "2400bps");  
				parasw = 0x00;
				break;
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			switch (parasw) {
			case 0:
				DisplayStringHigh(13, "9600bps");  
				parasw = 0x03;
				break;
			case 1:
				DisplayStringHigh(13, "2400bps");  
				parasw = 0x00;
				break;
			case 2:
				DisplayStringHigh(13, "4800bps");  
				parasw = 0x01;
				break;
			case 3:
				DisplayStringHigh(13, "7200bps");  
				parasw = 0x02;
				break;
			default:
				DisplayStringHigh(13, "2400bps");  
				parasw = 0x00;
				break;
			}
			break;
		case ENTER:
			if (parasw != save_parasw){
				SYB_MachineParameter[M_PARA_SW_I3] = (SYB_MachineParameter[M_PARA_SW_I3] & ~ISSEI_SPEED_MASK) | parasw;
			}
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

UBYTE SetIsseiCode(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_IsseiCode);				/* ﾌｺﾞｳｶ ﾎｳｼｷ       " */
	DisplayStringHigh(15, ":");
	
	if (SYB_MachineParameter[M_PARA_SW_I3] & ISSEI_CODE_MR) {
		DisplayStringHigh(16, "MR");
		parasw = TRUE;
	}
	else {
		DisplayStringHigh(16, "MH");
		parasw = FALSE;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(16, "MH");
				parasw = FALSE;
			}
			else {
				DisplayStringHigh(16, "MR");
				parasw = TRUE;
			}
			break;
		case ENTER:
			if(parasw){
				SYB_MachineParameter[M_PARA_SW_I3] |= ISSEI_CODE_MR;
			}
			else{
				SYB_MachineParameter[M_PARA_SW_I3] &= ~ISSEI_CODE_MR;
			}
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

UBYTE SetIsseiMinScanLineTime(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	parasw;
	UBYTE	save_parasw;
	int		index;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, D2W_IsseiMinScanLineTime);				/* "ﾃﾞﾝｿｳ ｼﾞｶﾝ      " */
	DisplayStringHigh(12, ":");

	save_parasw = SYB_MachineParameter[M_PARA_SW_I3] & ISSEI_MIN_SCAN_LINE_TIME_MASK;
	
	parasw = save_parasw;
	
	switch (parasw) {
	case 0:
		DisplayStringHigh(13, "20ms   ");  
		index = 0;
		break;
	case 16:
		DisplayStringHigh(13, "10ms   ");  
		index = 1;
		break;
	case 48:
		DisplayStringHigh(13, "10/20ms");  
		index = 2;
		break;
	default:
		DisplayStringHigh(13, "20ms   ");  
		index = 0;
		break;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
			switch (index) {
			case 0:
				DisplayStringHigh(13, "10/20ms");  
				parasw = 0x30;
				index = 2;
				break;
			case 1:
				DisplayStringHigh(13, "20ms   ");  
				parasw = 0x00;
				index = 0;
				break;
			case 2:
				DisplayStringHigh(13, "10ms   ");  
				parasw = 0x10;
				index = 1;
				break;
			default:
				DisplayStringHigh(13, "20ms   ");  
				parasw = 0x00;
				index = 0;
				break;
			}
			break;
		case LEFT_ARROW:	/* 左矢印キー */
			switch (index) {
			case 0:
				DisplayStringHigh(13, "10ms   ");  
				parasw = 0x10;
				index = 2;
				break;
			case 1:
				DisplayStringHigh(13, "20ms   ");  
				parasw = 0x00;
				index = 0;
				break;
			case 2:
				DisplayStringHigh(13, "10/20ms");  
				parasw = 0x30;
				index = 1;
				break;
			default:
				DisplayStringHigh(13, "20ms   ");  
				parasw = 0x00;
				index = 0;
				break;
			}
			break;
		case ENTER:
			if (parasw != save_parasw){
				SYB_MachineParameter[M_PARA_SW_I3] = 
					(SYB_MachineParameter[M_PARA_SW_I3] & ~ISSEI_MIN_SCAN_LINE_TIME_MASK) | parasw;
			}

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_IsseiAbility[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);
			
			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

UBYTE SetIsseiTimeOut(void)
{
	UBYTE	disp_position;
	UWORD	count_min;
	UWORD	count_max;
	UWORD	time_out_count;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*----------------------*/
	/*  送出レベル セット   */
	/*----------------------*/
	count_min = 1;
	count_max = 3;
	CMN_MemorySetNULL(SubTitleDisplayBuffer, OPR_DISPLAY_MAX, ' ');
	CMN_StringCopy(SubTitleDisplayBuffer, "ﾌﾝ");
	FixedNumberInputRangeSet(count_min, count_max, (UBYTE)12, SubTitleDisplayBuffer);
	disp_position = (UBYTE)(OPR_DISPLAY_MAX - FigureCalculation(count_max));

	DisplayStringHigh(0, &D2W_IsseiTimeOut[3]);

	/* 送出レベル入力 */
	time_out_count = FixedLengthNumberInput((UWORD)(SYB_MachineParameter[M_PARA_SW_I4]),
										  count_min,
										  count_max,
										  disp_position,
										  SubTitleDisplayBuffer);
	if (0xFFFF == time_out_count){
		return (NG);
	}
	
	/* 入力された値をセット */
	SYB_MachineParameter[M_PARA_SW_I4] = (UBYTE)time_out_count;

	/* 完了表示 */
	ChildDisplaySetCompleted(&D2W_IsseiTimeOut[3]);
	
	return (OK);
}

UBYTE SetRemoteRxDialOne(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	memsw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, &D2W_RemoteRxDialOne[3]);		/* "ﾘﾓｰﾄ ﾄｸﾊﾞﾝ ｹﾀｽｳ  " */
	DisplayStringHigh(18, ":");

	if (CHK_RemoteTransferDialOne()) {
		DisplayStringHigh(19, "1");
		memsw = TRUE;
	}
	else {
		DisplayStringHigh(19, "2");
		memsw = FALSE;
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (memsw) {
				DisplayStringHigh(19, "2");
				memsw = FALSE;
			}
			else {
				DisplayStringHigh(19, "1");
				memsw = TRUE;
			}
			break;
		case ENTER:
			if (memsw) {
				SYS_MemorySwitch[MEMORY_SW_G5] |= REMOTE_TRANSFER_DIAL_ONE;
			}
			else {
				SYS_MemorySwitch[MEMORY_SW_G5] &= ~REMOTE_TRANSFER_DIAL_ONE;
			}

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_RemoteRxDialOne[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

UBYTE SetKeidenRxPriority(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	parasw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, &D2W_KeidenRxPriority[3]);		/* "ｹｲﾃﾞﾝ ﾕｳｾﾝ ｼﾞｭｼﾝ  " */
	DisplayStringHigh(15, ":");

	if (SYB_MachineParameter[M_PARA_SW_I0] & KEIDEN_RX_PRIORITY) {
		DisplayStringHigh(16, D2W_On);  
		parasw = TRUE;					 
	}
	else {
		DisplayStringHigh(16, D2W_Off);   
		parasw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (parasw) {
				DisplayStringHigh(16, D2W_Off);
				parasw = FALSE;	
			}
			else {
				DisplayStringHigh(16, D2W_On);
				parasw = TRUE;
			}
			break;
		case ENTER:
			if (parasw) {
				SYB_MachineParameter[M_PARA_SW_I0] |= KEIDEN_RX_PRIORITY;
			}
			else {
				SYB_MachineParameter[M_PARA_SW_I0] &= ~KEIDEN_RX_PRIORITY;
			}

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_KeidenRxPriority[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}

void GetFPGAVersion(void)
{
	UBYTE	key;
	UBYTE	keytype;

	ClearDisplayHigh();
	ClearDisplayLow();

	S1_GetFPGA_VersionString(FunctionDisplayBufferLow);

	DisplayStringHigh(0, &D2W_FPGAVersion[3]);
	DisplayStringLow(0, FunctionDisplayBufferLow);

	while (1) {
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		key = GetInputKeyCode();
		keytype = GetInputKeyType();

		switch (keytype) {
		case STOP:
			return;
		case NO_EFFECT:
			break;
		default:
			NackBuzzer();
			break;
		}
	}
	
	return;
}

UBYTE	SetKeidenDialTone(void)
{
	UBYTE	keycode;
	UBYTE	keytype;
	UBYTE	memsw;

	ClearDisplayHigh();
	ClearDisplayLow();

	/*-----------*/
	/** 画面表示 */
	/*-----------*/
	/* 上段表示 */
	DisplayStringHigh(0, &D2W_KeidenDialTone[3]);		/* "ｹｲﾃﾞﾝ ﾀﾞｲﾔﾙ ﾄｰﾝ  " */
	DisplayStringHigh(15, ":");
	
	if (!(SYS_MemorySwitch[MEMORY_SW_A1] & DIALTONE_OR_TIMEUP_EXT)) {
		DisplayStringHigh(16, D2W_On);  
		memsw = TRUE;					 
	}
	else {
		DisplayStringHigh(16, D2W_Off);   
		memsw = FALSE;					 
	}

	/* 下段点滅表示 */
	FlashDisplayStringLow(D2W_ProgramEnter);	/* "            ｷﾉｳ/ｾｯﾄ " */

	while(1) {

		/** キー取り込み */
		OPR_GetKey(KEY_WAIT_ONE_MINUTE);
		keycode = GetInputKeyCode();
		keytype = GetInputKeyType();

		/** 取り込んだキーに対する処理を実行 */
		switch (keytype) {
		case FUNCTION:		/* 機能キー／右矢印キー*/
		case LEFT_ARROW:	/* 左矢印キー */
			if (memsw) {
				DisplayStringHigh(16, D2W_Off);
				memsw = FALSE;
			}
			else {
				DisplayStringHigh(16, D2W_On);
				memsw = TRUE;
			}
			break;
		case ENTER:
			if (memsw) {
				SYS_MemorySwitch[MEMORY_SW_A1] &= ~DIALTONE_OR_TIMEUP_EXT;
			}
			else {
				SYS_MemorySwitch[MEMORY_SW_A1] |= DIALTONE_OR_TIMEUP_EXT;
			}

			/* 完了表示 */
			CMN_MemorySetNULL(FunctionDisplayBufferHigh, OPR_DISPLAY_MAX, ' ');
			CMN_StringCopy(FunctionDisplayBufferHigh, &D2W_KeidenDialTone[3]);
			ChildDisplaySetCompleted(FunctionDisplayBufferHigh);

			return (OK);
		case STOP:
		case KEY_TIME_UP:
			return (NG);

		case NO_EFFECT:
			break;

		default:
			NackBuzzer();
			break;
		}
	}
	
	return (NG);
}
#endif		/* End of (defined (KEISATSU)) */
