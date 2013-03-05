/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMRXC.C													 */
/*	モジュール	 :															 */
/*				 : FaxRxPhaseC()											 */
/*				 : SetRxPageData()											 */
/*				 : StartRxPix()												 */
/*				 : RxECM_PixData()											 */
/*				 : StartECM_RxPix()											 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysdoc.h"
#include	"\src\atlanta\define\std.h"
#include	"\src\atlanta\define\syst30.h"
#include	"\src\atlanta\define\fcm_def.h"
#include	"\src\atlanta\define\apl_msg.h"
#include	"\src\atlanta\define\mem_def.h"

#if (PRO_PRINTER_RX == ENABLE)
	#include "\src\atlanta\define\unisw_c.h"	/* added by H.Hirao 1998/12/25 */
 #if (PRO_MEM_RX_REJECT == ENABLE)
	#include	"\src\atlanta\define\sys_stat.h"	/* 椛のみ Feb.07.1995 */
 #endif
#endif

#include	"\src\atlanta\define\mon_pro.h"
#include	"\src\atlanta\define\man_pro.h"
#include	"\src\memsw\define\mems_pro.h" /*1996/04/17 Eguchi */
#include	"\src\atlanta\define\fcm_pro.h"
#include	"\src\atlanta\define\mem_pro.h"
#include	"\src\atlanta\define\cmn_pro.h"

#include	"\src\atlanta\ext_v\bkupram.h"
#include	"\src\atlanta\ext_v\sys_data.h"
#include	"\src\atlanta\ext_v\fcm_data.h"
#if (PRO_CLASS1 == ENABLE)
#include	"\src\atlanta\ext_v\cl1_data.h"
#endif
#include	"\src\atlanta\define\mntsw_d.h"	/* 1997/06/13  By T.Yamaguchi */

#if (PRO_MODEM == ORANGE3)
#include	"\src\atlanta\mdm\orange\define\mdm_def.h"
#include	"\src\atlanta\mdm\orange\define\mdm_pro.h"
#include	"\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F)
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include	"\src\atlanta\mdm\fm336\define\mdm_def.h"
#include	"\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include	"\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include	"\src\atlanta\mdm\r288f\define\mdm_def.h"
#include	"\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include	"\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"		/*	MDM_ToneTx(),MDM_FilterSet() */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif

#if (PRO_TX_SPEED == V34)
#include	"\src\atlanta\define\uni_pro.h"
#endif /* (PRO_MODEM == R288F) */

#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)  96/1/11 Y.S */
#include	"\src\atlanta\scd\define\scdpro.h"
#endif /* 96/1/11 Y.S */

#if (PRO_PAPER_TYPE == ROLL_PAPER) && (PRO_PRINTER_RX == ENABLE) && (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
 #if defined(STOCKHM2)
#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h" /* added by H.Hirao 1999/01/05 */
 #else
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h" /* added by H.Hirao 1999/01/05 */
 #endif
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/17 K.Kawata */
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif
/************************************************************************
	module		:[受信フェーズＣ]
	function	:[
		以下の処理を１物理ページ受信完了まで繰り返す
		1.	受信ページをオープンする
		2.	画データ受信を起動する
		3.	受信ページをクローズする
		4.	ＥＣＭの再送受信する
		5.	ポストメッセージハンドシェークを行う（受信フェーズＤ）
	]
	return		:[]
	common		:[
		FaxComPerformingFlag	RxWholePageCompletedFlag
		RxEOR_ReceiveFlag		RxECM_Mode
		SYS_RxMemoryFileItem	RxPmType
		RxPageFinishStatus		SYS_DocBlock
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/06]
	author		:[竹内茂樹]
************************************************************************/
void	FaxRxPhaseC( void )
{
	FaxComPhaseStatus = FAX_RX_PH_C_BEFORE_PIX;

	/**	受信ページデータセット	*/
	SetRxPageData();

	/**	変数初期化	*/
	RxPageFinishStatus = RX_PAGE_END;
	RxWholePageCompletedFlag = 0;
	RxEOR_ReceiveFlag = 0;
	PRI_Q_RxFlag = 0;
	PRI_Q_RxCount = 0;
	DEU_Return_Flag = 0; /* 1997/06/02  By T.Yamaguchi DEU条件削除 */
	PIP_TX_Flag = 0;	/* 1997/06/02  By T.Yamaguchi DEU条件削除 */ /* 97/04/26 by M.H. */

	while ((FaxComPerformingFlag == 1)
	&&	   (RxWholePageCompletedFlag == 0)) {	/**	通信中&&物理ページ受信中	*/

		RxECM_PixTimeoutFlag = 0;	/**	ＥＣＭタイムアウト回避フラグをクリア	*/	/* Oct.13.1994 */

		/*--------------------------*/
		/**	高速画データ受信待ち	*/
		/*--------------------------*/
		StartRxPix();	/* 高低速識別等の処理 */

#if (0)	/*	By Y.Suzuki 1998/09/18	*/
//#if defined (ESP)	/*	スペインの申請時に必要	*/
//		if ((FaxComPerformingFlag == 1)
//		&&	(FaxComTxPerformingFlag == 1)
//		&&	(FaxComRxPerformingFlag == 0)) {	/**	送信(ポーリング)に切り替わった	*/
//			return;								/**	リターン	*/
//		}
#endif
		/* ＴＣＦを再受信するためリターンで抜ける */
		if( DEU_Return_Flag == 1 ){	/* 1997/06/02  By T.Yamaguchi DEU条件削除 */
			return;
		}

		if (FaxComPerformingFlag == 1) {		/**	高速画データ受信ＯＫ	*/

			/** Ｔ３０モニタ用データセット	*/
			SaveT30TimingData( SYS_T30_START_TIME );
			SaveT30Data( SYS_T30_RX_PIX, &MDM_ModemBuffer[0][0], 0 );

			/**	表示切替指示(画データ受信中)	*/
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE) /* 1998/04/07  By T.Yamaguchi */
			if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {
				SYS_FaxCommStage = FCM_FLASH_ROM_WRITING;
			}
			else {
				SYS_FaxCommStage = FCM_RECEIVE_SET;		/*	May.30.1994	*/
			}
#else
			SYS_FaxCommStage = FCM_RECEIVE_SET;		/*	May.30.1994	*/
#endif
			SendMsgFaxComToMain( MSG_FAXCOM_DISPLAY );

#if (PRO_MODEM == R288F)	/* ROCKWELL製 28.8K *//* Add By O.Kimoto 1997/12/02 */
			/*------------------------------------------------------*/
			/* プライマリチャネルに入る前にデータレイトをリード     */
			/* 送信局よりオートでデータレイト変わるかもしれへんから */
			/*------------------------------------------------------*/
			FCM_SetRxDataRate();
#endif

#if (0) /* MDMモジュールへ移動します 1998/12/3 by T.Soneoka */
**#if (PRO_PRINTER_RX == ENABLE)	/* 1998/11/11 追加 by T.Soneoka */
**	#if (PRO_PRINT_TYPE == THERMAL)
**			if (SYS_RxMemoryFileItem == NULL) {		/**	プリンタ受信	*/
**				PRT_StartPrint();
**			}
**	#endif
**#endif
#endif
			/*------------------*/
			/**	画データ受信	*/
			/*------------------*/
			FaxComPhaseStatus = FAX_RX_PH_C_PIX;
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)  96/1/11 Y.S */
			RxPageFinishStatus = SCDC_RxPix( RxECM_Mode, RxPmType );
#else /* 96/1/11 Y.S */
			RxPageFinishStatus = MDM_RxPix( RxECM_Mode, RxPmType );
#endif /* 96/1/11 Y.S */
			MDM_RxPixClose( RxECM_Mode );
			FaxComPhaseStatus = FAX_RX_PH_C_AFTER_PIX;

			/*--------------------------------------------------*/
			/**	画データ受信結果を確認 (エラーコードをセット)	*/
			/*--------------------------------------------------*/
			CheckRxPixResultPhaseC();

			if (FaxComPerformingFlag == 1) {	/**	通信中 (画データ受信結果ＯＫ)	*/
				/*------------------------------*/
				/*	命令受信 (ＥＣＭ再送処理)	*/
				/*------------------------------*/
				RxECM_PixData();		/**	ＥＣＭ再送受信	*/
			}

			if (FaxComPerformingFlag == 1) {	/**	画データ受信，ポストメッセージ受信ＯＫ	**
												***	ＥＣＭエラーフレーム受信ＯＫ			*/
				/*----------------------------------------------------------*/
				/**	ＥＯＲ－Ｑを受信した時は，								**
				***	動作中のデコードタスクを停止し，メモリ受信ページは削除	*/
				/*----------------------------------------------------------*/
				if ((RxECM_Mode == 1) && (RxEOR_ReceiveFlag == 1)) {
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)  96/1/11 Y.S */
					SCDC_BreakRxTask();
#else /* 96/1/11 Y.S */
					MDM_BreakRxTask();
#endif /* 96/1/11 Y.S */
					if (RxPmType == RX_MEMORY) {
/* #if (PRO_MULTI_LINE == ENABLE) */
						if (SYS_FaxComIndexConflictStatus == 0) {
							MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
						}
/* #else  */
/*						MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/@ Jul.04.1994 */
/*#endif */
					}
				}

				/*------------------------------*/
				/**	受信フェーズＤ (応答送信)	*/
				/*------------------------------*/
				FaxRxPhaseD();

				/*--------------------------------------------------------------*/
				/*	画データ受信後のポストメッセージハンドシェークに移った時は	*/
				/*	受信フェーズＤで受信ページクローズする						*/
				/*	ＥＣＭ受信異常時はフェーズＤでMDM_BreakRxTask()する			*/
				/*--------------------------------------------------------------*/
			}
			else {		/**	画データ受信ＮＧ／ポストメッセージ受信ＮＧ	*/
				/*--------------------------------------------------------------*/
				/*	動作中のデコードタスクを停止し，メモリ受信ページは削除する	*/
				/*	ただし設定により，メモリ受信原稿は印字する					*/
				/*--------------------------------------------------------------*/
				if ((RxPageFinishStatus == RX_CONTINUE)
				||	(RxPageFinishStatus == RX_BLOCK_END)
				||	(RxPageFinishStatus == RX_TMOUT)) {	/* Aug.10.1994 */
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) 96/1/11 Y.S */
					SCDC_BreakRxTask();
#else /* 96/1/11 Y.S */
					MDM_BreakRxTask();
#endif /* 96/1/11 Y.S */
				}

				if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
					if (((RxPageFinishStatus == RX_PAGE_END) || (RxPageFinishStatus == RX_ERROR))
					/* 1998/05/11  By T.Yamaguchi
					** 暗号化受信時に、命令受信ＮＧでも受信原稿プリントするパスを通ると
					** 受信通知も出ずに、プリントもしないため、原稿が残ったままになるので
					** 再送を期待して、原稿クリアする。親展受信等も同様なので、受信原稿のみの条件を付ける
					*/
					&& (SYS_RxMemoryFileItem == SYS_MEM_RX_FILE)	/* 通常の受信原稿のみ 1998/05/11  By T.Yamaguchi */
					&&	(CHK_PostMsgErrRxDocPrint() != 0)) {		/**	命令受信ＮＧでも受信原稿プリントする時	*/
						/**	受信ページを登録 (メインタスクへ通知)	*/
						SendMsgFaxComToMain( MSG_RX_PRINT_PAGE );
					}
					else {
/* #if (PRO_MULTI_LINE == ENABLE)	/@ 1997/01/10 Y.Murata */
						if (SYS_FaxComIndexConflictStatus == 0) {
							MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );	/* Jul.04.1994 */
						}
