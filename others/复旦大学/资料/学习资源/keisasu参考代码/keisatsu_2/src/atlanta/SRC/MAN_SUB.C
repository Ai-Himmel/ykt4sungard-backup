/************************************************************************
*				BY:	 S.Kawasaki
*			  DATE:	 Jan.7,1994
*		 COPY DATE: 1996/10/23 From \src\kobe\anzu\src\ By M.Kotani
*		 FILE NAME:	 man_sub.c
*	   DESCRIPTION:
*  PUBLIC ROUTINES: void DeleteScannerCommand(void)
*					UBYTE CheckScannerCommand(BYTE CommandNumber)
*					UBYTE CheckDocStoredCommand(UBYTE CommandNumber)
*					void DeleteCommandFileExecQueueFile(void)
*					UBYTE SYS_FaxComStopSwitch(void)
*					UBYTE SYS_TelephoneStopSwitch(void)
*					UBYTE SYS_ScannerCopyStopSwitch(void)
*					UBYTE SYS_MultiCopyStopSwitch(void)
*					UBYTE SYS_ListPrintStopSwitch(void)
*					UBYTE SYS_FipStopSwitch(void)
*					UBYTE SYS_TAD_StopSwitch(void)
*					UBYTE SYS_InterCallStopSwitch(void)
*					UBYTE SYS_DocumentStoreStopSwitch(void)
*					UBYTE SYS_ImagePrintStopSwitch(void)
*					void InitializeDRAM_Parameter(void)
* PRIVATE ROUTINES: void MemoryTxDocStoreNG(UBYTE command_type)
*					void MultiCopyDocStoreNG(void)
*					void MemoryTxDocStoreOK(UBYTE command_type)
*					void MultiCopyDocStoreOK(void)
*					UBYTE CheckInitializeKeyON(void)
*					void BackupCommandFile(void)
*					void BackupMemoryRxPrintFile(void)
*					void BackupBufferingRxPrintFile(void)
*					void BackupExecQueueFile(void)
*					void BackupSecureFile(void)
*					void BackupPollingFile(void)
*					void BackupBatchTxFile(void)
*					void BackupDeleteingComOrExecFile(void)
*					void RecoverDRAM_Parameter(void)
*					void InitializeDRAM_Backup(void)
*					void CreateRelayedReportCommand(UBYTE report_no, UBYTE relayed_no)
*					void ExecuteRelayedReportPrint(UBYTE relayed_no)
*					void CheckMessageTest(void)
*					void MAN_ClearCommunicationError(void)
*					UBYTE MAN_AutoReadyModeChangeEnable(void)
*					void MAN_AutoChangeReadyMode(void)
*		 コメント : MemoryTxDocStoreNG() MultiCopyDocStoreNG()
*				  : MemoryTxDocStoreOK() MultiCopyDocStoreOK() をMAN_MAIN.cから移動 1994/10/13 Y.Murata
*				  : InitializeDRAM_Parameter()
*				  : RecoverDRAM_Parameter()
*				  : InitializeDRAM_Backup() をMAN_INIT.cから移動 1994/11/26 Y.Murata
*				  : ラベンダー用のＰＩＮアクセスのパスを抹消しました 1996/02/07 Eguchi
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sys_pdwn.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\sysprint.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\sysexec.h"
#include "\src\atlanta\define\mntsw_a.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\define\SYSDOC.h"		/* DEBUG */
#include "\src\atlanta\sh7043\define\sh_sys.h"
/*MON*/
#include "\src\atlanta\sh7043\define\def_semn.h"
#include "\src\atlanta\sh7043\define\def_tib.h"
/*MEM*/
#include "\src\atlanta\define\mem_def.h"
/*FCM*/
#include "\src\atlanta\define\fcm_def.h"
/*MDM*/

#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#endif

/*DPR*/
#if (PRO_PC_PRINT == ENABLE)
#include "\src\atlanta\define\syspcrx.h"
#endif
/*FIP*/
#if (PRO_FIP == ENABLE)
#include "\src\atlanta\define\fip_def.h"
#endif
/* 連続ポーリング機能 */
#if (PRO_CONTINUOUS_POLLING == ENABLE)
#include "\src\atlanta\define\syscntpl.h"
#endif
#if (PRO_MULTI_LINE == ENABLE)
#include "\src\atlanta\define\sys_opt.h"
#endif

#if defined(ANZU_L)	/* debug debug */
#include "\src\atlanta\define\syscntpl.h"
#endif

/*参照ファイル*/
/*SYS*/
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\man_data.h"
#if (PRO_CLASS1 == ENABLE)
#include "\src\atlanta\ext_v\cl1_data.h"
#endif
/*MON*/
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
/*FCM*/
#include "\src\atlanta\ext_v\fcm_data.h"

#if (PRO_CIPHER == ENABLE)/*	By Y.Suzuki 1997/09/04	*/
#include "\src\atlanta\scd\ext_v\cph_data.h"
#endif

/*プロトタイプ宣言*/
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\stng_pro.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#if (PRO_DPRAM == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#if (PRO_PANEL == ANK)
#include "\src\atlanta\opr\ank\define\opr_pro.h"
#endif
#if (PRO_PANEL == KANJI)
#include "\src\atlanta\opr\kanji\define\opr_pro.h"
#endif


#if defined(ANZU_L)	/* debug debug */
void TestDataClear(void);
#include "\src\atlanta\define\sysmailb.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
void	RecoverMailComDramBackUpOK(void);
void	RecoverMailComDramBackUpNG(void);
#endif

#if (0)	/* 1998/12/14 H.Yoshikawa */
//#if defined (SAKAKI)	/* 1998/12/11 H.Yoshikawa ＤＲＡＭ電池残量テスト用 */
//#define	MODEM2_PORT	0x00C20400	/* アドレス */
//extern UWORD SYS_Modem2PortStatus;
//#endif
#endif

#if (PRO_PRINTER_RX == ENABLE)
	#include "\src\atlanta\define\unisw_c.h"	/* added by H.Hirao 1998/12/24 */
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
	#include "\src\atlanta\define\mntsw_b.h"	/* added by H.Hirao 1998/02/01 */
#endif
#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
#include	"\src\atlanta\define\unisw_j.h"
#include	"\src\atlanta\define\status.h"
#include	"\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.2.25 K.Kawata */
#include "\src\atlanta\define\unisw_c.h"
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
																		/* Add by Y.Kano 2003/07/11 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
#include "\src\atlanta\define\cmn_def.h"
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
#include "\src\atlanta\define\cmn_def.h"
#endif

#if defined (KEISATSU) /* 警察FAX 05/11/16 石橋正和 */
#include "\src\atlanta\define\s1_pro.h"
#endif

#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/07/18 */
extern UBYTE	IsSHIREIDisable;
#endif /* defined (KEISATSU) */

/* Module Header For CIM-E ********************************************
		module		:	[スキャナーコマンドを消去する。]
		function	:	[]
		return		:	[無し]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/7]
		author		:	[川崎真史]
************************************************************************/
void DeleteScannerCommand(void)
{
	UBYTE com_no;
	UBYTE exec_no;
	struct	SYS_CommandData_t *com_ptr;
	struct	SYS_ExecQueueData_t *exec_ptr;


	/* 予約中,実行中または実行前のスキャナコマンドを消去するようにする */
	/* 実行終了したものなどは消去しない *//*原稿引き抜き時、何でもかんでも消すとチェックメッセージをプリント時に困る*/

	for (com_no = 0; com_no < SYS_COM_FILE_MAX; com_no++) {
		com_ptr = &SYB_CommandFile[com_no];

		if ((com_ptr->Status == SYS_CMD_WAITING)
		||	(com_ptr->Status == SYS_CMD_EXECUTE)) {/** 予約中・実行中 */
			switch (com_ptr->Option.Item) {
			case SYS_SCANNER_TX:
			case SYS_DELAYED_SCANNER_TX:
			case SYS_SCANNER_SECURE_TX:
			case SYS_SCANNER_RELAY_BROADCAST:
			case SYS_FX_SCANNER_RELAY_TX:	/* By H.Y 1994/10/26 */
			case SYS_FX_SCANNER_SECURE_TX:	/* By H.Y 1994/10/26 */
#if (PRO_F_CODE == ENABLE)
			case SYS_SCANNER_SUB_ADDRESS_TX:	/* 1997/04/16  By T.Yamaguchi */
#endif
				if (com_ptr->Status == SYS_CMD_WAITING) {
					/* 予約中のスキャナコマンド発見 */
					CMN_ClearCommandArea(SYS_COMMAND_TRX , com_no);
				}
				else {/* com_ptr->Status == SYS_CMD_EXECUTE */
					for (exec_no = 0; exec_no < SYS_EXEC_QUEUE_MAX; exec_no++) {
						exec_ptr = &SYB_ExecQueue[exec_no];
						if ((exec_ptr->Status >= SYS_EXEC_WAITING)
						&&	(exec_ptr->Status <= SYS_EXEC_FORWARD_EXECUTE)
						&&	(exec_ptr->Kind == SYS_COMMAND_TRX)
						&&	(exec_ptr->Number.Command == com_no)){
							/* 実行まちのスキャナコマンド発見 */
							CMN_ClearCommandArea(SYS_COMMAND_TRX , com_no);
							break;
						}
					}
				}
			}
		}
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[指定されたコマンド番号がスキャナーコマンド可を確認する。]
		function	:	[]
		return		:	[
						０：スキャナー・コマンドではない。
						１：スキャナー・コマンドである。
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE CheckScannerCommand(BYTE CommandNumber)
{
	if (CommandNumber < SYS_COM_FILE_MAX) {
		switch (SYB_CommandFile[CommandNumber].Status) {
			case SYS_CMD_WAITING:
			case SYS_CMD_EXECUTE:
				switch (SYB_CommandFile[CommandNumber].Option.Item) {
					case SYS_SCANNER_TX:
					case SYS_DELAYED_SCANNER_TX:
					case SYS_SCANNER_SECURE_TX:
					case SYS_SCANNER_RELAY_BROADCAST:
					case SYS_FX_SCANNER_RELAY_TX:	/* By H.Y 1994/10/26 */
					case SYS_FX_SCANNER_SECURE_TX:	/* By H.Y 1994/10/26 */
#if (PRO_F_CODE == ENABLE)
					case SYS_SCANNER_SUB_ADDRESS_TX: /* 1997/04/16  By T.Yamaguchi */
#endif
						return(1);
					default:
						return(0);
				}
			default:
				return(0);
		}
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[ポーリングコマンドかどうかのチェック]
	function	:[
		1.MAN_CheckPollingCommand(UBYTE CommandNumber)を移植
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/12/24]
	author		:[村田 山口]
*************************************************************************/
UBYTE CheckPollingRxCommand(UBYTE CommandNumber)
{
	if (CommandNumber < SYS_COM_FILE_MAX) {
		switch (SYB_CommandFile[CommandNumber].Status) {
		case SYS_CMD_WAITING:
		case SYS_CMD_EXECUTE:
			switch (SYB_CommandFile[CommandNumber].Option.Item) {
			case SYS_POLLING_RX:
			case SYS_DB_POLLING_RX:
			case SYS_SEQUENTIAL_POLLING:
#if (PRO_F_CODE == ENABLE)
			case SYS_SELECT_POLLING_RX:
#endif
				return(1);
			default:
				return(0);
			}
		default:
			return(0);
		}
	}
	else {
		return(0);
	}
}

/* Module Header For CIM-E ********************************************
		module		:	[指定されたコマンド番号がメモリ蓄積コマンド可を確認する。]
		function	:	[]
		return		:	[
						０：メモリ蓄積コマンドではない。
						１：メモリ蓄積スキャナー・コマンドである。
						]
		common		:	[]
		condition	:	[]
		comment		:	[
				95/02/17  不達通知送信のアイテム追加。 Y.Suzuki
		]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE CheckDocStoredCommand(UBYTE CommandNumber)
{
	if (CommandNumber < SYS_COM_FILE_MAX) {
		switch (SYB_CommandFile[CommandNumber].Status) {
			case SYS_CMD_WAITING:
			case SYS_CMD_EXECUTE:
				switch (SYB_CommandFile[CommandNumber].Option.Item) {
					case SYS_MEMORY_TX:
					case SYS_DELAYED_MEMORY_TX:
					case SYS_MEMORY_SECURE_TX:
					case SYS_MEMORY_RELAY_BROADCAST:
					case SYS_DELAYED_BROADCAST:
					case SYS_RELAYED_TX:
					case SYS_FX_MEMORY_RELAY_TX:	/* By H.Y 1994/10/26 */
					case SYS_FX_MEMORY_SECURE_TX:	/* By H.Y 1994/10/26 */
					case SYS_RELAYED_TX_REPORT:		/* By Y.S 1995/02/17 */
#if (PRO_F_CODE == ENABLE)
					case SYS_MEMORY_SUB_ADDRESS_TX:
#endif
					case SYS_CIPHER_TX:/* By Y.Suzuki 1998/04/23 */
						return(1);
					default:
						return(0);
				}
			default:
				return(0);
		}
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[通信処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_FaxComStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_FAXCOM) {
		return(1);
	}
#if defined (KEISATSU) /* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
	else if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_COM_ON_FORCE) {
		if (!IsSHIREIDisable){
			FaxComTXorRX_Flag = FaxComTXorRX_Sign;
		}
		return(1);
	}
#endif /* defined (KEISATSU) */
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[多機能電話処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_TelephoneStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_TELEPHONE) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[スキャナー・コピー処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_ScannerCopyStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_SCANNER_COPY) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[マルチ・コピー処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_MultiCopyStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_MULTI_COPY) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[リスト・プリント処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_ListPrintStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_LIST_PRINT) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[ＦＩＰ処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_FipStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_FIP) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[ＴＡＤ処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_TAD_StopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_TAD) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[内線呼び出し処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_InterCallStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_INTER_CALL) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[原稿蓄積処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_DocumentStoreStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_DOC_STORE) {
		return(1);
	}
	else {
		return(0);
	}
}


/* Module Header For CIM-E ********************************************
		module		:	[イメージ・プリント処理停止要求確認]
		function	:	[]
		return		:	[
						０：停止要求無し
						１：停止要求有り
						]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[94/2/4]
		author		:	[川崎真史]
************************************************************************/
UBYTE SYS_ImagePrintStopSwitch(void)
{
	if (SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_IMAGE_PRINT) {
		return(1);
	}
	else {
		return(0);
	}
}


/** Module Header For CIM-E ********************************************
		module		:	[コマンド通信登録キャンセル]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/10(金)]
		author		:	[川崎真史]
************************************************************************/
void MemoryTxDocStoreNG(UBYTE command_type)
{
	UBYTE i;
#if (PRO_BATCH_TX == ENABLE)
	UBYTE batch_command_no;
#endif

	if (command_type == SYS_COMMAND_TRX) {
		if (SYS_MultiProgramFlag == 1) { /* 7/22/1994 */
			for (i = 0; (i < SYS_JOB_MAX)&&(SYS_MultiProgramNo[i] != 0xFF); i++) {
				SYB_CommandFile[SYS_MultiProgramNo[i]].Page = 1;
				SYB_CommandFile[SYS_MultiProgramNo[i]].Status = SYS_CMD_EMPTY;
#if (PRO_F_CODE == ENABLE)	/* 1997/08/08  By T.Yamaguchi */
				if (CMN_CheckFcodeCommand(SYB_CommandFile[SYS_MultiProgramNo[i]].Option.Item) == TRUE) {	/** 交信種別判断 */
					SYB_FcodeNumberCDataBuffer[SYB_CommandFile[SYS_MultiProgramNo[i]].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
					SYB_FcodeNumberCDataBuffer[SYB_CommandFile[SYS_MultiProgramNo[i]].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
				}
#endif
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[SYS_MultiProgramNo[i]] = SYS_CMD_EMPTY;
#endif
#if (PRO_FAX_AND_1COPY == ENABLE)	/* 1999/02/18 H.Yoshikawa */
				if (SYS_FaxAnd1CopyEnable == TRUE) {
					MultiCopyDocStoreNG();
				}
#endif	
			}
		}
		else {
			SYB_CommandFile[SYS_DocumentStoreNo].Page = 1;
			SYB_CommandFile[SYS_DocumentStoreNo].Status = SYS_CMD_EMPTY;
#if (PRO_F_CODE == ENABLE)	/* 1997/08/08  By T.Yamaguchi */
			if (CMN_CheckFcodeCommand(SYB_CommandFile[SYS_DocumentStoreNo].Option.Item) == TRUE) {	/** 交信種別判断 */
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[SYS_DocumentStoreNo].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
				SYB_FcodeNumberCDataBuffer[SYB_CommandFile[SYS_DocumentStoreNo].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
			}
#endif
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[SYS_DocumentStoreNo] = SYS_CMD_EMPTY;
#endif
#if (PRO_FAX_AND_1COPY == ENABLE)	/* 1999/02/18 H.Yoshikawa */
			if (SYS_FaxAnd1CopyEnable == TRUE) {
				MultiCopyDocStoreNG();
			}
#endif	
		}
	}
#if (PRO_BATCH_TX == ENABLE)
	else if (command_type == SYS_BATCH_TX) {
		batch_command_no = (UBYTE)(SYS_DocumentStoreItem - SYS_MEM_BATCH_TX_FILE1); /** 一括送信コマンド番号 */

		SYB_BatchTxFile[batch_command_no].IndexNo[SYS_DocumentStoreNo] = SYS_BAT_DOC_EMPTY;	/** 原稿無しをセット *//* By H.Y 1994/08/15 */
		for (i = 0; i < SYS_BATCH_INDEX_MAX; i++) {
			if (SYB_BatchTxFile[batch_command_no].IndexNo[i] == SYS_BAT_DOC_STORE) { /** 登録原稿有り */
				SYB_BatchTxFile[batch_command_no].Status = SYS_CMD_WAITING;
				return; /** 一つでも登録原稿があれば処理中断 */
			}
		}
		SYB_BatchTxFile[batch_command_no].Status = SYS_CMD_EMPTY;
	}
#endif
}


/** Module Header For CIM-E ********************************************
		module		:	[マルチ・コピー・コマンドのキャンセル]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/10(金)]
		author		:	[川崎真史]
************************************************************************/
void MultiCopyDocStoreNG(void)
{
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_EMPTY;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ExecutiveNumber = 0;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = 0;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 0;
}


/** Module Header For CIM-E ********************************************
		module		:	[手差しコピー・コマンドのキャンセル]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[Aug.07.1996]
		author		:	[曽根岡拓]
************************************************************************/
void ManualCopyDocStoreNG(void)
{
	SYB_ManualCopyFile.Status = SYS_MCOPY_EMPTY;
	SYB_ManualCopyFile.ExecutiveNumber = 0;
	SYB_ManualCopyFile.StorePage = 0;
	SYB_ManualCopyFile.PrintPage = 0;
}


/* Module Header For CIM-E ********************************************
		module		:	[コマンド通信の登録終了]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/10(金)]
		author		:	[川崎真史]
************************************************************************/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/12 Y.Murata for KAKI */
void MemoryTxDocStoreOK(UBYTE command_type)
{
	UBYTE batch_command_no;
	UBYTE i;

	if (command_type == SYS_COMMAND_TRX) {
		if ((SYB_CommandFile[SYS_DocumentStoreNo].Status == SYS_CMD_WAITING) 
		|| (SYB_CommandFile[SYS_DocumentStoreNo].Status == SYS_CMD_EXECUTE)) {	/* クイック送信時 */

			SYB_CommandFile[SYS_DocumentStoreNo].Page = MEM_CountFinalPage(SYS_MEM_TX_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);

			/* この行はデバックでＴＴＩに総ページ数を出すために入れる */
			CommandFilePage = (UWORD)SYB_CommandFile[SYS_DocumentStoreNo].Page;

		}
		else if (SYB_CommandFile[SYS_DocumentStoreNo].Status == SYS_CMD_SETTING) {

			if (SYS_MultiProgramFlag == 1) {
				for (i = 0; (i < SYS_JOB_MAX)&&(SYS_MultiProgramNo[i] != 0xFF); i++) {
					SYB_CommandFile[SYS_MultiProgramNo[i]].Page = MEM_CountTotalPage(SYS_MEM_TX_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* １ペ-ジ以上蓄積されていてFIPファイルでない時 */
					SYB_CommandFile[SYS_MultiProgramNo[i]].Status = SYS_CMD_WAITING;
					SYB_CommandStatus[SYS_MultiProgramNo[i]] = SYS_CMD_WAITING;
				}
			}
			else {
				SYB_CommandFile[SYS_DocumentStoreNo].Page = MEM_CountTotalPage(SYS_MEM_TX_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* １ペ-ジ以上蓄積されていてFIPファイルでない時 */
				SYB_CommandFile[SYS_DocumentStoreNo].Status = SYS_CMD_WAITING;
				SYB_CommandStatus[SYS_DocumentStoreNo] = SYS_CMD_WAITING;
			}
		}
		else {
			/*
			 * 上記以外の状態の時
			 * 一番恐いんがクイックメモリ送信中にオペレーションでコマンドを消去された時
			*/
			switch (SYB_CommandFile[SYS_DocumentStoreNo].Status) {
			case SYS_CMD_ERASED:
				/* あとで考える */
				break;
			case SYS_CMD_EMPTY:
			case SYS_CMD_POWER_OFF:
			default:
				/* ここは絶対にない */
				break;
			}
		}
	}
	else if (command_type == SYS_BATCH_TX) {
		batch_command_no = (UBYTE)(SYS_DocumentStoreItem - SYS_MEM_BATCH_TX_FILE1);

		SYB_BatchTxFile[batch_command_no].IndexNo[SYS_DocumentStoreNo] = SYS_BAT_DOC_STORE;	/** 原稿有りをセット */
		SYB_BatchTxFile[batch_command_no].Status = SYS_CMD_WAITING;
	}
}

#else

void MemoryTxDocStoreOK(UBYTE command_type)
{
#if (PRO_BATCH_TX == ENABLE)
	UBYTE batch_command_no;
#endif
	UBYTE i;

	if (command_type == SYS_COMMAND_TRX) {
		if (SYS_MultiProgramFlag == 1) { /* 7/22/1994 */
			for (i = 0; (i < SYS_JOB_MAX)&&(SYS_MultiProgramNo[i] != 0xFF); i++) {
				SYB_CommandFile[SYS_MultiProgramNo[i]].Page = MEM_CountTotalPage(SYS_MEM_TX_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* １ペ-ジ以上蓄積されていてFIPファイルでない時 */
				SYB_CommandFile[SYS_MultiProgramNo[i]].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[SYS_MultiProgramNo[i]] = SYS_CMD_WAITING;
#endif
#if (PRO_FAX_AND_1COPY == ENABLE)	/* 1999/02/18 H.Yoshikawa */
				if (SYS_FaxAnd1CopyEnable == TRUE) {
					MultiCopyDocStoreOK();
				}
#endif	
			}
		}
		else {
			/* SYB_CommandFile[SYS_DocumentStoreNo].Page = MEM_CountTotalPage(SYS_MEM_TX_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);  １ペ-ジ以上蓄積されていてFIPファイルでない時 */
			SYB_CommandFile[SYS_DocumentStoreNo].Page = MEM_CountTotalPage(SYS_MEM_TX_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER); /* １ペ-ジ以上蓄積されていてFIPファイルでない時 */
			SYB_CommandFile[SYS_DocumentStoreNo].Status = SYS_CMD_WAITING;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[SYS_DocumentStoreNo] = SYS_CMD_WAITING;
#endif
#if (PRO_FAX_AND_1COPY == ENABLE)	/* 1999/02/18 H.Yoshikawa */
			if (SYS_FaxAnd1CopyEnable == TRUE) {
				MultiCopyDocStoreOK();
			}
#endif	
		}
	}
#if (PRO_BATCH_TX == ENABLE)
	else if (command_type == SYS_BATCH_TX) {
		batch_command_no = (UBYTE)(SYS_DocumentStoreItem - SYS_MEM_BATCH_TX_FILE1);

		SYB_BatchTxFile[batch_command_no].IndexNo[SYS_DocumentStoreNo] = SYS_BAT_DOC_STORE;	/** 原稿有りをセット */
		SYB_BatchTxFile[batch_command_no].Status = SYS_CMD_WAITING;
	}
#endif
}

#endif /* #if (PRO_QUICK_TX_TEST == ENABLE) */


/** Module Header For CIM-E ********************************************
		module		:	[マルチ・コピー・コマンドの登録終了]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[93/12/10(金)]
		author		:	[川崎真史]
************************************************************************/
void MultiCopyDocStoreOK(void)
{
/* #if (PRO_FBS == DISABLE) ソートノンソートのPROを切っていないのでFACEアップで区別する
  もし、FACE_UPでない機種でノンソートの機種があれば変更して下さい 1997/11/13  By T.Yamaguchi */
#if (PRO_PRINT_FACE_UP == DISABLE)
 /* Modify start by SMuratec 夏 2004/6/8 */
 #if defined (STOCKHM2)
	UWORD max_page;

	max_page = MEM_CountMaxPage(SYS_MEM_MULTI_COPY_FILE, (UWORD)SYB_MultiCopyWritePoint, MEM_IGNORE_BOX_NUMBER);

	if (max_page == MEM_NO_INDEX) {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_EMPTY;
	}
	else {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_PRINT;	/* add by J.M 1994/05/13 */

		/*---------------------------------------------------------------------
		** ノンソートコピーの場合は、１ページ蓄積終了後にプリントを開始しているので既にインクリメントされている。
		** だから、ExecutiveNumberは読取開始時に１にセットしておき、ここではセットしません。
		*/
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = MEM_CountMaxPage(SYS_MEM_MULTI_COPY_FILE, (UWORD)SYB_MultiCopyWritePoint, MEM_IGNORE_BOX_NUMBER);
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 1;
	}
	SYB_MultiCopyWritePoint++;
	if (SYB_MultiCopyWritePoint >= SYS_MULTI_COPY_MAX)
		SYB_MultiCopyWritePoint = 0;

 #else
 
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_PRINT;	/* add by J.M 1994/05/13 */
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].ExecutiveNumber = 1;
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = MEM_CountTotalPage(SYS_MEM_MULTI_COPY_FILE, (UWORD)SYB_MultiCopyWritePoint, MEM_IGNORE_BOX_NUMBER);

/* #if (PRO_PRINT_FACE_UP == ENABLE)
**	if (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType == SYS_SORT) {
**		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage;
**	}
** #else /* Face Down
*/
	SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 1;
/* #endif */
	SYB_MultiCopyWritePoint++;
	if (SYB_MultiCopyWritePoint >= SYS_MULTI_COPY_MAX)
		SYB_MultiCopyWritePoint = 0;
 #endif
/* Modify end by SMuratec 夏 2004/6/8 */ 
#else
	/* ノンソートの仕様がある場合はこちらを使う By M.Tachiban 1997/08/20 */

	UWORD max_page;

	max_page = MEM_CountMaxPage(SYS_MEM_MULTI_COPY_FILE, (UWORD)SYB_MultiCopyWritePoint, MEM_IGNORE_BOX_NUMBER);

	if (max_page == MEM_NO_INDEX) {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_EMPTY;
	}
	else {
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Status = SYS_MCOPY_PRINT;	/* add by J.M 1994/05/13 */

		/*---------------------------------------------------------------------
		** ノンソートコピーの場合は、１ページ蓄積終了後にプリントを開始しているので既にインクリメントされている。
		** だから、ExecutiveNumberは読取開始時に１にセットしておき、ここではセットしません。
		*/
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage = MEM_CountMaxPage(SYS_MEM_MULTI_COPY_FILE, (UWORD)SYB_MultiCopyWritePoint, MEM_IGNORE_BOX_NUMBER);

#if (PRO_PRINT_FACE_UP == ENABLE)
		/*---------------------------------------------------------------------
		** ノンソートコピーの場合は、１ページ蓄積終了後にプリントを開始しているのでインクリメントされている。
		** だから、PrintPageは読取開始時に１にセットしておき、ここではセットしません。
		*/
		if (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].SortType == SYS_SORT) {
			SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = SYB_MultiCopyFile[SYB_MultiCopyWritePoint].StorePage;
		}
#else /* Face Down */
		SYB_MultiCopyFile[SYB_MultiCopyWritePoint].PrintPage = 1;
#endif
	}
	SYB_MultiCopyWritePoint++;
	if (SYB_MultiCopyWritePoint >= SYS_MULTI_COPY_MAX)
		SYB_MultiCopyWritePoint = 0;

#endif
}


/** Module Header For CIM-E ********************************************
		module		:	[手差し・コピー・コマンドの登録終了]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[]
		language	:	[]
		keyword		:	[]
		date		:	[Aug.07.1996]
		author		:	[曽根岡拓]
************************************************************************/
void ManualCopyDocStoreOK()
{
	UWORD max_page;	/* 1997/01/24 */

	max_page = MEM_CountMaxPage(SYS_MEM_MANUAL_COPY_FILE, (UWORD)0, MEM_IGNORE_BOX_NUMBER);

	if (max_page == MEM_NO_INDEX) {
		SYB_ManualCopyFile.Status = SYS_MCOPY_EMPTY;
	}
	else {
		SYB_ManualCopyFile.Status = SYS_MCOPY_PRINT;
		SYB_ManualCopyFile.ExecutiveNumber = 1;	/* H.Yoshikawa 1996/12/03 */

		SYB_ManualCopyFile.StorePage = MEM_CountMaxPage(SYS_MEM_MANUAL_COPY_FILE, (UWORD)SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
#if (PRO_PRINT_FACE_UP == ENABLE)
		if (SYB_ManualCopyFile.SortType == SYS_SORT) {
			SYB_ManualCopyFile.PrintPage = SYB_ManualCopyFile.StorePage;
		}
#else /* Face Down */
		SYB_ManualCopyFile.PrintPage = 1;
#endif
	}
}


/*************************************************************************
	module		:[マルチコピーでメモリオーバー時の処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		MultiCopyDocStoreOK() を SYS_MCOPY_MEMORY_OVER にしただけ
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/18]
	author		:[竹内茂樹]
*************************************************************************/
void	MultiCopyDocStoreMemoryOver( void )
{
	struct SYS_MultiCopyData_t	* multi_copy_file;

	multi_copy_file = &SYB_MultiCopyFile[SYB_MultiCopyWritePoint];

	multi_copy_file->Status = SYS_MCOPY_MEMORY_OVER;
	multi_copy_file->StorePage = MEM_CountMaxPage( SYS_MEM_MULTI_COPY_FILE, (UWORD)SYB_MultiCopyWritePoint, MEM_IGNORE_BOX_NUMBER);

#if (PRO_PRINT_FACE_UP == ENABLE)
	if (multi_copy_file->SortType == SYS_SORT) {
		multi_copy_file->PrintPage = multi_copy_file->StorePage;
	}
#else /* Face Down */
	multi_copy_file->PrintPage = 1;
#endif

	SYB_MultiCopyWritePoint++;
	if (SYB_MultiCopyWritePoint >= SYS_MULTI_COPY_MAX) {
		SYB_MultiCopyWritePoint = 0;
	}
}


/*************************************************************************
	module		:[手差しコピーでメモリオーバー時の処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		ManualCopyDocStoreOK() を SYS_MCOPY_MEMORY_OVER にしただけ
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CMN]
	date		:[1996/12/18]
	author		:[竹内茂樹]
*************************************************************************/
void	ManualCopyDocStoreMemoryOver( void )
{
	SYB_ManualCopyFile.Status = SYS_MCOPY_MEMORY_OVER;
	SYB_ManualCopyFile.ExecutiveNumber = 1;	/* H.Yoshikawa 1996/12/03 */

	SYB_ManualCopyFile.StorePage = MEM_CountMaxPage(SYS_MEM_MANUAL_COPY_FILE, (UWORD)SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
#if (PRO_PRINT_FACE_UP == ENABLE)
	if (SYB_ManualCopyFile.SortType == SYS_SORT) {
		SYB_ManualCopyFile.PrintPage = SYB_ManualCopyFile.StorePage;
	}
#else /* Face Down */
	SYB_ManualCopyFile.PrintPage = 1;
#endif
}

#if (PRO_F_CODE == ENABLE)
/* Module Header For CIM-E ********************************************
		module		:	[ＦコードＢＯＸ原稿蓄積終了]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[1997/03/12]
		author		:	[山口哲治]
************************************************************************/
void FcodeDocStoreOK(UBYTE box_number)
{
	UBYTE box_position;

	if (box_number != 0) {
		box_position = (UBYTE)(box_number - 1);
	}
	else {
		/* Ｂｏｘ番号０は有り得ない */
		SaveReturnAddressAndJumpBegin();	/* ここに来るのはおかしい */
	}

	if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_BULLETIN_BOX) {	/* 掲示板ＢＯＸなら */
		if (SYB_SubAddressBoxTable[box_position].DataStatus == SYS_SUB_ADDRESS_BOX_STR_TX) {
			SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_TXING;
		}
		else {
			SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
		}
		/* 掲示板原稿保持期間は設定できないため消去時間は0xffffffffを代入 */
		if (SYB_SubAddressBoxTable[box_position].HoldTime == 0 ) {
			SYB_SubAddressBoxTable[box_position].ErasedTime  = (UDWORD)0xffffffff;
		}
		else {	/** 消去時間 現在時間（秒）＋ 保持期間（日）× ２４時間×６０分×６０秒 */
			SYB_SubAddressBoxTable[box_position].ErasedTime  = ( SYB_CurrentTime ) + ( (UDWORD)SYB_SubAddressBoxTable[box_position].HoldTime * 24L * 60L * 60L );
		}
		SYB_SubAddressBoxTable[box_position].ScnStoringNo = 0;	/* 蓄積中原稿番号クリア */
		SYB_SubAddressBoxTable[box_position].StoredDocBit |= (UDWORD)(1 << (SYS_DocumentStoreNo - 1));	/* 蓄積ファイル番号セット */
#if 0	/* Del 1997/04/30  By T.Yamaguchi */
//		if (SYS_DocumentStoreNo != 31) {
//			SYB_SubAddressBoxTable[box_position].StoredDocBit |= (UDWORD)(1 << (SYS_DocumentStoreNo - 1));	/* 蓄積ファイル番号セット */
//		}
//		else {	/* ファイル上書き処理 前蓄積ファイルありの場合は原稿を消去して、ファイル番号３１を１へ変換する */
//			if (MEM_ClearBoxNoAppintDoc(SYS_DocumentStoreItem, SYS_DocumentStoreBoxNumber, SYS_DocumentStoreNo) != MEM_OK) {
//				SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
//			}
//			if (MEM_IndexConvert(SYS_DocumentStoreItem, SYS_DocumentStoreBoxNumber,SYS_DocumentStoreNo, 1) != MEM_OK) {
//				SaveReturnAddressAndJumpBegin();	/* なったらアカンの */
//			}
//			SYB_SubAddressBoxTable[box_position].StoredDocBit = 1;	/* 受信蓄積ファイル番号リセット */
//		}
#endif
		SYB_SelectPollDocumentStatus = 1;	/* ＦコードＢＯＸに蓄積原稿あり */
	}
	/* Ｆコード親展ＢＯＸには蓄積はできない仕様なので何も処理しない */
}


/** Module Header For CIM-E ********************************************
		module		:	[Ｆコード原稿蓄積キャンセル]
		function	:	[]
		return		:	[]
		common		:	[]
		condition	:	[]
		comment		:	[]
		machine		:	[SH7043]
		language	:	[SHC]
		keyword		:	[MAN]
		date		:	[1997/03/12]
		author		:	[山口哲治]
************************************************************************/
void FcodeDocStoreNG(UBYTE box_number)
{
	UBYTE box_position;

	box_position = (UBYTE)(box_number - 1);

	if (SYB_SubAddressBoxTable[box_position].Status == SUB_ADDRESS_BULLETIN_BOX) {	/* 掲示板ＢＯＸなら */
		if (MEM_CountTotalBoxPage(SYS_DocumentStoreItem, box_number) == MEM_NO_INDEX) {	/** 以前にも受信・蓄積原稿がない */
			if (SYB_SubAddressBoxTable[box_position].DataStatus == SYS_SUB_ADDRESS_BOX_STR_TX) {
				SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_TXING;
			}
			else {
				SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
			}
		}
		else {	/* 以前に蓄積された原稿がある */
			if (SYB_SubAddressBoxTable[box_position].DataStatus == SYS_SUB_ADDRESS_BOX_STR_TX) {
				SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_TXING;
			}
			else {
				SYB_SubAddressBoxTable[box_position].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
			}
		}
		SYB_SubAddressBoxTable[box_position].ScnStoringNo = 0;	/* 蓄積中原稿番号クリア */
	}
	/* Ｆコード親展ＢＯＸには蓄積はできない仕様なので何も処理しない */
}
#endif
/*************************************************************************
	module		:[電源投入時ストップキーが押されているか]
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
	date		:[1994/11/14]
	author		:[村田]
*************************************************************************/
UBYTE CheckInitializeKeyON(void)
{
	return(0);
}


/*************************************************************************
	module		:[コマンドファイルのバックアップ処理]
	function	:[
		1. 即時スキャナ送信、スキャナ送信予約に関してはバックアップしない
		 　コマンド消去のリストがプリントされる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1994/11/16]
	author		:[村田]
*************************************************************************/
void BackupCommandFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)

	UWORD i;
	struct SYS_CommandData_t *com_ptr;

	for (i = 0; i < SYS_COM_FILE_MAX; i ++)	 {
		com_ptr = &SYB_CommandFile[i];
		if (com_ptr->Status == SYS_CMD_SETTING) {	/* コマンド獲得中又は原稿蓄積中なら */
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)i);	/* 蓄積原稿なしでもこの関数を呼びます（一応）*/
		}
		else if (com_ptr->Status == SYS_CMD_EMPTY) {	/* ｽﾃｰﾀｽがｴﾝﾌﾟﾃｨでも原稿及びスケジューラが残っている可能性もある1994/11/14 Y.Murata */
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)i);	/* 蓄積原稿なしでもこの関数を呼びます（一応）*/
		}
		else if (com_ptr->Status == SYS_CMD_WAITING) {		/* 予約中であれば *//* 1994/11/18 Y.Murata */
			if (CheckScannerCommand((UBYTE)i) == 1) {	/* ｽｷｬﾅ送信 */
				CancelExecQueue(SYS_COMMAND_TRX, (UBYTE)i);		/* ｽｹｼﾞｭｰﾗｰｸﾘｱ */
				SYS_ScannerComEraseListRequest = 1;
				com_ptr->Status = SYS_CMD_POWER_OFF;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[i] = SYS_CMD_POWER_OFF;
#endif
			}
			else {	/* ﾒﾓﾘ送信 */
				CancelExecQueue(SYS_COMMAND_TRX, (UBYTE)i);		/* ｽｹｼﾞｭｰﾗｰｸﾘｱ */
			}
		}
		else if (com_ptr->Status == SYS_CMD_EXECUTE) {	/* 実行中 */
			if (CheckScannerCommand((UBYTE)i) == 1) {	/* ｽｷｬﾅ送信 */
				CancelExecQueue(SYS_COMMAND_TRX, (UBYTE)i);		/* ｽｹｼﾞｭｰﾗｰｸﾘｱ */
				SYS_ScannerComEraseListRequest = 1;
				com_ptr->Status = SYS_CMD_POWER_OFF;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[i] = SYS_CMD_POWER_OFF;
#endif
			}
		}
		else if (com_ptr->Status == SYS_CMD_POWER_OFF) {	/* ｺﾏﾝﾄﾞﾌｧｲﾙを空けるため */
			SYS_ScannerComEraseListRequest = 1;
		}
		else if (com_ptr->Status == SYS_CMD_ERASED) {
			CMN_ClearCommandArea(SYS_COMMAND_TRX, (UBYTE)i);	/* 蓄積原稿なしでもこの関数を呼びます（一応）*/
		}
	}
#endif
}

