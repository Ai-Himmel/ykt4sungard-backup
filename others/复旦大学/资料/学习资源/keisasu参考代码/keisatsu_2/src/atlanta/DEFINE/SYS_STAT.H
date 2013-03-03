/* By S.K Spe.21,1995 */
#ifndef sys_stat_h
	#define	sys_stat_h

/* #define	SYS_MACHINE_STATUS_MAX	20 */
#define	SYS_RESOURCE_STATUS				0
#define	SYS_MACHINE_STATUS				1
#define	SYS_MACHINE_STATUS_NCU			2
#define	SYS_MACHINE_STATUS_RESERVE		3
#define	SYS_STOP_SWITCH_STATUS			4
#define	SYS_STOP_SWITCH_STATUS_RESERVE	5
#define	SYS_PRINTER_STATUS1				6
#define	SYS_PRINTER_STATUS2				7
#define	SYS_PRINTER_STATUS3				8
#define	SYS_SCANNER_STATUS				9
#define	SYS_COVER_STATUS				10
#define SYS_SENSOR_STATUS				11
#define	SYS_ERROR_STATUS				12
#define	SYS_WARNING_STATUS				13	/* By S.Kawasaki 1996/06/20 */
#define	SYS_OTHER_STATUS				14	/* By S.Kawasaki 1996/04/04 */
#define	SYS_CASSETTE_OPTION_STATUS		15	/* By M.Tachibana 1997/01/09 */
#define	SYS_CIPHER_STATUS				16	/* By Y.Suzuki 1997/11/08 */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_RESOURCE_STATUS];
* DESCRIPTION:   ﾘｿｰｽ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_LINE_BUSY				0x0001	/* 回線使用中*/
#define	SYS_SCANNER_BUSY			0x0002	/* ｽｷｬﾅ使用中*/
#define	SYS_PRINTER_BUSY			0x0004	/* ﾌﾟﾘﾝﾀｰ使用中（ｲﾒｰｼﾞﾌﾟﾘﾝﾄ､ﾘｽﾄﾌﾟﾘﾝﾄ）*/
#define	SYS_PANEL_BUSY				0x0008	/* ﾊﾟﾈﾙ使用中*/
#define	SYS_PRE_LINE_BUSY			0x0010	/* CI検出中*/
#define	SYS_PREHEAT					0x0020	/* 寒冷地 PreHeat中 */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_MACHINE_STATUS];
* DESCRIPTION:   ﾏｼｰﾝ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_FAXCOM					0x0001	/* 通信中*/
#define	SYS_POCKET_BELL				0x0002	/* ﾎﾟｹｯﾄ･ﾍﾞﾙ呼び出し*/
#define	SYS_SCANNER_COPY			0x0004	/* ｽｷｬﾅｰ･ｺﾋﾟｰ中*/
#define	SYS_MULTI_COPY				0x0008	/* ﾏﾙﾁ･ｺﾋﾟｰ中*/
#define	SYS_LIST_PRINT				0x0010	/* ﾘｽﾄ･ﾌﾟﾘﾝﾄ中*/
#define	SYS_IMAGE_PRINT				0x0020	/* イメージ・プリント中 */
#define	SYS_DOC_STORE				0x0040	/* 蓄積中 */
#define	SYS_OPERATE					0x0080	/* ｵﾍﾟﾚｰｼｮﾝ中*/
#define	SYS_FIP						0x0100	/* FIP使用中*/
#define	SYS_TELEPHONE				0x0200	/* 多機能電話使用中*/
#define	SYS_FEED_IN					0x0400	/* FEED IN SCANNER BUSY	*/
#define	SYS_FEED_OUT				0x0800	/* FEED OUT SCANNER BUSY */
#define	SYS_BUFFERING_PRINT			0x1000	/* ﾊﾞｯﾌｧﾘﾝｸﾞ･ﾌﾟﾘﾝﾄ中 */
#define	SYS_PRINT_JAM_RECOVER		0x2000	/* ｼﾞｬﾑﾘｶﾊﾞｰ処理中 */
#define	SYS_PRINT_WARMUP			0x4000	/* ｳｵｰﾑｱｯﾌﾟ中 */
#define	SYS_FAXMODEM				0x8000	/** CLASS1動作中セット 1996/03/29 */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Jan.17,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_MACHINE_STATUS_NCU];
* DESCRIPTION:   回線回りのステ－タス
************************************************************************/
#define	SYS_TEL1_OFF_HOOK			0x0001	/* TEL1がオフ・フック 			  */
#define	SYS_TEL2_OFF_HOOK			0x0002	/* TEL2がオフ・フック			  */
#define	SYS_BRANCH_OFF_HOOK			0x0004	/* ブランチ・オフ・フック		  */
#define	SYS_HOOK_KEY_OFF_HOOK		0x0008	/* フック・キ－・オフ・フック 	  */
#define	SYS_TAD						0x0010	/* TAD操作中					  */
#define	SYS_DIAL_IN					0x0020	/* ダイアル・イン着信			  */
#define	SYS_INTER_COM				0x0040	/* 内線通話中					  */
#define	SYS_INTER_CALL				0x0080	/* 内線呼び出し中				  */
#define	SYS_LINE_HOLD				0x0100	/* 回線保留中					  */
#define	SYS_HOLD_TRANSFER			0x0200	/* 保留転送中					  */
#define	SYS_TRIPLE_COM				0x0400	/* 三者通話中					  */
#define	SYS_BRC_LINE_VOLT_CHK		0x0800	/* ブランチ検出用回線電圧測定中   */
#define	SYS_NO_LINE					0x1000	/* ブランチ電圧測定中回線抜け検出 */
#define SYS_ND_DISPLAY				0x2000	/* ナンバーディスプレイで相手先表示中 */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_MACHINE_STATUS_RESERVE];
* DESCRIPTION:   ﾏｼｰﾝ･ｽﾃｰﾀｽ
************************************************************************/
/** 予備 **/
/** ＰＣプリント追加の為、このエリアを使用します。By J.Miyazaki 1996/09/14 */
#define	SYS_PC_PRINTDATA_RX			0x0001	/* ＰＣからのデータ受信中 */
#define	SYS_MANUAL_COPY_DOC_OPR		0x0002	/* 手差し用紙要求 *//* ●ICHOU追加 by T.Soneoka 1996/06/28 */
#define	SYS_MANUAL_COPY				0x0004	/* 手差しコピー中 *//* ●ICHOU追加 by T.Soneoka 1996/10/3 */
#define	SYS_PRINTER_POWER_ON		0x0008	/* POWER ONウォームアップ中 *//* POPLAR By M.Tachibana */
#define	SYS_PRINTER_CLEANING		0x0010	/* 後クリーニング中 *//* POPLAR By M.Tachibana */
#define	SYS_LED_TEST				0x0020	/* ＬＥＤテスト中 *//* By M.Tachibana 1997/06/09 */
#define	SYS_FCOT_INITIAL_ABORT		0x0040	/* FCOT起動直後の停止 *//* POPLAR By M.Tachibana */
#define SYS_PC_PRINT_CONFIRM_OPR	0x0080	/* ＰＣプリント手差し用紙の確認オペレーション by T.Soneoka 1997/07/17 */
#define SYS_PC_1PAGE_RECEIVING		0x0100	/* ＰＣからの１ページ受信中 H.Yoshikawa 1997/07/18 */
#define SYS_PC_NO_SAME_DOCUMENT		0x0200	/* ＰＣプリントで自動カセット選択時に同じサイズ用紙がなくなった H.Yoshikawa 1997/08/08 */
#define	SYS_PRINT_END_WAIT			0x0400	/* 後クリーニング終了待ち *//* POPLAR By M.Tachibana 1997/10/13 */
#define	SYS_PRINTER_WAKEUP			0x0800	/* ウェイクアップ処理中 *//* POPLAR By M.Tachibana 1997/12/03 */
#define	SYS_DIALUP_INTERNET_FAX		0x1000	/* インターネットＦＡＸ動作中　by Y.Tanimoto 1998/03/12 */
#define	SYS_CL1_FNET_RING			0x2000  /** F網RING送出中(NCU_Taskなし)  PRO_CL1_TELFAX_LAN S.Fukui June 19,1998 */
#if defined (KEISATSU) /* Added by SMuratec 李 2005/06/27 */
#define	SYS_STD_LINE_IN_RECEIVE		0x4000	/* 標準回線受話中 	*/
#define	SYS_EXT_LINE_IN_RECEIVE		0x8000	/* 拡張回線受話中 	*/
#endif /* defined (KEISATSU) */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS];
* DESCRIPTION:   停止ﾎﾞﾀﾝ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_STOP_FAXCOM		0x0001	/* 通信停止要求*/
#define	SYS_STOP_TELEPHONE	0x0002	/* 多機能電話停止要求*/
					/* TAD操作中，ダイアル・イン操作中，内線呼び出し中，保留転送中，三者通話中 */
