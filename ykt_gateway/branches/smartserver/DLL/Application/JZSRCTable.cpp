
#include "stdafx.h"
#include "JZSRCTable.h"

CSmartJZSRCTable::CSmartJZSRCTable()
{
	strSQL1 = "";
	strSQL2 = "";

	m_bUpdate = true ;

	ZeroMemory(&m_SRC, sizeof(m_SRC));
	ZeroMemory(&m_SRCTotal, sizeof(m_SRCTotal));
}

CSmartJZSRCTable::~CSmartJZSRCTable()
{

}

//*========================================================================================
//*函数: void CSmartJZSRCTable::EnableSaveFile(bool bBool)
//*功能: 设置为是否保存为文件
//*参数: 略
//*返回: 无
//*说明: 虚基类程序
//*========================================================================================
void CSmartJZSRCTable::EnableSaveFile(bool bBool)
{
	m_bSaveFile = bBool ;
}

//*========================================================================================
//*函数: void CSmartJZSRCTable::EnableSaveDB(bool bBool)
//*功能: 设置为是否保存为数据库
//*参数: 略
//*返回: 无
//*说明: 虚基类程序
//*========================================================================================
void CSmartJZSRCTable::EnableSaveDB(bool bBool)
{
	m_bSaveDB = bBool ;
}

bool CSmartJZSRCTable::IsValidDateTime(unsigned char *pDateTime)
{
	if(pDateTime[0] > 100 || 
	   pDateTime[1] >= 13 || pDateTime[1] == 0 || 
	   pDateTime[2] > 31 || pDateTime[2] == 0 ||
	   pDateTime[3] > 24 || 
	   pDateTime[4] > 60 ||  
	   pDateTime[5] > 60 )
	{
		return false;
	}

	return true;
}

