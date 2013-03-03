/*---------------------------------------------------------------------------*/
/*  プロジェクト : POPLAR_F                                                  */
/*  ファイル名   : mdm_ecm.c                                                 */
/*  モジュール   :                                                           */
/*  作成者       :                                                           */
/*  日  付       : 1999/10/06                                                */
/*  概  要       : ＥＣＭバッファ定義                                        */
/*  修正履歴     :                                                           */
/*---------------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\mdm\fm336\define\mdm_def.h"

/*
** RISCコンパイラー用のデータセクションを設定します。
** MEMINDEXはDMEMINDEXの名前が自動的に設定されます。
** 86系のセグメント名に相当する。
** By S.Kawasaki 1996/03/11
*/
#pragma	section	ECMBUF

UBYTE	EcmBuffer[ECM_BUFFER_MAX][ECM_BUFFER_LENGTH] = {0};

#if (PRO_CODEC_NUMBER == CDC_SINGLE)	/* 1999/10/06 ECM_BUFFER_OVER */
BYTE	EcmBuffer2[ECM_BUFFER_MAX][ECM_BUFFER_LENGTH] = {0};
#endif

#pragma	section

/*
** RISCコンパイラー用のデータセクションを設定します。
** MEMINDEXはDMEMINDEXの名前が自動的に設定されます。
** 86系のセグメント名に相当する。
** By S.Kawasaki 1996/03/11
*/
#pragma	section	MDM_STAT

struct	ModemInternalStatusTable_t MDM_InternalStatus[MODEM_STATUS_TABLE_MAX] = {0};	/** モデム内部遷移ステータス用テーブル **/

#pragma	section

