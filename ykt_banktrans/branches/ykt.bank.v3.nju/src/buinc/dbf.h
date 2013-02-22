// DBF.h: interface for the CDBF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBF_H__284EC5BE_7513_469F_90AD_F867587F2973__INCLUDED_)
#define AFX_DBF_H__284EC5BE_7513_469F_90AD_F867587F2973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
���ж������ݿ��ļ���ʱ�Ĺ���ģʽ��
EXCL_ON -- ��ռ�򿪣� ���������û����޷��򿪣����Լ�������һ������Ҳ���ܴ���
EXCL_OFF -- ����򿪣� �ɹ��������û����������ñ���ʽ�򿪣���FOX��
         :set excl off
         :use xxxx
         ���ܹ��ɹ���
*/
#define EXCL_ON  1
#define EXCL_OFF 0

/*
���ж������ݿ��ļ������ͣ���Ҫ��ͬ���ں�����ϵͳ�������ݿ�ʱ�����ļ�����
*/
enum DBF_TYPES {
   DBF_FOXBASE = 0,
   DBF_DBASE3  = 1,
   DBF_CLIPPER = 2,
   DBF_DBASE4  = 3,
   DBF_FOXPRO  = 4,
   DBF_FOXCDX  = 5
};

/*
���ж������ݿ��ļ���ʱ��
      ֻ���򿪣�ACCESS_RDONLY��������
      ��д�򿪣�ACCESS_RDWR��
*/
#define ACCESS_RDONLY  0
#define ACCESS_RDWR    1


#define MAXFNL 256
#define MAXLEVELS 6

/*
DBF_ERRNO: Ϊ�󲿷����ݿ⺯����������ֵ
*/
enum DBF_ERRNO {
   DBF_OK = 0,
   DBF_HEADERR,  // ����ȷ�����ݿ�ͷ
   DBF_NOMEM,    // û���㹻���ڴ�
   DBF_OPENFAIL, // ���ļ���ʧ��, �繲���ʧ�� �� ��ռ��ʧ��, �򲻴��ڸ��ļ���
   DBF_RECNOERR, // ��������ʱ,��¼�Ų���ȷ, ���¼��<1
   DBF_RECNO_OF, // ��¼�Ų���ȷ, ��¼�ų����ܵļ�¼����
   DBF_RECLOCFAIL, // ��¼��λʧ��, _lseek failure
   DBF_READFAIL, // ��¼���ݶ�ȡʧ��
   DBF_LOCKFAIL, // ���ݿ���������ʧ��
   DBF_WRITEFAIL, // ��¼����д��ʧ��
   DBF_EOF,       // ���ܶ�λ,
   DBF_USED       // ���ݿ�������
};

/*
����һ�鶨��Ϊ�ֶ����ͺʹ��������
*/


#define FT_STRING   'C'  // Ϊ�ַ����� �� ��C��
#define FT_DOUBLE   'N'  // Ϊ�������� �� ��N��
#define FT_LOGICAL  'L'  // Ϊ�߼����� �� ��L�� 
#define FT_MEMO     'M' // MEMO����  �� ��M��
#define FT_DATE     'D' // ��������  �� ��D��
#define FT_BINARY   'X' // ���������� �� ��X�� ��ϵͳ���е����ͣ����ڴ����������ݣ���󳤶Ⱥ�F_WORDLEN�й�
#define FT_UNDEFINED 0xFF  // δ������ֶ�����
#define FV_OUTREC    0xFE   // ��¼û�ж�λ
#define FV_NOFIELD   0xFD   // û���ҵ����ֶ�



/*
����һ�鶨��Ϊ��¼��λʱ�ȽϵıȽϷ�
*/
#define DBFCMP_LT  -2
#define DBFCMP_LE  -1
#define DBFCMP_EQ   0
#define DBFCMP_GE   1
#define DBFCMP_GT   2

#ifndef BYTE
#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned int
#endif

#ifndef NULL
#define NULL 0
#endif


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

//#define F_WORDLEN

typedef struct {
  char name[11];
  char f_type;  // 'C':char; 'N':Numeric; 'L':Logic; 'M':Memo; 'D':Date; 'Y':CURRENCY; 'T':DATETIME;'B':DOUBLE;'I':INTEGER;'L':LOGICAL;'G':General;'C':CharacterBinary;'M':MemoBinary
  int  address;  // never mind...
#ifdef F_WORDLEN
  unsigned short len;
#else
  unsigned char len;
#endif
  unsigned char bits;  // use only in type='N', else as 0;
  unsigned char blen;  // use in 'Y','T','B','I','C'-CharBinary,'M'-MemoBinary
} __PACKED__ TField;



