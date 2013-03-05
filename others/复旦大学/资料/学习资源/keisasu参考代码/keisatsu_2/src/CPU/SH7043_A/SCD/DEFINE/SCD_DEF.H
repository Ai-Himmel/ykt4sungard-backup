/*	By Y.Suzuki 1996/10/15	*/
/* Original File jun\usr2:\src\kobe\anzu\scdc\define\scdc_def.h */
#ifndef scd_def_h
	#define scd_def_h

/*----------------------------------*/
/*	ＭＨエンコードテーブル			*/
/*----------------------------------*/
struct MH_EC_Table_t {
	UBYTE	BitLength;			/*	ビット長					*/
	UWORD			MHData;				/*	ＭＨデータ（下位８ビット）	*/
};
 typedef	CONST struct MH_EC_Table_t MH_EC_TABLE_t;

/*----------------------------------*/
/*	ＭＲエンコードテーブル			*/
/*----------------------------------*/
struct MR_EC_Table_t {
	UBYTE		BitLength;			/*	ビット長					*/
	UBYTE		MRData;				/*	ＭＲデータ（下位８ビット）	*/
};
 typedef	CONST struct MR_EC_Table_t MR_EC_TABLE_t; /* const -> CONST  S.Wang 96/03/15 */

/*----------------------------------*/
/*	ＭＨデコード１次テーブル		*/
/*----------------------------------*/
struct MH_DC_Table1_t {
	WORD		RunLength;					/*	ランレングス				*/
};
 typedef	CONST struct MH_DC_Table1_t MH_DC_TABLE1_t;

/*----------------------------------*/
/*	ＭＨデコード２次テーブル		*/
/*----------------------------------*/
struct MH_DC_Table2_t {
	MH_DC_TABLE1_t   *Adr;				/*								*/
	UBYTE		MaskBit;			/*	マスクビット(01～1F)		*/
};
 typedef	CONST struct MH_DC_Table2_t MH_DC_TABLE2_t;

/*----------------------------------*/
/*	ＭＲデコードテーブル		*/
/*----------------------------------*/
struct MR_DC_Table_t {
	BYTE		ModeType;					/*					*/
};
 typedef	CONST struct MR_DC_Table_t MR_DC_TABLE_t;

/*---------------------------------------------*/
/* ﾒｯｾｰｼﾞ関連定義                              */
/*---------------------------------------------*/
#define MSG_SCDC_START			0
#define MSG_SCDC_DECODE_START	1
#define MSG_SCDC_TTI_COMPLETE	2
#define MSG_SCDC_PAGE_END		3
#define MSG_SCDC_BLOCK_START	4
#endif
