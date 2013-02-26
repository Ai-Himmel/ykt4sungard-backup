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

#include <string.h>
#include "des.h"

#define EN0 0
#define DE1 1

#ifdef CLEAN_STACK
void zeromem(void *dst, size_t len)
{
    unsigned char *mem = (unsigned char *)dst;
    while (len-- > 0)
        *mem++ = 0;
}

void burn_stack(unsigned long len)
{
    unsigned char buf[32];
    zeromem(buf, sizeof(buf));
    if (len > (unsigned long)sizeof(buf))
        burn_stack(len - sizeof(buf));
}
#endif

static const unsigned long bytebit[8] =
{
    0200, 0100, 040, 020, 010, 04, 02, 01
};

static const unsigned long bigbyte[24] =
{
    0x800000UL,  0x400000UL,  0x200000UL,  0x100000UL,
    0x80000UL,   0x40000UL,   0x20000UL,   0x10000UL,
    0x8000UL,    0x4000UL,    0x2000UL,    0x1000UL,
    0x800UL,     0x400UL,     0x200UL,     0x100UL,
    0x80UL,      0x40UL,      0x20UL,      0x10UL,
    0x8UL,       0x4UL,       0x2UL,       0x1L
};

/* Use the key schedule specific in the standard (ANSI X3.92-1981) */

static const unsigned char pc1[56] = {
    56, 48, 40, 32, 24, 16,  8,  0, 57, 49, 41, 33, 25, 17,
     9,  1, 58, 50, 42, 34, 26, 18, 10,  2, 59, 51, 43, 35,
    62, 54, 46, 38, 30, 22, 14,  6, 61, 53, 45, 37, 29, 21,
    13,  5, 60, 52, 44, 36, 28, 20, 12,  4, 27, 19, 11,  3
};

static const unsigned char totrot[16] = {
    1,   2,  4,  6,
    8,  10, 12, 14,
    15, 17, 19, 21,
    23, 25, 27, 28
};

static const unsigned char pc2[48] = {
    13, 16, 10, 23,  0,  4,      2, 27, 14,  5, 20,  9,
    22, 18, 11,  3, 25,  7,     15,  6, 26, 19, 12,  1,
    40, 51, 30, 36, 46, 54,     29, 39, 50, 44, 32, 47,
    43, 48, 38, 55, 33, 52,     45, 41, 49, 35, 28, 31
};


static const unsigned long SP1[64] =
{
    0x01010400UL, 0x00000000UL, 0x00010000UL, 0x01010404UL,
    0x01010004UL, 0x00010404UL, 0x00000004UL, 0x00010000UL,
    0x00000400UL, 0x01010400UL, 0x01010404UL, 0x00000400UL,
    0x01000404UL, 0x01010004UL, 0x01000000UL, 0x00000004UL,
    0x00000404UL, 0x01000400UL, 0x01000400UL, 0x00010400UL,
    0x00010400UL, 0x01010000UL, 0x01010000UL, 0x01000404UL,
    0x00010004UL, 0x01000004UL, 0x01000004UL, 0x00010004UL,
    0x00000000UL, 0x00000404UL, 0x00010404UL, 0x01000000UL,
    0x00010000UL, 0x01010404UL, 0x00000004UL, 0x01010000UL,
    0x01010400UL, 0x01000000UL, 0x01000000UL, 0x00000400UL,
    0x01010004UL, 0x00010000UL, 0x00010400UL, 0x01000004UL,
    0x00000400UL, 0x00000004UL, 0x01000404UL, 0x00010404UL,
    0x01010404UL, 0x00010004UL, 0x01010000UL, 0x01000404UL,
    0x01000004UL, 0x00000404UL, 0x00010404UL, 0x01010400UL,
    0x00000404UL, 0x01000400UL, 0x01000400UL, 0x00000000UL,
    0x00010004UL, 0x00010400UL, 0x00000000UL, 0x01010004UL
};

