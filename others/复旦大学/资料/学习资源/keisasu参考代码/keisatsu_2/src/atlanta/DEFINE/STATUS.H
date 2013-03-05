/*	By Y.Suzuki 1996/10/21	*/
/* Original File : jun\usr2:\src\ichou\define\status.h */
#ifndef status_h
    #define status_h

/************************************************************************
 * 回線種別																*
 * unsigned char SYB_SettingStatus[0]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_0		0	/* SYB_SettingStatus[SETTING_STATUS_0] */

#define LINE_TYPE0_MASK			0x03
#define	DIAL_SPEED_10PPS		0x00	/* 10PPS */
#define	DIAL_SPEED_20PPS		0x01	/* 20PPS */
#define	LINE_TYPE_TONE			0x02	/* Tone Line */

#define LINE_TYPE1_MASK			0x0C
#define	DIAL_SPEED_10PPS_1		0x00	/* 外付け第１10PPS 		*/
#define	DIAL_SPEED_20PPS_1		0x04	/* 外付け第１20PPS 		*/
#define	LINE_TYPE_TONE_1		0x08	/* 外付け第１Tone Line 	*/

#define LINE_TYPE2_MASK			0x30
#define	DIAL_SPEED_10PPS_2		0x00	/* 外付け第２10PPS 		*/
#define	DIAL_SPEED_20PPS_2		0x10	/* 外付け第２20PPS 		*/
#define	LINE_TYPE_TONE_2		0x20	/* 外付け第２Tone Line 	*/

/************************************************************************
 * 読取り設定データ														*
 * unsigned char SYB_SettingStatus[1]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_1		1	/* SYB_SettingStatus[SETTING_STATUS_1] */

#define	SCANNING_WIDTH_A4		0x00	/* 読み取りサイズA4 */
#define	SCANNING_WIDTH_B4		0x01	/* 読み取りサイズB4 */
#define	SCANNING_WIDTH_A3		0x02	/* 読み取りサイズA3 */
#define	PRIMARY_MODE_NORMAL		0x00	/* 優先モードNORMAL */
#define	PRIMARY_MODE_FINE		0x04	/* 優先モードFINE */
#define	PRIMARY_MODE_SFINE		0x08	/* 優先モードSFINE */
#define	PRIMARY_MODE_GRAY		0x0C	/* 優先モードHALF */
#if (0)	/* ●ICHOU変更 ５段階になりSETTING_STATUS_26に移動しました by T.Soneoka 1996/06/19 */
**#define	PRIMARY_CONTRAST_NORMAL	0x00	/* 優先濃度普通 */
**#define	PRIMARY_CONTRAST_DARK	0x10	/* 優先濃度濃く */
**#define	PRIMARY_CONTRAST_LIGHT	0x20	/* 優先濃度淡く */
#endif
#define	HALFTONE_MODE_2			0x40	/* 写真　モード1/2 */
#define	HALFTONE_MODE_64		0x80	/* 写真　階調16/64 */

/************************************************************************
 * 機器設定データ														*
 * unsigned char SYB_SettingStatus[2]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_2		2	/* SYB_SettingStatus[SETTING_STATUS_2] */

#define	MULTI_PASS_INK_RIBBON	0x01	/* マルチパスインクリボンON */
#define HEAT_TRANSFER_ON		0x02	/* 熱転写/感熱記録 */
#define STNG_NON_SORT_COPY      0x04    /* ノンソートコピー */
/* ↓●ICHOU追加予定 by T.Soneoka 1996/05/09 */
#define	JOURNAL_AUTO_PRINT_ON	0x08	/* ジャーナル自動プリントON */
/* JUNK MAIL 新仕様 1997/05/12  By T.Yamaguchi	*/
#define BLOCK_JUNK_FAX_OFF		0x00	/*	ジャンクメール防止機能 ＯＦＦ		*/
#define BLOCK_JUNK_FAX_MODE1	0x10	/*	ＭＯＤＥ１（従来仕様）				*/
#define BLOCK_JUNK_FAX_MODE2	0x20	/*	ＭＯＤＥ２ (新仕様）				*/
#define BLOCK_JUNK_FAX_MODE3	0x30	/*	ＭＯＤＥ３（ＭＯＤＥ１＋ＭＯＤＥ２）*/

