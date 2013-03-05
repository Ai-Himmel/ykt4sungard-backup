/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\kobe\anzu\define\mem_def.h */
#ifndef mem_def_h
	#define	mem_def_h

/* ＃＃＃ 警告！！ ＃＃＃
 * MEM_RX_BORDERLINE は０固定としてください。
 * MEM_RX_BORDERLINE を使用する場合は、MEM_RX_BORDERLINEを使用しているところ全部書き換えてください。
 * MEM_RX_BORDERLINEを０以外にするとメモリ残量が少なくても着信したりしてしまいます
 * アトランタでは裏メモリをもたないので大丈夫だと思いますが。。。    1997/11/20
*/


/********************************************
* メモリ管理パラメータ						*
*********************************************/
#if (PRO_KEYPANEL == PANEL_POPLAR_B)
	#if(PRO_CIPHER == DISABLE)
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*/ /* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_IMAGE_RAM_START_ADDRESS   0x01026000	/* 暗号化タスク使用イメージＲＡＭ (330K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#else/* ALIROO仕様 By Y.Suzuki 1997/07/08 */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#if(0)
#define MEM_FAT_AREA_STANDARD				 392	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2440	/* ブロック数 (10Mの時) */
#endif
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_FAT_AREA_SCRAMBLE				276		/* スクランブルに必要なブロック数 (1104KB) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (332KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#endif
#endif/* POPLAR_B */

#if (PRO_KEYPANEL == PANEL_POPLAR_L)	/* 標準１Ｍ仕様用 poplar_l */
	#if defined(POPLAR_F)
	/* Ｌ４００後継 */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
 #if defined(JP1)
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
 #else
#define MEM_SPEC_STANDARD_SIZE				1024	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
 #endif
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 441	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数 202+256) */
#define MEM_FAT_AREA_MAX					2489	/* ブロック数 (10Mの時 458 + (256 * 8))*/
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS */
#define MEM_INDEX_START_ADDRESS		  0x01020000	/* インデックス・テーブルのSTART ADDRESS */
#define MEM_FAT_START_ADDRESS		  0x01024000	/* FATエリアのSTART ADDRESS */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01025400	/* キャラクタービットﾏｯﾌﾟアドレス */
#define MEM_COMMANDFILE_START_ADDRESS 0x01026400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01047000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					 198	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
													/* マスクすると、0x110D000 から蓄積する */
	#else

#define MEM_STANDARD_SIZE					   1	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				1024	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 217	/* ブロック数 (標準の1MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2265	/* ブロック数 (10Mの時)*/
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(512K) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01100000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01100000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01120000	/* インデックス・テーブルのSTART ADDRESS (16K) */
#define MEM_FAT_START_ADDRESS		  0x01124000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01125400	/* キャラクタービットﾏｯﾌﾟアドレス (4K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01127000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#endif
#endif	/* End of PANEL_POPLAR_L */

#if (0)	/* 標準２Ｍ起用 poplar_l */
** #define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
** #define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
** #define MEM_FAT_AREA_STANDARD				 473	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数 217+256) */
** #define MEM_FAT_AREA_MAX					2521	/* ブロック数 (10Mの時 473 + (256 * 8))*/
** #define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
** #define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
** #define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
** #define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
** #define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS */
** #define MEM_INDEX_START_ADDRESS		  0x01020000	/* インデックス・テーブルのSTART ADDRESS */
** #define MEM_FAT_START_ADDRESS		  0x01024000	/* FATエリアのSTART ADDRESS */
** #define	MEM_FONT_IMAGE_ADDRESS		  0x01025400	/* キャラクタービットﾏｯﾌﾟアドレス */
** #define MEM_STOREAREA_START_ADDRESS	  0x01027000	/* 蓄積エリア先頭アドレス */
** #define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
** #define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
** #define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
** #define MEM_DRAM_MASK_BLOCK					 230	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB)473-243 */
#endif
#if (0)
** #define MEM_STANDARD_SIZE					   1	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
** #define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
** #define MEM_FAT_AREA_STANDARD				 233	/* ブロック数 (標準の1MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
** #define MEM_FAT_AREA_MAX						2281	/* ブロック数 (10Mの時)*/
** #define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
** #define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(512K) */
** #define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
** #define MEM_DRAM_START_ADDRESS		  0x01100000	/* DRAMのSTART ADDRESS */
** #define MEM_ECM_BUFFER_START_ADDRESS   0x01100000	/* ECM BUFFERのSTART ADDRESS (64K) */
** #define MEM_INDEX_START_ADDRESS		  0x01110000	/* インデックス・テーブルのSTART ADDRESS (16K) */
** #define MEM_FAT_START_ADDRESS		  0x01114000	/* FATエリアのSTART ADDRESS (5K) */
** #define	MEM_FONT_IMAGE_ADDRESS		  0x01115400	/* キャラクタービットﾏｯﾌﾟアドレス (4K) */
** #define MEM_STOREAREA_START_ADDRESS	  0x01116400	/* 蓄積エリア先頭アドレス */
** #define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
** #define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
** #define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
#endif

