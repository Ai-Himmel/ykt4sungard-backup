/* Oct.3,1995 By S.K */
#ifndef syslocal_h
	#define syslocal_h

/************************************************************************
 * ローカル機器設定														*
 * unsigned char SYB_LocalStatus[SYS_LOCAL_MAX];						*
 * syslocal.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
/* 
 * SYB_LocalStatus[0]
 */
#define SYS_MEMORY_TX_ON		0x01		/* メモリ送信 */
#define SYS_STAMP_ON			0x02		/* 済スタンプ */
/* #define SYS_CONFIRM_ON			0x04 */		/* 通信証     */
/* 通信証のローカル機器設定はSYB_ConfirmationReportSwitchを使うこととする           */
/* \src\rice\def_v\bkupram.cと\src\rice\define\fcm_def.hを参照のこと(石橋 94/06/29) */
#define	SYS_TTI_TX_AVAILABLE_ON	0x04	/*【CSDR-No.102】発信元ON/OFF By H.Fujimura 1998/12/17 */

 #if (PRO_RED_SCAN == ENABLE)
#define SYS_RED_SCAN			0x08		/* 朱色原稿読み取り 2002/03/04 T.Takagi */	
 #endif
#endif

