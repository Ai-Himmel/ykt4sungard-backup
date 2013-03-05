/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_int.c                                                 */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : モデム割り込み・ＤＭＡ割り込み関連処理                    */
/*  修正履歴     :                                                           */
/*	keyword			:[MDM]                                                   */
/*	machine			:[SH7043]                                                */
/*	language		:[MS-C(Ver.6.0)]                                         */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_io.h"
#include "\src\atlanta\define\dpr_def.h"
#include "\src\atlanta\define\scn_def.h"

#include "\src\atlanta\define\man_pro.h"		/* 1996/03/11 Y.M */
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\dma_pro.h"
#if (PRO_DPRAM == ENABLE)
#include "\src\atlanta\define\dpr_pro.h"
#endif
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\mem_pro.h"	/* 1997/01/28 Y.M */
#include "\src\memsw\define\mems_pro.h" /* by H.Kubo 1997/07/07 */
#include "\src\atlanta\define\cmn_pro.h" /* by H.Kubo 1997/07/08*/

#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\ext_v\scn_data.h" /* Added by H.Kubo 1997/07/14 */
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
#include "\src\atlanta\ext_v\dma_data.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_tbl.h"	/** For Debug By O.K Jan.25,1996 **/
#include "\src\atlanta\ext_v\sys_data.h"	/** For Debug Y.M 1996/01/30 **/
#include "\src\atlanta\ext_v\fcm_data.h"	/** For Debug Y.M 1996/10/30 **/
#include "\src\atlanta\ext_v\bkupram.h"	/** For Debug Y.M 1997/03/03 **/
#include "\src\atlanta\define\mnt_sw.h"	/** For Debug H.Kubo 1997/11/13 **/

#include "\src\atlanta\SH7043\define\io_pro.h" /* Added by H.Kubo 1997/10/08 */
#include "\src\atlanta\mdm\fm336\define\mdmnddef.h"
#if defined(SAKAKI) /* /* 2002/09/18 By M.Maeda */
#include "\src\atlanta\sh7043\define\sh_sys.h" /* Added by H.Kubo 1998/07/20 */
#endif

CONST	unsigned char far TONE_Debug = 1;		/* 1996/03/12 Y.M ; 0->1 1996/03/28 */
extern CONST unsigned char far TCF_DEBUG;	/* 1996/10/11 Y.M */

#if defined(SAKAKI) /* added by H.Kubo 1998/10/05 *//* 2002/09/18 By M.Maeda */
#include "\src\atlanta\ext_v\sys_port.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\sakaki\define\md9805.h"
CONST UBYTE mdm_news_debug = 0;
#endif

#if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/06/10 */
 #include "\src\atlanta\define\mntsw_i.h"	/** For Debug H.Kubo 1997/11/13 **/
#endif

UWORD	DebugZeroCnt = 0;
UBYTE CL1_PNSUC_TurnOff = 0;	/*  By O.Kimoto 1997/05/16 */
UBYTE CL1_RLSD_TurnOff = 0;	/*  By O.Kimoto 1997/05/16 */
UBYTE CL1_FLAGDT_Found = 0;	/*  By O.Kimoto 1997/05/16 */
UBYTE CL1_HDLC_AbortSequence = 0; /* by H.Kubo 1997/08/28 */

#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* Changed by H.Kubo 1998/11/10 *//* 2002/09/18 By M.Maeda */
/*************************************************************************
	module		:[モデム割り込み用モデムステータス読み込み]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		モデム割り込みから呼ばれる
	]
	comment		:[
	]
	ProtoType	:[void MDM_ReadModemStatus(void){}]
	date		:[1998/11/10]
	author		:[久保博]
*************************************************************************/
void MDM_ReadModemStatus(void)
{
	/* 割り込み処理で必要なポートだけを読みます。 */
	MDM_CurrentModemRegister.MDM_REG_0A = inp(MDM_REG_0A_PORT);
	MDM_CurrentModemRegister.MDM_REG_0B = inp(MDM_REG_0B_PORT);
	MDM_CurrentModemRegister.MDM_REG_0C = inp(MDM_REG_0C_PORT);
	MDM_CurrentModemRegister.MDM_REG_0D = inp(MDM_REG_0D_PORT);
	MDM_CurrentModemRegister.MDM_REG_0E = inp(MDM_REG_0E_PORT);
	MDM_CurrentModemRegister.MDM_REG_0F = inp(MDM_REG_0F_PORT);
	MDM_CurrentModemRegister.MDM_REG_12 = inp(MDM_REG_12_PORT);
	MDM_CurrentModemRegister.MDM_REG_14 = inp(MDM_REG_14_PORT);
	MDM_CurrentModemRegister.MDM_REG_16 = inp(MDM_REG_16_PORT);
	MDM_CurrentModemRegister.MDM_REG_17 = inp(MDM_REG_17_PORT);
	MDM_CurrentModemRegister.MDM_REG_1E = inp(MDM_REG_1E_PORT);
	MDM_CurrentModemRegister.MDM_REG_1F = inp(MDM_REG_1F_PORT);

	MDM_ReviewRegister.MDM_REG_0A = IO_BIT_PNSUC | IO_BIT_FLAGDT | IO_BIT_PE | IO_BIT_FE | IO_BIT_OE | IO_BIT_FLAGS | IO_BIT_SYNCD;
	MDM_ReviewRegister.MDM_REG_0B = IO_BIT_ATV25;
	MDM_ReviewRegister.MDM_REG_0C = IO_BIT_PCOFF | IO_BIT_RXFNE;
	MDM_ReviewRegister.MDM_REG_0D = IO_BIT_PNDET;
	MDM_ReviewRegister.MDM_REG_0E = 0;
	MDM_ReviewRegister.MDM_REG_0F = IO_BIT_RLSD | IO_BIT_FED;
	MDM_ReviewRegister.MDM_REG_12 = 0; /* CONF */
	MDM_ReviewRegister.MDM_REG_14 = 0; /* ABCODE */
	MDM_ReviewRegister.MDM_REG_16 = IO_BIT_SECRXB;
	MDM_ReviewRegister.MDM_REG_17 = 0; /* SECTXB */
	MDM_ReviewRegister.MDM_REG_1E = IO_BIT_RDBF | IO_BIT_RDBIA;
	MDM_ReviewRegister.MDM_REG_1F = IO_BIT_NEWS | IO_BIT_NSIA;
}

/*************************************************************************
	module		:[モデム割り込み用モデムステータスチェック]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		モデム割り込みから呼ばれる
	]
	comment		:[
	]
	ProtoType	:[void MDM_ReadModemStatus(void){}]
	date		:[1998/11/10]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_IsNewModemInterruptRaised(void)
{
	MDM_PreviousModemRegister.MDM_REG_0A = MDM_CurrentModemRegister.MDM_REG_0A;
	MDM_PreviousModemRegister.MDM_REG_0B = MDM_CurrentModemRegister.MDM_REG_0B;
	MDM_PreviousModemRegister.MDM_REG_0C = MDM_CurrentModemRegister.MDM_REG_0C;
	MDM_PreviousModemRegister.MDM_REG_0D = MDM_CurrentModemRegister.MDM_REG_0D;
	MDM_PreviousModemRegister.MDM_REG_0E = MDM_CurrentModemRegister.MDM_REG_0E;
	MDM_PreviousModemRegister.MDM_REG_0F = MDM_CurrentModemRegister.MDM_REG_0F;
	MDM_PreviousModemRegister.MDM_REG_12 = MDM_CurrentModemRegister.MDM_REG_12;
	MDM_PreviousModemRegister.MDM_REG_14 = MDM_CurrentModemRegister.MDM_REG_14;
	MDM_PreviousModemRegister.MDM_REG_16 = MDM_CurrentModemRegister.MDM_REG_16;
	MDM_PreviousModemRegister.MDM_REG_17 = MDM_CurrentModemRegister.MDM_REG_17;
	MDM_PreviousModemRegister.MDM_REG_1E = MDM_CurrentModemRegister.MDM_REG_1E;
	MDM_PreviousModemRegister.MDM_REG_1F = MDM_CurrentModemRegister.MDM_REG_1F;

	/* 割り込み処理で必要なポートだけを読みます。 */
	MDM_CurrentModemRegister.MDM_REG_0A = inp(MDM_REG_0A_PORT);
	MDM_CurrentModemRegister.MDM_REG_0B = inp(MDM_REG_0B_PORT);
	MDM_CurrentModemRegister.MDM_REG_0C = inp(MDM_REG_0C_PORT);
	MDM_CurrentModemRegister.MDM_REG_0D = inp(MDM_REG_0D_PORT);
	MDM_CurrentModemRegister.MDM_REG_0E = inp(MDM_REG_0E_PORT);
	MDM_CurrentModemRegister.MDM_REG_0F = inp(MDM_REG_0F_PORT);
	MDM_CurrentModemRegister.MDM_REG_12 = inp(MDM_REG_12_PORT);
	MDM_CurrentModemRegister.MDM_REG_14 = inp(MDM_REG_14_PORT);
	MDM_CurrentModemRegister.MDM_REG_16 = inp(MDM_REG_16_PORT);
	MDM_CurrentModemRegister.MDM_REG_17 = inp(MDM_REG_17_PORT);
	MDM_CurrentModemRegister.MDM_REG_1E = inp(MDM_REG_1E_PORT);
	MDM_CurrentModemRegister.MDM_REG_1F = inp(MDM_REG_1F_PORT);

	/* 状態の変化しているポートがあれば、 TRUE を返します。 */
	if (((MDM_PreviousModemRegister.MDM_REG_0A ^ MDM_CurrentModemRegister.MDM_REG_0A) & MDM_ReviewRegister.MDM_REG_0A)
	||	((MDM_PreviousModemRegister.MDM_REG_0B ^ MDM_CurrentModemRegister.MDM_REG_0B) & MDM_ReviewRegister.MDM_REG_0B)
	||	((MDM_PreviousModemRegister.MDM_REG_0C ^ MDM_CurrentModemRegister.MDM_REG_0C) & MDM_ReviewRegister.MDM_REG_0C)
	||	((MDM_PreviousModemRegister.MDM_REG_0D ^ MDM_CurrentModemRegister.MDM_REG_0D) & MDM_ReviewRegister.MDM_REG_0D)
	||	((MDM_PreviousModemRegister.MDM_REG_0E ^ MDM_CurrentModemRegister.MDM_REG_0E) & MDM_ReviewRegister.MDM_REG_0E)
	||	((MDM_PreviousModemRegister.MDM_REG_0F ^ MDM_CurrentModemRegister.MDM_REG_0F) & MDM_ReviewRegister.MDM_REG_0F)
	||	((MDM_PreviousModemRegister.MDM_REG_12 ^ MDM_CurrentModemRegister.MDM_REG_12) & MDM_ReviewRegister.MDM_REG_12)
	||	((MDM_PreviousModemRegister.MDM_REG_14 ^ MDM_CurrentModemRegister.MDM_REG_14) & MDM_ReviewRegister.MDM_REG_14)
	||	((MDM_PreviousModemRegister.MDM_REG_16 ^ MDM_CurrentModemRegister.MDM_REG_16) & MDM_ReviewRegister.MDM_REG_16)
	||	((MDM_PreviousModemRegister.MDM_REG_17 ^ MDM_CurrentModemRegister.MDM_REG_17) & MDM_ReviewRegister.MDM_REG_17)
	||	((MDM_PreviousModemRegister.MDM_REG_1E ^ MDM_CurrentModemRegister.MDM_REG_1E) & MDM_ReviewRegister.MDM_REG_1E)
	||	((MDM_PreviousModemRegister.MDM_REG_1F ^ MDM_CurrentModemRegister.MDM_REG_1F) & MDM_ReviewRegister.MDM_REG_1F)
	 ){
		return TRUE;
	}
	return FALSE;


}

/*************************************************************************
	module		:[モデム割り込み用モデム割り込みステータスチェック]
	function	:[
	]
	return		:[]
	common		:[
	]
	condition	:[
		モデム割り込みから呼ばれる
	]
	comment		:[
	]
	ProtoType	:[UBYTE MDM_IsModemInterruptActive(void){}]
	date		:[1998/11/10]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_IsModemInterruptActive(void)
{
#if (PRO_EXT_INT_TYPE == EXT_INT_SAKAKI)
	if ((SH__ISR & IRQ7_STATUS) && (inpw(INTERRPUT_PORT) & IO_BIT_INT70)) {
		return TRUE;
	}
	return FALSE;
#endif
}

/*************************************************************************
	module		:[モデム割り込み処理]
	function	:[
	]
	return		:[なし]
	common		:[
	]
	condition	:[
		1.１４４００ｂｐｓで受信時は、５５５μｓで次のＤＭＡを起動しなければ
		, データ取りこぼすため割り込み内で処理します

		モデム割り込みから呼ばれる
		
		以下の大域変数に、最新のモデムレジスタの内容が読み込まれていること

		MDM_CurrentModemRegister

	]
	comment		:[
		ここでの処理は、すべて MDM_CurrentModemRegister に読み込まれた値をもとに行う。

	]
	ProtoType	:[void MDM_ModemInterruptSub(void){}]
	date		:[1998/11/10]
	author		:[久保博]
*************************************************************************/
UBYTE mdm_stat=0;
void MDM_ModemInterruptSub(void)
{
	UWORD rtn;
#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi *//* By M.Maeda 2002/10/24 */
	UBYTE temp_reg;
#endif

	rtn = 0;

	/** ２１００Ｈｚ検出（ＣＥＤ,ＡＮＳａｍ） **/
	if (MDM_CurrentModemRegister.MDM_REG_0B & IO_BIT_ATV25) {
		SYS_V8DetectATV25Flag = 1;
		rtn |= MDM_EVT_ATV25_DETECT_BIT;	/* return(EVT_MDM_ATV25) */
	}

	/** ＤＭＡの起動が早すぎる対策（暫定） **//**  By O.K Jan.17,1996 **/
	if ((MDM_CurrentModemRegister.MDM_REG_0F & IO_BIT_RLSD)
	&&  (MDM_CurrentModemRegister.MDM_REG_1E & IO_BIT_RDBF)) {
		if (MDM_DmaStart == MDM_DMA_READY) {
			switch (ModemBlock.Mode) {
			case MODE_RX_ECM:
			case MODE_RX_FSK:
				SelectDreqDirection(RX_DMA);
				DMA_RequestEnable(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
				MDM_DmaStart = MDM_DMA_GO;
#if  (PRO_MODEM_R288F_VERSION >= R288F_VERSION_22P) /* (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) */ /* 1998/10/09 By H.Hirao */ /* Condition changd by H.Kubo 1998/10/17  */
		 		IsRlsdAndRdbfOn = 1;
#endif
				break;
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23) /* added by H.Kubo 1998/08/04 */
			case MODE_RX_ND:
				SelectDreqDirection(RX_DMA);
				DMA_RequestEnable(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
				MDM_DmaStart = MDM_DMA_GO;
				rtn |= MDM_EVT_RX_RDBF_BIT;
				break;
#endif
			default:
				break;
			}
		}
#if  (PRO_MODEM_R288F_VERSION >= R288F_VERSION_22P) /* R4.2(ABCODE 96)対策。 added by H.Kubo 1998/11/10  */
		if ((ModemBlock.Mode == MODE_RX_FSK) && SYS_V34ProcedureExecuting() && (MDM_DmaStart == MDM_DMA_READY)) {
			switch (SYS_ModemVersion) {
			case MDM_L6713_22P:
			case MDM_L6713_24P:
			case MDM_L6713_26P:
				if ((MDM_CurrentModemRegister.MDM_REG_0C & IO_BIT_CCDET_DET800) /* in Control Channel  */
				&&  (MDM_CurrentModemRegister.MDM_REG_1E & IO_BIT_RDBF)) {
					SelectDreqDirection(RX_DMA);
					DMA_RequestEnable(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
					MDM_DmaStart = MDM_DMA_GO;
			 		IsRlsdAndRdbfOn = 1;
				}
				break;
			default:
				break;
			}
		}
#endif
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23) /* added by H.Kubo 1998/08/04 */
		if ((ModemBlock.Mode == MODE_RX_ND) && MDM_ND_WaitFirstDataEvent) {
			rtn |= MDM_EVT_RX_RDBF_BIT;
			MDM_ND_WaitFirstDataEvent = FALSE;
		}
#endif
#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* For configuring RLSD drop-out timer. by H.Kubo 1998/10/21 */
	if ((!IsRlsdAndRdbfOn) && ((ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_G3))) {
		IsRlsdAndRdbfOn = 1;
	}
#endif
	}

	if (!(SYS_V34ProcedureExecuting())) {	/** 従来のプロトコルならば **/
		/* 1997/02/01 Y.Murata
		 * モデム割り込みの中でトレーニング信号とＴＣＦデータの検出を行っているが
		 * タイミングにより割り込みがとれない時がある（特にＴＣＦデータ）
		 * 今まではたまたま動いていた。ここでの処理は気休めになってしまっている
		*/
		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_TRDETON) {
			/*--------------------------------------*/
			/* PNSUC ﾋﾞｯﾄをみる 1997/01/16 Y.Murata */
			/*--------------------------------------*/
			/* 両方みる  1997/01/28 Y.Murata        */
			/*--------------------------------------*/
				/** ＴＣＦ前モデムトレーニング受信 **/
				if ((MDM_CurrentModemRegister.MDM_REG_0D & IO_BIT_PNDET) || (MDM_CurrentModemRegister.MDM_REG_0A & IO_BIT_PNSUC)) {
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					rtn |= MDM_EVT_MDM_PNSUC_BIT;	/* return(EVT_MDM_PNSUC) */
				}
			}
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_RLSDON) {
				/** ＴＣＦデータ受信 */
				if (MDM_CurrentModemRegister.MDM_REG_0F & IO_BIT_RLSD) {
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					rtn |= MDM_EVT_MDM_PNSUC_BIT;	/* return(EVT_MDM_PNSUC) */
				}
			}
		}
	}	/* end of if (!(SYS_V34ProcedureExecuting())) { */

	switch (ModemBlock.Mode) {	/**	交信モード	*/
	case MODE_TX_FSK:	/**	ＦＳＫ送信モードの時	*/
	case MODE_TX_ECM:	/**	ＥＣＭ送信モードの時	*/
		mdm_stat = MDM_CurrentModemRegister.MDM_REG_0A; 	/**	ＨＤＬＣデータコントロール表示レジスタ読み込み	*/
		if (ModemControl.Status & STAT_ALSENT) {			/**	送出データがセット済みの時	*/
			if (mdm_stat & IO_BIT_FLAGS) {					/**	ＦＣＳ割り込み発生した時	*/
				ModemControl.Status &= (~STAT_ALSENT);		/**	ＦＣＳ割り込み待ち解除	*/
				ModemInterruptFlag = 1;						/**	モデム割り込み発生フラグセット	*/
				MDM_SetIO(POS_TEOF,OFF);					/** TEOF は 11:1 */
				rtn |= MDM_EVT_TX_FCS_COMPLETE_BIT; 		/* V21ch2 フラグ(7E) 検出 */
			}
		}
		break;
	case MODE_RX_ECM:	/**	ＥＣＭ受信モード	*/
		mdm_stat = MDM_CurrentModemRegister.MDM_REG_0A;	/**	モデム割り込みステータス読み込み */
		if (SYS_V34ProcedureExecuting()) {	/* V34 */
			if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_SYNCD)) {	/**	フラグ検出フェーズ時	*/
				ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
				ModemControl.Status |= STAT_FCSDET;	/**	ＦＣＳ検出フェーズ設定	*/
				/*----------------------------------------------*/
				/**	イベントセット処理							*/
				/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
				/*----------------------------------------------*/
				ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
				rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
			}
#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/30 */
			/* R4.2 対策。  Primary channel OFF の検出が 20P までで使っていた SECRXBを監視する方法ではだめなことがある。 by H.Kubo 1998/10/30 */
			if ((SYS_ModemVersion == MDM_L6713_24P)|| (SYS_ModemVersion == MDM_L6713_26P)) {
				if (MDM_RlsdTurnOffCheckFlag == TRUE) {
					if (MDM_CurrentModemRegister.MDM_REG_0C & IO_BIT_PCOFF) {
						/* if ((MDM_CurrentModemRegister.MDM_REG_16 == 0xA3) ) {  */ /* FED が落ちてからにします changed by H.Kubo 1998/11/13 */ /* データ受信中か？ */
						if ((MDM_CurrentModemRegister.MDM_REG_16 == 0xA3) 
						&&  !(MDM_CurrentModemRegister.MDM_REG_0C & IO_BIT_FED)) { /* データ受信中か？ */
							MDM_RlsdTurnOffFlag = 1;
							rtn |= MDM_EVT_PCOFF_DETECT_BIT;
						}
					}
				}
			}
#endif
		}
		else {
			if (CHK_HIGH_MODE_CATCH()) {	/* 高速のみまつ 1997/01/28 Y.Murata */
				/* Nothing */
			}
			else {
				if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_FLAGDT)) {	/**	フラグ検出フェーズ時	*/
					ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
					ModemControl.Status |= STAT_FCSDET;	/**	ＦＣＳ検出フェーズ設定	*/
					/*----------------------------------------------*/
					/**	イベントセット処理							*/
					/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
					/*----------------------------------------------*/
					ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
					rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
				}
			}
		}

#ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi *//* By M.Maeda 2002/10/24 */
		if (MDM_DmaStart == MDM_DMA_MASK) {
			break;	/* case文脱出 *//* DMAの再起動は、まだしたらダメ。まだDMAのセットアップできてません */
		}
#endif

		/* ロックウェルのソースから By O.K Feb.20,1996 */
		if (mdm_stat & IO_BIT_FE) {
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
			SelectDreqDirection(RX_DMA);
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
			MDM_DmaStart = MDM_DMA_GO;
		}
		else if (mdm_stat & IO_BIT_OE) {
			MDM_SetIO(POS_OE, OFF); /* OE はホストで落とさないといつまでも落ちない。 */
			MDM_ReviewRegister.MDM_REG_0A &= ~IO_BIT_OE; /* ステータスの変化の検査で OE を無視。 */
			DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
			SelectDreqDirection(RX_DMA);
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
			MDM_DmaStart = MDM_DMA_GO;
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* added by H.Kubo 1998/01/29 */
		}
		else if (mdm_stat & IO_BIT_SYNCD) {	/** test **/
			if ((!(mdm_stat & IO_BIT_PE))&&(MDM_DmaStart != MDM_DMA_MASK)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 1999/01/19 By H.Kubo */
				/* DMA(DTC) はここで止めないといけない。カウンタを読んでからマスクするまでの間に次の DREQ が来たら
				** 終了割り込みがかかることがある。
				** by H.Kubo 1999/01/18 */
				DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#endif
				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
				ModemControl.UsedCount++;
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* added by H.Kubo 1999/01/18 */
				/* フレーム最後のフラグを受信してからここに来るまでの間に次のフレームの先頭を受信していたら、
				** 次のフレームの先頭は次のモデムバッファにコピーして残りのデータの受信を始めます。
				** そうでなければ、次のフレームは普通に次のモデムバッファの先頭から受信し始めます。
				** by H.Kubo 1999/01/18
				*/
				if ((MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1))
					&& (MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] == 0xff)) {
					MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] = 0x0;
					MDM_RxSize[ModemControl.WritePoint] -= 1; /* 次のモデムバッファに移した分だけ引き算します。 */
					NextMdmBufWritePointSetExtRom();
					MDM_ModemBuffer[ModemControl.WritePoint][0] = 0xff;
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
				}
				else {
					NextMdmBufWritePointSetExtRom();
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
				}

#else
				NextMdmBufWritePointSetExtRom();
 #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 1999/01/19 By H.Kubo */
				/* ここで DMA(DTC) を止めても遅い。DMA(DTC) のカウンタが 1 でDMA(DTC) のカウンタを
				** 読んでからここに来るまでの間に DMA(DTC) のリクエストが来たら、 DMA(DTC) 終了
				** 割り込みがかかることがある。 DMA(DTC) マスクの位置を前へ移動。
				** by H.Kubo 1999/01/18
 #else
				DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
 #endif
				SelectDreqDirection(RX_DMA);
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
				MDM_DmaStart = MDM_DMA_GO;
			}
			else {
				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 1999/01/19 PPR デバッグのため。By H.Kubo */
				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
				if (MDM_RxSize[ModemControl.WritePoint] > 1) {
					MDMWPNT.DataCount = MDM_RxSize[ModemControl.WritePoint]; /* デバッグ用に覚えておく */
					MDMWPNT.TopAddress = MDM_ModemBuffer[ModemControl.WritePoint];
				}
