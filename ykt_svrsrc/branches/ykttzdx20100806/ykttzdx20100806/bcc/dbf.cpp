// DBF.cpp: implementation of the CDBF class.
//
//////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef WIN32
#include <share.h>
#include <io.h>
#include <sys/locking.h>

#define sh_open(a,b,c)  _sopen(a,b|O_BINARY,c,S_IREAD | S_IWRITE)
#else  // LINUX or UNIX 
#include <unistd.h>
#include <sys/time.h>

#define SH_DENYNO    0x40
#define SH_DENYRW    0x10
#define sh_open(a,b,c)  open(a,b,S_IREAD | S_IWRITE)
#endif
#include <string.h>
#include "dbf.h"

#define LOCK_POSITION 0x40000000L
#define MAX_FILELEN   0x3FFFFFFFL

#define CB_LOCKPOS 0X3B9ACA00L  /* For CLIPPER & DBASE4 lock */

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDBF::CDBF()
{
   handle = -1;
   fvtemp = NULL;
   first = NULL;
   buffer = NULL;
}


CDBF::~CDBF()
{
   d4close();
}

int CDBF::d4close()
{
   if (fvtemp!=NULL)
   {
      delete []fvtemp;
      fvtemp = NULL;
   }
   if (buffer!=NULL) {
      delete [] buffer;
      buffer = NULL;
   }
   if (first!=NULL) {
      delete [] first;
      first = NULL;
   }
   field_no = 0;
   record_no = 0;
   current_recno = 0;
   if (handle!=-1) {
      close(handle);
      handle = -1;
   }
   return(DBF_OK);
}

int CDBF::d4use(char *dname,int dtype,int excl,int acce)
{
   BYTE head[32];
   int i,j;
   unsigned int offset;
   unsigned int maxflen;


   d4close();
   if (dname==NULL||dname[0]=='\0')
      return(DBF_OK);
   if (acce==ACCESS_RDONLY)
      access = O_RDONLY;
   else
      access = O_RDWR;

   int shflag;
   if (excl==EXCL_ON)
      shflag = SH_DENYRW;
   else
      shflag = SH_DENYNO;

   
   handle = sh_open(dname,access,shflag);
   if (handle==-1)
   {
      // Cannot open the DBF file:
      return(DBF_OPENFAIL);      
   }
   else 
   {
      lseek(handle,0,SEEK_END);
      exclusive = excl;
      dbf_type = dtype;
      strcpy(dbf_name,dname);
      lseek(handle,0,SEEK_SET);
      if (read(handle,&version,32)!=32
         || head_len<64)
      {
         d4close();
         return(DBF_HEADERR);             
      }
      field_no = head_len/32-1;
      first =  new TField[field_no];
      if (first == NULL) 
      {
         d4close();
         return(DBF_NOMEM);
      }
      offset = 1;
      maxflen = 1;
      for (i=0;i<field_no;i++)
      {
         read(handle,head,32);
         memcpy(first+i,head,sizeof(TField));
         j = strlen(first[i].name);
         if (j>11) j = 11;
         for (j--;j>=0;j--) 
         {
            if (first[i].name[j]==' ')
               first[i].name[j]=0;
            else break;
         }
         if (maxflen<first[i].len)
            maxflen = first[i].len;
         if (first[i].len<=0||first[i].name[0]==0x0D)
         {
            first[i].len = 0;
            break;
         }
         first[i].address = offset;
         offset += first[i].len;
      }
      field_no = i;
      record_len = offset;      
      buffer = new BYTE[record_len];
      if (buffer==NULL) 
      {
         d4close();
         return(DBF_NOMEM);
      }
      if (maxflen<255)
         maxflen = 255;
      fvtemp = new char[maxflen+1];
      lseek(handle,LOCK_POSITION,SEEK_SET);
      current_recno = 0;
      dbf_buffer(1);
      return(DBF_OK);
   }
}

#ifdef WIN32
#define LT_LOCK      _LK_NBLCK
#define LT_UNLOCK    _LK_UNLCK
int CDBF::locktype(int ltype,DWORD lstart,DWORD len)
{
   _lseek(handle,lstart,SEEK_SET);
   if (_locking(handle,ltype,len)==0)
      return(DBF_OK);
   else
      return(DBF_LOCKFAIL);
}

