/************************************************************************
*				By : NOBUKO
*			  Date : Wed 05 Jan. 1994 (\SRC\RICE\SRC\MEMREAD.C)
*		 Copy Date : Tue 12 Sep. 1995
*		           : 1996/10/21 From \src\kobe\anzu\src\ By M.Kotani
*		 File Name : MEMREAD.C
*	   Module Name :
*			1. UBYTE MEM_ReadOpen(struct MEM_IndexData_t *IndexP, struct MEM_ExecData_t *ExecP)
*			2. void MEM_Read(UBYTE Item, struct MEM_ExecData_t *ExecP)
*			3. UWORD MEM_ReadGetNextBlockNo(UWORD BlockNo)
*			4. UDWORD MEM_CalculateDMAAddress(UWORD BlockNo)
*			5. UBYTE *MEM_CalculateSoftAddress (UWORD)
*------------------------------------------------------------------------
*            Date : Jan.17,1996
*                   S.Kawasaki
*         Comment : プリンター／モデムに使用されている。
*                 : この状態で使用可能
*************************************************************************/
#include "\src\atlanta\define\product.h"			/* 条件コンパイルのため */
#include "\src\atlanta\define\cmn_pro.h"			/* 標準関数・プロトタイプ */
#include "\src\atlanta\define\mon_pro.h"			/* モニタ・プロトタイプ */
#include "\src\atlanta\sh7043\define\def_semn.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\sh7043\ext_v\extv_sem.h"	/* 1997/12/16 Y.M */
#include "\src\atlanta\define\mem_pro.h"			/* メモリ管理・プロトタイプ */
#include "\src\atlanta\ext_v\mem_data.h"			/* メモリ管理使用ヘッダ */
#include "\src\atlanta\ext_v\sys_data.h"			/* SYS_MachineStatus[] */
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\sys_stat.h"			/* SYS_MachineStatus[] */
#include "\src\atlanta\define\dma_pro.h"
#include "\src\atlanta\define\dma_def.h"		/* V53DMA使用ヘッダ */
#include "\src\atlanta\define\dma_blk.h"		/* V53DMA使用ヘッダ */
#include "\src\atlanta\define\mntsw_a.h"

#if (PRO_EXT_DMAC == ENABLE) /* 1998/01/29 by H.Kubo */
#include "\src\atlanta\define\mntsw_c.h"
#endif

#include "\src\atlanta\sh7043\define\def_evtn.h"

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/23 Y.Murata for KAKI */
 #if (PRO_MODEM == ORANGE3)
	#include "\src\atlanta\mdm\orange\ext_v\mdm_data.h"
 #else
	#include "\src\atlanta\mdm\r288f\ext_v\mdm_data.h"
 #endif
#endif


#define NO			0
#define YES			1
#define V53_DMATC	5

#if (0) /* ext_v\bkupram.h で宣言してるので削除 S.Fukui June 19,1998  */
extern	UBYTE SYS_MemorySwitch[];	/* Dec.15,1994 */
#endif

