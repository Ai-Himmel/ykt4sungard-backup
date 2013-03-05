/* By Y.Suzuki 1996/10/15 */
/* Original File : jun\usr2:\src\kobe\anzu\define\sysmax.h */
#ifndef sysmax_h
	#define sysmax_h
/*
** 履歴：
**		1996/05/20 S.Kawasaki モデル別のMAX値の削除
**
*/
/************************************************************************
 * 機種名バージョン名 (16 Chars + NULL)									*
 * unsigned char ROM_Revision[ROM_REVISION_MAX]							*
 * 1997/05/28															*
 * 橘正樹																*
 ************************************************************************/
#define ROM_REVISION_MAX	17		/* (16+NULL) */

/************************************************************************
 * バックアップRAMテスト												*
 * unsigned char SYB_BackupRAM_TestArea[SYS_BACKUP_RAM_TEST_AREA_MAX]	*
 * 機種名を記憶する														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_BACKUP_RAM_TEST_AREA_MAX	5

/************************************************************************
 * パスコード															*
 * unsigned char SYB_PasscodeNumber[SYS_PASSCODE_MAX]					*
 * syspass.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_PASSCODE_MAX		4	/* パスコード4桁 */

/************************************************************************
 * 親展受信ボックス														*
 * struct SYS_MailBoxData_t SYB_MailBox[SYS_MAILBOX_MAX]				*
 * struct SYS_MailBoxData_t.RemoteName[SYS_REMOTE_NAME_MAX]				*
 * struct SYS_MailBoxData_t.BoxName[SYS_BOX_NAME_MAX]					*
 * sysmailb.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_MAILBOX_MAX		10	/* 最大親展受信ボックス数 */
#define	SYS_REMOTE_NAME_MAX	21	/* 親展受信相手先名20文字+NULL */
#define	SYS_BOX_NAME_MAX	17	/* 親展者名16文字+NULL */

/************************************************************************
 * 通信管理記録(分離型)													*
 * struct SYS_JournalData_t SYB_TxJournalFile[SYS_JOURNAL_MAX]			*
 * struct SYS_JournalData_t SYB_RxJournalFile[SYS_JOURNAL_MAX]			*
 * struct SYS_JournalData_t.RemoteID_TTI[SYS_JOURNAL_RMT_MAX]			*
 * sysjrnl.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if (0)
**	#define	SYS_JOURNAL_MAX		25	/* 最大通信管理記録数 */
**	#define	SYS_JOURNAL_RMT_MAX	21	/* 相手先名20文字+NULL */
#endif

/************************************************************************
 * 通信管理記録(一体型)													*
 * struct SYS_JournalData_t SYB_JournalFile[SYS_JOURNAL_MAX]			*
 * struct SYS_JournalData_t.RemoteID_TTI[SYS_JOURNAL_RMT_MAX]			*
 * sysjrnl.jsw参照														*
 * 1993/12/21															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_JOURNAL_MAX	125		/* 最大通信管理記録（送受信用）数 *//* Change 25 to 125 by O.Kimoto 1998/01/17 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	#define	SYS_JOURNAL_MAX	125		/* 最大通信管理記録（送受信用）数 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
	#define	SYS_JOURNAL_MAX	70		/* 最大通信管理記録（送受信用）数 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	#define	SYS_JOURNAL_MAX	100		/* 最大通信管理記録（送受信用）数 *//* 25から100に変更 1997/09/10 Y.Matsukuma */
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_JOURNAL_MAX	125		/* 最大通信管理記録（送受信用）数 *//* Change 25 to 125 by O.Kimoto 1998/01/17 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)	/* Add by Y.Kano 2003/07/11 */
 #if (PRO_POST_OFFICE == ENABLE)	/* 郵政局特ROM by O.Kimoto 2001/01/21 */
	#define	SYS_JOURNAL_MAX_AREA	125		/* 最大通信管理記録（送受信用）数 */
 #else
	#define	SYS_JOURNAL_MAX	125		/* 最大通信管理記録（送受信用）数 *//* Change 25 to 125 by O.Kimoto 1998/01/17 */
 #endif
#elif (PRO_KEYPANEL == PANEL_STOCKHM2) /* Add by SMuratec C.P 2004/06/10 for V195通信結果記録表示仕様 */
	#define	SYS_JOURNAL_MAX  125		/* 最大通信管理記録（送受信用）数 */
#endif

#define	SYS_JOURNAL_RMT_MAX	21	/* 相手先名20文字+NULL */

/************************************************************************
 * 電話番号																*
 * struct SYS_DialData_t_t.Direct[SYS_DIRECT_DIAL_MAX]					*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_DIRECT_DIAL_MAX		21	/* 直接ダイヤル番号40桁+NULL */
#define	SYS_FXSPEED_DIAL_MAX	2	/* FX短縮4桁 */

