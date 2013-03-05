/*
 *	@(#)$Id: PRT_DEF.H,v 1.1.1.1 2005/04/04 04:24:06 mi93007 Exp $
 *	FileName:	/home2/prj/Eva/Src/inc/printer.h
 *	Create:	Thu Apr  2 10:21:45 1998	by	ishiyama
 *	Description:
 *		Printer and Other Task Interface
 *	Change Log:
 *		
 */
#ifndef	PRINTER_H
#define PRINTER_H

#if (0) /* 未使用 1998/11/19 by T.Soneoka */
**/* extern UBYTE PrintEvtStatus */
**/* for EvtNo.PrinterStat */
**#define PRT_EVT_STATUS_RX	(0x01 << 0)	/* Printer Status Receive */
**
**/* for EvtNo.PrintImage */
**/* use for Page Printer Only */
**#define PRT_EVT_DMA_END		(0x01 << 1)	/* Printer DMA End */
**#define PRT_EVT_TOD			(0x01 << 2)	/* TOD Rx */
#endif

/* use for Thermal Printer Only */
#define PRT_EVT_ERROR				(0x01 << 3)	/* プリンタエラー各種 */
#define PRT_EVT_CUT_ON				(0x01 << 4)	/* 記録紙カット実行可 */
#define PRT_EVT_DOC_READY_COMPLETE	(0x01 << 5)	/* 待機位置セット完了 */
#define PRT_EVT_DOC_PRINT_POS		(0x01 << 6)	/* 印字位置セット完了 */

#if (0) /* 未使用 1998/11/19 by T.Soneoka */
**/*
** *	Printer Error Statuts
** */
**#define PRTERROR_COVER_OPEN			0x01 /* カバーオープン */
**#define PRTERROR_JAM				0x02 /* ジャム */
**#define PRTERROR_NO_PAPER			0x04 /* 記録紙なし */
**#define PRTERROR_FAN_ALARM			0x08 /* ファンモータの異常 */
**#define PRTERROR_ROS_MOTOR_ABNORMAL	0x10 /* スキャナモータの異常 */
**#define PRTERROR_LASER_ABNORMAL		0x20 /* レーザー異常 */
**#define PRTERROR_HIGH_TEMP			0x40 /* 定着器の異常温度検出 */
#endif


/*
 *	To Print Task
 */
/* PRN_ImagePrintTaskからPrinterTaskへのメッセージ */

#if (0) /* 未使用 1998/11/19 by T.Soneoka */
**	#define MSG_LIST_PRINT_QUEUE_SET	2	/* リストプリント開始命令 */
**	#define MSG_PRINT_QUEUE_FLASH		3	/* プリント・キュー全終了要求 */
**	#define MSG_PRINT_SUSPEND			4	/* プリント中断要求 */
**
**	/* from Debug Task */
**	#define MSG_TEST_PRINT				5	/* Test Print for GateArray Test */
**	#define MSG_ACK						10
#endif

/* PrinterTaskからPRN_ImagePrintTaskへのメッセージ */
#define FROM_PRINTER_TASK	1
	#define MSG_CONTINUE			0	
	#define MSG_PRINT_END			2	/* １ページ正常にプリント完了 */
	#define MSG_PRINT_STOPSW		4	/* STOPSWでプリント停止 */
	#define MSG_PRINT_ERROR			5	/* 記録紙ジャム等で停止 */

	#if (0) /* 未使用 1998/11/19 by T.Soneoka */
	**	#define MSG_PRINT_QUEUE_ACK		1	/* プリントキューに登録完了 */
	**	#define MSG_PRINT_SUSPEND_ACK	3	/* プリント中断受付 */
	**	#define MSG_PRINTER_READY		6	/* TBD:プリンタからエラー解除通知 */
	**	#define MSG_PRINT_MEM_ERROR		7	/* Memory Open Error */
	**	#define MSG_PRINT_PAGE_START	8	/* KURUMIプリンタ起動タイミング(PleaseWait表示解除) */
	**	#define MSG_PRINT_DETECT_ERROR	9	/* プリンタ・エラー発生通知(表示更新用) */
	#endif

/* Print Task 内部メッセージ(MeSsaGe Local) */
#define FROM_PRINTIMAGE_TASK			3
#define FROM_PRINT_IMAGE_EVENT_TASK		10

