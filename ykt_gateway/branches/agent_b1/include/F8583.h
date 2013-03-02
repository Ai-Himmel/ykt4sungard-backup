#ifndef _ISO_F8583_H_
#define _ISO_F8583_H_

#ifdef _MSC_VER
#pragma once
#endif

#include <cassert>
#include "ksgexception.h"
#include "bit_endian.h"
#include "hddev/hddef.h"
#include "xutils/xtypelist.h"
#include "ksglobal.h"
#include "mytypes.h"
//#include <ace/OS.h>

// 根据不同系统，可能不一样
typedef unsigned char	uint8;
typedef short			int16;
typedef unsigned short	uint16;
typedef unsigned int	uint32;
typedef unsigned char BYTE;

//定义信息对应的域
#define FIELD1		(uint8)0		//未定义
#define FIELD2		(uint8)1		//终端序列号
#define FIELD3		(uint8)2		//CAN地址
#define FIELD4		(uint8)3		//卡号
#define FIELD5		(uint8)4		//交易金额
#define FIELD6		(uint8)5		//POS流水号
#define FIELD7		(uint8)6		//日期、时间
#define FIELD8		(uint8)7		//POS中心流水号
#define FIELD9		(uint8)8		//响应码
#define FIELD10		(uint8)9		//终端号
#define FIELD11		(uint8)10		//终端类型
#define FIELD12		(uint8)11		//商户号
#define FIELD13		(uint8)12		//PIN个人识别号
#define FIELD14		(uint8)13		//操作员号
#define FIELD15		(uint8)14		//累计充值额
#define FIELD16		(uint8)15		//交易批次号
#define FIELD17		(uint8)16		//原交易流水号
#define FIELD18		(uint8)17		//附加金额
#define FIELD19		(uint8)18		//黑名单版本
#define FIELD20		(uint8)19		//附加信息1
#define FIELD21		(uint8)20		//附加信息2
#define FIELD22		(uint8)21		//附加信息3
#define FIELD23		(uint8)22		//附加信息4
#define FIELD24		(uint8)23		//MAC值

#define _BIT_LEN (sizeof(unsigned char)*8)
#define PF_BITMAP_LEN(fieldcnt) (fieldcnt<_BIT_LEN ? 1 : (fieldcnt + 1) / _BIT_LEN)
#define _BITMAP_LEN(bt) (sizeof(bt) * 8)
#define _IS_BITMAP_SET(bt,offset) (bt[offset/8] & (1 << (7 - offset%8)))

enum
{
	IFT_CHAR = 0,
	IFT_BCD,
	IFT_BYTE,
	IFT_SHORT,
	IFT_USHORT,
	IFT_INT,
	IFT_UINT,
	IFT_LONG,
	IFT_ULONG,
	IFT_STRING,
	IFT_BUFFER,
	IFT_DATETIME,
	IFT_LONGLONG,
	IFT_NULL
};

struct ISO8583Field
{
	int length_in_byte;
	int length;
	char attribute;		// 0:char,1 1: BCD 
	char variable_flag;
	char bit_flag;
	unsigned char* data;
	union 
	{
		BYTE* _bValue;
		char* _cValue;
		short* _sValue;
		unsigned short* _usValue;
		int* _iValue;
		unsigned int* _uiValue;
		long* _lValue;
		unsigned long* _ulValue;
#ifndef NO_LONGLONG_TYPE
		long long* _llValue;
#endif
	};
};

uint16  GenerateCRC16(const unsigned char *pBuf, uint16 len);

template<class T,int fieldcount>
class ISO8583Msg
{
private:
	typedef T DataPackType;
	static const int FIELD_COUNT = fieldcount;
	static const int CRC_FIELD = 23;
	unsigned char _bitmap[PF_BITMAP_LEN(fieldcount)];
public:
	ISO8583Msg()
	{}

