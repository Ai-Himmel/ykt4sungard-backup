#ifndef _KSG_HD_DEF_H_
#define _KSG_HD_DEF_H_

#ifdef _MSC_VER
#pragma once
#endif 

#include "ksglobal.h"
#include "mytypes.h"

//---------------------------------------------------------------------------
// �궨��
//---------------------------------------------------------------------------
// CCU�ļ�����
#define HDA_FILENAME_IMAGE				"vxworks"
#define HDA_FILENAME_VERSION			"Version.inf"
#define HDA_FILENAME_CONFIG				"Config.inf"
#define HDA_FILENAME_KEY				"Key.inf"
#define HDA_FILENAME_CARDRIGHT			"CardRight.dat"
#define HDA_FILENAME_TERMINAL			"Terminal.dat"
#define HDA_FILENAME_TEMPBLIST			"TempBList.dat"
#define HDA_FILENAME_TERBLIST			"TerBList.dat"
#define HDA_FILENAME_TARIFF				"Tariff.dat"
#define HDA_FILENAME_POSRULE			"POSRule.dat"
#define HDA_FILENAME_ACCESSRULE			"AccessRule.dat"
#define HDA_FILENAME_ATTENDRULE			"AttendRule.dat"
#define HDA_FILENAME_PRECORD1			"PRecord.dat"
#define HDA_FILENAME_PRECORD2			"PRecord2.dat"
#define HDA_FILENAME_GRECORD			"GRecord.dat"
#define HDA_FILENAME_ARECORD			"ARecord.dat"

// CCU�ļ�·��
#define HDA_CCUPATH_ROOT				"/ata0/"
#define HDA_CCUPATH_SYSTEM				"/ata0/sys/"
#define HDA_CCUPATH_CONFIG				"/ata0/config/"
#define HDA_CCUPATH_RECORD				"/ata0/record/"

// ����
#define HDA_BROADCASTADDRESSOFALL		0xffff	// CANȫ���㲥��ַ
#define HDA_BROADCASTADDRESSOFONE		0xff	// CAN�㲥��ַ
#define HDA_SYSTEMIDOFALL				0xff00	// ������ϵͳ��
#define HDA_SYSTEMIDOFATT1_1			0x0400	// CAN1.1����ϵͳ��ϵͳ��
#define HDA_SYSTEMIDOFACC1_1			0x0500	// CAN1.1�Ž�ϵͳ��ϵͳ��
#define HDA_SYSTEMIDOFPOS1_1			0x0600	// CAN1.1�շ�ϵͳ��ϵͳ��
#define HDA_SYSTEMIDOFADDPOS1_1			0x0900	// CAN1.1��ֵϵͳ��ϵͳ��

#define HDA_BROADCASTSN					0		// �㲥���к�
#define HDA_BROADCASTTERMINALID			0		// �㲥�ն˺�

#define HDA_REQMESSAGEOFBACKGROUND		1		// ��̨������
#define HDA_REQMESSAGEOFTERMINAL		0		// �ն�������
#define HDA_FIELDCOUNTOFBASALBITMAP		24		// ����λͼ�������
#define HDA_FIELDCOUNTOFEXTENDEDBITMAP	64		// ��չλͼ�������

#define CF_CAN10FRAMEMAXLEN				12		// CAN1.0֡��󳤶�
#define CF_CAN11FRAMEMAXLEN				13		// CAN1.1֡��󳤶�
#define CF_CAN20FRAMEMAXLEN				15		// CAN2.0֡��󳤶�
#define CF_RS232FRAMEMAXLEN				2500	// RS232֡��󳤶�

//---------------------------------------------------------------------------
// ö������
//---------------------------------------------------------------------------
enum CHINESETYPE// ��������
{
	GB_GB							= 0,	// ��̨��GB   / �նˣ�GB
	GB_BIG5							= 1,	// ��̨��GB   / �նˣ�BIG5
	BIG5_GB							= 2,	// ��̨��BIG5 / �նˣ�GB
	BIG5_BIG5						= 3,	// ��̨��BIG5 / �նˣ�BIG5
};

