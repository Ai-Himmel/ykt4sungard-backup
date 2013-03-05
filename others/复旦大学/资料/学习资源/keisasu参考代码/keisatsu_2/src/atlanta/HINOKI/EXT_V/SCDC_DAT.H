/************************************************************************
*	System			: HINOKI
*	File Name		: SCDC_DAT.C
*	Author			: 木元修
*	Date			: 1998/10/02
*	RealTimeOS		: ＲＩＳＣ（ＳＨ７０４３）モニター
*	Description		: ソフトコーデック用変数
*	Original File	: 
*	Maintenance		:
*
*	Copyright (C) 1996 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"

#include "\src\cpu\sh7043_a\scd\define\scd.h"

/*************************************************************************
* 以下は、データ宣言用ファイル（XXXX_DATA.C）に含めるべきデータです。
* 今は、プログラム中なので、ここで宣言しておきます。
* 後で整理しましょうね。＞木元
* by O.Kimoto 1998/10/01
*************************************************************************/
/* エンコード デコード 変数 */
extern struct CdcBlk_t EncodeData;
extern struct CdcBlk_t DecodeData;
extern UWORD SCDC_EncodeLine;
extern UWORD SCDC_DecodeLine;
extern UBYTE EncCodecPageStatus;
extern UBYTE DecCodecPageStatus;
extern UBYTE SCDC_EncReduction;
extern UBYTE SCDC_DecReduction;

/* ＲＬバッファアクセス用変数 */
extern struct WorkBuf_t *EncodeA_buf;
extern struct WorkBuf_t *EncodeB_buf;
extern struct WorkBuf_t *EncodeC_buf;
extern struct WorkBuf_t *EncodeD_buf;
extern struct WorkBuf_t *EncodeTmp_buf;

extern struct WorkBuf_t *DecodeA_buf;
extern struct WorkBuf_t *DecodeB_buf;
extern struct WorkBuf_t *DecodeC_buf;
extern struct WorkBuf_t *DecodeD_buf;
extern struct WorkBuf_t *DecodeTmp_buf;

/* ＲＬバッファ */
extern struct reduction_t Enc_reduc_data;
extern struct reduction_t *enc_rp;
extern struct reduction_t Dec_reduc_data;
extern struct reduction_t *dec_rp;

extern struct	WorkBuf_t	EncRL1;
extern struct	WorkBuf_t	EncRL2;
extern struct	WorkBuf_t	EncRL3;
extern struct	WorkBuf_t	EncRL4;

extern struct	WorkBuf_t	DecRL1;
extern struct	WorkBuf_t	DecRL2;
extern struct	WorkBuf_t	DecRL3;
extern struct	WorkBuf_t	DecRL4;

extern UBYTE	first_line_encode;	/*	ＴＴＩを除く画データの先頭行をエンコードする直前まで１	*/

extern struct	MEM_ExecData_t	EncMemoryExecBkupData;	/*	蓄積中指定データ	*/
extern struct	MEM_ExecData_t	DecMemoryExecBkupData;	/*	蓄積中指定データ	*/