#define	VOICE_MESSAGE_ON		0x40	/* 電話優先時の音声応答ＯＮ(ＮＴＴ) 1998/01/27  By T.Yamaguchi */

/************************************************************************
 * 電話機接続機能														*
 * unsigned char SYB_SettingStatus[3]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_3		3	/* SYB_SettingStatus[SETTING_STATUS_3] */

#define	CONNECTING_2ND_TEL		0x01	/* 子電話接続ON */
#define	ANS_MACHINE_PHONE1		0x02	/* 留守番電話Phone1接続 */
#define	HOLD_MELODY_ON			0x04	/* 保留メロディーON */
#define	BRANCH_ON				0x08	/* ブランチ検出ON '95.07/20 K.Watanabe */

#define	DIAL_IN_ON				0x10	/* ダイヤルインON */
#if (0)	/* TEL待機を追加のためこのﾋﾞｯﾄを削除します（待機ﾓｰﾄﾞに吸収されているので問題はなし）by K.Watanabe 1997/03/22 */
#define	PRIMARY_FAX				0x20	/* TEL/FAX待機時 FAX優先(無鳴動着信) */
#endif

#if (0)
#define	AUTO_RX_MODE_FAX		0x00	/* 自動受信モードFAX */
#define	AUTO_RX_MODE_TELFAX		0x40	/* 自動受信モードTEL/FAX */
#define	AUTO_RX_MODE_ANSFAX		0x80	/* 自動受信モードANS/FAX */
#endif

#define	MANUAL_RX_MODE			0x00	/* 手動受信モードTEL				*/
#define	AUTO_RX_MODE_FAX		0x20	/* 自動受信モードFAX				*/
#define	AUTO_RX_MODE_FAXTEL		0x40	/* 自動受信モードTEL/FAX (FAX優先）	*/
#define	AUTO_RX_MODE_TELFAX		0x60	/* 自動受信モードTEL/FAX (TEL優先）	*/
#define	AUTO_RX_MODE_ANSFAX		0x80	/* 自動受信モードANS/FAX			*/

#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* オペレーション時のみ使用 by Y.Kano 2003/09/09 */
#define	DIALIN_MODE				0xa0	/* ダイヤルインモード				*/
#endif

/************************************************************************
 * 機器設定データ														*
 * unsigned char SYB_SettingStatus[4]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_4		4	/* SYB_SettingStatus[SETTING_STATUS_4] */

#define	CLOSED_NETWORK_ON		0x01	/* 閉域通信ON */
#define	SECURITY_TRANSMISSION	0x02	/* パスワード送信 */
#define	BLOCK_JUNK_FAX_ON		0x04	/* ダイレクトメール防止ON */
#define	MESSAGE_TRANSMIT_ON		0x08	/* メッセージ送信ON */
#define	PRINTER_NO_FORM_FEED	0x10	/* ページ合成ON */
#define	RX_REDUCTION_1			0x00	/* 固定受信縮小率1 */
#define	RX_REDUCTION_2			0x20	/* 固定受信縮小率2 */
#define	RX_REDUCTION_3			0x40	/* 固定受信縮小率3 */
#define	RX_REDUCTION_4			0x60	/* 固定受信縮小率4 */
#define	RX_REDUCTION_5			0x80	/* 固定受信縮小率5 */
#define	RX_REDUCTION_6			0xA0	/* 固定受信縮小率6 */
#define	RX_REDUCTION_7			0xC0	/* 固定受信縮小率7 */

/************************************************************************
 * RS232Cパラメータ														*
 * unsigned char SYB_SettingStatus[5]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_5		5	/* SYB_SettingStatus[SETTING_STATUS_5] */