/* #else */
						/**	受信ページを削除	*/
/* 						MEM_ClearPageAndFATArea( &SYS_DocBlock.Index ); */
/* #endif  */
					}
				}
			}
		}
		else {		/**	高速画データ受信ＮＧ	*/	/* Aug.11.1994 */
			/*------------------------------------------------------*/
			/*	前ページ受信時に動作中のデコードタスクを停止する	*/
			/*------------------------------------------------------*/
			if ((RxPageFinishStatus == RX_CONTINUE) || (RxPageFinishStatus == RX_BLOCK_END)) {
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) 96/1/11 Y.S */
				SCDC_BreakRxTask();
#else /* 96/1/11 Y.S */
				MDM_BreakRxTask();
#endif /* 96/1/11 Y.S */
			}

			/* 1999/07/13  NAGANOより 1999/10/21 Y.Murata
			 * 部分ページ受信途中での高低速識別で、交信が途絶えた時(PPS_NULL受信後)、中途半端なインデックスが残ってしまう。
			 * ここで、中途半端なのがあれば、そのページを削除します。
			*/
			if (RxPmType == RX_MEMORY) {	/**	メモリ受信	*/
				/**	メモリファイルクローズし，受信ページ削除	*/
				if (SYS_FaxComIndexConflictStatus == 0) {
					MEM_ClearPageAndFATArea( &SYS_DocBlock.Index );
				}
			}

		}
	}
}


