// DBF.h: interface for the CDBF class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBF_H__284EC5BE_7513_469F_90AD_F867587F2973__INCLUDED_)
#define AFX_DBF_H__284EC5BE_7513_469F_90AD_F867587F2973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
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


#define MAXFNL 256
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


#define FT_STRING   'C'  // 为字符类型 即 ‘C’
#define FT_DOUBLE   'N'  // 为数字类型 即 ‘N’
#define FT_LOGICAL  'L'  // 为逻辑类型 即 ‘L’ 
#define FT_MEMO     'M' // MEMO类型  即 ‘M’
#define FT_DATE     'D' // 日期类型  即 ‘D’
#define FT_BINARY   'X' // 二进制类型 即 ‘X’ 本系统独有的类型，用于存放特殊的数据，最大长度和F_WORDLEN有关
#define FT_UNDEFINED 0xFF  // 未定义的字段类型
#define FV_OUTREC    0xFE   // 记录没有定位
#define FV_NOFIELD   0xFD   // 没有找到该字段



/*
下面一组定义为记录定位时比较的比较符
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


/* 以下代码是用来字节对齐使用的 */
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

   // 函数名: f4r_field
   // 编程  : 陈永华 2003-10-10 12:24:16
   // 描述  : 只是用fieldbuf修改当前记录的指定的字段值，并写入到DBF中
   // 返回  : int 写入的长度（==0出错，>0一般是对的）
   // 参数  : char *fieldname
   // 参数  : void *fieldbuf
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

   // 以下两个专门针对‘X’－ 二进制类型字段操作
	int f4binary(char *fieldname,void *value,int valuesize);
	int f4b_binary(char *fieldname,void *bin,int blen);


   // f4b_xx 用于非'X'类的缓冲写，最后必须用d4putrec()或d4append()才真正写入到DBF库中
	int f4b_char(char *fieldname,char c);
	int f4b_double(char *fieldname,double data);
	int f4b_int(char *fieldname,int data);
	int f4b_str(char *fieldname,char *fvalue);

   // f4xxxx如下为读取字段中的数据，注意字段类型为'X'可能处理和常规的不同，应用f4binary(...)
	int f4ncpy(char *fieldname,void *value,int vlen);
	long f4long(char *fieldname);
	int f4int(char *fieldname);
	char * f4str(char *fieldname);
	double f4double(char *fieldname);
	char f4char(char *fieldname);
	void * f4bstr(char *fieldname);
	
   int f4setvalue(char *fieldname,void *value);

   // 以字段内容的原值存放在value返回，返回为相应的字段定义
	TField * f4getvalue(char *fieldname,void *value,int valuelen=0);

	TField * f4findfield(char *fieldname);
	void d4setbuffer(DWORD record,void *buf);
	int d4reclen();  // 返回记录长度
	DWORD d4recno();  // 返回记录号
	DWORD d4reccount(); // 返回当前库中有多少记录数
	int d4b_blank(); // 置记录缓冲为' '
	int d4append_blank(); // 追加一条' '记录

	int d4top();
	int d4end();
	int d4next(int next=1);
	int d4go(DWORD recno);  // 跳转到记录号为recno

	int d4append(void *buf=NULL); // 追加新记录，多用户时注意加锁，buf当做一条记录内容，buf==NULL时，则用f4b_xxx设置后的缓冲
	int d4unrlock();  // 对当前记录解锁
	int d4rlock(); // 对当前记录加锁 成功返回DBF_OK(0)
	int d4unflock(); // 对库解锁
	int d4flock(); // 对库加锁 成功返回DBF_OK(0)
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
