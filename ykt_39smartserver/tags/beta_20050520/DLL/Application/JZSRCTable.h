#ifndef __JZSRC_TABLE_H__
#define __JZSRC_TABLE_H__

//*******************************************************************************
//*����: TSJZSRCSetlment
//*����: ��Ӧ�ڱ�SMART_JZSOURCEYYYYMM
//*******************************************************************************
struct TSJZSRCSetlment
{
	long    nAuthno;				//�ն˻����������������
	char    sMachineID[11];			//�ն��豸ID�ţ�Ψһʶ��,�������û�����
	char    sOrg_id[37];			//��������֯����
	long    nSettleInvoice;			//�ն˽�����ˮ��
	char    sSettleTime[24];		//����ʱ��
	char    sBeginDealtime[24];		//����Ŀ�ʼ����ʱ��
	long    nBeginInvoice;			//����Ŀ�ʼ������ˮ��
	char    sEndDealtime[24];		//����� ��������ʱ��
	long    nEndInvoice;			//����Ľ���������ˮ��
	long    nDealCount;				//�������ױ���
	long    nDealAmount;			//�������׽��
	long    nCancelCount;			//�������ױ���
	long    nCancelAmount;			//�������׽��
	long    nExcepCount;            //�쳣���ױ���
	long    nExcepACount;           //�쳣���׽��
	long    nOtherCount;			//�������ͽ��ױ���
	char    sOperatorID[5];			//�û�������
	long    nOuterkeeper;			//���ױ�־��0-���׳ɹ� 1-���ʳɹ� 2-���ʳɹ� 3-���ʴ� 4-���ʴ�
	char    sKeepingDate[24];		//��������ʱ��
	long    nBatchNo;				//��������
	long    nSettleType;			//�������ͣ���������Ա���� ����ϵͳ��ʱ�Զ����������ݽ�����ˮ��ϸ����
	char    sDealCode[3];			//�������ʹ����
};

//*******************************************************************************
//*����: TSJZSRCSource
//*����: ҵ�����������ԭʼƾ֤��
//*******************************************************************************
struct TSJZSRCSource
{
	long     AuthNo;					//�ն˻�����������
	char     sData[101];				//����
	long     nCRC;						//CRC�Ƿ���ȷ 1��ʾ��ȷ��0��ʾ����
	char     sDateTime[24];				//�ռ�����ʱ��
	long     nDealWith;					//�Ƿ���  0��ʾδ����1��ʾ�Ѵ���
	char     sDealWithDateTime[24];		//��������ʱ��
	char     sAdjustCode[5];			//����ʱ�жϸ������ݵ���ȷ���
};

//*******************************************************************************
//*����: CSmartJZSRCTable
//*����: ҵ�����������ת����
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