/*************************************************************************
	module		:[受信ページデータセット]
	function	:[
		1.	プリンタエラーの場合はメモリ残を確認し，メモリ受信に切り替える
		2.	受信ページのパラメータを原稿制御ブロックにセットする
	]
	return		:[]
	common		:[
		RxMinimumScanningTime	:確定受信１ライン最少伝送時間
		RxBaudRate				:確定受信ボーレイト
		FaxRxMaxLength
		SYS_RxMemoryFileItem	SYS_RxMemoryFileNo	SYS_RxMemoryFilePage
	]
	condition	:[
		１物理ページごとにセット（コール）する
	]
	comment		:[
		Feb.06.1995
		メモリ代行受信に切り替わった時にＲＸモーター砺磁ＯＦＦする
		Feb.07.1995
		Ｓコピーを実行中でスキャナ優先のときは代行受信する処理を追加
		メインへはプリンタエラーなしをsnd_msg()する
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[竹内茂樹]
*************************************************************************/
void	SetRxPageData( void )
{
#if (PRO_TX_SPEED == V34) /* Added by H.Kubo 1997/07/26 */
	if (SYS_V34ProcedureExecuting() == 1) {
		RxBaudRate = FCM_CheckRxDataRate();
	}
#endif /* (PRO_TX_SPEED == V34) */

	/*----------------------------------*/
	/*	受信方式(メモリ／プリンタ)指定	*/
	/*----------------------------------*/
	/* ●ICHOU追加 by T.Soneoka 1996/06/18 */
	if (SYS_FaxComType == SYS_REMOTE_DIAG) {
		RxPmType = RX_BKUPRAM;
	}
	else {
		if (SYS_RxMemoryFileItem == NULL) {		/**	プリンタ受信	*/
#if (PRO_PRINTER_RX == ENABLE)
			if ((CMN_CheckFaxComPrinterError() == FALSE)
			&&	(RxPrinterErrorFlag == 0)) {			/**	プリンタ受信可能	*/
				/*----------------------*/
					/**	プリンタ受信を指定	*/
				/*----------------------*/
				RxPmType = RX_PRINTER;

		#if 0	/* スキャナ優先時の「PRx→MRx切り替え」はやめる	 Feb.17.1995 */
		//#if (PRO_MEM_RX_REJECT == ENABLE)		/* Feb.07.1995 */
		//		/* "スキャナ使用中"and"スキャナ優先設定"and"メモリ受信可"の場合はメモリ受信する */
		//		/* その他の場合は,プリンタ受信を続行する							Feb.07.1995 */
		//		if ((SYS_MachineStatus[SYS_RESOURCE_STATUS] & SYS_SCANNER_BUSY)
		//		&&	!CHK_PreferPrinterToScanner()
		//		&&	!CHK_MemoryReceiveReject()) {
		//			RxPmType = RX_MEMORY;	/** メモリ受信にする */
		//			/**	メモリ受信用の Item,No,Page をセット	*/
		//			SYS_RxMemoryFileNo	 = SYB_MemoryRxPrintWritePoint;
		//			SYS_RxMemoryFilePage = 1;
		//			SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;
		//
		//			/* 現状は,通信終了までプリンタの資源は放さない (ここではポストクローズできないので) */
		//			/**	プリンタを開放するためのメッセージをメインに送信	*/
		//			MsgFromFaxComToMain.SubMessage1 = GetRxPrinterErrorStatus();
		//			SendMsgFaxComToMain( MSG_FAXCOM_PRINTER_ERROR );
		//			PrinterRxPreOpenFlag = 0;
		//		}
		//#endif
		#endif

			}
			else {		/**	プリンタ受信不可	*/
				/*------------------------------------------*/
				/**	プリンタ受信からメモリ受信に切り替える	**
				***		(切り替えた時の先頭ページだけ通る)	*/
				/*------------------------------------------*/
				if (CMN_CheckMemoryReceiveEnable()
		#if (PRO_PRINTER_RX == ENABLE)
				&& (CHK_UNI_V17ReceiveType() != V17_PRX_TO_PRX)	/* added by H.Hirao 1998/12/25 */
		#endif
		#if (PRO_MEM_RX_REJECT == ENABLE)		/* Oct.19.1994 */
				&&	!CHK_MemoryReceiveReject()
		#endif
				) {		/**	代行受信可能	*/
					RxPmType = RX_MEMORY;
					/**	メモリ受信用の Item,No,Page をセット	*/
					SYS_RxMemoryFileNo	 = SYB_MemoryRxPrintWritePoint;
					SYS_RxMemoryFilePage = 1;
					SYS_RxMemoryFileItem = SYS_MEM_RX_FILE;

					PmenOff();	/* ＲＸモーター励磁ＯＦＦ(下から移動)  Feb.06.1995 */

					/**	プリンタを開放するためのメッセージをメインに送信	*/
					MsgFromFaxComToMain.SubMessage1 = GetRxPrinterErrorStatus();
					SendMsgFaxComToMain( MSG_FAXCOM_PRINTER_ERROR );

					/*	プリンタ受信→メモリ受信に切り替わったら，以降はメモリ受信で動作するので	*/
					/*	プリンタエラーのページを示すこのフラグはクリアする			Sep.14.1994		*/
					RxPrinterErrorFlag = 0;		/* Sep.14.1994 */

		#if 0		/* 必ずフラグをクリアする  Oct.19.1994 */
					/**	プリンタエラーならプリオープンフラグをクリアする	**
					***		(ポストクローズさせないため)					*/
					if (RxPageFinishStatus == RX_PRT_ERR) {
						PrinterRxPreOpenFlag = 0;
					}
		#endif

					/* Feb.03.1995 */
					/**	プリオープンフラグをクリアする (ポストクローズさせないため)	*/
					PrinterRxPreOpenFlag = 0;
		#if 0		/* ＲＸモーター砺磁ＯＦＦはプリンタを開放する前(上)に行う  Feb.06.1995 */
			#if (PRO_CPU == V53)		/* for Momiji  Feb.03.1995 */
					/* プリンタ受信から代行受信に移った場合，ＲＸモーター励磁ＯＦＦしないため */
					PmenOff();
			#endif
		#endif
					/* Feb.03.1995 */

				}
				else {
					/**	Ｒ．３．５で通信終了	*/
					ReceiveError( 0x35 );
					/*	R.3.5 : 受信する前に受信出来ないことが判明	*/
				}
		#if 0	/* Feb.03.1995 */
		//		/**	プリオープンフラグをクリアする (ポストクローズさせないため)	*/
		//		PrinterRxPreOpenFlag = 0;		/* Oct.19.1994 */
		#endif
			}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/4 K.Kawata*/
			RxPmType = RX_PRINTER;
#endif
		}
		else {		/**	メモリ受信	*/
			/*----------------------*/
			/**	メモリ受信を指定	*/
			/*----------------------*/
			RxPmType = RX_MEMORY;
		}
	}
	/*--------------------------------------------------*/
	/**	原稿制御ブロックに最少１ラインバイト長をセット	*/
	/*--------------------------------------------------*/
	SYS_DocBlock.MinimumLineSize = CheckMinimumLineSize( RxMinimumScanningTime, RxBaudRate );

	/*----------------------------------------------*/
	/**	原稿制御ブロックに最大受信原稿長をセット	*/
	/*----------------------------------------------*/
#if defined(FRA)
 #if 0	/* フランスも他と同じにします 98/07/16 By T.Fukumoto */
//	/*	フランス仕様　Ａ４＋１０％	*/
//	SYS_DocBlock.DocLength = SYS_A4_PAGE_LENGTH + (SYS_A4_PAGE_LENGTH / 10);
 #endif
	/*	無制限	*/
	SYS_DocBlock.DocLength = SYS_NO_LIMIT_PAGE_LENGTH;
#else
	/*	無制限	*/
	SYS_DocBlock.DocLength = SYS_NO_LIMIT_PAGE_LENGTH;
#endif

	/*------------------------------------------------------*/
	/**	原稿制御ブロックにファイルインデックスをセットする	*/
	/*------------------------------------------------------*/
	SYS_DocBlock.Index.No	= SYS_RxMemoryFileNo;				/*	受信メモリファイル番号		*/
	SYS_DocBlock.Index.Page = SYS_RxMemoryFilePage;				/*	受信メモリページ			*/
	SYS_DocBlock.Index.Item = SYS_RxMemoryFileItem;				/*	受信メモリファイルアイテム	*/
/* #if (PRO_F_CODE == ENABLE)	/@ 1997/01/29  By T.Yamaguchi */
	SYS_DocBlock.Index.BoxNumber = SYS_RxMemoryFileBoxNumber;	/*	受信メモリファイルアイテム	*/
/* #endif */
}


