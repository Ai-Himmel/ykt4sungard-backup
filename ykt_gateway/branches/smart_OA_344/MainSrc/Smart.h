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
	bool		Smt_CollectDataProcess();					//交易记录收集
	bool		Smt_ShowerDataProcess();					//淋浴记录收集	
	bool		Smt_WLportDataProcess();					//
	bool		Smt_QueryDeviceStatus();					//查询所有设备的当前状态
	bool		SMT_ContinueCollectData( int nPostion);
	bool		SMT_ConfirmData(SMARTCOMMPACK* Doc);		//记录确认
	bool		SMT_OpenCtrl(SMARTCOMMPACK* Doc);			//开水
	bool		SMT_CloseCtrl(SMARTCOMMPACK* Doc);			//关水
	bool		SMT_SetWorkKey(SMARTCOMMPACK* Doc);			//设置工作密钥和钱包号
	bool		SMT_SetCardType(SMARTCOMMPACK* Doc);		//设置卡类
	bool		SMT_GetCardType(SMARTCOMMPACK* Doc);		//上传卡类
	bool        SMT_SetFreeRate(SMARTCOMMPACK* Doc);		//设置工作费率
	bool		SMT_SetAddTotalMoney(SMARTCOMMPACK* Doc);   //设置充值总额
	bool        SMT_GetFreeRate(SMARTCOMMPACK* Doc);		//得到工作费率
	bool		SMT_SetWhiteCard(SMARTCOMMPACK* Doc);		//增加一条白名单
	bool		SMT_DelWhiteCard(SMARTCOMMPACK* Doc);		//删除一条白名单
	bool		SMT_ConfirmWhiteCard(SMARTCOMMPACK* Doc);	//判断一条白名单
	bool		SMT_DelAllWhiteCard(SMARTCOMMPACK* Doc);	//删除所有白名单
	bool		SMT_SetPosPlace(SMARTCOMMPACK* Doc);		//设置计费器地点
	bool		SMT_GetPosPlace(SMARTCOMMPACK* Doc);		//上传计费器地点
	bool		SMT_SetWarmMoney(SMARTCOMMPACK* Doc);		//设置报警金额
	bool		SMT_GetWarmMoney(SMARTCOMMPACK* Doc);		//上传报警金额
	bool		SMT_SetBlackCard(SMARTCOMMPACK* Doc);		//增加一条黑名单
	bool		SMT_DelBlackCard(SMARTCOMMPACK* Doc);		//删除一条黑名单
	bool		SMT_BroadCastBlackCard(SMARTCOMMPACK* Doc); //广播黑名单
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
	int				m_nPortTotal;		//服务器的端口总数
	char			m_regno[5];			//服务器注册号
	char			m_IDNo[5];			//服务ID号
	char			m_MacCode[4];		 //机型代码(类型)
	int				m_MacNum;			 //服务器机号
	IP_PAR			m_IpPar;			 //服务的端口号、IP地址
	int				m_nTotalPos;         //服务目前所挂终端设备总数量
	int				nCommunicationStatus; //服务器通讯状态
	SMARTPOS		m_SmartPos[MAX_POSNO]; //保存该服务所带终端数据信息
	int				m_SmartPosConnCnts[MAX_POSNO]; // 保存POS连接数据
	int				m_SmartPosTaskPos;		//保存当前获取任务的设备位置
	int				m_TaskCount;			//待执行的任务数
	int				 m_SmartPosPostion;	   //在m_SmartPos[MAX_POSNO]的位置
	OVERLAPPED		 m_ReadOver;		   //IO重叠的接收
	OVERLAPPED		 m_WriteOver;		   //IO重叠的发送
	unsigned long	 m_nWriteBytes;		    //发送到端口数据长度
	unsigned long	 m_nReadBytes;		    //接收端口数据长度
	unsigned char	 m_ucReadBytes[1024];    //接收到的数据
	char			 m_szErrorText[1024];	//保存通讯时的错误信息
	DWORD			 m_nContinueTime;		//连续时间内未收到设备的数据		
	char			 m_CreatePath[256];		//保存路径
	DWORD			 m_nActionTime;			//每做一个业务耗时
	DWORD			 m_nWaitRecvTime;		//等待真正接收数据时间	
	DWORD			 m_nStartTime;			//时间	
	int				 m_nMaxMacNo;			//设备的最大机号
	DWORD			 m_nQueryFailCount;		//连接查询次数
	int				 m_nTaskResultStatus;	//任务处理结果
	byte			 m_sCurDate[9];			//当前日期
	int				 m_nTaskPoint;			//任务指针
	int				 m_nInsertTaskPoint;	//插入任务指针
	int				 m_nPostion;			//采集数据的位置
	//////////////////////////////////////////////////////////////////////////
	// 任务状态
