/*---------------------------------------------------------------------------*/
/*	プロジェクト : ATLANTA		ANZUを移植									 */
/*	ファイル名	 : FCMFIF1.C												 */
/*	モジュール	 :															 */
/*				 : CheckDocPaperSize()										 */
/*				 : CheckPollingDocuments()									 */
/*				 : CheckTxMemorySize()										 */
/*				 : CheckRestMemory()										 */
/*				 : CheckPasscodeBuf()										 */
/*				 : CheckSecureMailBox()										 */
/*				 : CheckDatabasePollingData()								 */
/*				 : CheckRelayedBroadcastGroup()								 */
/*				 : CheckExpandFieldBIT()									 */
/*				 : CheckMMRinNonStandardFrame()								 */
/*				 : CheckPassCodeMatching()									 */
/*				 : CheckPartnerSCFR_Func()									 */
/*				 : CheckPartnerRCR_Func()									 */
/*				 : CheckPartnerPassCodeSetting()							 */
/*				 : CheckPartnerSecureMailFunc()								 */
/*				 : CheckPartnerRelayBroadCastFunc()							 */
/*				 : CheckPartnerDB_PollingFunc()								 */
/*				 : CheckPartnerCharMailFunc()								 */
/*	作成者		 : 山口														 */
/*	日	付		 :1996/11/19												 */
/*	概	要		 :															 */
/*				 :															 */
/*	修正履歴	 :															 */
/*				 :															 */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\PRODUCT.H"
#include "\src\atlanta\define\SYSDOC.H"
#include "\src\atlanta\define\FCM_DEF.H"
#include "\src\atlanta\define\STD.H"
#include "\src\atlanta\define\mem_def.H"
#include "\src\atlanta\define\SYS_STAT.H"
#include "\src\atlanta\ext_v\BKUPRAM.H"
#include "\src\atlanta\ext_v\FCM_DATA.H"
#include "\src\atlanta\ext_v\SYS_DATA.H"
#include "\src\atlanta\ext_v\MEM_DATA.H"
#include "\src\atlanta\define\FCM_PRO.H"
#include "\src\atlanta\define\MEM_PRO.H"
#include "\src\atlanta\define\mntsw_b.h"	/* 96/07/29 add By T.Yamaguchi */

/* MDM */
#if (PRO_MODEM == ORANGE3) /* Added by H.Kubo 1997/07/25 */
#include "\src\atlanta\mdm\orange\define\MDM_DEF.H"
#include "\src\atlanta\mdm\orange\ext_v\MDM_DATA.H"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* Added by H.Kubo 1997/07/25 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\MDM_DEF.H"
#include "\src\atlanta\mdm\r288f\ext_v\MDM_DATA.H"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"		/*	TONE_1080HZ, AFTER_DIAL_FILTER */
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"	/* Add By O.Kimoto 1996/04/24 */
#endif
#include "\src\atlanta\define\mlt_pro.h"

/*DPR*/
#if (PRO_DPRAM == ENABLE)
#include  "\src\atlanta\ext_v\dpr_data.h"
#include  "\src\atlanta\define\dpr_pro.h"
#endif