static UWORD  read_buffer_point = 0;
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[メモリ・リード・オープン]
	function	:[
		1. 蓄積されている原稿を読みだす際の指定を行ないます
	]
	return		:[
		#define MEM_NO_INDEX	指定原稿なし
		#define MEM_OK			読みだし原稿指定OK
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/15 Y.Murata for KAKI */

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui June 19,1998  */
UWORD MEM_ReadOpenFlsRom (struct MEM_IndexData_t *IndexP,		/* 読みだし原稿のインデックスの内容を指示します */
						  struct MEM_ExecData_t *ExecP)			/* 読みだし状況格納領域を指定します */
 #else
UWORD MEM_ReadOpen (struct MEM_IndexData_t *IndexP,		/* 読みだし原稿のインデックスの内容を指示します */
					struct MEM_ExecData_t *ExecP)			/* 読みだし状況格納領域を指定します */
 #endif
{
	UWORD index_no;											/* MEM_IndexTable[]上のポインタ */

	/** 割込み禁止期間開始 */
	wai_sem(semno.MEM_WriteOpenSem);

	ExecP -> IndexNo1 = MEM_NO_INDEX;								/* 初期化します */
	ExecP -> IndexNo2 = MEM_NO_INDEX;								/* 初期化します */
	ExecP -> ExecBlockNo = MEM_NO_INDEX;							/* 初期化します */
	ExecP -> NextBlockNo = MEM_NO_INDEX;							/* 初期化します */

																	/* 該当インデックスを確定します */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブル内を検索し、指定インデックスを捜します  */
		if (((MEM_IndexTable[index_no].Item & ~MEM_NOW_STORING) == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */

			ExecP -> IndexNo1 = index_no;							/* 読みだしインデックスNoをセットします */
			ExecP -> ExecBlockNo = MEM_IndexTable[index_no].StartBlockNo;	/* 読みだしブロックNoをセットします */
			break;													/* 該当インデックスが見つかったらインデックス・テーブルの検索は終了します */
		}
	}

	if (ExecP -> IndexNo1 == MEM_NO_INDEX) {						/* 該当インデックスがなかったら */
		sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}

	read_buffer_point = ExecP -> ExecBlockNo;

	sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	return (MEM_OK);												/* 読みだし原稿の指定が正常終了したら MEM_OK を返します */
}

#else

 #if (PRO_EX_CLASS1 == ENABLE)	/* 拡張ＲＯＭからの参照ルーチン S.Fukui June 19,1998  */
UWORD MEM_ReadOpenFlsRom (struct MEM_IndexData_t *IndexP,		/* 読みだし原稿のインデックスの内容を指示します */
						  struct MEM_ExecData_t *ExecP)			/* 読みだし状況格納領域を指定します */
 #else
UWORD MEM_ReadOpen (struct MEM_IndexData_t *IndexP,		/* 読みだし原稿のインデックスの内容を指示します */
					struct MEM_ExecData_t *ExecP)			/* 読みだし状況格納領域を指定します */
 #endif
{
	/* まだきっちりできてへんで */
	UWORD index_no;											/* MEM_IndexTable[]上のポインタ */

	/** 割込み禁止期間開始 */
	/*CMN_DisableInterrupt(); WRITE_OPEN_SEM 1997/12/16 Y.Murata */		/* By Y.Suzuki 1997/05/07 */
	wai_sem(semno.MEM_WriteOpenSem);

	ExecP -> IndexNo1 = MEM_NO_INDEX;								/* 初期化します */
	ExecP -> IndexNo2 = MEM_NO_INDEX;								/* 初期化します */
	ExecP -> ExecBlockNo = MEM_NO_INDEX;							/* 初期化します */
	ExecP -> NextBlockNo = MEM_NO_INDEX;							/* 初期化します */

																	/* 該当インデックスを確定します */
	for (index_no = 0; index_no < MEM_INDEX_TABLE_MAX; index_no++) {/* 全インデックス・テーブル内を検索し、指定インデックスを捜します  */
		if ((MEM_IndexTable[index_no].Item == IndexP -> Item) &&	/* MEM_IndexTable[]上のItemと指定されたItemが一致していて */
			(MEM_IndexTable[index_no].No   == IndexP -> No)	  &&	/* MEM_IndexTable[]上のNoと指定されたNoが一致していて */
/* #if(PRO_F_CODE == ENABLE) */
			((MEM_IndexTable[index_no].BoxNumber   == IndexP -> BoxNumber) ||	/* MEM_IndexTable[]上のBoxNUmberと指定されたNoが一致している */
			 (IndexP -> BoxNumber == MEM_IGNORE_BOX_NUMBER))  &&				/* またはBoxNumberを無視 */
/* #endif */
			(MEM_IndexTable[index_no].Page == IndexP -> Page)) {	/* MEM_IndexTable[]上のPageと指定されたPageが一致していたら */
			ExecP -> IndexNo1 = index_no;							/* 読みだしインデックスNoをセットします */
			ExecP -> ExecBlockNo = MEM_IndexTable[index_no].StartBlockNo;	/* 読みだしブロックNoをセットします */
			break;													/* 該当インデックスが見つかったらインデックス・テーブルの検索は終了します */
		}
	}

	if (ExecP -> IndexNo1 == MEM_NO_INDEX) {						/* 該当インデックスがなかったら */
		sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
		return (MEM_NO_INDEX);										/* MEM_NO_INDEX を返します */
	}

	read_buffer_point = ExecP -> ExecBlockNo;

	/*CMN_EnableInterrupt(); WRITE_OPEN_SEM */		/* 1997/08/18 M.Kotani */
	sig_sem(semno.MEM_WriteOpenSem);	/* WRITE_OPEN_SEM 1997/12/16 Y.Murata */
	return (MEM_OK);												/* 読みだし原稿の指定が正常終了したら MEM_OK を返します */
}

#endif	/* End of (PRO_QUICK_TX_TEST == ENABLE) */

#if (PRO_CPU == SH7043)
	#if (PRO_SCN_CODEC_TYPE == MN86063) || (PRO_SCN_CODEC_TYPE == MN86064) \
	|| (PRO_COM_CODEC_TYPE == MN86063) || (PRO_COM_CODEC_TYPE == MN86064) \
	|| (PRO_SCN_CODEC_TYPE == IDP301)
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[蓄積原稿の読みだし]
	function	:[
		1.
	]
	return		:[
		#define MEM_OK			蓄積原稿の読みだし正常終了
		#define MEM_STOP_SW		蓄積原稿の読み出し中にSTOP_SW押下
	]
	common		:[なし]
	condition	:[]
	comment		:[
		DRAM読み出し時のDMAで､通信の時は通常のV53 DMAを使用
		ﾌﾟﾘﾝﾄの時は､V53 DMA の ｵｰﾄｲﾆｼｬﾗｲｽﾞ機能を使用
	]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
UDWORD DebugDMAAddress = 0;
UBYTE MEM_Read (UBYTE Type,						/* 読みだし先の指定(MODEM or PRINTER) */
				struct MEM_ExecData_t *ExecP)		/* 読み出し中のデータの格納エリア */
{
	UBYTE end_status;
	struct DMA_Data_t MEM_ReadDMA;
#if (PRO_CPU == SH7043) /* T.Nose 1996/04/24 */
	UWORD word_register_value;
#endif

	UDWORD chk_rd_dma_address;	/* Add By O.Kimoto 1998/05/09 */

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/23 Y.Murata for KAKI */
	UWORD timer;
#endif

	chk_rd_dma_address = 0;	/*  By O.Kimoto 1998/05/09 */

	if (Type == MEM_PRINTER) {				/** 呼び元がPRINTER */
		MEM_DMAEndStatus &= ~MEM_PRINT_PAGE_END;
		end_status = MEM_PRINT_PAGE_END;
		MEM_ReadDMA.Channel = DMA_DRAM_PRNCDC_CH;								/** DMA Channel指定 */
	}
	else {									/** 呼び元がMODEM */
		MEM_DMAEndStatus &= ~MEM_TX_PAGE_END;
		end_status = MEM_TX_PAGE_END;
		MEM_ReadDMA.Channel = DMA_DRAM_COMCDC_CH;								/** DMA Channel指定 */
	}
		/** V53 DMA Initialize */


#if (0)
** 	/* Ｖ８５０に於いて、フィールドでプリント中にリセット発生という不具合が出た。
** 	** 原因調査の結果、以下の処理を追加した為の二次障害であることがわかった。
** 	** 
** 	**        ＦＡＴチェーンの最終ブロックのまた最後の方にＲＴＣがある場合に、
** 	**        最終ブロックのＤＭＡが終了した時点で、次のブロックはＥＯＰブロックの為
** 	**        ＤＭＡを止めて、メモリエラーにしていた（これが間違いでした！）
** 	**        
** 	**        従来は、次のブロックがＥＯＰブロックであっても、とりあえず１回はＤＭＡを実行し
** 	**        （但し、この時のＤＭＡアドレスはデタラメです）次のＴＣが発生したら、もうＤＭＡすべき
** 	**        ブロックは存在しないということでメモリＯＫで戻っていました。
** 	**
** 	**        修正としては、従来方式に戻します。
** 	**
** 	** by O.Kimoto 1998/10/31
** 	*/
** 	*/
** #if (0)
** ** 	/* MEM_CalculateDMAAddress()の戻り値はエラーの可能性がある。しかし、それを判断せずにＤＭＡアドレスを
** ** 	** セットしており、それは非常にまずい。
** ** 	** ということで上記関数の戻り値を判断しエラーの場合はメモリエラーで終わります。
** ** 	** By O.Kimoto 1998/05/09
** ** 	*/
** ** 	MEM_ReadDMA.SrcAddress = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
** #else
** 	chk_rd_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
**  #if (PRO_FBS == DISABLE)	/* ポプラＢで舞子チャートFCOT時リセットがかかる。調査完了まで従来パスに戻す。S.Fukui Jul.14,1998 */
** 	if (chk_rd_dma_address == (UDWORD)MEM_BLOCK_OVER) {
** 		DMA_RequestMask(MEM_ReadDMA.Channel);
** 		return ((UBYTE)MEM_NG);
** 	}
**  #endif
** 	MEM_ReadDMA.SrcAddress = chk_rd_dma_address;
** #endif
#else
	chk_rd_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);	/** DMA開始アドレス指定 */
	MEM_ReadDMA.SrcAddress = chk_rd_dma_address;
#endif

	MEM_ReadDMA.Counter = (UWORD)(MEM_BLOCK_SIZE / 2);						/** 転送WORD数(N-1)指定 １を引かなくしたM.Kotani1996/12/17*/
	MEM_ReadDMA.Unit = DMA_WORD_TRANSFER;										/** WORD転送指定 */
	MEM_ReadDMA.Direction = DMA_MEMORY_TO_IO;									/** 転送方向指定 */

	DMA_SetupDMAU(&MEM_ReadDMA);												/** DMAU Setup */

	while ((MEM_DMAEndStatus & end_status) != end_status) {						/** MEM_DMAEndStatusが何も立っていない場合(READのときは立ちません) */
#if (PRO_PRINT_TYPE == LASER)	/* ポプラはこの関数の中で監視しない By M.Tachibana 1997/04/28 */
		/** STOP SW の監視 読みだしを止めるかどうか */
		if (Type == MEM_PRINTER) {
			if ((SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_MULTI_COPY) ||
				(SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] & SYS_STOP_IMAGE_PRINT)) {
/*				SYS_MachineStatus[SYS_STOP_SWITCH_STATUS] &= ~(SYS_STOP_IMAGE_PRINT + SYS_STOP_MULTI_COPY); */
				DMA_RequestMask(MEM_ReadDMA.Channel);
				return ((UBYTE)MEM_STOP_SW);
			}
			/* 通信時のSTOP_SWの監視はMODEMの中でやっているのでここでは必要ありません */
		}
#endif

		/** 割込み禁止期間開始 */
		CMN_DisableInterrupt();
		DMA_RequestEnable(MEM_ReadDMA.Channel);				/** DMA Start (DRAM -> CODEC) */
		/** DMATCのウエイト */
		if (Type == MEM_PRINTER) {
			wai_evt(EVT_DMA_DRAM_PRNCDC);
			#if (PRO_EXT_DMAC == ENABLE) /* 1997/11/10 */
				CMN_DisableInterrupt();
				outp(DMAU_DCH,0x01);
				/* if (0xffff == inp(DMAU_DBC_DCC_WORD)) [ T.Nose 1996/04/03 */
				/* if (0xffff == inpw(DMAU_DBC_DCC_WORD)) [ T.Nose 1996/04/24 */
				word_register_value = (UWORD)inp(DMAU_DBC_DCC_WORD - 1);
				word_register_value <<= 8;
				word_register_value += (UWORD)inp(DMAU_DBC_DCC_WORD);
				if (0xffff == word_register_value) {
					/* 正常 */
				}
				else { /* 不正ＤＭＡ ＴＣ */
					SYB_MaintenanceSwitch[MNT_SW_A7] |= DMA_FAT_ERROR_BIT;
				}
				CMN_EnableInterrupt();
			#else
				word_register_value = DMA_CheckDMA_Counter(DMA_DRAM_PRNCDC_CH);
				if (0x0000 == word_register_value) {
					/* 正常 */
				}
				else { /* 不正ＤＭＡ ＴＣ */
					SYB_MaintenanceSwitch[MNT_SW_A7] |= DMA_FAT_ERROR_BIT;
				}
			#endif
		}
		else if (Type == MEM_MODEM) {
			wai_evt(EVT_DMA_DRAM_COMCDC);
			/** 割込み禁止期間終了 */
#if 0 /* (PRO_EXT_DMAC == ENABLE) /@ 1997/12/02 by H.Kubo */ /* Deleted by H.Kubo 1998/07/08 */
@@			CMN_DisableInterrupt();
@@			word_register_value = DMA_CheckDMA_Counter(DMA_DRAM_COMCDC_CH);
@@			if (0 == word_register_value) {
@@				/* 正常 */
@@			}
@@			else { /* 不正ＤＭＡ ＴＣ */
@@
@@				SYB_MaintenanceSwitch[MNT_SW_C1] |= MEM_MODEM_DMA_TC_ILLEGAL;
@@#if (PRO_MODEM == R288F) /* #if is added by H.Kubo 1998/01/30 */
@@				/* カウンタが終了しておらず、外部 DREQ がまだあるときは、
@@				** DMA 転送を継続する。
@@				*/
@@				if (DMA_CheckDreq(MEM_ReadDMA.Channel)) {
@@					continue;
@@				}
@@#endif
@@			}
@@			CMN_EnableInterrupt(); /* added by H.Kubo 1998/0122 これいれるの忘れてました。*/
#endif /* 0 */ /* (PRO_EXT_DMAC == ENABLE) */
		}
		else { /* ここに来たら使い方がおかしい。*/
			DMA_RequestMask(MEM_ReadDMA.Channel);
			return ((UBYTE)MEM_NG);
		}	

		if (ExecP -> ExecBlockNo == MEM_EOP_BLOCK) {		/** 読みだしたブロックが EOP */
			/** 読みだし終了 */
			DMA_RequestMask(MEM_ReadDMA.Channel);
			return ((UBYTE)MEM_OK);
		}

#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/16 Y.Murata for KAKI */
		if (Type == MEM_MODEM) {
			timer = 0;
			while (1) {
				if ((MEM_ReadGetNextBlockNo(ExecP -> ExecBlockNo)) & MEM_STORING_BLOCK) {
					wai_tsk(1);
					timer++;
					if (timer > 3000) {	/* ３０秒 */
						/*
						 * ここにきたらBUGです
						 * ３０秒間で４ｋのデータが溜まらない なんてことは無いと思うけど。
						 * ＥＣＭの場合ＰＩＸのフレーム間フラブはＴ１タイマー分出せるます。
						 * Ｇ３の場合ＭＲ送信になるから蓄積より通信の方が遅いのでここでは考慮しません。
						*/
						MDM_MemReadStatus = 1;
						outp((unsigned long)0,(UBYTE)0);	/* WriteProtectError for ICE */
						DMA_RequestMask(MEM_ReadDMA.Channel);
						return ((UBYTE)MEM_NG);
					}
				}
				else {
					break;
				}
			}
			ExecP -> ExecBlockNo = MEM_ReadGetNextBlockNo(ExecP -> ExecBlockNo);
		}
		else {
			ExecP -> ExecBlockNo = MEM_ReadGetNextBlockNo(ExecP -> ExecBlockNo);
		}
#else
		/** 次の読みだしブロックの獲得、更新 */
		ExecP -> ExecBlockNo = MEM_ReadGetNextBlockNo(ExecP -> ExecBlockNo);
#endif
		/** 読みだしブロックのアドレス算出 */

#if (0)
** 	/* Ｖ８５０に於いて、フィールドでプリント中にリセット発生という不具合が出た。
** 	** 原因調査の結果、以下の処理を追加した為の二次障害であることがわかった。
** 	** 
** 	**        ＦＡＴチェーンの最終ブロックのまた最後の方にＲＴＣがある場合に、
** 	**        最終ブロックのＤＭＡが終了した時点で、次のブロックはＥＯＰブロックの為
** 	**        ＤＭＡを止めて、メモリエラーにしていた（これが間違いでした！）
** 	**        
** 	**        従来は、次のブロックがＥＯＰブロックであっても、とりあえず１回はＤＭＡを実行し
** 	**        （但し、この時のＤＭＡアドレスはデタラメです）次のＴＣが発生したら、もうＤＭＡすべき
** 	**        ブロックは存在しないということでメモリＯＫで戻っていました。
** 	**
** 	**        修正としては、従来方式に戻します。
** 	**
** 	** by O.Kimoto 1998/10/31
** 	*/
** #if (0)
** ** 		/* MEM_CalculateDMAAddress()の戻り値はエラーの可能性がある。しかし、それを判断せずにＤＭＡアドレスを
** ** 		** セットしており、それは非常にまずい。
** ** 		** ということで上記関数の戻り値を判断しエラーの場合はメモリエラーで終わります。
** ** 		** By O.Kimoto 1998/05/09
** ** 		*/
** ** 		DebugDMAAddress = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);
** ** 		DMA_SetDMA_Address(MEM_ReadDMA.Channel, DMA_MEMORY_TO_IO, MEM_CalculateDMAAddress(ExecP -> ExecBlockNo));
** #else
** 		chk_rd_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);
**  #if (PRO_FBS == DISABLE)	/* ポプラＢで舞子チャートFCOT時リセットがかかる。調査完了まで従来パスに戻す。S.Fukui Jul.14,1998 */
** 		if (chk_rd_dma_address == (UDWORD)MEM_BLOCK_OVER) {
** 			DMA_RequestMask(MEM_ReadDMA.Channel);
** 			return ((UBYTE)MEM_NG);
** 		}
**  #endif
** 		DMA_SetDMA_Address(MEM_ReadDMA.Channel, DMA_MEMORY_TO_IO, chk_rd_dma_address);
** #endif
#else
		chk_rd_dma_address = MEM_CalculateDMAAddress(ExecP -> ExecBlockNo);
		DMA_SetDMA_Address(MEM_ReadDMA.Channel, DMA_MEMORY_TO_IO, chk_rd_dma_address);
