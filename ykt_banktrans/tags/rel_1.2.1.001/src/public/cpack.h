/********************************************************************
created:	2005/01/25 14:33:52
filename:cpack.h
author:chenyh
purpose:	ST_PACK data structure defined file 
		 created from cpack.dbf
*********************************************************************/
#ifndef __CPACK_H
#define __CPACK_H

#include "PackB.h"

// ���ֶ���Ŵ���ԭ�����ʹ�õ��ֶ�λͼ
// Define F_xxxx as field index number
#define F_SCUST_NO		0
#define F_SCUST_NO2		1
#define F_SHOLDER_AC_NO		2
#define F_SHOLDER_AC_NO2		3
#define F_SHOLDER_TYPE		4
#define F_SHOLDER_TYPE2		5
#define F_SNAME		6
#define F_SNAME2		7
#define F_SALL_NAME		8
#define F_SMARKET_CODE		9
#define F_SMARKET_CODE2		10
#define F_SDATE0		11
#define F_SDATE1		12
#define F_SDATE2		13
#define F_SDATE3		14
#define F_STIME0		15
#define F_STIME1		16
#define F_STIME2		17
#define F_STIME3		18
#define F_LVOL0		19
#define F_LVOL1		20
#define F_LVOL2		21
#define F_LVOL3		22
#define F_LVOL4		23
#define F_LVOL5		24
#define F_LVOL6		25
#define F_LVOL7		26
#define F_LVOL8		27
#define F_LVOL9		28
#define F_LVOL10		29
#define F_LVOL11		30
#define F_LVOL12		31
#define F_DAMT0		32
#define F_DAMT1		33
#define F_DAMT2		34
#define F_DAMT3		35
#define F_DAMT4		36
#define F_DAMT5		37
#define F_DAMT6		38
#define F_DAMT7		39
#define F_DAMT8		40
#define F_DAMT9		41
#define F_DAMT10		42
#define F_DAMT11		43
#define F_DAMT12		44
#define F_DAMT13		45
#define F_DAMT14		46
#define F_DAMT15		47
#define F_DAMT16		48
#define F_DAMT17		49
#define F_DAMT18		50
#define F_DAMT19		51
#define F_DAMT20		52
#define F_DAMT21		53
#define F_DAMT22		54
#define F_DAMT23		55
#define F_DAMT24		56
#define F_DAMT25		57
#define F_DAMT26		58
#define F_DAMT27		59
#define F_DAMT28		60
#define F_DAMT29		61
#define F_DAMT30		62
#define F_DAMT31		63
#define F_DAMT32		64
#define F_DAMT33		65
#define F_SSTOCK_CODE		66
#define F_SSTOCK_CODE2		67
#define F_SCUST_TYPE		68
#define F_SCUST_TYPE2		69
#define F_SSTAT_TYPE		70
#define F_SSTAT_TYPE2		71
#define F_SROOM_NO		72
#define F_SROOM_NO2		73
#define F_SOPEN_EMP		74
#define F_SCLOSE_EMP		75
#define F_SCHANGE_EMP		76
#define F_SCHECK_EMP		77
#define F_SEMP		78
#define F_SNATION_CODE		79
#define F_LCERT_CODE		80
#define F_STX_PWD		81
#define F_STX_PWD2		82
#define F_SWITHDRAW_PWD		83
#define F_SWITHDRAW_PWD2		84
#define F_SEMP_PWD		85
#define F_SEMP_PWD2		86
#define F_SBANK_PWD		87
#define F_SBANK_PWD2		88
#define F_SCUST_AUTH		89
#define F_SCUST_AUTH2		90
#define F_SCUST_LIMIT		91
#define F_SCUST_LIMIT2		92
#define F_LSAFE_LEVEL		93
#define F_LSAFE_LEVEL2		94
#define F_SPOST_CODE		95
#define F_SPOST_CODE2		96
#define F_SPHONE		97
#define F_SPHONE2		98
#define F_SPHONE3		99
#define F_SPAGER		100
#define F_SEMAIL		101
#define F_SEMAIL2		102
#define F_SNOTE		103
#define F_SNOTE2		104
#define F_SCERT_NO		105
#define F_SCERT_NO2		106
#define F_SCERT_ADDR		107
#define F_SSTATUS0		108
#define F_SSTATUS1		109
#define F_SSTATUS2		110
#define F_SSTATUS3		111
#define F_SSTATUS4		112
#define F_LWITHDRAW_FLAG		113
#define F_SADDR		114
#define F_SADDR2		115
#define F_SSERIAL0		116
#define F_SSERIAL1		117
#define F_SSERIAL2		118
#define F_SSERIAL3		119
#define F_SSERIAL4		120
#define F_SCURRENCY_TYPE		121
#define F_SCURRENCY_TYPE2		122
#define F_SBRANCH_CODE0		123
#define F_SBRANCH_CODE1		124
#define F_SBRANCH_CODE2		125
#define F_USSET0		126
#define F_USSET1		127
#define F_USSET2		128
#define F_USSET3		129
#define F_USSET4		130
#define F_USSET5		131
#define F_USSET6		132
#define F_SSTATION0		133
#define F_SSTATION1		134
#define F_SBANK_ACC		135
#define F_SBANK_ACC2		136
#define F_LBANK_ACC_TYPE		137
#define F_LBANK_ACC_TYPE2		138
#define F_SMAIN_FLAG		139
#define F_SMAIN_FLAG2		140
#define F_SBANK_CODE		141
#define F_SBANK_CODE2		142
#define F_SEMP_NO		143
#define F_SEMP_NO2		144
#define F_DRATE0		145
#define F_DRATE1		146
#define F_LSERIAL0		147
#define F_LSERIAL1		148
#define F_SBANKNAME		149
#define F_SBANKNAME2		150
#define F_SCARD0		151
#define F_SCARD1		152
#define F_SORDER0		153
#define F_SORDER1		154
#define F_SORDER2		155
#define F_SCUSTTYPES		156
#define F_SSECTYPES		157
#define F_VSMESS		176
#define F_VSVARSTR0		177
#define F_VSVARSTR1		178
#define F_VSVARSTR2		179
#define F_VSVARSTR3		180
/* ���´����������ֽڶ���ʹ�õ� */
#ifdef WIN32
   #define __PACKED__ 
   #pragma pack(push,1)
