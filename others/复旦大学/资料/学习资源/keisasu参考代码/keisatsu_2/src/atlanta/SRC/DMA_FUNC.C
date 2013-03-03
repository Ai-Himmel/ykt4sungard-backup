/************************************************************************
*               BY:  T.Nose
*             DATE:  1996/11/09
*        FILE NAME:  dma_sub.c
*       Task ID No:
*      DESCRIPTION:  タスクからコールするDMACのインターフェース関数
*  PUBLIC ROUTINES:  void DMA_RequestMask(UBYTE channel)
* PRIVATE ROUTINES:
*        REFERENCE:
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\std.h"


/*************************************************************************
	module		:[引数のチャンネルのDMA転送開始アドレスをセットします]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetDMA_Address(UBYTE channel,		/* チャンネル */
						UBYTE direction,	/* 転送方向 */
						UDWORD address)		/* 転送開始アドレス */
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SetSH_Address(channel,direction,address);
	}
	else {
		DMA_SetDMA_BaseCurrentAddress((channel - DMA_INTERNAL_CH_MAX),address);
	}
#else
 #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_SetSH_Address(channel,direction, address);
	}
	else {
		DMA_DTC_SetAddress(channel,direction, address);	/* DTCを使用する場合 */
	}
 #else
	DMA_SetSH_Address(channel,direction,address);
 #endif
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのDMA転送アドレスを読み出します]
	function	:[
		1.
	]
	return		:[転送アドレス]
	common		:[なし]
	condition	:[]
	comment		:[
		DMA_IO_TO_MEMORY/DMA_MEMORY_TO_IO のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UDWORD DMA_CheckDMA_AddressFlsRom(UBYTE channel,		/* チャンネル */
								  UBYTE direction)		/* 転送方向 */
#else
UDWORD DMA_CheckDMA_Address(UBYTE channel,		/* チャンネル */
							UBYTE direction)	/* 転送方向 */
#endif
{
	UWORD int_enable;
	UDWORD ret_val;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		ret_val = DMA_CheckSH_Address(channel,direction);
	}
	else {
		ret_val = DMA_CheckDMA_CurrentAddress(channel - DMA_INTERNAL_CH_MAX);
	}
#else
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		ret_val = DMA_CheckSH_Address(channel,direction);
	}
	else {
  #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		ret_val = DMA_DTC_CheckAddress(channel,direction);	/* DTCを使用する場合 */
  #else
		if (channel == DMA_MDM_MDMBUF_CH) {
			channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
		}
		else if (channel == DMA_MPC_MPCBUF_CH) {
			channel = DTC_INTERRUPT_CH2;	/* CLASS1 */
		}
		ret_val = DMA_DTC_CheckAddress(channel,direction);	/* DTCを使用する場合 */
  #endif
	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
	return(ret_val);
}


/*************************************************************************
	module		:[引数のチャンネルのDMA転送回数をセットします]
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
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetDMA_Counter(UBYTE channel,	/* チャンネル */
						UWORD count)	/* 転送回数 */
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SetSH_Counter(channel,(UDWORD)count);
	}
	else {
		DMA_SetDMA_BaseCurrentCounter((channel - DMA_INTERNAL_CH_MAX),count - 1);
	}
#else

 #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_SetSH_Counter(channel, (UDWORD) count);
	}
	else {
		DMA_DTC_SetCounter(channel, count);	/* DTCを使用する場合 */
	}
 #else
	DMA_SetSH_Counter(channel,(UDWORD)count);
 #endif
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのDMA転送回数を読み出します]
	function	:[
		1.
	]
	return		:[
		n>=0:残りのDMA転送回数
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
UWORD DMA_CheckDMA_CounterFlsRom(UBYTE channel)	/* チャンネル */
#else
UWORD DMA_CheckDMA_Counter(UBYTE channel)	/* チャンネル */
#endif
{
	UWORD int_enable;
	UWORD ret_val;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		ret_val = (UWORD)DMA_CheckSH_Counter(channel);
	}
	else {
		ret_val = (DMA_CheckDMA_CurrentCounter(channel - DMA_INTERNAL_CH_MAX) + 1);
	}
#else
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		ret_val = (UWORD)DMA_CheckSH_Counter(channel);
	}
	else {
  #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		ret_val = DMA_DTC_CheckCounter(channel);	/* DTCを使用する場合 */
  #else
		if (channel == DMA_MDM_MDMBUF_CH) {
			channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
		}
		else if (channel == DMA_MPC_MPCBUF_CH) {
			channel = DTC_INTERRUPT_CH2;	/* CLASS1 */
		}
		ret_val = DMA_DTC_CheckCounter(channel);	/* DTCを使用する場合 */
  #endif
	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
	return(ret_val);
}


