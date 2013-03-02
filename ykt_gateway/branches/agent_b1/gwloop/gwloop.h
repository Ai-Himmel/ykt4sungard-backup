#ifndef _GWLOOP_H_
#define _GWLOOP_H_

#include "localinterface.h"

#ifdef __cplusplus
extern "C" {
#endif 

#ifdef WIN32
#ifdef GWLOOP_EXPORTS
#define GWLOOP_API __declspec(dllexport)
#else
#define GWLOOP_API __declspec(dllimport)
#endif
#else
#define GWLOOP_API
#endif //WIN32


//! ��ʼ������,ϵͳ����ʱ�Զ�����һ��
/*!
 \return ����0��ʾ��ʼ���ɹ�,���򷵻�-1
 */
GWLOOP_API int __stdcall Initialize();
//! �ͷ���Դ����,ϵͳ�����˳�ʱ�Զ�����,��ϵͳ�ڲ������˳�ʱ��һ������.
/*!
 \return ���� 0 ��ʾ��ʼ���ɹ�, ���򷵻� -1
 */
GWLOOP_API int __stdcall Uninitialize();
//! ����������
/*!
 \param request_no �����׺�
 \param pack �������ݰ�����,Ҳ��Ϊ�������ݰ�
 \return 0 ����0 ��ʾ����ɹ�, ���򷵻ش�����,����pack->outdata�б��������Ϣ
 */
GWLOOP_API int __stdcall ProcessRequest(int request_no,request_pack * pack);

#ifdef __cplusplus
}
#endif 
#endif // _GWLOOP_H_
