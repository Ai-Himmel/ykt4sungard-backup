/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR/ANZU_L                                               */
/*モジュ-ル名 : DEF_SEMN.H                                                  */
/*作成者名 	  : 野瀬                                                        */
/*日  付   	  : 96.10.12                                                    */
/*概  要   	  : セマフォNo定義                                              */
/*修正履歴    : ANZUから流用 1996/10/12 T.Nose                              */
/*--------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"

/* ＳＡＫＡＫＩ／ＨＩＮＯＫＩ以降の機種は、マスクプログラム変更
** by O.Kimoto 1998/09/12
*/
#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\irom\define\def_semn.h"
#else
#ifndef DEF_SEMN_H
#define  DEF_SEMN_H	1



/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｂ												*
 ************************************************************************/
#if defined(POPLAR_B) || defined(POPLR_BN)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
/*#define	MAX_SEMNO	19*/		/* 18->19 1999/10/19 Y.Murata */
#define	MAX_SEMNO	20		/* 19->20  By M.Tachibana 2002/11/18 */
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
	WORD ATD_PulseDialer;			/**パルス誤ダイヤル用セマフォ				add By M.Tachibana 2002/11/18*/
};
#endif

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｌ												*
 ************************************************************************/
#if defined(POPLAR_L) || defined(POPLAR_N) 
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
};
#endif

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｈ												*
 ************************************************************************/
#if defined(POPLAR_H)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
/*#define	MAX_SEMNO	19*/		/* 18->19 1999/10/19 Y.Murata */
#define	MAX_SEMNO	20		/* 19->20  By Y.Suzuki 2002/09/06 */
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
	WORD ATD_PulseDialer;			/**パルス誤ダイヤル用セマフォ				By Y.Suzuki 2002/09/06*/
};
#endif

/************************************************************************
 * ＡＮＺＵ タイプ Ｌ													*
 ************************************************************************/
#if defined(ANZU_L)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
};
#endif

/************************************************************************
 * ＡＮＺＵ タイプ Ｖ													*
 ************************************************************************/
#if defined(ANZU_V)
/*#define	MAX_SEMNO	18		@* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
/*#define	MAX_SEMNO	19*/		/* 18->19  1998/05/22 Eguchi*/
#define	MAX_SEMNO	20		/* 19->20 1999/10/19 Y.Murata */
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD INF_MailJournal;			/* ﾒｰﾙｼﾞｬｰﾅﾙﾌｧｲﾙのｾﾏﾌｫ 1998/05/22 Eguchi*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
};
#endif

/************************************************************************
 * ＳＡＫＡＫＩ															*
 ************************************************************************/
#if defined(SAKAKI)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
};
#endif

/************************************************************************
 * Ｌ４００後継															*
 ************************************************************************/
#if defined(POPLAR_F)
#define	MAX_SEMNO	19
struct semno_data_t  {
	WORD rtc;
	WORD lcd;
	WORD prn_serial;
	WORD ModemBuffer[8];
	WORD DPR_DownLoadFunctionTx;	/**ダウンロード関数送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadDataTx;		/**ダウンロードデータ送信用セマフォ			add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadAtTx;			/**ダウンロードＡＴコマンド送信用セマフォ	add by M.Kotani 1996/08/05*/
	WORD DPR_DownLoadTxArea;		/**ダウンロード送信エリアのセマフォ			add by M.Kotani 1996/08/05*/
	WORD MEM_WriteOpenSem;			/**メモリライトオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_ReadOpenSem;			/**メモリリードオープンのセマフォ			add by Y.Murata 1997/12/16*/
	WORD MEM_CheckSem;				/**メモリチェックのセマフォ					add by Y.Murata 1997/12/16*/
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
};
#endif


#endif

#endif
