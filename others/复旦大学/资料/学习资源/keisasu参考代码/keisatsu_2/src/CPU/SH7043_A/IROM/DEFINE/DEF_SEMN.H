/*--------------------------------------------------------------------------*/
/*プロジェクト: POPLAR/ANZU_L												*/
/*モジュ-ル名 : DEF_SEMN.H													*/
/*作成者名	  : 野瀬														*/
/*日  付	  : 96.10.12													*/
/*概  要	  : セマフォNo定義												*/
/*修正履歴	  : ANZUから流用 1996/10/12 T.Nose								*/
/*--------------------------------------------------------------------------*/
#ifndef DEF_SEMN_H
	#define	 DEF_SEMN_H	1

#include "\src\atlanta\define\product.h"

/************************************************************************
 * ＰＯＰＬＡＲ タイプ Ｂ												*
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合には		*
 * semno.ATD_PulseDialerの追加と										*
 * MAX_SEMNOの変更を願います 2000/10/18 H.Yoshikawa						*
 ************************************************************************/
#if defined(POPLAR_B) || defined(POPLR_BN)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t	 {
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
 * ＰＯＰＬＡＲ タイプ Ｌ												*
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合には		*
 * semno.ATD_PulseDialerの追加と										*
 * MAX_SEMNOの変更を願います 2000/10/18 H.Yoshikawa						*
 ************************************************************************/
#if defined(POPLAR_L) || defined(POPLAR_N)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t	 {
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
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合には		*
 * semno.ATD_PulseDialerの追加と										*
 * MAX_SEMNOの変更を願います 2000/10/18 H.Yoshikawa						*
 ************************************************************************/
#if defined(POPLAR_H)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t	 {
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
 * ＡＮＺＵ タイプ Ｌ													*
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合には		*
 * semno.ATD_PulseDialerの追加と										*
 * MAX_SEMNOの変更を願います 2000/10/18 H.Yoshikawa						*
 ************************************************************************/
#if defined(ANZU_L)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t	 {
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
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合には		*
 * semno.ATD_PulseDialerの追加と										*
 * MAX_SEMNOの変更を願います 2000/10/18 H.Yoshikawa						*
 ************************************************************************/
#if defined(ANZU_V)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#define	MAX_SEMNO	19		/* 18->19 1999/10/19 Y.Murata */
struct semno_data_t	 {
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
 * ＳＡＫＡＫＩ															*
 * 1998/10/09 H.Yoshikawa												*
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合に			*
 * semno.ATD_PulseDialerを使用します。 2000/10/18 H.Yoshikawa			*
 ************************************************************************/
#if defined(SAKAKI)
/*#define	MAX_SEMNO	18*/		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
/*#define	MAX_SEMNO	19*/		/* 18->19 1999/10/19 Y.Murata */
#define	MAX_SEMNO	20
struct semno_data_t	 {
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
	WORD ATD_PulseDialer;			/**パルス誤ダイヤル用セマフォ					H.Yoshikawa 2000/10/18*/
};
#endif

/************************************************************************
 * ＨＩＮＯＫＩ															*
 * 誤ダイヤル対策として、PRO_DIAL_PULSE_TASKをENABLEした場合には		*
 * semno.ATD_PulseDialerの追加と										*
 * MAX_SEMNOの変更を願います 2000/10/18 H.Yoshikawa						*
 ************************************************************************/
#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined(STOCKHM2) /* HINOKI2 2001/11/12 T.Takagi */
#if (0)
** #define	MAX_SEMNO	18		/* 15->18 WRITE_OPEN_SEM 1997/12/16 Y.Murata */
#else
/*#define	MAX_SEMNO	19*/		/* 18->19 SCDC_DRAM_Access 1998/10/05 O.Kimoto */
/*#define	MAX_SEMNO	20		/* 19->20 1999/10/19 Y.Murata */
#define	MAX_SEMNO	21			/* 20->21 for 誤ダイヤル  2000/11/24 by T.Soneoka */
#endif

struct semno_data_t	 {
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
	WORD SCDC_DRAM_Access;			/** ソフトコーデックでＤＲＡＭアクセスのセマフォ By O.Kimoto 1998/10/05 */
	WORD OPR_UpDateDisp;			/**表示ＵＰＤＡＴＥﾉセマフォ				add by Y.Murata 1999/10/19*/
	WORD ATD_PulseDialer;			/**パルス誤ダイヤル用セマフォ					H.Yoshikawa 2000/10/18	2000/11/24 by T.Soneoka */
};
#endif


#endif
