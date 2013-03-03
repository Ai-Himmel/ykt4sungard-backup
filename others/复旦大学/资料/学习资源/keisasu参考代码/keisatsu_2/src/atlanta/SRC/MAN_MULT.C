/*---------------------------------------------------------------------------*/
/*  プロジェクト : Jun/KOBE                                                  */
/*  ファイル名   : MAN_MULT.C                                                */
/*  モジュール   :                                                           */
/*               :                                                           */
/*  作成者       : 村田                                                      */
/*  日  付       : 1996/11/07  -> 1997/06/10kobeより移植                     */
/*  概  要       : ２回線仕様関連モジュール                                  */
/*               :                                                           */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/

/*------------------------*/
/* インクルードファイル達 */
/*------------------------*/
#include  "\src\atlanta\define\product.h"

#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\sysmax.h"
#include  "\src\atlanta\define\sys_stat.h"
#include  "\src\atlanta\define\sys_line.h"
#include  "\src\atlanta\define\sysmjnl.h"
#include  "\src\atlanta\define\sys_opt.h"
#include  "\src\atlanta\define\fcm_def.h"
#include  "\src\atlanta\define\syscomf.h"
#include  "\src\atlanta\define\sysbatch.h"
#include  "\src\atlanta\define\mem_def.h"

#include  "\src\atlanta\ext_v\sys_data.h"
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\man_data.h"
#include  "\src\atlanta\ext_v\pro_tbl.h"
#include  "\src\atlanta\ext_v\mlt_data.h"
#include  "\src\atlanta\ext_v\fcm_data.h"
#include  "\src\atlanta\ext_v\mem_data.h"

#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"

/* 簡易料金管理リスト By S.Fukui Dec.4,1997 */
#if (PRO_PANEL == ANK)
#include  "\src\atlanta\opr\ank\ext_v\opr_data.h"
#endif
#if (PRO_PANEL == KANJI)
#include  "\src\atlanta\opr\kanji\ext_v\opr_data.h"
#endif


#include  "\src\atlanta\define\mem_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#if (PRO_DPRAM == ENABLE)
#include  "\src\atlanta\define\dpr_pro.h"
#endif
#include  "\src\atlanta\define\man_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\memsw\define\mems_pro.h"
#include  "\src\atlanta\define\fcm_pro.h"
#include  "\src\atlanta\define\mlt_pro.h"
#include  "\src\atlanta\define\ncu_def.h"
#include  "\src\atlanta\define\unisw_a.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\cmn_pro.h"		/* S.Fukui June 19,1998 */

#if (PRO_CIPHER == ENABLE)
#include	"\src\atlanta\scd\ext_v\cph_data.h"	/* 98/06/10 By T.Fukumoto */
#endif

#include	"\src\atlanta\sh7043\define\io_pro.h"	/* PRO_EX_CLASS1 対応 S.Fukui June 16,1998  */
/* void	MonitorSpeakerOn(void);  */
/* void	MonitorSpeakerOff(void); */
UBYTE	*CMN_StringCopyNumOrNULL(UBYTE  *dst_ptr,CONST UBYTE  *src_ptr,register WORD  str_cnt);
void 	CMN_ClearCommandArea(UBYTE  com_type,UBYTE  com_no);
#if (0)	/* cmn_pro.hで宣言 S.Fukui June 19,1998 */
void 	outp(UDWORD, UBYTE);
#endif
UBYTE 	CHK_DepartmentON(void);

extern UWORD	tskno_NCU_TelephoneOperation;
extern UWORD	tskno_NCU_Task;
extern UWORD	tskno_SCN_GearBackLashTask;
extern UBYTE 	HungUpCheck;

#if (PRO_MULTI_LINE == ENABLE)
	#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
	#endif
	#if (PRO_MODEM == R288F)
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
	#endif
	#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
	#endif
#endif
/* 移植 by SMuratec L.Z.W 2003/07/24 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* 中国郵政局特ROM By O.Kimoto 2001/01/22 */
																		/* Add by Y.Kano 2003/07/11 */
#include	"\src\atlanta\ext_v\ini_tbl.h"
#endif

/*************************************************************************
	module		:[マルチ回線受信可能かどうかの判断]
	function	:[
		1.空きメモリおよび空きインデックがあるかチェックする
		2.代行受信管理テーブルの空きを見つける
		3.代行受信管理テーブルにスタックＮｏをセットに使用中にする
	]
	return		:[
					0xFFFF:   受信不可
					上記以外: 受信可能（獲得した代行受信管理テーブル番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/11/08]
	author		:[村田]
*************************************************************************/
UWORD MAN_CheckMultiLineReceiveEnable(UBYTE StackNo, UBYTE ReceiveMode)
{
	UWORD	ret;
	UWORD	i;

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
	/* フラッシュＲＯＭ書き換え中なら、着信しない */
	if (SYB_FlashROM_WriteStatus != NO_STATUS) {
		return(0xFFFF);
	}
#endif

#if (PRO_CIPHER == ENABLE)/* By Y.Suzuki 1997/12/10 */
	/* スクランブル処理中なら着信しない */
 #if (PRO_COM_CODEC_TYPE == SOFTWARE) /* By Y.Suzuki 1998/04/27 */
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/06/19 */
	if ((StackNo & 0x7f) == 0) {/* 1Line */
  #else
	if (StackNo == 0) {/* 1Line */
  #endif
		if (CHK_UNI_PriorityReceive()){/*By Y.Suzuki 1998/06/16*/
		/* スクランブル中の受信優先なし*/
			if (CMN_CheckScrambleBusy() == TRUE) {
				return(0xFFFF);
			}
		}
	}
	else {/* other Line */
	}
 #else

#if (0)
** 	/* ＰＯＰＬＡＲ＿ＨもＰＯＰＬＡＲ＿Ｂに合わせます。 By O.Kimoto 1998/05/06 */
** 	if (CMN_CheckScrambleBusy() == TRUE) {
** 		return(0xFFFF);
** 	}
#else
  #if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/06/19 */
	if ((StackNo & 0x7f) == 0) {/* 1Line */
  #else
	if (StackNo == 0) {/* 1Line */
  #endif
		if (CHK_UNI_PriorityReceive()){/*By Y.Suzuki 1998/06/16*/
		/* スクランブル中の受信優先なし*/
			if (CMN_CheckScrambleBusy() == TRUE) {
				return(0xFFFF);
			}
		}
	}
	else {/* other Line */
	}
#endif

 #endif
#endif

	/* オペレーションで送信専用になっている時は、着信を拒否します。
	** by O.Kimoto 1997/02/08
	*/
	if (ReceiveMode == AUTO_RECEIVE) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		if (StackNo == 0) {
			if (CHK_UNI_Line0_TxRx() == EXCLUSIVE_TX) {
				return(0xFFFF);
			}
#if (0) /* 1998/03/16 by T.Soneoka */
//			if (SYS_InternalLineNumber == SYS_STD_LINE_COM) {
//				if (CHK_UNI_Line0_TxRx() == EXCLUSIVE_TX) {
//					return(0xFFFF);
//				}
//			}
//			else {
//				if (CHK_UNI_Line_EXT_TxRx() == EXCLUSIVE_TX) {
//					return(0xFFFF);
//				}
//			}
#endif
		}
		/* 拡張回線は０ｘ８０としてみるように変更します by T.Soneoka 1998/03/16 */
		else if (StackNo == 0x80) {
			if (CHK_UNI_Line_EXT_TxRx() == EXCLUSIVE_TX) {
				return(0xFFFF);
			}
		}
		else {
			if (OPT_CHK_UNI_LineTxRx(StackNo) & EXCLUSIVE_TX) {
				return(0xFFFF);
			}
		}
#else
		if (OPT_CountModems() >1 ) {
			if (OPT_CHK_UNI_LineTxRx(StackNo) & EXCLUSIVE_TX) {
				return(0xFFFF);
			}
		}
#endif
	}

#if (PRO_PRINT_TYPE == LASER)
	/* 1998/01/17 Y.Murata	F100R D65RL
	 * Ｆ１００ではＡＬ１００がついていても無視する
	*/
	if (CMN_CheckF100Model()) {		/* Ｆ１００なら */
		if (StackNo != 0) {	/* ホスト回線でない */
			return(0xFFFF);		/* 着信しません */
		}
	}
#endif

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */
	if ((CMN_CheckMemoryForMemRx())
	&& (MEM_CountTotalEmptyPage() > 0)) {	/** 空きメモリおよび空きインデックス有り */
#else
	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)
	&& (MEM_CountTotalEmptyPage() > 0)) {	/** 空きメモリおよび空きインデックス有り */
#endif

/* 拡張回線で受信があった場合、StackNoは0x80ではいってくる為、0x7fでマスクしてみるように変更します 
** また、引き数は0x80でわたってOKです 疑似２回線仕様 by T.Soneoka 1998/06/19 */
#if (PRO_LINENUMBER == TWICE_LINE)
		if ((StackNo & 0x7f) == 0) {/* 1Line */
#else
		if (StackNo == 0) {
#endif
			ret = MAN_GetMultiLineReceiveNumber(StackNo);
			return(ret);
		}
		else {
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) {	/* 内臓モデムがある */
				if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
					if (FinalRxMode == DIAGMODE) {
						return(0xFFFF);
					}
				}
				ret = MAN_GetMultiLineReceiveNumber(StackNo);
				return(ret);
			}
			else {
				for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
					if (CHK_OptionLineExist((UBYTE)i)) {
						break;
					}
				}
				if (StackNo == (UBYTE)i) {
					ret = MAN_GetMultiLineReceiveNumber(StackNo);
					return(ret);
				}
				else {
					if (CHK_OptionLineBusy((UBYTE)i)) {
						if (SYS_Opt[i].FinalRxMode == DIAGMODE) {
							return(0xFFFF);
						}
					}
					ret = MAN_GetMultiLineReceiveNumber(StackNo);
					return(ret);
				}
			}
		}
	}
	else {
		return(0xFFFF);
	}
}

/*************************************************************************
	module		:[マルチ回線代行受信管理テーブル獲得]
	function	:[
		1.代行受信管理テーブルの空きを見つける
		2.代行受信管理テーブルにスタックＮｏをセットに使用中にする
	]
	return		:[
					0xFFFF:   受信不可
					上記以外: 受信可能（獲得した代行受信管理テーブル番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/12/24]
	author		:[村田]
*************************************************************************/
UWORD MAN_GetMultiLineReceiveNumber(UBYTE StackNo)
{
	UWORD	i;

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
		if (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_EMPTY) {	/** 空きを見つける */
			SYB_MemoryRxPrint[i].StackNumber = StackNo;				/** スタックＮｏセット */
			SYB_MemoryRxPrint[i].JournalPoint = 0;					/** ジャーナルポイント初期化 */
			SYB_MemoryRxPrint[i].Status = SYS_MEMORY_RX_SETTING;	/** 空き代行受信管理テーブルをキープする */
			SYB_MemoryRxPrint[i].Cassette = SYS_AUTO_CASSETTE;		/** カセット選択を初期化 *//* By M.Tachibana 1998/01/30 */
			SYB_OptionMemoryRxWritePoint[StackNo] = i;
			return(i);
		}
	}
	return(0xFFFF);
}

/*************************************************************************
	module		:[受信原稿プリントするステータスをチェック]
	function	:[
		1.
	]
	return		:[
					1:ﾌﾟﾘﾝﾄできる
					0:ﾌﾟﾘﾝﾄなし

	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/11/08]
	author		:[村田]
*************************************************************************/
UBYTE MAN_CheckMemRxPrintStatus(UWORD No)
{
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
	if (CHK_UNI_MemoryRxAndPrint()) {
		if ((SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_STORE)
		||	(SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_PRINT)) {

			return(1);
		}
	}
	else {
		if (SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_PRINT) {
			return(1);
		}
	}
	return(0);
#else
	if ((SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_PRINT)
	||	(SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_FAST_PRINT)) {
		return(1);
	}
	if (CHK_UNI_MemoryRxAndPrint()) {
		if (CHK_UNI_RxDocReversePrint()) {
			if ((SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_STORE_PRINT) && (SYB_MemoryRxPrint[No].StorePage >= 1)) {
				return(1);
			}
		}
		else {
			if ((SYB_MemoryRxPrint[No].Status == SYS_MEMORY_RX_STORE) && (SYB_MemoryRxPrint[No].StorePage >= 1)) {
				return(1);
			}
		}
	}
	return(0);
#endif
}


