#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\sys_line.h" /** ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ用ｽﾃｰﾀｽのﾋﾞｯﾄ定義 */
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\define\mem_def.h"
#if (PRO_DPRAM == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\unisw_a.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\cmn_def.h"
#include "\src\atlanta\sh7043\define\io_pro.h"
#include "\src\atlanta\define\sysprint.h"

#include "\src\memsw\define\mem_sw_b.h"
#include "\src\memsw\define\mems_pro.h"

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\mlt_data.h"
#include "\src\atlanta\ext_v\mlt_tbl.h"
#include "\src\atlanta\ext_v\fcm_data.h"

#if (PRO_MULTI_LINE == ENABLE)

/*UBYTE DBG_LineAttribute[9] = {0};*/	/* 1997/11/17 BOARD_MAX_MISS */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 本体内臓の回線が、標準ラインと拡張ラインがあるため拡張します by T.Soneoka 1997/11/21 */
UBYTE DBG_LineAttribute[SYS_OPTION_BOARD_MAX][INTERNAL_LINE_MAX] = {0};
#else
UBYTE DBG_LineAttribute[SYS_OPTION_BOARD_MAX] = {0};
#endif
UBYTE DBG_SourceAttribute = 0;
UBYTE DBG_Exist144Modems = 0;
UBYTE DBG_Exist288Modems = 0;
UBYTE DBG_Exist288ModemFirstPosition = 0;

/*************************************************************************
	module		:[オプションボード及び内臓モデム管理データの初期化]
	function	:[
		1.内臓モデムの有無及びオプション・ボード装着状態を下記データへ登録する。
			UWORD SYS_MachineStatus[SYS_OTHER_STATUS]
			UWORD SYS_OptionLineStatus[0]
	]
	return		:[無し]
	common		:[なし]
	condition	:[無し]
	comment		:[]
	machine		:[V53/SH]
	language	:[]
	keyword		:[288]
	date		:[1996/04/04]
	author		:[川崎真史]
*************************************************************************/
void MAN_InitilizeOptionBoard( void )
{
	SYS_MachineStatus[SYS_OTHER_STATUS] = 0;	/**  初期ｸﾘｱ */
	
	MAN_ConfirmOptionBoard();
	
#if (0)
** 	if (ExistOrangeModem()) { /** 標準モデム有りか */
** 		SYS_MachineStatus[SYS_OTHER_STATUS] |= (SYS_INTERNAL_MODEM+SYS_MODEM_144K);
** 	}
** 	else { /**  標準内臓モデム無し*/
** 		/** 内蔵モデムを使用できないようにする。 */
** 		SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_INTERNAL_MODEM+SYS_MODEM_144K);
** 
** #if (0)	/** T.B.D. By O.Kimoto 1996/11/18 **/
** 		if ((CHK_OptionLineExist(0) == 1) && (CHK_OptionLineError(0) == 0)) {
** 			SYS_OptionLineStatus[0] &= ~(SYS_OPTION_LINE_VALID); /** オプション・ボード０を無効にする */
** 			SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_EXTERNAL_MODEM; /** オプションボード０を本体モデムとして使用する */
** 			if (CHK_OptionLine288(0) == 1) {
** 				SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(SYS_MODEM_144K);
** 			}
** 		}
** 		else { /** モデムエラー（全てのモデム使用不可能） */
** 			/** １つも正常なモデムが存在しないことをエラー表示した方がいいと思う。 By O.Kimoto 1996/11/18 */
** 			SYS_MachineStatus[SYS_OTHER_STATUS] |= (SYS_MODEM_ERROR); /** 全てのモデムが使用不可能 */
** 		}
** #endif
** 
** 	}
#endif

	/* アトランタでは、モデムの種類がオレンジかＲ２８８Ｆの可能性がありますので
	** 以下のように変更します
	** By O.Kimoto 1997/06/14
	*/
	SYS_MachineStatus[SYS_OTHER_STATUS] &= ~(UWORD)(SYS_INTERNAL_MODEM+SYS_EXTERNAL_MODEM+SYS_MODEM_144K+SYS_MODEM_ERROR);
	switch(CMN_KinkOfModem()) {
	case CMN_ORANGE_MODEM:
#if (PRO_MODEM == R288F)				/* ROCKWELL製 28.8K */
		SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_MODEM_ERROR;
#endif
#if (PRO_MODEM == ORANGE3)
		SYS_MachineStatus[SYS_OTHER_STATUS] |= (SYS_INTERNAL_MODEM+SYS_MODEM_144K);
#endif
		break;
	case CMN_R288F_MODEM:
#if (PRO_MODEM == R288F)				/* ROCKWELL製 28.8K */
		SYS_MachineStatus[SYS_OTHER_STATUS] |= (SYS_INTERNAL_MODEM);
#endif
#if (PRO_MODEM == ORANGE3)
		SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_MODEM_ERROR;
#endif
		break;
	case CMN_NO_MODEM:
	default:
		SYS_MachineStatus[SYS_OTHER_STATUS] |= SYS_MODEM_ERROR;
		break;
	}
}


/*************************************************************************
	module		:[オプションボード管理データの初期化]
	function	:[
		1.オプション・ボード装着状態を下記データへ登録する。
			UWORD SYS_OptionLineStatus[0-7]
	]
	return		:[無し]
	common		:[なし]
	condition	:[無し]
	comment		:[]
	machine		:[V53/SH]
	language	:[]
	keyword		:[288]
	date		:[1996/04/04]
	author		:[川崎真史]
*************************************************************************/
void far MAN_ConfirmOptionBoard( void )
{
	UBYTE board_number;

	/*
	** オプション・ボード・ステータスをクリア
	*/
	for (board_number = 0; board_number < SYS_OPTION_BOARD_MAX; board_number++) {
		SYS_OptionLineStatus[board_number] = 0x0000;
	}
	
	for (board_number = 1; board_number < SYS_OPTION_BOARD_MAX; board_number++) {
		if (DPR_CheckOptionModemBoardExist((UWORD)(board_number-1))) { /** モデム・オプション・ボードが接続されているか？ */
			SYS_OptionLineStatus[board_number] |= (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID);
			if (DPR_CheckOption288ModemBoard((UWORD)(board_number-1))) { /** オプション・ボードは２８．８Ｋモデムか？ */
				SYS_OptionLineStatus[board_number] |= SYS_OPTION_SPEED_MAX_288;
			}

#if (0)	/* T.B.D. By O.Kimoto 1996/11/14 */
			if () { /** オプション・ボードの初期化エラー有り？ */
				SYS_OptionLineStatus[board_number] |= SYS_OPTION_LINE_ERROR;
			}
#endif

		}
		else {
			/*
			** ｵﾌﾟｼｮﾝﾎﾞｰﾄﾞ0番目で接続エラーが発生した場合、他のﾎﾞｰﾄﾞは
			** 全て動作できない。
			*/
			if (board_number == 0) {
				break; /** ｵﾌﾟｼｮﾝ･ﾎﾞｰﾄﾞ全て無し */
			}
		}
	}
}


/*************************************************************************
	module		:[オプションボードの未使用番号を返す]
	function	:[
		1.オプション・ボード装着状態を下記データへ登録する。
			UWORD SYS_OptionLineStatus[0-7]
	]
	return		:[0～(SYS_OPTION_BOARD_MAX-1) : 使用可能なオプションボード番号
				  SYS_OPTION_BOARD_MAX		   : オプションボード使用不可能
				 ]
	common		:[なし]
	condition	:[無し]
	comment		:[]
	machine		:[V53/SH]
	language	:[]
	keyword		:[288]
	date		:[1996/04/04]
	author		:[川崎真史]
*************************************************************************/
UBYTE far CHK_UnusedOptionLine( void )
{
	UBYTE board_number;
	
	for (board_number = 1; board_number < SYS_OPTION_BOARD_MAX; board_number++) {
		if (CHK_OptionLineExist( board_number ) == 1) { /** 指定されたオプション番号のボードがあるか？ */
			if ((CHK_OptionLineValid( board_number )) /** オプションラインとして有効か？ */
				&& (CHK_OptionLineError( board_number ) == 0) /** 初期化エラーがないか？ */
				&& (CHK_OptionPreLineBusy( board_number ) == 0) /** ＣＩ検出中でない */
				&& (CHK_OptionLineBusy( board_number ) == 0)) { /** 回線使用中でない */
					return ( board_number );
			}
		}
		else {
			if (board_number == 0) { /** オプションボードの一個目が接続されていない */
				return( SYS_OPTION_BOARD_MAX ); /** オプションボード無し */
			}
		}
	}
	return( SYS_OPTION_BOARD_MAX ); /** オプションボード無し */
}



