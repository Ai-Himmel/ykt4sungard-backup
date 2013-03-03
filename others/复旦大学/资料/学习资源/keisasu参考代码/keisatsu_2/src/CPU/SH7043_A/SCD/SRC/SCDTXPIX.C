/************************************************************************
*	System		: POPLAR
*	File Name	: SCDTXPIX.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
/*---------------------------------------------------------------------------------------*/
/*	プロジェクト : KIRI/MOMIJI															 */
/*	ファイル名	 : scdtxpix.c															 */
/*	モジュール																			 */
/*				 :	unsigned char	far		SCDC_TxPix(unsigned char, unsigned char)	 */
/*				 :	void			far		SCDC_BreakTxTask(void)						 */
/*				 :	unsigned char	near	SF_EcmTx(void)								 */
/*	作成者		 : 曽根岡																 */
/*	RISC用変更	 : 鈴木																	 */
/*	日	付		 : 94.5.10																 */
/*	概	要		 : 画データ送信関連処理													 */
/*	修正履歴	 :																		 */
/*---------------------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\fcm_def.h"
#include "\src\atlanta\define\man_pro.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\memsw\define\mems_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sys_stat.h"
/* #include "\src\atlanta\sh\define\def_tib.hv"By Y.Suzuki 1996/10/18 */

#include "\src\atlanta\define\idp_def.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\scn_def.h"
#include "\src\atlanta\define\scn_pro.h"

#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h"


#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#include "\src\atlanta\mdm\pana\define\mdm_pro.h"
#else
 #if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI2) || defined(HINOKI3)/* SMuratec H.C.H 2003.07.11 */
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\define\mdm_pro.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
 #endif
#endif

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\scd\define\scd_def.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#else
#include "\src\atlanta\sh7043\define\def_tib.h"
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\scd\define\scd_def.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#endif


/* static UWORD tskno_DummyPixTimer = 0; MDMの大域変数になった By Y.Suzuki 1996/12/27 */
static UWORD tskno_SCDC_MTxCodeConvertTask = 0;
/* static UWORD tskno_CDC_MTxCodeConvertTask = 0;*/

