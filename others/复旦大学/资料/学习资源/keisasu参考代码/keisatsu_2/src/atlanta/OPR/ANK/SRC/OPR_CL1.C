/************************************************************************
*	System		: POPLAR_B/POPLAR_L/ANZU_L
*	File Name	: OPR_CL1.C
*	Author		: 渡辺一章
*	Date		: 1996/10/18
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: クラス１関係のオペレーション
*	Maintenance	: 
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\param.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\syslocal.h"
#include	"\src\atlanta\opr\ank\define\opr_def.h"

#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\ctry_pro.h"
#include	"\src\atlanta\define\mon_pro.h"
/*#include	"\src\atlanta\define\prn_pro.h"		/* 移植まだ */
#include	"\src\atlanta\define\stng_pro.h"
#include	"\src\atlanta\opr\ank\define\opr_pro.h"
#include	"\src\memsw\define\mems_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_wrd0.h"

#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\define\cl1_pro.h"
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif

/* Prototype
void	SetRS232CPCFaxScsn(void);
void	SetRS232CParameter(void);
void	SetRS232CPCFaxInitial(void);
*/

#if (PRO_CLASS1 == ENABLE)
/*************************************************************************
	module		:[ＲＳ２３２Ｃローカルスキャン]
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
	date		:[1996/08/06]
	author		:[松隈,渡辺一章]
*************************************************************************/
void SetRS232CPCFaxScsn(void)
{
	if (SYS_RS232C_Exist == 0) { /* RS232C基盤がない 1996/09/17 Matsukuma */
		NackBuzzer();
		return;
	}
 #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/02/01 */
	if (!QueryClass1Enable(2)) {	/* クラス１デュアル制限 */
		NackBuzzer();
		return;
	}
 #endif
	/* 蓄積できる状態かを調べます */
	switch (CheckScanStartEnable(OPR_DOC_SET_CHK_INP_SET)) {
	case OPR_SCAN_ENABLE:	/* 原稿読み取り可能な時 */
		if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)
		 && (SYS_CL1_RxEnableFlag == 1)
		 && (SYS_CL1_Status == 0)

		/* 以下２行追加  By O.Kimoto 1999/07/19 */
		 && (CheckMemoryOver() == FALSE)
		 && (CheckScanDisableCondition() == FALSE)) {
			/*OperationMessageToMain.Item = FROM_OPERATION; 1996/07/08 eguchi*/
			OperationMessageToMain.Message = MSG_STORE_CLASS1_TX_DOC;
			snd_msg(mbxno.MAN_Task, &OperationMessageToMain);
			MainTaskExecWait();
		}
		else {
			NackBuzzer();
		}
		break;
	case OPR_SCAN_DISABLE:	/* 原稿読み取り不可能な時 */
		NackBuzzer();
		break;
	case OPR_SCAN_STOP:		/* ブック原稿サイズ入力中に停止又は、タイムアップした時 */
		/* ナックは鳴らしません */
		break;
	default:
		break;
	}
}