#endif
				SelectDreqDirection(RX_DMA);
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);/**  By O.K Jan.K Jan.23,1996 **/
				MDM_DmaStart = MDM_DMA_GO;
			}
		}
		break;
	case MODE_RX_FSK:	/**	ＦＳＫ受信モード	*/
		mdm_stat = MDM_CurrentModemRegister.MDM_REG_0A;	/**	モデム割り込みステータス読み込み */
		if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_SYNCD)) {	/**	フラグ検出フェーズ時	*/
			/* 1997/04/01 Y.Murata
			 * 会話予約でPIPとPRI_EOPがぶつかってしまう。SYNCDの誤検出が原因。
			 * RLSDがONの時のみSYNCDを見に行く。
			*/
			if (!SYS_V34ProcedureExecuting()) {
				if (MDM_CurrentModemRegister.MDM_REG_0F & IO_BIT_RLSD) {
					ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
					ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
					/**	ＨＤＬＣモデムモード設定	*/
					/**	ＦＣＳ検出時、割り込み発生設定	*/
					/**	受信データ要求ＯＮ	*/
					/*----------------------------------------------*/
					/**	イベントセット処理							*/
					/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
					/*----------------------------------------------*/
					ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
					rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
				}
			}
			else {
				ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
				ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
				/**	ＨＤＬＣモデムモード設定	*/
				/**	ＦＣＳ検出時、割り込み発生設定	*/
				/**	受信データ要求ＯＮ	*/
				/*----------------------------------------------*/
				/**	イベントセット処理							*/
				/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
				/*----------------------------------------------*/
				ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
				rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
			}
		}

#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi */
		if (MDM_DmaStart == MDM_DMA_MASK) {
			break;	/* case文脱出 *//* DMAの再起動は、まだしたらダメ。まだDMAのセットアップできてません。 */
		}
#endif

		/* ロックウェルのソースから By O.K Feb.20,1996 */
		if (mdm_stat & IO_BIT_FE) { /* ABORT シーケンス検出 */
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
			SelectDreqDirection(RX_DMA);
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
			MDM_DmaStart = MDM_DMA_GO;
		}
		else if (mdm_stat & IO_BIT_OE) { /* 受信オーバーラン */
			MDM_SetIO(POS_OE, OFF); /* OE はホストで落とさないといつまでも落ちない。 */
			MDM_ReviewRegister.MDM_REG_0A &= ~IO_BIT_OE; /* ステータスの変化の検査で OE を無視。 */
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
			SelectDreqDirection(RX_DMA);
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1),(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
			MDM_DmaStart = MDM_DMA_GO;
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* added by H.Kubo 1998/01/29 */
		}
		else if (mdm_stat & IO_BIT_SYNCD) {
			if ((!(mdm_stat & IO_BIT_PE))&&(MDM_DmaStart != MDM_DMA_MASK)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */
				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
				/*----------------------*/
				/**	フレーム補正処理	*/
				/*----------------------*/
				if (ModemBufferFormatControl(ModemControl.WritePoint) == NG) {	/**	不正フレームを受信した時	*/
					DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
					SelectDreqDirection(RX_DMA);
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
					MDM_DmaStart = MDM_DMA_GO;
				}
				else {	/**	正常なフレームを受信した時	*/
					if (MDM_ModemBuffer[ModemControl.WritePoint][2] == EchoFCF) {
						DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
						SelectDreqDirection(RX_DMA);
						DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
						MDM_DmaStart = MDM_DMA_GO;
						if (HighSpeedCheckFlag == 1) {
							EchoFrameRcvFlag = 1;
						}
					}
					else {
						ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
						NextMdmBufWritePointSetExtRom();
						DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
						SelectDreqDirection(RX_DMA);
						DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
						MDM_DmaStart = MDM_DMA_GO;
					}
				}
			}
			else {	/**	ＦＣＳエラー時	*/
				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
				SelectDreqDirection(RX_DMA);
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
				MDM_DmaStart = MDM_DMA_GO;
			}
		}
		break;
	case MODE_RX_G3: /* Added by H.Kubo 1998/01/30 */
		mdm_stat = MDM_CurrentModemRegister.MDM_REG_0A;	/**	モデム割り込みステータス読み込み */
		if (mdm_stat & IO_BIT_OE) { /* 受信オーバーランを起こしていたら */
			MDM_SetIO(POS_OE, OFF); /* OE bit をリセット。*/
			MDM_ReviewRegister.MDM_REG_0A &= ~IO_BIT_OE; /* ステータスの変化の検査で OE を無視。 */
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN;/* メンテナンススイッチに通知*/
		}
		break;
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23) /* added by H.Kubo 1998/10/27 */
	case MODE_RX_ND:
		mdm_stat = MDM_CurrentModemRegister.MDM_REG_0A;	/**	モデム割り込みステータス読み込み */
		if (mdm_stat & IO_BIT_OE) { /* 受信オーバーランを起こしていたら */
			MDM_SetIO(POS_OE, OFF); /* OE bit をリセット。*/
			MDM_ReviewRegister.MDM_REG_0A &= ~IO_BIT_OE; /* ステータスの変化の検査で OE を無視。 */
		}
		break;
#endif
	default:
		break;
	}
	if ((MDM_DmaStart == MDM_DMA_GO) && (MDM_CurrentModemRegister.MDM_REG_1E & IO_BIT_RDBIE)) {
		MDM_SetIO(POS_RDBIE,OFF);			/* 1E:2 */
		MDM_DmaStart = MDM_DMA_CONTINUE;
		MDM_ReviewRegister.MDM_REG_1E &= ~(IO_BIT_RDBF | IO_BIT_RDBIA | IO_BIT_RDBIE); /* 状態変化しても無視する */
	}

	if (rtn != 0 ) {
		if ( (rtn & MDM_EVT_ATV25_DETECT_BIT) != 0 ) {
			idet_evt(EVT_MDM_ATV25);
		}
		if ( (rtn & MDM_EVT_MDM_PNSUC_BIT) != 0 ) {
			idet_evt(EVT_MDM_PNSUC);
		}
		if ( (rtn & MDM_EVT_TX_FCS_COMPLETE_BIT) != 0 ) {
			idet_evt(EVT_TX_FCS_COMPLETE);
		}
		if ( (rtn & MDM_EVT_RX_FLG_DETECT_BIT) != 0 ) {
			idet_evt(EVT_RX_FLG_DETECT);
		}
#if (PRO_NUMBER_DISPLAY == ENABLE) && (PRO_CALLER_ID_PROTOCOL == CALLER_ID_V23) /* added by H.Kubo 1998/08/04 */
		if ( (rtn & MDM_EVT_RX_RDBF_BIT) != 0 ) {
			idet_evt(EVT_MDM_RX_NEW_DATA);
		}
#endif
#if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/30 */
			/* R4.2 対策(試験中)。  PC OFF のとき、20P までで使っていた SECRXBを監視する方法ではだめなことがある。 by H.Kubo 1998/10/30 */
		if ( (rtn & MDM_EVT_PCOFF_DETECT_BIT) != 0 ) {
			idet_evt(EVT_MDM_TURNOFF);
		}
#endif
	} /* if (rtn != 0) */

#ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi *//* By M.M.Maeda 2002/10/24 */
	temp_reg = inp(NEWS_PORT);
	if (temp_reg & IO_BIT_NEWS) {	/* モデム割り込み要因がある */
		MDM_SetIO(POS_NSIE,OFF);	/* モデム割り込みをOFFします */
		MDM_SetIO(POS_NSIE,ON);		/* モデム割り込みをONします */
	}

	if ((MDM_DmaStart == MDM_DMA_READY) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
		if (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIA) {	/* 受信データ割り込み要因がある */
			MDM_SetIO(POS_RDBIE,OFF);				/* 受信データ割り込みをOFFします */
			MDM_SetIO(POS_RDBIE,ON);				/* 受信データ割り込みをONします */
		}
	}
#else
	MDM_REG_1F_PortStatus = inp(MDM_REG_1F_PORT);
	MDM_REG_1F_PortStatus &= ~IO_BIT_NEWS;
	outp(MDM_REG_1F_PORT, MDM_REG_1F_PortStatus);
#endif

	return;
}

/*************************************************************************
	module		:[モデム割り込み]
	function	:[
	]
	return		:[なし]
	common		:[
		ModemBlock
		ModemControl
		ModemWork
	]
	condition	:[
		モデム割り込みから呼ばれる
	]
	comment		:[
		MODE_TX_FSK	1	:
		MODE_TX_ECM	2	:
		MODE_TX_G3	3	:
		MODE_TX_TCF	4	:
		MODE_RX_FSK	5	:
		MODE_RX_ECM	6	:
		MODE_RX_G3	7	:
		MODE_RX_TCF	8	:
		MODE_RX_V23	
	]
	ProtoType	:[void MDM_ModemInterrupt(void){}]
	date		:[1994/04/13]
	update		:[1998/11/10]
	author		:[曽根岡拓、木元修、久保博]
*************************************************************************/
void MDM_ModemInterrupt(void)
{
	UBYTE i;
	i = 0;
	do {
		MDM_SetIO(POS_NEWS,OFF); /* NEWS を下げて、次の割り込みを許可する */
		MDM_ReadModemStatus();
		MDM_ModemInterruptSub();
#if defined (SAKAKI) /* added by H.Kubo 1998/10/04 */
		if (mdm_news_debug && MDM_GetIO(POS_RDBIA)) {
			outp(0,0); /* ICE 止めます。 */
			/* MDM_SetIO(POS_NEWS, OFF); */ /* もう一回。 */
		}
#endif
	} while ( MDM_IsNewModemInterruptRaised() && ((i++ < 3) || !MDM_IsModemInterruptActive()));
	return;
}

#else
/*************************************************************************
	module		:[モデム割り込み]
	function	:[
		1.１４４００ｂｐｓで受信時は、５５５μｓで次のＤＭＡを起動しなければ
		, データ取りこぼすため割り込み内で処理します
	]
	return		:[なし]
	common		:[
		ModemBlock
		ModemControl
		ModemWork
	]
	condition	:[
		モデム割り込みから呼ばれる
	]
	comment		:[
		MODE_TX_FSK	1	:
		MODE_TX_ECM	2	:
		MODE_TX_G3	3	:
		MODE_TX_TCF	4	:
		MODE_RX_FSK	5	:
		MODE_RX_ECM	6	:
		MODE_RX_G3	7	:モデム割り込みでは、特に行う処理は無い。
		MODE_RX_TCF	8	:モデム割り込みでは、特に行う処理は無い。
	]
	ProtoType	:[UWORD near MDM_ModemInterrupt(void){}]
	date		:[1994/04/13]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
UBYTE mdm_stat=0;
CONST UBYTE DBG_MDM_IO = 0;

void MDM_ModemInterrupt(void)
{
	UWORD rtn;

#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi */
	UBYTE temp_reg;
	temp_reg = inp(NEWS_PORT);	/** モデム割り込み受け付け */
	temp_reg &= ~IO_BIT_NEWS;
	outp(NEWS_PORT, temp_reg);
#endif

#if 0
// #if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
// 	if ((FCM_S1_Scramble == TRUE) && (ModemBlock.Mode == MODE_RX_ECM)) {
// 		return;
// 	}
// #endif
#endif

	rtn = 0;

	/** ２１００Ｈｚ検出（ＣＥＤ,ＡＮＳａｍ） **/
	MDM_REG_0B_PortStatus = inp(MDM_REG_0B_PORT);
	if (MDM_REG_0B_PortStatus & IO_BIT_ATV25) {
		SYS_V8DetectATV25Flag = 1;
		rtn |= MDM_EVT_ATV25_DETECT_BIT;
	}

	/** ＤＭＡの起動が早すぎる対策（暫定） **//**  By O.K Jan.17,1996 **/
	MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT);
	MDM_REG_1E_PortStatus = inp(MDM_REG_1E_PORT);
	if ((MDM_REG_0F_PortStatus & IO_BIT_RLSD) && (MDM_REG_1E_PortStatus & IO_BIT_RDBF)) {
		if ((ModemBlock.Mode == MODE_RX_ECM)&&(MDM_DmaStart == MDM_DMA_READY)) {



#if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
			if (FCM_S1_Scramble == FALSE) {
#endif
				
				
				
				/* Added by H.Kubo 1997/10/08
				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
				*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
				DMA_RequestEnableInternalDMAUGo(DMA_CH_RX);
#else
				DMA_RequestEnable(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#endif
				MDM_DmaStart = MDM_DMA_GO;

				/* 
				** R288F VERSION 22P以上
				** 1998/10/09 By H.Hirao
				** Condition changd by H.Kubo 1998/10/17
				*/
		 		IsRlsdAndRdbfOn = 1;
		 		
	 			
	 			
#if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
	 		}
#endif
			
			
			
		}
		else if ((ModemBlock.Mode == MODE_RX_FSK)&&(MDM_DmaStart == MDM_DMA_READY)) {
			/* Added by H.Kubo 1997/10/08
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
			DMA_RequestEnableInternalDMAUGo(DMA_CH_RX);
#else
			DMA_RequestEnable(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#endif
			MDM_DmaStart = MDM_DMA_GO;

			/*
			** R288F VERSION 22P以上
			** by H.Kubo 1998/10/17
			*/
			IsRlsdAndRdbfOn = 1;
		}

		/*
		** R288F VERSION 24P
		** For configuring RLSD drop-out timer. by H.Kubo 1998/10/21
		*/
		else if ((!IsRlsdAndRdbfOn) && ((ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_G3))) {
			IsRlsdAndRdbfOn = 1;
		}

		else if ((ModemBlock.Mode == MODE_RX_ND) && (MDM_DmaStart == MDM_DMA_READY)) {
			/* Added by H.Kubo 1997/10/08
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
			DMA_RequestEnable(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
			MDM_DmaStart = MDM_DMA_GO;
			rtn |= MDM_EVT_RX_RDBF_BIT;
		}
		if ((ModemBlock.Mode == MODE_RX_ND) && MDM_ND_WaitFirstDataEvent) {
			rtn |= MDM_EVT_RX_RDBF_BIT;
			MDM_ND_WaitFirstDataEvent = FALSE;
		}
	}

	if (!(SYS_V34ProcedureExecuting())) {	/** 従来のプロトコルならば **/
		/* 1997/02/01 Y.Murata
		 * モデム割り込みの中でトレーニング信号とＴＣＦデータの検出を行っているが
		 * タイミングにより割り込みがとれない時がある（特にＴＣＦデータ）
		 * 今まではたまたま動いていた。ここでの処理は気休めになってしまっている
		*/
		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_TRDETON) {
			/*--------------------------------------*/
			/* PNSUC ﾋﾞｯﾄをみる 1997/01/16 Y.Murata */
			/*--------------------------------------*/
			/* 両方みる  1997/01/28 Y.Murata        */
			/*--------------------------------------*/
				/** ＴＣＦ前モデムトレーニング受信 **/
				MDM_REG_0D_PortStatus = inp(MDM_REG_0D_PORT);
				MDM_REG_0A_PortStatus = inp(MDM_REG_0A_PORT);
				if ((MDM_REG_0D_PortStatus & IO_BIT_PNDET) || (MDM_REG_0A_PortStatus & IO_BIT_PNSUC)) {
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					rtn |= MDM_EVT_MDM_PNSUC_BIT;	/* return(EVT_MDM_PNSUC) */
				}
			}
		}
		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_RLSDON) {
				MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT);
				/** ＴＣＦデータ受信 */
				if (MDM_REG_0F_PortStatus & IO_BIT_RLSD) {
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					rtn |= MDM_EVT_MDM_PNSUC_BIT;	/* return(EVT_MDM_PNSUC) */
				}
			}
		}
	}	/* end of if (!(SYS_V34ProcedureExecuting())) { */

	switch (ModemBlock.Mode) {	/**	交信モード	*/
	case MODE_TX_FSK:	/**	ＦＳＫ送信モードの時	*/
	case MODE_TX_ECM:	/**	ＥＣＭ送信モードの時	*/
		mdm_stat = inp(MDM_REG_0A_PORT);					/**	ＨＤＬＣデータコントロール表示レジスタ読み込み	*/
		if (ModemControl.Status & STAT_ALSENT) {			/**	送出データがセット済みの時	*/
			if (mdm_stat & IO_BIT_FLAGS) {					/**	ＦＣＳ割り込み発生した時	*/
				ModemControl.Status &= (~STAT_ALSENT);		/**	ＦＣＳ割り込み待ち解除	*/
				ModemInterruptFlag = 1;						/**	モデム割り込み発生フラグセット	*/
#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2001/12/18 T.Takagi */
				MDM_SetIO(POS_TEOF,OFF);
#else
				MDM_REG_11_PortStatus = inp(MDM_REG_11_PORT);
				MDM_REG_11_PortStatus &= ~IO_BIT_TEOF;
				outp(MDM_REG_11_PORT, MDM_REG_11_PortStatus);
#endif
				rtn |= MDM_EVT_TX_FCS_COMPLETE_BIT; 		/* V21ch2 フラグ(7E) 検出 */
			}
		}
		break;
	case MODE_RX_ECM:	/**	ＥＣＭ受信モード	*/
		mdm_stat = inp(MDM_REG_0A_PORT);	/**	モデム割り込みステータス読み込み */
		if (SYS_V34ProcedureExecuting()) {	/* V34 */
			if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_SYNCD)) {	/**	フラグ検出フェーズ時	*/
				ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
				ModemControl.Status |= STAT_FCSDET;	/**	ＦＣＳ検出フェーズ設定	*/
				/*----------------------------------------------*/
				/**	イベントセット処理							*/
				/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
				/*----------------------------------------------*/
				ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
				rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
			}
		}
		else {
			if (CHK_HIGH_MODE_CATCH()) {	/* 高速のみまつ 1997/01/28 Y.Murata */
				/* Nothing */
			}
			else {
				if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_FLAGDT)) {	/**	フラグ検出フェーズ時	*/
					ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
					ModemControl.Status |= STAT_FCSDET;	/**	ＦＣＳ検出フェーズ設定	*/
					/*----------------------------------------------*/
					/**	イベントセット処理							*/
					/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
					/*----------------------------------------------*/
					ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
					rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
				}
			}
		}

#ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
		if (MDM_DmaStart == MDM_DMA_MASK) {
			break;	/* case文脱出 *//* DMAの再起動は、まだしたらダメ。まだDMAのセットアップできてません */
		}
#endif

		/* ロックウェルのソースから By O.K Feb.20,1996 */
		if (mdm_stat & IO_BIT_FE) {
#if defined(POPLAR_F)
			DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#endif
			/* Added by H.Kubo 1997/10/09
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
			DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
			MDM_DmaStart = MDM_DMA_GO;
		}
		else if (mdm_stat & IO_BIT_OE) {
			
			
			
			
			
#if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
			if (FCM_S1_Scramble == FALSE) {
#endif
			
			
			
			
			
#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi */
			temp_reg = inp(OE_PORT);
			temp_reg &= ~IO_BIT_OE;
			outp(OE_PORT, temp_reg);
#endif
			
#if defined(POPLAR_F)
			DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
			DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#endif
			/* Added by H.Kubo 1997/10/08
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
			DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
			MDM_DmaStart = MDM_DMA_GO;
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* added by H.Kubo 1998/01/29 */
			
			
			
			
			
#if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
			}
#endif
			
			
			
			
			
		}
		
		
		
		
		
		else if (mdm_stat & IO_BIT_SYNCD) {	/** test **/
#if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
		if (FCM_S1_Scramble == FALSE) {
#endif
			if ((!(mdm_stat & IO_BIT_PE))&&(MDM_DmaStart != MDM_DMA_MASK)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */

				/* ここに来るまでに次のフレームの先頭データを受信したときの処理を追加。 Changed by H.Kubo 1999/01/26 */
				/* DMA(DTC) はここで止めないといけない。カウンタを読んでからマスクするまでの間に次の DREQ が来たら
				** 終了割り込みがかかることがある。
				** by H.Kubo 1999/01/26 */
#if defined(POPLAR_F)
				DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
				DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/26 */
#endif
				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
				ModemControl.UsedCount++;
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
					/* フレーム最後のフラグを受信してからここに来るまでの間に次のフレームの先頭を受信していたら、
					** 次のフレームの先頭は次のモデムバッファにコピーして残りのデータの受信を始めます。
					** そうでなければ、次のフレームは普通に次のモデムバッファの先頭から受信し始めます。
					** by H.Kubo 1999/01/26
					*/
				if ((MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1))
					&& (MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] == 0xff)) {
					/* 次のアドレスフィールドのデータが末尾にある場合 */
					MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] = 0x0;
					MDM_RxSize[ModemControl.WritePoint] -= 1; /* 次のモデムバッファに移した分だけ引き算します。 */
					NextMdmBufWritePointSetExtRom();
					MDM_ModemBuffer[ModemControl.WritePoint][0] = 0xff;
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
					SelectDreqDirection(RX_DMA);
#else
					SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
					DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
#else
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
#endif
				}
				else {
					NextMdmBufWritePointSetExtRom();
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
					SelectDreqDirection(RX_DMA);
#else
					SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
					DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
				}
				MDM_DmaStart = MDM_DMA_GO;
			}
			else {
#if defined(POPLAR_F)
				DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
#endif
				/* Added by H.Kubo 1997/10/09
				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
				*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif				
#if defined(POPLAR_F)
				DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);/**  By O.K Jan.K Jan.23,1996 **/
#else
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);/**  By O.K Jan.K Jan.23,1996 **/
#endif
				MDM_DmaStart = MDM_DMA_GO;
			}
#if defined (KEISATSU) /* 警察FAX 05/08/31 石橋正和 */
		}
