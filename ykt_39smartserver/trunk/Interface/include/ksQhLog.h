
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSQHLOG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSQHLOG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __KSQHLOG_H
#define __KSQHLOG_H

#include "log.h"
#include "cpack.h"
const	int	LOG_APPCPACKCID				= 12;
const	char	LOG_APPCPACKCNAME[LOG_APPMAXNAME]	= "CPACKC����־";

#ifdef _DEBUG
#pragma comment(lib,"../lib/KSLOGd.lib")
#pragma message("Automatically Linking KSLOGd.dll")
#else
#pragma comment(lib,"../lib/KSLOG.lib")
#pragma message("Automatically Linking KSLOG.dll")
#endif

#ifdef KSQHLOG_EXPORTS
#define KSQHLOG_API __declspec(dllexport)
#else
#define KSQHLOG_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksQhLogd.lib")
#pragma message("Automatically Linking ksQhLogd.dll")
#else
#pragma comment(lib,"../lib/ksQhLog.lib")
#pragma message("Automatically Linking ksQhLog.dll")
#endif
#endif

// This class is exported from the ksQhLog.dll
class KSQHLOG_API CKsQhLog : public CLog{
public:
	BOOL WriteDataWithCPackArray(ST_CPACK *pPack,ST_PACK *pArray,LPCSTR pszPackHint="CPACKC���ݰ�");
	BOOL WriteDataWithCPack(ST_CPACK *pPack,LPCSTR pszPackHint="CPACKC���ݰ�");
	BOOL WritePackC(void *pBuf, int nBufLen, LPCSTR pszPackHint="CPACKC���ݰ�");
	CKsQhLog(void);
	virtual ~CKsQhLog();
	// TODO: add your methods here.
};
#ifdef __cplusplus
extern "C" {
#endif
//��־��ʼ������
//���������
//szAppName:Ӧ�ó����Ӣ�ļ�ƣ����ɵ���־�ļ�����ΪszAppName+YYYYMMDD.klg
//szLogFilePath:��־�ļ���Ŀ¼�����Ŀ¼�������ܹ��Զ�����
//nFileHoldCount:��־Ŀ¼�±�������־�ļ����������Ϊ0��������
//����
//TRUE:�ɹ�
//FALSE:ʧ��
BOOL KSQHLOG_API WINAPI AppLogInit(char *szAppName,char *szLogFilePath,int nFileHoldCount=0);

//��¼�ַ�����־
//���������
//szLogContent:�ַ�����Ϣ
//����
//TRUE:�ɹ�
//FALSE:ʧ��
BOOL KSQHLOG_API WINAPI AppWriteLog(char *szLogContent);

//��¼cpack����־
//���������
//pBuf:cpack��ѹ����Ļ���
//nBufLen:�����С
//szPackHint:���cpack��������
//����
//TRUE:�ɹ�
//FALSE:ʧ��
BOOL KSQHLOG_API WINAPI AppWriteCommPack(void *pBuf, int nBufLen, char *szPackHint="ͨѶ������");

//��¼cpack����־-��ѹ����ʽ-����¼��ʽ
//���������
//pPack:cpack��ָ��
//szPackHint:���cpack��������
//���أ�
//TRUE:�ɹ�
//FALSE:ʧ��
BOOL KSQHLOG_API WINAPI AppWriteDataWithCPack(ST_CPACK *pPack, LPCSTR szPackHint="CPACKC���ݰ�");

//��¼cpack����־-��ѹ����ʽ-���¼��ʽ
//���������
//pPack:cpack��ָ��
//pArray:������¼����ָ��
//szPackHint:���cpack��������
//���أ�
//TRUE:�ɹ�
//FALSE:ʧ��
BOOL KSQHLOG_API WINAPI AppWriteDataWithCPackArray(ST_CPACK *pPack, ST_PACK *pArray, LPCSTR szPackHint="CPACKC���ݰ�");

//�ر���־����
//����
//TRUE:�ɹ�
//FALSE:ʧ��
BOOL KSQHLOG_API WINAPI AppLogClose();
#ifdef __cplusplus
}
#endif
#endif
