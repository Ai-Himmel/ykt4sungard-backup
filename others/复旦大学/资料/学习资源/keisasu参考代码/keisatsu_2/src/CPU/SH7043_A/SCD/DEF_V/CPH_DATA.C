/*--------------------------------------------------------------------
* プロジェクト : POPLAR
* ファイル名   : cph_def.h
* 作成者       : By Y.Suzuki
* 日  付       : 1997/06/10
* 概  要       : SH2
*              : 暗号化用大域変数
* 参照
*--------------------------------------------------------------------*/
#include "\src\atlanta\define\product.h"
#include "\src\atlanta\define\mem_def.h"
#include "\src\atlanta\define\message.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\cph_def.h"
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#else
#include "\src\atlanta\scd\define\cph_def.h"
#include "\src\atlanta\scd\define\scd.h"
#endif

#if (PRO_CIPHER == ENABLE)
struct CipherTbl_t CipherData = {0};

/*	メモリリードライトオープンに必要なパラメータ	*/
struct MEM_IndexData_t CipherReadIndex = {0};
struct MEM_IndexData_t CipherWriteIndex = {0};
struct MEM_ExecData_t  CipherExecReadData = {0};
struct MEM_ExecData_t  CipherExecWriteData = {0};
struct MEM_StoreData_t CipherStoreData = {0};
UWORD CipherReadPageNo = 0;
UWORD CipherWritePageNo = 0;

/*	ソフトコーデック初期化に必要なデータ	*/
UBYTE CipherWriteCode = 0;
UBYTE CipherWriteMode = 0;
UBYTE CipherWriteSize = 0;
UBYTE CipherReadCode = 0;
UBYTE CipherReadMode = 0;
UBYTE CipherReadSize = 0;
UWORD CipherReadTotalLine = 0;

/* エンコード／デコード 初期化フラグ !=0 の時初期化する */
UBYTE CipherBegin = 0;

/* ＲＬバッファアクセス用変数 */
struct WorkBuf_t *EncodeA_buf = {0};
struct WorkBuf_t *EncodeB_buf = {0};
struct WorkBuf_t *DecodeA_buf = {0};
struct WorkBuf_t *DecodeB_buf = {0};

/* エンコード／デコード 変数 */
struct CdcBlk_t CipherEncodeData = {0};
struct CdcBlk_t CipherDecodeData = {0};
UWORD CipherEncodeLine = 0;
UWORD CipherDecodeLine = 0;

/* 暗号化結果メッセージ送信用 */
MESSAGE_t	CipherMessage = {0};

/* スクランブル／復元処理停止ステータス */
/* SYS_Machinestatus を参照したくない。アドレスの固定化が難しそうなんで */
UBYTE CipherStopOn = 0;

/* 本来は、SYS_DATA.Cにあるべきやけど By Y.Suzuki 1997/12/09 */
/* SYS_DATA のｱﾄﾞﾚｽを固定したくない。(この時期に動かしたくない) */
/* 拡張ROM が接続されていれば ON する */
UBYTE ScrambleOn = 0;

/* Aliroo MML I/O IMAGE BUFFER By Y.Suzuki 1997/09/18 */
#pragma section IMGBUF /* locate section name "DIMGBUF" By Y.Suzuki 1997/10/28 */
UBYTE	Img_Buffer1[SCD_LINE_SIZE][SCD_LINE_BYTE_SIZE] = {0};/* Ｂ４ ファイン １ページ分 デコード用 */
UBYTE	Img_Buffer2[1][SCD_LINE_BYTE_SIZE] = {0};			/* Ｂ４ ライン１ライン分 エンコード用 */
#pragma section /* locate section name "CIMGTBL" */

/* パーセント表示用 By Y.Suzuki 1998/01/12 */
/* アリロの表示用パラメータの値がいまいちなんでこっちで改ざんする */
int RealPercent = 0;

/* For Debug By Y.Suzuki 1997/11/02 */
UBYTE SCD_DebugCopyOn = 0;
UWORD SCD_DebugLineToLabel = 0;

/* 2回線目のラインＮＯ．記憶 By Y.Suzuki 1998/04/28 */
UBYTE OtherLineNo = 0;

#else
/* ＲＬからイメージに変換する関数が以下の配列を参照しています。
** ついては、これらの配列を内部ＲＯＭ側からアクセスする際は間接ポインターアクセスとします。
** ロケーションについては、各機種で自由にしてください。
** By O.Kimoto 1998/09/25
*/
#pragma section IMGBUF /* locate section name "DIMGBUF" By Y.Suzuki 1997/10/28 */
#if defined(HINOKI) || defined (HINOKI2) || defined(HINOKI3) || defined (SATSUKI2) || defined (STOCKHM2)/* HINOKI2 2001/11/12 T.Takagi */
/* ＨＩＮＯＫＩはそれぞれのバッファを別で宣言します。
** UBYTE	Img_Buffer1[1][1] = {0};	＝＞ \src\atlanta\prt\iu_therm\def_v\prt_data.c
** UBYTE	Img_Buffer2[1][1] = {0};	＝＞ \src\atlanta\hinoki\def_v\page_mem.c
** By O.Kimoto 1998/10/05
*/
#elif defined(SAKAKI)
UBYTE	Img_Buffer1[1][1] = {0};/* Ｂ４ ファイン １ページ分 デコード用 */
UBYTE	Img_Buffer2[1][1] = {0};			/* Ｂ４ ライン１ライン分 エンコード用 */
#else
UBYTE	Img_Buffer1[SCD_LINE_SIZE][SCD_LINE_BYTE_SIZE] = {0};/* Ｂ４ ファイン １ページ分 デコード用 */
UBYTE	Img_Buffer2[1][SCD_LINE_BYTE_SIZE] = {0};			/* Ｂ４ ライン１ライン分 エンコード用 */
#endif

#pragma section /* locate section name "CIMGTBL" */

#endif	/* End of PRO_CIPHER */

