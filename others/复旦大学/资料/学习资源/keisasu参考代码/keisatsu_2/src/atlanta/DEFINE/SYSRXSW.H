#ifndef sysrxsw_h
	#define sysrxsw_h

/************************************************************************
 * 受信モード															*
 * unsigned char SYB_RxModeSwitch										*
 * sysrxsw.jsw参照														*
 * 1993/11/24	吉川弘康												*
 * 変更の際はSYSRXSW.HDRも変更して下さい。  By N.S. '94,07,19			*
 ************************************************************************/
#define SYS_AUTO_CALLED_SW		0x01		/* 自動受信/手動受信 */
#define SYS_TAD_CALLED_SW		0x02		/* 留守番電話モード ON/OFF */
/************************************************************************
 * 現在の受信モードの確認は												*
 * unsigned char far CMN_PresentReceiveMode(void)の戻り値で行う			*
 * 戻り値は下記変数･関数から算出する									*
 * unsigned char SYB_RxModeSwitch										*
 * unsigned char far CHK_AutoRxMode()									*
 * unsigned char far CHK_DialinModeON(void)								*
 * sysrxsw.jsw参照														*
 * 1994/03/04	吉川弘康												*
 * 変更の際はSYSRXSW.HDRも変更して下さい。  By N.S. '94,07,19			*
************************************************************************/
#if (0) /* 1995/12/04 Eguchi */
#define SYS_TEL_READY			0	/* 電話待機 */
#define SYS_FAX_READY			1	/* FAX待機 */
#define SYS_TEL_FAX_READY		2	/* 電話/FAX待機 */
#define SYS_ANS_FAX_READY		3	/* 留守/FAX待機 */
#define SYS_DIAL_IN_READY		4	/* ダイヤルイン待機 */
#define SYS_DIALIN_TAD_READY	5	/* ダイアルインで内蔵TAD待機 	1994/04/08 Y.M */
#define SYS_TAD_READY			6	/* 内蔵TAD待機 */
#endif
#define SYS_TEL_READY			0	/* 電話待機 */
#define SYS_FAX_READY			1	/* FAX待機 */
#define SYS_FAX_TEL_READY		2	/* 電話/FAX待機(ＦＡＸ優先） 変更点 */
#define SYS_TEL_FAX_READY		3	/* 電話/FAX待機(電話優先)    変更点 */
#define SYS_ANS_FAX_READY		4	/* 留守/FAX待機 */
#define SYS_DIAL_IN_READY		5	/* ダイヤルイン待機 */
#define SYS_DIALIN_TAD_READY	6	/* ダイアルインで内蔵TAD待機 	1994/04/08 Y.M */
#define SYS_TAD_READY			7	/* 内蔵TAD待機 */
#define SYS_MODEM_DIALIN_READY	8	/* モデムダイヤルイン待機 by H.Kubo 1998/10/15 */
#endif