/*************************************************************************
	module		:[受信原稿プリントＮｏ獲得]
	function	:[
		1.代行受信テーブルの０番目から検索
		2.１枚以上受信しているテーブルを見つける
		3.一番古い時間に受信しているテーブルＮｏを獲得する
	]
	return		:[
					0xFFFF:               代行受信原稿なし
					0～SYS_MEMORY_RX_MAX: 代行受信原稿プリントする番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/11/08]
	author		:[村田]
*************************************************************************/
UWORD MAN_GetMemoryRxPrintNumber(void)
{
	UWORD			i;
	UWORD			number;
	unsigned long	receive_time;

	i = 0;
	number = 0xFFFF;
	receive_time = 0xFFFFFFFF;

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
		if (MAN_CheckMemRxPrintStatus(i)) {	/* 受信している */

			if (receive_time == 0xFFFFFFFF) {	/** １発目 */
				receive_time = SYB_MemoryRxPrint[i].ReceiveTime;
				number = i;
			}
			else {
				/** 受信時間が同じ時は、ナンバーの若いのを優先する */
				if (receive_time > SYB_MemoryRxPrint[i].ReceiveTime) {
					receive_time = SYB_MemoryRxPrint[i].ReceiveTime;
					number = i;
				}
			}
		}
	}
	return(number);
}


/*************************************************************************
	module		:[オプションの通信タスクからのメッセージをチェックする]
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
	date		:[1996/11/09]
	author		:[村田]
*************************************************************************/
void MAN_CheckFaxComOption(void)
{
#if (PRO_MULTI_LINE == ENABLE)
	MESSAGE_t	send_message;
	MESSAGE_t	*receive_message;
	UBYTE	i;

	for (i = 0; i < SYS_OPTION_MESSAGE_MAX; i ++) {
		if (SYS_OptionMessage[OptMessageRead].Status == 1) {
			send_message.Item = FROM_FAXCOM_OPTION;
			send_message.Message = SYS_OptionMessage[OptMessageRead].Message;
			send_message.SubMessage1 = SYS_OptionMessage[OptMessageRead].SubMessage1;
			send_message.SubMessage2 = SYS_OptionMessage[OptMessageRead].SubMessage2;
			send_message.SubMessage3 = SYS_OptionMessage[OptMessageRead].SubMessage3;
			send_message.SubMessage4 = SYS_OptionMessage[OptMessageRead].SubMessage4;
			SYS_OptionMessage[OptMessageRead].Status = 0;
			snd_msg(mbxno.MAN_Task, &send_message);
			rcv_msg(mbxno.FCM_Option, &receive_message);
			OptMessageRead++;
			if (OptMessageRead >= SYS_OPTION_MESSAGE_MAX) {
				OptMessageRead = 0;
			}
		}
	}
	/* オプション表示更新のためメインを走らす */
	if (SYS_OptionFaxComUpDataDisplay) {
		SYS_OptionFaxComUpDataDisplay = 0;
		send_message.Item = FROM_FAXCOM_OPTION;
		send_message.Message = MSG_OPT_FAXCOM_DISPLAY;
		snd_msg(mbxno.MAN_Task, &send_message);
		rcv_msg(mbxno.FCM_Option, &receive_message);
	}
#endif
}


/*************************************************************************
	module		:[マルチ回線ジャーナルセット]
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
	date		:[1996/12/02]
	author		:[村田]
*************************************************************************/
void far	MAN_SetJournalMultiLine(void)
{
	UWORD	i;
	UWORD	line_number;

	/* ジャーナル展開中かののチェック */
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		if (SYS_JournalRequest[i] == SYS_JOURNAL_REQ_WORKING) {
			break;
		}
	}
	if (i < SYS_OPTION_BOARD_MAX) {
		return;		/* ジャーナル展開中 */
	}
	/* ジャーナル展開要求があるかのチェック */
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		if (SYS_JournalRequest[i] == SYS_JOURNAL_REQ) {
			break;
		}
	}
	if (i >= SYS_OPTION_BOARD_MAX) {
		return;		/* 要求なし */
	}

	/*--------------------------*/
	/* ジャーナルセット処理開始 */
	/*--------------------------*/
	line_number = i;	/* ジャーナル展開する回線番号 */
	SYS_JournalRequest[line_number] = SYS_JOURNAL_REQ_WORKING;	/* セット中 */

#if (PRO_PAT_JOURNAL == ENABLE)
	/* ジャーナルイメージデータ獲得 */
	if (line_number != 0) {
		/* オプションのジャーナルイメージデータ獲得 */
		DPR_GetPAT_JournalImageData(line_number - 1);
	}

	/* ジャーナルイメージデータをＭＨに圧縮 */
	PAT_SetJournal2((UBYTE)line_number);
#endif

	/*CMN_DisableInterrupt(); 1998/01/26 Y.Murata */
	/* キャラクタージャーナルセット */
	MAN_SetJournal((UBYTE)line_number);
	/*CMN_EnableInterrupt(); 1998/01/26 Y.Murata */

	/* Ｔ３０モニタセット */
	CHK_SetT30Sign((UBYTE)line_number);
	SYS_JournalRequest[line_number] = SYS_JOURNAL_REQ_NOTHING;	/* セット完了 */
}


/*************************************************************************
	module		:[工場ファンクション（回線テスト）項目コマンド発行]
	function	:[
		1.オプションモデムボードに対してコマンドを発行します。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1996/12/10]
	author		:[村田]
*************************************************************************/
void MAN_OptFactoryFunctionCommand(struct SYS_FactoryOptModemData_t *com_data)
{
#if (PRO_MULTI_LINE == ENABLE)
	struct SYS_FactoryOptModemData_t function_data;
	UWORD	number;

	function_data.Item = com_data->Item;
	function_data.Kind = com_data->Kind;
	function_data.BaudRate = com_data->BaudRate;
	function_data.DataRate = com_data->DataRate;
	function_data.PIX_Pattern = com_data->PIX_Pattern;
	function_data.StackNumber = com_data->StackNumber;
	number = com_data->StackNumber;

	SYS_OptFactoryFunctionResponse = 0;
	DPR_SendFactoryFunctionData(&function_data, number);	/* ｺﾏﾝﾄﾞ発行 */
	MAN_OptFactoryFunctionPeriod(&function_data);	/* 受け付けｺﾏﾝﾄﾞ待ち */
#endif
}


void MAN_OptFactoryFunctionPeriod(struct SYS_FactoryOptModemData_t *com_data)
{
#if (PRO_MULTI_LINE == ENABLE)
	if ((com_data->Item == OPT_MDM_FACTORY_TEST_START) ||
		(com_data->Item == OPT_MDM_FACTORY_TEST_END)) {

		return;
	}

	while (SYS_OptFactoryFunctionResponse == 0) {
		wai_tsk(1);
	}
	SYS_OptFactoryFunctionResponse = 0;
	return;
#endif
}




/*************************************************************************
	module		:[指定した回線の実行キューを消去します]
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
	date		:[1996/12/17]
	author		:[村田]
*************************************************************************/
void MltDeleteComFileExecQueueFile(UBYTE stack_number)
{
	UBYTE	i;
	UWORD	l;
	UBYTE	ErasedCommandNumber;
	UBYTE	SameCommandNumberExist;
	UBYTE	BatchOrCommand;

	ErasedCommandNumber = 0xFF;
	SameCommandNumberExist = 0;

	/* ｽﾃｰﾀｽが消去になっていて かつ 指定した回線番号のｷｭｰを消去します */
	for (l = 0; l < SYS_EXEC_QUEUE_MAX; l++ ) {
		if ((SYB_ExecQueue[l].Status == SYS_EXEC_ERASED) && (SYB_ExecQueue[l].StackNumber == stack_number)) {
			SYB_ExecQueue[l].Status = SYS_EXEC_EMPTY;

			/* 消去したｷｭｰのｺﾏﾝﾄﾞﾌｧｲｱﾙ番号をｾｰﾌﾞ */
			ErasedCommandNumber = SYB_ExecQueue[l].Number.Command;

			if (SYB_ExecQueue[l].Kind == SYS_BATCH_TX) { /** 一括送信ファイル */
				BatchOrCommand = SYS_BATCH_TX;
			}
			else {
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング処理追加　1997/03/06　Matsukuma */
				if (SYB_ExecQueue[l].Kind == SYS_CONTINUOUS_POLLING) {
					BatchOrCommand = SYS_CONTINUOUS_POLLING;
				}
				else {
					BatchOrCommand = SYS_COMMAND_TRX;
				}
#else
				BatchOrCommand = SYS_COMMAND_TRX;
#endif
			}

			if (BatchOrCommand == SYS_COMMAND_TRX) {
				if (CheckScannerCommand(SYB_ExecQueue[l].Number.Command)) {
					SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);  /* スキャナー使用中をクリア */
				}
			}
		}
	}

	/* 上でｾｰﾌﾞしたｺﾏﾝﾄﾞﾌｧｲｱﾙが他にｷｭｰを展開しているか検索します */
	for (l = 0; l < SYS_EXEC_QUEUE_MAX; l++ ) {
		switch (SYB_ExecQueue[l].Status) {
		case SYS_EXEC_OK:
			/* 送信証をプリント要求がある場合はコマンド消去は行なわない 1997/09/11  By T.Yamaguchi */
			if (((SYB_CommandFile[SYB_ExecQueue[l].Number.Command].Option.ConfirmationReport & SYS_RCR_REQUESTED) != SYS_TCR_REQUESTED)
			 && ((SYB_CommandFile[SYB_ExecQueue[l].Number.Command].Option.ConfirmationReport & SYS_TCR_AND_RCR) != SYS_TCR_AND_RCR)){ /** モニターレポートＯＦＦ **/
			 	break;
			}
		case SYS_EXEC_WAITING:
		case SYS_EXEC_EXECUTE:
		case SYS_EXEC_FORWARD_WAITING:
		case SYS_EXEC_FORWARD_EXECUTE:
		case SYS_EXEC_ERROR:
		case SYS_EXEC_ERASED:		/* 1997/02/08 Y.Murata */
			if (SYB_ExecQueue[l].Number.Command == ErasedCommandNumber) {
				SameCommandNumberExist = 1;
				if (BatchOrCommand == SYS_COMMAND_TRX) {
					if (CheckScannerCommand(SYB_ExecQueue[l].Number.Command)) { /* 7/30/1994 */
						SYS_MachineStatus[SYS_RESOURCE_STATUS] &= ~(SYS_SCANNER_BUSY);  /* スキャナー使用中をクリア */
					}
				}
				break;
			}
			break;
		default:
			break;
		}
	}

	/* 1997/02/08 Y.Murata
	 * キューが全てERASEDでも、コマンドファルは消しません。
	 * コマンドがERASEDで、それにぶらさがっているキューにERASEDが無い時コマンドを消します。
	*/
	if ((!SameCommandNumberExist) && (ErasedCommandNumber != 0xFF)) {
		if (BatchOrCommand == SYS_COMMAND_TRX) {
			SYB_CommandFile[ErasedCommandNumber].Status = SYS_CMD_ERASED;
#if (PRO_COMMANDFILE_SRAM == DISABLE)	/* M.Tachibana 1997/07/07 */
			SYB_CommandStatus[ErasedCommandNumber] = SYS_CMD_ERASED;
#endif
		}
		else {
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング処理追加　1997/03/06　Matsukuma */
				if (SYB_ExecQueue[l].Kind == SYS_CONTINUOUS_POLLING) {
					SYB_ContinuousPolling.Status = SYS_CMD_ERASED;
				}
				else {
					SYB_BatchTxFile[ErasedCommandNumber].Status = SYS_CMD_ERASED;
				}
#else
			SYB_BatchTxFile[ErasedCommandNumber].Status = SYS_CMD_ERASED;
#endif
		}
	}
	for (i = 0; i < SYS_COM_FILE_MAX; i++ ) {
		if ((SYB_CommandFile[i].Status == SYS_CMD_ERASED) ||
			(SYB_CommandFile[i].Status == SYS_CMD_POWER_OFF)) {

			for (l = 0; l < SYS_EXEC_QUEUE_MAX; l++ ) {
				if (SYB_ExecQueue[l].Number.Command == (UBYTE)i) {
					if (SYB_ExecQueue[l].Status == SYS_EXEC_ERASED) {
						break;
					}
				}
			}
			if (l >= SYS_EXEC_QUEUE_MAX) {
				CMN_ClearCommandArea(SYS_COMMAND_TRX, i);
			}
		}
	}
	for (i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
		if ((SYB_BatchTxFile[i].Status == SYS_CMD_ERASED) ||
			(SYB_BatchTxFile[i].Status == SYS_CMD_POWER_OFF)) {

			for (l = 0; l < SYS_EXEC_QUEUE_MAX; l++ ) {
				if (SYB_ExecQueue[l].Number.Batch == (UBYTE)i) {
					if (SYB_ExecQueue[l].Status == SYS_EXEC_ERASED) {
						break;
					}
				}
			}
			if (l >= SYS_EXEC_QUEUE_MAX) {
				CMN_ClearCommandArea(SYS_BATCH_TX, i);
			}
		}
	}
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング処理追加　1997/03/06　Matsukuma */
	if ((SYB_ContinuousPolling.Status == SYS_CMD_ERASED) ||
		(SYB_ContinuousPolling.Status == SYS_CMD_POWER_OFF)) {
		DeleteContinuousPollingCommand();
	}
