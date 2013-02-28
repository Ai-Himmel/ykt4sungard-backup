#ifndef _DB_DEFINE_H_
#define _DB_DEFINE_H_
/**
 文件: 数据类型定义
*/
#ifdef IBMDB2
// for IBM DB2 
#include <sql.h>
#include <sqlca.h>
/*
typedef sqlint32	db_int32;
typedef char		db_char;
typedef sqlint16	db_int16;
typedef sqlint16	db_indr;
*/
#define db_int32	sqlint32
#define db_char	char
#define db_int16	sqlint16
#define db_indr	sqlint16

#define BEGIN_DECLARE	EXEC SQL BEGIN DECLARE SECTION
#define END_DECLARE		EXEC SQL END DECLARE SECTION

#elif defined(ORACLE)

#endif

#endif // _DB_DEFINE_H_

