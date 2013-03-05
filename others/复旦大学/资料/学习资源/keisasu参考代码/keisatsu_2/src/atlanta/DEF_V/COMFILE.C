/*************************************************************************
*	System			: POPLAR/ANZU-L
*	File Name		: comfile.c
*	Author			: 橘正樹
*	Date			: 1997/02/07
*	RealTimeOS		: RISCモニタ
*	Description		: ＤＲＡＭに配置するコマンドファイルの宣言
*	Maintenance		: extern宣言はbkupram.hを参照すること
*
*	Copyright (C) 1997 Murata Machinery,Ltd. All rights reserved.
*************************************************************************/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\sysmax.h"
#include "\src\atlanta\define\syscomf.h"
#if (PRO_F_CODE == ENABLE)
	#include "\src\atlanta\define\sysfcode.h"	/* 1997/01/09  By T.Yamaguchi */
#endif

#if (PRO_COMMANDFILE_SRAM == DISABLE)

#pragma section COMFILE

#if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/08/06 Y.Murata */
struct SYS_CommandData_t SYB_CommandFile[SYS_COM_FILE_MAX] = {0};
#else
struct SYS_CommandData_t SYB_CommandFile[SYS_COM_FILE_MAX] = {0};
#endif

#if (PRO_F_CODE == ENABLE)	/*	1997/01/09	By T.Yamaguchi */
/************************************************************************
 *	Fｺｰﾄﾞﾃﾞｰﾀ格納ﾊﾞｯﾌｧ			(ｺﾏﾝﾄﾞﾌｧｲﾙ登録用)	D-RAM領域に移動する予定
 ***********************************************************************/
struct SYS_FcodeNumberData_t	SYB_FcodeNumberCDataBuffer[SYS_COM_FILE_MAX * F_CODE_DATA_MAX] = {0};
#endif

#pragma section

#endif
