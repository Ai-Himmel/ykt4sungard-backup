/************************************************************************
*				BY:	 M.Kotani
*			  DATE:	 1996/10/17
*		 FILE NAME:	 cdc_main.c
*	   DESCRIPTION:	 桐コーデックのメイン制御
*					 各タスクからクリエイトされる
*  PUBLIC ROUTINES:	 void CDC_EncodePageTask(void);
*					 void CDC_DecodePageTask(struct PrintQueueData_t *prt_queue);
*					 void CDC_STxCodeConvertPageTask(void);
*					 void CDC_CTxCodeConvertPageTask(void);
*					 void CDC_MTxCodeConvertPageTask(void);
*					 void CDC_MRxCodeConvertPageTask(void);
*					 void CDC_DataTransferPageTask(void);
*					 void CDC_DecodeJournalPageTask(void);
*					 void CDC_PcPrintDataTransfer(struct PrintQueueData_t *prt_queue);
* PRIVATE ROUTINES:
*		 REFERENCE:	 SH7043 for POPLAR/ANZU_L
*************************************************************************/
/*定義ファイル*/
/*SYS*/
#include  "\src\atlanta\define\product.h"
#include  "\src\atlanta\define\std.h"
#include  "\src\atlanta\define\message.h"
#include  "\src\atlanta\define\apl_msg.h"
#include  "\src\atlanta\define\sysdoc.h"
#include  "\src\atlanta\define\sysdblk.h" /* Added by H.Kubo 1997/11/17 */
#include  "\src\atlanta\define\mntsw_a.h"
#include  "\src\atlanta\define\mntsw_b.h"
#include  "\src\atlanta\define\mntsw_c.h"
/*MON*/
#include  "\src\atlanta\sh7043\define\def_evtn.h"
/*CDC*/
#include  "\src\atlanta\define\cdc_def.h"
#include  "\src\atlanta\define\cdc_blk.h"
/*SCN*/
#include  "\src\atlanta\define\scn_def.h"
#include  "\src\atlanta\define\sysscan.h"
/*MEM*/
#include  "\src\atlanta\define\mem_def.h"
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\define\prn_def.h"
#include  "\src\atlanta\prt\ph3\define\prn_pro.h"
#elif (PRO_PRINT_TYPE == THERMAL)
 #if defined(STOCKHM2) /* Modify by SMuratec 李 2004/04/22 */
#include "\src\atlanta\prt\lv_therm\define\prt_def.h"
#include "\src\atlanta\prt\lv_therm\define\prt_pro.h"
 #else
#include  "\src\atlanta\prt\iu_therm\define\prt_def.h"
#include  "\src\atlanta\prt\iu_therm\define\prt_pro.h"
 #endif
#elif (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/12 K.Kawata */
 #if defined(STOCKHM2)
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\prt\lv_therm\define\prn_def.h"
#include "\src\atlanta\prt\lv_therm\define\prn_pro.h"
 #else
#include "\src\atlanta\define\sys_stat.h"
#include "\src\atlanta\prt\thermal\define\prn_def.h"
#include "\src\atlanta\prt\thermal\define\prn_pro.h"
 #endif
#else
#include  "\src\atlanta\prt\sp322\define\prn_def.h"
#include  "\src\atlanta\prt\sp322\define\prn_pro.h"
#endif
/*MDM*/
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include  "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif /* (PRO_MODEM == ORANGE3) */
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include  "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
#include  "\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif /* (PRO_MODEM == R288F) */
#if (PRO_MODEM == MN195006)
#include	"\src\atlanta\mdm\pana\define\mdm_def.h"	/* BEFORE_DIAL_FILTER */
#endif

/*FCM*/
#include  "\src\atlanta\define\fcm_def.h"
/*LST*/
#include  "\src\atlanta\define\lst_def.h"
/*DMA*/
#include  "\src\atlanta\define\dma_def.h"
#include  "\src\atlanta\define\dma_blk.h"
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	/* メモリ送信原稿が途中から縮む件 T.Nose 1997/10/21 */
	#include "\src\atlanta\define\mntsw_e.h"
	#include "\src\atlanta\poplar_b\define\popb_sys.h"
	void HungUpBuzzer(void);
#endif
#include  "\src\atlanta\sh7043\define\sh_SYS.h"

/*参照ファイル*/
/*SYS*/
#include  "\src\atlanta\ext_v\bkupram.h"
#include  "\src\atlanta\ext_v\sys_data.h"
/*MON*/
#include  "\src\atlanta\sh7043\ext_v\extv_mbx.h"
/*CDC*/
#include  "\src\atlanta\ext_v\cdc_data.h"
#include  "\src\atlanta\ext_v\cdc_tbl.h"
/*SCN*/
#include  "\src\atlanta\ext_v\scn_data.h"
/*MEM*/
#include  "\src\atlanta\ext_v\mem_data.h"
/*PRN*/
#if (PRO_PRINT_TYPE == LED)
#include  "\src\atlanta\prt\ph3\ext_v\prn_data.h"
#include  "\src\atlanta\prt\ph3\ext_v\prn_tbl.h"
#elif (PRO_PRINT_TYPE == THERMAL)
 #if defined(STOCKHM2)
#include "\src\atlanta\prt\lv_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
 #else
#include  "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include  "\src\atlanta\prt\iu_therm\ext_v\prt_tbl.h"
 #endif
#elif (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/2/12 K.Kawata */
 #if defined(STOCKHM2) /* Modify by SMuratec 李 2004/04/22 */
#include "\src\atlanta\prt\lv_therm\ext_v\prn_data.h"
#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
 #else
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
 #endif
#else
#include  "\src\atlanta\prt\sp322\ext_v\prn_data.h"
#include  "\src\atlanta\prt\sp322\ext_v\prn_tbl.h"
#endif
/*MDM*/
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/08/11 */
#include  "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif
#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1997/08/11 */
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) /* SMuratec H.C.H 2003.07.11 */
#include  "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include  "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif
#if (PRO_MODEM == MN195006)
#include  "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif
/*FCM*/
#include  "\src\atlanta\ext_v\fcm_data.H"
/*LST*/
#include  "\src\atlanta\ext_v\lst_data.h"
#if (PRO_CLASS1 == ENABLE)	/* 1996/07/01 by Y.Tanimoto */
#include  "\src\atlanta\ext_v\cl1_data.h"
#endif
/*IDP*/
#if (PRO_SCN_CODEC_TYPE == IDP301) || (PRO_PRN_CODEC_TYPE  == IDP301) || (PRO_COM_CODEC_TYPE == IDP301)
#include  "\src\atlanta\ext_v\idp_tbl.h"
#endif
/*ROT*/
#if (PRO_ROTATE == ENABLE)
#include  "\src\atlanta\ext_v\rot_data.h"
#endif
/*DMA*/
#include  "\src\atlanta\ext_v\dma_data.h"
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
#include  "\src\atlanta\ext_v\ini_tbl.h"
 #endif
#endif

/*プロトタイプ宣言*/
#include  "\src\atlanta\define\uni_pro.h"
#include  "\src\atlanta\define\cmn_pro.h"
#include  "\src\atlanta\define\mon_pro.h"
#include  "\src\atlanta\define\cdc_pro.h"
#include  "\src\atlanta\define\scn_pro.h"
#include  "\src\atlanta\sh7043\define\io_pro.h"
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
#include  "\src\atlanta\scd\define\scdpro.h"
#endif

#if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/17 */
#include	"\src\atlanta\sh7043\define\def_tib.h"
#include	"\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif


#if defined(POPLAR_F)	/* とりあえず */
extern UBYTE	MDM_EcmBufferOverEncodeStop;
#endif



#if (PRO_CIPHER == ENABLE) || (PRO_PRINTER_RX == ENABLE) /* PRO_PRINTER_RX added by H.Hirao 1998/12/07 */
#include  "\src\atlanta\define\sys_stat.h"
#endif

#if defined(POPLAR_H) && defined(JP0)/* V851 原稿付きﾁｪｯｸﾒｯｾｰｼﾞ ｺﾞﾐ対策 By Y.Suzuki 2002/10/01*/
#include  "\src\atlanta\define\sys_stat.h"
#endif
UBYTE	FCM_PtnrChkTTI_TxAvailable(void);


#if (PRO_CPU == SH7043) /* コーデックデバッグ T.Nose 1996/05/15 */
extern UWORD DEBUG_AddressBuffer[30][2];
extern UBYTE DEBUG_DMA_Counter;
extern UBYTE DEBUG_EncodeCounter;
extern UBYTE DEBUG_ScanLine;
#endif
UWORD	DEBUG_dec_first_cnt = 0;
UWORD	DEBUG_dma_first_cnt = 0;
UBYTE	DEBUG_DataTrans = 0;

/* スタティック変数 */
static MESSAGE_t CDC_EncodePageTaskMsg = {0};
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
static UWORD QBUF0_stat = 0;
static UWORD QBUF1_stat = 0;
UWORD DebugEncodeLine = 0;
UWORD DebugDecodeLine = 0;
#endif

#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
/*extern UBYTE	SYS_INF_MinimumSetRequest; 1998/05/23 Eguchi */
#endif

#if (0)
** /** by O.Kimoto 1998/04/27 */
** #if (PRO_PANEL == KANJI)
** /* プリンターコーデックをＭＮ８６０６４にした時のパフォーマンス測定用 By O.Kimoto 1998/04/23 */
** extern UBYTE cdc2buf_dma_count;
** extern UWORD SYS_LED1_PortStatus;
** #endif
#endif

#if (PRO_PRN_CODEC_TYPE == MN86063) /* 400dpiのｲﾒｰｼﾞを2重に書く件 by O.Kimoto 1998/04/24 */
UBYTE TrueReductiondatio = 0;
#endif
#if (PRO_FCODE_RELAY == ENABLE) /* By H.Hirao 1998/08/21 */
 #include "\src\atlanta\define\fcm_pro.h"
#endif

#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/10/09 By H.Hirao */
  #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
 #include "\src\atlanta\satsuki2\define\scn_pro.h"
 #include "\src\atlanta\satsuki2\define\scn_def.h"
  #elif defined(STOCKHM2)
 #include "\src\atlanta\stockhm2\define\scn_pro.h"
 #include "\src\atlanta\stockhm2\define\scn_def.h"
  #else
 #include "\src\atlanta\hinoki\define\scn_pro.h"
 #include "\src\atlanta\hinoki\define\scn_def.h"
  #endif
 #include "\src\atlanta\sh7043\define\def_tib.h"
 static struct DMA_Data_t STxDMA_Data;
#endif

#if (PRO_PRN_CODEC_TYPE == SOFTWARE) && (PRO_PRINT_TYPE == THERMAL) /* 1998/10/19 By H.Hirao */
#if !defined(STOCKHM2) /* Delete by SMuratec L.Z.W 2004/05/18 */
 #include "\src\atlanta\prt\iu_therm\define\prt_pro.h"
#endif
 static struct DMA_Data_t PRxDMA_Data;
#endif
#if (PRO_PRINT_TYPE == THERMAL_TRANS) /* 1999/2/12 K.Kawata */
 static struct DMA_Data_t PRxDMA_Data;
#endif
#if (PRO_SCN_CODEC_TYPE == MN86063) || (PRO_SCN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
/*************************************************************************
	module		:[1ページ符号化する]
	function	:[
		1.スキャナコーデックを獲得する
		2.コーデックパラメータを設定する
		3.大域変数にセットされたライン数符号化を繰り返す
		4.RTCをセットする
		5.スキャナコーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		スキャナタスクでコーデックは獲得されている事
		V53のDMAを起動した後,このタスクをクリエイトする事
	]
	comment		:[
		スキャナタスクからクリエイトされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1993/12/09]
	author		:[小谷正樹]
*************************************************************************/
void CDC_EncodePageTask(void)
{
	struct CodecEncodeParameterBlk_t enc_blk;
	struct CodecDMA_TransferParameterBlk_t dma_blk;
	UWORD h_resolution;
	UWORD h_reduction;
	UWORD dma_address;
	UWORD encode_address;
	UWORD encode_line;
	UWORD loop_flg;
	UBYTE is_end_of_scan; /* FBS原稿の後端検出用 */

	UWORD tmp;	/* ﾉｰﾏﾙﾌｧｲﾝ縮小率とｸﾗｽ１縮小率の掛合せ計算用 By S.Fukui */
				/* ﾉｰﾏﾙﾌｧｲﾝ縮小率とﾏﾙﾁｺﾋﾟｰ縮小率 T.Nose 1998/04/09 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)
	UWORD inf_red;
#endif

#if (PRO_CPU == SH7043) /* コーデックデバッグ T.Nose 1996/05/15 */
	for (DEBUG_DMA_Counter = 0; DEBUG_DMA_Counter < 30; DEBUG_DMA_Counter++) {
		DEBUG_AddressBuffer[DEBUG_DMA_Counter][0] = 0;
		DEBUG_AddressBuffer[DEBUG_DMA_Counter][1] = 0;
	}
	DEBUG_DMA_Counter = 0;
	DEBUG_EncodeCounter = 0;
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	SetClear((UBYTE *)&enc_blk, sizeof(struct CodecEncodeParameterBlk_t), 0x00);
#endif

	CDC_EncodePageTaskMsg.Item = FROM_SCN_SUB_TASK;
	/***********************************************************/
	/**スキャナコーデックの符号化&DMA転送のパラメータを設定する*/
	/***********************************************************/
	/**使用するコーデックを決定する*/
	enc_blk.CodecType = dma_blk.CodecType = SCANNER_CODEC;	/**符号化&DMA転送に使用するコーデックID (ex. SCANNER_CODEC)*/
	/** 入出力パラメータを決定する */
	enc_blk.FRWORD_Status = dma_blk.FRWORD_Status = 304;	/**(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
	enc_blk.INLINE_Status = dma_blk.T0_BLGR_Status = 20;	/**入力ライン数(1回に符号化するライン数) & DMA転送ライン数*/
	enc_blk.C0_MTOPA_Status = dma_blk.T0_MTOPA_Status = 0;		/**符号化イメージバッファ先頭アドレス & DMA転送バッファ先頭アドレス*/
	enc_blk.C0_MENDA_Status = dma_blk.T0_MENDA_Status = 0x6160;	/**符号化イメージバッファ最終アドレス & DMA転送バッファ最終アドレス*/
#else
	enc_blk.INLINE_Status = dma_blk.T0_BLGR_Status = 53;	/**入力ライン数(1回に符号化するライン数) & DMA転送ライン数*/
	enc_blk.C0_MTOPA_Status = dma_blk.T0_MTOPA_Status = 0;		/**符号化イメージバッファ先頭アドレス & DMA転送バッファ先頭アドレス*/
	enc_blk.C0_MENDA_Status = dma_blk.T0_MENDA_Status= 0xFE20;	/**符号化イメージバッファ最終アドレス & DMA転送バッファ最終アドレス*/
#endif
	enc_blk.I_OBXR_Status = 0;								/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
	enc_blk.C0_LCONT_Status = 0;							/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
	enc_blk.C0_MCLR_Status = 0;								/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
	/** 符号化パラメータ Ch.0の固定値を決定する*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/**DMA1ラインからスタートさせる*/	/*By M.Kotani 1997/11/26*/
	enc_blk.C0_STRA_Status = (enc_blk.FRWORD_Status * 2);	/**符号化ライン先頭アドレス(スキャナイメージバッファの符号化開始アドレス)*/
#else
	enc_blk.C0_STRA_Status = 0;								/**符号化ライン先頭アドレス(スキャナイメージバッファの符号化開始アドレス)*/
#endif
	/* ICHOUの縮小スキャンでは入力ワードが符号化ワードより少なくなる(INWORD<PWDR)ので、符号化オフセット(OBXR)は0固定とする  1997/02/14*/
	enc_blk.C0_OBXR_Status	= 0;	/**符号化オフセット*/
	/**スキャナコーデックのDMA転送のパラメータを設定する*/
	dma_blk.Channel	  = 0;									/** 使用するチャンネル (0 or 1)*/
	/** DMA転送パラメータ (CODEC MEMORY <- CUSTOM) */
	dma_blk.T0_STRA_Status	= 0;							/** DMA転送先頭アドレスポインタ*/
	/** DMA転送パラメータ (CODEC MEMORY -> CUSTOM ･･･ 使用せず) */
	dma_blk.T1_STRA_Status	= 0;							/** DMA転送先頭アドレスポインタ*/
	dma_blk.T1_WORD_Status	= 0;							/** DMA転送ワード数（１ラインのワード数）*/
	dma_blk.T1_BLGR_Status	= 0;							/** DMA転送ライン数*/
	dma_blk.T1_MTOPA_Status = 0;							/** DMA転送バッファ先頭アドレス*/
	dma_blk.T1_MENDA_Status = 0;							/** DMA転送バッファ最終アドレス*/
	/*--------------------------------------------------------*/
	/*  符号化方式を決定する                                  */
	/*	符号化方式 \src\atlanta\define\sysdoc.h				  */
	/*	#define SYS_IMAGE_DATA	   0						  */
	/*	#define SYS_MH_CODE		   1						  */
	/*	#define SYS_MR_CODE		   2						  */
	/*	#define SYS_MMR_CODE	   3						  */
	/*	#define SYS_MG3_CODE	   4	MN86063&4のみ使用可能 */
	/*	#define SYS_JBIG_CODE	   5	MN86064のみ使用可能   */
	/*  SCN_Task で決定する T.Nose 1997/01/30                 */
	/*--------------------------------------------------------*/
	enc_blk.CodeType = SCN_StoreData.Code;		/** SCN_Task()で指定した符号化方式をセット */

	/**符号化方式を元にしてＫパラメータを決定する*/
	if (enc_blk.CodeType == SYS_MR_CODE) {
		enc_blk.C0_KPR_Status = GetK_Parameter(SCN_ModeSw);
	}
	else {
		enc_blk.C0_KPR_Status = 0;
	}
	/*****************************/
	/**主走査方向のハラメータ設定*/
	/*****************************/
	enc_blk.C0_HCONV_Status = 0;			/**符号化主走査方向変換率 100 % */
	if (SCN_GetArithmeticReduction()) {		/** 細線保持モードのチェック */
		enc_blk.C0_HCONV_Status |= 0x4000;		/** 細線保持モードＯＮ */
	}
	enc_blk.INWORD_Status = dma_blk.T0_WORD_Status = SCN_GetEncodePageSize(SCN_GetEncodeStoreImageRes()) / 16;	/** 入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定 */	/** DMA転送ワード数（１ラインのワード数）*/

#if (PRO_PRN_CODEC_TYPE == MN86063) /* PRN_CODEC <- SCN_CODEC 条件変更 T.Nose 1998/04/08 */
	/* Ａ３縮小コピー間に合わない件
	** ４００ｄｐｉ、Ａ３原稿のコピー蓄積は
	** スキャナーＣＯＤＥＣでＢ４に縮小して蓄積する
	*/
	if (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10) {
		enc_blk.C0_PWDR_Status = SCN_GetEncodeOutputSize(SCN_GetEncodeStoreCodeRes()) / 16;	/** 符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定) */
	}
	else {
		enc_blk.C0_PWDR_Status = SCN_GetEncodePageSize(SCN_GetEncodeStoreCodeRes()) / 16;	/** 符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定) */
	}
#else
	enc_blk.C0_PWDR_Status = SCN_GetEncodePageSize(SCN_GetEncodeStoreCodeRes()) / 16;	/** 符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定) */
#endif
#if (PRO_CLASS1 == ENABLE)
	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する。
	** 注：enc_blk.CO_PWDR_Status を上書きする処理とします。By S.Fukui Feb.23,1998
    */
	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		/** 符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定) */
		enc_blk.C0_PWDR_Status = SCN_GetEncodeLocalScanSize(SCN_GetEncodeStoreCodeRes()) / 16;
	}
#endif /* (PRO_CLASS1 == ENABLE) */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/25 */
	/*　ｲﾝﾀｰﾈｯﾄFAX用に変換　*/
	if (SYS_DocumentStoreItem == SYS_MEM_MAIL_TX_FILE) {
		enc_blk.C0_PWDR_Status = (GetInternetFaxEncodeScanSize(GetInternetFaxEncodeScanRes()) / 16);
	}
#endif

	enc_blk.C0_LMASK_Status = enc_blk.C0_RMASK_Status = 0;	/**符号化左右側白マスク*/
	if (SCN_WhiteMaskFlag) { /** 両端白マスク有り */
		enc_blk.C0_LMASK_Status = enc_blk.C0_RMASK_Status = SCN_GetEncodeMaskSize(SCN_GetEncodeStoreCodeRes()) / 8;
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {
#if defined(USA) /* レター・リーガル対応 T.Nose 1998/03/06 */
			 if (SYS_DocumentScanSize == SYS_DOCUMENT_A4_SIZE) {
				enc_blk.C0_LMASK_Status	= 2 * 2;	/**符号化左側白マスク 2mm */
				enc_blk.C0_RMASK_Status	= 2 * 2;	/**符号化右側白マスク 2mm */
			}
#endif
		}
		/** FBS読取りなら、ADFでの白マスク量に設定された左右余白(白マスク)量を加える */
		else { /* SCN_FBS */
			switch (SCN_RegularDocumentSize) { /* レター・リーガル対応 T.Nose 1998/03/06 */
			case SYS_REGULAR_SIZE_LETTER:
			case SYS_REGULAR_SIZE_LEGAL:
				enc_blk.C0_LMASK_Status	= 2 * 2;	/**符号化左側白マスク 2mm */
				enc_blk.C0_RMASK_Status	= 2 * 2;	/**符号化右側白マスク 2mm */
				break;
			default:
				break;
			}
			enc_blk.C0_LMASK_Status += CHK_UNI_FBS_LeftMargin(SCN_GetEncodeStoreCodeRes()) / 8;
			enc_blk.C0_RMASK_Status += CHK_UNI_FBS_RightMargin(SCN_GetEncodeStoreCodeRes()) / 8;
		}
#endif
	}

#if (PRO_PRN_CODEC_TYPE == MN86063) /* PRN_CODEC <- SCN_CODEC 条件変更 T.Nose 1998/04/08 */
	/* Ａ３縮小コピー間に合わない件
	** ４００ｄｐｉ、Ａ３原稿のコピー蓄積は
	** スキャナーＣＯＤＥＣでＢ４に縮小して蓄積する
	** 出力ページ幅はＢ４で、縮小率はコピーファイルに設定されている縮小率を使用する
	*/
	if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette != SYS_AUTO_CASSETTE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		h_reduction = SCN_DocumentReduction;
		if ((SCN_ModeSw == SYS_NORMAL) || (SCN_ModeSw == SYS_FINE) || (SCN_ModeSw == SYS_SFINE)) {
			h_reduction /= 2; /* NORMAL,FINE,SFINE は水平200dpi */
		}
	}
#if (PRO_ADF_AUTO_CASSETTE == DISABLE)
	else if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette == SYS_AUTO_CASSETTE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		h_reduction = SCN_DocumentReduction;
		if ((SCN_ModeSw == SYS_NORMAL) || (SCN_ModeSw == SYS_FINE) || (SCN_ModeSw == SYS_SFINE)) {
			h_reduction /= 2; /* NORMAL,FINE,SFINE は水平200dpi */
		}
	}
#endif
	else if ((SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		h_reduction = SCN_DocumentReduction;
		if ((SCN_ModeSw == SYS_NORMAL) || (SCN_ModeSw == SYS_FINE) || (SCN_ModeSw == SYS_SFINE)) {
			h_reduction /= 2; /* NORMAL,FINE,SFINE は水平200dpi */
		}
	}
 #if (PRO_CLASS1 == ENABLE)
	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する By S.Fukui Feb.1998 */
	else if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		h_reduction = SCN_DocumentReduction;	/** ０～１００ */
		if ((SCN_ModeSw == SYS_NORMAL) || (SCN_ModeSw == SYS_FINE) || (SCN_ModeSw == SYS_SFINE)) {
			h_reduction /= 2; /* NORMAL,FINE,SFINE は水平200dpi */
		}
	}
 #endif /* (PRO_CLASS1 == ENABLE) */
	else { /* 送信原稿 */
		h_reduction = (UWORD)(((UDWORD)enc_blk.C0_PWDR_Status * (UDWORD)100) / (UDWORD)enc_blk.INWORD_Status);	/** ０～１００ */
	}
#else /* MN86063 else */
	h_reduction = (UWORD)(((UDWORD)enc_blk.C0_PWDR_Status * (UDWORD)100) / (UDWORD)enc_blk.INWORD_Status);	/** ０～１００ */
 #if (0)	/* 処理不要 By S.Fukui Apr.16,1998 */
// #if (PRO_CLASS1 == ENABLE)
//	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する By S.Fukui Feb.1998 */
//	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
//		h_reduction = SCN_DocumentReduction;	/** ０～１００ */
//		if ((SCN_ModeSw == SYS_NORMAL) || (SCN_ModeSw == SYS_FINE) || (SCN_ModeSw == SYS_SFINE)) {
//			h_reduction /= 2; /* NORMAL,FINE,SFINE は水平200dpi */
//		}
/	}
// #endif /* (PRO_CLASS1 == ENABLE) */
 #endif
#endif
	if (h_reduction == 100) {
		enc_blk.C0_HCONV_Status = 0;	/**符号化主走査方向変換率 100 % */
	}
	else {
		enc_blk.C0_HCONV_Status |= (UDWORD)h_reduction * (UDWORD)0x400 / (UDWORD)100;	/**符号化主走査方向変換率 0-99 % */
	}

	/*****************************/
	/**副走査方向のハラメータ設定*/
	/*****************************/
	/*--------------------------------------------------Jun.21,1994-----*/
	/* 読み取り原稿長の制限をする為の設定を行う。						*/
	/* 制限時　－＞１ｍ													*/
	/* 無制限時－＞３．６ｍ												*/
	/*------------------------------------------------------------------*/
	SCN_ScanMaxLine = CDC_GetDocumentMaxLine( SCN_ModeSw );			/* 最大読み取りライン数 */
#if (PRO_FBS == ENABLE) /* T.Nose 1997/02/03 */
	/** 原稿長制限のライン数と読み取りライン数をセットする */
	CDC_DocumentScanLine = CDC_GetDocumentScanLine( SCN_ModeSw );	/* FBS定型原稿の読み取りライン数 */
#endif

#if (PRO_PRN_CODEC_TYPE == MN86063) /* PRN_CODEC <- SCN_CODEC 条件変更 T.Nose 1998/04/08 */
 #if (PRO_SCN_CODEC_TYPE == MN86063) /* T.Nose 1998/04/08 */
 /******************************************/
 /*** プリンタコーデック：ＭＮ８６０６３ ***/
 /*** スキャナコーデック：ＭＮ８６０６３ ***/
 /*** → ＰＯＰＬＡＲ＿Ｂ                ***/
 /******************************************/
	/* Ａ３縮小コピー間に合わない件
	** ４００ｄｐｉ、Ａ３原稿のコピー蓄積は
	** スキャナーＣＯＤＥＣで縮小して蓄積する
	** 記録紙自動の場合は縮小しない
	*/
	if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette != SYS_AUTO_CASSETTE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		enc_blk.C0_VCONV_Status = (UDWORD)0x10000 - ((UDWORD)SCN_DocumentReduction * (UDWORD)0x10000 / (UDWORD)100);	/** 符号化副走査方向変換率 */
	}
	else if ((SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		enc_blk.C0_VCONV_Status = (UDWORD)0x10000 - ((UDWORD)SCN_DocumentReduction * (UDWORD)0x10000 / (UDWORD)100);	/** 符号化副走査方向変換率 */
	}
  #if (PRO_CLASS1 == ENABLE)
	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する By S.Fukui Feb.23,1998 */
	else if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		enc_blk.C0_VCONV_Status = (UDWORD)0x10000 - ((UDWORD)SCN_DocumentReduction * (UDWORD)0x10000 / (UDWORD)100);	/** 符号化副走査方向変換率 */
	}
  #endif /* (PRO_CLASS1 == ENABLE) */
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	else if (SYS_DocumentStoreItem == SYS_MEM_MAIL_TX_FILE) {
		enc_blk.C0_VCONV_Status = (UDWORD)0x10000 - ((UDWORD)SCN_DocumentReduction * (UDWORD)0x10000 / (UDWORD)100);	/** 符号化副走査方向変換率 */
	}
  #endif
	else {
		enc_blk.C0_VCONV_Status = 0;
	}

 #else /* SCN_CODEC == MN86063 else */
 /******************************************/
 /*** プリンタコーデック：ＭＮ８６０６３ ***/
 /*** スキャナコーデック：ＭＮ８６０６４ ***/
 /*** → ＰＯＰＬＡＲ＿Ｈ                ***/
 /******************************************/

	if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
		if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
			enc_blk.C0_VCONV_Status = 0x2000;	/** 符号化副走査方向変換率 50%縮小 */
			enc_blk.Vmn_Status = 0x8000;		/** 副走査:ラインOR処理 By Y.Suzuki 1997/09/10 */
		}
		else { /* ファイン→ノーマル変換しない */
			if (CMN_NormalScan4Sec()) { /* ノーマル４秒読取り */
				enc_blk.C0_VCONV_Status = 0x2000;	/** 符号化副走査方向変換率 50%縮小 */
				enc_blk.Vmn_Status = 0x0000;		/** 副走査:ライン間引き処理 By Y.Suzuki 1997/09/10 */
			}
			else { /* ノーマル２秒読取り */
				enc_blk.C0_VCONV_Status = 0;		/** 符号化副走査方向変換率 等倍 */
				enc_blk.Vmn_Status = 0x0000;		/** 副走査:ライン間引き処理 By Y.Suzuki 1997/09/10 */
			}
		}
	}
	else { /* ノーマル以外 */
		enc_blk.C0_VCONV_Status = 0;		/** 符号化副走査方向変換率 等倍 */
		enc_blk.Vmn_Status = 0x0000;		/** 副走査:ライン間引き処理 By Y.Suzuki 1997/09/10 */
	}

 	/* Ａ３縮小コピー間に合わない件
	** ４００ｄｐｉ、Ａ３原稿のコピー蓄積は
	** スキャナーＣＯＤＥＣでＢ４に縮小して蓄積する
	** 記録紙自動の場合はＡ３→Ｂ４縮小
	*/
	if ((SYS_DocumentStoreItem == SYS_MEM_MULTI_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		tmp = (((UDWORD)0x4000 - (UDWORD)enc_blk.C0_VCONV_Status) * (UDWORD)100) / (UDWORD)0x4000;	/* Fine->Nomal変換の縮小率x100を求めます */
		if (SYB_MultiCopyFile[SYB_MultiCopyWritePoint].Cassette == SYS_AUTO_CASSETTE) {
  #if (PRO_CCD == DPI400)
			if (SCN_GetEncodeStoreCodeRes() == (UDWORD)200) {
				h_reduction = h_reduction * 2;
			}
  #endif
  #if (PRO_CCD == DPI300)
			if (SCN_GetEncodeStoreCodeRes() == (UDWORD)200) {
				h_reduction = h_reduction * 3 / 2;
			}
  #endif
	        tmp = ((UWORD)h_reduction * (UWORD)tmp) / (UWORD)100; /* A3→B4縮小との合成縮小率x100を求めます */
  		}
  		else {
	        tmp = ((UWORD)SCN_DocumentReduction * (UWORD)tmp) / (UWORD)100; /* A3→B4縮小との合成縮小率x100を求めます */
  		}
		/* ラインOR処理では変換率５０％未満の設定が出来ない為、ファイン→ノーマル変換を禁止する。*/
		if (tmp < 50) {
			enc_blk.Vmn_Status = 0x0000;
		}
		enc_blk.C0_VCONV_Status = (UDWORD)0x4000 - ((UDWORD)tmp * (UDWORD)0x4000 / (UDWORD)100);	/* 符号化副走査方向変換率を求めます */
	}
	else if ((SYS_DocumentStoreItem == SYS_MEM_MANUAL_COPY_FILE)
	 && (SYS_DocumentScanSize == SYS_DOCUMENT_A3_SIZE)
	 && (SYB_MaintenanceSwitch[MNT_SW_C9] & 0x10)) {
		tmp = (((UDWORD)0x4000 - (UDWORD)enc_blk.C0_VCONV_Status) * (UDWORD)100) / (UDWORD)0x4000;	/* Fine->Nomal変換の縮小率x100を求めます */
        tmp = ((UWORD)SCN_DocumentReduction * (UWORD)tmp) / (UWORD)100; /* A3→B4縮小との合成縮小率x100を求めます */
		/* ラインOR処理では変換率５０％未満の設定が出来ない為、ファイン→ノーマル変換を禁止する。*/
		if (tmp < 50) {
			enc_blk.Vmn_Status = 0x0000;
		}
		enc_blk.C0_VCONV_Status = (UDWORD)0x4000 - ((UDWORD)tmp * (UDWORD)0x4000 / (UDWORD)100);	/* 符号化副走査方向変換率を求めます */
	}
  #if (PRO_CLASS1 == ENABLE)
	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する対策 By S.Fukui Feb.23,1998 */
	else if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		tmp = (((UDWORD)0x4000 - (UDWORD)enc_blk.C0_VCONV_Status) * (UDWORD)100) / (UDWORD)0x4000;	/* Fine->Nomal変換の縮小率x100を求めます */
        tmp = ((UWORD)SCN_DocumentReduction * (UWORD)tmp) / (UWORD)100;								/* class1との合成縮小率x100を求めます */
		/* ラインOR処理では変換率５０％未満の設定が出来ない為、ファイン→ノーマル変換を禁止する。*/
		if (tmp < 50) {
			enc_blk.Vmn_Status = 0x0000;
		}
		enc_blk.C0_VCONV_Status = (UDWORD)0x4000 - ((UDWORD)tmp * (UDWORD)0x4000 / (UDWORD)100);	/* 符号化副走査方向変換率を求めます */
	}
  #endif /* (PRO_CLASS1 == ENABLE) */
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	else if (SYS_DocumentStoreItem == SYS_MEM_MAIL_TX_FILE) {
		/* InternetFaxの場合、SCN_DocumentReductionは100%かX→A4の縮小率しか入らない　*/
		inf_red = (((UDWORD)0x4000 - (UDWORD)enc_blk.C0_VCONV_Status) * (UDWORD)100) / (UDWORD)0x4000;
		inf_red = ((UWORD)SCN_DocumentReduction * (UWORD)inf_red) / (UWORD)100;
		if (inf_red < 50) {
			enc_blk.Vmn_Status = 0x0000;
		}
		enc_blk.C0_VCONV_Status = (UDWORD)0x4000 - ((UDWORD)inf_red * (UDWORD)0x4000 / (UDWORD)100);
	}
  #endif
 #endif /* SCN_CODEC end */

