#ifndef __KSDBF_FOR_DELPHI__
#define __KSDBF_FOR_DELPHI__

#include "ksdbf.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXDBFHANDLE	256

struct DBFHANDLE {
	CDBF *handle;
};

KSDBF_API int k4_init(void);
KSDBF_API void k4_shut(void);
KSDBF_API int k4_alloc_dbfhandle(void);
KSDBF_API void k4_release_dbfhandle(int dbfhandle);

KSDBF_API int k4_LockRecord(int dbfhandle);
KSDBF_API int k4_UnLockRecord(int dbfhandle);
KSDBF_API int k4_LockFile(int dbfhandle);
KSDBF_API int k4_UnLockFile(int dbfhandle);

KSDBF_API int k4_Goto(int dbfhandle,DWORD recno);
KSDBF_API int k4_Next(int dbfhandle,long next);
KSDBF_API int k4_End(int dbfhandle);

KSDBF_API DWORD k4_Recno(int dbfhandle);
KSDBF_API DWORD k4_Reccount(int dbfhandle);

KSDBF_API int k4_RecLength(int dbfhandle);
KSDBF_API int k4_IsEOF(int dbfhandle);

/* Return 0 -- Field is a String,
  -1 -- Double,
  -2 -- Logical,
  -3 -- Memo.
  -4 -- Date.
   2 -- Irregular record.
   3 -- Not find the field. */
KSDBF_API int k4_FieldValue(int dbfhandle,char *fieldname,BYTE *fieldvalue);

KSDBF_API int k4_SetField(int dbfhandle,char *fieldname,BYTE *fieldvalue);
KSDBF_API int k4_PutRecord(int dbfhandle);
KSDBF_API int k4_ReplaceRecord(int dbfhandle,char *buf);
KSDBF_API int k4_Replace(int dbfhandle,char *fieldname,BYTE *fieldvalue);
KSDBF_API int k4_DeleteRecord(int dbfhandle);
KSDBF_API int k4_UnDeleteRecord(int dbfhandle);
KSDBF_API int k4_IsDeleted(int dbfhandle);

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
KSDBF_API int k4_IsTrue(int dbfhandle,char *fieldname,BYTE *fieldvalue,int GEL);
KSDBF_API int k4_Locate(int dbfhandle,DWORD from,char *fieldname,BYTE *fieldvalue,int GEL);
KSDBF_API int k4_LocateNext(int dbfhandle,char *fieldname,BYTE *fieldvalue,int GEL);
KSDBF_API int k4_ReadRecords(int dbfhandle,DWORD from,int records,void *buffer);
KSDBF_API int k4_WriteRecords(int dbfhandle,DWORD from,int records,void *buffer);
KSDBF_API void k4_SetBuffer(int dbfhandle,DWORD record,void *buf);
KSDBF_API void k4_GetBuffer(int dbfhandle,char *buf);
KSDBF_API int k4_Append(int dbfhandle);
KSDBF_API int k4_AppendRecord(int dbfhandle,char *buf);
KSDBF_API int k4_AppendBlank(int dbfhandle);

KSDBF_API int k4_SetRecords(int dbfhandle,DWORD recno);
KSDBF_API int k4_Zap(int dbfhandle);

KSDBF_API int k4_Used(int dbfhandle);  // 判断是否数据库打开
KSDBF_API int k4_Use(int dbfhandle,char *dname,int dtype, int excl, int acce);
KSDBF_API int k4_Create(int dbfhandle,char *filename,int fields,TField *fieldlist);
KSDBF_API int k4_GetStructure(int dbfhandle,TField *fields,int *fieldno);
KSDBF_API int k4_Close(int dbfhandle);
KSDBF_API int k4_find_field(int dbfhandle,char *name);

// 为了原来编程习惯:
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4close(int dbfhandle);
// 取得数据库的记录缓存：
KSDBF_API BYTE *k4_d4buffer(int dbfhandle);

//返回：(见DBF_ERRNO) DBF_OK:数据库打开成功； else 失败
KSDBF_API int k4_d4usefile(int dbfhandle,char *dbfname,int type,int exclusive,int access);
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4flock(int dbfhandle);  //返回： DBF_OK: 锁成功； else: DBF_LOCKFAIL 锁失败
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4unflock(int dbfhandle); //返回： DBF_OK: 解锁成功； else 编程应该有问题
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4rlock(int dbfhandle); //返回： DBF_OK: 锁成功； else: DBF_LOCKFAIL 锁失败
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4unrlock(int dbfhandle); //返回： DBF_OK: 解锁成功； else 编程应该有问题
KSDBF_API int k4_d4flush(int dbfhandle);
KSDBF_API int k4_d4append(int dbfhandle);
KSDBF_API int k4_d4b_blank(int dbfhandle);
KSDBF_API int k4_d4append_blank(int dbfhandle);

