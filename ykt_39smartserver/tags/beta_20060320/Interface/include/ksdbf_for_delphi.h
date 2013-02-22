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

KSDBF_API int k4_Used(int dbfhandle);  // �ж��Ƿ����ݿ��
KSDBF_API int k4_Use(int dbfhandle,char *dname,int dtype, int excl, int acce);
KSDBF_API int k4_Create(int dbfhandle,char *filename,int fields,TField *fieldlist);
KSDBF_API int k4_GetStructure(int dbfhandle,TField *fields,int *fieldno);
KSDBF_API int k4_Close(int dbfhandle);
KSDBF_API int k4_find_field(int dbfhandle,char *name);

// Ϊ��ԭ�����ϰ��:
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4close(int dbfhandle);
// ȡ�����ݿ�ļ�¼���棺
KSDBF_API BYTE *k4_d4buffer(int dbfhandle);

//���أ�(��DBF_ERRNO) DBF_OK:���ݿ�򿪳ɹ��� else ʧ��
KSDBF_API int k4_d4usefile(int dbfhandle,char *dbfname,int type,int exclusive,int access);
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4flock(int dbfhandle);  //���أ� DBF_OK: ���ɹ��� else: DBF_LOCKFAIL ��ʧ��
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4unflock(int dbfhandle); //���أ� DBF_OK: �����ɹ��� else ���Ӧ��������
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4rlock(int dbfhandle); //���أ� DBF_OK: ���ɹ��� else: DBF_LOCKFAIL ��ʧ��
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4unrlock(int dbfhandle); //���أ� DBF_OK: �����ɹ��� else ���Ӧ��������
KSDBF_API int k4_d4flush(int dbfhandle);
KSDBF_API int k4_d4append(int dbfhandle);
KSDBF_API int k4_d4b_blank(int dbfhandle);
KSDBF_API int k4_d4append_blank(int dbfhandle);

//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4go(int dbfhandle,DWORD recno);

//���أ����ݿ��ܼ�¼��
KSDBF_API DWORD k4_d4reccount(int dbfhandle);
//���أ���ǰ��¼��(0��ʧ�ܣ�>0 ʵ�ʼ�¼��)
KSDBF_API DWORD k4_d4recno(int dbfhandle);

//���ײ�Ҫ�� �����Ƿ��Ѿ�Ϊ���ݿ��ļ���
KSDBF_API int k4_d4eof(int dbfhandle);
// ���ر���׼�¼���ݳ��ȣ�������¼delete��־1BYTE��
KSDBF_API int k4_d4reclen(int dbfhandle);

//========== �Ӽ�¼�ж�ȡָ���ֶε�ֵ: ==========
//���ַ����ķ�ʽ, �г��ȵ�����

// ����ֵΪ�ֶε�����
KSDBF_API int k4_f4ncpy(int dbfhandle,char *fieldname,BYTE *str,int cnt);
// ��unsigned char *�����ֶε�ֵ
KSDBF_API BYTE *k4_f4bstr(int dbfhandle,char *fieldname);
// ��char * �����ֶε�ֵ
KSDBF_API char *k4_f4str(int dbfhandle,char *fieldname);
// ���ֶ������Ե��ֽڷ���
KSDBF_API int k4_f4char(int dbfhandle,char *fieldname);
// �Գ����ͷ���
KSDBF_API long k4_f4long(int dbfhandle,char *fieldname);
// �����ͷ��أ���windows�к��ϱ�һ����
KSDBF_API int k4_f4int(int dbfhandle,char *fieldname);
// ��double�����ֶε�ֵ
KSDBF_API double k4_f4double(int dbfhandle,char *fieldname);

//========= ��¼�ڴ��е����ݲ���:
// ��������¼���ֶ�����������ɺ�, 
// ����Ӧʹ��d4putrec(void) �� d4append(void)
// ��С��ʹ�����и�����:

//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_f4b_str(int dbfhandle,char *fieldname,void *str);
KSDBF_API int k4_f4b_long(int dbfhandle,char *fieldname,long l);
KSDBF_API int k4_f4b_double(int dbfhandle,char *fieldname,double d);
KSDBF_API int k4_f4b_char(int dbfhandle,char *fieldname,char c);
KSDBF_API int k4_d4putrec(int dbfhandle);

// �����ݿ���һ�ζ�ȡ������¼,Ȼ����d4setbuffer��f4***�����������
// �������ڿ��ٴ������ݿ�����ʱʹ��
// ���ض����ļ�¼��
KSDBF_API int k4_d4readrecords(int dbfhandle,DWORD from,int records,void *buf);
// ����¼��������������Ϊrecbuf
KSDBF_API void k4_d4setbuffer(int dbfhandle,DWORD record,void *recbuf);
// ���Ƽ�¼���������ݵ�dest
KSDBF_API void k4_d4getbuffer(int dbfhandle,char *dest);
// һ��д�������¼����
KSDBF_API int k4_d4writerecords(int dbfhandle,DWORD from,int records, void *buf);


// ======= �ֶ����ݵ�ֱ���滻, �����к�������ɲ�������,
// ��¼���ݲ�ͳһ, ��Ҫͨ��d4rlock(void) / d4flock(void) ������������
// ��ʹ��:
KSDBF_API int k4_f4r_str(int dbfhandle,char *fieldname, void *str);
KSDBF_API int k4_f4r_long(int dbfhandle,char *fieldname, long l);
KSDBF_API int k4_f4r_int(int dbfhandle,char *fieldname, int i);
KSDBF_API int k4_f4r_double(int dbfhandle,char *fieldname,double d);
KSDBF_API int k4_f4r_char(int dbfhandle,char *fieldname,BYTE c);


//���أ�DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4zap(int dbfhandle);
// ��Ե�ǰ��¼��ƫ��
KSDBF_API int k4_d4skip(int dbfhandle,long recs);
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4top(int dbfhandle); // ��λ�����ݿ��һ����¼
//���أ�(��DBF_ERRNO) DBF_OK:�ɹ��� else ʧ��
KSDBF_API int k4_d4bottom(int dbfhandle); // ��λ�����ݿ����һ����¼

// ======== ȡ�ֶ���Ϣ:
KSDBF_API int k4_getfieldno(int dbfhandle);
KSDBF_API int k4_getfieldname(int dbfhandle,int fn, char *fname);
KSDBF_API int k4_getfieldlen(int dbfhandle,int fn);
KSDBF_API int k4_getfieldbits(int dbfhandle,int fn);
KSDBF_API int k4_getfieldtype(int dbfhandle,int fn);


#ifdef __cplusplus
}
#endif

#endif //__KSDBF_FOR_DELPHI__