#if (PRO_KEYPANEL == PANEL_POPLAR_H)
#if (0)
** /* とりあえず、ＰＯＰＬＡＲ＿Ｂと同じにしておきます。 by O.Kimoto 1997/10/15 */
** #define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
** #define MEM_INDEX_TABLE_MAX					 682	/* インデックス枚数 */
** #define MEM_FAT_AREA_STANDARD				 109	/* ブロック数 (標準の512KByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
** #define MEM_FAT_AREA_MAX					2029	/* ブロック数 */
** #define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
** #define MEM_SIZECHECK_BLOCK					 128	/* DRAM容量自動判別チェック時の単位ブロック数(512K) */
** #define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
** #define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
** #define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS */
** #define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS */
** #define MEM_FAT_START_ADDRESS		  0x01012000	/* FATエリアのSTART ADDRESS */
** #define	MEM_FONT_IMAGE_ADDRESS		  0x01013000	/* キャラクタービットﾏｯﾌﾟアドレス */
** #define MEM_STOREAREA_START_ADDRESS	  0x01014000	/* 蓄積エリア先頭アドレス */
** #define MEM_SIZECHECK_START_ADDRESS	  0x01400000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
** #define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
** #define MEM_FAT_AREA_SCRAMBLE				276		/* スクランブルに必要なブロック数 (1104KB) */
** #define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#endif
	#if(PRO_CIPHER == DISABLE)
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_IMAGE_RAM_START_ADDRESS   0x01026000	/* 暗号化タスク使用イメージＲＡＭ (330K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#else/* ALIROO仕様 By Y.Suzuki 1997/07/08 */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#if(0)
#define MEM_FAT_AREA_STANDARD				 392	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2440	/* ブロック数 (10Mの時) */
#endif
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_FAT_AREA_SCRAMBLE				276		/* スクランブルに必要なブロック数 (1104KB) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#endif
#endif

#if (PRO_KEYPANEL == PANEL_ANZU_L)
 #if (PRO_DIALUP_INTERNET_FAX == DISABLE)/*1998/7/16 Eguchi*/
  #if (PRO_MINOLTA_TEST_FUNC == ENABLE)	/* 1998/07/24 Y.Matsukuma */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
