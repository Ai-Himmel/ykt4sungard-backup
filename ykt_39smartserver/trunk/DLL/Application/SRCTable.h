 #ifndef __SRC_TABLE_H__
#define __SRC_TABLE_H__

//*******************************************************************************
//*名称: TSSRCSFTable
//*功能: 0226 收费机,0228 车载机,0201 增值机,0232 上机上网机
//*      0230 管理机,0234 管理机(淋浴专用),0236 独立式淋浴计费器,0240 售票机,
//*      0130 身份识别机,1055 手持机（计费）
//*******************************************************************************
struct TSSRCSFTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
	char    sCommVer[3];		//通信版本号（十六进制）
	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号
	long    nTimes;				//次数
	char    sWalletcode[3];		//钱包
	long    nInMoney;           //入卡金额
	long    nOutMoney;          //出卡金额

	char    sDealCode1[3];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;

public:
	void Clear();
	void AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);

};

//*******************************************************************************
//*名称: TSSRCBZTable
//*功能: 5301 数据服务器(补助记录), 1056 手持机(计费+补助)
//*******************************************************************************
struct TSSRCBZTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
	char    sCommVer[3];		//通信版本号（十六进制）
	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号
	long    nUserInvoice;       //卡片使用流水

	long    nTimes;             //IC卡使用次数（开环钱包可以为空）
	char    sWalletCode[3];     //电子钱包代码，对应钱包标识代码表
	long    nInMoney;           //入卡值，以分为单位
	long    nOutMoney;          //出卡值，以分为单位
	long    nBatch;             //批次号

	char    sInductorNo[9];     //感应头ID编号,工作模式5时,保存借出还入钥匙的设备(0~15)
	long    nDutyFlag;          //上/下班标记 1上班/0班
	long    nTimerType;         //考勤类型,工作模式5时,保存房间号
	long    nWorkMode;          //工作模式(1~4)
	long    nManagerCardNo;     //管理员卡号(4byte)
	char    sTicketEndDate[12]; //该票截止日期(年月日)

	char    sDealCode1[3];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;

public:
	void Clear();
	void AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);
};

//*******************************************************************************
//*名称: TSSRCJSBTable
//*功能: 0121 计时宝,5501 扇型通道机
//*******************************************************************************
struct TSSRCJSBTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
	char    sCommVer[3];		//通信版本号（十六进制）
	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号

	long    nInductorNo;        //感应头编号,工作模式5时,保存借出还入钥匙的设备(0~15)
	long    nDutyFlag;          //上/下班标记 1上班/0班
	long    nTimerType;         //考勤类型,工作模式5时,保存房间号
	long    nWorkMode;          //工作模式(1~4)
	long    nManagerCardNo;     //管理员卡号(4byte)

	char    sDealCode1[3];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;

public:
	void Clear();
	void AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);

};

//*******************************************************************************
//*名称: TSSRCJPJTable
//*功能: 0140 检票机
//*******************************************************************************
struct TSSRCJPJTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
	char    sCommVer[3];		//通信版本号（十六进制）
	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡片结构代码(十六进制)
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号

	char    sWicketID[9];       //售票点终端ID
	long    nTicket;            //票号
	char    sTicketEndDate[12]; //该票截止日期(年月日)

	char    sDealCode1[3];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;

public:
	void Clear();
	void AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);
};

//*******************************************************************************
//*名称: TSSRCGSJTable
//*功能: 0224 挂失机 
//*******************************************************************************
struct TSSRCGSJTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//上传数据的注册号
	char    sCommVer[3];		//通信版本号（十六进制）
	char    sCommStart[3];		//数据通信启动原因（十六进制）
	char    sMachineCode[5];	//机型代码
	long    nInvoiceNo;			//终端交易流水号
	char    sDealDateTime[24];	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//卡型代码
	long    nICCardCode;		//IC卡类别代码(预留)
	char    sShowCardNo[11];	//显示卡号
	long    nCardID;			//IC卡交易号或显示卡号/序列号
    char    sPassword[17];      //个人密码（修改密码为：旧个人密码（6），新个人密码（6）；挂失为：8字节密文,
	char    sDealCode1[3];      //终端交易代码（十六进制）
	char    sCRCData[9];        //数据体CRC 校验码（十六进制）
	char    sDateTime[24];      //收集日期时间
	char    sAdjustCode[5];     //校验结果（参见校验结果代码表），Null表示未校验
	char    sDealWithDateTime[24];  //校验日期时间
	char    sOperator[5];           //操作员号
	long    nSendflag;              //发送标志
	long    nCheckStep;             //
	char    sCheckResult[5];
	char    sCheckDate[24];
	char    sCheckKeepingdate[24];
	long    nRepeatNo;