/*************************************************************************
	module		:[記録紙幅チェック]
	function	:[
		ダブルカセットの場合､大きい方のサイズを返す
	]
	return		:[]
	common		:[
					SYS_Paper1Size
					SYS_Paper2Size
					??WarningStatus該当するパラメータはあるのか確認
	]
	condition	:[]
	comment		:[カセットタイプ(桐､ラベンダー)とロール紙タイプは別にする
					94/12/20 椛用熱転処理追加
					95/1/25	 桐は、紙無し時A3を返すように修正。 SYS_Paper1､2Size に何もセットされないため。
							ラベンダーは、そのまま(A4)｡
					ANZU	A4,LTR,B5
					96/09/25 トレイの用紙サイズが、Ａ５、Ｂ５がセットされた場合、ＰＣプリントでしか、プリント
　　　　　　　　　　しない為、A5/B5のケース文を、PRO_PC_PRINTで条件コンパイルをいれた。By J.Miyazaki 1996/09/25
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UBYTE CheckDocPaperSizeFlsRom(void)
#else
UBYTE CheckDocPaperSize(void)
#endif
{
#if (PRO_PAPER_TYPE == CUT_PAPER)
 #if (PRO_PRINT_TYPE == LASER)	/* ANZU */
	UBYTE cassette1;
	UBYTE cassette2;
	/*	上段の紙サイズチェック	*/
	switch (SYS_Paper1Size) {		/**	上段記録紙サイズ	*/
  #if (PRO_PC_PRINT == DISABLE)	/* By J.Miyazaki 1996/09/25 */
		/* ＰＣプリントでのみプリントする用紙サイズ。その他ではプリントされない */
		case SYS_A5_PAPER:	/**	A5	*/
  #endif
		case SYS_LT_PAPER:	/**	LETTER	*/
		case SYS_A4_PAPER:	/**	A4	*/
		case SYS_LG_PAPER:	/**	LEGAL	*/
			/**	A4サイズセット	*/
			cassette1 = SYS_A4_PAPER;
			break;
  #if (PRO_PC_PRINT == DISABLE)	/* By J.Miyazaki 1996/09/25 */
		/* ＰＣプリントでのみプリントする用紙サイズ。その他ではプリントされない */
		case SYS_B5_PAPER:	/**	B5	*/
  #endif
		case SYS_B4_PAPER:	/**	B4	*/
			/**	B4サイズセット	*/
			cassette1 = SYS_B4_PAPER;
			break;
		case SYS_A3_PAPER:	/**	A3	*/
		case SYS_LTR_PAPER:	/**	LETTER横 by NOBUKO	Aug.31,94 */
		case SYS_A4R_PAPER:	/**	A4横	 by NOBUKO	Aug.31,94 */
			/**	A3サイズセット	*/
			cassette1 = SYS_A3_PAPER;
			break;
		case SYS_NO_CASSETTE:	/**	カセットなし	*/
		case SYS_NO_PAPER:		/** 紙なし						*/
		default:				/* add By t.yamaguchi '96.03.15 */
			/**	カセットなし	*/
			cassette1 = SYS_NO_CASSETTE;
			break;
	}
	/*	下段の紙サイズチェック	*/
	switch (SYS_Paper2Size) {		/**	下段記録紙サイズ	*/
		case SYS_A5_PAPER:	/**	A5	*/
		case SYS_LT_PAPER:	/**	LETTER	*/
		case SYS_A4_PAPER:	/**	A4	*/
		case SYS_LG_PAPER:	/**	LEGAL	*/
			/**	A4サイズセット	*/
			cassette2 = SYS_A4_PAPER;
			break;
		case SYS_B5_PAPER:	/**	B5	*/
		case SYS_B4_PAPER:	/**	B4	*/
			/**	B4サイズセット	*/
			cassette2 = SYS_B4_PAPER;
			break;
		case SYS_A3_PAPER:	/**	A3	*/
		case SYS_LTR_PAPER:	/**	LETTER横 by NOBUKO	Aug.31,94 */
		case SYS_A4R_PAPER:	/**	A4横	 by NOBUKO	Aug.31,94 */
			/**	A3サイズセット	*/
			cassette2 = SYS_A3_PAPER;
			break;
		case SYS_NO_CASSETTE:	/**	カセットなし	*/
		case SYS_NO_PAPER:		/** 紙なし						*/
		default:				/* Add By T.Yamaguchi '96.03.15 */
			/**	カセットなしセット	*/
			cassette2 = SYS_NO_CASSETTE;
			break;
	}
	/*	上段・下段共紙あり	*/
	if((cassette1 != SYS_NO_CASSETTE) && (cassette2 != SYS_NO_CASSETTE)) {	/**	上段､下段共紙あり	*/
		/* できるだけ縮小をしないで済む（大きいサイズ）様にする */
		switch (cassette1) {		/**	上段記録紙サイズ	*/
			case SYS_A4_PAPER:	/**	A4	*/
				/**	リターン下段の記録紙サイズ	*/
				return(cassette2);
				break;
			case SYS_B4_PAPER:	/**	B4	*/
				/**	リターン上段の記録紙サイズ	*/
				if(cassette2 != SYS_A3_PAPER) {
					return(cassette1);
				}
				else {
					return(cassette2);
				}
				break;
			case SYS_A3_PAPER:	/**	A3	*/
				/**	リターン上段の記録紙サイズ	*/
				return(cassette1);
				break;
		}
	}
	/*	下段がなし	*/
	else if((cassette2 == SYS_NO_CASSETTE) && (cassette1 != SYS_NO_CASSETTE)) {	/**	下段の記録紙なし	*/
		/**	リターン上段の記録紙サイズ	*/
		return(cassette1);
	}
	/*	上段がなし	*/
	else if((cassette1 == SYS_NO_CASSETTE) && (cassette2 != SYS_NO_CASSETTE)) {	/**	下段の記録紙なし	*/
		/**	リターン下段の記録紙サイズ	*/
		return(cassette2);
	}
	/*	上段・下段共紙なし	*/
	else {
  #if defined(JPN)
   #if (PRO_MAKER == FX)
		/* 常にA3を返す 25.Jan'95  Y.Suzuki */
		return(SYS_A3_PAPER);
   #else
		/* カセットの爪を見る。極力大きな記録紙巾を返すようにする　A3追加 8.Jly'94 Y.Suzuki */
		if((SYS_Paper1Size == SYS_A5_PAPER) || (SYS_Paper1Size == SYS_LT_PAPER) ||
			(SYS_Paper1Size == SYS_A4_PAPER) || (SYS_Paper1Size == SYS_LG_PAPER)) {		/**	上段記録紙幅A5､LETTER､A4､LEGAL	*/
			if((SYS_Paper2Size == SYS_A5_PAPER) || (SYS_Paper2Size == SYS_LT_PAPER) ||
				(SYS_Paper2Size == SYS_A4_PAPER) || (SYS_Paper2Size == SYS_LG_PAPER)) {		/**	下段記録紙幅A5､LETTER､A4､LEGAL	*/
				/**	リターンA4	*/
				return(SYS_A4_PAPER);
			}
		}
		if((SYS_Paper1Size == SYS_A3_PAPER) || (SYS_Paper2Size == SYS_A3_PAPER)) {		/**	上段または下段記録紙幅 A3	*/
			/**	リターンA3	*/
			return(SYS_A3_PAPER);
		}
		/**	リターンB4	*/
		return(SYS_B4_PAPER);
   #endif
  #else
		return(SYS_A4_PAPER);
  #endif
	}	
 #else	
  #if defined(STOCKHM2)	/* DVT修正：820-020130 by SMuratec 夏 2004/7/30 */
  	 /**	リターンA4	*/
  	 /* 修正理由：STOCKHOLM2機種中で１ヶカセットだけがある。記録紙サイズはA4だけ。*/ 
	 return(SYS_A4_PAPER);	
  #else /* POPLAR *//* By M.Tachibana 1997/04/22 */
	UBYTE i;
	UBYTE sys_paper_size[3];
	UBYTE cassette[3];

	sys_paper_size[0] = SYS_Paper1Size;
	sys_paper_size[1] = SYS_Paper2Size;
	sys_paper_size[2] = SYS_Paper3Size;

	for (i = 0; i < 3; i++) {
		switch (sys_paper_size[i]) {
		case SYS_A4_PAPER:
		case SYS_A5R_PAPER:
		case SYS_LT_PAPER:
		case SYS_LG_PAPER:
			cassette[i] = SYS_A4_PAPER;
			break;
		case SYS_B4_PAPER:
		case SYS_B5R_PAPER:
			cassette[i] = SYS_B4_PAPER;
			break;
		case SYS_A3_PAPER:
		case SYS_A4R_PAPER:
			cassette[i] = SYS_A3_PAPER;
			break;
		case SYS_NO_CASSETTE:
		case SYS_NO_PAPER:
			cassette[i] = SYS_NO_CASSETTE;
			break;
		default:
			cassette[i] = SYS_NO_CASSETTE;
			break;
		}
	}

	/* 現在装着されている最大の紙サイズを探します */
