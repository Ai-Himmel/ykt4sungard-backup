/********************************************************
* �ļ�����: ʵ����������Խ�ʱ����ж�̬���ض�̬��
* �ļ���:	DllFun.h
* ˵��:		��̬�������ݽṹ�ڴ�,��̬�����ɵ���������.h�ļ�
* ����:		����
* ʱ��:		2007-07-02
* �޸�ԭ��: 
**********************************************************/

#ifndef _DLL_FUN_H_
#define _DLL_FUN_H_
#pragma once

#include "DllFunErrCode.h"
#include <Windows.h>

#ifndef _DYNAMIC_LOAD		// ������̬���ص�������̬��		
#define _DYNAMIC_LOAD
#endif

#ifndef SYNJONES_FUNC		// �������������º���		
#define SYNJONES_FUNC
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* �Խӵ�����������Ϣ�ṹ                                          
/************************************************************************/
#pragma pack(1)
typedef struct _Data_Info 
{
	int      cut_id;                //�ͻ�ID��
	char	 physical_no[9];		//������
	char	 old_physical_no[9];	//��������(������ʱ���������Ŵ���)
	int		 card_state;			//��״̬, ��state_id��card_flag��ᵽһ����־��
	int      cut_type;				//�ͻ����, �ͻ������, ���ƶ�Ӧ11, �о�����Ӧ13�ȵ�
	char     cut_type_name[51];		//�ͻ��������, ������, �о�������
	char	 cut_name[61];			//�ͻ�����
	char     volume[13];			//���°汾��(070403102045), һ��ͨ���ݿ�����ȡ���µİ汾�ŵ����ݴ��͸��󷽣������ҷ��������˹�ʧ��state_id�ֶη����仯����Ὣ���˵İ汾������Ȼ���͵�ʱ����������İ汾������ʶ�ļ�¼�����͸��Է�.
	char 	 classdept_name[101];	//��ϵ�˲�������, ����ϵ,��ѧϵ�ȵ�
	char 	 stuemp_no[21];			//ѧ����
	char	 sex[2];				//�Ա�(1Ϊ��, 2ΪŮ)
	int  	 card_id;				//���׿���
	int 	 type_id;				//�����: (1��ʽ��, 2��ʱ��, 3�Ǽ�����ʱ
									//��, 4VIP������ʱ��, 5������ʱ��)
	char 	 show_id[11];			//��ʾ����	
	int      area;					//�ͻ���������
	char     area_name[51];			//�ͻ���������
	char	 main_id[21];			//���֤��
	char	 reg_time[31];			//�û�ע��ʱ��
	char	 can_time[31];			//�û�ע��ʱ��, ��̫׼ȷ��Ӧ����ѧУ����
//	double   curBalance;			//����ǰ�������
//	char	 state_id[5];			//��״̬(4���ֽ�) ע��1000, ע��2000,��
									//��3000����ʧ1100������1010, д��ʧ��
									//1001, ��ʧ����1110, ��ʧ����д��ʧ��1111
//	int      cut_state;				//�ͻ�״̬(1Ϊע��, 2Ϊע��)
//	double   frozenBalance;		    //�������
//	int      acc_current_state;     //�ʻ���ǰ״̬, 1ע��, 2ע��, 3����
//	int      card_flag;				//��Ƭ״̬����,���¿���Ҫ�õ�(1 �˿�״̬, 2 ��
									//����״̬, 3 �����ľɿ�״̬, 4 ���¿�״̬, -1��ʾ�����ڴ��࿨)
}Data_Info;

typedef struct _Save_Info
{
	int		cut_id;		//�ͻ�ID��(�ʺ�)
	int     save_Money;	//ת�ʽ��,��ȷ����
	int     save_type;	//0=��Ǯ,1=����
}Save_Info;

#pragma pack()

/************************************************************************/
/* ���ض�̬��궨��                                                                     
/************************************************************************/
#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
	{ \
		::FreeLibrary(handle); \
		handle = NULL; \
		return DLLFUN_ERR_NO_FUNADDRESS; \
	}

/************************************************************************/
/* ���ض�̬�⺯��, �Խӵ�������Ϣ����
/************************************************************************/
// ˮ��ת��
DCLR_DLLFUNC(int,GetDataInfo,(Data_Info *in_pack, int *errcode));
DCLR_DLLFUNC(int,SaveInfo,(Save_Info *in_pack, int *errcode));
//#ifdef SYNJONES_FUNC
DCLR_DLLFUNC(int,InitDB,());
//#else
//	NULL;
//#endif
DCLR_DLLFUNC(int,CloseDB,());

// ���ת��
DCLR_DLLFUNC(float,CNectDB,(bool is_connect));
DCLR_DLLFUNC(int,GetRoomName,(int room_code, char *room_name));
DCLR_DLLFUNC(int,SellElec,(int room_code, int money, char *room_name));
DCLR_DLLFUNC(int,GetDBStatus,());
DCLR_DLLFUNC(int,GetRemainE,(int nRoomCode,char * sElecDate));
//DCLR_DLLFUNC(float,GetEPrice,());

#ifdef __cplusplus
}
#endif

#endif