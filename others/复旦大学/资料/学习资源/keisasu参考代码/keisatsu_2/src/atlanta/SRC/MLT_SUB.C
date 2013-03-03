#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sys_opt.h"
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\define\sys_line.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\mlt_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\sys_opt.h"	/* 1997/01/13 Y.Murata */
#include "\src\atlanta\define\mem_def.h"	/* 1997/01/13 Y.Murata */

#include  "\src\memsw\define\mem_sw_b.h"

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\mlt_data.h"
#include "\src\atlanta\ext_v\bkupram.h"

#include "\src\memsw\define\mems_pro.h"

/*#if (PRO_MULTI_LINE == ENABLE)*/

/*************************************************************************
	module		:[送信受信設定チェック関数]
	function	:[
		1.
	]
	return		:[
		EXCLUSIVE_TRX		0x00
		EXCLUSIVE_TX		0x01
		EXCLUSIVE_RX		0x02
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[UBYTE far OPT_CHK_UNI_LineTxRx(UBYTE){}]
	date		:[1996/12/16]
	author		:[木元修]
*************************************************************************/
UBYTE  OPT_CHK_UNI_LineTxRx(UBYTE number)
{
	UBYTE value;

	switch(number){
	case 0:
		value = CHK_UNI_Line0_TxRx();
		break;
	case 1:
		value = CHK_UNI_Line1_TxRx();
		break;
	case 2:
		value = CHK_UNI_Line2_TxRx();
		break;
	case 3:
		value = CHK_UNI_Line3_TxRx();
		break;
	case 4:
		value = CHK_UNI_Line4_TxRx();
		break;
	case 5:
		value = CHK_UNI_Line5_TxRx();
		break;
	case 6:
		value = CHK_UNI_Line6_TxRx();
		break;
	case 7:
		value = CHK_UNI_Line7_TxRx();
		break;
	case 8:
		value = CHK_UNI_Line8_TxRx();
		break;
	}
	return(value);
}


/*************************************************************************
	module		:[内線／外線設定チェック関数]
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
	ProtoType	:[UBYTE far OPT_CHK_Pbx(UBYTE){}]
	date		:[1996/12/17]
	author		:[木元修]
*************************************************************************/
UBYTE  OPT_CHK_Pbx(UBYTE number)
{
	UBYTE value;
	
	switch(number) {
	case 0:
		value = CHK_PBX();
		break;
	case 1:
		value = CHK_PBX1();
		break;
	case 2:
		value = CHK_PBX2();
		break;
	case 3:
		value = CHK_PBX3();
		break;
	case 4:
		value = CHK_PBX4();
		break;
	case 5:
		value = CHK_PBX5();
		break;
	case 6:
		value = CHK_PBX6();
		break;
	case 7:
		value = CHK_PBX7();
		break;
	case 8:
		value = CHK_PBX8();
		break;
	}
	return(value);
}


/*************************************************************************
	module		:[回線番号獲得]
	function	:[
		1.指定したスタック番号のモデムが何番目の回線かを示します
	]
	return		:[
			０：該当なし
			１：１回線目
			２：２回線目
			３：３回線目
				・
				・
	]
	common		:[
			引数のスタックナンバーは
			０：ホスト
			１：１番目のオプションボード（モデム、ＰＣ関係なし）
			２：２番目のオプションボード
	]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPT]
	date		:[1996/12/20]
	author		:[村田]
*************************************************************************/
UBYTE  OPT_GetMultiLinrNumber(UBYTE stack_number)
{
	UWORD	i;
	UWORD	line_number;

	line_number = 0;
	for (i = 0; i <= stack_number; i++) {
		if (i == 0) {
			if (SYS_MachineStatus[SYS_OTHER_STATUS] & SYS_INTERNAL_MODEM) {
				line_number++;
			}
		}
		else {
			if (CHK_OptionLineExist((UBYTE)i)) {
				line_number++;
			}
		}
	}
	return((UBYTE)line_number);

}



/*************************************************************************
	module		:[回線が使用中かどうかのチェック]
	function	:[
		1. 引数が０ならば、内蔵回線の意味なので従来からある関数を呼ぶ
		2. １から８の場合は外付け回線
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[MLT]
	ProtoType	:[UBYTE far OPT_CHK_SelecetedLineEnable(UBYTE){}]
	date		:[1996/12/20]
	author		:[木元修]
*************************************************************************/
UBYTE  OPT_CHK_SelecetedLineEnable(UBYTE line_number)
{
	if (line_number == 0) {
		return(CMN_CheckLineEnable());
	}
	else {
		return(CHK_SelectedLineEnable(line_number));
	}
}


