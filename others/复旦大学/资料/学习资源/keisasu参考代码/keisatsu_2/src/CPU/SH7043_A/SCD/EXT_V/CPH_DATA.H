/*--------------------------------------------------------------------
* プロジェクト : POPLAR
* ファイル名   : cph_def.h
* 作成者       : By Y.Suzuki
* 日  付       : 1997/06/10
* 概  要       : SH2
*              : 暗号化用大域変数
* 参照
*--------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\message.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\cph_def.h"
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#else
#include "\src\atlanta\scd\define\cph_def.h"
#include "\src\atlanta\scd\define\scd.h"
#endif

extern struct CipherTbl_t CipherData;

/*	メモリリードライトオープンに必要なパラメータ	*/
extern struct MEM_IndexData_t CipherReadIndex;
extern struct MEM_IndexData_t CipherWriteIndex;
extern struct MEM_ExecData_t  CipherExecReadData;
extern struct MEM_ExecData_t  CipherExecWriteData;
extern struct MEM_StoreData_t CipherStoreData;
extern UWORD CipherReadPageNo;
extern UWORD CipherWritePageNo;

/*	ソフトコーデック初期化に必要なデータ	*/
extern UBYTE CipherWriteCode;
extern UBYTE CipherWriteMode;
extern UBYTE CipherWriteSize;
extern UBYTE CipherReadCode;
extern UBYTE CipherReadMode;
extern UBYTE CipherReadSize;
extern UWORD CipherReadTotalLine;

extern UBYTE CipherBegin;
/* ＲＬバッファアクセス用変数 */
extern struct WorkBuf_t *EncodeA_buf;
extern struct WorkBuf_t *EncodeB_buf;
extern struct WorkBuf_t *DecodeA_buf;
extern struct WorkBuf_t *DecodeB_buf;

/* エンコード／デコード 変数 */
extern struct CdcBlk_t CipherEncodeData;
extern struct CdcBlk_t CipherDecodeData;
extern UWORD CipherEncodeLine;
extern UWORD CipherDecodeLine;

/* 暗号化結果メッセージ送信用 */
extern MESSAGE_t	CipherMessage;

/* スクランブル／復元処理停止ステータス */
/* SYS_Machinestatus を参照したくない。アドレスの固定化が難しそうなんで */
extern UBYTE CipherStopOn;

/* イメージ用ＲＡＭ */
/* extern UBYTE	Img_Buffer[1320][256];* DRAM に割り当てる */
/* extern UBYTE Img_Buffer[2803][256];* DRAM に割り当てる By Y.Suzuki 1997/09/01 */
/*extern struct CipherParameter_t IMG_BUF;*/
/*extern struct CipherParameter_t *CipherP;*/
extern UBYTE ScrambleOn;

#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
#else
extern UBYTE	Img_Buffer1[SCD_LINE_SIZE][SCD_LINE_BYTE_SIZE];/* Ｂ４ ファイン １ページ分 デコード用 */
extern UBYTE	Img_Buffer2[1][SCD_LINE_BYTE_SIZE];			/* Ｂ４ ライン１ライン分 エンコード用 */
#endif

/* ライブラリ使用のため */
extern int *_B_BGN;

/* For Debug By Y.Suzuki 1997/11/02 */
extern UBYTE SCD_DebugCopyOn;
extern UWORD SCD_DebugLineToLabel;

/* パーセント表示用 */
/* アリロの表示用パラメータの値がいまいちなんでこっちで改ざんする */
extern int RealPercent;

/* 2回線目のラインＮＯ．記憶 By Y.Suzuki 1998/04/28 */
extern UBYTE OtherLineNo;
