#ifndef _INTERFACE__H_
#define _INTERFACE__H_

#include "SmartCommunicationDlg.h"
class CInterface
{

public:
	CInterface();
	~CInterface();
	bool SMT_InterfaceInit(char* szAddr, int nPort );
	bool SMT_ReConnect(int nPostion);
	bool SMT_ClosePackHandle();
	bool SMT_PackInit(XDHANDLE nHandle);
	XDHANDLE SMT_GetXDHandle();
	XDHANDLE SMT_GetXDHandleRecorder();
	bool SMT_SetXDHandleFree(XDHANDLE nHandle);
	bool SMT_SetRequestFunID(XDHANDLE nHandle,int nFunId);
	bool SMT_SetValue(XDHANDLE nHandle,int nRow,char *FieldName,int Value);
	bool SMT_SetValue(XDHANDLE nHandle,int nRow,char *FieldName,double Value);
	bool SMT_SetValue(XDHANDLE nHandle,int nRow,char *FieldName,char* Value);
	bool SMT_GetValue(XDHANDLE nHandle,int nRow,char * FieldName,int *Value);
	bool SMT_GetValue(XDHANDLE nHandle,int nRow,char * FieldName,double *Value);
	bool SMT_GetValue(XDHANDLE nHandle,int nRow,char *FieldName,char* Value,int ValueSize);
	bool SMT_SendAndRecvData(int nPostion, XDHANDLE nHandle,DWORD TimeOut,int*errcode,char* errmsg);

	int	 SMT_RecvStatus(XDHANDLE nHandle);
	bool SMT_GetRowCount(XDHANDLE nHandle,int *row);
	bool SMT_PackIsEof(XDHANDLE nHandle);
	bool SMT_NextPack(XDHANDLE nHandle,DWORD TimeOut,int *errcode,char* errmsg);
public:
	bool SMT_GetAllInitBlackList(int FunId);					//ǰ������ʱ����˴��ȡ���к�����
	bool SMT_GetAllInitAssistantList(bool bAnswer,long nReMessageID);				//��ȡ���в�������
	bool SMT_CheckWhetherAssistant( byte *ucData,int *nMoney,int *nBatch);	//�����˴��̨�Ƿ�����첹��
	bool SMT_GetAllDeviceInfo();					//ǰ������ʱ��ȡ���е��豸������Ϣ
	bool SMT_GetSysTask();							//�ӽ��˴��ȡ����	
	bool SMT_ReportTaskResult();					//����˴ﱨ��������
	bool SMT_UpDeviceStatus();						//�ϴ��豸״̬�����˴�
	bool SMT_GetDeviceTask();						//��ȡ����
	bool SMT_GetDeviceBlackCardTask(SMARTPOS cPos);	//��ȡ����������
	bool SMT_InsertTaskToLink(SMARTCOMMPACK Task,bool bFlag=false);	//��������뵽��Ӧ��·
	bool SMT_GetDeviceOneRate(SMARTCOMMPACK *Task);	//�ӽ��˴��ȡ�豸�ķ���
	bool SMT_GetDeviceCardType(SMARTCOMMPACK *Task,char* sBuffer);
	bool SMT_SmartRegister(DWORD nTimeOut);			//ǰ��ע��
	bool SMT_SmartFrontLogin(DWORD nTimeOut);		//ǰ��ǩ��
	bool SMT_UpDealRecord(XDHANDLE nHandler,char* sData,int nTimeOut,int *nErrCode,char* sErrMsg); //�ϴ����׼�¼�����˴�
	bool SMT_SaleRecordAnalysis(char* ssData,STRSALERECORD &StrDeal);
	bool SMT_SaleRecordAnalysis_SongJiang(char* ssData,STRSALERECORD &StrDeal);	
	bool SMT_SaleRecordAnalysis_GuangZhou(XDHANDLE nHandler,int nTimeOut,int *nErrCode,char* sErrMsg,char* ssData,STRSALERECORD &StrDeal);
	bool SMT_AssitantRecordAnalysis(char* ssData,STRSALERECORD &StrDeal);
	bool SMT_RequestAddMoney(byte *ucDevice,int *nMoney,int *nBatch);	
	bool SMT_TimeRecordAnalysis(XDHANDLE nHandler,int nTimeOut,int *nErrCode,char* sErrMsg,char* ssData,STRSALERECORD &StrDeal);
	bool SMT_SmartFrontAddAuthTrue(byte *ucDevice, byte *ucData);
	bool SMT_SmartFrontAddRequest(byte *ucDevice, byte *ucData);
	bool SMT_SmartFrontAddRequestCancel(byte *ucDevice, byte *ucData);
private:	
	char		m_cPackPath[256];					//·��
	int			m_drtpno;	
	CPACKHANDLE	m_handler[256];
	char		m_szHost[20];						//IP��ַ
	int			m_nPort;							//�˿ں�
	CData		m_Data;
public:
	CSmartCommunicationDlg	*m_pDlg;
	void		SetParentpDlg(CSmartCommunicationDlg* pDlg){m_pDlg=pDlg;};
	char		m_szText[256];		//������Ϣ
	int			m_mainfunc;
	bool		m_bConnectStatus;	//����״̬ true��ʾ����  false��ʾʧ��
};
#endif