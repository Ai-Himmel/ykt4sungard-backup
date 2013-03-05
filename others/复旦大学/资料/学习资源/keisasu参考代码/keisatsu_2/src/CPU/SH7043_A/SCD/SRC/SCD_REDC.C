/************************************************************************
*	System		: POPLAR
*	File Name	: SCD_REDC.C
*	Author		: Y.Suzuki
*	Date		: 1996/12/12
*	Description	:
*	Maintenance	:
*
*	Copyright (C) 1996 Murata Machienry,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysdoc.h"
#include "\src\atlanta\define\sysdblk.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd_def.h"
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\define\scdpro.h"
#include "\src\cpu\sh7043_a\scd\ext_v\scd_data.h"
#include "\src\cpu\sh7043_a\scd\ext_v\reductbl.h"
#else
#include "\src\atlanta\scd\define\scd_def.h"
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\define\scdpro.h"
#include "\src\atlanta\scd\ext_v\scd_data.h"
#include "\src\atlanta\scd\ext_v\reductbl.h"
#endif

#if(0)		/*	By Y.Suzuki 1997/03/07	*/
//
///*************************************************************************
//	module		:[ü–§“xƒ‚[ƒhƒpƒ‰ƒ[ƒ^•ÏŠ·]
//	function	:[
//		1.
//	]
//	return		:[	‚m‚n‚q‚l‚`‚k	F‚P
//					‚e‚h‚m‚d		F‚Q
//					‚r‚e‚h‚m‚d		F‚S
//					‚g‚e‚h‚m‚d		F‚S POPLAR:R16 * 15.4l/mm
//	]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH2]
//	language	:[SHC]
//	keyword		:[SCD]
//	date		:[1995/11/21]
//	author		:[—é–Øˆè“ñ]
//*************************************************************************/
//UBYTE ModePara(UBYTE mode)
//{
//	UBYTE para;
//
//	switch(mode){
//	case SYS_FINE:
//	case SYS_GRAY16:
//	case SYS_GRAY16_SEP:
//	case SYS_GRAY64:
//	case SYS_GRAY64_SEP:
//		para = 2;
//		break;
//	case SYS_SFINE:
//		para = 4;
//		break;
//	case SYS_HFINE:
//		para = 5;
//		break;
//	default:	/* NORMAL */
//	     para = 1;
//	     break;
//	}
//	return(para);
//}
//
//
///*************************************************************************
//	module		:[ƒ‚[ƒh•ÏX‚É‚æ‚ék¬A•›‘–¸ƒXƒLƒbƒvƒ‚[ƒhŠl“¾]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH2]
//	language	:[SHC]
//	keyword		:[SCD]
//	date		:[1995/11/21]
//	author		:[—é–Øˆè“ñ]
//*************************************************************************/
///* get mode skip parameter */
//UBYTE GetModeSkip(UBYTE src_mode,UBYTE dst_mode)
//{
//	UBYTE    src,dst;
//
//	ReductionFromHfine = 0;
//	src = ModePara(src_mode);
//	dst = ModePara(dst_mode);
//	if(src == 4 && dst == 2) {     /* SFINE to FINE */
//	   dst++;
//	}
//	else if(src == 5 && dst != 5) {
//		ReductionFromHfine = 1;
//		src = 4;/* •›‘–¸‚Ìk¬‚ÍAƒX[ƒp[ƒtƒ@ƒCƒ“‚Æ“¯‚¶ */
//		if(dst == 2) {
//			dst++;
//		}
//	}
//	return((UBYTE)(src - dst));
//}
//
//
//
///*************************************************************************
//	module		:[k¬ƒpƒ^[ƒ“ƒZƒbƒg]
//	function	:[
//		1.
//	]
//	return		:[	‚a‚S|„‚`‚SF‚P
//					‚`‚R|„‚a‚SF‚Q
//					‚`‚R|„‚`‚SF‚R
//					k¬‚È‚µ	F‚O
//					Œ´e•‚Ìk¬‚È‚µAƒ‚[ƒh•ÏX‚É‚æ‚éå‘–¸‚Ìk¬‚ ‚èF‚S By Y.Suzuki 1997/01/17
//	]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH2]
//	language	:[SHC]
//	keyword		:[SCD]
//	date		:[1995/11/21]
//	author		:[—é–Øˆè“ñ]
//*************************************************************************/
//UBYTE SetReduce(struct MEM_DocParamData_t *src,struct MEM_DocParamData_t *dst)
//{
//	UBYTE  flag;
//	/* ‚gQ‚e‚h‚m‚d‚Ìˆ— */
//
//	switch(src->Size){
//	case SYS_DOCUMENT_A4_SIZE:
//		flag = 0;
//		break;
//	case SYS_DOCUMENT_B4_SIZE:
//		if(dst->Size == SYS_DOCUMENT_A4_SIZE)
//			flag = 3;
//		else
//			flag = 0;
//		break;
//	case SYS_DOCUMENT_A3_SIZE:
//		if(dst->Size == SYS_DOCUMENT_A4_SIZE)
//			flag = 1;
//		else if(dst->Size == SYS_DOCUMENT_B4_SIZE)
//			flag = 2;
//		else
//			flag = 0;
//		break;
//	default:
//		flag = 0;
//		break;
//	}
//	if (!flag && ReductionFromHfine) {/*	Œ´e•‚Ìk¬‚È‚µAƒ‚[ƒh•ÏX‚É‚æ‚éå‘–¸‚Ìk¬‚ ‚è	*/
//		flag = 6;
//	}
//	return(flag);
//}
#endif 		/*	By Y.Suzuki 1997/03/07	*/


