#ifndef __JZSRC_TABLE_H__
#define __JZSRC_TABLE_H__

//*******************************************************************************
//*名称: TSJZSRCSetlment
//*功能: 对应于表SMART_JZSOURCEYYYYMM
//*******************************************************************************
struct TSJZSRCSetlment
{
	long    nAuthno;				//终端机基本参数表的主键
	char    sMachineID[11];			//终端设备ID号（唯一识别）,不能由用户输入
	char    sOrg_id[37];			//所属的组织代码
	long    nSettleInvoice;			//终端结算流水号
	char    sSettleTime[24];		//结账时间
	char    sBeginDealtime[24];		//结算的开始交易时间
	long    nBeginInvoice;			//结算的开始交易流水号
	char    sEndDealtime[24];		//结算的 结束交易时间
	long    nEndInvoice;			//结算的结束交易流水号
	long    nDealCount;				//正常交易笔数
	long    nDealAmount;			//正常交易金额
	long    nCancelCount;			//充正交易笔数
	long    nCancelAmount;			//充正交易金额
	long    nExcepCount;            //异常交易笔数
	long    nExcepACount;           //异常交易金额
	long    nOtherCount;			//其他类型交易笔数
	char    sOperatorID[5];			//用户名代码
	long    nOuterkeeper;			//交易标志，0-交易成功 1-对帐成功 2-入帐成功 3-对帐错 4-入帐错
	char    sKeepingDate[24];		//记帐日期时间
	long    nBatchNo;				//交易批次
	long    nSettleType;			//结算类型：０－操作员结算 １－系统定时自动　２－根据交易流水明细结算
	char    sDealCode[3];			//交易类型代码表
};

//*******************************************************************************
//*名称: TSJZSRCSource
//*功能: 业务层扎帐数据原始凭证表
//*******************************************************************************
struct TSJZSRCSource
{
	long     AuthNo;					//终端机基本参数表
	char     sData[101];				//数据
	long     nCRC;						//CRC是否正确 1表示正确；0表示错误
	char     sDateTime[24];				//收集日期时间
	long     nDealWith;					//是否处理  0表示未处理；1表示已处理
	char     sDealWithDateTime[24];		//处理日期时间
	char     sAdjustCode[5];			//处理时判断该条数据的正确或错
};

//*******************************************************************************
//*名称: CSmartJZSRCTable
//*功能: 业务层扎帐数据转换类
//*******************************************************************************
class CSmartJZSRCTable
{
protected:
	CString       strSQL1;
	CString       strSQL2;
	CString       strText;
	CString       strUpdate;

	CString       m_strTableName;

	TSSmartDoc   *m_pDoc;

	bool          m_bSaveDB;
	bool          m_bSaveFile;
	bool          m_bUpdate;

public:
	TSJZSRCSetlment   m_SRC;
	TSJZSRCSetlment   m_SRCTotal;

protected:
	bool SaveToFile(CString strText);
	bool SaveToDB(CString strSQL1, CString strSQL2);

public:
	CSmartJZSRCTable();
	virtual ~CSmartJZSRCTable();

	bool IsSaveFile() const { return m_bSaveFile; }
	bool IsSaveDB() const { return m_bSaveDB; }

	void EnableSaveFile(bool bBool);
	void EnableSaveDB(bool bBool);

	bool Convert(int nAuthNo, TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode);

	bool Write(bool bUpdate = true );
	bool IsValidDateTime(unsigned char *pDateTime);
};

#endif //__JZSRC_TABLE_H__