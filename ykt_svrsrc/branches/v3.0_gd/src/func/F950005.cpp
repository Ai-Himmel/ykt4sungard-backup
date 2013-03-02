
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
           char  filnam[11];
};
static const struct sqlcxp sqlfpn =
{
    10,
    "F950005.eC"
};


static unsigned int sqlctx = 63405;


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
            void  *sqhstv[6];
   unsigned int   sqhstl[6];
            int   sqhsts[6];
            void  *sqindv[6];
            int   sqinds[6];
   unsigned int   sqharm[6];
   unsigned int   *sqharc[6];
   unsigned short  sqadto[6];
   unsigned short  sqtdso[6];
} sqlstm = {12,6};

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
5,0,0,1,151,0,4,32,0,0,6,1,0,1,0,2,97,0,0,2,3,0,0,2,3,0,0,2,3,0,0,2,3,0,0,1,3,
0,0,
};


#line 1 "F950005.eC"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "cpack.h"
 #include "errdef.h"
 #include "pubdef.h"
 #include "pubdb.h"
 #include "pubfunc.h"
 #include "dbfunc.h"
 #include "busqc.h"
 #include "dbfunc_foo.h"

/* EXEC SQL INCLUDE SQLCA;
 */ 
#line 1 "/opt/oracle/product/10.2.0/client_1/precomp/public/SQLCA.H"
/*
 * $Header: sqlca.h 24-apr-2003.12:50:58 mkandarp Exp $ sqlca.h 
 */

/* Copyright (c) 1985, 2003, Oracle Corporation.  All rights reserved.  */
 
/*
NAME
  SQLCA : SQL Communications Area.
FUNCTION
  Contains no code. Oracle fills in the SQLCA with status info
  during the execution of a SQL stmt.
NOTES
  **************************************************************
  ***                                                        ***
  *** This file is SOSD.  Porters must change the data types ***
  *** appropriately on their platform.  See notes/pcport.doc ***
  *** for more information.                                  ***
  ***                                                        ***
  **************************************************************

  If the symbol SQLCA_STORAGE_CLASS is defined, then the SQLCA
  will be defined to have this storage class. For example:
 
    #define SQLCA_STORAGE_CLASS extern
 
  will define the SQLCA as an extern.
 
  If the symbol SQLCA_INIT is defined, then the SQLCA will be
  statically initialized. Although this is not necessary in order
  to use the SQLCA, it is a good pgming practice not to have
  unitialized variables. However, some C compilers/OS's don't
  allow automatic variables to be init'd in this manner. Therefore,
  if you are INCLUDE'ing the SQLCA in a place where it would be
  an automatic AND your C compiler/OS doesn't allow this style
  of initialization, then SQLCA_INIT should be left undefined --
  all others can define SQLCA_INIT if they wish.

  If the symbol SQLCA_NONE is defined, then the SQLCA variable will
  not be defined at all.  The symbol SQLCA_NONE should not be defined
  in source modules that have embedded SQL.  However, source modules
  that have no embedded SQL, but need to manipulate a sqlca struct
  passed in as a parameter, can set the SQLCA_NONE symbol to avoid
  creation of an extraneous sqlca variable.
 
MODIFIED
    lvbcheng   07/31/98 -  long to int
    jbasu      12/12/94 -  Bug 217878: note this is an SOSD file
    losborne   08/11/92 -  No sqlca var if SQLCA_NONE macro set 
  Clare      12/06/84 - Ch SQLCA to not be an extern.
  Clare      10/21/85 - Add initialization.
  Bradbury   01/05/86 - Only initialize when SQLCA_INIT set
  Clare      06/12/86 - Add SQLCA_STORAGE_CLASS option.
*/
 
#ifndef SQLCA
#define SQLCA 1
 
struct   sqlca
         {
         /* ub1 */ char    sqlcaid[8];
         /* b4  */ int     sqlabc;
         /* b4  */ int     sqlcode;
         struct
           {
           /* ub2 */ unsigned short sqlerrml;
           /* ub1 */ char           sqlerrmc[70];
           } sqlerrm;
         /* ub1 */ char    sqlerrp[8];
         /* b4  */ int     sqlerrd[6];
         /* ub1 */ char    sqlwarn[8];
         /* ub1 */ char    sqlext[8];
         };

#ifndef SQLCA_NONE 
#ifdef   SQLCA_STORAGE_CLASS
SQLCA_STORAGE_CLASS struct sqlca sqlca
#else
         struct sqlca sqlca
#endif
 
#ifdef  SQLCA_INIT
         = {
         {'S', 'Q', 'L', 'C', 'A', ' ', ' ', ' '},
         sizeof(struct sqlca),
         0,
         { 0, {0}},
         {'N', 'O', 'T', ' ', 'S', 'E', 'T', ' '},
         {0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0}
         }
#endif
         ;
#endif
 
#endif
 
/* end SQLCA */

#line 14 "F950005.eC"

