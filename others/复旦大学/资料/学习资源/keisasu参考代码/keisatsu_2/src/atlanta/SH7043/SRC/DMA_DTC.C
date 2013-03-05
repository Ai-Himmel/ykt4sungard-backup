/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : dma_dtc.c                                                */
/*  作成者       : 野瀬                                                     */
/*  日  付       : 1996/12/17                                               */
/*  概  要       : SH7043内蔵DTCの各種設定を行う為の関数群                  */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\dma_blk.h"
/* #include "\src\atlanta\define\dma_def.h" */
#include "\src\atlanta\ext_v\dma_data.h"
#include "\src\atlanta\sh7043\define\sh_sys.h"

#if (PRO_MODEM == R288F) /* Added by H.Kubo 1998/06/29 */
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
#include "\src\atlanta\mdm\fm336\define\mdm_pro.h"
#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
 #else
#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
#include "\src\atlanta\mdm\r288f\define\mdm_pro.h"
#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif
#if defined(POPLAR_F)
#else
	#if (PRO_DTC_INT_TYPE != DTC_INT_HINOKI)
	#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
	#include "\src\atlanta\prt\thermal\define\prn_def.h"
	#endif
#endif
/* debug */
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1998/06/29 */
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
#endif

#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\sakaki\ext_v\dcp_data.h"
#include "\src\atlanta\sakaki\ext_v\ga_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_c.h" /* added by H.Kubo 1999/01/13 */
#endif

#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
#include "\src\atlanta\ext_v\cl1_data.h"
#include "\src\atlanta\define\mntsw_g.h"
#include "\src\atlanta\ext_v\bkupram.h"
#endif

#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)
#include "\src\atlanta\ext_v\sys_data.h"
 #if defined(SATSUKI2) || defined(STOCKHM2)
#include "\src\atlanta\sh7043\define\sh_port.h"
 #else
#include "\src\atlanta\hinoki\define\hinoport.h"
 #endif
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
 #if defined(STOCKHM2)
#include "\src\atlanta\prt\lv_therm\ext_v\prt_data.h"
 #else
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
 #endif
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_h.h"
#endif

#if defined (KEISATSU) /* 警察FAX 05/06/20 石橋正和 */
#include "\src\atlanta\ext_v\fcm_data.h"
#endif

void SaveReturnAddressAndJumpBegin(void);
void MDM_ModemDMA_TC_Interrupt(void);

/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.ブロック転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetupDTC(struct DMA_DTC_Data_t *setup)
{
#if 1 /* (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) */	/* 2002/12/11 T.Takagi */
/* DTC Address Error のビットが立っていた場合、二度とDTCが起動されないので、ここで落とす */
	if ((SH__DTCSR & DTCSR_AE) == DTCSR_AE) {
		SH__DTCSR &= ~DTCSR_AE;
	}
#endif
	switch (setup->DTC_Mode) {
	case	DTC_INTERRUPT_CH:
		DMA_SetupIntDTC(setup);	/* 割り込みを起動要因 */
		break;
	case	DTC_BLOCK_MODE:
		DMA_SetupBlockDTC(setup);	/* ソフト起動要因 */
		break;
	case	DTC_NORMAL_MODE:
		DMA_SetupNormalDTC(setup);	/* ソフト起動要因 */
		break;
	case	DTC_REPEAT_MODE:
		DMA_SetupRepeatDTC(setup);	/* ソフト起動要因 */
		break;
	case	DTC_INTERRUPT_CH2:
		DMA_SetupIntDTC2(setup);	/* 割り込みを起動要因 */
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case	DTC_INTERRUPT_IRQ0:
	case	DTC_INTERRUPT_IRQ1:
	case	DTC_INTERRUPT_IRQ2:
	case	DTC_INTERRUPT_IRQ3:
	case	DTC_INTERRUPT_IRQ4:
	case	DTC_INTERRUPT_IRQ5:
	case	DTC_INTERRUPT_IRQ6:
	case	DTC_INTERRUPT_IRQ7:
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case	DTC_INTERRUPT_RXI1:
	case	DTC_INTERRUPT_TXI1:
 #endif
		DMA_SetupIntDTC_IRQ(setup);	/* 割り込みを起動要因 */
		break;
#endif
	}
}

