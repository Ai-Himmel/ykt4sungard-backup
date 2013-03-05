/*---------------------------------------------------------------------------*/
/*  プロジェクト : HINOKI2                                                   */
/*  ファイル名   : mdm_io.h                                                  */
/*  作成者       : 岸田二郎                                                  */
/*  日  付       : 2002/10/02                                                */
/*  概  要       :                                                           */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#ifndef	MDM_IO_H
	#define	MDM_IO_H	1

#if (PRO_MODEM == ORANGE3)
	#include	"\src\atlanta\mdm\orange\define\mdm_io.h"
#endif
#if (PRO_MODEM == R288F)
	#include	"\src\atlanta\mdm\r288f\define\mdm_io.h"
#endif
#if (PRO_MODEM == MN195006)
	#include	"\src\atlanta\mdm\pana\define\mdm_io.h"
#endif

#endif