int F950005(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
 /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 17 "F950005.eC"

 sqlint32 hi_sysid = 0;
 char ho_drtp_ip[21] = "";
 sqlint32 ho_drtp_port = 0;
 sqlint32 ho_drtp_no = 0;
 sqlint32 ho_bcc_interval = 0;
 sqlint32 ho_drtp_main_func = 0;
 sqlint16 indr = 0;
 /* EXEC SQL END DECLARE SECTION; */ 
#line 25 "F950005.eC"

 int ret;
 ST_CPACK aPack;
 ST_PACK *out_pack = &(aPack.pack);

 hi_sysid = rPack->lcert_code;

 /* EXEC SQL
 SELECT BCCDRTPIP,BCCDRTPPORT,BCCDRTPNO,BCCMAINFUNCNO,BCCINTERVAL
 INTO :ho_drtp_ip:indr,:ho_drtp_port:indr,:ho_drtp_no:indr,:ho_drtp_main_func:indr
 ,:ho_bcc_interval:indr
 FROM YKT_CUR.T_SUBSYSPAR
 WHERE SYSID=:hi_sysid; */ 
#line 37 "F950005.eC"

{
#line 32 "F950005.eC"
 struct sqlexd sqlstm;
#line 32 "F950005.eC"
 sqlstm.sqlvsn = 12;
#line 32 "F950005.eC"
 sqlstm.arrsiz = 6;
#line 32 "F950005.eC"
 sqlstm.sqladtp = &sqladt;
#line 32 "F950005.eC"
 sqlstm.sqltdsp = &sqltds;
#line 32 "F950005.eC"
 sqlstm.stmt = "select BCCDRTPIP ,BCCDRTPPORT ,BCCDRTPNO ,BCCMAINFUNCNO ,BC\
CINTERVAL into :b0:b1,:b2:b3,:b4:b5,:b6:b7,:b8:b9  from YKT_CUR.T_SUBSYSPAR w\
here SYSID=:b10";
#line 32 "F950005.eC"
 sqlstm.iters = (unsigned int  )1;
#line 32 "F950005.eC"
 sqlstm.offset = (unsigned int  )5;
#line 32 "F950005.eC"
 sqlstm.selerr = (unsigned short)1;
#line 32 "F950005.eC"
 sqlstm.cud = sqlcud0;
#line 32 "F950005.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 32 "F950005.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 32 "F950005.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqhstv[0] = (         void  *)ho_drtp_ip;
#line 32 "F950005.eC"
 sqlstm.sqhstl[0] = (unsigned int  )21;
#line 32 "F950005.eC"
 sqlstm.sqhsts[0] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqindv[0] = (         void  *)&indr;
#line 32 "F950005.eC"
 sqlstm.sqinds[0] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqhstv[1] = (         void  *)&ho_drtp_port;
#line 32 "F950005.eC"
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
#line 32 "F950005.eC"
 sqlstm.sqhsts[1] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqindv[1] = (         void  *)&indr;
#line 32 "F950005.eC"
 sqlstm.sqinds[1] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqhstv[2] = (         void  *)&ho_drtp_no;
#line 32 "F950005.eC"
 sqlstm.sqhstl[2] = (unsigned int  )sizeof(int);
#line 32 "F950005.eC"
 sqlstm.sqhsts[2] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqindv[2] = (         void  *)&indr;
#line 32 "F950005.eC"
 sqlstm.sqinds[2] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqharm[2] = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqadto[2] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqtdso[2] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqhstv[3] = (         void  *)&ho_drtp_main_func;
#line 32 "F950005.eC"
 sqlstm.sqhstl[3] = (unsigned int  )sizeof(int);
#line 32 "F950005.eC"
 sqlstm.sqhsts[3] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqindv[3] = (         void  *)&indr;
#line 32 "F950005.eC"
 sqlstm.sqinds[3] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqharm[3] = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqadto[3] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqtdso[3] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqhstv[4] = (         void  *)&ho_bcc_interval;
#line 32 "F950005.eC"
 sqlstm.sqhstl[4] = (unsigned int  )sizeof(int);
#line 32 "F950005.eC"
 sqlstm.sqhsts[4] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqindv[4] = (         void  *)&indr;
#line 32 "F950005.eC"
 sqlstm.sqinds[4] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqharm[4] = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqadto[4] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqtdso[4] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqhstv[5] = (         void  *)&hi_sysid;
#line 32 "F950005.eC"
 sqlstm.sqhstl[5] = (unsigned int  )sizeof(int);
#line 32 "F950005.eC"
 sqlstm.sqhsts[5] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqindv[5] = (         void  *)0;
#line 32 "F950005.eC"
 sqlstm.sqinds[5] = (         int  )0;
#line 32 "F950005.eC"
 sqlstm.sqharm[5] = (unsigned int  )0;
#line 32 "F950005.eC"
 sqlstm.sqadto[5] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqtdso[5] = (unsigned short )0;
#line 32 "F950005.eC"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 32 "F950005.eC"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 32 "F950005.eC"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 32 "F950005.eC"
 sqlstm.sqpind = sqlstm.sqindv;
#line 32 "F950005.eC"
 sqlstm.sqpins = sqlstm.sqinds;
#line 32 "F950005.eC"
 sqlstm.sqparm = sqlstm.sqharm;
#line 32 "F950005.eC"
 sqlstm.sqparc = sqlstm.sqharc;
#line 32 "F950005.eC"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 32 "F950005.eC"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 32 "F950005.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 32 "F950005.eC"
}

#line 37 "F950005.eC"


 if(SQLCODE)
 {
  ret = SQLCODE;
  CHECK_DB_ERR;
  if(DB_NOTFOUND == ret)
   return E_DB_SUBSYSPARAMS_N;
  else
   return E_DB_SUBSYSPARAMS_R;
 }

 memset(&aPack,0,sizeof aPack);
 ResetNormalCPack(&aPack,0,1);
 SetCol(handle,0);
 SetCol(handle,F_SPHONE,F_LVOL0,F_LVOL1,F_LVOL2,F_LVOL3,F_LVOL4,0);
 des2src(out_pack->sphone,ho_drtp_ip);
 out_pack->lvol0 = ho_drtp_port;
 out_pack->lvol1 = ho_drtp_no;
 out_pack->lvol2 = ho_drtp_main_func;
 out_pack->lvol3 = 0;
 out_pack->lvol4 = ho_bcc_interval;
 PutRow(handle,out_pack,pRetCode,szMsg);
 return 0;
}
