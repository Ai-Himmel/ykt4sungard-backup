/**********************************************************************************************
*				By : NOBUKO
*			  Date : Mon 20 Dec. 1993 (\SRC\RICE\DEFINE\MEMFILE.H)
*		 Copy Date : Tue 12 Sep. 1995
*		 File Name : MEMFILE.H
*					 メモリ蓄積 原稿種別
*	   Module Name :
**********************************************************************************************/

#ifndef memfile_h
	#define	memfile_h

#define SYS_MEM_FILE_EMPTY					   0	/* 空インデックス		  */
#define SYS_MEM_TX_FILE						   1	/* メモリ送信原稿		  */
#define SYS_MEM_RX_FILE						   2	/* メモリ受信原稿		  */
#define SYS_MEM_POLLING_FILE				   3	/* ポーリング送信原稿	  */
#define SYS_MEM_DB_POLLING_FILE				   4	/* 検索ポーリング送信原稿 */
#define SYS_MEM_SECURE_RX_FILE				   5	/* 親展受信原稿			  */
#define SYS_MEM_MULTI_COPY_FILE				   6	/* マルチ・コピー原稿	  */
#define SYS_MEM_FIP_FILE					   7	/* FIP原稿				  */
#define SYS_MEM_BATCH_TX_FILE1				   8	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE2				   9	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE3				   10	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE4				   11	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE5				   12	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define	SYS_MEM_REMOTE_TX_FILE				   13	/* リモート送信原稿       Jan.19,1994 By S.K */
#define	SYS_MEM_BUFFERING_RX_FILE			   14	/* バッファリング受信原稿 Jun.15,1994 By M.T */
#define	SYS_MEM_CLASS1_TX_FILE				   15	/* ﾛｰｶﾙｽｷｬﾝ用送信原稿     by Y.Tanimoto 1996/06/26 */
#define SYS_MEM_CL1_RX_FILE                    16	/* Class 1 ﾛｰｶﾙﾌﾟﾘﾝﾄ用原稿 by Y.Tanimoto 1996/06/28 */
#define SYS_MEM_PC_RX_FILE					   17	/* ＰＣプリントファイル	  by J.Miyazaki 1996/08/10 */
#define	SYS_MEM_MAIL_TX_FILE				   18	/* メール送信原稿 */
#define	SYS_MEM_MAIL_RX_FILE				   19	/* 受信メール */

#define MEM_NSORT_COPY_FILE						20	/* ノン・ソート用コピー・ファイル  1998/10/05 by T.Soneoka */
#define MEM_REALTIME_COPY_FILE					21	/* リアルタイムコピー・ファイル  1998/10/05 by T.Soneoka */

#endif