/*************************************************************************
	module		:[引数のチャンネルのDMA転送単位を設定します]
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
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetDMA_Unit(UBYTE channel,	/* チャンネル */
					UBYTE unit)	/* 転送単位 */
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SetSH_Unit(channel,unit);
	}
	else {
		DMA_SetV53DMA_Unit((channel - DMA_INTERNAL_CH_MAX),unit);
	}
#else

 #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_SetSH_Unit(channel, unit);
	}
	else {
		DMA_DTC_SetUnit(channel, unit);	/* DTCを使用する場合 */
	}
 #else
	DMA_SetSH_Unit(channel,unit);
 #endif
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのDMA転送方向を設定します]
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
	date		:[1996/11/12]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_SetDMA_Direction(UBYTE channel,	/* チャンネル */
						UBYTE direction)	/* 転送方向 */
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SetSH_Direction(channel,direction);
	}
	else {
		DMA_SetV53DMA_Direction((channel - DMA_INTERNAL_CH_MAX),direction);
	}
#else
 #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
	DMA_SetSH_Direction(channel,direction);
	}
	else { /* DTC の場合 */
		/* DTC では、特に設定することはありません。 でも、この引数で内蔵 DMA の設定関数を読んではいけません。*/
	}
 #else
	DMA_SetSH_Direction(channel,direction);
 #endif
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのDMARQをマスクします]
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
	date		:[1996/11/09]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void DMA_RequestMaskFlsRom(UBYTE channel)		/*マスクするチャンネル*/
#else
void DMA_RequestMask(UBYTE channel)		/*マスクするチャンネル*/
#endif
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_RequestMaskInternalDMAU(channel);
	}
	else {
		DMA_RequestMaskExternalDMAU(channel - DMA_INTERNAL_CH_MAX);
	}
#else
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_RequestMaskInternalDMAU(channel);
	}
	else {
  #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		DMAtoDTC_RequestMask(channel);
  #else
		if (channel == DMA_MDM_MDMBUF_CH) {
			channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
		}
		else if (channel == DMA_MPC_MPCBUF_CH) {
			channel = DTC_INTERRUPT_CH2;	/* CLASS1 */
		}
		DMAtoDTC_RequestMask(channel);
  #endif
	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのDMARQを有効にします]
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
	date		:[1996/11/09]
	author		:[野瀬敏弘]
*************************************************************************/
#if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui Jun 19,1998  */
void DMA_RequestEnableFlsRom(UBYTE channel)	/*有効にするチャンネル*/
#else
void DMA_RequestEnable(UBYTE channel)	/*有効にするチャンネル*/
#endif
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_RequestEnableInternalDMAU(channel);
	}
	else {
		DMA_RequestEnableExternalDMAU(channel - DMA_INTERNAL_CH_MAX);
	}
#else
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_RequestEnableInternalDMAU(channel);
	}
	else {
  #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		DMAtoDTC_RequestEnable(channel);
  #else
		if (channel == DMA_MDM_MDMBUF_CH) {
			channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
		}
		else if (channel == DMA_MPC_MPCBUF_CH) {
			channel = DTC_INTERRUPT_CH2;	/* CLASS1 */
		}
		DMAtoDTC_RequestEnable(channel);
  #endif
	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのオートイニシャライズを有効にします]
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
	date		:[1996/12/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_AutoInitializeEnable(UBYTE channel)
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */

#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SH_AutoInitializeEnable(channel);
	}
	else {
		DMA_V53_AutoInitializeEnable(channel);
	}
#else
	DMA_SH_AutoInitializeEnable(channel);
#endif

	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}


/*************************************************************************
	module		:[引数のチャンネルのオートイニシャライズを禁止します]
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
	date		:[1996/12/11]
	author		:[野瀬敏弘]
*************************************************************************/
void DMA_AutoInitializeDisable(UBYTE channel)
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */

#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SH_AutoInitializeDisable(channel);
	}
	else {
		DMA_V53_AutoInitializeDisable(channel);
	}