#define	SYS_STOP_SCANNER_COPY	0x0004	/* ｽｷｬﾅｰ･ｺﾋﾟｰ停止要求*/
#define	SYS_STOP_MULTI_COPY	0x0008	/* ﾏﾙﾁ･ｺﾋﾟｰ停止要求*/
#define	SYS_STOP_LIST_PRINT	0x0010	/* ﾘｽﾄ･ﾌﾟﾘﾝﾄ停止要求*/
#define	SYS_STOP_FIP		0x0020	/* FIP停止要求*/
#define	SYS_STOP_TAD		0x0040	/* TAD停止要求*/
#define	SYS_STOP_INTER_CALL	0x0080	/* 内線呼び出し停止要求*/
#define	SYS_STOP_DOC_STORE	0x0100	/* 原稿蓄積停止要求*/
#define	SYS_STOP_IMAGE_PRINT	0x0200	/* イメージプリント停止要求*/
#define	SYS_STOP_CIPHER		0x0400	/* スクランブル/デスクランブル停止要求*/
#if defined (KEISATSU) /* 強制終了 Added by SMuratec 李 2005/06/28 */
#define	SYS_STOP_COM_ON_FORCE	0x0800	/* 通信強制終了要求*/
#endif /* defined (KEISATSU) */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_STOP_SWITCH_STATUS_RESERVE];
* DESCRIPTION:   停止ﾎﾞﾀﾝ･ｽﾃｰﾀｽ
************************************************************************/
/** 予備 **/

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_PRINTER_STATUS];
* DESCRIPTION:   ﾌﾟﾘﾝﾀｰ･ｽﾃｰﾀｽ
************************************************************************/
#if (0)	/* By M.Tachibana 1996/11/08 */
** #define	SYS_PRINTER_NO_PAPER			0x0001	/* ﾛｰﾙ紙無し、ｶｾｯﾄ1記録紙無し */
** #define	SYS_PRINTER_NO_PAPER2			0x0002	/* ｶｾｯﾄ2記録紙無し*/
** #define	SYS_PRINTER_PAPER_JAM			0x0004	/* ﾍﾟｰﾊﾟｰｼﾞｬﾑ(KIRIでも使います  Jan.18,95) */
** #define	SYS_PRINTER_RESET_ERROR			0x0008	/* ﾐﾉﾙﾀ ﾌﾟﾘﾝﾀｰ初期化エラー By S.K Jan.29,1996 */
** #define	SYS_PRINTER_NO_INK				0x0010	/* ｲﾝｸﾘﾎﾞﾝ無し/ﾄﾅｰ無し */
** #define	SYS_PRINTER_SIZE_ERROR			0x0020  /* ﾐﾉﾙﾀ 記録紙ｻｲｽﾞｴﾗｰ By S.Kawsaki 1996/03/15 */
** #define	SYS_PRINTER_NO_EP_CARTRIDGE		0x0040	/* KIRI EPｶｰﾄﾘｯｼﾞなし */
** #define	SYS_PRINTER_EXIT_JAM			0x0080	/* KIRI 記録紙排出 JAM */
** #define	SYS_PRINTER_MISS_FEED_JAM		0x0100	/* KIRI 記録紙引上げ JAM */
** #define	SYS_PRINTER_REG_JAM				0x0200	/* KIRI 記録中 JAM */
** #define	SYS_PRINTER_FUSER_ABNORMAL		0x0400	/* ﾐﾉﾙﾀ By S.K Jan.29,1996 */
** #define	SYS_PRINTER_FAN_ABNORMAL		0x0800	/* KIRI FAN ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
** #define	SYS_PRINTER_MOTOR_ABNORMAL		0x1000	/* KIRI MOTOR ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
** #define	SYS_PRINTER_LASER_ABNORMAL		0x2000	/* ﾐﾉﾙﾀ LASER ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
** #define	SYS_PRINTER_SERIAL_ERROR		0x4000	/* KIRI SERIAL ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
** #define	SYS_PRINTER_FEW_TONAR			0x8000	/* ﾄﾅｰ残量が少ない */
** #define	SYS_PRINTER_FEW_EP_CARTRIDGE	0x8000	/* KIRI EPｶｰﾄﾘｯｼﾞのﾄﾅｰ量が残り少ない */
**
** #define	SYS_PRINTER_END_MARK			0x0002	不必要　*/ /* ｴﾝﾄﾞﾏｰｸ */
** #define	SYS_PRINTER_CUTTER_ERROR		0x0008			*/ /* ｶｯﾀｰｴﾗｰ */
** #define	SYS_PRINTER_HIGH_TEMP			0x0020  		*/ /*  */
** #define SYS_PRINTER_MEMORY_ABNORMAL		0x0400			*/ /* KIRI NVM ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
#endif

