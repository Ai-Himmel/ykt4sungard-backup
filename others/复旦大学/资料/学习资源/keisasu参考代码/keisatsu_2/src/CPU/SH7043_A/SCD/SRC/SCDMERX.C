/************************************************************************
*	System		: POPLAR
*	File Name	: SCDMERX.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdblk.h"

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
 #endif
#endif

#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mon_pro.h"		/* By Y.SUZUKI 96/07/22 */
/* #include "\src\atlanta\ext_v\extv_mbx.hv"		@*	By Y.Suzuki 1996/07/22	*/

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"		/*	By Y.Suzuki 1996/07/22	*/
#else
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"		/*	By Y.Suzuki 1996/07/22	*/
#endif

 #if (PRO_KEYPANEL == PANEL_POPLAR_L)
#include "\src\atlanta\define\std.h"
 #endif

/* By Y.Suzuki 1998/01/30 */
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
extern UWORD	tskno_SCN_DocumentStoreTask;
extern UWORD	tskno_OPR_KeyTimerTask;
#endif

#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\lst_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\ext_v\lst_data.h"
void SetDateRxDocECM(struct CdcBlk_t *, struct WorkBuf_t *, struct WorkBuf_t *);
#endif

/*************************************************************************
	module		:[ＥＣＭメモリ受信]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[
	以下桐よりコピー
	キャリア断判定ブロック数（１ｂｌｏｃｋ＝２５６ｂｙｔｅ）
	＝（３００ｂｙｔｅ／ｓ（２４００ｂｐｓ時）×キャリア断判定時間（ｓ）×通信速度倍（１．．．６）
	　／２５６ｂｙｔｅ／ｂｌｏｃｋ）＋１
	よって キャリア断時間５秒で換算すると以下の通り
	２４００　ｂｐｓ－＞６　ブロック
	４８００　ｂｐｓ－＞１２ブロック
	７２００　ｂｐｓ－＞１８ブロック
	９６００　ｂｐｓ－＞２４ブロック
	１２０００ｂｐｓ－＞３０ブロック
	１４４００ｂｐｓ－＞３６ブロック
	尚、キャリア断時間の変更はＮＯ＿ＣＡＲＲＹ＿ＭＡＸＴＩＭＥを変更するだけ
	現在５秒に設定
	]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/12/25]
	author		:[鈴木郁二]
*************************************************************************/
void SCDC_EcmDecodeTask(void)
{
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	struct CdcBlk_t encdata,*Sedp;
	struct CdcBlk_t decdata,*Sddp;
	/* UWORD	err_continuemax;* 連続エラー許容ライン数 松、竹、桜は２０本ＮｏｒｍａｌでＲＴＮ 返送	*/
	/* エンコード用ＲＬバッファ */
	struct WorkBuf_t *a_buf;
	struct WorkBuf_t *b_buf;
	struct WorkBuf_t *c_buf;
	struct WorkBuf_t *tmp;
	WORD	mem_status;
	WORD	rx_status;
	UWORD	page_length;
	UWORD	err_rate;
	UBYTE stop_on;
	WORD	c_err_line, c_err_max, mr_line;/* 連続エラーライン/同更新用パラメータ */
	UWORD tsk_sw_line_no;
	UBYTE print_on;
	UBYTE scan_on;
	UBYTE panel_on;
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
	UBYTE	n;
#endif


	mem_status = 0;
	rx_status = 0;
	stop_on = 0;
	tsk_sw_line_no = 0;
	print_on = 0;
	scan_on= 0;
	panel_on = 0;

	/** ソフトコーデック初期化 */
	Sedp = &encdata;
	Sddp = &decdata;
	Sedp->BufMode = MEM1;
	Sddp->BufMode = ECM_BUF;
	CodecPageStatus = CDC_READY;
	SoftEncodeInitial(Sedp);
	SoftDecodeInitial(Sddp);
	/* デコード符号化方式をＭＭＲ/ＭＲ */
	/* Sddp->Coding = RxMemoryStoreData.Code;*/

	/* ＦＣＭの大域変数をＳＣＤの大域変数へ */
	SCD_EcmSize = FcomEcmSize;

	/* タスクスイッチ調整用メンテナンスＳＷ－Ｆをコピーする By Y.Suzuki 1997/10/17 */
	CopyFromMantSwF();

	/* ＲＬバッファ初期化 */
	RlBufInit(Sddp->Img_Size);
	a_buf = &RL1;
	b_buf = &RL2;
	c_buf = &RL3;


	/*	ダイレクト受信有無 By Y.Suzuki 1997/06/13	*/
	SCD_CheckDirectRx();
	if (SCD_DirectRx) {
		Sddp->Wp = Sedp->Wp;
		Sddp->Wp->Buf = Sedp->Wp->Buf;
		Sddp->Wp->Adr = Sedp->Wp->Adr;
		Sddp->Wp->Bit = Sedp->Wp->Bit;
	}

	c_err_line = 0;
	c_err_max = 0;
	MDM_RxTotalLine = 0;		/**	１ページトータルライン数初期化	*/
	MDM_RxErrorTotalLine = 0;	/**	１ページエラーライン数初期化	*/
	MDM_EncodeLine = 0;
	mr_line = 1;
	if (SYS_DocBlock.Src.Code == SYS_MR_CODE) {
	    mr_line = 2;
		if (SYS_DocBlock.Src.Mode == SYS_FINE) {
			mr_line = mr_line * 2;
		}
		else if (SYS_DocBlock.Src.Mode != SYS_NORMAL) {/* HFINE SFINE */
			mr_line = mr_line * 4;
		}
	}

	/*--------------------------------------*/
	/* 最大受信ライン数セット 				*/
	/*--------------------------------------*/
	page_length = SYS_DocBlock.DocLength;
	if(page_length != SYS_NO_LIMIT_PAGE_LENGTH) {
		switch(SYS_DocBlock.Src.Mode) {
		case SYS_FINE:
			page_length *= 2;
			break;
		case SYS_SFINE:
		case SYS_HFINE:
			page_length *= 4;
			break;
		}
	}

	/*--------------------------------------*/
	/*	ＲＴＮ返送連続エラーライン数設定	*/
	/*--------------------------------------*/
#if(0)/* ECM ではいらない */
	page_length = SYS_DocBlock.DocLength;
	switch(SYS_DocBlock.Src.Mode) {
	case SYS_FINE:
		err_continuemax *= 2;
		break;
	case SYS_SFINE:
	case SYS_HFINE:
		err_continuemax *= 4;
		break;
	}
#endif

	/*----------------------*/
	/*	エラー判定基準設定	*/
	/*----------------------*/
	err_rate = CHK_RTN_TxRate();	/*	エラー判定基準設定	*/

	/*------------------------------------------------------*/
	/*	ＲＴＣ検出するまでＤＥＣＯＤＥ／ＥＮＣＯＤＥする	*/
	/*------------------------------------------------------*/
	CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/

#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
	/*----------------------------*/
	/* 受信原稿の上に日時を付ける */
	/*----------------------------*/
	if (CMN_CheckCILEnable()) {	/* ＣＩＬ機能有りで、ユニークＳＷ I:5-7 が有効 */
		SetDateRxDocECM(Sedp, a_buf, b_buf);
	}

	if (!SCD_DirectRx) {	/* ﾀﾞｲﾚｸﾄ受信ではｲﾝｻｲﾄﾞできないので、ｱｳﾄｻｲﾄﾞの時 */
		/*----------------------*/
		/* ＣＩＬインサイド処理 */
		/*----------------------*/
		if (CMN_CheckCILEnable()) {	/* CIL機能有りで、UNISW I:5-7 */
			if (CHK_UNI_CIL_Inside()) {	/* UNISW I:5-4 */
				n = (UBYTE)(16 * ModePara(SYS_DocBlock.Dst.Mode));
				if (n > 64) {
					n = 64;
				}
				while (n--) {							/* dst -> src に変更	Mar 26 '93 */
					/* Caution! c_bufをﾃﾞｺｰﾄﾞ用,a_bufを参照用として使用する */
					rx_status = Ecm_Decode(Sddp,c_buf,a_buf);
					tmp = a_buf;
					a_buf = c_buf;
					c_buf = tmp;
				}
			}
		}
	}
#endif

	do {
		tmp = c_buf;
		c_buf = b_buf;
		b_buf = a_buf;
		a_buf = tmp;
		/*	停止キー	*/
		if (SYS_FaxComStopSwitch()) {
			stop_on = 1;
			break;
		}
#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* By Y.Suzuki 1998/1/30 */
		/* タスクスイッチ調整 By Y.Suzuki 1998/01/30 */
		print_on = CMN_CheckPrinting();
		if (tskno_SCN_DocumentStoreTask != 0xFFFF) {
			scan_on = TRUE;
		}
		else {
			scan_on = 0;
		}
		if (tskno_OPR_KeyTimerTask != 0xFFFF) {
			panel_on = TRUE;
		}
		else {
			panel_on = 0;
		}
		if ((print_on == TRUE) || (scan_on == TRUE) || (panel_on == TRUE)) {
			SCD_MaintenanceSwitch[SCD_MNT_SW_F3] = 32; /* By Y.Suzuki 1998/02/07 */
		}
#endif
		if (!SCD_DirectRx) {
			/** １ラインデコード */
			/* Caution! dec_rl_aをﾃﾞｺｰﾄﾞ用,dec_rl_bを参照用として使用する */
			rx_status = Ecm_Decode(Sddp,a_buf,b_buf);
			if(SCD_DBG_RLOVER == 3) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x08;
			}
			/* 受信ライン数チェック */
			if(++MDM_RxTotalLine > page_length) {
				CodecPageStatus = CDC_PAGE_SEPARATE;
				break;
			}
			if (rx_status == RX_ERROR) {
				/* 松、竹、桜は、ＭＲ，ＭＭＲのデコードの場合、ＭＨのラインでエラーが
				発生したものとして、エラーラインをカウントしている。*/
				/* エラーラインの処理 */
				MDM_RxErrorTotalLine += mr_line;
				if(SYS_DocBlock.Src.Code == SYS_MMR_CODE) {
					CodecPageStatus = CDC_DECODE_ERROR;
					break;
				}
			}

#if(0)		/*	By Y.Suzuki 1997/07/07	*/
//			/**	タスクスイッチング 10 ライン毎１０ｍｓ	*/
//			if ((++tsk_sw_line_no > 10) || (SCD_Det_Rcp)) {/* By Y.Suzuki 1996/07/06 */
//				tsk_sw_line_no = 0; /* By Y.Suzuki 1996/07/06 */
//				if (SYB_MaintenanceSwitch[MNT_SW_F3]) {
//					if (SCD_Det_Rcp) {
//						wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F3]+5);
//					}
//					else {
//						wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F3]);
//					}
//				}
//				else {
//					if (SCD_Det_Rcp) {
//						wai_oneshot(8);
//					}
//					else {
//						wai_oneshot(5);
//					}
//				}
//			}
#endif
			/* 参照ラインを符号化する */
			/** １ラインエンコード */
			/* Caution! enc_rl_aをｴﾝｺｰﾄﾞ用,enc_rl_bを参照用として使用する */
			mem_status = Mem_Encode(Sedp,b_buf,c_buf);
			if(SCD_DBG_PMODE == 5) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x80;
			}
			if(SCD_DBG_ENC_RLSIZE == 1) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x20;
			}
			if(SCD_DBG_ENC_RLSIZE == 3) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x40;
			}
			/* メモリオーバーのチェック */
			if(mem_status == RX_MEM_OVER) {
				CodecPageStatus = CDC_MEM_OVER;
				break;
			}
		}/* DirectRx */
		else {
			/** １ラインデコード */
			/* Caution! dec_rl_aをﾃﾞｺｰﾄﾞ用,dec_rl_bを参照用として使用する */
			rx_status = Ecm_Decode(Sddp,a_buf,b_buf);
			if(SCD_DBG_RLOVER == 3) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x08;
			}
			/* 受信ライン数チェック */
			if(++MDM_RxTotalLine > page_length) {
				CodecPageStatus = CDC_PAGE_SEPARATE;
				break;
			}
			if (rx_status == RX_ERROR) {
				/* 松、竹、桜は、ＭＲ，ＭＭＲのデコードの場合、ＭＨのラインでエラーが
				発生したものとして、エラーラインをカウントしている。*/
				/* エラーラインの処理 */
				MDM_RxErrorTotalLine += mr_line;
				if(SYS_DocBlock.Src.Code == SYS_MMR_CODE) {
					CodecPageStatus = CDC_DECODE_ERROR;
					/*rx_status = RTC;*/
					break;
				}
			}
			else if (rx_status == RTC) {/* RTC 検出後は、タスクスイッチ不要 By Y.Suzuki 1997/07/07 */
				CodecPageStatus = CDC_RTC_DET;
				break;
			}
			else if (rx_status == RX_MEM_OVER) {	/*	ダイレクト受信時メモリオーバー	*/
				CodecPageStatus = CDC_MEM_OVER;
				/* rx_status = RTC;*/
				mem_status = RX_MEM_OVER;
				break;
			}