#else
#define LT_LOCK   F_WRLCK
#define LT_UNLOCK F_UNLCK

int CDBF::locktype(int ltype,DWORD lstart,DWORD len)
{
   struct flock lck;
   lck.l_type = ltype;
   lck.l_whence = SEEK_SET;
   lck.l_start = lstart;
   lck.l_len = len;
   lck.l_pid = getpid();
   if (fcntl(handle,F_SETLK,&lck)==0)
      return(DBF_OK);
   else
      return(DBF_LOCKFAIL);
}
#endif


int CDBF::d4flock()
{
   switch (dbf_type)
   {
      case DBF_FOXBASE:
      case DBF_FOXPRO:
      case DBF_FOXCDX:
         return(locktype(LT_LOCK,LOCK_POSITION,MAX_FILELEN));
      default:
         return(locktype(LT_LOCK,CB_LOCKPOS,CB_LOCKPOS));
   }
}


int CDBF::d4unflock()
{
   switch (dbf_type)
   {
      case DBF_FOXBASE:
      case DBF_FOXPRO:
      case DBF_FOXCDX:
         return(locktype(LT_UNLOCK,LOCK_POSITION,MAX_FILELEN));
      default:
         return(locktype(LT_UNLOCK,CB_LOCKPOS,CB_LOCKPOS));
   }
}

int CDBF::d4rlock()
{
   int rtn;
   switch (dbf_type)
   {
   case DBF_FOXBASE:
      rtn = locktype(LT_LOCK,
         LOCK_POSITION+dbf_rec_pos(current_recno),
         record_len);
      break;
   case DBF_FOXPRO:
      rtn = locktype(LT_LOCK,
         LOCK_POSITION+dbf_rec_pos(current_recno),
         1);
      break;
   case DBF_FOXCDX:
      rtn = locktype(LT_LOCK,
         LOCK_POSITION+MAX_FILELEN-current_recno,
         1);
      break;
   default:
      rtn = locktype(LT_LOCK,
         CB_LOCKPOS+current_recno,
         1);
      break;
   }
   if (rtn==DBF_OK)
   {
      dbf_buffer(current_recno);
   }
   return(rtn);
}

DWORD CDBF::dbf_rec_pos(DWORD recno)
{
   DWORD offset;
   offset = head_len;
   if (recno<1 || recno>record_no+1)
      return(offset);
   else
      return(offset+(recno-1)*record_len);
}

int CDBF::dbf_buffer(DWORD recno, void *buf)
{
   DWORD offset;
   if (buf==NULL)
      buf = buffer;
   if (recno<1) return(DBF_RECNOERR);
   if (record_no<recno) return(DBF_RECNO_OF);
   offset = dbf_rec_pos(recno);
   if (lseek(handle,offset,SEEK_SET)==-1)
      return(DBF_RECLOCFAIL);
   if (read(handle,buf,record_len)!=record_len)
      return(DBF_READFAIL);
   return(DBF_OK);
}

int CDBF::d4unrlock()
{
   int rtn;
   switch (dbf_type)
   {
   case DBF_FOXBASE:
      rtn = locktype(LT_UNLOCK,
         LOCK_POSITION+dbf_rec_pos(current_recno),
         record_len);
      break;
   case DBF_FOXPRO:
      rtn = locktype(LT_UNLOCK,
         LOCK_POSITION+dbf_rec_pos(current_recno),
         1);
      break;
   case DBF_FOXCDX:
      rtn = locktype(LT_UNLOCK,
         LOCK_POSITION+MAX_FILELEN-current_recno,
         1);
      break;
   default:
      rtn = locktype(LT_UNLOCK,
         CB_LOCKPOS+current_recno,
         1);
      break;
   }
   return(rtn);
}

bool CDBF::reopen_dbf()
{
   if (handle!=-1)
   {
      lseek(handle,0,SEEK_SET);
      return(read(handle,&version,32)==32);
   }
   else return(false);
}

