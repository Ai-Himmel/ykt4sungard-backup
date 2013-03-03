/*************************************************************************
	System		:ANZU_L InternetFAX
				:POPLAR_B InternetFAX
				:POPLAR_H InternetFAX
	FileName	:CMN_INF.C
	Author		:Y.Tanimoto
	Date		:1998/02/02
	RealTimeOS	:RISC Monitor
	Description	:
	Module		:
	Language	:SHC
	CPU			:SH7043
	Maintenance	:

	Copyright(C) 1997 Murata Machinery Ltd. All rights reserved
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysmax.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sys_stat.h"
#include	"\src\atlanta\define\syscomf.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\mem_def.h"
#include	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\atlanta\define\mon_pro.h"/*1998/05/22 Eguchi */
#include 	"\src\atlanta\sh7043\define\def_semn.h"	/* 1998/05/22 Eguchi */
#include 	"\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1998/05/22 Eguchi */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
#include	"\src\atlanta\define\sys_infd.h"
#include	"\src\atlanta\ext_v\sys_inf.h"
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/*************************************************************************
	module		:[ユーザー情報編集可能かどうか判断]
	function	:[
		1.引数で指定されたユーザーのユーザー情報を編集してもいいかどうか判断する
	]
	return		:[
		1.TRUE		1	編集可
		2.FALSE		0	編集不可
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/04/20]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckUpdateUserData(UBYTE user_no)
{
	UBYTE	cnt;

	/*　実行中のコマンドがあるか　*/
	for (cnt = 0; cnt < SYS_INF_MAIL_COM_MAX ; cnt++) {
		if ( (SYS_INF_MailCommand[cnt].Status == SYS_INF_MAIL_CMD_EXECUTE)
			 && (SYS_INF_MailCommand[cnt].UserNumber == user_no) ) {
			return (FALSE);
		}
	}
	if ((SYS_INF_ExecStatus == SYS_INF_STATUS_INITIAL)
		|| (SYS_INF_ExecStatus == SYS_INF_STATUS_UPDATE)) {
		return (FALSE);
	}
	return (TRUE);
}

/*************************************************************************
	module		:[ユーザー情報消去可能かどうか判断]
	function	:[
		1.引数で指定されたユーザーのユーザー情報を消去してもいいかどうか判断する
	]
	return		:[
		1.TRUE		1	消去可
		2.FALSE		0	消去不可
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/25]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckEraseUserData(UBYTE user_no)
{

	UBYTE	cnt;

	/*　実行中のコマンドがあるか　*/
	for (cnt = 0; cnt < SYS_INF_MAIL_COM_MAX ; cnt++) {
		if ( (SYS_INF_MailCommand[cnt].Status == SYS_INF_MAIL_CMD_EXECUTE)
			 && (SYS_INF_MailCommand[cnt].UserNumber == user_no) ) {
			return (FALSE);
		}
	}
	/*　代行受信原稿が有るか　*/
	for (cnt = 0; cnt < SYS_INF_MAIL_BOX_MAX ; cnt++) {
		if ( (SYS_INF_RxMailBox[cnt].Status != SYS_INF_RX_MAIL_EMPTY)
			 && (SYS_INF_RxMailBox[cnt].UserNumber == user_no) ) {
			return (FALSE);
		}
	}
	if ((SYS_INF_ExecStatus == SYS_INF_STATUS_INITIAL)
		|| (SYS_INF_ExecStatus == SYS_INF_STATUS_UPDATE)) {
		return (FALSE);
	}
	/*　予約中、リダイアル待ちのコマンドを消去　*/
	for (cnt = 0; cnt < SYS_INF_MAIL_COM_MAX ; cnt++) {
		if ( (SYS_INF_MailCommand[cnt].Status != SYS_INF_MAIL_CMD_EMPTY)
			 && (SYS_INF_MailCommand[cnt].UserNumber == user_no) ) {
			CMN_ChangeAutoRcvComStatus(cnt);
			CMN_ClearMailCommand(cnt);
		}
	}
	return (TRUE);

}

/*************************************************************************
	module		:[ユーザー情報の消去]
	function	:[
		1.引数で指定されたユーザーのユーザー情報を消去
		2.OPRでユーザー情報の削除が実行された時に呼ぶ
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/25]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_EraseUserData(UBYTE user_no)
{

	CMN_ClearAutoRcvData(user_no);
	CMN_ClearCommandCounter(user_no);
	CMN_ClearRxMailCounter(user_no);
	CMN_ClearHistoryBox(user_no);
	CMN_ClearPrintPosition(user_no);
	CMN_ClearMailJournalData(user_no);
	CMN_ClearUserData(user_no);

}

/*************************************************************************
	module		:[ユーザー情報の初期化]
	function	:[
		1.引数で指定されたユーザーのユーザー情報を初期化
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		こんなにバカ丁寧に初期化する必要は無い。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearUserData(UBYTE user_no)
{

	UBYTE	i;

	for (i = 0; i < SYS_INF_USER_CODE_MAX ; i++) {
		SYB_INF_UserData[user_no].UserCodeNumber[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_USER_NAME_MAX ; i++) {
		SYB_INF_UserData[user_no].UserName[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_SUB_DIAL_MAX ; i++) {
		SYB_INF_UserData[user_no].TelNumber [i][0] = 0xFF;
	}
	for (i = 0; i < SYS_PIN_MAX ; i++) {
		SYB_INF_UserData[user_no].PIN_Number[i] = 0xFF;
	}
	for (i = 0; i < SYS_INF_ISP_NAME_MAX ; i++) {
		SYB_INF_UserData[user_no].ISP_Name[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_PPP_ID_MAX ; i++) {
		SYB_INF_UserData[user_no].PPP_LoginID[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_PPP_PASSWORD_MAX ; i++) {
		SYB_INF_UserData[user_no].PPP_Password[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_POP_ID_MAX ; i++) {
		SYB_INF_UserData[user_no].POP_LoginID[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_POP_PASSWORD_MAX ; i++) {
		SYB_INF_UserData[user_no].POP_Password[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_MAIL_ADDRESS_MAX ; i++) {
		SYB_INF_UserData[user_no].MailAddress[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_POP_SERVER_NAME_MAX ; i++) {
		SYB_INF_UserData[user_no].POP_Server[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_SMTP_SERVER_NAME_MAX ; i++) {
		SYB_INF_UserData[user_no].SMTP_Server[i] = (UBYTE)NULL;
	}
	for (i = 0; i < SYS_INF_IP_ADDRESS_OCTET_MAX ; i++) {
		SYB_INF_UserData[user_no].ISP_ServerAddress[i] = (UBYTE)NULL;
		SYB_INF_UserData[user_no].IP_Address[i] = (UBYTE)NULL;
		SYB_INF_UserData[user_no].Primary_DNS_Server[i] = (UBYTE)NULL;
		SYB_INF_UserData[user_no].Secondary_DNS_Server[i] = (UBYTE)NULL;
		SYB_INF_UserData[user_no].GatewayAddress[i] = (UBYTE)NULL;
	}
	SYB_INF_UserData[user_no].PPP_Authentication = SYS_INF_PPP_AUTH_PAP;
	SYB_INF_UserData[user_no].OptionalSetting = 0;
	SYB_INF_UserData[user_no].OptionalSetting |= SYS_INF_AUTO_PRINT_ON;
	SYB_INF_UserData[user_no].OptionalSetting |= SYS_INF_AUTO_DOWNLOAD_ON;
	SYB_INF_UserData[user_no].StartTime = 0xFFFF;		/*　表示は現在時刻を出す　*/
	SYB_INF_UserData[user_no].EndTime = 0xFFFF;			/*　表示は現在時刻を出す　*/
	SYB_INF_UserData[user_no].IntervalTime = 0xFFFF;	/*　表示は3:00(時間）　*/
	SYB_INF_UserData[user_no].HoldTime = 0xFFFF;		/*　表示は1(日)　*/

	/*SYS_INF_JournalLogNumber[user_no] = 0;*/	/*  通信管理記録の通番をクリア　*/
	SYS_INF_JournalLogNumber[user_no] = 1;		/*  通信管理記録の通番をクリア　*//* 0 -> 1 1998/05/22 Eguchi */


}

