#include "\src\atlanta\define\product.h"

#define _NFILE 20

/* 低水準インターフェース */
#define STDIN	0			/*	標準入力	*/
#define STDOUT	1			/*	標準出力	*/
#define STDERR	2			/*	標準エラー出力	*/

#define FLMIN	0			/*	最小のファイル番号	*/
#define FLMAX	3			/*	ファイル数の最大値	*/

/*	ファイルのフラグ	*/
#define O_RDONLY	0x0001	/*	読み込み専用	*/
#define O_WRONLY	0x0002	/*	書き込み専用	*/
#define O_RDWR		0x0004	/*	読み書き両用	*/

/*	特殊文字コード	*/
#define CR 0x0d
#define LF 0x0a
#if(0)
struct _iobuf{
	UBYTE *_bufptr;	 	/* バッファへのポインタ */
	DWORD _bufcnt; 		/* バッファカウンタ */
	UBYTE *_bufbase; 	/* バッファベースポインタ */
	DWORD _buflen; 		/* バッファ長 */
	UBYTE _ioflag1; 	/* I/O フラグ */
	UBYTE _ioflag2; 	/* I/O フラグ */
	UBYTE _iofd; 		/* I/O フラグ */
};
#endif
