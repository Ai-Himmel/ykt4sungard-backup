/* Oct.3,1995 By S.K */
#ifndef sysprint_h
	#define	sysprint_h

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Jan.10,1994
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned char	SYS_DocumentPrintClass;
* DESCRIPTION:
************************************************************************/
#define	SYS_PRINT_CLASS_INITIAL		1	/* プリンターの初期化要求 					*/
#define	SYS_PRINT_CLASS			2	/* 印字ページが鋸っている時 					*/
#define	SYS_PRINT_CLASS_END		3	/* 印字ページが残っていない時で排出				*/
#define	SYS_PRINT_CLASS_FORCE		4	/* 強制印字 							*/
#define	SYS_PRINT_CLASS_LIST_MEMORY	5	/* 通常コマンド用チェック・メッセージ付き原稿印字要求		*/
#define	SYS_PRINT_CLASS_LIST_MONITOR	6	/* 通常コマンド用モニター・レポート付き原稿印字要求 		*/
#define	SYS_PRINT_CLASS_LIST_BA_MEMORY	7	/* 一括送信用チェック・メッセージ付き原稿印字要求 		*/
#define	SYS_PRINT_CLASS_LIST_BA_MONITOR	8	/* 一括送信用モニター・レポート付き原稿印字要求 		*/
#define SYS_PRINT_CLASS_EXIT		9	/* BY O.K Oct,13,1994						*/
#define	SYS_PRINT_CLASS_LIST_CIPHER	10	/* 暗号化受信通知リスト 印字要求 By Y.Suzuki 1997/06/19		*/
#define	SYS_PRINT_CLASS_RETURNED_MAIL	11	/* ｲﾝﾀｰﾈｯﾄFAX用不達通知 印字要求 By Y.Tanimoto 1998/03/11	*/
#define	SYS_PRINT_CLASS_REALTIMECOPY	12	/* リアルタイムコピー印字要求 1998/10/08 by T.Soneoka */
#define	SYS_PRINT_CLASS_PRINTER_RX		13	/* プリンタ受信原稿印字要求 by H.Hirao 1998/11/06 */
#endif