/*************************************************************************
	module		:[全ユーザー情報の初期化]
	function	:[
		1.全ユーザーのユーザー情報を初期化
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		こんなにバカ丁寧に初期化する必要は無い。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllUserData(void)
{

	UBYTE	user_no;

	for (user_no = 0; user_no < SYS_INF_USER_MAX; user_no++) {
		CMN_ClearUserData(user_no);
	}


}

/*************************************************************************
	module		:[自動受信用データの初期化]
	function	:[
		1.引数で指定されたユーザーの自動受信元データを初期化
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/10]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAutoRcvData(UBYTE user_no)
{

	SYS_INF_AutoRcvData[user_no].Status = SYS_INF_AUTO_RCV_OFF;
	SYS_INF_AutoRcvData[user_no].StartTime = 0xFFFF;
	SYS_INF_AutoRcvData[user_no].EndTime = 0xFFFF;
	SYS_INF_AutoRcvData[user_no].IntervalTimer = 180;

}

/*************************************************************************
	module		:[自動受信用データの初期化]
	function	:[
		1.全ユーザーの自動受信元データを初期化
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/10]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllAutoRcvData(void)
{

	UBYTE user_no;

	for (user_no = 0; user_no < SYS_INF_USER_MAX; user_no++) {
		CMN_ClearAutoRcvData(user_no);
	}

}

/*************************************************************************
	module		:[コマンドファイルの空きのチェックと予約]
	function	:[
			1.コマンドファイルに空きが有るかどうかチェック
			2.空きが有ればコマンドファイルを予約中にする
	]
	return		:[
			1.予約したコマンド番号　空きが有り予約成功
			2.SYS_INF_MAIL_COM_MAX　コマンドに空き無し
	]
	common		:[]
	condition	:[]
	comment		:[
			ユーザーからメール送信、あるいは受信の起動がされたときに
			OPRはこのモジュールでコマンドの空きを探し同時に予約しておきます。
			最終的に、コマンドに値をセットしない場合は必ずクリアのモジュールを呼ぶこと
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/02]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckAndReserveMailCommand(void)
{

	UBYTE i;
	for (i = 0; i < SYS_INF_MAIL_COM_MAX;i++) {
		if (SYS_INF_MailCommand[i].Status == SYS_INF_MAIL_CMD_EMPTY) {
			SYS_INF_MailCommand[i].Status = SYS_INF_MAIL_CMD_SETTING;
			SYB_INF_MailCommandStatus[i].Status = SYS_INF_MAIL_CMD_SETTING;
			return(i);
		}
	}
	return(i);

}

/*************************************************************************
	module		:[コマンドファイルの初期化]
	function	:[
		1.引数で指定されたコマンドファイルの初期化
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/02]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearMailCommand(UBYTE	com_no)
{

	UBYTE	i;

	SYS_INF_MailCommand[com_no].Status = SYS_INF_MAIL_CMD_ERASED;
	SYB_INF_MailCommandStatus[com_no].Status = SYS_INF_MAIL_CMD_ERASED;

	SYS_INF_MailCommand[com_no].Kind = SYS_INF_NO_JOB;
	SYS_INF_MailCommand[com_no].UserNumber = 0xFF;
	SYS_INF_MailCommand[com_no].SubDialPosition = 0;
	SYS_INF_MailCommand[com_no].ExecTime = 0xFFFFFFFF;
	SYS_INF_MailCommand[com_no].RedialCount = 0;
	SYS_INF_MailCommand[com_no].RedialInterval = 0;
	for (i = 0; i < SYS_INF_MAIL_DIRECT_COUNT_MAX; i++) {
		SYS_INF_MailCommand[com_no].Direct[i][0] = NULL;
	}
	for (i = 0; i < SYS_INF_ONETOUCH_POSITION_MAX; i++) {
		SYS_INF_MailCommand[com_no].Onetouch[i] = 0;
	}
	SYS_INF_MailCommand[com_no].FoundJunkMail = 0;
	SYS_INF_MailCommand[com_no].ListPrintRequest = 0;
	SYS_INF_MailCommand[com_no].Result = SYS_INF_RESULT_OK;
	/*	コマンドファイルの中身を初期化し終わったら
	**	最後にStatusをEMPTYに変更。
	*/
	SYB_INF_MailCommandStatus[com_no].Status = SYS_INF_MAIL_CMD_EMPTY;
	SYB_INF_MailCommandStatus[com_no].UserNumber = 0xFF;
	SYS_INF_MailCommand[com_no].Status = SYS_INF_MAIL_CMD_EMPTY;


}

