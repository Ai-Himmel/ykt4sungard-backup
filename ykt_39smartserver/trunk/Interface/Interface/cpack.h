
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CPACK_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// CPACK_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef CPACK_H
#define CPACK_H

#ifdef CPACK_EXPORTS
#define CPACK_API __declspec(dllexport)
#else
#define CPACK_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"..\\lib\\cpackd.lib") 
#pragma message("Automatically linking with cpackd.dll")
#else
#pragma comment(lib,"..\\lib\\cpack.lib") 
#pragma message("Automatically linking with cpack.dll")
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
/* ���´����������ֽڶ���ʹ�õ� */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#pragma options align=packed
#else
#define __PACKED__	__attribute__ ((packed))
#pragma pack(push,1)
#endif
#else
#define __PACKED__ 
#pragma pack(push,1)
#endif

/* ������PARMBITS������С��ÿ�ֽڵ�BITS�� */
#define PARMBITS	(256)
#define BITSPERBYTE	(8)

/*
	��ַ����
*/
typedef struct st_addr
{
	unsigned char addr[6];
}__PACKED__ ST_ADDR;

typedef struct st_hook
{
    unsigned int	UserID;					/* �����ߵ�ID����*/
	char hostname[33];						/* ������ */
	char queuename[33];						/* ������ */
	unsigned int	queuetype;				/* �������� */
}__PACKED__ ST_HOOK;

/* 
	��ͷ�ṹ
*/
typedef struct st_packhead
{
	unsigned int	RequestType;
	unsigned char	firstflag;				/* �Ƿ��һ�������װ�����*/
	unsigned char	nextflag;					/* �Ƿ����������*/
	unsigned int	recCount;					/* �����ļ�¼��*/
	unsigned int	retCode;					/* ���ش���*/
	
	ST_ADDR			addr;						/* �����ŵĵ�ַ��6���ӽڣ�*/
	ST_HOOK         hook;	                    /*                    */
	unsigned int    userdata;					/*					*/

	unsigned char ParmBits[PARMBITS/BITSPERBYTE];
}__PACKED__ ST_PACKHEAD;

/*
	������ÿһ��pack��Ա������ֵ����ʽ���£�
	0xAABB
	AA:	��Ա��PARMBITS�е��ֽں�(0��ʼ)
	BB: ��Ա������ֽڵ�λͼ
*/
#define F_SCUST_NO			0x0001
#define F_SCUST_NO2			0x0002
#define F_SHOLDER_AC_NO		0x0004
#define	F_SHOLDER_AC_NO2	0x0008
#define	F_SHOLDER_TYPE		0x0010
#define	F_SHOLDER_TYPE2		0x0020
#define F_SNAME				0x0040
#define	F_SNAME2			0x0080

#define	F_SALL_NAME			0x0101
#define F_SMARKET_CODE		0x0102
#define F_SMARKET_CODE2		0x0104
#define F_SDATE0			0x0108
#define F_SDATE1			0x0110
#define F_SDATE2			0x0120
#define F_SDATE3			0x0140
#define F_STIME0			0x0180

#define F_STIME1			0x0201
#define F_STIME2			0x0202
#define F_STIME3			0x0204
#define	F_LVOL0				0x0208
#define F_LVOL1				0x0210
#define F_LVOL2				0x0220
#define F_LVOL3				0x0240
#define F_LVOL4				0x0280

#define F_LVOL5				0x0301
#define F_LVOL6				0x0302
#define F_LVOL7				0x0304
#define F_LVOL8				0x0308
#define F_LVOL9				0x0310
#define F_LVOL10			0x0320
#define F_LVOL11			0x0340
#define F_LVOL12			0x0380

#define F_DAMT0				0x0401
#define F_DAMT1				0x0402
#define F_DAMT2				0x0404
#define F_DAMT3				0x0408
#define F_DAMT4				0x0410
#define F_DAMT5				0x0420
#define F_DAMT6				0x0440
#define F_DAMT7				0x0480

#define F_DAMT8				0x0501
#define F_DAMT9				0x0502
#define F_DAMT10			0x0504
#define F_DAMT11			0x0508
#define F_DAMT12			0x0510
#define F_DAMT13			0x0520
#define F_DAMT14			0x0540
#define F_DAMT15			0x0580

#define F_DAMT16			0x0601
#define F_DAMT17			0x0602
#define F_DAMT18			0x0604
#define F_DAMT19			0x0608
#define F_DAMT20			0x0610
#define F_DAMT21			0x0620
#define F_DAMT22			0x0640
#define	F_DAMT23			0x0680