/*************************************************************************
	module		:[指定したボードにＣＩ検出中をセット]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[void far SYS_SetOptionPreLineBusy(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
void far SYS_SetOptionPreLineBusy( UBYTE board_number )
{
	SYS_OptionLineStatus[ board_number ] |= SYS_OPTION_PRE_LINE_BUSY;
}


/*************************************************************************
	module		:[指定したボードに回線使用中をセットする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[void far SYS_SetOptionLineBusy(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
void far SYS_SetOptionLineBusy( UBYTE board_number )
{
	SYS_OptionLineStatus[ board_number ] &= ~(SYS_OPTION_PRE_LINE_BUSY);
	SYS_OptionLineStatus[ board_number ] |= SYS_OPTION_LINE_BUSY;
}


/*************************************************************************
	module		:[指定したボードの回線使用中をﾘｾｯﾄする。]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[void far SYS_ClearOptionLineBusy(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
void far SYS_ClearOptionLineBusy( UBYTE board_number )
{
	SYS_OptionLineStatus[ board_number ] &= ~(SYS_OPTION_LINE_BUSY);
}


/*************************************************************************
	module		:[指定したボードの停止要求ビットをリセットする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[void far SYS_ClearOptionLineStio(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
void far SYS_ClearOptionLineStop( UBYTE board_number )
{
	SYS_OptionLineStatus[ board_number ] &= ~(SYS_OPTION_STOP_FAXCOM);
}


/*************************************************************************
	module		:[ＰＢＸ－＞ＰＳＴＮ発呼指定があるかどうかのチェック]
	function	:[
		1.
	]
	return		:[
		INTERNEL_NUMBER		0	: 外線発呼用番号
		OTHER_NUMBER		1	: 内線発呼用番号
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[UBYTE far OPT_CheckPstnAccess(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_CheckPstnAccess(void)
{
	UBYTE count;
	
	for (count = 0; count < DIALING_NUMBER_MAX; count ++) {
		if (*(OPT_DialingNumber.Buffer+count) == '!') {
			if (*(OPT_DialingNumber.Buffer+count+1) == NULL) {
				return(INTERNAL_NUMBER);
			}
		}
		else if (*(OPT_DialingNumber.Buffer+count) == NULL) {
			break;
		}
	}
	return(OTHER_NUMBER);
}


/*************************************************************************
	module		:[実行すべきｷｭｰとｺﾏﾝﾄﾞﾌｧｲﾙを探す]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[UBYTE far OPT_GetQueueAndCommand(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_GetQueueAndCommand(void)
{
	
	UBYTE current_exe_que;
	UBYTE result;

	result = OK;

	current_exe_que = (UBYTE)SYB_ExecQueueSerchPoint;	/* NEW_JUDGE 1997/10/28 */
	/*current_exe_que = (UBYTE)GetNextExecNo();*/

	SYS_CurrentExecQueueNo = current_exe_que;

	OPT_QueueP = &SYB_ExecQueue[current_exe_que];	/** 発信スケジューラー ポインター */

	if ( OPT_QueueP->Kind == SYS_COMMAND_TRX ){								/** 通信予約による送受信 */
		OPT_CommandP			= &SYB_CommandFile[OPT_QueueP->Number.Command];	/** 通信予約番号 */
		OPT_CommandFileOptionItem	= OPT_CommandP->Option.Item;						/** 通信種別	 */
	}
#if (PRO_BATCH_TX == ENABLE)
	else if ( OPT_QueueP->Kind == SYS_BATCH_TX ){		/** 一括送信 */
		OPT_BatchP					= &SYB_BatchTxFile[OPT_QueueP->Number.Batch];	/** 通信予約番号 */
		OPT_CommandFileOptionItem	= SYS_BATCH_MEMORY_TX;	/** 一括送信 */												/** 通信種別	 */
	}
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	else if ( OPT_QueueP->Kind == SYS_CONTINUOUS_POLLING ){		/** 連続ポーリング */
		OPT_ContPollingP			= &SYB_ContinuousPolling;				/** 連続ポーリング受信ファイル */
		OPT_CommandFileOptionItem	= SYS_CONTINUOUS_POLLING_RX;			/** 連続ポーリング	 */	/** 通信種別	 */
	}
#endif
	else {
		/** ここに来るのはバグ ExecQueueのKindに変な値が入っている */
		result = NG;
	}
	return(result);
}


/*************************************************************************
	module		:[発呼すべき番号の属性をＧｅｔ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[UBYTE far OPT_GetAttribute(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_GetAttribute(void)
{
	UBYTE Ability0 = 0;				/* 属性 １ */
	UBYTE Ability1 = 0;				/* 属性 ２ */
	UBYTE Ability2 = 0;				/* 属性 ３ */
	UBYTE Ability3 = 0;				/* 属性 ４ */

	/* Ｑｕｅｕｅが掴んでいる宛先の属性取得 */
	/* Ｑｕｅｕｅが掴んでいる宛先の最高速度取得 */
	switch (OPT_QueueP->ExecDial.Item) {	/** ダイアル種別 */
	case SYS_SPEED_DIAL:
		Ability0 = SYB_SpeedDial[OPT_QueueP->ExecDial.ExecNumber.Speed].Attribute1;
		Ability1 = SYB_SpeedDial[OPT_QueueP->ExecDial.ExecNumber.Speed].Attribute2;
		Ability2 = SYB_SpeedDial[OPT_QueueP->ExecDial.ExecNumber.Speed].Attribute3;
		Ability3 = SYB_SpeedDial[OPT_QueueP->ExecDial.ExecNumber.Speed].Attribute4;
		break;
	case SYS_ONETOUCH_DIAL:
		Ability0 = SYB_OnetouchDial[OPT_QueueP->ExecDial.ExecNumber.Onetouch].Attribute1;
		Ability1 = SYB_OnetouchDial[OPT_QueueP->ExecDial.ExecNumber.Onetouch].Attribute2;
		Ability2 = SYB_OnetouchDial[OPT_QueueP->ExecDial.ExecNumber.Onetouch].Attribute3;
		Ability3 = SYB_OnetouchDial[OPT_QueueP->ExecDial.ExecNumber.Onetouch].Attribute4;
		break;
	default:
		Ability0 = SYS_MemorySwitch[MEMORY_SW_B0];
		Ability1 = SYS_MemorySwitch[MEMORY_SW_B1];
		Ability2 = SYS_MemorySwitch[MEMORY_SW_B2];
		Ability3 = SYS_MemorySwitch[MEMORY_SW_B3];
		break;
	}

	/* コマンドスキャナ送信時の属性 1997/01/27 Y.Murata */
	if (OPT_QueueP->Kind == SYS_COMMAND_TRX) {
		if (CheckScannerCommand(OPT_QueueP->Number.Command)) {
			SYS_ScannerTxAbility0 = Ability0;
			SYS_ScannerTxAbility1 = Ability1;
			SYS_ScannerTxAbility2 = Ability2;
			SYS_ScannerTxAbility3 = Ability3;
		}
	}
	SYS_WorkAbility0 = Ability0;
	SYS_WorkAbility1 = Ability1;
	SYS_WorkAbility2 = Ability2;
	SYS_WorkAbility3 = Ability3;

	return((UBYTE)(Ability3 & SPEED_HANDSHAKE_V8 ? V8_START_ENABLE : V8_START_DISABLE));
}



/*************************************************************************
	module		:[発呼すべき番号をＧｅｔ]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MAN]
	ProtoType	:[UBYTE far OPT_GetDialNumber(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_GetDialNumber(void)
{
	UBYTE result;
	
	result = OK;
	
	/* Ｑｕｅｕｅが掴んでいる宛先の電話番号取得 */
	switch (OPT_QueueP->ExecDial.Item) {	/** ダイアル種別判定 */
	case SYS_SPEED_DIAL	  :			/** 短縮ダイアル */
		if (OPT_QueueP->Status == SYS_EXEC_WAITING) {		/** 発信スケジューラ～実行中 */
			if (OPT_QueueP->ExecDial.ExecNumber.Speed < SYS_SPEED_DIAL_MAX) {	/** 第１短縮ダイアル */
				/** 第１短縮ダイアルの番号取得 */
				CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
						 (UBYTE far *)&SYB_SpeedDial[OPT_QueueP->ExecDial.ExecNumber.Speed].Dial);
			}
		}
#if !defined (KEISATSU) /* 05/04/12 石橋正和 */
		/* 転送先ダイアル 有り */
		else { /** 転送先ﾀﾞｲｱﾙ */
			CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
				 (UBYTE far *)&SYB_SubDial[SYB_SpeedDial[OPT_QueueP->ExecDial.ExecNumber.Speed].SubDialPosition][0]);
		}
#endif
		break;
	case SYS_ONETOUCH_DIAL:	/* ワンタッチ・ダイアル */
		if (OPT_QueueP->Status == SYS_EXEC_WAITING) {
			CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
				 (UBYTE far *)&SYB_OnetouchDial[OPT_QueueP->ExecDial.ExecNumber.Onetouch].Dial);
		}
#if !defined (KEISATSU) /* 05/04/12 石橋正和 */
		/* 転送先ダイアル 有り */
		else { /** 転送先ﾀﾞｲｱﾙ */
			CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
				 (UBYTE far *)&SYB_SubDial[SYB_OnetouchDial[OPT_QueueP->ExecDial.ExecNumber.Onetouch].SubDialPosition][0]);
		}
