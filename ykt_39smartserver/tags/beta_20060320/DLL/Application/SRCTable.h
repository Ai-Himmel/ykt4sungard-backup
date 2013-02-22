 #ifndef __SRC_TABLE_H__
#define __SRC_TABLE_H__

//*******************************************************************************
//*����: TSSRCSFTable
//*����: 0226 �շѻ�,0228 ���ػ�,0201 ��ֵ��,0232 �ϻ�������
//*      0230 �����,0234 �����(��ԡר��),0236 ����ʽ��ԡ�Ʒ���,0240 ��Ʊ��,
//*      0130 ���ʶ���,1055 �ֳֻ����Ʒѣ�
//*******************************************************************************
struct TSSRCSFTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�
	long    nTimes;				//����
	char    sWalletcode[3];		//Ǯ��
	long    nInMoney;           //�뿨���
	long    nOutMoney;          //�������

	char    sDealCode1[3];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
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
//*����: TSSRCBZTable
//*����: 5301 ���ݷ�����(������¼), 1056 �ֳֻ�(�Ʒ�+����)
//*******************************************************************************
struct TSSRCBZTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�
	long    nUserInvoice;       //��Ƭʹ����ˮ

	long    nTimes;             //IC��ʹ�ô���������Ǯ������Ϊ�գ�
	char    sWalletCode[3];     //����Ǯ�����룬��ӦǮ����ʶ�����
	long    nInMoney;           //�뿨ֵ���Է�Ϊ��λ
	long    nOutMoney;          //����ֵ���Է�Ϊ��λ
	long    nBatch;             //���κ�

	char    sInductorNo[9];     //��ӦͷID���,����ģʽ5ʱ,����������Կ�׵��豸(0~15)
	long    nDutyFlag;          //��/�°��� 1�ϰ�/0��
	long    nTimerType;         //��������,����ģʽ5ʱ,���淿���
	long    nWorkMode;          //����ģʽ(1~4)
	long    nManagerCardNo;     //����Ա����(4byte)
	char    sTicketEndDate[12]; //��Ʊ��ֹ����(������)

	char    sDealCode1[3];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
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
//*����: TSSRCJSBTable
//*����: 0121 ��ʱ��,5501 ����ͨ����
//*******************************************************************************
struct TSSRCJSBTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�

	long    nInductorNo;        //��Ӧͷ���,����ģʽ5ʱ,����������Կ�׵��豸(0~15)
	long    nDutyFlag;          //��/�°��� 1�ϰ�/0��
	long    nTimerType;         //��������,����ģʽ5ʱ,���淿���
	long    nWorkMode;          //����ģʽ(1~4)
	long    nManagerCardNo;     //����Ա����(4byte)

	char    sDealCode1[3];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
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
//*����: TSSRCJPJTable
//*����: 0140 ��Ʊ��
//*******************************************************************************
struct TSSRCJPJTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//��Ƭ�ṹ����(ʮ������)
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�

	char    sWicketID[9];       //��Ʊ���ն�ID
	long    nTicket;            //Ʊ��
	char    sTicketEndDate[12]; //��Ʊ��ֹ����(������)

	char    sDealCode1[3];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
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
//*����: TSSRCGSJTable
//*����: 0224 ��ʧ�� 
//*******************************************************************************
struct TSSRCGSJTable
{
	CString strSQL;
	CString strText;
	CString strProcStore;

	long    nAuthID;			//Auth ID
	char    sAuthData[9];		//�ϴ����ݵ�ע���
	char    sCommVer[3];		//ͨ�Ű汾�ţ�ʮ�����ƣ�
	char    sCommStart[3];		//����ͨ������ԭ��ʮ�����ƣ�
	char    sMachineCode[5];	//���ʹ���
	long    nInvoiceNo;			//�ն˽�����ˮ��
	char    sDealDateTime[24];	//��������ʱ��(YYYY-MM-DD HH24:MM:SS)
	char    sUseCard[3];		//���ʹ���
	long    nICCardCode;		//IC��������(Ԥ��)
	char    sShowCardNo[11];	//��ʾ����
	long    nCardID;			//IC�����׺Ż���ʾ����/���к�
    char    sPassword[17];      //�������루�޸�����Ϊ���ɸ������루6�����¸������루6������ʧΪ��8�ֽ�����,
	char    sDealCode1[3];      //�ն˽��״��루ʮ�����ƣ�
	char    sCRCData[9];        //������CRC У���루ʮ�����ƣ�
	char    sDateTime[24];      //�ռ�����ʱ��
	char    sAdjustCode[5];     //У�������μ�У�����������Null��ʾδУ��
	char    sDealWithDateTime[24];  //У������ʱ��
	char    sOperator[5];           //����Ա��
	long    nSendflag;              //���ͱ�־
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
//*����: CSmartSRCTable
//*����: ҵ���ʵʱ�ռ�����ת����(�����)
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
//*����: CSmartSRCBZTable
//*����: 0226 �շѻ�,0228 ���ػ�,0201 ��ֵ��,0232 �ϻ������� .....
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
//*����: TSSRCBZTable
//*����: 5301 ���ݷ�����(������¼), 1056 �ֳֻ�(�Ʒ�+����)
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
//*����: CSmartSRCJSBTable
//*����: 0121 ��ʱ��,5501 ����ͨ����
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
//*����: CSmartSRCJPJTable
//*����: 0140 ��Ʊ��
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
//*����: CSmartSRCJPJTable
//*����: 0224 ��ʧ�� 
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
 