	size_t CalcCRC();
	size_t Pack(DataPackType& pack,void* buf,size_t maxlen)
	{
		if(pack.Unnormalize() != 0)
			return -1;
		memset(&_bitmap,0,sizeof(_bitmap));
		size_t offset = sizeof(_bitmap);
		unsigned char* output = static_cast<unsigned char*>(buf);
		for(int i = 0;i < FIELD_COUNT && offset < maxlen; ++i)
		{
			if(pack[i].bit_flag)
			{
				// 设置域长度
				switch(pack[i].variable_flag)
				{
				case 0:
					break;
				case 1:
					output[offset++] = static_cast<unsigned char>(pack[i].length_in_byte);
					break;
				default:
					output[offset] = pack[i].length_in_byte % 0x100;
					output[offset + 1] = pack[i].length_in_byte / 0x100;
					offset += 2;
					break;
				}
				memcpy(output+offset,pack[i].data,pack[i].length_in_byte);
				offset += pack[i].length_in_byte;
				_bitmap[i / 8] |= 1 << (7 - i % 8);
			}
		}
		// 拷贝位图
		memcpy(output,&_bitmap,sizeof(_bitmap));
		return offset;
	}
	int Unpack(DataPackType& pack,void* buf,size_t buflen)
	{
		memset(&_bitmap,0,sizeof(_bitmap));
		size_t offset = sizeof(_bitmap);
		unsigned char* input = static_cast<unsigned char*>(buf);
		pack.Init();
		memcpy(_bitmap,buf,sizeof(_bitmap));
		for(int i = 0;i < _BITMAP_LEN(_bitmap) && i < FIELD_COUNT && offset < buflen; ++i)
		{	
			if(_IS_BITMAP_SET(_bitmap,i))
			{
				pack[i].bit_flag = 1;
				switch(pack[i].variable_flag)
				{
				case 0:
					pack[i].length_in_byte = pack[i].length;
					break;
				case 1:
					pack[i].length_in_byte = input[offset++];
					break;
				default:
					BUF_2_SHORT(pack[i].length_in_byte,&input[offset]);
					offset += 2;
					break;
				}
				// 判断数据域长度
				// add 2006-8-16
				if((size_t)pack[i].length_in_byte > buflen - offset)
					return -1;
				memcpy(pack[i].data,&input[offset],pack[i].length_in_byte);
				offset += pack[i].length_in_byte;
			}
			else
			{
				pack[i].bit_flag = 0;
			}
		}
		if(pack.Normalize() != 0)
			return -1;
		return (int)offset;
	}
};


struct HD8583Record	// 按结构方式调用报文结构
{
	BYTE MessageType			;   // 信息码(报文类型)
	BYTE ResponseCode           ;   // 响应码
	BYTE TerminalType			;   // 终端类型
	BYTE WorkMode		        ;   // 终端工作模式
	BYTE IndexOfEW				;   // 电子钱包索引号
	MYDATETIMESTRUCT DateTime	;   // 日期和时间

	unsigned long CardNumber	;   // 卡号
	long Amount					;   // 交易金额
	long AdditionalAmount1	    ;   // 附加金额1
	long AdditionalAmount2		;   // 附加金额2
	unsigned long TraceOfPOS	;   // POS流水号
	unsigned long OrgTransTrace	;	// 原交易POS流水号
	unsigned long OperatorID    ;   // 操作员号
	unsigned long TerminalSN	;   // 终端序列号
	unsigned long VerOfList		;	// 黑名单版本

	unsigned short TraceOfEW    ;   // 电子钱包流水号
	unsigned short TerminalID   ;   // 终端号
	unsigned short MerchantID   ;   // 商户号
	unsigned short Address		;   // 终端地址

	short LenOfAdditionalData1	;	// 附加数据1长度
	BYTE AdditionalData1[2500]  ;   // 附加数据1
	short LenOfAdditionalData2	;	// 附加数据2长度
	BYTE AdditionalData2[2500]  ;   // 附加数据2
	short LenOfAdditionalData3	;	// 附加数据3长度
	char AdditionalData3[2500]  ;   // 附加数据3
	short LenOfAdditionalData4	;	// 附加数据4长度
	char AdditionalData4[2500]  ;   // 附加数据4

	BYTE PIN[8]                 ;   // 个人识别码
	BYTE WorkKey[8]             ;   // 工作密钥

	BYTE mac[2];
private:
	struct _Record_Index
	{
		int _index;

	};
};