enum FILEID		// CCU�ļ�������
{
	FILEID_IMAGE					= 0, 	// Image�ļ�
	FILEID_VERSION					= 1, 	// CCU�汾�ļ�
	FILEID_CONFIG					= 2, 	// CCU�����ļ�
	FILEID_KEY						= 3, 	// ��Կ�ļ�
	FILEID_CARDRIGHT				= 4, 	// ��Ȩ���ļ�
	FILEID_TERMINAL					= 5, 	// �ն��ļ�
	FILEID_TEMPBLIST				= 6, 	// ��ʱ�������ļ�
	FILEID_TERBLIST					= 7, 	// �ն˺������ļ�
	FILEID_TARIFF					= 8, 	// ��Ŀ���ļ�
	FILEID_POSRULE					= 9, 	// �ն����ѹ����ļ�
	FILEID_ACCESSRULE				= 10,	// �ն��Ž������ļ�
	FILEID_ATTENDRULE				= 11,	// �ն˿��ڹ����ļ�
	FILEID_PRECORD1					= 12,	// ���Ѽ�¼�ļ�1
	FILEID_PRECORD2					= 13,	// ���Ѽ�¼�ļ�2
	FILEID_GRECORD					= 14,	// �Ž���¼�ļ�
	FILEID_ARECORD					= 15,	// ���ڼ�¼�ļ�
};

enum COMMTYPE	// ͨѶ��ʽ
{
	COMMTYPE_CAN1_0					= 0,	// CAN 1.0(��ַ1B)
	COMMTYPE_CAN1_1					= 1,	// CAN 1.1(��ַ2B)
	COMMTYPE_CAN2_0					= 2,	// CAN 2.0(��ַ2B)
	COMMTYPE_RS232					= 3,	// RS232
	COMMTYPE_TCP_IP					= 4,	// TCP/IP
};

enum FIELD		// �����
{
	FIELD_BITMAPTYPE				= 0,  	// BITMAP TYPE(0-BASAL BITMAP/1-EXTENDED BITMAP)
	FIELD_TERMINALSN				= 1,  	// TERMINAL SN
	FIELD_ADDRESS					= 2,  	// ADDRESS
	FIELD_CARDNUMBER				= 3,  	// CARD NUMBER
	FIELD_INDEXOFEW					= 4,  	// EW INDEX
	FIELD_EWTRACE					= 5,	// EW TRACE, TRANSACTION
	FIELD_TRANSAMOUNT				= 6,	// AMOUNT, TRANSACTION
	FIELD_ADDITIONALAMOUNTS			= 7,	// ADDITIONAL AMOUNTS
	FIELD_POSTRACE					= 8,	// POS TRACE
	FIELD_ORGTRANSTRACE				= 9,	// POS TRACE, ORIGINAL TRANS
	FIELD_DATEANDTIME				= 10,	// DATE & TIME
	FIELD_RESPONSECODE				= 11,	// RESPONSE CODE
	FIELD_TERMINALID				= 12,	// TERMINAL ID
	FIELD_TERMINALTYPE				= 13,	// TERMINAL TYPE
	FIELD_MERCHANTID				= 14,	// MERCHANT ID
	FIELD_OPERATORID				= 15,	// OPERATOR ID
	FIELD_PIN						= 16,	// PERSONAL IDENTIFICATION NUMBER
	FIELD_VERSIONOFLIST				= 17,	// LIST VERSION
	FIELD_RESERVEFIELD				= 18,	// RESERVE FIELD
	FIELD_ADDITIONALDATA1			= 19,	// ADDITIONAL DATA 1
	FIELD_ADDITIONALDATA2			= 20,	// ADDITIONAL DATA 2
	FIELD_ADDITIONALDATA3			= 21,	// ADDITIONAL DATA 3
	FIELD_ADDITIONALDATA4			= 22,	// ADDITIONAL DATA 4
	FIELD_MACOFBASALBITMAP			= 23,	// MAC OF BASAL BITMAP
	FIELD_MACOFEXTENDEDBITMAP		= 63,	// MAC OF EXTENDED BITMAP
};