#if(0)		/*	By Y.Suzuki 1997/07/07	*/
//			/**	タスクスイッチング 10 ライン毎１０ｍｓ	*/
//			if ((++tsk_sw_line_no > 10) || (SCD_Det_Rcp)) {/* By Y.Suzuki 1996/07/06 */
//				tsk_sw_line_no = 0; /* By Y.Suzuki 1996/07/06 */
//				if (SYB_MaintenanceSwitch[MNT_SW_F3]) {
//					if (SCD_Det_Rcp) {
//						wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F3]+5);
//					}
//					else {
//						wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F3]);
//					}
//				}
//				else {
//					if (SCD_Det_Rcp) {
//						wai_oneshot(8);
//					}
//					else {
//						wai_oneshot(5);
//					}
//				}
//			}
#endif
		}
	} while(rx_status != RTC);
	if (rx_status == RTC) {
		MDM_RxTotalLine--;/* RTC の分を減算する By Y.Suzuki 1997/07/08 */
	}
	MDM_EncodeLine = MDM_RxTotalLine;	/*	メモリインデックスに格納するライン数 By Y.Suzuki 1997/01/13	*/
	/* ＲＴＣの書き込み */
/*	CodecPageStatus = CDC_RTC_DET;受信エラーにならない！ By Y.Suzuki 1997/09/29 */
	if (CodecPageStatus == CDC_CONTINUE) {
		CodecPageStatus = CDC_RTC_DET;
	}
	if(mem_status != RX_MEM_OVER) {
		if (SCD_DirectRx) {/*	ダイレクト送信 By Y.Suzuki 1997/02/15	*/
			mem_status = WriteRtcToMem(Sddp);
		}
		else {
			mem_status = WriteRtcToMem(Sedp);
		}
	}
	/* 停止キーのチェック */
	if(stop_on) {
		CodecPageStatus = CDC_STOPPED;
	}

	/* メモリオーバーのチェック */
	else if(mem_status == RX_MEM_OVER) {
		CodecPageStatus = CDC_MEM_OVER;
	}

	/* エラー率のチェック */
	else if (err_rate <= (UWORD)(((UDWORD)(MDM_RxErrorTotalLine)*100)/((UDWORD)MDM_RxTotalLine))) {	/**	エラーライン数が基準値以上の時	*/
		CodecPageStatus = CDC_DECODE_ERROR;
	}
