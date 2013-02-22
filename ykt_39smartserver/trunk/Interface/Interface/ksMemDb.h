#ifndef __KSMEMDB_H
#define __KSMEMDB_H
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the KSMEMDB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// KSMEMDB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef KSMEMDB_EXPORTS
#define KSMEMDB_API __declspec(dllexport)
#else
#define KSMEMDB_API __declspec(dllimport)
#ifdef _DEBUG
#pragma comment(lib,"../lib/ksMemDbd.lib")
#pragma message("automatic link ksMemDbd.dll")
#else
#pragma comment(lib,"../lib/ksMemDb.lib")
#pragma message("automatic link ksMemDb.dll")
#endif
#endif

#ifdef __cplusplus
extern "C"
{
#endif
//���ܣ�
//��ʼ�����򿪻��ߴ����ڴ����ݿ�
//����˵����
//szDbName[����]���ڴ����ݿ�����
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_Init(char *szDbName,char *szMsg);

//���ܣ�
//�ر��ڴ����ݿ⣬�ͷ���Դ
//����ֵ��
//��
void KSMEMDB_API WINAPI KSMEMDB_Free();

//���ܣ�
//�����
//����˵����
//szTableName[����]������
//nTimeOut[����]����ʱʱ�䣨���룩�����Ϊ0��������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_LockTable(char *szTableName, int nTimeOut,char *szMsg);

//���ܣ�
//�����
//����˵����
//szTableName[����]������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_UnLockTable(char *szTableName,char *szMsg);

//���ܣ�
//�����׸���ѯ������������where��������ݣ�
//����˵����
//szTableName[����]������
//str[����]����������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_AddFirstCondition(char *szTableName, char *str,char *szMsg);

//���ܣ�
//������ֵ�Ͳ�ѯ������������where��������ݣ�
//����˵����
//szTableName[����]������
//value[����]����������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_AddConditionOfValue(char *szTableName, int *value,char *szMsg);

//���ܣ�
//�����ַ��Ͳ�ѯ������������where��������ݣ�
//����˵����
//szTableName[����]������
//value[����]����������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_AddConditionOfStr(char *szTableName, char *value,char *szMsg);

//���ܣ�
//����в�������
//����˵����
//szTableName[����]������
//buf[����]����¼����
//nbufsize[����]������Ĵ�С
//multi[����]���Ƿ������ظ���¼����
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_Insert(char *szTableName, char *buf, int nbufsize,bool multi,char *szMsg);

//���ܣ�
//����������ڵ���AddFirstConditionʱ��ϵͳ�Զ����ã�
//����˵����
//szTableName[����]������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_Reset(char *szTableName,char *szMsg);

//���ܣ�
//ѡ����ǰ�еļ�¼
//����˵����
//szTableName[����]������
//buf[���]����¼����
//nbufsize[����]������Ĵ�С
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_SelectCurrent(char *szTableName, char *buf,int nbufsize,char *szMsg);

//���ܣ�
//����ǰ������ɾ��
//����˵����
//szTableName[����]������
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_SelectDelete(char *szTableName,char *szMsg);

//���ܣ�
//�õ���һ����¼
//����˵����
//szTableName[����]������
//buf[���]����¼����
//nbufsize[����]������Ĵ�С
//condition[����]���Ƿ�ʹ��where����
//szMsg[���]��������Ϣ
//����ֵ��
//>=0 ���صķ��������ļ�¼����
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_SelectFirst(char *szTableName, char *buf, int nbufsize,bool condition,char *szMsg);

//���ܣ�
//�õ�������¼
//����˵����
//szTableName[����]������
//buf[���]����¼����
//nbufsize[����]������Ĵ�С
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_SelectNext(char *szTableName, char *buf,int nbufsize,char *szMsg);

//���ܣ�
//�޸ĵ�ǰselect�ļ�¼����
//����˵����
//szTableName[����]������
//buf[����]����¼����
//nbufsize[����]������Ĵ�С
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_SelectUpdate(char *szTableName, char *buf,int nbufsize,char *szMsg);

//���ܣ�
//update��¼
//����˵����
//szTableName[����]������
//buf[����]����¼����
//nbufsize[����]������Ĵ�С
//condition[����]���Ƿ�ʹ��where����
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_Update(char *szTableName, char *buf, int nbufsize,bool condition,char *szMsg);

//���ܣ�
//ɾ����¼
//����˵����
//szTableName[����]������
//condition[����]���Ƿ�ʹ��where����
//szMsg[���]��������Ϣ
//����ֵ��
//0 �ɹ�
//-1 ʧ�ܣ�ʧ��ԭ���szMsg����
int KSMEMDB_API WINAPI KSMEMDB_Delete(char *szTableName, bool condition,char *szMsg);
#ifdef __cplusplus
}
#endif

#endif
