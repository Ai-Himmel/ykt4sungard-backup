
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
    "F950041.eC"
};


static unsigned int sqlctx = 63437;


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
            void  *sqhstv[3];
   unsigned int   sqhstl[3];
            int   sqhsts[3];
            void  *sqindv[3];
            int   sqinds[3];
   unsigned int   sqharm[3];
   unsigned int   *sqharc[3];
   unsigned short  sqadto[3];
   unsigned short  sqtdso[3];
} sqlstm = {12,3};

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
5,0,0,1,179,0,4,22,0,0,3,2,0,1,0,2,3,0,0,1,3,0,0,1,97,0,0,
32,0,0,2,68,0,4,42,0,0,2,1,0,1,0,2,3,0,0,1,3,0,0,
};


#line 1 "F950041.eC"
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
 #include "acctrans.h"
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

#line 13 "F950041.eC"
int IsShopPosDeviceExist(int deviceid,int& existcnt)
{
 /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 15 "F950041.eC"

 sqlint32 hi_deviceid=0;
 char hi_enddate[9]="";
 sqlint32 ho_cnt=0;
 /* EXEC SQL END DECLARE SECTION; */ 
#line 19 "F950041.eC"

 hi_deviceid=deviceid;
 getsysdate(hi_enddate);
 /* EXEC SQL
 SELECT count(1) INTO :ho_cnt
 FROM ykt_cur.t_shoppos
 WHERE deviceid=:hi_deviceid and status='1' and enddate>=:hi_enddate
 and shopid in(select shopid from ykt_cur.t_shop where boardfeeflag ='1'); */ 
#line 26 "F950041.eC"

{
#line 22 "F950041.eC"
 struct sqlexd sqlstm;
#line 22 "F950041.eC"
 sqlstm.sqlvsn = 12;
#line 22 "F950041.eC"
 sqlstm.arrsiz = 3;
#line 22 "F950041.eC"
 sqlstm.sqladtp = &sqladt;
#line 22 "F950041.eC"
 sqlstm.sqltdsp = &sqltds;
#line 22 "F950041.eC"
 sqlstm.stmt = "select count(1) into :b0  from ykt_cur.t_shoppos where (((d\
eviceid=:b1 and status='1') and enddate>=:b2) and shopid in (select shopid  f\
rom ykt_cur.t_shop where boardfeeflag='1'))";
#line 22 "F950041.eC"
 sqlstm.iters = (unsigned int  )1;
#line 22 "F950041.eC"
 sqlstm.offset = (unsigned int  )5;
#line 22 "F950041.eC"
 sqlstm.selerr = (unsigned short)1;
#line 22 "F950041.eC"
 sqlstm.cud = sqlcud0;
#line 22 "F950041.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 22 "F950041.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 22 "F950041.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 22 "F950041.eC"
 sqlstm.sqhstv[0] = (         void  *)&ho_cnt;
#line 22 "F950041.eC"
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 22 "F950041.eC"
 sqlstm.sqhsts[0] = (         int  )0;
#line 22 "F950041.eC"
 sqlstm.sqindv[0] = (         void  *)0;
#line 22 "F950041.eC"
 sqlstm.sqinds[0] = (         int  )0;
#line 22 "F950041.eC"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 22 "F950041.eC"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 22 "F950041.eC"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 22 "F950041.eC"
 sqlstm.sqhstv[1] = (         void  *)&hi_deviceid;
#line 22 "F950041.eC"
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
#line 22 "F950041.eC"
 sqlstm.sqhsts[1] = (         int  )0;
#line 22 "F950041.eC"
 sqlstm.sqindv[1] = (         void  *)0;
#line 22 "F950041.eC"
 sqlstm.sqinds[1] = (         int  )0;
#line 22 "F950041.eC"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 22 "F950041.eC"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 22 "F950041.eC"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 22 "F950041.eC"
 sqlstm.sqhstv[2] = (         void  *)hi_enddate;
#line 22 "F950041.eC"
 sqlstm.sqhstl[2] = (unsigned int  )9;
#line 22 "F950041.eC"
 sqlstm.sqhsts[2] = (         int  )0;
#line 22 "F950041.eC"
 sqlstm.sqindv[2] = (         void  *)0;
#line 22 "F950041.eC"
 sqlstm.sqinds[2] = (         int  )0;
#line 22 "F950041.eC"
 sqlstm.sqharm[2] = (unsigned int  )0;
#line 22 "F950041.eC"
 sqlstm.sqadto[2] = (unsigned short )0;
#line 22 "F950041.eC"
 sqlstm.sqtdso[2] = (unsigned short )0;
#line 22 "F950041.eC"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 22 "F950041.eC"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 22 "F950041.eC"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 22 "F950041.eC"
 sqlstm.sqpind = sqlstm.sqindv;
#line 22 "F950041.eC"
 sqlstm.sqpins = sqlstm.sqinds;
#line 22 "F950041.eC"
 sqlstm.sqparm = sqlstm.sqharm;
#line 22 "F950041.eC"
 sqlstm.sqparc = sqlstm.sqharc;
#line 22 "F950041.eC"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 22 "F950041.eC"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 22 "F950041.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 22 "F950041.eC"
}

#line 26 "F950041.eC"

 if(SQLCODE)
 {
     db_chk_err("F950041.sqC",43,&sqlca);
     return E_DB_SHOPPOS_R;
 }
 existcnt=ho_cnt;
 return 0;
}
int IsShopFeeCfgExist(int shopid,int& existcnt)
{
 /* EXEC SQL BEGIN DECLARE SECTION; */ 
#line 37 "F950041.eC"

 sqlint32 hi_shopid=0;
 sqlint32 ho_cnt=0;
 /* EXEC SQL END DECLARE SECTION; */ 
#line 40 "F950041.eC"

 hi_shopid=shopid;
 /* EXEC SQL
 SELECT count(1) INTO :ho_cnt
 FROM ykt_cur.t_cfgshopfee
 WHERE shopid=:hi_shopid; */ 
#line 45 "F950041.eC"

{
#line 42 "F950041.eC"
 struct sqlexd sqlstm;
#line 42 "F950041.eC"
 sqlstm.sqlvsn = 12;
#line 42 "F950041.eC"
 sqlstm.arrsiz = 3;
#line 42 "F950041.eC"
 sqlstm.sqladtp = &sqladt;
#line 42 "F950041.eC"
 sqlstm.sqltdsp = &sqltds;
#line 42 "F950041.eC"
 sqlstm.stmt = "select count(1) into :b0  from ykt_cur.t_cfgshopfee where s\
hopid=:b1";
#line 42 "F950041.eC"
 sqlstm.iters = (unsigned int  )1;
#line 42 "F950041.eC"
 sqlstm.offset = (unsigned int  )32;
#line 42 "F950041.eC"
 sqlstm.selerr = (unsigned short)1;
#line 42 "F950041.eC"
 sqlstm.cud = sqlcud0;
#line 42 "F950041.eC"
 sqlstm.sqlest = (unsigned char  *)&sqlca;
#line 42 "F950041.eC"
 sqlstm.sqlety = (unsigned short)256;
#line 42 "F950041.eC"
 sqlstm.occurs = (unsigned int  )0;
#line 42 "F950041.eC"
 sqlstm.sqhstv[0] = (         void  *)&ho_cnt;
#line 42 "F950041.eC"
 sqlstm.sqhstl[0] = (unsigned int  )sizeof(int);
#line 42 "F950041.eC"
 sqlstm.sqhsts[0] = (         int  )0;
#line 42 "F950041.eC"
 sqlstm.sqindv[0] = (         void  *)0;
#line 42 "F950041.eC"
 sqlstm.sqinds[0] = (         int  )0;
#line 42 "F950041.eC"
 sqlstm.sqharm[0] = (unsigned int  )0;
#line 42 "F950041.eC"
 sqlstm.sqadto[0] = (unsigned short )0;
#line 42 "F950041.eC"
 sqlstm.sqtdso[0] = (unsigned short )0;
#line 42 "F950041.eC"
 sqlstm.sqhstv[1] = (         void  *)&hi_shopid;
#line 42 "F950041.eC"
 sqlstm.sqhstl[1] = (unsigned int  )sizeof(int);
#line 42 "F950041.eC"
 sqlstm.sqhsts[1] = (         int  )0;
#line 42 "F950041.eC"
 sqlstm.sqindv[1] = (         void  *)0;
#line 42 "F950041.eC"
 sqlstm.sqinds[1] = (         int  )0;
#line 42 "F950041.eC"
 sqlstm.sqharm[1] = (unsigned int  )0;
#line 42 "F950041.eC"
 sqlstm.sqadto[1] = (unsigned short )0;
#line 42 "F950041.eC"
 sqlstm.sqtdso[1] = (unsigned short )0;
#line 42 "F950041.eC"
 sqlstm.sqphsv = sqlstm.sqhstv;
#line 42 "F950041.eC"
 sqlstm.sqphsl = sqlstm.sqhstl;
#line 42 "F950041.eC"
 sqlstm.sqphss = sqlstm.sqhsts;
#line 42 "F950041.eC"
 sqlstm.sqpind = sqlstm.sqindv;
#line 42 "F950041.eC"
 sqlstm.sqpins = sqlstm.sqinds;
#line 42 "F950041.eC"
 sqlstm.sqparm = sqlstm.sqharm;
#line 42 "F950041.eC"
 sqlstm.sqparc = sqlstm.sqharc;
#line 42 "F950041.eC"
 sqlstm.sqpadto = sqlstm.sqadto;
#line 42 "F950041.eC"
 sqlstm.sqptdso = sqlstm.sqtdso;
#line 42 "F950041.eC"
 sqlcxt((void **)0, &sqlctx, &sqlstm, &sqlfpn);
#line 42 "F950041.eC"
}

#line 45 "F950041.eC"

 if(SQLCODE)
 {
     db_chk_err("F950041.sqC",62,&sqlca);
     return E_DB_CFGSHOPFEE_R;
 }
 existcnt=ho_cnt;
 return 0;
}

