/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR/ANZU_L                                             */
/*  ファイル名   : sys_def.h                                                 */
/*  作成者       : 橘正樹                                                    */
/*  日  付       : 1997/05/17                                                */
/*  概  要       : フラッシュ書き換えシステム                                */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef SYS_DEF_H
 #define SYS_DEF_H	1

/*------------------------------------------------------------------------
**	ＬＥＤ点灯
*/
#define	LED_SEL_FAX_COM			1		/* 通信中ＬＥＤ				*/
#define	LED_SEL_MEMORY_RX		2		/* 代行受信ＬＥＤ			*/
#define	LED_SEL_AUTO_RX			3		/* 自動受信ＬＥＤ			*/
#define	LED_SEL_STAMP			4		/* 済みスタンプＬＥＤ		*/
#define	LED_SEL_COPY_MODE		5		/* コピーモードＬＥＤ		*/
#define	LED_SEL_FAX_MODE		6		/* ファクスモードＬＥＤ		*/
#define	LED_SEL_ON_HOOK			7		/* フック／会話予約ＬＥＤ	*/
#define	LED_SEL_ALARM			8		/* アラームＬＥＤ			*/
#define	LED_SEL_PAPER_JAM		9		/* 紙づまりＬＥＤ			*/
#define	LED_SEL_REPLACE_PAPER	10		/* 記録紙ＬＥＤ				*/
#define	LED_SEL_MEMORY_TX		11		/* メモリ送信ＬＥＤ			*/
#define	LED_SEL_MODE_GRAY		12		/* 画質：写真				*/
#define	LED_SEL_MODE_SFINE		13		/* 画質：Ｓファイン			*/
#define	LED_SEL_MODE_FINE		14		/* 画質：ファイン			*/
#define	LED_SEL_MODE_NORMAL		15		/* 画質：ノーマル			*/
#define	LED_SEL_DST_DARK		16		/* 濃度：濃く				*/
#define	LED_SEL_DST_NORMAL		17		/* 濃度：普通				*/
#define	LED_SEL_DST_LIGHT		18		/* 濃度：薄く				*/
#define	LED_SEL_PRT_ALARM		19		/* プリンタアラームＬＥＤ	*/

#endif
