
#include "stdafx.h"
#include "SRCTable.h"

//*========================================================================================
//*函数: void TSSRCSFTable::Clear()
//*功能: 清除数据值
//*参数: 略
//*返回: 无
//*说明: 0226 收费机,0228 车载机,0201 增值机,0232 上机上网机
//*      0230 管理机,0234 管理机(淋浴专用),0236 独立式淋浴计费器,0240 售票机,
//*      0130 身份识别机,1055 手持机（计费）
//*========================================================================================
void TSSRCSFTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID             = 0 ;				   //Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //传数据的注册号
	ZeroMemory(sCommVer, sizeof(sCommVer));    //通信版本号（十六进制）
	ZeroMemory(sCommStart, sizeof(sCommStart));//数据通信启动原因（十六进制）
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //机型代码
	nInvoiceNo          = 0 ;						 //终端交易流水号
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));			 //卡片结构代码(十六进制)
	nICCardCode          = 0 ;						 //IC卡类别代码(预留)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));	 //显示卡号
	nCardID              = 0 ;						 //IC卡交易号或显示卡号/序列号
	nTimes               = 0 ;					     //次数
	ZeroMemory(sWalletcode, sizeof(sWalletcode));    //钱包
	nInMoney             = 0 ;						 //入卡金额
	nOutMoney            = 0 ;						 //出卡金额

	ZeroMemory(sDealCode1, sizeof(sDealCode1));   //终端交易代码（十六进制）
	ZeroMemory(sCRCData, sizeof(sCRCData));       //数据体CRC 校验码（十六进制）
	ZeroMemory(sDateTime, sizeof(sDateTime));     //收集日期时间
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode)); //校验结果（参见校验结果代码表），Null表示未校验
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //校验日期时间
	ZeroMemory(sOperator, sizeof(sOperator));  //操作员号

	nSendflag             = 0 ;      //发送标志
	nCheckStep            = 0 ;      //
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*函数: void TSSRCSFTable::AssignBy(unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 无
//*说明: 0226 收费机,0228 车载机,0201 增值机,0232 上机上网机
//*      0230 管理机,0234 管理机(淋浴专用),0236 独立式淋浴计费器,0240 售票机,
//*      0130 身份识别机,1055 手持机（计费）
//*========================================================================================
void TSSRCSFTable::AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
	CString strValue, strField, strTableName;

	strTableName.Format("SMART_SRC%d", pDoc->m_nAuthID);

	nAuthID = pDoc->m_nAuthID ;
	strcpy(sMachineCode , pDoc->m_szMacCode);

	CTime  t = CTime::GetCurrentTime();
	strText.Format("%04d-%02d-%02d %02d:%02d:%02d  ", 
		t.GetYear(), t.GetMonth(), t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());

	strValue.Format("注册号:%.2X%.2X%.2X%.2X ", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("通信版本:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("钱包号:%d ",ucRawData[5]>>4); strText += strValue ;
	GetValue(strValue, sWalletcode);

	strValue.Format("启动原因:%.2X ",ucRawData[5]&0x0F); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("交易卡号:%d ",ucRawData[8]*65536+ucRawData[9]*256+ucRawData[10]); strText += strValue ;
	GetValue(strValue, nCardID);

	strValue.Format("交易流水号:%.5d ",ucRawData[6]*256+ucRawData[7]); strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	if( ucRawData[12] >= 100 || ucRawData[13] >= 100 || 
		ucRawData[14] >= 100 || ucRawData[15] >= 100  || ucRawData[16] >= 100 )
	{
		strValue.Format("交易时间:%04d-%02d-%02d %02d:%02d:%02d ", 2000, 1, 1, 1,1,1);
	    strText += strValue ;
	}
	else
	{
		strValue.Format("交易时间:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[11]+2000,ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]); strText += strValue ;
	}

	GetValue(strValue, sDealDateTime);

	strValue.Format("卡片累计使用次数:%d ",ucRawData[17]*256+ucRawData[18]); strText += strValue ;
	GetValue(strValue, nTimes);

	strValue.Format("入卡金额(分):%d ",ucRawData[19]+ucRawData[20]*256+ucRawData[21]*65536); strText += strValue ;
	GetValue(strValue, nInMoney);

	strValue.Format("出卡金额(分):%d ",ucRawData[22]+ucRawData[23]*256+ucRawData[24]*65536); strText += strValue ;
	GetValue(strValue, nOutMoney);

	strValue.Format("交易标记:%.2X ",ucRawData[25]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	if(ucRawData[25] == 0x00)
		strValue = "黑卡交易 "; 
	else if(ucRawData[25] == 0x02)
		strValue = "中途拔卡 ";
	else if(ucRawData[25] == 0x03)
		strValue = "钱包格式错 ";
	else if(ucRawData[25] == 0x05)
		strValue = "无法写卡 ";
	else if(ucRawData[25] == 0x10)
		strValue = "密码错误 ";
	else if(ucRawData[25] == 0xFA)
		strValue = "充值交易 ";
	else if(ucRawData[25] == 0xFE)
		strValue = "冲正交易 ";
	else if(ucRawData[25] == 0x99)
		strValue = "正确交易 ";
	else 
		strValue = "未知类型交易 ";

    strText += strValue ;

	strValue.Format("CRC:%.2X%.2X ",ucRawData[26],ucRawData[27]); strText += strValue ;
	GetValue(strValue, sCRCData);

	CString strAdjust=GetAdjustCode(pszAdjustCode, nInvoiceNo, sDealDateTime, strTableName);

	strText += "\n";

	strField=  " SMT_RowID, SMT_AuthNo, SMT_AuthData, SMT_CommVer, " ;
	strField+= " SMT_CommStart, SMT_MachineCode, SMT_InvoiceNo, SMT_DealDateTime, " ;
	strField+= " SMT_UseCard, SMT_ICCardCode, SMT_ShowCardNo, SMT_CardID, " ;
	strField+= " SMT_Times, SMT_WalletCode, SMT_InMoney, SMT_OutMoney, " ;

	strField+= " SMT_DealCode1, SMT_CRCData, SMT_DateTime, SMT_ADJUSTCODE " ;

	strValue.Format(" %s_rowid.nextval,  %d, '%s', '%s', "
					"'%s', '%s', %d,  '%s', "
	                "'%s',  %d, '%s', '%d', "
	                " %d,   '%s', %d, '%d', "
	                "'%s', '%s', SYSDATE, '%s' ",
					strTableName.GetBuffer(0), nAuthID, sAuthData, sCommVer,
					sCommStart, sMachineCode, nInvoiceNo, sDealDateTime, 
					sUseCard, nICCardCode, sShowCardNo, nCardID,
					nTimes, sWalletcode, nInMoney, nOutMoney, 
					sDealCode1, sCRCData, strAdjust.GetBuffer(0));
	strSQL.Format("INSERT INTO %s(%s) VALUES(%s)", strTableName.GetBuffer(0), 
		strField.GetBuffer(0), strValue.GetBuffer(0));

	pDoc->m_nFlow = nInvoiceNo;
	pDoc->m_nCardID = nCardID;
	pDoc->m_nInMoney = nInMoney;
	pDoc->m_nOutMoney = nOutMoney;
	pDoc->m_nDealCount++;

	CString strString;
	strString.Format("%d&%d&%d&%s&%d&%.2f&%.2f",
		pDoc->m_nAuthID, pDoc->m_nDealCount, nInvoiceNo,
		sDealDateTime, nCardID, (float)(nInMoney-nOutMoney)/100, (float)nOutMoney/100);

	BroadcastPro(PACKET_CMD_1002, pDoc, strString.GetBuffer(0), strString.GetLength());
}

//*========================================================================================
//*函数: void TSSRCBZTable::Clear()
//*功能: 清除数据值
//*参数: 略
//*返回: 无
//*说明: 5301 数据服务器(补助记录), 1056 手持机(计费+补助)
//*========================================================================================
void TSSRCBZTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID             = 0 ;	//Auth ID

	ZeroMemory(sAuthData, sizeof(sAuthData));  //传数据的注册号
	ZeroMemory(sCommVer, sizeof(sCommVer));  //通信版本号（十六进制）
	ZeroMemory(sCommStart, sizeof(sCommStart));  //数据通信启动原因（十六进制）
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //机型代码
	nInvoiceNo          = 0 ;	//终端交易流水号
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //卡片结构代码(十六进制)
	nICCardCode          = 0 ;	//IC卡类别代码(预留)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //显示卡号
	nCardID              = 0 ;	//IC卡交易号或显示卡号/序列号

	nTimes               = 0;   //IC卡使用次数（开环钱包可以为空）
	ZeroMemory(sWalletCode, sizeof(sWalletCode));  //电子钱包代码，对应钱包标识代码表
	nInMoney             = 0;   //入卡值，以分为单位
	nOutMoney            = 0;   //出卡值，以分为单位
	nBatch               = 0;   //批次号

	ZeroMemory(sInductorNo, sizeof(sInductorNo));  //感应头ID编号,工作模式5时,保存借出还入钥匙的设备(0~15)
	nDutyFlag            = 0;   //上/下班标记 1上班/0班
	nTimerType           = 0;   //考勤类型,工作模式5时,保存房间号
	nWorkMode            = 0;   //工作模式(1~4)
	nManagerCardNo       = 0;   //管理员卡号(4byte)
	ZeroMemory(sTicketEndDate, sizeof(sTicketEndDate));  //该票截止日期(年月日)

	ZeroMemory(sDealCode1, sizeof(sDealCode1));       //终端交易代码（十六进制）
	ZeroMemory(sCRCData, sizeof(sCRCData));       //数据体CRC 校验码（十六进制）
	ZeroMemory(sDateTime, sizeof(sDateTime));       //收集日期时间
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));       //校验结果（参见校验结果代码表），Null表示未校验
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //校验日期时间
	ZeroMemory(sOperator, sizeof(sOperator));  //操作员号

	nSendflag             = 0 ;      //发送标志
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*函数: void TSSRCBZTable::AssignBy(unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 无
//*说明: 5301 数据服务器(补助记录), 1056 手持机(计费+补助)
//*========================================================================================
void TSSRCBZTable::AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
	CString strValue, strField, strTableName;

	strTableName.Format("SMART_SRC%d", pDoc->m_nAuthID);

	nAuthID = pDoc->m_nAuthID ;

	CTime  t = CTime::GetCurrentTime();
	strText.Format("%04d-%02d-%02d %02d:%02d:%02d  ", 
		t.GetYear(), t.GetMonth(), t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());

	strValue.Format("注册号:%.2X%.2X%.2X%.2X ",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("通信版本:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("启动原因:%.2X ",ucRawData[5]); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("机型代码:%.2X%.2X ",ucRawData[6],ucRawData[7]);  strText += strValue ;
	GetValue(strValue, sMachineCode);

	strValue.Format("补助流水号:%.5d ",ucRawData[8]*256+ucRawData[9]); strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	strValue.Format("补助时间:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[10]+2000,ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15]); strText += strValue ;
	GetValue(strValue, sDealDateTime);

	strValue.Format("卡型代码:%.2X ",ucRawData[16]); strText += strValue ;
	GetValue(strValue, sUseCard);

	strValue.Format("卡类:%d ",ucRawData[17]);  strText += strValue ;
	GetValue(strValue, nICCardCode);

	strValue.Format("显示卡号:%.2X%.2X%.2X%.2X%.2X ",ucRawData[18],ucRawData[19],ucRawData[20],ucRawData[21],ucRawData[22]);  strText += strValue ;
	GetValue(strValue, sShowCardNo);

	strValue.Format("交易卡号:%d ",ucRawData[23]*256*256+ucRawData[24]*256+ucRawData[25]); strText += strValue ;
	GetValue(strValue, nCardID);

	strValue.Format("卡片使用流水:%d ",ucRawData[26]*256+ucRawData[27]); strText += strValue ;
	GetValue(strValue, nTimes);

	strValue.Format("钱包属性代码:%d ",ucRawData[28] & 0x0F); strText += strValue ;
	GetValue(strValue, sWalletCode);

	int flag = ucRawData[28] & 0xF0;

	strValue.Format("补助金额:%d ",ucRawData[29]+ucRawData[30]*256);  strText += strValue ;
	GetValue(strValue, nInMoney);

	strValue.Format("钱包余额:%d ",ucRawData[31]+ucRawData[32]*256+ucRawData[33]*65536); strText += strValue ;
	GetValue(strValue, nOutMoney);

	if( !flag )
	{
		nInMoney = nInMoney + nOutMoney;
	}
	else
	{
		nInMoney = nOutMoney - nInMoney;
	}

	strValue.Format("补助批次号:%d ",ucRawData[34]*256+ucRawData[35]); strText += strValue ;
	GetValue(strValue, nBatch);

	strValue.Format("交易标记:%.2X ",ucRawData[36]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	if(ucRawData[25] == 0x00)
		strValue = "黑卡交易 ";
	else if(ucRawData[25] == 0x02)
		strValue = "中途拔卡 ";
	else if(ucRawData[25] == 0x03)
		strValue = "钱包格式错 ";
	else if(ucRawData[25] == 0x05)
		strValue = "无法写卡 ";
	else if(ucRawData[25] == 0x10)
		strValue = "密码错误 ";
	else if(ucRawData[25] == 0xFA)
		strValue = "充值交易 ";
	else if(ucRawData[25] == 0xFE)
		strValue = "冲正交易 ";
	else if(ucRawData[25] == 0x99)
		strValue = "正确交易 ";
	else 
		strValue = "未知交易 ";

	strText += strValue ;

	strValue.Format("CRC:%.2X%.2X ", ucRawData[37],ucRawData[38]); strText += strValue ;
	GetValue(strValue, sCRCData);

	CString strAdjust=GetAdjustCode(pszAdjustCode, nInvoiceNo, sDealDateTime, strTableName);

	strText += "\n";

	strField=  " SMT_RowID, SMT_AuthNo, SMT_AuthData, SMT_CommVer, " ;
	strField+= " SMT_CommStart, SMT_MachineCode, SMT_InvoiceNo, SMT_DealDateTime, " ;
	strField+= " SMT_UseCard, SMT_ICCardCode, SMT_ShowCardNo, SMT_CardID, " ;
	strField+= " SMT_Times, SMT_WalletCode, SMT_InMoney, SMT_OutMoney, " ;
	strField+= " SMT_Batch, SMT_InductorNo, SMT_DutyFlag, SMT_TimerType, " ;
	strField+= " SMT_WorkMode, SMT_ManagerCardNo, SMT_TicketEndDate, " ;

	strField+= " SMT_DealCode1, SMT_CRCData, SMT_DateTime, SMT_ADJUSTCODE  " ;

	strValue.Format(" %s_rowid.nextval,  %d, '%s', '%s', "
					"'%s', '%s', %d,  '%s', "
	                "'%s',  %d, '%s', '%d', "
	                " %d,   '%s', %d, '%d', "
					" %d,  '%s', %d, %d,    "
					" %d,  %d,   '%s',      "
	                "'%s', '%s', SYSDATE ,'%s'   ",
					strTableName.GetBuffer(0), nAuthID, sAuthData, sCommVer,
					sCommStart, sMachineCode, nInvoiceNo, sDealDateTime, 
					sUseCard, nICCardCode, sShowCardNo, nCardID,
					nTimes, sWalletCode, nInMoney, nOutMoney, 
					nBatch, sInductorNo, nDutyFlag, nTimerType, 
					nWorkMode, nManagerCardNo, sTicketEndDate , 
					sDealCode1, sCRCData, strAdjust.GetBuffer(0));

	strSQL.Format("INSERT INTO %s(%s) VALUES(%s)", strTableName.GetBuffer(0), 
		strField.GetBuffer(0), strValue.GetBuffer(0));

	strProcStore.Format("execute PROC_SMART_UPDATEBUZHU('%s', %d, '%05d', '%s', '%d', %d, %d, %d, '%s')", 
		sShowCardNo, nCardID,  nBatch, sDealDateTime, nAuthID, nTimes, nInMoney, nOutMoney, sDealCode1);

	CString strString;

	pDoc->m_nFlow = nInvoiceNo;
	pDoc->m_nCardID = nCardID;
	pDoc->m_nInMoney = nInMoney;
	pDoc->m_nOutMoney = nOutMoney;
	pDoc->m_nDealCount++;

	strString.Format("%d&%d&%d&%s&%d&%.2f&%.2f",
		pDoc->m_nAuthID, pDoc->m_nDealCount, nInvoiceNo, 
		sDealDateTime, nCardID, (float)(nInMoney-nOutMoney)/100, (float)nOutMoney/100);

	BroadcastPro(PACKET_CMD_1002, pDoc, strString.GetBuffer(0), strString.GetLength());
}

//*========================================================================================
//*函数: void TSSRCGSJTable::Clear()
//*功能: 清除数据值
//*参数: 略
//*返回: 无
//*说明: 0224 挂失机 
//*========================================================================================
void TSSRCGSJTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID = 0 ; //Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //传数据的注册号
	ZeroMemory(sCommVer, sizeof(sCommVer));  //通信版本号（十六进制）
	ZeroMemory(sCommStart, sizeof(sCommStart));  //数据通信启动原因（十六进制）
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //机型代码
	nInvoiceNo          = 0 ;	//终端交易流水号
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //卡片结构代码(十六进制)
	nICCardCode          = 0 ;	//IC卡类别代码(预留)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //显示卡号
	nCardID              = 0 ;	//IC卡交易号或显示卡号/序列号

    ZeroMemory(sPassword, sizeof(sPassword));  //个人密码（修改密码为：旧个人密码（6），新个人密码（6）；挂失为：8字节密文,

	ZeroMemory(sDealCode1, sizeof(sDealCode1));  //终端交易代码（十六进制）
	ZeroMemory(sCRCData, sizeof(sCRCData));  //数据体CRC 校验码（十六进制）
	ZeroMemory(sDateTime, sizeof(sDateTime));  //收集日期时间
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));  //校验结果（参见校验结果代码表），Null表示未校验
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //校验日期时间
	ZeroMemory(sOperator, sizeof(sOperator));  //操作员号

	nSendflag             = 0 ;      //发送标志
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}


//*========================================================================================
//*函数: void TSSRCGSJTable::AssignBy(unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 无
//*说明: 0224 挂失机 
//*========================================================================================
void TSSRCGSJTable::AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
	CString strValue = "" ;
	CString strTableName;

	strTableName.Format("SMART_SRC%d", pDoc->m_nAuthID);

	nAuthID = pDoc->m_nAuthID ;
	strcpy(sMachineCode , pDoc->m_szMacCode);

	CTime  t = CTime::GetCurrentTime();
	strText.Format("%04d-%02d-%02d %02d:%02d:%02d  ", 
		t.GetYear(), t.GetMonth(), t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());

	strValue.Format("注册号:%.2X%.2X%.2X%.2X ", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("通信版本:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("启动原因:%.2X ",ucRawData[5]); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("交易流水:%d ",  ucRawData[6]*256+ucRawData[7]); strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	strValue.Format("显示卡号:%.2X%.2X%.2X%.2X%.2X ",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]); strText += strValue ;
	GetValue(strValue, sShowCardNo);

	strValue.Format("个人密码密文:%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X ",	ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16],ucRawData[17],ucRawData[18],ucRawData[19],ucRawData[20]); strText += strValue ;
	GetValue(strValue, sPassword);

	strValue.Format("交易时间:%04d-%02d-%02d %02d ",ucRawData[21]+2000,ucRawData[22],ucRawData[23],ucRawData[24]); strText += strValue ;
	GetValue(strValue, sDealDateTime);

	strValue.Format("交易标记:%.2X ", ucRawData[25]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	strValue.Format("CRC:%.2X%.2X ",   ucRawData[26],ucRawData[27]); strText += strValue ;
	GetValue(strValue, sCRCData);

	CString strAdjust=GetAdjustCode(pszAdjustCode, nInvoiceNo, sDealDateTime, strTableName);

	strText += "\n";

	CString strField;

	strField=  " SMT_RowID, SMT_AuthNo, SMT_AuthData, SMT_CommVer, " ;
	strField+= " SMT_CommStart, SMT_MachineCode, SMT_InvoiceNo, SMT_DealDateTime, " ;
	strField+= " SMT_UseCard, SMT_ICCardCode, SMT_ShowCardNo, SMT_CardID, " ;
	strField+= " SMT_Password," ;

	strField+= " SMT_DealCode1, SMT_CRCData, SMT_DateTime , SMT_ADJUSTCODE " ;

	strValue.Format(" %s_rowid.nextval,  %d, '%s', '%s', "
					"'%s', '%s', %d,  '%s', "
	                "'%s',  %d, '%s', '%d', "
	                "'%s', "
	                "'%s', '%s', SYSDATE,'%s'",
					strTableName.GetBuffer(0), nAuthID, sAuthData, sCommVer,
					sCommStart, sMachineCode, nInvoiceNo, sDealDateTime, 
					sUseCard, nICCardCode, sShowCardNo, nCardID,
					sPassword, 
					sDealCode1, sCRCData, strAdjust.GetBuffer(0));

	strSQL.Format("INSERT INTO %s(%s) VALUES(%s)", strTableName.GetBuffer(0), 
		strField.GetBuffer(0), strValue.GetBuffer(0));

	pDoc->m_nFlow = nInvoiceNo;
	pDoc->m_nCardID = ucRawData[8]*256*256*256+ucRawData[9]*256*256+
					  ucRawData[10]*256+ucRawData[11];
	pDoc->m_nInMoney = 0;
	pDoc->m_nOutMoney = 0;
	pDoc->m_nDealCount++;

	CString strString;
	strString.Format("%d&%d&%d&%s&%s& & ",
		pDoc->m_nAuthID, pDoc->m_nDealCount, nInvoiceNo,
		sDealDateTime, sShowCardNo, 0, 0);

	BroadcastPro(PACKET_CMD_1002, pDoc, strString.GetBuffer(0), strString.GetLength());
}

//*========================================================================================
//*函数: void TSSRCJPJTable::Clear()
//*功能: 清除数据值
//*参数: 略
//*返回: 无
//*说明: 0140 检票机
//*========================================================================================
void TSSRCJPJTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID             = 0 ;	//Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //传数据的注册号
	ZeroMemory(sCommVer, sizeof(sCommVer));  //通信版本号（十六进制）
	ZeroMemory(sCommStart, sizeof(sCommStart));  //数据通信启动原因（十六进制）
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //机型代码
	nInvoiceNo          = 0 ;	//终端交易流水号
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //卡片结构代码(十六进制)
	nICCardCode          = 0 ;	//IC卡类别代码(预留)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //显示卡号
	nCardID              = 0 ;	//IC卡交易号或显示卡号/序列号

	ZeroMemory(sWicketID, sizeof(sWicketID));   //售票点终端ID
	nTicket              = 0;   //票号
	ZeroMemory(sTicketEndDate, sizeof(sTicketEndDate)); //该票截止日期(年月日)

	ZeroMemory(sDealCode1, sizeof(sDealCode1));  //终端交易代码（十六进制）
	ZeroMemory(sCRCData, sizeof(sCRCData));  //数据体CRC 校验码（十六进制）
	ZeroMemory(sDateTime, sizeof(sDateTime));  //收集日期时间
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));  //校验结果（参见校验结果代码表），Null表示未校验
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //校验日期时间
	ZeroMemory(sOperator, sizeof(sOperator));  //操作员号

	nSendflag             = 0 ;      //发送标志
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*函数: void TSSRCJPJTable::AssignBy(unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 无
//*说明: 0140 检票机 
//*========================================================================================
void TSSRCJPJTable::AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
/*	pDoc->m_nFlow = nInvoiceNo;
	pDoc->m_nCardID = nCardID;
	pDoc->m_nInMoney = nInMoney;
	pDoc->m_nOutMoney = nOutMoney;
	pDoc->m_nDealCount++;

	CString strString;
	strString.Format("%d&%d&%d&%s&%d&%d&%d",
		pDoc->m_nAuthID, nInvoiceNo, pDoc->m_nDealCount, 
		sDealDateTime, nCardID, nInMoney, nOutMoney);

	BroadcastPro(PACKET_CMD_1002, pDoc, strString.GetBuffer(0), strString.GetLength());
*/
}

//*========================================================================================
//*函数: void TSSRCJSBTable::Clear()
//*功能: 清除数据值
//*参数: 略
//*返回: 无
//*说明: 0121 计时宝,5501 扇型通道机
//*========================================================================================
void TSSRCJSBTable::Clear()
{
	strProcStore = "" ;

	nAuthID             = 0 ;	//Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //传数据的注册号
	ZeroMemory(sCommVer, sizeof(sCommVer));  //通信版本号（十六进制）
	ZeroMemory(sCommStart, sizeof(sCommStart));  //数据通信启动原因（十六进制）
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //机型代码
	nInvoiceNo          = 0 ;	//终端交易流水号
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//交易日期时间(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //卡片结构代码(十六进制)
	nICCardCode          = 0 ;	//IC卡类别代码(预留)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //显示卡号
	nCardID              = 0 ;	//IC卡交易号或显示卡号/序列号

	nInductorNo          = 0;    //感应头编号,工作模式5时,保存借出还入钥匙的设备(0~15)
	nDutyFlag            = 0;    //上/下班标记 1上班/0班
	nTimerType           = 0;    //考勤类型,工作模式5时,保存房间号
	nWorkMode            = 0;    //工作模式(1~4)
	nManagerCardNo       = 0;    //管理员卡号(4byte)

	ZeroMemory(sDealCode1, sizeof(sDealCode1));  //终端交易代码（十六进制）
	ZeroMemory(sCRCData, sizeof(sCRCData));  //数据体CRC 校验码（十六进制）
	ZeroMemory(sDateTime, sizeof(sDateTime));  //收集日期时间
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));  //校验结果（参见校验结果代码表），Null表示未校验
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //校验日期时间
	ZeroMemory(sOperator, sizeof(sOperator));  //操作员号

	nSendflag             = 0 ;      //发送标志
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*函数: void TSSRCJSBTable::AssignBy(unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 无
//*说明: 0121 计时宝,5501 扇型通道机
//*========================================================================================
void TSSRCJSBTable::AssignBy(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
	CString strValue, strField, strTableName;
	strTableName.Format("SMART_SRC%d", pDoc->m_nAuthID);

	nAuthID = pDoc->m_nAuthID ;
	strcpy(sMachineCode , pDoc->m_szMacCode);

	CTime  t = CTime::GetCurrentTime();
	strText.Format("%04d-%02d-%02d %02d:%02d:%02d  ", 
		t.GetYear(), t.GetMonth(), t.GetDay(),
		t.GetHour(), t.GetMinute(), t.GetSecond());

	strValue.Format("注册号:%.2X%.2X%.2X%.2X ",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("通信版本:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("启动原因:%.2X ",ucRawData[5]); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("交易流水号:%.5d ",ucRawData[6]*256+ucRawData[7]);	 strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	strValue.Format("卡型代码:%d ",ucRawData[22]);
	GetValue(strValue, nICCardCode);

	strValue.Format("工作模式代码:%d ",ucRawData[20]);
	GetValue(strValue, nWorkMode);

#if 0
	for(int kk=0; kk<100; kk++)
		printf("%02X ", ucRawData[kk]);
	printf("\n");
#endif 

	if( nICCardCode == 0 )
	{
		strValue.Format("卡号:%ld ",ucRawData[9]*256*256*256+ucRawData[10]*256*256+ucRawData[11]*256+ucRawData[12]);	 strText += strValue ;
		GetValue(strValue, nCardID);
	}
	else if( nICCardCode == 100 )
	{
		if( nWorkMode == 4 )
			strValue.Format("卡号:%ld ", 0);
		else
			strValue.Format("卡号:%ld ",ucRawData[10]*256*256+ucRawData[11]*256+ucRawData[12]);	 strText += strValue ;

		GetValue(strValue, nCardID);
	}
	else if( nICCardCode == 101 )
	{
		strValue.Format("卡号:%ld ",ucRawData[11]*256+ucRawData[12]);	 strText += strValue ;
		GetValue(strValue, nCardID);
	}
	else
	{
		strValue.Format("卡号:%ld ",0);	 strText += strValue ;
		GetValue(strValue, nCardID);
	}

	if( nWorkMode == 4 && (nICCardCode == 100 || nICCardCode == 101 ) )
	{
		strValue.Format("显示卡号:%.2X%.2X%.2X%.2X%.2X ",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]); strText += strValue ;
		GetValue(strValue, sShowCardNo);
	}

	strValue.Format("交易时间:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[13]+2000,ucRawData[14],ucRawData[15],ucRawData[16],ucRawData[17],ucRawData[18]); strText += strValue ;
	GetValue(strValue, sDealDateTime);

	strValue.Format("工作模式代码:%d ",ucRawData[20]); strText += strValue ;
	GetValue(strValue, nWorkMode);

	strValue.Format("考勤类型:%d ",ucRawData[21]); strText += strValue ;
	GetValue(strValue, nTimerType);

	strValue.Format("卡型代码:%d ",ucRawData[22]); strText += strValue ;
	GetValue(strValue, nICCardCode);

	strValue.Format("感应头编号:%d ",ucRawData[23]); strText += strValue ;
	GetValue(strValue, nInductorNo);

	strValue.Format("上下班标记:%d ",ucRawData[24]); strText += strValue ;
	GetValue(strValue, nDutyFlag);
	if( nDutyFlag > 9 )
		nDutyFlag = 0 ;

	strValue.Format("交易标记:%.2X ",ucRawData[25]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	if(ucRawData[25] == 0x00)
		strValue = "黑卡交易 ";
	else if(ucRawData[25] == 0x01)
		strValue = "非法卡 ";
	else if(ucRawData[25] == 0x02)
		strValue = "中途拔卡 ";
	else if(ucRawData[25] == 0x03)
		strValue = "钱包格式错 ";
	else if(ucRawData[25] == 0x05)
		strValue = "无法写卡 ";
	else if(ucRawData[25] == 0x10)
		strValue = "密码错误 ";
	else if(ucRawData[25] == 0xA0)
		strValue = "不在时间段内打卡 ";
	else if(ucRawData[25] == 0xA1)
		strValue = "次数超出 ";
	else if(ucRawData[25] == 0xA2)
		strValue = "时间间隔不够 ";
	else if(ucRawData[25] == 0xFA)
		strValue = "充值交易 ";
	else if(ucRawData[25] == 0xFE)
		strValue = "冲正交易 ";
	else if(ucRawData[25] == 0x99)
		strValue = "正确交易 ";
	else 
		strValue = "未知交易 ";

	strValue.Format("CRC:%.2X%.2X ",ucRawData[26],ucRawData[27]); strText += strValue ;
	GetValue(strValue, sCRCData);

	CString strAdjust=GetAdjustCode(pszAdjustCode, nInvoiceNo, sDealDateTime, strTableName);

	strText += "\n";

	strField=  " SMT_RowID, SMT_AuthNo, SMT_AuthData, SMT_CommVer, " ;
	strField+= " SMT_CommStart, SMT_MachineCode, SMT_InvoiceNo, SMT_DealDateTime, " ;
	strField+= " SMT_UseCard, SMT_ICCardCode, SMT_ShowCardNo, SMT_CardID, " ;
	strField+= " SMT_InductorNo, SMT_DutyFlag, SMT_TimerType, SMT_WorkMode, " ;
	strField+= " SMT_ManagerCardNo, " ;

	strField+= " SMT_DealCode1, SMT_CRCData, SMT_DateTime, SMT_ADJUSTCODE  " ;

	strValue.Format(" %s_rowid.nextval,  %d, '%s', '%s', "
					"'%s', '%s', %d,  '%s', "
	                "'%s',  %d, '%s', %d, "
	                " %d,   %d, %d,  %d, "
	                " %d, " 
	                "'%s', '%s', SYSDATE,'%s' ",
					strTableName.GetBuffer(0), nAuthID, sAuthData, sCommVer,
					sCommStart, sMachineCode, nInvoiceNo, sDealDateTime, 
					sUseCard, nICCardCode, sShowCardNo, nCardID,
					nInductorNo, nDutyFlag, nTimerType, nWorkMode, 
					nManagerCardNo, 
					sDealCode1, sCRCData, strAdjust.GetBuffer(0));
	strSQL.Format("INSERT INTO %s(%s) VALUES(%s)", strTableName.GetBuffer(0), 
		strField.GetBuffer(0), strValue.GetBuffer(0));

	CString strString;

	pDoc->m_nFlow = nInvoiceNo;
	pDoc->m_nCardID = nCardID;
	pDoc->m_nInMoney = 0;
	pDoc->m_nOutMoney = 0;
	pDoc->m_nDealCount++;

	strString.Format("%d&%d&%d&%s&%d& & ",
		pDoc->m_nAuthID, pDoc->m_nDealCount, nInvoiceNo, 
		sDealDateTime, nCardID);
	BroadcastPro(PACKET_CMD_1002, pDoc, strString.GetBuffer(0), strString.GetLength());
}

//*========================================================================================
//*函数: void CSmartSRCTable::EnableSaveFile(bool bBool)
//*功能: 设置为是否保存为文件
//*参数: 略
//*返回: 无
//*说明: 虚基类程序
//*========================================================================================
void CSmartSRCTable::EnableSaveFile(bool bBool)
{
	m_bSaveFile = bBool ;
}

//*========================================================================================
//*函数: void CSmartSRCTable::EnableSaveDB(bool bBool)
//*功能: 设置为是否保存为数据库
//*参数: 略
//*返回: 无
//*说明: 虚基类程序
//*========================================================================================
void CSmartSRCTable::EnableSaveDB(bool bBool)
{
	m_bSaveDB = bBool ;
}

//*========================================================================================
//*函数: bool CSmartSRCTable::Convert(TSSmartDoc *pDoc, unsigned char *ucRawData)
//*功能: 转换结构
//*参数: 略
//*返回: 是否成功
//*说明: 虚基类程序
//*========================================================================================
bool CSmartSRCTable::Convert(TSSmartDoc *pDoc, unsigned char *ucRawData, char *pszAdjustCode)
{
	ASSERT(pDoc);

	m_nType = COperator::GetMachineType(pDoc);

	if( m_nType != MACHINE_TYPE_UNKNOW )
	{
		m_pDoc = pDoc ;
		long nMoney = ConvertDoc(ucRawData, pszAdjustCode);

		m_nDealMoney = nMoney;

		if( !strcmp(pszAdjustCode, "") )
		{
			m_pDoc->m_nDealNumber++;
			m_pDoc->m_nTransMoney += nMoney;

			m_pDoc->m_nCheckSuccess++;
			m_pDoc->m_nCheckSuccessMoney += nMoney;
		} 
		else if( !strcmp(pszAdjustCode, "0102") )
		{
			m_pDoc->m_nDealNumber++;
			m_pDoc->m_nTransMoney += nMoney;

			m_pDoc->m_nCheckFaild++;
			m_pDoc->m_nCheckFaildMoney += nMoney;
		}
		return true;
	}
	else
	{
		m_nDealMoney = 0;
		return false;
	}
}

//*========================================================================================
//*函数: bool CSmartSRCSFTable::Write()
//*功能: 保存到文件与数据库
//*参数: 略
//*返回: 无
//*说明: 虚基类程序
//*========================================================================================
bool CSmartSRCTable::Write(bool bUpdate)
{
	CString strString = "" ;

	bool bResult1 = false ;
	bool bResult2 = false ;

	m_bUpdate = bUpdate ;

	if( IsSaveDB() )
	{
		bResult1 = SaveToDB(GetStringSQL());
		if( bUpdate )
		{
			if( bResult1 )
			{
				m_pDoc->m_nInSuccess++;
				m_pDoc->m_nInSuccessMoney+=m_nDealMoney;
			}
			else
			{
				m_pDoc->m_nInFaild++;
				m_pDoc->m_nInFaildMoney+=m_nDealMoney;
			}
		}
	}

	strString = "" ; 

	if( IsSaveFile() )
	{
		bResult2 = SaveToFile(GetStringText());
	}

	return bResult1&&bResult2;
}

//*========================================================================================
//*函数: bool CSmartSRCTable::SvaeToDB(CString strSQL)
//*功能: 保存到数据库
//*参数: 略
//*返回: 成功与否
//*说明: 虚基类程序
//*========================================================================================
bool CSmartSRCTable::SaveToDB(CString strSQL)
{
	DWORD dwTick = GetTickCount();

	if( strSQL == "" )
	{
//		printf("The SQL is Empty!.MacType:%d............... ", m_nType);
		return false;
	}

	long nDatabase = GetDBHandle(DATABASE_NORMAL);
	if( nDatabase <= 0 )
	{
		ReportLog(RET_DBBUSY, "实时收集数据", "保存到数据库时, 不能得到数据库句柄!");
		return false;
	}

	long nRec = ExecuteSQL(nDatabase, strSQL.GetBuffer(0));
	if( nRec != RET_OK )
	{
		CString strDDL;

		strDDL.Format("execute proc_smart_AuthnoSourcenew('%s', 'SMART_SRC%d')", m_pDoc->m_szMacCode, m_pDoc->m_nAuthID);
		nRec = ExecuteSQL(nDatabase, strDDL.GetBuffer(0));
		if( nRec != RET_OK )
		{
			ReportLog(nRec, "创建原始凭证表", "数据库不能创建原始凭证表!");
			FreeDBHandle(nDatabase);
			return false;
		}

		sprintf(m_pDoc->m_szTableName, "SMART_SRC%d", m_pDoc->m_nAuthID);

		if( ExecuteSQL(nDatabase, strSQL.GetBuffer(0)) != RET_OK )
		{
			ReportLog(nRec, "写原始凭证表", strSQL.GetBuffer(0));
			FreeDBHandle(nDatabase);
			return false;
		}
	}

	CString strProcStore = GetStringProc();
	if( strProcStore != "" )
	{
		ExecuteSQL(nDatabase, strProcStore.GetBuffer(0));
	}

//	ExecuteSQL(nDatabase, strSQL.GetBuffer(0));

	if( m_bUpdate )
	{
		CString strUpdate;
		strUpdate = GetStringUpdate();

		if( ExecuteSQL(nDatabase, strUpdate.GetBuffer(0)) != RET_OK )
		{
//			printf("\n%s\n", strSQL.GetBuffer(0));
			FreeDBHandle(nDatabase);
			return false;
		}
	}

	FreeDBHandle(nDatabase);

	InterlockedIncrement((LONG*)&gTryWriteDB);
	InterlockedExchangeAdd((LONG*)&gWriteDB, (LONG)(GetTickCount() - dwTick));

	return true;
}

//*========================================================================================
//*函数: bool CSmartSRCTable::SvaeToFile(CString strText)
//*功能: 保存到文件
//*参数: 略
//*返回: 成功与否
//*说明: 虚基类程序
//*========================================================================================
bool CSmartSRCTable::SaveToFile(CString strText)
{
	return true;	

}


//*========================================================================================
//*函数: CSmartSRCTable* CSmartSRCTable::Alloc(TSSmartDoc *pDoc)
//*功能: 分配一个实时数据表
//*参数: 略
//*返回: 成功与否
//*说明: 虚基类程序
//*========================================================================================
CSmartSRCTable* CSmartSRCTable::Alloc(TSSmartDoc *pDoc)
{
	CSmartSRCTable *pTable = NULL ;

	switch(COperator::GetMachineType(pDoc))
	{
	case MACHINE_TYPE_5301:     //服务器
	case MACHINE_TYPE_1056:     //手持机(计费+补助)
		pTable = new CSmartSRCBZTable;
		break;
	case MACHINE_TYPE_0201:     //增值机
	case MACHINE_TYPE_0226:     //收费机
	case MACHINE_TYPE_0228:     //车载机
	case MACHINE_TYPE_0230:     //管理机
	case MACHINE_TYPE_0232:     //上机上网机
	case MACHINE_TYPE_0234:     //淋浴管理机
	case MACHINE_TYPE_0236:     //0236 独立式淋浴计费器
	case MACHINE_TYPE_0240:     //售票机
	case MACHINE_TYPE_0130:     //身份识别机
	case MACHINE_TYPE_1055:
	case MACHINE_TYPE_0248://上海理工转帐机
		pTable = new CSmartSRCSFTable;
		break;
	case MACHINE_TYPE_0140:     //检票机
		pTable = new CSmartSRCJPJTable;
		break;
	case MACHINE_TYPE_0121:     //计时宝
	case MACHINE_TYPE_5501:     //扇型通道机
		pTable = new CSmartSRCJSBTable;
		break;
	case MACHINE_TYPE_0224:     //挂失机
		pTable = new CSmartSRCGSJTable;
		break;
	default:
		break;
	}

	return pTable;
}

//*========================================================================================
//*函数: void CSmartSRCTable::Release(CSmartSRCTable *pTable)
//*功能: 释放一个实时数据表
//*参数: 略
//*返回: 成功与否
//*说明: 虚基类程序
//*========================================================================================
void CSmartSRCTable::Release(CSmartSRCTable *pTable)
{
	switch(pTable->m_nType)
	{
	case MACHINE_TYPE_5301:     //服务器
	case MACHINE_TYPE_1056:     //手持机(计费+补助)
		delete (CSmartSRCBZTable*)pTable;
		break;
	case MACHINE_TYPE_0201:     //增值机
	case MACHINE_TYPE_0226:     //收费机
	case MACHINE_TYPE_0228:     //车载机
	case MACHINE_TYPE_0230:     //管理机
	case MACHINE_TYPE_0232:     //上机上网机
	case MACHINE_TYPE_0234:     //淋浴管理机
	case MACHINE_TYPE_0236:     //0236 独立式淋浴计费器
	case MACHINE_TYPE_0240:     //售票机
	case MACHINE_TYPE_0130:     //身份识别机
	case MACHINE_TYPE_1055:
	case MACHINE_TYPE_0248://上海理工转帐机
		delete (CSmartSRCSFTable*)pTable;
		break;
	case MACHINE_TYPE_0140:     //检票机
		delete (CSmartSRCJPJTable*)pTable;
		break;
	case MACHINE_TYPE_0121:     //计时宝
	case MACHINE_TYPE_5501:     //扇型通道机
		delete (CSmartSRCJSBTable*)pTable;
		break;
	case MACHINE_TYPE_0224:     //挂失机
		delete (CSmartSRCGSJTable*)pTable;
		break;
	default:
		delete pTable;
		break;
	}
}

