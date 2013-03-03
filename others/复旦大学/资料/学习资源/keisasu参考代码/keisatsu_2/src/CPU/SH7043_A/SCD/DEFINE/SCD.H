/*	By Y.Suzuki 1996/10/15	*/
/*	Original File jun/usr2:\src\kobe\scdc\define\scdc.h	*/
#ifndef scd
	#define scd

#include "\src\atlanta\define\mem_def.h"/* 95/12/24 Y.S */

/************************************************************************
 *  soft codec 										            		*
 * "\src\kobe\anzu\scdc\define\scdc.h"										*
 *																		*
 * 概要　　：Soft codec table for RISC chip                             *
 *			        													*
 ************************************************************************/

/* \src\kobe\anzu\define\std.h にすでにある。ただし論理は、逆なので注意。
#define NG              0
#define OK              1
*/
#define P_MODE			0
#define H_MODE			1
#define VL3_MODE		2
#define VL2_MODE		3
#define VL1_MODE		4
#define V0_MODE			5
#define VR1_MODE		6
#define VR2_MODE		7
#define VR3_MODE		8
/* #define V0_MAX_COUNT	16		  @* v0連続の場合の処理: Ｖ０のMAX個数 */
#define V0_MAX_COUNT	4864		  /* v0連続の場合の処理: Ｖ０のMAX個数 */
#define RCP				11
#define EOL_MR			12        /* MR符号化のＥＯＬ＋0 */
#define EOL_MH			13        /* MR符号化のＥＯＬ＋1 */
#define RTC             14
#define EOL_FOUND       15
#define MH_EOL_FOUND    16
#define MR_EOL_FOUND    17
#define MMR_FOUND       18
#define ERR				-1
#define EOL				-2        /* Decode Tableで８個０を見付けたreturn値 */
#define MEM_OVER		-3        /* ダイレクトメモリ受信用 By Y.Suzuki 1997/09/11 */

#define	EOL_NO			104		  /* used by encode */
#define EOL_MH_NO       105
#define EOL_MR_NO       106

#define P_DATA			0x08	 /* used by  MR encode table data */
#define H_DATA			0x04
#define VL3_DATA		0x20
#define VL2_DATA		0x10
#define VL1_DATA		0x02
#define V0_DATA			0x01
#define VR1_DATA		0x06
#define VR2_DATA		0x30
#define VR3_DATA		0x60

#define RL_OVER			 0      /* for debug */

/* RL color */
#define WHITE       	0
#define BLACK			1

/*	MH CODE MAKE_UP MAX	By Y.Suzuki 1996/12/02 */
#define MH_MAKEUP_MAX	2560

/* ＲＬ＿ＢＵＦ［((A3*2(符号化/参照ﾗｲﾝ))*2(400DPI))*2(ｴﾝｺｰﾄﾞ/ﾃﾞｺｰﾄﾞを同時に処理する。ﾒﾓﾘ送受信)］*/
	/*	A3 400DPI の場合	*/
#define RLBUF_SIZE  4864	/* 参照ﾗｲﾝ/符号化ﾗｲﾝの切り替えに使用 1RLﾊﾞｯﾌｧのｻｲｽﾞ */
#define RLBUF_ENC   0	 	/* 0--9727は、ｴﾝｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
#define RLBUF_DEC   9728	/* 9728--19455(9728 + RLBUF_SIZE * 2) は、ﾃﾞｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
/*-----------------------------------------------------------------
 *	アリロー用ＲＬバッファサイズ
 *	通信でA3/400DPI/3 LINEとして使用.アリローでは、B4/200DPI/4 LINE
 *	で使用する。
 *	By Y.Suzuki 1997/06/12
*------------------------------------------------------------------*/
#define RLBUF_CPH_SIZE  2048	/* 参照ﾗｲﾝ/符号化ﾗｲﾝの切り替えに使用 1RLﾊﾞｯﾌｧのｻｲｽﾞ アリロは、B4まで */
#define RLBUF_CPH_ENC   0	 	/* 0--4095は、ｴﾝｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
#define RLBUF_CPH_DEC   4096	/* 4096--8192(4096 + RLBUF_CPH_SIZE * 2) は、ﾃﾞｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */

#if (0)/*	B4 200DPI の場合 RL BUF 容量確認のためBy Y.Suzuki Aug.29'96	*/
//#define RLBUF_SIZE  2048	/* 参照ﾗｲﾝ/符号化ﾗｲﾝの切り替えに使用 1RLﾊﾞｯﾌｧのｻｲｽﾞ */
//#define RLBUF_ENC   0	 	/* 0--4095は、ｴﾝｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
//#define RLBUF_DEC   4096	/* 4096--8192(5184 + RLBUF_SIZE * 2)は、ﾃﾞｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
#endif

