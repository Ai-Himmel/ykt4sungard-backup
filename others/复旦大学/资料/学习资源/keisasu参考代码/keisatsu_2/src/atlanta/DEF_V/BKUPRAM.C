/*	By Y.Suzuki 1996/10/12	*/
/* By S.K Spe.21,1995 */
/*------------------------------------------------------------------*/
/* 警告 ！！														*/
/* リモート診断でアクセスする時にアドレスがずれる恐れがありますので */
/* 追加及び変更は慎重にお願いします									*/
/*------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"	/*	By Y.Suzuki 1996/10/16	*/
#include "\src\atlanta\define\sysmailb.h"
#include "\src\atlanta\define\sysjrnl.h"
#include "\src\atlanta\define\sysbatch.h"
#include "\src\atlanta\define\syscomf.h"
#include "\src\atlanta\define\sysonet.h"
#include "\src\atlanta\define\sysexec.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\syslifem.h"
#include "\src\atlanta\define\sysshad.h"
#include "\src\atlanta\define\sysspeed.h"
#include "\src\atlanta\define\sysdiali.h"
#include "\src\atlanta\define\sysmemrx.h"
#include "\src\atlanta\define\syscost.h"
#include "\src\atlanta\define\syst30.h"
#include "\src\atlanta\define\sysdeprt.h"
#include "\src\atlanta\define\systbok.h"	/* 94/04/08 By K.W */
#include "\src\atlanta\define\sysopspd.h"	 /* 95/02/09 By T.Nose */
#include "\src\atlanta\define\sysringm.h"
#include "\src\atlanta\define\syscntpl.h"
#include "\src\atlanta\define\sysorder.h"	/* 1997/09/19 By M.Tachibana */

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/12 */
#include "\src\atlanta\define\sysnd.h"
#endif

/*#if (PRO_F_CODE == ENABLE)*/
	#include "\src\atlanta\define\sysfcode.h"	/* 1997/01/09  By T.Yamaguchi */
/*#endif*/
/*#if (PRO_PC_PRINT == ENABLE)*/
	#include "\src\atlanta\define\syspcrx.h"	/* By J.Miyazaki 1996/08/13 */
/*#endif*/
/*#if (PRO_DPRAM == ENABLE)*/
	#include "\src\atlanta\define\dpr_def.h"	/* 96/11/13 By M.Kotani */
/*#endif*/

/*#if (PRO_CIPHER == ENABLE)*/
	#include "\src\atlanta\define\syskey.h"		/* By Y.Suzuki 1997/06/02 */
	#include "\src\atlanta\define\syscph.h"		/* By Y.Suzuki 1997/06/02 */
/*#endif*/

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/*	とりあえず条件コンパイルで切り分けます	*/
	#include "\src\atlanta\define\sys_infd.h"	/* 1998/03/10 By Y.Tanimoto */
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)
/*	とりあえず条件コンパイルで切り分けます	*/
#include "\src\atlanta\define\syswarp.h"	/* 1998/06/15 By M.Kuwahara */
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)
/*	とりあえず条件コンパイルで切り分けます	*/
#include "\src\atlanta\define\sysnd.h"	/* 1998/06/15 By M.Kuwahara */
#endif

#if (PRO_KEY_MACRO == ENABLE)
/*	とりあえず条件コンパイルで切り分けます	*/
#include "\src\atlanta\define\sysmcr.h"	/* 1998/06/17 By M.Kuwahara */
#endif

#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/04 By M.Kuwahara */
#include	"\src\atlanta\define\syspgone.h"
#endif

#pragma section BKUPRAM		/* セクション指定 */


/*######################################################################################*
 * リモート診断のユーザ選択により読み書きできる先頭アドレス								*
 * リモート診断ON :これ以降のアドレスのデータの読み書きができる							*
 * リモート診断OFF:これ以降のアドレスのデータの読み書きができない						*
 * 1993/11/24																			*
 * 吉川弘康																				*
 *######################################################################################*/
UBYTE	SYB_DiagRW_UserSelectAddress = 0;

/************************************************************************
 * パスコード															*
 * syspass.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_PasscodeNumber[SYS_PASSCODE_MAX] = {0};

/************************************************************************
 * 親展受信ボックス														*
 * "\src\rice\define\sysmailb.h"										*
 * sysmailb.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_MailBoxData_t	SYB_MailBox[SYS_MAILBOX_MAX] = {0};

/************************************************************************
 * 通信管理記録(送受信分離型)											*
 * "\src\rice\define\sysjrnl.h"											*
 * sysjrnl.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_JOURNAL == SEPARATE)
/*
 * 送信用通信管理記録
 */
struct SYS_JournalData_t	SYB_TxJournalFile[SYS_JOURNAL_MAX] = {0};
/*
 * 受信用通信管理記録
 */
struct SYS_JournalData_t	SYB_RxJournalFile[SYS_JOURNAL_MAX] = {0};
/*
 * 送信用通信管理記録の記録位置
 * ・次にセットすべきSYB_TxJournalFile[]の配列オフセット値
 * ・サイクリック加算で0となると自動プリントを行う
 */
UBYTE	SYB_TxJournalPoint = 0;
/*
 * 受信用通信管理記録の記録位置
 * ・次にセットすべきSYB_RxJournalFile[]の配列オフセット値
 * ・サイクリック加算で0となると自動プリントを行う
 */
UBYTE	SYB_RxJournalPoint = 0;
#endif

/************************************************************************
 * 通信管理記録(送受信一体型)											*
 * "\src\rice\define\sysjrnl.h"											*
 * sysjrnl.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_JOURNAL == UNITED)
/*
 * 送受信用通信管理記録
 */
 
/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)

 #if (PRO_POST_OFFICE == ENABLE)	/* 郵政局特ROM by O.Kimoto 2001/01/21 */
struct SYS_JournalData_t	SYB_JournalFile[SYS_JOURNAL_MAX_AREA] = {0};
 #else
struct SYS_JournalData_t	SYB_JournalFile[SYS_JOURNAL_MAX] = {0};
 #endif
#else
struct SYS_JournalData_t	SYB_JournalFile[SYS_JOURNAL_MAX] = {0};
#endif
/*
 * 送受信用通信管理記録の記録位置
 * ・次にセットすべきSYB_JournalFile[]の配列オフセット値
 * ・サイクリック加算で0となると自動プリントを行う
 */
UBYTE	SYB_JournalPoint = {0};
#endif

/************************************************************************
 * 通信管理記録															*
 * "\src\rice\define\sysjrnl.h"											*
 * sysjrnl.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
/*
 * 通信管理記録の送信通番
 * ・次にセットすべき送信用通番
 * ・0～9999
 */
UWORD	SYB_TxJournalNumber = {0};
/*
 * 通信管理記録の受信通番
 * ・次にセットすべき受信用通番
 * ・0～9999
 */
UWORD	SYB_RxJournalNumber = {0};

/************************************************************************
 * 標準短縮ダイヤル														*
 * "\src\atlanta\define\sysspeed.h"										*
 * sysspeed.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
/*struct SYS_SpeedDialData_t	SYB_SpeedDial[SYS_SPEED_DIAL_MAX] = {0};By Y.Suzuki 1998/03/15 */
struct SYS_SpeedDialData_t	SYB_SpeedDial[SYS_SPEED_DIAL_MAX_BKUP] = {0};

/************************************************************************
 * 任意短縮番号オペレーション用管理テーブル								*
 * struct SYS_OptionalSpeedTable_t SYB_OptionalSpeed[SYS_SPEED_DIAL_MAX] *
 * 1995/02/09															*
 * 野瀬敏弘			下から移動しましした 97/06/06 T.Yamaguchi			*
 * #if (PRO_OPTIONAL_SPEED == ENABLE)									*
 ************************************************************************/
/*struct SYS_OptionalSpeedTable_t	SYB_OptionalSpeed[SYS_SPEED_DIAL_MAX] = {0};By Y.Suzuki 1998/03/15 */
struct SYS_OptionalSpeedTable_t	SYB_OptionalSpeed[SYS_SPEED_DIAL_MAX_BKUP] = {0};


/************************************************************************
 * 第2短縮ダイヤル														*
 * "\src\atlanta\define\sysspeed.h"										*
 * 1993/12/06															*
 * 吉川弘康																*
 ************************************************************************/
