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
struct CdcBlk_t EncodeData = {0};
struct CdcBlk_t DecodeData = {0};
UWORD SCDC_EncodeLine = 0;
UWORD SCDC_DecodeLine = 0;
UBYTE EncCodecPageStatus = 0;
UBYTE DecCodecPageStatus = 0;
UBYTE SCDC_EncReduction = 0;
UBYTE SCDC_DecReduction = 0;

/* ＲＬバッファアクセス用変数 */
struct WorkBuf_t *EncodeA_buf = {0};
struct WorkBuf_t *EncodeB_buf = {0};
struct WorkBuf_t *EncodeC_buf = {0};
struct WorkBuf_t *EncodeD_buf = {0};
struct WorkBuf_t *EncodeTmp_buf = {0};

struct WorkBuf_t *DecodeA_buf = {0};
struct WorkBuf_t *DecodeB_buf = {0};
struct WorkBuf_t *DecodeC_buf = {0};
struct WorkBuf_t *DecodeD_buf = {0};
struct WorkBuf_t *DecodeTmp_buf = {0};

/* ＲＬバッファ */
struct reduction_t Enc_reduc_data = {0};
struct reduction_t *enc_rp = {0};
struct reduction_t Dec_reduc_data = {0};
struct reduction_t *dec_rp = {0};

struct	WorkBuf_t	EncRL1 = {0};
struct	WorkBuf_t	EncRL2 = {0};
struct	WorkBuf_t	EncRL3 = {0};
struct	WorkBuf_t	EncRL4 = {0};

struct	WorkBuf_t	DecRL1 = {0};
struct	WorkBuf_t	DecRL2 = {0};
struct	WorkBuf_t	DecRL3 = {0};
struct	WorkBuf_t	DecRL4 = {0};


UBYTE	first_line_encode = 0;	/*	ＴＴＩを除く画データの先頭行をエンコードする直前まで１	*/

struct	MEM_ExecData_t	EncMemoryExecBkupData = {0};	/*	蓄積中指定データ	*/
struct	MEM_ExecData_t	DecMemoryExecBkupData = {0};	/*	蓄積中指定データ	*/
