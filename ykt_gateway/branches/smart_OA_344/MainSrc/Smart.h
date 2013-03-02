#ifndef __SMART_H_
#define __SMART_H_

#include "smartcommunicationdlg.h"
#include "TThread.h"
#include "data.h"
#include "smartlog.h"

class CSmart : public CTThread
{
public:
	bool		Smt_CollectDataInit();
	bool		Smt_CollectDataProcess();					//���׼�¼�ռ�
	bool		Smt_ShowerDataProcess();					//��ԡ��¼�ռ�	
	bool		Smt_WLportDataProcess();					//
	bool		Smt_QueryDeviceStatus();					//��ѯ�����豸�ĵ�ǰ״̬
	bool		SMT_ContinueCollectData( int nPostion);
	bool		SMT_ConfirmData(SMARTCOMMPACK* Doc);		//��¼ȷ��
	bool		SMT_OpenCtrl(SMARTCOMMPACK* Doc);			//��ˮ
	bool		SMT_CloseCtrl(SMARTCOMMPACK* Doc);			//��ˮ
	bool		SMT_SetWorkKey(SMARTCOMMPACK* Doc);			//���ù�����Կ��Ǯ����
	bool		SMT_SetCardType(SMARTCOMMPACK* Doc);		//���ÿ���
	bool		SMT_GetCardType(SMARTCOMMPACK* Doc);		//�ϴ�����
	bool        SMT_SetFreeRate(SMARTCOMMPACK* Doc);		//���ù�������
	bool		SMT_SetAddTotalMoney(SMARTCOMMPACK* Doc);   //���ó�ֵ�ܶ�
	bool        SMT_GetFreeRate(SMARTCOMMPACK* Doc);		//�õ���������
	bool		SMT_SetWhiteCard(SMARTCOMMPACK* Doc);		//����һ��������
	bool		SMT_DelWhiteCard(SMARTCOMMPACK* Doc);		//ɾ��һ��������
	bool		SMT_ConfirmWhiteCard(SMARTCOMMPACK* Doc);	//�ж�һ��������
	bool		SMT_DelAllWhiteCard(SMARTCOMMPACK* Doc);	//ɾ�����а�����
	bool		SMT_SetPosPlace(SMARTCOMMPACK* Doc);		//���üƷ����ص�
	bool		SMT_GetPosPlace(SMARTCOMMPACK* Doc);		//�ϴ��Ʒ����ص�
	bool		SMT_SetWarmMoney(SMARTCOMMPACK* Doc);		//���ñ������
	bool		SMT_GetWarmMoney(SMARTCOMMPACK* Doc);		//�ϴ��������
	bool		SMT_SetBlackCard(SMARTCOMMPACK* Doc);		//����һ��������
	bool		SMT_DelBlackCard(SMARTCOMMPACK* Doc);		//ɾ��һ��������
	bool		SMT_BroadCastBlackCard(SMARTCOMMPACK* Doc); //�㲥������
	bool		SMT_CheckWhetherAssistantCard(int nCardNo,int nBatchNo);
	bool		SMT_AssistantListCofirm(int nPosition,int nCardNo,int nBatchNo,int nMoney);
	bool		SMT_RequestAssistant( BYTE *RespData,int nPosition);
	bool		SMT_CheckCardWhetherAssistant(BYTE *cCardNo,int nPosition);
	bool		SMT_RequestUpAssistanRecord( BYTE *RespData,int nRespDataLen,int nPostion);
	bool		SMT_RequestAddMoney( SMARTPOS sPos);
	bool		SMT_SmartFrontAddAuthTrue( SMARTPOS sPos);
	bool		SMT_SmartFrontAddRequest( SMARTPOS sPos);
	bool		SMT_SmartFrontAddRequestCancel( SMARTPOS sPos);
public:	
	int				m_nPortTotal;		//�������Ķ˿�����
	char			m_regno[5];			//������ע���
	char			m_IDNo[5];			//����ID��
	char			m_MacCode[4];		 //���ʹ���(����)
	int				m_MacNum;			 //����������
	IP_PAR			m_IpPar;			 //����Ķ˿ںš�IP��ַ
	int				m_nTotalPos;         //����Ŀǰ�����ն��豸������
	int				nCommunicationStatus; //������ͨѶ״̬
	SMARTPOS		m_SmartPos[MAX_POSNO]; //����÷��������ն�������Ϣ
	int				m_SmartPosConnCnts[MAX_POSNO]; // ����POS��������
	int				m_SmartPosTaskPos;		//���浱ǰ��ȡ������豸λ��
	int				m_TaskCount;			//��ִ�е�������
	int				 m_SmartPosPostion;	   //��m_SmartPos[MAX_POSNO]��λ��
	OVERLAPPED		 m_ReadOver;		   //IO�ص��Ľ���
	OVERLAPPED		 m_WriteOver;		   //IO�ص��ķ���
	unsigned long	 m_nWriteBytes;		    //���͵��˿����ݳ���
	unsigned long	 m_nReadBytes;		    //���ն˿����ݳ���
	unsigned char	 m_ucReadBytes[1024];    //���յ�������
	char			 m_szErrorText[1024];	//����ͨѶʱ�Ĵ�����Ϣ
	DWORD			 m_nContinueTime;		//����ʱ����δ�յ��豸������		
	char			 m_CreatePath[256];		//����·��
	DWORD			 m_nActionTime;			//ÿ��һ��ҵ���ʱ
	DWORD			 m_nWaitRecvTime;		//�ȴ�������������ʱ��	
	DWORD			 m_nStartTime;			//ʱ��	
	int				 m_nMaxMacNo;			//�豸��������
	DWORD			 m_nQueryFailCount;		//���Ӳ�ѯ����
	int				 m_nTaskResultStatus;	//��������
	byte			 m_sCurDate[9];			//��ǰ����
	int				 m_nTaskPoint;			//����ָ��
	int				 m_nInsertTaskPoint;	//��������ָ��
	int				 m_nPostion;			//�ɼ����ݵ�λ��
	//////////////////////////////////////////////////////////////////////////
	// ����״̬
public:
	CSmartCommunicationDlg* m_pDialog; //��ʾ��	
	CData		m_Data;					//������
	CMyLog		m_Log;					//��־��	
	SMARTCOMMPACKSTR	m_STaskArr;		//����
public:
	void Run();	
	CSmart();
	virtual ~CSmart();
protected:
	bool		SMT_VerifyClock();
	bool		SMT_GetHistoryData(SMARTCOMMPACK* Doc);		//�ɼ���ʷ����	
	bool		SMT_SetClock(SMARTCOMMPACK* Doc);			//�����ն˻�ʱ��
	bool		SMT_GetClock(SMARTCOMMPACK* Doc);			//ȡ�ն˻�ʱ��	
	bool		SMT_SetOpenSaleCtrl(SMARTCOMMPACK* Doc);	//�����ѿ���		
	bool		SMT_Login(SMARTCOMMPACK* Doc);				//�ն�ǩ��	
	bool		SMT_ReConnectServer();						//�������ӷ���
	bool		SMT_CollateClock();	
	bool		SMT_RequestLogin( BYTE *RespData,int nPosition);	//��ԡ��ǩ��
	bool		SMT_RequestConsume( BYTE *RespData,int nPosition);	//��ԡ��������ȷ��		
	bool		SMT_CheckCardNoAvailability(BYTE *cCardNo);			//��鿨����Ч�� ��Ϊ��Ч����Ϊ��Ч		
	bool		SMT_RequestUpConsumeRecord( BYTE *RespData,int nRespDataLen,int nPostion);	//������ԡ����������	
	bool		SMT_ProcessDeviceRegNoErr(int NetWorkType,int nPostion);	//����ע��Ų��������
	bool		SMT_ExecuteCmd411(SMARTCOMMPACK* Doc);
	bool		GetDeviceInfo(char *cDeviceID,int *nPosition);		//����ID�Ż�ȡ���豸�����豸�����е�λ��
	bool		ValidateData(BYTE* Data,int DataLen);				//����յ����ն������Ƿ�Ϸ�
	bool		DealWithRecvData(SMARTCOMMPACK* Doc, BYTE* RecvData);	//�����յ�������	
	char*		GetStatusErrMsg(BYTE StatusCode);
	bool		CreateRecordPath();
	bool		SMT_SettleAccount( int nPosition);			//���ʼ�¼ȷ��
	bool		SMT_GetDeviceID(SMARTCOMMPACK* Doc);		//��ȡID��
	bool		SMT_SetDeviceID(SMARTCOMMPACK* Doc);		//����ID��
	bool		SMT_ProcessIDError(int nPostion);			//����ID�Ŵ�
	bool		SMT_ProcessMACError(int nPostion);			//������Ŵ�
	bool		SMT_ListRequestConfirm(int nPostion);		//��������ȷ��
	bool		SMT_SetMainPara(SMARTCOMMPACK* Doc);		//�����շѻ�������
	bool		SMT_GetMainPara(SMARTCOMMPACK* Doc);		//�ϴ��ն�������
	bool		SMT_SetCardtypeCon(SMARTCOMMPACK* Doc);		//��չ����
	bool		SMT_SetWhiteListAndVer(SMARTCOMMPACK *Doc);
public:
	void		WriteLog(char* msg);						//д��־�ļ�
	bool		WriteTradeDeal(char* Data);					//д���׼�¼�ļ�	
public:
	inline void SetParent(CSmartCommunicationDlg *pt){m_pDialog=pt;};
	bool		InsertTask(SMARTCOMMPACK *Task);			//���������ѹ��һ������
	bool		GetTask(SMARTCOMMPACK *cTask);
	bool		SMT_InsertTaskResult(SMARTCOMMPACK Doc,bool bStatus);		//��������list
public:			//ͨѶ����
	virtual bool  Open()=0;
	virtual void  Close()=0;
	virtual bool  ReConnect()=0;
	virtual bool  WaitRecv(int WaitTime)=0 ;	
	virtual bool  PostSend(char *lpBuffer, int nBufSize, long nTimeOut)=0;
	virtual bool  PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)=0;	
	virtual bool  RecvQueryData(byte *lpData, int*nlpDatalen,DWORD nTimeOut)=0;
};
#endif 