/***********************************************************************
*          BY:   M.Tachibana
*        DATE:   1996/11/08
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_PRINTER_STATUS1];
* DESCRIPTION:   ﾌﾟﾘﾝﾀｰ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_PRINTER_NO_MANUAL_PAPER	0x0001	/* マルチ手差しに記録紙無し *//*POPLAR*/
#define	SYS_PRINTER_NO_PAPER		0x0002	/* ﾛｰﾙ紙無し、ｶｾｯﾄ1記録紙無し */
#define	SYS_PRINTER_NO_PAPER2		0x0004	/* ｶｾｯﾄ2記録紙無し*/
#define	SYS_PRINTER_NO_PAPER3		0x0008	/* ｶｾｯﾄ3記録紙無し*//*POPLAR*/
#define	SYS_PRINTER_NO_ALL_PAPER	0x000F	/* 全ての記録紙無し *//*POPLAR*/
#define	SYS_PRINTER_NO_CARTRIDGE	0x0010	/* ｶｰﾄﾘｯｼﾞなし */
#define	SYS_PRINTER_NO_INK			0x0020	/* ｲﾝｸﾘﾎﾞﾝ無し/ﾄﾅｰ無し */
#define	SYS_PRINTER_FEW_TONER		0x0040	/* ﾄﾅｰ残量が少ない */
#define	SYS_PRINTER_END_TONER		0x0080	/* トナー交換 *//*POPLAR*/
#define	SYS_PRINTER_NO_DRUM			0x0100	/* ドラムユニット無し *//*POPLAR*/
#define	SYS_PRINTER_NEAREND_DRUM	0x0200	/* ドラム寿命近し・プリント可 *//*POPLAR*/
#define	SYS_PRINTER_END_DRUM		0x0400	/* ドラム交換 *//*POPLAR*/
#define	SYS_PRINTER_ERROR_ALARM1	0x07FE	/* 状態が０から１になるとアラーム鳴動するビット */
											/* 0x07F0 -> 0x07FE by K.Watanabe 1997/12/24 */

