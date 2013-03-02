
#include "stdafx.h"
#include "SRCTable.h"

//*========================================================================================
//*����: void TSSRCSFTable::Clear()
//*����: �������ֵ
//*����: ��
//*����: ��
//*˵��: 0226 �շѻ�,0228 ���ػ�,0201 ��ֵ��,0232 �ϻ�������
//*      0230 �����,0234 �����(��ԡר��),0236 ����ʽ��ԡ�Ʒ���,0240 ��Ʊ��,
//*      0130 ���ʶ���,1055 �ֳֻ����Ʒѣ�
//*========================================================================================
void TSSRCSFTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID             = 0 ;				   //Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //�����ݵ�ע���
	ZeroMemory(sCommVer, sizeof(sCommVer));    //ͨ�Ű汾�ţ�ʮ�����ƣ�
	ZeroMemory(sCommStart, sizeof(sCommStart));//����ͨ������ԭ��ʮ�����ƣ�
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //���ʹ���
	nInvoiceNo          = 0 ;						 //�ն˽�����ˮ��
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));			 //��Ƭ�ṹ����(ʮ������)
	nICCardCode          = 0 ;						 //IC��������(Ԥ��)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));	 //��ʾ����
	nCardID              = 0 ;						 //IC�����׺Ż���ʾ����/���к�
	nTimes               = 0 ;					     //����
	ZeroMemory(sWalletcode, sizeof(sWalletcode));    //Ǯ��
	nInMoney             = 0 ;						 //�뿨���
	nOutMoney            = 0 ;						 //�������

	ZeroMemory(sDealCode1, sizeof(sDealCode1));   //�ն˽��״��루ʮ�����ƣ�
	ZeroMemory(sCRCData, sizeof(sCRCData));       //������CRC У���루ʮ�����ƣ�
	ZeroMemory(sDateTime, sizeof(sDateTime));     //�ռ�����ʱ��
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode)); //У�������μ�У�����������Null��ʾδУ��
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //У������ʱ��
	ZeroMemory(sOperator, sizeof(sOperator));  //����Ա��

	nSendflag             = 0 ;      //���ͱ�־
	nCheckStep            = 0 ;      //
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*����: void TSSRCSFTable::AssignBy(unsigned char *ucRawData)
//*����: ת���ṹ
//*����: ��
//*����: ��
//*˵��: 0226 �շѻ�,0228 ���ػ�,0201 ��ֵ��,0232 �ϻ�������
//*      0230 �����,0234 �����(��ԡר��),0236 ����ʽ��ԡ�Ʒ���,0240 ��Ʊ��,
//*      0130 ���ʶ���,1055 �ֳֻ����Ʒѣ�
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

	strValue.Format("ע���:%.2X%.2X%.2X%.2X ", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("ͨ�Ű汾:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("Ǯ����:%d ",ucRawData[5]>>4); strText += strValue ;
	GetValue(strValue, sWalletcode);

	strValue.Format("����ԭ��:%.2X ",ucRawData[5]&0x0F); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("���׿���:%d ",ucRawData[8]*65536+ucRawData[9]*256+ucRawData[10]); strText += strValue ;
	GetValue(strValue, nCardID);

	strValue.Format("������ˮ��:%.5d ",ucRawData[6]*256+ucRawData[7]); strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	if( ucRawData[12] >= 100 || ucRawData[13] >= 100 || 
		ucRawData[14] >= 100 || ucRawData[15] >= 100  || ucRawData[16] >= 100 )
	{
		strValue.Format("����ʱ��:%04d-%02d-%02d %02d:%02d:%02d ", 2000, 1, 1, 1,1,1);
	    strText += strValue ;
	}
	else
	{
		strValue.Format("����ʱ��:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[11]+2000,ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16]); strText += strValue ;
	}

	GetValue(strValue, sDealDateTime);

	strValue.Format("��Ƭ�ۼ�ʹ�ô���:%d ",ucRawData[17]*256+ucRawData[18]); strText += strValue ;
	GetValue(strValue, nTimes);

	strValue.Format("�뿨���(��):%d ",ucRawData[19]+ucRawData[20]*256+ucRawData[21]*65536); strText += strValue ;
	GetValue(strValue, nInMoney);

	strValue.Format("�������(��):%d ",ucRawData[22]+ucRawData[23]*256+ucRawData[24]*65536); strText += strValue ;
	GetValue(strValue, nOutMoney);

	strValue.Format("���ױ��:%.2X ",ucRawData[25]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	if(ucRawData[25] == 0x00)
		strValue = "�ڿ����� "; 
	else if(ucRawData[25] == 0x02)
		strValue = "��;�ο� ";
	else if(ucRawData[25] == 0x03)
		strValue = "Ǯ����ʽ�� ";
	else if(ucRawData[25] == 0x05)
		strValue = "�޷�д�� ";
	else if(ucRawData[25] == 0x10)
		strValue = "������� ";
	else if(ucRawData[25] == 0xFA)
		strValue = "��ֵ���� ";
	else if(ucRawData[25] == 0xFE)
		strValue = "�������� ";
	else if(ucRawData[25] == 0x99)
		strValue = "��ȷ���� ";
	else 
		strValue = "δ֪���ͽ��� ";

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
//*����: void TSSRCBZTable::Clear()
//*����: �������ֵ
//*����: ��
//*����: ��
//*˵��: 5301 ���ݷ�����(������¼), 1056 �ֳֻ�(�Ʒ�+����)
//*========================================================================================
void TSSRCBZTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID             = 0 ;	//Auth ID

	ZeroMemory(sAuthData, sizeof(sAuthData));  //�����ݵ�ע���
	ZeroMemory(sCommVer, sizeof(sCommVer));  //ͨ�Ű汾�ţ�ʮ�����ƣ�
	ZeroMemory(sCommStart, sizeof(sCommStart));  //����ͨ������ԭ��ʮ�����ƣ�
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //���ʹ���
	nInvoiceNo          = 0 ;	//�ն˽�����ˮ��
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //��Ƭ�ṹ����(ʮ������)
	nICCardCode          = 0 ;	//IC��������(Ԥ��)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //��ʾ����
	nCardID              = 0 ;	//IC�����׺Ż���ʾ����/���к�

	nTimes               = 0;   //IC��ʹ�ô���������Ǯ������Ϊ�գ�
	ZeroMemory(sWalletCode, sizeof(sWalletCode));  //����Ǯ�����룬��ӦǮ����ʶ�����
	nInMoney             = 0;   //�뿨ֵ���Է�Ϊ��λ
	nOutMoney            = 0;   //����ֵ���Է�Ϊ��λ
	nBatch               = 0;   //���κ�

	ZeroMemory(sInductorNo, sizeof(sInductorNo));  //��ӦͷID���,����ģʽ5ʱ,����������Կ�׵��豸(0~15)
	nDutyFlag            = 0;   //��/�°��� 1�ϰ�/0��
	nTimerType           = 0;   //��������,����ģʽ5ʱ,���淿���
	nWorkMode            = 0;   //����ģʽ(1~4)
	nManagerCardNo       = 0;   //����Ա����(4byte)
	ZeroMemory(sTicketEndDate, sizeof(sTicketEndDate));  //��Ʊ��ֹ����(������)

	ZeroMemory(sDealCode1, sizeof(sDealCode1));       //�ն˽��״��루ʮ�����ƣ�
	ZeroMemory(sCRCData, sizeof(sCRCData));       //������CRC У���루ʮ�����ƣ�
	ZeroMemory(sDateTime, sizeof(sDateTime));       //�ռ�����ʱ��
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));       //У�������μ�У�����������Null��ʾδУ��
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //У������ʱ��
	ZeroMemory(sOperator, sizeof(sOperator));  //����Ա��

	nSendflag             = 0 ;      //���ͱ�־
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*����: void TSSRCBZTable::AssignBy(unsigned char *ucRawData)
//*����: ת���ṹ
//*����: ��
//*����: ��
//*˵��: 5301 ���ݷ�����(������¼), 1056 �ֳֻ�(�Ʒ�+����)
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

	strValue.Format("ע���:%.2X%.2X%.2X%.2X ",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("ͨ�Ű汾:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("����ԭ��:%.2X ",ucRawData[5]); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("���ʹ���:%.2X%.2X ",ucRawData[6],ucRawData[7]);  strText += strValue ;
	GetValue(strValue, sMachineCode);

	strValue.Format("������ˮ��:%.5d ",ucRawData[8]*256+ucRawData[9]); strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	strValue.Format("����ʱ��:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[10]+2000,ucRawData[11],ucRawData[12],ucRawData[13],ucRawData[14],ucRawData[15]); strText += strValue ;
	GetValue(strValue, sDealDateTime);

	strValue.Format("���ʹ���:%.2X ",ucRawData[16]); strText += strValue ;
	GetValue(strValue, sUseCard);

	strValue.Format("����:%d ",ucRawData[17]);  strText += strValue ;
	GetValue(strValue, nICCardCode);

	strValue.Format("��ʾ����:%.2X%.2X%.2X%.2X%.2X ",ucRawData[18],ucRawData[19],ucRawData[20],ucRawData[21],ucRawData[22]);  strText += strValue ;
	GetValue(strValue, sShowCardNo);

	strValue.Format("���׿���:%d ",ucRawData[23]*256*256+ucRawData[24]*256+ucRawData[25]); strText += strValue ;
	GetValue(strValue, nCardID);

	strValue.Format("��Ƭʹ����ˮ:%d ",ucRawData[26]*256+ucRawData[27]); strText += strValue ;
	GetValue(strValue, nTimes);

	strValue.Format("Ǯ�����Դ���:%d ",ucRawData[28] & 0x0F); strText += strValue ;
	GetValue(strValue, sWalletCode);

	int flag = ucRawData[28] & 0xF0;

	strValue.Format("�������:%d ",ucRawData[29]+ucRawData[30]*256);  strText += strValue ;
	GetValue(strValue, nInMoney);

	strValue.Format("Ǯ�����:%d ",ucRawData[31]+ucRawData[32]*256+ucRawData[33]*65536); strText += strValue ;
	GetValue(strValue, nOutMoney);

	if( !flag )
	{
		nInMoney = nInMoney + nOutMoney;
	}
	else
	{
		nInMoney = nOutMoney - nInMoney;
	}

	strValue.Format("�������κ�:%d ",ucRawData[34]*256+ucRawData[35]); strText += strValue ;
	GetValue(strValue, nBatch);

	strValue.Format("���ױ��:%.2X ",ucRawData[36]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	if(ucRawData[25] == 0x00)
		strValue = "�ڿ����� ";
	else if(ucRawData[25] == 0x02)
		strValue = "��;�ο� ";
	else if(ucRawData[25] == 0x03)
		strValue = "Ǯ����ʽ�� ";
	else if(ucRawData[25] == 0x05)
		strValue = "�޷�д�� ";
	else if(ucRawData[25] == 0x10)
		strValue = "������� ";
	else if(ucRawData[25] == 0xFA)
		strValue = "��ֵ���� ";
	else if(ucRawData[25] == 0xFE)
		strValue = "�������� ";
	else if(ucRawData[25] == 0x99)
		strValue = "��ȷ���� ";
	else 
		strValue = "δ֪���� ";

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
//*����: void TSSRCGSJTable::Clear()
//*����: �������ֵ
//*����: ��
//*����: ��
//*˵��: 0224 ��ʧ�� 
//*========================================================================================
void TSSRCGSJTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID = 0 ; //Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //�����ݵ�ע���
	ZeroMemory(sCommVer, sizeof(sCommVer));  //ͨ�Ű汾�ţ�ʮ�����ƣ�
	ZeroMemory(sCommStart, sizeof(sCommStart));  //����ͨ������ԭ��ʮ�����ƣ�
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //���ʹ���
	nInvoiceNo          = 0 ;	//�ն˽�����ˮ��
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //��Ƭ�ṹ����(ʮ������)
	nICCardCode          = 0 ;	//IC��������(Ԥ��)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //��ʾ����
	nCardID              = 0 ;	//IC�����׺Ż���ʾ����/���к�

    ZeroMemory(sPassword, sizeof(sPassword));  //�������루�޸�����Ϊ���ɸ������루6�����¸������루6������ʧΪ��8�ֽ�����,

	ZeroMemory(sDealCode1, sizeof(sDealCode1));  //�ն˽��״��루ʮ�����ƣ�
	ZeroMemory(sCRCData, sizeof(sCRCData));  //������CRC У���루ʮ�����ƣ�
	ZeroMemory(sDateTime, sizeof(sDateTime));  //�ռ�����ʱ��
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));  //У�������μ�У�����������Null��ʾδУ��
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //У������ʱ��
	ZeroMemory(sOperator, sizeof(sOperator));  //����Ա��

	nSendflag             = 0 ;      //���ͱ�־
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}


//*========================================================================================
//*����: void TSSRCGSJTable::AssignBy(unsigned char *ucRawData)
//*����: ת���ṹ
//*����: ��
//*����: ��
//*˵��: 0224 ��ʧ�� 
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

	strValue.Format("ע���:%.2X%.2X%.2X%.2X ", ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("ͨ�Ű汾:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("����ԭ��:%.2X ",ucRawData[5]); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("������ˮ:%d ",  ucRawData[6]*256+ucRawData[7]); strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	strValue.Format("��ʾ����:%.2X%.2X%.2X%.2X%.2X ",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]); strText += strValue ;
	GetValue(strValue, sShowCardNo);

	strValue.Format("������������:%.2X%.2X%.2X%.2X%.2X%.2X%.2X%.2X ",	ucRawData[13],ucRawData[14],ucRawData[15],ucRawData[16],ucRawData[17],ucRawData[18],ucRawData[19],ucRawData[20]); strText += strValue ;
	GetValue(strValue, sPassword);

	strValue.Format("����ʱ��:%04d-%02d-%02d %02d ",ucRawData[21]+2000,ucRawData[22],ucRawData[23],ucRawData[24]); strText += strValue ;
	GetValue(strValue, sDealDateTime);

	strValue.Format("���ױ��:%.2X ", ucRawData[25]); strText += strValue ;
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
//*����: void TSSRCJPJTable::Clear()
//*����: �������ֵ
//*����: ��
//*����: ��
//*˵��: 0140 ��Ʊ��
//*========================================================================================
void TSSRCJPJTable::Clear()
{
	strText = "" ;
	strSQL  = "" ;
	strProcStore = "" ;

	nAuthID             = 0 ;	//Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //�����ݵ�ע���
	ZeroMemory(sCommVer, sizeof(sCommVer));  //ͨ�Ű汾�ţ�ʮ�����ƣ�
	ZeroMemory(sCommStart, sizeof(sCommStart));  //����ͨ������ԭ��ʮ�����ƣ�
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //���ʹ���
	nInvoiceNo          = 0 ;	//�ն˽�����ˮ��
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //��Ƭ�ṹ����(ʮ������)
	nICCardCode          = 0 ;	//IC��������(Ԥ��)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //��ʾ����
	nCardID              = 0 ;	//IC�����׺Ż���ʾ����/���к�

	ZeroMemory(sWicketID, sizeof(sWicketID));   //��Ʊ���ն�ID
	nTicket              = 0;   //Ʊ��
	ZeroMemory(sTicketEndDate, sizeof(sTicketEndDate)); //��Ʊ��ֹ����(������)

	ZeroMemory(sDealCode1, sizeof(sDealCode1));  //�ն˽��״��루ʮ�����ƣ�
	ZeroMemory(sCRCData, sizeof(sCRCData));  //������CRC У���루ʮ�����ƣ�
	ZeroMemory(sDateTime, sizeof(sDateTime));  //�ռ�����ʱ��
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));  //У�������μ�У�����������Null��ʾδУ��
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //У������ʱ��
	ZeroMemory(sOperator, sizeof(sOperator));  //����Ա��

	nSendflag             = 0 ;      //���ͱ�־
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*����: void TSSRCJPJTable::AssignBy(unsigned char *ucRawData)
//*����: ת���ṹ
//*����: ��
//*����: ��
//*˵��: 0140 ��Ʊ�� 
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
//*����: void TSSRCJSBTable::Clear()
//*����: �������ֵ
//*����: ��
//*����: ��
//*˵��: 0121 ��ʱ��,5501 ����ͨ����
//*========================================================================================
void TSSRCJSBTable::Clear()
{
	strProcStore = "" ;

	nAuthID             = 0 ;	//Auth ID
	ZeroMemory(sAuthData, sizeof(sAuthData));  //�����ݵ�ע���
	ZeroMemory(sCommVer, sizeof(sCommVer));  //ͨ�Ű汾�ţ�ʮ�����ƣ�
	ZeroMemory(sCommStart, sizeof(sCommStart));  //����ͨ������ԭ��ʮ�����ƣ�
	ZeroMemory(sMachineCode, sizeof(sMachineCode));  //���ʹ���
	nInvoiceNo          = 0 ;	//�ն˽�����ˮ��
	ZeroMemory(sDealDateTime, sizeof(sDealDateTime));	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	ZeroMemory(sUseCard, sizeof(sUseCard));  //��Ƭ�ṹ����(ʮ������)
	nICCardCode          = 0 ;	//IC��������(Ԥ��)
	ZeroMemory(sShowCardNo, sizeof(sShowCardNo));  //��ʾ����
	nCardID              = 0 ;	//IC�����׺Ż���ʾ����/���к�

	nInductorNo          = 0;    //��Ӧͷ���,����ģʽ5ʱ,����������Կ�׵��豸(0~15)
	nDutyFlag            = 0;    //��/�°��� 1�ϰ�/0��
	nTimerType           = 0;    //��������,����ģʽ5ʱ,���淿���
	nWorkMode            = 0;    //����ģʽ(1~4)
	nManagerCardNo       = 0;    //����Ա����(4byte)

	ZeroMemory(sDealCode1, sizeof(sDealCode1));  //�ն˽��״��루ʮ�����ƣ�
	ZeroMemory(sCRCData, sizeof(sCRCData));  //������CRC У���루ʮ�����ƣ�
	ZeroMemory(sDateTime, sizeof(sDateTime));  //�ռ�����ʱ��
	ZeroMemory(sAdjustCode, sizeof(sAdjustCode));  //У�������μ�У�����������Null��ʾδУ��
	ZeroMemory(sDealWithDateTime, sizeof(sDealWithDateTime));  //У������ʱ��
	ZeroMemory(sOperator, sizeof(sOperator));  //����Ա��

	nSendflag             = 0 ;      //���ͱ�־
	nCheckStep            = 0 ;      
	ZeroMemory(sCheckResult, sizeof(sCheckResult));
	ZeroMemory(sCheckDate, sizeof(sCheckDate));
	ZeroMemory(sCheckKeepingdate, sizeof(sCheckKeepingdate));
	nRepeatNo             = 0 ;
}

//*========================================================================================
//*����: void TSSRCJSBTable::AssignBy(unsigned char *ucRawData)
//*����: ת���ṹ
//*����: ��
//*����: ��
//*˵��: 0121 ��ʱ��,5501 ����ͨ����
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

	strValue.Format("ע���:%.2X%.2X%.2X%.2X ",ucRawData[0],ucRawData[1],ucRawData[2],ucRawData[3]); strText += strValue ;
	GetValue(strValue, sAuthData);

	strValue.Format("ͨ�Ű汾:%.2X ",ucRawData[4]); strText += strValue ;
	GetValue(strValue, sCommVer);

	strValue.Format("����ԭ��:%.2X ",ucRawData[5]); strText += strValue ;
	GetValue(strValue, sCommStart);

	strValue.Format("������ˮ��:%.5d ",ucRawData[6]*256+ucRawData[7]);	 strText += strValue ;
	GetValue(strValue, nInvoiceNo);

	strValue.Format("���ʹ���:%d ",ucRawData[22]);
	GetValue(strValue, nICCardCode);

	strValue.Format("����ģʽ����:%d ",ucRawData[20]);
	GetValue(strValue, nWorkMode);

#if 0
	for(int kk=0; kk<100; kk++)
		printf("%02X ", ucRawData[kk]);
	printf("\n");
#endif 

	if( nICCardCode == 0 )
	{
		strValue.Format("����:%ld ",ucRawData[9]*256*256*256+ucRawData[10]*256*256+ucRawData[11]*256+ucRawData[12]);	 strText += strValue ;
		GetValue(strValue, nCardID);
	}
	else if( nICCardCode == 100 )
	{
		if( nWorkMode == 4 )
			strValue.Format("����:%ld ", 0);
		else
			strValue.Format("����:%ld ",ucRawData[10]*256*256+ucRawData[11]*256+ucRawData[12]);	 strText += strValue ;

		GetValue(strValue, nCardID);
	}
	else if( nICCardCode == 101 )
	{
		strValue.Format("����:%ld ",ucRawData[11]*256+ucRawData[12]);	 strText += strValue ;
		GetValue(strValue, nCardID);
	}
	else
	{
		strValue.Format("����:%ld ",0);	 strText += strValue ;
		GetValue(strValue, nCardID);
	}

	if( nWorkMode == 4 && (nICCardCode == 100 || nICCardCode == 101 ) )
	{
		strValue.Format("��ʾ����:%.2X%.2X%.2X%.2X%.2X ",ucRawData[8],ucRawData[9],ucRawData[10],ucRawData[11],ucRawData[12]); strText += strValue ;
		GetValue(strValue, sShowCardNo);
	}

	strValue.Format("����ʱ��:%04d-%02d-%02d %02d:%02d:%02d ",ucRawData[13]+2000,ucRawData[14],ucRawData[15],ucRawData[16],ucRawData[17],ucRawData[18]); strText += strValue ;
	GetValue(strValue, sDealDateTime);

	strValue.Format("����ģʽ����:%d ",ucRawData[20]); strText += strValue ;
	GetValue(strValue, nWorkMode);

	strValue.Format("��������:%d ",ucRawData[21]); strText += strValue ;
	GetValue(strValue, nTimerType);

	strValue.Format("���ʹ���:%d ",ucRawData[22]); strText += strValue ;
	GetValue(strValue, nICCardCode);

	strValue.Format("��Ӧͷ���:%d ",ucRawData[23]); strText += strValue ;
	GetValue(strValue, nInductorNo);

	strValue.Format("���°���:%d ",ucRawData[24]); strText += strValue ;
	GetValue(strValue, nDutyFlag);
	if( nDutyFlag > 9 )
		nDutyFlag = 0 ;

	strValue.Format("���ױ��:%.2X ",ucRawData[25]); strText += strValue ;
	GetValue(strValue, sDealCode1);

	if(ucRawData[25] == 0x00)
		strValue = "�ڿ����� ";
	else if(ucRawData[25] == 0x01)
		strValue = "�Ƿ��� ";
	else if(ucRawData[25] == 0x02)
		strValue = "��;�ο� ";
	else if(ucRawData[25] == 0x03)
		strValue = "Ǯ����ʽ�� ";
	else if(ucRawData[25] == 0x05)
		strValue = "�޷�д�� ";
	else if(ucRawData[25] == 0x10)
		strValue = "������� ";
	else if(ucRawData[25] == 0xA0)
		strValue = "����ʱ����ڴ� ";
	else if(ucRawData[25] == 0xA1)
		strValue = "�������� ";
	else if(ucRawData[25] == 0xA2)
		strValue = "ʱ�������� ";
	else if(ucRawData[25] == 0xFA)
		strValue = "��ֵ���� ";
	else if(ucRawData[25] == 0xFE)
		strValue = "�������� ";
	else if(ucRawData[25] == 0x99)
		strValue = "��ȷ���� ";
	else 
		strValue = "δ֪���� ";

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
//*����: void CSmartSRCTable::EnableSaveFile(bool bBool)
//*����: ����Ϊ�Ƿ񱣴�Ϊ�ļ�
//*����: ��
//*����: ��
//*˵��: ��������
//*========================================================================================
void CSmartSRCTable::EnableSaveFile(bool bBool)
{
	m_bSaveFile = bBool ;
}

//*========================================================================================
//*����: void CSmartSRCTable::EnableSaveDB(bool bBool)
//*����: ����Ϊ�Ƿ񱣴�Ϊ���ݿ�
//*����: ��
//*����: ��
//*˵��: ��������
//*========================================================================================
void CSmartSRCTable::EnableSaveDB(bool bBool)
{
	m_bSaveDB = bBool ;
}

//*========================================================================================
//*����: bool CSmartSRCTable::Convert(TSSmartDoc *pDoc, unsigned char *ucRawData)
//*����: ת���ṹ
//*����: ��
//*����: �Ƿ�ɹ�
//*˵��: ��������
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
//*����: bool CSmartSRCSFTable::Write()
//*����: ���浽�ļ������ݿ�
//*����: ��
//*����: ��
//*˵��: ��������
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
//*����: bool CSmartSRCTable::SvaeToDB(CString strSQL)
//*����: ���浽���ݿ�
//*����: ��
//*����: �ɹ����
//*˵��: ��������
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
		ReportLog(RET_DBBUSY, "ʵʱ�ռ�����", "���浽���ݿ�ʱ, ���ܵõ����ݿ���!");
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
			ReportLog(nRec, "����ԭʼƾ֤��", "���ݿⲻ�ܴ���ԭʼƾ֤��!");
			FreeDBHandle(nDatabase);
			return false;
		}

		sprintf(m_pDoc->m_szTableName, "SMART_SRC%d", m_pDoc->m_nAuthID);

		if( ExecuteSQL(nDatabase, strSQL.GetBuffer(0)) != RET_OK )
		{
			ReportLog(nRec, "дԭʼƾ֤��", strSQL.GetBuffer(0));
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
//*����: bool CSmartSRCTable::SvaeToFile(CString strText)
//*����: ���浽�ļ�
//*����: ��
//*����: �ɹ����
//*˵��: ��������
//*========================================================================================
bool CSmartSRCTable::SaveToFile(CString strText)
{
	return true;	

}


//*========================================================================================
//*����: CSmartSRCTable* CSmartSRCTable::Alloc(TSSmartDoc *pDoc)
//*����: ����һ��ʵʱ���ݱ�
//*����: ��
//*����: �ɹ����
//*˵��: ��������
//*========================================================================================
CSmartSRCTable* CSmartSRCTable::Alloc(TSSmartDoc *pDoc)
{
	CSmartSRCTable *pTable = NULL ;

	switch(COperator::GetMachineType(pDoc))
	{
	case MACHINE_TYPE_5301:     //������
	case MACHINE_TYPE_1056:     //�ֳֻ�(�Ʒ�+����)
		pTable = new CSmartSRCBZTable;
		break;
	case MACHINE_TYPE_0201:     //��ֵ��
	case MACHINE_TYPE_0226:     //�շѻ�
	case MACHINE_TYPE_0228:     //���ػ�
	case MACHINE_TYPE_0230:     //�����
	case MACHINE_TYPE_0232:     //�ϻ�������
	case MACHINE_TYPE_0234:     //��ԡ�����
	case MACHINE_TYPE_0236:     //0236 ����ʽ��ԡ�Ʒ���
	case MACHINE_TYPE_0240:     //��Ʊ��
	case MACHINE_TYPE_0130:     //���ʶ���
	case MACHINE_TYPE_1055:
	case MACHINE_TYPE_0248://�Ϻ���ת�ʻ�
		pTable = new CSmartSRCSFTable;
		break;
	case MACHINE_TYPE_0140:     //��Ʊ��
		pTable = new CSmartSRCJPJTable;
		break;
	case MACHINE_TYPE_0121:     //��ʱ��
	case MACHINE_TYPE_5501:     //����ͨ����
		pTable = new CSmartSRCJSBTable;
		break;
	case MACHINE_TYPE_0224:     //��ʧ��
		pTable = new CSmartSRCGSJTable;
		break;
	default:
		break;
	}

	return pTable;
}

//*========================================================================================
//*����: void CSmartSRCTable::Release(CSmartSRCTable *pTable)
//*����: �ͷ�һ��ʵʱ���ݱ�
//*����: ��
//*����: �ɹ����
//*˵��: ��������
//*========================================================================================
void CSmartSRCTable::Release(CSmartSRCTable *pTable)
{
	switch(pTable->m_nType)
	{
	case MACHINE_TYPE_5301:     //������
	case MACHINE_TYPE_1056:     //�ֳֻ�(�Ʒ�+����)
		delete (CSmartSRCBZTable*)pTable;
		break;
	case MACHINE_TYPE_0201:     //��ֵ��
	case MACHINE_TYPE_0226:     //�շѻ�
	case MACHINE_TYPE_0228:     //���ػ�
	case MACHINE_TYPE_0230:     //�����
	case MACHINE_TYPE_0232:     //�ϻ�������
	case MACHINE_TYPE_0234:     //��ԡ�����
	case MACHINE_TYPE_0236:     //0236 ����ʽ��ԡ�Ʒ���
	case MACHINE_TYPE_0240:     //��Ʊ��
	case MACHINE_TYPE_0130:     //���ʶ���
	case MACHINE_TYPE_1055:
	case MACHINE_TYPE_0248://�Ϻ���ת�ʻ�
		delete (CSmartSRCSFTable*)pTable;
		break;
	case MACHINE_TYPE_0140:     //��Ʊ��
		delete (CSmartSRCJPJTable*)pTable;
		break;
	case MACHINE_TYPE_0121:     //��ʱ��
	case MACHINE_TYPE_5501:     //����ͨ����
		delete (CSmartSRCJSBTable*)pTable;
		break;
	case MACHINE_TYPE_0224:     //��ʧ��
		delete (CSmartSRCGSJTable*)pTable;
		break;
	default:
		delete pTable;
		break;
	}
}

