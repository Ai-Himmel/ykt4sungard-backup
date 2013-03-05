/**********************************************************************
*	RISC
*	File   Name:	CDC_INT.C
*	Coded    by:	野瀬敏弘
*	Moved    by:	小谷正樹 From \src\kobe\anzu\sh\src\icdc_sub.c
*	Date       :	1996/11/12 From \src\kobe\anzu\sh\src\icdc_sub.c
*	Module Name:
*	Note       :	コーデック割込処理サブルーチン
*
***********************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\std.h"
#include "\src\atlanta\define\mon_pro.h"
#include "\src\atlanta\sh7043\define\def_evtn.h"
#include "\src\atlanta\ext_v\cdc_data.h"
#include "\src\atlanta\ext_v\scn_data.h"
#include "\src\atlanta\ext_v\scn_tbl.h"
#if (PRO_PRINT_TYPE == LED)
#include "\src\atlanta\prt\ph3\define\prn_def.h"
#elif (PRO_PRINT_TYPE == THERMAL) /* SMuratec H.C.H 2003.07.11 */
 #if defined(STOCKHM2)			/* Modify by SMuratec K.W.Q 2004/05/18 */
#include "\src\atlanta\prt\lv_therm\define\prt_def.h"
 #else
#include "\src\atlanta\prt\iu_therm\define\prt_def.h"
 #endif
#else
#include "\src\atlanta\prt\sp322\define\prn_def.h"
#endif

#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\define\cdc_pro.h"
#include "\src\atlanta\define\scn_pro.h"
#include "\src\atlanta\define\cdc_def.h"
#include "\src\atlanta\define\scn_io.h"
#include "\src\atlanta\ext_v\cdc_tbl.h"

/*** For Debug T.Nose 1996/05/10 ***/
extern UWORD DEBUG_AddressBuffer[][2];
extern unsigned char DEBUG_EncodeCounter;
static UWORD DEBUG_CodecDMA_line = 0;
static unsigned char DEBUG_CommandEndFlag;
/*** debug line end ****************/

/* メモリー送信原稿後端縮む件 T.Nose 1997/11/05 */
#include "\src\atlanta\define\mntsw_g.h"
#include "\src\atlanta\ext_v\bkupram.h"

#if (0) /* デバッグ終了 1998/04/30 by T.Soneoka */
**#if (PRO_PANEL == KANJI)
**/* プリンターコーデックをＭＮ８６０６４にした時のパフォーマンス測定用 By O.Kimoto 1998/04/23 */
**#include "\src\atlanta\sh7043\define\sh_sys.h"
**UBYTE cdc2buf_dma_count = 0;
**extern UWORD SYS_LED1_PortStatus;
**#endif
#endif

#if (0)
** /* コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策
** ** が有効であることを確認できた為、ここは従来の処理にもどします 1998/04/28 by T.Soneoka
** */
** #if (PRO_PRN_CODEC_TYPE == MN86063) /* 400dpiのｲﾒｰｼﾞを2重に書く件 T.Nose 1998/0421 */
** extern UBYTE TrueReductiondatio;
** #endif
#endif

/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
#include "\src\atlanta\define\mntsw_e.h"
#endif

