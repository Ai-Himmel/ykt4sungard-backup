/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: man_comm.c
*	Author			:
*	Date			: 1997/06/09
*	RealTimeOS		: RISCモニタ
*	Description		: メインタスクMAN_Task()のメッセージ処理部
*					: 回線、通信関連部
*	Module Name		: MAN_FromClass1()
*					: MAN_CL1Faxcom()
*					: MAN_DPR_RemoteFuncExecTask()
*					: MAN_FromROT_Task()
*					: MAN_FromFaxcomOption()
*	Maintenance		:
*
*	Copyright (C) 1997 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\sysprint.h"
#include  "\src\atlanta\define\sysrxsw.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sys_opt.h"
#include  "\src\atlanta\define\sys_line.h"
#include  "\src\atlanta\define\fcm_def.h"
#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\sysmjnl.h"
#include  "\src\atlanta\define\sysmcopy.h"
/*MON*/
#include  "\src\atlanta\sh7043\define\def_tib.h"
#include  "\src\atlanta\sh7043\define\def_evtn.h"
/*SCN*/
#include  "\src\atlanta\define\sysscan.h"
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"
/*ROT*/
#if (PRO_ROTATE == ENABLE)
#include  "\src\atlanta\define\rot_pro.h"
#endif
/* CDC */
#include  "\src\atlanta\define\cdc_def.h"
/* NCU */
#include  "\src\atlanta\define\ncu_def.h"

#if(PRO_CIPHER == ENABLE)
#include "\src\atlanta\scd\ext_v\cph_data.h"
#include "\src\atlanta\ext_v\mem_data.h"
#include "\src\atlanta\define\mntsw_e.h"
#endif

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\man_data.h"
#include  "\src\atlanta\ext_v\mlt_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include  "\src\atlanta\sh7043\ext_v\extv_sem.h"
/*FCM*/
#include  "\src\atlanta\ext_v\fcm_data.h"
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include  "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_CLASS1 == ENABLE)
#include  "\src\atlanta\ext_v\cl1_data.h"
 #if (PRO_PRINT_TYPE == THERMAL)
 #include  "\src\atlanta\prt\iu_therm\ext_v\prn_data.h" /* added by H.Hirao 1999/01/12 */
 #endif
#endif
#if (PRO_PC_PRINT == ENABLE)
#include  "\src\atlanta\ext_v\dpr_data.h"
#endif

/*プロトタイプ宣言*/
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\stng_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#if (PRO_DPRAM == ENABLE)
#include  "\src\atlanta\define\dpr_pro.h"
#endif
#include  "\src\atlanta\define\scn_pro.h"
#include  "\src\atlanta\sh7043\define\io_pro.h"
#include  "\src\atlanta\define\mlt_pro.h"

void	SetSecurityRxChkMsgPrint(void);		/* 1998/04/13 Y.Murata */

static UWORD	tskno_Bell = 0;

#if (PRO_CLASS1 == ENABLE)
/*************************************************************************
	module		:[CLASS 1 ﾀｽｸからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromClass1(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
	UWORD	cl1_item;
	UWORD	cl1_message;
	UWORD	cl1_sub_message1;
	UWORD	cl1_sub_message2;
	/* 追加 1997/08/07 Y.Matsukuma */
	UWORD line_number;	/* Add Class1 By O.Kimoto 1997/05/28 */
	unsigned char	value;	/* D65B-010 By O.Kimoto 1997/06/18 */

	cl1_item = item;
	cl1_message = message;
	cl1_sub_message1 = sub_message1;
	cl1_sub_message2 = sub_message2;

	line_number = 1;	/* Add Class1 By O.Kimoto 1997/05/28 */

	/* D65B-010 By O.Kimoto 1997/06/18 */
	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) {
		value = 0;
	}
	else {
		value = 1;
	}

	switch (cl1_message) {
	case MSG_CL1_CALLED:
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
#else
	/*	if (cl1_sub_message1 == 0x0010) {	/@ CL1_CALLED = 0x0010	*/
		if (tskno_NCU_Task != 0xffff) {
			del_tsk(&tskno_NCU_Task);
		}
#endif

#if (PRO_CLASS1_VIA_DPRAM == ENABLE)	/* 条件コンパイルぬけてる 1997/12/04 */
		/* 本来は、SYS_OptionLineStatusの状態変数を変更するべきですが、
		** ＬＣＤの表示の関係でＣｌａｓｓ１のみ、SYS_MachineStatusの状態変数を変更します。
		** By O.Kimoto 1997/05/28
		*/
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;	/* Add By O.Kimoto 1997/05/28 */
		SYS_OptionLineStatus[line_number] |= SYS_OPTION_LINE_BUSY;	/* D65B-010 By O.Kimoto 1997/06/18 */
		SYS_OptionLineStatus[line_number] |= SYS_OPTION_FAXMODEM;	/* D65B-010 By O.Kimoto 1997/06/18 */
#endif
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
		switch (cl1_sub_message1) {
		case	CL1_DIALIN_CALLED:		/* Class1ダイヤルイン対応   */
			/* ダイヤルインタスクを終了させる */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_DIAL_IN);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_CL1_DIALIN_EXIT;
			snd_msg(mbxno.NCU_DialInAutoSwitchTask, &MainTaskMessage);
			break;
		case	CL1_FNET_CALLED:		/* Class1 F網対応   */
			if (!(SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_CL1_FNET_RING)) {
				del_tsk(&tskno_NCU_Task);
			}
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~(SYS_CL1_FNET_RING);
			break;
		default:	/* CL1_CALLED */
			del_tsk(&tskno_NCU_Task);
			break;
		}
#endif

		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRE_LINE_BUSY; /** CI検出中クリア */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /** 通信使用中セット */
	/*	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;*/ /* FAXCOM動作中セット->キー入力ガードの為	*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM; /** CLASS1動作中セット */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_RCV_ACCEPT;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;
	case MSG_CL1_ONLINE_REQ:
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/9 K.Kawata */
		if (CL1_ExtFunctionEnableFlag == 1) { /* 拡張モードであれば */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_ONLINE_REJECT; /** 通信不可 */
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			break;
		}
#endif
#if (PRO_CLASS1_VIA_DPRAM == DISABLE)	/* 条件コンパイルぬけてる 1997/12/04 */
 #if (PRO_RS_INTERNAL == ENABLE)
		/* 他のリソースを使用中はクラス１使用不可にする by H.Hirao 1999/02/01 */
		if (CMN_CheckLineEnable() /** 通信使用状況確認 */
 		 && QueryClass1Enable(0)) {
 #else
		if (CMN_CheckLineEnable()) { /** 通信使用状況確認 */
 #endif
#else
		if (OPT_CHK_SelecetedLineEnable(value)) { /* 回線使用可能か確認 *//* D65B-010 By O.Kimoto 1997/06/18 */
#endif
			if (tskno_NCU_Task != 0xffff) {
				del_tsk(&tskno_NCU_Task);
			}

#if (PRO_CLASS1_VIA_DPRAM == ENABLE)	/* 条件コンパイルぬけてる 1997/12/04 */
			/* 本来は、SYS_OptionLineStatusの状態変数を変更するべきですが、
			** ＬＣＤの表示の関係でＣｌａｓｓ１のみ、SYS_MachineStatusの状態変数を変更します。
			** By O.Kimoto 1997/05/28
			*/
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;	/* Add By O.Kimoto 1997/05/28 */
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_LINE_BUSY;	/* D65B-010 By O.Kimoto 1997/06/18 */
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_FAXMODEM;	/* D65B-010 By O.Kimoto 1997/06/18 */
#endif

			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_PRE_LINE_BUSY; /** CI検出中クリア */
			SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_LINE_BUSY; /** 通信使用中セット */
		/*	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXCOM;*/ /* FAXCOM動作中セット->キー入力ガードの為	*/
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM; /** CLASS1動作中セット */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_ONLINE_ACCEPT; /** 通信可 */
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
		else {
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
			/* Class1 F網対応 */
			if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_CL1_FNET_RING) {
				SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~(SYS_CL1_FNET_RING);
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY);
				cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
			}
#endif
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_ONLINE_REJECT; /** 通信不可 */
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
		break;
	case MSG_CL1_SCAN_END:		/* Local Scan END */
	case MSG_CL1_PRINT_END:		/* Local Print END */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_EXIT;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
 #if (PRO_RS_INTERNAL == ENABLE)	/* ローカルスキャン、ローカルプリント後、一定時間、デュアル制限する by H.Hirao 1999/05 12 */
		CMN_DisableInterrupt();
		CL1_RestrictionStatusResetTimer = cl1_sub_message2;
		CMN_EnableInterrupt();
 #endif
		break;
	case MSG_CL1_ONLINE_EXIT:	/* Class 1 FaxModem END */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_EXIT;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM;		/** CLASS1動作中クリア	*/
		/* SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXCOM;	*//* 通信実行中をクリア */
#if (PRO_CLASS1_VIA_DPRAM == ENABLE)	/* 条件コンパイルぬけてる 1997/12/04 */
		/* 本来は、SYS_OptionLineStatusの状態変数を変更するべきですが、
		** ＬＣＤの表示の関係でＣｌａｓｓ１のみ、SYS_MachineStatusの状態変数を変更します。
		** By O.Kimoto 1997/05/28
		*/
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;	/* Add By O.Kimoto 1997/05/28 */
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_LINE_BUSY;	/* D65B-010 By O.Kimoto 1997/06/18 */
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_FAXMODEM;	/* D65B-010 By O.Kimoto 1997/06/18 */
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_REAL_LINE_BUSY;
#endif
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY; /* 回線使用中クリア */
 #if (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
		CMN_DisableInterrupt();
		CL1_DualRestrictionStatus &= ~CL1_CLASS1_IN_USE;	/* クラス１受信中リセット */
		CL1_RestrictionStatusResetTimer = cl1_sub_message2;	/* リモート受信後、一定時間デュアル制限します by H.Hirao 1999/05/12 */
		CMN_EnableInterrupt();
 #endif
 #if (PRO_NUMBER_DISPLAY == ENABLE)	/* 発信者番号の表示を消す by H.Hirao 1999/05/12 */
		SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_ND_DISPLAY;
 #endif
		cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
		SYS_VariableTimer = 5;
		break;

	case MSG_CL1_RING_TIMEOUT:
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/

#if (PRO_CLASS1_VIA_DPRAM == ENABLE)	/* 条件コンパイルぬけてる 1997/12/04 */
		/* 本来は、SYS_OptionLineStatusの状態変数を変更するべきですが、
		** ＬＣＤの表示の関係でＣｌａｓｓ１のみ、SYS_MachineStatusの状態変数を変更します。
		** By O.Kimoto 1997/05/28
		*/
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;	/* Add By O.Kimoto 1997/05/28 */
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_LINE_BUSY;	/* D65B-010 By O.Kimoto 1997/06/18 */
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_FAXMODEM;	/* D65B-010 By O.Kimoto 1997/06/18 */
		SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_REAL_LINE_BUSY;
#endif

		/* SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY; *//* 回線使用中クリア */
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY | SYS_PRE_LINE_BUSY);	/** 回線使用中クリア */
 #if (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
		CMN_DisableInterrupt();
		CL1_DualRestrictionStatus &= ~CL1_CLASS1_IN_USE;	/* クラス１受信中リセット */
		CMN_EnableInterrupt();
 #endif
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998  */
		switch (cl1_sub_message1) {
		case	CL1_DIALIN_CALLED:
			/* Class1ダイヤルイン対応  1998/04/06 s.takeuchi */
			/* ダイヤルインタスクを終了させる */
			SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_DIAL_IN);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = MSG_CL1_DIALIN_EXIT;
			snd_msg(mbxno.NCU_DialInAutoSwitchTask, &MainTaskMessage);
			break;
		default:
			break;
		}
