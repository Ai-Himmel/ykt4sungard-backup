#ifndef _KSDBF_
#define _KSDBF_
/*
DLL的目的：
   本动态连接库主要为了让开发人员利用它，可以对DBF数据库进行正确操作，不需要再深入了解
   复杂的DBF库的文件操作。也就不需要担心DBF文件操作的失误。
DLL的编写整理人员：
   陈永华
整理日期：
   2001/3/30： KSDBF.DLL 第一版。基于近八年的数据库操作的使用，为了方便其他程序员使用，
      而专门整理的。

使用时注意的要点：
1。
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
下列定义数据库文件打开时的共享模式：
EXCL_ON -- 独占打开， 这样其他用户就无法打开，连自己的另外一个进程也不能打开了
EXCL_OFF -- 共享打开， 成功后，其他用户还可以利用本方式打开，如FOX中
         :set excl off
         :use xxxx
         就能够成功打开
*/
#define EXCL_ON  1
#define EXCL_OFF 0

/*
下列定义数据库文件的类型，主要不同在于和其他系统共享数据库时加锁的兼容性
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
下列定义数据库文件打开时是
      只读打开（ACCESS_RDONLY），还是
      读写打开（ACCESS_RDWR）
*/
#define ACCESS_RDONLY  0
#define ACCESS_RDWR    1


#define MAXFNL 80
#define MAXLEVELS 6

/*
DBF_ERRNO: 为大部分数据库函数操作返回值
*/
enum DBF_ERRNO {
   DBF_OK = 0,
   DBF_HEADERR,  // 不正确的数据库头
   DBF_NOMEM,    // 没有足够的内存
   DBF_OPENFAIL, // 库文件打开失败, 如共享打开失败 或 独占打开失败, 或不存在该文件等
   DBF_RECNOERR, // 函数调用时,记录号不正确, 如记录号<1
   DBF_RECNO_OF, // 记录号不正确, 记录号超过总的记录条数
   DBF_RECLOCFAIL, // 记录定位失败, _lseek failure
   DBF_READFAIL, // 记录数据读取失败
   DBF_LOCKFAIL, // 数据库加锁或解锁失败
   DBF_WRITEFAIL, // 记录数据写入失败
   DBF_EOF,       // 不能定位,
   DBF_USED       // 数据库正常打开
};

/*
下面一组定义为字段类型和错误的类型
*/
#define FT_STRING   0  // 为字符类型 即 ‘C’
#define FT_DOUBLE  -1  // 为数字类型 即 ‘N’
#define FT_LOGICAL -2  // 为逻辑类型 即 ‘L’ 
#define FT_MEMO    -3  // MEMO类型  即 ‘M’
#define FT_DATE    -4  // 日期类型  即 ‘D’
#define FT_UNDEFINED 1  // 未定义的字段类型
#define FV_OUTREC   2   // 记录没有定位
#define FV_NOFIELD  3   // 没有找到该字段



/*
下面一组定义为记录定位时比较的比较符
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

   int Used();  // 判断是否数据库打开
   int Use(char *dname=NULL,int dtype=DBF_FOXBASE, int excl=EXCL_OFF, int acce=ACCESS_RDWR);
   int Create(char *filename,int fields,TField *fieldlist);
   int GetStructure(TField *fields,int &fieldno);
   int Close();
   int find_field(char *name);

   // 为了原来编程习惯:
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4close();
   // 取得数据库的记录缓存：
   BYTE *d4buffer(void);

   //返回：(见DBF_ERRNO) DBF_OK:数据库打开成功； else 失败
   int d4usefile(char *dbfname=NULL,int type=DBF_FOXBASE,int exclusive=EXCL_OFF,int access=ACCESS_RDWR);
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4flock();  //返回： DBF_OK: 锁成功； else: DBF_LOCKFAIL 锁失败
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4unflock(); //返回： DBF_OK: 解锁成功； else 编程应该有问题
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4rlock(); //返回： DBF_OK: 锁成功； else: DBF_LOCKFAIL 锁失败
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4unrlock(); //返回： DBF_OK: 解锁成功； else 编程应该有问题
   int d4flush();
   int d4append();
   int d4b_blank();
   int d4append_blank();

   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4go(DWORD recno);

   //返回：数据库总记录数
   DWORD d4reccount();
   //返回：当前记录号(0－失败，>0 实际记录号)
   DWORD d4recno();

   //轻易不要用 返回是否已经为数据库文件底
   int d4eof();
   // 返回本库底记录数据长度（包括记录delete标志1BYTE）
   int d4reclen();

   //========== 从记录中读取指定字段的值: ==========
   //以字符串的方式, 有长度的限制

   // 返回值为字段的类型
   int f4ncpy(char *fieldname,BYTE *str,int cnt);
   // 以unsigned char *返回字段的值
   BYTE *f4bstr(char *fieldname);
   // 以char * 返回字段的值
   char *f4str(char *fieldname);
   // 将字段内容以单字节返回
   BYTE f4char(char *fieldname);
   // 以长整型返回
   long f4long(char *fieldname);
   // 以整型返回（在windows中和上边一样）
   int f4int(char *fieldname);
   // 以double返回字段的值
   double f4double(char *fieldname);

//========= 记录内存中的数据操作:
// 在完整记录各字段数据设置完成后, 
// 正常应使用d4putrec() 或 d4append()
// 请小心使用下列各函数:

   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int f4b_str(char *fieldname,void *str);
   int f4b_long(char *fieldname,long l);
   int f4b_double(char *fieldname,double d);
   int f4b_char(char *fieldname,char c);
   int d4putrec(void);

   // 从数据库中一次读取多条记录,然后用d4setbuffer和f4***函数浏览数据
   // 常常用于快速处理数据库数据时使用
   // 返回读到的记录数
   int d4readrecords(DWORD from,int records,void *buf);
   // 将记录缓冲区内容设置为recbuf
   void d4setbuffer(DWORD record,void *recbuf);
   // 复制记录缓冲区内容到dest
   void d4getbuffer(void *dest);
   // 一次写入多条记录数据
   int d4writerecords(DWORD from,int records, void *buf);


   // ======= 字段数据的直接替换, 用下列函数会造成操作过慢,
   // 记录数据不统一, 需要通过d4rlock() / d4flock() 共享锁操作后
   // 再使用:
   int f4r_str(char *fieldname, void *str);
   int f4r_long(char *fieldname, long l);
   int f4r_int(char *fieldname, int i);
   int f4r_double(char *fieldname,double d);
   int f4r_char(char *fieldname,BYTE c);


   //返回：DBF_OK:成功； else 失败
   int d4zap();
   // 相对当前记录的偏移
   int d4skip(long recs);
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4top(); // 定位到数据库第一条记录
   //返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
   int d4bottom(); // 定位到数据库最后一条记录

   // ======== 取字段信息:
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