/*************************************************************************
	module		:[スキャナーコーデック割込処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/02/09]
	author		:[野瀬敏弘]
*************************************************************************/
void ScannerCodecInterrupt(void)
{
#if (PRO_SCN_CODEC_TYPE == MN86063) || (PRO_SCN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
	UWORD status;
	UWORD work;
	UWORD loop_limit;	/*Add By M.Kotani 1998/01/23*/
	UWORD *mscr_dtcr;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
	UDWORD address;
	UWORD dma_address;
	UWORD encode_address;
	UWORD decode_address;
	UWORD encode_line;
	UWORD decode_line;
#endif /* (PRO_CODEC_NUMBER == CDC_SINGLE) */

	loop_limit = 10000;	/*10000回を上限とする Add By M.Kotani 1998/01/23*/
	mscr_dtcr = (UWORD *)CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MSCR_DTCR];
	status = inpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_DMCR_DMIR]);

	if (status & DBEND1_BIT) {	/*先にプリンタを処理するように変更 1998/01/22 M.Kotani*/
		CodecDMCR_DMIR_Status[SCANNER_CODEC] = status;
		/* dma1_end */
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
		if (status & DABOT1_BIT) {	/* DMA ABORTED */
			dma_address = CodecParameterRegister[SCANNER_CODEC].T1_STRA_Status;
			outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MAR], T1_STRA_ADR);	/* DMAﾁｬﾝﾈﾙ1転送ﾗｲﾝ数のﾚｼﾞｽﾀｱﾄﾞﾚｽ */
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR], dma_address);
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			decode_line = PRN_FROM_CODEC_LINECOUNT;										/** DMA転送ライン数*/
			outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MAR], T1_BLGR_ADR);	/* DMAﾁｬﾝﾈﾙ1転送ﾗｲﾝ数のﾚｼﾞｽﾀｱﾄﾞﾚｽ */
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR], decode_line);
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			/** ＤＭＡ再起動 */
			address = CodecRegisterAddressTable[SCANNER_CODEC][CODEC_DMCR_DMIR];	/* DMCRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
			CodecDMCR_DMIR_Status[SCANNER_CODEC] &= 0xFF00;	/**下位クリア*/
			CodecDMCR_DMIR_Status[SCANNER_CODEC] |= inp(address + 1);			/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
			CodecDMCR_DMIR_Status[SCANNER_CODEC] |= DMENB1_BIT;					/* DMAｲﾈｰﾌﾞﾙ */
			outp((address + 1), (UBYTE)CodecDMCR_DMIR_Status[SCANNER_CODEC]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
			/**スムージングLSIを通常動作に戻す(ROUTE1をやめる)*/
		}
		else {
			/** ＤＭＡ終了アドレスをＧｅｔ */
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MAR], (T1_STRA_ADR | MAR_R_W_BIT));	/**アドレスをポートにライトする*/
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			dma_address = inpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR]);	/**パラメータをリードする*/
#if (0)
			dma_address = ReadCodecParameterRegister(SCANNER_CODEC,T1_STRA_ADR);
#endif
			/** デコード終了アドレスをＧｅｔ */
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MAR], (D1_STRA_ADR | MAR_R_W_BIT));		/* DMAﾁｬﾝﾈﾙ1転送ｱﾄﾞﾚｽのﾚｼﾞｽﾀをﾘｰﾄﾞで選択する */
			while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
			WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			decode_address = inpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR]);
#if (0)
			decode_address = ReadCodecParameterRegister(SCANNER_CODEC,D1_STRA_ADR);
#endif

			if ((decode_address == 0) || (decode_address != dma_address)) {
				if (decode_address == 0) { /* リストプリントの時 */
					decode_line = CDC_LIST_PRINT_LINE_COUNT;					/* decode_line : 転送ライン数 (52)*/
				}
				else {	/**デコード中のとき*/
					if (decode_address > dma_address) {
						decode_address -= dma_address;
					}
					else {
						decode_address = (decode_address - CodecParameterRegister[SCANNER_CODEC].D1_MTOPA_Status)
									   + (CodecParameterRegister[SCANNER_CODEC].D1_MENDA_Status - dma_address);
					}
					decode_line = decode_address / (304 * 2);				/* decode_line : 転送ライン数 */
				}

				outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MAR], T1_BLGR_ADR);	/* DMAﾁｬﾝﾈﾙ1転送ﾗｲﾝ数のﾚｼﾞｽﾀｱﾄﾞﾚｽ */
				while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
					if (*mscr_dtcr & PBRR_BIT) {
						break; /**パラメータレジスタアクセス可能　PBRレディ*/
					}
				}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
				WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
				outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR], decode_line);
				while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
					if (*mscr_dtcr & PBRR_BIT) {
						break; /**パラメータレジスタアクセス可能　PBRレディ*/
					}
				}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
				WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
