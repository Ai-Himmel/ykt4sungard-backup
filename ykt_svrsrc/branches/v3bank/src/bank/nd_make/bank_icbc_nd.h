/* ----------------------------------------------------------
 * �������ƣ�bank_iccb_nd.h
 * �������ڣ�2010-10-26
 * �������ߣ�xlh
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��ɵ罨�нӿڵ�ͷ�ļ�����
 * ----------------------------------------------------------*/


#ifndef __BANK_ICBC_ND_H__
#define __BANK_ICBC_ND_H__

#define QUERY_CODE               "000201"     //����ѯ
#define TRANS_CODE           "000202"     //�ʽ�ת��
#define REV_TRANS_CODE       "000203"     //Ȧ�潻�׳���
#define CHECK_CODE           "000301"    //���׼�¼������
#define SCHOOLCODE           "CNDCD19005"    //ѧУ����
#pragma pack(1)
typedef struct {
    char PACKLEN[4];                // ������
    char RespCode[4];                    //��Ӧ��
    char RespMess[100];                  //��Ӧ��Ϣ
} PACKHEAD;

typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_TERM[8];               // �ն˺�
    char DCC_LS[6];                 // Ȧ����ˮ��
    char DCC_ID_NO[18];             // ѧ��
    char DCC_ACC_NO[20];            // ���п���
    char DCC_TYPE[1];               // ֤������
    char DCC_NO[20];                    //֤������
    char DCC_NAME[20];              // ����
    char DCC_DDP_RMRK[32];          // ��ע1
    char DCC_DEP_RMRK[32];          // ��ע2
    char DCC_DRW_RMRK[32];          // ��ע3
} QUERY_BODY_REQ;

typedef struct {
    PACKHEAD head;
    QUERY_BODY_REQ body;
} QUERY_REQ;

typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_TERM[8];               // �ն˺�
    char DCC_LS[6];                 // Ȧ����ˮ��
    char DCC_BANK_LS[20];                   //������ˮ
    char DCC_ID_NO[18];             // ѧ��
    char DCC_ACC_NO[20];            // ���п���
    char DCC_TYPE[1];               // ֤������
    char DCC_NO[20];                    //֤������
    char DCC_NAME[20];              // ����
    char DCC_BAL[18];               //�ʺ����
    char DCC_AVL_BAL[18];           // �������
    char DCC_MEMO[40];              // ��ע
} QUERY_BODY_ANS;

typedef struct {
    PACKHEAD head;
    QUERY_BODY_ANS body;
} QUERY_ANS;

typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_TERM[8];               // �ն˺�
    char DCC_LS[6];                 // Ȧ����ˮ��
    char DCC_ID_NO[18];             // ѧ��
    char DCC_ACC_NO[20];            // ���п���
    char DCC_TYPE[1];               // ֤������
    char DCC_NO[20];                    //֤������
    char DCC_NAME[20];              // ����
    char DCC_AMT[18];                          //���׽��
    char DCC_DDP_RMRK[32];          // ��ע1
    char DCC_DEP_RMRK[32];          // ��ע2
    char DCC_DRW_RMRK[32];          // ��ע3
} TRANS_BODY_REQ;

typedef struct {
    PACKHEAD head;
    TRANS_BODY_REQ body;
} TRANS_REQ;


typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_TERM[8];               // �ն˺�
    char DCC_LS[6];                 // Ȧ����ˮ��
    char DCC_BANK_LS[20];                   //������ˮ
    char DCC_ID_NO[18];             // ѧ��
    char DCC_ACC_NO[20];            // ���п���
    char DCC_TYPE[1];               // ֤������
    char DCC_NO[20];                    //֤������
    char DCC_NAME[20];              // ����
    char DCC_AMT[18];               //�ʺ����
    char DCC_MEMO[40];              // ��ע
} TRANS_BODY_ANS;

typedef struct {
    PACKHEAD head;
    TRANS_BODY_ANS body;
} TRANS_ANS;

typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_TERM[8];               // �ն˺�
    char DCC_LS[6];                 // Ȧ����ˮ��
    char DCC_BANK_LS[20];           //������ˮ��
    char DCC_ACC_NO[20];            // ����ԭ������ˮ��
    char DCC_MEMO[40];              // ��ע
} REVTRANS_BODY_REQ;

typedef struct {
    PACKHEAD head;
    REVTRANS_BODY_REQ body;
} RECTRANS_REQ;

typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_BANK_LS[20];                   //������ˮ
    char DCC_MEMO[40];              // ��ע
} RECTRANS_BODY_ANS;

typedef struct {
    PACKHEAD head;
    RECTRANS_BODY_ANS body;
} RECTRANS_ANS;

typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
} CHECK_BODY_REQ;

typedef struct {
    PACKHEAD head;
    CHECK_BODY_REQ body;
} CHECK_REQ;


typedef struct {
    char DCC_CODE[6];               // Ȧ�潻����
    char DCC_SCHID[10];             //ѧУ����
    char DCC_DATE[8];               //��������
    char DCC_COUNT[10];                      //������ˮ
    char DCC_SUM[12];                          //������ˮ
    char DCC_FILE[40];              // �����ļ���
} CHECK_BODY_ANS;

typedef struct {
    PACKHEAD head;
    CHECK_BODY_ANS body;
} CHECK_ANS;

#pragma pack()
#endif