public:
	void Clear();
	void AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);
};

//*******************************************************************************
//*名称: CSmartSRCTable
//*功能: 业务层实时收集数据转换类(虚基类)
//*******************************************************************************
class CSmartSRCTable
{
protected:
    MachineType   m_nType;
	TSSmartDoc   *m_pDoc;

	bool          m_bUpdate;
	bool          m_bSaveDB;
	bool          m_bSaveFile;

	long          m_nDealMoney;

	CString		  m_strLastTime;

protected:
	bool SaveToFile(CString strText);
	bool SaveToDB(CString strSQL);

	virtual long ConvertDoc(unsigned char *ucRawDatachar, char *pszAdjustCode) = 0 ;

	virtual CString GetStringSQL() = 0 ;
	virtual CString GetStringText() = 0 ;
	virtual CString GetStringUpdate() = 0 ;
	virtual CString GetStringProc() = 0 ;

public:
	CSmartSRCTable() 
	{ 
		m_nDealMoney = 0 ;
		m_nType = MACHINE_TYPE_UNKNOW;
		m_bUpdate = false ;
	} 

	virtual ~CSmartSRCTable() { }

	bool IsSaveFile() const { return m_bSaveFile; }
	bool IsSaveDB() const { return m_bSaveDB; }

	void EnableSaveFile(bool bBool);
	void EnableSaveDB(bool bBool);

	bool Convert(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);
	bool Write(bool bUpdate = true);

	static CSmartSRCTable* Alloc(TSSmartDoc *pDoc);
	static void Release(CSmartSRCTable *pTable);

	friend class CHistoryData;
	friend class CCollectionData;
};

//*******************************************************************************
//*名称: CSmartSRCBZTable
//*功能: 0226 收费机,0228 车载机,0201 增值机,0232 上机上网机 .....
//*******************************************************************************
class CSmartSRCSFTable : public TSSRCSFTable, public CSmartSRCTable
{
public:
	CSmartSRCSFTable() {   Clear(); }
	virtual ~CSmartSRCSFTable() {   }

protected:
	long ConvertDoc(unsigned char *ucRawData, char *pszAdjustCode) 
	{
		AssignBy(m_pDoc, ucRawData, pszAdjustCode);
		return (nInMoney - nOutMoney);
	}

	CString GetStringSQL() { return strSQL; }
	CString GetStringText() { return strText; }
	CString GetStringUpdate()
	{
		CString strString;
		strString.Format("UPDATE smart_commrec SET  SMT_LASTDEALDATETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_COMMDATETIME=sysdate, SMT_LASTINVOICENO=%ld where SMT_AUTHNO=%ld", 
			sDealDateTime, nInvoiceNo, nAuthID);
		return strString;
	}

	CString GetStringProc()
	{
		return strProcStore;
	}

	friend class CHistoryData;
	friend class CCollectionData;
};


//*******************************************************************************
//*名称: TSSRCBZTable
//*功能: 5301 数据服务器(补助记录), 1056 手持机(计费+补助)
//*******************************************************************************
class CSmartSRCBZTable : public TSSRCBZTable, public CSmartSRCTable
{
public:
	CSmartSRCBZTable() {   Clear(); }
	virtual ~CSmartSRCBZTable() {  }

protected:
	long ConvertDoc(unsigned char *ucRawData, char *pszAdjustCode) 
	{
		AssignBy(m_pDoc, ucRawData, pszAdjustCode);
		return (nInMoney - nOutMoney);
	}