/* #if (PRO_2ND_SPEED == ENABLE) */
/* struct SYS_2ndSpeedDialData_t SYB_2ndSpeedDial[SYS_2ND_SPEED_DIAL_MAX] = {0}; */
/* #endif */

/************************************************************************
 * 標準ワンタッチダイヤル												*
 * "\src\atlanta\define\sysonet.h"										*
 * sysonet.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if (0) /* 1995/11/27 ワンタッチ・プログラムワンタッチの兼用が廃止になるため */
//struct SYS_OnetouchDialData_t SYB_OnetouchDial[SYS_ONETOUCH_MAX] = {0};
#endif
struct SYS_SpeedDialData_t	SYB_OnetouchDial[SYS_ONETOUCH_MAX] = {0};

/************************************************************************
 * プログラムワンタッチダイアル											*
 * 1995/11/27 Eguchi													*
 * プログラムワンタッチは専用キーになるため								*
 ************************************************************************/
/*struct	SYS_CommandData_t	SYB_ProgramOnetouch[SYS_PROGRAM_MAX] = {0}; define name change 1998/02/19 Y.Murata */
#if (PRO_EXT_P_ONETOUCH == ENABLE)	/* 1998/08/11 By M.Kuwahara */
struct	SYS_ProgramOnetouchData_t	SYB_ProgramOnetouch[SYS_PROGRAM_MAX_BKUP] = {0};
#else
struct	SYS_CommandData_t	SYB_ProgramOnetouch[SYS_PROGRAM_MAX_BKUP] = {0};
#endif

/************************************************************************
 * 第2ワンタッチダイヤル												*
 * "\src\atlanta\define\sysspeed.h"										*
 * 1993/12/06															*
 * 吉川弘康																*
 ************************************************************************/
/* #if (PRO_2ND_ONETOUCH == ENABLE) */
/* struct SYS_SpeedDialData_t SYB_2ndOnetouchDial[SYS_2ND_ONETOUCH_MAX] = {0};*/
/* #endif */

/************************************************************************
 * 転送先ダイヤル														*
 * syssubd.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 * #if (PRO_SUB_DIAL == ENABLE)											*
 ************************************************************************/
UBYTE	SYB_SubDial[SYS_SUB_DIAL_MAX][SYS_TEL_2DIGIT_MAX] = {0};

/************************************************************************
 * 部門別料金管理のトータル時間											*
 * "\src\atlanta\define\sysdeprt.h"										*
 * 1994/03/25															*
 * 吉川弘康																*
 * #if (PRO_DEPARTMENT == ENABLE)										*
 ************************************************************************/
struct SYS_DepartData_t SYB_DepartFile[SYS_DEPART_MAX] = {0};

/************************************************************************
 * 一括送信																*
 * "\src\atlanta\define\sysbatch.h"										*
 * 1993/11/19															*
 * 吉川弘康																*
 * #if (PRO_BATCH_TX == ENABLE)											*
 ************************************************************************/
struct SYS_BatchTxData_t	SYB_BatchTxFile[SYS_BATCH_FILE_MAX] = {0};

/************************************************************************
 * カバーページ送信のメッセージ内容										*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_CoverPageMessage[SYS_MESSAGE_MAX] = {0};


/*#if (PRO_F_CODE == ENABLE)*/	/*	1997/01/09	By T.Yamaguchi */
/************************************************************************
 *	Fｺｰﾄﾞﾃﾞｰﾀ格納ﾊﾞｯﾌｧ			(プログラムワンタッチ登録用)
 ***********************************************************************/
/*struct SYS_FcodeNumberData_t	SYB_FcodeNumberPDataBuffer[SYS_PROGRAM_MAX * F_CODE_DATA_MAX] = {0}; define name change 1998/02/19 Y.Murata */
struct SYS_FcodeNumberData_t	SYB_FcodeNumberPDataBuffer[SYS_PROGRAM_MAX_BKUP * F_CODE_DATA_MAX] = {0};

/***************************************************************
 *	サブアドレスＢＯＸ
 ***************************************************************/
struct SYS_SubAddressBoxData_t	SYB_SubAddressBoxTable[SUB_ADDRESS_BOX_MAX] = {0};

/************************************************************************/
/* 選択ﾎﾟｰﾘﾝｸﾞ原稿蓄積状態管理ﾃﾞ-ﾀ										*/
/************************************************************************/
UBYTE	SYB_SelectPollDocumentStatus = 0;	/* 選択ポーリング蓄積原稿あり */
/*#endif*/

/************************************************************************
 *	ジャンクメール防止ダイヤル登録バッファ	1997/05/12  By T.Yamaguchi
 ***********************************************************************/
UBYTE	SYB_JunkMailProtectDialBuffer[SYS_JUNK_DIAL_MAX][SYS_JUNK_DIAL_NUMBER_MAX] = {0};

/************************************************************************
 *	MercuryAccessCode,MercuryPINNumber入力用DialBuffer					*
 *		1994.3.9			原田										*
 ************************************************************************/
UBYTE	SYB_MercuryDialBuffer[SYS_MERCURY_BUF_MAX] = {0};

/************************************************************************
 * FXポーリングパスワード												*
 * 1994/07/27															*
 * 吉川弘康																*
 ************************************************************************/
/*#if (PRO_MAKER == FX)*/
UBYTE	SYB_FX_PollingPassword[SYS_FX_POLLING_PASSWARD_MAX] = {0};
/*#endif*/

/************************************************************************
 * リモート診断パスワード												*
 * 1994/08/17															*
 * 村田																	*
 ************************************************************************/
UBYTE	SYB_DiagPasscodeNumber[4] = {0};


/*######################################################################################*
 * リモート診断のユーザ選択にかかわらずに読み書きできる先頭アドレス						*
 * リモート診断ON :これ以前のアドレスのデータの読み書きができる							*
 * リモート診断OFF:これ以前のアドレスのデータの読み書きができない						*
 * 1993/11/24																			*
 * 吉川弘康																				*
 *######################################################################################*/
UBYTE	SYB_DiagRW_Address = 0;

#if (0)	/* バックアップエリアの最後にもっていく By M.Tachibana 1997/12/16 */
///************************************************************************
// * バックアップRAMテスト												*
// * 機種名を記憶する														*
// * 1993/11/24															*
// * 吉川弘康																*
// ************************************************************************/
//UBYTE	SYB_BackupRAM_TestArea[SYS_BACKUP_RAM_TEST_AREA_MAX] = {0};
#endif

/************************************************************************
 * ＣＰＵのバージョン													*
 * 1997/05/28															*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_CPU_Revision[ROM_REVISION_MAX] = {0};

/************************************************************************
 * メモリスイッチ														*
 * "\src\atlanta\define\mem_sw_a.h"										*
 * "\src\atlanta\define\mem_sw_b.h"										*
 * "\src\atlanta\define\mem_sw_c.h"										*
 * "\src\atlanta\define\mem_sw_d.h"										*
 * "\src\atlanta\define\mem_sw_e.h"										*
 * "\src\atlanta\define\mem_sw_f.h"										*
 * "\src\atlanta\define\mem_sw_g.h"										*
 * "\src\atlanta\define\mem_sw_h.h"										*
 * "\src\atlanta\define\mem_sw_i.h"										*
 * "\src\atlanta\define\mem_sw_j.h"										*
 * memsw.xls参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYS_MemorySwitch[SYS_MEMORY_SWITCH_MAX] = {0};

/************************************************************************
 * 機器パラメータ														*
 * "\src\atlanta\define\param.h"										*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_MachineParameter[SYS_MACHINE_PARAMETER_MAX] ={0};

/************************************************************************
 * 機種固有スイッチ
 * 1996/03/06 Eguchi
 ************************************************************************/
UBYTE	SYB_MachineUniqSwitch[SYS_MEMORY_SWITCH_MAX] = {0};

/************************************************************************
 * 保守用スイッチ
 * 1996/03/06 Eguchi
 ************************************************************************/
UBYTE	SYB_MaintenanceSwitch[SYS_MEMORY_SWITCH_MAX] = {0};