int F930006(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg);

int F950041(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
 int ret;
 T_t_device tDevice;
 char sysdate[9]="";
 char systime[7]="";
 T_t_msglist tMsg;
 unsigned char buf[32] = "";
 char cardlist[100] = "";
 int rows = 0;
 int i,j;

 getsysdate(sysdate);
 getsystime(systime);
 memset(&tDevice,0,sizeof tDevice);

 ST_CPACK aPack;
 ST_PACK *out_pack = &(aPack.pack);
 memset(&aPack,0,sizeof aPack);

 ResetNormalCPack(&aPack,0,1);
 SetCol(handle,0);
 SetCol(handle,F_VSVARSTR0,F_VSMESS,0);

 if(rPack->lcert_code < 1)
 {
  return E_NOTEXIST_DEVICE;
 }
 ret = DB_t_device_read_by_deviceid(rPack->lcert_code,&tDevice);
 if(ret)
 {
  if(DB_NOTFOUND == ret)
   return ERRINFO(E_NOTEXIST_DEVICE,rPack->lcert_code);
  else
   return E_DB_DEVICE_R;

 }
 if(tDevice.status[0]!=STATUS_NORMAL)
 {
  return E_DEVICE_LOGOUT;
 }

 int existcnt=0;
 ret=IsShopPosDeviceExist(tDevice.deviceid,existcnt);
 if(ret)
  return ret;
 if(!existcnt)
 {
  ERRTIP("该pos未分配商户或商户不收搭伙费");
  return E_COMMON_ERR;
 }
 int deviceid=0;
 int shopid=0;
 ret = GetShopidByDevphyid(tDevice.devphyid,sysdate,systime,tDevice.deviceid,shopid);
 if(ret)
 {
  return ret;
 }
 existcnt=0;
 writelog(LOG_INFO,"GetShopidByDevphyid OK");
 ret=IsShopFeeCfgExist(shopid,existcnt);
 if(ret)
  return ret;
 if(!existcnt)
 {

  shopid=0;
  writelog(LOG_INFO,"该商户%d搭伙费参数不存在,取通用搭伙费参数",shopid);
 }

 if(strcmp(tDevice.devtypecode,"0201") == 0 && tDevice.devphytype == 1000)
 {
  des2src(rPack->sdate0,tDevice.devphyid);
  ret = F930006(handle,iRequest,rPack,pRetCode,szMsg);
  if(ret)
  {
   return ret;
  }
  return 0;
 }
 double feerate=0;
 ret=GetMaxShopFeeRate(feerate);
 if(ret)
  return ret;

 memset(buf,0,sizeof buf);
 T_t_cfgshopfee cfgshopfee;

 ret = DB_t_cfgshopfee_open_select_by_c1_and_shopid(shopid);
 if(ret)
 {
  return E_DB_CURSOR_OPEN;
 }
 while(1)
 {
  memset(&cfgshopfee,0,sizeof cfgshopfee);
  ret = DB_t_cfgshopfee_fetch_select_by_c1(&cfgshopfee);
  if(ret)
  {
   if(DB_NOTFOUND == ret)
   {
    if(!rows)
     return E_DB_CFGSHOPFEE_N;
    break;
   }
   else
   {
    return E_DB_CFGSHOPFEE_R;
   }
  }
  rows++;
  do { buf[ (cfgshopfee.feetype-1) / (sizeof(unsigned char) * 8) ] |= (1 << ((sizeof(unsigned char) * 8) - 1 - (cfgshopfee.feetype-1) % (sizeof(unsigned char) * 8))); } while(0);
 }

 memset(&tMsg,0,sizeof tMsg);
 tMsg.pfuncno=iRequest;
 tMsg.funcno= 950041;
 tMsg.msglevel = 1;
 tMsg.deviceid= tDevice.deviceid;
 for(i = 0,j = 0;i < sizeof buf;++i,j+=2)
 {
  sprintf(cardlist+j,"%02x",buf[i]);
 }
 int iFeerate=D4U5(feerate*100,0);
 AddXmlItemInt(tMsg.reqdata,XML_KEY_FEE,iFeerate);
 AddXmlItemStr(tMsg.reqdata,XML_KEY_CARDRIGHTTYPE,cardlist);
 tMsg.maxsendcnt = 5;
 if((ret = AddMsgLst(&tMsg)))
 {
  return ret;
 }
 strcpy(out_pack->vsmess,"成功");
 strcpy(szMsg,"成功");
 PutRow(handle,out_pack,pRetCode,szMsg);
 return 0;
}