/************************************************************************
 * 標準短縮ダイヤル														*
 * struct SYS_SpeedDialData_t SYB_SpeedDial[SYS_SPEED_DIAL_MAX]			*
 * struct SYS_SpeedDialData_t.Dial[SYS_TEL_2DIGIT_MAX]					*
 * struct SYS_SpeedDialData_t.Name[SYS_DIAL_NAME_MAX]					*
 * sysspeed.jsw参照														*
 * SYS_TEL_2DIGIT_MAX < SYS_DIRECT_DIAL_MAXであること					*
 * 1993/11/19	1993/12/28												*
 * 吉川弘康		田中伸一												*
 ***********************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_SPEED_DIAL_MAX			128	/* 最大短縮ダイヤル数 */
	#define	SYS_SPEED_DIAL_MAX_BKUP		128	/* 最大短縮ダイヤル数 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_BIT_FIELD_MAX		16	/* 短縮ダイヤル数128としたとき(128/8bit) */
	#define	SYS_TEL_2DIGIT_MAX			21	/* 短縮ダイヤル40桁+NULL */
	#define	SYS_DIAL_NAME_MAX			25	/* ICHOU変更 -- 相手先名24文字+NULL */
	#define	SYS_NAME_PRONUNCIATION_MAX	2	/* 読み仮名 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	#define	SYS_SPEED_DIAL_MAX			128	/* 最大短縮ダイヤル数 */
	#define	SYS_SPEED_DIAL_MAX_BKUP		128	/* 最大短縮ダイヤル数 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_BIT_FIELD_MAX		16	/* 短縮ダイヤル数128としたとき(128/8bit) */
	#define	SYS_TEL_2DIGIT_MAX			21	/* 短縮ダイヤル40桁+NULL */
	#define	SYS_DIAL_NAME_MAX			25	/* ICHOU変更 -- 相手先名24文字+NULL */
	#define	SYS_NAME_PRONUNCIATION_MAX	2	/* 読み仮名 */
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_L)
 #if defined(POPLAR_F)
  #if defined(JP1)
	#define	SYS_SPEED_DIAL_MAX			128	/* 最大短縮ダイヤル数 */
  #else
	#define	SYS_SPEED_DIAL_MAX			100	/* 最大短縮ダイヤル数 */
  #endif
 #else
  #if defined(POPLAR_N) /* ポプラＮＴＴ仕様は、短縮１００件 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_DIAL_MAX			100	/* 最大短縮ダイヤル数 */
  #else /* POPLAR_L */
	#define	SYS_SPEED_DIAL_MAX			128	/* 最大短縮ダイヤル数 */
  #endif
 #endif
	#define	SYS_SPEED_DIAL_MAX_BKUP		128	/* 最大短縮ダイヤル数 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_BIT_FIELD_MAX		16	/* 短縮ダイヤル数128としたとき(128/8bit) */
	#define	SYS_TEL_2DIGIT_MAX			21	/* 短縮ダイヤル40桁+NULL */
	#define	SYS_DIAL_NAME_MAX			25	/* ICHOU変更 -- 相手先名24文字+NULL */
	#define	SYS_NAME_PRONUNCIATION_MAX	2	/* 読み仮名 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	#define	SYS_SPEED_DIAL_MAX			140	/* 最大短縮ダイヤル数 */
	#define	SYS_SPEED_DIAL_MAX_BKUP		140	/* 最大短縮ダイヤル数 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_BIT_FIELD_MAX		18	/* 短縮ダイヤル数140としたとき(140/8bit) */
	#define	SYS_TEL_2DIGIT_MAX			21	/* 短縮ダイヤル40桁+NULL */
	#define	SYS_DIAL_NAME_MAX			17	/* 相手先名16文字+NULL */
	#define	SYS_NAME_PRONUNCIATION_MAX	2	/* 読み仮名 */
/* ANZU F-100 */
/*	#define	SYS_SPEED_DIAL_MAX			120	   最大短縮ダイヤル数 */
/*	#define	SYS_SPEED_BIT_FIELD_MAX		 15	   短縮ダイヤル数120としたとき(120/8bit) */
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_SPEED_DIAL_MAX			176	/* 最大短縮ダイヤル数 200-SYS_ONTOUCH_MAX(24) = 176 1998/09/04 H.Yoshikawa */
	#define	SYS_SPEED_DIAL_MAX_BKUP		176	/* 最大短縮ダイヤル数 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_BIT_FIELD_MAX		22	/* 短縮ダイヤル数176としたとき(176/8bit) *//* 1998/09/08 */
	#define	SYS_TEL_2DIGIT_MAX			21	/* 短縮ダイヤル40桁+NULL */
	#define	SYS_DIAL_NAME_MAX			25	/* ICHOU変更 -- 相手先名24文字+NULL */
	#define	SYS_NAME_PRONUNCIATION_MAX	2	/* 読み仮名 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

	/* HINOKI By O.Kimoto 1998/09/04 */
 #if 0 /* defined (HINOKI2)	/@ 短縮ダイヤル増加検討（暫定） 2002/07/24 T.Takagi */
	/* QUEUEの数を管理する変数がUBYTE宣言されているため、					**
	** 最大短縮ダイヤル数= 255 - SYS_ONETOUCH_MAX - SYS_COM_DIRECT_DIAL_MAX	**
	** に制限される。														*/
//	#define	SYS_SPEED_DIAL_MAX			210	/* 最大短縮ダイヤル数 */
//	#define	SYS_SPEED_DIAL_MAX_BKUP		210	/* 最大短縮ダイヤル数 */
//	#define	SYS_SPEED_BIT_FIELD_MAX		27  /* 短縮ダイヤル数210としたとき(210/8bit) */
 #else
  #if defined(HINOKI2) && defined(JPNNTT)	/* NTT仕様 音声応答/通信結果表示 by J.Kishida 2002/09/09 */
	#define	SYS_SPEED_DIAL_MAX			196	/* 最大短縮ダイヤル数 標準に20件追加 by J.Kishida 2002/09/09 */
	#define	SYS_SPEED_DIAL_MAX_BKUP		196	/* 最大短縮ダイヤル数 */
	#define	SYS_SPEED_BIT_FIELD_MAX		25	/* 短縮ダイヤル数196としたとき(196/8bit=24.5) */
  #else
   #if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Added by SMuratec L.Z.W 2003/08/05 */
	#define	SYS_SPEED_DIAL_MAX			80	/* 最大短縮ダイヤル数 標準に20件追加 */
	#define	SYS_SPEED_DIAL_MAX_BKUP		80	/* 最大短縮ダイヤル数 */
	#define	SYS_SPEED_BIT_FIELD_MAX		10	/* 短縮ダイヤル数80としたとき(80/8bit=10) */
   #else /* (PRO_KEYPANEL != PANEL_SATSUKI2)  && (PRO_KEYPANEL != PANEL_STOCKHM2) */
	#define	SYS_SPEED_DIAL_MAX			176	/* 最大短縮ダイヤル数 200-SYS_ONTOUCH_MAX(24) = 176 1998/09/04 H.Yoshikawa */
	#define	SYS_SPEED_DIAL_MAX_BKUP		176	/* 最大短縮ダイヤル数 By Y.Suzuki 1998/03/15 */
	#define	SYS_SPEED_BIT_FIELD_MAX		22	/* 短縮ダイヤル数176としたとき(176/8bit) */
   #endif /* End of (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2) */
  #endif
 #endif
	#define	SYS_TEL_2DIGIT_MAX			21	/* 短縮ダイヤル40桁+NULL */
	#define	SYS_DIAL_NAME_MAX			25	/* ICHOU変更 -- 相手先名24文字+NULL */
	#define	SYS_NAME_PRONUNCIATION_MAX	2	/* 読み仮名 */
