//********************************************************
//kst_struct.h
//********************************************************
#ifndef _KST_STRUCT_H
#define _KST_STRUCT_H
/////////////////////////////////////////////////////////
//     �����Ĳ�ѯ
/////////////////////////////////////////////////////////
typedef struct kst_ald_sqr
{
	char idf[8];              //��ʶ��
	char trcd[4];             //������
	char roomname[30];         //�տ��ʺ�
	char stdu[20];            //ѧ����
	char name[60];            //����
	char tmlid[12];           //�ն�
	char  amt[30] ;           //���
    char area[30];            //������Ϣ
}ald_sqr;

typedef struct kst_ald_sqrrec
{
	char idf[8];              //��ʶ��
	char trcd[4];             //������
	char roomname[30];         //�տ��ʺ�
	char accountmsg[100];     //�ʺ���Ϣ
	char addamt[30] ;         //���ӽ��
    char msg[4];              //��Ϣ
}ald_sqrrec;

////////////////////////////////////////////////////
//           ������ת��
////////////////////////////////////////////////////

typedef struct kst_ald_pay
{
	char idf[8];              //��ʶ��
	char trcd[4];             //������
	char account[30];         //�տ��ʺ�
    char payaccount[30];      //֧���ʺ�
	char customerid[30];      //�ͻ���
	char stdu[20];            //ѧ����
	char name[60];            //����
	char schid[3];            //ѧУ��
	char tmlid[12];           //�����ն˺�
	char  bfamt[30];          //����ǰ���
	char  payamt[30] ;        //֧�����
    char datetime[14];        //����ʱ��
	char rfn[14];             //���ײο���
	char paycode[30];         //֧������
	char paytype[4];          //��������
	char remark[100];         //��ע
    char code[32];            //��֤��
}ald_pay;

typedef struct kst_ald_payrec
{
	char idf[8];              //��ʶ��
	char trcd[4];             //������
	char account[30];         //�տ��ʺ�
	char accountmsg[100];     //�ʺ���Ϣ
	char addamt[30] ;         //���ӽ��
	char rfn[14];             //���ײο���
	char result[4];          //���׽��
	char remark[100];            //������Ϣ
	char code[32];            //��֤��
}ald_payrec;
/////////////////////////////////////////////////////////////
//                    ��������
/////////////////////////////////////////////////////////////

typedef struct  kst_ald_rvs
{
	char idf[8];              //��ʶ��
	char trcd[4];             //������
	char account[30];         //�տ��ʺ�
	char tmlid[12];           //�����ն˺�
	char payamt[30] ;        //֧�����
	char rfn[14];             //���ײο���
	char remark[100];         //��ע
    char code[32];            //��֤��
}ald_rvs;

typedef struct kst_ald_rvsrec
{
	char idf[8];              //��ʶ��
	char trcd[4];             //������
	char account[30];         //�տ��ʺ�
	char accountmsg[100];     //�ʺ���Ϣ
	char addamt[30] ;         //���ӽ��
	char rfn[14];             //���ײο���
	char result[30];          //���׽��
	char area[30];            //������Ϣ
	char code[32];            //��֤��
}ald_rvsrec;
#endif