#define	RS232C_SPEED_300		0x00	/* RS232C速度300 */
#define	RS232C_SPEED_VARIABLE	0x00	/* RS232C速度AUTO */
#define	RS232C_SPEED_600		0x01	/* RS232C速度600 */
#define	RS232C_SPEED_1200		0x02	/* RS232C速度1200 */
#define	RS232C_SPEED_2400		0x03	/* RS232C速度2400 */
#define	RS232C_SPEED_4800		0x04	/* RS232C速度4800 */
#define	RS232C_SPEED_9600		0x05	/* RS232C速度9600 */
#define	RS232C_SPEED_19200		0x06	/* RS232C速度19200 */
#define	RS232C_SPEED_38400		0x07	/* RS232C速度38400 *//* Add By O.Kimoto 1997/12/07 */
#define	RS232C_DATA_LENGTH_8	0x08	/* RS232Cデータ長８or７ */
#define	RS232C_PARITY_NONE		0x00	/* RS232CパリティNONE */
#define	RS232C_PARITY_ODD		0x10	/* RS232CパリティODD */
#define	RS232C_PARITY_EVEN		0x20	/* RS232CパリティEVEN */
#define	RS232C_STOP_LENGTH_2	0x40	/* RS232Cストップビット2or1 */

/************************************************************************
 * 機器設定データ														*
 * unsigned char SYB_SettingStatus[6]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_6		6	/* SYB_SettingStatus[SETTING_STATUS_6] */

#define	DOCUMENT_STAMP_ON		0x01	/* 済スタンプON */
#define	MEMORY_TRANSMISSION_ON	0x02	/* メモリ送信ON */
#define	SECTION_CHECK_ON		0x04	/* 部門管理ON */
#define	CONFIRM_ON				0x08	/* 通信証ON */
#define	CONFIRM_TYPE_RCR		0x10	/* 受領証ON */
#define	ECM_SETTING				0x20	/* ECM ON */
#define	COPY_PROTECT_ON			0x40	/* コピー禁止ON */
#define	REMOTE_DIAG_ON			0x80	/* リモート診断ON */

/************************************************************************
 * 受信縮小のしきい値													*
 * unsigned char SYB_SettingStatus[7]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	RX_MARGIN					7	/* SYB_SettingStatus[MARGIN] */

/************************************************************************
 * リダイヤル回数														*
 * unsigned char SYB_SettingStatus[8]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	NUMBER_OF_REDIAL		8	/* SYB_SettingStatus[NUMBER_OF_REDIAL] */

/************************************************************************
 * リダイヤル間隔														*
 * unsigned char SYB_SettingStatus[9]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	REDIAL_INTERVAL			9	/* SYB_SettingStatus[REDIAL_INTERVAL] */

/************************************************************************
 * ポーズ時間															*
 * unsigned char SYB_SettingStatus[10]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	DIALING_PAUSE			10	/* SYB_SettingStatus[DIALING_PAUSE] */

/************************************************************************
 * ベル回数																*
 * unsigned char SYB_SettingStatus[11]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	NUMBER_OF_RINGS			11	/* SYB_SettingStatus[NUMBER_OF_RINGS] */

/************************************************************************
 * 親展受信原稿保持期間													*
 * unsigned char SYB_SettingStatus[12]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	SECURE_MAIL_HOLD_TIME	12	/* SYB_SettingStatus[SECURE_MAIL_HOLD_TIME] */

/************************************************************************
 * リングマスタの設定													*
 * unsigned char SYB_SettingStatus[13]									*
 * 1995/03/23															*
 * 宮崎仁一																*
 ************************************************************************/
#define SETTING_STATUS_13		13

#define RING_MASTER_PATTERN_1	0x00	/* リングマスタのベルパターン1 */
#define RING_MASTER_PATTERN_2	0x01	/* リングマスタのベルパターン2 */
#define RING_MASTER_PATTERN_3	0x02	/* リングマスタのベルパターン3 */
#define RING_MASTER_PATTERN_4	0x03	/* リングマスタのベルパターン4 */
#define RING_MASTER_PATTERN_5	0x04	/* リングマスタのベルパターン5 */
#define RING_MASTER_PATTERN_6	0x05	/* リングマスタのベルパターン6 */
#define RING_MASTER_PATTERN_7	0x06	/* リングマスタのベルパターン5 */	/* MBS要求により追加 '95.03/23 By J.Miyazaki */
#define RING_MASTER_PATTERN_8	0x07	/* リングマスタのベルパターン6 */	/* MBS要求により追加 '95.03/23 By J.Miyazaki */
#define RING_MASTER_PATTERN_9	0x08	/* リングマスタのベルパターン9 */	/* AUS FaxStream DRD7 */

