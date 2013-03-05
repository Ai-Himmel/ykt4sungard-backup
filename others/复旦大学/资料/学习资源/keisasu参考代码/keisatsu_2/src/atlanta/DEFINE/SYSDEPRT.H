/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\sysdeprt.h */
#ifndef sysdeprt_h
    #define sysdeprt_h

/************************************************************************
 * 部門別料金管理のトータル時間											*
 * struct SYS_DepartData_t SYB_DepartFile[SYS_DEPART_MAX]					*
 * sysdeprt.doc参照														*
 * 1994/03/25															*
 * 吉川弘康																*
 ************************************************************************/
struct SYS_DepartData_t {
	UWORD  Code;		/* 部門コード(0000～9999) */
	UWORD  TxRxPage;	/* 1ヶ月の累積送受信ﾍﾟｰｼﾞ数 */
	UDWORD Cost;		/* 1ヶ月の累積料金(円単位) */
};

/****************************************************************************
 * 簡易料金管理																*
 * struct SYS_DepartManageTime_t SYB_DepartManageTimeFile[SYS_DEPART_MAX]	*
 * sysdeprt.doc参照															*
 * 1997/12/09																*
 * 本多智幸																	*
 ****************************************************************************/
struct SYS_DepartManageTime_t {  /* added by thonda 1997/12/09 */
	UWORD   Page;		/* 1ヶ月の通信枚数 */
	UDWORD  Timer;		/* 1ヶ月の通信時間 */
};
#endif
