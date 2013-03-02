
/* Result Sets Interface */
#ifndef SQL_CRSR
#  define SQL_CRSR
  struct sql_cursor
  {
    unsigned int curocn;
    void *ptr1;
    void *ptr2;
    unsigned int magic;
  };
  typedef struct sql_cursor sql_cursor;
  typedef struct sql_cursor SQL_CURSOR;
#endif /* SQL_CRSR */

/* Thread Safety */
typedef void * sql_context;
typedef void * SQL_CONTEXT;

/* Object support */
struct sqltvn
{
  unsigned char *tvnvsn; 
  unsigned short tvnvsnl; 
  unsigned char *tvnnm;
  unsigned short tvnnml; 
  unsigned char *tvnsnm;
  unsigned short tvnsnml;
};
typedef struct sqltvn sqltvn;

struct sqladts
{
  unsigned int adtvsn; 
  unsigned short adtmode; 
  unsigned short adtnum;  
  sqltvn adttvn[1];       
};
typedef struct sqladts sqladts;

static struct sqladts sqladt = {
  1,1,0,
};

/* Binding to PL/SQL Records */
struct sqltdss
{
  unsigned int tdsvsn; 
  unsigned short tdsnum; 
  unsigned char *tdsval[1]; 
};
typedef struct sqltdss sqltdss;
static struct sqltdss sqltds =
{
  1,
  0,
};

/* File name & Package Name */
struct sqlcxp
{
  unsigned short fillen;
           char  filnam[9];
};
static const struct sqlcxp sqlfpn =
{
    8,
    "busqc.eC"
};


static unsigned int sqlctx = 18765;


static struct sqlexd {
   unsigned int   sqlvsn;
   unsigned int   arrsiz;
   unsigned int   iters;
   unsigned int   offset;
   unsigned short selerr;
   unsigned short sqlety;
   unsigned int   occurs;
      const short *cud;
   unsigned char  *sqlest;
      const char  *stmt;
   sqladts *sqladtp;
   sqltdss *sqltdsp;
            void  **sqphsv;
   unsigned int   *sqphsl;
            int   *sqphss;
            void  **sqpind;
            int   *sqpins;
   unsigned int   *sqparm;
   unsigned int   **sqparc;
   unsigned short  *sqpadto;
   unsigned short  *sqptdso;
   unsigned int   sqlcmax;
   unsigned int   sqlcmin;
   unsigned int   sqlcincr;
   unsigned int   sqlctimeout;
   unsigned int   sqlcnowait;
              int   sqfoff;
   unsigned int   sqcmod;
   unsigned int   sqfmod;
            void  *sqhstv[4];
   unsigned int   sqhstl[4];
            int   sqhsts[4];
            void  *sqindv[4];
            int   sqinds[4];
   unsigned int   sqharm[4];
   unsigned int   *sqharc[4];
   unsigned short  sqadto[4];
   unsigned short  sqtdso[4];
} sqlstm = {12,4};

