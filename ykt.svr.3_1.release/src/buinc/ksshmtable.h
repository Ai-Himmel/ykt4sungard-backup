/********************************************************************
	created:	2005/11/24
	created:	24:11:2005   9:39
	filename: 	D:\proj\ksbass\ksshmtable\ksshmtable.h
	file path:	D:\proj\ksbass\ksshmtable
	file base:	ksshmtable
	file ext:	h
	author:		CHENYH

	purpose:	 为了能够提供给ESQL-C程序调用，特别抽取出来一个C调用接口

   限制条件：  tableid: 0-99; idxid: 0-9 (每个表唯一，不同表的值可以相同)；
            keylength: 可以为SHT_KEYTYPES中定义的，或者为>0表示的关键字长度
*********************************************************************/
#ifndef _KSSHMTABLE_
#define _KSSHMTABLE_

#ifndef SMT_IN_ONE
#define SMT_IN_ONE
#endif

typedef void * CURSORHANDLE;        // 多记录查询时候的游标句柄

typedef void * SMTABLEHANDLE;       // 共享内存表的句柄

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


enum SHTCMP_TYPES {     // 数据比较的时候的比较符
    SHTCT_L,
    SHTCT_LE,
    SHTCT_E,
    SHTCT_GE,
    SHTCT_G
};

enum SHT_KEYTYPES {     // 索引关键字的类型，如果为纯内存数据或字符串比较，则用>0的长度值
    SHTKT_INT32 = -1,
    SHTKT_INT64 = -2,
    SHTKT_FLOAT = -3,
    SHTKT_DOUBLE = -4,
    SHTKT_UINT32 = -5
};

#define SHTABLE_KEYID   28