enum MESSAGETYPE	// ��Ϣ��(Ϊż����ֵ��ʾ���ķ���Ϊ�ն�һ����Ϊ������ʾ���ķ���Ϊ��̨һ��)
{
	MT_INITPARA1					= 0x00,	// ��ʼ������
	MT_INITPARA2					= 0x01,	
	MT_INITKEY1						= 0x02,	// ��ʼ����Կ
	MT_INITKEY2						= 0x03,	
	MT_CLEARUPRECORD1				= 0x04,	// ��ռ�¼
	MT_CLEARUPRECORD2				= 0x05,	
	MT_ALLOTADDRESS1				= 0x06,	// �����ַ
	MT_ALLOTADDRESS2				= 0x07,	
	MT_SETFACTORYPARAOFTER2			= 0x09,	// �ն˳�������
	MT_SETFACTORYPARAOFCCU2			= 0x0b,	// CCU��������
	MT_SETUSERDEFNUMBER2			= 0x0d,	// �����û��Զ�����
	MT_SETHD4KSECTORANDKEY2			= 0x0f,	// ����HD4k����������Կ
	MT_CARDFROMHD4KTOHD6K1			= 0x10,	// ��Ƭ�ṹת��HD4k��HD6k

	MT_SIGNIN1						= 0x20,	// ǩ��
	MT_CONFIGPARA1					= 0x22,	// ���ò���
	MT_CONFIGPARA2					= 0x23,	
	MT_CONFIGTARIFF1				= 0x24,	// ���ü�Ŀ��
	MT_CONFIGTARIFF2				= 0x25,	
	MT_ONLINENOTICE1				= 0x26,	// �ն�����֪ͨ
	MT_ONLINENOTICE2				= 0x27,	
	MT_REECHO1						= 0x28,	// �������
	MT_REECHO2						= 0x29,	
	MT_UPDATELIST1					= 0x2a,	// ���º�����
	MT_UPDATELIST2					= 0x2b,	
	MT_CHANGEPIN1					= 0x2c,	// ��PIN��
	MT_AUTHGROUP1					= 0x2e,	// ��Ȩ����/����
	MT_AUTHGROUP2					= 0x2f,	
	MT_BATCHSENDRECORD1				= 0x30,	// �ѻ���¼������
	MT_BATCHSENDRECORD2				= 0x31,	// �ɼ��ѻ���¼
	MT_DELETERECORD2				= 0x33,	// ɾ�����βɼ���¼
	MT_UPDATEWORKKEY1				= 0x34,	// ���¹�����Կ
	MT_UPDATEWORKKEY2				= 0x35,
	MT_ACTIVECARD1					= 0x36,	// ��Ƭ����
	MT_SELFBOOKLOSSCARD1			= 0x38,	// ������ʧ
	MT_UPDATEIDLIST1				= 0x3a,	// ����ID������
	MT_UPDATEIDLIST2				= 0x3b,	
	MT_UPDATEIDWCLIST2				= 0x3d,	// ����ID������
	MT_REBATCHSENDRECORD2			= 0x3f,	// ���ɼ�¼

	MT_SET_FEE_RATE2				= 0x41, // ���÷������ѱ���

	MT_COLLECT_SERIAL1				= 0x45, // ָ����ˮ�Ų��ɼ�¼

	MT_QUERY1						= 0x50,	// ��ѯ
	MT_QUERYHISTORYTRADE1			= 0x52,	// ��ѯ�ն���ʷ����
	MT_QUERYHISTORYTRADEOFOPR1		= 0x54,	// ��ѯ��ǰ����Ա��ʷ����
	MT_QUERYTRADELISTOFSOMEONE1		= 0x5a,	// ��ѯĳ���ѿ��Ľ�����ϸ
	MT_TRADE1						= 0x60,	// ����
	MT_ALLOWANCE1					= 0x62,	// ����
	MT_RETURNGOODS1					= 0x64,	// �˻�
	MT_CANCELTRADE1					= 0x66,	// ����
	MT_ROLLBACK1					= 0x68,	// ����
	MT_DEPOSIT1						= 0x6a,	// ��ֵ
	MT_CLEARUPTRADE1				= 0x6c,	// ����

	MT_SETJOWTIME2					= 0x91,	// ���ô���ʱ��
	MT_SETCARDTIME2					= 0x93,	// ����ˢ��ʱ��
	MT_SENDATTENDEVENT1				= 0x94,	// ���Ϳ����¼�

	MT_GCUONLINENOTICE1				= 0xb0,	// GCU����֪ͨ
	MT_GCUONLINENOTICE2				= 0xb1,	
	MT_SETLOCKPROP2					= 0xb3,	// ���õ�������
	MT_SETACCESSPERIOD2				= 0xb5,	// �����Ž�ʱ��
	MT_SETWORKADAYACCESSRULE2		= 0xb7,	// ���ù������Ž�����
	MT_SETHOLIDAYACCESSRULE2		= 0xb9,	// ���ýڼ����Ž�����
	MT_UPDATEACCESSTABLE2			= 0xbb,	// �����Ž�Ȩ�ޱ�
	MT_REMOTEOPENLOCK2				= 0xbd,	// Զ�̿���
	MT_SENDACCESSEVENT1				= 0xbe,	// �����Ž��¼�

	MT_CCUONLINENOTICE1				= 0xf0,	// CCU����֪ͨ
	MT_CCUONLINENOTICE2				= 0xf1,	
	MT_REBOOTCCU2					= 0xf3,	// ����CCU
	MT_RELOADFILE2					= 0xf5,	// �����ļ�
	MT_DELETEFILE2					= 0xf7,	// ɾ���ļ�
	MT_LOCKFILE2					= 0xf9,	// �����ļ�
	MT_UPDATEWLISTOFCCU2			= 0xfb,	// ����CCU������
	MT_UPDATEBLISTOFCCU1			= 0xfc,	// ����CCU������
	MT_UPDATEBLISTOFCCU2			= 0xfd,	
	MT_CLEARFILE2					= 0xff,	// ����ļ�
};

enum RESPONSECODE// ������Ӧ��
{
	RC_SUCCESS						= 0, 	// ��׼��ɹ������
	RC_ENQUIRECENTER				= 1, 	// ���ѯ��������
	RC_ADDRESSCONFLICT				= 2, 	// ��ַ��ͻ
	RC_INVALIDMERCHANT				= 3, 	// ��Ч�̻�
	RC_SEIZURECARD					= 4,	// û�տ�
	RC_TERMINALSTATEERROR			= 5,	// �ն�״̬����
	RC_INVALIDMESSAGE				= 12,	// ��Ч����
	RC_INVALIDAMOUNT				= 13,	// ��Ч���
	RC_INVALIDCARDNO				= 14,	// ��Ч����
	RC_INVALIDOPRCARDNO				= 15,	// ��Ч����Ա����
	RC_NOORIGINALTRANS				= 25,	// δ���ҵ�ԭ����
	RC_DATAGRAMERROR				= 30,	// ���Ĵ�
	RC_MACERROR						= 31,	// ����MAC��
	RC_PINFORMATERROR				= 32,	// PIN��ʽ��
	RC_CONFIOVERDUECARD				= 33,	// ���ڵĿ�-û��
	RC_CONFIPINWRONGOVERTIMES		= 38,	// ���������PIN������-û��
	RC_LISTVERSIONERROR				= 39,	// �������汾����
	RC_CONFIREPORTLOSSCARD			= 41,	// ��ʧ��-û��
	RC_CONFIBESTOLENCARD			= 43,	// ���Կ�-û��
	RC_VERSIONERROR					= 44,	// �汾����(�������汾����)
	RC_NOTSUFFICIENT				= 51,	// ���㹻�Ĵ��
	RC_OVERDUECARD					= 54,	// ���ڵĿ�
	RC_PINWRONG						= 55,	// ����ȷ��PIN
	RC_UNALLOWEDTRANSFORCARDHOLDER	= 57,	// ������ֿ��˽��еĽ���
	RC_UNALLOWEDTRANSFORTERMINAL	= 58,	// �������ն˽��еĽ���
	RC_ORIGINALAMOUNTWRONG			= 64,	// ԭʼ����ȷ
	RC_GETCASHOVERTIMES				= 65,	// ����ȡ���������
	RC_PINWRONGOVERTIMES			= 75,	// ���������PIN��������
	RC_BALANCEWRONG					= 77,	// ���㲻ƽ
	RC_VOUCHERIDWRONG				= 78,	// ƾ֤�Ŵ���
	RC_BATCHIDWRONG					= 80,	// ���Ŵ���
	RC_ORIGINALTRANSBECHANGED		= 86,	// ԭ�����Ѹı�
	RC_NOANSWER						= 87,	// �ղ�����������Ӧ��
	RC_INVALIDTERMINAL				= 89,	// ��Ч�ն�
	RC_INDATESWITCHING				= 90,	// �����л����ڴ���
	RC_TRANSUNALLOWEDTEMP			= 91,	// ��������POS���Ĳ��ܲ���
	RC_TRANSREPEATED				= 94,	// �����ظ�
	RC_BALANCEWRONGANDBATCHSEND		= 95,	// ���㲻ƽ��Ҫ��������
	RC_SYSTEMDISABLED				= 96,	// ϵͳ�쳣��ʧЧ
};

