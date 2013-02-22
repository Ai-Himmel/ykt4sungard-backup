/*
ver 2.0
		DRTPAPPDLL_API WORD App_GetVer();
		DRTPAPPDLL_API int App_Init(int QueueLen = 20 , int ErrorMode = 0 , void *lp = NULL);
		DRTPAPPDLL_API bool App_Connect(int index , LPSTR ServerIp , short ServerPort , WORD FunctionCount , void *func , int EncryptMode = 0);
		DRTPAPPDLL_API bool App_Recv(int index);
		DRTPAPPDLL_API bool App_ReConnect(int index , int ReConnectDelay = 1);
		DRTPAPPDLL_API int App_Pop(APPHANDLE *handle , LPSTR Data , int len);
		DRTPAPPDLL_API bool App_Send(APPHANDLE *handle , LPSTR Data , int len);
		DRTPAPPDLL_API void App_Close(int index,APPHANDLE *handle = NULL);
		DRTPAPPDLL_API void App_GetLastError(LPSTR error);
ver 2.01
		DRTPAPPDLL_API bool App_RecvDone(LPSTR ServerIp , short ServerPort , WORD FunctionCount , WORD *func);
ver 2.02
		DRTPAPPDLL_API int App_Pop2(APPHANDLE *handle , LPSTR Data , int len);
		DRTPAPPDLL_API bool App_Send2(APPHANDLE *handle , LPSTR Data , int len ,int ColNum , int flag);
ver 2.03
		DRTPAPPDLL_API bool App_Transmit(APPHANDLE *handle , LPSTR Data , int len , int DestNo , WORD MainFunc);
		DRTPAPPDLL_API void App_SetLogFileName(char *filename)
		DRTPAPPDLL_API void App_GetUserHandle(APPHANDLE *handle , char *UserHandle)
*/

#ifndef _DRTPAPPDLL_H
#define _DRTPAPPDLL_H

#if defined(WIN32)
	#ifdef DRTPAPPDLL_EXPORTS
		#define DRTPAPPDLL_API __declspec(dllexport)
	#else
		#define DRTPAPPDLL_API __declspec(dllimport)
	#endif
#else
	#define DRTPAPPDLL_API
	#include "mytypes.h"
	#include <stdlib.h>
#endif

#if !defined(GETLOW)
#define GETDRTPLOW(ver) ((BYTE)(ver>>8)&0xff)
#endif
#if !defined(GETHIGH)
#define GETDRTPHIGH(ver) ((BYTE)ver&0xff)
#endif
#if !defined(MAKEDRTPVER)
#define MAKEDRTPVER(high,low) ((WORD)high|(WORD)low<<8)
#endif

#ifndef DRTPAPPVER
#define DRTPAPPVER		MAKEDRTPVER(2,3)
#endif

#define APPENOREPORT	0
#define APPEPRINTF		1
#define APPEWRITEBUF	2
#define APPEMSGDLG		3

#define USER_MESSAGE_RESULT		2	//���ؽ����������Ӧ������
#define USER_MESSAGE_REPORT		5	//���ر�����Ϣ�����ش�����Ϣ
#define USER_MESSAGE_ENDPACK	12	//�����������������ݷ�����֮�󣬱��뷢�ͽ��������ð������ݣ�len=0

struct APPHANDLE
{
	char buf[64];
};

//�õ��汾��
DRTPAPPDLL_API WORD App_GetVer();

//��ʼ����������socket�����ý��ն��г��ȣ����õ�һ����������index��
//ͨ��������������ͨѶ,(���ñ���ʽ,��δʵ��)
//����-1��ʾʧ��
DRTPAPPDLL_API int App_Init(int QueueLen = 20 , int ErrorMode = 0 , void *lp = NULL);

//����index�������أ�������Կ��ע�Ṧ�ܺ�
//index��App_Init���ص���������
//����ʧ�ܷ���false;
DRTPAPPDLL_API bool App_Connect(int index , LPSTR ServerIp , short ServerPort , WORD FunctionCount , void *func , int EncryptMode = 0);

//������������index�������Ͻ���һ�����ݰ����������յ�������������ն���
//���û�н��յ��������������գ�������<0���ɹ��򷵻�0
//����-2��Ҫ�������ӣ�������Ҫ
DRTPAPPDLL_API int iApp_Recv(int index);

//������������index�������Ͻ���һ�����ݰ����������յ�������������ն���
//���û�н��յ��������������գ�������false���ɹ��򷵻�true
DRTPAPPDLL_API bool App_Recv(int index);

//�������أ�����ʧ��ʱ��ʱReConnectDelay������ԣ�ֱ�����ӳɹ�
//��� ReConnectDelay <= 0 ������ʧ�ܺ����ԣ���false����
DRTPAPPDLL_API bool App_ReConnect(int index , int ReConnectDelay = 1);