#if (0)	/* POPLARはＡ３記録紙はセットできません */
//	for (i = 0; i < 3; i++) {
//		if (cassette[i] == SYS_A3_PAPER) {
//			return(SYS_A3_PAPER);
//		}
//	}
#endif
	/* 回転基盤が存在する場合は、Ａ４原稿しかなくてもＢ４幅を返す 1997/04/24  By T.Yamaguchi */
	if (DPR_SlaveBoardEnable && DPR_CheckRotateBoardExist()) {	/** 回転オプション基盤装着時 */
		if (SYB_MaintenanceSwitch[MNT_SW_B4] & ROTATE_DIS_A3_BIT_ON) {	/* B4-1 0:A3 1:B4 */
			for (i = 0; i < 3; i++) {
				if (cassette[i] == SYS_B4_PAPER) {
					return(SYS_B4_PAPER);
				}
			}
			for (i = 0; i < 3; i++) {
				if (cassette[i] == SYS_A4_PAPER) {
					return(SYS_A4_PAPER);
				}
			}
			return(SYS_B4_PAPER);
		}
		else {
			return(SYS_A3_PAPER);
		}
	}
	for (i = 0; i < 3; i++) {
		if (cassette[i] == SYS_B4_PAPER) {
			return(SYS_B4_PAPER);
		}
	}
	for (i = 0; i < 3; i++) {
		if (cassette[i] == SYS_A4_PAPER) {
			return(SYS_A4_PAPER);
		}
	}
	/* 全カセットに紙がない場合Ｂ４を返します */
	return(SYS_B4_PAPER);
	#endif	/* DVT修正：820-020130 by SMuratec 夏 2004/7/30 */

 #endif