/************************************************************************
 * ローカル機器設定														*
 * "\src\atlanta\define\syslocal.h"										*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_LocalStatus[SYS_LOCAL_MAX] = {0};

/************************************************************************
 * 機器設定																*
 * "\src\atlanta\define\status.h"										*
 * setting.xls参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_SettingStatus[SYS_SETTING_MAX] = {0};


/************************************************************************
 * 発信元電話番号														*
 * syssubid.jsw参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 ************************************************************************/
/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	UBYTE	SYB_ID_Buffer[2][SYS_ID_MAX] = {0};
#else
	UBYTE	SYB_ID_Buffer[SYS_ID_MAX] = {0};
#endif


/************************************************************************
 * 発信元名																*
 * 漢字有りの機種では、送信原稿先頭付加専用のバッファになる				*
 * 漢字無しの機種では、送信原稿先頭付加と非標準用と兼用で使う			*
 * systti.jsw参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 ************************************************************************/
/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	UBYTE	SYB_TTI_Buffer[2][SYS_TTI_MAX] = {0};
#else
	UBYTE	SYB_TTI_Buffer[SYS_TTI_MAX] = {0};
#endif


/************************************************************************
 * 発信元名カナＩＤ(非標準手順用)										*
 * 漢字有りの機種のみで、非標準手順専用のバッファとなる					*
 * systti.jsw参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 * #if (PRO_PANEL == KANJI) || (PRO_JIS_CODE == ENABLE)					*
 ************************************************************************/
/* ＰＯＰＬＡＲ＿Ｈ 標準２回線収容対応の為 By O.Kimoto 1997/11/01 */
#if (PRO_LINENUMBER == TWICE_LINE)
	UBYTE	SYB_TTI_ID_Buffer[2][SYS_TTI_ID_MAX] ={0};
#else
	UBYTE	SYB_TTI_ID_Buffer[SYS_TTI_ID_MAX] ={0};
#endif

/************************************************************************
 * ライフモニタ															*
 * "\src\atlanta\define\syslifem.h"										*
 * syslifem.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_LifeMonitorData_t	SYB_LifeMonitor = {0};

/************************************************************************
 * 通信予約																*
 * "\src\atlanta\define\syscomf.h"										*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_COMMANDFILE_SRAM == ENABLE)
struct SYS_CommandData_t	SYB_CommandFile[SYS_COM_FILE_MAX] = {0};
#endif

#if (PRO_COMMANDFILE_SRAM == ENABLE)
/*#if (PRO_F_CODE == ENABLE)*/	/*	1997/01/09	By T.Yamaguchi */
/************************************************************************
 *	Fｺｰﾄﾞﾃﾞｰﾀ格納ﾊﾞｯﾌｧ			(ｺﾏﾝﾄﾞﾌｧｲﾙ登録用)	D-RAM領域に移動する予定
 ***********************************************************************/
struct SYS_FcodeNumberData_t	SYB_FcodeNumberCDataBuffer[SYS_COM_FILE_MAX * F_CODE_DATA_MAX] = {0};
/*#endif*/
#endif

#if (PRO_COMMANDFILE_SRAM == DISABLE)
/************************************************************************
 * コマンドファイルのステータス（コマンド消去リストプリントに使用）		*
 * 97/03/21																*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_CommandStatus[SYS_COM_FILE_MAX] = {0};
#endif

/************************************************************************
 * 発信スケジューラ														*
 * "\src\atlanta\define\sysexec.h"										*
 * sysexec.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if(0) /* 最終オフセットはチェックメッセージのテンポラリバッファとして使用 By H.Hirao 1996/06/17 */
//struct SYS_ExecQueueData_t SYB_ExecQueue[SYS_EXEC_QUEUE_MAX] = {0};
#endif
struct SYS_ExecQueueData_t	SYB_ExecQueue[SYS_EXEC_QUEUE_MAX+1] = {0};

#if defined (KEISATSU)		/* 警察FAX Added by SMuratec K.W.Q 2005/08/01 */
struct SYS_CommandKeisatsu_t SYB_ExecQueueKeisatsu[SYS_EXEC_QUEUE_MAX+1] = {0};
#endif		/* End of (defined (KEISATSU)) */

/************************************************************************/
/*	実行待ちﾌｧｲﾙの展開位置												*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UWORD	SYB_ExecQueueWritePoint = 0;

/************************************************************************/
/*	実行待ちﾌｧｲﾙの実行位置												*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UWORD	SYB_ExecQueueReadPoint = 0;

/************************************************************************
 * マルチコピー															*
 * "\src\atlanta\define\sysmcopy.h"										*
 * sysmcopy.jsw参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_MultiCopyData_t	SYB_MultiCopyFile[SYS_MULTI_COPY_MAX] = {0};
/*
 * マルチコピー位置
 * ・次にセットすべきSYB_MultiCopyFile[]の配列オフセット値
 * 　SYB_MultiCopyFile[SYB_MultiCopyPoint].StatusがSYS_MULTI_EMPTYでない
 * 　場合は、全てのｺﾋﾟｰ予約が実施されている
 * ・SYB_MultiCopyPoint+1からサイクリックにStatusがSYS_MULTI_PRINTである
 *	 SYB_MultiCopyFile[]をプリントする
 */
UBYTE	SYB_MultiCopyPoint = {0};		/* 要らんのと違うか要確認 橘ー＞小谷 ！！ */

/************************************************************************/
/*	ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの展開位置											*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UBYTE	SYB_MultiCopyWritePoint = 0;

/************************************************************************/
/*	ﾏﾙﾁｺﾋﾟｰ管理ﾌｧｲﾙの実行位置											*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UBYTE	SYB_MultiCopyReadPoint = 0;

/************************************************************************
 * メモリ受信原稿プリント												*
 * "\src\atlanta\define\sysmemrx.h"										*
 * sysmemrx.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_MemoryRxPrintData_t	SYB_MemoryRxPrint[SYS_MEMORY_RX_MAX] = {0};
/*
 * メモリ受信位置
 * ・次にセットすべきSYB_MemoryRxPrint[]の配列オフセット値
 * 　SYB_MemoryRxPrint[SYS_MemoryRxPoint].StatusがSYS_MEMORY_RX_EMPTYで
 *	 ない場合は、代行受信が一杯である
 * ・SYB_MemoryRxPoint+1からサイクリックにStatusがSYS_MEMORY_RX_PRINTで
 *	 あるSYB_MemoryRxPrint[]をプリントする
 */
UBYTE	SYB_MemoryRxPoint = {0};	/* この変数は使われていないのでは　1997/03/07  By T.Yamaguchi */

/************************************************************************/
/*	ﾒﾓﾘ受信ﾌﾟﾘﾝﾄ管理ﾌｧｲﾙ書き込み位置									*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UBYTE	SYB_MemoryRxPrintWritePoint = 0;

/************************************************************************/
/*	ﾒﾓﾘ受信ﾌﾟﾘﾝﾄ管理ﾌｧｲﾙ実行位置										*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UBYTE	SYB_MemoryRxPrintReadPoint = 0;

/************************************************************************/
/*	ﾎﾟ-ﾘｸﾞ原稿蓄積状態管理ﾃﾞ-ﾀ											*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UBYTE	SYB_PollingDocumentStatus = 0;

/************************************************************************/
/*	DBﾎﾟ-ﾘｸﾞ原稿蓄積状態管理ﾃﾞ-ﾀ										*/
/*	93/12/20															*/
/*	By S.Kawasaki														*/
/************************************************************************/
UBYTE	SYB_DB_PollingDocumentStatus = 0;

/************************************************************************
 * リダイヤルバッファ													*
 * sysrdial.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_RedialBuffer[SYS_REDIAL_BUF_MAX] = {0};
UBYTE	SYB_RedialBufWritePointer = 0;

/************************************************************************
 * 現在時間																*
 * 1992年1月1日0時0分0秒からの蓄積秒数									*
 * sysclock.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UDWORD	SYB_CurrentTime = 0;

/**********************************************************************
 * 受信確定時間
 * 1996/12/02 Y.Murata	POPLAR追加 1997/03/19  By T.Yamaguchi
 **********************************************************************/
UDWORD SYB_CurrentFaxReceiveTime = 0;