#endif
		cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
		SYS_VariableTimer = 5;
		break;
	case MSG_CL1_PRINT_REQ:
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
		/* フラッシュＲＯＭ書き換え中なら、着信しない */
		if (SYB_FlashROM_WriteStatus != NO_STATUS) {
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_PRINT_REJECT;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			break;
		}
#endif
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/7 K.Kawata */
		if (CL1_ExtFunctionEnableFlag == 1) { /* 拡張モードであれば */
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_PRINT_REJECT;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
			break;
		}
#endif
	/*	if (CMN_CheckPrintEnable(SYS_FAXMODEM)) {	*/
/* #if (PRO_MULTI_LINE == DISABLE)	 1996/12/24 Y.Murata */
/*		if (CMN_CheckMemoryReceiveEnable() == TRUE) {	 1996/09/06 */
/* #else */
 #if (PRO_RS_INTERNAL == ENABLE)
		/* 他のリソースを使用中はクラス１使用不可にする by H.Hirao 1999/02/01 */
 		if ((CMN_CL1CheckMemoryReceiveEnable() == TRUE)
 		  && QueryClass1Enable(0)) {
 #else
		if (CMN_CL1CheckMemoryReceiveEnable() == TRUE) {
 #endif
/* #endif */
		/* ANZUのﾛｰｶﾙﾌﾟﾘﾝﾄは､メモリ受信 */
		/*	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; *//* プリンタ使用中セット */
			SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM; /** CLASS1動作中セット */
			cre_tsk(&tskno_CL1_FaxComTask, TSK_CL1_FAXCOMTASK, 0);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = SYS_CLASS1_PRINT;
			snd_msg(mbxno.CL1_FaxComTask, &MainTaskMessage);
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_PRINT_ACCEPT;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
		else {
			MainTaskMessage.Item = FROM_MAIN;
			MainTaskMessage.Message = CL1_PRINT_REJECT;
			snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		}
		break;
	case MSG_CL1_SCAN_ACCEPT:
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/** CLASS1動作中セット */
		cre_tsk(&tskno_CL1_FaxComTask, TSK_CL1_FAXCOMTASK, 0);
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = SYS_CLASS1_SCAN;
		MainTaskMessage.SubMessage1 = cl1_sub_message1;
		snd_msg(mbxno.CL1_FaxComTask, &MainTaskMessage);
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_EXIT;
		snd_msg(mbxno.CL1_Task, &MainTaskMessage);
		break;
	case MSG_CL1_SCAN_REJECT:
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
		/*
		** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
		** 原稿無し：MEM_NO_INDEX(0xFFFF)
		** 原稿有り：０以外のページ数
		** By S.Kawasaki 1996/08/10
		*/
		/* if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER)) { By S.Kawasaki 1996/08/10 */
		if (SYB_CL1_LocalScanDocStatus == 1) {/**ローカルスキャン原稿あり *//* 1996/09/24 Eguchi */
			SYB_CL1_LocalScanDocStatus = 0; /**ローカルスキャン原稿なしセット *//*1996/09/24 Eguchi */
		}
#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/18 K.Kawata */
		if (CL1_ExtFunctionEnableFlag == 1) { /* 拡張モードであれば */
			if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 原稿があれば */
				if (CL1_ExtLocalPrtRejectCnt > 0) {
					CL1_ExtTransmitErrorFlag = 0;
					CL1_ExtLocalPrtRejectCnt--;
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_FAXMODEM;	/** CLASS1動作中セット */
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = CL1_SCAN_REQ;
					MainTaskMessage.SubMessage1 = SYS_CLASS1_SCAN_MEMORY;
					snd_msg(mbxno.CL1_Task, &MainTaskMessage);
				}
				else {
					MAN_ChangeItemLS2MP();
					CL1_ExtFunctionEnableFlag = 0;
					CL1_ExtLocalPrtRejectCnt = 0;
					CL1_ExtTransmitErrorFlag = 0;
				}
			}
			else {
				CL1_ExtFunctionEnableFlag = 0;
				CL1_ExtLocalPrtRejectCnt = 0;
				CL1_ExtTransmitErrorFlag = 0;
			}
		}
		else {
			if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 原稿があれば */
				MEM_ClearDocAndFATArea(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
			}
		}
#else
		if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 原稿があれば */
			MEM_ClearDocAndFATArea(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
		}
#endif
 #if (PRO_RS_INTERNAL == ENABLE)	/* ローカルスキャン後、一定時間デュアル制限します by H.Hirao 1999/05/12 */
		CMN_DisableInterrupt();
		CL1_RestrictionStatusResetTimer = cl1_sub_message2;
		CMN_EnableInterrupt();
 #endif
		break;
	case MSG_CL1_TEST_END:
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = CL1_RS232C_TEST_END;
		MainTaskMessage.SubMessage1 = cl1_sub_message1;
		/* snd_msg(mbxno.OPR_Task, &MainTaskMessage); Comment By Eguchi 1996/04/19 */
		snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage); /* 1996/04/19 Eguchi */
		rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);	 /* 1996/04/19 Eguchi */
		break;
	case MSG_CL1_INIT_END:
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~SYS_FAXMODEM; /** CLASS1動作中クリア	*/
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~SYS_ERROR_CLASS1_INIT;
		if (cl1_sub_message1 == 0) { /* NG */
			SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_CLASS1_INIT;
		}
 #if (PRO_RS_INTERNAL == ENABLE)	/* クラス１初期化後、一定時間デュアル制限します by H.Hirao 1999/05/12 */
		CMN_DisableInterrupt();
		CL1_RestrictionStatusResetTimer = cl1_sub_message2;
		CMN_EnableInterrupt();
 #endif
		break;
#if (PRO_CL1_TELFAX_LAN == ENABLE) /* S.Fukui June 19,1998 */
	case MSG_CL1_FNET_RING:		/* Class1 F網対応  */
		/*
		* 再度NCU_Taskを起動し1300Hz検出する (PRE_LINE_BUSYのまま)
		*/
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_CL1_FNET_RING) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~(SYS_CL1_FNET_RING);
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
			SYS_VariableTimer = 5;
		}
		break;
	case MSG_CL1_FNET_TIMEOUT:	/* Class1 F網対応  1998/04/09 s.takeuchi */
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_FAXMODEM);	/** CLASS1動作中クリア	*/
		SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_LINE_BUSY | SYS_PRE_LINE_BUSY);	/** 回線使用中クリア */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] & SYS_CL1_FNET_RING) {
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~(SYS_CL1_FNET_RING);
			cre_tsk(&tskno_NCU_Task, TSK_NCU_TASK, 0);
		}
		SYS_VariableTimer = 5;
		break;
#endif
	default:
		break;
	}
	/* 完了表示 */
	if ((cl1_message == MSG_CL1_ONLINE_EXIT)
	||	(cl1_message == MSG_CL1_INIT_END && cl1_sub_message1 == 1)
	||	(cl1_message == MSG_CL1_SCAN_REJECT)) {
		if (tskno_pc_fax_complete == 0xFFFF) {
			cre_tsk(&tskno_pc_fax_complete , TSK_CMN_MAN_TIMER10MSTASK , &PC_FAX_CompleteMessage);
		}
	}
}
#endif	/* #if (PRO_CLASS1 == ENABLE) */


#if (PRO_CLASS1 == ENABLE)
/*************************************************************************
	module		:[ＣＬＡＳＳ１通信タスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromCL1Faxcom(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	i;
	UWORD	cl1_item;
	UWORD	cl1_message;
	UWORD	cl1_sub_message1;
	UWORD	cl1_sub_message2;

	cl1_item = item;
	cl1_message = message;
	cl1_sub_message1 = sub_message1;
	cl1_sub_message2 = sub_message2;

/* #if 0	@@ test */

	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.CL1_FaxComTask, &MainTaskMessage);
	switch (cl1_message) {
	case MSG_RX_PRINT_PAGE: /* 通常のメモリ受信原稿の時だけこのメッセージを受信、１ページ受信毎にメモリ受信テーブルを更新 */
		/*
		** MEM_CountTotalPage()の戻り値は次の通り。原稿の有無確認方法変更。
		** 原稿無し：MEM_NO_INDEX(0xFFFF)
		** 原稿有り：０以外のページ数
		** By S.Kawasaki 1996/08/10
		*/
		if ( (SYS_CL1_RxMemoryFileItem != SYS_MEM_BUFFERING_RX_FILE)
		 /* &&	 (MEM_CountTotalPage(SYS_MEM_CL1_RX_FILE, CL1_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER) > 0) ) { @* 1ページ以上蓄積されていれば By S.Kawasaki 1996/08/10 */
		 &&	 (MEM_CountTotalPage(SYS_MEM_CL1_RX_FILE, CL1_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) ) { /* 1ページ以上蓄積されていれば */
			/* メモリ受信テーブル更新 */
			CL1_MemoryRxPrintPoint = &SYB_CL1_MemoryRxPrint[CL1_MemoryRxPrintWritePoint];
			CL1_MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
			CL1_MemoryRxPrintPoint->StorePage++;
		}
/*#if (PRO_PRINT_TYPE == LASER)*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		PRN_1PageReceived = 1;
		det_evt(EVT_PRN_RESTART);
		CMN_EnableInterrupt();	/**	割り込み許可	*/
/*#endif*/
		break;
	case MSG_FAXCOM_END:
		CL1_MemoryRxPrintPoint = &SYB_CL1_MemoryRxPrint[CL1_MemoryRxPrintWritePoint];
		if (CL1_MemoryRxPrintPoint->StorePage > 0) {
			CL1_MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT; /* By H.Y 1994/11/17 */
			if (CL1_MemoryRxPrintWritePoint + 1 >= SYS_MEMORY_RX_MAX) {
				i = 0;
			}
			else {
				i = CL1_MemoryRxPrintWritePoint + 1;
			}
			if ((CL1_MemoryRxPrintWritePoint != CL1_MemoryRxPrintReadPoint) ||
				(SYB_CL1_MemoryRxPrint[i].Status == SYS_MEMORY_RX_EMPTY)) {
					CL1_MemoryRxPrintWritePoint++;
					if (CL1_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
						CL1_MemoryRxPrintWritePoint = 0;
					}
			}
			else { /** 代行受信原稿が満杯 */
				/* Nothing to do */
			}
		}
		else  {
			CL1_MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			CL1_MemoryRxPrintPoint->StorePage = 0;
			CL1_MemoryRxPrintPoint->PrintPage = 1;
			CL1_MemoryRxPrintPoint->ErasePage = 1;
		}
/*#if (PRO_PRINT_TYPE == LASER)		@* By H.Y 1994/06/29 */
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		PRN_1PageReceived = 1;
		det_evt(EVT_PRN_RESTART);
		CMN_EnableInterrupt();	/**	割り込み許可	*/
/*#endif*/
		SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_FAXMODEM); /** CLASS1動作中解除 */

#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/18 K.Kawata */
		if ((CL1_ExtFunctionEnableFlag == 1) && (CL1_ExtTransmitErrorFlag == 1)) {
			if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 原稿があれば */
				MAN_ChangeItemLS2MP();
			}
		}
		CL1_ExtFunctionEnableFlag = 0;
		CL1_ExtLocalPrtRejectCnt = 0;
		CL1_ExtTransmitErrorFlag = 0;
