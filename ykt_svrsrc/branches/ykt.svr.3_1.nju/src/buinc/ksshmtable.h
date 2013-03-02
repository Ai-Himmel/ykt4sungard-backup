/********************************************************************
	created:	2005/11/24
	created:	24:11:2005   9:39
	filename: 	D:\proj\ksbass\ksshmtable\ksshmtable.h
	file path:	D:\proj\ksbass\ksshmtable
	file base:	ksshmtable
	file ext:	h
	author:		CHENYH
	
	purpose:	 Ϊ���ܹ��ṩ��ESQL-C������ã��ر��ȡ����һ��C���ýӿ�

   ����������  tableid: 0-99; idxid: 0-9 (ÿ����Ψһ����ͬ���ֵ������ͬ)��
            keylength: ����ΪSHT_KEYTYPES�ж���ģ�����Ϊ>0��ʾ�Ĺؼ��ֳ���
*********************************************************************/
#ifndef _KSSHMTABLE_
#define _KSSHMTABLE_

#ifndef SMT_IN_ONE
#define SMT_IN_ONE
#endif

typedef void * CURSORHANDLE;        // ���¼��ѯʱ����α���

typedef void * SMTABLEHANDLE;       // �����ڴ��ľ��

#ifdef WIN32
typedef __int64 Int64;
#else
typedef long long Int64;
#endif


#ifdef KSSHMT_EXPORTS
#define KSSHMT_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define KSSHMT_API __declspec(dllimport)
#else
#define KSSHMT_API 
#endif
#endif


enum SHTCMP_TYPES       // ���ݱȽϵ�ʱ��ıȽϷ�
{
   SHTCT_L,
   SHTCT_LE,
   SHTCT_E,
   SHTCT_GE,
   SHTCT_G
};

enum SHT_KEYTYPES       // �����ؼ��ֵ����ͣ����Ϊ���ڴ����ݻ��ַ����Ƚϣ�����>0�ĳ���ֵ
{
   SHTKT_INT32 = -1,
   SHTKT_INT64 = -2,
   SHTKT_FLOAT = -3,
   SHTKT_DOUBLE = -4,
   SHTKT_UINT32 = -5
};

#define SHTABLE_KEYID   28


typedef  struct {
   int  m_tableid;      // ��ID
   int  m_idxcnt;       // �����ݱ��ڰ������ٸ�����
	int  m_reccnt;       // ʵ������
	int  m_maxrecs;      // ����������
	int  m_recsize;      // ��¼��С (ԭʼ��¼����)
   int  m_unitsize;     // ��¼�����ĳ���(�ֽ���)
   int  m_firstfree;    // ��һ������Record�ı��
   int  m_firstdata;    // ��һ����Ч���ݿ��
   int  m_lastdata;     // ���һ����Ч���ݿ��
} sH_TABLEHEAD;

