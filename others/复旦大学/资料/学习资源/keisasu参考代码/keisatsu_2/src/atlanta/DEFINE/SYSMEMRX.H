/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\sysmemrx.h */
#ifndef sysmemrx_h
	#define sysmemrx_h

#include "\src\atlanta\define\sysjrnl.h"

/************************************************************************
 * メモリ受信原稿プリント												*
 * struct SYS_MemoryRxPrintData_t SYB_MemoryRxPrint[SYS_MEMORY_RX_MAX]	*
 * sysmemrx.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
struct	SYS_MemoryRxPrintData_t {
	UBYTE	Status;			/* 動作状態 */
	UBYTE	Protect;		/* プリントプロテクト設定状態 For ANZU 1995.12.22 Eguchi */
	UBYTE	Cassette;		/* カセット指定 */
	UBYTE	StackNumber;	/* マルチ回線時どの回線に使用されているか記憶（マルチ回線） */
	UDWORD	ReceiveTime;	/* １枚目受信確定時間（マルチ回線） */
	struct SYS_JournalData_t * JournalPoint;
	UWORD	StorePage;		/* 受信枚数 ０～６５５３５ページまで Sep.29,1995	*/
	UWORD	RotatePage;		/* 回転枚数 ０～６５５３５ページまで By M.Kotani 97/03/26 */
	UWORD	PrintPage;		/* プリント枚数 ０～６５５３５ページまで Sep.29,1995 */
	UWORD	ErasePage;		/* 消去ペ－ジ ０～６５５３５ページまで Sep.29,1995 */
};

/************************************************************************
 * メモリ受信原稿プリントの動作状態										*
 * struct SYS_MemoryRxData_t												*
 * sysmemrx.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_MEMORY_RX_EMPTY		0	/* 未使用 */
#define SYS_MEMORY_RX_SETTING	1	/* セット中 */
#define SYS_MEMORY_RX_STORE		2	/* メモリ受信原稿(受領証含む)蓄積中 */
#define SYS_MEMORY_RX_PRINT		3	/* メモリ受信原稿（受領証含む)プリント*/
									/* プリント待ち */
#define SYS_MEMORY_RX_POWEROFF	4	/* 停電により消去された */
#define SYS_MEMORY_RX_STORE_PRINT	5	/* 受信中に正順プリント *//* By M.Tachibana 1998/05/19 */
#define SYS_MEMORY_RX_FAST_PRINT	6	/* 受信中に正順プリント、受信終了 *//* By M.Tachibana 1998/05/19 */

/************************************************************************
 * メモリ受信原稿のプロテクト状態										*
 * struct SYS_MemoryRxData_t												*
 * 1995/12/22 Eguchi													*
 ************************************************************************/
#define	SYS_PROTECT_ON	1
#define	SYS_PROTECT_OFF	0

/************************************************************************
 * メモリ受信原稿プリントの回線番号										*
 * struct SYS_MemoryRxData.StackNumber									*
 * 1996/08/14															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_STACK_NUMBER0		0	/* １回線目 */
#define SYS_STACK_NUMBER1		1	/* ２回線目 */
#define SYS_STACK_NUMBER2		2	/* ３回線目 */
#define SYS_STACK_NUMBER3		3	/* ４回線目 */
#define SYS_STACK_NUMBER4		4	/* ５回線目 */
#define SYS_STACK_NUMBER5		5	/* ６回線目 */

/************************************************************************
 * メモリ受信原稿プリントの受信時間										*
 * struct SYS_MemoryRxData.ReceiveTime									*
 * 1996/08/14															*
 * 吉川弘康																*
 ************************************************************************/

/************************************************************************
 * メモリ受信原稿プリントのカセット指定									*
 * struct SYS_MemoryRxData.Cassette										*
 * 記録紙なし状態になった時に最後にプリントしていたカセットを代入する	*
 * このカセットに記録紙がセットされるとプリントを再開する				*
 * define\sysdoc.hの指定カセット（SYS_AUTO_CASSETTE等）の値を使用する	*
 * 1996/08/14															*
 * 吉川弘康																*
 ************************************************************************/

#endif