#endif

		break;
	case MSG_FAXCOM_RX_START:
		/*	メモリ受信でかつFAXCOMタスクがPRINTERを使用中にしていたら、PRINTER を開放する Y.Suzuki*/
		if((SYS_CL1_RxMemoryFileItem != NULL) && (CMN_CheckFaxComPrinterEnable() == TRUE)) {/* メモリ受信かつ通信以外のタスクがプリンタを使用していない*/
			SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRINTER_BUSY);/* プリンタ開放する */
		}
		break;
	case MSG_FAXCOM_DISPLAY:
		/* ＬＣＤ表示切り替え用 */
		break;
	default:
		break;
	}
	if (cl1_message == MSG_FAXCOM_END) {
		if (tskno_pc_fax_complete == 0xFFFF) {
			cre_tsk(&tskno_pc_fax_complete , TSK_CMN_MAN_TIMER10MSTASK , &PC_FAX_CompleteMessage);
		}
	}
/* #endif */
}
#endif	/* #if (PRO_CLASS1 == ENABLE) */


#if (PRO_PC_PRINT == ENABLE)		/* By J.Miyazaki 1996/08/09 */
/*************************************************************************
	module		:[ＤＰＲＡＭリモート関数実行タスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/10/12]
	author		:[小谷正樹]
*************************************************************************/
void	MAN_FromDPR_RemoteFuncExecTask(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	MESSAGE_t	MainTaskMessage;

	MainTaskMessage.Item = FROM_MAIN;
  #if (0)	/* メインが処理を終了した時に同期用メッセージを送信すべき By J.Miyazaki 1996/09/14 */
  **			MainTaskMessage.Item = FROM_MAIN;
  **			MainTaskMessage.Message = MSG_EXIT;
  **			snd_msg(mbxno.DPR_RemoteFuncExecTask, &MainTaskMessage);
  #endif
	switch (message) {
		case MSG_DPR_PCPRINTJOBTRANSSTART:
			/* ＰＣデータ受信中表示の為 */
			/* ＰＣプリント受信テーブル再初期化 */
			/*SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;*/
			SYB_PcRxPrint.StorePage = 0;
			SYB_PcRxPrint.PrintPage = 1;
			SYB_PcRxPrint.ErasePage = 1;
			SYB_PcRxPrint.PrintEndPage = 0;
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] |= SYS_PC_PRINTDATA_RX;
			break;
		case MSG_DPR_PCPRINTPAGETRANSEND:
			/** ＰＣより１ページ以上受信した場合 */
			if (MEM_CountTotalPage(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				if (!(SYB_PcRxPrint.Status & SYS_PC_RX_JAMWAIT)) {	/* By J.Miyazaki 1997/03/28 */
					SYB_PcRxPrint.Status = SYS_PC_RX_STORE;
				}
				SYB_PcRxPrint.StorePage++;
			}
	/*#if (PRO_PRINT_TYPE == LASER)*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

			if ((SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {

				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				PRN_1PageReceived = 1;
				det_evt(EVT_PRN_RESTART);
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
#endif

	/*#endif*/
			/*JOBTRANSENDが来たときのみこれを落とすように変更。でないとＰＣ受信中表示が
			　プリントエラーになった時，表示されなくなるので，以下，１行コメント By J.Miyazaki 1996/12/11 */
			/*SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PC_PRINTDATA_RX;*/
			break;
		case MSG_DPR_PCPRINTJOBTRANSEND:
			/** 本コマンドがきた時に，プリントすべき原稿がある場合 */
			/* if (SYS_PcRxPrint.StorePage > 0) { 見方があきらかにおかしかった。By J.Miyazaki 1997/03/28 */
			if (MEM_CountTotalPage(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX /* > 0 By J.Miyazaki 1997/04/07 */) {
				SYB_PcRxPrint.Status = SYS_PC_RX_PRINT;
			}
			else  {
				SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
				SYB_PcRxPrint.StorePage = 0;
				SYB_PcRxPrint.PrintPage = 1;
				SYB_PcRxPrint.ErasePage = 1;
				SYB_PcRxPrint.PrintEndPage= 0;
			}
	/*#if (PRO_PRINT_TYPE == LASER)*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

			/*
			 * プリント原稿がＰＣプリント原稿の時のみ下記処理を行います。
			 * その他の受信原稿プリントに行ったらまずい。By J.Miyazaki 1997/02/10
			*/
			if ((SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
				/* プリントタスクが、次ページ受信のイベントを待っているために
				 * 解除してやる必要が有ります。
   	            */
				/*PRN_1PageReceived = 1; By J.Miyazaki 1996/11/01 */
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				PRN_1PageReceived = 1; /* 立てた方が安全　By 吉川　By J.Miyazaki 1997/02/12 */
				det_evt(EVT_PRN_RESTART);
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
	/*#endif*/
#endif

			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PC_PRINTDATA_RX;
			break;
		case MSG_DPR_PCPRINTPAGETRANSABORT:		/** 停止キーが押された場合。1997/02/03 */
			DPR_PCR_DataReceiving = 0;	/* 仮の変数追加。By J.Miyazaki 1997/01/10 */
			DPR_PCR_Timer = 0;			/* 仮の変数追加。By J.Miyazaki 1997/01/10 */
#if (PRO_PRINT_TYPE == LED)
			DPR_PCR_PrintTimer = 0;		/* By M.Tachibana 1998/01/27 */
#endif
			DPR_PCR_JamStatus = 0;				/* By J.Miyazaki 1997/03/29 */
			DPR_PCR_JamRecognizeReceive = 0;	/* By J.Miyazaki 1997/03/29 */
			/* By J.Miyazaki 1997/03/27 */
			SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;

			/* 1998/04/08 Y.Murata MEM_PC_BUG
			 * ＰＣのデータを受信中に強制アボートすると、MEM_TotalStoreBlockCounterがOxFFFFとなり
			 * 次からメモリ蓄積できないことがある。
			 * ＰＣの蓄積中に強制アボートした場合は、先に蓄積中のインデック及びＦＡＴをクリアするようにします。
			*/
			MEM_ClearStroingPCPrintFile();

			MEM_ClearDoc(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
	/*#if (PRO_PRINT_TYPE == LASER)*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

			/*
			 * プリント原稿がＰＣプリント原稿の時のみ下記処理を行います。
			 * その他の受信原稿プリントに行ったらまずい。By J.Miyazaki 1997/02/10
			*/
			if ((SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
				/* プリントタスクが、次ページ受信のイベントを待っているために
				 * 解除してやる必要が有ります。By J.Miyazaki 1996/11/15
   	            */
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				PRN_1PageReceived = 1; /* 立てた方が安全。By J.Miyazaki 1997/02/12 */
				det_evt(EVT_PRN_RESTART);
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
#endif

	/*#endif*/
			DPR_COM_Initialize(0xFFFF); /**プリンタボードを初期化 By J.Miyazaki 1997/01/27 */
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PC_PRINTDATA_RX;
			break;
		case MSG_DPR_PCRPRINTTESTSTART:
			if ((CMN_CheckPaperExist()			== TRUE)		/** 紙なし */
			&&	(CMN_CheckNoPrinterError() 		== TRUE)		/** プリンターエラーあり */
			&&	(CMN_CheckPrinterCoverClose() 	== TRUE)		/** プリンターカバーオープン */
			&&	(CMN_CheckBothCassetteClose() 	== TRUE)		/** どちらかのカセットが開いている */
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/**スキャナー使用中のリストプリントはできない。追加 M.Kotani 1997/10/16*/
			&&	(CMN_CheckScanEnable() == TRUE)
#endif
			&&	(CMN_CheckPrinting() 		  	== FALSE )) {	/** プリント中 */
			/*if (CMN_CheckPrintEnable(SYS_LIST_PRINT))	 { 1996/11/22 By J.Miyazaki */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンター使用中セット */
				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント実行中をセット */
				SYS_DocumentPrintPageNo = 1;
				cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0); /* リスト・プリント・タスク起動 */
				MainTaskMessage.Message = DPR_PCR_TESTPRINT_OK;
			}
			else {
				MainTaskMessage.Message = DPR_PCR_TESTPRINT_NG;
			}
			break;
		case MSG_DPR_PCRTIMEOUT:	/* By J.Miyazaki 1997/01/10 */
			DPR_PCR_DataReceiving = 0;	/* 仮の変数追加。By J.Miyazaki 1997/01/10 */
			DPR_PCR_Timer = 0;			/* 仮の変数追加。By J.Miyazaki 1997/01/10 */
#if (PRO_PRINT_TYPE == LED)
			DPR_PCR_PrintTimer = 0;		/* By M.Tachibana 1998/01/27 */
#endif
			DPR_PCR_JamStatus = 0;				/* By J.Miyazaki 1997/03/29 */
			DPR_PCR_JamRecognizeReceive = 0;	/* By J.Miyazaki 1997/03/29 */
			/* By J.Miyazaki 1997/03/29 */
			SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
			MEM_ClearDoc(SYS_MEM_PC_RX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
	/*#if (PRO_PRINT_TYPE == LASER)*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

			/*
			 * プリント原稿がＰＣプリント原稿の時のみ下記処理を行います。
			 * その他の受信原稿プリントに行ったらまずい。By J.Miyazaki 1997/02/10
			*/
			if ((SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
				/* プリントタスクが、次ページ受信のイベントを待っているために
			 	 * 解除してやる必要が有ります。By J.Miyazaki 1996/11/15
            	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				PRN_1PageReceived = 1; /* 立てた方が安全 By 吉川　By J.Miyazaki 1996/02/12 */
				det_evt(EVT_PRN_RESTART);
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
#endif

	/*#endif*/
			DPR_COM_Initialize(0xFFFF); /**最終スレーブボード(プリンタボードを初期化）*/
			SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE] &= ~SYS_PC_PRINTDATA_RX;
			break;
		default:
			break;
	}

	if (message != MSG_DPR_PCRPRINTTESTSTART) {
		MainTaskMessage.Message = MSG_EXIT;
	}

	MainTaskMessage.Item = FROM_MAIN;
	if (message == MSG_DPR_PCRTIMEOUT) {
  		snd_msg(mbxno.MAN_TimerTask, &MainTaskMessage);
	}
	/* ＰＣプリント停止受付 By J.Miyazaki 1997/02/03 */
	else if (message == MSG_DPR_PCPRINTPAGETRANSABORT) {
		snd_msg(mbxno.OPR_MAN_MessageTask, &MainTaskMessage);
	}
	else {
		/* ２８．８ボードとＰＣプリンターボードが同時に動いたとき
		** メッセージを横取りしてしまうので、同期のとれるFCM_Option
		** をメイルボックスに利用する
		** BY H.H 1997/04/10
		*/
  		/* snd_msg(mbxno.DPR_RemoteFuncExecTask, &MainTaskMessage); */
  		snd_msg(mbxno.FCM_Option, &MainTaskMessage); /* 1997/04/10 BY H.H */
	}
}
#endif	/* #if (PRO_PC_PRINT == ENABLE) */


#if (PRO_ROTATE == ENABLE)
/*************************************************************************
	module		:[回転受信タスクからのメッセージ処理]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/03/31]
	author		:[小谷正樹]
*************************************************************************/
void MAN_FromROT_Task(
	UWORD	item,
	UWORD	message,
	UWORD	sub_message1,
	UWORD	sub_message2)
{
	struct MEM_IndexData_t		MemoryRxErasePoint;
	UWORD	rot_item;
	UWORD	rot_message;
	UWORD	rot_sub_message1;
	UWORD	rot_sub_message2;

	rot_item = item;
	rot_message = message;
	rot_sub_message1 = sub_message1;
	rot_sub_message2 = sub_message2;

	if (tskno_ROT_Task != 0xffff) {
		del_tsk(&tskno_ROT_Task); /** 回転受信・タスク停止 */
	}
	MAN_RotateIsBusy = 0;
	switch (rot_message) {
	case MSG_ROT_COMPLETE:			/* 1 連続回転実行時に全ページ正常に回転できた */
		switch (SYS_DocumentRotateClass) {	/** 回転クラス */
		case SYS_PRINT_CLASS:	/** １ページ回転処理の終了 */
			switch (SYS_DocumentRotateItem) { /** 回転原稿の種別 */
			case SYS_MEM_RX_FILE: /** メモリ受信原稿 */
				ROT_FixIndex();
 #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
				MemoryRxRotatePoint->RotatePage++; /** メモリ受信原稿回転ページ数を加算 */
 #else
				if (CHK_UNI_RxDocReversePrint() && (MemoryRxRotatePoint->Status == SYS_MEMORY_RX_PRINT)) {
					MemoryRxRotatePoint->RotatePage--; /** メモリ受信原稿回転ページ数を減算 */
				}
				else {
					MemoryRxRotatePoint->RotatePage++; /** メモリ受信原稿回転ページ数を加算 */
				}
 #endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

				if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
				 && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
					PRN_1PageReceived = 1;
					det_evt(EVT_PRN_RESTART);
				}
#endif

				break;
			default: /** その他の原稿 */
				break;
			}
			break;
		default: /** ここに来たらバグ */
			break;
		}
		break;
	case MSG_ROT_ERROR:				/* 0 回転基盤のメモリオーバー回転エラー */
	case MSG_ROT_NO_DOCUMENT:		/* 2 回転原稿なし終了 */
	case MSG_ROT_CANCEL:			/* 3 回転不要原稿 */
	case MSG_ROT_MEMORY_OVER:		/* 4 回転中にメモリオーバー */
	case MSG_ROT_STOP:				/* 5 何らかの要因で強制中断した */
	case MSG_ROT_BUSY:				/* 6 回転処理中のため回転できず */
	case MSG_ROT_COMPOUND:			/* 7 ページ合成するため、回転せず */
		switch (SYS_DocumentRotateClass) {	/** 回転クラス */
		case SYS_PRINT_CLASS:	/** １ページ回転処理の終了 */
			switch (SYS_DocumentRotateItem) { /** 回転原稿の種類 */
			case SYS_MEM_RX_FILE: /** メモリ受信原稿 */
 #if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
				MemoryRxRotatePoint->RotatePage++; /** メモリ受信原稿回転ページ数を加算 */

				/* 回転オプション有りでページ合成を行う T.Nose 1998/6/11 */
				if (rot_message == MSG_ROT_COMPOUND) {
					/* ページ合成実行の場合、2ページ分をプリントアウトするのでさらに加算 */
					MemoryRxRotatePoint->RotatePage++;
				}
 #else
				if (CHK_UNI_RxDocReversePrint() && (MemoryRxRotatePoint->Status == SYS_MEMORY_RX_PRINT)) {
					MemoryRxRotatePoint->RotatePage--; /** メモリ受信原稿回転ページ数を減算 */
					/* 回転オプション有りでページ合成を行う T.Nose 1998/6/11 */
					if (rot_message == MSG_ROT_COMPOUND) {
						/* ページ合成実行の場合、2ページ分をプリントアウトするのでさらに減算 */
						MemoryRxRotatePoint->RotatePage--;
					}
				}
				else {
					MemoryRxRotatePoint->RotatePage++; /** メモリ受信原稿回転ページ数を加算 */
					/* 回転オプション有りでページ合成を行う T.Nose 1998/6/11 */
					if (rot_message == MSG_ROT_COMPOUND) {
						/* ページ合成実行の場合、2ページ分をプリントアウトするのでさらに加算 */
						MemoryRxRotatePoint->RotatePage++;
					}
				}
 #endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

				if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
				 && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT)) {
					PRN_1PageReceived = 1;
					det_evt(EVT_PRN_RESTART);
				}
#endif

				break;
			default: /** その他の原稿 */
				break;
			}
			break;
		default: /** ここに来たらバグ */
			break;
		}
		break;
	default:
		break;
	}
}
#endif


#if (PRO_MULTI_LINE == ENABLE)
/*************************************************************************
	module		:[マルチ回線時のメッセージ処理]
	function	:[
		1.オプションモデムボードからのメッセージ処理を行う
		2.SubMessage4はスタックナバーを示す。
			0:ﾎｽﾄ
			1:ｵﾌﾟｼｮﾝの１番目
			2:ｵﾌﾟｼｮﾝの２番目
			3:ｵﾌﾟｼｮﾝの３番目
				・
				・
			7:ｵﾌﾟｼｮﾝの７番目

		  実際のＤＰＲの示すスタックナンバーは
			0:ｵﾌﾟｼｮﾝの１番目
			1:ｵﾌﾟｼｮﾝの２番目
		  となるため、判別しやすいように上記のようにした
		#--------------------------------------------------------------#
		# ホストから何番目のオプションボードに送信するかの指定は要注意 #
		#--------------------------------------------------------------#
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
void	MAN_FromFaxcomOption(
	UWORD	Item,
	UWORD	Message,
	UWORD	SubMessage1,
	UWORD	SubMessage2,
	UWORD	SubMessage3,
	UWORD	SubMessage4)
{
	MESSAGE_t	MainTaskMessage;
	MESSAGE_t	*MessageControl;
	UWORD	memory_rx_num;
	UWORD	line_number;
	struct	SYS_ExecQueueData_t *exec_point;
	struct GenerateRingData_t ring_data;
	UWORD	debug_data;
	UBYTE	i;

	line_number = SubMessage4;	/* 回線番号 */
	MainTaskMessage.Item = FROM_MAIN;
	MainTaskMessage.Message = MSG_EXIT;
	snd_msg(mbxno.FCM_Option, &MainTaskMessage);
	switch (Message) {
		case MSG_OPT_FAXCOM_CLOSE_ERROR:
			SYS_MachineStatus[SYS_SCANNER_STATUS] |= SYS_SCANNER_FEED_ERROR; /** スキャナー・フィード・エラーをセット */
			break;
		case MSG_OPT_FAXCOM_DISPLAY:
			break;
		case MSG_OPT_RX_PRINT_PAGE: /* 通常のメモリ受信原稿の時だけこのメッセージを受信、１ページ受信毎にメモリ受信テーブルを更新 */

			for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
				if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
				|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)) {
#else
				if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
				|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)
				|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE_PRINT)) {
#endif

#if (PRO_LINENUMBER == TWICE_LINE)
					/* ＱＡＴ不具合
					** 拡張回線で受信ができない不具合修正
					** 拡張回線の処理が抜けていた（ "& 0x7f")
					** by O.Kimoto 1998/04/13
					*/
					if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (UBYTE)line_number) {
						break;
					}
#else
					if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (UBYTE)line_number) {
						break;
					}