#endif
}


/*************************************************************************
	module		:[通信停止]
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
	date		:[1996/12/17]
	author		:[村田]
*************************************************************************/
void MAN_MltFaxComStop(void)
{
	UWORD	i;
	UWORD	j;
	UBYTE	is_faxcom_stop;

	is_faxcom_stop = 0;
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++ ) {				/* キュー検索 */
		if (SYB_ExecQueue[i].Status == SYS_EXEC_ERASED) {	/* ERASEのキューがあった */
			if (SYB_ExecQueue[i].StackNumber == 0x00) {		/* そのキューはホストである */
				if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) && (SYS_FaxComType == SYS_COMMAND_EXECUTE)) {
					CommandErased[0] = 1;
					if (SYS_ExecutingExecNo[0] == i) {	/* add if() COMMAND_DEL */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/22 Y.Murata for KAKI */
						if (CheckQucikTxScan(i)) {
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_DOC_STORE;
						}
						else {
							SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;
						}
#else
						SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_FAXCOM;
#endif
					}
					is_faxcom_stop = 1;
				}
				else {
					/* リダイアルで再発呼待ちの時 */
					MltDeleteComFileExecQueueFile((UBYTE)0x00);
					is_faxcom_stop = 1;
				}
			}
			else if (SYB_ExecQueue[i].StackNumber == 0xFF) {
				MltDeleteComFileExecQueueFile((UBYTE)0xFF);
				is_faxcom_stop = 1;
			}
			else {
				for (j = 0; j < SYS_OPTION_BOARD_MAX; j++) {
					if (SYB_ExecQueue[i].StackNumber == (UBYTE)j) {
						if ((SYS_OptionLineStatus[j] & SYS_OPTION_LINE_BUSY) && (SYS_Opt[j].SYS_FaxComType == SYS_COMMAND_EXECUTE)) {
							if (SYS_ExecutingExecNo[j] == i) {	/* add if() COMMAND_DEL */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/22 Y.Murata for KAKI */
								if (CheckQucikTxScan(j)) {
									SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] |= SYS_STOP_DOC_STORE;
								}
								else {
									SYS_OptionLineStop((UBYTE)j);
								}
#else
								SYS_OptionLineStop((UBYTE)j);
#endif
							}
							CommandErased[j] = 1;
							is_faxcom_stop = 1;
						}
						else {
							/* リダイアルで再発呼待ちの時 */
							SYS_OptionLineStop((UBYTE)j);
							MltDeleteComFileExecQueueFile((UBYTE)j);
							is_faxcom_stop = 1;
						}
					}
				}
			}
		}
	}
	if (is_faxcom_stop == 0) {
		/* キューに展開されていない時 */
		MltDeleteComFileExecQueueFile((UBYTE)0xFF);
	}
}


/*--------------------------------*/
/* キャラクタジャーナルセット関連 */
/*--------------------------------*/
/* JOURANL_JOURANL */
/*************************************************************************
	module		:[ジャーナル・データの相手先名をセットする]
	function	:[]
	commom		:[
		NonStandardID[]		: 非標準ＩＤ
		StandardID[]		: 標準ＩＤ
	]
	condition	:[]
	comment		:[DEU仕様のRemoteID_TTIの優先順位  < by M.H. >
					1. Standard ID
					2. NonStandard ID
					3. Dialした番号
					]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[MAN]
	date		:[1996/12/19]
	author		:[村田]
*************************************************************************/
void MAN_SetRemoteID_ToJournal(UBYTE stack_number)
{
#if defined (KEISATSU) /* 警察FAX Added by SMuratec 李 2005/09/15 */
	Journal->KeisatsuID[0] = 0x00;	/* NULL */
#endif /* defined (KEISATSU) */
#if defined(DEU)	/* 97/11/13 by M.H. */
	if (SYS_Opt[stack_number].StandardID[0] != 0x00) {	/** 交信相手機の標準ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].StandardID[0], 20);	/** 相手先名セット */
	}
	else if (SYS_Opt[stack_number].NonStandardID[0] != 0x00) {		/** 交信相手機の村田（／ＯＥＭ）ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].NonStandardID[0], 20);	/** 相手先名セット */
	}
#else
 #if defined(EUR)
	if (CHK_ForeignApprovalDEU()) {
		if (SYS_Opt[stack_number].StandardID[0] != 0x00) {	/** 交信相手機の標準ＩＤに何か登録されている */
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].StandardID[0], 20);	/** 相手先名セット */
		}
		else if (SYS_Opt[stack_number].NonStandardID[0] != 0x00) {		/** 交信相手機の村田（／ＯＥＭ）ＩＤに何か登録されている */
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].NonStandardID[0], 20);	/** 相手先名セット */
		}
	}
	else {
		if (SYS_Opt[stack_number].NonStandardID[0] != 0x00) {		/** 交信相手機の村田（／ＯＥＭ）ＩＤに何か登録されている */
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].NonStandardID[0], 20);	/** 相手先名セット */
		}
		else if (SYS_Opt[stack_number].StandardID[0] != 0x00) {	/** 交信相手機の標準ＩＤに何か登録されている */
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].StandardID[0], 20);	/** 相手先名セット */
		}
	}
 #else
	if (SYS_Opt[stack_number].NonStandardID[0] != 0x00) {		/** 交信相手機の村田（／ＯＥＭ）ＩＤに何か登録されている */
		CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].NonStandardID[0], 20);	/** 相手先名セット */
	}
	else if (SYS_Opt[stack_number].StandardID[0] != 0x00) {	/** 交信相手機の標準ＩＤに何か登録されている */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
 #if 0 /* 仕様変更 Modify by SMuratec 李 2005/10/10 */
**		if (SYS_InternalLineNumberSave == SYS_STD_LINE_COM) {
**			CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[0], "ｶ", 1);
**		}
**		else {
**			CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[0], "ｹ", 1);
**		}
**		switch (SYS_FaxComType){
**			case SYS_ISSEI_TX: /* 一斉指令送信 */
**			case SYS_ISSEI_RX: /* 一斉指令受信 */
**			case SYS_ISSEI_KIDO_TX: /* 指令起動信号による一斉指令送信 */
**			case SYS_ISSEI_KIDO_RX: /* 指令起動信号による一斉指令受信 */
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[1], "ｲ", 1);
**				break;
**			default:
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[1], "ｺ", 1);
**				break;
**		}
**		if (FCM_S1_Scramble){
**			CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[2], "S", 1);
**		}
**		else {
**			CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[2], "N", 1);
**		}
**		if (FCM_S1_Senyo){
**			CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[3], "ｾ", 1);
**		}
**		else {
**			CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[3], "ｷ", 1);
**		}
**		Journal->KeisatsuID[4] = 0x00;	/* NULL */
 #endif
#endif /* defined (KEISATSU) */
		CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, (UBYTE *)&SYS_Opt[stack_number].StandardID[0], 20);	/** 相手先名セット */
	}
 #endif
#endif
}