#else /****** PRN_CODEC == MN86063 else * T.Nose 1998/04/09 *******/

 #if (PRO_SCN_CODEC_TYPE == MN86063) /* T.Nose 1998/04/08 */
 /******************************************/
 /*** プリンタコーデック：ＭＮ８６０６４ ***/
 /*** スキャナコーデック：ＭＮ８６０６３ ***/
 /*** → 該当機種なし                    ***/
 /******************************************/

  #if (PRO_CLASS1 == ENABLE)
	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する By S.Fukui Feb.23,1998 */
	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		enc_blk.C0_VCONV_Status = (UDWORD)0x10000 - ((UDWORD)SCN_DocumentReduction * (UDWORD)0x10000 / (UDWORD)100);	/** 符号化副走査方向変換率 */
	}
  #endif /* (PRO_CLASS1 == ENABLE) */
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	else if (SYS_DocumentStoreItem == SYS_MEM_MAIL_TX_FILE) {
		enc_blk.C0_VCONV_Status = (UDWORD)0x10000 - ((UDWORD)SCN_DocumentReduction * (UDWORD)0x10000 / (UDWORD)100);	/** 符号化副走査方向変換率 */
	}
  #endif
	else {
		enc_blk.C0_VCONV_Status = 0;
	}

 #else /* SCN_CODEC == MN86063 else */
 /******************************************/
 /*** プリンタコーデック：ＭＮ８６０６４ ***/
 /*** スキャナコーデック：ＭＮ８６０６４ ***/
 /*** → ＰＯＰＬＡＲ＿Ｌ                ***/
 /*** → ＡＮＺＵ＿Ｌ                    ***/
 /******************************************/
	if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
		if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
			enc_blk.C0_VCONV_Status = 0x2000;	/** 符号化副走査方向変換率 50%縮小 */
			enc_blk.Vmn_Status = 0x8000;		/** 副走査:ラインOR処理 By Y.Suzuki 1997/09/10 */
		}
		else { /* ファイン→ノーマル変換しない */
			if (CMN_NormalScan4Sec()) { /* ノーマル４秒読取り */
				enc_blk.C0_VCONV_Status = 0x2000;	/** 符号化副走査方向変換率 50%縮小 */
				enc_blk.Vmn_Status = 0x0000;		/** 副走査:ライン間引き処理 By Y.Suzuki 1997/09/10 */
			}
			else { /* ノーマル２秒読取り */
				enc_blk.C0_VCONV_Status = 0;		/** 符号化副走査方向変換率 等倍 */
				enc_blk.Vmn_Status = 0x0000;		/** 副走査:ライン間引き処理 By Y.Suzuki 1997/09/10 */
			}
		}
	}
	else { /* ノーマル以外 */
		enc_blk.C0_VCONV_Status = 0;		/** 符号化副走査方向変換率 等倍 */
		enc_blk.Vmn_Status = 0x0000;		/** 副走査:ライン間引き処理 By Y.Suzuki 1997/09/10 */
	}
  #if (PRO_CLASS1 == ENABLE)
	/* PCの記録幅能力がFAXの記録幅(読取り原稿幅）より下回っている時縮小して蓄積する対策 By S.Fukui Feb.23,1998 */
	if (SYS_DocumentStoreItem == SYS_MEM_CLASS1_TX_FILE) {
		tmp = (((UDWORD)0x4000 - (UDWORD)enc_blk.C0_VCONV_Status) * (UDWORD)100) / (UDWORD)0x4000;	/* Fine->Nomal変換の縮小率x100を求めます */
        tmp = ((UWORD)SCN_DocumentReduction * (UWORD)tmp) / (UWORD)100;								/* class1との合成縮小率x100を求めます */
		/* ラインOR処理では変換率５０％未満の設定が出来ない為、ファイン→ノーマル変換を禁止する。*/
		if (tmp < 50) {
			enc_blk.Vmn_Status = 0x0000;
		}
		enc_blk.C0_VCONV_Status = (UDWORD)0x4000 - ((UDWORD)tmp * (UDWORD)0x4000 / (UDWORD)100);	/* 符号化副走査方向変換率を求めます */
	}
  #endif /* (PRO_CLASS1 == ENABLE) */
  #if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
	if (SYS_DocumentStoreItem == SYS_MEM_MAIL_TX_FILE) {
		/* InternetFaxの場合、SCN_DocumentReductionは100%かX→A4の縮小率しか入らない　*/
		inf_red = (((UDWORD)0x4000 - (UDWORD)enc_blk.C0_VCONV_Status) * (UDWORD)100) / (UDWORD)0x4000;
		inf_red = ((UWORD)SCN_DocumentReduction * (UWORD)inf_red) / (UWORD)100;
		if (inf_red < 50) {
			enc_blk.Vmn_Status = 0x0000;
		}
		enc_blk.C0_VCONV_Status = (UDWORD)0x4000 - ((UDWORD)inf_red * (UDWORD)0x4000 / (UDWORD)100);
	}
  #endif

 #endif /* SCN_CODEC end */

#endif /************ PRN_CODEC end * T.Nose 1998/04/09 **********/


	/*************************************************/
	/**上記のパラメータでコーデックをセットアップする*/
	/*************************************************/
	CodecEncodeSetup(&enc_blk);			/*上記のパラメータでエンコードするようにセットアップされる*/
	CDC0_DMA0_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
	CodecDMA_TransferSetup(&dma_blk);	/*上記のパラメータにＤＭＡ転送するようにセットアップされる*/
	/**符号化を開始する*/
	CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**コーデックの符号化は終了したため、イメージメモリを開放する*/
	loop_flg = TRUE;
	is_end_of_scan = FALSE;
	while (loop_flg) { /**1ページ符号化するまでループする*/
		CMN_DisableInterrupt();	/**割り込み禁止*/
		if (SCN_DocumentStatus != SCN_DOC_END_OF_SCAN) { /**ページ終了フレーム以外の場合*/
			if (CDC0_DMA0_EndFlag) {
				CDC0_DMA0_EndFlag--;
			}
			else {
				wai_evt(EVT_CDC0_DMA0_END); /**IDPからイメージメモリ53LinesのDMA終了を待つ*/
			}
			CDC0_DMA0_EndFlag = 0;
			CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_LOWER_BLOCK_ACCESS;
			if (SCN_SpeedCheckPoint != 0) { /* Nov.13,1994 */
				SCN_SpeedCheckPoint = 0;
			}
		}
		CMN_EnableInterrupt();	/**割り込み許可*/
		if (SCN_ScanMaxLine) {
			if (SCN_ScanMaxLine <= SCN_ReadMotorPulseCounter()) { /* TBD */
#if (PRO_CIPHER == ENABLE)/*By Y.Suzuki 1998/06/11*/
				/*スクランブルエラーステータスセットBy Y.Suzuki 1998/06/11 */
				if (SYS_DocumentStoreItem == SYS_MEM_CIPHER_FILE) {/* By Y.Suzuki 2002/01/16 */
					/*------------------------------------------------------------------------
						スクランブル以外の蓄積原稿でもスクランブル用のエラー表示になっていた
						蓄積itemを確認してエラーステータスを立てるようにする。
					--------------------------------------------------------------------------*/
					SYS_MachineStatus[SYS_CIPHER_STATUS] |= SYS_SCRAMBLE_LENGTH_ERROR;
				}
#endif
				CDC_EncodePageTaskMsg.Message = CDC_MAX_LINE_OVER;	/** Over 1 meter/3.6meter */
				snd_msg( mbxno.SCN_Task, &CDC_EncodePageTaskMsg );	/* TBD */
				wai_tsk(0xFFFF);
			}
		}
		if ((SCN_DocumentStatus == SCN_DOC_END_OF_SCAN) || (is_end_of_scan)) {	/**ページ終了フレームの場合*/
			loop_flg = FALSE;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
#else		/**読み取り専用ハードコーデックあり*/
			dma_address    = ReadCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR);
			encode_address = ReadCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR);
			if (dma_address >= encode_address) {
				encode_address = dma_address - encode_address;
			}
			else {
				encode_address = (dma_address - CodecParameterRegister[SCANNER_CODEC].C0_MTOPA_Status)
							   + (CodecParameterRegister[SCANNER_CODEC].C0_MENDA_Status - encode_address);
			}
			encode_line = encode_address / (dma_blk.FRWORD_Status * 2);
#endif

#if (PRO_FBS == ENABLE)
			/** FBS読取りで、残りラインが53ライン以下の場合は、残りを今回の符号化ライン数とする
			**	(残りが0ラインなら、すぐ下の「ちょうど53ラインの…」の処理に入る)
			*/
			if (CDC_DocumentScanLine <= enc_blk.INLINE_Status) {
				encode_line = CDC_DocumentScanLine;
			}
			/*	ここでEND_OF_SCANにすると残りのエンコード後にRestartMotorできないので
			**	ミラーキャリッジエラー(8)になるため、この処理をループの外でする
			**		1997/03/31 s.takeuchi
			@* スキャナの読取りを止めるためにSCN_DOC_END_OF_SCANにする
			** SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;
			*/
#endif

			if (encode_line == 0) {	/**ちょうど５３ラインの倍数で読み取りラインが終了したとき*/
				CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**コーデックは符号化しないため、イメージメモリを開放する*/
				break;
			}
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, encode_line);
		}
		else {	/**通常（符号化継続） ※次の53LinesのDMAを設定する*/
		}
#if (PRO_CPU == SH7043) /* コーデックデバッグ 1996/05/15 T.Nose */
		if (DEBUG_DMA_Counter < 30) {
			DEBUG_AddressBuffer[DEBUG_DMA_Counter][1] = ReadCodecParameterRegister(SCANNER_CODEC,C0_STRA_ADR);
			DEBUG_DMA_Counter++;
		}
#endif
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
		/* CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status はコーデック割り込みで更新されるが */
		/* ページの終わりのときはコーデック割り込みは来ないので直接レジスタから読み出す。          */
		/* T.Nose 2000/1/27   新Ｌ４００だけでなくＬ系全部対応 2000/1/28 Y.Murata */
		/*dma_address		= CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status;*/
		dma_address		= ReadCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR);
		encode_address	= ReadCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR);
		if (dma_address >= encode_address) {
			encode_address = dma_address - encode_address;
		}
		else {
			encode_address = (dma_address - CodecParameterRegister[SCANNER_CODEC].C0_MTOPA_Status)
						   + (CodecParameterRegister[SCANNER_CODEC].C0_MENDA_Status - encode_address);
		}
		encode_line = encode_address / (dma_blk.FRWORD_Status * 2);
		CodecParameterRegister[SCANNER_CODEC].INLINE_Status	= encode_line;	/**入力ライン数*/
		if (encode_line) {	/**せってい範囲が1以上のため0のときは何もしない。上の大域変数を見て0の時はエンコードをスタートしないようにする必要がある*/
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, encode_line);
		}
#endif
		if (CodecParameterRegister[SCANNER_CODEC].INLINE_Status) {	/**エンコードするラインがある場合（通常は53ライン）add By M.Kotani 1997/11/13*/
			StartEncode(SCANNER_CODEC, enc_blk.CodeType);	/**PBR:INLINEに設定したライン数を連続して符号化する。符号化終了までリターンしない。*/
		}
		else {
			CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**コーデックは符号化しないため、イメージメモリを開放する*/
		}
#if (PRO_FBS == ENABLE) /* T.Nose 1997/02/03 */
		/**	FBS読取りの場合は、残りの符号化ライン数を減算して
		**	次の53ラインの符号化で読取り原稿長を超える時は、残りのライン数を
		**	次回の符号化ライン数としてセットして、1ページの読取りは終了とする
		*/	/* ICHOU用  1996/07/02 s.takeuchi */
		if (SYS_ScannerExecMode == SCN_FBS) {
			CDC_DocumentScanLine -= enc_blk.INLINE_Status;		/* 残りの符号化ライン */
			if (CDC_DocumentScanLine <= enc_blk.INLINE_Status) {
				/* SCN_DocumentStatus = SCN_DOC_END_OF_SCAN; */
				is_end_of_scan = TRUE;
			}
		}
#endif

		if (CDC0_DMA0_EndFlag) {
			CDC0_DMA0_EndFlag = 1;	/*ここに来るとモーターが止めきれていない(バッファを壊している)*/
		}
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
		if (SCN_ADF_MotorStopRequest == ADF_MOTOR_NO_STOP) {	/* By M.Kotani 1997/11/26 */
			SCN_RestartMotor();	/** May.24,1994 Restart Motor if motor has beem stopped */
		}
#else
		SCN_RestartMotor();	/** May.24,1994 Restart Motor if motor has beem stopped */
#endif
	}

#if (PRO_FBS == ENABLE)
	/* ミラーキャリッジエラー(8)対策  1997/03/31 s.takeuchi */
	/** FBS読み取りでスキャナの読取りを止めるためにSCN_DOC_END_OF_SCANにする */
	if (SYS_ScannerExecMode == SCN_FBS) {
		SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;

		/* メモリー送信原稿後端縮む件 T.Nose 1997/11/03 */
		DEBUG_DocumentScanning = 0;
	}
#endif

	CodecParameterRegister[SCANNER_CODEC].C0_LCONT_Status = ReadCodecParameterRegister(SCANNER_CODEC, C0_LCONT_ADR);
	SCN_TotalEncodeLine = EncodeLine(SCANNER_CODEC); /** Aug.20,1994 符号化ライン数を保存 */

	SetRTC(SCANNER_CODEC, enc_blk.CodeType);	/**ページの終わりにRTCをセットする*/
	CDC_EncodePageTaskMsg.Message = CDC_ENCODE_OK;	/**1 Page 符号化終了を報告する*/
	snd_msg( mbxno.SCN_Task, &CDC_EncodePageTaskMsg );
	wai_tsk(0xFFFF);
}
#endif	/* 1998/06/10 H.Yoshikawa */

/*************************************************************************
	module		:[1論理ページ復号化する]
	function	:[
		1.プリンタコーデックを獲得する
		2.コーデックパラメータを設定する
		3.RTCを検出するまで復号化する
		4.プリンタを起動する
		5.プリンタコーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		このタスクをクリエイトする前に,V53のDMAを起動する事
	]
	comment		:[
		プリントタスクからクリエイトされ
		, 長尺原稿時はプリンタはくり返し起動される
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1993/12/10]
	author		:[小谷正樹 & NOBUKO]
*************************************************************************/
void CDC_DecodePageTask(struct PrintQueueData_t *prt_queue)
{
#if (PRO_PRN_CODEC_TYPE == MN86063) || (PRO_PRN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
	struct CodecDecodeParameterBlk_t dec_blk;
	struct CodecDMA_TransferParameterBlk_t dma_blk;
	UBYTE printer; /**プリンタ起動用*/
	UBYTE print_mode;
	UWORD loop_flg;
	UWORD dec_start_pointer;
	UWORD dma_start_pointer;
	UWORD prn_codec_limit; /* 1997/07/25 Y.Murata*/
#if (PRO_PRINT_TYPE == LED)
	UBYTE cassette_pos;
	UBYTE adjust;
	UBYTE prn_form;
#endif

	DEBUG_CDC_DecodeError = 0;
	dma_start_pointer = 0;
	prn_codec_limit = 0;

#if (PRO_PRINT_TYPE == LED)
 #if (PRO_PRN_CODEC_TYPE == MN86063) /* 400dpiのｲﾒｰｼﾞを2重に書く件 T.Nose 1998/0421 */
	TrueReductiondatio = prt_queue->Index[PRN_CompPageNo].Reduction;
 #endif
#endif

#if (0)
** #if (PRO_PANEL == KANJI)
** 	/* プリンターコーデックをＭＮ８６０６４にした時のパフォーマンス測定用 By O.Kimoto 1998/04/23 */
** 	cdc2buf_dma_count = 0;
** 	SYS_LED1_PortStatus &= 0x003f;
** 	outpw(LED1_PORT, (UWORD)SYS_LED1_PortStatus);
** #endif
#endif

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/26 */
	/* イメージデータのメモリプリントの場合（ＰＣプリントのみここに入る）*/
	if (MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Code == SYS_IMAGE_DATA) {
		CDC_PcPrintDataTransfer(prt_queue);
		wai_tsk(0xFFFF);
	}
#endif

	switch (MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Mode) {
	case SYS_NORMAL:
		print_mode = PRN_NORMAL;
		break;
	case SYS_FINE:
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY32:
	case SYS_GRAY32_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		print_mode = PRN_FINE;
		break;
	case SYS_SFINE:
		print_mode = PRN_SFINE;
		break;
	case SYS_HFINE:
		print_mode = PRN_HFINE;
		break;
#if (PRO_PRINT_TYPE == LASER)
	case SYS_EFINE:
		print_mode = PRN_EFINE;
		break;
	case SYS_E_HFINE:
		print_mode = PRN_E_HFINE;
		break;
	case SYS_UFINE:
		print_mode = PRN_UFINE;
		break;
	case SYS_300_NORMAL:
		print_mode = PRN_300NORMAL;
		break;
	case SYS_300_FINE:
		print_mode = PRN_300FINE;
		break;
#endif
#if (PRO_ROTATE == ENABLE)
	case SYS_NORMAL_ROT:	/* 30  普通回転	   	100dpi: 4 dot/m 200dpi: 7.7本/l */
		print_mode = PRN_NORMAL;
		break;
	case SYS_SFINE_ROT:		/*31  超高画質回転	400dpi:16 dot/m 200dpi: 7.7本/l */
		print_mode = PRN_HFINE;
		break;
#endif
	default:
		print_mode = PRN_NORMAL;
		break;
	}

#if (PRO_PRINT_TYPE == LASER)	/* 1997/07/25 Y.Murata */

	/* 1997/07/19 Y.Murata  -> 1997/11/29 やっぱりここにする
	** デコードページタスクを起動する前に、サイドマージンとオフセット
	** 再度設定し直します（従来のアンズでﾃﾞｺｰﾄﾞﾍﾟｰｼﾞﾀｽｸの中でやっていたことをここでします。）
	*/
	PRN_CodecLeftMargine /= GA_H_Reduction; /* By S.Kawasaki 1996/04/05 */
	PRN_PrintDataOffset /=GA_H_Reduction; /* S.Kawasaki 1996/05/10 */

	prn_codec_limit = 5184; /* 1997/07/25 */
	if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) { /** プリントがＰＣプリントの場合 */
		if ((print_mode == PRN_EFINE) || (print_mode == PRN_UFINE)) {
			if (GA_H_Reduction == 1) {
				prn_codec_limit = 4848;
			}
			else {
				prn_codec_limit = 4992;
			}
		}
	}
	else {	/** プリントがＰＣプリント以外の場合 */
#if (0)
** 		/*
** 		** ＳＦＩＮＥでの１００％以外印字時に副走査が倍になる為の修正
** 		** 1996/06/06
** 		** ３００×３００／６００×６００モード追加
** 		** 1996/06/14
** 		*/
** 		if ((print_mode == PRN_E_HFINE)||(print_mode == PRN_HFINE)||(print_mode == PRN_SFINE)||(print_mode == PRN_EFINE)||(print_mode == PRN_UFINE)) {
** 			if (GA_H_Reduction == 1) {
** 				prn_codec_limit = 4864;
** 			}
** 			else {
** 				prn_codec_limit = 4992;
** 			}
** 		}
#else
		prn_codec_limit = 4992; /* 1997/12/01 By M.Kotani Test*/
#endif
	}
	dec_start_pointer = (UWORD)(PRN_CodecLeftMargine / 8);				/** 復号化ライン先頭アドレス(プリンタイメージバッファの符号化開始アドレス)*/
#endif

#if (PRO_PRINT_TYPE == LED)
	dec_start_pointer = (UWORD)PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_D_STRA];	/** 復号化ライン先頭アドレス(プリンタイメージバッファの符号化開始アドレス)*/
 #if (PRO_SCN_CODEC_TYPE == MN86063)
  #if defined(USA)	/* レジャー → リーガル縮小コピー補正（最大７７％） By S.Fukui Feb.25,1998 */
	if ((SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE)
		 || (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE)) {
		if ((MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Size == SYS_DOCUMENT_A3_SIZE)
			&& (prt_queue->PrintedForm == SYS_LG_PAPER)) {
				/* ((304 - 279)/2) * 0.77 = 約10 → スタートポインタを調整 */
				dec_start_pointer -= (10 * 2);
		}
	}
  #endif
 #endif

	/*--------------------------------------------------------------------
	** カセットの中心ずれ対策
	** １ｍｍ×３＝±３．０ｍｍ
	*/
	cassette_pos = PRN_GetCassetteAdjustPosition(prt_queue->Cassette);
	adjust = (SYB_MachineParameter[cassette_pos] & 0x7f);
	if (adjust > 20) {	/* <- 3 By M.Tachibana 1998/02/19 */
		adjust = 20;
	}
	adjust *= 2;
	if (SYB_MachineParameter[cassette_pos] & 0x80) {	/** マイナス */
		dma_start_pointer = (UWORD)adjust;
	}
	else {
 #if (PRO_PRINTER == DPI200)	/* add M.Tachibana 1998/02/19 */
		adjust *=  2;
 #endif
		dec_start_pointer += (UWORD)adjust;
	}

	if (prt_queue->Index[PRN_CompPageNo].Reduction < 100) {		/* 先頭に白付け 99 ～ 50 % */

		prn_form = prt_queue->PrintedForm;
		if ((SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE)
		 || (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE)) {	/* 1997/12/19 */
			if ((MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Size == SYS_DOCUMENT_B4_SIZE)
			 && (PRN_HorizontalDataTable[SYS_B4_PAPER][PRN_ALL_DOT] !=
					PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_ALL_DOT])) {
				/* Ｂ４からＡ４幅より小さい記録紙に対して */
				switch (prt_queue->PrintedForm) {
				case SYS_LT_PAPER:
				case SYS_LG_PAPER:
				case SYS_HLTR_PAPER:
					prn_form = SYS_LT_PAPER;	/* 追加 By M.Tachibana 1998/03/06 */
					break;
				default:
					prn_form = SYS_A4_PAPER;
					break;
				}
			}
		}

		dec_start_pointer += (PRN_HorizontalDataTable[prn_form][PRN_ALL_MASK] * 2 - 2);
 #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
		dec_start_pointer = ((dec_start_pointer * 100) / PRN_ReducData.GA_H_Reduction);
 #else
		dec_start_pointer /= PRN_ReducData.GA_H_Reduction;	/* 回転(SYS_NORMAL_ROT)のため Add by M.Tachibana 97/10/23*/
 #endif
 #if (PRO_PRINTER == DPI200)	/* For Test */
		dec_start_pointer /= 2;
 #endif
	}
	else if (prt_queue->Index[PRN_CompPageNo].Reduction > 100) {
		dec_start_pointer += ((PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_ALL_MASK]
							- PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_PAPER_MASK]) * 2);
#if (0)	/* By M.Tachibana 1998/05/15 */
//		if (print_mode != SYS_HFINE) {
//			dec_start_pointer /= PRN_ReducData.GA_H_Reduction;
//		}
//		else {
//			dec_start_pointer /= 2;		/* G/Aで２倍しているため */
//		}
#endif
 #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
		dec_start_pointer = ((dec_start_pointer * 100) / PRN_ReducData.GA_H_Reduction);
 #else
		dec_start_pointer /= PRN_ReducData.GA_H_Reduction;
 #endif
 #if (PRO_PRINTER == DPI200)
		dec_start_pointer /= 2;
 #endif
	}
	else {
		if (print_mode != SYS_HFINE) {
#if (0)	/* By M.Tachibana 1998/05/15 */
//			dec_start_pointer /= 2;
#endif
 #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
			dec_start_pointer = ((dec_start_pointer * 100) / PRN_ReducData.GA_H_Reduction);
 #else
			dec_start_pointer /= PRN_ReducData.GA_H_Reduction;
 #endif
 #if (PRO_PRINTER == DPI200)
			dec_start_pointer /= 2;
 #endif
		}
	}

#endif

	/**プリンタコーデックの復号化&DMA転送のパラメータを設定する*/
		/** Kiri用追加パラメータ */
	dec_blk.CodecType = dma_blk.CodecType			= PRINTER_CODEC;		/** 復号化&DMA転送に使用するコーデックID (ex. SCANNER_CODEC)*/
	dec_blk.CodeType								= MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Code;	/** 復号化方式 */
		/** 入出力パラメータ */
	dec_blk.FRWORD_Status = dma_blk.FRWORD_Status	= 304;					/** フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	dec_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/** 復号化パラメータ Ch.0 */
#if (PRO_PRINT_TYPE == LED)	/**ＬＥＤプリンタの場合*/
	dec_blk.O_OBXR_Status	= CDC_GetOBXR_Size(prt_queue);						/** 出力オフセット(左寄せ 左データカット)*/
 #if (PRO_PRINTER == DPI400)
  #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
	dec_blk.OTWORD_Status = dma_blk.T1_WORD_Status = ((256*100) / PRN_ReducData.GA_H_Reduction);	/** 復号化ページ幅(復号化した結果できる1ラインの画素数) *//** DMA転送ワード数 (== １ラインのプリンタＧ／Ａ転送ワード数) */
  #else
	dec_blk.OTWORD_Status = dma_blk.T1_WORD_Status = 256 / PRN_ReducData.GA_H_Reduction;	/** 復号化ページ幅(復号化した結果できる1ラインの画素数) *//** DMA転送ワード数 (== １ラインのプリンタＧ／Ａ転送ワード数) */
  #endif
 #endif
 #if (PRO_PRINTER == DPI200)
	dec_blk.OTWORD_Status = dma_blk.T1_WORD_Status = 128 / PRN_ReducData.GA_H_Reduction;	/** 復号化ページ幅(復号化した結果できる1ラインの画素数) *//** DMA転送ワード数 (== １ラインのプリンタＧ／Ａ転送ワード数) */
 #endif
#endif
#if (PRO_PRINT_TYPE == LASER)	/**ＬＡＳＥＲプリンタの場合*/
	dec_blk.O_OBXR_Status	= (UBYTE)(PRN_PrintDataOffset / 16);				/** 出力オフセット(左寄せ 左データカット)*/
	/* ANZUより移植 1997/07/25 */
	dec_blk.OTWORD_Status = dma_blk.T1_WORD_Status = (UWORD)(prn_codec_limit /(16*GA_H_Reduction));	/* 1997/07/25 *//** 復号化ページ幅(復号化した結果できる1ラインの画素数) *//** DMA転送ワード数 (== 復号化ページ幅) */
	dec_blk.OTWORD_Status += 1; 											/* By S.Kawasai 1996/04/03 */
	if ((dec_blk.O_OBXR_Status + dec_blk.OTWORD_Status) > dec_blk.FRWORD_Status) {
		dec_blk.OTWORD_Status = (UWORD)(prn_codec_limit /(16*GA_H_Reduction));			/* Feb.27,1996 */ /** 復号化ページ幅(復号化した結果できる1ラインの画素数) */
		dec_blk.OTWORD_Status = (UWORD)(dec_blk.OTWORD_Status - dec_blk.O_OBXR_Status); /* Feb.27,1996 */ /** 復号化ページ幅(復号化した結果できる1ラインの画素数) */
	}
#endif
#if (PRO_ROTATE == ENABLE)	/* By M.Kotani 97/04/22 */
	if (MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Item == SYS_MEM_ROTATE_FILE) {
		/** 回転原稿の主走査の画素数を獲得する */
		dec_blk.D0_PWDR_Status = (ROT_CheckDocumentWidth(MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Size)) / 16;	/** 回転原稿の幅を調べる */
		switch (MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Mode) {
		case SYS_NORMAL_ROT:
			dec_blk.D0_PWDR_Status /= 4;
			break;
		case SYS_SFINE_ROT:
		case SYS_HFINE:
			break;
		default:
			dec_blk.D0_PWDR_Status /= 2;
		break;
		}	/** 復号化ページ幅(復号化する1ラインの画素数をWordで設定) */
	}
	else {
		dec_blk.D0_PWDR_Status	= PRN_ScanScanningLineTable[MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Size][print_mode][HORIZONTAL] / 16;
																				/** 復号化ページ幅(復号化する1ラインの画素数をWordで設定) */
	}
#else
	dec_blk.D0_PWDR_Status	= PRN_ScanScanningLineTable[MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Size][print_mode][HORIZONTAL] / 16;
																				/** 復号化ページ幅(復号化する1ラインの画素数をWordで設定) */
#endif
	dec_blk.D0_OBXR_Status	= 0;								/** 復号化オフセット(右寄せ 左ダミーデータ付け)*/
	dec_blk.D0_RTCR_Status	= 2;								/** 復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	dec_blk.D0_BLGR_Status	= PRN_ReducData.CDCSubLineCount;	/** 復号化処理ライン数(1回に復号化するライン数)*/
	dec_blk.D0_LCONT_Status	= 0;								/** 復号化ラインカウンタ(復号化したライン数(エラーを含む)がセットされます)*/
	dec_blk.D0_ELIN_Status	= 0;								/** 復号化エラーライン数(1ページ内のエラーライン数の総数がセットされます)*/
	dec_blk.D0_VCONV_Status = PRN_ReducData.CDCSubReduction;	/** 復号化副走査方向変換率*/
	dec_blk.D0_HCONV_Status = PRN_ReducData.CDCMainReduction;	/** 復号化主走査方向変換率*/
	dec_blk.D0_LMASK_Status	= 0;								/** 復号化左側白マスク*/
	dec_blk.D0_RMASK_Status	= 0;								/** 復号化右側白マスク*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
	dec_blk.D0_MTOPA_Status	= dec_blk.D0_STRA_Status	= 0x63C0 + dec_start_pointer;	/** 復号化イメージバッファ先頭アドレス*/
																						/** 復号化ライン先頭アドレス(プリンタイメージバッファの符号化開始アドレス)*/
	dec_blk.D0_MENDA_Status								= 0xFE20 + dec_start_pointer;	/** 復号化イメージバッファ最終アドレス 0x260*0x6b=0xfe20*/
	dma_blk.T1_STRA_Status = dma_blk.T1_MTOPA_Status	= 0x63C0 + dma_start_pointer;	/** DMA転送先頭アドレスポインタ*//** DMA転送バッファ先頭アドレス*/
	dma_blk.T1_MENDA_Status								= 0xFE20 + dma_start_pointer;	/** DMA転送バッファ最終アドレス 0x260*0x6b=0xfe20 */
#else
	dec_blk.D0_MTOPA_Status	= dec_blk.D0_STRA_Status	= 0		 + dec_start_pointer;	/** 復号化イメージバッファ先頭アドレス*/
																						/** 復号化ライン先頭アドレス(プリンタイメージバッファの符号化開始アドレス)*/
	dec_blk.D0_MENDA_Status								= 0xFE20 + dec_start_pointer;	/** 復号化イメージバッファ最終アドレス 0x260*0x6b=0xfe20*/
	dma_blk.T1_STRA_Status = dma_blk.T1_MTOPA_Status	= 0 	 + dma_start_pointer;	/** DMA転送先頭アドレスポインタ*//** DMA転送バッファ先頭アドレス*/
	dma_blk.T1_MENDA_Status								= 0xFE20 + dma_start_pointer;	/** DMA転送バッファ最終アドレス 0x260*0x6b=0xfe20 */
#endif
	/**プリンタコーデックのDMA転送のパラメータを設定する*/
		/** Kiri用追加パラメータ */
	dma_blk.Channel	  = 1;				/** 使用するチャンネル (0 or 1)*/
		/** DMA転送パラメータ (CODEC MEMORY <- CUSTOM ･･･ 使用せず) */
	dma_blk.T0_STRA_Status	= 0;							/** DMA転送先頭アドレスポインタ*/
	dma_blk.T0_WORD_Status	= 0;							/** DMA転送ワード数（１ラインのワード数）*/
	dma_blk.T0_BLGR_Status	= 0;							/** DMA転送ライン数*/
	dma_blk.T0_MTOPA_Status	= 0;							/** DMA転送バッファ先頭アドレス*/
	dma_blk.T0_MENDA_Status	= 0;							/** DMA転送バッファ最終アドレス*/
		/** DMA転送パラメータ (CODEC MEMORY -> CUSTOM) */
	dma_blk.T1_BLGR_Status	= PRN_FROM_CODEC_LINECOUNT;		/** DMA転送ライン数*/
	/**上記のパラメータでコーデックをセットアップする*/
	CodecDecodeSetup(&dec_blk);			/*上記のパラメータであるようにデコードするようにセットアップされる*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/**DMAを正常終了させる*/
#if (0)
** 	CDC1_DMA1_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
** 	IO__PEDR &= ~0x8000;
** 	CodecDMA_TransferSetup(&dma_blk);	/*上記のパラメータにあるようにプリンタに転送するようにセットアップされる*/
** 	AbortCodecDMA_Transfer(PRINTER_CODEC, 1);	/*Add By M.Kotani 1997/11/12*//*使用するコーデック*//*セットするチャンネル*/
**     for (loop_flg = 0; loop_flg < 1000; loop_flg++) {
** 		if (CDC1_DMA1_EndFlag) {	/* DMA ABORTED */
** 			IO__PEDR &= ~0x8000;
** 			IO__PEDR |= 0x8000;
** 			IO__PEDR &= ~0x8000;
** 			break;
** 		}
** 	}
** 	if (loop_flg > 900) {
** 		loop_flg = TRUE;
** 	}
#endif
#endif
	CDC1_DMA1_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
	CodecDMA_TransferSetup(&dma_blk);	/*上記のパラメータにあるようにプリンタに転送するようにセットアップされる*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/**DMAを正常終了させる*/
	AbortCodecDMA_Transfer(PRINTER_CODEC, 1);	/*Add By M.Kotani 1997/11/12*//*使用するコーデック*//*セットするチャンネル*/
#endif
	printer = FALSE;
	loop_flg = TRUE;
	CDC_ImageBufferStatus[PRINTER_CODEC] = CDC_NOT_ACCESS;	/**０で初期化する。イメージメモリを開放する*/
