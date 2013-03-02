/********************************************************************
	created:	2008/08/19
	created:	19:8:2008   14:41
	filename: 	D:\proj\ksbass\bcclink\bccclt\bccclt.cpp
	file path:	D:\proj\ksbass\bcclink\bccclt
	file base:	bccclt
	file ext:	cpp
	author:		Yonghua.Chen
	
	purpose:	由于在不同平台下（Windows，AIX，HP-UX等），都会有BCCClt和BCCSvr的混用情况，
   因此，内部的类，如CXPData必须和BCCSvr中的进行区分。目前已经发现在HP-UX的aCC下，两个so
   混用的情况下，如果BCCClt中的CXPData和BCCSvr中CXPData采用相同的命名，那么就会出现混乱。
   为此，在2008-8-19 14:45:45，将本模块中的CXPData进行了重新命名。
   由此也需要将CDRTP
*********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
//#include "com_kingstar_bcc_bccclt.h"
#include "XPack.h"
#include "XPData.h"
#include "mutex.h"
#include "DRTPRouter.h"
#include "bccclt.h"
#include "nbccclt.h"

#define MAXXPACKS 100

//typedef jlong XPHANDLE;
typedef void* XPHANDLE;

FILE *g_fpLog=NULL;
int g_logDate=0;

#include <sys/stat.h>

#ifdef WIN32
#include <direct.h>
#else
#include <sys/types.h>
#include <dirent.h>
#endif

//////////////////////////////////////////////////////////////////////
bool CheckPath(char *path)
{
   if (access(path,0)!=0)
   {
#ifdef WIN32
      if (mkdir(path)!=0)
#else
      if (mkdir(path,0777)!=0)
#endif
      {
         printf("Cannot create direct <%s> - error:%d <%s>!\n",path,errno,strerror(errno));
         return(false);
      }
   }
   return(true);
}



void Debug_FileOut(char *file,char *fmt,...);

#define BCCDBGPATH "bclog"
void OpenBCLog(int logdate)
{
   char logfile[1024];
   if (g_fpLog!=NULL)
      fclose(g_fpLog);
   sprintf(logfile,"%s/%d.log",BCCDBGPATH,logdate);
   g_fpLog = fopen(logfile,"a+t");
   g_logDate = logdate;
}

bool CheckDebugLog()
{
   if (g_fpLog==NULL)
      return(false);
   time_t timet;
   struct tm tmloc;
   time(&timet);
   memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
   int logdate = ((tmloc.tm_year+1900)*100+tmloc.tm_mon+1)*100+tmloc.tm_mday;
   if (logdate!=g_logDate)
   {
      OpenBCLog(logdate);
   }
   return(g_fpLog!=NULL);
}

void BCSetDebugSwitch(bool bDebug)
{
   if (bDebug)
   {
      time_t timet;
      time(&timet);
      CheckPath(BCCDBGPATH);
      struct tm tmloc;
      memcpy(&tmloc,localtime(&timet),sizeof(tmloc));
      int logdate = ((tmloc.tm_year+1900)*100+tmloc.tm_mon+1)*100+tmloc.tm_mday;
      OpenBCLog(logdate);
   }
   else 
   {
      if (g_fpLog!=NULL)
      {
         fclose(g_fpLog);
         g_fpLog = NULL;
      }
   }
}

void SetDebugSwitch(bool bDebug)
{
   BCSetDebugSwitch(bDebug);
}


CBCXPData *OpenNewXPData(const char *XPackName);

CBCXPData * GetXPData(XPHANDLE handle);


bool XPackInit(int maxXPackDefs)
{
   return (maxXPackDefs<=MAXXPACKS);
}

bool IsValidHandle(BCHANDLE Handle)
{
   return(Handle!=NULL && Handle->m_iClassID==XPD_CLTID);
}

BCHANDLE BCNewHandle(const char * XpackDescribleFile)
{
   return(OpenNewXPData(XpackDescribleFile));
}

BCHANDLE NewXpackHandle(const char * XpackDescribleFile)
{
   return(OpenNewXPData(XpackDescribleFile));
}

bool BCResetHandle(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      Handle->Reset();
      return(true);
   }
   else
      return(false);
}

bool ResetPackHandle(BCHANDLE Handle)
{
   return(BCResetHandle(Handle));
}

bool BCCopyHandle(BCHANDLE SourceHandle,BCHANDLE DestHandle)
{
   if (IsValidHandle(SourceHandle) && IsValidHandle(DestHandle))
   {
      memcpy(DestHandle,SourceHandle,sizeof(CBCXPData));
      return(true);
   }
   else
      return(false);
}

bool CopyHandle(BCHANDLE SourceHandle,BCHANDLE DestHandle)
{
   return(BCCopyHandle(SourceHandle,DestHandle));
}

bool BCDeleteHandle(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      Handle->m_iClassID=0;
      delete Handle;
      return(true);
   }
   else
   {
      return(false);
   }
}

bool DeleteXpackHandle(BCHANDLE Handle)
{
   return(BCDeleteHandle(Handle));
}

int BCGetFieldTypeByName(BCHANDLE Handle,char * FieldName)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetFieldType(FieldName));
   }
   else
      return(-2);
}

int GetFieldTypeByName(BCHANDLE Handle,char * FieldName)
{
   return(BCGetFieldTypeByName(Handle,FieldName));
}

bool BCGetIntFieldByName(BCHANDLE Handle,int Row,char * FieldName,int * Value)
{
   if (IsValidHandle(Handle))
   {
      long value;
      if (Handle->GetIntField(Row,FieldName,&value))
      {
         *Value = value;
         return(true);
      }
   }
   return(false);
}

bool GetIntFieldByName(BCHANDLE Handle,int Row,char * FieldName,int * Value)
{
   return(BCGetIntFieldByName(Handle,Row,FieldName,Value));
}

bool BCGetDoubleFieldByName(BCHANDLE Handle,int Row,char * FieldName,double * Value)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetDoubleField(Row,FieldName,Value));
   }
   return(false);
}

bool GetDoubleFieldByName(BCHANDLE Handle,int Row,char * FieldName,double * Value)
{
   return(BCGetDoubleFieldByName(Handle,Row,FieldName,Value));
}

bool BCGetStringFieldByName(BCHANDLE Handle,int Row,char * FieldName,char * Value,int ValueBufferSize)
{
   if (IsValidHandle(Handle) && ValueBufferSize>0)
   {
      char value[520];
      if (Handle->GetStringField(Row,FieldName,value))
      {
         memcpy(Value,value,ValueBufferSize>sizeof(value)?sizeof(value):ValueBufferSize);
         return(true);
      }
   }
   return(false);
}

bool GetStringFieldByName(BCHANDLE Handle,int Row,char * FieldName,char * Value,int ValueBufferSize)
{
   return(BCGetStringFieldByName(Handle,Row,FieldName,Value,ValueBufferSize));
}
	
bool BCSetIntFieldByName(BCHANDLE Handle,int Row,char * FieldName,int Value)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->SetIntField(Row,FieldName,Value));
   }
   return(false);
}

bool SetIntFieldByName(BCHANDLE Handle,int Row,char * FieldName,int Value)
{
   return(BCSetIntFieldByName(Handle,Row,FieldName,Value));
}

bool BCSetDoubleFieldByName(BCHANDLE Handle,int Row,char * FieldName,double Value)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->SetDoubleField(Row,FieldName,Value));
   }
   return(false);
}

bool SetDoubleFieldByName(BCHANDLE Handle,int Row,char * FieldName,double Value)
{
   return(BCSetDoubleFieldByName(Handle,Row,FieldName,Value));
}


bool BCSetStringFieldByName(BCHANDLE Handle,int Row,char * FieldName,char * Value)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->SetStringField(Row,FieldName,Value));
   }
   return(false);
}

bool SetStringFieldByName(BCHANDLE Handle,int Row,char * FieldName,char * Value)
{
   return(BCSetStringFieldByName(Handle,Row,FieldName,Value));
}

bool BCSetRequestType(BCHANDLE Handle,int RequestType)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->SetRequestType(RequestType));
   }
   return(false);
}

bool SetRequestType(BCHANDLE Handle,int RequestType)
{
   return(BCSetRequestType(Handle,RequestType));
}

bool IsEof(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->IsEof());
   }
   return(true);
}

bool BCGetRecordCount(BCHANDLE Handle,int * RecordCount)
{
   if (IsValidHandle(Handle))
   {
      *RecordCount = Handle->GetRecordCount();
      return(true);
   }
   return(false);
}

bool GetRecordCount(BCHANDLE Handle,int * RecordCount)
{
   return(BCGetRecordCount(Handle,RecordCount));
}

bool BCGetRetCode(BCHANDLE Handle,int * RetCode)
{
   if (IsValidHandle(Handle))
   {
      *RetCode = Handle->GetRetCode();
      return(true);
   }
   return(false);
}

bool GetRetCode(BCHANDLE Handle,int * RetCode)
{
   return(BCGetRetCode(Handle,RetCode));
}

int BCGetPrivateFunctionForNext(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetPrivateFunctionForNext());
   }
   return(-1);
}

int GetPrivateFunctionForNext(BCHANDLE Handle)
{
   return(BCGetPrivateFunctionForNext(Handle));
}

int BCGetBranchNoForNext(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetBranchNoForNext());
   }
   return(-1);
}

int GetBranchNoForNext(BCHANDLE Handle)
{
   return(BCGetBranchNoForNext(Handle));
}

bool SetRecordCount(BCHANDLE Handle,int RecordCount)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->SetRecordCount(RecordCount));
   }
   return(false);
}

bool BCSetMaxRetCount(BCHANDLE Handle,int MaxRetCount)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->SetMaxRetCount(MaxRetCount));
   }
   return(false);
}

bool SetMaxRetCount(BCHANDLE Handle,int MaxRetCount)
{
   return(BCSetMaxRetCount(Handle,MaxRetCount));
}

int BCGetXPackType(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetXPackType());
   }
   return(-1);
}

int GetXPackType(BCHANDLE Handle)
{
   return(BCGetXPackType(Handle));
}


bool BCIsValidField(BCHANDLE Handle, int Row, char *FieldName)
{
   if (IsValidHandle(Handle))
   {
      if (Row>=0 && Row<Handle->GetRecordCount())
      {
         return(Handle->IsValidColumn(FieldName));
      }
   }
   return(false);
}

#define MAXRAWLEN 7998
bool BCSetRawRecord(BCHANDLE Handle, int Row, char * RawData, int RawDataLength)
{
   if (IsValidHandle(Handle) && RawDataLength<=MAXRAWLEN && RawDataLength>=0)
   {
      return(Handle->SetRawRecord(Row,RawData,RawDataLength));
   }
   return(false);
}

bool SetRawRecord(BCHANDLE Handle, int Row, char * RawData, int RawDataLength)
{
   return(BCSetRawRecord(Handle,Row,RawData,RawDataLength));
}

int BCGetRawRecord(BCHANDLE Handle, int Row, char * RawData, int RawDataSize)
{
   if (IsValidHandle(Handle))
   {
      ST_SDPACK *psd = Handle->GetRawRecord(Row);
      if (psd!=NULL)
      {
         if (RawDataSize<psd->usDataLength)
            return(-1);
         if (psd->usDataLength>0)
            memcpy(RawData,psd->data,psd->usDataLength);
         return(psd->usDataLength);
      }
      return(-2);
   }
   return(-3);
}

int GetRawRecord(BCHANDLE Handle, int Row, char * RawData, int RawDataSize)
{
   return(BCGetRawRecord(Handle,Row,RawData,RawDataSize));
}

int BCGetMaxColumn(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetMaxColumn());
   }
   return(-2);
}

int GetMaxColumn(BCHANDLE Handle)
{
   return(BCGetMaxColumn(Handle));
}

int BCGetFieldColumn(BCHANDLE Handle, char * FieldName)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->GetFieldColumn(FieldName));
   }
   return(-2);
}

int GetFieldColumn(BCHANDLE Handle, char * FieldName)
{
   return(BCGetFieldColumn(Handle,FieldName));
}

bool BCGetFieldInfo(BCHANDLE Handle,int Col, char * FieldName, int * FieldType, int * FieldLength)
{
   if (IsValidHandle(Handle))
   {
      int fieldtype,fieldlen;
      if (Handle->GetFieldInfo(Col,FieldName,fieldtype,fieldlen))
      {
         *FieldType = fieldtype;
         *FieldLength = fieldlen;
         return(true);
      }
   }
   return(false);
}

bool GetFieldInfo(BCHANDLE Handle,int Col, char * FieldName, int * FieldType, int * FieldLength)
{
   return(BCGetFieldInfo(Handle,Col,FieldName,FieldType,FieldLength));
}

bool BCHaveNextPack(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->HaveNextPack());
   }
   return(false);
}

bool HaveNextPack(BCHANDLE Handle)
{
   return(BCHaveNextPack(Handle));
}

bool BCCallRequest(BCHANDLE Handle, int drtpno, int branchno,int function, int timeout, int *errcode,char * errormessage)
{
   *errcode = -1000;
   if (IsValidHandle(Handle))
   {
      return(Handle->CallRequest(drtpno,branchno,function,timeout,*errcode,errormessage));
   }
   strcpy(errormessage,"Irregular XPack Handle!");
   return(false);
}

bool CallRequest(BCHANDLE Handle, int drtpno, int branchno,int function, int timeout, int *errcode,char * errormessage)
{
   return(BCCallRequest(Handle, drtpno, branchno,function, timeout, errcode,errormessage));
}

bool BCCallNext(BCHANDLE Handle, int timeout, int* errcode,char * errormessage)
{
   *errcode = -1000;
   if (IsValidHandle(Handle))
   {
      return(Handle->CallNext(timeout,*errcode,errormessage));
   }
   strcpy(errormessage,"Irregular XPack Handle!");
   return(false);
}

bool CallNext(BCHANDLE Handle, int timeout, int* errcode,char * errormessage)
{
   return(BCCallNext(Handle,timeout,errcode,errormessage));
}

int BCEmulateMaxRows(BCHANDLE Handle)
{
   if (IsValidHandle(Handle))
   {
      return(Handle->EmulateMaxRows());
   }
   return(-1);
}

int EmulateMaxRows(BCHANDLE Handle)
{
   return(BCEmulateMaxRows(Handle));
}


bool BCBroad(BCHANDLE Handle, int drtpno, int destno, int funcno, int *errcode, char *errmsg)
{
   *errcode = -1000;
   if (IsValidHandle(Handle))
   {
      return(Handle->Broad(drtpno,destno,funcno,*errcode,errmsg));
   }
   strcpy(errmsg,"Irregular XPack Handle!");
   return(false);
}

bool Broad(BCHANDLE Handle, int drtpno, int destno, int funcno, int *errcode, char *errmsg)
{
   return(BCBroad(Handle,drtpno,destno,funcno,errcode,errmsg));
}

//////////////////////////////////////////////////////////////////////////
/*
void JString_CChar(JNIEnv *env, jbyteArray jstr, char *cstr, int maxcslen)
{
   jsize len = env->GetArrayLength(jstr);
   if (len>maxcslen)
      len = maxcslen;
   env->GetByteArrayRegion(jstr,0,len,(jbyte *)cstr);
   cstr[len]='\0';
}

#define JField_CField(env,FieldName,fieldname) {JString_CChar(env,FieldName,fieldname,32);}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_XPackInit
  (JNIEnv *env, jobject obj, jint MaxXPackDefs)
{
   return(XPackInit(MaxXPackDefs));
}

JNIEXPORT XPHANDLE JNICALL Java_com_kingstar_bcc_bccclt_NewXpackHandle
  (JNIEnv *env, jobject obj, jbyteArray XpackDescribleFile)
{
   char xpackname[1024];
   XPHANDLE handle;
   JString_CChar(env,XpackDescribleFile,xpackname,sizeof(xpackname)-1);
   handle = (XPHANDLE)OpenNewXPData(xpackname);
   Debug_FileOut("NewXpackHandle","OpenNewXPData(...,'%s')=%ld",xpackname,handle);
   return(handle);   
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_ResetPackHandle
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   CBCXPData *pData = GetXPData(Handle);
   return(BCResetHandle(pData));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_CopyHandle
  (JNIEnv *env, jobject obj, XPHANDLE SourceHandle, XPHANDLE DestHandle)
{
   return(BCCopyHandle(GetXPData(SourceHandle),GetXPData(DestHandle)));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_DeleteXpackHandle
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(BCDeleteHandle(GetXPData(Handle)));
}


/* ****** Updated by CHENYH at 2005-11-12 16:56:05 ****** 
-1: 错误的Col；-2: 错误的Handle
0 - None; 1-char; 2-vs_char; 3-unsigned char; 4-int; 5-double
*******************************************************/
/*
JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetFieldTypeByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Col)
{
   CBCXPData *pData = GetXPData(Handle);
   if (IsValidHandle(pData))
   {
      return(pData->GetFieldType(Col));
   }
   return(-2);
}

JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetFieldTypeByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jbyteArray FieldName)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   return(GetFieldTypeByName(GetXPData(Handle),fieldname));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetIntFieldByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jint Col, jintArray Value)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      long value;
      if (!pData->GetIntField(Row,Col,&value))
         return(false);
	  jint jval=value;
      env->SetIntArrayRegion(Value,0,1,&jval);
      return(true);
   }
   return(false);
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetDoubleFieldByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jint Col, jdoubleArray Value)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      double value;
      if (!pData->GetDoubleField(Row,Col,&value))
         return(false);
      env->SetDoubleArrayRegion(Value,0,1,&value);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetStringFieldByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jint Col, jbyteArray Value, jint ValueBufferSize)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      char value[512]={0};
      jsize len;
      if (!pData->GetStringField(Row,Col,value))
         return(false);
      len = sizeof(value);
      if (len>ValueBufferSize)
         len = ValueBufferSize;
      env->SetByteArrayRegion(Value,0,len,(jbyte *)value);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetIntFieldByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray FieldName, jintArray Value)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   int ivalue;
   if (BCGetIntFieldByName(GetXPData(Handle),Row,fieldname,&ivalue))
   {
      jint value = ivalue;
      env->SetIntArrayRegion(Value,0,1,&value);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetDoubleFieldByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray FieldName, jdoubleArray Value)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   double value;
   if (BCGetDoubleFieldByName(GetXPData(Handle),Row,fieldname,&value))
   {
      env->SetDoubleArrayRegion(Value,0,1,&value);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetStringFieldByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray FieldName, jbyteArray Value, jint ValueBufferSize)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   char value[520]={0};
   if (BCGetStringFieldByName(GetXPData(Handle),Row,fieldname,value,sizeof(value)))
   {
      env->SetByteArrayRegion(Value,0,ValueBufferSize>(int)sizeof(value)?sizeof(value):ValueBufferSize,(jbyte *)value);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetIntFieldByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jint Col, jint Value)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      return(pData->SetIntField(Row,Col,Value));
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetDoubleFieldByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jint Col, jdouble Value)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      return(pData->SetDoubleField(Row,Col,Value));
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetStringFieldByCol
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jint Col, jbyteArray Value)
{
   CBCXPData *pData = GetXPData(Handle);
   char value[257];
   JString_CChar(env,Value,value,sizeof(value)-1);
   if (pData!=NULL)
   {
      return(pData->SetStringField(Row,Col,value));   
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetIntFieldByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray FieldName, jint Value)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   return(BCSetIntFieldByName(GetXPData(Handle),Row,fieldname,Value));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetDoubleFieldByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray FieldName, jdouble Value)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   return(BCSetDoubleFieldByName(GetXPData(Handle),Row,fieldname,Value));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetStringFieldByName
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray FieldName, jbyteArray Value)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   char value[520];
   JString_CChar(env,Value,value,sizeof(value)-1);
   return(BCSetStringFieldByName(GetXPData(Handle),Row,fieldname,value));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetRequestType
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint RequestType)
{
   return(BCSetRequestType(GetXPData(Handle),RequestType));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_IsEof
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(IsEof(GetXPData(Handle)));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetRecordCount
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jintArray RecordCount)
{
   int reccount;
   if (BCGetRecordCount(GetXPData(Handle),&reccount))
   {
      jint jrc=reccount;
      env->SetIntArrayRegion(RecordCount,0,1,&jrc);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetRetCode
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jintArray RetCode)
{
   int retcode;
   if (BCGetRetCode(GetXPData(Handle),&retcode))
   {
      jint rcode=retcode;
      env->SetIntArrayRegion(RetCode,0,1,&rcode);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_EnCodeXpackForRequest
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jbyteArray PackBuffer, jint PackBufferSize, jintArray PackDataLength)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      char buf[MAXENCODEBUFSIZE];
      jint blen;
      if (PackBufferSize>MAXENCODEBUFSIZE)
         PackBufferSize = MAXENCODEBUFSIZE;
      blen = pData->EncodeXPackForRequest(buf,PackBufferSize);
      if (blen<(int)sizeof(ST_PACKHEAD))
         return(false);
      env->SetByteArrayRegion(PackBuffer,0,blen,(jbyte *)buf);
      env->SetIntArrayRegion(PackDataLength,0,1,&blen);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_EnCodeXpackForNext
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jbyteArray PackBuffer, jint PackBufferSize, jintArray PackDataLength)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      char buf[MAXENCODEBUFSIZE];
      jint blen;
      if (PackBufferSize>MAXENCODEBUFSIZE)
         PackBufferSize = MAXENCODEBUFSIZE;
      blen = pData->EncodeXPackForNext(buf,PackBufferSize);
      if (blen<(int)sizeof(ST_PACKHEAD))
         return(false);
      env->SetByteArrayRegion(PackBuffer,0,blen,(jbyte *)buf);
      env->SetIntArrayRegion(PackDataLength,0,1,&blen);
      return(true);
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_DeCodeXpack
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jbyteArray PackData, jint PackDataLength)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      char buf[MAXENCODEBUFSIZE];
      JString_CChar(env,PackData,buf,sizeof(buf)-1);
      return(pData->DecodeXPack(buf,PackDataLength));   
   }
   return(false);
}


JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetPrivateFunctionForNext
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(BCGetPrivateFunctionForNext(GetXPData(Handle)));
}


JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetBranchNoForNext
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(BCGetBranchNoForNext(GetXPData(Handle)));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetRecordCount
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint RecordCount)
{
   return(SetRecordCount(GetXPData(Handle),RecordCount));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetMaxRetCount
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint MaxRetCount)
{
   return(BCSetMaxRetCount(GetXPData(Handle),MaxRetCount));
}


JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetXPackType
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(BCGetXPackType(GetXPData(Handle)));
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetRawRecord
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray RawData, jint RawDataLength)
{
   CBCXPData *pData = GetXPData(Handle);
   if (IsValidHandle(pData) && RawDataLength<=MAXRAWLEN && RawDataLength>=0)
   {
      char buf[8192];
      ST_SDPACK *psd=(ST_SDPACK *)buf;
      env->GetByteArrayRegion(RawData,0,RawDataLength,(jbyte *)psd->data);
      psd->usDataLength = (unsigned short)RawDataLength;
      return(pData->SetRawRecord(Row,psd));
   }
   return(false);
}


JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetRawRecord
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Row, jbyteArray RawData, jint RawDataSize)
{
   char buf[8192];
   int rc = BCGetRawRecord(GetXPData(Handle),Row,buf,RawDataSize);
   if (rc>0)
   {
      env->SetByteArrayRegion(RawData,0,rc,(jbyte *)buf);
   }
   return(rc);
}

JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetMaxColumn
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(BCGetMaxColumn(GetXPData(Handle)));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_IsValidColumn
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Col)
{
   CBCXPData *pData = GetXPData(Handle);
   if (pData!=NULL)
   {
      return(pData->IsValidColumn(Col));
   }
   return(false);
}

JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_GetFieldColumn
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jbyteArray FieldName)
{
   char fieldname[33]={0};
   JField_CField(env,FieldName,fieldname);
   return(BCGetFieldColumn(GetXPData(Handle),fieldname));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_GetFieldInfo
  (JNIEnv *env, jobject obj, XPHANDLE Handle, jint Col, jbyteArray FieldName, jintArray FieldType, jintArray FieldLength)
{
   char fieldname[33]={0};
   int fieldtype,fieldlen;
   if (BCGetFieldInfo(GetXPData(Handle),Col,fieldname,&fieldtype,&fieldlen))
   {
      jsize jlen = strlen(fieldname)+1;
      env->SetByteArrayRegion(FieldName,0,jlen,(jbyte *)fieldname);
      jint fv;
      fv = fieldtype;
      env->SetIntArrayRegion(FieldType,0,1,&fv);
      fv = fieldlen;
      env->SetIntArrayRegion(FieldLength,0,1,&fv);
      return(true);         
   }
   return(false);
}


JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_HaveNextPack
  (JNIEnv *env, jobject obj, XPHANDLE Handle)
{
   return(BCHaveNextPack(GetXPData(Handle)));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_BCCCLTInit
  (JNIEnv *env, jobject obj, jint maxnodes)
{
   return(BCCCLTInit(maxnodes));
}

JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_AddDrtpNode
  (JNIEnv *env, jobject obj, jbyteArray ip, jint port)
{
   char ipadd[MAXIPLENGTH]={0};
   JString_CChar(env,ip,ipadd,MAXIPLENGTH-1);
   return(BCAddDrtpNode(ipadd,port));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_CallRequest
  (JNIEnv *env, jobject obj, jlong Handle, jint drtpno, jint branchno, jint function, jint timeout, jintArray errcode, jbyteArray errormessage)
{
   CBCXPData *pData = GetXPData(Handle);
   char errmsg[MAXERRMSGLENGTH]={0};
   int ecode=0;
   if (IsValidHandle(pData))
   {
      pData->CallRequest(drtpno,branchno,function,timeout,ecode,errmsg);
   }
   else
   {
      ecode = -1000;
      strcpy(errmsg,"Irregular XPack Handle!");
   }
   jint jecode=ecode;
   env->SetIntArrayRegion(errcode,0,1,&jecode);
   int len=env->GetArrayLength(errormessage);
   if (len>strlen(errmsg)+1)
      len = strlen(errmsg+1);
   env->SetByteArrayRegion(errormessage,0,len,(jbyte *)errmsg);
   return(ecode==0);
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_CallNext
  (JNIEnv *env, jobject obj, jlong Handle, jint timeout, jintArray errcode, jbyteArray errormessage)
{
   CBCXPData *pData = GetXPData(Handle);
   char errmsg[MAXERRMSGLENGTH];
   int ecode=0;
   if (IsValidHandle(pData))
   {
      pData->CallNext(timeout,ecode,errmsg);
   }
   else
   {
      ecode = -1000;
      strcpy(errmsg,"Irregular XPack Handle!");
   }
   jint jecode=ecode;
   env->SetIntArrayRegion(errcode,0,1,&jecode);
   int len=env->GetArrayLength(errormessage);
   if (len>strlen(errmsg)+1)
      len = strlen(errmsg)+1;
   env->SetByteArrayRegion(errormessage,0,len,(jbyte *)errmsg);
   return(ecode==0);
}

JNIEXPORT jint JNICALL Java_com_kingstar_bcc_bccclt_EmulateMaxRows
  (JNIEnv *env, jobject obj, jlong Handle)
{
   return(BCEmulateMaxRows(GetXPData(Handle)));
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_SetDebugSwitch
  (JNIEnv *env, jobject obj, jboolean bDebug)
{
   BCSetDebugSwitch(bDebug!=0);
   return(bDebug!=0);
}

JNIEXPORT jboolean JNICALL Java_com_kingstar_bcc_bccclt_Broad
  (JNIEnv *env, jobject obj, jlong Handle, jint drtpno, jint branchno, jint function, jintArray errcode, jbyteArray errormessage)
{
   CBCXPData *pData = GetXPData(Handle);
   char errmsg[MAXERRMSGLENGTH]={0};
   int ecode=0;
   if (IsValidHandle(pData))
   {
      pData->Broad(drtpno,branchno,function,ecode,errmsg);
   }
   else
   {
      ecode = -1000;
      strcpy(errmsg,"Irregular XPack Handle!");
   }
   jint jecode=ecode;
   env->SetIntArrayRegion(errcode,0,1,&jecode);
   int len=env->GetArrayLength(errormessage);
   if (len>strlen(errmsg)+1)
      len = strlen(errmsg+1);
   env->SetByteArrayRegion(errormessage,0,len,(jbyte *)errmsg);
   return(ecode==0);

}
*/

