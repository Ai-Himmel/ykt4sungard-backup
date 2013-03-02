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
	bool SMT_GetAllInitBlackList(int FunId);					//前置启动时向金仕达获取所有黑名单
	bool SMT_GetAllInitAssistantList(bool bAnswer,long nReMessageID);				//获取所有补助名单
	bool SMT_CheckWhetherAssistant( byte *ucData,int *nMoney,int *nBatch);	//检查金仕达后台是否可以领补助
	bool SMT_GetAllDeviceInfo();					//前置启动时获取所有的设备档案信息
	bool SMT_GetSysTask();							//从金仕达获取任务	
	bool SMT_ReportTaskResult();					//向金仕达报告任务结果
	bool SMT_UpDeviceStatus();						//上传设备状态到金仕达
	bool SMT_GetDeviceTask();						//获取任务
	bool SMT_GetDeviceBlackCardTask(SMARTPOS cPos);	//获取黑名单任务
	bool SMT_InsertTaskToLink(SMARTCOMMPACK Task,bool bFlag=false);	//将任务插入到相应链路
	bool SMT_GetDeviceOneRate(SMARTCOMMPACK *Task);	//从金仕达获取设备的费率
	bool SMT_GetDeviceCardType(SMARTCOMMPACK *Task,char* sBuffer);
	bool SMT_SmartRegister(DWORD nTimeOut);			//前置注册
	bool SMT_SmartFrontLogin(DWORD nTimeOut);		//前置签到
	bool SMT_UpDealRecord(XDHANDLE nHandler,char* sData,int nTimeOut,int *nErrCode,char* sErrMsg); //上传交易记录到金仕达
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
	char		m_cPackPath[256];					//路径
	int			m_drtpno;	
	CPACKHANDLE	m_handler[256];
	char		m_szHost[20];						//IP地址
	int			m_nPort;							//端口号
	CData		m_Data;
public:
	CSmartCommunicationDlg	*m_pDlg;
	void		SetParentpDlg(CSmartCommunicationDlg* pDlg){m_pDlg=pDlg;};
	char		m_szText[256];		//错误信息
	int			m_mainfunc;
	bool		m_bConnectStatus;	//连接状态 true表示连接  false表示失败
};
#endif