#endif
				}
			}

			if (memory_rx_num < SYS_MEMORY_RX_MAX) {
				if (MEM_CountTotalPage(SYS_MEM_RX_FILE, memory_rx_num, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 1ページ以上蓄積されていれば */
					/* メモリ受信テーブル更新 */
					MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
#else
					if (CHK_UNI_RxDocReversePrint()) {
						if (MemoryRxPrintPoint->Status != SYS_MEMORY_RX_STORE_PRINT) {
							if (CMN_CheckOptionFastPrintStart()) {
								MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE_PRINT;
							}
							else {
								MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
							}
						}
					}
					else {
						MemoryRxPrintPoint->Status = SYS_MEMORY_RX_STORE;
					}
#endif
					MemoryRxPrintPoint->StorePage++;
					if (MemoryRxPrintPoint->StorePage == 1) {
						MemoryRxPrintPoint->ReceiveTime = SYB_CurrentFaxReceiveTime;
						/*
						** １ページ完了時間において、他の受信で同じ時刻がある場合、プラス１秒加算する処理
						** 回転オプションがある場合で、同時刻の受信があると、プリントできなくなることがある
						** 1998/05/20 by T.Soneoka */
						if (MAN_CheckReceiveTime(MemoryRxPrintPoint->ReceiveTime, memory_rx_num)) {
							MemoryRxPrintPoint->ReceiveTime++;
						}
					}
					/*----------------------------------------------------------*/
					/* セキュリティ受信機能追加		1996/04/27 Eguchi			*/
					/*----------------------------------------------------------*/
					if (SYB_SecurityRxModeFlag == 1) {/** セキュリティ受信モード中 */
						if ((MemoryRxPrintPoint->StorePage == 1) /*２枚目以降にプロテクトＯＮにしても無効にするため */
						&&	(MemoryRxPrintPoint->Protect == SYS_PROTECT_OFF)) {
							MemoryRxPrintPoint->Protect = SYS_PROTECT_ON;
						}
					}

/*#if (PRO_PRINT_TYPE == LASER)*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

					/* 1997/02/10 Y.Murata
					 * プリンタが今、受信している原稿をプリントしている場合のみイベントを発行します
					*/
					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
						if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
						&& (SYS_DocumentPrintNo == memory_rx_num)) {

							CMN_DisableInterrupt();	/**	割り込み禁止	*/
							PRN_1PageReceived = 1;
							det_evt(EVT_PRN_RESTART);
							CMN_EnableInterrupt();	/**	割り込み許可	*/
						}
					}
#endif

/*#endif*/
				}
			}