/************************************************************************
 * 任意受信縮小率(%刻み)												*
 * unsigned char SYB_SettingStatus[14]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	FREE_REDUCTION			14	/* SYB_SettingStatus[REDUCTION] */

#define AUTO_FREE_REDUCTION		0xFF

/************************************************************************
 * リモートFAX															*
 * unsigned char SYB_SettingStatus[15]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_15		15	/* SYB_SettingStatus[SETTING_STATUS_15] */

#define	REMOTE_FAX_ON			0x01	/* リモートFaxON */
#define	REMOTE_FAX_DEL			0x02	/* リモートFax取出し時の原稿消去 */
#define	REMOTE_FAX_PRN			0x04	/* リモートFax設定時の受信原稿プリント */
#define	TAD_POCKET_BELL_ON		0x08	/* ポケベル呼び出しON */
#define	TAD_OGM_USER_MESSAGE	0x10	/* 内蔵TADでユーザメッセージ有効 */
#define RELAYED_RELAY_TX_ON		0x20	/* 中中継ON */
#define CATCH_PHONE_ON			0x40	/* キャッチホンON */
#define RING_MASTER_ON			0x80	/* リングマスタON */

/************************************************************************
 * リモートFAX															*
 * unsigned char SYB_SettingStatus[16]									*
 * 1994/03/03															*
 * 吉川弘康																*
 ************************************************************************/
#define SETTING_STATUS_16		16	/* SYB_SettingStatus[SETTING_STATUS_16] */

#define COPY_FIXED_REDUCTION_1	0x00	/* コピー用固定縮小率1 */
#define COPY_FIXED_REDUCTION_2	0x08	/* コピー用固定縮小率2 */
#define COPY_FIXED_REDUCTION_3	0x10	/* コピー用固定縮小率3 */
#define COPY_FIXED_REDUCTION_4	0x18	/* コピー用固定縮小率4 */
#define COPY_FIXED_REDUCTION_5	0x20	/* コピー用固定縮小率5 */
#define COPY_FIXED_REDUCTION_6	0x28	/* コピー用固定縮小率6 */
#define COPY_FIXED_REDUCTION_7	0x30	/* コピー用固定縮小率7 */
#define PRINTER_RECEIVE_ON		0x40	/* PRINTER受信ON */
/*
ﾒﾓﾘｰｽｲｯﾁE5に移動　1994/06/20    M.Eguchi
#define ALL_MODE_TO_ANS_MODE	0x40	 遠隔操作での留守モードへの切替え
*/
#define STG_SILENT_OPERATION	0x80	/* サイレントオペレーション */

/************************************************************************
 * コピー縮小のしきい値													*
 * unsigned char SYB_SettingStatus[17]									*
 * 1994/03/03															*
 * 吉川弘康																*
 ************************************************************************/
#define	COPY_MARGIN					17	/* SYB_SettingStatus[COPY_MARGIN] */

/************************************************************************
 * トールセーバ用ベル回数												*
 * unsigned char SYB_SettingStatus[18]									*
 * 1994/03/03															*
 * 吉川弘康																*
 ************************************************************************/
#define TOLL_SAVER_BELL_COUNT		18	/* SYB_SettingStatus[TOLL_SAVER_BELL_COUNT] */

/************************************************************************
 * 上段手動記録紙選択													*
 * unsigned char SYB_SettingStatus[19]									*
 * 1994/03/04															*
 * 吉川弘康																*
 ************************************************************************/
#define UPPER_SIZE					19	/* SYB_SettingStatus[UPPER_SIZE] */

#define UPPER_SIZE_NONE			0x00	/* 上段ｶｾｯﾄ無 */
#define UPPER_SIZE_A4			0x01	/* 上段手動記録紙選択A4 */
#define UPPER_SIZE_B4			0x02	/* 上段手動記録紙選択B4 */
#define UPPER_SIZE_LETTER		0x03	/* 上段手動記録紙選択レター */
#define UPPER_SIZE_LEGAL		0x04	/* 上段手動記録紙選択リーガル */
#define UPPER_SIZE_F4			0x05	/* 上段手動記録紙選択F4 */