#if (PRO_PRINT_TYPE == LED)
	PrintStatusTime[prt_queue->PhysicalPage % PRN_QUEUE_MAX].Time[2] = SYS_GeneralTimer;		/* for Debug */
 #if defined(POPLAR_H)	/* ページ合成２ページ目先頭ごみ By M.Tachibana 2002/10/02 */
	if (!(SYB_MachineUniqSwitch[90] & 0x20)) {	/* UNIQ_SW_J0 */
		if (PRN_CompPageNo == 1) {
			PRN_StopSMTH_Clear();
			PRN_PrintSUM_ON();
		}
	}
 #endif
#else
	PrintStatusTime.Time[2] = SYS_GeneralTimer;		/* for Debug */
#endif

	while (loop_flg) { /**1ページ復号化するまでループする*/
		CDC_ImageBufferStatus[PRINTER_CODEC]++;		/**イメージバッファ更新回数のログをとる*/
		/* SetCodecParameterRegister(PRINTER_CODEC, D0_HCONV_ADR, PRN_ReducData.CDCMainReduction); Feb.9,1996 */

#if (0)
** #if (PRO_PANEL == KANJI)
** 		/* プリンターコーデックをＭＮ８６０６４にした時のパフォーマンス測定用 By O.Kimoto 1998/04/23 */
** 		SYS_LED1_PortStatus |= 0x0080;
** 		outpw(LED1_PORT, (UWORD)SYS_LED1_PortStatus);
** #endif
#endif

		StartDecode(PRINTER_CODEC, dec_blk.CodeType);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する ※復号化するまでリターンしない*/
		if (CDC_CheckDetectRTC(PRINTER_CODEC)) {	/**コマンド終了割り込みでセットされている終了状態ＳＴＩＲをチェックする*/
			loop_flg = FALSE;	/**RTC検出*/
		}
		if (CDC_CheckDecodeError(PRINTER_CODEC)) {	/**コマンド終了割り込みでセットされている終了状態ＳＴＩＲをチェックする*/
			SYB_MaintenanceSwitch[MNT_SW_A7] |= PRINT_DECODE_ERROR;	/**デコードエラーした事をメモリースイッチにセット*/
			if ((dec_blk.CodeType == SYS_MMR_CODE) || (dec_blk.CodeType == SYS_MG3_CODE)) {	/**MMR or MG3の時*/
				loop_flg = FALSE;	/**デコードエラーで復元不可能*/
#if (PRO_PRINT_TYPE == LED)
				PRN_DisableStrobe();
#endif
			}
		}
		if (printer) { /**プリンタが起動されている時*/
			CMN_DisableInterrupt();	/**割り込み禁止*/
			if (!CDC1_DMA1_EndFlag) {	/**DMA未終了のとき*/
				DEBUG_dec_first_cnt++;
				wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ53LinesのDMA終了を待つ*/
			}
			else {
				DEBUG_dma_first_cnt++;
			}
			CDC1_DMA1_EndFlag = 0;
			CMN_EnableInterrupt();	/**割り込み許可*/
			/**次のＤＭＡの起動は割り込みルーチンの中で処理する*/
		}
		else {
			printer = TRUE;
			PRN_StartImagePrint();	/**プリンタを起動する*/
#if (PRO_PRINT_TYPE == LED)
			PrintStatusTime[prt_queue->PhysicalPage % PRN_QUEUE_MAX].Time[6] = SYS_GeneralTimer;
 #if defined(POPLAR_H) && defined(JP0)	/* V851 原稿付きﾁｪｯｸﾒｯｾｰｼﾞごみ対策 By M.Tachibana 2002/09/28 */
			if (SYB_MachineUniqSwitch[90] & 0x10) {	/* UNIQ_SW_J0 */
				if (PRN_CheckListWithImageData()) {
					wai_tsk(3);
					PRN_EnableStrobe();
				}
			}
 #endif
#endif
		}
	}
	wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ53LinesのDMA終了を待つ*/
	/*ここでデコードしたすべてのデータはプリンターに転送したのじゃ！ (^m^;)*/
#if (PRO_PRINT_TYPE == LED)
	PrintStatusTime[prt_queue->PhysicalPage % PRN_QUEUE_MAX].Time[3] = SYS_GeneralTimer;
#else
	PrintStatusTime.Time[3] = SYS_GeneralTimer;
#endif
	wai_tsk(0xFFFF);
#endif	/* 1998/06/10 H.Yoshikawa */
}

#if (PRO_PRINT_TYPE == LED)
/*************************************************************************
	module		:[プリントサイズを決定する]
	function	:[
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1997/12/06]
	author		:[橘正樹]
*************************************************************************/
UBYTE	CDC_GetOBXR_Size(
struct PrintQueueData_t *prt_queue )
{
	UWORD	size;
	UBYTE	scn_size;
	UBYTE	item;

	size = 0;

	scn_size = MEM_IndexTable[prt_queue->Index[PRN_CompPageNo].IndexNo].Size;

/*#if (PRO_FBS == ENABLE)*/
#if (PRO_SCAN_WIDTH == A3WIDTH)	/* By M.Tachibana 1998/04/07 */
#if (0)	/* By M.Tachibana 1998/06/15 */
//	if ((SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE)
//	 || (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE)) {
//	/*	if (SYB_MaintenanceSwitch[MNT_SW_C9] & SCANNER_CODEC_REDUCE) { この条件はいらない */
//		/*------------------------------------------------------
//		** Ａ３からＢ４への縮小
//		** (scn_size == SYS_DOCUMENT_A3_SIZE) 1997/12/19
//		*/
//		if (McopyPtr->ScanType == SYS_ADF_SCAN) {	/* 1997/12/26 */
//			if ((McopyPtr->ScanSize == SYS_DOCUMENT_A3_SIZE)
//			 && (prt_queue->PrintedForm == SYS_B4_PAPER)) {
//				/*
//				** A3->B4コピー スキャナで縮小するパスでFine,Normalの時、左端がきれる
//				** Ｇ／Ａの拡大を考慮していなかったため
//				** By M.Tachibana 1998/06/05
//				*/
//			/*	size = 3;	*/
//				size = (3 / PRN_ReducData.GA_H_Reduction);
//				if (PRN_ReducData.GA_H_Reduction == 2) {
//					size += 1;	/* 左余白が空きすぎるため微調整 */
//				}
//			}
//		}
//	}
#endif
	item = (MEM_IndexTable[prt_queue->Index[PRN_CompPageNo].IndexNo].Item & ~MEM_NOW_STORING);
	if ((SYS_DocumentPrintItem == SYS_MEM_MULTI_COPY_FILE)
	 || (SYS_DocumentPrintItem == SYS_MEM_MANUAL_COPY_FILE)) {
		if (McopyPtr->ScanType == SYS_ADF_SCAN) {	/* 1997/12/26 */
			/* A3原稿スキャナで縮小 */
			if (McopyPtr->ScanSize == SYS_DOCUMENT_A3_SIZE) {
				switch (prt_queue->PrintedForm) {
				case SYS_B4_PAPER:
				case SYS_B5R_PAPER:
  #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
					size = ((3*100) / PRN_ReducData.GA_H_Reduction);
					if ((PRN_ReducData.GA_H_Reduction/100) == 2) {
						size += 1;	/* 左余白が空きすぎるため微調整 */
					}
  #else
					size = (3 / PRN_ReducData.GA_H_Reduction);
					if (PRN_ReducData.GA_H_Reduction == 2) {
						size += 1;	/* 左余白が空きすぎるため微調整 */
					}
  #endif
					break;
				case SYS_A4_PAPER:
				case SYS_A5R_PAPER:
				case SYS_F4_PAPER:
  #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
					if (!(SYB_MaintenanceSwitch[MNT_SW_C9] & SCANNER_CODEC_REDUCE)) {
						size = ((3*100) / PRN_ReducData.GA_H_Reduction);
						if ((PRN_ReducData.GA_H_Reduction/100) == 2) {
							size += 1;	/* 左余白が空きすぎるため微調整 */
						}
					}
  #else
					if (!(SYB_MaintenanceSwitch[MNT_SW_C9] & SCANNER_CODEC_REDUCE)) {
						size = (3 / PRN_ReducData.GA_H_Reduction);
						if (PRN_ReducData.GA_H_Reduction == 2) {
							size += 1;	/* 左余白が空きすぎるため微調整 */
						}
					}
  #endif
					break;
				default:
					break;
				}
			}
		}
	}
	else {
		/* PCプリント,回転以外 */
		if ((item != SYS_MEM_PC_RX_FILE) && (item != SYS_MEM_ROTATE_FILE)) {
			if (scn_size == SYS_DOCUMENT_A3_SIZE) {
				switch (prt_queue->PrintedForm) {
				case SYS_B4_PAPER:
				case SYS_B5R_PAPER:
				case SYS_A4_PAPER:
				case SYS_A5R_PAPER:
				case SYS_F4_PAPER:
  #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
					size = ((3*100) / PRN_ReducData.GA_H_Reduction);
					if ((PRN_ReducData.GA_H_Reduction/100) == 2) {
						size += 1;	/* 左余白が空きすぎるため微調整 */
					}
  #else
					size = (3 / PRN_ReducData.GA_H_Reduction);
					if (PRN_ReducData.GA_H_Reduction == 2) {
						size += 1;	/* 左余白が空きすぎるため微調整 */
					}
  #endif
					break;
				default:
					break;
				}
			}
		}
	}
#endif

	if (prt_queue->Index[PRN_CompPageNo].Reduction < 100) {
		size += PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_PAPER_MASK];
		size = (size * prt_queue->Index[PRN_CompPageNo].Reduction) / 100;
#if (PRO_PRINTER == DPI200)	/* add M.Tachibana 1998/05/21 */
#if (0)	/* 下記処理に変更 By M.Tachibana 1998/09/02 */
//		if (scn_size == SYS_DOCUMENT_B4_SIZE) {
//			switch (prt_queue->PrintedForm) {
//			case SYS_A4_PAPER:
//			case SYS_A5R_PAPER:
//				size = 0;
//				break;
//			default:
//				break;
//			}
//		}
#endif
		if ((scn_size == SYS_DOCUMENT_B4_SIZE)
		 && ((prt_queue->PrintedForm == SYS_A4_PAPER) || (prt_queue->PrintedForm == SYS_A5R_PAPER))) {
			/* B4 -> A4記録紙 縮小時の微調整 */
			size = 0;
		}
		else {
			/* 固定縮小時の左欠けが縮小率が小さいほど大きくなるため微調整 */
			size /= 2;
		}
#endif
	}
	else if (prt_queue->Index[PRN_CompPageNo].Reduction > 100) {
		size += PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_PAPER_MASK];
		/* (50/size) = ( 100% / size ) / 2 四捨五入 */
		size = (size * (prt_queue->Index[PRN_CompPageNo].Reduction - 100 + (50/size) )) / 100;
	}

	return ((UBYTE)size);
}
#endif

#if (PRO_SCN_CODEC_TYPE == MN86063) || (PRO_SCN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
/*************************************************************************
	module		:[ECMバッファにスキャナイメージをエンコードする]
	function	:[
		1.通信コーデックを獲得する
		2.コーデックパラメータを設定する
		3.エンコード開始する
		5.通信コーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1994/3/26]
	author		:[曽根岡拓]
*************************************************************************/
#define LOCAL2STATIC	/*ローカル変数をスタティック変数にする 1998/02/10 By M.Kotani*/
#ifdef LOCAL2STATIC
	static struct CodecEncodeParameterBlk_t enc_blk2;
	static struct CodecDMA_TransferParameterBlk_t dma_blk2;
#endif
void CDC_STxCodeConvertPageTask(void)
{
	UBYTE encode_counter;
	UBYTE loop_flg;
	UBYTE encode_line;
	UBYTE encode_kpara;
	UBYTE tti_available;
	UBYTE tti_inside;
	UBYTE tti_line;		/**TTI Inside時に無効にする画データのライン数*/
	UBYTE cdc_stat;
	UWORD dma_address;
	UWORD encode_address;
	UWORD encode_size;
	UWORD tskno_EncodeDMA_End = 0xffff;
	UDWORD scan_line;
	UDWORD reduc;
	UBYTE is_end_of_scan;
#if (PRO_CCD == DPI200)
	UWORD real_pix_size;	/* By Y.Suzuki 1998/11/07 */
	UWORD src_pix_size;		/* By Y.Suzuki 1998/11/07 */
	UWORD reduction;		/* T.Nose 1998/11/13 */
#endif

#ifndef LOCAL2STATIC
	struct CodecEncodeParameterBlk_t enc_blk2;
	struct CodecDMA_TransferParameterBlk_t dma_blk2;
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	struct DMA_Data_t CodecTxDMA;
#endif

/*
** スキャナ送信 Ｔ．３．１エラー不具合修正
** 下記２ライン下から移動してきました 1998/04/16 by T.Soneoka
*/
	CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/
	cdc_stat = CDC_CONTINUE;

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	SetClear((UBYTE *)&enc_blk2, sizeof(struct CodecEncodeParameterBlk_t), 0x00);
#endif
	/*------------------*/
	/*	ＴＴＩ送出処理	*/
	/*------------------*/
	tti_available = FCM_PtnrChkTTI_TxAvailable();	/* 属性2 */
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
#if (0) /* ＭＮＴ＿ＳＷ＿Ｂ５は使用できません 1998/04/16 by T.Soneoka */
**	if ((SYS_DocBlock.Dst.Code == SYS_JBIG_CODE)
**	&& (SYB_MaintenanceSwitch[MNT_SW_B5] & JBIG_SCANNERTX_TTI_OFF)) {
#else
	if ((SYS_DocBlock.Dst.Code == SYS_JBIG_CODE)
	&& (SYB_MaintenanceSwitch[MNT_SW_B8] & JBIG_SCANNERTX_TTI_OFF)) {
#endif
		tti_available = 0;
	}
#endif
	tti_inside = CHK_UNI_TTI_Inside();	/* USA以外のため 96/05/16 By T.Yamaguchi */

	/*----------------------*/
	/*	符号化ページ幅設定	*/
	/*----------------------*/
	encode_size = GetCodecSize(SYS_DocBlock.Dst.Size, SYS_DocBlock.Dst.Mode);
	/*--------------------------*/
	/*	符号化Ｋパラメータ設定	*/
	/*--------------------------*/
	encode_kpara = GetK_Parameter(SYS_DocBlock.Dst.Mode);
	/*--------------------------*/
	/*	符号化変化率設定処理	*/
	/*--------------------------*/
	TxPixReductionSet(SYS_DocBlock.Src.Size,
					  SYS_DocBlock.Src.Mode,
					  SYS_DocBlock.Dst.Size,
					  SYS_DocBlock.Dst.Mode,
					  SYS_DocBlock.ModeMethod);

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1998/1/7 */
	GetCodecFlag = NO;
	tti_line = 0;
	if (tti_available) {	/**ＴＴＩを送出するとき*/
			/*------------------------------*/
			/*	スキャナコーデックを獲得	*/
			/*------------------------------*/
			if (!GetCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
				SaveReturnAddressAndJumpBegin();
			}
			GetCodecFlag = YES;
			/*----------------------------------*/
			/*	ＥＣＭバッファにＴＴＩをセット	*/
			/*----------------------------------*/
			EcmBufferBaseWritePoint = CDC_DataTransferAndSetTTI();
			tti_line = EncodeLine(SCANNER_CODEC);	/* TTIライン数 */
#if (0) /* 上記に変更 JBIG以外のコードでもスキャナコーデックを使用するように統一します */
//		if (SYS_DocBlock.Dst.Code == SYS_JBIG_CODE) {
//			/*------------------------------*/
//			/*	スキャナコーデックを獲得	*/
//			/*------------------------------*/
//			if (!GetCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
//				SaveReturnAddressAndJumpBegin();
//			}
//			/*----------------------------------*/
//			/*	ＥＣＭバッファにＴＴＩをセット	*/
//			/*----------------------------------*/
//			EcmBufferBaseWritePoint = CDC_DataTransferAndSetTTI();
//			tti_line = EncodeLine(SCANNER_CODEC);	/* TTIライン数 */
//		}
//		else {
//			/*--------------------------*/
//			/*	通信コーデックを獲得	*/
//			/*--------------------------*/
//			if (!GetCodec(COMMUNICATION_CODEC, CODEC_CHARACTER_TX)) {
//				/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
//				SaveReturnAddressAndJumpBegin();
//			}
//			/*----------------------------------*/
//			/*	ＥＣＭバッファにＴＴＩをセット	*/
//			/*----------------------------------*/
//			EcmBufferBaseWritePoint = CDC_SetTTI();
//			tti_line = CDC_GetTxTTI_Line( SCN_ModeSw );						/* TTIライン数 */
//			/*----------------------*/
//			/*	通信コーデック開放	*/
//			/*----------------------*/
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_CHARACTER_TX)) {
//				/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
//				SaveReturnAddressAndJumpBegin();
//			}
//			/*------------------------------*/
//			/*	スキャナコーデックを獲得	*/
//			/*------------------------------*/
//			if (!GetCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {	/**	スキャナコーデック獲得	*/
//				/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
//				SaveReturnAddressAndJumpBegin();
//			}
//		}
#endif
	}
	else {
		EcmBufferBaseWritePoint = ECM_BUFFER_AREA_START_ADDRESS;
		/*------------------------------*/
		/*	スキャナコーデックを獲得	*/
		/*------------------------------*/
		if (!GetCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {	/**	スキャナコーデック獲得	*/
			/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
			SaveReturnAddressAndJumpBegin();
		}
		GetCodecFlag = YES;
	}
	CDC_EncodePageTaskMsg.Item = FROM_SCN_SUB_TASK;
	/** 原稿長制限のライン数と読み取りライン数をセットする  関数化 1997/05/27  By T.Yamaguchi */
	SCN_ScanMaxLine = CDC_GetDocumentMaxLine( SCN_ModeSw );			/* 最大読み取りライン数 */

#else
	if (tti_available != 0) {	/**ＴＴＩを送出するとき*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE) By Y.Suzuki 1996/09/26 */
		SCD_TxTTI_OnScanTx();
#else
		/*--------------------------*/
		/*	通信コーデックを獲得	*/
		/*--------------------------*/
		if (!GetCodec(COMMUNICATION_CODEC, CODEC_CHARACTER_TX)) {
			/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
			SaveReturnAddressAndJumpBegin();
		}
		/*----------------------------------*/
		/*	ＥＣＭバッファにＴＴＩをセット	*/
		/*----------------------------------*/
		EcmBufferBaseWritePoint = CDC_SetTTI();
		/*----------------------*/
		/*	通信コーデック開放	*/
		/*----------------------*/
		if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_CHARACTER_TX)) {
			/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
			SaveReturnAddressAndJumpBegin();
		}
#endif
	}
	else {
		EcmBufferBaseWritePoint = ECM_BUFFER_AREA_START_ADDRESS;
	}
	/*------------------------------*/
	/*	スキャナコーデックを獲得	*/
	/*------------------------------*/
	if (!GetCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {	/**	スキャナコーデック獲得	*/
		/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
		SaveReturnAddressAndJumpBegin();
	}
	GetCodecFlag = YES;

	CDC_EncodePageTaskMsg.Item = FROM_SCN_SUB_TASK;

	/** 原稿長制限のライン数と読み取りライン数をセットする  関数化 1997/05/27  By T.Yamaguchi */
	SCN_ScanMaxLine = CDC_GetDocumentMaxLine( SCN_ModeSw );			/* 最大読み取りライン数 */
	tti_line = CDC_GetTxTTI_Line( SCN_ModeSw );						/* TTIライン数 */
#endif
#if (PRO_FBS == ENABLE)
	CDC_DocumentScanLine = CDC_GetDocumentScanLine( SCN_ModeSw );	/* FBS定型原稿の読み取りライン数 */
	/** FBSでの読み取りライン数を、モードと縮小率で補正する */
	if (SYS_ScannerExecMode == SCN_FBS) {
		switch (SCN_ModeSw) {
		case	SYS_GRAY16:
		case	SYS_GRAY16_SEP:
		case	SYS_GRAY32:
		case	SYS_GRAY32_SEP:
		case	SYS_GRAY64:
		case	SYS_GRAY64_SEP:
			/* 読み取るラインにIDPでの縮小率を掛ける */
			scan_line = (UDWORD)CDC_DocumentScanLine;
			scan_line *= IDP_GraySTxReductionRate[SCN_ScannerTxReductionPattern];
			scan_line /= 1000;
			CDC_DocumentScanLine = (UWORD)scan_line;
			break;
		}
	}
#endif

	/*---------------------------------------------------------*/
	/**スキャナコーデックの符号化&DMA転送のパラメータを設定する*/
	/*---------------------------------------------------------*/
	/**使用するコーデックを決定する*/
	enc_blk2.CodecType = dma_blk2.CodecType = SCANNER_CODEC; /**符号化&DMA転送に使用するコーデックID (ex. SCANNER_CODEC)*/
	/** 入出力パラメータを決定する */
	enc_blk2.FRWORD_Status = dma_blk2.FRWORD_Status = 304;					/**(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
	enc_blk2.INLINE_Status = dma_blk2.T0_BLGR_Status = 20;		/**入力ライン数(1回に符号化するライン数) & DMA転送ライン数*/
	enc_blk2.C0_MTOPA_Status = dma_blk2.T0_MTOPA_Status = 0;		/**符号化イメージバッファ先頭アドレス & DMA転送バッファ先頭アドレス*/
	enc_blk2.C0_MENDA_Status = dma_blk2.T0_MENDA_Status= 0x6160;	/**符号化イメージバッファ最終アドレス & DMA転送バッファ最終アドレス*/
#else
	enc_blk2.INLINE_Status = dma_blk2.T0_BLGR_Status = 53;		/**入力ライン数(1回に符号化するライン数) & DMA転送ライン数*/
	enc_blk2.C0_MTOPA_Status = dma_blk2.T0_MTOPA_Status = 0;		/**符号化イメージバッファ先頭アドレス & DMA転送バッファ先頭アドレス*/
	enc_blk2.C0_MENDA_Status = dma_blk2.T0_MENDA_Status = 0xFE20;	/**符号化イメージバッファ最終アドレス & DMA転送バッファ最終アドレス*/
#endif
#if (PRO_CCD == DPI200) /* とりあえず POPLAR_L のみ T.Nose 1998/11/13 */
	/* 縮小後の画像を中央寄せにする。By Y.Suzuki 1998/11/07 */
	if (CHK_UNI_ReducedPixToMid()) {
		if ((SYS_DocBlock.Src.Mode == SYS_GRAY16)
		 || (SYS_DocBlock.Src.Mode == SYS_GRAY16_SEP)
		 || (SYS_DocBlock.Src.Mode == SYS_GRAY32)
		 || (SYS_DocBlock.Src.Mode == SYS_GRAY32_SEP)
		 || (SYS_DocBlock.Src.Mode == SYS_GRAY64)
		 || (SYS_DocBlock.Src.Mode == SYS_GRAY64_SEP)) {
			switch (SCN_ScannerTxReductionPattern) {
			case SYS_A3_400_TO_B4_400:
				reduction = 0x360;	/* 84.375(27/32)% */
				break;
			case SYS_A3_400_TO_A4_400:
				reduction = 0x2C0;	/* 68.75(22/32)% */
				break;
			case SYS_B4_400_TO_A4_400:
				reduction = 0x340;	/* 81.25(26/32)% */
				break;
			default:
				reduction = 0x400;	/* 100% */
			}
		}
		else {
			reduction = Pix_H_Reduction;
		}
		src_pix_size = SCN_GetEncodePageSize(SCN_GetEncodeStoreImageRes()) / 16;	/** 入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定 */	/** DMA転送ワード数（１ラインのワード数）*/
		real_pix_size = (src_pix_size * reduction)/1024;
		if (real_pix_size < encode_size) {
			enc_blk2.I_OBXR_Status = (encode_size - real_pix_size)/2;		/**符号化オフセット*/
		}
		else {
			enc_blk2.I_OBXR_Status = 0;								/**符号化オフセット*/
		}
	}
	else {
		enc_blk2.I_OBXR_Status = 0;									/**符号化オフセット*/
	}
#else
	enc_blk2.I_OBXR_Status = 0;									/**符号化オフセット*/
#endif
	/** 符号化パラメータ Ch.0の固定値を決定する*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1998/1/7 */
	if (SYS_DocBlock.Dst.Code == SYS_JBIG_CODE) {
		enc_blk2.C0_LCONT_Status = tti_line;								/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
	}
	else {
		enc_blk2.C0_LCONT_Status = 0;								/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
	}
#else
	enc_blk2.C0_LCONT_Status = 0;								/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
#endif
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/**DMA1ラインからスタートさせる*/	/*By M.Kotani 1997/11/26*/
	enc_blk2.C0_STRA_Status = (enc_blk2.FRWORD_Status * 2);	/**符号化ライン先頭アドレス(スキャナイメージバッファの符号化開始アドレス)*/
#else
	enc_blk2.C0_STRA_Status = 0;								/**符号化ライン先頭アドレス(スキャナイメージバッファの符号化開始アドレス)*/
#endif
	enc_blk2.C0_OBXR_Status = 0;									/**符号化オフセット*/
	/**スキャナコーデックのDMA転送のパラメータを設定する*/
	dma_blk2.Channel = 0;	/** 使用するチャンネル (0 or 1)*/
	/** DMA転送パラメータ (CODEC MEMORY <- CUSTOM) */
	dma_blk2.T0_STRA_Status = 0;	/** DMA転送先頭アドレスポインタ*/
	/** DMA転送パラメータ (CODEC MEMORY -> CUSTOM ･･･ 使用せず) */
	dma_blk2.T1_STRA_Status = 0;	/** DMA転送先頭アドレスポインタ*/
	dma_blk2.T1_WORD_Status = 0;	/** DMA転送ワード数（１ラインのワード数）*/
	dma_blk2.T1_BLGR_Status = 0;	/** DMA転送ライン数*/
	dma_blk2.T1_MTOPA_Status = 0;	/** DMA転送バッファ先頭アドレス*/
	dma_blk2.T1_MENDA_Status = 0;	/** DMA転送バッファ最終アドレス*/
	/** 最小伝送時間を決定する */
	if (CommunicateType == TX_G3_SCAN) {
		if (SYS_DocBlock.MSE_Method == MSE1) {
			enc_blk2.C0_MCLR_Status = SetTransmitCount((UWORD)10);
		}
		else {
			enc_blk2.C0_MCLR_Status = SYS_DocBlock.MinimumLineSize;	/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
		}
	}
	else {
		enc_blk2.C0_MCLR_Status = 0;
	}
	/*--------------------------------------------------------*/
	/*  符号化方式を決定する                                  */
	/*	符号化方式 \src\atlanta\define\sysdoc.h				  */
	/*	#define SYS_IMAGE_DATA	   0						  */
	/*	#define SYS_MH_CODE		   1						  */
	/*	#define SYS_MR_CODE		   2						  */
	/*	#define SYS_MMR_CODE	   3						  */
	/*	#define SYS_MG3_CODE	   4	MN86063&4のみ使用可能 */
	/*	#define SYS_JBIG_CODE	   5	MN86064のみ使用可能   */
	/*--------------------------------------------------------*/
	enc_blk2.CodeType = SYS_DocBlock.Dst.Code; /** 符号化方式 (ex. SYS_MMR_CODE)*/
	enc_blk2.C0_KPR_Status = encode_kpara;	/**符号化Kパラメータ*/
	/*****************************/
	/**主走査方向のハラメータ設定*/
	/*****************************/
#if (PRO_SCN_CODEC_TYPE == MN86064)
	if (Pix_H_Reduction == 0x400) {
		enc_blk2.C0_HCONV_Status = 0;	/**符号化主走査方向変換率 100 % */
	}
	else {
		enc_blk2.C0_HCONV_Status = Pix_H_Reduction | 0x4000;	/**主走査細線保持有効*/
	}
#else
	if ((Pix_H_Reduction == 0x400) && (Pix_V_Reduction == 0x00)) {
		enc_blk2.C0_HCONV_Status = 0;	/**符号化副走査方向変換率 100 % */
	}
	else {
		enc_blk2.C0_HCONV_Status = Pix_H_Reduction | 0x4000;	/**符号化副走査方向変換率 100 % */
	}
#endif
	enc_blk2.INWORD_Status = dma_blk2.T0_WORD_Status = EncInpStatus; /**入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(A3_SIZE))*/ /** DMA転送ワード数（１ラインのワード数）*/
	enc_blk2.C0_PWDR_Status = EncOtpStatus;	/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)(1/2設定) May.19,1994 */

	enc_blk2.C0_LMASK_Status = 0;	/**符号化左側白マスク*/
	enc_blk2.C0_RMASK_Status = 0;	/**符号化右側白マスク*/
	if (SCN_WhiteMaskFlag) { /** 両端白マスク有り *//* 追加 T.Nose 1997/08/29 */
		enc_blk2.C0_LMASK_Status = enc_blk2.C0_RMASK_Status = SCN_GetEncodeMaskSize(SCN_GetEncodeStoreCodeRes()) / 8;
#if (PRO_FBS == ENABLE)
		if (SYS_ScannerExecMode == SCN_ADF) {
#if defined(USA) /* レター・リーガル対応 T.Nose 1998/03/06 */
			 if (SYS_DocumentScanSize == SYS_DOCUMENT_A4_SIZE) {
				enc_blk2.C0_LMASK_Status	= 2 * 2;	/**符号化左側白マスク 2mm */
				enc_blk2.C0_RMASK_Status	= 2 * 2;	/**符号化右側白マスク 2mm */
			}
#endif
		}
		/** FBS読取りなら、ADFでの白マスク量に設定された左右余白(白マスク)量を加える */
		else { /* SCN_FBS */
			switch (SCN_RegularDocumentSize) { /* レター・リーガル対応 T.Nose 1998/03/06 */
			case SYS_REGULAR_SIZE_LETTER:
			case SYS_REGULAR_SIZE_LEGAL:
				enc_blk2.C0_LMASK_Status	= 2 * 2;	/**符号化左側白マスク 2mm */
				enc_blk2.C0_RMASK_Status	= 2 * 2;	/**符号化右側白マスク 2mm */
				break;
			default:
				break;
			}
			enc_blk2.C0_LMASK_Status += CHK_UNI_FBS_LeftMargin(SCN_GetEncodeStoreCodeRes()) / 8;
			enc_blk2.C0_RMASK_Status += CHK_UNI_FBS_RightMargin(SCN_GetEncodeStoreCodeRes()) / 8;
		}
#endif
	}
#if (0) /* 上記の関数 SCN_GetEncodeMaskSize()の中で送信モードによるマスク量は考慮されていますので、以下の処理はいりません by T.Soneoka 1998/05/22 */
**	/** HFineの時はマスク量を2倍する  ICHOU */
**	if (SYS_DocBlock.Dst.Mode == SYS_HFINE) {
**		enc_blk2.C0_LMASK_Status *= 2;
**		enc_blk2.C0_RMASK_Status *= 2;
**	}
#endif

	/*****************************/
	/**副走査方向のハラメータ設定*/
	/*****************************/
#if (PRO_SCN_CODEC_TYPE == MN86064)
	if (Pix_V_Reduction == 0x00) {	/*副走査等倍の時*/
		enc_blk2.C0_VCONV_Status = 0;	/**符号化副走査方向変換率 100%*/
		enc_blk2.Vmn_Status = 0;	/**副走査:間引き指定 MN86063では無効*/
		/* ここからファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
		if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
			if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
				enc_blk2.C0_VCONV_Status = 0x2000;	/**符号化副走査方向変換率 50%*/
				enc_blk2.Vmn_Status = 0x8000;	/** 副走査:ラインOR処理 */
			}
		}
		/* ここまでファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
	}
	else {
		/* ここからファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
		if (SCN_ModeSw == SYS_NORMAL) { /** 読み取りモードをチェック */
			if (CHK_UNI_FineNormalConvert()) { /* ファイン→ノーマル変換する */
				/*	６５５３６－（Reduc×６５５３６）＝ Pix_V_Reduction */
				reduc = (UDWORD)((UDWORD)65536 - (UDWORD)Pix_V_Reduction);
				reduc /= (UDWORD)2;	/*ここで%*0.01*65536の縮小率が求まる*/
				/*ここからPix_V_Reductionを求める*/
				Pix_V_Reduction = (UWORD)((UDWORD)65536 - reduc);
			}
		}
		/* ここまでファイン→ノーマル変換 T.Nose Add By M.Kotani 1998/01/17 */
		enc_blk2.C0_VCONV_Status = Pix_V_Reduction / 4;	/**TBD符号化副走査方向変換率*//**MN86064の場合は設定値が1/4です*/
		if (enc_blk2.C0_VCONV_Status > 0x2000) {
			enc_blk2.Vmn_Status = 0;	/**コーデックバグ By M.Kotani 1997/11/17*/
		}
		else {
			enc_blk2.Vmn_Status = 0x8000;	/** 副走査:ラインOR処理 */
		}
	}
#else
	if ((Pix_H_Reduction == 0x400) && (Pix_V_Reduction == 0x00)) {
		enc_blk2.C0_VCONV_Status = 0;	/**TBD符号化副走査方向変換率*/
	}
	else {
		enc_blk2.C0_VCONV_Status = Pix_V_Reduction;	/**TBD符号化副走査方向変換率*/
	}
	enc_blk2.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
