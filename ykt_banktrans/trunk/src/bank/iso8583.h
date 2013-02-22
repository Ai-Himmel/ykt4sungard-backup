/*****************************iso8583.h******************************/

#ifndef _ISO8583_H
#define _ISO8583_H

#include <stdio.h>

#ifdef MY_DEBUG
#define MY_TRACE(x,args)  fprintf(stderr, x, args)
#else
#define MY_TRACE(x,args)
#endif

#define MY_BITGET(p,n)  ((p)[(n-1)/8]&(0x80>>((n-1)%8)))       //取bit位
#define MY_BITSET(p,n)  ((p)[(n-1)/8]|=(0x80>>((n-1)%8)))      //设bit位
#define MY_BITCLR(p,n)  ((p)[(n-1)/8]&=(~(0x80>>((n-1)%8))))   //清bit位


/*
 * ISO8583版本信息，不同版本，ISO_DEF变量g_isodef定义就不同,为0时自定义
 */
#define ISO8583_VERSION  0

/*
 * 数据域个数，正常标准为128，如有需要可以为64
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
 * ISO定义域结构定义
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
 * ISO数据域结构定义
 */
typedef struct tagISO_MSG {
 struct tagISO_FLD {
  int len;
  unsigned char *buf;
 } fld[ISO_FLDS+1];
} ISO_MSG;

/*
 * 对ISO_MSG变量m进行初始化，最开始必须先调用此函数
 */
void iso8583_init(ISO_MSG *m);

/*
 * 设置ISO_MSG变量m中第idx位的值为data, data长度为len.
 */
int iso8583_set(ISO_MSG *m, int idx, const unsigned char *data, int len);

/*
 * 取得ISO_MSG变量m中第idx位的值到data, 希望最大长度为len.
 */
int iso8583_get(const ISO_MSG *m, int idx, unsigned char *data, int len);

/*
 * 把ISO_MSG变量m中数据按定义好的格式组包到buf中。
 */
int iso8583_pack(const ISO_MSG *m, char *buf);

/*
 * 把buf中数据按定义好的格式解包到ISO_MSG变量m中。
 */
int iso8583_unpack(ISO_MSG *m, const char *buf);

/*
 * 把ISO_MSG变量m中数据按定义好的格式保存到FILE中。
 */
void iso8583_dump(FILE *fp, ISO_MSG *m);

/*
 * 释放ISO_MSG变量m中数据及占用空间,unpack之前也需要free.
 */
void iso8583_free(ISO_MSG *m);

#endif /* iso8583.h */
