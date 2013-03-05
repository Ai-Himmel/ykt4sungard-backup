/*
 *  \src\atlanta\define\dma_pro.h   T.Nose 1996/11/12
 *  Ãﬂ€ƒ¿≤ÃﬂêÈåæ
 */
/********** \src\atlanta\src\dma_dbca.c **********/
#if (PRO_EX_CLASS1 == ENABLE)	/* S.Fukui June 19,1998  */
#include "\src\atlanta\define\cl1expro.h"
#endif
#if (PRO_EXT_DMAC == ENABLE)
UDWORD CheckDMAU_DBA_DCA(void);
void SetDMAU_DBA_DCA(UDWORD  address);
UDWORD DMA_CheckDMA_BaseAddress(UBYTE channel);
UDWORD DMA_CheckDMA_CurrentAddress(UBYTE  channel);
void DMA_SetDMA_BaseAddress(UBYTE  channel,UDWORD  address);
void DMA_SetDMA_BaseCurrentAddress(UBYTE  channel,UDWORD  address);
void DMA_SetDMA_BaseCurrentAddress(UBYTE  channel,UDWORD address);
#endif
/********** \src\kobe\atlanta\src\dma_dbcc.c **********/
#if (PRO_EXT_DMAC == ENABLE)
UWORD CheckDMAU_DBC_DCC(void);
void  SetDMAU_DBC_DCC(UWORD  data);
UWORD DMA_CheckDMA_BaseCounter(UBYTE  channel);
UWORD DMA_CheckDMA_CurrentCounter(UBYTE  channel);
void  DMA_SetDMA_BaseCounter(UBYTE  channel,UWORD  count);
void  DMA_SetDMA_BaseCurrentCounter(UBYTE  channel,UWORD  count);
#endif
/********** \src\atlanta\src\dma_dch.c **********/
#if (PRO_EXT_DMAC == ENABLE)
UBYTE CheckDMAU_DCH(void);
void  SetDMAU_DCH(UBYTE  data);
UBYTE CheckDMA_Channel(void);
UBYTE CheckDMA_AccessMethod(void);
void  SetDMA_Channel(UBYTE  channel);
void  SetDMA_AccessMethod(UBYTE  method);
#endif
/********** \src\atlanta\src\dma_ddc.c **********/
#if (PRO_EXT_DMAC == ENABLE)
UWORD CheckDMAU_DDC(void);
void  SetDMAU_DDC(UWORD data);
void  DMA_V53DMAU_Enable(void);
void  DMA_V53DMAU_Disable(void);
#endif
/********** \src\atlanta\src\dma_dmd.c **********/
#if (PRO_EXT_DMAC == ENABLE)
UBYTE CheckDMAU_DMD(void);
void  SetDMAU_DMD(UBYTE  data);
void  DMA_SetV53DMA_Unit(UBYTE  channel,UBYTE  unit);
void	DMA_V53_AutoInitializeEnable(UBYTE channel);
void	DMA_V53_AutoInitializeDisable(UBYTE channel);
void  DMA_SetV53DMA_Direction(UBYTE  channel,UBYTE  dir);
void  DMA_SetV53DMA_Mode(UBYTE  channel,UBYTE  mode);
#endif
/********** \src\atlanta\src\dma_dmk.c **********/
#if (PRO_EXT_DMAC == ENABLE)
UBYTE CheckDMAU_DMK(void);
void  SetDMAU_DMK(UBYTE  data);
void  DMA_RequestMaskExternalDMAU(UBYTE  channel);
void  DMA_RequestEnableExternalDMAU(UBYTE  channel);
#endif
/********** \src\atlanta\src\dma_dst.c **********/
#if (PRO_EXT_DMAC == ENABLE)
UBYTE CheckDMAU_DST(void);
#endif
/********** \src\atlanta\src\dma_stup.c **********/
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
void  DMA_SetupDMAU(struct  DMA_Data_t *dma);
void  DMA_RestartDMAU(UBYTE channel, UBYTE direction, UWORD count, UDWORD address);
#endif
#if (PRO_EXT_DMAC == ENABLE)
void  DMA_RestartExternalDMAU(UBYTE channel,UWORD count,UDWORD address);
#endif
UBYTE	DMA_ChannelCheck(UBYTE channel);
/********** \src\kobe\anzu\v53\def_v\dma_tbl.c **********/
/********** \src\kobe\anzu\v53\def_v\dma_data.c **********/