/* この２ｂｉｔは杏では使用しない */
#define GBR_RX_ALARM			0x40	/* Rx Alarm ON '95.07/18 K.Watanabe */
#define GBR_SECURITY_RX			0x80	/* Security Receive ON 95.01.26 M.HARADA */

/************************************************************************
 * 上段手動記録紙選択													*
 * unsigned char SYB_SettingStatus[20]									*
 * 1994/03/04															*
 * 吉川弘康																*
 ************************************************************************/
#define LOWER_SIZE					20	/* SYB_SettingStatus[LOWER_SIZE] */

#define LOWER_SIZE_NONE			0x00	/* 下段ｶｾｯﾄ無 */
#define LOWER_SIZE_A4			0x01	/* 下段手動記録紙選択A4 */
#define LOWER_SIZE_B4			0x02	/* 下段手動記録紙選択B4 */
#define LOWER_SIZE_LETTER		0x03	/* 下段手動記録紙選択レター */
#define LOWER_SIZE_LEGAL		0x04	/* 下段手動記録紙選択リーガル */
#define LOWER_SIZE_F4			0x05	/* 下段手動記録紙選択F4 */

/************************************************************************
 * 受信プリント枚数(桐特ＲＯＭ対応のため)								*
 * unsigned char SYB_SettingStatus[21]									*
 * オペレーションで1～255の値をセットする								*
 * 1995/06/21															*
 * 石橋正和																*
 ************************************************************************/
#define NUMBER_OF_PRINTING_RX_DOCUMENTS	21	/* SYB_SettingStatus[NUMBER_OF_PRINTING_RX_DOCUMENTS] */

#if (0)	/* SYB_SettingStatusが足りなくなったので、使用されていない部分を変更します 97'08/30 by K.Watanabe */
///************************************************************************
// * 椛　Ａ３／Ｂ４機識別用バックアップ変数格納用							*
// * 1995/09/25															*
// * ０：Ａ３仕様機　１：Ｂ４仕様機										*
// * 木元修																*
// ************************************************************************/
//#define MOMIJI_MODEL_SELECT		22
#endif

/************************************************************************
 * 回転受信用しきい値													*
 * unsigned char SYB_SettingStatus[22]									*
 * 1997/08/30															*
 * 渡辺一章																*
 ************************************************************************/
#define	ROTATE_RX_MARGIN		22	/* SYB_SettingStatus[ROTATE_RX_MARGIN] */

/************************************************************************
 * 機器設定データ														*
 * unsigned char	SYS_SettingData[23]									*
 * 杏で新規追加になる項目に対してはこれ以降に全て登録します				*
 * 1995/11/27 Eguchi													*
 * 江口																	*
 * アクセス関数作成済み 1995/12/01 Eguchi								*
 ************************************************************************/
#define	SETTING_STATUS_23		23			/* By S.K Dec.11,1995 */

#define	DAYLIGHT_SAVING_AUTO		0x01	/* 夏時間自動切り替え　*/
#define	SECURITY_RX_ON				0x02	/* セキュリティ受信 */
#define	OPERATION_PROTECT_ON		0x04	/* オペレーションプロテクト */
#define	SECTION_CHECK_PROTECT_ON	0x08	/* 部門管理プロテクト */
#define	PIN_ACCESS_OFF				0x00	/* ＰＩＮアクセスしない */
#define	PIN_ACCESS_MODE1			0x10	/* 個別ＰＩＮアクセス（相手先別のＰＩＮ番号で発呼） */
#define	PIN_ACCESS_MODE2			0x20	/* 部門ＰＩＮアクセス（発呼者別のＰＩＮ番号で発呼)  */
#define	AUDIBLE_ALARM				0x40	/* 受信完了アラーム（ＧＢＲのみ）1996/08/14 */
#define	REMOTE_RX_ON				0x80	/* リモート受信（ＮＴＴ）1998/01/24  By T.Yamaguchi */

/************************************************************************
 * プリンタ動作時間(MATSUのみ)											*
 * unsigned char SYB_SettingStatus[]									*
 * 1994/01/06															*
 * 吉川弘康																*
 ************************************************************************/
/*#define	PRINTER_TIME			13*/
#define	PRINTER_TIME			24		/* 13から移動　変更 1996/02/29 Eguchi */