#if (0)	/* ＩＣＨＯＵで削除予定 */
//*************************************************************************
//	module		:[メモリ代行受信管理データのバックアップ処理]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[MAN]
//	date		:[1994/11/16]
//	author		:[村田]
//*************************************************************************/
//void BackupMemoryRxPrintFile(void)
//{
//#if (PRO_DRAM_BACKUP == ENABLE)
//
//	UWORD	i;
//	struct MEM_IndexData_t IndexP;
//
//	/** ポインタ再設定処理 －初級偏－ */
//	if (SYB_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX) {
//		SYB_MemoryRxPrintReadPoint = 0;
//	}
//	if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX) {
//		SYB_MemoryRxPrintWritePoint = 0;
//	}
//
//	if (MEM_CountTotalPage(SYS_MEM_RX_FILE, SYB_MemoryRxPrintReadPoint, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) {	/** リードポインタの原稿が無いとき */
//
//		/*-----------------------------------*/
//		/** リードポインタの管理データ初期化 */
//		/*-----------------------------------*/
//		SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage = 0;
//		SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].PrintPage = 1;
//		SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].ErasePage = 1;
//		SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Protect	= SYS_PROTECT_OFF; /*プリントプロテクト初期化 1995.12.22 Eguchi */
//		SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Status	= SYS_MEMORY_RX_EMPTY;
//
//		if (SYB_MemoryRxPrintReadPoint + 1 >= SYS_MEMORY_RX_MAX) {
//			i = 0;
//		}
//		else {
//			i = SYB_MemoryRxPrintReadPoint + 1;
//		}
//		if ((SYB_MemoryRxPrintReadPoint == SYB_MemoryRxPrintWritePoint) &&
//			(SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_PRINT)) {	/** リードとライトが同じでリードの次ステータスがＰＲＩＮＴ */
//			/*--------------------------------------------------*/
//			/* 代行受信満杯で１通信分プリントして消去中に電源断 */
//			/*--------------------------------------------------*/
//
//			/** リードポインタ更新 */
//			SYB_MemoryRxPrintReadPoint++;
//			if (SYB_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX)  {
//				SYB_MemoryRxPrintReadPoint = 0;
//			}
//		}
//		else if (SYB_MemoryRxPrintReadPoint != SYB_MemoryRxPrintWritePoint) {	/** リードとライトポインタが同じでなければ */
//			/*---------------------------------------------------*/
//			/* リードポインタは,原稿が無いときはライトと同じはず */
//			/* 同じでないとゆうことはプリントして消去中に電源断	 */
//			/*---------------------------------------------------*/
//
//			/** リードポインタ更新 */
//			SYB_MemoryRxPrintReadPoint++;
//			if (SYB_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX)  {
//				SYB_MemoryRxPrintReadPoint = 0;
//			}
//			/*-------------------------------------------------------------*/
//			/** リードとライトポインタが違う時の処理					   */
//			/** 受信中に前回のプリントが完了したと同時に電源断した時の処理 */
//			/*-------------------------------------------------------------*/
//
//			if (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_EMPTY) {	/** ライトのステータスがＥＭＰＴＹ */
//
//				/** 正常（なにもしない）*/
//			}
//			else if (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_STORE) {	/** ライトのステータスがＳＴＯＲＥ */
//				/*----------------------------------------------------*/
//				/* このポインタの原稿はまだ１枚もプリントされていない */
//				/* なぜなら、リードとライトのポインタが違うから		  */
//				/*----------------------------------------------------*/
//
//				/*----------------------------*/
//				/* 原稿の確認（ページ再設定） */
//				/*----------------------------*/
//				if (MEM_CountTotalPage(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** ライトの原稿が有る時 */
//
//					/** ライトの管理データ PrintPage <- 再設定 */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].PrintPage = 1;
//
//					/** ライトの管理データ ErasePage <- 再設定 */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].ErasePage = 1;
//
//					/** ライトの管理データ StorePage <- 原稿枚数 */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage = MEM_CountTotalPage(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER);
//
//					/** ライトの管理データ Protectの再設定 */
//					if ((SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage == 1) /* １ページだけ受信完了 */
//					&&	(SYB_SecurityRxModeFlag								  == 1) /* プロテクト設定がＯＮ */
//					&&	(SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect == SYS_PROTECT_OFF)) {/*プロテクトがかかっていない */
//						/* １ページ受信完了して、ステータスをＳＴＯＲＥにセット後、プロテクトの設定を
//							行う前に電源ＯＦＦした場合 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect = SYS_PROTECT_ON;
//					}
//
//					/** ライトのステータスをＰＲＩＮＴに変更 */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_PRINT;
//
//					/** ライトポインタ更新 */
//					SYB_MemoryRxPrintWritePoint++;
//					if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
//						SYB_MemoryRxPrintWritePoint = 0;
//					}
//				}
//				else {	/** ライトの原稿が無い時 */
//
//					/** ライトの管理データを初期化 */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage = 0;
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].PrintPage = 1;
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].ErasePage = 1;
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect	 = SYS_PROTECT_OFF; /* プリントプロテクトＯＦＦ 1995/12/22 Eguchi */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status	 = SYS_MEMORY_RX_EMPTY;
//				}
//			}
//			else if (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_PRINT) {	/** ライトのステータスがＰＲＩＮＴ */
//				/*------------------------------------------------------------------------*/
//				/* ﾘｰﾄﾞのｽﾃｰﾀｽが"EMPTY"で,ﾗｲﾄのｽﾃｰﾀｽが"PRINT"の場合は起こり得ないと思う？ */
//				/*------------------------------------------------------------------------*/
//
//			}
//
//		}
//	}
//	else {	/** リードポイントの位置に原稿が有るとき */
//
//		if (SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Status == SYS_MEMORY_RX_EMPTY) {	/** リードのステータスがＥＭＰＴＹ */
//			/* ﾒﾓﾘ受信で１枚受信しｽﾃｰﾀｽが”ＳＲＯＲＥ”になるまでに電源断 */
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage = 0;
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].PrintPage = 1;
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].ErasePage = 1;
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Protect	= SYS_PROTECT_OFF; /* プリントプロテクト初期化1995/12/22 Eguchi */
//			/* MEM_ClearDoc(SYS_MEM_RX_FILE, SYB_MemoryRxPrintReadPoint, MEM_IGNORE_BOX_NUMBER);	ﾃﾞｩｱﾙｵｰﾌﾟﾝの可能性もあるので 1994/12/02 */
//			/* MEM_ClearDocAndFATArea(SYS_MEM_RX_FILE, SYB_MemoryRxPrintReadPoint); */
//			IndexP.Item = SYS_MEM_RX_FILE;
//			IndexP.No	= SYB_MemoryRxPrintReadPoint;
//			IndexP.Page = 1;
//			MEM_ClearPageAndFATArea(&IndexP);
//		}
//		else if (SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Status == SYS_MEMORY_RX_STORE) {	/** リードのステータスがＳＴＯＲＥ */
//			/*----------------------------------*/
//			/* この時リードとライトが同じはず	*/
//			/* 受信しながらプリントしているかも */
//			/*----------------------------------*/
//
//			/** リードの管理データ PrintPage <- 再設定 */
//			IndexP.Item = SYS_MEM_RX_FILE;
//			IndexP.No	= SYB_MemoryRxPrintReadPoint;
//
//			for (i = 1; i <= (SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage + (UBYTE)1); i++) {
//				IndexP.Page = i;
//				if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].PrintPage = i;
//					break;
//				}
//			}
//			/** リードの管理データ ErasePage <- 再設定 */
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].ErasePage = i;
//
//			/** リードの管理データ StorePage <- 蓄積ページ数（ページ再設定）*/
//			IndexP.Item = SYS_MEM_RX_FILE;
//			IndexP.No	= SYB_MemoryRxPrintReadPoint;
//
//			for (i = (SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage + 1); i > 0; i--) {
//				IndexP.Page = i;
//				if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage = (UBYTE)i;
//					break;
//				}
//			}
//
//			/** プロテクト状態の再設定 1995/12/22 Eguchi TBD*/
//			if ((SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage == 1)
//			&&	(SYB_SecurityRxModeFlag								  == 1) /* プロテクト設定がＯＮ */
//			&&	(SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Protect == SYS_PROTECT_OFF)) {
//				/*１ページ受信完了し、ステータスをSTOREDにセットし、プロテクト状態をセットする
//				  前に電源ＯＦＦされた場合 */
//				SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Protect = SYS_PROTECT_ON;
//			}
//
//			/** リードの管理データ Status	 <- ＰＲＩＮＴ */
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Status = SYS_MEMORY_RX_PRINT;
//
//			/** ライトポインタ更新 */
//			SYB_MemoryRxPrintWritePoint++;
//			if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
//				SYB_MemoryRxPrintWritePoint = 0;
//			}
//		}
//		else if (SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].Status == SYS_MEMORY_RX_PRINT) {	/** リードのステータスがＰＲＩＮＴ */
//
//			if (SYB_MemoryRxPrintWritePoint + 1 >= SYS_MEMORY_RX_MAX) {
//				i = 0;
//			}
//			else {
//				i = SYB_MemoryRxPrintWritePoint + 1;
//			}
//			if ((SYB_MemoryRxPrintReadPoint == SYB_MemoryRxPrintWritePoint) &&
//				(SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_EMPTY)) {	/** リードとライトのポインタが同じ && ライトポインタの次ステータスがＥＭＰＴＹ */
//
//				/** ライトポインタ更新 */
//				SYB_MemoryRxPrintWritePoint++;
//				if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
//					SYB_MemoryRxPrintWritePoint = 0;
//				}
//			}
//			else {	/** リードとライトのポインタが違う || 代行受信が満杯の時 */
//
//				if (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_EMPTY) {	/** ライトのステータスがＥＭＰＴＹ */
//
//					/* ﾒﾓﾘ受信で１枚受信しｽﾃｰﾀｽが”ＳＲＯＲＥ”になるまでに電源断 */
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage = 0;
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].PrintPage = 1;
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].ErasePage = 1;
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect	 = SYS_PROTECT_OFF;
//					/* MEM_ClearDoc(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER);	ﾃﾞｩｱﾙｵｰﾌﾟﾝの可能性もあるので 1994/12/02 */
//					/* MEM_ClearDocAndFATArea(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint); */
//					IndexP.Item = SYS_MEM_RX_FILE;
//					IndexP.No	= SYB_MemoryRxPrintWritePoint;
//					IndexP.Page = 1;
//					MEM_ClearPageAndFATArea(&IndexP);
//				}
//				else if (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_STORE) {	/** ライトのステータスがＳＴＯＲＥ */
//					/*----------------------------------------------------------*/
//					/* ここに来るとゆうことは、リードとライトが違う、			*/
//					/* つまりこのポインタの原稿はまだ１枚もプリントされていない */
//					/*----------------------------------------------------------*/
//
//					/*----------------------------*/
//					/* 原稿の確認（ページ再設定） */
//					/*----------------------------*/
//					if (MEM_CountTotalPage(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** ライトの原稿が有る時 */
//
//						/** ライトの管理データ PrintPage <- 再設定 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].PrintPage = 1;
//
//						/** ライトの管理データ ErasePage <- 再設定 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].ErasePage = 1;
//
//						/** ライトの管理データ StorePage <- 原稿枚数 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage = (UBYTE)MEM_CountTotalPage(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER);
//
//						/** ライトの管理データ Protect の再設定 1995/12/22 Eguchi */
//						if ((SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage == 1)
//						&&	(SYB_SecurityRxModeFlag								  == 1) /* プロテクト設定がＯＮ */
//						&&	(SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect == SYS_PROTECT_OFF)) {
//							/*１ページ受信完了し、ステータスをSTOREDにセットし、プロテクト状態をセットする
//							  前に電源ＯＦＦされた場合 */
//							SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect = SYS_PROTECT_ON;
//						}
//
//						/** ライトのステータスをＰＲＩＮＴに変更 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status = SYS_MEMORY_RX_PRINT;
//
//						/** ライトポインタ更新 */
//						SYB_MemoryRxPrintWritePoint++;
//						if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
//							SYB_MemoryRxPrintWritePoint = 0;
//						}
//					}
//					else {	/** ライトの原稿が無い時 */
//
//						/** ライトの管理データを初期化 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage = 0;
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].PrintPage = 1;
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].ErasePage = 1;
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Protect	 = SYS_PROTECT_OFF;/*プロテクト状態初期化 1995/12/22 Eguchi */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status	 = SYS_MEMORY_RX_EMPTY;
//					}
//				}
//				else if (SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].Status == SYS_MEMORY_RX_PRINT) {	/** ライトのステータスがＰＲＩＮＴ */
//
//					/*----------------------------*/
//					/* ポインタの確認（再設定）	  */
//					/*----------------------------*/
//					if (SYB_MemoryRxPrintReadPoint == SYB_MemoryRxPrintWritePoint) {	/** リードとライトのポインタが同じ */
//
//						/** なにもしない（代行受信満杯）*/
//					}
//					else {
//						/** ライトの管理データ PrintPage <- 再設定 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].PrintPage = 1;
//
//						/** ライトの管理データ ErasePage <- 再設定 */
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].ErasePage = 1;
//
//						/** ライトの管理データ StorePage <- 蓄積ページ数（ページ再設定）*/
//						SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint].StorePage = (UBYTE)MEM_CountTotalPage(SYS_MEM_RX_FILE, SYB_MemoryRxPrintWritePoint, MEM_IGNORE_BOX_NUMBER);
//
//						/** プロテクト状態はそのまま? 1995/12/22 Eguchi TBD */
//
//						/** ライトポインタ更新 */
//						SYB_MemoryRxPrintWritePoint++;
//						if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
//							SYB_MemoryRxPrintWritePoint = 0;
//						}
//					}
//				}
//			}
//
//			/*----------------------------*/
//			/* 原稿の確認（ページ再設定） */
//			/*----------------------------*/
//
//			/** リードの管理データ PrintPage <- 再設定 */
//			IndexP.Item = SYS_MEM_RX_FILE;
//			IndexP.No	= SYB_MemoryRxPrintReadPoint;
//
//			for (i = 1; i <= SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].StorePage; i++) {
//				IndexP.Page = i;
//				if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
//					SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].PrintPage = (UBYTE)i;
//					break;
//				}
//			}
//
//			/** リードの管理データ ErasePage <- 再設定 */
//			SYB_MemoryRxPrint[SYB_MemoryRxPrintReadPoint].ErasePage = (UBYTE)i;
//
//			/** リードの管理データ StorePage <- 蓄積ページ数・再設定不要？ */
//			/** ステータスがプリントであるから蓄積は完了している		   */
//		}
//	}
//#endif
//}
#endif