/*#define MEM_SPEC_STANDARD_SIZE				2048 2000/03/13 Y.Murata*/	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_SPEC_STANDARD_SIZE				1024	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					  20	/* インデックス枚数 *//* 1998/08/10 Y.Murata */
#define MEM_INDEX_TABLE_MAX2				1024	/* インデックス枚数 *//* 1998/08/10 Y.Murata */
#define MEM_FAT_AREA_STANDARD				 458	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数 202+256) */
#define MEM_FAT_AREA_MAX					2048	/* ブロック数 (10Mの時 458 + (256 * 8) - 458)*/
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01200000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS */
#define MEM_INDEX_START_ADDRESS		  0x01200000	/* インデックス・テーブルのSTART ADDRESS */
#define MEM_FAT_START_ADDRESS		  0x01204000	/* FATエリアのSTART ADDRESS */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01205400	/* キャラクタービットﾏｯﾌﾟアドレス */
#define MEM_COMMANDFILE_START_ADDRESS 0x01206400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01216000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
  #else
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
/*#define MEM_SPEC_STANDARD_SIZE				2048  2000/03/13 Y.Murata */	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_SPEC_STANDARD_SIZE				1024	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 458	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数 202+256) */
#define MEM_FAT_AREA_MAX					2506	/* ブロック数 (10Mの時 458 + (256 * 8))*/
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS */
#define MEM_INDEX_START_ADDRESS		  0x01020000	/* インデックス・テーブルのSTART ADDRESS */
#define MEM_FAT_START_ADDRESS		  0x01024000	/* FATエリアのSTART ADDRESS */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01025400	/* キャラクタービットﾏｯﾌﾟアドレス */
#define MEM_COMMANDFILE_START_ADDRESS 0x01026400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01036000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					 215	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
  #endif
 #endif
 #if (PRO_DIALUP_INTERNET_FAX == ENABLE)/*1998/7/16 Eguchi*/
 /* 1036000Hから256KB分（64ﾌﾞﾛｯｸ)をｲﾝﾀｰﾈｯﾄﾓｼﾞｭｰﾙのﾜｰｸに使用
  * これに伴い
  * 蓄積開始ｴﾘｱを1036000Hから1076000Hに変更。
  * 蓄積可能ﾌﾞﾛｯｸ数を458から394へ変更
  * 実装ﾒﾓﾘｰよりも減らすﾌﾞﾛｯｸ数を215から151へ変更
  * 総ﾌﾞﾛｯｸ数を2506から2442へ変更
  */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
/*#define MEM_SPEC_STANDARD_SIZE				2048  2000/03/13 Y.Murata*/	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_SPEC_STANDARD_SIZE				1024	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 394	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数 138+256) */
#define MEM_FAT_AREA_MAX					2442	/* ブロック数 (10Mの時 394 + (256 * 8))*/
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS */
#define MEM_INDEX_START_ADDRESS		  0x01020000	/* インデックス・テーブルのSTART ADDRESS */
#define MEM_FAT_START_ADDRESS		  0x01024000	/* FATエリアのSTART ADDRESS */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01025400	/* キャラクタービットﾏｯﾌﾟアドレス */
#define MEM_COMMANDFILE_START_ADDRESS 0x01026400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01076000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					 151	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) */
 #endif


#if (0)	/*標準DRAM増設のため変更 By M.Kotani1997/12/12 */
//#define MEM_STANDARD_SIZE					   1	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
//#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
//#define MEM_FAT_AREA_STANDARD				 202	/* ブロック数 (標準の1MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
//#define MEM_FAT_AREA_MAX					2250	/* ブロック数 (9Mの時)*/
//#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
//#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
//#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
//#define MEM_DRAM_START_ADDRESS		  0x01100000	/* DRAMのSTART ADDRESS */
//#define MEM_ECM_BUFFER_START_ADDRESS  0x01100000	/* ECM BUFFERのSTART ADDRESS */
//#define MEM_INDEX_START_ADDRESS		  0x01120000	/* インデックス・テーブルのSTART ADDRESS */
//#define MEM_FAT_START_ADDRESS		  0x01124000	/* FATエリアのSTART ADDRESS */
//#define	MEM_FONT_IMAGE_ADDRESS		  0x01125400	/* キャラクタービットﾏｯﾌﾟアドレス */
//#define MEM_COMMANDFILE_START_ADDRESS 0x01126400	/* コマンドファイル先頭アドレス (40K) */
//#define MEM_STOREAREA_START_ADDRESS	  0x01136000	/* 蓄積エリア先頭アドレス */
//#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
//#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
//#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#endif
#if 0
//#define MEM_STANDARD_SIZE						   1	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
//#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
//#define MEM_FAT_AREA_STANDARD					 218	/* ブロック数 (標準の1MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
//#define MEM_FAT_AREA_MAX						2266	/* ブロック数 (9Mの時)*/
//#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
//#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(256Blocks) */
//#define MEM_RX_BORDERLINE						   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
//#define MEM_DRAM_START_ADDRESS		  0x01100000	/* DRAMのSTART ADDRESS */
//#define MEM_ECM_BUFFER_START_ADDRESS	  0x01100000	/* ECM BUFFERのSTART ADDRESS */
//#define MEM_INDEX_START_ADDRESS		  0x01110000	/* インデックス・テーブルのSTART ADDRESS */
//#define MEM_FAT_START_ADDRESS			  0x01114000	/* FATエリアのSTART ADDRESS */
//#define	MEM_FONT_IMAGE_ADDRESS		  0x01115400	/* キャラクタービットﾏｯﾌﾟアドレス */
//#define MEM_COMMANDFILE_START_ADDRESS	  0x01116400	/* コマンドファイル先頭アドレス (40K) */
//#define MEM_STOREAREA_START_ADDRESS	  0x01126000	/* 蓄積エリア先頭アドレス */
//#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は1M分とします) */
//#define MEM_SIZECHECK_END_ADDRESS		  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
//#define MEM_SCRAMBLE_INTERNAL_BLOCK			  83	/* スクランブル内部で必要なブロック数 (330KB) */
#endif
#endif