#if defined(GBR) || defined(STOCKHM2) || (PRO_PREFIX_KEY == ENABLE)	/* Added by SMuratec C.P 2004/07/08 for prefix *//* by K.Watanabe 2004/10/12 */
/************************************************************************
 * マーキュリｰポーズ時間												*
 * unsigned char SYB_SettingStatus[25]									*
 * 1994/01/06															*
 * 吉川弘康																*
 * 1996/06/24 H.Yagi													*
 ************************************************************************/
#define	MERCURY_PAUSE			25	/* SYB_SettingStatus[MERCURY_PAUSE] */
#endif

/************************************************************************
 * 機器設定データ														*
 * unsigned char SYB_SettingStatus[26]									*
 * 1996/04/11															*
 * 曽根岡拓																*
 ************************************************************************/
#define SETTING_STATUS_26		26	/* SYB_SettingStatus[SETTING_STATUS_26] */
#define	PCFAX_ON						0x01	/* ＰＣＦＡＸ接続ＯＮ */
#define READY_MODE_FAX					0x00	/* ＦＡＸ待機 */
#define READY_MODE_COPY					0x02	/* コピー待機 */
 #if (PRO_ONHOOK_RX_SWITCH == ENABLE)
#define	ONHOOK_RX_ON					0x04	/* オンフック受信ＯＮ(ＮＴＴ) 98/03/13 Add By T.Fukumoto */
 #endif
#define	PRIMARY_CONTRAST_LIGHT			0x00	/* 薄く */
#define	PRIMARY_CONTRAST_LIGHT_NORMAL	0x10	/* 薄く－普通の間 */
#define	PRIMARY_CONTRAST_NORMAL			0x20	/* 普通 */
#define	PRIMARY_CONTRAST_DARK_NORMAL	0x30	/* 濃く－普通の間 */
#define	PRIMARY_CONTRAST_DARK			0x40	/* 濃く */
#define	PHONE2_EXTLINE_ON				0x80	/* 擬似2回線のPHONE2接続状態 Clear:標準ライン側 Set:拡張ライン側 by T.Soneoka 1997/11/11 */

/***********************************************************************
 * プリンターコントローラー用手差しトレー記録紙サイズ
 * SYS_SettingStatus[19]より移動
 * 1996/10/08 Eguchi
 ***********************************************************************/
/*#define PCR_UPPER_SIZE			27	By M.Tachibana 1997/06/30 */
#define PCR_MANUAL_SIZE			27

/* 注）defineの変更等がある場合は、PRN_CheckPaperSize(), MAN_SensorTask()も変更が必要な場合があります */
#define PCR_MANUAL_SIZE_NONE	0x00	/* 上段手動記録紙選択　なし                   */
#define PCR_MANUAL_SIZE_A5		0x01    /* 上段手動記録紙選択　Ａ５縦                 */
#define PCR_MANUAL_SIZE_LT		0x02    /* 上段手動記録紙選択　レター縦               */
#define PCR_MANUAL_SIZE_A4		0x03    /* 上段手動記録紙選択　Ａ４縦                 */
#define PCR_MANUAL_SIZE_LG		0x04    /* 上段手動記録紙選択　リーガル縦             */
#define PCR_MANUAL_SIZE_B5R		0x05    /* 上段手動記録紙選択　Ｂ５横 ＪＩＳ          */
#define PCR_MANUAL_SIZE_B4		0x06    /* 上段手動記録紙選択　Ｂ４縦 ＪＩＳ          */
#define PCR_MANUAL_SIZE_A3		0x07    /* 上段手動記録紙選択　Ａ３縦                 */
#define PCR_MANUAL_SIZE_A4R		0x08    /* 上段手動記録紙選択　Ａ４横                 */
#define PCR_MANUAL_SIZE_LTR		0x09    /* 上段手動記録紙選択　レター横               */
#define PCR_MANUAL_SIZE_F4		0x0A    /* 上段手動記録紙選択　Ｆ４縦                 */
#define PCR_MANUAL_SIZE_A5R		0x0B    /* 上段手動記録紙選択　Ａ５横                 */
#define PCR_MANUAL_SIZE_POST	0x0C    /* 上段手動記録紙選択　はがき縦               */
#define PCR_MANUAL_SIZE_LD		0x0D    /* 上段手動記録紙選択　レジャー縦             */
#define PCR_MANUAL_SIZE_GLTR	0x0E    /* 上段手動記録紙選択　ガバメント・レター横   */
#define PCR_MANUAL_SIZE_EXER	0x0F    /* 上段手動記録紙選択　エグゼブティブ横       */