#endif



		DMA_SetDMA_Counter(MEM_ReadDMA.Channel, MEM_ReadDMA.Counter);
	}

	/** ここにきたらBUGです */
	DMA_RequestMask(MEM_ReadDMA.Channel);
	return ((UBYTE)MEM_NG);
}
	#endif
#endif


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[次の読みだしブロックの獲得]
	function	:[
		1. 指定されたブロックのチェーン化されている次の蓄積ブロックNoを獲得します
	]
	return		:[
		0 ～ MEM_AvailableMaxFATArea	次ブロックNo
		#define MEM_EOP_BLOCK			指定ブロックが原稿の最終ブロック
	]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* UWORD MEM_ReadGetNextBlockNo (UWORD BlockNo)		@* この次の読みだしブロックNoが知りたいというブロックNoを指定します */
/* UWORD MEM_ReadGetNextBlockNoExtRom(UWORD BlockNo)	 この次の読みだしブロックNoが知りたいというブロックNoを指定します */
UWORD MEM_ReadGetNextBlockNoERom(UWORD BlockNo)		/* この次の読みだしブロックNoが知りたいというブロックNoを指定します */
{
#if (PRO_QUICK_TX_TEST == ENABLE)	/* 1998/10/16 Y.Murata for KAKI */
	/* debug & test */
	while (1) {
		if (MEM_FATArea[BlockNo] & MEM_STORING_BLOCK) {
			wai_tsk(1);
		}
		else {
			break;
		}
	}
#endif

	return (MEM_FATArea[BlockNo]);									/* 次の読みだしブロック(MEM_FATArea[指定ブロック])を返します */
}


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	module		:[DRAM上のアドレスの算出]
	function	:[
		1.
	]
	return		:[なし]
	common		:[なし]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1994/01/05]
	author		:[NOBUKO]
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* UDWORD CalAddress = 0;	デコードエラー対策 1997/02/20 M.Tachibana */
UDWORD MEM_CalculateDMAAddress (UWORD BlockNo)	/* 先頭アドレスを知りたいブロックNoを指定します */
{
	UDWORD CalAddress = 0;	/* デコードエラー対策 1997/02/20 M.Tachibana */

	if ((BlockNo == MEM_EOP_BLOCK) ||								/* 指定ブロックNoがEOPか */
		(BlockNo == MEM_EOB_BLOCK) ||								/* 指定ブロックNoがEOBか */
		(BlockNo == MEM_BLOCK_OVER)) {								/* 指定ブロックNoがMEM_BLOCK_OVERなら */
		return (MEM_BLOCK_OVER);									/* MEM_BLOCK_OVERを返します */
	}

#if (0)
** 	/* Ｖ８５０に於いて、フィールドでプリント中にリセット発生という不具合が出た。
** 	** 原因調査の結果、以下の処理を追加した為の二次障害であることがわかった。
** 	** 
** 	**        ＦＡＴチェーンの最終ブロックのまた最後の方にＲＴＣがある場合に、
** 	**        最終ブロックのＤＭＡが終了した時点で、次のブロックはＥＯＰブロックの為
** 	**        ＤＭＡを止めて、メモリエラーにしていた（これが間違いでした！）
** 	**        
** 	**        従来は、次のブロックがＥＯＰブロックであっても、とりあえず１回はＤＭＡを実行し
** 	**        （但し、この時のＤＭＡアドレスはデタラメです）次のＴＣが発生したら、もうＤＭＡすべき
** 	**        ブロックは存在しないということでメモリＯＫで戻っていました。
** 	**
** 	**        修正としては、従来方式に戻します。
** 	**
** 	** by O.Kimoto 1998/10/31
** 	*/
** 	*/
** 	/* この関数の以下の処理は、引数に対して計算結果が絶対正しいということで動作しています。万一、引数が
** 	** 間違えている場合、ＤＲＡＭエリア以外のアドレスを返す可能性が有ります。
** 	** ですが、ＰＯＰＬＡＲのシステムでは、外付けＤＭＡＣの関係で２０ビット分しか有効になりません。
** 	** ということは、結果的に間違えたアドレスに対してＤＭＡを実行することとなり、非常にまずいです。
** 	** よって、引数（ＢｌｏｃｋＮｏ）が適正かどうかを判断し、不正なら、とりあえず、「MEM_BLOCK_OVER」を返します。
** 	** By O.Kimoto 1998/05/09
** 	*/
** 	if (BlockNo >= MEM_FAT_AREA_MAX) {
** 		return (MEM_BLOCK_OVER);									/* MEM_BLOCK_OVERを返します */
** 	}
#endif

	CalAddress = (UDWORD)(MEM_STOREAREA_START_ADDRESS + ((UDWORD)BlockNo * (UDWORD)MEM_BLOCK_SIZE));	/* By S.K Apr.30,1994 */
/*	CalAddress = (UDWORD)(MEM_STOREAREA_START_ADDRESS + ((UDWORD)BlockNo * (UDWORD)(128 * 1024)));	*/	/* 128Kbyte仕様 */
	return ((UDWORD)CalAddress);	/* 指定ブロックの16M空間上の絶対アドレスを返します */

}