/*************************************************************************
	module		:[ジャーナル・データの相手先名をセットする（発呼）]
	function	:[]
	commom		:[
		SYB_SpeedDial[]			: 短縮ダイアル
		SYB_OnetouchDial[]		: ワンタッチダイアル
	]
	condition	:[]
	comment		:[DEU仕様は、ｼﾞｬｰﾅﾙの相手先名の欄にﾜﾝﾀｯﾁ/短縮の相手先名を印字してはいけない。 < by M.H.>
				  以下の場合、ｼﾞｬｰﾅﾙのﾛｹｰｼｮﾝは空欄とする。
					1. 手動送信、ﾎﾟｰﾘﾝｸﾞ送信で相手機よりIDを受信しない場合。
					2. 自動受信、手動受信で相手機よりIDを受信しない場合。
					]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[MAN]
	date		:[1996/12/19]
	author		:[村田]
	変更履歴	:1.	DEU仕様で回線No.が必要なため共通仕様として引数を追加｡ 97/11/14 by M.H.
*************************************************************************/
void MAN_SetCOMEXEC_ModeToJournal(UWORD que_num, UBYTE stack_number)
{
	UBYTE is_set;
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
	UBYTE is_dail_set;
	
	is_dail_set = FALSE;
#endif /* defined (KEISATSU) */
	
#if defined(CHN) /* China Spec 95.03.01 S.Tanaka */
 #if (PRO_MEM_NEW == ENABLE) /* 1996/04/15 Eguchi */
	if (CHK_UNI_JrnlLifeMonitorPrint() == 0) {
 #else
	if(!(((UBYTE)(SYS_MemorySwitch[MEMORY_SW_I0] & 0x10)))){ /* StandardID[] Fix */
 #endif
		switch (SYS_Opt2[stack_number].QueueDialItem) {	/** ダイアル種別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
		case SYS_SPEED_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			break;
		case SYS_ONETOUCH_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			break;
		case SYS_DIRECT_DIAL:		/** 直接ダイアル */
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYS_OptionDirectDial );
			break;
		default:
			break;
		}
		if((SYS_Opt2[stack_number].QueueDialItem == SYS_SPEED_DIAL) ||									/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
		   (SYS_Opt2[stack_number].QueueDialItem == SYS_ONETOUCH_DIAL)){	/** ワンタッチ・ダイアル *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, &SYS_OptionDialBuffer[0], 20);		/** ダイアル・データを相手先名にセット */

			Journal->Kind = SYS_JournalKind;	/** 通信種別 */
			return;
		}
	}
#endif

#if defined(DEU)	/* 97/11/13 by M.H. */
	if ((SYS_Opt[stack_number].StandardID[0] == 0x00)&&(SYS_Opt[stack_number].NonStandardID[0] == 0x00)) {	/** 交信相手機の標準ＩＤと非標準ＩＤに何も登録されていない */
		switch (SYS_Opt2[stack_number].QueueDialItem) {	/** ダイアル種別 */	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
		/*================*/
		/*= 短縮ダイアル =*/
		/*================*/
		case SYS_SPEED_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			if ( SYS_Opt2[stack_number].QueueDialOffset < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				if ((SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
					CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
				}
			}
			break;
		/*========================*/
		/*= ワンタッチ・ダイアル =*/
		/*========================*/
		case SYS_ONETOUCH_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			if ((SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
			}
			break;
		/*================*/
		/*= 直接ダイアル =*/
		/*================*/
		case SYS_DIRECT_DIAL:		/** 直接ダイアル */
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYS_OptionDirectDial );
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, &SYS_OptionDialBuffer[0], 20);		/** ダイアル・データを相手先名にセット */
				break;
		default:
			break;
		}
	}
#else	/* (DEU) */
 #if defined(EUR)
	if (CHK_ForeignApprovalDEU()) {
		if ((SYS_Opt[stack_number].StandardID[0] == 0x00)&&(SYS_Opt[stack_number].NonStandardID[0] == 0x00)) {	/** 交信相手機の標準ＩＤと非標準ＩＤに何も登録されていない */
			switch (SYS_Opt2[stack_number].QueueDialItem) {	/** ダイアル種別 */	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			/*================*/
			/*= 短縮ダイアル =*/
			/*================*/
			case SYS_SPEED_DIAL:
				FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				if ( SYS_Opt2[stack_number].QueueDialOffset < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
					if ((SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
						CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
					}
				}
				break;
			/*========================*/
			/*= ワンタッチ・ダイアル =*/
			/*========================*/
			case SYS_ONETOUCH_DIAL:
				FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);	/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				if ((SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
					CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
				}
				break;
			/*================*/
			/*= 直接ダイアル =*/
			/*================*/
			case SYS_DIRECT_DIAL:		/** 直接ダイアル */
				FCM_GetDialData(&SYS_OptionDialBuffer[0], SYS_OptionDirectDial );
				CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, &SYS_OptionDialBuffer[0], 20);		/** ダイアル・データを相手先名にセット */
					break;
			default:
				break;
			}
		}
	}
	else {
		switch (SYS_Opt2[stack_number].QueueDialItem) {	/** ダイアル種別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
		/*================*/
		/*= 短縮ダイアル =*/
		/*================*/
		case SYS_SPEED_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			if ( SYS_Opt2[stack_number].QueueDialOffset < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				if (SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Name[0] != 0x00) {	/** 相手先名が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
					CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Name, 20);		/** 相手先名セット *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				}
				else if ((SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
					CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],
											&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
				}
			}
			break;
		/*========================*/
		/*= ワンタッチ・ダイアル =*/
		/*========================*/
		case SYS_ONETOUCH_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			if (SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Name[0] != 0x00) {	/** 相手先名が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI,SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Name, 20);		/** 相手先名セット *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			}
			else if ((SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],
										&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
			}
			break;
		/*================*/
		/*= 直接ダイアル =*/
		/*================*/
		case SYS_DIRECT_DIAL:		/** 直接ダイアル */
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYS_OptionDirectDial );
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, &SYS_OptionDialBuffer[0], 20);		/** ダイアル・データを相手先名にセット */
			break;
		default:
			break;
		}
	 #if (PRO_DEPARTMENT == ENABLE)
		Journal->DepartmentCode = SYS_JournalDepartmentCode;	/** 部門コード */
	 #endif
	}
 #else	/* (EUR) */
 	/*
 	** ジャーナルの相手先欄に載せる内容の優先順位を変更するスイッチ (RDC200000497 郵政向け特ＲＯＭ作成依頼)
 	** modified by H.Hirao 2000/12/05
 	*/
 	is_set = TRUE;
 	if (CHK_UNI_JournalPriority()) {
		is_set = FALSE;
		/*
		** まず、この関数をコールする前に相手先のNon Standard ID -> Standard ID の優先順位でセットされ、
		** これらの情報が受信できていなければ、ここでワンタッチ、短縮、ダイレクトダイアルをジャーナルにセットする
		*/
		if (Journal->RemoteID_TTI[0] == NULL) {
			is_set = TRUE;
		}
	}
	if (is_set) {
		switch (SYS_Opt2[stack_number].QueueDialItem) {	/** ダイアル種別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
		/*================*/
		/*= 短縮ダイアル =*/
		/*================*/
		case SYS_SPEED_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			if ( SYS_Opt2[stack_number].QueueDialOffset < SYS_SPEED_DIAL_MAX ) {		/** 第２短縮の判別 *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				if (SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Name[0] != 0x00) {	/** 相手先名が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
					CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Name, 20);		/** 相手先名セット *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				}
				else if ((SYB_SpeedDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
					is_dail_set = TRUE;
#endif /* defined (KEISATSU) */
					CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],
											&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
				}
			}
			break;
		/*========================*/
		/*= ワンタッチ・ダイアル =*/
		/*========================*/
		case SYS_ONETOUCH_DIAL:
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial);/* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			if (SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Name[0] != 0x00) {	/** 相手先名が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
				CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI,SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Name, 20);		/** 相手先名セット *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
			}
			else if ((SYB_OnetouchDial[SYS_Opt2[stack_number].QueueDialOffset].Dial[0]&0xF0) != 0xF0) {	/** 電話番号が登録されている *//* 1998/02/03 Y.Murata	CHAR_JOURNAL */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
				is_dail_set = TRUE;
#endif /* defined (KEISATSU) */
				CMN_StringCopyNumOrNULL(&Journal->RemoteID_TTI[0],
										&SYS_OptionDialBuffer[0], 20);		/** 相手先名にセット */
			}
			break;
		/*================*/
		/*= 直接ダイアル =*/
		/*================*/
		case SYS_DIRECT_DIAL:		/** 直接ダイアル */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
			is_dail_set = TRUE;
#endif /* defined (KEISATSU) */
			FCM_GetDialData(&SYS_OptionDialBuffer[0], SYS_OptionDirectDial );
			CMN_StringCopyNumOrNULL(Journal->RemoteID_TTI, &SYS_OptionDialBuffer[0], 20);		/** ダイアル・データを相手先名にセット */
			break;
		default:
			break;
		}
	}
 #if (PRO_DEPARTMENT == ENABLE)
	Journal->DepartmentCode = SYS_JournalDepartmentCode;	/** 部門コード */
 #endif
 #endif	/* (EUR) */
#endif	/* (DEU) */
	Journal->Kind = SYS_JournalKind;	/** 通信種別 */
#if defined (KEISATSU) /* 警察FAX Modify by SMuratec 李 2005/08/23 */
 #if 0 /* 仕様変更 Modify by SMuratec 李 2005/10/10 */
**	if (is_dail_set) {
**		if  (Journal->KeisatsuID[0] == NULL) {
**			if (SYS_InternalLineNumberSave == SYS_STD_LINE_COM) {
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[0], "ｶ", 1);
**			}
**			else {
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[0], "ｹ", 1);
**			}
**			switch (SYS_FaxComType){
**				case SYS_ISSEI_TX: /* 一斉指令送信 */
**				case SYS_ISSEI_RX: /* 一斉指令受信 */
**				case SYS_ISSEI_KIDO_TX: /* 指令起動信号による一斉指令送信 */
**				case SYS_ISSEI_KIDO_RX: /* 指令起動信号による一斉指令受信 */
**					CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[1], "ｲ", 1);
**					break;
**				default:
**					CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[1], "ｺ", 1);
**					break;
**			}
**			if (FCM_S1_Scramble){
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[2], "S", 1);
**			}
**			else {
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[2], "N", 1);
**			}
**			if (FCM_S1_Senyo){
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[3], "ｾ", 1);
**			}
**			else {
**				CMN_StringCopyNumNotNULL(&Journal->KeisatsuID[3], "ｷ", 1);
**			}
**			Journal->KeisatsuID[4] = 0x00;	/* NULL */
**		}
**	}
**	else {
**		Journal->KeisatsuID[0] = 0x00;	/* NULL */
**	}
 #endif
#endif /* defined (KEISATSU) */
}

/*************************************************************************
	module		:[ジャーナル・データを登録する]
	function	:[]
	commom		:[
		FaxComTXorRX_Sign		: 送信受信判別
		GrayModeFlag			: ハーフトーンモード
		FirstTxMode				: 送信モード
		TxMode					: 送信モード
		FaxComStartTime			: 通信開始時刻
		FaxComPeriod			: 通信時間
		SYS_TxTotalPage			: 送信ページ
		FaxComResult			: 通信結果
		SYS_FaxComType			: 通信種別
	]
	condition	:[]
	comment		:[
			修正履歴
			1.料金表に載せる部門コード毎の送受信ページ数のセット 94/9/12
	]
	return		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver6.0),H8/300]
	keyword		:[MAN]
	date		:[]
	author		:[村田]
*************************************************************************/
void MAN_SetJournal(UBYTE stack_number)
 {
	UBYTE	i;
	UBYTE	num;
	UBYTE	dummy;
	UWORD			que_num;
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/25 By H.Hirao */
	UBYTE	box_num;
#endif
#if defined(POPLAR_F)
	UBYTE	backup_journal_point;
	struct SYS_T30MonitorData_t	*t30;
#endif

#if defined(POPLAR_F)
	backup_journal_point = SYB_JournalPoint;
#endif

	num = stack_number;

	if (stack_number == 0) {
		CMN_DisableInterrupt(); /* 1998/01/26 Y.Murata */
		/*----------------------------------------------*/
		/*---各メンバをコピーします  (FaxComEndData) ---*/
		/*----------------------------------------------*/
		SYS_Opt[0].SYS_CurrentExecQueueNo	= SYS_CurrentExecuteNoSave;	/* display data */

		SYS_Opt[0].SYS_FaxCommStage			= SYS_FaxCommStage;
		SYS_Opt[0].SYS_FaxComType			= SYS_FaxComType;
		SYS_Opt[0].SYS_FaxComTxType			= SYS_FaxComTxType;
		SYS_Opt[0].SYS_TxTotalPage			= SYS_TxTotalPage;
		SYS_Opt[0].SYS_RxTotalPage			= SYS_RxTotalPage;
		SYS_Opt[0].SYS_RxMemoryFileItem		= SYS_RxMemoryFileItem;
		SYS_Opt[0].TxMemoryFileItem			= TxMemoryFileItem;
		SYS_Opt[0].RxMode					= RxMode;
		SYS_Opt[0].TxMode					= TxMode;
		SYS_Opt[0].FaxComTXorRX_Sign		= FaxComTXorRX_Sign;
		SYS_Opt[0].FaxCompatibleErrorCode	= FaxCompatibleErrorCode;
		SYS_Opt[0].FaxComResult				= FaxComResult;
		SYS_Opt[0].SYS_VoiceCallAccepted	= SYS_VoiceCallAccepted;
		SYS_Opt[0].SYS_TensouJushinFlag		= SYS_TensouJushinFlag;
		SYS_Opt[0].FirstTxMode				= FirstTxMode;
		SYS_Opt[0].JournalTxTotalCount		= JournalTxTotalCount;
		SYS_Opt[0].JournalRxTotalCount		= JournalRxTotalCount;
		SYS_Opt[num].GrayModeFlag			= GrayModeFlag;		/* 1997/11/27 */
#if (PRO_FCODE_RELAY == ENABLE) /* 1998/09/25 By H.Hirao */
		SYS_Opt[0].SYS_RxMemoryFileNo		= SYS_RxMemoryFileNo;
#endif
		for (i = 0; i < SYS_ERROR_PAGE; i++) {
			SYS_Opt[0].TxResponsedRTN_PageSign[i] = TxResponsedRTN_PageSign[i];
		}
		for (i = 0; i < SYS_TTI_ID_MAX; i++) {
			SYS_Opt[0].NonStandardID[i] = NonStandardID[i];
		}
		for (i = 0; i < SYS_ID_MAX; i++) {
			SYS_Opt[0].StandardID[i] = StandardID[i];
		}

		if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_MODEM_144K) {
			SYS_Opt[0].SYS_V34ProcedureExecutingFlag = 0;
		}
		else {

#if (PRO_MODEM == R288F)
			SYS_Opt[0].SYS_V34ProcedureExecutingFlag = SYS_V34ProcedureExecutingFlag;	/** AL-100と同じ処理にします by O.Kimoto 1997/11/29 */
#else
			SYS_Opt[0].SYS_V34ProcedureExecutingFlag = 0;	/** AL-100と同じ処理にします by O.Kimoto 1997/11/29 */
#endif

		}

		SYS_OptionModemTime[0].StartTime = FaxComStartTime;
		SYS_OptionModemTime[0].EndTime = FaxComStartTime + (unsigned long)FaxComPeriod;

		CMN_EnableInterrupt(); /* 1998/01/26 Y.Murata */

	}