/*************************************************************************
	module		:[マルチ回線仕様の受信原稿管理ファイルを使用した場合のＤＲＡＭバックアップ処理]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[PRN]
	date		:[1996/08/20]
	author		:[吉川弘康]
*************************************************************************/
void BackupMemoryRxPrintFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)
	UWORD	i;
	UBYTE mprint_num;
	struct MEM_IndexData_t IndexP;
	struct SYS_MemoryRxPrintData_t *mprint_ptr;

	/** ポインタ再設定処理 －初級偏－ */
#if (0)	/* ＩＣＨＯＵでは、使用する時に一時的に使用する変数となったので、この変数はあてになりません */
//	if (MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX) {
//		MemoryRxPrintReadPoint = 0;
//	}
#endif

	if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX) {
		SYB_MemoryRxPrintWritePoint = 0;
	}

	for (mprint_num = 0; mprint_num < SYS_MEMORY_RX_MAX; mprint_num++) {
		mprint_ptr = &SYB_MemoryRxPrint[mprint_num];
		switch (mprint_ptr->Status) {
		case SYS_MEMORY_RX_EMPTY:
		case SYS_MEMORY_RX_SETTING:
			mprint_ptr->Status    = SYS_MEMORY_RX_EMPTY;
			mprint_ptr->StorePage = 0;
			mprint_ptr->RotatePage = 1;
			mprint_ptr->PrintPage = 1;
			mprint_ptr->ErasePage = 1;
			mprint_ptr->ReceiveTime = 0;
			/*------------------------------------------------------------
			** メモリ受信で１枚受信しステータスが”ＳＴＯＲＥ”になるまでに電源断
			*/
			if (MEM_CountTotalPage(SYS_MEM_RX_FILE, mprint_num, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				/* MEM_ClearDoc(SYS_MEM_RX_FILE, mprint_num, MEM_IGNORE_BOX_NUMBER);	ﾃﾞｩｱﾙｵｰﾌﾟﾝの可能性もあるので 1994/12/02 */
				/* MEM_ClearDocAndFATArea(SYS_MEM_RX_FILE, mprint_num); */
				IndexP.Item = SYS_MEM_RX_FILE;
				IndexP.No   = mprint_num;
				IndexP.Page = 1;
				IndexP.BoxNumber = MEM_IGNORE_BOX_NUMBER;
				MEM_ClearPageAndFATArea(&IndexP);
			}
			break;
		/*-----------------------------------------------------------------
		** メモリ受信中の場合
		** 受信しながらプリントしている場合は、プリント済ページは既に消去されている
		*/
		case SYS_MEMORY_RX_STORE:
		case SYS_MEMORY_RX_PRINT:
#if (PRO_REVERSE_PRINT == ENABLE)	/* By M.Tachibana 1998/05/20 */
		case SYS_MEMORY_RX_STORE_PRINT:
		case SYS_MEMORY_RX_FAST_PRINT:
#endif
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/20 */
			/*------------------------------------------------------------
			** プリント済ページ数をセットする
			** 消去済ページ数をセットする
			*/
			IndexP.Item = SYS_MEM_RX_FILE;
			IndexP.No   = mprint_num;
			IndexP.BoxNumber = MEM_IGNORE_BOX_NUMBER;
			for (i = 1; i <= (mprint_ptr->StorePage + 1); i++) {
				IndexP.Page = i;
				if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
					mprint_ptr->PrintPage = i;
					break;
				}
			}
			mprint_ptr->ErasePage = i;

			/*------------------------------------------------------------
			** 蓄積ページ数をセットする
			*/
			IndexP.Item = SYS_MEM_RX_FILE;
			IndexP.No   = mprint_num;
			IndexP.BoxNumber = MEM_IGNORE_BOX_NUMBER;

			for (i = (mprint_ptr->StorePage + 1); i > 0; i--) {
				IndexP.Page = i;
				if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
					mprint_ptr->StorePage = i;
					break;
				}
			}

			/*------------------------------------------------------------
			** ステータスをプリント待ち状態にセットする
			*/
			mprint_ptr->Status = SYS_MEMORY_RX_PRINT;

#else
			/*-------------------------------------------------------------
			** 逆順プリントの場合
			*/
/*			if (CHK_UNI_RxDocReversePrint() && (mprint_ptr->Status == SYS_MEMORY_RX_PRINT)) { By M.Tachibana 1999/12/27 */
			if (CHK_UNI_RxDocReversePrint() &&
			   ((mprint_ptr->Status == SYS_MEMORY_RX_STORE) || (mprint_ptr->Status == SYS_MEMORY_RX_PRINT))) {
				/*------------------------------------------------------------
				** プリント済ページ数をセットする
				** 消去済ページ数をセットする
				*/
				IndexP.Item = SYS_MEM_RX_FILE;
				IndexP.No   = mprint_num;
				IndexP.BoxNumber = MEM_IGNORE_BOX_NUMBER;

				for (i = (mprint_ptr->StorePage + 1); i > 0; i--) {
					IndexP.Page = i;
					if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
						mprint_ptr->PrintPage = i;
						break;
					}
				}
				mprint_ptr->ErasePage = i;	/* 参照しているところ無し。参照する場合は変更が必要 */

				/*------------------------------------------------------------
				** 蓄積ページ数をセットする
				** 蓄積ページは確定しているため、新たに設定する必要なし
				*/
				mprint_ptr->StorePage = i;	/* Add By M.Tachibana 1999/12/27 */

			}
			else {
				/*------------------------------------------------------------
				** プリント済ページ数をセットする
				** 消去済ページ数をセットする
				*/
				IndexP.Item = SYS_MEM_RX_FILE;
				IndexP.No   = mprint_num;
				IndexP.BoxNumber = MEM_IGNORE_BOX_NUMBER;
				for (i = 1; i <= (mprint_ptr->StorePage + 1); i++) {
					IndexP.Page = i;
					if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
						mprint_ptr->PrintPage = i;
						break;
					}
				}
				mprint_ptr->ErasePage = i;

				/*------------------------------------------------------------
				** 蓄積ページ数をセットする
				*/
				IndexP.Item = SYS_MEM_RX_FILE;
				IndexP.No   = mprint_num;
				IndexP.BoxNumber = MEM_IGNORE_BOX_NUMBER;

				for (i = (mprint_ptr->StorePage + 1); i > 0; i--) {
					IndexP.Page = i;
					if (MEM_CheckIndexNo(&IndexP) != MEM_NO_INDEX) {
						mprint_ptr->StorePage = i;
						break;
					}
				}
			}

			/*------------------------------------------------------------
			** ステータスをプリント待ち状態にセットする
			*/
			if ((mprint_ptr->Status == SYS_MEMORY_RX_STORE) || (mprint_ptr->Status == SYS_MEMORY_RX_PRINT)) {
				mprint_ptr->Status = SYS_MEMORY_RX_PRINT;
			}
			else {
				mprint_ptr->Status = SYS_MEMORY_RX_FAST_PRINT;
			}
#endif

#if (0)
//			/*------------------------------------------------------------
//			** ライトポインタ更新
//			** ＩＣＨＯＵでは、受信した順番にSYS_MemoryRxPrintFile[]に格納する必要がない。
//			*/
//			MemoryRxPrintWritePoint++;
//			if (MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX)  {
//				MemoryRxPrintWritePoint = 0;
//			}
#endif
			break;
		case SYS_MEMORY_RX_POWEROFF:
			break;
		default:
			break;
		}
	}
#endif
}



/*************************************************************************
	module		:[スケジューラーのバックアップ処理]
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
	date		:[1994/11/24]
	author		:[村田]
*************************************************************************/
void BackupExecQueueFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)

	UWORD	i;
	struct SYS_ExecQueueData_t *exec_ptr;

	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++ ) {
		exec_ptr = &SYB_ExecQueue[i];
		if (exec_ptr->Status == SYS_EXEC_EXECUTE) {
			exec_ptr->Status = SYS_EXEC_WAITING;
			/*break; 2000/08/09 Y.Murata */
		}
		if (exec_ptr->Status == SYS_EXEC_FORWARD_EXECUTE) {
			exec_ptr->Status = SYS_EXEC_FORWARD_WAITING;
			/*break; 2000/08/09 Y.Murata */
		}
	}
#endif
}


/*************************************************************************
	module		:[親展受信のバックアップ処理]
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
	date		:[1994/11/24]
	author		:[村田]
*************************************************************************/
void BackupSecureFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)

	UWORD i;

	for (i = 0; i < SYS_MAILBOX_MAX; i ++) {
		if (MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** １枚以上正常原稿がある */
			if (SYB_MailBox[i].Status == SYS_MAILBOX_SET) {
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
				MEM_ClearDocAndFATArea(SYS_MEM_SECURE_RX_FILE, i, MEM_IGNORE_BOX_NUMBER);
			}
			else if (SYB_MailBox[i].Status != SYS_MAILBOX_RECEIVE) {	/** 親展受信中に瞬断が発生したので */
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_RCV_MSG;		/** 親展受信通知メッセージ */
				SYB_MailBox[i].ErasedTime = SYB_CurrentTime +
											(UDWORD)CHK_SecureMailHoldTime() * 24 * 60 * 60;	/** 消去時間 現在時間（秒）＋ 保持期間（日）× ２４時間×６０分×６０秒 */
				SYB_MailBox[i].Status = SYS_MAILBOX_RECEIVE;		/** ステータスを親展受信済にする */
/*				break;	要らんのちゃうか	*/
			}
		}
		else {		/** １枚も正常な原稿がない */	/* 1994/11/11 Y.Murata */
			if (SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING) {	/** １枚目受信中に電源断 */
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
				SYB_MailBox[i].Status = SYS_MAILBOX_SET;
			}
			else if (SYB_MailBox[i].Status == SYS_MAILBOX_SET) {		/* 1994/12/19 */
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
			}
			else if ((SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)		/* 1994/12/22 */
				  || (SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING)) {	/* 条件追加 1997/10/18  By T.Yamaguchi */
				SYS_ErasePixMemoryListRequest = 1;
			}
		}
	}


#endif
}


/*************************************************************************
	module		:[ポーリング原稿のバックアップ処理]
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
	date		:[1994/11/24]
	author		:[村田]
*************************************************************************/
void BackupPollingFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)
 #if (PRO_DB_POLLING_TX == ENABLE)

/*	UWORD i; */

	/*------------------------------------*/
	/* 検索ポーリング送信原稿蓄積中の処理 */
	/*------------------------------------*/
	/* できれば、マシンステータスを使用せずに、SYB_PollingDocumentStatusに蓄積中の識別を追加したい */
	/* if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) {
	** ミラー移動中でも、ｽｷｬﾅﾋﾞｼﾞｰになるため、蓄積中のｽｽﾃｰﾀｽを見る様変更 1997/10/18 by T.Yamaguchi
	*/
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {

		if (SYS_DocumentStoreItem == SYS_MEM_DB_POLLING_FILE) {
			MEM_ClearDoc(SYS_MEM_DB_POLLING_FILE, SYS_DocumentStoreNo, MEM_IGNORE_BOX_NUMBER);
#if 0	/* 1997/04/26  By T.Yamaguchi */
//			for (i = 0; i < 100; i ++) {
//				if (MEM_CountTotalPage(SYS_MEM_DB_POLLING_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
//					break;
//				}
//			}
//			if (i < 100) {
//				SYB_DB_PollingDocumentStatus = 1; /** 検索ポーリング有りセット */
//			}
//			else {
//				SYB_DB_PollingDocumentStatus = 0; /** 検索ポーリング無しセット */
//			}
#endif
		}
	}
	/*------------------------------------*/
	/* 検索ポーリング送信原稿消去中の処理 */
	/*------------------------------------*/	/* 1994/11/28 */
#if 0 /* 1997/04/26  By T.Yamaguchi */
//	for (i = 0; i < 100; i ++) {
//		if (MEM_CountTotalPage(SYS_MEM_DB_POLLING_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
//			break;
//		}
//	}
//	if (i < 100) {
#endif

	if (MEM_CountItemTotalPage(SYS_MEM_DB_POLLING_FILE) != MEM_NO_INDEX) {
		SYB_DB_PollingDocumentStatus = 1; /** 検索ポーリング有りセット */
	}
	else {
		SYB_DB_PollingDocumentStatus = 0; /** 検索ポーリング無しセット */
	}

	if (SYB_PowerDownListStatus & SYS_POWER_DB_POLL) {		/* 1994/12/22 Y.Murata */
		SYS_ErasePixMemoryListRequest = 1;
	}

 #endif
	/*----------------*/
	/* ポーリング原稿 */
	/*----------------*/
	if (SYB_PollingDocumentStatus == 0) {	/** ポーリング原稿がない */

		if (MEM_CountTotalPage(SYS_MEM_POLLING_FILE,0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** ポーリング原稿が有る */
			/*------------------------------------*/
			/* ポーリング原稿蓄積中に電源が落ちた */
			/*------------------------------------*/
			MEM_ClearDoc(SYS_MEM_POLLING_FILE, 0, MEM_IGNORE_BOX_NUMBER);		/** ポーリング原稿消去 */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/11 */
** 			SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
			SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
#endif

		}
	}
	else {

		if (MEM_CountTotalPage(SYS_MEM_POLLING_FILE,0, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX) {	/** ポーリング原稿が無い */
			SYB_PollingDocumentStatus = 0;			/** ポーリング原稿ステータスクリア */

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/11 */
** 			SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
			SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
#endif

		}
		/*----------------------------------------------------------------------------*/
		/* ポーリング原稿のステータスがたっていればポーリング原稿の蓄積が完了している */
		/* と言うことなのでポーリング原稿が存在すれば何もしない						  */
		/*----------------------------------------------------------------------------*/
		/* add 3line 1999/10/21 Y.Murata NAGANOより */
		else {
			SYB_PollingDocExclusiveFlag = SYS_EXIST_AND_NO_SENDING;	/* ポーリング原稿があるかどうかの変数 */
		}
	}

	if (SYB_PowerDownListStatus & SYS_POWER_POLLING) {	/* 1994/12/22 Y.Murata */
		SYS_ErasePixMemoryListRequest = 1;
	}

#endif
}

/*************************************************************************
	module		:[サブアドレスＢＯＸのバックアップ処理]
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
	date		:[1997/01/24]
	author		:[山口 哲治]
*************************************************************************/
void BackupSubAddressBoxFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)
 #if (PRO_F_CODE == ENABLE)
	UWORD i;
	UBYTE file_item;
	UWORD file_no;

	file_no = 0;

	for (i = 0; i < SUB_ADDRESS_BOX_MAX; i++) {
		if (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY) {
			if (SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_BULLETIN_BOX) {
				file_item = SYS_MEM_SUB_BULLETIN_FILE;
			}
			else if (SYB_SubAddressBoxTable[i].Status == SUB_ADDRESS_SECURE_BOX) {
				file_item = SYS_MEM_SUB_SECURE_FILE;
			}
			if (MEM_CountTotalBoxPage(file_item, (UBYTE)(i + 1)) != MEM_NO_INDEX) {	/* 原稿が１枚以上存在する */
				if (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_NO_SET) {	/* 蓄積なし */
					SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
					MEM_ClearDoc(file_item, MEM_ALL_NO, (UBYTE)(i + 1));
					SYB_SubAddressBoxTable[i].StoredDocBit = 0;
				}
				else if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVING)
					|| (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_RX)) {
					if (MEM_CountTotalPage(file_item,(UWORD)SYB_SubAddressBoxTable[i].RxStoringNo ,(UBYTE)(i + 1)) != MEM_NO_INDEX) {	/* 受信中に瞬断が発生したので */
						SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_RCV_MSG;
						if (SYB_SubAddressBoxTable[i].HoldTime == 0) {
							SYB_SubAddressBoxTable[i].ErasedTime = 0xffffffff;
						}
						else {
							SYB_SubAddressBoxTable[i].ErasedTime = SYB_CurrentTime +
											(UDWORD)SYB_SubAddressBoxTable[i].HoldTime * 24 * 60 * 60;	/** 消去時間 現在時間（秒）＋ 保持期間（日）× ２４時間×６０分×６０秒 */
						}
						SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_RECEIVE;			/** 受信済にする */
						file_no = (UWORD)SYB_SubAddressBoxTable[i].RxStoringNo;
						SYB_SubAddressBoxTable[i].StoredDocBit |= (UDWORD)(1 << (file_no - 1));	/* 蓄積ファイル番号セット */
					}
					else {
						if (MEM_CountTotalBoxPage(file_item, (UBYTE)(i + 1)) != MEM_NO_INDEX) {
							SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;			/** 蓄積済にする */
						}
						else {
							SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
						}
					}
				}
				else if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORING)	/* 蓄積中に瞬断が発生したので */
					||   (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STR_TX)) {
					file_no = (UWORD)SYB_SubAddressBoxTable[i].ScnStoringNo;
					/* 蓄積中の原稿は消去する */
					MEM_ClearDoc(file_item, file_no , (UBYTE)(i + 1));	/* 蓄積中の原稿を消去 */
					SYB_SubAddressBoxTable[i].ScnStoringNo = 0;
					if (MEM_CountTotalBoxPage(file_item, (UBYTE)(i + 1)) != MEM_NO_INDEX) {
						SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;			/** 蓄積済にする */
					}
					else {
						SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
					}
				}
				else if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_TXING)
					  || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_TX)
					  || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRINTING)) {
					SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
				}
			}
			else {		/** １枚も正常な原稿がない */
				if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVING)	/** １枚目受信中に電源断 */
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_RX)
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORING)	/** １枚目受信中に電源断 */
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STR_TX) ) {
					if (SYB_SubAddressBoxTable[i].StoredDocBit == 0) {
						SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
						SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
					}
					else {
						SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
						SYS_ErasePixMemoryListRequest = 1;
					}
				}
				else if (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_NO_SET) {
					SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
				}
				else if ((SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE)
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_TXING)
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRINTING)
				 || (SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_PRT_TX)) {
					SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
					SYS_ErasePixMemoryListRequest = 1;
				}
				SYB_SubAddressBoxTable[i].StoredDocBit = 0;	/* 蓄積ファイル番号りセット */
			}
		}
	}

	/*------------------------------------*/
	/* 掲示板にポーリング送信原稿中の処理 */
	/*------------------------------------*/
	if (MEM_CountItemTotalPage(SYS_MEM_SUB_BULLETIN_FILE) != MEM_NO_INDEX) {
		SYB_SelectPollDocumentStatus = 1; /** 選択ポーリング有りセット */
	}
	else {
		SYB_SelectPollDocumentStatus = 0; /** 選択ポーリング無しセット */
	}
 #endif
#endif
}