//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4go(int dbfhandle,DWORD recno);

//返回：数据库总记录数
KSDBF_API DWORD k4_d4reccount(int dbfhandle);
//返回：当前记录号(0－失败，>0 实际记录号)
KSDBF_API DWORD k4_d4recno(int dbfhandle);

//轻易不要用 返回是否已经为数据库文件底
KSDBF_API int k4_d4eof(int dbfhandle);
// 返回本库底记录数据长度（包括记录delete标志1BYTE）
KSDBF_API int k4_d4reclen(int dbfhandle);

//========== 从记录中读取指定字段的值: ==========
//以字符串的方式, 有长度的限制

// 返回值为字段的类型
KSDBF_API int k4_f4ncpy(int dbfhandle,char *fieldname,BYTE *str,int cnt);
// 以unsigned char *返回字段的值
KSDBF_API BYTE *k4_f4bstr(int dbfhandle,char *fieldname);
// 以char * 返回字段的值
KSDBF_API char *k4_f4str(int dbfhandle,char *fieldname);
// 将字段内容以单字节返回
KSDBF_API int k4_f4char(int dbfhandle,char *fieldname);
// 以长整型返回
KSDBF_API long k4_f4long(int dbfhandle,char *fieldname);
// 以整型返回（在windows中和上边一样）
KSDBF_API int k4_f4int(int dbfhandle,char *fieldname);
// 以double返回字段的值
KSDBF_API double k4_f4double(int dbfhandle,char *fieldname);

//========= 记录内存中的数据操作:
// 在完整记录各字段数据设置完成后, 
// 正常应使用d4putrec(void) 或 d4append(void)
// 请小心使用下列各函数:

//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_f4b_str(int dbfhandle,char *fieldname,void *str);
KSDBF_API int k4_f4b_long(int dbfhandle,char *fieldname,long l);
KSDBF_API int k4_f4b_double(int dbfhandle,char *fieldname,double d);
KSDBF_API int k4_f4b_char(int dbfhandle,char *fieldname,char c);
KSDBF_API int k4_d4putrec(int dbfhandle);

// 从数据库中一次读取多条记录,然后用d4setbuffer和f4***函数浏览数据
// 常常用于快速处理数据库数据时使用
// 返回读到的记录数
KSDBF_API int k4_d4readrecords(int dbfhandle,DWORD from,int records,void *buf);
// 将记录缓冲区内容设置为recbuf
KSDBF_API void k4_d4setbuffer(int dbfhandle,DWORD record,void *recbuf);
// 复制记录缓冲区内容到dest
KSDBF_API void k4_d4getbuffer(int dbfhandle,char *dest);
// 一次写入多条记录数据
KSDBF_API int k4_d4writerecords(int dbfhandle,DWORD from,int records, void *buf);


// ======= 字段数据的直接替换, 用下列函数会造成操作过慢,
// 记录数据不统一, 需要通过d4rlock(void) / d4flock(void) 共享锁操作后
// 再使用:
KSDBF_API int k4_f4r_str(int dbfhandle,char *fieldname, void *str);
KSDBF_API int k4_f4r_long(int dbfhandle,char *fieldname, long l);
KSDBF_API int k4_f4r_int(int dbfhandle,char *fieldname, int i);
KSDBF_API int k4_f4r_double(int dbfhandle,char *fieldname,double d);
KSDBF_API int k4_f4r_char(int dbfhandle,char *fieldname,BYTE c);


//返回：DBF_OK:成功； else 失败
KSDBF_API int k4_d4zap(int dbfhandle);
// 相对当前记录的偏移
KSDBF_API int k4_d4skip(int dbfhandle,long recs);
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4top(int dbfhandle); // 定位到数据库第一条记录
//返回：(见DBF_ERRNO) DBF_OK:成功； else 失败
KSDBF_API int k4_d4bottom(int dbfhandle); // 定位到数据库最后一条记录

// ======== 取字段信息:
KSDBF_API int k4_getfieldno(int dbfhandle);
KSDBF_API int k4_getfieldname(int dbfhandle,int fn, char *fname);
KSDBF_API int k4_getfieldlen(int dbfhandle,int fn);
KSDBF_API int k4_getfieldbits(int dbfhandle,int fn);
KSDBF_API int k4_getfieldtype(int dbfhandle,int fn);


#ifdef __cplusplus
}
#endif

#endif //__KSDBF_FOR_DELPHI__