#else
 #if(PRO_PRINT_TYPE == THERMAL_TRANS)/* 熱転ﾛｰﾙ 椛 20.Dec'94 */ /* SAKAKI by H.Kubo 1998/08/20 */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) || (RxPrinterErrorFlag == 1)) {/* 3.Feb'95 紙なしチェック不十分 */
		/**	記録紙なし	*/
		/* MachineStatus だけでは、紙なしを検出できないことがある。
			PHASE_C で使用しているフラグも Check する。 2.Feb'95 Y.Suzuki */
		if(CHK_HeatTransferON()) {
			/** Check NO_IDF By O.K Feb,6,1995 **/
			if (!RIBON()) {
				return (SYS_B4_PAPER);
			}
			else if(CheckDonarSize()) {
				return (SYS_B4_PAPER);
			}
			else {
				return(SYS_A4_PAPER);
			}
		}
		else {
			return(SYS_B4_PAPER);
		}
	}
	/*	紙ありの場合	*/
	else {
		if(CHK_HeatTransferON()) {
			if (SYS_Paper1Size == SYS_B4_PAPER) {		/**	記録紙B4サイズ	*/
				/** Check NO_IDF BY O.K Feb,6,1995 **/
				if (!RIBON()) {
					return (SYS_B4_PAPER);
				}
				else if(CheckDonarSize()) {
					return (SYS_B4_PAPER);
				}
				else {
					return(SYS_A4_PAPER);
				}
			}
			else {
				/**	リターンA4	*/
				return(SYS_A4_PAPER);
			}
		}
		else {
			if (SYS_Paper1Size == SYS_B4_PAPER) {		/**	記録紙B4サイズ	*/
				/**	リターンB4	*/
				return(SYS_B4_PAPER);
			}
			else {
				/**	リターンA4	*/
				return(SYS_A4_PAPER);
			}
		}
	}
 #elif (PRO_PRINT_TYPE == THERMAL)	/* For HINOKI By O.Kimoto 1998/09/07 */
	if ((SYS_MachineStatus[SYS_PRINTER_STATUS1] & SYS_PRINTER_NO_PAPER) || (RxPrinterErrorFlag == 1)) {/* 3.Feb'95 紙なしチェック不十分 */
		/**	記録紙なし	*/
		/* MachineStatus だけでは、紙なしを検出できないことがある。
		** PHASE_C で使用しているフラグも Check する。 
		** 2.Feb'95 Y.Suzuki
		*/
		return(SYS_B4_PAPER);
	}
	/*	紙ありの場合	*/
	else {
		if (SYS_Paper1Size == SYS_B4_PAPER) {		/**	記録紙B4サイズ	*/
			/**	リターンB4	*/
			return(SYS_B4_PAPER);
		}
		else {
			/**	リターンA4	*/
			return(SYS_A4_PAPER);
		}
	}
 #else /* さつき */
	/*	A4Head	*/
	/*-------------------------------- ヘッドサイズの取得？　セットされていない様子なのでコメントにする 6.Jun'94 Y.Suzuki
	if (SYS_ThermalHeadSize == SYS_THERMALHEAD_A4) {		@**	A4ヘッド	*@
		@**	リターンA4	*@
		return(SYS_A4_PAPER);
	}
	----------------------------------------*/
	/*	紙なしの場合	*/
	if (SYS_MachineStatus[SYS_PRINTER_STATUS] & SYS_PRINTER_NO_PAPER) {		/**	記録紙なし	*/
		/**	リターンB4	*/
		return(SYS_B4_PAPER);
	}
	/*	紙ありの場合	*/
	else {
		if (SYS_Paper1Size == SYS_B4_PAPER) {		/**	記録紙B4サイズ	*/
			/**	リターンB4	*/
			return(SYS_B4_PAPER);
		}
		else {
			/**	リターンA4	*/
			return(SYS_A4_PAPER);
		}
	}
	/*-----------------------------------*/
 #endif
#endif
}