/***********************************************************************
*          BY:   M.Tachibana
*        DATE:   1996/11/08
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_PRINTER_STATUS2];
* DESCRIPTION:   ﾌﾟﾘﾝﾀｰ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_PRINTER_PAPER_JAM		0x0001	/* ﾍﾟｰﾊﾟｰｼﾞｬﾑ */
#define	SYS_PRINTER_1ST_FEED_JAM	0x0002	/* カセット１からの給紙ＪＡＭ *//*POPLAR*/
#define	SYS_PRINTER_2ND_FEED_JAM	0x0004	/* カセット２からの給紙ＪＡＭ *//*POPLAR*/
#define	SYS_PRINTER_3RD_FEED_JAM	0x0008	/* カセット３からの給紙ＪＡＭ *//*POPLAR*/
#define	SYS_PRINTER_MANUAL_FEED_JAM	0x0010	/* 手差しカセットからの給紙ＪＡＭ *//*POPLAR*/
#define	SYS_PRINTER_MISS_FEED_JAM	0x0020	/* 記録紙引上げ JAM */
#define	SYS_PRINTER_REG_JAM			0x0040	/* 記録中 JAM */
#define	SYS_PRINTER_EXIT_JAM		0x0080	/* 記録紙排出 JAM */
#define	SYS_PRINTER_ERROR_JAM		0x00FF	/* 何らかのＪＡＭが起こった */
#define	SYS_PRINTER_SIZE_ERROR		0x0100	/* 記録紙ｻｲｽﾞｴﾗｰ */
#define	SYS_PRINTER_CUTTER_ERROR	0x0200	/* ｶｯﾀｰｴﾗｰ *//* SAKAKI */
#define	SYS_PRINTER_HIGH_TEMP		0x0400	/* サーマルヘッド異常温度 *//* SAKAKI */
#define	SYS_PRINTER_3M_OVER			0x0800	/* ３Ｍ受信原稿長オーバー by H.Hirao 1998/12/15 */
#define	SYS_PRINTER_ERROR_ALARM2	0x03FF	/* 状態が０から１になるとアラーム鳴動するビット */
/***********************************************************************
*          BY:   M.Tachibana
*        DATE:   1996/11/08
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_PRINTER_STATUS3];
* DESCRIPTION:   ﾌﾟﾘﾝﾀｰ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_PRINTER_FUSER_ABNORMAL	0x0001	/* 定着器エラー */
#define	SYS_PRINTER_FAN_ABNORMAL	0x0002	/* FAN ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
#define	SYS_PRINTER_MOTOR_ABNORMAL	0x0004	/* MOTOR ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
#define	SYS_PRINTER_LASER_ABNORMAL	0x0008	/* LASER ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
#define	SYS_PRINTER_SERIAL_ERROR	0x0010	/* SERIAL ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) */
#define	SYS_PRINTER_RESET_ERROR		0x0020	/* ﾌﾟﾘﾝﾀｰ初期化エラー */
#define	SYS_PRINTER_DRUM_ABNORMAL	0x0040	/* DRUM ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) For POPLAR */
#define	SYS_PRINTER_PS_FAN_ABNORMAL	0x0080	/* 電源冷却FAN ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) For POPLAR */
#define	SYS_PRINTER_HV_FUSE_ERROR	0x0100	/* 高圧フューズ切断 ｴﾗｰ (ｻｰﾋﾞｽ･ｺｰﾙ) For POPLAR */
#define	SYS_PRINTER_ERROR_ALARM3	0x01FF	/* 状態が０から１になるとアラーム鳴動するビット */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_SCANNER_STATUS];
* DESCRIPTION:   ｽｷｬﾅｰ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_SCANNER_FEED_ERROR			0x0001	/* 繰り込み不良 Clear Sensor & Main */
#define	SYS_SCANNER_LAMP_ERROR			0x0002	/* 光量不足 Clear Sensor & Main */
#define	SYS_SCANNER_MEMORY_OVER			0x0004	/* メモリ・オーバー Clear Initial & Opr. */
#define	SYS_SCANNER_PAGE_ERROR			0x0008	/* 指定ページ枚数と原稿枚数不一致 Clear Opr */
#define	SYS_SCANNER_MIRROR_ERROR		0x0010	/* ミラーキャリッジエラー */
#define	SYS_SCANNER_FBS_RECOVER_OPR		0x0020	/* FBS使用中のプリンタカバー開閉時の継続スキャン指示オペレーション */
#define	SYS_SCANNER_GEAR_BACKLASH		0x0080	/* ADFギアバックラッシュ中 */ /* 1997/05/10 s.takeuchi */
#define	SYS_SCANNER_MEMORY_OVER_OPR 	0x0100	/* メモリ・オーバー オペレーション */
#define	SYS_SCANNER_JAM_RECOVER_OPR		0x0200	/* JAM解除後の継続スキャン指示オペレーション */
#define	SYS_SCANNER_NEXT_SCAN_OPR		0x0400	/* ADF/ブックスキャン時の次原稿スキャン指示オペレーション */
#define	SYS_SCANNER_NEXT_SCAN_START_OPR	0x0800	/* ADF/ブックスキャン時の次原稿開始オペレーション */
#define	SYS_SCANNER_NEXT_SCAN_START		0x1000	/* ADF/ブックスキャンの次原稿読取開始指示 */
#define	SYS_SCANNER_MIRROR_INIT			0x2000	/* 電源ON時のミラーキャリッジ初期化中 (FBS用) */
#define	SYS_SCANNER_MIRROR_BUSY			0x4000	/* ミラーキャリッジ移動中 (使用中) */
#define	SYS_SCANNER_PREPARATION_ADF		0x8000	/* ADF読み取り前の移動中(お待ち下さい表示用) */
#define	SYS_SCANNER_ERROR_ALARM			0x011F	/* 状態が０から１になるとアラーム鳴動するビット */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_COVER_STATUS];
* DESCRIPTION:   ｶﾊﾞｰ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_COVER_SCANNER_OPEN		0x0001	/* スキャナカバーオープン*/
#define	SYS_COVER_PRINTER_OPEN		0x0002	/* プリンターカバーオープン*/
#define	SYS_COVER_JAM_OPEN			0x0004	/* ジャム除去カバーオープン*/
#define	SYS_COVER_CASSETTE1_OPEN	0x0008	/* カセット１オープン*/
#define	SYS_COVER_CASSETTE2_OPEN	0x0010	/* カセット２オープン*/
#define	SYS_COVER_CASSETTE3_OPEN	0x0020	/* カセット３オープン */
#define	SYS_COVER_2JAM_OPEN			0x0040	/* ２ｎｄジャム処理カバーオープン */
#define	SYS_COVER_3JAM_OPEN			0x0080	/* ３ｎｄジャム処理カバーオープン */
#define	SYS_COVER_BOOK_OPEN			0x0400	/* ブック原稿押さえカバーオープン */
#define	SYS_COVER_ERROR_ALARM_STOP	0x00FE	/* 状態が０から１になる時に他のエラーが発生してもアラームを鳴動させないビット */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Nov.18,1993
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_SENSOR_STATUS];
* DESCRIPTION:   ｾﾝｻｰ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_SENSOR_DS1_ON			0x0001	/* DS1 ON */
#define	SYS_SENSOR_DS2_ON			0x0002	/* DS2 ON */
#define	SYS_SENSOR_DS3_ON			0x0004	/* DS3 ON */
#define	SYS_SENSOR_PS1_ON			0x0008	/* PS1 ON */
#define	SYS_SENSOR_PS2_ON			0x0010	/* PS2 ON */
#define	SYS_SENSOR_PB4_ON			0x0020	/* PB4 ON */
#define	SYS_SENSOR_DIAL_IN_ON		0x0040	/* DIAL IN ON */
#define	SYS_SENSOR_PSS_ON			0x0080	/* PSS ON (POPLAR) */
#define	SYS_SENSOR_PDS_ON			0x0100	/* PDS ON (POPLAR) */
#define	SYS_SENSOR_HPES_ON			0x0200	/* HPES ON (POPLAR) */
#if defined (KEISATSU) /* 警察FAX 05/09/07 石橋正和 */
#define SYS_SCRAMBLE_ON				0x0400	/* スクランブルSW ON */
#endif

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Feb.3,1994
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_ERROR_STATUS];
* DESCRIPTION:   エラー・ステータス
************************************************************************/
#define	SYS_ERROR_HUNG_UP			0x0001	/* ハング・アップ・エラー */
#define	SYS_ERROR_NO_DIAL_IN_NUMBER	0x0002	/* ダイアルイン・モードでダイアル・インＮｏがセットされていない。 */
#define	SYS_ERROR_FAXCOM			0x0004	/* 通信エラー */
#define	SYS_BATTERY_EMPTY			0x0008	/* バッテリエラー（電池切れ）*/
#define	SYS_ERROR_CLASS1_INIT		0x0010	/* Class1 AutoInitialize error by Y.T 1996/09/14 */
#define	SYS_ERROR_PC_MEMORY_OVER	0x0020	/* PCﾌﾟﾘﾝﾄﾒﾓﾘｰｵｰﾊﾞｰ 1998/02/12 By M.Kuwahara */
#define SYS_MOMENT_TOP_COVER_OPEN	0x0040	/* RXIL瞬断 T.Nose 1998/03/04 */
#define	SYS_ERROR_INF_INIT			0x0080	/* InternetFAX Initialize error by Y.T 1996/04/28 */
#define	SYS_DIALIN_SW_OFF_REQUEST	0x0100	/* ダイヤルインＳＷをＯＦＦにしてください */	/* 1998/06/16 Add By M.Kuwahara */
#define	SYS_DIALIN_SW_ON_REQUEST	0x0200	/* ダイヤルインＳＷをＯＮにしてください */	/* 1998/06/16 Add By M.Kuwahara */
#if defined (KEISATSU) /* 警察FAX 05/11/29 石橋正和 */
#define SYS_ERROR_S1				0x0400	/* S1エラー */
#endif

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Jun.20,1996
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_WARNING_STATUS];
* DESCRIPTION:   ﾜｰﾆﾝｸﾞ･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_WARNING_DRUM_REPLACE	0x0001	/* プリンターのドラム交換ﾜｰﾆﾝｸﾞ/継続印字可能 By S.Kawasaki 1996/06/20 */

