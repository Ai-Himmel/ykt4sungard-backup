/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_PDWN.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: 停電検出通知
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include 	"\src\atlanta\define\apl_msg.h"
#include 	"\src\atlanta\define\std.h"
#include 	"\src\atlanta\define\sys_pdwn.h"/*94/11/26 By j.masuda*/
/* #include 	"\src\kobe\anzu\define\sys_remo.h" Oct.3,1995 By S.K */

#include 	"\src\atlanta\define\cmn_def.h"
#include	"\src\atlanta\define\lst_def.h"
#include	"\src\atlanta\define\mem_def.h"

#include 	"\src\atlanta\define\cmn_pro.h"
#include	"\src\atlanta\define\lst_pro.h"
#include	"\src\atlanta\define\mem_pro.h"

#include 	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include 	"\src\atlanta\ext_v\sys_data.h"

#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング機能追加 1996/10/18 Eguchi */
#include	"\src\atlanta\define\syscntpl.h" /* 1996/10/16 Eguchi */
#endif


/*************************************************************************
	module		:[停電検出通知印刷]
	function	:[停電検出通知を印刷する]
	common		:[]
	condition	:[]
	commment	:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD 			Print_PowerOff_Notice(
						 void )			/*なし*/
{
	register WORD		ret;				/*実行結果*/
	register WORD		all_ret;			/*全体実行結果*/

	all_ret = MSG_PRN_LST_NO_LIST;
	/*親展受信消去通知*/
	ret = Print_DelSecure_Notice( LST_POWEROFF_NOTICE );
	if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
		/*ｲﾆｼｬﾙ*/
		Init_AnyList( LST_DELSECURE_NOTICE );	 	/*親展受信消去通知*/
#if (PRO_F_CODE == ENABLE)
		Init_AnyList( LST_DEL_FCODE_BOX_DOC_NOTICE ); /*Ｆコード原稿消去通知*/
#endif
		Init_AnyList( LST_DELMEMORYRCV_NOTICE ); 	/*代行受信消去通知*/
		Init_AnyList( LST_DELRESERVECMD_NOTICE );	/*通信予約消去通知*/
		Init_AnyList( LST_DELPOLLING_NOTICE );		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
#if ( PRO_BATCH_TX == ENABLE )
		Init_AnyList( LST_DELBATCHTXDOC_NOTICE );	/*一括送信原稿消去通知*/
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング追加　1996/10/18　Eguchi */
		Init_AnyList(LST_DELCONTPOLLCMD_NOTICE);	/** 連続ポーリングコマンド消去通知 */
#endif
		Init_AnyList( LST_POWEROFF_NOTICE );		/*停電検出通知*/
		return ( ret );
	}
	if ( ret == OK ) {
		all_ret = OK;
	}

	/* Ｆコード原稿消去通知 */
#if (PRO_F_CODE == ENABLE)	/* ANZU_LはＦコードないため 1997/06/18 Y.Matsukuma */
	ret = Print_Del_F_CodeBoxDoc_Notice( LST_POWEROFF_NOTICE );
	if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
		/*ｲﾆｼｬﾙ*/
/* #if (PRO_F_CODE == ENABLE) */	/* 1997/06/18 Y.Matsukuma */
		Init_AnyList( LST_DEL_FCODE_BOX_DOC_NOTICE ); /*Ｆコード原稿消去通知*/
/* #endif */
		Init_AnyList( LST_DELMEMORYRCV_NOTICE ); 	/*代行受信消去通知*/
		Init_AnyList( LST_DELRESERVECMD_NOTICE );	/*通信予約消去通知*/
		Init_AnyList( LST_DELPOLLING_NOTICE );		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
#if ( PRO_BATCH_TX == ENABLE )
		Init_AnyList( LST_DELBATCHTXDOC_NOTICE );	/*一括送信原稿消去通知*/
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング追加　1996/10/18　Eguchi */
		Init_AnyList(LST_DELCONTPOLLCMD_NOTICE);	/** 連続ポーリングコマンド消去通知 */