#endif
		}
		
		
		
		
		
		break;
	case MODE_RX_FSK:	/**	ＦＳＫ受信モード	*/
		mdm_stat = inp(MDM_REG_0A_PORT);	/**	ＨＤＬＣデータコントロール表示レジスタ読み込み	*/
		if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_SYNCD)) {	/**	フラグ検出フェーズ時	*/
			/* 1997/04/01 Y.Murata
			 * 会話予約でPIPとPRI_EOPがぶつかってしまう。SYNCDの誤検出が原因。
			 * RLSDがONの時のみSYNCDを見に行く。
			*/
			if (SYS_V34ProcedureExecuting() == 0) {
#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2001/12/18 T.Takagi */
				if (MDM_GetIO(POS_RLSD)) {
#else
				if (MDM_REG_0F_PortStatus & IO_BIT_RLSD) {
#endif
					ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
					ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
					/**	ＨＤＬＣモデムモード設定	*/
					/**	ＦＣＳ検出時、割り込み発生設定	*/
					/**	受信データ要求ＯＮ	*/
					/*----------------------------------------------*/
					/**	イベントセット処理							*/
					/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
					/*----------------------------------------------*/
					ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
					rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
				}
			}
			else {
				ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
				ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
				/**	ＨＤＬＣモデムモード設定	*/
				/**	ＦＣＳ検出時、割り込み発生設定	*/
				/**	受信データ要求ＯＮ	*/
				/*----------------------------------------------*/
				/**	イベントセット処理							*/
				/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
				/*----------------------------------------------*/
				ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
				rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
			}
		}

#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi */
		if (MDM_DmaStart == MDM_DMA_MASK) {
			break;	/* case文脱出 *//* DMAの再起動は、まだしたらダメ。まだDMAのセットアップできてません。 */
		}
#endif

		/* ロックウェルのソースから By O.K Feb.20,1996 */
		if (mdm_stat & IO_BIT_FE) { /* ABORT シーケンス検出 */
#if defined(POPLAR_F)
			DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif

			/* Added by H.Kubo 1997/10/09
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
			/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)-1); */
#if defined(POPLAR_F)
			DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
			MDM_DmaStart = MDM_DMA_GO;
		}
		else if (mdm_stat & IO_BIT_OE) { /* 受信オーバーラン */
#ifdef MDM_INT_DMA_BUG_FIX	/* YAWARAより移植 2002/01/17 T.Takagi */
			temp_reg = inp(OE_PORT);
			temp_reg &= ~IO_BIT_OE;
			outp(OE_PORT, temp_reg);
#endif

#if defined(POPLAR_F)
			DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif

			/* Added by H.Kubo 1997/10/09
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
			/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)-1); */
#if defined(POPLAR_F)
			DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1),(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1),(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
			MDM_DmaStart = MDM_DMA_GO;
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* added by H.Kubo 1998/01/29 */
		}
		else
		if (mdm_stat & IO_BIT_SYNCD) {	/** test **/
			if ((!(mdm_stat & IO_BIT_PE))&&(MDM_DmaStart != MDM_DMA_MASK)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */
				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
				/*----------------------*/
				/**	フレーム補正処理	*/
				/*----------------------*/
				if (ModemBufferFormatControl(ModemControl.WritePoint) == NG) {	/**	不正フレームを受信した時	*/
#if defined(POPLAR_F)
					DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
					DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif

					/* Added by H.Kubo 1997/10/09
					**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
					*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
					SelectDreqDirection(RX_DMA);
#else
					SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
					DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
					MDM_DmaStart = MDM_DMA_GO;
				}
				else {	/**	正常なフレームを受信した時	*/
					if (MDM_ModemBuffer[ModemControl.WritePoint][2] == EchoFCF) {
#if defined(POPLAR_F)
						DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
						DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif
						/* Added by H.Kubo 1997/10/09
						**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
						*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
						SelectDreqDirection(RX_DMA);
#else
						SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
						DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
						DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
						MDM_DmaStart = MDM_DMA_GO;
						if (HighSpeedCheckFlag == 1) {
							EchoFrameRcvFlag = 1;
						}
					}
					else {
						ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
						NextMdmBufWritePointSetExtRom();
#if defined(POPLAR_F)
						DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
						DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif
						/* Added by H.Kubo 1997/10/09
						**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
						*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
						SelectDreqDirection(RX_DMA);
#else
						SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
						DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
						DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
						MDM_DmaStart = MDM_DMA_GO;
					}
				}
			}
			else {	/**	ＦＣＳエラー時	*/
#if defined(POPLAR_F)
				DMA_RequestMaskInternalDMAU(DMA_CH_RX);
#else
				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif
				/* Added by H.Kubo 1997/10/09
				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
				*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif
#if defined(POPLAR_F)
				DMA_RestartInternalDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#else
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
#endif
				MDM_DmaStart = MDM_DMA_GO;
			}
		}
		break;
	case MODE_RX_G3: /* Added by H.Kubo 1998/01/30 */
		mdm_stat = inp(MDM_REG_0A_PORT);	/**	モデム割り込みステータス読み込み */
		if (mdm_stat & IO_BIT_OE) { /* 受信オーバーランを起こしていたら */
#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2001/12/18 T.Takagi */
			MDM_SetIO(POS_OE, OFF); /* OE bit をリセット。*/
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN;	/* メンテナンススイッチに通知*/
#else
			MDM_REG_0A_PortStatus = mdm_stat;
			MDM_REG_0A_PortStatus &= ~IO_BIT_OE;
			outp(MDM_REG_0A_PORT, MDM_REG_0A_PortStatus);
#endif
		}
		break;
	case MODE_RX_ND:
		mdm_stat = inp(MDM_REG_0A_PORT);	/**	モデム割り込みステータス読み込み */
		if (mdm_stat & IO_BIT_OE) { /* 受信オーバーランを起こしていたら */
#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2001/12/18 T.Takagi */
			MDM_SetIO(POS_OE, OFF);	 /* OE bit をリセット。*/
#else
			MDM_REG_0A_PortStatus = mdm_stat;
			MDM_REG_0A_PortStatus &= ~IO_BIT_OE;
			outp(MDM_REG_0A_PORT, MDM_REG_0A_PortStatus);
#endif
		}
		break;
	default:
		break;
	}
	if ((MDM_DmaStart == MDM_DMA_GO) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)
		MDM_SetIO(POS_RDBIE,OFF);
#else
		MDM_REG_1E_PortStatus = inp(MDM_REG_1E_PORT);
		MDM_REG_1E_PortStatus &= ~IO_BIT_RDBIE;
		outp(MDM_REG_1E_PORT, MDM_REG_1E_PortStatus);
#endif
		MDM_DmaStart = MDM_DMA_CONTINUE;
	}

	/* Ported from \src\clover\src\INT_MDM.ASM and translated into C by H.Kubo 1997/07/19 */
	if (rtn != 0 ) {
		if ( (rtn & MDM_EVT_ATV25_DETECT_BIT) != 0 ) {
			idet_evt(EVT_MDM_ATV25);
		}
		if ( (rtn & MDM_EVT_MDM_PNSUC_BIT) != 0 ) {
			idet_evt(EVT_MDM_PNSUC);
		}
		if ( (rtn & MDM_EVT_TX_FCS_COMPLETE_BIT) != 0 ) {
			idet_evt(EVT_TX_FCS_COMPLETE);
		}
		if ( (rtn & MDM_EVT_RX_FLG_DETECT_BIT) != 0 ) {
			idet_evt(EVT_RX_FLG_DETECT);
		}
		if ( (rtn & MDM_EVT_RX_RDBF_BIT) != 0 ) {
			idet_evt(EVT_MDM_RX_NEW_DATA);
		}
	}

#if defined (HINOKI2) || defined (SATSUKI2) || defined(STOCKHM2)	/* 2001/12/18 T.Takagi */
 #ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	temp_reg = inp(NEWS_PORT);
	if (temp_reg & IO_BIT_NEWS) {	/* モデム割り込み要因がある */
		MDM_SetIO(POS_NSIE,OFF);	/* モデム割り込みをOFFします */
		MDM_SetIO(POS_NSIE,ON);		/* モデム割り込みをONします */
	}

	if ((MDM_DmaStart == MDM_DMA_READY) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
		if (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIA) {	/* 受信データ割り込み要因がある */
			MDM_SetIO(POS_RDBIE,OFF);				/* 受信データ割り込みをOFFします */
			MDM_SetIO(POS_RDBIE,ON);				/* 受信データ割り込みをONします */
		}
	}
 #else
	MDM_SetIO(POS_NEWS,OFF);	/** モデム割り込み受け付け */
 #endif
#else
 #ifdef MDM_INT_DMA_BUG_FIX		/* YAWARAより移植 2002/01/17 T.Takagi */
	temp_reg = inp(NEWS_PORT);
	if (temp_reg & IO_BIT_NEWS) {	/* モデム割り込み要因がある */
		MDM_SetIO(POS_NSIE,OFF);	/* モデム割り込みをOFFします */
		MDM_SetIO(POS_NSIE,ON);		/* モデム割り込みをONします */
	}

	if ((MDM_DmaStart == MDM_DMA_READY) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
		if (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIA) {	/* 受信データ割り込み要因がある */
			MDM_SetIO(POS_RDBIE,OFF);				/* 受信データ割り込みをOFFします */
			MDM_SetIO(POS_RDBIE,ON);				/* 受信データ割り込みをONします */
		}
	}
 #else
	MDM_REG_1F_PortStatus = inp(MDM_REG_1F_PORT);
	MDM_REG_1F_PortStatus &= ~IO_BIT_NEWS;
	outp(MDM_REG_1F_PORT, MDM_REG_1F_PortStatus);
 #endif
#endif
}
#endif

#if 0
//void MDM_ModemInterrupt(void)
//{
//	UWORD rtn;
//	rtn = 0;
//
//
//if (DBG_MDM_IO) {
//	/* For Debug by O.Kimoto 1996/03/05 */
//	(void)(inp(MDM_REG_0A_PORT));
//	(void)(inp(MDM_REG_0B_PORT));
//	(void)(inp(MDM_REG_0C_PORT));
//	(void)(inp(MDM_REG_0D_PORT));
//	(void)(inp(MDM_REG_0E_PORT));
//	(void)(inp(MDM_REG_0F_PORT));
//	(void)(inp(MDM_REG_12_PORT));
//	(void)(inp(MDM_REG_14_PORT));
//	(void)(inp(MDM_REG_16_PORT));
//	(void)(inp(MDM_REG_17_PORT));
//	(void)(inp(MDM_REG_1A_PORT));
//	(void)(inp(MDM_REG_1B_PORT));
//	(void)(inp(MDM_REG_1E_PORT));
//	(void)(inp(MDM_REG_1F_PORT));
//}
//
//	/** ２１００Ｈｚ検出（ＣＥＤ,ＡＮＳａｍ） **/
//	MDM_REG_0B_PortStatus = inp(MDM_REG_0B_PORT);
//	if (MDM_REG_0B_PortStatus & IO_BIT_ATV25) {
//		SYS_V8DetectATV25Flag = 1;
//		rtn |= MDM_EVT_ATV25_DETECT_BIT;	/* return(EVT_MDM_ATV25) */
//	}
//
//	/** ＤＭＡの起動が早すぎる対策（暫定） **//**  By O.K Jan.17,1996 **/
//	MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT);
//	MDM_REG_1E_PortStatus = inp(MDM_REG_1E_PORT);
//	if ((MDM_REG_0F_PortStatus & IO_BIT_RLSD) && (MDM_REG_1E_PortStatus & IO_BIT_RDBF)) {
//		if ((ModemBlock.Mode == MODE_RX_ECM)&&(MDM_DmaStart == MDM_DMA_READY)) {
//			/* Added by H.Kubo 1997/10/08
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//			DMA_RequestEnable(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
//			MDM_DmaStart = MDM_DMA_GO;
//
//			/* 
//			** R288F VERSION 22P以上
//			** 1998/10/09 By H.Hirao
//			** Condition changd by H.Kubo 1998/10/17
//			*/
//	 		IsRlsdAndRdbfOn = 1;
//
//		}
//		else if ((ModemBlock.Mode == MODE_RX_FSK)&&(MDM_DmaStart == MDM_DMA_READY)) {
//			/* Added by H.Kubo 1997/10/08
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//			DMA_RequestEnable(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
//			MDM_DmaStart = MDM_DMA_GO;
//
//			/*
//			** R288F VERSION 22P以上
//			** by H.Kubo 1998/10/17
//			*/
//			IsRlsdAndRdbfOn = 1;
//		}
//
//		/*
//		** R288F VERSION 24P
//		** For configuring RLSD drop-out timer. by H.Kubo 1998/10/21
//		*/
//		else if ((!IsRlsdAndRdbfOn) && ((ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_G3))) {
//			IsRlsdAndRdbfOn = 1;
//		}
//
//		else if ((ModemBlock.Mode == MODE_RX_ND) && (MDM_DmaStart == MDM_DMA_READY)) {
//			/* Added by H.Kubo 1997/10/08
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//			DMA_RequestEnable(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
//			MDM_DmaStart = MDM_DMA_GO;
//			rtn |= MDM_EVT_RX_RDBF_BIT;
//		}
//		if ((ModemBlock.Mode == MODE_RX_ND) && MDM_ND_WaitFirstDataEvent) {
//			rtn |= MDM_EVT_RX_RDBF_BIT;
//			MDM_ND_WaitFirstDataEvent = FALSE;
//		}
//	}
//
//	if (!(SYS_V34ProcedureExecuting())) {	/** 従来のプロトコルならば **/
//		/* 1997/02/01 Y.Murata
//		 * モデム割り込みの中でトレーニング信号とＴＣＦデータの検出を行っているが
//		 * タイミングにより割り込みがとれない時がある（特にＴＣＦデータ）
//		 * 今まではたまたま動いていた。ここでの処理は気休めになってしまっている
//		*/
//		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
//			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_TRDETON) {
//			/*--------------------------------------*/
//			/* PNSUC ﾋﾞｯﾄをみる 1997/01/16 Y.Murata */
//			/*--------------------------------------*/
//			/* 両方みる  1997/01/28 Y.Murata        */
//			/*--------------------------------------*/
//				/** ＴＣＦ前モデムトレーニング受信 **/
//				MDM_REG_0D_PortStatus = inp(MDM_REG_0D_PORT);
//				MDM_REG_0A_PortStatus = inp(MDM_REG_0A_PORT);
//				if ((MDM_REG_0D_PortStatus & IO_BIT_PNDET) || (MDM_REG_0A_PortStatus & IO_BIT_PNSUC)) {
//					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
//					rtn |= MDM_EVT_MDM_PNSUC_BIT;	/* return(EVT_MDM_PNSUC) */
//				}
//			}
//		}
//		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
//			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_RLSDON) {
//				MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT);
//				/** ＴＣＦデータ受信 */
//				if (MDM_REG_0F_PortStatus & IO_BIT_RLSD) {
//					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
//					rtn |= MDM_EVT_MDM_PNSUC_BIT;	/* return(EVT_MDM_PNSUC) */
//				}
//			}
//		}
//	}	/* end of if (!(SYS_V34ProcedureExecuting())) { */
//
//	switch (ModemBlock.Mode) {	/**	交信モード	*/
//	case MODE_TX_FSK:	/**	ＦＳＫ送信モードの時	*/
//	case MODE_TX_ECM:	/**	ＥＣＭ送信モードの時	*/
//		mdm_stat = inp(MDM_REG_0A_PORT);					/**	ＨＤＬＣデータコントロール表示レジスタ読み込み	*/
//		if (ModemControl.Status & STAT_ALSENT) {			/**	送出データがセット済みの時	*/
//			if (mdm_stat & IO_BIT_FLAGS) {					/**	ＦＣＳ割り込み発生した時	*/
//				ModemControl.Status &= (~STAT_ALSENT);		/**	ＦＣＳ割り込み待ち解除	*/
//				ModemInterruptFlag = 1;						/**	モデム割り込み発生フラグセット	*/
//				MDM_SetIO(POS_TEOF,OFF);
//				rtn |= MDM_EVT_TX_FCS_COMPLETE_BIT; 		/* V21ch2 フラグ(7E) 検出 */
//			}
//		}
//		break;
//	case MODE_RX_ECM:	/**	ＥＣＭ受信モード	*/
//		mdm_stat = inp(MDM_REG_0A_PORT);	/**	モデム割り込みステータス読み込み */
//		if (SYS_V34ProcedureExecuting()) {	/* V34 */
//			if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_SYNCD)) {	/**	フラグ検出フェーズ時	*/
//				ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
//				ModemControl.Status |= STAT_FCSDET;	/**	ＦＣＳ検出フェーズ設定	*/
//				/*----------------------------------------------*/
//				/**	イベントセット処理							*/
//				/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
//				/*----------------------------------------------*/
//				ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
//				rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
//			}
//
//#if (0)
//** /* プライマリーチャンネルの終端でループすることが在ります。
//** ** ついては、そのデバッグのために下記ＰＣＯＦＦビットを使ってみます。
//** ** 尚、処理はかなり暫定ですので、対応するには注意が必要です。
//** ** by O.Kimoto 1998/11/28
//** */
//** #if (0)
//** ** /* ＰＣＯＦＦでプライマリーチャンネルのＴｕｒｎＯｆｆを検出するのには、下記では不十分です。
//** ** ** よって、プライマリーチャンネルのＴｕｒｎＯｆｆの検出は－２０Ｐまでと同一処理とします。
//** ** ** By O.Kimoto 1998/11/19
//** ** */
//** ** #if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/30 */
//** ** 			/* R4.2 対策。  Primary channel OFF の検出が 20P までで使っていた SECRXBを監視する方法ではだめなことがある。 by H.Kubo 1998/10/30 */
//** **  #if (PRO_MODEM_R288F_VERSION >= FM336_VERSION_12P) /* CONEXANT(旧Rockwell) FM336 テスト用コード。 by H.Kubo 1999/03/08 */
//** ** 			if ((SYS_ModemVersion == MDM_L6713_24P)|| (SYS_ModemVersion == MDM_L6713_26P) || (SYS_ModemVersion >= MDM_L6719_12P_ES)) {
//** **  #else
//** ** 			if ((SYS_ModemVersion == MDM_L6713_24P)|| (SYS_ModemVersion == MDM_L6713_26P)) {
//** **  #endif
//** ** 				MDM_REG_0C_PortStatus = inp(MDM_REG_0C_PORT);
//** ** 				if (MDM_RlsdTurnOffCheckFlag == TRUE) {
//** ** 					if (MDM_REG_0C_PortStatus & IO_BIT_PCOFF) {
//** ** 						MDM_REG_16_PortStatus = inp(MDM_REG_16_PORT);
//** ** 						if ((MDM_REG_16_PortStatus == 0xA3) ) { /* データ受信中か？ */
//** ** 							MDM_RlsdTurnOffFlag = 1;
//** ** 							rtn |= MDM_EVT_PCOFF_DETECT_BIT;
//** ** 							MDM_PreviousPCOFF_Status = 0xff; /* PCOFF 検出したら、 0xff 入れます。デバッグ用。 by H.Kubo 1998/10/31 */
//** ** 						}
//** ** 					}
//** ** 				}
//** ** 			}
//** ** #endif
//** #endif
//#endif
//
//		}
//		else {
//			if (CHK_HIGH_MODE_CATCH()) {	/* 高速のみまつ 1997/01/28 Y.Murata */
//				/* Nothing */
//			}
//			else {
//				if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_FLAGDT)) {	/**	フラグ検出フェーズ時	*/
//					ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
//					ModemControl.Status |= STAT_FCSDET;	/**	ＦＣＳ検出フェーズ設定	*/
//					/*----------------------------------------------*/
//					/**	イベントセット処理							*/
//					/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
//					/*----------------------------------------------*/
//					ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
//					rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
//				}
//			}
//		}
//		/* ロックウェルのソースから By O.K Feb.20,1996 */
//		if (mdm_stat & IO_BIT_FE) {
//			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
//			/* Added by H.Kubo 1997/10/09
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//
//			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//			MDM_DmaStart = MDM_DMA_GO;
//		}
//		else if (mdm_stat & IO_BIT_OE) {
//			DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
//			/* Added by H.Kubo 1997/10/08
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//
//			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//			MDM_DmaStart = MDM_DMA_GO;
//			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* added by H.Kubo 1998/01/29 */
//		}
//		else if (mdm_stat & IO_BIT_SYNCD) {	/** test **/
//			if ((!(mdm_stat & IO_BIT_PE))&&(MDM_DmaStart != MDM_DMA_MASK)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */
//
//				/* ここに来るまでに次のフレームの先頭データを受信したときの処理を追加。 Changed by H.Kubo 1999/01/26 */
//				/* DMA(DTC) はここで止めないといけない。カウンタを読んでからマスクするまでの間に次の DREQ が来たら
//				** 終了割り込みがかかることがある。
//				** by H.Kubo 1999/01/26 */
//				DMA_RequestMask(DMA_CH_RX);  /* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/26 */
//				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
//				ModemControl.UsedCount++;
//				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
//					/* フレーム最後のフラグを受信してからここに来るまでの間に次のフレームの先頭を受信していたら、
//					** 次のフレームの先頭は次のモデムバッファにコピーして残りのデータの受信を始めます。
//					** そうでなければ、次のフレームは普通に次のモデムバッファの先頭から受信し始めます。
//					** by H.Kubo 1999/01/26
//					*/
//				if ((MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1))
//					&& (MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] == 0xff)) {
//					/* 次のアドレスフィールドのデータが末尾にある場合 */
//					MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] = 0x0;
//					MDM_RxSize[ModemControl.WritePoint] -= 1; /* 次のモデムバッファに移した分だけ引き算します。 */
//					NextMdmBufWritePointSetExtRom();
//					MDM_ModemBuffer[ModemControl.WritePoint][0] = 0xff;
//					SetModemDMA_DirectionRx();
//					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
//				}
//				else {
//					NextMdmBufWritePointSetExtRom();
//					SetModemDMA_DirectionRx();
//					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//				}
//				MDM_DmaStart = MDM_DMA_GO;
//			}
//			else {
//				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU deleted by H. Kubo 1997/06/24 */
//				/* Added by H.Kubo 1997/10/09
//				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//				*/
//				SetModemDMA_DirectionRx();
//				
//				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);/**  By O.K Jan.K Jan.23,1996 **/
//				MDM_DmaStart = MDM_DMA_GO;
//			}
//		}
//		break;
//	case MODE_RX_FSK:	/**	ＦＳＫ受信モード	*/
//		mdm_stat = inp(MDM_REG_0A_PORT);	/**	ＨＤＬＣデータコントロール表示レジスタ読み込み	*/
//		if ((ModemControl.Status & STAT_FLGDET) && (mdm_stat & IO_BIT_SYNCD)) {	/**	フラグ検出フェーズ時	*/
//			/* 1997/04/01 Y.Murata
//			 * 会話予約でPIPとPRI_EOPがぶつかってしまう。SYNCDの誤検出が原因。
//			 * RLSDがONの時のみSYNCDを見に行く。
//			*/
//			if (SYS_V34ProcedureExecuting() == 0) {
//				if (MDM_GetIO(POS_RLSD)) {
//					ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
//					ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
//					/**	ＨＤＬＣモデムモード設定	*/
//					/**	ＦＣＳ検出時、割り込み発生設定	*/
//					/**	受信データ要求ＯＮ	*/
//					/*----------------------------------------------*/
//					/**	イベントセット処理							*/
//					/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
//					/*----------------------------------------------*/
//					ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
//					rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
//				}
//			}
//			else {
//				ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
//				ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
//				/**	ＨＤＬＣモデムモード設定	*/
//				/**	ＦＣＳ検出時、割り込み発生設定	*/
//				/**	受信データ要求ＯＮ	*/
//				/*----------------------------------------------*/
//				/**	イベントセット処理							*/
//				/*	EVT_RX_FLG_DETECT	:	フラグ検出タスクへ	*/
//				/*----------------------------------------------*/
//				ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
//				rtn |= MDM_EVT_RX_FLG_DETECT_BIT;
//			}
//		}
//		/* ロックウェルのソースから By O.K Feb.20,1996 */
//		if (mdm_stat & IO_BIT_FE) { /* ABORT シーケンス検出 */
//			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
//
//			/* Added by H.Kubo 1997/10/09
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//
//			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
//			/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)-1); */
//			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//			MDM_DmaStart = MDM_DMA_GO;
//		}
//		else if (mdm_stat & IO_BIT_OE) { /* 受信オーバーラン */
//			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
//
//			/* Added by H.Kubo 1997/10/09
//			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//			*/
//			SetModemDMA_DirectionRx();
//
//			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
//			/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)-1); */
//			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1),(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//			MDM_DmaStart = MDM_DMA_GO;
//			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN; /* added by H.Kubo 1998/01/29 */
//		}
//		else
//		if (mdm_stat & IO_BIT_SYNCD) {	/** test **/
//			if ((!(mdm_stat & IO_BIT_PE))&&(MDM_DmaStart != MDM_DMA_MASK)) {	/**	ＦＣＳ計算結果ＯＫの時	*//* For Debug By O.K Feb.16,1996 */
//				GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
//				/*----------------------*/
//				/**	フレーム補正処理	*/
//				/*----------------------*/
//				if (ModemBufferFormatControl(ModemControl.WritePoint) == NG) {	/**	不正フレームを受信した時	*/
//					DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
//
//					/* Added by H.Kubo 1997/10/09
//					**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//					*/
//					SetModemDMA_DirectionRx();
//
//					DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//					MDM_DmaStart = MDM_DMA_GO;
//				}
//				else {	/**	正常なフレームを受信した時	*/
//					if (MDM_ModemBuffer[ModemControl.WritePoint][2] == EchoFCF) {
//						DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
//
//						/* Added by H.Kubo 1997/10/09
//						**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//						*/
//						SetModemDMA_DirectionRx();
//
//						DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//						MDM_DmaStart = MDM_DMA_GO;
//						if (HighSpeedCheckFlag == 1) {
//							EchoFrameRcvFlag = 1;
//						}
//					}
//					else {
//						ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
//						NextMdmBufWritePointSetExtRom();
//						DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
//
//						/* Added by H.Kubo 1997/10/09
//						**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//						*/
//						SetModemDMA_DirectionRx();
//
//						DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//						MDM_DmaStart = MDM_DMA_GO;
//					}
//				}
//			}
//			else {	/**	ＦＣＳエラー時	*/
//				DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
//
//				/* Added by H.Kubo 1997/10/09
//				**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
//				*/
//				SetModemDMA_DirectionRx();
//
//				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  RX_FSK_HDLC_LENGTH, (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//				MDM_DmaStart = MDM_DMA_GO;
//			}
//		}
//#if (0)
////		/*
////		** V34受信で、フラグ検出フェーズになる前に、フラグ検出割込みが入ると、
////		** １発目のポストメッセージを取りこぼす。この後、送信側は２発目の
////		** ポストメッセージを送っているのに、6sタイムアップするまで、
////		** フラグ検出割込みが入ってこないため、２発目もとれない。
////		** （再コンフィグ後の３発目はとれることが多い）
////		** 以下の処理を追加すると、２発目のフラグ検出割込みが起きることが
////		** 多くなる。
////		** ただし、約1m600uかかってしまうので割込み処理内ではまずい
////		**
////		** 1999/08/05 by K.Okada
////		*/
////		if (!(mdm_stat & IO_BIT_SYNCD)) {
////			if (ModemControl.Status & STAT_FLGDET) {
////				/** 割込みOFF */
////				MDM_SetIO(POS_RDBIE,OFF);
////				MDM_SetIO(POS_NSIE,OFF);
////				
////				/** 受信データバッファ読み出し・受信FIFOクリア */
////				for( count=0; count<16; count++ ) {
////					(void)inp(MDM_REG_00_PORT);
////				}
////				MDM_SetRxFIFOClear();
////				
////				/** ステータスクリア */
////				MDM_SetIO(POS_PE, OFF);
////				MDM_SetIO(POS_FE, OFF);
////				MDM_SetIO(POS_OE, OFF);
////				MDM_SetIO(POS_SYNCD, OFF);
////				MDM_SetIO(POS_PNSUC,OFF);
////				
////				/** 割込みON */
////				MDM_SetIO(POS_RDBIE,ON);
////				MDM_SetIO(POS_NSIE,ON);
////			}
////		}
//#endif
//		break;
//	case MODE_RX_G3: /* Added by H.Kubo 1998/01/30 */
//		mdm_stat = inp(MDM_REG_0A_PORT);	/**	モデム割り込みステータス読み込み */
//		if (mdm_stat & IO_BIT_OE) { /* 受信オーバーランを起こしていたら */
//			MDM_SetIO(POS_OE, OFF); /* OE bit をリセット。*/
//			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_RX_BUFFER_OVERRUN;/* メンテナンススイッチに通知*/
//		}
//		break;
//	case MODE_RX_ND:
//		mdm_stat = inp(MDM_REG_0A_PORT);	/**	モデム割り込みステータス読み込み */
//		if (mdm_stat & IO_BIT_OE) { /* 受信オーバーランを起こしていたら */
//			MDM_SetIO(POS_OE, OFF); /* OE bit をリセット。*/
//		}
//		break;
//	default:
//		break;
//	}
//	if ((MDM_DmaStart == MDM_DMA_GO) && (inp(MDM_REG_1E_PORT) & IO_BIT_RDBIE)) {
//		MDM_SetIO(POS_RDBIE,OFF);
//		MDM_DmaStart = MDM_DMA_CONTINUE;
//	}
//
//
//	/* Ported from \src\clover\src\INT_MDM.ASM and translated into C by H.Kubo 1997/07/19 */
//	if (rtn != 0 ) {
//		if ( (rtn & MDM_EVT_ATV25_DETECT_BIT) != 0 ) {
//			idet_evt(EVT_MDM_ATV25);
//		}
//		if ( (rtn & MDM_EVT_MDM_PNSUC_BIT) != 0 ) {
//			idet_evt(EVT_MDM_PNSUC);
//		}
//		if ( (rtn & MDM_EVT_TX_FCS_COMPLETE_BIT) != 0 ) {
//			idet_evt(EVT_TX_FCS_COMPLETE);
//		}
//		if ( (rtn & MDM_EVT_RX_FLG_DETECT_BIT) != 0 ) {
//			idet_evt(EVT_RX_FLG_DETECT);
//		}
//		if ( (rtn & MDM_EVT_RX_RDBF_BIT) != 0 ) {
//			idet_evt(EVT_MDM_RX_NEW_DATA);
//		}
//
//#if (0)
//** /* プライマリーチャンネルの終端でループすることが在ります。
//** ** ついては、そのデバッグのために下記ＰＣＯＦＦビットを使ってみます。
//** ** 尚、処理はかなり暫定ですので、対応するには注意が必要です。
//** ** by O.Kimoto 1998/11/28
//** */
//** #if (0)
//** ** /* ＰＣＯＦＦでプライマリーチャンネルのＴｕｒｎＯｆｆを検出するのには、下記では不十分です。
//** ** ** よって、プライマリーチャンネルのＴｕｒｎＯｆｆの検出は－２０Ｐまでと同一処理とします。
//** ** ** By O.Kimoto 1998/11/19
//** ** */
//** ** #if (PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P) /* by H.Kubo 1998/10/30 */
//** ** 		if ( (rtn & MDM_EVT_PCOFF_DETECT_BIT) != 0 ) {
//** ** 			idet_evt(EVT_MDM_TURNOFF);
//** ** 		}
//** ** #endif
//** #endif
//#endif
//	} /* if (rtn != 0) */
//
//	MDM_SetIO(POS_NEWS,OFF);	/** モデム割り込み受け付け */
//
//}
#endif

/*************************************************************************
	module		:[モデムＤＭＡ終了割り込み]
	function	:[
		1.モデムＤＭＡ終了割り込みからコールされます
		2. 現在の処理が送信か受信かを判断し、それぞれの処理へ飛びます。
	]
	return		:[なし]
	common		:[
		ModemBlock
		ModemRxStatus
		MDM_ModemBuffer
		ModemControl
	]
	condition	:[
		#define	MODE_TX_FSK			1
		#define	MODE_TX_ECM			2
		#define MODE_TX_G3			3
		#define MODE_TX_TCF			4
		#define MODE_RX_FSK			5
		#define MODE_RX_ECM			6
		#define MODE_RX_G3			7
		#define MODE_RX_TCF			8
		#define MODE_CL1_RX
	]
	comment		:[
		ＤＭＡ割り込みから呼ばれる
	]
	date		:[1997/09/08]
	author		:[久保博]
*************************************************************************/
void	MDM_ModemDMA_TC_Interrupt(void)
{
	switch (ModemBlock.Mode) {
	case	MODE_TX_TCF:
	case	MODE_TX_G3:
	case	MODE_TX_FSK:
	case 	MODE_TX_ECM:
	/* 送信 */
		MDM_TxDMA_TC_Interrupt();
		break;
	case	MODE_RX_TCF:	/* add 1996/10/18 Y.Murata */
	case	MODE_RX_G3:	/**	Ｇ３受信モード処理	*/
	case	MODE_RX_ECM:
	case	MODE_RX_FSK:
	case	MODE_CL1_RX:	/**	CLASS 1受信モード処理 by O.Kimoto 1997/04/26 */
	/* 受信 */
		MDM_RxDMA_TC_Interrupt();
		break;
	}
}



/*************************************************************************
	module		:[モデムＤＭＡ終了割り込み]
	function	:[
		1.モデムＤＭＡ終了割り込みからコールされます
	]
	return		:[なし]
	common		:[
		ModemBlock
		ModemRxStatus
		MDM_ModemBuffer
		ModemControl
	]
	condition	:[
		#define	MODE_TX_FSK			1
		#define	MODE_TX_ECM			2
		#define MODE_TX_G3			3
		#define MODE_TX_TCF			4
	]
	comment		:[
		ＤＭＡ割り込みから呼ばれる
	]
	date		:[1994/04/13]
	author		:[曽根岡拓]
*************************************************************************/
void	MDM_TxDMA_TC_Interrupt(void)
{
	UWORD	rtn;

	rtn = 0;

	switch (ModemBlock.Mode) {
	case	MODE_TX_TCF:
	/* case	MODE_TX_G3: */ /* デバッグのため別にします */
		if (!(ModemControl.Status & STAT_ACT)) {
			break;
		}
		ModemControl.UsedCount--;	/**	モデムバッファ使用本数を１マイナスする	*/
		NextMdmBufReadPointSetExtRom();
		if (ModemControl.UsedCount != 0) {	/**	次登録ブロック有り	*/
			DMA_RequestMask(DMA_CH_TX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
			DMA_RestartDMAU(DMA_CH_TX, DMA_MEMORY_TO_IO, ModemControl.BufferControl[ModemControl.ReadPoint].DataCount,(UDWORD)ModemControl.BufferControl[ModemControl.ReadPoint].TopAddress);
		}
		else {	/** 次登録ブロック無し	*/
			ModemControl.Status &= ~STAT_ACT;	/**	モデムステータスアイドル状態設定	*/
			if (ModemControl.Status & STAT_EMPTYPT) {	/**	全ブロック送出完了処理	*/
				DMA_RequestMask(DMA_CH_TX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
				TxCompleteEventFlag = 1;
				rtn = EVT_TX_COMPLETE;
			}
			else {
				DebugZeroCnt++;	/*	ここに入って来たら符号化が間に合っていません	*/
			}
		}
		break;
	case	MODE_TX_G3:
		if (!(ModemControl.Status & STAT_ACT)) {
			break;
		}
		ModemControl.UsedCount--;	/**	モデムバッファ使用本数を１マイナスする	*/
		NextMdmBufReadPointSetExtRom();
		if (ModemControl.UsedCount != 0) {	/**	次登録ブロック有り	*/
			DMA_RequestMask(DMA_CH_TX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
			DMA_RestartDMAU(DMA_CH_TX, DMA_MEMORY_TO_IO, ModemControl.BufferControl[ModemControl.ReadPoint].DataCount,(UDWORD)ModemControl.BufferControl[ModemControl.ReadPoint].TopAddress);
		}
		else {	/** 次登録ブロック無し	*/
			ModemControl.Status &= ~STAT_ACT;	/**	モデムステータスアイドル状態設定	*/
			if (ModemControl.Status & STAT_EMPTYPT) {	/**	全ブロック送出完了処理	*/
				DMA_RequestMask(DMA_CH_TX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
				TxCompleteEventFlag = 1;
				rtn = EVT_TX_COMPLETE;
			}
			else {
				DebugZeroCnt++;	/*	ここに入って来たら符号化が間に合っていません	*/
			}
		}
		break;
	case	MODE_TX_FSK:
	case 	MODE_TX_ECM:
		if (MDM_LastData == ON) {
			MDM_LastData = OFF;
#if defined (KEISATSU) /* 警察FAX 05/07/21 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && (ModemBlock.Mode == MODE_TX_ECM)) { /* スクランブル通信の場合 */
				S1_HDLC_TxLast(1);
			}
			else {
				MDM_SetIO(POS_TEOF,ON);	/** モデムにＴＥＯＦをセットする。 **/
			}
#else
			MDM_SetIO(POS_TEOF,ON);	/** モデムにＴＥＯＦをセットする。 **/
#endif
			/** 送信すべき最後の１バイトをＤＭＡ転送する。 **/

#if  (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* ここの処理に時間がかかりすぎているので変えてみます（試験中）。added by H.Kubo 1998/11/19 *//* 2002/09/18 By M.Maeda */
			SelectDreqDirection(TX_DMA); /* I/O ポートでDREQ切り替え */
			DMA_SetDMA_Counter(DMA_CH_TX,(UWORD)(1));
			DMA_Continue(DMA_CH_TX); 
#else
			/* 次の転送元アドレスをセットし直す。 */
			DMA_SetDMA_Address(DMA_CH_TX, DMA_MEMORY_TO_IO, DMA_CheckDMA_Address(DMA_CH_TX, DMA_MEMORY_TO_IO));

			/* DMA_SetDMA_BaseCurrentCounter(MASTER_DMAU, DMA_CH_TX,(UWORD)(1-1)); */
			DMA_SetDMA_Counter(DMA_CH_TX,(UWORD)(1)); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */

			/* Added by H.Kubo 1997/10/08
			**モデム用 DREQ 一本になったため、 I/O ポートで DREQ の送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(TX_DMA); /* I/O ポートでDREQ切り替え */
#else
			SetModemDMA_DirectionTx(); /* I/O ポートでDREQ切り替え */
#endif
			DMA_RequestEnable(DMA_CH_TX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#endif
		}
		break;
	case MODE_TX_ND:
		if (!(ModemControl.Status & STAT_ACT)) {
			break;
		}
		ModemControl.UsedCount--;	/**	モデムバッファ使用本数を１マイナスする	*/
		NextMdmBufReadPointSetExtRom();
		if (ModemControl.UsedCount != 0) {	/**	次登録ブロック有り	*/
			DMA_RequestMask(DMA_CH_TX);
			DMA_RestartDMAU(DMA_CH_TX, DMA_MEMORY_TO_IO, ModemControl.BufferControl[ModemControl.ReadPoint].DataCount,(UDWORD)ModemControl.BufferControl[ModemControl.ReadPoint].TopAddress);
		}
		else {	/** 次登録ブロック無し	*/
			ModemControl.Status &= ~STAT_ACT;	/**	モデムステータスアイドル状態設定	*/
			if (ModemControl.Status & STAT_EMPTYPT) {	/**	全ブロック送出完了処理	*/
				DMA_RequestMask(DMA_CH_TX);
				TxCompleteEventFlag = 1;
				rtn = EVT_TX_COMPLETE;
			}
			else {
				DebugZeroCnt++;	/*	ここに入って来たら符号化が間に合っていません	*/
			}
		}
		break;
	default:
		break;
	}

	/* Ported from \src\clover\src\int_dma0.asm and translated into C by H.Kubo 1997/07/19 */
	/* ... from tc1: */
	/* DMA0_TC1Flag = 1; */ /* イベントを捕まえてもらうときの空振り防止のフラグ */
	IsMemoryToModemXferDone = TRUE;  /* イベントを捕まえてもらうときの空振り防止のフラグ */
	idet_evt(EVT_DMA_MDMBUF_MDM); /* DMA 転送終了のイベントを投げる。 */

	/* Adeded by H.Kubo 1997/10/15. See int_dma0.asm of CLOVER.*/
	if (rtn == EVT_TX_COMPLETE) {
		idet_evt(EVT_TX_COMPLETE);
	}
}


/*************************************************************************
	module		:[モデムＤＭＡ終了割り込み]
	function	:[
		1.モデムＤＭＡ終了割り込みからコールされます
		2.１４４００ｂｐｓで受信時は、５５５μｓで次のＤＭＡを起動しなければ
		, データ取りこぼすため割り込み内で処理します
	]
	return		:[なし]
	common		:[
		ModemBlock
		ModemRxStatus
		MDM_ModemBuffer
		ModemControl
	]
	condition	:[
		#define MODE_RX_FSK			5
		#define MODE_RX_ECM			6
		#define MODE_RX_G3			7
		#define MODE_RX_TCF			8
	]
	comment		:[
		ＤＭＡ割り込みから呼ばれる
	]
	date		:[1994/04/13]
	author		:[曽根岡拓]
*************************************************************************/
void		MDM_RxDMA_TC_Interrupt(void)
{
	switch (ModemBlock.Mode) {
	case	MODE_RX_TCF:	/* add 1996/10/18 Y.Murata */
	case	MODE_RX_G3:	/**	Ｇ３受信モード処理	*/
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* モデムバッファのデータ長が必要 by H.Kubo 1999/03/23 *//* By M.Maeda 2002/10/24 */
		MDM_RxSize[ModemControl.WritePoint] = MODEM_DMA_SIZE;
#endif
#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
		/** DMA TC 割り込み内なので、 DMA は指定転送回数だけ転送している。 */
		MDM_RxSize[ModemControl.WritePoint] = MDM_ModemDmaSize;
#endif
		if (CommunicateType == RX_G3_MEM) {
			ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	受信上位通知処理	*/
			NextMdmBufWritePointSetExtRom();
			ModemControl.UsedCount++;
			DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */

			/* Added by H.Kubo 1997/10/09
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA); /* I/O ポートでDREQ切り替え */
#else
			SetModemDMA_DirectionRx();
#endif

			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
			/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), MODEM_DMA_SIZE-1);*/	/** 256 Bytes **/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  MDM_ModemDmaSize,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
#else
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  MODEM_DMA_SIZE,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
#endif
		}
		else {
			ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	受信上位通知処理	*/
			NextMdmBufWritePointSetExtRom();
			ModemControl.UsedCount++;
			DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */

			/* Added by H.Kubo 1997/10/09
			**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
			*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
			SelectDreqDirection(RX_DMA);
#else
			SetModemDMA_DirectionRx();
#endif
			/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
			/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), MODEM_DMA_SIZE-1);*/	/** 256 Bytes **/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, MDM_ModemDmaSize,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
#else
			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, MODEM_DMA_SIZE,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
#endif
		}
		break;
	case	MODE_RX_ECM:
#if 0
//#if defined (KEISATSU) /* 警察FAX 05/09/01 石橋正和 */
//		if (FCM_S1_Scramble == TRUE) { /* スクランブル通信の場合 */
//			/* ここに来るまでに次のフレームの先頭データを受信したときの処理を追加。 Changed by H.Kubo 1999/01/26 */
//			/* DMA(DTC) はここで止めないといけない。カウンタを読んでからマスクするまでの間に次の DREQ が来たら
//			** 終了割り込みがかかることがある。
//			** by H.Kubo 1999/01/26 */
//			DMA_RequestMask(DMA_CH_RX);
//			GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
//			ModemControl.UsedCount++;
//			ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
//				/* フレーム最後のフラグを受信してからここに来るまでの間に次のフレームの先頭を受信していたら、
//				** 次のフレームの先頭は次のモデムバッファにコピーして残りのデータの受信を始めます。
//				** そうでなければ、次のフレームは普通に次のモデムバッファの先頭から受信し始めます。
//				** by H.Kubo 1999/01/26
//				*/
//#if 0
////			if ((MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1))
////				&& (MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] == 0xff)) {
////				/* 次のアドレスフィールドのデータが末尾にある場合 */
////				MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH] = 0x0;
////				MDM_RxSize[ModemControl.WritePoint] -= 1; /* 次のモデムバッファに移した分だけ引き算します。 */
////				NextMdmBufWritePointSetExtRom();
////				MDM_ModemBuffer[ModemControl.WritePoint][0] = 0xff;
////				SelectDreqDirection(RX_DMA);
////				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
////			}
////			else {
//#endif
//				NextMdmBufWritePointSetExtRom();
//				SelectDreqDirection(RX_DMA);
//				/* DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]); */
//				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize + 4), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
//#if 0
////			}
//#endif
//			MDM_DmaStart = MDM_DMA_GO;
//			break;
//		}
//#endif
#endif
		/* 基本的にはありえませんが、何らかの要因でモデムバッファサイズより多く受信して、
		 * 結果的にＤＭＡがストップした場合、モデムがアンダーランを起こすので、
		 * とりあえず、ＤＭＡを起動しておきます。By O.K Jan.26,1996
		 */
		DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
		/*
		** フレーム間フラグが短くてモデムがフラグを取り逃がしたときの処理
		** by H.Kubo 1999/01/22
		*/
		GetRxSize(ModemControl.WritePoint);	/**	フレームサイズ取得	*/
		if (MDM_RxSize[ModemControl.WritePoint] == (FcomEcmSize + MODEM_FRAMING_CODE_LENGTH + 1)) {
			UBYTE tail_data;
			tail_data = MDM_ModemBuffer[ModemControl.WritePoint][FcomEcmSize+MODEM_FRAMING_CODE_LENGTH];
			if ((tail_data == 0xff) || (tail_data & 0xDF == 0x03)) { /* 次のフレームの先頭のデータなら */
				ModemControl.UsedCount++;
				MDM_RxSize[ModemControl.WritePoint] -= 1; /* 次のフレームの分は引いておく */
				ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	フレーム受信上位通知処理	*/
				MDM_EcmRxFcsCheckRequest |= (1 << ModemControl.WritePoint);
				NextMdmBufWritePointSetExtRom();
				MDM_ModemBuffer[ModemControl.WritePoint][0] = tail_data; /* 次のフレームのデータを次のバッファへ */
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
				SelectDreqDirection(RX_DMA);
#else
				SetModemDMA_DirectionRx();
#endif
				DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][1]);
				MDM_EcmRxFcsCheckRequest |= (1 << ModemControl.WritePoint);
				break;
			}
		}

		/* Added by H.Kubo 1997/10/09
		**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
		*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
		SelectDreqDirection(RX_DMA);
#else
		SetModemDMA_DirectionRx();
#endif

		/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
		/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1)-1); */
		DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  (FcomEcmSize+MODEM_FRAMING_CODE_LENGTH+1), (UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);
		break;
	case	MODE_RX_FSK:
		break;
	case	MODE_CL1_RX:	/**	CLASS 1受信モード処理 by O.Kimoto 1997/04/26 */
#if (PRO_CLASS1 == ENABLE) /* Added by H.Kubo 1998/03/04 */
		/** DMA TC 割り込み内なので、 DMA は指定転送回数だけ転送している。 */
		MDM_RxSize[ModemControl.WritePoint] = MDM_ModemDmaSize;
#endif
		ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	受信上位通知処理	*/
		NextMdmBufWritePointSetExtRom();
		ModemControl.UsedCount++;

		/* Added by H.Kubo 1997/10/09
		**モデム用 DREQ 一本になったため、 I/O ポートで送受信切り替え。
		*/
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
		SelectDreqDirection(RX_DMA);
#else
		SetModemDMA_DirectionRx();
#endif

#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/09 */
		/* CLASS1 2400BPS ECM 受信対策。 初回と２回目以降で DMA のカウンタの値を変えます。*/
		switch (ModemBlock.Speed) {
		case SPEED_2400:
			MDM_ModemDmaSize = (MODEM_DMA_SIZE / 2);  /* モデムバッファは 1 本あたり 64Byte とします。*/
			break;
		case SPEED_4800:
			MDM_ModemDmaSize = (MODEM_DMA_SIZE / 2); /* モデムバッファは 1 本あたり 128Byte とします。*/
			break;
		case SPEED_7200:
			MDM_ModemDmaSize = MODEM_BUFFER_LENGTH; /* モデムバッファは 1 本あたり 128Byte とします。*/
			break;
		case SPEED_9600:
			MDM_ModemDmaSize = 192; /* モデムバッファは 1 本あたり 192Byte とします。*/
			break;
		case SPEED_12000:
			MDM_ModemDmaSize = 192; /* モデムバッファは 1 本あたり 192Byte とします。*/
			break;
		default:
			MDM_ModemDmaSize = MODEM_BUFFER_LENGTH; /* モデムバッファは 1 本あたり (256 + 8) Byte とします。*/
			break;
		}
#endif

		DMA_RequestMask(DMA_CH_RX); /* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
		/* Following line is modified by H. Kubo for POPLAR_H 1997/06/24 */
		/* DMA_RestartDMAU(MASTER_DMAU, DMA_CH_RX, DMA_AddressSet((UBYTE  *)&MDM_ModemBuffer[ModemControl.WritePoint][0]), MODEM_DMA_SIZE-1);*/	/** 256 Bytes **/
#if (PRO_CLASS1 == ENABLE) /* Changed by H.Kubo 1998/03/04 */
		DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, MDM_ModemDmaSize,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
#else
		DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, MODEM_DMA_SIZE,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
#endif
		break;
	case MODE_RX_ND:
		MDM_RxSize[ModemControl.WritePoint] = ND_MODEM_DMA_SIZE;
		ModemRxStatus &= ~(1<<ModemControl.WritePoint);	/**	受信上位通知処理	*/
		NextMdmBufWritePointSetExtRom();
		ModemControl.UsedCount++;
		DMA_RequestMask(DMA_CH_RX);/* 1st argument MASTER_DMAU is deleted by H. Kubo for POPLAR_H 1997/06/24 */
#if defined (HINOKI2) || (defined(POPLAR_H) && defined(JP0)) || (defined(SAKAKI) && defined(JP0)) || defined(SATSUKI2) || defined(STOCKHM2)
		SelectDreqDirection(RX_DMA);
#else
		SetModemDMA_DirectionRx();
#endif
		DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY,  ND_MODEM_DMA_SIZE,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][0]);	/** 256 Bytes **/
		break;
	default:
		break;
	}

	/* Ported from \src\clover\src\int_dma0.asm and translated into C by H.Kubo 1997/07/19 */
	/* ... from tc0: */
	/* DMA0_TC0Flag = 1; */  /* イベントを捕まえてもらうときの空振り防止のフラグ */
	IsModemToMemoryXferDone = TRUE; /* イベントを捕まえてもらうときの空振り防止のフラグ */
	idet_evt(EVT_DMA_MDM_MDMBUF); /* DMA 転送終了のイベントを投げる。 */

}