#if (0)
				SetCodecParameterRegister(SCANNER_CODEC, T1_BLGR_ADR, decode_line);	/**DMA転送ライン数*/
				WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
				address = CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR];	/* PBRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
				outpw(address, decode_line);
				WaitPBR_Ready(SCANNER_CODEC);								/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
				/** ＤＭＡ再起動 */
				address = CodecRegisterAddressTable[SCANNER_CODEC][CODEC_DMCR_DMIR];	/* DMCRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
				CodecDMCR_DMIR_Status[SCANNER_CODEC] &= 0xFF00;	/**下位クリア*/
				CodecDMCR_DMIR_Status[SCANNER_CODEC] |= inp(address + 1);			/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
				CodecDMCR_DMIR_Status[SCANNER_CODEC] |= DMENB1_BIT;					/* DMAｲﾈｰﾌﾞﾙ */
				outp((address + 1), (UBYTE)CodecDMCR_DMIR_Status[SCANNER_CODEC]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
#if (0)
				CodecDMA_Enable(SCANNER_CODEC, 1);
#endif
			}
			CDC1_DMA1_EndFlag = 1;
			idet_evt(EVT_CDC1_DMA1_END);			/* イベントを発行 */
		}
#else /* (PRO_CODEC_NUMBER == CDC_SINGLE) */
		idet_evt(EVT_CDC0_DMA1_END);			/* イベントを発行 */
#endif /* (PRO_CODEC_NUMBER == CDC_SINGLE) */
	}
#if (0)	/**アボートを使用するように変更 By M.Kotani 1997/11/13*/
	if (status & DABOT0_BIT) {
		CodecDMCR_DMIR_Status[SCANNER_CODEC] = status;
		outp((unsigned long)0,(unsigned char)0);		/* DMA ABORTED */
	}
#endif
	if (status & DBEND0_BIT) {
		CodecDMCR_DMIR_Status[SCANNER_CODEC] = status;
#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/*ハードコーデック１個使用*/
		while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
			if (*mscr_dtcr & PBRR_BIT) {
				break; /**パラメータレジスタアクセス可能　PBRレディ*/
			}
		}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
		WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
		outpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_MAR], (T0_STRA_ADR | MAR_R_W_BIT));	/**アドレスをポートにライトする*/
		while (loop_limit--) {	/*Add By M.Kotani 1998/01/23*/
			if (*mscr_dtcr & PBRR_BIT) {
				break; /**パラメータレジスタアクセス可能　PBRレディ*/
			}
		}
#if (0)	/*上記に書き換え By M.Kotani 1998/01/23*/
		WaitPBR_Ready(SCANNER_CODEC);												/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
		CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status = inpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_PBR]);	/**パラメータをリードする*/
 #if (0)	/* 1997/11/19 Y.M */
		CodecParameterRegister[SCANNER_CODEC].T0_STRA_Status = ReadCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR);

		dma_address		= ReadCodecParameterRegister(SCANNER_CODEC, T0_STRA_ADR);
		encode_address	= ReadCodecParameterRegister(SCANNER_CODEC, C0_STRA_ADR);
		if (dma_address >= encode_address) {
			encode_address = dma_address - encode_address;
		}
		else {
			encode_address = (dma_address - CodecParameterRegister[SCANNER_CODEC].C0_MTOPA_Status)
						   + (CodecParameterRegister[SCANNER_CODEC].C0_MENDA_Status - encode_address);
		}
		encode_line = encode_address / (304 * 2);
		CodecParameterRegister[SCANNER_CODEC].INLINE_Status	= encode_line;	/**入力ライン数*/
		if (encode_line) {	/**せってい範囲が1以上のため0のときは何もしない。上の大域変数を見て0の時はエンコードをスタートしないようにする必要がある*/
			SetCodecParameterRegister(SCANNER_CODEC, INLINE_ADR, encode_line);
		}
 #endif