#endif

/************************************************************************
 * 第2短縮ダイヤル														*
 * struct SYS_SpeedDialData_t SYB_2ndSpeedDial[SYS_2ND_SPEED_DIAL_MAX]	*
 * 1993/12/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_2ND_SPEED_DIAL_MAX	0	/* 最大第2短縮ダイヤル数 */

/************************************************************************
 * 標準ワンタッチダイヤル												*
 * struct SYS_OnetouchDialData_t SYB_OnetouchDial[SYS_ONETOUCH_MAX]		*
 * struct SYS_OnetouchDialData_t.DialData.Job[SYS_JOB_MAX]				*
 * sysonet.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_ONETOUCH_MAX			72	/* 最大ワンタッチダイヤル数 */
	#define	SYS_ONETOUCH_BIT_FIELD_MAX	9	/* ワンタッチダイヤル数７２としたとき(72/8bit) */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	#define	SYS_ONETOUCH_MAX			72	/* 最大ワンタッチダイヤル数 */
	#define	SYS_ONETOUCH_BIT_FIELD_MAX	9	/* ワンタッチダイヤル数７２としたとき(72/8bit) */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/23 Y.Matsukuma */
	#define	SYS_ONETOUCH_MAX			14	/* 最大ワンタッチダイヤル数 */
 #else
	#define	SYS_ONETOUCH_MAX			60	/* 最大ワンタッチダイヤル数 */
 #endif
	#define	SYS_ONETOUCH_BIT_FIELD_MAX	8	/* ワンタッチダイヤル数６０としたとき(30/8bit) */
	/* ANZU F-100 */
/*	#define	SYS_ONETOUCH_MAX			30	   最大ワンタッチダイヤル数 */
/*	#define	SYS_ONETOUCH_BIT_FIELD_MAX	4	   ワンタッチダイヤル数３０としたとき(30/8bit) */
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_ONETOUCH_MAX			24	/* 最大ワンタッチダイヤル数 */
	#define	SYS_ONETOUCH_BIT_FIELD_MAX	3	/* ワンタッチダイヤル数２４としたとき(24/8bit) */
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)
	#define	SYS_ONETOUCH_MAX			24	/* 最大ワンタッチダイヤル数 */
	#define	SYS_ONETOUCH_BIT_FIELD_MAX	3	/* ワンタッチダイヤル数２４としたとき(24/8bit) */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)		/* Add by Y.Kano 2003/07/11 */
	/* (SYS_ONETOUCH_MAX 24->20) Modify by SMuratec L.Z.W 2003/08/05 */
	#define	SYS_ONETOUCH_MAX			20	/* 最大ワンタッチダイヤル数  ２０に変更必要 ？*/
	#define	SYS_ONETOUCH_BIT_FIELD_MAX	3	/* ワンタッチダイヤル数２０としたとき(20/8bit) */
#endif


#define	SYS_JOB_MAX				6	/* 1キー当たりの最大ジョフ゛数+-1 */
#define	SYS_PRG_DIAL_MAX		10	/* プログラム同報数 */
#define	SYS_2ND_PRG_DIAL_MAX	10	/* 最大ワンタッチダイヤル同報数 */

/************************************************************************
 * 第2ワンタッチダイヤル												*
 * struct SYS_SpeedDialData_t SYB_2ndOnetouchDial[SYS_2ND_ONETOUCH_MAX]	*
 * 1993/12/06															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_2ND_ONETOUCH_MAX	0	/* 最大第2ワンタッチダイヤル数 */

/************************************************************************
 * 転送先ダイヤル														*
 * unsigned char SYB_SubDial[SYS_SUB_DIAL_MAX][SYS_TEL_2DIGIT_MAX]		*
 * syssubd.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_SUB_DIAL_MAX	10	/* 最大転送先ダイヤル数 */

/************************************************************************
 * プログラムワンタッチダイアル											*
 * 1995/11/27 Eguchi													*
 * プログラムワンタッチは専用キーになるため								*
 ************************************************************************/
/* 1998/02/19 Y.Murata
 * アンズＧＢＲのマーキュリーキー対応のためbkupram.c 専用のdefineを追加しました
 * SYS_PROGRAM_MAX_BKUPとSYS_PROGRAM_MAXは特殊な場合をのぞいて同じ値にしてください。
 * プログラム上はSYS_PROGRAM_MAXを使うこと
*/

#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_PROGRAM_MAX_BKUP		8	/* 最大プログラムワンタッチ数 */
	#define	SYS_PROGRAM_MAX				8	/* 最大プログラムワンタッチ数 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	#define	SYS_PROGRAM_MAX_BKUP		8	/* 最大プログラムワンタッチ数 */
	#define	SYS_PROGRAM_MAX				8	/* 最大プログラムワンタッチ数 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	#define	SYS_PROGRAM_MAX_BKUP		12	/* 最大プログラムワンタッチ数 */
 #if defined(GBR)  /*GBR仕様はP６とP12をマーキュリーキーとする 1998/02/19 Y.Matsukuma */
	#define	SYS_PROGRAM_MAX				10	/* 最大プログラムワンタッチ数 */
 #else
	#define	SYS_PROGRAM_MAX				12	/* 最大プログラムワンタッチ数 */
 #endif
#endif

