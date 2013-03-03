/*--------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                            */
/*  ファイル名   : MON_TBL.C                                                */
/*  作成者       : 野瀬                                                     */
/*  日  付       : 97.04.09                                                 */
/*  概  要       : モニタ管理ブロック（ＴＣＢ、ＭＣＢ等）の                 */
/*               : 先頭アドレステーブル                                     */
/*               : モニターコールから管理ブロックへのアクセスは以下の       */
/*               : ポインタを間接参照することにより行います                 */
/*  修正履歴     :                                                          */
/*--------------------------------------------------------------------------*/

#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\mon_func.h"
#include "\src\cpu\sh7043_a\irom\define\def_mon.h"
#include "\src\cpu\sh7043_a\irom\define\def_tib.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mon.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"

#include "\src\cpu\sh7043_a\scd\define\cph_def.h"

#include "\src\atlanta\define\memerpro.h"

#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdmerpro.h"
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#if (PRO_MODEM == R288F)
 #if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)	/* 2001/12/21 T.Takagi */
 #include "\src\atlanta\mdm\fm336\define\mdmerpro.h"
 #include "\src\atlanta\mdm\fm336\define\mdm_def.h"
 #else
 #include "\src\atlanta\mdm\r288f\define\mdmerpro.h"
 #include "\src\atlanta\mdm\r288f\define\mdm_def.h"
 #endif
#endif
#if (PRO_MODEM == MN195006)
 #include "\src\atlanta\mdm\pana\define\mdmerpro.h"
 #include "\src\atlanta\mdm\pana\define\mdm_def.h"
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 熱転写記録方式 */
#include "\src\atlanta\prt\thermal\ext_v\prn_data.h"
#endif
#if (PRO_PRINT_TYPE == THERMAL)	/* 感熱記録方式 */
 #if defined(STOCKHM2)
#include "\src\atlanta\prt\lv_therm\define\prt_drv.h"
 #else
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
 #endif
#endif

extern UBYTE RL_Buffer[];			/* For Run Length */
extern UWORD	MDM_RxTotalLine;												/*	受信トータルライン	*/
extern	UDWORD	EncodeDataCount;
extern	struct mdmcntl_t	ModemControl;
extern	struct	MEM_ExecData_t	MemoryExecData;
extern	UDWORD			EncodeDataCount;
extern	UWORD			DecodeEcmFrameNum;
extern	UBYTE			TxStartFlag;
extern UBYTE	MDM_ModemBuffer[MODEM_BUFFER_MAX][MODEM_BUFFER_LENGTH];			/* モデムバッファ */
extern	UBYTE			CodecPageStatus;

#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) /* HINOKI2 2001/11/12 T.Takagi */
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\page_mem.h"
#endif

#if defined (SATSUKI2)
#include "\src\atlanta\satsuki2\define\scn_def.h"
#include "\src\atlanta\satsuki2\ext_v\page_mem.h"
#endif

#if defined (STOCKHM2)
#include "\src\atlanta\stockhm2\define\scn_def.h"
#include "\src\atlanta\stockhm2\ext_v\page_mem.h"
#endif
extern UBYTE PRN_ImageBuffer1[PRINT_IMAGE_BUF_LINE][PRINT_IMAGE_BUF_SIZE];

extern UBYTE	Img_Buffer1[SCD_LINE_SIZE][SCD_LINE_BYTE_SIZE];
extern UBYTE	Img_Buffer2[1][SCD_LINE_BYTE_SIZE];


/* 外付けＲＯＭに配置するＣＯＮＳＴデータ群です。
** 追加する時は、「Ｂ Ｓｅｃｔｉｏｎ」できられた内蔵ＲＡＭの方も合わせて変更してください。
** また、追加する時は、必ず下から下から追加するように！（でないと、参照ポインターがずれてしまい
** 暴走します。
*/

#pragma section REFTBL	/* locate section name "CREF_TBL" { */

/**************************************************
 * 外付けＲＯＭ（Ｆｌａｓｈ等）エリアの先頭を示す *
 **************************************************/
CONST UBYTE INI_ROMAreaIndicater[] = "Ext.ROM";

