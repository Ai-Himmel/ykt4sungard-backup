/*******************************************************************************

	file name : PersonInfoApi.h
    Auther : Skaen
    Function : PersonInfo Call Api        

********************************************************************************/


#ifndef _PersonInfoAPI_H
#define _PersonInfoAPI_H

#include<windows.h>

#ifdef __cplusplus
#define DLLAPI                         extern "C" __declspec (dllexport)
#else
#define DLLAPI                         extern __declspec (dllexport)
#endif

typedef struct _SL_PERSON_INFO 
{
	char 	 show_id[11];		//��ʾ����
	char 	 classdept_name[101];	//��ϵ�˲�������
	char 	 stuemp_no[21];		//ѧ����
	int  	 card_id;		//���׿���
	int 	 type_id;		//�����: (1��ʽ��, 2��ʱ��, 3�Ǽ�����ʱ
					//��, 4VIP������ʱ��, 5������ʱ��)
	int      cut_id;                //�ͻ�ID��
	char     cut_type_name[51];	//�ͻ��������
	int      cut_state;		//�ͻ�״̬(1Ϊע��, 2Ϊע��)
	int      area;			//�ͻ���������(ѧУ�ƶ�)
	char	 main_id[21];		//���֤��
	char	 state_id[5];		//��״̬(4���ֽ�) ע��1000, ע��2000,��
					//��3000����ʧ1100������1010, д��ʧ��
					//1001, ��ʧ����1110, ��ʧ����д��ʧ��1111 
	char	 reg_time[31];		//�û�ע��ʱ��
	char	 can_time[31];		//�û�ע��ʱ��, ��Ϊ��Ч��ʱ��
	char	 cut_name[61];		//�ͻ�����
	char	 sex[2];		//�Ա�(1Ϊ��, 2ΪŮ)
	char	 physical_no[41];	//������
	char     volume[13];		//���°汾��(070403102045), һ��ͨ���ݿ�����ȡ���µİ汾�ŵ����ݴ��͸��󷽣�
					//�����ҷ��������˹�ʧ��state_id�ֶη����仯����Ὣ���˵İ汾������
					//Ȼ���͵�ʱ����������İ汾������ʶ�ļ�¼�����͸��Է�.
}PERSON_INFO;

DLLAPI int CALLBACK GetPersonInfo(PERSON_INFO *in_pack, int *errcode);

DLLAPI int CALLBACK CloseDB();


#endif