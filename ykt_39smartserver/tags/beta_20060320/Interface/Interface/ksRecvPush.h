
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSRECVPUSH_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSRECVPUSH_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __KSRECVPUSH_H
#define __KSRECVPUSH_H

#ifdef KSRECVPUSH_EXPORTS
#define KSRECVPUSH_API __declspec(dllexport)
#else
#define KSRECVPUSH_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksRecvPushd.lib")
#pragma message("Automatically Linking ksRecvPushd.dll")
#else
#pragma comment(lib,"../lib/ksRecvPush.lib")
#pragma message("Automatically Linking ksRecvPush.dll")
#endif
#endif

#include "ksProcPush.h"

#ifndef NOTIMSGINFO
#define NOTIMSGINFO
#define MAXMSGLEN 255
typedef struct
{
	int nLevel;
	char strMsg[MAXMSGLEN];
}ST_NOTIMSG;
#endif

#ifdef __cplusplus
extern "C" {
#endif
//���ܣ���ʼ������
//����˵����
//nBatch:�Ự���κ�
//hCallerWnd:�����ߵľ��
//nPushMessage:�������ݵ���֪ͨ��Ϣ
//nNotiMessage:dll�ڲ�֪ͨ��Ϣ
//nReadPushMethod:�������ݶ�ȡ��ʽ 1-����nPushMessage��Ϣ�������ߵ���RecvPush_GetMultiPushPack�������
//								   2-��������Ϣ����������������RecvPush_RecvPushPack�������
//nReadMsgMethod:�ڲ���Ϣ��ȡ��ʽ  1-����nNotiMessage��Ϣ�������ߵ���RecvPush_GetMultiMsgPack�������
//								   2-��������Ϣ����������������RecvPush_RecvMsgPack�������
//nMaxPushQueLen:ϵͳ�ڲ�����������������ݶ��г���
//nMaxMsgQueLen:ϵͳ�ڲ�����������ڲ���Ϣ���г���
//����ֵ��
//0 �ɹ� 
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_Initialize(int nBatch,HWND hCallerWnd=NULL,int nPushMessage=0,
								 int nNotiMessage=0,int nReadPushMethod=2,int nReadMsgMethod=2,
								 int nMaxPushQueLen=1000,int nMaxMsgQueLen=1000);

//���ܣ���ʼ���պ���
//����˵��:
//strDrtpAddr:ͨѶƽ̨ip��ַ
//nDrtpPort:ͨѶƽ̨�˿ں�
//nMainFunc:�����ܺ�
//����ֵ��
//0 �ɹ� 
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_Start(char* strDrtpAddr,int nDrtpPort,int nMainFunc);

//���ܣ�ֹͣ���պ���
//����ֵ��
//0 �ɹ� 
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_Stop();

//���ܣ��ͷ���Դ����
//����ֵ��
//0 �ɹ� 
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_Uninitialize();

//���ܣ���ȡָ���������������ݣ����ڶ�ȡ��ʽ1��,������cpack��ʽ���
//����˵����
//buf:�������ݻ��壬����С��cpack����
//nBufSize:�������Ĵ�С
//nPackCount:ϣ����ȡ�����ݸ���
//����ֵ��
//>0��������õ��������ݸ���
//=0����ǰû����������
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_GetMultiPushPack(char* buf,int nBufSize,int nPackCount);

//���ܣ���ȡָ���������ڲ���Ϣ���ݣ����ڶ�ȡ��ʽ1��,������ST_NOTIMSG��ʽ���
//����˵����
//buf:�������ݻ��壬����С��ST_NOTIMSG����
//nBufSize:�������Ĵ�С
//nPackCount:ϣ����ȡ�����ݸ���
//����ֵ��
//>0��������õ��ڲ���Ϣ���ݸ���
//=0����ǰû���ڲ���Ϣ����
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_GetMultiMsgPack(char* buf,int nBufSize,int nPackCount);

//���ܣ���ȡһ���������ݣ����ڶ�ȡ��ʽ2����������CPACK��ʽ���
//����˵����
//buf:������������С��cpack����
//nBufSize:�������Ĵ�С
//nTimeOut:��ʱʱ�䣬�Ժ���Ϊ��λ������С��100ms,���Ϊ0������������
//����ֵ��
//0����ʱ
//1����ȡ�ɹ�
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_RecvPushPack(char* buf,int nBufSize,int nTimeOut);

//���ܣ���ȡһ���ڲ���Ϣ���ݣ����ڶ�ȡ��ʽ2����������ST_NOTIMSG��ʽ���
//����˵����
//buf:������������С��ST_NOTIMSG����
//nBufSize:�������Ĵ�С
//nTimeOut:��ʱʱ�䣬�Ժ���Ϊ��λ������С��100ms,���Ϊ0������������
//����ֵ��
//0����ʱ
//1����ȡ�ɹ�
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_RecvMsgPack(char* buf,int nBufSize,int nTimeOut);

//���ܣ��鿴�ڲ���Ϣ���л�������С
//����ֵ��
//>=0�����л�������С
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_GetMsgQueLen();

//���ܣ��鿴���Ͷ��л�������С
//����ֵ��
//>=0�����л�������С
//-1 ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_GetPushQueLen();

//���ܣ��õ��ܵĶ���������
//����ֵ��
//>=0 ,����������
int KSRECVPUSH_API WINAPI RecvPush_GetThrowPackCount();

//���ܣ��õ�������������Ϣ
//����˵����
//pErrorCode:�������
//strMsg:��������
void KSRECVPUSH_API WINAPI RecvPush_GetLastError(int *pErrorCode,char* strMsg);

//���ܣ����ÿ�����Ϣ��requesttype����
//����˵����
//nCount:ControlReq�����е�Ԫ�ظ���
//ControlReq:������Ϣ��requesttype����
//����ֵ��
//=0 ,���óɹ�
//<0 ,ʧ�ܣ�����ͨ������RecvPush_GetLastError�õ��ڲ�ʧ�ܴ����ʧ��ԭ��
int KSRECVPUSH_API WINAPI RecvPush_SetControlReqTypes(int nCount,unsigned int *ControlReq);
#ifdef __cplusplus
}
#endif

#endif