///////////////////////////////////////////////////////

static int g_nXPacks=0;
static CXPack *g_pXPacks[MAXXPACKS];
static char g_XPackNames[MAXXPACKS][1024];
static CMUTEX g_XPacksMutex;



CBCXPData * GetXPData(XPHANDLE xphandle)
{
   return((CBCXPData *)xphandle);
}

/* ****** Updated by CHENYH at 2005-11-12 21:18:42 ****** 
#define MAXXPDATAS 1000
CBCXPData g_XPData[MAXXPDATAS];

int NewXPData()
{
   int xpd;
   // 找到一个空闲的CBCXPData实例空间：
   for (xpd=0;xpd<MAXXPDATAS;xpd++)
   {
      if (g_XPData[xpd].m_pXPack==NULL)
         break;
   }
   if (xpd>=MAXXPDATAS)
      return(-3);  // 没有空间提供CBCXPData的实例了
   return(xpd);
}
*******************************************************/

CBCXPData * OpenNewXPData(const char *XPackName)
{
   int xpno;
   CBCXPData *pxp;

   CPMUTEX pmutex(&g_XPacksMutex);

   for (xpno=0;xpno<g_nXPacks;xpno++)
   {
      if (strcmp(XPackName,g_XPackNames[xpno])==0)
         break;
   }
   if (xpno>=g_nXPacks)
   {
      xpno = g_nXPacks;
      if (xpno<MAXXPACKS)
      {
         g_nXPacks++;
         strcpy(g_XPackNames[xpno],XPackName);
         g_pXPacks[xpno] = new CXPack;
         if (g_pXPacks[xpno]==NULL||g_pXPacks[xpno]->Initialize(XPackName)<0)
         {
            g_nXPacks--;
            if (g_pXPacks[xpno]!=NULL)
               delete g_pXPacks[xpno];
            return(NULL); // 装载指定格式文件错误
         }
      }
      else 
         return(NULL);  // 需要扩展MAXXPACKS的个数了
   }
   pxp = new CBCXPData;
   if (pxp==NULL)
      return(NULL);
   pxp->m_pXPack = g_pXPacks[xpno];
   return(pxp);
}