/*************************************************************************
	module		:[モデム割り込み監視タスク]
	function	:[
		1.
	]
	return		:[なし]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_ModemInterruptTask(void){}]
	date		:[1993/12/10]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_ModemInterruptTask(void)
{
	UBYTE debug;

	/*------------------------------------------*/
	/*	イベント待ち処理						*/
	/*	EVT_TX_FCS_COMPLETE:モデム割り込みより	*/
	/*------------------------------------------*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	if (ModemInterruptFlag == 0) {	/**	モデム割り込み未発生の時	*/
		wai_evt(EVT_TX_FCS_COMPLETE);	/**	ＦＣＳ送出完了イベント待ち	*/
	}
	else {
		debug++;
	}
	ModemInterruptFlag = 0;	/**	モデム割り込み発生フラグ初期化	*/
	CMN_EnableInterrupt();	/**	割り込み許可	*/
	/*------------------------------------------------------*/
	/**	フレーム送出完了メッセージ送信						*/
	/*	MSG_TXFRAME_END	:	ＦＳＫ送信フレーム監視タスクへ	*/
	/*					:	ＥＣＭ送信フレーム監視タスクへ	*/
	/*------------------------------------------------------*/

	TxFrameEndMessage.Message = MSG_TXFRAME_END;
	snd_msg(mbxno.MDM_TaskSub, &TxFrameEndMessage);
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[モデムＤＭＡ転送終了監視タスク]
	function	:[
		1.ＤＭＡ終了割り込みより、ＤＭＡ終了イベント待ち
		2.メッセージ送信処理
	]
	return		:[
		なし
	]
	common		:[
		ModemMessage
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_ModemDMA_TC_DetectTask(void){}]
	date		:[1993/12/13]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
#if 0 /* Commented out by H.Kubo 1997/08/13, for not used in POPLAR_H. */
/** 以下のタスクは未使用ですが、Ｕｎｄｅｆｉｎｅが出るので！ By O.K Feb.09,1996 **/
** void  MDM_TxDMA_TC_DetectTask(void)
** {
** 	/*--------------------------------------------------*/
** 	/*	イベント待ち処理								*/
** 	/*--------------------------------------------------*/
** 	CMN_DisableInterrupt();	/**	割り込み禁止	*/
** 	/** 受信方向ＤＭＡ終了待ち **/
** #if 0
** 	if (DMA0_TC1Flag == 0) {
** 		/* wai_evt(EVT_DMA0_TC1); */	/**	Ｖ５３ＤＭＡスレーブ１　ＴＣ１のイベント待ち	*/
** 	}
** 	DMA0_TC1Flag = 0;
** #else
** 	if (IsModemToMemoryXferDone == 0) {
** 		wai_evt(EVT_DMA_MDM_MDMBUF); /* 受信／送信の終了イベント待ち by H.Kubo 1997/0/04 */
** 	}
** 	IsModemToMemoryXferDone = 0;
** #endif
** 	CMN_EnableInterrupt();	/**	割り込み許可	*/
** 	switch (ModemBlock.Mode) {	/**	交信モード	*/
** 	/*--------------------------*/
** 	/**	ＦＳＫ受信モード処理	*/
** 	/*--------------------------*/
** 	case MODE_TX_FSK:
** 	case MODE_TX_ECM:
** 	case MODE_TX_G3:
** 	case MODE_TX_TCF:
** 	default:
** 		break;
** 	}
** 	wai_tsk(0xffff);
** }
#endif /* 0 */