enum ERRORCODE	// ������
{
	EC_SUCCESS						= 0,  	// �ɹ�
	EC_NOTFINISHFRM					= 1,	// ֡δ������
	EC_WRITECOMMDATAERROR			= 500,	// COMM�������ݴ���
	EC_WRITEHDLCDATAERROR			= 501,	// HDLC�������ݴ���
	EC_APPFRAMEOVERFLOW				= 1000,	// Ӧ��֡����
	EC_HDLCFRAMEOVERFLOW			= 1001,	// HDLC֡����
	EC_FRAMECHECKERROR				= 1002,	// ֡У�����
	EC_COMMTYPEERROR				= 1003,	// ͨѶ��ʽ����
	EC_FRAMEIDNOTCONTINUE			= 1004,	// ֡��ˮ������
	EC_ADDRESSFIELDNOTEXIT			= 1007,	// �������޵�ַ��
};

enum TERMINALTYPE		// �ն�����
{
	TERMINALTYPE_ICREADER			= 0x00,	// IC����д���ն�
	TERMINALTYPE_ICPOS				= 0x01,	// IC�������ն�
	TERMINALTYPE_ICATTEND			= 0x02,	// IC�������ն�
	TERMINALTYPE_ICGCU				= 0x03,	// IC��GCU
	TERMINALTYPE_ICCARDCONV			= 0x04,	// IC���ṹת����
	TERMINALTYPE_ICALLOWANCE		= 0x05,	// IC��������

	TERMINALTYPE_IDREADER			= 0x40,	// ID����д���ն�
	TERMINALTYPE_IDPOS				= 0x41,	// ID�������ն�
	TERMINALTYPE_IDATTEND			= 0x42,	// ID�������ն�
	TERMINALTYPE_IDGCU				= 0x43,	// ID��GCU
	TERMINALTYPE_IDALLOWANCE		= 0x45,	// ID��������
};

//---------------------------------------------------------------------------
// ���ݽṹ����
//---------------------------------------------------------------------------
struct ORGTRADERECORDSTRUCT// ԭʼ�������ݽṹ
{
	BYTE Data[47];
};

struct ORGATTENDRECORDSTRUCT// ԭʼ�������ݽṹ
{
	BYTE Data[14];
};

struct ORGACCESSRECORDSTRUCT// ԭʼ�Ž����ݽṹ
{
	BYTE Data[18];
};

struct ORGCONVCARDRECORDSTRUCT// ԭʼ���ṹת�����ݽṹ
{
	BYTE Data[38];
};

struct MYDATETIMESTRUCT// ����ʱ��ṹ
{
	BYTE Year;		// ��
	BYTE Month;		// ��
	BYTE Day;		// ��
	BYTE Hour;		// ʱ
	BYTE Minute;	// ��
	BYTE Second;	// ��
	BYTE DayOfWeek;	// ��
};

