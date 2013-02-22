#ifndef	__BANK_PUB_H__
#define	__BANK_PUB_H__

#include "tcp.h"
#include "bank.h"
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_gd.h"
#include "mac.h"
#include "Third_Mac.h"
#include "iso8583.h"

#pragma once

void Trace_Bank_Package_GSYH(BANK_GSYH_TRADE_STRUCT *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_R(BANK_ZGYH_TRADE_STRUCT_TRANS_REQ *pTransPak, char *stage);
void Trace_Bank_Package_ZGYH_A(BANK_ZGYH_TRADE_STRUCT_TRANS_ANS *pTransPak, char *stage);
int send_to_and_recv_from_bank(int const bank_id,char* pSend, int send_len,char* pRecv,int recv_len,ST_BANK_CONFIG *pBank);
void Trace_Bank_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
void Trace_Bank_Package_YNNH(BANK_YNNH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
void Trace_Bank_Package_HRBZH(BANK_HRBZH_TRADE_STRUCT_PACKET *pTransPak, char *stage);
int Get_Bank_Error_Code(void *pTransPak, int bank_id);

/*================================================================ 
* ������:      Trade_Package_YNXH
* ����1:       [in or out] (BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak)
*			   ��ȡ�������õı�������
* ����2:	   [in or out] (int trade_type) ��������: ��ѯ,����,����,����
* ����3:	   [in] (int packet_flag) ���ױ�ʶ: ��ȡ����(0), ���ñ���(1)
* ����4:       [in] (ST_BANK_CONFIG *pBank) ����ȫ�����ò����ṹ
* ����5:       [in] (INNER_TRANS_REQUEST * pNode) ��������ṹ
* ��������:    �����źϽ��ױ��Ļ��߻�ȡ�źϽ��ױ���
* ����ֵ��     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int Trade_Package_YNXH(BANK_YNXH_TRADE_STRUCT_PACKET *pTransPak, int trade_type, int packet_flag, 
							  ST_BANK_CONFIG *pBank, INNER_TRANS_REQUEST * pNode);

/*================================================================ 
* ������:      Packet_Buf_Transform
* ����1:       [in or out] (char *buf) ת����buf������
* ����2:	   [in or out] (void *packet) ���еı��ĸ�ʽ
* ����3:	   [in] (int change_flag) ѹ���ͽ����־: ����0��ʾѹ��
* 			   (packet to buf), 1��ʾ���(buf to packet)
* ����4:       [in] (int bank_id) �������: �����й�����, ũҵ���е�
* ����5:       [in] (int trade_type) ��������: ��ѯ, ����, ����, ���˵�
* ����6:       [in] (INNER_TRANS_REQUEST * pNode) ���洫��Ľṹ����
* ����7:       [in] (int serial_no) ת�ʻ��߳���ʹ�õ���ˮ��
* ��������:    �Է������ж����ݽ���ѹ�����յ������ж����ݽ��н��
* ����ֵ��     int, ��ȷ����0, ʧ�ܷ�������ֵ
================================================================*/
int Packet_Buf_Transform(char *buf, void *packet, int change_flag, 
							  int bank_id, int trade_type, 
							  INNER_TRANS_REQUEST * pNode, int serial_no); 

void Trace_8583_Package(char *_8583_buf, int _8583_length, int format, char *msg);


#endif 