//�ӽ��ն�����ȡ���ݣ�APPHANDLE�ɺ��������߷����ڴ棬
//������Ϣ�����浽���ڴ���У��ڷ�����ȫ������֮ǰ�����ڴ治���ͷ�
//����ֵ <= 0 ��ʾ���������ʾȡ�������ݳ���
DRTPAPPDLL_API int App_Pop(APPHANDLE *handle , LPSTR Data , int len , DWORD TimeOut = 0);

//�����ط������ݣ�handle������Pop�������صľ��
DRTPAPPDLL_API bool App_Send(APPHANDLE *handle , LPSTR Data , int len);

//�ر������ص�����,���handle��ΪNULL��رվ���ϵ����ӣ�����ر�indexָ��������
DRTPAPPDLL_API void App_Close(int index,APPHANDLE *handle = NULL);

DRTPAPPDLL_API void App_GetLastError(LPSTR error);

///////////////////////////////////////////////////////////////////////
//DRTPAPPDLL ver 2.01

//ʹ��ȱʡ�������������̣߳�ʵ����App_Init,App_Connect,App_Recv��App_ReConnect�Ĺ���
//ServerIp ���ص�ַ,ServerPort ���Ӷ˿ں�,FunctionCount �����ܺ���Ŀ,func ���ܺ�����
//�ú���������һ���������̸߳������ݵĽ���
DRTPAPPDLL_API bool App_RecvDone(LPSTR ServerIp , short ServerPort , WORD FunctionCount , WORD *func);

///////////////////////////////////////////////////////////////////////
//DRTPAPPDLL ver 2.02

//�ӽ��ն�����ȡ���ݣ�APPHANDLE�ɺ��������߷����ڴ棬
//������Ϣ�����浽���ڴ���У��ڷ�����ȫ������֮ǰ�����ڴ治���ͷ�
//����ֵ <= 0 ��ʾ���������ʾȡ�������ݳ���
//ע�⣺���ص�����Data�в�����Ӧ��ͷ����һ����|�ָ����ַ�������App_Pop���������а���Ӧ��ͷ
DRTPAPPDLL_API int App_Pop2(APPHANDLE *handle , LPSTR Data , int len , DWORD TimeOut = 0);

//�����ط������ݣ�handle������Pop�������صľ��
//ע�⣬��������Data������Ӧ��ͷ����һ����|�ָ����ַ�������App_Send�������ݰ���Ӧ��ͷ
//ColNum ��ʾ���͵��ֶ���Ŀ����|�ָ����ַ�����Ŀ���磺���� A|123|11 ��ColNum = 3
//flag ������ʾ�������ݵ����ͣ������¼���:
//		USER_MESSAGE_RESULT		���ؽ����������Ӧ������
//		USER_MESSAGE_REPORT		���ر�����Ϣ�����ش�����Ϣ
//		USER_MESSAGE_ENDPACK	�����������������ݷ�����֮�󣬱��뷢�ͽ��������ð������ݣ�len=0
DRTPAPPDLL_API bool App_Send2(APPHANDLE *handle , LPSTR Data , int len ,int ColNum , int flag);

///////////////////////////////////////////////////////////////////////
//DRTPAPPDLL ver 2.03

//������һ��Ӧ��ת���������ݰ�
//DestNo ת�����ݵ�Ŀ��Ӫҵ������
//����������App_Send��ͬ
//�ú��������㽫����Ӧ���޷����������������Ӧ�õ���Ҫ
DRTPAPPDLL_API bool App_Transmit(APPHANDLE *handle , LPSTR Data , int len , int DestNo, WORD MainFunc = 0);

//���ü�¼������־���ļ���
//�粻���øú�����ȱʡ����־�ļ����ǿ�ִ���ļ�����Ŀ¼�µ�liblog.txt�ļ�
//���filename��������·�������Զ���ӿ�ִ���ļ����ڵ�Ŀ¼
DRTPAPPDLL_API void App_SetLogFileName(char *filename);

//�õ��ͻ��˱�־
//UserHandle�������ĳ���Ϊ64�ֽڣ��ɺ����������ṩ
DRTPAPPDLL_API void App_GetUserHandle(APPHANDLE *handle , char *UserHandle);


// ������: App_GetConnectIndex
// ���  : ������ 2002-5-26 11:14:07
// ����  : ����APPHANDLE ȡ��ʹ�õ�Index(��App_Init()���ص�������)
// ����  : DRTPAPPDLL_API int 
// ����  : APPHANDLE *handle
DRTPAPPDLL_API int App_GetConnectIndex(APPHANDLE *handle);

#endif