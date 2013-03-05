#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\cmn_pro.h"
#include "\src\atlanta\prt\iu_therm\define\prt_drv.h"
#include "\src\atlanta\ext_v\sys_data.h"
#include "\src\atlanta\hinoki\define\scn_def.h"
#include "\src\atlanta\hinoki\ext_v\ga_buf.h"
#include "\src\cpu\sh7043_a\irom\define\io_pro.h"
#include "\src\cpu\sh7043_a\irom\define\sh_port.h"
#include "\src\atlanta\define\mntsw_h.h"
#include "\src\atlanta\ext_v\bkupram.h"

/*------------------------------------------------------------------------
 *  GA初期化ルーチン
 *    2.5ms間隔で割込みを発生させる
 *-----------------------------------------------------------------------*/
void InitializeGateArray(void)
{
	UWORD Status;
	
	CMN_DisableInterrupt();

	/* SH2.5ms, SPINT2.5ms, ImgBufEnable, 16本, B4 */
	GA_MWR_Status = ((UWORD)(((UDWORD)(&ScanBuf) & (MWR_IBADD << 1)) >> 1) | MWR_IBN_VALUE | MWR_IBEN | MWR_IBB4);
	OutputWORD(GA_MWR, GA_MWR_Status);

	/* CI, 2.5ms割込みスタート */
#if defined (KEISATSU) /* 警察FAX 05/06/30 石橋正和 */
	GA_IntMaskStatus = (IMASK_INTSP | IMASK_XCI | IMASK_XCIEX);	
#else
	GA_IntMaskStatus = (IMASK_INTSP | IMASK_XCI);	
#endif
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	GaPrtcStatus = 0;
	OutputWORD(GA_PRTC, GaPrtcStatus);

	/* スキャナタイマー割込み禁止 */
	DisableIntScannerTimer();

	/* プリンタタイマー割込み禁止 */
	DisableIntPrinterTimer();

	IntTimerCounter = 0;

	CMN_EnableInterrupt();
}

/*------------------------------------------------------------------------
 *  GA割込み停止ルーチン
 *-----------------------------------------------------------------------*/
void DisableGateArrayInt(void)
{
	CMN_DisableInterrupt();

	/* GateArray割込み全て禁止 */
	GA_IntMaskStatus = 0;	
	OutputWORD(GA_INT_MASK, GA_IntMaskStatus);

	/* スキャナタイマー割込み禁止 */
	DisableIntScannerTimer();
	/* プリンタタイマー割込み禁止 */
	DisableIntPrinterTimer();

	CMN_EnableInterrupt();
}