/*************************************************************************
	module		:[全コマンドファイルの初期化]
	function	:[
		1.全コマンドファイルの初期化
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/02]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllMailCommand(void)
{

	UBYTE	com_no;

	for (com_no = 0; com_no < SYS_INF_MAIL_COM_MAX; com_no++) {
		CMN_ClearMailCommand(com_no);
	}


}


/*************************************************************************
	module		:[電源ON/OFF後のコマンドファイルのリカバー]
	function	:[
		1.電源OFF前のコマンドファイルの状態によって処理を施す
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/02]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_RecoverMailCommand(void)
{

	UBYTE	com_no;
	UBYTE	box_no;

	for (com_no = 0; com_no < SYS_INF_MAIL_COM_MAX; com_no++) {
		switch (SYS_INF_MailCommand[com_no].Status) {
		case SYS_INF_MAIL_CMD_EMPTY:
		case SYS_INF_MAIL_CMD_REDIAL:
			break;
		case SYS_INF_MAIL_CMD_WAITING:
			if ((SYS_INF_MailCommand[com_no].Kind == SYS_INF_MAIL_AUTO_RX)
				|| (SYS_INF_MailCommand[com_no].Kind == SYS_INF_MAIL_AUTO_CHK)) {
				SYS_INF_AutoRcvData[SYS_INF_MailCommand[com_no].UserNumber].Status = (UBYTE)SYS_INF_AUTO_RCV_EXECUTE;
			}
			break;
		case SYS_INF_MAIL_CMD_COMPLETED:
			if (SYS_INF_MailCommand[com_no].ListPrintRequest == 0) {
				CMN_ChangeAutoRcvComStatus(com_no);
				CMN_ClearMailCommand(com_no);
			}
			break;
		case SYS_INF_MAIL_CMD_EXECUTE:
			switch (SYS_INF_MailCommand[com_no].Kind) {
			case SYS_INF_MAIL_TX:
			case SYS_INF_MAIL_TXRX:
				/*　WAITINGに変えてやるように変更する　*/
				if (MEM_CountTotalPage(SYS_MEM_MAIL_TX_FILE, com_no, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
					/*　微妙なタイミングで電源断になったときは同じメールが２回送信されることになる　*/
					SYS_INF_MailCommand[com_no].ListPrintRequest = 0;
					SYB_INF_MailCommandStatus[com_no].UserNumber = SYS_INF_MailCommand[com_no].UserNumber;
					SYB_INF_MailCommandStatus[com_no].Status = SYS_INF_MAIL_CMD_WAITING;
					SYS_INF_MailCommand[com_no].Status = SYS_INF_MAIL_CMD_WAITING;
				}
				else {
					SYB_INF_MailCommandStatus[com_no].Status = SYS_INF_MAIL_CMD_COMPLETED;
					SYS_INF_MailCommand[com_no].Status = SYS_INF_MAIL_CMD_COMPLETED;
					if (SYS_INF_MailCommand[com_no].ListPrintRequest == 0) {	/* リストの印字要求無し　*/
						CMN_ClearMailCommand(com_no);	/*	コマンド消去	*/
					}
				}
				break;
			case SYS_INF_MAIL_AUTO_CHK:
			case SYS_INF_MAIL_AUTO_RX:
				CMN_ClearReservedMailBox();
				box_no = SYS_INF_ManualPrintPosition[SYS_INF_MailCommand[com_no].UserNumber].PrintEnd;
				if (SYS_INF_RxMailBox[box_no].DocumentType == SYS_INF_NOT_DNLD_MAIL_LIST) {
					CMN_ReleaseHoldTimeoutMailBox(box_no);
				}
				CMN_ChangeAutoRcvComStatus(com_no);
				CMN_ClearMailCommand(com_no);
				break;
			case SYS_INF_MAIL_MANUAL_RX:
			default:
				SYS_INF_MailCommand[com_no].ListPrintRequest |= SYS_INF_LST_ERROR_PRINT;
				SYS_INF_MailCommand[com_no].Result = SYS_INF_RESULT_POWEROFF;
				SYB_INF_MailCommandStatus[com_no].Status = SYS_INF_MAIL_CMD_COMPLETED;
				SYS_INF_MailCommand[com_no].Status = SYS_INF_MAIL_CMD_COMPLETED;
				break;
			}
			break;
		case SYS_INF_MAIL_CMD_SETTING:
		case SYS_INF_MAIL_CMD_ABORT:
			if (MEM_CountTotalPage(SYS_MEM_MAIL_TX_FILE, com_no, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				MEM_ClearDoc(SYS_MEM_MAIL_TX_FILE, com_no, MEM_IGNORE_BOX_NUMBER);
			}
			CMN_ClearMailCommand(com_no);	/*	コマンド消去	*/
			break;
		case SYS_INF_MAIL_CMD_ERASED:
		default:
			CMN_ClearMailCommand(com_no);	/*	コマンド消去	*/
			break;
		}
	}


}

/*************************************************************************
	module		:[メモリの空きをチェックする]
	function	:[]
	return		:[
		1.TRUE		メモリに空きがある
		2.FALSE		メモリに空きが無い
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckFreeMemoryArea(void)
{

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/14 Y.Murata for KAKI */
	if ((CMN_CheckMemoryForMemRx())/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
		return(TRUE);
	}
	else {
		return(FALSE);
	}
#else
	if (((MEM_CountTotalEmptyBlock() + MEM_RX_BORDERLINE) > SYS_MEMORY_EMPTY_BLOCK)/** メモリーブロックに空きあり     */
	&&	(MEM_CountTotalEmptyPage() > 0)) {	/** インデックスに空きあり */
		return(TRUE);
	}
	else {
		return(FALSE);
	}
#endif
}

