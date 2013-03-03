#ifndef syskey_h
	#define syskey_h

#include "\src\atlanta\define\sysmax.h"

/******************************************
 * キーブック用パラメータ
 * struct KeyBookTbl_t SYB_KeyBookData
 * 1997/6/2
 * 鈴木郁二
 ******************************************/
struct KeyTbl_t {
	UBYTE	Key[SYS_KEY_MAX];				/*	暗号化キー 半角２４桁＋null	*/
	UBYTE	KeyClue[SYS_KEY_CLUE_MAX];		/*	キーのヒント 半角３４桁＋null	*/
	UBYTE	KeyName[SYS_BOX_NAME_MAX];		/*	キーの名前 １６桁+null	*/
	UWORD	KeyPassCode;					/*	キーのパスコード	*/
};

struct KeyBookTbl_t {
	UWORD	CipherPassCode;							/*	暗号化設定のパスコード	*/
	UBYTE	DefaultKeyNo;							/*	デフォルトで使用するキーのキーブックNO.	*/
	UBYTE	OffsetServiceLabel;						/*	サービスラベルのオフセット	*/
	UBYTE	KeyExtensionOn;							/*	拡張キー有無	*/
	UBYTE	NoiseRemovalOn;							/*	ノイズ除去	*/
	struct KeyTbl_t SYB_KeyData[SYS_KEY_BOOK_MAX];
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/12/19
*             TYPE:  struct
*      VAR TO HOLD:  struct SYS_CipherData_t SYB_CipherPData[SYS_PROGRAM_MAX]
*      DESCRIPTION:  暗号化送信用キーデータ（プログラムワンタッチ登録用）
************************************************************************/
struct SYS_CipherTxData_t {
	UBYTE	SetKeyMode;					/* キー入力の設定方法（デフォルト・キーブック・直接）	*/
	UBYTE	KeyNumber;					/* キー番号（キーブック選択時セット）					*/
	UBYTE	Key[SYS_KEY_MAX];			/* 暗号化キー（直接選択時セット）						*/
	UBYTE	KeyClue[SYS_KEY_CLUE_MAX];	/* 暗号化キーのヒント（直接選択時セット）				*/
	UBYTE	KeyExtensionOn;				/* 拡張キー設定（直接選択時セット）						*/
	UBYTE	Dummy;						/* ダミー（構造体の空きエリアを予め確保）				*/
};

/************************************************************************
*               BY:  K.Watanabe
*             DATE:  1997/12/19
*             TYPE:  define
*      VAR TO HOLD:  SYB_CipherPData[].SetKeyMode
*      DESCRIPTION:  キー入力の設定方法
************************************************************************/
#define	SYS_CIPHER_KEY_DEFAULT	0x00	/* デフォルトキーを使用	*/
#define	SYS_CIPHER_KEY_BOOK		0x01	/* キーブックから選択	*/
#define	SYS_CIPHER_KEY_DIRECT	0x02	/* 直接入力				*/

#endif