static const unsigned long SP2[64] =
{
    0x80108020UL, 0x80008000UL, 0x00008000UL, 0x00108020UL,
    0x00100000UL, 0x00000020UL, 0x80100020UL, 0x80008020UL,
    0x80000020UL, 0x80108020UL, 0x80108000UL, 0x80000000UL,
    0x80008000UL, 0x00100000UL, 0x00000020UL, 0x80100020UL,
    0x00108000UL, 0x00100020UL, 0x80008020UL, 0x00000000UL,
    0x80000000UL, 0x00008000UL, 0x00108020UL, 0x80100000UL,
    0x00100020UL, 0x80000020UL, 0x00000000UL, 0x00108000UL,
    0x00008020UL, 0x80108000UL, 0x80100000UL, 0x00008020UL,
    0x00000000UL, 0x00108020UL, 0x80100020UL, 0x00100000UL,
    0x80008020UL, 0x80100000UL, 0x80108000UL, 0x00008000UL,
    0x80100000UL, 0x80008000UL, 0x00000020UL, 0x80108020UL,
    0x00108020UL, 0x00000020UL, 0x00008000UL, 0x80000000UL,
    0x00008020UL, 0x80108000UL, 0x00100000UL, 0x80000020UL,
    0x00100020UL, 0x80008020UL, 0x80000020UL, 0x00100020UL,
    0x00108000UL, 0x00000000UL, 0x80008000UL, 0x00008020UL,
    0x80000000UL, 0x80100020UL, 0x80108020UL, 0x00108000UL
};

static const unsigned long SP3[64] =
{
    0x00000208UL, 0x08020200UL, 0x00000000UL, 0x08020008UL,
    0x08000200UL, 0x00000000UL, 0x00020208UL, 0x08000200UL,
    0x00020008UL, 0x08000008UL, 0x08000008UL, 0x00020000UL,
    0x08020208UL, 0x00020008UL, 0x08020000UL, 0x00000208UL,
    0x08000000UL, 0x00000008UL, 0x08020200UL, 0x00000200UL,
    0x00020200UL, 0x08020000UL, 0x08020008UL, 0x00020208UL,
    0x08000208UL, 0x00020200UL, 0x00020000UL, 0x08000208UL,
    0x00000008UL, 0x08020208UL, 0x00000200UL, 0x08000000UL,
    0x08020200UL, 0x08000000UL, 0x00020008UL, 0x00000208UL,
    0x00020000UL, 0x08020200UL, 0x08000200UL, 0x00000000UL,
    0x00000200UL, 0x00020008UL, 0x08020208UL, 0x08000200UL,
    0x08000008UL, 0x00000200UL, 0x00000000UL, 0x08020008UL,
    0x08000208UL, 0x00020000UL, 0x08000000UL, 0x08020208UL,
    0x00000008UL, 0x00020208UL, 0x00020200UL, 0x08000008UL,
    0x08020000UL, 0x08000208UL, 0x00000208UL, 0x08020000UL,
    0x00020208UL, 0x00000008UL, 0x08020008UL, 0x00020200UL
};

static const unsigned long SP4[64] =
{
    0x00802001UL, 0x00002081UL, 0x00002081UL, 0x00000080UL,
    0x00802080UL, 0x00800081UL, 0x00800001UL, 0x00002001UL,
    0x00000000UL, 0x00802000UL, 0x00802000UL, 0x00802081UL,
    0x00000081UL, 0x00000000UL, 0x00800080UL, 0x00800001UL,
    0x00000001UL, 0x00002000UL, 0x00800000UL, 0x00802001UL,
    0x00000080UL, 0x00800000UL, 0x00002001UL, 0x00002080UL,
    0x00800081UL, 0x00000001UL, 0x00002080UL, 0x00800080UL,
    0x00002000UL, 0x00802080UL, 0x00802081UL, 0x00000081UL,
    0x00800080UL, 0x00800001UL, 0x00802000UL, 0x00802081UL,
    0x00000081UL, 0x00000000UL, 0x00000000UL, 0x00802000UL,
    0x00002080UL, 0x00800080UL, 0x00800081UL, 0x00000001UL,
    0x00802001UL, 0x00002081UL, 0x00002081UL, 0x00000080UL,
    0x00802081UL, 0x00000081UL, 0x00000001UL, 0x00002000UL,
    0x00800001UL, 0x00002001UL, 0x00802080UL, 0x00800081UL,
    0x00002001UL, 0x00002080UL, 0x00800000UL, 0x00802001UL,
    0x00000080UL, 0x00800000UL, 0x00002000UL, 0x00802080UL
};