	CString GetStringSQL() { return strSQL; }
	CString GetStringText() { return strText; }
	CString GetStringUpdate()
	{
		CString strString;
		strString.Format("UPDATE smart_commrec SET  SMT_LASTDEALDATETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_COMMDATETIME=sysdate, SMT_LASTINVOICENO=%ld where SMT_AUTHNO=%ld", 
			sDealDateTime, nInvoiceNo, nAuthID);
		return strString;
	}
	CString GetStringProc()
	{
		return strProcStore;
	}

	friend class CHistoryData;
	friend class CCollectionData;
};

//*******************************************************************************
//*名称: CSmartSRCJSBTable
//*功能: 0121 计时宝,5501 扇型通道机
//*******************************************************************************
class CSmartSRCJSBTable : public TSSRCJSBTable, public CSmartSRCTable
{
public:
	CSmartSRCJSBTable() {   Clear(); }
	virtual ~CSmartSRCJSBTable() {  }

protected:
	long ConvertDoc(unsigned char *ucRawData, char *pszAdjustCode) 
	{
		AssignBy(m_pDoc, ucRawData, pszAdjustCode);
		return 0;
	}

	CString GetStringSQL() { return strSQL; }
	CString GetStringText() { return strText; }
	CString GetStringUpdate()
	{
		CString strString;
		strString.Format("UPDATE smart_commrec SET  SMT_LASTDEALDATETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_COMMDATETIME=sysdate, SMT_LASTINVOICENO=%ld where SMT_AUTHNO=%ld", 
			sDealDateTime, nInvoiceNo, nAuthID);
		return strString;
	}
	CString GetStringProc()
	{
		return strProcStore;
	}

	friend class CHistoryData;
	friend class CCollectionData;
};

//*******************************************************************************
//*名称: CSmartSRCJPJTable
//*功能: 0140 检票机
//*******************************************************************************
class CSmartSRCJPJTable : public TSSRCJPJTable, public CSmartSRCTable
{
public:
	CSmartSRCJPJTable() {   Clear(); }
	virtual ~CSmartSRCJPJTable() {  }

protected:
	long ConvertDoc(unsigned char *ucRawData, char *pszAdjustCode) 
	{
		AssignBy(m_pDoc, ucRawData, pszAdjustCode);
		return 0;
	}

	CString GetStringSQL() { return strSQL; }
	CString GetStringText() { return strText; }
	CString GetStringUpdate()
	{
		CString strString;
		strString.Format("UPDATE smart_commrec SET SMT_LASTDEALDATETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_COMMDATETIME=sysdate, SMT_LASTINVOICENO=%ld where SMT_AUTHNO=%ld", 
			sDealDateTime, nInvoiceNo, nAuthID);
		return strString;
	}
	CString GetStringProc()
	{
		return strProcStore;
	}

	friend class CHistoryData;
	friend class CCollectionData;
};

//*******************************************************************************
//*名称: CSmartSRCJPJTable
//*功能: 0224 挂失机 
//*******************************************************************************
class CSmartSRCGSJTable : public TSSRCGSJTable, public CSmartSRCTable
{
public:
	CSmartSRCGSJTable() {   Clear(); }
	virtual ~CSmartSRCGSJTable() {  }

protected:
	long ConvertDoc(unsigned char *ucRawData, char *pszAdjustCode) 
	{
		AssignBy(m_pDoc, ucRawData, pszAdjustCode);
		return 0;
	}

	CString GetStringSQL() { return strSQL; }
	CString GetStringText() { return strText; }
	CString GetStringUpdate()
	{
		CString strString;
		strString.Format("UPDATE smart_commrec SET SMT_LASTDEALDATETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_COMMDATETIME=sysdate, SMT_LASTINVOICENO=%ld where SMT_AUTHNO=%ld", 
			sDealDateTime, nInvoiceNo, nAuthID);
		return strString;
	}
	CString GetStringProc()
	{
		return strProcStore;
	}

	friend class CHistoryData;
	friend class CCollectionData;
};

#endif //__SRC_TABLE_H__
 