/*-------------------------------------------------------------------------
** SAKAKIでは、この機能を廃止し、キーマクロ機能に統合しました。
** undefにならないようにしておきます。値を０にするとコンパイルエラーとなる。
** 1998/06/10 H.Yoshikawa
** プログラムワンタッチ復帰 [25] - [30] 1998/07/22 By M.Kuwahara
*/
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_PROGRAM_MAX_BKUP		6	/* 最大プログラムワンタッチ数 */
	#define	SYS_PROGRAM_MAX				6	/* 最大プログラムワンタッチ数 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
 #if defined(KEISATSU)	/* 警察FAX Modify by SMuratec 夏 2005/08/05 */
 	#define	SYS_PROGRAM_MAX_BKUP		2	/* 最大プログラムワンタッチ数 */
	#define	SYS_PROGRAM_MAX				2	/* 最大プログラムワンタッチ数 */
 #else
  #if defined(HINOKI3)	/* by K.Watanabe 2004/10/12 */
	#define	SYS_PROGRAM_MAX_BKUP		5	/* 最大プログラムワンタッチ数 */
	#define	SYS_PROGRAM_MAX				5	/* 最大プログラムワンタッチ数 */
  #else
	/* HINOKI By O.Kimoto 1998/09/04 */
	#define	SYS_PROGRAM_MAX_BKUP		6	/* 最大プログラムワンタッチ数 */
  #define	SYS_PROGRAM_MAX				6	/* 最大プログラムワンタッチ数 */
  #endif
 #endif	/* KEISATSU */
#endif

/************************************************************************
 * グループ番号															*
 * OPR_DEF.hから移動してきました(元OPR_GROUP_NUMBER_MAX)				*
 * 1996/5/23															*
 * 曽根岡拓																*
 ************************************************************************/
#define	SYS_GROUP_NUMBER_MAX	32

/************************************************************************
 * メモリスイッチ														*
 * unsigned char SYS_MemorySwitch[SYS_MEMORY_SWITCH_MAX]				*
 * memsw.xls参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_MEMORY_SWITCH_MAX	100

/************************************************************************
 * 機器パラメータ														*
 * unsigned char SYB_MachineParameter[SYS_MACHINE_PARAMETER_MAX]		*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_MACHINE_PARAMETER_MAX	100

/************************************************************************
 * ローカル機器設定														*
 * unsigned char SYB_LocalStatus[SYS_LOCAL_MAX]							*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_LOCAL_MAX		5

/************************************************************************
 * 機器設定																*
 * unsigned char SYB_SettingStatus[SYS_SETTING_MAX]						*
 * setting.xls参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_EXT_SETTING_STATTUS == DISABLE)
#define	SYS_SETTING_MAX			30
#endif

#if (PRO_EXT_SETTING_STATTUS == ENABLE)
#define	SYS_SETTING_MAX			50
#endif

/************************************************************************
 * 発信元電話番号														*
 * syssubid.jsw参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_ID_MAX				21

/************************************************************************
 * 発信元名(送信原稿先頭付加用)											*
 * systti.jsw参照														*
 * 1994/05/12															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_TTI_MAX				23

/************************************************************************
 * 発信元名カナＩＤ(非標準手順用)										*
 * systti.jsw参照														*
 * 1993/11/20															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_TTI_ID_MAX			17

/************************************************************************
 * ダイヤルイン															*
 * struct SYS_DialinData_t.FaxNumber[SYS_DIALIN_MAX]					*
 * struct SYS_DialinData_t.Tel1Number[SYS_DIALIN_MAX]					*
 * struct SYS_DialinData_t.Tel2Number[SYS_DIALIN_MAX]					*
 * sysdiali.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_DIALIN_MAX		5	/* ダイヤルイン用電話番号4桁+NULL */

/************************************************************************
 * 料金管理																*
 * struct SYS_CostBaseTable_t SYB_CostTable[SYS_COST_TABLE_MAX]			*
 * syscost.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_COST_TABLE_MAX	20	/* 最大料金管理テーブル数 */

/************************************************************************
 * 部門管理別料金管理のトータル時間										*
 * struct SYS_DepartData_t SYB_DepartFile[SYS_DEPART_MAX]				*
 * sysdeprt.doc参照														*
 * 1994/03/25															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_DEPART_MAX	100	/* 最大部門管理数 */ /* 50から100に変更 1997/10/27  By T.Yamaguchi */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L)
	#define	SYS_DEPART_MAX	100	/* 最大部門管理数 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	#define	SYS_DEPART_MAX	100	/* 最大部門管理数 *//* 50から100に変更 1997/09/10 Y.Matsukuma */
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_DEPART_MAX	100	/* 最大部門管理数 */ /* 50から100に変更 1997/10/27  By T.Yamaguchi */
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)
	/* HINOKI By O.Kimoto 1998/09/04 */
	#define	SYS_DEPART_MAX	100	/* 最大部門管理数 */ /* 50から100に変更 1997/10/27  By T.Yamaguchi */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
	/* SATSUKI2 by Y.Kano 2003/07/11 */
	#define	SYS_DEPART_MAX	100	/* 最大部門管理数 */ /* 50から100に変更 1997/10/27  By T.Yamaguchi */
#endif

