/* By S.K Oct.2,1995 */
#ifndef	CMN_DEF_H
	#define	CMN_DEF_H	1

/************************************************************************
 * 文字列比較															*
 * unsigned char far CMN_StirngCompare();								*
 *		1.STRCMP_EQUAL( 0):string1とstring2は等しい						*
 *		2.STRCMP_UPPER( 1):string1がstring2より大きい					*
 *		3.STRCMP_LOWER( 2):string1がstring2より小さい					*
 ************************************************************************/
#define	STRCMP_EQUAL	0
#define	STRCMP_UPPER	1
#define	STRCMP_LOWER	2

/**********************************************************************
 * スピーカーボリューム値
 * SYB_MonitorSpeakerOutLevelの値 
 * 1996/01/16 Eguchi
 **********************************************************************/
#define	SYS_VOLUME_OFF		0
#define	SYS_VOLUME_MINIMUM	1
#define	SYS_VOLUME_MIDDLE	2
#define	SYS_VOLUME_MAXIMUM	3

/**********************************************************************
 * スピーカー出力状態
 * UWORD	SYS_SpeakerOutputStatus
 * 1996/02/20 Eguchi
 **********************************************************************/
#define	SYS_SPK_OFF					0x0000
#define	SYS_SPK_OUT_MONITOR			0x0001	/* 回線モニター			*/
#define	SYS_SPK_OUT_KEYBUZZER		0x0002	/* アック         		*/
#define	SYS_SPK_OUT_ENDBUZZER		0x0004	/* 終了ブザー 			*/
#define	SYS_SPK_OUT_ALARMBUZZER		0x0008	/* アラームブザー 		*/
#define	SYS_SPK_OUT_HUNGUP			0x0010	/* ハングアップブザー 	*/
#define	SYS_SPK_OUT_HOLDALARM		0x0020	/* 保留アラーム　		*/
#define	SYS_SPK_OUT_HOLDEND			0x0040	/* 保留終了				*/
#define	SYS_SPK_OUT_ENDLESSALARM 	0x0080	/* エンドレスアラーム   */
#define	SYS_SPK_OUT_FAKERINGER	 	0x0100	/* 疑似ベル				*/
#define	SYS_SPK_OUT_PAPERSUPPLY	 	0x0200	/* 手差し用紙補給ブザー For POPLAR	*/
#if defined(STOCKHM2) /* 本体鳴動のテスト : by SMuratec C.P 2004/09/24 */
#define SYS_SPK_OUT_CALLINGBUZZER	0x0400	/* 呼出ブザー			*/	

#define	SYS_CHKBUZZER_MASK_BIT	(SYS_SPK_OUT_KEYBUZZER|SYS_SPK_OUT_ENDBUZZER|SYS_SPK_OUT_ALARMBUZZER|SYS_SPK_OUT_HUNGUP|SYS_SPK_OUT_HOLDALARM|SYS_SPK_OUT_HOLDEND|SYS_SPK_OUT_ENDLESSALARM|SYS_SPK_OUT_FAKERINGER|SYS_SPK_OUT_PAPERSUPPLY|SYS_SPK_OUT_CALLINGBUZZER)
#else
#define	SYS_CHKBUZZER_MASK_BIT	(SYS_SPK_OUT_KEYBUZZER|SYS_SPK_OUT_ENDBUZZER|SYS_SPK_OUT_ALARMBUZZER|SYS_SPK_OUT_HUNGUP|SYS_SPK_OUT_HOLDALARM|SYS_SPK_OUT_HOLDEND|SYS_SPK_OUT_ENDLESSALARM|SYS_SPK_OUT_FAKERINGER|SYS_SPK_OUT_PAPERSUPPLY)
#endif

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) /* Add by Y.kano 2003/09/24 */
/************************************************************************
*          BY:	加納義彦
*        DATE:	2003/09/24
* DESCRIPTION:	キータッチボリュームのためのデータ定義
************************************************************************/
#define		KEY_BUZZER_VOLUME_OFF	0x00
#define		KEY_BUZZER_VOLUME_MIN	0x01
#define		KEY_BUZZER_VOLUME_MID	0x02
#define		KEY_BUZZER_VOLUME_MAX	0x03
#endif

