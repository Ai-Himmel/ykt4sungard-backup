/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\sysdblk.h */
/*----------------------------------*/
/*	通信（原稿制御関連）の構造体	*/
/*		Jan.12'94	竹内茂樹		*/
/*----------------------------------*/
/* 1994/1/14															*
 * 鈴木　　																*
 * 注)メモリには、各モードともインチで蓄積される(94.1.12現在)			*
 *	  従って､メモリにインチ／ミリどちらで蓄積されているかを示す変数は､	*
 *	  不要																*
 *	  交信がインチ／ミリのどちらで行われるかを記憶する変数は必要		*
 *	  その変数によってインチー＞ミリ変換を行うか否かを判断する(鈴木)	*/
#ifndef	sysdblk_h
	#define sysdblk_h

#include	"\src\atlanta\define\mem_def.h"

/*	原稿制御ブロック	*/
struct	SYS_DocBlockData_t {
	struct	MEM_IndexData_t		Index;	/*	ファイルインデックス	*/
	struct	MEM_DocParamData_t	Src;	/*	元原稿パラメータ		*/
	struct	MEM_DocParamData_t	Dst;	/*	先原稿パラメータ		*/
	UWORD	MinimumLineSize;			/*	最小１ラインバイト長	*/
	UWORD	DocLength;					/*	１ページ最大ライン数	*/
	UBYTE	MSE_Method;					/*	ＭＳＥ種類				*/
	UBYTE	ModeMethod;					/*	線密度 インチ／ミリ		*/
};

#endif