#if(0)	/*	By Y.Suzuki 1996/07/22	*/
**	SoftCDC_Message.Message = MSG_SCDC_PAGE_END;
**	snd_msg(mbxno.SCDC_RxEcmControlTask, &SoftCDC_Message);	/*	エンコード開始メッセージ送信	*/
#endif
	wai_tsk(0xFFFF);
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
}



#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[ダイレクトメモリ受信]
	function	:[
		1.受信符号化モードと蓄積符号化モードがともにＭＭＲの時のみ
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7043)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/06/13]
	author		:[鈴木郁ニ]
*************************************************************************/
void SCD_CheckDirectRx(void)
{
#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
	/* 1998/06/15 Y.Murata
	 * ダイレクト受信でＣＩＬインサイドはできないので、ＣＩＬインサイドの時は
	 * ダイレクト受信しない
	*/
	if (CMN_CheckCILEnable()) {	/* CIL機能有りで、UNISW I:5-7 */
		if (CHK_UNI_CIL_Inside()) {	/* UNISW I:5-4 */
			SCD_DirectRx = 0;
			return;
		}
	}
#endif

	SCD_DirectRx = 0;
	if (!(SYB_MaintenanceSwitch[MNT_SW_F1] & DIRECT_OFF)) {
		if (RxCodingMethod == SYS_MMR_CODE) {
			if (CHK_UNI_StoredMethodMMR()) {
				SCD_DirectRx = 1;
			}
		}
	}
}
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/


