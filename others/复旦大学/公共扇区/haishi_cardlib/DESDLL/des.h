/* des.h -
*/
#ifndef __DES_H__
#define __DES_H__

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================ 
* ������:    DES
* ����:      [in] (unsigned char key[8])������Կ, 8λ�޷����ַ���ָ��
* ����:      [in] (unsigned char source[8])����������, 8λ�޷����ַ���ָ��
* ����:      [in] (unsigned char dest[8])���ܺ������, 8λ�޷����ַ���
* ��������:  ��׼DES�����㷨
* ����ֵ:    ��
================================================================*/
extern void DES(unsigned char *key, unsigned char *text, unsigned char *mtext);

/*================================================================ 
* ������:    _DES
* ����:      [in] (unsigned char key[8])�ӽ�����Կ, 8λ�޷����ַ���ָ��
* ����:      [in] (unsigned char source[8])����������, 8λ�޷����ַ���ָ��
* ����:      [in] (unsigned char dest[8])���ܺ������, 8λ�޷����ַ���
* ��������:  ��׼DES�����㷨
* ����ֵ:    ��
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