/*************************************************************************
	module		:[モデムＤＭＡ転送終了監視タスク]
	function	:[
		1.ＤＭＡ終了割り込みより、ＤＭＡ終了イベント待ち
		2.メッセージ送信処理
	]
	return		:[
		なし
	]
	common		:[
		ModemMessage
	]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_ModemRxChannelDMA_TC_DetectTask(void){}]
	date		:[1993/12/13]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_RxDMA_TC_DetectTask(void)
{
	/*
	*	イベント待ち処理
	*/
	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	/** 受信方向ＤＭＡ終了待ち **/
	if (IsModemToMemoryXferDone == FALSE) { /* Changed by H.Kubo 1997/07/18 */
		wai_evt(EVT_DMA_MDM_MDMBUF); /* 受信／送信の終了イベント待ち by H.Kubo 1997/0/04 */
	}
	IsModemToMemoryXferDone  = FALSE; /* Since modem to memory transfer event is catched, reset the flag. */
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	switch (ModemBlock.Mode) {	/**	交信モード	*/

	/*
	*	ＦＳＫ受信モード処理
	*/
	case	MODE_RX_FSK:
		/*
		*	メッセージ送信処理
		* 1.MSG_DMA_STOP:	フレーム受信コントロールタスクへ
		*/
		ModemMessage.Message = MSG_DMA_STOP;
		snd_msg(mbxno.MDM_TaskSub, &ModemMessage);
		break;
	case	MODE_RX_ECM:
		break;
	case	MODE_RX_G3:
#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* by H.Kubo 1999/03/20 *//* 2002/09/18 By M.Maeda */
		/* SAKAKI プリンタ受信で受信画が壊れる対策。記録紙の準備ができる前に
		** モデムバッファ溢れが起こるので、モデムバッファの空きが少なくなったら
		** モデムバッファに溜まった受信データを ECM バッファに待避します。
		** ここではモデムバッファ一本分の受信があったことを G3_Rx() に通知します。
		** プリンタ受信のない機種では必要ないでしょう。また、 POPLAR_H の
		**  ECM バッファの使い方とは共存できないので注意してください。
		** by H.Kubo 1999/03/20
		*/
		ModemMessage.Message = MSG_DMA_STOP;
		snd_msg(mbxno.MDM_RxEcmControlTask, &ModemMessage);
		break;
#endif
	case	MODE_RX_TCF:
	default:
		break;
	}
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[通信コーデック　エンコードＤＭＡ終了割り込み監視タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/01/12]
	author		:[曽根岡拓]
*************************************************************************/
#if defined (SAKAKI)	/* 1998/11/19 *//* 2002/09/18 By M.Maeda */
UBYTE	ECM_WritePageCounter = 0;
#endif
void 	MDM_EncodeDMA_TC_DetectTask(void)
{
	struct DMA_Data_t CodecTxDMA;
	MESSAGE_t	*MDM_Msg;
	UDWORD	ecd_data_max;
	UWORD	dma_set_cnt;
	UBYTE	debug_err;
	UBYTE	loop_flg;

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*  ECM_BUFFER_OVER */
	if ((CommunicateType == TX_G3_SCAN) || (CommunicateType == TX_ECM_SCAN)) {
		MDM_EncodeDMA_TC_Detect();
		wai_tsk(0xFFFF);
	}
#endif

	/*----------------------------------------------*/
	/*	エンコードＤＭＡ開始（２５６ｂｙｔｅ単位）	*/
	/*	ＣＯＤＥＣ－＞ＥＣＭバッファ				*/
	/*----------------------------------------------*/
	do {	/**	エンコード開始メッセージ待ち	*/
		rcv_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &MDM_Msg);
	} while (!(MDM_Msg->Message == MSG_ENCODE_DMA_START));

	/*----------------------------------------------*/
	/*	ＴＴＩのエンコードデータ量をセットします	*/
	/*----------------------------------------------*/
	EncodeDataCount = EcmBufferBaseWritePoint - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
	if (EncodeDataCount == 0) {
		DebugDMA_EncodeStopCounter = 0;
	}
	else {
		DebugDMA_EncodeStopCounter = (UWORD)(EncodeDataCount/CODEC_DMA_SIZE);
	}

	/*------------------------------------------*/
	/*	ＥＣＭバッファのＭＡＸをセットします	*/
	/*------------------------------------------*/
	ecd_data_max = (UDWORD)0x10000;

	/*----------------------------------------------*/
	/*	エンコードＤＭＡのカウント数の設定（２５６ｂｙｔｅ単位）*/
	/*	エンコードＤＭＡのセットアップ、起動	*/
	/*----------------------------------------------*/
#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/10/13 By H.Hirao */ /* ported by T.Takagi 2001/12/18 */
	/* スキャナ送信は通信コーデックを使用 */
	IsCOMCDC_ToMemoryXferDone = NO;
	CodecTxDMA.Channel = DMA_CH_ENC;
#else
	switch (CommunicateType) {
	case	TX_G3_SCAN:
	case	TX_ECM_SCAN:
		IsSCNCDC_ToMemoryXferDone = NO;		/* Changed by H.Kubo 1997/07/18 */
		CodecTxDMA.Channel = DMA_SCNCDC_DRAM_CH; /* Modified by H.Kubo 1997/07/11 */
		break;
	case	TX_G3_MEM:
	case	TX_ECM_MEM:
	case TX_G3_RELAYED_TX_REPORT:
	case TX_ECM_RELAYED_TX_REPORT:
		IsCOMCDC_ToMemoryXferDone = NO; /* Changed by H.Kubo 1997/07/18 */
		CodecTxDMA.Channel = DMA_CH_ENC;
		break;
	default:
		break;
	}
#endif
	CodecTxDMA.DstAddress	= (UDWORD) EcmBufferBaseWritePoint; /* Modified by H. Kubo 1997/06/24 */
	CodecTxDMA.SrcAddress	= CodecTxDMA.DstAddress; /* SrcAddress will be referred in DMA_SetupDMAU() */
	dma_set_cnt				= GetCount((UDWORD) (ecd_data_max - EncodeDataCount), CODEC_DMA_SIZE);

	/* 2002/09/18 By M.Maeda */
	/*---------------------------------------------------------------------
	** IDP(DICEP)を使用してスキャナ送信する場合(SAKAKI用)
	** 1998/08/11 H.Yoshikawa
	*/
#if (PRO_SCN_CODEC_TYPE == IDP301)	/* 1998/08/11 H.Yoshikwa */
	switch (CommunicateType) {
	case	TX_G3_SCAN:
	case	TX_ECM_SCAN:
		CodecTxDMA.Counter		= dma_set_cnt;  /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
		CodecTxDMA.Unit			= DMA_BYTE_TRANSFER;
		break;
	case	TX_G3_MEM:
	case	TX_ECM_MEM:
	default:
		CodecTxDMA.Counter		= dma_set_cnt / 2;  /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
		CodecTxDMA.Unit			= DMA_WORD_TRANSFER;
		break;
	}
	ECM_WritePageCounter = 0;	/* 1998/11/19 */
#else
	CodecTxDMA.Counter		= dma_set_cnt / 2;  /* Modified for DMA routine of Atlanta by H. Kubo 1997/06/25 */
	CodecTxDMA.Unit			= DMA_WORD_TRANSFER;
#endif

	CodecTxDMA.Direction	= DMA_IO_TO_MEMORY;
	DMA_SetupDMAU(&CodecTxDMA);
	DMA_RequestEnable(CodecTxDMA.Channel); /* Modified by H. Kubo for POPLAR_H 1997/06/24 */

	loop_flg = 1;
	while (loop_flg) {
		/*------------------------------------------*/
		/*	エンコードＤＭＡ終了割り込み待ち処理	*/
		/*------------------------------------------*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
#if (PRO_SCN_CODEC_TYPE == SOFTWARE) /* 1998/10/13 By H.Hirao */ /* ported for HINOKI2 2001/12/17 T.Takagi */
		/* スキャナ送信は通信コーデックを使用 */
		if (IsCOMCDC_ToMemoryXferDone == NO) {
			wai_evt(EVT_DMA_COMCDC_DRAM);
		}
		IsCOMCDC_ToMemoryXferDone = NO; /* Changed by H.Kubo 1997/07/18 */
#else
		switch (CommunicateType) {
		case	TX_G3_SCAN:
		case	TX_ECM_SCAN:
			if (IsSCNCDC_ToMemoryXferDone == NO) { /* Chaned by H.Kubo 1997/07/18 */
				/* wai_evt(EVT_DMA0_TC2); */	/*	Ｖ５３内臓ＤＭＡＵ　ＴＣ０	*/
				/* wai_evt(EVT_DMA_COMCDC_DRAM); */	/*	通信コーデック -> DRAM commented out by H.Kubo 1997/07/11 */
				wai_evt(EVT_DMA_SCNCDC_DRAM);  /* ported from ORANGE by H.Kubo 1997/07/11 */
			}
			IsSCNCDC_ToMemoryXferDone = NO;
			break;
		case	TX_G3_MEM:
		case	TX_ECM_MEM:
		case 	TX_G3_RELAYED_TX_REPORT:
		case 	TX_ECM_RELAYED_TX_REPORT:
		default:
			if (IsCOMCDC_ToMemoryXferDone == NO) { /* Changed by H.Kubo 1997/07/18 */
				/* wai_evt(EVT_DMA0_TC2);	*/ /*	Ｖ５３内臓ＤＭＡＵ　ＴＣ２	*/
				wai_evt(EVT_DMA_COMCDC_DRAM);	/*	通信コーデック -> DRAM by H.Kubo 1997/07/04	*/
			}
			IsCOMCDC_ToMemoryXferDone = NO; /* Changed by H.Kubo 1997/07/18 */
			break;
		}
#endif
		CMN_EnableInterrupt();	/**	割り込み許可	*/
		/*--------------------------*/
		/*	エンコードデータ量更新	*/
		/*--------------------------*/
		EncodeDataCount += (UDWORD) dma_set_cnt;
		/*------------------------------------------------------*/
		/*	送信開始イベント設定（最初の１ブロックだけ有効）	*/
		/*------------------------------------------------------*/
		TxStartFlag = 1;
		/*------------------------------*/
		/*	エンコードＤＭＡの次起動	*/
		/*------------------------------*/
		if (EncodeDataCount < ecd_data_max) {	/**	ＥＣＭバッファが空いている時	*/
			if ((MDM_TxStopSwFlag == 1) && (EncodeDataCount < 0xF000)		/* 通信ストップ且つＥＣＭバッファに最大１ライン符号化数（４Ｋ）以上の空きがある時 */
			 && (CommunicateType != TX_ECM_SCAN) && (CommunicateType != TX_G3_SCAN)) {	/* メモリ送信の場合 条件追加 96/07/05 By T.Yamaguchi */
				/* DMA_RestartDMAU(CodecTxDMA.Item, CodecTxDMA.Channel, (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount), MAX_1LINE_ENCODE_DATA);*/ /* 96/07/02 By T.Yamaguchi */
				DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction,  MAX_1LINE_ENCODE_DATA,
								(UDWORD) (ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount)
								); /* 96/07/02 By T.Yamaguchi */
				switch (CommunicateType) {
				case	TX_G3_MEM:	/**	メモリＧ３送信	*/
				case	TX_ECM_MEM:	/**	メモリＥＣＭ送信	*/
				case	TX_G3_CVR: /* added by H.Kubo 1998/01/19 */
				case	TX_G3_RCR: /* added by H.Kubo 1998/01/19 */
				case	TX_ECM_CVR: /* added by H.Kubo 1998/01/19 */
				case	TX_ECM_RCR: /* added by H.Kubo 1998/01/19 */
				case	TX_G3_RELAYED_TX_REPORT:
				case	TX_ECM_RELAYED_TX_REPORT:
					AbortCodecCommand(COMMUNICATION_CODEC); /* コーデックアボートサブルーチンコール	*/ /* Ported from ORANGE by H.Kubo 1997/07/04 */
					break;
				case	TX_G3_SCAN:	/**	スキャナＧ３送信	*/
				case	TX_ECM_SCAN:	/**	スキャナＥＣＭ送信	*/
				default:
/*				スキャナ送信の場合はコーデックでＥＮＣＯＤＥした後に抜ける処理に変更 96/07/05 By T.Yamaguchi */
/*					AbortCodecCommand();		/@ コーデックアボートサブルーチンコール	del By T.Yamaguchi 96/07/01 */
					break;
				}
				while (CodecPageStatus != CDC_STOPPED) {
					wai_tsk(10/10);
				}
				/* ｺｰﾃﾞｯｸの方でスキャナを止める様にした 96/07/02 By T.Yamaguchi */
				loop_flg = 0;
			}
			else {
				dma_set_cnt = GetCount((UDWORD)(ecd_data_max - EncodeDataCount), CODEC_DMA_SIZE);
				DMA_RequestMask(CodecTxDMA.Channel);
				/*---------------------------------------------------------------------
				** IDP(DICEP)を使用してスキャナ送信する場合(SAKAKI用)
				** 1998/08/11 H.Yoshikawa
				*/
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* 1998/08/11 H.Yoshikwa *//* 2002/09/18 By M.Maeda */
				if ((CommunicateType == TX_ECM_SCAN) ||
				    (CommunicateType == TX_G3_SCAN)) { /* The condition is added by H.Kubo 1998/08/19  */
					DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt),
										(UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount)
									);
				}
				else {
					DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt/2),
									(UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount)
									);
				}
  #else
				DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt/2),
									(UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount)
								);
  #endif
			}
		}
		/*--------------------------------------*/
		/*	エンコードＤＭＡ起動待ち処理	*/
		/*--------------------------------------*/
		else if (EncodeDataCount == ecd_data_max) {	/**	ＥＣＭバッファがＦＵＬＬの時	*/
			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			if (CodecPageStatus != CDC_CONTINUE) {
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				loop_flg = 0;
			}
			else {
				CodecPageStatus = CDC_BLOCK_END;	/**	コーデックステータスをブロックエンドにセット	*/
#if 0
//#if defined (HIIRAGI) /* KAKI の対策を持ってきました。スキャナ側にページメモリを持つ機種では不要でしょう。 by H.Kubo 1999/08/28 */
//				/* Ｇ３スキャナー送信中に送信画像が欠ける不具合対策。	S.Fukui Aug.14,1999
//				** DACKが発生せず、DREQが立ち放しになり、約２２ライン画像が欠けている為、救済策としてここで読取りを一旦停止します。
//				*/
//				if ((CommunicateType == TX_G3_SCAN) || (CommunicateType == TX_ECM_SCAN)) {
//					SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
//					SCN_StopMotor(); /** モーター停止 */		
//				}
//#endif
#endif
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				do {	/**	エンコード再起動メッセージ待ち	*/
					rcv_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &MDM_Msg);
				} while (!(MDM_Msg->Message == MSG_ENCODE_DMA_START));

				CodecPageStatus = CDC_CONTINUE;	/**	コーデックステータスをコンティニューにセット	*/
				EncodeDataCount = 0;	/**	エンコードデータ量初期化	*/
				TxStartFlag = 0;
				switch (CommunicateType) {
				case	TX_G3_SCAN:
				case	TX_ECM_SCAN:
#if (PRO_SCN_CODEC_TYPE == MN86063) || (PRO_SCN_CODEC_TYPE == MN86064)	/* 1998/08/11 H.Yoshikawa */ /* ported by T.Takagi 2001/12/18 */
					/* Ported from ORANGE\src\mdm_int.c by H.Kubo 1997/07/11 */
					/* 位相ずれ上から移動してきた 1997/02/08  By T.Yamaguchi */
 #if (1) /* この処理がF-160のシステムで必要か不明。念の為従来通り入れて置きますが留意しときましょう。S.Fukui Feb.26,1999 */
					SCN_SetScanDMA(SCN_DISABLE);				/** スキャン用ＤＭＡ禁止 */
					SCN_SetScanDMA(SCN_ENABLE);					/** スキャン用ゲートアレイからコーデックへのＤＲＥＱ許可 Apr.24,1994 */
 #endif
					if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
					}
					/* Bellow is ported from ORANGE by H.Kubo 1997/11/13 */
					/*-----------------------------------------------------
					** ６４ＫＢ送出完了後、次の６４ＫＢ分のデータをコーデックから取り出しを開始する時に、
					** エンコードタスクがすでに、エンコードを終了し EVT_DMA_SCNCDC_DRAM のイベント待ちとなっている場合には、
					** 読み取りモータの再起動をここで実施するようにする。
					** 1997/05/09
					** H.Yoshikawa
					*/
					if (CDC_WaitingCDC0_DMA0_END) {
						SCN_RestartMotor();
					}
					/* ここまで 1997/02/08	By T.Yamaguchi */
#endif
					IsSCNCDC_ToMemoryXferDone = NO;  /* Changed by H.Kubo 1997/07/18 */
					break;
				case	TX_G3_MEM:
				case	TX_ECM_MEM:
				case	TX_G3_CVR: /* added by H.Kubo 1998/01/19 */
				case	TX_G3_RCR: /* added by H.Kubo 1998/01/19 */
				case	TX_ECM_CVR: /* added by H.Kubo 1998/01/19 */
				case	TX_ECM_RCR: /* added by H.Kubo 1998/01/19 */
				case	TX_G3_RELAYED_TX_REPORT:
				case	TX_ECM_RELAYED_TX_REPORT:
					IsCOMCDC_ToMemoryXferDone = NO;
					break;
				default:
					break;
				}
				dma_set_cnt = GetCount((UDWORD)(ecd_data_max - EncodeDataCount), CODEC_DMA_SIZE);
				DMA_RequestMask(CodecTxDMA.Channel);
				/* 2002/09/18 By M.Maeda */
				/*---------------------------------------------------------------------
				** IDP(DICEP)を使用してスキャナ送信する場合(SAKAKI用)
				** 1998/08/11 H.Yoshikawa
				*/
  #if (PRO_SCN_CODEC_TYPE == IDP301)	/* 1998/08/11 H.Yoshikwa */
				if ((CommunicateType == TX_ECM_SCAN) ||
				    (CommunicateType == TX_G3_SCAN)) { /* The condition is added by H.Kubo 1998/08/19  */
					DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt),
									(UDWORD) ECM_BUFFER_AREA_START_ADDRESS
									);
				}
				else {
					DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt/2),
									(UDWORD) ECM_BUFFER_AREA_START_ADDRESS
									);
				}
				ECM_WritePageCounter ++;	/* 1998/11/19 */
  #else
				DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt/2),
								(UDWORD) ECM_BUFFER_AREA_START_ADDRESS
								);
  #endif
			}
		}
		else {	/*	ここに入って来たら絶対にダメ（ＤＲＡＭ領域を壊しています）デバッグの為	*/
			debug_err = 1;
		}
	}
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[通信コーデック　デコードＤＭＡ終了割り込み監視タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_DecodeDMA_TC_DetectTask(void){}]
	date		:[1994/01/12]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
void  MDM_DecodeDMA_TC_DetectTask(void)
{
#if (PRO_CPU == SH7043) && (PRO_EXT_DMAC == ENABLE) /* H.Kubo 1998/01/29 */ /* ported by T.Takagi 2001/12/18 T.Takagi */
	UWORD word_register_value;
#endif

	while (1) {
		/*--------------------------------------*/
		/*	デコードＤＭＡ終了割り込み待ち処理	*/
		/*--------------------------------------*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		if (IsMemoryToCOMCDC_XferDone == NO) { /* Changed by H.Kubo 1997/07/19 */
			/* wai_evt(EVT_DMA0_TC3); */
			wai_evt(EVT_DMA_DRAM_COMCDC);	/*	DRAM -> 通信コーデック by H.Kubo 1997/07/04	*/
		}
		IsMemoryToCOMCDC_XferDone = NO; /* Changed by H.Kubo 1997/07/19 */
		CMN_EnableInterrupt();	/**	割り込み許可	*/
		DecodeMessage.Message = MSG_FROM_DECODEDMA_TC_TASK;
		snd_msg(mbxno.MDM_RxEcmControlTask, &DecodeMessage);
	}
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[モデムステータスチェック]
	function	:[
		1.１０ｍｓタイマー割り込みより呼び出される
		2.該当ステータスが発生した時、イベントをセットする
		3.イベントをセットする前に、待ちステータスを初期化する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[UWORD near MDM_ModemStatusCheck(void){}]
	date		:[1993/12/27]
	update		:[1995/12/13]
	author		:[曽根岡拓、木元修]
*************************************************************************/
UWORD  MDM_ModemStatusCheck(void)
{
	/** for Debug of Control Channel Turn-off **/
	/** ゆくゆくはモデム割り込みに移動させる方が効率が良い **/
	/** 尚、ＣＴＳの立ち下がりの検出が必要なのは受信側のコントロールチャンネルのＴｕｒｎＯｆｆ時のみ **/

	if (SYS_V34ProcedureExecuting()) {	/* add if() 1997/02/01 Y.Murata */
		if (MDM_CtsTurnOffCheckFlag == TRUE) {
			dbg_new_cts_status = (UBYTE)(inp(MDM_REG_0F_PORT) & IO_BIT_CTS);
			if (!dbg_new_cts_status) {
				if (dbg_old_cts_status) {
					dbg_old_cts_status = dbg_new_cts_status;

					dbg_old_rlsd_status = 0;	/**  By O.K Feb.03,1996 **/
					dbg_new_rlsd_status = 0;	/**  By O.K Feb.03,1996 **/

					MDM_CtsTurnOffFlag = 1;
					ModemStatusFlag = 1;
					return(EVT_MDM_PNSUC);
				}
			}
			dbg_old_cts_status = dbg_new_cts_status;
		}
	}

	/** プライマリーチャンネル終了処理（暫定） By O.K Feb.03,1996 **/
	if (MDM_RlsdTurnOffCheckFlag == TRUE) {
		dbg_new_rlsd_status = (UBYTE)(inp(MDM_REG_0F_PORT) & IO_BIT_RLSD);
		if (!dbg_new_rlsd_status) {
			if (dbg_old_rlsd_status) {
				dbg_old_rlsd_status = dbg_new_rlsd_status;

				/* Ｌ８１５３－４以降は、プライマリーチャンネルの終了時ＲＬＳＤが
				** ＴｕｒｎＯｆｆしない様になってしまったので、ここで、下記のイベ
				** ントを出すのはＲ６７１３－１３Ｐのみとなります。
				** また、ー４以降は、モデムステータスをチェックして、イベントが発
				** 行されるようになります。
				** By O.Kimoto 1996/10/17
				*/
				if (SYS_V34ProcedureExecuting()) {	/* add if 1996/10/24 Y.Murata */
					if (SYS_ModemVersion == MDM_L6713_13P) {
						MDM_RlsdTurnOffFlag = 1;
						return(EVT_MDM_TURNOFF);
					}
				}
			}
		}
		/* Add for EQM By O.K Feb.22,1996 */
		else if (dbg_new_rlsd_status) {
			if (!dbg_old_rlsd_status) {
				dbg_old_rlsd_status = dbg_new_rlsd_status;
				MDM_RlsdTurnOnFlag = 1;
				return(EVT_MDM_TURNON);
			}
		}
		dbg_old_rlsd_status = dbg_new_rlsd_status;
	}


	/*----------------------*/
	/*	シーケンス信号検出	*/
	/*----------------------*/
	/* 1997/02/01 Y.Murata
	 * トレーニング信号とＴＣＦデータの検出はここで行います
	 * モデム割り込みでは今の制御ではＴＣＦデータは検出できない。（今までは偶然動いていた）
	 * それと、ＴＣＦの終了の検出もここでやります
	*/
	/* ﾀｰﾝｱﾗｳﾝﾄﾞ debug 1996/03/13 Y.M */
	/*標準でいれます 1996/05/22 Y.Murata */
	if (SYS_V34ProcedureExecuting()) {	/* add if() 1997/02/01 Y.Murata */
		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_TRDETON) {
				MDM_REG_0A_PortStatus = inp(MDM_REG_0A_PORT);
				/** ＴｕｒｎＯｆｆ検出（Ｖ．３４時） **/
				if (MDM_REG_0A_PortStatus & IO_BIT_PNSUC) {
					MDM_SetIO(POS_PNSUC,OFF);	/** PNSUC Access By O.Kimoto 1996/05/13 **/
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					return(EVT_MDM_PNSUC);
				}
			}
		}
	}
	else {
		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_TRDETON) {
				/** モデムトレーニング受信 **/
				MDM_REG_0A_PortStatus = inp(MDM_REG_0A_PORT);
				MDM_REG_0D_PortStatus = inp(MDM_REG_0D_PORT);
				if ((MDM_REG_0D_PortStatus & IO_BIT_PNDET) ||
					(MDM_REG_0A_PortStatus & IO_BIT_PNSUC)) {

					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					return(EVT_MDM_PNSUC);
				}
			}
		}
	}

	if (SYS_V34ProcedureExecuting() == 0) {	/* 1997/02/01 Y.Murata */
		if (ModemWaitStatus & PHS_STAT_CHECK_SEQ_BIT) {
			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_RLSDON) {
				MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT);
				/** ＴＣＦデータ受信 */
				if (MDM_REG_0F_PortStatus & IO_BIT_RLSD) {
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					return(EVT_MDM_PNSUC);
				}
			}

			if ((ModemWaitStatus & 0x00ff) == PHS_STAT_CHECK_RLSDOFF) {
				MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT);
				/** ＴＣＦデータ受信END */
				if (MDM_REG_0F_PortStatus & IO_BIT_RLSD) {
					/* Nothing */
				}
				else {
					ModemStatusFlag = 1;	/**	モデム割り込み発生フラグセット	*/
					return(EVT_MDM_PNSUC);
				}
			}
		}

		/* ここの処理はモデム割り込みでもやっています。保険みたいなものです 1997/02/01 */
		if (ModemBlock.Mode == MODE_RX_FSK) {
			if (ModemControl.Status & STAT_FLGDET) {
			/* 1997/04/01 Y.Murata
			 * 会話予約でPIPとPRI_EOPがぶつかってしまう。SYNCDの誤検出が原因。
			 * RLSDがONの時のみSYNCDを見に行く。
			*/
				if (MDM_GetIO(POS_RLSD)) {
					MDM_REG_0A_PortStatus = inp(MDM_REG_0A_PORT);
					if (MDM_REG_0A_PortStatus & IO_BIT_SYNCD) {	/**	フラグ検出時	*/
						ModemControl.Status &= ~STAT_FLGDET;	/**	フラグ検出フェーズ初期化	*/
						ModemControl.Status |= STAT_FCSDET;		/**	ＦＣＳ検出フェーズ設定	*/
						/**	受信データ要求ＯＮ	*/
						ModemInterruptFlag = 1;	/**	モデム割り込み完了フラグセット	*/
						return(EVT_RX_FLG_DETECT);
					}
				}
			}
		}
	}

	return (0);
}



