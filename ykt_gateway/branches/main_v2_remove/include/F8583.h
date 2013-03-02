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

// ���ݲ�ͬϵͳ�����ܲ�һ��
typedef unsigned char	uint8;
typedef short			int16;
typedef unsigned short	uint16;
typedef unsigned int	uint32;
typedef unsigned char BYTE;

//������Ϣ��Ӧ����
#define FIELD1		(uint8)0		//δ����
#define FIELD2		(uint8)1		//�ն����к�
#define FIELD3		(uint8)2		//CAN��ַ
#define FIELD4		(uint8)3		//����
#define FIELD5		(uint8)4		//���׽��
#define FIELD6		(uint8)5		//POS��ˮ��
#define FIELD7		(uint8)6		//���ڡ�ʱ��
#define FIELD8		(uint8)7		//POS������ˮ��
#define FIELD9		(uint8)8		//��Ӧ��
#define FIELD10		(uint8)9		//�ն˺�
#define FIELD11		(uint8)10		//�ն�����
#define FIELD12		(uint8)11		//�̻���
#define FIELD13		(uint8)12		//PIN����ʶ���
#define FIELD14		(uint8)13		//����Ա��
#define FIELD15		(uint8)14		//�ۼƳ�ֵ��
#define FIELD16		(uint8)15		//�������κ�
#define FIELD17		(uint8)16		//ԭ������ˮ��
#define FIELD18		(uint8)17		//���ӽ��
#define FIELD19		(uint8)18		//�������汾
#define FIELD20		(uint8)19		//������Ϣ1
#define FIELD21		(uint8)20		//������Ϣ2
#define FIELD22		(uint8)21		//������Ϣ3
#define FIELD23		(uint8)22		//������Ϣ4
#define FIELD24		(uint8)23		//MACֵ

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
				// �����򳤶�
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
		// ����λͼ
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
				// �ж������򳤶�
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


struct HD8583Record	// ���ṹ��ʽ���ñ��Ľṹ
{
	BYTE MessageType			;   // ��Ϣ��(��������)
	BYTE ResponseCode           ;   // ��Ӧ��
	BYTE TerminalType			;   // �ն�����
	BYTE WorkMode		        ;   // �ն˹���ģʽ
	BYTE IndexOfEW				;   // ����Ǯ��������
	MYDATETIMESTRUCT DateTime	;   // ���ں�ʱ��

	unsigned long CardNumber	;   // ����
	long Amount					;   // ���׽��
	long AdditionalAmount1	    ;   // ���ӽ��1
	long AdditionalAmount2		;   // ���ӽ��2
	unsigned long TraceOfPOS	;   // POS��ˮ��
	unsigned long OrgTransTrace	;	// ԭ����POS��ˮ��
	unsigned long OperatorID    ;   // ����Ա��
	unsigned long TerminalSN	;   // �ն����к�
	unsigned long VerOfList		;	// �������汾

	unsigned short TraceOfEW    ;   // ����Ǯ����ˮ��
	unsigned short TerminalID   ;   // �ն˺�
	unsigned short MerchantID   ;   // �̻���
	unsigned short Address		;   // �ն˵�ַ

	short LenOfAdditionalData1	;	// ��������1����
	BYTE AdditionalData1[2500]  ;   // ��������1
	short LenOfAdditionalData2	;	// ��������2����
	BYTE AdditionalData2[2500]  ;   // ��������2
	short LenOfAdditionalData3	;	// ��������3����
	char AdditionalData3[2500]  ;   // ��������3
	short LenOfAdditionalData4	;	// ��������4����
	char AdditionalData4[2500]  ;   // ��������4

	BYTE PIN[8]                 ;   // ����ʶ����
	BYTE WorkKey[8]             ;   // ������Կ

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
		unsigned char cTerminalSerial[4];			//Field 2 �ն����к�
		unsigned char cCardNumber[4];         	// Field 4������
		unsigned char cTransactionAmount[4];   // Field 5�����׽��(BCD..4, ����)
		unsigned char cAuditNumber[4];         	// Field 6��POS��ˮ��(BCD..4, ����)
		unsigned char cHostTrace[4];			//Field 8 ��POS������ˮ�ţ�(ϵͳ�ο���)
		unsigned char cPIN[8];					//Field 13 ��PIN ����ʶ���
		unsigned char cOperatorID[4];             	// Field 14������Ա��(ASCII..4, ����)
		unsigned char cAddUpTotalValue[4];		 		// Field 15���ۼƳ�ֵ��
		unsigned char cOriginalAuditNumber[4]; // Field17��ԭ������ˮ��
		unsigned char cAdditionalAmounts[4];    // Field 18�����ӽ��(ASCII..8, ���ֻ���ĸ)
		unsigned char cBlacklistVersion[4];  	// Field 19���������汾
		unsigned char cAdditionalData1[550];  	// Field 20��������Ϣ1����(BCD..2, ����)
		unsigned char cAdditionalData2[420];  	// Field 21��������Ϣ2����(BCD..2, ����)
		unsigned char cAdditionalData3[48];  	// Field 22��������Ϣ3����(BCD..2, ����)	
		unsigned char cAdditionalData4[20];  	// Field 23��������Ϣ3����(BCD..2, ����)	