#endif
		break;
	case SYS_DIRECT_DIAL  :	/* 直接ダイアル */
		if ( OPT_QueueP->Kind == SYS_COMMAND_TRX ){								/** 通信予約による送受信 */
			CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
				 (UBYTE far *)&OPT_CommandP->DialNumber.Direct[OPT_QueueP->ExecDial.ExecNumber.Command]);
		}
#if (PRO_BATCH_TX == ENABLE)
		else if ( OPT_QueueP->Kind == SYS_BATCH_TX ){		/** 一括送信 */
			CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
				(UBYTE far *)&OPT_BatchP->DialNumber[OPT_QueueP->ExecDial.ExecNumber.Command].FaxNumber.Direct);		/** ダイレクトダイアルセーブ */
		}
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE)
		else if ( OPT_QueueP->Kind == SYS_CONTINUOUS_POLLING ){		/** 連続ポーリング */
			CMN_BCD_ToASC_String((UBYTE far *)&OPT_DialingNumber.Buffer ,
				(UBYTE far *)&OPT_ContPollingP->DialNumber.Direct[OPT_QueueP->ExecDial.ExecNumber.Command]);		/** ダイレクトダイアルセーブ */
		}
#endif
		break;
	default			  :
		/* ｾｯﾄ･ｴﾗｰ･ｺｰﾄﾞ　*/
		result = NG;
		break;
	}
	return(result);
}


/*************************************************************************
	module		:[送・受信専用設定チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[UBYTE far OPT_CheckExclusiveTxRx(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_CheckExclusiveTxRx(void)
{
	UBYTE line_count;
	UBYTE count;
	
	line_count = 0;

	/** 内蔵ラインの設定状況チェック */
	if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM) {
		/** 送・受信設定のチェック */
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
#if (0)	/* 見方間違えていた by T.Soneoka 1998/03/11 */
//		if (!(CHK_UNI_Line0_TxRx() & LINE0_RX_ONLY)) {
#endif
		if (!(CHK_UNI_Line0_TxRx() == EXCLUSIVE_RX)) {
			DBG_LineAttribute[0][0] |= OPT_TX_ENABLE;
			line_count ++;
		}
		if (!(CHK_UNI_Line_EXT_TxRx() & LINE0_RX_ONLY)) {
			DBG_LineAttribute[0][1] |= OPT_TX_ENABLE;
			line_count ++;
		}
#else
#if (0)	/* 見方間違えていた by T.Soneoka 1998/03/11 */
//		if (!(CHK_UNI_Line0_TxRx() & LINE0_RX_ONLY)) {
#endif
		if (!(CHK_UNI_Line0_TxRx() == EXCLUSIVE_RX)) {
			DBG_LineAttribute[0] |= OPT_TX_ENABLE;
			line_count ++;
		}
#endif
	}

	/* スキャナー送信は、基本的には第1回線しか仕様的にはありません。
	** しかし、技術的には可能なのでメモリスイッチの設定を見て動作を
	** 切り替えます。
	** by O.kimoto 1997/01/17
	*/
	if (line_count == 1) {	/** 内蔵モデムがあった ＝＞Ｆ－１２０ */
		if (OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo)) { /* スキャナ－・コマンドかを確認 */
			if (!CHK_UNI_OptionStxAvailable()) {	/** オプションボードでのスキャナー送信設定は？ */
				return(line_count);
			}
		}
		
	}

	/** 外付けラインの設定状況チェック */
	for (count = 1; count < SYS_OPTION_BOARD_MAX; count ++) {
		if ((SYS_OptionLineStatus[count] & (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) == (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) {
			/** 送・受信設定のチェック */
			if ((OPT_CHK_UNI_LineTxRx(count) != EXCLUSIVE_RX)) {
				line_count ++;
			}
			if ((OPT_CHK_UNI_LineTxRx(count) != EXCLUSIVE_RX)) {
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
				DBG_LineAttribute[count][0] |= OPT_TX_ENABLE;
#else
				DBG_LineAttribute[count] |= OPT_TX_ENABLE;
#endif
				line_count ++;
			}
		}

		/* スキャナー送信は、基本的には第1回線しか仕様的にはありません。
		** しかし、技術的には可能なのでメモリスイッチの設定を見て動作を
		** 切り替えます。
		** by O.kimoto 1997/01/17
		*/
		if (count == 1) {	/** 2回線目のモデムがあった ＝＞Ｆ－１５０ */
			if (OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo)) { /* スキャナ－・コマンドかを確認 */
				if (!CHK_UNI_OptionStxAvailable()) {	/** オプションボードでのスキャナー送信設定は？ */
					return(line_count);
				}
			}
			
		}

	}

	return(line_count);
}


/*************************************************************************
	module		:[回線のＰＢＸ／ＰＳＴＮ設定チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[void far OPT_CheckLineType(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
void far OPT_CheckLineType(void)
{
	UBYTE count;
	
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	/** 内蔵ラインの設定状況チェック */
	if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM) {
		/* 標準回線のPBX/PSTNのチェックをします */
		if (CHK_PBX()) {	/** ＰＢＸ */
			DBG_LineAttribute[0][0] |= OPT_PBX_ENABLE;
			
			if (SYB_PbxAccessNumber[0][0][0] != 0xff) {
				DBG_LineAttribute[0][0] |= OPT_PSTN_ACCESS_ENABLE;
			}
		}
		else {	/** ＰＳＴＮ */
			DBG_LineAttribute[0][0] |= OPT_PSTN_ENABLE;
			DBG_LineAttribute[0][0] |= OPT_PSTN_ACCESS_ENABLE;
		}
		/* 拡張回線のPBX/PSTNのチェックをします */
		if (CHK_PBX_EXT()) {
			DBG_LineAttribute[0][1] |= OPT_PBX_ENABLE;
			
			if (SYB_PbxAccessNumber[0][1][0] != 0xff) {
				DBG_LineAttribute[0][1] |= OPT_PSTN_ACCESS_ENABLE;
			}
		}
		else {	/** ＰＳＴＮ */
			DBG_LineAttribute[0][1] |= OPT_PSTN_ENABLE;
			DBG_LineAttribute[0][1] |= OPT_PSTN_ACCESS_ENABLE;
		}
	}
	/** 外付けラインの設定状況チェック */
	for (count = 1; count < SYS_OPTION_BOARD_MAX; count ++) {
		if ((SYS_OptionLineStatus[count] & (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) == (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) {
			/** ＰＢＸ／ＰＳＴＮのチェック */
			if (OPT_CHK_Pbx(count)) {	/** ＰＢＸ */
				DBG_LineAttribute[count][0] |= OPT_PBX_ENABLE;
				
				if (SYB_PbxAccessNumber[count][0][0] != 0xff) {
					DBG_LineAttribute[count][0] |= OPT_PSTN_ACCESS_ENABLE;
				}
			}
			else {	/** ＰＳＴＮ */
				DBG_LineAttribute[count][0] |= OPT_PSTN_ENABLE;
				DBG_LineAttribute[count][0] |= OPT_PSTN_ACCESS_ENABLE;
			}
		}
	}
#else
	/** 内蔵ラインの設定状況チェック */
	if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM) {
		/** ＰＢＸ／ＰＳＴＮのチェック */
		if (CHK_PBX()) {	/** ＰＢＸ */
			DBG_LineAttribute[0] |= OPT_PBX_ENABLE;
			
			if (SYB_PbxAccessNumber[0][0] != 0xff) {
				DBG_LineAttribute[0] |= OPT_PSTN_ACCESS_ENABLE;
			}
		}
		else {	/** ＰＳＴＮ */
			DBG_LineAttribute[0] |= OPT_PSTN_ENABLE;
			DBG_LineAttribute[0] |= OPT_PSTN_ACCESS_ENABLE;
		}
	}

	/** 外付けラインの設定状況チェック */
	for (count = 1; count < SYS_OPTION_BOARD_MAX; count ++) {
		if ((SYS_OptionLineStatus[count] & (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) == (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) {
			/** ＰＢＸ／ＰＳＴＮのチェック */
			if (OPT_CHK_Pbx(count)) {	/** ＰＢＸ */
				DBG_LineAttribute[count] |= OPT_PBX_ENABLE;
				
				if (SYB_PbxAccessNumber[count][0] != 0xff) {
					DBG_LineAttribute[count] |= OPT_PSTN_ACCESS_ENABLE;
				}
			}
			else {	/** ＰＳＴＮ */
				DBG_LineAttribute[count] |= OPT_PSTN_ENABLE;
				DBG_LineAttribute[count] |= OPT_PSTN_ACCESS_ENABLE;
			}
		}
	}
#endif
}


/*************************************************************************
	module		:[送・受信専用設定チェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[vois far OPT_CheckV34ModemExist(void){}]
	date		:[1996/12/02]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_CheckV34ModemExist(void)
{
	UBYTE count;
	UBYTE count2;

	count = 0;
	DBG_Exist144Modems = 0;
	DBG_Exist288Modems = 0;
	DBG_Exist288ModemFirstPosition = 0xff;

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	/** 内蔵ラインの設定状況チェック */
	if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM) {
		DBG_LineAttribute[0][0] |= OPT_144_ENABLE;
		DBG_LineAttribute[0][1] |= OPT_144_ENABLE;
		DBG_Exist144Modems ++;

		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_MODEM_144K) == 0) {	/* if R288F */
			DBG_LineAttribute[0][0] |= OPT_288_ENABLE;
			DBG_LineAttribute[0][1] |= OPT_288_ENABLE;
			DBG_Exist288Modems++;
			DBG_Exist288ModemFirstPosition = 0;
		}
		count ++;	/* Add By O.Kimoto 1997/03/04 */
	}
	/** 外付けラインの設定状況チェック */
	for (count2 = 1; count2 < SYS_OPTION_BOARD_MAX; count2 ++) {
		if ((SYS_OptionLineStatus[count2] & (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) == (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) {
			DBG_LineAttribute[count2][0] |= OPT_144_ENABLE;
			DBG_Exist144Modems ++;
			count ++;	/* 下記から移動 By O.Kimoto 1997/03/04 */
			if (CHK_OptionLine288(count2)) {
				DBG_LineAttribute[count2][0] |= OPT_288_ENABLE;
				DBG_Exist288Modems++;
				/** count ++; 上記へ移動 By O.Kimoto 1997/03/04 */
				if (DBG_Exist288ModemFirstPosition == 0xff) {
					DBG_Exist288ModemFirstPosition = count2;
				}
			}
		}
	}
	return(count);
#else
	/** 内蔵ラインの設定状況チェック */
	if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM) {
		DBG_LineAttribute[0] |= OPT_144_ENABLE;
		DBG_Exist144Modems ++;

		if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_MODEM_144K) == 0) {	/* if R288F */
			DBG_LineAttribute[0] |= OPT_288_ENABLE;
			DBG_Exist288Modems++;
			DBG_Exist288ModemFirstPosition = 0;
		}
		count ++;	/* Add By O.Kimoto 1997/03/04 */
	}

	/** 外付けラインの設定状況チェック */
	for (count2 = 1; count2 < SYS_OPTION_BOARD_MAX; count2 ++) {
		if ((SYS_OptionLineStatus[count2] & (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) == (SYS_OPTION_LINE_EXIST + SYS_OPTION_LINE_VALID)) {
			DBG_LineAttribute[count2] |= OPT_144_ENABLE;
			DBG_Exist144Modems ++;
			count ++;	/* 下記から移動 By O.Kimoto 1997/03/04 */
			if (CHK_OptionLine288(count2)) {
				DBG_LineAttribute[count2] |= OPT_288_ENABLE;
				DBG_Exist288Modems++;
				/** count ++; 上記へ移動 By O.Kimoto 1997/03/04 */
				if (DBG_Exist288ModemFirstPosition == 0xff) {
					DBG_Exist288ModemFirstPosition = count2;
				}
			}
		}
	}
	return(count);
#endif
}


