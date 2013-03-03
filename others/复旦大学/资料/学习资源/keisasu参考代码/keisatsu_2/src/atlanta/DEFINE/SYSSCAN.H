/* Copied From ICHOU by T.Nose 1996/11/28 */
/* Original File : jun\usr1:\src\rice\define\sysscan.h */
#ifndef sysscan_h
	#define sysscan_h

/************************************************************************
 * 送信モード															*
 * unsigned char SYS_DocumentScanSize									*
 * sysscan.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_DOCUMENT_A4_SIZE		0		/* A4 */
#define SYS_DOCUMENT_B4_SIZE		1		/* B4 */
#define SYS_DOCUMENT_A3_SIZE		2		/* A3 */

/*	FBS用のスキャナの識別(ADF/FBS)
**		unsigned char	SYS_ScannerExecMode;	動作中の読取り装置
**		unsigned char	SCN_MotorDriveMode;		モーター駆動経路
**		1996/06/10 s.takeuchi
*/
#define	SCN_ADF			0		/* ADF部 */
#define	SCN_FBS			1		/* FBS部 */

#endif