/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.モデムＤＲＥＱ割り込みでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[山口哲治]
*************************************************************************/
void DMA_SetupIntDTC(struct DMA_DTC_Data_t *setup)
{
	UDWORD address;
	
	/* モードレジスタ情報の設定
	** ソースアドレス増加
	** ノーマル転送モード
	** デスティネーション側ブロック領域
	** １ブロック転送終了で割込み発生
	** インタラプトセレクト
	** データ転送継続
	*/
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/10/09 */
	if (setup->SrcAddress == MDM_ADDRESS) {
		/** ソースアドレス固定,デスティネーションアドレス増加 */
		DTC_INT_NORMAL.DTMR_Status = (0 | DTMR_DM_INC );
	}
	else if (setup->DstAddress == MDM_ADDRESS) {
		/** ソースアドレス増加,デスティネーションアドレス固定 */
		DTC_INT_NORMAL.DTMR_Status = (0 | DTMR_SM_INC );
	}
#endif /* (PRO_MODEM == ORANGE3) */

	switch (setup->Unit) {
	case DMA_BYTE_TRANSFER: /* バイト転送 */
		/* 初期設定値なので何もしない */
		break;
	case DMA_WORD_TRANSFER: /* ワード転送 */
		DTC_INT_NORMAL.DTMR_Status |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER: /* ロング転送 */
		DTC_INT_NORMAL.DTMR_Status |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	/* カウントレジスタ情報の設定 */
	DTC_INT_NORMAL.DTCRA_Status = setup->Counter;

	/* ブロック長レジスタ情報の設定 ﾉｰﾏﾙﾓｰﾄﾞはない */
	/* DTC_INT_NORMAL.DTCRB_Status = setup->Length; */

	/* 転送元アドレスレジスタ情報の設定 */
	DTC_INT_NORMAL.DTSAR_Status = setup->SrcAddress;

	/* 転送先アドレスレジスタ情報の設定 */
	DTC_INT_NORMAL.DTDAR_Status = setup->DstAddress;

	/* ＤＴＣ情報ベースレジスタの設定 */
	address = (UDWORD)(&DTC_INT_NORMAL);
	SH__DTBR = (UWORD)(address >> 16);
}

/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.ブロック転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetupBlockDTC(struct DMA_DTC_Data_t *setup)
{
	UDWORD address;

	/* モードレジスタ情報の設定
	** ソースアドレス増加
	** デスティネーションアドレス増加
	** ブロック転送モード
	** デスティネーション側ブロック領域
	** １ブロック転送終了で割込み発生
	*/
	DTC_BLOCK.DTMR_Status = (0 | DTMR_SM_INC | DTMR_DM_INC | DTMR_MD_BLOCK | DTMR_DISEL_SET);
	switch (setup->Unit) {
	case DMA_BYTE_TRANSFER: /* バイト転送 */
		/* 初期設定値なので何もしない */
		break;
	case DMA_WORD_TRANSFER: /* ワード転送 */
		DTC_BLOCK.DTMR_Status |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER: /* ロング転送 */
		DTC_BLOCK.DTMR_Status |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	/* カウントレジスタ情報の設定 */
	DTC_BLOCK.DTCRA_Status = setup->Counter;

	/* ブロック長レジスタ情報の設定 */
	DTC_BLOCK.DTCRB_Status = setup->Length;

	/* 転送元アドレスレジスタ情報の設定 */
	DTC_BLOCK.DTSAR_Status = setup->SrcAddress;

	/* 転送先アドレスレジスタ情報の設定 */
	DTC_BLOCK.DTDAR_Status = setup->DstAddress;

	/* ＤＴＣ情報ベースレジスタの設定 */
	address = (UDWORD)(&DTC_BLOCK);
	SH__DTBR = (UWORD)(address >> 16);

}

/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.ノーマル転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[山口哲治]
*************************************************************************/
void DMA_SetupNormalDTC(struct DMA_DTC_Data_t *setup)
{
	UDWORD address;

	/* モードレジスタ情報の設定
	** ソースアドレス増加
	** デスティネーションアドレス増加
	** ノーマル転送モード
	** 転送終了で割込み発生
	** インタラプトセレクト
	*/
	DTC_BLOCK.DTMR_Status = (0 | DTMR_SM_INC | DTMR_DM_INC | DTMR_DISEL_SET);
	switch (setup->Unit) {
	case DMA_BYTE_TRANSFER: /* バイト転送 */
		/* 初期設定値なので何もしない */
		break;
	case DMA_WORD_TRANSFER: /* ワード転送 */
		DTC_NORMAL.DTMR_Status |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER: /* ロング転送 */
		DTC_NORMAL.DTMR_Status |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	/* カウントレジスタ情報の設定 */
	DTC_NORMAL.DTCRA_Status = setup->Counter;

	/* ブロック長レジスタ情報の設定 */
	/* DTC_NORMAL.DTCRB_Status = setup->Length; */

	/* 転送元アドレスレジスタ情報の設定 */
	DTC_NORMAL.DTSAR_Status = setup->SrcAddress;

	/* 転送先アドレスレジスタ情報の設定 */
	DTC_NORMAL.DTDAR_Status = setup->DstAddress;

	/* ＤＴＣ情報ベースレジスタの設定 */
	address = (UDWORD)(&DTC_NORMAL);
	SH__DTBR = (UWORD)(address >> 16);

}

/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.リピート転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[山口哲治]
*************************************************************************/
void DMA_SetupRepeatDTC(struct DMA_DTC_Data_t *setup)
{
	UDWORD address;

	/* モードレジスタ情報の設定
	** ソースアドレス増加
	** デスティネーションアドレス増加
	** リピート転送モード
	** 転送終了で割込み発生
	*/
	DTC_REPEAT.DTMR_Status = (0 | DTMR_SM_INC | DTMR_DM_INC | DTMR_MD_REPEAT | DTMR_DISEL_SET);
	switch (setup->Unit) {
	case DMA_BYTE_TRANSFER: /* バイト転送 */
		/* 初期設定値なので何もしない */
		break;
	case DMA_WORD_TRANSFER: /* ワード転送 */
		DTC_REPEAT.DTMR_Status |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER: /* ロング転送 */
		DTC_REPEAT.DTMR_Status |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	/* カウントレジスタ情報の設定 */
	DTC_REPEAT.DTCRA_Status = setup->Counter;

	/* 初期アドレスレジスタ情報の設定 */
	DTC_REPEAT.DTIAR_Status = setup->SrcAddress;

	/* 転送元アドレスレジスタ情報の設定 */
	DTC_REPEAT.DTSAR_Status = setup->SrcAddress;

	/* 転送先アドレスレジスタ情報の設定 */
	DTC_REPEAT.DTDAR_Status = setup->DstAddress;

	/* ＤＴＣ情報ベースレジスタの設定 */
	address = (UDWORD)(&DTC_REPEAT);
	SH__DTBR = (UWORD)(address >> 16);

}

/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.ＭＰＳＣのＤＲＥＱ起動でノーマル転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[山口哲治]
*************************************************************************/
void DMA_SetupIntDTC2(struct DMA_DTC_Data_t *setup)
{
	UDWORD address;
		
	/* モードレジスタ情報の設定
	** ノーマル転送モード
	** 転送終了で割込み発生
	** インタラプトセレクト
	*/
	if (setup->SrcAddress == RS_ADDRESS) {
		/** ソースアドレス固定,デスティネーションアドレス増加 */
		DTC_INT_NORMAL2.DTMR_Status = (0 | DTMR_DM_INC );
	}
	else if (setup->DstAddress == RS_ADDRESS) {
		/** ソースアドレス増加,デスティネーションアドレス固定 */
		DTC_INT_NORMAL2.DTMR_Status = (0 | DTMR_SM_INC );
	}
	switch (setup->Unit) {
	case DMA_BYTE_TRANSFER: /* バイト転送 */
		/* 初期設定値なので何もしない */
		break;
	case DMA_WORD_TRANSFER: /* ワード転送 */
		DTC_INT_NORMAL2.DTMR_Status |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER: /* ロング転送 */
		DTC_INT_NORMAL2.DTMR_Status |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	/* カウントレジスタ情報の設定 */
	DTC_INT_NORMAL2.DTCRA_Status = setup->Counter;

	/* ブロック長レジスタ情報の設定 ﾉｰﾏﾙﾓｰﾄﾞはない */
	/* DTC_INT_NORMAL2.DTCRB_Status = setup->Length; */

	/* 転送元アドレスレジスタ情報の設定 */
	DTC_INT_NORMAL2.DTSAR_Status = setup->SrcAddress;

	/* 転送先アドレスレジスタ情報の設定 */
	DTC_INT_NORMAL2.DTDAR_Status = setup->DstAddress;

	/* ＤＴＣ情報ベースレジスタの設定 */
	address = (UDWORD)(&DTC_INT_NORMAL2);
	SH__DTBR = (UWORD)(address >> 16);

}

/*************************************************************************
	module		:[SH7043内蔵DTCの転送スタート]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[
		１ブロックの転送が終了するまでＰＣは停止します。
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[野瀬敏弘]
*************************************************************************/
static UBYTE DMA_DTC_DummyVer[2];
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
#include "\src\atlanta\ext_v\sys_port.h"
CONST UBYTE R288f_dtc_int_edge = 0;

#endif

void DMA_DTC_TransferStart(UBYTE mode)
{

	switch (mode) {
	case DTC_BLOCK_MODE:
		while (DTC_BLOCK.DTCRA_Status) {
			/* 転送開始
			** ベクタアドレスは H'442
			*/
			SH__DTCSR &= ~DTCSR_SWDTE;
			SH__DTCSR = 0x0042;			/* ベクタオフセット加算 */
			SH__DTCSR |= DTCSR_SWDTE;	/* スタート */
			/* DTCSR のソフトウェア起動ビットをＯＮして DTCSRをリードするまでの間に
			** アセンブラレベルで少なくとも２命令を置かないと実際に転送終了した後の
			** DTCSRをリードできないのでダミーのライトを入れます。
			** T.Nose 1997/09/30
			*/
			DMA_DTC_DummyVer[0] = 0;
			DMA_DTC_DummyVer[1] = 0;
		}
		break;
	case DTC_NORMAL_MODE:
		while (DTC_NORMAL.DTCRA_Status) {
			/* 転送開始
			** ベクタアドレスは H'444
			*/
			SH__DTCSR &= ~DTCSR_SWDTE;
			SH__DTCSR = 0x0044;			/* ベクタオフセット加算 */
			SH__DTCSR |= DTCSR_SWDTE;	/* スタート */
			/* DTCSR のソフトウェア起動ビットをＯＮして DTCSRをリードするまでの間に
			** アセンブラレベルで少なくとも２命令を置かないと実際に転送終了した後の
			** DTCSRをリードできないのでダミーのライトを入れます。
			** T.Nose 1997/09/30
			*/
			DMA_DTC_DummyVer[0] = 0;
			DMA_DTC_DummyVer[1] = 0;
		}
		break;
	case DTC_REPEAT_MODE:
		while (DTC_REPEAT.DTCRA_Status) {
			/* 転送開始
			** ベクタアドレスは H'446
			*/
			SH__DTCSR &= ~DTCSR_SWDTE;
			SH__DTCSR = 0x0046;			/* ベクタオフセット加算 */
			SH__DTCSR |= DTCSR_SWDTE;	/* スタート */
			/* DTCSR のソフトウェア起動ビットをＯＮして DTCSRをリードするまでの間に
			** アセンブラレベルで少なくとも２命令を置かないと実際に転送終了した後の
			** DTCSRをリードできないのでダミーのライトを入れます。
			** T.Nose 1997/09/30
			*/
			DMA_DTC_DummyVer[0] = 0;
			DMA_DTC_DummyVer[1] = 0;
		}
		break;
	case DTC_INTERRUPT_CH:
		/* 転送開始
		** ベクタアドレスは H'42E	IRQ5
		*/
		SH__DTEC &= ~IREQ5_ENABLE;
		SH__DTEC |= IREQ5_ENABLE;	/* スタート */
		SH__IPRB |= IRQ5_LEVEL;		/* IRQ5マスク解除 1997/08/05  By T.Yamaguchi */
		break;
	case DTC_INTERRUPT_CH2:
		/* 転送開始
		** ベクタアドレスは H'430	IRQ6
		*/
		SH__DTED &= ~IREQ6_ENABLE;
		SH__DTED |= IREQ6_ENABLE;	/* スタート */
		SH__IPRB |= IRQ6_LEVEL;		/* IRQ5マスク解除 1997/08/05  By T.Yamaguchi */
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		SH__DTEC &= ~IREQ0_ENABLE;
		SH__DTEC |= IREQ0_ENABLE;	/* スタート */
		SH__IPRA |= IRQ0_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ1:
		SH__DTEC &= ~IREQ1_ENABLE;
		SH__DTEC |= IREQ1_ENABLE;	/* スタート */
		SH__IPRA |= IRQ1_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ2:
		SH__DTEC &= ~IREQ2_ENABLE;
		SH__DTEC |= IREQ2_ENABLE;	/* スタート */
		SH__IPRA |= IRQ2_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ3:
		SH__DTEC &= ~IREQ3_ENABLE;
		SH__DTEC |= IREQ3_ENABLE;	/* スタート */
		SH__IPRA |= IRQ3_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ4:
		SH__DTEC &= ~IREQ4_ENABLE;
		SH__DTEC |= IREQ4_ENABLE;	/* スタート */
		SH__IPRB |= IRQ4_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ5:
		SH__DTEC &= ~IREQ5_ENABLE;
		SH__DTEC |= IREQ5_ENABLE;	/* スタート */
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
		if (R288f_dtc_int_edge) {	/* IRQ05マスク解除 */
			SH__IPRB |= IRQ5_LEVEL;		/* SH IRQ5 割込み優先順位設定。 */
			SYS_MCR_PortStatus &= ~IO_BIT_INTSEL; /* MD9805 エッジ検出 */
			outpw(MCR_PORT,SYS_MCR_PortStatus);
		}
		else {
			SH__IPRB |= IRQ5_LEVEL;		/* IRQ05マスク解除 */
		}
		outp(0x00C30201, 0x0); /* DTC 起動用IRQ をクリア by H.Kubo 1998/07/21 */

		SYS_MCR_PortStatus &= ~IO_BIT_MREQ5; /* DTC 転送要求のマスクを解除します。added by H.Kubo 1998/10/27 */
		outpw(MCR_PORT, SYS_MCR_PortStatus);
#else
		SH__IPRB |= IRQ5_LEVEL;		/* IRQ05マスク解除 */
#endif
		break;
	case DTC_INTERRUPT_IRQ6:
		SH__DTED &= ~IREQ6_ENABLE;
		SH__DTED |= IREQ6_ENABLE;	/* スタート */
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
		if (R288f_dtc_int_edge) {	/* IRQ05マスク解除 */
			SH__IPRB |= IRQ6_LEVEL;		/* SH IRQ5 割込み優先順位設定。 */
			SYS_MCR_PortStatus &= ~IO_BIT_INTSEL; /* MD9805 エッジ検出 */
			outpw(MCR_PORT,SYS_MCR_PortStatus);
		}
		else {
			SH__IPRB |= IRQ6_LEVEL;		/* IRQ06マスク解除 */
		}
		outp(0x00C40001, 0x0); /* DTC 割り込みクリア by H.Kubo 1998/07/21 */

		SYS_MCR_PortStatus &= ~IO_BIT_MREQ6; /* DTC 転送要求のマスクを解除します。added by H.Kubo 1998/10/27 */
		outpw(MCR_PORT, SYS_MCR_PortStatus);
#else
		SH__IPRB |= IRQ6_LEVEL;		/* IRQ06マスク解除 */
#endif
		break;
	case DTC_INTERRUPT_IRQ7:
		SH__DTED &= ~IREQ7_ENABLE;
		SH__DTED |= IREQ7_ENABLE;	/* スタート */
		SH__IPRB |= IRQ7_LEVEL;		/* IRQ05マスク解除 */
		break;
#endif
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		SH__DTED &= ~RXI1_ENABLE;
		SH__DTED |= RXI1_ENABLE;	/* スタート */
		/* SH__IPRF |= SCI1_LEVEL;		@* SCI1マスク解除 */
		break;
	case DTC_INTERRUPT_TXI1:
		SH__DTED &= ~TXI1_ENABLE;
		SH__DTED |= TXI1_ENABLE;	/* スタート */
		/* SH__IPRF |= SCI1_LEVEL;		@* SCI1マスク解除 */
		break;
#endif
	}
}

/*************************************************************************
	module		:[SH7043内蔵DTCの転送回数を読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/22]
	author		:[山口哲治]
*************************************************************************/
UWORD DMA_DTC_CheckCounter(UBYTE channel)
{
	UWORD count;

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		count = DTC_INT_NORMAL.DTCRA_Status;
		break;
	case DTC_BLOCK_MODE:
		count = DTC_BLOCK.DTCRA_Status;
		break;
	case DTC_NORMAL_MODE:
		count = DTC_BLOCK.DTCRA_Status;
		break;
	case DTC_REPEAT_MODE:
		count = DTC_REPEAT.DTCRA_Status;
		break;
	case DTC_INTERRUPT_CH2:
		count = DTC_INT_NORMAL2.DTCRA_Status;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		count = DTC_INT_NORMAL_IRQ0.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ1:
		count = DTC_INT_NORMAL_IRQ1.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ2:
		count = DTC_INT_NORMAL_IRQ2.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ3:
		count = DTC_INT_NORMAL_IRQ3.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ4:
		count = DTC_INT_NORMAL_IRQ4.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ5:
		count = DTC_INT_NORMAL_IRQ5.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ6:
		count = DTC_INT_NORMAL_IRQ6.DTCRA_Status;
		break;
	case DTC_INTERRUPT_IRQ7:
		count = DTC_INT_NORMAL_IRQ7.DTCRA_Status;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		count = DTC_INT_NORMAL_RXI1.DTCRA_Status;
		break;
	case DTC_INTERRUPT_TXI1:
		count = DTC_INT_NORMAL_TXI1.DTCRA_Status;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(count);
}

/*************************************************************************
	module		:[SH7043内蔵DTCの現在の転送アドレスを読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/22]
	author		:[山口哲治]
*************************************************************************/
UDWORD DMA_DTC_CheckAddress(UBYTE channel, UBYTE direction)
{
	UDWORD address;

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		address = DMA_DTC_CheckDstAddress(channel);	/* DTCを使用する場合 */
		break;
	case DMA_MEMORY_TO_IO:
		address = DMA_DTC_CheckSrcAddress(channel);	/* DTCを使用する場合 */
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(address);
}

/*************************************************************************
	module		:[SH7043内蔵DTCの現在の転送アドレスを読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/22]
	author		:[山口哲治]
*************************************************************************/
UDWORD DMA_DTC_CheckDstAddress(UBYTE channel)
{
	UDWORD address;

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		address = DTC_INT_NORMAL.DTDAR_Status;
		break;
	case DTC_BLOCK_MODE:
		address = DTC_BLOCK.DTDAR_Status;
		break;
	case DTC_NORMAL_MODE:
		address = DTC_BLOCK.DTDAR_Status;
		break;
	case DTC_REPEAT_MODE:
		address = DTC_REPEAT.DTDAR_Status;
		break;
	case DTC_INTERRUPT_CH2:
		address = DTC_INT_NORMAL2.DTDAR_Status;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		address = DTC_INT_NORMAL_IRQ0.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ1:
		address = DTC_INT_NORMAL_IRQ1.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ2:
		address = DTC_INT_NORMAL_IRQ2.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ3:
		address = DTC_INT_NORMAL_IRQ3.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ4:
		address = DTC_INT_NORMAL_IRQ4.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ5:
		address = DTC_INT_NORMAL_IRQ5.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ6:
		address = DTC_INT_NORMAL_IRQ6.DTDAR_Status;
		break;
	case DTC_INTERRUPT_IRQ7:
		address = DTC_INT_NORMAL_IRQ7.DTDAR_Status;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		address = DTC_INT_NORMAL_RXI1.DTDAR_Status;
		break;
	case DTC_INTERRUPT_TXI1:
		address = DTC_INT_NORMAL_TXI1.DTDAR_Status;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(address);
}

/*************************************************************************
	module		:[SH7043内蔵DTCの現在の転送アドレスを読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/22]
	author		:[山口哲治]
*************************************************************************/
UDWORD DMA_DTC_CheckSrcAddress(UBYTE channel)
{
	UDWORD address;

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		address = DTC_INT_NORMAL.DTSAR_Status;
		break;
	case DTC_BLOCK_MODE:
		address = DTC_BLOCK.DTSAR_Status;
		break;
	case DTC_NORMAL_MODE:
		address = DTC_BLOCK.DTSAR_Status;
		break;
	case DTC_REPEAT_MODE:
		address = DTC_REPEAT.DTSAR_Status;
		break;
	case DTC_INTERRUPT_CH2:
		address = DTC_INT_NORMAL2.DTSAR_Status;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		address = DTC_INT_NORMAL_IRQ0.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ1:
		address = DTC_INT_NORMAL_IRQ1.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ2:
		address = DTC_INT_NORMAL_IRQ2.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ3:
		address = DTC_INT_NORMAL_IRQ3.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ4:
		address = DTC_INT_NORMAL_IRQ4.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ5:
		address = DTC_INT_NORMAL_IRQ5.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ6:
		address = DTC_INT_NORMAL_IRQ6.DTSAR_Status;
		break;
	case DTC_INTERRUPT_IRQ7:
		address = DTC_INT_NORMAL_IRQ7.DTSAR_Status;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		address = DTC_INT_NORMAL_RXI1.DTSAR_Status;
		break;
	case DTC_INTERRUPT_TXI1:
		address = DTC_INT_NORMAL_TXI1.DTSAR_Status;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}

	return(address);
}



/*************************************************************************
	module		:[SH7043内蔵DTCの転送ブロック長読み出し]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[野瀬敏弘]
*************************************************************************/
UWORD DMA_DTC_CheckDTCRB(void)
{
	return(DTC_BLOCK.DTCRB_Status);
}

/*************************************************************************
	module		:[SH7043内蔵DTCの初期アドレス読み出し]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/20]
	author		:[野瀬敏弘]
*************************************************************************/
UDWORD DMA_DTC_CheckDTIAR(void)
{
	return(DTC_REPEAT.DTIAR_Status);
}


/*************************************************************************
	module		:[SH7043内蔵DTCの割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/12/25]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)
/* プリント中ループ調査用Debug Program */
UWORD DTCSR_Status = 0;
UWORD DTCSR_count = 0;
#endif

void DMA_DTC_Interrupt(void)
{
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)
	/* プリント中ループ調査用Debug Program */
	DTCSR_Status = SH__DTCSR;
	
	if ((DTCSR_Status & 0x0200) == 0x0200) {
		DTCSR_count++;
		DTCSR_count++;
		DTCSR_count++;
		DTCSR_count++;
	}
#endif

	SH__DTCSR &= ~DTCSR_SWDTE;

	/* デスティネーションアドレス情報を１ブロック分進める。*/
	switch (DTC_BLOCK.DTMR_Status & 0x0300) { /* D9,D8をマスク */
	case 0: /* バイト転送 */
		DTC_BLOCK.DTDAR_Status += (UDWORD)DTC_BLOCK.DTCRB_Status;
		break;
	case DTMR_SZ_WORD: /* ワード転送 */
		DTC_BLOCK.DTDAR_Status += (UDWORD)(DTC_BLOCK.DTCRB_Status * 2);
		break;
	case DTMR_SZ_DWORD: /* ロング転送 */
		DTC_BLOCK.DTDAR_Status += (UDWORD)(DTC_BLOCK.DTCRB_Status * 4);
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
}

/*************************************************************************
	module		:[SH7043内蔵DTCの終了割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[ＤＴＣの終了割り込みは、ＤＴＣを起動していない状態での
				  起動要因の割り込みで発生する]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/08/06]
	author		:[山口哲治]
*************************************************************************/
void DTC_TC_MDM_Interrupt(void)
{
#if (PRO_EXT_DMAC == DISABLE)	/* 1997/12/16 */
	DMA_DTC_RequestReqDisable();
#endif
	 SH__IPRB &= ~IRQ5_LEVEL;	/* IRQ5マスク 1997/08/05  By T.Yamaguchi */

	/* DMA終了割り込みを呼ぶ */
	MDM_ModemDMA_TC_Interrupt();

#if (PRO_EXT_DMAC == DISABLE)	/* 1997/12/16 */
	DMA_DTC_RequestReqEnable();
#endif
}

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
/*************************************************************************
	module		:[ＤＭＡのｾｯﾄｱｯﾌﾟ時の変数からDTC用の変数に変換して
				SH7043内蔵DTCのセットアップを起動]
	function	:[
		1.ブロック転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/08]
	author		:[山口 哲治/吉川弘康]
*************************************************************************/
void DMAtoDTC_SetupDTC(struct DMA_Data_t *dma_setup_data)	/* SAKAKI 用 */
{
	struct DMA_DTC_Data_t dma_setup;
	
	dma_setup.Unit = dma_setup_data->Unit;
/*	dma_setup.DTC_Mode = dma_setup_data->Channel;	1998/06/17 */
	dma_setup.Counter = dma_setup_data->Counter;
	dma_setup.Length = 1;	/*	ノーマルモードでは使わない */
	dma_setup.Direction = dma_setup_data->Direction;

	/*---------------------------------------------------------------------
	** DMAのChannelをDTCのModeに変換する。
	** DMAで使用するアドレスとDTCで使用するアドレスの指定方法が異なっているので、
	** その変換処理を行う。
	** この処理の中身は機種によって異なります。
	** 1998/06/17
	*/
	DMAtoDTC_Convert(&dma_setup, dma_setup_data);
	
	DMA_SetupDTC(&dma_setup);
	/* DMAtoDTC_RequsetEnable()でセットする */
	/* DMA_DTC_TransferStart(dma_setup.DTC_Mode); */
}

#else
/*************************************************************************
	module		:[ＤＭＡのｾｯﾄｱｯﾌﾟ時の変数からDTC用の変数に変換して
				SH7043内蔵DTCのセットアップを起動]
	function	:[
		1.ブロック転送モードでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/08]
	author		:[山口 哲治]
*************************************************************************/
void DMAtoDTC_SetupDTC(struct DMA_Data_t *dma_setup_data)
{
	struct DMA_DTC_Data_t dma_setup;
	
	dma_setup.Unit = dma_setup_data->Unit;
	dma_setup.DTC_Mode = dma_setup_data ->Channel;
	dma_setup.Counter = dma_setup_data->Counter;
	dma_setup.Length = 1;	/*	ノーマルモードでは使わない */
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/10/09 */
	switch (dma_setup_data->Direction) {
	case DMA_IO_TO_MEMORY:
		if (dma_setup_data ->Channel == DTC_INTERRUPT_CH) {
			dma_setup.SrcAddress = MDM_ADDRESS;
		}
		else if (dma_setup_data ->Channel == DTC_INTERRUPT_CH2) {
			dma_setup.SrcAddress = RS_ADDRESS;
		}
		dma_setup.DstAddress = dma_setup_data -> SrcAddress;
		break;
	case DMA_MEMORY_TO_IO:
		dma_setup.SrcAddress = dma_setup_data -> SrcAddress;
		if (dma_setup_data ->Channel == DTC_INTERRUPT_CH) {
			dma_setup.DstAddress = MDM_ADDRESS;
		}
		else if (dma_setup_data ->Channel == DTC_INTERRUPT_CH2) {
			dma_setup.DstAddress = RS_ADDRESS;
		}
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
#endif /* (PRO_MODEM == ORANGE3)  */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/10/09 */
	/* POPLAR_H では外付 DMAC があるため、モデムのデータ転送に DTC は
	** 使わないが、念のため入れておく。
	*/
	switch (dma_setup_data->Direction) {
	case DMA_IO_TO_MEMORY:
		if (dma_setup_data ->Channel == DTC_INTERRUPT_CH) {
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					dma_setup.SrcAddress = S1_HDLC_DATA_ADDRESS;
				}
				else {
					dma_setup.SrcAddress = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				dma_setup.SrcAddress = MDM_RX_ADDRESS;
			}
#else
			dma_setup.SrcAddress = MDM_RX_ADDRESS;
#endif
		}
		else if (dma_setup_data ->Channel == DTC_INTERRUPT_CH2) {
			dma_setup.SrcAddress = RS_ADDRESS;
		}
		dma_setup.DstAddress = dma_setup_data -> SrcAddress;
		break;
	case DMA_MEMORY_TO_IO:
		dma_setup.SrcAddress = dma_setup_data -> SrcAddress;
		if (dma_setup_data ->Channel == DTC_INTERRUPT_CH) {
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					dma_setup.DstAddress = S1_HDLC_DATA_ADDRESS;
				}
				else {
					dma_setup.DstAddress = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				dma_setup.DstAddress = MDM_TX_ADDRESS;
			}
#else
			dma_setup.DstAddress = MDM_TX_ADDRESS;
#endif
		}
		else if (dma_setup_data ->Channel == DTC_INTERRUPT_CH2) {
			dma_setup.DstAddress = RS_ADDRESS;
		}
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
#endif /* (PRO_MODEM == R288F) */
	DMA_SetupDTC(&dma_setup);
	/* DMAtoDTC_RequsetEnable()でセットする */
	/* DMA_DTC_TransferStart(dma_setup.DTC_Mode); */
}
#endif

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
/*************************************************************************
	module		:[ＤＭＡのｾｯﾄｱｯﾌﾟ時の変数からDTC用の変数に変換して
				SH7043内蔵DTCのセットアップを再起動]
	function	:[
		1.ＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/17]
	author		:[山口 哲治/吉川弘康]
*************************************************************************/
void DMAtoDTC_Restart(UBYTE dtc_mode,		/* DMAチャンネル */
					  UBYTE direction,	/* DMA転送方向 */
					  UWORD count,		/* DMA転送回数 */
					  UDWORD address)	/* DMAアドレス */		/* SAKAKI用 */
{
	
	struct DMA_Data_t dma_setup;
	struct DMA_DTC_Data_t dtc_setup;
	
	/*---------------------------------------------------------------------
	** DMAのChannelをDTCのModeに変換する。
	** DMAで使用するアドレスとDTCで使用するアドレスの指定方法が異なっているので、
	** その変換処理を行う。
	** この処理の中身は機種によって異なります。
	** 1998/06/17
	*/
	dma_setup.Channel = dtc_mode;
	dma_setup.Direction = direction;	/* 1998/08/13 H.Yoshikawa */
	dma_setup.SrcAddress = address;
	dma_setup.DstAddress = address;
	DMAtoDTC_Convert(&dtc_setup, &dma_setup);

	switch (dtc_setup.DTC_Mode) {
	case DTC_INTERRUPT_CH:
		/* カウントレジスタ情報の設定 */
		DTC_INT_NORMAL.DTCRA_Status = count;

		/* 転送元アドレスレジスタ情報の設定 */
		/* 転送先アドレスレジスタ情報の設定 */
		switch (direction) {
		case DMA_IO_TO_MEMORY:
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					DTC_INT_NORMAL.DTSAR_Status = S1_HDLC_DATA_ADDRESS;
				}
				else {
					DTC_INT_NORMAL.DTSAR_Status = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				DTC_INT_NORMAL.DTSAR_Status = MDM_RX_ADDRESS;
			}
#else
			DTC_INT_NORMAL.DTSAR_Status = MDM_RX_ADDRESS;
#endif
			DTC_INT_NORMAL.DTDAR_Status = address;
			break;
		case DMA_MEMORY_TO_IO:
			DTC_INT_NORMAL.DTSAR_Status = address;
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					DTC_INT_NORMAL.DTDAR_Status = S1_HDLC_DATA_ADDRESS;
				}
				else {
					DTC_INT_NORMAL.DTDAR_Status = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				DTC_INT_NORMAL.DTDAR_Status = MDM_TX_ADDRESS;
			}
#else
			DTC_INT_NORMAL.DTDAR_Status = MDM_TX_ADDRESS;
#endif
			break;
		}
		break;
	case DTC_INTERRUPT_CH2:
		/* カウントレジスタ情報の設定 */
		DTC_INT_NORMAL2.DTCRA_Status = count;

		/* 転送元アドレスレジスタ情報の設定 */
		/* 転送先アドレスレジスタ情報の設定 */
		switch (direction) {
		case DMA_IO_TO_MEMORY:
			DTC_INT_NORMAL2.DTSAR_Status = RS_ADDRESS;
			DTC_INT_NORMAL2.DTDAR_Status = address;
			break;
		case DMA_MEMORY_TO_IO:
			DTC_INT_NORMAL2.DTSAR_Status = address;
			DTC_INT_NORMAL2.DTDAR_Status = RS_ADDRESS;
			break;
		}
		break;
	case DTC_NORMAL_MODE:
	case DTC_BLOCK_MODE:
	case DTC_REPEAT_MODE:
	case DTC_INTERRUPT_IRQ0:
		DTC_INT_NORMAL_IRQ0.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ0.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ0.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ1:
		DTC_INT_NORMAL_IRQ1.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ1.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ1.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ2:
		DTC_INT_NORMAL_IRQ2.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ2.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ2.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ3:
		DTC_INT_NORMAL_IRQ3.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ3.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ3.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ4:
		DTC_INT_NORMAL_IRQ4.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ4.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ4.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ5:
		DTC_INT_NORMAL_IRQ5.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ5.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ5.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ6:
		DTC_INT_NORMAL_IRQ6.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ6.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ6.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_IRQ7:
		DTC_INT_NORMAL_IRQ7.DTCRA_Status = count;
		DTC_INT_NORMAL_IRQ7.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_IRQ7.DTDAR_Status = dtc_setup.DstAddress;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		DTC_INT_NORMAL_RXI1.DTCRA_Status = count;
		DTC_INT_NORMAL_RXI1.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_RXI1.DTDAR_Status = dtc_setup.DstAddress;
		break;
	case DTC_INTERRUPT_TXI1:
		DTC_INT_NORMAL_TXI1.DTCRA_Status = count;
		DTC_INT_NORMAL_TXI1.DTSAR_Status = dtc_setup.SrcAddress;
		DTC_INT_NORMAL_TXI1.DTDAR_Status = dtc_setup.DstAddress;
		break;
 #endif
	default:
		break;
	}
	DMA_DTC_TransferStart(dtc_setup.DTC_Mode);
}
#else	/* 1998/06/17 H.Yoshikawa */
/*************************************************************************
	module		:[ＤＭＡのｾｯﾄｱｯﾌﾟ時の変数からDTC用の変数に変換して
				SH7043内蔵DTCのセットアップを再起動]
	function	:[
		1.ＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/08]
	author		:[山口 哲治]
*************************************************************************/
void DMAtoDTC_Restart(UBYTE dtc_mode,		/* DMAチャンネル */
					  UBYTE direction,	/* DMA転送方向 */
					  UWORD count,		/* DMA転送回数 */
					  UDWORD address)	/* DMAアドレス */
{
#if (PRO_MODEM == ORANGE3) /* #if is added by H.Kubo 1997/10/09 */
	switch (dtc_mode) {
	case DTC_INTERRUPT_CH:
		/* カウントレジスタ情報の設定 */
		DTC_INT_NORMAL.DTCRA_Status = count;

		/* 転送元アドレスレジスタ情報の設定 */
		/* 転送先アドレスレジスタ情報の設定 */
		switch (direction) {
		case DMA_IO_TO_MEMORY:
			DTC_INT_NORMAL.DTSAR_Status = MDM_ADDRESS;
			DTC_INT_NORMAL.DTDAR_Status = address;
			break;
		case DMA_MEMORY_TO_IO:
			DTC_INT_NORMAL.DTSAR_Status = address;
			DTC_INT_NORMAL.DTDAR_Status = MDM_ADDRESS;
			break;
		}
		break;
	case DTC_INTERRUPT_CH2:
		/* カウントレジスタ情報の設定 */
		DTC_INT_NORMAL2.DTCRA_Status = count;

		/* 転送元アドレスレジスタ情報の設定 */
		/* 転送先アドレスレジスタ情報の設定 */
		switch (direction) {
		case DMA_IO_TO_MEMORY:
			DTC_INT_NORMAL2.DTSAR_Status = RS_ADDRESS;
			DTC_INT_NORMAL2.DTDAR_Status = address;
			break;
		case DMA_MEMORY_TO_IO:
			DTC_INT_NORMAL2.DTSAR_Status = address;
			DTC_INT_NORMAL2.DTDAR_Status = RS_ADDRESS;
			break;
		}
		break;
	case DTC_NORMAL_MODE:
	case DTC_BLOCK_MODE:
	case DTC_REPEAT_MODE:
	default:
		break;
	}
#endif /* (PRO_MODEM == ORANGE3)  */
#if (PRO_MODEM == R288F) /* added by H.Kubo 1997/10/09 */
	/* POPLAR_H では外付 DMAC があるため、モデムのデータ転送に DTC は
	** 使わないが、念のため入れておく。
	*/
	switch (dtc_mode) {
	case DTC_INTERRUPT_CH:
		/* カウントレジスタ情報の設定 */
		DTC_INT_NORMAL.DTCRA_Status = count;

		/* 転送元アドレスレジスタ情報の設定 */
		/* 転送先アドレスレジスタ情報の設定 */
		switch (direction) {
		case DMA_IO_TO_MEMORY:
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					DTC_INT_NORMAL.DTSAR_Status = S1_HDLC_DATA_ADDRESS;
				}
				else {
					DTC_INT_NORMAL.DTSAR_Status = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				DTC_INT_NORMAL.DTSAR_Status = MDM_RX_ADDRESS;
			}
#else
			DTC_INT_NORMAL.DTSAR_Status = MDM_RX_ADDRESS;
#endif

			DTC_INT_NORMAL.DTDAR_Status = address;
			break;
		case DMA_MEMORY_TO_IO:
			DTC_INT_NORMAL.DTSAR_Status = address;
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					DTC_INT_NORMAL.DTDAR_Status = S1_HDLC_DATA_ADDRESS;
				}
				else {
					DTC_INT_NORMAL.DTDAR_Status = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				DTC_INT_NORMAL.DTDAR_Status = MDM_TX_ADDRESS;
			}
#else
			DTC_INT_NORMAL.DTDAR_Status = MDM_TX_ADDRESS;
#endif
			break;
		}
		break;
	case DTC_INTERRUPT_CH2:
		/* カウントレジスタ情報の設定 */
		DTC_INT_NORMAL2.DTCRA_Status = count;

		/* 転送元アドレスレジスタ情報の設定 */
		/* 転送先アドレスレジスタ情報の設定 */
		switch (direction) {
		case DMA_IO_TO_MEMORY:
			DTC_INT_NORMAL2.DTSAR_Status = RS_ADDRESS;
			DTC_INT_NORMAL2.DTDAR_Status = address;
			break;
		case DMA_MEMORY_TO_IO:
			DTC_INT_NORMAL2.DTSAR_Status = address;
			DTC_INT_NORMAL2.DTDAR_Status = RS_ADDRESS;
			break;
		}
		break;
	case DTC_NORMAL_MODE:
	case DTC_BLOCK_MODE:
	case DTC_REPEAT_MODE:
	default:
		break;
	}
#endif /* (PRO_MODEM == R288F) */
	DMA_DTC_TransferStart(dtc_mode);
}
#endif	/* 1998/06/17 H.Yoshikawa */

