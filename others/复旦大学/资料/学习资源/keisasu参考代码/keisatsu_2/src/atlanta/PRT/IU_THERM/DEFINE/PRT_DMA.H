/*
 *	@(#)%Id%
 *	FileName:	//jason/home2/prj/Eva/Src/inc/prt_dma.h
 *	Create:	Wed Apr 15 14:40:45 1998	by	ishiyama
 *	Description:
 *		Printer DMA Header File
 *	Change Log:
 *		
 */
#ifndef	PRT_DMA_H
#define PRT_DMA_H

/*
 *	DMAC Channel
 */
struct Dmac {
	volatile UDWORD	*Sar;				/* Source Address Register */
	volatile UDWORD	*Dar;				/* Destination Address Register */
	volatile UDWORD	*Tcr;				/* Transfer Count Register */
	volatile UDWORD	*Chcr;				/* Channel Control Register */
};

/*
 *	Function Prototypes
 */
void	DisablePrinterDmac(void);
void	EnablePrinterDmac(void);
void	ClearPrinterDmac(void);
void SetupPrinterDmac(
	UWORD	*SrcAddress,
	UWORD	*DstAddress,
	UDWORD	Count);
BOOL	CheckDmaTE(void);
void	StartPrinterDma(void);
void	RestartPrinterDma(void);
UWORD	*ReadPrinterDmaCurrentAddress(void);
UWORD	ReadPrinterDmaCurrentCounter(void);

#endif /* PRT_DMA_H */
