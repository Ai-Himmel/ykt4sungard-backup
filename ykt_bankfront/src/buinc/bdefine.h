/********************************************************************
	created:	2004/02/11
	created:	11:2:2004   14:15
	filename: 	E:\proj\goldmem\gmsvrall\BDefine.h
	file path:	E:\proj\goldmem\gmsvrall
	file base:	BDefine
	file ext:	h
	author:		CHENYH
	
	purpose:	��ģ�����ڶ�������ҵ�����ܱ�����g_BDefines
*********************************************************************/
// BDefine.h: interface for the TBDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)
#define AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cxpack.h"
#include "bupub.h"
#include "comstru.h"
#include "svrlink.h"
#include "logfile.h"

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

// ����ҵ������̣�
// ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��
// ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ
// ����  : ST_PACK *rPack ҵ������������
// ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0
// ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""
typedef int (* APPFUNC)(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *iRetCode,char *szMsg); 

#define INSERT_FUNCTION(funcno,func,comment,coder,pr) {funcno,func,comment,coder,pr,false,0,0,0,0,0},

typedef struct 
{
   unsigned int RequestType;  // �����ܺ�
   APPFUNC  pFunc;            // �����ܺ���ָ�룬��������ڵ�ַ
   char szRTName[80];         // ������ҵ������
   char szProgrammer[20];     // �����Ա��
   int  iPriority;            // ���ȼ� Ŀǰ��Ϊ1,2,3 �Ըߵ���
                              /* ͬʱҲ�����䴦������ȼ�
                                           1 - �����ࣨ���޸����ݵ����󣩻� �ؼ���ѯҵ�� ...
                                           2 - ���ʷ������ݲ�ѯ
                                           3 - ��ʷ������ݲ�ѯ
                              */
   bool bStoped;              // �Ƿ���ʱֹͣ��ҵ��
   unsigned int nSuccess;     // ����ɹ�����
   unsigned int nFail;        // ����ʧ�ܴ���
   double       dTakentime;   // ����ɹ��ۼ�ʱ�� �Ժ���ƣ����ڲ����ڱ�BCC�¸�ҵ��Ĵ����ٶ�
   unsigned int nTt_max;      // �����ʱ��
   unsigned int nTt_min;      // ��С����ʱ��
} TBDefine;

extern TBDefine *g_BDefines;


// ���  : ������ 2006-3-3 11:54:01
// ����  : ��������Ŀ��Ҫ������֯���ȹ��ܵ�ʱ����Ҫ��BU������У��ṩ���ඨ��ĺ����ӿ�
// ����  : int 
// ����  : TRUSERID *handle [IN]: �������󷽵ľ��
// ����  : char *rdata[IN]: �յ���������� ��δ��ѹ�����ݣ�
// ����  : int rdlen[IN]: �յ��������ݵĳ���
// ����  : int *iRetCode [OUT]: ������
// ����  : char *szMsg
typedef int (*XPROCESS_M)(TRUSERID *handle,char *rdata,int rdlen,int *iRetCode, char *szMsg);
extern XPROCESS_M pProcess;

typedef int (*XCALLBDFUNC_M)(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);
extern XCALLBDFUNC_M pCallBDFunc;
typedef int (*XWRITEAPPFUNC)(int bccBaseFuncNo,int bccID);
extern XWRITEAPPFUNC pWriteAppInfo;


/******* Updated by CHENYH at 2005-11-6 12:38:32 *******/
// �������������������������ʵ�֣�
// Ȼ��ͨ��
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);

// ������: WriteAppInfo
// ���  : ������ 2004-3-22 15:34:38
// ����  : BCC���һ�����Ӻõ�BU�����һ��ˢ�º�̨�������Ա�ҵ��ģ�鲿���ܹ�����ش���
// ����  : int 
// ����  : int bccBaseFuncNo
// ����  : int bccID
int WriteAppInfo(int bccBaseFuncNo,int bccID);
/*******************************************************/

// ������: ResetBPFunctions
// ���  : ������ 2004-2-11 22:40:49
// ����  : ���ù��ܱ��еĲ���
// ����  : int :�ǼǵĹ��ܸ���
BUPUB_API int ResetBPFunctions();


// ������: ListBPFunctions
// ���  : ������ 2004-2-11 22:41:18
// ����  : ��ʾ���ܱ��е�ͳ�ƻ򵼳����ļ���
// ����  : int �ǼǵĹ��ܸ���
// ����  : char *bpfile �� NULL �� ����������Ļ����ʾ�����򵼳���ָ���ļ���
BUPUB_API int ListBPFunctions(char *bpfile);


// ������: FindBPFunction
// ���  : ������ 2004-2-11 22:50:46
// ����  : ���ݹ��ܺţ���ѯ��Ӧ�Ĺ��ܱ���
// ����  : int <0:û���ҵ���>=0:�ڹ��ܱ��ж�Ӧ�����
// ����  : unsigned int reqtype �����ܺ�
BUPUB_API int FindBPFunction(unsigned int reqtype);


#ifdef __cplusplus
}
#endif

// ������: BUPubInitialize
// ���  : ������ 2005-11-6 12:43:26
// ����  : ͨ�������Ի����Ա���������ܹ�����ʹ��BUPub��
// ����  : CSvrLink *: ����bupub������ڲ��е�һ��ԭʼʵ��
// ����  : TBDefine *pBDefine �� ��������ṩ�Ĺ����б��嵥
// ����  : XCALLBDFUNC_M pCallFunc �� ��������ṩ��CallBDFunc��ָ��, ����������ַ�ʽ������XPROCESS_M��ʽ�ṩ���ܵ��ȵĻ��������������ΪNULL
// ����  : XWRITEAPPFUNC pWriteApp �� ��������ṩ��WriteAppInfo�ĺ���ָ��
// ����  : CLogFile *pLogFile - ����������ı���־ʵ��ָ��
// ����  : XPROCESS_M process - ��������ṩ������һ�ֹ��ܵ��õķ�ʽ�����ʱ���಻��鹦�ܺţ���Ҫprocess�ڲ�����һЩ��صĹ�����
//                               ���������ֵ��÷�ʽ�Ļ�, ����XALLBDFUNC_M��ʽ������͸�����ΪNULL
BUPUB_API CSvrLink *BUPubInitialize(TBDefine *pBDefine,XCALLBDFUNC_M pCallFunc,XWRITEAPPFUNC pWriteApp,CLogFile *pLogFile,XPROCESS_M process=NULL);

#undef BUPUB_API

#endif // !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)