#ifdef  __cplusplus
extern "C" {
#else
#ifndef true
#define __true__
typedef unsigned char bool;
#define true  1
#define false 0
#endif
#endif
   
#ifdef SMT_IN_ONE   // �������һ��ϵͳ�еĹ����ڴ��ֻ��һ�������ڴ�飬����Ҫ���º�����
typedef struct  
{
   unsigned int maxrecs;
   unsigned int recsize;
   int   idxcnt;
} T_TABLEINFO;

KSSHMT_API bool INITSMT(const char *SMTName, int tablecnt, T_TABLEINFO *tableinfo);

KSSHMT_API void EXITSMT();
KSSHMT_API void REMOVESMT(const char *SMTName);   // �������ڴ���ϵͳ�г������

// ������: SMTCreate
// ���  : ������ 2005-11-24 18:13:57
// ����  : Ϊһ�������ڴ����ݱ���һ�������ڴ��
// ����  : SMTABLEHANDLE �� ���ش����ɹ����ڴ������ʧ���򷵻�NULL���μ�eMsg�е���Ϣ
// ����  : int tableid [IN]: �����ID (��0��ʼ������Ϊ99) �μ�INITSMT�е�tableinfo�е����
// ����  : unsigned int maxrecs [IN]: �����ڴ�����ɴ�ż�¼��
// ����  : unsigned int recsize [IN]: һ����¼�ĳ����ֽ���
// ����  : int idxcnt [IN]: ��������н�������ٸ�������
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API SMTABLEHANDLE SMTCreate(int tableid, unsigned int maxrecs, unsigned int recsize, int idxcnt, char *eMsg);


// ������: SMTOpen
// ���  : ������ 2005-11-24 18:17:21
// ����  : ��һ���Ѿ��������˵Ĺ����ڴ��
// ����  : SMTABLEHANDLE : ���ش򿪳ɹ��Ĺ����ľ����==NULL: ʧ�ܣ��μ�eMsg�е���Ϣ
// ����  : int tableid [IN]: �����ID (��0��ʼ������Ϊ99) �μ�INITSMT�е�tableinfo�е����
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API SMTABLEHANDLE SMTOpen(int tableid, char *eMsg);

#else

// ������: SMTCreate
// ���  : ������ 2005-11-24 18:13:57
// ����  : Ϊһ�������ڴ����ݱ���һ�������ڴ��
// ����  : SMTABLEHANDLE �� ���ش����ɹ����ڴ������ʧ���򷵻�NULL���μ�eMsg�е���Ϣ
// ����  : const char *tablename  [IN]: ��������ƣ�Ҳ�ǹ�����Ӧ���ļ�
// ����  : int tableid [IN]: �����ID (��0��ʼ������Ϊ99)
// ����  : unsigned int maxrecs [IN]: �����ڴ�����ɴ�ż�¼��
// ����  : unsigned int recsize [IN]: һ����¼�ĳ����ֽ���
// ����  : int idxcnt [IN]: ��������н�������ٸ�������
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API SMTABLEHANDLE SMTCreate(const char *tablename, int tableid, unsigned int maxrecs, unsigned int recsize, int idxcnt, char *eMsg);


// ������: SMTOpen
// ���  : ������ 2005-11-24 18:17:21
// ����  : ��һ���Ѿ��������˵Ĺ����ڴ��
// ����  : SMTABLEHANDLE : ���ش򿪳ɹ��Ĺ����ľ����==NULL: ʧ�ܣ��μ�eMsg�е���Ϣ
// ����  : const char *tablename  [IN]: ��������ƣ�Ҳ�ǹ�����Ӧ���ļ�
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API SMTABLEHANDLE SMTOpen(const char *tablename, char *eMsg);
#endif


// ������: EmulateSizeOfSMT
// ���  : ������ 2005-11-24 18:11:42
// ����  : ���ڹ��㽨��һ�������ڴ����Ҫ�Ĺ����ڴ�ռ�
// ����  : unsigned int ����Ҫ�Ĺ����ڴ�ռ���ֽ���
// ����  : unsigned int maxrecs [IN]: �����ڴ�����ɴ�ż�¼��
// ����  : unsigned int recsize [IN]: һ����¼�ĳ����ֽ���
// ����  : int idxcnt [IN]: ��������н�������ٸ�������
KSSHMT_API unsigned int EmulateSizeOfSMT(unsigned int maxrecs, unsigned int recsize, int idxcnt);


// ������: SMTCreateIndex
// ���  : ������ 2005-11-24 18:19:29
// ����  : ��һ�������ڴ���д���һ������
// ����  : bool �������Ƿ�ɹ�������������false(0): ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int idxid [IN]: ���屾������ID����0��ʼ��9��һ����������ظ�����ͬ��֮���޹�
// ����  : unsigned int keyoffset [IN]: �����ؼ��������ڼ�¼�е�ƫ��λ��
// ����  : int keytype_len [IN]: �����ؼ��ֵ����ͣ��ο�SHT_KEYTYPES�����Ϊ���ڴ����ݻ��ַ����Ƚϣ�����>0�ĳ���ֵ
// ����  : int uniquekey [IN]: �������Ƿ�Ϊunique index��0 - ���ǣ��ؼ��ֿ��ظ���1 - �ǣ��ؼ��ֲ������ظ� 
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTCreateIndex(SMTABLEHANDLE SMTHandle,int idxid, unsigned int keyoffset, int keytype_len, int uniquekey, char *eMsg);


// ������: SMTClose
// ���  : ������ 2005-11-24 18:24:36
// ����  : �ر�һ�������ڴ���������ڴ�û�б�ժ��
// ����  : void 
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
KSSHMT_API void SMTClose(SMTABLEHANDLE SMTHandle);


// ������: SMTInsert
// ���  : ������ 2005-11-24 18:26:00
// ����  : ��һ����¼���뵽ָ���Ĺ����ڴ��
// ����  : int  ���ز����¼��DATAID��>=0:�ɹ���<0:ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : void *recdata [IN]: һ�������ļ�¼����
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int  SMTInsert(SMTABLEHANDLE SMTHandle, void *recdata, char *eMsg);


// ������: SMTUpdate
// ���  : ������ 2005-11-24 18:28:53
// ����  : �޸�һ��ָ��DATAID�ļ�¼����
// ����  : bool �������Ƿ�ɹ���0-ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int dataid [IN]: ָ����¼��DATAID
// ����  : void *recdata [IN]: һ�������ļ�¼����
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTUpdate(SMTABLEHANDLE SMTHandle, int dataid,void *recdata, char *eMsg);


// ������: SMTDelete
// ���  : ������ 2005-11-25 10:53:30
// ����  : �ӹ����ڴ����ɾ��ָ����һ����¼����
// ����  : bool �������Ƿ�ɹ��� 0-ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int dataid [IN]: ָ����¼��DATAID
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTDelete(SMTABLEHANDLE SMTHandle, int dataid, char *eMsg);


// ������: SMTGetRecord
// ���  : ������ 2005-11-25 10:54:49
// ����  : ��ָ��λ��dataid�У���ȡ�����¼���ݣ������ģ�
// ����  : bool �������Ƿ�ɹ��� 0-ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int dataid [IN]: ָ����¼��DATAID
// ����  : void *recdata [OUT]: ��Ŷ�ȡ��������¼���ݵĻ���
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTGetRecord(SMTABLEHANDLE SMTHandle, int dataid,void *recdata, char *eMsg);


// ������: SMTGetFirstDataID
// ���  : ������ 2005-11-25 10:56:33
// ����  : ��ȡָ�������ڴ����׼�¼��DATAID
// ����  : int �������׼�¼��DATAID��<0: ʧ�ܣ�������Ϊ�޼�¼����
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int SMTGetFirstDataID(SMTABLEHANDLE SMTHandle, char *eMsg);


// ������: SMTGetNextDataID
// ���  : ������ 2005-11-25 11:10:53
// ����  : ��ȡ�����ڴ���е���Ե�ǰ����һ����¼��DATAID
// ����  : int ��������һ����¼��DATAID��<0: ʧ�ܣ�������Ϊû�к���ļ�¼����
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int cur_dataid [IN]: ��ǰ��¼��DATAID
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int SMTGetNextDataID(SMTABLEHANDLE SMTHandle, int cur_dataid, char *eMsg);


// ������: SMTGetRecordCount
// ���  : ������ 2005-11-25 11:12:56
// ����  : ȡָ�������ڴ���ڵļ�¼��
// ����  : int �����ع����ڴ���еļ�¼��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int SMTGetRecordCount(SMTABLEHANDLE SMTHandle, char *eMsg);


// ������: SMTIndexSeek
// ���  : ������ 2005-11-25 11:13:52
// ����  : ���������ҵ�һ�����ϱ����������ļ�¼��������DATAID
// ����  : int �����ط��������ļ�¼DATAID��<0: û���ҵ�����������
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int idxid [IN]: �Ѿ�������������
// ����  : void *key [IN]: ���ڱȽϵĹؼ�������
// ����  : int cmp_oper [IN]: �Ƚϵ����ͣ��ο�SHTCMP_TYPES�е��嵥
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int SMTIndexSeek(SMTABLEHANDLE SMTHandle, int idxid, void *key, int cmp_oper, char *eMsg);



// ������: SMTSelectFirst
// ���  : ������ 2005-11-29 11:35:38
// ����  : ȫ����ҵ�һ�����ϱ������ļ�¼��������DATAID
// ����  : int �����ط��������ļ�¼DATAID��<0: û���ҵ�����������
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : void *cmpdata [IN]: �Ƚ����ݵ�ָ�룬NULL���������׼�¼
// ����  : int cmp_oper [IN]: �Ƚϵ����ͣ��ο�SHTCMP_TYPES�е��嵥
// ����  : int cd_offset [IN]: �Ƚ������ڼ�¼�е�ƫ��λ��
// ����  : int type_len [IN]: �Ƚ����ݲ������ͣ��ο�SHT_KEYTYPES�����Ϊ���ڴ����ݻ��ַ����Ƚϣ�����>0�ĳ���ֵ
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int SMTSelectFirst(SMTABLEHANDLE SMTHandle, void *cmpdata, int cmp_oper,int cd_offset,int type_len, char *eMsg);


// ������: SMTIsOpen
// ���  : ������ 2005-11-25 11:18:48
// ����  : ��鱾�����ڴ���Ƿ��������ˣ�Ҳ���ڸ����ݲ����Ƿ�����һ���Ϸ��Ĺ����ڴ���
// ����  : bool �������Ƿ�Ϊ���˵Ĺ����ڴ���
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTIsOpen(SMTABLEHANDLE SMTHandle, char *eMsg);


// ������: SMTIsValidRecord
// ���  : ������ 2005-11-25 11:21:04
// ����  : ���ָ����dataid�Ƿ�Ϊ�������ڴ���е���Ч��¼���ݵ�DATAID
// ����  : bool �������Ƿ�Ϊ��Ч��DATAID
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int dataid [IN]: ָ����¼��DATAID
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTIsValidRecord(SMTABLEHANDLE SMTHandle, int dataid, char *eMsg);


// ������: SMTLock
// ���  : ������ 2005-11-25 11:22:32
// ����  : �Թ����ڴ�����
// ����  : bool �������Ƿ�����ɹ�
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : bool bWait [IN]: �Ƿ���õȴ�����false(0): ��������״̬
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTLock(SMTABLEHANDLE SMTHandle, bool bWait, char *eMsg);


// ������: SMTUnlock
// ���  : ������ 2005-11-25 11:24:10
// ����  : �Թ����ڴ�����
// ����  : bool �������Ƿ�����ɹ�
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTUnlock(SMTABLEHANDLE SMTHandle, char *eMsg);


// ������: SMTCursorIndexOpen
// ���  : ������ 2005-11-25 11:24:58
// ����  : �򿪸���������ʽ������һ����ѯ�α�
// ����  : CURSORHANDLE �����ظò�ѯ�α�ľ����==NULL:ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int idxid [IN]: �Ѿ�������������
// ����  : void *key [IN]: ���ڱȽϵĹؼ�������
// ����  : int cmp_oper [IN]: �Ƚϵ����ͣ��ο�SHTCMP_TYPES�е��嵥
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API CURSORHANDLE SMTCursorIndexOpen(SMTABLEHANDLE SMTHandle, int idxid, void *key, int cmp_oper, char *eMsg);


// ������: SMTCursorOpen
// ���  : ������ 2005-11-25 11:26:51
// ����  : ��һ��ȫ������Ĳ�ѯ�α�
// ����  : CURSORHANDLE �����ظò�ѯ�α�ľ����==NULL:ʧ��
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : void *cmpdata [IN]: ���ڱȽϵ�����
// ����  : int cmp_oper [IN]: �Ƚϵ����ͣ��ο�SHTCMP_TYPES�е��嵥
// ����  : int cd_offset [IN]: �Ƚ������ڼ�¼�е�ƫ��λ��
// ����  : int cd_type_len [IN]: �Ƚ����ݲ������ͣ��ο�SHT_KEYTYPES�����Ϊ���ڴ����ݻ��ַ����Ƚϣ�����>0�ĳ���ֵ
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API CURSORHANDLE SMTCursorOpen(SMTABLEHANDLE SMTHandle, void *cmpdata, int cmp_oper, int cd_offset, int cd_type_len, char *eMsg);


// ������: SMTCursorDestroy
// ���  : ������ 2005-11-25 11:29:49
// ����  : �ر��Ѿ��򿪵Ĳ�ѯ�α�
// ����  : bool �������Ƿ�ɹ���false��������Ϊ�α�����Ч
// ����  : CURSORHANDLE csrhandle [IN]: Ҫ�رյĲ�ѯ�α���
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTCursorDestroy(CURSORHANDLE csrhandle, char *eMsg);


// ������: SMTCursorSize
// ���  : ������ 2005-11-25 11:31:42
// ����  : ȡ�Ѿ��򿪵��α����У�һ���ж�����Ч��¼��
// ����  : int ��������Ч��¼��
// ����  : CURSORHANDLE csrhandle [IN]: ָ���Ĳ�ѯ�α���
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API int SMTCursorSize(CURSORHANDLE csrhandle, char *eMsg);


// ������: SMTCursorFetch
// ���  : ������ 2005-11-25 11:32:53
// ����  : ��ȡ��ǰλ�õ��α��еļ�¼���ݣ����α�ոմ򿪵�ʱ�򣬼�Ϊ�α��е��׼�¼
// ����  : bool ����¼���ݶ�ȡ�Ƿ�ɹ�
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : CURSORHANDLE csrhandle [IN]: ָ���Ĳ�ѯ�α���
// ����  : int *dataid [OUT]: �α��е�ǰ����DATAID
// ����  : void *pData [OUT]: �����α��е�ǰλ�õļ�¼���ݣ����÷���Ҫ����ռ�
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTCursorFetch(SMTABLEHANDLE SMTHandle, CURSORHANDLE csrhandle, int *dataid, void *pData, char *eMsg);


// ������: SMTCursorPrev
// ���  : ������ 2005-11-25 11:36:30
// ����  : ���α��������ƶ�һ���α�λ��ָ��
// ����  : bool �������Ƿ�ɹ��ƶ���true����ʾ�ƶ�ǰ��λ�ò����׸�λ�ã�false����ʾ�����Ѿ����׸�λ�ã�Ҳ��������������
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : CURSORHANDLE csrhandle [IN]: ָ���Ĳ�ѯ�α���
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTCursorPrev(SMTABLEHANDLE SMTHandle, CURSORHANDLE csrhandle, char *eMsg);


// ������: SMTCursorNext
// ���  : ������ 2005-11-25 11:38:40
// ����  : ���α��������ƶ�һ���α�λ��ָ��
// ����  : bool �������Ƿ�ɹ��ƶ���true����ʾ�ƶ�ǰ��λ�ò������λ�ã�false����ʾ�����Ѿ������λ�ã�Ҳ��������������
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : CURSORHANDLE csrhandle [IN]: ָ���Ĳ�ѯ�α���
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTCursorNext(SMTABLEHANDLE SMTHandle, CURSORHANDLE csrhandle, char *eMsg);


// ������: SMTGetIndexInfo
// ���  : ������ 2005-12-1 11:51:34
// ����  : ��ȡָ����������Ϣ
// ����  : bool ���Ƿ��ȡ�ɹ���false��ʧ�ܣ��μ�eMsg������Ϣ
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int idxid [IN]: ָ��������ID����0��ʼ��9
// ����  : int *k_offset [OUT]: ���عؼ����ڼ�¼��ƫ��λ��
// ����  : int *k_type_len [OUT]: ���عؼ��ֵ����ͣ�����int,float,int64,double�ȣ������ȣ������ַ������ڴ��ֽڣ�
// ����  : int *uniquekey [OUT]: ���ر������Ƿ�Ϊunique index��0-���ǣ�������
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTGetIndexInfo(SMTABLEHANDLE SMTHandle, int idxid, int *k_offset, int *k_type_len, int *uniquekey, char *eMsg);


// ������: SMTGetIndexKeyData
// ���  : ������ 2005-12-1 11:55:27
// ����  : ��������ID����һ����¼������ժ���ؼ��ֲ��ֵ�����
// ����  : bool �������Ƿ�����ɹ���false��ʧ�ܣ��μ�eMsg������Ϣ
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : int idxid [IN]: ָ��������ID����0��ʼ��9
// ����  : void *recdata [IN]: һ��������¼����
// ����  : void *keybuf [OUT]: ����ժ�����������ؼ��ֵ�����
// ����  : int *type_len [OUT]: ���ظ������Ĺؼ������ͻ򳤶�
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTGetIndexKeyData(SMTABLEHANDLE SMTHandle,int idxid, void *recdata, void *keybuf, int *type_len, char *eMsg);


// ������: SMTCompData
// ���  : ������ 2005-12-1 11:59:33
// ����  : �����������ͣ��Ƚ���������
// ����  : int : ����<0 �� ��ʾdata0<data1; ==0 - ��ʾdata0=data1; >0 - ��ʾdata0>data1
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ (����ΪNULL)
// ����  : int type_len [IN]: ���ͻ򳤶�
// ����  : void *data0 [IN]: �Ƚ�����0�ĵ�ַ
// ����  : void *data1 [IN]: �Ƚ�����1�ĵ�ַ
KSSHMT_API int SMTCompData(SMTABLEHANDLE SMTHandle, int type_len, void *data0, void *data1);


// ������: SMTGetTableInfo
// ���  : ������ 2005-12-1 12:02:37
// ����  : ��ȡ�򿪵Ĺ����ڴ���Ҫ��Ϣ
// ����  : bool : �����Ƿ�ɹ���ȡ��false��ʧ�ܣ��ο�eMsg������Ϣ
// ����  : SMTABLEHANDLE SMTHandle [IN]: �Ѿ��򿪵Ĺ������ 
// ����  : sH_TABLEHEAD *ptableinfo [OUT]: ���ش�Ź����ڴ��ĸ�Ҫ��Ϣ
// ����  : char *eMsg [OUT]: �������ʱ�����ڷ��ش�����Ϣ��Ӧ�ö��� char eMsg[256];
KSSHMT_API bool SMTGetTableInfo(SMTABLEHANDLE SMTHandle, sH_TABLEHEAD *ptableinfo, char *eMsg);


// ������: SMTRemove
// ���  : ������ 2005-12-1 12:04:30
// ����  : ��ϵͳ�ڴ��У�ժ���ù����ڴ��һֱ�����д򿪵Ľ��̶��˳��󣬲���ϵͳ����ȫ�����鹲���ڴ�飩
// ����  : bool �������Ƿ�ɹ�ժ��
// ����  : const char *tablename [IN]: �����ڴ����ID
KSSHMT_API bool SMTRemove(const char *tablename);


// ������: SMTClear
// ���  : ������ 2005-12-24 16:05:57
// ����  : ��չ����ڴ���е����ݺ�������ǣ���Ϊһ���ձ�
// ����  : void 
// ����  : SMTABLEHANDLE SMTHandle
KSSHMT_API void SMTClear(SMTABLEHANDLE SMTHandle);

#ifdef  __cplusplus
}
#endif

#undef KSSHMT_API
   
#endif