#ifdef WIN32
#define getlocaltime(a,b)   memcpy(b,localtime(a),sizeof(struct tm))
#else
#define getlocaltime(a,b)   localtime_r(a,b)
#endif

int CDBF::dbf_update_head()
{
   struct tm ltm;
   time_t loctime;


   if (handle==-1)
   {
      return(DBF_OPENFAIL);
   }

   time(&loctime);
#ifdef WIN32
   memcpy(&ltm,localtime(&loctime),sizeof(ltm));
#else
   memcpy(&ltm,localtime(&loctime),sizeof(ltm));
   //localtime_r(&loctime,&ltm);
#endif
   //getlocaltime(&loctime,&ltm);
   year = (BYTE)(ltm.tm_year%100);
   month = (BYTE)(ltm.tm_mon);
   day = (BYTE)(ltm.tm_mday);   

   lseek(handle,0,SEEK_SET);
   if (write(handle,&version,32)!=32)
      return(DBF_WRITEFAIL);
   else 
      return(DBF_OK);
}

int CDBF::dbf_wbuffer(DWORD recno, void *buf)
{
   DWORD offset;
   if (handle==-1)
      return(DBF_OPENFAIL);
   if (recno<1) 
      return(DBF_RECNOERR);
   if (record_no+1 < recno) 
      return(DBF_RECNO_OF);
   offset=dbf_rec_pos(recno);
   if (lseek(handle,offset,SEEK_SET)==-1)
      return(DBF_RECLOCFAIL);
   if (write(handle,buf,record_len)!=record_len)
      return(DBF_WRITEFAIL);
   return(DBF_OK);
}

int CDBF::d4append(void *buf)
{
   int rtn;
   BYTE bb[2];
   if (reopen_dbf())
   {
      if (buf!=NULL && buf!=buffer)
         memcpy(buffer,buf,record_len);
      record_no++;
      buffer[0]=' ';
      rtn = dbf_wbuffer(record_no,buffer);
      if (rtn==DBF_OK)
      {
         bb[0]=26;
         write(handle,bb,1);
         dbf_update_head();
         current_recno = record_no;
      }
      else
         current_recno = 0;
      return(rtn);            
   }
   else return(DBF_OPENFAIL);
}

int CDBF::d4go(DWORD recno)
{
   int rtn;
   if (reopen_dbf())
   {
      rtn = dbf_buffer(recno);
      if (rtn==DBF_OK)
         current_recno = recno;
      else
         current_recno = 0;
      return(rtn);      
   }
   else
      return(DBF_OPENFAIL);
}

int CDBF::d4append_blank()
{
   if (buffer==NULL)
      return(DBF_OPENFAIL);
   memset(buffer,' ',record_len);
   return(d4append());
}


int CDBF::d4b_blank()
{
   if (buffer==NULL)
      return(DBF_OPENFAIL);
   memset(buffer,' ',record_len);
   return(DBF_OK);
}

DWORD CDBF::d4reccount()
{
   if (reopen_dbf())
   {
      return(record_no);
   }
   else return(0);
}

DWORD CDBF::d4recno()
{
   return(current_recno);
}

int CDBF::d4reclen()
{
   return(record_len);
}

void CDBF::d4setbuffer(DWORD record, void *buf)
{
   current_recno = record;
   memcpy(buffer,buf,record_len);
}

#ifdef WIN32
#define Strnicmp(a,b,c)  strnicmp(a,b,c)
#else
#define Strnicmp(a,b,c)  strncasecmp(a,b,c)
#endif

TField * CDBF::f4findfield(char *fieldname)
{
   TField *f_ptr;
   int i;
   if (handle==-1) 
      return(NULL);
   f_ptr = first;
   for (i=0;i<field_no;i++)
   {
      if (Strnicmp(fieldname,f_ptr->name,11)==0)
         return(f_ptr);
      f_ptr++;
   }
   return(NULL);
}