/*************************************************************************
	module		:[ポーリング原稿の有無]
	function	:[
		画像メモリの有無をチェック
	]
	return		:[ポーリング原稿あり:YES ポーリング原稿無し:NO]
	common		:[PollingTxType]
	condition	:[]
	comment		:[
			修正履歴	94/9/16 メモリなし機のコンパイル時の Warning 消去のため
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
				:ポーリング原稿蓄積状況を確認する際、IndexTableを２回見に行っていたので、不要部分を削除
*************************************************************************/
UBYTE CheckPollingDocuments(void)
{

#if (0)
** /* メモリ送信中の確認プリント不具合 By O.Kimoto 1998/09/02 */
** #if (PRO_MULTI_LINE == ENABLE)
** #if (0)	/*  By O.Kimoto 1997/07/07 */
** ** 	/* メモリスイッチＨ：２－１を０にしたときに、ポーリング原稿の権利を放さないと
** ** 	** いう不具合が発生したので
** ** 	** By O.Kimoto 1997/07/07
** ** 	*/
** ** 	if ((SYS_PollingDocExclusiveFlag & 0x000F) == SYS_SEND_INTERNAL_LINE) {
** ** 		if (SYS_PollingDocumentStatus) {
** ** 			PollingTxType = SYS_MEMORY_TX;
** ** 			return(YES);
** ** 		}
** ** 	}
** ** 	return(NO);
** #endif
** 
** 	if((UWORD)CMN_CheckPollingDocRights((UWORD)(SYS_SEND_INTERNAL_LINE))) {
** 		PollingTxType = SYS_MEMORY_TX;
** 		return(YES);
**  	}
**  	return(NO);
** 
** #endif
** #if (PRO_MULTI_LINE == DISABLE)
** 	if (MEM_CountTotalPage(SYS_MEM_POLLING_FILE, 0, MEM_IGNORE_BOX_NUMBER) != MEM_NO_INDEX) { /** ポーリング原稿あり	By S.Kawasaki 1996/08/10 */
** 		/**	ポーリング送信種別にメモリ送信セット スキャナポーリングもある	*/
** 		PollingTxType = SYS_MEMORY_TRANSMIT;	/* 1996/11/28  By T.Yamaguchi */
** 		/**	リターン YES	*/
** 		return(YES);
** 	}
** 
** 	/*	割り込み許可 いりません 9.Mar'94 確認 今村さん	*/
** 	/**	リターンNO	*/
** 	return(NO);
** #endif
#else
	if((UWORD)CMN_CheckPollingDocRights((UWORD)(SYS_SEND_INTERNAL_LINE))) {
		PollingTxType = SYS_MEMORY_TX;
		return(YES);
 	}
 	return(NO);
#endif

}


/*************************************************************************
	module		:[送信メモリサイズチェック]
	function	:[
		1.
	]
	return		:[送信原稿メモリ容量＜受信メモリ容量：YES／送信原稿メモリ容量＞受信メモリ容量：NO]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/05/06]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CheckTxMemorySize(WORD pos) /* モデムバッファのポインタ(NSF FIF) */
{
	WORD low_pos;
	UWORD page;
	UWORD block;
	UDWORD src_block;

	low_pos = 0;
	page = 0;
	block = 0;
	src_block = 0;

	page = MDM_ModemBuffer[NonStdFrmPos][pos];/* 受信可能ページ */
	pos++;
	low_pos = pos;
	pos++;
	block = MDM_ModemBuffer[NonStdFrmPos][pos];
	block <<= 8;
	block |= MDM_ModemBuffer[NonStdFrmPos][low_pos];
	/* 送信原稿使用ページ数 */
	if(page > MEM_CountTotalPage(SYS_DocBlock.Index.Item,SYS_DocBlock.Index.No, SYS_DocBlock.Index.BoxNumber)) {
		return(YES);
	}
	src_block = MEM_CountTotalBlock(SYS_DocBlock.Index.Item,SYS_DocBlock.Index.No, SYS_DocBlock.Index.BoxNumber);
	src_block *= MEM_BLOCK_SIZE;
	src_block /= 1024;/*独自フレーム内は、１ブロック 1024 バイト に換算されている*/
	if((UWORD)src_block < block) {
		return(YES);
	}
	return(NO);
}


/*************************************************************************
	module		:[メモリ残量チェック]
	function	:[

	]
	return		:[残量あり(１ブロック２５６(桐４ＫＢｙｔｅ）Ｂｙｔｅ以上):YES 残量なし:NO]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckRestMemory(void)
{
	if (MEM_CountTotalEmptyBlock() > 0) {/**	メモリ残量あり	*/
		/**	リターンYES	*/
		return(YES);
	}
	/**	リターンNO	*/
	return(NO);
}


/* ここから下は、ＭＭＬ専用です */
#if(PRO_MAKER == MML)
/*************************************************************************
	module		:[自機パスコード有無チェック]
	function	:[
		1.パスコード（アスキーコードでバッファにはいっている）初期設定 "0000"
	]
	return		:[登録済み:YES	未登録:NO]
	common		:[PasscodeNumber ]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckPasscodeBuf(void)
{
	UBYTE i;
	for(i = 0;	i < 4; i++) {
		if(SYB_PasscodeNumber[i] != '0') {/**	パスコード登録有	*/
			/**	リターンYES	*/
			break;
		}
	}
	if(i >= 4) {/**	パスコード"0000"	*/
		/**	リターンNO	*/
		return(NO);
	}
	return(YES);
}