#if (PRO_KEYPANEL == PANEL_SAKAKI)	/* 1998/06/10 H.Yoshikawa */
	#if(PRO_CIPHER == DISABLE)
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_IMAGE_RAM_START_ADDRESS   0x01026000	/* 暗号化タスク使用イメージＲＡＭ (330K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			  83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#else/* ALIROO仕様 By Y.Suzuki 1997/07/08 */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				2048	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_FAT_AREA_SCRAMBLE				276		/* スクランブルに必要なブロック数 (1104KB) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#endif
#endif

/* 移植 by SMuratec K.W.Q 2003/07/23 */
/*#if (PRO_KEYPANEL == PANEL_HINOKI)*/	/* For HINOKI By O.Kimoto 1998/09/07 */
#if (PRO_KEYPANEL == PANEL_HINOKI) || (PRO_KEYPANEL == PANEL_SATSUKI2)  || (PRO_KEYPANEL == PANEL_STOCKHM2)	/* For HINOKI By O.Kimoto 1998/09/07 */

	#if(PRO_CIPHER == DISABLE)
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				1168	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#if (0)
** /* 読み取り用ページメモリをＢ４／ノーマル／１枚からＢ４／ファイン／１枚に変更 By O.Kimoto 1999/01/09 */
** #define MEM_FAT_AREA_STANDARD				 377	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) *//* Change 474 to 377 By O.Kimoto 1998/11/18 */
** #define MEM_FAT_AREA_MAX					1401	/* ブロック数 (10Mの時) *//* Change 2522 to 1401(6M) By O.Kimoto 1998/11/18 */
#else
#define MEM_FAT_AREA_STANDARD				 293	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) *//* Change 474 to 377 By O.Kimoto 1998/11/18 */
#define MEM_FAT_AREA_MAX					1317	/* ブロック数 (6Mの時) *//* Change 2522 to 1401(6M) By O.Kimoto 1998/11/18 */
#endif