/*************************************************************************
	module		:[管理テーブルの空きをチェック]
	function	:[
		1.管理テーブルの空きを探す
		2.空きが有ればそのBOX番号をリターン
		3.空きがなければSYS_INF_MAIL_BOX_MAXをリターン
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckMailBox(void)
{
	UBYTE	i;

	for (i = 0; i < SYS_INF_MAIL_BOX_MAX; i++) {
		if (SYS_INF_RxMailBox[i].Status == SYS_INF_RX_MAIL_EMPTY) {
			return(i);
		}
	}
	return(i);
}

/*************************************************************************
	module		:[メモリ受信可能かどうかをチェック]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/05/13]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckMailRcvEnable(void)
{
	if ((CMN_CheckFreeMemoryArea() == TRUE)
		&& (CMN_CheckMailBox() < SYS_INF_MAIL_BOX_MAX)) {
		return (TRUE);
	}
	return (FALSE);
}

/*************************************************************************
	module		:[指定された管理BOXを予約する]
	function	:[
		1.指定された管理テーブルが空きかどうかチェック
		2.空きで有ればそのBOXを予約しそのBOX番号を再度リターン
		3.空きでなければSYS_INF_MAIL_BOX_MAXをリターン（ありえないけど）
	]
	return		:[
		1.予約完了	TRUE
		2.予約失敗	FALSE
	]
	common		:[
		1.CMN_CheckMailBoxで空き番号をCheckした後に呼ぶ
		2.そのBOX番号と実行中のコマンド番号を引数で渡す
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_ReserveMailBox(UBYTE box_no,UBYTE com_no)
{
	if ( (SYS_INF_RxMailBox[box_no].Status == SYS_INF_RX_MAIL_EMPTY)
		  && (box_no < SYS_INF_MAIL_BOX_MAX) ) {
		SYS_INF_RxMailBox[box_no].UserNumber = SYS_INF_MailCommand[com_no].UserNumber;
		if (SYS_INF_MailCommand[com_no].Kind == SYS_INF_MAIL_MANUAL_RX) {
			SYS_INF_RxMailBox[box_no].PrintPolicy = SYS_INF_AUTO_PRINT;
			SYS_INF_RxMailBox[box_no].CommandNo = 0xFF;
		}
		else if (SYS_INF_MailCommand[com_no].Kind == SYS_INF_MAIL_AUTO_CHK) {
			SYS_INF_RxMailBox[box_no].PrintPolicy = SYS_INF_AUTO_PRINT;
			SYS_INF_RxMailBox[box_no].CommandNo = 0xFF;
		}
		else {
			if (SYB_INF_UserData[SYS_INF_MailCommand[com_no].UserNumber].OptionalSetting & SYS_INF_AUTO_PRINT_ON) {
				SYS_INF_RxMailBox[box_no].PrintPolicy = SYS_INF_AUTO_PRINT;
				SYS_INF_RxMailBox[box_no].CommandNo = 0xFF;
			}
			else {
				SYS_INF_RxMailBox[box_no].PrintPolicy = SYS_INF_MANUAL_PRINT;
				SYS_INF_RxMailBox[box_no].CommandNo = com_no;
			}
		}
		SYS_INF_RxMailBox[box_no].Status = SYS_INF_RX_MAIL_RESERVED;
		SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_RESERVED;
		SYB_INF_RxMailBoxStatus[box_no].UserNumber = SYS_INF_RxMailBox[box_no].UserNumber;
		return(TRUE);
	}
	return(FALSE);
}

/*************************************************************************
	module		:[空いている管理BOXを探しあれば予約する]
	function	:[
		1.管理テーブルの空きを検索
		2.空きが有れば予約する
		3.Kindに自動プリントか手動プリントかをセット
		4.UserNumberに予約したユーザー番号をセット
	]
	return		:[
		1.空きが有り予約完了	予約したBOXの番号
		2.空きが無く予約失敗	SYS_INF_MAIL_BOX_MAX
	]
	common		:[]
	condition	:[]
	comment		:[
		このモジュールでは空いている管理テーブルが有れば予約中に
		してしまうので、単に管理テーブルの空きを探すだけには使用できない。
		空きだけを探すならCMN_CheckMailBoxの方を使用。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckAndReserveMailBox(UBYTE com_no)
{

	UBYTE	box_no;

	box_no = CMN_CheckMailBox();
	if (box_no < SYS_INF_MAIL_BOX_MAX) {
		CMN_ReserveMailBox(box_no,com_no);
		return(box_no);
	}
	return(SYS_INF_MAIL_BOX_MAX);


}


/*************************************************************************
	module		:[指定された管理BOXをリンクにセットする]
	function	:[
	]
	return		:[
		1.リンク接続成功	TRUE
		2.リンク接続失敗	FALSE
	]
	common		:[]
	condition	:[]
	comment		:[
		今はリンクセット中に電源OFFが起こっても、もう一度このモジュールを
		通すだけでRENEWAL中だったMailBoxのリカバー処理にも対応できるが、
		処理を変えたときには対応できなくなる可能性が有るので注意。
		変数に値をセットする順番を変えただけでもだめ。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_SetRxMailBox(UBYTE box_no)
{

	UBYTE user_no;
	struct	SYS_INF_PrintPositionTable_t *print_pos;

	SYS_INF_RxMailBox[box_no].Status |= SYS_INF_RX_MAIL_RENEWAL;
	SYB_INF_RxMailBoxStatus[box_no].Status |= SYS_INF_RX_MAIL_RENEWAL;

	user_no = SYS_INF_RxMailBox[box_no].UserNumber;
	SYS_INF_RxMailBox[box_no].NextBoxNo = 0xFE;	/* リンクの最後尾を示します　*/

	if (SYS_INF_RxMailBox[box_no].PrintPolicy == SYS_INF_AUTO_PRINT) {
		print_pos = &SYS_INF_AutoPrintPosition[user_no];
	}
	else {
		print_pos = &SYS_INF_ManualPrintPosition[user_no];
	}

	if (print_pos->PrintTop == 0xFF) {
		print_pos->PrintTop = box_no;
		print_pos->PrintEnd = box_no;
	}
	/*　単にリンクに繋ぐだけなら以下のelse ifは一括にelseでいいが
	**　この条件文にしておくことによって電源OFF時のリカバーにも対応できるようになる
	*/
	else if (print_pos->PrintEnd == 0xFF) {
		print_pos->PrintEnd = box_no;
	}
	else if (print_pos->PrintEnd != box_no) {
		SYS_INF_RxMailBox[print_pos->PrintEnd].NextBoxNo = box_no;
		print_pos->PrintEnd = box_no;
	}

	SYB_INF_RxMailBoxStatus[box_no].Status &= ~SYS_INF_RX_MAIL_RENEWAL;
	SYS_INF_RxMailBox[box_no].Status &= ~SYS_INF_RX_MAIL_RENEWAL;


}

/*************************************************************************
	module		:[先頭の管理BOXをリンクからはずす]
	function	:[
	]
	return		:[
		1.分離成功	TRUE
		2.分離失敗	FALSE
	]
	common		:[]
	condition	:[]
	comment		:[
		今は先頭のMailBoxをRelease中に電源OFFが起こっても、
		もう一度このモジュールを通すだけでRelease中だった
		MailBoxのリカバー処理にも対応できるが、処理を変えた
		ときには対応できなくなる可能性が有るので注意。
		変数に値をセットする順番を変えただけでもだめ。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ReleaseTopMailBox(UBYTE box_no)
{

	UBYTE user_no;
	struct	SYS_INF_PrintPositionTable_t *print_pos;

	user_no = SYS_INF_RxMailBox[box_no].UserNumber;
	SYS_INF_RxMailBox[box_no].Status |= SYS_INF_RX_MAIL_TOP_RELEASE;
	SYB_INF_RxMailBoxStatus[box_no].Status |= SYS_INF_RX_MAIL_TOP_RELEASE;

	if (SYS_INF_RxMailBox[box_no].PrintPolicy == SYS_INF_AUTO_PRINT) {
		print_pos = &SYS_INF_AutoPrintPosition[user_no];
	}
	else {
		print_pos = &SYS_INF_ManualPrintPosition[user_no];
	}

	if (SYS_INF_RxMailBox[box_no].NextBoxNo == 0xFE) {	/*　最後尾のメールBOX　*/
		print_pos->PrintTop = 0xFF;
		print_pos->PrintEnd = 0xFF;
	}
	else {
		print_pos->PrintTop = SYS_INF_RxMailBox[box_no].NextBoxNo;
	}

	SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_RELEASED;
	SYS_INF_RxMailBox[box_no].Status = SYS_INF_RX_MAIL_RELEASED;


}

/*************************************************************************
	module		:[指定した管理BOXをリンクからはずす]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		今はMailBoxをRelease中に電源OFFが起こっても、
		もう一度このモジュールを通すだけでRelease中だった
		MailBoxのリカバー処理にも対応できるが、処理を変えた
		ときには対応できなくなる可能性が有るので注意。
		変数に値をセットする順番を変えただけでもだめ。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ReleaseMailBox(UBYTE box_no)
{

	UBYTE user_no;
	UBYTE i;
	struct	SYS_INF_PrintPositionTable_t *print_pos;

	user_no = SYS_INF_RxMailBox[box_no].UserNumber;

	if (SYS_INF_RxMailBox[box_no].PrintPolicy == SYS_INF_AUTO_PRINT) {
		print_pos = &SYS_INF_AutoPrintPosition[user_no];
	}
	else {
		print_pos = &SYS_INF_ManualPrintPosition[user_no];
	}

	if (print_pos->PrintTop == box_no) {
		/*　指定されたのが先頭のBoxだった　*/
		CMN_ReleaseTopMailBox(box_no);
	}
	else {
		SYS_INF_RxMailBox[box_no].Status |= SYS_INF_RX_MAIL_RELEASE;
		SYB_INF_RxMailBoxStatus[box_no].Status |= SYS_INF_RX_MAIL_RELEASE;
		for (i = 0; i < SYS_INF_MAIL_BOX_MAX; i++) {
			if ((SYS_INF_RxMailBox[i].UserNumber == user_no)
				&& (SYS_INF_RxMailBox[i].NextBoxNo == box_no)) {
				if (SYS_INF_RxMailBox[box_no].NextBoxNo == 0xFE) {	/* 最後のBOXだった　*/
					print_pos->PrintEnd = i;
				}
				SYS_INF_RxMailBox[i].NextBoxNo = SYS_INF_RxMailBox[box_no].NextBoxNo;
				SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_RELEASED;
				SYS_INF_RxMailBox[box_no].Status = SYS_INF_RX_MAIL_RELEASED;
				break;
			}
		}
		/*　ここでさらにStatusを変えるのは不要に見えるが、
		**　こうしておくと、電源OFF時のリカバーにも対応できる
		*/
		SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_RELEASED;
		SYS_INF_RxMailBox[box_no].Status = SYS_INF_RX_MAIL_RELEASED;
	}

}