#endif
		Init_AnyList( LST_POWEROFF_NOTICE );		/*停電検出通知*/
		return ( ret );
	}
	if ( ret == OK ) {
		all_ret = OK;
	}
#endif


	/*代行受信消去通知*/
	ret = Print_DelMemoryRcv_Notice();
	if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
		/*ｲﾆｼｬﾙ*/
		Init_AnyList( LST_DELMEMORYRCV_NOTICE ); 	/*代行受信消去通知*/
		Init_AnyList( LST_DELRESERVECMD_NOTICE );	/*通信予約消去通知*/
		Init_AnyList( LST_DELPOLLING_NOTICE );		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
#if ( PRO_BATCH_TX == ENABLE )
		Init_AnyList( LST_DELBATCHTXDOC_NOTICE );	/*一括送信原稿消去通知*/
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング追加　1996/10/18　Eguchi */
		Init_AnyList(LST_DELCONTPOLLCMD_NOTICE);	/** 連続ポーリングコマンド消去通知 */
#endif
		Init_AnyList( LST_POWEROFF_NOTICE );		/*停電検出通知*/
		return ( ret );
	}
	if ( ret == OK ) {
		all_ret = OK;
	}

	/*通信予約消去通知*//* 一括送信消去通知も連続ポーリングコマンド消去通知もここで書く 1996/10/18 Eguchi*/
	ret = Print_DelReserveCmd_Notice();
	if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
		/*ｲﾆｼｬﾙ*/
		Init_AnyList( LST_DELRESERVECMD_NOTICE );	/*通信予約消去通知*/
		Init_AnyList( LST_DELPOLLING_NOTICE );		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
#if ( PRO_BATCH_TX == ENABLE )
		Init_AnyList( LST_DELBATCHTXDOC_NOTICE );	/*一括送信原稿消去通知*/
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング追加　1996/10/18　Eguchi */
		Init_AnyList(LST_DELCONTPOLLCMD_NOTICE);	/** 連続ポーリングコマンド消去通知 */
#endif
		Init_AnyList( LST_POWEROFF_NOTICE );		/*停電検出通知*/
		return ( ret );
	}
	if ( ret == OK ) {
		all_ret = OK;
	}

	/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
	ret = Print_DelPoll_List();
	if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
		/*ｲﾆｼｬﾙ*/
		Init_AnyList( LST_DELPOLLING_NOTICE );		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
#if ( PRO_BATCH_TX == ENABLE )
		Init_AnyList( LST_DELBATCHTXDOC_NOTICE );	/*一括送信原稿消去通知*//*通信予約消去通知と一緒の所で記録するのでここにあるのは無意味 */
#endif
#if (PRO_CONTINUOUS_POLLING == ENABLE) /* 連続ポーリング追加　1996/10/18　Eguchi */
		Init_AnyList(LST_DELCONTPOLLCMD_NOTICE);	/** 連続ポーリングコマンド消去通知 *//*通信予約消去通知と一緒の所で記録するのでここにあるのは無意味 */
#endif
		Init_AnyList( LST_POWEROFF_NOTICE );		/*停電検出通知*/
		return ( ret );
	}
	if ( ret == OK ) {
		all_ret = OK;
	}

	/*ﾘﾓｰﾄﾌｧｸｽ原稿消去通知*/

#if (PRO_CIPHER == ENABLE)
	/* ｽｸﾗﾝﾌﾞﾙ受信原稿消去通知 */
	ret = Print_DelScrambleRx_List();
	if ( ret != OK && ret != MSG_PRN_LST_NO_LIST ) {
		/*ｲﾆｼｬﾙ*/
		Init_AnyList( LST_DEL_SCRAMBLE_RX_NOTICE );	/*ｽｸﾗﾝﾌﾞﾙ受信原稿消去通知*/
		Init_AnyList( LST_POWEROFF_NOTICE );		/*停電検出通知*/
		return ( ret );
	}
	if ( ret == OK ) {
		all_ret = OK;
	}
