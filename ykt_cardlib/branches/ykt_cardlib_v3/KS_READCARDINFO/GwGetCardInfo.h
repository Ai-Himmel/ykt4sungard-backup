#ifndef _GW_GETCARDINFO_H_
#define _GW_GETCARDINFO_H_

#pragma once
#pragma pack(1)

typedef struct _tagCardInfo
{
	// <! ���׿���
	int cardid;
	// <! ѧ����
	char stuemp_no[21];
	// <! ����
	char name[4];
	// <! ������
	char phyid[9];
	// <! ��ʾ����
	char cardno[11];
	// <! ��λ����
	char deptno[11];
	// <! ��λ����
	char deptname[51];
	// <! ������
	int cut_name[51];
	// <! �Ա�, 1�У� 2Ů�� 9 ����
	int sex;
	// <! ���������
	char card_type_name[51];
}CardInfo_t;

#pragma pack()

/// �����붨��
// <! �ɹ�
#define KE_SUCCESS 0

// <! δ֪����
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

// ! ��½ע�ᵽӦ�÷�����
/*
\return ����0��ʾ��½�ɹ�, ʧ�ܷ��ش�����
*/
int KGetErrorNo();

//! ��ȡ������Ϣ
void KGetErrorMsg(char msg[512]);

//! ͨ�������Ŷ�ȡ��Ա��Ϣ
/*
 \param phyid ������,�������� '\0' ����
 \param tCard ��Ա��Ϣ
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int KGetCardInfoByPhyId(const char phyid[9],CardInfo_t* tCard);

//! ͨ����ʾ���Ŷ�ȡ��Ա��Ϣ
/*
 \param cardno ��ʾ����, �������� '\0' ����
 \param tCard ��Ա��Ϣ
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int KGetCardInfoByCardNo(const char cardno[21],CardInfo_t* tCard);

//! ͨ��ѧ���Ŷ�ȡ��Ա��Ϣ
/*
 \param stuempno ��ʾ����, �������� '\0' ����
 \param tCard ��Ա��Ϣ
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */

int KGetCardInfoByStuempNo(const char stuempno[21],CardInfo_t* tCard);
//! ��ȡ��Ա��Ϣ
/*
 \brief ���˳��, phyid , cardno, stuempno ,����һ��Ϊ��,�����һ��
 \param phyid
 \param cardno
 \param stuempno
 \param tCard
 \return ���� 0 ��ʾ��ȡ�ɹ�,ʧ�ܷ��ش�����
 */
int KGetCardInfo(const char phyid[9],const char cardno[21]
							,const char stuempno[21],CardInfo_t* tCard);

//! ͨ�������Ŷ�ȡѧ����
/*
\ param phyid ��Ҫ�����������
\ param stuempno ��Ҫ��õ�ѧ����
\ return ����0��ʾ�ɹ�������ʧ�ܷ��ش�����
*/
int KGetStuempNoByPhyid(const char phyid[9], char stuemp_no[21]);

// !������ʼ������
/*
\ ����ʵ�ִ�����Ϣ��DRTP�ĳ�ʼ������
\ reutn ����TURE��ʾ��ʼ���ɹ�, ��֮��ʾʧ��
*/
BOOL KInitFunc();

// !�ӷ������ϻ�ȡ��Կ
/*
\ ����ʵ�ִӷ������ϻ�ȡ��Կ
\ return����0Ϊ�ɹ������ط�0���ɹ�
*/
int KRecPwdFromSvr();

#endif