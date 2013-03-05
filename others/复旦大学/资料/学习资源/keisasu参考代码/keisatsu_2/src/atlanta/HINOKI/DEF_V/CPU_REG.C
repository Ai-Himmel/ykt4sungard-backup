/*
**	%W%
**	File Name:	f:\prj\eva\src\def\cpu_reg.c
**	Create:	1997/11/14	ANZU_LよりCopy By Masahiro,IIDA
**	Description: SH7014 CPU & CPU Peripheral Address Map
**	Change: 19xx/xx/xx	
*/
#include "\src\atlanta\define\product.h"

#pragma section CPUREG		/* locate section name "BCPUREG" */
/*****************************************************/
/*  シリアルコミュニケーションインターフェース		 */
/*****************************************************/
/*--＜チャンネル０＞------------------------------------------------------------------------*/
volatile UBYTE	sci_smr0;		/* (0xffff81A0)	  シリアルモードレジスタ			*/
volatile UBYTE	sci_brr0;		/* (0xffff81A1)	  ビットレートレジスタ			*/
volatile UBYTE	sci_scr0;		/* (0xffff81A2)	  シリアルコントロールレジスタ	*/
volatile UBYTE	sci_tdr0;		/* (0xffff81A3)	  トランスミットデータレジスタ	*/
volatile UBYTE	sci_ssr0;		/* (0xffff81A4)	  シリアルステータスレジスタ		*/
volatile UBYTE	sci_rdr0;		/* (0xffff81A5)	  レシーブデータレジスタ			*/
volatile UBYTE	sci_dummy0[10];	/* 0xfff81A6-0xffff81AF  ＤＵＭＭＹ			*/
/*--＜チャンネル１＞------------------------------------------------------------------------*/
volatile UBYTE	sci_smr1;		/* (0xffff81B0)	  シリアルモードレジスタ			*/
volatile UBYTE	sci_brr1;		/* (0xffff81B1)	  ビットレートレジスタ			*/
volatile UBYTE	sci_scr1;		/* (0xffff81B2)	  シリアルコントロールレジスタ	*/
volatile UBYTE	sci_tdr1;		/* (0xffff81B3)	  トランスミットデータレジスタ	*/
volatile UBYTE	sci_ssr1;		/* (0xffff81B4)	  シリアルステータスレジスタ		*/
volatile UBYTE	sci_rdr1;		/* (0xffff81B5)	  レシーブデータレジスタ			*/
volatile UBYTE	sci_dummy1[74];	/* 0xfff81B6-0xffff81FF  ＤＵＭＭＹ				*/
/*****************************************************/
/*  マルチファンクションタイマパルスユニット 		 */
/*****************************************************/
/*--＜チャンネル３＞ ＜チャンネル４＞--------------------------------------------------*/
volatile UBYTE	mtu_tcr3;		/* 0xffff8200：  タイマーコントロールレジスタ３	*/
volatile UBYTE	mtu_tcr4;		/* 0xffff8201： タイマーコントロールレジスタ４	*/
volatile UBYTE	mtu_tmdr3;		/* 0xffff8202：  タイマーモードレジスタ３		*/
volatile UBYTE	mtu_tmdr4;		/* 0xffff8203： タイマーモードレジスタ４		*/
volatile UBYTE	mtu_tior3h;		/* 0xffff8204：  タイマーＩ／Ｏコントロールレジスタ３Ｈ*/
volatile UBYTE	mtu_tior3l;		/* 0xffff8205：  タイマーＩ／Ｏコントロールレジスタ３Ｌ*/
volatile UBYTE	mtu_tior4h;		/* 0xffff8206： タイマーＩ／Ｏコントロールレジスタ４Ｈ*/
volatile UBYTE	mtu_tior4l;		/* 0xffff8207： タイマーＩ／Ｏコントロールレジスタ４Ｌ*/
volatile UBYTE	mtu_tier3;		/* 0xffff8208：  タイマーインターラプトイネーブルレジスタ３*/
volatile UBYTE	mtu_tier4;		/* 0xffff8209： タイマーインターラプトイネーブルレジスタ４*/
volatile UBYTE	mtu_toer;		/* 0xffff820A：  タイマーアウトプットマスターイネーブルレジスタ*/
volatile UBYTE	mtu_tocr;		/* 0xffff820B：  タイマーアウトプットコントロールレジスタ*/
volatile UBYTE	mtu_dummy0;		/* 0xffff820C：  ＤＵＭＭＹ	*/
volatile UBYTE	mtu_tgcr;		/* 0xffff820D：  タイマーゲートコントロールレジスタ*/
volatile UBYTE	mtu_dummy1[2];	/* 0xffff820E～0F：  ＤＵＭＭＹ	*/
volatile UWORD	mtu_tcnt3;		/* 0xffff8210：  タイマーカウンタ３				*/
volatile UWORD	mtu_tcnt4;		/* 0xffff8212：  タイマーカウンタ４				*/
volatile UWORD	mtu_tcdr;		/* 0xffff8214：  タイマー周期データレジスタ		*/
volatile UWORD	mtu_tddr;		/* 0xffff8216：  タイマーデッドタイムデータレジスタ*/
volatile UWORD	mtu_tgr3a;		/* 0xffff8218：  ジェネラルレジスタ３Ａ			*/
volatile UWORD	mtu_tgr3b;		/* 0xffff821A：  ジェネラルレジスタ３Ｂ			*/
volatile UWORD	mtu_tgr4a;		/* 0xffff821C：  ジェネラルレジスタ４Ａ			*/
volatile UWORD	mtu_tgr4b;		/* 0xffff821E：  ジェネラルレジスタ４Ｂ			*/
volatile UWORD	mtu_tcnts;		/* 0xffff8220：  タイマーサブカウンタ			*/
volatile UWORD	mtu_tcbr;		/* 0xffff8222：  タイマー周期バッファレジスタ	*/
volatile UWORD	mtu_tgr3c;		/* 0xffff8224：  ジェネラルレジスタ３Ｃ			*/
volatile UWORD	mtu_tgr3d;		/* 0xffff8226：  ジェネラルレジスタ３Ｄ			*/
volatile UWORD	mtu_tgr4c;		/* 0xffff8228：  ジェネラルレジスタ４Ｃ			*/
volatile UWORD	mtu_tgr4d;		/* 0xffff822A：  ジェネラルレジスタ４Ｄ			*/
volatile UBYTE	mtu_tsr3;		/* 0xffff822C：  タイマーステータスレジスタ３	*/
volatile UBYTE	mtu_tsr4;		/* 0xffff822D：  タイマーステータスレジスタ４	*/
volatile UBYTE	mtu_dummy2[18];	/* 0xffff822E～3F：  ＤＵＭＭＹ	*/
/*--＜チャンネル共通＞----------------------------------------------------------------------*/
volatile UBYTE	mtu_tstr;		/* 0xffff8240：  タイマースタートレジスタ		*/
volatile UBYTE	mtu_tsyr;		/* 0xffff8241：  タイマーシンクロレジスタ		*/
volatile UBYTE	mtu_dummy3[30];	/* 0xffff8242～5F：  ＤＵＭＭＹ	*/
/*--＜チャンネル０＞------------------------------------------------------------------------*/
volatile UBYTE	mtu_tcr0;		/* 0xffff8260：  タイマーコントロールレジスタ０	*/
volatile UBYTE	mtu_tmdr0;		/* 0xffff8261：  タイマーモードレジスタ０		*/
volatile UBYTE	mtu_tior0h;		/* 0xffff8262：  タイマーＩ／Ｏコントロールレジスタ０Ｈ*/
volatile UBYTE	mtu_tior0l;		/* 0xffff8263：  タイマーＩ／Ｏコントロールレジスタ０Ｌ*/
volatile UBYTE	mtu_tier0;		/* 0xffff8264：  タイマーインターラプトイネーブルレジスタ０*/
volatile UBYTE	mtu_tsr0;		/* 0xffff8265：  タイマーステータスレジスタ０	*/
volatile UWORD	mtu_tcnt0;		/* 0xffff8266：  タイマーカウンタ０				*/
volatile UWORD	mtu_tgr0a;		/* 0xffff8268：  ジェネラルレジスタ０Ａ			*/
volatile UWORD	mtu_tgr0b;		/* 0xffff826A：  ジェネラルレジスタ０Ｂ			*/
volatile UWORD	mtu_tgr0c;		/* 0xffff826C：  ジェネラルレジスタ０Ｃ			*/
volatile UWORD	mtu_tgr0d;		/* 0xffff826E：  ジェネラルレジスタ０Ｄ			*/
volatile UBYTE	mtu_dummy4[16];	/* 0xffff8270～7F：  ＤＵＭＭＹ	*/
/*--＜チャンネル１＞------------------------------------------------------------------------*/
volatile UBYTE	mtu_tcr1;		/* 0xffff8280：  タイマーコントロールレジスタ１	*/
volatile UBYTE	mtu_tmdr1;		/* 0xffff8281：  タイマーモードレジスタ１		*/
volatile UBYTE	mtu_tior1;		/* 0xffff8282：  タイマーＩ／Ｏコントロールレジスタ１*/
volatile UBYTE	mtu_tier1;		/* 0xffff8284：  タイマーインターラプトイネーブルレジスタ１*/
volatile UBYTE	mtu_tsr1;		/* 0xffff8285：  タイマーステータスレジスタ１	*/
volatile UWORD	mtu_tcnt1;		/* 0xffff8286：  タイマーカウンタ１				*/
volatile UWORD	mtu_tgr1a;		/* 0xffff8288：  ジェネラルレジスタ１Ａ			*/
volatile UWORD	mtu_tgr1b;		/* 0xffff828A：  ジェネラルレジスタ１Ｂ			*/
volatile UBYTE	mtu_dummy5[20];	/* 0xffff828C～9F：  ＤＵＭＭＹ	*/
/*--＜チャンネル２＞------------------------------------------------------------------------*/
volatile UBYTE	mtu_tcr2;		/* 0xffff82A0：  タイマーコントロールレジスタ２	*/
volatile UBYTE	mtu_tmdr2;		/* 0xffff82A1：  タイマーモードレジスタ２		*/
volatile UBYTE	mtu_tior2;		/* 0xffff82A2：  タイマーＩ／Ｏコントロールレジスタ２*/
volatile UBYTE	mtu_tier2;		/* 0xffff82A4：  タイマーインターラプトイネーブルレジスタ２*/
volatile UBYTE	mtu_tsr2;		/* 0xffff82A5：  タイマーステータスレジスタ２	*/
volatile UWORD	mtu_tcnt2;		/* 0xffff82A6：  タイマーカウンタ２				*/
volatile UWORD	mtu_tgr2a;		/* 0xffff82A8：  ジェネラルレジスタ２Ａ			*/
volatile UWORD	mtu_tgr2b;		/* 0xffff82AA：  ジェネラルレジスタ２Ｂ			*/
volatile UBYTE	mtu_dummy6[156];	/* 0xffff82AC～0xffff8347：  ＤＵＭＭＹ	*/