#if (PRO_COM_CODEC_TYPE == SOFTWARE)
/*************************************************************************
	module		:[送信ＰＩＸ]
	function	:[
		1.送信コントロールタスクを起動（エンコード制御）
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
		TX_1M_OVER					8			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
		TX_SEPARATE					9			○	○		○	○		F網設定時、送信がA4 2枚分に達した
			○：戻り値あり
			×：戻り値なし
			△：未定
	]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[
		もみじでは"エンコードV53DMA終了割り込み監視タスク"
		のクリエイトはしません (MDM_EncodeDMA_TC_DetectTask)
	]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1993/12/21]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE	SCDC_TxPix(
UBYTE	ecm_type,
UBYTE	sm_type)
{
	UBYTE	rtn;
	TxStartFlag = 0;	/**	送信開始フラグ（エンコードデータ準備ＯＫ）	*/

	/*	通信の最初でCodecPageStatus = CDC_READYに設定しておく	*/

	/*------------------*/
	/*	送信種別設定	*/
	/*------------------*/
	if (ecm_type == ECM_OFF) {	/**	Ｇ３送信の時	*/
		if(SYS_DocBlock.MSE_Method == NOMSE) {
			SCD_MinimumLineSize = SYS_DocBlock.MinimumLineSize;/*	By Y.Suzuki 1997/04/03	*/
		}
		else {
			SCD_MinimumLineSize = 0xFFFF;
		}
		switch (sm_type) {	/**	送信種別	*/
		case	TX_SCAN:	/**	スキャナ送信の時	*/
			CommunicateType = TX_G3_SCAN;	/**	交信タイプをＧ３スキャナにセット	*/
			break;
		case	TX_MEMORY:	/**	メモリ送信の時	*/
			CommunicateType = TX_G3_MEM;	/**	交信タイプをＧ３メモリにセット	*/
			break;
		case	TX_CVR:	/**	カバーページ送信の時	*/
			CommunicateType = TX_G3_CVR;	/**	交信タイプをＧ３カバーページにセット	*/
			break;
		case	TX_RCR:	/**	受領証送信の時	*/
			CommunicateType = TX_G3_RCR;	/**	交信タイプをＧ３受領証にセット	*/
			break;
		}
	}
	else {	/**	ＥＣＭ送信の時	*/
		SCD_MinimumLineSize = 0xFFFF;/*	By Y.Suzuki 1997/04/03	*/
		switch (sm_type) {	/**	送信種別	*/
		case	TX_SCAN:	/**	スキャナ送信の時	*/
			CommunicateType = TX_ECM_SCAN;	/**	交信タイプをＥＣＭスキャナにセット	*/
			break;
		case	TX_MEMORY:	/**	メモリ送信の時	*/
			CommunicateType = TX_ECM_MEM;	/**	交信タイプをＥＣＭメモリにセット	*/
			break;
		case	TX_CVR:	/**	カバーページ送信の時	*/
			CommunicateType = TX_ECM_CVR;	/**	交信タイプをＥＣＭカバーページにセット	*/
			break;
		case	TX_RCR:	/**	受領証送信の時	*/
			CommunicateType = TX_ECM_RCR;	/**	交信タイプをＥＣＭ受領証にセット	*/
			break;
		case	TX_BKUPRAM: /** 高速リモート診断バックアップデータ送信の時	*/
			CommunicateType = TX_ECM_BKUPRAM;	/** 交信タイプを高速リモート診断データ	*/
			break;
		}
	}

	/*------------------------------*/
	/*	送信種別各タスク起動処理	*/
	/*------------------------------*/
	switch (sm_type) {	/**	送信種別	*/

	case TX_MEMORY:	/**	メモリ送信の時	*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)*/
		/* ここからＲＩＳＣのため、ソフトコーデックによるメモリ送信の変更 96/3/15 Y.Suzuki */
		/* メモリリードオープン */
		if (CodecPageStatus != CDC_BLOCK_END) {	/**	ECM ブロックエンドの時は、メモリオープンしない By Y.Suzuki 1996/07/11	*/
			if (MEM_ReadOpen(&SYS_DocBlock.Index, &MemoryExecData) == MEM_NO_INDEX) {
				MDM_PhaseC_Status = TX_FILE_ERR;
				return (MDM_PhaseC_Status);	/**	戻り値ファイルエラーセット	*/
			}
		}
#endif
		switch (CodecPageStatus) {	/**	コーデックの状態	*/
		case CDC_BLOCK_END:	/**	ブロックエンドの時	*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == DISABLE)*/
			SoftcodecMessage.Message = MSG_SCDC_START;
			snd_msg(mbxno.SCDC_MTxCodeConvertTask, &SoftcodecMessage);	/*	エンコード開始メッセージ送信	*/
			break;
#else
			/*----------------------------------------------------------------------------------*/
			/*	Ｖ５３ＤＭＡ・ＭＡＳＴＥＲ　ＣＨ２　エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			/*----------------------------------------------------------------------------------*/
			ModemMessage.Message = MSG_ENCODE_DMA_START;	/**	Ｖ５３ＤＭＡ・ＭＡＳＴＥＲ　ＣＨ２　エンコード開始（ＤＭＡ起動）メッセージ送信	*/
			snd_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &ModemMessage);
			break;
#endif
		default:	/**	送信コントロール監視タスクが終了状態の時	*/
			/*----------------------------------*/
			/*	送信１ページ符号変換タスク起動	*/
			/*----------------------------------*/
#if (PRO_COM_CODEC_TYPE == SOFTWARE) /* 通信コーデックがソフトなら */
/* #if(PRO_SOFT_CODEC == ENABLE)*/
			tskno_SCDC_MTxCodeConvertTask = 0xffff;
			cre_tsk(&tskno_SCDC_MTxCodeConvertTask, TSK_SCDC_MTXCODECONVERTTASK, 0);	/**	送信１ページ符号変換タスク起動	*/
#else
			tskno_CDC_MTxCodeConvertTask = 0xffff;
			cre_tsk(&tskno_CDC_MTxCodeConvertTask, TSK_CDC_MTXCODECONVERTPAGETASK, 0);	/**	送信１ページ符号変換タスク起動	*/
#endif
		}
		break;
	case TX_BKUPRAM:
	 /* ICHOU通信タスクの先頭で初期化します by T.Soneoka 1996/10/24 */
		tskno_MDM_BackupRamToEcmBufTask = 0xffff;
		cre_tsk(&tskno_MDM_BackupRamToEcmBufTask, TSK_MDM_BACKUPRAMTOECMBUFTASK, 0);
		break;
	case TX_CVR:	/**	カバーページ送信の時	*/
	case TX_RCR:	/**	受領証送信の時	*/
	default:
		/*----------------------------------*/
		/*	キャラクタ送信エンコードタスク	*/
		/*----------------------------------*/
		tskno_SCD_CTxCodeConvertTask = 0xffff;
		cre_tsk(&tskno_SCD_CTxCodeConvertTask, TSK_SCD_CTXCODECONVERTPAGETASK, 0);
		break;
	}
	/*----------------------*/
	/*	画データ送出処理	*/
	/*----------------------*/
	if (ecm_type == ECM_OFF) {	/**	Ｇ３送信時	*/
	/*	rtn = G3_Tx();	@**	Ｇ３送信	*/
		rtn = SCD_G3_Tx();	/**	Ｇ３送信	*/
	}
	else {	/**	ＥＣＭ送信時	*/
		rtn = SCDC_EcmTx();	/**	ＥＣＭ送信	*/
	}
	MDM_PhaseC_Status = rtn;	/**	フェーズＣステータスに戻り値セット	*/
	return(rtn);
}



