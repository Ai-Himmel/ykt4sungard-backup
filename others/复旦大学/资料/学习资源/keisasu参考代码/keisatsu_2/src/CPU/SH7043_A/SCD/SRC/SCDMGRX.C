/************************************************************************
*	System		: POPLAR
*	File Name	: SCDMGRX.C
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
#include "\src\atlanta\define\mon_pro.h"		/* By Y.SUZUKI 96/06/17 */
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdblk.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\man_pro.h"
/* #include "\src\atlanta\ext_v\extv_mbx.hv" */

#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
 #endif
#endif

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#else
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#endif

#include "\src\atlanta\define\mntsw_d.h"	/* 1997/06/04  By T.Yamaguchi */

 #if (PRO_KEYPANEL == PANEL_POPLAR_L)
#include "\src\atlanta\define\std.h"
 #endif
#if defined(DEU)/*By Y.Suzuki 1998/05/22*/
#include "\src\atlanta\define\mntsw_e.h"
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
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\ext_v\lst_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
void SetDateRxDoc(struct CdcBlk_t *, struct WorkBuf_t *, struct WorkBuf_t *);
#endif

/*************************************************************************
	module		:[Ｇ３メモリ受信]
	function	:[
		1.
	]
	return		:[
	]
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

	受信デコードルーチンエラーチェック強化版をフラッシュＲＯＭに作成。
	]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/12/01]
	author		:[鈴木郁二]
*************************************************************************/
void SCD_G3_MemRxTask(void)
{
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	struct CdcBlk_t encdata,*Sedp;
	struct CdcBlk_t decdata,*Sddp;
	UWORD	err_continuemax;/* 連続エラー許容ライン数 松、竹、桜は２０本ＮｏｒｍａｌでＲＴＮ 返送	*/
	/* エンコード用ＲＬバッファ */
	struct WorkBuf_t *a_buf;
	struct WorkBuf_t *b_buf;
	struct WorkBuf_t *c_buf;
	struct WorkBuf_t *tmp;
	struct WorkBuf_t *reprint;/*エラーライン検出時前ライン記憶用 By Y.Suzuki 1998/06/24*/
	WORD	mem_status;
	WORD	rx_status;
	UWORD	page_length;
	UWORD	err_rate;
	UBYTE	rtn;
	UBYTE	stop_on;
	UWORD	c_err_line, c_err_max, mr_line;/* 連続エラーライン/同更新用パラメータ */
#if defined(DEU)
/*	UWORD	err_count; エラー検出時カウントするライン数（正確なエラー率の計算のため） By Y.Suzuki 1998/05/22 */
	UWORD	err_mode;
#endif
	UWORD	tsk_sw_line_no;
	UBYTE	loop_flg;

	/* タスクスイッチング時間調節する様に変更 By Y.Suzuki 1998/01/30 */
	UBYTE print_on;
	UBYTE scan_on;
	UBYTE panel_on;
	UBYTE i;/*エラーラインリプリント時使用 By Y.Suzuki 1998/06/24*/

#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
	UBYTE	n;
#endif

	MDM_DebugRxCount = 0;	/* debug for ANZU_L R.3.3 1997/12/12 Y.M */ /**	ＥＣＭバッファ読み出しバイト数	*/

	mem_status = 0;
	rx_status = 0;
	stop_on = 0;
	print_on = 0;
	scan_on= 0;
	panel_on = 0;
	/* Ｇ３受信結果格納用大域変数初期化 By Y.Suzuki 1998/01/26 */
	SCD_G3RxResult = RX_PAGE_END;
#if defined(DEU)	/* 1998/05/22 M.H */
	err_mode = 0;
#endif

	/** ソフトコーデック初期化 */
	Sedp = &encdata;
	Sddp = &decdata;
	Sedp->BufMode = MEM1;
	Sddp->BufMode = MDM;

	SoftEncodeInitial(Sedp);
	SoftDecodeInitial(Sddp);

	/* タスクスイッチ調整用メンテナンスＳＷ－Ｆをコピーする By Y.Suzuki 1997/10/17 */
	CopyFromMantSwF();

	/* ＲＬバッファ初期化 */
	RlBufInit(Sddp->Img_Size);
	a_buf = &RL1;
	b_buf = &RL2;
	c_buf = &RL3;
	reprint = &RL4;/* By Y.Suzuki 1998/06/24 */

	c_err_line = 0;
	c_err_max = 0;
	MDM_RxTotalLine = 0;		/**	１ページトータルライン数初期化	*/
	MDM_RxErrorTotalLine = 0;	/**	１ページエラーライン数初期化	*/
	MDM_EncodeLine = 0;
	mr_line = 1;
	if (SYS_DocBlock.Src.Code == SYS_MR_CODE) {
	    mr_line = 2;
#if defined(DEU)
		err_mode = SYB_MaintenanceSwitch[MNT_SW_E5] & ERROR_MODE3;	/* 1998/05/22 M.H */
		if (err_mode == ERROR_MODE1) {
			mr_line = 1;
		}
#endif
		if (SYS_DocBlock.Src.Mode == SYS_FINE) {
			mr_line = mr_line * 2;
#if defined(DEU)
			if (err_mode == ERROR_MODE2) {
				mr_line = 1;
			}
			else if (err_mode == ERROR_MODE1) {
				mr_line = 2;
			}
			if (err_mode == ERROR_MODE3) {
				mr_line = 3;
			}
#endif
		}
		else if (SYS_DocBlock.Src.Mode != SYS_NORMAL) {/* HFINE SFINE */
			mr_line = mr_line * 4;
		}
	}

	SCD_SkipMrEol = 0; /*	By Y.Suzuki 1997/02/19	*/

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
	/*page_length = SYS_DocBlock.DocLength;いらん！By Y.Suzuki 1998/07/15 */
#if (0)	/*	By Y.Suzuki 1997/07/11	*/
//	err_continuemax = 50;	/*	とりあえず By Y.Suzuki 1996/07/12	*/
//	switch(SYS_DocBlock.Src.Mode) {
//	case SYS_FINE:
//		err_continuemax *= 2;
//		break;
//	case SYS_SFINE:
//	case SYS_HFINE:
//		err_continuemax *= 4;
//		break;
//	}
#endif

	/*--------------------------*/
	/*	ＭＡＸキャリア断設定	*/
	/*--------------------------*/
/*	SCD_CarryDownBlock = 300*NO_CARRY_MAXTIME;	1997/06/04  By T.Yamaguchi */
	SCD_CarryDownBlock = 300*(SYB_MaintenanceSwitch[MNT_SW_D0]);	/* ﾒﾝﾃﾅﾝｽｲｯﾁの値を参照する */
	SCD_CarryDownBlock = (UWORD)((UDWORD)(SCD_CarryDownBlock*(ModemBlock.Speed+1)))/256;
	SCD_CarryDownBlock++;	/* 切り上げ処理 */
	SCD_CarryDownByteCnt = 0;
	/*----------------------*/
	/*	エラー判定基準設定	*/
	/*----------------------*/
	err_rate = CHK_RTN_TxRate();	/*	エラー判定基準設定	*/


#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
	/*----------------------------*/
	/* 受信原稿の上に日時を付ける */
	/*----------------------------*/
	if (CMN_CheckCILEnable()) {	/* ＣＩＬ機能有りで、ユニークＳＷ I:5-7 が有効 */
		SetDateRxDoc(Sedp, a_buf, b_buf);
	}
#endif

	/*----------------------*/
	/*	先頭ダミー無視処理	*/
	/*----------------------*/
	loop_flg = 1;	/**	ループ制御フラグ１に設定	*/
	while (loop_flg) {	/**	ＥＯＬ検出／キャリア断するまでループ	*/
		rtn = RxG3_Read();	/**	受信データリード	*/
		if (rtn == RCV_BLOCK) {	/**	受信データ有り	*/
			SCD_G3ReadStatus = rtn;/* 初期化 By Y.Suzuki 1998/01/23 */
			break;
		}
		else if (rtn == RCV_STOP) {	/**	ストップＳｗ検出時	*/
		/*	SCDC_BreakRxTask();	*	受信子タスク終了処理	*/
			SCD_G3RxResult = RX_STOPPED;
			break;/*抜けてました By Y.Suzuki 1997/12/17*/
		}
		else {	/**	受信データ無し	*/
		/*	SCDC_BreakRxTask();	@*	受信子タスク終了処理	*/
			SCD_G3RxResult = RX_CARRIER_DOWN;
			break;/*抜けてました By Y.Suzuki 1997/12/15*/
		}
	}
	if (rtn != RCV_BLOCK) {
		SoftcodecMessage.Message = MSG_SCDC_PAGE_END;
		snd_msg(mbxno.SCDC_MTxCodeConvertTask, &SoftcodecMessage);	/*	エンコード開始メッセージ送信	*/
		wai_tsk(0xffff);
	}

	/*------------------------------*/
	/*	イコライザーホールド処理	*/
	/*------------------------------*/
	if (CHK_V17EqualizerHold()) {	/**	イコライザホールドのメモリスイッチが有効の時	*/
		if (ModemBlock.Type == TYPE_V17) {	/**	モデムタイプがＶ１７の時	*/
			EqualizerHoldOn();	/**	イコライザホールドに設定	*/
		}
	}

#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
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
					rx_status = Mdm_Decode(Sddp,c_buf,a_buf);
					tmp = a_buf;
					a_buf = c_buf;
					c_buf = tmp;
				}
			}
		}
