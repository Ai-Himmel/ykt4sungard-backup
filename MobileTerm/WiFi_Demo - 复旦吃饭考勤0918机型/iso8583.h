/****************************************************************************
*
*文件(File):         iso8583.h
*
*修改(Modify):       2011/8/11 11:43:35
*
*作者(Author):       USER
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
*
*
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011/8/11 11:43:35           USER 
----------------------------------------------------------------------------
****************************************************************************/


 #ifndef   iso8583_h_2011_08_11_14_43_35_INCLUDED
 #define   iso8583_h_2011_08_11_14_43_35_INCLUDED
// #include <stdio.h>
#include "in_call.h"
#ifdef MY_DEBUG
#define MY_TRACE(x,args) fprintf(stderr, x, args)
#else
#define MY_TRACE(x,args)
#endif
#define NUM	999	//字节数
#define BITGET(p,n) ( ( p[n/8]<<(n-(n/8*8)) )&0x80 )       //取bit位

#define ISO8583_VERSION 0		//ISO8583版本信息，不同版本，ISO_DEF变量g_isodef定义就不同,为0时自定义

#define ISO_FLDS 64	//数据域个数，正常标准为128，如有需要可以为64

#define TYP_BIT 0
#define TYP_BCD 1
#define TYP_ASC 2
#define TYP_BIN 3

#define FMT_FIXED 0
#define FMT_LLVAR 2
#define FMT_LLLVAR 3

//8583_ISO定义域结构定义
typedef struct tagISO_DEF {
	short typ;		//数据格式	0--位	1--BCD	2--ASC
	short fmt;		//变长：0--不变  1--1位变长  2--2位变长   3--3位变长
	int   len;			//数据长度（包括变长位）
} ISO_DEF;

//8583_ISO数据域结构定义
typedef struct tagISO_MSG {
	struct tagISO_FLD {
		int len;								//实际长度
		unsigned char buf[NUM];			//数据内容
	} fld[ISO_FLDS+1];
} ISO_MSG;

void iso8583_init(ISO_MSG *m);	// 对ISO_MSG变量m进行初始化，最开始必须先调用此函数

int iso8583_set(ISO_MSG *m, int idx, const unsigned char *data, int len); //设置ISO_MSG变量m中第idx位的值为data, data长度为len.

int iso8583_get(const ISO_MSG *m, int idx, unsigned char *data, int len); //取得ISO_MSG变量m中第idx位的值到data, 希望最大长度为len.

int iso8583_pack(const ISO_MSG *m, char *buf);	//把ISO_MSG变量m中数据按定义好的格式组包到buf中。

int iso8583_unpack(ISO_MSG *m, const char *buf);	//把buf中数据按定义好的格式解包到ISO_MSG变量m中。

void iso8583_dump(FILE *fp, ISO_MSG *m);	// 把ISO_MSG变量m中数据按定义好的格式保存到FILE中。

//void iso8583_free(ISO_MSG *m);		//释放ISO_MSG变量m中数据及占用空间,unpack之前也需要free.

int ASC2BCD (unsigned char *bcd, const char *asc, int len, int fmt);	//asc转bcd

int BCD2ASC (char *asc, const unsigned char *bcd, int len, int fmt);		//bcd转asc

int BCD2INT(int *plen, const unsigned char *bcd, int len, int fmt);	//bcd转int
void hex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int* iDecBUfLen);
void dec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr);	//解压
void atd_pack(char* aBuffer, char* context, int contextLen);
 #endif   /*iso8583_h_2011_08_11_14_43_35_INCLUDED*/