/*************************************************************************
	module		:[]
	function	:[
		1.
	]
	return		:[
		０～８	： 発呼するべき回線が存在した。但し、最上位ビットは、内線専用発呼かどうかの設定を
		           するために使用します。（１：内線専用番号、０：その他）
		０ｘＦＦ： 最終的に発呼すべき回線が存在しなかった。
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[CMN]
	ProtoType	:[void far OPT_JudgeSelectLine2(void){}]
	date		:[]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_JudgeSelectLine(void)
{
	UBYTE result;
	UBYTE dial_kind;	/** PSTN / PBX/PSB->PSTN */
	UBYTE modem_type;	/** V.34 / under V.17 */
	UBYTE direction;	/** 1st Line to 8th Line / 8th Line to 1st Line */
	UBYTE count;
	UBYTE wait_line;
	UBYTE mask_value;
	UBYTE error_line_number;
	UBYTE decided_line_number;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	UBYTE internal_line_cnt;
	UBYTE rx_enable;
#endif

	DBG_SourceAttribute = 0;
	wait_line = 0xff;
	error_line_number = 0xff;

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	for (internal_line_cnt = 0; internal_line_cnt < INTERNAL_LINE_MAX; internal_line_cnt++) {
		for(count = 0; count < (SYS_OPTION_BOARD_MAX);count ++) {
			DBG_LineAttribute[count][internal_line_cnt] = 0;
		}
	}
#else
	for(count = 0; count < (SYS_OPTION_BOARD_MAX);count ++) {	/* 1997/11/17 BOARD_MAX_MISS */
		DBG_LineAttribute[count] = 0;
	}
#endif

	/*
	** まず、コマンドファイル及びキューから得られる情報を集める。
	*/
	result = OPT_GetQueueAndCommand();	/** 実行すべきキューとコマンドファイルの取得 */

	if (SYS_CurrentExecQueueNo != SYS_EXEC_QUEUE_MAX) {	/** キューが存在した */
		result = OPT_GetDialNumber();	/** 発呼すべき番号の取得 */

		modem_type = OPT_GetAttribute();	/** 発呼すべき番号が持っている属性の取得 */
		
		dial_kind = OPT_CheckPstnAccess();	/** 発呼すべき番号の種類を判断（ＰＳＴＮ ｏｒ ＰＢＸ－＞ＰＳＴＮ／ＰＢＸ専用） */

		/* 
		** 次に機器の設定状態から得られる情報を集める。
		*/
		OPT_CheckLineType();	/** ＰＢＸ／ＰＳＴＮの設定 */

		/*
		** 接続されているモデムの種類（１４．４／２８．８）
		*/
		result = OPT_CheckV34ModemExist();

		/* もしF-120 1回線仕様かF-150 1回線仕様ならば回線選択は不可能なので
		** 強制的に最初に見つかったモデムで発呼するものとします。
		** その場合、PSTN Access Numberの発呼をするとF-120のベース仕様と
		** 動作が異なるので、ここでの指示は内線番号という風にします。
		** By O.Kimoto 1997/01/27
		*/
#if (0)
		if (result == 1) {	/** モデムが１つしかない？ */
			if (DBG_Exist144Modems == 1) {
				if (DBG_Exist288Modems == 0) {
					/** F-120 1回線仕様 */
					return((UBYTE)(SYS_SEND_INTERNAL_LINE | INTERNAL_NUMBER));
				}
				else if (DBG_Exist288Modems == 1) {
					/** F-150 1回線仕様 */
					return((UBYTE)(DBG_Exist288ModemFirstPosition | INTERNAL_NUMBER));
				}
			}
		}
#endif

		/* 第1回線が話中時のスキャナー送信の対応ができていなかったため
		** by O.Kimoto 1997/03/07
		*/
		if (result == 0) {
			/** 発呼出来る回線が１つもなかった　－＞Ｄ．０．１０ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
			/*
			** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
			** Mode init in nomal.
			*/
			OPT_QueueP->StartTime = SYB_CurrentTime;
			OPT_QueueP->TotalTime = 0;
			OPT_QueueP->StackNumber = 0xFF;
#endif
			OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
			OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
			return(0xff);
		}
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
		else {
#if (0) /* Changed by H.Kubo 1998/03/12 */
@@			if (OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo)) { /* スキャナ－・コマンドかを確認 */
@@				if (!CHK_UNI_OptionStxAvailable()) {	/** オプションボードでのスキャナー送信設定は？ */
#else
			if ( ( OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo) 		/* スキャナ－・コマンドかを確認 */
					&& !CHK_UNI_OptionStxAvailable()  ) 						/** オプションボードでのスキャナー送信設定は？ */
#if (PRO_RELAYED_REPORT == ENABLE) /* Added by H.Kubo 1998/03/12 */
			|| OPT_CheckRlyTxRptCommandFromQue(SYS_CurrentExecQueueNo) 			/** 不達通知か？ */
#endif
				) {	
#endif
					/*
					** まず、内蔵回線（標準／拡張回線）の中に送信可能な回線があるかどうかチェックします
					*/
					for (internal_line_cnt = 0; internal_line_cnt < INTERNAL_LINE_MAX; internal_line_cnt++) {
						if (internal_line_cnt == 0) {
							rx_enable = OPT_CHK_UNI_LineTxRx(0);
						}
						else {
							rx_enable = CHK_UNI_Line_EXT_TxRx();
						}
						if (!(rx_enable == EXCLUSIVE_RX)) {
							break;
						}
					}
					/* 結果チェック */
					if (internal_line_cnt >= INTERNAL_LINE_MAX) {
						/** 発呼出来る回線が１つもなかった　－＞Ｄ．０．１０ */
						OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
						OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
						return(0xff);
					}
					/*
					** 送信可能な回線がある場合
					** 今送信しようとしてるダイヤル番号と各回線の設定状況にあう回線があるかどうかチェックします
					*/
					for (internal_line_cnt = 0; internal_line_cnt < INTERNAL_LINE_MAX; internal_line_cnt++) {
						if (internal_line_cnt == 0) {
							rx_enable = OPT_CHK_UNI_LineTxRx(0);
						}
						else {
							rx_enable = CHK_UNI_Line_EXT_TxRx();
						}
						if (!(rx_enable == EXCLUSIVE_RX)) {
							if ((DBG_LineAttribute[0][internal_line_cnt] & OPT_PBX_ENABLE)
							&& (dial_kind == INTERNAL_NUMBER)) {
								if (CMN_CheckTwiceLineEnable(internal_line_cnt)) {
									SYS_InternalLineNumber = internal_line_cnt;
									return((UBYTE)(SYS_SEND_INTERNAL_LINE | dial_kind));
								}
								else {
									wait_line = 0;	/* 内蔵回線ウェイト */
								}
							}
							if ((DBG_LineAttribute[0][internal_line_cnt] & OPT_PSTN_ACCESS_ENABLE)
							&& (dial_kind == OTHER_NUMBER)) {
								if (CMN_CheckTwiceLineEnable(internal_line_cnt)) {
									SYS_InternalLineNumber = internal_line_cnt;
									return((UBYTE)(SYS_SEND_INTERNAL_LINE | dial_kind));
								}
								else {
									wait_line = 0;	/* 内蔵回線ウェイト */
								}
							}
						}
					}
					/*
					** ここにきたときは、回線空き状態待ちか各回線の設定状況にあう回線がない場合です
					*/
					if (wait_line == 0xff) {
						if (dial_kind == INTERNAL_NUMBER) {
							/** 番号：内線専用、回線設定：外線設定の為、発呼出来ず－＞Ｄ．０．１２ */
							OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000C);				/** 交信結果 */
						}
						else {
							/** 番号：外線専用、回線設定：内線設定の為、発呼出来ず－＞Ｄ．０．１３ */
							OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000D);				/** 交信結果 */
						}
						OPT_QueueP->Status = SYS_EXEC_ERROR;	/** エラー終了 */
						OPT_QueueP->StackNumber = error_line_number;
						return(0xff);
					}

					/* 内蔵回線で更新中のスキャナー送信を実行すると、外付け回線で実行
					** されてしまう。
					** QAT不具合 D71-119
					** by O.Kimoto 1998/09/11
					*/
					else {
						return(0xff);
					}

				}
