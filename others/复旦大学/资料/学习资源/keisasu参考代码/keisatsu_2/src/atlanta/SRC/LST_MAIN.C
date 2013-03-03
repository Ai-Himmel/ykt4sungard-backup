/*************************************************************************
*	System		: POPLAR/ANZU_L
*	File Name	: LST_MAIN.C
*	Author		: 桑原 美紀
*	Date		: 1997/03/11
*	RealTimeOS	: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description	: リストプリントメイン
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\message.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\sys_stat.h"

#include	"\src\atlanta\define\lst_def.h"

#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\lst_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\lst_data.h"
#include	"\src\atlanta\ext_v\sys_data.h"

#include	"\src\memsw\define\mems_pro.h" /* Add By H.Hirao 1996/07/04 */
#if (PRO_CPU == SH7043)
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif
#if (PRO_PRINT_TYPE == LED)
#include	"\src\atlanta\prt\ph3\define\prn_pro.h"
#include	"\src\atlanta\prt\ph3\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == LASER)
#include	"\src\atlanta\prt\sp322\ext_v\prn_data.h"
#endif
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2004/10/11 */
#include	"\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
#include	"\src\atlanta\define\sys_infd.h"
#include	"\src\atlanta\ext_v\sys_inf.h"
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"	/* added by H.Hirao 1999/03/04 */
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
#include	"\src\atlanta\define\man_pro.h" /* Add By H.Hirao 1996/07/04 */
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/19 By M.Maeda */
#include	"\src\atlanta\define\man_pro.h" /* Add By H.Hirao 1996/07/04 */
#endif
/*************************************************************************
	module		:[リストプリントメイン]
	function	:[
		リストプリントのメイン処理。ここから各リスト印刷に分岐する。
	]
	common		:[
		SYS_STOP_LIST_PRINT		:
		SYS_DocumentPrintItem	:
		SYS_DocumentPrintNo		:
	]
	condition	:[]
	comment		:[]
	return		:[印刷結果]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[LST]
	date		:[1993/11/20]
	author		:[増田次郎]
*************************************************************************/
void 				LST_PrintTask(
							void )				/*なし*/
{
	WORD			ret;					/*印刷結果*/
	MESSAGE_t		tx_message;				/*メインへの送メッセージ*/
	MESSAGE_t		*rx_message;			/*メインへの受メッセージ*/

	LST_Reduction = 100;	/* 記録紙がA4.B4.A3の時 94.9.2 */
	LST_PageCounter = 0;	/* Add By M.Tachibana 1997/04/18 */

#if defined(POPLAR_F)
	/* 2000/08/11 Y.Murata
	 * 写真原稿をプリントする時、頭数センチ分だけ濃度が濃くなる。
	 * 環境温度と、サーミスをアナログＳＷで切り替えてるが、確定するまでここで待ちます。
	*/
	wai_tsk(100);
#endif

#if (PRO_PRINT_TYPE == LED)
 #if (PRO_FAN_TEST == ENABLE)	/* By M.Tachibana 2000/02/14 */
	PRN_CalculateEnvTemp(PRN_EnvTempData);
	PRN_SaveEnvironmentTemp = PRN_EnvironmentTemp;
 #endif
#endif

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/19*/
	MAN_ExecEcoWakeUp();
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/19 By M.Maeda */
 #if (1) /* カバーオープンで２４ＶをＯＮしないようにする By M.Maeda 2003/01/22 */
	MAN_ChangeEcoMode(0);
 #else
//	MAN_ChangeEcoMode(FALSE);
 #endif
#endif

	while ( 1 ) {

/*		SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_LIST_PRINT;	@**停止ボタンデータ クリアー*/
		SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~(SYS_STOP_IMAGE_PRINT + SYS_STOP_MULTI_COPY + SYS_STOP_LIST_PRINT);	/* StopSw  by NOBUKO  Nov.01,94 */
		ret = OK;								/**印刷結果=OKセット*/
#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Enable the flag for print checking. Added by SMuratec 李 2004/10/11 */
		Paper.ListFlag = TRUE;
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

		switch ( SYS_DocumentPrintItem ) {		/**各リストに分岐*/
		case LST_JOURNAL_LIST:				/**通信管理レポート「送受信」*/
#if defined(SAKAKI) && defined(JP0)	/* 2002/08/30 By M.Maeda */
		case LST_JOURNAL_TX_LIST:			/* 通信管理レポート「送信」  */
		case LST_JOURNAL_RX_LIST:			/* 通信管理レポート「受信」  */
#endif
#if (PRO_DAILY_REPORT == ENABLE)	/* by K.Watanabe 2004/10/28 */
		case LST_AUTO_ALL_JOURNAL:			/* 通信管理記録自動プリント */
		case LST_DAILY_REPORT:				/* 通信管理記録日報プリント */
#endif
#if (PRO_PAT_JOURNAL == DISABLE)
			/**通信管理レポート「送受信」を印刷*/
#if (0)
//			LST_SelectPaperSize();
//			if ( (SelectedPaper == SYS_A4R_PAPER) || (SelectedPaper == SYS_B5R_PAPER) || (SelectedPaper == SYS_A5R_P//APER) ) {
//				LST_Reduction = 50;
//			}
#endif
			ret = Print_Journal_List();
#endif
#if (0)	/* POPLAR,ANZUでは使用しない By M.Tachibana 1997/03/13 */
//#if ( PRO_PAT_JOURNAL == ENABLE )
//			ret = Print_Journal_List();
//#endif
#endif
			break;
#if ( PRO_TCR_PRINT == ENABLE )	/* MILANはDISABLE */
		case LST_TXCONF_REPORT:				/**送信証*/
			/**送信証を印刷*/
			ret = Print_TxConf_List();
			break;
#endif
		case LST_SPEEDDIAL_LIST:			/**ダイヤルリスト（短縮）*/
			/**ダイヤルリスト（短縮）を印刷*/
			ret = Print_SpeedDial_List();
			break;
		case LST_ONETOUCHDIAL_LIST:			/**ダイヤルリスト（ワンタッチ）*/
			/**ダイヤルリスト（ワンタッチ）を印刷*/
			ret = Print_OnetouchDial_List();
			break;
		case LST_PROGRAM_LIST:				/**プログラムリスト*/
			/**プログラムリストを印刷*/
			ret = Print_Program_List();
			break;
		case LST_GROUP_LIST:				/**グループリスト*/
			/**グループリストを印刷*/
			ret = Print_Group_List();
			break;
		case LST_FUNCTION_LIST:				/**機能リスト*/
			/**機能リストを印刷*/
			ret = Print_Function_List();
			break;
		case LST_PARAMETER_LIST:			/**機器設定リスト*/
			/**機器設定リストを印刷*/
			ret = Print_Parameter_List();
			break;
		case LST_RESERVECMD_LIST:			/**ツウシン ヨヤクリスト*/
			/**ツウシン ヨヤクリストを印刷*/
			ret = Print_ReserveCmd_List();
			break;
		case LST_MAILBOX_LIST:				/**親展者リスト*/
			/**親展者リストを印刷*/
			ret = Print_Mailbox_List();
			break;
#if (0)
//		case LST_TTI_LIST:					/**発信元リスト*/
//			/**発信元リストを印刷*/
//		 	ret = Print_TTI_List();
//		 	break;
#endif
		case LST_COVERPAGE_LIST:			/**カバーページプリント*/
			/**カバーページプリントを印刷*/
			ret = Print_CoverPage_List( LST_MODE_PRINT, List.S.Print, List.S.Attribute, NULL, 0);
			break;
		case LST_SECURERCV_NOTICE:			/**親展受信通知*/
			/**親展受信通知を印刷*/
			ret = Print_SecureRcv_Notice( (UBYTE)SYS_DocumentPrintNo ) ;
			break;
		case LST_DELSECURE_NOTICE:			/**親展受信消去通知*/
			/**親展受信消去通知を印刷*/
			ret = Print_DelSecure_Notice( LST_DELSECURE_NOTICE );
			break;
		case LST_DELMEMORYRCV_NOTICE:		/**代行受信消去通知*/
			/**代行受信消去通知を印刷*/
			ret = Print_DelMemoryRcv_Notice();
			break;
		case LST_DELRESERVECMD_NOTICE:		/**通信予約消去通知*/
		case LST_DELBATCHTXDOC_NOTICE:		/**一括送信原稿消去通知**/
			/**通信予約消去通知を印刷*/
			ret = Print_DelReserveCmd_Notice();
			break;
		case LST_COMMERR_CHECKMSG:			/**チェックメッセージB コウシンエラー*/
			/**チェックメッセージB コウシンエラーを印刷*/
			ret = Print_CommErr_ChkMsg();
			break;
#if defined(KEISATSU)	/* 警察FAX DVT_ID2 Added by SMuratec 夏 2005/11/01 */
		case LST_FORCE_STOP_COMM_CHKMSG:	/**強制中断チェックメッセージ*/
			ret = Print_ForceStopComm_ChkMsg(); 
			break;
#endif

#if ( PRO_BATCH_TX == ENABLE )
		case LST_COMMERR_BATCH_CHECKMSG:	/**ﾁｪｯｸﾒｯｾｰｼﾞH　一括送信通知(ﾓﾆﾀｰﾚﾎﾟｰﾄ） */
			if ( CHK_BatchTxTCR_ON() ) {	/** 一括送信後、送信証印字する設定の場合 */
				ret = Print_TxConf( LST_ERR_CLOSE );
			}
			else {
				ret = Print_CommErr_ChkMsg();
			}
			break;
#endif
#if ( PRO_MONITOR_REPORT == ENABLE )
		case LST_MONITOR_REPORT:			/**ﾓﾆﾀｰﾚﾎﾟｰﾄ**/
			ret = Print_TxConf( LST_ERR_CLOSE ); /** 原稿無し送信証 By H.Hirao 1996/05/08 */
			/* ret = Print_CommErr_ChkMsg(); */ /* ﾓﾆﾀｰﾚﾎﾟｰﾄを送信証に変更 By H.Hirao 1996/05/08 */
			break;
#endif
		case LST_MANUAL_TXCONF_REPORT:		/** 手動送信送信証 Add By H.Hirao 1996/06/24 */
			ret = Print_ManualTxConf();
			break;
		case LST_MRYOVER_CHECKMSG:			/**チェックメッセージC メモリオーバー*/
			/**チェックメッセージC メモリオーバーを印刷*/
			ret = Print_MryOver_ChkMsg( (UBYTE)SYS_DocumentPrintNo );
			break;
		case LST_MNLERR_CHECKMSG:			/**チェックメッセージE 手動送信エラー*/
			/**チェックメッセージE 手動送信エラーを印刷*/
			ret = Print_MnlErr_ChkMsg();
			break;
#if (PRO_PC_PRINT == ENABLE)
		case	LST_PCMRYOVER_CHECKMSG:  		/** PC用メモリオーバー Aug.13.1997 by T.Soneoka */
			ret = Print_PcMryOver_ChkMsg();
			break;
#endif
#if (0)
//		case LST_RXMRYOVER_CHECKMSG:		/**チェックメッセージF 受信メモリオーバー*/
//			/**チェックメッセージF 受信メモリオーバーを印刷*/
//			ret = Print_RxmryOver_ChkMsg();
//			break;
#endif
#if (0)	/* ﾁｪｯｸﾒｯｾｰｼﾞBに移行 '94.11.14 H.T */
//		case LST_COMMERR_BATCH_CHECKMSG:	/**ﾁｪｯｸﾒｯｾｰｼﾞH　一括送信通知 */
//			/**ﾁｪｯｸﾒｯｾｰｼﾞH　一括送信通知(ﾓﾆﾀｰﾚﾎﾟｰﾄ)を印刷*/
//			ret = Print_BatchErr_ChkMsg();
//			break;
#endif
		case LST_T30MONITOR:				/**T30モニタ*/
			/**T30モニタを印刷*/
			ret = Print_T30Monitor();
			break;
		case LST_POWEROFF_NOTICE:			/**停電検出通知*/
			/**停電検出通知を印刷*/
			ret = Print_PowerOff_Notice();
			break;
		case LST_DELPOLLING_NOTICE:			/**ﾎﾟｰﾘﾝｸﾞ原稿消去通知**/
			/**ﾎﾟｰﾘﾝｸﾞ原稿消去通知を印刷**/
			ret = Print_DelPoll_List();
#if (PRO_PC_PRINT == ENABLE) /* #if is added by H.Kubo 1998/02/23 */
/* PCﾌﾟﾘﾝﾄﾒﾓﾘｵｰﾊﾞｰﾘｽﾄをここからｷｯｸ 97/10/02 By M.Kuwahara */
			ret = Print_PcMryOver_ChkMsg();
#endif /* (PRO_PC_PRINT == ENABLE) */
/********/
			break;
#if (PRO_BATCH_TX == ENABLE)
		case LST_BATCHTXBOX_LIST:			/**一括送信BOXﾘｽﾄ**/
			/**一括送信BOXﾘｽﾄを印刷**/
			ret = Print_BatchTxBox_List();
			break;
		case LST_BATCHTXDOC_LIST:			/**一括送信原稿ﾘｽﾄ**/
			/**一括送信原稿ﾘｽﾄを印刷**/
#if (0)
//			LST_SelectPaperSize();
//			if ( (SelectedPaper == SYS_A4R_PAPER) || (SelectedPaper == SYS_B5R_PAPER) || (SelectedPaper == SYS_A5R_P//APER) ) {
//				LST_Reduction = 50;
//			}
#endif
			ret = Print_BatchTxDoc_List();
			break;
#endif
#if (0)
//		case LST_DELBATCHTXDOC_NOTICE:		/**一括送信原稿消去通知**/
//			/**一括送信原稿消去通知を印刷**/
//			ret = Print_DelBatchTxDoc_Notice();
//			break;
#endif
#if (PRO_COST == ENABLE) /* For ANZU By S.K Dec.15,1995 */
		case LST_COSTTABLE_LIST:			/**料金表**/
			/**料金表を印刷**/
			ret = Print_CostTable_List();
			break;
#endif

#if (PRO_DEPARTMENT == ENABLE) /* For ANZU By H.Hirao 1996/02/23 */
  #if (PRO_COST == ENABLE)
		case LST_DEPARTDATACODE_LIST:		/**部門管理ﾘｽﾄ**/
			/**部門管理ﾘｽﾄを印刷**/
			ret = Print_DepartData_List();
			break;
  #elif (PRO_DEPART_NEW_LIST == ENABLE)		/* 簡易料金管理リスト By thonda 1997/11/29 */
		case LST_DEPARTMANAGE_LIST:			/**簡易料金管理ﾘｽﾄ**/
			/**簡易料金管理ﾘｽﾄを印刷**/
			ret = Print_DepartManage_List();
			break;
  #endif
#endif

#if (PRO_F_CODE == ENABLE)
		case LST_FCODE_BOXRCV_NOTICE: 		/**Ｆコード受信通知**/
			/** ｻﾌﾞｱﾄﾞﾚｽ受信通知ﾘｽﾄ **/
			ret = Print_F_CodeBoxRcv_Notice((UBYTE)SYS_DocumentPrintBoxNumber, (UBYTE)SYS_DocumentPrintNo);
			break;
		case LST_DEL_FCODE_BOX_DOC_NOTICE:	/**Ｆコード原稿消去通知**/
			/** ｻﾌﾞｱﾄﾞﾚｽ原稿消去通知 **/
			ret = Print_Del_F_CodeBoxDoc_Notice(LST_DEL_FCODE_BOX_DOC_NOTICE);
			break;
		case LST_F_CODE_BOX_LIST:			/**Ｆコードボックスリスト**/
			/** ｻﾌﾞｱﾄﾞﾚｽＢＯＸﾘｽﾄを印刷 **/
			ret = Print_F_CodeBox_List();
			break;
		case LST_F_CODE_DOC_LIST:			/**Ｆコード蓄積原稿リスト**/
			/** ｻﾌﾞｱﾄﾞﾚｽBOX蓄積原稿ﾘｽﾄ **/
			ret = Print_F_CodeDoc_List(); 
			break;
#endif
#if (PRO_PANEL == ANK)	/* Add by O.Kimoto 1998/11/12 */
		/* 下記リストはＡＮＫ（20文字×2行）だけが必要です。
		** by O.Kimoto 1998/11/20
		*/
		case LST_FACT_MENU:					/**工場メニュー*/
			/**工場メニューを印刷*/
			ret = Print_Fact_Menu();
			break;
#endif
#if (PRO_CIPHER == ENABLE)
		case LST_SCRAMBLE_RCV_NOTICE:
			ret = Print_CipherRecieve_Notice();
			break;
		case LST_SCRAMBLE_KEY:				/** 暗号化キーリスト	97/10/21 By M.Kuwahara */
			ret = Print_KeyWord_List();
			break;
		case LST_SCRAMBLE_KEY_LIST:			/** 暗号化キーブックリスト	97/10/21 By M.Kuwahara */
			ret = Print_KeyBook_List();
			break;
		case LST_DEL_SCRAMBLE_RX_NOTICE:	/** 暗号化受信原稿消去通知  97/11/21 By M.Kuwahara */
			ret = Print_DelScrambleRx_List();
			break;
#endif
		case LST_MEM_SW:					/**メモリスイッチ*/
			/**メモリスイッチを印刷*/
			ret = Print_Memory_switch();
			break;
		case LST_PATTERN_PRINT:				/**パターンプリント*/
			/**パターンプリントを印刷*/
			ret = Print_Pattern_Print( (UBYTE)SYS_DocumentPrintNo );
			break;
#if (PRO_SECURITY_RX == ENABLE)
		case LST_SEC_RX_MEMOVER_CHKMSG:		/*セキュリティ受信メモリーオーバー */
			ret = Print_SecurityRx_MemOver();
			break;
#endif
#if ( PRO_CLASS1 == ENABLE ) /** Add By H.H 1996/08/21 */
		case LST_CL1_ONLINE_MONITOR:		/* クラス１オンラインモニター */
			ret = PrintClass1Monitor();
			break;
#endif
		case LST_BLOCK_JUNK_LIST:			/* ｼﾞｬﾝｸﾒｰﾙ防止ﾀﾞｲﾔﾙﾘｽﾄ */
			ret = Print_BlockJunkFax_List();
			break;
		case LST_SERVICE_LIST:				/* ｻｰﾋﾞｽﾚﾎﾟｰﾄ */
			ret = Print_ServiceReport();
			break;
		case LST_MEMORY_DUMP:				/** メモリダンプリスト */
			ret = MemoryDumpList();
			break;
		case LST_CONSUMERORDER_SHEET:		/** 消耗品発注リスト 97/10/01 By T.Fukumoto */
			ret = Print_ConsumerOrder_Sheet();
			break;
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
		case LST_INF_TEXT_MAIL:	/*　ｲﾝﾀｰﾈｯﾄFAX　TEXTﾒｰﾙﾌﾟﾘﾝﾄ　*/
			ret = LST_PrintRxTextMail();
			break;
		case LST_INF_ADDRESS_LIST:
			ret = LST_PrintMailAddressList();
			break;
		case LST_INF_GROUP_LIST:
			ret = LST_PrintMailGroupList();
			break;
		case LST_INF_SETTING_LIST:
			ret = LST_PrintMailSettingList();
			break;
		case LST_INF_MAILCOM_LIST:
			ret = LST_PrintMailCommandList();
			break;
		case LST_INF_ERROR_NOTICE:
			ret = LST_PrintMailComCheckMsg();
			break;
		case LST_INF_ERASED_MAIL_NOTICE:
			ret = LST_PrintErasedRxMailNotice();
			break;
		case LST_INF_ERASED_COMMAND_NOTICE:
			ret = LST_PrintErasedCommandNotice();
			break;
		case LST_INF_SECURE_NOTICE:
			ret = LST_PrintSecureRxNotice();
			break;
		case LST_INF_JOURNAL_LIST:
			ret = LST_PrintJournalReport();
			break;
		case LST_INF_MONITOR: /* 1998/05/22 Eguchi */
			ret = LST_INF_Monitor();
			break;

#endif
#if (PRO_KEY_MACRO == ENABLE)	/* 1998/06/24 By M.Kuwahara */
		case LST_KEYMACRO_LIST:		/* ｷｰﾏｸﾛﾀｲﾄﾙﾘｽﾄ				*/
			/*
			** ワープ機能リストをストップで抜けると、プリント完了表示される不具合
			** retが抜けてる by H.Hirao 1999/09/13
			** Ported from \src\nagano\lst\ank_mfp\src\lst_main.c by H.Hirao 1999/12/10
			*/
			/* Print_KeyMacro_List(); */
			ret = Print_KeyMacro_List();
			break;
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE)	/* 1998/06/24 By M.Kuwahara */
		case LST_ND_LIST:		/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲﾀﾞｲﾔﾙﾘｽﾄ	*/
			ret = Print_ND_List();
			break;
		case LST_INF_ND_LIST:	/* ﾅﾝﾊﾞｰﾃﾞｨｽﾌﾟﾚｲ着信履歴ﾘｽﾄ*/
			ret = Print_INF_ND_List();
			break;
#endif
#if (PRO_RX_DOC_TRANSFER == ENABLE)	/* 1998/06/24 Add By M.Kuwahara */
		case LST_WARP_LIST:		/* ﾜｰﾌﾟ機能ﾘｽﾄ				*/
			/*
			** ワープ機能リストをストップで抜けると、プリント完了表示される不具合
			** retが抜けてる by H.Hirao 1999/09/13
			** Ported from \src\nagano\lst\ank_mfp\src\lst_main.c by H.Hirao 1999/12/10
			*/
			/* Print_Warp_List(); */
			ret = Print_Warp_List();
			break;
#endif
#if (PRO_SGP_TEST_ROM == ENABLE) /* by S.Wang 98/07/24 */
		case LST_SGP_REPORT_LIST:	/* シンガポール市場調査レポート */
			ret = Print_Sgp_Report_list();
			break;
#endif

#if (PRO_COM_RESULT == ENABLE) /* 2002/08/22 By M.Maeda */
		case LST_COM_RESULT_LIST:	/* 通信結果プリント */
			ret = PrintComResultList();
			break;
#endif

		default:
			break;
		}

		LST_Reduction = 100;	/* 記録紙がA4.B4.A3の時 94.9.2 */

#if (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) /* Added by SMuratec 李 2004/7/15 */
		Paper.ListFlag = FALSE; /* Disable the flag for print checking. Added by SMuratec 李 2004/10/11 */
		if (PRN_PrintErrorHaltRequest() == OK) {
			PRN_PaperPostOut();
		}
#endif /* (PRO_PAPER_TYPE == CUT_PAPER) && defined(STOCKHM2) */

		tx_message.Item	= FROM_PRN_LST_PRINT_TASK;
		tx_message.Message	= ret;
	    snd_msg( mbxno.MAN_Task, &tx_message );	/**メインタスクに印刷結果のメッセージ送信*/
		rcv_msg( mbxno.LST_Task, &rx_message );	/**メインタスクより終了メッセージ受信*/
#if (PRO_PRINT_TYPE == LED)
	/*	if ((ret == OK) || (ret == MSG_PRN_LST_STOPSW_ON)) {	By M.Tachibana 1997/10/01 */
			LST_CleaningEnd();
	/*	}	*/
		tx_message.Message	= MSG_PRN_LST_PRINTER_END;
	    snd_msg( mbxno.MAN_Task, &tx_message );	/**メインタスクに印刷結果のメッセージ送信*/
		rcv_msg( mbxno.LST_Task, &rx_message );	/**メインタスクより終了メッセージ受信*/
#endif
#if (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/03/03 */
		CMN_DisableInterrupt();
		CL1_DualRestrictionStatus &= ~CL1_PRINTER_IN_USE; /* プリント中リセット */
		CMN_EnableInterrupt();
#endif
		exi_tsk();
	}
}
