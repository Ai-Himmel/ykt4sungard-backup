/************************************************************************
*	System		: POPLAR
*	File Name	: SCDTX.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"		/* By Y.SUZUKI 96/06/17 */
#include "\src\atlanta\define\mntsw_f.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
/* #include "\src\atlanta\ext_v\extv_mbx.hv"By Y.Suzuki 1996/10/18 */
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\sysdblk.h"
#include "\src\atlanta\define\fcm_pro.h"
#include "\src\memsw\define\mem_sw_b.h"
#include "\src\atlanta\define\unisw_b.h"

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
#include "\src\atlanta\define\syscomf.h"	/*	スキャナ送信ＴＴＩ送出のため By Y.Suzuki 1996/09/26	*/
#include "\src\atlanta\define\uni_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\std.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scdrlbuf.h"
#include "\src\cpu\sh7043_a\scd\define\scd_def.h"
#include "\src\cpu\sh7043_a\scd\define\scd.h"	/* By Y.Suzuki 1997/01/17 */
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#else
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\scdrlbuf.h"
#include "\src\atlanta\scd\define\scd_def.h"
#include "\src\atlanta\scd\define\scd.h"	/* By Y.Suzuki 1997/01/17 */
#include "\src\atlanta\scd\define\scdpro.h"
#endif

/* extern UWORD SCD_EOL_WriteCount;		@*	By Y.Suzuki 1997/04/14	*/

/*	By Y.Suzuki 1997/12/3	*/
extern UWORD	tskno_SCN_DocumentStoreTask;
extern UWORD	tskno_PRN_ImagePrintTask;
extern UWORD	tskno_OPR_KeyTimerTask;

