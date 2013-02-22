#ifndef _KSG_GWDLL_H_
#define _KSG_GWDLL_H_

#ifdef __cplusplus
extern "C" {
#endif
// ע��, ���ݰ��ṹ������ֽڶ���
#pragma pack(1)

typedef struct _tagCardInfo
{
	//<! ���׿���
	int cardid;
	//<! ѧ����
	char stuemp_no[21];
	//<! ����
	char name[41];
	//<! ������
	char phyid[9];
	//<! ��ʾ����
	char cardno[11];
	//<! ��λ����
	char deptno[11];
	//<! ��λ����
	char deptname[51];
	//<! ������
	int cut_type;
	//<! ��������
	char cut_name[51];
	//<! �Ա� , 1 �� 2 Ů ,9 ����
	int sex;
	//<! ��������
	int card_type_id;
	//<! ���������
	char card_type_name[51];
}CardInfo_t;

typedef struct _tSerialRec
{
	//<! ϵͳ��ʶ
	char sys_id[6];
	//<! ������
	char phy_card[12];
	//<! ���׿���
	int	 card_id;
	//<! ��������
	char tx_date[9];
	//<! ��������1
	char tx_date1[9];
	//<! ����ʱ��
	char tx_time[7];
	//<! ����ʱ��1
	char tx_time1[7];
	//<! �豸����ID
	char device_id[21];
	//<1 �豸����
	char device_name[41];
	//<! �豸����2
	char device_name2[41];
	//<! �¼�����
	char event_code[5];
	//<! �¼�����
	char event_des[61];
	//<! ����1
	char pwd1[17];
	//<! ����2
	char pwd2[17];
	//<! ����
	char card_no[21];
	//<! ����
	char card_no2[21];
	/*����Ϊ��������*/
	double amt1;
	double amt2;
	double amt3;
	double amt4;
	double amt5;
	/*����Ϊ������*/
	int	   lvol1;
	int	   lvol2;
	int	   lvol3;
	int	   lvol4;
	int	   lvol5;
}SerialRecord_t;

typedef struct _hCustomerInfo 
{
	char szName[20 + 1];					// ��ϵ������
	char szStuempNo[20 + 1];			    // ѧ����
	char szSex[1 + 1];					    // �Ա�
	char szManId[20 + 1];					// ���֤��
	char szClassDeptName[150 + 1];		    // ��������
	char szTel[20 + 1];						// ��ϵ�绰
	int  nMendFeeType;						// ҽ���շ�����(1Ϊ����, 2Ϊ�Է�)
	int  nCustomerId;						// �ͻ���(��������)
}CustomerInfo;

typedef struct _hTradeSerial 
{
	int	   nSerialNo;						// ��ˮ��
	int	   nOtherSerialNo;					// �ϴ�����ˮ��
	int    nSerialType;						// ��ˮ����
	int    nSerialState;					// ��ˮ״̬
	char   szOperateDate[10 + 1];			// ��������
	char   szOperateTime[8 + 1];			// ����ʱ��
	char   szCollectDate[10 + 1];			// �ɼ�����
	char   szCollectTime[8 + 1];			// �ɼ�ʱ��
	char   szEnteractDate[10 + 1];			// ��������
	char   szEnteractTime[8 + 1];			// ����ʱ��
	int    nMainDeviceId;					// �ϴ�����վ��ʶ
	int    nDeviceId;						// ���׷����豸��ʶ
	char   szDevphy999Id[8 + 1];			// �����豸����ID
	char   szShowId[10 + 1];				// ��ʾ����
	int    nCardId;							// ���׿���
	int    nPurseId;						// Ǯ����
	int	   nTradeCount;						// ���״���
	double dTradeFee;						// ���׽��
	double dInBalance;						// �뿨ֵ
	double dOutBalance;						// ����ֵ
	double dDepositFee;						// Ѻ����
	double dInFee;							// ������
	double dCostFee;						// ���ɱ���
	double dBoardFee;						// ����
	int    nCoustomerId;					// �ͻ�ID��
	char   szOperCode[10 + 1];				// ����Ա��
	char   szOutAccountId[16 + 1];			// �����ʺ�
	char   szInAccountId[16 + 1];			// �����ʺ�
	int    nSysId;							// �ⲿϵͳ��ʶ
	int    nTmark;							// ���ױ��
	int    nErrCode;						// ������
	int    nReviseSerialNo;					// ������ˮ��
}TradeSerial;

#pragma pack()

#ifdef GWDLL_EXPORTS
#define API_EXPORT __stdcall //__declspec(dllexport) __stdcall
#else
#define API_EXPORT __declspec(dllimport) __stdcall
#endif // GWDLL_EXPORT

#ifndef BYTE
#define BYTE unsigned char
#endif // BYTE

/// �����붨��
//<! �ɹ�
#define KE_SUCCESS 0
//<! δ֪���� 
#define KE_UNKNOWN_ERR		9999
//<! �������¼,����IP��MAC��ַ��Ϣ����ȷ
#define KE_PERMISSION_DENY	1001
//<! �������ӵ�Ӧ�÷�����,�����������
#define KE_CONNECT_ERROR	1002
//<! �����ܺŲ�����
#define KE_REQ_FUNC_NOT_EXISTS 1003
//<! ��ѯʧ��, ���ܷ�����æ
#define KE_QUERY_ERROR	1004
//<! ����ʧ��,��Ҫ���µ�¼
#define KE_NOT_LOGIN	1005
//<! ��ȡ����MAC��ַ����
#define KE_READ_LOCAL_MAC 1006
//<! ����Ƶ��̫��
#define KE_REQUEST_INTERVAL 1007

//<! ָ���Ŀ�������
#define KE_CARD_NO_EXIST	1010

//<! �����¼ʧ��
#define KE_SAVE_SERIAL		1011

//! ��¼ע�ᵽӦ�÷�����
/*
 \return ���� 0 ��ʾ��¼�ɹ�,ʧ�ܷ��ش�����
 */
int API_EXPORT KLogin();
//! ���ش�����
int API_EXPORT KGetErrorNo();
//! ��ȡ������Ϣ
void API_EXPORT KGetErrorMsg(char msg[512]);
//! ͨ�������Ŷ�ȡ��Ա��Ϣ
/*
 \param phyid ������,�������� '\0' ����
 \param tCard ��Ա��Ϣ
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int API_EXPORT KGetCardInfoByPhyId(const char phyid[9],CardInfo_t* tCard);
//! ͨ����ʾ���Ŷ�ȡ��Ա��Ϣ
/*
 \param cardno ��ʾ����, �������� '\0' ����
 \param tCard ��Ա��Ϣ
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int API_EXPORT KGetCardInfoByCardNo(const char cardno[21],CardInfo_t* tCard);

//! ͨ��ѧ���Ŷ�ȡ��Ա��Ϣ
/*
 \param stuempno ��ʾ����, �������� '\0' ����
 \param tCard ��Ա��Ϣ
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int API_EXPORT KGetCardInfoByStuempNo(const char stuempno[21],CardInfo_t* tCard);

//! ��ȡ��Ա��Ϣ
/*
 \brief ���˳��, phyid , cardno, stuempno ,����һ��Ϊ��,�����һ��
 \param phyid
 \param cardno
 \param stuempno
 \param tCard
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int API_EXPORT KGetCardInfo(const char phyid[9],const char cardno[21]
							,const char stuempno[21],CardInfo_t* tCard);
//! �ϴ���ˮ
/*
 \brief �ϴ���ˮ
 \param serial ��ˮ�ṹ
 \return ���� 0 ��ʾ�ɹ�, ʧ�ܷ��ش�����
 */
int API_EXPORT KSaveRecord(const SerialRecord_t * serial);
//! ͨ��ѧ���Ž��й�ʧ
/*
\param stuempno ѧ����
\param passwod ������
\param validate_pwd ��֤������, 1��ʾʹ�����룬0��ʾ��ʹ������
\return ����Ϊ0��ʾ��ȡ�ɹ�, ʧ�ܷ��ش�����
*/
//int API_EXPORT KGetLossOfSthByStuempNo(const char stuempno[21], const char password[7], int validate_pwd);

//! ���н��
/*
\ 
\return ����Ϊ0��ʾ�ӹҳɹ�, ʧ�ܷ��ش�����
*/
int API_EXPORT KGetRescind();

//!������
/*
 \brief �����׹���
 \param req_no ���׹��ܺ�
 \param request ���������ݰ�
 \param response ����Ӧ�����ݰ�
 \return ���� 0 ��ʾ���׳ɹ�, ʧ�ܷ��ش�����.
 */
int API_EXPORT KSendRequest(int req_no,SerialRecord_t* request,SerialRecord_t* response);

//!��ʼ����������
/*
\brief				��ʼ���������ù���
\return				���� 0 ��ʾ��ȡ��Ϣ�ɹ�, ʧ�ܷ��ش�����.
*/
int API_EXPORT KInitLocal();

//!��ȡ�ͻ���Ϣ
/*
\brief				��ȡ�ͻ���Ϣ����
\param szStuempNo	ѧ����
\param CutInfo		��ȡ�Ŀͻ���Ϣ
\return				���� 0 ��ʾ��ȡ��Ϣ�ɹ�, ʧ�ܷ��ش�����.
*/
int API_EXPORT KCustomerInfo(const char szStuempNo[21], CustomerInfo *CutInfo);

//!��ȡ��ǰ�������Ϣ
/*
\brief				��ȡ����ǰ����
\param szStuempNo	ѧ����
\param dCurBalance	��ȡ�Ŀ���ǰ���
\return				���� 0 ��ʾ��ȡ��Ϣ�ɹ�, ʧ�ܷ��ش�����.
*/
int API_EXPORT KGetCurBalance(const char szStuempNo[21], double *dCurBalance);

//!��ȡ��ˮ��Ϣ
/*
\brief					��ȡ��ˮ��Ϣ����
\param nDeviceId		ѧ����
\param Serial			��ȡ����ˮ��Ϣ
\param nNextFlag		��ȡ�Ƿ�����һ�ΰ��ı��
\param nInputFlag		������Ի�ȡ����һ�ΰ����
\param szBeginDate		��ʼ����(��:��:��)
\param szEndDate		��������(��:��:��)

\param szSerialYear		��ˮ�������
\param szSerialMonth	��ˮ�����·�
\param szBeginDay		��ˮ��ʼ����
\param szEndDay			��ˮ��������
\return					���� 0 ��ʾ��ȡ��Ϣ�ɹ�, ʧ�ܷ��ش�����.
*/
//int API_EXPORT KGetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, const char szSerialYear[5], const char szSerialMonth[3], const char szBeginDay[3], const char szEndDay[3]);
int API_EXPORT KGetTradeSerial(int nDeviceId, TradeSerial Serial[], int *nNextFlag, int nInputFlag, char szBeginDate[11], char szEndDate[11]);

//!��ȡ����������Ϣ
/*
\brief					��ȡ�������ƹ���
\param szClassDeptNo	���ű��
\param szClassDeptName  ��ȡ�Ĳ�������
\return					���� 0 ��ʾ��ȡ��Ϣ�ɹ�, ʧ�ܷ��ش�����.
*/
int API_EXPORT KGetDeptNameFromDeptNo(const char szClassDeptNo[10 + 1], char szClassDeptName[150 + 1]);

//!��ȡҽ��������Ϣ
/*
\brief					��ȡҽ�����͹���
\param nCustomerId		�ͻ���
\param nMendFeeType     ҽ������
\return					���� 0 ��ʾ��ȡ��Ϣ�ɹ�, ʧ�ܷ��ش�����.
*/
int API_EXPORT KGetMendFeeTypeFromCutId(int nCustomerId, int *nMendFeeType);

#ifdef __cplusplus
}
#endif

#endif // _KSG_GWDLL_H_