#if 0	/* 1997/02/10 Y.Murata */
//#if (PRO_PRINT_TYPE == LASER)		/* By H.Y 1994/06/29 */
//			PRN_1PageReceived = 1;
//			det_evt(EVT_PRN_RESTART);
//#endif
#endif
			break;
		case MSG_OPT_FAXCOM_END:
		case MSG_OPT_FAXCOM_END_OFF_HOOK:
		case MSG_OPT_FAXCOM_ANS_CHANGE_KAMO:

			MAN_OptionModemLast((UBYTE)line_number);
			if (SYS_Opt[line_number].SYS_FaxComType == SYS_COMMAND_EXECUTE) {
				exec_point = &SYB_ExecQueue[SYS_Opt[line_number].SYS_CurrentExecQueueNo];
			}
			else {
				exec_point = 0x00;
			}

	#if (PRO_CONTINUOUS_POLLING == ENABLE)/* 連続ポーリング機能追加 */
			/* 連続ポーリングコマンド実行終了であればキューを無条件でクリア */
			/* 本当にこの場所でいいのか */
			if (SYS_Opt[line_number].SYS_FaxComType == SYS_COMMAND_EXECUTE) {
				if (exec_point->Kind == SYS_CONTINUOUS_POLLING) {
					exec_point->Status = SYS_EXEC_ERASED; /* 無理矢理消去 */
					DeleteContinuousPollingCommand();
					CommandErased[line_number] = 0;		/* 1997/10/29 COMMAND_DEL */
				}
			}
	#endif

			switch (SubMessage1) { /** 通信終了状況を調べる */
				case OPT_FAXCOM_OK:
/* T.B.D */
					if (tskno_faxcom_complete == 0xffff) {
						cre_tsk(&tskno_faxcom_complete, TSK_CMN_MAN_TIMER10MSTASK, &FaxcomCompleteMessage);
						FaxComCompleteDisplaySign = SYS_Opt[line_number].FaxComTXorRX_Sign;

					}

					break;
				case OPT_FAXCOM_REDIAL:
					break;
				case OPT_FAXCOM_ERROR:
					/*
					** ＵＳＡ仕様のみ通信エラー発生後のエラーは、チェックメッセージ印字終了と同時に
					** 消去する仕様とします。F-82/92で採用済み。 By S.Kawasaki 1996/04/26
					*/
					if (CHK_UNI_ClearCommunicationError()) {
						if (SYS_Opt[line_number].SYS_FaxComType == SYS_AUTO_CALLED) {
							/** 何もしない */
						}
						else {
							SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_FAXCOM; /** 通信エラーをセット */
							/* 通信エラーを通信毎にクリアする場合、この処理は不要になるはず　TBD 1995/12/06 Eguchi*/
							BackUpStatusError &= ~SYS_ERROR_FAXCOM;	/* 94.11.16 by T.Nose */
						}
					}
					else {
						SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_FAXCOM; /** 通信エラーをセット */
						/* 通信エラーを通信毎にクリアする場合、この処理は不要になるはず　TBD 1995/12/06 Eguchi*/
						BackUpStatusError &= ~SYS_ERROR_FAXCOM;	/* 94.11.16 by T.Nose */
					}

					break;
			}
			for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
				if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
				|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)) {
#else
				if ((SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING)
				|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE)
				|| (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_STORE_PRINT)) {
#endif

#if (PRO_LINENUMBER == TWICE_LINE)
					/* ＱＡＴ不具合
					** 拡張回線で受信ができない不具合修正
					** 拡張回線の処理が抜けていた（ "& 0x7f")
					** by O.Kimoto 1998/04/13
					*/
					if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (UBYTE)line_number) {
						break;
					}
#else
					if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (UBYTE)line_number) {
						break;
					}
#endif
				}
			}
			if (memory_rx_num < SYS_MEMORY_RX_MAX) {
				MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];
				if (MemoryRxPrintPoint->StorePage > 0) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT; /* By H.Y 1994/11/17 */
#else
					if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_STORE_PRINT) {
						MemoryRxPrintPoint->Status = SYS_MEMORY_RX_FAST_PRINT;
					}
					else {
						MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT;
						if (CHK_UNI_RxDocReversePrint()) {
							MemoryRxPrintPoint->PrintPage = MemoryRxPrintPoint->StorePage;
							MemoryRxPrintPoint->RotatePage = MemoryRxPrintPoint->StorePage;
						}
					}
#endif
/*#if (PRO_PRINT_TYPE == LASER)*/

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

					/* 1997/02/10 Y.Murata
					 * プリンタが今、受信している原稿をプリントしている場合のみイベントを発行します
					*/
					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
						if ((SYS_DocumentPrintItem == SYS_MEM_RX_FILE)
						&& (SYS_DocumentPrintNo == memory_rx_num)) {

							CMN_DisableInterrupt();	/**	割り込み禁止	*/
							PRN_1PageReceived = 1;
							det_evt(EVT_PRN_RESTART);
							CMN_EnableInterrupt();	/**	割り込み許可	*/
						}
					}
#endif

/*#endif*/
				}
				else  {
					MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
					MemoryRxPrintPoint->StorePage = 0;
					MemoryRxPrintPoint->RotatePage = 1;	/* Add By M.Tachibana 1998/05/22 */
					MemoryRxPrintPoint->PrintPage = 1;
					MemoryRxPrintPoint->ErasePage = 1;
					MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /**受信原稿プリントプロテクト初期化 */
					MemoryRxPrintPoint->StackNumber = 0;
					MemoryRxPrintPoint->ReceiveTime = 0;
					MemoryRxPrintPoint->JournalPoint = 0;
				}
			}
#if 0	/* 1997/02/10 Y.Murata */
//#if (PRO_PRINT_TYPE == LASER)		/* By H.Y 1994/06/29 */
//			PRN_1PageReceived = 1;
//			det_evt(EVT_PRN_RESTART);
//#endif
#endif
			SYS_MltVariableTimer[line_number] = 5; /* タイマー・タスクへ５秒タイマー起動 */
			debug_data = SYS_Opt[line_number].SYS_VoiceCallAccepted;	/* for debug */

			if ((!(ExistOrangeModem())) && (line_number == 1)) {
				if ((SYS_Opt[line_number].SYS_VoiceCallAccepted) || (SYS_Opt[line_number].SYS_TensouJushinFlag)) { /* 通信終了時に会話予約が成立していれば */
					HungUpCheck = 0; /* 通信終了後の受話器上がりは検出しない */
				}
				else {
					if ((Message == MSG_OPT_FAXCOM_END_OFF_HOOK) ||
						(Message == MSG_OPT_FAXCOM_ANS_CHANGE_KAMO)) {
						HungUpCheck = 0; /* 通信終了後の受話器上がりは検出しない */
					}
					else {
						HungUpCheck = 1; /* 通信終了後の受話器上がりを検出する */
					}
				}
			}
			/*----------------------------------------------------*/
			/* 会話予約のクリア処理								  */
			/* 会話予約の表示／ＬＥＤを消すならここでやって下さい */
			/*----------------------------------------------------*/
			if (SYS_Opt[line_number].SYS_VoiceCallAccepted) { /* 通信終了時に会話予約が成立していれば */
				SYS_VoiceSwitch = 0;	/* 会話予約のリセット */
			}
			else {
				if (!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM)) {	/* 内臓モデムがない */
					for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
						if (CHK_OptionLineExist((UBYTE)i)) {
							if (((UBYTE)line_number) == i) {
								SYS_VoiceSwitch = 0;	/* 会話予約のリセット */
							}
							break;
						}
					}
				}
			}
			/* マシーンステータスの管理 */
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_LINE_BUSY;
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_REAL_LINE_BUSY;

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** /* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** ** いう不具合が発生したので
** ** By O.Kimoto 1997/07/07
** */
** #if (PRO_MULTI_LINE == ENABLE)
** 			CMN_ReleasePollingDocRight(line_number);
** #endif
#else
			CMN_ReleasePollingDocRight(line_number);
#endif


			if (((SYS_Opt[line_number].SYS_FaxComType == SYS_COMMAND_EXECUTE) &&
				(SYS_Opt[line_number].SYS_FaxComTxType == SYS_SCANNER_TX) &&
				(!((exec_point->Status == SYS_EXEC_WAITING) || (exec_point->Status == SYS_EXEC_FORWARD_WAITING))))
				|| (SYS_Opt[line_number].SYS_FaxComType == SYS_MANUAL_TX)) { /* 実行終了した通信がスキャナー送信のコマンドタイプで、リダイアルにならなかった時と */
														/* 実行終了した通信が手動送信の時 */
				CMN_ResetMemoyFeederTx();
				CMN_ResetStamp();
				CMN_ResetPrimaryMode(); /* 読み取りモード、濃度をリセット */
				CMN_ResetPrimaryContrast(); /* 読み取りモード、濃度をリセット */
				CMN_ResetConfirmationReport(); /* By S.K Sep.19,1994 */
#if (PRO_RED_SCAN == ENABLE)	/* 朱色読み取り 2002/03/05 T.Takagi */
				CMN_ResetRedScan();
#endif
				if (!(SYS_MachineStatus[SYS_SENSOR_STATUS] & (SYS_SENSOR_DS1_ON+SYS_SENSOR_DS2_ON))) { /* スキャナーに原稿がなければ */
					CMN_ResetPrimaryDocumentSize(); /* 優先読み取りサイズの処理 */
				}
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* 移動 1994/06/01 Y.Murata */ /* スキャナー使用中をクリア */
				if (!(SYS_MachineStatus[SYS_RESOURCE_STATUS]&SYS_SCANNER_BUSY) &&
					!(SYS_MachineStatus[SYS_MACHINE_STATUS]&(SYS_FEED_IN+SYS_FEED_OUT))) { /* 7/29/1994 */
					SCN_Init();
					if(( tskno_SCN_GearBackLashTask	  == 0xffff )	/* '96,03,13 By N.S. */
					&& ( SYS_SCN_MotorReverseControal == 0		)){	/* '96,03,29 By N.S. 1line insert for ﾓｰﾀｰ反転 0:正転 1:反転*/
						SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;	/* '96,03,13 By N.S. */
						cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
					}
					/*	SCN_GearBackLashTaskの二重Cleateと原稿繰込動作が起動されない状態の防止 7 lines Insert By N.S. 1996/05/07 */
					else{
						if( SYS_SCN_MotorReverseControal == 0 ){	/* ﾓｰﾀｰ反転 0:正転 1:反転*/
							del_tsk(&tskno_SCN_GearBackLashTask);
							SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_SCANNER_BUSY;
							cre_tsk(&tskno_SCN_GearBackLashTask, TSK_SCN_GEARBACKLASHTASK, 0 );
						}
					}
				}
			}
			else { /* Jan.30,1995 For Debug By S.K */
				/*DebugScan = 0;*/
			}
			if (((SYS_Opt[line_number].SYS_FaxComType == SYS_COMMAND_EXECUTE) && (SYS_Opt[line_number].SYS_FaxComTxType == SYS_SCANNER_TX))
				|| (SYS_Opt[line_number].SYS_FaxComType == SYS_MANUAL_TX)) { /* 実行終了した通信がスキャナー送信のコマンドタイプで、リダイアルにならなかった時と */
														/* 実行終了した通信が手動送信の時 */
				SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY); /* 移動 1994/06/01 Y.Murata */ /* スキャナー使用中をクリア */
			}
			/* 自動のｽｷｬﾅ送信でﾘﾀﾞｲｱﾙになった時に原稿が無ければｽｷｬﾅｺﾏﾝﾄﾞを消去	1994/08/27 Y.Murata */
			/* そうしないとコールしている時に原稿をぬかれたら送る原稿も無いのに予約になってしまうための対応 */
			if ((SYS_Opt[line_number].SYS_FaxComType == SYS_COMMAND_EXECUTE) &&
				(CheckScannerCommand(exec_point->Number.Command)) &&
				((exec_point->Status == SYS_EXEC_WAITING) || (exec_point->Status == SYS_EXEC_FORWARD_WAITING)) &&
				(!(SYS_MachineStatus[SYS_SENSOR_STATUS] & (SYS_SENSOR_DS1_ON+SYS_SENSOR_DS2_ON)))) {
				DeleteScannerCommand();
			}

			if (SYS_Opt[line_number].SYS_FaxComType == SYS_COMMAND_EXECUTE) {
				if (CommandErased[line_number]) { /* コマンド消去がオペレーションより実行されていれば */
					CommandErased[line_number] = 0;
					MltDeleteComFileExecQueueFile((UBYTE)line_number); /* コマンドファイル、ExecQueueを消去 */
				}
			}

			if (Message == MSG_OPT_FAXCOM_END) {
				/*受信完了アラーム鳴動処理 1996/08/13 Eguchi */
				if ((CHK_AudibleAlarmON() && !SYB_SecurityRxModeFlag)
				&& 	((SubMessage1 == FAXCOM_OK) || (SubMessage1 == FAXCOM_ERROR && SYS_Opt[line_number].SYS_RxTotalPage > 0))
				&&	(SYS_Opt[line_number].SYS_FaxComType == SYS_AUTO_CALLED || SYS_Opt[line_number].SYS_FaxComType == SYS_MANUAL_RX)
				&&	(SYS_Opt[line_number].FaxComTXorRX_Sign == RX_COM_MODE)
				&&	(!SYS_AudibleAlarmStatus)) {
					SYS_AudibleAlarmStatus |= 0x01; /* 鳴動要求セット */
				}
				SYS_MltVariableTimer[line_number] = 5;			/* 1994/10/15 Y.Murata */
			}
			else if (Message == MSG_OPT_FAXCOM_END_OFF_HOOK) {
				/* マシーンステータスの管理 */
				SYS_OptionLineStatus[line_number] |= SYS_OPTION_TELEPHONE_UES;

				/* 1997/02/15 Y.Murata
				 *
				*/
				if((!(ExistOrangeModem())) && (line_number == 1)){
					SYS_RxDetectFlag = 1;
					if (SubMessage2 == MSG_FCOM_TEL1_OH) {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
					}
					else if (SubMessage2 == MSG_FCOM_TEL2_OH) {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL2_OFF_HOOK);
					}
					else if (SubMessage2 == MSG_FCOM_HOOK_KEY_OH) {
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_HOOK_KEY_OFF_HOOK);
					}
					SYS_MachineStatus[SYS_MACHINE_STATUS] |= (SYS_TELEPHONE);

		 /* SYS_TELEPHONEをセット後にメッセージ送信しなければならない。勝手に移動禁止*/
					MainTaskMessage.Item = FROM_MAIN;
					MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
					snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);	/* Jan.18,1995 By T.Nose */
					rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);		/* Jan.18,1995 By T.Nose */
				}
			}
			else if (Message == MSG_OPT_FAXCOM_ANS_CHANGE_KAMO) {
				/* Nothing */
			}

			if (SubMessage3 == MSG_OPT_FCOM_HAVE_QUE) {
				SYS_OptionLineStatus[line_number] |= SYS_OPTION_LINE_BUSY;
			}

			/* 1998/04/01 Y.Murata -> 1998/04/13 F150Jより移植
			 * セキュリテイ受信メモリオーバーのチェック
			*/
			if ((SYS_Opt[line_number].FaxComResult & 0x0FFF) == (RECEIVEERROR|0x44)) {	/* R.4.4なら */
				/* セキュリティー受信時のメモリオーバーのチェックメッセージプリント要求 */
				SetSecurityRxChkMsgPrint();
			}

			/* TBD さつき/もみじは問題ないが,ラベンダーのバッファリング受信の時は注意！！ Y.Murata */
			/*	プリンタ受信でかつFAXCOMタスクがPRINTERを使用中にしていたら、PRINTER を開放する 1994/05/30 Y.Murata*/

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
			i = (0x01 << (UBYTE)line_number);
			if (SYS_QucikTxStopStatus & (UWORD)i) {
				SYS_QucikTxStopStatus = 0;
			}