/*************************************************************************
	module		:[暗号化受信のバックアップ処理]
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
	date		:[1997/06/18]
	author		:[山口]
*************************************************************************/
void BackupCipherFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)
 #if (PRO_CIPHER == ENABLE)

	UWORD i;

	if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
	for (i = 0; i < SYS_CIPHERBOX_MAX; i ++) {
		if (MEM_CountTotalPage(SYS_MEM_CIPHER_RX_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** １枚以上正常原稿がある */
			if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_NO) {
				SYB_CipherBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
				SYB_CipherBox[i].StorePage = 0;
				SYB_CipherBox[i].PrintPage = 1;
				MEM_ClearDocAndFATArea(SYS_MEM_CIPHER_RX_FILE, i, MEM_IGNORE_BOX_NUMBER);
			}
			else if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVING) {	/** 暗号化受信中に瞬断が発生したので */
				SYB_CipherBox[i].MessageStatus = SYS_CIPHERBOX_RCV_MSG;		/** 暗号化受信通知メッセージ */
				SYB_CipherBox[i].Status = SYS_CIPHERBOX_RECEIVE;		/** ステータスを暗号化受信済にする */
			}
		}
		else {		/** １枚も正常な原稿がない */
			if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVING) {	/** １枚目受信中に電源断 */
				SYB_CipherBox[i].MessageStatus = SYS_CIPHERBOX_MSG_EMPTY;
				SYB_CipherBox[i].Status = SYS_CIPHERBOX_NO;
				SYB_CipherBox[i].StorePage = 0;
				SYB_CipherBox[i].PrintPage = 1;
			}
			else if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_NO) {
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
			}
			else if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVE) {
				SYS_ErasePixMemoryListRequest = 1;
			}
		}
	}
	}/**	By Y.Suzuki 1997/09/04	*/
 #endif
#endif
}

/*************************************************************************
	module		:[暗号化関連ファイルの消去処理]
	function	:[
		1.スクランブル前原稿、デスクランブル原稿は、消去する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/04/17]
	author		:[鈴木]
*************************************************************************/
void ClearCipherFile(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)
 #if (PRO_CIPHER == ENABLE)

	UWORD i;

	if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
		/* スクランブル前原稿消去 By Y.Suzuki 1998/04/17 */
		for (i = 0; i < SYS_COM_FILE_MAX; i ++) {
			if (MEM_CountTotalPage(SYS_MEM_CIPHER_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** １枚以上正常原稿がある */
				MEM_ClearDocAndFATArea(SYS_MEM_CIPHER_FILE, i, MEM_IGNORE_BOX_NUMBER);
			}
		}
		/* 送信予約暗号化復元原稿消去 By Y.Suzuki 1998/04/17 */
		for (i = 0; i < SYS_COM_FILE_MAX; i ++) {
			if (MEM_CountTotalPage(SYS_MEM_TX_DECIPHER_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** １枚以上正常原稿がある */
				MEM_ClearDocAndFATArea(SYS_MEM_TX_DECIPHER_FILE, i, MEM_IGNORE_BOX_NUMBER);
			}
		}
		/* 暗号化受信復元原稿消去 By Y.Suzuki 1998/04/17 */
		for (i = 0; i < SYS_COM_FILE_MAX; i ++) {
			if (MEM_CountTotalPage(SYS_MEM_DECIPHER_FILE, i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** １枚以上正常原稿がある */
				MEM_ClearDocAndFATArea(SYS_MEM_DECIPHER_FILE, i, MEM_IGNORE_BOX_NUMBER);
			}
		}
		SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;
	}
 #endif
#endif
}

/*************************************************************************
	module		:[一括送信のバックアップ処理]
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
	date		:[1994/12/08]
	author		:[鈴木]
*************************************************************************/
void BackupBatchTxFile(void)
{
#if (PRO_BATCH_TX == ENABLE)
 #if (PRO_DRAM_BACKUP == ENABLE)

	struct SYS_BatchTxData_t *bat_ptr;

	UWORD	i;
	UWORD	j;

	for (i = 0; i < SYS_BATCH_FILE_MAX; i++) {
		bat_ptr = &SYB_BatchTxFile[i];
		if (bat_ptr->Status == SYS_CMD_EMPTY) {
			CMN_ClearCommandArea(SYS_BATCH_TX, (UBYTE)i);
		}
		else if (bat_ptr->Status == SYS_CMD_SETTING) {
			for (j = 0; j < SYS_BATCH_INDEX_MAX; j++) {
				if (bat_ptr->IndexNo[j] == SYS_BAT_DOC_STORING) {
					break;
				}
			}
			if (j != SYS_BATCH_INDEX_MAX) {
				MEM_ClearDoc((UBYTE)(SYS_MEM_BATCH_TX_FILE1 + i), j, MEM_IGNORE_BOX_NUMBER);
				bat_ptr->IndexNo[j] = SYS_BAT_DOC_EMPTY;
			}
			for (j = 0; j < SYS_BATCH_INDEX_MAX; j++) {
				if (bat_ptr->IndexNo[j] != SYS_BAT_DOC_EMPTY) {
					break;
				}
			}
			if (j != SYS_BATCH_INDEX_MAX) {
				bat_ptr->Status = SYS_CMD_WAITING;
			}
			else {
				bat_ptr->Status = SYS_CMD_EMPTY;
			}
		}
	}

 #endif
#endif
}


/*************************************************************************
	module		:[コマンド、バッチ、スケジューラ消去中のバックアップ処理]
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
	date		:[1994/11/24]
	author		:[村田]
*************************************************************************/
void BackupDeleteingComOrExecFile(void)
{
	UWORD	l;
	UBYTE	i;
	UBYTE	ErasedCommandNumber;
	UBYTE	SameCommandNumberExist;
#if (PRO_BATCH_TX == ENABLE)
	UBYTE	BatchOrCommand;
#endif

	ErasedCommandNumber = 0xFF;
	SameCommandNumberExist = 0;
	for (l = 0; l < SYS_EXEC_QUEUE_MAX; l++ ) {
		if (SYB_ExecQueue[l].Status == SYS_EXEC_ERASED) {
			SYB_ExecQueue[l].Status = SYS_EXEC_EMPTY;
			ErasedCommandNumber = SYB_ExecQueue[l].Number.Command;
#if (PRO_BATCH_TX == ENABLE)
			if (SYB_ExecQueue[l].Kind == SYS_BATCH_TX) { /** 一括送信ファイル */
				BatchOrCommand = SYS_BATCH_TX;
			}
			else {
				BatchOrCommand = SYS_COMMAND_TRX;
			}
#endif
		}
	}

	if (ErasedCommandNumber != 0xFF) {	/* 消去中のスケジューラーがあった */

		for (l = 0; l < SYS_EXEC_QUEUE_MAX; l++ ) {
			switch (SYB_ExecQueue[l].Status) {
				case SYS_EXEC_WAITING:
				case SYS_EXEC_EXECUTE:
				case SYS_EXEC_FORWARD_WAITING:
				case SYS_EXEC_FORWARD_EXECUTE:
					if (SYB_ExecQueue[l].Number.Command == ErasedCommandNumber) {
						SameCommandNumberExist = 1;
					}
					break;
				default:
					break;
			}
		}
#if (PRO_BATCH_TX == ENABLE)
		if (! SameCommandNumberExist) {
			if (BatchOrCommand == SYS_COMMAND_TRX) {
				SYB_CommandFile[ErasedCommandNumber].Status = SYS_CMD_ERASED;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
				SYB_CommandStatus[ErasedCommandNumber] = SYS_CMD_ERASED;
#endif
			}
			else {
				SYB_BatchTxFile[ErasedCommandNumber].Status = SYS_CMD_ERASED;
			}
		}
		for (i = 0; i < SYS_COM_FILE_MAX; i++ ) {
			if (SYB_CommandFile[i].Status == SYS_CMD_ERASED) {
				CMN_ClearCommandArea(SYS_COMMAND_TRX, i);
			}
		}
		for (i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
			if (SYB_BatchTxFile[i].Status == SYS_CMD_ERASED) {
				CMN_ClearCommandArea(SYS_BATCH_TX, i);
			}
		}
#endif

#if (PRO_BATCH_TX == DISABLE)
		if (! SameCommandNumberExist) {
			SYB_CommandFile[ErasedCommandNumber].Status = SYS_CMD_ERASED;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
			SYB_CommandStatus[ErasedCommandNumber] = SYS_CMD_ERASED;
#endif
		}
		for (i = 0; i < SYS_COM_FILE_MAX; i++ ) {
			if (SYB_CommandFile[i].Status == SYS_CMD_ERASED) {
				CMN_ClearCommandArea(SYS_COMMAND_TRX, i);
			}
		}
#endif
	}
}


/*************************************************************************
	module		:[ＤＲＡＭをクリアする時に必要なＲＡＭの初期化]
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
	date		:[1994/08/15]
	author		:[吉川弘康]
*************************************************************************/
void InitializeDRAM_Parameter(void)
{
	UWORD	i;

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/11 Y.Murata */
	if (CMN_CheckMinoltaFlashEnable()) {
		/* Nothing */
	}
	else {
		MEM_ClearAll();	/** Initialize Memory Control Table */
	}
#else
	MEM_ClearAll();	/** Initialize Memory Control Table */
#endif

	SYS_ErasePixMemoryListRequest = 1;		/** 停電検出フラグを立てる */

	SYB_ExecQueueWritePoint = 0;			/* 実行待ちﾌｧｲﾙの展開位置初期化 */
	SYB_ExecQueueReadPoint = 0;				/* 実行待ちﾌｧｲﾙの実行位置初期化 */
	SYB_ExecQueueSerchPoint = 0;			/* 実行ｷｭｰ検索ﾎﾟｲﾝﾀｰ初期化 1997/10/28 Y.Murata */

	SYB_MultiCopyWritePoint = 0;			/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの展開位置 */
	SYB_MultiCopyReadPoint = 0;				/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの実行位置 */

	SYS_ManualFaxCommErrRequest = 0;		/* 手動通信チェックメッセージのプリント要求 */
	SYS_BackUpManualFaxCommErrReq = 0;
	SYS_BackUpConfirmationReport = 0;
	SYS_TxAutoJournalPrintRequest = 0;		/* 通信管理記録（送信）自動プリント要求 */
	SYS_RxAutoJournalPrintRequest = 0;		/* 通信管理記録（受信）自動プリント要求 */
	SYS_ProtocolMonitorPrintRequest = 0;	/* プロトコルモニタのプリント要求 */
	SYS_BackUpProtocolMonitorReq = 0;

	/* 1997/10/18 Y.Murata オプション回線用Ｔ３０モニタ印字要求 */
	SYS_OptionLineT30PrintRequest = 0;
	SYS_BackUpOptionLineT30PrintReq = 0;

	SYS_BackUpRamListRequest = 0;			/* ＲＡＭ領域初期化通知のプリント要求（「しない」にプリセット） */
	SYS_MemoryOverListRequest = 0;			/* 画像メモリあふれ通知のプリント要求 */
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/19 Y.Murata for KAKI */
	SYS_MemoryOverListPage = 0;
#endif
#if (PRO_PC_PRINT == ENABLE)	/* 追加 by M.Tachibana 1997/10/02 */
	SYS_PcMemoryOverListRequest = 0;		/* ＰＣプリント用画像メモリあふれ通知のプリント要求 */
	SYS_PcMemoryOverDispRequest = 0;		/* ＰＣ画像メモリあふれ表示要求 */
#endif
#if (PRO_DEPARTMENT == ENABLE)
  #if (PRO_COST == ENABLE)
	SYS_DepartmentListRequest = 0;			/* 部門リストのプリント要求 */
	SYS_DepartmentClearRequest = 0;
  #endif
  #if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By thonda 1997/11/29 */
	SYS_DepartManageListRequest = 0;		/* 部門リストのプリント要求 */
	SYS_DepartManageClearRequest = 0;
  #endif
#endif

	SYS_MultiPrintCount = 0;				/* 受信原稿を複数枚プリントする時の残ページ数 *//* 1995/06/26 By H.Y */

	/* 追加　1996/06/28 Eguchi */
	SYB_SecurityRxChkMsgRequest = 0;		/* セキュリティ受信モード中、受信メモリーオーバーチェックメッセージ要求フラグクリア */
	SYB_SecurityRxChkMsgPrint = 0;			/* セキュリティ受信モード中、受信メモリーオーバーチェックメッセージプリント済みフラグクリア */


	/*------------------------*/
	/* マルチコピー・ファイル */
	/*------------------------*/
	for (i = 0; i < SYS_MULTI_COPY_MAX; i++) {
		SYB_MultiCopyFile[i].Status = SYS_MCOPY_EMPTY;
	}

	/*------------------------*/
	/* 手差しコピー・ファイル */
	/*------------------------*/
	SYB_ManualCopyFile.Status = SYS_MCOPY_EMPTY;

	/*--------------------*/
	/* 発信スケジューラー */
	/*--------------------*/
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++ ) {
		SYB_ExecQueue[i].Status = SYS_EXEC_EMPTY;
	}

	/*-----------------------------------*/
	/* コマンド･ファイルの消去メッセージ */
	/*-----------------------------------*/
#if (PRO_COMMANDFILE_SRAM == ENABLE)	/* M.Tachibana 1997/03/22 */
	for (i = 0; i < SYS_COM_FILE_MAX; i++ )	 {
		if (SYB_CommandFile[i].Status == SYS_CMD_SETTING) {		/* By H.Y 1995/01/11 電話番号入力後スタートキー押下前に電源OFF/ONすると通信予約通知がプリントされる件の修正 */
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
		} else if (SYB_CommandFile[i].Status != SYS_CMD_EMPTY) {
			SYB_CommandFile[i].Status = SYS_CMD_POWER_OFF;
		}
	}
#else	/* PRO_COMMANDFILE_SRAM == DISABLE */
	for (i = 0; i < SYS_COM_FILE_MAX; i++ )	 {
		if (SYB_CommandStatus[i] == SYS_CMD_SETTING) {		/* By H.Y 1995/01/11 電話番号入力後スタートキー押下前に電源OFF/ONすると通信予約通知がプリントされる件の修正 */
			SYB_CommandStatus[i] = SYS_CMD_EMPTY;
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;		/* Add By M.Tachibana 1997/10/20 */
		} else if (SYB_CommandStatus[i] != SYS_CMD_EMPTY) {
			SYB_CommandStatus[i] = SYS_CMD_POWER_OFF;
			SYB_CommandFile[i].Status = SYS_CMD_POWER_OFF;	/* Add By M.Tachibana 1997/10/20 */
		}
		else {	/* SYS_CMD_EMPTY */
			SYB_CommandFile[i].Status = SYS_CMD_EMPTY;		/* Add By M.Tachibana 1997/10/20 */
		}
		/* コマンド消去通知をプリント中にコマンドを登録すると消去通知が
		** 見出しだけ出る。または、消去通知が出ない  By M.Tachibana 1997/10/20
		*/
/*		SYB_CommandFile[i].Status = SYS_CMD_EMPTY; Del By M.Tachibana 1997/10/20 */
	}
#endif
	/* Ｆードコマンドファイル用データのクリア 1997/08/08  By T.Yamaguchi */
#if (PRO_F_CODE == ENABLE)
	for (i = 0; i < SYS_COM_FILE_MAX; i ++) {	/* コマンドファイル用 */
		SYB_FcodeNumberCDataBuffer[i].SYS_SubAddressNumber[0] = 0xFF;
		SYB_FcodeNumberCDataBuffer[i].SYS_PassWordNumber[0] = 0xFF;
	}
#endif

	/*--------------------------------*
	 * 一括送信ファイル消去メッセージ *
	 *--------------------------------*/
#if (PRO_BATCH_TX == ENABLE)
	for (i = 0; i < SYS_BATCH_FILE_MAX; i ++) {
		if (SYB_BatchTxFile[i].Status != SYS_CMD_EMPTY) {
			SYB_BatchTxFile[i].Status = SYS_CMD_POWER_OFF;
		}
	}
#endif

	/*------------------------------*/
	/* メモリ受信原稿消去メッセージ */
	/*------------------------------*/
	if (SYB_MemoryRxPrintReadPoint >= SYS_MEMORY_RX_MAX) {		/* 1994/11/17 Y.Murata */
		SYB_MemoryRxPrintReadPoint = 0;
	}
	if (SYB_MemoryRxPrintWritePoint >= SYS_MEMORY_RX_MAX) {		/* 1994/11/17 Y.Murata */
		SYB_MemoryRxPrintWritePoint = 0;
	}

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/*消去ﾒｯｾｰｼﾞ作成時変更*/
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[i];

#if (0)
/*
** 代行受信消去通知が書けない状態で通信が入り、電源ＯＦＦ／ＯＮした場合、
** １回目の代行受信の明細が消去通知に載らない
** By M.Tachibana 1998/05/12
*/
//		if (MemoryRxPrintPoint->Status == SYS_MEMORY_RX_PRINT) {
//#if (PRO_MULTI_LINE == ENABLE)
//			/* 1997/01/16 Y.Murata
//			 * ステータスがプリントになってからジャーナルのポインターをセットするので
//			 * ジャーナルのポインターが確定していなければ消去通知はださない
//			*/
//			if (MemoryRxPrintPoint->JournalPoint == 0) {
//				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
//			}
//			else {
//				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_POWEROFF;
//			}
//#else
//			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_POWEROFF;
//#endif
//		}
//		else {
//			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
//		}
#endif

		switch (MemoryRxPrintPoint->Status) {
		case SYS_MEMORY_RX_EMPTY:
		case SYS_MEMORY_RX_POWEROFF:
			break;
		case SYS_MEMORY_RX_PRINT:
#if (PRO_REVERSE_PRINT == ENABLE)	/* By M.Tachibana 1998/05/20 */
		case SYS_MEMORY_RX_FAST_PRINT:
#endif
#if (PRO_MULTI_LINE == ENABLE)
			/* 1997/01/16 Y.Murata
			 * ステータスがプリントになってからジャーナルのポインターをセットするので
			 * ジャーナルのポインターが確定していなければ消去通知はださない
			*/
			if (MemoryRxPrintPoint->JournalPoint == 0) {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			}
			else {
				MemoryRxPrintPoint->Status = SYS_MEMORY_RX_POWEROFF;
			}
#else
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_POWEROFF;
#endif
			break;
		case SYS_MEMORY_RX_SETTING:
		case SYS_MEMORY_RX_STORE:
#if (PRO_REVERSE_PRINT == ENABLE)	/* By M.Tachibana 1998/05/20 */
		case SYS_MEMORY_RX_STORE_PRINT:
#endif
		default:
			MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
			break;
		}

		MemoryRxPrintPoint->StorePage = 0;
		MemoryRxPrintPoint->RotatePage = 1;
		MemoryRxPrintPoint->PrintPage = 1;
		MemoryRxPrintPoint->ErasePage = 1;
		MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /* プロテクト状態初期化 1995/12/22 Eguchi */
	}
	/*----------------------------------------------------------------------------------------------*/
	/* 代行受信消去通知印字終了後又は、印字が必要でないことを確認後クリアを行うように変更 7/26/1994 */
	/* ＤＲＡＭバック・アップ有り使用では単純にクリアしてはいけない									*/
	/* SATSUKI QAT BY S.K																			*/
	/* SYB_MemoryRxPrintReadPoint = 0; */
	/* SYB_MemoryRxPrintWritePoint = 0;	*//* 代行受信消去通知でクレームついたら変更 */

	/* 代行受信バグ Oct.5,1994	*/
	SYS_MemoryRxEraseReportPoint = SYB_MemoryRxPrintReadPoint;
	SYB_MemoryRxPrintReadPoint = SYB_MemoryRxPrintWritePoint;

	/*----------------------------*/
	/* 親展受信原稿消去メッセージ */
	/*----------------------------*/
	for (i = 0; i < SYS_MAILBOX_MAX; i++)  {
		/* 既に受信した受信原稿があるＢＯＸに再び受信中に電源断した場合
		** 受信した原稿が消去されても消去メッセージがでないため変更	1997/10/18  By T.Yamaguchi
		** if (SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)  {
		*/
		if (SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE) {
			SYB_MailBox[i].MessageStatus = SYS_MAILBOX_ERASED_MSG;
		}
		else if (SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING) {
			SYB_MailBox[i].MessageStatus = SYS_MAILBOX_ERASED_MSG;
			SYB_MailBox[i].Status = SYS_MAILBOX_RECEIVE;
		}
		else if (SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING) {	/* 親展受信中の電源断は消去通知を出さない */
			SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
			SYB_MailBox[i].Status = SYS_MAILBOX_SET;
		}
	}
#if (PRO_F_CODE == ENABLE)
	/*---------------------------------
	** Ｆコード蓄積原稿消去メッセージ
	*/
	for (i = 0;i < SUB_ADDRESS_BOX_MAX;i++) {
		if (SYB_SubAddressBoxTable[i].Status != SUB_ADDRESS_BOX_EMPTY) {	/* ｻﾌﾞｱﾄﾞﾚｽＢＯＸ登録済み */
			if (SYB_SubAddressBoxTable[i].StoredDocBit) {	/* 原稿が蓄積されている */
				SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_ERASED_MSG;
				if (SYB_SubAddressBoxTable[i].DataStatus != SYS_SUB_ADDRESS_BOX_NO_SET) {
					SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_STORED;
/*					SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;消去通知のため必要？ */
				}
				SYB_SubAddressBoxTable[i].StoredDocBit = 0;	/* 蓄積ファイル番号りセット */
			}
			else {	/* 蓄積原稿なしで受信中／蓄積中のときの電源断は消去通知を出さない */
				SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
				SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
			}
		}
	}
	if (SYB_SelectPollDocumentStatus == 1) {
		SYB_SelectPollDocumentStatus = 0;
	}
#endif
#if (PRO_CIPHER == ENABLE)
	/*----------------------------*/
	/* 暗号化受信原稿消去メッセージ */
	/*----------------------------*/
	if (ScrambleOn == 1) {/*	By Y.Suzuki 1997/09/04	*/
	for (i = 0; i < SYS_CIPHERBOX_MAX; i ++) {
		if (SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVING) {/* 暗号化受信中の電源断は消去通知を出さない */
			SYB_CipherBox[i].MessageStatus = SYS_CIPHERBOX_MSG_EMPTY;
			SYB_CipherBox[i].Status = SYS_CIPHERBOX_NO;
			SYB_CipherBox[i].StorePage = 0;
			SYB_CipherBox[i].PrintPage = 1;
		}
		else if (SYB_CipherBox[i].Status != SYS_CIPHERBOX_NO) {
			SYB_CipherBox[i].MessageStatus = SYS_CIPHERBOX_MSG_EMPTY;
		}
	}
	/* デスクランブル原稿プリントステータスクリア By Y.Suzuki 1998/04/17 */
	SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;
	}/* By Y.Suzuki 1997/09/04	*/
#endif
#if (PRO_REMOTE_FAX == ENABLE) /* By S.K Oct.5,1995 */
	SYS_RemoteFaxReceiveCount = 0;				/** リモートＦＡＸ取り出し用原稿件数 */

	/*------------------------------------*/
	/* リモートＦＡＸメモリオーバーフラグ */
	/*------------------------------------*/
	SYS_RemoteFaxMemoryOverFlag = 0;			/* 1994/06/17 Y.Murta */
#endif

	/*--------------*/
	/* 停電検出通知 */
	/*--------------*/	/* 1994/11/26 Y.Murata */
	if (SYB_PollingDocumentStatus == 1) {
		SYB_PowerDownListStatus |= SYS_POWER_POLLING;
		SYB_PollingDocumentStatus = 0;

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/01 */
** #if (PRO_MULTI_LINE == ENABLE)	/* Add By O.Kimoto 1996/11/11 */
** 		SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
** #endif
#else
		SYB_PollingDocExclusiveFlag = SYS_POLL_DOC_NO_EXIST;	/* ポーリング原稿があるかどうかの変数 */
#endif

	}

	if (SYB_DB_PollingDocumentStatus == 1) {
		SYB_PowerDownListStatus |= SYS_POWER_DB_POLL;
		SYB_DB_PollingDocumentStatus = 0;
	}

#if (PRO_REMOTE_FAX == ENABLE) /* By S.K Oct.5,1995 */
	if (SYS_RemoteFaxTAD_DataRecFlag & REMOTE_FAX_DATA) {
		SYB_PowerDownListStatus |= SYS_POWER_REMOTE_FAX;
		SYS_RemoteFaxTAD_DataRecFlag &= ~REMOTE_FAX_DATA;
	}