struct TRADERECORDSTRUCT// ���׼�¼���ݽṹ
{
	unsigned long CardNumber	;   // ����
	long Balance				;   // �����
	long Amount					;   // ���׽��
	unsigned long Year			;   // ��������
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// ����ʱ��
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TraceOfEW		;   // Ǯ����ˮ��
	unsigned long TraceOfPOS	;   // POS��ˮ��
	unsigned long OrgTransTrace ;	// ԭ����POS��ˮ��
	unsigned long OperatorID    ;   // ����Ա��
	//unsigned long PreTerminalSN ;   // ǰ�ʽ����ն����к�
	unsigned long TerminalSN;		// �ն����к�
	//unsigned long TerminalID    ;   // �����ն˺�
	short AdditionalMoney;		// �����
	unsigned long GoodsNumber	;   // ��Ʒ���
	unsigned long IndexOfEW		;   // Ǯ��������
	unsigned long RecordType	;   // ���Ѽ�¼����
	unsigned long ConsumeMode	;   // ����ģʽ
	BYTE MAC[4]					;   // MAC
};

struct ATTENDRECORDSTRUCT// ���ڼ�¼���ݽṹ
{
	unsigned long CardNumber	;   // ����
	unsigned long Year			;   // ����
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// ʱ��
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TerminalID    ;   // �ն˺�
	unsigned long ReaderID		;   // ��ͷ��
	unsigned long RecordType	;   // ��¼����
};

struct ACCESSRECORDSTRUCT// �Ž���¼���ݽṹ
{
	unsigned long CardNumber	;   // ����
	unsigned long Year			;   // ����
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// ʱ��
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TerminalID    ;   // �ն˺�
	unsigned long ReaderID		;   // ��ͷ��
	unsigned long EventType		;   // �¼�����
	unsigned char EventInfo[4]	;   // �¼���Ϣ
};

struct CONVCARDRECORDSTRUCT// ת�����ṹ��¼���ݽṹ
{
	unsigned long CardNumber	;   // ����
	long Balance				;   // �����
	unsigned long Year			;   // ��������
	unsigned long Month			;
	unsigned long Day			;
	unsigned long Hour			;	// ����ʱ��
	unsigned long Minute		;
	unsigned long Second		;
	unsigned long TraceOfEW		;   // Ǯ����ˮ��
	unsigned long TerminalID    ;   // �ն˺�
	unsigned char CardType[4]	;   // ������
	unsigned char Name[8]		;	// �ֿ�������
	unsigned long Grade			;   // ����
	unsigned long Group			;   // ����
	char PersonNo[8]			;   // �ֿ��˱��
	unsigned long RecordType	;   // ��¼����
};


//////////////////////////////////////////////////////////////////////
//
#include "999dev/999devtype.h"
#define KSG_HD_POS_DEV	KSG_999_DEV_POS 
#define KSG_HD_SERVER_DEV KSG_999_DEV_SERVER
#define KSG_HD_ADD_POS_DEV	KSG_999_DEV_ADDPOS
#define KSG_HD_GCU_DEV	"0121"

#define KSG_TASK_RESP_FUNC 930098

#define KSG_HD_CCU_LISTENER 1001

//<! CCU FTP �û���
//#define HD_CCU_FTP_USER	"hdhdhdhd"
#define HD_CCU_FTP_USER 1701
//<! CCU FTP ����
#define HD_CCU_FTP_PSWD 1702 //"11111111"
//<! CCU FTP �˿ں�
#define HD_CCU_FTP_PORT	1703 //"21"

#define FILE_CLOSE 0x00

#define DEL_BLK_LIST 0x00
#define ADD_BLK_LIST 0x01

#define HD_SYSPARAM_LISTEN_PORT 1200

namespace HDDEV
{
	extern std::string hd_ccu_ftp_user_name;
	extern std::string hd_ccu_ftp_pswd;
	extern std::string hd_ccu_ftp_port;
};


#endif // _KSG_HD_DEF_H_