/*************************************************************************
	module		:[ƒƒ‚ƒŠ‘—Må‘–¸‚Ìƒ\ƒtƒgk¬]
	function	:[
		ƒƒ‚ƒŠ“à‚É‚‚‚Å’~Ï‚³‚ê‚éB
		1.	‚`‚R[„‚a‚S
			‚`‚R|„‚`‚S
			‚a‚S|„‚`‚S
			‚g‚e‚h‚m‚d|„‚m‚n‚q‚lC‚r‚e‚h‚m‚dC‚e‚h‚m‚di“ ‚q‚P‚U|„‚q‚Wj
		2.‚’‚Œƒoƒbƒtƒ@‚©‚ç‚’‚Œ‚ğæ‚èo‚µAk¬—¦‚É‚æ‚èk¬‚µ‚’‚Œƒoƒbƒtƒ@‚É–ß‚·B
		3.æ‚èo‚µ‚Ä‚«‚½‚’‚Œ‚Ì‘˜a‚ğk¬ŒãA‘O‚Ìk¬Œã‚Ì’l‚Æ‚Ì·‚©‚çk¬Œã‚Ì‚’‚Œ‚ğZoB
	]
	return		:[]
	common		:[]
	condition	:[]
	comment		:[
					STIGR-007 ‚Ì‹K’è‚É‚æ‚èk¬—¦•ÏX By Y.Suzuki 1996/12/12
					Œ´e•‚Ìk¬‚Æ‚g‚e‚h‚m‚d‚©‚ç‚Ìƒ‚[ƒh•ÏX‚ª“¯‚É”­¶‚µ‚½ê‡A“¯‚Éˆ—‚·‚é
	]
	machine		:[SH2]
	language	:[SHC]
	keyword		:[SCD]
	date		:[1995/11/21]
	author		:[—é–Øˆè“ñ]
*************************************************************************/
/* static UBYTE SCD_DBG_OldRlSize = 0;*/
void RedLineIntRom(struct CdcBlk_t *Sddp,struct WorkBuf_t *rl_buf,UBYTE reduc/* k¬ƒpƒ^[ƒ“ */)
{
	DWORD	mul_value;
	UWORD	new_rl_size;			/* k¬‘OAŒã‚Ìrl_size‹L‰¯ */
	UWORD	new_rl_cnt;				/* k¬Œã‚Ìrl_size‚ÌƒJƒEƒ“ƒ^ */
	DWORD	old_rl_cnt;				/* k¬‘O‚Ìrl_size‚ÌƒJƒEƒ“ƒ^ A3->‚Ì‚Æ‚«word‚Å‚ÍÌÛ°‚·‚é */
	UWORD	mul_data,div_data;
	UWORD	rl_data;				/* k¬Œã‚Ìrl */
/*	UWORD	read_pointer;			 rlƒoƒbƒtƒ@‚©‚ç“Ç‚İo‚µ—p */
	UWORD	write_pointer;			/* rlƒoƒbƒtƒ@‚©‚ç‘‚«‚İ—p */
	UWORD	update_rl;
	UWORD	pre_data;				/* ‘O‚ÉƒZƒbƒg‚µ‚½k¬Œã‚Ì‚q‚k‚ÌƒTƒCƒY */
	UWORD	old_data;				/* ‘O‚ÉƒŠ[ƒh‚µ‚½k¬‘O‚Ì‚q‚k‚ÌƒTƒCƒY */

	UBYTE	col,pre_col;	/* ¾¯Ä‚·‚érl‚Ì¶×°,ˆê‚Â‘O‚Ì¶×° */
	UBYTE	byte_data;

	/* GetRL */
	UWORD	firstbyte;
	UWORD	secondbyte;
	UWORD	rl;
	/* PutRL */
	UWORD	word_data;

	mul_value = 0;
	mul_data = 0;
	div_data = 0;
	new_rl_size = 0;
	old_rl_cnt = 0;
	new_rl_cnt = 0;
/*	read_pointer = 0;*/
	write_pointer = 0;
	update_rl = 0;
	col = 0;
	pre_col = 0;
	byte_data = 0;
	pre_data = 0;
	old_data = 0;

	SCD_DBG_OldRlSize = 0;/*	By Y.Suzuki 1997/02/08	*/

	/** ‚Pƒ‰ƒCƒ“‚ÌƒCƒ[ƒWƒTƒCƒY‚ğk¬‚·‚é */
	mul_value =  Sddp->Img_Size;
	switch(reduc) {
	case A3_TO_A4:
	/*	mul_data = 27;
	**	div_data = 38;*/
		mul_data = 22;	/*	By Y.Suzuki 1997/09/26	*/
		div_data = 32;
		break;
	case A3_TO_B4:
		mul_data = 32;
		div_data = 38;
	/*	mul_data = 27;
	**	div_data = 32;*/
		break;
	case B4_TO_A4:
	/*	mul_data = 27;
	**	div_data = 32;*/
		mul_data = 26;	/*	By Y.Suzuki 1997/09/26	*/
		div_data = 32;
		break;
	case P_A3_TO_A4:
		mul_data = 26;
		div_data = 38;
		break;
	case P_B4_TO_A4:
		mul_data = 26;
		div_data = 32;
		break;
	case HFINE_TO_OTHER:
		mul_data = 20;
		div_data = 40;
		ReductionFromHfine = 0;/* ’P‚È‚éå‘–¸‚Ì‚İ‚Ìk¬ */
		break;
	/* ƒnƒCƒp[ƒtƒ@ƒCƒ“‚ÌŒ´e‚Åƒ‚[ƒh•ÏXAk¬‚ª“¯‚Ìê‡ k¬—¦A–¢’è */
	case HFA3_TO_A4_OTHER:
		mul_data = 11;
		div_data = 32;
		break;
	case HFA3_TO_B4_OTHER:
		mul_data = 13;
		div_data = 32;
		break;
	case HFB4_TO_A4_OTHER:
		mul_data = 13;
		div_data = 32;
		break;
	default:
		new_rl_size = 0;
	}
	if(ReductionFromHfine) {/*	ƒnƒCƒp[ƒtƒ@ƒCƒ“‚©‚ç‚Ìƒ‚[ƒh•ÏX‚ ‚è */
		div_data *= 2;
	}
	new_rl_size = (UWORD)((mul_value * mul_data)/div_data);	/* mul_value == Src.Img_Size */
	rl_buf->Cout = 0;										/* RL Buffer Read Byte Pointer ‰Šú‰» */
	/*-------------------------------------------------*/
	/**ƒ‰ƒCƒ“æ“ª‚Ì‚q‚k‚ğk¬Œã¤‚q‚kƒoƒbƒtƒ@‚ÉŠi”[‚·‚é */
	/*-------------------------------------------------*/
	/* old_data = GetRLR(rl_buf,read_pointer);*/
	firstbyte = *(rl_buf->Data + rl_buf->Cout);
	col = (UBYTE)(firstbyte & 0x0040);	/*	White:0  Black:0x0040	*/
	if ((firstbyte & 0x0080) != 0x0080) {
		rl_buf->Cout ++;
		rl = firstbyte & 0x003F;
	}
	else {
		rl_buf->Cout ++;
		secondbyte = *(rl_buf->Data + rl_buf->Cout);
		rl = ((firstbyte & 0x003F) << 8) + secondbyte;
		rl_buf->Cout ++;
	}

	old_data = rl;

	old_rl_cnt += (DWORD)old_data;
	update_rl = (UWORD)((old_rl_cnt * mul_data)/div_data);
	rl_data = update_rl - new_rl_cnt;
	new_rl_cnt = update_rl;
	pre_data = rl_data;
/*	PutRLR(rl_buf,write_pointer,rl_data,0);* k¬Œã‚Ìrl‚ğRLƒoƒbƒtƒ@‚ÉÄƒZƒbƒg */
	col = 0;
	byte_data = 0;
	word_data = 0;

	if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
		SCD_NgRl = 1;
	}
	if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
		SCD_NgRl = 2;
	}
	if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
		return;
	}
	if (rl_data <= 0x003F) {
		if (col == WHITE) {
			byte_data = (UBYTE)rl_data;
			*(rl_buf->Data + write_pointer) = byte_data;
			write_pointer ++;
		}
		else {
			word_data = rl_data | 0x0040;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) = byte_data;
			write_pointer ++;
		}
	}
	else {
		if (col == WHITE) {
			rl_data |= 0x8000;
			word_data = rl_data & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
			byte_data = (UBYTE)(rl_data & 0x00FF);
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
		}
		else {
			rl_data |= 0xC000;
			word_data = rl_data & 0xFF00;
			word_data >>= 8;
			byte_data = (UBYTE)word_data;
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
			byte_data = (UBYTE)(rl_data & 0x00FF);
			*(rl_buf->Data + write_pointer) =  byte_data;
			write_pointer ++;
		}
	}


	rl_data = 0;
	while(new_rl_size > new_rl_cnt) {						/** ‚c‚r‚s‚ÌƒTƒCƒY‚É‚È‚é‚Ü‚Å‚q‚k‚ğk¬‚·‚é */
		/*-------------------------------------------------------*/
		/**ˆêƒ‰ƒCƒ“•ª‚Ì‚q‚k‚ğk¬‚µ‚È‚ª‚ç¤‚q‚kƒoƒbƒtƒ@‚ÉŠi”[‚·‚é */
		/*-------------------------------------------------------*/
		/* RLƒoƒbƒtƒ@‚©‚çRLæ‚èo‚µ	*/
	/*	old_data = GetRLR(rl_buf,read_pointer);*/
		firstbyte = *(rl_buf->Data + rl_buf->Cout);
		col = (UBYTE)(firstbyte & 0x0040);	/*	White:0  Black:0x0040	*/
		if ((firstbyte & 0x0080) != 0x0080) {
			rl_buf->Cout ++;
			rl = firstbyte & 0x003F;
		}
		else {
			rl_buf->Cout ++;
			secondbyte = *(rl_buf->Data + rl_buf->Cout);
			rl = ((firstbyte & 0x003F) << 8) + secondbyte;
			rl_buf->Cout ++;
		}

		old_data = rl;
		old_rl_cnt += (DWORD)old_data;
		if ((UWORD)old_rl_cnt > Sddp->Img_Size) {
			SCD_DBG_OldRlSize = 1;/*	By Y.Suzuki 1997/02/08	*/
		}
		update_rl = (UWORD)((old_rl_cnt * mul_data)/div_data);
		if(update_rl != new_rl_cnt) {/* k¬Œã‚Ìrl”­¶ */
			rl_data = update_rl - new_rl_cnt;
			/* k¬‘O‚Ìrl¶×°î•ñ‚Ìæ“¾ */
			if(old_data < 64) {/* rl‚ª‚U‚RˆÈ‰º */
				byte_data = *(rl_buf->Data + (rl_buf->Cout - 1));
			}
			else {/* if(old_data <= MH_MAKEUP_MAX) @* rl‚ª‚Q‚T‚U‚OˆÈ‰º */
				byte_data = *(rl_buf->Data + (rl_buf->Cout - 2));
			}
			new_rl_cnt = update_rl;/* k¬Œã‚q‚kXV */
			col = (UBYTE)(byte_data & 0x40);
			/* ‘O‚ÉƒZƒbƒg‚µ‚½‚’‚Œ‚Æ“¯‚¶F‚© */
			if(pre_data < 64) {
				byte_data = *(rl_buf->Data + (write_pointer - 1));
			}
			else { /*if(pre_data <= MH_MAKEUP_MAX) */
				byte_data = *(rl_buf->Data + (write_pointer - 2));
			}
			pre_col = (UBYTE)(byte_data & 0x0040);
			if(col == pre_col) {/* ‘O‚ÉƒZƒbƒg‚µ‚½‚’‚Œ‚Æ“¯‚¶F */
				rl_data += pre_data;
				if(pre_data < 64) {
					write_pointer--;
				}
				else {
					write_pointer -= 2;
				}
			}
			pre_data = rl_data;
		/*	PutRLR(rl_buf,write_pointer,rl_data,col);@* k¬Œã‚Ìrl‚ğRLƒoƒbƒtƒ@‚ÉÄƒZƒbƒg */
			byte_data = 0;
			word_data = 0;

			if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
				SCD_NgRl = 1;
			}
			if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
				SCD_NgRl = 2;
			}
			if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
				return;
			}
			if (rl_data <= 0x003F) {
				if (col == WHITE) {
					byte_data = (UBYTE)rl_data;
					*(rl_buf->Data + write_pointer) = byte_data;
					write_pointer ++;
				}
				else {
					word_data = rl_data | 0x0040;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) = byte_data;
					write_pointer ++;
				}
			}
			else {
				if (col == WHITE) {
					rl_data |= 0x8000;
					word_data = rl_data & 0xFF00;
					word_data >>= 8;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
					byte_data = (UBYTE)(rl_data & 0x00FF);
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
				}
				else {
					rl_data |= 0xC000;
					word_data = rl_data & 0xFF00;
					word_data >>= 8;
					byte_data = (UBYTE)word_data;
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
					byte_data = (UBYTE)(rl_data & 0x00FF);
					*(rl_buf->Data + write_pointer) =  byte_data;
					write_pointer ++;
				}
			}


			rl_data = 0;
			col = 0;
			pre_col = 0;
		}
	}
	if (new_rl_cnt > new_rl_size) {
		SCD_DBG_RLOVER = 4;
	}
	/*	å‘–¸‚É–‚½‚È‚¢‚q‚k‚ğƒZƒbƒg‚·‚é By Y.Suzuki 1997/09/26	*/
	if ((reduc == A3_TO_A4) || (reduc == B4_TO_A4)) {
		col = 0;
		if(SCD_TxMode == SYS_HFINE) {/** ƒnƒCƒp[ƒtƒ@ƒCƒ“‚È‚çå‘–¸ƒhƒbƒg”‚Q”{ */
			rl_data = SYS_A4_LINE * 2 - new_rl_size;
		}
		else {
			rl_data = SYS_A4_LINE - new_rl_size;
		}
		if(pre_data < 64) {
			byte_data = *(rl_buf->Data + (write_pointer - 1));
		}
		else { /*if(pre_data <= MH_MAKEUP_MAX) */
			byte_data = *(rl_buf->Data + (write_pointer - 2));
		}
		pre_col = (UBYTE)(byte_data & 0x0040);
		if(col == pre_col) {/* ‘O‚ÉƒZƒbƒg‚µ‚½‚’‚Œ‚Æ“¯‚¶F */
			rl_data += pre_data;
			if(pre_data < 64) {
				write_pointer--;
			}
			else {
				write_pointer -= 2;
			}
		}
		byte_data = 0;
		word_data = 0;

		if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
			SCD_NgRl = 1;
		}
		if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
			SCD_NgRl = 2;
		}
		if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
			return;
		}
		if (rl_data <= 0x003F) {
			if (col == WHITE) {
				byte_data = (UBYTE)rl_data;
				*(rl_buf->Data + write_pointer) = byte_data;
				write_pointer ++;
			}
			else {
				word_data = rl_data | 0x0040;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) = byte_data;
				write_pointer ++;
			}
		}
		else {
			if (col == WHITE) {
				rl_data |= 0x8000;
				word_data = rl_data & 0xFF00;
				word_data >>= 8;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
				byte_data = (UBYTE)(rl_data & 0x00FF);
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
			}
			else {
				rl_data |= 0xC000;
				word_data = rl_data & 0xFF00;
				word_data >>= 8;
				byte_data = (UBYTE)word_data;
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
				byte_data = (UBYTE)(rl_data & 0x00FF);
				*(rl_buf->Data + write_pointer) =  byte_data;
				write_pointer ++;
			}
		}
	}
}