/*************************************************************************
	module		:[モデムステータス監視タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	date		:[1994/02/04]
	author		:[曽根岡拓]
*************************************************************************/
void 			MDM_ModemStatusCheckTask(UWORD *mbx_no)
{
	UBYTE dust_data;

	CMN_DisableInterrupt();	/**	割り込み禁止	*/
	if (ModemStatusFlag == 0) {
		wai_evt(EVT_MDM_PNSUC);
	}
	ModemStatusFlag = 0;
	CMN_EnableInterrupt();	/**	割り込み許可	*/

	/** For Debug By O.K Jan.19,1996 **/
	while(inp(MDM_REG_0C_PORT) & IO_BIT_RXFNE) {
		dust_data = inp(MDM_REG_00_PORT);
	}

	ModemWaitStatus = 0;
	MDM_CtsTurnOffCheckFlag = FALSE;
	ModemMessage.Message = MSG_ENABLE_MODEM_STATUS;
	snd_msg(*mbx_no, &ModemMessage);
	wai_tsk(0xffff);
}


/*************************************************************************
	module		:[トーン検出処理(１０ｍｓ割り込み)]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	ProtoType	:[void far MDM_ToneCheck(void){}]
	date		:[1995/12/15]
	author		:[木元　修]
*************************************************************************/
#if defined (SAKAKI) /* for DEBUG by H.Kubo 1998/02/10 */ /* CONST is added by H.Kubo 1998/02/16 *//* 2002/09/18 By M.Maeda */
CONST UBYTE MDM_DebugFilterBit = 0;
static UDWORD MDM_ModemFilterDebugCounter = 0;
#endif
void  MDM_ToneCheck(void)
{
	UBYTE modem_reg_0b_port;
	modem_reg_0b_port = inp(MDM_REG_0B_PORT);
	MDM_REG_0B_PortStatus = modem_reg_0b_port; /* Memorize the port status */

	if (modem_reg_0b_port & IO_BIT_TONEA) {
		idet_evt(EVT_TONE_FILTER1_ON);
	}
	else {
		idet_evt(EVT_TONE_FILTER1_OFF);
	}
	if (modem_reg_0b_port & IO_BIT_TONEB) {
		idet_evt(EVT_TONE_FILTER2_ON);
	}
	else {
		idet_evt(EVT_TONE_FILTER2_OFF);
	}
	if (modem_reg_0b_port & IO_BIT_TONEC) {
		idet_evt(EVT_TONE_FILTER3_ON);
	}
	else {
		idet_evt(EVT_TONE_FILTER3_OFF);
	}

#if defined (SAKAKI) /* for DEBUG by H.Kubo 1998/02/10 *//* 2002/09/18 By M.Maeda */
 	/* モデムのフィルタのデバッグのためのｺｰﾄﾞです。
 	** 通信していないとき、 10ms 毎に EcmBuffer に
 	** フィルタのフラグを書き込みます。
 	** 実際の動作では何の役にも立ちません。
 	*/
 	if (MDM_DebugFilterBit == 1 && ModemBlock.Mode == 0) {
 		*(&EcmBuffer[0][0] + MDM_ModemFilterDebugCounter) = modem_reg_0b_port;
 		if (++MDM_ModemFilterDebugCounter >= ECM_BUFFER_MAX * ECM_BUFFER_LENGTH ) {
 			MDM_ModemFilterDebugCounter = 0;
 		}
 	}
#endif
}