/*************************************************************************
	module		:[ソフトコーデック使用ＥＣＭ送信]
	function	:[
		1.
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
		TX_1M_OVER					8			×	×		○	○		ｽｷｬﾅ送信が１ｍを越えた
		TX_SEPARATE					9			○	○		○	○		F網設定時、送信がA4 2枚分に達した
			○：戻り値あり
			×：戻り値なし
			△：未定
	]
	common		:[]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[SH7034/SH704X]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1995/12/13]
	author		:[鈴木郁二]
*************************************************************************/
UBYTE SCD_DebugFlag = 0;
UBYTE	SCDC_EcmTx(
void)
{
	/*------------------*/
	/* ローカル変数宣言 */
	/*------------------*/
	/* 以下３つの変数このサブルーチンのみのローカル変数とする */
	#if(0)	/*	TEST By Y.Suzuki 1996/08/24	*/
	unsigned int	MDM_DebugDataWaitCnt;
	unsigned int	next_mbf_set_cnt;	/*	モデムバッファ書き込みデータ数	*/
	unsigned long	ebr_cnt;	/**	ＥＣＭバッファ読み出しバイト数	*/
	#endif
	UWORD	SCD_DebugDataWaitCnt;
	UWORD	SCD_next_mbf_set_cnt;	/*	モデムバッファ書き込みデータ数	*/
	UDWORD	SCD_ebr_cnt;	/**	ＥＣＭバッファ読み出しバイト数	*/

	UBYTE	*ebf_base_rp;	/*	ＥＣＭバッファ読み出しポインタ	*/
	UBYTE	rtn;	/*	リターンコード	*/
	UBYTE	i;
	UBYTE	page_loop;
	UBYTE	loop_flg;
/* 950203 1line insert */
	UBYTE	cdc_stat;
	UBYTE	detect_block_end;/* By Y.Suzuki 1998/01/23 */

	/* For Debug By Y.Suzuki 1997/09/19 */
	UBYTE	*dummy_address;
	dummy_address = (UBYTE *)0;
	/*------------------*/
	/*	変数初期化処理	*/
	/*------------------*/
	SCD_DebugFlag = 0;
	ebf_base_rp = &EcmBuffer[0][0];	/**	ＥＣＭバッファ読み出し先頭アドレス設定	*/
	SCD_ebr_cnt = 0;	/**	ＥＣＭバッファ読み出しバイト数	*/
	rtn = 0;	/**	リターンコード初期化	*/
	MDM_EcmFrameNumber = 0;	/**	ＥＣＭフレームナンバー初期化	*/

    /*----------------------*/
    /*  同期信号待ち処理    */
    /*----------------------*/
	/* 日立メールシステムにて画データ前同期信号が短いと受信できないという不具合（ＫＩＲＩにて発生）があるので反映させます */
	/* 1998/06/18 by M.Tachibana */
	wai_tsk(200/10);	/**	タスクウェイト２００ｍｓ	*/

	/*------------------------------------------------------------------------------------------------------*/
	/*	先頭２５６ｂｙｔｅブロック送出処理待ち処理（ＤＭＡ終了割り込み　ＯＲ　１ページ符号変換タスクより）	*/
	/*------------------------------------------------------------------------------------------------------*/
	loop_flg = 1;	/**	ループ制御フラグ１にセット	*/
	while (loop_flg) {	/**	ループ制御フラグが１の時	*/
		if (TxStartFlag == 1) {	/**	画データ送出フラグが１の時（エンコードデータが揃った時）	*/
			loop_flg = 0;	/**	ループ制御フラグクリア	*/
		}
		else {	/**	その他の時	*/
			rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			if (rtn) {	/**	送信異常有りの時	*/
				SCDC_BreakTxTask();	/**	送信子タスク終了	*/
				return (rtn);
			}
		}
		wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
	}
	/*--------------------------------------*/
	/*	送出未処理のエンコードデータ数取得	*/
	/*--------------------------------------*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	RemainEncodeData = EncodeDataCount;	/**	送出未処理エンコードデータ数更新	*/
/* 950203 1line insert */
	cdc_stat = CodecPageStatus;
	TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
	CMN_EnableInterrupt();	/**	割り込み許可	*/
	/*--------------------------------------*/
	/*	ＦＣＤフレーム送信登録／送出処理	*/
	/*--------------------------------------*/
	page_loop = 1;	/**	１ページ完了フラグ設定	*/
	while (page_loop) {	/**	１ページ送信ループ（エンコードデータがなくなり、ＲＴＣ（その他）を検出するまで）*/
		/*------------------------------------------------------*/
		/*	送出バイト数取得処理、通常１ブロック２５６ｂｙｔｅ	*/
		/*	次送出バイト数更新									*/
		/*------------------------------------------------------*/
		SCD_next_mbf_set_cnt = GetCount(RemainEncodeData, FcomEcmSize);	/**	１ブロック送出バイト数切り出し（２５６ｂｙｔｅ以下）	*/
		/*------------------------------------------*/
		/*	フレーム書き込みモデムバッファ獲得処理	*/
		/*------------------------------------------*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/
/* 950206 1line insert for T.5.3 error (SAKURA etc) */
		SetClear((UBYTE *)&MDM_ModemBuffer[ModemControl.WritePoint][0], RX_FSK_HDLC_LENGTH, 0x00);
		/*------------------------------------------------------------------------------------------*/
		/*	ＦＣＤフレーム送信登録（ＥＣＭバッファからモデムバッファにプログラム転送）／送出処理	*/
		/*------------------------------------------------------------------------------------------*/
		WriteFCD(MDM_EcmFrameNumber, &MDM_ModemBuffer[ModemControl.WritePoint][0], ebf_base_rp+SCD_ebr_cnt, SCD_next_mbf_set_cnt);	/**	ＦＣＤフレーム送信登録（ＥＣＭバッファからモデムバッファにプログラム転送）／送出処理	*/
		/*------------------------------*/
		/*	ＥＣＭフレームナンバー更新	*/
		/*------------------------------*/
		MDM_EcmFrameNumber++;	/**	ＥＣＭフレームナンバーインクリメント	*/
		/*----------------------------------*/
		/*	ＥＣＭバッファ読み出し数更新	*/
		/*----------------------------------*/
		SCD_ebr_cnt += (UDWORD)SCD_next_mbf_set_cnt;	/**	ＥＣＭバッファ読み出しバイト数更新	*/
		/*------------------*/
		/*	タスクウェイト	*/
		/*------------------*/
		wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
		/*------------------------------------------*/
		/*	送出未処理エンコードデータ数取得処理	*/
		/*------------------------------------------*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		RemainEncodeData = EncodeDataCount - SCD_ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
/* 950203 1line insert */
		cdc_stat = CodecPageStatus;
		TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
		CMN_EnableInterrupt();	/**	割り込み許可	*/
		/*----------------------------------*/
		/*	強制終了処理(ストップ処理）		*/
		/*----------------------------------*/
		if (MDM_TxStopSwFlag == 0) {	/**	画データ用ストップＳｗがＯＦＦの時	*/
			if (SYS_FaxComStopSwitch() == 1) {	/**	ストップＳｗ　ＯＮの時	*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				if (CHK_TxForceStop() != 0) {	/**	強制終了時	*/
					rtn = TX_STOPPED;	/**	戻り値ストップＳｗＯＮ設定	*/
				}
				MDM_TxStopSwFlag = 1;	/**	画データ用ストップＳｗをＯＮに設定	*/
				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~SYS_STOP_FAXCOM;	/**	マシンステータスの通信ストップ解除	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
			}
			else {
				rtn = CheckTxSystemError();	/**	送信異常チェック	*/
			}
			if (rtn) {	/**	送信異常有りの時	*/
				SCDC_BreakTxTask();	/**	送信子タスク終了	*/
				return (rtn);
			}
		}
		/*------------------------------*/
		/*	送出終了／子タスク終了処理	*/
		/*------------------------------*/
		if (RemainEncodeData == (UDWORD)0) {	/**	エンコードエンコードデータがないとき	*/
/* 950203 1line modify */
/*			switch (CodecPageStatus)	*	コーデックの状態	*/
			switch (cdc_stat) {	/**	コーデックの状態	*/
			case CDC_CONTINUE:	/**	エンコード中	*/
				SCD_DebugDataWaitCnt++;
				/*----------------------------------------------------------------------------------*/
				/*	モデムバッファにセットする方が速い時											*/
				/*	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）	*/
				/*----------------------------------------------------------------------------------*/
				loop_flg = 1;	/**	ループ制御フラグ１にセット	*/
				detect_block_end = 0;/* ブロックエンド発見クリア By Y.Suzuki 1998/01/23 */
				while (loop_flg) {	/**	ループ制御フラグが１の時	*/
					if (TxStartFlag == 1) {	/**	画データ送出フラグが１の時（エンコードデータが揃った時）	*/
						loop_flg = 0;	/**	ループ制御フラグを０にセット	*/
					}
					else {	/**	その他の時	*/
						rtn = CheckTxSystemError();	/**	送信異常チェック	*/
						if (rtn) {	/**	送信異常有りの時	*/
							SCDC_BreakTxTask();	/**	送信子タスク終了	*/
							return (rtn);
						}
						else {/* マルチコピー中のＥＣＭ送信でループ対策。真の原因は、ECMWRITE()で By Y.Suzuki 1998/01/23 */
							  /* TxStartFlag=1とCodecPageStatus=CDC_BLOCK_ENDの間にタイムラグが生じるため */
							if (CodecPageStatus == CDC_BLOCK_END) {
								detect_block_end = 1;
								break;
							}
							else {
								detect_block_end = 0;
							}
						}
					}
					wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
				}
				if (detect_block_end) {/* ブロックエンド発生 By Y.Suzuki 1998/01/23 */
					page_loop = 0;	/**	１ページ送信ループ抜ける	*/
					rtn = TX_BLOCK_END;	/**	戻り値ブロックエンド設定	*/
					break;
				}
				/*--------------------------------------*/
				/*	送出未処理のエンコードデータ数取得	*/
				/*--------------------------------------*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - SCD_ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
/* 950203 1line insert */
				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				break;
			case CDC_BLOCK_END:	/**	ＥＣＭバッファオーバの時	*/
				if (MDM_EcmFrameNumber) {
					/* デバックのため強制ﾗｲﾄﾌﾟﾛﾃｸﾄ By Y.Suzuki 1997/09/19 */
					SCD_DebugFlag = 3;
					*dummy_address = SCD_DebugFlag;
					wai_tsk(0xffff);
				}
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_BLOCK_END;	/**	戻り値ブロックエンド設定	*/
				break;
			case CDC_RTC_DET:	/**	ＲＴＣ検出の時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				SCDC_BreakTxTask();/**	各子タスク終了処理	*/
				rtn = TX_PAGE_END;	/**	戻り値１ページ送信完了設定	*/
				break;
			case CDC_STOPPED:	/**	正常ストップＳｗ終了の時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_STOPPED;	/**	戻り値ストップＳＷ設定	*/
				SCDC_BreakTxTask();	/**	各子タスク終了処理	*/
				break;
#if (0) /* (PRO_CODEC_TYPE == IDP301) */
			case CDC_PAGE_SEPARATE:	/**	ページ分割の時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				rtn = TX_SEPARATE;	/**	戻り値分割送信設定	*/
				break;
			case CDC_DOC_OVER:	/**	１ｍ原稿長オーバの時	*/
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				SCDC_BreakTxTask();	/**	各子タスク終了処理	*/
				rtn = TX_1M_OVER;	/**	戻り値１ｍ原稿長オーバ設定	*/
				break;
#endif
/***********************************/
/* 950118 3line insert for tx loop */
/***********************************/
			default:
				page_loop = 0;	/**	１ページ送信ループ抜ける	*/
				SCDC_BreakTxTask();	/**	各子タスク終了処理	*/
				rtn = TX_1M_OVER;	/* T.3.1 error */
				break;
			}
		}
		/*-----------------------------------------------------------*/
		/*	ＴＴＩ送出と画データとの間で２５６ｂｙｔｅそろわない時	 */
		/*-----------------------------------------------------------*/
		else if (RemainEncodeData < (UDWORD)FcomEcmSize) {	/**	エンコードエンコードデータがないとき	*/
/* 950203 1line modify */
/*			switch (CodecPageStatus)	*	コーデックの状態	*/
			switch (cdc_stat) {	/**	コーデックの状態	*/
			case	CDC_CONTINUE:	/**	エンコード中の時	*/
				SCD_DebugDataWaitCnt++;
				/*----------------------------------------------------------------------------------*/
				/*	モデムバッファにセットする方が速い時											*/
				/*	符号変換完了待ち（ＤＭＡ終了割り込み　ＯＲ　送信１ページ符号変換タスクより）	*/
				/*----------------------------------------------------------------------------------*/
				loop_flg = 1;	/**	ループ制御フラグを１にセット	*/
				detect_block_end = 0;/* ブロックエンド発見クリア By Y.Suzuki 1998/01/23 */
				while (loop_flg) {	/**	ループ制御フラグが１の時	*/
					if (TxStartFlag == 1) {	/**	画データ送出フラグが１の時（エンコードデータが揃った時）	*/
						loop_flg = 0;	/**	ループ制御フラグを０にセット	*/
					}
					else {	/**	その他の時	*/
						rtn = CheckTxSystemError();	/**	送信異常チェック	*/
						if (rtn) {	/**	送信異常有りの時	*/
							SCDC_BreakTxTask();	/**	送信子タスク終了	*/
							return (rtn);
						}
						else {/* マルチコピー中のＥＣＭ送信でループ対策。真の原因は、ECMWRITE()で By Y.Suzuki 1998/01/23 */
							  /* TxStartFlag=1とCodecPageStatus=CDC_BLOCK_ENDの間にタイムラグが生じるため */
							if (CodecPageStatus == CDC_BLOCK_END) {
								detect_block_end = 1;
								break;
							}
							else {
								detect_block_end = 0;
							}
						}
					}
					wai_tsk(10/10);	/**	タスクウェイト１０ｍｓ	*/
				}
				if (detect_block_end) {/* ブロックエンド発生 By Y.Suzuki 1998/01/23 */
					break;
				}
				/*--------------------------------------*/
				/*	送出未処理のエンコードデータ数取得	*/
				/*--------------------------------------*/
				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				RemainEncodeData = EncodeDataCount - SCD_ebr_cnt;	/**	送出未処理エンコードデータ数更新	*/
/* 950203 1line insert */
				cdc_stat = CodecPageStatus;
				TxStartFlag = 0;	/**	画データ送出フラグクリア	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				break;
			default:	/**	その他の時	*/
				break;
			}
		}
	}
	MDM_EcmFrameNumber--;	/**	ＥＣＭフレームナンバーデクリメント	*/
	LastEcmFrameNumber = MDM_EcmFrameNumber;	/**	最終ＥＣＭフレームナンバー設定	*/
	LastEcmFrameLength = SCD_next_mbf_set_cnt;	/**	最終ＥＣＭフレームサイズ設定	*/