/*************************************************************************
	module		:[メイルボックス有無チェック]
	function	:[
		メイルボックスのステータスをチェックする
	]
	return		:[メイルボックスあり:YES  なし:NO]
	common		:[
					SYB_Mailbox.:Status
	]
	condition	:[]
	comment		:[
			修正履歴	94/9/16 メモリなし機のコンパイル時の Warning 消去のため
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckSecureMailBox(void)
{
	UBYTE i;

	for(i = 0;i < SYS_MAILBOX_MAX;i++) {
	/* 95/12/28 Y.S 親展ボックスのステータス追加 */
	/* 親展受信中のボックスしか登録されていない時、*/
	/* モード変更されると次のページでコンパチエラーとなる 親展ﾌｨｰﾙﾄﾞなしになる */
	/*	if ((SYB_MailBox[i].Status == SYS_MAILBOX_SET) || 95/12/28 Y.S */
		if ((SYB_MailBox[i].Status == SYS_MAILBOX_SET)
		  ||(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVING)
		  ||(SYB_MailBox[i].Status == SYS_MAILBOX_RCV_TO_RECEVING)	/* 1line add 1997/10/18  By T.Yamaguchi */
		  ||(SYB_MailBox[i].Status == SYS_MAILBOX_RECEIVE)) {		/**	各メイルボックスのステータスがボックスありか受信原稿あり	*/
			/* 短縮ハンドシェーク時の親展受信も可能とするなら、SYS_MAILBOX_RECEIVING を追加すること。 16.Sep'94 */
			/**	リターンYES	*/
			return(YES);
		}
		/**	リターンNO	*/
	}
	return(NO);
}


/*************************************************************************
	module		:[検索ポーリングファイルの有無チェック]
	function	:[
		1.
	]
	return		:[ファイルあり:YES ファイルなし:NO]
	common		:[
					SYS_IndexTable.:Item
					SYS_IndexTable.:Page
	]
	condition	:[]
	comment		:[
			修正履歴	94/9/16 メモリなし機のコンパイル時の Warning 消去のため
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckDatabasePollingData(void)
{
	if (SYB_DB_PollingDocumentStatus) {
		PollingTxType = SYS_MEMORY_TRANSMIT;
		return(YES);
	}
	else {
		return(NO);
	}
}


/*************************************************************************
	module		:[中継同報のグループの有無をチェック]
	function	:[
		ワンタッチ､短縮のグループ登録の有無をチェックする
	]
	return		:[グループ登録されている:YES グループ登録されてない:NO]
	common		:[]
	condition	:[]
	comment		:[第２ワンタッチ、第２短縮の処理追加必要
			修正履歴	94/9/16 メモリなし機のコンパイル時の Warning 消去のため
	]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/09]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckRelayedBroadcastGroup(void)
{
	UBYTE i;

	for(i = 0; i < SYS_ONETOUCH_MAX; i++) {	/**	全てのワンタッチ	*/
		if ((SYB_OnetouchDial[i].Dial[0] & 0xF0) != 0xF0) {			/* Add By T.Y 96.03.09 */
			if (SYB_OnetouchDial[i].Group != 0) {		/**	グループ登録あり	*/
				/**	リターンYES	*/
				return(YES);
			}
		}
	}
	for(i = 0; i < SYS_SPEED_DIAL_MAX; i++)	/**	全ての短縮	*/{
		if ((SYB_SpeedDial[i].Dial[0] & 0xF0) != 0xF0) {		/* Add By T.Y 96.03.09 */
			if (SYB_SpeedDial[i].Group !=0) {		/**	グループ登録あり	*/
				/**	リターンYES	*/
				return(YES);
			}
		}
	}
	/**	リターンNO	*/
	return(NO);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CheckExpandFieldBIT()]
	function	:[
		拡張フィールドありなしをチェック（標準、独自共通）
	]
	return		:[
		あり---YES／なし---NO
	]
	common		:[
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/27]
	author		:[鈴木 郁二]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE CheckExpandFieldBIT(
				WORD pos1,		/*	モデムバッファのポジション	*/
				WORD pos2)		/*	モデムバッファのポジション	*/
{
	if (MDM_ModemBuffer[pos1][pos2] & EXPAND_FIELD_BIT) {		/**	拡張フィールドON	*/
		return(YES);
	}
	return(NO);
}


