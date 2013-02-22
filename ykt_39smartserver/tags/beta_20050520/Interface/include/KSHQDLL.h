#ifndef	_KSHQDLL_H
#define _KSHQDLL_H

#ifdef  KSHQDLL_EXPORTS
#define KSHQDLL_API __declspec(dllexport)
#else
#define KSHQDLL_API __declspec(dllimport)

#ifdef  _DEBUG
#pragma comment(lib, "..\\lib\\KSHQDLL_D.lib")
#pragma message("Automatically Linking KSHQDLL_D.DLL")
#else
#pragma comment(lib, "..\\lib\\KSHQDLL.lib")
#pragma message("Automatically Linking KSHQDLL.DLL")
#endif
#endif

/* ʹ��˵��:
 *	��1��. ���ȵ���HQ_Init(), ��ʼ����Դ,��ͨ��ƽ̨������Ҳ�ڴ�ʱ����.
 *	��2��. ����HQ_Start(), ��ɺ�Dll��������������ȡ����,��ȡ����������뱾���ڴ���
 *  ��3��. ��HQ_GetRec() �� HQ_GetnRec()ȡ�������ڴ������. ���ȡ�����������DLL
           ��ʱֹͣ�������������ȡ����, ���Ե���HQ_Stop(); �����ָ�,�ٴε���HQ_Start()
 *  ��4��. �������ʱ, ����HQ_Uninit()�ͷ���Դ
 *  ע��: ��������ķ���ֵ����������,���Ե���HQ_GetErrorNo()ȡ�������,HQ_GetErrorMsg()ȡ
          ������Ϣ
	hezhenhua 20040312
 */
#ifdef __cplusplus
extern "C" {
#endif
KSHQDLL_API bool WINAPI HQ_Init(int iHqWay, 
						  HANDLE hWnd, 
						  unsigned int iMsg, 
						  char* strOperCode,
						  unsigned short wDestNo,
						  unsigned short wMainFunc,
						  char* strIP,
						  unsigned short wPort,
						  unsigned short wLocalPort, 
						  unsigned short wRegtimeval);
/*
	������ȡֵ:
 	iHqWay��1			//��TCP��ʽ��ͨ��ͨ��ƽ̨��
 			2			//��UDP��ʽ ����Ե㣩
 			3			//UDP�㲥��ʽ 
 
 			hWnd:       //��Ϣ���մ���ľ��������DLL���巢����Ϣ
 			iMsg��		//DLL���巢����Ϣ����Ϣ��
 			strCustNo:	//����Ա��(11λ)
 			wDestNo:	//����������Ľ���
 			wMainFunc:	//����������������ܺ�(ͨ��Ϊ3001)
 			strIP:		//ͨ��ƽ̨(�����������)��IP��ַ
 			wPort:  	//ͨ��ƽ̨(�����������)�Ķ˿ں�(������ߵĶ˿ں�)
 			wLocalPort:	//���ض˿ںŻ�㲥�˿ں�
 
 	����ֵ��true		//��ʼ���ɹ�
 			false		//��ʼ��ʧ��
 ע��:���iHqWay��ֵΪ 1:	strOperCode->����
							wDestNo->����������Ľ���(��0����), ����
							wMainFunc->����������������ܺ�(Ĭ��Ϊ666), ����
							strIP->ͨ��ƽ̨��IP��ַ, ����
							wPort->ͨ��ƽ̨�Ķ˿�, ����
							wRegtimeval->��ʱע���ʱ����, ����
	 ���iHqWay��ֵΪ 2:	strOperCode->����Ա��,����
							strIP->�����������IP��ַ, ����
							wPort->����������Ķ˿�, ����
							wLocalPort->����DLL�ĳ���ı��ض˿ںű���
							wRegtimeval->��ʱע���ʱ����, ����
 	 ���iHqWay��ֵΪ 3:	wLocalPort->���չ㲥�Ķ˿ں�, ����

   ��Բ�ͬ��iHqWay��ȡֵ,����Ĳ����Ǳ���ȷ����ȷ��.
   ������Ҫ����Ĳ���: �������ֵ�͵�,ȫ��Ϊ0;�����ָ����ַ����͵�,ȫ��ΪNULL
   �㲥�˿ں�Ҫ�����������������ת��������һ��.��������䶯
   ���������������ת�����Ĺ㲥�˿�Ϊ27657
*********************************************************************************
*/   

KSHQDLL_API int WINAPI HQ_GetRec(unsigned char* buf, int isize, int itimeout);
/*
 *	����˵����
 *		buf:	//ָ����ȡ��������Ļ���
 *		isize:	//����Ĵ�С
 *		itimeout://����Ϊ��ʱ�ĳ�ʱʱ��
 *	���itimeout = 0,������Ϊ��ʱ,ֱ�ӷ���
 *  ���itimeout > 10, ������Ϊ��ʱ,��˯��itimeout������ٷ���
 *  ���itimeout��1~10���,����󷵻�
 *
 *	����ֵ��ȡ���������¼��ʵ�ʵĴ�С
 *		0 ������ն���Ϊ��
 *		< 0 ����
 *		> 0	��ȷ��ʵ�������¼�Ĵ�С
 *
 *  ˵��:���������û�е��������̵߳��ñ�����������, itimeoutһ��Ҫ��Ϊ 0
 *		 ����,ÿȡһ�μ�¼,�ͻ�˯��1000����	
 ****************************************************************************
 */


KSHQDLL_API int WINAPI HQ_GetnRec (unsigned char* buf, int isize, int *ireccount, int itimeout);
/*
 *	����˵����
 *		buf:	//ָ����ȡ��������Ļ���
 *		isize:	//����Ĵ�С
 *		ireccount://ʵ��ȡ���ļ�¼������
 *		
 *      hezhenhua 20031205 add
 *		itimeout: //�������������Ϊ�յĳ�ʱֵ
 *	����ֵ��ȡ���������¼��ʵ�ʵĴ�С֮��
 *		0 ������ն���Ϊ��
 *		< 0 ����
 *		> 0	��ȷ��ʵ�������¼�Ĵ�С
 **************************************************************************
 */

KSHQDLL_API bool WINAPI HQ_Uninit();
/*
 *	��Դ�ͷŲ���, ���������ն��У��ж�TCP��UDP������, ע��
 ************************************************************
 */

KSHQDLL_API int WINAPI  HQ_GetErrorNo();

KSHQDLL_API bool WINAPI HQ_Start();
/*
 *	��ʼ�����������ȡ����, ��HQ_Init()�ɹ�ִ�����,Ҫ����HQ_Start�Ż��
 *  �����������ȡ����.
 */

KSHQDLL_API void WINAPI HQ_GetErrorMsg(char *msgbuf, int ibufsize);
/*
 *	������һ�δ���Ĵ�����Ϣ
 */

KSHQDLL_API bool WINAPI HQ_Stop();
/*
 *	��ͣ�����������ȡ����, ������ʱֹͣ�������������������ʱ,����HQ_Stop()
 *  ��������������ͷ���Դʱ,ֻҪ����HQ_Uninit()�Ϳ�����,���õ���HQ_Stop();
 */

KSHQDLL_API int WINAPI HQ_GetQueSize();
/*
 *	��ȡ����������еĳ���
 */

KSHQDLL_API void WINAPI HQ_GetHandle(HANDLE *phandle);
/*
 *	ȡ����TCP���ӵľ��
 */
#ifdef __cplusplus
}
#endif
#endif