/*************************************************************************
	module		:[ＤＭＡのリクエストをマスクします]
	function	:[
		1.ＤＴＣの割り込みレベルレジスタ
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/08]
	author		:[山口 哲治]
*************************************************************************/
void DMAtoDTC_RequestMask(UBYTE dtc_mode)
{
	
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	dtc_mode = DMAtoDTC_ChannelConvert(dtc_mode);
#endif
	
	switch (dtc_mode) {
	case DTC_INTERRUPT_CH:
#if 0	/* 1997/12/14 */
	/* 先にＤＴＣを無効にしてしまうとＤＲＥＱがＴＣになって誤動作するかもしれない */
		SH__DTEC &= ~IREQ5_ENABLE;
		SH__IPRB &= ~IRQ5_LEVEL;		/* IRQ5マスク 1997/08/05  By T.Yamaguchi */
#endif
		SH__IPRB &= ~IRQ5_LEVEL;		/* IRQ5マスク 1997/08/05  By T.Yamaguchi */
		SH__DTEC &= ~IREQ5_ENABLE;
		break;
	case DTC_BLOCK_MODE:
		if (SH__DTCSR == (DTCSR_SWDTE | 0x42)) {
			SH__DTCSR &= ~DTCSR_SWDTE;
		}
		break;
	case DTC_NORMAL_MODE:
		if (SH__DTCSR == (DTCSR_SWDTE | 0x44)) {
			SH__DTCSR &= ~DTCSR_SWDTE;
		}
		break;
	case DTC_REPEAT_MODE:
		if (SH__DTCSR == (DTCSR_SWDTE | 0x46)) {
			SH__DTCSR &= ~DTCSR_SWDTE;
		}
		break;
	case DTC_INTERRUPT_CH2:
#if 0	/* 1997/12/14 Y.M */
		SH__DTED &= ~IREQ6_ENABLE;
		SH__IPRB &= ~IRQ6_LEVEL;		/* IRQ6マスク 1997/08/05  By T.Yamaguchi */
#endif
		SH__IPRB &= ~IRQ6_LEVEL;		/* IRQ6マスク 1997/08/05  By T.Yamaguchi */
		SH__DTED &= ~IREQ6_ENABLE;
		break;

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
 #if 0 /* DTER を IPR より先に落とすと、 DTER を落としてからかかる DTC 起動割り込みで DTC 終了割り込みが起動される。 by H.Kubo 1999/01/18 */
@@	case DTC_INTERRUPT_IRQ0:
@@		SH__DTEC &= ~IREQ0_ENABLE;		/* スタート */
@@		SH__IPRA &= ~IRQ0_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ1:
@@		SH__DTEC &= ~IREQ1_ENABLE;		/* スタート */
@@		SH__IPRA &= ~IRQ1_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ2:
@@		SH__DTEC &= ~IREQ2_ENABLE;		/* スタート */
@@		SH__IPRA &= ~IRQ2_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ3:
@@		SH__DTEC &= ~IREQ3_ENABLE;		/* スタート */
@@		SH__IPRA &= ~IRQ3_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ4:
@@		SH__DTEC &= ~IREQ4_ENABLE;		/* スタート */
@@		SH__IPRB &= ~IRQ4_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ5:
@@		SH__DTEC &= ~IREQ5_ENABLE;		/* スタート */
@@		SH__IPRB &= ~IRQ5_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ6:
@@		SH__DTED &= ~IREQ6_ENABLE;		/* スタート */
@@		SH__IPRB &= ~IRQ6_LEVEL;		/* IRQ05マスク解除 */
@@		break;
@@	case DTC_INTERRUPT_IRQ7:
@@		SH__DTED &= ~IREQ7_ENABLE;		/* スタート */
@@		SH__IPRB &= ~IRQ7_LEVEL;		/* IRQ05マスク解除 */
@@		break;
 #else
	case DTC_INTERRUPT_IRQ0:
		SH__IPRA &= ~IRQ0_LEVEL;		/* IRQ05マスク解除 */
		SH__DTEC &= ~IREQ0_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ1:
		SH__IPRA &= ~IRQ1_LEVEL;		/* IRQ05マスク解除 */
		SH__DTEC &= ~IREQ1_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ2:
		SH__IPRA &= ~IRQ2_LEVEL;		/* IRQ05マスク解除 */
		SH__DTEC &= ~IREQ2_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ3:
		SH__IPRA &= ~IRQ3_LEVEL;		/* IRQ05マスク解除 */
		SH__DTEC &= ~IREQ3_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ4:
		SH__IPRB &= ~IRQ4_LEVEL;		/* IRQ05マスク解除 */
		SH__DTEC &= ~IREQ4_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ5:
		SH__IPRB &= ~IRQ5_LEVEL;		/* IRQ05マスク解除 */
		SH__DTEC &= ~IREQ5_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ6:
		SH__IPRB &= ~IRQ6_LEVEL;		/* IRQ05マスク解除 */
		SH__DTED &= ~IREQ6_ENABLE;		/* スタート */
		break;
	case DTC_INTERRUPT_IRQ7:
		SH__IPRB &= ~IRQ7_LEVEL;		/* IRQ05マスク解除 */
		SH__DTED &= ~IREQ7_ENABLE;		/* スタート */
		break;
  #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		/* SH__IPRF &= ~SCI1_LEVEL; */
		SH__DTED &= ~RXI1_ENABLE;
		break;
	case DTC_INTERRUPT_TXI1:
		/* SH__IPRF &= ~SCI1_LEVEL; */
		SH__DTED &= ~TXI1_ENABLE;
		break;
  #endif
 #endif
#endif
	default:
		break;
	}
#if 1 /* (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) */	/* 2002/12/11 T.Takagi */
/* DTC Address Error のビットが立っていた場合、二度とDTCが起動されないので、ここで落とす */
	if ((SH__DTCSR & DTCSR_AE) == DTCSR_AE) {
		SH__DTCSR &= ~DTCSR_AE;
	}
#endif
}