#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
static struct	SYS_DocBlockData_t	*cil_docp = {0};	/* B Section By O.Kimoto 1998/08/28 */
static struct	WorkBuf_t	*cil_mr_ref_buf = {0};		/* B Section By O.Kimoto 1998/08/28 */
static struct	WorkBuf_t	*cil_tmp = {0};				/* B Section By O.Kimoto 1998/08/28 */

/*	condition	:[フラッシュＲＯＭ] */
void SetDateRxDocECM(	struct CdcBlk_t *ecp,		/* ソフトコーデックパラメータ */
						struct WorkBuf_t *char_a,	/* 参照ラインバッファのポインタ */
						struct WorkBuf_t *char_b)	/* 符合化ラインバッファのポインタ */
{
	WORD	i;
	WORD	j;
	WORD	mode_cnt;
	WORD	mem_status;
	UWORD	cli_count;
	UBYTE	is_memory_over;

	cli_count = 0;
	is_memory_over = 0;
	cil_mr_ref_buf = &RL3;
	cil_docp = &SYS_DocBlock;
	if (cil_docp->Dst.Mode == SYS_NORMAL) {
		mode_cnt = 1;
	}
	else if ((cil_docp->Dst.Mode == SYS_HFINE) || (cil_docp->Dst.Mode == SYS_SFINE) || (cil_docp->Dst.Mode ==SYS_E_HFINE)) {
		mode_cnt = 4;
	}
	else if (cil_docp->Dst.Mode == SYS_EFINE) {/* R12 * 11.55l/mm TTI LINE 48LINE */
		mode_cnt = 3;
	}
	else {	/* docp->dst.d_mode == FINE or GREY */
		mode_cnt = 2;
	}