		unsigned char cCAN[2]	; 	         	 	// Field 3��CAN��ַ
		unsigned char cGroupNum[2];			// Field 16 --�������κ�	
		unsigned char cTerminalID[2];          	// Field 10���ն˺�(ASCII..2, ����)
		unsigned char cTerminalType[2];		//Field 11 ���ն�����
		unsigned char cMerchantID[2];         	// Field 12���̻���(ASCII..2, ����)
		unsigned char cMac[2];                    		// Field 24����Ϣ��֤��(BIN..64, binary)
		unsigned char cPurseAudit[2];			// Field 6 ��Ǯ����ˮ��
		unsigned char cAckDateTime[7];             // Field 7������ʱ��(BCD..3, ����)
		unsigned char cResponseCode; 	       	// Field 9����Ӧ��(ASCII..2, ���ֻ���ĸ)
		unsigned char cMessageType;         		// 	��Ϣ����
		unsigned char cPurseIndex;			// Field 5 Ǯ��������
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
			/* FIELD  1 */ {0,0,   	IFT_NULL, 0, 0, NULL,NULL},				//��չ���
			/* FIELD  2 */ {0,4, 	IFT_ULONG, 0, 0,HD8583.cTerminalSerial,(BYTE*)&_record.TerminalSN},// �ն����к�
			/* FIELD  3 */ {0,2,   	IFT_USHORT, 0, 0, HD8583.cCAN,(BYTE*)&_record.Address},				//CAN��ַ
			/* FIELD  4 */ {0,4, 	IFT_ULONG, 0, 0, HD8583.cCardNumber,(BYTE*)&_record.CardNumber},	//����
			/* FIELD  5 */ {0,1,   	IFT_BYTE, 0, 0, &HD8583.cPurseIndex,(BYTE*)&_record.IndexOfEW},	// Ǯ������
			/* FIELD  6 */ {0,2,   	IFT_USHORT, 0, 0, HD8583.cPurseAudit,(BYTE*)&_record.TraceOfEW},			// Ǯ����ˮ��
			/* FIELD  7 */ {0,4,   	IFT_LONG, 0, 0, HD8583.cTransactionAmount,(BYTE*)&_record.Amount},	// ���׽��
			/* FIELD  8 */ {0,4,  	IFT_LONG, 0, 0, HD8583.cAdditionalAmounts,(BYTE*)&_record.AdditionalAmount1},		//���ӽ��
			/* FIELD  9 */ {0,4,   	IFT_ULONG, 0, 0, HD8583.cAuditNumber,(BYTE*)&_record.TraceOfPOS},			//POS��ˮ��
			/* FIELD 10 */ {0,4,  	IFT_ULONG, 0, 0, HD8583.cOriginalAuditNumber,(BYTE*)&_record.OrgTransTrace},	//ԭ������ˮ��
			/* FIELD 11 */ {0,7,   	IFT_DATETIME, 0, 0, HD8583.cAckDateTime,(BYTE*)&_record.DateTime},	//�������ں�ʱ��
			/* FIELD 12 */ {0,1,   	IFT_BYTE, 0, 0, &HD8583.cResponseCode,(BYTE*)&_record.ResponseCode},//��Ӧ��
			/* FIELD 13 */{0,2,   	IFT_USHORT, 0, 0, HD8583.cTerminalID,(BYTE*)&_record.TerminalID},			//�ն˺�
			/* FIELD 14 */{0,2, 	IFT_USHORT, 0, 0, HD8583.cTerminalType,(BYTE*)&_record.TerminalType},			//�ն�����
			/* FIELD 15 */{0,2,  	IFT_USHORT, 0, 0, HD8583.cMerchantID,(BYTE*)&_record.MerchantID},			//�̻�(����)��
			/* FIELD 16 */{0,4,  	IFT_ULONG, 0, 0, HD8583.cOperatorID,(BYTE*)&_record.OperatorID},			//����Ա��
			/* FIELD 17 */{0,8,  	IFT_BUFFER, 0, 0, HD8583.cPIN,(BYTE*)&_record.PIN},					//����ʶ����PIN
			/* FIELD 18 */{0,4, 	IFT_ULONG, 0, 0, HD8583.cBlacklistVersion,(BYTE*)&_record.VerOfList},		//�������汾

			/* FIELD 19 */{0,2,  	IFT_USHORT, 0, 0, HD8583.cGroupNum,(BYTE*)&_record.WorkMode},  //�������κ�(�ݲ���)
			/* FIELD 20 */{0,360, 	IFT_BUFFER, 2, 0, HD8583.cAdditionalData1,(BYTE*)_record.AdditionalData1},		//������Ϣ1
			/* FIELD 21 */{0,420, 	IFT_BUFFER, 2, 0, HD8583.cAdditionalData2,(BYTE*)_record.AdditionalData2},		//������Ϣ2
			/* FIELD 22 */{0,48, 	IFT_STRING, 2, 0, HD8583.cAdditionalData3,(BYTE*)_record.AdditionalData3},		//������Ϣ3
			/* FIELD 23 */{0,20, 	IFT_STRING, 2, 0, HD8583.cAdditionalData4,(BYTE*)_record.AdditionalData4},		//������Ϣ4
			/* FIELD 24 */{0,2, 	IFT_USHORT, 0, 0, HD8583.cMac,(BYTE*)_record.mac},					//��Ϣ��֤��
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