/*************************************************************************
	module		:[SH7043内蔵DTCの起動を許可する]
	function	:[
		1.ＤＴＣレジスタイネーブルビットを許可します
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/08]
	author		:[山口 哲治]
*************************************************************************/
void DMAtoDTC_RequestEnable(UBYTE dtc_mode)
{

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	dtc_mode = DMAtoDTC_ChannelConvert(dtc_mode);
#endif

	switch (dtc_mode) {
	case DTC_INTERRUPT_CH:
		SH__DTEC |= IREQ5_ENABLE;	/* スタート */
		SH__IPRB |= IRQ5_LEVEL;		/* IRQ5マスク解除 1997/08/05  By T.Yamaguchi */
		break;
	case DTC_BLOCK_MODE:
		/* 許可 */
		break;
	case DTC_NORMAL_MODE:
		/* 許可 */
		break;
	case DTC_REPEAT_MODE:
		/* 許可 */
		break;
	case DTC_INTERRUPT_CH2:
		SH__DTED |= IREQ6_ENABLE;	/* スタート */
		SH__IPRB |= IRQ6_LEVEL;		/* IRQ6マスク解除 1997/08/05  By T.Yamaguchi */
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		SH__DTEC |= IREQ0_ENABLE;	/* スタート */
		SH__IPRA |= IRQ0_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ1:
		SH__DTEC |= IREQ1_ENABLE;	/* スタート */
		SH__IPRA |= IRQ1_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ2:
		SH__DTEC |= IREQ2_ENABLE;	/* スタート */
		SH__IPRA |= IRQ2_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ3:
		SH__DTEC |= IREQ3_ENABLE;	/* スタート */
		SH__IPRA |= IRQ3_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ4:
		SH__DTEC |= IREQ4_ENABLE;	/* スタート */
		SH__IPRB |= IRQ4_LEVEL;		/* IRQ05マスク解除 */
		break;
	case DTC_INTERRUPT_IRQ5:
		SH__DTEC |= IREQ5_ENABLE;	/* スタート */
		SH__IPRB |= IRQ5_LEVEL;		/* IRQ05マスク解除 */
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 割り込みマスクを解除。 added by H.Kubo 1998/10/27 */
		SYS_MCR_PortStatus &= ~IO_BIT_MREQ5; /* DTC 転送要求のマスクを解除します。added by H.Kubo 1998/10/27 */
		outpw(MCR_PORT, SYS_MCR_PortStatus);
#endif
		break;
	case DTC_INTERRUPT_IRQ6:
		SH__DTED |= IREQ6_ENABLE;	/* スタート */
		SH__IPRB |= IRQ6_LEVEL;		/* IRQ05マスク解除 */
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* 割り込みマスクを解除。 added by H.Kubo 1998/10/27 */
		SYS_MCR_PortStatus &= ~IO_BIT_MREQ6; /* DTC 転送要求のマスクを解除します。added by H.Kubo 1998/10/27 */
		outpw(MCR_PORT, SYS_MCR_PortStatus);
#endif
		break;
	case DTC_INTERRUPT_IRQ7:
		SH__DTED |= IREQ7_ENABLE;	/* スタート */
		SH__IPRB |= IRQ7_LEVEL;		/* IRQ05マスク解除 */
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		/* SH__IPRF |= SCI1_LEVEL; */
		SH__DTED |= RXI1_ENABLE;
		break;
	case DTC_INTERRUPT_TXI1:
		/* SH__IPRF |= SCI1_LEVEL; */
		SH__DTED |= TXI1_ENABLE;
		break;
 #endif
#endif
	default:
		break;
	}
}