class HD8583STRUCT
{
public:
	static const int PACK_LENGTH = 24;
private:
	typedef struct LT8583
	{
		unsigned char cTerminalSerial[4];			//Field 2 终端序列号
		unsigned char cCardNumber[4];         	// Field 4－卡号
		unsigned char cTransactionAmount[4];   // Field 5－交易金额(BCD..4, 数字)
		unsigned char cAuditNumber[4];         	// Field 6－POS流水号(BCD..4, 数字)
		unsigned char cHostTrace[4];			//Field 8 －POS中心流水号，(系统参考号)
		unsigned char cPIN[8];					//Field 13 －PIN 个人识别号
		unsigned char cOperatorID[4];             	// Field 14－操作员号(ASCII..4, 数字)
		unsigned char cAddUpTotalValue[4];		 		// Field 15－累计充值额
		unsigned char cOriginalAuditNumber[4]; // Field17－原交易流水号
		unsigned char cAdditionalAmounts[4];    // Field 18－附加金额(ASCII..8, 数字或字母)
		unsigned char cBlacklistVersion[4];  	// Field 19－黑名单版本
		unsigned char cAdditionalData1[550];  	// Field 20－附加信息1长度(BCD..2, 数字)
		unsigned char cAdditionalData2[420];  	// Field 21－附加信息2长度(BCD..2, 数字)
		unsigned char cAdditionalData3[48];  	// Field 22－附加信息3长度(BCD..2, 数字)	
		unsigned char cAdditionalData4[20];  	// Field 23－附加信息3长度(BCD..2, 数字)	

		unsigned char cCAN[2]	; 	         	 	// Field 3－CAN地址
		unsigned char cGroupNum[2];			// Field 16 --交易批次号	
		unsigned char cTerminalID[2];          	// Field 10－终端号(ASCII..2, 数字)
		unsigned char cTerminalType[2];		//Field 11 －终端类型
		unsigned char cMerchantID[2];         	// Field 12－商户号(ASCII..2, 数字)
		unsigned char cMac[2];                    		// Field 24－消息认证码(BIN..64, binary)
		unsigned char cPurseAudit[2];			// Field 6 －钱包流水号
		unsigned char cAckDateTime[7];             // Field 7－交易时间(BCD..3, 数字)
		unsigned char cResponseCode; 	       	// Field 9－响应码(ASCII..2, 数字或字母)
		unsigned char cMessageType;         		// 	信息类型
		unsigned char cPurseIndex;			// Field 5 钱包索引号
	}LT8583;
	static const int FIELD_LENGTH = 64;
	ISO8583Field _fields[FIELD_LENGTH];
	LT8583 HD8583;
	HD8583Record _record;
	int Normalize();
	int Unnormalize();
	void updateFieldLength(int fieldno);
public:
	template<class T,int LENGTH> friend class ISO8583Msg;
	HD8583STRUCT()
	{
		Init();
	}
	~HD8583STRUCT()
	{}