/************************************************************************
 * ワーディング番号														*
 * sysword.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_WordingNumber = 0;		/* 0～2 */

/************************************************************************
 * 受信モードスイッチ													*
 * "\src\atlanta\define\sysrxsw.h"										*
 * \src\rice\h8\doc\spec\sys_auto.jsw参照								*
 * sysrxsw.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_RxModeSwitch = 0;

/************************************************************************
 * 送信モードスイッチ													*
 * "\src\atlanta\define\sysmode.h"->sysdoc.h							*
 * sysmode.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_ModeSw = 0;

/************************************************************************
 * 原稿濃度スイッチ														*
 * "\src\atlanta\define\sysdens.h"										*
 * sysdens.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_DensitySw = 0;

/************************************************************************
 * コピー送信モードスイッチ（コピー／ファクス切り替え時）				*
 * 1997/02/27															*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_CopyModeSw = 0;

/************************************************************************
 * コピー原稿濃度スイッチ（コピー／ファクス切り替え時）					*
 * 1997/02/27															*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_CopyDensitySw = 0;

/************************************************************************
 * PBX番号																*
 * syscomf.jsw参照														*
 * syspbx.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
UBYTE	SYB_PBX_Number[SYS_PBX_NUMBER_MAX] ={0};

/************************************************************************
 * T30モニタ															*
 * "\src\atlanta\define\syst30.h"										*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_T30MonitorData_t	SYB_T30Monitor = {0}; /* By S.K Jan.17,1994 */

/************************************************************************
 * 送信回数																*
 * 1993/12/27															*
 * S.Kawasaki															*
 ************************************************************************/
UWORD	SYB_TxTotalCount = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
UWORD	SYB_TxTotalCountExt = 0;
#endif

/************************************************************************
 * 受信回数																*
 * 1993/12/27															*
 * S.Kawasaki															*
 ************************************************************************/
UWORD	SYB_RxTotalCount = 0;
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1998/03/11 */
UWORD	SYB_RxTotalCountExt = 0;
#endif

/************************************************************************
 *	通信証ｽｲｯﾁ															*
 * 1993/12/27															*
 * S.Kawasaki															*
 ************************************************************************/
UBYTE	SYB_ConfirmationReportSwitch = 0;

/************************************************************************
 *	通信管理自動出力状態												*
 * 1993/12/27															*
 * S.Kawasaki															*
 ************************************************************************/
#if (0) /* SYB_SettingStatus[]に移動したため削除します 1996/02/07 Eguchi */
//UBYTE SYB_JournalAutoStatus = 0;
#endif

/************************************************************************
 * 通信管理記録自動プリント・カウンタ－									*
 * 94/1/6																*
 * S.Kawasaki															*
 ************************************************************************/
UBYTE	SYB_AutoJournalCounter = 0;

/************************************************************************
 * 電話帳機能用データバッファ											*
 * 電話帳機能用データ登録件数											*
 * "\src\atlanta\define\systbok.h"										*
 * 1994/04/08	渡辺一章												*
 * #if (PRO_DIRECTORY == ENABLE)										*
 ************************************************************************/
#if (PRO_SPEED_DIAL_ADDITION == ENABLE)	/* 短縮２００件対応 by K.Watanabe 1998/06/04 */
UWORD	SYB_TelephoneBookData[SYS_TELBOOK_MAX + 1][2] = {0};
UWORD	SYB_TelBookDataEnd = {0};
#else
UBYTE	SYB_TelephoneBookData[SYS_TELBOOK_MAX + 1][2] = {0};	/* +1 By Eguchi 1996/03/26	*/
UBYTE	SYB_TelBookDataEnd = {0};								/* 1995/12/04　Eguchi */
#endif

/************************************************************************
 * ＤＲＡＭバックアップ用												*
 * 1994/08/15															*
 * 吉川弘康																*
 ***********************************************************************/
UDWORD	SYB_PowerOFF_StartTime = 0;
UDWORD	SYB_PowerON_StartTime = 0;

/************************************************************************
 * ＤＲＡＭバックアップ可能時間
 * 1994/11/02
 * 村田
 ***********************************************************************/
UDWORD	SYB_DRAM_BackupTime = 0;		/** ＤＲＡＭバックアップ可能時間 *//* 1994/11/02 Y.Murata */

/************************************************************************
 * 停電検出リストステータス
 * 1994/11/26
 * 村田
 ***********************************************************************/
UBYTE	SYB_PowerDownListStatus = 0;					/** 停電検出リストステータス *//* 1994/11/26 Y.Murata */

/**********************************************************************
*				By : NOBUKO
*			  Date : Tue 22 Nov. 1994
*					 ﾒﾓﾘ管理使用ﾃﾞｰﾀ
***********************************************************************/
UWORD	MEM_TopEmptyBlock = 0;							/** 空ブロックの先頭 */
UWORD	MEM_EndBlock = 0;								/** 空ブロックの最終 */
UWORD	MEM_TotalStoreBlockCounter = 0;					/** 蓄積済ブロックの総数 */
UWORD	MEM_TotalAvailableStoreBlkCnt = 0;				/** 蓄積可能ブロックの総数 */
UWORD	MEM_AvailableMaxFATArea = 0;					/** 有効FATエリアの最終ブロック */
UBYTE	MEM_DMAEndStatus = 0;							/** DMA終了時に使用 */
UWORD	MEM_MultiProgramOpenIndexNo[SYS_JOB_MAX] = {0};	/** XEROX仕様 マルチ・プログラム送信 に使用 */
UWORD	MEM_BlockCounterEndStatus = 0;					/** 使用ブロック数カウント時の最終ブロックの種別 */
UBYTE	MEM_ScanFlag = 0;								/** スキャン原稿蓄積フラグ */

/************************************************************************
 * モニタースピーカー出力 (ANZU)
 * 1995/12/02
 * 江口
 ***********************************************************************/
UBYTE	SYB_MonitorSpeakerOutLevel = 0;

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add By Y.Kano 2003/08/29 */
/************************************************************************
 * ブザー出力
 * 2003/08/29
 * 加納
 ***********************************************************************/
UBYTE	SYB_BuzzerOutLevel = 0;

/************************************************************************
 * リング出力
 * 2003/09/18
 * 加納
 ***********************************************************************/
UBYTE	SYB_RingOut = 0;
/************************************************************************
 * ＰＳ２デフォルト値
 * 2003/10/18
 * 加納
 ***********************************************************************/
UBYTE	SYB_PS2LimitValue = 0;
#endif

/************************************************************************
 * 部門コード　(ｱﾝｽﾞ)
 * 1995/12/02
 * 江口
 ***********************************************************************/
UWORD	SYB_DepartmentCode[SYS_DEPART_MAX + 1] = {0};

/************************************************************************
 * プロテクトパスコード　(ANZU)
 * 1995/12/02
 * 江口
 ***********************************************************************/
UWORD	SYB_ProtectPasscode = 0;

/************************************************************************
 * T30モニタ H-Fine(R12*15.4L/mm)表示用フラグ
 * 1996/04/10 T.Yamaguchi
 ************************************************************************/
UBYTE	SYB_T30_TxFrame300dpiFlag = 0;
UBYTE	SYB_T30_RxFrame300dpiFlag = 0;

/************************************************************************
 * トナー残量がわずかであると判断されてから印字可能な枚数をセットする。
 * この値が０以外から減算されて０になった時点でSYS_MachineStatus[SYS_PRINTER_STATUS]
 * のSYS_PRINTER_NO_INKがセットされ印字不可状態となる。
 * By S.Kawaski 1996/06/20
 *
 ************************************************************************/
UWORD	SYB_TonarEndPageCounter = 0;

/************************************************************************
 * 手差し原稿プリント													*
 * 96/06/27																*
 * by T.Soneoka															*
 ************************************************************************/
struct SYS_MultiCopyData_t	SYB_ManualCopyFile = {0};	/* ●ICHOU追加 by T.Soneoka 1996/06/28 */

/************************************************************************
 * セキュリティ受信用データ
 * 1996/04/27 Eguchi
 * #if (PRO_SECURITY_RX == ENABLE)
 ************************************************************************/
