/**********************************************************************************************************************
	@(#)$Id: s1_reg.c,v 1.14 2005/11/17 23:19:34 mi93007 Exp $
	Create        : 2005/06/13
	Author        : 石橋正和
	Description   : S1レジスタ処理
	Maintenance   : 
	Copyright (C) 2002-2005 Murata Machinery,Ltd. All rights reserved.
**********************************************************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\s1_pro.h"
#include "\src\atlanta\define\s1_def.h"
#include "\src\atlanta\ext_v\s1_data.h"

/**************************************************************************************************/
/**
	@brief		S1を初期化する(起動時)
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/09 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_Initialize(void)
{
	S1_HardwareReset();
	
	wai_tsk(20); /* 200ms */
}

/**************************************************************************************************/
/**
	@brief		S1を初期化する(通信開始時)
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/09 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_InitializeFaxCom(
				BOOL bavailable,	/* スクランブル有効/無効 */
				BOOL bbypass)		/* S1バイパスするか否か */
{
	S1_SoftwareReset(); /* S1ソフトリセット */
	
	/* スクランブラの有効/無効のセット */
	if (bavailable == TRUE) {
		S1_SetScrambleAvailable(TRUE);
	}
	else {
		S1_SetScrambleAvailable(FALSE);
	}
	
	S1_BypassS1(bbypass); /* S1バイパスのセット */
	
	S1_HDLC_InitializeCRC(); /* CRC生成多項式の初期化 */
	S1_HDLC_InitializeTransMode(); /* HDLC 転送モードの初期化 */
	S1_HDLC_InitializeTxMode(); /* HDLC 送信モード初期化 */
}

/**************************************************************************************************/
/**
	@brief		G3受信オープン
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_OpenG3Rx(
			BOOL bsenyo) /* TRUE:専用 FALSE:共通 */
{
	S1_SetMode(FALSE); /* SCIモード */
	
	S1_SetScrambleMode(bsenyo);
	
	S1_SCI_SetIntDTC_Enabled(S1_REG_BIT_SCI_OVEIE | S1_REG_BIT_SCI_RXRDYDTCE);
	
	S1_EnableInterrupt(); /* S1割り込み許可 */
	S1_EnableDTC_Request(S1_DTC_RX_SCI); /* DTC要求許可 */
	S1_SCI_EnableRx(TRUE); /* 受信許可 */
	
	S1_EnableRLSD(TRUE); /* RLSDを有効にする */
}

/**************************************************************************************************/
/**
	@brief		G3受信クローズ
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_CloseG3Rx(void)
{
	S1_EnableRLSD(FALSE); /* RLSDを無効にする */
	
	S1_SCI_EnableRx(FALSE); /* 受信禁止 */
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC要求クリア */
	S1_DisableInterrupt(); /* S1割り込み禁止 */
	
}

/**************************************************************************************************/
/**
	@brief		G3送信オープン
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/21 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_OpenG3Tx(
			BOOL bsenyo) /* TRUE:専用 FALSE:共通 */
{
	volatile UBYTE benable = 1;
	
	S1_SetMode(FALSE); /* SCIモード */
	
	S1_SetScrambleMode(bsenyo);
	
	S1_SCI_SetIntDTC_Enabled(S1_REG_BIT_SCI_TXRDYDTCE);
	
	S1_EnableInterrupt(); /* S1割り込み許可 */
	S1_EnableDTC_Request(S1_DTC_TX_SCI); /* DTC要求許可 */
	
	S1_SCI_EnableTx(TRUE); /* 送信許可 */
	
	if (benable == 1) {
		S1_EnableRTS(TRUE); /* RTSを有効にする */
	}
}

/**************************************************************************************************/
/**
	@brief		G3送信クローズ
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/21 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_CloseG3Tx(void)
{
	S1_EnableRTS(FALSE); /* RTSを無効にする */
	
	S1_SCI_EnableTx(FALSE); /* 送信禁止 */
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC要求クリア */
	S1_DisableInterrupt(); /* S1割り込み禁止 */
}