#endif

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	SetScannerCodecToDramDACK();	/* スキャナコーデックDACK設定 */
	if (enc_blk2.CodeType == SYS_JBIG_CODE) {
#if 0 /* メモリ節約のため、共通のコードを関数にまとめます。By H.Kubo 1998/07/08 */
@@#if (0)	/* 下記メモリＳｗにて設定対応できるように変更 */
@@//		enc_blk2.C_QMCR_Status = (VLENGTH_BIT | TPBON_BIT);	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
@@#endif
@@		enc_blk2.C_QMCR_Status = VLENGTH_BIT;
@@		if (CHK_UNI_JBIG_2lineTemplate()) {
@@			enc_blk2.C_QMCR_Status |= LRLTWO_BIT;
@@		}
@@		if (CHK_UNI_JBIG_TPB_Mode()) {
@@			enc_blk2.C_QMCR_Status |= TPBON_BIT;
@@		}
@@		if (CHK_UNI_JBIG_SDRST()) {
@@			enc_blk2.C_QMCR_Status |= SDRST_BIT;
@@		}
@@		enc_blk2.C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
@@		enc_blk2.C_Yd_Status = 0xffff;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
@@		enc_blk2.C_L0_Status = 128;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
@@		enc_blk2.C_Mx_Status = 127;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
@@		enc_blk2.D_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
@@		enc_blk2.D_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
@@		enc_blk2.D_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
@@		enc_blk2.D_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
@@		enc_blk2.D_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
#else
		CDC_InitCodecEncodeStructJbig(&enc_blk2);
#endif
	}
	ModemMessage.Message = MSG_TTI_COMPLETE;
	snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
	if (tti_available) {	/**ＴＴＩを送出するとき*/
		CodecImageByteSwapDisable(enc_blk2.CodecType);	/**DTCR設定(バイトSwap無効)*/
		CodecEncodeCDCR_Setup(enc_blk2.CodecType);	/**CDCR設定*/
		CodecEncodeParameterSetup(&enc_blk2);			/**パラメータレジスタセット*/
		/* 符号化の初期化コマンドは発行しません */
	}
	else {
		CodecEncodeSetup(&enc_blk2);	/*上記のパラメータであるように最初はＡ面をエンコードするようにセットアップされる*/
	}
	CDC0_DMA0_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
	CodecDMA_TransferSetup(&dma_blk2);	/*上記のパラメータにあるように最初はＡ面に転送するようにセットアップされる*/
	CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;

#if (0) /* 上記に変更 JBIG以外のコードでもスキャナコーデックを使用するように統一します */
//	if (enc_blk2.CodeType == SYS_JBIG_CODE) {
//		enc_blk2.C_QMCR_Status = (VLENGTH_BIT | TPBON_BIT);	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
//		enc_blk2.C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
//		enc_blk2.C_Yd_Status = 0xffff;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
//		enc_blk2.C_L0_Status = 128;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
//		enc_blk2.C_Mx_Status = 127;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
//		enc_blk2.D_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
//		enc_blk2.D_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
//		enc_blk2.D_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
//		enc_blk2.D_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
//		enc_blk2.D_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
//
//		ModemMessage.Message = MSG_TTI_COMPLETE;
//		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
//		if (tti_available != 0) {	/**ＴＴＩを送出するとき*/
//			CodecImageByteSwapDisable(enc_blk2.CodecType);	/**DTCR設定(バイトSwap無効)*/
//			CodecEncodeCDCR_Setup(enc_blk2.CodecType);	/**CDCR設定*/
//			CodecEncodeParameterSetup(&enc_blk2);			/**パラメータレジスタセット*/
//			/* JBIG初期化はかけません */
//		}
//		else {
//			CodecEncodeSetup(&enc_blk2);	/*上記のパラメータであるように最初はＡ面をエンコードするようにセットアップされる*/
//		}
//		CDC0_DMA0_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
//		CodecDMA_TransferSetup(&dma_blk2);	/*上記のパラメータにあるように最初はＡ面に転送するようにセットアップされる*/
//		CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;
//	}
//	else {
//		CodecEncodeSetup(&enc_blk2);	/*上記のパラメータであるように最初はＡ面をエンコードするようにセットアップされる*/
//		CDC0_DMA0_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
//		CodecDMA_TransferSetup(&dma_blk2);	/*上記のパラメータにあるように最初はＡ面に転送するようにセットアップされる*/
//		CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;
//		ModemMessage.Message = MSG_TTI_COMPLETE;
//		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
//	}
#endif
#else
	CodecEncodeSetup(&enc_blk2);	/*上記のパラメータであるように最初はＡ面をエンコードするようにセットアップされる*/
	CDC0_DMA0_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
	CodecDMA_TransferSetup(&dma_blk2);	/*上記のパラメータにあるように最初はＡ面に転送するようにセットアップされる*/
	CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;
	/*-------------*/
	/**Motor Start**/
	/*-------------*/
	ModemMessage.Message = MSG_TTI_COMPLETE;	/*Moved 19941122 Kotani*/
	snd_msg(mbxno.MDM_TaskSub, &ModemMessage);	/*Moved 19941122 Kotani*/
#endif
	/*---------------------*/
	/**ＴＴＩインサイド処理*/
	/*---------------------*/
	if ((tti_inside != 0) && (tti_available != 0)) {	/**ＴＴＩインサイド時*/
		loop_flg = tti_line / dma_blk2.T0_BLGR_Status;	/**スキップするライン数が一回で処理できないとき*/
		while (loop_flg) {
			loop_flg--;
			CMN_DisableInterrupt();	/**割り込み禁止*/
			if (SCN_DocumentStatus != SCN_DOC_END_OF_SCAN) { /**ページ終了フレームの場合*/
				if (!CDC0_DMA0_EndFlag) {
					wai_evt(EVT_CDC0_DMA0_END); /**IDPからイメージメモリ53LinesのDMA終了を待つ*/
				}
				CDC0_DMA0_EndFlag = 0;
			}
			CMN_EnableInterrupt();	/**割り込み許可*/
			if (SCN_DocumentStatus == SCN_DOC_END_OF_SCAN) { /**ページ終了フレームの場合*/
				SetRTC(SCANNER_CODEC, enc_blk2.CodeType);	/**ページの終わりにRTCをセットする*/
#if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//				if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
//					/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
//					SaveReturnAddressAndJumpBegin();
//				}
//				GetCodecFlag = NO;
#else
				CMN_DisableInterrupt();
				if (GetCodecFlag == YES) {
					GetCodecFlag = NO;
					if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
						CMN_EnableInterrupt();
						SaveReturnAddressAndJumpBegin();
					}
				}
				CMN_EnableInterrupt();
#endif
				CodecPageStatus = CDC_RTC_DET;
				TxStartFlag = 1;
				det_evt(EVT_TX_START);
				wai_tsk(0xFFFF);
			}
			CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**add 1994/11/22 Kotani イメージメモリを開放する*/
			SCN_RestartMotor();	/** May.24,1994 Restart Motor if motor has beem stopped */
		}
		CMN_DisableInterrupt();	/**割り込み禁止*/
		if (SCN_DocumentStatus != SCN_DOC_END_OF_SCAN) { /**ページ終了フレームの場合*/
			if (!CDC0_DMA0_EndFlag) {
				wai_evt(EVT_CDC0_DMA0_END); /**IDPからイメージメモリ53LinesのDMA終了を待つ*/
			}
			CDC0_DMA0_EndFlag = 0;
		}
		CMN_EnableInterrupt();	/**割り込み許可*/
		if (SCN_DocumentStatus == SCN_DOC_END_OF_SCAN) { /**ページ終了フレームの場合*/
			SetRTC(SCANNER_CODEC, enc_blk2.CodeType);	/**ページの終わりにRTCをセットする*/
#if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//			if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
//				/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
//				SaveReturnAddressAndJumpBegin();
//			}
//			GetCodecFlag = NO;
#else
			CMN_DisableInterrupt();
			if (GetCodecFlag == YES) {
				GetCodecFlag = NO;
				if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
					CMN_EnableInterrupt();
					SaveReturnAddressAndJumpBegin();
				}
			}
			CMN_EnableInterrupt();
#endif
			CodecPageStatus = CDC_RTC_DET;
			TxStartFlag = 1;
			det_evt(EVT_TX_START);
			wai_tsk(0xFFFF);
		}
		loop_flg = tti_line / dma_blk2.T0_BLGR_Status;	/**スキップした回数*/
		if (loop_flg) {
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, (dma_blk2.T0_BLGR_Status * (loop_flg + 1)) - tti_line);	/**符号化ライン数をセットする*/
#if (0) /* イメージの先頭からのアドレスに修正します by T.Soneoka 1998/05/22 */
**			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2) * (tti_line - (loop_flg * dma_blk2.T0_BLGR_Status)));	/**符号化を開始するイメージメモリのアドレスを計算するby M.kotani 1997/11/6*/
/*#else By Y.Suzuki 1998/10/28 */
//			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2)*tti_line);	/**符号化を開始するイメージメモリのアドレスを計算するby M.kotani 1997/11/6*/
#endif
			/**符号化を開始するイメージメモリのアドレスを計算するBy Y.Suzuki 1998/10/29*/
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
			if (loop_flg == 1) {/* FINE の場合は、TTILINEのままでよいBy Y.Suzuki 1998/10/29 */
				loop_flg = 0;
			}
			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2) * (tti_line - (loop_flg * dma_blk2.T0_BLGR_Status)));
#else
			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2)*tti_line);
#endif
		}
		else {
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, dma_blk2.T0_BLGR_Status - tti_line);	/**符号化ライン数をセットする*/

#if (PRO_SCN_CODEC_TYPE == MN86064)
			/* 舞子チャートノーマル送信、ファインノーマル変換ＯＮ、ＴＴＩインサイドＯＮの時、横縞がでる。
			** 因果関係ははっきりしないが、ＴＴＩの後、符号化開始アドレスを１ライン分後ろへずらすと
			** 横縞が出なくなった。T.Nose 2000/2/3
			/* SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2)*tti_line);	/@ １６ライン分イメージをエンコードするポインタを進める*/
 #if (PRO_CODEC_NUMBER == CDC_SINGLE)
			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2)*(tti_line+1));	/**１６ライン分イメージをエンコードするポインタを進める*/
 #else
			/* POPLAR_H2でノーマル、MMR、スキャナ送信の時５３ライン分昔のデータをエンコードする
			** 上記の対策はファインノーマル変換の場合のみ必要。POPLAR_Hはファインノーマル変換無いので元に戻す
			** T.Nose 2002/08/07
			*/
			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2)*tti_line);	/** １６ライン分イメージをエンコードするポインタを進める*/
 #endif
#else
			SetCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR, (enc_blk2.FRWORD_Status*2)*tti_line);	/** １６ライン分イメージをエンコードするポインタを進める*/
#endif
		}
		if (CodecParameterRegister[SCANNER_CODEC].INLINE_Status) {	/**エンコードするラインがある場合（通常は53ライン）add By M.Kotani 1997/11/13*/
			StartEncode(SCANNER_CODEC, enc_blk2.CodeType);	/**PBR:INLINEに設定したライン数を連続して符号化する。符号化終了までリターンしない。*/
		}
		else {
			CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**コーデックは符号化しないため、イメージメモリを開放する*/
		}
		SCN_RestartMotor();	/** May.24,1994 Restart Motor if motor has beem stopped */
		SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, enc_blk2.INLINE_Status);	/**読み取りライン数を符号化ライン数にセットする*/

#if (PRO_FBS == ENABLE)
		/** FBSでの読み取りライン数を、TTIインサイド分を含む53ラインを引く */
		if (SYS_ScannerExecMode == SCN_FBS) {
			if (tti_line > 53) {
				CDC_DocumentScanLine -= 53 * 2;
			}
			else {
				CDC_DocumentScanLine -= 53;
			}
		}
#endif
	}
	/*-----------------*/
	/**符号化を開始する*/
	/*-----------------*/
/*
** スキャナ送信 Ｔ．３．１エラー不具合修正
** ＰＯＰＬＡＲ＿Ｈで発生した
** 上記ＴＴＩインサイドの処理ですでに符号化データは生成されているので
** この上でCodecPageStatus=CDC_CONINUEにしないとだめ、このタスクの最初で行う
** 1998/04/16 by T.Soneoka
*/
#if (0)
**	CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/
**	cdc_stat = CDC_CONTINUE;
#endif
	encode_counter = 0;
	loop_flg = TRUE;
	is_end_of_scan = FALSE;
	while (loop_flg) { /**1ページ符号化するまでループする*/
		CMN_DisableInterrupt();	/**割り込み禁止*/
		if (SCN_DocumentStatus != SCN_DOC_END_OF_SCAN) { /**ページ終了フレームの場合*/
			if (!CDC0_DMA0_EndFlag) {
				CDC_WaitingCDC0_DMA0_END = TRUE;	/* 1997/05/09 H.Yoshikawa */
				wai_evt(EVT_CDC0_DMA0_END); /**IDPからイメージメモリ53LinesのDMA終了を待つ*/
				CDC_WaitingCDC0_DMA0_END = FALSE;	/* 1997/05/09 H.Yoshikawa */
			}
			CDC0_DMA0_EndFlag = 0;
			CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_LOWER_BLOCK_ACCESS;	/**コーデックはencode_counter回目の符号化を開始する*/
			encode_counter++;

			if (SCN_SpeedCheckPoint != 0) { /* Nov.13,1994 */
				SCN_SpeedCheckPoint = 0;
			}
		}
		CMN_EnableInterrupt();	/**割り込み許可*/

		if (SCN_ScanMaxLine) {
			if (SCN_ScanMaxLine <= SCN_ReadMotorPulseCounter()) { /* TBD */
/* #if defined (DEU)	@* 1997/04/25 s.takeuchi */
#if defined (DEU) || defined (FRA) || defined (GBR) || defined (EC1) || defined(EUR)	/* 沖の要求により。By Y.Suzuki 1998/10/13 */
																		/* 欧州仕様追加 by M.H 1999/09/15 */
				cdc_stat = CDC_DOC_OVER;
				loop_flg = FALSE;
				break;
#else
				CodecPageStatus = CDC_DOC_OVER;
				wai_tsk(0xFFFF);
#endif
			}
		}
/*		DEBUG_ScanLine = SCN_ReadMotorPulseCounter(); */
		if ((SCN_DocumentStatus == SCN_DOC_END_OF_SCAN)
		 || (is_end_of_scan)) { /**ページ終了フレームの場合*/
			loop_flg = FALSE;
			cdc_stat = CDC_RTC_DET;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
#else		/**読み取り専用ハードコーデックあり*/
			dma_address    = ReadCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR);
			encode_address = ReadCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR);
			if (dma_address >= encode_address) {
				encode_address = dma_address - encode_address;
			}
			else {
				encode_address = (dma_address - CodecParameterRegister[SCANNER_CODEC].C0_MTOPA_Status)
							   + (CodecParameterRegister[SCANNER_CODEC].C0_MENDA_Status - encode_address);
			}
			encode_line = encode_address / (dma_blk2.FRWORD_Status * 2);
#endif

#if (PRO_FBS == ENABLE)
			/** FBS読取りで、残りラインが53ライン以下の場合は、残りを今回の符号化ライン数とする
			**	(残りが0ラインなら、すぐ下の「ちょうど53ラインの…」の処理に入る)
			*/
			if (CDC_DocumentScanLine <= enc_blk2.INLINE_Status) {
				encode_line = (UBYTE)CDC_DocumentScanLine;
			}
			/*	ここでEND_OF_SCANにすると残りのエンコード後にRestartMotorできないので
			**	ミラーキャリッジエラー(8)になるため、この処理をループの外でする
			**		1997/03/31 s.takeuchi
			@* スキャナの読取りを止めるためにSCN_DOC_END_OF_SCANにする
			** SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;
			*/

/*			CDC_DebugScanEndLine = SCN_MirrorMotorPulseCount;	@* debug  1997/02/07 s.takeuchi */
#endif

			if (encode_line == 0) {	/**ちょうど５３ラインの倍数で読み取りラインが終了したとき*/
				break;
			}
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, encode_line);
		}
		else {	/**通常（符号化継続） ※次の53LinesのDMAを設定する*/
			/*---------------------------------------------------------------*/
			/** 読み取り開始につき、読み取りラインの割り込みを初期化します。 */
			/** Aug.20,1994													 */
			/*---------------------------------------------------------------*/
			/*CMN_DisableInterrupt();	/**割り込み禁止*/
			/*SCN_SpeedCheckPoint = 0;					/** ライン割り込み数管理テーブルのポインターをイニシャルにセット */
			/*SCN_SetLineStep(SCN_SpeedCheckLine[0]);		/** イニシャルのライン割り込み数をＧ／Ａにセット */
			/*SCN_SetLineInt(SCN_ENABLE);					/** ライン割り込みを許可 */
			/*CMN_EnableInterrupt();	/**割り込み許可*/
			/*CodecDMA_Enable(SCANNER_CODEC, 0);	/**DMA Channel 0を有効にする*/
		}
#if (0) /* by T.Soneoka 1998/04/27 */
** #if defined(POPLAR_H) /* コーデックデバッグ 1998/04/21 T.Nose */
** 		if (DEBUG_DMA_Counter < 50) {
** 			DEBUG_AddressBuffer[DEBUG_DMA_Counter][1] = ReadCodecParameterRegister(SCANNER_CODEC,C0_STRA_ADR);
** 			DEBUG_DMA_Counter++;
** 		}
** #endif
#endif
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
		/* 2000/1/31 T.Nose
		 * スキャナ送信後端欠け
		 * CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status はコーデック割り込みで更新されるが
		 * ページの終わりのときはコーデック割り込みは来ないので直接レジスタから読み出す。
		*/
		/*dma_address		= CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status;*/
		dma_address    	= ReadCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR);
		encode_address	= ReadCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR);
		if (dma_address >= encode_address) {
			encode_address = dma_address - encode_address;
		}
		else {
			encode_address = (dma_address - CodecParameterRegister[SCANNER_CODEC].C0_MTOPA_Status)
						   + (CodecParameterRegister[SCANNER_CODEC].C0_MENDA_Status - encode_address);
		}
		encode_line = encode_address / (dma_blk2.FRWORD_Status * 2);
		CodecParameterRegister[SCANNER_CODEC].INLINE_Status	= encode_line;	/**入力ライン数*/
		if (encode_line) {	/**せってい範囲が1以上のため0のときは何もしない。上の大域変数を見て0の時はエンコードをスタートしないようにする必要がある*/
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, encode_line);
		}
#endif
		if (CodecParameterRegister[SCANNER_CODEC].INLINE_Status) {	/**エンコードするラインがある場合（通常は53ライン）add By M.Kotani 1997/11/13*/
			StartEncode(SCANNER_CODEC, enc_blk2.CodeType);	/**PBR:INLINEに設定したライン数を連続して符号化する。符号化終了までリターンしない。*/
		}
		else {
			CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**コーデックは符号化しないため、イメージメモリを開放する*/
		}
		/* ｺｰﾃﾞｯｸのｴﾝｺｰﾄﾞ開始コマンドとｱﾎﾞｰﾄコマンドのﾀｲﾐﾝｸﾞが見分けるのが困難なため条件追加 96/07/06 ADD By T.Yamaguchi */
		if ((CDC_CheckAccept(SCANNER_CODEC)) || (MDM_TxStopSwFlag == 1)) {	/**コマンド終了割り込みでセットされている終了状態ＳＴＩＲをチェックする*/
			loop_flg = FALSE;	/**アボート検出*/ /*曽根岡ちゃん、たしといたよ(^_^)*/
			cdc_stat = CDC_STOPPED;
			if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {	/* 4LINE 96/07/06 ADD By T.Yamaguchi */
				SCN_StopMotor();
				SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
				LampOff();
			}
		}

#if (PRO_FBS == ENABLE)
		/**	FBS読取りの場合は、残りの符号化ライン数を減算して
		**	次の53ラインの符号化で読取り原稿長を超える時は、残りのライン数を
		**	次回の符号化ライン数としてセットして、1ページの読取りは終了とする
		*/
		if (SYS_ScannerExecMode == SCN_FBS) {
			CDC_DocumentScanLine -= enc_blk2.INLINE_Status;		/* 残りの符号化ライン */
			if (CDC_DocumentScanLine <= enc_blk2.INLINE_Status) {
				/* SCN_DocumentStatus = SCN_DOC_END_OF_SCAN; */
				is_end_of_scan = TRUE;
			}
		}
#endif

		if (CDC0_DMA0_EndFlag) {
		/*	SYS_MemorySwitch[MEMORY_SW_D9] |= MOTOR_OVER_RUN;	ここに来るとモーターが止めきれていない(バッファを壊している) '96,04,15 By N.S. */
			SYB_MaintenanceSwitch[MNT_SW_A7] |= MOTOR_OVER_RUN;				/* '96,04,15 By N.S. */
		}
		CDC_ImageBufferStatus[SCANNER_CODEC] = CDC_NOT_ACCESS;	/**add 1994/11/22 Kotani イメージメモリを開放する*/
/*		if (MDM_TxStopSwFlag == 0) { */	/* STOPスイッチが押された場合  96/07/01 By T.Yamaguchi */
		if (loop_flg) {	/* 中断する時は再スタートしない  1996/11/27 s.takeuchi */
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
			if (!MDM_EcmBufferOverEncodeStop) {	/* By M.Kotani 1997/11/25 */
				SCN_RestartMotor();	/** May.24,1994 Restart Motor if motor has beem stopped */
			}
#else
			SCN_RestartMotor();	/** May.24,1994 Restart Motor if motor has beem stopped */
#endif
		}
	}

#if (PRO_FBS == ENABLE)
	/* ミラーキャリッジエラー(8)対策  1997/03/31 s.takeuchi */
	/** FBS読み取りでスキャナの読取りを止めるためにSCN_DOC_END_OF_SCANにする */
	if (SYS_ScannerExecMode == SCN_FBS) {
		SCN_DocumentStatus = SCN_DOC_END_OF_SCAN;
	}
#endif

	CodecParameterRegister[SCANNER_CODEC].C0_LCONT_Status = ReadCodecParameterRegister(SCANNER_CODEC, C0_LCONT_ADR);

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/19 */
	/* RTC/NEWLENコマンドを実行する前に符号化ラインを待避しておきます （このコマンドによってクリアされてしまうため） */
	SCN_TotalEncodeLine = EncodeLine(SCANNER_CODEC); /** Aug.20,1994 符号化ライン数を保存 */
	/* RTC/NEWLENコマンド発行 */
	if (enc_blk2.CodeType == SYS_JBIG_CODE) {
#if (0)
//		SetCodecParameterRegister(SCANNER_CODEC, C_YD_ADR, SCN_TotalEncodeLine);	/* C-Yd更新 */
#endif
#if (0) /*  by T.Soneoka 1998/02/26 */
//		SetCodecParameterRegister(SCANNER_CODEC, C_YD_ADR, SCN_TotalEncodeLine+1);	/* C-Yd更新 */
#endif
		SetCodecParameterRegister(SCANNER_CODEC, C_YD_ADR, SCN_TotalEncodeLine);	/* C-Yd更新 */
		EnterCodecCommand(SCANNER_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
	}
	else {
		SetRTC(SCANNER_CODEC, SYS_DocBlock.Dst.Code);	/**RTCコマンド発行*/
	}
#else
	SCN_TotalEncodeLine = EncodeLine(SCANNER_CODEC); /** Aug.20,1994 符号化ライン数を保存 */
	SetRTC(SCANNER_CODEC, enc_blk2.CodeType);	/**ページの終わりにRTCをセットする*/
#endif

	EncodeDataCountSet();
	switch (cdc_stat) {
/* #if defined (DEU)	@* 1997/04/25 s.takeuchi */
#if defined (DEU) || defined (FRA) || defined (GBR) || defined (EC1) || defined(EUR)	/* 沖の要求により。By Y.Suzuki 1998/10/13 */
																		/* 欧州仕様追加 by M.H 1999/09/15 */
	case	CDC_DOC_OVER:
		CodecPageStatus = CDC_DOC_OVER;
		break;
#endif
	case	CDC_STOPPED:
		CodecPageStatus = CDC_STOPPED;
		break;
	case	CDC_RTC_DET:
	default:
		CodecPageStatus = CDC_RTC_DET;
		break;
	}
	/*--------------------------*/
	/*	エンコードデータ量更新	*/
	/*--------------------------*/
#if (0)	/* 下記処理ではスキャナ送信でリセットがかかる可能性があるので対策します 1998/03/31 by T.Soneoka */
//	if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
//		/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
//		SaveReturnAddressAndJumpBegin();
//	}
//	GetCodecFlag = NO;
#else
	CMN_DisableInterrupt();
	if (GetCodecFlag == YES) {
		GetCodecFlag = NO;
		if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {
			CMN_EnableInterrupt();
			SaveReturnAddressAndJumpBegin();
		}
	}
	CMN_EnableInterrupt();	/**割り込み許可*/
#endif
	TxStartFlag = 1;
	det_evt(EVT_TX_START);

	/*-----------------------------------*/
	/** スキャナー・ライフ・モニター加算 */
	/*	Dec.20,1994						 */
	/*-----------------------------------*/
	SYB_LifeMonitor.ScanCount++;	/** 読取り枚数加算 */

	wai_tsk(0xFFFF);
}
#endif	/* 1998/06/13 H.Yoshikawa */