/***********************************************************************
*          BY:   S.Kawasaki
*        DATE:   Apr.4,1996
*        TYPE:   DEFINE
* VAR TO HOLD:   unsigned int	SYS_MachineStatus[SYS_OTHER_STATUS];
* DESCRIPTION:   その他･ｽﾃｰﾀｽ
************************************************************************/
#define	SYS_INTERNAL_MODEM			0x0001	/* 本体内にモデムが実装されている場合。 28.8K対応用に追加 */
#define	SYS_EXTERNAL_MODEM			0x0002	/* ｵﾌﾟｼｮﾝﾎﾞｰﾄ0を第一ﾓﾃﾞﾑとして使用可能 					  */
#define	SYS_MODEM_144K				0x0004	/* 第一モデムとして認識出来るモデムスピード SET:14.4K/CLEAR:28.8K */
#define	SYS_MODEM_ERROR				0x0008	/** モデムエラー（全てのモデム使用不可能） */
#if defined (KEISATSU) /* ハンドセット電話状態 Added by SMuratec 李 2005/06/27 */
#define	SYS_HDST_STD_OFFHOOK		0x0010	/* 標準回線のハンドセットがオフ・フック	  */
#define	SYS_HDST_EXT_OFFHOOK		0x0020	/* 拡張回線のハンドセットがオフ・フック	  */
#define	SYS_CONT24_LINE_BUSY		0x0040	/* 擬似鳴動中							  */
#define	SYS_SHIREI_SIGNEL_ON		0x0080	/* 指令回線モード						  */
#define	SYS_SHIREI_IDLE				0x0100	/* 指令回線のDCS待ち段階				  */
#define	SYS_SHIREI_FAXCOM			0x0200	/* 指令回線送受信段階					  */
#endif /* defined (KEISATSU) */

