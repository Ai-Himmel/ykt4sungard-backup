// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
//��ı�׼�������� DLL �е������ļ��������������϶���� ADVANSTA_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
//�κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ 
// ADVANSTA_API ������Ϊ�ǴӴ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#include "Pubdef.h"

#ifdef ADVANSTA_EXPORTS
#define ADVANSTA_API __declspec(dllexport)
#else
#define ADVANSTA_API __declspec(dllimport)
#endif

#ifndef EXTER_C
#define EXTERN_C    extern "C"
//#define EXTERN_C
#endif

//======================================================================================================
// �ӿ����ƣ�	ConfigParamters
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	char *	lpAddrServer			// ������IP��ַ����0��β���ַ���
//				int		nPortHost				// SocketͨѶ�˿�		
//												// ���׼�¼����������ļ���Ŀ¼
//												// ��0��β���ַ���
//				char *	lpDeviceID				// �̻�ID��16�����ַ���,��0��β
//				char * lpEplink_AddrServer		// EƱ��������IP
//				int nEplink_PortHost			// EƱ��������Socket�˿�	
// ��    �ܣ�									// ���洫��Ĳ��������жϺϷ���
//												// ������Դ
// ����˵����									// ���ظ�DLL���һ�����õĺ�����
//												// �������ʧ�ܣ�Ӧ��ֹ��������				
//======================================================================================================
EXTERN_C int ADVANSTA_API ConfigParamters(char * lpAddrServer, int nPortHost,					// ��ͨǮ����������ַ
								 char * lpCommTickAddrServer, int nCTPortHost,			// ��ƱǮ����������ַ
								 char * lpEplink_AddrServer, int nEplink_HostPort,		// ��Ʊ����̨��������ַ
								 char * lpDeviceID);



//======================================================================================================
// �ӿ����ƣ�	Common_Initialize_RW
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	int				nPort			// ͨѶ�˿�
//				int				Baud			// ͨѶ������
//				int				nSamSlot		// PSAM���ۣ�SAM1\SAM2
//				char *			lpPKIPin		// PKI��pin��
//				LPBYTE			lpInitKey		// ��ʼ��ֵ
//              int             hdVersion       // Ӳ���汾,�������ֲ�ͬ���ҵĶ�д��
//				char *			ServCode		// ���÷����̴���(2byte,BCD��)
//              int             Only            // ����ѡ��
// ��    �ܣ�									// ��ʼ��ͨѶ�˿ڣ�������Դ
// ����˵����									// ������ConfigParamters����ã�
//												// �������ʧ�ܣ�Ӧ��ֹ��������				
//======================================================================================================
EXTERN_C int ADVANSTA_API Common_Initialize_RW(const int nPort, int Baud, int nSamSlot, char * lpPKIPin, LPBYTE lpInitKey, int hdVersion, char * SvrCode, int Only);
//EXTERN_C int ADVANSTA_API Common_Initialize_RW(const int nPort, int Baud, int nSamSlot, char * lpPKIPin, LPBYTE lpInitKey, int hdVersion, char * SvrCode, int Only, HANDLE Comm = 0);



//======================================================================================================
// �ӿ����ƣ�	Common_Destroy_RW
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	int		nPort					// ͨѶ�˿�
// ��    �ܣ�									// �ر�ͨѶ�˿ڣ��ͷ���Դ
// ����˵����									// ж��DLLǰ�Ĳ���		
//======================================================================================================
EXTERN_C int ADVANSTA_API Common_Destroy_RW(const int nPort);



//======================================================================================================
// �ӿ����ƣ�	QueryBalance
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	int			nPort				// ͨѶ�˿�
//				PPURCHSEARCH preqPurchase		// ���Ѳ�ѯ�ṹ
// ��    �ܣ�									// ��ѯ����POS����ʾ
// ����˵����									// ���
//======================================================================================================
EXTERN_C int ADVANSTA_API QueryBalance(const int nPort,PPURCHSEARCH pPurSearch);



//======================================================================================================
// �ӿ����ƣ�	Consumption
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	int			nPort				// ͨѶ�˿�
//				DWORD		dwValue				// ���ѽ��
// ��    �ܣ�									// ���ѣ������ն��γ����Ѽ�¼
//												// ����POS����ʾ�����Ϣ
// ����˵����									// ���
//======================================================================================================
EXTERN_C int ADVANSTA_API Consumption(const int nPort, const DWORD dwValue, PPURCHPREPARE ppurPrepare);