#endif
		/***********************************/
		/*** SCN_ReadMotorPulseCounter() ***/
		/***********************************/

		/* メモリー送信原稿後端縮む件 T.Nose 1997/11/05 */
		if (SYB_MaintenanceSwitch[MNT_SW_G8] & 0x01) {
			/* カウンターの値が上位/下位が逆だった
			** 他の場所と同じ様に関数でリードするように変更
			** T.Nose 1997/10/20
			*/
			work = (UWORD)inp(MTCNT0_PORT);
			work = (work << 8);
			work = (work + (UWORD)inp(MTCNT1_PORT));
		}
		else {
			work = SCN_ReadMotorPulseCounter();
		}

		SCN_Debug53Lines = work;
		DebugLineInt = work;
		DebugPreLineInt = work;
		SCN_SpeedCheckPoint = 0;

		SCN_SetLineStep(SCN_SpeedCheckLine[0]);	/**以下の行を元に戻しました1997/09/10 M.Kotani*/
#if (0)
		SCN_INTLNCN_Status = 0x20;
		outp(INTLNCN_PORT,SCN_INTLNCN_Status);

		SCN_MTCNT_Status |= IO_BIT_LINE_INT_COUNT_LATCH;
		outp(MTCNT_PORT,SCN_MTCNT_Status);

		SCN_MTCNT_Status &= ~IO_BIT_LINE_INT_COUNT_LATCH;
		outp(MTCNT_PORT,SCN_MTCNT_Status);

		SCN_MTCNT_Status |= IO_BIT_LINE_INT_COUNT_LATCH;
		outp(MTCNT_PORT,SCN_MTCNT_Status);
#endif
		/**********************************/
		/*** SCN_SetLineInt(SCN_ENABLE) ***/
		/**********************************/
/* STx First Scan T.Nose 1998/06/29 */
#if (PRO_MINOLTA_TEST_FUNC == ENABLE)
		if (SYB_MaintenanceSwitch[MNT_SW_E0] & 0x80) {
			if (SCN_STxLineIntDisableFlag == 0) {
				SCN_SCCNT_Status |= IO_BIT_LINE_INT_ENABLE;
				outp(SCCNT_PORT,SCN_SCCNT_Status);
			}
		}
		else {
			SCN_SCCNT_Status |= IO_BIT_LINE_INT_ENABLE;
			outp(SCCNT_PORT,SCN_SCCNT_Status);
		}
#else
		SCN_SCCNT_Status |= IO_BIT_LINE_INT_ENABLE;
		outp(SCCNT_PORT,SCN_SCCNT_Status);
#endif

		/********************************************************************/
		/*** CodecDMA_Enable(SCANNER_CODEC, 0);	DMA Channel 0を有効にする ***/
		/********************************************************************/
		if (status & DABOT0_BIT) {	/**アボートの時は再起動しないように変更 By M.Kotani 1997/11/13*/
		}
		else {
			CodecDMA_Enable(SCANNER_CODEC, 0);
		}
#if (0)
		CodecDMCR_DMIR_Status[SCANNER_CODEC] &= 0xFF00;	/**下位クリア*/
		CodecDMCR_DMIR_Status[SCANNER_CODEC] |= inp((CodecRegisterAddressTable[SCANNER_CODEC][CODEC_DMCR_DMIR] + 1));	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
		CodecDMCR_DMIR_Status[SCANNER_CODEC] |= DMENB0_BIT;
		outp(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_DMCR_DMIR] + 1, (UBYTE)CodecDMCR_DMIR_Status[SCANNER_CODEC]);	/**ハードの仕様 By M.Kotani or T.Kumano 1997/08/29*/