CONST UBYTE (*CONST RL_Buffer_pc) = &RL_Buffer[0];

/************************************************************************
 * タスクイニシャルブロックの先頭アドレス								*
 * 野瀬敏弘																*
 ************************************************************************/
CONST struct tib_table_data_t (* CONST tib_pc) = &tib[0];

/************************************************************************
 * タスクコントロールブロックの先頭アドレス								*
 * 野瀬敏弘																*
 ************************************************************************/
CONST struct tcb_table_data_t (* CONST tcb_pc) = &tcb[0];

/************************************************************************
 * セマフォコントロールブロックの先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
CONST struct scb_table_data_t (* CONST scb_pc) = &scb[0];

/************************************************************************
 * メッセージコントロールブロックの先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE (* CONST mcb_pc) = &mcb[0];

/************************************************************************
 * イベントコントロールブロックの先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE (* CONST ecb_pc) = &ecb[0];

/************************************************************************
 * スタックアドレスチェックテーブルの先頭アドレス						*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD (* CONST MON_StackCheckTable_pc) = &MON_StackCheckTable[0];

/************************************************************************
 * 大サイズのスタック領域の先頭アドレス									*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD (* CONST large_stack_area_pc) = &large_stack_area[0][0];

/************************************************************************
 * 小サイズのスタック領域の先頭アドレス									*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD (* CONST small_stack_area_pc) = &small_stack_area[0][0];

/************************************************************************
 * アイドルタスクのスタック領域の先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD (* CONST initial_task_stack_area_pc) = &small_stack_area[SMALL_STACK_MAX - 1][0];

/************************************************************************
 * メールボックス管理テーブルの先頭アドレス								*
 * 野瀬敏弘																*
 ************************************************************************/
CONST struct mbxno_data_t (* CONST mbxno_pc) = &mbxno;

/************************************************************************
 * セマフォ管理テーブルの先頭アドレス									*
 * 野瀬敏弘																*
 ************************************************************************/
CONST struct semno_data_t (* CONST semno_pc) = &semno;

/************************************************************************
 * 大タスクコントロールブロックの最大値									*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE MON_MAX_LARGE_TCB_C = LARGE_STACK_MAX;

/************************************************************************
 * 小タスクコントロールブロックの最大値									*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE MON_MAX_SMALL_TCB_C = SMALL_STACK_MAX;

/************************************************************************
 * 大・小合計のタスクコントロールブロックの最大値						*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE MON_MAX_TCB_C = TOTAL_STACK_MAX;

/************************************************************************
 * 大タスクのスタックサイズ												*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UWORD MON_SIZE_LARGE_STACK_C = LARGE_STACK;

/************************************************************************
 * 小タスクのスタックサイズ												*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UWORD MON_SIZE_SMALL_STACK_C = SMALL_STACK;

/************************************************************************
 * スタックエリアの底アドレス											*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD MON_STACK_START_ADDR_C = TASK_STACK_START;

/************************************************************************
 * 大タスククリエイト時のスタック開始基準アドレス						*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD MON_TOP_LARGE_ADDR_C = TOP_LARGE_ADDR;

/************************************************************************
 * 小タスククリエイト時のスタック開始基準アドレス						*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UDWORD MON_TOP_SMALL_ADDR_C = TOP_SMALL_ADDR;

/************************************************************************
 * ＳＣＢの最大値														*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE MON_MAX_SCB_C = SEMNO_MAX;

/************************************************************************
 * セマフォ管理テーブルの最大値											*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE MON_MAX_SEMNO_C = MAX_SEMNO;

/************************************************************************
 * ＭＣＢの最大値														*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UWORD MON_MAX_MCB_C = MBXNO_MAX;

/************************************************************************
 * メールボックス管理テーブルの最大値									*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UBYTE MON_MAX_MBXNO_C = MAX_MBXNO;

/************************************************************************
 * ＥＣＢの最大値														*
 * 野瀬敏弘																*
 ************************************************************************/
CONST UWORD MON_MAX_ECB_C = EVENT_MAX;