static const unsigned long SP5[64] =
{
    0x00000100UL, 0x02080100UL, 0x02080000UL, 0x42000100UL,
    0x00080000UL, 0x00000100UL, 0x40000000UL, 0x02080000UL,
    0x40080100UL, 0x00080000UL, 0x02000100UL, 0x40080100UL,
    0x42000100UL, 0x42080000UL, 0x00080100UL, 0x40000000UL,
    0x02000000UL, 0x40080000UL, 0x40080000UL, 0x00000000UL,
    0x40000100UL, 0x42080100UL, 0x42080100UL, 0x02000100UL,
    0x42080000UL, 0x40000100UL, 0x00000000UL, 0x42000000UL,
    0x02080100UL, 0x02000000UL, 0x42000000UL, 0x00080100UL,
    0x00080000UL, 0x42000100UL, 0x00000100UL, 0x02000000UL,
    0x40000000UL, 0x02080000UL, 0x42000100UL, 0x40080100UL,
    0x02000100UL, 0x40000000UL, 0x42080000UL, 0x02080100UL,
    0x40080100UL, 0x00000100UL, 0x02000000UL, 0x42080000UL,
    0x42080100UL, 0x00080100UL, 0x42000000UL, 0x42080100UL,
    0x02080000UL, 0x00000000UL, 0x40080000UL, 0x42000000UL,
    0x00080100UL, 0x02000100UL, 0x40000100UL, 0x00080000UL,
    0x00000000UL, 0x40080000UL, 0x02080100UL, 0x40000100UL
};

static const unsigned long SP6[64] =
{
    0x20000010UL, 0x20400000UL, 0x00004000UL, 0x20404010UL,
    0x20400000UL, 0x00000010UL, 0x20404010UL, 0x00400000UL,
    0x20004000UL, 0x00404010UL, 0x00400000UL, 0x20000010UL,
    0x00400010UL, 0x20004000UL, 0x20000000UL, 0x00004010UL,
    0x00000000UL, 0x00400010UL, 0x20004010UL, 0x00004000UL,
    0x00404000UL, 0x20004010UL, 0x00000010UL, 0x20400010UL,
    0x20400010UL, 0x00000000UL, 0x00404010UL, 0x20404000UL,
    0x00004010UL, 0x00404000UL, 0x20404000UL, 0x20000000UL,
    0x20004000UL, 0x00000010UL, 0x20400010UL, 0x00404000UL,
    0x20404010UL, 0x00400000UL, 0x00004010UL, 0x20000010UL,
    0x00400000UL, 0x20004000UL, 0x20000000UL, 0x00004010UL,
    0x20000010UL, 0x20404010UL, 0x00404000UL, 0x20400000UL,
    0x00404010UL, 0x20404000UL, 0x00000000UL, 0x20400010UL,
    0x00000010UL, 0x00004000UL, 0x20400000UL, 0x00404010UL,
    0x00004000UL, 0x00400010UL, 0x20004010UL, 0x00000000UL,
    0x20404000UL, 0x20000000UL, 0x00400010UL, 0x20004010UL
};

static const unsigned long SP7[64] =
{
    0x00200000UL, 0x04200002UL, 0x04000802UL, 0x00000000UL,
    0x00000800UL, 0x04000802UL, 0x00200802UL, 0x04200800UL,
    0x04200802UL, 0x00200000UL, 0x00000000UL, 0x04000002UL,
    0x00000002UL, 0x04000000UL, 0x04200002UL, 0x00000802UL,
    0x04000800UL, 0x00200802UL, 0x00200002UL, 0x04000800UL,
    0x04000002UL, 0x04200000UL, 0x04200800UL, 0x00200002UL,
    0x04200000UL, 0x00000800UL, 0x00000802UL, 0x04200802UL,
    0x00200800UL, 0x00000002UL, 0x04000000UL, 0x00200800UL,
    0x04000000UL, 0x00200800UL, 0x00200000UL, 0x04000802UL,
    0x04000802UL, 0x04200002UL, 0x04200002UL, 0x00000002UL,
    0x00200002UL, 0x04000000UL, 0x04000800UL, 0x00200000UL,
    0x04200800UL, 0x00000802UL, 0x00200802UL, 0x04200800UL,
    0x00000802UL, 0x04000002UL, 0x04200802UL, 0x04200000UL,
    0x00200800UL, 0x00000000UL, 0x00000002UL, 0x04200802UL,
    0x00000000UL, 0x00200802UL, 0x04200000UL, 0x00000800UL,
    0x04000002UL, 0x04000800UL, 0x00000800UL, 0x00200002UL
};