#if (0)	/* 950306 2line insert for able 3010 */
	MDM_Tx1BlockEncodeLine = MDM_EncodeLine - MDM_TxEncodeLine;
	MDM_TxEncodeLine += MDM_Tx1BlockEncodeLine;
#endif
	/*--------------------------------------*/
	/*	ＲＣＰフレーム送信登録／送出処理	*/
	/*--------------------------------------*/
	for (i = 0; i < RCP_COUNT; i++) {	/**	ＲＣＰフレーム３個送出するまで	*/
		/*------------------------------------------*/
		/*	フレーム書き込みモデムバッファ獲得処理	*/
		/*------------------------------------------*/
		ModemBufferWaiSem(ModemControl.WritePoint);	/**	フレーム書き込みモデムバッファ獲得	*/
		/*----------------------*/
		/*	最終フレーム登録	*/
		/*----------------------*/
/*		if (i == (RCP_COUNT - 1)) {	*	最後のＲＣＰかチェック	 */
/*			ModemBlock.Chain = SET_COMPL;	*	最終フレーム登録	*/
/*		} */
/* 950203 1line insert */
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		/*--------------------------------------*/
		/**	ＲＣＰフレーム送信登録／送出処理	*/
		/*--------------------------------------*/
		WriteRCP(&MDM_ModemBuffer[ModemControl.WritePoint][0]);		/**	ＲＣＰフレーム登録	*/
		/*----------------------*/
		/*	最終フレーム登録	*/
		/*----------------------*/
		if (i == (RCP_COUNT - 1)) {	/**	最後のＲＣＰかチェック	*/
			ModemBlock.Chain = SET_COMPL;	/**	最終フレーム登録	*/
		}
/* 950203 1line insert */
		CMN_EnableInterrupt();	/**	割り込み許可	*/
		/*------------------*/
		/*	タスクウェイト	*/
		/*------------------*/
		wai_tsk(50/10);	/**	タスクウェイト５０ｍｓ	*/
	}
	return (rtn);
}