UBYTE	SYB_SecurityRxModeFlag = 0;		/* セキュリティ受信モード中フラグ */
UDWORD	SYB_SecurityRxModeStartTime = 0;/* セキュリティ受信モード開始時刻(比較用） */
UWORD	SYB_SecurityRxSettingTime = 0;	/* セキュリティ受信モード開始時刻オペレーション設定値を０時０分（日の始め）からの積算分になおしたもの*/

/************************************************************************
 * セキュリティ受信モード中、受信メモリーオーバーチェックメッセージ
 * プリント要求フラグ
 * 1996/06/28　Eguchi
 * #if (PRO_SECURITY_RX == ENABLE)
 ************************************************************************/
UBYTE	SYB_SecurityRxChkMsgRequest = 0;

/************************************************************************
 * セキュリティ受信モード中、受信メモリーオーバーチェックメッセージ
 * プリント済みフラグ
 * 1996/06/28　Eguchi
 * #if (PRO_SECURITY_RX == ENABLE)
 ************************************************************************/
UBYTE	SYB_SecurityRxChkMsgPrint = 0;

/**********************************************************************
 * 連続ポーリングコマンドデータ
 * 1996/10/17 Eguchi
 * #if (PRO_CONTINUOUS_POLLING == ENABLE)
 **********************************************************************/
struct	SYS_ContinuousPollingData_t	SYB_ContinuousPolling = {0};

/************************************************************************
 * ダイヤル・イン待機モードでダイヤル・イン回線に接続されている場合　(0)*
 * ダイヤル・イン待機モードでダイヤル・イン回線に接続されていない場合(1)*
 * Feb.15'94	坂本直史												*
 * #if (PRO_DIALIN == ENABLE)											*
 ************************************************************************/
UBYTE	SYB_DialInNoNumberSignal = 0;

/************************************************************************
 * ダイヤルイン															*
 * "\src\atlanta\define\sysdiali.h"										*
 * sysdiali.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 * #if (PRO_DIALIN == ENABLE)											*
 ************************************************************************/
struct SYS_DialinData_t	SYB_Dialin = {0};

/************************************************************************
 * リングマスターパターン自動検出機能									*
 * 95/5/25																*
 * T.Hiraoka															*
 * #if (PRO_RING_MASTER == ENABLE)										*
 ************************************************************************/
struct SubRingMaster_t	SYB_TeachingPattern[2] = {0};
UBYTE	SYB_RingG_SetNumber = 0;
UBYTE	SYB_RingH_SetNumber = 0;

/************************************************************************
 * ＤＥＵ（ドイツ仕様）ダイアル失敗カウンター							*
 * 1994/02/07 Y.Murata													*
 * #if defined(DEU)														*
 ************************************************************************/
UBYTE	SYB_DEUDialerFaultCounter = 0;

/************************************************************************
 * MercuryTone検出時間													*
 * 1994/11/17	 by.M.HARADA/* by SMuratec C.P 2004/07/08 for prefix    *
 * #if defined(GBR) || defined(STOCKHM2) 								*
 ************************************************************************/
UWORD	SYB_MercuryPauseTime = 0;

/************************************************************************
 * 料金管理テーブル														*
 * "\src\atlanta\define\syscost.h"										*
 * syscost.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 * #if (PRO_COST == ENABLE)												*
 ************************************************************************/
struct SYS_CostBaseTable_t	SYB_CostTable[SYS_COST_TABLE_MAX] = {0};
/*By Y.Suzuki 1998/03/15 */
/*struct SYS_NTT_AccessData_t	SYB_NTT_AccessFile[SYS_SPEED_DIAL_MAX + SYS_2ND_SPEED_DIAL_MAX + SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX] = {0};*/
struct SYS_NTT_AccessData_t	SYB_NTT_AccessFile[SYS_SPEED_DIAL_MAX_BKUP + SYS_2ND_SPEED_DIAL_MAX + SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX] = {0};


#if (0)	/* By M.Tachibana 1997/05/26 */
//#if (PRO_BRANCH_RX == ENABLE)
///************************************************************************
// * ＣＭＬリレーＯＮ時のブランチＯＨ検出基準電圧						*
// * 94/9/12															*
// * T.Hiraoka															*
// ************************************************************************/
//UBYTE	SYB_CML_BRCOhLevel = 0;
//#endif
//
//#if (PRO_BRANCH_RX == ENABLE)
///**************************************************************************************/
///* 電源投入時にＢＲＣ　ＴＥＬがＯＮ　ＨＯＯＫされていることを確認後、本来動作に移る為 */
///*												   未確認(0)						  */
///*													 確認(1)						  */
///*		 May.11'94					 坂本直史										  */
///**************************************************************************************/
//UBYTE	SYB_BRC_OnHook_DetectFlag = 0;
//#endif
#endif

/************************************************************************
 * 通信でFIP受信かどうかを判断するフラグ								*
 * 1995/02/15	sys_data.cより移動										*
 * 橘正樹																*
 * #if (PRO_FIP == ENABLE)												*
 ************************************************************************/
UBYTE	SYB_FIP_ReceiveEnableFlag = 0;

/************************************************************************
 * シェーディング領域													*
 * "\src\atlanta\define\sysshad.h"										*
 * 1993/11/27															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
  #if defined(SATSUKI2) || defined(STOCKHM2)
	UBYTE	SYB_WhiteShadingRAM[SYS_SHADING_MAX] = {0};
	UBYTE	SYB_BlackShadingRAM[SYS_SHADING_MAX] = {0};
  #else
	UBYTE	SYB_ShadingRAM[SYS_SHADING_MAX] = {0};
  #endif
	UBYTE	SYB_BlackCorrectionData = 0;
	UBYTE	SYB_AgcDaHighReference = 0;
	UBYTE	SYB_AgcDaLowReference = 0;
#else
	UBYTE	SYB_InitialRAM[SYS_INITIAL_MAX] = {0};
	UBYTE	SYB_ShadingRAM[SYS_SHADING_MAX] = {0};
	UBYTE	SYB_PeakData = 0;		/* Add By J.Miyazaki '94.07/07 */
#endif

/*	ミラーキャリッジ輸送モードの状態記憶用
**	1997/03/05 s.takeuchi
*/
UBYTE	SYB_ScannerTransportMode = 0;

/************************************************************************
 * プリンタライフモニタ													*
 * "\src\atlanta\define\syslifem.h"										*
 * 1997/04/11															*
 * 橘正樹																*
 ************************************************************************/
/*#if (PRO_PRINT_TYPE == LED)*/
struct SYS_PrinterLifeMonitorData_t	SYB_PrinterLifeMonitor = {0};
UBYTE	SYB_PrinterTonerData[SYS_TONER_DATA_AREA_MAX] = {0};		/* 1997/12/16 */
/*#endif*/

/************************************************************************
 * 通信エラーモニタ														*
 * "\src\atlanta\define\syslifem.h"										*
 * 1997/06/23															*
 * 橘正樹																*
 ************************************************************************/
struct SYS_FaxComErrorMonitorData_t	SYB_FaxComErrorMonitor[SYS_FAXCOM_ERROR_LINE_MAX][SYS_FAXCOM_ERROR_MONITOR_MAX] = {0};

/************************************************************************
 * 消耗品発注用紙プリント要求											*
 * 1997/09/06															*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_ConsumerOrderListRequest = 0;

/************************************************************************
 * 消耗品発注データ														*
 * struct SYS_ConsumerOrderData_t SYB_ConsumerOrder						*
 * 1997/09/18															*
 * 橘正樹																*
 ************************************************************************/
struct SYS_ConsumerOrderData_t	SYB_ConsumerOrder = {0};

/************************************************************************
 * ドラムヒューズカット要求												*
 * 1997/10/13															*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_DrumFuseCutRequest = 0;

/************************************************************************
 * ジャンクメールチェック用バッファ										*
 * 1997/10/21															*
 * 山口哲治																*
 ************************************************************************/
UWORD	SYB_OnetouchJunkDial[SYS_ONETOUCH_MAX] = {0};
/*UWORD	SYB_SpeedJunkDial[SYS_SPEED_DIAL_MAX] = {0};By Y.Suzuki 1998/03/15 */
UWORD	SYB_SpeedJunkDial[SYS_SPEED_DIAL_MAX_BKUP] = {0};