#if 0	/* 1998/02/03 Y.Murata */
**	if (SYS_Opt[num].SYS_FaxComType == SYS_COMMAND_EXECUTE) {
**		que_num = SYS_Opt[num].SYS_CurrentExecQueueNo;
**
**		if (SYB_ExecQueue[que_num].Kind == SYS_COMMAND_TRX) {
**			SYS_JournalKind = SYB_CommandFile[SYB_ExecQueue[que_num].Number.Command].Option.Item;
**			SYS_JournalDepartmentCode = SYB_CommandFile[SYB_ExecQueue[que_num].Number.Command].DepartmentCode;
**			if ( SYB_ExecQueue[que_num].ExecDial.Item == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
**				SYS_OptionDirectDial
**				= SYB_CommandFile[SYB_ExecQueue[que_num].Number.Command].DialNumber.Direct[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Command];		/** ダイレクトダイアルセーブ */
**			}
**		}
**		else if (SYB_ExecQueue[que_num].Kind == SYS_BATCH_TX) {
**			SYS_JournalKind = SYS_BATCH_MEMORY_TX;
**			SYS_JournalDepartmentCode = 0xFFFF;
**			if ( SYB_ExecQueue[que_num].ExecDial.Item == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
**				SYS_OptionDirectDial
**				= SYB_BatchTxFile[SYB_ExecQueue[que_num].Number.Batch].DialNumber[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Command].FaxNumber.Direct;		/** ダイレクトダイアルセーブ */
**			}
**		}
**#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 1997/03/06 Y.Murata */
**		else {
**			SYS_JournalKind = SYS_CONTINUOUS_POLLING_RX;
**			SYS_JournalDepartmentCode = 0xFFFF;
**			if ( SYB_ExecQueue[que_num].ExecDial.Item == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
**				SYS_OptionDirectDial
**				= SYB_ContinuousPolling.DialNumber.Direct[SYB_ExecQueue[que_num].ExecDial.ExecNumber.Command];		/** ダイレクトダイアルセーブ */
**
**			}
**		}
**#endif
**	}
**#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By S.Fukui Dec.4,1997 */
**	else if (SYS_Opt[num].SYS_FaxComType == SYS_MANUAL_TX) {					/** 手動送信 */
**		SYS_JournalDepartmentCode = SpecialCommandValue.DepartmentCode;
**	}
**	else if (SYS_Opt[num].SYS_FaxComType == SYS_MANUAL_RX) {					/** 手動送信 */
**		SYS_JournalDepartmentCode = SpecialCommandValue.DepartmentCode;
**	}
**#endif
#endif
	/* 1998/02/03 Y.Murata	CHAR_JOURNAL
	 * キャラクタジャーナル記載用データ
	*/
	if (SYS_Opt[num].SYS_FaxComType == SYS_COMMAND_EXECUTE) {
		que_num = SYS_Opt[num].SYS_CurrentExecQueueNo;

		if (SYS_Opt2[num].QueueKind == SYS_COMMAND_TRX) {
			SYS_JournalKind = SYS_Opt[num].CommandFileOptionItem;
			SYS_JournalDepartmentCode = SYS_Opt2[num].CommandDepartmentCode;
			if ( SYS_Opt2[num].QueueDialItem == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
				SYS_OptionDirectDial
				= &SYS_Opt2[num].CommandDirectDial[0];		/** ダイレクトダイアルセーブ */
			}
		}
		else if (SYS_Opt2[num].QueueKind == SYS_BATCH_TX) {
			SYS_JournalKind = SYS_BATCH_MEMORY_TX;
			SYS_JournalDepartmentCode = 0xFFFF;
			if ( SYS_Opt2[num].QueueDialItem == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
				SYS_OptionDirectDial
				= &SYS_Opt2[num].CommandDirectDial[0];		/** ダイレクトダイアルセーブ */
			}
		}
#if (PRO_CONTINUOUS_POLLING == ENABLE)	/* 1997/03/06 Y.Murata */
		else {
			SYS_JournalKind = SYS_CONTINUOUS_POLLING_RX;
			SYS_JournalDepartmentCode = 0xFFFF;
			if ( SYS_Opt2[num].QueueDialItem == SYS_DIRECT_DIAL) {		/** 直接ダイアル */
				SYS_OptionDirectDial
				= &SYS_Opt2[num].CommandDirectDial[0];		/** ダイレクトダイアルセーブ */

			}
		}
#endif
	}
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By S.Fukui Dec.4,1997 */
	else if (SYS_Opt[num].SYS_FaxComType == SYS_MANUAL_TX) {					/** 手動送信 */
		SYS_JournalDepartmentCode = SpecialCommandValue.DepartmentCode;
	}
	else if (SYS_Opt[num].SYS_FaxComType == SYS_MANUAL_RX) {					/** 手動送信 */
		SYS_JournalDepartmentCode = SpecialCommandValue.DepartmentCode;
	}
