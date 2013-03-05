/*	By Y.Suzuki 1996/10/15	*/
/*	Original file jun\usr2:\src\kobe\anzu\scdc\def_v\scdrlbuf.c	*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysdoc.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include	"\src\cpu\sh7043_a\scd\define\scd.h"
#else
#include	"\src\atlanta\scd\define\scd.h"
#endif

#pragma section RLBUF /* locate sectionname "DRLBUF" */
/*------------------*/
/* ０．ＲＬバッファ */
/*------------------*/
/* A3(2432) 400DPI(*2) ｴﾝｺｰﾄﾞ/ﾃﾞｺｰﾄﾞ同時処理(*2) 参照ﾗｲﾝ､符号化ﾗｲﾝの2本分(*2) */
/* SYS_A3_LINE:2432 */
UBYTE RL_Buffer[RLBUF_DEC+(RLBUF_SIZE * 2)] = {0};			/* For Run Length */

/* struct CdcBlk_t Cdc = {0};ローカル変数にする 95/12/20 Y.Suzuki */
/* struct WorkBuf_t Work = {0}; By Y.Suzuki 1997/02/28 */

/*------------------------------------------*/
/*	１９４５６．メモリアクセス用バッファ	*/
/*------------------------------------Y.S---*/
struct Buf_p_t MemRp = {0};
struct Buf_p_t MemWp = {0};

/*--------------------------------------------------*/
/*	１９４７４．モデムバッファアクセス用バッファ	*/
/*--------------------------------------------Y.S---*/
struct Buf_p_t MdmRp = {0};
struct Buf_p_t MdmWp = {0};

/*----------------------------------------------*/
/*	１９４９２．ECMバッファアクセス用バッファ	*/
/*----------------------------------------Y.S---*/
struct Buf_p_t EcmRp = {0};
struct Buf_p_t EcmWp = {0};

#if (0) /* 新ﾏｽｸ変更 内蔵RAMへ移動 */
/*-----------------------------------------------*/
/*  １９５１０．ＲＬバッファアクセス用パラメータ */
/*-------------------------------------------Y.S-*/
struct	WorkBuf_t	RL1 = {0};
struct	WorkBuf_t	RL2 = {0};
struct	WorkBuf_t	RL3 = {0};
struct	WorkBuf_t	RL4 = {0}; /* アリロー用 By Y.Suzuki 1997/06/12 */
#endif

/*----------------------*/
/*  １９５３１．バイト  */
/*----------------------*/
UBYTE SCD_Dummy2[13] = {0};

/*----------------------*/
/*  １９５４４．バイト  */
/*----------------------*/
/* このファイルにデータを追加する場合、ファイルの最後に SCD_Dummy2 に収まる13バイト程度にする。*/
#pragma section

#pragma section RLBUFI /* locate section name "DRLBUFI" */
/*-----------------------------------------------*/
/*  １９５１０．ＲＬバッファアクセス用パラメータ */
/*-------------------------------------------Y.S-*/
struct	WorkBuf_t	RL1 = {0};
struct	WorkBuf_t	RL2 = {0};
struct	WorkBuf_t	RL3 = {0};
struct	WorkBuf_t	RL4 = {0}; /* アリロー用 By Y.Suzuki 1997/06/12 */
#pragma section