static const unsigned long SP8[64] =
{
    0x10001040UL, 0x00001000UL, 0x00040000UL, 0x10041040UL,
    0x10000000UL, 0x10001040UL, 0x00000040UL, 0x10000000UL,
    0x00040040UL, 0x10040000UL, 0x10041040UL, 0x00041000UL,
    0x10041000UL, 0x00041040UL, 0x00001000UL, 0x00000040UL,
    0x10040000UL, 0x10000040UL, 0x10001000UL, 0x00001040UL,
    0x00041000UL, 0x00040040UL, 0x10040040UL, 0x10041000UL,
    0x00001040UL, 0x00000000UL, 0x00000000UL, 0x10040040UL,
    0x10000040UL, 0x10001000UL, 0x00041040UL, 0x00040000UL,
    0x00041040UL, 0x00040000UL, 0x10041000UL, 0x00001000UL,
    0x00000040UL, 0x10040040UL, 0x00001000UL, 0x00041040UL,
    0x10001000UL, 0x00000040UL, 0x10000040UL, 0x10040000UL,
    0x10040040UL, 0x10000000UL, 0x00040000UL, 0x10001040UL,
    0x00000000UL, 0x10041040UL, 0x00040040UL, 0x10000040UL,
    0x10040000UL, 0x10001000UL, 0x10001040UL, 0x00000000UL,
    0x10041040UL, 0x00041000UL, 0x00041000UL, 0x00001040UL,
    0x00001040UL, 0x00040040UL, 0x10000000UL, 0x10041000UL
};


static void cookey(const unsigned long *raw1, unsigned long *keyout);

#ifdef CLEAN_STACK
void _deskey(const unsigned char *key, short edf, unsigned long *keyout)
#else
void deskey(const unsigned char *key, short edf, unsigned long *keyout)
#endif
{
    unsigned long i, j, l, m, n, kn[32];
    unsigned char pc1m[56], pcr[56];

    for (j=0; j < 56; j++) {
        l = (unsigned long)pc1[j];
        m = l & 7;
        pc1m[j] = (unsigned char)((key[l >> 3U] & bytebit[m]) == bytebit[m] ? 1 : 0);
    }

    for (i=0; i < 16; i++) {
        if (edf == DE1) {
           m = (15 - i) << 1;
        } else {
           m = i << 1;
        }
        n = m + 1;
        kn[m] = kn[n] = 0L;
        for (j=0; j < 28; j++) {
            l = j + (unsigned long)totrot[i];
            if (l < 28) {
               pcr[j] = pc1m[l];
            } else {
               pcr[j] = pc1m[l - 28];
            }
        }
        for (/*j = 28*/; j < 56; j++) {
            l = j + (unsigned long)totrot[i];
            if (l < 56) {
               pcr[j] = pc1m[l];
            } else {
               pcr[j] = pc1m[l - 28];
            }
        }
        for (j=0; j < 24; j++)  {
            if ((int)pcr[(int)pc2[j]] != 0) {
               kn[m] |= bigbyte[j];
            }
            if ((int)pcr[(int)pc2[j+24]] != 0) {
               kn[n] |= bigbyte[j];
            }
        }
    }

    cookey(kn, keyout);
}

#ifdef CLEAN_STACK
void deskey(const unsigned char *key, short edf, unsigned long *keyout)
{
   _deskey(key, edf, keyout);
   burn_stack(sizeof(int)*5 + sizeof(unsigned long)*32 + sizeof(unsigned char)*112);
}
#endif

#ifdef CLEAN_STACK
static void _cookey(const unsigned long *raw1, unsigned long *keyout)
#else
static void cookey(const unsigned long *raw1, unsigned long *keyout)
#endif
{
    unsigned long *cook;
    const unsigned long *raw0;
    unsigned long dough[32];
    int i;

    cook = dough;
    for(i=0; i < 16; i++, raw1++)
    {
        raw0 = raw1++;
        *cook    = (*raw0 & 0x00fc0000L) << 6;
        *cook   |= (*raw0 & 0x00000fc0L) << 10;
        *cook   |= (*raw1 & 0x00fc0000L) >> 10;
        *cook++ |= (*raw1 & 0x00000fc0L) >> 6;
        *cook    = (*raw0 & 0x0003f000L) << 12;
        *cook   |= (*raw0 & 0x0000003fL) << 16;
        *cook   |= (*raw1 & 0x0003f000L) >> 4;
        *cook++ |= (*raw1 & 0x0000003fL);
    }

    memcpy(keyout, dough, sizeof dough);
}