/*************************************************************************
	module		:[ECMバッファにキャラクタイメージをエンコードする]
	function	:[
		1.通信コーデックを獲得する
		2.コーデックパラメータを設定する
		3.エンコード開始する
		5.通信コーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
	]
	comment		:[
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1994/3/26]
	author		:[曽根岡拓]
*************************************************************************/
void CDC_CTxCodeConvertPageTask(void)
{
#if (PRO_COM_CODEC_TYPE != SOFTWARE)
	if (!GetCodec(COMMUNICATION_CODEC, CODEC_CHARACTER_TX)) {
		/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
		SaveReturnAddressAndJumpBegin();
	}
	switch (TxSmType) { /* 受領証とカバーページを区別するため８行追加 (For ANZU) By H.Hirao Feb 23.1996 */
	case TX_RCR:/*	ＥＣＭバッファに受領証をセット	*/
		EncodeDataCount = (CDC_SetRCR() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
		break;
	case TX_CVR:/*	ＥＣＭバッファにカバーページをセット	*/
/* 移植 by SMuratec L.Z.W 2003/07/24 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if(PRO_SPECIAL_DOCTOR_REPORT == ENABLE)	/* 医師会特ＲＯＭ By O.Kimoto 1999/04/01 */
if (ROM_SW_SpecialDoctorReport) {
			if (CommandFileTitleMessage == YES) {
				EncodeDataCount = (CDC_SetCoverPage() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
			}
			else {	/* 医師会特ＲＯＭ用メッセージ送信 */
				EncodeDataCount = (CDC_SetEmergencyReport() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
			}
}
else {
			EncodeDataCount = (CDC_SetCoverPage() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
}
 #else
		EncodeDataCount = (CDC_SetCoverPage() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
 #endif
#else
		EncodeDataCount = (CDC_SetCoverPage() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
#endif
		break;
#if (PRO_RELAYED_REPORT == ENABLE) /* H.Kubo 1998/01/17 */
	case TX_RELAYED_TX_REPORT:
		EncodeDataCount = (CDC_SetRelayedTxReport() - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS);
		break;
#endif
	default:
		break;
	}
	/*----------------------*/
	/*	通信コーデック開放	*/
	/*----------------------*/
	if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_CHARACTER_TX)) {
		/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
		SaveReturnAddressAndJumpBegin();
	}
	CodecPageStatus = CDC_RTC_DET;
	TxStartFlag = 1;
	det_evt(EVT_TX_START);
	wai_tsk(0xffff);
#endif
}


/*************************************************************************
	module		:[DRAMからECMバッファに1論理ページ符号変換する]
	function	:[
		1.通信コーデックを獲得する
		2.コーデックパラメータを設定する
		3.RTCを検出するまで符号変換する
		4.RTCをセットする
		5.通信コーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		このタスクをクリエイトする前に,
		DRAMを制御するV53のDMAを起動する事
	]
	comment		:[
		メモリ送信タスクからクリエイトされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1993/12/10]
	author		:[小谷正樹]
*************************************************************************/
#if 0 /* (PRO_COM_CODEC_TYPE == MN86064) */ /* Deleted by H.Kubo 1998/02/17 */
** static	struct CodecCodeConvertParameterBlk_t code_conv_blk;  /* for debug by H.Kubo 1997/12/01 */
#endif
void CDC_MTxCodeConvertPageTask(void)
{
#if (PRO_COM_CODEC_TYPE != SOFTWARE)
	struct CodecCodeConvertParameterBlk_t code_conv_blk;
	UWORD	encode_size;
	UBYTE	encode_kpara;
	UWORD	decode_size;
	UWORD	max_decode_line;
	UBYTE	tti_available;
	UBYTE	tti_inside;
	UWORD	tti_line;		/**TTI Inside時に無効にする画データのライン数*/
	UBYTE	code_convert_flg;
	UBYTE	debugsw;
	UBYTE	cdc_stat;
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	UBYTE	list_tx;
	UDWORD	max_encode_line;
  #if (PRO_JBIG == DISABLE)
	MESSAGE_t    			*CDC_TaskMsg;
  #endif
 #endif
 #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	MESSAGE_t    			*CDC_TaskMsg;
	DEBUG_EncodeCounter = 0;
 #endif
 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	if ((TxSmType == TX_RELAYED_TX_REPORT) && (LST_TxPageFinishStatus != TX_END)) {
		list_tx = TRUE;
	}
	else {
		list_tx = FALSE;
	}
 #endif
	debugsw = 0;
	tti_available = 0;
	tti_line = 0;

 #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	SetClear((UBYTE *)&code_conv_blk, sizeof(struct CodecCodeConvertParameterBlk_t), 0x00);
 #endif

	/*------------------*/
	/*	ＴＴＩ送出処理	*/
	/*------------------*/
 #if (0)	/* 受信原稿ポーリング取り出し修正分 by T.Soneoka 1997/02/21 */
//	tti_available = FCM_PtnrChkTTI_TxAvailable();
 #endif
	if(CHK_UNI_RxDocToPollingDoc()) {
		tti_available = 0;
	}
	else {
 #if (PRO_FCODE_RELAY == ENABLE) /** Ｆコード中継機能 1998/08/21 By H.Hirao */
		tti_available = FCM_FcodeRelayTxTTI_Available();
 #else
		tti_available = FCM_PtnrChkTTI_TxAvailable();
 #endif
	}
/* ここまで */
 #if (PRO_FCODE_RELAY == ENABLE) /** Ｆコード中継機能 1998/08/21 By H.Hirao */
	tti_inside = FCM_FcodeRelayTxTTI_Inside();
 #else
	tti_inside = CHK_UNI_TTI_Inside();	/* USA以外のため 96/05/16 By T.Yamaguchi */
 #endif
	/*----------------------*/
	/*	符号化ページ幅設定	*/
	/*----------------------*/
	encode_size = GetCodecSize(SYS_DocBlock.Dst.Size, SYS_DocBlock.Dst.Mode);
	/*--------------------------*/
	/*	符号化Ｋパラメータ設定	*/
	/*--------------------------*/
	encode_kpara = GetK_Parameter(SYS_DocBlock.Dst.Mode);
	/*----------------------*/
	/*	復号化ページ幅設定	*/
	/*----------------------*/
	decode_size = GetCodecSize(SYS_DocBlock.Src.Size, SYS_DocBlock.Src.Mode);
	/*--------------------------*/
	/*	復号化処理ライン数設定	*/
	/*--------------------------*/
	max_decode_line = GetMaxTxLine(SYS_DocBlock.DocLength);
	/*--------------------------*/
	/*	復号化変化率設定処理	*/
	/*--------------------------*/
	TxPixReductionSet(SYS_DocBlock.Src.Size,
					  SYS_DocBlock.Src.Mode,
					  SYS_DocBlock.Dst.Size,
					  SYS_DocBlock.Dst.Mode,
					  SYS_DocBlock.ModeMethod);
	/*--------------------------*/
	/*	通信コーデックを獲得	*/
	/*--------------------------*/
	if (!GetCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {
		/*begin(); /** 有り得ないけど、とりあえずリセット処理 */
		SaveReturnAddressAndJumpBegin();
	}
	GetCodecFlag = YES;
	/**コーデックパラメータを設定する*/
	/** Kiri用追加パラメータ */
	code_conv_blk.CodecType	   = COMMUNICATION_CODEC;	/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/
	code_conv_blk.SrcCodeType  = SYS_DocBlock.Src.Code;	/**復号化方式 (ex. SYS_MMR_CODE)*/
	code_conv_blk.DestCodeType = SYS_DocBlock.Dst.Code;	/**符号化方式 (ex. SYS_MMR_CODE)*/
	code_conv_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/*------------------------*/
	/** 符号化パラメータ Ch.0 */
	/*------------------------*/
	code_conv_blk.C0_PWDR_Status  = encode_size;		/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
	code_conv_blk.C0_OBXR_Status  = 0;					/**符号化オフセット*/
	code_conv_blk.C0_KPR_Status	  = encode_kpara;		/**符号化Kパラメータ*/
	code_conv_blk.C0_LCONT_Status = 0;					/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/

 #if 0 /* メモリ節約のため、共通コードを関数にまとめました。 Changed by H.Kubo 1998/07/08 */
@@	code_conv_blk.C0_MCLR_Status  = 0;					/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
@@/* 950314 ＥＣＭ送信の時は最小伝送符号バイト数は０にセット	*/
@@	if (TxECM_Mode == ECM_ON) {
@@		code_conv_blk.C0_MCLR_Status  = 0;
@@	}
@@	else {
@@		if (SYS_DocBlock.MSE_Method == MSE1) {
@@			code_conv_blk.C0_MCLR_Status  = 0;
@@		}
@@		else {
@@			code_conv_blk.C0_MCLR_Status  = SYS_DocBlock.MinimumLineSize;	/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
@@		}
@@	}
 #else
	code_conv_blk.C0_MCLR_Status =  CDC_GetCodecEncodeMCLR();
 #endif

	/*-----------------------*/
	/* 復号化パラメータ Ch.0 */
	/*-----------------------*/
	code_conv_blk.D0_PWDR_Status  = decode_size;		/**復号化ページ幅(メモリに蓄積されている1ラインの有効画素数をWordで設定)*/
	code_conv_blk.D0_OBXR_Status  = 0;					/**復号化オフセット*/
	code_conv_blk.D0_RTCR_Status  = 3;					/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	/*----------------------------------------------------------------------*/
	/*	今のところ分割送信がないのでデコードライン数は無限にしておきます	*/
	/*----------------------------------------------------------------------*/
/*	code_conv_blk.D0_BLGR_Status  = max_decode_line;	/**復号化処理ライン数(1回に復号化するライン数)*/
	code_conv_blk.D0_BLGR_Status  = 0xffff;				/**復号化処理ライン数(1回に復号化するライン数)*/
	code_conv_blk.D0_LCONT_Status = 0;					/**復号化ラインカウンタ(復号化したライン数(エラーを含む)がセットされます)*/
	code_conv_blk.D0_ELIN_Status  = 0;					/**復号化エラーライン数(1ページ内のエラーライン数の総数がセットされます)*/
	code_conv_blk.D0_HCONV_Status = 0;					/**復号化主走査方向変換率*/
	code_conv_blk.D0_VCONV_Status = 0;					/**復号化副走査方向変換率*/
	code_conv_blk.D0_LMASK_Status = 0;					/**復号化左側白マスク*/
	code_conv_blk.D0_RMASK_Status = 0;					/**復号化右側白マスク*/

 #if (PRO_COM_CODEC_TYPE == MN86064)
	if (Pix_H_Reduction == 0x400) {
		code_conv_blk.D0_HCONV_Status = 0;	/**符号化副走査方向変換率 100 % */
	}
	else {
		code_conv_blk.D0_HCONV_Status = Pix_H_Reduction | 0x4000;	/**符号化副走査方向変換率 100 % */
	}
	if (Pix_V_Reduction == 0x00) {
		code_conv_blk.D0_VCONV_Status = 0;	/**符号化副走査方向変換率 100%*/
		code_conv_blk.Vmn_Status = 0;	/**副走査:間引き指定 MN86063では無効*/
	}
	else {
		code_conv_blk.D0_VCONV_Status = Pix_V_Reduction / 4;	/**TBD符号化副走査方向変換率*//**MN86064の場合は設定値が1/4です*/
		if (code_conv_blk.D0_VCONV_Status > 0x2000) {
			code_conv_blk.Vmn_Status = 0;	/**コーデックバグ By M.Kotani 1997/11/17*/
		}
		else {
			code_conv_blk.Vmn_Status = 0x8000;	/** 副走査:ラインOR処理 */
		}
	}
 #else
	if ((Pix_H_Reduction == 0x400) && (Pix_V_Reduction == 0x00)) {
		code_conv_blk.D0_HCONV_Status = 0;	/**符号化副走査方向変換率 100 % */
		code_conv_blk.D0_VCONV_Status = 0;	/**TBD符号化副走査方向変換率*/
	}
	else {
		code_conv_blk.D0_HCONV_Status = Pix_H_Reduction | 0x4000;	/**符号化副走査方向変換率 100 % */
		code_conv_blk.D0_VCONV_Status = Pix_V_Reduction;	/**TBD符号化副走査方向変換率*/
	}
 #endif
 #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (code_conv_blk.DestCodeType == SYS_JBIG_CODE) {
  #if (0)	/* 下記メモリＳｗにて設定対応できるように変更 */
//		code_conv_blk.C_QMCR_Status = (VLENGTH_BIT | TPBON_BIT);	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
  #endif
		code_conv_blk.C_QMCR_Status = VLENGTH_BIT;
		if (CHK_UNI_JBIG_2lineTemplate()) {
			code_conv_blk.C_QMCR_Status |= LRLTWO_BIT;
		}
		if (CHK_UNI_JBIG_TPB_Mode()) {
			code_conv_blk.C_QMCR_Status |= TPBON_BIT;
		}
		if (CHK_UNI_JBIG_SDRST()) {
			code_conv_blk.C_QMCR_Status |= SDRST_BIT;
		}
		code_conv_blk.C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
		code_conv_blk.C_Yd_Status = 0xffff;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
		code_conv_blk.C_L0_Status = 128;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
		code_conv_blk.C_Mx_Status = 127;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
		code_conv_blk.D_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
		code_conv_blk.D_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
		code_conv_blk.D_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
		code_conv_blk.D_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
		code_conv_blk.D_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
	}
 #endif
	/**上記のパラメータでコーデックをセットアップする*/
	/*-----------------*/
	/**ＴＴＩセット処理*/
	/*-----------------*/
 #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
  #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	if (list_tx) {
		(void) CDC_SetRelayedTxReport();
		CodecImageByteSwapDisable(code_conv_blk.CodecType);	/**DTCR設定(バイトSwap無効)*/
		CodecCodeConvertCDCR_Setup(code_conv_blk.CodecType);	/**CDCR設定*/
		CodecCodeConvertParameterSetup(&code_conv_blk);	/**パラメータレジスタセット*/
		EnterCodecCommand(code_conv_blk.CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
		tti_inside = 0; /* TTI インサイド処理を飛ばす。 */
	}
	else
  #endif
	if (tti_available) {	/**ＴＴＩを送出するとき*/
		/*----------------------------------*/
		/*	ＥＣＭバッファにＴＴＩをセット	*/
		/*----------------------------------*/
		EcmBufferBaseWritePoint = CDC_SetTTI();
		/*
		** 符号変換の符号化ラインパラメータにTTI符号ライン数をセットします
		** 1998/1/9 by T.Soneoka
		*/
		tti_line = code_conv_blk.C0_LCONT_Status = EncodeLine(COMMUNICATION_CODEC);
		CodecImageByteSwapDisable(code_conv_blk.CodecType);	/**DTCR設定(バイトSwap無効)*/
		CodecCodeConvertCDCR_Setup(code_conv_blk.CodecType);	/**CDCR設定*/
		CodecCodeConvertParameterSetup(&code_conv_blk);	/**パラメータレジスタセット*/
		EnterCodecCommand(code_conv_blk.CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
		ModemMessage.Message = MSG_TTI_COMPLETE;
		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
		if ((debugsw == 1)
		&&  (code_conv_blk.DestCodeType == SYS_JBIG_CODE)) {
			/* RTC/NEWLENコマンドを実行する前に符号化ラインを待避しておきます （このコマンドによってクリアされてしまうため） */
			MDM_EncodeLine = tti_line;
			/* RTC/NEWLENコマンド発行 */
			SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
			EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
			EncodeDataCountSet();
			CodecPageStatus = CDC_RTC_DET;
  #if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性がまだあるので対策します 1998/03/31 by T.Soneoka */
//			CMN_DisableInterrupt(); /* by S.Kawasaki 1996/07/26 */
//			GetCodecFlag = NO; /* by S.Kawasaki 1996/07/26 */
//			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {
//				CMN_EnableInterrupt();
//				SaveReturnAddressAndJumpBegin();
//			}
//			CMN_EnableInterrupt();
  #else
			CMN_DisableInterrupt(); /* by S.Kawasaki 1996/07/26 */
			if (GetCodecFlag == YES) {
				GetCodecFlag = NO; /* by S.Kawasaki 1996/07/26 */
				if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {
					CMN_EnableInterrupt();
					SaveReturnAddressAndJumpBegin();
				}
			}
			CMN_EnableInterrupt();
  #endif
			TxStartFlag = 1;
			det_evt(EVT_TX_START);
			wai_tsk(0xFFFF);
		}
	}
	else {
		/* JBIGの場合は、JBIG初期化コマンドによってBIHを作成するため、先に外部DMAを起動します */
		EcmBufferBaseWritePoint = ECM_BUFFER_AREA_START_ADDRESS;
		ModemMessage.Message = MSG_TTI_COMPLETE;
		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
		CodecCodeConvertSetup(&code_conv_blk);
	}
 #else
	if (tti_available) {	/**ＴＴＩを送出するとき*/
		/*----------------------------------*/
		/*	ＥＣＭバッファにＴＴＩをセット	*/
		/*----------------------------------*/
		EcmBufferBaseWritePoint = CDC_SetTTI();
		/*
		** 符号変換の符号化ラインのパラメータにTTI符号ライン数をセットします
		** 1998/1/9 by T.Soneoka
		*/
		tti_line = code_conv_blk.C0_LCONT_Status = EncodeLine(COMMUNICATION_CODEC);
		CodecImageByteSwapDisable(code_conv_blk.CodecType);	/**DTCR設定(バイトSwap無効)*/
		CodecCodeConvertCDCR_Setup(code_conv_blk.CodecType);	/**CDCR設定*/
		CodecCodeConvertParameterSetup(&code_conv_blk);	/**パラメータレジスタセット*/
		EnterCodecCommand(code_conv_blk.CodecType, CODEC_CMD_DECODE_INIT);	/**初期化(復号化)*/
	}
	else {
		EcmBufferBaseWritePoint = ECM_BUFFER_AREA_START_ADDRESS;
		CodecCodeConvertSetup(&code_conv_blk);
	}
	ModemMessage.Message = MSG_TTI_COMPLETE;
	snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
 #endif

	CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/
	cdc_stat = CDC_CONTINUE;
	CDC_ImageBufferStatus[COMMUNICATION_CODEC] = CDC_NOT_ACCESS;	/**イメージメモリを開放する*/
	code_convert_flg = TRUE;

 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	if (list_tx) {
		cdc_stat = CDC_RTC_DET;
		if (LST_TxPageFinishStatus != TX_END) {
			code_convert_flg = FALSE; 		/* 画データはつけずに RTC をつけて終了 */
		}
		else {
			/* added by H.Kubo 1998/12/18 */
			max_encode_line = SYS_DocBlock.DocLength;
			switch (SYS_DocBlock.Dst.Mode) {
			case SYS_NORMAL:					/**	普通	*/
				break;
			case SYS_FINE:						/**	高画質	*/
			case SYS_GRAY16:					/**	16階調	*/
			case SYS_GRAY16_SEP:				/**	16階調像域分離	*/
			case SYS_GRAY32:					/**	32階調	*/
			case SYS_GRAY32_SEP:				/**	32階調像域分離	*/
			case SYS_GRAY64:					/**	64階調	*/
			case SYS_GRAY64_SEP:				/**	64階調像域分離	*/
				max_encode_line *= 2;			/**	最大ライン数２倍	*/
				break;
			case SYS_SFINE:						/**	超高画質	*/
			case SYS_HFINE:						/**	超高画質	*/
			case SYS_EFINE:
			case SYS_E_HFINE:
				max_encode_line *= 4;			/**	最大ライン数４倍	*/
				break;
			default: /* とりあえず、副走査方向 600DPI 用を入れときます。*/
				max_encode_line *= 6;
			}

			if (MDM_EncodeLine * 2 >= max_encode_line) {
				code_convert_flg = FALSE; 		/* 画データはつけずに RTC をつけて終了 */
			}
			else { /* 蓄積原稿をつける処理。途中まででちょん切る長さを獲得。 */
				if (max_encode_line > MDM_EncodeLine) {
					code_conv_blk.D0_BLGR_Status = CDC_GetDecodeLineFromOutLine(max_encode_line - MDM_EncodeLine);
					SetCodecParameterRegister(COMMUNICATION_CODEC, D0_BLGR_ADR, code_conv_blk.D0_BLGR_Status);	/**復号化処理ライン数(1回に復号化するライン数)*/
					/* 蓄積原稿を読む DMA を起動します。 */
					if (tskno_MTxReadDMA_Task != 0xffff) {
						del_tsk(&tskno_MTxReadDMA_Task);	/**	メモリ送信メモリリードタスク終了	*/
					}
					tskno_MTxReadDMA_Task = 0xffff;
					cre_tsk(&tskno_MTxReadDMA_Task, TSK_MDM_MTXREADDMA_TASK, NULL);	/**	メモリリードＤＭＡ終了監視タスク起動 */
					do {
						rcv_msg(mbxno.MDM_MTxReadDMA_Task, &CDC_TaskMsg);	/**	オープン結果メッセージ受信	*/
					} while (!((CDC_TaskMsg->Message == MEM_OK) ||
					          (CDC_TaskMsg->Message == MEM_NO_INDEX)));
					if (CDC_TaskMsg->Message == MEM_OK) {	/**	メモリリードオープンＮＧの時	*/
						CDC_ReadPageCount = SYS_DocBlock.Index.Page;
					}
					else {
						cdc_stat = CDC_DECODE_ERROR;
						CodecPageStatus = CDC_DECODE_ERROR; /* オープンできなかったら、デコードエラーということにしておきます。 */
						code_convert_flg = FALSE; 		/* 画データはつけずに RTC をつけて終了 */
						/*	メモリ送信メモリリードタスク終了	*/
						if (tskno_MTxReadDMA_Task != 0xffff) {
							del_tsk(&tskno_MTxReadDMA_Task);	/**	メモリ送信メモリリードタスク終了	*/
						}
					}
				}
				else {
					code_conv_blk.D0_BLGR_Status = 0;
					code_convert_flg = FALSE; 		/* 画データはつけずに RTC をつけて終了 */
				}
			}
			
		}
	}
	else if (!list_tx && (TxSmType == TX_RELAYED_TX_REPORT)){
		CDC_ReadPageCount = SYS_DocBlock.Index.Page;
	}
 #endif

	/*---------------------*/
	/**ＴＴＩインサイド処理*/
	/*---------------------*/
	if ((tti_inside != 0) && (tti_available != 0)) {	/**ＴＴＩインサイド時*/
		CodecDecodeCheckCDCR_Setup(COMMUNICATION_CODEC);	/**デコードチェックに切り替える*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_BLGR_ADR, tti_line);	/**復号化処理ライン数(1回に復号化するライン数)*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, OTWORD_ADR, 304);	/** 復号化ページ幅(復号化した結果できる1ラインの画素数) */
		SetCodecParameterRegister(COMMUNICATION_CODEC, O_OBXR_ADR, 0);	/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
		StartDecode(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT){	/* ストップスイッチを押された時 */
			cdc_stat = CDC_STOPPED;
			code_convert_flg = FALSE;
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			cdc_stat = CDC_RTC_DET;
			code_convert_flg = FALSE;	/**RTC検出*/
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			if ((code_conv_blk.SrcCodeType == SYS_MMR_CODE) || (code_conv_blk.SrcCodeType == SYS_MG3_CODE)) {
				if (debugsw == 1) {
 #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
					PC_24V_On();
 #endif
					LampOn();
				}
				cdc_stat = CDC_DECODE_ERROR;
				code_convert_flg = FALSE;	/**デコードエラー*/
 #if (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/12/08 */
				code_conv_blk.D0_LCONT_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR);
 #endif /* (PRO_COM_CODEC_TYPE == MN86064) /* added by H.Kubo 1997/11/26 */
			}
		}
		CodecCodeConvertCDCR_Setup(COMMUNICATION_CODEC);	/**符号変換に切り替える*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_BLGR_ADR, 0xFFFF);	/**復号化処理ライン数(1回に復号化するライン数)*/
	}

	/*-------------------------*/
	/**送出画データ符号変換開始*/
	/*-------------------------*/
 #if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	while (code_convert_flg) { /**画データがあれば1ページ符号変換する*/
		StartCodeConvert(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code, SYS_DocBlock.Dst.Code);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/
		/* JBIGコマンド割り込み */
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
			SetCodecParameterRegister(COMMUNICATION_CODEC, C_QMIR_ADR, 0);	/* QMIRクリア */
			CodecParameterRegister[COMMUNICATION_CODEC].C_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, C_QMIR_ADR);
			Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
		}
		/* コマンド終了時 */
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & CMDE0_BIT) {
			if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
				cdc_stat = CDC_STOPPED;
				break;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {
  #if defined (SAKAKI) /* SAKAKI のデバッグ用に入れます。 by H.Kubo 1998/10/08 */
				if (ReadCodecParameterRegister(COMMUNICATION_CODEC, D0_ELIN_ADR) > 0) {
					cdc_stat = CDC_DECODE_ERROR;
				}
				else {
					cdc_stat = CDC_RTC_DET;
				}
  #else
				cdc_stat = CDC_RTC_DET;
  #endif
				break;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {
				cdc_stat = CDC_DECODE_ERROR;
				break;
			}
			else {
				cdc_stat = CDC_RTC_DET;
				break;
			}
		}
	}
	/* RTC/NEWLENコマンドを実行する前に符号化ラインを待避しておきます （このコマンドによってクリアされてしまうため） */
  #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/20 */
	if (list_tx && (LST_TxPageFinishStatus == TX_END)) { /* 画データがリストの後につく場合 */
		MDM_EncodeLine += EncodeLine(COMMUNICATION_CODEC);
	}
	else {
		MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
	}
  #else
	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
  #endif
	/* RTC/NEWLENコマンド発行 */
	if (code_conv_blk.DestCodeType != SYS_JBIG_CODE) {
		SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**RTCコマンド発行*/
	}
	else {
  #if (0) /* by T.Soneoka 1998/02/13 */
//		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
  #endif
  #if (0) /*  by T.Soneoka 1998/02/26 */
//		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine+1);	/* C-Yd更新 */
  #endif
		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/* C-Yd更新 */
		EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/* NEWLENコマンド発行 */
	}
 #else
	/*-------------------------*/
	/**送出画データ符号変換開始*/
	/*-------------------------*/
	if (code_convert_flg) { /**画データがあれば1ページ符号変換する*/
		CDC_ImageBufferStatus[COMMUNICATION_CODEC]++;		/**コーデックは1回目を開始する*/
		/*----------------------*/
		/*	画データ送出処理	*/
		/*----------------------*/
		StartCodeConvert(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code, SYS_DocBlock.Dst.Code);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			cdc_stat = CDC_STOPPED;
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			cdc_stat = CDC_RTC_DET;
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			if ((code_conv_blk.SrcCodeType == SYS_MMR_CODE) || (code_conv_blk.SrcCodeType == SYS_MG3_CODE)) {
				if (debugsw == 1) {
  #if (PRO_ENERGY_SAVE == ENABLE)		/* 2001/11/30 T.Takagi */
					PC_24V_On();
  #endif
					LampOn();
				}
				cdc_stat = CDC_DECODE_ERROR;
			}
		}
	}
	/*------------------*/
	/*	ＲＴＣセット	*/
	/*------------------*/
	SetRTC(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/**ページの終わりにRTCをセットする*/
 #endif
	/*--------------------------*/
	/*	エンコードデータ量更新	*/
	/*--------------------------*/
	EncodeDataCountSet();

 #if (PRO_LIST_TX_WITH_IMG == ENABLE) /* added by H.Kubo 1998/12/16 */
	/*	メモリ送信メモリリードタスク終了	*/
	if (tskno_MTxReadDMA_Task != 0xffff) {
		del_tsk(&tskno_MTxReadDMA_Task);	/**	メモリ送信メモリリードタスク終了	*/
	}
 #endif

	switch (cdc_stat) {
	case	CDC_STOPPED:
		CodecPageStatus = CDC_STOPPED;
		break;
	case	CDC_DECODE_ERROR:
		CodecPageStatus = CDC_DECODE_ERROR;
		break;
	case	CDC_RTC_DET:
	default:
		CodecPageStatus = CDC_RTC_DET;
		break;
	}

	/*--------------------------*/
	/*	通信コーデックを解放する*/
	/*--------------------------*/
	/*
	** ポーリング原稿送出用のＴＣＦ送出中にポーリング原稿を消去すると
	** リセットに飛ぶ不具合修正
	** 原因：下記GetCodecFlagをReleaseCodecの後で行っていたため、
	** MDMPIXTX.C内のJumpBeginが実行されていた。
	** KIRI,KIRI+共通
	** By S.Kawasaki 1996/07/26
	*/
 #if (0)	/* 下記処理ではメモリ送信でリセットがかかる可能性がまだあるので対策します 1998/03/31 by T.Soneoka */
//	CMN_DisableInterrupt(); /* by S.Kawasaki 1996/07/26 */
//	GetCodecFlag = NO; /* by S.Kawasaki 1996/07/26 */
//	if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {
//		/* begin(); /** 有り得ないけど、とりあえずリセット処理 */
//		CMN_EnableInterrupt(); /* by S.Kawasaki 1996/07/26 */
//		SaveReturnAddressAndJumpBegin();
//	}
//	CMN_EnableInterrupt(); /* by S.Kawasaki 1996/07/26 */
 #else
	CMN_DisableInterrupt(); /* by S.Kawasaki 1996/07/26 */
	if (GetCodecFlag == YES) {
		GetCodecFlag = NO; /* by S.Kawasaki 1996/07/26 */
		if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {
			/* begin(); /** 有り得ないけど、とりあえずリセット処理 */
			CMN_EnableInterrupt(); /* by S.Kawasaki 1996/07/26 */
			SaveReturnAddressAndJumpBegin();
		}
	}
	CMN_EnableInterrupt(); /* by S.Kawasaki 1996/07/26 */
 #endif
	/* GetCodecFlag = NO; by S.Kawasaki 1996/07/26 */
	TxStartFlag = 1;
	det_evt(EVT_TX_START);
	wai_tsk(0xFFFF);
#endif
}


/*************************************************************************
	module		:[モデムバッファからDRAMに1論理ページ符号変換する]
	function	:[
		1.通信コーデックを獲得する
		2.コーデックパラメータを設定する
		3.RTCを検出するまで符号変換する
		4.RTCをセットする
		5.通信コーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		このタスクをクリエイトした後に,V53のDMAを起動する事
	]
	comment		:[
		メモリ受信タスクからクリエイトされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1993/12/10]
	author		:[小谷正樹]
*************************************************************************/
void CDC_MRxCodeConvertPageTask(void)
{
#if (PRO_COM_CODEC_TYPE != SOFTWARE)
	struct CodecCodeConvertParameterBlk_t code_conv_blk;
	UWORD rx_size;
	UWORD dma_counter;
	UBYTE	cdc_stat;
	UBYTE debugsw;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	UBYTE loop;
	UBYTE min_yat0_pos;
	UWORD min_yat0;
	UWORD jbig_err;
	MESSAGE_t    			*CDC_TaskMsg;
#endif

	debugsw = 0;
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	SetClear((UBYTE *)&code_conv_blk, sizeof(struct CodecCodeConvertParameterBlk_t), 0x00);
#endif

	/*------------------------------*/
	/*	通信コーデックを獲得する	*/
	/*------------------------------*/
	if (!GetCodec(COMMUNICATION_CODEC, CODEC_MEMORY_RX)) {
		/* begin(); /** 有り得ないけど、とりあえずリセット処理 */
		SaveReturnAddressAndJumpBegin();
	}

	/*----------------------*/
	/*	符号化ページ幅設定	*/
	/*----------------------*/
	rx_size = GetCodecSize(SYS_DocBlock.Src.Size, SYS_DocBlock.Src.Mode);

	/**コーデックパラメータを設定する*/
	/** Kiri用追加パラメータ */
	code_conv_blk.CodecType	   = COMMUNICATION_CODEC;	/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/
	code_conv_blk.SrcCodeType  = SYS_DocBlock.Src.Code;				/**復号化方式 (ex. SYS_MMR_CODE)*/
	/*
	** ＪＢＩＧ受信・ＴＰＯｎモードの場合は蓄積符号をＭＭＲにする対応 1998/05/01 by T.Soneoka
	** ＭＮ８６０６４で符号変換コマンドＪＢＩＧ－＞ＭＧ３の場合、ＴＰ Ｏｆｆモードではループする
	*/
#if (0)
**	code_conv_blk.DestCodeType = RxMemoryStoreData.Code;				/**符号化方式 (ex. SYS_MMR_CODE)*/
#endif
	code_conv_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/** 符号化パラメータ Ch.0 */
	code_conv_blk.C0_PWDR_Status  = rx_size;				/**符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
	code_conv_blk.C0_OBXR_Status  = 0;						/**符号化オフセット*/
	code_conv_blk.C0_KPR_Status	  = 0;						/**符号化Kパラメータ*/
	code_conv_blk.C0_LCONT_Status = 0;						/**符号化ラインカウンタ(符号化したライン数がここでわかります)*/
	code_conv_blk.C0_MCLR_Status  = 0;						/**符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数)*/
	/** 復号化パラメータ Ch.0 */
	code_conv_blk.D0_PWDR_Status  = rx_size;				/**復号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
	code_conv_blk.D0_OBXR_Status  = 0;						/**復号化オフセット*/
	if (code_conv_blk.SrcCodeType == SYS_MMR_CODE) {
		code_conv_blk.D0_RTCR_Status  = 1;						/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	}
	else {
		code_conv_blk.D0_RTCR_Status  = 3;						/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	}
	code_conv_blk.D0_BLGR_Status  = 0xffff;					/**復号化処理ライン数(1回に復号化するライン数)*/
	code_conv_blk.D0_LCONT_Status = 0;						/**復号化ラインカウンタ(復号化したライン数(エラーを含む)がセットされます)*/
	code_conv_blk.D0_ELIN_Status  = 0;						/**復号化エラーライン数(1ページ内のエラーライン数の総数がセットされます)*/
	if (CHK_UNI_InchMiriConvert() == 0){	/* インチ／ミリ変換しない場合 */
		code_conv_blk.D0_HCONV_Status = 0;						/**復号化主走査方向変換率*/
		code_conv_blk.D0_VCONV_Status = 0;						/**復号化副走査方向変換率*/
	}
	else {
		if (SYS_DocBlock.ModeMethod == SYS_METRIC) {
			code_conv_blk.D0_HCONV_Status = 0;		/** 復号化主走査方向変換率 */
			code_conv_blk.D0_VCONV_Status = 0;		/** 復号化副走査方向変換率 */
		}
		else {	/* インチで受信ミリで蓄積 */
#if (PRO_COM_CODEC_TYPE == MN86064) /* Changed by H.Kubo 1997/12/08 */
			code_conv_blk.D0_HCONV_Status = 0x410;		/**復号化主走査方向変換率	inch -> mili 101.60% */
			code_conv_blk.D0_VCONV_Status = 0x16a;		/**復号化副走査方向変換率	inch -> mili  97.79% */
#else
			code_conv_blk.D0_HCONV_Status = 0x410;		/**復号化主走査方向変換率	inch -> mili 101.60% */
			code_conv_blk.D0_VCONV_Status = 0x5a2;		/**復号化副走査方向変換率	inch -> mili  97.79% */
#endif
		}
	}
	code_conv_blk.D0_LMASK_Status = 0;						/**復号化左側白マスク*/
	code_conv_blk.D0_RMASK_Status = 0;						/**復号化右側白マスク*/

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (SYS_DocBlock.Src.Code == SYS_JBIG_CODE) {
		/*
		** BIHがとれるまで待ちます
		*/
		rcv_msg(mbxno.CDC_Task, &CDC_TaskMsg);

		/* 符号化側をセットします */
		code_conv_blk.C_QMCR_Status = 0;	/*QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
		code_conv_blk.C_QMIRM_Status = 0;	/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
		code_conv_blk.C_Yd_Status = 0;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
		code_conv_blk.C_L0_Status = 0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
		code_conv_blk.C_Mx_Status = 0;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
		/* 復号化側をセットします */
		/* QMｺﾝﾄﾛｰﾙﾚｼﾞｽﾀ*/
		code_conv_blk.D_QMCR_Status = 0;
		if (CDC_JBG_BIH.Options & JBG_BIT_LRLTWO) {	/* ２ラインテンプレートか？ */
			code_conv_blk.D_QMCR_Status |= LRLTWO_BIT;	/**	２ラインテンプレート選択 */
		}
		if (CDC_JBG_BIH.Options & JBG_BIT_VLENGTH) {	/* NEWLEN有効か？ */
			code_conv_blk.D_QMCR_Status |= VLENGTH_BIT;	/**	NEWLENマーカ有効 */
		}
		if (CDC_JBG_BIH.Options & JBG_BIT_TPBON) {	/* TP Onか？ */
			code_conv_blk.D_QMCR_Status |= TPBON_BIT;	/**	TPモード有効 */
		}
		/*QM割り込みﾏｽｸﾚｼﾞｽﾀ*/
#if (0)
//		code_conv_blk.D_QMIRM_Status = (PAGENDM_BIT		/*PAGEENDの割り込みマスク*/
//		                              | DETABTM_BIT		/*DETABTの割り込みマスク*/
//	                                  | DETNWLM_BIT		/*DETNWLの割り込みマスク*/
//	                                  | ATMREQM_BIT		/*ATMREQの割り込みマスク*/
//	                                  | STRPIRM_BIT);	/*STRPIRの割り込みマスク*/
#endif
		/* ＮＥＷＬＥＮ割り込みによるバグ調査のため 1998/03/17 by T.Soneoka */
		if (debugsw == 1) {
			code_conv_blk.D_QMIRM_Status = (PAGENDM_BIT | DETNWLM_BIT);
		}
		else {
			code_conv_blk.D_QMIRM_Status = 0;
		}
		code_conv_blk.D_Yd_Status = CDC_JBG_BIH.YD;	/*1ﾍﾟｰｼﾞ処理ﾗｲﾝ*/
		code_conv_blk.D_L0_Status = CDC_JBG_BIH.L0;	/*ｽﾄﾗｲﾌﾟﾗｲﾝ数*/
		code_conv_blk.D_Mx_Status = CDC_JBG_BIH.MX;	/*ATMOVEの最大許可ｵﾌｾｯﾄ*/
		QBUF0_stat = 0;
		QBUF1_stat = 0;
	}
#endif

	/*
	** ＪＢＩＧ受信・ＴＰＯｎモードの場合は蓄積符号をＭＭＲにする対応 1998/05/01 by T.Soneoka
	** ＭＮ８６０６４で符号変換コマンドＪＢＩＧ－＞ＭＧ３の場合、ＴＰ Ｏｆｆモードではループする
	*/
	/* 上から移動してきました */
	code_conv_blk.DestCodeType = RxMemoryStoreData.Code;				/**符号化方式 (ex. SYS_MMR_CODE)*/


	/**上記のパラメータでコーデックをセットアップする*/
	CodecCodeConvertSetup(&code_conv_blk);
#if (PRO_JBIG == ENABLE)	/*  BIHエラー調査のため by T.Soneoka 1998/03/16 */
	if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
		CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR);
		CodecPageStatus = CDC_DECODE_ERROR;
		CodecMessage.Message = MSG_FROM_CODE_CONVERT_TASK;
		snd_msg(mbxno.MDM_RxEcmControlTask, &CodecMessage);
		wai_tsk(0xFFFF);
	}
#endif
	if (CodecPageStatus == CDC_CONTINUE) {
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR, MDM_RxTotalLine);	/**復号化ﾗｲﾝｶｳﾝﾀ*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_ELIN_ADR, MDM_RxErrorTotalLine);	/**復号化ｴﾗｰﾗｲﾝ数*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, C0_LCONT_ADR, MDM_EncodeLine);	/**符号化ﾗｲﾝｶｳﾝﾀ*/
		CodecRestartFlag = 1;
	}
	CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/
	cdc_stat = CDC_CONTINUE;
	/*--------------------------*/
	/*	受信データ符号変換開始	*/
	/*--------------------------*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	do {
		StartCodeConvert(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code, RxMemoryStoreData.Code);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/

		/* JBIGコマンド割り込み */
		/* Debug用 1998/03/03 by T.Soneoka */
		DebugEncodeLine = ReadCodecParameterRegister(COMMUNICATION_CODEC, C0_LCONT_ADR);
		DebugDecodeLine = ReadCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR);

		if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
			CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR);
			if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETATM_BIT) {	/*ATMOVEマーカの検出（1ストライプ3個以上）*/
				QBUF0_stat = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMBUF0_ADR);		/* QMBUF0リード */
				QBUF1_stat = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMBUF1_ADR);		/* QMBUF1リード */
#if (0)
//				SetCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR, 0);	/* QMIRクリア */
#endif
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & ATMREQ_BIT) {	/*ATMOVEパラメータ（τx，YAT）の書き込み要求*/
				SetCodecParameterRegister(COMMUNICATION_CODEC, (0x00FF & QBUF0_stat), D_TX0_ADR);	/*Tx0設定 */
				SetCodecParameterRegister(COMMUNICATION_CODEC, QBUF1_stat, D_YAT0_ADR);	/*YAT0設定 */
				code_conv_blk.D_QMCR_Status |= AT0ENB_BIT;	/*AT0有効設定 */
#if (0)
//				SetCodecParameterRegister(COMMUNICATION_CODEC, code_conv_blk.D_QMCR_Status, D_QMCR_ADR);
#endif
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETCMT_BIT) {	/*コメントマーカの検出*/
				/* マスクしているので入ってこない */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETNWL_BIT) {	/*NEWLENマーカの検出*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETABT_BIT) {	/*アボートBIDマーカの検出*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETERR_BIT) {	/*エラー検出（ビット1,0参照）*/
				/* ERR0_BIT このビット読む */	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
				/* ERR1_BIT	このビット読む */	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & PAGEND_BIT) {	/*1ページ処理終了*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else {
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			/*  移動 by T.Soneoka 1998/03/04 */
			SetCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR, 0);	/* QMIRクリア */
		}
		/* コマンド終了割り込み */
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & CMDE0_BIT) {
			if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
				cdc_stat = CDC_STOPPED;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {
				cdc_stat = CDC_RTC_DET;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {
				if ((code_conv_blk.SrcCodeType == SYS_MMR_CODE)
				||  (code_conv_blk.SrcCodeType == SYS_MG3_CODE)
				||  (code_conv_blk.SrcCodeType == SYS_JBIG_CODE)) {
					cdc_stat = CDC_DECODE_ERROR;
					if (debugsw == 1) {
						wai_tsk(0xFFFF);
					}
				}
			}
			else {
				cdc_stat = CDC_RTC_DET;
			}
		}
#if (0) /* 1998/03/08 by T.Soneoka */
//		if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
//			cdc_stat = CDC_STOPPED;
//		}
//		else if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {
//			cdc_stat = CDC_RTC_DET;
//		}
//		else if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {
//			if ((code_conv_blk.SrcCodeType == SYS_MMR_CODE)
//			||  (code_conv_blk.SrcCodeType == SYS_MG3_CODE)
//			||  (code_conv_blk.SrcCodeType == SYS_JBIG_CODE)) {
//				cdc_stat = CDC_DECODE_ERROR;
//			}
//		}
#endif
	} while (cdc_stat == CDC_CONTINUE);

	if (RxMemoryStoreData.Code != SYS_JBIG_CODE) {
		MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
		SetRTC(COMMUNICATION_CODEC, RxMemoryStoreData.Code);	/**ページの終わりにRTCをセットする*/
	}
	else {
		MDM_EncodeLine = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_YD_ADR);	/* D-Ydを読みます */
	}

#else
	do {
		StartCodeConvert(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code, RxMemoryStoreData.Code);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT){	/**コマンド終了割り込みでこの変数にセットされている*/
			cdc_stat = CDC_STOPPED;
		}

		if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			cdc_stat = CDC_RTC_DET;
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数にセットされている*/
			/*------------------------------*/
			/*	デコードエラーを検出した時	*/
			/*------------------------------*/
			if ((code_conv_blk.SrcCodeType == SYS_MMR_CODE) || (code_conv_blk.SrcCodeType == SYS_MG3_CODE)) {
				dma_counter = DMA_CheckDMA_Counter(DMA_DRAM_COMCDC_CH);
				cdc_stat = CDC_DECODE_ERROR;
			}
		}
		if (cdc_stat == CDC_CONTINUE) {
			debugsw = 1;
		}
	} while (cdc_stat == CDC_CONTINUE);
	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);
	SetRTC(COMMUNICATION_CODEC, RxMemoryStoreData.Code);	/**ページの終わりにRTCをセットする*/