#if(0)	/*	A4 300DPI の場合	*/
//#define RLBUF_SIZE  2592	/* 参照ﾗｲﾝ/符号化ﾗｲﾝの切り替えに使用 1RLﾊﾞｯﾌｧのｻｲｽﾞ */
//#define RLBUF_ENC   0	 	/* 0--5183は、ｴﾝｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
//#define RLBUF_DEC   5184	/* 5184--10368(5184 + RLBUF_SIZE * 2)は、ﾃﾞｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
#endif
#if(0)/* ﾃﾞﾊﾞｯｸ用 高速SRAMが8KWORDしかないため */
//#define RLBUF_SIZE  2048	/* 参照ﾗｲﾝ/符号化ﾗｲﾝの切り替えに使用 1RLﾊﾞｯﾌｧのｻｲｽﾞ */
//#define RLBUF_ENC   0	 	/* 0--4055は、ｴﾝｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
//#define RLBUF_DEC   4096	/* 4056--8112は、ﾃﾞｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
#endif

/********************************************************************************
* 現状、ＲＬ＿Ｂｕｆｆｅｒ[]はＡ３／４００ｄｐｉで４本分ある。
* しかし、ＨＩＮＯＫＩはＢ４／２００ｄｐｉ仕様である。そこで、このＲＬ＿Ｂｕｆｆｅｒの
* 資源を有効に利用する。
*       エリア確保：Ａ３／４００ｄｐｉ（現状）＜＝４本
*       実使用時  ：Ｂ４／２００ｄｐｉ        ＜＝９．５本
*         ＝＞  エンコード用：４本
*               デコード用  ：４本
*               余り        ：１．５本
* となる。
********************************************************************************/
#define RLBUF_SIZE_B4  2048		/* 参照ﾗｲﾝ/符号化ﾗｲﾝの切り替えに使用 1RLﾊﾞｯﾌｧのｻｲｽﾞ */
#define RLBUF_ENC_B4      0		/* 0--8191は、ｴﾝｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */
#define RLBUF_DEC_B4   8192		/* 8192--16383(8192 + RLBUF_SIZE * 2) は、ﾃﾞｺｰﾄﾞ用 参照ﾗｲﾝ/符号化ﾗｲﾝ */


/******************************************************/
/* ｿﾌﾄ･ｺｰﾃﾞｯｸ ﾊﾞｯﾌｧﾓｰﾄﾞ                               */
/******************************************************/
/* #define SCN             0
   #define PRT             1 */
#define MDM             0
#define MEM1            1
#define MEM2            2
#define MEM3            3
#define ECM_BUF         4
#define MEMFIP          5     /* 93.11.05 Soft:Tanaka */
/******************************************************/

/* ｿﾌﾄ･ｺｰﾃﾞｯｸ･ﾌﾞﾛｯｸ(ｴﾝｺｰﾄﾞ/ﾃﾞｺｰﾄﾞ共通) */
struct Buf_p_t {
	UBYTE	*Buf;		/* バッファ先頭アドレス  ﾎﾟｲﾝﾀの型を UWORD から UBYTE に変更 */
	UDWORD	Adr;		/* バイト位置 For Debug UWORD-->unsigned long */
	UBYTE	Bit;		/* ビット位置 */
};

/*--------------------------------------*/
/* Byte と word データの操作  by S.Wang */
/*--------------------------------------*/
union Byte_WordData_u_t {
	struct{
		UBYTE	H;
		UBYTE	L;
	} Byte;
	UWORD	Word;
};

/*--------------------------------------*/
/* Softcodec用ﾊﾟﾗﾒｰﾀ by S.Wang          */
/*--------------------------------------*/
struct CdcBlk_t {
	UBYTE BufMode;			/* ｺｰﾃﾞｯｸ ﾊﾞｯﾌｧﾓｰﾄﾞ*/
	UBYTE Coding;			/* coding_method */
	UBYTE K_Para;			/* パラメータ Ｋ */
	UBYTE DecBits;	        /* 未書き込み端数ＭＨ、ＭＲデータのビット数（０～７）*/
	UWORD Line_Cntr;		/* ｺｰﾃﾞｯｸライン数*/
	UWORD Img_Size;	    	/* 1ライン画素数サイズ */
	struct Buf_p_t  *Wp;
	struct Buf_p_t  *Rp;
	union Byte_WordData_u_t DecData;	/* 未書き込み端数ＭＨ、ＭＲデータのビット */
};