/************************************************************************
 * ファン制御		1996/11/11 M.Tachibana								*
 ************************************************************************/
#define	FAN_OFF		0
#define	FAN_HALF	1
#define	FAN_FULL	2

/************************************************************************
 * フィードクラッチ制御		1996/11/11 M.Tachibana						*
 ************************************************************************/
#define	CLUTCH_CASSETTE1	1
#define	CLUTCH_CASSETTE2	2
#define	CLUTCH_CASSETTE3	3
#define	CLUTCH_MANUAL_TRAY	4

/************************************************************************
 * タイマー管理										1996/11/19 T.Nose	*
 * Timer10msQueue[TIMER_MULTI10MS_MAX]									*
 ************************************************************************/
#define	TIMER_MULTI10MS_MAX	10

/************************************************************************
 * 内蔵されているモデムの種類 By O.Kimoto 1997/06/14					*
 ************************************************************************/
#define	CMN_ORANGE_MODEM		0
#define	CMN_R288F_MODEM			1
#define	CMN_NO_MODEM			0xFF

/************************************************************************
 * メモリ送信チェック関数の引数				1997/07/22 by K.Watanabe	*
 ************************************************************************/
#define	CMN_STATUS_NO_CHK		0
#define	CMN_STATUS_CHK			1

/************************************************************************
*          BY:	桑原美紀
*        DATE:	1998/07/01
* DESCRIPTION:	LCD濃度調整の最大値
************************************************************************/
#define	CONTRAST_LCD_MAX			7
#define	CONTRAST_LCD_DEFAULT		2	/* 1998/11/16(3->4)1998/11/19(->2) H.Yoshikawa */

#if (PRO_ENERGY_SAVE_PPF == ENABLE)/*V851 省エネBy Y.Suzuki 2002/06/18*/
/************************************************************************
 * 省エネモード
 ************************************************************************/
#define ECO_MODE_OFF			0x00	/* 通常状態 */
#define ECO_MODE_ON				0x01	/* 省エネ状態 */
#define ECO_MODE_SETTING		0xFF	/* セッティング中 */
#endif

#if (defined(POPLAR_H) && defined(JP0)) /* V851 チェッカー By H.Fujimura 2002/07/15 */
/*************************************************************************
 * チェッカモード
 *************************************************************************/
#define	CHECKER_MAIN_TEST			1
#define	CHECKER_RTC_TEST			2
#define	CHECKER_PANEL_ASSY			3
#define	CHECKER_PRINTER_ASSY		4
#define	CHECKER_OP_CASSETTE_ASSY	5
#define	CHECKER_CCD_PCB				6
#define	CHECKER_SCANNER_PCB			7
#define	CHECKER_ADF_ASSY			8
#define	CHECKER_FBS_ASSY			9
#define	CHECKER_PANEL_FUNC			10
#define	CHECKER_2BIN_UNIT			11	/* Add By M.Tachibana 2000/09/26 */
#define	CHECKER_EX_MEMORY_PCB		12	/* Add By M.Maeda 2001/07/03 */
#define	CHECKER_ROTATE_PCB			13	/* Add By O.Oshima 2001/07/18 */
#define	CHECKER_FUNCTION			14
#endif

#if (PRO_ECO_MODE == ENABLE) /* 2002/09/09 By M.Maeda */
/************************************************************************
 * 省エネモード
 ************************************************************************/
#define ECO_MODE_OFF			0x00	/* 通常状態 */
#define ECO_MODE_ON				0x01	/* 省エネ状態 */
#endif

#if defined(SATSUKI2) || defined(STOCKHM2) || defined(HINOKI3) || defined(KEISATSU)	/* Add by Y.Kano 2004/12/21 */
/* Added by SMuratec K.W.Q 2003/08/26 */
/*************************************************************************
 * チェッカモード
 *************************************************************************/
#define	CHECKER_MAIN_TEST			1
#define	CHECKER_PANEL_ASSY			2
#endif

#endif