#if (0) /* H.Kubo 1998/03/12 */
@@			}
#endif
		}
#else
		else if (result == 1) {	/** モデムが１つしかない？ */
			if (DBG_Exist144Modems == 1) {
				if (DBG_Exist288Modems == 0) {
					/** F-120 1回線仕様 */
					return((UBYTE)(SYS_SEND_INTERNAL_LINE | INTERNAL_NUMBER));
				}
				else if (DBG_Exist288Modems == 1) {
					/** F-150 1回線仕様 */
					return((UBYTE)(DBG_Exist288ModemFirstPosition | INTERNAL_NUMBER));
				}
			}
		}
		else {	/** モデムが２個以上あった */
			if (OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo)) { /* スキャナ－・コマンドかを確認 */
				if (!CHK_UNI_OptionStxAvailable()) {	/** オプションボードでのスキャナー送信設定は？ */
					/* ということはスキャナー送信は第１回線のみ */
					if ((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM) {

						if (CMN_CheckLineEnable()) {	/* add if() NEW_JUDGE 1997/10/31 */
							/* F-120です */
							if ( OPT_CHK_UNI_LineTxRx(0) == EXCLUSIVE_RX ) {
								/** 発呼出来る回線が１つもなかった　－＞Ｄ．０．１０ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
								/*
								** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
								** Mode init in nomal.
								*/
								OPT_QueueP->StartTime = SYB_CurrentTime;
								OPT_QueueP->TotalTime = 0;
								OPT_QueueP->StackNumber = 0xFF;
#endif
								OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
								OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
								return(0xff);
							}
							else {
#if (0)	/** BUG by O.Kimoto 1997/07/09 */
**								return((UBYTE)(SYS_SEND_INTERNAL_LINE | INTERNAL_NUMBER));
#endif

								if (dial_kind == INTERNAL_NUMBER) {
									if (DBG_LineAttribute[0] & OPT_PBX_ENABLE) {
										/** やっと発呼する回線番号が決まった。！ */
										return((UBYTE)(SYS_SEND_INTERNAL_LINE | dial_kind));
									}
									else {
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
										/*
										** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
										** Mode init in nomal.
										*/
										OPT_QueueP->StartTime = SYB_CurrentTime;
										OPT_QueueP->TotalTime = 0;
										OPT_QueueP->StackNumber = 0xFF;
#endif
										OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
										OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
										return(0xff);
									}
								}
								else {
									if (DBG_LineAttribute[0] & OPT_PSTN_ACCESS_ENABLE) {
										/** やっと発呼する回線番号が決まった。！ */
										return((UBYTE)(SYS_SEND_INTERNAL_LINE | dial_kind));
									}
									else {
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
										/*
										** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
										** Mode init in nomal.
										*/
										OPT_QueueP->StartTime = SYB_CurrentTime;
										OPT_QueueP->TotalTime = 0;
										OPT_QueueP->StackNumber = 0xFF;
#endif
										OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
										OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
										return(0xff);
									}
								}
							}
						}
						/* 2000/1/21 Y.Murata 以下else{}分追加 NEW_JUDGE_BUG */
						else {
							if ( OPT_CHK_UNI_LineTxRx(0) == EXCLUSIVE_RX ) {
								/** 発呼出来る回線が１つもなかった　－＞Ｄ．０．１０ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
								/*
								** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
								** Mode init in nomal.
								*/
								OPT_QueueP->StartTime = SYB_CurrentTime;
								OPT_QueueP->TotalTime = 0;
								OPT_QueueP->StackNumber = 0xFF;
#endif
								OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
								OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
								return(0xff);
							}
							else {
								if (dial_kind == INTERNAL_NUMBER) {
									if (DBG_LineAttribute[0] & OPT_PBX_ENABLE) {
										;
									}
									else {
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
										/*
										** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
										** Mode init in nomal.
										*/
										OPT_QueueP->StartTime = SYB_CurrentTime;
										OPT_QueueP->TotalTime = 0;
										OPT_QueueP->StackNumber = 0xFF;
#endif
										OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
										OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
										return(0xff);
									}
								}
								else {
									if (DBG_LineAttribute[0] & OPT_PSTN_ACCESS_ENABLE) {
										;
									}
									else {
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
										/*
										** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
										** Mode init in nomal.
										*/
										OPT_QueueP->StartTime = SYB_CurrentTime;
										OPT_QueueP->TotalTime = 0;
										OPT_QueueP->StackNumber = 0xFF;
#endif
										OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
										OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
										return(0xff);
									}
								}
							}
						}

					}
					else {

						if (OPT_CHK_SelecetedLineEnable(1)) {	/* add if() NEW_JUDGE 1997/10/31 */
							/* F-150です */
							if ((OPT_CHK_UNI_LineTxRx(DBG_Exist288ModemFirstPosition) == EXCLUSIVE_RX)) {
								/** 発呼出来る回線が１つもなかった　－＞Ｄ．０．１０ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
								/*
								** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
								** Mode init in nomal.
								*/
								OPT_QueueP->StartTime = SYB_CurrentTime;
								OPT_QueueP->TotalTime = 0;
								OPT_QueueP->StackNumber = 0xFF;
#endif
								OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
								OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
								return(0xff);
							}
							else {
#if (0)	/** BUG by O.Kimoto 1997/07/09 */
**								return((UBYTE)(DBG_Exist288ModemFirstPosition | INTERNAL_NUMBER));
#endif

								if (dial_kind == INTERNAL_NUMBER) {
									if (DBG_LineAttribute[DBG_Exist288ModemFirstPosition] & OPT_PBX_ENABLE) {
										/** やっと発呼する回線番号が決まった。！ */
										return((UBYTE)(DBG_Exist288ModemFirstPosition | dial_kind));
									}
									else {
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
										/*
										** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
										** Mode init in nomal.
										*/
										OPT_QueueP->StartTime = SYB_CurrentTime;
										OPT_QueueP->TotalTime = 0;
										OPT_QueueP->StackNumber = 0xFF;
#endif
										OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
										OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
										return(0xff);
									}
								}
								else {
									if (DBG_LineAttribute[DBG_Exist288ModemFirstPosition] & OPT_PSTN_ACCESS_ENABLE) {
										/** やっと発呼する回線番号が決まった。！ */
										return((UBYTE)(DBG_Exist288ModemFirstPosition | dial_kind));
									}
									else {
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
										/*
										** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
										** Mode init in nomal.
										*/
										OPT_QueueP->StartTime = SYB_CurrentTime;
										OPT_QueueP->TotalTime = 0;
										OPT_QueueP->StackNumber = 0xFF;
#endif
										OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
										OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
										return(0xff);
									}
								}
							}
						}

					}
				}
			}

		}