#ifdef CLEAN_STACK
static void cookey(const unsigned long *raw1, unsigned long *keyout)
{
   _cookey(raw1, keyout);
   burn_stack(sizeof(unsigned long *) * 2 + sizeof(unsigned long)*32 + sizeof(int));
}
#endif

#ifndef CLEAN_STACK
static void desfunc(unsigned long *block, const unsigned long *keys)
#else
static void _desfunc(unsigned long *block, const unsigned long *keys)
#endif
{
    unsigned long work, right, leftt;
    int round;

    leftt = block[0];
    right = block[1];

    work = ((leftt >> 4)  ^ right) & 0x0f0f0f0fL;
    right ^= work;
    leftt ^= (work << 4);

    work = ((leftt >> 16) ^ right) & 0x0000ffffL;
    right ^= work;
    leftt ^= (work << 16);

    work = ((right >> 2)  ^ leftt) & 0x33333333L;
    leftt ^= work;
    right ^= (work << 2);

    work = ((right >> 8)  ^ leftt) & 0x00ff00ffL;
    leftt ^= work;
    right ^= (work << 8);

    right = ROL(right, 1);
    work = (leftt ^ right) & 0xaaaaaaaaL;

    leftt ^= work;
    right ^= work;
    leftt = ROL(leftt, 1);

    for (round = 0; round < 8; round++) {
        work  = ROR(right, 4) ^ *keys++;
        leftt ^= SP7[work        & 0x3fL]
              ^ SP5[(work >>  8) & 0x3fL]
              ^ SP3[(work >> 16) & 0x3fL]
              ^ SP1[(work >> 24) & 0x3fL];
        work  = right ^ *keys++;
        leftt ^= SP8[ work        & 0x3fL]
              ^  SP6[(work >>  8) & 0x3fL]
              ^  SP4[(work >> 16) & 0x3fL]
              ^  SP2[(work >> 24) & 0x3fL];

        work = ROR(leftt, 4) ^ *keys++;
        right ^= SP7[ work        & 0x3fL]
              ^  SP5[(work >>  8) & 0x3fL]
              ^  SP3[(work >> 16) & 0x3fL]
              ^  SP1[(work >> 24) & 0x3fL];
        work  = leftt ^ *keys++;
        right ^= SP8[ work        & 0x3fL]
              ^  SP6[(work >>  8) & 0x3fL]
              ^  SP4[(work >> 16) & 0x3fL]
              ^  SP2[(work >> 24) & 0x3fL];
    }
    right = (right << 31) | (right >> 1);
    work = (leftt ^ right) & 0xaaaaaaaaL;
    leftt ^= work;
    right ^= work;
    leftt = (leftt << 31) | (leftt >> 1);
    work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
    right ^= work;
    leftt ^= (work << 8);
    // --
    work = ((leftt >> 2) ^ right) & 0x33333333L;
    right ^= work;
    leftt ^= (work << 2);
    work = ((right >> 16) ^ leftt) & 0x0000ffffL;
    leftt ^= work;
    right ^= (work << 16);
    work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
    leftt ^= work;
    right ^= (work << 4);

    block[0] = right;
    block[1] = leftt;
}

#ifdef CLEAN_STACK
static void desfunc(unsigned long *block, const unsigned long *keys)
{
   _desfunc(block, keys);
   burn_stack(sizeof(unsigned long) * 4 + sizeof(int));
}
#endif

/*
 *  初始化DES算法密钥，并获取DES对称密钥，在加密/解密时使用
 *
 *  key:  用于加密/解密的DES密钥，必须为64位(8个字节)
 *  skey: 初始化得到的对称密钥，在加密/解密时使用
 */
int des_setup(const unsigned char *key, symmetric_key *skey)
{

    deskey(key, EN0, skey->des.ek);
    deskey(key, DE1, skey->des.dk);

    return CRYPT_OK;
}

/*
 *  初始化Triple-DES算法密钥，并获取Triple-DES对称密钥，在加密/解密时使用
 *
 *  key:  用于加密/解密的Triple-DES密钥，必须为192位(24个字节)
 *  skey: 初始化得到的对称密钥，在加密/解密时使用
 */