/*------------------------------*/
/* RLﾊﾞｯﾌｧ用操作ﾊﾟﾗﾒｰﾀ	Y.S		*/
/*------------------------------*/
struct	WorkBuf_t {
  UWORD		Cout;      		/* rl ﾊﾞｯﾌｧｻｲｽﾞｶｳﾝﾄ(rlﾊﾞｯﾌｧ相対位置 0 -- RL_SIZE) work.a_adr - wbuf.data で得られる */
  UBYTE		*Data;     		/* 使用rlﾊﾞｯﾌｧの先頭ｱﾄﾞﾚｽ */
  UBYTE		Flag;           /* rl=0のFlag S.Wang 96/07/04 */
};

/*--------------------*/
/* 変化画素制御構造体 */
/*----------------Y.S-*/
struct	ScdcWorkData_t {
	UWORD	a_pos;	 		/* 走査ライン用変化点の位置  */
	UWORD	a0;		 		/* a0のrl値 */
	UWORD	a1;
	UWORD	a2;
	UWORD	b_pos;	 		/* 参照ライン用変化点の位置  */
	UWORD	b0;
	UWORD	b1;
	UWORD	b2;
	UBYTE	a_color;
	UBYTE	b_color;
	UWORD	V0_Count;		/* v0連続の場合の処理: Ｖ０の個数 Decode used only */
	UBYTE	V0_Flag;		/* V0モードの flag Decode used only */
   	UWORD   V0_Begin;     	/* v0連続の場合の処理: 開始位置検出した時の参照ラインのCount数 Decode used only */
	UWORD	V0_End;      	/* v0連続の場合の処理: 終了位置検出した時の参照ラインのCount数 Decode used only */
};

/*--------------------------*/
/* Fill 制御に必要なﾊﾟﾗﾒｰﾀ 	*/
/*---------------------Y.S--*/
#if(0)
//struct	FillCntlData_t	{
//	UBYTE	MseMethod;
//	UWORD	MinLineSize;
//	UWORD	DocLength;
//	UWORD	TotalTxSize;
//	UBYTE	MseCount;
//};
#endif
/*----------------------------------------------*/
/*	ソフトコーデック使用時の送信の縮小のため	*/
/*-----------------------------------------Y.S--*/
#define MAX_REDUCTION	70	/* 自動縮小最大縮小率 - DUMMY */

/* ﾓｰﾄﾞによる縮小率の種別(ﾒﾓﾘ送信時のみ) */
#define FINE2NORM		1
#define SUPERFINE2NORM	2
#define SUPERFINE2FINE	3
/* 主走査縮小方式 */
#define AUTO				0		/* 自動縮小 */
#define A3_TO_A4			1		/* 固定縮小(A3->A4, 27/38) */
#define A3_TO_B4			2		/* 固定縮小(A3->B4, 32/38) */
#define B4_TO_A4			3		/* 固定縮小(B4->A4, 27/32) */
#define P_A3_TO_A4			4		/* 固定縮小(A3->A4, 26/38) */
#define P_B4_TO_A4			5		/* 固定縮小(B4->A4, 26/32) */
#define HFINE_TO_OTHER		6		/* 原稿幅かわらずモードのみ変更 mm->mm 50%(画素数）原稿幅変わらず */
#define HFA3_TO_A4_OTHER	7		/* HFINE A3 -> A4 OTHER MODE */
#define HFA3_TO_B4_OTHER	8		/* HFINE A3 -> B4 OTHER MODE */
#define HFB4_TO_A4_OTHER	9		/* HFINE B4 -> A4 OTHER MODE */
#define R12_TO_R8			10		/* 原稿幅かわらずモードのみ変更 mm->mm 50%(画素数）原稿幅変わらず */

/* 縮小/拡大制御ﾌﾞﾛｯｸ */
struct reduction_t {
	UWORD linecnt;		/* ｺｰﾙされた回数をｶｳﾝﾄするｶｳﾝﾀ */
	UWORD cntr_loop;		/* ｶｳﾝﾀを０に戻すﾀｲﾐﾝｸﾞ
			   固定縮小時　32 or 38　　可変縮小時 40 */
	UBYTE *r_tbl_p;		/* 縮小ﾃｰﾌﾞﾙを使用する位置 */
};

/*--------------------------------------*/
/*	ＲＴＮ返送連続エラーライン数設定	*/
/*----------------------------------Y.S-*/
#define CONTI_ERROR	20

/*------------------------------------------------
	内蔵CPU内でメンテナンスＳＷ－Ｆを参照するため
	By Y.Suzuki 1997/10/16
--------------------------------------------------*/
#define SCD_MNT_SW_MAX	10
#define SCD_MNT_SW_F0	0
#define SCD_MNT_SW_F1	1
#define SCD_MNT_SW_F2	2
#define SCD_MNT_SW_F3	3
#define SCD_MNT_SW_F4	4
#define SCD_MNT_SW_F5	5
#define SCD_MNT_SW_F6	6
#define SCD_MNT_SW_F7	7
#define SCD_MNT_SW_F8	8
#define SCD_MNT_SW_F9	9

#endif