#define F_DAMT24			0x0701
#define F_DAMT25			0x0702
#define F_DAMT26			0x0704
#define F_DAMT27			0x0708
#define F_DAMT28			0x0710
#define F_DAMT29			0x0720
#define F_DAMT30			0x0740
#define F_DAMT31			0x0780

#define F_DAMT32			0x0801
#define F_DAMT33			0x0802
#define F_SSTOCK_CODE		0x0804
#define F_SSTOCK_CODE2		0x0808
#define F_SCUST_TYPE		0x0810
#define F_SCUST_TYPE2		0x0820
#define F_SSTAT_TYPE		0x0840
#define F_SSTAT_TYPE2		0x0880

#define F_SROOM_NO			0x0901
#define F_SROOM_NO2			0x0902
#define F_SOPEN_EMP			0x0904
#define F_SCLOSE_EMP		0x0908
#define F_SCHANGE_EMP		0x0910
#define F_SCHECK_EMP		0x0920
#define F_SEMP				0x0940
#define F_SNATION_CODE		0x0980

#define F_LCERT_CODE		0x0A01
#define F_STX_PWD			0x0A02
#define F_STX_PWD2			0x0A04
#define F_SWITHDRAW_PWD		0x0A08
#define F_SWITHDRAW_PWD2	0x0A10
#define F_SEMP_PWD			0x0A20
#define F_SEMP_PWD2			0x0A40
#define F_SBANK_PWD			0x0A80

#define F_SBANK_PWD2		0x0B01
#define F_SCUST_AUTH		0x0B02
#define F_SCUST_AUTH2		0x0B04
#define F_SCUST_LIMIT		0x0B08
#define F_SCUST_LIMIT2		0x0B10
#define F_LSAFE_LEVEL		0x0B20
#define F_LSAFE_LEVEL2		0x0B40
#define F_SPOST_CODE		0x0B80

#define F_SPOST_CODE2		0x0C01
#define F_SPHONE			0x0C02
#define F_SPHONE2			0x0C04
#define F_SPHONE3			0x0C08
#define F_SPAGER			0x0C10
#define F_SEMAIL			0x0C20
#define F_SEMAIL2			0x0C40
#define F_SNOTE				0x0C80

#define F_SNOTE2			0x0D01
#define F_SCERT_NO			0x0D02
#define F_SCERT_NO2			0x0D04
#define F_SCERT_ADDR		0x0D08
#define F_SSTATUS0			0x0D10
#define F_SSTATUS1			0x0D20
#define F_SSTATUS2			0x0D40
#define F_SSTATUS3			0x0D80

#define F_SSTATUS4			0x0E01
#define F_LWITHDRAW_FLAG	0x0E02
#define F_SADDR				0x0E04
#define F_SADDR2			0x0E08
#define F_SSERIAL0			0x0E10
#define F_SSERIAL1			0x0E20
#define F_SSERIAL2			0x0E40
#define F_SSERIAL3			0x0E80

#define F_SSERIAL4			0x0F01
#define F_SCURRENCY_TYPE	0x0F02
#define F_SCURRENCY_TYPE2	0x0F04
#define F_SBRANCH_CODE0		0x0F08
#define F_SBRANCH_CODE1		0x0F10
#define F_SBRANCH_CODE2		0x0F20
#define F_USSET0			0x0F40
#define F_USSET1			0x0F80

#define F_USSET2			0x1001
#define F_USSET3			0x1002
#define F_USSET4			0x1004
#define F_USSET5			0x1008
#define F_USSET6			0x1010
#define F_SSTATION0			0x1020
#define F_SSTATION1			0x1040
#define F_SBANK_ACC			0x1080

#define F_SBANK_ACC2		0x1101
#define F_LBANK_ACC_TYPE	0x1102
#define F_LBANK_ACC_TYPE2	0x1104
#define F_SMAIN_FLAG		0x1108
#define F_SMAIN_FLAG2		0x1110
#define F_SBANK_CODE		0x1120
#define F_SBANK_CODE2		0x1140
#define F_SEMP_NO		0x1180
#define F_SEMP_NO2			0x1201
#define F_DRATE0			0x1202
#define F_DRATE1			0x1204
#define F_LSERIAL0			0x1208
#define F_LSERIAL1			0x1210
#define F_SBANKNAME			0x1220
#define F_SBANKNAME2			0x1240
#define F_SCARD0			0x1280