#if(0)	/*	By Y.Suzuki 1997/04/04	*/
** /*************************************************************************
** 	module		:[ƒƒ‚ƒŠ‘—M‚g‚e‚h‚m‚d‚©‚ç‚Ìƒ‚[ƒh•ÏX‚É‚æ‚éå‘–¸‚Ìƒ\ƒtƒgk¬]
** 	function	:[
** 		1.‚g‚e‚h‚m‚d|„‚m‚n‚q‚lC‚r‚e‚h‚m‚dC‚e‚h‚m‚di“ ‚q‚P‚U|„‚q‚Wj
** 			Œ´e•‚Ìk¬‚ª‚È‚­‚Ä‚à‚T‚O“å‘–¸‚ğk¬‚·‚éB
** 		2.‚’‚Œƒoƒbƒtƒ@‚©‚ç‚’‚Œ‚ğæ‚èo‚µAk¬—¦‚É‚æ‚èk¬‚µ‚’‚Œƒoƒbƒtƒ@‚É–ß‚·B
** 		3.æ‚èo‚µ‚Ä‚«‚½‚’‚Œ‚Ì‘˜a‚ğk¬ŒãA‘O‚Ìk¬Œã‚Ì’l‚Æ‚Ì·‚©‚çk¬Œã‚Ì‚’‚Œ‚ğZoB
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[
** 					STIGR-007 ‚Ì‹K’è‚É‚æ‚èk¬—¦•ÏX By Y.Suzuki 1996/12/12
** 	]
** 	machine		:[SH2]
** 	language	:[SHC]
** 	keyword		:[SCD]
** 	date		:[1995/11/21]
** 	author		:[—é–Øˆè“ñ]
** *************************************************************************/
//void RedLine50IntRom(struct CdcBlk_t *Sddp,struct WorkBuf_t *rl_buf,UBYTE reduc/* k¬ƒpƒ^[ƒ“ */)
//{
//	DWORD	mul_value;
//	UWORD	new_rl_size;			/* k¬‘OAŒã‚Ìrl_size‹L‰¯ */
//	UWORD	new_rl_cnt;				/* k¬Œã‚Ìrl_size‚ÌƒJƒEƒ“ƒ^ */
//	DWORD	old_rl_cnt;				/* k¬‘O‚Ìrl_size‚ÌƒJƒEƒ“ƒ^ A3->‚Ì‚Æ‚«word‚Å‚ÍÌÛ°‚·‚é */
//	UWORD	mul_data,div_data;
//	UWORD	rl_data;				/* k¬Œã‚Ìrl */
//	UWORD	read_pointer;			/* rlƒoƒbƒtƒ@‚©‚ç“Ç‚İo‚µ—p */
//	UWORD	write_pointer;			/* rlƒoƒbƒtƒ@‚©‚ç‘‚«‚İ—p */
//	UWORD	update_rl;
//	UWORD	pre_data;				/* ‘O‚ÉƒZƒbƒg‚µ‚½k¬Œã‚Ì‚q‚k‚ÌƒTƒCƒY */
//	UWORD	old_data;				/* ‘O‚ÉƒŠ[ƒh‚µ‚½k¬‘O‚Ì‚q‚k‚ÌƒTƒCƒY */
//
//	UBYTE	col,pre_col;	/* ¾¯Ä‚·‚érl‚Ì¶×°,ˆê‚Â‘O‚Ì¶×° */
//	UBYTE	byte_data;
//
//	/* GetRL */
//	UWORD	firstbyte;
//	UWORD	secondbyte;
//	UWORD	rl;
//	UWORD	color;
//	UBYTE	detect_makeup_max;
//	/* PutRL */
//	UWORD	word_data, temp;
////	UBYTE	next_rl;	/*	MH_MAKEUP_MAX‚Ìrl‚ª‚«‚½ON‚Æ‚È‚é	*/
//
//	mul_value = 0;
//	mul_data = 0;
//	div_data = 0;
//	new_rl_size = 0;
//	old_rl_cnt = 0;
//	new_rl_cnt = 0;
////	read_pointer = 0;
//	write_pointer = 0;
//	update_rl = 0;
//	col = 0;
//	pre_col = 0;
//	byte_data = 0;
//	pre_data = 0;
//	old_data = 0;
////
//	/** ‚Pƒ‰ƒCƒ“‚ÌƒCƒ[ƒWƒTƒCƒY‚ğk¬‚·‚é */
//	mul_value =  Sddp->Img_Size;
//	switch(reduc) {
//	case A3_TO_A4:
//	/*	mul_data = 27;
//	**	div_data = 38; */
//		mul_data = 22;
////		div_data = 32;
//		break;
//	case A3_TO_B4:
//	/*	mul_data = 32;
//	**	div_data = 38;*/
//		mul_data = 27;
//		div_data = 32;
//		break;
////	case B4_TO_A4:
//	/*	mul_data = 27;
//	**	div_data = 32;*/
//		mul_data = 26;
//		div_data = 32;
//		break;
//	case P_A3_TO_A4:
//		mul_data = 26;
////		div_data = 38;
//		break;
//	case P_B4_TO_A4:
//		mul_data = 26;
//		div_data = 32;
//		break;
//	case HFINE_TO_OTHER:
//		mul_data = 20;
////		div_data = 40;
//		break;
//	/* ƒnƒCƒp[ƒtƒ@ƒCƒ“‚ÌŒ´e‚Åƒ‚[ƒh•ÏXAk¬‚ª“¯‚Ìê‡ k¬—¦A–¢’è */
//	case HFA3_TO_A4_OTHER:
//		mul_data = 11;
//		div_data = 32;
//		break;
//	case HFA3_TO_B4_OTHER:
////		mul_data = 13;
//		div_data = 32;
//		break;
//	case HFB4_TO_A4_OTHER:
//		mul_data = 13;
//		div_data = 32;
//		break;
//	default:
////		new_rl_size = 0;
//	}
//	new_rl_size = (mul_value * mul_data)/div_data;	/* mul_value == Src.Img_Size */
//	rl_buf->Cout = 0;										/* RL Buffer Read Byte Pointer ‰Šú‰» */
//	/*-------------------------------------------------*/
//	/**ƒ‰ƒCƒ“æ“ª‚Ì‚q‚k‚ğk¬Œã¤‚q‚kƒoƒbƒtƒ@‚ÉŠi”[‚·‚é */
//	/*-------------------------------------------------*/
//	/* old_data = GetRLR(rl_buf,read_pointer); */
////	while(1) {
//		firstbyte = *(rl_buf->Data + rl_buf->Cout);
//		col = firstbyte & 0x0040;	/*	White:0  Black:0x0040	*/
//		if ((firstbyte & 0x0080) != 0x0080) {
//			rl_buf->Cout ++;
//			rl = firstbyte & 0x003F;
//			break;	/*	return (RL);	*/
//		}
////		else {
//			rl_buf->Cout ++;
//			secondbyte = *(rl_buf->Data + rl_buf->Cout);
//			rl = ((firstbyte & 0x003F) << 8) + secondbyte;
//			rl >>= 2;
//			rl_buf->Cout ++;
//			if (rl >= MH_MAKEUP_MAX) {/* ‚q‚kƒTƒCƒY2560 ‚Ìê‡ */
//				firstbyte = *(rl_buf->Data + rl_buf->Cout);
////				if (col == (firstbyte & 0x0040)) {
//					detect_makeup_max = 1;
//					continue;
//				}
//				else {
//					break;		/*	return(RL)	*/
//				}
//			}
////			break;		/*	return(RL)	*/
//		}
//	}
//	if (detect_makeup_max) {
//		old_data = MH_MAKEUP_MAX + rl;
//	}
//	else {
//		old_data = rl;
////	}
//
//
//	old_rl_cnt += (DWORD)old_data;
//	update_rl = (old_rl_cnt * mul_data)/div_data;
//	rl_data = update_rl - new_rl_cnt;
//	new_rl_cnt = update_rl;
//	pre_data = rl_data;
//	PutRLR(rl_buf,write_pointer,rl_data,0);	* k¬Œã‚Ìrl‚ğRLƒoƒbƒtƒ@‚ÉÄƒZƒbƒg */
//	col = 0;
//	byte_data = 0;
//	word_data = 0;
//	next_rl = 0;
//
//	if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
//		SCD_NgRl = 1;
//	}
////	if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
//		SCD_NgRl = 2;
//	}
//	if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
//		return;
//	}
//	while(1) {
//		if (rl_data <= 0x003F) {
////			next_rl = 0;
//			if (col == WHITE) {
//				byte_data = (UBYTE)rl_data;
//				*(rl_buf->Data + write_pointer) = byte_data;
//				write_pointer ++;
//			}
//			else {
//				word_data = rl_data | 0x0040;
////				byte_data = (UBYTE)word_data;
//				*(rl_buf->Data + write_pointer) = byte_data;
//				write_pointer ++;
//			}
//			break;
//		}
//		else {
//			if (rl_data >= MH_MAKEUP_MAX) {
////				temp = MH_MAKEUP_MAX;
//				rl_data = rl_data - MH_MAKEUP_MAX;
//				next_rl = 1;
//			}
//			else {
//				next_rl = 0;
//				temp = rl_data;
//			}
////			temp <<= 2;
//			if (col == WHITE) {
//				temp |= 0x8000;
//				word_data = temp & 0xFF00;
//				word_data >>= 8;
//				byte_data = (UBYTE)word_data;
//				*(rl_buf->Data + write_pointer) =  byte_data;
//				write_pointer ++;
////				byte_data = (UBYTE)(temp & 0x00FF);
//				*(rl_buf->Data + write_pointer) =  byte_data;
//				write_pointer ++;
//			}
//			else {
//				temp |= 0xC000;
//				word_data = temp & 0xFF00;
//				word_data >>= 8;
////				byte_data = (UBYTE)word_data;
//				*(rl_buf->Data + write_pointer) =  byte_data;
//				write_pointer ++;
//				byte_data = (UBYTE)(temp & 0x00FF);
//				*(rl_buf->Data + write_pointer) =  byte_data;
//				write_pointer ++;
//			}
//			if (next_rl && rl_data) {
////				continue;
//			}
//			else {
//				break;
//			}
//		}
//	}
//
////
//	rl_data = 0;
//	while(new_rl_size > new_rl_cnt) {						/** ‚c‚r‚s‚ÌƒTƒCƒY‚É‚È‚é‚Ü‚Å‚q‚k‚ğk¬‚·‚é */
//		/*-------------------------------------------------------*/
//		/**ˆêƒ‰ƒCƒ“•ª‚Ì‚q‚k‚ğk¬‚µ‚È‚ª‚ç¤‚q‚kƒoƒbƒtƒ@‚ÉŠi”[‚·‚é */
//		/*-------------------------------------------------------*/
//		/* RLƒoƒbƒtƒ@‚©‚çRLæ‚èo‚µ	*/
//		/* old_data = GetRLR(rl_buf,read_pointer);*/
////		detect_makeup_max = 0;
//		while(1) {
//			firstbyte = *(rl_buf->Data + rl_buf->Cout);
//			col = firstbyte & 0x0040;	/*	White:0  Black:0x0040	*/
//			if ((firstbyte & 0x0080) != 0x0080) {
//				rl_buf->Cout ++;
//				rl = firstbyte & 0x003F;
//				break;	/*	return (RL);	*/
////			}
//			else {
//				rl_buf->Cout ++;
//				secondbyte = *(rl_buf->Data + rl_buf->Cout);
//				rl = ((firstbyte & 0x003F) << 8) + secondbyte;
//				rl >>= 2;
//				rl_buf->Cout ++;
//				if (rl >= MH_MAKEUP_MAX) {/* ‚q‚kƒTƒCƒY2560 ‚Ìê‡ */
////					firstbyte = *(rl_buf->Data + rl_buf->Cout);
//					if (col == (firstbyte & 0x0040)) {
//						detect_makeup_max = 1;
//						continue;
//					}
//					else {
//						break;		/*	return(RL)	*/
//					}
////				}
//				break;		/*	return(RL)	*/
//			}
//		}
//		if (detect_makeup_max) {
//			old_data = MH_MAKEUP_MAX + rl;
//		}
//		else {
////			old_data = rl;
//		}
//
//
//		old_rl_cnt += (DWORD)old_data;
//		update_rl = (old_rl_cnt * mul_data)/div_data;
//		if(update_rl != new_rl_cnt) {/* k¬Œã‚Ìrl”­¶ */
//			rl_data = update_rl - new_rl_cnt;
////			/* rl¶×°î•ñ‚Ìæ“¾ */
//			byte_data = *(rl_buf->Data + (read_pointer - 2));
//			if(old_data < 64) {/* rl‚ª‚U‚RˆÈ‰º */
//				byte_data = *(rl_buf->Data + (read_pointer - 1));
//			}
//			if(byte_data & 0x40) {/* • */
//				col = 1;
//			}
////			new_rl_cnt = update_rl;
//			/* ‘O‚ÉƒZƒbƒg‚µ‚½‚’‚Œ‚Æ“¯‚¶F‚© */
//			byte_data = *(rl_buf->Data + (write_pointer - 2));
//			if(pre_data < 64) {
//				byte_data = *(rl_buf->Data + (write_pointer - 1));
//			}
//			if(byte_data & 0x0040) {
//				pre_col = 1;
////			}
//			if(col == pre_col) {/* ‘O‚ÉƒZƒbƒg‚µ‚½‚’‚Œ‚Æ“¯‚¶F */
//				rl_data += pre_data;
//				write_pointer--;
//				if(pre_data > 63) {
//					write_pointer--;
//				}
//			}
////			pre_data = rl_data;
//			/* PutRLR(rl_buf,write_pointer,rl_data,col);* k¬Œã‚Ìrl‚ğRLƒoƒbƒtƒ@‚ÉÄƒZƒbƒg */
//			byte_data = 0;
//			word_data = 0;
//			next_rl = 0;
//
//			if (rl_data > 4864) {/*	By Y.Suzuki 1997/02/08	*/
//				SCD_NgRl = 1;
////			}
//			if (rl_data & 0x8000) {/*	By Y.Suzuki 1997/02/27	*/
//				SCD_NgRl = 2;
//			}
//			if (SCD_NgRl) {		/*	By Y.Suzuki 1997/03/11	*/
//				return;
//			}
//			while(1) {
////				if (rl_data <= 0x003F) {
//					next_rl = 0;
//					if (col == WHITE) {
//						byte_data = (UBYTE)rl_data;
//						*(rl_buf->Data + write_pointer) = byte_data;
//						write_pointer ++;
//					}
//					else {
////						word_data = rl_data | 0x0040;
//						byte_data = (UBYTE)word_data;
//						*(rl_buf->Data + write_pointer) = byte_data;
//						write_pointer ++;
//					}
//					break;
//				}
//				else {
////					if (rl_data >= MH_MAKEUP_MAX) {
//						temp = MH_MAKEUP_MAX;
//						rl_data = rl_data - MH_MAKEUP_MAX;
//						next_rl = 1;
//					}
//					else {
//						next_rl = 0;
//						temp = rl_data;
////					}
//					temp <<= 2;
//					if (col == WHITE) {
//						temp |= 0x8000;
//						word_data = temp & 0xFF00;
//						word_data >>= 8;
//						byte_data = (UBYTE)word_data;
//						*(rl_buf->Data + write_pointer) =  byte_data;
////						write_pointer ++;
//						byte_data = (UBYTE)(temp & 0x00FF);
//						*(rl_buf->Data + write_pointer) =  byte_data;
//						write_pointer ++;
//					}
//					else {
//						temp |= 0xC000;
//						word_data = temp & 0xFF00;
////						word_data >>= 8;
//						byte_data = (UBYTE)word_data;
//						*(rl_buf->Data + write_pointer) =  byte_data;
//						write_pointer ++;
//						byte_data = (UBYTE)(temp & 0x00FF);
//						*(rl_buf->Data + write_pointer) =  byte_data;
//						write_pointer ++;
//					}
////					if (next_rl && rl_data) {
//						continue;
//					}
//					else {
//						break;
//					}
//				}
//			}
////
//
//			rl_data = 0;
//			col = 0;
//			pre_col = 0;
//		}
//	}
//}
#endif

