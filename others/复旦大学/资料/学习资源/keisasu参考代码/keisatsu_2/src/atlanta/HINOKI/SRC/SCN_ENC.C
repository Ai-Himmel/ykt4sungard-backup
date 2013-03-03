/*
 *	@(#)%W%
 *	FileName:	/home2/prj/Eva/Src/scn/scn_enc.c
 *	Create:	Tue Jan 13 14:20:19 1998	by	ishiyama
 *	Description:
 *		原稿蓄積エンコードタスク
 *	Change Log:
 *		
 */
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\message.h"
#include "\src\atlanta\define\mem_pro.h"
#include "\src\atlanta\define\apl_msg.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\define\unisw_e.h"
#include "\src\atlanta\define\sys_stat.h"

#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#endif
#if (PRO_MODEM == R288F)
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
		#include "\src\atlanta\mdm\fm336\ext_v\mdm_data.h"
	#else
		#include "\src\atlanta\mdm\r288f\define\mdm_def.h"
		#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"	/* T.3.1 by O.Kimoto 1999/02/10 */
	#endif
#endif
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#include "\src\atlanta\mdm\pana\ext_v\mdm_data.h"
#endif

#if (PRO_CPU_VERSION == SH7043_A)
	#include "\src\cpu\sh7043_a\scd\define\scd.h"
	#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#else
	#include "\src\atlanta\scd\define\scd.h"
	#include "\src\atlanta\scd\define\scdpro.h"
#endif
#include "\src\atlanta\sh7043\ext_v\extv_mbx.h"
#include "\src\cpu\sh7043_a\irom\ext_v\extv_sem.h"	/* T.3.1 by O.Kimoto 1999/02/10 */



#include "\src\atlanta\hinoki\define\scn_pro.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\hinoki\ext_v\scdc_dat.h"

#include "\src\atlanta\ext_v\fcm_data.h"
#include "\src\atlanta\define\fcm_def.h"

#include "\src\atlanta\define\mntsw_h.h"