#endif

		CDC0_DMA0_EndFlag = 1;
		CDC0_DMA0_EndCounter++;
		CDC_ImageBufferStatus[0] = 1;
		idet_evt(EVT_CDC0_DMA0_END);
	}
	/* check_command_end */
	status = inpw(CodecRegisterAddressTable[SCANNER_CODEC][CODEC_STIR]);
	if (status & CMDE0_BIT) {
		/* command0_end */
		CodecSTIR_Status[SCANNER_CODEC] = status;
		CDC_ImageBufferStatus[0] = 0;
		idet_evt(EVT_CDC0_COMMAND_END);
	}
#if (PRO_CODEC_NUMBER == CDC_SINGLE)
	if (status & CMDE1_BIT) {
		/* command1_end */
		CodecSTIR_Status[SCANNER_CODEC] = status;
		idet_evt(EVT_CDC1_COMMAND_END);
	}
#endif

#endif
}

/*************************************************************************
	module		:[プリンタコーデック割込処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/02/13]
	author		:[野瀬敏弘＋小谷正樹]
*************************************************************************/
void PrinterCodecInterrupt(void)
{
#if (PRO_PRN_CODEC_TYPE == MN86063) || (PRO_PRN_CODEC_TYPE == MN86064)	/* 1998/06/10 H.Yoshikawa */
	UDWORD address;
	UWORD status;
	UWORD dma_address;
	UWORD decode_address;
	UWORD decode_line;
	UWORD *mscr_dtcr;	/*Add By M.Kotani 1998/02/03*/
	UWORD loop_limit;	/*Add By M.Kotani 1998/02/03*/
	UWORD decode_delayed; 	/**コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策*/

	decode_delayed = 0;	/**コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策*/
	loop_limit = 10000;	/*10000回を上限とする Add By M.Kotani 1998/02/03*/
	mscr_dtcr = (UWORD *)CodecRegisterAddressTable[PRINTER_CODEC][CODEC_MSCR_DTCR];	/*Add By M.Kotani 1998/02/03*/

	/** ＤＭＡ終了をチェックする */
	status = inpw(CodecRegisterAddressTable[PRINTER_CODEC][CODEC_DMCR_DMIR]);	/** DMCR_DMIRをリードする */
	if (status & DBEND0_BIT) {	/** ＤＭＡチャンネル０が終了 */
		CodecDMCR_DMIR_Status[PRINTER_CODEC] = status;
		idet_evt(EVT_CDC1_DMA0_END);		/* イベントを発行 */
	}
	if (status & DBEND1_BIT) {	/** ＤＭＡチャンネル１が終了 */
		CodecDMCR_DMIR_Status[PRINTER_CODEC] = status;
		/** ＤＭＡ終了アドレスをＧｅｔ */
		address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_MAR];	/* MARﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
		outpw(address,(T1_STRA_ADR | MAR_R_W_BIT));						/* DMAﾁｬﾝﾈﾙ1転送ｱﾄﾞﾚｽのﾚｼﾞｽﾀをﾘｰﾄﾞで選択する */
		while (loop_limit--) {	/*Add By M.Kotani 1998/02/03*/
			if (*mscr_dtcr & PBRR_BIT) {
				break; /**パラメータレジスタアクセス可能　PBRレディ*/
			}
		}
#if (0)	/*上記に書き換え By M.Kotani 1998/02/03*/
		WaitPBR_Ready(PRINTER_CODEC);									/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
		address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_PBR];	/* PBRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
		dma_address = inpw(address);
		/** デコード終了アドレスをＧｅｔ */
		while (loop_limit--) {	/*Add By M.Kotani 1998/02/03*/
			if (*mscr_dtcr & PBRR_BIT) {
				break; /**パラメータレジスタアクセス可能　PBRレディ*/
			}
		}