/*************************************************************************
	module		:[DTC設定のパラメターを初期化する
				]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1997/07/08]
	author		:[山口 哲治]
*************************************************************************/
void DMA_DTC_Initialize(void)
{
	/* DTC転送カウンタの値を０に初期化しておく */
	DTC_INT_NORMAL.DTCRA_Status = 0;
	DTC_BLOCK.DTCRA_Status = 0;
	DTC_NORMAL.DTCRA_Status = 0;
	DTC_REPEAT.DTCRA_Status = 0;
	DTC_INT_NORMAL2.DTCRA_Status = 0;

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	DTC_INT_NORMAL_IRQ0.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ1.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ2.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ3.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ4.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ5.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ6.DTCRA_Status = 0;
	DTC_INT_NORMAL_IRQ7.DTCRA_Status = 0;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
 	DTC_INT_NORMAL_RXI1.DTCRA_Status = 0;
	DTC_INT_NORMAL_TXI1.DTCRA_Status = 0;
 #endif
#endif
}

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
/*************************************************************************
	module		:[SH7043内蔵DTCのセットアップ]
	function	:[
		1.モデムＤＲＥＱ割り込みでＤＴＣレジスタ情報をセットアップします
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/16]
	author		:[山口哲治]
*************************************************************************/
void DMA_SetupIntDTC_IRQ(struct DMA_DTC_Data_t *setup)
{
	struct DMA_DTC_NormalMode_t *DTC_Normal_ptr;
	UDWORD address;
	
	/* モードレジスタ情報の設定
	** ソースアドレス増加
	** ノーマル転送モード
	** デスティネーション側ブロック領域
	** １ブロック転送終了で割込み発生
	** インタラプトセレクト
	** データ転送継続
	*/
	switch (setup->DTC_Mode) {
	case DTC_INTERRUPT_IRQ0:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ0);
		break;
	case DTC_INTERRUPT_IRQ1:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ1);
		break;
	case DTC_INTERRUPT_IRQ2:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ2);
		break;
	case DTC_INTERRUPT_IRQ3:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ3);
		break;
	case DTC_INTERRUPT_IRQ4:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ4);
		break;
	case DTC_INTERRUPT_IRQ5:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ5);
		break;
	case DTC_INTERRUPT_IRQ6:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ6);
		break;
	case DTC_INTERRUPT_IRQ7:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ7);
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_RXI1);
		break;
	case DTC_INTERRUPT_TXI1:
		DTC_Normal_ptr = &(DTC_INT_NORMAL_TXI1);
		break;
 #endif
	default:					/* バグ */
		SaveReturnAddressAndJumpBegin();
		DTC_Normal_ptr = &(DTC_INT_NORMAL_IRQ0);
		break;
	}

	DTC_Normal_ptr->DTMR_Status = 0;
	switch (setup->Direction) {
	case DMA_IO_TO_MEMORY:	/* ソースアドレス固定,デスティネーションアドレス増加 */
		DTC_Normal_ptr->DTMR_Status = (0 | DTMR_DM_INC );
		break;
	case DMA_MEMORY_TO_IO:	/* ソースアドレス増加,デスティネーションアドレス固定 */
		DTC_Normal_ptr->DTMR_Status = (0 | DTMR_SM_INC );
		break;
	default:
		break;
	}

	/* DTC モードはノーマル。何もしない。*/

	/* DTC 転送サイズ */
	switch (setup->Unit) {
	case DMA_BYTE_TRANSFER: /* バイト転送 */
		/* 初期設定値なので何もしない */
		break;
	case DMA_WORD_TRANSFER: /* ワード転送 */
		DTC_Normal_ptr->DTMR_Status |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER: /* ロング転送 */
		DTC_Normal_ptr->DTMR_Status |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}

