#ifndef ESQLC_H__
#define ESQLC_H__
/** 确保只定义了一种数据库? */
#ifdef ESQL_DB2
#ifdef ESQL_DEFINED
#error you can only define one of ESQL_ORACLE, ESQL_DB2
#else
#define ESQL_DEFINED	
#include <sql.h>
#include <sqlcodes.h>
#include <sqlca.h>
#include <sqlda.h>

extern struct sqlca sqlca;	/**< 全局sqlca, 在embsql.sqc里定义 */
#define SQLCODE		sqlca.sqlcode
#define SQLCOUNT	sqlca.sqlerrd[2]
#define SQLERRMC	sqlca.sqlerrmc
#define EFFECT_ROWS sqlca.sqlerrd[2]

#define DB_SUCCESS 		0
#define DB_NOTFOUND 	100
#define DB_REPEAT 	    -803
#define DB_DISCONN	    -1024
#define DB_BADCONN     	-900

#endif
#endif

#ifdef ESQL_ORA
#ifdef ESQL_DEFINED
#error you can only define one of ESQL_ORACLE, ESQL_DB2
#else
#define ESQL_DEFINED	
#define SQLCA_NONE
#include <sqlca.h>
#include <sqlda.h>
extern struct sqlca sqlca;	/**< 全局sqlca, 在embsql.sqc里定义 */

#ifdef __cplusplus
extern "C" {
#endif

extern void sqlglm(char *,int *,int *);

#ifdef __cplusplus
}
#endif
#define SQLCODE		sqlca.sqlcode
#define SQLCOUNT	sqlca.sqlerrd[2]
#define SQLERRM		sqlca.sqlerrm.sqlerrmc
#define EFFECT_ROWS sqlca.sqlerrd[2]
#define	sqlint32	int
#define   sqlint16 short
		
#define DB_SUCCESS 0
#define DB_NOTFOUND 100
#define DB_NULL		-1405
#define DB_REPEAT 	    -1
#define DB_DISCONN	    -3114
#define DB_BADCONN     -1012

#endif
#endif


extern int g_dbchkerr;
extern int g_sqlcode;
extern char g_sqlmsg[1024];

//#ifdef __cplusplus
//extern "C" {
//#endif

void db_trim(char *str);
int db_chk_err(char file[],int line,struct sqlca *caPointer);
int db_connect(char *v_dbname,char *v_user,char *v_passwd);
int db_disconnect();
int db_commit();
int db_rollback();
int db_getsysdatetime(char *dbdate,char *dbtime);
int db_getsysdatetime2(char *dbdatetime);
int db_getsysdate(char *dbdate);
int db_getsystime(char *dbtime);

int DynamicStmtExecute(const char *stmt);
int dynamic_execute_sql(const char *sqlstr,int *count);

//
//#ifdef __cplusplus
//}
//#endif
#endif