/**************************************************************************************************/
/**
	@brief		ECM受信オープン
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/21 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_OpenECM_Rx(
			BOOL bsenyo) /* TRUE:専用 FALSE:共通 */
{
	S1_SetMode(TRUE); /* HDLCモード */
	
	S1_SetScrambleMode(bsenyo);
	
	S1_HDLC_SetRxIntDTC_Enabled(S1_REG_BIT_HDLC_ERRIE | S1_REG_BIT_HDLC_ENDIE | S1_REG_BIT_HDLC_RXDI);
	
	S1_HDLC_EnableRxInterrupt(TRUE);
	S1_HDLC_EnableRxDMA_Request(TRUE);
	
	S1_EnableInterrupt(); /* S1割り込み許可 */
	S1_EnableDTC_Request(S1_DTC_RX_HDLC); /* DTC要求許可 */
	S1_HDLC_EnableRx(TRUE); /* 受信許可 */
	
	S1_EnableRLSD(TRUE); /* RLSDを有効にする */
}

/**************************************************************************************************/
/**
	@brief		ECM受信クローズ
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/21 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_CloseECM_Rx(void)
{
	S1_EnableRLSD(FALSE); /* RLSDを無効にする */
	
	S1_HDLC_EnableRx(FALSE); /* 受信禁止 */
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC要求クリア */
	S1_DisableInterrupt(); /* S1割り込み禁止 */
	
	S1_HDLC_EnableRxDMA_Request(FALSE);
	S1_HDLC_EnableRxInterrupt(FALSE);
}

/**************************************************************************************************/
/**
	@brief		ECM送信オープン
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/21 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_OpenECM_Tx(
			BOOL bsenyo) /* TRUE:専用 FALSE:共通 */
{
	S1_SetMode(TRUE); /* HDLCモード */
	
	S1_SetScrambleMode(bsenyo);
	
	/* S1_HDLC_SetTxIntDTC_Enabled(S1_REG_BIT_HDLC_TXENDIE | S1_REG_BIT_HDLC_TXDI); */
	S1_HDLC_SetTxIntDTC_Enabled(S1_REG_BIT_HDLC_TXDI);
	
	S1_HDLC_EnableTxInterrupt(TRUE);
	S1_HDLC_EnableTxDMA_Request(TRUE);
	
	S1_EnableInterrupt(); /* S1割り込み許可 */
	S1_EnableDTC_Request(S1_DTC_TX_HDLC); /* DTC要求許可 */
	S1_HDLC_TxSelectIdle(TRUE);
	S1_HDLC_EnableTx(TRUE); /* 送信許可 */
	
	S1_EnableRTS(TRUE); /* RTSを有効にする */
}

/**************************************************************************************************/
/**
	@brief		ECM送信クローズ
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/21 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_CloseECM_Tx(void)
{
	S1_EnableRTS(FALSE); /* RTSを無効にする */
	
	S1_HDLC_EnableTx(FALSE); /* 送信禁止 */
	S1_HDLC_TxSelectIdle(FALSE);
	
	S1_EnableDTC_Request(S1_DTC_NONE);
	S1_ClearDTC_Request(); /* DTC要求クリア */
	S1_DisableInterrupt(); /* S1割り込み禁止 */
	
	S1_HDLC_EnableTxDMA_Request(FALSE);
	S1_HDLC_EnableTxInterrupt(FALSE);
}

/**************************************************************************************************/
/**
	@brief		FPGAバージョン文字列を取得
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/09/09 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_GetFPGA_VersionString(
					UBYTE* pversion) /* バージョン文字列(出力 NULL終端 十分な大きさを確保すること) */
{
	UBYTE version;
	
	version = S1_GetFPGA_Version();
	
	CMN_UnsignedLongToHexASC_NULL(pversion, (UDWORD)version, 2, '0');
}