#define F_SCARD1			0x1301
#define F_SORDER0			0x1302
#define F_SORDER1			0x1304
#define F_SORDER2			0x1308
#define F_SCUSTTYPES		0x1310
#define F_SSECTYPES			0x1320

#define F_VSMESS			0x1601
#define F_VSVARSTR0			0x1602
#define F_VSVARSTR1			0x1604
#define F_VSVARSTR2			0x1608
#define F_VSVARSTR3			0x1610

typedef struct {
	char scust_no[11];			/*1 �ͻ��� */
	char scust_no2[11];			/* �ڶ��ͻ��� */
	char sholder_ac_no[16];		/* �ɶ����� */
	char sholder_ac_no2[16];	/* �ڶ��ɶ����� */
	char sholder_type[3];		/* �ɶ�������� */
	char sholder_type2[3];		/* �ڶ��ɶ�������� */
	char sname[21];				/* ���� */
	char sname2[21];			/* �ڶ����� */

	char sall_name[81];			/*2 ȫ�� */
	char smarket_code[2];		/* �г����� */
	char smarket_code2[2];		/* �г�����2 */
	char sdate0[9];				/* ���� ί������*/
	char sdate1[9];				/* ���� �ɽ�����*/
	char sdate2[9];				/* ���� ��������*/
	char sdate3[9];				/* ���� ��������*/
	char stime0[9];				/* ʱ�� ί��ʱ��*/

	char stime1[9];				/*3 ʱ�� �ɽ�ʱ��*/
	char stime2[9];				/* ʱ�� ����ʱ��*/
	char stime3[9];				/* ʱ�� ����ʱ��*/
	int		lvol0;				/* ����0 ί������		����1*/
	int		lvol1;				/* ����1 �ɽ�����		����2*/
	int		lvol2;				/* ����2 ��������		����3*/
	int		lvol3;				/* ����3 �ֹ���������	����4*/
	int		lvol4;				/* ����4 ί�ж�������	����1*/

	int		lvol5;				/*4 ����5 ����ɽ�����	����2*/
	int		lvol6;				/* ����6 �����ɽ�����	����3*/
	int		lvol7;				/* ����7 ��������		����4*/
	int		lvol8;				/* ����8 �ֹ��ⶳ���� */
	int		lvol9;				/* ����9 �������� */
	int		lvol10;				/* ����10 ȡ������ */
	int		lvol11;				/* ����11 ����δ�������� */
	int		lvol12;				/* ����12 ����δ�������� */

	double	damt0;				/*5 ���0 ί�м۸� */
	double	damt1;				/* ���1 ί�н�� */
	double	damt2;				/* ���2 �ɽ��۸� */
	double	damt3;				/* ���3 �ɽ���� */
	double	damt4;				/* ���4 �������� */
	double	damt5;				/* ���5 ������ */
	double  damt6;				/* ���6 ȡ����� */
	double	damt7;				/* ���7 �ֽ��� */

	double	damt8;				/*6 ���8 ֧��Ʊ��� */
	double	damt9;				/* ���9 �쳣������ */
	double	damt10;				/* ���10 ���붳���� */
	double	damt11;				/* ���11 ���������� */
	double	damt12;				/* ���12 ����ɽ���� */
	double	damt13;				/* ���13 �����ɽ���� */
	double	damt14;				/* ���14 �ֹ������� */
	double	damt15;				/* ���15 �ֹ��ⶳ��� */

	double	damt16;				/*7 ���16 ������ */
	double	damt17;				/* ���17 ������� */
	double	damt18;				/* ���18 ����δ������� */
	double	damt19;				/* ���19 ����δ������� */
	double	damt20;				/* ���20 ��Ϣ���� */
	double	damt21;				/* ���21 ��Ϣ���� */
	double	damt22;				/* ���22 ������Ϣ9���� */
	double	damt23;				/* ���23 ���ý�� */

	double	damt24;				/*8 ���24 �����ʽ� */
	double	damt25;				/* ���25 ��ȡ�ʽ� */
	double	damt26;				/* ���26 ��Ϣ */
	double	damt27;				/* ���27 ��Ϣ */
	double	damt28;				/* ���28 ������Ϣ */
	double	damt29;				/* ���29 ��ֵ */
	double	damt30;				/* ���30 ������֤�� */
	double	damt31;				/* ���31 ������ */

	double	damt32;				/*9 ���32 ӡ��˰ */
	double	damt33;				/* ���33 ������ */
	char	sstock_code[9];		/* ֤ȯ���� */
	char	sstock_code2[9];	/* ֤ȯ����2 */
	char	scust_type[3];		/* �ͻ���� */
	char	scust_type2[3];		/* �ͻ����2 */
	char	sstat_type[3];		/* ͳ����� */
	char	sstat_type2[3];		/* ͳ�����2 */

	char	sroom_no[4];		/*10 �ͻ���� */
	char	sroom_no2[4];		/* �ͻ����2 */
	char	sopen_emp[7];		/* ְ�� */
	char	sclose_emp[7];		/* ְ�� */
	char	schange_emp[7];		/* ְ�� */
	char	scheck_emp[7];		/* ����ְ�� */
	char	semp[7];			/* ְ�� */
	char	snation_code[4];	/* �������� */

	int		lcert_code;			/*11 ֤����� */
	char	stx_pwd[9];			/* �������� */
	char	stx_pwd2[9];		/* ��������2 */
	char	swithdraw_pwd[9];	/* ȡ������ */
	char	swithdraw_pwd2[9];	/* ȡ������2 */
	char	semp_pwd[9];		/* ��Ա���� */
	char	semp_pwd2[9];		/* ��Ա����2 */
	char	sbank_pwd[9];		/* �������� */

	char	sbank_pwd2[9];		/*12 ��������2 */
	char	scust_auth[21];		/* �ͻ�Ȩ�� */
	char	scust_auth2[21];	/* �ͻ�Ȩ��2 */
	char	scust_limit[33];	/* �ͻ����� */
	char	scust_limit2[33];	/* �ͻ�����2 */
	int		lsafe_level;		/* ��ȫ���� */
	int		lsafe_level2;		/* ��ȫ����2 */
	char	spost_code[7];		/* �������� */

	char	spost_code2[7];		/*13 ��������2 */
	char	sphone[31];			/* ��ϵ�绰 */
	char	sphone2[31];		/* fax */
	char	sphone3[31];		/* �ƶ��绰 */
	char	spager[31];			/* ���� */
	char	semail[61];			/* email */
	char	semail2[61];		/* email2 */
	char	snote[81];			/* ��ע */

	char	snote2[81];			/*14 ��ע2 */
	char	scert_no[51];		/* ���֤���� */
	char	scert_no2[51];		/* ���֤����2 */
	char	scert_addr[81];		/* ���֤��ַ */
	char	sstatus0[2];		/* ״̬���ͻ�״̬ */
	char	sstatus1[2];		/* ״̬1 */
	char	sstatus2[2];		/* ״̬2 */
	char	sstatus3[2];		/* ״̬3 */

	char	sstatus4[2];		/*15 ״̬4 */
	int		lwithdraw_flag;		/* ��ʽ */
	char	saddr[81];			/* ��ϵ��ַ */
	char	saddr2[81];			/* ��ϵ��ַ2 */
	char	sserial0[13];		/* ���0 */
	char	sserial1[13];		/* ���1 */
	char	sserial2[13];		/* ���2 */
	char	sserial3[13];		/* ���3 */

	char	sserial4[13];		/*16 ���4 */
	char	scurrency_type[3];	/* �������� */
	char	scurrency_type2[3];	/* ��������2 */
	char	sbranch_code0[4];	/* ����Ӫҵ������ */
	char	sbranch_code1[4];	/* ����Ӫҵ������ */
	char	sbranch_code2[4];	/* Ӫҵ������2 */
	unsigned char usset0[100];	/* ����Ȩ�޼��� */
	unsigned char usset1[100];	/* ��ȨȨ�޼��� */

	unsigned char usset2[100];	/*17 ����Ȩ�޼��� */
	unsigned char usset3[100];	/* �˵�Ȩ�޼��� */
	unsigned char usset4[100];	/* ��λ���� */
	unsigned char usset5[100];	/* �г����� */
	unsigned char usset6[100];	/* ���Ҽ��� */
	char	sstation0[17];		/* ����վ��ַ */
	char	sstation1[17];		/* ����վ��ַ2 */
	char	sbank_acc[41];		/* �����˺� */

	char	sbank_acc2[41];		/*18 �����˺�2 */
	int		lbank_acc_type;		/* �����˺���� */
	int		lbank_acc_type2;	/* �����˺����2 */
	char	smain_flag[2];		/* ������־ */
	char	smain_flag2[2];		/* ������־ */
	char	sbank_code[7];		/* ���д��� */
	char	sbank_code2[7];		/* ���д���2 */
	char	semp_no[9];			/* ���� */

	char	semp_no2[9];		/*19 ����2 */
	double	drate0;				/* ���� */
	double	drate1;				/* ����1 */
	int		lserial0;			/* ���к� 0 */
	int		lserial1;			/* ���к� 1 */
	char	sbankname[81];		/* �������� */
	char	sbankname2[81];		/* ��������2 */
	char	scard0[51];			/* �ſ����� */

	char	scard1[51];			/*20 �ſ����� */
	char	sorder0[11];			/* ��ͬ��� */
	char	sorder1[11];			/* ��ͬ��� */
	char	sorder2[11];			/* ��ͬ��� */
	char    scusttypes[201];	        /* �ͻ���𼯺� */
	char    ssectypes[201];	                /* ֤ȯ��𼯺� */

	char	vsmess[256];		/* 23 ��Ϣ */
	char	vsvarstr0[256];		/* �䳤���ַ��� */
	char	vsvarstr1[256];		/* �䳤���ַ��� */
	char	vsvarstr2[256];		/* �䳤���ַ��� */
	char	vsvarstr3[256];		/* �䳤���ַ��� */
}__PACKED__ ST_PACK;