/*************************************************************************
	module		:[指定した管理BOXをリンクからはずす]
	function	:[
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		今はMailBoxをRelease中に電源OFFが起こっても、
		もう一度このモジュールを通すだけでRelease中だった
		MailBoxのリカバー処理にも対応できるが、処理を変えた
		ときには対応できなくなる可能性が有るので注意。
		変数に値をセットする順番を変えただけでもだめ。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ReleaseHoldTimeoutMailBox(UBYTE box_no)
{

	UBYTE user_no;
	UBYTE i;
	struct	SYS_INF_PrintPositionTable_t *print_pos;

	user_no = SYS_INF_RxMailBox[box_no].UserNumber;
	print_pos = &SYS_INF_ManualPrintPosition[user_no];

	SYS_INF_RxMailBox[box_no].Status |= SYS_INF_RX_MAIL_HOLD_TIMEOUT;
	SYB_INF_RxMailBoxStatus[box_no].Status |= SYS_INF_RX_MAIL_HOLD_TIMEOUT;
	if (print_pos->PrintTop == box_no) {
		if (SYS_INF_RxMailBox[box_no].NextBoxNo == 0xFE) {	/*　最後尾のメールBOX　*/
			print_pos->PrintTop = 0xFF;
			print_pos->PrintEnd = 0xFF;
		}
		else {
			print_pos->PrintTop = SYS_INF_RxMailBox[box_no].NextBoxNo;
		}
	}
	else {
		for (i = 0; i < SYS_INF_MAIL_BOX_MAX; i++) {
			if ((SYS_INF_RxMailBox[i].UserNumber == user_no)
				&& (SYS_INF_RxMailBox[i].NextBoxNo == box_no)) {
				if (SYS_INF_RxMailBox[box_no].NextBoxNo == 0xFE) {	/* 最後のBOXだった　*/
					print_pos->PrintEnd = i;
				}
				SYS_INF_RxMailBox[i].NextBoxNo = SYS_INF_RxMailBox[box_no].NextBoxNo;
				break;
			}
		}
	}
	SYS_INF_RxMailBox[box_no].PrintPolicy = SYS_INF_AUTO_PRINT;
	SYB_INF_RxMailBoxStatus[box_no].Status &= ~SYS_INF_RX_MAIL_HOLD_TIMEOUT;
	SYS_INF_RxMailBox[box_no].Status &= ~SYS_INF_RX_MAIL_HOLD_TIMEOUT;
	CMN_SetRxMailBox(box_no);
}


/*************************************************************************
	module		:[電源OFFの後の全管理BOXのリカバー]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_RecoverMailBox(void)
{

	UBYTE	box_no;

	for (box_no = 0; box_no < SYS_INF_MAIL_BOX_MAX; box_no++) {
		switch (SYS_INF_RxMailBox[box_no].Status) {
		case SYS_INF_RX_MAIL_EMPTY:
			CMN_ClearRxMailBox(box_no);	/*　念のため初期化しておく　*/
			break;
		case SYS_INF_RX_MAIL_RESERVED:
		case SYS_INF_RX_MAIL_RECEIVING:
			MEM_ClearDoc(SYS_MEM_MAIL_RX_FILE ,box_no, MEM_IGNORE_BOX_NUMBER);
			CMN_ReleaseMailBox(box_no);
			CMN_ClearRxMailBox(box_no);
			break;
		case SYS_INF_RX_MAIL_RECEIVED:
			if (MEM_CountTotalPage(SYS_MEM_MAIL_RX_FILE , box_no, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) {
				/*　プリント中に電源OFFが起こった　*/
				if (SYS_INF_RxMailBox[box_no].NextBoxNo == 0xFF) {
					/*  まだリンクにセットされていなければセットする　*/
					CMN_SetRxMailBox(box_no);
				}
			}
			else {
				/*　プリントは終了していた　*/
				CMN_ReleaseMailBox(box_no);
				CMN_ClearRxMailBox(box_no);
			}
			break;
		case SYS_INF_RX_MAIL_RELEASED:
			/*　プリント終了し、リンクからもはずされた後　*/
			CMN_ClearRxMailBox(box_no);
			break;
		default:
			if (SYS_INF_RxMailBox[box_no].Status & SYS_INF_RX_MAIL_RENEWAL) {
				CMN_SetRxMailBox(box_no);
			}
			else if (SYS_INF_RxMailBox[box_no].Status & SYS_INF_RX_MAIL_TOP_RELEASE) {
				CMN_ReleaseTopMailBox(box_no);
				CMN_ClearRxMailBox(box_no);
			}
			else if (SYS_INF_RxMailBox[box_no].Status & SYS_INF_RX_MAIL_RELEASE) {
				CMN_ReleaseMailBox(box_no);
				CMN_ClearRxMailBox(box_no);
			}
			else if (SYS_INF_RxMailBox[box_no].Status & SYS_INF_RX_MAIL_HOLD_TIMEOUT) {
				CMN_ReleaseHoldTimeoutMailBox(box_no);
			}
			else {	/*  有り得ないけど　*/
				CMN_ClearRxMailBox(box_no);
			}
			break;
		}
	}


}


/*************************************************************************
	module		:[指定された管理BOXを消去]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearRxMailBox(UBYTE box_no)
{

	UBYTE i;

	SYS_INF_RxMailBox[box_no].PrintPolicy = SYS_INF_AUTO_PRINT;
	SYS_INF_RxMailBox[box_no].CommandNo = 0xff;
	SYS_INF_RxMailBox[box_no].DocumentType = SYS_INF_FAX_MAIL;
	SYS_INF_RxMailBox[box_no].NextBoxNo = 0xff;
	SYS_INF_RxMailBox[box_no].UserNumber = 0xff;
	for (i = 0; i < SYS_INF_MAIL_ADDRESS_MAX; i++) {
		SYS_INF_RxMailBox[box_no].From[i] = NULL;
	}
	SYS_INF_RxMailBox[box_no].PrintTime = 0;
	/* 各変数を初期化し終わった後、StatusをEMPTYに変更する　*/
	SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_EMPTY;
	SYB_INF_RxMailBoxStatus[box_no].UserNumber = 0xFF;
	SYS_INF_RxMailBox[box_no].Status = SYS_INF_RX_MAIL_EMPTY;


}