/*************************************************************************
	module		:[送信コントロールタスク強制終了処理]
	function	:[
	]
	return		:[]
	common		:[
			ソフトコーデックメモリ送信に対応 95/12/20 Y.Suzuki
	]
	condition	:[フラッシュＲＯＭ]
	comment		:[]
	machine		:[V53]
	language	:[MS-C(Ver.6.0)]
	keyword		:[MDM]
	date		:[1995/12/23]
	author		:[鈴木郁ニ]
*************************************************************************/
void	SCDC_BreakTxTask(
void)
{
	switch (CommunicateType) {	/**	交信種別	*/
	case TX_G3_MEM:	/**	メモリＧ３送信の時	*/
		if (tskno_DummyPixTimer != 0xff) {
			CMN_MultiTimer10msStop(&tskno_DummyPixTimer);	/**	ダミーデータ監視タイマタスク終了	*/
		}
	case TX_ECM_MEM:	/**	メモリＥＣＭ送信の時	*/
		if(tskno_SCDC_MTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_SCDC_MTxCodeConvertTask);
		}
		break;
#if(0)/* ここから、ソフトコーデックに不要な処理 96/1/6 Y.S */
	case TX_ECM_MEM:	/**	メモリＥＣＭ送信の時	*/
		/*------------------------------------------*/
		/*	メモリ送信１ページ符号変換タスク終了	*/
		/*------------------------------------------*/
		if (tskno_CDC_MTxCodeConvertTask != 0xffff) {
#if (PRO_CODEC_TYPE == IDP301)		/* 竹内 Nov.04.1994 */
			AbortCodecCommand( COMMUNICATION_CODEC );		/**	符号変換タスクの停止指示する	*/
#endif
			del_tsk(&tskno_CDC_MTxCodeConvertTask);	/**	メモリ送信１ページ符号変換タスク終了	*/
		}
#if (PRO_CODEC_TYPE == MN86063)
		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
			if (!ReleaseCodec(COMMUNICATION_CODEC, CODEC_MEMORY_TX)) {	/**	通信コーデックを解放（できない時）	*/
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
		}
		/*--------------------------------------*/
		/*	メモリ送信メモリリードタスク終了	*/
		/*--------------------------------------*/
		if (tskno_MTxReadDMA_Task != 0xffff) {
			del_tsk(&tskno_MTxReadDMA_Task);	/**	メモリ送信メモリリードタスク終了	*/
		}
		DMA_RequestMask(SLAVE1_DMAU, 0);	/**	Ｖ５３ＤＭＡ　ＳＬＡＶＥ　ＣＨ０　マスク	*/
		/*--------------------------------------------------*/
		/*	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		/*--------------------------------------------------*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}
		DMA_RequestMask(MASTER_DMAU, 2);	/**	Ｖ５３ＤＭＡ　ＭＡＳＴＥＲ　ＣＨ２　マスク	*/
#endif
		break;
	case TX_G3_SCAN:	/**	スキャナＧ３送信の時	*/
		if (tskno_DummyPixTimer != 0xff) {
			CMN_MultiTimer10msStop(&tskno_DummyPixTimer);	/**	ダミーデータ監視タイマタスク終了	*/
		}
	case TX_ECM_SCAN:	/**	スキャナＥＣＭ送信の時	*/
		/*------------------------------------------*/
		/*	スキャナ送信１ページ符号化タスク終了	*/
		/*------------------------------------------*/
		if (tskno_CDC_EncodePageTask != 0xffff) {
#if (PRO_CODEC_TYPE == IDP301)		/* 竹内 Nov.04.1994 */
			AbortCodecCommand( COMMUNICATION_CODEC );		/**	符号変換タスクの停止指示する	*/
#endif
			del_tsk(&tskno_CDC_EncodePageTask);	/**	１ページエンコードタスク終了	*/
		}
#if (PRO_CODEC_TYPE == MN86063)
		if (GetCodecFlag == YES) {	/**	コーデックを使用している時	*/
			if (!ReleaseCodec(SCANNER_CODEC, CODEC_SCANNER_TX)) {	/**	通信コーデックを解放（できない時）	*/
				SaveReturnAddressAndJumpBegin();	/**	リセット	*/
			}
		}
		/*--------------------------------------------------*/
		/*	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		/*--------------------------------------------------*/
		if (tskno_EncodeDMA_End != 0xffff) {
			del_tsk(&tskno_EncodeDMA_End);	/**	送信エンコードＶ５３ＤＭＡ監視タスク終了処理	*/
		}
		DMA_RequestMask(MASTER_DMAU, 0);	/**	Ｖ５３ＤＭＡ　ＭＡＳＴＥＲ　ＣＨ０　マスク	*/
#endif
		break;
#endif/* ここまで、ソフトコーデックに不要な処理 96/1/6 Y.S */
	case TX_ECM_BKUPRAM:
		if (tskno_MDM_BackupRamToEcmBufTask != 0xffff) {
			del_tsk(&tskno_MDM_BackupRamToEcmBufTask);	/** キャラクタ送信１ページ符号化タスク終了	*/
		}
		break;
	case TX_ECM_CVR:	/**	ＥＣＭカバーページ送信の時	*/
	case TX_ECM_RCR:	/**	ＥＣＭ受領証送信の時	*/
	case TX_G3_CVR:	/**	Ｇ３カバーページ送信の時	*/
	case TX_G3_RCR:	/**	Ｇ３受領証送信の時	*/
	default: /**	その他の時	*/
		/*------------------------------------------*/
		/*	キャラクタ送信１ページ符号化タスク終了	*/
		/*------------------------------------------*/
		if (tskno_SCD_CTxCodeConvertTask != 0xffff) {
			del_tsk(&tskno_SCD_CTxCodeConvertTask);	/**	キャラクタ送信１ページ符号化タスク終了	*/
		}
#if(0)/* ｿﾌﾄｺｰﾃﾞｯｸ不要 96/1/11 Y.S */
		/*------------------------------------------*/
		/*	キャラクタ送信１ページ符号化タスク終了	*/
		/*------------------------------------------*/
		if (tskno_CDC_CTxCodeConvertTask != 0xffff) {
#if (PRO_CODEC_TYPE == IDP301)		/* 竹内 Nov.04.1994 */
			AbortCodecCommand( COMMUNICATION_CODEC );		/**	符号変換タスクの停止指示する	*/
#endif
			del_tsk(&tskno_CDC_CTxCodeConvertTask);	/**	キャラクタ送信１ページ符号化タスク終了	*/
		}
#endif /* ｿﾌﾄｺｰﾃﾞｯｸ不要 96/1/11 Y.S */
		break;
	}
	CodecPageStatus = CDC_READY;	/**	コーデックステータスクリア	*/
}
#endif/* PRO_COM_CODEC_TYPE SOFTWARE*/