TField * CDBF::f4getvalue(char *fieldname, void *value,int valuelen)
{
   TField *f_ptr;
   *(char *)value = '\0';
   f_ptr = f4findfield(fieldname);
   if (f_ptr==NULL)
      return(NULL);
/* ****** Updated by CHENYH at 2003-10-9 22:44:03 ****** 
   if (f_ptr->f_type=='X')
   {
      if (valuelen==0 || valuelen>f_ptr->len)
         valuelen = f_ptr->len;
      if (*(WORD *)(buffer-f_ptr->address)<valuelen)
         valuelen = *(WORD *)(buffer-f_ptr->address);
      memcpy(value,buffer+f_ptr->address+sizeof(WORD),valuelen);
   }
   else
*/
   {
      if (valuelen==0 || valuelen>f_ptr->len)
         valuelen = f_ptr->len;
      memcpy(value,buffer+f_ptr->address,valuelen);
   }
   ((char *)value)[valuelen]='\0';
   return(f_ptr);
}

int CDBF::f4setvalue(char *fieldname, void *value)
{
   TField *f_ptr;
   f_ptr = f4findfield(fieldname);
   if (f_ptr==NULL)
      return(-1);
   memcpy(buffer+f_ptr->address,value,f_ptr->len);
   return(0);
}

void * CDBF::f4bstr(char *fieldname)
{
   if (f4getvalue(fieldname,fvtemp,0)==NULL)
      return(NULL);
   else
      return(fvtemp);
}


char CDBF::f4char(char *fieldname)
{
   if (f4getvalue(fieldname,fvtemp,0)==NULL)
      return(0);
   else
      return(fvtemp[0]);
}



double CDBF::f4double(char *fieldname)
{
   if (f4getvalue(fieldname,fvtemp,0)==NULL)
      return(0);
   else
      return(atof(fvtemp));
}

char * CDBF::f4str(char *fieldname)
{
   f4getvalue(fieldname,fvtemp,0);
   return(fvtemp);
}

int CDBF::f4int(char *fieldname)
{
   f4getvalue(fieldname,fvtemp,0);
   return(atoi(fvtemp));
}

long CDBF::f4long(char *fieldname)
{
   f4getvalue(fieldname,fvtemp,0);
   return(atol(fvtemp));
}


int CDBF::f4ncpy(char *fieldname, void *value, int vlen)
{
   TField *f_ptr;
   f_ptr = f4getvalue(fieldname,fvtemp,0);
   if (f_ptr==NULL)
      return(0);
   else if ((char *)value!=fvtemp)
   {
      memcpy(value,fvtemp,vlen);
   }
   return(f_ptr->len);
}




int CDBF::f4b_str(char *fieldname, char *fvalue)
{
   TField *f_ptr;
   char *pb;
   f_ptr = f4findfield(fieldname);
   if (f_ptr==NULL)
      return(-1);

   pb = (char *)buffer+f_ptr->address;
   switch (f_ptr->f_type)
   {
   case 'C': // string:
      {
         int i;
         for (i=0;i<f_ptr->len;i++)
         {
            if (fvalue[i]=='\0') break;
            pb[i]=fvalue[i];
         }
         for (;i<f_ptr->len;i++)
         {
            pb[i]=' ';
         }
      }
      break;
   case 'F': // Float:
   case 'N': // Numeric:
      {
         char fmt[10];
         sprintf(fmt,"%%%d.%dlf",f_ptr->len,f_ptr->bits);
         sprintf(fvtemp,fmt,atof(fvalue));
         memcpy(pb,fvtemp,f_ptr->len);
      }
      break;
   case 'I': // Integer:
      {
         int i;
         i = atoi(fvalue);
         memcpy(pb,&i,sizeof(int));
      }
      break;
   case 'L': // Logical:
      if (fvalue[0]=='0'||fvalue[0]=='f'||fvalue[0]=='F')
      {
         fvalue[0]='F';
      }
      else
      {
         fvalue[0]='T';
      }
      pb[0]=fvalue[0];
      break;
   case 'D': // Date:
      {
         sprintf(fvtemp,"%08d",atoi(fvalue));
         memcpy(pb,fvtemp,8);
      }
      break;
   case 'B': // Double:
      {
         double dd;
         dd = atof(fvalue);
         memcpy(pb,&dd,sizeof(dd));
      }
      break;
   case 'Y': // Currency:
      {
         int f64;
#ifdef WIN32
         __int64 d64;
#else
         //int64_t d64;
         long long d64;
#endif
         int i,d;
         if (fvalue[0]=='-')
         {
            f64 = -1;
            i = 1;
         }
         else
         {
            f64 = 1;
            i = 0;
         }
         d64 = 0;
         for (;i<256;i++)
         {
            if (fvalue[i]<'0'||fvalue[i]>'9') break;
            d64 = d64*10+fvalue[i]-'0';
         }
         d = 1;
         if (fvalue[i]=='.')
         {
            for (;d<5;d++)
            {
               if (fvalue[i+d]<'0'||fvalue[i+d]>'9') break;
               d64 = d64*10+fvalue[i+d]-'0';
            }
         }
         for (;d<5;d++)
         {
            d64 *= 10;
         }
         d64 *= f64;
         memcpy(pb,&d64,sizeof(d64));
      }
      break;
   case 'X':  // as my binary value
      memcpy(pb,fvalue,f_ptr->len);
      break;
   default:
      return(-2);
   }
   return(f_ptr->f_type);
}