public:
	CSmartCommunicationDlg* m_pDialog; //显示类	
	CData		m_Data;					//工具类
	CMyLog		m_Log;					//日志类	
	SMARTCOMMPACKSTR	m_STaskArr;		//任务
public:
	void Run();	
	CSmart();
	virtual ~CSmart();
protected:
	bool		SMT_VerifyClock();
	bool		SMT_GetHistoryData(SMARTCOMMPACK* Doc);		//采集历史数据	
	bool		SMT_SetClock(SMARTCOMMPACK* Doc);			//设置终端机时钟
	bool		SMT_GetClock(SMARTCOMMPACK* Doc);			//取终端机时钟	
	bool		SMT_SetOpenSaleCtrl(SMARTCOMMPACK* Doc);	//打开消费开关		
	bool		SMT_Login(SMARTCOMMPACK* Doc);				//终端签到	
	bool		SMT_ReConnectServer();						//重新连接服务
	bool		SMT_CollateClock();	
	bool		SMT_RequestLogin( BYTE *RespData,int nPosition);	//淋浴机签到
	bool		SMT_RequestConsume( BYTE *RespData,int nPosition);	//淋浴名单交易确认		
	bool		SMT_CheckCardNoAvailability(BYTE *cCardNo);			//检查卡的有效性 真为有效，假为无效		
	bool		SMT_RequestUpConsumeRecord( BYTE *RespData,int nRespDataLen,int nPostion);	//处理淋浴机交易数据	
	bool		SMT_ProcessDeviceRegNoErr(int NetWorkType,int nPostion);	//处理注册号不符的情况
	bool		SMT_ExecuteCmd411(SMARTCOMMPACK* Doc);
	bool		GetDeviceInfo(char *cDeviceID,int *nPosition);		//根据ID号获取该设备在子设备数组中的位置
	bool		ValidateData(BYTE* Data,int DataLen);				//检查收到的终端数据是否合法
	bool		DealWithRecvData(SMARTCOMMPACK* Doc, BYTE* RecvData);	//处理收到的数据	
	char*		GetStatusErrMsg(BYTE StatusCode);
	bool		CreateRecordPath();
	bool		SMT_SettleAccount( int nPosition);			//结帐记录确认
	bool		SMT_GetDeviceID(SMARTCOMMPACK* Doc);		//获取ID号
	bool		SMT_SetDeviceID(SMARTCOMMPACK* Doc);		//设置ID号
	bool		SMT_ProcessIDError(int nPostion);			//处理ID号错
	bool		SMT_ProcessMACError(int nPostion);			//处理机号错
	bool		SMT_ListRequestConfirm(int nPostion);		//名单申请确认
	bool		SMT_SetMainPara(SMARTCOMMPACK* Doc);		//设置收费机主参数
	bool		SMT_GetMainPara(SMARTCOMMPACK* Doc);		//上传终端主参数
	bool		SMT_SetCardtypeCon(SMARTCOMMPACK* Doc);		//扩展卡类
	bool		SMT_SetWhiteListAndVer(SMARTCOMMPACK *Doc);
public:
	void		WriteLog(char* msg);						//写日志文件
	bool		WriteTradeDeal(char* Data);					//写交易记录文件	
public:
	inline void SetParent(CSmartCommunicationDlg *pt){m_pDialog=pt;};
	bool		InsertTask(SMARTCOMMPACK *Task);			//向任务池中压入一条任务
	bool		GetTask(SMARTCOMMPACK *cTask);
	bool		SMT_InsertTaskResult(SMARTCOMMPACK Doc,bool bStatus);		//任务结果入list
public:			//通讯方法
	virtual bool  Open()=0;
	virtual void  Close()=0;
	virtual bool  ReConnect()=0;
	virtual bool  WaitRecv(int WaitTime)=0 ;	
	virtual bool  PostSend(char *lpBuffer, int nBufSize, long nTimeOut)=0;
	virtual bool  PostRecv(char *lpBuffer, int nBufSize, long nTimeOut)=0;	
	virtual bool  RecvQueryData(byte *lpData, int*nlpDatalen,DWORD nTimeOut)=0;
};
#endif 