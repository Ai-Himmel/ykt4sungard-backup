#ifndef __BANK_TYPE_H_
#define __BANK_TYPE_H_

/******************************ͳһ�������ݽṹ********************************
* �ļ�����: Ȧ�����ж����ݽṹ˵��
* �ļ���:	banktype.h
* ˵��:		ʵ������ͨѶ���ݽṹ�Ͷ��˽ṹ
* ����:		����
* ʱ��:		2008-05-23
* �޸�ԭ��:
*****************************************************************************/

#pragma pack(1)

// �Ϻ����ж����ļ����ݽṹ
typedef struct	
{
	char	device_id[27];					// �豸ID��
	char    cmp_date[8];					// ���׷���ʱ��
	char    bank_account[25];				// ���п���
	char    trans_money[17];				// ת�ʽ��
	char    line_split[4];					// \r\n
}BANK_SHGH_TRADE_COMP_STRUCT;

#pragma pack()

#endif