#endif
/* 950201 r.3.3 debug */
	switch (cdc_stat) {
	case CDC_DECODE_ERROR:
		CodecPageStatus = CDC_DECODE_ERROR;
		break;
	case CDC_RTC_DET:
	case CDC_STOPPED:
	default:
		CodecPageStatus = CDC_RTC_DET;
		break;
	}
	CodecMessage.Message = MSG_FROM_CODE_CONVERT_TASK;
	snd_msg(mbxno.MDM_RxEcmControlTask, &CodecMessage);
	wai_tsk(0xFFFF);
#endif
}


/*************************************************************************
	module		:[1ページプリンタにデータ転送する]
	function	:[
		1.プリンタコーデックを獲得する
		2.コーデックパラメータを設定する
		3.大域変数にセットされたライン数、データ転送を繰り返す
		4.プリンタコーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		V53のDMAを起動した後,このタスクをクリエイトする事
	]
	comment		:[
		リストプリントからクリエイトされる
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1994/06/07]
	author		:[小谷正樹]
*************************************************************************/
void CDC_DataTransferPageTask(void)
{
#if (PRO_PRN_CODEC_TYPE == MN86063) || (PRO_PRN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
	struct CodecDataTransferParameterBlk_t data_trans_blk;
	struct CodecDMA_TransferParameterBlk_t dma_blk;
	UBYTE printer; /**プリンタ起動用*/
	UWORD line_word;	/**１ラインの画素数（単位はワード）*/
#if (PRO_PRINT_TYPE == LED)
	UWORD dec_start_pointer;
	UWORD dma_start_pointer;
	UBYTE cassette_pos;
	UBYTE adjust;
#endif

	line_word = 0;	/*初期化*/

	/**プリンタコーデックの復号化&DMA転送のパラメータを設定する*/
	/** Kiri用追加パラメータ */
	data_trans_blk.CodecType = dma_blk.CodecType			= PRINTER_CODEC;	/**データ転送に使用するコーデックID (ex. SCANNER_CODEC)*/
	/** 入出力パラメータ */
#if (PRO_PRINT_TYPE == LED)/* V851 原稿付きﾁｪｯｸﾒｯｾｰｼﾞｺﾞﾐ対策(QAT基板でﾁｪｯｸﾒｯｾｰｼﾞﾌﾟﾘﾝﾄでｷｬﾗｸﾀﾌﾟﾘﾝﾄと画像の境目にｺﾞﾐが出た。) By Y.Suzuki 2002/10/01 */
 #if defined(POPLAR_H) && defined(JP0)
	if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_LIST_PRINT) {
		data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status	= 304;				/**フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	}
	else {
		data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status	= LST_WORD_WIDTH;	/**フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	}
 #else
	data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status	= 304;				/**フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
 #endif
#else
	data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status	= 304;				/**フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
#endif
#if (0)/* V851 原稿付きﾁｪｯｸﾒｯｾｰｼﾞｺﾞﾐ対策 By Y.Suzuki 2002/10/01 */
//	data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status	= 304;				/**フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
#endif
	data_trans_blk.O_OBXR_Status							= 0;				/**入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
	data_trans_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/** 符号化パラメータ Ch.0 */
	data_trans_blk.C0_MTOPA_Status = 0;			/**(未使用)符号化イメージバッファ先頭アドレス*/
	data_trans_blk.C0_MENDA_Status = 0;			/**(未使用)符号化イメージバッファ最終アドレス*/
	/** 復号化パラメータ Ch.0 */
	data_trans_blk.D0_MTOPA_Status = dma_blk.T1_MTOPA_Status = 0;	/**復号化イメージバッファ先頭アドレス*/	/** DMA転送バッファ先頭アドレス*/
#if (PRO_PRINTER == DPI600)
	data_trans_blk.INLINE_Status = dma_blk.T1_BLGR_Status	= CDC_LIST_PRINT_LINE_COUNT;		/**入力ライン数(1回に転送するライン数), DMA転送ライン数*/
	data_trans_blk.D0_MENDA_Status = dma_blk.T1_MENDA_Status = 0xF700;/*デバッグ一時的*/
#elif (PRO_PRINTER == DPI200)
	data_trans_blk.INLINE_Status = dma_blk.T1_BLGR_Status	= CDC_LIST_PRINT_LINE_COUNT;		/**入力ライン数(1回に転送するライン数), DMA転送ライン数*/
	data_trans_blk.D0_MENDA_Status = dma_blk.T1_MENDA_Status = 0xF700;/*デバッグ一時的*/
#else
	data_trans_blk.INLINE_Status = dma_blk.T1_BLGR_Status	= PRN_FROM_CODEC_LINECOUNT;		/**入力ライン数(1回に転送するライン数), DMA転送ライン数*/
	data_trans_blk.D0_MENDA_Status = dma_blk.T1_MENDA_Status = 0xFE20;	/**復号化イメージバッファ最終アドレス*/	/** DMA転送バッファ最終アドレス*/
#endif
	/** データ転送パラメータ */
	data_trans_blk.B_STRA0_Status = 0;			/**(未使用)データ転送先頭アドレス0*/
	data_trans_blk.B_STRA1_Status = 0;			/**データ転送先頭アドレス1(プリンタイメージバッファへの転送開始アドレス)*/
	data_trans_blk.B_VCONV_Status = 0;			/**データ転送副走査方向変換率 (等倍 ※G.Aにて４倍拡大)*/
	data_trans_blk.B_LMASK_Status = 0;			/**データ転送左側白マスク*/
	data_trans_blk.B_RMASK_Status = 0;			/**データ転送右側白マスク*/
	dma_blk.Channel	  = 1;						/** 使用するチャンネル (0 or 1)*/
	/** DMA転送パラメータ (CODEC MEMORY <- CUSTOM ･･･ 使用せず) */
	dma_blk.T0_STRA_Status	= 0;						/** DMA転送先頭アドレスポインタ*/
	dma_blk.T0_WORD_Status	= 0;						/** DMA転送ワード数（１ラインのワード数）*/
	dma_blk.T0_BLGR_Status	= 0;						/** DMA転送ライン数*/
	dma_blk.T0_MTOPA_Status	= 0;						/** DMA転送バッファ先頭アドレス*/
	dma_blk.T0_MENDA_Status	= 0;						/** DMA転送バッファ最終アドレス*/
	/** DMA転送パラメータ (CODEC MEMORY -> CUSTOM) */
	dma_blk.T1_STRA_Status	= 0;					/** DMA転送先頭アドレスポインタ*/

#if (PRO_PRINT_TYPE == LASER)
	if ( SYS_DocumentPrintItem == LST_PATTERN_PRINT) {	/**テストプリントのとき*/
		data_trans_blk.B_HCONV_Status							= 0;		/**データ転送主走査方向変換率 (等倍)*/
		data_trans_blk.I_OBXR_Status							= 0;		/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
		data_trans_blk.INWORD_Status							= 304;		/**入力ワード数(SRAM上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		switch (SelectedPaper) {	/**記録紙の幅にしたがって1ラインのDMA転送量を設定する*/
		case SYS_A4_PAPER:
		case SYS_A5_PAPER:
		case SYS_LT_PAPER:
		case SYS_LG_PAPER:
		case SYS_F4_PAPER:		/* 1998/01/08 Y.Murata */
			data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status	= LST_A4_WORD_WIDTH;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		case SYS_B4_PAPER:
		case SYS_B5_PAPER:
			data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status	= LST_B4_WORD_WIDTH;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		case SYS_A3_PAPER:
		case SYS_A4R_PAPER:
		case SYS_LTR_PAPER:
			data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status	= LST_A3_WORD_WIDTH;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		default:
			data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status	= LST_A4_WORD_WIDTH;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		}
	}
	else {	/**リストプリントのとき*/
		data_trans_blk.INWORD_Status = 40;		/**入力ワード数(SRAM上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		if (LST_Reduction == 50) {	/**50%縮小*/
 #if (PRO_PRINTER == DPI600)
			/* data_trans_blk.B_HCONV_Status = 0x2003; For ANZU By S.K Feb.2,1996 */	/**データ転送主走査方向変換率 (３倍拡大)*/
			data_trans_blk.B_HCONV_Status = 0x2001; /* For ANZU By S.K Feb.2,1996 */	/**データ転送主走査方向変換率 (1倍拡大)*/
 #endif
		}
		else {	/**100%*/
 #if (PRO_PRINTER == DPI600)
			/* data_trans_blk.B_HCONV_Status = 0x2006; For ANZU By S.K Feb.2,1996 */	/**データ転送主走査方向変換率 (６倍拡大)*/
			data_trans_blk.B_HCONV_Status = 0x2002;	/**データ転送主走査方向変換率 (2倍拡大)*/
 #endif
		}
		switch (SelectedPaper) {	/**記録紙の幅にしたがって左余白を設ける*/
		case SYS_A4_PAPER:	/* A4とLTの左余白を区別する為に追加 By H.Hirao 1996/05/06 */
		case SYS_A5_PAPER:
		case SYS_LT_PAPER:
		case SYS_LG_PAPER:
		case SYS_F4_PAPER:		/* 1998/01/08 Y.Murata */
			data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_A4;	/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
			line_word = 216;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		case SYS_B4_PAPER:
		case SYS_B5_PAPER:
			data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_B4;	/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
			line_word = 256;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		case SYS_A3_PAPER:
		case SYS_A4R_PAPER:
		case SYS_LTR_PAPER:
			data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_A3;	/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
			line_word = 304;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		default:
			data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_A3;	/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
			line_word = 304;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
			break;
		}
		data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status = line_word / 2;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
	}
#endif
#if (PRO_PRINT_TYPE == LED)

	if ( SYS_DocumentPrintItem == LST_PATTERN_PRINT) {	/**テストプリントのとき*/
		data_trans_blk.B_HCONV_Status							= 0;		/**データ転送主走査方向変換率 (等倍)*/
		data_trans_blk.I_OBXR_Status							= 0;		/**縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット)*/
/*		data_trans_blk.I_OBXR_Status = 3;	@**縮小処理後の入力オフセット(縮小処理後のライン先頭アドレスから有効画素までのオフセット)*/
		/**入力ワード数(SRAM上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		data_trans_blk.INWORD_Status = LST_WORD_WIDTH;
		data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status = LST_WORD_WIDTH;
	}
	else {	/**リストプリントのとき*/
		data_trans_blk.INWORD_Status = 40;		/**入力ワード数(SRAM上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		if (LST_Reduction == 50) {	/**50%縮小*/
 #if (PRO_PRINTER == DPI200)
			data_trans_blk.B_HCONV_Status = 0x2001;		/**データ転送主走査方向変換率 (１倍拡大)*/
 #endif
 #if (PRO_PRINTER == DPI400)
			data_trans_blk.B_HCONV_Status = 0x2002;		/**データ転送主走査方向変換率 (２倍拡大)*/
 #endif
		}
		else {	/**100%*/
 #if (PRO_PRINTER == DPI200)
			data_trans_blk.B_HCONV_Status = 0x2002;		/**データ転送主走査方向変換率 (２倍拡大)*/
 #endif
 #if (PRO_PRINTER == DPI400)
			if (CHK_UNI_ListFormat3x3()) {
				data_trans_blk.B_HCONV_Status = 0x2003;		/**データ転送主走査方向変換率 (３倍拡大)*/
			}
			else {
				data_trans_blk.B_HCONV_Status = 0x2004;		/**データ転送主走査方向変換率 (４倍拡大)*/
			}
 #endif
		}
		if (LST_Reduction == 50) {	/**50%縮小*/
			data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_50;	/**縮小処理後の入力オフセット(縮小処理後のライン先頭アドレスから有効画素までのオフセット)*/
		}
		else {
			if (CHK_UNI_ListFormat3x3()) {
				data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_75;	/**縮小処理後の入力オフセット(縮小処理後のライン先頭アドレスから有効画素までのオフセット)*/
			}
			else {
				data_trans_blk.I_OBXR_Status = LST_LEFT_WHITE_100;	/**縮小処理後の入力オフセット(縮小処理後のライン先頭アドレスから有効画素までのオフセット)*/
			}
		}
 #if (PRO_PRINTER == DPI200)
		data_trans_blk.I_OBXR_Status /= 2;
 #endif
		data_trans_blk.OTWORD_Status = dma_blk.T1_WORD_Status = LST_WORD_WIDTH;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
	}

	/*--------------------------------------------------------------------
	** カセットの中心ずれ対策
	** １ｍｍ×３＝±１．０ｍｍ
	*/
	cassette_pos = PRN_GetCassetteAdjustPosition(SelectedCassette);
	adjust = (SYB_MachineParameter[cassette_pos] & 0x7f);
	if (adjust > 20) {	/* <- 3 By M.Tachibana 1998/02/19 */
		adjust = 20;
	}
	adjust *= 2;
	if (SYB_MachineParameter[cassette_pos] & 0x80) {	/** マイナス */
		dma_blk.T1_STRA_Status	+= adjust;			/** DMA転送先頭アドレスポインタ*/
		dma_blk.T1_MTOPA_Status += adjust;			/**復号化イメージバッファ先頭アドレス*/	/** DMA転送バッファ先頭アドレス*/
		dma_blk.T1_MENDA_Status += adjust;			/**復号化イメージバッファ最終アドレス*/	/** DMA転送バッファ最終アドレス*/
	}
	else {
		adjust /= 2;
		data_trans_blk.I_OBXR_Status += adjust;	/* 200dpiの時、気を付ける */
	}

#endif

	/**上記のパラメータでコーデックをセットアップする*/
	CodecDataTransferSetup(&data_trans_blk);	/*上記のパラメータであるようにデータ転送するようにセットアップされる*/
	CDC1_DMA1_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
	CodecDMA_TransferSetup(&dma_blk);			/*上記のパラメータにあるようにプリンタにＤＭＡ転送するようにセットアップされる*/
	printer = FALSE;
	CDC_ImageBufferStatus[PRINTER_CODEC] = CDC_NOT_ACCESS;	/**イメージメモリを開放する*/
	while (1) { /**1ページデータ転送するまでループする*/
		CDC_ImageBufferStatus[PRINTER_CODEC]++;	/**コーデックはデータ転送を開始する*/
		EnterCodecCommand(PRINTER_CODEC, CODEC_CMD_DATA_TRANSFER);	/**PBR:INLINEに設定したライン数を連続してデータ転送する*//*※データ転送するまでリターンしない*/
		if (CDC_CheckAccept(PRINTER_CODEC)) {	/*Add By M.Kotani 1998/01/30*/
			break;	/**アボート検出*/
		}
		if (printer) { /**プリンタが起動されている時*/
			CMN_DisableInterrupt();	/**割り込み禁止*/
			if (!CDC1_DMA1_EndFlag) {	/**DMA未終了のとき*/
				wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ53LinesのDMA終了を待つ*/
			}
			else {
				DEBUG_DataTrans++;	/* By M.Tachibana 1997/07/22 */
			}
			CDC1_DMA1_EndFlag = 0;
			CMN_EnableInterrupt();	/**割り込み許可*/
			/**次のＤＭＡの起動は割り込みルーチンの中で処理する*/
		}
		else {
			printer = TRUE;
			PRN_StartImagePrint();	/**プリンタを起動する*/
		}
	}
	wai_tsk(0xFFFF);
#endif	/* 1998/06/10 H.Yoshikawa */
}

/*************************************************************************
	module		:[ジャーナルデータを1ページ復号化する]
	function	:[
		1.プリンタコーデックを獲得する
		2.コーデックパラメータを設定する
		3.RTCを検出するまで復号化する
		4.プリンタを起動する
		5.プリンタコーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		このタスクをクリエイトする前に,V53のDMAを起動する事
	]
	comment		:[
		ジャーナルプリントタスクからクリエイトされ
		, 複数プリント時はこのタスクがくり返し起動される
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1994/08/26]
	author		:[小谷正樹]
*************************************************************************/
void CDC_DecodeJournalPageTask(void)
{
#if (PRO_PAT_JOURNAL == ENABLE)
	struct CodecDecodeParameterBlk_t dec_blk;
	struct CodecDMA_TransferParameterBlk_t dma_blk;
	UBYTE printer; /**プリンタ起動用*/
	UBYTE loop_flg;
	UWORD line_word;	/**１ラインの画素数（単位はワード）*/

	line_word = 0;	/*初期化*/

	/**プリンタコーデックの復号化&DMA転送のパラメータを設定する*/
		/** Kiri用追加パラメータ */
	dec_blk.CodecType = dma_blk.CodecType			= PRINTER_CODEC;	/** 復号化&DMA転送に使用するコーデックID (ex. SCANNER_CODEC)*/
	dec_blk.CodeType								= SYS_MH_CODE;		/** 復号化方式 */
		/** 入出力パラメータ */
	dec_blk.FRWORD_Status = dma_blk.FRWORD_Status	= 304;				/** フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	dec_blk.O_OBXR_Status							= 0;				/** 出力オフセット(左寄せ 左データカット)*/
	dec_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/
	/** 復号化パラメータ Ch.0 */
	dec_blk.D0_STRA_Status	= dma_blk.T1_STRA_Status	= 0;		/** 復号化ライン先頭アドレス(プリンタイメージバッファの符号化開始アドレス) & DMA転送先頭アドレスポインタ*/
	dec_blk.D0_PWDR_Status	= 1280/16;								/** 復号化ページ幅(復号化する1ラインの画素数をWordで設定) */
	dec_blk.D0_RTCR_Status	= 2;									/** 復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	dec_blk.D0_BLGR_Status	= dma_blk.T1_BLGR_Status	= 16;		/** 復号化処理ライン数(1回に復号化するライン数)&DMA転送ライン数*/
	dec_blk.D0_LCONT_Status	= 0;									/** 復号化ラインカウンタ(復号化したライン数(エラーを含む)がセットされます)*/
	dec_blk.D0_ELIN_Status	= 0;									/** 復号化エラーライン数(1ページ内のエラーライン数の総数がセットされます)*/
	if (LST_Reduction == 50) {	/**50%縮小*/
		dec_blk.D0_HCONV_Status = 0;								/** 復号化主走査方向変換率 (等倍)*/
	}
	else {	/**100%*/
		/* dec_blk.D0_HCONV_Status = 0x2002; */							/** 復号化主走査方向変換率 (２倍拡大)*/
		dec_blk.D0_HCONV_Status = 0;								/** For ANZU MHｴﾝｺｰﾄﾞで2倍しているので、復号化主走査方向変換率 (等倍) 96/02/13 H.Hirao */
	}
	dec_blk.D0_VCONV_Status = 0;									/** 復号化副走査方向変換率 (等倍 ※G.Aにて４倍拡大)*/
	dec_blk.D0_LMASK_Status	= 0;									/** 復号化左側白マスク*/
	dec_blk.D0_RMASK_Status	= 0;									/** 復号化右側白マスク*/
	dec_blk.D0_MTOPA_Status	= dma_blk.T1_MTOPA_Status	= 0;		/** 復号化イメージバッファ先頭アドレス & DMA転送バッファ先頭アドレス*/
	dec_blk.D0_MENDA_Status	= dma_blk.T1_MENDA_Status	= 0xFE20;	/** 復号化イメージバッファ最終アドレス & DMA転送バッファ最終アドレス 0x260*0x6b=0xfe20*/
	/**プリンタコーデックのDMA転送のパラメータを設定する*/
		/** Kiri用追加パラメータ */
	dma_blk.Channel	  = 1;				/** 使用するチャンネル (0 or 1)*/
		/** DMA転送パラメータ (CODEC MEMORY <- CUSTOM ･･･ 使用せず) */
	dma_blk.T0_STRA_Status	= 0;							/** DMA転送先頭アドレスポインタ*/
	dma_blk.T0_WORD_Status	= 0;							/** DMA転送ワード数（１ラインのワード数）*/
	dma_blk.T0_BLGR_Status	= 0;							/** DMA転送ライン数*/
	dma_blk.T0_MTOPA_Status	= 0;							/** DMA転送バッファ先頭アドレス*/
	dma_blk.T0_MENDA_Status	= 0;							/** DMA転送バッファ最終アドレス*/
		/** DMA転送パラメータ (CODEC MEMORY -> CUSTOM) */
	switch (SelectedPaper) {	/**記録紙の幅にしたがって左余白を設ける*/
	case SYS_A4_PAPER:	/* A4とLTの左余白を区別する為に追加 By H.Hirao 1996/05/06 */
	case SYS_A5_PAPER:
	case SYS_F4_PAPER:		/* 1998/01/08 Y.Murata */
#if (PRO_PRINTER == DPI400)
		dec_blk.D0_OBXR_Status = 0;	/** 復号化オフセット(右寄せ 左白付け)*/
#endif
#if (PRO_PRINTER == DPI600)
		dec_blk.D0_OBXR_Status = 10;	/** 杏 (4848画素-(80文字×8ﾋﾞｯﾄ×6倍拡大)画素)÷2÷(GA_H_Reduvtion)÷16ﾋﾞｯﾄ=11.9ﾜｰﾄﾞ By H.Hirao 1996/05/06 */
#endif
		line_word = 216;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		break;
	case SYS_LT_PAPER:
	case SYS_LG_PAPER:
#if (PRO_PRINTER == DPI400)
		dec_blk.D0_OBXR_Status = 0;	/** 復号化オフセット(右寄せ 左白付け)*/
#endif
#if (PRO_PRINTER == DPI600)
		dec_blk.D0_OBXR_Status = 12;	/** 杏 (4990画素-(80文字×8ﾋﾞｯﾄ×6倍拡大)画素)÷2÷(GA_H_Reduvtion)÷16ﾋﾞｯﾄ=11.9ﾜｰﾄﾞ By H.Hirao 1996/05/06 */
#endif
		line_word = 216;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		break;
	case SYS_B4_PAPER:
	case SYS_B5_PAPER:
		dec_blk.D0_OBXR_Status = 0;	/** 復号化オフセット(右寄せ 左白付け)*/
		line_word = 256;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		break;
	case SYS_A3_PAPER:
	case SYS_A4R_PAPER:
	case SYS_LTR_PAPER:
		dec_blk.D0_OBXR_Status = 0;	/** 復号化オフセット(右寄せ 左白付け)*/
		line_word = 304;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		break;
	default:
		dec_blk.D0_OBXR_Status = 0;					/** 復号化オフセット(右寄せ 左白付け)*/
		line_word = 304;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
		break;
	}
#if (PRO_CCD == DPI400)
		dec_blk.OTWORD_Status = dma_blk.T1_WORD_Status	= line_word;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
#endif
#if (PRO_CCD == DPI200)
		dec_blk.OTWORD_Status = dma_blk.T1_WORD_Status	= line_word / 2;	/**出力ワード数,DMA転送ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(ex. A4_SIZE=1728bit=108word))*/
#endif
	/**上記のパラメータでコーデックをセットアップする*/
	CodecDecodeSetup(&dec_blk);
	CodecDMA_TransferParameterSetup(&dma_blk);	/**パラメータレジスタセット*/
	CodecDMCR_DMIR_Status[dma_blk.CodecType] |= MBEND0_BIT;	/**0x0002 DBEND0マスク(0:割り込みマスク, 1:割り込み許可)*/
	CodecDMCR_DMIR_Status[dma_blk.CodecType] |= MBEND1_BIT;	/**0x0020 DBEND1マスク(0:割り込みマスク, 1:割り込み許可)*/
	outpw(CodecRegisterAddressTable[dma_blk.CodecType][CODEC_DMCR_DMIR],
		  CodecDMCR_DMIR_Status[dma_blk.CodecType]);
	printer = FALSE;
	loop_flg = TRUE;
	CDC_ImageBufferStatus[PRINTER_CODEC] = CDC_NOT_ACCESS;	/**イメージメモリを開放する*/
	CDC1_DMA1_EndFlag = 0;
	while (loop_flg) { /**1ページ復号化するまでループする*/
		CDC_ImageBufferStatus[PRINTER_CODEC]++;		/**コーデックは1回目の復号化を開始する*/
		StartDecode(PRINTER_CODEC, dec_blk.CodeType);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する ※復号化するまでリターンしない*/
		if (CodecSTIR_Status[PRINTER_CODEC] & RTCDT0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			loop_flg = FALSE;	/**RTC検出*/
		}
		if (CodecSTIR_Status[PRINTER_CODEC] & DERR0_BIT) {	/**コマンド終了割り込みでこの変数に終了状態がセットされている*/
			if ((dec_blk.CodeType == SYS_MMR_CODE) || (dec_blk.CodeType == SYS_MG3_CODE)) {	/**MMR or MG3の時*/
				loop_flg = FALSE;	/**デコードエラーで復元不可能*/
			}
		}
		if (printer) { /**プリンタが起動されている時*/
			CMN_DisableInterrupt();	/**割り込み禁止*/
			if (!CDC1_DMA1_EndFlag) {	/**DMA未終了のとき*/
				wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ53LinesのDMA終了を待つ*/
			}
			CDC1_DMA1_EndFlag = 0;
			CMN_EnableInterrupt();	/**割り込み許可*/
			/**次のＤＭＡの起動は割り込みルーチンの中で処理する*/
		}
		else {
			printer = TRUE;
			CodecDMA_Enable(dma_blk.CodecType, dma_blk.Channel);
			PRN_StartImagePrint();	/**プリンタを起動する*/
		}
	}
	wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ32LinesのDMA終了を待つ*/
	/*ここでデコードしたすべてのデータはプリンターに転送したのじゃ！ (^m^;)*/
	wai_tsk(0xFFFF);
#endif
}

#if (PRO_PC_PRINT == ENABLE)	/* By J.Miyazaki 1996/09/26 */
/*************************************************************************
	module		:[1論理ページ(イメージデータ）を転送する]
	function	:[
		1.プリンタコーデックを獲得する
		2.コーデックパラメータを設定する
		3.RTCを検出するまで復号化する
		4.プリンタを起動する
		5.プリンタコーデックを解放する
	]
	return		:[なし]
	common		:[]
	condition	:[
		このタスクをクリエイトする前に,V53のDMAを起動する事
	]
	comment		:[
		1.ＰＣプリント時しかコールされない。
		2.CDC_DecodePageTask()よりコールされる。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/09/26]
	author		:[宮崎]
*************************************************************************/
void CDC_PcPrintDataTransfer(struct PrintQueueData_t *prt_queue)
{
	struct CodecDataTransferParameterBlk_t data_trans_blk;
	struct CodecDMA_TransferParameterBlk_t dma_blk;
	UBYTE printer; /**プリンタ起動用*/
	UBYTE print_mode;
	UWORD	prn_codec_limit; /* S.Kawasaki 1996/05/13 */
#if (PRO_PRINT_TYPE == LED)
	UWORD dec_start_pointer;
	UWORD dma_start_pointer;
	UBYTE cassette_pos;
	UBYTE adjust;
	UBYTE prn_form;
#endif


#if (PRO_CPU == SH7043) /* コーデックデバッグ T.Nose 1996/07/15 */
	for (DEBUG_DMA_Counter = 0; DEBUG_DMA_Counter < 30; DEBUG_DMA_Counter++) {
		DEBUG_AddressBuffer[DEBUG_DMA_Counter][0] = 0;
		DEBUG_AddressBuffer[DEBUG_DMA_Counter][1] = 0;
	}
	DEBUG_DMA_Counter = 0;
	DEBUG_EncodeCounter = 0;
#endif

	prn_codec_limit = 4864; /* 1996/05/13 */
	prn_codec_limit = 4992; /* 1996/05/22 */
	prn_codec_limit = 4864; /* 1996/05/27 */
	prn_codec_limit = 5184; /* 1996/05/27 */

	switch (MEM_IndexTable[prt_queue -> Index[PRN_CompPageNo].IndexNo].Mode) {
	case SYS_NORMAL:
		print_mode = PRN_NORMAL;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction; /* By S.Kawasaki 1996/05/10 */
		PRN_PrintDataOffset /=GA_H_Reduction; /* S.Kawasaki 1996/05/10 */
#endif
		break;
	case SYS_FINE:
	case SYS_GRAY16:
	case SYS_GRAY16_SEP:
	case SYS_GRAY32:
	case SYS_GRAY32_SEP:
	case SYS_GRAY64:
	case SYS_GRAY64_SEP:
		print_mode = PRN_FINE;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction; /* By S.Kawasaki 1996/04/05 */
		PRN_PrintDataOffset /=GA_H_Reduction; /* S.Kawasaki 1996/05/10 */
#endif
		break;
	case SYS_SFINE:
		print_mode = PRN_SFINE;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction; /* By S.Kawasaki 1996/04/05 */
		PRN_PrintDataOffset /=GA_H_Reduction; /* S.Kawasaki 1996/05/10 */
#endif
		break;
	case SYS_HFINE:
		print_mode = PRN_HFINE;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction; /* By S.Kawasaki 1996/04/05 */
		PRN_PrintDataOffset /=GA_H_Reduction; /* S.Kawasaki 1996/05/10 */
#endif
		break;
	/*
	** ３００×３００／６００×６００モードを追加
	** By S.Kawasaki 1996/06/14
	*/
	case SYS_EFINE:
		print_mode = PRN_EFINE;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction;
		PRN_PrintDataOffset /=GA_H_Reduction;
#endif
		break;
	case SYS_UFINE:
		print_mode = PRN_UFINE;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction;
		PRN_PrintDataOffset /=GA_H_Reduction;
#endif
		break;
	default:
		print_mode = PRN_NORMAL;
#if (PRO_PRINT_TYPE == LASER)
		PRN_CodecLeftMargine /= GA_H_Reduction;
		PRN_PrintDataOffset /=GA_H_Reduction;
#endif
		break;
	}


#if (PRO_PRINT_TYPE == LASER)
	if (SYS_DocumentPrintItem == SYS_MEM_PC_RX_FILE) { /** プリントがＰＣプリントの場合 */
		if ((print_mode == PRN_EFINE) || (print_mode == PRN_UFINE)) {
			if (GA_H_Reduction == 1) {
				prn_codec_limit = 4848;
			}
			else {
				prn_codec_limit = 4992;
			}
		}
	}
	else {	/** プリントがＰＣプリント以外の場合 */
		/*
		** ＳＦＩＮＥでの１００％以外印字時に副走査が倍になる為の修正
		** 1996/06/06
		** ３００×３００／６００×６００モード追加
		** 1996/06/14
		*/
		/* if (print_mode == PRN_HFINE) { @* S.Kawasaki 1996/05/27 */
		/* if ((print_mode == PRN_HFINE)||(print_mode == PRN_SFINE)) { @* S.Kawasaki 1996/06/06 */
		if ((print_mode == PRN_HFINE)||(print_mode == PRN_SFINE)||(print_mode == PRN_EFINE)||(print_mode == PRN_UFINE)) { /* S.Kawasaki 1996/06/14 */
			if (GA_H_Reduction == 1) {
				prn_codec_limit = 4864; /* 1996/05/13 */
				/* prn_codec_limit = 4992; @* 1996/05/27 */
			}
			else {
				prn_codec_limit = 4992; /* 1996/05/27 */
			}
		}
	}
#endif

	/**プリンタコーデックの復号化&DMA転送のパラメータを設定する*/
	data_trans_blk.CodecType = dma_blk.CodecType			= PRINTER_CODEC;		/** 復号化&DMA転送に使用するコーデックID (ex. SCANNER_CODEC)*/

#if (PRO_PRINT_TYPE == LASER)
	/** 入出力パラメータ */
	data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status = 304;	/** フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	data_trans_blk.O_OBXR_Status = (UBYTE)(PRN_PrintDataOffset / 16);	/** コーデック出力オフセット */
	data_trans_blk.I_OBXR_Status = 0;											/** 縮小処理後のコーデック入力オフセット */
	data_trans_blk.OTWORD_Status = (UWORD)(prn_codec_limit /(16*GA_H_Reduction));/** 転送データ1ラインの画素数) */
	data_trans_blk.OTWORD_Status += 1;
	data_trans_blk.Vmn_Status = 0;	/**副走査:間引き/OR指定 MN86063では無効*/

	if ((data_trans_blk.O_OBXR_Status + data_trans_blk.OTWORD_Status) > data_trans_blk.FRWORD_Status) {
		data_trans_blk.OTWORD_Status = (UWORD)((prn_codec_limit /(16*GA_H_Reduction)) - data_trans_blk.O_OBXR_Status); /* Feb.14,1996 */ /** 復号化ページ幅(復号化した結果できる1ラインの画素数) */
		data_trans_blk.OTWORD_Status += 1; /* By S.Kawasai 1996/04/03 */
		data_trans_blk.OTWORD_Status = (UWORD)(prn_codec_limit /(16*GA_H_Reduction));
		data_trans_blk.OTWORD_Status = (UWORD)(data_trans_blk.OTWORD_Status - data_trans_blk.O_OBXR_Status);
	}
#endif
#if (PRO_PRINT_TYPE == LED)
	/** 入出力パラメータ */
	data_trans_blk.FRWORD_Status = dma_blk.FRWORD_Status = 304;			/** フレームワード数(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	data_trans_blk.O_OBXR_Status = CDC_GetOBXR_Size(prt_queue);			/** コーデック出力オフセット *//* By M.Tachibana 1998/03/30 */
	data_trans_blk.I_OBXR_Status = 0;									/** 縮小処理後のコーデック入力オフセット */
	data_trans_blk.OTWORD_Status = 256;									/** 転送データ1ラインの画素数) */
 #if (PRO_PRINTER_GA_MD9803 == ENABLE) /* Add for MD9803 1999/05/21 by T.Soneoka */
	data_trans_blk.OTWORD_Status = ((data_trans_blk.OTWORD_Status * 100) / PRN_ReducData.GA_H_Reduction);
 #else
	data_trans_blk.OTWORD_Status /= PRN_ReducData.GA_H_Reduction;
 #endif
 
	dma_start_pointer = 0;
	dec_start_pointer = (UWORD)PRN_HorizontalDataTable[prt_queue->PrintedForm][PRN_D_STRA];	/** 復号化ライン先頭アドレス(プリンタイメージバッファの符号化開始アドレス)*/
	/*--------------------------------------------------------------------
	** カセットの中心ずれ対策
	** １ｍｍ×３＝±３．０ｍｍ
	*/
	cassette_pos = PRN_GetCassetteAdjustPosition(prt_queue->Cassette);
	adjust = (SYB_MachineParameter[cassette_pos] & 0x7f);
	if (adjust > 20) {	/* <- 3 By M.Tachibana 1998/02/19 */
		adjust = 20;
	}
	adjust *= 2;
	if (SYB_MachineParameter[cassette_pos] & 0x80) {	/** マイナス */
		dma_start_pointer = (UWORD)adjust;
	}
	else {
 #if (PRO_PRINTER == DPI200)	/* add M.Tachibana 1998/02/19 */
		adjust *=  2;
 #endif
		dec_start_pointer += (UWORD)adjust;
	}
	if (print_mode != SYS_HFINE) {
		dec_start_pointer /= 2;
	}
#endif

	data_trans_blk.C0_MTOPA_Status = 0;	/* 未使用 */
	data_trans_blk.C0_MENDA_Status = 0;	/* 未使用 */
	data_trans_blk.B_STRA0_Status = 0;	/* 未使用 */
	/** 復号化パラメータ Ch.0 */
#if (PRO_PRINT_TYPE == LASER)
	data_trans_blk.B_STRA1_Status = (UWORD)(PRN_CodecLeftMargine / 8);
#else
#if (PRO_PRINT_TYPE == THERMAL_TRANS) || (PRO_PRINT_TYPE == THERMAL)	/* 1998.6.1 K.Kawata */
#else
	data_trans_blk.B_STRA1_Status = dec_start_pointer;
#endif
#endif
	data_trans_blk.INWORD_Status = PRN_ScanScanningLineTable[MEM_IndexTable[prt_queue->Index[PRN_CompPageNo].
									IndexNo].Size][print_mode][HORIZONTAL] / 16;
	data_trans_blk.B_VCONV_Status = PRN_ReducData.CDCSubReduction;	/** 副走査方向変換率*/
	data_trans_blk.B_HCONV_Status = PRN_ReducData.CDCMainReduction;	/** 主走査方向変換率*/
	data_trans_blk.B_LMASK_Status	= 0;							/** 左側白マスク*/
	data_trans_blk.B_RMASK_Status	= 0;							/** 右側白マスク*/
	data_trans_blk.D0_MTOPA_Status = 0 + data_trans_blk.B_STRA1_Status;		/** イメージバッファ先頭アドレス */
	data_trans_blk.D0_MENDA_Status = 0xFE20 + data_trans_blk.B_STRA1_Status;	/** イメージバッファ最終アドレス */
	data_trans_blk.INLINE_Status = PRN_FROM_CODEC_LINECOUNT;

	/**プリンタコーデックのDMA転送のパラメータを設定する*/
	dma_blk.Channel	  = 1;				/** 使用するチャンネル (0 or 1)*/

	/** DMA転送パラメータ (CODEC MEMORY <- CUSTOM ･･･ 使用せず) */
	dma_blk.T0_STRA_Status	= 0;							/** DMA転送先頭アドレスポインタ*/
	dma_blk.T0_WORD_Status	= 0;							/** DMA転送ワード数（１ラインのワード数）*/
	dma_blk.T0_BLGR_Status	= 0;							/** DMA転送ライン数*/
	dma_blk.T0_MTOPA_Status	= 0;							/** DMA転送バッファ先頭アドレス*/
	dma_blk.T0_MENDA_Status	= 0;							/** DMA転送バッファ最終アドレス*/

	/** DMA転送パラメータ (CODEC MEMORY -> CUSTOM) */
#if (PRO_PRINT_TYPE == LASER)
	dma_blk.T1_STRA_Status	= 0;			/** DMA転送先頭アドレスポインタ*/
	dma_blk.T1_WORD_Status	= prn_codec_limit / (16*GA_H_Reduction);			/** DMA転送ワード数 (== 復号化ページ幅) */
	dma_blk.T1_BLGR_Status	= 53 - 1;						/** DMA転送ライン数*/
	dma_blk.T1_MTOPA_Status	= 0;							/** DMA転送バッファ先頭アドレス*/
	dma_blk.T1_MENDA_Status	= 0xFE20;						/** DMA転送バッファ最終アドレス 0x260*0x6b=0xfe20 */
#endif
#if (PRO_PRINT_TYPE == LED)	/* Add By O.Kimoto 1997/06/13 */
	dma_blk.T1_STRA_Status	= dma_start_pointer;			/** DMA転送先頭アドレスポインタ*/
	dma_blk.T1_WORD_Status	= data_trans_blk.OTWORD_Status;	/** DMA転送ワード数 (== 復号化ページ幅) */
	dma_blk.T1_BLGR_Status	= 53 - 1;						/** DMA転送ライン数*/
	dma_blk.T1_MTOPA_Status	= 0      + dma_start_pointer;	/** DMA転送バッファ先頭アドレス*/
	dma_blk.T1_MENDA_Status	= 0xFE20 + dma_start_pointer;	/** DMA転送バッファ最終アドレス 0x260*0x6b=0xfe20 */
#endif

	/**上記のパラメータでコーデックをセットアップする*/
/*	CodecDataTransferSetup(&data_trans_blk);*/	/*上記のパラメータであるように最初はＡ面をデコードするようにセットアップされる*/
	CodecPcDataTransferSetup(&data_trans_blk);	/*上記のパラメータであるように最初はＡ面をデコードするようにセットアップされる*//* By M.Tachibana 1998/03/30 */
	CDC1_DMA1_EndFlag = 0;	/**DMAの初期化前にクリアすること*/
	CodecDMA_TransferSetup(&dma_blk);			/*上記のパラメータにあるように最初はＡ面をプリンタに転送するようにセットアップされる*/
	printer = FALSE;
	CDC_ImageBufferStatus[PRINTER_CODEC] = CDC_NOT_ACCESS;	/**イメージメモリを開放する*/
#if (PRO_PRINT_TYPE == LED)	/* Add By O.Kimoto 1997/06/13 */
	PrintStatusTime[prt_queue->PhysicalPage % PRN_QUEUE_MAX].Time[2] = SYS_GeneralTimer;
#else
	PrintStatusTime.Time[2] = SYS_GeneralTimer;		/* for Debug */
#endif

	while (1) { /** 1ページイメージ転送するまでループする */
		CDC_ImageBufferStatus[PRINTER_CODEC]++;		/**コーデックはＡ面の符号化を開始する*/
		EnterCodecCommand(PRINTER_CODEC, CODEC_CMD_DATA_TRANSFER);
		if (printer) { /**プリンタが起動されている時*/
			CMN_DisableInterrupt();	/**割り込み禁止*/
			if (!CDC1_DMA1_EndFlag) {	/**DMA未終了のとき*/
				wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ53LinesのDMA終了を待つ*/
			}
			CDC1_DMA1_EndFlag = 0;
			CMN_EnableInterrupt();	/**割り込み許可*/
			/**次のＤＭＡの起動は割り込みルーチンの中で処理する*/
		}
		else {
			printer = TRUE;
			PRN_StartImagePrint();	/**プリンタを起動する*/
		}
#if (PRO_CPU == SH7043) /* コーデックデバッグ 1996/07/15 T.Nose */
		if (DEBUG_DMA_Counter < 30) {
			DEBUG_AddressBuffer[DEBUG_DMA_Counter][1] = ReadCodecParameterRegister(PRINTER_CODEC,D0_STRA_ADR);
			DEBUG_DMA_Counter++;
		}
#endif
	}
	wai_evt(EVT_CDC1_DMA1_END); /**イメージメモリからプリンタへ53LinesのDMA終了を待つ*/
	/*ここでデコードしたすべてのデータはプリンターに転送したのじゃ！ (^m^;)*/
#if (PRO_PRINT_TYPE == LED)	/* Add By O.Kimoto 1997/06/13 */
	PrintStatusTime[prt_queue->PhysicalPage % PRN_QUEUE_MAX].Time[3] = SYS_GeneralTimer;
#else
	PrintStatusTime.Time[3] = SYS_GeneralTimer;
#endif

	/* wai_tsk(0xFFFF); リターンしたところで見る */
}
#endif


