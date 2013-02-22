/* des.h -
*/
#ifndef __DES_H__
#define __DES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================ 
* 函数名:    DES
* 参数:      [in] (unsigned char key[8])加密密钥, 8位无符号字符串指针
* 参数:      [in] (unsigned char source[8])待加密明文, 8位无符号字符串指针
* 参数:      [in] (unsigned char dest[8])加密后的密文, 8位无符号字符串
* 功能描述:  标准DES加密算法
* 返回值:    无
================================================================*/
extern void DES(unsigned char *key, unsigned char *text, unsigned char *mtext);

/*================================================================ 
* 函数名:    _DES
* 参数:      [in] (unsigned char key[8])加解密密钥, 8位无符号字符串指针
* 参数:      [in] (unsigned char source[8])待解密密文, 8位无符号字符串指针
* 参数:      [in] (unsigned char dest[8])解密后的明文, 8位无符号字符串
* 功能描述:  标准DES解密算法
* 返回值:    无
================================================================*/
extern void _DES(unsigned char *key, unsigned char *text, unsigned char *mtext);

extern void expand0(unsigned char *in, char *out);

extern void discrypt0(unsigned char *text, unsigned char *mtext);

extern void compress0(char *out, unsigned char *in);

extern void LS(unsigned char *bits, unsigned char *buffer, int count);

extern void setkeystar(char bits[64]);

extern void son(unsigned char *cc, unsigned char *dd, unsigned char *kk);

extern void F(int n, char *ll, char *rr, char *LL, char *RR);

extern void s_box(char *aa, char *bb);

extern void _ip(char *text, char *ll, char *rr);

extern void ip(unsigned char *text, char *ll, char *rr);

extern void encrypt0(unsigned char *text, unsigned char *mtext);

#ifdef __cplusplus
}
#endif

#endif