#define PCR_MANUAL_SIZE_HLTR	0x10    /* 上段手動記録紙選択　ハーフレター横         */
#define PCR_MANUAL_SIZE_INVR	0x10    /* 上段手動記録紙選択　インボイス横           */

#define PCR_MANUAL_SIZE_GLG		0x11    /* 上段手動記録紙選択　ガバメント・リーガル縦 */
#define PCR_MANUAL_SIZE_GLT		0x12    /* 上段手動記録紙選択　ガバメント・レター縦   */
#define PCR_MANUAL_SIZE_CARD	0x13    /* 上段手動記録紙選択　カードストック紙       */
#define PCR_MANUAL_SIZE_EXE		0x14    /* 上段手動記録紙選択　エグゼブティブ縦       */
#define PCR_MANUAL_SIZE_B5		0x15    /* 上段手動記録紙選択　Ｂ５縦 ＪＩＳ          */
#define PCR_MANUAL_SIZE_C5		0x16    /* 上段手動記録紙選択　Ｃ５縦                 */
#define PCR_MANUAL_SIZE_HLT		0x17    /* 上段手動記録紙選択　ハーフ・レター縦       */
#define PCR_MANUAL_SIZE_INV		0x18    /* 上段手動記録紙選択　インボイス縦           */
#define PCR_MANUAL_SIZE_B6		0x19    /* 上段手動記録紙選択　Ｂ６縦 ＪＩＳ          */
#define PCR_MANUAL_SIZE_DL		0x1A    /* 上段手動記録紙選択　ＤＬ縦                 */
#define PCR_MANUAL_SIZE_CM10	0x1B    /* 上段手動記録紙選択　コマーシャル１０縦     */
#define PCR_MANUAL_SIZE_A6		0x1C    /* 上段手動記録紙選択　Ａ６縦                 */
#define PCR_MANUAL_SIZE_MNK		0x1D    /* 上段手動記録紙選択　モナーク縦             */
#define PCR_MANUAL_SIZE_35		0x1E    /* 上段手動記録紙選択　３”ｘ５”縦           */
#define PCR_MANUAL_SIZE_USER	0x1F    /* 上段手動記録紙選択　不定形紙               */

/************************************************************************
 * 回線種別（３から５回線）												*
 * unsigned char SYS_SettingStatus[28]									*
 * 1996/12/17															*
 * Y.Matsukuma															*
 ************************************************************************/
#define SETTING_STATUS_28		28	/* SYS_SettingStatus[SETTING_STATUS_28] */

#define	DIAL_SPEED_10PPS_3		0x00	/* 外付け第３10PPS 		*/
#define	DIAL_SPEED_20PPS_3		0x01	/* 外付け第３20PPS 		*/
#define	LINE_TYPE_TONE_3		0x02	/* 外付け第３Tone Line 	*/

#define	DIAL_SPEED_10PPS_4		0x00	/* 外付け第４10PPS 		*/
#define	DIAL_SPEED_20PPS_4		0x04	/* 外付け第４20PPS 		*/
#define	LINE_TYPE_TONE_4		0x08	/* 外付け第４Tone Line 	*/

#define	DIAL_SPEED_10PPS_5		0x00	/* 外付け第５10PPS 		*/
#define	DIAL_SPEED_20PPS_5		0x10	/* 外付け第５20PPS 		*/
#define	LINE_TYPE_TONE_5		0x20	/* 外付け第５Tone Line 	*/

/************************************************************************
 * 回線種別（６から８回線）												*
 * unsigned char SYS_SettingStatus[29]									*
 * 1996/12/17															*
 * Y.Matsukuma															*
 * ＰＯＰＬＡＲ＿Ｈは標準で２回線収容（標準／拡張）の為、				*
 * ビット割り当てを追加します。											*
 * By O.Kimoto 1997/11/04												*
 ************************************************************************/
#define SETTING_STATUS_29		29	/* SYS_SettingStatus[SETTING_STATUS_29] */