#else
   #ifdef __GNUC__
      #define __PACKED__	__attribute__ ((packed))
      //#pragma pack(push,1)
   #else
      #ifdef HP_UX
         #define __PACKED__
         #pragma pack 1
      #else
         #define __PACKED__
         #pragma options align=packed
      #endif
   #endif
#endif
typedef struct _ST_PACK 
{
	char	scust_no[11];		//0.1 �ͻ���
	char	scust_no2[11];		//1.�ڶ��ͻ���
	char	sholder_ac_no[16];		//2.�ɶ�����
	char	sholder_ac_no2[16];		//3.�ڶ��ɶ�����
	char	sholder_type[3];		//4.�ɶ��������
	char	sholder_type2[3];		//5.�ڶ��ɶ��������
	char	sname[21];		//6.����
	char	sname2[21];		//7.�ڶ�����
	char	sall_name[81];		//8.2 ȫ��
	char	smarket_code[2];		//9.�г�����
	char	smarket_code2[2];		//10.�г�����2
	char	sdate0[9];		//11.���� ί������
	char	sdate1[9];		//12.���� �ɽ�����
	char	sdate2[9];		//13.���� ��������
	char	sdate3[9];		//14.���� ��������
	char	stime0[9];		//15.ʱ�� ί��ʱ��
	char	stime1[9];		//16.3 ʱ�� �ɽ�ʱ��
	char	stime2[9];		//17.ʱ�� ����ʱ��
	char	stime3[9];		//18.ʱ�� ����ʱ��
	int	lvol0;		//19.����0 ί������ ����1
	int	lvol1;		//20.����1 �ɽ����� ����2
	int	lvol2;		//21.����2 �������� ����3
	int	lvol3;		//22.����3 �ֹ��������� ����4
	int	lvol4;		//23.����4 ί�ж������� ����1
	int	lvol5;		//24.����5 ����ɽ����� ����2
	int	lvol6;		//25.����6 �����ɽ����� ����3
	int	lvol7;		//26.����7 �������� ����4
	int	lvol8;		//27.����8 �ֹ��ⶳ����
	int	lvol9;		//28.����9 ��������
	int	lvol10;		//29.����10 ȡ������
	int	lvol11;		//30.����11 ����δ��������
	int	lvol12;		//31.����12 ����δ��������
	double	damt0;		//32.5 ���0 ί�м۸�
	double	damt1;		//33.���1 ί�н��
	double	damt2;		//34.���2 �ɽ��۸�
	double	damt3;		//35.���3 �ɽ����
	double	damt4;		//36.���4 ��������
	double	damt5;		//37.���5 ������
	double	damt6;		//38.���6 ȡ�����
	double	damt7;		//39.���7 �ֽ���
	double	damt8;		//40.6 ���8 ֧��Ʊ���
	double	damt9;		//41.���9 �쳣������
	double	damt10;		//42.���10 ���붳����
	double	damt11;		//43.���11 ����������
	double	damt12;		//44.���12 ����ɽ����
	double	damt13;		//45.���13 �����ɽ����
	double	damt14;		//46.���14 �ֹ�������
	double	damt15;		//47.���15 �ֹ��ⶳ���
	double	damt16;		//48.7 ���16 ������
	double	damt17;		//49.���17 �������
	double	damt18;		//50.���18 ����δ�������
	double	damt19;		//51.���19 ����δ�������
	double	damt20;		//52.���20 ��Ϣ����
	double	damt21;		//53.���21 ��Ϣ����
	double	damt22;		//54.���22 ������Ϣ9����
	double	damt23;		//55.���23 ���ý��
	double	damt24;		//56.8 ���24 �����ʽ�
	double	damt25;		//57.���25 ��ȡ�ʽ�
	double	damt26;		//58.���26 ��Ϣ
	double	damt27;		//59.���27 ��Ϣ
	double	damt28;		//60.���28 ������Ϣ
	double	damt29;		//61.���29 ��ֵ
	double	damt30;		//62.���30 ������֤��
	double	damt31;		//63.���31 ������
	double	damt32;		//64.9 ���32 ӡ��˰
	double	damt33;		//65.���33 ������
	char	sstock_code[9];		//66.֤ȯ����
	char	sstock_code2[9];		//67.֤ȯ����2
	char	scust_type[3];		//68.�ͻ����
	char	scust_type2[3];		//69.�ͻ����2
	char	sstat_type[3];		//70.ͳ�����
	char	sstat_type2[3];		//71.ͳ�����2
	char	sroom_no[4];		//72.10 �ͻ����
	char	sroom_no2[4];		//73.�ͻ����2
	char	sopen_emp[7];		//74.ְ��
	char	sclose_emp[7];		//75.ְ��
	char	schange_emp[7];		//76.ְ��
	char	scheck_emp[7];		//77.����ְ��
	char	semp[7];		//78.ְ��
	char	snation_code[4];		//79.��������
	int	lcert_code;		//80.11 ֤�����
	char	stx_pwd[9];		//81.��������
	char	stx_pwd2[9];		//82.��������2
	char	swithdraw_pwd[9];		//83.ȡ������
	char	swithdraw_pwd2[9];		//84.ȡ������2
	char	semp_pwd[9];		//85.��Ա����
	char	semp_pwd2[9];		//86.��Ա����2
	char	sbank_pwd[9];		//87.��������
	char	sbank_pwd2[9];		//88.12 ��������2
	char	scust_auth[21];		//89.�ͻ�Ȩ��
	char	scust_auth2[21];		//90.�ͻ�Ȩ��2
	char	scust_limit[33];		//91.�ͻ�����
	char	scust_limit2[33];		//92.�ͻ�����2
	int	lsafe_level;		//93.��ȫ����
	int	lsafe_level2;		//94.��ȫ����2
	char	spost_code[7];		//95.��������
	char	spost_code2[7];		//96.13 ��������2
	char	sphone[31];		//97.��ϵ�绰
	char	sphone2[31];		//98.fax
	char	sphone3[31];		//99.�ƶ��绰
	char	spager[31];		//100.����
	char	semail[61];		//101.email
	char	semail2[61];		//102.email2
	char	snote[81];		//103.��ע
	char	snote2[81];		//104.14 ��ע2
	char	scert_no[51];		//105.���֤����
	char	scert_no2[51];		//106.���֤����2
	char	scert_addr[81];		//107.���֤��ַ
	char	sstatus0[2];		//108.״̬���ͻ�״̬
	char	sstatus1[2];		//109.״̬1
	char	sstatus2[2];		//110.״̬2
	char	sstatus3[2];		//111.״̬3
	char	sstatus4[2];		//112.15 ״̬4
	int	lwithdraw_flag;		//113.��ʽ
	char	saddr[81];		//114.��ϵ��ַ
	char	saddr2[81];		//115.��ϵ��ַ2
	char	sserial0[13];		//116.���0
	char	sserial1[13];		//117.���1
	char	sserial2[13];		//118.���2
	char	sserial3[13];		//119.���3
	char	sserial4[13];		//120.16 ���4
	char	scurrency_type[3];		//121.��������
	char	scurrency_type2[3];		//122.��������2
	char	sbranch_code0[4];		//123.����Ӫҵ������
	char	sbranch_code1[4];		//124.����Ӫҵ������
	char	sbranch_code2[4];		//125.Ӫҵ������2
	unsigned char	usset0[100];		//126.����Ȩ�޼���
	unsigned char	usset1[100];		//127.��ȨȨ�޼���
	unsigned char	usset2[100];		//128.17 ����Ȩ�޼���
	unsigned char	usset3[100];		//129.�˵�Ȩ�޼���
	unsigned char	usset4[100];		//130.��λ����
	unsigned char	usset5[100];		//131.�г�����
	unsigned char	usset6[100];		//132.���Ҽ���
	char	sstation0[17];		//133.����վ��ַ
	char	sstation1[17];		//134.����վ��ַ2
	char	sbank_acc[41];		//135.�����˺�
	char	sbank_acc2[41];		//136.18 �����˺�2
	int	lbank_acc_type;		//137.�����˺����
	int	lbank_acc_type2;		//138.�����˺����2
	char	smain_flag[2];		//139.������־
	char	smain_flag2[2];		//140.������־
	char	sbank_code[7];		//141.���д���
	char	sbank_code2[7];		//142.���д���2
	char	semp_no[9];		//143.����
	char	semp_no2[9];		//144.19 ����2
	double	drate0;		//145.����
	double	drate1;		//146.����1
	int	lserial0;		//147.���к� 0
	int	lserial1;		//148.���к� 1
	char	sbankname[81];		//149.��������
	char	sbankname2[81];		//150.��������2
	char	scard0[51];		//151.�ſ�����
	char	scard1[51];		//152.20 �ſ�����
	char	sorder0[11];		//153.��ͬ���
	char	sorder1[11];		//154.��ͬ���
	char	sorder2[11];		//155.��ͬ���
	char	scusttypes[201];		//156.�ͻ���𼯺�
	char	ssectypes[201];		//157.֤ȯ��𼯺�
	char	vsmess[256];		//176.23 ��Ϣ
	char	vsvarstr0[256];		//177.�䳤���ַ���
	char	vsvarstr1[256];		//178.�䳤���ַ���
	char	vsvarstr2[256];		//179.�䳤���ַ���
	char	vsvarstr3[256];		//180.�䳤���ַ���
} __PACKED__ ST_PACK;
typedef struct _ST_CPACK
{
	ST_PACKHEAD head;
	ST_PACK     pack;
} __PACKED__ ST_CPACK;
#ifdef WIN32
   #pragma pack(pop)
#else
   #ifdef __GNUC__
   #else
      #ifdef HP_UX
         #pragma pack 0
      #else
         #pragma options align=reset
      #endif
   #endif
#endif
#undef __PACKED__

#include "PackC.h"

#endif