#if (0)	/*上記に書き換え By M.Kotani 1998/02/03*/
		WaitPBR_Ready(PRINTER_CODEC);									/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
		address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_MAR];	/* MARﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
		outpw(address,(D0_STRA_ADR | MAR_R_W_BIT));						/* DMAﾁｬﾝﾈﾙ1転送ｱﾄﾞﾚｽのﾚｼﾞｽﾀをﾘｰﾄﾞで選択する */
		while (loop_limit--) {	/*Add By M.Kotani 1998/02/03*/
			if (*mscr_dtcr & PBRR_BIT) {
				break; /**パラメータレジスタアクセス可能　PBRレディ*/
			}
		}
#if (0)	/*上記に書き換え By M.Kotani 1998/02/03*/
		WaitPBR_Ready(PRINTER_CODEC);									/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
		address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_PBR];	/* PBRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
		decode_address = inpw(address);
		if ((decode_address == 0) || (decode_address != dma_address)) {
			if (decode_address == 0) { /* リストプリントの時 */
				decode_line = PRN_FROM_CODEC_LINECOUNT;					/* decode_line : 転送ライン数 (52)*/
			}
			else {	/**デコード中のとき*/
/*
** コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策
** が有効であることを確認できた為、ここは従来の処理にもどします 1998/04/28 by T.Soneoka
*/
#if (0)
**#if (PRO_PRN_CODEC_TYPE == MN86063) /* 400dpiのｲﾒｰｼﾞを2重に書く件 T.Nose 1998/0421 */
**				/* ＭＮ８６０６３でデコードが間に合わない件
**				** とりあえず、下記のような対策を入れます。
**				**     １００％時：  メンテナンススイッチＧ：３－１ ０：可変
**				**                                                  １：５２ライン固定
**				**         縮小時：  従来どおり、可変
**				** By O.Kimoto 1998/04/24
**				*/
**				if (TrueReductiondatio == 100) {	/*  100% ?*/
**					if (SYB_MaintenanceSwitch[MNT_SW_G3] & 0x02) {
**						decode_line = PRN_FROM_CODEC_LINECOUNT;					/* decode_line : 転送ライン数 (52)*/
**					}
**					else {
**						if (decode_address > dma_address) {
**							decode_address -= dma_address;
**						}
**						else {
**							decode_address = (decode_address - CodecParameterRegister[PRINTER_CODEC].D0_MTOPA_Status)
**										   + (CodecParameterRegister[PRINTER_CODEC].D0_MENDA_Status - dma_address);
**						}
**						decode_line = decode_address / (304 * 2);				/* decode_line : 転送ライン数 */
**					}
**				}
**				else {	/* 縮小時 */
**					if (decode_address > dma_address) {
**						decode_address -= dma_address;
**					}
**					else {
**						decode_address = (decode_address - CodecParameterRegister[PRINTER_CODEC].D0_MTOPA_Status)
**									   + (CodecParameterRegister[PRINTER_CODEC].D0_MENDA_Status - dma_address);
**					}
**					decode_line = decode_address / (304 * 2);				/* decode_line : 転送ライン数 */
**				}
**#else
**				if (decode_address > dma_address) {
**					decode_address -= dma_address;
**				}
**				else {
**					decode_address = (decode_address - CodecParameterRegister[PRINTER_CODEC].D0_MTOPA_Status)
**								   + (CodecParameterRegister[PRINTER_CODEC].D0_MENDA_Status - dma_address);
**				}
**				decode_line = decode_address / (304 * 2);				/* decode_line : 転送ライン数 */
**#endif
#else
				if (decode_address > dma_address) {
					decode_address -= dma_address;
				}
				else {
					decode_address = (decode_address - CodecParameterRegister[PRINTER_CODEC].D0_MTOPA_Status)
								   + (CodecParameterRegister[PRINTER_CODEC].D0_MENDA_Status - dma_address);
				}
				decode_line = decode_address / (304 * 2);				/* decode_line : 転送ライン数 */
#endif
			}
			if (decode_line > PRN_FROM_CODEC_LINECOUNT) {	/**コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策*/
				decode_line /= 2;	/**転送を2回に分割する*/
				decode_delayed = 1;	/*次のデコード開始イベントを見送る*/
			}
			else {
				decode_delayed = 0;	/*デコード開始イベントを発行する*/
			}