/*************************************************************************
	module		:[どっかの回線がスキャナ送信中か否か]
	function	:[
		1.
	]
	return		:[
			ＦＦ：該当なし
			０  ：ホストがスキャナ送信中
			１  ：オプションの1番目がスキャナ送信中
				・
				・
		]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPT]
	date		:[1996/12/20]
	author		:[村田]
*************************************************************************/
UBYTE  OPT_CHK_ScannerTxExecute(void)
{
	UBYTE	i;

	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
		if ((SYS_FaxComTxType == SYS_SCANNER_TX) || (SYS_FaxComType == SYS_MANUAL_TX)) {
			return(0);
		}
	}
	for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
		if (CHK_OptionLineBusy(i)) {
			if ((SYS_Opt[i].SYS_FaxComTxType == SYS_SCANNER_TX) || (SYS_Opt[i].SYS_FaxComType == SYS_MANUAL_TX)) {
				return(i);
			}
		}
	}
	return(0xFF);
}

/*************************************************************************
	module		:[どっかの回線が通信中か否か]
	function	:[
		1.
	]
	return		:[
		]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPT]
	date		:[1996/12/20]
	author		:[村田]
*************************************************************************/
UBYTE  OPT_CHK_FaxComExecute(void)
{
	UWORD	i;

	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM)) {
		return(1);
	}
	else {
		for (i = 0; i < SYS_OPTION_BOARD_MAX; i++) {
			if (CHK_OptionLineBusy((UBYTE)i)) {
				return(1);
			}
		}
	}
	return(0);
}


/*************************************************************************
	module		:[どっかの回線が親展受信中か否か]
	function	:[
		1.
	]
	return		:[
		 0xFF:該当なし
			0:親展ＢＯＸの０番目が受信中
			1:親展ＢＯＸの１番目が受信中
			2:親展ＢＯＸの２番目が受信中
			3:親展ＢＯＸの３番目が受信中
			4:親展ＢＯＸの４番目が受信中
			5:親展ＢＯＸの５番目が受信中
			6:親展ＢＯＸの６番目が受信中
			7:親展ＢＯＸの７番目が受信中
			8:親展ＢＯＸの８番目が受信中
			9:親展ＢＯＸの９番目が受信中
		]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPT]
	date		:[1997/01/10]
	author		:[村田]
*************************************************************************/
UWORD  OPT_CHK_FaxComSecureRxExecute(void)
{
	UWORD	i;

	CMN_DisableInterrupt();
	if ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) &&
		(SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE)) {

		CMN_EnableInterrupt();
		return(SYS_RxMemoryFileNo);
	}
	else {
		for (i = 1; i < SYS_OPTION_BOARD_MAX; i++) {
			if (CHK_OptionLineBusy((UBYTE)i)) {
				if ((SYS_Opt[i].SYS_FaxComType == SYS_AUTO_CALLED) || (SYS_Opt[i].SYS_FaxComType == SYS_MANUAL_RX)) {
					if (SYS_Opt[i].SYS_RxMemoryFileItem == SYS_MEM_SECURE_RX_FILE) {
						CMN_EnableInterrupt();
						return(SYS_Opt[i].SYS_RxMemoryFileNo);
					}
				}
			}
		}
	}
	CMN_EnableInterrupt();
	return(0xFFFF);

}




/*************************************************************************
	module		:[通信回線の数を数える]
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
	ProtoType	:[UBYTE far OPT_CountModems(void){}]
	date		:[1997/01/18]
	author		:[木元修]
*************************************************************************/
UBYTE  OPT_CountModems(void)
{
	UBYTE	i;
	UBYTE	line_cnt;
	
	if (OPT_GetMultiLinrNumber(0) != 0) {
#if (0)	/* 元に戻します by T.Soneoka 1998/03/10 */
///* 内外線切り替え対応 By O.Kimoto 1998/03/06 */
//#if (PRO_LINENUMBER == TWICE_LINE)
//		line_cnt = 2;	/** F-120 */
//#else
//		line_cnt = 1;	/** F-120 */
//#endif
#endif
		line_cnt = 1;	/** F-120 */
	}
	else {
		line_cnt = 0;	/** F-150 */
	}
	
	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i ++ ) {
		if (CHK_OptionLineExist(i) ==1) {
			line_cnt++;
		}
	}
	return(line_cnt);
}