//======================================================================================================
// �ӿ����ƣ�	CashIncrease
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	int			nPort				// ͨѶ�˿�
//				DWORD		dwValue				// ��ֵ���
//              PPURCHASEINCREASE pIncrease     // ��ֵ���ݽӿ�
//              BOOL bMustCmp                   // �Ƿ�������δ��������
// ��    �ܣ�									// ��ֵ�������δ��������
//												// ����POS����ʾ�����Ϣ
// ����˵����									// ���
//======================================================================================================
EXTERN_C int ADVANSTA_API CashIncrease(const int nPort, const DWORD dwValue, PPURCHASEINCREASE pIncrease, BOOL bMustCmp);


//======================================================================================================
// �ӿ����ƣ�	GetAPIVersion
// �������ͣ�	int								// 0���ɹ���
//												// ��0��ʧ��
// ����˵����	char *Version					// ���صİ汾�� VX.XX
// ��    �ܣ�									// ��ȡAPI�汾��
// ����˵����									// ���
//======================================================================================================
EXTERN_C int ADVANSTA_API GetAPIVersion(char *Version);


//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_SignIn
// �������ͣ�	int										// 0���ɹ���
//														// ��0��ʧ��
// ����˵����	const int nPort							// ͨѶ�˿�
//				pCommTicket_SignIn_Info_t pSignInInfo	// ǩ����Ϣ
// ��    �ܣ�											// ��Ʊ��ֵǰǩ��
// ����˵����											// ������Ʊ��ֵ����֮ǰ����
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_SignIn(const int nPort, pCommTicket_SignIn_Info_t pSignInInfo);

//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_Query
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	const int nPort								// ͨѶ�˿�
//				const char OperaType
//				pCommTicket_Increase_t pCommTickParam
//				pCommTicket_Info_t pCommTickInfo
// ��    �ܣ�												// ��Ʊ��ֵ\������ѯ
// ����˵����												// ����CommutationTicket_SignIn�ɹ������
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Query(const int nPort, const char OperaType,
												pCommTicket_Increase_t pCommTickParam, 
												pCommTicket_Info_t pCommTickInfo);

//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_Increase
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	const int nPort								// ͨѶ�˿�
//				const char OperaType
//				pCommTicket_Increase_t pCommTickParam
//				pCommTicket_Info_t pCommTickInfo
// ��    �ܣ�												// ��Ʊ��ֵ
// ����˵����												// ����CommutationTicket_Query�ɹ������
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Increase(const int nPort,
												pCommTicket_Info_t pCommTickInfo, 
												pCommTicket_Charge_Info pCommTickChargeInfo);

//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_Rcharge
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	const int nPort								// ͨѶ�˿�
//				const char OperaType
//				char *pSysCounts
// ��    �ܣ�	��ֵ����/��������
// ����˵����												// 
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Rcharge(const int nPort, 
												const char OperaType, 
												char *pSysCounts);

// 
//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_ReadInfo_offline
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	const int nPort								// ͨѶ�˿�
//				char *pDealCounts
//				pCommTicket_ReadInfo_Offline_t pCommTickInfo
// ��    �ܣ�	�ѻ���ѯ��Ʊ
// ����˵����												// ��ʱ
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_ReadInfo_offline(const int nPort, 
														char *pDealCounts, 
														pCommTicket_ReadInfo_Offline_t pCommTickInfo);


// 
//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_ReadInfo_online
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	const int nPort								// ͨѶ�˿�
//				char Rdtype									// ��ѯ����
//				char *pKey									// �Ự��Կ
//				pCommTicket_Online_Info_t pInfo				// ���ز�ѯ��Ϣ
// ��    �ܣ�	������ѯ��Ʊ
// ����˵����												// ��ʱ
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_ReadInfo_online(const int nPort, char Rdtype, char *pKey, pCommTicket_Online_Info_t pInfo);

// 
//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_Epaylinks_Deduction
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	pCommTicket_Info_t pCommTickInfo			// ��ֵ������Ϣ
//				char *pcEpalinkSysNo						// ���ص���Ʊ���ʺ���ˮ
// ��    �ܣ�	��Ʊ���ʻ��۷�
// ����˵����												// ��ʱ
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Epaylinks_Deduction(pCommTicket_Info_t pCommTickInfo,
																char *pcEpalinkSysNo);
//
//======================================================================================================
// �ӿ����ƣ�	CommutationTicket_Epaylinks_Back
// �������ͣ�	int											// 0���ɹ���
//															// ��0��ʧ��
// ����˵����	char *pcEpalinkSysNo						// ��Ҫ��������Ʊ���ʺ���ˮ
// ��    �ܣ�	��Ʊ���ʻ�����
// ����˵����												// ��ʱ
//======================================================================================================
EXTERN_C int ADVANSTA_API CommutationTicket_Epaylinks_Back(char *pcEpalinkSysNo);

//#pragma comment(lib, "AdvanSta.lib")