#endif
#if (PRO_DRAM_BACKUP == ENABLE)
	/*--------------------------------*/	/* バックアップ可能時のみ有効 */
	/* スキャナコマンド消去リクエスト */
	/*--------------------------------*/	/* 1994/11/26 Y.Murata */
	SYS_ScannerComEraseListRequest = 0;
#endif

#if (PRO_CLASS1 == ENABLE) /* 1996/09/21 Eguchi */

	/* クラス１関係追加　1996/09/24　Eguchi */
	/* 消去通知は不要 */
	/*-----------------------------------*
	 * ローカルスキャン原稿蓄積状態初期化
	 *-----------------------------------*/
	SYB_CL1_LocalScanDocStatus = 0;

	/*-----------------------------------------*
	 *　ローカルプリント原稿管理テーブル初期化
	 *-----------------------------------------*/
	for (i = 0; i < SYS_MEMORY_RX_MAX; i ++) {
		SYB_CL1_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
		SYB_CL1_MemoryRxPrint[i].StorePage = 0;
		SYB_CL1_MemoryRxPrint[i].PrintPage = 1;
		SYB_CL1_MemoryRxPrint[i].ErasePage = 1;
		SYB_CL1_MemoryRxPrint[i].Protect   = SYS_PROTECT_OFF;
	}

	/*-----------------------------------------*
	 *　ローカルプリント原稿書き込み位置初期化
	 *-----------------------------------------*/
	CL1_MemoryRxPrintWritePoint = 0;

	/*-----------------------------------------*
	 *　ローカルプリント原稿読み出し位置初期化
	 *-----------------------------------------*/
	CL1_MemoryRxPrintReadPoint = 0;


#endif

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/10/02 */
	/*-----------------------------------------*
	 *　ＰＣプリント原稿管理テーブル初期化	   *
	 *-----------------------------------------*/
	SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
	SYB_PcRxPrint.ExecutiveNumber = 0;
	SYB_PcRxPrint.RemainMultiPrintCount = 0;
	SYB_PcRxPrint.StorePage = 0;
	SYB_PcRxPrint.PrintPage = 1;
	SYB_PcRxPrint.ErasePage = 1;
	SYB_PcRxPrint.PrintEndPage = 0;
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE) /*連続ポーリング処理追加 1996/10/18 Eguchi */
	if (SYB_ContinuousPolling.Status == SYS_CMD_SETTING) {	/** 登録中に電源断した場合 */
		SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;		/** 未使用状態 */
	}
	else if (SYB_ContinuousPolling.Status != SYS_CMD_EMPTY) {
		SYB_ContinuousPolling.Status = SYS_CMD_POWER_OFF;	/** 消去通知印字 */
	}
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	/*----------------------------------------*/
	/* ダイアルアップ型　インターネットＦＡＸ */
	/*----------------------------------------*/
	RecoverMailComDramBackUpNG();
#endif

#if defined(POPLAR_F)
	/*---------------------------------------------------------------
	 * Ｔ３０モニタ管理ステータス
	 *   ジャーナル分Ｔ３０モニタを確保するための管理ステータス
	*/
	for (i = 0; i < SYS_JOURNAL_MAX; i++) {
		SYB_T30MonitorDRAM_Status[i] = 0;
	}
#endif

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
	for (i = 0; i < SYS_MULTI_COPY_MAX; i++) {
		SYS_MinoltaTestFuncData[i].Status = SYS_FUNC_TEST_DATA_EMPTY;
		SYS_MinoltaTestFuncData[i].IntervalTimer = 0;
	}
	SYS_MinoltaTestFuncData[0].Status = SYS_FUNC_TEST_DATA_OFF;	/* ０番目は未使用 */
	SYS_MinoltaFuncIntervalTimer = 0;
#endif


	/*------------------------------------*
	 * バックアップテストエリアの初期化	  *
	 *------------------------------------*/
	CMN_InitDRAM_BackupTestArea();	/* By M.Tachibana 1997/10/31 */

}


/*************************************************************************
	module		:[電源ＯＦＦ／ＯＦＦされたがＤＲＡＭクリアをする必要の無い時のＲＡＭの初期化]
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
	date		:[1994/08/15]
	author		:[吉川弘康]
*************************************************************************/
void RecoverDRAM_Parameter(void)
{
#if (PRO_DRAM_BACKUP == ENABLE)
	UWORD i;

	SYS_RingCounter	 = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/12/1 */
	SYS_RingCounterExt = 0;
#endif

	SYS_RxDetectFlag = 0;
	SYS_ErasePixMemoryListRequest = 0;

	/*--------------------------------*/
	/* スキャナコマンド消去リクエスト */
	/*--------------------------------*/	/* 1994/11/28 Y.Murata */
	SYS_ScannerComEraseListRequest = 0;

	/*--------------------*/
	/* 蓄積中ページの消去 */
	/*--------------------*/
	MEM_ClearPowerDown();

	/*----------------------------------------------------------------------------------*/
	/* ＤＲＡＭ消去中に瞬断が発生した場合、消去中のインデックス・ＦＡＴの消去処理を行う */
	/*----------------------------------------------------------------------------------*/
	/* TBD */
	/*------------------------*/
	/* マルチコピー・ファイル */
	/*------------------------*/
	for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
		SYB_MultiCopyFile[i].Status = SYS_MCOPY_EMPTY;
		MEM_ClearDocAndFATArea(SYS_MEM_MULTI_COPY_FILE, i, MEM_IGNORE_BOX_NUMBER);
	}
	SYB_MultiCopyWritePoint = 0;				/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの展開位置 */
	SYB_MultiCopyReadPoint = 0;					/* ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの実行位置 */

	/*------------------------*/
	/* 手差しコピー・ファイル */
	/*------------------------*/
	SYB_ManualCopyFile.Status = SYS_MCOPY_EMPTY;
	MEM_ClearDocAndFATArea(SYS_MEM_MANUAL_COPY_FILE, 0, MEM_IGNORE_BOX_NUMBER);

	/*-------------------------------------*/
	/* コマンド･ファイルのバックアップ処理 */
	/*-------------------------------------*/
	BackupCommandFile();		/* 1994/11/17 Y.Murata */

	/*--------------------------------------*/
	/* 発信スケジューラーのバックアップ処理 */
	/*--------------------------------------*/
	BackupExecQueueFile();		/* 1994/11/24 Y.Murata */

	/*---------------------------------------------------*/
	/* コマンド･ファイル  一括送信ファイルの消去中の処理 */
	/*---------------------------------------------------*/
	BackupDeleteingComOrExecFile();			/* 1994/11/25 Y.Murata */

	/*--------------------------------------------------------------*/
	/* 一括送信ファイル消去メッセージ								*/
	/* 原稿蓄積中に瞬断が発生した場合は、既に蓄積済原稿はそのままで */
	/* 蓄積中原稿のみ消去します										*/
	/*--------------------------------------------------------------*/
#if 0
//#if (PRO_BATCH_TX == ENABLE)
//	for (i = 0; i < SYS_BATCH_FILE_MAX; i ++) {
//		bat_ptr = &SYB_BatchTxFile[i];
//		for (j = 0; j < SYS_BATCH_INDEX_MAX; j ++) {
//			if (bat_ptr->IndexNo[j] == SYS_BAT_DOC_STORING) {
//				break;
//			}
//		}
//		if (j != SYS_BATCH_INDEX_MAX) {
//			bat_ptr->IndexNo[j] = SYS_BAT_DOC_EMPTY;
//			MEM_ClearDoc((UBYTE)(SYS_MEM_BATCH_TX_FILE1 + i), j, MEM_IGNORE_BOX_NUMBER);
//			break;
//		}
//	}
//#endif
#endif

	BackupBatchTxFile();

	/*--------------------------------------*/
	/* ポーリング送信原稿のバックアップ		*/
	/* 検索ポーリング送信原稿のバックアップ */
	/*--------------------------------------*/
	BackupPollingFile();			/* 1994/11/24 Y.Murata */

	/*--------------------------------------------------------------------*/
	/* メモリ受信原稿消去メッセージ										  */
	/*１ページ目受信中の時はStatusがSYS_MEMORY_RX_EMPTY					  */
	/* 2ページ目以降受信中の時はStatusがSYS_MEMORY_RX_STORE				  */
	/* 受信終了の時はStatusがSYS_MEMORY_RX_PRINT						  */
	/* 蓄積中ページは既に消去済のため、ここでは処理しない				  */
	/*--------------------------------------------------------------------*/
	BackupMemoryRxPrintFile();			/* 1994/11/17 Y.Murata */

	/*-----------------------------------------------------------*
	 * 代行受信管理テーブルの内容から、セキュリティ受信原稿
	 * 時の受信メモリーオーバーチェックメッセージの印字フラグを
	 * 念のため再設定する
	 * 1996/06/28 Eguchi
	 *-----------------------------------------------------------*/
#if (PRO_SECURITY_RX == ENABLE)
	if ((CheckProtectedDocStored() == FALSE)	/** プリント待ちのセキュリティ受信原稿なし*/
	&&	(CheckProtectedDocStoring() == FALSE)) {/** 受信中のセキュリティ受信原稿なし*/
		if (SYB_SecurityRxChkMsgRequest == 1) {/* チェックメッセージ印字要求がセットされている(印字中に電源断) */
			SYB_SecurityRxChkMsgRequest = 0;
		}
	}
#endif
	/*----------------------------------------------------------------------------------------------*/
	/* 代行受信消去通知印字終了後又は、印字が必要でないことを確認後クリアを行うように変更 7/26/1994 */
	/* ＤＲＡＭバック・アップ有り使用では単純にクリアしてはいけない									*/
	/* SATSUKI QAT BY S.K																			*/
	/* SYB_MemoryRxPrintReadPoint = 0; */
	/* SYB_MemoryRxPrintWritePoint = 0;	*//* 代行受信消去通知でクレームついたら変更 */


	/*----------------------------*/
	/* 親展受信原稿消去メッセージ */
	/*----------------------------*/
	BackupSecureFile();					/* 1994/11/24 Y.Murata */

	/*----------------------------*/
	/* Ｆコード原稿消去メッセージ */
	/*----------------------------*/
	BackupSubAddressBoxFile();			/* 1997/04/26 T.Yamaguchi */

	/*----------------------------*/
	/* 暗号化原稿消去メッセージ */
	/*----------------------------*/
	BackupCipherFile();			/* 1997/06/18  By T.Yamaguchi */

	/*----------------------------------*/
	/* 暗号化前原稿／暗号化復元原稿消去 */
	/*----------------------------------*/
	ClearCipherFile();			/* By Y.Suzuki 1998/04/17 */


	/*----------------*/
	/* リモートＦＡＸ */
	/*----------------*/