int CDBF::f4b_int(char *fieldname, int data)
{
   char buf[20];
   sprintf(buf,"%d",data);
   return(f4b_str(fieldname,buf));
}


int CDBF::f4b_double(char *fieldname, double data)
{
   char buf[40];
   sprintf(buf,"%.6lf",data);
   return(f4b_str(fieldname,buf));
}


int CDBF::f4b_char(char *fieldname, char c)
{
   char bb[2];
   bb[0]=c; bb[1]='\0';
   return(f4b_str(fieldname,bb));
}

int CDBF::f4b_binary(char *fieldname, void *bin, int blen)
{
   TField *f_ptr;
   WORD binlen;
   char *pb;
   f_ptr = f4findfield(fieldname);
   if (f_ptr==NULL)
      return(-1);
   if (f_ptr->f_type!='X')
      return(-3);
   if (blen<=0)
      binlen = 0;
   else
      binlen = (WORD)blen;
   pb = (char *)buffer+f_ptr->address;
   memcpy(pb,&binlen,sizeof(binlen));
   if (binlen>0)
      memcpy(pb+sizeof(binlen),bin,binlen);
   return('X');
}

int CDBF::f4binary(char *fieldname, void *value, int valuesize)
{
   TField *f_ptr;
   WORD binlen;
   BYTE *pb;
   f_ptr = f4findfield(fieldname);
   if (f_ptr==NULL)
      return(-1);
   if (f_ptr->f_type!='X')
      return(-3);
   pb = (BYTE *)(buffer+f_ptr->address);
   binlen = *(WORD *)(pb);
   if (binlen<valuesize)
   {
      valuesize = binlen;
   }
   if (valuesize>0)
   {
      memcpy(value,pb+sizeof(WORD),valuesize);
   }
   return(binlen);
}

int CDBF::d4putrec(void *buf)
{
   if (buf==NULL)
      buf = buffer;
   return(dbf_wbuffer(current_recno,buf));
}

void CDBF::d4getbuffer(void *buf)
{
   memcpy(buf,buffer,record_len);
}

int CDBF::d4readrecord(unsigned int from, unsigned int records, void *buf)
{
   int recs;
   int rlen;
   reopen_dbf();
   if (from>record_no) 
      return(0);
   recs = record_no-from+1;
   if ((unsigned int)recs>records)
      recs = records;
   lseek(handle,dbf_rec_pos(from),SEEK_SET);
   rlen = read(handle,buf,recs*record_len);
   return(rlen/record_len);
}

bool CDBF::d4eof()
{
   return (current_recno==0);
}

int CDBF::d4next(int next)
{
   DWORD recno = current_recno+next;
   return(d4go(recno));
}

int CDBF::d4end()
{
   reopen_dbf();
   return(d4go(record_no));
}

int CDBF::d4top()
{
   return(d4go(1));
}

int CDBF::dbf_setdeleteflag(char flag)
{
   DWORD offset;

   if (current_recno==0)
      return(DBF_RECNOERR);
   reopen_dbf();
   offset=dbf_rec_pos(current_recno);
   lseek(handle,offset,SEEK_SET);
   write(handle,&flag,1);
   return(dbf_buffer(current_recno,buffer));
}

