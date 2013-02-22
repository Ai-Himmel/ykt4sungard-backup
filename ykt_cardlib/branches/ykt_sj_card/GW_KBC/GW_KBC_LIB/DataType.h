#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_
#pragma once

#include "kbclt.h"

static char g_msg[1024] = "";		// ע�⾡����������Ϊ >=1024�ֽ�
static KBDCHandle g_gw_handle;		// KBDCȫ�־��
static bool g_handle_flag = false;	// KBDCȫ�־����־

#pragma pack(1)
typedef struct _CheckBillSerial 
{
	int 	 serial_no;			//�����շѽ�����ˮ��
	int 	 customer_id;		//�ͻ���ʶ
	int	 	 card_id;			//���׿���
	char 	 operate_date[11];	//��������
	char     operate_time[9];	//����ʱ��
	int      serial_state;      //��ˮ״̬��2��ʾ���˳ɹ�(�ɹ�����)��1��ʾ//δ�����ˣ���ʱ�����¼��
	double   trade_fee;			//���׽��
	double   in_fee;			//�뿨ֵ
	double   out_fee;			//����ֵ
	int	     device_id;			//���׷����豸ID��
	int      sys_id;			//�ⲿϵͳ��ʶ��ת�˳ɹ�Ϊ0�����ɹ�Ϊ1001(��
								//ʱ��¼)
	char     cut_name[61];		//�ͻ�����
	char     stuemp_no[21];		//ѧ����
} CheckBillSerial;

typedef struct _CardInfo 
{
	int 	 card_id;			//���׿���
	int 	 customer_id;		//�ͻ���
	char     physical_no[9];	//������
	char     state_id[5];		//��״̬
	char     password[33];		//������
} CardInfo;

typedef struct _CutInfo 
{
	int 	 customer_id;				//�ͻ���
	char 	 cut_name[21];				//�ͻ�����
	char     classdept_no[11];			//���ű��
	char     class_no[11];				//�༶���
	char     classdept_name[151];		//��ϵ�˲��Ż��߰༶����
	char     stuemp_no[21];				//ѧ����
} CutInfo;

typedef struct _DataInfo              
{
	int      cut_id;                //�ͻ�ID��      
	char	 cut_name[21];			//�ͻ�����
	char     class_no[11];			//�༶
	char     classdept_no[11];		//���ű��
	char 	 classdept_name[151];	//��ϵ�˲��Ż��߰༶����
	char     password[33];			//������, ��ʱ��Ϊ�����ֶ�
	char     state_id[5];			//��״̬, �����ֶ�
	char     stuemp_no[21];			//ѧ����
} DataInfo;
#pragma pack()

#endif