/*************************************************************************
	module		:[独自フレームMMR対応ビットチェック]
	function	:[
		1.受信バイト数チェック
		2.ビットチェック
	]
	return		:[YES-ビットON　　NO-ビットOFF]
	common		:[RxNonStandardFrameByteCount]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1994/01/27]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE CheckMMRinNonStandardFrame( WORD pos )	/*	モデムバッファのポインター	*/
{
	if (CheckExpandFieldBIT(NonStdFrmPos, 6)) {		/**	拡張フィールド１あり	*/
		if (MDM_ModemBuffer[NonStdFrmPos][pos] & MMR_USE_BIT) {/**	MMRビットチェック	*/
			return (YES);
		}
	}
	return (NO);
}


/*************************************************************************
	module		:[パスコードチェック]
	function	:[
		1.相手機のパスコードと自機パスコードのマッチングをチェックする
	]
	return		:[OK--YES／NG--NO]
	common		:[
				SYB_PasscodeNumber
				MDM_ModemBuffer
				NonStdFrmPos
	]
	condition	:[]
	comment		:[パスコードに"0000"が登録されている（パスコードが登録されていない）場合は、YESをリターンする]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/25]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckPassCodeMatching(WORD pos)/*	モデムバッファのポインタ	*/
{
	WORD	 i;
	UBYTE j;
	UBYTE passcode;

	i = 0;
	j = 0;
	passcode = 0;

	for(i = 0; i < 4; i++) {
		if (SYB_PasscodeNumber[i] != '0') {
			break;
		}
	}
	if (i == 4) {		/**	パスコードがセットされていない 0000 がセットされている	*/
		/**	リターンYES	*/
		return(YES);
	}
	for(i = pos, j = 0; j < 4; i++, j++/**	４回ループ	*/) {
		passcode = MDM_ModemBuffer[NonStdFrmPos][i];
		if (passcode != SYB_PasscodeNumber[j]) {		/**	相手機のパスコードと自機パスコード不一致	*/
			/**	リターンNO	*/
			return(NO);
		}
	}
}


/*************************************************************************
	module		:[短縮ハンドシェーク機能有無]
	function	:[
		1.相手機の短縮ハンドシェーク機能有無をチェックする
	]
	return		:[あり--YES／なし--NO]
	common		:[
				SYS_FaxComType
				NonStdFrmPos
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/25]
	author		:[鈴木 郁二]
*************************************************************************/
void CheckPartnerSCFR_Func(void)
{
	if (SYS_FaxComType != SYS_COMMAND_EXECUTE) {		/**	通信種別コマンド実行ではない	*/
		/**	リターンNO	*/
		PartnerSpeedHandshakeAbility = NO;
	}
	if (MDM_ModemBuffer[NonStdFrmPos][6] & SCFR_MODE_BIT) {		/**	独自フレームの短縮ハンドシェークビットON	*/
		/**	短縮ハンドシェーク機能あり	*/
		PartnerSpeedHandshakeAbility = YES;
	}
	else {
		/**	短縮ハンドシェーク機能なし	*/
		PartnerSpeedHandshakeAbility = NO;
	}
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CheckPartnerRCR_Func()]
	function	:[
		相手機の受領証発行機能の有無をチェックする
	]
	return		:[
		機能あり---YES／機能無し---NO
	]
	common		:[
	]
	condition	:[]
	comment		:[FX仕様はなし]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/27]
	author		:[鈴木 郁二]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE CheckPartnerRCR_Func(void)
{
	if (MDM_ModemBuffer[NonStdFrmPos][6] & RCR_ON_BIT) {		/**	受領証ありビットON	*/
		return(YES);
	}
	return(NO);
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[CheckPartnerPassCodeSetting()]
	function	:[
		相手機のパスコード登録の有無をチェックする
	]
	return		:[
		パスコード有り---YES／パスコード無し---NO
	]
	common		:[
				NonStdFrmPos
	]
	condition	:[]
	comment		:[FX仕様のパスコードは、異なるはず]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/11/27]
	author		:[鈴木 郁二]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UBYTE CheckPartnerPassCodeSetting(WORD pos)	/*	モデムバッファのポジション	*/
{
	if (CheckExpandFieldBIT(NonStdFrmPos, 6)) {		/**	拡張フィールド１あり	*/
		if (MDM_ModemBuffer[NonStdFrmPos][pos] & PASSCODE_SET_BIT) {		/**	パスコードセットビットON	*/
			return(YES);
		}
	}
	return(NO);
}