#endif

	Init_AnyList( LST_POWEROFF_NOTICE );			/*停電検出通知*/
	return ( all_ret );
}


/*************************************************************************
	module		:[停電時、データ存在検査]
	function	:[
		親展受信消去,代行受信消去,通信予約消去,ポーリング原稿消去,停電の
		データ存在を検査する
	]
	common		:[
		SYB_MailBox			:
		SYB_MemoryRxPrint	:
		SYB_CommandFile		:
		SYB_BatchTxFile		:
		SYB_PowerDownListStatus;
	]
	condition	:[
		チェックモード
		,	LST_DELSECURE_NOTICE	 	親展受信消去通知
		,	LST_DELMEMORYRCV_NOTICE 	代行受信消去通知
		,	LST_DELRESERVECMD_NOTICE	通信予約消去通知
		,	LST_DELPOLLING_NOTICE		ポーリング原稿消去通知
		,	LST_DELBATCHTXDOC_NOTICE	一括送信原稿消去通知
		,	LST_POWEROFF_NOTICE			停電検出通知
	]
	commment	:[
		94/11/26	By j.masuda
			ポーリング原稿消去通知、検索ポーリング原稿消去通知、
			リモートファクス消去通知のステータスをSYB_PowerDownListStatusに
			変更。
		94/11/29	By j.masuda
			親展受信消去通知はステータスがSYS_MAILBOX_RECEIVEで、かつ、
			メモリがない時のみ印刷する。
	]
	return		:[
		データ存在
		,	MSG_PRN_LST_NO_LIST	データなし
		,	OK			データあり
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
WORD 				Check_AnyList(
						 UBYTE Mode )	/*チェックモード*/
{
	UBYTE	i;					/*loop*/
	register WORD	ret;					/*実行結果*/

	ret = MSG_PRN_LST_NO_LIST;

	if ( Mode == LST_DELSECURE_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*親展受信消去通知*/
		for ( i = 0; i < SYS_MAILBOX_MAX; i++ ) {
			if ( SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE &&	/*94/11/29 By j.masuda*/
			  MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,i, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX ) {
				ret = OK;
				break;
			}
		}
	}
#if (PRO_F_CODE == ENABLE)
	if ( Mode == LST_DEL_FCODE_BOX_DOC_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/* Ｆコード原稿消去通知*/
		for ( i = 0; i < SUB_ADDRESS_BOX_MAX; i++ ) {
			switch (SYB_SubAddressBoxTable[i].Status) {
			case SUB_ADDRESS_BULLETIN_BOX:
				if ( (( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
				   ||( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE))
				  && ( MEM_CountTotalBoxPage(SYS_MEM_SUB_BULLETIN_FILE, (UBYTE)(i + 1)) == (UWORD)MEM_NO_INDEX )) {
					ret = OK;
				}
				break;
			case SUB_ADDRESS_SECURE_BOX:
				if ( (( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
				   || ( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE) )
				  && ( MEM_CountTotalBoxPage(SYS_MEM_SUB_SECURE_FILE, (UBYTE)(i + 1)) == MEM_NO_INDEX )) {
					ret = OK;
				}
				break;
			case SUB_ADDRESS_BOX_EMPTY:
			default:
				break;
			}
			if (ret == OK) {	/* 原稿消去が発見されたらブレークで抜ける */
				break;
			}
		}
	}
#endif
#if (PRO_CIPHER == ENABLE)
	if ( Mode == LST_DEL_SCRAMBLE_RX_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/* 暗号化受信消去通知 */
		for ( i = 0; i < SYS_CIPHERBOX_MAX; i++ ) {
			if ((SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVE )&&
			    (MEM_CountTotalPage(SYS_MEM_CIPHER_RX_FILE,i, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX )) {
				ret = OK;
				break;
			}
		}
	}
#endif
	if ( Mode == LST_DELMEMORYRCV_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*代行受信消去通知*/
		for ( i = 0; i < SYS_MEMORY_RX_MAX; i++ ) {
			if ( SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_POWEROFF ) {
				ret = OK;
				break;
			}
		}
	}
	if ( Mode == LST_DELRESERVECMD_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*通信予約消去通知*/
		for ( i = 0; i < SYS_COM_FILE_MAX; i++ ) {
#if (PRO_COMMANDFILE_SRAM == ENABLE)	/* M.Tachibana 1997/03/22 */
			if ( SYB_CommandFile[i].Status == SYS_CMD_POWER_OFF ) {
				ret = OK;
				break;
			}
#else
			if ( SYB_CommandStatus[i] == SYS_CMD_POWER_OFF ) {
				ret = OK;
				break;
			}
#endif
		}
	}
	if ( Mode == LST_DELPOLLING_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/

/*94/11/26 ↓ By jmasuda*/
		if ( (SYB_PowerDownListStatus & (SYS_POWER_POLLING | SYS_POWER_DB_POLL)) != 0 ) {
			ret = OK;
		}
/*94/11/26 ↑ By jmasuda*/
	}
#if ( PRO_BATCH_TX == ENABLE )
	if ( Mode == LST_DELBATCHTXDOC_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*一括送信原稿消去通知*/
		for ( i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
			if ( SYB_BatchTxFile[i].Status == SYS_CMD_POWER_OFF ) {
				ret = OK;
				break;
			}
		}
	}
#endif

	/*-------------------------------*
	 *連続ポーリング追加1996/10/18 Eguchi
	 *-------------------------------*/
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	if (Mode == LST_DELCONTPOLLCMD_NOTICE || Mode == LST_POWEROFF_NOTICE) {
		if (SYB_ContinuousPolling.Status == SYS_CMD_POWER_OFF) {
			ret = OK;
		}
	}
#endif

	return ( ret );
}

/*************************************************************************
	module		:[停電時データ初期化]
	function	:[
		親展受信消去,代行受信消去,通信予約消去,ポーリング原稿消去,停電の
		各データを初期状態にする
	]
	common		:[
		SYB_MailBox			:
		SYB_MemoryRxPrint	:
		SYB_CommandFile		:
		SYB_BatchTxFile		:
		SYS_ErasePixMemoryListRequest;
		SYB_PowerDownListStatus;
		SYS_ScannerComEraseRequest:
	]
	condition	:[
		消去モード
		,	LST_DELSECURE_NOTICE	 	親展受信消去通知
		,	LST_DELMEMORYRCV_NOTICE 	代行受信消去通知
		,	LST_DELRESERVECMD_NOTICE	通信予約消去通知
		,	LST_DELPOLLING_NOTICE		ポーリング原稿消去通知
		,	LST_DELBATCHTXDOC_NOTICE	一括送信原稿消去通知
		,	LST_POWEROFF_NOTICE			停電検出通知
	]
	commment	:[
		94/11/26	By j.masuda
			ポーリング原稿消去通知、検索ポーリング原稿消去通知、
			リモートファクス消去通知のステータスをSYB_PowerDownListStatusに
			変更。
		94/11/26	By j.masuda
			親展受信消去通知のステータスクリアーをメモリがない時のみ
			SYS_MAIL_SETとする。またメモリのクリアーはメインで行う事とし
			リストではおこなわない。
		94/11/26	By j.masuda
			コマンドファイルのステータスをEMPTYにする前に
			SYS_ScannerComEraseListRequestをクリアーする。
			PRO_DRAM_BACKUP==ENABLEの時のみ。
		94/11/29	By j.masuda
			親展受信消去通知はステータスがSYS_MAILBOX_RECEIVEで、かつ、
			メモリがない時のみ印刷する。
	]
	return		:[なし]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[93/11/25]
	author		:[増田次郎]
*************************************************************************/
void 				Init_AnyList(
						 UBYTE Mode )		/*消去モード*/
{
	UBYTE	i;						/*loop*/

	if ( Mode == LST_DELSECURE_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*親展受信消去通知*/
		for ( i = 0; i < SYS_MAILBOX_MAX; i++ ) {
			if ( SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE &&
			  MEM_CountTotalPage(SYS_MEM_SECURE_RX_FILE,i, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX ) {
													/*94/11/29 By j.masuda*/
				SYB_MailBox[i].MessageStatus = SYS_MAILBOX_MSG_EMPTY;
				SYB_MailBox[i].Status = SYS_MAILBOX_SET;
			}
		}
	}
#if (PRO_F_CODE == ENABLE)
	if ( Mode == LST_DEL_FCODE_BOX_DOC_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/* Ｆコード原稿消去通知*/
		for ( i = 0; i < SUB_ADDRESS_BOX_MAX; i++ ) {
			switch (SYB_SubAddressBoxTable[i].Status) {
			case SUB_ADDRESS_BULLETIN_BOX:
				if ( (( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
				   || ( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE))
				  && ( MEM_CountTotalBoxPage(SYS_MEM_SUB_BULLETIN_FILE, (UBYTE)(i + 1)) == MEM_NO_INDEX )) {
					SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
					SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
					SYB_SubAddressBoxTable[i].StoredDocBit = 0;
				}
				break;
			case SUB_ADDRESS_SECURE_BOX:
				if ( (( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_STORED)
				   || ( SYB_SubAddressBoxTable[i].DataStatus == SYS_SUB_ADDRESS_BOX_RECEIVE))
				  && ( MEM_CountTotalBoxPage(SYS_MEM_SUB_SECURE_FILE,(UBYTE)(i + 1)) == MEM_NO_INDEX )) {
					SYB_SubAddressBoxTable[i].MessageStatus = SYS_SUB_ADDRESS_BOX_MSG_EMPTY;
					SYB_SubAddressBoxTable[i].DataStatus = SYS_SUB_ADDRESS_BOX_NO_SET;
					SYB_SubAddressBoxTable[i].StoredDocBit = 0;
				}
				break;
			case SUB_ADDRESS_BOX_EMPTY:
			default:
				break;
			}
		}
	}
#endif
#if (PRO_CIPHER == ENABLE)
	if ( Mode == LST_DEL_SCRAMBLE_RX_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/* 暗号化受信消去通知 */
		for ( i = 0; i < SYS_CIPHERBOX_MAX; i++ ) {
			if ((SYB_CipherBox[i].Status == SYS_CIPHERBOX_RECEIVE )&&
			    (MEM_CountTotalPage(SYS_MEM_CIPHER_RX_FILE,i, MEM_IGNORE_BOX_NUMBER) == MEM_NO_INDEX )) {
				SYB_CipherBox[i].MessageStatus = SYS_CIPHERBOX_MSG_EMPTY;
				SYB_CipherBox[i].Status = SYS_CIPHERBOX_NO;
				SYB_CipherBox[i].StorePage = 1;
				SYB_CipherBox[i].PrintPage = 0;
			}
		}
	}
#endif
	if ( Mode == LST_DELMEMORYRCV_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*代行受信消去通知*/
		/*代行受信消去通知*/
		for ( i = 0; i < SYS_MEMORY_RX_MAX; i++ ) {
			if ( SYB_MemoryRxPrint[i].Status == SYS_MEMORY_RX_POWEROFF ) {
				SYB_MemoryRxPrint[i].Status = SYS_MEMORY_RX_EMPTY;
			}
		}
		/* 代行受信バグ Oct.5,1994 By S.K  */
		/* SYB_MemoryRxPrintWritePoint = 0;    */
		/* SYB_MemoryRxPrintReadPoint = 0;     */
	}
	if ( Mode == LST_DELRESERVECMD_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*通信予約消去通知*/
#if (PRO_DRAM_BACKUP == ENABLE)			/*94/11/26 ↓ By jmasuda*/
		SYS_ScannerComEraseListRequest = 0;
#endif									/*94/11/26 ↑ By jmasuda*/
		for ( i = 0; i < SYS_COM_FILE_MAX; i++ ) {
#if (PRO_COMMANDFILE_SRAM == ENABLE)	/* M.Tachibana 1997/03/22 */
			if ( SYB_CommandFile[i].Status == SYS_CMD_POWER_OFF ) {
				SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
 #if (PRO_F_CODE == ENABLE)
				if (CMN_CheckFcodeCommand(SYB_CommandFile[i].Option.Item) == TRUE) {	/** 交信種別判断 */
					SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
					SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
				}
 #endif
			}
#else
			if ( SYB_CommandStatus[i] == SYS_CMD_POWER_OFF ) {
				SYB_CommandFile[i].Status = SYS_CMD_EMPTY;
 #if (PRO_F_CODE == ENABLE)
				if (CMN_CheckFcodeCommand(SYB_CommandFile[i].Option.Item) == TRUE) {	/** 交信種別判断 */
					SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_SubAddressNumber[0] = 0xFF;
					SYB_FcodeNumberCDataBuffer[SYB_CommandFile[i].Option.OptionNumber.FcodeDataPosition[0]].SYS_PassWordNumber[0] = 0xFF;
				}
 #endif
				SYB_CommandStatus[i] = SYS_CMD_EMPTY;
			}
#endif
		}
	}
	if ( Mode == LST_DELPOLLING_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*ﾎﾟｰﾘﾝｸﾞ原稿消去通知*/
/*94/11/26 ↓ By jmasuda*/
		if ( (SYB_PowerDownListStatus & SYS_POWER_POLLING ) != 0 ) {
			SYB_PowerDownListStatus &= ~SYS_POWER_POLLING;
		}
		if ( (SYB_PowerDownListStatus & SYS_POWER_DB_POLL ) != 0 ) {
			SYB_PowerDownListStatus &= ~SYS_POWER_DB_POLL;
		}
/*94/11/26 ↑ By jmasuda*/
	}
	if ( Mode == LST_DELBATCHTXDOC_NOTICE || Mode == LST_POWEROFF_NOTICE ) {
		/*一括送信原稿消去通知*/
#if ( PRO_BATCH_TX == ENABLE )
		for ( i = 0; i < SYS_BATCH_FILE_MAX; i++ ) {
			if ( SYB_BatchTxFile[i].Status == SYS_CMD_POWER_OFF ) {
				SYB_BatchTxFile[i].Status = SYS_CMD_EMPTY;
/*				for ( j = 0; j < SYS_BATCH_INDEX_MAX; j++ ) {	0ｸﾘｱはｵﾍﾟﾚｰｼｮﾝがする '94.11.16 H.T */
/*					SYB_BatchTxFile[i].IndexNo[j] = 0xFFFF;				*/
/*				}														*/
			}
		}
#endif
	}

	/*-------------------------------*
	 *連続ポーリング追加1996/10/18 Eguchi
	 *-------------------------------*/
#if (PRO_CONTINUOUS_POLLING == ENABLE)
	if (Mode == LST_DELCONTPOLLCMD_NOTICE || Mode == LST_POWEROFF_NOTICE) {
		if (SYB_ContinuousPolling.Status == SYS_CMD_POWER_OFF) {
			SYB_ContinuousPolling.Status = SYS_CMD_EMPTY;
		}
	}
#endif

	if ( Mode == LST_POWEROFF_NOTICE ) {
		/*停電検出通知*/
		SYS_ErasePixMemoryListRequest = 0;
	}
}