typedef struct st_cpack
{
	ST_PACKHEAD head;
	ST_PACK		pack;
}__PACKED__ ST_CPACK;

#ifndef WIN32
#ifndef __GNUC__
#pragma options align=reset
#else
#pragma pack(pop)
#endif
#else
#pragma pack(pop)
#endif

CPACK_API void Reserve(unsigned char *buf,int len);
CPACK_API void Reverse(unsigned char *buf,int len);
CPACK_API void _DecodeSingleItem(int idx,ST_PACK *pPack,char **pSrc);
CPACK_API BOOL DecodeBufHead(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg);
CPACK_API BOOL DecodeBuf(unsigned char *buf,int len,ST_CPACK *pPack,char *eMsg);
CPACK_API BOOL DecodeBufWithArray(unsigned char *buf,int len,ST_CPACK *pPack,ST_PACK *packArray,
						int *recCount,char *eMsg);
CPACK_API void _EncodeSingleItem(int idx,ST_PACK *pPack,char **pDst,int *len);
CPACK_API BOOL ModifyHead(ST_PACKHEAD *pHeadPack,unsigned char *buf);
CPACK_API BOOL EncodeRow(ST_PACKHEAD *pHeadPack,ST_PACK *pRowPack,unsigned char *buf,int *len,char *eMsg);
CPACK_API BOOL EncodeBuf(ST_CPACK *pPack,unsigned char *buf,int *len,char *eMsg);
CPACK_API BOOL EncodeBufArray(ST_CPACK *pPack,ST_PACK *pArray,unsigned char *buf,int *len,char *eMsg);
CPACK_API BOOL SetParmBit(ST_PACKHEAD *ph,int bit);
CPACK_API BOOL SetErrorPack(ST_CPACK *inPack,ST_CPACK *outPack,
				  char *emsg,int eCode);