/********** \src\atlanta\src\dma_ini.c ******************/
#if (PRO_EXT_DMAC == ENABLE)
void INI_ExternalDMAC(void);
#endif
/********** \src\atlanta\src\dma_func.c ******************/
void	DMA_SetDMA_Address(UBYTE channel,UBYTE direction,UDWORD address);
#if (PRO_EX_CLASS1 == DISABLE)	/* S.Fukui June 19,1998  */
UDWORD	DMA_CheckDMA_Address(UBYTE channel,UBYTE direction);
UWORD	DMA_CheckDMA_Counter(UBYTE channel);
void	DMA_RequestMask(UBYTE channel);
void	DMA_RequestEnable(UBYTE channel);
#endif

void	DMA_SetDMA_Counter(UBYTE channel,UWORD count);
void	DMA_SetDMA_Unit(UBYTE channel,UBYTE unit);
void	DMA_SetDMA_Direction(UBYTE channel,UBYTE direciton);
void	DMA_AutoInitializeEnable(UBYTE channel);
void	DMA_AutoInitializeDisable(UBYTE channel);
UBYTE	DMA_CheckDreq(UBYTE channel);
void DMA_SetDMA_DstSrcAddress(UBYTE channel, UBYTE direction, UDWORD dst_address, UDWORD src_address);
void DMA_Continue(UBYTE); /* added by H.Kubo 1998/11/20 */

#if defined(POPLAR_F)
void DMA_RequestEnableSub(UBYTE channel);
#endif

/********** \src\atlanta\sh7043\src\dma_sh.c ******************/
void	DMA_SH_StartDMAU(void);
void	DMA_SH_StopDMAU(void);
void	DMA_SetSH_Address(UBYTE channel,UBYTE direction,UDWORD address);
void	DMA_SetSH_SAR(UBYTE channel,UDWORD address);
void	DMA_SetSH_DAR(UBYTE channel,UDWORD address);
UDWORD	DMA_CheckSH_Address(UBYTE channel,UBYTE direction);
UDWORD	CheckDMAU_SH_SAR(UBYTE channel);
UDWORD	CheckDMAU_SH_DAR(UBYTE channel);
void	DMA_SetSH_Counter(UBYTE channel,UDWORD counter);
void	DMA_SetSH_TCR(UBYTE channel,UDWORD counter);
UDWORD	DMA_CheckSH_Counter(UBYTE channel);
void	DMA_SetSH_Unit(UBYTE channel,UBYTE unit);
void	DMA_SetSH_CHCR_Unit(UBYTE channel,UBYTE unit);
void	DMA_SetSH_CH0_Unit(UBYTE unit);
void	DMA_SetSH_CH1_Unit(UBYTE unit);
void	DMA_SetSH_CH2_Unit(UBYTE unit);
void	DMA_SetSH_CH3_Unit(UBYTE unit);
void	DMA_SetSH_Direction(UBYTE channel,UBYTE direction);
void	DMA_SetSH_CHCR_Direction(UBYTE channel,UBYTE direction);
void	DMA_SetSH_CH0_Direction(UBYTE direction);
void	DMA_SetSH_CH1_Direction(UBYTE direction);
void	DMA_SetSH_CH2_Direction(UBYTE direction);
void	DMA_SetSH_CH3_Direction(UBYTE direction);
void	DMA_RequestMaskInternalDMAU(UBYTE channel);
void	DMA_RequestEnableInternalDMAU(UBYTE channel);
void	DMA_RestartInternalDMAU(UBYTE channel,UBYTE direction,UDWORD count,UDWORD address);
void	DMA_SH_AutoInitializeEnable(UBYTE channel);
void	DMA_SH_AutoInitializeDisable(UBYTE channel);
void	DMA_SetSH_DstSrcAddress(UBYTE channel, UBYTE direction, UDWORD dst_address, UDWORD src_address);
void	DMA_MemoryToMemory_TC_Interrupt(void);
UBYTE	DMA_IsTheAddressInInternalRAM(UDWORD address); /* added by H.Kubo for SAKAKI 1998/08/10 */
void DMA_ContinueInternalDMAU(UBYTE channel); /* added by H.Kubo 1998/11/20 */