/*************************************************************************
	module		:[モデムステータスを監視する]
	function	:[
		1.１０ｍｓ割り込みから呼び出され、以下の処理を行う。
		-	a)モデムの内部遷移ステータスを監視する。
		-	b)ＡＢＣＯＤＥレジスターを読み出す。
	]
	return		:[
		無し
	]
	common		:[
		MDM_ModemInternalStatusCounter
		MDM_NewSecTxb
		MDM_OldSecTxb
		MDM_InternalStatus[]
		MDM_SameSecTxbTime
		MDM_NewSecRxb
		MDM_OldSecRxb
		MDM_SameSecRxbTime
	]
	condition	:[
		１０ｍｓ割り込みからのみコールします。
	]
	comment		:[]
	ProtoType	:[UBYTE near MDM_CheckInternalStatus(void){}]
	date		:[1996/02/28]
	author		:[木元修]
*************************************************************************/
void  MDM_CheckInternalStatus(void)
{
	struct ModemInternalStatusTable_t  *modeminternaltable_ptr;
	UWORD return_value;
	UBYTE MDM_StatusChanged;
	UBYTE temp_abort_code;
	UBYTE dbg_temp_reg;
	UBYTE	read_reg; /* Added by H.Kubo 1997/08/28 */

	/* debug */
	UBYTE debug;
	debug = 0;
	if (debug) {
		if (ModemBlock.Mode == MODE_RX_ECM) {
			if (MDM_GetIO(POS_TDBE)) {
			}
			else {
				debug++;
			}
		}
	}



	modeminternaltable_ptr = &MDM_InternalStatus[MDM_ModemInternalStatusCounter];

	MDM_StatusChanged = FALSE;
	return_value = 0;

	dbg_temp_reg = inp(MDM_REG_0A_PORT);
	/* ロックウエルモデム不具合
	 * 1997/09/09 Y.Murata
	 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
	 *  受信できないことがある」
	 * ひらたくいえば、モデムが発散します。
	 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
	*/
	if (SYS_V34ProcedureExecuting()) {
		if ((MDM_PixStartFlag == 1) && (MDM_AlreadyRtdisSetFlag >= 10)) {	/* 100ms */
			MDM_PixStartFlag = 0;
			MDM_AlreadyRtdisSetFlag = 0;

#if (0)
** 			/* ０で有効です */
** 			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
** 				/* ｱﾄﾞﾚｽ$B0Fと$A0Fを20h->F0h */
** 				/* 設定ﾀｲﾐﾝｸﾞ２ */
** 				DspRamAccessWriteMethod3(0xA0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
** 				DspRamAccessWriteMethod3(0xB0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
** 			}
#else
			MDM_RecoverStatus |= MDM_EVT_SHIFT_100PPM_1;
#endif
		}
	}
	else {

	/* 1997/05/09 Y.Murata
	 * Ｒ．３．３対策 RLSDが誤動作すればRTDISのｾｯﾄﾀｲﾐﾝｸﾞが狂いR.3.3が発生するため100msのﾁｬﾀを見る
	*/
	if (dbg_temp_reg & IO_BIT_PNSUC) {
			if ((MDM_PixStartFlag == 1) && (MDM_AlreadyRtdisSetFlag >= 10)) {	/* 100ms */
				MDM_PixStartFlag = 0;
				MDM_AlreadyRtdisSetFlag = 0;

			/* ロックウエルモデム不具合
			 * 1997/09/09 Y.Murata
			 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
			 *  受信できないことがある」
			 * ひらたくいえば、モデムが発散します。
			 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
			*/
#if (0)
** 				/* ０で有効です */
** 				if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
** 					if (ModemBlock.Type == TYPE_V17) {
** 						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを600h->3000h */
** 						/* 設定ﾀｲﾐﾝｸﾞ２ */
** 						DspRamAccessWriteMethod3(0xA0F, 0x3000, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
** 						DspRamAccessWriteMethod3(0xB0F, 0x3000, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
** 					}
** 					else if (ModemBlock.Type == TYPE_V29) {
** 						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを80h->200h */
** 						/* 設定ﾀｲﾐﾝｸﾞ２ */
** 						DspRamAccessWriteMethod3(0xA0F, 0x0200, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
** 						DspRamAccessWriteMethod3(0xB0F, 0x0200, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
** 					}
** 					else {
** 						/* それ以外の時は何もしない */
** 					}
** 				}
#else
				MDM_RecoverStatus |= MDM_EVT_SHIFT_100PPM_2;
#endif

				dbg_temp_reg = inp(MDM_REG_06_PORT);
				dbg_temp_reg |= IO_BIT_RTDIS;
				outp(MDM_REG_06_PORT,dbg_temp_reg);

				/* 以下はＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策です。
				** By O.Kimoto 1996/12/18
				*/

				MDM_AlreadyRtdisSetFlag ++;

				/* 1997/02/05 Y.Murata
				 * トレイン・オン・データセット
				 */
				/* MDM_SetIO(POS_TOD, ON); 1997/02/06 Y.M */

				/* 1997/02/25 Y.Murata
				 * 良好なＥＹＥＱ値が確定してから、ＰＩＸの頭まで
				 * イコライザーをホールドします。
				 * Ｖ２９の７２００ｂｐｓのＥＹＥ発散対策。
				*/
				MDM_SetIO(POS_EQFZ, OFF);
			}
		}
	}

	if (MDM_ModemInternalStatusCounter < MODEM_STATUS_TABLE_MAX) {

		/* モデムステータスの１レコードを毎回クリアする By O.Kimoto 1996/09/27 */
		modeminternaltable_ptr->Tx_Phase = 0xff;
		modeminternaltable_ptr->Rx_Phase = 0xff;

		modeminternaltable_ptr->DTR_Status = 0xff;
		modeminternaltable_ptr->RTS_Status = 0xff;
		modeminternaltable_ptr->CTS_Status = 0xff;
		modeminternaltable_ptr->RLSD_Status = 0xff;
		modeminternaltable_ptr->FED_Status = 0xff;
		modeminternaltable_ptr->PNDET_Status = 0xff;
		modeminternaltable_ptr->PNSUC_Status = 0xff;
		modeminternaltable_ptr->DMY4_Status = 0xff;

		modeminternaltable_ptr->T30Status = 0xff;

		modeminternaltable_ptr->AbortCode = 0xff;

		modeminternaltable_ptr->Timer = 0x0;

		MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT); /* added by H.Kubo 0F の値は何度も参照されるので、一度読み込んでそのまま使いまわします。 1998/01/28 */

		/* ＳＥＣＴＸＢレジスターのチェック */
		MDM_NewSecTxb = inp(MDM_REG_17_PORT);
		if (MDM_NewSecTxb != MDM_OldSecTxb) {
			MDM_OldSecTxb = MDM_NewSecTxb;
			modeminternaltable_ptr->Tx_Phase = MDM_NewSecTxb;
			MDM_StatusChanged = TRUE;
		}

		/* ＳＥＣＲＸＢレジスターのチェック */
		MDM_NewSecRxb = inp(MDM_REG_16_PORT);
		if (MDM_NewSecRxb != MDM_OldSecRxb) {

#if (0)	/* ＣＣ　ＲｅｔｒａｉｎはＡｂｏｒｔＣｏｄｅで判断します。 By O.Kimoto 1996/09/04 */
** 			/* ＣＣ Ｒｅｔａｉｎ対策（暫定）By O.Kimoto 1996/05/16 */
** 			if ((MDM_OldSecRxb & 0xF0) == 0x80) {
** 				if ((MDM_OldSecRxb & 0xF0) == (MDM_NewSecRxb & 0xF0)) {
** 					if (MDM_NewSecRxb == 0x80) {
** 						/* CC Retrain Start !! */
** 						ControlChannelRetrainFlag = 1;
** 						return_value |= MDM_EVT_CC_RETRAIN_DETECT_BIT;
** 					}
** 				}
** 			}
#endif

			/* Ｌ８１５３－４からプライマリーチャンネルの終了時にＲＬＳＤがＯＦＦしなくなった。
			** その為、＄０Ｃ：７が用意されているがそれも上手く動作しない
			** しかし、ここでの処理が不十分だとＴ．４．１／Ｒ．４．２が多発する。
			** よって、モデムステータスをチェックすることで、ＲＬＳＤのＴｕｒｎＯｆｆを代用する。
			** By O.Kimoto 1996/10/15
			**/
			/* －２２Ｐに関してもこの部分は変更されていない。よって、下記処理はー１３Ｐとそれ以外
			** ということにしておく
			** By O.Kimoto 1997/07/02
			*/
			if (SYS_ModemVersion != MDM_L6713_13P) {
				if (MDM_RlsdTurnOffCheckFlag == TRUE) {
					if (((MDM_OldSecRxb & 0xF0) == 0xA0) && ((MDM_NewSecRxb & 0xF0) == 0x80)) {
						MDM_RlsdTurnOffFlag = 1;
						return_value |= MDM_EVT_MDM_TURNOFF_BIT;
					}
				}
			}

			/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
			** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
			** レインが発生していれば、フラグをセットします。
			** By O.Kimoto 1996/08/14
			*/
			if ((MDM_NewSecRxb & 0xF0) == 0x30) {	/* ０ｘ３Ｃ固定で見ていても良いかもしれない */
				MDM_RetrainFirstCCTrainFlag = 1;
			}

			/* ロックウエルモデム不具合
			 * 1997/09/09 Y.Murata 1997/09/10
			 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
			 *  受信できないことがある」
			 * ひらたくいえば、モデムが発散します。
			 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
			*/
			/* ０で有効です */
#if (0)
** 			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
** 				if (MDM_NewSecRxb == 0x46) {
** 					if (MDM_GetIO(POS_ORG)) {
** 						/* Nothing */
** 					}
** 					else {
** 						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを20h->F0h */
** 						DspRamAccessWriteMethod3(0xA0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
** 						DspRamAccessWriteMethod3(0xB0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
** 					}
** 				}
** 			}
#else
			MDM_RecoverStatus |= MDM_EVT_SHIFT_100PPM_3;
#endif

			MDM_OldSecRxb = MDM_NewSecRxb;
			modeminternaltable_ptr->Rx_Phase = MDM_NewSecRxb;
			MDM_StatusChanged = TRUE;
		}

		/* ＤＴＲビットのチェック */
		MDM_NewDtrStatus = (UBYTE)(inp(MDM_REG_09_PORT) & IO_BIT_DTR);
		if (MDM_NewDtrStatus != MDM_OldDtrStatus) {
			MDM_OldDtrStatus = MDM_NewDtrStatus;
			modeminternaltable_ptr->DTR_Status &= ~DTR_OFF_STATUS;
			if (MDM_OldDtrStatus == 0) {
				/* modeminternaltable_ptr->DTR_Status &= ~DTR_OFF_STATUS; */
			}
			else {
				modeminternaltable_ptr->DTR_Status |= DTR_ON_STATUS;
			}
			MDM_StatusChanged = TRUE;
		}

		/* ＲＬＳＤビットのチェック */
		MDM_NewRlsdStatus = (UBYTE)(MDM_REG_0F_PortStatus & IO_BIT_RLSD);
		if (MDM_NewRlsdStatus != MDM_OldRlsdStatus) {

			if (MDM_PixStartFlag == 1) {
				if ((MDM_OldRlsdStatus == 0) && (MDM_NewRlsdStatus == IO_BIT_RLSD)) {
					MDM_AlreadyRtdisSetFlag ++;
				}
			}

			MDM_OldRlsdStatus = MDM_NewRlsdStatus;
			modeminternaltable_ptr->RLSD_Status &= ~RLSD_OFF_STATUS;
			if (MDM_OldRlsdStatus == 0) {
				/* modeminternaltable_ptr->RLSD_Status &= ~RLSD_OFF_STATUS; */
				if (CL1_PNSUC_TurnOff == 0) {	/*  By O.Kimoto 1997/05/16 */
					CL1_RLSD_TurnOff = 1;	/*  By O.Kimoto 1997/05/16 */
				}
			}
			else {
				modeminternaltable_ptr->RLSD_Status |= RLSD_ON_STATUS;
				CL1_RLSD_TurnOff = 0;	/*  By O.Kimoto 1997/05/16 */
			}
			MDM_StatusChanged = TRUE;
		}
		/* 1997/05/09 Y.M */
		else {
			if (MDM_PixStartFlag == 1) {
				if (MDM_NewRlsdStatus & IO_BIT_RLSD) {
					MDM_AlreadyRtdisSetFlag ++;
				}
				else {
					MDM_AlreadyRtdisSetFlag = 0;
				}
			}
		}

		/* ＣＴＳビットのチェック */
		MDM_NewCtsStatus = (UBYTE)(MDM_REG_0F_PortStatus & IO_BIT_CTS);
		if (MDM_NewCtsStatus != MDM_OldCtsStatus) {
			MDM_OldCtsStatus = MDM_NewCtsStatus;
			modeminternaltable_ptr->CTS_Status &= ~CTS_OFF_STATUS;
			if (MDM_OldCtsStatus == 0) {
				/* modeminternaltable_ptr->CTS_Status &= ~CTS_OFF_STATUS; */
			}
			else {
				modeminternaltable_ptr->CTS_Status |= CTS_ON_STATUS;
			}
			MDM_StatusChanged = TRUE;
		}

		/* ＲＴＳビットのチェック */
		MDM_NewRtsStatus = (UBYTE)(inp(MDM_REG_08_PORT) & IO_BIT_RTS);
		if (MDM_NewRtsStatus != MDM_OldRtsStatus) {
			MDM_OldRtsStatus = MDM_NewRtsStatus;
			modeminternaltable_ptr->RTS_Status &= ~RTS_OFF_STATUS;
			if (MDM_OldRtsStatus == 0) {
				/* modeminternaltable_ptr->RTS_Status &= ~RTS_OFF_STATUS; */
			}
			else {
				modeminternaltable_ptr->RTS_Status |= RTS_ON_STATUS;
			}
			MDM_StatusChanged = TRUE;
		}

		/* ＦＥＤビットのチェック */
		MDM_NewFedStatus = (UBYTE)(MDM_REG_0F_PortStatus & IO_BIT_FED);
		if (MDM_NewFedStatus != MDM_OldFedStatus) {
			MDM_OldFedStatus = MDM_NewFedStatus;
			modeminternaltable_ptr->FED_Status &= ~FED_OFF_STATUS;
			if (MDM_OldFedStatus == 0) {
				/* modeminternaltable_ptr->FED_Status &= ~FED_OFF_STATUS; */
			}
			else {
				modeminternaltable_ptr->FED_Status |= FED_ON_STATUS;
			}
			MDM_StatusChanged = TRUE;
		}

		/* ＰＮＤＥＴビットのチェック */
		MDM_NewPndetStatus = (UBYTE)(inp(MDM_REG_0D_PORT) & IO_BIT_PNDET);
		if (MDM_NewPndetStatus != MDM_OldPndetStatus) {
			MDM_OldPndetStatus = MDM_NewPndetStatus;
			modeminternaltable_ptr->PNDET_Status &= ~PNDET_OFF_STATUS;
			if (MDM_OldPndetStatus == 0) {
				/* modeminternaltable_ptr->PNDET_Status &= ~PNDET_OFF_STATUS; */
			}
			else {
				modeminternaltable_ptr->PNDET_Status |= PNDET_ON_STATUS;
			}
			MDM_StatusChanged = TRUE;
		}

		/* ＰＮＳＵＣビットのチェック */
		/* MDM_NewPnsucStatus = (UBYTE)(inp(MDM_REG_0A_PORT) & IO_BIT_PNSUC); */
		read_reg = inp(MDM_REG_0A_PORT); /* Changed by H.Kubo 1997/08/28 */
		MDM_NewPnsucStatus = read_reg & IO_BIT_PNSUC;
		if (MDM_NewPnsucStatus != MDM_OldPnsucStatus) {
			MDM_OldPnsucStatus = MDM_NewPnsucStatus;
			modeminternaltable_ptr->PNSUC_Status &= ~PNSUC_OFF_STATUS;
			if (MDM_OldPnsucStatus == 0) {
				/* modeminternaltable_ptr->PNSUC_Status &= ~PNSUC_OFF_STATUS; */

				if (CL1_RLSD_TurnOff == 0) {
					CL1_PNSUC_TurnOff = 1;	/*  By O.Kimoto 1997/05/16 */
				}
			}
			else {
				modeminternaltable_ptr->PNSUC_Status |= PNSUC_ON_STATUS;
				CL1_PNSUC_TurnOff = 0;	/*  By O.Kimoto 1997/05/16 */
			}
			MDM_StatusChanged = TRUE;
		}
		/* ＦＥビットのチェック */
		MDM_NewFeStatus = read_reg & IO_BIT_FE; /*read_reg = inp(MDM_REG_0A_PORT);*/
		if (MDM_NewFeStatus != MDM_OldFeStatus) {
			MDM_OldFeStatus = MDM_NewFeStatus;
			if (MDM_NewFeStatus) {
				CL1_HDLC_AbortSequence = 1;
			}
			else {
				CL1_HDLC_AbortSequence = 0;
			}
			MDM_StatusChanged = TRUE;
		}

		/* ＤＭＹ４のチェック */
		/** とりあえず、ＦＬＡＧＤＴのチェックを入れておきます。 */
		/* change FLAGDT -> SYNCD 1997/01/16 Y.Murata */
		/* やっぱりFLAGDTにします 1997/01/28 Y.Murata */
		MDM_NewDmy4Status = (UBYTE)(inp(MDM_REG_0A_PORT) & IO_BIT_FLAGDT);
		if (MDM_NewDmy4Status != MDM_OldDmy4Status) {
			MDM_OldDmy4Status = MDM_NewDmy4Status;
			modeminternaltable_ptr->DMY4_Status &= ~DMY4_OFF_STATUS;
			if (MDM_OldDmy4Status == 0) {
				/* modeminternaltable_ptr->DMY4_Status &= ~DMY4_OFF_STATUS; */

				/* Class1で、高速受信から抜けない時が有るので、FLAGDTの検出をします。 By O.Kimoto 1997/05/24 */
				CL1_FLAGDT_Found = 0;	/*  By O.Kimoto 1997/05/16 */

			}
			else {
				modeminternaltable_ptr->DMY4_Status |= DMY4_ON_STATUS;

				/* Class1で、高速受信から抜けない時が有るので、FLAGDTの検出をします。 By O.Kimoto 1997/05/24 */
				if ((CL1_PNSUC_TurnOff == 0) && (CL1_RLSD_TurnOff == 0)) {
					CL1_FLAGDT_Found = 1;	/*  By O.Kimoto 1997/05/16 */
				}

			}
			MDM_StatusChanged = TRUE;
		}

		/* ＡＢＣＯＤＥレジスターの読み出し処理 */
		temp_abort_code = inp(MDM_REG_14_PORT);
		if (temp_abort_code != 0x00) {
			MDM_AbortCode = temp_abort_code;
			MDM_InternalStatus[0].Rx_Phase = MDM_AbortCode;	/* Add By O.Kimoto 1996/10/24 */
			modeminternaltable_ptr->AbortCode = MDM_AbortCode;
			outp(MDM_REG_14_PORT,0x00);
			return_value |= MDM_EVT_ABORT_CODE_DETECT_BIT;

			switch(MDM_AbortCode) {
			case 0x25:	/* timeout waiting for probing cut-off tone */
			case 0x2A:	/* checksum error in INFO1 */
			case 0x2B:	/* found tone before INFO0 */
				/* 本当はここでＮＥＷＣをしばきたい */
				break;
			case 0x91:	/* error in first CC train */
			case 0xC7:	/* training on TRN failed */
				MDM_RetrainFirstCCTrainFlag = 1;
				/* もしかすると、ＮＥＷＣが必要かもしれない */
				break;
			case 0x92:	/* time out waiting for PPh */
			case 0x94:	/* time out waiting for ALT */
			case 0x95:	/* Found ACh */
			case 0xD6:	/* Timed out waiting for MPh */	/* Add test By O.Kimoto 1996/10/24 */
			case 0xD8:	/* Timed out waiting for E */	/* Add test By O.Kimoto 1996/10/24 */
				ControlChannelRetrainFlag = 1;
				return_value |= MDM_EVT_CC_RETRAIN_DETECT_BIT;
				MDM_NewT30Status = MODE_CC_RETRAIN;
				break;
			case 0x96:	/* FED off during CC data */
			case 0xDB:	/* Time out in transmitter MPh *//* add test By O.Kimoto 1996/10/17 */
				MDM_FedOffFlag = 1;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */
				break;
			}
		}

		/* Ｔ３０Ｓｔａｔｕｓのチェック */
		if (MDM_NewT30Status != MDM_OldT30Status) {
			MDM_OldT30Status = MDM_NewT30Status;
			modeminternaltable_ptr->T30Status = MDM_NewT30Status;
			MDM_StatusChanged = TRUE;
		}

		if (MDM_StatusChanged == TRUE) {
			modeminternaltable_ptr->Timer = MDM_ModemInternalStatusTimer;
			MDM_ModemInternalStatusCounter++;

			/* モデムステータスバッファをリングで使います。 By O.Kimoto 1996/09/20 */
			if (MDM_ModemInternalStatusCounter >= MODEM_STATUS_TABLE_MAX) {
				MDM_ModemInternalStatusCounter = 1;
			}

		}

		MDM_ModemInternalStatusTimer ++;
	}

	/* チャンネル切り替え時のキャリア断検出処理
	** 本来はタスクにしたいところですが、桐＋では時期的に
	** 間に合いませんので割り込み処理としておきます。
	** 杏以降はタスクにします。
	** By O.Kimoto 1996/09/10
	*/
	if ((MDM_CarrierDropoutFlag != 0xFF)) {
		if (!(inp(MDM_REG_0F_PORT) & IO_BIT_FED)) {
			MDM_CarrierDropoutTimer ++;
			if (MDM_CarrierDropoutTimer >= (UWORD)(6000/10)) {
				MDM_CarrierDropoutFlag = 1;
				MDM_FedOffFlag = 2;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/20 */
			}
		}
		else {
			MDM_CarrierDropoutTimer = 0;
		}
	}

	/* 受信レベルの測定 1997/01/28 Y.Murata */
	if (SYS_V34ProcedureExecuting() == 0) {	/** 従来のプロトコルならば **/
		if (MDM_V21MeasureStartGo) {
			if (MDM_V21MeasureStartGo == 1) {
				if ((MDM_GetIO(POS_SYNCD)) && (MDM_GetIO(POS_RLSD))) {
					MDM_V21MeasureStartGo = 2;
				}
			}
			else {
				MDM_V21MeasureStartGo++;
				if (MDM_V21MeasureStartGo > 82) {	/* 800ms */
					MDM_V21MeasureStartGo = 0;
					MDM_RecoverStatus |= MDM_EVT_RTH_CHANGE;	/* Add By O.Kimoto 1998/02/03 */
				}
			}
		}
	}

	/* Ported from Clover\src\int_time.asm by H.Kubo 1997/09/05 */
	if (return_value & MDM_EVT_CC_RETRAIN_DETECT_BIT ) {
		idet_evt(EVT_MDM_CC_RETRAIN);
	}
	if (return_value & MDM_EVT_MDM_TURNOFF_BIT) {
		idet_evt(EVT_MDM_TURNOFF);
	}
	if (return_value & MDM_EVT_ABORT_CODE_DETECT_BIT ) {
		idet_evt(EVT_MDM_ABCODE);
	}

}

/*************************************************************************
	module		:[モデム不具合救済タスク]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[V53]
	language	:[CH38(V.2.0B)]
	keyword		:[MDM]
	ProtoType	:[void MDM_ModemRecoverTask(void){}]
	date		:[1998/02/03]
	author		:[木元  修]
*************************************************************************/
void MDM_ModemRecoverTask(void)
{
	MDM_RecoverStatus = 0;

	while (1) {
		while (MDM_RecoverStatus == 0) {
			wai_tsk(10/10);

 #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 割り込み処理の補完 added by H.Kubo 1998/11/11 */
			MDM_ModemInterruptComplement();
 #endif
 /*
 ** HINOKIでは、以下の処理を行うと、ＮＤの後のＶ３４受信が高速からＴＵＲＮＯＦＦしないので
 ** SAKAKIのみとします by H.Hirao 1998/12/04
 */
 #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /*(PRO_MODEM_R288F_VERSION >= R288F_VERSION_24P)*/ /* For configuring RLSD drop-out timer. by H.Kubo 1998/10/21 */
	 		if (IsRlsdAndRdbfOn == 1) {
				/* 2002/02/04 Y.Murata
				 * ＳＡＫＡＫＩからＦ網に手動送信でＴ．１．１エラーになる件
				 * SAKAKI世代は、NSFがなかったらDISをもう一回取りにいくSWが初期値で有効となっている。
				 * 26Pの不具合で、V21モード時RLSDのドロップアウト時間が延長されると、そのタイミングでPNSUCも１になってしまう。
				 * この延長区間にきたV21信号は、検出することができません。EYEが発散してしまう。（NEWCをセットするまでなおらない）
				 * FSKには、RLSDドロップアウト時間の延長は必要ないので通らないようにします。
				*/
				if ((!SYS_V34ProcedureExecuting()) && (ModemBlock.Type == TYPE_FSK)) {	/* V21の時 */
					IsRlsdAndRdbfOn = 2;
				}
				else {
					IsRlsdAndRdbfOn = 2;
					MDM_SetRLSD_DropOutTimer(3); /* 3 sec timer */
					if (ModemBlock.Type == TYPE_V27) {
						MDM_SetIO(POS_TOD, ON);
					}
				}
			}
 #endif

 #if (0)	/* deletedbythonda1999/03/05 */
			/*
			** R288F VERSION 24P以上の場合
			** For configuring RLSD drop-out timer. by H.Kubo 1998/10/21
			*/
	 		if (IsRlsdAndRdbfOn == 1) {
				IsRlsdAndRdbfOn = 2;
				MDM_SetRLSD_DropOutTimer(3); /* 3 sec timer */
				if (ModemBlock.Type == TYPE_V27) {
					MDM_SetIO(POS_TOD, ON);
				}
			}
 #endif

		}

		if (MDM_RecoverStatus & MDM_EVT_SHIFT_100PPM_1) {/* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 *//* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
				/* ｱﾄﾞﾚｽ$B0Fと$A0Fを20h->F0h */
				/* 設定ﾀｲﾐﾝｸﾞ２ */
				DspRamAccessWriteMethod3(0xA0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
				DspRamAccessWriteMethod3(0xB0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
			}
			MDM_RecoverStatus &= ~MDM_EVT_SHIFT_100PPM_1;
		}

		if (MDM_RecoverStatus & MDM_EVT_SHIFT_100PPM_2) {/* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 *//* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
				if (ModemBlock.Type == TYPE_V17) {
					/* ｱﾄﾞﾚｽ$B0Fと$A0Fを600h->3000h */
					/* 設定ﾀｲﾐﾝｸﾞ２ */
					DspRamAccessWriteMethod3(0xA0F, 0x3000, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
					DspRamAccessWriteMethod3(0xB0F, 0x3000, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
				}
				else if (ModemBlock.Type == TYPE_V29) {
					/* ｱﾄﾞﾚｽ$B0Fと$A0Fを80h->200h */
					/* 設定ﾀｲﾐﾝｸﾞ２ */
					DspRamAccessWriteMethod3(0xA0F, 0x0200, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
					DspRamAccessWriteMethod3(0xB0F, 0x0200, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
				}
				else {
					/* それ以外の時は何もしない */
				}
			}

			/* 以下はＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策です。
			** By O.Kimoto 1996/12/18
			*/
			DspRamAccessWriteMethod1(0x4803,0x00,0xEF);
			MDM_SetIO(POS_EQFZ, OFF);

			MDM_RecoverStatus &= ~MDM_EVT_SHIFT_100PPM_2;
		}

		if (MDM_RecoverStatus & MDM_EVT_SHIFT_100PPM_3) {/* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 *//* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
				if (MDM_NewSecRxb == 0x46) {
					if (MDM_GetIO(POS_ORG)) {
						/* Nothing */
					}
					else {
						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを20h->F0h */
						DspRamAccessWriteMethod3(0xA0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
						DspRamAccessWriteMethod3(0xB0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
					}
				}
			}
			MDM_RecoverStatus &= ~MDM_EVT_SHIFT_100PPM_3;
		}

		if (MDM_RecoverStatus & MDM_EVT_RTH_CHANGE) {/* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 *//* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
			MDM_V21MeasureReceiveLevel = DspRamAccessReadMethod4(0x0A00);
			if (MDM_V21MeasureReceiveLevel > 0x7556) {	/* 30038(7556h) / 682.7 - 54 = -10dBm */

#if 0	/* 1999/12/28 Y.Murata SET_RTH_LEVEL */
** 				/* 1999/12/28 Y.Murata
** 				 * この処理はいりません
** 				*/
** 				MDM_ReceiveLevelExtension = 1;
#endif
			}

#if 0	/* 1999/12/28 Y.Murata SET_RTH_LEVEL */
** 			/* 1997/12/22 RTH_CONTROL
** 			 * 受信レベルより受信器スレッショルドをコントロールします。
** 			*/
** 			if (MDM_RTH_ControlStatus == 0xFF) {
** 				if (MDM_V21MeasureReceiveLevel > 0x7556) {	/* 30038(7556h) / 682.7 - 54 = -10dBm */
** 					MDM_RTH_ControlStatus = RTH_HIGHEST;	/** ON=-16dBm / OFF=-21dBm **/
** 				}
** 				else if (MDM_V21MeasureReceiveLevel > 0x5AAC) {	/* 23212(5AACh) / 682.7 - 54 = -20dBm */
** 					MDM_RTH_ControlStatus = RTH_HIGHER;		/** ON=-26dBm / OFF=-31dBm **/
** 				}
** 				else if (MDM_V21MeasureReceiveLevel > 0x4801) {	/* 18433(4801h) / 682.7 - 54 = -27dBm */
** 					MDM_RTH_ControlStatus = RTH_LOWER;		/** ON=-33dBm / OFF=-38dBm **/
** 				}
** 				else {
** 					MDM_RTH_ControlStatus = RTH_LOWEST;		/** ON=-43dBm / OFF=-48dBm **/
** 				}
** 				MDM_SetIO(POS_RTH, MDM_RTH_ControlStatus);
** 			}
#endif
			/* 1999/12/28 Y.Murata SET_RTH_LEVEL
			 * 受信レベルより受信器スレッショルドをコントロールします。
			 * コネクサント北瓜さん曰く、
			 * 「V.29/V.17の受信に関しては、R288Fのときより改善していると考えて
			 *   おります。しかしながら、従来からあります(R288FもFM336も同じなの
			 *   ですが）ノイズがターンオン/オフレベル付近にある場合のトレーニング
			 *   検出性能が劣っています。今回の現象も似たような症状ではないかと
			 *   思います。信号間の無音時間の違いによってノイズに対する影響の受
			 *   け方が異なり、トレーニングの不安定さがでてきます。
			 * 
			 *   (1)TCFまたはFSKの受信レベルを読み出す。
			 *   (2)受信レベルが-30dbm以上ならば、高速の受信を行う前にRTH(13：3-2)
			 *   を1にセットする。-30dbm以下ならばRTHは0のままで結構です。
			 * 
			 *   この設定により、ターンオンレベルが約-33dbmとなり、ノイズによる影響が
			 *   なくなります。」
			*/
			if (MDM_RTH_ControlStatus == 0xFF) {
				if (MDM_V21MeasureReceiveLevel > 0x4000) {	/* 16384(4000h) / 682.7 - 54 = -30dBm */
					MDM_RTH_ControlStatus = RTH_LOWER;		/** ON=-33dBm / OFF=-38dBm **/
				}
				else {
					MDM_RTH_ControlStatus = RTH_LOWEST;		/** ON=-43dBm / OFF=-48dBm **/
				}
				MDM_SetIO(POS_RTH, MDM_RTH_ControlStatus);
			}

			MDM_RecoverStatus &= ~MDM_EVT_RTH_CHANGE;
		}
	}
	/* ここへは絶対こないはず */
	SaveReturnAddressAndJumpBegin();
}

/*************************************************************************
	module		:[フラグ検出再割込み]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[2回目のPPS.MPSをとりこぼし対策]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	date		:[1999/08/09]
	author		:[K.Okada]
*************************************************************************/
void MDM_ReInterruptSYNCD(void)
{
	UBYTE count;

	/** 割込みOFF */
	MDM_SetIO(POS_RDBIE,OFF);
	MDM_SetIO(POS_NSIE,OFF);

	/** 受信データバッファ読み出し・受信FIFOクリア */
	for( count=0; count<16; count++ ) {
		(void)inp(MDM_REG_00_PORT);
	}
	MDM_SetRxFIFOClear();

	/** ステータスクリア */
	MDM_SetIO(POS_PE, OFF);
	MDM_SetIO(POS_FE, OFF);
	MDM_SetIO(POS_OE, OFF);
	MDM_SetIO(POS_SYNCD, OFF);
	MDM_SetIO(POS_PNSUC,OFF);

	/** 割込みON */
	MDM_SetIO(POS_RDBIE,ON);
	MDM_SetIO(POS_NSIE,ON);

}


#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* ECM_BUFFER_OVER */
/*
 * スキャナ送信 エンコード処理
*/
void	MDM_EncodeDMA_TC_Detect(void)
{
	struct DMA_Data_t CodecTxDMA;
	MESSAGE_t	*MDM_Msg;
	UDWORD	ecd_data_max;
	UDWORD	real_ecd_data_max;
	UWORD	dma_set_cnt;
	UBYTE	debug_err;
	UBYTE	loop_flg;
	UDWORD	remain;
	UDWORD	encode_over_cnt;
	UWORD	counter;			/* 2000/02/10 Y.Murata */
	UDWORD	*tgt_adr;
	UDWORD	*src_adr;

	remain = 0;
	MDM_EcmRemainCount = 0;
	encode_over_cnt = 0;

	/*----------------------------------------------*/
	/*	エンコードＤＭＡ開始（２５６ｂｙｔｅ単位）	*/
	/*	ＣＯＤＥＣ－＞ＥＣＭバッファ				*/
	/*----------------------------------------------*/
	do {	/**	エンコード開始メッセージ待ち	*/
		rcv_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &MDM_Msg);
	} while (!(MDM_Msg->Message == MSG_ENCODE_DMA_START));
	/*----------------------------------------------*/
	/*	ＴＴＩのエンコードデータ量をセットします	*/
	/*----------------------------------------------*/
	EncodeDataCount = EcmBufferBaseWritePoint - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
	if (EncodeDataCount == 0) {
		DebugDMA_EncodeStopCounter = 0;
	}
	else {
		DebugDMA_EncodeStopCounter = (UWORD)(EncodeDataCount/CODEC_DMA_SIZE);
	}

	/*------------------------------------------*/
	/*	ＥＣＭバッファのＭＡＸをセットします	*/
	/*------------------------------------------*/
	ecd_data_max = (UDWORD)0x20000;
	real_ecd_data_max = (UDWORD)0x10000;

	/*----------------------------------------------------------*/
	/*	エンコードＤＭＡのカウント数の設定（２５６ｂｙｔｅ単位）*/
	/*	エンコードＤＭＡのセットアップ、起動					*/
	/*----------------------------------------------------------*/
	DMA0_TC0Flag = 0;
	CodecTxDMA.Channel 		= DMA_SCNCDC_DRAM_CH;
	CodecTxDMA.DstAddress	= (UDWORD) EcmBufferBaseWritePoint;
	CodecTxDMA.SrcAddress	= CodecTxDMA.DstAddress;
	dma_set_cnt = GetCount((UDWORD)(real_ecd_data_max - EncodeDataCount), CODEC_DMA_SIZE);
	CodecTxDMA.Counter		= dma_set_cnt / 2;
	CodecTxDMA.Unit			= DMA_WORD_TRANSFER;
	CodecTxDMA.Direction	= DMA_IO_TO_MEMORY;

	DMA_SetupDMAU(&CodecTxDMA);
	DMA_RequestEnable(CodecTxDMA.Channel);

	loop_flg = 1;
	while (loop_flg) {
		/*------------------------------------------*/
		/*	エンコードＤＭＡ終了割り込み待ち処理	*/
		/*------------------------------------------*/
		CMN_DisableInterrupt();	/**	割り込み禁止	*/
		if (DMA0_TC0Flag == 0) {
			wai_evt(EVT_DMA_SCNCDC_DRAM);
		}
		DMA0_TC0Flag = 0;
		CMN_EnableInterrupt();	/**	割り込み許可	*/

		/*--------------------------*/
		/*	エンコードデータ量更新	*/
		/*--------------------------*/
		EncodeDataCount += (UDWORD) dma_set_cnt;

		/*------------------------------------------------------*/
		/*	送信開始イベント設定（最初の１ブロックだけ有効）	*/
		/*------------------------------------------------------*/
		TxStartFlag = 1;

		/*------------------------------*/
		/*	エンコードＤＭＡの次起動	*/
		/*------------------------------*/
		if (EncodeDataCount < real_ecd_data_max) {	/**	ＥＣＭバッファが空いている時	*/
			dma_set_cnt = GetCount((UDWORD)(real_ecd_data_max - EncodeDataCount), CODEC_DMA_SIZE);
			DMA_RequestMask(CodecTxDMA.Channel);
			DMA_RestartDMAU(CodecTxDMA.Channel, CodecTxDMA.Direction, (dma_set_cnt/2),
								(UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount));
		}
		/*--------------------------------------*/
		/*	エンコードＤＭＡ起動待ち処理	*/
		/*--------------------------------------*/
		else if ((EncodeDataCount >= real_ecd_data_max) && (EncodeDataCount < ecd_data_max)) {	/**	ＥＣＭバッファがＦＵＬＬの時	*/

			CMN_DisableInterrupt();	/**	割り込み禁止	*/
			/** ６４Ｋ超えたでフラグのセット */
			MDM_EcmBufferOverEncodeStop = 1;

			MDM_EcmRemainCount = 0;

			encode_over_cnt = 0;

			if (CodecPageStatus != CDC_CONTINUE) {
				TxStartFlag = 1;		/* 2000/02/10 Y.Murata */
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				loop_flg = 0;
			}
			else {
				CodecPageStatus = CDC_BLOCK_END;	/**	コーデックステータスをブロックエンドにセット	*/
				CMN_EnableInterrupt();	/**	割り込み許可	*/
				dma_set_cnt = GetCount((UDWORD)(ecd_data_max - EncodeDataCount), CODEC_DMA_SIZE);
				DMA_RequestMask(CodecTxDMA.Channel);
				DMA_RestartDMAU(CodecTxDMA.Channel, DMA_IO_TO_MEMORY, (dma_set_cnt/2), (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount));

				while (1) {

					CMN_DisableInterrupt();	/**	割り込み禁止	*/
					if ((DMA0_TC0Flag == 0) && (MDM_EcmBufferOverEncodeStop)) {
						wai_evt(EVT_DMA_SCNCDC_DRAM);	/*	Ｖ５３内臓ＤＭＡＵ　ＴＣ０	*/
						CMN_DisableInterrupt();	/**	割り込み禁止	*/
					}
					if (DMA0_TC0Flag == 1) {
						DMA0_TC0Flag = 0;
						CMN_EnableInterrupt();	/**	割り込み許可	*/
						MDM_EcmRemainCount += (UDWORD)dma_set_cnt;
						dma_set_cnt = GetCount((UDWORD)(ecd_data_max - (EncodeDataCount+MDM_EcmRemainCount)), CODEC_DMA_SIZE);
						DMA_RestartDMAU(CodecTxDMA.Channel, DMA_IO_TO_MEMORY, (dma_set_cnt/2), (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+EncodeDataCount+MDM_EcmRemainCount));
						if ((EncodeDataCount+MDM_EcmRemainCount) == ecd_data_max) {
							debug_err = 1;
							outp((UDWORD)0,(UBYTE)0);/* WriteProtectError for ICE */
						}
					}

					if (MDM_EcmBufferOverEncodeStop == 0) {	/* 全部送った */
						CMN_EnableInterrupt();	/**	割り込み許可	*/
						break;
					}
					CMN_EnableInterrupt();	/**	割り込み許可	*/
				}

				do {	/**	エンコード再起動メッセージ待ち	*/
					rcv_msg(mbxno.MDM_EncodeDMA_TC_DetectTask, &MDM_Msg);
				} while (!(MDM_Msg->Message == MSG_ENCODE_DMA_START));

				CMN_DisableInterrupt();	/**	割り込み禁止	*/
				if (CodecPageStatus != CDC_BLOCK_END) {
					TxStartFlag = 1;		/* 2000/02/10 Y.Murata */
					if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
					}
					CMN_EnableInterrupt();	/**	割り込み許可	*/
					loop_flg = 0;
				}
				else {
					CodecPageStatus = CDC_CONTINUE;	/**	コーデックステータスをコンティニューにセット	*/
					remain = EncodeDataCount;
					EncodeDataCount = 0;		/**	エンコードデータ量初期化	*/
					TxStartFlag = 0;
					CMN_EnableInterrupt();	/**	割り込み許可	*/

					/* 2000/02/10 Y.Murata
					 *
					 *
					*/
					DMA_RequestMask(CodecTxDMA.Channel);
					MDM_EcmRemainCount = DMA_CheckDMA_Address(DMA_SCNCDC_DRAM_CH,DMA_IO_TO_MEMORY) - (UDWORD)ECM_BUFFER_AREA_START_ADDRESS;
					if (MDM_EcmRemainCount >= 0x10000) {
						MDM_EcmRemainCount -= 0x10000;
					}

					if (MDM_EcmRemainCount) {
						tgt_adr = (UDWORD *)&EcmBuffer[0][0];
						src_adr = (UDWORD *)&EcmBuffer2[0][0];
						for (counter = 0; counter < ((MDM_EcmRemainCount/4) + 1); counter++) {
							*tgt_adr = *src_adr;
							tgt_adr++;
							src_adr++;
							if (!(counter & 0x00FF)) {	/* 256回に1回停める */
								wai_oneshot(1);
							}
						}
					}
					if (MDM_EcmRemainCount == 0) {
						DebugDMA_EncodeStopCounter = 0;
					}
					else {
						DebugDMA_EncodeStopCounter = (UWORD)(MDM_EcmRemainCount/CODEC_DMA_SIZE);
					}
/* 移動 */
					dma_set_cnt = GetCount((UDWORD)(ecd_data_max - (remain+MDM_EcmRemainCount)), CODEC_DMA_SIZE);
					DMA_RestartDMAU(CodecTxDMA.Channel, DMA_IO_TO_MEMORY, (dma_set_cnt/2), (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+MDM_EcmRemainCount));
					CMN_DisableInterrupt();	/**	割り込み禁止	*/
					EncodeDataCount += MDM_EcmRemainCount;
					CMN_EnableInterrupt();	/**	割り込み許可	*/

					MDM_EcmRemainCount = 0;

					SCN_SetScanDMA(SCN_DISABLE);				/** スキャン用ＤＭＡ禁止 */
					SCN_SetScanDMA(SCN_ENABLE);					/** スキャン用ゲートアレイからコーデックへのＤＲＥＱ許可 Apr.24,1994 */
					if (SCN_MotorSpeedControl != SCN_MOTOR_SPEED_STOP) {
						SCN_MotorSpeedControl = SCN_MOTOR_SPEED_STOP;
					}
					/* ここまで 1997/02/08	By T.Yamaguchi */

					/*-----------------------------------------------------
					** ６４ＫＢ送出完了後、次の６４ＫＢ分のデータをコーデックから取り出しを開始する時に、
					** エンコードタスクがすでに、エンコードを終了し EVT_DMA_SCNCDC_DRAM のイベント待ちとなっている場合には、
					** 読み取りモータの再起動をここで実施するようにする。
					** 1997/05/09
					** H.Yoshikawa
					*/
					if (CDC_WaitingCDC0_DMA0_END) {
						SCN_RestartMotor();
					}
#if defined(POPLAR_F)		/* 2000/02/04 Y.Murata */
					else {
						SYB_MaintenanceSwitch[87] |= 0x80;	/* mntsw I:7-7 */
						SCN_RestartMotor();
					}
#endif
#if 0
					dma_set_cnt = GetCount((UDWORD)(ecd_data_max - (remain+MDM_EcmRemainCount)), CODEC_DMA_SIZE);
					DMA_RestartDMAU(CodecTxDMA.Channel, DMA_IO_TO_MEMORY, (dma_set_cnt/2), (UDWORD)(ECM_BUFFER_AREA_START_ADDRESS+MDM_EcmRemainCount));
					CMN_DisableInterrupt();	/**	割り込み禁止	*/
					EncodeDataCount += MDM_EcmRemainCount;
					CMN_EnableInterrupt();	/**	割り込み許可	*/

					MDM_EcmRemainCount = 0;
#endif
				}
			}
		}
		else {	/*	ここに入って来たら絶対にダメ（ＤＲＡＭ領域を壊しています）デバッグの為	*/
			debug_err = 1;
			outp((UDWORD)0,(UBYTE)0);/* WriteProtectError for ICE */
		}
	}
	wai_tsk(0xffff);
}
#endif	/* End of PRO_CODEC_NUMBER */


/*************************************************************************
	module		:[モデムステータスを監視するタスク]
	function	:[
		1.１０ｍｓ割り込みから呼び出され、以下の処理を行う。
		-	a)モデムの内部遷移ステータスを監視する。
		-	b)ＡＢＣＯＤＥレジスターを読み出す。
	]
	return		:[
		無し
	]
	common		:[
		MDM_ModemInternalStatusCounter
		MDM_NewSecTxb
		MDM_OldSecTxb
		MDM_InternalStatus[]
		MDM_SameSecTxbTime
		MDM_NewSecRxb
		MDM_OldSecRxb
		MDM_SameSecRxbTime
	]
	condition	:[
		１０ｍｓ割り込みからのみコールします。
	]
	comment		:[]
	date		:[1999/12/03]
	author		:[村田]
*************************************************************************/
void  MDM_CheckInternalStatusTask(void)
{
	struct ModemInternalStatusTable_t  *modeminternaltable_ptr;
	UWORD return_value;
	UBYTE MDM_StatusChanged;
	UBYTE temp_abort_code;
	UBYTE dbg_temp_reg;
	UBYTE	read_reg; /* Added by H.Kubo 1997/08/28 */

	while (1) {
		wai_tsk(1);

		if (MDM_CHK_InternalStatus()) {

			modeminternaltable_ptr = &MDM_InternalStatus[MDM_ModemInternalStatusCounter];

			MDM_StatusChanged = FALSE;
			return_value = 0;

			dbg_temp_reg = inp(MDM_REG_0A_PORT);
			/* ロックウエルモデム不具合
			 * 1997/09/09 Y.Murata
			 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
			 *  受信できないことがある」
			 * ひらたくいえば、モデムが発散します。
			 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
			*/
			if (SYS_V34ProcedureExecuting()) {
				if ((MDM_PixStartFlag == 1) && (MDM_AlreadyRtdisSetFlag >= 10)) {	/* 100ms */
					MDM_PixStartFlag = 0;
					MDM_AlreadyRtdisSetFlag = 0;

		#if (0)
		** 			/* ０で有効です */
		** 			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
		** 				/* ｱﾄﾞﾚｽ$B0Fと$A0Fを20h->F0h */
		** 				/* 設定ﾀｲﾐﾝｸﾞ２ */
		** 				DspRamAccessWriteMethod3(0xA0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
		** 				DspRamAccessWriteMethod3(0xB0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
		** 			}
		#else
					MDM_RecoverStatus |= MDM_EVT_SHIFT_100PPM_1;
		#endif
				}
			}
			else {

			/* 1997/05/09 Y.Murata
			 * Ｒ．３．３対策 RLSDが誤動作すればRTDISのｾｯﾄﾀｲﾐﾝｸﾞが狂いR.3.3が発生するため100msのﾁｬﾀを見る
			*/
			if (dbg_temp_reg & IO_BIT_PNSUC) {
					if ((MDM_PixStartFlag == 1) && (MDM_AlreadyRtdisSetFlag >= 10)) {	/* 100ms */
						MDM_PixStartFlag = 0;
						MDM_AlreadyRtdisSetFlag = 0;

					/* ロックウエルモデム不具合
					 * 1997/09/09 Y.Murata
					 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
					 *  受信できないことがある」
					 * ひらたくいえば、モデムが発散します。
					 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
					*/
		#if (0)
		** 				/* ０で有効です */
		** 				if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
		** 					if (ModemBlock.Type == TYPE_V17) {
		** 						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを600h->3000h */
		** 						/* 設定ﾀｲﾐﾝｸﾞ２ */
		** 						DspRamAccessWriteMethod3(0xA0F, 0x3000, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
		** 						DspRamAccessWriteMethod3(0xB0F, 0x3000, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
		** 					}
		** 					else if (ModemBlock.Type == TYPE_V29) {
		** 						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを80h->200h */
		** 						/* 設定ﾀｲﾐﾝｸﾞ２ */
		** 						DspRamAccessWriteMethod3(0xA0F, 0x0200, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
		** 						DspRamAccessWriteMethod3(0xB0F, 0x0200, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
		** 					}
		** 					else {
		** 						/* それ以外の時は何もしない */
		** 					}
		** 				}
		#else
						MDM_RecoverStatus |= MDM_EVT_SHIFT_100PPM_2;
		#endif

						dbg_temp_reg = inp(MDM_REG_06_PORT);
						dbg_temp_reg |= IO_BIT_RTDIS;
						outp(MDM_REG_06_PORT,dbg_temp_reg);

						/* 以下はＶ．２７ｔｅｒ　２４００ｂｐｓ　ｎｏｎ－ＥＣＭ対策です。
						** By O.Kimoto 1996/12/18
						*/

						MDM_AlreadyRtdisSetFlag ++;

						/* 1997/02/05 Y.Murata
						 * トレイン・オン・データセット
						 */
						/* MDM_SetIO(POS_TOD, ON); 1997/02/06 Y.M */

						/* 1997/02/25 Y.Murata
						 * 良好なＥＹＥＱ値が確定してから、ＰＩＸの頭まで
						 * イコライザーをホールドします。
						 * Ｖ２９の７２００ｂｐｓのＥＹＥ発散対策。
						*/
						MDM_SetIO(POS_EQFZ, OFF);
					}
				}
			}

			if (MDM_ModemInternalStatusCounter < MODEM_STATUS_TABLE_MAX) {

				/* モデムステータスの１レコードを毎回クリアする By O.Kimoto 1996/09/27 */
				modeminternaltable_ptr->Tx_Phase = 0xff;
				modeminternaltable_ptr->Rx_Phase = 0xff;

				modeminternaltable_ptr->DTR_Status = 0xff;
				modeminternaltable_ptr->RTS_Status = 0xff;
				modeminternaltable_ptr->CTS_Status = 0xff;
				modeminternaltable_ptr->RLSD_Status = 0xff;
				modeminternaltable_ptr->FED_Status = 0xff;
				modeminternaltable_ptr->PNDET_Status = 0xff;
				modeminternaltable_ptr->PNSUC_Status = 0xff;
				modeminternaltable_ptr->DMY4_Status = 0xff;

				modeminternaltable_ptr->T30Status = 0xff;

				modeminternaltable_ptr->AbortCode = 0xff;

				modeminternaltable_ptr->Timer = 0x0;

				MDM_REG_0F_PortStatus = inp(MDM_REG_0F_PORT); /* added by H.Kubo 0F の値は何度も参照されるので、一度読み込んでそのまま使いまわします。 1998/01/28 */

				/* ＳＥＣＴＸＢレジスターのチェック */
				MDM_NewSecTxb = inp(MDM_REG_17_PORT);
				if (MDM_NewSecTxb != MDM_OldSecTxb) {
					MDM_OldSecTxb = MDM_NewSecTxb;
					modeminternaltable_ptr->Tx_Phase = MDM_NewSecTxb;
					MDM_StatusChanged = TRUE;
				}

				/* ＳＥＣＲＸＢレジスターのチェック */
				MDM_NewSecRxb = inp(MDM_REG_16_PORT);
				if (MDM_NewSecRxb != MDM_OldSecRxb) {

		#if (0)	/* ＣＣ　ＲｅｔｒａｉｎはＡｂｏｒｔＣｏｄｅで判断します。 By O.Kimoto 1996/09/04 */
		** 			/* ＣＣ Ｒｅｔａｉｎ対策（暫定）By O.Kimoto 1996/05/16 */
		** 			if ((MDM_OldSecRxb & 0xF0) == 0x80) {
		** 				if ((MDM_OldSecRxb & 0xF0) == (MDM_NewSecRxb & 0xF0)) {
		** 					if (MDM_NewSecRxb == 0x80) {
		** 						/* CC Retrain Start !! */
		** 						ControlChannelRetrainFlag = 1;
		** 						return_value |= MDM_EVT_CC_RETRAIN_DETECT_BIT;
		** 					}
		** 				}
		** 			}
		#endif

					/* Ｌ８１５３－４からプライマリーチャンネルの終了時にＲＬＳＤがＯＦＦしなくなった。
					** その為、＄０Ｃ：７が用意されているがそれも上手く動作しない
					** しかし、ここでの処理が不十分だとＴ．４．１／Ｒ．４．２が多発する。
					** よって、モデムステータスをチェックすることで、ＲＬＳＤのＴｕｒｎＯｆｆを代用する。
					** By O.Kimoto 1996/10/15
					**/
					/* －２２Ｐに関してもこの部分は変更されていない。よって、下記処理はー１３Ｐとそれ以外
					** ということにしておく
					** By O.Kimoto 1997/07/02
					*/
					if (SYS_ModemVersion != MDM_L6713_13P) {
						if (MDM_RlsdTurnOffCheckFlag == TRUE) {
							if (((MDM_OldSecRxb & 0xF0) == 0xA0) && ((MDM_NewSecRxb & 0xF0) == 0x80)) {
								MDM_RlsdTurnOffFlag = 1;
								return_value |= MDM_EVT_MDM_TURNOFF_BIT;
							}
						}
					}

					/* １ｓｔＣＣでリトレインが発生すると、実際のＴ３０＿Ｐｈａｓｅでタイムアウトが
					** 発生するので、１０ｍｓ毎に、モデムのステータスをチェックし、１ｓｔＣＣでリト
					** レインが発生していれば、フラグをセットします。
					** By O.Kimoto 1996/08/14
					*/
					if ((MDM_NewSecRxb & 0xF0) == 0x30) {	/* ０ｘ３Ｃ固定で見ていても良いかもしれない */
						MDM_RetrainFirstCCTrainFlag = 1;
					}

					/* ロックウエルモデム不具合
					 * 1997/09/09 Y.Murata 1997/09/10
					 * 「モデム動作周波数(52.416MHz)に100ppm以上の差がある場合にＶ２９、Ｖ１７、Ｖ３４で
					 *  受信できないことがある」
					 * ひらたくいえば、モデムが発散します。
					 * Ｖ２７ｔｅｒは問題ないとロックウエルは言ってます。
					*/
					/* ０で有効です */
		#if (0)
		** 			if (CHK_V34_R288F_WayWorkFreqBug() == 0) {	/* 対策有効設定なら *//* UNISW_D7:1, 0で有効 */
		** 				if (MDM_NewSecRxb == 0x46) {
		** 					if (MDM_GetIO(POS_ORG)) {
		** 						/* Nothing */
		** 					}
		** 					else {
		** 						/* ｱﾄﾞﾚｽ$B0Fと$A0Fを20h->F0h */
		** 						DspRamAccessWriteMethod3(0xA0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ周波数ｵﾌｾｯﾄ係数 */
		** 						DspRamAccessWriteMethod3(0xB0F, 0x00F0, 0x0000); /* ﾀｲﾐﾝｸﾞﾘｶﾊﾞﾘｰ位相係数 */
		** 					}
		** 				}
		** 			}
		#else
					MDM_RecoverStatus |= MDM_EVT_SHIFT_100PPM_3;
		#endif

					MDM_OldSecRxb = MDM_NewSecRxb;
					modeminternaltable_ptr->Rx_Phase = MDM_NewSecRxb;
					MDM_StatusChanged = TRUE;
				}

				/* ＤＴＲビットのチェック */
				MDM_NewDtrStatus = (UBYTE)(inp(MDM_REG_09_PORT) & IO_BIT_DTR);
				if (MDM_NewDtrStatus != MDM_OldDtrStatus) {
					MDM_OldDtrStatus = MDM_NewDtrStatus;
					modeminternaltable_ptr->DTR_Status &= ~DTR_OFF_STATUS;
					if (MDM_OldDtrStatus == 0) {
						/* modeminternaltable_ptr->DTR_Status &= ~DTR_OFF_STATUS; */
					}
					else {
						modeminternaltable_ptr->DTR_Status |= DTR_ON_STATUS;
					}
					MDM_StatusChanged = TRUE;
				}

				/* ＲＬＳＤビットのチェック */
				MDM_NewRlsdStatus = (UBYTE)(MDM_REG_0F_PortStatus & IO_BIT_RLSD);
				if (MDM_NewRlsdStatus != MDM_OldRlsdStatus) {

					if (MDM_PixStartFlag == 1) {
						if ((MDM_OldRlsdStatus == 0) && (MDM_NewRlsdStatus == IO_BIT_RLSD)) {
							MDM_AlreadyRtdisSetFlag ++;
						}
					}

					MDM_OldRlsdStatus = MDM_NewRlsdStatus;
					modeminternaltable_ptr->RLSD_Status &= ~RLSD_OFF_STATUS;
					if (MDM_OldRlsdStatus == 0) {
						/* modeminternaltable_ptr->RLSD_Status &= ~RLSD_OFF_STATUS; */
						if (CL1_PNSUC_TurnOff == 0) {	/*  By O.Kimoto 1997/05/16 */
							CL1_RLSD_TurnOff = 1;	/*  By O.Kimoto 1997/05/16 */
						}
					}
					else {
						modeminternaltable_ptr->RLSD_Status |= RLSD_ON_STATUS;
						CL1_RLSD_TurnOff = 0;	/*  By O.Kimoto 1997/05/16 */
					}
					MDM_StatusChanged = TRUE;
				}
				/* 1997/05/09 Y.M */
				else {
					if (MDM_PixStartFlag == 1) {
						if (MDM_NewRlsdStatus & IO_BIT_RLSD) {
							MDM_AlreadyRtdisSetFlag ++;
						}
						else {
							MDM_AlreadyRtdisSetFlag = 0;
						}
					}
				}

				/* ＣＴＳビットのチェック */
				MDM_NewCtsStatus = (UBYTE)(MDM_REG_0F_PortStatus & IO_BIT_CTS);
				if (MDM_NewCtsStatus != MDM_OldCtsStatus) {
					MDM_OldCtsStatus = MDM_NewCtsStatus;
					modeminternaltable_ptr->CTS_Status &= ~CTS_OFF_STATUS;
					if (MDM_OldCtsStatus == 0) {
						/* modeminternaltable_ptr->CTS_Status &= ~CTS_OFF_STATUS; */
					}
					else {
						modeminternaltable_ptr->CTS_Status |= CTS_ON_STATUS;
					}
					MDM_StatusChanged = TRUE;
				}

				/* ＲＴＳビットのチェック */
				MDM_NewRtsStatus = (UBYTE)(inp(MDM_REG_08_PORT) & IO_BIT_RTS);
				if (MDM_NewRtsStatus != MDM_OldRtsStatus) {
					MDM_OldRtsStatus = MDM_NewRtsStatus;
					modeminternaltable_ptr->RTS_Status &= ~RTS_OFF_STATUS;
					if (MDM_OldRtsStatus == 0) {
						/* modeminternaltable_ptr->RTS_Status &= ~RTS_OFF_STATUS; */
					}
					else {
						modeminternaltable_ptr->RTS_Status |= RTS_ON_STATUS;
					}
					MDM_StatusChanged = TRUE;
				}

				/* ＦＥＤビットのチェック */
				MDM_NewFedStatus = (UBYTE)(MDM_REG_0F_PortStatus & IO_BIT_FED);
				if (MDM_NewFedStatus != MDM_OldFedStatus) {
					MDM_OldFedStatus = MDM_NewFedStatus;
					modeminternaltable_ptr->FED_Status &= ~FED_OFF_STATUS;
					if (MDM_OldFedStatus == 0) {
						/* modeminternaltable_ptr->FED_Status &= ~FED_OFF_STATUS; */
					}
					else {
						modeminternaltable_ptr->FED_Status |= FED_ON_STATUS;
					}
					MDM_StatusChanged = TRUE;
				}

				/* ＰＮＤＥＴビットのチェック */
				MDM_NewPndetStatus = (UBYTE)(inp(MDM_REG_0D_PORT) & IO_BIT_PNDET);
				if (MDM_NewPndetStatus != MDM_OldPndetStatus) {
					MDM_OldPndetStatus = MDM_NewPndetStatus;
					modeminternaltable_ptr->PNDET_Status &= ~PNDET_OFF_STATUS;
					if (MDM_OldPndetStatus == 0) {
						/* modeminternaltable_ptr->PNDET_Status &= ~PNDET_OFF_STATUS; */
					}
					else {
						modeminternaltable_ptr->PNDET_Status |= PNDET_ON_STATUS;
					}
					MDM_StatusChanged = TRUE;
				}

				/* ＰＮＳＵＣビットのチェック */
				/* MDM_NewPnsucStatus = (UBYTE)(inp(MDM_REG_0A_PORT) & IO_BIT_PNSUC); */
				read_reg = inp(MDM_REG_0A_PORT); /* Changed by H.Kubo 1997/08/28 */
				MDM_NewPnsucStatus = read_reg & IO_BIT_PNSUC;
				if (MDM_NewPnsucStatus != MDM_OldPnsucStatus) {
					MDM_OldPnsucStatus = MDM_NewPnsucStatus;
					modeminternaltable_ptr->PNSUC_Status &= ~PNSUC_OFF_STATUS;
					if (MDM_OldPnsucStatus == 0) {
						/* modeminternaltable_ptr->PNSUC_Status &= ~PNSUC_OFF_STATUS; */

						if (CL1_RLSD_TurnOff == 0) {
							CL1_PNSUC_TurnOff = 1;	/*  By O.Kimoto 1997/05/16 */
						}
					}
					else {
						modeminternaltable_ptr->PNSUC_Status |= PNSUC_ON_STATUS;
						CL1_PNSUC_TurnOff = 0;	/*  By O.Kimoto 1997/05/16 */
					}
					MDM_StatusChanged = TRUE;
				}
				/* ＦＥビットのチェック */
				MDM_NewFeStatus = read_reg & IO_BIT_FE; /*read_reg = inp(MDM_REG_0A_PORT);*/
				if (MDM_NewFeStatus != MDM_OldFeStatus) {
					MDM_OldFeStatus = MDM_NewFeStatus;
					if (MDM_NewFeStatus) {
						CL1_HDLC_AbortSequence = 1;
					}
					else {
						CL1_HDLC_AbortSequence = 0;
					}
					MDM_StatusChanged = TRUE;
				}

				/* ＤＭＹ４のチェック */
				/** とりあえず、ＦＬＡＧＤＴのチェックを入れておきます。 */
				/* change FLAGDT -> SYNCD 1997/01/16 Y.Murata */
				/* やっぱりFLAGDTにします 1997/01/28 Y.Murata */
				MDM_NewDmy4Status = (UBYTE)(inp(MDM_REG_0A_PORT) & IO_BIT_FLAGDT);
				if (MDM_NewDmy4Status != MDM_OldDmy4Status) {
					MDM_OldDmy4Status = MDM_NewDmy4Status;
					modeminternaltable_ptr->DMY4_Status &= ~DMY4_OFF_STATUS;
					if (MDM_OldDmy4Status == 0) {
						/* modeminternaltable_ptr->DMY4_Status &= ~DMY4_OFF_STATUS; */

						/* Class1で、高速受信から抜けない時が有るので、FLAGDTの検出をします。 By O.Kimoto 1997/05/24 */
						CL1_FLAGDT_Found = 0;	/*  By O.Kimoto 1997/05/16 */

					}
					else {
						modeminternaltable_ptr->DMY4_Status |= DMY4_ON_STATUS;

						/* Class1で、高速受信から抜けない時が有るので、FLAGDTの検出をします。 By O.Kimoto 1997/05/24 */
						if ((CL1_PNSUC_TurnOff == 0) && (CL1_RLSD_TurnOff == 0)) {
							CL1_FLAGDT_Found = 1;	/*  By O.Kimoto 1997/05/16 */
						}

					}
					MDM_StatusChanged = TRUE;
				}

				/* ＡＢＣＯＤＥレジスターの読み出し処理 */
				temp_abort_code = inp(MDM_REG_14_PORT);
				if (temp_abort_code != 0x00) {
					MDM_AbortCode = temp_abort_code;
					MDM_InternalStatus[0].Rx_Phase = MDM_AbortCode;	/* Add By O.Kimoto 1996/10/24 */
					modeminternaltable_ptr->AbortCode = MDM_AbortCode;
					outp(MDM_REG_14_PORT,0x00);
					return_value |= MDM_EVT_ABORT_CODE_DETECT_BIT;

					switch(MDM_AbortCode) {
					case 0x25:	/* timeout waiting for probing cut-off tone */
					case 0x2A:	/* checksum error in INFO1 */
					case 0x2B:	/* found tone before INFO0 */
						/* 本当はここでＮＥＷＣをしばきたい */
						break;
					case 0x91:	/* error in first CC train */
					case 0xC7:	/* training on TRN failed */
						MDM_RetrainFirstCCTrainFlag = 1;
						/* もしかすると、ＮＥＷＣが必要かもしれない */
						break;
					case 0x92:	/* time out waiting for PPh */
					case 0x94:	/* time out waiting for ALT */
					case 0x95:	/* Found ACh */
					case 0xD6:	/* Timed out waiting for MPh */	/* Add test By O.Kimoto 1996/10/24 */
					case 0xD8:	/* Timed out waiting for E */	/* Add test By O.Kimoto 1996/10/24 */
						ControlChannelRetrainFlag = 1;
						return_value |= MDM_EVT_CC_RETRAIN_DETECT_BIT;
						MDM_NewT30Status = MODE_CC_RETRAIN;
						break;
					case 0x96:	/* FED off during CC data */
					case 0xDB:	/* Time out in transmitter MPh *//* add test By O.Kimoto 1996/10/17 */
						MDM_FedOffFlag = 1;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/10 */
						break;
					}
				}

				/* Ｔ３０Ｓｔａｔｕｓのチェック */
				if (MDM_NewT30Status != MDM_OldT30Status) {
					MDM_OldT30Status = MDM_NewT30Status;
					modeminternaltable_ptr->T30Status = MDM_NewT30Status;
					MDM_StatusChanged = TRUE;
				}

				if (MDM_StatusChanged == TRUE) {
					modeminternaltable_ptr->Timer = MDM_ModemInternalStatusTimer;
					MDM_ModemInternalStatusCounter++;

					/* モデムステータスバッファをリングで使います。 By O.Kimoto 1996/09/20 */
					if (MDM_ModemInternalStatusCounter >= MODEM_STATUS_TABLE_MAX) {
						MDM_ModemInternalStatusCounter = 1;
					}

				}

				MDM_ModemInternalStatusTimer ++;
			}

			/* チャンネル切り替え時のキャリア断検出処理
			** 本来はタスクにしたいところですが、桐＋では時期的に
			** 間に合いませんので割り込み処理としておきます。
			** 杏以降はタスクにします。
			** By O.Kimoto 1996/09/10
			*/
			if ((MDM_CarrierDropoutFlag != 0xFF)) {
				if (!(inp(MDM_REG_0F_PORT) & IO_BIT_FED)) {
					MDM_CarrierDropoutTimer ++;
					if (MDM_CarrierDropoutTimer >= (UWORD)(6000/10)) {
						MDM_CarrierDropoutFlag = 1;
						MDM_FedOffFlag = 2;		/* コントロールチャンネル中にＦＥＤがＯＦＦしたかどうかを示すフラグ By O.Kimoto 1996/09/20 */
					}
				}
				else {
					MDM_CarrierDropoutTimer = 0;
				}
			}

			/* 受信レベルの測定 1997/01/28 Y.Murata */
			if (SYS_V34ProcedureExecuting() == 0) {	/** 従来のプロトコルならば **/
				if (MDM_V21MeasureStartGo) {
					if (MDM_V21MeasureStartGo == 1) {
						if ((MDM_GetIO(POS_SYNCD)) && (MDM_GetIO(POS_RLSD))) {
							MDM_V21MeasureStartGo = 2;
						}
					}
					else {
						MDM_V21MeasureStartGo++;
						if (MDM_V21MeasureStartGo > 82) {	/* 800ms */
							MDM_V21MeasureStartGo = 0;
							MDM_RecoverStatus |= MDM_EVT_RTH_CHANGE;	/* Add By O.Kimoto 1998/02/03 */
						}
					}
				}
			}

			/* Ported from Clover\src\int_time.asm by H.Kubo 1997/09/05 */
			if (return_value & MDM_EVT_CC_RETRAIN_DETECT_BIT ) {
				det_evt(EVT_MDM_CC_RETRAIN);
			}
			if (return_value & MDM_EVT_MDM_TURNOFF_BIT) {
				det_evt(EVT_MDM_TURNOFF);
			}
			if (return_value & MDM_EVT_ABORT_CODE_DETECT_BIT ) {
				det_evt(EVT_MDM_ABCODE);
			}
		}
	}
}

UBYTE	MDM_CHK_InternalStatus(void)
{
	if (SYB_MaintenanceSwitch[12] & 0x02) {
		return(0);
	}
	return(1);
}

#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* added by H.Kubo 1998/11/11 */
/*************************************************************************
	module		:[モデム割込み要求ステータスの検査]
	function	:[
		モデムステータスを呼んで、割り込み要求中か判断。
	]
	return		:[]
	common		:[
		MDM_REG_1E_PortStatus
		MDM_REG_1F_PortStatus
	]
	condition	:[
		割込み禁止状態で呼んでください。
	]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void MDM_ModemRecoverTask(void){}]
	date		:[1998/11/11]
	author		:[久保博]
*************************************************************************/
UBYTE MDM_IsModemRequestingInterrupt(void)
{
	MDM_REG_1E_PortStatus = inp(MDM_REG_1E_PORT);
	MDM_REG_1F_PortStatus = inp(MDM_REG_1F_PORT);
	if ((MDM_REG_1E_PortStatus & (IO_BIT_RDBIA | IO_BIT_TDBIA)) 
	|| (MDM_REG_1F_PortStatus & (IO_BIT_NCIA | IO_BIT_NSIA)) ) {
		return TRUE;
	}
	return FALSE;
}


/*************************************************************************
	module		:[モデム割込み補完]
	function	:[
		モデムが割込み要求ステータスを立てているのに、割り込みがかからない場合、代わりに割り込み処理をする
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MDM]
	ProtoType	:[void MDM_ModemRecoverTask(void){}]
	date		:[1998/11/11]
	author		:[久保博]
*************************************************************************/
void MDM_ModemInterruptComplement(void)
{
	CMN_DisableInterrupt();
	if (MDM_IsModemRequestingInterrupt()) {
		MDM_ModemInterrupt();
	}
	CMN_EnableInterrupt();
}
#endif