#if (0) /* 未使用 1998/11/19 by T.Soneoka */
**	#define FROM_MAKEIMAGE_TASK				2
**	#define FROM_WATCHPRINTER_TASK			4
**	#define FROM_MAKEIMAGE_DECODE_TASK		5
**	#define FROM_MAKEIMAGE_LIST_TASK		6
**	#define FROM_MAKEIMAGE_LIST_DECODE_TASK	7
**	#define FROM_MAKEIMAGE_DIRECT_TASK		8
**	#define FROM_WATCHPRINTER1SEC_TASK		9
**	#define FROM_MAKE_EXIT_TIMING_TASK		11
**	#define FROM_COPYSTORE_TASK				12
**	#define FROM_WAIT_PRINTER_READY_TASK	13
**	#define FROM_ADDINDEXQUEUE_TASK			14
**	#define FROM_WATCH_PRINTER_EVENT_TASK	15
#endif

	#define MSGL_PAGE_END					12	/* １ページ正常にプリント完了 */
	#define MSGL_PRINTER_STOP				13	/* STOPSWでプリント停止 */
	#define MSGL_PRINTER_ERROR				14	/* プリントエラー */
	#define MSGL_START_MAKEIMAGE			18	/* Image 作成スタート */
	#define MSGL_READY_POS_COMP				28	/* 印字待機位置に来た*/
	#define MSGL_PREPARE_MAKEIMAGE			29	/* 記録紙引き戻し By O.Kimoto 1998/10/22 */
	#define MSGL_PRINT_CLOSE				34	/* 記録紙待機位置へ移動 1998/11/11 by T.Soneoka */
	#define MSGL_PRINTER_ERROR_CONTI		35	/* プリンタエラー表示更新処理のみ */

	#if (0) /* 未使用 1998/11/19 by T.Soneoka */
	**	#define MSGL_INDEX_QUEUE_ACK			10	/* プリントキューに登録完了 */
	**	#define MSGL_SUSPEND_ACK				11	/* プリント中断受付 */
	**	#define MSGL_PRINTER_READY				15	/* プリンタからエラー解除通知 */
	**	#define MSGL_DEQUEUE_INDEX				16	/* Index Queue に空きができたことを通知 */
	**	#define MSGL_DELETE_QUEUE				17	/* Print Task 内部 Message */
	**	#define MSGL_PRINTER_DMA_END			19	/* Printer DMA 終了 */
	**	#define MSGL_PRINTER_TOD				20	/* Printer TOD 検出 */
	**	#define MSGL_PRINT_EXIT_TIMEUP			21	/* Printer 排出完了時間経過 */
	**	#define MSGL_DEQUEUE_PAGE				22	/* Page Memory に空きができたことを通知 */
	**	#define MSGL_PRINT_QUEUE_FLASH			23	/* プリント・キュー全終了要求 */
	**	#define MSGL_PRINT_MEM_ERROR			24	/* Memory Open Error */
	**	#define MSGL_DIVID_PAGE					25	/* 分割ページ */
	**	#define MSGL_PRINT_SUSPEND				26	/* Printer Suspend Request */
	**	#define MSGL_PRINTER_WARMUP				27	/* Printer が印字可能になった */
	**	#define MSGL_ERROR_NO_PAPER				30	/* 紙なしエラー  1998/10/23 by T.Soneoka */
	**	#define MSGL_ERROR_JAM					31	/* 記録紙ＪＡＭエラー  1998/10/23 by T.Soneoka */
	**	#define MSGL_ERROR_CUT_ERROR			32	/* カットエラー  1998/10/23 by T.Soneoka */
	**	#define MSGL_ERROR_COVER_OPEN			33	/* プリンタカバーオープンエラー  1998/10/23 by T.Soneoka */
	#endif

	#define	PRTPAGE_COL	(256 / 2)