/*************************************************************************
	module		:[ソフトコーデックＥＣＭバッファへ符号化タスク]
	function	:[
		1.エンコード、デコード初期化
		2.メモリオープン
		3.縮小処理(副走査)
		4.１ラインデコード
		5.縮小加工(主走査)
		6.１ラインエンコード
		7.５ｍｓ／１００Ｌｉｎｅの割合でタスクスイッチングを入れるBy Y.SUZUKI 96/06/17
	]
	return		:[
													MG3	MECM	SG3	SECM
			TX_PAGE_END					0			○	○		○	○		1ﾍﾟｰｼﾞ送信完了
			TX_BLOCK_END				1			×	○		×	○		64KByte送信完了
			TX_STOPPED					2			○	○		○	○		停止ＳＷ　ＯＮ
			TX_DOC_ERR					3			×	×		○	○		原稿繰り込み不良
			TX_LAMP_ERR					4			×	×		○	○		ﾗﾝﾌﾟｴﾗｰ
			TX_FILE_ERR					5			○	○		×	×		該当するﾒﾓﾘﾌｧｲﾙが存在しない
			TX_MEM_ERR					7			○	○		×	×		画像ﾒﾓﾘ画品質不良
			TX_1M_OVER					8 			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
			TX_SEPARATE					9 			×	×		○	○		F網設定時、送信がA4 2枚分に達した
	]
	common		:[Ｇ３／ＥＣＭ共通]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1996/3/15]
	author		:[鈴木郁二]
*************************************************************************/
/* UWORD SCD_Debg_line_no;*/
/* UBYTE SCD_DirectTx;*/
UBYTE SCD_DebugSwitch = 0;/*By Y.Suzuki 1998/01/20*/
void SCDC_MTxCodeConvertTask(void)
/* void SCDC_G3_MemTx(void) */
{
#if (PRO_COM_CODEC_TYPE == SOFTWARE)
	struct CdcBlk_t encdata,*Sedp;
	struct CdcBlk_t decdata,*Sddp;
	UBYTE	reduce_f;
	UBYTE	mode_skip,n;
	UBYTE	stop_on;
	WORD	status;
	UBYTE	next_line_no;
	UBYTE	first_line_encode;	/*	ＴＴＩを除く画データの先頭行をエンコードする直前まで１	*/
	/* ＲＬバッファ */
	struct WorkBuf_t *a_buf;
	struct WorkBuf_t *b_buf;
	struct WorkBuf_t *c_buf;
	struct WorkBuf_t *tmp;
	struct reduction_t reduc_data,*rp;
	UWORD tsk_sw_line_no;
	UBYTE print_on;
	UBYTE scan_on;
	UBYTE panel_on;

	rp = &reduc_data;
	status = 0;/* OK */
	stop_on = 0;
	tsk_sw_line_no = 0;
/*	SCD_Debg_line_no = 0; */
	next_line_no = 0;
	print_on = 0;
	scan_on= 0;
	panel_on = 0;
	first_line_encode = 1;	/*	By Y.Suzuki 1997/08/25	*/

	/** コーデック初期化 */
	ScdcErrFlag = 0;
	Sedp = &encdata;
	Sddp = &decdata;
	CodecPageStatus = CDC_READY;
	EncodeDataCount = 0;
	Sedp->BufMode = ECM_BUF;
	Sddp->BufMode = MEM1;
	SoftEncodeInitial(Sedp);
	SoftDecodeInitial(Sddp);
	SCD_EOL_WriteCount = 0;		/*	By Y.Suzuki 1997/04/14	*/

	if (SCD_DebugSwitch) {
		SCD_SkipMrEol = 0; /*	By Y.Suzuki 1998/1/20	*/
	}

	/* タスクスイッチ調整用メンテナンスＳＷ－Ｆをコピーする By Y.Suzuki 1997/10/17 */
	CopyFromMantSwF();

	/** ＲＬバッファアドレスセット */
	/*EncRlBufInit(Sedp->Img_Size);縮小の場合もSrcのｲﾒｰｼﾞｻｲｽﾞで初期化*/
	/*------3本のバッファを初期化する
	EncRlBufInit(Sddp->Img_Size);
	DecRlBufInit(Sddp->Img_Size);
	--------*/
	RlBufInit(Sddp->Img_Size);
	a_buf = &RL1;
	b_buf = &RL2;
	c_buf = &RL3;

	/*	SCD 大域変数ヘ移動 By Y.Suzuki 1997/03/07	*/
	SCD_TxMode = TxMode;

	/*	ダイレクト送信有無 By Y.Suzuki 1997/02/14	*/
	SCD_CheckDirectTx();
	if (SCD_DirectTx) {
		Sddp->Wp = Sedp->Wp;
		Sddp->Wp->Buf = Sedp->Wp->Buf;
		Sddp->Wp->Adr = Sedp->Wp->Adr;
		Sddp->Wp->Bit = Sedp->Wp->Bit;
	}

	/** 縮小制御 */
	mode_skip = GetModeSkip(SYS_DocBlock.Src.Mode,SYS_DocBlock.Dst.Mode);
	reduce_f = SetReduce(&(SYS_DocBlock.Src), &(SYS_DocBlock.Dst));
	if(reduce_f == 1) {
		SetSkip(A3_TO_A4,rp);
	}
	else if(reduce_f == 2) {
		SetSkip(A3_TO_B4,rp);
	}
	else if(reduce_f == 3) {
		SetSkip(B4_TO_A4,rp);
	}
	else {
		SetSkip(100,rp);
	}

	CodecPageStatus = CDC_CONTINUE;			/**	初期化 By Y.Suzuki 1997/09/19	*/
	/** キャラクタ送信 */
	if(FCM_PtnrChkTTI_TxAvailable() == TTI_TX_AVAILABLE) {/** ＴＴＩ送信あり */
		SF_ECM_CharTx(Sedp,a_buf,b_buf);
		/* 参照ラインのクリア By Y.Suzuki 1997/08/26  */
		a_buf->Cout = 0;
		b_buf->Cout = 0;
		c_buf->Cout = 0;
		PutRL(a_buf,Sddp->Img_Size,0);
		PutRL(b_buf,Sddp->Img_Size,0);
		PutRL(c_buf,Sddp->Img_Size,0);
#if(0)	/*	By Y.Suzuki 1997/08/26	*/
		tmp = c_buf;
		c_buf = a_buf;
		a_buf = tmp;
#endif
		/* CodecPageStatus = CDC_CONTINUE;ここでは、遅い T3.1 になることがある */
		/* メモリ読み出し DMA 256 単位でよいか？ */
	/*	if (CHK_UNI_TTI_Inside() == TTI_INSIDE) [* USA以外のため 96/05/16 By T.Yamaguchi */
		if ((CHK_UNI_TTI_Inside() == TTI_INSIDE) || (CommandFileOptionItem == SYS_CIPHER_TX)) {
			/* スクランブル送信時TTIアウトサイドにすると元に戻らない。By Y.Suzuki 1998/04/23 */
			/* 16ラインデコード読み飛ばし */
			if(SCD_DirectTx == 1) {	/*	ＴＴＩインサイドのときは、ダイレクト送信できない By Y.Suzuki 1997/08/13	*/
				SCD_DirectTx = 0;
			}
			n = (UBYTE)(16 * ModePara(SYS_DocBlock.Src.Mode));
			if (n > 64) {/* By Y.Suzuki 1997/08/28 */
				n = 64;
			}
			while (n--) {							/* dst -> src に変更	Mar 26 '93 */
				/* Caution! a_bufをﾃﾞｺｰﾄﾞ用,b_bufを参照用として使用する */
				status = Mem_Decode(Sddp,c_buf,a_buf);
				if(SCD_DBG_RLOVER == 2) {
					SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x04;
				}
				tmp = a_buf;
				a_buf = c_buf;
				c_buf = tmp;
			}
		}
	}
/* By Y.Suzuki 1997/10/17
*	if (SYS_FaxComTxType == SYS_SCANNER_TX) {
*		EcmBufferBaseWritePoint = 0x1000000 + Sedp->Wp->Adr;
*		return;
*	}
*/

	/*	コーデックステータス とりあえず By Y.Suzuki 1996/07/04	*/
	/* CodecPageStatus = CDC_CONTINUE;			*	初期化	*/
	n = 0;
	do {	/*1ラインごとの処理。RTC検出までループ*/
		if (SCD_DebugSwitch) {/*By Y.Suzuki 1998/01/20*/
			if (!SCD_SkipMrEol) {
				tmp = c_buf;
				c_buf = b_buf;
				b_buf = a_buf;
				a_buf = tmp;
			}
		}
		else {
			tmp = c_buf;
			c_buf = b_buf;
			b_buf = a_buf;
			a_buf = tmp;
		}
		/* 停止キー確認、極性反転チェック */
		/* if (SYS_FaxComStopSwitch() == 1) [	*	ストップＳｗＯＮの時	*/
		if (MDM_TxStopSwFlag == 1) {	/**	ストップＳｗＯＮの時	*/
			stop_on = 1;
			CodecPageStatus = CDC_STOPPED;
			break;
		}
		if (n != 1) {/* EFINE --> FINE への縮小ではない */
			n = mode_skip;
		}
		/* 自動タスクスイッチ時間調節の処理 By Y.Suzuki 1997/08/13 */
		/* パネル使用中追加 By Y.Suzuki 1997/10/08 */
#if (0)
**		scan_on = CMN_CheckScanEnable();
**		panel_on = CMN_CheckPanelBusy();
**		タスク id を直接参照 By Y.Suzuki 1997/12/04
#endif
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
		if ((print_on == TRUE) && (scan_on == TRUE)) {
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* By Y.Suzuki 1997/12/05  */
/*	ポプラＬでＢ４－Ａ４の縮小Ｇ３送信＋コピープリント＋コピースキャンでエラーラインがあったので
By Y.Suzuki 1997/12/05	*/
			SCD_MaintenanceSwitch[SCD_MNT_SW_F2] = 80;
#else
			SCD_MaintenanceSwitch[SCD_MNT_SW_F2] = 60;
#endif
	}
		else if ((print_on == TRUE) || (scan_on == TRUE)) {
			SCD_MaintenanceSwitch[SCD_MNT_SW_F2] = 30;
		}
		else {
			if (panel_on) {
				SCD_MaintenanceSwitch[SCD_MNT_SW_F2] = 15;
			}
			else {
				SCD_MaintenanceSwitch[SCD_MNT_SW_F2] = 0;
			}
		}
		if (reduce_f) {
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* By Y.Suzuki 1997/12/05  */
/*	ポプラＬでＢ４－Ａ４の縮小Ｇ３送信＋コピープリント＋コピースキャンでエラーラインがあったので
By Y.Suzuki 1997/12/05	*/
			SCD_MaintenanceSwitch[SCD_MNT_SW_F2] += 40;
#else
			SCD_MaintenanceSwitch[SCD_MNT_SW_F2] += 30;
#endif
		}
		if (!SCD_DirectTx) {
			do {
				do {
					/** １ラインデコード */
					/* Caution! a_bufをﾃﾞｺｰﾄﾞ用,b_bufを参照用として使用する */
					status = Mem_Decode(Sddp,a_buf,b_buf);
					if(SCD_DBG_RLOVER == 2) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x04;
					}
					/*For Debug By Y.Suzuki 1998/01/20*/
					if ((status == TX_MEM_ERR) && (SYS_DocBlock.Src.Code == SYS_MR_CODE) && SCD_DebugSwitch) {
						SCD_SkipMrEol = 1;
						PutRL(a_buf,Sddp->Img_Size,0);	/*	RLバッファ全白クリア By Y.Suzuki 1997/09/30	*/
						continue;/*	By Y.Suzuki 1997/02/17	*/
					}
					if ((status == TX_MEM_ERR) && (SYS_DocBlock.Src.Code == SYS_MMR_CODE)) {
						CodecPageStatus = CDC_DECODE_ERROR;
						ScdcErrFlag = 1;
						status = RTC;
						break;
					}
					if (status == RTC) {
						break;
					}
					if(n && ReductionFromR12 != 2) {/** モード変更による副走査間引き処理 */
						tmp = a_buf;
						a_buf = b_buf;
						b_buf = tmp;
					}
					else if (ReductionFromR12 == 2 && n == 2) {/* EFINEからFINEへの縮小あり 11.55-->7.7  */
						n--;
						break;
					}
					else if (n) {
						tmp = a_buf;
						a_buf = b_buf;
						b_buf = tmp;
					}
				}while(n--);
				if(!reduce_f){
					break;
				}
				else if (reduce_f == 6) {/** ＨＦＩＮＥからのモード変更のみあり By Y.Suzuki 1997/01/17  */
					RedLine(Sddp,b_buf,reduce_f);
					if(SCD_DBG_OldRlSize) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 1;
					}
					if(SCD_DBG_RLOVER == 4) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x10;
					}
					break;
				}
				else if (reduce_f == R12_TO_R8) {/** Ｒ１２からＲ８のモード変更のみあり By Y.Suzuki 1997/11/13  */
					RedLineR12ToR8(Sddp,b_buf,reduce_f);
					if(SCD_DBG_OldRlSize) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 1;
					}
					if(SCD_DBG_RLOVER == 4) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x10;
					}
					break;
				}
				else if(!Skip(rp)){/** 主走査縮小による副走査間引き処理 */
					/** 主走査縮小 */
#if (0) /* By Y.Suzuki 1997/01/16 */
					if (ReductionFromHfine) {/* R16 --> R8 の縮小を行う。縮小率５０％ By Y.Suzuki 1997/01/16 */
						RedLine(Sddp,b_buf,reduce_f);
					}
#endif
					if (ReductionFromR12) {/* R12からの縮小あり	By Y.Suzuki 1997/11/13	*/
						RedLineR12ToR8(Sddp,b_buf,reduce_f);
					}
					else {
						RedLine(Sddp,b_buf,reduce_f);
					}
					if(SCD_DBG_OldRlSize) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 1;
					}
					if(SCD_DBG_RLOVER == 4) {
						SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x10;
					}
					break;
				}
				if (status == RTC) {
					next_line_no = 1;
					break;
				}
				tmp = a_buf;
				a_buf = b_buf;
				b_buf = tmp;
				if (n != 1) {/* EFINE --> FINE への縮小ではない */
					n = mode_skip;
				}
			}while(1);
			/*	ECMWrite()内で２５６バイトに１ｍｓタスク切替えする By Y.Suzuki 1996/08/23	*/
			/**	タスクスイッチング 5ms １００ライン毎 で256バイトデータがそろった場合	*/