/*************************************************************************
	module		:[親展受信機能の有無]
	function	:[
		1.相手機の親展受信機能をチェックする
	]
	return		:[あり--YES／なし--NO]
	common		:[NonStdFrmPos]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/25]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckPartnerSecureMailFunc(WORD pos)/*	モデムバッファのポジション	*/
{
	if (CheckExpandFieldBIT(NonStdFrmPos, 6)) {		/**	拡張フィールド１あり	*/
		if (MDM_ModemBuffer[NonStdFrmPos][pos] & SECUREMAIL_BIT) {		/**	親展ビットON	*/
			/**	親展機能あり	*/
			return (YES);
		}
	}
	/**	親展機能あり	*/
	return (NO);
}


/*************************************************************************
	module		:[中継配信機能有無チェック]
	function	:[
		1.相手機の中継配信機能（ＮＳＳは、中継指示送信）の有無をチェックする
	]
	return		:[あり--YES／なし--NO]
	common		:[
				NonStdFrmPos
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckPartnerRelayBroadCastFunc(WORD pos)/*	モデムバッファのポジション	*/
{
	if (CheckExpandFieldBIT(NonStdFrmPos, 6)) {		/**	拡張フィールド１あり	↓と順番変更した By T.Yamaguchi */
		if (MDM_ModemBuffer[NonStdFrmPos][pos] & RELAYED_BROADCAST_BIT) {		/**	独自フレーム中継配信ビットON	*/
			/**	中継同報機能あり	*/
			return (YES);
		}
	}
	/**	中継同報機能なし	*/
	return (NO);
}


/*************************************************************************
	module		:[検索ポーリング機能有無チェック]
	function	:[
		1.相手機（受信機）の検索ポーリング機能の有無をチェックする
	]
	return		:[あり--YES／なし--NO]
	common		:[NonStdFrmPos]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckPartnerDB_PollingFunc(WORD pos)/*	モデムバッファのポジション	*/
{
	if (MDM_ModemBuffer[NonStdFrmPos][pos] & DATABASE_POLLING_BIT) {		/**	独自フレームの検索ポーリングビットON	*/
		if (CheckExpandFieldBIT(NonStdFrmPos, 6)) {		/**	拡張フィールド１あり	*/
			/**	データベースポーリング機能あり	*/
			return (YES);
		}
	}
	/**	データベースポーリング機能なし	*/
	return (NO);
}


/*************************************************************************
	module		:[キャラクター送信機能有無チェック]
	function	:[
		1.相手機（受信機）のキャラクタ送信機能の有無をチェックする
	]
	return		:[あり--YES／なし--NO]
	common		:[
					NonStdFrm
					MDM_ModemBuffer
	]
	condition	:[]
	comment		:[]
	machine		:[V53,H8/300]
	language	:[MS-C(Ver.6.0),H8/300(日立マイコン)]
	keyword		:[FCM]
	date		:[1993/12/27]
	author		:[鈴木 郁二]
*************************************************************************/
UBYTE CheckPartnerCharMailFunc(WORD pos)/*	モデムバッファのポジション	*/
{
	if (MDM_ModemBuffer[NonStdFrmPos][pos] & CHARACTER_MAIL_BIT) {		/**	独自フレームのキャラクタメールビットON	*/
		if (CheckExpandFieldBIT(NonStdFrmPos, 6)) {		/**	拡張フィールド１ON	*/
			/**	キャラクタ送信機能あり	*/
			return (YES);
		}
	}
	/**	キャラクタ送信機能なし	*/
	return (NO);
}


/*************************************************************************
	module		:[局名表示フィールド機能有無チェック]
	function	:[
		1.相手機の局名表示機能の有無をチェックする
	]
	return		:[ex_pos1の値をリターンする]
	common		:[
					NonStdFrm
					MDM_ModemBuffer
	]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[FCM]
	date		:[1996/12/02]
	author		:[山口 哲治]
*************************************************************************/
UBYTE CheckPartnerTTI_Func(UBYTE pos)
{
	if(MDM_ModemBuffer[NonStdFrmPos][6] & TTI_ON_BIT) {	/**	NSF 局名表示フィールドON	*/
		/**	カナID取り込み	*/
		if(NonStandardID[0] == NULL) {
			GetOwnMakerPartnerID(pos);
		}
		if(MDM_ModemBuffer[NonStdFrmPos][6] & EXPAND_FIELD_BIT) {	/**	拡張フィールド1ON	*/
			/**	NSF FIFリード用ポインターをリターン	*/
			return((UBYTE)(pos+16));
		}
	}
	else if(MDM_ModemBuffer[NonStdFrmPos][6] & EXPAND_FIELD_BIT) {	/**	拡張フィールド1ON	*/
		/**	NSF FIFリード用ポインターをリターン	*/
		return(pos);
	}
	return (NO);
}
/* CheckPasscodeBuf(void) からここまでＭＭＬ専用です */
#endif