#if (PRO_REMOTE_FAX == ENABLE)

	if (SYS_RemoteFaxTxPerformingFlag == 1) {					/* 1994/12/19 */
		if (SYS_RemoteFaxTAD_DataRecFlag & REMOTE_FAX_DATA) {
			/* 何もしない */
		}
		else {
			SYS_RemoteFaxReceiveCount = 0;						/** リモートＦＡＸ蓄積原稿数クリア */
			MEM_ClearDoc(SYS_MEM_REMOTE_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);			/** リモートＦＡＸ原稿消去 */
		}
	}
	else {

		if (SYS_RemoteFaxTAD_DataRecFlag & REMOTE_FAX_DATA) {	/** リモートＦＡＸ原稿がある */

			if (MEM_CountTotalPage(SYS_MEM_REMOTE_TX_FILE,0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {		/** １ページ以上原稿がある */

				/** ページ再設定？ */

			}
			else {		/** フラグは原稿有りになっているが原稿が無い */

				SYS_RemoteFaxReceiveCount = 0;						/** リモートＦＡＸ受信カウンタクリア		 */
				SYS_RemoteFaxMemoryOverFlag = 0;					/** リモートＦＡＸメモリオーバーフラグクリア */
				MEM_ClearDoc(SYS_MEM_REMOTE_TX_FILE,0, MEM_IGNORE_BOX_NUMBER);	/** メモリのＦＡＴエリアクリア（一応）		 */
				SYS_RemoteFaxTAD_DataRecFlag &= ~REMOTE_FAX_DATA;	/** リモートＦＡＸ有無フラグクリア			 */
			}
		}
		else {	/** リモートＦＡＸ原稿がない */

			if (MEM_CountTotalPage(SYS_MEM_REMOTE_TX_FILE,0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {	/** １ページ以上原稿がある */

				SYS_RemoteFaxTAD_DataRecFlag |= REMOTE_FAX_DATA;	/** リモートＦＡＸ有無フラグを有にセット */
				SYS_RemoteFaxReceiveCount = 1;						/** リモートＦＡＸ受信カウンタを１にセット */

			}
			else {	/** フラグもメモリも原稿無しである */

				SYS_RemoteFaxReceiveCount = 0;						/** リモートＦＡＸ受信カウンタクリア（一応）		 */
				SYS_RemoteFaxMemoryOverFlag = 0;					/** リモートＦＡＸメモリオーバーフラグクリア（一応） */
			}
		}
	}
	SYS_RemoteFaxTxPerformingFlag = 0;

	if (SYB_PowerDownListStatus & SYS_POWER_REMOTE_FAX) {	/* 1994/12/22 Y.Murata */
		SYS_ErasePixMemoryListRequest = 1;
	}

#endif

#if (PRO_FIP == ENABLE)		/* Add By M.Tachibana 1995/07/21 */
	/*------------------*/
	/* ＦＩＰ原稿の消去 */
	/*------------------*/
	for (i = 0; i < FIP_MAIL_BOX_MAX; i ++) {
		MEM_ClearDoc(SYS_MEM_FIP_FILE, i, MEM_IGNORE_BOX_NUMBER);
	}
#endif


#if (PRO_CLASS1 == ENABLE) /* 1996/09/24 Eguchi */

	/* クラス１関係追加　1996/09/24　Eguchi */
	/* バックアップはしない。消去通知もださない */

	/*------------------------------------*
	 * クラス１ローカルスキャン原稿の消去
	 *------------------------------------*/
	SYB_CL1_LocalScanDocStatus = 0;
 #if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/8/12 K.Kawata */
	if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE , 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {/* １ページ以上蓄積済みであれば */
		if ((CL1_ExtFunctionEnableFlag == 1) && (CHK_UNI_Class1_EXT_Function())) {
			MAN_ChangeItemLS2MP();
		}
		else {
			MEM_ClearDocAndFATArea(SYS_MEM_CLASS1_TX_FILE , 0, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿をクリア */
		}
	}
 #else
	if (MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE , 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {/* １ページ以上蓄積済みであれば */
		MEM_ClearDocAndFATArea(SYS_MEM_CLASS1_TX_FILE , 0, MEM_IGNORE_BOX_NUMBER); /* 蓄積原稿をクリア */
	}
 #endif

	/*-----------------------------------------*
	 *　ローカルプリント原稿管理テーブル初期化
	 *-----------------------------------------*/
	for (i = 0; i < SYS_MEMORY_RX_MAX; i ++) {
		SYB_CL1_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
		SYB_CL1_MemoryRxPrint[i].StorePage = 0;
		SYB_CL1_MemoryRxPrint[i].PrintPage = 1;
		SYB_CL1_MemoryRxPrint[i].ErasePage = 1;
		SYB_CL1_MemoryRxPrint[i].Protect   = SYS_PROTECT_OFF;

		/*--------------------------------------*
		 * ローカルプリント原稿消去
		 *--------------------------------------*/
		if (MEM_CountTotalPage(SYS_MEM_CL1_RX_FILE , i, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 1ページ以上蓄積済み */
			MEM_ClearDocAndFATArea(SYS_MEM_CL1_RX_FILE , i, MEM_IGNORE_BOX_NUMBER); /* 原稿消去 */
		}
	}

	/*-----------------------------------------*
	 *　ローカルプリント原稿書き込み位置初期化
	 *-----------------------------------------*/
	CL1_MemoryRxPrintWritePoint = 0;

	/*-----------------------------------------*
	 *　ローカルプリント原稿読み出し位置初期化
	 *-----------------------------------------*/
	CL1_MemoryRxPrintReadPoint = 0;


#endif

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/10/02 */
	/*-----------------------------------------*
	 *　ＰＣプリント原稿管理テーブル初期化	   *
	 *-----------------------------------------*/
	SYB_PcRxPrint.Status = SYS_PC_RX_EMPTY;
	SYB_PcRxPrint.ExecutiveNumber = 0;
	SYB_PcRxPrint.RemainMultiPrintCount = 0;
	SYB_PcRxPrint.StorePage = 0;
	SYB_PcRxPrint.PrintPage = 1;
	SYB_PcRxPrint.ErasePage = 1;
	SYB_PcRxPrint.PrintEndPage = 0;

	/*--------------------------------------*
	 * ローカルプリント原稿消去
	 *--------------------------------------*/
	if (MEM_CountTotalPage(SYS_MEM_PC_RX_FILE , 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /* 1ページ以上蓄積済み */
		MEM_ClearDocAndFATArea(SYS_MEM_PC_RX_FILE , 0, MEM_IGNORE_BOX_NUMBER); /* 原稿消去 */
	}
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE) /*連続ポーリング機能追加。1996/10/18 Eguchi */
	/*--------------------------------------*
	 * 連続ポーリングコマンドバックアップ処理
	 *--------------------------------------*/
	switch (SYB_ContinuousPolling.Status) {
	case SYS_CMD_EMPTY:		/* 未使用 */
	case SYS_CMD_SETTING:	/* オペレーションセット中に電源断 */
		SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
		break;
	case SYS_CMD_WAITING:	/* 予約中に電源断 */
		/* キューには展開されてへんはずやけど念のためクリア */
		CancelExecQueue(SYS_CONTINUOUS_POLLING , 0);
		break;

	case SYS_CMD_EXECUTE:	/* 実行中に電源断 */
		break;

	case SYS_CMD_ERASED:	/* 消去中に電源断 */
		/*
		 * この時は以下の場合がある
		 * 連続ポーリングコマンドのキューが全て消去されて、結果的にコマンドを消去した時に電源断
		 * 実行中の状態の連続ポーリングコマンドを消去した時に電源断。この時連続ポーリングのキューの状態は全て消去中か未使用になっているはず
		 * 予約中の状態の連続ポーリングコマンドを消去した時に電源断
		 */
		CancelExecQueue(SYS_CONTINUOUS_POLLING , 0);
		SYB_ContinuousPolling.Status  = SYS_CMD_EMPTY;
		break;
	case SYS_CMD_POWER_OFF: /* 電源断検出 */
		/*
		 *以下の場合が考えられる
		 * 電源立ち上げ時に消去通知を書こうとしている時に電源断
		 */
		/* 恐らくキューは消えているはずだが念のため消去 */
		CancelExecQueue(SYS_CONTINUOUS_POLLING , 0);
		SYB_ContinuousPolling.Status  = SYS_CMD_EMPTY;
		break;
	default:
		break;
	}

#endif
#if (PRO_DIALUP_INTERNET_FAX == ENABLE) /* by Y.Tanimoto 1998/03/13 */
	/*----------------------------------------*/
	/* ダイアルアップ型　インターネットＦＡＸ */
	/*----------------------------------------*/
	RecoverMailComDramBackUpOK();
#endif


#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/12 Y.Murata */
	for (i = 0; i < SYS_MINOLTA_TEST_FUNC_MAX; i++) {
		if (SYS_MinoltaTestFuncData[i].Status == SYS_FUNC_TEST_DATA_PRINT) {
			SYS_MinoltaTestFuncData[i].Status = SYS_FUNC_TEST_DATA_STORE;
		}
	}
	SYS_MinoltaTestFuncData[0].Status = SYS_FUNC_TEST_DATA_OFF;	/* ０番目は未使用 */
	SYS_MinoltaFuncIntervalTimer = 0;
#endif



#endif
}


#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  Apr.07.1995 */
/*************************************************************************
	module		:[不達通知のコマンドファイルを作成]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		椛のみ
		MAN_Task()の中から抜き出して関数化
		i : report_no
		j : relayed_no
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/04/07]
	author		:[竹内茂樹]
*************************************************************************/
void CreateRelayedReportCommand(
	UBYTE	report_no,		/* 不達通知を作成するCommandFile番号 */
	UBYTE	relayed_no)		/* 中継配信(親)のCommandFile番号 */
{
	struct	SYS_CommandData_t		* report_comf;	/* 不達通知を作成するCommandFile */
	struct	SYS_CommandData_t		* relayed_comf;	/* 中継配信(親)のCommandFile */
	UWORD	count;

	/* ポインタをlocalに待避 */
	report_comf	 = &SYB_CommandFile[report_no];
	relayed_comf = &SYB_CommandFile[relayed_no];

	/*------------------------------------------*/
	/* 不達通知用のコマンドファイルを作製する。 */
	/*------------------------------------------*/
	/* SYB_CommandFile[report_no].Option.OptionNumber.RelaySourceID[0] には */
	/* １度不達通知をコマンドにセットすると、0-9までの数字が入る			*/
	/* 通常(コマンドに展開するまえ)は、アスキーダイヤル。(0x30 先頭は、0)	*/

	report_comf->Status = SYS_CMD_SETTING;		/** 不達通知をセット中 */
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
	SYB_CommandStatus[report_no] = SYS_CMD_SETTING;
#endif

	/* SYB_CommandFile[relayed_no].OptionNumber.RelaySourceID[SYS_SRC_ID_MAX]の番号をDirect[]に展開する。*/
	/**	中継配信(親)のコマンドファイルから中継指示機のＦａｘ番号を	**
	***	不達通知のコマンドファイルの送信番号に展開する				*/
	CMN_ASC_ToBCD_String( &(report_comf->DialNumber.Direct[0]),
						  &(relayed_comf->Option.OptionNumber.RelaySourceID[0]) );	/* ダイアル番号登録 */
	/* ダイアルの種別登録(不要領域はクリア) */
#if (0)
**	report_comf->DialNumber[0].Item = SYS_DIRECT_DIAL;
**	for (count = 1; count < SYS_COM_DIAL_MAX; count++) {
**		report_comf->DialNumber[count].Item = SYS_EMPTY_DIAL;
**	}
#endif
	for (count = 1; count < SYS_COM_DIRECT_DIAL_MAX; count++) {
		report_comf->DialNumber.Direct[count][0] = 0xff;
	}
	for (count = 0; count < SYS_ONETOUCH_BIT_FIELD_MAX; count++) {
		report_comf->DialNumber.Onetouch[count] = 0x00;
	}
	for (count = 0; count < SYS_SPEED_BIT_FIELD_MAX; count++) {
		report_comf->DialNumber.Speed[count] = 0x00;
	}
	report_comf->DialNumber.Group = 0;

	report_comf->ExecTime = SYB_CurrentTime;						/** 現在時刻 */
	report_comf->Option.Item = SYS_RELAYED_TX_REPORT;				/** 種別(不達通知) */
	report_comf->Option.OptionNumber.RelaySourceID[0] = relayed_no;	/** 中継配信(親)のCommandFileNo */
	report_comf->Option.ConfirmationReport = 0;						/** 通信証設定をセット */
 #if (PRO_DEPARTMENT == ENABLE)
	report_comf->DepartmentCode = 0;								/** 部門管理コード(なし) */
 #endif
 #if (PRO_JOURNAL == UNITED)
	report_comf->Type = 0;											/** 送受信一体型時の送受の識別 */
 #endif
	report_comf->TitleMessage = 0xFF;								/** タイトルメッセージ(なし) */
	report_comf->Page = 1;											/** ページ数(1) */
	report_comf->Ability = 0;										/** 付加属性(なし) */

	/** 中継配信(親)のコマンドファイルを「不達通知登録済み」とする */
	relayed_comf->Option.OptionNumber.RelaySourceID[0] = 0x00;		/* 不達通知が登録されたことを示す */
	RelayedTxDocumentStatus[relayed_no] = report_no;				/* 不達通知のCommandFileNoを記憶 */

	report_comf->Status = SYS_CMD_WAITING;		/** 不達通知をセット完了 */
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/03/22 */
	SYB_CommandStatus[report_no] = SYS_CMD_WAITING;
#endif

}
#endif


#if (PRO_RELAYED_REPORT == ENABLE)	/* 中継配信不達通知のため  Apr.07.1995 */
/*************************************************************************
	module		:[中継配信のチェックメッセージプリントを起動]
	function	:[
		中継配信のエラー件数を数え，チェックメッセージ印字を起動する
	]
	return		:[]
	common		:[]
	condition	:[
		プリンタが使用可能であること
	]
	comment		:[
		椛のみ
		MAN_Task()の中から抜き出して関数化
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1995/04/07]
	author		:[竹内茂樹]
*************************************************************************/
void ExecuteRelayedReportPrint(
	UBYTE	relayed_no)		/* 中継配信のCommandFile番号 */
{
	struct	SYS_ExecQueueData_t	* exec_queue;
	UBYTE	count;
	UBYTE	err_count;

	/** 交信エラーを数える */
	err_count = 0;
	for (count = 0; count < SYS_EXEC_QUEUE_MAX; count++) {
		exec_queue = &SYB_ExecQueue[count];
		if ((exec_queue->Number.Command == relayed_no)
		&&	(exec_queue->Status == SYS_EXEC_ERROR)) {
			err_count++;	/** 交信エラー数を加算 */
		}
	}

	/** プリンタ使用中とする */
	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY;

	/** プリントのパラメータをセット */
	SYS_DocumentPrintNo		= relayed_no;
	SYS_DocumentPrintPageNo	= 1;
	SYS_DocumentPrintClass	= SYS_PRINT_CLASS_LIST_MEMORY;

	/* 中継配信はメモリ送信なので CheckDocStoredCommand(relayed_no) は見ない */
#if (0)			/** １０件以上でも、蓄積原稿を印字するように変更 97/11/21 By M.Kuwahara */
//	if ((CHK_DocumentPrintAfterMemTx())
//	&&	(err_count <= 10)) {			/* メモリ送信エラー時の蓄積原稿印字ＯＮで，エラーが１０件以下 */
#endif
	if (CHK_DocumentPrintAfterMemTx()) {
		/** 蓄積原稿プリントタスクを起動 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_IMAGE_PRINT;
		SYS_DocumentPrintItem = SYS_MEM_TX_FILE;
		cre_tsk( &tskno_PRN_ImagePrintTask, TSK_PRN_IMAGEPRINTTASK, 0 );
	}
	else {
		/** リストプリントタスクを起動 */
		SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT;
		SYS_DocumentPrintItem = LST_COMMERR_CHECKMSG;
		cre_tsk( &tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0 );
	}
}
#endif

/*-----------------------------------------------------------------------*/

#if (0)
/* ここで必要なＲＡＭを定義する */
UBYTE	OK_No	 = 0;	/* OKの通信数を入力 */
UBYTE	ERROR_No = 0;	/* ERRORの通信数を入力 */
UBYTE	MONITOR_ON_OFF = 0;	/* ﾓﾆﾀﾚﾎﾟｰﾄの切替え 0:ON 1:OFF */

void CheckMessageTest(void)
{
	UBYTE i = 0;
	UBYTE j = 0;
	UWORD tskno_LST_PrintTask = 0;

	/* CommandFileの登録 */
	SYB_CommandFile[0].Status = SYS_CMD_EXECUTE;
	if ( MONITOR_ON_OFF == 0 ) {
/*		SYB_CommandFile[0].Option.ConfirmationReport = TCR_REQUEST;	*/
		SYB_CommandFile[0].Option.ConfirmationReport = SYS_TCR_REQUESTED;
	}
	else {
		SYB_CommandFile[0].Option.ConfirmationReport = NO_CONFIRMATION_REPORT;
	}
	/* ExecQueueの登録 (まず､ｺﾏﾝﾄﾞﾌｧｲﾙから) */
	for( i = 0; i < (OK_No+ERROR_No); i++ ) {
		SYB_ExecQueue[i].Kind = SYS_COMMAND_TRX;
		SYB_ExecQueue[i].Number.Command = 0;	/* CommandFile[]の配列ｵﾌｾｯﾄ値 */
	}
	for( j = 0; j < OK_No; j++ ) {
		SYB_ExecQueue[j].Status = SYS_EXEC_OK;
		SYB_ExecQueue[j].Result = 0;
	}
	for(  ; j < (OK_No+ERROR_No); j++ ) {
		SYB_ExecQueue[j].Status = SYS_EXEC_ERROR;
		SYB_ExecQueue[j].Result = 0x0400|0x0041; /* Transmit Error */
	}

#if (0)
** 	/* ﾘｽﾄ起動の設定 原稿無しの場合 */
** 	SYS_MachineStatus[SYS_RESOURCE_STATUS] |= SYS_PRINTER_BUSY; /* プリンタ使用中セット */
** 	SYS_MachineStatus[SYS_MACHINE_STATUS] |= SYS_LIST_PRINT; /* リスト・プリント使用中セット */
** 	SYS_DocumentPrintItem  = LST_COMMERR_CHECKMSG;
** 	SYS_DocumentPrintNo		= (UBYTE)j;
** 	SYS_DocumentPrintPageNo = 1;
** /*	if ( SYB_CommandFile[0].Option.ConfirmationReport == TCR_REQUEST ) {	*/
** 	if (((SYB_CommandFile[0].Option.ConfirmationReport & SYS_RCR_REQUESTED) == SYS_TCR_REQUESTED)
** 	 || ((SYB_CommandFile[0].Option.ConfirmationReport & SYS_TCR_AND_RCR) == SYS_TCR_AND_RCR )) {
** 	 {
** 		SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MONITOR; /** モニター・レポート印字指定 */
** 	}
** 	else {
** 		SYS_DocumentPrintClass = SYS_PRINT_CLASS_LIST_MEMORY;	/*ﾁｪｯｸﾒｯｾｰｼﾞ*/
** 	}
** 
** /*	cre_tsk(&tskno_LST_PrintTask, TSK_LST_PRINTTASK, 0);  リスト・プリント・タスク起動 */
#endif
}
#endif


/*************************************************************************
	module		:[チェックメッセージ印字後のＬＥＤ／ＬＣＤエラー消去
	function	:[
		コマンドとエグゼックファイルの状態から、チェックメッセージが印字
		されたかを判断し、印字終了であれば通信エラーステータスをクリアする。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1996/04/26]
	author		:[川崎 真史]
*************************************************************************/
void MAN_ClearCommunicationError(void)
{
	UBYTE com_no,queue_no;
	UBYTE error_clear_flag;

	error_clear_flag = 0;

	/*
	** 通常コマンドファイルの確認
	*/
	for (com_no = 0; com_no < SYS_COM_FILE_MAX; com_no++) {
		if (SYB_CommandFile[com_no].Status == SYS_CMD_EXECUTE) {
			for (queue_no = 0; queue_no < SYS_EXEC_QUEUE_MAX; queue_no++) {
				if ((SYB_ExecQueue[queue_no].Status == SYS_EXEC_ERROR) &&
					(SYB_ExecQueue[queue_no].Kind == SYS_COMMAND_TRX) &&
					(SYB_ExecQueue[queue_no].Number.Command == com_no)) {
					error_clear_flag = 1;
				}
			}
		}
	}
	if ( error_clear_flag == 0) {
#if (PRO_BATCH_TX == ENABLE)
		/*
		** 一括送信コマンドファイルの確認
		*/
		for (com_no = 0; com_no < SYS_BATCH_FILE_MAX; com_no++) {
			if (SYB_BatchTxFile[com_no].Status == SYS_CMD_EXECUTE) {
				for (queue_no = 0; queue_no < SYS_EXEC_QUEUE_MAX; queue_no++) {
					if ((SYB_ExecQueue[queue_no].Status == SYS_EXEC_ERROR) &&
						(SYB_ExecQueue[queue_no].Kind == SYS_BATCH_TX) &&
						(SYB_ExecQueue[queue_no].Number.Batch == com_no)) {
						error_clear_flag = 1;
					}
				}
			}
		}
#endif
	}
	if( (error_clear_flag == 0)	&&
		(SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_FAXCOM) ) {
		SYS_MachineStatus[SYS_ERROR_STATUS] &= ~(SYS_ERROR_FAXCOM);
	}
	
#if defined (KEISATSU) /* 警察FAX 05/11/16 石橋正和 */
	/* S1アラーム */
	if (error_clear_flag == 0) {
		if (SYS_MachineStatus[SYS_ERROR_STATUS] & SYS_ERROR_S1) {
			S1_SoftwareReset(); /* S1ソフトリセット */
			/* マシンステイタスはセンサタスクでON/OFFしている */
		}
	}
#endif
}

/*************************************************************************
	module		:[プリンターオプションからのメッセージをチェックする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1997/03/04]
	author		:[平尾 英典]
*************************************************************************/
#if (PRO_PC_PRINT == ENABLE) /* Add BY H.H 1997/03/04 */
void MAN_CheckPrinterOption(void)
{
	MESSAGE_t	send_message;
	MESSAGE_t	*receive_message;
	UBYTE	i;

	for (i = 0; i < SYS_PCR_OPTION_MESSAGE_MAX; i ++) {
		if (SYS_PCR_OptionMessage[PCR_OptMessagRead].Status == 1) {
			send_message.Item = SYS_PCR_OptionMessage[PCR_OptMessagRead].Item;
			send_message.Message = SYS_PCR_OptionMessage[PCR_OptMessagRead].Message;
			SYS_PCR_OptionMessage[PCR_OptMessagRead].Status = 0;
			snd_msg(mbxno.MAN_Task, &send_message);
			/* ２８．８ボードとＰＣプリンターボードが同時に動いたとき
			** メッセージを横取りしてしまうので、同期のとれるFCM_Option
			** をメイルボックスに利用する
			** BY H.H 1997/04/10
			*/
			/* rcv_msg(mbxno.DPR_RemoteFuncExecTask, &receive_message); */
			rcv_msg(mbxno.FCM_Option, &receive_message); /* 1997/04/10 BY H.H */
			PCR_OptMessagRead++;
			if (PCR_OptMessagRead >= SYS_PCR_OPTION_MESSAGE_MAX) {
				PCR_OptMessagRead = 0;
			}
		}
	}
}
#endif

#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング機能追加 1996/10/17 Eguchi */
/*************************************************************************
	module		:[自動受信開始時刻／終了時刻計算]
	function	:[
		1.SYS_CurrentTimeと同じ日付にする。
		2.1日進める
		3.それでも連続ポーリングの方が過去を示してるならば、さらに1日進める。
		4.終了時刻が開始時刻よりも前のときは終了時刻のみ1日進める
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1997/03/18]
	author		:[江口、きもと]
*************************************************************************/
void MAN_CalcContPollingExecTime(void)
{
	struct	SYS_ContinuousPollingData_t *ptr;
	TIME_DATA_t	now_bcd_time;
	TIME_DATA_t	poll_bcd_time;

	ptr = &SYB_ContinuousPolling;

	/** 現在時刻をばらす */
	CMN_LongTimeToBCD((TIME_DATA_t far*)&now_bcd_time , SYB_CurrentTime);

	/** 開始時刻の計算 */
	CMN_LongTimeToBCD((TIME_DATA_t far*)&poll_bcd_time , ptr->StartTime);

	now_bcd_time.Hour = poll_bcd_time.Hour;
	now_bcd_time.Minute = poll_bcd_time.Minute;
	ptr->StartTime = CMN_BCD_TimeToLong((TIME_DATA_t far*)&now_bcd_time);

	/** 終了時刻の計算 */
	CMN_LongTimeToBCD((TIME_DATA_t far*)&poll_bcd_time , ptr->EndTime);

	now_bcd_time.Hour = poll_bcd_time.Hour;
	now_bcd_time.Minute = poll_bcd_time.Minute;
	ptr->EndTime = CMN_BCD_TimeToLong((TIME_DATA_t far*)&now_bcd_time);

#if (0)	/*  By O.Kimoto 1997/07/18 */
** 	if (ptr->EndTime < SYB_CurrentTime) {
** 		/** １日進める */
** 		ptr->StartTime += (unsigned long)(24UL * 60UL * 60UL);
** 		ptr->EndTime += (unsigned long)(24UL * 60UL * 60UL);
** 	}
#endif

	if (ptr->StartTime >= ptr->EndTime) {/**終了時刻が開始時刻よりも前のとき */
		ptr->EndTime += (unsigned long)(24UL*60UL*60UL); /** 次の日の終了時刻に終わるため1日分加える */
	}
	/* 終了時刻から開始時刻の差が十分短く、終了時刻直前に開始された通信が開始時刻を過ぎて終了した場合、
	** 上記の１日進める処理のところで、余分に１日過ぎてしまう。（＝＞１日先を計算するときに、CurrentTimeから
	** カレンダーを引っ張っている関係上、日付が進んでしまっている。為）
	** よって、単純ですが、CurrentTimeと１日進めた結果のStartTimeを比較し、StartTimeがCurrentTimeより過去となって
	** いれば、１日戻します。
	** By O.Kimoto 1997/07/17
	*/
	if (ptr->StartTime < SYB_CurrentTime) {
		if (ptr->EndTime <= SYB_CurrentTime) {
	 		ptr->StartTime += (unsigned long)(24UL * 60UL * 60UL);
	 		ptr->EndTime += (unsigned long)(24UL * 60UL * 60UL);
		}
	}
}
#endif

/*************************************************************************
	module		:[メモリバックアップの処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[]
	language	:[]
	keyword		:[]
	date		:[]
	author		:[]
*************************************************************************/
void MAN_CheckDRAM_BackUp(void)
{
	UWORD	battery;
	UDWORD	current_time;

	battery = 0;
	current_time = 0;

#if (PRO_DRAM_BACKUP == ENABLE)
	/** セマフォ獲得　1996/03/29 Eguchi */
	wai_sem(semno.rtc);
	ReadCurrentTime();					/** RTCからデータを読み込む 時刻の更新 */

	/* 1997/05/10 Y.Murata
	 * 電源ＯＦＦの間に日付がかわった時にジャーナルの通番が「１」にならない
	*/
	/*SYB_CurrentTime = CMN_BCD_TimeToLong(&CurrentTimeInBCD);*/ /** BCD データをLONG型へ変換する。*/
	current_time = CMN_BCD_TimeToLong(&CurrentTimeInBCD); /** BCD データをLONG型へ変換する。*/

	/** セマフォ解放　1996/03/29 Eguchi */
	sig_sem(semno.rtc);

	/*------------------------------------------------------------------*/
	/* あるキー押しながら電源ＯＮすると自動的にＤＲＡＭクリアを実行する */
	/* あるキーとは、ポプラではストップキーのこと						*/
	/* ＤＲＡＭバックアップ機能がない機械での電源ＯＮ時の処理と同じ		*/
	/*------------------------------------------------------------------*/
	if (CMN_ForcedDRAM_InitialKey()) {
		InitializeDRAM_Parameter();
	}
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* ﾐﾉﾙﾀ8ppmﾃｽﾄ 1998/08/11 Y.Murata */
	else if (CMN_CheckMinoltaFlashEnable()) {
		InitializeDRAM_Parameter();
	}
#endif
	else if (SYS_AutoBackUpRAM_Clear) {	/* ｵｰﾙﾗﾑｸﾘｱが実行されたら */
		InitializeDRAM_Parameter();		/* 1997/12/03 */
	}
	else if (CHK_UNI_DRAM_BackupTest()) {		/*充電／停電時間に関係なく、DRAMバックアップする場合 */
		RecoverDRAM_Parameter();
	}
#if 0 /* (PRO_KEYPANEL == PANEL_POPLAR_L) 削除 */	/* 1998/02/12  By T.Yamaguchi */
//	/*------------------------------------------------------------------*/
//	/* あるキー押しながらリセットボタンＯＮすると強制的にＤＲＡＭ		*/
//	/*バックアップを実行する。あるキーとは、ポプラではスタートキーのこと*/
//	/*------------------------------------------------------------------*/
//	else if (CMN_ForcedDRAM_BackUpKey()) {
//		RecoverDRAM_Parameter();
//	}
#endif
	else {

#if (0)	/* 1998/12/14 H.Yoshikawa */
//#if defined (SAKAKI)	/* 1998/12/11 H.Yoshikawa ＤＲＡＭ電池残量テスト用 */
//		SYS_Modem2PortStatus &= ~(0x0008);	/* IO_BIT_ND_SET */
//		outpw(MODEM2_PORT, (UWORD)SYS_Modem2PortStatus);
//		SYS_Modem2PortStatus |= (0x0008);	/* IO_BIT_ND_SET */
//		outpw(MODEM2_PORT, (UWORD)SYS_Modem2PortStatus);
//		SYS_Modem2PortStatus &= ~(0x0008);	/* IO_BIT_ND_SET */
//		outpw(MODEM2_PORT, (UWORD)SYS_Modem2PortStatus);
//#endif
#endif
		battery = AD_Battery();
#if (PRO_PRINT_TYPE == THERMAL_TRANS) /* SAKAKI */
		SYB_MaintenanceSwitch[MNT_SW_H2] = SYB_MaintenanceSwitch[MNT_SW_A5];
		SYB_MaintenanceSwitch[MNT_SW_H3] = SYB_MaintenanceSwitch[MNT_SW_A6];
#endif
		SYB_MaintenanceSwitch[MNT_SW_A5] = (UBYTE)battery;
		SYB_MaintenanceSwitch[MNT_SW_A6] = (UBYTE)(battery >> 8);
		if (SYB_MaintenanceSwitch[MNT_SW_A9] & MEMORY_BACKUP_TEST) {	/* バックアップをしなくする */
			battery = 0;	/* For Test */
		}

		/*-----------------------------------------------------------------
		** DRAMが充電されているか否かのしきい値としてAD_BATTERY_MAXを使用するようにした
		** 1998/08/31 H.Yoshikawa
		*/
#if (0)	/* 1998/08/31 H.Yoshikawa */
//		if ((battery > 0x1ff) && (CMN_CheckDRAM_BackupTestArea() == TRUE)) {
//			RecoverDRAM_Parameter();
//		}
#endif

		if ((battery > AD_BATTERY_MAX) && (CMN_CheckDRAM_BackupTestArea() == TRUE)) {
			RecoverDRAM_Parameter();
		}
		else {
			InitializeDRAM_Parameter();
		}

#if (0)
//		if (!(SYB_MaintenanceSwitch[MNT_SW_A9] & MEMORY_BACKUP_TEST)) { /*1996/07/09 Eguchi */
//			if (((SYB_DRAM_BackupTime) >= (UDWORD)((UDWORD)40 * (UDWORD)60 * (UDWORD)60)) &&	/** 40時間以上電源ＯＮ(フルに充電)されていて 24 -> 40 By Eguchi 1996/06/10 */
//				/*((SYB_CurrentTime - SYB_PowerOFF_StartTime) < (UDWORD)(CHK_UNI_DRAM_BackupTime() * (UDWORD)60 * (UDWORD)60))) {*/	/** 一定時間以内電源ＯＦＦされていたなら */
//				((current_time - SYB_PowerOFF_StartTime) < (UDWORD)(CHK_UNI_DRAM_BackupTime() * (UDWORD)60 * (UDWORD)60))) {	/** 一定時間以内電源ＯＦＦされていたなら */
//
//				RecoverDRAM_Parameter();
//
//			} else { /* ４０時間充電されていない。または放電時間（バックアップ可能時間）以上電源断 */
//				InitializeDRAM_Parameter();
//			}
//		}
//		else { /* テストモード */
//			   /* DRAMバックアップの仕様を 充電時間２時間でメモリー容量に関係なくバックアップ可能時間が１時間固定 */
//			   /* であるとしてテストを行う。（バックアップのロジックの検査にはこれで十分  */
//			if (((SYB_DRAM_BackupTime) >= (UDWORD)((UDWORD)2 * (UDWORD)60 * (UDWORD)60))
//			/*&&	((SYB_CurrentTime - SYB_PowerOFF_StartTime) < (UDWORD)((UDWORD)1 * (UDWORD)60 * (UDWORD)60))) {*/
//			&&	((current_time - SYB_PowerOFF_StartTime) < (UDWORD)((UDWORD)1 * (UDWORD)60 * (UDWORD)60))) {
//				RecoverDRAM_Parameter();
//			} else {
//				InitializeDRAM_Parameter();
//			}
//		}
#endif
	}
	SYB_DRAM_BackupTime = 0; /* 充電時間初期化 */
	/*SYB_PowerOFF_StartTime = SYB_CurrentTime;*/	/* By H.Y 1994/10/29 */
	SYB_PowerOFF_StartTime = current_time;	/* 1997/05/10 Y.Murata */
#endif
#if (PRO_DRAM_BACKUP == DISABLE)
	InitializeDRAM_Parameter();
#endif
}


/* Added by H.Kubo 1997/07/07 */
/*************************************************************************
	module		:[Ｖ３４モードで通信が実行中か否か]
	function	:[
		1.
	]
	return		:[
						1:Ｖ３４で実行中
						0:Ｖ３４を実行していない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/03/11]
	author		:[村田]
*************************************************************************/
UWORD	 SYS_V34ProcedureExecuting(void)
{
#if ( PRO_TX_SPEED == V34 )
	if (SYS_V34ProcedureExecutingFlag) {
		return(1);
	}
	else {
		return(0);
	}
#else /* ( PRO_TX_SPEED == V34 ) */
	return (0);
#endif /* ( PRO_TX_SPEED == V34 ) */
}
#if ( PRO_TX_SPEED == V34 )

/*************************************************************************
	module		:[Ｖ３４モードで通信が実行中をセット／リセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/03/11]
	author		:[村田]
*************************************************************************/
void far SYS_SetV34ProcedureExecute(unsigned char sw)
{
	if (sw == 1) {
		SYS_V34ProcedureExecutingFlag = 1;
	}
	else {
		SYS_V34ProcedureExecutingFlag = 0;
	}
}

#endif /* ( PRO_TX_SPEED == V34 ) */

/*************************************************************************
	module		:[リダイアル待ちのキューの有無を調べる]
	function	:[
		1.実行待ち状態のキューのなかにリダイアル待ちのキューの有無を調べる
		2.リダイアル待ちかどうかはリダイアルタイムがセットされているかいないかで判断する
	]
	return		:[
					TRUE:リダイアル待ちキューあり
					FALSE:リダイアル待ちキューなし
				]
	common		:[]
	condition	:[]
	comment		:[コマンドが存在することを確認してから]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1996/10/21]
	author		:[曽根岡]
*************************************************************************/
UBYTE	MAN_CheckRedialQueueExist(void)
{
	UBYTE queue_no;

	for (queue_no = 0; queue_no < SYS_EXEC_QUEUE_MAX; queue_no++) {
		if ((SYB_ExecQueue[queue_no].Status == SYS_EXEC_WAITING)
		||	(SYB_ExecQueue[queue_no].Status == SYS_EXEC_FORWARD_WAITING)) {
			/*-------------------------------------------------------------
			** 新JATE基準９８では、リダイヤル間隔で０分が設定できます。
			** この時、RedialTime = 0でFCMが終了し、５秒後に再発呼することになる。
			** この５秒の間、「予約中」->「リダイヤル待ち」表示となるようにします。
			**	if (SYB_ExecQueue[queue_no].RedialTime >= 0) [
			** としてしまうと、予約中表示がでなくなります。
			** というわけで、リダイヤル間隔が０分時のリダイヤル待ちの場合は
			**「予約中」表示されるころを仕様とします。
			** 1998/10/15 H.Yoshikawa
			*/
			if (SYB_ExecQueue[queue_no].RedialTime > 0) {
				return (TRUE);
			}
		}
	}
	return (FALSE);
}


#if (0)
** /* 下記３つの関数は未使用ですので、コメントにします。 by O.Kimoto 1998/09/01 */
** #if (PRO_CIPHER == ENABLE)
** /** Module Header For CIM-E ********************************************
** 		module		:	[スクランブル受信解除プリントのキャンセル]
** 		function	:	[]
** 		return		:	[]
** 		common		:	[]
** 		condition	:	[]
** 		comment		:	[]
** 		machine		:	[SH7043]
** 		language	:	[SHC]
** 		keyword		:	[MAN]
** 		date		:	[98/01/02]
** 		author		:	[鈴木郁二]
** ************************************************************************/
** void CipherRxDocPrintNG(void)
** {
** 	SYB_CPH_RxPrint[0].Status = SYS_MCOPY_EMPTY;
** 	SYB_CPH_RxPrint[0].ExecutiveNumber = 0;
** 	SYB_CPH_RxPrint[0].StorePage = 0;
** 	SYB_CPH_RxPrint[0].PrintPage = 0;
** 	SYB_CipherPrintItem = SYS_MEM_FILE_EMPTY;
** }
** 
** 
** /** Module Header For CIM-E ********************************************
** 		module		:	[スクランブル受信解除プリントの登録終了]
** 		function	:	[]
** 		return		:	[]
** 		common		:	[]
** 		condition	:	[]
** 		comment		:	[]
** 		machine		:	[SH7043]
** 		language	:	[SHC]
** 		keyword		:	[MAN]
** 		date		:	[98/01/12]
** 		author		:	[鈴木郁二]
** ************************************************************************/
** void CipherRxDocStoreOK(void)
** {
** 
** 	SYB_CPH_RxPrint[0].Status = SYS_MCOPY_PRINT;	/* add by J.M 1994/05/13 */
** 	SYB_CPH_RxPrint[0].ExecutiveNumber = 1;
** 	if (SYB_CipherPrintItem == SYS_MEM_TX_DECIPHER_FILE) {
** 		SYB_CPH_RxPrint[0].StorePage = MEM_CountTotalPage(SYS_MEM_TX_DECIPHER_FILE, (UWORD)CipherStoreData.No, MEM_IGNORE_BOX_NUMBER);
** 	}
** 	else {
** 		SYB_CPH_RxPrint[0].StorePage = MEM_CountTotalPage(SYS_MEM_DECIPHER_FILE, (UWORD)CipherStoreData.No, MEM_IGNORE_BOX_NUMBER);
** 	}
** 	SYB_CPH_RxPrint[0].PrintPage = 1;
** }
** 
** 
** /*************************************************************************
** 	module		:[スクランブル受信解除プリントでメモリオーバー時の処理]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[
** 		MultiCopyDocStoreOK() を SYS_MCOPY_MEMORY_OVER にしただけ
** 	]
** 	machine		:[V53]
** 	language	:[MS-C(Ver.6.0)]
** 	keyword		:[CMN]
** 	date		:[1996/12/18]
** 	author		:[鈴木郁二]
** *************************************************************************/
** void	CipherRxDocStoreMemoryOver(void)
** {
** 	struct SYS_MultiCopyData_t	* cipher_print_file;
** 
** 	cipher_print_file = &SYB_CPH_RxPrint[0];
** 
** 	cipher_print_file->Status = SYS_MCOPY_MEMORY_OVER;
** 	if (SYB_CipherPrintItem == SYS_MEM_TX_DECIPHER_FILE) {
** 		cipher_print_file->StorePage = MEM_CountMaxPage( SYS_MEM_TX_DECIPHER_FILE, (UWORD)CipherStoreData.No, MEM_IGNORE_BOX_NUMBER);
** 	}
** 	else {
** 		cipher_print_file->StorePage = MEM_CountMaxPage( SYS_MEM_DECIPHER_FILE, (UWORD)CipherStoreData.No, MEM_IGNORE_BOX_NUMBER);
** 	}
** 
** 	cipher_print_file->PrintPage = 1;
** 
** }
** 
** #endif/* PRO_CIPHER */
#endif


#if (PRO_CL1_TELFAX_LAN == ENABLE) 
/*************************************************************************
	module		:[メモリ受信原稿プリントの動作状態を未使用にする]
	function	:[
		1.TEL/FAX,FAX/TEL,転送受信等でメモリ受信原稿プリントを
          SYS_MEMORY_RX_SETTINGでキープし、ＣＬＡＳＳ１に移行する
          際、未使用状態に戻す。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1998/06/19]
	author		:[福井知史]
*************************************************************************/
void	ClearMemoryRxSetting(void)
{
	UWORD	memory_rx_num;

	for (memory_rx_num = 0; memory_rx_num < SYS_MEMORY_RX_MAX; memory_rx_num++) {
		if (SYB_MemoryRxPrint[memory_rx_num].Status == SYS_MEMORY_RX_SETTING) {
#if (PRO_LINENUMBER == TWICE_LINE)
			if ((SYB_MemoryRxPrint[memory_rx_num].StackNumber & 0x7f) == (UBYTE)0) {
				break;
			}
#else
			if (SYB_MemoryRxPrint[memory_rx_num].StackNumber == (UBYTE)0) {
				break;
			}
#endif
		}
	}
	if (memory_rx_num < SYS_MEMORY_RX_MAX) {
		MemoryRxPrintPoint = &SYB_MemoryRxPrint[memory_rx_num];
		MemoryRxPrintPoint->Status = SYS_MEMORY_RX_EMPTY;
		MemoryRxPrintPoint->StorePage = 0;
		MemoryRxPrintPoint->RotatePage = 1;
		MemoryRxPrintPoint->PrintPage = 1;
		MemoryRxPrintPoint->ErasePage = 1;
		MemoryRxPrintPoint->Protect	  = SYS_PROTECT_OFF; /**受信原稿プリントプロテクト初期化 */
		MemoryRxPrintPoint->StackNumber = 0;
		MemoryRxPrintPoint->ReceiveTime = 0;
		MemoryRxPrintPoint->JournalPoint = 0;
	}
}
#endif

/*************************************************************************
	module		:[プリンタ受信可能か？]
	function	:[
		１．プリンタ使用可能か？
		２．スキャナ使用中か？
	]
	return		:[
		TRUE:可能
		FALSE:不可能
	]
	common		:[]
	condition	:[原稿蓄積の条件を追加 by H.Hirao 1998/12/17
				  強制メモリ受信のみの場合、FALSEをリターン]
	comment		:[とりあえず、プリンタ使用可能か？]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[MAN]
	date		:[1998/11/11]
	author		:[H.Hirao]
*************************************************************************/
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/11/11 */
UBYTE QueryPRxEnable(void)
{
  #if (0) /* (PRO_SCN_CODEC_TYPE == SOFTWARE) commented by H.Hirao 1998/12/24 */
//	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT)) {
//		/* if (CMN_CheckScanEnable()) { */
//		if (CMN_CheckScanEnable() && (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE))
//			return (FALSE);
//		else
//			return (TRUE);
//	else
//		return (FALSE);
  #else
  	/*
  	** Ｖ３４マスク かつ Ｖ１７以下強制メモリ受信設定
  	** 又は、Ｖ３４マスク否 かつ Ｖ１７以下強制メモリ受信 かつ Ｖ３４強制メモリ受信の場合、
  	** プリンタ受信不可 by H.Hirao 1998/12/24
  	*/
  	if ((CHK_V34SiganalRateV34Mask() && (CHK_UNI_V17ReceiveType() == V17_MRX_TO_MRX))
  	 || (!CHK_V34SiganalRateV34Mask() && (CHK_UNI_V17ReceiveType() == V17_MRX_TO_MRX) && (CHK_UNI_V34ReceiveType() == V34_MRX_TO_MRX))) {
		return (FALSE);
	}
	else {
  		if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT)) {
  			return (TRUE);
  		}
		else {
			return (FALSE);
		}
	}
  #endif
}

/* ＴＥＬ／ＦＡＸやＦＡＸ／ＴＥＬで着信後、疑似ベル中のＣＮＧ検出時に使用
** by O.kimoto 1999/02/27
*/
UBYTE QueryPRxEnableWholeCNGDetect(void)
{
	/*
	** Ｖ３４マスク かつ Ｖ１７以下強制メモリ受信設定
	** 又は、Ｖ３４マスク否 かつ Ｖ１７以下強制メモリ受信 かつ Ｖ３４強制メモリ受信の場合、
	** プリンタ受信不可 by H.Hirao 1998/12/24
	*/
	if ((CHK_V34SiganalRateV34Mask() && (CHK_UNI_V17ReceiveType() == V17_MRX_TO_MRX))
	 || (!CHK_V34SiganalRateV34Mask() && (CHK_UNI_V17ReceiveType() == V17_MRX_TO_MRX) && (CHK_UNI_V34ReceiveType() == V34_MRX_TO_MRX))) {
		return (FALSE);
	}
	else {
		if (CMN_CheckFaxComPrinterError()) {	/* プリンターエラーが発生している？ */
			return(FALSE);
		}
		else  {
			if (CMN_CheckFaxComPrinterEnable()) {	/* 通信がプリンターがつかんだ？ */
				return(TRUE);
			}
			else {
				return (FALSE);
			}
		}
	}
}
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999.3.4 K.Kawata */
UBYTE QueryPRxEnable(void)
{
	if (CHK_V34SiganalRateV34Mask()) {
		if (CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) {
			return (FALSE);
		}
	}
	else {
		if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) && (CHK_UNI_V34ReceiveType() != V34_PRX_TO_PRX)) {
			return (FALSE);
		}
	}
	if (CMN_CheckPrintEnable(SYS_IMAGE_PRINT)) {
 			return (TRUE);
	}
	return (FALSE);
}

/* ＴＥＬ／ＦＡＸやＦＡＸ／ＴＥＬで着信後、疑似ベル中のＣＮＧ検出時に使用 */
UBYTE QueryPRxEnableWholeCNGDetect(void)
{
	if (CHK_V34SiganalRateV34Mask()) {
		if (CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) {
			return (FALSE);
		}
	}
	else {
		if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) && (CHK_UNI_V34ReceiveType() != V34_PRX_TO_PRX)) {
			return (FALSE);
		}
	}
	if (PRN_PrintRxErrorHaltREQ() == NG) {	/* プリンターエラーが発生している？ */
		return(FALSE);
	}
	else  {
		if (CMN_CheckFaxComPrinterEnable()) {
			return(TRUE);
		}
		return (FALSE);
	}
}

UBYTE QueryWarpAndSecurityDisable(void)
{
#if (PRO_RX_DOC_TRANSFER == ENABLE)
  #if (PRO_NUMBER_DISPLAY_WARP == ENABLE)	/* Add By H.Fujimura 1999/01/07 */
	if ((CHK_WarpFunctionON() || CHK_ND_WarpON()) && CheckWarpRx()) {
  #else
	if (CHK_WarpFunctionON() && CheckWarpRx()) {
  #endif
		return(FALSE);
	}
#endif
#if (PRO_SECURITY_RX == ENABLE)
		if (SYB_SecurityRxModeFlag == 1) {/** セキュリティ受信モード中 */
			return(FALSE);
		}
#endif
	return (TRUE);
}
#endif
/*************************************************************************
	module		:[原稿蓄積可能か？]
	function	:[
		１．通信中？
		２．通信以外のタスクがプリンタを使用していない？
	]
	return		:[
		TRUE:可能
		FALSE:不可能
	]
	common		:[]
	condition	:[]
	comment		:[プリンタ受信中の原稿蓄積を制限します
				  Ｇ３プリンタ受信中にソフトコーデックで原稿蓄積はデュアル制限
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[MAN]
	date		:[1998/12/17]
	author		:[H.Hirao]
*************************************************************************/
#if (PRO_PRINTER_RX == ENABLE) /* added by H.Hirao 1998/12/17 */
 #if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103) /* (PRO_SCN_CODEC_TYPE == SOFTWARE) changed by H.Hirao 1998/12/26 */
UBYTE QueryDocStoreEnable(void)
{
#if (0)
**	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
**		if (CMN_CheckFaxComPrinterEnable()){
**			return (FALSE);
**		}
**		else {
**			return (TRUE);
**		}
**	}
**	else {
**		return (TRUE);
**	}
#else
	if ((SYS_DualRestrictionStatus & 0x01) == 0x01)
		return (FALSE);
	else
		return (TRUE);
#endif
}

 #endif
#endif

/*************************************************************************
	module		:[着信可能？（受信／原稿蓄積デュアル制限用）]
	function	:[
		１．
	]
	return		:[
		TRUE:可能
		FALSE:不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[MAN]
	date		:[1998/12/26]
	author		:[H.Hirao]
*************************************************************************/
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
UBYTE QueryAutoCalledEnable(UBYTE mode)
{
	switch (mode) {
	case 0:
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || CheckPollingTxType() || QueryPRxEnable()) {
			CMN_DisableInterrupt();
			if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中でなければ */
				/*
				** ＤＵＡＬ制限変更のため
				** 強制メモリ受信以外のときは、スキャナを停止処理をいれます
				** 1999/02/18 by T.Soneoka
				*/
#if (0)
**				SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
#else
				if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
					SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
				}
#endif
				CMN_EnableInterrupt();
				return (TRUE);
			}
			else {
				CMN_EnableInterrupt();
				return (FALSE);
			}
		}
		else {
			return (FALSE);
		}
		break;
	case 1:
		if ((SYB_MemoryRxPrintWritePoint < SYS_MEMORY_RX_MAX) || QueryPRxEnable()) {
			CMN_DisableInterrupt();
			if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中でなければ */
				/*
				** ＤＵＡＬ制限変更のため
				** 強制メモリ受信以外のときは、スキャナを停止処理をいれます
				** 1999/02/18 by T.Soneoka
				*/
#if (0)
**				SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
#else
				if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
					SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
				}