/**************************************************************************************************/
/**
	@brief		S1をソフトウェアリセットする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/08 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SoftwareReset(void)
{
	S1_REG_Reset = S1_REG_BIT_RST;
}

/**************************************************************************************************/
/**
	@brief		S1をハードウェアリセットする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/08 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HardwareReset(void)
{
	S1_REG_Reset = S1_REG_BIT_HRST;
}

/**************************************************************************************************/
/**
	@brief		S1割込みの種別を得る
	
	@li			
	@param		
	@return		割込み種別のビットアサイン
	@note		
	@date		2005/07/01 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_GetInterruptKind(void)
{
	UBYTE kind;
	
	kind = S1_REG_IntReqest;
	
	return kind;
}

/**************************************************************************************************/
/**
	@brief		S1割込みを有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/01 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_EnableInterrupt(void)
{
	S1_REG_IntMask = 0;
}

/**************************************************************************************************/
/**
	@brief		S1割込みを無効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/01 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_DisableInterrupt(void)
{
	S1_REG_IntMask = S1_REG_BIT_IMSK;
}

/**************************************************************************************************/
/**
	@brief		S1割り込みをクリアする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_ClearInterrupt(void)
{
	S1_REG_IntClear = S1_REG_BIT_ICLR;
}

/**************************************************************************************************/
/**
	@brief		DTC要求許可
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/20 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_EnableDTC_Request(
					UBYTE type) /* 種別 */
{
	switch (type) {
	case S1_DTC_NONE: /* なし */
		S1_REG_DTC_Enable = 0;
		break;
	case S1_DTC_RX_HDLC: /* HDLC受信 */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCRX_HDLC;
		break;
	case S1_DTC_TX_HDLC: /* HDLC送信 */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCTX_HDLC;
		break;
	case S1_DTC_RX_SCI: /* SCI受信 */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCRX_SCI;
		break;
	case S1_DTC_TX_SCI: /* SCI送信 */
		S1_REG_DTC_Enable = S1_REG_BIT_DTCTX_SCI;
		break;
	default:
		break;
	}
}

/**************************************************************************************************/
/**
	@brief		DTC要求クリア
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/20 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_ClearDTC_Request(void)
{
	S1_REG_DTC_Clear = S1_REG_BIT_DTCCLR;
}

/**************************************************************************************************/
/**
	@brief		SCI/HDLC切り替え
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/20 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SetMode(
			BOOL bhdlc) /* TRUE:HDLC FALSE:SCI */
{
	if (bhdlc == TRUE) {
		S1_REG_DTC_Mode = S1_REG_BIT_MODE;
	}
	else {
		S1_REG_DTC_Mode = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		RTSをセットする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SetRTS(
			UBYTE val) /* 0 or 1 */
{
	if (val == 0) {
		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENCDM | S1_REG_BIT_ENRSF);
	}
	else {
		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENCDM | S1_REG_BIT_ENRSF | S1_REG_BIT_RSF);
	}
#if 0
//	if (val == 0) {
//		S1_REG_MDM_ControlCommand = S1_REG_BIT_ENRSF;
//	}
//	else {
//		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENRSF | S1_REG_BIT_RSF);
//	}
#endif
}

#if 0
///**************************************************************************************************/
///**
//	@brief		RTS、RLSDを有効にする
//	
//	@li			
//	@param		
//	@return		なし
//	@note		
//	@date		2005/07/13 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//void S1_EnableRTS_RLSD(
//			BOOL benable) /* TRUE:有効 FALSE:無効 */
//{
//	if (benable == TRUE) {
//		S1_REG_MDM_ControlCommand = (S1_REG_BIT_ENCDM | S1_REG_BIT_ENRSF);
//	}
//	else {
//		S1_REG_MDM_ControlCommand = 0;
//	}
//}
#endif