#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#if (0) /* ページメモリ挿入の為 1998/10/01 by T.Soneoka */
** 	#define MEM_IMAGE_RAM_START_ADDRESS   0x01026000	/* 暗号化タスク使用イメージＲＡＭ (330K) */
** 	#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#else
#if (0)
** /* 読み取り用ページメモリをＢ４／ノーマル／１枚からＢ４／ファイン／１枚に変更 By O.Kimoto 1999/01/09 */
** #define MEM_IMAGE_RAM_START_ADDRESS   0x01087000	/* 暗号化タスク使用イメージＲＡＭ (330K) *//* Change 0x01086400 to 0x01087000 By O.Kimoto 1998/11/18 */
** #define MEM_STOREAREA_START_ADDRESS	  0x01087000	/* 蓄積エリア先頭アドレス *//* Change 0x01086400 to 0x01087000 By O.Kimoto 1998/11/18 */
#else
#define MEM_IMAGE_RAM_START_ADDRESS   0x010DB000	/* 暗号化タスク使用イメージＲＡＭ (330K) *//* Change 0x01086400 to 0x01087000 By O.Kimoto 1998/11/18 */
#define MEM_STOREAREA_START_ADDRESS	  0x010DB000	/* 蓄積エリア先頭アドレス *//* Change 0x01086400 to 0x01087000 By O.Kimoto 1998/11/18 */
#endif
#endif
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01600000	/* 拡張メモリの最終アドレス(拡張MAX=8M) *//* Change 0x01A00000 to 0x01600000(6M Max) By O.Kimoto 1998/11/18 */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#else/* ALIROO仕様 By Y.Suzuki 1997/07/08 */
#define MEM_STANDARD_SIZE					   2	/* 標準搭載メモリ（xMB）M.Kotani 1997/10/02 */
#define MEM_SPEC_STANDARD_SIZE				1168	/* カタログ上の標準搭載メモリ（xKB）1999/08/21 H.Yoshikawa */
#define MEM_INDEX_TABLE_MAX					1024	/* インデックス枚数 */
#define MEM_FAT_AREA_STANDARD				 474	/* ブロック数 (標準の2MByte分の蓄積ｴﾘｱのﾌﾞﾛｯｸ数) */
#define MEM_FAT_AREA_MAX					2522	/* ブロック数 (10Mの時) */
#define MEM_BLOCK_SIZE						4096	/* ブロック・サイズ(Byte) */
#define MEM_SIZECHECK_BLOCK					 256	/* DRAM容量自動判別チェック時の単位ブロック数(1M) */
#define MEM_RX_BORDERLINE					   0	/* 絶対０固定 いろたらあかんおかしなる*//* 受信用に裏に持つブロック数 */
#define MEM_DRAM_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */
#define MEM_ECM_BUFFER_START_ADDRESS  0x01000000	/* ECM BUFFERのSTART ADDRESS (64K) */
#define MEM_INDEX_START_ADDRESS		  0x01010000	/* インデックス・テーブルのSTART ADDRESS (8K) */
#define MEM_FAT_START_ADDRESS		  0x01014000	/* FATエリアのSTART ADDRESS (5K) */
#define	MEM_FONT_IMAGE_ADDRESS		  0x01015400	/* キャラクタービットマップアドレス (4K) */
#define MEM_COMMANDFILE_START_ADDRESS 0x01016400	/* コマンドファイル先頭アドレス (40K) */
#if (0) /* ページメモリ挿入の為 1998/10/01 by T.Soneoka */
#define MEM_STOREAREA_START_ADDRESS	  0x01026000	/* 蓄積エリア先頭アドレス */
#endif
#define MEM_STOREAREA_START_ADDRESS	  0x01086000	/* 蓄積エリア先頭アドレス */
#define MEM_SIZECHECK_START_ADDRESS	  0x01200000	/* 標準メモリ容量以上の先頭アドレス(標準は2M分とします) */
#define MEM_SIZECHECK_END_ADDRESS	  0x01A00000	/* 拡張メモリの最終アドレス(拡張MAX=8M) */
#define MEM_FAT_AREA_SCRAMBLE				276		/* スクランブルに必要なブロック数 (1104KB) */
#define MEM_SCRAMBLE_INTERNAL_BLOCK			83		/* スクランブル内部で必要なブロック数 (330KB) */
#define MEM_DRAM_MASK_BLOCK					   0	/* 実装メモリよりも蓄積枚数を減らすブロック数 (0KB) *//*M.Kotani 1997/12/12*/
	#endif
#endif