/*************************************************/
/*  割込みコントローラー・レジスター（ＩＮＴＣ） */
/*************************************************/
volatile UWORD	sh_ipra;		/* 0xffff8348： 割込み優先レベル設定レジスタＡ */
volatile UWORD	sh_iprb;		/* 0xffff834A： 割込み優先レベル設定レジスタＢ */
volatile UWORD	sh_iprc;		/* 0xffff834C：* 割込み優先レベル設定レジスタＣ */
volatile UWORD	sh_iprd;		/* 0xffff834E：割込み優先レベル設定レジスタＤ */
volatile UWORD	sh_ipre;		/* 0xffff8350：* 割込み優先レベル設定レジスタＥ */
volatile UWORD	sh_iprf;		/* 0xffff8352：割込み優先レベル設定レジスタＦ */
volatile UWORD	sh_iprg;		/* 0xffff8354：割込み優先レベル設定レジスタＧ */
volatile UWORD	sh_iprh;		/* 0xffff8356： 割込み優先レベル設定レジスタＨ */
volatile UWORD	sh_icr;			/* 0xffff8358：* 割込みコントロールレジスタ     */
volatile UWORD	sh_isr;			/* 0xffff835A：* ＩＲＱステータス・レジスタ     */
volatile UBYTE	sh_dummy0[36];	/* 0xffff835C～0xffff837F： ＤＵＭＭＹ	*/
/*****************************************************/
/*  Ｉ／Ｏポート									 */
/*****************************************************/
volatile UWORD	io_padrh;		/* 0xffff8380：  ポートＡデータレジスタＨ(注)SH7014 N/A */
volatile UWORD	io_padrl;		/* 0xffff8382：  ポートＡデータレジスタＬ		*/
volatile UWORD	pfc_paiorh;		/* 0xffff8384：  ポートＡ・ＩＯレジスタＨ		*/
volatile UWORD	pfc_paiorl;		/* 0xffff8386：  ポートＡ・ＩＯレジスタＬ		*/
volatile UWORD	pfc_pacrh;		/* 0xffff8388：  ポートＡコントロールレジスタＨ	*/
volatile UWORD	pfc_dummy0;		/* 0xffff838A：  ＤＵＭＭＹ	*/
volatile UWORD	pfc_pacrl1;		/* 0xffff838C：  ポートＡコントロールレジスタL1	*/
volatile UWORD	pfc_pacrl2;		/* 0xffff838E：  ポートＡコントロールレジスタL２*/
volatile UWORD	io_pbdr;		/* 0xffff839：  ポートＢデータレジスタ			*/
volatile UWORD	io_pcdr;		/* 0xffff839：  ポートＣデータレジスタ			*/
volatile UWORD	pfc_pbior;		/* 0xffff8394：  ポートＢ・ＩＯレジスタ			*/
volatile UWORD	pfc_pcior;		/* 0xffff8396：  ポートＣ・ＩＯレジスタ			*/
volatile UWORD	pfc_pbcr1;		/* 0xffff8398：  ポートＢコントロールレジスタ１	*/
volatile UWORD	pfc_pbcr2;		/* 0xffff839A：  ポートＢコントロールレジスタ２	*/
volatile UWORD	pfc_pccr;		/* 0xffff839C：  ポートＣコントロールレジスタ	*/
volatile UWORD	pfc_dummy1;		/* 0xffff839E～0xffff839F：  ＤＵＭＭＹ	*/
volatile UWORD	io_pddrh;		/* 0xffff83A0：  ポートＤデータレジスタＨ		*/
volatile UWORD	io_pddrl;		/* 0xffff83A2：  ポートＤデータレジスタＬ		*/
volatile UWORD	pfc_pdiorh;		/* 0xffff83A4：  ポートＤ・ＩＯレジスタＨ		*/
volatile UWORD	pfc_pdiorl;		/* 0xffff83A6：  ポートＤ・ＩＯレジスタＬ		*/
volatile UWORD	pfc_pdcrh1;		/* 0xffff83A8：  ポートＤコントロールレジスタＨ１*/
volatile UWORD	pfc_pdcrh2;		/* 0xffff83AA：  ポートＤコントロールレジスタＨ２*/
volatile UWORD	pfc_pdcrl;		/* 0xffff83AC：  ポートＤコントロールレジスタL	*/
volatile UWORD	pfc_dummy2;		/* 0xffff83AE～0xffff83AF：  ＤＵＭＭＹ	*/
volatile UWORD	io_pedr;		/* 0xffff83B0：  ポートＥデータレジスタ			*/
volatile UBYTE	io_dummy0;		/* 0xffff83B2：  ＤＵＭＭＹ	*/
volatile UBYTE	io_pfdr;		/* 0xffff83B3：  ポートＦデータレジスタ			*/
volatile UWORD	pfc_peior;		/* 0xffff83B4：  ポートＥ・ＩＯレジスタ			*/
volatile UWORD	pfc_dummy3;		/* 0xffff83B6～0xffff83B7：  ＤＵＭＭＹ	*/
volatile UWORD	pfc_pecr1;		/* 0xffff83B8：  ポートＥコントロールレジスタ１	*/
volatile UWORD	pfc_pecr2;		/* 0xffff83BA：  ポートＥコントロールレジスタ２	*/
volatile UWORD	pfc_dummy4[2];	/* 0xffff83BC～0xffff83BF：  ＤＵＭＭＹ	*/
/*****************************************************/
/*  ポートアウトプットイネーブル					 */
/*****************************************************/
volatile UWORD	poe_icsr;		/* 0xffff83C0：  入力レベルコントロール／ステータスレジスタ*/
volatile UWORD	poe_ocsr;		/* 0xffff83C2：  出力レベルコントロール／ステータスレジスタ*/
volatile UWORD	poe_dummy0[2];	/* 0xffff83C4～0xffff83C7：  ＤＵＭＭＹ	*/
volatile UWORD	pfc_ifcr;		/* 0xffff83C8：  IRQOUT機能コントロールレジスタ	*/
volatile UWORD	poe_dummy1[3];	/* 0xffff83CA～0xffff83CF：  ＤＵＭＭＹ	*/
/*****************************************************/
/*  コンペアマッチタイマ							 */
/*****************************************************/
/*--＜共通＞--------------------------------------------------------------------------------*/
volatile UWORD	cmt_cmstr;		/* 0xffff83D0：  コンペアマッチタイマースタートレジスタ*/
/*--＜チャンネル０＞------------------------------------------------------------------------*/
volatile UWORD	cmt_cmcsr0;		/* 0xffff83D2：  コンペアマッチタイマーコントロール／ステータスレジスタ*/
volatile UWORD	cmt_cmcnt0;		/* 0xffff83D4：  コンペアマッチカウンタ０		*/
volatile UWORD	cmt_cmcor0;		/* 0xffff83D6：  コンペアマッチコンスタントレジスタ０*/
/*--＜チャンネル１＞------------------------------------------------------------------------*/
volatile UWORD	cmt_cmcsr1;		/* 0xffff83D8：  コンペアマッチタイマーコントロール／ステータスレジスタ*/
volatile UWORD	cmt_cmcnt1;		/* 0xffff83DA：  コンペアマッチカウンタ０		*/
volatile UWORD	cmt_cmcor1;		/* 0xffff83DC：  コンペアマッチコンスタントレジスタ０*/
volatile UWORD	cmt_dummy1;		/* 0xffff83DE～0xffff83DF：  ＤＵＭＭＹ	*/
/*****************************************************/
/*  Ａ／Ｄ変換器									 */
/*****************************************************/
volatile UBYTE	ad_adcsr;		/* 0xffff83E0：  Ａ／Ｄコントロール／ステータスレジスタ  */
volatile UBYTE	ad_adcr;		/* 0xffff83E1：  Ａ／Ｄコントロールレジスタ    */
volatile UBYTE	ad_dummy0[14];	/* 0xffff83E2～0xffff83EF：  ＤＵＭＭＹ	*/
volatile UWORD	ad_addra;		/* 0xffff83F0：  Ａ／ＤデータレジスタＡ        */
volatile UWORD	ad_addrb;		/* 0xffff83F2：  Ａ／ＤデータレジスタＢ        */
volatile UWORD	ad_addrc;		/* 0xffff83F4：  Ａ／ＤデータレジスタＣ        */
volatile UWORD	ad_addrd;		/* 0xffff83F6：  Ａ／ＤデータレジスタＤ        */
volatile UWORD	ad_addre;		/* 0xffff83F8：  Ａ／ＤデータレジスタＥ        */
volatile UWORD	ad_addrf;		/* 0xffff83FA：  Ａ／ＤデータレジスタＦ        */
volatile UWORD	ad_addrg;		/* 0xffff83FC：  Ａ／ＤデータレジスタＧ        */
volatile UWORD	ad_addrh;		/* 0xffff83FE：  Ａ／ＤデータレジスタＨ        */

