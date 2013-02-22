#ifndef DRTPAPI_DLL_HEADER_1
#define DRTPAPI_DLL_HEADER_1


#if !defined(WIN32)
	#define __stdcall
	#include "mytypes.h"
#endif

//////////////////�����¼�����////////////////////////////
#define DRTP_READ		1
#define DRTP_WRITE		2
#define DRTP_EXCEPT		4
//////////////////////////////////////////////////////////
extern "C" BOOL __stdcall DRTPInitialize();
/*
	���ܣ���ʼ����
	�������ޡ�
	����ֵ�������ʼ���ɹ�������TRUE�����򷵻�FALSE��
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" BOOL __stdcall DRTPUninitialize();
/*
	���ܣ��ͷ���Դ
	�������ޡ�
	����ֵ�����ȡ����ʼ���ɹ�������TRUE�����򷵻�FALSE
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" int __stdcall DRTPGetHost (char*  strIP,WORD* pwPort,WORD wGatewayNo=0,WORD wBroadcastPort=1976,DWORD dwTimeout=5000);
/*
	���ܣ�������Ӧ��ŵ�·��ͨѶ��������IP�Ͷ˿ں�
	������
		strIP[OUT]:����·��ͨѶ��������IP,���û�����ÿռ�
		pwPort[OUT]:����·��ͨѶ�������Ķ˿ں�,���û�����ÿռ�
		wGatewayNo[IN]:����ѯ��·��ͨѶ�������ı��
		wBroadcastPort[IN]:�㲥�˿ں�
		dwTimeout[IN]:��ʱ
	����ֵ���ҵ��򷵻���Ӧ��·��ͨѶ���������룬���򷵻�-1
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" HANDLE __stdcall DRTPConnect (LPCTSTR strIP,WORD wPort,WORD Encode);
/*
	���ܣ�������·��ͨѶ������������
	������
		strIP[IN]:·��ͨѶ��������IP��ַ
		wpPort[IN]:·��ͨѶ�������Ķ˿ں�
		Encode[IN]:���ܷ�ʽ
	����ֵ��������ӳɹ��������½����ӵľ�������򷵻�NULL��
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" BOOL __stdcall DRTPClose (HANDLE hConnection);
/*
	���ܣ��ر���·��ͨѶ������������
	������
		hConnection[IN]:��DRTPConnect���ص�HANDLE
	����ֵ������رճɹ�������TRUE�����򷵻�FALSE��
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" BOOL __stdcall DRTPSend (HANDLE hConnection,WORD wDestNo,WORD wFunction, char * pSendData,int iLen,BYTE byFunctionPriority,bool Designed=false);
/*
	���ܣ���������\Ӧ������
	������
		hConnection[in]�����Ӿ��������DRTPConnectʱ���ء�
		dwDestNo [in]�����շ����롣���������Ϊ���������Ա�������
		dwMainFunction [in]�����շ������ܺš����������Ϊ���������Ա�������
		pSendData [in]�����ͻ�������
		iLen[in]�������͵��ֽ�����
		ByFunctionPriority[in]�����ܺ����ȼ���
								//1Ϊ���ȼ����ڱ�׼
								//2Ϊ��׼���ȼ�
								//3Ϊ���ȼ����ڱ�׼
		Designed[IN]:ָ��·�ɱ��
								//trueΪָ��·��
								//falseΪ��ָ��·��
	����ֵ��������ͳɹ�������TRUE�����򷵻�FALSE��
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" int __stdcall DRTPReceive(HANDLE hConnection,char * recvBuffer,int iBufferSize,DWORD dwTimeout= 0);
/*
	���ܣ��������ݡ�
	������
		hConnection[in]�����Ӿ��������DRTPConnectʱ���ء�
		recvBuffer [out]�����ջ���������С4096�ֽڡ�
		iBufferSize[in]�����ջ������ֽ�����
		dwTimeout [in]�����ճ�ʱ�����Ϊ0����Ϊ������ʽ��
	����ֵ��
		���ճɹ������ؽ��յ����ֽ�����
		���ճ�ʱ������0��
		����ʧ�ܣ�����-1
		·��ͨѶ������������Ϣ������ֵΪ -4��������DRTPGetLastError()��ȡ��
		��Ӧ����Ϣ���ַ�����

	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" BOOL __stdcall DRTPCheckNetState (HANDLE hConnection,DWORD dwTimeout=2000);
/*
	���ܣ������������״̬��
	������
		hConnection[in]�����Ӿ��������DRTPConnectʱ���ء�
		dwTimeout[in]����ⳬʱ�����룩��0ΪBlock��ʽ��
	����ֵ�������������������ֵ����0������ֵС��0�������ⳬʱ������0��
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" BOOL __stdcall DRTPCheckDataArrived (HANDLE hConnection,DWORD dwTimeout=0);
/*
	���ܣ�����ض��������Ƿ���������δ���ա�
	������
		hConnection[in]�����Ӿ��������DRTPConnectʱ���ء�
		dwTimeout[in]�����ʱ�䣨���룩��0ΪBlock��ʽ��
	����ֵ�������δ�������ݣ�����TRUE�����򷵻�FALSE�� 
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/
extern "C" int __stdcall DRTPGetLastError(HANDLE hConnection,char* ErrorMsgBuffer,int iMsgBufferSize);
/*
	���ܣ������ض������ϵĴ�����Ϣ��
	������
		hConnection[in]�����Ӿ��������DRTPConnectʱ���ء�
		ErrorMsgBuffer[in]:���������Ϣ�Ļ�����
		iMsgBufferSize[in]:�������ĳ���
	����ֵ���ɹ�����1��ʧ�ܷ���0
	�޸��ߣ����� 20010404
	�޸�ԭ�򣺹淶����
*/


extern "C" int __stdcall DRTPCloseSocket(HANDLE hConnection);
/*
	���ܣ��ر�SOCKET����
	������
		hConnection[in]�����Ӿ��������DRTPConnectʱ���ء�
	����ֵ���ɹ�����1��ʧ�ܷ���0
*/



#endif