#define	DIAL_SPEED_10PPS_6		0x00	/* 外付け第６10PPS 		*/
#define	DIAL_SPEED_20PPS_6		0x01	/* 外付け第６20PPS 		*/
#define	LINE_TYPE_TONE_6		0x02	/* 外付け第６Tone Line 	*/

#define	DIAL_SPEED_10PPS_7		0x00	/* 外付け第７10PPS 		*/
#define	DIAL_SPEED_20PPS_7		0x04	/* 外付け第７20PPS 		*/
#define	LINE_TYPE_TONE_7		0x08	/* 外付け第７Tone Line 	*/

#define	DIAL_SPEED_10PPS_8		0x00	/* 外付け第８10PPS 		*/
#define	DIAL_SPEED_20PPS_8		0x10	/* 外付け第８20PPS 		*/
#define	LINE_TYPE_TONE_8		0x20	/* 外付け第８Tone Line 	*/

#define	DIAL_SPEED_10PPS_EXT	0x00	/* 内蔵（拡張）10PPS 	 */ /* 警察FAXでは、警電回線用として使用する */
#define	DIAL_SPEED_20PPS_EXT	0x40	/* 内蔵（拡張）20PPS 	 */
#define	LINE_TYPE_TONE_EXT		0x80	/* 内蔵（拡張）Tone Line */

/*-------------------------------------------------------------------------
** SYS_SettingStatus[30]～SYS_SettingStatus[49]までを使用したい場合には
** product.hのPRO_EXT_SETTING_STATUSをENABLEにしてください。
** 1998/06/15 H.Yoshikawa
*/

/************************************************************************
 * 機器設定データ														*
 * unsigned char SYB_SettingStatus[30]									*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
#define SETTING_STATUS_30		30	/* SYB_SettingStatus[SETTING_STATUS_30] */
#define ND_MODE_ON	 			0x01	/* ナンバーディスプレイＯＮ	*/
#define ND_DIAL_IN_ON			0x02	/* ダイヤルインＯＮ（ＮＤ対応用）*/
#define WARP_MODE_ON			0x04	/* ワープ機能ＯＮ		*/
#define	ND_TEL2_ND_ON			0x08	/* TEL2 につないだ電話のナンバーディスプレイの機能を利用する */
#define ND_WARP_ON				0x10	/* ＮＤワープＯＮ By H.Fujimura 1999/01/07 */

 #if defined(SATSUKI2) || defined(HINOKI2) || defined (HINOKI3) || defined (KEISATSU)	/* F351用新機能チェック追加 by Y.Kano 2004/04/01 */
/************************************************************************
 * 機器設定データ														*
 * unsigned char SYB_SettingStatus[31]									*
 * 2004/01/07															*
 * 加納義彦																*
 ************************************************************************/
#define SETTING_STATUS_31		31	/* SYB_SettingStatus[SETTING_STATUS_31] */
#define NEW_SENSOR_SETIING		0x01	/* F250用A/Dセンサー調整機能 */	/* F351用追加 */
  #if defined(KEISATSU)				/* LCDで表示警察属性内容 Added by SMuratec 夏 2005/06/22 */
#define SETTING_LINE			0x02	/* 警電/加入の設定  0: 警電 1:加入 */
#define SETTING_MODE			0x04	/* 一斉/個別の設定  0: 一斉 1:個別 */
#define SETTING_SCRAMBLE_KANYU	0x08	/* 加入回線でスクランブル設定 0: ON   1:OFF  */
#define SETTING_SCRAMBLE_KEIDEN	0x10	/* 警電回線でスクランブル設定 0: ON   1:OFF  */
#define SETTING_SENYOU			0x20	/* 共通/専用の設定  0: 共通 1:専用 */
  #endif

 #endif

#if defined (KEISATSU)
/************************************************************************
 * 拡張回線用ベル回数(警察FAXでは警電回線に使用)						*
 * unsigned char SYB_SettingStatus[32]									*
 * 2005/06/06															*
 * 石橋正和																*
 ************************************************************************/
#define NUMBER_OF_RINGS_EXT		32	/* SYB_SettingStatus[NUMBER_OF_RINGS_EXT] */

#endif /* #if defined (KEISATSU) */



#endif