/*************************************************************************
	module		:[高速画データ受信待ち]
	function	:[
		1.	高速画データを受信するまで繰り返す
		2.	命令受信した場合は適当な応答を送信し，再度受信する
		3.	受信タイムアウトや不正な命令を受信した場合は，通信中フラグをクリアする
		4.	プリアンブル短縮フラグは，高速データ受信時にセットする
	]
	return		:[]
	common		:[
		FaxComPerformingFlag
		FaxComTxPerformingFlag		FaxComRxPerformingFlag
		RxBaudRate
	]
	condition	:[]
	comment		:[
		スペイン申請時に，高速データ待ちでＤＴＣを受信した時は
		「ポーリング送信」へ移る処理をする
		Sep.07.1994		プリアンブル短縮フラグのＯＮ／ＯＦＦ
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/02/07]
	author		:[竹内茂樹]
*************************************************************************/
void	StartRxPix( void )
{
	BYTE	result;

#if (PRO_TX_SPEED == V34) /* Ported from CLOVER by H.Kubo 1997/07/26 */
	if (SYS_V34ProcedureExecuting() == 1) {	/* CTS ON の時にﾘｰﾄﾞ 1996/03/04 */
		RxBaudRate = FCM_CheckRxDataRate();
	}
#endif /* (PRO_TX_SPEED == V34) */

	while (FaxComPerformingFlag == 1) {		/**	通信中	*/

		/**	ストップキー入力ありの時は通信中フラグを落としてループを終了	*/	/* Oct.13.1994 */
		if (SYS_FaxComStopSwitch()) {
			FaxComPerformingFlag = 0;
			break;
		}
#if (0)	/*	By Y.Suzuki 1998/09/18	*/
//#if defined (ESP)	/*	スペインの申請時に必要	*/
//		/**	ポーリング送信に変わったらループを終了	*/
//		if ((FaxComRxPerformingFlag != 1) || (FaxComTxPerformingFlag != 0)) {
//			break;
//		}
#endif

		/*----------------------*/
		/*	高速／低速受信識別	*/
		/*----------------------*/
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/07/26 */
		switch (FCM_FskHighSpeedCheck( RxBaudRate, RxECM_Mode )) {	/**	高低速識別	*/
#else /* (PRO_TX_SPEED == V34)  */
		switch (MDM_FskHighSpeedCheck( RxBaudRate, RxECM_Mode )) {	/**	高低速識別	*/
#endif /* (PRO_TX_SPEED == V34)  */

#if (PRO_MODEM == R288F)
		case	TURN_OFF_RECEIVE: /* from CLOVER\src\fcmrxc.c */
#endif /* (PRO_MODEM == R288F) */
		case	TRN_RECEIVE:	/**	高速信号受信	*/
			/**	プリアンブル短縮フラグをセット	*/
			ShorteningPreambleFlag = PostSpeedHandshakeFlag;
			return;		/**	ＯＫリターン	*/
			break;
		case	FSK_RECEIVE:	/**	ＦＳＫ受信	*/
#if (PRO_MODEM == ORANGE3)		/* Ｈ８では不要	 Feb.06.1995 */
			SaveReceivedT30Data();			/**	Ｔ３０データをセット	*/
#endif
			/**	送信した応答が正常に受信されなかったとして，プリアンブル短縮フラグをクリア	*/
			ShorteningPreambleFlag = 0;

			switch (CheckReceivedFCF()) {	/**	受信フレーム	*/
			case	DCS_F:					/**	ＤＣＳ	*/
				/*
				** DEU申請時にＣＦＲ送出後、ＴＣＦを受信した時にＴＣＦチェックすること
				** 従来は受け捨てていた
				*/
				if (SYB_MaintenanceSwitch[MNT_SW_D7] & NO_TCF_CHECK) { /* MNTSW D7-0 */
					FaxRxDCS_SemiCompatibleCheck();	/**	ＤＣＳセミコンパチチェック	*/
					MDM_ReceiveTCF( RxBaudRate );	/**	トレーニング受信（受捨て）	*/
					FaxHDLC_Transmit( CFR_F, 0 );	/**	ＣＦＲ送出	*/
					break;
				}
				else {
					RxModeChangeRequestedFlag = 1;
					DEU_Return_Flag = 1;
					return;
				}
#if(PRO_MAKER == FX)
			/* FX 独自手順は、NSS のみくる 31.Jly'94 Y.Suzuki */
			case	NSS_F:
				FaxRxFXNSS_SemiCompatibleCheck();	/**	ＤＣＳセミコンパチチェック	*/
				MDM_ReceiveTCF( RxBaudRate );		/**	トレーニング受信（受捨て）	*/
				FaxHDLC_Transmit( CFR_F, 0 );		/**	ＣＦＲ送出	*/
				break;
#endif
			case	CTC_F:					/**	ＣＴＣ	*/
				if (SYS_V34ProcedureExecuting() == 0) {		/* V34ではCTCは無視 1996/06/05 Y.Murata */
					FaxRxDCS_SemiCompatibleCheck();	/**	ＤＣＳセミコンパチチェック	*/
					FaxHDLC_Transmit( CTR_F, 0 );	/**	ＣＴＲ送出	*/
				}
				break;
			case	PPS_F:					/**	ＰＰＳ－Ｑ	*/
				/**	ＰＣ，ＢＣ，ＦＣを前回と今回で比較	*/
				result = CheckPPS_Frame();
				if (result == 1) {				/**	同じ	*/
					FaxHDLC_Transmit( MCF_F, 0 );	/**	ＭＣＦ送出	*/
					MemorizePPS_Frame();			/**	ＰＰＳフレームを記憶	*/
				}
				else if (result == 0) {			/**	違う	*/
					TransmitPPR( 1 );				/**	ＰＰＲ送出（全フレーム指定）	*/
					/*
					** PIXを認識できずにPPS-MPSを２回受信した場合、MCFを返すパスに行ってしまい
					** 受信原稿が消えるのでフレームを記憶しない様にする
					*/
					/* MemorizePPS_Frame(); Del 1998/08/13  By T.Yamaguchi*/
				}
				else {							/**	PPS-NULL / PPS-MPS 以外	*/
					FaxComPerformingFlag = 0;		/**	通信中フラグクリア	*/
					ReceiveError( 0x42 );			/**	Ｒ．４．２	*/
				}
				break;
			case	MPS_F:					/**	ＭＰＳ	*/
				/*
				** ＰＩＸを受信していなくてもＭＰＳを受信すると、無条件にＭＣＦを返していたため、受信
				** 原稿が消えることがあった 1998/08/13  By T.Yamaguchi
				** １枚目のＧ３受信で高速信号を認識せずにＭＰＳを受け取った場合は、Ｒ３．１ｴﾗｰにする
				** ２ページ目以降については対策しない
				*/
				if (SYS_RxTotalPage == 0) {
#if defined (DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
					FaxPhaseE( 1 );			/**	通信終了（ＤＣＮあり）	*/
#else
					FaxPhaseE( 4 );			/**	通信終了（ＤＣＮなし）	*/
#endif
					ReceiveError( 0x31 );	/**	Ｒ．３．１	*/
					break;
				}
				/* ここまで追加 1998/08/13  By T.Yamaguchi */
			case	RR_F:					/**	ＲＲ	*/
				FaxHDLC_Transmit( MCF_F, 0 );	/**	ＭＣＦ送出	*/
				break;
#if (0)/*By Y.Suzuki 1998/09/18*/
//#if defined (ESP)	/*	スペインの申請時に必要	*/
//			case	DTC_F:					/**	ＤＴＣ	*/
//				/**	ポーリング送信に切り替える	*/
//				/*	FinalTxMode = G3MODE	*	Ｇ２／ミニはなし	*/
//				FaxComTxPerformingFlag = 1;
//				FaxComRxPerformingFlag = 0;
//				DIS_ReceivedFlag	   = 0;
//	#if (PRO_FIP == ENABLE)
//				/**	ＦＩＰデータがＲＳ－２３２Ｃ上に流れている場合は，Ｔ．４．１で終了する	*/
//				/*----------------------------------------------------------------------*/
//				/*	??	松竹桜ではＦＩＰがどのコーデックをつかんでいるかわからないため	*/
//				/*	??	ＲＩＣＥでは，どうしましょ？									*/
//				/*----------------------------------------------------------------------*/
//				if (SYS_FIP_Status & (FIP_FILLIN_CMD | FIP_LOCALSCAN_CMD | FIP_RETRIVE_CMD)) {
//					TransmitError( 0x14, 1 );
//					FaxPhaseE( 1 );
//				}
//	#endif
//				break;
#endif
			case	DCN_F:					/**	ＤＣＮ	*/
				ReceiveError( 0x31 );			/**	Ｒ．３．１	*/
				FaxPhaseE( 4 );					/**	通信終了（ＤＣＮなし）	*/
				break;
#if defined(EUR)	/* DTS対策 by M.H 1999/12.28 Naganoでは共通で対策されているがATLANTAでは、EURのみとする */
			case	EOR_F:
				/**	ＥＲＲ応答送信	*/
				TxFCF = ERR_F;
				TxOptionFCF = 0;
				FaxHDLC_Transmit( TxFCF, TxOptionFCF );
				break;
#endif
			default:	/**	その他フレーム	*/
				ReceiveError( 0x42 );			/**	Ｒ．４．２	*/
				FaxPhaseE( 1 );					/**	通信終了（ＤＣＮあり）	*/
				break;
			}
			break;
		default:				/**	タイムアウト	*/
			/**	送信した応答が正常に受信されなかったとして，プリアンブル短縮フラグをクリア	*/
			ShorteningPreambleFlag = 0;
#if defined (DEU) || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
			FaxPhaseE( 1 );			/**	通信終了（ＤＣＮあり）	*/
#else
			FaxPhaseE( 4 );			/**	通信終了（ＤＣＮなし）	*/
#endif
			ReceiveError( 0x31 );	/**	Ｒ．３．１	*/
			break;
		}
	}
}


/*************************************************************************
	module		:[ＥＣＭ再送画データ受信]
	function	:[
		1.	ポストメッセージを受信する
		2.	ＥＣＭ受信では１部分ページ分のエラーフレームがなくなるまで
		.	画データを受信する
		3.	ＥＯＲを受信した場合は，フラグを立ててリターンする
		4.	Ｇ３受信の場合はポストメッセージの受信のみでリターンする
		*.	ＥＣＭ再送受信中は，ＥＣＭ再送受信中フラグを立てる
	]
	return		:[]
	common		:[
		FaxComPerformingFlag
		RxEOR_ReceiveFlag		RxECM_RetransmittedFlag
		RxOptionFCF				RxECM_Mode
		RxPageFinishStatus		RxECM_PixTimeoutFlag
		ECM_FrameCounter		MDM_EcmFrameNumber
	]
	condition	:[]
	comment		:[
		ＥＣＭ受信でない場合も，命令受信のみのために，この関数を一旦通る
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/10]
	author		:[竹内茂樹]
*************************************************************************/
void	RxECM_PixData( void )
{
	UBYTE	rx_fcf;
	UBYTE	f_partial_page;	/**	再送受信中フラグ	*/	/* Jul.18.1994 */
	UBYTE	retry_count;	/** フレーム受信リトライ回数 1997/07/01  By T.Yamaguchi */
	WORD	response_timer;	/* 1997/04/25 Y.Murata *//* Ported from CLOVER 1997/07/26 */

#if defined (DEU) || defined(EUR)	/* PIX受信後のﾎﾟｽﾄﾒｯｾｰｼﾞドイツはＴ２一回で回線断する */
									/* 欧州仕様追加 by M.H 1999/09/16 */
	retry_count = 3;				/** フレーム受信リトライ回数 */
#else
	if (RxECM_PixTimeoutFlag == 1) {	/* ECMタイムアウト回避なら 1997/11/27 T.Yamaguchi */
		retry_count = 3;				/** フレーム受信リトライ回数 */
	}
	else {
		retry_count = 0;				/** フレーム受信リトライ回数 */
	}
#endif
	RxECM_RetransmittedFlag = 1;	/**	ＥＣＭ再送受信初回フラグを立てる	*/
	ECM_FirstFrameCounter	= 0;
	f_partial_page = 0;				/**	再送受信中フラグを初期化	*/

	while ((FaxComPerformingFlag == 1)
	&&	   (RxEOR_ReceiveFlag == 0)) {	/**	通信中&&ＥＯＲ受信なし&&ストップ入力なし	*/

		/**	ストップキー入力ありの時は通信中フラグを落としてループを終了	*/	/* Oct.13.1994 */
		if (SYS_FaxComStopSwitch()) {
			FaxComPerformingFlag = 0;
			break;
		}

#if (PRO_MODEM == R288F) /* Ported from Clover by H.Kubo 1997/07/26 */
		/* 1997/04/25 Y.Murata
		 * Ｒ．４．２対策（ちょうと強引な対策）
		 * V848からR288Fの20PにG3で送信すると、V848は３秒間隔でﾎﾟｽﾄﾒｯｾｰｼﾞを出してくれない時がある
		 * 発生頻度は、ﾘﾝｸ3のﾉｲｽ40dB（SN:29）の条件で１％
		 * 多分、V848の方でﾌﾗｸﾞを誤検出しているように思われる。
		 * この不具合は、ｵﾚﾝｼﾞﾓﾃﾞﾑを使っている機種におこる可能性ありなので、ﾒﾓﾘSWで逃げを作っておく。
		*/
		if (SYS_V34ProcedureExecuting()) {	/* V34 */
			response_timer = TIME_OVER_6SEC;
		}
		else {
			if (CHK_V34_V21_R42EvasionEnable()) {
				response_timer = TIME_OVER_10SEC;
			}
			else {
				response_timer = TIME_OVER_6SEC;
			}
		}
#endif /* (PRO_MODEM == R288F) */

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 199/70/726 */
		if (FCM_ReceiveCommand( response_timer, CONTINUE_CCRETRAIN ) == FSK_RECEIVE) {	/**	命令受信	*/
#else /* (PRO_TX_SPEED == V34) */
		if (MDM_ReceiveCommand((UWORD)TIME_OVER_6SEC) == FSK_RECEIVE) {	/**	命令受信	*/
#endif /* (PRO_TX_SPEED == V34) */
			rx_fcf = CheckReceivedFCF();	/**	受信命令ＦＣＦ確認	*/
			AnalyzeRxPostMessageFrame();	/* ＰＲＩ－Ｑ受信数をカウントするため  Oct.31.1994 */

			if (rx_fcf == DCN_F) {			/**	ＤＣＮ受信	*/
				RxECM_RetransmittedFlag = 0;	/**	ＥＣＭ再送受信初回フラグをクリア	*/
				FaxPhaseE( 4 );					/**	通信終了（ＤＣＮなし）	*/
				ReceiveError( 0x31 );			/**	Ｒ．３．１	*/
				break;							/**	ループ終了	*/
			}

			if (RxECM_Mode == ECM_ON) {		/**	ＥＣＭ受信	*/
				if (FaxComPerformingFlag == 1) {	/**	通信中	*/
					if ((rx_fcf & POST_MESSAGE_F) == POST_MESSAGE_F) {	/**	ポストメッセージを受信	*/

						if (rx_fcf == PPS_F) {		/**	ＰＰＳ－Ｑ受信	*/
							/*	RxECM_PixTimeoutFlag = 0;	**	ＥＣＭタイムアウト回避フラグをクリア	Oct.13.1994	*/
							MemorizePPS_Frame();		/**	ＰＰＳフレームを記憶	*/

							/*	ＲＴＣが２フレームにまたがった場合に検出できないので，ＭＤＭ側(RxPix)で	*/
							/*	受けたフレーム数をデコードできたら，強制終了させるため		Jul.18.1994	*/
							if (f_partial_page == 0) {		/**	再送分でない時	*/
								/**	受けたブロックのフレーム数をＭＤＭ用の変数にセット	*/
								MDM_EcmFrameNumber = ECM_FrameCounter;
							}

							/**	エラーフレームチェック	*/
							if (JudgeECM_RxErrorFrame() == 1) {	/**	エラーフレームあり	*/
								RxECM_PixTimeoutFlag = 0;	/**	ＥＣＭタイムアウト回避フラグをクリア	*/	/* Oct.13.1994 */
#if (PRO_PRINTER_RX == ENABLE)
								if (RxPrinterErrorFlag == 1) {	/**	プリンタエラーあり	*/
									FaxPhaseE( 1 );			/**	ＤＣＮ送出	*/
									ReceiveError( 0x45 );	/**	Ｒ．４．５	*/
									break;					/**	ループ終了	*/
								}
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/3/9 K.Kawata*/
								if (PRN_Control.Error) {
									FaxPhaseE( 1 );			/**	ＤＣＮ送出	*/
									ReceiveError( 0x45 );	/**	Ｒ．４．５	*/
									break;					/**	ループ終了	*/
								}
#endif
								f_partial_page = 1;	/**	再送受信中フラグをセット	*/
								TransmitPPR( 0 );	/**	ＰＰＲ送出（エラーフレーム）	*/
								StartECM_RxPix();	/**	ＥＣＭ再送高速データ受信待ち	*/

								if ((FaxComPerformingFlag == 1)
								&&	(RxEOR_ReceiveFlag == 0)) {		/**	高速データ受信できた&&ＥＯＲ受信なし	*/
									/**	Ｔ３０モニタ用データをセット	*/
									SaveT30TimingData( SYS_T30_START_TIME );
									SaveT30Data( SYS_T30_RX_PIX, &MDM_ModemBuffer[0][0], 0 );

#if (PRO_MODEM == R288F)				/* ROCKWELL製 28.8K */
									FaxComPhaseStatus = FAX_RX_PH_C_RPIX;
									/*------------------------------------------------------*/
									/* プライマリチャネルに入る前にデータレイトをリード     */
									/* 送信局よりオートでデータレイト変わるかもしれへんから */
									/*------------------------------------------------------*/
									FCM_SetRxDataRate();
#endif

									/**	ＥＣＭ再送画データ受信	*/
									RxPageFinishStatus = MDM_RxEcmPartialPage();
									MDM_RxPixClose( RxECM_Mode );

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/07/26 */
									FaxComPhaseStatus = FAX_RX_PH_C_AFTER_RPIX;
#endif /* (PRO_TX_SPEED == V34) */

									/**	通信結果確認，エラーコードセット	*/
									CheckRxPixResultPhaseC();
									if (FaxComPerformingFlag == 0) {
										FaxPhaseE( 4 );
										/*	ループ終了	*/
									}
								}
							}
							else {		/**	エラーなし	*/
								/* ICHOU追加 by T.Soneoka 1996/09/12 */
								if (RxPmType == RX_BKUPRAM) {
#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
									/* フラッシュＲＯＭ書込み中なら */
									if (SYB_FlashROM_WriteStatus == ROM_DATA_RXING) {		/* フラッシュＲＯＭデータ受信中 */
										CopyRomDataEcmBufferToDRAM();
										if (RxFCF == NULL_FF) {
											MDM_PhaseC_Status = RX_BLOCK_END;	/* RX_PAGE_END は 1,RX_BLOCK_ENDは 2 */
										}
										else {
											MDM_PhaseC_Status = RX_PAGE_END;
										}
									}
									else {
										CopyEcmBufferToBackUpRAM();
										MDM_PhaseC_Status = RX_PAGE_END;
									}
#else
 #if (PRO_DIAG == ENABLE) /* added by H.Kubo 1998/04/02 */
									CopyEcmBufferToBackUpRAM();
									MDM_PhaseC_Status = RX_PAGE_END;
 #endif
#endif
								}
								break;	/**	ループ終了	*/
							}
						}
						else {		/**	ＥＯＲ－Ｑ受信（拡張ＦＣＦ）	*/
							RxEOR_ReceiveFlag = 1;			/**	ＥＯＲ受信済みフラグセット	*/
							RxECM_RetransmittedFlag = 0;	/**	ＥＣＭ再送受信初回フラグをクリア	*/
							break;							/**	ループ終了	*/
						}
					}
					else {		/**	ポストメッセージ以外を受信	*/
						FaxPhaseE( 1 );			/**	ＤＣＮ送出	*/
						ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
						break;					/**	ループ終了	*/
					}
				}
				else {		/**	再送受信前プロトコルエラー	*/
					FaxPhaseE( 1 );			/**	ＤＣＮ送出	*/
					ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
					break;					/**	ループ終了	*/
				}
			}
			else {		/**	Ｇ３受信	*/
#if (PRO_PAPER_TYPE == ROLL_PAPER)
				/*	ＥＣＭプリンタ受信の時は，カット待ちで命令受信を空振りした後	*/
				/*	ＲＮＲ処理をするので，Ｇ３受信の場合だけとする		Sep.14.1994	*/
				/*	ＰＲＩ－Ｑの場合は会話予約処理の後カット待ちする	Oct.31.1994	*/
  #if (PRO_PRINTER_RX == DISABLE)
				/* プリンター受信中のプリンターエラー発生時（カッターエラー/ＨｉｇｈＴｅｍｐ）
				** ポストメッセージに応答できなかった
				** by O.Kimoto 1999/01/05
				*/
				if ((RxPmType == RX_PRINTER)
				&&	(PRI_Q_RxFlag == 0)) {		/**	プリンタ受信の場合	*/
					if (WaitRxPaperCut( 25 ) == 0) {	/**	記録紙カット中→２．５秒経過	*/
						continue;						/**	もう一度，命令受信(ループの先頭)へ	*/
					}
					CheckRxPrinterError();				/**	プリンタエラーの種類を確認	*/
				}
  #else
				if ((RxPmType == RX_PRINTER)
				&&	(PRI_Q_RxFlag == 0)
				&&	(!PrinterError)) {		/**	プリンタ受信の場合	*/
					if (WaitRxPaperCut( 25 ) == 0) {	/**	記録紙カット中→２．５秒経過	*/
						CheckRxPrinterError();				/**	プリンタエラーの種類を確認	*/
						if (RxPageFinishStatus == RX_PRT_ERR) {
							/* Nothing */
						}
						else {
							continue;						/**	もう一度，命令受信(ループの先頭)へ	*/
						}
					}
				}
				if (RxPmType == RX_PRINTER) {
					CheckRxPrinterError();				/**	プリンタエラーの種類を確認	*/
				}
  #endif
#endif
				RxECM_RetransmittedFlag = 0;	/**	ＥＣＭ再送受信初回フラグをクリア	*/
				break;							/**	ループ終了	*/
			}
		}
		else {		/**	命令受信なし	*/
			/*
			** ﾎﾟｽﾄﾒｯｾｰｼﾞが取れない場合、Ｔ２タイマ経過後すぐに回線断しているが、ECMの場合は３回試行
			** が正しいので、ECM、G3に関係なく３回試行の条件を追加	1997/07/01  By T.Yamaguchi
			*/
			if (++retry_count >= 3) {
				FaxPhaseE( 4 );			/**	通信終了（ＤＣＮなし）	*/
				ReceiveError( 0x42 );	/**	Ｒ．４．２	*/
				break;					/**	ループ終了	*/
			}
		}
	}
}


/*************************************************************************
	module		:[ＥＣＭ再送高速データ受信待ち]
	function	:[
		1.	高速画データを受信するまで繰り返す
		2.	命令受信した場合は適当な応答を送信し，再度受信する
		3.	受信タイムアウトや不正な命令を受信した場合は，通信中フラグをクリアする
		4.	プリアンブル短縮フラグは，高速データ受信時にセットする
	]
	return		:[]
	common		:[
		FaxComPerformingFlag
		RxEOR_ReceiveFlag
		RxFCF		RxOptionFCF
		RxECM_Mode
		RxBaudRate
	]
	condition	:[]
	comment		:[
		Sep.07.1994		プリアンブル短縮フラグのＯＮ／ＯＦＦ
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/15]
	author		:[竹内茂樹]
*************************************************************************/
void	StartECM_RxPix( void )
{

#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/07/26 */
	if (SYS_V34ProcedureExecuting() == 1) {	/* CTS ON の時にﾘｰﾄﾞ 1996/03/04 */
		RxBaudRate = FCM_CheckRxDataRate();
	}
#endif /* (PRO_TX_SPEED == V34) */

	while ((FaxComPerformingFlag == 1)
	&&	   (RxEOR_ReceiveFlag == 0)) {	/**	通信中&&ＥＯＲ受信なし&&ストップ入力なし	*/

		/**	ストップキー入力ありの時は通信中フラグを落としてループを終了	*/	/* Oct.13.1994 */
		if (SYS_FaxComStopSwitch()) {
			FaxComPerformingFlag = 0;
			break;
		}

		/*----------------------*/
		/*	高速／低速受信識別	*/
		/*----------------------*/
#if (PRO_TX_SPEED == V34) /* Ported from Clover by H.Kubo 1997/07/26 */
		switch (FCM_FskHighSpeedCheck( RxBaudRate, RxECM_Mode )) {	/**	高低速識別	*/
#else /* (PRO_TX_SPEED == V34)  */
		switch (MDM_FskHighSpeedCheck( RxBaudRate, RxECM_Mode )) {	/**	高低速識別	*/
#endif /* (PRO_TX_SPEED == V34)  */

#if (PRO_MODEM == R288F)
		case	TURN_OFF_RECEIVE: /* from CLOVER\src\fcmrxc.c */
#endif /* (PRO_MODEM == R288F) */
		case	TRN_RECEIVE:	/**	高速画データ受信	*/
			/**	プリアンブル短縮フラグをセット	*/
			ShorteningPreambleFlag = PostSpeedHandshakeFlag;
			return;							/**	ＯＫリターン	*/
			break;
		case	FSK_RECEIVE:	/**	ＦＳＫ命令受信	*/
#if (PRO_MODEM == ORANGE3)		/* Ｈ８では不要	 Feb.06.1995 */
			SaveReceivedT30Data();			/**	Ｔ３０データをセット	*/
#endif
			/**	送信した応答が正常に受信されなかったとして，プリアンブル短縮フラグをクリア	*/
			ShorteningPreambleFlag = 0;

			switch (CheckReceivedFCF()) {	/**	受信フレーム	*/
			case	PPS_F:					/**	ＰＰＳ－Ｑ	*/
				TransmitPPR( 0 );				/**	ＰＰＲ送出（エラーフレーム）	*/
				break;
			case	CTC_F:					/**	ＣＴＣ	*/
				if (SYS_V34ProcedureExecuting() == 0) { /* Added by H.Kubo 1997/07/26 */ /* V34ではCTCは無視 1996/06/05 Y.Murata */
					FaxRxDCS_SemiCompatibleCheck();	/**	ＤＣＳセミコンパチチェック	*/
					FaxHDLC_Transmit( CTR_F, 0 );	/**	ＣＴＲ送出	*/
				}
				break;
			case	EOR_F:					/**	ＥＯＲ－？？？	*/
				RxEOR_ReceiveFlag = 1;			/**	ＥＯＲ受信済みフラグセット	*/
#if defined(DEU) || defined(EUR)	/* 「EOR-PRI-Q受信後の会話予約が動作しない」の対策 */
									/* 欧州仕様追加 by M.H 1999/09/16 */
				/* CCITTでは、ｵﾌﾟｼｮﾝのため、DTSで規定されているDEUのみの対策とします。*/
				AnalyzeRxPostMessageFrame();	/* ＰＲＩ－Ｑ受信フラグをセットするため  Dec.3.1997 by M.H.*/
#endif
				break;
			case	DCN_F:					/**	ＤＣＮ	*/
				ReceiveError( 0x42 );			/**	Ｒ．４．２	*/
				FaxPhaseE( 4 );					/**	通信終了（ＤＣＮなし）	*/
				break;
			default:						/**	その他フレーム	*/
				ReceiveError( 0x42 );			/**	Ｒ．４．２	*/
				FaxPhaseE( 1 );					/**	通信終了（ＤＣＮなし）	*/
				break;
			}
			break;
		default:			/**	タイムアウト	*/
			/**	送信した応答が正常に受信されなかったとして，プリアンブル短縮フラグをクリア	*/
			ShorteningPreambleFlag = 0;
#if defined (DEU)  || defined(EUR)	/* 欧州仕様追加 by M.H 1999/09/16 */
			FaxPhaseE( 1 );			/**	通信終了（ＤＣＮあり）	*/
#else
			FaxPhaseE( 4 );			/**	通信終了（ＤＣＮなし）	*/
#endif
			ReceiveError( 0x52 );	/**	Ｒ．５．２	*/
			break;
		}
	}
}


#if (PRO_DIAG == ENABLE) /* #if is added by H.Kubo 1998/04/02 */
/*************************************************************************
	module		:[高速ＲＤＳ データライト]
	function	:[ＥＣＭバッファからバックアップＲＡＭデータにコピーする
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[CDC]
	date		:[1996/6/17]
	author		:[曽根岡拓]
*************************************************************************/
void CopyEcmBufferToBackUpRAM(void)
{
	UBYTE i;
	UBYTE *start_address;
	UBYTE *current_address;
	UWORD size;

	current_address = (UBYTE *)&EcmBuffer[0][0];
	start_address = current_address;

#if 0 /* 1998/02/18  By T.Yamaguchi */
//	for (i = 0; i < HIGH_RDS_DATA_MAX; i++) {
//		size = HighRDS_Table[i].BackupDataLength;
//		if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//			MemoryMove((UBYTE *)HighRDS_Table[i].BackupDataAddress, (UBYTE *)current_address, size);
//			current_address += size;
//		}
//		else {
//			MemoryMove((UBYTE *)HighRDS_Table[i].BackupDataAddress, (UBYTE *)current_address,
//					   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//			current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//			return;
//		}
//	}
#endif
	for (i = 0; i < HIGH_RDS_DATA_MAX; i++) {
		size = HighRDS_Table[i].BackupDataLength;

		/* ライト禁止項目は、バックアップＲＡＭに書き込まない */
		if (((UBYTE *)HighRDS_Table[i].BackupDataAddress != (UBYTE *)&SYB_OptionROM_Revision)
		 && ((UBYTE *)HighRDS_Table[i].BackupDataAddress != (UBYTE *)&SYB_CPU_Revision)
		 && ((UBYTE *)HighRDS_Table[i].BackupDataAddress != (UBYTE *)&SYB_WordingNumber)
#if (PRO_EXT_ROM == ENABLE)		/* By M.Tachibana 1998/03/12 */
		 && ((UBYTE *)HighRDS_Table[i].BackupDataAddress != (UBYTE *)&SYB_ExtRomRevision)
#endif
		 && ((UBYTE *)HighRDS_Table[i].BackupDataAddress != (UBYTE *)&SYB_MailBox)) {

#if (0) /* 余計なアドレス演算子が入ってます。 by H.Kubo 1998/03/16 */
@			if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
@				MemoryMove((UBYTE *)HighRDS_Table[i].BackupDataAddress, (UBYTE *)current_address, size);
@				current_address += size;
@			}
@			else {
@				MemoryMove((UBYTE *)HighRDS_Table[i].BackupDataAddress, (UBYTE *)current_address,
@						   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
@				current_address += (BackUpDataLength-((*current_address)-(*start_address)));
@				return;
@			}
@		}
#else
			if (BackUpDataLength >= ( (UWORD) (current_address - start_address) )  + size) {
				MemoryMove((UBYTE *)HighRDS_Table[i].BackupDataAddress, (UBYTE *)current_address, size);
				current_address += size;
			}
			else {
				MemoryMove((UBYTE *)HighRDS_Table[i].BackupDataAddress, (UBYTE *)current_address,
						   (UWORD)(BackUpDataLength -((UWORD) (current_address - start_address) ) ) );
				current_address += (BackUpDataLength - ( (UWORD) (current_address - start_address) )  );
				return;
			}
		}
#endif
		else {
			current_address += size;
		}
	}


#if (0)
//	/* ＥＣＭバッファから機器パラメータに転送 */
//	size = sizeof(SYS_MachineParameter);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_MachineParameter, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_MachineParameter, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから機種共通メモリＳｗに転送 */
//	size = sizeof(SYS_MemorySwitch);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_MemorySwitch, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_MemorySwitch, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから機種固有メモリＳｗに転送 */
//	size = sizeof(SYS_MachineUniqSwitch);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_MachineUniqSwitch, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_MachineUniqSwitch, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//
//#if (0)
//	/* ＥＣＭバッファから保守メモリＳｗに転送 */
//	size = sizeof(SYS_MaintenanceSwitch);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_MaintenanceSwitch, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_MaintenanceSwitch, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//#endif
//
//	/* ＥＣＭバッファからワンタッチダイヤルに転送 */
//	size = sizeof(SYS_OnetouchDial);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_OnetouchDial, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_OnetouchDial, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから短縮ダイヤルに転送 */
//	size = sizeof(SYS_SpeedDial);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_SpeedDial, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_SpeedDial, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファからプログラムワンタッチに転送 */
//	size = sizeof(SYS_ProgramOnetouch);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_ProgramOnetouch, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_ProgramOnetouch, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから転送先番号に転送 */
//	size = sizeof(SYS_SubDial);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_SubDial, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_SubDial, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから部門別料金に転送 */
//	size = sizeof(SYS_DepartFile);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_DepartFile, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_DepartFile, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから一括送信に転送 */
//	size = sizeof(SYS_BatchTxFile);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_BatchTxFile, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_BatchTxFile, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから料金管理に転送 */
//	size = sizeof(SYS_CostTable);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_CostTable, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_CostTable, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから市外料金に転送 */
//	size = sizeof(SYS_NTT_AccessFile);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_NTT_AccessFile, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_NTT_AccessFile, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファからコメントに転送 */
//	size = sizeof(SYS_CoverPageMessage);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_CoverPageMessage, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_CoverPageMessage, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから発信元番号に転送 */
//	size = sizeof(SYS_ID_Buffer);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_ID_Buffer, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_ID_Buffer, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから発信元名に転送 */
//	size = sizeof(SYS_TTI_Buffer);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_TTI_Buffer, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_TTI_Buffer, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファからカナＩＤに転送 */
//	size = sizeof(SYS_TTI_ID_Buffer);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_TTI_ID_Buffer, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_TTI_ID_Buffer, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから親展ボックスに転送 */
//	size = sizeof(SYS_MailBox);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_MailBox, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_MailBox, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファから受信モードに転送 */
//	size = sizeof(SYS_RxModeSwitch);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_RxModeSwitch, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_RxModeSwitch, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファからワーディングに転送 */
//	size = sizeof(SYS_WordingNumber);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_WordingNumber, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_WordingNumber, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
//
//	/* ＥＣＭバッファからライフモニタに転送 */
//	size = sizeof(SYS_LifeMonitor);
//	if (BackUpDataLength >= (*current_address)-(*start_address)+size) {
//		MemoryMove((UBYTE *)&SYS_LifeMonitor, (UBYTE *)current_address, size);
//		current_address += size;
//	}
//	else {
//		MemoryMove((UBYTE *)&SYS_LifeMonitor, (UBYTE *)current_address,
//				   (UWORD)(BackUpDataLength-((*current_address)-(*start_address))));
//		current_address += (BackUpDataLength-((*current_address)-(*start_address)));
//		return;
//	}
#endif
}
#endif /* (PRO_DIAG == ENABLE) */

#if (PRO_RDS_FLASH_ROM_WRITE == ENABLE)
/*************************************************************************
	module		:[高速ＲＤＳ ＲＯＭデータライト]
	function	:[ＥＣＭバッファからＤＲＡＭにコピーする
	]
	return		:[なし]
	common		:[]
		ECM_PageCounter;		ページカウンタ
		ECM_BlockCounter;		ブロックカウンタ
		ECM_FrameCounter;		フレームカウンタ
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/03/24]
	author		:[山口]
*************************************************************************/
void CopyRomDataEcmBufferToDRAM(void)
{
	UWORD *write_start_address;
	UWORD *current_address;
	UWORD size;
	UWORD sum;
	/* UBYTE debug_sw;	*/

	/* debug_sw = 0;	*/

	current_address = (UWORD *)&EcmBuffer[0][0];
	/* write_start_address = (UWORD *)0x01000000;	*/	/* ROM_DATA_WRITE_ADDRESS; */		/* 機種によりことなる */
	write_start_address = (UWORD *)ROM_DATA_WRITE_ADDRESS;	/* 機種によりことなる */

	/*	write_start_address = (write_start_address + (UWORD *)(0x10000 * ECM_BlockCounter)); */	/* フロック数×０ｘ１００００（６４Ｋ） */
	write_start_address += (UDWORD)ECM_BlockCounter << 15;	/* フロック数×０ｘ１００００（６４Ｋ） */
	/* size = (UWORD)(((UWORD)(ECM_FrameCounter + 1) * (FcomEcmSize/2))); */ /* FcomEcmSize = 256固定 UWORDでコピーするため２で割る */
	size = (UWORD)(((UWORD)(ECM_FirstFrameCounter + 1) * (FcomEcmSize/2))); /* FcomEcmSize = 256固定 UWORDでコピーするため２で割る */

#if 0	/* 削除 1998/04/26  By T.Yamaguchi */
//	if (debug_sw == 1) {	/* 204msかかっています */
//		MemoryMoveWord((UWORD *)write_start_address, (UWORD *)current_address, size);
//		sum = SumCheck((UWORD *)write_start_address,(UDWORD)size);
//	}
//	else if (debug_sw == 2) {
//		MemoryMoveWord((UWORD *)write_start_address, (UWORD *)current_address, size);
//		sum = SumCheck((UWORD *)current_address,(UDWORD)size);
//		sum = SumCheck((UWORD *)write_start_address,(UDWORD)size);
//		sum = MemoryMoveWordAndSum((UWORD *)write_start_address, (UWORD *)current_address, size);
//	}
//	else {	/* 195msかかっています */
//		/* ワードでコピーしながらサムを計算して行きます */
//		sum = MemoryMoveWordAndSum((UWORD *)write_start_address, (UWORD *)current_address, size);
//	}
#endif
	sum = MemoryMoveWordAndSum((UWORD *)write_start_address, (UWORD *)current_address, size);


	FCM_ROMDataSum += sum;
}

#if 0	/* 削除 1998/04/26  By T.Yamaguchi */
///*************************************************************************
//	module		:[高速ＲＤＳ ＲＯＭデータライト]
//	function	:[従来のメモリーコピーの関数はUBYTE型だったものを
//					WORDでコピーするものに変更
//				ＤＴＣを使った方が早いかも
//	]
//	return		:[なし]
//	common		:[]
//	condition	:[
//	]
//	comment		:[
//	]
//	machine		:[SH7043]
//	language	:[SHC]
//	keyword		:[FCM]
//	date		:[1998/03/24]
//	author		:[山口]
//*************************************************************************/
//void MemoryMoveWord(register UWORD	*src_adr,register UWORD	*tgt_adr,UWORD	cnt)
//{
//	while (cnt--) {
//		*src_adr++ = *tgt_adr++;
//	}
//}
#endif

/*************************************************************************
	module		:[高速ＲＤＳ ＲＯＭデータライト]
	function	:[従来のメモリーコピーの関数はUBYTE型だったものを
					WORDでコピーするものに変更
				ＤＴＣを使った方が早いかも
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/03/24]
	author		:[山口]
*************************************************************************/
UWORD MemoryMoveWordAndSum(UWORD	*src_adr,UWORD	*tgt_adr,UWORD	cnt)
{
	UWORD sumcheck;

	sumcheck = 0;
	while (cnt--) {
		sumcheck += *tgt_adr;
		*src_adr++ = *tgt_adr++;
	}
	return(sumcheck);
}

/*************************************************************************
	module		:[サムチェック（１６ビット）]
	function	:[
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1998/03/24]
	author		:[山口]
*************************************************************************/
UWORD SumCheck(UWORD *tgt_adr,UDWORD cnt)
{
	UWORD sumcheck;

	sumcheck = 0;
	while (cnt--) {
		sumcheck += *tgt_adr++;
	}
	return(sumcheck);
}

#endif