/*************************************************************************
	module		:[ソフトコーデック用DRAMアドレス算出]
	function	:[
		1.DRAMの画データエリアをバイトの配列としそのポインタで算出する
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[MEM]
	date		:[1996/07/03]
	author		:[鈴木郁ニ]
*************************************************************************/
#if (PRO_CPU == SH7043)
/* UBYTE *MEM_CalculateSoftAddress (UWORD BlockNo)	@* 先頭アドレスを知りたいブロックNoを指定します */
/* UBYTE *MEM_CalculateSoftAddressExtRom(UWORD BlockNo)	@* 先頭アドレスを知りたいブロックNoを指定します */
UBYTE *MEM_CalculateSoftAddressERom(UWORD BlockNo)	/* 先頭アドレスを知りたいブロックNoを指定します */
{
	if ((BlockNo == MEM_EOP_BLOCK) ||								/* 指定ブロックNoがEOPか */
		(BlockNo == MEM_EOB_BLOCK) ||								/* 指定ブロックNoがEOBか */
		(BlockNo == MEM_BLOCK_OVER)) {								/* 指定ブロックNoがMEM_BLOCK_OVERなら */
		return (NO);									/* MEM_BLOCK_OVERを返します */
	}

	return(HeapArea.MEM_StoreArea + ((UDWORD)BlockNo * (UDWORD)MEM_BLOCK_SIZE));
}
#endif
