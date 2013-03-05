/*
**	%W%
**	File Name:	f:\prj\eva\src\init\int_top.c
**	Create:	1997/12/11	By Masahiro,IIDA
**	Description: IRQ3&7 Interrupt Routine Top
**	Change: 19xx/xx/xx	
*/

#include "\src\atlanta\define\product.h"
#include "\src\atlanta\hinoki\define\hinoport.h"
#include "\src\atlanta\hinoki\ext_v\scn_dath.h"
#include "\src\atlanta\opr\ank\define\opr_pro.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\atlanta\prt\iu_therm\ext_v\prt_data.h"
#include "\src\atlanta\ext_v\bkupram.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\hinoki\define\hino_sys.h"

/*
**	2.5ms毎にG/Aからくる割込み処理ルーチン１
*/
void GA_Interrupt1(void)
{
	UBYTE debug;
	
	++IntTimerCounter;

	/* 2.5ms毎に行うルーチンを記述 */
	/* 画処理 & 送信モータ制御 */
	ScannerInt();

	/* LCD/LED制御 */
#if 0 /* defined (HINOKI2) */	/* LCDドライバ変更対応 2002/05/15 T.Takagi */
	if (!SYS_IsCGRAM_Writing) {
		SYS_IsDisplayingLCD = TRUE;
		DisplayLCD();
		SYS_IsDisplayingLCD = FALSE;
	}
#else
	DisplayLCD();
#endif
	/* キースキャン */
	KeyScan();

	if (IntTimerCounter & 0x00000001) {	/* 5msに１回処理 */

#if (0) /* 1998/11/18 by T.Soneoka 以下の処理を２．５ｍｓで行うように上記に変更 */
**		/* LCD/LED制御 */
**		DisplayLCD();
**		/* キースキャン */
**		KeyScan();
#endif
		/* Thermal Printer 制御 */
		PrinterTimerInt();
		
		/*
		** 済みスタンプ保険処理
		** １５０ｍｓ以上Ｏｎ時間があると済みスタンプが壊れるため
		** それ以上Ｏｎしている場合は強制的にＯｆｆする
		*/
		if (RelayPortStatus & IO_BIT_STAMP) {
			StampOnTime++;
		} else {
			StampOnTime = 0;
		}
		if (StampOnTime > (150/5)) {
			RelayPortStatus &= (~IO_BIT_STAMP);
			OutputWORD(GA_PGADR, RelayPortStatus);
		}
	}
}


/*
**	プリンタ関連/CI等にG/Aからくる割込み処理ルーチン２
*/
void GA_Interrupt2(void)
{
	UWORD Status;
	UWORD DBG_Status;
	
	Status = InputWORD(GA_INT_STA);		/* G/A割込みステータス・ポート */
	OutputWORD(GA_INT_REC, Status);	/* 割込み受領 */

#if (0) /* Ｇ／Ａ調査用 */
	while (1) {
		DBG_Status = InputWORD(GA_INT_STA);	/* G/A割込みステータス・ポート */
		if (DBG_Status & IO_BIT_PBRDY) {
			SYB_MaintenanceSwitch[MNT_SW_H5] |= 0x02;
			OutputWORD(GA_INT_REC, DBG_Status);	/* 割込み受領 */
		} else {
			OutputWORD(GA_INT_REC, DBG_Status);	/* 割込み受領 */
			break;
		}
	}
#endif

	if (Status & IO_BIT_PBRDY) {
		/* Printer Buffer Ready 割込み */
		PrinterPbreadyInt();
	}
	if (Status & IO_BIT_CI_INT) {
		NCU_CI_Interrupt();				/* CI検出割込み処理 */
	}
#if defined (KEISATSU) /* 警察FAX 05/06/30 石橋正和 */
    if (Status & IO_BIT_CI_EX_INT) { /* 拡張回線(警電回線)CI割込み */
		if (InputWORD(GA_PGBDR) & IO_BIT_XCI_EX) { /* 警察FAX Modified by SMuratec 李 2005/07/05 */
        	NCU_CI2_Interrupt();
        }
    }
#endif
	
	return;
}
