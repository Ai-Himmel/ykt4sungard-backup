#ifndef _KSENC_H_
#define _KSENC_H_

#include "ksdevice.h"

//////////////////////////////////////////////////////////////////////////
// �㷨������
#define ENC_MFSIZE "mfsize" // mf ��С������������ʾ
#define ENC_INIT_MINSECT "minsect" // ��ʼ����ʼ������
#define ENC_INIT_MAXSECT "maxsect" // ��ʼ������������


typedef enum {KR_READ=1,KR_WRITE=2,KR_INC=4,KR_DEC=8,KR_WRITEKEY=16} MF_KEY_RIGHT;


typedef struct _tagMFCardKey {
	uint8 key[6];
	KS_MF_KEYTYPE keytype;
}ks_mf_cardkey_t;

typedef struct {
	ks_mf_cardkey_t keys[2];
	uint8 ctrlbit[4];
	MF_KEY_RIGHT keya_right;
	MF_KEY_RIGHT keyb_right;
	KS_MF_KEYTYPE initkey;
}ks_mf_init_cardkey_t;

typedef struct {
	const char *version;
	const char *enc_name;
	int (KSAPI *get_card_param)(const char *param_name,char *param_value);
	int (KSAPI *set_main_key)(const uint8 *mainkey,int idx);
	int (KSAPI *get_key)(ks_card_info_t *card,ks_mf_cardkey_t *key,KS_MF_KEYTYPE t,int sect_no);
	int (KSAPI *get_key_by_right)(ks_card_info_t *card,ks_mf_cardkey_t *key,MF_KEY_RIGHT r,int sect_no);
	int (KSAPI *get_mf_init_key)(ks_card_info_t *card,ks_mf_init_cardkey_t *key,KS_MF_KEYTYPE t,int sect_no);
}ks_enc_op_t;


DECL_DLLFUNC(int,register_enc_op,(ks_enc_op_t *op));


#endif // _KSENC_H_