#endif

	/*--------------------------*/
	/* 送信用ジャーナル・データ */
	/*--------------------------*/
	if ( SYS_Opt[num].FaxComTXorRX_Sign == TX_COM_MODE ) {	/** 送信 */
		MAN_SetJournalFileTxNo(stack_number);		/** 通番 */
		Journal->RemoteID_TTI[0] = 0x00;		/** 相手先名初期化 */
		MAN_SetRemoteID_ToJournal(stack_number);	/** 相手先名をジャーナルにセット */

		if ( SYS_Opt[num].GrayModeFlag == 1 ) {
			Journal->Mode  = SYS_Opt[num].FirstTxMode;	/** 通信モード */
		}
		else{
			Journal->Mode  = SYS_Opt[num].TxMode;
		}

		Journal->StartTime = SYS_OptionModemTime[num].StartTime;	/** 通信開始時間 */
		Journal->TotalTime = (UWORD)(SYS_OptionModemTime[num].EndTime - SYS_OptionModemTime[num].StartTime);	/** 通信時間 */
#if(0)/* 256ページ以上ジャーナルに記載できない。V851 By Y.Suzuki 2002/08/09 */
		Journal->Page	   = (UBYTE)SYS_Opt[num].SYS_TxTotalPage;/** 通信ページ数 */
#else
		Journal->Page	   = SYS_Opt[num].SYS_TxTotalPage;/** 通信ページ数 */
#endif
		if (SYB_MaintenanceSwitch[37] & 0x10) {
			SYB_LifeMonitor.TransmitCount++;	/** ライフモニタ送信回数 */
		}
		else {
			SYB_LifeMonitor.TransmitCount += SYS_Opt[num].SYS_TxTotalPage;	/** ライフモニタ送信枚数 */
		}

		Journal->Result = SYS_Opt[num].FaxComResult;				/** 交信結果 */
		if (SYS_Opt[num].SYS_V34ProcedureExecutingFlag == 1) {
			Journal->Result |= V34_MODE_SET;
		}

		switch ( SYS_Opt[num].SYS_FaxComType ) {		/** 通信種別 */
		case SYS_COMMAND_EXECUTE:		/** コマンド通信 */
			MAN_SetCOMEXEC_ModeToJournal(que_num,stack_number);	/** 通信モード、部門コードSET、RemoteID_TTI再セット *//*引数追加 上記履歴参照 */
#if (PRO_DEPARTMENT == ENABLE)/* 94/9/12 Y.Suzuki */
			if (CHK_DepartmentON()
			 && (SYS_JournalKind != SYS_RELAYED_TX)
			 && (SYS_JournalKind != SYS_RELAYED_TX_REPORT)
			 && (SYS_JournalKind != SYS_BATCH_MEMORY_TX)) {
								/* Never Count Up When Relayed Tx 94/12/28 Y.Suzuki */

 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト added by thonda 1997/11/29 */
				MAN_SetDepartManageFile( num ,0);
 #endif
				for(i = 0; i < (SYS_DEPART_MAX - 1); i++) {
					if(SYB_DepartFile[i].Code == SYS_JournalDepartmentCode) {
						SYB_DepartFile[i].TxRxPage += SYS_Opt[num].SYS_TxTotalPage;
					}
				}
			}
#endif
			break;
		case SYS_MANUAL_TX:		/** 手動送信 */
			Journal->Kind = SYS_MANUAL_TRANSMIT;
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By S.Fukui Dec.4,1997 */
			if (CHK_DepartmentON()
			 && CHK_UNI_ManualTxTimeManage()) {
				MAN_SetDepartManageFile( num ,0);
				Journal->DepartmentCode = SYS_JournalDepartmentCode;	/** 部門コード */
			}
#endif
			break;
		case SYS_AUTO_CALLED:		/** 自動着信 */
			switch (SYS_Opt[num].TxMemoryFileItem) {		/** メモリ送信種別 */
			case SYS_MEM_POLLING_FILE:		/** ポーリング送信原稿 */
				Journal->Kind = SYS_POLLING_TX;
				break;
			case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング送信原稿 */
				Journal->Kind = SYS_DB_POLLING_TX;
				break;
			case SYS_MEM_SUB_SECURE_FILE:	/* #if (PRO_F_CODE == ENABLE) 1997/09/22 */
			case SYS_MEM_SUB_BULLETIN_FILE:
				Journal->Kind = SYS_SELECT_POLLING_TX;
				break;
			default:
				Journal->Kind = 0xFF;
				break;
			}
			break;
#if (PRO_FIP == ENABLE)
		case SYS_FIP_SEND:		/** ＦＩＰ送信 */
			Journal->Kind = SYS_FIP_TRANSMIT;
			break;
#endif
		case SYS_REMOTE_FAX_TX:		/** リモートＦＡＸ送信 */
			Journal->Kind = SYS_REMOTE_TX;				/** リモートＦＡＸ送信 */;
			break;
		/* 手動ポーリング送信が備考欄に載らない不具合対応 by H.Kubo 1999/12/16 *//* 1999/12/16 Y.Murata NAGANO\HIIRAGIより */
		case SYS_MANUAL_RX:		/* 手動着信 */
			switch (SYS_Opt[num].TxMemoryFileItem) {		/** メモリ送信種別 */
			case SYS_MEM_POLLING_FILE:		/** ポーリング送信原稿 */
				Journal->Kind = SYS_POLLING_TX;
				break;
			case SYS_MEM_DB_POLLING_FILE:	/** 検索ポーリング送信原稿 */
				Journal->Kind = SYS_DB_POLLING_TX;
				break;
			case SYS_MEM_SUB_SECURE_FILE:
			case SYS_MEM_SUB_BULLETIN_FILE:
				Journal->Kind = SYS_SELECT_POLLING_TX;
				break;
			default:
				Journal->Kind = 0xFF;
				break;
			}
			break;
		}

#if 0	/* NAGANOより 1999/10/21 Y.Murata */
**		if ((SYS_Opt[num].FaxComResult&~ECM_MODE_SET) != (TRANSMITERROR|0x0014)&&
**			(SYS_Opt[num].FaxComResult&~ECM_MODE_SET) != (RECEIVEERROR|0x0014)) {	/** T.1.4 or R.1.4でない */
#endif
		if ((SYS_Opt[num].FaxComResult&~(ECM_MODE_SET | V34_MODE_SET)) != (TRANSMITERROR|0x0014)&&
			(SYS_Opt[num].FaxComResult&~(ECM_MODE_SET | V34_MODE_SET)) != (RECEIVEERROR|0x0014)) {	/** T.1.4 or R.1.4でない (V34ﾋﾞｯﾄ追加 1999/09/17 by K.Okada)  NAGANOより 1999/10/21 Y.Murata*/
			/*------------------------------*/
			/** 送信証のセット				*/
			/* ﾌﾟﾘﾝﾄの起動はﾒｲﾝで行います	*/
			/*------------------------------*/
			if (SYS_Opt[num].SYS_FaxComType == SYS_COMMAND_EXECUTE) {	/** コマンド通信 */
#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/02/14 */
#if (0)	/* 変更 MAN_SetJournalFileTxNo()の中でクリアするようにしましたのでここでは不要です   by T.Soneoka 1998/02/04 */
//				Journal->Option = 0;			/** 付加情報 通信証プリント要求クリア */
#endif
#else
				Journal->Option &= ~SYS_TCR_REQUEST;			/** 付加情報 通信証プリント要求クリア */
#endif

			}
			else {		/** 手動送受信、自動着信 */
				if ((SYS_Opt[num].TxMemoryFileItem != SYS_MEM_POLLING_FILE) &&
					(SYS_Opt[num].TxMemoryFileItem != SYS_MEM_DB_POLLING_FILE) &&
					(SYS_Opt[num].TxMemoryFileItem != SYS_MEM_SUB_SECURE_FILE) &&
					(SYS_Opt[num].TxMemoryFileItem != SYS_MEM_SUB_BULLETIN_FILE)) {	/** 手動送信である */
					if ((SYS_BackUpConfirmationReport == TCR_REQUEST) ||
						((SYS_BackUpConfirmationReport == RCR_REQUEST) &&
						(SYS_Opt[num].SYS_RxTotalPage < 1))) {

/* 
** 送信証とチェックメッセージを両方プリントする不具合、
** PRO_MULTI_LINE == ENABLEと同じパスにします 1999/1/26 by T.Soneoka 
*/
#if (0)
**#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/02/14 */
**#if (0)	/* 変更 MAN_SetJournalFileTxNo()の中でクリアするようにしたので、ＯＲにします   by T.Soneoka 1998/02/04 */
**//						Journal->Option = SYS_TCR_REQUEST;		/** 付加情報 通信証プリント */
**#endif
**						Journal->Option |= SYS_TCR_REQUEST;		/** 付加情報 通信証プリント */
**#else
**						Journal->Option |= SYS_TCR_REQUEST;		/** 付加情報 通信証プリント */
**						if (SYS_BackUpManualFaxCommErrReq) {
**							SYS_BackUpManualFaxCommErrReq = 0;
**						}
**#endif
#else
						Journal->Option |= SYS_TCR_REQUEST;		/** 付加情報 通信証プリント */
						if (SYS_BackUpManualFaxCommErrReq) {
							SYS_BackUpManualFaxCommErrReq = 0;
						}
#endif
					}
					else {
#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/02/14 */
#if (0)	/* 変更 MAN_SetJournalFileTxNo()の中でクリアするようにしたのでここでは不要です  by T.Soneoka 1998/02/04 */
//						Journal->Option = 0;		/** 付加情報 通信証プリント要求クリア */
#endif
#else
						Journal->Option &= ~SYS_TCR_REQUEST;		/** 付加情報 通信証プリント要求クリア */
#endif
					}
				}
			}
		}
		else {			/* 手動送信　T1.4のとき、送信証ﾘｸｴｽﾄを安全のためクリアしておく 96/08/09 By T.Yamaguchi */
#if (PRO_MULTI_LINE == DISABLE)	/* Add By O.Kimoto 1997/02/14 */
#if (0)	/* 変更 MAN_SetJournalFileTxNo()の中でクリアするようにしたのでここでは不要です  by T.Soneoka 1998/02/04 */
//			Journal->Option = 0;		/** 付加情報 通信証プリント要求クリア */
#endif
#else
			Journal->Option &= ~SYS_TCR_REQUEST;		/** 付加情報 通信証プリント要求クリア */
#endif
		}

		MAN_IncTxJournalPoint();					/** ジャーナル書き込みポイント更新 */
	}
	/*--------------------------*/
	/* 受信用ジャーナル・データ */
	/*--------------------------*/
	else if ( SYS_Opt[num].FaxComTXorRX_Sign == RX_COM_MODE ) {		/** 受信 */
		MAN_SetJournalFileRxNo(stack_number);			/** 通番 */
		Journal->RemoteID_TTI[0] = 0x00;			/*　相手先名初期化 */
		MAN_SetRemoteID_ToJournal(stack_number);		/** 相手先名をジャーナルにセット */

		Journal->Mode  = SYS_Opt[num].RxMode;		/** 通信モード */
		Journal->StartTime = SYS_OptionModemTime[num].StartTime;	/** 通信開始時間 */
		Journal->TotalTime = (UWORD)(SYS_OptionModemTime[num].EndTime - SYS_OptionModemTime[num].StartTime);	/** 通信時間 */
#if(0)/* 256ページ以上ジャーナルに記載できない。V851 By Y.Suzuki 2002/08/09 */
		Journal->Page	   = (UBYTE)SYS_Opt[num].SYS_RxTotalPage;	/** 通信ページ数 */
#else
		Journal->Page	   = SYS_Opt[num].SYS_RxTotalPage;	/** 通信ページ数 */
#endif
/*		SYB_LifeMonitor.ReceiveCount += SYS_RxTotalPage;	Del 1995.10.18 By T.Y  ライフ・モニタ R対策 受信枚数削除 */
		if (SYB_MaintenanceSwitch[37] & 0x10) {
			SYB_LifeMonitor.PrintCountReceive++;
		}
		Journal->Result	   = SYS_Opt[num].FaxComResult;			/** 交信結果 */
		if (SYS_Opt[num].SYS_V34ProcedureExecutingFlag == 1) {
			Journal->Result |= V34_MODE_SET;
		}

		switch ( SYS_Opt[num].SYS_FaxComType ) {		/** 通信種別 */
		case SYS_COMMAND_EXECUTE :		/** コマンド通信 */
			MAN_SetCOMEXEC_ModeToJournal(que_num,stack_number);			/** 通信モード、部門コードSET、RemoteID_TTI再SET *//*引数追加 上記履歴参照 */
#if(PRO_DEPARTMENT == ENABLE)/* 94/9/12 Y.Suzuki */
			if(CHK_DepartmentON()) {
				/** ポーリング受信原稿のページ数をカウント */
 #if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト added by thonda 1997/11/29 */
				MAN_SetDepartManageFile( num ,1);
 #endif
				for(i = 0; i < (SYS_DEPART_MAX - 1); i++) {
					if(SYB_DepartFile[i].Code == SYS_JournalDepartmentCode) {
						SYB_DepartFile[i].TxRxPage += SYS_Opt[num].SYS_RxTotalPage;
					}
				}
			}
#endif
			break;
		case SYS_MANUAL_RX :		/** 手動受信 */
			Journal->Kind = SYS_MANUAL_RECEIVE;		/** 通信種別セット */
#if (PRO_FIP == ENABLE)
			if ( SYS_FaxComFIP_RxActiveFlag == 1 ) {	/** ＦＩＰ受信 */
				Journal->Kind = SYS_FIP_RECEIVE;	/** 通信種別 */
				if ( SYS_Opt[num].SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE ) {		/** 親展受信 */
					Journal->Kind = SYS_FIP_SECURE;		/** 通信種別 */
				}
			}
#endif
#if (PRO_DEPART_NEW_LIST == ENABLE)	/* 簡易料金管理リスト By S.Fukui Dec.4,1997 */
			if (CHK_DepartmentON()
			 && CHK_UNI_ManualRxTimeManage()) {
				MAN_SetDepartManageFile( num , 1);
				Journal->DepartmentCode = SYS_JournalDepartmentCode;	/** 部門コード */
			}
#endif
			break;
		case SYS_AUTO_CALLED:		/** 自動着信 */
			switch ( SYS_Opt[num].SYS_RxMemoryFileItem ) {	/** 受信原稿 */
			case SYS_MEM_RX_FILE:		/** メモリ受信原稿 */
				Journal->Kind = SYS_NO_PAPER_RX;
				break;
			case SYS_MEM_SECURE_RX_FILE :		/** 親展受信原稿 */
				Journal->Kind = SYS_SECURE_RX;
				break;
			case SYS_MEM_TX_FILE:		/** メモリ送信原稿 (中継指示受信) */
#if (PRO_FCODE_RELAY == ENABLE) && (PRO_FCODE_KIND_DISPLAY == ENABLE)/* 1998/09/25 By H.Hirao */
				box_num = SYB_FcodeBoxNoByRelayedTxComNo[SYS_Opt[num].SYS_RxMemoryFileNo];
				if (!box_num) {
					Journal->Kind = SYS_RELAY_RX;
				}
				else {
					if (SYB_SubAddressBoxTable[box_num - 1].Status == SUB_ADDRESS_RELAY_BOX) {
						Journal->Kind = SYS_MEMORY_RELAY_BOX_RX;
					}
					else {
						Journal->Kind = SYS_RELAY_RX;
					}
				}
#else
				Journal->Kind = SYS_RELAY_RX;
#endif
				break;
			case SYS_MEM_REMOTE_TX_FILE :		/** リモートＦＡＸ受信 */
				Journal->Kind = SYS_REMOTE_RX;				/** リモートＦＡＸ受信 */
				break;
#if (PRO_FCODE_KIND_DISPLAY == ENABLE) /* ジャーナルにＦコードの種類を表示 1998/09/28 H.Hirao */
			case SYS_MEM_SUB_SECURE_FILE:	/* #if (PRO_F_CODE == ENABLE) 1997/09/22 */
				Journal->Kind = SYS_SUBADDRESS_SECURE_RX;
				break;
			case SYS_MEM_SUB_BULLETIN_FILE:
				Journal->Kind = SYS_SUBADDRESS_BULLETIN;
				break;
#else
			case SYS_MEM_SUB_SECURE_FILE:	/* #if (PRO_F_CODE == ENABLE) 1997/09/22 */
			case SYS_MEM_SUB_BULLETIN_FILE:
				Journal->Kind = SYS_SUBADDRESS_SECURE_RX;
				break;
#endif
#if (PRO_CIPHER == ENABLE)
			case SYS_MEM_CIPHER_RX_FILE:	/*	1998/01/12  By T.Yamaguchi */
				Journal->Kind = SYS_CIPHER_RX;
				break;
#endif
			default:
				Journal->Kind = 0xFF;
				break;
			}
			break;
#if (PRO_FIP == ENABLE)
		case SYS_FIP_CALLED:		/** ＦＩＰ自動着信 */
			Journal->Kind = SYS_FIP_RECEIVE;
			if ( SYS_Opt[num].SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE ) {
				Journal->Kind = SYS_FIP_SECURE;
			}
			break;
		case SYS_FIP_POLL:		/** ＦＩＰポーリング */
			Journal->Kind = SYS_FIP_POLLING;
			break;
#endif
		case SYS_MANUAL_POLLING:		/** 手動ポーリング受信 */
			Journal->Kind = SYS_POLLING_RX;
			break;
		}

		MAN_IncRxJournalPoint();			/** 受信ジャーナルポイント更新 */
	}
	/*--------------*/
	/* リモート診断 */
	/*--------------*/
	else if ( SYS_Opt[num].FaxComTXorRX_Sign == DIAG_MODE ) {	/** リモート診断 */
		if (num == 0) {
			SYB_T30Monitor.JournalType = SYS_T30_RXJOURNAL;		/** Ｔ３０モニタ通信種別セット */

	#if (PRO_JOURNAL == SEPARATE)
			SYB_T30Monitor.Index = SYS_RxJournalPoint;			/** Ｔ３０モニタ・データ識別 */
	#endif
	#if (PRO_JOURNAL == UNITED)
			SYB_T30Monitor.Index = SYB_JournalPoint;			/** Ｔ３０モニタ・データ識別 */
	#endif
		}
	}
#if (PRO_FIP == ENABLE)
	/* 一番最後にFIP用のIDをBufferにｾｯﾄします */
	CMN_StringCopyNumOrNULL((UBYTE *)&SYS_FIP_ComRemoteID[0], (UBYTE *)&SYS_OPt[num].StandardID[0], 20);		/** ＦＩＰ用バッファセット */
#endif

	if (SYS_Opt[num].SYS_RxMemoryFileItem == SYS_MEM_RX_FILE) {	/* 単なるメモリ受信 */
		if (SYS_Opt[num].SYS_RxTotalPage >= 1) {	/* 1枚以上受信 */
			/*
			 * 代行受信管理テーブルにキャラクタジャーナルポインタセット
			 * ジャーナルポインターのセットは代行受信消去通知のためにセットする
			 * よって、もしこの段階でプリント完了になっていたら、それはそれでいい
			*/
			/*アトランタでは、ＰＡＴジャーナルがない。そのためここを通る時、ステータスがまだ、プリントに
			 *なっていない。コウベの時は、ＭＨ展開している間にステータスが、プリントになっていた模様（ラッキ～）
			 *と言うわけで、ストアの時も条件に追加。
			*/
			for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {
#if (PRO_REVERSE_PRINT == DISABLE)	/* By M.Tachibana 1998/05/19 */
				if ((SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_PRINT) || (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE)) {
#else
				if ((SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_PRINT)
				 || (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE)
				 || (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE_PRINT)
				 || (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_FAST_PRINT)) {
#endif
					if (SYB_MemoryRxPrint[i].JournalPoint == 0) {
#if (PRO_LINENUMBER == TWICE_LINE)
						/* ＱＡＴ不具合
						** 拡張回線で受信ができない不具合修正
						** 拡張回線の処理が抜けていた（ "& 0x7f")
						** by O.Kimoto 1998/04/13
						*/
						if ((SYB_MemoryRxPrint[i].StackNumber & 0x7f) == num) {
							SYB_MemoryRxPrint[i].JournalPoint = Journal;
							break;
						}
#else
						if (SYB_MemoryRxPrint[i].StackNumber == num) {
							SYB_MemoryRxPrint[i].JournalPoint = Journal;
							break;
						}
#endif
					}
				}
			}
			if (i >= SYS_MEMORY_RX_MAX) {

				/*
				 * 受領証送信時は、通信が終了する前に受信原稿プリント終了している場合があるので
				 * その時はここを通る
				*/
				/* 受領証送信以外(単なる受信）で、ここを通ることはありえない */
				/*outp((unsigned long)0,(UBYTE)0);*/	/* WriteProtectError for ICE */	/**オプションボードをリセットしてください*/
				dummy = 1;	/* debug */
			}
		}
	}

#if defined(POPLAR_F)
	if ((SYS_Opt[num].FaxComTXorRX_Sign == TX_COM_MODE) ||	/** 送信 */
		(SYS_Opt[num].FaxComTXorRX_Sign == RX_COM_MODE)) {	/** 受信 */
		/*
		 * Ｔ３０のデータをＤＲＡＭにジャーナル分持たせる
		*/
		/*
		 * Ｔ３０コピー処理 stack_number番目のデータをbackup_journal_point番目にコピー
		*/
			CMN_DisableInterrupt();
			SYB_T30MonitorDRAM_Status[backup_journal_point] = 0;	/* */
			CMN_EnableInterrupt();

			/* ＤＲＡＭに貼り付けるアドレス */
			t30 = &SYB_T30MonitorDRAM[backup_journal_point];
			if (stack_number == 0) {
				CMN_StringCopyNum((UBYTE *)t30, &SYB_T30Monitor.JournalType,
					  (UWORD)sizeof(struct SYS_T30MonitorData_t));
				SYB_CompatibleErrorCode[backup_journal_point] = FaxCompatibleErrorCode;
			}
			else {
				DPR_GetT30Buffer((UWORD *)t30, (UWORD)(stack_number-1));
				SYB_CompatibleErrorCode[backup_journal_point] = SYS_Opt[stack_number].FaxCompatibleErrorCode;
			}
			t30->JournalType = MLT_T30Type[stack_number];
			t30->Index = MLT_T30Index[stack_number];
			CMN_DisableInterrupt();
			SYB_T30MonitorDRAM_Status[backup_journal_point] = 1;	/* データセット済み */
			CMN_EnableInterrupt();
	}
#endif

	CMN_DisableInterrupt(); /* 1998/01/26 Y.Murata */

	/*
	 * 手動送受信チェックメッセージ・プリント要求セット
	*/
	if (SYS_BackUpManualFaxCommErrReq) {
		SYS_BackUpManualFaxCommErrReq = 0;
		SYS_ManualFaxCommErrRequest = 1;
	}

	/*
	 * プロトコルモニタ自動印字要求セット。
	 * ジャーナルにのらないエラーの時は、自動プリントしません
	*/
	if (SYS_BackUpProtocolMonitorReq) {
		SYS_BackUpProtocolMonitorReq = 0;
		SYS_ProtocolMonitorPrintRequest = 1;
	}
	/* ２回線用追加 1997/10/18 */
	if (SYS_BackUpOptionLineT30PrintReq) {
		SYS_BackUpOptionLineT30PrintReq = 0;
		SYS_OptionLineT30PrintRequest = 1;
	}

	CMN_EnableInterrupt(); /* 1998/01/26 Y.Murata */

	/* 警察FAX DVT_ID46 Added by SMuratec 夏 2005/11/25 */
#if defined(KEISATSU)	
	IsJournalCompleted = TRUE;
#endif
}

/*************************************************************************
	module		:[－送信ジャーナルセット－　通番、ジャーナルポイント（書き
					込みポイント）の設定]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[H8/300,V53]
	language	:[H8/300,MS-C(Ver6.0)]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void MAN_SetJournalFileTxNo(UBYTE stack_number)
{
	Journal = &SYB_JournalFile[SYB_JournalPoint];		/** ポインタセット */

	Journal->Option = 0;			/** 付加情報クリア by T.Soneoka */
	if (stack_number == 0) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		if (SYS_InternalLineNumberSave == SYS_STD_LINE_COM) {
			Journal->Option &= ~SYS_EXT_LINE;
		}
		else {
			Journal->Option |= SYS_EXT_LINE;
		}
#endif
		SYB_T30Monitor.JournalType	= SYS_T30_TXJOURNAL;	/** Ｔ３０モニタ・通信種別 */
		SYB_T30Monitor.Index		= SYB_JournalPoint;		/** Ｔ３０モニタ・データ識別 */

#if defined(POPLAR_F)
#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/13 */
		if (CHK_UNI_MultiT30Monitor()) {
			CMN_StringCopyNum(&(SYS_T30Monitor + SYB_JournalPoint)->JournalType, &SYB_T30Monitor.JournalType, 
							  (UWORD)sizeof(struct SYS_T30MonitorData_t));
		}
 #endif
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		if (!(Journal->Option & SYS_EXT_LINE)) {	/* 標準ラインのとき */
			Journal->Number = SYS_Opt[stack_number].JournalTxTotalCount;	/** 送信通番 */
			if (SYB_TxTotalCount != SYS_Opt[stack_number].JournalTxTotalCount){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
				/** 何もしない */
				/* 日付が変われば ﾀｲﾏｰﾀｽｸ で SYB_TxTotalCount を 1 にしているが・・・しかし */
				/* その日の１発目の通信か日付が変わって１になったかわからないのでまずい		*/
			}
			else {	/** 通信開始時刻と終了時刻が日付を越えていない */
				if ( ++SYB_TxTotalCount > 999 ) {				/** １日の送信通番が９９９を越えた */
					SYB_TxTotalCount		= 1;				/** 送信通番１セット */
				}
			}
		}
		else {	/* 拡張ラインのとき */
			Journal->Number = JournalTxTotalCountExt;	/** 送信通番 */
			if (SYB_TxTotalCountExt != JournalTxTotalCountExt){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
				/** 何もしない */
				/* 日付が変われば ﾀｲﾏｰﾀｽｸ で SYB_TxTotalCount を 1 にしているが・・・しかし */
				/* その日の１発目の通信か日付が変わって１になったかわからないのでまずい		*/
			}
			else {	/** 通信開始時刻と終了時刻が日付を越えていない */
				if ( ++SYB_TxTotalCountExt > 999 ) {				/** １日の送信通番が９９９を越えた */
					SYB_TxTotalCountExt		= 1;				/** 送信通番１セット */
				}
			}
		}
#else
		Journal->Number = SYS_Opt[stack_number].JournalTxTotalCount;	/** 送信通番 */

		if (SYB_TxTotalCount != SYS_Opt[stack_number].JournalTxTotalCount){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
			/** 何もしない */
			/* 日付が変われば ﾀｲﾏｰﾀｽｸ で SYB_TxTotalCount を 1 にしているが・・・しかし */
			/* その日の１発目の通信か日付が変わって１になったかわからないのでまずい		*/
		}
		else {	/** 通信開始時刻と終了時刻が日付を越えていない */
			if ( ++SYB_TxTotalCount > 999 ) {				/** １日の送信通番が９９９を越えた */
				SYB_TxTotalCount		= 1;				/** 送信通番１セット */
			}
		}
#endif
	}
	else {
		Journal->Number = SYS_Opt[stack_number].JournalTxTotalCount;	/** 送信通番 */

		if (SYB_OptionJournalTxTotalCount[stack_number] != SYS_Opt[stack_number].JournalTxTotalCount){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
			/** 何もしない */
			/* 日付が変われば ﾀｲﾏｰﾀｽｸ で SYB_TxTotalCount を 1 にしているが・・・しかし */
			/* その日の１発目の通信か日付が変わって１になったかわからないのでまずい		*/
		}
		else {	/** 通信開始時刻と終了時刻が日付を越えていない */
			if ( ++SYB_OptionJournalTxTotalCount[stack_number] > 999 ) {	/** １日の送信通番が９９９を越えた */
				SYB_OptionJournalTxTotalCount[stack_number] = 1;			/** 送信通番１セット */
			}
		}
	}

	Journal->Type = TXTYPE;			/** 送信受信種別 */

	/** 回線番号の設定 *//* 1997/08/29 Y.Murata */
	Journal->StackNumber = stack_number;