/************************************************************************
 * 実行キュー検索ポインター												*
 * 1997/10/28 Y.Murata													*
 ************************************************************************/
UWORD	SYB_ExecQueueSerchPoint = 0;

/************************************************************************
 * 部門別料金管理のトータル時間											*
 * "\src\atlanta\define\sysdeprt.h"										*
 * 1997/12/09															*
 * 本多智幸																*
 * #if (PRO_DEPART_NEW_LIST == ENABLE)									*
 ************************************************************************/
struct SYS_DepartManageTime_t SYB_DepartManageTimeFile[SYS_DEPART_MAX] = {0};

/************************************************************************
 * 簡易時間部門管理の開始日時											*
 * 1992年1月1日0時0分0秒からの蓄積秒数									*
 * PRO_DEPART_NEW_LIST == ENABLE の時使用								*
 * 1997/12/12															*
 * 福井知史																*
 ************************************************************************/
UDWORD	SYB_DepartManageStartTime = 0;


/************************************************************************
 * バックアップRAMテスト												*
 * 機種名を記憶する														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
/* 上にあったものを下に移動 By M.Tachibana 1997/12/16 */
/* これより上に追加するとＲＡＭクリアがかかる */
UBYTE	SYB_BackupRAM_TestArea[SYS_BACKUP_RAM_TEST_AREA_MAX] = {0};


#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)
/************************************************************************
 * 消耗品発注データ２													*
 * 1998/05/18															*
 * 本多智幸		orderbythonda1998/05/18									*
 ************************************************************************/
UBYTE	SYB_ConsumerOrderFromSection2[SYS_ORDER_NAME_MAX] = {0};
#endif


#if (PRO_KEYPANEL == PANEL_POPLAR_B) && !defined(JPN)  /* lifemonitorbythonda1998/06/01 */
/************************************************************************
 * ライフモニタクリアパスコード											*
 * 1998/06/01															*
 * 本多智幸																*
 ************************************************************************/
UWORD	SYB_LifeMonitorPasscode = 0;
#endif

#if (PRO_RX_DOC_TRANSFER == ENABLE)
/************************************************************************
 * ワープ機能用データ													*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
struct SYS_SubDialData_t SYB_WarpFile[SYS_WARP_MAX] = {0};
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/15 By M.Kuwahara */
/************************************************************************
 * ナンバーディスプレイ機能用データ										*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
UBYTE SYB_NumberDisplayTel = 0;
struct SYS_NumberDisplayTable SYB_NumberDisplay[SYS_ND_MAX] = {0};
/************************************************************************
 * ナンバーディスプレイ機能の着信履歴データ								*
 * 1998/08/18															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_NumberDisplayJournalTable SYB_NumberDisplayJournal[SYS_ND_JRNL_MAX] = {0};
/*
 * ナンバーディスプレイ着信履歴の記録位置
 * ・次にセットすべきSYB_NumberDisplayJournal[]の配列オフセット値
 */
UBYTE   SYB_NumberDisplayJournalPoint = 0;    /* initialization code added by H.Kubo 1998/10/13 */
#endif

#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/17 By M.Kuwahara */
/************************************************************************
 * キーマクロ機能用データ												*
 * 1998/06/17															*
 * 桑原美紀																*
 ************************************************************************/
struct SYS_KeyMacroTable SYB_KeyMacro[SYS_KEYMACRO_MAX] = {0};
#endif

#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1998/07/01 By M.Kuwahara */
/************************************************************************
 * ＬＣＤ濃度調整用データ												*
 * 1998/07/01															*
 * 桑原美紀																*
 ************************************************************************/
UBYTE	SYB_ContrastLCD = 0;
#endif

#if (PRO_FCODE_RELAY == ENABLE)
/************************************************************************
 * 中継配信コマンドナンバーからＦコードボックスナンバーをたどるための変数*
 * 1998/07/16															*
 * H.Hirao																*
 ************************************************************************/
	UBYTE SYB_FcodeBoxNoByRelayedTxComNo[SYS_COM_FILE_MAX] = {0};
#endif


#if defined(US1)
/************************************************************************
 * 消耗品発注データ 発注先Ｆａｘ Ｎｏ．＆ 発注先Ｔｅｌ Ｎｏ．			*
 * 																		*
 * 本多智幸		orderbythonda1998/11/11									*
 ************************************************************************/
UBYTE	SYB_ToCompanyFaxNumber[SYS_ORDER_DIAL2_MAX] = {0};
UBYTE	SYB_ToCompanyTelNumber[SYS_ORDER_DIAL2_MAX] = {0};
#endif



/* #if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) 1998/03/31  By T.Yamaguchi */
/* オプションデータクリア／オールラムクリア／メモリスイッチ等の条件でクリアしなければならない */
/* 要検討 */
UBYTE	SYB_FlashROM_WriteStatus = 0;
UWORD	SYB_ROM_DataSumcheck = 0;
/* #endif */

#if (PRO_MULTI_TTI == ENABLE)
/* オプションバックアップＲＡＭ領域溢れのため、標準バックアップ領域に持っていきます。 By O.Kimoto 1998/07/09 */
/************************************************************************
 * 発信元名(ｶﾅID)														*
 ************************************************************************/
UBYTE	SYB_Multi_TTI_ID_Buffer[SYS_MULTI_MAX][SYS_TTI_ID_MAX] = {0};
#endif

#if defined(POPLAR_F)
/************************************************************************
 * Ｔ３０モニタ管理ステータス
 *   ジャーナル分Ｔ３０モニタを確保するための管理ステータス
 ************************************************************************/
UBYTE SYB_T30MonitorDRAM_Status[SYS_JOURNAL_MAX] = {0};
#endif

#if defined(HINOKI2) || defined (HINOKI3) || defined(SATSUKI2) || defined(STOCKHM2)	/*  (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103) 朱色読取り用データエリア by O.Kimoto 2002/02/27 */
 #if (PRO_RED_SCAN == ENABLE)	/* 朱色原稿読み取り 2002/03/04 T.Takagi */
	UBYTE	SYB_ShadingRAM_ForRedScan[SYS_SHADING_MAX] = {0};
	UBYTE	SYB_BLK_CorrectionDataForRedSCN = 0;
	UBYTE	SYB_AgcDaHighReferenceForRedSCN = 0;
	UBYTE	SYB_AgcDaLowReferenceForRedSCN = 0;
 #endif
#endif

#if defined(HINOKI2) || defined (HINOKI3)	/* LC821033仕様対応 Y.Kano 2003/11/28 */
UBYTE	SYB_WhiteShadingRAM[SYS_SHADING_MAX] = {0};
UBYTE	SYB_BlackShadingRAM[SYS_SHADING_MAX] = {0};
/************************************************************************
 * 画処理選択フラグ														*
 * 初期化時、MRD9801のPGB9ポートを読んで、								*
 *							HighならSYB_LC821033_FlgをONにする			*
 *						    LOwならSYB_LC821033_FlgをOFFにする			*
 *																		*
 * SYB_LC821033_FlgがONの時、ＬＣ８２１０３３仕様の画処理を行う。		*
 *                  OFFの時、ＬＣ８２１０３仕様の画処理を行う。			*
 * 2003/12/03															*
 * Y.Kano																*
 ************************************************************************/
UBYTE	SYB_LC821033_Flg = 0;		/* LC821033対応フラグ */
UBYTE	SYB_PS2_SensorStatus = 0;	/* ＰＳ２自動調整機能 by Y.Kano 2004/04/05 */
 #if defined(HINOKI3)	/* LC821033専用のシェーディングＲＡＭの追加 by Y.Kano 2005/01/24 */
UBYTE	SYB_WhiteShadingRAM_ForRedScan[SYS_SHADING_MAX] = {0};		/* 朱色用白シェーディングＲＡＭ */
UBYTE	SYB_BlackShadingRAM_ForRedScan[SYS_SHADING_MAX] = {0};		/* 朱色用黒シェーディングＲＡＭ */
 #endif
#endif

#pragma section


/* これより上には絶対にデータを追加しないで下さい　*/

/*★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★*/

/* オプション関係のバックアップデータはここよりも下に追加して下さい */


#pragma section BKUPRAM_OPTION		/* セクション指定 */