#endif
			break;
		case MSG_OPT_FAXCOM_TX_START: /* Nov.7,1994 */
			/*	ポーリング送信であることが判明すれば、着信時に確保したプリンターを開放する。現状椛のみ通るパス。 By S.K Nov.7,1994 */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1997/01/30 */
** 			if (SYS_Opt[line_number].TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE) { /** 検索ポーリング送信の場合 */
** 				CMN_ReleasePollingDocRight(line_number);
** 			}
** #endif
#else
			if ((SYS_Opt[line_number].TxMemoryFileItem == SYS_MEM_DB_POLLING_FILE)
				|| (SYS_Opt[line_number].TxMemoryFileItem == SYS_MEM_SUB_BULLETIN_FILE)) { /** 検索ポーリング送信の場合 */
				CMN_ReleasePollingDocRight(line_number);
			}
#endif

			break;
		case MSG_OPT_FAXCOM_RX_START:
			/*	メモリ受信でかつFAXCOMタスクがPRINTERを使用中にしていたら、PRINTER を開放する Y.Suzuki*/


#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/13 */
** 			CMN_ReleasePollingDocRight(line_number);
** #endif
#else
			CMN_ReleasePollingDocRight(line_number);
#endif

			break;
		case MSG_OPT_BUFFERING_PRINT_START:
			break;
		/* プリンタ受信からプリンタエラーで代行受信に移行したときの処理 */	/* 1994/07/20 Y.Murata */
		case MSG_OPT_FAXCOM_PRINTER_ERROR:
			break;
		case MSG_OPT_FAXCOM_OPTION_REC_REQ:
			/* if (CMN_CheckMultiLineReceiveNumber((UBYTE)line_number, AUTO_RECEIVE) < SYS_MEMORY_RX_MAX) { 1997/11/20  By T.Yamaguchi */
			if (MAN_CheckMultiLineReceiveEnable((UBYTE)line_number, AUTO_RECEIVE) < SYS_MEMORY_RX_MAX) {
				MAN_OptionModemStart((UBYTE)line_number);
				/* マシーンステータスの管理 */
				SYS_OptionLineStatus[line_number] |= SYS_OPTION_LINE_BUSY;
				SYS_Opt[line_number].SYS_FaxComType = SYS_AUTO_CALLED;
				SYS_Opt[line_number].SYS_FaxComTxType = 0;

				CMN_GetPollingDocRight(line_number);	/* Add By O.Kimoto 1997/01/13 */

				/* 個別属性セーブ 1997/01/27 Y.Murata */
				SYS_FaxComAbility0[line_number] = SYS_MemorySwitch[10];
				SYS_FaxComAbility1[line_number] = SYS_MemorySwitch[11];
				SYS_FaxComAbility2[line_number] = SYS_MemorySwitch[12];
				SYS_FaxComAbility3[line_number] = SYS_MemorySwitch[13];
				SYS_PreLineBusyCheckStatus[line_number] = 0;
				DPR_AutoCalled(line_number - 1);
			}
			else {
				SYS_PreLineBusyCheckStatus[line_number] = 1;
			}
			break;
		case MSG_OPT_DETECT_CI:
			/* マシーンステータスの管理 */
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_PRE_LINE_BUSY;
			SYS_PreLineBusyCheckStatus[line_number] = 0;
			break;
		case MSG_OPT_DETECT_CI_TIMEUP:
			/* マシーンステータスの管理 */
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;
			SYS_PreLineBusyCheckStatus[line_number] = 0;
			SYS_MltVariableTimer[line_number] = 5; /* タイマー・タスクへ５秒タイマー起動 */
			break;
		case MSG_OPT_FAXCOM_END_TIME:
			SYS_OptionModemTime[line_number].EndTime = SYB_CurrentTime;
			break;
		case MSG_OPT_FAXCOM_SET_JOURNAL:
			if (SYS_JournalRequest[line_number] == SYS_JOURNAL_REQ_NOTHING) {
				SYS_JournalRequest[line_number] = SYS_JOURNAL_REQ;
			}
			else {
				/* ありえない */
				outp((unsigned long)0,(unsigned char)0);		/* WriteProtectError for ICE */	/**オプションボードをリセットしてください*/
				SYS_JournalRequest[line_number] = SYS_JOURNAL_REQ;
			}
			break;
		case MSG_OPT_FAXCOM_START_TIME:
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_REAL_LINE_BUSY;
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;
			SYS_OptionModemTime[line_number].StartTime = SYB_CurrentTime;
			break;
		case MSG_OPT_FAXCOM_TEL1_OFF_HOOK:
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_TELEPHONE_UES;

			if((!(ExistOrangeModem())) && (line_number == 1)){
				if (HungUpCheck) {	/** ハング・アップ・チェックの場合 */
					 /** ハング・アップ・エラーをセット */
					SYS_MachineStatus[SYS_ERROR_STATUS] |= SYS_ERROR_HUNG_UP;
				}

				SYB_RedialBufWritePointer = 0;

				SYS_MachineStatus[SYS_RESOURCE_STATUS]    &= ~(SYS_PRE_LINE_BUSY);
				SYS_MachineStatus[SYS_RESOURCE_STATUS]    |= SYS_LINE_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS] 	  |= (SYS_TELEPHONE);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= (SYS_TEL1_OFF_HOOK);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_HOOK_KEY_OFF_HOOK);
				if( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_LINE_HOLD ){
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);
				}

				/* 1997/05/29 Y.Murata
				 * 電話器をあげられたら、本当はモニタスピーカーをＯＦＦにせなあかんけど
				 * Ｆ１５０は本体のスピーカをＯＮにせなあかん。そうせな電話器をあげてのＤＴＭＦ発呼で音でない
				 *MonitorSpeakerOff();	@* 1997/02/28 Y.Murata *@
				*/
				MonitorSpeakerOn();

				/* 1997/02/13 Y.Murata
				 * オペレーションタスクに電話関連の事象が変化したことを通知します
				*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
			}
			break;
		case MSG_OPT_FAXCOM_ON_HOOK_EXIT:
			SYS_OptionLineStatus[line_number] &= ~(SYS_OPTION_TELEPHONE_UES);
			SYS_MltVariableTimer[line_number] = 5; /* タイマー・タスクへ５秒タイマー起動 */
			if((!(ExistOrangeModem())) && (line_number == 1)){
#if 0
				if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_HUNG_UP) {	/** ハング・アップ・エラ－の場合 */
					HungUpCheck = 0; /* ハング・アップ・チェック・クリア */
					SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP);
				}

				NCU_DetectOnHookExit();
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
				SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP);
				if (!(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_PRE_LINE_BUSY);
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~SYS_LINE_BUSY;
				}

				MonitorSpeakerOff();	/* 1997/02/28 Y.Murata */

				/* 1997/02/13 Y.Murata
				 * オペレーションタスクに電話関連の事象が変化したことを通知します
				*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
#endif
			}
			break;
		case MSG_OPT_FAXCOM_ON_HOOK_CONT:
			if((!(ExistOrangeModem())) && (line_number == 1)){
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK);

				MonitorSpeakerOff();	/* 1997/02/28 Y.Murata */

				/* 1997/02/13 Y.Murata
				 * オペレーションタスクに電話関連の事象が変化したことを通知します
				*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
			}
			break;
		case MSG_OPT_FAXCOM_INPUT_HOOK_KEY:
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;	/* 1997/02/18 Y.Murata */
			SYS_OptionLineStatus[line_number] |= SYS_OPTION_TELEPHONE_UES;	/* 1997/02/18 Y.Murata */
			if((!(ExistOrangeModem())) && (line_number == 1)){
#if 0
				NCU_DetectHookKeyInputExit();
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |=   SYS_HOOK_KEY_OFF_HOOK;
				SYS_MachineStatus[SYS_RESOURCE_STATUS]	  &= ~(SYS_PRE_LINE_BUSY);
				SYS_MachineStatus[SYS_RESOURCE_STATUS]	  |=   SYS_LINE_BUSY;
				SYS_MachineStatus[SYS_MACHINE_STATUS]	  |=  (SYS_TELEPHONE);
				if (SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_DIAL_IN) {
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~SYS_DIAL_IN;
				}

				MonitorSpeakerOn();	/* 1997/02/28 Y.Murata */

				SYB_RedialBufWritePointer = 0;

				/* 1997/02/13 Y.Murata
				 * オペレーションタスクに電話関連の事象が変化したことを通知します
				*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
#endif
			}
			break;
		case MSG_OPT_FAXCOM_INPUT_HOLD_KEY:
			if((!(ExistOrangeModem())) && (line_number == 1)){
#if 0
				NCU_DetectHoldKeyInputExit();
				if( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_LINE_HOLD ){
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_LINE_HOLD);
					if( SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] & SYS_INTER_COM ){
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_INTER_COM);
						SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_TRIPLE_COM;
					}
				}
				else{
					SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] |= SYS_LINE_HOLD;
				}

				MonitorSpeakerOff();	/* 1997/02/28 Y.Murata */

				/* 1997/02/13 Y.Murata
				 * オペレーションタスクに電話関連の事象が変化したことを通知します
				*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
#endif
			}
			break;
		case MSG_OPT_FAXCOM_DET_TRANS_EXIT:
			SYS_OptionLineStatus[line_number] &= ~(SYS_OPTION_TELEPHONE_UES);
			if((!(ExistOrangeModem())) && (line_number == 1)){
#if 0
				NCU_DetectOnHookExit();
				SYS_MachineStatus[SYS_MACHINE_STATUS] &= ~(SYS_TELEPHONE);
				SYS_MachineStatus[SYS_MACHINE_STATUS_NCU] &= ~(SYS_TEL1_OFF_HOOK+SYS_TEL2_OFF_HOOK+SYS_BRANCH_OFF_HOOK+SYS_HOOK_KEY_OFF_HOOK+SYS_TAD+SYS_DIAL_IN+SYS_INTER_COM+SYS_INTER_CALL+SYS_LINE_HOLD+SYS_HOLD_TRANSFER+SYS_TRIPLE_COM);
				SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_HUNG_UP);

				/* if (CMN_CheckMultiLineReceiveNumber((UBYTE)line_number, AUTO_RECEIVE) < SYS_MEMORY_RX_MAX) { */
				if (MAN_CheckMultiLineReceiveEnable((UBYTE)line_number, AUTO_RECEIVE) < SYS_MEMORY_RX_MAX) {
					MAN_OptionModemStart((UBYTE)line_number);
					/* マシーンステータスの管理 */
					SYS_OptionLineStatus[line_number] |= SYS_OPTION_LINE_BUSY;
					SYS_Opt[line_number].SYS_FaxComType = SYS_AUTO_CALLED;
					SYS_Opt[line_number].SYS_FaxComTxType = 0;

					CMN_GetPollingDocRight(line_number);	/* Add By O.Kimoto 1997/01/13 */

					/* 個別属性セーブ 1997/01/27 Y.Murata */
					SYS_FaxComAbility0[line_number] = SYS_MemorySwitch[10];
					SYS_FaxComAbility1[line_number] = SYS_MemorySwitch[11];
					SYS_FaxComAbility2[line_number] = SYS_MemorySwitch[12];
					SYS_FaxComAbility3[line_number] = SYS_MemorySwitch[13];
					SYS_PreLineBusyCheckStatus[line_number] = 0;
					DPR_TransferCalled(line_number - 1);
				}
				else {
					SYS_PreLineBusyCheckStatus[line_number] = 1;
				}

				/* 1997/02/13 Y.Murata
				 * オペレーションタスクに電話関連の事象が変化したことを通知します
				*/
				MainTaskMessage.Item = FROM_MAIN;
				MainTaskMessage.Message = MSG_TEL_FROM_MAIN;
				snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
				rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
#endif
			}
			break;