int CDBF::d4deleterecord()
{
   return(dbf_setdeleteflag('*'));
}

int CDBF::d4undeleterecord()
{
   return(dbf_setdeleteflag(' '));
}

bool CDBF::d4isdeleted()
{
   dbf_buffer(current_recno,buffer);
   return (buffer[0]==' ');
}



int CDBF::d4writerecords(DWORD from, DWORD records, void *buf)
{
   DWORD offset;
   reopen_dbf();
   for (;record_no<from-1;)
   {
      d4append_blank();
   }
   offset = dbf_rec_pos(from);
   lseek(handle,offset,SEEK_SET);
   write(handle,buf,records*record_len);
   if (record_no<from+records-1)
   {
      char bb[2];
      bb[0]=26;
      write(handle,&bb,1);
      record_no = from+records-1;
   }
   dbf_update_head();
   if (d4go(from+records-1)==DBF_OK)
      return(records);
   else
      return(0);
}

bool CDBF::d4used()
{
   if (handle==-1)
      return(false);
   if (buffer==NULL)
      return(false);
   if (fvtemp==NULL)
      return(false);
   if (first==NULL)
      return(false);
   return(true);
}

int CDBF::d4create(char *filename, int fields, TField *fieldlist)
{
	unsigned char buf[32];
   int i,j;
   int offset;

   if (d4used()) 
      return(DBF_USED);
   handle = sh_open(filename,O_CREAT|O_RDWR,SH_DENYNO);
   if (handle==-1) 
      return(DBF_OPENFAIL);

#ifdef F_WORDLEN
   version = 0x10;
#else   
   version = 0x03;
#endif
   record_no = 0;
   offset = 1;
   for (i=0;i<fields;i++)
   {
      j = strlen(fieldlist[i].name);
      if (j>11) j = 11;
      for (;j>=0;j--)
      {
         if (fieldlist[i].name[j]==' ')
            fieldlist[i].name[j]='\0';
         else break;
      }
      fieldlist[i].address = offset;
      switch (fieldlist[i].f_type) 
      {
      case 'F':
      case 'N':
         if (fieldlist[i].len<fieldlist[i].bits+2)
            fieldlist[i].bits = fieldlist[i].len-2;
         if (fieldlist[i].bits+2>fieldlist[i].len)
            fieldlist[i].bits = 0;
         break;
      case 'L':
         fieldlist[i].len = 1;
      default:
         fieldlist[i].bits = 0;
         break;         
      }
      offset += fieldlist[i].len;
   }
   record_len = (WORD)offset;
   record_len = (WORD)offset;
   head_len = (fields+1)*32+1;
   record_no = 0;
   memset(reserved,0,sizeof(reserved));
#ifdef F_WORDLEN
   memcpy(reserved,"CYHLFIELDVER",12);
#endif
   j = dbf_update_head();
   memset(buf,0,sizeof(buf));
   if (j==DBF_OK) 
   {
      for (i=0;i<fields;i++) 
      {
         memcpy(buf,&(fieldlist[i]),sizeof(TField));
         write(handle,buf,32);
      }
      buf[0]=0x0D;
      write(handle,buf,1);
   }
   d4close();
   handle = -1;
   return(j);
}

int CDBF::f4r_field(char *fieldname, void *fieldbuf)
{
   TField *f_ptr;
   DWORD offset;
/* ****** Updated by CHENYH at 2003-10-10 12:17:06 ****** 
   if (d4go(current_recno)!=DBF_OK)
      return(0);
*/
   if (current_recno<=0||handle==-1)
      return(0);
   f_ptr = f4findfield(fieldname);
   if (f_ptr==NULL)
      return(0);
   offset = dbf_rec_pos(current_recno)+f_ptr->address;
   lseek(handle,offset,SEEK_SET);
   return(write(handle,fieldbuf,f_ptr->len));
}

TField * CDBF::f4field(int fieldno)
{
   if (handle==-1)
      return(NULL);
   if (fieldno>=field_no||fieldno<0)
      return(NULL);
   return(first+fieldno);
}