#if(0)		/*	By Y.Suzuki 1997/03/07	*/
** /*************************************************************************
** 	module		:[k¬‰Šú‰»]
** 	function	:[
** 		1.
** 	]
** 	return		:[]
** 	common		:[]
** 	condition	:[]
** 	comment		:[]
** 	machine		:[SH2]
** 	language	:[SHC]
** 	keyword		:[SCD]
** 	date		:[1995/11/21]
** 	author		:[—é–Øˆè“ñ]
** *************************************************************************/
//void SetSkip(UWORD percent, struct reduction_t *rp)
//{
//	WORD i;
//
//	rp->linecnt = 0;
//	if (percent == A3_TO_A4) {
//		rp->cntr_loop = 38;		/* 27/38 */
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[0][0];
//	}
//	else if (percent == A3_TO_B4) {
//		rp->cntr_loop = 38;		/* 32/38 */
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[1][0];
//	}
//	else if (percent == B4_TO_A4) {
//		rp->cntr_loop = 32;		/* 27/32 */
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[2][0];
//	}
//	else if (percent == P_A3_TO_A4) {
//		rp->cntr_loop = 38;		/* 26/38 */
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[3][0];
//	}
//	else if (percent == P_B4_TO_A4) {
//		rp->cntr_loop = 32;		/* 26/32 */
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[4][0];
//	}
//	else if (percent >= 50) {
//		rp->cntr_loop = 40;		/* ‰Â•Ïk¬ */
//		i = ((102 - percent) * 10) / 25;
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[i+5][0];
//	}
//	else {
//		rp->cntr_loop = 40;		/* ‰Â•Ïk¬ */
//		i = (((102 - percent) * 10) / 25) - 20;
//		i = (102 - percent) * 10;
//		rp->r_tbl_p = (UBYTE *)&reduc_tbl[25-i][0];
//	}
//	return;
//}
//
//
#endif
/*************************************************************************
//	module		:[‘—MŒ´eƒTƒCƒYk¬‚É‚Ä¶‚¸‚é•›‘–¸‚ÌŠÔˆø‚«ˆ—]
//	function	:[
//		1.
//	]
//	return		:[]
//	common		:[]
//	condition	:[]
//	comment		:[]
//	machine		:[SH2]
//	language	:[SHC]
//	keyword		:[SCD]
//	date		:[1995/11/25]
//	author		:[—é–Øˆè“ñ]
*************************************************************************/
#if(0)
//UBYTE Skip(struct reduction_t *rp)
//{
//	UWORD h, i, j;
//
//	i = rp->linecnt - (rp->cntr_loop * (rp->linecnt / rp->cntr_loop));
//	/* Ex.    85 - (38 * (85 / 38)) */
//	j = i % 8;		/* ‰½ËŞ¯Ä–Ú‚© */
//	i = i / 8;		/* ‰½ÊŞ²Ä–Ú‚© */
//	h = (0x80 >> j);
//	rp->linecnt++;
//	if ((*(rp->r_tbl_p + i)) & h) {
//		return(1);	/* k¬‚¹‚æ */
//	}
//	return(0);	/* k¬‚µ‚È‚¢ */
//}
#endif