/*************************************************************************
	module		:[データスピードセット]
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
	date		:[1996/08/06]
	author		:[松隈]
*************************************************************************/
void SetRS232CParameter(void)
{
	if (SYS_RS232C_Exist == 0) { /* RS232C基盤がない 1996/09/17 Matsukuma */
		NackBuzzer();
		return;
	}

	/* データスピードのセット */
	if (EnterSettingStatus(D2W_SelectRS232CBaudRate,
						   D2W_RS232CVariable,
						   7,
						   SETTING_STATUS_5,
						   OPR_RS232C_SPEED,
						   (RS232C_SPEED_VARIABLE | RS232C_SPEED_600  | RS232C_SPEED_1200 |
							RS232C_SPEED_2400     | RS232C_SPEED_4800 | RS232C_SPEED_9600 |
							RS232C_SPEED_19200 )) == NG) {

		return;
	}
	/* SYB_SettingStatus[]がセットされたらシリアルコントローラのパラメータレジスタをセットします。
	** ＳＴＯＰで終了した場合、SYB_SettingStatus[]がセットされたのにシリアルコントローラの
	** パラメータレジスタがセットし直されない。by H.Hirao 1999/02/10
	*/
 #if (PRO_RS_INTERNAL == ENABLE)
	MPSCSetParameter();
 #else
	/* MPSCSetParameter(); */
 #endif
	
	/* パリティビットのセット */
	if (EnterSettingStatus(D2W_SelectParity,
						   D2W_RS232CNone,
						   3,
						   SETTING_STATUS_5,
						   OPR_RS232C_PARITY,
						   (RS232C_PARITY_NONE | RS232C_PARITY_ODD | RS232C_PARITY_EVEN)) == NG) {

		return;
	}
	/* SYB_SettingStatus[]がセットされたらシリアルコントローラのパラメータレジスタをセットします。
	** ＳＴＯＰで終了した場合、SYB_SettingStatus[]がセットされたのにシリアルコントローラの
	** パラメータレジスタがセットし直されない。by H.Hirao 1999/02/10
	*/
 #if (PRO_RS_INTERNAL == ENABLE)
	MPSCSetParameter();
 #else
	/* MPSCSetParameter(); */
 #endif
	
	/* ストップビット */
	if (EnterSettingStatus(D2W_Select232CStopBit,
						   D2W_RS232C1bit,
						   2,
						   SETTING_STATUS_5,
						   OPR_VALID_CHECK_NOT_NEED,
						   RS232C_STOP_LENGTH_2) == NG) {
		return;
	}
	/* SYB_SettingStatus[]がセットされたらシリアルコントローラのパラメータレジスタをセットします。
	** ＳＴＯＰで終了した場合、SYB_SettingStatus[]がセットされたのにシリアルコントローラの
	** パラメータレジスタがセットし直されない。by H.Hirao 1999/02/10
	*/
 #if (PRO_RS_INTERNAL == ENABLE)
	MPSCSetParameter();
 #else
	/* MPSCSetParameter(); */
 #endif

	/* データ長のセット */
	if (EnterSettingStatus(D2W_Select232CDataLength,
						   D2W_RS232C7bit,
						   2,
						   SETTING_STATUS_5,
						   OPR_VALID_CHECK_NOT_NEED,
						   RS232C_DATA_LENGTH_8) == NG) {

		return;
	}

	ChildDisplaySetCompleted(D2W_SetRS232CParameter);	/* " RS232C ｾｯﾄ         " */

	MPSCSetParameter();

	if ((CL1_DataSpeed = CHK_RS232C_Speed()) == RS232C_SPEED_VARIABLE) {
		CL1_FaxSoftType = FS_SPEED_AUTO;
		CL1_DataSpeed = RS232C_SPEED_2400;
		MPSCDataSpeedChange(CL1_DataSpeed);
	}
	else {
		CL1_FaxSoftType = FS_SPEED_FIX;
	}
}

/*************************************************************************
	module		:[自動初期化]
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
	date		:[1996/08/06]
	author		:[松隈]
*************************************************************************/
void SetRS232CPCFaxInitial(void)
{
	if (SYS_RS232C_Exist == 0) { /* RS232C基盤がない 1996/09/17 Matsukuma */
		NackBuzzer();
		return;
	}
 #if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/02/01 */
	if (!QueryClass1Enable(2)) {	/* クラス１デュアル制限 */
		NackBuzzer();
		return;
	}
 #endif

	if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXMODEM)
	&&	(SYS_CL1_RxEnableFlag == 1) 
	&&  (SYS_CL1_Status == 0)) {
		OperationMessageToMain.Message = MSG_SERV_AUTO_INIT;
		snd_msg( mbxno.MAN_Task, &OperationMessageToMain );
		MainTaskExecWait();
	}
	else {
		/* エラー表示をどうするか　1996/09/13 Eguchi TBD */
		NackBuzzer();
	}
}
#endif
