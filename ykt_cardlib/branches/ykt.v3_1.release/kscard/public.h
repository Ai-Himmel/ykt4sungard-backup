#ifndef  __PBULIC__H
#define  __PBULIC__H

//1.========================================��ȫ�㷨===============
unsigned char* triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* _triple_des(unsigned char key[17],unsigned char in_data[9],unsigned char out_data[9]);
unsigned char* pboc_diver_key ( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] );

/*=================================================================
* Function ID : YCT_VerifyPurchaseMac1
* Input       : unsigned char *sAppNo,			//Ӧ�����кź�8�ֽ�
unsigned char *sKey,			//16�ֽڵ���������Կ
unsigned char *sRandom,			//���ѳ�ʼ���ɹ����ص�4�ֽ�α�����
unsigned long lCardInvoiceNo,	//���ѳ�ʼ������2�ֽڵ��ѻ��������				
unsigned long lPurchMoney,		//��Ҫ���ѵĽ��	
unsigned char *TerminalNo,      //�ն˺�			
* Output      : void
unsigned char *sMac1
* Return	  : 0=�ɹ�,����ֵ=ʧ��(�����PBOC������)
* Description : ��������MAC1
*=================================================================*/
unsigned long YCT_VerifyPurchaseMac1( 
									 unsigned char *sAppNo,
									 unsigned char *sKey,
									 unsigned char *sRandom,
									 unsigned long lCardInvoiceNo,
									 unsigned long lPurchMoney,
									 unsigned char *TerminalNo,
									 unsigned char *sMac1);

/*=================================================================
* Function ID : YCT_VerifyLoadMac1
* Input       : unsigned char *sAppNo,			//Ӧ�����кź�8�ֽ�
				unsigned char *sKey,			//16�ֽڵ�Ȧ������Կ
				unsigned char *sRandom,			//Ȧ���ʼ���ɹ����ص�4�ֽ�α�����
				unsigned long lCardInvoiceNo,	//Ȧ���ʼ���ɹ����ص�2�ֽڵĽ������
				unsigned long lCardBal,			//Ȧ���ʼ���ɹ����ص�Ǯ������ǰ���
				unsigned long lAddMoney,		//��Ҫ��ֵ�Ľ��
				unsigned char *TerminalNo,		//6�ֽڵ��ն˻����
				unsigned cha  *sMac1			//Ȧ���ʼ���ɹ����ص�4�ֽ�MAC1
* Output      : void
* Return	  : 0=�ɹ�,����ֵ=ʧ��(�����PBOC������)
* Description : У��Ȧ���ʼ��ʱ�����ص�MAC1��������֤�û����ĺϷ���
*=================================================================*/
unsigned long YCT_VerifyLoadMac1( unsigned char *sAppNo,
								 unsigned char *sKey,
								 unsigned char *sRandom,
								 unsigned long lCardInvoiceNo,
								 unsigned long lCardBal,
								 unsigned long lAddMoney,
								 unsigned char *TerminalNo,
								 unsigned char *sMac1);
/*=================================================================
* Function ID : YCT_CalLoadMac2
* Input       : unsigned char *sAppNo,			//Ӧ�����кź�8�ֽ�
				unsigned char *sKey,			//16�ֽڵ�Ȧ������Կ
				unsigned char *sRandom,			//Ȧ���ʼ���ɹ����ص�4�ֽ�α�����
				unsigned long lCardInvoiceNo,	//Ȧ���ʼ���ɹ����ص�2�ֽڵĽ������			
				unsigned long lAddMoney,		//��Ҫ��ֵ�Ľ��
				unsigned char *TerminalNo,		//6�ֽڵ��ն˻����
				unsigned char *sDate,			//4�ֽڽ�������(YYYYMMDD)
				unsigned char *sTime			//3�ֽڽ���ʱ��(HHMMSS)
* Output      : unsigned char *sMac2			//4�ֽڵ�MAC2
* Return	  : 0=�ɹ�,����ֵ=ʧ��(�����PBOC������)
* Description : ����Ȧ��MAC2
*=================================================================*/
unsigned long YCT_CalLoadMac2( unsigned char *sAppNo,
							  unsigned char *sKey,
							  unsigned char *sRandom,
							  unsigned long lCardInvoiceNo,
							  unsigned long lAddMoney,
							  unsigned char *TerminalNo,
							  unsigned char *sDate,
							  unsigned char *sTime,
							  unsigned char *sMac2);

//��ȫ����MAC
unsigned char* CalSecure_MAC(
							 unsigned char *key,
							 unsigned char *random, 
							 int len,
							 unsigned char *input_data,
							 unsigned char *out_data);

//2.�ṹ��===================================================
typedef struct sCardTableIndex
{
	int		nIndexNo; //������
	char	sIndexName[64]; //��������Ӧ���ƺ���
	char	sIndexValue[64];//��������Ӧ��ֵ
	bool	bStatus;		//��ʾ�Ƿ��Ѿ���ȡ true �Ѷ�  false δ��
}ST_SCARD_TABLE_INDEX;

//����Կ
typedef struct sCardMainKey
{
	byte DPK1[17]; //����
	byte DPK2[17]; //����
	byte DLK[17];  //Ȧ��
	byte DTAC1[17];//TAC
	byte DTAC2[17]; //TAC
	byte DUK[17];   //PIN����
	byte DRPK[17]; //PIN��װ
	byte DAMK[17];//ά��
	byte DACK[17];//����
	bool bLoad;
}ST_SCARD_MAIN_KEY;

//����д��������ֵ
typedef struct sWriteCardInfo
{
	int  nIndex; //������	
	byte sValues[128]; //ֵ
}ST_SWRITECARDINFO;

//���������������ֵ
typedef struct sReadCardInfo
{
	int  nIndex; //������	
	byte sValues[128]; //ֵ
}ST_SREADCARDINFO;

//����������Ϣ
typedef struct sPublicInfo_15
{
	char	sAppSerial[21]; //Ӧ�����к�(���׿���)
	char	sShowCard[11];  //��ʾ����
	int		nCardStatus;	//��״̬
	char	sBlkVer[15];	//�������汾
	char	sDeivceID[13];	//�豸ID��
	int		nFeeType;		//���շ����
	int     nCardType;		//�����
	int		nCardVer;		//���ṹ�汾 
	char	sStartDate[9];  //��������
	char	sValidDate[9];	//��Ч����
	int		nSubsidyBatchNo;//�������κ�
	int		nPublishID;		//���з���ʶ
} ST_SPUBLICINFO_15;


//�ֿ��˻�����Ϣ
typedef struct sPersonalInfo_16
{
	int		nCustType;		//�ͻ�����
	int		nCustID;		//�ͻ���
	char	sStuEmpNo[21];	//ѧ����
	char	sName[31];		//����
	char	sDeptCode[21];	//���Ŵ���
	char	sIDNo[33];		//֤������
	int		nIDType;		//֤������
	int		nSex;			//�Ա�		1-��2-Ů
} ST_SPERSONALINFO_16;

//���׹����ļ�
typedef struct sTradeRule_12
{
	int		nOnceLimitMoney;	//����
	int		nDaySaleLimitMoney; //����
	int		nDetailMax;			//��ϸ���ֵ
} ST_STRADERULE_12;

typedef struct sPublishUserCardInfo
{
	char	sBankNo[21];
	ST_SPUBLICINFO_15	sTrFile15;
	ST_SPERSONALINFO_16 sTrFile16;
	sTradeRule_12		sTrFile12;
} ST_SPUBLISHUSERCARDINFO;


#endif