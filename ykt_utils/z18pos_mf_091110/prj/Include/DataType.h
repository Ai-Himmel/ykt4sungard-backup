#ifndef	__DATATYPE_H
#define	__DATATYPE_H

//#define _DEBUG

#define TRUE		1
#define FALSE		0
#define ON			1
#define OFF			0	
#define	U8		unsigned char
#define U16		unsigned int
#define U32		unsigned long
#define	S8		char
#define S16		int
#define S32		long
#define INT8U	unsigned char
#define INT16U	unsigned int
#define INT32U	unsigned long
#define INT8UD	unsigned char data
#define INT16UD	unsigned int data
#define INT32UD	unsigned long data
#define INT8UX	unsigned char xdata
#define INT16UX	unsigned int xdata
#define INT8S	char
#define INT16S	int
#define INT32S	long
#define BOOL	bit

#define EXTERN extern
typedef struct{
	INT8U cer;
	INT8U year;
	U8 month;
	U8 day;
	U8 hour;
	U8 min;
	U8 sec;
}TIME_STRUC;

typedef union
{
	INT8U	CharBuff[2];
	INT16U	IntBuff;
}TYPE_CHAR_INT;

typedef union
{
	INT8U	CharBuff[4];
	INT16U	IntBuff[2];
	INT32U	LongBuff;
}TYPE_CHAR_LONG;
typedef struct
{
   	unsigned char	Command[4];
   	unsigned char   Lc;
   	unsigned char	DataIn[512];
   	unsigned char   Le;
}APDU_SEND;

typedef struct
{
	unsigned char	LenOut;
	unsigned char 	DataOut[512];
   	unsigned int	SW;
}APDU_RESP;


#define uint8	unsigned char
#define uint16	unsigned int
#define uint32	unsigned long

#endif