/*************************************************************************
	module		:[ライン数を数える]
	function	:[
		1.ホスト、オプションボードの合計ライン数（モデムの数ではない）
	]
	return		:[合計ライン数]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[OPR]
	date		:[1997/03/11]
	author		:[曽根岡]
*************************************************************************/
UBYTE		OPT_CheckMultiLine(void)
{
	UBYTE	i;
	UBYTE	line_cnt;
	
	if (OPT_GetMultiLinrNumber(0) != 0) {	/**	ホスト	*/
#if (PRO_LINENUMBER == TWICE_LINE)
		line_cnt = 2;	/* POPLAR_H */
#else
		line_cnt = 1;
#endif
	}
	else {
		line_cnt = 0;
	}
	
	for ( i = 0; i < SYS_OPTION_BOARD_MAX; i ++ ) {	/**	オプションボード	*/
		if (CHK_OptionLineExist(i) ==1) {
			line_cnt++;
		}
	}
	return(line_cnt);
}

/*************************************************************************
	module		:[スキャナ送信時のＴＴＩの有無（マルチ仕様）]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MLT]
	date		:[1997/01/27]
	author		:[村田]
*************************************************************************/
UBYTE  OPT_CHK_ScannerTTI_TxAvailable(void)
{
	if (SYS_ScannerTxAbility2 & TTI_TX_AVAILABLE) {
		return(1);
	}
	else {
		return(0);
	}
}

/*************************************************************************
	module		:[カレンダータイプ切り替えか否か]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MLT]
	date		:[1997/01/27]
	author		:[村田]
*************************************************************************/
UBYTE  OPT_CHK_CalendarTypeChange(UBYTE line_number)
{
	if (SYS_FaxComAbility2[line_number] & TTI_CALENDAR_TYPE_CHANGE) {
		return(1);
	}
	else {
		return(0);
	}
}


/*************************************************************************
	module		:[キューからスキャナコマンドか否か判断する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[LINE_SELECT_BUG]
	machine		:[V53]
	language	:[MS-C(Ver.6.0),CH38(Ver.2.0B)]
	keyword		:[OPT]
	ProtoType	:[]
	date		:[1997/10/03]
	author		:[村田]
*************************************************************************/
UBYTE OPT_CheckScannerCommandFromQue(UBYTE que_num)
{
	UBYTE command_number;

	if (SYB_ExecQueue[que_num].Kind == SYS_COMMAND_TRX) {
		command_number = SYB_ExecQueue[que_num].Number.Command;
		if (command_number < SYS_COM_FILE_MAX) {
			switch (SYB_CommandFile[command_number].Status) {
				case SYS_CMD_WAITING:
				case SYS_CMD_EXECUTE:
					switch (SYB_CommandFile[command_number].Option.Item) {
						case SYS_SCANNER_TX:
						case SYS_DELAYED_SCANNER_TX:
						case SYS_SCANNER_SECURE_TX:
						case SYS_SCANNER_RELAY_BROADCAST:
						case SYS_FX_SCANNER_RELAY_TX:
						case SYS_FX_SCANNER_SECURE_TX:

#if (PRO_F_CODE == ENABLE)
						/* Ｆコードが見れていない By O.Kimoto 1998/05/26 */
						case SYS_SCANNER_SUB_ADDRESS_TX:
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
	else {	/* 一括送信、連続ポーリング */
		return(0);
	}
}

/*#endif*/

#if (PRO_RELAYED_REPORT == ENABLE) /* Added by H.Kubo 1998/03/12 */
/*************************************************************************
	module		:[キューから不達通知コマンドか否か判断する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[OPT]
	ProtoType	:[]
	date		:[1998/02/12]
	author		:[久保博]
*************************************************************************/
UBYTE OPT_CheckRlyTxRptCommandFromQue(UBYTE que_num)
{
	UBYTE command_number;

	if (SYB_ExecQueue[que_num].Kind == SYS_COMMAND_TRX) {
		command_number = SYB_ExecQueue[que_num].Number.Command;
		if (command_number < SYS_COM_FILE_MAX) {
			switch (SYB_CommandFile[command_number].Status) {
				case SYS_CMD_WAITING:
				case SYS_CMD_EXECUTE:
					if (SYB_CommandFile[command_number].Option.Item == SYS_RELAYED_TX_REPORT) {
						return(1);
					}
					else {
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
	else {	/* 一括送信、連続ポーリング */
		return(0);
	}
}

#endif /* (PRO_RELAYED_REPORT == ENABLE) */