#endif

	/*------------------------------------------------------*/
	/*	ＲＴＣ検出するまでＤＥＣＯＤＥ／ＥＮＣＯＤＥする	*/
	/*------------------------------------------------------*/
	do {
		if (!SCD_SkipMrEol) {/*	デコードエラーが発生した時	*/
			tmp = c_buf;
			c_buf = b_buf;
			b_buf = a_buf;
			a_buf = tmp;
		}
		/*	停止キー	*/
		/*if (SYS_FaxComStopSwitch()) [By Y.Suzuki 1997/12/15 */
		/* SCD_G3ReadStatus は、MdmRead()で RxG3Read()の戻り値がセットされる */
		if (SYS_FaxComStopSwitch() || (SCD_G3ReadStatus == RCV_STOP)) {
			stop_on = 1;
			break;
		}

#if (PRO_KEYPANEL == PANEL_POPLAR_L)/*By Y.Suzuki 1998/01/30 */
		/* タスクスイッチング時間調節する様に変更 By Y.Suzuki 1998/01/30 */
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
		if ((print_on == TRUE) || (scan_on == TRUE) || (panel_on)) {
			/* タスクスイッチングの時間は、32が限界。受信がエラーする（mdm_bufフルのため) */
			SCD_MaintenanceSwitch[SCD_MNT_SW_F3] = 32;
		}
#endif

		/** １ラインデコード */
		/* Caution! dec_rl_aをﾃﾞｺｰﾄﾞ用,dec_rl_bを参照用として使用する */
#if (0)/*By Y.Suzuki 1998/01/26*/
//		/*フラッシュ上のデコードルーチン（エラー検出強化版)使用する By Y.Suzuki 1998/01/22 */
//		if ((SYB_MaintenanceSwitch[MNT_SW_E1] & USE_FLASH_DEC)) {
//			rx_status = Mdm_DecodeFlsRom(Sddp,a_buf,b_buf);
//		}
//		else {
//			rx_status = Mdm_Decode(Sddp,a_buf,b_buf);
//		}
#endif

		rx_status = Mdm_Decode(Sddp,a_buf,b_buf);
		if(SCD_DBG_RLOVER == 1) {
			SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x02;
		}
		/* 受信ライン数チェック */
		if(++MDM_RxTotalLine > page_length) {
			rx_status = RX_OVER;
			break;
		}
		/* キャリア断チェック */
		if (rx_status == RX_CARRIER_DOWN) {
			break;
		}
		if (SCD_G3ReadStatus == RCV_TMOUT) {/* By Y.Suzuki 1997/12/17 */
			/* mdm_decodeでrxg3_readの戻り値を正確に検出できないためここでSCD_G3ReadStatusをチェックします */
			rx_status = RX_CARRIER_DOWN;
			break;
		}

		if (rx_status == RX_ERROR) {
			/* 松、竹、桜は、ＭＲ，ＭＭＲのデコードの場合、ＭＨのラインでエラーが
			発生したものとして、エラーラインをカウントしている。*/
			/* エラーラインの処理 */
			if(SYS_DocBlock.Src.Code == SYS_MMR_CODE) {
				break;
			}
			if (SYB_MaintenanceSwitch[MNT_SW_D7] & ERROR_LINE_CARRY_DOWN) { /* 1997/07/11  By T.Yamaguchi */
				/*if (SCD_CarryDownByteCnt == 0xFFFF) [ By Y.Suzuki 1997/12/15 */
				/* SCD_G3ReadStatus は、MdmRead()で RxG3Read()の戻り値がセットされる */
				if ((SCD_CarryDownByteCnt == 0xFFFF) || (SCD_G3ReadStatus == RCV_TMOUT)) {
				/* 正確なキャリア断のため By Y.Suzuki 1997/06/03 */
					rx_status = RX_CARRIER_DOWN;
					break;
				}
			}
			SCD_SkipMrEol = 1;/*	By Y.Suzuki 1997/02/17	*/
			MDM_RxErrorTotalLine += mr_line;
			c_err_line += mr_line;
			if (c_err_line > c_err_max) {
				c_err_max = c_err_line;
#if(0)	/*	By Y.Suzuki 1997/07/11	*/
//				if (c_err_max > err_continuemax) {
//				/*	SCDC_BreakRxTask();	@*	受信子タスク終了処理	*/
//					SCD_G3RxResult =  RX_CONTI_ERR ;
//					SoftcodecMessage.Message = MSG_SCDC_PAGE_END;
//					snd_msg(mbxno.SCDC_MTxCodeConvertTask, &SoftcodecMessage);	/*	エンコード開始メッセージ送信	*/
//					wai_tsk(0xffff);
//				}
#endif
			}
			PutRL(a_buf,Sddp->Img_Size,0);	/*	RLバッファ全白クリア By Y.Suzuki 1997/09/30	*/

			/* カウントしたエラーライン数分リプリントする By Y.Suzuki 1998/06/24 */
			if (CHK_ErrorLineReplace()) {
				/*エラーライン検出時白ライン置き換えする*/
				PutRL(c_buf,Sedp->Img_Size,0);	/*	RLバッファ全白クリア By Y.Suzuki 1997/09/30	*/
			}
			for (i = 0; i < mr_line; i++) {
				mem_status = Mem_Encode(Sedp,c_buf,reprint);
				if(mem_status == RX_MEM_OVER) {
					break;
				}
			}
			if(mem_status == RX_MEM_OVER) {
				break;
			}

			continue;/*	By Y.Suzuki 1997/02/17	*/
		}
		else {
			c_err_line = 0;
			SCD_CarryDownByteCnt = 0;
		}

#if(0)		/*	By Y.Suzuki 1997/07/07	*/
//		/**	タスクスイッチング 10 ライン毎１０ｍｓ	*/
//		if (++tsk_sw_line_no > 10) {/* By Y.Suzuki 1996/07/06 */
//			tsk_sw_line_no = 0; /* By Y.Suzuki 1996/07/06 */
//			if (SYB_MaintenanceSwitch[MNT_SW_F3]) {
//				wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F3]);
//			}
//			else {
//				wai_oneshot(5);
//			}
//		}
#endif

		/* 参照ラインを符号化する */
		/** １ラインエンコード */
		/* Caution! enc_rl_aをｴﾝｺｰﾄﾞ用,enc_rl_bを参照用として使用する */
		mem_status = Mem_Encode(Sedp,b_buf,c_buf);
		/*参照ラインを記憶する*/
		reprint = c_buf;/*エラーライン検出時リプリント用 By Y.Suzuki 1998/06/24 */
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
			break;
		}
	} while(rx_status != RTC);
	if (rx_status == RTC) {
		MDM_RxTotalLine--;/* RTC の分を減算する By Y.Suzuki 1997/07/08 */
	}
	MDM_EncodeLine = (MDM_RxTotalLine - MDM_RxErrorTotalLine);	/*	メモリインデックスに格納するライン数 By Y.Suzuki 1997/07/10	*/
	/* ＲＴＣの書き込み */
	if(mem_status != RX_MEM_OVER) {
		mem_status = WriteRtcToMem(Sedp);
	}

	/* 停止キーのチェック */
	if(stop_on) {
	/*	SCDC_BreakRxTask();	*	受信子タスク終了処理	*/
		SCD_G3RxResult =  RX_STOPPED ;
	}

	/* メモリオーバーのチェック */
	/* キャリア断チェック */
	if((mem_status == RX_MEM_OVER) || (rx_status == RX_CARRIER_DOWN) || (rx_status == RX_ERROR)) {
	/*	SCDC_BreakRxTask();	*	受信子タスク終了処理	*/
		if (mem_status == RX_MEM_OVER) {
			SCD_G3RxResult =  (UBYTE)mem_status ;
		}
		else {
			SCD_G3RxResult = (UBYTE)rx_status;
		}
	}

	/* エラー率のチェック */
	if (rx_status == RTC) {
		/*受信ライン数より、エラーラインの方が多い（ゴミデータ内にＲＴＣを検出）By Y.Suzuki 1998/01/05*/
		/*場合は、キャリア断にする。*/
		if (MDM_RxTotalLine <= MDM_RxErrorTotalLine) {
			SCD_G3RxResult = RX_CARRIER_DOWN;
		}
		else {
			if (err_rate <= (UWORD)(((UDWORD)(MDM_RxErrorTotalLine)*100)/((UDWORD)MDM_RxTotalLine))) {	/**	エラーライン数が基準値以上の時	*/
			/*	SCDC_BreakRxTask();	*	受信子タスク終了処理	*/
				SCD_G3RxResult = RX_ERROR;
			}
		}
	}
	/* SCDC_BreakRxTask();	*	受信子タスク終了処理	*/
	/*	1ページ受信完了メッセージセット	*/
	SoftcodecMessage.Message = MSG_SCDC_PAGE_END;
	snd_msg(mbxno.SCDC_MTxCodeConvertTask, &SoftcodecMessage);
	wai_tsk(0xFFFF);
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
}



#if (PRO_DATE_SET_RXDOC_CHK == ENABLE)
/*	condition	:[フラッシュＲＯＭ] */
static struct	SYS_DocBlockData_t	*cil_docp = {0};	/* B Section By O.Kimoto 1998/08/28 */
static struct	WorkBuf_t	*cil_mr_ref_buf = {0};		/* B Section By O.Kimoto 1998/08/28 */
static struct	WorkBuf_t	*cil_tmp = {0};				/* B Section By O.Kimoto 1998/08/28 */
void SetDateRxDoc(	struct CdcBlk_t *ecp,		/* ソフトコーデックパラメータ */
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

	/* とりあえずＴＴＩ */
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
		SCD_G3RxResult = RX_MEM_OVER;
		SoftcodecMessage.Message = MSG_SCDC_PAGE_END;
		snd_msg(mbxno.SCDC_MTxCodeConvertTask, &SoftcodecMessage);
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