//*========================================================================================
//*函数: bool CSmartJZSRCTable::Convert(TSSmartDoc *pDoc, unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 是否成功
//*说明: 虚基类程序
//*========================================================================================
bool CSmartJZSRCTable::Convert(int nAuthNo, TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
	CString  strValue = "" ;
	CString  strText = "";
	CString  strData = "";
	char     szDateTime[7];

	CString strDealCode = "20";

	//收费机 0232 上机上网机
	if( !strcmp(pDoc->m_szMacCode, "0226") || 
		!strcmp(pDoc->m_szMacCode, "0232") )
	{
		strDealCode = "91";
	}
	//增值机
	else if( !strcmp(pDoc->m_szMacCode, "0201") )
	{
		strDealCode = "90";
	}

	CTime  t = CTime::GetCurrentTime();
	strText.Format("%04d-%02d-%02d %02d:%02d:%02d  ", 
		t.GetYear(), t.GetMonth(), t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());

	sprintf(szDateTime, "%04d%02d", t.GetYear(), t.GetMonth()); 

	m_strTableName.Format("Smart_JZSource%04d%02d", t.GetYear(), t.GetMonth());

	strValue.Format("注册号:%.2X%.2X%.2X%.2X ",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, m_SRC.sMachineID);
	strValue.Format("%s", m_SRC.sMachineID); strData+= strValue;

	strValue.Format("扎帐流水:%d ",  ucRawData[6]*256+ucRawData[7]); strText += strValue ;
	GetValue(strValue, m_SRC.nSettleInvoice);
	strValue.Format("%d", m_SRC.nSettleInvoice); strData+= strValue;

	if( !IsValidDateTime(&ucRawData[8])  )
	{
		char szDateTime[24];
		GetCurDateTime(szDateTime);
		strValue = szDateTime;  strText += strValue ;
		GetValue(strValue, m_SRC.sSettleTime);
	}
	else
	{
		strValue.Format("扎帐时间:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[8]+2000,ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12],ucRawData[13]);  strText += strValue ;
		GetValue(strValue, m_SRC.sSettleTime);
	}

	strValue.Format("%s", m_SRC.sSettleTime); strData+= strValue;

	strValue.Format("起始流水号:%d ",ucRawData[14]*256+ucRawData[15]); strText += strValue ;
	GetValue(strValue, m_SRC.nBeginInvoice);
	strValue.Format("%d", m_SRC.nBeginInvoice); strData+= strValue;

	strValue.Format("结束流水号:%d ",ucRawData[16]*256+ucRawData[17]); strText += strValue ;
	GetValue(strValue, m_SRC.nEndInvoice);
	strValue.Format("%d", m_SRC.nEndInvoice); strData+= strValue;

	strValue.Format("正常消费总笔数:%d ",ucRawData[18]*256+ucRawData[19]); strText += strValue ;
	GetValue(strValue, m_SRC.nDealCount);
	strValue.Format("%d", m_SRC.nDealCount); strData+= strValue;

	strValue.Format("正常消费总金额:%d ",ucRawData[20]+ucRawData[21]*256+ucRawData[22]*65536); strText += strValue ;
	GetValue(strValue, m_SRC.nDealAmount);
	strValue.Format("%d", m_SRC.nDealAmount); strData+= strValue;

	strValue.Format("冲正消费总笔数:%d ",ucRawData[23]*256+ucRawData[24]);  strText += strValue ;
	GetValue(strValue, m_SRC.nCancelCount);
	strValue.Format("%d", m_SRC.nCancelCount); strData+= strValue;

	strValue.Format("冲正消费总金额:%d ",ucRawData[25]+ucRawData[26]*256+ucRawData[27]*65536); strText += strValue ;
	GetValue(strValue, m_SRC.nCancelAmount);
	strValue.Format("%d", m_SRC.nCancelAmount); strData+= strValue;

	strValue.Format("异常消费总笔数%d\n",ucRawData[28]*256+ucRawData[29]); strText += strValue ;
	GetValue(strValue, m_SRC.nExcepCount);
	strValue.Format("%d", m_SRC.nExcepCount); strData+= strValue;

	strValue.Format("异常消费总金额%d\n",ucRawData[30]+ucRawData[31]*256+ucRawData[32]*65536); strText += strValue ;
	GetValue(strValue, m_SRC.nExcepACount);
	strValue.Format("%d", m_SRC.nExcepACount); strData+= strValue;

	strValue.Format("其他交易总笔数:%d ",ucRawData[33]*256+ucRawData[34]); strText += strValue ;
	GetValue(strValue, m_SRC.nOtherCount);
	strValue.Format("%d", m_SRC.nOtherCount); strData+= strValue;

	strValue.Format("扎帐标记:%.2X ",ucRawData[35]); strText += strValue ;
	GetValue(strValue, m_SRC.nOuterkeeper);
	strValue.Format("%d", m_SRC.nOuterkeeper); strData+= strValue;

	int nSettType = 0;

	if(ucRawData[35] == 0x00)
		strValue = "初次运行扎帐 ";
	else if(ucRawData[35] == 0x01)
		strValue = "上位机扎帐 ";
	else if(ucRawData[35] == 0x02)
		strValue = "复核扎帐 ";
	else if(ucRawData[35] == 0x03)
	{
		nSettType = 0;
		strValue = "手工扎帐 ";
	}
	else if(ucRawData[35] == 0x04)
	{
		nSettType = 1;
		strValue = "定时扎帐 ";
	}
	else if(ucRawData[35] == 0x05)
	{
		nSettType = 1;
		strValue = "开机扎帐 ";
	}
	else
		strValue = "未知类型 ";
	strValue.Format("CRC:%.2X%.2X\n", ucRawData[36],ucRawData[37]);  strText += strValue ;

	CString strAdjust=GetAdjustCode(pszAdjustCode, m_SRC.nSettleInvoice, 
		m_SRC.sSettleTime, "Smart_Settlement");

	if( strAdjust == "" && 	!IsValidDateTime(&ucRawData[8])  )
	{
		strAdjust = "0204";
	}

	m_pDoc = pDoc ;

	CString strTemp = "" ;

	strTemp = "INSERT INTO " + m_strTableName ;
	strTemp+= "(SMT_RowID, SMT_AuthNo, SMT_Data, SMT_CRC, ";
	strTemp+= "SMT_DateTime, SMT_DealWith, SMT_DealWithDateTime, SMT_AdjustCode) ";
	strTemp+= " VALUES(SMART_JZSOURCE%s_rowid.nextval, %ld, '%s', %d, SYSDATE, 0, NULL, '%s')";

	if( strAdjust == "0102" )
	{
		strSQL1.Format(strTemp, szDateTime, nAuthNo, 
			strData.GetBuffer(0), 0, strAdjust.GetBuffer(0));
	}
	else
	{
		strSQL1.Format(strTemp, szDateTime, nAuthNo, 
			strData.GetBuffer(0), 1, strAdjust.GetBuffer(0));
	}

	strTemp = "INSERT INTO Smart_Settlement(" ;
	strTemp+= " SMT_RowID, SMT_Authno, SMT_MachineID, SMT_Org_id, " ;
	strTemp+= " SMT_SettleInvoice, SMT_SettleTime, SMT_BeginInvoice, " ;
	strTemp+= " SMT_EndInvoice, SMT_DealCount, SMT_DealAmount, " ;
	strTemp+= " SMT_CancelCount, SMT_CancelAmount, SMT_OtherCount, " ;
	strTemp+= " SMT_OperatorID, SMT_KeepingDate, SMT_BatchNo, " ;
	strTemp+= " SMT_SettleType, SMT_DealCode, SMT_EXCEPTCOUNT, SMT_EXCEPTAMOUNT, SMT_ADJUSTCODE) VALUES( " ;
	strTemp+= " SMART_SETTLEMENT_ROWID.nextval, %d, '%s', '%s', " ;
	strTemp+= " %d, to_date('%s','yyyy-mm-dd hh24:mi:ss'), %d, " ;
	strTemp+= " %d, %d, %d, " ;
	strTemp+= " %d, %d, %d, " ;
	strTemp+= " '%d', SYSDATE, %d, " ;
	strTemp+= " %d, '%s', %d, %d,'%s')" ;

	char  szOrg[12];
	if( !strcmp(pDoc->m_szOrgid, "") )
		strcpy(szOrg, " ");
	else
		strcpy(szOrg, pDoc->m_szOrgid);

	strSQL2.Format(strTemp.GetBuffer(0), nAuthNo, m_SRC.sMachineID, szOrg, 
		m_SRC.nSettleInvoice, m_SRC.sSettleTime, m_SRC.nBeginInvoice, 
		m_SRC.nEndInvoice, m_SRC.nDealCount, m_SRC.nDealAmount, 
		m_SRC.nCancelCount, m_SRC.nCancelAmount, m_SRC.nOtherCount, 
		999, 0, 
		nSettType, strDealCode.GetBuffer(0), m_SRC.nExcepCount, m_SRC.nExcepACount, strAdjust.GetBuffer(0));

	strUpdate.Format("Update Smart_Commrec Set  SMT_LASTDEALDATETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_SETTLEINVOICE=%ld, SMT_SETTLETIME=to_date('%s','yyyy-mm-dd hh24:mi:ss'), SMT_BEGININVOICE=%d, SMT_ENDINVOICE=%d Where Smt_AuthNo=%ld ", 
		m_SRC.sSettleTime, m_SRC.nSettleInvoice, m_SRC.sSettleTime, m_SRC.nBeginInvoice, 
		m_SRC.nEndInvoice, nAuthNo);
/*
	CString strString;

	pDoc->m_nFlow = m_SRC.nSettleInvoice;
	pDoc->m_nCardID = 0;
	pDoc->m_nInMoney = m_SRC.nDealAmount;
	pDoc->m_nOutMoney = m_SRC.nCancelAmount;
	pDoc->m_nDealCount++;

	strString.Format("%d&%d&%d&%s&%d&%d&%d",
		pDoc->m_nAuthID, m_SRC.nSettleInvoice, pDoc->m_nDealCount, 
		m_SRC.sSettleTime, 0, m_SRC.nDealAmount, m_SRC.nCancelAmount);

	BroadcastPro(PACKET_CMD_1002, pDoc, strString.GetBuffer(0), strString.GetLength());
*/
	return true;
}

//*========================================================================================
//*函数: bool CSmartJZSRCTable::Write()
//*功能: 保存到文件与数据库
//*参数: 略
//*返回: 无
//*说明: 虚基类程序
//*========================================================================================
bool CSmartJZSRCTable::Write(bool bUpdate)
{
	CString strString = "" ;

	bool bResult1 = false ;
	bool bResult2 = false ;

	m_bUpdate = bUpdate;

	if( IsSaveDB() )
	{
		bResult1 = SaveToDB(strSQL1, strSQL2);
	}

	strString = "" ; 

	if( IsSaveFile() )
	{
		bResult2 = SaveToFile(strText);
	}

	return bResult1&&bResult2;
}

//*========================================================================================
//*函数: bool CSmartJZSRCTable::SvaeToDB(CString strSQL)
//*功能: 保存到数据库
//*参数: 略
//*返回: 成功与否
//*说明: 虚基类程序
//*========================================================================================
bool CSmartJZSRCTable::SaveToDB(CString strSQL1, CString strSQL2)
{
	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase <= 0 )
	{
		ReportLog(RET_DBBUSY, "保存扎帐数据", "不能得到数据库句柄!");
		return false;
	}

//	printf("%s\n", strSQL1.GetBuffer(0));

	long nRec = ExecuteSQL(nDatabase, strSQL1.GetBuffer(0));
	if( nRec != RET_OK )
	{
		printf("%s\n", strSQL1.GetBuffer(0));
		CString strText;

		strText =  "create table " + m_strTableName ;
        strText += "(smt_rowid integer not null primary key,smt_authno number(10,0) not null,";
        strText += "smt_data varchar(100) not null,smt_CRC number(2) , smt_datetime date ,";
        strText += "smt_dealwith number(2),smt_dealwithdatetime date,smt_adjustcode varchar(4)) ";
		ExecuteSQL(nDatabase, strText.GetBuffer(0));

		strText = "create sequence " + m_strTableName + "_rowid start with 1 increment by 1";
		ExecuteSQL(nDatabase, strText.GetBuffer(0));

		if( ExecuteSQL(nDatabase, strSQL1.GetBuffer(0)) != RET_OK )
		{
			FreeDBHandle(nDatabase);
			return false;
		}
	}

//	printf("%s\n", strSQL2.GetBuffer(0));

	nRec = ExecuteSQL(nDatabase, strSQL2.GetBuffer(0));
	if( nRec != RET_OK )
	{
		printf("%s\n", strSQL2.GetBuffer(0));
		FreeDBHandle(nDatabase);
		return false;
	}

	if( m_bUpdate )
	{
		nRec = ExecuteSQL(nDatabase, strUpdate.GetBuffer(0));
		if( nRec != RET_OK )
		{
			printf("%s\n", strUpdate.GetBuffer(0));
			FreeDBHandle(nDatabase);
			return false;
		}
	}

	FreeDBHandle(nDatabase);

	return true;
}

//*========================================================================================
//*函数: bool CSmartJZSRCTable::SvaeToFile(CString strText)
//*功能: 保存到文件
//*参数: 略
//*返回: 成功与否
//*说明: 虚基类程序
//*========================================================================================
bool CSmartJZSRCTable::SaveToFile(CString strText)
{
	return true;
}
