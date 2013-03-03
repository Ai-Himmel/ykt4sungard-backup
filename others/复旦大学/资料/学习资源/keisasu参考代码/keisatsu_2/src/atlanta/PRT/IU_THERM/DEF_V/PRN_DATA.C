/***************************************************************
*	System		: SAKAKI
*	File Name	: PRN_DATA.C
*	Author		: K.Kawata
*	Date		: 1998/6/9
*	Description	:
*	Maintenance	:
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
****************************************************************/
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

/* struct	PRN_Control_def	PRN_Control = {0}; */
struct	SYS_MultiCopyData_t	*McopyPtr = {0};	/* マルチコピープリント時のマルチコピーファイルのポインタ */
struct	SYS_MemoryRxPrintData_t	*MRxPtr = {0};	/* メモリ受信原稿プリント時のメモリ受信原稿ファイルのポインタ */
UBYTE	PRN_1PageReceived = 0;
UBYTE	CutToPrintExecFlag = 0;
MESSAGE_t	PrinterEndMessage = {0};
struct	WorkBuf_t	PRN_RL1 = {0};
struct	WorkBuf_t	PRN_RL2 = {0};
struct	WorkBuf_t *DecodeA_buffer = {0};
struct	WorkBuf_t *DecodeB_buffer = {0};
struct	CdcBlk_t PrintDecodeData = {0};
struct	Buf_p_t PrnRp = {0};
struct	MEM_IndexData_t PrintIndex = {0};
struct	MEM_ExecData_t  PrintExecReadData = {0};
UBYTE	PRN_PrintModeCount = 0;
UBYTE	PrintModeCountWork = 0;
UBYTE	DecodeWaitFlag = 0;
UBYTE	DecodeWaitCommandFlag = 0;
struct	reduction_t	PRN_LineSkipData = {0};
UWORD	PRN_OriginalImageSize = 0;
UWORD	PRN_ReductionImageSize = 0;

#if (0)
** /* 以下はSAKAKIで使用している変数達です。
** ** HINOKIでは不要なのでコメントにします。
** ** 必要に応じて戻してやってください。
** ** By O.Kimoto 1998/10/27
** */
** /* UWORD StoreDocumentPrintResult = 0; */
** /* UBYTE HeatPulseOffSet = 0; */
** /* UBYTE HeatPulseHeadRank = 0; */
** /* UBYTE DebugHsyncCount =0; */
** /* UBYTE PrintType = 0; */
** /* UBYTE PrintingType = 0; */
** /* UWORD Doc_ChkMsgReturnValue = 0; */
** /* UBYTE PRN_StartPrintFlag = 0; */
** /* UBYTE PRN_EndPrintFlag = 0; */
** /* UBYTE PRN_FirstPrintFlag = 0; */
** /* UBYTE ps2_off_count = 0; */
** /* UBYTE ps2_off_flag = 0; */
** /* UBYTE PRN_DFA4B4Sensor = 0; */
** /* UBYTE	PRN_LineMemoryStatus = 0; */
** /* UWORD	ThermisterValue = 0; */
** /* UWORD	PaperMargin = 0; */
** /* UBYTE	PRN_PB4Sensor = 0; */
** /* UBYTE	PRN_OpenCount = 0; */
** /* UBYTE	PrnMotorPhase = 0; */
** /* UWORD	ImageLineReadPoint = 0; */
** /* UWORD	ImageLineWritePoint = 0; */
** /* UWORD	ImageLineStartPoint = 0; */
** /* UBYTE	ReadPointWaitFlag = 0; */
** /* struct	DMA_Data_t	PRN_LineDMA = {0}; */
** /* UWORD	SMCR_StatusPRN_Dummy = 0; */
** /* UBYTE	PRN_DTC_Completed = 0; */
** #if (0)
** ** #pragma section PRNBUF /* locate section name "DPRNBUF" */
** ** UBYTE	PRN_ImageBuffer1[PRINT_IMAGE_BUF_LINE][PRINT_IMAGE_BUF_SIZE] = {0};	/* 1 LINE ﾌﾟﾘﾝﾄ用ﾋﾞｯﾄｲﾒｰｼﾞﾊﾞｯﾌｧ */
** ** #pragma section
** #endif
#endif

/*-------------------------------------------------------------------------
** これらは、CDC_DecodePageTask()で使用されています。
** SAKAKIでは、ソフトデコードプリントをするので、この関数をCallしません。
** ATLANTAとのソース共通のため、この関数は残しておきます。
** Undefにならないように定義だけしておきます。
** 1998/06/10 H.Yoshikawa
*/
UBYTE  PRN_CompPageNo = 0;
struct PRN_ReductionData_t	PRN_ReducData = {0};
struct PrintStatusTimeData_t	PrintStatusTime[1] = {0};

UWORD PRN_ListHight = 0;	/* キャラクタープリント高さ指示変数 by O.Kimoto 1998/11/07 */ 
UBYTE PRN_ImageBufferOffSet = 0;	/* PRN_ImageBuffer1のOffSet By O.Kimoto 1998/11/10 */
UWORD	PRN_MemoryOpenResult = 0;	/* Add By O.Kimoto 1998/12/01 */

/* メモリ送信時、1枚目以外で交信エラーが発生し、その時に蓄積原稿確認を行うと、白紙をプリント
** するので、（メモリ送信は送信ＯＫページは消しているため）次ページがあるかどうかを1ページプリント
** 完了する毎にチェックします。
** by O.Kimoto 1999/01/27
*/
struct	MEM_IndexData_t CheckPrintIndex = {0};
struct	MEM_ExecData_t  CheckPrintExecReadData = {0};