#if (0) /* 未使用 1998/11/19 by T.Soneoka */
**/*****************************************************************************
** *転送先ﾌﾗｸﾞ
********************************************************************************/
**
**#define 		SUB_FLG		1	/* 転送先有り １
**							       転送先無し ２ */
**								  
**/*****************************************************************************
** *ﾍｯﾀﾞ、ﾌｯﾀﾞ印字種類
********************************************************************************/
**
**#define			KIND		HED_PRT		/* ﾍｯﾀﾞ印字
**							FED_PRT 	  ﾌｯﾀﾞ印字 */
**
**/*****************************************************************************
** *明細項目印字ﾎﾟｲﾝﾄ
********************************************************************************/
**
**#define		LINE_PRT1	1			/* 罫線印字ﾎﾟｲﾝﾄ1 */
**#define		LINE_PRT2	5			/* 罫線印字ﾎﾟｲﾝﾄ2 */
**#define		LINE_PRT3	30			/* 罫線印字ﾎﾟｲﾝﾄ3 */
**#define		LINE_PRT4	70			/* 罫線印字ﾎﾟｲﾝﾄ4 */
**#define		LINE_PRT5	80			/* 罫線印字ﾎﾟｲﾝﾄ5 */
**
**#define		KYENAME		2			/* ﾜﾝﾀｯﾁｷｰ名ﾎﾟｲﾝﾄ */
**
**#define		NAMEPOINT	6			/* 相手先名入力位置 */
**
**#define		TELPOINT	31			/* FAx番号入力位置 */
**
**#define		PRINT_BUFFER_RAW	2
**
**#define NUM_OF_PAGES	1
#endif

/* プリンターの使用状態を示す。 */
#define PRINT_IDLE		0	/* 待機 */
#define PRINT_IMAGE		1	/* イメージプリント */
#define PRINT_LIST		2	/* リストプリント */
#define PRINT_LISTIMAGE	3	/* イメージ付きリストプリント */
#define PRINT_SCOPY		4	/* シングルコピー */
#define PRINT_RXPRINT	5	/* プリンター受信 */

#define HEAD_ROHM		0
#define HEAD_KYOCERA	1

/* SATSUKI2 追加 start by Y.Kano 2003/06/24 */
#if defined(SATSUKI2)
/*---------------------------------------------------*/
/* カッター位置チェック（ CutterPosition() ） 戻り値 */
/*---------------------------------------------------*/
#define CUTTER_BUSY		0		/* センサーの間(BUSY)	*/
#define	CUTTER_LEFT		1		/* 左側待機位置			*/
#define	CUTTER_RIGHT	2		/* 右側待機位置			*/
/*-------------------------------------------------*/
/* カッタードライブ( CutterDrive() )入力パラメータ */
/*-------------------------------------------------*/
#define	CUT_LEFT	1		   /* 左に向かって切る			*/
#define	CUT_RIGHT	2		   /* 右に向かって切る			*/
#define	CUT_BRAKE	3		   /* ブレーキをかける			*/
#define CUT_OFF		4		   /* カッターモーターをOFFする */

/*----------------------------------*/
/* プリンタードライバー制御テーブル */
/*----------------------------------*/
struct PRN_Control_def {
/* オープンパラメータ */		  /* 相対アドレス: 内容					*/
	UBYTE  CutterPhase;			  /* 17 :カッターの動作状況				*/
	UBYTE  CutterBusy;			  /* 18 :カッター動作中					*/
	WORD   CutterJamCount;		  /* 28 :カッタージャム検出カウンタ		*/
	WORD   CutterBrakeCount;	  /* 30 :カッターブレーキ時間カウンタ	*/
};
/************************************************************************
 * ＰＳ２閾値															*
 * PS2DEFAULT															*
 * 5C:デフォルト値														*
 * 0x7A:経年変化対応値													*
 * 0x99:経年変化対応値													*
 * 加納 義彦															*
 * 2003/10/18															*
 ************************************************************************/
#define PS2DEFAULT	0x8A	/* 閾値の変更 by Y.Kano 2003/10/31 */
#define PS2_LIMIT_1	0x99
#define PS2_LIMIT_2	0xA3

#define PS2_ENDMARKOFFSET	0x1C	/* エンドマークオフセット by Y.Kano 2003/10/23 */

#endif
/* SATSUKI2 追加 end   by Y.Kano 2003/06/24 */

#if defined(HINOKI2) && (PRO_PAPER_AD_SENSOR_INIT == DISABLE)	/* ＰＳ２自動調整機能 削除 by Y.Kano 2004/04/05 */ /* 復活させます。by Y.kano 2004/12/10 */
#define	VSIMI_THRESHOLD		0		/* Ｖｓｉｍｉ（仮想スライスレベル） */
#define	VSIM2_THRESHOLD		1		/* Ｖｓｉｍ２（仮想スライスレベル） */
#define	PS2_THRESHOLD		2		/* ＰＳ２の実スライスレベル			*/
#endif

#endif /* PRINTER_H */