	MLT_LST_SetCIL_Image(&FontImageBuffer.Font[CDC_CHARACTER_TX][0][0], SYS_RxMemoryFilePage, (UWORD *)&StandardID[0], 0);

	char_a->Cout = 0;
	char_b->Cout = 0;
	cil_mr_ref_buf->Cout = 0;

	PutRL(char_b, ecp->Img_Size, 0);			/*	MMR用参照ラインクリア	*/
	PutRL(char_a, ecp->Img_Size, 0);			/*	MMR用参照ラインクリア	*/
	PutRL(cil_mr_ref_buf, ecp->Img_Size, 0);	/*	MMR用参照ラインクリア	*/

	/*
	 * Img2Rl()の関数はｷｬﾗｸﾀ送信しか考慮されてへんし、
	 * 内臓ROMにおるから変更できへんし、
	 * 受信時には、この関数はそのまま使えへんから。
	 * むりからSCD_TxModeを書き込みます。
	*/
	SCD_TxMode = cil_docp->Dst.Mode;

	for(i = 0; i < 16; i++) {
		Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0], char_a, cil_docp->Dst.Size);
		/*	符号化ラインと参照ラインが同じＲＬの内容の場合	*/
		Img2Rl(&FontImageBuffer.Font[CDC_CHARACTER_TX][i][0], cil_mr_ref_buf, cil_docp->Dst.Size);

		/** 1ラインエンコード */
		cli_count++;
		mem_status = Mem_Encode(ecp, char_a, char_b);	/* char_a(符号化ライン)､char_b(参照ライン) */
		if (mem_status == RX_MEM_OVER) {
			is_memory_over = 1;
			break;
		}
		for (j = 1; j < mode_cnt; j++) {
			cli_count++;
			mem_status = Mem_Encode(ecp, char_a, cil_mr_ref_buf);
			if (mem_status == RX_MEM_OVER) {
				is_memory_over = 1;
				break;
			}
		}
		cil_tmp = char_b;
		char_b = char_a;
		char_a = cil_tmp;	/* 符号化ライン→参照ライン */
		if (is_memory_over) {
			break;
		}
	}
	/*
	 * ＴＴＩに漢字が使われた時のため全白ライン挿入
	 * 漢字フォントは、１６ライン目もデータあり
	*/
	if (is_memory_over == 0) {
		char_a->Cout = 0;
		PutRL(char_a, ecp->Img_Size, 0);
		cli_count++;
		mem_status = Mem_Encode(ecp, char_a, char_b);	/* char_a(符号化ライン)､char_b(参照ライン) */
		if (mem_status == RX_MEM_OVER) {
			is_memory_over = 1;
		}
	}
	MDM_RxTotalLine += cli_count;
	if (is_memory_over) {	/* 原稿の先端にＣＩＬをつけてる時にメモリオーバーすることはないけどね */
		CodecPageStatus = CDC_MEM_OVER;
		wai_tsk(0xFFFF);
	}
	char_a->Cout = 0;
	char_b->Cout = 0;
	cil_mr_ref_buf->Cout = 0;

	PutRL(char_b, ecp->Img_Size, 0);			/*	MMR用参照ラインクリア	*/
	PutRL(char_a, ecp->Img_Size, 0);			/*	MMR用参照ラインクリア	*/
	PutRL(cil_mr_ref_buf, ecp->Img_Size, 0);	/*	MMR用参照ラインクリア	*/
}
#endif	/* End of (PRO_DATE_SET_RXDOC_CHK == ENABLE) */

