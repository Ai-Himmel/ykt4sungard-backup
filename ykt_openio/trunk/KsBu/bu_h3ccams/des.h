/***************************************************************************
*
*            (C) Copyright 2003 HUAWEI-3COM Technologies
*                         All Rights Reserved
*
***************************************************************************
* DESCRIPTION:
*   ʹ��DES/Triple DES�㷨����/�������ݿ�
*   �����ṩ��Java����ݵ�DES����/�����㷨����֧����JavaӦ�ó��������ݴ��͡�
*   ��Java�У������ݽ��м���/����ʱ�Ĵ���Ϊ��
*   1�����������ݳ��Ȳ��� 8 ��������ʱ����������Ϊ8�������������������µĿ�λ
*      �ֽ������������ַ��ĸ��������磺
*      �����������Ϊ 0x12 0x34 0x56 0x78 0x9A����������Ϊ��
*      0x12 0x34 0x56 0x78 0x9A 0x03 0x03 0x03��Ȼ���ٽ��м��ܴ���
*   2�����������ݳ����� 8 ��������ʱ��������8���ֽڿ����ݣ���ȫ������"0x08"��
*   ������������󣬽���ʱ��ȡ������ʵ�ʳ���Ϊ��
*   �������ݳ��� - �������������һ���ֽڵ�����
*
*   �ڼ���/�������ݿ�ʱ����ʹ�����º���
*   des_setup          ����DES��Կ
*   des_encrypt        ʹ��DES�㷨��������
*   des_decrypt        ʹ��DES�㷨��������
*   des3_setup         ����Triple-DES��Կ
*   des3_encrypt       ʹ��Triple-DES�㷨��������
*   des3_decrypt       ʹ��Triple-DES�㷨��������
*   ��DESΪ������������:
*
*   symmetric_key des;
*   if ((err = des_setup(DES_SECRET_KEY, &des)) != CRYPT_OK)
*   {
*       //������Կʧ��
*       return err;
*   }
*   //�������ݣ����ܺ����ݳ��ȱ�����outLen��
*   outLen = des_encrypt(bufIn, len, bufOut, size, &des);
*   if (outLen > 0)
*   {
*       //����bufOut�еļ��ܺ�����(����)
*   }
*   //�������ݣ����ܺ����ݳ��ȱ�����outLen��
*   outLen = des_decrypt(bufIn, len, bufOut, size, &des);
*   if (outLen > 0)
*   {
*       //����bufOut�еĽ��ܺ�����(����)
*   }
*
*   ʹ��Triple-DES�ķ��������������ͬ����ͬ�����ڣ�
*   DES�㷨�ĵ���ԿΪ64λ(8���ֽ�)����Triple-DES�㷨����Կ����Ϊ192λ(24���ֽ�)
***************************************************************************/

#ifndef _CRYPT_DES_H_
#define _CRYPT_DES_H_

#ifdef __cplusplus
extern "C" {
#endif

#define ROL(x, y) ( (((unsigned long)(x)<<(unsigned long)((y)&31)) | (((unsigned long)(x)&0xFFFFFFFFUL)>>(unsigned long)(32-((y)&31)))) & 0xFFFFFFFFUL)
#define ROR(x, y) ( ((((unsigned long)(x)&0xFFFFFFFFUL)>>(unsigned long)((y)&31)) | ((unsigned long)(x)<<(unsigned long)(32-((y)&31)))) & 0xFFFFFFFFUL)

#define STORE32H(x, y)                                                                     \
    { (y)[0] = (unsigned char)(((x)>>24)&255);   \
      (y)[1] = (unsigned char)(((x)>>16)&255);   \
      (y)[2] = (unsigned char)(((x)>>8)&255);    \
      (y)[3] = (unsigned char)((x)&255); }

#define LOAD32H(x, y)                            \
    { x = ((unsigned long)((y)[0] & 255)<<24) |  \
        ((unsigned long)((y)[1] & 255)<<16) |    \
        ((unsigned long)((y)[2] & 255)<<8)  |    \
        ((unsigned long)((y)[3] & 255)); }

#define CRYPT_OK 0
#define CRYPT_TEXT_LENGTH_ERROR -1

struct des_key {
    unsigned long ek[32];
    unsigned long dk[32];
};

struct des3_key {
    unsigned long ek[3][32];
    unsigned long dk[3][32];
};

typedef union Symmetric_key {
    struct des_key des;
    struct des3_key des3;
} symmetric_key;

extern int des_setup(const unsigned char *, symmetric_key *);
extern int des3_setup(const unsigned char *, symmetric_key *);
extern void des_ecb_encrypt(const unsigned char *, unsigned char *, symmetric_key *);
extern void des_ecb_decrypt(const unsigned char *, unsigned char *, symmetric_key *);
extern void des3_ecb_encrypt(const unsigned char *, unsigned char *, symmetric_key *);
extern void des3_ecb_decrypt(const unsigned char *, unsigned char *, symmetric_key *);

extern size_t des_encrypt(const unsigned char *, size_t, unsigned char *, size_t, symmetric_key *);
extern size_t des_decrypt(const unsigned char *, size_t, unsigned char *, size_t, symmetric_key *);
extern size_t des3_encrypt(const unsigned char *, size_t, unsigned char *, size_t, symmetric_key *);
extern size_t des3_decrypt(const unsigned char *, size_t, unsigned char *, size_t, symmetric_key *);

#ifdef __cplusplus
}
#endif

#endif //_CRYPT_DES_H_
