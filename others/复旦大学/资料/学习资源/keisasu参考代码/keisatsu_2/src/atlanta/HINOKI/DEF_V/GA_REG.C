/*--------------------------------------------------------------------*/
/* プロジェクト : HINOKI											  */
/* ファイル名	: GA_REG.C											  */
/* 作成者		: 木元修											  */
/* 日  付		: 1998/09/19										  */
/* 概  要		: G/A用レジスター変数定義							  */
/* 修正履歴		: Jason\def\ga_reg.cよりコピー by O.Kimoto			  */
/*--------------------------------------------------------------------*/
/*
**	%W%
**	File Name:	f:\prj\eva\src\def\ga_reg.c
**	Create:	1998/02/03	By Masahiro,IIDA
**	Description: G/A Register Address Map
**	Change: 19xx/xx/xx	
*/
#include "\src\atlanta\define\product.h"

#pragma section GA_REG		/* locate section name "BGA_REG" */
volatile UWORD	ga_int_sta;			/* 0x00c00000 */
volatile UWORD	ga_int_rec;			/* 0x00c00002 */
volatile UWORD	ga_int_mask;		/* 0x00c00004 */
volatile UWORD	ga_rst;				/* 0x00c00006 */
volatile UWORD	ga_dmar;			/* 0x00C00008 */
volatile UWORD	ga_sp_req;			/* 0x00C0000A */
volatile UWORD	ga_mwr;				/* 0x00C0000C */
volatile UWORD	ga_sstart;			/* 0x00C0000E */
volatile UWORD	ga_pstart;			/* 0x00C00010 */
volatile UWORD	ga_mrd;				/* 0x00C00012 */
volatile UWORD	ga_scand;			/* 0x00C00014 */
volatile UWORD	ga_prid;			/* 0x00C00016 */
volatile UWORD	ga_tstm;			/* 0x00C00018 */
volatile UWORD	ga_pmd;				/* 0x00C0001A */
volatile UWORD	ga_dummy0[114];		/* 0x00C00018～FF */
volatile UWORD	ga_tmr0;			/* 0x00C00100 */
volatile UWORD	ga_tmr1;			/* 0x00C00102 */
volatile UWORD	ga_rmr;				/* 0x00C00104 */
volatile UWORD	ga_tph_reg;			/* 0x00C00106 */
volatile UWORD	ga_tphlmrg;			/* 0x00C00108 */
volatile UWORD	ga_swr;				/* 0x00C0010A */
volatile UWORD	ga_strm;			/* 0x00C0010C */
volatile UWORD	ga_dummy1[121];		/* 0x00C0010E～FF */
volatile UWORD	ga_prtc;			/* 0x00C00200 */
volatile UWORD	ga_cmdr1;			/* 0x00C00202 */
volatile UWORD	ga_cmdr2;			/* 0x00C00204 */
volatile UWORD	ga_stsr1;			/* 0x00C00206 */
volatile UWORD	ga_stsr2;			/* 0x00C00208 */
volatile UWORD	ga_prs;				/* 0x00C0020A */
volatile UWORD	ga_print_end;		/* 0x00C0020C */
volatile UWORD	ga_page_end;		/* 0x00C0020E */
volatile UWORD	ga_sub_rdc1;		/* 0x00C00210 */
volatile UWORD	ga_sub_rdc2;		/* 0x00C00212 */
volatile UWORD	ga_line_rdc1;		/* 0x00C00214 */
volatile UWORD	ga_line_rdc2;		/* 0x00C00216 */
volatile UWORD	ga_line_rdc3;		/* 0x00C00218 */
volatile UWORD	ga_line_rdc4;		/* 0x00C0021A */
volatile UWORD	ga_line_rdc5;		/* 0x00C0021C */
volatile UWORD	ga_line_rdc6;		/* 0x00C0021E */
volatile UWORD	ga_left_mrg;		/* 0x00C00220 */
volatile UWORD	ga_dummy2[111];		/* 0x00C00222～2FF */
volatile UWORD	ga_pgbdr;			/* 0x00C00300 */
volatile UWORD	ga_pgadr;			/* 0x00C00302 */

#pragma section