/*
 *	Name:	Store Page Task
 *	Create:	Tue Jan 13 15:35:43 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scanner.h"
 *		void	StorePageTask(void);
 *	Description:
 *		1ページをエンコードし、画像メモリに蓄積する
 *		1)コーデックパラメータを設定
 *		2)Scanner Page Buffer を読んで,エンコードし画像メモリに蓄積
 *		3)停止の指示(大域変数)があれば,RTC を付加し、終了。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	StorePageTask(void)
{
	MESSAGE_t	StorePageTaskMsg;			/* 親タスクへのメッセージ */
	WORD	cdc_status;		/* ＲＴＣの書き込み結果 */
	UWORD	ret_code;
	UWORD	wait_line;		/* 1999/01/06 by T.Soneoka */
	UBYTE	is_file_enable;	/* 蓄積ファイル有効/無効(ICHOUで追加) */

	UWORD	start_timer;	/* タスクウェイトを１ラインエンコード時間より設定する 1999/03/09 by T.Soneoka */
	UWORD	tsk_wait_timer;	/* タスクウェイトを１ラインエンコード時間より設定する 1999/03/09 by T.Soneoka */

	is_file_enable = FALSE;	/** 蓄積ファイル無効 */

	/*----------------------------------------------------------*/
	/** 蓄積原稿の消去											*/
	/**	 今から蓄積しようとしている原稿の消去を念の為行います。 */
	/*----------------------------------------------------------*/
	/*	ICHOUではJAMリカバー時とFBSメモリ送信時に、
	**	同じStoreNoでつづきのPageNoから再起動されるので、
	**	1ページ目のときだけ、原稿の消去をする。
	**	(念のための消去なので、出来ればこの処理を削除したい)
	*/
	if (SYS_DocumentStorePage == 1) {
		MEM_ClearDocAndFATArea( SYS_DocumentStoreItem, SYS_DocumentStoreNo, SYS_DocumentStoreBoxNumber);
	}

	if (SYS_MultiProgramFlag == 1) {
		/** DRAM１ページ・マルチオープン（０以外の戻り値はメモリオーバー */
		if (ret_code = MEM_MultiWriteOpen(&SCN_StoreData, &SCN_ExecData)) {
			/** Memory Overflow, ret_code:0xFC(Index Over),0xFE(Block Over) */
			MEM_ClearBreak(&SCN_IndexData); /** 蓄積途中のファイルをクリア */
#if (0) /* 1998/12/17 by T.Soneoka */
**			StorePageTaskMsg.Message = MSG_SCN_DOCSTORE_MEM_OVER;
#else
			StorePageTaskMsg.Message = MSG_DOCSTORE_MEMORY_OVER;
#endif
			SCN_ADF_MotorStopRequest = ADF_MOTOR_MEMORY_OVER;	/* 停止要求を出す */
		}
	}
	else {
		if (ret_code = MEM_WriteOpen(&SCN_StoreData, &SCN_ExecData)) {
			/** Memory Overflow, ret_code:0xFC(Index Over),0xFE(Block Over) */
			MEM_ClearBreak(&SCN_IndexData); /** 蓄積途中のファイルをクリア */
#if (0) /* 1998/12/17 by T.Soneoka */
**			StorePageTaskMsg.Message = MSG_SCN_DOCSTORE_MEM_OVER;
#else
			StorePageTaskMsg.Message = MSG_DOCSTORE_MEMORY_OVER;
#endif
			SCN_ADF_MotorStopRequest = ADF_MOTOR_MEMORY_OVER;	/* 停止要求を出す */
		}
	}

	if (ret_code == MEM_OK) {
		/* ソフトコーデック初期化 */
		EncCodecPageStatus = CDC_READY;
		SCDC_SoftEncodeInitial();

		start_timer = SYS_GeneralTimer;	/* タスクウェイトを１ラインエンコード時間より設定する 1999/03/09 by T.Soneoka */

		EncCodecPageStatus = CDC_CONTINUE;			/**	初期化 By Y.Suzuki 1997/09/19	*/
		/*
		**	Page 終了 または 終了要求があるまでエンコード
		*/
		while (1) {
			/* ストップキーチェック */
			if (SYS_DocumentStoreStopSwitch()) {
				StorePageTaskMsg.Message = MSG_DOCSTORE_STOPSW_ON;
				break;
			}

			if (EnableToReadScanPageMem()) {

				SYS_StorePause = FALSE;	/* 表示用 1999/1/14 by T.Soneoka */

				/* ＲＬバッファのポインタースワップ */
				EncodeTmp_buf = EncodeA_buf;
				EncodeA_buf = EncodeB_buf;
				EncodeB_buf = EncodeTmp_buf;

#if (0) /* ScanPageMemReadLineはEncodeOneLineの後でインクリメントするように変更します 1998/11/13 by T.Soneoka */
**				(void)GetLineAddress4ReadScanPageMem();
#endif

				EncodeOneLine();
				(void)GetLineAddress4ReadScanPageMem();
				DecScanPageMemReadableLine();
				if((EncCodecPageStatus == CDC_CONTINUE) || (EncCodecPageStatus == CDC_RTC_DET)) {
					ScanningTotalLine++;
				} else {
					StorePageTaskMsg.Message = MSG_DOCSTORE_MEMORY_OVER;
					break;
				}


/* タスクウェイトを１ラインエンコード時間より設定する 1999/03/10 by T.Soneoka */
#if (0)
**					/* エンコード中に他のタスクに処理がスイッチしない。
**					** エンコード中の処理を確認すると、モニターがほとんど呼ばれていない。（wai_sem()/sig_sem()）
**					** よって、ここで、１回／１０ライン毎に１０ｍｓのウエイトを入れます。
**					** Ａ４換算で、約１．４秒のウエイトとなりますが、キーが効かないことを考えると、
**					** 問題ないでしょう！ 
**					** By O.Kimoto 1998/12/16
**					*/
**	#if (0)
**	**				if ((ScanningTotalLine % 10) == 0) {
**	**					wai_tsk((UWORD)((SYB_MachineUniqSwitch[UNIQ_SW_E3] & IU_SCDC_WAIT_TIME) + 2));
**	**				}
**	#else
**
**
**					/* ＤＵＡＬ動作で、ＦＣＭ、ＮＣＵ、ＰＲＴが裏で走っているときはウェイトおおめに入れます 1999/01/06 by T.Soneoka */
**	/*
**	** ＦＣＭ中のとき、画データ送受信中のみエンコードウェイトを待機状態と同じにします
**	** 1999/03/09 by T.Soneoka
**	*/
**	#if (1)
**					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
**						wait_line = 1;
**	#else
**					if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
**						if ((((FaxComPhaseStatus == FAX_TX_PH_C_PIX) || (FaxComPhaseStatus == FAX_TX_PH_C_AFTER_PIX))
**							&& (ModemControl.UsedCount > 5))
**						|| ((FaxComPhaseStatus == FAX_RX_PH_C_PIX)
**							&& (ModemControl.UsedCount < 5))) {
**							wait_line = 10;
**						} else {
**							wait_line = 1;
**						}
**	#endif
**
**
**	#if (0) /* リストの罫線・文字が伸びる不具合、マルチコピープリントも入れ忘れているので追加 1999/02/23 by T.Soneoka */
**	**				} else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_IMAGE_PRINT) {
**	#else
**					} else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT | SYS_MULTI_COPY | SYS_LIST_PRINT)) {
**	#endif
**						wait_line = 2;
**					} else {
**						wait_line = 10;
**					}
**					if ((ScanningTotalLine % wait_line) == 0) {
**						wai_tsk((UWORD)((SYB_MachineUniqSwitch[UNIQ_SW_E3] & IU_SCDC_WAIT_TIME) + 2));
**					}
**	#endif
#else
					tsk_wait_timer = 0;
					if (SYB_MachineUniqSwitch[UNIQ_SW_E3] & IU_SCDC_WAIT_INTERVALTIME) {
						if 	((SYS_GeneralTimer - start_timer) >= ((SYB_MachineUniqSwitch[UNIQ_SW_E3] & IU_SCDC_WAIT_INTERVALTIME) >> 4)) {
							start_timer = SYS_GeneralTimer;
							tsk_wait_timer = ((SYB_MachineUniqSwitch[UNIQ_SW_E3] & IU_SCDC_WAIT_TIME) + 1);
						}
					} else {
						if (SYS_MachineStatus[SYS_MACHINE_STATUS] & (SYS_IMAGE_PRINT | SYS_MULTI_COPY | SYS_LIST_PRINT)) {
							if 	((SYS_GeneralTimer - start_timer) >= 1) {	/* １０ｍｓ間隔でウェイト */
								start_timer = SYS_GeneralTimer;
								tsk_wait_timer = 1; /* １０msウェイトする */
							}
						} else if (SYS_MachineStatus[SYS_MACHINE_STATUS] & SYS_FAXCOM) {
							if 	((SYS_GeneralTimer - start_timer) >= 3) {	/* ３０ｍｓ間隔でウェイト */
								start_timer = SYS_GeneralTimer;
								tsk_wait_timer = 1; /* １０msウェイトする */
							}
						} else if ((SYS_GeneralTimer - start_timer) >= 15) {	/* １５０ｍｓ間隔でウェイト */
							start_timer = SYS_GeneralTimer;
							tsk_wait_timer = 2; /* ２０msウェイトする */
						}
					}
					if (tsk_wait_timer) {
						wai_tsk(tsk_wait_timer);
					}
