#include "\src\atlanta\define\product.h"

#if (PRO_CPU_VERSION == SH7043_A)
#include "\src\cpu\sh7043_a\scd\define\scd.h"
#include "\src\cpu\sh7043_a\scd\ext_v\cphptbl.h"
#else
#include "\src\atlanta\scd\define\scd.h"
#include "\src\atlanta\scd\ext_v\cphptbl.h"
#endif

/*	暗号化エンコードで使用するローカル変数の初期化 */
void CipherEncodeInitial(void);

/*	暗号化デコードで使用するローカル変数の初期化  */
void CipherDecodeInitial(void);

/*	暗号化初期化 */
UWORD CipherInitial(void);

/*    １ライン分のＲＬをイメージに変換する */
void SCD1LineRlToImg(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);

/*	１ライン分のイメージをＲＬに変換する */
void SCD1LineImgToRl(struct WorkBuf_t *,struct CdcBlk_t *,UWORD);

/*	暗号化デコード */
UBYTE CipherDecode(UWORD);

/* ＭＨ、ＭＲ、ＭＭＲからビットマップにデコードする SAKAKI PRINT 用*/
UBYTE CodeToBitImage(UWORD);

/*	暗号化エンコード */
/* UBYTE CipherEncode(UWORD);By Y.Suzuki 1998/02/18 */
#define CipherEncode (*cph_enc_adr_tbl)

/*キー間違い検出通知*/
#define IncorrectKey (*incorrect_key_adr_tbl)

#define CuttingHeader (*cut_header_adr_tbl)

/*読み取り原稿上下逆時通知 （カラッポ） */
#define notify_upside_down (*notify_up_dw_adr_tbl)

void CopyImg1ToImg2(UWORD);
void CopyImg2ToImg1(UWORD);

/*	サービスラベル作成 */
/* UBYTE WriteLabel(void);By Y.Suzuki 1998/02/18 */
#define WriteLabel (*write_label_adr_tbl)

#define CuttingHeader (*cut_header_adr_tbl)

/*タスクスイッチ用ルーチン*/
#define show_slider (*show_slid_adr_tbl)

/*	スクランブル用ダミールーチン */
#if(0) /*By Y.Suzuki 1998/02/18*/
//void	CipherEncodeStart(void);
//void	CipherEncodeEnd(void);
//void	CipherDecodeStart(void);
//void	CipherDecodeEnd(void);
#endif
#define CipherEncodeStart (*cph_enc_st_adr_tbl)
#define CipherEncodeEnd (*cph_enc_ed_adr_tbl)
#define CipherDecodeStart (*cph_dec_st_adr_tbl)
#define CipherDecodeEnd (*cph_dec_ed_adr_tbl)



