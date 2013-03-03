/*	By Y.Suzuki 1996/10/15	*/
/*	Original File jun\usr2:\src\kobe\anzu\scdc\ext_v\scddrlbuf.h	*/
#include	"\src\atlanta\define\product.h"
#include	"\src\atlanta\define\sysdoc.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include	"\src\cpu\sh7043_a\scd\define\scd.h"
#include    "\src\cpu\sh7043_a\scd\define\scd_def.h"
#else
#include	"\src\atlanta\scd\define\scd.h"
#include    "\src\atlanta\scd\define\scd_def.h"
#endif

/*--------------*/
/* ＲＬバッファ */
/*--------------*/
/* A3(2432) 400DPI(*2) ｴﾝｺｰﾄﾞ/ﾃﾞｺｰﾄﾞ同時処理(*2) 参照ﾗｲﾝ､符号化ﾗｲﾝの2本分(*2) */
/* SYS_A3_LINE:2432 */

extern UBYTE RL_Buffer[8*SYS_A3_LINE];			/* For Run Length */
extern UBYTE *RL_Buffer_p; /* 新ﾏｽｸ変更 追加 T.Nose 1998/08/27 */

/* extern struct CdcBlk_t Cdc; ローカル変数にする Y.Suzuki */
/* extern struct WorkBuf_t Work; By Y.Suzuki 1997/02/28 */

/*-----------------------------------*/
/*  ＲＬバッファアクセス用パラメータ */
/*-------------------------------Y.S-*/
extern struct	WorkBuf_t	RL1;
extern struct	WorkBuf_t	RL2;
extern struct	WorkBuf_t	RL3;
extern struct	WorkBuf_t	RL4; /* アリロ用 By Y.Suzuki 1997/06/12 */

/*------------------------------*/
/*	メモリアクセス用バッファ	*/
/*------------------------Y.S---*/
extern UBYTE MemBuf[256];
extern struct Buf_p_t MemRp;
extern struct Buf_p_t MemWp;

/*--------------------------------------*/
/*	モデムバッファアクセス用バッファ	*/
/*--------------------------------Y.S---*/
extern struct Buf_p_t MdmRp;
extern struct Buf_p_t MdmWp;

/*--------------------------------------*/
/*	ECMバッファアクセス用バッファ	*/
/*--------------------------------Y.S---*/
extern struct Buf_p_t EcmRp;
extern struct Buf_p_t EcmWp;

extern UBYTE SCD_Dummy2[13];		/*	By Y.Suzuki 1997/02/28	*/