#endif
				CMN_EnableInterrupt();
				return (TRUE);
			}
			else {
				CMN_EnableInterrupt();
				return (FALSE);
			}
		}
		else {
			return (FALSE);
		}
		break;
	default:
		break;
	}
}
#endif

/*************************************************************************
	module		:[発呼可能？（受信／原稿蓄積デュアル制限用）]
	function	:[
		１．ポーリング受信コマンドなら、
	]
	return		:[
		TRUE:可能
		FALSE:不可能
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SH-C]
	keyword		:[MAN]
	date		:[1998/12/29]
	author		:[H.Hirao]
*************************************************************************/
#if (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
UBYTE QueryCommunicationStartEnable(UBYTE exec_no)	/* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */

{
#if (0)
** 	/* 呼び元の条件の書く順番に依存しているので、順番の依存性が無いように修正 by O.Kimoto 1999/01/25 */
** 	if (CheckPollingRxCommand(SYB_ExecQueue[exec_no].Number.Command)) {	/* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
** 		CMN_DisableInterrupt();
** 		if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中でなければ */
** 			SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
** 			CMN_EnableInterrupt();
** 			return (TRUE);
** 		}
** 		else {
** 			CMN_EnableInterrupt();
** 			return (FALSE);
** 		}
** 	}
** 	else {
** 			return (TRUE);
** 	}
#else

	/* 強制プリンター受信設定時、プリンターエラーが発生していた場合は、発呼しないように
	** します。（下記IF文追加）
	** by O.Kimoto 1999/01/28
	*/
	if (exec_no < SYS_EXEC_QUEUE_MAX)  {
/*
** ＤＵＡＬ制限変更のため
** スキャナ制限からプリント制限へ変更する
** 1999/02/18 by T.Soneoka
*/
#if (0)
**		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)
**			&& CHK_MANSameDocumentAccess(exec_no)
**			&& QueryMultiEnable()) {
#else
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/08/22 */
		if (CMN_CheckTwiceLineEnable(SYB_ExecQueueKeisatsu[exec_no].Line)
			&& (SYS_VariableTimer == 0)
#else /* !defined (KEISATSU) */
		if (CMN_CheckLineEnable() && (SYS_VariableTimer == 0)
#endif /* defined (KEISATSU) */
			&& CHK_MANSameDocumentAccess(exec_no)) {
#endif
			if (CheckPollingRxCommand(SYB_ExecQueue[exec_no].Number.Command)) {	/* 送信時、「ソウシン」と表示される不具合修正 by O.Kimoto 1999/01/25 */
				/* 強制プリンター受信設定時、プリンターエラーが発生していた場合は、発呼しないように
				** します。
				** by O.Kimoto 1999/01/27
				*/
				if (CHK_UNI_V17ReceiveType() == V17_PRX_TO_PRX) { /* under V.17 */
					if (!CHK_V34SiganalRateV34Mask() && (CHK_UNI_V34ReceiveType() == V34_PRX_TO_PRX)) {	/* V.34 */

#if (0)
** 						/* ここでは、プリンター動作中とプリンターエラー発生状況は分けて処理します。
** 						** by O.Kimoto 1999/01/29
** 						*/
** 						if(CMN_CheckPrintEnable(0) == FALSE) {	/* Check Printer Error */
** 							SYB_ExecQueue[exec_no].Result = (UWORD)(RECEIVEERROR | 0x0045);				/** 交信結果 */
** 							SYB_ExecQueue[exec_no].Status = SYS_EXEC_ERROR;			/** エラー終了 */
** 							return(FALSE);
** 						}
#else
						if (CMN_CheckFaxComPrinterError() == TRUE) {	/* Check Printer Error */
							SYB_ExecQueue[exec_no].Result = (UWORD)(RECEIVEERROR | 0x0045);				/** 交信結果 */
							SYB_ExecQueue[exec_no].Status = SYS_EXEC_ERROR;			/** エラー終了 */
							return(FALSE);
						}
						else if (CMN_CheckPrinting() == TRUE) {
							return(FALSE);
						}
#endif

					}
					else if (CHK_V34SiganalRateV34Mask()) {

#if (0)
** 						/* ここでは、プリンター動作中とプリンターエラー発生状況は分けて処理します。
** 						** by O.Kimoto 1999/01/29
** 						*/
** 						if(CMN_CheckPrintEnable(0) == FALSE) {	/* Check Printer Error */
** 							SYB_ExecQueue[exec_no].Result = (UWORD)(RECEIVEERROR | 0x0045);				/** 交信結果 */
** 							SYB_ExecQueue[exec_no].Status = SYS_EXEC_ERROR;			/** エラー終了 */
** 							return(FALSE);
** 						}
#else
						if (CMN_CheckFaxComPrinterError() == TRUE) {	/* Check Printer Error */
							SYB_ExecQueue[exec_no].Result = (UWORD)(RECEIVEERROR | 0x0045);				/** 交信結果 */
							SYB_ExecQueue[exec_no].Status = SYS_EXEC_ERROR;			/** エラー終了 */
							return(FALSE);
						}
						else if (CMN_CheckPrinting() == TRUE) {
							return(FALSE);
						}
#endif

					}
				}

				CMN_DisableInterrupt();
				if ((SYS_DualRestrictionStatus & 0x02) != 0x02) {	/* 原稿蓄積中でなければ */
					/*
					** ＤＵＡＬ制限変更のため
					** 強制メモリ受信以外のときは、スキャナを停止処理をいれます
					** 1999/02/18 by T.Soneoka
					*/
#if (0)
**					SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
#else
					if ((CHK_UNI_V17ReceiveType() != V17_MRX_TO_MRX) ||	(CHK_UNI_V34ReceiveType() != V34_MRX_TO_MRX)) {
						SYS_DualRestrictionStatus |= 0x01;	/* 受信中をセット */
					}
#endif
					CMN_EnableInterrupt();
					return (TRUE);
				}
				else {
					CMN_EnableInterrupt();
					return (FALSE);
				}
			}
			else {
					return (TRUE);
			}
		}
		else {
			return (FALSE);
		}
	}
	else {
		return (FALSE);
	}
#endif

}
#endif

/*
** ＤＵＡＬ制限変更のため
** スキャナ制限からプリント制限へ変更するため、削除します
** 1999/02/18 by T.Soneoka
*/
#if (0)
**#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
**/*************************************************************************
**	module		:[マルチ動作制限]
**	function	:[
**		１．蓄積            －イメージプリント －＞ メモリ送信禁止
**		    蓄積            －メモリ送信       －＞ イメージプリント禁止
**		２．イメージプリント－蓄積             －＞ メモリ送信禁止
**		    イメージプリント－メモリ送信       －＞ 蓄積禁止
**		３．メモリ送信      －蓄積             －＞ イメージプリント禁止
**		    メモリ送信      －イメージプリント －＞ 蓄積禁止
**	]
**	return		:[
**		TRUE :マルチ動作可能
**		FALSE:マルチ動作不可能
**	]
**	common		:[]
**	condition	:[]
**	comment		:[]
**	machine		:[SH7043]
**	language	:[SH-C]
**	keyword		:[MAN]
**	date		:[1999/1/14]
**	author		:[T.Soneoka]
***************************************************************************/
**UBYTE QueryMultiEnable(void)
**{
**	UBYTE is_memory_tx;
**	UBYTE multi_action_count;
**	
**	multi_action_count = 0;
**	
**	/* 蓄積中の判断 */
**	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
**	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE)) {
**#if (0) /* 1999/01/20 by T.Soneoka */
****		multi_action_count++;
**#else
**		/* 蓄積中でも一時中断中の場合はカウントしないように修正します  1999/01/20 by T.Soneoka */
**#if (0) /* チェックする条件が逆 1999/1/22 by T.Soneoka */
****		if (SYS_DualRestrictionStatus & 0x04) {
****			multi_action_count++;
****		}
**#else
**		if (!(SYS_DualRestrictionStatus & 0x04)) {
**			multi_action_count++;
**		}
**#endif
**#endif
**	}
**#if (0) /* マルチコピーの場合が抜けていた 1999/1/19 by T.Soneoka */
****	/* キャラクタ・イメージプリント中の判断 */
****	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
****	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT | SYS_LIST_PRINT))) {
**#else
**	/* キャラクタ・イメージプリント・マルチコピー中の判断 */
**	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
**	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT | SYS_LIST_PRINT | SYS_MULTI_COPY))) {
**#endif
**		multi_action_count++;
**	}
**	/* 通信中の判断 */
**	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)
**	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
**		multi_action_count++;
**	}
**	if (multi_action_count <= 1) {
**		return (TRUE);
**	}
**	return (FALSE);
#endif


/*
** ＤＵＡＬ制限変更のため、追加します
** 1999/02/18 by T.Soneoka
*/
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
UBYTE QueryResourceCount(void)
{
	UBYTE multi_action_count;
	
	multi_action_count = 0;
	
	/* スキャナ使用中（原稿蓄積・スキャナ送信）の判断 */
	if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY) {
		multi_action_count++;
	}
	/* キャラクタ・イメージプリント・マルチコピー中の判断 */
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT | SYS_LIST_PRINT | SYS_MULTI_COPY))) {
		multi_action_count++;
	}
	/* 通信中の判断 */
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)
	&&  (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
		multi_action_count++;
	}
	return (multi_action_count);
}
#endif


#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
/*************************************************************************
	module		:[クラス１が動作可能か？（クラス１デュアル制限用）]
	function	:[
		1.
	]
	return		:[TURE   : 可能
				  FALSE  : 不可能]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1999/02/01]
	author		:[平尾 英典]
*************************************************************************/
UBYTE QueryClass1Enable(UBYTE mode)
{
	if (mode == 0) {
		if (!CMN_CheckPrinting()		/* プリンタ使用可能 */
		 && CMN_CheckScanEnable()		/* スキャナ使用可能 */
		 && CMN_CheckLineEnable()) {	/* 回線使用可能 */
			return (TRUE);
		}
		else {
			return (FALSE);
		}
	}
	else if (mode == 1) {
		if (!CMN_CheckPrinting()		/* プリンタ使用可能 */
		 && CMN_CheckScanEnable()		/* スキャナ使用可能 */
		 && !(SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_LINE_BUSY)) {
			return (TRUE);
		}
		else {
			return (FALSE);
		}
	}
	else if (mode == 2) {
		if (!CMN_CheckPrinting()	/* プリンタ使用可能 */
		 && CMN_CheckScanEnable()	/* スキャナ使用可能 */
		 && !(SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
			return (TRUE);
		}
		else {
			return (FALSE);
		}
	}
	else {
		return (TRUE);
	}
}
#endif

/* debug */
void MAN_Anzudebug(void)
{
#if 0
	UBYTE	dummy;
	UWORD	i;
	UWORD	j;
	struct SYS_FactoryOptModemData_t function_data;

	dummy = 1;

/*#if defined(ANZU_L)*/
	DPR_GetT30Buffer((UWORD *)&SYB_T30Monitor.JournalType, 0);
	DPR_GetInternalStatus(0);
	DPR_SetBitStopFaxcom(0);

	function_data.Item = 0x0102;
	function_data.Kind = 0x0304;
	function_data.BaudRate = 0x0405;
	function_data.DataRate = 0x0506;
	function_data.PIX_Pattern = 0x0607;
	function_data.StackNumber = 0x0809;
	DPR_SendFactoryFunctionData(&function_data, 0);	/* ｺﾏﾝﾄﾞ発行 */

	SYS_ChangedSRAM_Status = 0x1234;
	DPR_ChangedSRAM_Parameter(0);
	DPR_CheckVoiceAccepted(0);
#endif

#if 0
/*#if defined(ANZU_L)*/
/*ｺﾏﾝﾄﾞﾌｧｲﾙ */
	SYB_CommandFile[0].Status = SYS_CMD_EXECUTE;	/* 3 */
	for (i = 0; i < SYS_PIN_MAX; i++) {
		SYB_CommandFile[0].DialNumber.PIN_Number[5][i] = i + 1;
	}
	for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
		SYB_CommandFile[0].DialNumber.Direct[5][i] = i + 0x30;
	}
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		SYB_CommandFile[0].DialNumber.Onetouch[i] = i + 0x11;
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		SYB_CommandFile[0].DialNumber.Speed[i] = i + 0x21;
	}
	SYB_CommandFile[0].DialNumber.Group = 0xabcdefbc;
	SYB_CommandFile[0].ExecTime = 0x12345678;
	SYB_CommandFile[0].Option.Item = SYS_MEMORY_SECURE_TX;	/* 6:SYS_MEMORY_SECURE_TX */
															/* 8:SYS_MEMORY_RELAY_BROADCAST */
															/* 10:SYS_RELAYED_TX */
															/* 12:SYS_DB_POLLING_RX */
	switch (SYB_CommandFile[0].Option.Item) {
	case SYS_MEMORY_SECURE_TX:
		SYB_CommandFile[0].Option.OptionNumber.SecureNumber = 0x4567;
		break;
	case SYS_MEMORY_RELAY_BROADCAST:
		SYB_CommandFile[0].Option.OptionNumber.RelayGroupNumber = 0xabcdefcd;
		break;
	case SYS_RELAYED_TX:
		for (i = 0; i < SYS_SRC_ID_MAX; i++) {
			SYB_CommandFile[0].Option.OptionNumber.RelaySourceID[i] = i + 0x41;
		}
		break;
	case SYS_DB_POLLING_RX:
		for (i = 0; i < SYS_DATA_BASE_MAX; i++) {
			SYB_CommandFile[0].Option.OptionNumber.DatabaseNumber[i] = i + 0x3401;
		}
		break;
	}
	SYB_CommandFile[0].Option.ConfirmationReport = 0xa1;
	SYB_CommandFile[0].DepartmentCode = 0x3456;
	SYB_CommandFile[0].Page = 0x7890;
	SYB_CommandFile[0].Type = 0x01;
	SYB_CommandFile[0].TitleMessage = 0x02;
	SYB_CommandFile[0].Ability = 0x03;
	SYB_CommandFile[0].PIN_AccessMode = 0x04;
	for (i = 0; i < SYS_PIN_MAX; i++) {
		SYB_CommandFile[0].PIN_Number[i] = i + 0x05;
	}