#if (PRO_DEPARTMENT == ENABLE)
	Journal->DepartmentCode = 0xffff;		/* 部門コード初期化 96/08/13 初期値変更 By T.Yamaguchi */
#endif

	MLT_T30Index[stack_number] = SYB_JournalPoint;
	MLT_T30Type[stack_number] = SYS_T30_TXJOURNAL;
}


/*************************************************************************
	module		:[－受信ジャーナルセット－　通番、ジャーナルポイント（書き
					込みポイント）の設定]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[H8/300,V53]
	language	:[H8/300,MS-C(Ver6.0)]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void MAN_SetJournalFileRxNo(UBYTE stack_number)
{
	Journal = &SYB_JournalFile[SYB_JournalPoint];		/** ポインタセット */

	Journal->Option = 0;			/** 付加情報クリア by T.Soneoka */
	if (stack_number == 0) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		if (SYS_InternalLineNumberSave == SYS_STD_LINE_COM) {
			Journal->Option &= ~SYS_EXT_LINE;
		}
		else {
			Journal->Option |= SYS_EXT_LINE;
		}
#endif
		SYB_T30Monitor.JournalType	= SYS_T30_RXJOURNAL;						/** Ｔ３０モニタ・通信種別 */
		SYB_T30Monitor.Index		= SYB_JournalPoint;							/** Ｔ３０モニタ・データ識別 */

#if defined(POPLAR_F)
#else
 #if (PRO_MULTI_T30_MONITOR == ENABLE) /* By H.Fujimura 1999/04/13 */
		if (CHK_UNI_MultiT30Monitor()) {
			CMN_StringCopyNum(&(SYS_T30Monitor + SYB_JournalPoint)->JournalType, &SYB_T30Monitor.JournalType, 
							  (UWORD)sizeof(struct SYS_T30MonitorData_t));
		}
 #endif
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
		if (!(Journal->Option & SYS_EXT_LINE)) {	/* 標準ラインのとき */
			Journal->Number = SYS_Opt[stack_number].JournalRxTotalCount;						/** 受信通番 */
			if (SYB_RxTotalCount != SYS_Opt[stack_number].JournalRxTotalCount){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
				/** 何もしない */
			}
			else {	/** 通信開始時刻と終了時刻が日付を越えていない */
				if ( ++SYB_RxTotalCount > 999 ) {				/** １日の受信通番が９９９を越えた */
					SYB_RxTotalCount		= 1;				/** 受信通番１セット */
				}
			}
		}
		else {
			Journal->Number = JournalRxTotalCountExt;						/** 受信通番 */
			if (SYB_RxTotalCountExt != JournalRxTotalCountExt){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
				/** 何もしない */
			}
			else {	/** 通信開始時刻と終了時刻が日付を越えていない */
				if ( ++SYB_RxTotalCountExt > 999 ) {				/** １日の受信通番が９９９を越えた */
					SYB_RxTotalCountExt		= 1;				/** 受信通番１セット */
				}
			}
		}
#else
		Journal->Number = SYS_Opt[stack_number].JournalRxTotalCount;						/** 受信通番 */

		if (SYB_RxTotalCount != SYS_Opt[stack_number].JournalRxTotalCount){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
			/** 何もしない */
		}
		else {	/** 通信開始時刻と終了時刻が日付を越えていない */
			if ( ++SYB_RxTotalCount > 999 ) {				/** １日の受信通番が９９９を越えた */
				SYB_RxTotalCount		= 1;				/** 受信通番１セット */
			}
		}
