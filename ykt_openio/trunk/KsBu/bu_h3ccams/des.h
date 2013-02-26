/***************************************************************************
*
*            (C) Copyright 2003 HUAWEI-3COM Technologies
*                         All Rights Reserved
*
***************************************************************************
* DESCRIPTION:
*   使用DES/Triple DES算法加密/解密数据块
*   该类提供与Java相兼容的DES加密/解密算法，可支持与Java应用程序间的数据传送。
*   在Java中，对数据进行加密/解密时的处理为：
*   1、当加密数据长度不是 8 的整数倍时，将其扩充为8的整数倍，并在在余下的空位
*      字节中填入扩充字符的个数。例如：
*      如果加密数据为 0x12 0x34 0x56 0x78 0x9A，则将其扩充为：
*      0x12 0x34 0x56 0x78 0x9A 0x03 0x03 0x03，然后再进行加密处理、
*   2、当加密数据长度是 8 的整数倍时，再扩充8个字节空数据，并全部填入"0x08"。
*   经过这样处理后，解密时获取的明文实际长度为：
*   密文数据长度 - 明文数据中最后一个字节的数据
*
*   在加密/解密数据块时，请使用如下函数
*   des_setup          创建DES密钥
*   des_encrypt        使用DES算法加密数据
*   des_decrypt        使用DES算法解密数据
*   des3_setup         创建Triple-DES密钥
*   des3_encrypt       使用Triple-DES算法加密数据
*   des3_decrypt       使用Triple-DES算法解密数据
*   以DES为例，代码如下:
*
*   symmetric_key des;
*   if ((err = des_setup(DES_SECRET_KEY, &des)) != CRYPT_OK)
*   {
*       //创建密钥失败
*       return err;
*   }
*   //加密数据，加密后数据长度保存在outLen中
*   outLen = des_encrypt(bufIn, len, bufOut, size, &des);
*   if (outLen > 0)
*   {
*       //处理bufOut中的加密后数据(密文)
*   }
*   //解密数据，解密后数据长度保存在outLen中
*   outLen = des_decrypt(bufIn, len, bufOut, size, &des);
*   if (outLen > 0)
*   {
*       //处理bufOut中的解密后数据(明文)
*   }
*
*   使用Triple-DES的方法与上面基本相同，不同处在于：
*   DES算法的的密钥为64位(8个字节)，而Triple-DES算法的密钥长度为192位(24个字节)
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