#endif

		result = OPT_CheckExclusiveTxRx();	/** 送・受信専用設定 */

		if (result == 0) {
			/** 発呼出来る回線が１つもなかった　－＞Ｄ．０．１０ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
			/*
			** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
			** Mode init in nomal.
			*/
			OPT_QueueP->StartTime = SYB_CurrentTime;
			OPT_QueueP->TotalTime = 0;
			OPT_QueueP->StackNumber = 0xFF;
#endif
			OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000A);				/** 交信結果 */
			OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
			return(0xff);
		}
		else {
			/** 取あえず発呼出来る回線が１つは存在した */
			if(modem_type == V8_START_ENABLE) {/** 今から発呼する番号はＧ３／スーパーＧ３　？ */

				/** スーパーＧ３でした。 */
				if (DBG_Exist288Modems == 0) {	/** Ｖ．３４モデムボードはある？ */
					if (!(CHK_UNI_SwitchV17Line()) /** Ｖ．１７回線に切り替える？ */
						&& (!OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo))) { /* スキャナ－・コマンドかを確認 */

						/** スーパーＧ３で発呼する為の回線が１つも無い　－＞Ｄ．０．１１ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
						/*
						** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
						** Mode init in nomal.
						*/
						OPT_QueueP->StartTime = SYB_CurrentTime;
						OPT_QueueP->TotalTime = 0;
						OPT_QueueP->StackNumber = 0xFF;
#endif
						OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000B);				/** 交信結果 */
						OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
						return(0xff);
					}
					else {
						/** Ｖ．１７以下に切り替えます */
						mask_value = (OPT_TX_ENABLE + OPT_144_ENABLE);
					}
				}
				else {
					if (((SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) == SYS_INTERNAL_MODEM)
						&& (OPT_CheckScannerCommandFromQue(SYS_CurrentExecQueueNo))) { /* スキャナ－・コマンドかを確認 */

						if (!CHK_UNI_OptionStxAvailable()) {	/** オプションボードでのスキャナー送信設定は？ */
							/** Ｖ．１７以下に切り替えます */
							mask_value = (OPT_TX_ENABLE + OPT_144_ENABLE);
						}
						else {
							mask_value = (OPT_TX_ENABLE + OPT_288_ENABLE);
						}
					}
					else {
						mask_value = (OPT_TX_ENABLE + OPT_288_ENABLE);
					}
				}
			}
			else {
				/** Ｇ３でした */
				mask_value = (OPT_TX_ENABLE + OPT_144_ENABLE);
			}

			if(CHK_UNI_PriorityDirection() == OUTWARD_DIRECTION) {/** 回線の優先順位は？ */
				direction = OUTWARD;	/** １ＳＴラインからでした。 */
			}
			else{
				direction = INWARD;	/** ８ＴＨラインからでした。 */
			}

			decided_line_number = OPT_DecideLineNumber(mask_value, dial_kind, direction, &wait_line, &error_line_number);
			
			if (decided_line_number != 0xff) {
#if (PRO_RELAYED_REPORT == ENABLE) /* Added by H.Kubo 1998/03/12 */
				if  (OPT_CheckRlyTxRptCommandFromQue(SYS_CurrentExecQueueNo) && (decided_line_number != 0)) { 	/** 不達通知か？ */
					return (0xFF);
				}
#endif
				return((UBYTE)(decided_line_number));
			}
			else {
				if ((mask_value == (OPT_TX_ENABLE + OPT_288_ENABLE)) && (CHK_UNI_SwitchV17Line())) { /** Ｖ．１７回線に切り替える？ */
					mask_value = (OPT_TX_ENABLE + OPT_144_ENABLE);
					wait_line = 0xff;
					error_line_number = 0xff;
					decided_line_number = OPT_DecideLineNumber(mask_value, dial_kind, direction, &wait_line, &error_line_number);

					if (decided_line_number != 0xff) {
#if (PRO_RELAYED_REPORT == ENABLE) /* Added by H.Kubo 1998/03/12 */
						if  (OPT_CheckRlyTxRptCommandFromQue(SYS_CurrentExecQueueNo) && (decided_line_number != 0)) { 	/** 不達通知か？ */
							return (0xFF);
						}
#endif
						return((UBYTE)(decided_line_number));
					}
				}

				/** 最終的に発呼出来る回線が見つからなかった。 */
				if (wait_line != 0xff) {
					return(0xFF);	/* Change wait_line to 0xFF By O.Kimoto 1997/01/30 */
				}
				if (dial_kind == INTERNAL_NUMBER) {
					/** 番号：内線専用、回線設定：外線設定の為、発呼出来ず－＞Ｄ．０．１２ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
					/*
					** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
					** Mode init in nomal.
					*/
					OPT_QueueP->StartTime = SYB_CurrentTime;
					OPT_QueueP->TotalTime = 0;
#endif
					OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000C);				/** 交信結果 */
					OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
					OPT_QueueP->StackNumber = error_line_number;
					return(0xFF);
				}
				else if (dial_kind == OTHER_NUMBER) {
					/** 番号：外線専用、回線設定：内線設定の為、発呼出来ず－＞Ｄ．０．１３ */
#if (PRO_NEW_TX_CONF == ENABLE)	/* 2000.2.9 K.Kawata */
					/*
					** Set Start time & Total time & Stack number by H.Hirao 2000/02/07
					** Mode init in nomal.
					*/
					OPT_QueueP->StartTime = SYB_CurrentTime;
					OPT_QueueP->TotalTime = 0;
#endif
					OPT_QueueP->Result = (UWORD)(DIALERROR | 0x000D);				/** 交信結果 */
					OPT_QueueP->Status = SYS_EXEC_ERROR;			/** エラー終了 */
					OPT_QueueP->StackNumber = error_line_number;
					return(0xFF);
				}
			}
		}
	}
	else {
		return(0xF0);	/** キューが存在しませんでした。 */
	}
}



/*************************************************************************
	module		:[回線を決定する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[UBYTE far OPT_DecideLineNumber(UBYTE){}]
	date		:[1997/01/30]
	author		:[木元修]
*************************************************************************/
UBYTE far OPT_DecideLineNumber(
	UBYTE mask_value,
	UBYTE dial_kind,
	UBYTE direction,
	UBYTE *wait_line,
	UBYTE *error_line_number
	)
{
	UBYTE sub_count;
	UBYTE count;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	UBYTE internal_line_cnt;
#endif

	*wait_line = 0xff;
	*error_line_number = 0xff;

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	for (count = 0; count < (SYS_OPTION_BOARD_MAX) ; count ++) {	/* 1997/11/17 BOARD_MAX_MISS */
		sub_count = MLT_SelectLineTable[direction][count];
		/* 内蔵回線(標準／拡張回線）のチェック */
		if (sub_count == 0) {
			for (internal_line_cnt = 0; internal_line_cnt < INTERNAL_LINE_MAX; internal_line_cnt++) {
				if ((DBG_LineAttribute[sub_count][internal_line_cnt] & mask_value) == mask_value) {
					if (dial_kind == INTERNAL_NUMBER) {
						if (DBG_LineAttribute[sub_count][internal_line_cnt] & OPT_PBX_ENABLE) {
							if (CMN_CheckTwiceLineEnable(internal_line_cnt)) {
								SYS_InternalLineNumber = internal_line_cnt;	/**	標準ライン／拡張ラインをセット	*/
								return((UBYTE)(sub_count | dial_kind));
							}
							else {
								if (*wait_line == 0xff) {
									*wait_line = sub_count;
								}
							}
						}
						else {
							if (*error_line_number == 0xff) {
								*error_line_number = sub_count;
							}
						}
					}
					else {
						if (DBG_LineAttribute[sub_count][internal_line_cnt] & OPT_PSTN_ACCESS_ENABLE) {
							if (CMN_CheckTwiceLineEnable(internal_line_cnt)) {
								SYS_InternalLineNumber = internal_line_cnt;	/**	標準ライン／拡張ラインをセット	*/
								return((UBYTE)(sub_count | dial_kind));
							}
							else {
								if (*wait_line == 0xff) {
									*wait_line = sub_count;
								}
							}
						}
						else {
							if (*error_line_number == 0xff) {
								*error_line_number = sub_count;
							}
						}
					}
				}
			}
		}
		/* オプション回線のチェック */
		else {
			internal_line_cnt = 0;
			if ((DBG_LineAttribute[sub_count][internal_line_cnt] & mask_value) == mask_value) {
				if (dial_kind == INTERNAL_NUMBER) {
					if (DBG_LineAttribute[sub_count][internal_line_cnt] & OPT_PBX_ENABLE) {
						if (OPT_CHK_SelecetedLineEnable(sub_count) == TRUE) {
							/** やっと発呼する回線番号が決まった。！ */
							return((UBYTE)(sub_count | dial_kind));
						}
						else {
							if (*wait_line == 0xff) {
								*wait_line = sub_count;
							}
						}
					}
					else {
						if (*error_line_number == 0xff) {
							*error_line_number = sub_count;
						}
					}
				}
				else {
					if (DBG_LineAttribute[sub_count][internal_line_cnt] & OPT_PSTN_ACCESS_ENABLE) {
						if (OPT_CHK_SelecetedLineEnable(sub_count) == TRUE) {
							/** やっと発呼する回線番号が決まった。！ */
							return((UBYTE)(sub_count | dial_kind));
						}
						else {
							if (*wait_line == 0xff) {
								*wait_line = sub_count;
							}
						}
					}
					else {
						if (*error_line_number == 0xff) {
							*error_line_number = sub_count;
						}
					}
				}
			}
		}
	}
	return((UBYTE)(0xff));
#else
	for (count = 0; count < (SYS_OPTION_BOARD_MAX) ; count ++) {	/* 1997/11/17 BOARD_MAX_MISS */
		sub_count = MLT_SelectLineTable[direction][count];
		if ((DBG_LineAttribute[sub_count] & mask_value) == mask_value) {
			if (dial_kind == INTERNAL_NUMBER) {
				if (DBG_LineAttribute[sub_count] & OPT_PBX_ENABLE) {
					if (OPT_CHK_SelecetedLineEnable(sub_count) == TRUE) {
						/** やっと発呼する回線番号が決まった。！ */
						return((UBYTE)(sub_count | dial_kind));
					}
					else {
						if (*wait_line == 0xff) {
							*wait_line = sub_count;
						}
					}
				}
				else {
					if (*error_line_number == 0xff) {
						*error_line_number = sub_count;
					}
				}
			}
			else {
				if (DBG_LineAttribute[sub_count] & OPT_PSTN_ACCESS_ENABLE) {
					if (OPT_CHK_SelecetedLineEnable(sub_count) == TRUE) {
						/** やっと発呼する回線番号が決まった。！ */
						return((UBYTE)(sub_count | dial_kind));
					}
					else {
						if (*wait_line == 0xff) {
							*wait_line = sub_count;
						}
					}
				}
				else {
					if (*error_line_number == 0xff) {
						*error_line_number = sub_count;
					}
				}
			}
		}
	}
	return((UBYTE)(0xff));
#endif
}