#endif
	}
	else {
		Journal->Number = SYS_Opt[stack_number].JournalRxTotalCount;						/** 受信通番 */

		if (SYB_OptionJournalRxTotalCount[stack_number] != SYS_Opt[stack_number].JournalRxTotalCount){	/** 通信開始時刻と終了時刻が日付を越えた *//* 1994/09/30 */
			/** 何もしない */
		}
		else {	/** 通信開始時刻と終了時刻が日付を越えていない */
			if ( ++SYB_OptionJournalRxTotalCount[stack_number] > 999 ) {	/** １日の受信通番が９９９を越えた */
				SYB_OptionJournalRxTotalCount[stack_number] = 1;			/** 受信通番１セット */
			}
		}
	}

	Journal->Type = RXTYPE;			/** 送信受信種別 */

	/** 回線番号の設定 *//* 1997/08/29 Y.Murata */
	Journal->StackNumber = stack_number;

#if (PRO_DEPARTMENT == ENABLE)
	Journal->DepartmentCode = 0xffff;		/* 初期値変更　96/08/13 T.Yamaguchi 部門コード初期化 */
#endif
	MLT_T30Index[stack_number] = SYB_JournalPoint;
	MLT_T30Type[stack_number] = SYS_T30_RXJOURNAL;

}


/*************************************************************************
	module		:[－送信ジャーナルセット－　ジャーナル・ポイント（書き込み
					ポイント）の更新]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[H8/300,V53]
	language	:[H8/300,MS-C(Ver6.0)]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void MAN_IncTxJournalPoint(void)
{

#if (0)
** 	/* SAKAKI/HINOKIのように、プリント時間が通信より絶対的に遅い機種で、
** 	** 受信原稿プリントが多量にあり、それでも送・受信が頻繁に行われた場合、
** 	** 下記変数がUBYTEのため、”FF + 1 = 100 => 0”という現象が発生し、
** 	** ジャーナル自動プリントがONになっている場合、プリントされないという現象が発生する。
** 	** ついては、下記変数が最大ジャーナル件数を超えれば、カウントアップを止めます。
** 	** by O.Kimoto 1999/02/19
** 	*/
** 	++SYB_AutoJournalCounter;
#else
	if (SYB_AutoJournalCounter <= SYS_JOURNAL_MAX) {
		++SYB_AutoJournalCounter;
	}
#endif

	if ( ++SYB_JournalPoint >= SYS_JOURNAL_MAX ) {			/** 通信管理記録の記録位置を更新し最大ジャーナル数を越えた */

		SYB_JournalPoint = 0;								/** 通信管理記録の記録位置を初期化 */

	}
}


/*************************************************************************
	module		:[－受信ジャーナルセット－　ジャーナル・ポイント（書き込み
					ポイント）の更新]
	function	:[]
	commom		:[
	]
	condition	:[]
	comment		:[]
	return		:[]
	machine		:[H8/300,V53]
	language	:[H8/300,MS-C(Ver6.0)]
	keyword		:[FCM]
	date		:[]
	author		:[村田]
*************************************************************************/
void MAN_IncRxJournalPoint(void)
{

#if (0)
** 	/* SAKAKI/HINOKIのように、プリント時間が通信より絶対的に遅い機種で、
** 	** 受信原稿プリントが多量にあり、それでも送・受信が頻繁に行われた場合、
** 	** 下記変数がUBYTEのため、”FF + 1 = 100 => 0”という現象が発生し、
** 	** ジャーナル自動プリントがONになっている場合、プリントされないという現象が発生する。
** 	** ついては、下記変数が最大ジャーナル件数を超えれば、カウントアップを止めます。
** 	** by O.Kimoto 1999/02/19
** 	*/
** 	++SYB_AutoJournalCounter;
#else
	if (SYB_AutoJournalCounter <= SYS_JOURNAL_MAX) {
		++SYB_AutoJournalCounter;
	}
#endif

	if ( ++SYB_JournalPoint >= SYS_JOURNAL_MAX ) {			/** 通信管理記録の記録位置を更新し最大ジャーナル数を越えた */

		SYB_JournalPoint = 0;								/** 通信管理記録の記録位置の初期化 */

	}
}

#if 0
//  MAN_SUB.Cの　UBYTE CheckPollingRxCommand(UBYTE CommandNumber)
//  を使ってください	1997/11/20  By T.Yamaguchi
///*************************************************************************
//	module		:[ポーリングコマンドかどうかのチェック]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[V53]
//	language	:[MS-C(Ver.6.0)]
//	keyword		:[MAN]
//	date		:[1996/12/24]
//	author		:[村田]
//*************************************************************************/
//UBYTE MAN_CheckPollingCommand(UBYTE CommandNumber)	/* 多分未使用 */
//{
//	if (CommandNumber < SYS_COM_FILE_MAX) {
//		switch (SYB_CommandFile[CommandNumber].Status) {
//			case SYS_CMD_WAITING:
//			case SYS_CMD_EXECUTE:
//				switch (SYB_CommandFile[CommandNumber].Option.Item) {
//					case SYS_POLLING_RX:
//					case SYS_DB_POLLING_RX:
//					case SYS_SEQUENTIAL_POLLING:
//						return(1);
//					default:
//						return(0);
//				}
//			default:
//				return(0);
//		}
//	}
//	else {
//		return(0);
//	}
//}
//
#endif

/*************************************************************************
	module		:[機器設定、メモリＳＷ、機器パラの内容が変わった事を通知する]
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
	date		:[1997/01/08]
	author		:[村田]
*************************************************************************/
void MAN_ChangedSRAM_Parameter(UWORD value)
{
#if (PRO_MULTI_LINE == ENABLE)
	UWORD	i;

	SYS_ChangedSRAM_Status |= value;

	if (SYS_ChangedSRAM_Status) {
		for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {
			if (CHK_OptionLineExist((UBYTE)i)) {
				DPR_ChangedSRAM_Parameter(i - 1);
			}
		}
		SYS_ChangedSRAM_Status = 0;
	}
#endif
}


/*************************************************************************
	module		:[オプションモデムボード通信起動時の初期化処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/01/09]
	author		:[村田]
*************************************************************************/
void MAN_OptionModemStart(UBYTE number)
{
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	i;

#if defined(GBR)
	/* 受信完了アラーム鳴動停止処理追加 1998/02/24 Y.Murata */
	if (SYS_AudibleAlarmStatus & 0x02) { /** 受信完了アラーム鳴動中 */
		SYS_AudibleAlarmStatus &= ~0x01; /** 受信完了アラーム鳴動要求クリア */
	}
#endif

	ClearOptionModemDataArea(number);

	SYS_ClearOptionLineStop(number);

	if (!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM)) {	/* 内臓モデムがない */
		for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
			if (CHK_OptionLineExist((UBYTE)i)) {
				/* i が第１回線目のボードナンバー */
				break;
			}
		}
		if (number == i) {
			if (CHK_LineMonitor()) {
				MonitorSpeakerOn();
			}
			MDM_TxStopSwFlag = 0;	/* 1997/03/17 Y.Murata */
		}
	}
#endif
}

/*************************************************************************
	module		:[オプションモデムボード通信終了時の処理]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FCM]
	date		:[1997/01/09]
	author		:[村田]
*************************************************************************/
void MAN_OptionModemLast(UBYTE number)
{
#if (PRO_MULTI_LINE == ENABLE)
	UBYTE	i;

	if (!(SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM)) {	/* 内臓モデムがない */
		for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
			if (CHK_OptionLineExist((UBYTE)i)) {
				/* i が第１回線目のボードナンバー */
				break;
			}
		}
		if (number == i) {
			MonitorSpeakerOff();
			MDM_TxStopSwFlag = 0;	/* 1997/03/17 Y.Murata */
		}
	}
#endif
}

/*************************************************************************
	module		:[簡易料金管理]
	function	:[
		1.簡易料金管理ﾘｽﾄに積算する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1997/12/02]
	author		:[本多智幸]
*************************************************************************/
#if (PRO_DEPART_NEW_LIST == ENABLE)			/* 簡易料金管理リスト */
void MAN_SetDepartManageFile(UBYTE num, UBYTE mode)
{
	UBYTE	i;

			/*for (i = 0; i < (SYS_DEPART_MAX - 1); i++) { 1999/10/21 Y.Murata NAGANOより*/					/* 上から順に調べます */
			for (i = 0; i < (SYS_DEPART_MAX); i++) {					/* 上から順に調べます */
				if (SYB_DepartmentCode[i] == SYS_JournalDepartmentCode) {	/* 一致したらそれに積算 */
					if (mode == 0) {										/* 送信 */
						SYB_DepartManageTimeFile[i].Page += SYS_Opt[num].SYS_TxTotalPage;
					}
					else {													/* 受信 */
						SYB_DepartManageTimeFile[i].Page += SYS_Opt[num].SYS_RxTotalPage;
					}
					SYB_DepartManageTimeFile[i].Timer += (UDWORD)(SYS_OptionModemTime[num].EndTime - SYS_OptionModemTime[num].StartTime);
					if (SYB_DepartManageTimeFile[i].Timer >= (UDWORD)(1000UL * 60UL * 60UL)) {       /* 1000時間を越えたら */
						SYB_DepartManageTimeFile[i].Timer = (UDWORD)((1000UL * 60UL * 60UL) - 1UL);  /* 999時間59分59秒に固定 bythonda 1997/12/14 */
					}
					break;
				}
			}
}
#endif





/*************************************************************************
	module		:[受信１ページ確定時間チェック]
	function	:[
		１．１ページ受信したときに、同時刻の受信がないかどうかチェックします
	]
	return		:[
		TRUE:同時刻あり
		FALSE:同時刻なし
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MAN]
	date		:[1998/05/20]
	author		:[曽根岡拓]
*************************************************************************/
UBYTE MAN_CheckReceiveTime(UDWORD rcv_time, UWORD current_num)
{
	UWORD			i;

	i = 0;

	for (i = 0; i < SYS_MEMORY_RX_MAX; i++) {	/** 代行受信管理テーブルを検索 */
#if (PRO_REVERSE_PRINT == ENABLE)
		if (((SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE)
		||   (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_PRINT)
		||   (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE_PRINT)
		||   (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_FAST_PRINT))
		&&  (i != current_num)) {	/* 現在チェックしようとしているＮｏは飛ばします */
#else
		if (((SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_STORE)
		||   (SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_PRINT))
		&&  (i != current_num)) {	/* 現在チェックしようとしているＮｏは飛ばします */
#endif
			if (SYB_MemoryRxPrint[i].ReceiveTime == rcv_time) {
				return(TRUE);
			}
		}
	}
	return(FALSE);
}


#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/22 Y.Murata for KAKI */
UBYTE CheckQucikTxScan(UWORD que_no)
{
	UBYTE com_no;

	if (SYB_ExecQueue[que_no].Kind == SYS_COMMAND_TRX) {
		com_no = SYB_ExecQueue[que_no].Number.Command;
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_DOC_STORE) {
			if (SYS_DocumentStoreItem == SYS_MEM_TX_FILE) {
				if (SYS_DocumentStoreNo == (UWORD)com_no) {
					return(1);
				}
			}
		}
	}
	return(0);
}

#endif

#if (PRO_CLASS1_EXT_FUNC == ENABLE)	/* 1999/6/24 K.Kawata */
void MAN_ChangeItemLS2MP(void)
{
struct MEM_IndexData_t IndexP;
UWORD i,j;

	SYB_MemoryRxPrintWritePoint = (UBYTE)(MAN_GetMultiLineReceiveNumber((UBYTE)0));
	MemoryRxPrintPoint = &SYB_MemoryRxPrint[SYB_MemoryRxPrintWritePoint];
	MemoryRxPrintPoint->Status = SYS_MEMORY_RX_PRINT;
	MemoryRxPrintPoint->StorePage = MEM_CountTotalPage(SYS_MEM_CLASS1_TX_FILE, 0, MEM_IGNORE_BOX_NUMBER);
	for (i = 1; i <= MemoryRxPrintPoint->StorePage; i++) {
		IndexP.Item = SYS_MEM_CLASS1_TX_FILE;
		IndexP.No = 0;
		IndexP.Page = i;
		j = MEM_CheckIndexNo(&IndexP);
		MEM_IndexTable[j].Item = SYS_MEM_RX_FILE;
		MEM_IndexTable[j].No = SYB_MemoryRxPrintWritePoint;
	}
}
#endif