#else
	DMA_SH_AutoInitializeDisable(channel);
#endif

	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}

#if (PRO_MODEM == R288F)
/*************************************************************************
	module		:[引数のチャンネルの外部割込み要求を有無を調べます。]
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
	date		:[1998/01/29]
	author		:[久保博]
*************************************************************************/
UBYTE DMA_CheckDreq(UBYTE channel)
{
	UBYTE stat;
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		return 0;
	}
	else {
		stat = CheckDMAU_DST();
		return stat & (1 << (channel - DMA_INTERNAL_CH_MAX) + 4);
	}
#else
	return 0;
#endif
}
#endif



#if (PRO_MODEM == R288F) /* by H.Kubo 1998/01/29 */
/*************************************************************************
	module		:[引数のチャンネルのDMA転送開始アドレスをセットします]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[
		MEMORY_TO_MEMORY のみ対応
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/01/29]
	author		:[久保博]
*************************************************************************/
void DMA_SetDMA_DstSrcAddress(UBYTE channel,		/* チャンネル */
						UBYTE direction,	/* 転送方向 */
						UDWORD dst_address,
						UDWORD src_address)		/* 転送開始アドレス */
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_SetSH_DstSrcAddress(channel,direction,dst_address, src_address);
	}
	else {
		/* DMA_SetDMA_BaseCurrentAddress((channel - DMA_INTERNAL_CH_MAX),address); */
	}
#else
	DMA_SetSH_DstSrcAddress(channel,direction,dst_address, src_address);
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}
#endif /* (PRO_MODEM == R288F) */

#if  (PRO_DTC_INT_TYPE == DTC_INT_SAKAKI) /* added by H.Kubo 1998/11/19 */
/*************************************************************************
	module		:[引数のチャンネルのDMA転送を継続]
	function	:[
		DMA 転送途中で止まった時、止まったアドレス、カウンタから継続させます。
		再起動で、時間がかかりすぎるので、サカキ用に作りました。
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1998/11/19]
	author		:[久保博]
*************************************************************************/
void DMA_Continue(UBYTE channel)	/*有効にするチャンネル*/
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */
#if (PRO_EXT_DMAC == ENABLE)
	if (channel < DMA_INTERNAL_CH_MAX) {
		DMA_ContinueInternalDMAU(channel);
	}
	else {
		DMA_RequestEnableExternalDMAU(channel - DMA_INTERNAL_CH_MAX);
	}
#else
	if (DMA_ChannelCheck(channel) == YES) {	/* ＤＭＡを使用する場合 */
		DMA_ContinueInternalDMAU(channel);
	}
	else {
	/* DTC の DMAtoDTC_RequestEnable() 関数は、アドレス、カウンタは前のままで起動するので、このままにします。 1998/11/19 */
  #if (PRO_DTC_INT_SYSTEM == ENABLE)				/* 割り込み要因DTCを汎用的に使用できる 1998/08/31 H.Yoshikawa */
		DMAtoDTC_RequestEnable(channel);
  #else
		if (channel == DMA_MDM_MDMBUF_CH) {
			channel = DTC_INTERRUPT_CH;	/* 取り敢えずモデムとモデムバッファ間では割り込み起動をセットする */
		}
		else if (channel == DMA_MPC_MPCBUF_CH) {
			channel = DTC_INTERRUPT_CH2;	/* CLASS1 */
		}
		DMAtoDTC_RequestEnable(channel);
  #endif
	}
#endif
	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}
#endif


#if defined(POPLAR_F)
/*************************************************************************
	module		:[引数のチャンネルのDMARQを有効にします]
	function	:[
		1.モデム専用
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[DMA]
	date		:[1999/12/06]
	author		:[村田]
*************************************************************************/
void DMA_RequestEnableSub(UBYTE channel)	/*有効にするチャンネル*/
{
	UWORD int_enable;

	int_enable = CheckInterruptEnable();	/* 現在の割り込み禁止状態を調べる 1=割り込み許可状態 : 0=割り込み禁止状態 */
	CMN_DisableInterrupt();	/* 割り込み禁止 */

	DMA_RequestEnableInternalDMAUSb(channel);

	if (int_enable) {	/* 割り込み禁止に変更時、割り込み許可中だった*/
		CMN_EnableInterrupt();	/*割り込み許可*/
	}
}
#endif