/*************************************************************************
	module		:[全管理BOXを消去]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/03]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllMailBox(void)
{

	UBYTE	box_no;

	for (box_no = 0; box_no < SYS_INF_MAIL_BOX_MAX; box_no++) {
		CMN_ClearRxMailBox(box_no);
	}


}

/*************************************************************************
	module		:[予約中BOXを消去]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/09]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearReservedMailBox(void)
{
	UBYTE	box_no;
	for (box_no = 0; box_no < SYS_INF_MAIL_BOX_MAX; box_no++) {
		if (SYS_INF_RxMailBox[box_no].Status == SYS_INF_RX_MAIL_RESERVED) {
			CMN_ClearRxMailBox(box_no);
		}
	}
}

/*************************************************************************
	module		:[管理テーブルの情報を消去]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearPrintPosition(UBYTE user_no)
{

	SYS_INF_AutoPrintPosition[user_no].PrintTop = 0xFF;
	SYS_INF_AutoPrintPosition[user_no].PrintEnd = 0xFF;
	SYS_INF_ManualPrintPosition[user_no].PrintTop = 0xFF;
	SYS_INF_ManualPrintPosition[user_no].PrintEnd = 0xFF;

}

/*************************************************************************
	module		:[全ユーザーの管理テーブルの情報を消去]
	function	:[
	]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllPrintPosition(void)
{

	UBYTE	user_no;

	for (user_no = 0; user_no < SYS_INF_USER_MAX;user_no++) {
		SYS_INF_AutoPrintPosition[user_no].PrintTop = 0xFF;
		SYS_INF_AutoPrintPosition[user_no].PrintEnd = 0xFF;
		SYS_INF_ManualPrintPosition[user_no].PrintTop = 0xFF;
		SYS_INF_ManualPrintPosition[user_no].PrintEnd = 0xFF;
	}

}

/*************************************************************************
	module		:[プリント開始するページ番号をチェック]
	function	:[]
	return		:[
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/09]
	author		:[Y.Tanimoto]
*************************************************************************/
UWORD	CMN_GetRxMailPrintStartPage(UBYTE item , UWORD no, UBYTE box)
{
	UWORD	page;

	page = MEM_CheckMostSmallPage(item,no);
	if (page == MEM_NO_INDEX) {
		return (0);
	}
	return (page);
}

/*************************************************************************
	module		:[ワンタッチの登録状況セット]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_SetOnetouchStatus(void)
{

	UBYTE	i;

	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
		if ((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0) {
			SYB_INF_OnetouchStatus[i] = SYS_INF_ONETOUCH_FAXNUMBER;
		}
		else if (SYB_INF_Onetouch[i].MailAddress[0] != NULL) {
			SYB_INF_OnetouchStatus[i] = SYS_INF_ONETOUCH_MAILADDRESS;
		}
		else {
			SYB_INF_OnetouchStatus[i] = SYS_INF_ONETOUCH_NO_ENTRY;
		}
	}

}

/*************************************************************************
	module		:[Ｐワンタッチの登録状況セット]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_SetProgramOnetouchStatus(void)
{

	UBYTE	i;
	UBYTE	j;

	for (i = 0; i < SYS_PROGRAM_MAX; i++) {
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/04 By M.Kuwahara */
		if (SYB_ProgramOnetouch[i].Item != SYS_PROGRAM_EMPTY) {
#else
		if (SYB_ProgramOnetouch[i].Status != SYS_CMD_EMPTY) {
#endif
			SYB_INF_ProgramOnetouchStatus[i] = SYS_INF_P_ONETOUCH_PROGRAM;
		}
		else {
			SYB_INF_ProgramOnetouchStatus[i] = SYS_INF_P_ONETOUCH_NO_ENTRY;
			for (j = 0; j < SYS_INF_ONETOUCH_POSITION_MAX; j++) {
				if (SYB_INF_MailGroup[i][j] != NULL) {
					SYB_INF_ProgramOnetouchStatus[i] = SYS_INF_P_ONETOUCH_MAILGROUP;
					break;
				}
			}
		}
	}

}

