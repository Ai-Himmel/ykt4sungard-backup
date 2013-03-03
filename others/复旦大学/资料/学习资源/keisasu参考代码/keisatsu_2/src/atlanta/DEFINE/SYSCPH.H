#ifndef syscph_h
	#define syscph_h
/*--------------------------------------------------------------------
* プロジェクト : POPLAR
* ファイル名   : syscph.h
* 作成者       : By Y.Suzuki
* 日  付       : 1997/06/10
* 概  要       : SH2
*              : 暗号化用定義
* 参照
*--------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"

struct CipherBoxData_t {
	UBYTE Status;				/* 暗号化原稿受信状態 */
	UBYTE MessageStatus;		/* 暗号化受信リスト出力状態 */
	UWORD StorePage;			/* 受信枚数 ０～６５５３５ページまで */
	UWORD PrintPage;			/* プリント枚数 ０～６５５３５ページまで */
};

#define SYS_CIPHERBOX_NO			0	/* 受信なし */
#define SYS_CIPHERBOX_RECEIVE		1	/* スクランブル受信原稿有り */
#define SYS_CIPHERBOX_RECEIVING		2	/* スクランブル受信原稿有り */
#define SYS_CIPHERBOX_CONVERTING	3	/* デスクランブル中 */
#define SYS_CIPHERBOX_PRINTING		4	/* デスクランブル原稿プリント中 */
#define SYS_CIPHERBOX_PRINTOUT		5	/* デスクランブル原稿プリント完了 */

#define SYS_CIPHERBOX_MSG_EMPTY		0	/* 無し */
#define SYS_CIPHERBOX_RCV_MSG		1	/* 受信通知メッセージ */

/*-------------------------------
* UBYTE SYS_CipherComExec
* 暗号化コマンド実行状態
* 待機中:0
--------------------------------*/
#define	SYS_CIPHER_EXEC				1	/* 暗号化中*/
#define	SYS_DECIPHER_EXEC			2	/*暗号化解除中*/
#define	SYS_TX_DOC_DECIPHER_EXEC	3	/*送信予約原稿暗号化解除中*/

/*-------------------------------------------------
* 暗号化解除プリント部数の管理に使用するパラメータ
* プリントタスクにて使用する By Y.Suzuki 1998/01/07
*-------------------------------------------------*/
struct SYS_CipherNumberCopyData_t {
	UWORD StorePage;			/* 暗号化解除原稿ページ数 */
	UWORD PrintPage;			/* プリント済みページ数 */
	UBYTE ExectiveNumber;		/* プリント済み部数 */
};

/*-----------------------------------
* ２回線目からの返送されるステータス
------------------------------------*/
#define SYS_OPT_CIPHER_NOTHING			0	/* 受信なし */
#define SYS_OPT_CIPHER_OK				1	/* スクランブル受信原稿有り */
#define SYS_OPT_CIPHER_NG				2	/* スクランブル受信失敗 */


#endif	/* End of File */