/* 発信ｷｭｰ */
	SYB_ExecQueue[1].Status = SYS_EXEC_EXECUTE;		/* 2 */
	SYB_ExecQueue[1].Kind = 0x1;
	SYB_ExecQueue[1].Number.Command = 0x12;
	SYB_ExecQueue[1].RedialCount = 0x13;
	SYB_ExecQueue[1].RedialTime = 0x14;
	SYB_ExecQueue[1].Mode = 0x15;
	SYB_ExecQueue[1].Option = 0x16;
	SYB_ExecQueue[1].StartTime = 0x51525354;
	SYB_ExecQueue[1].Page = 0x1234;
	SYB_ExecQueue[1].TotalTime = 0x5678;
	SYB_ExecQueue[1].Result = 0xabcd;
	SYB_ExecQueue[1].ExecDial.Item = SYS_DIRECT_DIAL;	/* 1:SYS_DIRECT_DIAL */
														/* 2:SYS_ONETOUCH_DIAL */
														/* 3:SYS_SPEED_DIAL */
	switch (SYB_ExecQueue[1].ExecDial.Item) {
	case SYS_DIRECT_DIAL:
		SYB_ExecQueue[1].ExecDial.ExecNumber.Command = 0x05;
		break;
	case SYS_ONETOUCH_DIAL:
		SYB_ExecQueue[1].ExecDial.ExecNumber.Onetouch = 0x06;
		break;
	case SYS_SPEED_DIAL:
		SYB_ExecQueue[1].ExecDial.ExecNumber.Speed = 0x1234;
		break;
	}
	for (i = 0; i < SYS_ERROR_PAGE; i ++) {
		SYB_ExecQueue[1].ErrorPage[i] = i + 0x70;
	}
	SYB_ExecQueue[1].StackNumber = 0x01;

/*一括 */
	SYB_BatchTxFile[0].Status = SYS_CMD_EXECUTE;	/* 3 */
	SYB_BatchTxFile[0].DialNumber[0].Item = SYS_DIRECT_DIAL;/*1:SYS_DIRECT_DIAL*/
															 /*2:SYS_ONETOUCH_DIAL*/
															 /*3:SYS_SPEED_DIAL*/
	switch (SYB_BatchTxFile[0].DialNumber[0].Item) {
	case SYS_DIRECT_DIAL:
		for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
			SYB_BatchTxFile[0].DialNumber[0].FaxNumber.Direct[i] = (UBYTE)((UBYTE)i + 0x20);
		}
		break;
	case SYS_ONETOUCH_DIAL:
		SYB_BatchTxFile[0].DialNumber[0].FaxNumber.Onetouch = 0xaa;
		break;
	case SYS_SPEED_DIAL:
		SYB_BatchTxFile[0].DialNumber[0].FaxNumber.Speed = 0xabcd;
		break;
	}
	SYB_BatchTxFile[0].ExecTime = 0x12345678;
	SYB_BatchTxFile[0].ProgramTime = 0xa1a2a3a4;
	SYB_BatchTxFile[0].Page = 0x8899;
	for (i = 0; i < SYS_BATCH_NAME_MAX; i++) {
		SYB_BatchTxFile[0].Name[i] = 0x80 + i;
	}
	for (i = 0; i < SYS_BATCH_INDEX_MAX; i++) {
		SYB_BatchTxFile[0].IndexNo[i] = 0xbb00 + i;
	}

/*連ﾎﾟｰ */
	SYB_ExecQueue[1].ExecDial.Item = SYS_DIRECT_DIAL;
	SYB_ExecQueue[1].ExecDial.ExecNumber.Command = 5;

	SYB_ContinuousPolling.Status = SYS_CMD_EXECUTE;	/* 3 */
	SYB_ContinuousPolling.DepartmentCode = 0x5678;
	SYB_ContinuousPolling.StartTime = 0xb1b2b3b4;
	SYB_ContinuousPolling.EndTime = 0xc1c2c3c4;
	for (i = 0; i < SYS_PIN_MAX; i++) {
		SYB_ContinuousPolling.DialNumber.PIN_Number[5][i] = i + 1;
	}
	for (i = 0; i < SYS_DIRECT_DIAL_MAX; i++) {
		SYB_ContinuousPolling.DialNumber.Direct[5][i] = i + 0x30;
	}
	for (i = 0; i < SYS_ONETOUCH_BIT_FIELD_MAX; i++) {
		SYB_ContinuousPolling.DialNumber.Onetouch[i] = i + 0x11;
	}
	for (i = 0; i < SYS_SPEED_BIT_FIELD_MAX; i++) {
		SYB_ContinuousPolling.DialNumber.Speed[i] = i + 0x21;
	}
	SYB_ContinuousPolling.DialNumber.Group = 0xabcdefbc;

	SYB_ContinuousPolling.PIN_AccessMode = 0xbc;
	for (i = 0; i < SYS_PIN_MAX; i++) {
		SYB_ContinuousPolling.PIN_AccessNumber[i] = i + 0xe0;
	}

/*親展*/
	for (j = 0; j < SYS_MAILBOX_MAX; j++) {
		SYB_MailBox[j].Status = SYS_MAILBOX_RECEIVE;		/* 2 */
		SYB_MailBox[j].MessageStatus = SYS_MAILBOX_RCV_MSG;	/* 1 */
		for (i = 0; i < SYS_REMOTE_NAME_MAX; i++) {
			SYB_MailBox[j].RemoteName[i] = (unsigned char)(i + 0x41);
		}
		for (i = 0; i < SYS_BOX_NAME_MAX; i++) {
			SYB_MailBox[j].BoxName[i] = (unsigned char)(i + 0x30);
		}
		SYB_MailBox[j].PassCode = 0x1234;
		SYB_MailBox[j].ErasedTime = 0x12345678;
	}

#endif
#if 0
** /*#if (PRO_KEYPANEL == PANEL_ANZU_L)*/
** 	UBYTE	data;
** 
** 	data = DSW();
** 	/* LED */
** 	AutoRxLedOn();
** 	AutoRxLedOff();
** 	AutoRxLedOn();
** 
** 	MemoryTxLedOn();
** 	MemoryTxLedOff();
** 	MemoryTxLedOn();
** 
** 	MemoryRxLedOn();
** 	MemoryRxLedOff();
** 	MemoryRxLedOn();
** 
** 	HookLedOn();
** 	HookLedOff();
** 	HookLedOn();
** 
** 	AlarmLedOn();
** 	AlarmLedOff();
** 	AlarmLedOn();
** 
** 	FaxComLedOn();
** 	FaxComLedOff();
** 	FaxComLedOn();
** 
** 	SYB_ModeSw = SYS_FINE;
** 	ModeLedOn();
** 	SYB_ModeSw = SYS_SFINE;
** 	ModeLedOn();
** 	SYB_ModeSw = SYS_GRAY16;
** 	ModeLedOn();
** 	SYB_ModeSw = SYS_NORMAL;
** 	ModeLedOn();
** 
** 	SYB_DensitySw = SYS_DARK_DENSITY;
** 	DensityLedOn();
** 	SYB_DensitySw = SYS_LIGHT_DENSITY;
** 	DensityLedOn();
** 	SYB_DensitySw = SYS_NORMAL_DENSITY;
** 	DensityLedOn();
** 
** 	ReplacePaperLedOn();
** 	ReplacePaperLedOff();
** 	ReplacePaperLedOn();
** 
** 	PaperJamLedOn();
** 	PaperJamLedOff();
** 	PaperJamLedOn();
** 
** 	PrinterAlarmLedOn();
** 	PrinterAlarmLedOff();
** 	PrinterAlarmLedOn();
** 
** 	StampLedOn();
** 	StampLedOff();
** 	StampLedOn();
** 
** 	LED_Initial();
** 
** 	AllLedOn();
** 	AllLedOff();
** 	AllLedOn();
** 
#endif
}
#if defined(ANZU_L)
void TestDataClear(void)
{
	UBYTE	i;

	for (i = 0; i < 5; i++) {
		dpr_testdata1[i] = 0xaa;
		dpr_testdata2[i] = 0xbb;
		dpr_testdata3[i] = 0xcc;
		dpr_testdata4[i] = 0xdddd;
		dpr_testdata5[i] = 0xeeee;
	}
	for (i = 0; i < 6; i++) {
		dpr_testdata6[i] = 0xff;
		dpr_testdata7[i] = 0xab;
		dpr_testdata8[i] = 0xcd;
	}
}
#endif


#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/09 Y.Murata for KAKI */
/*
 * クイックメモリ送信をするか否かのチェック
*/
UBYTE CheckQuickMemoryTxOK(UBYTE item, UBYTE command_no)
{
	UWORD	empty_block;
	UBYTE	debug;

	empty_block = 0;

	#if 0
		if () {	/* クイックメモリ送信設定でない */
			return(0);
		}
	#endif

	/** メモリ送信かどうか */
	if (item != SYS_MEM_TX_FILE) {
		return(0);
	}

	if (SYB_CommandFile[command_no].Status != SYS_CMD_SETTING) {
		return(0);
	}

	debug = 0;
	if (debug) {
		if (SYS_DocumentStorePage < 2) {
			return(0);
		}
	}

	/* 原稿枚数指定がされているかどうかのチェック */
	if (SYB_CommandFile[command_no].Page != 0) {
		return(0);
	}

	/* メモリ残量のチェック */
	if (CMN_CheckMemoryQucikTxStart() == 0) {
		return(0);
	}

	/** 同報かどうかのチェック */
	if (CheckCommandBroadcast(command_no) != 1) {
		return(0);
	}

	SYB_CommandFile[command_no].Page = 0;
	SYB_CommandFile[command_no].Status = SYS_CMD_WAITING;
	SYB_CommandStatus[command_no] = SYS_CMD_WAITING;
	return(1);
}

UBYTE SYS_QuickTxStopSwitch(UBYTE stack_number)
{
	UBYTE	num;

	num = (0x01 << stack_number);

	if (SYS_QucikTxStopStatus & (UWORD)num) {
		return(1);
	}
	else {
		return(0);
	}
}
#endif	/* End of (PRO_QUICK_TX_TEST == ENABLE) */

#if (PRO_COPY_FAX_MODE == ENABLE)	/* by K.Watanabe 1999/01/20 */
/*************************************************************************
	module		:[優先待機状態に切り替えるかどうか調べます]
	function	:[
		1.
	]
	return		:[
		TRUE	:切り替える
		FALSE	:切り替えない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1997/03/11]
	author		:[曽根岡・渡辺一章]
*************************************************************************/
UBYTE MAN_AutoReadyModeChangeEnable(void)
{
	UBYTE	i;

	/* コピーモードからファクスモードに自動切替できるかをチェック */
	if ((CHK_ReadyModeCopy()) && (CHK_UNI_PrimaryReadyMode() == (UBYTE)PRIMARY_FAX_READY)) {
		for (i = 0; i < SYS_MULTI_COPY_MAX; i ++) {
			if (SYB_MultiCopyFile[i].Status != SYS_MCOPY_EMPTY) {	/* コピー（カセット）がある時 */
				return(FALSE);
			}
		}

		if (SYB_ManualCopyFile.Status != SYS_MCOPY_EMPTY) {			/* 手差しコピーがある時 */
			return(FALSE);
		}

		if (IsSettingDensity) {										/* 濃度設定中の時 */
			return(FALSE);
		}

		return(TRUE);
	}
	/* ファクスモードからコピーモードに自動切替できるかをチェック */
	else if ((!CHK_ReadyModeCopy()) && (CHK_UNI_PrimaryReadyMode() == (UBYTE)PRIMARY_COPY_READY)) {
		for (i = 0; i < SYS_COM_FILE_MAX; i++)  {
			if (SYB_CommandFile[i].Status != SYS_CMD_EMPTY) {		/* 通信予約がある時 */
				return(FALSE);
			}
		}

		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_OPERATE) {	/* オペレーション中の時 */
			return(FALSE);
		}

		if (IsSettingDensity) {										/* 濃度設定中の時 */
			return(FALSE);
		}

		if (CheckExceptCopyDocStore()) {							/* コピー以外の原稿蓄積中の時 */
			return(FALSE);
		}

		if (CHK_CopyProtectON()) {									/* コピー禁止中の時 */
			return(FALSE);
		}

		if (SYB_ScannerTransportMode == TRUE) {						/* ミラーキャリッジ輸送モードの時 */
			return(FALSE);
		}

		return(TRUE);
	}

	return(FALSE);
}

/*************************************************************************
	module		:[待機モード自動切り替え]
	function	:[
		1.待機モードを現在の状態から、他方に切り替えます
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[1999/01/22]
	author		:[渡辺一章]
*************************************************************************/
void MAN_AutoChangeReadyMode(void)
{
	if (CHK_ReadyModeCopy()) {	/* コピーモードの時 */
		/* モードをファクスモードにする */
		SYB_SettingStatus[SETTING_STATUS_26] &= ~READY_MODE_COPY;

		/* コピーパラメーター優先表示を止めます */
		StopParamDispTask();
	}
	else {						/* ファクスモードの時 */
		/* モードをコピーモードにする */
		SYB_SettingStatus[SETTING_STATUS_26] |= READY_MODE_COPY;
	}
}
#endif	/* (PRO_COPY_FAX_MODE == ENABLE) */


#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
/*************************************************************************
	module		:[パワーオフモードの判断／実行モジュール]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2001/02/01]
	author		:[橘正樹]
*************************************************************************/
void MAN_ExecEcoMode(void)
{
	UBYTE is_key_input;

	/* 割り込み禁止区間開始 */
	CMN_DisableInterrupt();

	is_key_input = SYS_EcoResetKeyInput;
	SYS_EcoResetKeyInput = 0;

	/*
	** オートパワーオフモードセット中の場合は何もせずリターン
	*/
	if (SYS_EcoModeStatus == ECO_MODE_SETTING) {
		/* 割り込み禁止解除 */
		CMN_EnableInterrupt();
		return;
	}
	/*
	** 現在のオートパワーオフモードを待避します
	*/
	SYS_OldEcoModeStatus = SYS_EcoModeStatus;

	/*
	** オートパワーオフスイッチ状態をチェックし、可能なモードをセットします
	*/
	if (SYS_AutoPowerSW) {
		SYS_NewEcoModeStatus = ECO_MODE_OFF;		/* 通常状態にセット */
		if (CMN_CheckAvailableEcoMode() && (is_key_input == 0)) {
			/* MAN_TimerTaskでSYS_EcoModeTimerを減算 */
		}
		else {
			SYS_EcoModeTimer = (UWORD)CHK_UNI_EcoModeStartTime() * 60;
		}
	}
	else {
		if (CMN_CheckAvailableEcoMode() && (is_key_input == 0)) {
			SYS_NewEcoModeStatus = ECO_MODE_ON;		/* 省エネ状態にセット */
		}
		else {
			SYS_NewEcoModeStatus = ECO_MODE_OFF;	/* 通常状態にセット */
			SYS_AutoPowerSW = TRUE;
			SYS_EcoModeTimer = (UWORD)CHK_UNI_EcoModeStartTime() * 60;
		}
	}

	/*
	** オートパワーオフモードの状態が変化があったときに下記処理を行ないます
	*/
	if (SYS_OldEcoModeStatus != SYS_NewEcoModeStatus) {
		/*
		** オートパワーオフモードを処理中にする
		*/
		SYS_EcoModeStatus = ECO_MODE_SETTING;

		/* 割り込み禁止解除 */
		CMN_EnableInterrupt();

		switch (SYS_NewEcoModeStatus) {
		case ECO_MODE_OFF:	/* 通常状態 */
			/*
			** システム起動タスクの起動
			*/
			if (tskno_MAN_WakeUpSystemTask == 0xffff) {
				cre_tsk(&tskno_MAN_WakeUpSystemTask, TSK_MAN_WAKEUPSYSTEMTASK, 0);
			} else {
				SYS_EcoModeStatus = SYS_OldEcoModeStatus;
			}
			break;

		case ECO_MODE_ON:	/* 省エネ状態 */
			/*
			** システム停止タスクの起動
			*/
			if (tskno_MAN_SleepSystemTask == 0xffff) {
				cre_tsk(&tskno_MAN_SleepSystemTask, TSK_MAN_SLEEPSYSTEMTASK, 0);
			} else {
				SYS_EcoModeStatus = SYS_OldEcoModeStatus;
			}
			break;

		default:
			/* ここにはこないはず */
			SYS_EcoModeStatus = SYS_OldEcoModeStatus;
			break;
		}
	}
	else {
		/* 割り込み禁止解除 */
		CMN_EnableInterrupt();

		/*
		** オートパワーオフモード処理をしない場合、待避していたオートパワーオフモードを元に戻します
		*/
		SYS_EcoModeStatus = SYS_OldEcoModeStatus;

	}
}

/*************************************************************************
	module		:[システム起動タスク（通常状態への設定）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2001/02/01]
	author		:[橘正樹]
*************************************************************************/
void MAN_WakeUpSystemTask(void)
{
	INI_WakeUpSystem();

#if(0)
	/* 省エネ時検出不可センサーの検出許可 */
//	SYS_SensorDetectInhibit = 0;
#endif

	/* センサーがセットされるまでウェイト */
	wai_tsk(100);

	/* 割り込み禁止区間開始 */
	CMN_DisableInterrupt();
	/* オートパワーオフモードの確定 */
	SYS_EcoModeStatus = SYS_NewEcoModeStatus;
	tskno_MAN_WakeUpSystemTask = 0xffff;
	/* 割り込み禁止解除 */
	CMN_EnableInterrupt();

	exi_tsk();
}

/*************************************************************************
	module		:[システム停止タスク（パワーオフ状態への設定）]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2001/02/01]
	author		:[橘正樹]
*************************************************************************/
void MAN_SleepSystemTask(void)
{
#if(0)
	/* 省エネ時検出不可センサーの検出禁止 */
//	SYS_SensorDetectInhibit = 1;
#endif

	INI_SleepSystem();


	/* 割り込み禁止区間開始 */
	CMN_DisableInterrupt();
	/* オートパワーオフモードの確定 */
	SYS_EcoModeStatus = SYS_NewEcoModeStatus;
	tskno_MAN_SleepSystemTask = 0xffff;
	/* 割り込み禁止解除 */
	CMN_EnableInterrupt();

	exi_tsk();
}

/*************************************************************************
	module		:[システム起動モジュール（通常状態への設定）]
	function	:[
		１．通信、プリントの起動において、ＭＡＩＮ電源が必要なときにコールする
		２．現在のオートパワーオフモードをチェックする
		３．オートパワーオフモードがオートパワーオフ状態の場合のみ、システム起動タスクを起動する
		４．システム起動完了まで待ちあわせをする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2001/02/01]
	author		:[橘正樹]
*************************************************************************/
void MAN_ExecEcoWakeUp(void)
{
	UDWORD	loop_cnt;

	/*
	** オートパワーオフモードが処理中の場合、モードが確定するまで待ちます
	*/
	loop_cnt = 20000/10;	/* 万一、オートパワーモード処理中のままになった場合ループするので、このルーチンを抜けるパスを作る */
	while (loop_cnt) {
		/************************/
		/* 割り込み禁止区間開始 */
		/************************/
		CMN_DisableInterrupt();
		if (SYS_EcoModeStatus == ECO_MODE_SETTING) {
			/********************/
			/* 割り込み禁止解除 */
			/********************/
			CMN_EnableInterrupt();
			loop_cnt--;
			wai_tsk(1);
		} else {
			break;
		}
		if (!loop_cnt) {
			return;
		}
	}

	if (SYS_EcoModeStatus == ECO_MODE_ON) {
		/*
		** システム起動タスクの起動
		*/
		SYS_OldEcoModeStatus = SYS_EcoModeStatus;	/* 現在のオートパワーオフモードを待避します */
		SYS_EcoModeStatus = ECO_MODE_SETTING;		/* オートパワーモード処理中に設定する */

		SYS_NewEcoModeStatus = ECO_MODE_OFF;		/* 通常状態にセット */
		SYS_AutoPowerSW = TRUE;

		/********************/
		/* 割り込み禁止解除 */
		/********************/
		CMN_EnableInterrupt();
		if (tskno_MAN_WakeUpSystemTask == 0xffff) {
			cre_tsk(&tskno_MAN_WakeUpSystemTask, TSK_MAN_WAKEUPSYSTEMTASK, 0);
		}
	}
	/********************/
	/* 割り込み禁止解除 */
	/********************/
	CMN_EnableInterrupt();

	/*
	** システムが起動完了するまでウェイトします]
	*/
	loop_cnt = 20000/10;	/* 万一、オートパワーオフモード処理中のままになった場合ループするので、このルーチンを抜けるパスを作る */
	while (loop_cnt) {
		if ((SYS_EcoModeStatus == ECO_MODE_ON)	/* オートパワーオフモードがオートパワーモード状態かオートパワーモード処理中状態のとき */
		||	(SYS_EcoModeStatus == ECO_MODE_SETTING)) {
			wai_tsk(1);
			loop_cnt--;
		} else {
			break;
		}
		if (!loop_cnt) {
			return;
		}
	}
}
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
/*************************************************************************
	module		:[パワーオフモードの判断／実行モジュール]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MAN]
	date		:[2002/09/09]
	author		:[前田雅也]
*************************************************************************/
void MAN_ChangeEcoMode(UBYTE eco_on)
{
#if (1) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
	if ((SYS_EcoModeStatus == ECO_MODE_OFF) && (eco_on == 1)) {
		if (CMN_ShiftEcoModeEnable()) {
			EcoModeOn();
			SYS_EcoModeStatus = ECO_MODE_ON;
		}
	}
	else if ((SYS_EcoModeStatus == ECO_MODE_ON) && (eco_on == 0)) {
		EcoModeOff(eco_on);
		SYS_EcoModeStatus = ECO_MODE_OFF;
	}
	if ((eco_on == 2) || (eco_on == 3)) {
		EcoModeOff(eco_on);
		SYS_EcoModeStatus = ECO_MODE_OFF;
	}
#else
//	if ((SYS_EcoModeStatus == ECO_MODE_OFF) && (eco_on == TRUE)) {
//		if (CMN_ShiftEcoModeEnable()) {
//			EcoModeOn();
//			SYS_EcoModeStatus = ECO_MODE_ON;
//		}
//	}
//	else if ((SYS_EcoModeStatus == ECO_MODE_ON) && (eco_on == FALSE)) {
//		EcoModeOff();
//		SYS_EcoModeStatus = ECO_MODE_OFF;
//	}
#endif
}
#endif
