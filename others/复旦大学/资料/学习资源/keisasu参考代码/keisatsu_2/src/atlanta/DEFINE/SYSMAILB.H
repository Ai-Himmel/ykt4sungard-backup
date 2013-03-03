/* By Y.Suzuki 1996/10/14 */
#ifndef sysmailb_h
	#define sysmailb_h

#include "\src\atlanta\define\sysmax.h"

/************************************************************************
 * 親展受信ボックス														*
 * struct SYS_MailBoxData_t SYB_MailBox[SYS_MAILBOX_MAX]				*
 * sysmailb.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_MailBoxData_t {
	UBYTE Status;				/* 親展受信状態 */
	UBYTE MessageStatus;		/* メッセージ出力状態 */
	UBYTE RemoteName[SYS_REMOTE_NAME_MAX];
								/* 親展受信相手先名(NULL含む) */
	UBYTE BoxName[SYS_BOX_NAME_MAX];
								/* 親展者名(NULL含む) */
	UWORD PassCode;				/* パスコード(暗証番号) */
								/* スカラー値 */
	UDWORD ErasedTime;			/* 消去時間 */
								/* 1992年1月1日0時0分0秒からの蓄積
								 * 秒数
								 */
};

/************************************************************************
 * 親展受信ボックスの受信状態											*
 * struct SYS_MailBoxData_t.Status										*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_MAILBOX_NO_SET				0	/* 未登録 */
#define SYS_MAILBOX_SET					1	/* オペレーション登録(親展者名登録済み) */
#define SYS_MAILBOX_RECEIVE				2	/* 親展受信原稿有り */
#define SYS_MAILBOX_RECEIVING			3	/* 親展受信原稿有り */
#define SYS_MAILBOX_RCV_TO_RECEVING		4	/* 親展受信原稿ありのＢＯＸに受信中の原稿有り */

/************************************************************************
 * 親展受信ボックスのメッセージの出力状態								*
 * struct SYS_MailBoxData_t.MessageStatus								*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_MAILBOX_MSG_EMPTY	0	/* 無し */
#define SYS_MAILBOX_RCV_MSG		1	/* 親展受信通知メッセージ */
#define SYS_MAILBOX_ERASED_MSG	2	/* 消去メッセージ */

#endif
