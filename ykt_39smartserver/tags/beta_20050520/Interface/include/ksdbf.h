#ifndef _KSDBF_
#define _KSDBF_
/*
DLL��Ŀ�ģ�
   ����̬���ӿ���ҪΪ���ÿ�����Ա�����������Զ�DBF���ݿ������ȷ����������Ҫ�������˽�
   ���ӵ�DBF����ļ�������Ҳ�Ͳ���Ҫ����DBF�ļ�������ʧ��
DLL�ı�д������Ա��
   ������
�������ڣ�
   2001/3/30�� KSDBF.DLL ��һ�档���ڽ���������ݿ������ʹ�ã�Ϊ�˷�����������Աʹ�ã�
      ��ר������ġ�

ʹ��ʱע���Ҫ�㣺
1��
*/

#pragma comment(lib, "../lib/KSDBF.lib")
#pragma message("Automatically linking with KSDBF.dll")


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSDBF_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSDBF_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef KSDBF_EXPORTS
#define KSDBF_API __declspec(dllexport)
#else
#define KSDBF_API __declspec(dllimport)
#define DBFHandle CDBF
#endif

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


#define MAXFNL 80
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
#define FT_STRING   0  // Ϊ�ַ����� �� ��C��
#define FT_DOUBLE  -1  // Ϊ�������� �� ��N��
#define FT_LOGICAL -2  // Ϊ�߼����� �� ��L�� 
#define FT_MEMO    -3  // MEMO����  �� ��M��
#define FT_DATE    -4  // ��������  �� ��D��
#define FT_UNDEFINED 1  // δ������ֶ�����
#define FV_OUTREC   2   // ��¼û�ж�λ
#define FV_NOFIELD  3   // û���ҵ����ֶ�



/*
����һ�鶨��Ϊ��¼��λʱ�ȽϵıȽϷ�
*/
#define DBFCMP_LT  -2
#define DBFCMP_LE  -1
#define DBFCMP_EQ   0
#define DBFCMP_GE   1
#define DBFCMP_GT   2


#pragma pack(1)


typedef struct {
  char name[11];
  char f_type;  // 'C':char; 'N':Numeric; 'L':Logic; 'M':Memo; 'D':Date
  long address;  // never mind...
  BYTE len;
  BYTE bits;  // use only in type='N', else as 0;
} TField;


class KSDBF_API TNdx {
  int handle;
  char ndx_name[MAXFNL];
//  CDBF *dbf_head;
  TNdx *nextndx;

  DWORD rootpos;
  DWORD ffffffff;
  DWORD blocks;
  WORD  key_len;
  BYTE key_type;
  char expr[100];

  BYTE flag; /* 0 - frame, 1 - root, 2 - leaf, 3 - both */
  BYTE count; /* count for the node */
  BYTE items; /* efficient items */
  char comp;
  DWORD prev;
  DWORD next;
  char buffer[500];

  char old_keys[256];
  int  gel;
};


// This class is exported from the ksdbf.dll
class KSDBF_API CDBF {
private:
   BYTE   *buffer;
   DWORD  current_recno;

   BYTE   fvtemp[256];

   int field_no;
   TField *first;

   char   dbf_name[MAXFNL];

   int    handle;
   int    exclusive;  /* 1 -- on , 0 -- off */
   int    access;
   int    dbf_type;   

   TNdx  *ndx_ptr;

   BYTE version;
   BYTE year,month,day;
   DWORD record_no;
   WORD head_len;
   WORD record_len;
   BYTE reserved[20];

private:
   DWORD dbf_rec_pos(DWORD recno);
   int dbf_update_head();
   int SetDeleteFlag(char *dflag);
   void reopen_dbf();
   int dbf_buffer(DWORD recno,void *buf);
   int dbf_wbuffer(DWORD recno,void *buf);
   int append_buffer();
   int append_record(void *buf);


public:
   CDBF();
   ~CDBF();

   int LockRecord();
   int UnLockRecord();
   int LockFile();
   int UnLockFile();

   int Goto(DWORD recno);
   int Next(long next);
   int End();

   DWORD Recno();
   DWORD Reccount();
   
   WORD RecLength();
   int IsEOF();

   /* Return 0 -- Field is a String,
          -1 -- Double,
          -2 -- Logical,
          -3 -- Memo.
          -4 -- Date.
           2 -- Irregular record.
           3 -- Not find the field. */
   int FieldValue(char *fieldname,BYTE *fieldvalue);

   int SetField(char *fieldname,BYTE *fieldvalue);
   int PutRecord();
   int ReplaceRecord(void *buf);
   int Replace(char *fieldname,BYTE *fieldvalue);
   int DeleteRecord();
   int UnDeleteRecord();
   int IsDeleted();

   /* GEL:  -2 -- "<";
            -1 -- "<=";
            0  -- "=";
            1  -- ">=";
            2  -- ">";
      recno: from which record. 0/1 -- From Begin
      Return 0 -- Find and read.
             1 -- Not found.
            2/3 -- Fail.
   */
   int IsTrue(char *fieldname,BYTE *fieldvalue,int GEL);
   int Locate(DWORD from,char *fieldname,BYTE *fieldvalue,int GEL);
   int LocateNext(char *fieldname,BYTE *fieldvalue,int GEL);
   int ReadRecords(DWORD from,int records,void *buffer);
   int WriteRecords(DWORD from,int records,void *buffer);
   void SetBuffer(DWORD record,void *buf);
   void GetBuffer(void *buf);
   int Append();
   int AppendRecord(void *buf);
   int AppendBlank();

   int SetRecords(DWORD recno);
   int Zap();

