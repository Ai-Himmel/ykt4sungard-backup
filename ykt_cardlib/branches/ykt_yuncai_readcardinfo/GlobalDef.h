#ifndef _GLOBAL_DEF_H_
#define _GLOBAL_DEF_H_
#pragma once 

#define CHARGE_TERMINAL			0x01			// �շ��ն�
#define MANAGE_CENTER			(0x01 << 1)		// ��������
#define SAVING_POS				(0x01 << 2)		// ��ֵ�ն�
#define DOOR_DEVICE				(0x01 << 3)		// �Ž�
#define AUTHENTICATION_TERMINAL (0x01 << 4)		// ��֤�ն�
#define AREA_CONTROL			(0x01 << 5)		// �������
#define REMAIN_BIT_SEVEN		0				// ����
#define REMAIN_BIT_EIGHT		0				// ����

#define  CARDSTAT_TYPE_REG	 		0     	//��״̬:��ʧ1-����2-��ʧ
#define  CARDSTAT_TYPE_LOST	 		1     	//��״̬:��ʧ0-����1-��ʧ
#define  CARDSTAT_TYPE_FREEZE		2     	//��״̬ ����0-����1-����
#define  CARDSTAT_TYPE_WFAIL 		3  		//��״̬:д��ʧ��0-����1-д��ʧ��

#endif	_GLOBAL_DEF_H_