/**/		DEBUG_CodecDMA_line = decode_line;	/* For DEBUG */
			address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_MAR];	/* MARﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
			outpw(address, T1_BLGR_ADR);									/* DMAﾁｬﾝﾈﾙ1転送ﾗｲﾝ数のﾚｼﾞｽﾀｱﾄﾞﾚｽ */
			while (loop_limit--) {	/*Add By M.Kotani 1998/02/03*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/02/03*/
			WaitPBR_Ready(PRINTER_CODEC);									/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_PBR];	/* PBRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
			outpw(address, decode_line);
			while (loop_limit--) {	/*Add By M.Kotani 1998/02/03*/
				if (*mscr_dtcr & PBRR_BIT) {
					break; /**パラメータレジスタアクセス可能　PBRレディ*/
				}
			}
#if (0)	/*上記に書き換え By M.Kotani 1998/02/03*/
			WaitPBR_Ready(PRINTER_CODEC);									/* ﾚｼﾞｽﾀ処理時間20MHz6ｻｲｸﾙ */
#endif
			/** ＤＭＡ再起動 */
			address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_DMCR_DMIR];	/* DMCRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
			status = inpw(address);
			status |= DMENB1_BIT;					/* DMAｲﾈｰﾌﾞﾙ */
			outpw(address, status);

#if (0) /* デバッグ終了 1998/04/30 by T.Soneoka */
**#if (PRO_PANEL == KANJI)
**			/* プリンターコーデックをＭＮ８６０６４にした時のパフォーマンス測定用 By O.Kimoto 1998/04/23 */
**#if (0)
**** 			/* ポート変更 By O.Kimoto 1998/04/30 */
**** 			if ((cdc2buf_dma_count % 2) == 1) {
**** 				SYS_LED1_PortStatus |= 0x0040;
**** 			}
**** 			else {
**** 				SYS_LED1_PortStatus &= 0x00BF;
**** 			}
**** 			outpw(LED1_PORT, (UWORD)SYS_LED1_PortStatus);
**** 			cdc2buf_dma_count ++;
**#else
**			if ((cdc2buf_dma_count % 2) == 1) {
**				IO__PADRH |= IO_BIT_FCLCH3;
**			}
**			else {
**				IO__PADRH &= ~IO_BIT_FCLCH3;
**			}
**			cdc2buf_dma_count ++;
**#endif
**
**#endif
#endif

		}
		else {	/*デコードが間に合わなくて絵が無くなっちゃた！！。ここにきたら過去の絵をもう一度転送するよ Add By M.kotani 1998/04/27*/
			/** ＤＭＡ再起動 */
			address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_DMCR_DMIR];	/* DMCRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
			status = inpw(address);
			status |= DMENB1_BIT;					/* DMAｲﾈｰﾌﾞﾙ */
			outpw(address, status);
		}
		if (!CDC1_DMA1_EndFlag) {	/**コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策*/
			if (!decode_delayed) {	/**コーデック処理が間に合わない時の処理を追加 M.Kotani 98/04/27 未来の絵を描く対策*/
				CDC1_DMA1_EndFlag = 1;
				idet_evt(EVT_CDC1_DMA1_END);			/* イベントを発行 */
			}
		}
	}
	/** コマンド終了をチェックする */
	address = CodecRegisterAddressTable[PRINTER_CODEC][CODEC_STIR];		/* STIRﾚｼﾞｽﾀｱﾄﾞﾚｽ           */
	status = inpw(address);
	if ((status & CMDE0_BIT) != 0) {

#if (0) /* デバッグ終了 1998/04/30 by T.Soneoka */
**#if (PRO_PANEL == KANJI)
**		/* プリンターコーデックをＭＮ８６０６４にした時のパフォーマンス測定用 By O.Kimoto 1998/04/23 */
**
**#if (0)
**** 		/* ポート変更 By O.Kimoto 1998/04/30 */
**** 		SYS_LED1_PortStatus &= 0x007f;
**** 		outpw(LED1_PORT, (UWORD)SYS_LED1_PortStatus);
**#else
**		IO__PADRH &= ~IO_BIT_FCLCHH;
**#endif
**
**#endif
#endif
		CodecSTIR_Status[PRINTER_CODEC] = status;
		idet_evt(EVT_CDC1_COMMAND_END);
	}

