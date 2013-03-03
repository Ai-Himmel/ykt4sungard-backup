/* By S.K Spe.21,1995 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\status.h"

/************************************************************************
 * 桐用初期値テーブル													*
 * UBYTE MachineParameterInitialTable[SYS_MACHINE_PARAMETER_MAX]*
 * UBYTE SettingStatusInitialTable[SYS_SETTING_MAX]			*
 * UBYTE MemorySwitchInitialTable[SYS_MEMORY_SWITCH_MAX]	*
 * 1994/02/23															*
 * 吉川弘康																*
 ************************************************************************/


/************************************************************************
 * 機器パラメータの初期値												*
 * UBYTE SYB_MachineParameter[SYS_MACHINE_PARAMETER_MAX]		*
 * 1994/01/31															*
 * 吉川弘康																*
 ************************************************************************/
extern const UBYTE MachineParameterInitialTable[SYS_MACHINE_PARAMETER_MAX];

/************************************************************************
 * 機器設定の初期値														*
 * UBYTE SYB_SettingStatus[SYS_SETTING_MAX]						*
 * 1994/01/31															*
 * 吉川弘康																*
 ************************************************************************/
extern const UBYTE SettingStatusInitialTable[SYS_SETTING_MAX];

/************************************************************************
 * メモリスイッチの初期値												*
 * UBYTE SYS_MemorySwitch[SYS_MEMORY_SWITCH_MAX]				*
 * 1994/01/31															*
 * 吉川弘康																*
 ************************************************************************/
extern const UBYTE MemorySwitchInitialTable[SYS_MEMORY_SWITCH_MAX];


/************************************************************************
 * 機種固有スイッチの初期値												*
 * UBYTE SYS_MachineUniqSwitch[SYS_MEMORY_SWITCH_MAX]			*
 * 1996/03/06															*
 * 江口																	*
 ************************************************************************/
extern	const UBYTE UniqSwitchInitialTable[SYS_MEMORY_SWITCH_MAX];

/************************************************************************
 * 保守用スイッチの初期値												*
 * UBYTE SYB_MaintenanceSwitch[SYS_MEMORY_SWITCH_MAX]			*
 * 1996/03/06															*
 * 江口																	*
 ************************************************************************/
extern	const UBYTE MaintenanceSwInitialTable[SYS_MEMORY_SWITCH_MAX];

/*----------------------------------------------*/
/*ハードディップスイッチが付いている機械かどうか*/
/*----------------------------------------------*/
extern const UBYTE HardDIP_SwitchEnable;

/*
const UBYTE HardDIP_SwitchEnable = 1;
*/

#if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
extern CONST UDWORD TBL_BaseAddressMD9803;	/**  MD9803実装先頭アドレス */
#endif

/* スクランブルあり・なし用 By Y.Suzuki 1997/09/01 */
#if (PRO_CIPHER == ENABLE)
/* extern CONST UBYTE ScrambleOn;By Y.Suzuki 1997/12/09 */
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.4.21 K.Kawata	*/
extern CONST UBYTE ROM_Switch[SYS_ROM_SWITCH_MAX];
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI) && defined(JPN)*/	/* ＨＩＮＯＫＩ特ＲＯＭ用ＲＯＭスイッチ by H.Hirao 1999/04/14 */
#if (((PRO_KEYPANEL == PANEL_HINOKI) && defined(JPN)) || ((PRO_KEYPANEL == PANEL_SATSUKI2) && defined(JPN))  || ((PRO_KEYPANEL == PANEL_STOCKHM2) && defined(JPN)))	/* Add by Y.Kano 2003/07/11 *//* ＨＩＮＯＫＩ特ＲＯＭ用ＲＯＭスイッチ by H.Hirao 1999/04/14 */

extern CONST UBYTE ROM_SW_SpecialRelayTrans;	/* 折り返し特ＲＯＭ */
extern CONST UBYTE ROM_SW_SpecialPauseInput;	/* ダイアル記号キーにポーズ追加 */
extern CONST UBYTE ROM_SW_SpecialDoctorReport;	/* 医師会特ＲＯＭ */

 #if (PRO_POST_OFFICE == ENABLE)
extern CONST UBYTE SYS_JOURNAL_MAX;				/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
 #else
extern CONST UBYTE ROM_SW_DUMMY60;		/* PRO_POST_OFFICE == ENABLEでSYS_JOURNAL_MAXを定義しているのでべたで定義するとずれる為Dummyで領域確保 By O.Kimoto 2002/06/17 */
 #endif

extern CONST UBYTE ROM_SW_SpecialDailyPolling;	/* 毎日ポーリングＲＯＭ *//* Add By O.Kimoto 2002/06/17 */
extern CONST UBYTE ROM_SW_OptionalSpeedDial;	/* スギ薬局特ROM（任意短縮）2003/01/06 T.Takagi */
#endif

#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/17 */
extern CONST UBYTE	CheckerRomSw;
extern CONST UBYTE	CheckerRomTimer;
#endif