#if 0 /* defined (SAKAKI) */ /* added by H.Kubo 1998/07/20 */ /* レベルセンスにするので、削除します。 H.Kubo 1998/07/21 */
	/* SAKAKI の R288F DTC 用の汚い対策です。 DTC による一バイト転送ごとに CPU へ割り込みが入るようにします。
	** これは、一バイト転送ごとに割込み要求をクリアするためです。
	** なお、この対策は、一時的なものです。
	*/

	switch (setup->DTC_Mode) {
	case DTC_INTERRUPT_IRQ5:
	case DTC_INTERRUPT_IRQ6:
		DTC_Normal_ptr->DTMR_Status |= DTMR_DISEL_SET;
		break;
	default:
		break;
	}

#endif




	/* カウントレジスタ情報の設定 */
	DTC_Normal_ptr->DTCRA_Status = setup->Counter;

	/* ブロック長レジスタ情報の設定 ﾉｰﾏﾙﾓｰﾄﾞはない */
	/* DTC_Normal_ptr->DTCRB_Status = setup->Length; */

	/* 転送元アドレスレジスタ情報の設定 */
	DTC_Normal_ptr->DTSAR_Status = setup->SrcAddress;

	/* 転送先アドレスレジスタ情報の設定 */
	DTC_Normal_ptr->DTDAR_Status = setup->DstAddress;

	/* ＤＴＣ情報ベースレジスタの設定 */
/*	address = (UDWORD)(&DTC_INT_NORMAL); */
	address = (UDWORD)(DTC_Normal_ptr);
	SH__DTBR = (UWORD)(address >> 16);
}

/*************************************************************************
	module		:[DMAをDTCに置換えて使用するときのパラメータを変換する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/16]
	author		:[吉川弘康]
*************************************************************************/
void DMAtoDTC_Convert(struct DMA_DTC_Data_t *dtc_ptr,
	 				  struct DMA_Data_t *dma_ptr)
{
	
	/*---------------------------------------------------------------------
	** 機種ごとに、CannelとIRQの割付が異なるので、
	** SAKAKI以外の場合には、条件コンパイルにて変更する必要がある。
	** 今は、この関数そのものがSAKAKIのみ有効です。
	*/
	dtc_ptr->DTC_Mode = DMAtoDTC_ChannelConvert(dma_ptr->Channel);
	
