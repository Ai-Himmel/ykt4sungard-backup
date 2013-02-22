// Operator.h: interface for the COperator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPERATOR_H__E01A02C6_A08C_48FB_A5D0_022E902913BD__INCLUDED_)
#define AFX_OPERATOR_H__E01A02C6_A08C_48FB_A5D0_022E902913BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//�������еĻ���
enum MachineType
{
	MACHINE_TYPE_UNKNOW,   //δ֪�Ļ���
	MACHINE_TYPE_5301,     //������
	MACHINE_TYPE_0201,     //��ֵ��
	MACHINE_TYPE_0226,     //�շѻ�
	MACHINE_TYPE_0228,     //���ػ�
	MACHINE_TYPE_0230,     //�����
	MACHINE_TYPE_0232,     //�ϻ�������
	MACHINE_TYPE_0234,     //��ԡ�����
	MACHINE_TYPE_0240,     //��Ʊ��
	MACHINE_TYPE_0130,     //���ʶ���
	MACHINE_TYPE_0140,     //��Ʊ��
	MACHINE_TYPE_0121,     //��ʱ��
	MACHINE_TYPE_0224,     //��ʧ��
	MACHINE_TYPE_0236,     //����ʽ��ԡ�Ʒ���
	MACHINE_TYPE_1055,     //�ֳֻ����Ʒѣ�
	MACHINE_TYPE_5501,     //����ͨ����
	MACHINE_TYPE_1056      //�ֳֻ�(�Ʒ�+����)
};

//������������
enum MacDataType
{
	MACDATA_TYPE_JY,		//Ϊ������������
	MACDATA_TYPE_ZZ,		//Ϊ��������
	MACDATA_TYPE_BZ,		//Ϊ��������
	MACDATA_TYPE_UNKNOW		//δ֪����������
};

//*******************************************************************************
//*����: COperator  
//*����: ҵ������
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
	static CString  m_strAccTime;		//��ʱ����ʱ��
	static CString  m_strBlackVer;      //�������汾
	static CString  m_strRight;         //��Ȩ��
	static bool     m_bReadPara;        //�Ѷ��������־

protected:
	CString         m_strTaskCode;
	bool            m_bMarkCheck;
	bool            m_bMachineNo;

	TSSmartDocEx   *m_pDocEx;
	TSCmdBuffer    *m_pBuffer;
	TSSmartTask    *m_pTask;

	TSSmartDoc     *m_pDoc;			//ָ��Ĭ�ϵ��豸��Ϣ
	long            m_nIndex;		//ָ��Ĭ�ϵ��豸
	long            m_nPort;		//ָ��ǰ�˿�

protected:
	virtual void OnPacketError(long nResult);

	//CRCУ���
	virtual void OnCRCError();

	//MARKֵ��
	virtual bool OnMarkValueError(TSSmartDoc *pDoc, TSSmartTask *pTask, TSCmdBuffer *pBuffer, int nMark);

	//��Ȩ�Ų�����
	virtual void OnAuthNoError(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	//���Ŵ���
	virtual void OnMachineNoError(TSSmartDoc *pDoc, int nNo);

	//��֧�ֵĻ���
	virtual void OnMacTypeError();

	virtual void WriteFile(char *pszFileName, char *pBuffer);

	//дϵͳ�쳣��־
	void WriteError(char *pszDeviceID, const char *format, ...);

	//����ҵ��ϵͳ����
	bool ReadSmartSetup();

public:
	void ReportException(CString strText, BYTE *pszByte, int nLen);

	//�õ����ʹ���
	static MachineType GetMachineType(TSSmartDoc *pSmartDoc);

	//�õ���������
	MacDataType GetMacDataType(TSCmdBuffer *pBuffer);

	//��λ�豸
	virtual bool ResetDevice(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	//�޸�ע���
	virtual bool ModifyRegister(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer);

	virtual bool ModifyRegisterEx(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer, int nPort);

	//����ö˿����ݣ������ռ�
	virtual bool ClearPortData(TSSmartDoc *pDoc, TSCmdBuffer *pBuffer, int nPortNo);

	//�޸Ĳ���������
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

	//������ݰ�
	virtual bool CheckPacket(TSCmdBuffer *pBuffer);

	//��ⷵ������������Ƿ����
	virtual bool CheckMachineNo(TSSmartDocEx *pDocEx, TSCmdBuffer *pBuffer);

	//���REMARKֵ�Ƿ����
	virtual bool CheckMarkValue(int nMark);

	//������һ�������
	virtual long CreateBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer) = 0 ;

	//����������, ����ʵ�־����ҵ������
	virtual long ProcessData(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer) = 0 ;
	//�豸�ն�״̬
	long ProcessStatusRequest(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	//������������
	long ProcessRequest(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

//*******************************************************************************
//*����: CSmartLog
//*����: ҵ�����־��
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