#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/10/09 By H.Hirao */
 #if defined(SATSUKI2)  /* 他の機種との共用ソースなのでSATSUKI2で切ります。O.Oshima 2003/11/07 Smuratec H.C.H 2003.07.11 */
#include "\src\atlanta\satsuki2\ext_v\scn_dath.h"
#include "\src\atlanta\satsuki2\define\scn_def.h"
#include "\src\atlanta\satsuki2\ext_v\page_mem.h"
 #elif defined(STOCKHM2)
#include "\src\atlanta\stockhm2\ext_v\scn_dath.h"
#include "\src\atlanta\stockhm2\define\scn_def.h"
#include "\src\atlanta\stockhm2\ext_v\page_mem.h"
 #else
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\page_mem.h"
 #endif
#define STX_INLINE_MAX	50 /*1*//*50*/	/* 一回のコマンドでエンコードするライン数 */

static UWORD	DebugScanPageMemWriteLine[10];	/* 次に書込むラインをポイント */
static UWORD	ScanPageMemReadableLine; /* まだ読込まれていないライン数 */
static UWORD	ScanPageMemReadLine2;	/* 次に読込むラインをポイント */

/* static UWORD		ScanPageMemEncodableLine; @* まだコーデックが符号変換していないライン数 */
static UBYTE	IsScanPageEnd;	/* スキャナが原稿１ページを読み取り終了したかのフラグ */
BOOL	EnableToWriteScanPageMem2(void);	/* Enable to Write Scanner Page Memory */
BOOL	EnableToReadScanPageMem2(void);	/* Enable to Read Scanner Page Memory */
UBYTE	*GetLineAddress4ReadScanPageMem2(void); /* Get Line Address Scanner Page Memory */
void DecScanPageMemReadableLine2(void);	/* Decrement ScanPageMemReadbleLine */
extern UWORD	ScanPageMemReadLine;	/* 次に読込むラインをポイント */

/*************************************************************************
	module		:[スキャナイメージをＥＣＭバッファにエンコードするタスク]
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
	keyword		:[CDC]
	date		:[1998/10/09]
	author		:[H.Hirao]
*************************************************************************/
void CDC_STxEncodePageTask(void)
{
	UBYTE encode_kpara;
	UBYTE is_tti_available;
	UBYTE is_tti_inside;
	UBYTE tti_line;
	UBYTE cdc_stat;
	UBYTE is_abacto_on;
	UBYTE is_stop;
	UWORD scan_max_line;
	UDWORD reduc;
	/* UWORD tskno_cdc_stxdma_task; */
	UWORD tskno_cdc_encodepagetask;
	struct CodecEncodeParameterBlk_t enc_blk;
	MESSAGE_t message;
	UBYTE i;
	BYTE doc_position;

	/*--------*/
	/* 初期化 */
	/*--------*/
	CodecPageStatus = CDC_CONTINUE;
	cdc_stat = CDC_CONTINUE;
	tskno_CDC_STxDMA_Task = 0xFFFF;
	tskno_cdc_encodepagetask = 0xFFFF;
	SetClear((UBYTE *)&enc_blk, sizeof(struct CodecEncodeParameterBlk_t), 0x00);
	if (!SYS_TxTotalPage) {
		for (i = 0; i < 10; i++) {
			DebugScanPageMemWriteLine[i] = 0xffff;
		}
	}
	/*--------------------------------------------*/
	/* ＴＴＩ付ける／付けない、外付け／内付け判断 */
	/*--------------------------------------------*/
	is_tti_available = FCM_PtnrChkTTI_TxAvailable();
	if ((SYS_DocBlock.Dst.Code == SYS_JBIG_CODE)
	&& (SYB_MaintenanceSwitch[MNT_SW_B8] & JBIG_SCANNERTX_TTI_OFF)) {
		is_tti_available = 0;
	}
	is_tti_inside = CHK_UNI_TTI_Inside();

	/*------------------------*/
	/* 符号化Ｋパラメータ取得 */
	/*------------------------*/
	encode_kpara = GetK_Parameter(SYS_DocBlock.Dst.Mode);

	/*----------------------*/
	/* 符号化変化率設定処理 */
	/*----------------------*/
	TxPixReductionSet(SYS_DocBlock.Src.Size,
					  SYS_DocBlock.Src.Mode,
					  SYS_DocBlock.Dst.Size,
					  SYS_DocBlock.Dst.Mode,
					  SYS_DocBlock.ModeMethod);

	/*----------------------*/
	/* 通信コーデックを獲得 */
	/*----------------------*/
	if (!GetCodec(COMMUNICATION_CODEC, CODEC_SCANNER_TX)) {
		SaveReturnAddressAndJumpBegin();
	}
	GetCodecFlag = YES;

	/*------------------------------*/
	/* ＥＣＭバッファにＴＴＩセット */
	/*------------------------------*/
	if (is_tti_available != 0) {	/** ＴＴＩを送出するとき */
		EcmBufferBaseWritePoint = CDC_SetTTI();
	}
	else {
		EcmBufferBaseWritePoint = ECM_BUFFER_AREA_START_ADDRESS;
	}

	/*--------------------------------------------*/
	/* 原稿長制限のライン数とＴＴＩのライン数取得 */
	/*--------------------------------------------*/
	scan_max_line = CDC_GetDocumentMaxLine(SCN_ModeSw);
	tti_line = EncodeLine(COMMUNICATION_CODEC);

	/*--------------------------------------*/
	/* 通信コーデックの符号化パラメータ設定 */
	/*--------------------------------------*/
	enc_blk.CodecType = COMMUNICATION_CODEC;	/** 符号化に使用するコーデックID (ex. COMMUNICATION_CODEC) */
	enc_blk.CodeType = SYS_DocBlock.Dst.Code;	/** 符号化方式 (ex. SYS_MMR_CODE) */

	enc_blk.FRWORD_Status = 0;					/** (イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word)) */
	enc_blk.INWORD_Status = EncInpStatus;		/** 入力ワード数(イメージメモリ上の1Lineの有効画素数をWordで設定(A3_SIZE)) */
	enc_blk.INLINE_Status = STX_INLINE_MAX;		/** 入力ライン数(1回に符号化するライン数) */
	enc_blk.I_OBXR_Status = 0;					/** 縮小処理後の入力オフセット(ライン先頭アドレスから有効画素までのオフセット) */

	enc_blk.C0_STRA_Status = 0;					/** 符号化ライン先頭アドレス(スキャナイメージバッファの符号化開始アドレス) */
	enc_blk.C0_PWDR_Status = EncOtpStatus;		/** 符号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)(1/2設定) May.19,1994 */
	enc_blk.C0_OBXR_Status = 0;					/** 符号化オフセット */
	enc_blk.C0_KPR_Status = encode_kpara;		/** 符号化Kパラメータ */
	enc_blk.C0_LCONT_Status = tti_line;			/** 符号化ラインカウンタ(符号化したライン数がここでわかります) */

	/** 符号化最小符号バイト数(MH,MR符号化時に有効で1ラインの最小符号バイト数) */
	if (SYS_FaxComTxType = SYS_SCANNER_TRANSMIT) {
		enc_blk.C0_MCLR_Status = CDC_GetCodecEncodeMCLR();
	}
	else {
		enc_blk.C0_MCLR_Status = 0;
	}

	/** 符号化主走査方向変換率 */
	if (Pix_H_Reduction == 0x400) {
		enc_blk.C0_HCONV_Status = 0;	/** 100% */
	}
	else {
		enc_blk.C0_HCONV_Status = Pix_H_Reduction | 0x4000;	/** 主走査細線保持有効 */
	}

	/** 符号化副走査方向変換率 */
	if (Pix_V_Reduction == 0x00) {	/** 副走査等倍の時 */
		enc_blk.C0_VCONV_Status = 0;	/** 100% */
		enc_blk.Vmn_Status = 0;	/** 副走査:間引き指定 */
		/* ファイン→ノーマル変換 */
		if (SYS_DocBlock.Src.Mode == SYS_NORMAL) { /** 読み取りモードをチェック */
			if (CHK_UNI_FineNormalConvert()) { /** ファイン→ノーマル変換する場合 */
				enc_blk.C0_VCONV_Status = 0x2000;	/** 50% */
				enc_blk.Vmn_Status = 0x8000;	/** 副走査:ラインOR処理 */
			}
		}
	}
	else {
		/** ファイン→ノーマル変換 */
		if (SYS_DocBlock.Src.Mode == SYS_NORMAL) { /** 読み取りモードをチェック */
			if (CHK_UNI_FineNormalConvert()) { /** ファイン→ノーマル変換する場合 */
				reduc = (UDWORD)((UDWORD)65536 - (UDWORD)Pix_V_Reduction);	/** ６５５３６－（reduc × ６５５３６）＝ Pix_V_Reduction */
				reduc /= (UDWORD)2;	/** ここで%*0.01*65536の縮小率が求まる */
				Pix_V_Reduction = (UWORD)((UDWORD)65536 - reduc);	/** ここからPix_V_Reductionを求める */
			}
		}
		enc_blk.C0_VCONV_Status = Pix_V_Reduction / 4;	/** MN86064の場合は設定値が1/4です */
		if (enc_blk.C0_VCONV_Status > 0x2000) {
			enc_blk.Vmn_Status = 0;	/** コーデックバグ By M.Kotani 1997/11/17 */
		}
		else {
			enc_blk.Vmn_Status = 0x8000;	/** 副走査:ラインOR処理 */
		}
	}
	enc_blk.C0_LMASK_Status = 0;	/** 符号化左側白マスク */
	enc_blk.C0_RMASK_Status = 0;	/** 符号化右側白マスク */
#if (0)
** 	if (SCN_WhiteMaskFlag) {	/** 両端白マスク有り *//* 追加 T.Nose 1997/08/29 */
** 		enc_blk.C0_LMASK_Status = enc_blk.C0_RMASK_Status = SCN_GetEncodeMaskSize(SCN_GetEncodeStoreCodeRes()) / 8;
** 	}
#endif
	enc_blk.C0_MTOPA_Status = 0;	/** 符号化イメージバッファ先頭アドレス */
	enc_blk.C0_MENDA_Status = 0;	/** 符号化イメージバッファ最終アドレス */

	if (enc_blk.CodeType == SYS_JBIG_CODE) {
		enc_blk.C_QMCR_Status = VLENGTH_BIT;
		if (CHK_UNI_JBIG_2lineTemplate()) {
			enc_blk.C_QMCR_Status |= LRLTWO_BIT;
		}
		if (CHK_UNI_JBIG_TPB_Mode()) {
			enc_blk.C_QMCR_Status |= TPBON_BIT;
		}
		if (CHK_UNI_JBIG_SDRST()) {
			enc_blk.C_QMCR_Status |= SDRST_BIT;
		}
		enc_blk.C_QMIRM_Status = 0;		/** QM割り込みマスクレジスタ */
		enc_blk.C_Yd_Status = 0xffff;	/** 1ページ処理ライン */
		enc_blk.C_L0_Status = 128;		/** ストライプライン数 */
		enc_blk.C_Mx_Status = 127;		/** ATMOVEの最大許可オフセット */
		enc_blk.D_QMCR_Status = 0;		/** QMコントロールレジスタ */
		enc_blk.D_QMIRM_Status = 0;		/** QM割り込みマスクレジスタ */
		enc_blk.D_Yd_Status = 0;		/** 1ページ処理ライン */
		enc_blk.D_L0_Status = 0;		/** ストライプライン数 */
		enc_blk.D_Mx_Status = 0;		/** ATMOVEの最大許可オフセット */
	}

	/*------------------------------*/
	/* ＴＴＩ送出完了メッセージ送信 */
	/*------------------------------*/
	ModemMessage.Message = MSG_TTI_COMPLETE;
	snd_msg(mbxno.MDM_TaskSub, &ModemMessage);

	/*----------------------*/
	/* ＴＴＩインサイド処理 */
	/*----------------------*/
	if ((is_tti_inside != 0) && (is_tti_available != 0)) {	/** ＴＴＩインサイド時 */
		while (tti_line) {
			if (EnableToReadScanPageMem() && ScanPageMemEncodableLine) {	/** スキャナページメモリから読み込み可能 */
				CMN_DisableInterrupt();	/** 割り込み禁止 */
				GetLineAddress4ReadScanPageMem();	/** ダミーで呼び出す */
				DecScanPageMemReadableLine();	/** スキャナページメモリの読み込み可能ラインをデクリメントする */
				ScanPageMemEncodableLine--;		/** スキャナページメモリのエンコード可能ラインをデクリメントする */
				CMN_EnableInterrupt();	/** 割り込み許可 */
				tti_line--;
			}
			else {
				/* if (SCN_DocumentChanged) { */
				doc_position = QueryDocPosition();
#if (0) /* 1998/11/17 by T.Soneoka */
**				if (SCN_DocumentChanged || (doc_position == DOC_POS_MOVE_TO_PUSH_STAMP) || (doc_position == DOC_POS_FEED_OUT)) {
#else
				if (SCN_DocumentChanged) {
#endif
					SetRTC(COMMUNICATION_CODEC, enc_blk.CodeType);	/**ページの終わりにRTCをセットする*/
					CMN_DisableInterrupt();
					if (GetCodecFlag == YES) {
						GetCodecFlag = NO;
						if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_SCANNER_TX)) {
							CMN_EnableInterrupt();
							SaveReturnAddressAndJumpBegin();
						}
					}
					wai_tsk(0xFFFF);
				}
				else {
					wai_tsk(1);
				}
			}
		}
	}
#if (0)	/* for debug by H.Hirao 1998/10/29 */
** 	if (tskno_cdc_encodepagetask == 0xFFFF) {
** 		cre_tsk(&tskno_cdc_encodepagetask, TSK_CDC_ENCODEPAGETASK, 0);
** 	}
#endif
	if (tskno_CDC_STxDMA_Task == 0xFFFF) {
		cre_tsk(&tskno_CDC_STxDMA_Task, TSK_CDC_STXDMA_TASK, 0);
	}
	/*--------------------------------*/
	/* 通信コーデックのパラメータ転送 */
	/*--------------------------------*/
	if (is_tti_available) {	/** ＴＴＩを送出するとき */
		CodecImageByteSwapDisable(enc_blk.CodecType);	/** DTCR設定(バイトSwap無効) */
		CodecEncodeCDCR_Setup(enc_blk.CodecType);	/** CDCR設定 */
		CodecEncodeParameterSetup(&enc_blk);	/** パラメータレジスタセット */
		/* 符号化の初期化コマンドは発行しません */
	}
	else {
		CodecEncodeSetup(&enc_blk);
	}
	/*------------------------*/
	/* 送出画データ符号化開始 */
	/*------------------------*/
#if (0) /* 1998/10/14 */
** 	while (1) {
** 		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);	/** PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する */
** 		if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {	/** JBIGコマンド割り込み */
** 			SetCodecParameterRegister(COMMUNICATION_CODEC, C_QMIR_ADR, 0);	/** QMIRクリア */
** 			CodecParameterRegister[COMMUNICATION_CODEC].C_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, C_QMIR_ADR);
** 			Is_JBIG_Restart = 1;	/** JBIGリスタートビットOn */
** 		}
** 		if (CodecSTIR_Status[COMMUNICATION_CODEC] & CMDE0_BIT) {	/** コマンド終了時 */
** 			if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
** 				cdc_stat = CDC_RTC_DET;
** 				break;
** 			}
** 			else {	/** 原稿長制限のライン数を全てエンコード終了した場合 */
** 				cdc_stat = CDC_RTC_DET;
** 				break;
** 			}
** 		}
** 	}
#else
	is_abacto_on = FALSE;
	while (1) {
		CMN_DisableInterrupt();	/** 割り込み禁止 */
		if (ScanPageMemEncodableLine >= STX_INLINE_MAX) {
			StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
			/*
			** タスク間で変数を同時にライトする場合は割り込み禁止が必要
			** by H.Hirao 1998/12/09
			*/			
			CMN_DisableInterrupt();	/** 割り込み禁止 */
			ScanPageMemEncodableLine -= STX_INLINE_MAX;
			CMN_EnableInterrupt();	/* 割り込み許可 */
		}
		else {
			/* if (SCN_DocumentChanged) { @* ページ終了の場合 */
			doc_position = QueryDocPosition();
#if (0) /* 1998/11/17 by T.Soneoka */
**			if (SCN_DocumentChanged || (doc_position == DOC_POS_MOVE_TO_PUSH_STAMP) || (doc_position == DOC_POS_FEED_OUT)) {
#else
			if (SCN_DocumentChanged) {
#endif
				DebugScanPageMemWriteLine[SYS_TxTotalPage] = QueryScanPageMemReadableLine();
				CMN_EnableInterrupt();	/* 割り込み許可 */
				break;
			}
			else {
				wai_tsk(1);
			}
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {	/** JBIGコマンド割り込み */
			SetCodecParameterRegister(COMMUNICATION_CODEC, C_QMIR_ADR, 0);	/** QMIRクリア */
			CodecParameterRegister[COMMUNICATION_CODEC].C_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, C_QMIR_ADR);
			Is_JBIG_Restart = 1;	/** JBIGリスタートビットOn */
		}
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & CMDE0_BIT) {	/** コマンド終了時 */
			if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
				is_abacto_on = TRUE;
				cdc_stat = CDC_STOPPED;
				break;
			}
			else {
				cdc_stat = CDC_RTC_DET;
			}
		}
		if (MDM_TxStopSwFlag) {	/** ストップＳＷ */ 
			is_stop = TRUE;
			cdc_stat = CDC_STOPPED;
			break;
		}
	}
	CMN_DisableInterrupt();	/** 割り込み禁止 */
	if (ScanPageMemEncodableLine && !is_abacto_on && !is_stop) {
		SetCodecParameterRegister(COMMUNICATION_CODEC, INLINE_ADR, ScanPageMemEncodableLine);
		ScanPageMemEncodableLine = 0;
		StartEncode(COMMUNICATION_CODEC, SYS_DocBlock.Dst.Code);
	}
	else {
		CMN_EnableInterrupt();	/* 割り込み許可 */
	}
 #endif
	/*-------------------------------------------------------------------------------------------------*/
	/* RTC/NEWLENコマンドを実行する前に符号化ライン待避 （このコマンドによってクリアされてしまうため） */
	/*-------------------------------------------------------------------------------------------------*/
	MDM_EncodeLine = EncodeLine(COMMUNICATION_CODEC);

	/*------------------------*/
	/* RTC/NEWLENコマンド発行 */
	/*------------------------*/
	if (enc_blk.CodeType != SYS_JBIG_CODE) {
		SetRTC(COMMUNICATION_CODEC, enc_blk.CodeType);	/** RTCコマンド発行 */
	}
	else {
		SetCodecParameterRegister(COMMUNICATION_CODEC, C_YD_ADR, MDM_EncodeLine);	/** C-Yd更新 */
		EnterCodecCommand(COMMUNICATION_CODEC, CODEC_CMD_NEWLEN);	/** NEWLENコマンド発行 */
	}
	/*------------------------*/
	/* エンコードデータ量更新 */
	/*------------------------*/
	EncodeDataCountSet();

	/*--------------------------*/
	/* コーデックステータス更新 */
	/*--------------------------*/
	/*
	** コーデックステータスは、SCN_STxStoreTaskで更新する
	*/
	switch (cdc_stat) {
	case CDC_STOPPED:
		message.Message = MSG_DOCSTORE_STOPSW_ON;
		break;
	case CDC_RTC_DET:
	default:
		message.Message = MSG_DOCSTORE_OK;
		break;
	}

	/*--------------------*/
	/* 通信コーデック解放 */
	/*--------------------*/
	CMN_DisableInterrupt();
	if (GetCodecFlag == YES) {
		GetCodecFlag = NO;
		if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_SCANNER_TX)) {
			CMN_EnableInterrupt();
			SaveReturnAddressAndJumpBegin();
		}
	}
	CMN_EnableInterrupt();
	/* TxStartFlag = 1; このフラグを立てるのは、スキャナストアタスクで行います by H.Hirao 1998/12/21 */
	snd_msg(mbxno.SCN_Task, &message);

#if (0) /* for debug by H.Hirao */
** 	if (tskno_cdc_stxdma_task != 0xFFFF) {
** 		DMA_RequestMask(0);
** 		del_tsk(&tskno_cdc_stxdma_task);
** 	}
** 	if (tskno_cdc_encodepagetask != 0xFFFF) {
** 		del_tsk(&tskno_cdc_encodepagetask);
** 	}
#endif
	wai_tsk(0xFFFF);
}