#if defined(JPN)
#else
		case MSG_OPT_FAXCOM_CREATE_GRS_TASK:		/*  FAX側の擬似ベル鳴動タスク起動指示 */
			if((!(ExistOrangeModem())) && (line_number == 1)){
				SYS_RingSignalStopFlag  = 1;
				ring_data.StartTime		= 0;
				ring_data.SendMBX		= mbxno.FCM_Option;		/* メッセージ受信は有り得ない */
				ring_data.RingingTel	= ALL_TEL_RINGING;
				cre_tsk(&tskno_Bell, TSK_NCU_GENERATERINGSIGNALTASK, &ring_data );
			}
			break;
		case MSG_OPT_FAXCOM_DELETE_GRS_TASK:		/*  FAX側の擬似ベル鳴動タスク削除指示 */
			if((!(ExistOrangeModem())) && (line_number == 1)){
				SYS_RingSignalStopFlag  = 0;
				del_tsk( &tskno_Bell );
			}
			break;
		case MSG_OPT_FAXCOM_START_GRS_BELL:		/*  FAX側の呼出ブザー鳴動開始指示 */
			if((!(ExistOrangeModem())) && (line_number == 1)){
				SYS_RingSignalStopFlag  = 0;
			}
			break;
		case MSG_OPT_FAXCOM_STOP_GRS_BELL:		/*  FAX側の呼出ブザー鳴動停止指示 */
			if((!(ExistOrangeModem())) && (line_number == 1)){
				SYS_RingSignalStopFlag  = 1;
			}
			break;
#endif
		case MSG_OPT_EXEC_ERROR:	/* ｷｭｰ異常 */
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_PRE_LINE_BUSY;
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_LINE_BUSY;
			SYS_OptionLineStatus[line_number] &= ~SYS_OPTION_REAL_LINE_BUSY;

			if (CommandErased[line_number]) { /* コマンド消去がオペレーションより実行されていれば */
				CommandErased[line_number] = 0;
				MltDeleteComFileExecQueueFile((unsigned char)line_number); /* コマンドファイル、ExecQueueを消去 */
			}
			break;
		default:
			break;
	} /* End of 通信処理 */
}
#endif /* End of (PRO_MULTI_LINE == ENABLE)*/

