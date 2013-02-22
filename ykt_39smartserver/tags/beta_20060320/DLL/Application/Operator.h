// Operator.h: interface for the COperator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATOR_H__E01A02C6_A08C_48FB_A5D0_022E902913BD__INCLUDED_)
#define AFX_OPERATOR_H__E01A02C6_A08C_48FB_A5D0_022E902913BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//定义所有的机型
enum MachineType
{
	MACHINE_TYPE_UNKNOW,   //未知的机型
	MACHINE_TYPE_5301,     //服务器
	MACHINE_TYPE_0201,     //增值机
	MACHINE_TYPE_0226,     //收费机
	MACHINE_TYPE_0228,     //车载机
	MACHINE_TYPE_0230,     //管理机
	MACHINE_TYPE_0232,     //上机上网机
	MACHINE_TYPE_0234,     //淋浴管理机
	MACHINE_TYPE_0240,     //售票机
	MACHINE_TYPE_0130,     //身份识别机
	MACHINE_TYPE_0140,     //检票机
	MACHINE_TYPE_0121,     //计时宝
	MACHINE_TYPE_0224,     //挂失机
	MACHINE_TYPE_0236,     //独立式淋浴计费器
	MACHINE_TYPE_1055,     //手持机（计费）
	MACHINE_TYPE_5501,     //扇型通道机
	MACHINE_TYPE_1056      //手持机(计费+补助)
};

//定义数据类型
enum MacDataType
{
	MACDATA_TYPE_JY,		//为交易类型数据
	MACDATA_TYPE_ZZ,		//为扎帐数据
	MACDATA_TYPE_BZ,		//为补助数据
	MACDATA_TYPE_UNKNOW		//未知的数据类型
};

//*******************************************************************************
//*名称: COperator  
//*功能: 业务层基类
//*******************************************************************************
class COperator  
{
public:
	struct TSMacTypeArray
	{
		MachineType   nType;
		char         *pCode;
		char         *pName;
	};

	struct TSMacDataTypeArray
	{
		MacDataType   nType;
		int           nCode;
		char         *pName;
	};

public:
	static CString  m_strAccTime;		//定时扎帐时间
	static CString  m_strBlackVer;      //黑名单版本
	static CString  m_strRight;         //授权号
	static bool     m_bReadPara;        //已读入参数标志

protected:
	CString         m_strTaskCode;
	bool            m_bMarkCheck;
	bool            m_bMachineNo;

	TSSmartDocEx   *m_pDocEx;
	TSCmdBuffer    *m_pBuffer;
	TSSmartTask    *m_pTask;

	TSSmartDoc     *m_pDoc;			//指向默认的设备信息
	long            m_nIndex;		//指向默认的设备
	long            m_nPort;		//指向当前端口

protected:
	virtual void OnPacketError(long nResult);

	//CRC校验错
	virtual void OnCRCError();

	//MARK值错
	virtual bool OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark);

	//授权号不符合
	virtual void OnAuthNoError(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	//机号错误
	virtual void OnMachineNoError(TSSmartDoc *pDoc, int nNo);

	//不支持的机型
	virtual void OnMacTypeError();

	virtual void WriteFile(char *pszFileName, char *pBuffer);

	//写系统异常日志
	void WriteError(char *pszDeviceID, const char *format, ...);

	//读入业务系统参数
	bool ReadSmartSetup();

public:
	void ReportException(CString strText, BYTE *pszByte, int nLen);

	//得到机型代号
	static MachineType GetMachineType(TSSmartDoc *pSmartDoc);

	//得到数据类型
	MacDataType GetMacDataType(TSCmdBuffer *pBuffer);

	//复位设备
	virtual bool ResetDevice(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	//修改注册号
	virtual bool ModifyRegister(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	virtual bool ModifyRegisterEx(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int nPort);

	//清除该端口数据，重新收集
	virtual bool ClearPortData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer, int nPortNo);

	//修改并保存密码
	virtual bool ModifyPassword(TSSmartTask *pTask, TSSmartDoc *pDoc, unsigned char *ucRawData);

	int GetPos(TSSmartDocEx *pDocEx, long nPort);
	int GetPos(TSSmartDocEx *pDocEx, char *pszReg);
	int GetPosEx(TSSmartDocEx *pDocEx, char *pszID);

	bool ModifyDocRegister(TSSmartDocEx *pDocEx, TSSmartDoc *pDoc, TSCmdBuffer *pBuffer, int nPort,char *szOldReg);

public:
	COperator();
	virtual ~COperator();

	virtual void InitInstance();
	virtual void ExitInstance();

	CString GetTaskCode() const ;
	bool IsEqual(CString strTaskCode) const;

	void TerminateTask(int nFlag = 1);

	virtual bool IsSupportMacType();

	virtual bool CRCValid(BYTE *pszByte, int nPos=26);

	//检测数据包
	virtual bool CheckPacket(TSCmdBuffer *pBuffer);

	//检测返回数据体机号是否相等
	virtual bool CheckMachineNo(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer);

	//检测REMARK值是否相等
	virtual bool CheckMarkValue(int nMark);

	//创建第一个任务包
	virtual long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer) = 0 ;

	//派生类重载, 用于实现具体的业务流程
	virtual long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer) = 0 ;
	//设备终端状态
	long ProcessStatusRequest(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	//任务包结果处理
	long ProcessRequest(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

//*******************************************************************************
//*名称: CSmartLog
//*功能: 业务层日志类
//*******************************************************************************
class CSmartLog
{
protected:
	CString  m_strFileName;

public:
	CSmartLog();
	virtual ~CSmartLog();

	virtual bool Open();
	virtual void Close();

	void Flush();

	virtual void WriteLog(const char *format, ...);
};


#endif // !defined(AFX_OPERATOR_H__E01A02C6_A08C_48FB_A5D0_022E902913BD__INCLUDED_)