	ISO8583Field& operator[](int index)
	{
		assert(index >= 0 && index < PACK_LENGTH);
		return _fields[index];
	}
	void Init()
	{
		memset(&_fields,0,sizeof(_fields));
		memset(&_record,0,sizeof(_record));
		ISO8583Field temp[FIELD_LENGTH] = {
			/* FIELD  1 */ {0,0,   	IFT_NULL, 0, 0, NULL,NULL},				//扩展域否
			/* FIELD  2 */ {0,4, 	IFT_ULONG, 0, 0,HD8583.cTerminalSerial,(BYTE*)&_record.TerminalSN},// 终端序列号
			/* FIELD  3 */ {0,2,   	IFT_USHORT, 0, 0, HD8583.cCAN,(BYTE*)&_record.Address},				//CAN地址
			/* FIELD  4 */ {0,4, 	IFT_ULONG, 0, 0, HD8583.cCardNumber,(BYTE*)&_record.CardNumber},	//卡号
			/* FIELD  5 */ {0,1,   	IFT_BYTE, 0, 0, &HD8583.cPurseIndex,(BYTE*)&_record.IndexOfEW},	// 钱包索引
			/* FIELD  6 */ {0,2,   	IFT_USHORT, 0, 0, HD8583.cPurseAudit,(BYTE*)&_record.TraceOfEW},			// 钱包流水号
			/* FIELD  7 */ {0,4,   	IFT_LONG, 0, 0, HD8583.cTransactionAmount,(BYTE*)&_record.Amount},	// 交易金额
			/* FIELD  8 */ {0,4,  	IFT_LONG, 0, 0, HD8583.cAdditionalAmounts,(BYTE*)&_record.AdditionalAmount1},		//附加金额
			/* FIELD  9 */ {0,4,   	IFT_ULONG, 0, 0, HD8583.cAuditNumber,(BYTE*)&_record.TraceOfPOS},			//POS流水号
			/* FIELD 10 */ {0,4,  	IFT_ULONG, 0, 0, HD8583.cOriginalAuditNumber,(BYTE*)&_record.OrgTransTrace},	//原交易流水号
			/* FIELD 11 */ {0,7,   	IFT_DATETIME, 0, 0, HD8583.cAckDateTime,(BYTE*)&_record.DateTime},	//交易日期和时间
			/* FIELD 12 */ {0,1,   	IFT_BYTE, 0, 0, &HD8583.cResponseCode,(BYTE*)&_record.ResponseCode},//响应码
			/* FIELD 13 */{0,2,   	IFT_USHORT, 0, 0, HD8583.cTerminalID,(BYTE*)&_record.TerminalID},			//终端号
			/* FIELD 14 */{0,2, 	IFT_USHORT, 0, 0, HD8583.cTerminalType,(BYTE*)&_record.TerminalType},			//终端类型
			/* FIELD 15 */{0,2,  	IFT_USHORT, 0, 0, HD8583.cMerchantID,(BYTE*)&_record.MerchantID},			//商户(网点)号
			/* FIELD 16 */{0,4,  	IFT_ULONG, 0, 0, HD8583.cOperatorID,(BYTE*)&_record.OperatorID},			//操作员号
			/* FIELD 17 */{0,8,  	IFT_BUFFER, 0, 0, HD8583.cPIN,(BYTE*)&_record.PIN},					//个人识别码PIN
			/* FIELD 18 */{0,4, 	IFT_ULONG, 0, 0, HD8583.cBlacklistVersion,(BYTE*)&_record.VerOfList},		//黑名单版本

			/* FIELD 19 */{0,2,  	IFT_USHORT, 0, 0, HD8583.cGroupNum,(BYTE*)&_record.WorkMode},  //交易批次号(暂不用)
			/* FIELD 20 */{0,360, 	IFT_BUFFER, 2, 0, HD8583.cAdditionalData1,(BYTE*)_record.AdditionalData1},		//附加信息1
			/* FIELD 21 */{0,420, 	IFT_BUFFER, 2, 0, HD8583.cAdditionalData2,(BYTE*)_record.AdditionalData2},		//附加信息2
			/* FIELD 22 */{0,48, 	IFT_STRING, 2, 0, HD8583.cAdditionalData3,(BYTE*)_record.AdditionalData3},		//附加信息3
			/* FIELD 23 */{0,20, 	IFT_STRING, 2, 0, HD8583.cAdditionalData4,(BYTE*)_record.AdditionalData4},		//附加信息4
			/* FIELD 24 */{0,2, 	IFT_USHORT, 0, 0, HD8583.cMac,(BYTE*)_record.mac},					//消息认证码
			/* FIELD 25 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 26 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 27 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 28 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 29 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 30 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 31 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 32 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 33 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 34 */{0,0, 	IFT_NULL, 0, 0, NULL,NULL},					//
			/* FIELD 35 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 36 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 37 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 38 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 39 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 40 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 41 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 42 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 43 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 44 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 45 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 46 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 47 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 48 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 49 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 50 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 51 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 52 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 53 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 54 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 55 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 56 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 57 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 58 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 59 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 60 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 61 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 62 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 63 */{0,0, 	0, 0, 0, NULL,NULL},					//
			/* FIELD 64 */{0,2, 	IFT_USHORT, 0, 0, HD8583.cMac,(BYTE*)_record.mac},					//
		};
		memcpy(_fields,temp,sizeof(_fields));
	}
	template<class T>
	int SetFieldValue(int fieldno,T value)
	{
		if(fieldno < 0 || fieldno >= PACK_LENGTH)
			return -2;
		//memcpy(_fields[fieldno].data,(const void*)&value,sizeof(T));
		if(_fields[fieldno]._bValue == NULL)
			return -1;
		switch(_fields[fieldno].attribute)
		{
		case IFT_BYTE:
			*_fields[fieldno]._bValue = (BYTE)value;
			_fields[fieldno].length_in_byte = sizeof(BYTE);
			break;
		case IFT_CHAR:
			*_fields[fieldno]._cValue = (char)value;
			_fields[fieldno].length_in_byte = sizeof(char);
			break;
		case IFT_USHORT:
			*_fields[fieldno]._usValue = (unsigned short)value;
			_fields[fieldno].length_in_byte = sizeof(unsigned short);
			break;
		case IFT_SHORT:
			*_fields[fieldno]._sValue = (short)value;
			_fields[fieldno].length_in_byte = sizeof(short);
			break;
		case IFT_INT:
			*_fields[fieldno]._iValue = (int)value;
			_fields[fieldno].length_in_byte = sizeof(int);
			break;
		case IFT_UINT:
			*_fields[fieldno]._uiValue = (unsigned int)value;
			_fields[fieldno].length_in_byte = sizeof(unsigned int);
			break;
		case IFT_LONG:
			*_fields[fieldno]._lValue = (long)value;
			_fields[fieldno].length_in_byte = sizeof(long);
			break;
		case IFT_ULONG:
			*_fields[fieldno]._ulValue = (unsigned long)value;
			_fields[fieldno].length_in_byte = sizeof(unsigned long);
			break;
#ifndef NO_LONGLONG_TYPE
		case IFT_LONGLONG:
			*_fields[fieldno]._llValue = (long long)value;
			*_fields[fieldno].length_in_byte = sizeof(long long);
			break;
#endif
		case IFT_STRING:
		case IFT_BUFFER:
			return -1;
		default:
			return -1;
		}		
		_fields[fieldno].bit_flag = 1;
		return 0;
	}
	int SetFieldValue(int fieldno,char* buf)
	{
		if(fieldno < 0 || fieldno >= PACK_LENGTH)
			return -2;
		//memcpy(_fields[fieldno].data,(const void*)&value,sizeof(T));
		if(_fields[fieldno]._cValue == NULL)
			return -1;
		if(_fields[fieldno].attribute != IFT_STRING 
			&& _fields[fieldno].attribute != IFT_BUFFER)
			return -1;
		ACE_OS::strcpy(_fields[fieldno]._cValue,buf);
		_fields[fieldno].length_in_byte = (int)ACE_OS::strlen(buf);
		_fields[fieldno].bit_flag = 1;
		return 0;
	}
	int SetFieldValue(int fieldno,char* buf,int buflen)
	{
		ACE_ASSERT(_fields[fieldno].length >= buflen);
		if(_fields[fieldno].length < buflen )
			return -1;
		if(fieldno < 0 || fieldno >= PACK_LENGTH)
			return -2;
		memcpy(_fields[fieldno]._cValue,buf,buflen);
		_fields[fieldno].bit_flag = 1;
		_fields[fieldno].length_in_byte = buflen;
		return 0;
	}
	int SetFieldValue(int fieldno,unsigned char* buf,int buflen)
	{
		ACE_ASSERT(_fields[fieldno].length >= buflen);
		if(_fields[fieldno].length < buflen )
			return -1;
		if(fieldno < 0 || fieldno >= PACK_LENGTH)
			return -2;
		memcpy(_fields[fieldno]._bValue,buf,buflen);
		_fields[fieldno].bit_flag = 1;
		_fields[fieldno].length_in_byte = buflen;
		return 0;
	}
	HD8583Record* operator->()
	{
		return &_record;
	}
};

typedef ISO8583Msg<HD8583STRUCT,HD8583STRUCT::PACK_LENGTH> HDISO8583Msg;

#endif // _ISO_F8583_H_