/*************************************************************************
	module		:[ワンタッチに登録されたメールアドレスのクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearOnetouchMailData(UBYTE pos)
{

	UBYTE i;

	SYB_INF_OnetouchStatus[pos] = SYS_INF_ONETOUCH_NO_ENTRY;

	for (i = 0; i < SYS_INF_MAIL_ADDRESS_MAX; i++) {
		SYB_INF_Onetouch[pos].MailAddress[i] = NULL;
	}
	for (i = 0; i < SYS_INF_MAIL_NAME_MAX; i++) {
		SYB_INF_Onetouch[pos].Name[i] = NULL;
	}


}

/*************************************************************************
	module		:[ワンタッチに登録されたメールアドレスのオールクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllOnetouchMailData(void)
{

	UBYTE i;
	for (i = 0; i < SYS_ONETOUCH_MAX; i++) {
		CMN_ClearOnetouchMailData(i);
	}

}

/*************************************************************************
	module		:[Ｐワンタッチに登録されたメールアドレスのクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearGroupMailData(UBYTE pos)
{

	UBYTE i;

	SYB_INF_ProgramOnetouchStatus[pos] = SYS_INF_P_ONETOUCH_NO_ENTRY;

	for (i = 0; i < SYS_INF_ONETOUCH_POSITION_MAX; i++) {
		SYB_INF_MailGroup[pos][i] = NULL;
	}


}

/*************************************************************************
	module		:[Ｐワンタッチに登録されたメールアドレスのオールクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllGroupMailData(void)
{

	UBYTE i;
	for (i = 0; i < SYS_PROGRAM_MAX; i++) {
		CMN_ClearGroupMailData(i);
	}

}

/*************************************************************************
	module		:[アドレスのヒストリー登録用BOXのクリア]
	function	:[特定のユーザーの特定のBOXをクリア]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearOneHistoryBox(UBYTE box_no,UBYTE user_no)
{

	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Status = SYS_INF_HISTORY_EMPTY;
	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Address[0] = NULL;
	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].NextBox = 0xFF;

}

/*************************************************************************
	module		:[アドレスのヒストリー登録用BOXのクリア]
	function	:[
		一人のユーザー分のヒストリーデータをすべてクリア
		]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearHistoryBox(UBYTE user_no)
{

	UBYTE i;
	SYS_INF_MailAddressHistory[user_no].TopBox = 0xFF;
	for (i = 0; i < SYS_INF_HISTORY_MAX; i++) {
		SYS_INF_MailAddressHistory[user_no].HistoryBox[i].Status = SYS_INF_HISTORY_EMPTY;
		SYS_INF_MailAddressHistory[user_no].HistoryBox[i].Address[0] = NULL;
		SYS_INF_MailAddressHistory[user_no].HistoryBox[i].NextBox = 0xFF;
	}

}

/*************************************************************************
	module		:[アドレスのヒストリー登録用BOXのオールクリア]
	function	:[
		1.全ユーザー分の全ヒストリーデータをクリア
		2.電源OFF後の立ち上げ時にDRAMバックアップがNGの時に呼ばれる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllHistoryBox(void)
{

	UBYTE i,j;
	for (i = 0; i < SYS_INF_USER_MAX; i++) {
		SYS_INF_MailAddressHistory[i].TopBox = 0xFF;
		for (j = 0; j < SYS_INF_HISTORY_MAX; j++) {
			SYS_INF_MailAddressHistory[i].HistoryBox[j].Status = SYS_INF_HISTORY_EMPTY;
			SYS_INF_MailAddressHistory[i].HistoryBox[j].Address[0] = NULL;
			SYS_INF_MailAddressHistory[i].HistoryBox[j].NextBox = 0xFF;
		}
	}

}

/*************************************************************************
	module		:[アドレスのヒストリー登録用BOXの空きを探す]
	function	:[
		1.空きのBOXを探し、空のBOXならBOX番号をリターン
		2.一番古いBOXを渡す時にはリンクからはずして渡す
		]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckEmptyHistoryBox(UBYTE user_no)
{

	UBYTE i;
	for (i = 0; i < SYS_INF_HISTORY_MAX; i++) {
		if (SYS_INF_MailAddressHistory[user_no].HistoryBox[i].Status == SYS_INF_HISTORY_EMPTY) {
			return (i);
		}
	}
	for (i = 0; i < SYS_INF_HISTORY_MAX; i++) {
		if (SYS_INF_MailAddressHistory[user_no].HistoryBox[i].NextBox == 0xFF) {
			CMN_ReleaseHistoryBox(user_no, i);
			return (i);
		}
	}

}

/*************************************************************************
	module		:[アドレスのヒストリー登録用BOXの空きを探す]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ReleaseHistoryBox(UBYTE user_no, UBYTE box_no)
{

	UBYTE i;
	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Status = SYS_INF_HISTORY_RELEASE;
	for (i = 0; i < SYS_INF_HISTORY_MAX; i++) {
		if (SYS_INF_MailAddressHistory[user_no].HistoryBox[i].NextBox == box_no) {
			SYS_INF_MailAddressHistory[user_no].HistoryBox[i].NextBox = 0xFF;
			CMN_ClearOneHistoryBox(box_no,user_no);
			break;
		}
	}
	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Status = SYS_INF_HISTORY_EMPTY;

}

/*************************************************************************
	module		:[指定されたデータをヒストリー中のデータと比較]
	function	:[]
	return		:[
		1.TRUE		同じ物が登録済み
		2.FALSE		同じ物は登録されていない
	]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/25]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CompareHistoryData(UBYTE *string, UBYTE user_no, UBYTE length)
{

	UBYTE	box_no;
	for (box_no = 0; box_no < SYS_INF_HISTORY_MAX; box_no++) {
		if ( (SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Status == SYS_INF_HISTORY_STORED)
			 && (CMN_StringCompare(string,&SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Address[0],length) == STRCMP_EQUAL) ) {
				return (TRUE);
		}
	}
	return (FALSE);

}

/*************************************************************************
	module		:[アドレスをセットしたヒストリー登録用BOXをリンクにセット]
	function	:[
		1.OPRでアドレスをヒストリーBOXに登録した後に使用する
		2.リンクに最新（表示の優先順位が一番高い）のものとしてセットされる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_SetHistoryBox(UBYTE user_no, UBYTE box_no)
{

	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Status = SYS_INF_HISTORY_SETTING;
	if (SYS_INF_MailAddressHistory[user_no].TopBox != 0xFF) {
		SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].NextBox = SYS_INF_MailAddressHistory[user_no].TopBox;
	}
	SYS_INF_MailAddressHistory[user_no].TopBox = box_no;
	SYS_INF_MailAddressHistory[user_no].HistoryBox[box_no].Status = SYS_INF_HISTORY_STORED;

}

/*************************************************************************
	module		:[電源ON/OFF時のヒストリーのリカバー]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/13]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_RecoverHistoryBox(void)
{

	UBYTE	i,j;
	for (i = 0; i < SYS_INF_USER_MAX; i++) {
		for (j = 0; j < SYS_INF_HISTORY_MAX; j++) {
			if (SYS_INF_MailAddressHistory[i].HistoryBox[j].Status == SYS_INF_HISTORY_SETTING) {
				if (SYS_INF_MailAddressHistory[i].TopBox != j) {
					CMN_SetHistoryBox(i, j);
				}
				else {
					SYS_INF_MailAddressHistory[i].HistoryBox[j].Status = SYS_INF_HISTORY_STORED;
				}
			}
			else if (SYS_INF_MailAddressHistory[i].HistoryBox[j].Status == SYS_INF_HISTORY_RELEASE) {
				CMN_ReleaseHistoryBox(i, j);
			}
		}
	}

}

/*************************************************************************
	module		:[コマンド消去通知プリント用のカウンターのクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/14]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearCommandCounter(UBYTE user_no)
{

	UBYTE	cmd_no;

	for (cmd_no = 0; cmd_no < SYS_INF_MAIL_BOX_MAX; cmd_no++) {
		if (SYB_INF_MailCommandStatus[cmd_no].UserNumber == user_no) {
			SYB_INF_MailCommandStatus[cmd_no].Status = SYS_INF_MAIL_CMD_EMPTY;
		}
	}
	SYB_INF_ErasedMailComRequest[user_no] = FALSE;


}

/*************************************************************************
	module		:[コマンド消去通知プリント用のカウンターのオールクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/14]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllCommandCounter(void)
{

	UBYTE	user_no;
	UBYTE	cmd_no;

	for (cmd_no = 0; cmd_no < SYS_INF_MAIL_BOX_MAX; cmd_no++) {
		SYB_INF_MailCommandStatus[cmd_no].Status = SYS_INF_MAIL_CMD_EMPTY;
	}
	for (user_no = 0; user_no < SYS_INF_USER_MAX; user_no++) {
		SYB_INF_ErasedMailComRequest[user_no] = FALSE;
	}

}

/*************************************************************************
	module		:[受信原稿消去通知プリント用のカウンターのクリア]
	function	:[
		1.一人のユーザーの代行受信原稿の有無を管理するデータをクリア
		2.受信原稿消去通知を書いた後に呼ばれる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/14]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearRxMailCounter(UBYTE user_no)
{

	UBYTE	box_no;

	for (box_no = 0; box_no < SYS_INF_MAIL_BOX_MAX; box_no++) {
		if (SYB_INF_RxMailBoxStatus[box_no].UserNumber == user_no) {
			SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_EMPTY;
		}
	}
	SYB_INF_ErasedRxMailRequest[user_no] = FALSE;

}

/*************************************************************************
	module		:[受信原稿消去通知プリント用のカウンターのオールクリア]
	function	:[
		1.代行受信原稿の有無を管理するデータをオールクリア
		2.オールＲＡＭクリアの時に呼ばれる
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/14]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllRxMailCounter(void)
{

	UBYTE	box_no;
	UBYTE	user_no;

	for (box_no = 0; box_no < SYS_INF_MAIL_BOX_MAX; box_no++) {
		SYB_INF_RxMailBoxStatus[box_no].Status = SYS_INF_RX_MAIL_EMPTY;
	}
	for (user_no = 0; user_no < SYS_INF_USER_MAX; user_no++) {
		SYB_INF_ErasedRxMailRequest[user_no] = FALSE;
	}

}

/*************************************************************************
	module		:[コマンドファイルにセットされたリスト印字要求のクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/24]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearPrintRequest(UBYTE item,UBYTE com_no)
{

	switch (item) {
	case LST_INF_ERROR_NOTICE:
		SYS_INF_MailCommand[com_no].ListPrintRequest &= ~SYS_INF_LST_ERROR_PRINT;
		break;
	case LST_INF_SECURE_NOTICE:
		CMN_ClearSecureNoticeRequest(com_no);
		SYS_INF_MailCommand[com_no].ListPrintRequest &= ~SYS_INF_LST_SECURE_PRINT;
		break;
	}
	if (SYS_INF_MailCommand[com_no].ListPrintRequest == 0) {
		CMN_ChangeAutoRcvComStatus(com_no);
		CMN_ClearMailCommand(com_no);
	}

}

/*************************************************************************
	module		:[自動受信コマンドの状態更新]
	function	:[
		1.実行されていたコマンドが自動受信なら状態の更新
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/25]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ChangeAutoRcvComStatus( UBYTE com_no )
{

	UBYTE user_no;

	/*　自動受信コマンドをクリアするときにはこの処理が必要　*/
	user_no = SYS_INF_MailCommand[com_no].UserNumber;
	if (((SYS_INF_MailCommand[com_no].Kind == SYS_INF_MAIL_AUTO_RX)
		|| (SYS_INF_MailCommand[com_no].Kind == SYS_INF_MAIL_AUTO_CHK))
		&& (SYS_INF_AutoRcvData[user_no].Status == SYS_INF_AUTO_RCV_EXECUTE)) {
		SYS_INF_AutoRcvData[user_no].IntervalTimer = SYB_INF_UserData[user_no].IntervalTime;
		SYS_INF_AutoRcvData[user_no].Status = SYS_INF_AUTO_RCV_WAITING;
	}

}

