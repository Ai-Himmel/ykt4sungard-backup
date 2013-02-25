#ifndef __SPXDLLINFO_H__
#define __SPXDLLINFO_H__

#include "SList.h"

typedef BOOL (*FORMPACKFUNC)(int nFunction, char *buffer, CSList *plist, void *pvoid, int DestNO);
typedef BOOL (*FORMSTRFUNC)(int nFunction, char *buffer, CSList *plist, void *pvoid, bool bFirstRow);
typedef BOOL (*INITFUNC)(char *IniFileName);
typedef BOOL (*EXITFUNC)(void);

typedef struct  
{
	int	 nFunction;		// ������SPX���
	char     szName[48];		// ����������
	int	 nRequestType;		// �����ܺ�̨CPACKЭ����
	int      type;          /* �������ͣ�
                                           0 - ����������
                                           1 - ���ʷ������ݲ�ѯ
                                           2 - ��ʷ������ݲ�ѯ
				*/
	FORMPACKFUNC  pFormPackFunc;		// ���̨����ĺ���ָ��
	FORMSTRFUNC  pFormStrFunc;		// ��CPACK���������ǰ̨������صĺ���ָ��
} DLLFUNCENTRY, *LPDLLFUNCENTRY;

typedef  struct 
{
	int		iFuncNum;               // ������Ŀ
	DLLFUNCENTRY	*pDllFunc;		// ����˵��������
	INITFUNC	pFuncInit;		// ��ʼ��������ָ��
	EXITFUNC	pFuncExit;		// �˳�������ָ��
	FORMPACKFUNC	pDefaultFormPackFunc;	// ��CPACK���������ǰ̨������صĺ���ָ��
	FORMSTRFUNC	pDefaultFormStrFunc;	// ���̨����ĺ���ָ��
	int		m_MinFuncNo,m_MaxFuncNo;	// ��С���ܺ�����   ����ܺ�����
	char		m_productName[40];		// ģ������:
						// V7Inter/VCInter
	int		m_Version;			// �汾�� i.e.130:Ver1.30 / 100:Ver1.00
	int		m_BuildDate;			// �������� yyyymmdd
	char		m_programmer[12];		// DLL����Ա  

} DLLINFO, *LPDLLINFO;

#ifdef SPXDLL_EXPORTS
#define SPXDLL_API __declspec(dllexport)
#else
#define SPXDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {  //�ԡ�c����ʽ���룬�Ƿ�ֹ���������������ı�
#endif
      SPXDLL_API DLLINFO *GetDllInfo(void);

#ifdef __cplusplus
}
#endif


#endif //__SPXDLLINFO_H__