/********************************************
*	メモリ蓄積 原稿種別						*
*********************************************/
#define SYS_MEM_FILE_EMPTY					0	/* 空インデックス		  */
#define SYS_MEM_TX_FILE						1	/* メモリ送信原稿		  */
#define SYS_MEM_RX_FILE						2	/* メモリ受信原稿		  */
#define SYS_MEM_POLLING_FILE				3	/* ポーリング送信原稿	  */
#define SYS_MEM_DB_POLLING_FILE				4	/* 検索ポーリング送信原稿 */
#define SYS_MEM_SECURE_RX_FILE				5	/* 親展受信原稿			  */
#define SYS_MEM_MULTI_COPY_FILE				6	/* マルチ・コピー原稿	  */
#define SYS_MEM_FIP_FILE					7	/* FIP原稿				  */
#define SYS_MEM_BATCH_TX_FILE1				8	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE2				9	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE3				10	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE4				11	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define SYS_MEM_BATCH_TX_FILE5				12	/* バッチ送信原稿		  Mar.29,1994 By NOBUKO */
#define	SYS_MEM_REMOTE_TX_FILE				13	/* リモート送信原稿		  Jan.19,1994 By S.K */
#define	SYS_MEM_BUFFERING_RX_FILE			14	/* バッファリング受信原稿 Jun.15,1994 By M.T */
#define	SYS_MEM_CLASS1_TX_FILE				15	/* ﾛｰｶﾙｽｷｬﾝ用送信原稿	  by Y.Tanimoto 1996/06/26 */
#define SYS_MEM_CL1_RX_FILE					16	/* Class 1 ﾛｰｶﾙﾌﾟﾘﾝﾄ用原稿 by Y.Tanimoto 1996/06/28 */
#define SYS_MEM_PC_RX_FILE					17	/* ＰＣプリントファイル	  by J.Miyazaki 1996/08/10 */
#define SYS_MEM_MANUAL_COPY_FILE			18	/* 手差しコピー原稿 ●ICHOU追加 by T.Soneoka 1996/06/28 */
#define SYS_MEM_ROTATE_FILE					19	/* 回転プリント原稿 By Y.Suzuki 1996/11/13 */
#define SYS_MEM_CIPHER_FILE					20	/* 暗号化前原稿 By Y.Suzuki 1996/11/13 */
#define SYS_MEM_SUB_SECURE_FILE				21	/* サブアドレス通信原稿	－＞親展受信原稿 */
#define SYS_MEM_SUB_BULLETIN_FILE			22	/* サブアドレス通信原稿	－＞掲示板受信原稿、掲示板蓄積原稿 */
#define SYS_MEM_CIPHER_RX_FILE				23	/* 暗号化受信原稿 By Y.Suzuki 1996/3/14 */
#define SYS_MEM_DECIPHER_FILE				24	/* 暗号化受信復元原稿 By Y.Suzuki 1996/3/14 */
#define SYS_MEM_TX_DECIPHER_FILE			25	/* 送信予約暗号化復元原稿 By Y.Suzuki 1997/10/24 */
#if (PRO_DIALUP_INTERNET_FAX == ENABLE)	/* by Y.Tanimoto 1998/03/12 */
 #define	SYS_MEM_MAIL_TX_FILE			26	/* メール送信原稿 */
 #define	SYS_MEM_MAIL_RX_FILE			27	/* 受信メール */
#endif

/* Milli/Inch */
#define MEM_INCH_MODE						   0	/* インチ系 */
#define MEM_MILLI_MODE						   1	/* ミリ系 */
#define MEM_MILLI_BIT						0x80	/* ミリ系蓄積を示すBit(MEM_IndexTable[].Size上に立てます) */

/* DATA */
#define MEM_CHECK_DATA						0x55	/* メモリ有/無チェック時のデータ */

/* FATエリア指定時のDEFINE (FATエリア上のブロック数が32,752(0x7FF0)以上だと まずそう...) */
#define MEM_STORING_BLOCK				  0x8000	/* 蓄積中ブロック		  */
#define MEM_RESERVED_BLOCK				  0x7FF0	/* 蓄積予約ブロック		  */
#define MEM_EOP_BLOCK					  0x7FFC	/* EOPブロック			  */
#define MEM_BAD_BLOCK					  0x7FFE	/* 蓄積不可能ブロック	  */
#define MEM_EOB_BLOCK					  0x7FFF	/* EOBブロック			  */

/* IndexTable[].Item  蓄積中 */
#define MEM_NOW_STORING						0x80	/* 現在蓄積中を表すビット */
#define MEM_NOW_DELETING					0x40	/* 現在消去中を表すビット */

/* RETURN値 */
#define MEM_OK								   0
#define MEM_NG								   1
#define MEM_NO_CLEAR_DOC					   2
#define MEM_EXIST_CLEAR_DOC					   3
#define MEM_STOP_SW							   4
#define MEM_INDEX_CONFLICT				  0xFFFB	/* INDEX競合 */	/* 1997/01/09 Y.Murata */
#define MEM_INDEX_OVER					  0xFFFC
#define MEM_BLOCK_OVER					  0xFFFE
#define MEM_NO_INDEX					  0xFFFF