/*******************************************/
/* SCDからコールされるモニタの先頭アドレス */
/*******************************************/
CONST void (* CONST wai_tsk_vecc)() = (void (*)())wai_tsk_irom;
CONST void (* CONST wai_oneshot_vecc)() = (void (*)())wai_oneshot_irom;
CONST void (* CONST rcv_msg_vecc)() = (void (*)())rcv_msg_irom;

/**************************************/
/* モニターサブルーチンの先頭アドレス */
/**************************************/
CONST void (* CONST cre_ready_link_vecc)() = (void (*)())cre_ready_link_irom;
CONST void (* CONST del_ready_link_vecc)() = (void (*)())del_ready_link_irom;
CONST void (* CONST rescheduler_vecc)() = (void (*)())rescheduler_irom;
CONST void (* CONST ready_func_vecc)() = (void (*)())ready_func_irom;
CONST void (* CONST monitor_error_vecc)() = (void (*)())monitor_error;

#if (0) /* MTU1の不正割り込み処理追加の為のカウンタリセット処理を入れるため､外ＲＯＭに変更。 by H.Kubo 2001/02/21 */
** CONST void (* CONST SetOneshotTimer_vecc)() = (void (*)())SetOneshotTimer_irom;
#else
CONST void (* CONST SetOneshotTimer_vecc)() = (void (*)())SetOneshotTimer_erom;
#endif

/****************************************/
/* システム初期化ルーチンの先頭アドレス */
/****************************************/
CONST void (* CONST InitializeSystem_vecc)() = (void (*)())InitializeSystem;

/* mdm_g3.c */
/*UBYTE	RxG3_ReadExtRom(void);*/
CONST UBYTE (* CONST rx_g3_read_ext_tbl_c)(void) = (UBYTE (*)(void))RxG3_ReadExtRom;

/* mdm_sub.c */
CONST void (* CONST next_mdmbuf_wp_set_ext_tbl_c)(void) = (void (*)(void))NextMdmBufWritePointSetExtRom;
/* void NextModemBufferWritePointSetExtRom(void);*/

/*UBYTE	CheckEcmStatusExtRom(UWORD)		フレーム番号（０～２５５）	*/
CONST UBYTE (* CONST check_ecm_status_ext_tbl_c)(UWORD) = (UBYTE (*)(UWORD))CheckEcmStatusExtRom;

/* void NextModemBufferReadPointSet(void);	*	割り込みで使用	*/
CONST void (* CONST next_mdmbuf_rp_set_ext_tbl_c)(void) = (void (*)(void))NextMdmBufReadPointSetExtRom;

/* ソフトコーデックで参照している変数を間接参照に変更 By O.Kimoto 1998/08/27 */
CONST struct mdmcntl_t (* CONST ModemControl_pc) = &ModemControl;
CONST struct MEM_ExecData_t (* CONST MemoryExecData_pc) = &MemoryExecData;
CONST UDWORD (* CONST EncodeDataCount_c) = &EncodeDataCount;		/*	エンコードデータ総符号量	*/
CONST UWORD (* CONST MDM_RxTotalLine_c) = &MDM_RxTotalLine;		/*	受信トータルライン	*/
CONST UWORD	(* CONST DecodeEcmFrameNum_pc) = &DecodeEcmFrameNum;
CONST UBYTE	(* CONST TxStartFlag_pc) = &TxStartFlag;
CONST UBYTE	(* CONST MDM_ModemBuffer_pc) = &MDM_ModemBuffer[0][0];			/* モデムバッファ */
CONST UBYTE (* CONST CodecPageStatus_pc) = &CodecPageStatus;

CONST UWORD MODEM_BUFFER_LENGTH_PC = MODEM_BUFFER_LENGTH;
CONST UBYTE MODEM_BUFFER_MAX_PC = MODEM_BUFFER_MAX;

/* memread.c */
/* UWORD MEM_ReadGetNextBlockNoExtRom(UWORD);*/
/* CONST UWORD (* CONST mem_read_get_next_blk_no_exttbl_c)(UWORD) = (UWORD (*)(UWORD))MEM_ReadGetNextBlockNoERom; */
CONST UWORD (* CONST Mem_ReadGetNextBlkNoExttbl_c)(UWORD) = (UWORD (*)(UWORD))MEM_ReadGetNextBlockNoERom;