/**************************************************************************************************/
/**
	@brief		RTSを有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_EnableRTS(
			BOOL benable) /* TRUE:有効 FALSE:無効 */
{
	if (benable == TRUE) {
		S1_REG_MDM_ControlCommand = S1_REG_BIT_ENRSF;
	}
	else {
		S1_REG_MDM_ControlCommand = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		RLSDを有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_EnableRLSD(
			BOOL benable) /* TRUE:有効 FALSE:無効 */
{
	if (benable == TRUE) {
		S1_REG_MDM_ControlCommand = S1_REG_BIT_ENCDM;
	}
	else {
		S1_REG_MDM_ControlCommand = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		RTSの値を得る
	
	@li			
	@param		
	@return		0 or 1
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_GetRTS(void)
{
	UBYTE val;
	
	if (S1_REG_MDM_ControlStatus & S1_REG_BIT_STAT_RSF) {
		val = 1;
	}
	else {
		val = 0;
	}
	
	return val;
}

/**************************************************************************************************/
/**
	@brief		CTSの値を得る
	
	@li			
	@param		
	@return		0 or 1
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_GetCTS(void)
{
	UBYTE val;
	
	if (S1_REG_MDM_ControlStatus & S1_REG_BIT_STAT_CSF) {
		val = 1;
	}
	else {
		val = 0;
	}
	
	return val;
}

/**************************************************************************************************/
/**
	@brief		RLSDの値を得る
	
	@li			
	@param		
	@return		0 or 1
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_GetRLSD(void)
{
	UBYTE val;
	
	if (S1_REG_MDM_ControlStatus & S1_REG_BIT_STAT_CDF) {
		val = 1;
	}
	else {
		val = 0;
	}
	
	return val;
}

/**************************************************************************************************/
/**
	@brief		TCF検知回路のフラグをクリアする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_TCF_Clear(void)
{
	S1_REG_MDM_TCF_Clear = (S1_REG_BIT_TCFCLR1 | S1_REG_BIT_TCFCLR2);
}

/**************************************************************************************************/
/**
	@brief		TCF検知回路のフラグを取得する
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/13 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_TCF_Detect(
			UBYTE* pflag1, /* フラグ1(出力) */
			UBYTE* pflag2) /* フラグ2(出力) */
{
	UBYTE reg;
	
	*pflag1 = 0;
	*pflag2 = 0;
	
	reg = S1_REG_MDM_TCF_Detect;
	
	if (reg & S1_REG_BIT_TCFDET1) {
		*pflag1 = 1;
	}
	if (reg & S1_REG_BIT_TCFDET2) {
		*pflag2 = 1;
	}
}

/**************************************************************************************************/
/**
	@brief		スクランブラの有効/無効セット
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/06/17 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SetScrambleAvailable(
					BOOL available) /* TRUE:有効にする FALSE:無効にする */
{
	UBYTE val;
	
	val = S1_REG_MDM_ConfigureS1;
	
	if (available == TRUE) {
		S1_REG_MDM_ConfigureS1 = (val & ~S1_REG_BIT_SC1);
	}
	else {
		S1_REG_MDM_ConfigureS1 = (val | S1_REG_BIT_SC1);
	}
}

/**************************************************************************************************/
/**
	@brief		スクランブラの有効/無効を取得
	
	@li			
	@param		
	@return		TRUE:  有効
				FALSE: 無効
	@note		
	@date		2005/08/23 作成
	@author		石橋正和
*/
/**************************************************************************************************/
BOOL S1_GetScrambleAvailable(void)
{
	UBYTE val;
	
	val = S1_REG_MDM_ConfigureS1;
	
	if (val & S1_REG_BIT_SC1) {
		return FALSE;
	}
	else {
		return TRUE;
	}
}

/**************************************************************************************************/
/**
	@brief		スクランブラの動作モード(専用/共通)セット
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SetScrambleMode(
					BOOL bsenyo) /* TRUE:専用 FALSE:個別 */
{
	UBYTE val;
	
	val = S1_REG_MDM_ConfigureS1;
	
	if (bsenyo == TRUE) {
		S1_REG_MDM_ConfigureS1 = (val | S1_REG_BIT_SC2);
	}
	else {
		S1_REG_MDM_ConfigureS1 = (val & ~S1_REG_BIT_SC2);
	}
}

/**************************************************************************************************/
/**
	@brief		S1をバイパスする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/11/17 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_BypassS1(
			BOOL bbypass) /* TRUE:バイパスする FALSE:バイパスしない */
{
	if (bbypass == TRUE) {
		S1_REG_MDM_BypassS1 |= S1_REG_BIT_BYPASS;
	}
	else {
		S1_REG_MDM_BypassS1 &= ~S1_REG_BIT_BYPASS;
	}
}

/**************************************************************************************************/
/**
	@brief		FPGAのバージョンを取得
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/09/09 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_GetFPGA_Version(void)
{
	UBYTE version;
	
	version = S1_REG_FPGA_Version;
	
	return version;
}

/**************************************************************************************************/
/**
	@brief		SCI 受信許可
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_EnableRx(
				BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_SCI_RxControl = S1_REG_BIT_SCI_RXEN;
	}
	else {
		S1_REG_SCI_RxControl = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		SCI 受信FIFOクリア
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_ClearRxFIFO(void)
{
	S1_REG_SCI_RxControl = S1_REG_BIT_SCI_RX_STCLR;
}

/**************************************************************************************************/
/**
	@brief		SCI 受信ステイタスクリア
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_ClearRxStatus(void)
{
	S1_REG_SCI_RxControl = S1_REG_BIT_SCI_RX_STCLR;
}

#if 0
///**************************************************************************************************/
///**
//	@brief		SCI OE(オーバーランエラー)クリア
//	
//	@li			
//	@param		
//	@return		なし
//	@note		
//	@date		2005/07/14 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//void S1_SCI_ClearRxOE(void)
//{
//	S1_REG_SCI_RxControl |= S1_REG_BIT_SCI_RX_STCLR;
//}
#endif

/**************************************************************************************************/
/**
	@brief		SCI 受信ステイタス取得
	
	@li			
	@param		
	@return		受信ステイタスのビットアサイン
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_SCI_GetRxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_SCI_RxStatus;
	
	return status;
}

#if 0
///**************************************************************************************************/
///**
//	@brief		SCI 受信データチェック
//	
//	@li			
//	@param		
//	@return		TRUE: 受信データあり FALSE:受信データなし
//	@note		
//	@date		2005/07/14 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckRxData(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_RxStatus & S1_REG_BIT_SCI_RXRDY) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
//
///**************************************************************************************************/
///**
//	@brief		SCI OE(オーバーランエラー)チェック
//	
//	@li			
//	@param		
//	@return		TRUE: OE発生 FALSE:OEなし
//	@note		
//	@date		2005/07/14 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckRxOE(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_RxStatus & S1_REG_BIT_SCI_OVE) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
#endif

/**************************************************************************************************/
/**
	@brief		SCI 送信許可
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_EnableTx(
				BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_SCI_TxControl = S1_REG_BIT_SCI_TXEN;
	}
	else {
		S1_REG_SCI_TxControl = 0;
	}
}

/**************************************************************************************************/
/**
	@brief		SCI アンダーランエラーを発生させる
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_SetTxUNE(void)
{
	S1_REG_SCI_TxControl = S1_REG_BIT_SCI_UNEND;
}

/**************************************************************************************************/
/**
	@brief		SCI 送信ステイタスクリア
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_ClearTxStatus(void)
{
	S1_REG_SCI_TxControl = S1_REG_BIT_SCI_TX_STCCLR;
}

/**************************************************************************************************/
/**
	@brief		SCI 送信ステイタス取得
	
	@li			
	@param		
	@return		送信ステイタスのビットアサイン
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_SCI_GetTxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_SCI_TxStatus;
	
	return status;
}

#if 0
//**************************************************************************************************/
///**
//	@brief		SCI 送信データチェック
//	
//	@li			
//	@param		
//	@return		TRUE: 送信データあり FALSE:送信データなし
//	@note		
//	@date		2005/07/14 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckTxData(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_TxStatus & S1_REG_BIT_SCI_TXEND) {
//		bret = FALSE;
//	}
//	else {
//		bret = TRUE;
//	}
//	return bret;
//}
//
///**************************************************************************************************/
///**
//	@brief		SCI アンダーランエラーチェック
//	
//	@li			
//	@param		
//	@return		TRUE: アンダーランエラー発生 FALSE:アンダーランエラーなし
//	@note		
//	@date		2005/07/14 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckTxUNE(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_TxStatus & S1_REG_BIT_SCI_UNE) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
//
///**************************************************************************************************/
///**
//	@brief		SCI 送信データ書き込み可否を得る
//	
//	@li			
//	@param		
//	@return		TRUE: 書き込み可 FALSE:書き込み不可
//	@note		
//	@date		2005/07/14 作成
//	@author		石橋正和
//*/
///**************************************************************************************************/
//BOOL S1_SCI_CheckTxDataReady(void)
//{
//	BOOL bret;
//	
//	if (S1_REG_SCI_TxStatus & S1_REG_BIT_SCI_TXRDY) {
//		bret = TRUE;
//	}
//	else {
//		bret = FALSE;
//	}
//	return bret;
//}
#endif

/**************************************************************************************************/
/**
	@brief		SCI 割り込み、DTCの条件を設定する
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_SCI_SetIntDTC_Enabled(
						UBYTE bits) /* 有効にする条件のビットアサイン */
{
	S1_REG_SCI_IntDTC_Enable = bits;
}

/**************************************************************************************************/
/**
	@brief		SCI 割り込み要因を得る
	
	@li			
	@param		
	@return		割り込み要因のビットアサイン
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_SCI_GetIntFactor(void)
{
	UBYTE ret;
	
	ret = S1_REG_SCI_IntRequest;
	
	return ret;
}

/**************************************************************************************************/
/**
	@brief		HDLC 生成多項式の初期化
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_InitializeCRC(void)
{
	S1_REG_HDLC_SelectCRC = 0x1C; /* CCITT(x^16 + x^12 + x^5 + 1) */
}

/**************************************************************************************************/
/**
	@brief		HDLC 転送モードの初期化
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/14 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_InitializeTransMode(void)
{
	S1_REG_HDLC_TransMode = 0;
}

/**************************************************************************************************/
/**
	@brief		HDLC 受信ステータスを得る
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetRxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_HDLC_RxStatus0;
	
	return status;
}

/**************************************************************************************************/
/**
	@brief		HDLC 最終受信データの端数ビット数を得る
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetRxRemainedBitNum(void)
{
	UBYTE num;
	
	num = S1_REG_HDLC_RxStatus1;
	
	return num;
}

/**************************************************************************************************/
/**
	@brief		HDLC 受信許可
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_EnableRx(
				BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_HDLC_RxControl |= S1_REG_BIT_HDLC_RXE;
	}
	else {
		S1_REG_HDLC_RxControl &= ~S1_REG_BIT_HDLC_RXE;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 受信ステイタスクリア
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_ClearRxStatus(void)
{
	S1_REG_HDLC_RxControl |= S1_REG_BIT_HDLC_STC;
}

/**************************************************************************************************/
/**
	@brief		HDLC 受信 割り込み、DTCの条件を設定する
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_SetRxIntDTC_Enabled(
						UBYTE bits) /* 有効にする条件のビットアサイン */
{
	S1_REG_HDLC_RxIntPermit = bits;
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信ステータスを得る
	
	@li			
	@param		
	@return		送信ステータスのビットアサイン
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetTxStatus(void)
{
	UBYTE status;
	
	status = S1_REG_HDLC_TxStatus;
	
	return status;
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信ステータスをクリアする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_ClearTxStatus(
					UBYTE status) /* クリアするステイタスのビットアサイン */
{
	S1_REG_HDLC_TxStatus &= (~status);
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信許可
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_EnableTx(
				BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_TXE;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_TXE;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信 出力レベルを強制的に"H"にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_TxSendHighLevel(
						BOOL benable) /* TRUE:強制"H" FALSE:戻す */
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_SH;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_SH;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信 出力レベルを強制的に"L"にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_TxSendBreak(
					BOOL benable) /* TRUE:強制"L" FALSE:戻す */
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_SB;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_SB;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信 ???
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_TxSelectIdle(
					BOOL benable)
{
	if (benable == TRUE) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_IDLS;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_IDLS;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信部をリセットする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_RestTx(void)
{
	S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_TXRST;
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信 アボートを送信する
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_TxSendAbort(void)
{
	S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_SA;
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信 最終フレームを指定
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_TxLast(
				UBYTE val) /* 0 or 1 */
{
	if (val == 1) {
		S1_REG_HDLC_TxControl |= S1_REG_BIT_HDLC_TXLAST;
	}
	else {
		S1_REG_HDLC_TxControl &= ~S1_REG_BIT_HDLC_TXLAST;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信 割り込み、DTCの条件を設定する
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_SetTxIntDTC_Enabled(
						UBYTE bits) /* 有効にする条件のビットアサイン */
{
	S1_REG_HDLC_TxIntPermit = bits;
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信モードレジスタ初期化
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_InitializeTxMode(void)
{
	S1_REG_HDLC_TxMode = S1_REG_BIT_HDLC_TXUEND;
}

/**************************************************************************************************/
/**
	@brief		HDLC 割込み、DMA要求の状態を取得する
	
	@li			
	@param		
	@return		各種要求のビットアサイン
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
UBYTE S1_HDLC_GetRequestStatus(void)
{
	UBYTE status;
	
	status = S1_REG_HDLC_Request;
	
	return status;
}

/**************************************************************************************************/
/**
	@brief		HDLC 受信割り込みを有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_EnableRxInterrupt(
					BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MRX;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MRX;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 受信DMA要求を有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_EnableRxDMA_Request(
							BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MRXDRQ;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MRXDRQ;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信割り込みを有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_EnableTxInterrupt(
							BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MTX;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MTX;
	}
}

/**************************************************************************************************/
/**
	@brief		HDLC 送信DMA要求を有効にする
	
	@li			
	@param		
	@return		なし
	@note		
	@date		2005/07/19 作成
	@author		石橋正和
*/
/**************************************************************************************************/
void S1_HDLC_EnableTxDMA_Request(
							BOOL benable) /* TRUE:許可 FALSE:禁止 */
{
	if (benable == TRUE) {
		S1_REG_HDLC_Mask &= ~S1_REG_BIT_HDLC_MTXDRQ;
	}
	else {
		S1_REG_HDLC_Mask |= S1_REG_BIT_HDLC_MTXDRQ;
	}
}

