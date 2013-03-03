/************************************************************************
*	System		: SAKAKI
*	File Name	: PRN_DATA.H
*	Author		: K.Kawata
*	Date		: 1998/6/23
*	Description	:
*	Maintenance	:
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmcopy.h"
#include "\src\atlanta\define\sysmemrx.h"
#include "\src\atlanta\define\syslifem.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\dma_blk.h"
#include "\src\atlanta\define\message.h"
/* #include "\src\atlanta\prt\thermal\define\prn_stat.h" */
/* #include "\src\atlanta\prt\thermal\define\prn_def.h" */
#include "\src\atlanta\define\syscph.h"
#include "\src\atlanta\define\sysdoc.h"
#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\define\scd.h"
#else
	#include "\src\atlanta\scd\define\scd.h"
#endif


/*----------------------------------*/
/* プリンタードライバー制御テーブル */
/*----------------------------------*/
/*POPLAR_H のためのﾀﾞﾐｰ*/
struct PRN_ReductionData_t {
	UWORD	MainReduction;		/* 主走査方向の拡大/縮小(拡大/等倍/縮小) */
	UWORD	CDCMainReduction;	/* 主走査方向のCODECでの倍率 */
	UWORD	SubReduction;		/* 副走査方向の拡大/縮小(拡大/等倍/縮小) */
	UWORD	CDCSubReduction;	/* 副走査方向のCODECでの倍率 */
	UBYTE	CDCSubLineCount;	/* 副走査方向のCODECでの倍率に伴う1回にデコードできるライン数 */
	UBYTE	GAReduction;		/* スムージングのゲートアレイでの倍率 */
	UBYTE	GA_H_Reduction;		/* 主走査方向のゲートアレイでの倍率 */
	UBYTE	GA_V_Reduction;		/* 副走査方向のゲートアレイでの倍率 */
	UWORD	CDC_H_Reduction;	/* コーデック主走査倍率 */
	UWORD	CDC_V_Reduction;	/* コーデック副走査倍率 */
};

struct PrintStatusTimeData_t {
	UBYTE	Status;
	UWORD	Time[7];
};



extern	struct	SYS_MultiCopyData_t	*McopyPtr;
extern	struct	SYS_MemoryRxPrintData_t	*MRxPtr;
extern	UBYTE	PRN_1PageReceived;
extern	UBYTE	CutToPrintExecFlag;

extern	MESSAGE_t	PrinterEndMessage;
extern struct	WorkBuf_t	PRN_RL1;
extern struct	WorkBuf_t	PRN_RL2;
extern struct	WorkBuf_t *DecodeA_buffer;
extern struct	WorkBuf_t *DecodeB_buffer;
extern struct	CdcBlk_t PrintDecodeData;
extern struct	Buf_p_t PrnRp;
extern struct	MEM_IndexData_t PrintIndex;
extern struct	MEM_ExecData_t  PrintExecReadData;
extern	UBYTE	PRN_PrintModeCount;
extern	UBYTE	PrintModeCountWork;
extern	UBYTE	DecodeWaitFlag;
extern	UBYTE	DecodeWaitCommandFlag;
extern	struct	reduction_t	PRN_LineSkipData;
extern	UWORD	PRN_OriginalImageSize;
extern	UWORD	PRN_ReductionImageSize;
extern	UBYTE	PreheatContCount;
extern	UBYTE	PreheatContCountSCN;
extern	UBYTE	PreheatStopCount;
extern	UBYTE	PreheatStopCountSCN;
extern	UBYTE	PRN_ResonanceStopCount;

#if (0)
** /* 以下はSAKAKIで使用している変数達です。
** ** HINOKIでは不要なのでコメントにします。
** ** 必要に応じて戻してやってください。
** ** By O.Kimoto 1998/10/27
** */
** /* extern	UWORD	StoreDocumentPrintResult; */
** /* extern	UBYTE	HeatPulseOffSet; */
** /* extern	UBYTE	HeatPulseHeadRank;*/
** /* extern	UBYTE	DebugHsyncCount; */
** /* extern	UBYTE	PrintType; */
** /* extern	UBYTE	PrintingType; */
** /* extern	UWORD	Doc_ChkMsgReturnValue; */
** /* extern	UBYTE	PRN_StartPrintFlag; */
** /* extern	UBYTE	PRN_EndPrintFlag; */
** /* extern	UBYTE	PRN_FirstPrintFlag; */
** /* extern	UBYTE	ps2_off_count; */
** /* extern	UBYTE	ps2_off_flag; */
** /* extern	UBYTE	PRN_DFA4B4Sensor; */
** /* extern	UBYTE	PRN_LineMemoryStatus; */
** /* extern	UWORD	ThermisterValue; */
** /* extern	UWORD	PaperMargin; */
** /* extern	UBYTE	PRN_PB4Sensor; */
** /* extern	UBYTE	PRN_OpenCount; */
** /* extern	UBYTE	PrnMotorPhase; */
** /* extern	UWORD	ImageLineReadPoint; */
** /* extern	UWORD	ImageLineWritePoint; */
** /* extern	UWORD	ImageLineStartPoint; */
** /* extern	UBYTE	ReadPointWaitFlag; */
** /* extern	struct	DMA_Data_t	PRN_LineDMA; */
** /* extern	UWORD	SMCR_StatusPRN_Dummy; */
** /* extern	UBYTE	PRN_DTC_Completed; */
** /* extern UBYTE	PRN_ImageBuffer1[PRINT_IMAGE_BUF_LINE][PRINT_IMAGE_BUF_SIZE]; */
#endif

/*-------------------------------------------------------------------------
** これらは、CDC_DecodePageTask()で使用されています。
** SAKAKIでは、ソフトデコードプリントをするので、この関数をCallしません。
** ATLANTAとのソース共通のため、この関数は残しておきます。
** Undefにならないように定義だけしておきます。
** 1998/06/10 H.Yoshikawa
*/
extern UBYTE  PRN_CompPageNo;					/* 今プリントしているのがページ合成の1ページめ(0)か2ページめ(1)か */
extern struct PRN_ReductionData_t	PRN_ReducData;
extern struct PrintStatusTimeData_t	PrintStatusTime[];

extern UWORD PRN_ListHight;	/* キャラクタープリント高さ指示変数 by O.Kimoto 1998/11/07 */ 
extern UBYTE PRN_ImageBufferOffSet;	/* PRN_ImageBuffer1のOffSet By O.Kimoto 1998/11/10 */
extern UWORD PRN_MemoryOpenResult;	/* Add By O.Kimoto 1998/12/01 */

/* メモリ送信時、1枚目以外で交信エラーが発生し、その時に蓄積原稿確認を行うと、白紙をプリント
** するので、（メモリ送信は送信ＯＫページは消しているため）次ページがあるかどうかを1ページプリント
** 完了する毎にチェックします。
** by O.Kimoto 1999/01/27
*/
extern struct	MEM_IndexData_t CheckPrintIndex;
extern struct	MEM_ExecData_t  CheckPrintExecReadData;