/*#if (PRO_DPRAM == ENABLE)*/	/* J.Miyazaki 1996/08/10 */
/************************************************************************
 * オプションボードのＲＯＭバージョン									*
 * 97/03/24																*
 * M.Kotani																*
 ************************************************************************/
UWORD	SYB_OptionROM_Revision[SYS_OPTION_BOARD_MAX][OPTION_ROM_REVISION_WORD_MAX] = {0};
/************************************************************************
 * ＤＰＲＡＭ通信履歴													*
 * 96/09/04																*
 * M.Kotani																*
 ************************************************************************/
UWORD	DPR_SamplingTxBuffer[DPR_MAX_SAMPLING] = {0};		/** 過去１０通信の履歴を記録するバッファ */
UWORD	DPR_SamplingTxSaveBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingTxResetBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingTxPointer = 0;						/** 過去１０通信の履歴を残す */
UWORD	DPR_SamplingRxBuffer[DPR_MAX_SAMPLING] = {0};		/** 過去１０通信の履歴を記録するバッファ */
UWORD	DPR_SamplingRxSaveBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingRxResetBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingRxPointer = 0;						/** 過去１０通信の履歴を残す */
UWORD	DPR_ErrorCode = 0;				/** エラーコードを保存する */
UWORD	DPR_SamplingUpTxSaveBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingUpTxResetBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingDownRxSaveBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */
UWORD	DPR_SamplingDownRxResetBuffer[DPR_MAX_SAMPLING] = {0};	/** リセット後の過去１０通信の履歴を残す */

/* #if (PRO_PC_PRINT == ENABLE)*/	/* J.Miyazaki 1996/08/10 */
/************************************************************************
 * ＰＣ受信原稿プリント													*
 * "\src\atlanta\define\syspcrx.h"										*
 * 1996/08/10															*
 * 宮崎仁一																*
 ************************************************************************/
struct SYS_PcRxPrintData_t	SYB_PcRxPrint = {0};

/* #endif*/	/* #if (PRO_PC_PRINT == ENABLE) */
/*#endif*/	/* #if (PRO_DPRAM == ENABLE) */

/*#if (PRO_CLASS1 == ENABLE)*/
/***********************************************************************
 * ローカルスキャン原稿蓄積状態
 * 0:原稿なし。1:原稿あり
 * 1996/09/24 Eguchi
 ***********************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998 */
UBYTE	SYB_CL1_LocalScanDocStatusSram = 0;
#else
UBYTE	SYB_CL1_LocalScanDocStatus = 0;
#endif

/***********************************************************************
 * ローカルプリント原稿管理テーブル
 * 1996/09/24 Eguchi
 * CL1FDATA.Cより移動
 ***********************************************************************/
struct SYS_MemoryRxPrintData_t	SYB_CL1_MemoryRxPrint[SYS_MEMORY_RX_MAX] = {0};
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998  */
UBYTE	CL1_MemoryRxPrintWritePointSram = 0;
#else
UBYTE	CL1_MemoryRxPrintWritePoint = 0;
#endif
UBYTE	CL1_MemoryRxPrintReadPoint = 0;
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui Jun.19,1998  */
UBYTE	CL1_PCDocumentCodeSram = 0;
UBYTE	CL1_PCDocumentModeSram = 0;
UBYTE	CL1_PCDocumentSizeSram = 0;
#else
UBYTE	CL1_PCDocumentCode = 0;
UBYTE	CL1_PCDocumentMode = 0;
UBYTE	CL1_PCDocumentSize = 0;
#endif
/*#endif*/	/* #if (PRO_CLASS1 == ENABLE) */


/*#if (PRO_MULTI_LINE == ENABLE)*/	/* Add By O.Kimoto 1996/11/08 */
/************************************************************************
 * オプションボード用発信元電話番号
 * By O.Kimoto 1996/11/8
 ************************************************************************/
	UBYTE	SYB_Option_ID_Buffer[SYS_OPTION_BOARD_MAX][SYS_ID_MAX] = {0};

/**********************************************************************
 * オプションボード用発信元名(送信原稿先頭付加用)
 * By O.Kimoto 1996/11/8
 **********************************************************************/
	UBYTE	SYB_Option_TTI_Buffer[SYS_OPTION_BOARD_MAX][SYS_TTI_MAX] = {0};

/**********************************************************************
 * オプションボード用発信元名(かなＩＤ)
 * 1997/05/23
 * 清水政貴
 **********************************************************************/
/*#if (PRO_PANEL == KANJI)*/
	UBYTE	SYB_Option_TTI_ID_Buffer[SYS_OPTION_BOARD_MAX][SYS_TTI_ID_MAX] = {0};
/*#endif*/

/**********************************************************************
 * 内線－＞外線発呼用アクセス番号
 * By O.Kimoto 1996/11/8
 **********************************************************************/
#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	UBYTE	SYB_PbxAccessNumber[SYS_OPTION_BOARD_MAX][INTERNAL_LINE_MAX][SYS_ACCESS_NUMBER_MAX] = {0};
#else
	UBYTE	SYB_PbxAccessNumber[SYS_OPTION_BOARD_MAX][SYS_ACCESS_NUMBER_MAX] = {0};
#endif

/**********************************************************************
 * ポーリング原稿排他処理用変数
 * By O.Kimoto 1996/11/11
 **********************************************************************/
	UWORD	SYB_PollingDocExclusiveFlag = 0;	/* ポーリング原稿があるかどうかの変数 */

/**********************************************************************
 * オプションボード代行受信ポインター格納バッファ
 * 1996/12/02 Y.Murata
 **********************************************************************/
	UWORD	SYB_OptionMemoryRxWritePoint[SYS_OPTION_BOARD_MAX] = {0};

/**********************************************************************
 * オプションボード送信ジャーナルナンバー
 * 1996/12/02 Y.Murata
 **********************************************************************/
	UWORD	SYB_OptionJournalTxTotalCount[SYS_OPTION_BOARD_MAX] = {0};

/**********************************************************************
 * オプションボード受信ジャーナルナンバー
 * 1996/12/02 Y.Murata
 **********************************************************************/
	UWORD	SYB_OptionJournalRxTotalCount[SYS_OPTION_BOARD_MAX] = {0};

/*#endif*/	/** (PRO_MULTI_LINE == ENABLE) Add BY H.Hirao 1997/03/07 */

/*#if (PRO_CIPHER == ENABLE)*/	/*	By Y.Suzuki 1997/06/02	*/
/************************************************
*	アリロー設定、キーブック用バックアップデータ
*	By Y.Suzuki 1997/06/02
*************************************************/
struct KeyBookTbl_t	SYB_KeyBookData = {0};
/************************************************
*	アリロ受信ボックス用データ
*	By Y.Suzuki 1997/06/12
************************************************/
struct CipherBoxData_t SYB_CipherBox[SYS_CIPHERBOX_MAX] = {0};
/*#endif*/

/**********************************************************************
 * F-150 Low Toner時のプリント枚数制限処理
 * 後々、F-120にも入れなければならない仕様です。
 * By O.Kimoto 1996/12/26
 **********************************************************************/
WORD SYB_RestPrintPages = 0;

/**********************************************************************
 * ＰＯＰＬＡＲ＿Ｈ用Ｐｈｏｎｅ２の属性を記憶する変数
 * ０：標準回線
 * １：Ｅｘｔ．Ｌｉｎｅ
 * By O.Kimoto 1997/08/07
 **********************************************************************/
UBYTE SYB_Phone2Attribute = 0;

/**********************************************************************
 * 暗号化送信用キーデータ（プログラムワンタッチ登録用）
 * 1997/12/19
 * 渡辺一章
 * #if (PRO_CIPHER == ENABLE)
 **********************************************************************/
/*struct SYS_CipherTxData_t SYB_CipherPData[SYS_PROGRAM_MAX] = {0}; define name change 1998/02/19 Y.Murata */
struct SYS_CipherTxData_t SYB_CipherPData[SYS_PROGRAM_MAX_BKUP] = {0};

/***********************************************************************
 * 暗号化受信解除プリント原稿管理テーブル
 * By Y.Suzuki 1998/01/08
 * Cipher (CPH)
 ***********************************************************************/