/*************************************************************************
	module		:[スキャナバッファからコーデックにＤＭＡを起動するタスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1998/08/27]
	author		:[H.Hirao]
*************************************************************************/
void CDC_STxDMA_Task(void)
{
	struct DMA_Data_t dma_data;
	BYTE doc_position;

	dma_data.Channel = 0;
	dma_data.SrcAddress = (UDWORD)GetLineAddress4ReadScanPageMem();
	dma_data.Counter = EncInpStatus;
	dma_data.Unit = DMA_WORD_TRANSFER;
	dma_data.Direction = DMA_MEMORY_TO_IO;
	do {
		if (dma_data.SrcAddress) {
			DMA_SetupDMAU(&dma_data);
			break;
		}
		else {
			dma_data.SrcAddress = (UDWORD)GetLineAddress4ReadScanPageMem();
			wai_tsk(1);
		}
	} while (1);
	do {
		if (EnableToReadScanPageMem()) {
			CMN_DisableInterrupt();	/** 割り込み禁止 */
			DMA0_TC3Flag = 0;
			DMA_RequestEnable(dma_data.Channel);
			if (!DMA0_TC3Flag) {	/** イベント空振り防止 by H.Hirao 1998/12/08 */
				wai_evt(EVT_DMA_DRAM_COMCDC);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
			}
			/*
			** タスク間で変数を同時にライトする場合は割り込み禁止が必要
			** by H.Hirao 1998/12/09
			*/
			CMN_DisableInterrupt();	/** 割り込み禁止 */
			DecScanPageMemReadableLine();
			CMN_EnableInterrupt();	/** 割り込み許可 */
			break;
		}
		else {
			wai_tsk(1);
		}
	} while (1);

	do {
		if (EnableToReadScanPageMem()) {	/** スキャナバッファから読み込み可能 */
			CMN_DisableInterrupt();	/** 割り込み禁止 */
			dma_data.SrcAddress = (UDWORD)GetLineAddress4ReadScanPageMem();
			if (dma_data.SrcAddress) {
				DMA0_TC3Flag = 0;
				DMA_RestartDMAU(dma_data.Channel, dma_data.Direction, dma_data.Counter, (UDWORD)dma_data.SrcAddress);
				if (!DMA0_TC3Flag) {	/* イベント空振り防止 by H.Hirao 1998/12/08 */
					wai_evt(EVT_DMA_DRAM_COMCDC);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
				}
				/*
				** タスク間で変数を同時にライトする場合は割り込み禁止が必要
				** by H.Hirao 1998/12/09
				*/
				CMN_DisableInterrupt();	/** 割り込み禁止 */
				DecScanPageMemReadableLine();
				CMN_EnableInterrupt();	/** 割り込み許可 */
			}
			else {
				wai_tsk(1);
			}
		}
		else {
			/* if (SCN_DocumentChanged) { */
			doc_position = QueryDocPosition();
#if (0) /* 1998/11/17 by T.Soneoka */
**			if (SCN_DocumentChanged || (doc_position == DOC_POS_MOVE_TO_PUSH_STAMP) || (doc_position == DOC_POS_FEED_OUT)) {
#else
			if (SCN_DocumentChanged) {
#endif
				DMA_RequestMask(dma_data.Channel);
				break;
			}
			else {
				wai_tsk(1);
			}
		}
	} while (1);

	wai_tsk(0xFFFF);

}

/* デバッグ用タスク by H.Hirao 1998/10/28 */
void CDC_EncodePageTask(void)
{
	UBYTE	*dest;						/* Destination Address */
	UWORD	*destw;

/* Modify by SMuratec K.W.Q 2003/07/24 */
/*	UWORD	*srcw;*/
	UBYTE	*srcw;

	UWORD	ploop;

	if (CodecGetID[COMMUNICATION_CODEC] == CODEC_SCANNER_TX) {
#if (0)
** 		ploop = 1143;
** 		ScanPageMemWriteLine = 0;
** 		ScanPageMemReadLine2 = 0;
** 		ScanPageMemReadableLine = 0;
** 		ScanPageMemEncodableLine = 0;
** 		IsScanPageEnd = FALSE;
** 
** 		while (ploop) {
** 			if (EnableToWriteScanPageMem2()) {
** 				dest = &ScanPageMem[ScanPageMemWriteLine][0];
** 				CMN_MemorySet(dest, SYS_A4_PAGE_WIDTH, 0xC3);
** 				if (++ScanPageMemWriteLine >= SCANPAGE_ROW) {
** 					ScanPageMemWriteLine = 0;
** 				}
** 				ScanPageMemReadableLine++;
** 				ScanPageMemEncodableLine++;
** 				ploop --;
** 			}
** 			else {
** 				wai_tsk(1);
** 			}
** 		}
** 		IsScanPageEnd = TRUE;
** 		wai_tsk(0xFFFF);
#endif
	}
	else if (CodecGetID[COMMUNICATION_CODEC] == CODEC_PRINTER_RX) {
		destw = (UWORD *)&ScanPageMem[0][0];
		while (1) {
			if (EnableToReadPrtImageBuf()) {
				srcw = GetReadPtrPrtImageBuf();

				/* Modify by SMuratec K.W.Q 2003/07/24 */
				/*destw = CMN_IntDataCopyNum(destw, srcw, PRxDMA_Data.Counter);*/
				destw = CMN_IntDataCopyNum(destw, (UWORD *)srcw, PRxDMA_Data.Counter);
				
				DecPrtImageReadableLine();
			}
			else {
				if ((CodecPageStatus == CDC_DECODE_ERROR) || (CodecPageStatus == CDC_RTC_DET)) {
					break;
				}
				else {
					wai_tsk(1);
				}
			}
		}
		wai_tsk(0xFFFF);
	}
}


UBYTE	*GetLineAddress4ReadScanPageMem2(void)
{
	UBYTE	*Address;

	if (ScanPageMemReadableLine > 0) {
		Address = &ScanPageMem[ScanPageMemReadLine2][0];
		if (++ScanPageMemReadLine2 >= SCANPAGE_ROW) {
			ScanPageMemReadLine2 = 0;
		}
	} else {
		Address = (UBYTE *)0;
	}

	return	Address;
}


BOOL	EnableToReadScanPageMem2(void)
{
	return	(ScanPageMemReadableLine != 0) ? TRUE : FALSE;
}


void DecScanPageMemReadableLine2(void)
{
	if (ScanPageMemReadableLine > 0) {
		ScanPageMemReadableLine--;
	}
}


BOOL	EnableToWriteScanPageMem2(void)
{
	return	(ScanPageMemReadableLine < (SCANPAGE_ROW - 5)) ? TRUE : FALSE;
}

#endif /* (PRO_SCN_CODEC_TYPE == SOFTWARE) 1998/10/09 by H.Hirao */

/* #if (PRO_PRN_CODEC_TYPE	== SOFTWARE) && (PRO_PRINT_TYPE == THERMAL) *//* 1998/10/19 by H.Hirao */
#if (PRO_PRINTER_RX == ENABLE)	/* by H.Hirao 1998/10/27 */
static BOOL IsPrinterError = 0; /* by H.Hirao 1998/12/07 */
/*************************************************************************
	module		:[モデム（ＥＣＭ）バッファからプリンタバッファに1論理ページ複合するタスク]
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
	keyword		:[CDC]
	date		:[1998/10/19]
	author		:[H.Hirao]
*************************************************************************/
void CDC_PRxDecodePageTask(void)
{
	struct CodecDecodeParameterBlk_t dec_blk;
	UWORD rx_size;
	/* UWORD tskno_cdc_prxdma_task; */
	UBYTE cdc_stat;
	UBYTE debugsw;
	MESSAGE_t	*CDC_TaskMsg;

	/*--------*/
	/* 初期化 */
	/*--------*/
	/* tskno_cdc_prxdma_task = 0xFFFF; */
	tskno_CDC_PRxDMA_Task = 0xFFFF;
	debugsw = 0;
	SetClear((UBYTE *)&dec_blk, sizeof(struct CodecDecodeParameterBlk_t), 0x00);
	IsPrinterError = FALSE; /* added by H.Hirao 1998/12/07 */
	
	/*--------------------*/
	/* 通信コーデック獲得 */
	/*--------------------*/
	if (!GetCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
		SaveReturnAddressAndJumpBegin();
	}

	/*--------------------*/
	/* 復号化ページ幅設定 */
	/*--------------------*/
	rx_size = GetCodecSize(SYS_DocBlock.Src.Size, SYS_DocBlock.Src.Mode);

	/*--------------------------------------*/
	/* 通信コーデックの復号化パラメータ設定 */
	/*--------------------------------------*/
	dec_blk.CodecType = COMMUNICATION_CODEC;	/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/
	dec_blk.CodeType = SYS_DocBlock.Src.Code;	/**復号化方式 (ex. SYS_MMR_CODE)*/

	dec_blk.FRWORD_Status = 0;			/**(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	dec_blk.OTWORD_Status = rx_size;	/**復号化ページ幅(復号化した結果できる1ラインの画素数)*/
	dec_blk.O_OBXR_Status = 0;			/**出力オフセット(左寄せ 左データカット)*/

	dec_blk.D0_STRA_Status = 0;			/**復号化イメージバッファ先頭アドレス*/
	dec_blk.D0_PWDR_Status = rx_size;	/**復号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
	dec_blk.D0_OBXR_Status = 0;			/**複合化オフセット*/
	if (dec_blk.CodeType == SYS_MMR_CODE) {
		dec_blk.D0_RTCR_Status = 1;			/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	}
	else {
		dec_blk.D0_RTCR_Status = 3;			/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	}
	dec_blk.D0_BLGR_Status  = 0xffff;	/**復号化処理ライン数(1回に復号化するライン数)*/
	dec_blk.D0_LCONT_Status = 0;		/**復号化ラインカウンタ(復号化したライン数(エラーを含む)がセットされます)*/
	dec_blk.D0_ELIN_Status  = 0;		/**復号化エラーライン数(1ページ内のエラーライン数の総数がセットされます)*/
	if (CHK_UNI_InchMiriConvert() == 0){	/**インチ／ミリ変換しない場合*/
		dec_blk.D0_HCONV_Status = 0;		/**復号化主走査方向変換率*/
		dec_blk.D0_VCONV_Status = 0;		/**復号化副走査方向変換率*/
	}
	else {
		if (SYS_DocBlock.ModeMethod == SYS_METRIC) {
			dec_blk.D0_HCONV_Status = 0;		/**復号化主走査方向変換率*/
			dec_blk.D0_VCONV_Status = 0;		/**復号化副走査方向変換率*/
		}
		else {	/* インチで受信ミリで蓄積 */
			dec_blk.D0_HCONV_Status = 0x410;	/**復号化主走査方向変換率	inch -> mili 101.60%*/
			dec_blk.D0_VCONV_Status = 0x16a;	/**復号化副走査方向変換率	inch -> mili  97.79%*/
		}
	}
	dec_blk.D0_LMASK_Status = 0;		/**復号化左側白マスク*/
	dec_blk.D0_RMASK_Status = 0;		/**復号化右側白マスク*/
	dec_blk.D0_MTOPA_Status = 0;		/**復号化イメージバッファ先頭アドレス*/
	dec_blk.D0_MENDA_Status = 0;		/**復号化イメージバッファ最終アドレス*/

#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (SYS_DocBlock.Src.Code == SYS_JBIG_CODE) {
		/*
		** BIHがとれるまで待ちます
		*/
		rcv_msg(mbxno.CDC_Task, &CDC_TaskMsg);

		/* 符号化側をセットします */
		dec_blk.C_QMCR_Status = 0;	/*QMコントロールレジスタ*/
		dec_blk.C_QMIRM_Status = 0;	/*QM割り込みマスクレジスタ*/
		dec_blk.C_Yd_Status = 0;	/*1ページ処理ライン*/
		dec_blk.C_L0_Status = 0;	/*ストライプライン数*/
		dec_blk.C_Mx_Status = 0;	/*ATMOVEの最大許可オフセット*/
		/* 復号化側をセットします */
		/* QMコントロールレジスタ */
		dec_blk.D_QMCR_Status = 0;
		if (CDC_JBG_BIH.Options & JBG_BIT_LRLTWO) {	/* ２ラインテンプレートか？ */
			dec_blk.D_QMCR_Status |= LRLTWO_BIT;	/**	２ラインテンプレート選択 */
		}
		if (CDC_JBG_BIH.Options & JBG_BIT_VLENGTH) {	/* NEWLEN有効か？ */
			dec_blk.D_QMCR_Status |= VLENGTH_BIT;	/**	NEWLENマーカ有効 */
		}
		if (CDC_JBG_BIH.Options & JBG_BIT_TPBON) {	/* TP Onか？ */
			dec_blk.D_QMCR_Status |= TPBON_BIT;	/**	TPモード有効 */
		}
		/* QM割り込みマスクレジスタ */
		/* ＮＥＷＬＥＮ割り込みによるバグ調査のため 1998/03/17 by T.Soneoka */
		if (debugsw == 1) {
			dec_blk.D_QMIRM_Status = (PAGENDM_BIT | DETNWLM_BIT);
		}
		else {
			dec_blk.D_QMIRM_Status = 0;
		}
		dec_blk.D_Yd_Status = CDC_JBG_BIH.YD;	/** 1ページ処理ライン */
		dec_blk.D_L0_Status = CDC_JBG_BIH.L0;	/** ストライプライン数 */
		dec_blk.D_Mx_Status = CDC_JBG_BIH.MX;	/** ATMOVEの最大許可オフセット */
		QBUF0_stat = 0;
		QBUF1_stat = 0;
	}
#endif

	/**上記のパラメータでコーデックをセットアップする*/
	CodecDecodeSetup(&dec_blk);
#if (PRO_JBIG == ENABLE)	/* BIHエラー調査のため by T.Soneoka 1998/03/16 */
	if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
		CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR);
		CodecPageStatus = CDC_DECODE_ERROR;
		CodecMessage.Message = MSG_FROM_CODE_CONVERT_TASK;
		snd_msg(mbxno.MDM_RxEcmControlTask, &CodecMessage);
		wai_tsk(0xFFFF);
	}
#endif
	if (CodecPageStatus == CDC_CONTINUE) {
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR, MDM_RxTotalLine);	/**復号化ラインカウンタ*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_ELIN_ADR, MDM_RxErrorTotalLine);	/**復号化エラーライン数*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, C0_LCONT_ADR, MDM_EncodeLine);	/**符号化ラインカウンタ*/
		CodecRestartFlag = 1;
	}
	CodecPageStatus = CDC_CONTINUE;	/** 初期化 */
	cdc_stat = CDC_CONTINUE;


	/*--------------------------------------------------------------------*/
	/* コーデックからプリントバッファにＤＭＡを起動するタスクを生成する。 */
	/*--------------------------------------------------------------------*/
	PRxDMA_Data.Channel = 1;
	/* PRxDMA_Data.SrcAddress = (UDWORD)&PRN_ImageBuffer1[0][0]; */
	PRxDMA_Data.Counter = rx_size;
	PRxDMA_Data.Unit = DMA_WORD_TRANSFER;
	PRxDMA_Data.Direction = DMA_IO_TO_MEMORY;

	if (tskno_CDC_PRxDMA_Task == 0xFFFF) {
		cre_tsk(&tskno_CDC_PRxDMA_Task, TSK_CDC_PRXDMA_TASK, 0);
	}

	/*--------------------------*/
	/*	受信データ複合化開始	*/
	/*--------------------------*/
	do {
		StartDecode(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code);	/**PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/
#if (PRO_JBIG == ENABLE)
		/* JBIGコマンド割り込み */
		/* Debug用 1998/03/03 by T.Soneoka */
		DebugDecodeLine = ReadCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR);

		if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
			CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR);
			if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETATM_BIT) {	/*ATMOVEマーカの検出（1ストライプ3個以上）*/
				QBUF0_stat = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMBUF0_ADR);		/* QMBUF0リード */
				QBUF1_stat = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMBUF1_ADR);		/* QMBUF1リード */
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & ATMREQ_BIT) {	/*ATMOVEパラメータ（τx，YAT）の書き込み要求*/
				SetCodecParameterRegister(COMMUNICATION_CODEC, (0x00FF & QBUF0_stat), D_TX0_ADR);	/*Tx0設定 */
				SetCodecParameterRegister(COMMUNICATION_CODEC, QBUF1_stat, D_YAT0_ADR);	/*YAT0設定 */
				dec_blk.D_QMCR_Status |= AT0ENB_BIT;	/*AT0有効設定 */
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETCMT_BIT) {	/*コメントマーカの検出*/
				/* マスクしているので入ってこない */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETNWL_BIT) {	/*NEWLENマーカの検出*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETABT_BIT) {	/*アボートBIDマーカの検出*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETERR_BIT) {	/*エラー検出（ビット1,0参照）*/
				/* ERR0_BIT このビット読む */	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
				/* ERR1_BIT	このビット読む */	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & PAGEND_BIT) {	/*1ページ処理終了*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else {
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			/*  移動 by T.Soneoka 1998/03/04 */
			SetCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR, 0);	/* QMIRクリア */
		}
#endif
		/* コマンド終了割り込み */
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & CMDE0_BIT) {
			if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
				cdc_stat = CDC_STOPPED;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {
				cdc_stat = CDC_RTC_DET;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {
				if ((dec_blk.CodeType == SYS_MMR_CODE)
				||  (dec_blk.CodeType == SYS_MG3_CODE)
				||  (dec_blk.CodeType == SYS_JBIG_CODE)) {
					cdc_stat = CDC_DECODE_ERROR;
					if (debugsw == 1) {
						wai_tsk(0xFFFF);
					}
				}
			}
			else {
				cdc_stat = CDC_RTC_DET;
			}
		}
	} while (cdc_stat == CDC_CONTINUE);

	/* コーデックからプリンタバッファに１ライン毎にＤＭＡを起動するタイミングで
	** プリンタにエラーが有るかどうかをチェックする
	** by H.Hirao 1998/12/07
	*/
	if (!IsPrinterError) {
		switch (cdc_stat) {
		case CDC_DECODE_ERROR:
			CodecPageStatus = CDC_DECODE_ERROR;
			break;
		case CDC_RTC_DET:
		case CDC_STOPPED:
		default:
			CodecPageStatus = CDC_RTC_DET;
			break;
		}
	}
	else {
		switch (cdc_stat) {
		case CDC_DECODE_ERROR:
			CodecPageStatus = CDC_DECODE_ERROR;
			break;
		case CDC_RTC_DET:
		case CDC_STOPPED:
		default:
			CodecPageStatus = CDC_PRINTER_ERROR;
		}
	}
	/*--------------------*/
	/* 通信コーデック解放 */
	/*--------------------*/
	CMN_DisableInterrupt();
	if (GetCodecFlag == YES) {
		GetCodecFlag = NO;
		if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
			CMN_EnableInterrupt();
			SaveReturnAddressAndJumpBegin();
		}
	}
#if (0)
** 	if (tskno_cdc_prxdma_task != 0xFFFF) {
** 		DMA_RequestMask(PRxDMA_Data.Channel);
** 		del_tsk(&tskno_cdc_prxdma_task);
** 	}
#endif

	ClosePrtImageBuf4Copy();
	CodecMessage.Message = MSG_FROM_CODE_CONVERT_TASK;
	snd_msg(mbxno.MDM_RxEcmControlTask, &CodecMessage);

	wai_tsk(0xFFFF);
}


/* 1998/11/18 Add by T.Soneoka */
void CDC_PRxDecodePageTaskExit(void)
{
#if (0) /* 1998/12/08 by T.Soneoka */
**	ClosePrtImageBuf4Copy();
#endif
	/* 異常終了した場合に、記録紙カット動作させる為 1998/12/22 by T.Soneoka */
	if (Paper.Phase == PAPER_PHASE_PRINT) {
		IsPrintFinish = TRUE;
	}
	exi_tsk();
}

/*************************************************************************
	module		:[コーデックからプリンタバッファにＤＭＡを起動する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1998/10/19]
	author		:[H.Hirao]
*************************************************************************/
void CDC_PRxDMA_Task(void)
{
	UWORD tskno_cdc_encodepagetask;
	UBYTE is_printer_error;
	UBYTE debug;	/* 1998/12/16 by T.Soneoka */
	
	debug = 0;

	tskno_cdc_encodepagetask = 0xFFFF;

	OpenPrtImageBuf4Copy();
	/* InzPrtImageBuf();	@** Initialize Print Image Buffer */
	PRxDMA_Data.SrcAddress = (UDWORD)GetWritePtrPrtImageBuf();
	DMA_SetupDMAU(&PRxDMA_Data);

#if (0) /* for debug by H.Hirao 1998/11/06 */
** 	if (tskno_cdc_encodepagetask == 0xFFFF) {
** 		cre_tsk(&tskno_cdc_encodepagetask, TSK_CDC_ENCODEPAGETASK, 0);
** 	}
#endif

	do {
		if (EnableToWritePrtImageBuf()) {
			CMN_DisableInterrupt();	/** 割り込み禁止 */
			DMA0_TC2Flag = 0;
			DMA_RequestEnable(PRxDMA_Data.Channel);
			if (!DMA0_TC2Flag) {	/** イベント空振り防止 by H.Hirao 1998/12/09 */
				wai_evt(EVT_DMA_COMCDC_DRAM);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
			}
			CMN_EnableInterrupt();	/** 割り込み許可 */
			IncPrtImageReadableLine();
			/* 1998/12/16 by T.Soneoka */
			if (debug) {
				wai_tsk(debug);
			}
			break;
		}
		else {
			wai_tsk(1);	/** 10ms Wait */
		}
	} while (1);

	do {
		/* １ライン毎にプリンタエラーをチェック
		** by H.Hirao 1998/12/07
		*/
		if (!IsPrinterError) {	/** プリンタ正常時 */
			if ((SYS_MachineStatus[SYS_COVER_STATUS] & SYS_COVER_PRINTER_OPEN)
			/* ||	(PrinterError & (PRT_ERROR_JAM | PRT_ERROR_NO_PAPER))) {	@** カバーオープン||記録紙無し||ジャムの場合 */
			 || (PrinterError)) {
				IsPrinterError = TRUE;
			}
		}
		if (!IsPrinterError) {	/** プリンタ正常時 */
			if (EnableToWritePrtImageBuf()) {
				CMN_DisableInterrupt();	/** 割り込み禁止 */
				PRxDMA_Data.SrcAddress = (UDWORD)GetWritePtrPrtImageBuf();
				DMA0_TC2Flag = 0;
				DMA_RestartDMAU(PRxDMA_Data.Channel, PRxDMA_Data.Direction, PRxDMA_Data.Counter, (UDWORD)PRxDMA_Data.SrcAddress);
				if (!DMA0_TC2Flag) {	/** イベント空振り防止 by H.Hirao 1998/12/09 */
					wai_evt(EVT_DMA_COMCDC_DRAM);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
				}
				CMN_EnableInterrupt();	/** 割り込み許可 */
				IncPrtImageReadableLine();
				/* 1998/12/16 by T.Soneoka */
				if (debug) {
					wai_tsk(debug);
				}
			}
			else {
				if ((CodecPageStatus == CDC_DECODE_ERROR) || (CodecPageStatus == CDC_RTC_DET)) {
					DMA_RequestMask(PRxDMA_Data.Channel);
					break;
				}
				else {
					wai_tsk(1);	/** 10ms Wait */ /** 割り込み禁止解除 */
				}
			}
		}
		else {	/** プリンタエラーの場合 */
			if (EnableToWritePrtImageBuf()) {
				CMN_DisableInterrupt();	/** 割り込み禁止 */
				PRxDMA_Data.SrcAddress = (UDWORD)GetWritePtrPrtImageBuf();
				DMA0_TC2Flag = 0;
				DMA_RestartDMAU(PRxDMA_Data.Channel, PRxDMA_Data.Direction, PRxDMA_Data.Counter, (UDWORD)PRxDMA_Data.SrcAddress);
				if (!DMA0_TC2Flag) {	/** イベント空振り防止 by H.Hirao 1998/12/09 */
					wai_evt(EVT_DMA_COMCDC_DRAM);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
				}
				CMN_EnableInterrupt();	/** 割り込み許可 */
				IncPrtImageReadableLine();
				/* 1998/12/16 by T.Soneoka */
				if (debug) {
					wai_tsk(debug);
				}
			}
			else {
				if ((CodecPageStatus == CDC_DECODE_ERROR) || (CodecPageStatus == CDC_PRINTER_ERROR)) {
					DMA_RequestMask(PRxDMA_Data.Channel);
					break;
				}
				else {
					/* プリンタエラー時に画データを受け捨てる
					*/
					CMN_DisableInterrupt();	/** 割り込み禁止 */
					DMA0_TC2Flag = 0;
					DMA_RestartDMAU(PRxDMA_Data.Channel, PRxDMA_Data.Direction, PRxDMA_Data.Counter, (UDWORD)PRxDMA_Data.SrcAddress);
					if (!DMA0_TC2Flag) {	/** イベント空振り防止 by H.Hirao 1998/12/09 */
						wai_evt(EVT_DMA_COMCDC_DRAM);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
					}
					CMN_EnableInterrupt();	/** 割り込み許可 */
				}
			}
		}
	} while (1);

	wai_tsk(0xFFFF);
}
#endif /* (PRO_PRINTER_RX == ENABLE) 1998/10/28 */ /* (PRO_PRN_CODEC_TYPE == SOFTWARE) && (PRO_PRINT_TYPE == THERMAL) 1998/10/19 By H.Hirao */

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/*1999.2.5 K.Kawata	*/
/*****************************************************************************************
	module		:[モデム（ＥＣＭ）バッファからプリンタバッファに1論理ページ複合するタスク]
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
	keyword		:[CDC]
	date		:[1999/2/5]
	author		:[K.Kawata]
***************************************************************************************/
void CDC_PRxDecodePageTask(void)
{
struct		CodecDecodeParameterBlk_t	dec_blk;
UWORD		rx_size;
UBYTE		cdc_stat;
MESSAGE_t	*CDC_TaskMsg;

	PRN_PrinterRxOpen();
	tskno_CDC_PRxDMA_Task = 0xFFFF;	/* 初期化 */
	SetClear((UBYTE *)&dec_blk, sizeof(struct CodecDecodeParameterBlk_t), 0x00);
	PRN_Control.Error = NO;
/* 通信コーデック獲得 */
	if (!GetCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
		SaveReturnAddressAndJumpBegin();
	}
/* 復号化ページ幅設定 */
	rx_size = GetCodecSize(SYS_DocBlock.Src.Size, SYS_DocBlock.Src.Mode);
/* 通信コーデックの復号化パラメータ設定 */
	dec_blk.CodecType = COMMUNICATION_CODEC;	/**符号化に使用するコーデックID (ex. SCANNER_CODEC)*/
	dec_blk.CodeType = SYS_DocBlock.Src.Code;	/**復号化方式 (ex. SYS_MMR_CODE)*/
	dec_blk.FRWORD_Status = 0;			/**(イメージメモリ上の1Lineの画素数をWordで設定(A3_SIZE=4864bit=304word))*/
	dec_blk.OTWORD_Status = rx_size;	/**復号化ページ幅(復号化した結果できる1ラインの画素数)*/
	dec_blk.O_OBXR_Status = 0;			/**出力オフセット(左寄せ 左データカット)*/
	dec_blk.D0_STRA_Status = 0;			/**復号化イメージバッファ先頭アドレス*/
	dec_blk.D0_PWDR_Status = rx_size;	/**復号化ページ幅(縮小処理などの結果出力される有効画素数をWordで設定)*/
	dec_blk.D0_OBXR_Status = 0;			/**複合化オフセット*/
	if (dec_blk.CodeType == SYS_MMR_CODE) {
		dec_blk.D0_RTCR_Status = 1;			/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	}
	else {
		dec_blk.D0_RTCR_Status = 3;			/**復号化RTC数(設定数のRTCを検出すればデコードを終了する)*/
	}
	dec_blk.D0_BLGR_Status  = 0xffff;	/**復号化処理ライン数(1回に復号化するライン数)*/
	dec_blk.D0_LCONT_Status = 0;		/**復号化ラインカウンタ(復号化したライン数(エラーを含む)がセットされます)*/
	dec_blk.D0_ELIN_Status  = 0;		/**復号化エラーライン数(1ページ内のエラーライン数の総数がセットされます)*/
	dec_blk.D0_HCONV_Status = 0;		/**復号化主走査方向変換率*/
	dec_blk.D0_VCONV_Status = 0;		/**復号化副走査方向変換率*/
	dec_blk.D0_LMASK_Status = 0;		/**復号化左側白マスク*/
	dec_blk.D0_RMASK_Status = 0;		/**復号化右側白マスク*/
	dec_blk.D0_MTOPA_Status = 0;		/**復号化イメージバッファ先頭アドレス*/
	dec_blk.D0_MENDA_Status = 0;		/**復号化イメージバッファ最終アドレス*/
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	if (SYS_DocBlock.Src.Code == SYS_JBIG_CODE) {
		rcv_msg(mbxno.CDC_Task, &CDC_TaskMsg);	/* BIHがとれるまで待ちます */
		/* 符号化側をセットします */
		dec_blk.C_QMCR_Status = 0;	/*QMコントロールレジスタ*/
		dec_blk.C_QMIRM_Status = 0;	/*QM割り込みマスクレジスタ*/
		dec_blk.C_Yd_Status = 0;	/*1ページ処理ライン*/
		dec_blk.C_L0_Status = 0;	/*ストライプライン数*/
		dec_blk.C_Mx_Status = 0;	/*ATMOVEの最大許可オフセット*/
		/* 復号化側をセットします */
		dec_blk.D_QMCR_Status = 0;	/* QMコントロールレジスタ */
		if (CDC_JBG_BIH.Options & JBG_BIT_LRLTWO) {	/* ２ラインテンプレートか？ */
			dec_blk.D_QMCR_Status |= LRLTWO_BIT;	/**	２ラインテンプレート選択 */
		}
		if (CDC_JBG_BIH.Options & JBG_BIT_VLENGTH) {	/* NEWLEN有効か？ */
			dec_blk.D_QMCR_Status |= VLENGTH_BIT;	/**	NEWLENマーカ有効 */
		}
		if (CDC_JBG_BIH.Options & JBG_BIT_TPBON) {	/* TP Onか？ */
			dec_blk.D_QMCR_Status |= TPBON_BIT;	/**	TPモード有効 */
		}
		/* QM割り込みマスクレジスタ */
		/* ＮＥＷＬＥＮ割り込みによるバグ調査のため 1998/03/17 by T.Soneoka */
		dec_blk.D_QMIRM_Status = 0;
		dec_blk.D_Yd_Status = CDC_JBG_BIH.YD;	/** 1ページ処理ライン */
		dec_blk.D_L0_Status = CDC_JBG_BIH.L0;	/** ストライプライン数 */
		dec_blk.D_Mx_Status = CDC_JBG_BIH.MX;	/** ATMOVEの最大許可オフセット */
		QBUF0_stat = 0;
		QBUF1_stat = 0;
	}
#endif
	/**上記のパラメータでコーデックをセットアップする*/
	CodecDecodeSetup(&dec_blk);
#if (PRO_JBIG == ENABLE)	/* BIHエラー調査のため by T.Soneoka 1998/03/16 */
	if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
		CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR);
		CodecPageStatus = CDC_DECODE_ERROR;
		CodecMessage.Message = MSG_FROM_CODE_CONVERT_TASK;
		snd_msg(mbxno.MDM_RxEcmControlTask, &CodecMessage);
		wai_tsk(0xFFFF);
	}
#endif
	if (CodecPageStatus == CDC_CONTINUE) {
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR, MDM_RxTotalLine);	/**復号化ラインカウンタ*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, D0_ELIN_ADR, MDM_RxErrorTotalLine);	/**復号化エラーライン数*/
		SetCodecParameterRegister(COMMUNICATION_CODEC, C0_LCONT_ADR, MDM_EncodeLine);	/**符号化ラインカウンタ*/
		CodecRestartFlag = 1;
	}
	CodecPageStatus = CDC_CONTINUE;	/** 初期化 */
	cdc_stat = CDC_CONTINUE;
/* コーデックからプリントバッファにＤＭＡを起動するタスクを生成する。 */
	PRxDMA_Data.Channel = DMA_COMCDC_DRAM_CH;
	PRxDMA_Data.Counter = rx_size;
	PRxDMA_Data.Unit = DMA_WORD_TRANSFER;
	PRxDMA_Data.Direction = DMA_IO_TO_MEMORY;
	if (tskno_CDC_PRxDMA_Task == 0xFFFF) {
		cre_tsk(&tskno_CDC_PRxDMA_Task, TSK_CDC_PRXDMA_TASK, 0);
	}
/* 受信データ複合化開始 */
	do {
		StartDecode(COMMUNICATION_CODEC, SYS_DocBlock.Src.Code);	/* PBR:D0_BLGR_ADRに設定したライン数を連続して復号化する*/
#if (PRO_JBIG == ENABLE)
		/* JBIGコマンド割り込み */
		/* Debug用 1998/03/03 by T.Soneoka */
		DebugDecodeLine = ReadCodecParameterRegister(COMMUNICATION_CODEC, D0_LCONT_ADR);
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & JBIGIRQ_BIT) {
			CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR);
			if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETATM_BIT) {	/*ATMOVEマーカの検出（1ストライプ3個以上）*/
				QBUF0_stat = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMBUF0_ADR);		/* QMBUF0リード */
				QBUF1_stat = ReadCodecParameterRegister(COMMUNICATION_CODEC, D_QMBUF1_ADR);		/* QMBUF1リード */
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & ATMREQ_BIT) {	/*ATMOVEパラメータ（τx，YAT）の書き込み要求*/
				SetCodecParameterRegister(COMMUNICATION_CODEC, (0x00FF & QBUF0_stat), D_TX0_ADR);	/*Tx0設定 */
				SetCodecParameterRegister(COMMUNICATION_CODEC, QBUF1_stat, D_YAT0_ADR);	/*YAT0設定 */
				dec_blk.D_QMCR_Status |= AT0ENB_BIT;	/*AT0有効設定 */
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETCMT_BIT) {	/*コメントマーカの検出*/
				/* マスクしているので入ってこない */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETNWL_BIT) {	/*NEWLENマーカの検出*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETABT_BIT) {	/*アボートBIDマーカの検出*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & DETERR_BIT) {	/*エラー検出（ビット1,0参照）*/
				/* ERR0_BIT このビット読む */	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
				/* ERR1_BIT	このビット読む */	/*00:エラーなし 01:終端マーカエラー 10:BIHエラー 11:その他*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else if (CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status & PAGEND_BIT) {	/*1ページ処理終了*/
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			else {
				Is_JBIG_Restart = 1;	/**	JBIGリスタートビットOn */
			}
			/*  移動 by T.Soneoka 1998/03/04 */
			SetCodecParameterRegister(COMMUNICATION_CODEC, D_QMIR_ADR, 0);	/* QMIRクリア */
		}
#endif
		/* コマンド終了割り込み */
		if (CodecSTIR_Status[COMMUNICATION_CODEC] & CMDE0_BIT) {
			if (CodecSTIR_Status[COMMUNICATION_CODEC] & ABACT0_BIT) {
				cdc_stat = CDC_STOPPED;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & RTCDT0_BIT) {
				cdc_stat = CDC_RTC_DET;
			}
			else if (CodecSTIR_Status[COMMUNICATION_CODEC] & DERR0_BIT) {
				if ((dec_blk.CodeType == SYS_MMR_CODE)
				||  (dec_blk.CodeType == SYS_MG3_CODE)
				||  (dec_blk.CodeType == SYS_JBIG_CODE)) {
					cdc_stat = CDC_DECODE_ERROR;
				}
			}
			else {
				cdc_stat = CDC_RTC_DET;
			}
		}
	} while (cdc_stat == CDC_CONTINUE);
	if (PRN_Control.Error == NO) {
		WaitAllImageLinePrint();
		if (PRN_PrinterRxClose()) {
			switch (cdc_stat) {
			case CDC_DECODE_ERROR:
				CodecPageStatus = CDC_DECODE_ERROR;
				break;
			case CDC_RTC_DET:
			case CDC_STOPPED:
			default:
				CodecPageStatus = CDC_RTC_DET;
				break;
			}
		}
		else {
			CodecPageStatus = CDC_PRINTER_ERROR;
		}
	}
	else {
		PRN_PrinterRxClose();
		switch (cdc_stat) {
		case CDC_DECODE_ERROR:
			CodecPageStatus = CDC_DECODE_ERROR;
			break;
		case CDC_RTC_DET:
		case CDC_STOPPED:
		default:
			CodecPageStatus = CDC_PRINTER_ERROR;
		}
	}
	/* 通信コーデック解放 */
	CMN_DisableInterrupt();
	if (GetCodecFlag == YES) {
		GetCodecFlag = NO;
		if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_PRINTER_RX)) {
			CMN_EnableInterrupt();
			SaveReturnAddressAndJumpBegin();
		}
	}
	CMN_EnableInterrupt();
	CodecMessage.Message = MSG_FROM_CODE_CONVERT_TASK;
	snd_msg(mbxno.MDM_RxEcmControlTask, &CodecMessage);
	wai_tsk(0xFFFF);
}

void CDC_PRxDecodePageTaskExit(void)
{
	if (PRN_Control.PrinterRxMode != PRINT_RXPIX_PIX) {	/* 異常終了した場合に、記録紙カット動作させる為 */
		if (PRN_Control.Error == NO) {
			PRN_PrinterRxClose();
		}
		else {
			PRN_PrintRxErrorInitial();
			PRN_Control.PrinterRxMode = PRINT_RXPIX_PIX;
		}
	}
	exi_tsk();
}

/******************************************************************
	module		:[コーデックからプリンタバッファにＤＭＡを起動する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1999/2/10]
	author		:[K.Kawata]
******************************************************************/
void CDC_PRxDMA_Task(void)
{
UWORD	tskno_cdc_encodepagetask;
UWORD	over_heat_cont_count;

	tskno_cdc_encodepagetask = 0xFFFF;
	PRxDMA_Data.SrcAddress = (UDWORD)GetWritePtrPrtImageBuf();
	DMA_SetupDMAU(&PRxDMA_Data);
	CMN_DisableInterrupt();	/* 割り込み禁止 */
	DMA0_TC2Flag = 0;
	DMA_RequestEnable(PRxDMA_Data.Channel);
	over_heat_cont_count = 0;
	if (!DMA0_TC2Flag) {	/* イベント空振り防止 by H.Hirao 1998/12/09 */
		wai_evt(EVT_DMA_COMCDC_DRAM);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
	}
	CMN_EnableInterrupt();	/** 割り込み許可 */
	IncPrtImageReadableLine();
	for (;;) {
		CMN_DisableInterrupt();	/* 割り込み禁止 */
		PRxDMA_Data.SrcAddress = (UDWORD)GetWritePtrPrtImageBuf();
		DMA0_TC2Flag = 0;
		DMA_RestartDMAU(PRxDMA_Data.Channel, PRxDMA_Data.Direction, PRxDMA_Data.Counter, (UDWORD)PRxDMA_Data.SrcAddress);
		if (!DMA0_TC2Flag) {	/** イベント空振り防止 by H.Hirao 1998/12/09 */
			wai_evt(EVT_DMA_COMCDC_DRAM);	/** ＤＭＡ終了イベント待ち */ /** 割り込み禁止解除 */
		}
		CMN_EnableInterrupt();	/** 割り込み許可 */
		if (PRN_Control.Error == NO) {
			if (PRN_PrintRxErrorHaltREQ() == OK) {
				IncPrtImageReadableLine();
			}
			else {
				PRN_Control.Error = YES;
				PRN_PrintRxErrorInitial();
			}
			if (PRN_OverHeatCheck() == TRUE) {
				over_heat_cont_count++;
			}
			else {
				over_heat_cont_count = 0;
			}
			if (over_heat_cont_count > 100) {
				SYS_MachineStatus[SYS_PRINTER_STATUS2] |= SYS_PRINTER_HIGH_TEMP;
			}
		}
	}
	wai_tsk(0xFFFF);
}
#endif /* (PRO_PRINT_TYPE == THERMAL_TRANS) */