int des3_setup(const unsigned char *key, symmetric_key *skey)
{
    deskey(key,    EN0, skey->des3.ek[0]);
    deskey(key+8,  DE1, skey->des3.ek[1]);
    deskey(key+16, EN0, skey->des3.ek[2]);

    deskey(key,    DE1, skey->des3.dk[2]);
    deskey(key+8,  EN0, skey->des3.dk[1]);
    deskey(key+16, DE1, skey->des3.dk[0]);

    return CRYPT_OK;
}

/*
 *  使用DES算法加密一个8字节的数据块
 *
 *  pt:   指向需要加密的明文(Plain Text)数据块的指针;
 *  ct:   指向存放加密后的密文(Crypto Text)数据地址的指针;
 *  key:  用于加密使用的对称密钥
 *
 */
void des_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key)
{
    unsigned long work[2];
    LOAD32H(work[0], pt+0);
    LOAD32H(work[1], pt+4);
    desfunc(work, key->des.ek);
    STORE32H(work[0],ct+0);
    STORE32H(work[1],ct+4);
}

/*
 *  使用DES算法解密一个8字节的数据块
 *
 *  ct:   指向密文(Crypto Text)数据块的指针;
 *  pt:   指向解密后的明文(Plain Text)数据块的指针;
 *  key:  用于解密使用的对称密钥
 *
 */
void des_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key)
{
    unsigned long work[2];
    LOAD32H(work[0], ct+0);
    LOAD32H(work[1], ct+4);
    desfunc(work, key->des.dk);
    STORE32H(work[0],pt+0);
    STORE32H(work[1],pt+4);
}

/*
 *  使用Triple-DES算法加密一个8字节的数据块
 *
 *  pt:   指向需要加密的明文(Plain Text)数据块的指针;
 *  ct:   指向存放加密后的密文(Crypto Text)数据地址的指针;
 *  key:  用于加密使用的对称密钥
 *
 */
void des3_ecb_encrypt(const unsigned char *pt, unsigned char *ct, symmetric_key *key)
{
    unsigned long work[2];

    LOAD32H(work[0], pt+0);
    LOAD32H(work[1], pt+4);
    desfunc(work, key->des3.ek[0]);
    desfunc(work, key->des3.ek[1]);
    desfunc(work, key->des3.ek[2]);
    STORE32H(work[0],ct+0);
    STORE32H(work[1],ct+4);
}

/*
 *  使用Triple-DES算法解密一个8字节的数据块
 *
 *  ct:   指向密文(Crypto Text)数据块的指针;
 *  pt:   指向解密后的明文(Plain Text)数据块的指针;
 *  key:  用于解密使用的对称密钥
 *
 */
void des3_ecb_decrypt(const unsigned char *ct, unsigned char *pt, symmetric_key *key)
{
    unsigned long work[2];
    LOAD32H(work[0], ct+0);
    LOAD32H(work[1], ct+4);
    desfunc(work, key->des3.dk[0]);
    desfunc(work, key->des3.dk[1]);
    desfunc(work, key->des3.dk[2]);
    STORE32H(work[0],pt+0);
    STORE32H(work[1],pt+4);
}

/*
 *  使用DES算法加密数据块
 *
 *  pt:    指向需要加密的明文(Plain Text)数据块的指针;
 *  len:   需要加密的明文长度(字节数);
 *  ct:    指向存放加密后的密文(Crypto Text)数据地址的指针;
 *  nSize: 用于存放加密后密文的数据缓冲区长度(ct的长度)
 *  key:   用于加密使用的对称密钥
 *
 *  返回值:
 *  如果加密成功，则返回加密后密文的长度
 *  如果存放密文的数据缓冲区长度不够，则返回CRYPT_TEXT_LENGTH_ERROR(-1)
 *
 *  注意: 用于存放密文的数据地址块的长度必须满足以下要求
 *        该长度必须大于 len，且必须大于8的整数倍，即
 *        该长度不能少于 ((len / 8) + 1) * 8
 */
size_t des_encrypt(const unsigned char *pt, size_t len,
				   unsigned char *ct, size_t nSize, symmetric_key *key)
{
    size_t i, ctlen, remainder;
    unsigned char text[8];
    //保证加密后的长度为8的倍数
    ctlen = ((len / 8) + 1) * 8;
	if (nSize < ctlen)
		return CRYPT_TEXT_LENGTH_ERROR;
    for (i = 0; i < len / 8; i++)
        des_ecb_encrypt(pt + (i * 8), ct + (i * 8), key);
    remainder = 8 - len % 8;
    memcpy(text, pt + (i * 8), len % 8);
    memset(text + len % 8, remainder, remainder);
    des_ecb_encrypt(text, ct + (i * 8), key);
    return ctlen;
}