#if(0)
//		/*	if((++tsk_sw_line_no > 10) && TxStartFlag) [ By Y.Suzuki 1996/08/16 */
//			if((++tsk_sw_line_no > 10) && SCD_DirectTx) {/* 復活 By Y.Suzuki 1997/08/13 */
//				/* ダイレクト送信時タスクスイッチ用 */
//				tsk_sw_line_no = 0; /* By Y.Suzuki 1996/07/06 */
//		/*	if((++SCD_Debg_line_no > 10) && TxStartFlag) [
//				SCD_Debg_line_no = 0; */
//				if (SYB_MaintenanceSwitch[MNT_SW_F2]) {
//					wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F2]);
//				}
//				else {
//					wai_oneshot(5);
//				}
//			}
#endif
			if (next_line_no) {/* 縮小送信のRTC検出時、最後のラインが読み飛ばしのとき */
				break;
			}
			/** １ラインエンコード */
			/* Caution! enc_rl_aをｴﾝｺｰﾄﾞ用,enc_rl_bを参照用として使用する */
			SCD_EOL_WriteCount++;		/*	By Y.Suzuki 1997/04/14	*/
			if (reduce_f && first_line_encode) {/* 縮小送信時の参照ライン をセット By Y.Suzuki 1997/08/25 */
				c_buf->Cout = 0;
				PutRL(c_buf,Sedp->Img_Size,0);
				first_line_encode = 0;
			}
			Ecm_Encode(Sedp,b_buf,c_buf);
			if(SCD_DBG_PMODE == 5) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x80;
			}
			if(SCD_DBG_ENC_RLSIZE == 1) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x20;
			}
			if(SCD_DBG_ENC_RLSIZE == 3) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x40;
			}
		}
		else {/*	ダイレクト送信 By Y.Suzuki 1997/02/14	*/
			status = Mem_Decode(Sddp,a_buf,b_buf);
			if(SCD_DBG_RLOVER == 2) {
				SYB_MaintenanceSwitch[MNT_SW_F0] |= 0x04;
			}
			if ((status == TX_MEM_ERR) && (SYS_DocBlock.Src.Code == SYS_MMR_CODE)) {
				CodecPageStatus = CDC_DECODE_ERROR;
				ScdcErrFlag = 1;
				status = RTC;
				break;
			}
			if(++tsk_sw_line_no > 10) {/* 復活 By Y.Suzuki 1996/08/16 */
				/* ダイレクト送信時タスクスイッチ用 */
				tsk_sw_line_no = 0; /* By Y.Suzuki 1996/07/06 */
#if (0)/* EcmWrite でやってるので不要 By Y.Suzuki 1997/11/29 */
**				if (SYB_MaintenanceSwitch[MNT_SW_F2]) {
**					wai_oneshot(SYB_MaintenanceSwitch[MNT_SW_F2]);
**				}
**				else {
**					wai_oneshot(5);
**				}
#endif
			}
		}
	} while(status != RTC);
	/* ｒｔｃ書き込み */
	if (SCD_DirectTx) {/*	ダイレクト送信 By Y.Suzuki 1997/02/15	*/
#if defined(DEU)
		WriteRtcToEcmByte(Sddp);
#else
		WriteRtcToEcm(Sddp);
#endif
	}
	else {
		SCD_EOL_WriteCount = 0xFFFF;		/*	By Y.Suzuki 1997/04/14	*/
#if defined(DEU)
		WriteRtcToEcmByte(Sedp);
#else
		WriteRtcToEcm(Sedp);
#endif
	}
	if((CodecPageStatus == CDC_CONTINUE) && !ScdcErrFlag) {
		CodecPageStatus = CDC_RTC_DET;
	}
	/* コーデック終了処理ソフトコーデックは、特にやることない */
	/* 戻り値セット、ページ終了、停止キー有り */
	else if(stop_on) {
		CodecPageStatus = CDC_STOPPED;
	}
	/* 送信開始フラグＯＮ */
	/*
	** 64K以上のPIX送出中に通信予約ｸﾘｱするとﾙｰﾌﾟするので条件削除する
	** 1997/08/12  By T.Yamaguchi	*/
	/* if(!ScdcErrFlag & !stop_on) {  */
		if(!TxStartFlag) {
			TxStartFlag = 1;
		}
		/* エンコードデータ数セット */
	/* } */
	/* タスク終了 */
	/* exi_tsk(); By Y.Suzuki 1997/01/18 */
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[スキャナ送信用ＴＴＩ送信]
	function	:[
		1.エンコード、デコード初期化
	]
	return		:[
	]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1996/9/26]
	author		:[鈴木郁二]