   int Used();  // �ж��Ƿ����ݿ��
   int Use(char *dname=NULL,int dtype=DBF_FOXBASE, int excl=EXCL_OFF, int acce=ACCESS_RDWR);
   int Create(char *filename,int fields,TField *fieldlist);
   int GetStructure(TField *fields,int &fieldno);
   int Close();
   int find_field(char *name);

   // Ϊ��ԭ�����ϰ��:
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4close();
   // ȡ�����ݿ�ļ�¼���棺
   BYTE *d4buffer(void);

   //���أ�(��DBF_ERRNO) DBF_OK:���ݿ�򿪳ɹ��� else ʧ��
   int d4usefile(char *dbfname=NULL,int type=DBF_FOXBASE,int exclusive=EXCL_OFF,int access=ACCESS_RDWR);
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4flock();  //���أ� DBF_OK: ���ɹ��� else: DBF_LOCKFAIL ��ʧ��
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4unflock(); //���أ� DBF_OK: �����ɹ��� else ���Ӧ��������
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4rlock(); //���أ� DBF_OK: ���ɹ��� else: DBF_LOCKFAIL ��ʧ��
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4unrlock(); //���أ� DBF_OK: �����ɹ��� else ���Ӧ��������
   int d4flush();
   int d4append();
   int d4b_blank();
   int d4append_blank();

   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4go(DWORD recno);

   //���أ����ݿ��ܼ�¼��
   DWORD d4reccount();
   //���أ���ǰ��¼��(0��ʧ�ܣ�>0 ʵ�ʼ�¼��)
   DWORD d4recno();

   //���ײ�Ҫ�� �����Ƿ��Ѿ�Ϊ���ݿ��ļ���
   int d4eof();
   // ���ر���׼�¼���ݳ��ȣ�������¼delete��־1BYTE��
   int d4reclen();

   //========== �Ӽ�¼�ж�ȡָ���ֶε�ֵ: ==========
   //���ַ����ķ�ʽ, �г��ȵ�����

   // ����ֵΪ�ֶε�����
   int f4ncpy(char *fieldname,BYTE *str,int cnt);
   // ��unsigned char *�����ֶε�ֵ
   BYTE *f4bstr(char *fieldname);
   // ��char * �����ֶε�ֵ
   char *f4str(char *fieldname);
   // ���ֶ������Ե��ֽڷ���
   BYTE f4char(char *fieldname);
   // �Գ����ͷ���
   long f4long(char *fieldname);
   // �����ͷ��أ���windows�к��ϱ�һ����
   int f4int(char *fieldname);
   // ��double�����ֶε�ֵ
   double f4double(char *fieldname);

//========= ��¼�ڴ��е����ݲ���:
// ��������¼���ֶ�����������ɺ�, 
// ����Ӧʹ��d4putrec() �� d4append()
// ��С��ʹ�����и�����:

   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int f4b_str(char *fieldname,void *str);
   int f4b_long(char *fieldname,long l);
   int f4b_double(char *fieldname,double d);
   int f4b_char(char *fieldname,char c);
   int d4putrec(void);

   // �����ݿ���һ�ζ�ȡ������¼,Ȼ����d4setbuffer��f4***�����������
   // �������ڿ��ٴ������ݿ�����ʱʹ��
   // ���ض����ļ�¼��
   int d4readrecords(DWORD from,int records,void *buf);
   // ����¼��������������Ϊrecbuf
   void d4setbuffer(DWORD record,void *recbuf);
   // ���Ƽ�¼���������ݵ�dest
   void d4getbuffer(void *dest);
   // һ��д�������¼����
   int d4writerecords(DWORD from,int records, void *buf);


   // ======= �ֶ����ݵ�ֱ���滻, �����к�������ɲ�������,
   // ��¼���ݲ�ͳһ, ��Ҫͨ��d4rlock() / d4flock() ������������
   // ��ʹ��:
   int f4r_str(char *fieldname, void *str);
   int f4r_long(char *fieldname, long l);
   int f4r_int(char *fieldname, int i);
   int f4r_double(char *fieldname,double d);
   int f4r_char(char *fieldname,BYTE c);


   //���أ�DBF_OK:�ɹ��� else ʧ��
   int d4zap();
   // ��Ե�ǰ��¼��ƫ��
   int d4skip(long recs);
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4top(); // ��λ�����ݿ��һ����¼
   //���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
   int d4bottom(); // ��λ�����ݿ����һ����¼

   // ======== ȡ�ֶ���Ϣ:
   int getfieldname(int fn, char *fname);
   int getfieldlen(int fn);
   int getfieldbits(int fn);
   char getfieldtype(int fn);
};

#pragma pack()

KSDBF_API int IsInString(char c,char *string);

KSDBF_API void InsertC(char *string,int lp,char c);

KSDBF_API void DeleteC(char *string,int lp);

KSDBF_API void InsertCR(char *string,int rp,char c);

KSDBF_API char * LTrim(char *string);

KSDBF_API char * RTrim(char *string);

KSDBF_API char * LRTrim(char *string);

KSDBF_API void LFillC(char *buf,int len,char c);

KSDBF_API void RFillC(char *buf,int len,char c);

KSDBF_API void NumFormat(char *number,int l);


KSDBF_API char * AnalyBuffer(char *buffer,int *offset,char *notnull);


KSDBF_API int XMGetCurrentDiskInfo(DWORD *sn1,DWORD *sn2);

KSDBF_API int  XMCheckSerialNumber(char *szSerial,DWORD sn1,DWORD sn2,char *szXMKey);

/*
// This class is exported from the ksdbf.dll
class KSDBF_API CKsdbf {
public:
	CKsdbf(void);
	// TODO: add your methods here.
};

extern KSDBF_API int nKsdbf;

KSDBF_API int fnKsdbf(void);
*/

#endif