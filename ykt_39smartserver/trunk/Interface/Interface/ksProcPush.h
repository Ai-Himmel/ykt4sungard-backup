
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSPROCPUSH_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSPROCPUSH_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifndef __KSPROCPUSH_H
#define __KSPROCPUSH_H

#ifdef KSPROCPUSH_EXPORTS
#define KSPROCPUSH_API __declspec(dllexport)
#else
#define KSPROCPUSH_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksProcPushd.lib")
#pragma message("Automatically Linking ksProcPushd.dll")
#else
#pragma comment(lib,"../lib/ksProcPush.lib")
#pragma message("Automatically Linking ksProcPush.dll")
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif
//���ܣ��������ݴ�����
//����˵����
//recvpack[����]:���յ������ݻ���(ST_CPACK��ʽ)
//ackpack[���]:�����ҪӦ����Ļ���Ӧ�����ݵĻ���(ST_CPACK��ʽ)
//pAckFlag[���]:��ҪӦ�����ǣ�	0������ҪӦ���
//									1����ҪӦ���
//pCtlFlag[���]:������Ϣ��ǣ�		0�����ǿ�����Ϣ
//									1���ǿ�����Ϣ
//szMsg[���]:��Ϣ���
//����ֵ��
//0 �ɹ� 
//-1 ʧ�ܣ����յ������ݷ�����������
//���� ʧ�ܣ�����ͨ��szMsg֪��ʧ��ԭ��
int KSPROCPUSH_API WINAPI ProcPush_ProcPushData(char *recvpack,char* ackpack,int *pAckFlag,int *pCtlFlag,char *szMsg);

//���ܣ���ʼ�����ݺ���
//����˵����
//nBatch[����]:�Ự���κ�
//����ֵ��
//0 �ɹ� 
//���� ʧ��
int KSPROCPUSH_API WINAPI ProcPush_Init(int nBatch);

//���ܣ���ʼ����Դ����
//����˵����
//����ֵ��
//0 �ɹ� 
//���� ʧ��
int KSPROCPUSH_API WINAPI ProcPush_InitRes();

//���ܣ��ͷ���Դ����
//����˵����
//����ֵ��
//0 �ɹ� 
//���� ʧ��
void KSPROCPUSH_API WINAPI ProcPush_FreeRes();

//���ܣ����ÿ�����Ϣ����
//����˵����
//nCount[����]:������Ϣ����
//ControlReq[����]:������Ϣ����
//����ֵ��
//0 �ɹ� 
//���� ʧ��
int KSPROCPUSH_API WINAPI ProcPush_SetControlReqTypes(int nCount,unsigned int *ControlReq);

//���ܣ��ж��Ƿ�Ϊ��Ч�������ݺ���
//����˵����
//recvpack[����]:���յ������ݻ���(ST_CPACK��ʽ)
//����ֵ��
//0 ��Ч���� 
//���� ��Ч����
int KSPROCPUSH_API WINAPI ProcPush_CheckValidPushData(char* recvpack);

#ifdef __cplusplus
}
#endif

#endif