/* UBYTE *MEM_CalculateSoftAddressExtRom(UWORD) */
CONST UBYTE * (* CONST Mem_CalculateSoftaddrExtTbl_c)(UWORD) = (UBYTE * (*)(UWORD))MEM_CalculateSoftAddressERom;

/* memwrite.c */
/* UWORD MEM_WriteGetNextBlockNoExtRom(struct MEM_ExecData_t *);*/
CONST UWORD (* CONST Mem_WriteGgetNextBlkNoExtTbl_c)(struct MEM_ExecData_t *)
	= (UWORD (*)(struct MEM_ExecData_t *))MEM_WriteGetNextBlkNoERom;

CONST UDWORD SCD_MEM_BLOCK_SIZE = MEM_BLOCK_SIZE;

/************************************************************************
 * ＲＬからイメージに展開する為のバッファ＆サイズテーブル				*
 * 木元修																*
 ************************************************************************/
CONST UBYTE (* CONST prn_imgbuf1_pc) = &PRN_ImageBuffer1[0][0];
CONST UWORD PRT_IMG_BUF_SIZE_C = PRINT_IMAGE_BUF_SIZE;	/* 256 */
CONST UWORD PRT_IMG_BUF_LINE_C = PRINT_IMAGE_BUF_LINE;	/*  48 */

#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
CONST UBYTE (* CONST IMG_BUFFER1_C) = &PRN_ImageBuffer1[0][0];	/* RL -> Image */
CONST UBYTE (* CONST IMG_BUFFER2_C) = &ScanPageMem[0][0];	/* Image -> RL */
CONST UWORD SCD_LINE_BUF1_WIDTH_C = PRINT_IMAGE_BUF_SIZE;	/* 256 */
CONST UWORD SCD_LINE_BUF1_NUMBER_C = PRINT_IMAGE_BUF_LINE;	/*  20 */
CONST UWORD SCD_LINE_BUF2_WIDTH_C = SCANPAGE_COL;	/* 256 */
CONST UWORD SCD_LINE_BUF2_NUMBER_C = SCANPAGE_ROW;	/*  2 */
#elif defined(SAKAKI)
CONST UBYTE (* CONST IMG_BUFFER1_C) = &Img_Buffer1[0][0];	/* RL -> Image */
CONST UBYTE (* CONST IMG_BUFFER2_C) = &Img_Buffer2[0][0];	/* Image -> RL */
CONST UWORD SCD_LINE_BUF1_WIDTH_C = SCD_LINE_BYTE_SIZE;	/* 256 */
CONST UWORD SCD_LINE_BUF1_NUMBER_C = SCD_LINE_SIZE;	/*  2 */
CONST UWORD SCD_LINE_BUF2_WIDTH_C = SCD_LINE_BYTE_SIZE;	/* 256 */
CONST UWORD SCD_LINE_BUF2_NUMBER_C = SCD_LINE_SIZE;	/*  2 */
#else
CONST UBYTE (* CONST IMG_BUFFER1_C) = &Img_Buffer1[0][0];	/* RL -> Image */
CONST UBYTE (* CONST IMG_BUFFER2_C) = &Img_Buffer2[0][0];	/* Image -> RL */
CONST UWORD SCD_LINE_BUF1_WIDTH_C = SCD_LINE_BYTE_SIZE;	/* 256 */
CONST UWORD SCD_LINE_BUF1_NUMBER_C = SCD_LINE_SIZE;	/*  2 */
CONST UWORD SCD_LINE_BUF2_WIDTH_C = SCD_LINE_BYTE_SIZE;	/* 256 */
CONST UWORD SCD_LINE_BUF2_NUMBER_C = SCD_LINE_SIZE;	/*  2 */
#endif

#pragma section		/* #pragma section REFTBL*/	/* locate section name "CREF_TBL" { */