class __PACKED__ CDBF  
{
private:
   BYTE *buffer;
   unsigned int current_recno;

   char *fvtemp;
   int field_no;
   TField *first;

   char   dbf_name[MAXFNL];

   int    handle;
   int    exclusive;  /* 1 -- on , 0 -- off */
   int    access;
   int    dbf_type;   

   BYTE version;
   BYTE year,month,day;
   DWORD record_no;
   WORD head_len;
   WORD record_len;
   BYTE reserved[20];

private:
	int dbf_setdeleteflag(char flag);
	int dbf_wbuffer(DWORD recno,void *buf);
	int dbf_update_head();
	bool reopen_dbf();
	int dbf_buffer(DWORD recno,void *buf=NULL);
	DWORD dbf_rec_pos(DWORD recno);
	int locktype(int ltype,DWORD lstart,DWORD len);
   
public:
	TField * f4field(int fieldno);

   // ������: f4r_field
   // ���  : ������ 2003-10-10 12:24:16
   // ����  : ֻ����fieldbuf�޸ĵ�ǰ��¼��ָ�����ֶ�ֵ����д�뵽DBF��
   // ����  : int д��ĳ��ȣ�==0����>0һ���ǶԵģ�
   // ����  : char *fieldname
   // ����  : void *fieldbuf
	int f4r_field(char *fieldname,void *fieldbuf);
   
	int d4create(char *filename,int fields,TField *fieldlist);
	bool d4used();
	int d4writerecords(DWORD from,DWORD records,void *buf);
	bool d4isdeleted();
	int d4undeleterecord();
	int d4deleterecord();
	bool d4eof();
	int d4readrecord(unsigned int from,unsigned int records,void *buf);
	void d4getbuffer(void *buf);
	int d4putrec(void *buf=NULL);

   // ��������ר����ԡ�X���� �����������ֶβ���
	int f4binary(char *fieldname,void *value,int valuesize);
	int f4b_binary(char *fieldname,void *bin,int blen);


   // f4b_xx ���ڷ�'X'��Ļ���д����������d4putrec()��d4append()������д�뵽DBF����
	int f4b_char(char *fieldname,char c);
	int f4b_double(char *fieldname,double data);
	int f4b_int(char *fieldname,int data);
	int f4b_str(char *fieldname,char *fvalue);

   // f4xxxx����Ϊ��ȡ�ֶ��е����ݣ�ע���ֶ�����Ϊ'X'���ܴ���ͳ���Ĳ�ͬ��Ӧ��f4binary(...)
	int f4ncpy(char *fieldname,void *value,int vlen);
	long f4long(char *fieldname);
	int f4int(char *fieldname);
	char * f4str(char *fieldname);
	double f4double(char *fieldname);
	char f4char(char *fieldname);
	void * f4bstr(char *fieldname);
	
   int f4setvalue(char *fieldname,void *value);

   // ���ֶ����ݵ�ԭֵ�����value���أ�����Ϊ��Ӧ���ֶζ���
	TField * f4getvalue(char *fieldname,void *value,int valuelen=0);

	TField * f4findfield(char *fieldname);
	void d4setbuffer(DWORD record,void *buf);
	int d4reclen();  // ���ؼ�¼����
	DWORD d4recno();  // ���ؼ�¼��
	DWORD d4reccount(); // ���ص�ǰ�����ж��ټ�¼��
	int d4b_blank(); // �ü�¼����Ϊ' '
	int d4append_blank(); // ׷��һ��' '��¼

	int d4top();
	int d4end();
	int d4next(int next=1);
	int d4go(DWORD recno);  // ��ת����¼��Ϊrecno

	int d4append(void *buf=NULL); // ׷���¼�¼�����û�ʱע�������buf����һ����¼���ݣ�buf==NULLʱ������f4b_xxx���ú�Ļ���
	int d4unrlock();  // �Ե�ǰ��¼����
	int d4rlock(); // �Ե�ǰ��¼���� �ɹ�����DBF_OK(0)
	int d4unflock(); // �Կ����
	int d4flock(); // �Կ���� �ɹ�����DBF_OK(0)
	int d4use(char *dbfname=NULL,int type=DBF_FOXBASE,int exclusive=EXCL_OFF,int access=ACCESS_RDWR);
	int d4close();
	CDBF();
	virtual ~CDBF();

   
};

   
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

#endif // !defined(AFX_DBF_H__284EC5BE_7513_469F_90AD_F867587F2973__INCLUDED_)