*************************************************************************/
/* スタックオーバーフロー対策 By Y.Suzuki 1998/02/10 */
static struct CdcBlk_t encdata = {0};		/* B Section By O.Kimoto 1998/08/28 */
static struct CdcBlk_t *ttiSedp = {0};		/* B Section By O.Kimoto 1998/08/28 */
static struct WorkBuf_t *tti_a_buf = {0};	/* B Section By O.Kimoto 1998/08/28 */
static struct WorkBuf_t *tti_b_buf = {0};	/* B Section By O.Kimoto 1998/08/28 */
static struct WorkBuf_t *tti_c_buf = {0};	/* B Section By O.Kimoto 1998/08/28 */
static struct WorkBuf_t *tti_tmp = {0};		/* B Section By O.Kimoto 1998/08/28 */

void SCD_TxTTI_OnScanTx(void)
{
#if (0) /*By Y.Suzuki 1998/02/10*/
/*	struct CdcBlk_t encdata;By Y.Suzuki 1998/02/10 */
//	struct CdcBlk_t *Sedp;
/*	struct CdcBlk_t decdata;By Y.Suzuki 1998/02/10 */
//	struct CdcBlk_t *Sddp;
//	UBYTE	stop_on;
//	WORD	status;
	/* ＲＬバッファ */
//	struct WorkBuf_t *a_buf;
//	struct WorkBuf_t *b_buf;
//	struct WorkBuf_t *c_buf;
//	struct WorkBuf_t *tmp;
#endif

/*	status = 0;* OK */
/*	stop_on = 0;*/
	/*tsk_sw_line_no = 0;*/
	/** コーデック初期化 */
	ScdcErrFlag = 0;
	ttiSedp = &encdata;
	EncodeDataCount = 0;
	ttiSedp->BufMode = ECM_BUF;
	SoftEncodeInitial(ttiSedp);

	/** ＲＬバッファアドレスセット */
	RlBufInit(ttiSedp->Img_Size);
	tti_a_buf = &RL1;
	tti_b_buf = &RL2;
	tti_c_buf = &RL3;

	SCD_TxMode = TxMode;

	/** キャラクタ送信 */
	/* if(FCM_PtnrChkTTI_TxAvailable() == TTI_TX_AVAILABLE) [@** ＴＴＩ送信あり */
		SF_ECM_CharTx(ttiSedp,tti_a_buf,tti_b_buf);
		tti_tmp = tti_c_buf;
		tti_c_buf = tti_a_buf;
		tti_a_buf = tti_tmp;
		CodecPageStatus = CDC_CONTINUE;			/**	初期化	*/
		/* メモリ読み出し DMA 256 単位でよいか？ */
	/*]*/
	/*EcmBufferBaseWritePoint = (UDWORD)(0x1000000 + EncodeDataCount);*/
	EcmBufferBaseWritePoint = (UDWORD)(SCD_EcmBufTopAddress + EncodeDataCount);
	return;
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
}