/* MEM_Read(), MEM_Write()で使用 */
#define MEM_MODEM				(UBYTE)0
#define MEM_SCANNER				(UBYTE)1
#define MEM_PRINTER				(UBYTE)2
#define MEM_TX_PAGE_END			(UBYTE)0x01
#define MEM_RX_PAGE_END			(UBYTE)0x02
#define MEM_SCAN_PAGE_END		(UBYTE)0x04
#define MEM_PRINT_PAGE_END		(UBYTE)0x08
#define MEM_NEXT_BLOCK_OK		(UBYTE)0
#define MEM_NEXT_BLOCK_EOB		(UBYTE)1
#define MEM_NO_BLOCK			(UBYTE)2

/* UBYTE BoxNumber BOXﾅﾝﾊﾞｰを入れる(F-CODE) 1997/01/09	By T.Yamaguchi */
#define MEM_IGNORE_BOX_NUMBER	(UBYTE)0x00
#define MEM_ALL_NO			(UWORD)0xFFFF

/* 標準DRAM容量 1MB で実装は、2MBの場合(ﾎﾟﾌﾟﾗL)のDRAM CHECK ｽﾀｰﾄｱﾄﾞﾚｽ */
/* By Y.Suzuki 1998/05/18 */
#define MEM_DRAM_CHECK_START_ADDRESS		  0x01000000	/* DRAMのSTART ADDRESS */

/* インデックス・テーブル */
struct IndexTableData_t {
	UWORD No;
	UWORD Page;
	UBYTE Item;
/*#if (PRO_F_CODE == ENABLE)*/
	UBYTE BoxNumber;	/* BOXﾅﾝﾊﾞｰを入れる(F-CODE) 1997/01/09	By T.Yamaguchi */
	UBYTE Dummy;		/* 未使用 */
/*#endif*/
	UBYTE Code;
	UBYTE Mode;
	UBYTE Size;
	UBYTE Area;			/* 原稿サイズ（ＰＣプリント） */
	UBYTE Cassette;		/* プリント時の指定カセット（ＰＣプリント） */
	UWORD LineCount;
	UWORD StartBlockNo;
};

/* 蓄積時に指定するデータ */
struct MEM_StoreData_t {
	UWORD No;
	UWORD Page;
	UBYTE Item;
	UBYTE Code;
	UBYTE Mode;
	UBYTE Size;
	UBYTE Area;			/* 原稿サイズ（ＰＣプリント） */
	UBYTE Cassette;		/* プリント時の指定カセット（ＰＣプリント） */
/*#if (PRO_F_CODE == ENABLE)*/
	UBYTE BoxNumber;	/* BOXﾅﾝﾊﾞｰを入れる(F-CODE) 1997/01/09	By T.Yamaguchi */
	UBYTE Dummy;		/* 未使用 */
/*#endif*/
};

/* 蓄積中指定データ */
struct MEM_ExecData_t {
	UWORD IndexNo1;
	UWORD IndexNo2;		/* Dual指定時は絶対に"0"は入らない */
	UWORD ExecBlockNo;
	UWORD NextBlockNo;
};

/* インデックス指定データ */
struct MEM_IndexData_t {
	UWORD No;
	UWORD Page;
	UBYTE Item;
/*#if (PRO_F_CODE == ENABLE)*/
	UBYTE BoxNumber;	/* BOXﾅﾝﾊﾞｰを入れる(F-CODE) 1997/01/09	By T.Yamaguchi */
/*#endif*/
};

/* 原稿蓄積状態指定データ */
struct MEM_DocParamData_t {
	UBYTE Code;
	UBYTE Mode;
	UBYTE Size;
};

/* DMAアドレス指定データ */
union MEM_DMAAddressData_t {
	UBYTE DMAAddress[4];	/* DMA起動時に使用 */
	UDWORD Address;			/* DMAアドレス計算時に使用 */
};

/* 原稿蓄積状態記憶ビット */
struct MEM_StoredNo_t {
	UDWORD	stored_indexno_lower;
	UDWORD	stored_indexno_uper;
};


#endif