/* 内蔵ＲＡＭに配置する参照ポインターデータ群です。
** 追加する時は、「Ｃ Ｓｅｃｔｉｏｎ」できられた外付けＲＯＭの方も合わせて変更してください。
** また、追加する時は、必ず下から下から追加するように！（でないと、参照ポインターがずれてしまい
** 暴走します。
*/
#pragma section REFTBLIMG /* locate section name "BREFTBLIMG" */

UBYTE *RL_Buffer_p;

/************************************************************************
 * タスクイニシャルブロックの先頭アドレス								*
 * 野瀬敏弘																*
 ************************************************************************/
struct tib_table_data_t *tib_p;

/************************************************************************
 * タスクコントロールブロックの先頭アドレス								*
 * 野瀬敏弘																*
 ************************************************************************/
struct tcb_table_data_t *tcb_p;

/************************************************************************
 * セマフォコントロールブロックの先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
struct scb_table_data_t *scb_p;

/************************************************************************
 * メッセージコントロールブロックの先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE *mcb_p;

/************************************************************************
 * イベントコントロールブロックの先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE *ecb_p;

/************************************************************************
 * スタックアドレスチェックテーブルの先頭アドレス						*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD *MON_StackCheckTable_p;

/************************************************************************
 * 大サイズのスタック領域の先頭アドレス									*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD *large_stack_area_p;

/************************************************************************
 * 小サイズのスタック領域の先頭アドレス									*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD *small_stack_area_p;

/************************************************************************
 * アイドルタスクのスタック領域の先頭アドレス							*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD *initial_task_stack_area_p;

/************************************************************************
 * メールボックス管理テーブルの先頭アドレス								*
 * 野瀬敏弘																*
 ************************************************************************/
struct mbxno_data_t *mbxno_p;

/************************************************************************
 * セマフォ管理テーブルの先頭アドレス									*
 * 野瀬敏弘																*
 ************************************************************************/
struct semno_data_t *semno_p;


/************************************************************************
 * 大タスクコントロールブロックの最大値									*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE MON_MAX_LARGE_TCB;

/************************************************************************
 * 小タスクコントロールブロックの最大値									*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE MON_MAX_SMALL_TCB;

/************************************************************************
 * 大・小合計のタスクコントロールブロックの最大値						*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE MON_MAX_TCB;

/************************************************************************
 * 大タスクのスタックサイズ												*
 * 野瀬敏弘																*
 ************************************************************************/
UWORD MON_SIZE_LARGE_STACK;

/************************************************************************
 * 小タスクのスタックサイズ												*
 * 野瀬敏弘																*
 ************************************************************************/
UWORD MON_SIZE_SMALL_STACK;

/************************************************************************
 * スタックエリアの底アドレス											*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD MON_STACK_START_ADDR;

/************************************************************************
 * 大タスククリエイト時のスタック開始基準アドレス						*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD MON_TOP_LARGE_ADDR;

/************************************************************************
 * 小タスククリエイト時のスタック開始基準アドレス						*
 * 野瀬敏弘																*
 ************************************************************************/
UDWORD MON_TOP_SMALL_ADDR;

/************************************************************************
 * ＳＣＢの最大値														*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE MON_MAX_SCB;

/************************************************************************
 * セマフォ管理テーブルの最大値											*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE MON_MAX_SEMNO;

/************************************************************************
 * ＭＣＢの最大値														*
 * 野瀬敏弘																*
 ************************************************************************/
UWORD MON_MAX_MCB;

/************************************************************************
 * メールボックス管理テーブルの最大値									*
 * 野瀬敏弘																*
 ************************************************************************/
UBYTE MON_MAX_MBXNO;

/************************************************************************
 * ＥＣＢの最大値														*
 * 野瀬敏弘																*
 ************************************************************************/
UWORD MON_MAX_ECB;

/*******************************************/
/* SCDからコールされるモニタの先頭アドレス */
/*******************************************/
void *wai_tsk_vec;
void *wai_oneshot_vec;
void *rcv_msg_vec;

/**************************************/
/* モニターサブルーチンの先頭アドレス */
/**************************************/
void *cre_ready_link_vec;
void *del_ready_link_vec;
void *rescheduler_vec;
void *ready_func_vec;
void *monitor_error_vec;
void *SetOneshotTimer_vec;

