
#include "stdafx.h"
#include "string.h"
#include	<stdio.h>
#include	<stdlib.h>
#include	<memory.h>
#include	<malloc.h>
#include 	"txntyp.h"
#include "pubfunc.h"
//#include    "key.h"
#include    "typdef.h"
//#include    "mac.h"
//#include    <iconv.h>           /* BOS character set conversion  */
#define  TO_HEX(value)  ((((value)/10)&0x0F)*16 + (((value)%10)&0x0F))
/**************************************************************
  ISO8583 struct  describiton
  ISO8583 define standard iso8583 struct,it include all attribute
  such as data_name
datatyp:0 string;1 int;2 binary
length:it is as same as length_in_byte in most condition,the
different is length's inital value is the most length
of the field.length_in_byte's inital value is 0.
length_in_byte:the filed's real length in byte.
variable_flag:it described whether the filed 's length can be 
changed.value 0 means No changed,2 means this 
fileled has a two bytes length desscribe head.
data:the field's real data
bit_flag:reserved for further use
attribute:reserved for further use
 *****************************************************************/  
typedef struct 
{  
	char msgType[5];        
	char procCode[7];       
	int type;                
	unsigned char bitmap[16];

}TRANS_MAP_TB;


TRANS_MAP_TB trans_tb[TRANS_TYPE]= 
{         
	{"0190","880108",0,
		{0x63,0x38,0x08,0x89,0x00,0xC0,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{"0180","880108",1,
		{0x63,0x38,0x08,0x89,0x00,0xC0,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	/*银行卡查询*/
	{"0240","880108",2,
		{0x63,0x38,0x0A,0x89,0x02,0xC0,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	{"0250","880108",3,
		{0x63,0x38,0x0A,0x89,0x02,0xC0,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}},
	/*银行转账*/
	{"0200","488833",4,
		{0xF3,0x38,0x80,0x81,0x02,0xE1,0x00,0x00,
			0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00}},
	{"0210","488833",5,
		{0xF3,0x38,0x80,0x81,0x02,0xE1,0x00,0x00,
			0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00}},
	/**/
	{"0400","488833",6,
		{0xB3,0x38,0x82,0x81,0x00,0xE1,0x00,0x00,
			0x00,0x00,0x00,0x40,0x02,0x00,0x00,0x00}},
	{"0410","488833",7,
		{0xB3,0x38,0x82,0x81,0x00,0xE1,0x00,0x00,
			0x00,0x00,0x00,0x40,0x02,0x00,0x00,0x00}},
};

typedef struct ISO8583 {
	int  bit_flag;
	char *data_name;
	int  length;
	int  length_in_byte;
	int  variable_flag;
	int  datatyp;
	char *data;
	int  attribute;
} ISO8583;
ISO8583 Tbl8583[128] = {
	/* FLD   1 */ {0,"BIT MAP,EXTENDED                    ",  8, 0, 0, 2, NULL,0},
	/* FLD   2 */ {0,"PRIMARY ACCOUNT NUMBER              ", 22, 0, 2, 0, NULL,0},
	/* FLD   3 */ {0,"PROCESSING CODE                     ",  6, 0, 0, 0, NULL,0},
	/* FLD   4 */ {0,"AMOUNT, TRANSACTION                 ", 12, 0, 0, 1, NULL,0},
	/* FLD   5 */ {0,"NO USE                              ", 12, 0, 0, 0, NULL,0},
	/* FLD   6 */ {0,"NO USE                              ", 12, 0, 0, 0, NULL,0},
	/* FLD   7 */ {0,"TRANSACTION DATE AND TIME           ", 10, 0, 0, 0, NULL,0},
	/* FLD   8 */ {0,"companyid     ",  8, 0, 0, 0, NULL,0},
	/* FLD   9 */ {0,"NO USE                              ",  8, 0, 0, 0, NULL,0},
	/* FLD  10 */ {0,"NO USE                              ",  8, 0, 0, 0, NULL,0},
	/* FLD  11 */ {0,"SYSTEM TRACE AUDIT NUMBER           ",  6, 0, 0, 1, NULL,0},
	/* FLD  12 */ {0,"TIME, LOCAL TRANSACTION             ",  6, 0, 0, 0, NULL,0},
	/* FLD  13 */ {0,"DATE, LOCAL TRANSACTION             ",  4, 0, 0, 0, NULL,0},
	/* FLD  14 */ {0,"DATE, EXPIRATION                    ",  4, 0, 0, 0, NULL,0},
	/* FLD  15 */ {0,"DATE, SETTLEMENT                    ",  4, 0, 0, 0, NULL,0},
	/* FLD  16 */ {0,"NO USE                              ",  4, 0, 0, 0, NULL,0},
	/* FLD  17 */ {0,"DATE, CAPTURE                       ",  4, 0, 0, 0, NULL,0},
	/* FLD  18 */ {0,"MERCHANT'S TYPE                     ",  4, 0, 0, 0, NULL,0},
	/* FLD  19 */ {0,"NO USE                              ",  3, 0, 0, 0, NULL,0},
	/* FLD  20 */ {0,"NO USE                              ",  3, 0, 0, 0, NULL,0},
	/* FLD  21 */ {0,"srvTyp                              ",  3, 0, 0, 0, NULL,0},
	/* FLD  22 */ {0,"POINT OF SERVICE ENTRY MODE         ",  3, 0, 0, 0, NULL,0},
	/* FLD  23 */ {0,"actTyp			    ",  3, 0, 0, 0, NULL,0},
	/* FLD  24 */ {0,"NO USE                              ",  3, 0, 0, 0, NULL,0},
	/* FLD  25 */ {0,"POINT OF SERVICE CONDITION CODE     ",  2, 0, 0, 0, NULL,0},
	/* FLD  26 */ {0,"NO USE                              ",  2, 0, 0, 0, NULL,0},
	/* FLD  27 */ {0,"NO USE                              ",  1, 0, 0, 0, NULL,0},
	/* FLD  28 */ {0,"field27                             ",  6, 0, 0, 0, NULL,0},
	/* FLD  29 */ {0,"pinDat1                       ",  8, 0, 2, 0, NULL,0},
	/* FLD  30 */ {0,"NO USE                              ",  8, 0, 1, 0, NULL,0},
	/* FLD  31 */ {0,"NO USE                              ",  8, 0, 1, 0, NULL,0},
	/* FLD  32 */ {0,"ACQUIRER INSTITUTION ID. CODE       ", 11, 0, 2, 0, NULL,0},
	/* FLD  33 */ {0,"FORWARDING INSTITUTION ID. CODE     ", 11, 0, 2, 0, NULL,0},
	/* FLD  34 */ {0,"NO USE                              ", 28, 0, 2, 0, NULL,0},
	/* FLD  35 */ {0,"TRACK 2 DATA                        ", 37, 0, 2, 0, NULL,0},
	/* FLD  36 */ {0,"TRACK 3 DATA                        ",104, 0, 3, 0, NULL,0},
	/* FLD  37 */ {0,"RETRIEVAL REFERENCE NUMBER          ", 12, 0, 0, 0, NULL,0},
	/* FLD  38 */ {0,"AUTH. IDENTIFICATION RESPONSE       ",  6, 0, 0, 0, NULL,0},
	/* FLD  39 */ {0,"RESPONSE CODE                       ",  2, 0, 0, 0, NULL,0},
	/* FLD  40 */ {0,"NO USE                              ",  3, 0, 0, 0, NULL,0},
	/* FLD  41 */ {0,"CARD ACCEPTOR TERMINAL ID.          ",  8, 0, 0, 0, NULL,0},
	/* FLD  42 */ {0,"CARD ACCEPTOR IDENTIFICATION CODE   ", 15, 0, 0, 0, NULL,0},
	/* FLD  43 */ {0,"CARD ACCEPTOR NAME LOCATION         ", 40, 0, 0, 0, NULL,0},
	/* FLD  44 */ {0,"ADDITIONAL RESPONSE DATA            ", 25, 0, 2, 0, NULL,0},
	/* FLD  45 */ {0,"NO USE                              ", 76, 0, 2, 0, NULL,0},
	/* FLD  46 */ {0,"NO USE                             ",999, 0, 3, 0, NULL,0},
	/* FLD  47 */ {0,"field47                            ",999, 0, 3, 0, NULL,0},
	/* FLD  48 */ {0,"ADDITIONAL DATA --- PRIVATE         ",999, 0, 3, 0, NULL,0},
	/* FLD  49 */ {0,"CURRENCY CODE,TRANSACTION           ",  3, 0, 0, 0, NULL,0},
	/* FLD  50 */ {0,"CURRENCY CODE,SETTLEMENT            ",  3, 0, 0, 0, NULL,0},
	/* FLD  51 */ {0,"NO USE                              ",  3, 0, 0, 0, NULL,0},
	/* FLD  52 */ {0,"PERSONAL IDENTIFICATION NUMBER DATA ",  8, 0, 0, 2, NULL,0},
	/* FLD  53 */ {0,"SECURITY RELATED CONTROL INFORMATION", 16, 0, 0, 0, NULL,0},
	/* FLD  54 */ {0,"ADDITIONAL AMOUNTS                  ",120, 0, 3, 0, NULL,0},
	/* FLD  55 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  56 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  57 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  58 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  59 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  60 */ {0,"NO USE                              ",  5, 0, 3, 0, NULL,0}, 
	/* FLD  61 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  62 */ {0,"NO USE                              ", 11, 0, 3, 0, NULL,0},
	/* FLD  63 */ {0,"NO USE                              ", 11, 0, 3, 0, NULL,0},
	/* FLD  64 */ {0,"MESSAGE AUTHENTICATION CODE FIELD   ",  8, 0, 0, 2, NULL,0},
	/* FLD  65 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  66 */ {0,"NO USE                              ",  1, 0, 0, 0, NULL,0},
	/* FLD  67 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  68 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  69 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  70 */ {0,"SYSTEM MANAGEMENT INFORMATION CODE  ",  3, 0, 0, 0, NULL,0},
	/* FLD  71 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  72 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  73 */ {0,"NO USE                              ",  6, 0, 0, 0, NULL,0},
	/* FLD  74 */ {0,"NUMBER OF CREDITS                   ", 10, 0, 0, 0, NULL,0},
	/* FLD  75 */ {0,"REVERSAL NUMBER OF CREDITS          ", 10, 0, 0, 0, NULL,0},
	/* FLD  76 */ {0,"NUMBER OF DEBITS                    ", 10, 0, 0, 0, NULL,0},
	/* FLD  77 */ {0,"REVERSAL NUMBER OF DEBITS           ", 10, 0, 0, 0, NULL,0},
	/* FLD  78 */ {0,"NUMBER OF TRANSFER                  ", 10, 0, 0, 0, NULL,0},
	/* FLD  79 */ {0,"REVERSAL NUMBER OF TRANSFER         ", 10, 0, 0, 0, NULL,0},
	/* FLD  80 */ {0,"NUMBER OF INQUIRS                   ", 10, 0, 0, 0, NULL,0},
	/* FLD  81 */ {0,"AUTHORIZATION NUMBER                ", 10, 0, 0, 0, NULL,0},
	/* FLD  82 */ {0,"NO USE                              ", 12, 0, 0, 0, NULL,0},
	/* FLD  83 */ {0,"CREDITS,TRANSCATION FEEAMOUNT       ", 12, 0, 0, 0, NULL,0},
	/* FLD  84 */ {0,"NO USE                              ", 12, 0, 0, 0, NULL,0},
	/* FLD  85 */ {0,"DEBITS,TRANSCATION FEEAMOUNT        ", 12, 0, 0, 0, NULL,0},
	/* FLD  86 */ {0,"AMOUNT OF CREDITS                   ", 16, 0, 0, 0, NULL,0},
	/* FLD  87 */ {0,"REVERSAL AMOUNT OF CREDITS          ", 16, 0, 0, 0, NULL,0},
	/* FLD  88 */ {0,"AMOUNT OF DEBITS                    ", 16, 0, 0, 0, NULL,0},
	/* FLD  89 */ {0,"REVERSAL AMOUNT OF DEBITS           ", 16, 0, 0, 0, NULL,0},
	/* FLD  90 */ {0,"ORIGINAL DATA ELEMENTS              ", 42, 0, 0, 0, NULL,0},
	/* FLD  91 */ {0,"FILE UPDATE CODE                    ",  1, 0, 0, 0, NULL,0},
	/* FLD  92 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  93 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  94 */ {0,"SERVICE INDICATOR                   ",  7, 0, 0, 0, NULL,0},
	/* FLD  95 */ {0,"REPLACEMENT AMOUNTS                 ", 42, 0, 0, 0, NULL,0},
	/* FLD  96 */ {0,"NO USE                              ",  8, 0, 0, 0, NULL,0},
	/* FLD  97 */ {0,"AMOUNT OF NET SETTLEMENT            ", 16, 0, 0, 0, NULL,0},
	/* FLD  98 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD  99 */ {0,"SETTLEMENT INSTITUTION ID           ", 11, 0, 2, 0, NULL,0},
	/* FLD 100 */ {0,"RECVEING INSTITUTION ID             ", 11, 0, 2, 0, NULL,0},
	/* FLD 101 */ {0,"FILENAME                            ", 17, 0, 2, 0, NULL,0},
	/* FLD 102 */ {0,"ACCOUNT IDENTIFICATION1             ", 28, 0, 2, 0, NULL,0},
	/* FLD 103 */ {0,"ACCOUNT IDENTIFICATION2             ", 28, 0, 2, 0, NULL,0},
	/* FLD 104 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 105 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 106 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 107 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 108 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 109 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 110 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 111 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 112 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 113 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 114 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 115 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 116 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 117 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 118 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 119 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 120 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 121 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 122 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 123 */ {0,"NEW PIN DATA                        ",  8, 0, 3, 2, NULL,0},
	/* FLD 124 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 125 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 126 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 127 */ {0,"NO USE                              ",999, 0, 3, 0, NULL,0},
	/* FLD 128 */ {0,"MESSAGE AUTHENTICATION CODE FIELD   ",  8, 0, 0, 2, NULL,0},
};

int initstr(char *str)
{
	str[0]='\0';
	return(0);
}

/*****TRANS_MAP_TB is a macro defined in txntyp.h****************/
//TRANS_MAP_TB
/*-------------------------------------------------------------------*
 * Function: Pack message from 'Tbl8583[]' into ISO8583(64/128 bits). *
 * Return: FAIL(-1) -- failure.                                      *
 *         Length -- the length of message, if succeed.              *
 * Parameter:                                                        *
 *     bitMap -- 64/128 bits BITMAP.                                 *
 *     buf -- request or response message. (message type, 64/128     *
 *            BITMAP, & data fields).                                *
 *     msgType -- message type been disposed.                       *
 *     convDirect--coversion code direction(0:no conv,1:a to e
 :*     BM -- 0: 64 bits BITMAP; 128: 128 bits BITMAP.                *
 * Call: memcpy(),translate().                                       *
 *-------------------------------------------------------------------*/

int Pack8583Tb(unsigned char *bitMap,unsigned char *buf,unsigned char *msgType,int convDirect,int BM)
{

	char *trans_tmp;
	char *tmp;
	int i,j,k,t,bit,len;
	int BITMAP_LEN,dataLen;
	if(convDirect<2)
	{
		trans_tmp=(char *)malloc(5);
		translate(convDirect,(char*)msgType,trans_tmp);
		memcpy(buf,trans_tmp,4);
		free(trans_tmp);
		trans_tmp = NULL;
	}
	else
	{
		//memcpy(buf,"8583",4);
		memcpy(buf,msgType,4);
	}
	if (BM)
	{
		memcpy(buf+4,bitMap,16);
		BITMAP_LEN=16;
	}
	else
	{
		memcpy(buf+4,bitMap,8);
		BITMAP_LEN=8;
	}

	tmp=(char *)malloc(MAXMSGSIZE);
	trans_tmp=(char *)malloc(MAXMSGSIZE);

	for (len=(int)(4+BITMAP_LEN),i=0; i<BITMAP_LEN; i++)
		for (bit=0x80,j=0; j<8; bit/=2,j++)
		{
			k=i*8+j;
			if ((!(bitMap[i]&bit)) || ((k==0) && (buf[4]&0x80)))
			{
				free(Tbl8583[k].data);
				Tbl8583[k].data = NULL;
				continue;
			}
			if (t=(int)(Tbl8583[k].variable_flag))
			{
				switch (t)
				{
				case 2:
					sprintf(tmp,"%02d",Tbl8583[k].length);
					break;
				default:
					sprintf(tmp,"%03d",Tbl8583[k].length);
				}
				dataLen=strlen(tmp);
			}
			if (Tbl8583[k].attribute)          
				Tbl8583[k].length_in_byte=(short)((Tbl8583[k].length+1)/2);
			else
				Tbl8583[k].length_in_byte=Tbl8583[k].length;
			memcpy(tmp+Tbl8583[k].variable_flag,Tbl8583[k].data,Tbl8583[k].length_in_byte);
			if(!(Tbl8583[k].datatyp==2)&&(convDirect<2))
				translate(convDirect,tmp,trans_tmp);
			else
				memcpy(trans_tmp,tmp,Tbl8583[k].length_in_byte+Tbl8583[k].variable_flag);
			memcpy(buf+len,trans_tmp,Tbl8583[k].length_in_byte+Tbl8583[k].variable_flag);
			free(Tbl8583[k].data);
			Tbl8583[k].data = NULL;
			len=len+Tbl8583[k].length_in_byte+Tbl8583[k].variable_flag;



		}
	free(tmp);
	tmp = NULL;
	free(trans_tmp);
	trans_tmp = NULL;
	return(len);
}

/**
 *	Fountion:	init the trans_tb with the data in share memory
 *  Return:    -1: failure.
 *              0: ok.
 *  Parameter: 
 *			   transTb :     the table want to init.
 *			   shmidx :      the index of the share memory.
 *			   transTypeNum: the number of trans type
 *			   size:         the size of slot want to get	
 */

int initTransTb(int shmidx,int transTypeNum,int size)
{
	/*
	   char *txndsc;
	   int ret = 0;
	   int i = 0;
	   char typTmp[10];

	   typTmp[0] = 0;
	//txndsc = malloc(sizeof(TBL_TXNDSC));

	txndsc = malloc(sizeof(TBL_TXNDSC));
	for (i = 0; i < transTypeNum;i++) {
	memset(txndsc,0,sizeof(TBL_TXNDSC));
	ret = ReadShmData(shmidx,i,txndsc,size);
	if ( ret < 0 ) {
	free(txndsc);
	txndsc = NULL;
	return -1;
	}
	memcpy(trans_tb[i].msgType,txndsc,4);
	trans_tb[i].msgType[5] = 0;
	memcpy(trans_tb[i].procCode,txndsc+5,6);
	trans_tb[i].procCode[6] = 0;
	memcpy(trans_tb[i].bitmap,txndsc+49,16);
	memcpy(typTmp,txndsc+68,sizeof(int));
	typTmp[sizeof(int)] = 0;
	trans_tb[i].type = *((int *)(typTmp));
	}
	free((char *)txndsc);
	txndsc = NULL;
	return 0;
	*/
	return 0;
}

/*------------------------------------------------------*
 * Function: Generate a request or response message of  *
 *           Telphone Bank format.                      *
 * Return: FAIL(-1) -- failure.                         *
 *         Length -- the length of message, if succeed. *
 * Parameter:                                           *
 *       buf -- a request or response message, (message *
 *              type, 64/128 BITMAP, & data. no TPDU).  *
 *       flag -- REQUEST: request message.              *
 *               RESPONSE: response message.            *
 * Call: Pack8583Tb(), memcpy(), sprintf().            *
 *                                                      *
 * Note: We must set the defined length of the variable *
 *       length field, say Tbl8583[k].length, before ca- *
 *       ll Pack8583Tb().                              *
 *------------------------------------------------------*/

int Pack8583(unsigned char *buf, MSG8583 TransMsg,int convDirect)
	//unsigned char *buf;  /* There isn't TPDU head. */
	//int convDirect;
	//MSG8583 TransMsg;
{
	char msgType[5];  /* transmit 'message type' to 'Pack8583Tb()'. */
	int BM;        /* 0 -- 64 bits BITMAP; 128 -- 128 bits. */
	unsigned char bitMap[16];
	int trans_type,i,j,k,bit;
	//   long t;
	int bitmapLen;
	int lenTmp;
	int isMac ;               /* the mark  have or no mac*/
	int bitData[128];
	//int TRANS_TYPE;		/* max number of trans type*/
	char masKey16[17];
	char masKey8[9];
	char macKey16[17];
	char macKey8[9];            
	char mac[9];
	char pBuf[100];
	int ret = 0;
	int transTbSize = 0;
	//int transTypeSize = 4;

	int pBufSize = 0;

	if ((atoi(TransMsg.mac2)==99)&&(strlen(TransMsg.mac2)==2)){
		isMac = 0;
	}else{
		isMac = 1;
	}


	for(i = 0;i < 16; i++){
		if ((TransMsg.mac1[i]>='a')&&(TransMsg.mac1[i]<='f')) 
			masKey16[i] = TransMsg.mac1[i] + 'A' -'a';
		else{
			masKey16[i] = TransMsg.mac1[i];
		}

		if ((TransMsg.mac2[i]>='a')&&(TransMsg.mac2[i]<='f'))
			macKey16[i] = TransMsg.mac2[i] + 'A' -'a';
		else {
			macKey16[i] = TransMsg.mac2[i];
		}
	}
	macKey16[16] = '\0';
	masKey16[16] = '\0';


	masKey8[0] = 0;
	macKey8[0] = 0;
	mac[0] = 0;
	pBuf[0] = 0;
	lenTmp = 0;


	/* initialize trans_tb[] by the data in share mem */
	//TRANS_TYPE = GetShmSlotNumber(SHM_TXNDSC_IDX);
	if (TRANS_TYPE < 0) {
		puts("error to get transTypeNum from shm");
		return -1;
	}
	//transTypeSize = GetShmSlotSize(SHM_TXNDSC_IDX);
	if (transTypeSize < 0) {
		puts("error to get transTypeSize");
		return -1;
	}
	transTbSize = transTypeSize * TRANS_TYPE;

	/*		trans_tb = malloc(transTbSize);	*/
	memset(trans_tb,0,transTbSize);
	ret = initTransTb(SHM_TXNDSC_IDX,TRANS_TYPE,transTypeSize);
	if (ret < 0) {
		return -1;
	}

	for (i=0;i<128;i++)
		bitData[i]=0;
	for (i=0; i<TRANS_TYPE; i++)
	{
		if ((strcmp(trans_tb[i].msgType,TransMsg.msgType)==0)&&(strcmp(trans_tb[i].procCode,TransMsg.procCode)==0))
			break;
	}
	if (i>=TRANS_TYPE)     
		return(-1);
	trans_type=trans_tb[i].type;
	memcpy(msgType,TransMsg.msgType,4);
	BM=(int)(trans_tb[trans_type].bitmap[0]&0x80);
	//BM=1;
	if (BM)
	{
		bitmapLen=16;
		memcpy(bitMap,trans_tb[trans_type].bitmap,16);
	}
	else
	{
		bitmapLen=8;
		memcpy(bitMap,trans_tb[trans_type].bitmap,8);
	}

	/* free memory of trans_tb ,19981112 Houga */
	/*
	   free(trans_tb);
	   trans_tb = NULL;
	   */

	for (i=0; i<bitmapLen; i++)

		for (bit=0x80,j=0; j<8; bit/=2,j++)
		{
			k=i*8+j;
			if ((!(bitMap[i]&bit)) || ((k==0) && (bitMap[0]&0x80)))
				continue;

			bitData[k]=1;
		}
	if (bitData[1]==1)
	{
		Tbl8583[1].data=(char *)malloc(strlen(TransMsg.priActNum)+1);
		Tbl8583[1].length=strlen(TransMsg.priActNum);
		memcpy(Tbl8583[1].data,TransMsg.priActNum,Tbl8583[1].length);
	}
	if (bitData[2]==1)
	{
		Tbl8583[2].data=(char *)malloc(Tbl8583[2].length+1);
		memcpy(Tbl8583[2].data,TransMsg.procCode,Tbl8583[2].length);
	}
	if (bitData[3]==1)
	{
		Tbl8583[3].data=(char *)malloc(Tbl8583[3].length+1);
		sprintf(Tbl8583[3].data,"%012.0f",TransMsg.txnAmunt*100);
	}

	if (bitData[6]==1)
	{
		Tbl8583[6].data=(char *)malloc(Tbl8583[6].length+1);
		memcpy(Tbl8583[6].data,TransMsg.txnDatTim,Tbl8583[6].length);
	}
	if (bitData[7]==1)
	{
		Tbl8583[7].data=(char *)malloc(Tbl8583[7].length+1);
		memcpy(Tbl8583[7].data,TransMsg.companyid,Tbl8583[7].length);
	}

	if (bitData[10]==1)
	{
		Tbl8583[10].data=(char *)malloc(Tbl8583[10].length+1);
		sprintf(Tbl8583[10].data,"%06lu",TransMsg.tracAudNum);
	}
	if (bitData[11]==1)
	{
		Tbl8583[11].data=(char *)malloc(Tbl8583[11].length+1);
		memcpy(Tbl8583[11].data,TransMsg.txnLocTim,Tbl8583[11].length);
	}
	if (bitData[12]==1)
	{
		Tbl8583[12].data=(char *)malloc(Tbl8583[12].length+1);
		memcpy(Tbl8583[12].data,TransMsg.txnLocDat,Tbl8583[12].length);
	}

	if (bitData[16]==1)
	{
		Tbl8583[16].data=(char *)malloc(Tbl8583[16].length+1);
		memcpy(Tbl8583[16].data,TransMsg.datCap,Tbl8583[16].length);
	}
	if (bitData[17]==1)
	{
		Tbl8583[17].data=(char *)malloc(Tbl8583[17].length+1);
		memcpy(Tbl8583[17].data,TransMsg.ctTxnCod,Tbl8583[17].length);
	}

	if (bitData[18]==1)
	{
		Tbl8583[18].data=(char *)malloc(Tbl8583[18].length+1);
		memcpy(Tbl8583[18].data,TransMsg.teller,Tbl8583[18].length);
	}

	if (bitData[19]==1)
	{
		Tbl8583[19].data=(char *)malloc(Tbl8583[19].length+1);
		memcpy(Tbl8583[19].data,TransMsg.supervisor,Tbl8583[19].length);
	}
	if (bitData[20]==1)
	{
		Tbl8583[20].data=(char *)malloc(Tbl8583[20].length+1);
		memcpy(Tbl8583[20].data,TransMsg.srvTyp,Tbl8583[20].length);
	}
	if (bitData[22]==1)
	{
		Tbl8583[22].data=(char *)malloc(Tbl8583[22].length+1);
		memcpy(Tbl8583[22].data,TransMsg.actTyp,Tbl8583[22].length);
	}

	if (bitData[24]==1)
	{
		Tbl8583[24].data=(char *)malloc(Tbl8583[24].length+1);
		sprintf(Tbl8583[24].data,"%02d",TransMsg.pSrvCdCod);
	}

	if (bitData[27]==1)
	{
		Tbl8583[27].data = (char *)malloc(Tbl8583[27].length+1);
		sprintf(Tbl8583[27].data,"%06lu",TransMsg.bankid);
	}

	if(bitData[28] == 1)
	{
		/*
		Tbl8583[28].data = (char*)malloc(Tbl8583[28].length+1);
		memset(Tbl8583[28].data,0,Tbl8583[28].length);
		strncpy(Tbl8583[28].data,TransMsg.pinDat1,Tbl8583[28].length);
		*/
		Tbl8583[28].data = (char*)malloc(strlen(TransMsg.pinDat1)+1);
		Tbl8583[28].length = strlen(TransMsg.pinDat1);
		memcpy(Tbl8583[28].data,TransMsg.pinDat1,Tbl8583[28].length);
	}
	
	if (bitData[31]==1)
	{
		Tbl8583[31].data=(char *)malloc(strlen(TransMsg.acqInstID)+1);
		Tbl8583[31].length=strlen(TransMsg.acqInstID);
		//Tbl8583[31].data=(char *)malloc(Tbl8583[31].length+1);
		memcpy(Tbl8583[31].data,TransMsg.acqInstID,Tbl8583[31].length);
	}

	if (bitData[32]==1)
	{
		Tbl8583[32].data=(char *)malloc(strlen(TransMsg.forInst)+1);
		Tbl8583[32].length=strlen(TransMsg.forInst);
		memcpy(Tbl8583[32].data,TransMsg.forInst,Tbl8583[32].length);
	}
	if (bitData[38]==1)
	{
		writelog(LOG_DEBUG,"length of field 39 is [%d]",Tbl8583[38].length);
		Tbl8583[38].data=(char *)malloc(Tbl8583[38].length+1);
		memcpy(Tbl8583[38].data,TransMsg.rspCod,Tbl8583[38].length);
	}
	if (bitData[40]==1)
	{

		Tbl8583[40].data=(char *)malloc(Tbl8583[40].length+1);
		memcpy(Tbl8583[40].data,TransMsg.termID,Tbl8583[40].length);
		if ((lenTmp=strlen(TransMsg.termID))!=Tbl8583[40].length)
			memset(Tbl8583[40].data+lenTmp,' ',Tbl8583[40].length-lenTmp);
	}
	if (bitData[41]==1)
	{

		Tbl8583[41].data=(char *)malloc(Tbl8583[41].length+1);
		memcpy(Tbl8583[41].data,TransMsg.idenCod,Tbl8583[41].length);
		if ((lenTmp=strlen(TransMsg.idenCod))!=Tbl8583[41].length)
			memset(Tbl8583[41].data+lenTmp,' ',Tbl8583[41].length-lenTmp);
	}
	if (bitData[42]==1)
	{
		Tbl8583[42].data=(char *)malloc(strlen(TransMsg.agtcus)+1);
		Tbl8583[42].length=strlen(TransMsg.agtcus);
		memcpy(Tbl8583[42].data,TransMsg.agtcus,Tbl8583[42].length);
	}

	if (bitData[43]==1)
	{
		Tbl8583[43].data=(char *)malloc(strlen(TransMsg.addRspDat)+1);
		Tbl8583[43].length=strlen(TransMsg.addRspDat);
		memcpy(Tbl8583[43].data,TransMsg.addRspDat,Tbl8583[43].length);
	}
	if(bitData[46]==1)
	{
		Tbl8583[46].data = (char *)malloc(strlen(TransMsg.field47)+1);
		Tbl8583[46].length = strlen(TransMsg.field47);
		memcpy(Tbl8583[46].data,TransMsg.field47,\
			   Tbl8583[46].length);
	}


	if (bitData[47]==1)
	{
		Tbl8583[47].data=(char *)malloc(86+strlen(TransMsg.prvData.backData)+1);
		Tbl8583[47].length=86+strlen(TransMsg.prvData.backData);
		memcpy(Tbl8583[47].data,TransMsg.prvData.receNum,2);
		if ((lenTmp=strlen(TransMsg.prvData.receNum))<2)
			memset(Tbl8583[47].data+lenTmp,' ',2-lenTmp);

		memcpy(Tbl8583[47].data+2,TransMsg.prvData.checkNum,10);
		if ((lenTmp=strlen(TransMsg.prvData.checkNum))<10)
			memset(Tbl8583[47].data+2+lenTmp,' ',10-lenTmp);


		sprintf(Tbl8583[47].data+12,"%08s",TransMsg.prvData.beginDate);
		if ((lenTmp=strlen(TransMsg.prvData.beginDate))<8)
			memset(Tbl8583[47].data+12+lenTmp,' ',8-lenTmp);

		sprintf(Tbl8583[47].data+20,"%08s",TransMsg.prvData.endDate);
		if ((lenTmp=strlen(TransMsg.prvData.endDate))<8)
			memset(Tbl8583[47].data+20+lenTmp,' ',8-lenTmp);

		sprintf(Tbl8583[47].data+28,"%2s",TransMsg.prvData.despTime);
		if ((lenTmp=strlen(TransMsg.prvData.despTime))<2)
			memset(Tbl8583[47].data+28+lenTmp,' ',2-lenTmp);

		sprintf(Tbl8583[47].data+30,"%2s",TransMsg.prvData.despDollor);
		if ((lenTmp=strlen(TransMsg.prvData.despDollor))<2)
			memset(Tbl8583[47].data+30+lenTmp,' ',2-lenTmp);

		sprintf(Tbl8583[47].data+32,"%2s",TransMsg.prvData.despType);
		if ((lenTmp=strlen(TransMsg.prvData.despType))<2)
			memset(Tbl8583[47].data+32+lenTmp,' ',2-lenTmp);

		sprintf(Tbl8583[47].data+34,"%2s",TransMsg.prvData.accountType);
		if ((lenTmp=strlen(TransMsg.prvData.accountType))<2)
			memset(Tbl8583[47].data+34+lenTmp,' ',2-lenTmp);

		sprintf(Tbl8583[47].data+36,"%8s",TransMsg.prvData.inqueNum);
		if ((lenTmp=strlen(TransMsg.prvData.inqueNum))<8)
			memset(Tbl8583[47].data+36+lenTmp,' ',8-lenTmp);

		sprintf(Tbl8583[47].data+44,"%8s",TransMsg.prvData.exchangeCode);
		if ((lenTmp=strlen(TransMsg.prvData.exchangeCode))<8)
			memset(Tbl8583[47].data+44+lenTmp,' ',8-lenTmp);

		sprintf(Tbl8583[47].data+52,"%2s",TransMsg.prvData.despNum);
		if ((lenTmp=strlen(TransMsg.prvData.despNum))<2)
			memset(Tbl8583[47].data+52+lenTmp,' ',2-lenTmp);

		sprintf(Tbl8583[47].data+54,"%1s",TransMsg.prvData.accountTyp1);
		if ((lenTmp=strlen(TransMsg.prvData.accountTyp1))<1)
			memset(Tbl8583[47].data+54+lenTmp,' ',1-lenTmp);

		sprintf(Tbl8583[47].data+55,"%31s",TransMsg.prvData.Reserved);
		if ((lenTmp=strlen(TransMsg.prvData.Reserved))<31)
			memset(Tbl8583[47].data+55+lenTmp,' ',31-lenTmp);

		memcpy(Tbl8583[47].data+86,TransMsg.prvData.backData,strlen(TransMsg.prvData.backData));




	} 
	if (bitData[48]==1)
	{
		Tbl8583[48].data=(char *)malloc(Tbl8583[48].length+1);
		memcpy(Tbl8583[48].data,TransMsg.txnCuuCod,Tbl8583[48].length);
	}
	if (bitData[51]==1)
	{
		Tbl8583[51].data=(char *)malloc(Tbl8583[51].length+1);
		sprintf(Tbl8583[51].data,"%08lx",TransMsg.pinDat);
	}
	if (bitData[53]==1)
	{
		Tbl8583[53].data=(char *)malloc(Tbl8583[53].length+1);
		sprintf(Tbl8583[53].data,"%.0f",TransMsg.addAmunt);
		Tbl8583[53].length=strlen(Tbl8583[53].data);
	}
	if (bitData[69]==1)
	{
		Tbl8583[69].data=(char *)malloc(Tbl8583[69].length+1);
		memcpy(Tbl8583[69].data,TransMsg.netMngInfo,Tbl8583[69].length);
	}
	if (bitData[89]==1)
	{
		Tbl8583[89].data = (char *)malloc(Tbl8583[89].length+1);
		memcpy(Tbl8583[89].data,TransMsg.OrgDatElm.msgType,4);
		sprintf(Tbl8583[89].data+4,"%06lu",TransMsg.OrgDatElm.tracNum);
		if (strlen(TransMsg.OrgDatElm.txnDatTim) < 10)
			return (-1);
		memcpy(Tbl8583[89].data+10,TransMsg.OrgDatElm.txnDatTim,10);
		lenTmp = strlen(TransMsg.OrgDatElm.acqInstID);
		if (lenTmp > 11){
			return (-1);
		}
		if (lenTmp < 11){
			memset(Tbl8583[89].data+20,'0',11-lenTmp);
		}
		memcpy(Tbl8583[89].data+20+11-lenTmp,\
			   TransMsg.OrgDatElm.acqInstID,lenTmp);
		lenTmp = strlen(TransMsg.OrgDatElm.forInst);
		if (lenTmp > 11){
			return (-1); 
		}
		if (lenTmp < 11){ 
			memset(Tbl8583[89].data+31,'0',11-lenTmp);
		}
		memcpy(Tbl8583[89].data+31+11-lenTmp,\
			   TransMsg.OrgDatElm.forInst,lenTmp);		
	}

	if (bitData[99]==1)
	{  
		Tbl8583[99].data=(char *)malloc(strlen(TransMsg.recvIntID)+1);
		Tbl8583[99].length=strlen(TransMsg.recvIntID);
		memcpy(Tbl8583[99].data,TransMsg.recvIntID,Tbl8583[99].length);
	}
	if (bitData[101]==1)
	{  
		Tbl8583[101].data=(char *)malloc(strlen(TransMsg.chkAct)+1);
		Tbl8583[101].length=strlen(TransMsg.chkAct);
		memcpy(Tbl8583[101].data,TransMsg.chkAct,Tbl8583[101].length);
	}
	if (bitData[102]==1)
	{  
		Tbl8583[102].data=(char *)malloc(strlen(TransMsg.addAcNo103)+1);
		Tbl8583[102].length=strlen(TransMsg.addAcNo103);
		memcpy(Tbl8583[102].data,TransMsg.addAcNo103,Tbl8583[102].length);
	}

	if (bitData[127] == 1) {    /* FIELD127 if */
		Tbl8583[127].data=(char *)malloc(9);
		memset(Tbl8583[127].data,0,9);

		switch (atoi(TransMsg.msgType)) {

		case 810:
			if (strcmp(TransMsg.netMngInfo,"001") != 0)
				break;
			if (isMac == 0)
				break;
#ifdef DEBUG
			printf("\n\nmacKey input :=%s\n",macKey16);
#endif
			//	DSP_2_HEX(masKey16,masKey8,8);
			//	DSP_2_HEX(macKey16,macKey8,8); 
			memset(mac,0,8);
			//	/* DES(macKey8,mac,masKey8,'E');*/
			//	DES(0,masKey8,macKey8,mac,8);
			memcpy(Tbl8583[127].data,mac,8);

			break;

		case 800:
			break;

		default:
			if (isMac == 0)
				break;
			if (strlen(TransMsg.chkAct) < 8)
				return -1;
			sprintf(pBuf,"%016s",TransMsg.chkAct+8);
			pBufSize += 16;

			sprintf(pBuf+pBufSize,"%022s",TransMsg.priActNum);
			pBufSize += 22; 

			sprintf(pBuf+pBufSize,"%014.0f",TransMsg.txnAmunt);
			pBufSize += 14;                    /* 04 */

			lenTmp = strlen(TransMsg.msgType);
			if (lenTmp != 4)
				return -1;
			memcpy(pBuf+pBufSize,TransMsg.msgType,4);
			pBufSize += 4;

			lenTmp = strlen(TransMsg.procCode);
			if (lenTmp != 6)
				return -1;
			memcpy(pBuf+pBufSize,TransMsg.procCode,6);
			pBufSize += Tbl8583[2].length;

			lenTmp = strlen(TransMsg.rspCod);
			if (lenTmp != 2){
				memset(pBuf+pBufSize,0,2);
			}else{
				memcpy(pBuf+pBufSize,TransMsg.rspCod,2);
			}
			pBufSize += 2;

			//	DSP_2_HEX(macKey16,macKey8,8);
			memset(mac,0,8);
#ifdef DEBUG
			printf("\n\nmacKey input in pack:=%s\n",macKey16);
			for (i=0;i<64;i++)
				printf("[%02x]",pBuf[i]);
#endif

			/*		MAC(pBuf,pBufSize,mac,macKey8,STAND);*/
			if ( pBufSize % 8  != 0)
				pBufSize = (pBufSize/8 + 1) * 8;
			//	GenerateMAC(MAC_STAND,pBuf,pBufSize,macKey8,mac);

#ifdef DEBUG
			printf("\n\nthe macKey send to sec\n");
			for(i=0;i<8;i++)
				printf("[%02x]",mac[i]);
#endif

			memcpy(Tbl8583[127].data,mac,8);
			break;
		}    /* end of case*/
	}		 /* end of FIELD 127 */

	return(Pack8583Tb(bitMap,buf,(unsigned char*)msgType,convDirect,BM));
}

/*---------------------------------------------------------------*
 * Function: Unpack message into Tbl8583[], using ISO8583 format. *
 * Return: OK(0) -- success.                                     *
 *         FAIL(-1) -- failure.                                  *
 * Parameter:                                                    *
 *      buf -- request or response message (message type, 64/128 *
 *             BITMAP, data fields).                             *
 *      BM -- 0: 64 bits BITMAP; 128: 128 bits BITMAP.           *
 *---------------------------------------------------------------*/

int unpack8583_tb(unsigned char *buf,MSG8583 *TransMsg,char *bitMap,int convDirect,int *BM)
{

	unsigned char *data;
	int BITMAP_LEN;
	int datalength;
	int i,j,k,t,bit,dataLen;
	char *tmp,*trans_tmp;
	char inbuf[5],outbuf[5];
	char *len1,*len2,*len3,*len4;
	inbuf[4]=outbuf[4]=0;
	if(convDirect<2)
	{
		memcpy(inbuf,buf,4);
		translate(convDirect,inbuf,outbuf);
		memcpy(TransMsg->msgType,outbuf,5);//get message type ID
	}
	else
		memcpy(TransMsg->msgType,buf,4);//get message type ID
	memcpy(bitMap,buf+4,16);
	*BM=(int)(bitMap[0]&0x80);
	//*BM=1;
	if (*BM==0) 
	{
		BITMAP_LEN=8;             // 64 bits
		datalength=4+8;
	}

	else           	
	{
		BITMAP_LEN=16;            //128 bits 
		datalength=4+16;
	}

	trans_tmp=(char *)malloc(MAXMSGSIZE);
	len1=(char *)malloc(3);
	len2=(char *)malloc(3);
	len3=(char *)malloc(4);
	len4=(char *)malloc(4);
	tmp=(char *)malloc(MAXMSGSIZE);
	//Skip 'message type', 'bitMap'.
	for (data=(buf+4+BITMAP_LEN),i=0; i<BITMAP_LEN; i++)
		for (bit=0x80,j=0; j<8; j++,bit/=2)
		{
			k=i*8+j;	                  // field position
			//Judge BITMAP position is existing or not;
			//      * and dispose 64/128 BITMAP -- Tbl8583[0].

			if ((!(buf[4+i]&bit)) || ((k==0) && (buf[4]&0x80)))
				continue;
			if (t=(int)(Tbl8583[k].variable_flag))
			{
				switch (t)
				{
				case 2:
					for(dataLen=0;dataLen<2;dataLen++)                 
						len1[dataLen]=data[dataLen];
					if ((Tbl8583[k].datatyp==2)||(convDirect==2))
					{
						dataLen=atoi(len1); }
					else
					{
						translate(convDirect,len1,len2);
						dataLen=atoi(len2);
					}
					break;
				default:
					for(dataLen=0;dataLen<3;dataLen++)
						len3[dataLen]=data[dataLen];
					if ((Tbl8583[k].datatyp==2)||(convDirect==2))
						dataLen=atoi(len3);
					else
					{ 
						translate(convDirect,len3,len4);
						dataLen=atoi(len4);
					}
					break;

				}
				Tbl8583[k].length=dataLen;
			}
			if (Tbl8583[k].attribute)  //BCD, 2 data each byte 
				Tbl8583[k].length_in_byte=(short)((Tbl8583[k].length+1)/2);
			else
				Tbl8583[k].length_in_byte=Tbl8583[k].length;
			Tbl8583[k].data=(char*)calloc(Tbl8583[k].length_in_byte+1,sizeof(char)) ;
			memcpy(tmp,data+Tbl8583[k].variable_flag,Tbl8583[k].length_in_byte);

			if(!(Tbl8583[k].datatyp==2)&&(!(convDirect==2)))
			{
				translate(convDirect,tmp,trans_tmp);
				memcpy(Tbl8583[k].data,trans_tmp,Tbl8583[k].length_in_byte);

			}
			else
				memcpy(Tbl8583[k].data,tmp,Tbl8583[k].length_in_byte);



			datalength+=Tbl8583[k].length_in_byte+Tbl8583[k].variable_flag;
			data+=Tbl8583[k].length_in_byte+Tbl8583[k].variable_flag;
		}
	free(len1);
	len1 = NULL;
	free(len2);
	len2 = NULL;
	free(len3);
	len3 = NULL;
	free(len4);
	len4 = NULL;
	free(tmp);
	tmp = NULL;
	free(trans_tmp);
	trans_tmp = NULL;
	return(datalength);
}

/************************************************************************/
/*   ASCII to EBCDIC and EBCDIC to ASCII translation                    */
/************************************************************************/
int  translate(int direction,char *inbuf,char *outbuf)
{
	/*
	   char *ip, *op;
	   size_t InBytesLeft, OutBytesLeft;
	   iconv_t cd;
	   int r;
	   if(direction==2)
	   {
	   strcpy(outbuf,inbuf);
	   return(0);
	   }
	   if (direction == A2E) {            
	   cd = iconv_open(ASCII, EBCDIC); 
	   }
	   else {                             
	   cd = iconv_open(EBCDIC, ASCII); 
	   }

	   InBytesLeft = strlen(inbuf);
	   OutBytesLeft = InBytesLeft;
	   memset(outbuf, 0, strlen(inbuf));
	   ip = inbuf;
	   op = outbuf;
	   r = iconv(cd, (char **) &ip, &InBytesLeft,&op, &OutBytesLeft); 
	   iconv_close(cd);  
	   return(r);
	   */
	return 0;
}
/*------------------------------------------------------*
 * Function: Generate a request or response message of  *
 *           JingKa format.                             *
 * Return: FAIL(-1) -- failure.                         *
 *         Length -- the length of message, if succeed. *
 * Parameter:                                           *
 *       buf -- a request or response message, (message *
 *              type, 64/128 BITMAP, & data. no TPDU).  *
 *       flag -- REQUEST: request message.              *
 *               RESPONSE: response message.            *
 * Call: Pack8583Tb(), memcpy(), sprintf().            *
 *                                                      *
 * Note: We must set the defined length of the variable *
 *       length field, say Tbl8583[k].length, before ca- *
 *       ll Pack8583Tb().                              *
 *------------------------------------------------------*/
int UnPack8583(unsigned char *buf,MSG8583 *TransMsg,int convDirect)
{
	char bitmap[16];
	//char *msgType;  /* transmit 'message type' to 'Pack8583Tb()'. */
	int BM;        /* 0 -- 64 bits BITMAP; 128 -- 128 bits. */
	int i,j,k,bit;
	char *tmp;
	int lenTmp;
	int datalength;
	int BITMAP_LEN;
	int bitData[128];
	int isMac;
	char masKey16[17];
	char masKey8[9];
	char macKey16[17];
	char macKey8[9];
	char mac[9];
	char pBuf[100];
	char pBufSize = 0;


	if ((atoi(TransMsg->mac2)==99)&&(strlen(TransMsg->mac2)==2)){
		isMac = 0;
	}else{
		isMac = 1;
	}

	for(i = 0;i < 16; i++){
		if ((TransMsg->mac1[i]>='a')&&(TransMsg->mac1[i]<='f')) 
			masKey16[i] = TransMsg->mac1[i] + 'A' -'a';
		else{
			masKey16[i] = TransMsg->mac1[i];
		}

		if ((TransMsg->mac2[i]>='a')&&(TransMsg->mac2[i]<='f'))
			macKey16[i] = TransMsg->mac2[i] + 'A' -'a';
		else {
			macKey16[i] = TransMsg->mac2[i];
		}
	}

	masKey8[0] = 0;
	macKey8[0] = 0;
	mac[0] = 0;
	pBuf[0] = 0;

	for(i=0;i<128;i++)
		bitData[i]=0;
	datalength=unpack8583_tb(buf,TransMsg,bitmap,convDirect,&BM);
	if(datalength<0)
		return(-1);
	//BM=1;
	if (BM==0) 
		BITMAP_LEN=8;             /* 64 bits */
	else           	
		BITMAP_LEN=16;            /* 128 bits */


	for (i=0; i<BITMAP_LEN; i++)
		for (bit=0x80,j=0; j<8; bit/=2,j++)
		{           
			k=i*8+j;
			if ((!(bitmap[i]&bit)) || ((k==0) && (bitmap[0]&0x80)))
				continue;
			bitData[k]=1;
		}
	if (bitData[1]==1)
	{
		memcpy(TransMsg->priActNum,Tbl8583[1].data,Tbl8583[1].length);
		memcpy(TransMsg->priActNum+Tbl8583[1].length,"\0",1);
		free(Tbl8583[1].data);
		Tbl8583[1].data = NULL;
	}
	if (bitData[2]==1)
	{
		memcpy(TransMsg->procCode,Tbl8583[2].data,Tbl8583[2].length);
		memcpy(TransMsg->procCode+Tbl8583[2].length,"\0",1);
		free(Tbl8583[2].data);
		Tbl8583[2].data = NULL;
	}
	if (bitData[3]==1)
	{
		tmp=(char*)malloc(Tbl8583[3].length+1);
		memcpy(tmp,Tbl8583[3].data,Tbl8583[3].length);
		memcpy(tmp+Tbl8583[3].length,"\0",1);
		TransMsg->txnAmunt=atof(tmp)/100.00;
		free(tmp);
		tmp = NULL;
		free(Tbl8583[3].data);
		Tbl8583[3].data = NULL;
	}
	if (bitData[6]==1)
	{
		memcpy(TransMsg->txnDatTim,Tbl8583[6].data,Tbl8583[6].length);
		memcpy(TransMsg->txnDatTim+Tbl8583[6].length,"\0",1);
		free(Tbl8583[6].data);
		Tbl8583[6].data = NULL;
	}
	if (bitData[7]==1)
	{
		memcpy(TransMsg->companyid,Tbl8583[7].data,Tbl8583[7].length);
		memcpy(TransMsg->companyid+Tbl8583[7].length,"\0",1);
		free(Tbl8583[7].data);
		Tbl8583[7].data = NULL;
	}

	if (bitData[10]==1)
	{
		tmp=(char*)malloc(Tbl8583[10].length+1);
		memcpy(tmp,Tbl8583[10].data,Tbl8583[10].length);
		memcpy(tmp+Tbl8583[10].length,"\0",1);
		TransMsg->tracAudNum=strtoul(tmp,NULL,10);
		free(tmp);
		tmp = NULL;
		free(Tbl8583[10].data);
		Tbl8583[10].data = NULL;
	}
	if (bitData[11]==1)
	{
		memcpy(TransMsg->txnLocTim,Tbl8583[11].data,Tbl8583[11].length);
		memcpy(TransMsg->txnLocTim+Tbl8583[11].length,"\0",1);
		free(Tbl8583[11].data);
		Tbl8583[11].data = NULL;
	}
	if (bitData[12]==1)
	{
		memcpy(TransMsg->txnLocDat,Tbl8583[12].data,Tbl8583[12].length);
		memcpy(TransMsg->txnLocDat+Tbl8583[12].length,"\0",1);
		free(Tbl8583[12].data);
		Tbl8583[12].data = NULL;
	}

	if (bitData[16]==1)
	{
		memcpy(TransMsg->datCap,Tbl8583[16].data,Tbl8583[16].length);
		memcpy(TransMsg->datCap+Tbl8583[16].length,"\0",1);
		free(Tbl8583[16].data);
		Tbl8583[16].data = NULL;
	}
	if (bitData[17]==1)
	{
		memcpy(TransMsg->ctTxnCod,Tbl8583[17].data,Tbl8583[17].length);
		memcpy(TransMsg->ctTxnCod+Tbl8583[17].length,"\0",1);
		free(Tbl8583[17].data);
		Tbl8583[17].data = NULL;
	}

	if (bitData[18]==1)
	{
		memcpy(TransMsg->teller,Tbl8583[18].data,Tbl8583[18].length);
		memcpy(TransMsg->teller+Tbl8583[18].length,"\0",1);
		free(Tbl8583[18].data);
		Tbl8583[18].data = NULL;
	}

	if (bitData[19]==1)
	{
		memcpy(TransMsg->supervisor,Tbl8583[19].data,Tbl8583[19].length);
		memcpy(TransMsg->supervisor+Tbl8583[19].length,"\0",1);
		free(Tbl8583[19].data);
		Tbl8583[19].data = NULL;
	}

	if (bitData[20]==1)
	{
		memcpy(TransMsg->srvTyp,Tbl8583[20].data,Tbl8583[20].length);
		memcpy(TransMsg->srvTyp+Tbl8583[20].length,"\0",1);
		free(Tbl8583[20].data);
		Tbl8583[20].data = NULL;
	}

	if (bitData[22]==1)
	{
		memcpy(TransMsg->actTyp,Tbl8583[22].data,Tbl8583[22].length);
		memcpy(TransMsg->actTyp+Tbl8583[22].length,"\0",1);
		free(Tbl8583[22].data);
		Tbl8583[22].data = NULL;
	}

	if (bitData[24]==1)
	{
		tmp=(char*)malloc(Tbl8583[24].length+1);
		memcpy(tmp,Tbl8583[24].data,Tbl8583[24].length);
		memcpy(tmp+Tbl8583[24].length,"\0",1);
		TransMsg->pSrvCdCod=atoi(tmp);
		free(tmp);
		tmp = NULL;
		free(Tbl8583[24].data);
		Tbl8583[24].data = NULL;
	}
	if (bitData[27] == 1)
	{
		tmp=(char*)malloc(Tbl8583[27].length+1);
		memcpy(tmp,Tbl8583[27].data,Tbl8583[27].length);
		memcpy(tmp+Tbl8583[27].length,"\0",1);
		TransMsg->bankid=strtoul(tmp,NULL,10);
		free(tmp);
		tmp = NULL;
		free(Tbl8583[27].data);
		Tbl8583[27].data = NULL;
	}

	if(bitData[28] == 1)
	{
		memcpy(TransMsg->pinDat1,Tbl8583[28].data,Tbl8583[28].length);
		memcpy(TransMsg->pinDat1+Tbl8583[28].length,"\0",1);
		free(Tbl8583[28].data);
		Tbl8583[28].data = NULL;
	}
	if (bitData[31]==1)
	{
		memcpy(TransMsg->acqInstID,Tbl8583[31].data,Tbl8583[31].length);
		memcpy(TransMsg->acqInstID+Tbl8583[31].length,"\0",1);
		free(Tbl8583[31].data);
		Tbl8583[31].data = NULL;
	}

	if (bitData[32]==1)
	{
		memcpy(TransMsg->forInst,Tbl8583[32].data,Tbl8583[32].length);
		memcpy(TransMsg->forInst+Tbl8583[32].length,"\0",1);
		free(Tbl8583[32].data);
		Tbl8583[32].data = NULL;
	}
	if (bitData[38]==1)
	{
		memcpy(TransMsg->rspCod,Tbl8583[38].data,Tbl8583[38].length);
		memcpy(TransMsg->rspCod+Tbl8583[38].length,"\0",1);
		free(Tbl8583[38].data);
		Tbl8583[38].data = NULL;
	}
	if (bitData[40]==1)
	{
		memcpy(TransMsg->termID,Tbl8583[40].data,Tbl8583[40].length);
		memcpy(TransMsg->termID+Tbl8583[40].length,"\0",1);
		free(Tbl8583[40].data);
		Tbl8583[40].data = NULL;
	}

	if (bitData[41]==1)
	{
		memcpy(TransMsg->idenCod,Tbl8583[41].data,Tbl8583[41].length);
		memcpy(TransMsg->idenCod+Tbl8583[41].length,"\0",1);
		free(Tbl8583[41].data);
		Tbl8583[41].data = NULL;
	}

	if (bitData[43]==1)
	{
		memcpy(TransMsg->addRspDat,Tbl8583[43].data,Tbl8583[43].length);
		memcpy(TransMsg->addRspDat+Tbl8583[43].length,"\0",1);
		free(Tbl8583[43].data);
		Tbl8583[43].data = NULL;
	}

	if (bitData[46]==1)
	{
		memcpy(TransMsg->field47,Tbl8583[46].data,\
			   Tbl8583[46].length);
		memcpy(TransMsg->field47+Tbl8583[46].length,"\0",1);
		free(Tbl8583[46].data);
		Tbl8583[46].data = NULL;
	}

	if (bitData[47]==1)
	{
		/*
		   memcpy(TransMsg->prvData.Reserved+10,"\0",1);
		   free(Tbl8583[47].data);
		   */
		memcpy(TransMsg->prvData.receNum,Tbl8583[47].data,2);
		memcpy(TransMsg->prvData.receNum+2,"\0",1);
		memcpy(TransMsg->prvData.checkNum,Tbl8583[47].data+2,10);
		memcpy(TransMsg->prvData.checkNum+10,"\0",1);
		memcpy(TransMsg->prvData.beginDate,Tbl8583[47].data+12,8);
		memcpy(TransMsg->prvData.beginDate+8,"\0",1);
		memcpy(TransMsg->prvData.endDate,Tbl8583[47].data+20,8);
		memcpy(TransMsg->prvData.endDate+8,"\0",1);
		memcpy(TransMsg->prvData.despTime,Tbl8583[47].data+28,2);
		memcpy(TransMsg->prvData.despTime+2,"\0",1);
		memcpy(TransMsg->prvData.despDollor,Tbl8583[47].data+30,2);
		memcpy(TransMsg->prvData.despDollor+2,"\0",1);
		memcpy(TransMsg->prvData.despType,Tbl8583[47].data+32,2);
		memcpy(TransMsg->prvData.despType+2,"\0",1);
		memcpy(TransMsg->prvData.accountType,Tbl8583[47].data+34,2);
		memcpy(TransMsg->prvData.accountType+2,"\0",1);
		memcpy(TransMsg->prvData.inqueNum,Tbl8583[47].data+36,8);
		memcpy(TransMsg->prvData.inqueNum+8,"\0",1);
		memcpy(TransMsg->prvData.exchangeCode,Tbl8583[47].data+44,8);
		memcpy(TransMsg->prvData.exchangeCode+8,"\0",1);
		memcpy(TransMsg->prvData.despNum,Tbl8583[47].data+52,2);
		memcpy(TransMsg->prvData.despNum+2,"\0",1);
		memcpy(TransMsg->prvData.accountTyp1,Tbl8583[47].data+54,1);
		memcpy(TransMsg->prvData.accountTyp1 +1,"\0",1);
		memcpy(TransMsg->prvData.Reserved,Tbl8583[47].data+55,31);
		memcpy(TransMsg->prvData.Reserved+31,"\0",1);

		if ((Tbl8583[47].length-86)>0)
			memcpy(TransMsg->prvData.backData,Tbl8583[47].data+86,\
				   Tbl8583[47].length-86);
		/* the length of 48 field */
		memcpy(TransMsg->prvData.backData+Tbl8583[47].length-86,"\0",1);

		free(Tbl8583[47].data);
		Tbl8583[47].data = NULL;

	}

	if (bitData[48]==1)
	{
		memcpy(TransMsg->txnCuuCod,Tbl8583[48].data,Tbl8583[48].length);
		memcpy(TransMsg->txnCuuCod+Tbl8583[48].length,"\0",1);
		free(Tbl8583[48].data);
		Tbl8583[48].data = NULL;
	}
	if (bitData[51]==1)
	{
		tmp=(char*)malloc(Tbl8583[51].length+1);
		memcpy(tmp,Tbl8583[51].data,Tbl8583[51].length);
		memcpy(tmp+Tbl8583[51].length,"\0",1);
		TransMsg->pinDat=strtoul(tmp,NULL,16);
		free(tmp);
		tmp = NULL;
		free(Tbl8583[51].data);
		Tbl8583[51].data = NULL;
	}
	if (bitData[53]==1)
	{
		tmp=(char*)malloc(Tbl8583[53].length+1);
		memcpy(tmp,Tbl8583[53].data,Tbl8583[53].length);
		memcpy(tmp+Tbl8583[53].length,"\0",1);
		TransMsg->addAmunt=atof(tmp);
		free(tmp);
		tmp = NULL;
		free(Tbl8583[53].data);
		Tbl8583[53].data = NULL;
	}
	if (bitData[69]==1)
	{
		memcpy(TransMsg->netMngInfo,Tbl8583[69].data,Tbl8583[69].length);
		memcpy(TransMsg->netMngInfo+Tbl8583[69].length,"\0",1);
		free(Tbl8583[69].data);
		Tbl8583[69].data = NULL;
	}

	if (bitData[89]==1)
	{
		/* these line for old 90 field unpacked 
		   TransMsg->OrgDatElm.tracNum=strtoul(tmp,NULL,10);  
		   free(tmp);
		   free(Tbl8583[89].data);
		   */

		memcpy(TransMsg->OrgDatElm.msgType,Tbl8583[89].data,4);
		memcpy(TransMsg->OrgDatElm.msgType+4,"\0",1);
		tmp = (char*)malloc(7);
		memcpy(tmp,Tbl8583[89].data+4,6);
		memcpy(tmp+6,"\0",1);
		TransMsg->OrgDatElm.tracNum=strtoul(tmp,NULL,10);
		free(tmp);
		tmp = NULL;
		memcpy(TransMsg->OrgDatElm.txnDatTim,Tbl8583[89].data+10,10);
		memcpy(TransMsg->OrgDatElm.txnDatTim+10,"\0",1);
		tmp = (char *)malloc(12);
		memcpy(tmp,Tbl8583[89].data+20,11);
		memcpy(tmp+11,"\0",1);
		{
			i = 0;
			while (tmp[i] == '0') i++;
			strcpy(TransMsg->OrgDatElm.acqInstID,tmp+i);
		}		
		free(tmp);
		tmp = NULL;

		tmp = (char *)malloc(12);
		memcpy(tmp,Tbl8583[89].data+31,11);
		memcpy(tmp+11,"\0",1);
		{
			i = 0;
			while (tmp[i] == '0') i++;
			strcpy(TransMsg->OrgDatElm.forInst,tmp+i);
		}	
		free(tmp);	
		tmp = NULL;
		free(Tbl8583[89].data);	
		Tbl8583[89].data = NULL;

	}

	if (bitData[99]==1)
	{  
		memcpy(TransMsg->recvIntID,Tbl8583[99].data,Tbl8583[99].length);
		TransMsg->recvIntID[Tbl8583[99].length]='\0';
		free(Tbl8583[99].data);
		Tbl8583[99].data = NULL;
	}
	if (bitData[101]==1)
	{  
		memcpy(TransMsg->chkAct,Tbl8583[101].data,Tbl8583[101].length);
		TransMsg->chkAct[Tbl8583[101].length]='\0';
		free(Tbl8583[101].data);
		Tbl8583[101].data = NULL;
	}

	if (bitData[127] == 1){
		memcpy(TransMsg->mac,Tbl8583[127].data,8);

		switch (atoi(TransMsg->msgType)) {

		case 800:
			memset(mac,0,8);				

			break;

		case 810:
			/*
			   if (isMac == 0)
			   break;
			   DSP_2_HEX(masKey16,masKey8,8);
			   memset(mac,0,8);
			   DES(TransMsg->mac,mac,masKey8,'D');
			   HEX_2_DSP(mac,macKey16,8);
			   */

			break;

		default:

#ifdef DEBUG
			printf("\n in unpack\n\n");
			printf("macKey in unpack =%s\n", macKey16);
#endif
			if (isMac == 0)
				break;
			if (strlen(TransMsg->chkAct)<8)
				return -1;
			sprintf(pBuf,"%016s",TransMsg->chkAct+8);
			pBufSize += 16;

			sprintf(pBuf+pBufSize,"%022s",TransMsg->priActNum);
			pBufSize += 22; 

			sprintf(pBuf+pBufSize,"%014.0f",TransMsg->txnAmunt);
			pBufSize += 14;                    /* 04 */

			lenTmp = strlen(TransMsg->msgType);
			if (lenTmp != 4)
				return -1;
			memcpy(pBuf+pBufSize,TransMsg->msgType,4);
			pBufSize += 4;

			lenTmp = strlen(TransMsg->procCode);
			if (lenTmp != 6)
				return -1;
			memcpy(pBuf+pBufSize,TransMsg->procCode,6);
			pBufSize += 6;

			lenTmp = strlen(TransMsg->rspCod);
			if (lenTmp != 2){
				memset(pBuf+pBufSize,0,2);
			}else{
				memcpy(pBuf+pBufSize,TransMsg->rspCod,2);
			}
			pBufSize += 2;
			if (pBufSize % 8 != 0)
				pBufSize = (pBufSize/8 + 1) * 8;

			//DSP_2_HEX(macKey16,macKey8,8);
			memset(mac,0,8);
			//GenerateMAC(MAC_STAND,pBuf,pBufSize,macKey8,mac);
			/*	MAC(pBuf,pBufSize,mac,macKey8,STAND);*/
#ifdef DEBUG
			pBuf[64] = '\0';
			for (i=0;i<64;i++)
				printf("[%02x]",pBuf[i]);

			printf("\n\n the mac creat");
			for (i=0;i<8;i++)
				printf("[%02x]",mac[i]);
			printf("\n\n the mac recv");
			for (i=0;i<8;i++)
				printf("[%02x]",TransMsg->mac[i]);
#endif

			if (memcmp(mac,TransMsg->mac,8) == 0){
			}else{
				free(Tbl8583[127].data);
				Tbl8583[127].data = NULL;
				return (-55);
			}

			break;
		}    			/* end of case*/
		free(Tbl8583[127].data);
		Tbl8583[127].data = NULL;
	}

	return(datalength);
}

int init8583(MSG8583 *msg)
{
	initstr(msg->msgType);
	msg->bitMapExt=(unsigned long)0 ;  /*bitmap extend*/
	initstr(msg->priActNum);     /*priamary account*/
	initstr(msg->procCode);
	msg->txnAmunt=(double)0; 
	initstr(msg->txnDatTim);   /*6*/
	msg->tracAudNum=(unsigned long)0 ;  /*10*/
	initstr(msg->txnLocTim);   /*11*/
	initstr(msg->txnLocDat);   /*12*/
	initstr(msg->datCap);      /* 16  */
	msg->pSrvCdCod=0;   /* 24  */
	msg->bankid=(unsigned long)0 ;  /*27*/
	initstr(msg->acqInstID);  /*31*/
	initstr(msg->forInst);     /*33*/
	initstr(msg->rspCod);      /* 38*/
	initstr(msg->termID);      /* 40*/
	initstr(msg->idenCod);    /*  41*/
	initstr(msg->addRspDat);  /*43*/
	initstr(msg->field47);  /*47*/
	initstr(msg->prvData.receNum);
	initstr(msg->prvData.checkNum);
	initstr(msg->prvData.beginDate);
	initstr(msg->prvData.endDate);
	initstr(msg->prvData.despTime);
	initstr(msg->prvData.despDollor);
	initstr(msg->prvData.despType);
	initstr(msg->prvData.despNum);
	initstr(msg->prvData.inqueNum);
	initstr(msg->prvData.exchangeCode);
	initstr(msg->prvData.accountType);
	initstr(msg->prvData.accountTyp1);
	initstr(msg->prvData.Reserved);
	initstr(msg->prvData.backData);
	initstr(msg->txnCuuCod);   /*48*/
	msg->pinDat=(unsigned long)0;         /*  51*/
	msg->addAmunt=(double)0;   /*53*/
	initstr(msg->netMngInfo);   /*69*/
	initstr(msg->OrgDatElm.msgType);  /*  89*/
	msg->OrgDatElm.tracNum=(unsigned long)0;  /*  89*/
	initstr(msg->OrgDatElm.txnDatTim);  /*  89*/
	initstr(msg->OrgDatElm.acqInstID);  /*  89*/
	initstr(msg->OrgDatElm.forInst);    /*  89*/
	initstr(msg->recvIntID);  /*99*/
	initstr(msg->chkAct);/*101*/
	memset(msg->mac,0,sizeof(msg->mac));/*101*/
	initstr(msg->mac1);/*101*/
	initstr(msg->mac2);/*101*/
	return(0);
}



