/* ----------------------------------------------------------
 * �������ƣ�bank_ccb_nm.h
 * �������ڣ�2009-08-10
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ����ɲƾ����нӿڵ�ͷ�ļ�����
 * ----------------------------------------------------------*/


#ifndef	__BANK_BCC_NM_H__
#define	__BANK_BCC_NM_H__

#define REQ_PACK_LEN 157
#define ANS_PACK_LEN 56

#define REV_REQ_PACK_LEN 107
#define REV_ANS_PACK_LEN 40

#define TRANS_CODE   		"1001"
#define REV_TRANS_CODE   	"1002"

/*
#pragma pack(1)

typedef struct{
	char packlen[4];				// ���ĳ���
	char transcode[4];				// ������ 1001
	char transdate[8];				// ��������
	char refno[14];					// һ��ͨ���ײο���
	char stuempno[32];				// ѧ����
	char name[32];					// ����
	char idcardno[18];				// ���֤��
	char bankno[32];				// ���п���
	char tradeamt[17];				// ���׽��
}TRANS_REQ;

typedef struct{
	char packlen[4];				// ���ĳ���
	char bankdate[8];				// ����ҵ������
	char bankserial[8];			// ������ˮ��
	char rescode[6];				// ��Ӧ��
	char resmsg[34];				// ��Ӧ��Ϣ
}TRANS_ANS;

typedef struct{
	char packlen[4];				// ���ĳ���
	char transcode[4];				// ������ 1001
	char transdate[8];				// ��������
	char refno[14];					// һ��ͨ���ײο���
	char stuempno[32];				// ѧ����
	char bankno[32];				// ���п���
	char tradeamt[17];				// ���׽��
}REVERSE_REQ;

typedef struct{
	char packlen[4];				// ���ĳ���
	char rescode[6];				// ��Ӧ��
	char resmsg[34];				// ��Ӧ��Ϣ
}REVERSE_ANS;

#pragma pack()
*/

#endif