/****************************************/
/* システム初期化ルーチンの先頭アドレス */
/****************************************/
void *InitializeSystem_vec;

/* mdm_g3.c */
/*UBYTE	RxG3_ReadExtRom(void);*/
UBYTE *rx_g3_read_ext_tbl;

/* mdm_sub.c */
void *next_mdmbuf_wp_set_ext_tbl;
/* void NextModemBufferWritePointSetExtRom(void);*/

/*UBYTE	CheckEcmStatusExtRom(UWORD)		フレーム番号（０～２５５）	*/
UBYTE *check_ecm_status_ext_tbl;

/* void NextModemBufferReadPointSet(void);	*	割り込みで使用	*/
void *next_mdmbuf_rp_set_ext_tbl;

/* ソフトコーデックで参照している変数を間接参照に変更 By O.Kimoto 1998/08/27 */
/* CONST struct mdmcntl_t (* ModemControl_pc) = &ModemControl; */
struct mdmcntl_t (* ModemControl_p);

/* CONST struct MEM_ExecData_t (* MemoryExecData_pc) = &MemoryExecData; */
struct MEM_ExecData_t (* MemoryExecData_p);

/* CONST UDWORD (* CONST EncodeDataCount_c) = &EncodeDataCount; */		/*	エンコードデータ総符号量	*/
UDWORD (* EncodeDataCount_p);		/*	エンコードデータ総符号量	*/

/* CONST UWORD (* CONST MDM_RxTotalLine_c) = &MDM_RxTotalLine; */		/*	受信トータルライン	*/
UWORD (* MDM_RxTotalLine_p);		/*	受信トータルライン	*/

/* CONST UWORD	(* DecodeEcmFrameNum_pc) = &DecodeEcmFrameNum; */
UWORD	(* DecodeEcmFrameNum_p);

/* CONST UBYTE	(* TxStartFlag_pc) = &TxStartFlag; */
UBYTE	(* TxStartFlag_p);

/* CONST UBYTE	(* MDM_ModemBuffer_pc) = &MDM_ModemBuffer[0][0]; */			/* モデムバッファ */
UBYTE	(* MDM_ModemBuffer_p);			/* モデムバッファ */

/* CONST UBYTE (* CodecPageStatus_pc) = &CodecPageStatus; */
UBYTE (* CodecPageStatus_p);

/* CONST UBTYE MODEM_BUFFER_LENGTH_PC = MODEM_BUFFER_LENGTH; */
UBYTE MODEM_BUF_LENGTH_P;

/* CONST UBYTE MODEM_BUFFER_MAX_PC = MODEM_BUFFER_MAX; */
UBYTE MODEM_BUF_MAX_P;

/* memread.c */
/* UWORD MEM_ReadGetNextBlockNoExtRom(UWORD);*/
UWORD *mem_read_get_next_blk_no_exttbl;

/* UBYTE *MEM_CalculateSoftAddressExtRom(UWORD) */
UBYTE * (* mem_calculate_softaddr_exttbl);

/* memwrite.c */
/* UWORD MEM_WriteGetNextBlockNoExtRom(struct MEM_ExecData_t *);*/
UWORD *mem_write_get_nextblk_no_exttbl;

UDWORD SCD_MEM_BLOCK_SIZE_I;

/************************************************************************
 * ＲＬからイメージに展開する為のバッファ＆サイズテーブル				*
 * 木元修																*
 ************************************************************************/
UBYTE *prn_imgbuf1_p;
UWORD PRT_IMG_BUF_SIZE;	/* 256 */
UWORD PRT_IMG_BUF_LINE;	/*  48 */

UBYTE *img_buffer1;
UBYTE *img_buffer2;
UWORD SCD_LINE_BUF1_WIDTH;	/* 256 */
UWORD SCD_LINE_BUF1_NUMBER;	/*  2 */
UWORD SCD_LINE_BUF2_WIDTH;	/* 256 */
UWORD SCD_LINE_BUF2_NUMBER;	/*  2 */


#pragma section		/* #pragma section REFTBLIMG *//* locate section name "BREFTBLIMG" */

#endif