#if defined(POPLAR_F)
void DMA_RequestEnableInternalDMAUSb(UBYTE channel);
void DMA_RequestEnableInternalDMAUGo(UBYTE channel);
#endif
/********** \src\atlanta\sh7043\src\dma_dtc.c ******************/
void	DMA_SetupDTC(struct DMA_DTC_Data_t *setup);
void	DMA_SetupIntDTC(struct DMA_DTC_Data_t *setup);
void	DMA_SetupBlockDTC(struct DMA_DTC_Data_t *setup);
void	DMA_SetupNormalDTC(struct DMA_DTC_Data_t *setup);
void	DMA_SetupRepeatDTC(struct DMA_DTC_Data_t *setup);
void	DMA_SetupIntDTC2(struct DMA_DTC_Data_t *setup);
void	DMA_DTC_TransferStart(UBYTE mode);
UWORD	DMA_DTC_CheckCounter(UBYTE channel);
UDWORD	DMA_DTC_CheckAddress(UBYTE channel, UBYTE direction);
UDWORD	DMA_DTC_CheckDstAddress(UBYTE channel);
UDWORD	DMA_DTC_CheckSrcAddress(UBYTE channel);
UWORD	DMA_DTC_CheckDTCRB(void);
UDWORD	DMA_DTC_CheckDTIAR(void);
void	DMA_DTC_Interrupt(void);
void	DTC_TC_MDM_Interrupt(void);
void	DMAtoDTC_SetupDTC(struct DMA_Data_t *dma_setup_data);
void	DMAtoDTC_Restart(UBYTE dtc_mode,UBYTE direction,UWORD count,UDWORD address);
void	DMAtoDTC_RequestMask(UBYTE dtc_mode);
void	DMAtoDTC_RequestEnable(UBYTE dtc_mode);
void 	DMA_DTC_Initialize(void);
void 	DMA_SetupIntDTC_IRQ(struct DMA_DTC_Data_t *setup);
void	DMAtoDTC_Convert(struct DMA_DTC_Data_t *dtc_ptr, struct DMA_Data_t *dma_ptr);
UBYTE	DMAtoDTC_ChannelConvert(UBYTE channel);
void 	DTC_SCN_DRAM_Interrupt(void);
void 	DTC_DRAM_PRN_Interrupt(void);
void 	DTC_MDMBUF_MDM_Interrupt(void);
void 	DTC_MDM_MDMBUF_Interrupt(void);
void	DTC_GateArrayWriteInterrupt(void); /* 1998/10/26 by T.Soneoka */
void DMA_DTC_SetAddress(UBYTE channel, UBYTE direction, UDWORD address); /* added by H.Kubo 1998/07/16 */
void DMA_DTC_SetDstAddress(UBYTE channel, UDWORD address); /* added by H.Kubo 1998/07/16 */
void DMA_DTC_SetSrcAddress(UBYTE channel, UDWORD address);  /* added by H.Kubo 1998/07/16 */
void DMA_DTC_SetCounter(UBYTE channel, UWORD count); /* added by H.Kubo 1998/07/16 */
void DMA_DTC_SetUnit(UBYTE channel, UBYTE unit);  /* added by H.Kubo 1998/07/16 */
void DMA_DTC_InitializeCounter(void); /* added by H.Kubo 1998/11/19 */