volatile UWORD	ad_addra0;		/* 0xffff8400：  Ａ／ＤデータレジスタＡ        */
volatile UWORD	ad_addrb0;		/* 0xffff8402：  Ａ／ＤデータレジスタＢ        */
volatile UWORD	ad_addrc0;		/* 0xffff8404：  Ａ／ＤデータレジスタＣ        */
volatile UWORD	ad_addrd0;		/* 0xffff8406：  Ａ／ＤデータレジスタＤ        */
volatile UWORD	ad_addra1;		/* 0xffff8408：  Ａ／ＤデータレジスタＡ        */
volatile UWORD	ad_addrb1;		/* 0xffff840a：  Ａ／ＤデータレジスタＢ        */
volatile UWORD	ad_addrc1;		/* 0xffff840c：  Ａ／ＤデータレジスタＣ        */
volatile UWORD	ad_addrd1;		/* 0xffff840e：  Ａ／ＤデータレジスタＤ        */
volatile UBYTE	ad_adcsr0;		/* 0xffff8410：  Ａ／Ｄコントロール／ステータスレジスタ  */
volatile UBYTE	ad_adcsr1;		/* 0xffff8411：  Ａ／Ｄコントロール／ステータスレジスタ  */
volatile UBYTE	ad_adcr0;		/* 0xffff8412：  Ａ／Ｄコントロールレジスタ    */
volatile UBYTE	ad_adcr1;		/* 0xffff8413：  Ａ／Ｄコントロールレジスタ    */
/********************************************/
/*  ユーザーブレークコントローラー（ＵＢＣ）*/
/********************************************/
volatile UBYTE	sh_dummy1[492];	/* 0xffff8414～0xffff85FF：  ＤＵＭＭＹ	*/
volatile UWORD	sh_ubarh;		/* 0xffff8600：ユーザーブレークアドレスレジスタＨ		*/
volatile UWORD	sh_ubarl;		/* 0xffff8602：ユーザーブレークアドレスレジスタＬ		*/
volatile UWORD	sh_ubamrh;		/* 0xffff8604：ユーザーブレークアドレスマスクレジスタＨ	*/
volatile UWORD	sh_ubamrl;		/* 0xffff8606：ユーザーブレークアドレスマスクレジスタＬ	*/
volatile UWORD	sh_ubbr;		/* 0xffff8608：ユーザーブレークバスサイクルレジスタ	*/
volatile UWORD	sh_dummy2[3];	/* 0xffff860A～0xffff860F：  ＤＵＭＭＹ	*/
/*****************************************************/
/*  ウオッチドックタイマ							 */
/*****************************************************/
volatile UBYTE	wdt_tcsr;		/* 0xffff8610：  タイマーコントロール／ステータスレジスタ */
volatile UBYTE	wdt_tcnt;		/* 0xffff8611：  タイマーカウンタ				*/
volatile UBYTE	wdt_rstcsr;		/* 0xffff8612：  リセットコントロール／ステータスレジスタ*/
volatile UBYTE	sh_dummy4[13];	/* 0xffff8613～0xffff861F：  ＤＵＭＭＹ	*/
/*******************************************/
/*  バスステートコントローラー・レジスター */
/*******************************************/
volatile UWORD	sh_bcr1;		/* 0xffff8620：  バスコントロールレジスタ１		*/
volatile UWORD	sh_bcr2;		/* 0xffff8622：  バスコントロールレジスタ２		*/
volatile UWORD	sh_wcr1;		/* 0xffff8624：  ウェイトコントロールレジスタ１	*/
volatile UWORD	sh_wcr2;		/* 0xffff8626：  ウェイトコントロールレジスタ２	*/
volatile UWORD	sh_dummy5;		/* 0xffff8628～0xffff8629：  ＤＵＭＭＹ	*/
volatile UWORD	sh_dcr;			/* 0xffff862A：  DRAMエリアコントロールレジスタ			*/
volatile UWORD	sh_rtcsr;		/* 0xffff862C：  リフレッシュタイマーコントロール／ステータスレジスタ */
volatile UWORD	sh_rtcnt;		/* 0xffff862E：  リフレッシュタイマーカウンタ			*/
volatile UWORD	sh_rtcor;		/* 0xffff8630：  リフレッシュタイムコンスタントレジスタ	*/
volatile UWORD	sh_dummy6[63];	/* 0xffff8632～0xffff86AF：  ＤＵＭＭＹ	*/
/*******************************************/
/*  ダイレクトメモリアクセスコントローラー */
/*******************************************/
volatile UDWORD	dma_dmaopr;		/* 0xffff86B0：* ＤＭＡオペレーションレジスタ   */
volatile UDWORD	dma_dummy0[3];	/* 0xffff86B4～0xffff86BF：  ＤＵＭＭＹ	*/
/*--＜チャンネル０＞------------------------------------------------------------------------*/
volatile UDWORD	dma_sar0;		/* 0xffff86C0：* ＤＭＡソースアドレスレジスタ０ */
volatile UDWORD	dma_dar0;		/* 0xffff86C4：* ＤＭＡデスティネーションアドレスレジスタ０ */
volatile UDWORD	dma_tcr0;		/* 0xffff86C8：* ＤＭＡトランスファカウントレジスタ０ */
volatile UDWORD	dma_chcr0;		/* 0xffff86CC：* ＤＭＡチャンネルコントロールレジスタ０ */
/*--＜チャンネル１＞------------------------------------------------------------------------*/
volatile UDWORD	dma_sar1;		/* 0xffff86D0：* ＤＭＡソースアドレスレジスタ１ */
volatile UDWORD	dma_dar1;		/* 0xffff86D4：* ＤＭＡデスティネーションアドレスレジスタ１ */
volatile UDWORD	dma_tcr1;		/* 0xffff86D8：* ＤＭＡトランスファカウントレジスタ１ */
volatile UDWORD	dma_chcr1;		/* 0xffff86DC：* ＤＭＡチャンネルコントロールレジスタ１ */
/*--＜チャンネル２＞------------------------------------------------------------------------*/
volatile UDWORD	dma_sar2;		/* 0xffff86E0：* ＤＭＡソースアドレスレジスタ２ */
volatile UDWORD	dma_dar2;		/* 0xffff86E4：* ＤＭＡデスティネーションアドレスレジスタ２ */
volatile UDWORD	dma_tcr2;		/* 0xffff86E8：* ＤＭＡトランスファカウントレジスタ２ */
volatile UDWORD	dma_chcr2;		/* 0xffff86EC：* ＤＭＡチャンネルコントロールレジスタ２ */
/*--＜チャンネル３＞------------------------------------------------------------------------*/
volatile UDWORD	dma_sar3;		/* 0xffff86F0：* ＤＭＡソースアドレスレジスタ３ */
volatile UDWORD	dma_dar3;		/* 0xffff86F4：* ＤＭＡデスティネーションアドレスレジスタ３ */
volatile UDWORD	dma_tcr3;		/* 0xffff86F8：* ＤＭＡトランスファカウントレジスタ３ */
volatile UDWORD	dma_chcr3;		/* 0xffff86FC：* ＤＭＡチャンネルコントロールレジスタ３ */
/**********************************************/
/*  データトランスファコントローラー（ＤＴＣ）*/
/**********************************************/
volatile UBYTE	sh_dtea;		/* 0xffff8700:  DTCイネーブルレジスタA			*/
volatile UBYTE	sh_dteb;		/* 0xffff8701:  DTCイネーブルレジスタB			*/
volatile UBYTE	sh_dtec;		/* 0xffff8702:  DTCイネーブルレジスタC			*/
volatile UBYTE	sh_dted;		/* 0xffff8703:  DTCイネーブルレジスタD			*/
volatile UBYTE	sh_dtee;		/* 0xffff8704:  DTCイネーブルレジスタE			*/
volatile UBYTE	sh_dummy7;		/* 0xffff8605:  ＤＵＭＭＹ	*/
volatile UWORD	sh_dtcsr;		/* 0xffff8706:  DTCコントロール／ステータスレジスタ	*/
volatile UWORD	sh_dtbr;		/* 0xffff8708:  DTC情報ベースレジスタ			*/
volatile UWORD	sh_dummy8[27];	/* 0xffff860A～0xffff863F:  ＤＵＭＭＹ	*/
/********************************************/
/*  キャッシュコントローラー（ＣＡＣ）		*/
/********************************************/
volatile UWORD	sh_ccr;			/* 0xffff8740:  キャッシュコントロールレジスタ	*/
#pragma section


#pragma section INT_STACK /* ロケート時のセクション名 "BINT_STACK" */
/* とりあえず、Lotus/Kurumiから貰ってきました。*/
	#define IRQ_STACK_SIZE	64
	UDWORD SciIntStackArea[IRQ_STACK_SIZE/4];
#pragma section