	switch (dma_ptr->Channel) {
	case DMA_SCNCDC_DRAM_CH:	/* DMA_IO_TO_MEMORY */
		if (dma_ptr->Direction == DMA_IO_TO_MEMORY) {	/* 1998/07/22 H.Yoshikawa */
			dtc_ptr->SrcAddress = SCN_TO_DRAM_ADDRESS;
			dtc_ptr->DstAddress = dma_ptr->SrcAddress;
		}
		else {
			dtc_ptr->SrcAddress = dma_ptr->SrcAddress;
			dtc_ptr->DstAddress = SCN_TO_DRAM_ADDRESS;
		}
		break;
	case DMA_DRAM_PRNCDC_CH:	/* DMA_MEMORY_TO_IO */
		dtc_ptr->SrcAddress = dma_ptr->SrcAddress;
		dtc_ptr->DstAddress = PRN_TO_DRAM_ADDRESS;
		break;
	case DMA_MDM_MDMBUF_CH:		/* DMA_IO_TO_MEMORY */
#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
		if ((FCM_S1_Scramble == TRUE) && 
			((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
			|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
			if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
				dtc_ptr->SrcAddress = S1_HDLC_DATA_ADDRESS;
			}
			else {
				dtc_ptr->SrcAddress = S1_SCI_DATA_ADDRESS;
			}
		}
		else {
			dtc_ptr->SrcAddress = MDM_RX_ADDRESS;
		}
#else
		dtc_ptr->SrcAddress = MDM_RX_ADDRESS;
#endif
		dtc_ptr->DstAddress = dma_ptr->SrcAddress;
		break;
	case DMA_MDMBUF_MDM_CH:		/* DMA_MEMORY_TO_IO */
		dtc_ptr->SrcAddress = dma_ptr->SrcAddress;
#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
		if ((FCM_S1_Scramble == TRUE) && 
			((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
			|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
			if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
				dtc_ptr->DstAddress = S1_HDLC_DATA_ADDRESS;
			}
			else {
				dtc_ptr->DstAddress = S1_SCI_DATA_ADDRESS;
			}
		}
		else {
			dtc_ptr->DstAddress = MDM_TX_ADDRESS;
		}
#else
		dtc_ptr->DstAddress = MDM_TX_ADDRESS;
#endif
		break;
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
	case DMA_GATEARRAYWRITE_CH:	/* DMA_MEMORY_TO_IO *//* プリンタイメージバッファ → Ｇ／Ａ 1998/10/26 by T.Soneoka */
		dtc_ptr->SrcAddress = dma_ptr->SrcAddress;
		dtc_ptr->DstAddress = PRN_TO_GA_ADDRESS;
		break;
#endif
	case DMA_MPC_MPCBUF_CH:	/* CLASS1 */
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
		if (SYB_MaintenanceSwitch[MNT_SW_G2] & 0x02) {	/* ＤＭＡ／ＤＴＣをスイッチで切り替える by H.Hirao 1999/01/23 */
			if (dma_ptr->Direction == DMA_IO_TO_MEMORY) {
				dtc_ptr->SrcAddress = (UDWORD)SCI_RDR1;
				dtc_ptr->DstAddress = dma_ptr->SrcAddress;
			}
			else {
				dtc_ptr->SrcAddress = dma_ptr->SrcAddress;
				dtc_ptr->DstAddress = (UDWORD)SCI_TDR1;
			}
			break;
		}
#endif
	default:	/* ここにきたらバグです */
		SaveReturnAddressAndJumpBegin();
		dtc_ptr->SrcAddress = dma_ptr->SrcAddress;
		dtc_ptr->DstAddress = dma_ptr->DstAddress;
		break;
	}
	
}

/*************************************************************************
	module		:[DMAをDTCに置換えて使用するときのCannelを変換する]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/16]
	author		:[吉川弘康]
*************************************************************************/
UBYTE DMAtoDTC_ChannelConvert(UBYTE channel)
{
	
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/08/31 H.Yoshikawa */
	/*---------------------------------------------------------------------
	** 機種ごとに、CannelとIRQの割付が異なるので、
	** SAKAKI以外の場合には、条件コンパイルにて変更する必要がある。
	** 今は、この関数そのものがSAKAKIのみ有効です。
	*/
	switch (channel) {
	case DMA_SCNCDC_DRAM_CH:	/* DMA_IO_TO_MEMORY */
		return (DTC_INTERRUPT_IRQ3);
	case DMA_DRAM_PRNCDC_CH:	/* DMA_MEMORY_TO_IO */
		return (DTC_INTERRUPT_IRQ4);
	case DMA_MDMBUF_MDM_CH:		/* DMA_MEMORY_TO_IO */
		return (DTC_INTERRUPT_IRQ5);
	case DMA_MDM_MDMBUF_CH:		/* DMA_IO_TO_MEMORY */
		return (DTC_INTERRUPT_IRQ6);
	case DMA_MPC_MPCBUF_CH:	/* CLASS1 */
	default:
		SaveReturnAddressAndJumpBegin();
		return (channel);
	}
#elif (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
	/*---------------------------------------------------------------------
	** 機種ごとに、CannelとIRQの割付が異なるので、
	** HINOKI以外の場合には、条件コンパイルにて変更する必要がある。
	** 今は、この関数そのものがHINOKIのみ有効です。
	*/
	switch (channel) {
	case DMA_MDMBUF_MDM_CH:		/* DMA_MEMORY_TO_IO */
		return (DTC_INTERRUPT_IRQ2);
	case DMA_MDM_MDMBUF_CH:		/* DMA_IO_TO_MEMORY */
		return (DTC_INTERRUPT_IRQ3);
	case DMA_GATEARRAYWRITE_CH:	/* DMA_MEMORY_TO_IO *//* プリンタイメージバッファ → Ｇ／Ａ 1998/10/26 by T.Soneoka */
		return (DTC_INTERRUPT_IRQ6);
	case DMA_MPC_MPCBUF_CH:	/* CLASS1 */
#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
		if (SYB_MaintenanceSwitch[MNT_SW_G2] & 0x02) {	/* ＤＭＡ／ＤＴＣをスイッチで切り替える by H.Hirao 1999/01/23 */
			if (RsDMA_Data.Direction == DMA_IO_TO_MEMORY) {
				return (DTC_INTERRUPT_RXI1);
			}
			else {
				return (DTC_INTERRUPT_TXI1);
			}
		}
#endif
	default:
		SaveReturnAddressAndJumpBegin();
		return (channel);
	}
#endif
}

/*************************************************************************
	module		:[SH7043内蔵DTCの終了割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[ＤＴＣの終了割り込みは、ＤＴＣを起動していない状態での
				  起動要因の割り込みで発生する]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/17]
	author		:[山口哲治/吉川弘康]
*************************************************************************/
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
UWORD DTC_SCN_EndCount = 0;	/* 1998/07/06 */
void DTC_SCN_DRAM_Interrupt(void)
{
	UDWORD count;	/* テスト用 */
	UDWORD address;	/* テスト用 */

#if (0)	/* 1998/11/25 H.Yoshikawa */	
//	if (SYB_MaintenanceSwitch[MNT_SW_H0] & SCN_DTC_END_TEST) {	/* 1998/11/21 */
//		address = DTC_INT_NORMAL_IRQ3.DTDAR_Status;
//		if (address == 0x01010000) {
//			SYS_Modem2PortStatus &= ~ (IO_BIT_STAMP);	/** Stamp OFF */
//			outpw(MODEM2_PORT, (UWORD)SYS_Modem2PortStatus);	/** Stamp OFF */
//		}
//	}
#endif

	SH__IPRA &= ~IRQ3_LEVEL;	/* IRQ3マスク */

	/*---------------------------------------------------------------------
	** プリント中に、舞子チャートをSfineでスキャナ送信すると、T.4.1/R.3.3エラーとなる件
	** 読み取り終了後に、プリントを再開すると、なぜか、DTC割り込みが発生する
	** 1998/11/17 H.Yoshikawa
	*/
	SH__DTEC &= ~IREQ3_ENABLE;		/* マスク */
	count = DTC_INT_NORMAL_IRQ3.DTCRA_Status;
	if (count > 0) { /* DTC が終了していないのに割り込み処理に来たら */
		SYB_MaintenanceSwitch[MNT_SW_H0] |= SCN_DTC_TC_ILLEGAL;
		SH__DTEC &= ~IREQ3_ENABLE;
		SH__DTEC |= IREQ3_ENABLE;	/* スタート */
		SH__IPRA |= IRQ3_LEVEL;		/* IRQ05マスク解除 */
		return;
	}

	DTC_SCN_EndCount ++;	/* 1998/07/06 */
	DMA_SysDICEP_End = 1;	/* メモリ蓄積時に使用 1998/08/12 */
	IsSCNCDC_ToMemoryXferDone = YES;	/* スキャナ送信時に使用 1998/08/12 */

/*	idet_evt(EVT_COMMAND_OR_DMA_BLOCK_END);	1998/07/29 */
	idet_evt(EVT_DMA_SCNCDC_DRAM);

	/* DMA終了割り込みを呼ぶ */
	
}
#endif /* (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) */

/*************************************************************************
	module		:[SH7043内蔵DTCの終了割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[ＤＴＣの終了割り込みは、ＤＴＣを起動していない状態での
				  起動要因の割り込みで発生する]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/17]
	author		:[山口哲治/吉川弘康]
*************************************************************************/
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
extern UWORD SMCR_Status;	/* 1998/08/04 */
void DTC_DRAM_PRN_Interrupt(void)
{
	UDWORD count;	/* テスト用 */

	SH__IPRB &= ~IRQ4_LEVEL;	/*** IRQ4マスク ***/

	/*---------------------------------------------------------------------
	**	PRNのDTC転送時に、残り転送データがあるにも関わらず、
	** 転送終了割り込みが発生した場合
	** 1998/11/17 H.Yoshikawa
	*/
	SH__DTEC &= ~IREQ4_ENABLE;		/* マスク */
	count = DTC_INT_NORMAL_IRQ4.DTCRA_Status;
	if (count > 0) { /* DTC が終了していないのに割り込み処理に来たら */
		SYB_MaintenanceSwitch[MNT_SW_H0] |= PRN_DTC_TC_ILLEGAL;
		SH__DTEC &= ~IREQ4_ENABLE;
		SH__DTEC |= IREQ4_ENABLE;	/* スタート */
		SH__IPRB |= IRQ4_LEVEL;		/* IRQ05マスク解除 */
		return;
	}

	PRN_DTC_INT_Completed = NO;
#if (0)
		/*** 時間稼ぎのため ***/
		DmaEnable();
		DmaEnable();
		DmaEnable();
		/*** SMCR Serial + IDP301 ***/
		SMCR_StatusPRN_Dummy = SMCR_Status;
		SMCR_StatusPRN_Dummy &= ~(0x0002);
		SMCR_StatusPRN_Dummy |= 0x0080;
		(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
		(*(UWORD *)0xC20644) = SMCR_Status;
		(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
		(*(UWORD *)0xC20644) = SMCR_Status;
		(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
		(*(UWORD *)0xC20644) = SMCR_Status;
		(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
		(*(UWORD *)0xC20644) = SMCR_Status;
		(*(UWORD *)0xC20644) = SMCR_StatusPRN_Dummy;
		(*(UWORD *)0xC20644) = SMCR_Status;
#endif
}
#endif /* (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) */

/*************************************************************************
	module		:[SH7043内蔵DTCの終了割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[ＤＴＣの終了割り込みは、ＤＴＣを起動していない状態での
				  起動要因の割り込みで発生する]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/17]
	author		:[山口哲治/吉川弘康]
*************************************************************************/
void DTC_MDMBUF_MDM_Interrupt(void)
{
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
	 SH__IPRB &= ~IRQ5_LEVEL;	/* IRQ5マスク */

	/* DMA終了割り込みを呼ぶ */
	/* 久保さんへ、処理を追加してください。 */	
 #if (PRO_MODEM == R288F) && (PRO_EXT_DMAC == DISABLE) /* Moved from mdm_int.c by H.Kubo 1999/01/13 */
  #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /*  スキャナ送信 T4.1, R3.3 デバッグ用。Added by H.Kubo 1998/11/17 */
	{
		UDWORD count;
		DMA_RequestMask(DMA_CH_TX);
		count = DMA_CheckDMA_Counter(DMA_CH_TX);
		if (count > 0) { /* DTC が終了していないのに割り込み処理に来たら */
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_MODEM_DMA_TC_ILLEGAL;
			/* 黙って DTC の続きを再起動。 */
  #if 0 /* カウンタの値が不正になることがあるので修正します。 by H.Kubo 1999/01/18 */
@@			DMA_RestartDMAU(DMA_CH_TX, DMA_IO_TO_MEMORY, count ,
@@				(UDWORD)&MDMRPNT.TopAddress[(UWORD)(MDMRPNT.DataCount - count)]);
  #else
			DMA_Continue(DMA_CH_TX);
  #endif
			return;
		}
	}
  #endif
	MDM_TxDMA_TC_Interrupt();
 #endif
#elif (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
	 SH__IPRA &= ~IRQ2_LEVEL;	/* IRQ2マスク */

	/* DMA終了割り込みを呼ぶ */
	/* 久保さんへ、処理を追加してください。 */	
 #if (PRO_MODEM == R288F) && (PRO_EXT_DMAC == DISABLE) /* added by H.Kubo 1998/06/29 */
	MDM_TxDMA_TC_Interrupt();
 #endif
#endif
	
}
/*************************************************************************
	module		:[SH7043内蔵DTCの終了割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[ＤＴＣの終了割り込みは、ＤＴＣを起動していない状態での
				  起動要因の割り込みで発生する]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/17]
	author		:[山口哲治/吉川弘康]
*************************************************************************/
void DTC_MDM_MDMBUF_Interrupt(void)
{
#if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
	 SH__IPRB &= ~IRQ6_LEVEL;	/* IRQ6マスク */

	/* DMA終了割り込みを呼ぶ */
	/* 久保さんへ、処理を追加してください。 */	
 #if (PRO_MODEM == R288F) && (PRO_EXT_DMAC == DISABLE) /* added by H.Kubo 1998/06/29 */
  #if (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /*  Moved mdm_int.c by H.Kubo 1999/01/13 */
	{
		UDWORD count; /* added by H.Kubo 1998/11/13 */
		DMA_RequestMask(DMA_CH_RX);
		count = DMA_CheckDMA_Counter(DMA_CH_RX);
		if (count > 0) { /* DTC が終了していないのに割り込み処理に来たら */
			SYB_MaintenanceSwitch[MNT_SW_C1] |= MDM_MODEM_DMA_TC_ILLEGAL;
			/* 黙って DTC の続きを再起動。 */
  #if 0 /* カウンタの値が不正になることがあります。カウンタもアドレスも更新せずに再起動。 by H.Kubo 1999/01/18 */
@@			DMA_RestartDMAU(DMA_CH_RX, DMA_IO_TO_MEMORY, count ,(UDWORD)&MDM_ModemBuffer[ModemControl.WritePoint][(UWORD)(MODEM_DMA_SIZE - count)]);
  #else
			DMA_Continue(DMA_CH_RX);
  #endif
			return;
		}
	}
  #endif
	MDM_RxDMA_TC_Interrupt();
 #endif
#elif (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)		/* PRO_DTC_INT_SYSTEMがENABLE時の割り込み要因割り当て 1998/09/21 H.Hirao */
	 SH__IPRA &= ~IRQ3_LEVEL;	/* IRQ3マスク */

	/* DMA終了割り込みを呼ぶ */
	/* 久保さんへ、処理を追加してください。 */	
 #if (PRO_MODEM == R288F) && (PRO_EXT_DMAC == DISABLE) /* added by H.Kubo 1998/06/29 */
	MDM_RxDMA_TC_Interrupt();
 #endif
#endif
}

#if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI)
/*************************************************************************
	module		:[SH7043内蔵DTCの終了割り込み処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[ＤＴＣの終了割り込みは、ＤＴＣを起動していない状態での
				  起動要因の割り込みで発生する]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/06/17]
	author		:[曽根岡拓]
*************************************************************************/
void DTC_GateArrayWriteInterrupt(void)
{
	UWORD Status;

#if (0)
** 	/* マスクするレジスターが間違えている。
** 	** by O.Kimoto 1998/11/27
** 	*/
** 	SH__IPRA &= ~IRQ6_LEVEL;	/* IRQ6マスク */
#else
	SH__IPRB &= ~IRQ6_LEVEL;	/* IRQ6マスク */
#endif

	/* プリントループ調査用 add 2 line 1999/1/25 by T.Soneoka */
	if (SYB_MaintenanceSwitch[MNT_SW_H5] & 0x80) {
		RelayPortStatus &= ~0x4000;
		OutputWORD(GA_PGADR, RelayPortStatus);
	}

	DtcPermission = TRUE;
	DMA_RequestMask(DMA_GATEARRAYWRITE_CH);

}
#endif

/*************************************************************************
	module		:[SH7043内蔵DTCの転送アドレスを設定する]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[198/07/16]
	author		:[久保博]
*************************************************************************/
void DMA_DTC_SetAddress(UBYTE channel, UBYTE direction, UDWORD address)
{
#if defined (KEISATSU) /* 警察FAX 05/07/27 石橋正和 */
	UDWORD src_addr;
	UDWORD dst_addr;
#endif

	switch (direction) {
	case DMA_IO_TO_MEMORY:
		DMA_DTC_SetDstAddress(channel, address);	/* DTCを使用する場合 */
		if (channel == DMA_MDM_MDMBUF_CH) {
#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((RxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					src_addr = S1_HDLC_DATA_ADDRESS;
				}
				else {
					src_addr = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				src_addr = MDM_RX_ADDRESS;
			}
			DMA_DTC_SetSrcAddress(channel, src_addr);	/* DTCを使用する場合 */
#else
			DMA_DTC_SetSrcAddress(channel, MDM_RX_ADDRESS);	/* DTCを使用する場合 */
#endif
		}
		break;
	case DMA_MEMORY_TO_IO:
		DMA_DTC_SetSrcAddress(channel, address);	/* DTCを使用する場合 */
		if (channel == DMA_MDMBUF_MDM_CH) {
#if defined (KEISATSU) /* 警察FAX 05/06/17 石橋正和 */
			if ((FCM_S1_Scramble == TRUE) && 
				((ModemBlock.Mode == MODE_TX_ECM) || (ModemBlock.Mode == MODE_TX_G3) || (ModemBlock.Mode == MODE_TX_TCF)
				|| (ModemBlock.Mode == MODE_RX_ECM) || (ModemBlock.Mode == MODE_RX_G3) || (ModemBlock.Mode == MODE_RX_TCF))) {
				if ((TxECM_Mode == ECM_ON) && (ModemBlock.Mode != MODE_TX_TCF) && (ModemBlock.Mode != MODE_RX_TCF)) {
					dst_addr = S1_HDLC_DATA_ADDRESS;
				}
				else {
					dst_addr = S1_SCI_DATA_ADDRESS;
				}
			}
			else {
				dst_addr = MDM_TX_ADDRESS;
			}
			DMA_DTC_SetDstAddress(channel, dst_addr);	/* DTCを使用する場合 */
#else
			DMA_DTC_SetDstAddress(channel, MDM_TX_ADDRESS);	/* DTCを使用する場合 */
#endif
			
		}
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}


}

/*************************************************************************
	module		:[SH7043内蔵DTCの転送アドレスを設定する]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[198/07/16]
	author		:[久保博]
*************************************************************************/
void DMA_DTC_SetDstAddress(UBYTE channel, UDWORD address)
{
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		DTC_INT_NORMAL.DTDAR_Status = address;
		break;
	case DTC_BLOCK_MODE:
		DTC_BLOCK.DTDAR_Status = address;
		break;
	case DTC_NORMAL_MODE:
		DTC_BLOCK.DTDAR_Status = address;
		break;
	case DTC_REPEAT_MODE:
		DTC_REPEAT.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_CH2:
		DTC_INT_NORMAL2.DTDAR_Status = address;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		DTC_INT_NORMAL_IRQ0.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ1:
		DTC_INT_NORMAL_IRQ1.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ2:
		DTC_INT_NORMAL_IRQ2.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ3:
		DTC_INT_NORMAL_IRQ3.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ4:
		DTC_INT_NORMAL_IRQ4.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ5:
		DTC_INT_NORMAL_IRQ5.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ6:
		DTC_INT_NORMAL_IRQ6.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ7:
		DTC_INT_NORMAL_IRQ7.DTDAR_Status = address;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		DTC_INT_NORMAL_RXI1.DTDAR_Status = address;
		break;
	case DTC_INTERRUPT_TXI1:
		DTC_INT_NORMAL_TXI1.DTDAR_Status = address;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}
}

/*************************************************************************
	module		:[SH7043内蔵DTCの現在の転送アドレスを読み出す]
	function	:[
		1.
	]
	return		:[アドレス]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[198/07/16]
	author		:[久保博]
*************************************************************************/
void DMA_DTC_SetSrcAddress(UBYTE channel, UDWORD address)
{
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		DTC_INT_NORMAL.DTSAR_Status = address;
		break;
	case DTC_BLOCK_MODE:
		DTC_BLOCK.DTSAR_Status = address;
		break;
	case DTC_NORMAL_MODE:
		DTC_BLOCK.DTSAR_Status = address;
		break;
	case DTC_REPEAT_MODE:
		DTC_REPEAT.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_CH2:
		DTC_INT_NORMAL2.DTSAR_Status = address;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		DTC_INT_NORMAL_IRQ0.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ1:
		DTC_INT_NORMAL_IRQ1.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ2:
		DTC_INT_NORMAL_IRQ2.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ3:
		DTC_INT_NORMAL_IRQ3.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ4:
		DTC_INT_NORMAL_IRQ4.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ5:
		DTC_INT_NORMAL_IRQ5.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ6:
		DTC_INT_NORMAL_IRQ6.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_IRQ7:
		DTC_INT_NORMAL_IRQ7.DTSAR_Status = address;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		DTC_INT_NORMAL_RXI1.DTSAR_Status = address;
		break;
	case DTC_INTERRUPT_TXI1:
		DTC_INT_NORMAL_TXI1.DTSAR_Status = address;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}
}


/*************************************************************************
	module		:[SH7043内蔵DTCの転送回数を設定する]
	function	:[
		1.
	]
	return		:[]
	common		:[
		DTC の転送回数を設定する。リピートモード、ブロックモードの場合は、 DTCRA 。
	]
	condition	:[]
	comment		:[
		さかき専用
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/07/16]
	author		:[久保博]
*************************************************************************/
void DMA_DTC_SetCounter(UBYTE channel, UWORD count)
{

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		DTC_INT_NORMAL.DTCRA_Status = count;
		break;
	case DTC_BLOCK_MODE:
		DTC_BLOCK.DTCRA_Status = count;
		break;
	case DTC_NORMAL_MODE:
		DTC_BLOCK.DTCRA_Status = count;
		break;
	case DTC_REPEAT_MODE:
		DTC_REPEAT.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_CH2:
		DTC_INT_NORMAL2.DTCRA_Status = count;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		DTC_INT_NORMAL_IRQ0.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ1:
		DTC_INT_NORMAL_IRQ1.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ2:
		DTC_INT_NORMAL_IRQ2.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ3:
		DTC_INT_NORMAL_IRQ3.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ4:
		DTC_INT_NORMAL_IRQ4.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ5:
		DTC_INT_NORMAL_IRQ5.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ6:
		DTC_INT_NORMAL_IRQ6.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_IRQ7:
		DTC_INT_NORMAL_IRQ7.DTCRA_Status = count;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		DTC_INT_NORMAL_RXI1.DTCRA_Status = count;
		break;
	case DTC_INTERRUPT_TXI1:
		DTC_INT_NORMAL_TXI1.DTCRA_Status = count;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}

}


/*************************************************************************
	module		:[SH7043内蔵DTCの転送回数を設定する]
	function	:[
		1.
	]
	return		:[]
	common		:[
		DTC の転送回数を設定する。リピートモード、ブロックモードの場合は、 DTCRA 。
	]
	condition	:[]
	comment		:[
		さかき専用
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/07/16]
	author		:[久保博]
*************************************************************************/
void DMA_DTC_SetUnit(UBYTE channel, UBYTE unit)
{
	UWORD	*dtmr_ptr;

#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	channel = DMAtoDTC_ChannelConvert(channel);
#endif

	switch (channel) {
	case DTC_INTERRUPT_CH:
		dtmr_ptr = &DTC_INT_NORMAL.DTMR_Status;
		break;
	case DTC_BLOCK_MODE:
		dtmr_ptr = &DTC_BLOCK.DTMR_Status;
		break;
	case DTC_NORMAL_MODE:
		dtmr_ptr = &DTC_BLOCK.DTMR_Status;
		break;
	case DTC_REPEAT_MODE:
		dtmr_ptr = &DTC_REPEAT.DTMR_Status;
		break;
	case DTC_INTERRUPT_CH2:
		dtmr_ptr = &DTC_INT_NORMAL2.DTMR_Status;
		break;
#if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	case DTC_INTERRUPT_IRQ0:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ0.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ1:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ1.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ2:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ2.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ3:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ3.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ4:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ4.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ5:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ5.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ6:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ6.DTMR_Status;
		break;
	case DTC_INTERRUPT_IRQ7:
		dtmr_ptr = &DTC_INT_NORMAL_IRQ7.DTMR_Status;
		break;
 #if (PRO_DTC_INT_TYPE == DTC_INT_HINOKI) && (PRO_CLASS1 == ENABLE) && (PRO_RS_INTERNAL == ENABLE)	/* by H.Hirao 1999/01/23 */
	case DTC_INTERRUPT_RXI1:
		dtmr_ptr = &DTC_INT_NORMAL_RXI1.DTMR_Status;
		break;
	case DTC_INTERRUPT_TXI1:
		dtmr_ptr = &DTC_INT_NORMAL_TXI1.DTMR_Status;
		break;
 #endif
#endif
	default:
		SaveReturnAddressAndJumpBegin();
	}

#if (PRO_CPU == SH7043)
	switch (unit) {
	case DMA_BYTE_TRANSFER:
		*dtmr_ptr &= ~(DTMR_SZ_WORD | DTMR_SZ_DWORD);
		break;
	case DMA_WORD_TRANSFER:
		*dtmr_ptr &= ~DTMR_SZ_DWORD;
		*dtmr_ptr |= DTMR_SZ_WORD;
		break;
	case DMA_DWORD_TRANSFER:
		*dtmr_ptr &= ~DTMR_SZ_WORD;
		*dtmr_ptr |= DTMR_SZ_DWORD;
		break;
	default:
		SaveReturnAddressAndJumpBegin();
	}
#else
	#error "The CPU has Changed! */
#endif
}

#if (PRO_DTC_INT_SYSTEM == ENABLE)	/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
/*************************************************************************
	module		:[SH7043内蔵DTCの転送回数を初期化する]
	function	:[
		1.
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/11/19]
	author		:[久保博]
*************************************************************************/
void DMA_DTC_InitializeCounter(void)
{
	UWORD i;
	for (i = (DTC_INTERRUPT_IRQ0 - DTC_INTERRUPT_IRQ0); i <= (DTC_INTERRUPT_IRQ7 - DTC_INTERRUPT_IRQ0); i++) {
		DMA_DTC_ParamIRQ[i].SetData.NormalMode.DTCRA_Status = 0; /* DTC 転送カウンタ 0 */
	}
}

#endif


#endif /* (SAKAKI) */