#endif

			} else {
				SYS_StorePause = TRUE;	/* 表示用 1999/1/14 by T.Soneoka */

				/* 原稿がスタンプ位置にきていたら読み取り完了とします */
#if (0) /* 1998/11/17 by T.Soneoka */
**				if ((CurrentPage->Position >= DOC_POS_MOVE_TO_PUSH_STAMP) ||  (SCN_DocumentChanged == TRUE)) {
#else
				if (SCN_DocumentChanged == TRUE) {
#endif
					/* ＲＴＣコードをセット */
#if (0)
** 					/* T.3.1 エラー 
** 					** 最終の画データがブロックの最終バイトだった場合、ＲＴＣをセットする時に、次のブロックをＧｅｔしてから
** 					** ＲＴＣをセットしているが、その時の大域変数も更新されている。
** 					** しかし、そのことを考慮せずにＷｒｉｔｅＣｌｏｓｅを行っていたためにＲＴＣ無しの原稿を蓄積してしまって
** 					** いた。
**					** by O.Kimoto 1999/02/10
**					*/
** 					cdc_status = WriteRtcToMem(&EncodeData);
#else				
					wai_sem(semno.SCDC_DRAM_Access);
					
					CMN_DisableInterrupt();
					EncMemoryExecBkupData = MemoryExecData;
					MemoryExecData = SCN_ExecData;
					CMN_EnableInterrupt();

					cdc_status = WriteRtcToMem(&EncodeData);

					CMN_DisableInterrupt();
					SCN_ExecData = MemoryExecData;
					MemoryExecData = EncMemoryExecBkupData;
					CMN_EnableInterrupt();	/* For Debug By O.Kimoto 1998/12/16 */

					/* CMN_EnableInterrupt(); Sig_semの中で割り込み解除しているのでここでは許可しない。 */
					sig_sem(semno.SCDC_DRAM_Access);
#endif

					/* メモリオーバーのチェック */
					if(cdc_status == RX_MEM_OVER) {
						EncCodecPageStatus = CDC_MEM_OVER;
					}
					else {
						StorePageTaskMsg.Message = MSG_DOCSTORE_OK;
						is_file_enable = TRUE;	/** 蓄積ファイル有効 */
						break;
					}
				}
				wai_tsk(50/10);
			}
		} /* for end */

		/* ファイルのクローズ */
		/* 蓄積OK以外でもファイルが有効なら確定する  1996/12/16 */
		if (is_file_enable) {	/** 蓄積ページが有効 */
			/*
			**	オープンファイルのクローズ
			*/
			if (SYS_MultiProgramFlag == 1) {
				MEM_MultiWriteClose(&SCN_ExecData, SCN_TotalEncodeLine);
			}
			else {
				MEM_WriteClose(&SCN_ExecData, SCN_TotalEncodeLine);
			}
		}
		else {
			MEM_ClearBreak( &SCN_IndexData );	/** 無効ページはここで削除 */
		}
	}
	SleepDocStoreSubTask = TRUE;		/* 兄弟タスクを停止し、親タスクに制御を移すため */
	snd_msg(mbxno.SCN_Task, &StorePageTaskMsg);
	wai_tsk(0xffff);
}


/*
 *	Name:	Exit Store Page Task
 *	Create:	Thu Feb 19 17:14:03 1998	by	ishiyama
 *	Synopsis:
 *		#include	"scn_task.h"
 *		void	ExitStorePageTask(void);
 *	Description:
 *		Store Page Task 終了関数
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	ExitStorePageTask(void)
{
#if (0)
** 	/* ファイルのクローズ */
** 	IndexWriteClose(&StorePageMemHandle, ScanningTotalLine, 0);
#endif
	exi_tsk();
}


/*
 *	Name:	Initialize Store Page Resource
 *	Create:	Thu Feb 19 15:30:16 1998	by	ishiyama
 *	Synopsis:
 *		#inlcude	"scn_task.h"
 *		void	InzStorePageResource(void);
 *	Description:
 *		1ページ蓄積タスクに必要なリソースの初期化
 *		ページ途中で、親タスクから Delete されたとき、
 *		Memory などのリークを防ぐため、Create される前にコールすること。
 *	Return Value:
 *		void
 *	Change Log:
 *		
 */
void	InzStorePageResource(void)
{
	ScanningTotalLine = 0;
#if (0)
	/* Memory Index Clear */
	InzIndexNo(&StorePageMemHandle);
#endif
}