#endif	/* End of Multi_line */

/*************************************************************************
	module		:[モデムボードがあるかどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[UWORD CHK_OptionLineExist(UBYTE board_number)]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
UWORD far CHK_OptionLineExist( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_LINE_EXIST );
}


/*************************************************************************
	module		:[オプションモデムボードが回線使用中かどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[UWORD far CHK_OptionLineBusy(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
UWORD far CHK_OptionLineBusy( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_LINE_BUSY );
}

/*************************************************************************
	module		:[指定したボードに停止要求ビットをセットする]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[void far SYS_OptionLineStop(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
void far SYS_OptionLineStop( UBYTE board_number )
{
	SYS_OptionLineStatus[ board_number ] |= SYS_OPTION_STOP_FAXCOM;
}

/*************************************************************************
	module		:[指定されたボードで通信可能かどうかを返す]
	function	:[
		1.オプション・ボード装着状態を下記データへ登録する。
			UWORD SYS_OptionLineStatus[0-7]
	]
	return		:[0～(SYS_OPTION_BOARD_MAX-1) : 使用可能なオプションボード番号
				  SYS_OPTION_BOARD_MAX		   : オプションボード使用不可能
				 ]
	common		:[なし]
	condition	:[無し]
	comment		:[]
	machine		:[V53/SH]
	language	:[]
	keyword		:[288]
	date		:[1996/04/04]
	author		:[川崎真史]
*************************************************************************/
UBYTE far CHK_SelectedLineEnable( UBYTE board_number )
{
	UBYTE i;

	/* 第１回線がリモート診断中は送信を拒否します。
	** by O.Kimoto 1997/02/24
	*/
	if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) {	/* 内臓モデムがある */
		if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
			if (FinalRxMode == DIAGMODE) {
				return(FALSE);
			}
		}
	}
	for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {		/* 第１回線目かどうか */
		if (CHK_OptionLineBusy((UBYTE)i)) {
			if (SYS_Opt[i].FinalRxMode == DIAGMODE) {
				return(FALSE);
			}
		}
	}

	if (CHK_OptionLineExist( board_number ) == 1) { /** 指定されたオプション番号のボードがあるか？ */
		if ((CHK_OptionLineValid( board_number )) /** オプションラインとして有効か？ */
			&& (CHK_OptionLineError( board_number ) == 0) /** 初期化エラーがないか？ */
			&& (CHK_OptionTelephoneUse( board_number ) == 0) /** 受話器使用中でないか？ 1997/01/29 Y.Murata */
			&& (CHK_OptionPreLineBusy( board_number ) == 0) /** ＣＩ検出中でない */
			&& (CHK_OptionLineBusy( board_number ) == 0)) { /** 回線使用中でない */

#if (PRO_CLASS1 == ENABLE)	/** Add Class1 By O.kimoto 1997/05/28 */
	#if (PRO_CLASS1_VIA_DPRAM == ENABLE)
			if (board_number == SYS_SEND_1ST_LINE) {
				/* D65B-010 By O.Kimoto 1997/06/18 */
				if ((SYS_OptionLineStatus[board_number] & SYS_OPTION_FAXMODEM) == SYS_OPTION_FAXMODEM) {
					return(FALSE);
				}
			}
	#endif
#endif

			return ( TRUE );
		}
	}
	return(FALSE);
}

/*************************************************************************
	module		:[オプションモデムボードが２８．８ｋかどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[UWORD CHK_OptionLine288(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
UWORD far CHK_OptionLine288( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_SPEED_MAX_288 );
}


/*************************************************************************
	module		:[オプションモデムボードがＣＩ検出中かどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[UWORD far CHK_OptionPreLineBusy(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
UWORD far CHK_OptionPreLineBusy( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_PRE_LINE_BUSY );
}


/*************************************************************************
	module		:[オプションボードの初期化不良の有無のチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[UWORD far CHK_OptionLineError(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
UWORD far CHK_OptionLineError( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_LINE_ERROR );
}


/*************************************************************************
	module		:[オプションボードとして有効かどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	ProtoType	:[UWORD far CHK_OptionLineValid(UBYTE board_number){}]
	date		:[1996/11/14]
	author		:[木元修]
*************************************************************************/
UWORD far CHK_OptionLineValid( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_LINE_VALID );
}


/*************************************************************************
	module		:[受話器使用中かどうかのチェック]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[288]
	date		:[1997/01/29]
	author		:[村田]
*************************************************************************/
UWORD far CHK_OptionTelephoneUse( UBYTE board_number )
{
	return( SYS_OptionLineStatus[ board_number ] & SYS_OPTION_TELEPHONE_UES );
}


#if (PRO_MULTI_LINE == ENABLE)	/* #if is added by H.Kubo 1998/02/23  */

/* NEW_JUDGE 1997/10/28 */
UBYTE MAN_JudgeSelectLine(void)
{
	UWORD	i;
	UWORD	result;
	UBYTE	reserve;
	UBYTE	meory_rx_enable;

	reserve = 0;

	meory_rx_enable = CMN_CheckPollingReceiveEnable();

	/* スキャナ送信チェック */
	result = GetNextExecNoScannerTx();	/* 0～SYS_EXEC_QUEUE_MAXまで検索 */
	if (result != 0xFFFF) {
		SYB_ExecQueueSerchPoint = result;
		result = (UWORD)OPT_JudgeSelectLine();
		if (result == 0x00F0) {
			/* 次ぎへ */
		}
		else if (result == 0xFF) {
			reserve++;	/* 次ぎへ */
		}
		else {
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
			if (MAN_CheckSingleCodecScanTx()) {	/* スキャナ送信可能 */
				return((UBYTE)result);
			}
			else {
				reserve++;	/* 次ぎへ */
			}
#else
			return((UBYTE)result);
#endif
		}
	}

	/* ポーリング一宛先チェック */
	if (meory_rx_enable) {
		SYB_ExecQueueSerchPoint = 0;
		for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
			result = GetNextExecNoPollingRx(SYB_ExecQueueSerchPoint);
			if (result != 0xFFFF) {
				result = (UWORD)OPT_JudgeSelectLine();
				if (result == 0x00F0) {
					/* 次ぎへ */
				}
				else if (result == 0xFF) {
					reserve++;	/* 次ぎへ */
				}
				else {
					return((UBYTE)result);
				}
			}
			SYB_ExecQueueSerchPoint++;
			if (SYB_ExecQueueSerchPoint >= SYS_EXEC_QUEUE_MAX) {
				SYB_ExecQueueSerchPoint = 0;
			}
		}
	}

	/* コマンド・一括チェック */
	SYB_ExecQueueSerchPoint = (UWORD)(SYB_ExecQueueWritePoint + 1);
	if (SYB_ExecQueueSerchPoint >= SYS_EXEC_QUEUE_MAX) {
		SYB_ExecQueueSerchPoint = 0;
	}
	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
		result = GetNextExecQueueNoCommandBatch(SYB_ExecQueueSerchPoint, (UWORD)meory_rx_enable);
		if (result != 0xFFFF) {
			result = (UWORD)OPT_JudgeSelectLine();
			if (result == 0x00F0) {
				/* 次ぎへ */
			}
			else if (result == 0xFF) {
				reserve++;	/* 次ぎへ */
			}
			else {
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
				if ((OPT_CheckScannerCommandFromQue((UBYTE)SYB_ExecQueueSerchPoint))
				&& (MAN_CheckSingleCodecScanTx() == 0)) {

					reserve++;	/* 次ぎへ */
				}
				else {
					return((UBYTE)result);
				}
#else
				return((UBYTE)result);
#endif
			}
		}
		SYB_ExecQueueSerchPoint++;
		if (SYB_ExecQueueSerchPoint >= SYS_EXEC_QUEUE_MAX) {
			SYB_ExecQueueSerchPoint = 0;
		}
	}

	/* 連続ポーリングチェック */
	if (meory_rx_enable) { /** ポーリング受信可能 */
		SYB_ExecQueueSerchPoint = 0;
		for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++) {
			result = GetNextExecNoContPolling(SYB_ExecQueueSerchPoint);
			if (result != 0xFFFF) {
				result = (UWORD)OPT_JudgeSelectLine();
				if (result == 0x00F0) {
					/* 次ぎへ */
				}
				else if (result == 0xFF) {
					reserve++;	/* 次ぎへ */
				}
				else {
					return((UBYTE)result);
				}
			}
			SYB_ExecQueueSerchPoint++;
			if (SYB_ExecQueueSerchPoint >= SYS_EXEC_QUEUE_MAX) {
				SYB_ExecQueueSerchPoint = 0;
			}
		}
	}

	if (reserve) {
		result = 0x00FF;
	}
	else {
		result = 0x00F0;
	}
	return((UBYTE)result);
}
#endif /* (PRO_MULTI_LINE == ENABLE) */



