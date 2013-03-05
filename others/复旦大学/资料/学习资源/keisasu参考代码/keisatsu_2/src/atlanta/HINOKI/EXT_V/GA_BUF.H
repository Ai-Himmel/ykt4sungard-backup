#include "\src\atlanta\define\product.h"
#if (PRO_MODEM == MN195006)
#include "\src\atlanta\mdm\pana\define\mdm_def.h"
#elif (PRO_MODEM == ORANGE3)
#include "\src\atlanta\mdm\orange\define\mdm_def.h"
#else
	#if (PRO_MODEM_R288F_VERSION == FM336_VERSION_12P)
		#include "\src\atlanta\mdm\fm336\define\mdm_def.h"
	#else
		#include "\src\atlanta\mdm\R288f\define\mdm_def.h"
	#endif
#endif

extern UBYTE SmoothingBuffer[3][256];		/* G/A使用スムージング・バッファ */
extern UBYTE PrinterBuffer[2][256];			/* G/A使用プリンタ・バッファ */
extern UBYTE ScanBuf[16][256];
