/****************************************************************************
*
*�ļ�(File):         iso8583.h
*
*�޸�(Modify):       2011/8/11 11:43:35
*
*����(Author):       USER
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
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
#define NUM	999	//�ֽ���
#define BITGET(p,n) ( ( p[n/8]<<(n-(n/8*8)) )&0x80 )       //ȡbitλ

#define ISO8583_VERSION 0		//ISO8583�汾��Ϣ����ͬ�汾��ISO_DEF����g_isodef����Ͳ�ͬ,Ϊ0ʱ�Զ���

#define ISO_FLDS 64	//�����������������׼Ϊ128��������Ҫ����Ϊ64

#define TYP_BIT 0
#define TYP_BCD 1
#define TYP_ASC 2
#define TYP_BIN 3

#define FMT_FIXED 0
#define FMT_LLVAR 2
#define FMT_LLLVAR 3

//8583_ISO������ṹ����
typedef struct tagISO_DEF {
	short typ;		//���ݸ�ʽ	0--λ	1--BCD	2--ASC
	short fmt;		//�䳤��0--����  1--1λ�䳤  2--2λ�䳤   3--3λ�䳤
	int   len;			//���ݳ��ȣ������䳤λ��
} ISO_DEF;

//8583_ISO������ṹ����
typedef struct tagISO_MSG {
	struct tagISO_FLD {
		int len;								//ʵ�ʳ���
		unsigned char buf[NUM];			//��������
	} fld[ISO_FLDS+1];
} ISO_MSG;

void iso8583_init(ISO_MSG *m);	// ��ISO_MSG����m���г�ʼ�����ʼ�����ȵ��ô˺���

int iso8583_set(ISO_MSG *m, int idx, const unsigned char *data, int len); //����ISO_MSG����m�е�idxλ��ֵΪdata, data����Ϊlen.

int iso8583_get(const ISO_MSG *m, int idx, unsigned char *data, int len); //ȡ��ISO_MSG����m�е�idxλ��ֵ��data, ϣ����󳤶�Ϊlen.

int iso8583_pack(const ISO_MSG *m, char *buf);	//��ISO_MSG����m�����ݰ�����õĸ�ʽ�����buf�С�

int iso8583_unpack(ISO_MSG *m, const char *buf);	//��buf�����ݰ�����õĸ�ʽ�����ISO_MSG����m�С�

void iso8583_dump(FILE *fp, ISO_MSG *m);	// ��ISO_MSG����m�����ݰ�����õĸ�ʽ���浽FILE�С�

//void iso8583_free(ISO_MSG *m);		//�ͷ�ISO_MSG����m�����ݼ�ռ�ÿռ�,unpack֮ǰҲ��Ҫfree.

int ASC2BCD (unsigned char *bcd, const char *asc, int len, int fmt);	//ascתbcd

int BCD2ASC (char *asc, const unsigned char *bcd, int len, int fmt);		//bcdתasc

int BCD2INT(int *plen, const unsigned char *bcd, int len, int fmt);	//bcdתint
void hex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int* iDecBUfLen);
void dec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr);	//��ѹ
void atd_pack(char* aBuffer, char* context, int contextLen);
 #endif   /*iso8583_h_2011_08_11_14_43_35_INCLUDED*/