struct SYS_MultiCopyData_t	SYB_CPH_RxPrint[SYS_CIPHERBOX_MAX] = {0};
UBYTE SYB_CipherPrintItem = 0;/* スクランブル送信予約原稿の解除、又はスクランブル受信原稿の解除 */
UBYTE SYB_CipherPrintNo = 0;/* ０から９ */
#if (0)
//UBYTE	CHP_MemoryRxPrintWritePoint = 0;
//UBYTE	CHP_MemoryRxPrintReadPoint = 0;
#endif

/**********************************************************************
 * 拡張ＲＯＭバージョン
 * 1998/02/27
 * 渡辺一章
 **********************************************************************/
UBYTE SYB_ExtRomRevision[SYS_EXT_ROM_MAX][ROM_REVISION_MAX] = {0};


/*************************************************************
 **	インターネットＦＡＸオプション用　ＢａｃｋＵｐデータ	**
 **	開発中に追加していくオプションですので、とりあえず		**
 **	条件コンパイルで切り分けときます。						**
 **	By Y.Tanimoto 1998/03/10								**
 *************************************************************/
/*↓↓↓↓↓↓↓↓↓↓↓ここから↓↓↓↓↓↓↓↓↓↓↓↓*/
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
/****************************************
 **	ワンタッチ登録用メールアドレスデータ
 ****************************************/
struct		SYS_INF_OnetouchData_t		SYB_INF_Onetouch[SYS_ONETOUCH_MAX] = {0};
UBYTE		SYB_INF_OnetouchStatus[SYS_ONETOUCH_MAX]  = {0};

/******************************************
 **	Ｐワンタッチ登録用メールアドレスデータ
 ******************************************/
UBYTE		SYB_INF_MailGroup[SYS_PROGRAM_MAX][SYS_INF_ONETOUCH_POSITION_MAX] = {0};
UBYTE		SYB_INF_ProgramOnetouchStatus[SYS_PROGRAM_MAX]  = {0};

/******************************************
 **	ユーザーデータ登録用データ
 ******************************************/
struct		SYS_INF_UserData_t			SYB_INF_UserData[SYS_INF_USER_MAX] = {0};
struct		SYS_INF_UserDataStatus_t	SYB_INF_UserDataStatus[SYS_INF_USER_MAX] = {0};
UBYTE		SYB_INF_ClearAllAccountReq = 0;

/******************************************
 **	通信予約管理用データ
 ******************************************/
struct		SYS_INF_MailCommandStatus_t		SYB_INF_MailCommandStatus[SYS_INF_MAIL_COM_MAX] = {0};
UBYTE		SYB_INF_ErasedMailComRequest[SYS_INF_USER_MAX] = {0};	/* コマンド消去通知印字要求 */

/******************************************
 **	受信管理テーブル管理用データ
 ******************************************/
struct		SYS_INF_RxMailBoxStatus_t		SYB_INF_RxMailBoxStatus[SYS_INF_MAIL_BOX_MAX] = {0};
UBYTE		SYB_INF_ErasedRxMailRequest[SYS_INF_USER_MAX] = {0};	/* 受信原稿消去の通知印字要求 */

/******************************************
 * エンジンボード接続状態
 * 1998/04/20 Eguchi
 ******************************************/
UBYTE	SYB_INF_DeviceExist = 0;

/*****************************************
 * ﾕｰｻﾞﾃﾞｰﾀ設定状態
 * 1998/04/20 Eguchi
 ******************************************/
UBYTE	INF_AccessUserData = 0;

/*************************************
 *ボーレート
 *1998/04/20 Eguchi 
 *************************************/
UBYTE	INF_SerialSpeed = 0;

#endif /*End of (PRO_DIALUP_INTERNET_FAX == ENABLE)*/
/*↑↑↑↑↑↑↑↑↑↑↑ここまで↑↑↑↑↑↑↑↑↑↑↑↑*/

#if (PRO_MULTI_TTI == ENABLE)
/************************************************************************
 * マルチ発信元															*
 * 1998/05/25															*
 * 木元 修																*
 ************************************************************************/
/************************************************************************
 * 発信元電話番号														*
 ************************************************************************/
UBYTE	SYB_Multi_ID_Buffer[SYS_MULTI_MAX][SYS_ID_MAX] = {0};

/************************************************************************
 * 発信元名																*
 * 漢字有りの機種では、送信原稿先頭付加専用のバッファになる				*
 ************************************************************************/
UBYTE	SYB_Multi_TTI_Buffer[SYS_MULTI_MAX][SYS_TTI_MAX] = {0};

#if (0)
** 	/* オプションバックアップＲＡＭ領域溢れのため、標準バックアップ領域に持っていきます。 By O.Kimoto 1998/07/09 */
** #if (1)	/* マルチＴＴＩ仮名ＩＤ対応 By H.Fujimura 1998/07/07 */
** /************************************************************************
**  * 発信元名(ｶﾅID)														*
**  ************************************************************************/
** UBYTE	SYB_Multi_TTI_ID_Buffer[SYS_MULTI_MAX][SYS_TTI_ID_MAX] = {0};
** #endif
#endif

#endif

#if (PRO_CL1_TELFAX_LAN == ENABLE) 
/*　Class1で接続されているホストがSalutationかどうかを記憶する変数　*/
/*　ＡＮＺＵより移植 S.Fukui Jun 19,1998							*/
 #if (PRO_EX_CLASS1 == ENABLE)	
UBYTE	SYB_CL1_SalutationSram = 0;
 #else
UBYTE	SYB_CL1_Salutation = 0;
 #endif
#endif


#if (PRO_SGP_TEST_ROM == ENABLE) /** By S.Wang 98/07/25 */
UBYTE SYB_AutoSgpReportCounter = 0;
UDWORD SYB_NumberTotalCount = 0;
struct SYS_PerformanceData_t	SYB_PerformanceFile[SYS_SGP_REPORT_MAX];
#endif

#if (PRO_NUMBER_DISPLAY == ENABLE) /* added by H.Kubo 1998/10/12 */
UBYTE	SYB_ND_CarPattern[SYS_ND_CAR_PATTERN_MAX] = {0};
#endif

#if (PRO_FORVAL_LCR1 == ENABLE) /* By H.Fujimura 2002/07/11 */
/************************************************************************
 * 市外局番
 ************************************************************************/
UBYTE SYB_AreaCode[10 + 1] = {0};
#endif

/************************************************************************
 * 通信管理記録日報プリント 前回印字データ配列番号
 ************************************************************************/
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/27 */
UBYTE SYB_DailyReportPrintPos = 0;
#endif

#if defined (KEISATSU)

/************************************************************************
	拡張回線用受信モードスイッチ(警察FAXでは警電回線に使用)
											2005/06/06 石橋正和
************************************************************************/
UBYTE SYB_RxModeSwitchExt = 0;

/************************************************************************
	通信予約コマンドの警察FAX属性
											2005/06/22 石橋正和
************************************************************************/
struct SYS_CommandKeisatsu_t SYB_CommandKeisatsu[SYS_COM_FILE_MAX] = {0};

#endif /* #if defined (KEISATSU) */


/*これより上に登録してください*/
/*######################################################################*/
/* ＳＲＡＭをクリアする先頭アドレス										*/
/*######################################################################*/
/*WORD	SYB_SRAMClearStartAddress = 0;	By M.Tachibana 1997/05/28 */

#pragma section


#pragma section DRAM_TEST		/* セクション指定 */

/************************************************************************
 * ＤＲＡＭバックアップテスト・エリア									*
 * 1997/10/31															*
 * 橘正樹																*
 ************************************************************************/
UBYTE	SYB_DRAM_BackupTestArea[SYS_DRAM_BACKUP_TEST_AREA_MAX] = {0};

#pragma section


#if defined(POPLAR_F)
#pragma section DRAM_T30		/** セクション指定 DRAM_T30 */
/************************************************************************
 * T30モニタをジャーナル分もたせる										*
 ************************************************************************/
struct SYS_T30MonitorData_t	SYB_T30MonitorDRAM[SYS_JOURNAL_MAX] = {0};
UBYTE  SYB_CompatibleErrorCode[SYS_JOURNAL_MAX] = {0};
#pragma section		/** セクション指定の最後 DRAM_T30 */
#endif