#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[ダイレクト送信チェック]
	function	:[
		1.原稿巾、送信巾を比較
		2.蓄積モード、送信モードを比較
		3.蓄積符号化方式、送信符号化方式を比較
		4.3条件とも一致したらダイレクト送信する
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH(SH7041)]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1997/02/14]
	author		:[鈴木郁ニ]
*************************************************************************/
void SCD_CheckDirectTx(void)
{
	SCD_DirectTx = 0;
	if (!(SYB_MaintenanceSwitch[MNT_SW_F1] & DIRECT_OFF)) {
		if (SCD_TxMode == SYS_DocBlock.Src.Mode) {
			if (TxCodingMethod == SYS_DocBlock.Src.Code) {
				if (TxWidth == DocWidth) {
					SCD_DirectTx = 1;
				}
			}
		}
	}
}

#if defined(DEU)
/*************************************************************************
	module		:[ＥＣＭバッファにＲＴＣ書き込み]
	function	:[
		1.RTCの書き込み後、バイトバウンダリにする。（RTC6個を間違いなく送出するため）
	]
	return		:[]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[SCDC]
	date		:[1998/5/21]
	author		:[鈴木郁二]
*************************************************************************/
void WriteRtcToEcmByte(struct CdcBlk_t *cp)
{
	UBYTE bit_num,eol_cnt;
	UWORD data;
	eol_cnt = 6;/* eol の数 */
	bit_num = 12;
	data =0x800;/* For MH */
	if(cp->Coding == SYS_MR_CODE) {
		bit_num = 13;
		data = 0x1800;
	}
	else if(cp->Coding == SYS_MMR_CODE) {
		/* For EOFB */
		eol_cnt = 6;
	}
	do {
		EcmWrite(cp->Wp,bit_num,data);
		eol_cnt--;
	}while(eol_cnt);
	switch(cp->Wp->Bit) { /* 96/05/13 S.Wang (requested by Y.Suzuki) */
	case 0x01:
		break;
	case 0x02:
		EcmWrite(cp->Wp, 7, 0x00);
		break;
	case 0x04:
		EcmWrite(cp->Wp, 6, 0x00);
		break;
	case 0x08:
		EcmWrite(cp->Wp, 5, 0x00);
		break;
	case 0x10:
		EcmWrite(cp->Wp, 4, 0x00);
		break;
	case 0x20:
		EcmWrite(cp->Wp, 3, 0x00);
		break;
	case 0x40:
		EcmWrite(cp->Wp, 2, 0x00);
		break;
	case 0x80:
		EcmWrite(cp->Wp, 1, 0x00);
		break;
	default:
		break;
	}
}
#endif/*DEU*/

#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/