/***********************************************************************
*          BY:   M.Tachibana
*        DATE:   1997/01/09
*        TYPE:   DEFINE
* VAR TO HOLD:   UWORD	SYS_MachineStatus[SYS_CASSETTE_OPTION_STATUS];
* DESCRIPTION:
************************************************************************/
#define	SYS_1ST_UNIT				0x0001	/* １ｓｔカセットが装着済 */
#define	SYS_2ND_UNIT				0x0002	/* ２ｎｄカセットが装着済 */
#define	SYS_3RD_UNIT				0x0004	/* ３ｒｄカセットが装着済 */

/***********************************************************************
*          BY:   Y.Suzuki
*        DATE:   1997/11/08
*        TYPE:   DEFINE
* VAR TO HOLD:   UWORD	SYS_MachineStatus[SYS_CIPHER_STATUS];
* DESCRIPTION:
************************************************************************/
#define	SYS_SCRAMBLE_EXEC			0x0001	/* スクランブル中								*/
#define	SYS_DESCRAMBLE_EXEC			0x0002	/* デスクランブル中								*/
#define	SYS_SCRAMBLE_MEM_OVER		0x0004	/* スクランブル中メモリオーバー					*/
#define	SYS_DESCRAMBLE_MEM_OVER		0x0008	/* デスクランブル中メモリオーバー				*/
#define	SYS_SCRAMBLE_ERROR			0x0010	/* スクランブル時エラー							*/
#define	SYS_DESCRAMBLE_ERROR		0x0020	/* デスクランブル時エラー						*/
#define	SYS_WRONG_KEY_ERROR			0x0040	/* デスクランブル時キーワード間違い				*/
#define	SYS_DESCRAMBLE_PRINT		0x0080	/* デスクランブルプリント中						*/
#define	SYS_SCRAMBLE_LENGTH_ERROR	0x0100	/* スクランブル原稿長エラー By Y.Suzuki 1998/06/11 */
#define	SYS_DESCRAMBLE_FIRST_PAGE	0x0200	/* ｽｸﾗﾝﾌﾞﾙ解除1ﾍﾟｰｼﾞ目完了 By Y.Suzuki 1998/7/6 */
#define	SYS_ERASE_SCRAMBLE_DOC		0x0400	/* ｽｸﾗﾝﾌﾞﾙ解除時、処理済のｽｸﾗﾝﾌﾞﾙ原稿を消去する */
#define	SYS_DISPLAY_DESCRAMBLE		0x0800	/* ｽｸﾗﾝﾌﾞﾙ解除時、プリント起動後もＬＣＤにデスクランブル表示 */
#define	SYS_CIPHER_ERROR_ALARM		0x017C	/* 状態が０から１になるとアラーム鳴動するビット	*/

#endif
