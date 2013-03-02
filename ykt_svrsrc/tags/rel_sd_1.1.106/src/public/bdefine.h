/********************************************************************
	created:	2004/02/11
	created:	11:2:2004   14:15
	filename: 	E:\proj\goldmem\fdsvrall\BDefine.h
	file path:	E:\proj\goldmem\fdsvrall
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

#include "fdsqc.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

#ifdef __cplusplus
}
#endif

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

extern TBDefine g_BDefines[];


/* ****** Updated by CHENYH at 2004-4-9 10:06:44 ****** 
   ����pArrays�� Ϊ���ܹ����մ���������¼�����
*/
int CallBDFunc(int fno,TRUSERID *handle,ST_CPACK *rpack,ST_PACK *pArrays,int *iRetCode, char *szMsg);

// ������: ResetBPFunctions
// ���  : ������ 2004-2-11 22:40:49
// ����  : ���ù��ܱ��еĲ���
// ����  : int :�ǼǵĹ��ܸ���
int ResetBPFunctions();


// ������: ListBPFunctions
// ���  : ������ 2004-2-11 22:41:18
// ����  : ��ʾ���ܱ��е�ͳ�ƻ򵼳����ļ���
// ����  : int �ǼǵĹ��ܸ���
// ����  : char *bpfile �� NULL �� ����������Ļ����ʾ�����򵼳���ָ���ļ���
int ListBPFunctions(char *bpfile);


// ������: FindBPFunction
// ���  : ������ 2004-2-11 22:50:46
// ����  : ���ݹ��ܺţ���ѯ��Ӧ�Ĺ��ܱ���
// ����  : int <0:û���ҵ���>=0:�ڹ��ܱ��ж�Ӧ�����
// ����  : unsigned int reqtype �����ܺ�
int FindBPFunction(unsigned int reqtype);

#endif // !defined(AFX_BDEFINE_H__DC4F6CAA_3CE4_438A_8DCF_D92AF3610688__INCLUDED_)