UWORD GetNextExecNoScannerTx(void)
{
	UWORD	i;
	struct SYS_ExecQueueData_t *ep;
	struct SYS_CommandData_t *cp;

	for (i = 0; i < SYS_EXEC_QUEUE_MAX; i++)  { /* ExecQueueの0-SYS_EXEC_QUEUE_MAXまで */
		ep = &SYB_ExecQueue[i];
		if (((ep->Status == SYS_EXEC_WAITING) || (ep->Status == SYS_EXEC_FORWARD_WAITING)) /* ｺﾏﾝﾄﾞ発呼待ちか,転送発呼待ちで */
#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
			&& ((ep->RedialTime <= 0) || (ep->RedialTime == 0xFF))
#else
			&& (ep->RedialTime <= 0)
#endif
			&& (ep->Kind == SYS_COMMAND_TRX))  { /* 既に時間が経過していれば */
			cp = &SYB_CommandFile[ep->Number.Command];

			if ((cp->Option.Item == SYS_SCANNER_TX) ||
				(cp->Option.Item == SYS_DELAYED_SCANNER_TX) ||
				(cp->Option.Item == SYS_SCANNER_SECURE_TX) ||
				(cp->Option.Item == SYS_SCANNER_RELAY_BROADCAST) ||
				(cp->Option.Item == SYS_SCANNER_SUB_ADDRESS_TX)) {

#if (PRO_PREHEAT == ENABLE)
				/* 寒冷地 PreHeat  1999/01/06 s.takeuchi */
				if (SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT) {
					/* プリヒート中のスキャナ送信は無視する(他のコマンドを検索) */
					return(0xFFFF);
				}
#endif

				return(i);
			}
		}
	}
	return(0xFFFF);
}

UWORD GetNextExecNoPollingRx(UWORD point)
{
	struct SYS_ExecQueueData_t *ep;
	struct SYS_CommandData_t *cp;

	ep = &SYB_ExecQueue[point];
	if (((ep->Status == SYS_EXEC_WAITING)
		|| (ep->Status == SYS_EXEC_FORWARD_WAITING)) /* コマンド発呼待ちか,転送発呼待ちで */
#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
	&& ((ep->RedialTime <= 0) || (ep->RedialTime == 0xFF))
#else
	&& (ep->RedialTime <= 0)
#endif
	&& (ep->Kind == SYS_COMMAND_TRX))  { /* 既に時間が経過していれば */
		cp = &SYB_CommandFile[ep->Number.Command];

		if (((cp->Option.Item == SYS_POLLING_RX)
			|| (cp->Option.Item == SYS_DB_POLLING_RX)
			|| (cp->Option.Item == SYS_SELECT_POLLING_RX))
		&&	!CMN_CheckBroadcastCommand(point)) {	/* 一宛先ポーリングで受信可能 */
			return(point);
		}
	}
	return(0xFFFF);
}

UWORD GetNextExecQueueNoCommandBatch(UWORD point, UWORD meory_rx_enable)
{
	struct SYS_ExecQueueData_t *ep;
	struct SYS_CommandData_t *cp;

	SYB_ExecQueueReadPoint = point;
	ep = &SYB_ExecQueue[SYB_ExecQueueReadPoint];
	if (((ep->Status == SYS_EXEC_WAITING) || (ep->Status == SYS_EXEC_FORWARD_WAITING))
#if (PRO_NEW_JATE == ENABLE) /* 条件を変えます By M.Maeda 2002/10/21 *//*#if defined(POPLAR_F)	/* 2000/01/14 Y.Murata RIDIAL_DISP_0_MINITE */
		&& ((ep->RedialTime <= 0) || (ep->RedialTime == 0xFF))) {
#else
		&& (ep->RedialTime <= 0)) {
#endif
		if (ep->Kind == SYS_COMMAND_TRX) {
			cp = &SYB_CommandFile[ep->Number.Command];

#if (PRO_PREHEAT == ENABLE)
			/* 寒冷地 PreHeat  1999/01/06 s.takeuchi */
			if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PREHEAT)
			&&	((cp->Option.Item == SYS_SCANNER_TX)
			  || (cp->Option.Item == SYS_DELAYED_SCANNER_TX)
			  || (cp->Option.Item == SYS_SCANNER_SECURE_TX)
			  || (cp->Option.Item == SYS_SCANNER_RELAY_BROADCAST))) {
				/* プリヒート中のスキャナ送信は無視する(他のコマンドを検索) */
				return(0xFFFF);
			}
#endif

			if (!((cp->Option.Item == SYS_POLLING_RX) ||
			  (cp->Option.Item == SYS_SEQUENTIAL_POLLING) ||	/* 1997/10/06 s.takeuchi */
			  (cp->Option.Item == SYS_DB_POLLING_RX) ||
			  (cp->Option.Item == SYS_SELECT_POLLING_RX)) ||
				meory_rx_enable) {
				return(SYB_ExecQueueReadPoint);
			}
		}
		else if (ep->Kind == SYS_BATCH_TX) {	/* 1997/10/28 */
			return(SYB_ExecQueueReadPoint);
		}
	}
	return(0xFFFF);
}

UWORD GetNextExecNoContPolling(UWORD point)
{
	struct SYS_ExecQueueData_t *ep;

	ep = &SYB_ExecQueue[point];
	if (((ep->Status == SYS_EXEC_WAITING) || (ep->Status == SYS_EXEC_FORWARD_WAITING)) 
	&&	(ep->Kind == SYS_CONTINUOUS_POLLING)) { /** 実行待ちの連続ポーリングコマンドあり */
		return (point);
	}
	return(0xFFFF);
}

UBYTE MAN_CheckSingleCodecScanTx(void)
{
#if (PRO_PRINT_TYPE == LASER)
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) {	/** リストプリント中 */
		return(0);
	}
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {	/** イメージプリント中 */

		if (CMN_CheckF100Model()) {
			if (SYS_DualPrinterWaiting) {
				switch (SYS_DocumentPrintClass) {
				case SYS_PRINT_CLASS_LIST_MEMORY:
				case SYS_PRINT_CLASS_LIST_MONITOR:
				case SYS_PRINT_CLASS_LIST_BA_MEMORY:
				case SYS_PRINT_CLASS_LIST_BA_MONITOR:
				case SYS_PRINT_CLASS_LIST_CIPHER:
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/26 */
				case SYS_PRINT_CLASS_RETURNED_MAIL:
 #endif
					return(0);
				default:
					break;
				}
			}
			else {
				return(0);
			}
		}
		else {
			switch (SYS_DocumentPrintClass) {
			case SYS_PRINT_CLASS_LIST_MEMORY:
			case SYS_PRINT_CLASS_LIST_MONITOR:
			case SYS_PRINT_CLASS_LIST_BA_MEMORY:
			case SYS_PRINT_CLASS_LIST_BA_MONITOR:
			case SYS_PRINT_CLASS_LIST_CIPHER:
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/26 */
			case SYS_PRINT_CLASS_RETURNED_MAIL:
 #endif
				return(0);
			default:
				break;
			}
		}
	}
	else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_MULTI_COPY) {
		if (CMN_CheckF100Model()) {
			if (SYS_DualPrinterWaiting == 0) {
				return(0);
			}
		}
	}
	return(1);

#else
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) {	/** リストプリント中 */
		return(0);
	}
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {	/** イメージプリント中 */
		switch (SYS_DocumentPrintClass) {
		case SYS_PRINT_CLASS_LIST_MEMORY:
		case SYS_PRINT_CLASS_LIST_MONITOR:
		case SYS_PRINT_CLASS_LIST_BA_MEMORY:
		case SYS_PRINT_CLASS_LIST_BA_MONITOR:
		case SYS_PRINT_CLASS_LIST_CIPHER:
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/26 */
		case SYS_PRINT_CLASS_RETURNED_MAIL:
 #endif
			return(0);
		default:
			break;
		}
	}
	return(1);
#endif
}