/*************************************************************************
	module		:[親展受信通知プリント済みをセット]
	function	:[
		1.親展受信通知を書き終わった管理テーブルに
		　プリント済みをセットします。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/02/26]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearSecureNoticeRequest( UBYTE cmd_no )
{
	UBYTE box_no;
	UBYTE user_no;
	struct	SYS_INF_PrintPositionTable_t *print_pos;

	user_no = SYS_INF_MailCommand[cmd_no].UserNumber;
	print_pos = &SYS_INF_ManualPrintPosition[user_no];
	box_no = print_pos->PrintTop;

	while ((box_no != 0xFF) && (box_no != 0xFE)) {
		if (SYS_INF_RxMailBox[box_no].CommandNo == cmd_no) {
			SYS_INF_RxMailBox[box_no].CommandNo = 0xFF;
		}
		box_no = SYS_INF_RxMailBox[box_no].NextBoxNo;
	}
}

/*************************************************************************
	module		:[ジャーナルデータ消去]
	function	:[
		１ユーザー分のジャーナルデータを格納している領域を初期化する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearMailJournalData( UBYTE user_no )
{
	UBYTE log_no;

	SYS_INF_MailJournalData[user_no].ConnectTime = 0;
	SYS_INF_MailJournalData[user_no].ConnectCount = 0;
	SYS_INF_MailJournalData[user_no].ReadPoint = 0;
	for (log_no = 0; log_no < SYS_INF_LOG_MAX; log_no++) {
		SYS_INF_MailJournalData[user_no].Log[log_no].Status = 0;
		SYS_INF_MailJournalData[user_no].Log[log_no].Number = 0;
		SYS_INF_MailJournalData[user_no].Log[log_no].Address[0] = 0;
	}
	SYS_INF_JournalLogNumber[user_no] = 1;/*0->1 1998/05/22 Eguchi*/
}

/*************************************************************************
	module		:[ジャーナルデータ消去]
	function	:[
		全ユーザー分のジャーナルデータを格納している領域を初期化する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/03/04]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllMailJournalData( void )
{
	UBYTE user_no;

	for (user_no = 0; user_no < SYS_INF_USER_MAX; user_no++) {
		CMN_ClearMailJournalData(user_no);
	}
}

/*************************************************************************
	module		:[蓄積ページのデータ量記憶領域の初期化]
	function	:[
		1.DRAM上に取っている送信用の蓄積原稿のデータ量を
		　記憶しておく領域を初期化する。
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
		DRAMﾊﾞｯｸｱｯﾌﾟがNGのときにコールする。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/03/26]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllStoreDocParameter(void)
{
	UWORD index_no;
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {
		SYS_INF_StoredMailDataCount[index_no] = 0;	/* 初期化 */
	}
}

/*************************************************************************
	module		:[ユーザーデータ更新情報のクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/04/20]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearUserDataStatus(UBYTE user_no)
{
	SYB_INF_UserDataStatus[user_no].UserCodeNumber = 0;
	SYB_INF_UserDataStatus[user_no].UserName = 0;
	SYB_INF_UserDataStatus[user_no].TelNumber = 0;
	SYB_INF_UserDataStatus[user_no].PIN_Number = 0;
	SYB_INF_UserDataStatus[user_no].ISP_Name = 0;
	SYB_INF_UserDataStatus[user_no].PPP_LoginID = 0;
	SYB_INF_UserDataStatus[user_no].PPP_Password = 0;
	SYB_INF_UserDataStatus[user_no].PPP_Authentication = 0;
	SYB_INF_UserDataStatus[user_no].POP_LoginID = 0;
	SYB_INF_UserDataStatus[user_no].POP_Password = 0;
	SYB_INF_UserDataStatus[user_no].IP_Address = 0;
	SYB_INF_UserDataStatus[user_no].MailAddress = 0;
	SYB_INF_UserDataStatus[user_no].ISP_ServerAddress = 0;
	SYB_INF_UserDataStatus[user_no].POP_Server = 0;
	SYB_INF_UserDataStatus[user_no].SMTP_Server = 0;
	SYB_INF_UserDataStatus[user_no].Primary_DNS_Server = 0;
	SYB_INF_UserDataStatus[user_no].Secondary_DNS_Server = 0;
	SYB_INF_UserDataStatus[user_no].GatewayAddress = 0;
	SYB_INF_UserDataStatus[user_no].Status = 0;
	SYB_INF_UserDataStatus[user_no].ChangeMailBox = 0;
}

/*************************************************************************
	module		:[全ユーザーデータ更新情報のクリア]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/04/20]
	author		:[Y.Tanimoto]
*************************************************************************/
void	CMN_ClearAllUserDataStatus(void)
{
	UBYTE	user_no;

	for (user_no = 0; user_no < SYS_INF_USER_MAX; user_no++) {
		CMN_ClearUserDataStatus(user_no);
	}
	SYB_INF_ClearAllAccountReq = 0;
}

/*************************************************************************
	module		:[]
	function	:[]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CMN]
	date		:[1998/05/14]
	author		:[Y.Tanimoto]
*************************************************************************/
UBYTE	CMN_CheckMailBoxPrintStatus(UBYTE box_no)
{
	UBYTE	ret;

	ret = 0;
	if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_PRINTER_BUSY)
		&& ((SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT)
			 || (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT))
		&& 	(SYS_DocumentPrintItem 	== SYS_MEM_MAIL_RX_FILE)
		&& 	(SYS_DocumentPrintNo 	== box_no)) {
		ret = 1;
	}
	return (ret);
}




/*************************************************************************
	module		:[ジャーナルプリント用データの初期化]
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
void	CMN_ClearPrintJournalData(void)
{
	UBYTE log_no;

	SYS_PrintMailJournalData.ConnectTime = 0;
	SYS_PrintMailJournalData.ConnectCount = 0;
	SYS_PrintMailJournalData.ReadPoint = 0;
	for (log_no = 0; log_no < SYS_INF_LOG_MAX; log_no++) {
		SYS_PrintMailJournalData.Log[log_no].Status = 0;
	}
}

#endif	/* PRO_DIALUP_INTERNET_FAX == ENABLE */

