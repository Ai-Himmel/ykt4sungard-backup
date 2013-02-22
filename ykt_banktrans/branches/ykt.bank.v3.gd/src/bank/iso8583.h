/*****************************iso8583.h******************************/

#ifndef _ISO8583_H
#define _ISO8583_H

#include <stdio.h>

#ifdef MY_DEBUG
#define MY_TRACE(x,args)  fprintf(stderr, x, args)
#else
#define MY_TRACE(x,args)
#endif

#define MY_BITGET(p,n)  ((p)[(n-1)/8]&(0x80>>((n-1)%8)))       //ȡbitλ
#define MY_BITSET(p,n)  ((p)[(n-1)/8]|=(0x80>>((n-1)%8)))      //��bitλ
#define MY_BITCLR(p,n)  ((p)[(n-1)/8]&=(~(0x80>>((n-1)%8))))   //��bitλ


/*
 * ISO8583�汾��Ϣ����ͬ�汾��ISO_DEF����g_isodef����Ͳ�ͬ,Ϊ0ʱ�Զ���
 */
#define ISO8583_VERSION  0

/*
 * �����������������׼Ϊ128��������Ҫ����Ϊ64
 */
#define ISO_FLDS 128

#define TYP_BIT  0
#define TYP_BCD  1
#define TYP_ASC  2
#define TYP_BIN  3

#define FMT_FIXED 0
#define FMT_LLVAR 2
#define FMT_LLLVAR 3

/*
 * ISO������ṹ����
 */
typedef struct tagISO_DEF {
 short typ;
 short fmt;
 int   len;
#if ISO8583_VERSION==93
 const char *dsc;
#endif
} ISO_DEF;

/*
 * ISO������ṹ����
 */
typedef struct tagISO_MSG {
 struct tagISO_FLD {
  int len;
  unsigned char *buf;
 } fld[ISO_FLDS+1];
} ISO_MSG;

/*
 * ��ISO_MSG����m���г�ʼ�����ʼ�����ȵ��ô˺���
 */
void iso8583_init(ISO_MSG *m);

/*
 * ����ISO_MSG����m�е�idxλ��ֵΪdata, data����Ϊlen.
 */
int iso8583_set(ISO_MSG *m, int idx, const unsigned char *data, int len);

/*
 * ȡ��ISO_MSG����m�е�idxλ��ֵ��data, ϣ����󳤶�Ϊlen.
 */
int iso8583_get(const ISO_MSG *m, int idx, unsigned char *data, int len);

/*
 * ��ISO_MSG����m�����ݰ�����õĸ�ʽ�����buf�С�
 */
int iso8583_pack(const ISO_MSG *m, char *buf);

/*
 * ��buf�����ݰ�����õĸ�ʽ�����ISO_MSG����m�С�
 */
int iso8583_unpack(ISO_MSG *m, const char *buf);

/*
 * ��ISO_MSG����m�����ݰ�����õĸ�ʽ���浽FILE�С�
 */
void iso8583_dump(FILE *fp, ISO_MSG *m);

/*
 * �ͷ�ISO_MSG����m�����ݼ�ռ�ÿռ�,unpack֮ǰҲ��Ҫfree.
 */
void iso8583_free(ISO_MSG *m);

#endif /* iso8583.h */