typedef  struct {
    int  m_tableid;      // 表ID
    int  m_idxcnt;       // 本数据表内包含多少个索引
    int  m_reccnt;       // 实际数量
    int  m_maxrecs;      // 可容纳数量
    int  m_recsize;      // 记录大小 (原始记录长度)
    int  m_unitsize;     // 记录对齐后的长度(字节数)
    int  m_firstfree;    // 第一个空闲Record的编号
    int  m_firstdata;    // 第一个有效数据块号
    int  m_lastdata;     // 最后一个有效数据块号
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

#ifdef SMT_IN_ONE   // 如果采用一个系统中的共享内存表只用一个共享内存块，则需要如下函数：
    typedef struct {
        unsigned int maxrecs;
        unsigned int recsize;
        int   idxcnt;
    } T_TABLEINFO;

    KSSHMT_API bool INITSMT(const char *SMTName, int tablecnt, T_TABLEINFO *tableinfo);

    KSSHMT_API void EXITSMT();
    KSSHMT_API void REMOVESMT(const char *SMTName);   // 将共享内存表从系统中彻底清除

// 函数名: SMTCreate
// 编程  : 陈永华 2005-11-24 18:13:57
// 描述  : 为一个共享内存数据表创建一个共享内存块
// 返回  : SMTABLEHANDLE ： 返回创建成功的内存块句柄；失败则返回NULL，参见eMsg中的信息
// 参数  : int tableid [IN]: 共享表ID (从0开始最大可以为99) 参见INITSMT中的tableinfo中的序号
// 参数  : unsigned int maxrecs [IN]: 共享内存的最大可存放记录数
// 参数  : unsigned int recsize [IN]: 一条记录的长度字节数
// 参数  : int idxcnt [IN]: 本共享表中将保存多少个索引树
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API SMTABLEHANDLE SMTCreate(int tableid, unsigned int maxrecs, unsigned int recsize, int idxcnt, char *eMsg);


// 函数名: SMTOpen
// 编程  : 陈永华 2005-11-24 18:17:21
// 描述  : 打开一个已经被创建了的共享内存表
// 返回  : SMTABLEHANDLE : 返回打开成功的共享表的句柄；==NULL: 失败，参见eMsg中的信息
// 参数  : int tableid [IN]: 共享表ID (从0开始最大可以为99) 参见INITSMT中的tableinfo中的序号
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API SMTABLEHANDLE SMTOpen(int tableid, char *eMsg);

#else

// 函数名: SMTCreate
// 编程  : 陈永华 2005-11-24 18:13:57
// 描述  : 为一个共享内存数据表创建一个共享内存块
// 返回  : SMTABLEHANDLE ： 返回创建成功的内存块句柄；失败则返回NULL，参见eMsg中的信息
// 参数  : const char *tablename  [IN]: 共享表名称，也是共享表对应的文件
// 参数  : int tableid [IN]: 共享表ID (从0开始最大可以为99)
// 参数  : unsigned int maxrecs [IN]: 共享内存的最大可存放记录数
// 参数  : unsigned int recsize [IN]: 一条记录的长度字节数
// 参数  : int idxcnt [IN]: 本共享表中将保存多少个索引树
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API SMTABLEHANDLE SMTCreate(const char *tablename, int tableid, unsigned int maxrecs, unsigned int recsize, int idxcnt, char *eMsg);


// 函数名: SMTOpen
// 编程  : 陈永华 2005-11-24 18:17:21
// 描述  : 打开一个已经被创建了的共享内存表
// 返回  : SMTABLEHANDLE : 返回打开成功的共享表的句柄；==NULL: 失败，参见eMsg中的信息
// 参数  : const char *tablename  [IN]: 共享表名称，也是共享表对应的文件
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API SMTABLEHANDLE SMTOpen(const char *tablename, char *eMsg);
#endif


// 函数名: EmulateSizeOfSMT
// 编程  : 陈永华 2005-11-24 18:11:42
// 描述  : 用于估算建立一个共享内存表，需要的共享内存空间
// 返回  : unsigned int ：需要的共享内存空间的字节数
// 参数  : unsigned int maxrecs [IN]: 共享内存的最大可存放记录数
// 参数  : unsigned int recsize [IN]: 一条记录的长度字节数
// 参数  : int idxcnt [IN]: 本共享表中将保存多少个索引树
    KSSHMT_API unsigned int EmulateSizeOfSMT(unsigned int maxrecs, unsigned int recsize, int idxcnt);


// 函数名: SMTCreateIndex
// 编程  : 陈永华 2005-11-24 18:19:29
// 描述  : 在一个共享内存表中创建一个索引
// 返回  : bool ：返回是否成功创建本索引，false(0): 失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int idxid [IN]: 定义本索引的ID，从0开始到9，一个共享表不能重复，不同表之间无关
// 参数  : unsigned int keyoffset [IN]: 索引关键字数据在记录中的偏移位置
// 参数  : int keytype_len [IN]: 索引关键字的类型，参考SHT_KEYTYPES。如果为纯内存数据或字符串比较，则用>0的长度值
// 参数  : int uniquekey [IN]: 本索引是否为unique index；0 - 不是，关键字可重复；1 - 是，关键字不可以重复
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTCreateIndex(SMTABLEHANDLE SMTHandle,int idxid, unsigned int keyoffset, int keytype_len, int uniquekey, char *eMsg);


// 函数名: SMTClose
// 编程  : 陈永华 2005-11-24 18:24:36
// 描述  : 关闭一个共享内存表，但共享内存没有被摘除
// 返回  : void
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
    KSSHMT_API void SMTClose(SMTABLEHANDLE SMTHandle);


// 函数名: SMTInsert
// 编程  : 陈永华 2005-11-24 18:26:00
// 描述  : 将一个记录插入到指定的共享内存表
// 返回  : int  返回插入记录的DATAID；>=0:成功；<0:失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : void *recdata [IN]: 一条完整的记录数据
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int  SMTInsert(SMTABLEHANDLE SMTHandle, void *recdata, char *eMsg);


// 函数名: SMTUpdate
// 编程  : 陈永华 2005-11-24 18:28:53
// 描述  : 修改一个指定DATAID的记录数据
// 返回  : bool ：返回是否成功；0-失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int dataid [IN]: 指定记录的DATAID
// 参数  : void *recdata [IN]: 一条完整的记录数据
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTUpdate(SMTABLEHANDLE SMTHandle, int dataid,void *recdata, char *eMsg);


// 函数名: SMTDelete
// 编程  : 陈永华 2005-11-25 10:53:30
// 描述  : 从共享内存表中删除指定的一个记录数据
// 返回  : bool ：返回是否成功； 0-失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int dataid [IN]: 指定记录的DATAID
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTDelete(SMTABLEHANDLE SMTHandle, int dataid, char *eMsg);


// 函数名: SMTGetRecord
// 编程  : 陈永华 2005-11-25 10:54:49
// 描述  : 从指定位置dataid中，读取具体记录数据（完整的）
// 返回  : bool ：返回是否成功； 0-失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int dataid [IN]: 指定记录的DATAID
// 参数  : void *recdata [OUT]: 存放读取的完整记录数据的缓存
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTGetRecord(SMTABLEHANDLE SMTHandle, int dataid,void *recdata, char *eMsg);


// 函数名: SMTGetFirstDataID
// 编程  : 陈永华 2005-11-25 10:56:33
// 描述  : 读取指定共享内存表的首记录的DATAID
// 返回  : int ：返回首记录的DATAID，<0: 失败，可能因为无记录数据
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int SMTGetFirstDataID(SMTABLEHANDLE SMTHandle, char *eMsg);


// 函数名: SMTGetNextDataID
// 编程  : 陈永华 2005-11-25 11:10:53
// 描述  : 读取共享内存表中的相对当前的下一个记录的DATAID
// 返回  : int ：返回下一条记录的DATAID，<0: 失败，可能因为没有后面的记录数据
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int cur_dataid [IN]: 当前记录的DATAID
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int SMTGetNextDataID(SMTABLEHANDLE SMTHandle, int cur_dataid, char *eMsg);


// 函数名: SMTGetRecordCount
// 编程  : 陈永华 2005-11-25 11:12:56
// 描述  : 取指定共享内存表内的记录数
// 返回  : int ：返回共享内存表中的记录数
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int SMTGetRecordCount(SMTABLEHANDLE SMTHandle, char *eMsg);


// 函数名: SMTIndexSeek
// 编程  : 陈永华 2005-11-25 11:13:52
// 描述  : 根据索引找第一个符合本索引条件的记录，返回其DATAID
// 返回  : int ：返回符合条件的记录DATAID；<0: 没有找到或其他错误
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int idxid [IN]: 已经创建的索引号
// 参数  : void *key [IN]: 用于比较的关键字数据
// 参数  : int cmp_oper [IN]: 比较的类型，参考SHTCMP_TYPES中的清单
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int SMTIndexSeek(SMTABLEHANDLE SMTHandle, int idxid, void *key, int cmp_oper, char *eMsg);



// 函数名: SMTSelectFirst
// 编程  : 陈永华 2005-11-29 11:35:38
// 描述  : 全表查找第一个符合本条件的记录，返回其DATAID
// 返回  : int ：返回符合条件的记录DATAID；<0: 没有找到或其他错误
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : void *cmpdata [IN]: 比较数据的指针，NULL，即查找首记录
// 参数  : int cmp_oper [IN]: 比较的类型，参考SHTCMP_TYPES中的清单
// 参数  : int cd_offset [IN]: 比较数据在记录中的偏移位置
// 参数  : int type_len [IN]: 比较数据部分类型，参考SHT_KEYTYPES。如果为纯内存数据或字符串比较，则用>0的长度值
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int SMTSelectFirst(SMTABLEHANDLE SMTHandle, void *cmpdata, int cmp_oper,int cd_offset,int type_len, char *eMsg);


// 函数名: SMTIsOpen
// 编程  : 陈永华 2005-11-25 11:18:48
// 描述  : 检查本共享内存表是否正常打开了，也用于该数据部分是否属于一个合法的共享内存句柄
// 返回  : bool ：返回是否为打开了的共享内存句柄
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTIsOpen(SMTABLEHANDLE SMTHandle, char *eMsg);


// 函数名: SMTIsValidRecord
// 编程  : 陈永华 2005-11-25 11:21:04
// 描述  : 检查指定的dataid是否为本共享内存表中的有效记录数据的DATAID
// 返回  : bool ：返回是否为有效的DATAID
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int dataid [IN]: 指定记录的DATAID
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTIsValidRecord(SMTABLEHANDLE SMTHandle, int dataid, char *eMsg);


// 函数名: SMTLock
// 编程  : 陈永华 2005-11-25 11:22:32
// 描述  : 对共享内存表加锁
// 返回  : bool ：返回是否加锁成功
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : bool bWait [IN]: 是否采用等待锁，false(0): 立即返回状态
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTLock(SMTABLEHANDLE SMTHandle, bool bWait, char *eMsg);


// 函数名: SMTUnlock
// 编程  : 陈永华 2005-11-25 11:24:10
// 描述  : 对共享内存表解锁
// 返回  : bool ：返回是否解锁成功
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTUnlock(SMTABLEHANDLE SMTHandle, char *eMsg);


// 函数名: SMTCursorIndexOpen
// 编程  : 陈永华 2005-11-25 11:24:58
// 描述  : 打开根据索引方式检索的一个查询游标
// 返回  : CURSORHANDLE ：返回该查询游标的句柄，==NULL:失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int idxid [IN]: 已经创建的索引号
// 参数  : void *key [IN]: 用于比较的关键字数据
// 参数  : int cmp_oper [IN]: 比较的类型，参考SHTCMP_TYPES中的清单
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API CURSORHANDLE SMTCursorIndexOpen(SMTABLEHANDLE SMTHandle, int idxid, void *key, int cmp_oper, char *eMsg);


// 函数名: SMTCursorOpen
// 编程  : 陈永华 2005-11-25 11:26:51
// 描述  : 打开一个全表检索的查询游标
// 返回  : CURSORHANDLE ：返回该查询游标的句柄，==NULL:失败
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : void *cmpdata [IN]: 用于比较的数据
// 参数  : int cmp_oper [IN]: 比较的类型，参考SHTCMP_TYPES中的清单
// 参数  : int cd_offset [IN]: 比较数据在记录中的偏移位置
// 参数  : int cd_type_len [IN]: 比较数据部分类型，参考SHT_KEYTYPES。如果为纯内存数据或字符串比较，则用>0的长度值
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API CURSORHANDLE SMTCursorOpen(SMTABLEHANDLE SMTHandle, void *cmpdata, int cmp_oper, int cd_offset, int cd_type_len, char *eMsg);


// 函数名: SMTCursorDestroy
// 编程  : 陈永华 2005-11-25 11:29:49
// 描述  : 关闭已经打开的查询游标
// 返回  : bool ：返回是否成功，false－往往因为游标句柄无效
// 参数  : CURSORHANDLE csrhandle [IN]: 要关闭的查询游标句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTCursorDestroy(CURSORHANDLE csrhandle, char *eMsg);


// 函数名: SMTCursorSize
// 编程  : 陈永华 2005-11-25 11:31:42
// 描述  : 取已经打开的游标句柄中，一共有多少有效记录数
// 返回  : int ：返回有效记录数
// 参数  : CURSORHANDLE csrhandle [IN]: 指定的查询游标句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API int SMTCursorSize(CURSORHANDLE csrhandle, char *eMsg);


// 函数名: SMTCursorFetch
// 编程  : 陈永华 2005-11-25 11:32:53
// 描述  : 获取当前位置的游标中的记录数据，在游标刚刚打开的时候，即为游标中的首记录
// 返回  : bool ：记录数据读取是否成功
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : CURSORHANDLE csrhandle [IN]: 指定的查询游标句柄
// 参数  : int *dataid [OUT]: 游标中当前数据DATAID
// 参数  : void *pData [OUT]: 返回游标中当前位置的记录数据，调用方需要分配空间
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTCursorFetch(SMTABLEHANDLE SMTHandle, CURSORHANDLE csrhandle, int *dataid, void *pData, char *eMsg);


// 函数名: SMTCursorPrev
// 编程  : 陈永华 2005-11-25 11:36:30
// 描述  : 在游标中向上移动一个游标位置指针
// 返回  : bool ：返回是否成功移动，true：表示移动前的位置不是首个位置；false：表示可能已经是首个位置，也可能是其他错误
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : CURSORHANDLE csrhandle [IN]: 指定的查询游标句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTCursorPrev(SMTABLEHANDLE SMTHandle, CURSORHANDLE csrhandle, char *eMsg);


// 函数名: SMTCursorNext
// 编程  : 陈永华 2005-11-25 11:38:40
// 描述  : 在游标中向下移动一个游标位置指针
// 返回  : bool ：返回是否成功移动，true：表示移动前的位置不是最后位置；false：表示可能已经是最后位置，也可能是其他错误
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : CURSORHANDLE csrhandle [IN]: 指定的查询游标句柄
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTCursorNext(SMTABLEHANDLE SMTHandle, CURSORHANDLE csrhandle, char *eMsg);


// 函数名: SMTGetIndexInfo
// 编程  : 陈永华 2005-12-1 11:51:34
// 描述  : 获取指定索引的信息
// 返回  : bool ：是否读取成功，false：失败，参见eMsg返回信息
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int idxid [IN]: 指定索引的ID，从0开始到9
// 参数  : int *k_offset [OUT]: 返回关键字在记录的偏移位置
// 参数  : int *k_type_len [OUT]: 返回关键字的类型（对于int,float,int64,double等），长度（对于字符串或内存字节）
// 参数  : int *uniquekey [OUT]: 返回本索引是否为unique index，0-不是，否则是
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTGetIndexInfo(SMTABLEHANDLE SMTHandle, int idxid, int *k_offset, int *k_type_len, int *uniquekey, char *eMsg);


// 函数名: SMTGetIndexKeyData
// 编程  : 陈永华 2005-12-1 11:55:27
// 描述  : 根据索引ID，从一个记录数据中摘出关键字部分的数据
// 返回  : bool ：返回是否操作成功；false：失败，参见eMsg返回信息
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : int idxid [IN]: 指定索引的ID，从0开始到9
// 参数  : void *recdata [IN]: 一个完整记录数据
// 参数  : void *keybuf [OUT]: 返回摘出来的索引关键字的数据
// 参数  : int *type_len [OUT]: 返回该索引的关键字类型或长度
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTGetIndexKeyData(SMTABLEHANDLE SMTHandle,int idxid, void *recdata, void *keybuf, int *type_len, char *eMsg);


// 函数名: SMTCompData
// 编程  : 陈永华 2005-12-1 11:59:33
// 描述  : 根据数据类型，比较两个数据
// 返回  : int : 返回<0 － 表示data0<data1; ==0 - 表示data0=data1; >0 - 表示data0>data1
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄 (可以为NULL)
// 参数  : int type_len [IN]: 类型或长度
// 参数  : void *data0 [IN]: 比较数据0的地址
// 参数  : void *data1 [IN]: 比较数据1的地址
    KSSHMT_API int SMTCompData(SMTABLEHANDLE SMTHandle, int type_len, void *data0, void *data1);


// 函数名: SMTGetTableInfo
// 编程  : 陈永华 2005-12-1 12:02:37
// 描述  : 获取打开的共享内存表概要信息
// 返回  : bool : 返回是否成功读取；false：失败，参考eMsg错误信息
// 参数  : SMTABLEHANDLE SMTHandle [IN]: 已经打开的共享表句柄
// 参数  : sH_TABLEHEAD *ptableinfo [OUT]: 返回存放共享内存表的概要信息
// 参数  : char *eMsg [OUT]: 当错误的时候，用于返回错误信息，应该定义 char eMsg[256];
    KSSHMT_API bool SMTGetTableInfo(SMTABLEHANDLE SMTHandle, sH_TABLEHEAD *ptableinfo, char *eMsg);


// 函数名: SMTRemove
// 编程  : 陈永华 2005-12-1 12:04:30
// 描述  : 从系统内存中，摘除该共享内存表（一直到所有打开的进程都退出后，操作系统才完全清除这块共享内存块）
// 返回  : bool ：返回是否成功摘除
// 参数  : const char *tablename [IN]: 共享内存表名ID
    KSSHMT_API bool SMTRemove(const char *tablename);


// 函数名: SMTClear
// 编程  : 陈永华 2005-12-24 16:05:57
// 描述  : 清空共享内存表中的数据和索引标记，成为一个空表
// 返回  : void
// 参数  : SMTABLEHANDLE SMTHandle
    KSSHMT_API void SMTClear(SMTABLEHANDLE SMTHandle);

#ifdef  __cplusplus
}
#endif

#undef KSSHMT_API

#endif