#if(PRO_CIPHER == ENABLE)
/*************************************************************************
	module		:[暗号化タスクからのメッセージ処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/07/23]
	author		:[鈴木郁ニ]
*************************************************************************/
void	MAN_FromCipherTask(
	UWORD	Item,
	UWORD	Message,
	UWORD	SubMessage1,
	UWORD	SubMessage2)
{
	MESSAGE_t	MainTaskMessage;
	UWORD	cipher_item;
	UWORD	cipher_message;
	UWORD	cipher_sub_message1;
	UWORD	cipher_sub_message2;
	MESSAGE_t	*MessageControl;
	UBYTE result;

	cipher_item = Item;
	cipher_message = Message;
	cipher_sub_message1 = SubMessage1;
	cipher_sub_message2 = SubMessage2;

	if ((tskno_SCD_CipherTask != 0xffff)
		&& (cipher_message != MSG_DISPLAY_IDLE)
	/*	&& (cipher_message != MSG_OPT_CIPHER_PRT_RESTART)By Y.Suzuki 1998/07/24*/
		&& (cipher_message != MSG_OPT_DECIPHER_KEY_ERROR)) {
		del_tsk(&tskno_SCD_CipherTask); /** スクランブルタスク停止 */
	}
	switch(cipher_message) {
	case MSG_OPT_CIPHER_COMPLETE:
		if (SYS_CipherComExec == SYS_CIPHER_EXEC) {/*	暗号化	*/
			SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_SCRAMBLE_EXEC;
			SYS_CipherComExec = 0;
		/*	MemoryTxDocStoreOK(SYS_COMMAND_TRX);By Y.Suzuki 1997/12/11 */
			/* スクランブル処理中の原稿蓄積に対応するため */
			SYB_CommandFile[CipherStoreData.No].Page = MEM_CountTotalPage(SYS_MEM_TX_FILE, CipherStoreData.No, MEM_IGNORE_BOX_NUMBER); /* １ペ-ジ以上蓄積されていてFIPファイルでない時 */
			SYB_CommandFile[CipherStoreData.No].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)
			SYB_CommandStatus[CipherStoreData.No] = SYS_CMD_WAITING;
#endif
		}
		else {
		/*	if ((CipherReadPageNo > 1)&&(SYB_MaintenanceSwitch[MNT_SW_E1] & ALIROO_PRT_START_ON)) [By Y.Suzuki 1998/07/25 */
			if ((SYS_CipherComExec == SYS_DECIPHER_EXEC)&&(SYB_MaintenanceSwitch[MNT_SW_E1] & ALIROO_PRT_START_ON)) {
				/*２ページ目以降のスクランブル解除原稿の起動 By Y.Suzuki 1998/07/03 */
#if (0)
//				CMN_DisableInterrupt();	/**	割り込み禁止	*/
//				PRN_1PageReceived = 1;
//				det_evt(EVT_PRN_RESTART);
//				CMN_EnableInterrupt();	/**	割り込み許可	*/
#endif
				if (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC) {/* By Y.Suzuki 1998/07/15 */
					/*スクランブル解除完了後、受信原稿自動消去の場合*/
					/*スクランブル受信原稿ボックス受信なしにする。*/
					SYB_CipherBox[CipherReadIndex.No].Status = SYS_CIPHERBOX_NO;
				}
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_ERASE_SCRAMBLE_DOC;/* By Y.Suzuki 1998/07/15 */
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DISPLAY_DESCRAMBLE;/*By Y.Suzuki 1998/07/22*/
			}

			SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_EXEC;
			SYS_CipherComExec = 0;/*By Y.Suzuki 1998/06/08*/
		}
#if(0)/*By Y.Suzuki 1998/01/14*/
//		else {/**	イメージプリント起動	*/
//			if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT) == TRUE) { /** プリント可能 */	/*種類を追加 M.Kotani 1997/10/16*/
//				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
//				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
//				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_EXEC;
//				if (SYS_CipherComExec == SYS_DECIPHER_EXEC) {/* スクランブル受信原稿 */
//					SYS_DocumentPrintItem = SYS_MEM_DECIPHER_FILE;
//				}
//				else {/* スクランブル送信予約原稿 */
//					SYS_DocumentPrintItem = SYS_MEM_TX_DECIPHER_FILE;
//				}
//				SYS_DocumentPrintNo = cipher_sub_message2;/* スクランブル解除プリント時 受信ＮＯ．０から９ */
//				SYS_DocumentPrintPageNo = 1;
//				SYS_DocumentPrintClass = SYS_PRINT_CLASS;
//				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /** 畜積原稿ﾌﾟﾘﾝﾄﾀｽｸ起動 */
//			}
//		}
#endif
		break;
	case MSG_OPT_ALIROO_ERROR:
		if (SYS_CipherComExec == SYS_CIPHER_EXEC) {
			SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_SCRAMBLE_ERROR;
			MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセルBy Y.Suzuki 1998/02/09 */
		}
		else {
			SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_DESCRAMBLE_ERROR;
			if ((SYS_CipherComExec == SYS_DECIPHER_EXEC)
				&& (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC)) {/*By Y.Suzuki 1998/07/20*/
				/*スクランブル原稿自動消去で既に消去されたページがある*/
				/*スクランブル受信原稿を全て消去する。*/
				MEM_ClearDocAndFATArea(CipherReadIndex.Item, CipherReadIndex.No, CipherReadIndex.BoxNumber);
				SYB_CipherBox[CipherReadIndex.No].Status = SYS_CIPHERBOX_NO;
			}
			/* デスクランブルプリント中のエラーで、プリント中の表示のままとなる。*/
			SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;/*By Y.Suzuki 1998/07/31*/
		}
		break;
	case MSG_OPT_CIPHER_MEM_ERROR:
		SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_SCRAMBLE_MEM_OVER;
		MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセル */
		break;
	case MSG_OPT_DECIPHER_MEM_ERROR:
		SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_DESCRAMBLE_MEM_OVER;
		if ((SYS_CipherComExec == SYS_DECIPHER_EXEC)
			&& (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC)) {/*By Y.Suzuki 1998/07/20*/
			/*スクランブル原稿自動消去で既に消去されたページがある*/
			/*スクランブル受信原稿を全て消去する。*/
			MEM_ClearDocAndFATArea(CipherReadIndex.Item, CipherReadIndex.No, CipherReadIndex.BoxNumber);
			SYB_CipherBox[CipherReadIndex.No].Status = SYS_CIPHERBOX_NO;
		}
		/* デスクランブルプリント中のエラーで、プリント中の表示のままとなる。*/
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;/*By Y.Suzuki 1998/07/31*/
		break;
	case MSG_OPT_CIPHER_DECODE_ERROR:
		SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_SCRAMBLE_ERROR;
		MemoryTxDocStoreNG(SYS_COMMAND_TRX); /** メモリ送信コマンド・ファイルのキャンセルBy Y.Suzuki 1998/02/09 */
		break;
	case MSG_OPT_DECIPHER_DECODE_ERROR:
		SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_DESCRAMBLE_ERROR;
		if ((SYS_CipherComExec == SYS_DECIPHER_EXEC)
			&& (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC)) {/*By Y.Suzuki 1998/07/20*/
			/*スクランブル原稿自動消去で既に消去されたページがある*/
			/*スクランブル受信原稿を全て消去する。*/
			MEM_ClearDocAndFATArea(CipherReadIndex.Item, CipherReadIndex.No, CipherReadIndex.BoxNumber);
			SYB_CipherBox[CipherReadIndex.No].Status = SYS_CIPHERBOX_NO;
		}
		/* デスクランブルプリント中のエラーで、プリント中の表示のままとなる。*/
		SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;/*By Y.Suzuki 1998/07/31*/
		break;
	case MSG_OPT_DECIPHER_FROM_OPR:
		SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_WRONG_KEY_ERROR;
		break;
	case MSG_OPT_CIPHER_STOPON:
		if (SYS_CipherComExec == SYS_CIPHER_EXEC) {
			if (SYS_CipherInterruptionOn == 0) {/*受信優先ではないBy Y.Suzuki 1998/06/09 */
				/* スクランブル/デスクランブル前原稿の消去 */
				MEM_ClearDocAndFATArea(CipherReadIndex.Item, CipherReadIndex.No, CipherReadIndex.BoxNumber);
			/*	MemoryTxDocStoreNG(SYS_COMMAND_TRX); @** メモリ送信コマンド・ファイルのキャンセル By Y.Suzuki 1998/02/13 */
				SYB_CommandFile[CipherReadIndex.No].Page = 1;
				SYB_CommandFile[CipherReadIndex.No].Status = SYS_CMD_EMPTY;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[CipherReadIndex.No] = SYS_CMD_EMPTY;
#endif
			}
		}
		else {
			if (SYS_CipherInterruptionOn == 0) {/*受信優先ではないBy Y.Suzuki 1998/06/09 */
				if (SYB_CPH_RxPrint[0].Status == SYS_MCOPY_STORE) {
					/* デスクランブル完了ページがない場合（プリントタスク起動されてないときのみ）By Y.Suzuki 1998/01/27*/
					SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;
				}
				if ((SYS_CipherComExec == SYS_DECIPHER_EXEC)
					&& (SYS_MachineStatus[SYS_CIPHER_STATUS] & SYS_ERASE_SCRAMBLE_DOC)) {/*By Y.Suzuki 1998/07/20*/
					/*スクランブル原稿自動消去で既に消去されたページがある*/
					/*スクランブル受信原稿を全て消去する。*/
					MEM_ClearDocAndFATArea(CipherReadIndex.Item, CipherReadIndex.No, CipherReadIndex.BoxNumber);
					SYB_CipherBox[CipherReadIndex.No].Status = SYS_CIPHERBOX_NO;
				}
			}
			/*デスクランブルプリント中のストップキー入力で、プリント中の表示のままとなる。*/
			SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_PRINT;/*By Y.Suzuki 1998/07/31*/
		}
		if (SYS_CipherInterruptionOn == 0) {/*受信優先ではないBy Y.Suzuki 1998/06/09 */
			/* 処理中の原稿消去 */
			/* 蓄積中だったブロックはまだカウントされていません By Y.Suzuki 1997/12/09 */
			MEM_TotalStoreBlockCounter++;
			MEM_ClearDocAndFATArea(CipherStoreData.Item, CipherStoreData.No, CipherStoreData.BoxNumber);
		}
		else {/*受信優先の場合、処理中のページのみ消去する By Y.Suzuki 1998/06/09 */
			if (CipherStoreData.Page > 1) {/*処理の終わったページが存在する*/
				CipherWriteIndex.No  = CipherStoreData.No;
				CipherWriteIndex.Page  = CipherStoreData.Page;
				CipherWriteIndex.Item  = CipherStoreData.Item;
				CipherWriteIndex.BoxNumber = 0;/* By Y.Suzuki 1998/04/14 */
				CipherWriteIndex.Item |= MEM_NOW_STORING;/* By Y.Suzuki 1998/04/08 */
				result = MEM_ClearPageAndFATArea(&CipherWriteIndex);/* By Y.Suzuki 1998/04/8 */
			}
			else {
				MEM_TotalStoreBlockCounter++;
				MEM_ClearDocAndFATArea(CipherStoreData.Item, CipherStoreData.No, CipherStoreData.BoxNumber);
			}
		}
		break;
	case MSG_OPT_DECIPHER_KEY_ERROR:
		/* ＯＰＲにてデスクランブル継続/中断の入力あり */
		MainTaskMessage.Item = FROM_MAIN;
		MainTaskMessage.Message = MSG_EXIT;
		SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_WRONG_KEY_ERROR;
		snd_msg(mbxno.OPR_SubMessageTask, &MainTaskMessage);
		/* 上のメッセージ受信部で下のメッセージを送信してくるので受信する。他の処理は特になし */
		rcv_msg(mbxno.OPR_Sub_MANTask, &MessageControl);
		break;
	case MSG_OPT_CIPHER_PRT_RESTART:/* By Y.Suzuki 1998/01/16 */

#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1988.6.1 K.Kawata */
#else

#if (0)/*By Y.Suzuki 1998/07/24*/
	/* 復元原稿のプリント２ページ目以降 起動 */
//		CMN_DisableInterrupt();	/**	割り込み禁止	*/
//		PRN_1PageReceived = 1;
//		det_evt(EVT_PRN_RESTART);
//		CMN_EnableInterrupt();	/**	割り込み許可	*/
#endif
#endif

		break;
	default:/* MSG_DISPLAY_IDLE */
		break;
	}
	if ((cipher_message != MSG_OPT_CIPHER_COMPLETE)
/*	&& (cipher_message != MSG_OPT_CIPHER_PRT_RESTART)By Y.Suzuki 1998/07/21*/
	&& (cipher_message != MSG_DISPLAY_IDLE)) {
#if (0)/*By Y.Suzuki 1998/01/14*/
//		/* 復元処理中のエラー発生時、正常終了したページがあったらプリントする。 */
//		if ((cipher_sub_message1 == 1) || (cipher_sub_message1 == 2)) {
//			if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT) == TRUE) { /** プリント可能 */	/*種類を追加 M.Kotani 1997/10/16*/
//				SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /** ﾌﾟﾘﾝﾀ使用中ｾｯﾄ */
//				SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT; /** ﾒﾓﾘﾌﾟﾘﾝﾄ使用中ｾｯﾄ */
//				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_EXEC;
//				if (SYS_CipherComExec == SYS_DECIPHER_EXEC) {/* スクランブル受信原稿 */
//					SYS_DocumentPrintItem = SYS_MEM_DECIPHER_FILE;
//				}
//				else {/* スクランブル送信予約原稿 */
//					SYS_DocumentPrintItem = SYS_MEM_TX_DECIPHER_FILE;
//				}
//				SYS_DocumentPrintNo = cipher_sub_message2;
//				SYS_DocumentPrintPageNo = 1;
//				SYS_DocumentPrintClass = SYS_PRINT_CLASS;
//				cre_tsk(&tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0); /** 畜積原稿ﾌﾟﾘﾝﾄﾀｽｸ起動 */
//			}
//		}
#endif
		/* ｽｸﾗﾝﾌﾞﾙ終了ﾒｯｾｰｼﾞ、表示用ﾒｯｾｰｼﾞ以外のﾒｯｾｰｼﾞ受信の場合と
		*  キー間違いでかつ最終ページの場合。By Y.Suzuki 1998/07/21
		*  に以下の処理を行う。
		*  最終ページでも１ページのみの場合は、以下の処理行わない。By Y.Suzuki 1998/07/24 */
		if ((cipher_message == MSG_OPT_DECIPHER_KEY_ERROR) && (CipherReadPageNo != CipherData.PageNo)) {
			/*スクランブル処理継続する*/
		}
		else {
		/*	if (CipherReadPageNo != 1) [By Y.Suzuki 1998/08/03*/
			if (!((cipher_message == MSG_OPT_DECIPHER_KEY_ERROR) && (CipherReadPageNo == CipherData.PageNo)
				&& (CipherReadPageNo == 1))) {
				/*スクランブル終了処理*/
#if (0)/*By Y.Suzuki 1998/07/24*/
//				if (cipher_sub_message1 == 1) {/* By Y.Suzuki 1998/07/08 */
//					/* 復元処理中のエラー発生時、正常終了したページがあったらプリントする。 */
//					CMN_DisableInterrupt();	/**	割り込み禁止	*/
//					PRN_1PageReceived = 1;
//					det_evt(EVT_PRN_RESTART);
//					CMN_EnableInterrupt();	/**	割り込み許可	*/
//				}
#endif
				/* スクランブル中／復元中 ステータスＯＦＦ */

				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_SCRAMBLE_EXEC;
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DESCRAMBLE_EXEC;
				SYS_CipherComExec = 0;
				CipherStopOn = 0;
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_ERASE_SCRAMBLE_DOC;/* By Y.Suzuki 1998/07/15 */
				SYS_MachineStatus[SYS_CIPHER_STATUS] &= ~SYS_DISPLAY_DESCRAMBLE;/*By Y.Suzuki 1998/07/22*/
			}
		}
	}
}
#endif /* PRO_CIPHER ENABLE */
