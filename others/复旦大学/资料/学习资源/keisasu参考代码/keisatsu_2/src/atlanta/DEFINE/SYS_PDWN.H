/* Oct.3,1995 By S.K */
#ifndef	sys_pdwn_h
	#define	sys_pdwn_h

/*----------------------------------------------------*/
/* 停電検出リストステータス                           */
/* unsigned char SYB_PowerDownListStatus              */
/* 1994/11/26 Y.Murata                                */
/*----------------------------------------------------*/
#define SYS_POWER_POLLING		0x01	/* ポーリング原稿消去通知     */
#define SYS_POWER_DB_POLL		0x02	/* 検索ポーリング原稿消去通知 */
#define SYS_POWER_REMOTE_FAX	0x04	/* リモートＦＡＸ原稿消去通知 */

#endif