// Prototypes
extern "C" {
  void sqlcxt (void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlcx2t(void **, unsigned int *,
               struct sqlexd *, const struct sqlcxp *);
  void sqlbuft(void **, char *);
  void sqlgs2t(void **, char *);
  void sqlorat(void **, unsigned int *, void *);
}

// Forms Interface
static const int IAPSUCC = 0;
static const int IAPFAIL = 1403;
static const int IAPFTL  = 535;
extern "C" { void sqliem(char *, int *); }

typedef struct { unsigned short len; unsigned char arr[1]; } VARCHAR;
typedef struct { unsigned short len; unsigned char arr[1]; } varchar;

#define SQLCODE sqlca.sqlcode

/* cud (compilation unit data) array */
static const short sqlcud0[] =
{12,4128,852,27,0,
5,0,0,1,0,0,30,57,0,0,0,0,0,1,0,
20,0,0,2,0,0,27,113,0,0,4,4,0,1,0,1,97,0,0,1,97,0,0,1,97,0,0,1,10,0,0,
51,0,0,3,29,0,4,136,0,0,1,0,0,1,0,2,3,0,0,
70,0,0,4,29,0,4,162,0,0,1,0,0,1,0,2,3,0,0,
89,0,0,5,77,0,4,199,0,0,2,1,0,1,0,2,3,0,0,1,3,0,0,
112,0,0,6,76,0,3,208,0,0,3,3,0,1,0,1,97,0,0,1,3,0,0,1,97,0,0,
139,0,0,7,0,0,31,214,0,0,0,0,0,1,0,
154,0,0,8,0,0,29,217,0,0,0,0,0,1,0,
169,0,0,9,0,0,31,221,0,0,0,0,0,1,0,
};


#line 1 "busqc.eC"
 #include <string.h>
 #include <time.h>
 #include "esqlc.h"
 #include "busqc.h"
 #include "pubfunc.h"
 #include "XPack.h"

extern ST_BUNIT g_BUnit;
extern ST_SQLDB g_SqlDB;
extern "C" void GetPack(ST_CPACK *pack,char *buf);
extern "C" int GetCpackDataString(ST_CPACK *cpack,char *buf);


CXPack *pXPack=(CXPack *)GetDefaultXPack();

int GetCpackDataString(ST_CPACK *cpack,char *buf)
{
 int iLastFidx;
 char sFieldValue[512];

 const ST_PDATALIST *PDataList;
 PDataList=pXPack->GetPackDef(iLastFidx);
 for(int i=0;i<iLastFidx;i++)
 {
  if(pXPack->IsValidField(&(cpack->head),i))
  {
   pXPack->GetFieldValue(&(cpack->pack),i,sFieldValue);
   sprintf(buf+strlen(buf),"%s:%d:%s\n",PDataList[i].szName,strlen(sFieldValue),sFieldValue);
  }
 }
 return 0;
}
void SQLErrorHandler()
{
   g_SqlDB.lErrorCode = SQLCODE;



   if (SQLCODE<=-10000)
      SQLDebugLog(SQLCODE,"SQLERROR DEBUG: SQLSTATE(%s)-msg%ld:'%s'",
         g_SqlDB.szErrorState,
         g_SqlDB.lErrorNumber,
         g_SqlDB.szErrorMsg);
}

void SQLInitialize()
{
}

void SQLDisconnect()
{
   if (g_SqlDB.bConnected)
   {



 /* EXEC SQL COMMIT WORK RELEASE; */ 
#line 57 "busqc.eC"

{
#line 57 "busqc.eC"
 struct sqlexd sqlstm;
#line 57 "busqc.eC"
 sqlstm.sqlvsn = 12;
#line 57 "busqc.eC"
 sqlstm.arrsiz = 0;
#line 57 "busqc.eC"
 sqlstm.sqladtp = &sqladt;
#line 57 "busqc.eC"
 sqlstm.sqltdsp = &sqltds;
#line 57 "busqc.eC"
 sqlstm.iters = (unsigned int  )1;
#line 57 "busqc.eC"
 sqlstm.offset = (unsigned int  )5;
#line 57 "busqc.eC"
 sqlstm.cud = sqlcud0;
#line 57 "busqc.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 57 "busqc.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 57 "busqc.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 57 "busqc.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 57 "busqc.eC"
}

#line 57 "busqc.eC"


      g_SqlDB.bConnected = 0;
   }
}

void SQLExit()
{
   SQLDisconnect();
}






long SQLConnectToServer()
{
   /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 75 "busqc.eC"


   char szConnectToServer[32] = "";
   char szConnectToDatabase[32] = "";
   char szConnectToLogin[32] = "";
   char szConnectToPassword[32] = "";
   /* EXEC SQL END DECLARE SECTION; */ 
#line 81 "busqc.eC"



   ST_SQLDB *pSqlDB = &(g_SqlDB);


   if (strlen(pSqlDB->szDatabase) == 0)
   {
      strcpy(pSqlDB->szDatabase, "pubs");
   }


   if (strlen(pSqlDB->szServer) != 0)
   {
      strcpy(szConnectToServer, pSqlDB->szServer);
   }
   if (strlen(pSqlDB->szDatabase) != 0)
   {
      strcpy(szConnectToDatabase, pSqlDB->szDatabase);
   }
   if (strlen(pSqlDB->szLogin) != 0)
   {
      strcpy(szConnectToLogin, pSqlDB->szLogin);
   }
   if (strlen(pSqlDB->szPassword) != 0)
   {
      strcpy(szConnectToPassword, pSqlDB->szPassword);
   }




 /* EXEC SQL CONNECT :szConnectToLogin IDENTIFIED BY :szConnectToPassword USING :szConnectToDatabase; */ 
#line 113 "busqc.eC"

{
#line 113 "busqc.eC"
 struct sqlexd sqlstm;
#line 113 "busqc.eC"
 sqlstm.sqlvsn = 12;
#line 113 "busqc.eC"
 sqlstm.arrsiz = 4;
#line 113 "busqc.eC"
 sqlstm.sqladtp = &sqladt;
#line 113 "busqc.eC"
 sqlstm.sqltdsp = &sqltds;
#line 113 "busqc.eC"
 sqlstm.iters = (unsigned int  )50;
#line 113 "busqc.eC"
 sqlstm.offset = (unsigned int  )20;
#line 113 "busqc.eC"
 sqlstm.cud = sqlcud0;
#line 113 "busqc.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 113 "busqc.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 113 "busqc.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 113 "busqc.eC"
 sqlstm.sqhstv[0] = (         void  *)szConnectToLogin;
#line 113 "busqc.eC"
 sqlstm.sqhstl[0] = (unsigned int  )32;
#line 113 "busqc.eC"
 sqlstm.sqhsts[0] = (         int  )32;
#line 113 "busqc.eC"
 sqlstm.sqindv[0] = (         void  *)0;
#line 113 "busqc.eC"
 sqlstm.sqinds[0] = (         int  )0;
#line 113 "busqc.eC"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 113 "busqc.eC"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 113 "busqc.eC"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 113 "busqc.eC"
 sqlstm.sqhstv[1] = (         void  *)szConnectToPassword;
#line 113 "busqc.eC"
 sqlstm.sqhstl[1] = (unsigned int  )32;
#line 113 "busqc.eC"
 sqlstm.sqhsts[1] = (         int  )32;
#line 113 "busqc.eC"
 sqlstm.sqindv[1] = (         void  *)0;
#line 113 "busqc.eC"
 sqlstm.sqinds[1] = (         int  )0;
#line 113 "busqc.eC"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 113 "busqc.eC"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 113 "busqc.eC"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 113 "busqc.eC"
 sqlstm.sqhstv[2] = (         void  *)szConnectToDatabase;
#line 113 "busqc.eC"
 sqlstm.sqhstl[2] = (unsigned int  )32;
#line 113 "busqc.eC"
 sqlstm.sqhsts[2] = (         int  )32;
#line 113 "busqc.eC"
 sqlstm.sqindv[2] = (         void  *)0;
#line 113 "busqc.eC"
 sqlstm.sqinds[2] = (         int  )0;
#line 113 "busqc.eC"
 sqlstm.sqharm[2] = (unsigned int  )0;
#line 113 "busqc.eC"
 sqlstm.sqadto[2] = (unsigned short )0;
#line 113 "busqc.eC"
 sqlstm.sqtdso[2] = (unsigned short )0;
#line 113 "busqc.eC"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 113 "busqc.eC"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 113 "busqc.eC"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 113 "busqc.eC"
 sqlstm.sqpind = sqlstm.sqindv;
#line 113 "busqc.eC"
 sqlstm.sqpins = sqlstm.sqinds;
#line 113 "busqc.eC"
 sqlstm.sqparm = sqlstm.sqharm;
#line 113 "busqc.eC"
 sqlstm.sqparc = sqlstm.sqharc;
#line 113 "busqc.eC"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 113 "busqc.eC"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 113 "busqc.eC"
 sqlstm.sqlcmax = (unsigned int )100;
#line 113 "busqc.eC"
 sqlstm.sqlcmin = (unsigned int )2;
#line 113 "busqc.eC"
 sqlstm.sqlcincr = (unsigned int )1;
#line 113 "busqc.eC"
 sqlstm.sqlctimeout = (unsigned int )0;
#line 113 "busqc.eC"
 sqlstm.sqlcnowait = (unsigned int )0;
#line 113 "busqc.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 113 "busqc.eC"
}

#line 113 "busqc.eC"



   if (SQLCODE == 0)
   {
      pSqlDB->bConnected = 1;
   }
   else
   {

      pSqlDB->bConnected = 0;
   }
   return(SQLCODE);
}

int SQLIsConnectOK()
{
   /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 130 "busqc.eC"

   sqlint32 sv_tv = 0;
   /* EXEC SQL END DECLARE SECTION; */ 
#line 132 "busqc.eC"




   /* EXEC SQL SELECT 1 INTO :sv_tv FROM dual; */ 
#line 136 "busqc.eC"

{
#line 136 "busqc.eC"
   struct sqlexd sqlstm;
#line 136 "busqc.eC"
   sqlstm.sqlvsn = 12;
#line 136 "busqc.eC"
   sqlstm.arrsiz = 4;
#line 136 "busqc.eC"
   sqlstm.sqladtp = &sqladt;
#line 136 "busqc.eC"
   sqlstm.sqltdsp = &sqltds;
#line 136 "busqc.eC"
   sqlstm.stmt = "select 1 into :b0  from dual ";
#line 136 "busqc.eC"
   sqlstm.iters = (unsigned int  )1;
#line 136 "busqc.eC"
   sqlstm.offset = (unsigned int  )51;
#line 136 "busqc.eC"
   sqlstm.selerr = (unsigned short)1;
#line 136 "busqc.eC"
   sqlstm.cud = sqlcud0;
#line 136 "busqc.eC"
   sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 136 "busqc.eC"
   sqlstm.sqlety = (unsigned short)256;
#line 136 "busqc.eC"
   sqlstm.occurs = (unsigned int  )0;
#line 136 "busqc.eC"
   sqlstm.sqhstv[0] = (         void  *)&sv_tv;
#line 136 "busqc.eC"
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 136 "busqc.eC"
   sqlstm.sqhsts[0] = (         int  )0;
#line 136 "busqc.eC"
   sqlstm.sqindv[0] = (         void  *)0;
#line 136 "busqc.eC"
   sqlstm.sqinds[0] = (         int  )0;
#line 136 "busqc.eC"
   sqlstm.sqharm[0] = (unsigned int  )0;
#line 136 "busqc.eC"
   sqlstm.sqadto[0] = (unsigned short )0;
#line 136 "busqc.eC"
   sqlstm.sqtdso[0] = (unsigned short )0;
#line 136 "busqc.eC"
   sqlstm.sqphsv = sqlstm.sqhstv;
#line 136 "busqc.eC"
   sqlstm.sqphsl = sqlstm.sqhstl;
#line 136 "busqc.eC"
   sqlstm.sqphss = sqlstm.sqhsts;
#line 136 "busqc.eC"
   sqlstm.sqpind = sqlstm.sqindv;
#line 136 "busqc.eC"
   sqlstm.sqpins = sqlstm.sqinds;
#line 136 "busqc.eC"
   sqlstm.sqparm = sqlstm.sqharm;
#line 136 "busqc.eC"
   sqlstm.sqparc = sqlstm.sqharc;
#line 136 "busqc.eC"
   sqlstm.sqpadto = sqlstm.sqadto;
#line 136 "busqc.eC"
   sqlstm.sqptdso = sqlstm.sqtdso;
#line 136 "busqc.eC"
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 136 "busqc.eC"
}

#line 136 "busqc.eC"



   if (SQLCODE==0 && sv_tv==1)
      return(1);
   else
      return(0);
}

int TestSQLConnect()
{
  int state = 0;
   static time_t lasttry = 0;
   time_t now = 0;

   /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 151 "busqc.eC"

   sqlint32 sv_tv_test = 0;
   /* EXEC SQL END DECLARE SECTION; */ 
#line 153 "busqc.eC"


   now = time(0);
   if((now - lasttry) > 10)
   {
   lasttry = now;



   /* EXEC SQL SELECT 1 INTO :sv_tv_test FROM dual; */ 
#line 162 "busqc.eC"

{
#line 162 "busqc.eC"
   struct sqlexd sqlstm;
#line 162 "busqc.eC"
   sqlstm.sqlvsn = 12;
#line 162 "busqc.eC"
   sqlstm.arrsiz = 4;
#line 162 "busqc.eC"
   sqlstm.sqladtp = &sqladt;
#line 162 "busqc.eC"
   sqlstm.sqltdsp = &sqltds;
#line 162 "busqc.eC"
   sqlstm.stmt = "select 1 into :b0  from dual ";
#line 162 "busqc.eC"
   sqlstm.iters = (unsigned int  )1;
#line 162 "busqc.eC"
   sqlstm.offset = (unsigned int  )70;
#line 162 "busqc.eC"
   sqlstm.selerr = (unsigned short)1;
#line 162 "busqc.eC"
   sqlstm.cud = sqlcud0;
#line 162 "busqc.eC"
   sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 162 "busqc.eC"
   sqlstm.sqlety = (unsigned short)256;
#line 162 "busqc.eC"
   sqlstm.occurs = (unsigned int  )0;
#line 162 "busqc.eC"
   sqlstm.sqhstv[0] = (         void  *)&sv_tv_test;
#line 162 "busqc.eC"
   sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 162 "busqc.eC"
   sqlstm.sqhsts[0] = (         int  )0;
#line 162 "busqc.eC"
   sqlstm.sqindv[0] = (         void  *)0;
#line 162 "busqc.eC"
   sqlstm.sqinds[0] = (         int  )0;
#line 162 "busqc.eC"
   sqlstm.sqharm[0] = (unsigned int  )0;
#line 162 "busqc.eC"
   sqlstm.sqadto[0] = (unsigned short )0;
#line 162 "busqc.eC"
   sqlstm.sqtdso[0] = (unsigned short )0;
#line 162 "busqc.eC"
   sqlstm.sqphsv = sqlstm.sqhstv;
#line 162 "busqc.eC"
   sqlstm.sqphsl = sqlstm.sqhstl;
#line 162 "busqc.eC"
   sqlstm.sqphss = sqlstm.sqhsts;
#line 162 "busqc.eC"
   sqlstm.sqpind = sqlstm.sqindv;
#line 162 "busqc.eC"
   sqlstm.sqpins = sqlstm.sqinds;
#line 162 "busqc.eC"
   sqlstm.sqparm = sqlstm.sqharm;
#line 162 "busqc.eC"
   sqlstm.sqparc = sqlstm.sqharc;
#line 162 "busqc.eC"
   sqlstm.sqpadto = sqlstm.sqadto;
#line 162 "busqc.eC"
   sqlstm.sqptdso = sqlstm.sqtdso;
#line 162 "busqc.eC"
   sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 162 "busqc.eC"
}

#line 162 "busqc.eC"


   if (SQLCODE==0 && sv_tv_test==1)
 state = 1;
   else
      state = 0;
   }
   else
   {
 if(SQLCODE == DB_DISCONN || SQLCODE == DB_BADCONN)
        state = 0;
 else
  state = 1;
   }
   g_SqlDB.bConnected = state;
   return state;

}
int SaveCPackData(ST_CPACK* rpack)
{

    /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 183 "busqc.eC"

    sqlint32 hi_func_code = 0;
 char hi_cpack_data[4001]="";
 char hi_save_time[31]="";
     sqlint32 ho_func_code = 0;
   /* EXEC SQL END DECLARE SECTION; */ 
#line 188 "busqc.eC"



 GetCpackDataString(rpack,hi_cpack_data);
 getdbtimestamp(hi_save_time);

 hi_func_code=rpack->head.RequestType;




 /* EXEC SQL
  select func_code into :ho_func_code from t_comm_cfg where func_code=:hi_func_code and rownum=1; */ 
#line 200 "busqc.eC"

{
#line 199 "busqc.eC"
 struct sqlexd sqlstm;
#line 199 "busqc.eC"
 sqlstm.sqlvsn = 12;
#line 199 "busqc.eC"
 sqlstm.arrsiz = 4;
#line 199 "busqc.eC"
 sqlstm.sqladtp = &sqladt;
#line 199 "busqc.eC"
 sqlstm.sqltdsp = &sqltds;
#line 199 "busqc.eC"
 sqlstm.stmt = "select func_code into :b0  from t_comm_cfg where (func_code\
=:b1 and rownum=1)";
#line 199 "busqc.eC"
 sqlstm.iters = (unsigned int  )1;
#line 199 "busqc.eC"
 sqlstm.offset = (unsigned int  )89;
#line 199 "busqc.eC"
 sqlstm.selerr = (unsigned short)1;
#line 199 "busqc.eC"
 sqlstm.cud = sqlcud0;
#line 199 "busqc.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 199 "busqc.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 199 "busqc.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 199 "busqc.eC"
 sqlstm.sqhstv[0] = (         void  *)&ho_func_code;
#line 199 "busqc.eC"
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 199 "busqc.eC"
 sqlstm.sqhsts[0] = (         int  )0;
#line 199 "busqc.eC"
 sqlstm.sqindv[0] = (         void  *)0;
#line 199 "busqc.eC"
 sqlstm.sqinds[0] = (         int  )0;
#line 199 "busqc.eC"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 199 "busqc.eC"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 199 "busqc.eC"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 199 "busqc.eC"
 sqlstm.sqhstv[1] = (         void  *)&hi_func_code;
#line 199 "busqc.eC"
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
#line 199 "busqc.eC"
 sqlstm.sqhsts[1] = (         int  )0;
#line 199 "busqc.eC"
 sqlstm.sqindv[1] = (         void  *)0;
#line 199 "busqc.eC"
 sqlstm.sqinds[1] = (         int  )0;
#line 199 "busqc.eC"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 199 "busqc.eC"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 199 "busqc.eC"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 199 "busqc.eC"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 199 "busqc.eC"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 199 "busqc.eC"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 199 "busqc.eC"
 sqlstm.sqpind = sqlstm.sqindv;
#line 199 "busqc.eC"
 sqlstm.sqpins = sqlstm.sqinds;
#line 199 "busqc.eC"
 sqlstm.sqparm = sqlstm.sqharm;
#line 199 "busqc.eC"
 sqlstm.sqparc = sqlstm.sqharc;
#line 199 "busqc.eC"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 199 "busqc.eC"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 199 "busqc.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 199 "busqc.eC"
}

#line 200 "busqc.eC"


 if(SQLCODE)
 {
  db_chk_err("busqc.sqC", 248,&sqlca);
  SQLCODE = 0;
  return 0;
 }
 /* EXEC SQL
 insert into t_comm_log( SAVE_TIME,FUNC_CODE,CPACK_DATA)
 values(:hi_save_time,:hi_func_code,:hi_cpack_data); */ 
#line 210 "busqc.eC"

{
#line 208 "busqc.eC"
 struct sqlexd sqlstm;
#line 208 "busqc.eC"
 sqlstm.sqlvsn = 12;
#line 208 "busqc.eC"
 sqlstm.arrsiz = 4;
#line 208 "busqc.eC"
 sqlstm.sqladtp = &sqladt;
#line 208 "busqc.eC"
 sqlstm.sqltdsp = &sqltds;
#line 208 "busqc.eC"
 sqlstm.stmt = "insert into t_comm_log (SAVE_TIME,FUNC_CODE,CPACK_DATA) val\
ues (:b0,:b1,:b2)";
#line 208 "busqc.eC"
 sqlstm.iters = (unsigned int  )1;
#line 208 "busqc.eC"
 sqlstm.offset = (unsigned int  )112;
#line 208 "busqc.eC"
 sqlstm.cud = sqlcud0;
#line 208 "busqc.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 208 "busqc.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 208 "busqc.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 208 "busqc.eC"
 sqlstm.sqhstv[0] = (         void  *)hi_save_time;
#line 208 "busqc.eC"
 sqlstm.sqhstl[0] = (unsigned int  )31;
#line 208 "busqc.eC"
 sqlstm.sqhsts[0] = (         int  )0;
#line 208 "busqc.eC"
 sqlstm.sqindv[0] = (         void  *)0;
#line 208 "busqc.eC"
 sqlstm.sqinds[0] = (         int  )0;
#line 208 "busqc.eC"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 208 "busqc.eC"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 208 "busqc.eC"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 208 "busqc.eC"
 sqlstm.sqhstv[1] = (         void  *)&hi_func_code;
#line 208 "busqc.eC"
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
#line 208 "busqc.eC"
 sqlstm.sqhsts[1] = (         int  )0;
#line 208 "busqc.eC"
 sqlstm.sqindv[1] = (         void  *)0;
#line 208 "busqc.eC"
 sqlstm.sqinds[1] = (         int  )0;
#line 208 "busqc.eC"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 208 "busqc.eC"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 208 "busqc.eC"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 208 "busqc.eC"
 sqlstm.sqhstv[2] = (         void  *)hi_cpack_data;
#line 208 "busqc.eC"
 sqlstm.sqhstl[2] = (unsigned int  )4001;
#line 208 "busqc.eC"
 sqlstm.sqhsts[2] = (         int  )0;
#line 208 "busqc.eC"
 sqlstm.sqindv[2] = (         void  *)0;
#line 208 "busqc.eC"
 sqlstm.sqinds[2] = (         int  )0;
#line 208 "busqc.eC"
 sqlstm.sqharm[2] = (unsigned int  )0;
#line 208 "busqc.eC"
 sqlstm.sqadto[2] = (unsigned short )0;
#line 208 "busqc.eC"
 sqlstm.sqtdso[2] = (unsigned short )0;
#line 208 "busqc.eC"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 208 "busqc.eC"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 208 "busqc.eC"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 208 "busqc.eC"
 sqlstm.sqpind = sqlstm.sqindv;
#line 208 "busqc.eC"
 sqlstm.sqpins = sqlstm.sqinds;
#line 208 "busqc.eC"
 sqlstm.sqparm = sqlstm.sqharm;
#line 208 "busqc.eC"
 sqlstm.sqparc = sqlstm.sqharc;
#line 208 "busqc.eC"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 208 "busqc.eC"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 208 "busqc.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 208 "busqc.eC"
}

#line 210 "busqc.eC"

 if(SQLCODE)
 {
  db_chk_err("busqc.sqC", 257,&sqlca);
  /* EXEC SQL ROLLBACK; */ 
#line 214 "busqc.eC"

{
#line 214 "busqc.eC"
  struct sqlexd sqlstm;
#line 214 "busqc.eC"
  sqlstm.sqlvsn = 12;
#line 214 "busqc.eC"
  sqlstm.arrsiz = 4;
#line 214 "busqc.eC"
  sqlstm.sqladtp = &sqladt;
#line 214 "busqc.eC"
  sqlstm.sqltdsp = &sqltds;
#line 214 "busqc.eC"
  sqlstm.iters = (unsigned int  )1;
#line 214 "busqc.eC"
  sqlstm.offset = (unsigned int  )139;
#line 214 "busqc.eC"
  sqlstm.cud = sqlcud0;
#line 214 "busqc.eC"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 214 "busqc.eC"
  sqlstm.sqlety = (unsigned short)256;
#line 214 "busqc.eC"
  sqlstm.occurs = (unsigned int  )0;
#line 214 "busqc.eC"
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 214 "busqc.eC"
}

#line 214 "busqc.eC"

  return -1;
 }
 /* EXEC SQL COMMIT; */ 
#line 217 "busqc.eC"

{
#line 217 "busqc.eC"
 struct sqlexd sqlstm;
#line 217 "busqc.eC"
 sqlstm.sqlvsn = 12;
#line 217 "busqc.eC"
 sqlstm.arrsiz = 4;
#line 217 "busqc.eC"
 sqlstm.sqladtp = &sqladt;
#line 217 "busqc.eC"
 sqlstm.sqltdsp = &sqltds;
#line 217 "busqc.eC"
 sqlstm.iters = (unsigned int  )1;
#line 217 "busqc.eC"
 sqlstm.offset = (unsigned int  )154;
#line 217 "busqc.eC"
 sqlstm.cud = sqlcud0;
#line 217 "busqc.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 217 "busqc.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 217 "busqc.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 217 "busqc.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 217 "busqc.eC"
}

#line 217 "busqc.eC"

 if(SQLCODE)
 {
  db_chk_err("busqc.sqC", 264,&sqlca);
  /* EXEC SQL ROLLBACK; */ 
#line 221 "busqc.eC"

{
#line 221 "busqc.eC"
  struct sqlexd sqlstm;
#line 221 "busqc.eC"
  sqlstm.sqlvsn = 12;
#line 221 "busqc.eC"
  sqlstm.arrsiz = 4;
#line 221 "busqc.eC"
  sqlstm.sqladtp = &sqladt;
#line 221 "busqc.eC"
  sqlstm.sqltdsp = &sqltds;
#line 221 "busqc.eC"
  sqlstm.iters = (unsigned int  )1;
#line 221 "busqc.eC"
  sqlstm.offset = (unsigned int  )169;
#line 221 "busqc.eC"
  sqlstm.cud = sqlcud0;
#line 221 "busqc.eC"
  sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 221 "busqc.eC"
  sqlstm.sqlety = (unsigned short)256;
#line 221 "busqc.eC"
  sqlstm.occurs = (unsigned int  )0;
#line 221 "busqc.eC"
  sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 221 "busqc.eC"
}

#line 221 "busqc.eC"

  return -2;
 }
 return 0;
}
