#ifndef _KSG_GWDLL_H_
#define _KSG_GWDLL_H_

#ifdef __cplusplus
extern "C" {
#endif

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
//! ͨ��ѧ���Ž��й�ʧ
/*
\ param stuempno ѧ����
\ param passwod ������
\ param validate_pwd ��֤������, 1��ʾʹ�����룬0��ʾ��ʹ������
\ return ����Ϊ0��ʾ��ȡ�ɹ�, ʧ�ܷ��ش�����
*/
int API_EXPORT KGetLossOfSthByStuempNo(const char stuempno[21], const char password[7], int validate_pwd);

//! ���н��
/*
\ 
\ return ����Ϊ0��ʾ�ӹҳɹ�, ʧ�ܷ��ش�����
*/
int API_EXPORT KGetRescind();

#ifdef __cplusplus
}
#endif

#endif // _KSG_GWDLL_H_