#endif
}


/*************************************************************************
	module		:[通信コーデック割込処理]
	function	:[
		1.
	]
	return		:[無し]
	common		:[]
	condition	:[]
	comment		:[]
	machine		:[SH7043]
	language	:[SHC]
	keyword		:[CDC]
	date		:[1996/02/15]
	author		:[野瀬敏弘]
*************************************************************************/
CONST UBYTE com_codec_debug = 0; /* Debug switch by H.Kubo 1997/11/12 */ /* Disabled by H.Kubo 1998/02/17 */
void CommunicationCodecInterrupt(void)
{

/* #if (PRO_COM_CODEC_TYPE == MN86064) */
#if (PRO_COM_CODEC_TYPE != SOFTWARE) /* #if condition is changed by H.Kubo 1997/11/04 */
	UDWORD address;
	UWORD status;

	address = CodecRegisterAddressTable[COMMUNICATION_CODEC][CODEC_DMCR_DMIR];
	status = inpw(address);
	if ((status & DBEND0_BIT) != 0) {
		CodecDMCR_DMIR_Status[COMMUNICATION_CODEC] = status;
		idet_evt(EVT_CDC2_DMA0_END);
	}
	if ((status & DBEND1_BIT) != 0) {
		CodecDMCR_DMIR_Status[COMMUNICATION_CODEC] = status;
		idet_evt(EVT_CDC2_DMA1_END);
	}
	address = CodecRegisterAddressTable[COMMUNICATION_CODEC][CODEC_STIR];
	status = inpw(address);
#if (0)	/* Delete by O.Kimoto 1998/02/17 */
** 	if (com_codec_debug == 1) { /* Debug code by H.Kubo 1997/11/12 */
** 		CodecSTIR_Status[COMMUNICATION_CODEC] = status;
** 	}
#endif
#if (PRO_JBIG == ENABLE)	/*  by T.Soneoka 1997/12/10 */
	/* 1999/03/05 by T.Soneoka */
	if (status & JBIGIRQ_BIT) {
		outpw(CodecRegisterAddressTable[COMMUNICATION_CODEC][CODEC_MAR], (MAR_R_W_BIT | D_QMIR_ADR));
		CodecParameterRegister[COMMUNICATION_CODEC].D_QMIR_Status = inpw(CodecRegisterAddressTable[COMMUNICATION_CODEC][CODEC_PBR]);
		outpw(CodecRegisterAddressTable[COMMUNICATION_CODEC][CODEC_MAR], D_QMIR_ADR);
		outpw(CodecRegisterAddressTable[COMMUNICATION_CODEC][CODEC_PBR], 0x0);
	}
	if ((status & JBIGIRQ_BIT)
	||  (status & CMDE0_BIT)) {
		CodecSTIR_Status[COMMUNICATION_CODEC] = status;
		idet_evt(EVT_CDC2_COMMAND_END);
	}
#else
	if ((status & CMDE0_BIT) != 0) {
		CodecSTIR_Status[COMMUNICATION_CODEC] = status;
		idet_evt(EVT_CDC2_COMMAND_END);
	}
#endif
#endif /* (PRO_COM_CODEC_TYPE != SOFTWARE) */
}
