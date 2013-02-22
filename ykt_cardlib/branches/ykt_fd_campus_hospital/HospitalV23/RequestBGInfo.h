#ifndef _REQUEST_BG_INFO_H_
#define _REQUEST_BG_INFO_H_
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*================================================================ 	
* ��������    Login
* ������      [in]  ��
* ��������:   �ͻ��˷��𵽺�̨ǩ��, ��ȡ��Կ, ����drtp��Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ��ش�����
================================================================*/
int __stdcall Login();

/*================================================================ 
* ��������    GetCustomerInfo
* ������      [in]  (const char *szStuempNo)ѧ����
* ������      [out] (CustomerInfo *CutInfo)�ͻ���Ϣ
* ��������:   ��ȡ�ͻ���Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ��ش�����
================================================================*/
int __stdcall GetCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo);

/*================================================================ 
* ��������    GetCurBalance
* ������      [in]  (const char *szStuempNo)ѧ����
* ������      [out] (double *dCurBalance)��ȡ��ѧ�������
* ��������:   ��ȡ�ͻ���Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ��ش�����
================================================================*/
int __stdcall GetCurBalance(const char szStuempNo[21], double *dCurBalance);

/*================================================================ 
* ��������    GetTradeSerial
* ������      [in]  (int nDeviceId)�豸��
* ������      [out] (TradeSerial **Serial)������ˮ��ϸ
* ������      [in]	(int *nNextFlag)��ȡ�Ƿ�����һ�ΰ��ı��
* ������      [in]	(int nInputFlag)������Ի�ȡ����һ�ΰ����
* ������      [in]	(char *szBeginDate)��ˮ������ʼ(��:��:��)
* ������      [in]	(char *szEndDate)��ˮ��������(��:��:��)

* ������      [in]	(char *szSerialYear)��ˮ�������
* ������      [in]	(char *szSerialMonth)��ˮ�����·�
* ������      [in]	(char *szBeginDay)��ˮ������ʼ����
* ������      [in]	(char *szEndDay)��ˮ������������
* ��������:   ��ȡ�˻���ˮ��Ϣ
* ����ֵ��    int, ��ȷ����0, ʧ�ܷ��ش�����
================================================================*/
int __stdcall GetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11]);

#ifdef __cplusplus
}
#endif

#endif