/************************************************************************
 * 一括送信																*
 * struct SYS_BatchTxData_t SYB_BatchTxFile[SYS_BATCH_FILE_MAX]			*
 * struct SYS_BatchTxData_t.Name[SYS_BATCH_NAME_MAX]					*
 * struct SYS_BatchTxData_t.IndexNo[SYS_BATCH_INDEX_MAX]				*
 * sysbatch.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_BATCH_FILE_MAX	5	/* 最大一括送信数 */

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI)*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H) || (PRO_KEYPANEL == PANEL_POPLAR_B) || (PRO_KEYPANEL == PANEL_POPLAR_L) || (PRO_KEYPANEL == PANEL_SAKAKI) || (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */

	#define	SYS_BATCH_NAME_MAX	25	/* ICHOU変更 -- 宛先名24文字+NULL */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	#define	SYS_BATCH_NAME_MAX	17	/* 宛先名16文字+NULL */
#endif
#define	SYS_BATCH_INDEX_MAX	40	/* 最大原稿登録回数 */

/************************************************************************
 * カバーページ送信のメッセージ内容										*
 * unsighed char SYB_CoverPageMessage[SYS_MESSAGE_MAX]					*
 * sysmesg.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_MESSAGE_MAX		41	/* メッセージ40文字+NULL */

/************************************************************************
 * 通信予約																*
 * struct SYS_CommandData_t SYB_CommandFile[SYS_COM_FILE_MAX]			*
 * struct SYS_CommandData_t.DialNumber[SYS_COM_DIAL_MAX]				*
 * struct SYS_CommandData_t.OptionNumber.RelaySourceID[SYS_SRC_ID_MAX]	*
 * struct SYS_CommandData_t.OptionNumber.DataBaseNumber[SYS_DATA_BASE_MAX]*
 * syscomf.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
/* 1998/01/30
 * SYS_COM_DIAL_MAXは使用したらだめです。
 * SYS_COM_DIRECT_DIAL_MAXを追加したときにSYS_COM_DIAL_MAXは消しとくべきです。誰やもう
 * こんなしょうもないのは変更ＬＯＧにいれませんよ。誰も使ってないし
*/
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_COM_FILE_MAX		99	/*TBD*//* 最大通信予約数 *//* Change 50 to 99 by O.Kimoto 1998/01/17 */
	#define	SYS_COM_DIRECT_DIAL_MAX	20	/* 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	#define	SYS_COM_FILE_MAX		99	/* 最大通信予約数 */
	#define	SYS_COM_DIRECT_DIAL_MAX	20	/* 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
	#define	SYS_COM_FILE_MAX		20	/*TBD*//* 最大通信予約数 */
	#define	SYS_COM_DIRECT_DIAL_MAX	20	/* 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
  #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/10 Y.Murata */
	#define	SYS_COM_FILE_MAX		 1	/* 最大通信予約数 */
	#define	SYS_COM_FILE_MAX2		99	/* 最大通信予約数 */
  #else
	#define	SYS_COM_FILE_MAX		99	/* 最大通信予約数 *//* 20から99に変更 1997/09/10 Y.Matsukuma */
  #endif
	#define	SYS_COM_DIRECT_DIAL_MAX	20	/* 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_COM_FILE_MAX		99	/*TBD*//* 最大通信予約数 *//* Change 50 to 99 by O.Kimoto 1998/01/17 */
	#define	SYS_COM_DIRECT_DIAL_MAX	20	/* 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)
	/* HINOKI By O.Kimoto 1998/09/04 */
	#define	SYS_COM_FILE_MAX		100	/*TBD*//* 最大通信予約数 *//* Change 50 to 99 by O.Kimoto 1998/01/17 */
	#define	SYS_COM_DIRECT_DIAL_MAX	20	/* 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)
	/* SATSUKI2 by Y.Kano 2003/07/11 */
	#define	SYS_COM_FILE_MAX		100	/*TBD*//* 最大通信予約数 *//* Change 50 to 99 by O.Kimoto 1998/01/17 */
	#define	SYS_COM_DIRECT_DIAL_MAX	10	/* <-20 製品仕様書見落とし。O.Oshima 2003/11/07 1通信あたりの直接ダイヤル最大宛先 */
	/*#define	SYS_COM_DIAL_MAX		10*/	/* 1通信当たりの最大宛先数 */
#endif

#define	SYS_SRC_ID_MAX			21	/* 中継配信時の親機の発信元番号20桁+NULL*/
#define	SYS_DATA_BASE_MAX		11	/* 検索ポーリング時のファイル数10+ -1*/
#define	F_CODE_DATA_MAX			1	/* Ｆコード登録数 1	 ﾏﾙﾁｻﾌﾞｱﾄﾞﾚｽ通信の場合は増やす */
/************************************************************************
 * 発信スケジューラ														*
 * struct SYS_ExecQueueData_t	SYB_ExecQueue[SYS_EXEC_QUEUE_MAX]		*
 * struct SYS_ExecQueueData_t.ErrorPage[SYS_ERROR_PAGE]					*
 * sysexec.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
/*Ｌ４００ 短縮１００件のためﾃﾞﾌｧｲﾝ変更 By Y.Suzuki 1998/03/17 */
/*#define	SYS_EXEC_QUEUE_MAX	(SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX + SYS_2ND_SPEED_DIAL_MAX + SYS_COM_DIRECT_DIAL_MAX)  */
#define	SYS_EXEC_QUEUE_MAX	(SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX_BKUP + SYS_2ND_SPEED_DIAL_MAX + SYS_COM_DIRECT_DIAL_MAX)
									/* 最大同報可能数 */
#define	SYS_ERROR_PAGE		6		/* 6*8=48ページ */

/************************************************************************
 * マルチコピー															*
 * struct SYS_MultiCopyData_t SYB_MultiCopyFile[SYS_MULTI_COPY_MAX]		*
 * sysmcopy.jsw参照														*
 * 1993/11/19															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_MULTI_COPY_MAX	10		/* 最大マルチコピー数 */

/************************************************************************
 * メモリ受信原稿プリント												*
 * struct SYS_MemoryRxPrintData_t SYB_MemoryRxPrint[SYS_MEMORY_RX_MAX]	*
 * sysmemrx.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_H)
	#define	SYS_MEMORY_RX_MAX	100		/* 最大代行受信数 *//* Change 25 to 100 by O.Kimoto 1998/01/17 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	#define	SYS_MEMORY_RX_MAX	100		/* 最大代行受信数 */
#endif
#if (PRO_KEYPANEL == PANEL_POPLAR_L)
	#define	SYS_MEMORY_RX_MAX	50		/* 最大代行受信数 */
#endif
#if (PRO_KEYPANEL == PANEL_ANZU_L)
	#define	SYS_MEMORY_RX_MAX	50		/* 最大代行受信数 *//* 25->50 1997/08/12 Y.Murata */
#endif
#if (PRO_KEYPANEL == PANEL_SAKAKI)
	#define	SYS_MEMORY_RX_MAX	100		/* 最大代行受信数 *//* Change 25 to 100 by O.Kimoto 1998/01/17 */
#endif
#if (PRO_KEYPANEL == PANEL_HINOKI)
	#define	SYS_MEMORY_RX_MAX	100		/* 最大代行受信数 *//* Change 25 to 100 by O.Kimoto 1998/01/17 */
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
#if (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* Add by Y.Kano 2003/07/11 */
	#define	SYS_MEMORY_RX_MAX	100		/* 最大代行受信数 *//* Change 25 to 100 by O.Kimoto 1998/01/17 */
#endif

/************************************************************************
 * リダイヤルバッファ													*
 * unsinged char SYB_RedialBuffer[SYS_REDIAL_BUF_MAX]					*
 * sysrdial.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_REDIAL_BUF_MAX	41		/* リダイヤル40桁+NULL */

/************************************************************************
 * PBX番号																*
 * syspbx.jsw参照														*
 * syscomf.jsw参照														*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_PBX_NUMBER_MAX	5		/* 内線番号4桁+NULL */

/************************************************************************
 * T30モニタ															*
 * unsigned char SYS_T30MonitorBuffer[SYS_T30MONITOR_BUF_MAX]			*
 * 1993/11/24															*
 * 吉川弘康																*
 ************************************************************************/
#define	SYS_T30MONITOR_BUF_MAX	1024

/************************************************************************
 * ﾏｼ-ﾝ･ｽﾃ-ﾀｽ															*
 * unsigned char SYS_MachineStatus[SYS_MACHINE_STATUS_MAX]				*
 * 1993/12/20															*
 * S.Kawasaki															*
 ************************************************************************/
#define	SYS_MACHINE_STATUS_MAX	20

/***********************************************************************
 *		   BY:	 S.Kawasaki			copy by murata
 *		 DATE:	 Wed 8 Apr 1992
 *		 TYPE:	 DEFINE
 * VAR TO HOLD:	 struct	DialingData_t	DialingNumber
 * DESCRIPTION:	 多機能電話用バッファデータ
 ***********************************************************************/
#define	DIALING_NUMBER_MAX	80

/***********************************************************************
 *		   BY:	 t.yamaguchi
 *		 DATE:	 Fri 22 Dec 1995
 *		 TYPE:	 DEFINE
 * VAR TO HOLD:	 unsigned char	SYS_PinBuffer[PIN_DIALING_NUMBER_MAX]
 * DESCRIPTION:	 PIN番号用バッファデータ
 ***********************************************************************/
#define	PIN_DIALING_NUMBER_MAX	9	/* PIN番号8桁+NULL */

/************************************************************************
 * メモリ送信を行う原稿のファイルナンバー								*
 * TxMemoryFileNo[SYS_TX_MEMORY_FILE_NO_MAX]							*
 *		TxMemoryFileNoは通信で使っているだけですが、					*
 *		SYS_TX_MEMORY_FILE_NO_MAX はgalaxyの時はLSTでも使っているので	*
 *		SYS_にいれました												*
 * 1994/01/25 Y.Murata													*
 * 1994/09/22 Y.Suzuki 一括送信追加										*
 ************************************************************************/
#if(PRO_BATCH_TX == ENABLE)
	#define	SYS_TX_MEMORY_FILE_NO_MAX	40		/* 一括送信　１ボックスあたり　４０件の原稿を登録する */
#else
 #if (PRO_F_CODE == ENABLE)
	#define	SYS_TX_MEMORY_FILE_NO_MAX	30		/* Ｆコード原稿最大３０ファイル */
 #else
	#define	SYS_TX_MEMORY_FILE_NO_MAX	11		/* 通信予約数(10) + 即時メモリ送信(1) */
 #endif
#endif

/***********************************************************************
 *		   BY:	 t.yamaguchi
 *		 DATE:	 1997/05/12
 *		 TYPE:	 DEFINE
 * VAR TO HOLD:	 UBYTE	SYB_JunkMailProtectDialBuffer[SYS_JUNK_DIAL_MAX][SYS_JUNK_DIAL_NUMBER_MAX]
 * DESCRIPTION:	 ジャンクメール防止ダイヤル登録バッファ
  ***********************************************************************/
#define	SYS_JUNK_DIAL_MAX	50	/* 登録可能ﾀﾞｲﾔﾙ件数 */
#define	SYS_JUNK_DIAL_NUMBER_MAX	5	/* ダイヤル桁数 BCD8桁+0xFF 終端ｺｰﾄﾞに0xFを格納 */

/************************************************************************
 * ポケットベル電話番号エリアサイズ										*
 * unsigned char SYS_PocketBellDial[SYS_POCKETBELL_MAX]					*
 * 1994/02/07 村田														*
*************************************************************************/
#define	SYS_POCKETBELL_MAX			21

/************************************************************************
 *	マーキュリー・リダイヤルバッファ
 *	unsigned char SYB_MercuryDialBuffer[SYS_MERCURY_BUF_MAX]
 *	40桁+1(NULL)=41桁
 *	1993.3.9	HARADA
 ************************************************************************/
#define	SYS_MERCURY_BUF_MAX		41

/************************************************************************
 *		   BY:	 J.Masuda
 *		 DATE:	 1995/05/12
 *		 TYPE:	 DEFINE
 * VAR TO HOLD:	 N/A
 * DESCRIPTION:	 ﾒﾓﾘ受信のために使用するﾌﾞﾛｯｸ数
 ************************************************************************/
#define	MEM_BLOCK_MAX_FOR_MEM_RX	256

/************************************************************************
 *		   BY:	 J.Masuda
 *		 DATE:	 1994/04/01
 *		 TYPE:	 DEFINE
 * VAR TO HOLD:	 N/A
 * DESCRIPTION:	 CCITT　No.1ﾁｬｰﾄ　１枚を蓄積するのに要するﾌﾞﾛｯｸ数
 ************************************************************************/
#define	CCITT_NO1_CHART_ONE_PAGE_MAX	49

/************************************************************************
 *		   BY:	 K.Watanabe ( JCS )
 *		 DATE:	 1993/04/08
 *		 TYPE:	 DEFINE
 * VAR TO HOLD:	 struct SYS_TelephoneBookData_t SYB_TelephoneBookData[SYS_TELBOOK_MAX]
 * DESCRIPTION:	 電話帳機能用
 ************************************************************************/
/*Ｌ４００ 短縮１００件のためﾃﾞﾌｧｲﾝ変更 By Y.Suzuki 1998/03/17 */
/*#define	SYS_TELBOOK_MAX		(SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX + SYS_2ND_SPEED_DIAL_MAX) */
#define	SYS_TELBOOK_MAX		(SYS_ONETOUCH_MAX + SYS_2ND_ONETOUCH_MAX + SYS_SPEED_DIAL_MAX_BKUP + SYS_2ND_SPEED_DIAL_MAX)

/************************************************************************
 * ＴＡＤ録音テーブル／タイムスタンプテーブル							*
 *	unsigned char	TAD_DSPDataTable[TAD_DSP_DATA_MAX]					*
 *	unsigned char	TAD_DSPTimeStampDataTable[TAD_DSP_DATA_MAX]			*
 *	1994/04/26		Eguchi												*
 ************************************************************************/
#define	TAD_DSP_DATA_MAX	64

/************************************************************************
 * メモリ受信するか/しないか メモリ空きブッロクしきい値(No.1ﾁｬｰﾄ1枚分)	*
 * ナンバーワンチャート１枚で６４ブロック（１ブロック２５６バイト）		*
 * ナンバーワンチャート１枚で４ブロック（１ブロック４Ｋバイト）			*
 * 1994/06/17															*
 * Y.Murata																*
 ************************************************************************/
/* #define SYS_MEMORY_EMPTY_BLOCK	(64*1024)/(4*1024) *//* By S.Kawasaki 1996/06/19 */
#if defined(DEU) || defined(EUR)	/* 1998/05/25 M.H *//* CTR21対策 */
#define	SYS_MEMORY_EMPTY_BLOCK	32
#else
#define	SYS_MEMORY_EMPTY_BLOCK	16 /* By S.Kawasaki 1996/06/19 */
#endif

/************************************************************************
 * FX 用中継指示番号													*
 * SYB_CommandFile[i].Option.OptionNumber.FX_Relay.Number[SYS_FX_RELAY_MAX]	*
 * sysmcopy.jsw参照	して追加											*
 *	中継局が１回の通信予約で指定できる宛先数							*
 *	SYS_COM_DIAL_MAX に変更												*
 * 1994/08/19															*
 * 鈴木郁二																*
 ************************************************************************/
/*#if (PRO_MAKER == FX)*/
	#define	SYS_FX_RELAY_MAX	SYS_COM_DIAL_MAX
/*#endif*/

/************************************************************************
 * FXポーリングパスワード												*
 * unsigned char SYB_FX_PollingPassword[SYS_FX_POLLING_PASSWARD_MAX]	*
 * パスワード指定した場合は、配列４にNULLをセットする					*
 * 配列０がNULLの場合は、パスワード指定なしとする						*
 * 1994/07/27															*
 * 吉川弘康																*
 ************************************************************************/
/*#if (PRO_MAKER == FX)*/
	#define	SYS_FX_POLLING_PASSWARD_MAX		5
/*#endif*/

/************************************************************************
 * ＰＩＮ番号配列ＭＡＸ													*
 * ＢＣＤコードで登録し、８桁まで入力可能。								*
 * unsigned char PIN_Number[SYS_PIN_MAX]								*
 * 1995/09/21															*
 * 川崎 真史															*
 ************************************************************************/
#define	SYS_PIN_MAX		4

/************************************************************************
 * 連続ポーリング登録件数ＭＡＸ											*
 * 1996/10/30															*
 * 松隈																	*
 ************************************************************************/
#define	SYS_CONT_POLLING_MAX	1

/************************************************************************
 * Ｆコード用データ登録桁数	1997/02/24	By T.Yamaguchi
 ************************************************************************/
#define	SUB_ADDRESS_NUMBER_MAX		11	/* ＳＵＢ  BCDで20桁、終端ｺｰﾄﾞ0xff */
#define	PASSWORD_NUMBER_MAX			11	/* ＰＷＤ  BCDで20桁、終端ｺｰﾄﾞ0xff */

/************************************************************************
 * 通信エラーモニタ件数ＭＡＸ											*
 * SYB_FaxComErrorMonitor[LINE_MAX][MONITOR_MAX]						*
 * 1997/06/23															*
 * 橘正樹																*
 ************************************************************************/
#define	SYS_FAXCOM_ERROR_LINE_MAX		2
#define	SYS_FAXCOM_ERROR_MONITOR_MAX	70

/*------------------------------*/
/* オプション仕様（２回線仕様） */
/*------------------------------*/
/* #if (PRO_MULTI_LINE == ENABLE) || (PRO_DPRAM == ENABLE)	@* Add By O.Kimoto 1996/11/08 */
	/************************************************************************
	 * オプションボード最大接続可能枚数(T.B.D.)
	 * ０    ：内蔵回線
	 * １～８：オプションボード回線
	 * トータル：９回線分
	 * By O.Kimoto 1996/11/8
	 ************************************************************************/
	#if (PRO_CLASS1_VIA_DPRAM == ENABLE)		/* 1997/02/06	By N.Sakamoto */
	#define SYS_OPTION_BOARD_MAX	9	/* change 3 to 9 by O.Kimoto 1997/06/13 */
	#else
	#define SYS_OPTION_BOARD_MAX	9
	#endif

#if (PRO_MULTI_TTI == ENABLE)	/* マルチ発信元数をデファインします。By H.Fujimura 1998/05/28 */
	/************************************************************************
	 * マルチ発信元数
	 * By H.Fujimura 1998/05/28
	 ************************************************************************/
	 #define SYS_MULTI_MAX	SYS_OPTION_BOARD_MAX
#endif

#if (PRO_LINENUMBER == TWICE_LINE)	/* 疑似２回線仕様 by T.Soneoka 1997/11/22 */
	/************************************************************************
	 * 内蔵回線最大数（疑似２回線仕様）
	 * ０    ：標準回線
	 * １～  ：拡張回線
	 * by T.Soneoka 1997/11/22
	 ************************************************************************/
	#define INTERNAL_LINE_MAX	2
#endif

	/************************************************************************
	 * 内線－＞外線発呼用アクセス番号最大桁数
	 * ＢＣＤコードで登録し、１０桁まで入力可能
	 * By O.Kimoto 1996/11/8
	 ************************************************************************/
	#define SYS_ACCESS_NUMBER_MAX	6

	/*-------------------------------------------------*/
	/* ＤＰＲメッセージキューの数  1996/11/09 Y.Murata */
	/*-------------------------------------------------*/
	#define SYS_OPTION_MESSAGE_MAX	30

	/*-------------------------------------------------*/
	/* ＤＰＲメッセージキューの数  1996/11/09 Y.Murata */
	/*-------------------------------------------------*/
	#define SYS_OPTION_MESSAGE_MAX	30

	/* Option Rom Revision 1997/3/24 Y.M */
	#define OPTION_ROM_REVISION_WORD_MAX		9

/* #endif	@* End of (PRO_MULTI_LINE == ENABLE) */

/* #if (PRO_PC_PRINT == ENABLE) && (PRO_MULTI_LINE == DISABLE)	@* Add BY H.H 1997/03/04 */
 	/*--------------------------------------------------*/
 	/* プリンターコントローラＤＰＲメッセージキューの数 */
 	/*--------------------------------------------------*/
 	#define SYS_PCR_OPTION_MESSAGE_MAX	5
/* #endif*/

/*#if (PRO_CIPHER == ENABLE)*/	/*	By Y.Suzuki 1997/06/02	*/
/**********************************************************************
*	アリロー、キー、キーのヒント、拡張キーの桁数
*	キーブック登録件数、暗号化受信件数
*	By Y.Suzuki 1997/06/02
*	UBYTE	Key[SYS_KEY_MAX];
*	UBYTE	KeyClue[SYS_KEY_CLUE_MAX];
*	UBYTE	KeyExtension[SYS_KEY_EXTENSION_MAX];
*	struct KeyTbl_t SYB_KeyData[SYS_KEY_BOOK_MAX]
*	struct SYS_CipherBoxData_t SYB_CipherBox[SYS_CIPHERBOX_MAX]
***********************************************************************/
#define	SYS_KEY_MAX				25
#define	SYS_KEY_CLUE_MAX		35
#define	SYS_KEY_EXTENSION_MAX	3
#define	SYS_KEY_BOOK_MAX		10
#define	SYS_CIPHERBOX_MAX		10
/*#endif*/

/************************************************************************
 * ＤＲＡＭバックアップテスト・エリア									*
 * unsigned char SYB_DRAM_BackupTestArea[SYS_DRAM_BACKUP_TEST_AREA_MAX]	*
 * 1997/10/31															*
 * 橘正樹																*
 ************************************************************************/
#define	SYS_DRAM_BACKUP_TEST_AREA_MAX	16

/************************************************************************
 * 拡張ＲＯＭ内容最大数													*
 * CONST UBYTE EXT_ROM_Revision[SYS_EXT_ROM_MAX][ROM_REVISION_MAX]		*
 * 1998/02/27															*
 * 渡辺一章																*
 ************************************************************************/
#define	SYS_EXT_ROM_MAX		5

/************************************************************************
 * ワープ機能最大登録数													*
 * struct SYS_SubDialData_t SYB_WarpFile[SYS_WARP_MAX]					*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
#define	SYS_WARP_MAX		5

/************************************************************************
 * ナンバーディスプレイ機能最大登録数									*
 * struct SYS_NumberDisplayTable SYB_NumberDisplay[SYS_ND_MAX]			*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
#define SYS_ND_MAX			20

/************************************************************************
 * ナンバーディスプレイ機能の着信履歴データ								*
 * extern struct SYS_NumberDisplayJournalTable SYB_NumberDisplayJournal	*
 * 1998/08/18															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_ND_JRNL_MAX		20

/************************************************************************
 * キーマクロ機能最大登録数、ステップ数、タイトル文字数					*
 *	UBYTE Step[SYS_KEYMACRO_STEP_MAX]									*
 *	UBYTE Title[SYS_KEYMACRO_TITLE_MAX]									*
 *	struct SYS_KeyMacroTable SYB_KeyMacro[SYS_KEYMACRO_MAX]				*
 * 1998/06/15															*
 * 桑原美紀																*
 ************************************************************************/
#define SYS_KEYMACRO_MAX			3		/* 最大キーマクロ数			*/
#define SYS_KEYMACRO_STEP_MAX		61		/* 最大ステップ数 + NULL	*/
#define SYS_KEYMACRO_TITLE_MAX		37		/* タイトル36文字 + NULL	*/

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/05/13 Y.Murata */
/*
 * ミノルタテストプリント管理テーブルＭＡＸ
*/
#define	SYS_MINOLTA_TEST_FUNC_MAX		15
#endif

#if (PRO_SGP_TEST_ROM == ENABLE) /* by S.Wang 98/07/24 */
/* シンガポール市場調査レポート最大記録数 */
#define SYS_SGP_REPORT_MAX				100
#endif

#if (PRO_PRINT_TYPE == THERMAL_TRANS)	/* 1999/4/21 K.Kawata*/
#define SYS_ROM_SWITCH_MAX	50
#endif

#endif
