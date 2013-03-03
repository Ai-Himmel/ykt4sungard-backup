/*--------------------------------------------------------------------
* プロジェクト : POPLAR
* ファイル名   : cph_def.h
* 作成者       : By Y.Suzuki
* 日  付       : 1997/06/10
* 概  要       : SH2
*              : 暗号化用定義
* 参照
*--------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#ifndef cph_def_h
	#define cph_def_h

#if(0)
*#define ARFL_NO_X_ENHANCEMENT			0x0001		/* ｴﾝﾊﾝｽﾒﾝﾄなし */
*#define ARFL_NO_X_SHRINK				0x0002		/* 主走査縮小なし */
*#define ARFL_CHECK_SEPARATOR			0x0004		/* ｾﾊﾟﾚｰﾀとデータがかぶってたらエラーにする */
*#define ARFL_CHECK_VALID_KEY			0x0008		/* キーがまちがってたらエラーにする */
*#define ARFL_AUTO_CALIB_SEP			0x0010		/* ｾﾊﾟﾚｰﾀとデータがかぶってたら自動的にｾﾊﾟﾚｰﾀを上に移動 */
*#define ARFL_SEARCH_SEPARATOR			0x0020		/* search for reverse T separator (moving separator to reverse T line)  */
*#define ARFL_PRINT_DASH				0x0040		/* print dashed line on scrambled page */
*#define ARFL_DONT_IGNORE_EDGES			0x0080		/* don't ignore top and bottom 0.5cm of source image */
*#define ARFL_NOISE_REMOVAL				0x0100		/* ノイズ除去あり */

#endif
struct CipherTbl_t {
	WORD	ErrorCode;							/* Aliroo Error Code */
	UWORD	StartPageNo;						/* 暗号化ページカウント */
	UWORD	PrintPageNo;						/* 暗号化解除時プリント部数 */
	UBYTE	Key[SYS_KEY_MAX];					/* 暗号化キー */
	UBYTE	KeyClue[SYS_KEY_CLUE_MAX];			/* キーのヒント */
	UBYTE	ExtensionKey;						/* 拡張キー */
	UWORD	OffsetServiceLabel;					/* 原稿上端からサービスラベル上端までのオフセット(ﾗｲﾝ) */
/*	UBYTE	NoiseRemovalOn;					*/	/* 暗号化解除時、ノイズ除去あり */
/*	UBYTE	ReceiveNo;							* 暗号化受信原稿Ｎ０*/
	UBYTE	PageType;							/* 原稿サイズ */
	UWORD	LineSize;							/* 暗号化/復号化前原稿ライン数 */
	UWORD	PageNo;								/* 暗号化/復号化前原稿ページ数 */
	UBYTE	PageMode;							/* 暗号化/復号化前原稿モード */
	UWORD	Flags;
};


/* CipherEncode(),CipherDecode() Return Value */
#define	SCD_ENCODE_OK		0
#define	SCD_DECODE_OK		0
#define	SCD_MEMORY_OVER		1
#define	SCD_NO_INDEX		2
#define	SCD_ENCODE_NG		3
#define	SCD_DECODE_NG		4
#define	SCD_STOP_ON			5

/* ビットマップ用領域 ＤＲＡＭ */

#if (PRO_CIPHER == ENABLE)
#define	SCD_LINE_BYTE_SIZE 	256		/* 2048/8 */
/*#define	SCD_LINE_SIZE		2802	* ALIROO 要求ＲＡＭサイズ B4 ファインラインサイズ */
#define	SCD_LINE_SIZE		2740	/* ALIROO 要求ＲＡＭサイズ B4 ファインラインサイズ */
#else
#define	SCD_LINE_BYTE_SIZE 	256		/* 2048/8 */
#define	SCD_LINE_SIZE		  2	/* ALIROO 要求ＲＡＭサイズ B4 ファインラインサイズ */
#endif

#endif