CPACK_API BOOL SetErrorPack2(ST_CPACK *outPack,char *emsg,int eCode);

CPACK_API BOOL SetErrorPackNew(ST_CPACK *inPack,ST_CPACK *outPack,
				  char *emsg,char *emsg2,int eCode);
CPACK_API BOOL SetErrorPack2New(ST_CPACK *outPack,char *emsg,char *emsg2,int eCode);

CPACK_API BOOL SetNormalPack(ST_CPACK *inPack,ST_CPACK *outPack,int nextflag,
				   int recCount);
CPACK_API void ShowPack(ST_CPACK *pack,char *buf);
CPACK_API void ShowHex(unsigned char *p,int len,char* buf);
CPACK_API void ShowPackItem(int idx,ST_PACK *pack,char *buf);
CPACK_API void ShowHex(unsigned char *p,int len,char* buf);
CPACK_API void ShowPackNext(ST_CPACK *pPack,ST_PACK *pack,char *buf);
CPACK_API void GetPatitionKey(int patitionmap,ST_PACK pack,char *key);
CPACK_API BOOL ClearParmBit(ST_PACKHEAD *ph,int bit);
CPACK_API BOOL IsInParmBits(ST_PACKHEAD head,int bit);
#ifdef __cplusplus
}
#endif

#endif