/*
 *  使用DES算法解密数据块
 *
 *  ct:    指向密文(Crypto Text)数据块的指针;
 *  len:   密文长度(字节数), 必须为8的整数倍;
 *  pt:    指向解密后的明文(Plain Text)数据块的指针;
 *  nSize: 用于存放解密后明文的数据缓冲区长度(pt的长度)
 *  key:   用于解密使用的对称密钥
 *
 *  返回值:
 *  如果解密成功，则返回解密后明文的长度
 *  如果 len 不是8的整数倍，或存放明文的数据缓冲区长度不够，
 *  则返回 CRYPT_TEXT_LENGTH_ERROR(-1)
 *
 *  注意: 用于存放明文的数据地址块的长度不能少于密文长度
 */
size_t des_decrypt(const unsigned char *ct, size_t len,
				   unsigned char *pt, size_t nSize, symmetric_key *key)
{
    size_t i, ptlen;
    //保证长度为8的倍数
    if (len % 8 != 0)
        return CRYPT_TEXT_LENGTH_ERROR;
	if (nSize < len)
		return CRYPT_TEXT_LENGTH_ERROR;
    for (i = 0; i < len / 8; i++)
        des_ecb_decrypt(ct + (i * 8), pt + (i * 8), key);
    ptlen = len - pt[len - 1];
    return ptlen;
}

/*
 *  使用Triple-DES算法加密数据块
 *
 *  pt:    指向需要加密的明文(Plain Text)数据块的指针;
 *  len:   需要加密的明文长度(字节数);
 *  ct:    指向存放加密后的密文(Crypto Text)数据地址的指针;
 *  nSize: 用于存放加密后密文的数据缓冲区长度(ct的长度)
 *  key:   用于加密使用的对称密钥
 *
 *  返回值:
 *  如果加密成功，则返回加密后密文的长度
 *  如果存放密文的数据缓冲区长度不够，则返回CRYPT_TEXT_LENGTH_ERROR(-1)
 *
 *  注意: 用于存放密文的数据地址块的长度必须满足以下要求
 *        该长度必须大于 len，且必须大于8的整数倍，即
 *        该长度不能少于 ((len / 8) + 1) * 8
 */
size_t des3_encrypt(const unsigned char *pt, size_t len,
					unsigned char *ct, size_t nSize, symmetric_key *key)
{
    size_t i, ctlen, remainder;
    unsigned char text[8];
    //保证加密后的长度为8的倍数
    ctlen = ((len / 8) + 1) * 8;
	if (nSize < ctlen)
		return CRYPT_TEXT_LENGTH_ERROR;
    for (i = 0; i < len / 8; i++)
        des3_ecb_encrypt(pt + (i * 8), ct + (i * 8), key);
    remainder = 8 - len % 8;
    memcpy(text, pt + (i * 8), len % 8);
    memset(text + len % 8, remainder, remainder);
    des3_ecb_encrypt(text, ct + (i * 8), key);
    return ctlen;
}

/*
 *  使用Triple-DES算法解密数据块
 *
 *  ct:    指向密文(Crypto Text)数据块的指针;
 *  len:   密文长度(字节数), 必须为8的整数倍;
 *  pt:    指向解密后的明文(Plain Text)数据块的指针;
 *  nSize: 用于存放解密后明文的数据缓冲区长度(pt的长度)
 *  key:   用于解密使用的对称密钥
 *
 *  返回值:
 *  如果解密成功，则返回解密后明文的长度
 *  如果 len 不是8的整数倍，或存放明文的数据缓冲区长度不够，
 *  则返回 CRYPT_TEXT_LENGTH_ERROR(-1)
 *
 *  注意: 用于存放明文的数据地址块的长度不能少于密文长度
 */
size_t des3_decrypt(const unsigned char *ct, size_t len,
					unsigned char *pt, size_t nSize, symmetric_key *key)
{
    size_t i, ptlen;
    //保证长度为8的倍数
    if (len % 8 != 0)
        return CRYPT_TEXT_LENGTH_ERROR;
	if (nSize < len)
		return CRYPT_TEXT_LENGTH_ERROR;
    for (i = 0; i < len / 8; i++)
        des3_ecb_decrypt(ct + (i * 8), pt + (i * 8), key);
    ptlen = len - pt[len - 1];
    return ptlen;
}
